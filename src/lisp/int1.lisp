;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module INT1

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Lowell B. Hawkinson, Mark H. David, et al.



;;; Split from module INT by jh on 9/12/90.  (Previously, INT was called ICP.)
;;; INT1 contains ICP data structures and the various ICP formalisms.







;;;; Forward References in INT1

(declare-forward-references (:suppress-module-checks-for gsi)
  (reclaim-resumable-icp-output-task-queue-vector          function INT2)
  (transmit-icp-output-if-ready                            function INT2)
  (abort-for-icp-catcher?                                  variable INT2)
  (number-of-icp-bytes-ready-to-read                       variable INT2)
  (number-of-icp-bytes-for-message-series                  variable INT2)
  (number-of-icp-bytes-to-fill-buffer                      variable INT2)
  (number-of-icp-bytes-left-in-message-series              variable INT2)
  (set-up-icp-object-index-space                           function INT3A)
  (reclaim-icp-version-info                                function INT3B)
  (get-remote-host-name                                    function INT3B)
  (reclaim-index-space-location-and-corresponding-objects  function INT4)
  (shutdown-icp-socket-connection                          function INT4)
  (reclaim-gsi-list-function                               function GSI-COMMON)
  (reclaim-gsi-extension-data                              function GSI-COMMON)
  (gsi-initialize-icp-socket                               function GSI-COMMON)
  )

(declare-forward-reference gsi-connection-lost variable)
(declare-forward-reference gsi-resumable-icp-error variable)
(declare-forward-reference gsi-use-references-p variable)
(declare-forward-reference note-item-deleted-from-frame-serial-number-table function INT4)
(declare-forward-reference framep-function function)
(declare-forward-reference c-x11-draw-pixmap function) ; IMAGES


;;; `reclaim-frame-serial-number' - is actually defined earlier, in utilities4.
;;; But it is only defined in the ab system (G2).  It's also only called from
;;; that system, but it is referenced in this file, which is also part of TW.
;;; And so, when compiling TW in development (on this date) we got a warning.
;;; We used to not get this warning because there was a forward-reference in
;;; platforms.lisp.  I removed that forward reference on 12/12/2007, because
;;; it surely wasn't needed there, but that was what allowed the file to compile
;;; in Telewindows without warning.  I suppose a stub is the correct solution,
;;; but this is what had been done, so this is what I'll restore.  -jv, 1/11/08

(declare-forward-reference reclaim-frame-serial-number function)

(eval-when (:compile-toplevel :load-toplevel :execute)
(defmacro size-of-variable-fill-icp-buffers () 2048)
(defmacro size-of-variable-fill-icp-buffers-in-8-bit-bytes  () 4096)
)





;;;; ICP overview



;;; File name:                     INT1.LISP
;;; File location:             ma:>ab>
;;; Code control:             Zmacs on the Explorers.
;;; Purpose:                     ICP abstractions.
;;; Contents:                     Macros to define ICP structures, data types, and
;;;                          message types
;;; This file depends on:    Preceding .LISP files in the system load ordering.
;;; Dependent files:             Subsequent .LISP files in the system load ordering.
;;; Role in products:             Linked into G2 and Telewindows.
;;; Role in development:     None.
;;; Testing harness:         Reclamation of corresponding ICP objects can be tested
;;;                          using notify-when-reclaiming-icp-object?
;;; Performace requirements: These macros create functions which are central to ICP
;;;                          operation.  Performance is critical in these functions.
;;;                          The macros themselves, however, need not pay especial
;;;                          attention to performance.
;;; Major Entities:             [macro]       def-icp-value-type-equivalence
;;;                          [macro]       def-icp-value-reader
;;;                          [macro]       def-icp-value-reader-substitution-macro
;;;                          [macro]       def-icp-value-writer
;;;                          [macro]       def-icp-value-writer-substitution-macro
;;;                          [property]    icp-value-reclaimer
;;;                          [macro]       def-icp-object-type
;;;                          [functions]   defined by def-icp-object-type
;;;                          [subst macro] icp-object-type-given-icp-object
;;;                          [defvar]      icp-message-handler-array
;;;                          [macro]       def-icp-message-type-code
;;;                          [macro]       def-icp-message-type
;;;                          [functions]   defined by def-icp-message-type
;;;                          [macro]       def-icp-message-functions
;;;                          [sys var]     active-icp-sockets
;;;                          [structure]   icp-socket
;;;                          [structure]   i-am-alive-info
;;;                          [function]    register-icp-connection-loss-callback
;;;                          [function]    deregister-icp-connection-loss-callback
;;;                          [structure]   icp-port
;;;                          [system var]  current-icp-port
;;;                          [system var]  current-icp-socket
;;;                          [system var]  current-standard-icp-object-index-space
;;;                          [system var]  current-type-of-icp-buffer
;;;                                          <deleted -ncc, 7 Mar 1996>



;;; `ICP' (Intelligent Communication Protocol) is a high-performance,
;;; application-layer protocol for interprocess communication among one or more
;;; G2's and their data and/or user interface servers.  ICP runs on top of a
;;; network protocol such as TCP/IP.  ICP was developed by Gensym Corporation.



;;; An `ICP node' is a software process that can read and/or write ICP.  `ICP
;;; input' into a node comes into an `ICP receiver' and then passes through an
;;; ICP buffer (see below) to an `ICP reader' (or `ICP handler').  `ICP output'
;;; from a node is generated by an `ICP writer' and passes through an ICP buffer
;;; before being sent out by an `ICP transmitter'.  Each ICP input and output
;;; into a node is represented by an ICP port (see below) that holds an `ICP
;;; connection handle', a queue of ICP buffers, and other parameters and state
;;; information.  (Note that ICP receivers and transmitters may run in processes
;;; that are separate from the processes in which their associated ICP readers
;;; and writers run.)

;;; An `ICP connection' is an ICP communication link between two ICP nodes.  For
;;; each end of the connection, there is an `ICP socket'.  Since communication
;;; through an ICP connection is bidirectional, two ports (an `ICP input port'
;;; and an `ICP output port') are needed for each of the two connected sockets.


;;; ICP, as a protocol, is a sequence of ICP message groups.

;;; An `ICP message group' is a contiguous sequence of ICP messages that are
;;; (normally) to be processed as a whole, without interruption, by the ICP node
;;; to which they are sent.  An ICP message group consists of one or more ICP
;;; message series, the last of which is empty (contains no messages).

;;; An `ICP message block' is a contiguous sequence of ICP messages, within an
;;; ICP message group, that must be handled together in some special context.

;;; An `ICP message series' consists of a byte count followed by zero or more
;;; ICP messages, where the byte count is the number of ICP bytes in the message
;;; series, including the ICP byte that contains the byte count.  Note that an
;;; ICP message series can be no longer than maximum-icp-byte-unsigned-integer
;;; (see below).

;;; An `ICP message' consists of an ICP message type code followed by zero or
;;; more arguments.  An `ICP message type code' is an ICP byte, and each
;;; argument consists of one or more ICP bytes.

;;; An `ICP byte' is a 16-bit (unsigned) integer.





(defconser ICP int1)

;; ac & jh, 9/3/91.  Need the following two functions for the cleanup in
;; with-protected-listeners.

(defun copy-list-using-icp-conses-function (list?)
  (when list?
    (copy-list-using-icp-conses list?)))

(defun reclaim-icp-list-function (list?)
  (when list?
    (reclaim-icp-list list?)))

;; Moved here from telestubs.
(defun-void reclaim-icp-tree-with-text-strings (tree)
  (loop for tail = tree then next-tail
        while (consp tail)
        for car = (car tail)
        for next-tail = (cdr tail)
        do (reclaim-icp-tree-with-text-strings car)
           (reclaim-icp-cons tail)
        finally
          (when (text-string-p tail)
            (reclaim-text-string tail))))


;;; The macro `def-tree-reclaimer' defines a recursive function which reclaims a
;;; "proper" tree of conses using the given cons pool, strings, symbols, floats,
;;; and simple float arrays. A "proper" tree here is one where every CDR is a
;;; list.

(defmacro def-tree-reclaimer (function-name (tree) &key cons-pool)
  (or cons-pool (error "CONS-POOL is required."))
  (let ((fmt (format nil "Unknown lisp value in ~a: ~~s" function-name))
        (reclaim-xx-list (intern (format nil "RECLAIM-~A-LIST" cons-pool))))
    `(defun ,function-name (,tree)
       (cond ((null ,tree))
             ((symbolp ,tree))
             ((fixnump ,tree))
             ((text-string-p ,tree)
              (reclaim-text-string ,tree))
             ((managed-float-p ,tree)
              (reclaim-managed-float ,tree))
             ((managed-simple-float-array-p ,tree)
              (reclaim-managed-simple-float-array ,tree))
             ((consp ,tree)
              (loop for e in ,tree doing
                (,function-name e))
              (,reclaim-xx-list ,tree))
             (t
              (dwarn ,fmt ,tree))))))



;;;; ICP Errors




;;; When errors occur in handling ICP operations, the macro `icp-error' should
;;; be called with a tformat string and a set of formatted arguments to be
;;; displayed to the user.  This will be seen by the user as an internal error.
;;; This macro will shut down the current ICP context if possible, and will show
;;; the error message to the user in some way appropriate to the product
;;; currently running (i.e. an Internal Error window for G2, writing to stdout
;;; for GSI, etc.)

(defmacro icp-resumable-error (error-format-control-string &optional arg1 arg2 arg3)
  `(icp-error-internal 'resumable-error ,error-format-control-string ,arg1 ,arg2 ,arg3))

(defmacro icp-error (error-format-control-string &optional arg1 arg2 arg3)
  `(icp-error-internal 'error ,error-format-control-string ,arg1 ,arg2 ,arg3))

(defmacro icp-warning (error-format-control-string &optional arg1 arg2 arg3)
  `(icp-error-internal 'warning ,error-format-control-string ,arg1 ,arg2 ,arg3))





;;;; ICP tracing

;;; See the topic "External Interface to ICP Tracing" below for directions on
;;; using the ICP trace facility.


;; To do as of 3/4/93:

;; essential
;; ---------

;; nice
;; ----
;; gutter between levels of tracing
;; add printer for managed floats
;; better grouping of corresponding-object messages

#+ignore
(eval-when (:compile-toplevel :load-toplevel :execute)
  (pushnew :allow-icp-trace-for-gsi *features*)
)

;;; ICP Tracing Commonality

(defconstant blank-traced-icp-byte-column "|  ")



;;; If the macro `icp-optimizes-space-p' returns non-nil, an effort is made to
;;; emit compact code for ICP value and message functions, and ICP tracing will
;;; not work.

(defmacro icp-optimizes-space-p ()
  #+allow-icp-trace-for-gsi
  nil
  #-allow-icp-trace-for-gsi
  (gsi-eliminable-p))


(defvar trace-skip-data-service-i-am-alive-messages-p nil)
(defvar icp-trace-print-message-series-p t)

;;; Tracing ICP Reads

(def-global-property-name function-for-icp-value-reader?)

(defvar icp-read-trace-cutoff-level? nil)

(defmacro icp-read-trace-on-p ()
  `icp-read-trace-cutoff-level?)

(defmacro with-icp-read-tracing (tracep &body body)
  (declare (ignore tracep))
  #|
  `(let ((icp-read-trace-cutoff-level?
           (and ,tracep icp-read-trace-cutoff-level?)))
     ,@body)
  |#
  `(progn ,@body))

(defvar current-icp-read-trace-level 0)

(defun-simple instantaneous-icp-reader-byte-count ()
  (-f (+f number-of-icp-bytes-left-in-message-series
           number-of-icp-bytes-ready-to-read)))

(defmacro trace-read-icp-values-p ()
  ;(and icp-read-trace-cutoff-level?
        `(or (eq icp-read-trace-cutoff-level? t)
            (>=f icp-read-trace-cutoff-level? 4)))

(defmacro trace-read-icp-message-arguments-p ()
  `(and icp-read-trace-cutoff-level?
        (or (eq icp-read-trace-cutoff-level? t)
            (>=f icp-read-trace-cutoff-level? 3))))

(defmacro trace-read-icp-messages-p (data-service-i-am-alive-message-p)
  `(and ;icp-read-trace-cutoff-level?
        ,@(case data-service-i-am-alive-message-p
            ((t)   `((not trace-skip-data-service-i-am-alive-messages-p)))
            ((nil) `())
            (t     `((not (and trace-skip-data-service-i-am-alive-messages-p
                               ,data-service-i-am-alive-message-p)))))
        (or (eq icp-read-trace-cutoff-level? t)
            (>=f icp-read-trace-cutoff-level? 2))))

(defmacro trace-read-icp-message-series-p ()
  `(and icp-read-trace-cutoff-level?
        (or (eq icp-read-trace-cutoff-level? t)
            (>=f icp-read-trace-cutoff-level? 1))))

(defmacro emit-icp-read-trace-p ()
  ;(and icp-read-trace-cutoff-level? 
        `(or (eq icp-read-trace-cutoff-level? t)
            (>f icp-read-trace-cutoff-level? current-icp-read-trace-level)))

(defmacro convert-icp-byte-count-to-8-bit-bytes (icp-byte-count)
  `(*f ,icp-byte-count 2))

(defun-void emit-icp-read-trace
            (this-is-prologue-p
              byte-count-before? ;must be fixnum if (not this-is-prologue-p)
              byte-count-after?  ;must be fixnum if (not this-is-prologue-p)
              name-of-reader
              qualifier-string?
              trace-type
              report-icp-value-p
              icp-value?
              no-padding-p
              message-p)
  #-allow-icp-trace-for-gsi
  (declare (no-op-for-gsi))
  (when (and (emit-icp-read-trace-p)
             (or (not (eq trace-type 'message-series))
                 icp-trace-print-message-series-p)
             (if this-is-prologue-p
                 ;; only print msg name once if that's as deep as we go
                 (trace-read-icp-message-arguments-p)
                 t))
    (let ((tformat-fresh-line-is-newline-p nil)
          (padding
            (if no-padding-p
                ""
                (twith-output-to-text-string
                  (loop for index from 0 to current-icp-read-trace-level
                        do
                    (tformat "~a" blank-traced-icp-byte-column))))))
      ;; Make sure Chestnut handles these format directives!
      (if this-is-prologue-p
          (notify-user-in-parent-window "~&~areading ~a~@[ ~a~]~%"
            padding
            name-of-reader
            qualifier-string?)
          (let ((byte-delta
                  (+f (-f byte-count-after? byte-count-before?)
                      (if message-p 1 0))))
            (notify-user-in-parent-window "~&~a~a ~a~@[ ~a~]~:[~;: ~s~]~%"
              padding
              (convert-icp-byte-count-to-8-bit-bytes byte-delta)
              name-of-reader
              qualifier-string?
              report-icp-value-p
              icp-value?)))
      (unless no-padding-p
        (reclaim-text-string padding)))))

(defmacro tracing-icp-reads
          ((name-of-reader qualifier-string? trace-type tracep
            &optional report-read-result-p message-p)
           &body body)
  (if (icp-optimizes-space-p)
      `(progn ,@body)
      `(if icp-read-trace-cutoff-level? ;added in Gensym-343
      ,(avoiding-variable-capture (tracep qualifier-string?
                                         &aux result-of-read
                                         byte-count-before)
        `(with-icp-read-tracing ,tracep
           (let* ((,byte-count-before
                     (when ,tracep
                       (emit-icp-read-trace
                         t   ;this-is-prologue-p
                         nil ;byte-count-before?
                         nil ;byte-count-after?
                         ',name-of-reader
                         ,qualifier-string?
                         ',trace-type
                         nil ;report-icp-value-p
                         nil ;icp-value?
                         nil ;no-padding-p
                         ,message-p)
                       (instantaneous-icp-reader-byte-count)))
                  (current-icp-read-trace-level
                    (1+f current-icp-read-trace-level))
                  (,result-of-read
                     (progn ,@body)))
             (when ,tracep
               (emit-icp-read-trace
                 nil ;this-is-prologue-p
                 ,byte-count-before
                 (instantaneous-icp-reader-byte-count)
                 ',name-of-reader
                 ,qualifier-string?
                 ',trace-type
                 ,report-read-result-p
                 ,result-of-read
                 nil ;no-padding-p
                 ,message-p))
             ,result-of-read)))
           
           (progn ,@body) ;added in Gensym-343
           
           )))




;;; Tracing ICP Writes

(def-global-property-name function-for-icp-value-writer?)

(defvar icp-write-trace-cutoff-level? nil)

(defmacro icp-write-trace-on-p ()
  `icp-write-trace-cutoff-level?)

(defmacro with-icp-write-tracing (tracep &body body)
  (declare (ignore tracep))
  #|
  `(let ((icp-write-trace-cutoff-level?
           (and ,tracep icp-write-trace-cutoff-level?)))
     ,@body)
  |#
  `(progn ,@body))

(defvar current-icp-write-trace-level 0)

(defun-simple instantaneous-icp-writer-byte-count ()
  (-f number-of-icp-bytes-for-message-series
      number-of-icp-bytes-to-fill-buffer))

(defmacro trace-write-icp-values-p ()
  ;`(and icp-write-trace-cutoff-level?
        `(or (eq icp-write-trace-cutoff-level? t)
            (>=f icp-write-trace-cutoff-level? 4)))

(defmacro trace-write-icp-message-arguments-p ()
  ;`(and icp-write-trace-cutoff-level?
        `(or (eq icp-write-trace-cutoff-level? t)
            (>=f icp-write-trace-cutoff-level? 3)))

(defmacro trace-write-icp-messages-p (data-service-i-am-alive-message-p)
  `(and ;icp-write-trace-cutoff-level?
        ,@(case data-service-i-am-alive-message-p
            ((t)   `((not trace-skip-data-service-i-am-alive-messages-p)))
            ((nil) `())
            (t     `((not (and trace-skip-data-service-i-am-alive-messages-p
                               ,data-service-i-am-alive-message-p)))))
        (or (eq icp-write-trace-cutoff-level? t)
            (>=f icp-write-trace-cutoff-level? 2))))

(defmacro trace-write-icp-messages-and-no-deeper-p ()
  `(and icp-write-trace-cutoff-level?
        (fixnump icp-write-trace-cutoff-level?)
        (<=f icp-write-trace-cutoff-level? 2)))

(defmacro trace-write-icp-message-series-p ()
  `(and icp-write-trace-cutoff-level?
        (or (eq icp-write-trace-cutoff-level? t)
            (>=f icp-write-trace-cutoff-level? 1))))

(defmacro emit-icp-write-trace-p ()
  ;`(and icp-write-trace-cutoff-level?
        `(or (eq icp-write-trace-cutoff-level? t)
            (>f icp-write-trace-cutoff-level? current-icp-write-trace-level)))



(defun-void emit-icp-write-trace
            (this-is-prologue-p
              byte-count-before? ;must be fixnum if (not this-is-prologue-p)
              byte-count-after?  ;must be fixnum if (not this-is-prologue-p)
              name-of-writer
              qualifier-string?
              trace-type
              report-icp-value-p
              icp-value?
              no-padding-p
              message-p)
  #-allow-icp-trace-for-gsi
  (declare (no-op-for-gsi))
  (when (and (emit-icp-write-trace-p)
             (or (not (eq trace-type 'message-series))
                 icp-trace-print-message-series-p)
             (if this-is-prologue-p
                 ;only print msg name once if that's as deep as we go
                 (trace-write-icp-message-arguments-p)
                 t))
    (let ((tformat-fresh-line-is-newline-p nil)
          (padding
            (if no-padding-p
                ""
                (twith-output-to-text-string
                  (loop for index from 0 to current-icp-write-trace-level
                        do
                    (tformat "~a" blank-traced-icp-byte-column))))))
      ;; Make sure Chestnut handles these format directives!
      (if this-is-prologue-p
          (notify-user-in-parent-window "~&~awriting ~a~@[ ~a~]~:[~;: ~s~]~%"
            padding
            name-of-writer
            qualifier-string?
            report-icp-value-p
            icp-value?)
          (let ((byte-delta
                  (+f (-f byte-count-after? byte-count-before?)
                      (if message-p 1 0))))
            (notify-user-in-parent-window "~&~a~a ~a~@[ ~a~]~:[~;: ~s~]~%"
              padding
              (convert-icp-byte-count-to-8-bit-bytes byte-delta)
              name-of-writer
              qualifier-string?
              report-icp-value-p
              icp-value?)))
      (unless no-padding-p
        (reclaim-text-string padding)))))

(defmacro tracing-icp-writes
          ((name-of-writer qualifier-string? trace-type tracep
            &optional message-p (icp-value? nil icp-value-supplied-p))
           &body body)
  (unless icp-value? (setq icp-value-supplied-p nil))
  (if (icp-optimizes-space-p)
      `(progn ,@body)
      `(if icp-write-trace-cutoff-level? ;added in Gensym-343
      ,(avoiding-variable-capture (tracep icp-value?
                                         &aux byte-count-before result-of-write)
        `(with-icp-write-tracing ,tracep
           (let* ((,byte-count-before
                     (when ,tracep
                       (emit-icp-write-trace
                         t   ;this-is-prologue-p
                         nil ;byte-count-before?
                         nil ;byte-count-after?
                         ',name-of-writer
                         ,qualifier-string?
                         ',trace-type
                         ,icp-value-supplied-p
                         ,icp-value?
                         nil ;no-padding-p
                         ,message-p)
                       (instantaneous-icp-writer-byte-count)))
                  (current-icp-write-trace-level
                    (1+f current-icp-write-trace-level))
                  (,result-of-write
                    (progn ,@body)))
             (when ,tracep
               (emit-icp-write-trace
                 nil ;this-is-prologue-p
                 ,byte-count-before
                 (instantaneous-icp-writer-byte-count) ;byte-count-after
                 ',name-of-writer
                 ,qualifier-string?
                 ',trace-type
                 nil ;icp-value-supplied-p
                 nil ;icp-value may have been reclaimed after the write, so always nil
                 nil ;no-padding-p
                 ,message-p))
             ,result-of-write)))
           
           (progn ,@body) ;added in Gensym-343
           
           )))


;;;; External Interface to ICP Tracing

;;; The external interface to ICP tracing is the function icp-trace, constructed
;;; along the lines of the Common Lisp trace faciliity.

;;; To make things easier when debugging translated C code, icp-trace always
;;; takes two arguments.  The first argument to icp-trace will affect the level
;;; of ICP read tracing; the second argument to icp-trace will affect the level
;;; of write tracing.  Each argument must be either a fixnum representing a
;;; trace level, nil meaning that no tracing will occur, t meaning that all
;;; levels will be traced, the symbol SAME to indicate that the current trace
;;; level should not be changed, or the symbol whose printname is "?" to print a
;;; description of the trace levels of both ICP writing and ICP reading.  If an
;;; argument is not one of these values, a warning message will be printed and
;;; the trace level will not change.

;;; trace level                 meaning
;;; -----------                 --------
;;;                       nil : no tracing
;;;                         0 : code takes trace branches; no messages printed
;;;                         1 : message series
;;;                         2 : messages
;;;                         3 : message argument names
;;;                         4 : top-level message values
;;; 5 to most-positive-fixnum : embedded message values
;;;                         t : infinite depth
;;;                         ? : report current trace levels only

;;; Each line of ICP tracing output has two formats, prelude and postlude.  The
;;; first item in a prelude line is the name of the ICP event.  The first item
;;; in a postlude tracing line is a byte count followed by the event name.
;;; Typically, an ICP event is traced by printing a prelude, indented
;;; sub-events, then a postlude.  The one exception is that ICP messages are not
;;; printed twice if the tracing level is set no deeper.  This prevents
;;; confusion between two actual messages being processed and a single message
;;; causing two tracing lines.

;; jh, 3/4/93.  For the record, the tracing of ICP message series is
;; special-cased in the functions start-writing-icp-message,
;; advance-and-read-icp-byte-if-any, and end-icp-message-series-if-any.  This is
;; because we don't have a convenient abstraction for message series, as we do
;; for messages, value readers, and value writers.

(defmacro defvar-for-icp-trace (name &rest stuff)
  `(#+allow-icp-trace-for-gsi
      defvar
      #-allow-icp-trace-for-gsi
      defvar-excluding-gsi
      ,name ,@stuff))

(defvar-for-icp-trace icp-trace-level-descriptions
  '(
    (nil . "No tracing")
    (0   . "Code will take tracing branches, but will not print trace messages")
    (1   . "Message series will be traced")
    (2   . "Messages will be traced")
    (3   . "Message argument names will be traced")
    (4   . "Top-level message values will be traced")
    (etc . "Embedded message values will be traced")
    (t   . "All levels will be traced")
    ))

(defun describe-icp-trace-level (user-level read-or-write-string)
  #-allow-icp-trace-for-gsi
  (declare (eliminate-for-gsi))
  (case user-level
    ((nil t 0)
     (format t "~&ICP ~as:~%" read-or-write-string)
     (format t "~&  ~a.~%"
             (cdr (assoc user-level
                         icp-trace-level-descriptions))))
    (otherwise
     (format t "~&ICP ~a tracing at level ~s:~%"
             read-or-write-string
             user-level)
     (loop for (code . description) in icp-trace-level-descriptions
           with max-known-level = 0
           do
       (when (and (numberp code)
                  (pluspf code))
         (setq max-known-level (maxf max-known-level code))
         (when (>=f user-level code)
           (format t "~&  ~a.~%" description)))
           finally
             (when (>f user-level max-known-level)
               (format t "~&  ~a.~%"
                       (cdr (assq 'etc icp-trace-level-descriptions))))))))

(defun validate-icp-trace-cutoff-value
       (cutoff-value read-or-write-string previous-level)
  #-allow-icp-trace-for-gsi
  (declare (eliminate-for-gsi))
  (if (or (fixnump cutoff-value)
          (memq cutoff-value '(t nil)))
      t
      (format t "~&ICP-TRACE: expected a fixnum, T, or NIL -- got ~s.~%~
                  ICP ~a tracing level remains ~s."
              cutoff-value
              read-or-write-string
              previous-level)))

(defun-funcallable icp-trace (read-cutoff write-cutoff)
  #-allow-icp-trace-for-gsi
  (declare (eliminate-for-gsi))
  (let ((bad-settings nil))
    (case read-cutoff
      (same)
      (? (describe-icp-trace-level icp-read-trace-cutoff-level? "read"))
      (otherwise
       (if (validate-icp-trace-cutoff-value
             read-cutoff
             "read"
             icp-read-trace-cutoff-level?)
           (setq icp-read-trace-cutoff-level? read-cutoff)
           ;; jh, 3/30/95.  Using a symbol with a different print name than that
           ;; of lisp:read can save 60k in GSI!
           ;; jh, 4/4/95.  Still useful to know, even though this whole function
           ;; is no longer in released GSI.
           (icp-push '|read| bad-settings))))
    (case write-cutoff
      (same)
      (? (describe-icp-trace-level icp-write-trace-cutoff-level? "write"))
      (otherwise
       (if (validate-icp-trace-cutoff-value
             write-cutoff
             "write"
             icp-write-trace-cutoff-level?)
           (setq icp-write-trace-cutoff-level? write-cutoff)
           (icp-push 'write bad-settings))))
    (when (=f (length bad-settings) 1)
      (case (car bad-settings)
        (|read|
         (if (memq write-cutoff '(same ?))
             (format t "~&Write tracing unchanged at ~s.~%"
                     icp-write-trace-cutoff-level?)
             (format t "~&Write tracing successfully changed to ~s.~%"
                     icp-write-trace-cutoff-level?)))
        (write
         (if (memq read-cutoff '(same ?))
             (format t "~&Read tracing unchanged at ~s.~%"
                     icp-read-trace-cutoff-level?)
             (format t "~&Read tracing successfully changed to ~s.~%"
                     icp-read-trace-cutoff-level?)))))
    (reclaim-icp-list bad-settings)))



(defun icp-untrace ()
  #-allow-icp-trace-for-gsi
  (declare (eliminate-for-gsi))
  (setq icp-read-trace-cutoff-level? nil)
  (setq icp-write-trace-cutoff-level? nil))

;added in Gensym-343

(defun set-icp-tracing-level-from-command-line ()
  #-allow-icp-trace-for-gsi
  (declare (eliminate-for-gsi))
  (let ((trace-level (getf command-line-arguments 'icp-log-intensity)))
 ;check if option value is valid 
 (when trace-level
     (if (=f trace-level 7)
         
       (notify-user-if-possible 
        "Specified icp-log-intensity option value may be an integer from 0 to 6:~%~%
        0: Code will take tracing branches, but will not print trace messages~%
        1: Message series will be traced~%
        2: Messages will be traced~%
        3: Message argument names will be traced~%
        4: Top-level message values will be traced~%
        5: Embedded message values will be traced~%
        6: All levels will be traced~%~%
        Assuming no tracing~%")    
         
         (if (=f trace-level 6)
             (icp-trace t t)
             (if (=f trace-level 5)
                 (icp-trace t t)
                 (icp-trace trace-level trace-level)
             )
          )
      )
)))  

;end of changes

;;;; ICP Values


;;; An `ICP value' is a value that can be passed explicitly as an icp message
;;; argument, without referring to structures in the memory of another icp node.
;;; Every icp value must be of a particular `ICP value type', for which either
;;; an equivalent icp value type or a reader and/or writer are defined (see
;;; below).  A reclaimer may be declared for an icp value type by setting its
;;; icp-value-reclaimer property to an appropriate function or macro.

;;; Nothing more is necessary to declare an ICP value type than to define a
;;; writer and a reader for it.


;;; Maximum-icp-byte-unsigned-integer ...

(eval-when (:compile-toplevel :load-toplevel :execute)
(defmacro maximum-icp-byte-unsigned-integer ()
  63000))



;;; The value of special variable icp-nil is used to represent nil as an icp
;;; value returned by an icp value reader.

; (defvar icp-nil (list nil))





(defparameter-for-macro resumable-icp-value-types
  '(byte byte-macro large-integer array-of-unsigned-integers-given-length
    integer list-of-unsigned-integers fixnum double-float color-map ; macros
    boolean corresponding-object-index unsigned-integer unsigned-integer?
    character wide-string text-string gensym-string filtered-text-string
    symbol-as-value-type list-element list improper-list-element improper-list
    icp-tree interned-list-as-value-type resumable-gsi-values long
    number-of-icp-bytes-of-fill unsigned-integer-or-nil float managed-double-float
    sexp-element s-expression-for-remote-eval gsi-timestamp returned-gsi-sensor
    returned-gsi-interface gsi-value-vector gsi-ds-update-interval
    tiling-pattern-rows-with-color-values byte-vector array-of-unsigned-integers
    array-of-unsigned-integers? evaluation-sequence evaluation-structure
    remote-value-1 remote-value gsi-permanent-remote-value item-reference item-copy item-handle
    item-new-copy item list-of-foreign-function-registrations?
    foreign-function-argument foreign-function-value returned-external-simulation-object
    returned-g2ds-variable g2ds-float g2ds-list g2ds-dotted-list g2ds-data-value
    g2ds-expression nupec-synchronize-datum nupec-designation nupec-history-block
    list-of-attributes list-of-lists-of-attributes list-of-included-return-attributes
    list-of-excluded-return-attributes list-of-included-return-system-attributes
    possibly-interned-symbol g2ds-evaluation-sequence g2ds-evaluation-structure))

(defparameter-for-macro non-resumable-icp-value-types
  '(rpc-value-or-object rpc-argument-list
    evaluation-truth-value history-timestamp evaluation-quantity-or-nil
    resumable-object-portion resumable-node-indices
    list-of-foreign-function-registrations? index-space
    compressed-image-data-chunk image-data-chunk-byte-vector))

(defparameter-for-macro non-resumable-icp-object-types
  '(resumable-object gsi-instance resumable-instance-node))

(defparameter-for-macro non-resumable-icp-message-types
  '(start-icp-task resume-icp-task abort-icp-task
    define-temporary-index-space release-temporary-index-space))



(defparameter data-service-i-am-alive-messages
  '(i-am-alive message-group-id g2ds-send-data-values-if-any g2ds-server-status))


;;; Declaration:     def-icp-value-type-equivalence
;;;                   (new-icp-value-type old-equivalent-icp-value-type)
;;; Type:             Lisp macro.
;;; Purpose:             Declare an equivalence between an existing ICP value type and
;;;                  a new type.
;;; Arguments:             new-icp-value-type and old-equivalent-icp-value-type are
;;;                  unevaluated symbols.
;;; Return behavior: No useful value.
;;; Users:           ICP internal value type corresponding-icp-object-index (INT3),
;;;                  GSI (module GSI-COMMON), Telewindows and G2 printing (WINDOWS1,
;;;                  TELESTUBS).
;;; Prerequisites:   None.
;;; Side effects:    After a def-icp-value-type-equivalence form is evaluated at
;;;                  compile time, an ICP message handler which receives arguments
;;;                      of type new-icp-value-type will invoke the ICP value reader
;;;                  for old-equivalent-icp-value-type to read values of the new
;;;                      type.
;;; Non-local exits: None.
;;; Memory impact:   Creates a new entry on a symbol plist the first time it
;;;                  is called with a new value of new-icp-value-type.  This
;;;                  macro is typically called only once per type at run time.
;;; Notes:           It may not be necessary to call this at run time at all.

;;; Def-icp-value-type-equivalence defines icp-value-type as being equivalent,
;;; in the way values are represented, to equivalent-icp-value-type.  (Note
;;; that, though the relationship is one of equivalence, the defined type must
;;; be reducible through a loop-free series of equivalence definitions to an icp
;;; value type for which a reader and/or writer are defined.)

(eval-when (:compile-toplevel :load-toplevel :execute)
(def-global-property-name equivalent-icp-value-type))

(defmacro def-icp-value-type-equivalence (icp-value-type equivalent-icp-value-type)
  `(eval-when (:compile-toplevel :load-toplevel :execute)
     (setf (equivalent-icp-value-type ',icp-value-type) ',equivalent-icp-value-type)))



;;; Declaration:     def-icp-value-reader
;;;                   (icp-value-type &body icp-value-reader-body)
;;; Type:             Lisp macro.
;;; Purpose:             Define an icp-value-reader function.
;;; Arguments:             icp-value-type is the unevaluated type name, a symbol.
;;;                  icp-value-reader-body is the body of the icp-value-reader
;;;                  function.  The progn should read a value of type
;;;                  icp-value-type from ICP and return it.
;;; Return behavior: No useful value.
;;; Users:           Public ICP value types (INT3), GSI (module GSI-COMMON),
;;;                  Telewindows and G2 printing (WINDOWS2, TELESTUBS), G2 remote
;;;                  procedure calls (G2-RPC1 and G2-RPC2), G2 foreign functions
;;;                  (G2-FOREIGN), GSPAN, G2-to-G2 communication (G2DS, G2DS-NUPEC).
;;; Prerequisites:   None.
;;; Side effects:    Defines at compile time a function named
;;;                  READ-ICP-<icp-value-type> with body icp-value-reader-body.
;;;                  For details of the behavior of this function, see the doc for
;;;                  READ-ICP-<icp-value-type> below.
;;; Non-local exits: None.
;;; Memory impact:   Compile-time consing only.
;;; Notes:           Note the distinction between ICP values and ICP objects.
;;;                  ICP values cannot have corresponding objects on the other end
;;;                  of an ICP connection.  The entire value must be sent anew
;;;                  each time it is needed.

;;; Def-icp-value-reader defines an `ICP value reader' for icp-value-type, the
;;; name of which is constructed by prefixing icp-value-type with "READ-ICP-",
;;; and the body of which is icp-value-reader-body.
;;; Def-icp-value-reader-substitution-macro does the same thing, except that it
;;; defines a substitution macro (see def-substitution-macro) rather than a
;;; function.

;;; Declaration:     READ-ICP-<icp-value-type> () => icp-value
;;; Type:            Lisp function or G2 substitution macro.
;;; Purpose:         Read a value from ICP.
;;; Arguments:       None.
;;; Return behavior: Return the value read from ICP.
;;; Users:           See def-icp-value-reader and
;;;                  def-icp-value-reader-substitution-macro.
;;; Prerequisites:   Defined by a macro call to def-icp-value-reader or
;;;                  def-icp-value-reader-substitution-macro (see above).  The body
;;;                  of this function is given by the icp-value-reader-body arg to
;;;                  these macros.
;;; Side effects:    Depends on icp-value-reader-body.
;;; Non-local exits: icp-value-reader-body should not exit non-locally.
;;; Memory impact:   Depends on icp-value-reader-body.

;;; An icp value reader reads and returns the next argument, if any, in the icp
;;; message currently being read, assuming it to be of type icp-value-type.  (If
;;; and when optional arguments are implemented, nil would be returned to
;;; indicate the absence of an argument, and the value of special variable
;;; icp-nil to represent the value nil.)

;; jh, 3/3/93.  Each ICP value reader now has an extra null test due to
;; ICP tracing.

(defun-for-macro extract-non-ignore-declarations-and-doc (doc-and-decl-forms)
  (loop for doc-or-decl in doc-and-decl-forms
        when
          (or (text-string-p doc-or-decl)
              (and (consp doc-or-decl)
                   (not (eq (caadr doc-or-decl)
                            'ignore))))
          collect doc-or-decl))


;; jh, 3/11/93.  Added the icp-value-reader-function property.  This
;; is a property of the icp-value-type symbol and is visible at compile time.
;; This property stores the name of a functional version of the ICP value reader
;; for icp-value-type and is used to stop the macroexpansion of tracable ICP
;; message handlers at a reasonable level.

(def-global-property-name icp-value-reader-function)

(defun-for-macro get-icp-value-reader-name
                 (icp-value-type &optional functional-version-p)
  (if functional-version-p
      (intern (format nil "READ-ICP-~A-USING-FUNCTION" icp-value-type))
      (intern (format nil "READ-ICP-~A" icp-value-type))))

(defmacro def-icp-value-reader
    (icp-value-type &body icp-value-reader-body)
  (multiple-value-bind (doc-and-decl-forms body-after-doc-and-decl?)
      (split-defun-body icp-value-reader-body)
    (let* ((non-resumable-p (memq icp-value-type non-resumable-icp-value-types))
           (defun (if non-resumable-p
                      'defun
                      'defun-simple-resumable-icp-function))
           (reader-name (get-icp-value-reader-name icp-value-type))
           (read-forms
             `(,@doc-and-decl-forms
                 ,(if body-after-doc-and-decl?
                      `(tracing-icp-reads (,icp-value-type "[value]" value
                                           (trace-read-icp-values-p) t)
                         ,@body-after-doc-and-decl?)
                      `(error "No ICP value reader for ~s" ',icp-value-type)))))
      `(progn
         ,@(unless (eval-feature :no-macros)
             `((eval-when (:compile-toplevel :load-toplevel :execute)
                 (add-icp-value-reader ',icp-value-type ',reader-name))))
         (,defun ,reader-name ()
           ,@read-forms)
         ,(unless (eval-feature :chestnut-trans)
            `',icp-value-type))))) ;if a toplevel progn returns a symbol, Chestnut interns it!


#-no-macros
(eval-when (:compile-toplevel :load-toplevel :execute)
(defun add-icp-value-reader (icp-value-type reader-name)
  (setf (get icp-value-type 'icp-value-reader-function) reader-name))
)


;;; Declaration:     def-icp-value-reader-substitution-macro
;;;                   (icp-value-type &body icp-value-reader-body)
;;; Type:             Lisp macro.
;;; Purpose:             Define an icp-value-reader substitution macro.
;;; Arguments:             icp-value-type is the unevaluated type name, a symbol.
;;;                  icp-value-reader-body is the body of the icp-value-reader
;;;                  substitution macro.  The progn should read a value of type
;;;                  icp-value-type from ICP and return it.
;;; Return behavior: No useful value.
;;; Users:           Public ICP value types (INT3), Telewindows and G2 printing
;;;                  (WINDOWS1).
;;; Prerequisites:   None.
;;; Side effects:    Defines at compile time a substitution macro named
;;;                  READ-ICP-<icp-value-type> with body icp-value-reader-body.
;;;                  For details of the behavior of this substitution macro, see
;;;                  the doc for READ-ICP-<icp-value-type> below.
;;; Non-local exits: None.
;;; Memory impact:   Compile-time consing only.
;;; Notes:           See note under def-icp-value-reader.

(defmacro def-icp-value-reader-substitution-macro
          (icp-value-type &body icp-value-reader-body)
  (if (and (icp-optimizes-space-p) (not (eq icp-value-type 'double-float)))
      `(def-icp-value-reader ,icp-value-type ,@icp-value-reader-body)
      (multiple-value-bind (doc-and-decl-forms body-after-doc-and-decl?)
          (split-defun-body icp-value-reader-body)
        (let* ((non-resumable-p (memq icp-value-type non-resumable-icp-value-types))
               (defun (if non-resumable-p
                          'defun
                          'defun-simple-resumable-icp-function))
               (reader-name (get-icp-value-reader-name icp-value-type))
               (reader-function-name (get-icp-value-reader-name icp-value-type t))
               (splicable-reader-body
                 `(,@doc-and-decl-forms
                     ,(if body-after-doc-and-decl?
                          `(tracing-icp-reads (,icp-value-type "[value]" value
                                               (trace-read-icp-values-p) t)
                             ,@body-after-doc-and-decl?)
                          `(error "No ICP value reader for ~s" ',icp-value-type)))))
          `(progn
             ,@(unless (eval-feature :no-macros)
                 `((eval-when (:compile-toplevel :load-toplevel :execute)
                     (add-icp-value-reader ',icp-value-type ',reader-function-name))))
             (,defun ,reader-function-name ()
               ,@splicable-reader-body)
             (def-substitution-macro ,reader-name ()
               ,@splicable-reader-body)
             ,(unless (eval-feature :chestnut-trans)
                `',icp-value-type)))))) ;if a toplevel progn returns a symbol, Chestnut interns it!







;;; Declaration:     def-icp-value-writer
;;;                   (icp-value-type &body icp-value-writer-body)
;;; Type:             Lisp macro.
;;; Purpose:             Define an icp-value-writer function.
;;; Arguments:             icp-value-type is the unevaluated type name, a symbol.
;;;                  icp-value-writer-body is the body of the icp-value-writer
;;;                  function.  The progn should write a value of type
;;;                  icp-value-type over ICP.  Within the body of the progn, the
;;;                  variable named <icp-value-type> is bound to the value being
;;;                  written.
;;; Return behavior: No useful value.
;;; Users:           Public ICP value types (INT3), GSI (module GSI-COMMON),
;;;                  Telewindows and G2 printing (WINDOWS2, TELESTUBS), G2 remote
;;;                  procedure calls (G2-RPC1 and G2-RPC2), G2 foreign functions
;;;                  (G2-FOREIGN), GSPAN, G2-to-G2 communication (G2DS, G2DS-NUPEC).
;;; Prerequisites:   None.
;;; Side effects:    Defines at compile time a function named
;;;                  WRITE-ICP-<icp-value-type> with body icp-value-writer-body.
;;;                  For details of the behavior of this function, see the doc for
;;;                  WRITE-ICP-<icp-value-type> below.
;;; Non-local exits: None.
;;; Memory impact:   Compile-time consing only.
;;; Notes:           See note under def-icp-value-reader.

;;; Def-icp-value-writer defines an `ICP value writer' for icp-value-type, the
;;; name of which is constructed by prefixing icp-value-type with "WRITE-ICP-",
;;; and the body of which is icp-value-writer-body.
;;; Def-icp-value-writer-substitution-macro does the same thing, except that it
;;; defines a substitution macro (see def-substitution-macro) rather than a
;;; function.

;;; Declaration:     WRITE-ICP-<icp-value-type> (icp-value)
;;; Type:            Lisp function or G2 substitution macro.
;;; Purpose:         Write a value across ICP.
;;; Arguments:       The value to write across ICP.
;;; Return behavior: No useful value.
;;; Users:           See def-icp-value-writer and
;;;                  def-icp-value-writer-substitution-macro.
;;; Prerequisites:   Defined by a macro call to def-icp-value-writer or
;;;                  def-icp-value-writer-substitution-macro (see above).  The body
;;;                  of this function is given by the icp-value-writer-body arg to
;;;                  def-icp-value-writer or
;;;                  def-icp-value-writer-substitution-macro.
;;; Side effects:    Depends on icp-value-writer-body.
;;; Non-local exits: icp-value-writer-body should not exit non-locally.
;;; Memory impact:   Depends on icp-value-writer-body.

;;; An icp value writer takes a single argument, a value of type icp-value-type
;;; to be written as the next argument of the icp message currently being
;;; written.  It uses the icp value type to refer to this value.

;; jh, 3/3/93.  Each ICP value writer now has an extra null test due to
;; ICP tracing.

;; jh, 3/11/93.  Added the icp-value-write-function  property.  This
;; is a property of the icp-value-type symbol and is visible at compile time.
;; This property stores the name of a functional version of the ICP value writer
;; for icp-value-type and is used to stop the macroexpansion of tracable ICP
;; message senders at a reasonable level.

(def-global-property-name icp-value-write-function)

(defun-for-macro get-icp-value-writer-name
                 (icp-value-type &optional functional-version-p)
  (if functional-version-p
      (intern (format nil "WRITE-ICP-~A-USING-FUNCTION" icp-value-type))
      (intern (format nil "WRITE-ICP-~A" icp-value-type))))

(defmacro def-icp-value-writer (icp-value-type &body icp-value-writer-body)
  (multiple-value-bind (doc-and-decl-forms body-after-doc-and-decl?)
      (split-defun-body icp-value-writer-body)
    (let* ((non-resumable-p (memq icp-value-type non-resumable-icp-value-types))
           (defun (if non-resumable-p
                      'defun
                      'defun-simple-resumable-icp-function))
           (writer-name (get-icp-value-writer-name icp-value-type)))
      `(progn
         ,@(unless (eval-feature :no-macros)
             `((eval-when (:compile-toplevel :load-toplevel :execute)
                 (setf (get ',icp-value-type 'icp-value-write-function)
                       ',writer-name))))
         (,defun ,writer-name (,icp-value-type)
           ,@(if (null body-after-doc-and-decl?)
                 `(,@(extract-non-ignore-declarations-and-doc
                       doc-and-decl-forms)
                   (declare (ignore ,icp-value-type))
                   (error "No ICP value writer for ~s" ',icp-value-type))
                 `((tracing-icp-writes (,icp-value-type "[value]" value
                                        (trace-write-icp-values-p)
                                        nil ,icp-value-type)
                     ,@body-after-doc-and-decl?))))
         ,(unless (eval-feature :chestnut-trans)
            `',icp-value-type)))))





;;; Declaration:     def-icp-value-writer-substitution-macro
;;;                   (icp-value-type &body icp-value-writer-body)
;;; Type:             Lisp macro.
;;; Purpose:             Define an icp-value-writer substitution macro.
;;; Arguments:             icp-value-type is the unevaluated type name, a symbol.
;;;                  icp-value-writer-body is the body of the icp-value-writer
;;;                  substitution macro.  The progn should write a value of type
;;;                  icp-value-type over ICP.  Within the body of the progn, the
;;;                  variable named <icp-value-type> is bound to the value being
;;;                  written.
;;; Return behavior: No useful value.
;;; Users:             Telewindows and G2 printing (WINDOWS1).
;;; Prerequisites:   None.
;;; Side effects:    Defines at compile time a substitution macro named
;;;                  WRITE-ICP-<icp-value-type> with body icp-value-writer-body.
;;;                  For details of the behavior of this substitution macro, see
;;;                  the doc for WRITE-ICP-<icp-value-type> below.
;;; Non-local exits: None.
;;; Memory impact:   Compile-time consing only.
;;; Notes:           See note under def-icp-value-reader.

(defmacro def-icp-value-writer-substitution-macro
          (icp-value-type &body icp-value-writer-body)
  (if (and (icp-optimizes-space-p) (not (eq icp-value-type 'double-float)))
      `(def-icp-value-writer ,icp-value-type ,@icp-value-writer-body)
      (multiple-value-bind (doc-and-decl-forms body-after-doc-and-decl?)
          (split-defun-body icp-value-writer-body)
        (let* ((non-resumable-p (memq icp-value-type non-resumable-icp-value-types))
               (defun (if non-resumable-p
                          'defun
                          'defun-simple-resumable-icp-function))
               (writer-name (get-icp-value-writer-name icp-value-type))
               (writer-function-name (get-icp-value-writer-name icp-value-type t))
               (splicable-body-of-writer
                 (if body-after-doc-and-decl?
                     `(,@doc-and-decl-forms
                         (tracing-icp-writes (,icp-value-type "[value]" value
                                                              (trace-write-icp-values-p)
                                                              nil ,icp-value-type)
                           ,@body-after-doc-and-decl?))
                     `(,@(extract-non-ignore-declarations-and-doc
                           doc-and-decl-forms)
                         (declare (ignore ,icp-value-type))
                         (error "No ICP value writer for ~s" ',icp-value-type)))))
          `(progn
             ,@(unless (eval-feature :no-macros)
                 `((eval-when (:compile-toplevel :load-toplevel :execute)
                     (setf (get ',icp-value-type 'icp-value-write-function)
                           ',writer-function-name))))
             (,defun ,writer-function-name (,icp-value-type)
               ,@splicable-body-of-writer)
             (def-substitution-macro ,writer-name (,icp-value-type)
               ,@splicable-body-of-writer)
             ,(unless (eval-feature :chestnut-trans)
                `',icp-value-type))))))






;;; Declaration:     icp-value-reclaimer
;;; Type:             G2 global property.
;;; Purpose:         Allow automatic reclaiming of values when an ICP message is
;;;                  handled.
;;; Arguments:       N/A.
;;; Return behavior: N/A.
;;; Users:             Public ICP value types text-string and gensym-list (INT3).
;;; Prerequisites:   None.
;;; Side effects:    When this property is present on a symbol that names an ICP
;;;                  value type, def-icp-message-type will arrange that its message
;;;                  handler reclaim any value of this type.  It will do so by
;;;                  having the message handler funcall the value of this property.
;;;                  This value should name a funcallable function which takes a
;;;                  single argument, the ICP value to reclaim.
;;; Non-local exits: N/A.
;;; Memory impact:   One-shot consing at launch time only.

(eval-when (:compile-toplevel :load-toplevel :execute)                        ; def. needed below
(def-global-property-name icp-value-reclaimer)
)










;;;; ICP Objects



;;; An `ICP object' (or `original ICP object') is an object that may need to be
;;; represented by permanent (or semi-permanent) structures at more than one icp
;;; node.  When an icp object has a `corresponding object' (or `surrogate
;;; object') at some other icp node, that corresponding object is represented by
;;; an `ICP object index' in some (named) `ICP object index space'.

;;; Anything that can be an icp object must have a `corresponding icp object
;;; map' that is accessible from the object via an access form.  A corresponding
;;; icp object map is a plist that (at the very least) maps icp output ports
;;; into icp object indices for corresponding objects.  When an icp node becomes
;;; no longer useful, because it has had its memory of corresponding icp objects
;;; reset, mappings for corresponding objects in that node should be removed,
;;; and the conses recycled!



(eval-when (:compile-toplevel :load-toplevel :execute)

(def-global-property-name name-of-corresponding-icp-object-index-space)

(def-global-property-name access-form-for-corresponding-icp-object-map)

(def-global-property-name reclaimer-for-icp-port-entry)

(def-global-property-name reclaimer-for-icp-object)

(def-global-property-name shutdown-reclaimer-for-icp-object))

(def-system-variable delete-corresponding-object? INT1 t)
(def-system-variable deregister-corresponding-object? INT1 nil)



;;; Declaration:     def-icp-object-type
;;;                   (icp-object-type
;;;                     (name-of-corresponding-icp-object-index-space
;;;                      access-form-for-corresponding-icp-object-map
;;;                      &optional icp-object-reclaimer?
;;;                                icp-object-shutdown-reclaimer?)
;;;                    &body corresponding-icp-object-maker-body)
;;; Type:             Lisp macro.
;;; Purpose:             Set up machinery to send, receive, and reclaim ICP objects.
;;; Arguments:             > icp-object-type is an unevaluated symbol naming the
;;;                    ICP object type.
;;;                  > name-of-corresponding-icp-object-index-space
;;;                    is an unevaluated symbol naming the index space on the
;;;                    remote side which maps between an ICP object and its index.
;;;                    This index space is stored on a plist maintained in the
;;;                    corresponding-icp-object-index-space-plist of the ICP input
;;;                    port on the remote side. The first key in any such plist is
;;;                    the symbol standard-icp-object-index-space, and this symbol
;;;                    is the typical value for this argument.
;;;                  > access-form-for-corresponding-icp-object-map is the form the
;;;                    local side uses to obtain the ICP object map, and thereby the
;;;                    index of the ICP object on the remote side.  In this form,
;;;                    the variable named <icp-object-type> is bound to the ICP
;;;                    object being accessed.
;;;                  > icp-object-reclaimer?  is an unevaluated symbol naming a
;;;                    funcallable function which reclaims the ICP object on the
;;;                    remote side.  (This function need not reclaim the ICP object
;;;                    map for the object because that is empty on the remote side.)
;;;                    It takes a single argument, the object to be reclaimed, and
;;;                    is called when RECLAIM-ICP-OBJECT-MAP-FOR-<icp-object-type>
;;;                    (documented below) sends an ICP message to delete a remote
;;;                    ICP object.  If icp-object-reclaimer?  is nil the client of
;;;                    def-icp-object-type must make other arrangements to
;;;                    reclaim remote ICP objects upon deletion.
;;;                  > icp-object-shutdown-reclaimer?  is an unevaluated symbol
;;;                    naming a funcallable function which reclaims the ICP object
;;;                    on the local side when the ICP connection shuts down.  This
;;;                    function takes two arguments: the ICP object and the ICP
;;;                    port.  This function needs to reclaim the ICP object map for
;;;                    the object as well.  If icp-object-shutdown-reclaimer?  is
;;;                    nil, the client of def-icp-object-type must make other
;;;                    arrangements to reclaim local ICP objects and their object
;;;                    maps upon shutdown.
;;;                  > corresponding-icp-object-maker-body is an implicit progn
;;;                    which becomes the body of
;;;                    MAKE-CORRESPONDING-ICP-<icp-object-type>, the function which
;;;                    creates and indexes the ICP object on the remote side.  In
;;;                    this body, the variable named <icp-object-type> is bound to
;;;                    the ICP object being created.  For further details, see the
;;;                    doc for this function type below.
;;; Return behavior: No useful value.
;;; Users:           Public ICP object type symbol (INT3), GSI (module GSI-COMMON),
;;;                  Telewindows and G2 printing (WINDOWS1, WINDOWS2, WINDOWS3,
;;;                  FONTS, TELESTUBS), G2 remote procedures (G2-RPC1 and G2-RPC2),
;;;                  GSPAN, G2-to-G2 communication (G2DS, G2DS-NUPEC).
;;; Prerequisites:   None.
;;; Side effects:    Defines the functions:
;;;                    MAKE-CORRESPONDING-ICP-<icp-object-type>
;;;                    GET-ICP-OBJECT-INDEX-FOR-<icp-object-type>
;;;                    SET-ICP-OBJECT-INDEX-FOR-<icp-object-type>
;;;                    GET-<icp-object-type>-FROM-ICP-PORT
;;;                    RECLAIM-ICP-OBJECT-MAP-FOR-<icp-object-type>
;;;                    RECLAIM-ICP-PORT-ENTRY-FOR-<icp-object-type>
;;;                    SET-ACCESS-FORM-FOR-<icp-object-type>
;;;                  Each of these function types is documented below.
;;;                  Sets some global properties for the symbol <icp-object-type>:
;;;                    name-of-corresponding-icp-index-space
;;;                    access-form-for-corresponding-icp-object-map
;;;                    reclaimer-for-icp-object
;;;                    shutdown-reclaimer-for-icp-object
;;;                    reclaimer-for-icp-port-entry
;;;                  These properties are internal to the def-icp-object
;;;                  implementation and should not be used outside of it.
;;; Non-local exits: None.
;;; Memory impact:   Compile-time consing, one-shot consing onto property lists at
;;;                  launch time.
;;; Notes:           (1) Note the distinction between ICP objects and ICP values.
;;;                  ICP objects have corresponding objects on the other end
;;;                  of an ICP connection.  The first time an object is written
;;;                  an index to it is cached.  Subsequent writes need only
;;;                  refer to this index.
;;;                  (2) access-form-for-corresponding-icp-object-map need not be
;;;                  present at run time.

;;; Declaration:     MAKE-CORRESPONDING-ICP-<icp-object-type> (icp-object)
;;; Type:             Lisp function.
;;; Purpose:             Create a remote ICP object which corresponds to a local one.
;;; Arguments:             An ICP object.
;;; Return behavior: The index for the ICP object in the ICP port that was current
;;;                  at the time this function was called.
;;; Users:             See def-icp-object-type.
;;; Prerequisites:   Defined by def-icp-object-type.
;;; Side effects:    On the local side, this function adds a new entry to the place
;;;                  named by the access-form-for-corresponding-icp-object-map arg
;;;                  to the def-icp-object form which defined this function.  The
;;;                  entry associates the current ICP port with an index for
;;;                  icp-object.  This function executes
;;;                  corresponding-icp-object-maker-body, an arg to the
;;;                  def-icp-object form which defined this function.  The body
;;;                  typically arranges for the remote side to create an ICP object
;;;                  of type icp-object-type and associate its index with an ICP
;;;                  input port there.
;;; Non-local exits: corresponding-icp-object-maker-body should not exit non-locally.
;;; Memory impact:   On the local side, the memory for the new object index is two
;;;                  gensym-conses plus one possibly new index space slot.  This
;;;                  memory is reclaimed either when icp-object is deleted or when
;;;                  the ICP socket shuts down on the local side.  Typical
;;;                  allocation on the remote side is memory for the remote object
;;;                  itself and possibly memory for a new index space slot for the
;;;                  object index (depending on whether or not the index space needs
;;;                  to enlarge).  This memory is reclaimed either when the remote
;;;                  object is deleted or when the ICP socket shuts down.

;;; Declaration:     GET-ICP-OBJECT-INDEX-FOR-<icp-object-type>
;;;                   (icp-object icp-output-port) => object-index
;;; Type:             Lisp function.
;;; Purpose:         Get the object index for an ICP object from an ICP output port.
;;; Arguments:             An ICP object and an ICP output port.
;;; Return behavior: Returns the object index, a fixnum.
;;; Users:             See def-icp-object-type.
;;; Prerequisites:   Defined by def-icp-object-type.
;;; Side effects:    None.
;;; Non-local exits: None.
;;; Memory impact:   None.

;;; Declaration:     SET-ICP-OBJECT-INDEX-FOR-<icp-object-type>
;;;                   (icp-object object-index icp-output-port)
;;; Type:             Lisp function.
;;; Purpose:             Add a new object index to an ICP output port.
;;; Arguments:       An ICP object, its object index (a fixnum), and the ICP output
;;;                  port which will use that index to refer to the object on the
;;;                  remote side.
;;; Return behavior: No useful value.
;;; Users:             See def-icp-object-type.
;;; Prerequisites:   Defined by def-icp-object-type.
;;; Side effects:    Modifies the place named by the
;;;                  access-form-for-corresponding-icp-object-map argument to the
;;;                  def-icp-object-type form which created this function.
;;; Non-local exits: None.
;;; Memory impact:   Allocates a new entry (two gensym-conses) in the place named by
;;;                  the access-form-for-corresponding-icp-object-map argument to
;;;                  the def-icp-object-type form which created this function.  This
;;;                  memory is reclaimed when icp-object is deleted or when the ICP
;;;                  connection shuts down.
;;; Possible bugs:   No attempt is made to verify that an object index does not
;;;                  already exist for the given ICP port.

;;; Declaration:     GET-<icp-object-type>-FROM-ICP-PORT
;;;                   (icp-port icp-object-index) => icp-object
;;; Type:             Lisp function.
;;; Purpose:             Get an ICP object given from a given ICP input port and index.
;;; Arguments:             An ICP port and an ICP object index (a fixnum).
;;; Return behavior: The ICP object, or nil if it is not indexed in this ICP port.
;;; Users:             See def-icp-object-type.
;;; Prerequisites:   Defined by def-icp-object-type.
;;; Side effects:    None.
;;; Non-local exits: None.
;;; Memory impact:   None.

;;; Declaration:     RECLAIM-ICP-OBJECT-MAP-FOR-<icp-object-type> (icp-object)
;;; Type:             Lisp function.
;;; Purpose:             Reclaim the entire object map for an ICP object.
;;; Arguments:             An ICP object.
;;; Return behavior: No useful value.
;;; Users:             See def-icp-object-type.
;;; Prerequisites:   Defined by def-icp-object-type.
;;; Side effects:    The object map of icp-object, which is the place named by the
;;;                  access-form-for-corresponding-icp-object-map arg to the
;;;                  def-icp-object form for <icp-object-type>, is no longer usable.
;;; Non-local exits: None.
;;; Memory impact:   Reclaims the memory allocated by
;;;                  MAKE-CORRESPONDING-ICP-<icp-object-type>.

;;; Declaration:     RECLAIM-ICP-PORT-ENTRY-FOR-<icp-object-type>
;;;                   (icp-object icp-port)
;;; Type:             Lisp function.
;;; Purpose:             Reclaim a single entry in the object map of an ICP object.
;;; Arguments:             An ICP object an an ICP port.
;;; Return behavior: No useful value.
;;; Users:             See def-icp-object-type.
;;; Prerequisites:   Defined by def-icp-object-type.
;;; Side effects:    The object map of icp-object, which is the place named by the
;;;                  access-form-for-corresponding-icp-object-map arg to the
;;;                  def-icp-object form for <icp-object-type>, no longer contains
;;;                  an entry for icp-port.
;;; Non-local exits: None.
;;; Memory impact:   Reclaims some of the memory allocated by
;;;                  MAKE-CORRESPONDING-ICP-<icp-object-type>.

;;; Declaration:     SET-ACCESS-FORM-FOR-<icp-object-type> (icp-object new-value)
;;; Type:             Lisp function.
;;; Purpose:             Overwrite the object map of an ICP object.
;;; Arguments:       An ICP object and a new value, which should be a list of
;;;                  gensym-conses alternating ICP ports and object indexes
;;;                  (fixnums).
;;; Return behavior: No useful value.
;;; Users:             See def-icp-object-type.
;;; Prerequisites:   Defined by def-icp-object-type.
;;; Side effects:    Replaces the object map of icp-object, which is the place named
;;;                  by the access-form-for-corresponding-icp-object-map arg to
;;;                  the def-icp-object form for <icp-object-type>.
;;; Non-local exits: None.
;;; Memory impact:   This function assumes that the old object map has been
;;;                  reclaimed.  If not, a leak will result.

;;; Def-icp-object-type establishes name-of-corresponding-icp-object-index-
;;; space and access-form-for-corresponding-icp-object-map for icp-object-
;;; type.  It also defines for icp-object-type a `corresponding icp object
;;; maker', the name of which is constructed by prefixing icp-object-type with
;;; "MAKE-CORRESPONDING-ICP-", and the body of which consists of code to assign
;;; an icp object index followed by corresponding-icp-object-maker-body and
;;; code to return the assigned index.

;;; Icp-object-type must be a type of named structure (a type defined by
;;; def-structure).  The structure must be stored as a simple vector rather than a
;;; list; the :type option, if used, must be vector rather than list.  The purpose
;;; of these restrictions is to simplify determining the icp-object-type of an
;;; object from the type of the named structure.  Determining icp-object-type is
;;; necessary in order to get the reclaimer function (see below) which is in the
;;; reclaimer-for-icp-port-entry property of icp-object-type.  The only exceptions
;;; to these restrictions are the icp object types symbol and font-map.  The icp
;;; object type symbol is a symbol and the icp object type font-map is a list (for
;;; historical reasons).  Thus, if an icp object is a symbol, the icp object type
;;; is assumed to be symbol, and if an icp object is a list, the icp object type
;;; is assumed to be font-map.  The substitution macro
;;; icp-object-type-given-icp-object (see below) makes use of these assumptions.

;;; The corresponding icp object maker gets one argument, the icp object for
;;; which a corresponding object is to be made.  Icp-object-definer-body uses
;;; the icp object type to refer to the icp object to be defined and
;;; corresponding-icp-object-index (literally) to refer to the assigned icp
;;; object index (for the corresponding object in the specified index space).

;;; Access-form-for-corresponding-icp-object-map uses the icp object type, in
;;; any number of places as a subform, to refer to the icp object.  It may be
;;; evaluated more than once in the icp object maker.


;;; Also defined for icp-object-type are functions to get and to set the
;;; icp object index for this type of object with respect to a given icp
;;; port. The names of the get and set functions are constructed by prefixing
;;; icp-object-type with "GET-ICP-OBJECT-INDEX-FOR-" and "SET-ICP-OBJECT-INDEX-
;;; FOR-", respectively.   The get function's args are an icp object (of type
;;; icp-object-type and icp-port, in that order.  The set function's args are
;;; an icp object (of type icp-object-type), corresponding-icp-object-index,
;;; and icp-port, in that order.

;; [The above added 2/8/89 and 3/8/89 -mhd & blm]


;;; Also defined for icp-object-type is a function to get the object
;;; given an index and an icp port.  The name of the function is constructed
;;; by concatenating "GET-", icp-object-type, and "-FROM-ICP-PORT".  Its args
;;; are icp-port and icp-object-index, in that order.  It returns the result
;;; of calling get-object-from-index-space with the following arguments:
;;;
;;;   (1) the index space named name-of-corresponding-icp-object-
;;;         index-space in icp-port; and
;;;   (2) icp-object-index

;; [The above added 3/8/89 -mhd]


;;; Also defined for icp-object-type are a function to reclaim the plist in
;;; access-form-for-corresponding-icp-object-map and a function to remove one
;;; entry from the plist.  The names of the functions are constructed by prefixing
;;; icp-object-type with "RECLAIM-ICP-OBJECT-MAP-FOR-" for the former and with
;;; "RECLAIM-ICP-PORT-ENTRY-FOR-" for the latter.

;;; The requirements for what must be done when an icp object is reclaimed are
;;; determined by what is done when an icp object is created.  When an icp message
;;; is sent, the sender code (generated by expand-definition-of-icp-message-type)
;;; loops through the argument variables.  For each arg that is an icp object, it
;;; checks if a corresponding icp object exists in the other process by checking
;;; if there is an entry for it in access-form-for-corresponding-icp-object-map.
;;; If not, it calls the function named by concatenating "MAKE-CORRESPONDING-ICP-"
;;; and icp-object-type.  This function is defined by def-icp-object-type and it
;;; calls assign-corresponding-icp-object-index which puts the object into the
;;; index space for the output port from which the message is being sent (each
;;; port has its own index space).  It also enters the index into
;;; access-form-for-corresponding-icp-object-map.  Finally, it executes
;;; corresponding-icp-object-maker-body which is an arg to def-icp-object-type.
;;; This typically calls an icp sender function with the index as an arg.
;;; The handler function makes the icp object on the other side and calls
;;; store-corresponding-icp-object which puts the icp object into the index
;;; space for the (input) port handling the message.

;;; Thus, one requirement when reclaiming an icp object is that for each port in
;;; access-form-for-corresponding-icp-object-map (these should only be output
;;; ports), the index for the port be deassigned for the index space for the port,
;;; and the location corresponding to the index in the index space be set to nil
;;; so that it does not have a pointer to the reclaimed object.  In addition,
;;; it is desireable to reclaim corresponding objects in other processes.  When
;;; this is done, it is important that the location corresponding to the index
;;; in the index space of the input port for the remote process be set to nil.

;;; In general, the following must be done when reclaiming an icp object:
;;; 1.  reclaim the data structure in each process
;;; 2.  deassign the icp index in index space from which it was assigned
;;; 3.  set all locations in index spaces that point to the object to nil.
;;; The third requirement is crucial because when an icp index space
;;; is reclaimed, remove-icp-port-entries-from-icp-object is called for
;;; each object in the index space.  Thus, it is important that there be
;;; no pointers in the index space to reclaimed objects.

;;; The reclaim icp object map function should be used to reclaim the contents of
;;; access-form-for-corresponding-icp-object-map when the icp object is deleted.
;;; Before reclaiming the plist, this function loops through the entries,
;;; deassigning indices, and sending an icp message to delete corresponding
;;; objects.  The special variable in-message-group-context?  must be bound to
;;; non-nil if the reclaim function is being called from within the dynamic scope
;;; of a writing-icp-message-group form.  This happens, for example, when
;;; decaching graph or icon renderings (when these are decached from within their
;;; draw methods).  In such a case, access-form-for-corresponding-icp-object-map
;;; should only contain one icp-port - index pair and the icp-port should be eq to
;;; current-icp-port.  In other words, the icp-object should have only one
;;; corresponding icp object which should exist only in the process currently
;;; being written to.  The special variable dont-reclaim-corresponding-object?
;;; should be bound to non-nil if no attempt should be made to send an ICP message
;;; to reclaim the corresponding object(s).  This is the case, for example, when
;;; ICP objects are reclaimed after an ICP connection has been shutdown.

;; Note that because this function takes an icp object as an argument rather than
;; the value of the access form, it can not be used as a slot reclaimer for
;; the access form.

;;; The name of the function to remove an icp port entry is put in the
;;; reclaimer-for-icp-port-entry property of icp-object-type.  The function takes
;;; an icp object and icp-port?  as arguments.  It splices out only the entry
;;; corresponding to icp-port?  in access-form-for-corresponding-icp-object-map.
;;; This is useful when a connection is broken and the icp-sockets become
;;; inactive; the entries for icp-ports for the inactive icp-sockets must be
;;; removed from the corresponding icp object maps.  This is automatically done by
;;; remove-icp-port-entries-from-icp-object which is the index space object
;;; reclaimer arg for make-index-space in make-icp-object-index-space.

;;; If icp-object-reclaimer?  is non-nil, it is put in the
;;; reclaimer-for-icp-object property of icp-object-type.  It is used by the
;;; handler for delete-icp-object-for-process to reclaim the object.

;;; If icp-object-shutdown-reclaimer?  is non-nil, it is put in the
;;; shutdown-reclaimer-for-icp-object property of icp-object-type.  It should be
;;; a symbol naming a function of two arguments, the icp-object and the icp-port
;;; containing the index space which points to this ICP object.  This function
;;; is called from remove-icp-port-entries-from-icp-object as a result of
;;; reclaiming the icp index space.  The icp index space is reclaimed by
;;; reclaim-inactive-icp-sockets.  Note that the connection loss callback
;;; functions are called before the reclamation of the ICP index space.  This
;;; means that the icp-object-shutdown-reclaimer function is called only on those
;;; objects which remain in the index space after the connection loss callback
;;; functions return.

;;; Notify-when-reclaiming-icp-object? is useful when debugging.  It prints
;;; the icp object and its index when the icp object map reclaimer is called.

#+development
(def-system-variable notify-when-reclaiming-icp-object? INT1 nil)

;; [The above added 10/28/89 - agh]

(defun-for-macro get-name-of-function-to-get-icp-object-index (icp-object-type)
  (format-symbol "GET-ICP-OBJECT-INDEX-FOR-~A" icp-object-type))

(defun-for-macro get-name-of-function-to-reclaim-icp-port-entry (icp-object-type)
  (format-symbol "RECLAIM-ICP-PORT-ENTRY-FOR-~A" icp-object-type))

;The standard-icp-object-index-space is the default index space.

;The item index space has a shadow index space to store the frame serial numbers
;of the items.
;Or, should the frame serial numbers be the key into the space?
;  If so, need to associate g2-time-at-start with the fsn's


;index-space-names are pushed onto this list while :no-macros is not on *features*
(eval-when (:compile-toplevel :load-toplevel :execute)
(defmacro all-index-space-names ()
  (declare (special all-index-space-names))
  (unless (boundp 'all-index-space-names)
    (setq all-index-space-names nil))
  `',all-index-space-names)

(defvar all-index-space-names (all-index-space-names))
)

(defvar inhibit-corresponding-icp-object-making nil)

(defmacro def-icp-object-type
          (icp-object-type
           (name-of-corresponding-icp-object-index-space
            access-form-for-corresponding-icp-object-map
            &optional icp-object-reclaimer? icp-object-shutdown-reclaimer?)
           &body corresponding-icp-object-maker-body)
  (let* ((non-resumable-p (memq icp-object-type non-resumable-icp-object-types))
         (defun (if non-resumable-p
                    'defun
                    'defun-resumable-icp-function))
         (name-of-function-to-reclaim-icp-port-entry
           (get-name-of-function-to-reclaim-icp-port-entry icp-object-type))
         (name-of-function-to-set-access-form
           (format-symbol "SET-ACCESS-FORM-FOR-~A" icp-object-type))
         (name-of-function-to-establish-icp-object-index
           (format-symbol "ESTABLISH-NEW-OBJECT-INDEX-FOR-~a" icp-object-type))
         (name-of-macro-to-establish-icp-object-index
           (format-symbol "ESTABLISH-NEW-OBJECT-INDEX-FOR-~a-MACRO"
                          icp-object-type)))
    `(progn
       (def-substitution-macro ,name-of-macro-to-establish-icp-object-index
           (,icp-object-type icp-port send-enlarge-message-p)
         (multiple-value-bind (corresponding-icp-object-index
                                new-index-limit-plus-one?)
             (non-resumable-icp-form
               (assign-corresponding-icp-object-index
                 ,icp-object-type
                 ',name-of-corresponding-icp-object-index-space
                 send-enlarge-message-p))
           (setf ,access-form-for-corresponding-icp-object-map
                 (gensym-cons
                   icp-port
                   (gensym-cons
                     corresponding-icp-object-index
                     ,access-form-for-corresponding-icp-object-map)))
           (if send-enlarge-message-p
               corresponding-icp-object-index
               (values corresponding-icp-object-index new-index-limit-plus-one?))))

       ,@(unless (eval-feature :no-macros)
           `((eval-when (:compile-toplevel :load-toplevel :execute)
               (pushnew ',name-of-corresponding-icp-object-index-space
                        all-index-space-names)
               (pushnew ',name-of-macro-to-establish-icp-object-index
                        trif-macroexpand-approved-ab-macros))))

       (,defun ,name-of-function-to-establish-icp-object-index
           (,icp-object-type icp-port &optional (send-enlarge-message-p t))
         (,name-of-macro-to-establish-icp-object-index
            ,icp-object-type icp-port send-enlarge-message-p))

       (,defun ,(format-symbol "MAKE-CORRESPONDING-ICP-~A" icp-object-type)
              (,icp-object-type)
         (with-disabled-write-icp-suspension
           (let ((corresponding-icp-object-index
                   (,name-of-macro-to-establish-icp-object-index
                      ,icp-object-type current-icp-port t)))
             (unless inhibit-corresponding-icp-object-making
               ,@corresponding-icp-object-maker-body)
             corresponding-icp-object-index)))

       (defun ,(get-name-of-function-to-get-icp-object-index icp-object-type)
              (,icp-object-type icp-port)
         (getfq ,access-form-for-corresponding-icp-object-map icp-port))

       (defun ,(format-symbol "SET-ICP-OBJECT-INDEX-FOR-~A" icp-object-type)
              (,icp-object-type corresponding-icp-object-index icp-port)
         (setf ,access-form-for-corresponding-icp-object-map
               (gensym-cons
                 icp-port
                 (gensym-cons
                   corresponding-icp-object-index
                   ,access-form-for-corresponding-icp-object-map))))

       (defmacro ,(format-symbol "GET-~a-FROM-ICP-PORT" icp-object-type)
              (icp-port icp-object-index)
         `(get-from-icp-port ,icp-port ,icp-object-index
                             ',',name-of-corresponding-icp-object-index-space))

       (defmacro ,(format-symbol "GET-~a-FROM-ICP-PORT-IF-ANY" icp-object-type)
           (icp-port icp-object-index)
         `(get-from-icp-port-if-any ,icp-port ,icp-object-index
                                    ',',name-of-corresponding-icp-object-index-space))

       (defun ,(format-symbol "RECLAIM-ICP-OBJECT-MAP-FOR-~A" icp-object-type)
              (,icp-object-type)
         (let ((icp-object-map ,access-form-for-corresponding-icp-object-map))
           (when icp-object-map
             (reclaim-icp-object-map
               ,icp-object-type icp-object-map
               ',name-of-corresponding-icp-object-index-space))))

       (defun ,name-of-function-to-reclaim-icp-port-entry
              (,icp-object-type icp-port)
         (reclaim-icp-port-entry
           icp-port ,icp-object-type
           ,access-form-for-corresponding-icp-object-map
           ',name-of-function-to-set-access-form))

       (defun ,name-of-function-to-set-access-form
              (,icp-object-type new-value)
         (setf ,access-form-for-corresponding-icp-object-map new-value))

       (eval-when (:compile-toplevel :load-toplevel :execute)
         (initialize-icp-object-type-compile
           ',icp-object-type
           ',name-of-corresponding-icp-object-index-space
           ',access-form-for-corresponding-icp-object-map))

       (initialize-icp-object-type
         ',icp-object-type
         ',icp-object-reclaimer?
         ',icp-object-shutdown-reclaimer?
         ',name-of-function-to-reclaim-icp-port-entry))))

(eval-when (:compile-toplevel :load-toplevel :execute)
(defun initialize-icp-object-type-compile (icp-object-type
                                            name-of-corresponding-icp-object-index-space
                                            access-form-for-corresponding-icp-object-map)
  (setf (name-of-corresponding-icp-object-index-space icp-object-type)
        name-of-corresponding-icp-object-index-space)
  (setf (access-form-for-corresponding-icp-object-map icp-object-type)
        access-form-for-corresponding-icp-object-map)
  icp-object-type)

(defun initialize-icp-object-type (icp-object-type
                                    icp-object-reclaimer?
                                    icp-object-shutdown-reclaimer?
                                    name-of-function-to-reclaim-icp-port-entry)
  (setf (reclaimer-for-icp-object icp-object-type)
        (when icp-object-reclaimer?
          (symbol-function icp-object-reclaimer?)))
  (setf (shutdown-reclaimer-for-icp-object icp-object-type)
        (when icp-object-shutdown-reclaimer?
          (symbol-function icp-object-shutdown-reclaimer?)))
  (setf (reclaimer-for-icp-port-entry icp-object-type)
        (symbol-function name-of-function-to-reclaim-icp-port-entry))
  icp-object-type)
)



;;; Declaration:     icp-object-type-given-icp-object (icp-object)
;;; Type:             G2 substitution macro.
;;; Purpose:             Obtain the ICP object type of an ICP object.
;;; Arguments:       An ICP object.
;;; Return behavior: Returns a symbol namining the ICP type of an ICP object.
;;;                  This is always a symbol, because ICP object types
;;;                  are never composed.
;;; Users:           ICP internals:
;;;                    INT3: delete-icp-object-for-process ICP message
;;;                    INT4: remove-icp-port-entries-from-icp-object
;;;                          remove-icp-object-from-index-space
;;; Prerequisites:   The def-icp-object-type form for the object must have been
;;;                  executed.
;;; Side effects:    None.
;;; Non-local exits: None.
;;; Memory impact:   None.

(defun-simple icp-object-type-given-icp-object
              (icp-object name-of-corresponding-icp-object-index-space)
  (cond
    ((simple-vector-p icp-object)
     (or (let ((type (g2-type-name-of-named-simple-vector icp-object)))
           (when (and (symbolp type)
                      (eq (symbol-package type) the-g2-defstruct-package))
             (ab-name-of-unique-structure-type type)))
         (current-system-case
           (ab (when (framep-function icp-object)
                 'registered-item)))))
    ((symbolp icp-object)
     (when (eq name-of-corresponding-icp-object-index-space 'standard-icp-object-index-space)
       'symbol))
    ;; Note: need to unify the icp-plist for the
    ;; types font-map and icp-tree, probably by making them
    ;; both use the current icp-tree icp-plist mechanism.
    ;; - rh, 7/18/96  (... I think jed or ajs has done this)
    ((consp icp-object)
     'font-map)
    (t
     #+development
     (warn "~S was unable to determine the icp-object-type of ~S"
           'icp-object-type-given-icp-object icp-object)
     nil)))



;;;; ICP Message Types

;;; Declaration:     icp-message-handler-array
;;; Type:             Lisp defvar.
;;; Purpose:             Store handler functions for ICP messages.
;;; Value:           A simple general array of size icp-message-handler-array-size.
;;;                  When there is a handler for an ICP message, the element of this
;;;                  array corresponding to its message code contains a funcallable
;;;                  compiled function which handles this ICP message.
;;; Return behavior: N/A.
;;; Users:           ICP internals:
;;;                    INT1: functions defined by def-icp-object-type
;;;                    INT2: handle-icp-messages
;;; Prerequisites:         None.
;;; Side effects:    N/A.
;;; Non-local exits: N/A.
;;; Memory impact:   Initialized once, at launch time.

;;; Icp-message-handler-array is used for dispatching to handle icp messages....
;;; Cell 0 of icp-message-handler-array must not be used.

(eval-when (:compile-toplevel :load-toplevel :execute)
(defmacro icp-message-handler-array-size () 750))        ; 150 till 5/23/89
                                                        ; 250 till 5/24/90
                                                        ; 350 till 10/16/95
(defvar icp-message-handler-array
        (make-array-with-nils #.(icp-message-handler-array-size)))

(defvar icp-message-handler-name-array
        (make-array-with-nils #.(icp-message-handler-array-size)))







;;; Declaration:     icp-printing-message-handler-array
;;; Type:             Lisp defvar.
;;; Purpose:         Store handler functions for ICP messages which perform
;;;                  printing.
;;; Value:           A simple general array of size icp-message-handler-array-size.
;;;                  When there is a handler for an printing message, the element of
;;;                  this array corresponding to its message code contains a symbol
;;;                  naming a funcallable function which handles this ICP message.
;;;                  Other elements contain a symbol for a default function which
;;;                  signals an error.
;;; Return behavior: N/A.
;;; Users:             G2 printing (def-icp-message-functions in INT1).
;;; Prerequisites:   None.
;;; Side effects:    N/A.
;;; Non-local exits: N/A.
;;; Memory impact:   Initialized once, at launch time.
;;; Notes:           This array exists mainly to provide forward reference to the
;;;                  printing functions.

;;; `Icp-printing-message-handler-array' provides the dispatching when printing.
;;; The array entries are symbols, the symbol functions of which implement the
;;; actual printing.  The initial value of array elements is a routine that
;;; will complain if called during development.  As each message type is defined
;;; either by def-message-type, or def-icp-message-functions that symbol is
;;; replaced by the name of the actual printing handler.  These are of the
;;; form "PRINT-HANDLER-FOR-<icp-message-type>."

;;; The symbol-function of these symbols is accessed only in G2, ie. Telewindows
;;; does not define them, nor does it access them.  No compile time check is
;;; made that each one is actually defined in G2.  All of these functions,
;;; including the default handler, are defined in the module PRINTING.

;;; Using a dispatch array rather than calling the printing function directly
;;; resolves a few problems.  One problem it solves is the problem of having the
;;; functions defined for telewindows.  Since no explicit reference to the
;;; symbol function is made until run time the compiler will not complain about
;;; undefined functions.  The second problem is that we want to define the
;;; printing functions as a group in the module PRINTING, but that module must
;;; be defined after all the icp-message handlers and their argument types have
;;; been defined.  So the calls upon printing functions are all forward
;;; references.  It seemed unusual to be introducing def-forward-references in
;;; the macroexpansion.

(defvar icp-printing-message-handler-array
        (make-array #.(icp-message-handler-array-size)
                    :initial-element 'default-print-handler-for-icp-messages))



;;; Icp-message-type-code-offset ...  Icp messages always start with an icp byte
;;; larger than this.

(eval-when (:compile-toplevel :load-toplevel :execute)
(defmacro icp-message-type-code-offset ()
  64000))



;;; An `ICP message type' is a symbol....  Each icp message type is assigned a
;;; permanent ICP message type code.  Such indices are defined in a universal
;;; database.

;; Consider treating an icp message type as an icp object, where the
;; corresponding icp object map would simply be the symbol plist.  This would
;; eliminate the need to assign permanent icp message type indices for most
;; message types.



;;; Declaration:     def-icp-message-type-code (name-of-message message-code)
;;; Type:             Lisp macro.
;;; Purpose:             Declare a unique code for an ICP message.
;;; Arguments:             name-of-message is an unevaluated symbol naming the message.
;;;                  message-code is a fixnum code for the message.
;;; Return behavior: No useful value.
;;; Users:           Public ICP messages (INT1), GSI (module GSI-COMMON),
;;;                  Telewindows and G2 printing (WINDOWS1), G2 foreign functions
;;;                  (G2-FOREIGN), G2-to-G2 communication (G2DS, G2DS-NUPEC).
;;; Prerequisites:   None.
;;; Side effects:    Sets the icp-message-type-code property of <name-of-message>.
;;;                  This is an internal property and should not be used outside of
;;;                  ICP.
;;; Non-local exits: Signals an error at compile time if the code is already in use.
;;; Memory impact:   Compile-time consing, one-shot consing onto the
;;;                  icp-message-type-code plist for each name-of-message at launch
;;;                  time.
;;; Notes:           The icp-message-type-code property need not be present at run
;;;                  time.  We could save around 2 * 8 * 225 bytes if we removed it.

;;; This assigns codes for ICP message types.

(eval-when (:compile-toplevel :load-toplevel :execute)


(def-global-property-name icp-message-type-code)

#+development
(def-global-property-name icp-message-signature)

#+development
(defvar icp-message-type-code-table (make-hash-table :test 'eql))

(defvar-for-macro icp-messages-of-no-use-to-gsi nil)

(def-global-property-name priority-for-icp-priority-category)
(def-global-property-name icp-priority-category-for-message)

(defmacro def-icp-priority-category (name &optional priority)
  `(setf (priority-for-icp-priority-category ',name) ',(or priority name)))

(def-icp-priority-category icp) ; was: (def-icp-priority-category icp immediate)
(def-icp-priority-category i-am-alive)
(def-icp-priority-category rpc)
(def-icp-priority-category gsi)
(def-icp-priority-category gsi-ds data-service)
(def-icp-priority-category g2-ds data-service)
(def-icp-priority-category tw)
(def-icp-priority-category gspan)
(def-icp-priority-category view)
(def-icp-priority-category ole)

(eval-when (:compile-toplevel :load-toplevel :execute)
(defvar icp-priority-categories-for-gsi '(icp start-icp-task resume-icp-task rpc gsi gsi-ds))
)

(defmacro def-icp-message-type-code
    (icp-message-type icp-message-type-code &optional category dont-warn-about-redefinition-p)
  #-development (declare (ignore dont-warn-about-redefinition-p))
  (let ((useful-to-gsi-p (member category icp-priority-categories-for-gsi)))
    (cond
      ((or (not (gsi-eliminable-p)) useful-to-gsi-p)
       `(add-icp-message-type-code
          ',icp-message-type ,icp-message-type-code ',category
          #+development ,dont-warn-about-redefinition-p))
      (t
       (unless (eval-feature :no-macros)
         (pushnew icp-message-type icp-messages-of-no-use-to-gsi))
       nil))))

(defun add-icp-message-type-code (icp-message-type icp-message-type-code category
                                  #+development &optional #+development dont-warn-about-redefinition-p)
  #+development
  (let ((old-icp-message-type (gethash icp-message-type-code icp-message-type-code-table)))
    (when (and old-icp-message-type
               (not (eq old-icp-message-type icp-message-type))
               (not dont-warn-about-redefinition-p))
      (warn "The icp-message-type-code ~D, being assigned to ~S, was already in use by ~S"
            icp-message-type-code icp-message-type old-icp-message-type))
    (setf (gethash icp-message-type-code icp-message-type-code-table) icp-message-type))
  (unless (eq category 'gspan) ; avoid redefinition problem
    (setf (icp-priority-category-for-message icp-message-type) category))
  (setf (icp-message-type-code icp-message-type) icp-message-type-code))


  ;; The following are not yet defined.

(def-icp-message-type-code restart-yourself 11)
(def-icp-message-type-code I-have-restarted 12)
(def-icp-message-type-code reset-your-memory 13)        ; with alloc args
(def-icp-message-type-code I-am-alive 14 i-am-alive)


  ;; The following are defined in module ICP.

(def-icp-message-type-code enlarge-corresponding-icp-object-index-space 15 rpc)
(def-icp-message-type-code nop 16 icp)
(def-icp-message-type-code end-message-block 17 icp)
(def-icp-message-type-code define-dummy-object 18)


  ;; The following are defined in module WORKSTATION

(def-icp-message-type-code initialize-telewindows-workstation 19 tw)
(def-icp-message-type-code initialize-ntw-workstation 405 tw)

;(def-icp-message-type-code shutdown-telewindows-workstation 20)  ; obsolete

  ; before 3/29/89:
  ; (def-icp-message-type-code telewindows-command-user-event 24)
  ; (def-icp-message-type-code telewindows-character-user-event 25)
  ;
  ; after 3/29/89 ==>
(def-icp-message-type-code telewindows-workstation-event 24 tw)
;; after 2/5/02:  (MHD)
(def-icp-message-type-code extended-telewindows-workstation-event 25)

(def-icp-message-type-code telewindows-start-mouse-tracking 26 tw)
(def-icp-message-type-code telewindows-stop-mouse-tracking 27 tw)
(def-icp-message-type-code define-gensym-window 30 tw)
  ;; (def-icp-message-type-code define-telewindows-workstation 28)
  ;; (def-icp-message-type-code set-position-of-mouse 29)
  ;; 28 and 29 are assigned to define-telewindows-workstation and
  ;; set-position-of-mouse-in-workstation, resp., in TELESTUBS.
  ;; It should be moved back here eventually, but is included there
  ;; in order to patch release 1.11b!! (MHD 3/38/89)


  ;; The following are defined in module WINDOWS.

(def-icp-message-type-code begin-window-update 21)        ; begins a message group

(def-icp-message-type-code set-up-palette 23) ; obsolete nop, but may be sent by
                                                ;   G2's older than 12/27/89
(def-icp-message-type-code initialize-scratchpad-raster 31)
(def-icp-message-type-code paint-solid-rectangle-in-current-scratchpad-raster 32)
(def-icp-message-type-code paint-line-in-current-scratchpad-raster 33)
(def-icp-message-type-code paint-arc-or-circle-in-current-scratchpad-raster 34)
(def-icp-message-type-code paint-filled-triangle-in-current-scratchpad-raster 35)

(def-icp-message-type-code paint-wide-line-in-current-scratchpad-raster 36)
(def-icp-message-type-code paint-point-in-current-scratchpad-raster 37)

(def-icp-message-type-code paint-solid-rectangle-in-current-window 41)
(def-icp-message-type-code add-solid-rectangle-to-current-window 42)
(def-icp-message-type-code add-from-icon-rendering-to-current-window 43)
(def-icp-message-type-code add-upward-sloping-line-to-current-window 44)
(def-icp-message-type-code add-downward-sloping-line-to-current-window 45)
(def-icp-message-type-code copy-from-tiling-pattern-to-current-window 46)
(def-icp-message-type-code add-from-line-of-text-to-current-window 47)

(def-icp-message-type-code beep-in-window 48)        ; added 3/14/90 (MHD)
(def-icp-message-type-code scroll-rectangle-in-current-window 49)

;; jh, 12/27/95.  Following six codes added for Telewindows spawning project.
(def-icp-message-type-code spawn-remote-process 50)
(def-icp-message-type-code remote-process-exists-p 51)
(def-icp-message-type-code kill-remote-process 52)
(def-icp-message-type-code spawn-remote-process-reply 53)
(def-icp-message-type-code remote-process-exists-p-reply 54)
(def-icp-message-type-code kill-remote-process-reply 55)
 ;pbk 11/8/95
(def-icp-message-type-code orient-and-paint-line-of-text-to-current-scratchpad-raster 56)

(def-icp-message-type-code spawn-remote-executable 57)

(def-icp-message-type-code paint-filled-polygon-in-current-scratchpad-raster 58)


;; GSI ICP Messages Type Codes

;; IN USE: 59-80

;; For data transfer within context of a data server
(def-icp-message-type-code modify-gsi-sensor-definition                59 gsi-ds)
(def-icp-message-type-code begin-sensor-list                           60 gsi-ds)
(def-icp-message-type-code load-sensor-list-element                    61 gsi-ds)
(def-icp-message-type-code end-sensor-list                             62 gsi-ds)
(def-icp-message-type-code get-values-for-sensors-in-list              63 gsi-ds)
(def-icp-message-type-code set-values-for-sensors-in-list              64 gsi-ds)
(def-icp-message-type-code write-user-message-string                   65 gsi)
(def-icp-message-type-code return-peer-version                         66 gsi)
(def-icp-message-type-code receive-value-for-ping-request              67 gsi-ds)
(def-icp-message-type-code receive-value-for-gsi-sensor                68 gsi-ds)

;; For data server control
(def-icp-message-type-code initialize-data-server                      69 gsi-ds)
;; shut-down-data-server was promoted to the base ICP protocol by ncc 20 Apr
;; 1995 in support of the new ICP shutdown protocol with handshaking.
(def-icp-message-type-code shut-down-data-server                       70 icp)
(def-icp-message-type-code pause-data-server                           71 gsi-ds)
(def-icp-message-type-code resume-data-server                          72 gsi-ds)
(def-icp-message-type-code send-data-values-if-any                     73 gsi)

(def-icp-message-type-code stop-sending-values-for-sensors-in-list     74 gsi-ds)
(def-icp-message-type-code define-gsi-sensor                           75 gsi-ds)
(def-icp-message-type-code receive-value-for-gsi-sensor-with-timestamp 76 gsi-ds)
(def-icp-message-type-code define-gsi-interface                        77 gsi-ds)
(def-icp-message-type-code receive-gsi-sensor-value-vector             78 gsi-ds)
(def-icp-message-type-code receive-timestamped-gsi-sensor-value-vector 79 gsi-ds)
(def-icp-message-type-code receive-values-for-gsi-sensors              80 gsi-ds)

  ;; ICP message numbers 59 to 80 are used in GSI data service.
  ;; ICP message numbers 90 to 109 are used in MCS data service.
  ;; ICP message numbers 110 to 130,
  ;;      170, 171, 172 are used in G2DS data service.
  ;; ICP message numbers 110 to 130 are used in G2DS data service.
  ;;

  ;; Intern and add-to-list-of-symbols are defined in module ICP, and make-tiling-pattern
  ;; and begin-making-icon-rendering are defined in module WINDOWS.

(def-icp-message-type-code intern 81 rpc)
(def-icp-message-type-code add-to-list-of-symbols 82 rpc)
(def-icp-message-type-code make-tiling-pattern 83)
(def-icp-message-type-code begin-making-icon-rendering 84)
(def-icp-message-type-code region-extrema-for-stored-raster 85)
(def-icp-message-type-code intern-keyword 86 rpc)

;;; ICP message type codes 100-105 are reserved for OLE drag-and-drop emulation.

(eval-when (:compile-toplevel :load-toplevel :execute)
;;#+obsolete ;soon after 6/10/97
(def-icp-message-type-code request-ole-object-information 100 ole)
;;#+obsolete ;soon after 6/10/97
(def-icp-message-type-code provide-ole-object-information 101 ole)
(def-icp-message-type-code request-ole-object-transfer 102 ole)
(def-icp-message-type-code initiate-ole-object-transfer 103 ole)
(def-icp-message-type-code ole-object-transfer-milestone 104 ole)
)

  ;; There is an overlap in ICP message codes 120-127.  Both GSPAN and G2ds use these
  ;; codes, but this doesn't cause problems due to the following facts:
  ;;   1) Def-icp-message-type-code associates message codes with symbols,
  ;;      so it is possible (but strongly denigrated) for two different modules
  ;;      to send the same code number with two different "meanings".  Thus
  ;;      there is no conflict in sending codes 120-127.
  ;;   2) The def-icp-message-type forms for the GSPAN codes 120-127 contain no
  ;;      handler body, so no GSPAN handler functions get defined.  The
  ;;      def-icp-message-type forms for G2ds do create handler functions, but there
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
  ;; module.  If this is not feasible, place clear warning in INT where all
  ;; the other def-icp-message-type-codes are found. (jh, 4/25/90)

  ;; The following codes are for icp message types defined in GSPAN.

(def-icp-message-type-code new-externally-simulated-object 120 nil t) ; g2ds-initialize-server
(def-icp-message-type-code define-external-simulation-object 121 nil t) ; g2ds-shut-down-server
(def-icp-message-type-code simulation-initialization-value 122 nil t) ; g2ds-pause-server
(def-icp-message-type-code end-simulation-initialization-vector-for-object 123 nil t) ; g2ds-resume-server
(def-icp-message-type-code begin-simulation-input-vector-for-object 124 nil t) ; g2ds-send-data-values-if-any
(def-icp-message-type-code simulation-keyword 125 nil t) ; g2ds-configure-variable
(def-icp-message-type-code simulation-input-value 126 nil t) ; g2ds-stop-collecting-values
(def-icp-message-type-code end-simulation-input-vector-for-object 127 nil t) ; g2ds-server-status
(def-icp-message-type-code shutdown-external-simulator 128)
(def-icp-message-type-code pause-external-simulator 129)
(def-icp-message-type-code resume-external-simulator 130)
(def-icp-message-type-code begin-simulation-output-vector-for-object 131)
(def-icp-message-type-code simulation-output-value 132)
(def-icp-message-type-code end-simulation-output-vector-for-object 133)
(def-icp-message-type-code initialize-external-simulator 134)
(def-icp-message-type-code end-simulation-input-for-cycle 135)
(def-icp-message-type-code end-simulation-output-for-cycle 136)
(def-icp-message-type-code connection-info 137)

  ;; The following codes are for icp message types for graphs
  ;; defined in WINDOWS3.  We are leaving Graphs-related codes
  ;; the range 150-179.

(def-icp-message-type-code begin-making-graph-rendering 150)
(def-icp-message-type-code add-from-graph-rendering-to-current-window 151)
(def-icp-message-type-code make-graph-rendering-structure-if-necessary 152)
(def-icp-message-type-code update-graph-dateline 153)
(def-icp-message-type-code update-graph-data-extrema 154)
;(def-icp-message-type-code set-current-graph-color-value 155)  ; obsolete
(def-icp-message-type-code set-plot-pattern-to-use 156)
(def-icp-message-type-code update-ring-raster-for-graph-given-color-values 157)
(def-icp-message-type-code prepare-for-painting-graph 158)
;(def-icp-message-type-code paint-graph-rectangle-on-all-rasters 159)  ; obsolete
;(def-icp-message-type-code delete-graph-rendering-for-image 160)  ; obsolete
;(def-icp-message-type-code delete-icon-rendering-for-image 161)  ; obsolete
(def-icp-message-type-code clear-data-clipping-rectangles 162)
(def-icp-message-type-code delete-icp-object-for-process 163 rpc)

  ;; Used in NUPEC.
(def-icp-message-type-code paint-marker-onto-graph-raster 164)
(def-icp-message-type-code paint-icon-onto-graph-raster 165)

  ;; The following codes are for icp message types for telewindows.
  ;; We are leaving Telewindows-related codes the range 180-199.  Note
  ;; that there are a bunch of Windows and Telewindows icp codes already
  ;; defined with lower code numbers.

;(def-icp-message-type-code request-to-note-workstation-in-g2-window 180)  ; obsolete
(def-icp-message-type-code message-group-id 181 i-am-alive)
  ;; Message-group-id is actually a message type for ICP in general, not just
  ;; for Telewindows (see I-am-alive mechanism).

  ;; Message 182 is part of the icp-window-protocol-supports-monochrome-raster-lists
  ;; version of the Telewindows protocol.  Added today.  (MHD 2/16/93)
(def-icp-message-type-code update-ring-raster-for-graph-given-color-values-2 182)


  ;; Support for image rendering on TeleWindows. -fmw, 1/11/94
(def-icp-message-type-code begin-making-image-data 183)
(def-icp-message-type-code image-data-chunk 184)
(def-icp-message-type-code paint-image-in-current-window 185)
(def-icp-message-type-code paint-image-in-current-scratchpad-raster 186)
(def-icp-message-type-code change-image-palette-of-window 187)


;; Support for new flush/sync graphics messages.
(def-icp-message-type-code force-graphics-on-window 188)
(def-icp-message-type-code ping-drawing 189)
(def-icp-message-type-code ping-drawing-reply 190)

;; more image rendering support

(def-icp-message-type-code paint-icon-background-image-in-current-window 191)
(def-icp-message-type-code set-graph-rendering-foreground-only-mode 192)
(def-icp-message-type-code paint-clearing-rectangle-in-current-scratchpad-raster 193)

;; native menus support.

(def-icp-message-type-code post-native-menu 194) ; -fmw, 1/15/02

;; native dialog support.

(def-icp-message-type-code simple-dialog 195) ; -mhd, 1/31/02


;; Native scrolling via the "TWPro tie entire G2 window to a workspace" hack.
;; These messages are sent from G2 to TW. -fmw, 2/19/02

(def-icp-message-type-code set-scroll-info 196)        ; Obsolete. -fmw, 12/4/03
(def-icp-message-type-code set-window-title 197)

  ;; The codes 200-209 are reserved for ICP message types for NUPEC.  These
  ;; codes are defined elsewhere in the NUPEC modules.  -jra 11/29/89

(def-icp-message-type-code define-color-map 210)

  ;; ICP messages which manage RPC-related objects reserve codes 220 through 229.
  ;; (jh, 3/6/90)

(def-icp-message-type-code define-remote-procedure-name 221 rpc)
(def-icp-message-type-code define-remote-procedure-identifier 222 rpc)
(def-icp-message-type-code initialize-server-g2ds-interface 223)

  ;; RPC-related ICP messages reserve codes 230 through 250.
  ;; (jh, 3/6/90)

(def-icp-message-type-code rpc-start               230 rpc)
(def-icp-message-type-code rpc-call                231 rpc)
(def-icp-message-type-code rpc-error               232 rpc)
(def-icp-message-type-code rpc-error-to-caller     233 rpc)
(def-icp-message-type-code rpc-continue-from-error 234 rpc) ;not yet implemented
(def-icp-message-type-code rpc-asynchronous-abort  235 rpc)
(def-icp-message-type-code rpc-synchronous-abort   236 rpc) ;not yet implemented
(def-icp-message-type-code rpc-return-values       237 rpc)
(def-icp-message-type-code rpc-suspend             238 rpc) ;not yet implemented
(def-icp-message-type-code rpc-resume              239 rpc) ;not yet implemented
(def-icp-message-type-code rpc-acknowledge-abort   240 rpc)

(def-icp-message-type-code start-icp-task                245 start-icp-task) ; special case
(def-icp-message-type-code resume-icp-task               246 resume-icp-task)

(def-icp-message-type-code resumable-rpc-start           247 rpc)
(def-icp-message-type-code resumable-rpc-call            248 rpc)
(def-icp-message-type-code resumable-rpc-return-values   249 rpc)

(def-icp-message-type-code abort-icp-task                250 icp)

  ;; The codes 251 - 270 are reserved for the SPEEDUP interface.  -agh 5/24/90

(def-icp-message-type-code speedup-begin-tagnames 251)
(def-icp-message-type-code speedup-input-or-output-tagnames 252)
(def-icp-message-type-code speedup-tagname 253)
(def-icp-message-type-code speedup-end-tagnames 254)
(def-icp-message-type-code speedup-begin-values 255)
(def-icp-message-type-code speedup-value 256)
(def-icp-message-type-code speedup-end-values 257)

(def-icp-message-type-code paint-from-line-of-text-to-current-scratchpad-raster 271)        ; MHD, 8/29/90

  ;; The codes 280 - 299 are reserved for the asynchronous file server.
  ;; jh, 10/30/90.

  ;; jh, per bah 10/30/90
(def-icp-message-type-code remote-eval      300)

(def-icp-message-type-code define-temporary-index-space  301 rpc)
(def-icp-message-type-code release-temporary-index-space 302 rpc)

  ;; ICP message type codes 305 through 309 are reserved for network security
  ;; purposes.

  ;; jh, 1/30/91.  For network security.
(def-icp-message-type-code connection-denied 305 icp)
(def-icp-message-type-code connection-shutdown-imminent 306 icp)
(def-icp-message-type-code no-license 307 icp)

  ;; ICP message type codes 310 through 319 are reserved for the foreign function
  ;; server.  jh, 6/17/91.

(def-icp-message-type-code request-foreign-function-registry   311)
(def-icp-message-type-code provide-foreign-function-registry   312)
(def-icp-message-type-code call-foreign-function               313)
(def-icp-message-type-code return-foreign-function-value       314)
(def-icp-message-type-code signal-foreign-function-error       315)
(def-icp-message-type-code kill-foreign-function-server        316)
(def-icp-message-type-code shut-down-foreign-server-context    317)

  ;; ICP message type codes 320 through 329 are reserved for the RPC
  ;; object-passing facility, defined in module RPC-COMMON2.  jh, 12/17/93.

(def-icp-message-type-code continue-building-resumable-object       320 rpc)
(def-icp-message-type-code update-object-passing-network-resources  321 rpc)
(def-icp-message-type-code register-corresponding-icp-object        322 rpc)
(def-icp-message-type-code deregister-corresponding-icp-object      323 rpc)
(def-icp-message-type-code deregister-original-icp-object           324 rpc)
(def-icp-message-type-code acknowledge-deregister-corresponding-icp-object 325 rpc)
(def-icp-message-type-code deregister-icp-objects                   326 rpc)

  ;; ncc 2/3/94, message type code 330 is being for GSI filtering mechanism
  ;; new message named modify-gsi-sensor-definition.


  ;; 330-333: New messages added for mouse control on a per-workstation basis:
  ;; (MHD 10/18/94)
(def-icp-message-type-code start-mouse-tracking-in-window 330)
(def-icp-message-type-code stop-mouse-tracking-in-window 331)
(def-icp-message-type-code set-position-of-mouse-in-window 332)
(def-icp-message-type-code shift-position-of-mouse-in-window 333)

  ;; 334: reroute-telewindow (not in protocol prior to today. (MHD 10/20/94))
(def-icp-message-type-code reroute-telewindow 334)

  ;; 335:
(def-icp-message-type-code set-window-license-level 335)

  ;; 336: shutdown acknowledgement in new (4.0) ICP base protocol. -ncc, 2 May 1995
(def-icp-message-type-code acknowledge-shutdown                       336 icp)

;; 337: Telewindows Setup Protocol -- new for 4.0 POST Beta II (i.e., for 4.0 final) (MHD 5/19/95)
(def-icp-message-type-code set-telewindows-connection-license-info 337)



(def-icp-message-type-code initialize-gsi-interface 338 gsi)

(def-icp-message-type-code return-initialize-gsi-interface-status 339 gsi)

;; 340-349 in use for DDE (see module DDE)


;; The gap 350-399 is for general use:


;; 350: Telewindows User Settings Saving Protocol -- new for 5.0 Post Alpha II
;; (i.e., for 5.0 Alpha III+) Note that the Telewindows protocol version named
;; icp-window-protocol-supports-saving-passwords corresponds to the addition of
;; this message type code.  (MHD 10/2/96)

(def-icp-message-type-code save-user-settings-for-telewindows 350)



(def-icp-message-type-code intern-list 351 rpc)
(def-icp-message-type-code define-resumable-remote-procedure-identifier 352 rpc)

(def-icp-message-type-code resumable-rpc-error           353 rpc)
(def-icp-message-type-code resumable-rpc-error-to-caller 354 rpc)

(def-icp-message-type-code create-item-reference 355 rpc)
;(def-icp-message-type-code delete-item-reference 356 rpc) ; not useful

(def-icp-message-type-code copy-text-string-to-cut-buffer 357)      ; ICP msg from G2
(def-icp-message-type-code paste-from-telewindows-to-g2 358)        ; ICP msg from TW
(def-icp-message-type-code request-paste-of-cut-buffer-text 359)    ; ICP msg from G2
(def-icp-message-type-code update-paste-availability-status 360)    ; ICP msg from TW
(def-icp-message-type-code enable-or-disable-clipboard-polling 361) ; ICP msg from G2
(def-icp-message-type-code request-paste-availability-status 362)   ; ICP msg from G2

(def-icp-message-type-code start-data-server      363 gsi-ds)
(def-icp-message-type-code reset-data-server      364 gsi-ds)


;; stipple-rectangle-in-current-scratchpad-raster
;; From G2 (6.0) to TW (6.0)

(def-icp-message-type-code stipple-rectangle-in-current-scratchpad-raster 365)


;; New line-drawing primitive for connections.

(def-icp-message-type-code add-wide-polyline-to-current-window 366)


;; New primitive to manage off-screen drawing.

(def-icp-message-type-code draw-offscreen 367)


;; New way for G2 to create Gensym (MDI Child) windows. (MHD 4/29/02)
;; Obsolete, but TW 7.0 can send us this message.

;; Only a G270/TW70 pair will ever exchange this message, so the code can be
;; reused if desired.

(def-icp-message-type-code launch-peer-window 368)


;; Access to native file open/save dialog, html help viewer, and web browser.

(def-icp-message-type-code file-dialog 369)
(def-icp-message-type-code html-help 370)


;; set-window-show-status shows an existing window in "TW Pro", and later will
;; do more tricks. (MHD 9/27/02)

;; Only a G270/TW70 pair will ever exchange these messages, so the codes can be
;; reused if desired. There are still no-op handlers in telestubs.

(def-icp-message-type-code set-window-show-status 371)
(def-icp-message-type-code show-window-with-geometry 372) ; (MHD 1/28/03)


  ;; Messages 400 thru 799 Version 5 Telewindows Protocol
  ;; These messages are defined in the VIEW-MSG Module.  (JED)


;; Native menu-bars -- will supplant the previous native menu messages. -fmw, 3/19/02

(def-icp-message-type-code nms-create-menu 500)
(def-icp-message-type-code nms-delete-menu 501)
(def-icp-message-type-code nms-append-menu-item 502)
(def-icp-message-type-code nms-set-menu-bar 503)
(def-icp-message-type-code nms-pop-up-menu 504)
(def-icp-message-type-code nms-check-menu-item 505)
(def-icp-message-type-code nms-check-radio-item 506)
(def-icp-message-type-code nms-enable-menu-item 507)
(def-icp-message-type-code nms-modify-menu-item 508)
(def-icp-message-type-code nms-dismiss 509)
(def-icp-message-type-code nms-reset 510)
(def-icp-message-type-code nms-append-special 511)
(def-icp-message-type-code nms-enable-items 512)
(def-icp-message-type-code nms-set-menu-flags 518)           ; Added for 7.1 -fmw, 6/23/03
(def-icp-message-type-code nms-set-iconsize 591)
  
;; Native printing

(def-icp-message-type-code native-printing-dialog 513)       ; Post dialog
(def-icp-message-type-code native-printing-control 514)             ; Various small fcns
(def-icp-message-type-code native-printing-start-page 515)
(def-icp-message-type-code paint-icon-in-current-window 516) ; New drawing message.
(def-icp-message-type-code paint-line-of-text-in-current-window 517) ; New drawing message.

;; Native icons

(def-icp-message-type-code manage-native-icons 519)

;; Native Progress Bar

(def-icp-message-type-code manage-progress-bar 520)

;; Uncomplicated modal native dialogs

(def-icp-message-type-code basic-dialog 521)

;; Manage a non-modal native control

(def-icp-message-type-code manage-native-control 522)

;; General purpose message to get TW out of all modal event loops.

(def-icp-message-type-code reset-native-controls 523)

;; Native Windows (new in 8.0)

(def-icp-message-type-code create-window 524)         ; G2->TW
(def-icp-message-type-code manage-window 525)
(def-icp-message-type-code redirect-window 526)
(def-icp-message-type-code stack-windows 527)
(def-icp-message-type-code scroll-window 528)
(def-icp-message-type-code manage-scrollbars 529)
(def-icp-message-type-code mega-refresh 530)
(def-icp-message-type-code tw-command 531)

;; Complicated modal or modeless native dialogs

(def-icp-message-type-code start-custom-dialog  532)
(def-icp-message-type-code add-dialog-component 533)
(def-icp-message-type-code show-custom-dialog   534)
(def-icp-message-type-code abort-custom-dialog  535)
(def-icp-message-type-code add-dialog-component-with-font 594)
(def-icp-message-type-code set-dialog-locked 592)
;; NMS controls

(def-icp-message-type-code nms-create-control 536)
(def-icp-message-type-code nms-append-control 537)
(def-icp-message-type-code nms-delete-control 538)

;; UI Themes

(def-icp-message-type-code nms-set-theme 539)

;; Native dialog updates

(def-icp-message-type-code start-dialog-update 540)
(def-icp-message-type-code dialog-component-update 541)
(def-icp-message-type-code end-dialog-update 542)
(def-icp-message-type-code abort-dialog-update 543)

;; Native dialog queries

(def-icp-message-type-code query-custom-dialog 544)

;; Gensym Network File System

(def-icp-message-type-code list-directory-response 545) ; G2->TW


;; Native dialog tabular-view specification

;; These are obsolete as of 8.3b0, but must be kept around as long
;; as TW can connect to G2 8.2 or earlier.
(def-icp-message-type-code start-add-tabular-view 546)
;; unused: (def-icp-message-type-code start-add-tabular-view-columns 547)
(def-icp-message-type-code add-tabular-view-column 548)
;; unused: (def-icp-message-type-code end-add-tabular-view-columns 549)
(def-icp-message-type-code start-add-tabular-view-row 550)
(def-icp-message-type-code add-tabular-view-cell 551)
(def-icp-message-type-code end-add-tabular-view-row 552)
;; unused: (def-icp-message-type-code end-add-grid 553)
(def-icp-message-type-code delete-tabular-view-row 554)
)

;; Consider having separate subtract versions of add message types, to save
;; transmission of subtract-instead? arguments.


;; Dialog queries

(def-icp-message-type-code start-dialog-query  555)
(def-icp-message-type-code add-to-dialog-query 556)
(def-icp-message-type-code finish-dialog-query 557)
(def-icp-message-type-code abort-dialog-query  558)


;; More tabular-view operations

(def-icp-message-type-code start-replace-tabular-view-row 559)
(def-icp-message-type-code replace-tabular-view-cell 560)
(def-icp-message-type-code end-replace-tabular-view-row 561)


;; NMS Controls (8.0r1)

(def-icp-message-type-code nms-modify-control 562)

;; Configurable status bar (8.0r1)

(def-icp-message-type-code manage-status-bar 563)


;; Extended file dialog (8.1a0)

(def-icp-message-type-code file-dialog-ex 564)

;; Tree Views (8.1a0)

(def-icp-message-type-code manage-tree-view 565)

;; unused: (def-icp-message-type-code tree-object-viewer-info 601)
;; unused: (def-icp-message-type-code remove-tree-nodes-range-for-genflex 602)

;; HTML Views (8.1a0)

(def-icp-message-type-code manage-html-view 566)

;; Debugger Dialog (8.1a0)

(def-icp-message-type-code debugger-dialog 567)
;; unused: (def-icp-message-type-code debug-info-for-genflex 595)
;; unused: (def-icp-message-type-code genflex-debugger-step 596)


;; Native Editor (8.1a0)

(def-icp-message-type-code manage-editor 568) ; G2->TW

;; Extended Native Printing (8.1b0)

(def-icp-message-type-code native-printing-ex 569)

;; Shortcut Bars (8.1b0)

(def-icp-message-type-code manage-shortcut-bar 570)

;; New drawing primitives for connection arrows (8.1b0)

(def-icp-message-type-code add-polygon-to-current-window 571)
(def-icp-message-type-code add-ellipse-to-current-window 572)

;; Chart Views (8.1b0)

(def-icp-message-type-code manage-chart-view 573)

;; Grid Views (8.1b0)

(def-icp-message-type-code manage-grid-view 574)

;; Tabular-view selected-rows (8.1r0)

(def-icp-message-type-code select-tabular-view-rows 575)

;; Extended show options for dialog panes (8.1r0)

(def-icp-message-type-code show-custom-dialog-ex 576)

;; Generic pane management.

(def-icp-message-type-code manage-pane 577)

;; Extended Simple Dialogs (8.1r1)

(def-icp-message-type-code simple-dialog-ex 578)

;; Extended Html Help (8.2r0)

(def-icp-message-type-code html-help-ex 579)

;; Manage global UI properties (8.2r0)

(def-icp-message-type-code manage-ui-properties 580)

;; Manage and post messages to native logbook/message board

(def-icp-message-type-code manage-logbook 581)

;; Sending grid-view data in smaller chunks (8.2r0)

(def-icp-message-type-code specify-grid-view-cells 582)

;; Tabbed MDI Mode (8.2r0)

(def-icp-message-type-code tabbed-mdi-mode 583)

;; Modal dialogs for Native Login/Change Password (8.2r0)

(def-icp-message-type-code manage-dialog 584)

;; Property Grid (8.2r1)

(def-icp-message-type-code manage-property-grid 585)

;; Extended Text Boxes (8.2r1)

(def-icp-message-type-code specify-text-box-extensions 586)

;; Flag bits for NMS controls (8.2r1)

(def-icp-message-type-code nms-append-control-ex 587)

;; Programmatically dismiss a custom dialog (8.3a0)

(def-icp-message-type-code accept-custom-dialog  588)

;; Choose directory dialog (8.3a0)

(def-icp-message-type-code choose-directory 589)

;; Tabular View (8.3a1)

(def-icp-message-type-code manage-tabular-view 590)

(def-icp-message-type-code print-native-window 593)  ; ICP msg from G2 to TW

(def-icp-message-type-code list-sys-drives-response 600) ; G2->TW

(def-icp-message-type-code set-custom-dialog-background 601)

;; Get grid-view scrollbar position (2017)

(def-icp-message-type-code manage-grid-view-get-value 602)

(def-icp-message-type-code manage-grid-view-get-value-reply 603)



;;; Declaration:     def-icp-message-type
;;;                       (icp-message-name icp-arg-specs
;;;                        &body icp-message-handler-body?)
;;; Type:            Lisp macro.
;;; Purpose:             Define a sender and handler for an ICP message.
;;; Arguments:             > icp-message-name is an unevaluated symbol naming the message.
;;;                  > icp-arg-specs describes the arguments to the message sender.
;;;                    The following grammar describes the layout of an arg spec:
;;;                      arg-spec = arg-type | (arg-type [var] [= default])
;;;                      arg-type = icp-value-type | icp-object-type
;;;                  > icp-message-handler-body?  is an implicit progn which is
;;;                    executed when the ICP message is received.  In this progn,
;;;                    the variables given by icp-arg-specs are bound to the values
;;;                    received for the ICP message.  The naming scheme is as
;;;                    follows: if the spec is a symbol which is an ICP object type,
;;;                    the name of that type becomes the name of the variable.  If
;;;                    the spec is a singleton list, the element in that list
;;;                    becomes the name of the variable.  Otherwise, the second
;;;                    symbol in the list ("var" in the grammar above) becomes the
;;;                    name of the variable.  If icp-message-handler-body?  is nil,
;;;                    no handler is defined.
;;; Return behavior: No useful value.
;;; Users:             Public ICP messages (INT1), GSI (module GSI-COMMON),
;;;                  Telewindows and G2 printing (WINDOWS1), G2 foreign functions
;;;                  (G2-FOREIGN), G2-to-G2 communication (G2DS, G2DS-NUPEC).
;;; Prerequisites:   def-icp-message-type-code must have been called for
;;;                  icp-message-name.  A def-icp-value or def-icp-object form must
;;;                  have been executed for any arg-type mentioned in icp-arg-specs.
;;; Side effects:    Defines two functions:
;;;                    SEND-ICP-<icp-message-name>, unconditionally.
;;;                    HANDLE-ICP-<icp-message-name>, if the first form in
;;;                      icp-message-handler-body?  is not :no-handler.
;;;                  Modifies icp-message-handler-array to contain the compiled
;;;                  function HANDLE-ICP-<icp-message-name> if it was defined.
;;; Non-local exits: Signals an error if no ICP message type code exists.
;;; Memory impact:   Compile-time consing only.

;;; Def-icp-message-type defines for icp-message-type, when appropriate, (1) an
;;; `ICP message sender', the name of which is constructed by prefixing
;;; icp-message-type with "SEND-ICP-", and/or (2) an `ICP message handler', the
;;; name of which is constructed by prefixing icp-message-type with
;;; "HANDLE-ICP-".  The icp-arg-specs are used for defining both the sender and
;;; handler; their format is as follows.
;;;
;;;    icp-arg-spec = icp-arg-type | (icp-arg-type [var] [= default-value-form])
;;;
;;;    icp-arg-type = icp-value-type | icp-object-type

;;; Declaration:     SEND-ICP-<icp-message-name> (&rest args)
;;; Type:             Lisp function.
;;; Purpose:         Send the ICP message icp-message-name.
;;; Arguments:       The arguments specified in the icp-arg-specs of the
;;;                  def-icp-message-type form that defined this function.
;;; Return behavior: No useful value.
;;; Users:             See def-icp-message-type.
;;; Prerequisites:   Defined by def-icp-message-type.
;;; Side effects:    Transmits the ICP message over the network.  Further side
;;;                  effects occur if some arguments are ICP objects which have no
;;;                  corresponding objects as yet.  See
;;;                  MAKE-CORRESPONDING-<icp-object-type> for details.
;;; Non-local exits: None.
;;; Memory impact:   Will allocate memory if some arguments are ICP objects which
;;;                  have no corresponding objects as yet.  See
;;;                  MAKE-CORRESPONDING-<icp-object-type> for details.

;;; An icp message sender is passed arguments as specified by icp-arg-specs.
;;; Each argument that is an icp object, as determined by the icp-arg-type in
;;; the arg spec, is converted into the appropriate icp object index for the
;;; corresponding object, where assignment of an index and the making of the
;;; corresponding object is done if necessary.  Then the message, with its
;;; arguments, is written.

;;; Declaration:     HANDLE-ICP-<icp-message-name> ()
;;; Type:             Lisp function.
;;; Purpose:             Receive the ICP message icp-message-name.
;;; Arguments:             None.
;;; Return behavior: No useful value.
;;; Users:             See def-icp-message-type.
;;; Prerequisites:   Defined by def-icp-message-type.
;;; Side effects:    Executes the icp-handler-body?  arg to the def-icp-message-type
;;;                  form which defined this function.  Inside icp-handler-body?
;;;                  the variables from the icp-arg-specs (another arg to
;;;                  def-icp-message-type) are bound to the ICP values or objects
;;;                  received from the message in the order that they occur in
;;;                  icp-arg-specs.
;;; Non-local exits: Depends on icp-handler-body?.
;;; Memory impact:   Depends on icp-handler-body?.  Also note that if an ICP
;;;                  value-reclaimer has been declared for one of the argument
;;;                  types, that argument will be reclaimed automatically.  See doc
;;;                  for the icp-value-reclaimer property, above.

;;; An icp message handler is defined only if icp-message-handler-body? is
;;; specified (is non-nil).  Such a handler is a function of no arguments that:
;;; (1) reads the arguments that are present, each according to its type, using
;;; the value of the default value form for absent arguments when such a form is
;;; specified; (2) serially binds variables to the argument values (or to nil
;;; where there is no argument and no default value form), where the variables
;;; are the icp arg type, or the "var" where specified; (3) evaluates
;;; icp-message-handler-body? within the bound variables context; and
;;; (4) automatically reclaims any of its args for which an icp value reclaimer
;;; has been declared.  Icp-message-handler-body? should not (normally) setq any
;;; of its args that might be automatically reclaimed.  The value produced by
;;; icp-message-handler-body? will be ignored.

;;; A code for icp-message-type, as well as any icp object types used in
;;; icp-arg-specs, must already be defined by def-icp-message-type-code (q.v.).

(defmacro def-icp-message-type
          (icp-message-type icp-arg-specs
           &body icp-message-handler-body?)
  (unless (and (gsi-eliminable-p)
               (memq icp-message-type icp-messages-of-no-use-to-gsi))
    (expand-definition-of-icp-message-type
      icp-message-type icp-arg-specs icp-message-handler-body? nil nil)))

;; If it continues to be the case that all arguments must be present, the
;; default-value-form facilities should be eliminated!

;; Consider having up to four boolean arguments represented in the first byte of
;; the message.

;; Sadly this expander won't handle declare forms correctly. - ben 2/21/94




;;; Def-icp-message-functions ...

;;; Declaration:     def-icp-message-functions
;;;                   (icp-message-type icp-arg-specs
;;;                        &body case-form-without-icp-case)
;;; Type:             Lisp macro.
;;; Purpose:         Defines a icp message type used in the G2 to Telewindows
;;;                  protocol.  It creates a sender and a handler.  The sender
;;;                  contains a dispatch to switch between local drawing, remote
;;;                  drawing, or printing.  For each of these message types there
;;;                  must be a printing handler defined in the module PRINTING.
;;;                  Presumably, this is a superset of def-icp-message-type.
;;; Arguments:       > icp-message-type ...
;;;                  > icp-arg-specs has the same layout as in def-icp-message-type.
;;;                  > case-form-without-icp-case is a case form into which a case
;;;                    clause to handle the non-printing situation is inserted at
;;;                    the beginning of the form.  This is so printing can divert
;;;                    Telewindows output for its own use.
;;; Return behavior: No useful value.
;;; Users:           Telewindows and G2 printing (WINDOWS1, WINDOWS2, WINDOWS3,
;;;                  FONTS).
;;; Prerequisites:   def-icp-message-type-code must have been called for
;;;                  icp-message-name.  A def-icp-value or def-icp-object form must
;;;                  have been executed for any arg-type mentioned in icp-arg-specs.
;;; Side effects:    Defines a sender function named icp-message-type, and a handler
;;;                  function named HANDLE-ICP-<icp-message-type>.  Modifies
;;;                  icp-printing-message-handler-array to hold the handler
;;;                  function.  The sender function dispatches on special variables
;;;                  to perform normal Telewindows actions or divert the message to
;;;                  the printer.
;;; Non-local exits: None.
;;; Memory impact:   Compile-time consing only.

;;; Note that the case-form-without-icp-case is really a list of a single
;;; case-form element.

(defmacro def-icp-message-functions
          (icp-message-type icp-arg-specs &body case-form-without-icp-case)
  (expand-definition-of-icp-message-type
    icp-message-type icp-arg-specs nil t case-form-without-icp-case))





;;;; Macroexpansion for ICP Message Definers

(defun-for-macro parse-icp-arg-specs (icp-arg-specs)
 (loop for icp-arg-spec in icp-arg-specs
       collect
         (if (atom icp-arg-spec)
             icp-arg-spec
             (if (and (cdr icp-arg-spec)
                      (not (eq (cadr icp-arg-spec) '=)))
                 (cadr icp-arg-spec)
                 (car icp-arg-spec)))
         into arg-variables
       collect
         (loop as icp-arg-type
                  = (if (atom icp-arg-spec)
                        icp-arg-spec
                        (car icp-arg-spec))
                  then equivalent-icp-value-type?
               as equivalent-icp-value-type?
                  = (equivalent-icp-value-type icp-arg-type)
               while equivalent-icp-value-type?
               finally
                 (return icp-arg-type))
         into icp-arg-types
       finally
         (return (values arg-variables icp-arg-types))))

(defun-for-macro expander-for-recording-icp-message-signature
                 (icp-message-type icp-arg-specs arg-variables icp-arg-types)
  (when (eval-feature :development)
    `(setf (icp-message-signature ',icp-message-type)
           ',(loop for arg-name in arg-variables
                   as arg-specified-type in
                      (loop for icp-arg-spec in icp-arg-specs
                            collect (if (atom icp-arg-spec)
                                        icp-arg-spec
                                        (car icp-arg-spec)))
                   as arg-implementation-type in icp-arg-types
                   collect
                     (list arg-name
                           arg-specified-type
                           arg-implementation-type)))))



;;; ICP Message Sender Macroexpanders

(defun-for-macro get-corresponding-object-creating-forms
                 (arg-variables icp-arg-types)
  (loop for arg-variable in arg-variables
        as icp-arg-type in icp-arg-types
        as access-form-for-corresponding-icp-object-map?
           = (access-form-for-corresponding-icp-object-map icp-arg-type)
        when access-form-for-corresponding-icp-object-map?
          collect
            `(setq ,arg-variable ;note that this changes arg-variable
                   (or (getfq ,(if (eq arg-variable icp-arg-type)
                                   access-form-for-corresponding-icp-object-map?
                                   (substitute-args
                                     access-form-for-corresponding-icp-object-map?
                                     (list icp-arg-type)
                                     (list arg-variable)
                                     nil))
                              current-icp-port)
                     (resumable-icp-form
                       (,(intern (format nil "MAKE-CORRESPONDING-ICP-~A"
                                         icp-arg-type))
                         ,arg-variable))))))

(defun-for-macro get-icp-arg-writing-forms
                 (arg-variables icp-arg-types)
  (loop for arg-variable in arg-variables
        as icp-arg-type in icp-arg-types
        as object-p = (access-form-for-corresponding-icp-object-map icp-arg-type)
        collect
        (if object-p
            `(tracing-icp-writes (,arg-variable "[object arg]" argument
                                                (trace-write-icp-message-arguments-p))
               (resumable-icp-form
                 (write-icp-corresponding-object-index ,arg-variable)))
            `(tracing-icp-writes (,arg-variable "[value arg]" argument
                                                (trace-write-icp-message-arguments-p))
               (resumable-icp-form
                 (,(get-icp-value-writer-name icp-arg-type)
                   ,arg-variable))))))





;;; Note that when an ICP message function is used, the handler calls the sender
;;; directly.  That way we can use the same code whether the window is local or
;;; remote, simply by passing it a set of arguments obtained locally, or a set
;;; obtained via ICP.  The shared code is the body of the sender function.

(defun-for-macro expander-for-icp-message-functions-sender
    (message-function-sender-name ;same as icp-message-type
      icp-message-type-code
      arg-variables
      icp-arg-types
      case-form-without-icp-case)
  (let* ((data-service-i-am-alive-message-p
           (not (null (memq message-function-sender-name data-service-i-am-alive-messages))))
         (non-resumable-p (memq message-function-sender-name non-resumable-icp-message-types))
         (defun (if non-resumable-p
                    'defun-void
                    'defun-void-resumable-icp-function))
         (extracted-case-form (car case-form-without-icp-case)))
    (when (or (atom extracted-case-form) ;Gensym implementor's error
              (not (eq (car extracted-case-form) 'case)))
      (error "Need to define ~A as a case form"
             message-function-sender-name))
    `(progn
       (setf (aref icp-printing-message-handler-array ,icp-message-type-code)
             ',(intern (format nil "HANDLER-FOR-PRINTING-~A"
                               message-function-sender-name)))
       (,defun ,message-function-sender-name ,arg-variables
         ;; ajs (4/19/96) Added with-backtrace-for-internal-error
         (with-backtrace-for-internal-error ',message-function-sender-name
           (case ,(cadr extracted-case-form)
             (icp
              (icp-message-functions-icp-prologue ',message-function-sender-name)
              ,@(get-corresponding-object-creating-forms arg-variables icp-arg-types)
              #+development
              (trace-icp-message 'send ',message-function-sender-name ,@arg-variables)
              (resumable-icp-form (start-writing-icp-message ,icp-message-type-code))
              (tracing-icp-writes (,message-function-sender-name "[message]" message
                                   (trace-write-icp-messages-p ,data-service-i-am-alive-message-p))
                ,@(get-icp-arg-writing-forms arg-variables icp-arg-types)))
             (printer
              (non-resumable-icp-form
                (funcall (aref icp-printing-message-handler-array ,icp-message-type-code)
                         ,@arg-variables)))
             ,@(loop for (keys . forms) in (cddr extracted-case-form)
                     collect `(,keys
                               (non-resumable-icp-form
                                 (progn ,@forms))))))))))



(defun-for-macro expander-for-icp-message-sender
                 (icp-message-type
                  icp-message-type-code
                  arg-variables
                  icp-arg-types)
  (let* ((data-service-i-am-alive-message-p
           (not (null (memq icp-message-type data-service-i-am-alive-messages))))
         (non-resumable-p (memq icp-message-type non-resumable-icp-message-types))
         (defun (if non-resumable-p
                    'defun-void
                    'defun-void-resumable-icp-function))
         (name-of-main-sender
           (intern (format nil "SEND-ICP-~A" icp-message-type))))
    `(,defun ,name-of-main-sender ,arg-variables
       ;; ajs (4/19/96) Added with-backtrace-for-internal-error
       (with-backtrace-for-internal-error ',name-of-main-sender
         ,@(get-corresponding-object-creating-forms
             arg-variables icp-arg-types)
         #+development (trace-icp-message 'send ',icp-message-type ,@arg-variables)
         (resumable-icp-form (start-writing-icp-message ,icp-message-type-code))
         (tracing-icp-writes (,icp-message-type "[message]" message
                              (trace-write-icp-messages-p ,data-service-i-am-alive-message-p))
           ,@(get-icp-arg-writing-forms arg-variables icp-arg-types))))))



;;; ICP Message Handler Macroexpanders

(defun-for-macro get-icp-arg-reader-for-corresponding-object
    (name-of-corresponding-icp-object-index-space?)
  (cond ((not (eq 'item-index-space
                  name-of-corresponding-icp-object-index-space?))
         `(let ((index (resumable-icp-form (read-icp-corresponding-object-index))))
            (get-object-from-index-space-if-valid
              ,(case name-of-corresponding-icp-object-index-space?
                 (standard-icp-object-index-space
                  `(or current-temporary-icp-object-index-space
                       current-standard-icp-object-index-space)))
              index)))
        (t
         `(let ((index (resumable-icp-form (read-icp-corresponding-object-index)))
                (tmp-index-space current-temporary-icp-object-index-space))
            (if tmp-index-space
                (get-object-from-index-space tmp-index-space index)
                (case (index-space-name-for-item-index-space-for-icp-socket
                        current-icp-socket 'input)
                  (standard-icp-object-index-space
                   (get-object-from-index-space
                     current-standard-icp-object-index-space
                     index))
                  (item-index-space
                   (get-object-from-index-space
                     (item-index-space current-icp-port)))
                  (frame-serial-number
                   (lookup-item-from-frame-serial-number-table-of-port
                     index
                     current-icp-port))))))))

(defun-for-macro get-icp-arg-reader
                 (arg-variable icp-arg-type icp-read-trace-p)
  (let ((name-of-corresponding-icp-object-index-space?
          (name-of-corresponding-icp-object-index-space icp-arg-type)))
    (if name-of-corresponding-icp-object-index-space?
        `(tracing-icp-reads (,arg-variable "[object arg]" argument
                             ,icp-read-trace-p t)
           ,(get-icp-arg-reader-for-corresponding-object
              name-of-corresponding-icp-object-index-space?))
        `(tracing-icp-reads (,arg-variable "[value arg]" argument
                             ,icp-read-trace-p t)
           (resumable-icp-form
             (,(get-icp-value-reader-name icp-arg-type)))))))


(defun-for-macro get-arg-reclaiming-forms-for-icp-message-handler
                 (arg-variables icp-arg-types)
  (loop for arg-variable in arg-variables
        as icp-arg-type in icp-arg-types
        as icp-value-reclaimer?
           = (icp-value-reclaimer icp-arg-type)
        when icp-value-reclaimer?
          collect `(,icp-value-reclaimer? ,arg-variable)))




#+development
(defvar trace-icp-messages nil)

#+development
(defun trace-icp-messages ()
  (setq trace-icp-messages t))

#+development
(defun untrace-icp-messages ()
  (setq trace-icp-messages nil))

#+development
(defmacro trace-icp-message (direction name &rest arguments)
  `(when trace-icp-messages
     (trace-icp-message-1 ,direction ,name ,@arguments)))

#+development
(defvar last-trace-time 0)

#+development
(defun time-since-last-call ()
  (let ((time (get-fixnum-time)))
    (prog1
        (- time last-trace-time)
      (setq last-trace-time time))))


;;; The function `trace-time' annotates the info with the time since the last
;;; printout.

#+development
(defun trace-time (fmt &rest args)
  (format t "~4d " (time-since-last-call))
  (apply (lisp-format) t fmt args)
  (terpri))

#+development
(defun trace-icp-message-1 (direction name &rest arguments)
  (when (or (eq trace-icp-messages t)
            (eq trace-icp-messages 'handler)
            (and (consp trace-icp-messages)
                 (memq name trace-icp-messages)))
    (let ((*print-length* 3))
      (format t "~&~4d ~a: ~s ~{~s~^ ~}~%"
              (time-since-last-call)
              (case direction (receive "Rcv") (t "Send"))
              name
              (loop for argument in arguments
                    collect (if (and (text-string-p argument)
                                     (> (lengthw argument) 30))
                                (format nil "...")
                                argument))))))

(defun-for-macro merge-ignored-args-into-doc-and-decl-forms
    (ignored-args? doc-and-decl-forms)
  (loop with merged-doc-and-decl-forms = nil
        for doc-or-decl-form in doc-and-decl-forms
        with ignore-encountered-p = nil
        do
    (cond
      ((and (consp doc-or-decl-form)
            (eq (car doc-or-decl-form) 'declare))
       (let ((declaration-body (second doc-or-decl-form)))
         (cond
           ((and (consp declaration-body)
                 (eq (second declaration-body) 'ignore)
                 (not ignore-encountered-p))
            (setq ignore-encountered-p t)
            (push `(declare
                     (ignore
                       ,@(remove-duplicates
                           (append (cdr declaration-body) ignored-args?))))
                  merged-doc-and-decl-forms))
           (t (push doc-or-decl-form merged-doc-and-decl-forms)))))
      (t (push doc-or-decl-form merged-doc-and-decl-forms)))
        finally
          (when (and ignored-args? (not ignore-encountered-p))
            (push `(declare (ignore ,@ignored-args?))
                  merged-doc-and-decl-forms))
          (return (reverse merged-doc-and-decl-forms))))


(defun-for-macro get-icp-message-handler-name (icp-message-type)
  (intern (format nil "HANDLE-ICP-~A" icp-message-type)))

(defun-for-macro expander-for-icp-message-handler-1
    (icp-message-type
      icp-message-type-code
      icp-arg-specs
      arg-variables
      icp-arg-types
      icp-message-handler-body?
      message-functions-variety-p)
  (let ((handler-name
          (get-icp-message-handler-name icp-message-type))
        (arg-making-forms
          (loop for icp-arg-type in icp-arg-types
                for arg-variable in arg-variables
                as icp-arg-reader
                   = (get-icp-arg-reader
                       arg-variable
                       icp-arg-type
                       '(trace-read-icp-message-arguments-p))
                as icp-arg-spec in icp-arg-specs
                as default-value-form?
                   = (if (not (atom icp-arg-spec))
                         (cadr (memq '= (cdr icp-arg-spec))))
                collect
                (if default-value-form?
                    `(or ,icp-arg-reader ,default-value-form?)
                    icp-arg-reader)))
        (arg-reclaiming-forms?
          (get-arg-reclaiming-forms-for-icp-message-handler
            arg-variables icp-arg-types)))
    (if message-functions-variety-p
        (expander-for-icp-message-functions-handler
          handler-name icp-message-type icp-message-type-code arg-variables
          icp-arg-types arg-making-forms arg-reclaiming-forms?
          icp-message-type)
        (expander-for-icp-message-handler
          handler-name icp-message-type icp-message-type-code arg-variables
          icp-arg-types arg-making-forms arg-reclaiming-forms?
          icp-message-handler-body?))))

(defun-for-macro expander-for-icp-message-handler
                 (handler-name
                   icp-message-type
                   icp-message-type-code
                   arg-variables
                   icp-arg-types
                   arg-making-forms
                   arg-reclaiming-forms
                   icp-message-handler-body?)
  (declare (ignore icp-arg-types))
  (unless (eq (car icp-message-handler-body?) ':no-handler)
    (multiple-value-bind (doc-and-decl-forms body-after-doc-and-decl?)
        (split-defun-body icp-message-handler-body?)
      `(progn
         ,(if (not body-after-doc-and-decl?)
              `(defun-void ,handler-name ()
                 ,@doc-and-decl-forms
                 (error "ICP did not expect to handle message ~a, code ~a"
                        ',icp-message-type
                        ,icp-message-type-code))
              (let* ((data-service-i-am-alive-message-p
                       (not (null (memq icp-message-type data-service-i-am-alive-messages))))
                     (non-resumable-p (memq icp-message-type non-resumable-icp-message-types))
                     (defun (if non-resumable-p
                                'defun-void
                                'defun-void-resumable-icp-function))
                     (handler-body-name (intern (format nil "~A--BODY" handler-name)))
                     (handler-body-call `(,handler-body-name ,@arg-variables)))
                `(progn
                   (defun-void ,handler-body-name (,@arg-variables)
                     ,@doc-and-decl-forms
                     ,@body-after-doc-and-decl?)
                   (,defun ,handler-name ()
                     (tracing-icp-reads (,icp-message-type "[message]" message
                                         (trace-read-icp-messages-p ,data-service-i-am-alive-message-p)
                                         nil t)
                       (let* (,@(loop for arg-variable in arg-variables
                                      for arg-making-form in arg-making-forms
                                      collect `(,arg-variable ,arg-making-form)))
                         ,(if non-resumable-p
                              `(non-resumable-icp-form
                                 ,handler-body-call)
                              `(non-resumable-icp-form
                                 (let ((abort-for-icp-catcher? nil))
                                   ,handler-body-call)))
                         ,@arg-reclaiming-forms))))))

         (add-icp-message-handler ',handler-name ,icp-message-type-code)))))

(defun add-icp-message-handler (handler-name icp-message-type-code)
  #+development
  (check-for-message-type-code-clobbering handler-name icp-message-type-code)
  (setf (svref icp-message-handler-name-array icp-message-type-code)
        handler-name)
  (setf (svref icp-message-handler-array icp-message-type-code)
        #+development
        handler-name
        #-development
        (symbol-function handler-name))
  handler-name)


;;; Note that when an ICP message function is used, the handler calls the sender
;;; directly.  That way we can use the same code whether the window is local or
;;; remote, simply by passing it a set of arguments obtained locally, or a set
;;; obtained via ICP.  The shared code is the body of the sender function.

;; jh, 3/3/93.  Each ICP message function handler now has an extra null
;; test due to ICP tracing.


(defun-for-macro expander-for-icp-message-functions-handler
                 (handler-name
                   icp-message-type
                   icp-message-type-code
                   arg-variables
                   icp-arg-types
                   arg-making-forms
                   arg-reclaiming-forms?
                   message-function-sender-name) ;same as icp-message-type
  (declare (ignore icp-arg-types))
  (let* ((data-service-i-am-alive-message-p
           (not (null (memq icp-message-type data-service-i-am-alive-messages))))
         (non-resumable-p (memq icp-message-type non-resumable-icp-message-types))
         (defun (if non-resumable-p
                    'defun-void
                    'defun-void-resumable-icp-function)))
    `(progn
       (,defun ,handler-name ()
         (tracing-icp-reads (,icp-message-type "[msg funct]" message
                             (trace-read-icp-messages-p ,data-service-i-am-alive-message-p)
                             nil t)
           (let* (,@(loop for arg-variable in arg-variables
                          for arg-making-form in arg-making-forms
                          collect `(,arg-variable ,arg-making-form)))
             (non-resumable-icp-form
               (,message-function-sender-name ,@arg-variables))
             ,@arg-reclaiming-forms?)))

       (add-icp-message-handler ',handler-name ,icp-message-type-code))))

;; jh, 3/3/93.  We now install a dummy handler when no handler body is
;; specified to def-icp-message-type.  This will help us catch errors
;; where sender and receiver are reversed.

;; jh, 3/3/93.  Each ICP message handler now has an extra null test due
;; to ICP tracing.


(defun-for-macro expand-definition-of-icp-message-type
    (icp-message-type
      icp-arg-specs
      icp-message-handler-body?
      message-functions-variety-p
      case-form-without-icp-case?)
  (let ((icp-message-type-code?
          (icp-message-type-code icp-message-type)))
    (unless icp-message-type-code? ;Gensym implementor's error
      (error "No code for ICP message type ~A" icp-message-type))
    (multiple-value-bind (arg-variables icp-arg-types)
        (parse-icp-arg-specs icp-arg-specs)
      `(progn

         ;; Record on the icp-message-signature global property, when in
         ;; development, declarative info about each flavor of ICP message.
         ,(expander-for-recording-icp-message-signature
            icp-message-type
            icp-arg-specs
            arg-variables
            icp-arg-types)

         ;; Define ICP message sender.  This contains tracable (slower) and
         ;; non-tracable branches.  Care has been taken to minimize the time it
         ;; takes to reach the non-traced branch.
         ;;
         ;; The following form defines an ICP message sender that has a
         ;; different name depending on the switch message-functions-variety-p.
         ;; If this switch is nil, the sender's name is
         ;; SEND-ICP-<icp-message-type>.  If non-nil, the sender's name is the
         ;; same as icp-message-type.
         ,(if message-functions-variety-p
              (expander-for-icp-message-functions-sender
                icp-message-type
                icp-message-type-code?
                arg-variables
                icp-arg-types
                case-form-without-icp-case?)
              (expander-for-icp-message-sender
                icp-message-type
                icp-message-type-code?
                arg-variables
                icp-arg-types))

         ;; Define ICP message handler with both tracable (slower) and
         ;; non-tracable (faster) branches.
         ,(expander-for-icp-message-handler-1
            icp-message-type
            icp-message-type-code?
            icp-arg-specs
            arg-variables
            icp-arg-types
            icp-message-handler-body?
            message-functions-variety-p)

         ;; Do the traditional thing with a top-level defining form.
         ,(unless (eval-feature :chestnut-trans)
            `',icp-message-type)))))




;; Senders now write all arguments.  Consider implementing a mechanism to
;; support the omission of default-valued arguments at the end of a message.
;; Alternatively, consider eliminating default values (i.e., optional
;; arguments), since they do not seem to be very useful.

;; Icp message and object type definitions should be compilable only for one end
;; or the other of an icp connection, e.g., there should be a way to keep an icp
;; message sender from being defined where it is not needed!

;; Should there be code in the handler to check that icp object indices are
;; valid?  Or do we trust things higher up?

;; Added experimental case for calling a printing function this day (12/28/90 - ben).

;; ICP message definition now stores the compiled function itself in
;; icp-message-handler-array.  This keeps these symbols out of the runtime
;; Chestnut symbol table, which is of limited size.  Also removed the call to
;; check-for-message-type-code-clobbering, since this check always fails (two
;; compiled functions are never eq).  jh, 2/21/91.




;;; Check-for-message-type-code-clobbering checks if icp-message-type-code has
;;; already been associated with a handler name different from handler-name, and
;;; if it has, it signals a continuable error with a message saying that it is
;;; about to be reassigned to handler-name.

#+development
(defun-void check-for-message-type-code-clobbering
            (handler-name icp-message-type-code)
  (let ((previously-assigned-handler-name?
          (svref icp-message-handler-name-array icp-message-type-code)))
    (when previously-assigned-handler-name?
      (unless (eq previously-assigned-handler-name? handler-name)
        (cerror "Continue with the reassignment."
                "ICP Message Type Code ~d~%~
                 is about to be reassigned to ~a.~%~
                 It was previously assigned to ~a."
                icp-message-type-code
                handler-name
                previously-assigned-handler-name?)))))

;; Made a function to pull the code out of the expansion of the macro above.
;; (MHD 11/5/90)

;; Check-for-message-type-code-clobbering is no longer useful, since we use actual
;; compiled functions in icp-message-handler-array rather than their names.  This
;; function was never much use anyway, since it failed to warn us when GSPAN and
;; G2ds were using the same messages and one of the colliding message definitions
;; didn't specify a handler.  jh, 2/21/91.

;; jh, 3/2/93.  Put check-for-message-type-code-clobbering back in,
;; since we now have access to the name of the ICP message as part of
;; the ICP tracing project.






;;; Declare-ignorable-icp-argument ...


(defmacro declare-ignorable-icp-argument (name)
  name)

(defmacro declare-ignorable-icp-arguments (&rest names)
  `(progn ,@names))

;; Added declare-ignorable-icp-argument for those arguments we want to read from
;; ICP, but subsequently ignore.  For truly fussy compilers, the implementation of
;; this construct might have to be more complex than simply mentioning the
;; argument name.  (jh, 10/3/90)






;;;; ICP Sockets

;;; Declaration:     active-icp-sockets
;;; Type:             G2 system variable.
;;; Purpose:             Hold a list of currently active ICP sockets.
;;; Value:           an icp-list of icp-sockets.
;;; Return behavior: N/A.
;;; Users:           ICP internals:
;;;                    INT1: add-to-active-icp-sockets
;;;                    INT2: service-icp-sockets-awaiting-callback
;;;                          process-icp-sockets
;;;                          restore-icp-index-to-original-state
;;;                    INT3: warn-disallowed-icp-listener-connections
;;;                    INT4: transmit-localnet-buffer
;;;                          purge-inactive-icp-sockets
;;;                  Also G2 foreign functions (G2-FOREIGN), Telewindows (CONTROLS).
;;; Prerequisites:   Must be referenced inside the scope of with-system-variables.
;;; Side effects:    N/A.
;;; Non-local exits: N/A.
;;; Memory impact:   This is a list of icp-conses which grows and shrinks as ICP
;;;                  connections are made and broken.  It is the responsibility of
;;;                  the users of this variable to reclaim the extra gensym-conses
;;;                  as needed.  Note that ICP is in transition from using generic
;;;                  gensym-conses to using specific icp-conses.  Until the
;;;                  transition is complete, there is a chance of leaks between
;;;                  these two cons pools.  There is also an internal memory

;;; Active-icp-sockets holds a list of active icp sockets (in this system
;;; process).  These sockets should be serviced either periodically or upon
;;; `callback' (system process interrupt).

(defvar active-icp-sockets nil)


;; This should become a macro soon, for efficiency's sake.  jh, 2/21/91.
(defun add-to-active-icp-sockets (icp-socket)
  (icp-push icp-socket active-icp-sockets))



;;; An `ICP socket' ...

;;; Declaration:     icp-socket
;;; Type:             G2 def-structure.
;;; Purpose:             Maintain information about an ICP connection.
;;; Slots:           > type-of-icp-connection is one of the following symbols:
;;;                    > generic : any ICP connection in a distribution image
;;;                    > self : (not used)
;;;                    > localnet :  G2-to-G2 connection to this G2 iteself
;;;                  > icp-connection-name is a network pathname string naming the
;;;                    remote host, address, and transport type.  If the socket has
;;;                    not yet attempted to connect, this slot is nil.
;;;                  > icp-input-port is an icp-port structure or nil.
;;;                  > icp-output-port is an icp-port structure or nil.
;;;                  > icp-connection-open-p is t or nil.  This is set when the
;;;                    socket first attempts to connect and cleared by
;;;                    shutdown-icp-socket-connection.  Note that a true value may
;;;                    not be accurate between the time that the socket structure is
;;;                    created and when the actual network connection is made.
;;;                  > connection-loss is a symbol naming a funcallable
;;;                    function of two arguments, to be invoked whenever an ICP
;;;                    connection is closed or broken.  The first argument is
;;;                    the icp socket structure whose connection was lost, and
;;;                    the second is a boolean value which if nonnil indicates
;;;                    that the connection was broken rather than closed.
;;;                         >***NOTE that this was a list of symbols naming
;;;                         functions ..., prior to 5.0  -ncc, 18 Mar 1996
;;;                  > XXX document other new callback slots.
;;;                  > icp-connection-being-shutdown?  is t or nil.  This slot is
;;;                    set by flush-and-shutdown-icp-socket to prevent subsequent
;;;                    ICP transmission through this socket.  It is cleared by
;;;                    process-icp-sockets after the socket is shut down.
;;;                  > I-am-alive-info? is an I-am-alive structure or nil.
;;;                  > enclosing-interface-frame?  is an object with
;;;                    GSI-interface-configuration capability or nil.  The purpose
;;;                    of this slot is to allow proper reclamation of text sent
;;;                    through GSI and G2-to-G2 message service.
;;;                  > icp-socket-listener-client? is non-nil if this socket was
;;;                    created in response to a request-from a client. Currently
;;;                    (jh, 5/20/95) possible clients are G2, TELEWINDOWS, or T
;;;                    (meaning that the client is not yet known).
;;;                  > icp-connection-refused-p is non-nil if this is a listener
;;;                    socket and it has refused to accept a connnection (typically
;;;                    for security reasons).  Otherwise, this slot is nil.
;;;                  > icp-socket-shutdown-timer is a fixnum which counts the time
;;;                    until shutdown of a connection which has been refused.  (The
;;;                    connection is maintained temporarily until the refusing
;;;                    listener can notify the requestor of the reason for the
;;;                    shutdown.) If this socket is not a listener, this slot is
;;;                    nil.
;;;                  > reason-for-shutdown?  is one of the following symbols:
;;;                    > broken-while-receiving: happens in
;;;                      service-icp-sockets-awaiting-callback when a call to
;;;                      network-read or similar function gets an error.
;;;                    > broken-while-transmitting: happens in transmit-icp-buffer
;;;                      when call to c-network-write call or similar function gets
;;;                      an error.
;;;                    > protocol-out-of-synch-1: happens when
;;;                      enqueue-next-icp-buffer-if-any cannot read an ICP byte
;;;                      using get-icp-byte even though it is in the middle of
;;;                      reading an ICP message group and there previously appeared
;;;                      to be bytes to read.  (Note that get-icp-byte does not
;;;                      advance the pointer in an ICP buffer.)
;;;                    > protocol-out-of-synch-2: happens when
;;;                      enqueue-next-icp-buffer-if-any expects that the next ICP
;;;                      byte will be an ICP message type code (offset by
;;;                      icp-message-type-code-offset) but instead it is out of
;;;                      range.  (Note that get-icp-byte does not advance the
;;;                      pointer in an ICP buffer.)
;;;                    > protocol-out-of-synch-3: happens when the first byte read
;;;                      by handle-icp-messages using read-icp-byte-if-any is out of
;;;                      range for an ICP message type code plus
;;;                      icp-message-type-code-offset.  (Note that
;;;                      read-icp-byte-if-any can advance the pointer in an ICP
;;;                      buffer).
;;;                    > protocol-out-of-synch-4: happens when
;;;                      advance-and-read-icp-byte-if-any fails to get a buffer to
;;;                      read from current-icp-port.
;;;                    > protocol-out-of-synch-5: happens when
;;;                      advance-and-read-icp-byte-if-any has an ok-if-none?  arg of
;;;                      nil, is in the middle of reading an ICP message group, and
;;;                      the ICP byte read by get-icp-byte indicates that there are
;;;                      no more ICP bytes left in that message group.
;;;                    > unknown-message: handle-icp-messages could not find a
;;;                      handler for an ICP message with the message code received.
;;; Return behavior: No useful value.
;;; Users:             Telewindows (module TELEWINDOWS) and ICP internals.
;;; Prerequisites:   The macro def-structure must be defined.
;;; Side effects:    Defines a constructor macro make-icp-socket-structure, which
;;;                  takes three arguments: type-of-icp-connection,
;;;                  icp-connection-name, and icp-connection-open-p.  This
;;;                  constructor is internal to the ICP facility and should not be
;;;                  used elsewhere.  Defines a predicate icp-socket-p.
;;; Non-local exits: None.
;;; Memory impact:   Compile-time consing only.
;;; Notes:           The public interface to icp-sockets is through the special
;;;                  binding of the system variable current-icp-socket.

(eval-when (:compile-toplevel :load-toplevel :execute)
  (defconstant gsi-undefined-context -1)
  (defconstant gsi-uninitialized-context -2))

(defvar maximum-object-passing-bandwidth 8192)


;; Timeout on connection shutdown.  If peer does not respond in at least this many seconds,
;; shut down this end of the connection with an apropos warning message.
(eval-when (:compile-toplevel :load-toplevel :execute)
(defparameter icp-socket-shutdown-handshake-timeout 15)) ; wait 15s for shutdown ack.

(defvar icp-socket-connect-negotiation-timeout-default (*f 60 fixnum-time-units-per-second)) ;default value.

;; State machine info for icp sockets (icp-connection-state).  any transitions
;; not explicitly described are errors.  The error transition is to the closed
;; state.  The error action is the posting of an apropriate error message to the
;; logbook.  -ncc, 4 Apr 1995

(eval-when (:compile-toplevel :load-toplevel :execute)

;; sockets that are in this state are not in use by any ICP clients.
;; cannot read or write socket in this state.
;; cannot process messages in this state.
(defparameter icp-connection-closed                                  0) ; -> {running,
                                ;     connect-in-progress}

;; state in which connect is in progress, no IO ops possible.
;; running down a timer at expiry of which we'll give up on this cnxn.
;; expecting an event notification for connect completion or timeout.
(defparameter icp-connection-connect-in-progress                     1) ; -> {running,
                                        ;     closed}

;;when a connection is completed this state is entered: a shutdown request or a
;;local shutdown triggers the obvious transition.

;;can read and write socket in this state.
;;can of course process messages in this state.
(defparameter icp-connection-running                                 2) ; -> {rundown,
                                        ;     shutdown-awaiting-acknowledgement}

;; Have sent the acknowledgement, but possibly couldn't flush it out to the
;; transport layer.

;; cannot read or write socket in this state; must continue to
;; flush buffered output, however.
;; cannot process queued messages in this state (there should not be any, either!)
(defparameter icp-connection-shutdown-acknowledgement-rundown        4) ; -> {closed}    Times out after
                                        ; icp-socket-shutdown-handshake-timeout
                                        ; seconds, to avoid deadlock.

;; Have sent the shutdown request message, awaiting acknowledgement from
;; the peer. receipt of acknowledgement message or timeout triggers
;; the transition to the closed state.

;; can read but cannot write socket in this state.  can only process the ack
;; message in this state; all other messages are simply read and
;; discarded. (not an error; this may happen quite frequently!)
(defparameter icp-connection-awaiting-acknowledgement                5) ; -> {closed}  Times out after
                                        ; icp-socket-shutdown-handshake-timeout
                                        ; seconds, to avoid deadlock.
;;icp-socket-listening
;; this indicates that a socket is a listener, i.e. a passive endpoint that
;; accepts connectons.
(defparameter icp-socket-listening                                       6) ; -> {closed}

;;icp-socket-error
;; This state indicates that a socket has experienced an error which caused
;; the connection to be broken.  this is used to indicate to the client that a
;; socket has experienced an error, as opposed to a clean shut down.

(defparameter icp-socket-error                                       7) ; -> {closed}
)


(eval-when (:compile-toplevel :load-toplevel :execute)
;10-Aug-96
(defconstant release-1.0-icp-version 1)

(defconstant release-2.0-icp-version 2)
(defconstant reclaim-remote-corresponding-object-icp-version 2)
(defconstant modify-gsi-sensor-definition-icp-version 2)
;There is a comment in int3.lisp, at the icp writer and reader of float,
;that implies double-float-icp-version happened the revision after 2.1.
;So, I am leaving a gap to allow for it.
;But, for now, double-float-icp-version is still 2, since that's the
;way the code was.
(defconstant double-float-icp-version 2) ; change this to 3?

(defconstant release-3.0-icp-version 4)

(defconstant release-4.0-icp-version 5)
(defconstant ds-update-interval-as-float-icp-version 5)
(defconstant remote-procedure-include-attribute-icp-version 5)
(defconstant pass-item-as-handle-icp-version 5)
(defconstant pass-item-as-copy-icp-version 5)
(defconstant gsi-item-registration-icp-version 5)
(defconstant gsi-timestamp-as-float-icp-version 5)
(defconstant shutdown-protocol-icp-version 5)
(defconstant new-connect-scheme-icp-version 5)
(defconstant g2-version-reply-to-gsi-icp-version 5)

(defconstant wide-strings-icp-version 6)

(defconstant writing-coalesced-icp-message-group-icp-version 7)
;8: 06-Nov-96 to 25-Sep-97
(defconstant supports-icp-version-protocol-icp-version 8)
(defconstant remote-value-supports-item-icp-version 8)
(defconstant supports-optional-remote-value-tags-icp-version 8)
(defconstant evaluation-sequences-and-structures-icp-version 8)
(defconstant resumable-icp-version 8)
(defconstant new-rpc-kinds-icp-version 8)
(defconstant value-vector-names-are-symbols-icp-version 8)
(defconstant does-not-require-enlarge-corresponding-icp-object-index-space-icp-version 8)
(defconstant rel4-rpc-protocol-supports-non-objects-icp-version 8)
;9: 07-Apr-97
(defconstant resumable-gsi-ds-icp-version 9)
(defconstant remote-procedure-include-all-system-attributes-icp-version 9)
(defconstant no-telewindows-clogging-icp-version 9)
(defconstant remote-procedure-varargs-p-icp-version 9)
(defconstant new-remote-procedure-identifer-protocol-icp-version 9)
;10: 14-May-97
(defconstant rpc-use-value-structure-using-unix-time-icp-version 10)
(defconstant deregister-corresponding-icp-object-index-space-name-icp-version 10)
(defconstant deregister-original-icp-object-icp-version 10)
(defconstant item-index-space-icp-version 10)
(defconstant values-as-handle-icp-version 10)
;11: 19-May-97
(defconstant gsi-dataservice-uses-full-remote-value-protocol-icp-version 11)
;12: 21-May-97
(defconstant item-reference-icp-version 12)
(defconstant acknowledge-deregister-corresponding-icp-object-icp-version 12)
;13: 14-Aug-97
(defconstant abort-icp-task-icp-version 13)
(defconstant deregister-icp-objects-icp-version 13)
;14: 20-Aug-97
(defconstant unsigned-short-vector-icp-version 14)
;15: 23-Jan-98
(defconstant independent-layered-rendering-version 15)
(defconstant data-servers-can-run-while-inactive-version 15)

(defconstant by-copy-with-handle-supports-references-icp-version 16)
;17: 21-Feb-98
(defconstant return-g2ds-version-sends-class-icp-version 17)
(defconstant supports-non-resumability-icp-version 17)
;18: 14-Mar-98 to 24-Mar-98
(defconstant gsi-sends-returned-gsi-sensor-as-reference-icp-version 18)
(defconstant no-licence-icp-version 18)
(defconstant supports-new-references-icp-version 18)
;19: 24-Nov-98
(defconstant g2-supports-update-with-delete-icp-version 19)
;20: 24-Feb-99
(defconstant t2-supports-item-layer-change 20)
;21: 19-May-99
(defconstant do-not-reformat-message-icp-version 21)
;    22-May-99
(defconstant no-frame-serial-index-space-icp-version 21)
;22: 22-Jul-99
(defconstant intern-keyword-icp-version 22)
;23: 25-Sep-99
(defconstant long-string-icp-version 23)
;24: 02-Dec-99
(defconstant send-text-of-expressions-for-g2ds-icp-version 24)
;25: 07-Dec-99
(defconstant remote-procedure-include-all-system-attributes-except-icp-version 25)
;26: 19-Dec-99
(defconstant transparent-color-index-icp-version 26)
;27: 29-Apr-00
(defconstant compressed-image-data-chunk-icp-version 27)
;28: 24-Mar-15
(defconstant dialog-component-with-font-icp-version 28)
;29: 14-Nov-15
(defconstant supports-font-in-grid-view-icp-version 29)
;30: 3-Jan-2016
(defconstant native-long-icp-version 30)

(defparameter newest-icp-version 30)
)

;; See also print-icp-socket, when adding additional states. - ben Jul 13, 95

(eval-when (:compile-toplevel :load-toplevel :execute)
;; initializing: gsi connection is negotiating the protocol version
(defparameter gsi-connection-initializing 1)
;; established: protocol version has been determined
(defparameter gsi-connection-established 2)
)

(def-structure socket)

(def-structure (icp-socket
                 (:include socket)
                 (:constructor
                   make-icp-socket-structure
                   (type-of-icp-connection
                     icp-connection-name
                     icp-connection-state
                     listener-socket
                     icp-socket-local-system-name))
                 (:reclaimer reclaim-icp-socket-internal)
                 #+development
                 (:print-function print-icp-socket))


  type-of-icp-connection                  ;GENERIC, LOCALNET

  (icp-connection-name nil :reclaimer reclaim-if-text-string)

  icp-input-port
  icp-output-port

  (enclosing-interface-frame? nil)
  (enclosing-interface-frame-serial-number nil
    :reclaimer reclaim-enclosing-interface-frame-serial-number)

  (icp-socket-saw-io? nil) ; only read by gsi-context-received-data

  ;; Shutdown info
  last-icp-message-code-read ; only read by icp-out-of-synch
  (reason-for-shutdown? nil)

  ;; callbacks for IO events on this socket

  ;; connection-loss: a list of symbols naming funcallable functions of two
  ;; arguments, the icp socket being closed, and whether the closure was
  ;; shutdown(2) or close(2), i.e. a clean shutdown or an abortive close.
  ;;
  (icp-connection-loss-callbacks nil
    :reclaimer reclaim-icp-callbacks)

  ;; Connect: a list of symbols naming funcallable functions of one argument,
  ;; the icp socket which has finished connecting.  never defined for listener
  ;; sockets.
  ;;
  (icp-connect-callbacks nil
    :reclaimer reclaim-icp-callbacks)

  ;; accept: a list of symbols naming funcallable functions (or nil) which will
  ;; be called when a connection is accepted on this socket, which must
  ;; necessarily be a listener socket.  Takes 2 args, the listener and the
  ;; nascent socket just accepted on that listener.  Non-nil only for listener
  ;; sockets.
  (icp-accept-callbacks nil
    :reclaimer reclaim-icp-callbacks)

  ;; write: a list of symbols naming funcallable functions taking 2 arguments,
  ;; the icp-socket structure on which a write state change occurred, and the
  ;; state which now obtains (blocked, writeable)
  ;;
  (icp-write-callbacks nil
    :reclaimer reclaim-icp-callbacks)

  ;; read: a list of symbols naming funcallable functions taking 2 arguments,
  ;; the icp-socket structure on which a read state change occurred, and the
  ;; state which now obtains (blocked, readable)
  ;;
  (icp-read-callbacks nil
    :reclaimer reclaim-icp-callbacks)

  ;; see symbol definitions above, icp-connection-running, etc.
  icp-connection-state

  (icp-connection-timeout-task? nil :reclaimer cancel-task)
  (icp-connection-succeeds-at-first-message-p t)

  ;;*************************************

  (local-icp-version-info-state 'initial)

  (remote-icp-version-info nil :reclaimer reclaim-icp-version-info)

  ;; Since the determination of whether or not to use the new shutdown handshake
  ;; mechanism is made based on the peer's version, this value needs to be
  ;; determined at run time and this slot will remain in version 5.0:
  ;; -ncc, 24 Jan 1996

  (icp-connection-supports-shutdown-protocol? nil)

  (icp-protocol-version-for-input 0)
  (icp-protocol-version-for-output 0)

  ;;*************************************

  (icp-socket-workstation nil)

  ;; no longer assume socket:window is 1:1! (MHD 8/8/02)
  ;; (icp-socket-window nil) ; OBSOLETE!

  ;; I think this will change radically given the 5.0 flow control mechanism
  ;; -ncc, 24 Jan 1996
  ;;
  ;; Throughput info
  (I-am-alive-info? nil
   :reclaimer reclaim-I-am-alive-info?) ;see I-am-alive mechanism

  ;; The following three slots are for network security.
  (icp-socket-listener-client? nil) ;T, TELEWINDOWS, G2, OLE, GSI, or NIL
  (icp-connection-refused-p nil)
  (icp-socket-shutdown-timer nil)

  ;; GSI connection info (also used by G2)
  (gsi-connection-state #.gsi-connection-initializing)
  ;; GSI info (GSI only)
  (gsi-extension-data? nil
    :reclaimer reclaim-gsi-extension-data-for-gsi)

  ;; Object-passing info
  (available-bandwidth-for-object-passing
    maximum-object-passing-bandwidth)
  (resumable-objects-waiting-for-unclog nil)
  (resumable-objects-waiting-for-unclog-tail nil)

  ;; listener-socket holds a pointer to the listener that spawned this icp socket, if any, or nil.
  ;;
  (listener-socket nil)

  ;; this slot holds the task info for the task that is scheduled to process
  ;; queued message groups for this socket, if any.
  (icp-message-handler-future-task? nil
    :reclaimer cancel-task)
  (icp-message-handler-current-task? nil
    :reclaimer cancel-task)

  (shutdown-timeout-task? nil
    :reclaimer cancel-task)

  (resumable-icp-output-task-queue-vector
    nil
    :reclaimer reclaim-resumable-icp-output-task-queue-vector)

  (task-to-start-resumable-icp-writing
    nil)

  (icp-socket-representations nil) ; used to implement G2 api linkage - jed 9/29/96
  (icp-socket-session-id nil)      ; stale pointer protection hack    - jed 9/29/96

  (remote-procedure-call-start-map
    nil
    :reclaimer reclaim-remote-procedure-call-start-map)

  (corresponding-localnet-socket nil)

  (icp-socket-read-task nil :reclaimer cancel-task)
  (icp-socket-write-task nil :reclaimer cancel-task)
  (icp-socket-close-task nil :reclaimer cancel-task)

  (icp-socket-deregister-icp-objects-alist
    nil :reclaimer reclaim-icp-tree)
  (icp-socket-deregister-icp-objects-task nil :reclaimer cancel-task)

  (icp-socket-runs-while-inactive nil)

  (icp-socket-local-system-name nil)

  (icp-socket-uses-item-references 'unknown)
  (task-to-send-I-am-alive nil :reclaimer cancel-task)

  (icp-socket-gsi-application-name nil)
  (icp-socket-does-not-allow-resumability nil)

  (icp-remote-host-name nil :reclaimer reclaim-if-text-string)

  ;; New for G2 7.1.  If this socket is being used by a G2 for a TW client
  ;; connection, then this will be used to suppress notifications of connection
  ;; loss. See icp-socket-notifies-user-on-error-p, which decides if lost
  ;; connections should be reported. (MHD 9/2/03)
  (suppress-connection-loss-notification-for-tw-p nil))

(defun-void reclaim-remote-procedure-call-start-map (map)
  (when map (reclaim-index-space map)))

(defun-void reclaim-enclosing-interface-frame-serial-number (frame-serial-number)
  (current-system-case
    (ab (reclaim-frame-serial-number frame-serial-number))
    (otherwise frame-serial-number nil)))

(defmacro icp-connection-supports-wide-strings? (icp-socket direction)
  (if (constantp direction)
      (setq direction (eval direction))
      (error "The direction parameter to icp-connection-supports-wide-strings? was not a constant"))
  `(<=f wide-strings-icp-version
        (,(ecase direction
           (input 'icp-protocol-version-for-input)
           (output 'icp-protocol-version-for-output))
          ,icp-socket)))



(eval-when (:compile-toplevel :load-toplevel :execute)


;;;; def-icp-callback-functions
;;;;
;;;;  top-level form which defines three functions for a given slot in the
;;;;  structure icp-socket (below); the given slot holds a list of funcallable
;;;;  function symbols naming event callbacks.
;;;;
;;;;     execute-icp-<slotname>-callbacks, a function of n arguments, which will
;;;;     iterate over the list of callbacks for the given icp-socket, calling
;;;;     each on the given icp-socket and callback-arglist.  n is (1+ (length
;;;;     callback-arglist))
;;;;
;;;;     register-icp-<socket-callback-slot>-callback, a function of two
;;;;     arguments which registers the given symbol (representing a funcallable
;;;;     function whose arglist must match that described in
;;;;     execute-icp-<slotname>-callbacks, above) as a callback handler in the
;;;;     named handler slot in the given icp-socket structure.
;;;;
;;;;     deregister-all-icp-<socket-callback-slot>-callbacks, a function of one
;;;;     argument, an icp-socket.  The named callback slot will be cleared, and
;;;;     any list reclaimed.
;;;;
;;;;     reclaim-icp-<slotname-callbacks, a function of one argument, which can
;;;;     be either nil or a gensym-list to be reclaimed.  Used in the structure
;;;;     definition as a slot value reclaimer.

(defconser icp-callback int1)

(defmacro def-icp-callback-functions (socket-callback-slot &rest callback-arglist)
    (let* ((slot-accessor (intern (format nil "~A-CALLBACKS" socket-callback-slot)))
           (executor (intern (format nil "EXECUTE-~A-CALLBACKS" socket-callback-slot))))
      `(progn

        (defun-void ,executor (icp-socket ,@callback-arglist)
          (loop with callback-functions = (,slot-accessor icp-socket)
                for callback-function in callback-functions
                do (funcall callback-function icp-socket ,@callback-arglist))
          ,(when (eq socket-callback-slot 'icp-connection-loss)
             `(deregister-all-icp-callbacks 'icp-connection-loss icp-socket)))

        (defun-void ,(intern (format nil
                                     "REGISTER-~A-CALLBACK"
                                     socket-callback-slot))
            (callback-function icp-socket)
          (icp-callback-push callback-function (,slot-accessor icp-socket)))
        (defun-void ,(intern (format nil
                                     "RECLAIM-~A-CALLBACKS"
                                     socket-callback-slot))
            (callbacks)
          (reclaim-icp-callback-list callbacks))
        (defun-void ,(intern (format nil
                                     "DEREGISTER-ALL-~A-CALLBACKS"
                                     socket-callback-slot))
            (icp-socket)
          (let ((callback-functions? (,slot-accessor icp-socket)))
            (when callback-functions?
              (reclaim-icp-callback-list callback-functions?)
              (setf (,slot-accessor icp-socket) nil))))))))

(defmacro icp-callbacks (socket-callback-slot icp-socket)
  `(,(intern (format nil "~A-CALLBACKS" (eval socket-callback-slot)))
     ,icp-socket))

(defmacro register-icp-callback (socket-callback-slot &rest args)
  `(,(intern (format nil "REGISTER-~A-CALLBACK" (eval socket-callback-slot)))
     ,@args))

(defmacro execute-icp-callbacks (socket-callback-slot &rest args)
  `(,(intern (format nil "EXECUTE-~A-CALLBACKS" (eval socket-callback-slot)))
     ,@args))

(defun-void reclaim-icp-callbacks (callbacks)
  (reclaim-icp-callback-list callbacks))

(defmacro deregister-all-icp-callbacks (socket-callback-slot &rest args)
  `(,(intern (format nil "DEREGISTER-ALL-~A-CALLBACKS" (eval socket-callback-slot)))
     ,@args))


;;;;  callback definitions for icp-socket structure:

(def-icp-callback-functions icp-connection-loss clean?)
(def-icp-callback-functions icp-connect)
(def-icp-callback-functions icp-accept nascent-socket)
(def-icp-callback-functions icp-read readable?)
(def-icp-callback-functions icp-write writable?)


;;; not-a-listener-p

(defun-simple not-a-listener-p (icp-socket)
  (/=f (icp-connection-state icp-socket) icp-socket-listening))


;;ICP-SOCKET-SAW-IO?
;; Set in process-icp-sockets, this slot must be cleared by the user, from
;; above the ICP layer.  This slot indicates whether or not IO has been done
;; on this socket by the ICP layer, since this slot was last cleared.  This
;; socket is cleared for all active icp sockets by the ICP API function
;; reset-counters-for-all-icp-sockets, or for an individual socket via the ICP
;; API macro reset-counters-for-icp-socket.
;;

;; Users of ICP should set icp-connection-supports-new-connect-scheme? to t if
;; they want to take advantage of the new code I wrote to handle the fact that
;; we connect in a non-blocking fashion. (see my email or the relevant paper
;; trail entry) This change won't create compatibility problems with peers,
;; since it doesn't alter the protocol in any way.  But it does necessitate
;; changes in the code layers above ICP, to accomodate the new socket state
;; "icp-connection-connect-in-progress" which may occur after the call to
;; make-network-connection.  This slot of course defaults to the value nil.

;; Users of ICP should set icp-connection-supports-shutdown-protocol? to t on
;; sockets iff they know that the peer is version 4.0 or greater. the default
;; value of nil disables shutdown handshaking, preserving compatibility with
;; products built on older versions of ICP.  -ncc, 4 Apr 1995


;; Added enclosing-interface-frame? slot to the icp-socket structure.  This
;; supplies a backpointer to the frame in which this socket is embedded, useful in
;; allowing GSI message service to reclaim messages from the remote extension,
;; despite the fact that they have no frame of origin within G2.  (jh, 5/24/90)

;; Added three slots to the icp-socket structure to implement network security.
;; The icp-socket-is-listener-p slot is true if the socket was created by
;; responding to a request from outside G2.  This is the case for Telewindows and
;; G2-to-G2 connections, but not for GSI or GSPAN.  The icp-connection-refused-p
;; slot is true if this is a listener socket created when G2 was not accepting
;; remote connections.  We need this to allow a G2 to send a brief
;; connection-refused message before shutting down the illicit connection.
;; Finally, the icp-socket-shutdown-timer slot contains a counter used to allow
;; existing listener connections some warning time before shutdown.  This warning
;; time is controlled by the G2 doing the restricting, so the remote socket holder
;; is unable to "stall" and keep the connection open indefinitely.  For now this
;; warning time is a constant 10 seconds.  jh, 1/30/91.


(def-substitution-macro icp-socket-state->symbol (icp-socket-state)
  (assq icp-socket-state
        '(( 0                            closed)
          ( 1               connect-in-progress)
          ( 2                           running)
          ( 3                shutdown-requested)
          ( 4  shutdown-acknowledgement-rundown)
          ( 5          awaiting-acknowledgement)
          ( 6                         listening)
          ( 7                             error))))

(defun-void twrite-icp-socket-connection-name (icp-socket)
  (let* ((name (stringw (icp-connection-name icp-socket)))
         (limit1 #.(length ":ACCEPT:"))
         (name-length (wide-string-length name))
         (accept-pos (when (< limit1 name-length)
                       (search #w":ACCEPT:" name :end1 limit1)))
         (pos (or accept-pos
                  (search #w":" name :end1 1)
                  name-length))
         (remote-name
           (when accept-pos
             (get-remote-host-name icp-socket))))
    (loop for i from 0 below pos
          for char = (charw name i)
          unless (char=w char #.%\_)
            do (twrite-char (char-upcasew char)))
    (cond (remote-name
           (twrite-char #.%\:)
           (twrite-string remote-name))
          (t
           (loop for i from pos below name-length
                 for char = (charw name i)
                 do (twrite-char char))))))

(defun-simple icp-socket-description (icp-socket)
  (twith-output-to-text-string
    (tformat "ICP-SOCKET ")
    (twrite-icp-socket-connection-name icp-socket)
    (tformat " in state ~D (~a)"
             (icp-connection-state icp-socket)
             (second
               (or
                 (icp-socket-state->symbol (icp-connection-state icp-socket))
                 '(nil bizzare-state))))))

#+development
(defun print-icp-socket (icp-socket stream depth)
  (declare (ignore depth))
  (printing-random-object (icp-socket stream)
    (format stream "ICP-SOCKET ~A ~D:~a"
            (icp-connection-name icp-socket)
            (icp-connection-state icp-socket)
            (second
              (or
                (icp-socket-state->symbol (icp-connection-state icp-socket))
                '(nil bizzare-state))))))






;; GSI user data

(defun-void reclaim-gsi-extension-data-for-gsi (extension-data)
  (current-system-case
    (gsi (reclaim-gsi-extension-data extension-data))
    (t extension-data nil)))






;;; Declaration:     i-am-alive-info
;;; Type:             G2 def-structure.
;;; Purpose:             Hold information to monitor ICP throughput..
;;; Slots:           > remote-process-alive-p is t or nil.  I-am-alive internals set
;;;                    this slot to the value returned by the client-written function
;;;                    function-to-determine-if-remote-process-alive?.
;;;                  > icp-connection-clogged-p is t or nil.  I-am-alive internals
;;;                    set this slot to the value returned by the client-writen
;;;                    function function-to-determine-if-icp-connection-clogged?.
;;;                  > i-am-alive-send-time-interval?  is a fixnum time or nil.
;;;                    This slot is set by a call to initialize-i-am-alive-info made
;;;                    by the client of the i-am-alive facility.  The i-am-alive
;;;                    internals do not use this value (say to send a heartbeat); it
;;;                    is for reference by client-written functions like
;;;                    function-to-decide-whether-to-send-I-am-alive.
;;;                    (It looks to me like this is a time in seconds Ben 3/15/92)
;;;                  > deadman-switch-time-interval?  is nil or a a fixnum time
;;;                    which indicates how long to wait until assuming the remote
;;;                    process can not longer transmit ICP data.  This slot is set
;;;                    by a call to initialize-i-am-alive-info made by the client of
;;;                    the i-am-alive facility.  The i-am-alive internals do not use
;;;                    this value; This slot is for reference by client-written
;;;                    functions like
;;;                    function-to-determine-if-remote-process-alive?.
;;;                    (It looks to me like this is a time in seconds Ben 3/15/92)
;;;                  > time-i-am-alive-was-sent is a fixnum time.
;;;                  > time-i-am-alive-was-received is a fixnum time.
;;;                  > number-of-message-groups-handled-since-last-i-am-alive-was-
;;;                    sent is a fixnum.
;;;                  > number-of-icp-bytes-handled-since-last-i-am-alive-was-sent
;;;                    is a fixnum.
;;;                  > function-to-decide-whether-to-send-i-am-alive is a symbol
;;;                    naming a funcallable function.  This function is written by
;;;                    the client of the i-am-alive facility and takes a single
;;;                    argument, an i-am-alive-structure.
;;;                  > function-to-determine-if-remote-process-alive?  is nil or a
;;;                    symbol naming a funcallable function.  This function is
;;;                    written by the client of the i-am-alive facility and takes a
;;;                    single argument, an i-am-alive structure.
;;;                  > id-for-last-message-group-written is a fixnum identifying the
;;;                    last message group written on the local side.
;;;                  > id-for-last-message-group-handled is a fixnum identifying the
;;;                    last message group handled by the remote side.
;;;                  > id-for-last-message-group-handled-by-remote-socket is a fixnum.
;;;                  > function-to-determine-if-icp-connection-clogged?  is nil or a
;;;                    symbol naming a funcallable function.  This function is
;;;                    written by the client of the i-am-alive facility and takes a
;;;                    single argument, an i-am-alive structure.
;;;                  > things-to-update-when-unclogged?  is currently only used by
;;;                    Telewindows, but could be abstracted to provide a place to
;;;                    keep things relevant to a function called to unclog the ICP
;;;                    connection.
;;;                  > message-group-ids-and-byte-counts contains an alist, each
;;;                    entry of which is a gensym-cons whose car is a fixnum
;;;                    message-group-id and whose cdr is a fixnum byte-count.  This
;;;                    alist is manged by the internal i-am-alive machinery.
;;;                  > number-of-outstanding-icp-bytes is a fixnum.
;;;                  > time-when-first-suspected-clogging? is a fixnum time or nil.
;;; Return behavior: No useful value.
;;; Users:           Telewindows (TELESTUBS) and G2-to-G2 communication (G2DS).
;;; Prerequisites:   The macro def-structure must be defined.
;;; Side effects:    Defines a constructor macro make-i-am-alive-info, which takes
;;;                  no arguments.  This constructor is internal to the i-am-alive
;;;                  facility and should not be used elsewhere.  Defines a predicate
;;;                  i-am-alive-info-p.
;;; Non-local exits: None.
;;; Memory impact:   Compile-time consing only.
;;; Notes:           The public interface to this structure is
;;;                  initialize-i-am-alive-info, documented in INT3.

;;; The I-am-alive-info structure holds the micro-task state for a watch dog on the
;;; ICP connection.  Messages passed between both sides of the connection to sense
;;; the status of the connection.  These messages are message type I-AM-ALIVE.  The
;;; micro-task gets cycles either do to regular calles upon
;;; do-I-am-alive-processing, or by processing the I-AM-ALIVE message traffic.

;;; You may visualize this data structure using the Main Misc. Menu Command
;;; Telewindows Status Display.

;;; I think this is only used in Telewindows.  In telewindows the
;;; `function-to-decide-whether-to-send-I-am-alive', aka
;;; send-I-am-alive-for-telewindows-socket?, triggers due to
;;; time (I-am-alive-send-time-interval?),
;;; bytes (send-I-am-alive-for-telewindows-socket?), or
;;; message groups (telewindows-max-number-of-message-groups-between-I-am-alive).

;;; In Telewindows the `function-to-determine-if-remote-process-alive?', aka
;;; process-at-other-end-of-telewindows-connection-alive?, will set
;;; remote-process-alive-p to NIL if the deadman-switch-time-interval?  has passed
;;; since we last caught an I-AM-ALIVE from the other side.  Apparently only
;;; initialization sets this to T, and hence dead is forever.  That's "ok" because
;;; nothing apparently uses the flag, except the Telewindows Status Display.

;;; In Telewindows the `function-to-determine-if-icp-connection-clogged?', aka
;;; telewindows-connection-clogged{,for-g2}?, manages transitioning between three
;;; states: unclogged -> suspected -> (clogged or unclogged).  It will suspect
;;; clogging and set `time-when-first-suspected-clogging?' on the basis of either
;;; backedup bytes or message-groups (as per
;;; telewindows-max-number-of-icp-bytes-before-clogged, or
;;; telewindows-max-number-of-icp-bytes-before-clogged).  If sufficent time passes
;;; as per telewindows-seconds-to-wait-before-judging-clogged it will return T.  If
;;; the already clogged it begin to return T if enough bytes finally get
;;; acknowledged (per telewindows-min-number-of-icp-bytes-before-unclogged).

;;; The I-am-alive messages contain the message-id of the most recent message
;;; recieved.  Hence if A sends B message X latter B will send A an I-am-alive
;;; message contianing X's id or that of a latter message.  The
;;; message-group-ids-and-byte-counts slot in the i-am-alive-info maintains a list
;;; of all outgoing messages and their sizes.  When A send X it adds to that list,
;;; and when it recieves i-am-alive messages it pops entries off that list.
;;; Throughout it maintains the slot number-of-outstanding-icp-bytes.

;; - ben 3/15/93  (Comments above written by inspection of code so they are probably
;; wrong.)

(def-structure (I-am-alive-info (:eliminate-for-products gsi))

  (remote-process-alive-p t)
  (icp-connection-clogged-p nil)

  time-I-am-alive-was-sent
  time-I-am-alive-was-received
  number-of-message-groups-handled-since-last-I-am-alive-was-sent
  number-of-icp-bytes-handled-since-last-I-am-alive-was-sent

  id-for-last-message-group-written
  id-for-last-message-group-handled
  id-for-last-message-group-handled-by-remote-socket
;  id-for-last-message-group-written-by-remote-socket  ; not currently used

  (function-to-determine-if-icp-connection-clogged? nil)
  (things-to-update-when-unclogged?
    nil :reclaimer reclaim-things-to-update-when-unclogged?)

  (message-group-ids-and-byte-counts nil :reclaimer reclaim-icp-tree)
  message-group-ids-and-byte-counts-tail
  number-of-outstanding-icp-bytes
  (time-when-first-suspected-clogging? nil)

  (icp-bytes-per-second-through-output-port 0)
  (unclogged-cleanup-task nil :reclaimer cancel-task))

;;; Declaration:     reclaim-i-am-alive-info? (i-am-alive-info?)
;;; Type:             Lisp function.
;;; Purpose:             Reclaim an i-am-alive-info structure.
;;; Arguments:             An i-am-alive-info structure or nil.
;;; Return behavior: No useful value.
;;; Users:             ICP internals (slot reclaimer for icp-socket structure in
;;;                  INT1).
;;; Prerequisites:   None.
;;; Side effects:    None.
;;; Non-local exits: None.
;;; Memory impact:   If i-am-alive-info is an i-am-alive-info structure, it is is
;;;                  reclaimed.

(defun reclaim-I-am-alive-info? (I-am-alive-info?)
  (declare (no-op-for-gsi))
  (when I-am-alive-info?
    (reclaim-I-am-alive-info I-am-alive-info?)))

;; See I-am-alive mechanism.



(defun reclaim-things-to-update-when-unclogged?
       (things-to-update-when-unclogged?)
  (reclaim-gensym-list things-to-update-when-unclogged?))


(def-system-variable highest-icp-socket-session-id INT1 0)

;;; Make-icp-socket makes a new ICP socket initialized with two new ICP ports,
;;; one for use by the ICP transmitter and one for use by the ICP receiver.

(defun make-icp-socket
    (icp-connection-name
      type-of-icp-connection
      icp-connection-input-handle icp-connection-output-handle?
      receive-while-handling-icp-input? transmit-while-writing-icp?
      icp-connection-open-p
      parent-listener?
      local-system-name
      connect-timeout)
  (let* ((icp-connection-state (if icp-connection-open-p
                                   icp-connection-running
                                   icp-connection-closed))
         (icp-socket
           (make-icp-socket-structure
             type-of-icp-connection icp-connection-name
             icp-connection-state parent-listener?
             local-system-name)))

    ;;The input port holds the handle for listener sockets.  This is bogus, but
    ;; it will work.  -ncc, 8 Apr 1996
    (setf (icp-input-port icp-socket)
          (unless (eq type-of-icp-connection 'temporary-output)
            (make-icp-port
              icp-connection-input-handle icp-socket 'input
              receive-while-handling-icp-input?)))

    ;; Only create the output port structure when we're creating an endpoint and
    ;; not a listener -- listeners are distinguished here by having a null
    ;; icp-connection-output-handle, a convention established in 5.0 with the
    ;; creation of make-and-install-network-listener.  -ncc, 8 Apr 1996
    (setf (icp-output-port icp-socket)
          (when (or icp-connection-output-handle?
                    (eq type-of-icp-connection 'temporary-output))
            (make-icp-port
              icp-connection-output-handle? icp-socket 'output
              transmit-while-writing-icp?)))

    (setf (icp-socket-session-id icp-socket)
          (incff highest-icp-socket-session-id)) ; jed 9/29/96

    (when (fixnump connect-timeout)
      (with-current-scheduling
          ((icp-connection-timeout-task? icp-socket)
           lowest-system-priority
           nil nil t)
        (icp-connection-timeout-task-1 icp-socket connect-timeout)))

    (current-system-case
      (gsi (when icp-connection-output-handle? ; listeners are excluded
             (gsi-initialize-icp-socket icp-socket))))

    icp-socket))

(defun-void icp-connection-timeout-task-1 (icp-socket connect-timeout)
  (cancel-task (icp-connection-timeout-task? icp-socket))
  (with-future-scheduling
      ((icp-connection-timeout-task? icp-socket)
       lowest-system-priority
       (future-interval connect-timeout)
       nil nil t)
    (icp-connection-timeout-task-2 icp-socket)))

(defun-void icp-connection-timeout-task-2 (icp-socket)
  (cancel-task (icp-connection-timeout-task? icp-socket))
  (shutdown-icp-socket-connection icp-socket 'connection-attempt-timed-out))

;; see new state variable mod to icp-socket structure definition.
(defun-simple icp-connection-open-p (icp-socket-structure)
  (let* ((icp-connection-state (icp-connection-state icp-socket-structure)))
    (not (or  (=f icp-connection-state icp-connection-closed)
              (=f icp-connection-state icp-connection-awaiting-acknowledgement)
              (=f icp-connection-state icp-connection-connect-in-progress)))))

(defun-simple icp-connection-in-progress-p (icp-socket-structure)
  (let* ((icp-connection-state (icp-connection-state icp-socket-structure)))
    (=f icp-connection-state icp-connection-connect-in-progress)))



;; replaces structure slot icp-connection-being-shutdown? with a predicate:
;;  this supports old code that does not grok the new model shutdown.
;;  -ncc, 4 Apr 1995

;; icp-connection-being-shutdown? returns true if the given connection is in a
;; state where it is open but cannot be written to anymore.  The nature of the
;; shutdown protocol is such that any

(defun-simple icp-connection-being-shutdown? (icp-socket-structure)
  (let ((connection-state (icp-connection-state icp-socket-structure)))
    (or (=f connection-state icp-connection-awaiting-acknowledgement)
        (=f connection-state icp-connection-shutdown-acknowledgement-rundown))))


(defun-simple icp-connection-can-process-messages? (icp-socket-structure)
  (let ((connection-state (icp-connection-state icp-socket-structure)))
    (or (=f connection-state icp-connection-running)
        (=f connection-state icp-connection-awaiting-acknowledgement))))

(def-substitution-macro socket-can-accept-input (icp-socket)
  (let ((connection-state (icp-connection-state icp-socket)))
    (or (=f connection-state icp-connection-running)
        (=f connection-state icp-connection-awaiting-acknowledgement))))

(def-substitution-macro socket-can-perform-output (icp-socket)
  (=f (icp-connection-state icp-socket) icp-connection-running))


;;; This is currently unused, and will need fixing to make it
;;; two-word-frame-serial-number safe.
(def-hash-table frame-serial-number-to-item-table
    :constructor     make-frame-serial-number-to-item-table
    :accessor        get-item-from-frame-serial-number
    :key-deleter     delete-item-from-frame-serial-number-table
    :entry-reclaimer note-item-deleted-from-frame-serial-number-table
    :size            67 ; use a prime number
    )

(defun-void reclaim-if-frame-serial-number-to-item-table (table?)
  (when table?
    (reclaim-frame-serial-number-to-item-table table?)))



;;;; ICP Buffers


;;; An `ICP buffer' is a data-abstracted structure that holds a non-empty
;;; segment of an ICP byte stream that is in transit from an ICP receiver to an
;;; ICP reader (handler) or from an ICP writer to an ICP transmitter.  An icp
;;; buffer may not be implemented as nil.

;;; An `ICP byte position' is a data-abstracted representation for the position
;;; of an icp byte in an icp buffer.  An icp byte position may not be
;;; implemented as nil.

;;; The operations defined on an ICP buffer are specified in detail below.
;;; Except for receive-next-icp-buffer-listed-if-any and transmit-icp-buffer,
;;; they assume that special variable current-type-of-icp-buffer determines the
;;; type of icp buffer (there may be several types).  Also, they and functions
;;; that use them assume that `icp byte counts', for icp buffers and message
;;; series, are always small enough to be fixnums.

;;; !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
;;; !NOTA BENE: there is no more current-type-of-icp-buffer -- only            !
;;; !variable-fill icp buffers are left, and the vestigial code to handle the  !
;;; !other types has been removed.  -ncc, 7 Mar 1996                           !
;;; !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


;;; Declaration:     variable-fill-icp-buffer
;;; Type:             G2 vector pool.
;;; Purpose:             Buffer ICP input and output on delivery platforms.
;;; Arguments:             N/A.
;;; Return behavior: N/A.
;;; Users:             ICP internals.
;;; Prerequisites:   def-vector-pool must be defined.
;;; Side effects:    N/A.
;;; Non-local exits: N/A.
;;; Memory impact:   ICP buffers are managed in pools.
;;; Notes:           Vector pools are allocated one at a time.  We might gain some
;;;                  efficiency if we allocated ICP buffers according to some
;;;                  batching scheme.

;;; A `variable-fill ICP buffer' is a gensym cons of the form
;;; (simple-icp-byte-array .  icp-byte-count), where simple-icp-byte-array is a
;;; fixed-size simple array of icp bytes (16-bit unsigned integers) and where
;;; icp-byte-count is the number of icp bytes with which the array is filled
;;; (for reading) or may be filled (for writing).



(def-vector-pool variable-fill-icp-buffer
    #.(size-of-variable-fill-icp-buffers-in-8-bit-bytes)
  :element-type (unsigned-byte 8)
  ;; :unmoveable t ;see note below
  )

;; jh, 9/10/91.  Removed the :unmoveable option from the def-vector-pool for
;; variable-fill-icp-buffer.  This option is only necessary when we intend to pass
;; a pointer to a C asynchronous process and then resume Lisp processing, thereby
;; creating the risk that the pointer will be relocated by garbage collection.
;; Brian assures me that a pointer to a variable-fill-icp-buffer is never passed
;; to an asynchronous C process.  The buffer is always filled synchronously by a C
;; function call.


(def-system-variable recycled-variable-fill-icp-buffers INT2 nil)

(def-system-variable transmitted-variable-fill-icp-buffers INT2 nil)


;; Consider reclaiming variable-fill icp buffers, instead of recycling them in a
;; special-purpose way (which is a bit faster).  To do this, eliminate the
;; variable above and some code in make-listed-icp-buffer, and switch to the
;; commented-out code in release-listed-icp-buffer.



;; Define the following operations for other cases, and customize certain of
;; them for every operating system, type of icp connection (e.g., type of
;; network protocol), and desired level of performance!  Ideally, an icp buffer
;; is a TCP/IP or similar packet structure.



;;; Declaration:     make-listed-icp-buffer ()
;;; Type:             Lisp function.
;;; Purpose:             Create a new ICP buffer.
;;; Arguments:       None.
;;; Return behavior: Returns a one-element gensym-list containing a
;;;                  gensym-cons whose car is an ICP buffer of type
;;;                  variable-fill (-ncc, 7 Mar 1996).  The contents
;;;                  of the buffer are random.
;;; Users:             ICP internals:
;;;                    INT1: make-icp-port
;;;                    INT2: make-listed-icp-buffer
;;;                          receive-next-icp-buffer-listed-if-any
;;;                          transmit-icp-buffer
;;;                          write-icp-byte-into-new-buffer
;;;                    INT4: make-and-install-network-icp-socket
;;;                          make-localnet-connection
;;; Prerequisites:   None.
;;; Side effects:    None.
;;; Non-local exits: None.
;;; Memory impact:   Allocates a 256-element simple vector of 16-bit ICP bytes and two
;;;                  gensym-conses.  This memory is reclaimed by
;;;                  release-listed-icp-buffer.

;;; Make-listed-icp-buffer returns a one-element list with an icp buffer with
;;; arbitrary contents.

(def-substitution-macro reclaim-if-variable-fill-icp-buffer (vector)
  (when vector
    (reclaim-variable-fill-icp-buffer vector)))

(defconser icp-buffer-ref-count int1)

(def-structure (icp-buffer
                 (:constructor make-icp-buffer-internal (icp-buffer-vector))
                 (:reclaimer reclaim-icp-buffer-internal)
                 #+development
                 (:print-function print-icp-buffer))
  (icp-buffer-next nil)
  (icp-buffer-start-byte 0)
  (icp-buffer-end-byte 0)
  (icp-buffer-vector nil :reclaimer reclaim-if-variable-fill-icp-buffer)
  (icp-buffer-vector-reference-count nil)) ; may be a cons

(defmacro make-icp-buffer (&optional vector)
  `(make-icp-buffer-internal ,(or vector `(make-variable-fill-icp-buffer))))

(def-system-variable recycled-icp-buffers INT2 nil)

(defun-void reclaim-icp-buffer (icp-buffer)
  (let ((ref (icp-buffer-vector-reference-count icp-buffer)))
    (when ref
      (cond ((=f 0 (decff (car ref)))
             (reclaim-icp-buffer-ref-count-cons ref))
            (t
             (setf (icp-buffer-vector icp-buffer) nil)))
      (setf (icp-buffer-vector-reference-count icp-buffer) nil)))
  (reclaim-icp-buffer-internal icp-buffer))

(defun-simple copy-icp-buffer (buffer)
  (let ((copy (make-icp-buffer (icp-buffer-vector buffer))))
    (setf (icp-buffer-start-byte copy) (icp-buffer-start-byte buffer))
    (setf (icp-buffer-end-byte copy) (icp-buffer-end-byte buffer))
    (let ((ref (icp-buffer-vector-reference-count buffer)))
      (unless ref
        (setq ref (icp-buffer-ref-count-cons 1 nil))
        (setf (icp-buffer-vector-reference-count buffer) ref))
      (incff (car ref))
      (setf (icp-buffer-vector-reference-count copy) ref))
    copy))

(defun-void ensure-icp-buffer-vector-writability (buffer ref)
  (when ref
    (decff (car ref))
    (setf (icp-buffer-vector-reference-count buffer) nil)
    (unless (=f 0 (car ref))
      (setf (icp-buffer-vector buffer)
            (copy-icp-buffer-vector
              (icp-buffer-vector buffer)
              (make-variable-fill-icp-buffer)
              (icp-buffer-start-byte buffer)
              (icp-buffer-end-byte buffer))))))

(defun-simple copy-icp-buffer-vector (buffer-vector copy-vector buffer-start buffer-end)
  (declare (type (simple-array (unsigned-byte 8) (*)) buffer-vector copy-vector))
  (loop for icp-byte-index from buffer-start below buffer-end
        do
    (setf (aref copy-vector icp-byte-index)
          (aref buffer-vector icp-byte-index)))
  copy-vector)

(defun-simple copy-icp-buffer-chain (buffer-chain)
  (when buffer-chain
    (loop with first-copy = (copy-icp-buffer buffer-chain)
          for previous-buffer = buffer-chain then buffer
          for buffer = (icp-buffer-next previous-buffer)
          while buffer
          for previous-copy = first-copy then copy
          for copy = (copy-icp-buffer buffer)
          do (setf (icp-buffer-next previous-copy) copy)
          finally (return first-copy))))

#+development
(defun print-icp-buffer (buffer stream depth)
  (declare (ignore depth))
  (printing-random-object (buffer stream)
    (format stream "ICP-BUFFER (~D)"
            (-f (icp-buffer-end-byte buffer) (icp-buffer-start-byte buffer)))))




;;;; ICP Ports

;;; Declaration:     icp-port
;;; Type:             G2 def-structure.
;;; Purpose:         Hold information about a single direction of ICP traffic.
;;; Slots:             > icp-connection-handle contains the platform-specific network
;;;                    socket.
;;;                  > parent-icp-socket is the ICP socket of which this is a port.
;;;                  > icp-port-direction is a symbol, either input or output.
;;;                  > receive-or-transmit-directly? is either t or nil.  This slot
;;;                    is set when the constructor function make-icp-port-structure
;;;                  > awaiting-callback? is non-nil if the ICP internals are
;;;                    communicating through this port, nil otherwise.
;;;                  > icp-port-registration-number is an ID for callback.
;;;                  > listed-icp-buffer-for-callback is a listed ICP buffer for ICP
;;;                    input ports.  (For the structure of a listed ICP buffer, see
;;;                    make-listed-icp-buffer in INT2.)  Despite its name, the
;;;                    listed-icp-buffer-for-callback slot can apparently store
;;;                    non-listed ICP buffers in ICP output ports when a write fails.
;;;                    (For further details, see transmit-icp-buffer in INT2.)
;;;                  > corresponding-icp-object-index-space-plist is a plist whose
;;;                    keys are symbols naming index spaces and whose values are
;;;                    index spaces.  For active ports, the first entry in this
;;;                    plist always pairs the key standard-icp-object-index-space
;;;                    with an index space.
;;;                  > icp-buffer-queue-head is never empty.  This slot is examined
;;;                    and modified only by an ICP handler (on the ICP message
;;;                    layer) or transmitter (on the ICP network I/O layer).
;;;                  > icp-buffer-queue-tail is modified only by an ICP receiver or
;;;                    writer and is examined only by an ICP handler (messages) or
;;;                    transmitter (network I/O).
;;;                  > number-of-icp-bytes-still-needed-for-message-series is
;;;                    examined and modified only by an ICP receiver (network I/O).
;;;                  > icp-buffer-with-end-of-message-group?  is modified only by an
;;;                    ICP receiver (network I/O) and is examined only by an ICP
;;;                    handler (messages).  It is for the last message group
;;;                    received.
;;;                  > icp-byte-index-of-end-of-message-group?  is modified only by
;;;                    an ICP receiver (network I/O) and is examined only by an ICP
;;;                    handler (messages).  It is for the last message group
;;;                    received.
;;;                  > number-of-icp-bytes-left-in-current-buffer is examined and
;;;                    modified only by an ICP handler (messages).
;;; Return behavior: No useful value.
;;; Users:             ICP internals.
;;; Prerequisites:   The macro def-structure must be defined.
;;; Side effects:    Defines a constructor macro make-icp-port-structure, which
;;;                  takes four arguments: icp-connection-handle, parent-icp-socket,
;;;                  icp-port-direction, and receive-or-transmit-directly?.  This
;;;                  constructor is internal to the ICP facility and should not be
;;;                  used elsewhere.  Defines a predicate icp-port-p.
;;; Non-local exits: None.
;;; Memory impact:   Compile-time consing only.
;;; Notes:           The public interface to ICP ports is through special binding of
;;;                  the system variable current-icp-port.  Also note that the
;;;                  values of the two slots icp-buffer-with-end-of-message-group?
;;;                  and icp-byte-index-of-end-of-message-group?  must not be used
;;;                  other than by the function
;;;                  process-next-icp-message-group-if-ready.

;;; A `ICP port' represents an ICP input or output link to another ICP node.

;;; The corresponding-icp-object-index-space-plist is a plist of the form:
;;;
;;;     ( { name-of-icp-object-index-space icp-object-index-space } ).
;;;
;;; Such a plist always begins with an entry for the ICP object index space
;;; named standard-icp-object-index-space.

(def-structure (icp-port
                 (:constructor
                   make-icp-port-structure
                   (icp-connection-handle
                     parent-icp-socket
                     icp-port-direction
                     receive-or-transmit-directly?))
                 (:reclaimer reclaim-icp-port-internal)
                 #+development
                 (:print-function print-icp-port))

  icp-connection-handle                                ; an input or output handle
  parent-icp-socket                                ; the ICP socket of which this is a port

  icp-port-direction                                ; INPUT or OUTPUT

  (icp-port-blocked? nil)                                ; t -> blocked on read for INPUT ports,
                                                ;   -> blocked on write for OUTPUT ports.

  receive-or-transmit-directly?

  (awaiting-callback? nil)

  (icp-buffer-for-callback nil)

  ;;corresponding-icp-object-index-space-plist
  (standard-icp-object-index-space
    nil
    :reclaimer reclaim-if-index-space)
  (item-index-space-1
    nil
    :reclaimer reclaim-if-index-space)
  (item-with-handle-index-space-1 ;  for input-ports only
    nil
    :reclaimer reclaim-if-index-space)
  (frame-serial-number-to-item-table-1  ; for g2 to g2 item registration
    nil
    :reclaimer reclaim-if-frame-serial-number-to-item-table)

  ;; The following slots are examined and modified only by an ICP handler or
  ;; transmitter.

  icp-buffer-queue-head                                ; the queue is never empty

  ;; The following slots are modified only by an ICP receiver or writer and are
  ;; examined only by an ICP handler or transmitter.

  icp-buffer-queue-tail

  ;; The following slots are examined and modified only by an ICP receiver.

  (number-of-icp-bytes-still-needed-for-message-series 0)

  ;; The following slots are modified only by an ICP receiver and are examined
  ;; only by an ICP handler.

  (icp-buffer-with-end-of-message-group? nil)        ; these are for the LAST message group
  (icp-byte-index-of-end-of-message-group? nil)        ;   received

  ;; The following slot is examined and modified only by an ICP handler.

  (number-of-icp-bytes-left-in-current-buffer 0)

  ;; The following is used for the final partial buffer in an icp-output-port.
  (icp-output-port-flush-list-entry nil :reclaimer nil-out-car-of-cons)

  (temporary-icp-object-index-space nil :reclaimer reclaim-if-index-space)
  )

(defun set-socket-debug-status (icp-socket status)
  (c-set-debug-status (icp-connection-handle (icp-input-port icp-socket)) status))

(defun-simple nil-out-car-of-cons (cons?)
  (when cons?
    (setf (car cons?) nil)))

(defun-simple item-index-space (icp-port)
  (or (item-index-space-1 icp-port)
      (setf (item-index-space-1 icp-port)
            (set-up-icp-object-index-space 'item-index-space))))

(defun-simple item-with-handle-index-space (icp-port)
  (or (item-with-handle-index-space-1 icp-port)
      (setf (item-with-handle-index-space-1 icp-port)
            (set-up-icp-object-index-space 'item-with-handle-index-space))))

(defun-simple register-item-with-handle-on-port (index item icp-port)
  (let ((index-space (item-with-handle-index-space icp-port)))
    (store-object-in-index-space
      index-space
      index
      (gensym-cons item (get-object-from-index-space-if-any index-space index)))))

(defun-simple deregister-item-with-handle-on-port (index item icp-port)
  (let ((index-space (item-with-handle-index-space icp-port)))
    (store-object-in-index-space
      index-space
      index
      (delete-gensym-element item (get-object-from-index-space-if-any index-space index)))))

(defun-simple items-registered-with-handle-on-port (index icp-port)
  (when (item-with-handle-index-space-1 icp-port)
    (get-object-from-index-space-if-any
      (item-with-handle-index-space icp-port)
      index)))

(defun-simple clear-items-registered-with-handle-on-port (index icp-port)
  (let ((index-space (item-with-handle-index-space icp-port)))
    (store-object-in-index-space index-space index nil)))

(defun-simple frame-serial-number-to-item-table (icp-port)
  (or (frame-serial-number-to-item-table-1 icp-port)
      (setf (frame-serial-number-to-item-table-1 icp-port)
            (make-frame-serial-number-to-item-table))))

;; The slots beyond icp-buffer-queue-tail could have been icp socket slots.

#+development
(defun print-icp-port (icp-port stream depth)
  (declare (ignore depth))
  (printing-random-object (icp-port stream)
    (format stream "ICP-PORT~@{ ~a~}" (icp-port-direction icp-port))))


;;; Declaration:     current-icp-port
;;; Type:             G2 system variable.
;;; Purpose:             Dynamically binds the ICP port currently in use.
;;; Value:           Either an icp-port or nil.
;;; Return behavior: N/A.
;;; Users:             ICP internals:
;;;                    INT1: functions defined by def-icp-object-type
;;;                          make-icp-port
;;;                    INT2: advance-and-read-icp-byte-if-any
;;;                          process-next-icp-message-group-if-ready
;;;                          handle-icp-messages
;;;                          writing-icp-message-group
;;;                          end-icp-message-series-if-any
;;;                    INT3: assign-corresponding-icp-object-index
;;;                          get-corresponding-icp-object
;;;                          store-corresponding-icp-object
;;;                          get-original-icp-object
;;;                          set-up-icp-object-index-space
;;;                          enlarge-corresponding-icp-object-index-space
;;;                          delete-icp-object-for-process
;;;                  Also used by GSI (modules GSI, GSI-COMMON), GSPAN, G2-to-G2
;;;                  communication (G2DS).
;;; Prerequisites:   Must be referenced inside the scope of with-system-variables.
;;; Side effects:    N/A.
;;; Non-local exits: N/A.
;;; Memory impact:   Special variable binding.

(def-system-variable current-icp-port INT1 nil)



;;; Declaration:     current-icp-socket
;;; Type:             G2 system variable.
;;; Purpose:             Dynamically binds the ICP socket currently in use.
;;; Value:           Either an icp-socket or nil.
;;; Return behavior: N/A.
;;; Users:             ICP internals:
;;;                    INT2: advance-and-read-icp-byte-if-any
;;;                          process-next-icp-message-group-if-ready
;;;                          writing-icp-message-group
;;;                          end-icp-message-group
;;;                    INT3: i-am-alive
;;;                          message-group-id
;;;                          connection-denied
;;;                          connection-shutdown-imminent
;;;                  Also used by GSI (modules GSI-COMMON and GSI), Telewindows and
;;;                  G2 printing (WINDOWS1, TELESTUBS), G2 remote procedures
;;;                  (G2-RPC1 and G2-RPC2), G2 foreign functions (G2-FOREIGN),
;;;                  GSPAN, G2-to-G2 communication (G2DS, G2DS-NUPEC).
;;; Prerequisites:   Must be referenced inside the scope of with-system-variables.
;;; Side effects:    N/A.
;;; Non-local exits: N/A.
;;; Memory impact:   Special variable binding.

(defvar current-icp-socket nil)


(defmacro index-space-name-for-item-index-space-for-icp-socket (icp-socket direction)
  (let ((icp-socket-var (make-symbol "ICP-SOCKET")))
    `(let ((,icp-socket-var ,icp-socket))
       (cond (inhibit-corresponding-icp-object-making
              'standard-icp-object-index-space)
             ((runtime-current-system-case
                (ab (eq 'g2 (icp-socket-listener-client? ,icp-socket-var)))
                (t nil))
              (if (eq ,direction 'output)
                  'item-index-space
                  (with-bifurcated-version
                      (no-frame-serial-index-space-icp-version ,icp-socket-var)
                    'frame-serial-number
                    'item-index-space)))
             (t
              (with-bifurcated-version
                  (item-index-space-icp-version ,icp-socket-var)
                'standard-icp-object-index-space
                'item-index-space))))))

(defmacro index-space-name-for-icp-socket (index-space-name icp-socket direction)
  `(case ,index-space-name
     (standard-icp-object-index-space
      'standard-icp-object-index-space)
     (item-index-space
      (index-space-name-for-item-index-space-for-icp-socket ,icp-socket ,direction))
     (frame-serial-number
      (if (eq ,direction 'output)
          'item-index-space
          'frame-serial-number))
     (t ; maybe warn, in development?
      'standard-icp-object-index-space)))

(defmacro index-space-name-for-icp-port (index-space-name icp-port)
  (let ((port (make-symbol "PORT")))
    `(let ((,port ,icp-port))
       (index-space-name-for-icp-socket
         ,index-space-name (parent-icp-socket ,port) (icp-port-direction ,port)))))

(defmacro index-space-for-icp-port (converted-index-space-name icp-port)
  `(case ,converted-index-space-name
     (standard-icp-object-index-space
      (standard-icp-object-index-space ,icp-port))
     (item-index-space
      (item-index-space ,icp-port))
     (frame-serial-number
      (frame-serial-number-to-item-table ,icp-port))))

;;; Declaration:     current-standard-icp-object-index-space
;;; Type:             G2 system variable.
;;; Purpose:         Dynamically binds the default index space for reading ICP
;;;                  objects.
;;; Value:               This is a symbol, typically bound to
;;;                  standard-icp-object-index-space.
;;; Return behavior: N/A.
;;; Users:             ICP internals:
;;;                    INT1: functions defined by def-icp-message-type
;;;                    INT2: process-next-icp-message-group-if-ready
;;; Prerequisites:   Must be referenced inside the scope of with-system-variables.
;;; Side effects:    N/A.
;;; Non-local exits: N/A.
;;; Memory impact:   Special variable binding.

(def-system-variable current-standard-icp-object-index-space INT1 nil)
(def-system-variable current-temporary-icp-object-index-space INT1 nil)

(defun-simple get-from-icp-port (icp-port icp-object-index
                                 name-of-corresponding-icp-object-index-space)
  (let* ((index-space-name (index-space-name-for-icp-port
                             name-of-corresponding-icp-object-index-space
                             icp-port))
         (index-space (index-space-for-icp-port index-space-name icp-port)))
    (if (eq index-space-name 'frame-serial-number)
        (get-item-from-frame-serial-number icp-object-index index-space)
        (get-object-from-index-space index-space icp-object-index))))

(defun-simple get-from-icp-port-if-any (icp-port icp-object-index
                                        name-of-corresponding-icp-object-index-space)
  (let* ((index-space-name (index-space-name-for-icp-port
                             name-of-corresponding-icp-object-index-space
                             icp-port))
         (index-space (index-space-for-icp-port index-space-name icp-port)))
    (if (eq index-space-name 'frame-serial-number)
        (get-item-from-frame-serial-number icp-object-index index-space)
        (get-object-from-index-space-if-any index-space icp-object-index))))

(defun-simple set-in-icp-port (icp-port icp-object-index name-of-corresponding-icp-object-index-space
                                        new-value)
  (let* ((index-space-name (index-space-name-for-icp-port
                             name-of-corresponding-icp-object-index-space
                             icp-port))
         (index-space (index-space-for-icp-port index-space-name icp-port)))
    ;; we are assuming there is no existing entry here.  Otherwise, some cleanup is required.
    (if (eq index-space-name 'frame-serial-number)
        (setf (get-item-from-frame-serial-number icp-object-index index-space) new-value)
        (setf (get-object-from-index-space index-space icp-object-index) new-value))))

(defsetf get-from-icp-port set-in-icp-port)



;;; Make-icp-port makes a new ICP port, initialized with a queue containing a
;;; single ICP buffer that appears to already have been processed.

(defun make-icp-port
       (icp-connection-handle parent-icp-socket icp-port-direction
        receive-or-transmit-directly?)
  (let* ((current-icp-port
           (make-icp-port-structure
             icp-connection-handle parent-icp-socket
             icp-port-direction receive-or-transmit-directly?))
         (icp-buffer (make-icp-buffer)))
    (setf (standard-icp-object-index-space current-icp-port)
          (set-up-icp-object-index-space 'standard-icp-object-index-space))
    (setf (icp-buffer-queue-head current-icp-port) icp-buffer)
    (setf (icp-buffer-queue-tail current-icp-port) icp-buffer)
    (when (eq icp-port-direction 'input)
      (setf (icp-port-blocked? current-icp-port) 'initial))
    current-icp-port))



(defvar do-not-reclaim-runs-while-inactive-entries nil)

;; There is currently no need to put name-of-function-to-set-access-form on a
;; property of icp-object-type since it is called directly from function to
;; reclaim icp port entry.  Make property for this if necessary.
(defun reclaim-icp-object-map
       (icp-object icp-object-map
        name-of-corresponding-icp-object-index-space)
  (loop for map-tail = icp-object-map then next-map-tail
        while map-tail
        for next-map-tail = (cddr map-tail)
        for (icp-port index) = map-tail
        do
    (unless (and do-not-reclaim-runs-while-inactive-entries
                 (icp-socket-runs-while-inactive
                   (parent-icp-socket icp-port)))
      (reclaim-index-space-location-and-corresponding-objects
        icp-object icp-port index name-of-corresponding-icp-object-index-space))))



(defun-void reclaim-icp-port-entry
       (icp-port icp-object
        icp-object-map name-of-function-to-set-object-map)
  (loop as map-entry-tail = nil then rest-of-map-entries
        for rest-of-map-entries
            on icp-object-map
            by 'cddr
        do
    (when (eq (car rest-of-map-entries) icp-port)
      (if map-entry-tail
          (setf (cddr map-entry-tail) (cddr rest-of-map-entries))
          (funcall name-of-function-to-set-object-map
                   icp-object (cddr rest-of-map-entries)))
      (reclaim-gensym-cons (cdr rest-of-map-entries))
      (reclaim-gensym-cons rest-of-map-entries)
      (return nil))))




(defvar icp-output-ports-to-flush nil)

(defvar with-icp-buffer-coelescing-scope? nil)

(defmacro with-icp-buffer-coelescing-scope (&body forms)
  `(let ((outer-with-icp-buffer-coelescing-scope?
           with-icp-buffer-coelescing-scope?)
         (with-icp-buffer-coelescing-scope? t))
     (unless outer-with-icp-buffer-coelescing-scope?
       (when icp-output-ports-to-flush
         (flush-icp-output-ports)))
     (prog1 (progn
              ,@forms)
       (unless outer-with-icp-buffer-coelescing-scope?
         (when icp-output-ports-to-flush
           (flush-icp-output-ports))))))

(def-bombout-clean-up-function 'flush-icp-output-ports)

(defun-void flush-icp-output-ports ()
  (when icp-output-ports-to-flush
    (with-temporary-profiling-context icp
      (let ((ports-to-flush icp-output-ports-to-flush))
        (setq icp-output-ports-to-flush nil)
        (loop for icp-output-port? in ports-to-flush
              do
          (when icp-output-port?
            (setf (icp-output-port-flush-list-entry icp-output-port?) nil)
            (transmit-icp-output-if-ready icp-output-port? t)))
        (reclaim-gensym-list ports-to-flush)))))



(defvar disable-resumability nil)

(defvar *resumable-icp-state* nil)

(defvar icp-suspend (list 'suspend))

(defmacro defun-resumable-icp-function (name args &body body)
  (make-defun-simple-resumable-icp-function 'defun name args body))

(defmacro defun-simple-resumable-icp-function (name args &body body)
  (make-defun-simple-resumable-icp-function 'defun-simple name args body))

(defmacro defun-void-resumable-icp-function (name args &body body)
  (make-defun-simple-resumable-icp-function 'defun-simple name args `(,@body nil))) ; not defun-void!

(defvar-for-macro trif-current-name nil)
(defvar-for-macro recompile-resumable-icp-function-p nil)

#+development
(defvar-for-macro defun-simple-resumable-icp-function-table
  (make-hash-table))

#+development
(defun-for-macro save-defun-simple-resumable-icp-function (defun name args body)
  (setf (gethash name defun-simple-resumable-icp-function-table)
        `(,defun ,name ,args ,body))
  name)

#+development ; use this after changing transform-resumeable-icp-form or some macro
(defun-for-macro recompile-resumable-icp-functions ()
  (let ((names nil)
        length)
    (maphash #'(lambda (name form)
                 (declare (ignore form))
                 (pushnew name names))
             defun-simple-resumable-icp-function-table)
    (format t "~&recompiling ~D functions~%" (setq length (length names)))
    (loop for name in (sort names #'string<)
          for count from 1
          do
      (recompile-resumable-icp-function name)
      (when (zerop (mod count 10))
        (format t "~D " count)))
    (if (zerop (mod length 10))
        (format t "~&")
        (format t "~D~&" length))
    (values)))

#+development
(defun-for-macro recompile-resumable-icp-function (name)
  (let* ((recompile-resumable-icp-function-p t)
         #+lucid  (lcl:*redefinition-action* nil)
         (form (apply #'make-defun-simple-resumable-icp-function
                      (gethash name defun-simple-resumable-icp-function-table)))
         (name (cadr form)))
    (eval form)
    (compile name))
  name)

(defun-for-macro make-defun-simple-resumable-icp-function (defun name args body)
  (loop for arg in args
        when (memq arg '(&rest &key &aux))
          do (error "make-defun-simple-resumable-icp-function does not handle lambda-list-keywords: ~S"
                    arg))
  (let ((trif-current-name name))
    (multiple-value-bind (doc-and-decl-forms body-after-doc-and-decl?)
        (split-defun-body body)
      (let* ((resumable-body
               `(let ((resumable-icp-state-1 *resumable-icp-state*)
                      (icp-suspend-1 icp-suspend))
                  resumable-icp-state-1
                  icp-suspend-1
                  (macrolet ((resumable-icp-state ()
                               '(when resumable-icp-state-1 *resumable-icp-state*)))
                    (when (resumable-icp-state)
                      (let ((top (resumable-icp-pop)))
                        (unless (eq ',name top)
                          (return-from ,name
                            (icp-error "resumable icp synch error: ~S expected, ~S found"
                                       ',name top)))))
                    ,(transform-resumeable-icp-form
                       `(let* ,(loop for arg in args
                                     for var = (if (consp arg) (car arg) arg)
                                     unless (eq var '&optional)
                                       collect `(,var ,var))
                          ,@body-after-doc-and-decl?)
                       'values
                       `((resumable-icp-push ',name)
                         (return-from ,name icp-suspend)))
                    )
                  ))
             (form `(,defun ,name ,args
                      ,@doc-and-decl-forms
                      #-disable-resumability-optimization
                      (if disable-resumability
                          (progn ,@body-after-doc-and-decl?)
                          ,resumable-body)
                      #+disable-resumability-optimization
                      ,resumable-body)))
        (if recompile-resumable-icp-function-p
            form
            `(progn
               #+development
               (save-defun-simple-resumable-icp-function ',defun ',name ',args ',body)
               ,@(unless (eval-feature :no-macros)
                   `((eval-when (:compile-toplevel :load-toplevel :execute)
                       (note-defun-resumable-icp-function
                         ',name ,@(when (eq defun 'defun-simple) `(1))))))
               ,form))
        
        
        ))))

#-no-macros
(eval-when (:compile-toplevel :load-toplevel :execute)

(loop for type in resumable-icp-value-types
      for reader = (intern (format nil "READ-ICP-~A" type))
      for writer = (intern (format nil "WRITE-ICP-~A" type))
      do
  (note-defun-resumable-icp-function reader 1)  ; returns 1 value
  (note-defun-resumable-icp-function writer 1)) ; returns 1 value

(loop for name in
      '(peek-icp-byte read-icp-byte-if-any define-icp-tree-remotely
        read-acknowledge-icp-version-info read-icp-double-float-1
        read-icp-fill-bytes read-initial-icp-version-info send-icp-enlarge-corresponding-icp-object-index-space
        send-icp-intern send-icp-intern-keyword send-initial-icp-version-info write-acknowledge-icp-version-info
        write-icp-double-float-1 write-icp-fill-bytes write-initial-icp-version-info
        define-or-configure-gsi-sensor send-icp-define-gsi-interface
        send-all-image-data send-icp-begin-making-graph-rendering send-icp-begin-making-icon-rendering
        send-icp-begin-making-image-data send-icp-define-gensym-window send-icp-make-tiling-pattern
        send-icp-define-telewindows-workstation
        send-icp-define-remote-procedure-identifier send-icp-define-remote-procedure-name
        g2-read-icp-attribute-for-list-of-attributes g2-write-icp-list-of-attributes
        send-icp-define-nupec-synchronize-variable-or-parameter
        send-icp-g2ds-define-variable
        read-icp-suspend read-sequence-into-gsi-item write-sequence-from-gsi-item
        write-gsi-history-specification read-gsi-history-specification
        write-gsi-history read-gsi-history read-gsi-effective-data-type-into-item
        write-icp-gsi-values read-gsi-value-structure write-gsi-value-structure
        gsi-register-item icp-error-internal check-class-for-item-passing
        write-icp-maybe-suspend)
      do
  (note-defun-resumable-icp-function name 1))

(loop for name in
      '(allocate-byte-vector allocate-evaluation-sequence allocate-evaluation-structure
        assign-index-in-index-space car cdr cddr convert-value-to-gsi-value
        copy-text-string eql get-history-g2-time gensym-cons-1
        handler-for-enlarge-corresponding-icp-object-index-space
        import-text-string intern-text-string last length lengthw wide-string-length lookup-index-in-index-space
        lookup-or-create-item-from-reference-attributes
        make-gsi-instance make-transient-item not null obtain-simple-gensym-string
        obtain-text-string set-value-for-network-slot-description truncate
        char-int code-char gensym-string-substring gensym-string-to-wide-string make-unique-slot-name-symbol
        notify-user-if-possible reclaim-gensym-string reclaim-text-string schar values
        abs atom caar ceiling char char= characterp consp copy-illegal-gensym-string-without-bad-characters
        enlarge-index-space eq error export-text-string expt floatp icp-cons-1 integerp log
        obtain-long-enough-adjustable-gensym-string reclaim-s-expression-for-remote-eval
        reclaim-text-or-gensym-string set-up-icp-object-index-space store-corresponding-icp-object svref
        symbol-name-text-string symbol-plist symbolp symbol-package text-string-p text-string-substring
        twrite-ascii-from-gensym-string wide-string-p wide-string-to-gensym-string
        c-get_encoded_unix_time encode-unix-time-after-failure get-gsi-interface-for-gsi-sensor-if-any
        get-icp-object-index-for-sensor gsi-list-3 gsi-cons-1 corresponding-icp-object-map-for-sensor
        reclaim-icp-object-map-for-sensor get-icp-object-index-for-gsi-icp-interface
        - cerror copy-tree-using-gensym-conses-1 first second graphics-cons-1 gsi-list-trace-hook
        make-rendering-structure managed-float-reclaim-error mutate-gensym-plist
        reclaim-byte-vector reclaim-gensym-list-1 reclaim-gensym-tree-1 reclaim-gsi-value-vector
        reclaim-icp-list-element reclaim-if-managed-array reclaim-if-managed-float
        reclaim-managed-array reclaim-managed-simple-float-array-function round-post4.0-managed-float
        cadr convert-gsi-value-to-value ensure-item-copy-index-space eval-cons-1
        get-corresponding-icp-object get-network-slot-description-list
        get-user-slot-value-for-network-slot-description get-value-for-network-slot-description
        gsi-allocate-managed-array gsi-managed-array-length icp-list-2 icp-list-trace-hook
        icp-out-of-synch make-network-slot-description-for-class-description
        network-item-reference-information reclaim-evaluation-value reclaim-icp-list-1
        reclaim-ignored-rpc-argument-list reclaim-index-space-1 frame-has-been-reprocessed-p-function
        set-icp-object-index-for-registered-item simple-vector-p validate-item-or-evaluation-value
        * + / = > allocate-managed-array define-external-simulation-object g2ds-cons-1
        generate-designation-for-block get-history-value-for-cascaded-ring-buffer
        get-total-cascaded-ring-buffer-length increment-active-element-index-for-cascaded-ring-buffer
        make-icp-list-1 reclaim-eval-tree-1 reclaim-g2ds-data-value reclaim-g2ds-expression
        reclaim-if-evaluation-value-1 reclaim-list-of-foreign-function-registrations
        reclaim-nupec-designation reclaim-nupec-history-block reclaim-wide-string typep
        check-for-exceptional-float c-partition_float c-partition_long reclaim-remote-value
        evaluation-value-type class-for-gsi-item gsi-item-is-value-p make-gsi-sequence make-gsi-structure
        gsi-make-attributes-for-user-or-gsi intern-list get-from-icp-port store-corresponding-item
        make-interned-list-for-remote-procedure-item-passing-info
        change-attribute-description-evaluation-value gsi-simple-content-copy-internal
        gsi-special-attribute-p reclaim-gsi-instance get-attribute-description-evaluation-value
        get-attribute-description-list-for-interned-list gsi-option-is-set-p
        intern-class-and-attribute-list nconc third emit-icp-write-trace end-icp-message-series-if-any
        intern-attributes-of-structure intern-attributes-of-gsi-structure stringp memq-function
        intern-property-names-of-plist make-gsi-history gsi-error gsi-attribute-qualified-name
        gensym-string-to-wide-string-for-gsi wide-string-to-gensym-string-for-gsi gsi-warning
        set-icp-object-index-for-gsi-instance assq-function gsi-push-onto-appropriate-list
        gsi-sensor-index make-transient-frame-for-item-passing activate-item array-or-list-element-type-suitable-p
        element-type-for-gsi-type set-gsi-instance-value-type gsi-make-appropriate-array
        inline-restore-lisp-text-string make-gsi-history-from-specification fourth fifth
        add-vectors-to-gsi-history valid-wide-string-length-bv16 gsi-receive-value-for-gsi-sensor-1
        transfer-wrapper-components make-gsi-rpc-argument-list register-item-with-handle-on-port
        handle-missing-class-in-rpc check-class-for-item-passing-1 interned-list-p-function
        gsi-get-interned-slot-names-for-item-passing get-default-class-for-missing-class
        get-interned-slot-names-for-item-passing-from-class-description get-from-icp-port-if-any
        remote-procedure-item-info-included-attributes
        remote-procedure-item-info-excluded-attributes
        remote-procedure-item-info-included-system-attributes
        remote-procedure-item-info-include-all-system-attributes
        remote-procedure-item-info-include-all-system-attributes-except
        remote-procedure-item-info-kind
        get-icp-object-index-for-gsi-instance get-icp-object-index-for-registered-item nthcdr
        framep-function intern-list-of-item-reference-attributes gsi-call-receive-registration-callback
        change-attribute-description-evaluation-value-for-icp get-gsi-instance-plist-value
        tformat-text-string change-slot-value g2-array-aref-item-or-evaluation-value mutate-g2-array
        g2-list-length replace-g2-list-element maybe-insert-g2-list-element-at-end
        #-Lockfree-List g2-list-structure-next
        activate-item-if-necessary item-references-enabled-p gsi-make-array-for-user-or-gsi
        make-gsi-attribute-for-user-or-gsi set-gsi-attribute-name initialize-gsi-data-service
        note-allocate-cons note-reclaim-cons get-remote-icp-version-info-value
        info-for-write-icp-symbol-as-value-type maybe-set-connection-name
        delete-frame-for-rpc g2-list-empty-p delete-frame
        remove-g2-list-element-structure g2-list-last intern-text-string-for-icp
        reclaim-managed-simple-float-array copy-frame-serial-number
        default-owner-for-gsi-objects
        remote-side-supports-transparent-color-index-p make-remote-procedure-item-info-old
        remote-side-supports-dialog-component-with-font-p
        remote-side-supports-font-in-grid-view-p
        list-of-nil-p icp-message-functions-icp-prologue
        write-icp-compressed-image-data-chunk read-icp-compressed-image-data-chunk
        handle-too-long-icp-wide-string
        gensym-encode-unix-time-as-managed-float
        gensym-encode-unix-time-as-gensym-float
        reclaim-managed-simple-float-array-of-length-1)
      do
  (note-defun-resumable-icp-function name nil)) ; not resumable

)

(defun-for-macro make-concatenated-name (prefix name)
  (intern (format nil "~A~A" prefix name)))

(defmacro resumable-icp-call (form)
  form)

(defmacro non-resumable-icp-call (form)
  form)

(defmacro resumable-icp-form (form)
  form)

(defmacro non-resumable-icp-form (form)
  form)

;read-evaluation-structure-from-list
(defmacro with-reclaimable-icp-value ((variable form) &body body)
  `(let ((,variable ,form))
     ,@body))

(defmacro with-icp-assertion ((assertion error-format-control-string &rest error-arguments)
                              &body body)
  `(if ,assertion
       (progn ,@body)
       (icp-resumable-error ,error-format-control-string ,@error-arguments)))

;macros with function-like semantics
;  not including defconser macros, defstruct macros, and substitution macros
(defparameter-for-macro trif-macroexpand-function-macros
  '(*e *f +e +f +r -e -f -r /=f /e 1+f 1-f <=f <e <f <r =e =f >=f >e >f
    allocate-managed-float allocate-managed-float-box-macro ashf byte-mask-for-bit
    byte-vector-16-aref byte-vector-aref byte-vector-aset byte-vector-index
    managed-long-value long-vector-aref allocate-managed-long
    byte-vector-length cached-managed-float-value car-of-cons cdr-of-cons charw charw-bv16
    class class-description class-description-of-class-p class-description-slot
    class-description-subclass-of-class-description-p code-wide-character
    coerce-fixnum-to-gensym-float coerce-to-gensym-float convert-unix-time-to-gensym-time
    current-value-of-variable-or-parameter double-float-vector-p estructure-first-attribute-index
    evaluation-float-p evaluation-float-value evaluation-long-p evaluation-long-value
    evaluation-integer-p evaluation-integer-value evaluation-sequence-first-element-index
    evaluation-sequence-value long-vector-p long-vector-length cached-managed-long-value
    evaluation-structure-value evaluation-symbol-symbol evaluation-text-p
    evaluation-text-value evaluation-truth-value-value evaluation-unsigned-vector-16-value
    expiration-time-of-current-value fixnump
    float-vector-aset float-vector-length float-vector-p floore-first floorf floorf-positive format
    frame-of-class-p frame-or-value-object-passing-info? funcall
    g2-type-name-of-named-simple-vector gensym-float-p gensym-float-type
    get-gensym-plist-element get-icp-plist-element get-object-map-for-icp-tree
    get-original-icp-object get-slot-value-if-any getfq glength gsi-managed-svref
    icp-connection-supports-wide-strings? icp-warning
    icp-object-map-for-registered-item-general length-of-simple-string icp-object-map-for-registered-item
    length-of-simple-vector logandf logiorf make-evaluation-float make-evaluation-integer
    make-evaluation-symbol make-evaluation-text-reclaiming-argument make-evaluation-truth-value
    make-evaluation-unsigned-vector-16 make-object-passing-info managed-array-length managed-float-value
    managed-svref minf mutate-float-vector mutate-managed-float-value neq object-passing-info? pluspf
    reconstruct-float reconstruct-long mutate-long-vector mutate-managed-long-value
    set-frame-or-value-object-passing-info? set-gensym-plist-element
    set-icp-object-map-for-registered-item set-icp-object-map-for-registered-item-general
    set-icp-plist-element set-value-object-passing-info? setf-object-passing-info?
    simple-gensym-string-p stringpw symbol-plist-for-lookup time-of-most-recent-value
    value-object-passing-info? variable-or-parameter-stored-histories? variable-p wide-character-code
    simple-character-code-p currently-legal-character-following-@
    map-to-roman-font-special-character-code-if-any convert-simple-character-to-ascii
    get-gensym-plist-element svref corresponding-icp-object-map-for-symbol
    char remote-icp-version-info frame-serial-number gsi-instance-class-type
    managed-array-p gsi-attribute-count gsi-attributes gsi-element-count gsi-instance-class
    gsi-instance-name gsi-instance-value-type interned-list--attribute-list interned-list--class
    resumable-attribute-base-name resumable-attribute-class-qualifier?
    second-of-long-enough-list set--gsi-instance-name set-resumable-attribute-base-name
    set-resumable-attribute-class-qualifier? third-of-long-enough-list
    trace-write-icp-message-series-p gsi-instance-timestamp memq
    maximum-icp-byte-unsigned-integer maximum-icp-large-integer-byte-count
    gsi-instance-history remote-value-reclaim-converted-value gensym-string-p
    simplify-gsi-attribute-spec feature-assq assq gsi-typed-array-ref set--gsi-element-count
    gsi-coerce-symbol-array-element-to-symbol byte-vector-16-p unsigned-byte-16-vector-p
    reclaim-icp-cons evaluation-value-to-category-function gsi-instance-class-type
    remote-procedure-item-passing-info-varargs-p remote-procedure-item-passing-info-item-info-list
    gsi-attribute-is-transient-p icp-object-map-for-gsi-instance gsi-instance-timestamp
    evaluation-sequence-length halff gsi-item-reference-flag-value g2-array-element-type
    list-type list-structure g2-list-structure-head g2-array-length current-frame-serial-number
    gsi-attributes gsi-attribute-count role-serve-inactive-objects?
    gsi-item-name-is-identifying-flag-value
    gsi-item-class-is-identifying-flag-value gsi-attribute-is-identifying-p
    byte-vector-16-length byte-vector-16-aref maybe-make-evaluation-unsigned-vector-16
    ))

(defparameter-for-macro trif-macroexpand-body-macros
  '(declare-ignorable-icp-arguments potentially-rigorous-operation
    with-current-gensym-string with-temporary-bignum-creation
    twith-output-to-gensym-string with-permanent-gensym-float-creation))

(defparameter-for-macro trif-macroexpand-1-ignored-arg+body-macros
  '(tracing-icp-reads tracing-icp-writes
    with-backtrace-for-internal-error
    with-backtrace-for-internal-error-simple with-backtrace-for-internal-error-complex
    with-temporary-gensym-float-creation with-icp-assertion))

(defparameter-for-macro trif-macroexpand-1-evaluated-arg+body-macros
  '(with-designated-current-gensym-string))

(defparameter-for-macro trif-macroexpand-approved-system-macros
  '(and case cond ab-lisp::or prog1 return unless when))

(defparameter-for-macro trif-macroexpand-approved-ab-macros
  '(body-of-read-icp-unsigned-integer body-of-write-icp-unsigned-integer
    loop-body-of-read-icp-list-of-attributes
    loop loop-tagbody read-icp-gensym-string-body
    read-icp-raw-gensym-string-body provide-legal-gensym-string
    with-bifurcated-version-for-input with-bifurcated-version-for-output
    if-chestnut-gsi current-system-case runtime-current-system-case fixnum-case
    or loop-finish gensym-dstruct-bind evaluation-typecase
    partition-float partition-long
    with-attributes-for-item-copy with-item-index-space with-icp-item
    make-remote-value remote-value-value make-remote-value-for-current-system
    remote-value-typecode remote-value-typep remote-value-typecase
    remote-value-for-current-system-typecase
    read-icp-terminated-list read-icp-terminated-list-of-pairs
    evaluation-value-cdr-marker if-chestnut read-optional-remote-value-typetag
    write-optional-remote-value-typetag peek-optional-remote-value-typetag
    upgrade-type-for-sequence-element upgrade-type-for-sequence-element-internal
    read-icp-evaluation-sequence-body write-icp-evaluation-sequence-body
    with-remote-procedure-info icp-error read-icp-corresponding-icp-object-index
    write-icp-corresponding-icp-object-index
    ready-to-suspend-icp-writing-p suspend-icp-writing
    with-icp-write-buffer-non-resumable write-icp-item-reference-1
    with-disabled-write-icp-suspension
    with-appropriate-version))

(defparameter-for-macro trif-macroexpand-approved-setf-macros
  '(aref byte-vector-aref car cdr char charw charw-bv16 corresponding-icp-object-map-for-sensor
    eq-gethash frame-or-value-object-passing-info get-gensym-plist-element
    get-icp-plist-element get-object-map-for-icp-tree gsi-managed-svref icp-byte-aref
    icp-object-map-for-registered-item managed-svref object-passing-info schar svref the
    type-of-foreign-function-call value-object-passing-info
    corresponding-icp-object-map-for-symbol gsi-instance-timestamp gsi-instance-class-type
    remote-icp-version-info gsi-instance-name resumable-attribute-base-name
    resumable-attribute-class-qualifier? second third gsi-instance-history
    gsi-instance-value-type gsi-element-count gsi-typed-array-ref
    gsi-item-reference-flag-value gsi-attributes gsi-attribute-count
    role-serve-inactive-objects? gsi-item-name-is-identifying-flag-value
    gsi-item-class-is-identifying-flag-value long-vector-aref
    gsi-attribute-is-identifying-p byte-vector-16-aref))


(defun-for-macro macroexpand-or (forms)
  (cond ((null forms)
         nil)
        ((null (cdr forms))
         (car forms))
        (t
         (let ((value (make-symbol "VALUE")))
           `(let ((,value ,(car forms)))
              (if ,value
                  ,value
                  ,(macroexpand-or (cdr forms))))))))

(defun-for-macro trif-macroexpand-1 (form)
  (multiple-value-bind (new-form expandedp)
      (case (and (consp form) (car form))
        (or (values (macroexpand-or (cdr form)) t))
        (t  (macroexpand-1 form)))
    (when expandedp
      (cond ((or (function-call-macro-p (car form))
                 (memq (car form) trif-macroexpand-approved-system-macros)
                 (memq (car form) trif-macroexpand-approved-ab-macros)))
            ((eq (car form) 'setf)
             (let ((locations
                     (loop for (location value) on (cdr form) by 'cddr
                           when (consp location)
                             collect (car location))))
               (when locations
                 (format t "~&trif-macroexpand-1 ~S: setf ~S~%"
                         trif-current-name locations))))
            (t
             (format t "~&trif-macroexpand-1 ~S: ~S~%"
                     trif-current-name (car form)))))
    (values new-form expandedp)))

(defun-for-macro split-declarations-from-body (body)
  (let ((real-body (loop for tail on body
                         while (and (consp (car tail)) (eq (caar tail) 'declare))
                         finally (return tail))))
    (values real-body (ldiff body real-body))))

(defun-for-macro check-resumable-icp-form-list-p (form-list)
  (loop for form in form-list
        when (check-resumable-icp-form-p form)
          return t))

(defun-for-macro check-resumable-icp-form-p (form)
  (if (atom form)
      nil
      (case (car form)
        ((resumable-icp-call resumable-icp-form with-icp-assertion)
         t)
        ((non-resumable-icp-form trace-icp-message)
         nil)
        ((macrolet symbol-macrolet progv catch throw unwind-protect flet labels)
         (warn "check-resumable-icp-form-p ~S: ~S" trif-current-name form)
         nil)
        ((function)
         (if (symbolp (cadr form))
             nil
             (progn
               (warn "check-resumable-icp-form-p ~S: ~S" trif-current-name form)
               nil)))
        ((progn if ab-lisp::if tagbody setq non-resumable-icp-call)
         (check-resumable-icp-form-list-p (cdr form)))
        ((block the multiple-value-bind return-from eval-when)
         (check-resumable-icp-form-list-p (cddr form)))
        ((go quote declare) nil)
        ((let ab-lisp::let let* ab-lisp::let*)
         (or (loop for binding in (cadr form)
                   for value = (and (consp binding) (cadr binding))
                   when (check-resumable-icp-form-p value)
                     return t)
             (check-resumable-icp-form-list-p (cddr form))))
        ((incff incff-1 decff decff-1)
         (when (check-resumable-icp-form-list-p (cdr form))
           (warn "check-resumable-icp-form-p ~S: problem ~S" trif-current-name form))
         nil)
        ((setf)
         (cond ((null (cdr form))
                nil)
               ((cdddr form)
                (check-resumable-icp-form-p
                  `(progn ,@(loop for (location value) on (cdr form) by 'cddr
                                  collect `(setf ,location ,value)))))
               ((symbolp (cadr form))
                (check-resumable-icp-form-p (caddr form)))
               (t
                (when (check-resumable-icp-form-p (cadr form))
                  (warn "check-resumable-icp-form-p ~S: setf problem ~S" trif-current-name (cadr form)))
                (check-resumable-icp-form-p
                  (if (or (function-call-accessor-macro-p (caadr form))
                          (memq (caadr form) trif-macroexpand-approved-setf-macros))
                      (caddr form)
                      (trif-macroexpand-1 form))))))
        ((case fixnum-case)
         (or (check-resumable-icp-form-p (cadr form))
             (loop for (key-or-keys . forms) in (cddr form)
                   thereis (check-resumable-icp-form-list-p forms))))
        (t
         (cond ((symbolp (car form))
                (let ((resumablep (get (car form) 'resumable-icp-form 'unknown)))
                  (cond ((not (eq resumablep 'unknown))
                         (or resumablep
                             (check-resumable-icp-form-list-p (cdr form))))
                        ((or (memq (car form) trif-macroexpand-function-macros)
                             (memq (car form) trif-macroexpand-body-macros)
                             (memq (car form) trif-macroexpand-1-evaluated-arg+body-macros))
                         (check-resumable-icp-form-list-p (cdr form)))
                        ((memq (car form) trif-macroexpand-1-ignored-arg+body-macros)
                         (check-resumable-icp-form-list-p (cddr form)))
                        (t
                         (multiple-value-bind (new-form expandedp)
                             (trif-macroexpand-1 form)
                           (if expandedp
                               (check-resumable-icp-form-p new-form)
                               (or (check-resumable-icp-form-list-p (cdr form))
                                   (progn
                                     (note-function-call-of-unknown-resumability (car form))
                                     'unknown))))))))
               ((and (consp (car form))
                     (eq (caar form) 'lambda)
                     (consp (cadar form))) ; and no lambda-list keywords
                (check-resumable-icp-form-p
                  `(let ,@(loop for parameter in (cadar form)
                                for argument in (cdr form)
                                collect `(,parameter ,argument))
                        ,@(cddar form))))
               (t
                (warn "check-resumable-icp-form-p ~S: ~S" trif-current-name form)
                nil))))))

(defun-simple resumable-icp-push (form)
  (icp-push form *resumable-icp-state*)
  form)

(defmacro resumable-icp-push-list (&rest form-list)
  `(progn
     ,@(loop for form in (reverse form-list)
             collect `(resumable-icp-push ,form))))

(defmacro resumable-icp-push-list-end-marker ()
  `(resumable-icp-push 'resumable-icp-list-end))

(defun-simple resumable-icp-pop ()
  (icp-pop *resumable-icp-state*))

(defun-simple resumable-icp-pop-list-if-end-marker ()
  (when (eq 'resumable-icp-list-end (car *resumable-icp-state*))
    (icp-pop *resumable-icp-state*)
    t))

(defun-for-macro transform-resumeable-icp-form-list (form-list values suspend-forms tagbodyp)
  (let* ((resumablep-list (mapcar #'check-resumable-icp-form-p form-list))
         (count (loop for r-p in resumablep-list count r-p)))
    (cond ((zerop count)
           form-list)
          ((and (eql 1 count)
                (car resumablep-list))
           `(,(transform-resumeable-icp-form
                (car form-list)
                (if (cdr form-list) 'ignore values)
                suspend-forms)
              ,@(cdr form-list)))
          ((eql 1 count)
           (let ((rtail (loop for r-p in resumablep-list
                              for tail on form-list
                              when r-p return tail)))
             (if tagbodyp
                 (let ((resume (make-symbol "RESUME")))
                   `((when (resumable-icp-state)
                       (go ,resume))
                     ,@(ldiff form-list rtail)
                     ,resume
                     ,(transform-resumeable-icp-form
                        (car rtail) 'ignore suspend-forms)
                     ,@(cdr rtail)))
                 `((unless (resumable-icp-state)
                     ,@(ldiff form-list rtail))
                   ,(transform-resumeable-icp-form
                      (car rtail) (if (cdr rtail) 'ignore values) suspend-forms)
                   ,@(cdr rtail)))))
          (tagbodyp
           (transform-resumeable-icp-form-list-1
             form-list values suspend-forms t
             resumablep-list))
          (t
           (let ((block (make-symbol "BLOCK")))
             `(,(transform-resumeable-icp-form-handle-values
                  `(block ,block
                     (return-from ,block
                       (progn
                         ,@(transform-resumeable-icp-form-list-1
                             form-list values
                             `((return-from ,block icp-suspend))
                             nil
                             resumablep-list))))
                  values
                  suspend-forms)))))))

(defun-for-macro transform-resumeable-icp-form-list-1 (form-list values suspend-forms tagbodyp resumablep-list)
  (let* ((tag-indices (loop with so-far = 0
                            for r-p in resumablep-list
                            collect (when r-p (incf so-far))))
         (tags (loop for index in tag-indices
                     collect (when index (make-symbol (format nil "L~D" index)))))
         (dispatch
           `(when (resumable-icp-state)
              (case (resumable-icp-pop)
                ,@(loop for index in tag-indices
                        for tag in tags
                        when tag
                          collect `(,index (go ,tag))))))
         (body-forms
           (loop for index in tag-indices
                 for tag in tags
                 for form in form-list
                 for tail on form-list
                 for lastp = (null (cdr tail))
                 nconc
                 (cond ((and lastp (not tagbodyp))
                        (when tag (list tag)))
                       ((null tag)
                        (list form))
                       (t
                        (list tag
                              (transform-resumeable-icp-form
                                form 'ignore
                                `((resumable-icp-push ,index)
                                  ,@suspend-forms)))))))
         (last-form
           (unless tagbodyp
             (if (not (car (last resumablep-list)))
                 (car (last form-list))
                 (transform-resumeable-icp-form
                   (car (last form-list)) values
                   `((resumable-icp-push ,(car (last tag-indices)))
                     ,@suspend-forms))))))
    (if tagbodyp
        `(,dispatch ,@body-forms)
        `((tagbody ,dispatch ,@body-forms) ,last-form))))

(defvar trif-block-value-alist nil)

(defun-for-macro transform-resumeable-icp-form (form values suspend-forms)
  (if (atom form)
      form
      (case (car form)
        ((macrolet symbol-macrolet progv catch throw unwind-protect flet labels)
         (warn "transform-resumeable-icp-form ~S" form)
         nil)
        ((function)
         (if (symbolp (cadr form))
             form
             (progn
               (warn "transform-resumeable-icp-form ~S" form)
               nil)))
        ((go quote declare trace-icp-message) form)
        ((progn tagbody)
         `(,(car form)
            ,@(transform-resumeable-icp-form-list
                (cdr form) values suspend-forms (eq (car form) 'tagbody))))
        ((the eval-when)
         `(,(car form) ,(cadr form)
            ,@(transform-resumeable-icp-form-list
                (cddr form) values suspend-forms nil)))
        ((block)
         (let ((trif-block-value-alist (cons (cons (cadr form) values)
                                             trif-block-value-alist)))
           `(,(car form) ,(cadr form)
              ,@(transform-resumeable-icp-form-list
                  (cddr form) values suspend-forms nil))))
        ((return-from)
         `(,(car form) ,(cadr form)
            ,@(transform-resumeable-icp-form-list
                (cddr form)
                (or (cdr (assq (cadr form) trif-block-value-alist)) '???)
                suspend-forms nil)))
        ((if ab-lisp::if)
         (let* ((condition-resumable-p (check-resumable-icp-form-p (cadr form)))
                (true-resumable-p (check-resumable-icp-form-p (caddr form)))
                (false-resumable-p (check-resumable-icp-form-p (cadddr form)))
                (count (+ (if condition-resumable-p 1 0)
                          (if true-resumable-p 1 0)
                          (if false-resumable-p 1 0))))
           (cond ((< 1 count)
                  (let ((test (make-symbol "TEST")))
                    `(if (let ((,test nil))
                           (if (and (resumable-icp-state)
                                    (setq ,test (resumable-icp-pop)))
                               (eq ,test 'true)
                               ,(if condition-resumable-p
                                    (transform-resumeable-icp-form
                                      (cadr form)
                                      'boolean
                                      `((resumable-icp-push nil)
                                        ,@suspend-forms))
                                    (cadr form))))
                         ,(if true-resumable-p
                              (transform-resumeable-icp-form
                                (caddr form)
                                values
                                `((resumable-icp-push 'true)
                                  ,@suspend-forms))
                              (caddr form))
                         ,(if false-resumable-p
                              (transform-resumeable-icp-form
                                (cadddr form)
                                values
                                `((resumable-icp-push 'false)
                                  ,@suspend-forms))
                              (cadddr form)))))
                 (condition-resumable-p
                  `(if ,(transform-resumeable-icp-form (cadr form) 'boolean suspend-forms)
                       ,@(cddr form)))
                 (true-resumable-p
                  `(if (or (resumable-icp-state) ,(cadr form))
                       ,(transform-resumeable-icp-form (caddr form) values suspend-forms)
                       ,(cadddr form)))
                 (false-resumable-p
                  `(if (and (not (resumable-icp-state)) ,(cadr form))
                       ,(caddr form)
                       ,(transform-resumeable-icp-form (cadddr form) values suspend-forms)))
                 (t
                  form))))
        ((let* ab-lisp::let*)
         (if (null (cadr form))
             `(let* ()
                ,@(transform-resumeable-icp-form-list
                    (cddr form) values suspend-forms nil))
             (multiple-value-bind (real-body declarations)
                 (split-declarations-from-body (cddr form))
               (let ((variables-to-save
                       (loop for binding in (cadr form)
                             for variable = (if (consp binding) (car binding) binding)
                             collect variable)))
                 `(let* ,(loop for binding in (cadr form)
                               for variable = (if (consp binding) (car binding) binding)
                               for value = (if (consp binding) (cadr binding) nil)
                               for vtail on variables-to-save
                               for variables-before-this = (ldiff variables-to-save vtail)
                               for variables-after-this = (cdr vtail)
                               collect `(,variable
                                           (if (and (resumable-icp-state)
                                                    (not (resumable-icp-pop-list-if-end-marker)))
                                               (resumable-icp-pop)
                                               ,(transform-resumeable-icp-form
                                                  value
                                                  'value
                                                  `((resumable-icp-push-list-end-marker)
                                                    (resumable-icp-push-list ,@variables-before-this)
                                                    ,@suspend-forms)))))
                    ,@declarations
                    ,@(transform-resumeable-icp-form-list
                        real-body values
                        `((resumable-icp-push-list ,@variables-to-save)
                          ,@suspend-forms)
                        nil))))))
        ((let ab-lisp::let)
         ;; (when (cdadr form) (warn "transform-resumeable-icp-form ~S" form))
         (transform-resumeable-icp-form
           `(ab-lisp::let* ,@(cdr form)) values suspend-forms))
        ((multiple-value-bind)
         (multiple-value-bind (real-body declarations)
             (split-declarations-from-body (cdddr form))
           (let* ((values-resumable-p (check-resumable-icp-form-p (caddr form)))
                  (check-values-clauses
                    (when values-resumable-p
                      `(((eq icp-suspend-1 ,(caadr form)) ,@suspend-forms))))
                  (body-resumable-p (check-resumable-icp-form-list-p real-body)))
             (cond (body-resumable-p
                    `(multiple-value-bind ,(cadr form)
                         (if (resumable-icp-state)
                             (values ,@(loop for v in (cadr form)
                                             collect `(resumable-icp-pop)))
                             ,(if values-resumable-p
                                  (transform-resumeable-icp-form
                                    (caddr form)
                                    (length (cadr form))
                                    suspend-forms)
                                  (caddr form)))
                       ,@declarations
                       (cond ,@check-values-clauses)
                       ,@(transform-resumeable-icp-form-list
                           real-body
                           values
                           `((resumable-icp-push-list ,@(cadr form))
                             ,@suspend-forms)
                           nil)))
                   (values-resumable-p
                    `(multiple-value-bind ,(cadr form)
                         ,(transform-resumeable-icp-form
                            (caddr form)
                            (length (cadr form))
                            suspend-forms)
                       ,@declarations
                       (cond ,@check-values-clauses)
                       ,@real-body))
                 (t
                  form)))))
        ((setf setq)
         (cond ((null (cdr form))
                nil)
               ((cdddr form)
                (transform-resumeable-icp-form
                  `(progn ,@(loop for (location value) on (cdr form) by 'cddr
                                  collect `(,(car form) ,location ,value)))
                  values suspend-forms))
               ((or (symbolp (cadr form))
                    (function-call-accessor-macro-p (caadr form))
                    (memq (caadr form) trif-macroexpand-approved-setf-macros))
                `(,(if (symbolp (cadr form)) 'setq 'setf)
                   ,(cadr form)
                   ,(transform-resumeable-icp-form
                      (caddr form) 'value suspend-forms)))
               (t
                (transform-resumeable-icp-form
                  (trif-macroexpand-1 form)
                  'value suspend-forms))))
        ((incff incff-1 decff decff-1)
         form)
        ((non-resumable-icp-form)
         form)
        ((resumable-icp-call)
         (transform-resumeable-icp-call (cadr form) values suspend-forms))
        ((non-resumable-icp-call)
         (transform-non-resumeable-icp-call (cadr form) values suspend-forms))
        ((resumable-icp-form)
         (transform-resumeable-icp-form-handle-values
           (cadr form) values suspend-forms))
        ((case fixnum-case)
         (if (and (symbolp (cadr form))
                  (null (symbol-package (cadr form))))
             `(,(car form) ,(cadr form)
                ,@(loop for (key-or-keylist . forms) in (cddr form)
                        collect `(,key-or-keylist
                                    ,@(transform-resumeable-icp-form-list
                                        forms values suspend-forms nil))))
             (let ((key-variable (make-symbol "KEY")))
               (transform-resumeable-icp-form
                 `(let ((,key-variable ,(cadr form)))
                    (,(car form) ,key-variable
                      ,@(cddr form)))
                 values suspend-forms))))
        (t
         (if (not (symbolp (car form)))
             (if (and (consp (car form))
                      (eq (caar form) 'lambda)
                      (consp (cadar form))) ; and no lambda-list keywords
                 (transform-resumeable-icp-form
                   `(let ,@(loop for parameter in (cadar form)
                                 for argument in (cdr form)
                                 collect `(,parameter ,argument))
                         ,@(cddar form))
                   values suspend-forms)
                 (progn
                   (warn "transform-resumeable-icp-form ~S" form)
                   nil))
             (let ((resumablep (get (car form) 'resumable-icp-form 'unknown)))
               (cond ((not resumablep)
                      (transform-non-resumeable-icp-call form values suspend-forms))
                     ((not (eq resumablep 'unknown))
                      (let ((values (if (or (eq 'ignore values)
                                            (not (fixnump resumablep)))
                                        values
                                        resumablep)))
                        (if (macro-function (car form))
                            (transform-resumeable-icp-form
                              (trif-macroexpand-1 form)
                              values suspend-forms)
                            (transform-resumeable-icp-call
                              form values suspend-forms))))
                     ((memq (car form) trif-macroexpand-function-macros)
                      (transform-non-resumeable-icp-call form values suspend-forms))
                     ((memq (car form) trif-macroexpand-body-macros)
                      `(,(car form)
                         ,@(transform-resumeable-icp-form-list
                             (cdr form) values suspend-forms nil)))
                     ((or (memq (car form) trif-macroexpand-1-ignored-arg+body-macros)
                          (and (memq (car form) trif-macroexpand-1-evaluated-arg+body-macros)
                               (not (check-resumable-icp-form-p (cadr form)))))
                      `(,(car form) ,(cadr form)
                         ,@(transform-resumeable-icp-form-list
                             (cddr form) values suspend-forms nil)))
                     ((not (check-resumable-icp-form-p form))
                      form)
                     (t
                      (multiple-value-bind (new-form expandedp)
                          (trif-macroexpand-1 form)
                        (if expandedp
                            (transform-resumeable-icp-form new-form values suspend-forms)
                            (progn
                              (note-function-call-of-unknown-resumability (car form))
                              (transform-non-resumeable-icp-call
                                form values suspend-forms))))))))))))

(defun-for-macro transform-resumeable-icp-call (form values suspend-forms)
  (if (check-resumable-icp-form-list-p (cdr form))
      (let ((arg-variables (loop for arg-form in (cdr form)
                                 for i from 1
                                 collect (make-symbol (format nil "ARG~D" i)))))
        (transform-resumeable-icp-form
          `(let* ,(loop for arg-form in (cdr form)
                        for arg-variable in arg-variables
                        collect `(,arg-variable ,arg-form))
             (resumable-icp-call (,(car form) ,@arg-variables)))
          values suspend-forms))
      (transform-resumeable-icp-form-handle-values
        form values suspend-forms)))

(defun-for-macro transform-non-resumeable-icp-call (form values suspend-forms)
  (if (check-resumable-icp-form-list-p (cdr form))
      (let ((arg-variables (loop for arg-form in (cdr form)
                                 for i from 1
                                 collect (make-symbol (format nil "ARG~D" i)))))
        (transform-resumeable-icp-form
          `(let* ,(loop for arg-form in (cdr form)
                        for arg-variable in arg-variables
                        collect `(,arg-variable ,arg-form))
             (non-resumable-icp-call (,(car form) ,@arg-variables)))
          values suspend-forms))
      form))

(defmacro resumable-icp-handle-values (values form &rest suspend-forms)
  (cond ((eq values 'ignore)
         `(when (eq icp-suspend-1 ,form)
            ,@suspend-forms))
        ((or (eq values 'value)
             (eq values 'boolean)
             (eql values 1))
         (let ((value (make-symbol "VALUE")))
           `(let ((,value ,form))
              (when (eq icp-suspend-1 ,value)
                ,@suspend-forms)
              ,value)))
        ((not (or (fixnump values)
                  (when (eq values 'values)
                    (setq values 3))))
         (warn "transform-resumeable-icp-form-handle-values"))
        (t
         (let ((vars (loop for i from 1 to values
                           collect (make-symbol (format nil "V~D" i)))))
           `(multiple-value-bind ,vars
                ,form
              (when (eq icp-suspend-1 ,(car vars))
                ,@suspend-forms)
              (values ,@vars))))))

(defun-for-macro transform-resumeable-icp-form-handle-values (form values suspend-forms)
  `(resumable-icp-handle-values ,values ,form ,@suspend-forms))

(defvar-for-macro all-functions-of-unknown-resumability (make-hash-table))

(defun-for-macro note-function-call-of-unknown-resumability (symbol)
  (unless (gethash symbol all-functions-of-unknown-resumability)
    (warn "In ~S: The resumability of function ~S is not known (assuming it is resumable)"
          trif-current-name symbol))
  (setf (gethash symbol all-functions-of-unknown-resumability) t))

(defun-for-macro show-functions-of-unknown-resumability ()
  (let ((symbols nil))
    (maphash #'(lambda (symbol value)
                 (declare (ignore value))
                 (push symbol symbols))
             all-functions-of-unknown-resumability)
    (sort symbols #'string<)))

;; End file with CR

;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module INT3A

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; John Hodgkinson, Lowell B. Hawkinson, Mark H. David, et al.

;; jh, 8/14/96.  Split INT3 into INT3A and INT3B to appease the Watcom compiler
;; on the Windows platform.

;;; Split from module INT by jh on 9/12/90.  (Previously, INT was called ICP.)
;;; INT3 contains basic ICP value types and the I-am-alive mechanism.

;;; File name:		     INT3A.LISP
;;; File location:	     /bt/ab/lisp/
;;; Code control:	     CVS
;;; Purpose:	             ICP value types, object types, and flow control.   
;;; Contents:                ICP value types for numbers, characters, symbols,
;;;                          strings, s-expressions, and compound types.
;;; This file depends on:    Preceding .LISP files in the system load ordering.
;;; Dependent files:         Subsequent .LISP files in the system load ordering.
;;; Role in products:	     Linked into G2 and Telewindows.
;;; Role in development:     None.
;;; Testing harness:         The development function
;;;                          run-icp-text-string-reader-tests tests some aspects of
;;;                          the ICP text-string value type.  The function 
;;;                          dump-icp-buffer displays the contents of an ICP buffer.
;;; Performace requirements: These functions and macros are central to ICP 
;;;                          operation.  Performance is critical.
;;; Major Entities:	     [ICP value type]   boolean
;;;                          [ICP value type]   unsigned-integer
;;;                          [ICP value type]   unsigned-integer?
;;;                          [ICP value type]   integer
;;;                          [ICP value type]   list-of-unsigned-integer
;;;                          [ICP value type]   fixnum
;;;                          [ICP value type]   character
;;;                          [ICP value type]   text-string
;;;                          [ICP value type]   filtered-text-string
;;;                          [ICP value type]   list
;;;                          [ICP value type]   s-expression-for-remote-eval
;;;                          [ICP message type] remote-eval
;;;                          [setf-able macro]  get-gensym-plist-element
;;;                          [ICP value type]   corresponding-icp-object-index
;;;                          [function]         make-icp-object-index-space
;;;                          [function]         assign-corresponding-icp-object-
;;;                                               index
;;;                          [function]         get-corresponding-icp-object
;;;                          [function]         store-corresponding-icp-object
;;;                          [function]         get-original-icp-object
;;;                          [ICP object type]  symbol
;;;                          [function]         set-up-icp-object-index-space
;;;                          [ICP message type] intern
;;;                          [ICP message type] add-to-list-of-symbols


;; Forward references

;; To GSI

(declare-forward-reference gsi-internal-string-format variable)
(declare-forward-reference gensym-string-to-wide-string-for-gsi function)
(declare-forward-reference wide-string-to-gensym-string-for-gsi function)
(declare-forward-reference gsi-reclaim-contents function)
(declare-forward-reference frame-serial-number-function function)
(declare-forward-reference gsi-intern function)

;; To INT3B

(declare-forward-reference
  send-icp-enlarge-corresponding-icp-object-index-space
  function)
(declare-forward-reference
  handler-for-enlarge-corresponding-icp-object-index-space
  function)
(declare-forward-reference write-icp-managed-double-float function)

(declare-forward-reference read-icp-managed-double-float function)

(declare-forward-reference note-item-deleted-from-frame-serial-number-table function)
(declare-forward-reference notify-user function)
(declare-forward-reference flush-and-shutdown-icp-socket function)

(eval-when (:compile-toplevel :load-toplevel :execute)

(defconstant gsi-null-type-tag 0)
(defconstant gsi-integer-type-tag 1)
(defconstant gsi-float-type-tag 2)
(defconstant gsi-symbol-type-tag 3)
(defconstant gsi-string-type-tag 4)
(defconstant gsi-logical-type-tag 5)
(defconstant gsi-64bit-float-type-tag 6)
(defconstant gsi-item-type-tag 7)
(defconstant gsi-value-type-tag 8)
(defconstant gsi-item-handle-type-tag 9)
(defconstant gsi-quantity-type-tag 10)
(defconstant gsi-unsigned-short-vector-type-tag 11)

(defconstant gsi-integer-array-type-tag 17)
(defconstant gsi-symbol-array-type-tag 19)
(defconstant gsi-string-array-type-tag 20)
(defconstant gsi-logical-array-type-tag 21)
(defconstant gsi-64bit-float-array-type-tag 22)
(defconstant gsi-item-array-type-tag 23)
(defconstant gsi-value-array-type-tag 24)
(defconstant gsi-item-or-value-array-type-tag 25)
(defconstant gsi-quantity-array-type-tag 26)

(defconstant gsi-integer-list-type-tag 33)
(defconstant gsi-symbol-list-type-tag 35)
(defconstant gsi-string-list-type-tag 36)
(defconstant gsi-logical-list-type-tag 37)
(defconstant gsi-64bit-float-list-type-tag 38)
(defconstant gsi-item-list-type-tag 39)
(defconstant gsi-value-list-type-tag 40)
(defconstant gsi-item-or-value-list-type-tag 41)
(defconstant gsi-quantity-list-type-tag 42)

(defconstant gsi-sequence-type-tag 49)
(defconstant gsi-structure-type-tag 50)
(defconstant gsi-long-type-tag 51)
(defconstant gsi-end-type-tag 59)
(defconstant gsi-largest-unary-type-number 11) ; any type tag whose value is larger than this is an aggregate of some sort

(defconstant icp-cons-type-tag 80)
(defconstant icp-list-type-tag 81)
(defconstant icp-list-nil-terminator-type-tag 82)
(defconstant icp-list-non-nil-terminator-type-tag 83)

(defconstant icp-standard-index-space-type-tag 70)
(defconstant icp-new-symbol-type-tag 71)
(defconstant icp-new-symbol-expanding-index-space-type-tag 72)
(defconstant icp-temporary-index-space-type-tag 73)
(defconstant rpc-handle-for-temporary-object-handle-type-tag 74)
(defconstant icp-new-keyword-symbol-type-tag 75)

(defconstant rpc-unknown-type-tag       0)
(defconstant rpc-object-type-tag        7)
(defconstant rpc-object-handle-type-tag 8)

(defconstant rpc-handle-for-sending-side-object-type-tag 60)
(defconstant rpc-handle-for-receiving-side-object-handle-type-tag 61)
(defconstant rpc-handle-for-new-sending-side-object-type-tag 62)
(defconstant rpc-new-item-copy-with-reference 63)
(defconstant rpc-existing-item-copy 64)
(defconstant rpc-new-item-copy 65)
(defconstant rpc-new-item-copy-with-handle 66)
(defconstant gsi-typed-sequence-type-tag 67)
(defconstant gsi-gensym-string-type-tag 68)
(defconstant gsi-wide-string-type-tag 69)

(defconstant list-element-null-type-tag 0)
(defconstant list-element-integer-type-tag 1)
(defconstant list-element-symbol-type-tag 2)
(defconstant list-element-text-type-tag 3)
(defconstant list-element-list-type-tag 4)
(defconstant list-element-cons-type-tag 5)

(defconstant icp-tree-interned-list-type-tag 90)
(defconstant index-space-remote-procedure-name 91)

) ; eval-when

;;;; Primitive ICP Value Types

;;; Declaration:     boolean
;;; Type:	     ICP value type.
;;; Purpose:	     Represent a truth value in an ICP message.
;;; Arguments:	     True is the Lisp object t, false is the Lisp object nil.
;;; Return behavior: N/A.
;;; Users:	     GSI (GSI-COMMON).
;;; Prerequisites:   None.
;;; Side effects:    Affects ICP buffers and the remote ICP process.
;;; Non-local exits: N/A.
;;; Memory impact:   None.

;;; Boolean, as an icp value type, returns t or nil.

(def-icp-value-reader boolean
  (if (not (=f (read-icp-byte) 0)) t nil))

(def-icp-value-writer boolean
  (write-icp-byte (if boolean 1 0)))

;; Consider having the reader and/or writer for boolean be substitution macros,
;; in implementations where speed is more important than the non-trivial
;; expansion sizes of read-icp-byte-if-any and write-icp-byte.

;; If optional arguments are implemented, the reader for boolean should use the
;; value of icp-nil, and ICP message handlers should expect it.





;;; Declaration:     unsigned-integer
;;; Type:	     ICP value type.
;;; Purpose:	     Represent an unsigned integer in an ICP message.
;;; Arguments:	     A nonnegative Lisp fixnum.
;;; Return behavior: N/A.
;;; Users:	     ICP internals:
;;;                    INT1: corresponding object creation in def-icp-message-type
;;;                          macroexpansion
;;;                    INT3: compound ICP value types
;;;                  Also GSI (GSI-COMMON), Telewindows and G2 printing (WINDOWS1,
;;;                  WINDOWS2, WINDOWS3), G2 remote procedures (G2-RPC1 and G2-RPC2),
;;;                  GSPAN, G2-to-G2 communication (G2DS, G2DS-NUPEC).
;;; Prerequisites:   None.
;;; Side effects:    Affects ICP buffers and the remote ICP process.
;;; Non-local exits: N/A.
;;; Memory impact:   None.
;;; Notes:           This function should only be given fixnums.  If a bignum is
;;;                  given, this function will signal an error.

(defmacro body-of-read-icp-unsigned-integer ()
  `(let ((icp-byte (peek-icp-byte)))
     (declare (type fixnum icp-byte))
     (cond ((>f icp-byte #.(icp-message-type-code-offset))
	    nil) ; see notes below
	   ((>f icp-byte #.(maximum-icp-byte-unsigned-integer))
	    (read-icp-large-integer (read-icp-byte)))
	   (t (read-icp-byte)))))

;; GENSYMCID-1054: Gigasoft Charts Issue causes TWNG to crash and exit without
;;                 warning when using TWNG 2011 with 8.3r1
;;
;; also see (def-icp-message-type manage-chart-view) in NATIVE-TW.
;; 
;; When doing READ-ICP-CORRESPONDING-OBJECT-INDEX for ICP message `manage-chart-
;; view', due to previous wrong modifications to its argument signature, the
;; additional 5th argument caused ICP handler code failed: it trys to read the
;; 5th argument as a symbol, but wrongly get next message header (64000 +
;; message-type code).
;;
;; According to the definition of 'read-icp-large-integer', the first byte for
;; large integers should be range from 63001 = #.(1+ (maximum-icp-byte-
;; unsigned-integer)) to 64000 = #.(icp-message-type-code-offset).  When the
;; byte is bigger than 63500 = #.(+ (maximum-icp-byte-unsigned-integer)
;; (maximum-icp-large-integer-byte-count)), the large integer is negative, or
;; (<= 63500) it's positive.
;; 
;; If the initial byte is unfortunately bigger than 64000, that is the message
;; type code of next ICP message. Altough such ICP `out of sync' error should
;; cause client to fail, but if we actually read nothing in this case and simply
;; return NIL, then rest of ICP message handling won't be affected at all!
;; And the missing ICP args should have a default value when defining their ICP
;; messages (use '= in args spec).
;;
;; Based on these thoughts, we added (>f icp-byte #.(icp-message-type-code-
;; offset)) in above macro to handle this rare happen, almost impossible case.
;; It will be only used when TWNG 2011 connect to G2 8.3 when getting a out of
;; sync message, no affect to other cases. (so it's safe)
;;
;;  -- Chun Tian (binghe), 2013/06/19

(def-icp-value-reader corresponding-object-index
  (body-of-read-icp-unsigned-integer))

(def-icp-value-reader unsigned-integer
  (body-of-read-icp-unsigned-integer))

(def-substitution-macro body-of-write-icp-unsigned-integer (fixnum)
  (if (fixnump fixnum)
      (if (>f fixnum #.(maximum-icp-byte-unsigned-integer))
	  (write-icp-large-integer fixnum)
	  (write-icp-byte fixnum))
      (icp-error "An integer outside the allowed range was given to ~
                   ICP-write-unsigned-integer: ~a"
		 fixnum)))

(def-icp-value-writer corresponding-object-index
  (body-of-write-icp-unsigned-integer corresponding-object-index))

(def-icp-value-writer unsigned-integer
  (body-of-write-icp-unsigned-integer unsigned-integer))



;; Consider having the reader and/or writer for unsigned-integer be substitution
;; macros, in implementations where speed is more important than the non-trivial
;; expansion sizes of read-icp-byte-if-any and write-icp-byte.







;;; Declaration:     unsigned-integer?
;;; Type:	     ICP value type.
;;; Purpose:	     Represent an unsigned integer or nil in an ICP message.
;;; Arguments:	     A nonnegative Lisp fixnum or the Lisp object nil.
;;; Return behavior: N/A.
;;; Users:	     None.
;;; Prerequisites:   None.
;;; Side effects:    Affects ICP buffers and the remote ICP process.
;;; Non-local exits: N/A.
;;; Memory impact:   No impact since the argument is always fixnum or NIL.
;;; Notes:           Incompatible with the ICP value type unsigned-integer-or-nil,
;;;                  though their ranges are identical.

(def-icp-value-reader unsigned-integer?
  (let ((icp-byte (read-icp-byte)))
    (declare (type fixnum icp-byte))
    (cond
      ((=f icp-byte #.(maximum-icp-byte-unsigned-integer))
       nil)
      ((>f icp-byte #.(maximum-icp-byte-unsigned-integer))
       (read-icp-large-integer icp-byte))
      (t icp-byte))))

(def-icp-value-writer unsigned-integer?
  (cond
    ((null unsigned-integer?)
     (write-icp-byte #.(maximum-icp-byte-unsigned-integer)))
    ((>f unsigned-integer? #.(- (maximum-icp-byte-unsigned-integer) 1))
     (write-icp-large-integer unsigned-integer?))
    (t
     (write-icp-byte unsigned-integer?))))

;; Consider having the reader and/or writer for unsigned-integer? be substitution
;; macros, in implementations where speed is more important than the non-trivial
;; expansion sizes of read-icp-byte-if-any and write-icp-byte.

;; If optional arguments are implemented, the reader for unsigned-integer? should use
;; icp-nil, and ICP message handlers should expect it.






;;; Declaration:     integer
;;; Type:	     ICP value type.
;;; Purpose:	     Represent a signed integer in an ICP message.
;;; Arguments:       A Lisp fixnum.  If the fixnum is between -31500 and +31500
;;;                  inclusive, it is offset by +31500 and sent.  If the fixnum is
;;;                  outside that range, the first ICP byte sent encodes the number
;;;                  of further bytes to read and the sign as follows.  If the first
;;;                  ICP byte is between 63000 and 63500 exclusive, the number is
;;;                  positive, otherwise negative.  If the number is positive, the
;;;                  number of further ICP bytes to read is the difference between
;;;                  the first ICP byte and 63000, if the number is negative, the
;;;                  number of further ICP bytes to read is the difference between
;;;                  the first ICP byte and 65500.  Then the ICP bytes comprising
;;;                  the number are sent, most significant first.  (Note that the
;;;                  magic numbers -31500, +31500, 63000, and 63500 are based on the
;;;                  size of an ICP byte and the smallest most-positive-fixnum in
;;;                  any Lisp implementation we use.  These numbers have been
;;;                  properly abstracted in case any of these facts change.)
;;; Return behavior: N/A.
;;; Users:           ICP internals (compund ICP value types in INT3), GSI
;;;                  (GSI-COMMON), G2 remote procedures (G2-RPC1 and G2-RPC2),
;;;                  G2 foreign functions (G2-FOREIGN), G2-to-G2 communication
;;;                  (G2DS, G2DS-NUPEC).
;;; Prerequisites:   None.
;;; Side effects:    Affects ICP buffers and the remote ICP process.
;;; Non-local exits: N/A.
;;; Memory impact:   None.
;;; Notes:           The reader for this value type is a Lisp substitution macro
;;;                  instead of a Lisp function.

(defun-simple integer-length-in-icp-bytes (integer)
  (if (fixnump integer)
      (let ((fixnum integer))
	(declare (type fixnum fixnum))
	(if (and (>=f fixnum #.(- (floor (maximum-icp-byte-unsigned-integer) 2)))
		 (<=f fixnum
		      #.(- (maximum-icp-byte-unsigned-integer)
			   (floor (maximum-icp-byte-unsigned-integer) 2))))
	    1
	    (large-integer-length-in-icp-bytes integer)))
      (icp-error "Integer outside of the range for ICP integers: ~a" integer)))
  
(def-icp-value-reader integer
  (let ((icp-byte (read-icp-byte)))
    (declare (type fixnum icp-byte))
    (if (>f icp-byte #.(maximum-icp-byte-unsigned-integer))
	(read-icp-large-integer icp-byte)
	(-f icp-byte #.(floor (maximum-icp-byte-unsigned-integer) 2)))))

(def-icp-value-writer integer
  (if (fixnump integer)
      (let ((fixnum integer))
	(declare (type fixnum fixnum))
	(if (and (>=f fixnum #.(- (floor (maximum-icp-byte-unsigned-integer) 2)))
		 (<=f fixnum
		      #.(- (maximum-icp-byte-unsigned-integer)
			   (floor (maximum-icp-byte-unsigned-integer) 2))))
	    (write-icp-byte
	      (+f fixnum #.(floor (maximum-icp-byte-unsigned-integer) 2)))
	    (write-icp-large-integer fixnum)))
      (icp-error "Integer outside of the range for ICP integers: ~a" integer)))

;; Consider having the writer for integer be a substitution macro, in implementations
;; where speed is more important than the non-trivial expansion size of write-icp-byte.

(def-icp-value-writer managed-long
  (with-temporary-bignum-creation
    (partition-long (managed-long-value managed-long) write-icp-byte)))

(def-icp-value-reader managed-long
  (with-temporary-bignum-creation
    (allocate-managed-long (reconstruct-long (read-icp-byte)
					     (read-icp-byte)
					     (read-icp-byte)
					     (read-icp-byte)))))

;;; Declaration:     list-of-unsigned-integers
;;; Type:	     ICP value type.
;;; Purpose:	     Represent a list of unsigned integers in an ICP message.
;;; Arguments:	     A gensym-list of positive Lisp fixnums.
;;; Return behavior: N/A.
;;; Users:	     None.
;;; Prerequisites:   None.
;;; Side effects:    N/A.
;;; Non-local exits: N/A.
;;; Memory impact:   The reader creates a gensym-list.  If an integer to be read
;;;                  exceeds maximum-icp-byte-unsigned-integer (currently 63000), a
;;;                  Lisp bignum will be created.
;;; Notes:           The reader for this value type is a Lisp substitution macro
;;;                  instead of a Lisp function.

;;; Lists of unsigned integers are consed as gensym conses by the icp value
;;; reader reclaimed automatically after their use in an icp handler function
;;; by reclaim-gensym-list.

(def-icp-value-reader-substitution-macro list-of-unsigned-integers
  (loop repeat (read-icp-unsigned-integer)
	collect (read-icp-unsigned-integer) using gensym-cons))

(setf (icp-value-reclaimer 'list-of-unsigned-integers) 'reclaim-gensym-list)

(def-icp-value-writer list-of-unsigned-integers
  (write-icp-unsigned-integer (length list-of-unsigned-integers))
  (loop for unsigned-integer in list-of-unsigned-integers
	do (write-icp-unsigned-integer unsigned-integer)))

;; Consider using macro versions of the gensym consing and reclaiming functions
;; to gain a bit of speed.


;;; The ICP value type `list-of-integers' is used by the polyline drawing
;;; messages.  The integers are actually limited to 16 bits in that case.

(def-icp-value-reader-substitution-macro list-of-integers
  (loop repeat (read-icp-integer)
	collect (read-icp-integer) using gensym-cons))

(setf (icp-value-reclaimer 'list-of-integers) 'reclaim-gensym-list)

(def-icp-value-writer list-of-integers
  (write-icp-integer (length list-of-integers))
  (loop for integer in list-of-integers
	do (write-icp-integer integer)))


(eval-when (:compile-toplevel :load-toplevel :execute)
(defmacro maximum-icp-large-integer-byte-count ()
  500)					; half of alotted "byte space"

(defmacro bits-per-icp-large-integer-byte ()
  15)					; 16 - 1
)

;;; The function `read-icp-large-integer' is called with a fixnum argument,
;;; which is the first ICP byte written by write-icp-large-integer.  This
;;; function will read as many ICP bytes as called for by this argument,
;;; combining them to produce an integer that it will return.  This argument
;;; will be greater than (maximum-icp-byte-unsigned-integer) which indicates
;;; that this is a large integer instead of one of the small formats that
;;; optimize little integers.  Its value indicates how many bytes are to be read
;;; into the fixnum being produced, and it indicates the sign of the result.
;;; The bytes are ordered from most significant to least significant, 15 bits of
;;; data per ICP byte.

;;; Note that in order to avoid overflow, negative fixnums should be accumulated
;;; as a negative value, so that reception of most-negative-fixnum won't
;;; overflow fixnum ranges as a positive value.

(defun-simple-resumable-icp-function read-icp-large-integer (initial-icp-byte)
  (declare (type fixnum initial-icp-byte))
  (if (>f initial-icp-byte
	  #.(+ (maximum-icp-byte-unsigned-integer)
	       (maximum-icp-large-integer-byte-count)))
      (let ((count (-f initial-icp-byte
		       #.(+ (maximum-icp-byte-unsigned-integer)
			    (maximum-icp-large-integer-byte-count)
			    1))))
	(if (=f count 2)
	    most-negative-fixnum
	    (loop with negative-value-so-far fixnum = (-f (read-icp-byte))
		  repeat count
		  do
	      (setq negative-value-so-far
		    (-f (ashf negative-value-so-far
			      #.(bits-per-icp-large-integer-byte))
			(read-icp-byte)))
		  finally (return negative-value-so-far))))
      (loop with value-so-far fixnum = (read-icp-byte)
	    repeat (-f initial-icp-byte
		       #.(1+ (maximum-icp-byte-unsigned-integer)))
	    do
	(setq value-so-far
	      (+f (ashf value-so-far #.(bits-per-icp-large-integer-byte))
		  (read-icp-byte)))
	    finally (return value-so-far))))


;;; The void-function `write-icp-large-integer' is used to write fixnums that
;;; would not fit into the small value optimizations for unsigned or signed
;;; integers.  It sends an ICP byte whose value is larger than the
;;; maximum-icp-byte-unsigned-integer by the number of ICP bytes of data that
;;; will follow, then it sends that many ICP bytes of bits from the integer,
;;; from most significant to least significant.

;;; This mechanism will send 15 bits per ICP byte, and given 30 bit fixnums, it
;;; means that at most 3 ICP bytes total will be sent, unless the argument is
;;; most-negative fixnum, which will take 4 bytes, since the negation of
;;; most-negative fixnum equals most-positive-fixnum PLUS ONE.

(defparameter constant-in-large-integer-length-in-icp-bytes
  (logand most-positive-fixnum
	  (ash (1- (expt 2 (bits-per-icp-large-integer-byte)))
	       (bits-per-icp-large-integer-byte))))

(defun-simple large-integer-length-in-icp-bytes (fixnum)
  (declare (type fixnum fixnum))
  (when (<f fixnum 0)
    (if (=f fixnum most-negative-fixnum)
	(return-from large-integer-length-in-icp-bytes 4)
	(setq fixnum (-f fixnum))))
  (let ((upper-bits
	  (logandf fixnum
		   constant-in-large-integer-length-in-icp-bytes)))
    (declare (type fixnum upper-bits))
    (if (=f upper-bits 0) 2 3)))

(defparameter write-icp-large-integer-constant
  (logand (ash (- most-negative-fixnum) -15)
	  (1- (expt 2 (bits-per-icp-large-integer-byte)))))

(defun-void-resumable-icp-function write-icp-large-integer (fixnum)
  (declare (type fixnum fixnum))
  (let ((byte-count 0))
    (declare (type fixnum byte-count))
    (when (<f fixnum 0)
      ;; Handle most-negative-fixnum specially so that we don't have to negate it.
      (cond ((=f fixnum most-negative-fixnum)
	     (write-icp-byte (+f #.(+ (maximum-icp-byte-unsigned-integer)
				      (maximum-icp-large-integer-byte-count))
				 2))
	     (write-icp-byte
	       write-icp-large-integer-constant)
	     (write-icp-byte 0)
	     (return-from write-icp-large-integer nil))
	    (t
	     (setq fixnum (-f fixnum))
	     (incff byte-count (maximum-icp-large-integer-byte-count)))))
    (let ((upper-bits
	    (logandf (ashf fixnum -15)
		     #.(1- (expt 2 (bits-per-icp-large-integer-byte)))))
	  (lower-bits
	    (logandf fixnum
		     #.(1- (expt 2 (bits-per-icp-large-integer-byte))))))
      (declare (type fixnum upper-bits))
      (incff byte-count (maximum-icp-byte-unsigned-integer))
      (cond ((=f upper-bits 0)
	     (write-icp-byte (+f byte-count 1))
	     (write-icp-byte lower-bits))
	    (t
	     (write-icp-byte (+f byte-count 2))
	     (write-icp-byte upper-bits)
	     (write-icp-byte lower-bits))))))

;; It is assumed that large integers will occur relatively infrequently.




(defun-simple fixnum-length-in-icp-bytes (fixnum)
  (integer-length-in-icp-bytes fixnum))

(def-icp-value-reader fixnum
  (let ((icp-byte (read-icp-byte)))
    (declare (type fixnum icp-byte))
    (if (>f icp-byte #.(maximum-icp-byte-unsigned-integer))
	(read-icp-large-integer icp-byte)
	(-f icp-byte #.(floor (maximum-icp-byte-unsigned-integer) 2)))))

(def-icp-value-writer fixnum
  (write-icp-integer fixnum))




;;; Declaration:     character
;;; Type:	     ICP value type.
;;; Purpose:	     Represent a character in an ICP message.
;;; Arguments:	     A Lisp character disregarding font or shift information.
;;; Return behavior: N/A.
;;; Users:	     ICP internals (compound ICP value types in INT3).
;;; Prerequisites:   None.
;;; Side effects:    N/A.
;;; Non-local exits: N/A.
;;; Memory impact:   None.

;; Adapted from the reader for text-strings for BAH's testing harness, 
;; jh, 11/14/90.

(def-icp-value-reader character
  (let ((encoded-character 
	  (read-icp-byte)))
    (when encoded-character
      (code-char (ashf encoded-character -8)))))

;; Note that int-char is obsolete, but char-int is not.  For symmetry's sake, we
;; might want to change all occurrences to char-code someday, but CLtL/2e p
;; 384-85 says that they produce equivalent results except for code and font
;; bits, which we never use.  jh, 1/31/91.

(def-icp-value-writer character
  (write-icp-byte (char-int character)))





;;; Declaration:     text-string
;;; Type:	     ICP value type.
;;; Purpose:	     Represent a G2 string in an ICP message.
;;; Arguments:	     A G2 text-string
;;; Return behavior: N/A.
;;; Users:           ICP internals (compound ICP value types in INT3), GSI
;;;                  (GSI-COMMON), G2 remote procedures (G2-RPC1 and G2-RPC2),
;;;                  G2 foreign functions (G2-FOREIGN), G2-to-G2 communication
;;;                  (G2DS, G2DS-NUPEC).
;;; Prerequisites:   None.
;;; Side effects:    N/A.
;;; Non-local exits: N/A.
;;; Memory impact:   The reader allocates memory for the text-string.
;;; Possible bugs:   If a text-string contains illegal characters, information is
;;;                  lost when that text-string is retransmitted.
;;; Notes:           > If a text-string being read contains an illegal character,
;;;                    that character will be dropped.  An important illegal
;;;                    character is the tab.
;;;                  > No translations are made between G2 internal text
;;;                    representation and the string.  A commonly desired
;;;                    translation which is not performed is from G2's "@L" to a C
;;;                    newline.
;;;                  > If the text-string being read exceeds
;;;                    maximum-length-for-user-text-strings (currently 65536), the
;;;                    excess characters will be dropped.  
;;;                  > Also note that ICP text strings may contain byte triplets
;;;                    that represent legal Kanji characters in JIS.

;;; Text-string ...  The icp value writer may also be given an ordinary string to write.
;;; Text-strings are reclaimed automatically after their use in an icp handler function
;;; by reclaim-text-string.

;;; Declaration:     gensym-string
;;; Type:	     ICP value type.
;;; Purpose:	     Represent a G2 string in an ICP message.
;;; Arguments:	     A G2 gensym-string
;;; Return behavior: N/A.
;;; Users:           ICP internals (compound ICP value types in INT3), GSI
;;;                  (GSI-COMMON), G2 remote procedures (G2-RPC1 and G2-RPC2),
;;;                  G2 foreign functions (G2-FOREIGN), G2-to-G2 communication
;;;                  (G2DS, G2DS-NUPEC).
;;; Prerequisites:   None.
;;; Side effects:    N/A.
;;; Non-local exits: N/A.
;;; Memory impact:   The reader allocates memory for the gensym-string.
;;; Possible bugs:   If a gensym-string contains illegal characters, information is
;;;                  lost when that gensym-string is retransmitted.
;;; Notes:           > If a gensym-string being read contains an illegal character,
;;;                    that character will be dropped.  An important illegal
;;;                    character is the tab.
;;;                  > No translations are made between G2 internal text
;;;                    representation and the string.  A commonly desired
;;;                    translation which is not performed is from G2's "@L" to a C
;;;                    newline.
;;;                  > If the gensym-string being read exceeds
;;;                    maximum-length-for-user-gensym-strings (currently 65536), the
;;;                    excess characters will be dropped.  
;;;                  > Also note that ICP text strings may contain byte triplets
;;;                    that represent legal Kanji characters in JIS.

;;; gensym-string ...  The icp value writer may also be given an ordinary string to write.
;;; gensym-strings are reclaimed automatically after their use in an icp handler function
;;; by reclaim-gensym-string.

#+development
(defun convert-gensym-string-to-test-icp-bytes (gensym-string)  
  (loop with result = nil
	with string-length = (length gensym-string)
	for i from 0 below (-f string-length 1) by 2
	as first-char = (char gensym-string i)
	do (push
	     (+f (ashf (char-int first-char) 8)
		 (char-int (schar gensym-string (+f i 1))))
	     result)
	finally
	  (if (<f i string-length) 
	      (push 
		(char-int (schar gensym-string (-f string-length 1)))
		result))
	  (return (cons string-length (nreverse result)))))

#+development
(defparameter test-icp-bytes-string "test-string-1")

#+development
(defparameter test-icp-bytes?
	      (convert-gensym-string-to-test-icp-bytes test-icp-bytes-string))

#+development
(defun test-read-icp-byte-if-any (ok-if-none?)
  (cond
    (test-icp-bytes?
     (pop test-icp-bytes?))
    (ok-if-none?
     nil)
    (t
     (error "No (test) icp bytes left"))))


(defun-for-macro get-read-icp-gensym-string-body
    (byte-reader-function-name? obtainer)
  `(provide-legal-gensym-string
     :form-to-determine-string-length
     ,(if byte-reader-function-name?
	  `(,byte-reader-function-name? nil)
	  `(read-icp-byte))
     :loop-clauses-to-get-next-character
     (with icp-byte
      with even? = t
      do (cond
	   (even?
	    (setq icp-byte 
		  ,(if byte-reader-function-name?
		       `(,byte-reader-function-name? nil)
		       `(read-icp-byte)))
	    (setq even? nil)
	    (setq character-code
		  (if last-character-p
		      icp-byte
		      (ashf icp-byte -8))))
	   (t (setq even? t)
	      (setq character-code (logandf icp-byte 255))))
	 ;; we assume that code-char cannot return nil, which
	 ;; should be reviewed, since CLtL2 p. 382 says nil
	 ;; may be returned. (MHD 3/3/92)
	 (setq character (code-char character-code)))
     :gensym-string-obtainer ,obtainer
     :limit-string-length-p t))

(defmacro read-icp-raw-gensym-string-body ()
  `(let* ((string-length (read-icp-byte))
	  (gensym-string
	    (obtain-simple-gensym-string
	      (minf string-length maximum-length-for-user-gensym-strings)))
	  (string-length-exceeded-p nil)
	  (character-code 0)
	  (character #\a))
     (declare (type fixnum string-length character-code)
	      (type character character))
     (loop with last-char-index fixnum
	     = (minf (1-f string-length)
		     (1-f maximum-length-for-user-gensym-strings))
	   for character-index fixnum = 0 then (1+f character-index)
	   while (<f character-index string-length)
	   as last-character-p = (=f character-index last-char-index)
	   with icp-byte
	   with even-p = t
	   do
       (cond
	 (even-p
	  (setq icp-byte (read-icp-byte))
	  (setq even-p nil)
	  (setq character-code
		(if last-character-p
		    icp-byte
		    (ashf icp-byte -8))))
	 (t
	  (setq even-p t)
	  (setq character-code (logandf icp-byte 255))))
       (setq character (code-char character-code))
	   when (=f character-index maximum-length-for-user-gensym-strings)
	     do (setq string-length-exceeded-p t)
	   unless string-length-exceeded-p
	     do (setf (schar gensym-string character-index) character))
     (values gensym-string string-length-exceeded-p)))

(defmacro read-icp-gensym-string-body (&optional byte-reader-function-name?)
  `(runtime-current-system-case
     ((gsi telewindows)
      (read-icp-raw-gensym-string-body))
     (t ,(get-read-icp-gensym-string-body
	   byte-reader-function-name?
	   'obtain-gensym-string))))


;; This does not use as much abstraction as is available in cases where that would
;; be unwieldy or inefficient; that should be reviewed later, when perhaps more/better
;; abstractions can be created! (MHD 3/3/92)

;; jh, 3/23/92.  Climbed the abstraction ladder a bit because I needed this
;; functionality in copy-string-filtering-out-non-gensym-characters (see
;; UTILITIES1).  Used the provisional abstraction provide-legal-gensym-string.

;; jh, 5/29/92.  Added a true :limit-string-length-p argument to
;; read-icp-gensym-string-body, so we can limit the length of strings read by ICP.

#+development
(defun test-read-icp-gensym-string ()
  (read-icp-gensym-string-body test-read-icp-byte-if-any))


;;; Test with run-icp-gensym-string-reader-tests.  This puts a trace on
;;; copy-illegal-gensym-string-without-bad-characters and
;;; test-icp-test-string-reader.

#+development
(defvar standard-icp-text-reader-test-strings
	;; (<test-string> [<result if different>])
	'(("")					; ok - empty string
	  ("a b c")				; ok string
	  ("a
b" "ab")					; illegal return char 
	  ("a	b" "ab")			; illegal tab char
	  ("foo@Lbar")				; legal @L
	  ("foo@xbar" "foobar")			; illegal @ escape
	  ("~@~\\~~")				; legal ~ escapes
	  ("~" "")				; illegal ~ escape
	  ("@" "")				; illegal @ escape
	  ("\\" "")				; illegal \ escape
	  ("\\n" "")				; illegal \ escape
	  ("\\111")				; illegal \ escape
	  ("\\nn" "\\nn")			; "\\nn" - legal \ escape
	  ("\\8p" "")				; bad Kanji code - 2 char 
	  ("\\8q")				; good Kanji code - 2 char
	  ("\\#[S" "")				; bad Kanji code - 3 char
	  ("\\#[T")				; good Kanji code - 3 char
	  ;; The following tests for limits on maximum ICP string length.
	  ;; Change maximum-length-for-user-gensym-strings in CHARACTERS to a
	  ;; defvar initialized to 20 and then recompile
	  ;; test-read-icp-gensym-string for this test to work.
	  ;("123456789012345678901234567890" "12345678901234567890")
	  ;("123456789012345678901" "12345678901234567890")
	  ;("12345678901234567890" "12345678901234567890")
	  ;("1234567890123456789" "1234567890123456789")
	  ;("1234567890123456789~" "1234567890123456789")
	  ))

;; Do more mixing of escapes -- longer strings.  Add more cases! (MHD 3/3/92)



#+development
(defun generate-kstring (kcode)
  (twith-output-to-gensym-string
    (twrite-kanji-character kcode)))

#+development
(defun run-icp-gensym-string-reader-tests ()
  (trace test-icp-test-string-reader)
  (trace copy-illegal-gensym-string-without-bad-characters)
  #+obsolete
  (trace legal-kanji-character-code-p)
  (loop for (string different-result?)
	    in standard-icp-text-reader-test-strings
	as result = (test-icp-test-string-reader string)
	do (test-assertion
	     (string= result (or different-result? string))))
  (untrace))





;;; Test-icp-test-string-reader ... 

#+development
(defun test-icp-test-string-reader (&optional test-string?)
  (setq test-icp-bytes?
	(convert-gensym-string-to-test-icp-bytes
	  (or test-string? test-icp-bytes-string)))
  (prog1 (test-read-icp-gensym-string)
	 (test-assertion (null test-icp-bytes?))))

(def-icp-value-reader wide-string
  (let* ((string-length (with-bifurcated-version-for-input (long-string-icp-version)
			  (read-icp-byte)
			  (read-icp-unsigned-integer)))
	 (maximum-length (with-bifurcated-version-for-input (long-string-icp-version)
			   #.(expt 2 16)
			   maximum-length-for-user-text-strings))
	 (text-string-length (minf string-length maximum-length))
	 (text-string (obtain-text-string text-string-length)))
    #|
    (loop for character-index from 0 below text-string-length
	  do (setf (charw text-string character-index)
		   (code-wide-character (read-icp-byte))))
    |#
    (loop with character-index = 0
	  for characters-remaining = (-f text-string-length character-index)
	  while (<f 0 characters-remaining)
	  do
      (resumable-icp-form
	(unless (with-icp-read-buffer (array start length)
		  (let ((block-size (minf length characters-remaining)))
		    (loop for icp-buffer-position from start below (+f start block-size)
			  do
		      (setf (charw text-string character-index)
			    (code-wide-character (icp-byte-aref array icp-buffer-position)))
		      (incff character-index))
		    (update-icp-read-buffer block-size)
		    t))
	  (read-icp-suspend))))
    #|
    (loop for character-index from text-string-length below string-length
	  do (read-icp-byte))
    |#
    (loop with character-index = text-string-length
	  for characters-remaining = (-f string-length character-index)
	  while (<f 0 characters-remaining)
	  do
      (resumable-icp-form
	(unless (with-icp-read-buffer (array start length)
		  array start
		  (let ((block-size (minf length characters-remaining)))
		    (incff character-index block-size)
		    (update-icp-read-buffer block-size)
		    t))
	  (read-icp-suspend))))
    (unless (=f string-length text-string-length)
      (let ((beginning-of-truncated-string
	      (text-string-substring text-string 0 20)))
	(notify-user-if-possible 
	  "ICP attempted to read a text string longer than ~
           the maximum allowed length of ~a characters.  ~
           The string beginning ~s ~
           will be truncated to the maximum allowed length."
	  maximum-length-for-user-text-strings
	  beginning-of-truncated-string)
	(reclaim-text-string beginning-of-truncated-string)))
    text-string))

(def-substitution-macro gensym-string-to-wide-string-for-icp (string)
  (prog1 (gensym-string-to-wide-string string)
    (reclaim-gensym-string string)))

(def-icp-value-reader text-string
  (let* ((have-wide-string-p
	   (icp-connection-supports-wide-strings? current-icp-socket 'input))
	 (string
	   (if have-wide-string-p
	       (read-icp-wide-string)
	       (read-icp-gensym-string))))
    (if have-wide-string-p
	string
	(gensym-string-to-wide-string-for-icp string))))

(def-icp-value-reader gensym-string
  (multiple-value-bind (gensym-string length-limit-exceeded-p)
      (read-icp-gensym-string-body)
    (when length-limit-exceeded-p
      (let ((beginning-of-truncated-string
	      (gensym-string-substring gensym-string 0 20)))
	(notify-user-if-possible 
	  "ICP attempted to read a text string longer than ~
           the maximum allowed length of ~a bytes.  ~
           The string beginning ~s ~
           will be truncated to the maximum allowed length."
	  maximum-length-for-user-gensym-strings
	  beginning-of-truncated-string)
	(reclaim-gensym-string beginning-of-truncated-string)))
    gensym-string))

(def-icp-value-reader-substitution-macro raw-gensym-string
  (multiple-value-bind (raw-gensym-string length-limit-exceeded-p)
      (read-icp-raw-gensym-string-body)
    (when length-limit-exceeded-p
      (let ((beginning-of-truncated-string
	      (gensym-string-substring raw-gensym-string 0 20)))
	(notify-user-if-possible 
	  "ICP attempted to read a text string longer than ~
           the maximum allowed length of ~a bytes.  ~
           The string beginning ~s ~
           will be truncated to the maximum allowed length."
	  maximum-length-for-user-gensym-strings
	  beginning-of-truncated-string)
	(reclaim-gensym-string beginning-of-truncated-string)))
    raw-gensym-string))

;; jh, 10/24/91.  Added logandf wrappers within every call to code-char for
;; defensive programming, even though ICP-bytes are 16 bits and so we should never
;; overflow.  Note that there is a related problem in reading a gensym-string if it
;; contains escape characters in a strange place (such as the end of the text
;; string).  Using legal-gensym-string-p (in CHARACTERS) is considered too costly a
;; solution, and a few cursory experiments suggest it might not even work in all
;; cases.  We will have to address this problem soon.

;; -- It is too expensive to call every time.  The above implementation minimizes
;; the calls.  I will soon improve this by keeping track of the legality all in
;; the main pass.  This gets the test out into the Beta release, in case I can't
;; do that soon enough.  Review!! (MHD 2/10/92)


(defun-void reclaim-text-or-gensym-string (text-or-gensym-string)
  (if (wide-string-p text-or-gensym-string)
      (reclaim-text-string text-or-gensym-string)
      (reclaim-gensym-string text-or-gensym-string)))

(defun-void reclaim-if-text-or-gensym-string-function (string)
  (cond ((wide-string-p string)
	 (reclaim-text-string string))
	((gensym-string-p string)
	 (reclaim-gensym-string string))))

(defmacro reclaim-if-text-or-gensym-string (string)
  `(reclaim-if-text-or-gensym-string-function ,string))


(setf (icp-value-reclaimer 'text-string) 'reclaim-text-string)

(setf (icp-value-reclaimer 'gensym-string) 'reclaim-gensym-string)

(setf (icp-value-reclaimer 'raw-gensym-string) 'reclaim-gensym-string)

(defun-simple wide-string-length-in-icp-bytes (wide-string)
  (1+f (minf (lengthw wide-string) maximum-length-for-user-text-strings)))


;;; The `inlined pseudo-function inline-copy-widestr-to-icpbuf' is used to copy
;;; the 16-bit ICP bytes from wide-string to the 8-bit byte array in ICP's
;;; network byte order (big-endian, i.e., big byte first).  This is meant
;;; primarily to optimized the core of the wide-string ICP value writer. The
;;; code used in production builds is inlined C code, defined in rtl/c/gensym.h.
;;; The macro `copy-portion-of-wide-string-into-icp-write-buffer' is named
;;; better and implements a correct Lisp/development version of this
;;; functionality. In practice, it's only used in development.  The function
;;; `copy-widestr-to-icpbuf' is a shorter but less nicely named functional
;;; version of that macro.  See rtl/c/gensym.h for the C code that corresponds
;;; to the inline function, and its doc.

(defun-substitution-macro copy-portion-of-wide-string-into-icp-write-buffer
    (wide-string string-start icp-write-buffer buffer-start count)  
  (loop for i from buffer-start below (+f buffer-start count)
	as j from string-start
	do (setf (icp-byte-aref icp-write-buffer i)
		 (wide-character-code (charw wide-string j)))))

(defun copy-widestr-to-icpbuf
    (wide-string string-start icp-write-buffer buffer-start count)
  (copy-portion-of-wide-string-into-icp-write-buffer
    wide-string string-start icp-write-buffer buffer-start count))

(def-inlined-pseudo-function-with-side-effects
    inline-copy-widestr-to-icpbuf
    ((wide-string :16-bit-unsigned-array)
     (string-start :fixnum-long)
     (icp-write-buffer :8-bit-unsigned-array)
     (buffer-start :fixnum-long)
     (count :fixnum-long))
  (copy-widestr-to-icpbuf
    wide-string string-start icp-write-buffer buffer-start count))

;;; The function `handle-too-long-icp-wide-string' is just used by the ICP
;;; wide-string writer for the case of attempting to write a wide-string of too
;;; long a length.

(defmacro handle-too-long-icp-wide-string (wide-string string-length maximum-length)
  `(let ((beginning-of-truncated-string
	   (text-string-substring ,wide-string 0 20)))
     (notify-user-if-possible 
       "ICP attempted to write a text string longer than ~
           the maximum allowed length of ~a characters.  ~
           The string beginning ~s ~
           will be truncated to the maximum allowed length."
       ,maximum-length
       beginning-of-truncated-string)
     (reclaim-text-string beginning-of-truncated-string) ; JH, 8/24/93 -- See Note. 
     (setq ,string-length ,maximum-length)))

(def-icp-value-writer wide-string
  (let* ((string-length (wide-string-length wide-string))
	 (maximum-length
	   (with-bifurcated-version-for-output (long-string-icp-version)
	     #.(expt 2 16)
	     maximum-length-for-user-text-strings)))
    (declare (type fixnum string-length maximum-length))
    (when (>=f string-length maximum-length)
      (handle-too-long-icp-wide-string ; must be a macro, or string-lenth is not modified
	wide-string string-length maximum-length))
    (with-bifurcated-version-for-output (long-string-icp-version)
      (write-icp-byte string-length)
      (write-icp-unsigned-integer string-length))
    (loop with character-index fixnum = 0
	  for characters-remaining fixnum = (-f string-length character-index)
	  while (<f 0 characters-remaining)
	  do
      (resumable-icp-form
	(with-icp-write-buffer (array start length (write-get-new-buffer))
	  (let ((block-size (minf length characters-remaining)))
	    (declare (type fixnum block-size))
	    (inline-copy-widestr-to-icpbuf
	      wide-string character-index array start block-size)
	    (incff character-index block-size)
	    (update-icp-write-buffer block-size)))))))

;; Note: the main loop above is a variant of code previously unused with
;; #+fix-this in front of it.  The code appears correct to me (MHD). I tested
;; it, and found it working. I based the currently used code on it, and it's
;; tested and worked.  I searched commit logs for an explanation of what
;; #+fix-this might mean, but could not find one.  If an explanation if
;; forthcoming, someone should communicate that somewhere.  Otherwise, I'd like
;; to ultimately get rid of that bit of code.  The only clue is this commit log
;; entry for rev. 1.34 of this module, which involved the removal of the
;; #+fix-this code and replacement by the slow loop:
;;
;;   ----------------------------
;;   revision 1.34
;;   date: 1998/02/25 05:05:12;  author: rh;  state: Exp;  lines: +33 -31
;;   Authorization: jed
;;   Witness: jed
;;   
;;   Fix a problem reported by Mike Gribble.  His test case involves sending
;;   a large structure to G2, but the actual bug is in sending and receiving
;;   strings.
;;   
;;   int2.lisp int3a.lisp
;;     Fix the reader and writer for wide strings.
;;   =============================================================================
;;
;; We sent email to rh (Richard Harris) yesterday asking if he could remember
;; the issue. His answer:
;;
;;    I am going to have to think some more about this.  But the test case should
;;   send two arguments in a rpc call, and the first should be a string.  And you
;;   need to try every string length, or at least a bunch of lengths surrounding the
;;   resumable rpc size limit.  There might be a certain string length that doesn't
;;   work.
;;
;; To test this, I created the gsi example/test bridge gsi/c/pingpong.c and
;; companion KB kbs/gsi-pingpong.kb.  These test the integrity of sending and
;; receiving text via ICP.  I ran tests sending strings of all lengths from 0 to
;; the 100's of thousands, and several thousands of sizes up near the max string
;; length (1,000,000, including the NUL terminating character), both with the
;; GSI wide-string and narrow-string APIs, and there were no problems found.
;;
;; (MHD 3/3/04)

;; Note: on Sparcsol, the new inlined copy from the wide string to the ICP
;; buffer seemed to improve raw throughput up to about 2X for a text-heavy
;; bridge applications.  Unfortunately, it does not help much on IntelNT,
;; especially not for GSI.  First of all, the inlined expansion on Intel is not
;; a memcpy, but a slightly tighter loop than we had before.  We cannot use
;; memcpy() because that platform is little-endian.  In addition, for GSI on
;; Windows, the time seems to be dominated by waiting for tcp/ip buffers to be
;; flushed.  For G2-G2 on Windows, there was a somewhat noticeable improvement,
;; in the 15-25% range. (MHD 3/10/04)









(def-icp-value-writer text-string
  #+development
  (unless (wide-string-p text-string)
    (error "~S is not a text string" text-string))
  (let* ((want-wide-string-p
	   (icp-connection-supports-wide-strings? current-icp-socket 'output))
	 (converted-string
	   (unless want-wide-string-p
	     (wide-string-to-gensym-string text-string))) ; must convert using UTF-G
	 (output-string (or converted-string text-string)))
    (prog1 (if want-wide-string-p
	       (write-icp-wide-string output-string)
	       (write-icp-gensym-string output-string))
      (when converted-string
	(reclaim-gensym-string converted-string)))))
	 
(defun-simple gensym-string-length-in-icp-bytes (gensym-string)
  (let ((string-is-simple? (simple-gensym-string-p gensym-string)))
    (1+f (ceilingf-positive (minf (glength gensym-string string-is-simple?)
				  maximum-length-for-user-gensym-strings)
			    2))))

(def-icp-value-writer-substitution-macro raw-gensym-string
  (let* ((string-is-simple? (simple-gensym-string-p raw-gensym-string))
	 (string-length (glength raw-gensym-string string-is-simple?)))
    (when (>f string-length maximum-length-for-user-gensym-strings)
      (let ((beginning-of-truncated-string
	     (gensym-string-substring raw-gensym-string 0 20)))
	(notify-user-if-possible 
	  "ICP attempted to write a string longer than ~
           the maximum allowed length of ~a bytes.  ~
           The string beginning ~s ~
           will be truncated to the maximum allowed length."
	  maximum-length-for-user-gensym-strings
	  beginning-of-truncated-string)
	(reclaim-gensym-string
	  beginning-of-truncated-string) ; JH, 8/24/93 -- See Note. 
	(setq string-length maximum-length-for-user-gensym-strings)))
    (write-icp-byte string-length)
    (if string-is-simple?
	(loop for i from 0 below (-f string-length 1) by 2
	      as first-char = (schar raw-gensym-string i)
	      do (write-icp-byte
		   (+f (ashf (char-int first-char) 8)
		       (char-int (schar raw-gensym-string (+f i 1)))))
	      finally
		(if (<f i string-length) 
		    (write-icp-byte 
		      (char-int
			(schar raw-gensym-string (-f string-length 1))))))
	(loop for i from 0 below (-f string-length 1) by 2
	      as first-char = (char raw-gensym-string i)
	      do (write-icp-byte
		   (+f (ashf (char-int first-char) 8)
		       (char-int (char raw-gensym-string (+f i 1)))))
	      finally
		(if (<f i string-length) 
		    (write-icp-byte 
		      (char-int
			(char raw-gensym-string (-f string-length 1)))))))))
  

(def-icp-value-writer gensym-string
  (write-icp-raw-gensym-string gensym-string))


;; jh, 8/24/93.  Truncating too-long strings is not quite right: what if we
;; truncate an overlong gensym-string in the middle of a multi-character
;; sequence?  We really want to truncate an overlong text string at the final
;; legal character or character sequence.  For now, though, we note that any
;; illegal character sequence originally sent out by this icp-value-writer will
;; be filtered out when it is read in again by the icp-value-reader for
;; gensym-string (by the provide-legal-gensym-string wrapper therein).


;; The binding of first-char to (char gensym-string i) above, as opposed to
;; putting it in-line, is needed only because Lucid on the Sun-4, 2.1,
;; miscompiles it into something that produces garbage.  This way it works.
;; This is being reported to Lucid.  (MHD & BLM 2/11/89)

;; Consider distinguishing simple from adjustable text strings in the
;; reader/writer loops, for better efficiency.  -----> DONE.  Consider having a
;; tchar setf method instead of explicitly dispatching to char or schar in the
;; reader.  (MHD 10/11/89)

;; jh per jra, 1/31/91, regarding the above note.  We can avoid dispatching on
;; string-is-simple every time through the loop in the gensym-string readers and
;; writers by simply copying the loop for both cases.  This saves one branch
;; instruction per character.  The above setf idea wouldn't do this, so the code
;; has to remain bulky.  We also should consider changing char-int to char-code,
;; although (unlike int-char) char-int is still allowed by CLtL/2e.

;; Consider representing a length of 0-254 as an 8-bit length, and a longer length
;; as 255 as an 8-bit byte followed by a 32-bit length.

;; Note that a last odd byte is left unshifted, contrary to what one might expect.





;;; Declaration:     filtered-text-string
;;; Type:	     ICP value type.
;;; Purpose:	     Represent a C string in an ICP message.
;;; Arguments:       A text-string to be used or transmitted by GSI.
;;; Return behavior: N/A.
;;; Users:	     GSI (GSI-COMMON), G2 remote procedures (G2-RPC1 and G2-RPC2), IMAGES.
;;; Prerequisites:   None.
;;; Side effects:    N/A.
;;; Non-local exits: N/A.
;;; Memory impact:   The reader allocates memory for the text-string.
;;; Possible bugs:   If a text-string contains illegal characters, information is
;;;                  lost when that text-string is retransmitted.
;;; Notes:           The reader transforms G2 newlines into C newlines and
;;;                  removes G2 escape characters.  The writer transforms C
;;;                  newlines into G2 newlines and removes C characters which
;;;                  have no representation in G2, such as \t, the tab
;;;                  character.

;; jh, 12/8/91.  Added ICP reader for filtered text-strings.  See note by the
;; ICP writer, below.

(def-icp-value-reader filtered-text-string ; used only by begin-making-image-data
  (let* ((raw-text-string (read-icp-text-string))
	 (result (export-text-string
		   raw-text-string
		   'ICP-FILTERED-TEXT-STRING-READER)))
    (reclaim-text-or-gensym-string raw-text-string)
    result))

;; Had used gensym-to-ascii, which is a bit buggy, and which is only for
;; GSI. (MHD 5/6/95)


;; jh, 11/25/91.  Added the ICP writer for filtered text-strings.  These are
;; strings which convert some internal G2 encodings before transmission, @L into
;; #\Newline for example.  We have to convert the string and then write it because
;; we don't know its length at compile time (it could contain an arbitrary number
;; of G2 escape characters).  Eventually, we will decide on a good abstraction for
;; filtering text-strings to and from the outside world.

(def-icp-value-writer filtered-text-string  ; used only by begin-making-image-data
  (let ((text-string
	  (import-text-string
	    filtered-text-string
	    'ICP-FILTERED-TEXT-STRING-WRITER)))	; Review! (MHD 6/18/96)
    (prog1 (write-icp-text-string text-string)
	   (reclaim-text-string text-string))))

;; Had used ascii-to-gensym, which is a bit buggy, and which is only for
;; GSI. (MHD 5/6/95)






;;; Declaration:     list
;;; Type:	     ICP value type.
;;; Purpose:	     Represent a list in an ICP message.
;;; Arguments:       A proper (i.e., nil-terminated) gensym-list of
;;;                  symbols, integers, and strings, possibly with tree structure.
;;; Return behavior: N/A.
;;; Users:	     None.
;;; Prerequisites:   None.
;;; Side effects:    N/A.
;;; Non-local exits: N/A.
;;; Memory impact:   The reader allocates gensym-conses for the list.

;;; Lists ...  This ICP value reader and writer set handles simple lists of
;;; symbols, integers, and strings.  The list may have a tree structure.  The
;;; reader constructs the list from gensym-conses.

(def-icp-value-writer list-element 
  (cond ((null list-element)
	 (write-icp-byte list-element-null-type-tag))
	((fixnump list-element)
	 (write-icp-byte list-element-integer-type-tag)
	 (write-icp-integer list-element))
	((symbolp list-element)
	 (write-icp-byte list-element-symbol-type-tag)
	 (write-icp-text-string (symbol-name-text-string list-element)))
	((text-string-p list-element)
	 (write-icp-byte list-element-text-type-tag)
	 (write-icp-text-string list-element))
        ((consp list-element)
	 (write-icp-byte list-element-list-type-tag)
	 (write-icp-list list-element))
	(t
	 (icp-error "Bad ICP-list-element: ~a" list-element))))

(defun-void reclaim-icp-list-element (icp-list-element)
  (cond
    ((consp icp-list-element)
     (reclaim-icp-list-element (car icp-list-element))
     (reclaim-icp-list-element (cdr icp-list-element))
     (reclaim-gensym-cons icp-list-element))
    ((text-string-p icp-list-element)
     (reclaim-text-or-gensym-string icp-list-element))))

(def-icp-value-reader list-element
  (fixnum-case (read-icp-byte)
    (#.list-element-null-type-tag nil)
    (#.list-element-integer-type-tag
       (read-icp-integer))
    (#.list-element-symbol-type-tag 
       (intern-text-string 
	 (read-icp-text-string)))
    (#.list-element-text-type-tag
       (read-icp-text-string))
    (#.list-element-list-type-tag
       (read-icp-list))))

;used by window-parameters-plist in define-gensym-window
(def-icp-value-writer list
  (write-icp-unsigned-integer (length list))
  (loop for list-element in list 
        do (write-icp-list-element list-element)))
                              

(def-icp-value-reader list
  (loop for item-count from 1 to (read-icp-unsigned-integer)
        collect (read-icp-list-element)
        using gensym-cons))

(def-icp-value-writer improper-list-element 
  (cond ((null improper-list-element)
	 (write-icp-byte list-element-null-type-tag))
	((fixnump improper-list-element)
	 (write-icp-byte list-element-integer-type-tag)
	 (write-icp-integer improper-list-element))
	((symbolp improper-list-element)
	 (write-icp-byte list-element-symbol-type-tag)
	 (write-icp-text-string (symbol-name-text-string improper-list-element)))
	((text-string-p improper-list-element)
	 (write-icp-byte list-element-text-type-tag)
	 (write-icp-text-string improper-list-element))
        ((consp improper-list-element)
	 (let ((last-element (last improper-list-element)))
	   (cond
	     ((and (consp last-element) (null (cdr last-element)))
	      (write-icp-byte list-element-list-type-tag)
	      (write-icp-unsigned-integer (length improper-list-element))
	      (loop for this-element in improper-list-element
		    do
		(write-icp-improper-list-element this-element)))
	     (t (loop for this-element-cons = improper-list-element
					    then next-element
		      for this-element = (car this-element-cons)
		      for next-element = (cdr this-element-cons)
		      do
		  (cond
		    ((atom next-element)
		     (write-icp-byte list-element-cons-type-tag)
		     (write-icp-improper-list-element this-element)
		     (write-icp-improper-list-element next-element)
		     (loop-finish))
		    (t (write-icp-byte list-element-cons-type-tag)
		       (write-icp-improper-list-element this-element))))))))
	(t (icp-error "Bad ICP-improper-list-element: ~a"
		      improper-list-element))))

(def-icp-value-reader improper-list-element
  (fixnum-case (read-icp-byte)
    (#.list-element-null-type-tag nil)
    (#.list-element-integer-type-tag
       (read-icp-integer))
    (#.list-element-symbol-type-tag 
       (intern-text-string 
	 (read-icp-text-string)))
    (#.list-element-text-type-tag
       (read-icp-text-string))
    (#.list-element-list-type-tag
       (loop for item-count from 1 to (read-icp-unsigned-integer)
	     collect (read-icp-improper-list-element)
	       using gensym-cons))
    (#.list-element-cons-type-tag
       (gensym-cons (read-icp-improper-list-element)
		    (read-icp-improper-list-element)))))
       

;used by icon-attributes-plist in provide-ole-object-information
(def-icp-value-writer improper-list
  (write-icp-improper-list-element improper-list))
                              
;;; Reclaim-icp-list-element will work for improper-list-element too.

(def-icp-value-reader improper-list
  (read-icp-improper-list-element))








;; ;;;; Setting and Getting Gensym Plists


;;; Declaration:     get-gensym-plist-element (gensym-plist indicator)
;;; Type:	     Lisp macro suitable for a setf location.
;;; Purpose:	     Get or set a property list of reclaimable conses.
;;; Arguments:       gensym-plist is a gensym-list viewed as a property list.
;;;                  indicator is a key on that list.
;;; Return behavior: The entry whose key is indicator is returned.  If there is no 
;;;                  such indicator, nil is returned.
;;; Users:           ICP internals (enlarge-corresponding-icp-index-space in INT3),
;;;                  Telewindows and G2 printing (FONTS).
;;; Prerequisites:   None.
;;; Side effects:    A setf of this location modifies the plist there to contain the
;;;                  new entry.
;;; Non-local exits: None.
;;; Memory impact:   A setf of this location could allocate two gensym-conses.
;;; Notes:           Currently, (setf get-gensym-plist-element) does not return
;;;                  the new value, and so differs from the behavior of getf.

;;; Get-gensym-plist-element has the same semantics as GETF except that it
;;; will only add gensym conses to place when used with setf.
;;;
;;;

(define-modify-macro set-gensym-plist-element (indicator value)
  mutate-gensym-plist)

(defmacro get-gensym-plist-element (gensym-plist indicator)
  `(getf ,gensym-plist ,indicator))

;(defsetf get-gensym-plist-element set-gensym-plist-element)

(defsetf get-gensym-plist-element (gensym-plist indicator) (value)
  `(progn
     (set-gensym-plist-element ,gensym-plist ,indicator ,value)
     ,value))

(defun mutate-gensym-plist (gensym-plist indicator value)
  (cond
    ((null gensym-plist)
     (gensym-list indicator value))
    (t
     (loop as l on gensym-plist by #'cddr
	   when (eq (car l) indicator)
	     do (setf (cadr l) value)
		(return gensym-plist)
	   finally
	     (return
	       (gensym-cons indicator (gensym-cons value gensym-plist)))))))


;; This section will later be completed and put into a UTILITIES module.
;; For now it may only be used in INT.  This was written in the first place
;; in order to have some way to eliminate setf's of getf, i.e. calls of the
;; form (setf (getf place indicator) value).  The problem was that getf will
;; cons in the case where indicator is not already in place.  (This caused
;; corruption frequently in ICP when various plists were set within temporary
;; area contexts.)

;; For now we have implemented get-gensym-plist-element, which is to have
;; the same semantics as getf, except that it uses gensym conses.  However,
;; for now this has the limitation that it does not return value in the
;; setf case.  Later, JRA thinks he can fix this.
;; (MHD, AGH, JRA, BLM 11/17/89)










;;;; ICP Object Index Spaces



;;; Declaration:     corresponding-icp-object-index
;;; Type:	     ICP value type.
;;; Purpose:	     Represent a corresponding ICP object index in an ICP message.
;;; Arguments:	     A corresponding ICP object index is a nonnegative Lisp fixnum.
;;; Return behavior: N/A.
;;; Users:           Anything defined by def-icp-object-type uses this to create a
;;;                  corresponding ICP object on the remote side.
;;; Prerequisites:   None.
;;; Side effects:    N/A.
;;; Non-local exits: N/A.
;;; Memory impact:   None.
;;; Notes:           Created with a def-icp-value-type-equivalence to
;;;                  unsigned-integer.

(def-icp-value-type-equivalence corresponding-icp-object-index unsigned-integer)

(defmacro read-icp-corresponding-icp-object-index ()
  `(read-icp-unsigned-integer))

(defmacro write-icp-corresponding-icp-object-index (arg)
  `(write-icp-unsigned-integer ,arg))



;;; Declaration:     make-icp-object-index-space ()
;;; Type:	     Lisp function.
;;; Purpose:	     Create a new index space to store ICP objects.
;;; Arguments:	     None.
;;; Return behavior: An index space.
;;; Users:	     ICP internals (set-up-icp-object-index-space in INT3).
;;; Prerequisites:   None.
;;; Side effects:    None.
;;; Non-local exits: None.
;;; Memory impact:   Allocates memory for an index space.

(defun make-icp-object-index-space (name-of-icp-object-index-space)
  (let ((index-space (make-index-space name-of-icp-object-index-space
				       (case name-of-icp-object-index-space
					 (item-with-handle-index-space
					  'remove-icp-port-entries-from-icp-object-list)
					 (t
					  'remove-icp-port-entries-from-icp-object)))))
    (enlarge-index-space index-space 20)	; more than enough to get started
    index-space))

;; The elements of the index space are initially nil.




;;; Declaration:     assign-corresponding-icp-object-index
;;;                   (icp-object 
;;;                    name-of-corresponding-icp-object-index-space)
;;; Type:	     Lisp function.
;;; Purpose:	     Obtain an index for an ICP object being sent.
;;; Arguments:       name-of-corresponding-icp-object-index-space is a symbol naming
;;;                  the ICP object index space in which icp-object will be
;;;                  associated with the new index.
;;; Return behavior: Returns the new ICP object index.
;;; Users:           ICP internals (the MAKE-CORRESPONDING-ICP-<icp-object-type>
;;;                  function defined by def-icp-object-type).
;;; Prerequisites:   This function be used only when current-icp-port is an output
;;;                  port.
;;; Side effects:    Modifies the object index space of current-icp-port.
;;; Non-local exits: None.
;;; Memory impact:   Could allocate memory for a new index space entry.

;;; Assign-corresponding-icp-object-index ... should be used only when current-icp-port
;;; is an output port.

(defvar use-new-message-group-for-send-icp-enlarge-index-space-p nil) ; T is no longer supported.

(defun assign-corresponding-icp-object-index
    (icp-object
      name-of-corresponding-icp-object-index-space
      send-enlarge-message-p)
  (let* ((index-space-name (index-space-name-for-icp-port
			     name-of-corresponding-icp-object-index-space
			     current-icp-port))
	 (index-space (index-space-for-icp-port
			index-space-name current-icp-port))
	 (new-index-limit-plus-one? nil)
	 (index
	   (if (eq index-space-name 'frame-serial-number)
	       (current-system-case
		 (ab (frame-serial-number-function icp-object))
		 (t 0))
	       (multiple-value-bind (index inner-new-index-limit-plus-one?)
		   (assign-index-in-index-space index-space)
		 (setq new-index-limit-plus-one?
		       (with-bifurcated-version (resumable-icp-version) ; now, if necessary,
			 inner-new-index-limit-plus-one?
			 nil))                       ; index spaces get implicitly expanded.
		 index))))
    (setf (get-from-icp-port current-icp-port index name-of-corresponding-icp-object-index-space)
	  icp-object)
    (when (and new-index-limit-plus-one?
	       send-enlarge-message-p
	       (with-bifurcated-version-for-output
		   (does-not-require-enlarge-corresponding-icp-object-index-space-icp-version)
		 t
		 nil))
      (if use-new-message-group-for-send-icp-enlarge-index-space-p
	  (writing-icp-message-group (current-icp-port)
	    (send-icp-enlarge-corresponding-icp-object-index-space
	      index-space-name new-index-limit-plus-one?))
	  (send-icp-enlarge-corresponding-icp-object-index-space
	    index-space-name new-index-limit-plus-one?)))
    ;; jh, 4/24/96.  Jim A should review the following conditional values counts
    ;; for GLT-friendliness.
    (if send-enlarge-message-p
	(values index)
	(values index new-index-limit-plus-one?))))




;;; Declaration:     get-corresponding-icp-object
;;;                   (icp-object-type? 
;;; 	               corresponding-icp-object-index)
;;; Type:	     Lisp function.
;;; Purpose:	     Obtain an already-indexed ICP object from a received index.
;;; Arguments:       Looks up corresponding-icp-object-index in the index space
;;;                  whose name is determined by icp-object-type?.  If
;;;                  icp-object-type?  is nil, this function uses the index space
;;;                  named standard-icp-object-index-space.
;;; Return behavior: Returns the an object.
;;; Users:	     ICP internals (add-to-list-of-symbols in INT3).
;;; Prerequisites:   This function should be used only when current-icp-port is an
;;;                  input port.
;;; Side effects:    None.
;;; Non-local exits: None.
;;; Memory impact:   None.

;;; Get-corresponding-icp-object ... should be used only when current-icp-port is an
;;; input port.  If icp-object-type? is nil, the corresponding icp object is assumed to
;;; be in the icp object index space named standard-icp-object-index-space.

(defun get-corresponding-icp-object (corresponding-icp-object-index)
  (get-from-icp-port-if-any
    current-icp-port
    corresponding-icp-object-index
    'standard-icp-object-index-space))

(defmacro get-original-icp-object (corresponding-icp-object-index)
  `(let ((current-icp-port (icp-output-port (parent-icp-socket current-icp-port))))
     (get-corresponding-icp-object ,corresponding-icp-object-index)))


;;; Declaration:     store-corresponding-icp-object
;;;                    (icp-object-type? 
;;;                     corresponding-icp-object-index 
;;;                     corresponding-icp-object)
;;; Type:	     Lisp function.
;;; Purpose:	     Store a new ICP object in an input index space. 
;;; Arguments:       Stores corresponding-icp-object under
;;;                  corresponding-icp-object-index in the index space whose name is
;;;                  determined by icp-object-type?.  If icp-object-type?  is nil,
;;;                  the corresponding icp object is assumed to be in the icp object
;;;                  index space named standard-icp-object-index-space.
;;; Return behavior: Returns corresponding-icp-object.
;;; Users:	     Anything defined by def-icp-object-type uses this to create a
;;;                  corresponding ICP object on the remote side.
;;; Prerequisites:   This function should be used only when current-icp-port is an
;;;                  input port.
;;; Side effects:    Modifies the index space determined by icp-object-type?.
;;; Non-local exits: None.
;;; Memory impact:   Can allocate memory for a new index space entry.

;;; Store-corresponding-icp-object ... should be used only when current-icp-port is an
;;; input port.  Corresponding-icp-object is returned.  If icp-object-type? is nil, the
;;; corresponding icp object is assumed to be in the icp object index space named
;;; standard-icp-object-index-space.

(defun store-corresponding-icp-object
    (corresponding-icp-object-index corresponding-icp-object)
  (store-object-in-index-space
    (standard-icp-object-index-space current-icp-port)
    corresponding-icp-object-index
    corresponding-icp-object))

(defun store-corresponding-item
    (corresponding-icp-object-index corresponding-icp-object)
  (setf (get-from-icp-port current-icp-port
			   corresponding-icp-object-index
			   'item-index-space)
	corresponding-icp-object))



;;; Declaration:     get-original-icp-object
;;;                   (icp-object-type? 
;;; 	               corresponding-icp-object-index)
;;; Type:	     Lisp function.
;;; Purpose:	     Obtain an already-indexed ICP object from a received index.
;;; Arguments:       Looks up corresponding-icp-object-index in the index space
;;;                  whose name is determined by icp-object-type?.  If
;;;                  icp-object-type?  is nil, this function uses the index space
;;;                  named standard-icp-object-index-space.
;;; Return behavior: Returns the object.
;;; Users:	     GSI (GSI-COMMON), GSPAN, G2-to-G2 communication (G2DS).
;;; Prerequisites:   This function should be used only when current-icp-port is an
;;;                  input port.
;;; Side effects:    None.
;;; Non-local exits: None.
;;; Memory impact:   None.

;;; Get-original-icp-object ... should be used only when current-icp-port is an
;;; input port.  If icp-object-type? is nil, the original icp object is assumed to
;;; be in the icp object index space named standard-icp-object-index-space.



;; Consider having icp-output-port-for-current-icp-socket be bound in process-next-icp-
;; message-group-if-ready to (icp-output-port (parent-icp-socket current-icp-port)).







;;;; Symbols in ICP

;;; Declaration:     symbol
;;; Type:	     ICP object type.
;;; Purpose:	     Represent a symbol in an ICP message.
;;; Arguments:       A symbol is identified by its printname, which should be an ICP
;;;                  text-string.
;;; Return behavior: N/A.
;;; Users:	     ICP internals:
;;;                    INT3: add-to-list-of-symbols
;;;                          enlarge-corresponding-icp-object-index-space
;;;                          delete-icp-object-for-process
;;;                  Also G2 remote procedures (G2-RPC1 and G2-RPC2), Telewindows
;;;                  and G2 printing (WINDOWS3), G2-to-G2 communication
;;;                  (G2DS, G2DS-NUPEC).
;;; Prerequisites:   None.
;;; Side effects:    N/A.
;;; Non-local exits: N/A.
;;; Memory impact:   Allocates memory for the text-string which is the printname of
;;;                  the symbol.  For a new symbol, allocates memory for an entry in
;;;                  the symbol table.  Symbol printnames and symbol table entires
;;;                  are allocated in region 2, unlike the remainder of G2 memory,
;;;                  which is allocated in region 1.	



;;; A `symbol' is an ICP object type (as opposed to an ICP value type).

(def-global-property-name corresponding-icp-object-map-for-symbol)

(def-icp-object-type symbol
		     (standard-icp-object-index-space
		      (corresponding-icp-object-map-for-symbol symbol))
  (with-bifurcated-version-for-output (intern-keyword-icp-version)
    (send-icp-intern corresponding-icp-object-index (symbol-name-text-string symbol))
    (if (eq (symbol-package symbol) keyword-package-1)
	(send-icp-intern-keyword corresponding-icp-object-index (symbol-name-text-string symbol))
	(send-icp-intern corresponding-icp-object-index (symbol-name-text-string symbol)))))

(defun info-for-write-icp-symbol-as-value-type (symbol-as-value-type)
  (with-bifurcated-version-for-output (evaluation-sequences-and-structures-icp-version)
    #.gsi-symbol-type-tag
    (if (null symbol-as-value-type)
	#.gsi-null-type-tag
	(let ((existing-index
		(getfq (corresponding-icp-object-map-for-symbol symbol-as-value-type) current-icp-port)))
	  (multiple-value-bind (index index-limit-plus-one?)
	      (if existing-index
		  existing-index
		  (establish-new-object-index-for-symbol symbol-as-value-type current-icp-port nil))
	    (values
	      (cond (existing-index
		     (if inhibit-corresponding-icp-object-making
			 #.icp-temporary-index-space-type-tag
			 #.icp-standard-index-space-type-tag))
		    (inhibit-corresponding-icp-object-making
		     #.icp-temporary-index-space-type-tag)
		    ((and (eq (symbol-package symbol-as-value-type) keyword-package-1)
			  (with-bifurcated-version-for-output (intern-keyword-icp-version)
			    nil
			    t))
		     #.icp-new-keyword-symbol-type-tag)
		    ((null index-limit-plus-one?)
		     #.icp-new-symbol-type-tag)
		    (t
		     #.icp-new-symbol-expanding-index-space-type-tag))
	      index
	      index-limit-plus-one?))))))

(def-icp-value-writer symbol-as-value-type
  (with-disabled-write-icp-suspension
    (multiple-value-bind (code index index-limit-plus-one?)
	(info-for-write-icp-symbol-as-value-type symbol-as-value-type)
      (write-icp-byte code)
      (unless (=f code #.gsi-null-type-tag)
	(unless (=f code #.gsi-symbol-type-tag)
	  (when (=f code #.icp-new-symbol-expanding-index-space-type-tag)
	    (write-icp-fixnum index-limit-plus-one?))
	  (write-icp-corresponding-object-index index))
	(when (or (=f code #.gsi-symbol-type-tag)
		  (=f code #.icp-new-symbol-type-tag)
		  (=f code #.icp-new-keyword-symbol-type-tag)
		  (=f code #.icp-new-symbol-expanding-index-space-type-tag))
	  (write-icp-text-string (symbol-name-text-string symbol-as-value-type)))))))

(def-icp-value-reader symbol-as-value-type
  (case (peek-icp-byte)
    (#.gsi-symbol-type-tag
     (read-icp-byte)
     (intern-text-string (read-icp-text-string) ab-package-1))
    (#.gsi-null-type-tag
     (read-icp-byte)
     nil)
    (#.icp-temporary-index-space-type-tag
     (read-icp-byte)
     (get-object-from-index-space
       current-temporary-icp-object-index-space
       (read-icp-corresponding-object-index)))
    (#.icp-standard-index-space-type-tag
     (read-icp-byte)
     (get-object-from-index-space
       current-standard-icp-object-index-space
       (read-icp-corresponding-object-index)))
    ((#.icp-new-symbol-type-tag #.icp-new-symbol-expanding-index-space-type-tag)
     (when (=f #.icp-new-symbol-expanding-index-space-type-tag (read-icp-byte))
       (handler-for-enlarge-corresponding-icp-object-index-space
	 'standard-icp-object-index-space
	 (read-icp-fixnum)))
     (let* ((new-index (read-icp-corresponding-object-index))
	    (string (read-icp-text-string))
	    (symbol (intern-text-string-for-icp string ab-package-1)))
       (store-corresponding-icp-object new-index symbol)
       (reclaim-text-string string)
       symbol))
    (#.icp-new-keyword-symbol-type-tag
     (read-icp-byte)
     (let* ((new-index (read-icp-corresponding-object-index))
	    (string (read-icp-text-string))
	    (symbol (intern-text-string-for-icp string keyword-package-1)))
       (store-corresponding-icp-object new-index symbol)
       (reclaim-text-string string)
       symbol))))

;; Consider having corresponding-icp-object-map-for-symbol be a kb-specific property name.




;;; Declaration:     set-up-icp-object-index-space (name-of-icp-index-space)
;;; Type:	     Lisp function.
;;; Purpose:	     Create an index space for ICP objects.
;;; Arguments:       name-of-icp-index-space is a symbol, which is placed in entry 0
;;;                  of the new index space.
;;; Return behavior: The new index stace is returned.
;;; Users:	     ICP intenals:
;;;                    INT1: make-icp-port
;;;                    INT3: assign-corresponding-icp-object-index
;;;                          enlarge-corresponding-icp-object-index-space
;;; Prerequisites:   None.
;;; Side effects:    Creates and modifies a new ICP index space.
;;; Non-local exits: None.
;;; Memory impact:   Allocates a new ICP index space.

;;;  The function `set-up-icp-object-index-space' makes and sets up an icp
;;;  object index space (name of index space in 0th element)

(defun set-up-icp-object-index-space (name-of-icp-index-space)
  (let* ((new-icp-object-index-space 
          (make-icp-object-index-space name-of-icp-index-space))
         (index-for-name-of-index-space
          (assign-index-in-index-space new-icp-object-index-space)))
    (store-object-in-index-space
      new-icp-object-index-space 
      index-for-name-of-index-space
      name-of-icp-index-space)
    (when (eq 'standard-icp-object-index-space name-of-icp-index-space)
      (setf (corresponding-icp-object-map-for-symbol name-of-icp-index-space)
	    (gensym-cons
	      current-icp-port
	      (gensym-cons
		index-for-name-of-index-space
		(corresponding-icp-object-map-for-symbol name-of-icp-index-space)))))
    new-icp-object-index-space))



;;; Declaration:     intern (corresponding-icp-object-index text-string)
;;; Type:	     ICP message type.
;;; Purpose:	     Create a corresponding ICP object that is a symbol.
;;; Arguments:       corresponding-icp-object-index is the index under which the new
;;;                  symbol will be stored in the index-space for the ICP value type
;;;                  symbol (currently standard-icp-object-index-space).
;;;                  text-string is the printname of the symbol, whose ICP value
;;;                  type is text-string.
;;; Return behavior: The reader returns the symbol read from ICP.
;;; Users:	     See the symbol ICP object type.
;;; Prerequisites:   None.
;;; Side effects:    A new entry for the symbol may appear in the Lisp symbol table.
;;; Non-local exits: None.
;;; Memory impact:   Aside from the memory impact of the symbol ICP value type, this
;;;                  could allocate a new entry in the index space to hold a new
;;;                  symbol.

;;; Intern makes a corresponding icp object for a symbol.  Note that the
;;; "text-string" argument to send-icp-intern may be any string.

(def-icp-message-type intern (corresponding-icp-object-index text-string)
  (store-corresponding-icp-object
    corresponding-icp-object-index
    (intern-text-string-for-icp text-string ab-package-1)))

(def-icp-message-type intern-keyword (corresponding-icp-object-index text-string)
  (store-corresponding-icp-object
    corresponding-icp-object-index
    (intern-text-string-for-icp text-string keyword-package-1)))

(defun-simple intern-text-string-for-icp (name package)
  (runtime-current-system-case
    (gsi
      package
      (gsi-intern (copy-text-string name)))
    (t
      (intern-text-string
	(copy-text-string name)
	(with-bifurcated-version-for-input (intern-keyword-icp-version)
	  (if (and (eq 'gsi (icp-socket-listener-client? current-icp-socket))
		   (position-of-two-colons name))
	      keyword-package-1
	      ab-package-1)
	  package)))))



;;; Declaration:     add-to-list-of-symbols
;;;                    (corresponding-icp-object-index 
;;;                     symbol 
;;;                     first-element?)
;;; Type:	     ICP message type.
;;; Purpose:	     Add to a list of symbols stored as a corresponding ICP object.
;;; Arguments:       corresponding-icp-object-index is the index of the list, which
;;;                  the reader constructs from gensym-conses.  symbol is placed at
;;;                  the end of the list.  first-element?  is a boolean ICP value
;;;                  type.  If first-element?  is non-nil, a fresh lists is
;;;                  constructed and symbol becomes its only element.
;;; Return behavior: The reader returns the updated list.
;;; Users:	     Telewindows and G2 printings (FONTS).
;;; Prerequisites:   None.
;;; Side effects:    The list of symbols is modified.
;;; Non-local exits: None.
;;; Memory impact:   A new gensym cons is allocated to hole the symbol.  If
;;;                  first-element?  is non-nil and there is a non-empty list stored
;;;                  under corresponding-icp-object-index,
;;; 	             a leak could result.

;;; Add-to-list-of-symbols adds to a list of symbols that is a corresponding icp object
;;; in the ICP object index space named standard-icp-object-index-space.

(def-icp-message-type add-to-list-of-symbols
		      (corresponding-icp-object-index symbol (boolean first-element?))
  (store-corresponding-icp-object
    corresponding-icp-object-index
    (if first-element?
	(gensym-list symbol)
	(nconc (get-corresponding-icp-object corresponding-icp-object-index)
	       (gensym-list symbol)))))





;;;; The ICP-Tree Type

;;; The system variable `object-map-plist-for-icp-tree' holds the association
;;; between icp-trees and (icp-socket object-index) pairs on the sender side.

(def-system-variable object-map-plist-for-icp-tree INT3A nil)

;;; The setter/getter combination `get-icp-plist-element' is patterned after
;;; get-gensym-plist-element, except that a setf of a nil value will remove the
;;; entry and reclaim the icp-conses it occupied.  The plist indicator
;;; (a.k.a. "property") must not be nil.

(defmacro get-icp-plist-element (icp-plist indicator)
  `(getf ,icp-plist ,indicator))

(define-modify-macro set-icp-plist-element (indicator value)
  mutate-icp-plist)

(defsetf get-icp-plist-element set-icp-plist-element)

(defun mutate-icp-plist (icp-plist indicator value)
  (cond
    ((null value)
     (if (eq (car icp-plist) indicator)
	 (let ((new-plist (cddr icp-plist)))
	   (setf (cddr icp-plist) nil)
	   (reclaim-icp-list icp-plist)
	   new-plist)
	 (loop for l on (cdr icp-plist) by #'cddr
	       when (eq (cadr l) indicator)
		 do (let ((old-conses (cdr l)))
		      (setf (cdr l) (cdddr l))
		      (setf (cddr old-conses) nil)
		      (reclaim-icp-list old-conses)
		      (return icp-plist))
		   finally (return icp-plist))))
    ((null icp-plist) (icp-list indicator value))
    (t (loop for l on icp-plist by #'cddr
	     when (eq (car l) indicator)
	       do (setf (cadr l) value)
		  (return icp-plist)
	     finally
	       (return
		 (icp-cons indicator (icp-cons value icp-plist)))))))


(defmacro get-object-map-for-icp-tree (object-plist icp-tree)
  (avoiding-variable-capture (icp-tree)
    `(if (symbolp ,icp-tree)
	 (corresponding-icp-object-map-for-symbol ,icp-tree)
	 (get-icp-plist-element ,object-plist ,icp-tree))))

(defsetf get-object-map-for-icp-tree (object-plist icp-tree) (new-value)
  (avoiding-variable-capture (icp-tree)
    `(if (symbolp ,icp-tree)
	 (setf (corresponding-icp-object-map-for-symbol ,icp-tree)
	       ,new-value)
	 (setf (get-icp-plist-element ,object-plist ,icp-tree) ,new-value))))

;;; The ICP object type `icp-tree' sends an arbitrary icp-tree whose leaves may
;;; be fixnums, symbols, or text-strings.  When an icp-tree is sent as an
;;; argument to an ICP message, a call to reclaim-icp-object-map-for-icp-tree
;;; must follow, lest the entry for this list persist in the local and remote
;;; ICP object maps.  (See the development-only system procedure test-icp-tree
;;; for an example.)

;;; A cons structure passed as an icp-tree must not be circular.  It may have
;;; shared, non-circular conses.  The ICP message handler that gets an icp-tree
;;; as argument is responsible for reclaiming the icp-conses that make it up, as
;;; well as any text-string leaves.  The tree given to the handler will not
;;; contain any shared conses.

;; jh, 3/29/96.  The substitution macro icp-object-type-given-icp-object expects
;; any ICP object that is a cons to be a font-map.  This macro is used (a) to
;; access the ICP object reclaimer and ICP shutdown reclaimer for the object and
;; (b) by remove-icp-object-from-index-space to access the index space
;; associated with a given ICP object type.  Since neither font-map nor icp-tree
;; specify any reclaimers in their def-icp-object-type forms, (a) is not a
;; problem.  And at present, remove-icp-object-from-index-space only gets ICP
;; object arguments of type g2ds-variable, so (b) is not a problem for now.



(def-structure (symbol-tree
		 (:constructor make-symbol-tree ()))
  (symbol-tree-corresponding-object-map
    nil :reclaimer reclaim-gensym-list))


;;;; ICP-Tree Value Type


;;; The ICP value type `icp-tree' sends an arbitrary lisp s-expression whose
;;; leaves may be fixnums, symbols, text strings, managed floats, or
;;; interned-list structures. There was an earlier version written by jh of
;;; icp-tree as an ICP _object_ type, to which most of the comments above
;;; applied.  It was reimplemented as a value type by rh, but most of the
;;; comments were left in place. The reader constructs the tree using
;;; icp-conses.

(def-icp-value-writer icp-tree
  (cond ((fixnump icp-tree)
	 (write-icp-byte #.gsi-integer-type-tag)
	 (write-icp-integer icp-tree))
	((null icp-tree)
	 (write-icp-byte #.gsi-null-type-tag))
	((symbolp icp-tree)
	 (write-icp-symbol-as-value-type icp-tree))
	((text-string-p icp-tree)
	 (write-icp-byte #.gsi-string-type-tag)
	 (write-icp-text-string icp-tree))
	((managed-float-p icp-tree)
	 (write-icp-byte #.gsi-64bit-float-type-tag)
	 (write-icp-managed-double-float icp-tree))
	((interned-list-p-function icp-tree)
	 (write-icp-byte #.icp-tree-interned-list-type-tag)
	 (write-icp-interned-list-as-value-type icp-tree))
	((not (consp icp-tree))
	 #+development
	 (cerror
	   "Send NIL"
	   "WRITE-ICP-ICP-TREE: can't send ~S, which is neither a fixnum, symbol, string, or cons"
	   icp-tree)
	 (write-icp-byte #.gsi-null-type-tag))
	((consp (cdr-of-cons icp-tree))
	 (write-icp-byte #.icp-list-type-tag)
	 (loop for tail on icp-tree
	       while (consp tail)
	       do (write-icp-icp-tree (car-of-cons tail))
	       finally (cond (tail
			      (write-icp-byte #.icp-list-non-nil-terminator-type-tag)
			      (write-icp-icp-tree tail))
			     (t
			      (write-icp-byte #.icp-list-nil-terminator-type-tag)))))
	(t
	 (write-icp-byte #.icp-cons-type-tag)
	 (write-icp-icp-tree (car-of-cons icp-tree))
	 (write-icp-icp-tree (cdr-of-cons icp-tree)))))

(def-icp-value-reader icp-tree
  (let ((code (peek-icp-byte)))
    (if (or (=f code #.icp-standard-index-space-type-tag)
	    (=f code #.icp-temporary-index-space-type-tag)
	    (=f code #.icp-new-symbol-type-tag)
	    (=f code #.icp-new-keyword-symbol-type-tag)
	    (=f code #.icp-new-symbol-expanding-index-space-type-tag))
	(read-icp-symbol-as-value-type)
	(case (read-icp-byte)
	  (#.gsi-integer-type-tag (read-icp-integer))
	  (#.gsi-long-type-tag (read-icp-managed-long))
	  (#.gsi-null-type-tag nil)
	  (#.gsi-string-type-tag (read-icp-text-string))
	  (#.gsi-64bit-float-type-tag (read-icp-managed-double-float))
	  (#.icp-tree-interned-list-type-tag (read-icp-interned-list-as-value-type))
	  (#.icp-list-type-tag
	   (let ((list (icp-list (read-icp-icp-tree))))
	     (loop with next = nil
		   for last = list then next
		   for code = (peek-icp-byte)
		   until (or (=f code #.icp-list-non-nil-terminator-type-tag)
			     (=f code #.icp-list-nil-terminator-type-tag))
		   do (setq next (icp-list (read-icp-icp-tree)))
		      (setf (cdr last) next)
		   finally (when (=f (read-icp-byte) #.icp-list-non-nil-terminator-type-tag)
			     (setf (cdr last) (read-icp-icp-tree))))
	     list))
	  (#.icp-cons-type-tag (icp-cons (read-icp-icp-tree) (read-icp-icp-tree)))
	  (t
	   (icp-error "Unknown type tag ~a in READ-ICP-ICP-TREE" code))))))


;;; The function `reclaim-icp-tree-value' reclaims an instance of the icp value
;;; type known as `icp-tree'. Not to be confused with `reclaim-icp-tree', which
;;; reclaims a tree of icp conses. An icp tree value can be an atom, for
;;; example. Does NOT reclaim interned-list objects.

(defun-void reclaim-icp-tree-value (value)
  (cond ((or (null value) (symbolp value) (fixnump value)))
	((consp value)
	 (reclaim-icp-tree-value (cdr (last value))) ; cf: defconser
	 (setf (cdr (last value)) nil)
	 (loop for e in value doing
	   (reclaim-icp-tree-value e))
	 (reclaim-icp-list value))
	((text-string-p value)
	 (reclaim-text-string value))
	((managed-float-p value)
	 (reclaim-managed-float value))))


#+development
(eval-when (:compile-toplevel :load-toplevel :execute)
(def-icp-message-type-code test-icp-tree 215)
)

#+development
(def-icp-message-type test-icp-tree ((icp-tree icp-tree-1) (icp-tree icp-tree-2))
  (pprint icp-tree-1)
  (pprint icp-tree-2))

#+development
(defparameter icp-tree-for-test
  '(a (b c) (d 123 (f . #w"ho ho") (h (i (j)))) . k))

#+development
(defparameter icp-tree-for-test-2
  '(i (think . that)
    (i (shall (never (see (1 . poem)))) as lovely as 1 . tree)))

#+development
(defun print-first-few-index-space-elements (index-space few)
  (loop for i from 0 below (or few (last-assigned-index index-space))
	do
    (format t "~&~4t~S: ~S~%" i (get-object-from-index-space index-space i))))

#+development
(defun print-first-few-elements-in-standard-index-space (icp-port few)
  (print-first-few-index-space-elements
    (standard-icp-object-index-space icp-port) few))

#+development
(defun skim-index-spaces-of-icp-socket (icp-socket &optional (few 10))
  (format t "~&socket: ~S~%" icp-socket)
  (let ((input-port (icp-input-port icp-socket))
	(output-port (icp-output-port icp-socket)))
    (format t "~&~2tinput-port: ~S~%" input-port)
    (print-first-few-elements-in-standard-index-space input-port few)
    (format t "~&~2toutput-port: ~S~%" output-port)
    (print-first-few-elements-in-standard-index-space output-port few)))

#+development
(defun skim-index-spaces-of-all-icp-sockets (&optional (few 10))
  (loop for socket in active-icp-sockets
	do
    (skim-index-spaces-of-icp-socket socket few)))

;; See skim-index-spaces-of-g2-interface-and-peer in G2DS for further index
;; space probes.

;; Test KB is in /home/jh/kbs50/test-icp-tree.kb.

;; The system procedure to test the ICP value type icp-tree is test-icp-tree, in
;; FILE-SYSPROC.





(def-structure (interned-list
		 (:constructor make-interned-list (interned-list--list))
		 #+development
		 (:print-function print-interned-list))
  interned-list--list
  (interned-list--corresponding-icp-object-map nil)
  (interned-list--plist nil))

(defun-simple interned-list-p-function (x)
  (interned-list-p x))

#+development
(defun print-interned-list (interned-list stream depth)
  (declare (ignore depth))
  (printing-random-object (interned-list stream)
    (format stream "interned-list~{ ~S~}" (interned-list--list interned-list))))

;;
(defvar interned-list-conses nil)
(defvar interned-list-conses-in-use 0)

(defun-simple interned-list-cons (x y)
  (unless interned-list-conses
    (setq interned-list-conses (make-permanent-list-macro 50)))
  (let ((cons interned-list-conses))
    (setq interned-list-conses (cdr cons))
    (setf (car-of-cons cons) x)
    (setf (cdr-of-cons cons) y)
    (incff interned-list-conses-in-use)
    cons))

(defun-simple copy-tree-for-interned-list (tree)
  (cond ((symbolp tree) tree)
	((fixnump tree) tree)
	((consp tree)
	 (interned-list-cons
	   (copy-tree-for-interned-list (car tree))
	   (copy-tree-for-interned-list (cdr tree))))
	(t tree)))

(defmacro interned-list-push (e l)
  `(setf ,l (interned-list-cons ,e ,l)))


(def-global-property-name interned-list-table)
(defvar interned-list-non-symbol-root nil)
(defvar interned-list-symbols nil)
(defvar interned-list-nil nil)

(eval-when (:compile-toplevel :load-toplevel :execute)
(defmacro with-vars-bound-to-new-symbols (vars &body forms)
  `(let ,(loop for var in vars
	       collect `(,var (make-symbol ,(symbol-name var))))
     ,@forms))
)

(defmacro interning-list--intern-next-element
          (known-present-p element element-count root table entry-or-table entry
			   accumulating-list-p list forms)
  `(progn
     (incff ,element-count)
     (when (=f ,element-count 1)
       (setq ,root (when (symbolp ,element) ,element))
       (setq ,table (if ,root
			(or (interned-list-table ,root)
			    ,(unless known-present-p
			       `(progn
				  (setq ,accumulating-list-p t)
				  (interned-list-push ,root interned-list-symbols)
				  (setf (interned-list-table ,root)
					(interned-list-cons nil nil)))))
			(or interned-list-non-symbol-root
			    ,(unless known-present-p
			       `(setq interned-list-non-symbol-root
				      (interned-list-cons nil nil))))))
       (when (and ,accumulating-list-p ,root)
	 (interned-list-push ,root ,list))
       (setq ,entry-or-table ,table)
       (setq ,entry nil))
     (unless (and (=f ,element-count 1) ,root)
       (interning-list--intern-next-element-1
	 ,known-present-p
	 ,element-count ,element ,entry-or-table ,entry ,table
	 ,accumulating-list-p ,list ,forms))))

(defmacro interning-list--intern-next-element-1
          (known-present-p element-count element entry-or-table entry table
			   accumulating-list-p list forms)
  (let ((element-copy (make-symbol "ELEMENT-COPY")))
    `(progn
       (setq ,table (if (consp ,entry-or-table)
			,entry-or-table
			,(unless known-present-p
			   `(setf (cdr ,entry) (interned-list-cons ,entry-or-table nil)))))
       (setq ,entry (or (if (symbolp ,element)
			    (assq ,element (cdr ,table))
			    (assoc-equal ,element (cdr ,table)))
			,(unless known-present-p
			   `(let* ((,element-copy
				      (if (consp ,element)
					  (copy-tree-for-interned-list ,element)
					  ,element))			       
				   (e (interned-list-cons ,element-copy nil)))
			      (interned-list-push e (cdr ,table))
			      (unless ,accumulating-list-p
				(setq ,accumulating-list-p t)
				(interning-list--build-list-so-far
				  ,forms ,element-count ,list ,accumulating-list-p nil))
			      e))))
       (when ,accumulating-list-p
	 (interned-list-push (car ,entry) ,list))	   
       (setq ,entry-or-table (cdr ,entry)))))

(defmacro interning-list--result (accumulating-list-p list element-count
				  entry-or-table entry result forms)
    `(if (=f 0 ,element-count)
	 (or interned-list-nil
	     (setq interned-list-nil (make-interned-list nil)))
	 (or (if (consp ,entry-or-table)
		 (car ,entry-or-table)
		 ,entry-or-table)
	     (progn
	       (unless ,accumulating-list-p
		 (setq ,accumulating-list-p t)
		 (interning-list--build-list-so-far
		   ,forms ,element-count ,list ,accumulating-list-p t))
	       (let ((,result (make-interned-list (nreverse ,list))))
		 (if (consp ,entry-or-table)
		     (setf (car ,entry-or-table) ,result)
		     (setf (cdr ,entry) ,result)))))))

(defmacro interning-list--build-list-so-far (forms outer-element-count list
						   accumulating-list-p lastp)
  (with-vars-bound-to-new-symbols (element-count element root table entry-or-table
				   entry list-so-far-block limit)
    `(block ,list-so-far-block
       (let ((,element-count 0) ,element ,root ,table ,entry-or-table ,entry
	     (,limit ,(if lastp
			  outer-element-count
			  `(1-f ,outer-element-count))))
	 (macrolet ((intern-next-element (value)
		      `(progn
			 (when (=f ,',limit ,',element-count)
			   (return-from ,',list-so-far-block nil))
			 (setq ,',element ,value)
			 (interning-list--intern-next-element
			   t
			   ,',element ,',element-count ,',root
			   ,',table ,',entry-or-table ,',entry
			   ,',accumulating-list-p ,',list ,',forms))))
	   ,@forms)))))

(defmacro interning-list (&body forms)
  (with-vars-bound-to-new-symbols (element-count element root table entry-or-table
				   entry result accumulating-list-p list)
    `(let ((,element-count 0)
	   (,accumulating-list-p nil)
	   (,list nil)
	   ,element ,root ,table ,entry-or-table ,entry)
       (declare (type fixnum ,element-count))
       (macrolet ((intern-next-element (value)
		    `(progn
		       (setq ,',element ,value)
		       (interning-list--intern-next-element
			 nil
			 ,',element ,',element-count ,',root
			 ,',table ,',entry-or-table ,',entry
			 ,',accumulating-list-p ,',list ,',forms))))
	 ,@forms)
       (interning-list--result
	 ,accumulating-list-p ,list ,element-count
	 ,entry-or-table ,entry ,result ,forms))))

(defun-simple intern-list (list)
  (interning-list
    (loop for element in list
	  do (intern-next-element element))))


;;


(def-icp-message-type intern-list
                      (corresponding-icp-object-index (icp-tree list))
  (store-corresponding-icp-object
    corresponding-icp-object-index
    (intern-list list))
  (reclaim-icp-tree list))

(def-icp-object-type interned-list
		     (standard-icp-object-index-space
		      (interned-list--corresponding-icp-object-map interned-list))
  (send-icp-intern-list corresponding-icp-object-index
			(interned-list--list interned-list)))

(def-icp-value-writer interned-list-as-value-type
  (let* ((interned-list interned-list-as-value-type)
	 (index (getfq (interned-list--corresponding-icp-object-map interned-list)
		       current-icp-port)))
    (cond (inhibit-corresponding-icp-object-making
	   (write-icp-byte 65534)
	   (with-disabled-write-icp-suspension
	     (write-icp-corresponding-object-index
	       (or index
		   (establish-new-object-index-for-interned-list
		     interned-list current-icp-port nil)))))
	  (index
	   (write-icp-corresponding-object-index index))
	  (t
	   (write-icp-byte 65535)
	   (with-disabled-write-icp-suspension
	     (write-icp-corresponding-object-index
	       (establish-new-object-index-for-interned-list
		 interned-list current-icp-port nil))
	     (write-icp-icp-tree (interned-list--list interned-list)))))))

(def-icp-value-reader interned-list-as-value-type
  (cond ((=f (peek-icp-byte) 65535)
	 (read-icp-byte)
	 (let* ((corresponding-icp-object-index (read-icp-corresponding-object-index))
	        (tree (read-icp-icp-tree))
		(interned-list (intern-list tree)))
	   (store-corresponding-icp-object
	     corresponding-icp-object-index
	     interned-list)
	   (reclaim-icp-tree tree)
	   interned-list))
	((=f (peek-icp-byte) 65534)
	 (read-icp-byte)
	 (get-object-from-index-space
	   current-temporary-icp-object-index-space
	   (read-icp-corresponding-object-index)))
	(t
	 (get-object-from-index-space
	   current-standard-icp-object-index-space
	   (read-icp-corresponding-object-index)))))

#|(defvar interned-list-conses nil)
(defvar interned-list-conses-in-use 0)

(defun-simple interned-list-cons (x y)
  (unless interned-list-conses
    (setq interned-list-conses (make-permanent-list-macro 50)))
  (let ((cons interned-list-conses))
    (setq interned-list-conses (cdr cons))
    (setf (car-of-cons cons) x)
    (setf (cdr-of-cons cons) y)
    (incff interned-list-conses-in-use)
    cons))

(defun-simple copy-tree-for-interned-list (tree)
  (cond ((symbolp tree) tree)
	((fixnump tree) tree)
	((consp tree)
	 (interned-list-cons
	   (copy-tree-for-interned-list (car tree))
	   (copy-tree-for-interned-list (cdr tree))))
	(t tree)))

(defmacro interned-list-push (e l)
  `(setf ,l (interned-list-cons ,e ,l)))


(def-global-property-name interned-list-table)
(defvar interned-list-non-symbol-root nil)
(defvar interned-list-symbols nil)
(defvar interned-list-nil nil)

(eval-when (:compile-toplevel :load-toplevel :execute)
(defmacro with-vars-bound-to-new-symbols (vars &body forms)
  `(let ,(loop for var in vars
	       collect `(,var (make-symbol ,(symbol-name var))))
     ,@forms))
)

(defmacro interning-list--intern-next-element
          (known-present-p element element-count root table entry-or-table entry
			   accumulating-list-p list forms)
  `(progn
     (incff ,element-count)
     (when (=f ,element-count 1)
       (setq ,root (when (symbolp ,element) ,element))
       (setq ,table (if ,root
			(or (interned-list-table ,root)
			    ,(unless known-present-p
			       `(progn
				  (setq ,accumulating-list-p t)
				  (interned-list-push ,root interned-list-symbols)
				  (setf (interned-list-table ,root)
					(interned-list-cons nil nil)))))
			(or interned-list-non-symbol-root
			    ,(unless known-present-p
			       `(setq interned-list-non-symbol-root
				      (interned-list-cons nil nil))))))
       (when (and ,accumulating-list-p ,root)
	 (interned-list-push ,root ,list))
       (setq ,entry-or-table ,table)
       (setq ,entry nil))
     (unless (and (=f ,element-count 1) ,root)
       (interning-list--intern-next-element-1
	 ,known-present-p
	 ,element-count ,element ,entry-or-table ,entry ,table
	 ,accumulating-list-p ,list ,forms))))

(defmacro interning-list--intern-next-element-1
          (known-present-p element-count element entry-or-table entry table
			   accumulating-list-p list forms)
  (let ((element-copy (make-symbol "ELEMENT-COPY")))
    `(progn
       (setq ,table (if (consp ,entry-or-table)
			,entry-or-table
			,(unless known-present-p
			   `(setf (cdr ,entry) (interned-list-cons ,entry-or-table nil)))))
       (setq ,entry (or (if (symbolp ,element)
			    (assq ,element (cdr ,table))
			    (assoc-equal ,element (cdr ,table)))
			,(unless known-present-p
			   `(let* ((,element-copy
				      (if (consp ,element)
					  (copy-tree-for-interned-list ,element)
					  ,element))			       
				   (e (interned-list-cons ,element-copy nil)))
			      (interned-list-push e (cdr ,table))
			      (unless ,accumulating-list-p
				(setq ,accumulating-list-p t)
				(interning-list--build-list-so-far
				  ,forms ,element-count ,list ,accumulating-list-p nil))
			      e))))
       (when ,accumulating-list-p
	 (interned-list-push (car ,entry) ,list))	   
       (setq ,entry-or-table (cdr ,entry)))))

(defmacro interning-list--result (accumulating-list-p list element-count
				  entry-or-table entry result forms)
    `(if (=f 0 ,element-count)
	 (or interned-list-nil
	     (setq interned-list-nil (make-interned-list nil)))
	 (or (if (consp ,entry-or-table)
		 (car ,entry-or-table)
		 ,entry-or-table)
	     (progn
	       (unless ,accumulating-list-p
		 (setq ,accumulating-list-p t)
		 (interning-list--build-list-so-far
		   ,forms ,element-count ,list ,accumulating-list-p t))
	       (let ((,result (make-interned-list (nreverse ,list))))
		 (if (consp ,entry-or-table)
		     (setf (car ,entry-or-table) ,result)
		     (setf (cdr ,entry) ,result)))))))

(defmacro interning-list--build-list-so-far (forms outer-element-count list
						   accumulating-list-p lastp)
  (with-vars-bound-to-new-symbols (element-count element root table entry-or-table
				   entry list-so-far-block limit)
    `(block ,list-so-far-block
       (let ((,element-count 0) ,element ,root ,table ,entry-or-table ,entry
	     (,limit ,(if lastp
			  outer-element-count
			  `(1-f ,outer-element-count))))
	 (macrolet ((intern-next-element (value)
		      `(progn
			 (when (=f ,',limit ,',element-count)
			   (return-from ,',list-so-far-block nil))
			 (setq ,',element ,value)
			 (interning-list--intern-next-element
			   t
			   ,',element ,',element-count ,',root
			   ,',table ,',entry-or-table ,',entry
			   ,',accumulating-list-p ,',list ,',forms))))
	   ,@forms)))))

(defmacro interning-list (&body forms)
  (with-vars-bound-to-new-symbols (element-count element root table entry-or-table
				   entry result accumulating-list-p list)
    `(let ((,element-count 0)
	   (,accumulating-list-p nil)
	   (,list nil)
	   ,element ,root ,table ,entry-or-table ,entry)
       (declare (type fixnum ,element-count))
       (macrolet ((intern-next-element (value)
		    `(progn
		       (setq ,',element ,value)
		       (interning-list--intern-next-element
			 nil
			 ,',element ,',element-count ,',root
			 ,',table ,',entry-or-table ,',entry
			 ,',accumulating-list-p ,',list ,',forms))))
	 ,@forms)
       (interning-list--result
	 ,accumulating-list-p ,list ,element-count
	 ,entry-or-table ,entry ,result ,forms))))

(defun-simple intern-list (list)
  (interning-list
    (loop for element in list
	  do (intern-next-element element))))|#

(defmacro define-interned-list-mapper (name (argument) &body body)
  `(defun-void ,name (,argument)
     (cond ((null ,argument)
	    (when interned-list-nil
	      (,name interned-list-nil))
	    (when interned-list-non-symbol-root
	      (,name interned-list-non-symbol-root))
	    (loop for symbol in interned-list-symbols
		  for table = (interned-list-table symbol)
		  do (when table (,name table))))
	   ((consp ,argument)
	    (let ((car (car-of-cons ,argument))
		  (cdr (cdr-of-cons ,argument)))
	      (when car (,name car))
	      (when cdr (,name cdr))))
	   (t
	    ,@body))))




(def-structure (icp-read-task
		 (:constructor
		   make-icp-read-task
		   (icp-read-task-corresponding-icp-object-index)))
  (icp-read-task-corresponding-icp-object-index nil)
  (icp-read-task-message-receiver-function nil)
  (icp-read-task-resumable-icp-state nil :reclaimer reclaim-icp-list)
  (icp-read-task-priority nil)
  (icp-read-task-resumable-p nil)
  (icp-read-task-reclaim-list nil))

(defun-simple icp-read-task-priority-function (x)
  (icp-read-task-priority x))

(defun-simple current-icp-read-task-resumable-p ()
  (let ((task current-resumable-icp-read-task))
    (when task
      (icp-read-task-resumable-p task))))

(defun kill-current-icp-read-task ()
  (reclaim-icp-list *resumable-icp-state*)
  (setq *resumable-icp-state* nil)
  (let ((task current-resumable-icp-read-task))
    (when task
      (setf (icp-read-task-resumable-icp-state task) nil)
      (store-corresponding-icp-object (icp-read-task-corresponding-icp-object-index task) nil)
      (runtime-current-system-case
	(gsi (gsi-reclaim-contents (icp-read-task-reclaim-list task) 'gsi)))
      (reclaim-icp-read-task task)
      (setq current-resumable-icp-read-task nil))))  

(defun maybe-finish-current-icp-read-task ()
  (let ((task current-resumable-icp-read-task))
    (when (and task
	       (not (icp-read-task-resumable-p task)))
      (store-corresponding-icp-object (icp-read-task-corresponding-icp-object-index task) nil)
      (runtime-current-system-case
	(gsi (gsi-reclaim-contents (icp-read-task-reclaim-list task) 'gsi)))
      (reclaim-icp-read-task task)
      (setq current-resumable-icp-read-task nil))))

(defun resume-icp-task-1 (function?)
  (let* ((task current-resumable-icp-read-task)
	 (*resumable-icp-state* (unless function?
				  (icp-read-task-resumable-icp-state task)))
	 (function (or function?
		       (icp-read-task-message-receiver-function task)))
	 (gsi-reclaim-list? (icp-read-task-reclaim-list task))
	 (suspendp (when function (eq icp-suspend (funcall-simple-compiled-function function)))))
    (declare (special gsi-reclaim-list?))
    (setf (icp-read-task-message-receiver-function task) (when suspendp function))
    (setf (icp-read-task-reclaim-list task) gsi-reclaim-list?)
    (setf (icp-read-task-resumable-icp-state task) *resumable-icp-state*)))

(def-icp-value-reader icp-task-resumable-p
  (read-icp-boolean))

(defvar buffer-of-resumable-p)
(defvar index-of-resumable-p-in-icp-buffer)

(def-icp-value-writer icp-task-resumable-p
  (prog1 (write-icp-boolean icp-task-resumable-p)
    (setq buffer-of-resumable-p current-icp-buffer)
    (setq index-of-resumable-p-in-icp-buffer current-write-icp-byte-position)))

(def-icp-message-type start-icp-task ((icp-task-resumable-p resumable-p)
				      (unsigned-integer icp-task-index)
				      (unsigned-integer icp-task-priority))
  (let ((task (make-icp-read-task icp-task-index)))
    (setf (icp-read-task-priority task) icp-task-priority)
    (setf (icp-read-task-resumable-p task) resumable-p)
    (store-corresponding-icp-object icp-task-index task)
    (setq current-resumable-icp-read-task task)))

(def-icp-message-type resume-icp-task ((icp-task-resumable-p resumable-p)
				       (unsigned-integer icp-task-index))
  (let ((task (get-from-icp-port-if-any
		current-icp-port icp-task-index
		'standard-icp-object-index-space)))
    (unless task
      (icp-out-of-synch 6))
    (setf (icp-read-task-resumable-p task) resumable-p)
    (setq current-resumable-icp-read-task task)
    (resume-icp-task-1 nil)))

(def-icp-message-type abort-icp-task ((unsigned-integer icp-task-index))
  (let ((task (get-from-icp-port-if-any
		current-icp-port icp-task-index
		'standard-icp-object-index-space)))
    (unless task
      (icp-out-of-synch 6))
    (setf (icp-read-task-resumable-p task) nil)
    (setq current-resumable-icp-read-task task))
  (maybe-finish-current-icp-read-task))

(def-structure (icp-write-task
		 (:constructor
		   make-icp-write-task
		   (icp-write-task-corresponding-icp-object-index
		    icp-write-task-function
		    icp-write-task-argument-list
		    icp-write-task-startp
		    icp-write-task-resumable-icp-state
		    icp-write-task-completion-function
		    icp-write-task-completion-argument-list)))
  icp-write-task-corresponding-icp-object-index
  icp-write-task-function
  icp-write-task-argument-list
  icp-write-task-startp
  icp-write-task-resumable-icp-state
  icp-write-task-completion-function
  icp-write-task-completion-argument-list)

(defun-simple make-resumable-icp-output-task-queue-vector ()
  (let* ((length (1+f (-f lowest-system-priority highest-system-priority)))
	 (vector (allocate-managed-simple-vector length)))
    (loop for i from 0 below length
	  do (setf (svref vector i) nil))
    vector))

(defun-void reclaim-resumable-icp-output-task-queue-vector (vector?)
  (when vector?
    (loop for i from 0 below (length (the simple-vector vector?))
	  for queue? = (svref vector? i)
	  when queue?
	    do (setf (queue-datum queue?) nil)
	       (loop for task being each constant-queue-element of queue?
		     do (reclaim-icp-write-task task)
		     finally
			(reclaim-constant-queue queue?)))
    (reclaim-managed-simple-vector vector?)))

(defmacro run-resumable-icp-write-function (corresponding-object-index priority
					    function argument-list
					    startp resumable-icp-state
					    completion-function completion-argument-list)
  `(let* ((function ,function)
	  (argument-list ,argument-list)
	  (*resumable-icp-state* nil)
	  (current-icp-socket (parent-icp-socket current-icp-port))
	  (writing-resumable-icp-messages-p
	    (not (with-bifurcated-version-for-output (supports-non-resumability-icp-version)
		   nil
		   (icp-socket-does-not-allow-resumability current-icp-socket))))
	  icp-write-task-index
	  (icp-error-suspend-p nil)
	  (suspendp nil))
     (writing-icp-message-group (current-icp-port)
       (let ((buffer-of-resumable-p nil)
	     ;; message series, message code, <resumable-p>
	     (index-of-resumable-p-in-icp-buffer nil))
	 (unless disable-resumability
	   (setq icp-write-task-index
		 (or ,corresponding-object-index
		     (assign-corresponding-icp-object-index
		       nil 'standard-icp-object-index-space nil)))
	   (if ,startp
	       (send-icp-start-icp-task nil icp-write-task-index ,priority)
	       (send-icp-resume-icp-task nil icp-write-task-index)))
	 (setf ,startp nil)
	 (setq *resumable-icp-state* ,resumable-icp-state)
	 (when (setq suspendp (eq icp-suspend (funcall-simple-case-list function argument-list)))
	   (setf ,resumable-icp-state *resumable-icp-state*
		 ,corresponding-object-index icp-write-task-index))
	 (setq *resumable-icp-state* nil)
	 (when suspendp
	   (store-icp-byte buffer-of-resumable-p index-of-resumable-p-in-icp-buffer 1))))
     (cond
       ((and suspendp (not icp-error-suspend-p))
	t)
       (t
	(when icp-write-task-index
	  (when icp-error-suspend-p
	    (let ((current-icp-socket (parent-icp-socket current-icp-port)))
	      (when (=f (icp-connection-state current-icp-socket) #.icp-connection-running)
		(with-appropriate-version-for-output (abort-icp-task-icp-version)
		  (writing-icp-message-group (current-icp-port)
		    (send-icp-abort-icp-task icp-write-task-index))))))
	  (deassign-index-in-index-space
	    icp-write-task-index
	    (standard-icp-object-index-space current-icp-port)))
	(let ((completion-function ,completion-function)
	      (completion-argument-list ,completion-argument-list))
	  (when completion-function
	    (funcall-simple-case-list completion-function completion-argument-list))
	  (reclaim-icp-list argument-list)
	  (reclaim-icp-list completion-argument-list))
	nil))))

(defun-allowing-unwind run-resumable-icp-write-task (task priority)
  (run-resumable-icp-write-function
    (icp-write-task-corresponding-icp-object-index task)
    priority
    (icp-write-task-function task)
    (icp-write-task-argument-list task)
    (icp-write-task-startp task)
    (icp-write-task-resumable-icp-state task)
    (icp-write-task-completion-function task)
    (icp-write-task-completion-argument-list task)))

(defun-simple icp-write-task-not-allowed-to-write-p (there-is-a-scheduler? check-time-slice-p)
  (let ((current-icp-socket (parent-icp-socket current-icp-port)))
    (cond ((not (icp-connection-open-p current-icp-socket))
	   'not-open)
	  ((with-bifurcated-version-for-output (supports-non-resumability-icp-version)
	     nil
	     (icp-socket-does-not-allow-resumability current-icp-socket))
	   nil)
	  ((icp-port-blocked? current-icp-port)
	   'blocked)
	  ((and there-is-a-scheduler? check-time-slice-p (time-slice-expired-p))
	   'time-slice-expired))))

(defun-allowing-unwind send-or-enqueue-icp-write-task (icp-output-port priority function argument-list
						       completion-function completion-argument-list)
  #+development (unless (icp-port-p icp-output-port) (break))
  (let ((resumable-icp-state-1 nil)
	(corresponding-object-index-1 nil)
	(current-icp-port icp-output-port)
	(icp-socket (parent-icp-socket icp-output-port))
	(startp t))
    (ensure-icp-write-callback icp-socket)
    (when (loop with there-is-a-scheduler? = (eq current-system-name 'ab)
		for check-time-slice-p = nil then t
		when (icp-write-task-not-allowed-to-write-p there-is-a-scheduler? check-time-slice-p)
		  return t
		unless (run-resumable-icp-write-function
			 corresponding-object-index-1 priority
			 function argument-list
			 startp resumable-icp-state-1
			 completion-function completion-argument-list)
		  return nil)
      (enqueue-icp-write-task icp-output-port priority corresponding-object-index-1
			      function argument-list startp resumable-icp-state-1
			      completion-function completion-argument-list))))

(defun-simple enqueue-icp-write-task (icp-output-port priority corresponding-object-index-1
				      function argument-list startp resumable-icp-state-1
				      completion-function completion-argument-list)
  (let* ((icp-socket (parent-icp-socket icp-output-port))
	 (queue-vector (or (resumable-icp-output-task-queue-vector icp-socket)
			   (setf (resumable-icp-output-task-queue-vector icp-socket)
				 (make-resumable-icp-output-task-queue-vector))))
	 (queue (or (svref queue-vector priority)
		    (setf (svref queue-vector priority)
			  (make-empty-constant-queue))))
	 (task (make-icp-write-task corresponding-object-index-1
				    function argument-list
				    startp resumable-icp-state-1
				    completion-function completion-argument-list)))
    (constant-queue-enqueue queue task)
    (unless (icp-port-blocked? current-icp-port)
      (with-current-scheduling ((task-to-start-resumable-icp-writing icp-socket) priority
				nil nil t)
	(resumable-icp-write-callback icp-socket t)))
    task))

(defun-simple resumable-icp-write-callback (icp-socket writable?)
  (when writable?
    (loop with there-is-a-scheduler? = (eq current-system-name 'ab)
	  with current-icp-port = (icp-output-port icp-socket)
	  with queue-vector = (or (resumable-icp-output-task-queue-vector icp-socket)
				  (return-from resumable-icp-write-callback nil))
	  for priority from highest-system-priority to lowest-system-priority
	  when (loop with queue? = (svref queue-vector priority)
		     for current-task? = (when queue? (constant-queue-dequeue queue?))
		     unless current-task?
		       return nil
		     do (if (run-resumable-icp-write-task current-task? priority)
			    (constant-queue-enqueue queue? current-task?)
			    (reclaim-icp-write-task current-task?))
		     when (icp-write-task-not-allowed-to-write-p there-is-a-scheduler? t)
		       return t)
	    do (unless (icp-port-blocked? current-icp-port)
		 (with-current-scheduling ((task-to-start-resumable-icp-writing icp-socket) priority
					   nil nil t)
		   (resumable-icp-write-callback icp-socket t)))
	       (loop-finish))))

(defun-simple ensure-icp-write-callback (icp-socket)
  (when (and (cdr (icp-callbacks 'icp-write icp-socket))
	     (memq 'resumable-icp-write-callback (cdr (icp-callbacks 'icp-write icp-socket))))
    (error "bad write callback"))
  (unless (and (icp-callbacks 'icp-write icp-socket)
	       (eq 'resumable-icp-write-callback (car (icp-callbacks 'icp-write icp-socket))))
    (register-icp-callback 'icp-write 'resumable-icp-write-callback icp-socket))
  t)

(defmacro writing-resumable-icp-messages ((icp-output-port priority)
					  (function &rest argument-list)
					  (completion-function &rest completion-argument-list)
					  &key include-non-resumable-p)
  (let* ((icp-output-port-var (make-symbol "ICP-OUTPUT-PORT"))
	 (icp-socket-var (make-symbol "ICP-SOCKET"))
	 (old `(writing-icp-message-group (,icp-output-port-var)
		 (,function ,@argument-list)
		 (,completion-function ,@completion-argument-list)))
	 (new `(send-or-enqueue-icp-write-task
		 ,icp-output-port-var ,priority
		 #',function
		 (icp-list ,@argument-list)
		 #',completion-function
		 (icp-list ,@completion-argument-list))))
    `(let* ((,icp-output-port-var ,icp-output-port)
	    (,icp-socket-var (parent-icp-socket ,icp-output-port-var)))
       ,(if include-non-resumable-p
	    `(with-bifurcated-version-for-output (resumable-icp-version ,icp-socket-var)
	       ,old ,new)
	    new))))

;; End file with CR


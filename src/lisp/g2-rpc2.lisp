;; -*- Mode: LISP; Syntax: Common-Lisp; Base: 10; Package: AB -*-
(in-package "AB")

;;;; Module G2-RPC2

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All rights reserved.

;;; John Hodgkinson

;;; This module contains the machinery for remote-procedure execution that is
;;; specific to G2 and involves passing items as arguments and results.  The
;;; second, half of this module is in G2-RPC3.  The split is because of the
;;; possibilty that a file of the original size, when translated into C, can
;;; cause compiler errors.  (Also note that module G2-RPC1 contains the
;;; G2-specific machinery for passing values as arguments and results, and
;;; modules GSI-RPC1 and GSI-RPC2 contain RPC machinery for the GSI product.)

;; jh, 3/16/94.  Created this module.

;; jh, 2/3/95.  Split this module into G2-RPC2 and G2-RPC3 to isolate errors in
;; the Vax C compiler that don't appear in the debuggable (i.e., non-optimized)
;; image.




;;;; Table of Contents

;;; [2]        Forward References

;;; [5]        Data Structures for Resumable Object Contents
;;; [5.1]        Macros for Type Dispatching on Resumable Nodes
;;; [5.2]        Macros for Type Dispatching on Leaf Values
;;; [5.3]        Reclaimers for Resumable Object Contents

;;; [6.1]        Hashtable for Circularity Checks
;;; [6.3]        Sending Side RPC Object Arguments
;;; [6.3.1]        Sending Side RPC Object Container Structure
;;; [6.3.2]        Sending Side Circularity Checking Mechanism

;;; [8]       Reclaimers for RPC Object Arguments and Argument Lists

;;; [9]        G2 Capability for Object Passing
;;; [9.1]        Deactivator for Object-passing Capability

;;; [10]       G2 Sending Side Task to Preflight Resumable Objects
;;; [11]       ICP Writer and Reader for RPC Object Argument

;;; [13]       Clog Management
;;; [13.1]       Bandwidth for Resumable Nodes
;;; [13.2]       Bandwidth for Resumable Vectors
;;; [13.3]       Bandwidth for Resumable Lists
;;; [13.4]       Bandwidth for Resumable Histories

;;; [14.3.4.1]       G2 Leaf Protocols
;;; [14.3.4.1.1]       G2 System Attribute Protocol
;;; [14.3.4.1.2]       G2 User Attribute Protocols
;;; [14.3.4.2]       G2 Resumable Object Protocols
;;; [14.3.4.3]       G2 Resumable Sequence Protocols




;;;; [2] Forward References

(declare-forward-reference
  simple-text-string-copy-from-attribute-name
  function) ;GSI-RPC2
(declare-forward-reference
  enable-references-for-item-passing
  function) ;G2-RPC3
(declare-forward-reference
  get-attribute-names-for-object-passing
  function) ;G2-RPC3
(declare-forward-reference
  copy-history-state-into-resumable-history-node
  function) ;G2-RPC3
(declare-forward-reference
  g2-get-attribute-for-object-passing
  function) ;G2-RPC3
(declare-forward-reference
  try-to-transmit-resumable-object
  function) ;G2-RPC3
(declare-forward-reference
  get-exported-attribute-names-for-object-passing
  function) ;G2-RPC3
(declare-forward-reference
  get-or-make-gsi-sensor
  function) ;G2-GSI
(declare-forward-reference
  make-transient-item
  function) ;STACK-ACTS
(declare-forward-reference
  conclude-into-attribute-component
  function) ;STACK-ACTS
(declare-forward-reference
  parse-and-change-slot
  function) ;STACK-ACTS
(declare-forward-reference
  in-suspend-resume-p
  variable activate) ;ACTIVATE
(declare-forward-reference
  translation-and-text-of-embedded-rule-function
  function) ;CONTROLS
(declare-forward-reference gsi-register-item function)
	      
(declare-forward-reference define-or-configure-gsi-sensor function)
(declare-forward-reference icp-socket-of-interface-object function)
(declare-forward-reference attribute-operation-is-allowed-p function)

	      
	  

;;;; [5] Data Structures for Resumable Object Contents

;;; This section contains data structures that package an RPC object on the
;;; sending side before it can be sent.

;;; Unless the side-comment beside a slot a def-structure form mentions "share",
;;; the contents must be reclaimed.





;;; The `resumable-circular-node' structure represents an RPC object that has
;;; already been sent across ICP.  The occurrence of this structure in a
;;; resumable node tree implies that the same RPC object is being represented by
;;; two or more distinct resumable nodes: a resumable-instance-node-mixin (q.v.)
;;; and one or more resumable-circular-nodes.  This structure is only used on
;;; the sending side.

;;; The `resumable-circular-corresponding-icp-index' slot of a
;;; resumable-circular-node structure contains the corresponding ICP object
;;; index of the given RPC object.  This index is reclaimed by the :reclaimer in
;;; the icp-object-map-for-resumable-instance-node slot of the
;;; resumable-instance-node-mixin structure that represents the original RPC
;;; object.

(def-structure (resumable-circular-node
		 (:include resumable-node-mixin) 
		 (:constructor
		   make-resumable-circular-node
		   (resumable-attribute-spec?
		     resumable-circular-corresponding-icp-index
		     resumable-node-parent-node?)))
  resumable-circular-corresponding-icp-index ;a fixnum
  )

;;; The `resumable-value-node' represents an RPC value.  It never represents a
;;; "toplevel" argument to an RPC, but always has at least one level of
;;; enclosing RPC object.  This structure is only used on the sending side.

;;; The `resumable-attribute-value' slot of a resumable-value-node structure is
;;; an evaluation value, limited to type evaluation-integer, evaluation-float,
;;; evaluation-text, evaluation-truth-value, or evaluation-symbol.

;;; The resumable-value-corresponding-index? of a resumable-value-node structure
;;; is a fixnum representing the corresponding ICP object of the RPC value in
;;; the resumable-attribute-value slot, or nil if there is no such index.  The
;;; RPC value will have a corresponding index if it is a symbol and an index
;;; exists relative to the ICP socket through which the RPC is conducted.  Since
;;; this index represents an ICP symbol, it is only reclaimed when the ICP
;;; socket for the RPC is shut down.

(def-substitution-macro reclaim-evaluation-value-if-any (evaluation-value?)
  (when evaluation-value?
    (reclaim-evaluation-value evaluation-value?)))

(defun-void reclaim-evaluation-value-if-any-function (evaluation-value?)
  (reclaim-evaluation-value-if-any evaluation-value?))

(def-structure (resumable-value-node
		 (:include resumable-node-mixin) 
		 (:constructor
		   make-resumable-value-node
		   (resumable-attribute-spec?
		     resumable-attribute-value
		     resumable-node-parent-node?)))
  (resumable-attribute-value nil               ;an evaluation-value
   :reclaimer reclaim-evaluation-value-if-any)
  (resumable-value-corresponding-index? nil)   ;a fixnum or nil
  )

;;; The resumable-instance-node-mixin represents the information common to all
;;; resumable nodes holding RPC subobjects that are neither values nor
;;; corresponding ICP object indices.  Only structures that :include this
;;; structure are ever instantiated.  This structure is only used on the sender
;;; side.

;;; The `resumable-instance-current-object' slot of a
;;; resumable-instance-node-mixin structure contains the RPC object associated
;;; with this resumable node.

;;; The `resumable-instance-reference-serial-number' slot of a
;;; resumable-instance-node-mixin structure contains the frame
;;; serial number of the RPC object associated with this resumable node.
;;; This slot is not used in GSI.

;;; The `resumable-instance-class-name' slot of a resumable-instance-node-mixin
;;; structure contains a symbol that names the class of the associated RPC
;;; object.

;;; The `resumable-class-name-corresponding-index?' of a
;;; resumable-node-instance-mixin structure contains a fixnum representing the
;;; corresponding ICP object index of the symbol in the
;;; resumable-instance-class-name slot in that structure, or nil if there is no
;;; such index.  At the time of transmission, this slot will be non-nil if an
;;; index for the class-name symbol exists relative to the ICP socket through
;;; which the RPC is conducted.  Since this index represents an ICP symbol, it
;;; is only reclaimed when the ICP socket for the RPC is shut down.

;;; The `inferior-attributes' slot of a resumable-instance-node-mixin structure
;;; contains an icp-list of resumable nodes that represent the RPC subobjects
;;; immediately accessible from the given RPC object.  Note that the term
;;; "attributes" is extended to included any way of reaching subobjects that
;;; does not involve random access.  In other words, an `inferior attribute'
;;; includes any RPC subobject except RPC values that are elements of vectors
;;; and lists containing only RPC values.  Such access is handled by structure
;;; types that :include resumable-node-mixin (such as resumable-vector-node).
;;; This division is made for efficiency, since access of an internal array or
;;; list can be batched and therefore faster than traversal of substructure.

;;; The `current-cons-in-inferior-attributes?' and
;;; `last-cons-in-inferior-attributes?' slots in a resumable-instance-node-mixin
;;; structure share structure with the inferior attributes slot during
;;; object-passing tasks.

;;; The `node-itself-sent-p' slot of a resumable-instance-node-mixin structure
;;; contains a boolean that indicates to the object-passing transmission phase
;;; whether or not the node has been transmitted.

;;; The `ascension-target?' slot in a resumable-instance-node-mixin structure
;;; contains a resumable node that represents an enclosing RPC object one or
;;; more levels up.  The number of levels is indicated by the fixnum in the
;;; `resumable-node-ascension-count?' slot.  If the
;;; resumable-node-ascension-count?  slot is nil, this structure represents
;;; either a toplevel RPC object or the final RPC subobject in the traversal
;;; tree (i.e., the last one to be transmitted).  These slots are used during
;;; object-passing transission.

;;; The `current-trailing-edge-object-p' slot in a resumable-instance-node-mixin
;;; is a boolean indicating if the given RPC object could be the last one
;;; traversed.  This slot is used during the object-passing preflight phase.  If
;;; this slot is non-nil and if the RPC object has no subobjects, then the given
;;; RPC object is indeed the last.

;;; The `current-superiors' slot in a resumable-instance-node-mixin structure
;;; describes the enclosing RPC objects above this one.  This slot contains an
;;; an icp-list, each element of which is either a resumable node or nil, and is
;;; used to compute the value in the resumable-node-ascension-count? slot during
;;; object-passing preflight.

;;; The `current-attribute-names' slot of a resumable-instance-node-mixin
;;; structure is an icp-list of attribute-spec structures that are remaining to
;;; be traversed in the object-passing preflight phase.

(def-structure (resumable-instance-or-complex-value-node-mixin
		 (:include resumable-icp-node-mixin))
  resumable-instance-current-object               ;shared G2 object or GSI struct
  (node-itself-sent-p nil)                        ;t or nil
  (ascension-target? nil)                         ;shared resumable-node-mixin or nil
  (resumable-node-ascension-count? nil)           ;a fixnum or nil
  (current-trailing-edge-object-p t)              ;t or nil
  (current-superiors nil                          ;icp-list of shared resumable-node-mixins
   :reclaimer reclaim-icp-list)
  )

(def-structure (resumable-instance-node-mixin
		 (:include resumable-instance-or-complex-value-node-mixin))
  (resumable-instance-reference-serial-number nil :reclaimer reclaim-frame-serial-number)      ;a frame serial number
  resumable-instance-class-name                   ;a symbol
  (resumable-class-name-corresponding-index? nil) ;a fixnum or nil
  (inferior-attributes nil                        ;icp-list of resumable-node-mixins
   :reclaimer reclaim-inferior-attributes)
  (current-cons-in-inferior-attributes? nil)      ;shares with inferior-attributes
  (last-cons-in-inferior-attributes? nil)         ;shares with inferior-attributes

  (current-attribute-names nil                    ;an icp-list of resumable-attribute-specs
   :reclaimer
   reclaim-icp-list-of-resumable-attribute-specs)
  symbolic-attribute-count                        ;a fixnum
  )


(def-substitution-macro resumable-complex-value-node-p (thing)
  (or (resumable-evaluation-sequence-node-p thing)
      (resumable-evaluation-structure-node-p thing)))

(def-substitution-macro resumable-instance-or-complex-value-node-p (thing)
  (or (resumable-complex-value-node-p thing)
      (resumable-instance-node-p thing)))

;;; The substitution macro `resumable-instance-node-p' is a predicate that
;;; returns true if its argument is an instance of a structure that :includes
;;; resumable-instance-node-mixin, and nil otherwise.  Note that this predicate
;;; is distinct from resumable-instance-node-mixin-p, which only tests if its
;;; argument is a resumable-node-mixin structure and returns false if given
;;; something that :includes that structure indirectly.

(def-substitution-macro resumable-instance-node-p (thing)
  (or (resumable-object-node-p thing)
      (resumable-object-vector-node-p thing)
      (resumable-value-vector-node-p thing)
      (resumable-history-node-p thing)
      (resumable-object-list-node-p thing)
      (resumable-value-list-node-p thing)))


;;; The `resumable-object-node' structure represents an RPC object, all of whose
;;; subobjects are accessed through symbolic attribute names.  This structure is
;;; only used on the sending side.

;;; Currently (jh, 2/16/94), the resumable-object-node structure contains no
;;; slots in addition to those provided by the resumable-node-mixin structure,
;;; which it :includes.

(def-structure (resumable-object-node
		 (:include resumable-instance-node-mixin)
		 (:constructor
		   make-resumable-object-node
		   (resumable-instance-current-object
		     resumable-instance-reference-serial-number
		     current-attribute-names
		     symbolic-attribute-count
		     resumable-attribute-spec?
		     resumable-instance-class-name
		     resumable-node-parent-node?))
		 (:reclaimer reclaim-resumable-object-node))
  )

;;; The `resumable-sequence-node-mixin' structure represents an RPC object, some
;;; of whose subobjects are accessible by means other than symbolic attribute
;;; names.  That is, the resumable-sequence-node-mixin structure represents
;;; objects such as vectors and lists.  Only structures that :include this
;;; structure are ever instantiated.  This structure is only used on the sender
;;; side.

;;; The `resumable-sequence-length' slot in a resumable-sequence-node-mixin
;;; structure is a fixnum giving the length of the sequence in the given RPC
;;; object.

;;; The `homogeneous-element-type?' slot in a resumable-sequence-node-mixin
;;; structure holds either a non-nil symbol or nil.  If the slot is a non-nil
;;; symbol, it is one of 'integer, 'float, 'symbol, 'truth, or 'text and
;;; indicates that all the elements in the sequence are RPC values of the given
;;; type.  If the slot is nil, the elements may be RPC values of various type,
;;; or may be full-fledged RPC subobjects.

(def-structure (resumable-sequence-node-mixin
		 (:include resumable-instance-node-mixin))
  resumable-sequence-length       ;a fixnum
  (homogeneous-element-type? nil) ;a symbol: either nil or one of
                                  ; INTEGER, |float|, SYMBOL, TRUTH, or TEXT
  )

;;; The `resumable-vector-node-mixin' structure represents an `RPC vector
;;; object', that is, an RPC object, some of whose subobjects are available
;;; through random access via a fixnum index.  In other words, the
;;; resumable-vector-node-mixin structure represents one-dimensional arrays.
;;; Note that, in addition to its vector contents, an RPC vector object may have
;;; other substructure accessible through symbolic attribute names.

;;; Only structures that :include the resumable-vector-node-mixin structure are
;;; ever instantiated.  This structure is only used on the sending side.

;;; The `internal-vector-for-object-passing' slot in a
;;; resumable-vector-node-mixin structure holds a pointer to the actual vector
;;; inside the RPC vector object.  This slot is used during object-passing
;;; preflight, but more importantly, if this vector holds only RPC values, these
;;; values may be batched for efficiency during the object-passing transmission
;;; phase.

(def-structure (resumable-vector-node-mixin
		 (:include resumable-sequence-node-mixin))
  internal-vector-for-object-passing  ;original vector (not to be mutated!)
  )

;;; The `resumable-object-vector-node' structure represents an RPC vector
;;; object, some of whose elements are themselves RPC objects.  These elements
;;; are represented by resumable nodes with appropriate attribute specs, in the
;;; inferior-attributes slot that this structure inherits from the
;;; resumable-instance-node-mixin structure.  This structure is only used on the
;;; sending side.

;; jh, 12/17/93.  The current-object-vector-index slot can help the end-user
;; debug when some subobject can't be sent, e.g., "can't send my-object-vector
;; because my-object-vector[32] has been deleted".

;;; The `current-object-vector-index' slot of a resumable-object-vector-node
;;; structure contains a fixnum index into the RPC object vector during
;;; object-passing preflight.

(def-structure (resumable-object-vector-node
		 (:include resumable-vector-node-mixin)
		 (:constructor
		   make-resumable-object-vector-node-internal
		   (resumable-instance-current-object
		     resumable-instance-reference-serial-number
		     current-attribute-names
		     symbolic-attribute-count
		     resumable-attribute-spec?
		     resumable-instance-class-name
		     resumable-sequence-length
		     internal-vector-for-object-passing
		     resumable-node-parent-node?)))
  (current-object-vector-index 0)            ;a fixnum
  highest-object-vector-index                ;a fixnum
  )

;;; The substitution-macro 'make-resumable-object-vector-node' creates a
;;; resumable-object-vector-node structure.  Some of its arguments provide
;;; values for slots inherited from the resumable-instance-node-mixin and
;;; resumable-vector-node-mixin structures.

(def-substitution-macro make-resumable-object-vector-node
		        (resumable-instance-current-object
			  resumable-instance-reference-serial-number
			  current-attribute-names
			  symbolic-attribute-count
			  resumable-attribute-spec?
			  resumable-instance-class-name
			  resumable-sequence-length
			  internal-vector-for-object-passing
			  resumable-node-parent-node?)
  (let ((object-vector-node
	  (make-resumable-object-vector-node-internal
	    resumable-instance-current-object
	    resumable-instance-reference-serial-number
	    current-attribute-names
	    symbolic-attribute-count
	    resumable-attribute-spec?
	    resumable-instance-class-name
	    resumable-sequence-length
	    internal-vector-for-object-passing
	    resumable-node-parent-node?)))
    (setf (highest-object-vector-index object-vector-node)
	  (1- resumable-sequence-length))
    object-vector-node))

;;; The `resumable-value-vector-node' structure represents an RPC vector object,
;;; all of whose elements are RPC values.  Note that this structure makes use of
;;; the homogeneous-element-type? slot it inherits from the
;;; resumable-sequence-node-mixin structure.  This structure is only used on the
;;; sending side.

;;; The `highest-empty-value-vector-index' slot in a resumable-value-vector-node
;;; structure contains a fixnum giving the largest possible index into the given
;;; RPC vector object.

(def-structure (resumable-value-vector-node
		 (:include resumable-vector-node-mixin)
		 (:constructor
		   make-resumable-value-vector-node-internal
		   (resumable-instance-current-object
		     resumable-instance-reference-serial-number
		     current-attribute-names
		     symbolic-attribute-count
		     resumable-attribute-spec?
		     resumable-instance-class-name
		     resumable-sequence-length
		     internal-vector-for-object-passing
		     resumable-node-parent-node?)))
  ;; ... consolidate with highest-empty-object-vector-index slot?
  highest-empty-value-vector-index            ;a fixnum
  )

;;; The substitution-macro 'make-resumable-value-vector-node' creates a
;;; resumable-value-vector-node structure.  Some of its arguments provide values
;;; for slots inherited from the resumable-instance-node-mixin and
;;; resumable-vector-node-mixin structures.

(def-substitution-macro make-resumable-value-vector-node
                        (resumable-instance-current-object
			  resumable-instance-reference-serial-number
			  current-attribute-names
			  symbolic-attribute-count
			  resumable-attribute-spec?
			  resumable-instance-class-name
			  resumable-sequence-length
			  internal-vector-for-object-passing
			  resumable-node-parent-node?)
  (let ((value-vector-node
	  (make-resumable-value-vector-node-internal
	    resumable-instance-current-object
	    resumable-instance-reference-serial-number
	    current-attribute-names
	    symbolic-attribute-count
	    resumable-attribute-spec?
	    resumable-instance-class-name
	    resumable-sequence-length
	    internal-vector-for-object-passing
	    resumable-node-parent-node?)))
    (setf (highest-empty-value-vector-index value-vector-node)
	  (1- resumable-sequence-length))
    value-vector-node))

(defvar size-of-cached-subsequence-for-resumable-history 128)

(defun-void reclaim-cached-history-subsequence (history-subsequence)
  (cond
    ((managed-float-array-p history-subsequence)
     (reclaim-managed-float-array history-subsequence))
    ((simple-vector-p history-subsequence)
     (loop for index from 0 below (length history-subsequence)
	   for element? = (svref history-subsequence index)
	   do
       (unless (evaluation-value-p element?)
	 (loop-finish))
       (reclaim-evaluation-value element?)
       (setf (svref history-subsequence index) nil)
	   finally
	     (reclaim-managed-simple-vector history-subsequence)))
    ((null history-subsequence) nil)
    #+development
    (t (cerror "Do nothing (This behavior is what the user would see)"
	       "RECLAIM-CACHED-HISTORY-SUBSEQUENCE: Unexpected thing ~s"
	       history-subsequence))))

(defun-void reclaim-icp-list-of-evaluation-values? (icp-list)
  (loop for element? in icp-list
	when element?
	  do (reclaim-evaluation-value element?)
	finally (reclaim-icp-list icp-list)))

(def-structure (resumable-history-node
		 (:include resumable-sequence-node-mixin)
		 (:constructor
		   make-resumable-history-node
		   (resumable-instance-current-object
		     resumable-instance-reference-serial-number
		     current-attribute-names
		     symbolic-attribute-count
		     resumable-attribute-spec?
		     resumable-instance-class-name
		     resumable-sequence-length
		     resumable-node-parent-node?)))
  internal-history-for-object-passing?                  ;original history structure
                                                        ; (not to be mutated!)
  (internal-history-spec-for-object-passing nil         ;icp-list copy of history spec
   :reclaimer reclaim-icp-list)
  (dynamic-history-info-for-object-passing nil          ;icp-list of evaluation
   :reclaimer reclaim-icp-list-of-evaluation-values?)   ; quantities or nil
  ring-index-of-oldest-history-value                    ;fixnum
  (ring-index-of-next-uncached-history-value? nil)      ;fixnum or nil
  (count-of-history-elements-transmitted 0)             ;fixnum
  (timestamp-of-next-uncached-history-value? nil)       ;evaluation-float
  (count-of-preceding-identically-timestamped-values 0) ;fixnum
  (index-of-next-cached-history-value? nil)             ;fixnum or nil
  (cached-timestamp-subsequence-for-resumable-history?  ;managed simple vector
    nil                                                 ; of evaluation values
    :reclaimer reclaim-cached-history-subsequence)      ; or managed-float-array
  (cached-value-subsequence-for-resumable-history?      ;managed simple vector
    nil                                                 ; of evaluation values
    :reclaimer reclaim-cached-history-subsequence)      ; or managed-float-array
  )


    

;;; The `resumable-list-node-mixin' structure represents an `RPC list object',
;;; that is, an RPC object, some of whose subobjects are available through
;;; "head" and "tail"-like operations.  In short, the resumable-list-node-mixin
;;; structure represents lists.  Note that, in addition to its list contents, an
;;; RPC list object may have other substructure accessible through symbolic
;;; attribute names.

;;; Only structures that :include the resumable-list-node-mixin structure are
;;; ever instantiated.  This structure is only used on the sending side.

;;; The `internal-list-for-object-passing' slot in a resumable-list-node-mixin
;;; structure holds a pointer to the first element of the actual list inside the
;;; RPC list object.  This slot is used during object-passing preflight, but
;;; more importantly, if this list holds only RPC values, these values may be
;;; batched for efficiency during the object-passing transmission phase.

(def-structure (resumable-list-node-mixin
		 (:include resumable-sequence-node-mixin))
  internal-list-for-object-passing ;original g2-list-element
                                   ; (not to be mutated!)
  )

;;; The `resumable-object-list-node' structure represents an RPC list object,
;;; some of whose elements are themselves RPC objects.  These elements are
;;; represented by resumable nodes with appropriate attribute specs, in the
;;; inferior-attributes slot that this structure inherits from the
;;; resumable-instance-node-mixin structure.  This structure is only used on the
;;; sending side.

;; jh, 12/17/93.  The current-object-list-index slot can help the end-user debug
;; when some list element can't be sent, e.g., "can't send my-object-list
;; because element # 32 has been deleted".

(def-structure (resumable-object-list-node
		 (:include resumable-list-node-mixin)
		 (:constructor
		   make-resumable-object-list-node
		   (resumable-instance-current-object
		     resumable-instance-reference-serial-number
		     current-attribute-names
		     symbolic-attribute-count
		     resumable-attribute-spec?
		     resumable-instance-class-name
		     internal-list-for-object-passing
		     resumable-sequence-length
		     resumable-node-parent-node?)))
  )

;;; The `resumable-object-list-node' structure represents and RPC list object,
;;; all of whose elements are RPC values.  Note that this structure makes use of
;;; the homogeneous-element-type? slot it inherits from the
;;; resumable-sequence-node-mixin structure.

(def-structure (resumable-value-list-node
		 (:include resumable-list-node-mixin)
		 (:constructor
		   make-resumable-value-list-node
		   (resumable-instance-current-object
		     resumable-instance-reference-serial-number
		     current-attribute-names
		     symbolic-attribute-count
		     resumable-attribute-spec?
		     resumable-instance-class-name
		     internal-list-for-object-passing
		     resumable-sequence-length
		     resumable-node-parent-node?)))
  ;; current-value-list-index is 0-based, unlike lists seen by the G2 user.
  (current-value-list-index 0)        ;a fixnum 
  )


(def-structure (resumable-evaluation-sequence-node-mixin
		(:include resumable-instance-or-complex-value-node-mixin))
  resumable-evaluation-sequence-length       ;a fixnum
  (current-evaluation-vector-index 0)            ;a fixnum
  highest-evaluation-vector-index                ;a fixnum
  )

(def-structure (resumable-evaluation-sequence-node
		 (:include resumable-evaluation-sequence-node-mixin)
		 (:constructor
		   make-resumable-evaluation-sequence-node
		   (resumable-instance-current-object
		     resumable-evaluation-sequence-length
		     resumable-node-parent-node?))))

(def-structure (resumable-evaluation-structure-node
		 (:include resumable-evaluation-sequence-node-mixin)
		 (:constructor
		   make-resumable-evaluation-structure-node
		   (resumable-instance-current-object
		     resumable-evaluation-sequence-length
		     resumable-node-parent-node?)))
  (resumable-evaluation-structure-current-name-processed-p nil))


;;;; [5.1] Macros for Type Dispatching on Resumable Nodes

(defun-for-macro get-predicate-from-resumable-node-keyword (keyword node)
  (case keyword
    (:circular      `(resumable-circular-node-p ,node))
    (:value         `(resumable-value-node-p ,node))
    (:object        `(resumable-object-node-p ,node))
    (:object-vector `(resumable-object-vector-node-p ,node))
    (:value-vector  `(resumable-value-vector-node-p ,node))
    (:history       `(resumable-history-node-p ,node))
    (:object-list   `(resumable-object-list-node-p ,node))
    (:value-list    `(resumable-value-list-node-p ,node))
    (:instance      `(resumable-instance-node-p ,node))
    (:instance-or-complex-value `(resumable-instance-or-complex-value-node-p ,node))
    (:sequence      `(resumable-evaluation-sequence-node-p ,node))
    (:structure     `(resumable-evaluation-structure-node-p ,node))
    ((otherwise t)   t)
    (otherwise (error "RESUMABLE-NODE-TYPECASE: ~
                       unknown type keyword ~s near ~s"
		      keyword
		      most-recent-defun-name))))

;;; resumable-node-typecase keyform &rest (keyword-or-list . actions) ...

;;; The macro `resumable-node-typecase' resembles typecase in that it dispatches
;;; on the type of its keyform rather than the value.  The keyform of this macro
;;; is a resumable node.  The type of the resumable node is specified by one of
;;; the keywords :circular, :value,:object,:object-vector,:value-vector,
;;; :object-list, or :value-list.  Like case, disjunctions of these types may
;;; occur, when the keyword-or-list is a list containing these keywords.  Unlike
;;; typecase, arbitrary boolean formulations of these types are not permitted.

(defmacro resumable-node-typecase (node &body clauses)
  (avoiding-variable-capture (node)
    `(cond
       ,@(loop for (node-type-keyword-or-keywords . actions) in clauses
	       collect
	       `(,(if (symbolp node-type-keyword-or-keywords)
		      (get-predicate-from-resumable-node-keyword
			node-type-keyword-or-keywords
			node)
		      `(or
			 ,@(loop for keyword in node-type-keyword-or-keywords
				 collect
				 (get-predicate-from-resumable-node-keyword
				   keyword
				   node))))
		  ,@actions))
       ,@(if (and (eval-feature :development)
		  (loop for (keyword-or-list) in clauses
			never
			(memq keyword-or-list '(t otherwise))))
	     `((t (cerror "Continue, taking no action.  ~
                           (This behavior is what the user would get)"
			  "RESUMABLE-NODE-TYPECASE: unexpected thing ~s"
			  ,node)))
	     nil))))




;;;; [5.2] Macros for Type Dispatching on Leaf Values

(defun-for-macro get-actions-for-evaluation-typecase-clause (item type actions)
  (if (or (eq type 'evaluation-no-value)
	  (and (eq type 'evaluation-float)
	       (not
		 ;; Kludge against allocating temporary float if unnecessary.
		 ;; Really should code-walk for :eval spots.
		 (block occurs-in-block
		   (labels ((occurs-in (forms)
			      (cond
				((or (null forms) (text-string-p forms))
				 nil)
				((not (consp forms))
				 (when (eql forms 'evaluation-float)
				   (return-from occurs-in-block t)))
				(t (occurs-in (car forms))
				   (occurs-in (cdr forms))))))
		     (occurs-in actions)
		     nil)))))
      actions
      `((let ((,type
		 ,(case type
		    (evaluation-integer
		     `(evaluation-integer-value ,item))
		    (evaluation-float
		     `(evaluation-float-value ,item))
		    (managed-float item)
		    (evaluation-text
		     `(evaluation-text-value ,item))
		    (evaluation-truth-value
		     `(evaluation-truth-value-value ,item))
		    (evaluation-symbol
		     `(evaluation-symbol-symbol ,item))
		    (evaluation-sequence item)
		    (evaluation-structure item))))
	  ,@actions))))

;;; The macro `evaluation-typecase' resembles typecase, but dispatches on the
;;; type of evaluation-value given it as its keyform.  Each clause is of the
;;; form (<type> . <actions>), where <type> is one of evaluation-integer,
;;; evaluation-float, managed-float, evaluation-text, or evaluation-symbol.
;;; Inside <actions>, an implicit progn, the symbol given by <type> is bound to
;;; the value contained inside the evaluation-value, except in the cases of
;;; evaluation-structure and evaluation-sequence where it simply is bound to
;;; the evaluation-structure or evaluation-sequence (per usual).

;;; The difference between an evaluation-float clause and a managed-float clause
;;; is that the former binds its variable to a temporary gensym-float and the
;;; latter binds it variable to a managed-float.

;;; One implication of the binding scheme of evaluation-typecase is that a
;;; clause in which <type> is evaluation-float must occur within a
;;; with-temporary-gensym-float-creation context, since evaluation-float-value
;;; creates a temporary float.  As a special case, however, if the <actions> of
;;; such a clause do not reference the variable evaluation-float, then no
;;; temporary float is created.  For a <type> other than evaluation-float where
;;; <actions> do not reference <type>, compiler warnings will occur unless a
;;; (declare (ignore <type>)) form is added as the first subform of <actions>.

(defmacro evaluation-typecase (item &body clauses)
  (avoiding-variable-capture (item)
    `(cond 
       ,@(loop for (type . actions) in clauses
	       do
	   (unless (memq type 
			 '(evaluation-integer
			   evaluation-float
			   managed-float
			   evaluation-text
			   evaluation-truth-value
			   evaluation-symbol
			   evaluation-sequence
			   evaluation-structure
			   evaluation-no-value
			   t otherwise))
	     (error "EVALUATION-TYPECASE: unknown type ~s"
		    type))
	       collect
	       (if (memq type '(t otherwise))
		   `(t ,@actions)
		   `((,(case type
			 (evaluation-integer     'evaluation-integer-p)
			 ((evaluation-float
			    managed-float)       'evaluation-float-p)
			 (evaluation-text        'evaluation-text-p)
			 (evaluation-truth-value 'evaluation-truth-value-p)
			 (evaluation-symbol      'evaluation-symbol-p)
			 (evaluation-sequence    'evaluation-sequence-p)
			 (evaluation-structure   'evaluation-structure-p)
			 (evaluation-no-value    'null))
		       ,item)
		     ,@(get-actions-for-evaluation-typecase-clause
			 item
			 type
			 actions))))
       ,@(if (eval-feature :development)
	     `((t (cerror "Continue, taking no action.  ~
                           (This behavior is what the user would get)"
			  "~s is of unknown evaluation type"
			  ,item)))
	     nil))))




;;;; [5.3] Reclaimers for Resumable Object Contents

(defun-void reclaim-icp-list-of-resumable-attribute-specs (list)
  (loop for spec in list
	do (reclaim-resumable-attribute-spec spec)
	finally (reclaim-icp-list list)))
			 
(defun-void reclaim-resumable-node (resumable-node)
  (resumable-node-typecase resumable-node
    (:circular      (reclaim-resumable-circular-node resumable-node))
    (:value         (reclaim-resumable-value-node resumable-node))
    (:object        (reclaim-resumable-object-node resumable-node))
    (:object-vector (reclaim-resumable-object-vector-node resumable-node))
    (:value-vector  (reclaim-resumable-value-vector-node resumable-node))
    (:history       (reclaim-resumable-history-node resumable-node))
    (:object-list   (reclaim-resumable-object-list-node resumable-node))
    (:value-list    (reclaim-resumable-value-list-node resumable-node))
    (:sequence      (reclaim-resumable-evaluation-sequence-node resumable-node))
    (:structure     (reclaim-resumable-evaluation-structure-node resumable-node))
    ))

(def-substitution-macro reclaim-if-resumable-node (resumable-node?)
  (when resumable-node?
    (reclaim-resumable-node resumable-node?)))

(defun-void reclaim-inferior-attributes (inferior-attributes)
  (loop for inferior-attribute in inferior-attributes
	do
    (reclaim-resumable-node inferior-attribute))
  (reclaim-icp-list inferior-attributes))

(defun-void reclaim-internal-value-list (internal-value-list)
  (loop for internal-value in internal-value-list
	do
    (reclaim-evaluation-value internal-value))
  (reclaim-icp-list internal-value-list))
						       



;;;; [6.1] Hashtable for Circularity Checks

(def-hash-table object-circularity-hashtable
    :constructor            make-object-circularity-hashtable
    :accessor               get-object-circularity-hashtable-entry
    :clearer                clear-object-circularity-hashtable
    :hash-function-or-macro frame-hash-function
    :size                   131 ; use a prime number
    )

;; jh, 6/10/94.  Changed the :hash-function-or-macro of
;; object-circularity-hashtable from the macro frame-serial-number to the
;; function frame-serial-number-function.  Otherwise, a developer working on
;; both GSI and G2 in the same sandbox would experience problems caused by
;; stubbing out frame-serial-number in GSI-PATCHES.  Stubbing out this macro as
;; a function would make if this module was compiled in s GSI and used in a G2
;; under the same sandbox.  Changing the :hash-function-or-macro to a function
;; will fix the immediate problem until we can do a more systematic migration of
;; G2-specific machinery out of RPC-COMMON2.  Also made comparable changes in
;; make-sending-resumable-object




;;;; [6.3] Sending Side RPC Object Arguments

;;;; [6.3.1] Sending Side RPC Object Container Structure

;;; The `sending-resumable-object' structure manages the information associated
;;; with a single RPC object on the sending side.

;;; The `object-to-be-passed' slot of a sending-resumable-object structure
;;; contains the RPC object that was given to the RPC as an argument.  Note that
;;; this object may also be reached indirectly through the
;;; toplevel-resumable-node slot of this structure.

;;; The `toplevel-resumable-node' slot of a sending-resumable-object structure
;;; contains a resumable node that represents the RPC object itself, rather than
;;; any of its subobjects.

;;; The `current-resumable-node' slot of a sending-resumable-object structure
;;; contains the resumable node currently being processed by an object-passing
;;; task.

;;; The `resumable-object-reference-serial-number' slot of a
;;; sending-resumable-object structure is an integer that is a frame seral
;;; number stored so that a resumed object-passing task can determine if the
;;; frame representing the RPC object is still current.  If the frame is not
;;; current, the RPC must be discontinued on the sending side and any
;;; partially-built RPC objects on the receiving side must be reclaimed.

;;; The `resumable-object-icp-socket' slot of a sending-resumable-object
;;; structure contains the ICP socket through which the RPC is being conduced.

;;; The `resumable-object-priority' slot of a sending-resumable-object structure
;;; contains a fixnum giving the priority of any object-passing task.

;;; The `resumable-object-allocated-bandwidth' slot of a
;;; sending-resumable-object structure contains a fixnum representing the number
;;; of ICP bytes that have been used to transmit this object and its subobjects
;;; during the current object-passing transmission task.

;;; The `resumable-object-guessed-bandwidth-p' slot of a
;;; sending-resumable-object structure contains a boolean.  During the
;;; object-passing transmission phase of resumable-value-vector-nodes or
;;; resumable-value-list-nodes, it is necessary to determine how many elements
;;; can be sent during the current task.  This determination includes a guess at
;;; the amount of timeslice remaining in the current task.  (We have to guess
;;; because get-fixnum-time is purposely too coarse to change much in a single
;;; task, for reasons of scheduler efficiency.)  The
;;; resumable-object-guessed-bandwidth-p flag is set to a non-nil value after
;;; the elements are transmitted.  If, despite the guess, the timeslice has not
;;; been expended this flag directs the current object-passing transmission task
;;; to suspend, since further guesses are not possible (again, because
;;; get-fixnum-time changes so infrequently).  The
;;; resumable-object-guessed-bandwidth-p flag is cleared to nil at the beginning
;;; of each object-passing transmission task.

;;; The `resumable-object-circularity-hashtable' slot of a
;;; sending-resumable-object structure contains an object-circularity-hashtable
;;; that participates in circularity checks.

;;; The `transmit-resumable-object-as-handle-p' slot of a
;;; sending-resumable-object structure is non-nil if the RPC object should be
;;; transmitted as a corresponding ICP object index, non-nil otherwise.

;;; The `resumable-object-included-slots' slot of a sending-resumable-object
;;; structure is a slot-value list of symbolic attribute names supplied by the
;;; user.  This list shares atructure with the remote-procedure-declaration
;;; frame governing the RPC, and should not be reclaimed.  If the
;;; resumable-object-included-slots is non-nil, they are the only slots used
;;; during the object-passing preflight phase.  All others are ignored and any
;;; RPC subobjects reached through them are not transmitted.  Vector and list
;;; elements are sent as usual; this restriction only applies to symbolic
;;; attribute names.  This description has been left purposely vague (as of
;;; 2/16/94, jh) until the G2 multiple inheritance facility jells.

;;; The `resumable-object-excluded-slots' slot of a sending-resumable-object
;;; structure is a slot-value list of symbolic attribute names supplied by the
;;; user.  This list shares atructure with the remote-procedure-declaration
;;; frame governing the RPC, and should not be reclaimed.  If the
;;; resumable-object-excluded-slots is non-nil, the object-passing preflight
;;; phase will traverse all RPC subobjects except those reached through these
;;; slots.  Vector and list elements are sent completely; this restriction only
;;; applies to symbolic attribute names.  This description has been left
;;; purposely vague (as of 2/16/94, jh) until the G2 multiple inheritance
;;; facility jells.

;; ...
;; jh, 2/16/94.  Have to deal with "system slots" and with what an unqualified slot
;; name means when qualification is possible.

;;; The `resumable-object-task' slot of a sending-resumable-object structure is
;;; the location the scheduler uses to store the object-passing task associated
;;; with the given RPC object.

(def-structure (sending-resumable-object
		 (:include resumable-icp-object-mixin)
		 (:reclaimer reclaim-sending-resumable-object-internal)
		 (:constructor
		   make-sending-resumable-object-internal
		   (resumable-object-rpc-name?
		     object-or-handle-to-be-passed
		     toplevel-resumable-node
		     current-resumable-node
		     resumable-object-reference-serial-number
		     resumable-object-icp-socket
		     resumable-object-icp-interface-frame?
		     resumable-object-priority
		     transmit-resumable-object-as-handle-p
		     resumable-object-included-slots
		     resumable-object-excluded-slots
		     resumable-object-included-system-slots)))

  object-or-handle-to-be-passed                 ;fixnum or shared G2 object or GSI struct
  (toplevel-resumable-node nil                  ;a resumable-node-mixin
   :reclaimer reclaim-if-resumable-node)
  current-resumable-node                        ;shared resumable-node-mixin
  resumable-object-icp-socket                   ;shared icp-socket structure
  resumable-object-icp-index                    ;fixnum
  resumable-object-icp-interface-frame?         ;shared G2 object
  resumable-object-priority                     ;a fixnum
  (resumable-object-allocated-bandwidth 0)      ;a fixnum
  resumable-object-guessed-bandwidth-p          ;a boolean
  (resumable-object-bandwidth-denied-by-clog?
    nil)                                        ;a fixnum or nil
  (resumable-object-circularity-hashtable       ;a Gensym hash-table
   (make-object-circularity-hashtable)
   :reclaimer
   reclaim-object-circularity-hashtable)
  (resumable-object-task nil                    ;managed by the scheduler
   :reclaimer
   arrange-to-cancel-task-in-sending-resumable-object)
  (resumable-object-included-slots nil)         ;shared icp-cons tree
  (resumable-object-excluded-slots nil)         ;shared icp-cons tree
  (resumable-object-included-system-slots nil)  ;shared icp-cons tree  
  )

(defun-void arrange-to-cancel-task-in-sending-resumable-object (task?)
  (when task?
    (setf (schedule-task-reclaimable-by-scheduler-p task?) t)))
    
;;; The substitution macro `make-sending-resumable-object' creates a resumable
;;; object on the sending side.  Some of the slots it initializes are provided
;;; by the resumable-object structure, which it :includes.

(def-substitution-macro make-sending-resumable-object 
    (rpc-name
      object
      toplevel-resumable-node
      icp-socket
      icp-interface?
      priority
      as-handle-p
      includes
      excludes
      system-includes)
  (let* ((sending-resumable-object
	   (make-sending-resumable-object-internal
	     rpc-name
	     object
	     toplevel-resumable-node
	     toplevel-resumable-node
	     (unless (consp object)
	       (if icp-interface?
		   (let ((fsn1 (frame-serial-number object))
			 (fsn2 (frame-serial-number icp-interface?)))
		     (if (frame-serial-number-< fsn1 fsn2) fsn2 fsn1))
		   (frame-serial-number object)))
	     icp-socket
	     icp-interface?
	     priority
	     as-handle-p
	     includes
	     excludes
	     system-includes))
	 (current-icp-socket icp-socket)
	 (current-icp-port (icp-output-port current-icp-socket))
	 new-icp-index)
    (writing-icp-message-group (current-icp-port)
      (setq new-icp-index
	    (establish-new-object-index-for-resumable-object
	      sending-resumable-object
	      current-icp-port)))
    (setf (resumable-object-icp-index sending-resumable-object) new-icp-index)
    sending-resumable-object))

;; jh, 6/10/94.  See note under the def-hash-table form for
;; object-circularity-hashtable for details on why we use
;; frame-serial-number-function rather than frame-serial-number in
;; make-sending-resumable-object.

(def-substitution-macro make-sending-resumable-object-as-handle
    (rpc-name handle icp-socket reference-type)
  (let ((sending-resumable-object-as-handle
	  (make-sending-resumable-object-internal
	    rpc-name
	    handle
	    nil
	    nil
	    nil
	    icp-socket
	    nil
	    nil
	    reference-type ;transmit-resumable-object-as-handle-p
	    nil
	    nil
	    nil)))
    sending-resumable-object-as-handle))




;;;; [6.3.2] Sending Side Circularity Checking Mechanism

;;; The function `get-index-of-circular-resumable-node' takes two arguments: an
;;; RPC object and a sending-resumable-object structure.  If the given RPC
;;; object has already occurred during object-passing preflight, this function
;;; returns a corresponding ICP object index that will be used to denote the
;;; shared RPC object on the receiving side.

(defun-allowing-unwind get-index-of-circular-resumable-node
    (object resumable-object)
  (let ((circular-resumable-node?
	  (get-object-circularity-hashtable-entry
	    object
	    (resumable-object-circularity-hashtable resumable-object))))
    (if circular-resumable-node?
	(let* ((current-icp-socket
		 (resumable-object-icp-socket resumable-object))
	       (current-icp-port
		 (icp-output-port current-icp-socket))
	       (icp-object-index?
		 (get-icp-object-index-for-resumable-instance-node
		   circular-resumable-node?
		   current-icp-port)))
	  (or icp-object-index?
	      (let (new-index)
		(writing-icp-message-group (current-icp-port)
		  (setq new-index
			(establish-new-object-index-for-resumable-instance-node
			  circular-resumable-node?
			  current-icp-port)))
		new-index)))
	nil)))

;;; The function `set-index-of-circular-resumable-node' takes three arguments:
;;; an RPC object, a sending-resumable-object structure, and the resumable node
;;; corresponding to the RPC object.  It records the resumable node in the
;;; resumable-object-circularity-hashtable slot of the resumable object for
;;; subsequent circularity checks.

(defun set-index-of-circular-resumable-node
    (object resumable-object resumable-node)
  (setf (get-object-circularity-hashtable-entry
	  object
	  (resumable-object-circularity-hashtable resumable-object))
	resumable-node))




;;;; [8] Reclaimers for RPC Object Arguments and Argument Lists

(defun-allowing-unwind reclaim-sending-and-receiving-resumable-object
    (sending-resumable-object)
  (let* ((icp-socket
	   (resumable-object-icp-socket sending-resumable-object))
	 (reference-number
	   (resumable-object-reference-serial-number
	     sending-resumable-object))
	 (need-to-reclaim-remote-side-p
	   (frame-has-not-been-reprocessed-p
	     (object-or-handle-to-be-passed sending-resumable-object)
	     reference-number))
	 (index-space-name
	  (name-of-corresponding-icp-object-index-space 'resumable-object)))
    (when need-to-reclaim-remote-side-p
      (g2-reclaim-remote-side-for-deactivate-object-passing
	sending-resumable-object
	icp-socket
	index-space-name))
    (g2-reclaim-sending-resumable-object sending-resumable-object)))

(defun-void g2-reclaim-single-receiving-resumable-object
    (receiving-resumable-object)
  (let ((object-being-built?
	  (resumable-object-being-built? receiving-resumable-object)))
    (when (and (framep object-being-built?)
	       (not (rpc-object-handed-off-to-user-p object-being-built?)))
      (delete-frame object-being-built?))))




;;;; [9] G2 Capability for Object Passing

;;; Every block automatically has the ability to participate in object-passing.
;;; There is no need for a special mixin capability class.  The state needed for
;;; object-passing is held in an object-passing-info structure in the block's
;;; object-passing-info? attribute.

;;; The `rpc-object-handed-off-to-user-p' attribute in an object-passing-info
;;; structure is non-nil if the G2 user is responsible for reclaiming this
;;; object, and nil otherwise.

(def-structure (object-passing-info (:type vector)
				    (:creations-at-a-time 100))
  (resumable-object-structure-list-1 nil)    ;slot-value-list of shared structs
  (g2-rpc-object-handed-off-to-user-p-1 t)   ;a boolean
  (parent-item-lists-or-arrays-1 nil)        ;icp-list of shared frames
  (icp-object-map-for-registered-item-1 nil) ;gensym-list
  )

(define-slot-group-accessor resumable-object-structure-list
    object-passing-info
    object-passing-info?
  resumable-object-structure-list-1 nil :frame)

(define-slot-group-accessor g2-rpc-object-handed-off-to-user-p
    object-passing-info
    object-passing-info?
  g2-rpc-object-handed-off-to-user-p-1 t :frame)

(defun-simple g2-rpc-object-handed-off-to-user-p-function (block)
  (g2-rpc-object-handed-off-to-user-p block))

(define-slot-group-accessor parent-item-lists-or-arrays
    object-passing-info
    object-passing-info?
  parent-item-lists-or-arrays-1 nil :frame)

(define-slot-group-accessor icp-object-map-for-registered-item
    object-passing-info
    object-passing-info?
  icp-object-map-for-registered-item-1 nil :frame)

(defun-simple icp-object-map-for-registered-item-function (block)
  (icp-object-map-for-registered-item block))

(defvar g2-to-g2-uses-references-p nil)

(defun-simple item-references-enabled-p (icp-socket)
  (let ((enabled-p (icp-socket-uses-item-references icp-socket)))
    (when (eq enabled-p 'unknown)
      (setq enabled-p
	    (current-system-case
	      (gsi gsi-use-references-p)
	      (ab (case (icp-socket-listener-client? icp-socket)
		    (g2 g2-to-g2-uses-references-p)
		    (gsi (setq enabled-p
			       (=f 1 (get-remote-icp-version-info-value
				       icp-socket 'gsi-references-in-use 0)))
			 (when (and enabled-p (not g2-to-g2-uses-references-p))
			   (enable-references-for-item-passing))
			 enabled-p)
		    (t nil)))
	      (t nil)))
      (setf (icp-socket-uses-item-references icp-socket) enabled-p))
    enabled-p))

(defun-void initialize-gsi-data-service (registered-item interface)
  (let ((gsi-interface-name?
	  (get-slot-value-if-any registered-item 'gsi-interface-name)))
    (when (and gsi-interface-name?
	       (of-class-p interface 'gsi-interface)
	       (eq gsi-interface-name?
		   (get-primary-name-for-frame-if-any interface)))
      #+development
      (when (=f 0 (icp-protocol-version-for-output current-icp-socket))
	(error "Trying to register an item before ~
                receiving the version of the other side"))
      (get-or-make-gsi-sensor
	registered-item
	(get-slot-value-if-any registered-item 'gsi-collection-interval)))))

(def-icp-object-type registered-item
    (item-index-space
      (icp-object-map-for-registered-item registered-item))
  (let ((interface (enclosing-interface-frame? current-icp-socket))
	(sensor-p (frame-of-class-p registered-item 'gsi-data-service))
	(corresponding-icp-object-index-for-item-reference corresponding-icp-object-index))
    (when sensor-p
      (initialize-gsi-data-service registered-item interface))
    (if (with-bifurcated-version-for-output (item-reference-icp-version)
	  nil
	  (item-references-enabled-p current-icp-socket))	     
	(send-icp-create-item-reference registered-item)
	(unless (eq 'g2 (icp-socket-listener-client? current-icp-socket))
	  (if sensor-p
	      (define-or-configure-gsi-sensor
		  registered-item
		  corresponding-icp-object-index
		interface)
	      (with-bifurcated-version-for-output (gsi-item-registration-icp-version)
		nil
		(gsi-register-item
		  registered-item corresponding-icp-object-index interface)))))))

(def-icp-object-type class-description
    (item-index-space
      (icp-object-map-for-class-description class-description))
  (let ((corresponding-icp-object-index-for-item-reference corresponding-icp-object-index))
    (if (with-bifurcated-version-for-output (item-reference-icp-version)
	  nil
	  (item-references-enabled-p current-icp-socket))	     
	(send-icp-create-item-reference class-description)
	nil)))

(def-icp-index-reclaimer registered-item)

(defun-simple save-icp-object-map-for-registered-item (frame)
  (loop with icp-object-map = (icp-object-map-for-registered-item frame)
	for (icp-port index) on icp-object-map by 'cddr
	do (setf (get-registered-item-from-icp-port icp-port index) nil)
	finally (setf (icp-object-map-for-registered-item frame) nil)
		(return icp-object-map)))

(defun-void restore-icp-object-map-for-registered-item (frame icp-object-map)
  (setf (icp-object-map-for-registered-item frame) icp-object-map)
  (loop for (icp-port index) on icp-object-map by 'cddr
	do (setf (get-registered-item-from-icp-port icp-port index) frame)))

#+development
(defun show-object-map-for-all-frames ()
  (loop for instance being each class-instance of 'system-item ; proto-block
	for object-passing-info? = (get-slot-value instance 'object-passing-info?)
	do
    (when object-passing-info?
      (let ((object-map
	      (icp-object-map-for-registered-item-1 object-passing-info?)))
	(when object-map
	  (format t "~&~S  ~S~%" instance object-map))))))

#+development
(defun show-all-frame-icp-information ()
  (show-object-map-for-all-frames)
  (skim-index-spaces-of-all-icp-sockets nil)
  (values))

;; jh, 5/27/94.  See three-semi doc under "G2 System Procedures for Network
;; Registration" for why we use a hashtable instead of the ICP corresponding
;; object mechanism to provide network handles.

(defun-simple get-item-from-local-handle (handle icp-socket)
  (get-registered-item-from-icp-port-if-any
    (icp-output-port icp-socket)
    handle))

(defun-simple lookup-item-from-frame-serial-number-table-of-port (frame-serial-number icp-port)
  (get-item-from-frame-serial-number
    frame-serial-number
    (frame-serial-number-to-item-table icp-port)))

(defun-simple register-item-with-socket (item icp-socket use-existing-message-group-p)
  (let ((output-port (icp-output-port icp-socket)))
    (or (get-icp-object-index-for-registered-item item output-port)
	(if use-existing-message-group-p
	    (make-corresponding-icp-registered-item item)
	    (writing-icp-message-group (output-port)
	      (make-corresponding-icp-registered-item item))))))

(defun-void deregister-item-with-socket (item icp-socket)
  (loop with deregister-corresponding-object? = t
	with input-port = (icp-input-port icp-socket)
	with output-port = (icp-output-port icp-socket)
	for icp-object-map-tail = (icp-object-map-for-registered-item item)
				then next-tail
	while icp-object-map-tail
	for next-tail = (cddr icp-object-map-tail)
	for (icp-port index) = icp-object-map-tail
	when (or (eq icp-port input-port) (eq icp-port output-port))
	  do (reclaim-index-space-location-and-corresponding-objects
	       item icp-port index 'item-index-space)))

(defun-simple ensure-registration-on-network (item icp-interface)
  (let ((icp-socket (icp-socket-of-interface-object icp-interface)))
    (when (and icp-socket
	       (icp-connection-open-p icp-socket)
	       (not (icp-connection-being-shutdown? icp-socket)))
      (register-item-with-socket item icp-socket nil))))

(defun-void deregister-item-on-network (item icp-interface)
  (let ((icp-socket (icp-socket-of-interface-object icp-interface)))
    (when (and icp-socket
	       (icp-connection-open-p icp-socket)
	       (not (icp-connection-being-shutdown? icp-socket)))
      (deregister-item-with-socket item icp-socket))))

(def-class-method deactivate (system-item)
  (unless in-suspend-resume-p
    (let ((do-not-reclaim-runs-while-inactive-entries t))
      (reclaim-icp-object-map-for-registered-item system-item))))

(def-class-method cleanup (system-item)
  (reclaim-icp-object-map-for-registered-item system-item))

(def-slot-value-reclaimer object-passing-info? (object-passing-info? system-item)
  (when object-passing-info?
    (reclaim-icp-object-map-for-registered-item system-item)
    (reclaim-icp-tree (parent-item-lists-or-arrays-1 object-passing-info?))
    (reclaim-object-passing-info object-passing-info?)
    (setf (object-passing-info? system-item) nil)))

(defun rpc-object-handed-off-to-user-p (rpc-object)
  (current-system-case
    (ab (g2-rpc-object-handed-off-to-user-p rpc-object))
    (gsi
     ;; ...
     )))
   



;;;; [9.1] Deactivator for Object-passing Capability

;;; The following four paragraphs are incomplete (jh, 2/28/94).

;;; The deactivator for object-passing capability must discontinue each RPC that
;;; is in the process of sending the object being deactivated, if this procedure
;;; has not yet begun executing on the remote side.  If the procedure has begun
;;; executing, it is allowed to continue.  It could be argued that we only want
;;; this behavior if the object being passed is deleted, not simply deactivated.
;;; If so, we can branch based on the value of the global variable
;;; within-delete-frame-scope?.

;;; The sending side needs to reclaim each sending-resumable-object in its
;;; resumable-object-structure-list slot, reclaim the list itself, and run the
;;; body of the ICP handler for rpc-error.

;;; The receiving side needs to reclaim each receiving-resumable-object
;;; structure that corresponds to the object being deactivated.  (The ICP
;;; message handler for delete-icp-object-for-process runs the reclaimer for
;;; receiving-resumable-object, which handles the fact that more than one
;;; receiving-resumable-object can share a receiving-rpc-arglist-structure in
;;; their enclosing-rpc-arglist-structure? slots.)

;;; There is currently (jh, 1/30/94) no need for a def-capability-activator for
;;; the object-passing capability.

;;; The macro `find-and-delete-from-queue-of-resumable-objects' is a
;;; not-fully-hygenic place-altering macro for use only by the the
;;; object-passing facility.  It takes three forms: a form to locate a given
;;; resumable-object structure within a queue (the "test-form"), the form
;;; representing the place where the head of the queue is stored, and the form
;;; representing the place where the tail of the queue is stored.  The queue is
;;; assumed to consist of icp-conses and the test-, head-, and tail-forms are
;;; assumed to be side-effect-free, as they are evaluated more than once.  The
;;; test-form is evaluated with the variable this-resumable-object bound to the
;;; resumable-object structure to be tested.  If this macro is unable to satisfy
;;; the test, it returns nil.

(defmacro find-and-delete-from-queue-of-resumable-objects
    (test-form-with-this-resumable-object-bound head-place tail-place)
  (avoiding-variable-capture (&aux head-contents? tail-contents)
    `(let ((,head-contents? ,head-place))
       (when ,head-contents?
	 (let ((,tail-contents ,tail-place))
	   (cond
	     ;; If the resumable object is at the head of the queue.
	     ((let ((this-resumable-object (car ,head-contents?)))
		,test-form-with-this-resumable-object-bound)
	      (dequeue ,head-place ,tail-place reclaim-icp-cons))
	     ;; If the resumable object is not at the head of the queue
	     (t (loop for previous-cons on ,head-place
		      for this-resumable-object-cons? = (cdr previous-cons)
		      while this-resumable-object-cons?
		      for this-resumable-object
			= (car this-resumable-object-cons?)
		      when ,test-form-with-this-resumable-object-bound
			do ;; Remove from the queue tail if necessary
			  (when (eq this-resumable-object-cons? ,tail-contents)
			    (setf ,tail-place previous-cons))
			  ;; Splice out of the list representing the queue.
			  (setf (cdr previous-cons) (cddr previous-cons))
			  ;; Reclaim the cons that held it in the queue.
			  (reclaim-icp-cons this-resumable-object-cons?)
			  (return this-resumable-object)))))))))
  
(defun g2-reclaim-sending-resumable-object
    (resumable-object &optional (known-unclogged-p nil))

  ;; Remove from the resumable-object structures waiting for the connection to
  ;; unclog.
  (unless known-unclogged-p
    (let ((icp-socket (resumable-object-icp-socket resumable-object)))
      (find-and-delete-from-queue-of-resumable-objects
	(eq resumable-object this-resumable-object)
	(resumable-objects-waiting-for-unclog icp-socket)
	(resumable-objects-waiting-for-unclog-tail icp-socket))))

  ;; Remove the object from the list of resumable-objects stored in the
  ;; identifier for this particular remote procedure invocation.
  (let ((rpc-identifier? (rpc-identifier-for-this-object? resumable-object)))
    (when rpc-identifier?
      (setf (remote-procedure-identifier-resumable-objects rpc-identifier?)
	    (delete-icp-element
	      resumable-object
	      (remote-procedure-identifier-resumable-objects
		rpc-identifier?)))))

  ;; Reclaim the actual resumable-object structure.
  (reclaim-sending-resumable-object-internal resumable-object))

;; jh, 2/6/94.  It was necessary to extract
;; reclaim-remote-side-for-deactivate-object-passing because def-class-method
;; creates a defun instead of a defun-allowing-unwind.  Some sunny day when we
;; are sure Chestnut has fixed the problem that made defun-allowing-unwind
;; necessary, we will again be able to inline
;; reclaim-remote-side-for-deactive-object-passing into the deactivate method
;; for object-passing.

(defun-allowing-unwind g2-reclaim-remote-side-for-deactivate-object-passing
    (resumable-object-structure icp-socket index-space-name)
  (let ((output-port (icp-output-port icp-socket)))
    (mapping-across-resumable-object-siblings
      (resumable-object-structure)
      (writing-icp-message-group (output-port)
	(send-icp-delete-icp-object-for-process
	  (get-icp-object-index-for-resumable-object
	    resumable-object-structure
	    output-port)
	  index-space-name)))))

(defun receive-object-passing-remote-procedure-error
    (resumable-object-structure name error-string)
  (let* ((rpc-arglist?
	   (enclosing-rpc-arglist-structure? resumable-object-structure))
	 (continuation-tag?
	   (and rpc-arglist?
		(continuation-waiting-for-rpc-arglist rpc-arglist?))))
    (case continuation-tag?
      (call
       (receive-remote-procedure-error-for-caller
	 (rpc-identifier-waiting-for-rpc-arglist rpc-arglist?)
	 nil
	 name
	 1
	 error-string))
      (return
	(remote-procedure-error
	  (resumable-object-icp-socket resumable-object-structure)
	  name error-string
	  (rpc-index-waiting-for-rpc-arglist rpc-arglist?)))
      (start
       (receive-remote-procedure-error
	 (resumable-object-icp-socket resumable-object-structure)
	 name
	 1
	 error-string
	 nil))
      (otherwise ;trying to preflight or transmit a handled RPC object
       (let* ((bad-object
		(object-or-handle-to-be-passed resumable-object-structure))
	      (error-string-with-prologue
	       (if (framep bad-object)
		   (tformat-text-string
		     "An error occurred while attempting to register ~NF ~
                      on the network: ~A"
		     bad-object
		     error-string)
		   (tformat-text-string
		     "An error occurred while attempting to register ~
                      an argument on the network: ~A"
		     error-string))))
	 (receive-remote-procedure-error
	   (resumable-object-icp-socket resumable-object-structure)
	   name
	   1
	   error-string-with-prologue
	   nil)
	 (reclaim-text-string error-string-with-prologue))))))




;;;; [10] G2 Sending Side Task to Preflight Resumable Objects

(defun-void g2-attach-resumable-child-node-to-parent (child-node parent-node)
  (let ((new-tail (icp-list child-node))
	(last-cons? (last-cons-in-inferior-attributes? parent-node)))
    (if last-cons?
	(setf (cdr (last-cons-in-inferior-attributes? parent-node))
	      new-tail)
	(setf (inferior-attributes parent-node) new-tail))
    (setf (last-cons-in-inferior-attributes? parent-node)
	  new-tail)))

(defun-void g2-set-resumable-node-homogeneous-element-type
    (attribute-node attribute)
  (setf (homogeneous-element-type? attribute-node)
	(frame-class-case attribute
	  (integer-array         'integer)
	  (float-array           '|float|)
	  (text-array            'text)
	  (truth-value-array     'truth)
	  (symbol-array          'symbol)
	  (integer-list          'integer)
	  (float-list            '|float|)
	  (text-list             'text)
	  (truth-value-list      'truth)
	  (symbol-list           'symbol)
	  (integer-parameter     'integer)
	  (integer-variable      'integer)
	  (float-parameter       '|float|)
	  (float-variable        '|float|)
	  (text-parameter        'text)
	  (text-variable         'text)
	  (logical-parameter     'truth)
	  (logical-variable      'truth)
	  (symbolic-parameter    'symbol)
	  (symbolic-variable     'symbol)
	  (t nil))))

#-SymScale
(defmacro get-internal-list-for-object-passing (g2-list)
  (avoiding-variable-capture (g2-list)
    `(progn
       (unless (list-structure ,g2-list)
	 (setf (list-structure ,g2-list) (create-empty-g2-list-structure)))
       (list-next-element (list-structure ,g2-list)))))

#+SymScale
(defmacro get-internal-list-for-object-passing (g2-list)
  (let ((old-list (make-symbol "OLD-LIST"))
	(new-list (make-symbol "NEW-LIST")))
    (avoiding-variable-capture (g2-list old-list new-list)
      `(let ((,old-list (list-structure ,g2-list)))
	 (unless ,old-list
	   (let ((,new-list (create-empty-g2-list-structure)))
	     (unless (compare-and-swap (list-structure ,g2-list)
				       ,old-list ,new-list)
	       ;; means other threads did the same thing first.
	       (reclaim-empty-g2-list-structure ,new-list))))
	 #-Lockfree-Deque
	 (g2-list-structure-head (list-structure ,g2-list))
	 #+Lockfree-Deque
	 (list-next-element-real
	   (g2-list-structure-head (list-structure ,g2-list)))))))

(defmacro get-internal-array-for-object-passing (g2-array)
  (avoiding-variable-capture (g2-array)
    `(progn
       (unless (managed-g2-array ,g2-array)
	 (initialize-g2-array ,g2-array))
       (managed-g2-array ,g2-array))))

(defun-simple count-of-symbolic-attributes (attribute-specs)
  (loop for attribute-spec in attribute-specs
	count (and (eq (resumable-attribute-type attribute-spec) 'attribute)
		   (not (memq (resumable-attribute-base-name attribute-spec)
			      '(name value))))))


(defmacro def-catch-handling-function
    (defun-name innermost-args catcher-specs &body innermost-forms)
  (let ((value-var (gensym))
	(block-name (intern 
	  #-ansi-cl (lisp:format nil "~A-BODY" defun-name)
	  #+ansi-cl
	  (common-lisp:format nil "~A-BODY" defun-name))))
    `(defun ,defun-name ,innermost-args
       (let* ((rpc-throw-tag nil)
	      (,value-var
		 (block ,block-name
		   (with-throw-handling ,block-name
		     ,@innermost-forms))))
	 (case rpc-throw-tag
	   ,@(mapcar #'(lambda (catcher-spec)
			 `(,(car catcher-spec)
			    (let (,@(when (cadr catcher-spec)
				      `((,(caadr catcher-spec) ,value-var))))
			      ,@(cddr catcher-spec))))
		     catcher-specs)
	   (t ,value-var))))))

(defmacro with-throw-handling (name &body forms)
  `(macrolet ((handle-throw (form)
		`(let ((possible-throw-value ,form))
		   (when rpc-throw-tag
		     (return-from ,',name possible-throw-value))
		   possible-throw-value))
	      (throw* (tag value)
		`(progn
		   (setq rpc-throw-tag ,tag)
		   (return-from ,',name ,value))))
     ,@forms))


(defun-simple get-resumable-child-node
    (attribute-name
      child-object-or-value
      current-node
      resumable-object
      last-attribute-p)
  (with-throw-handling get-resumable-child-node
    (let ((icp-object-index?
	    (and (framep child-object-or-value)
		 (get-index-of-circular-resumable-node
		   child-object-or-value
		   resumable-object))))
      (cond
	(icp-object-index?
	 (make-resumable-circular-node
	   attribute-name
	   icp-object-index?
	   current-node))
	#+no
	((evaluation-sequence-p child-object-or-value)
	 (let ((child-node
		 (make-resumable-evaluation-sequence-node
		   child-object-or-value
		   (evaluation-sequence-length child-object-or-value)
		   current-node))
	       (grandparent nil))
	   (cond
	     (last-attribute-p
	      (setf (current-superiors child-node)
		    (icp-cons grandparent (current-superiors child-node)))
	      (setf (current-trailing-edge-object-p child-node)
		    (current-trailing-edge-object-p current-node)))
	     (t (setf (current-superiors child-node)
		      (icp-cons nil (current-superiors child-node)))
		(setf (current-trailing-edge-object-p child-node) nil)))
	   child-node))
	#+no
	((evaluation-structure-p child-object-or-value)
	 (let ((child-node
		 (make-resumable-evaluation-structure-node
		   child-object-or-value
		   (evaluation-sequence-length child-object-or-value)
		   current-node))
	       (grandparent nil))
	   (cond
	     (last-attribute-p
	      (setf (current-superiors child-node)
		    (icp-cons grandparent (current-superiors child-node)))
	      (setf (current-trailing-edge-object-p child-node)
		    (current-trailing-edge-object-p current-node)))
	     (t (setf (current-superiors child-node)
		      (icp-cons nil (current-superiors child-node)))
		(setf (current-trailing-edge-object-p child-node) nil)))
	   child-node))
	((framep child-object-or-value)
	 (let* ((serial-number (frame-serial-number child-object-or-value))
		(includes
		  (resumable-object-included-slots resumable-object))
		(excludes
		  (resumable-object-excluded-slots resumable-object))
		(system-includes
		  (resumable-object-included-system-slots resumable-object))
		(inferior-attribute-names?
		  (get-attribute-names-for-object-passing
		    child-object-or-value
		    includes
		    excludes
		    system-includes))
		(class-of-attribute (class child-object-or-value))
		(grandparent (resumable-node-parent-node? current-node))
		child-node)
	   (frame-class-case child-object-or-value
	     (value-array
	       (setq child-node
		     (make-resumable-value-vector-node
		       child-object-or-value
		       (copy-frame-serial-number serial-number)
		       inferior-attribute-names?
		       (count-of-symbolic-attributes inferior-attribute-names?)
		       attribute-name
		       class-of-attribute
		       (g2-array-length child-object-or-value)
		       (get-internal-array-for-object-passing
			 child-object-or-value)
		       current-node))
	       (g2-set-resumable-node-homogeneous-element-type
		 child-node
		 child-object-or-value))
	     ((item-array g2-array) ;must come after value-array case!
	      (let ((internal-attribute-vector
		      (get-internal-array-for-object-passing
			child-object-or-value)))
		(setq child-node
		      (make-resumable-object-vector-node
			child-object-or-value
			(copy-frame-serial-number serial-number)
			inferior-attribute-names?
			(count-of-symbolic-attributes inferior-attribute-names?)
			attribute-name
			class-of-attribute
			(g2-array-length child-object-or-value)
			internal-attribute-vector
			current-node))))
	     (variable-or-parameter
	       (let ((history-spec?
		       (variable-or-parameter-history-specification?
			 child-object-or-value)))
		 (cond
		   ((and history-spec? (memq 'history system-includes))
		    (setq child-node
			  (make-resumable-history-node
			    child-object-or-value
			    (copy-frame-serial-number serial-number)
			    inferior-attribute-names?
			    (count-of-symbolic-attributes
			      inferior-attribute-names?)
			    attribute-name
			    class-of-attribute
			    0
			    current-node))
		    (let ((history-enclosure?
			    (variable-or-parameter-stored-histories?
			      child-object-or-value))
			  (history?
			    (get-history-ring-buffer-if-any
			      child-object-or-value
			      nil)))
		      (when history?
			(copy-history-state-into-resumable-history-node
			  child-node
			  history-enclosure?
			  history?
			  history-spec?))
		      (g2-set-resumable-node-homogeneous-element-type
			child-node
			child-object-or-value)))
		   (t (setq child-node
			    (make-resumable-object-node
			      child-object-or-value
			      (copy-frame-serial-number serial-number)
			      inferior-attribute-names?
			      (count-of-symbolic-attributes
				inferior-attribute-names?)
			      attribute-name
			      class-of-attribute
			      current-node))))))
	     (value-list
	       (setq child-node
		     (make-resumable-value-list-node
		       child-object-or-value
		       (copy-frame-serial-number serial-number)
		       inferior-attribute-names?
		       (count-of-symbolic-attributes inferior-attribute-names?)
		       attribute-name
		       class-of-attribute
		       (get-internal-list-for-object-passing
			 child-object-or-value)
		       (g2-list-length child-object-or-value)
		       current-node))
	       (g2-set-resumable-node-homogeneous-element-type
		 child-node
		 child-object-or-value))
	     ((item-list g2-list) ;must follow value-list case!
	      (setq child-node
		    (make-resumable-object-list-node
		      child-object-or-value
		      (copy-frame-serial-number serial-number)
		      inferior-attribute-names?
		      (count-of-symbolic-attributes inferior-attribute-names?)
		      attribute-name
		      class-of-attribute
		      (get-internal-list-for-object-passing
			child-object-or-value)
		      (g2-list-length child-object-or-value)
		      current-node)))
	     ;; The following clause must go after more specific object
	     ;; subclasses!
	     (object
	       (setq child-node
		     (make-resumable-object-node
		       child-object-or-value
		       (copy-frame-serial-number serial-number)
		       inferior-attribute-names?
		       (count-of-symbolic-attributes inferior-attribute-names?)
		       attribute-name
		       class-of-attribute
		       current-node)))
	     ;; the following clause must go last!
	     (item
	       (with-bifurcated-version (rel4-rpc-protocol-supports-non-objects-icp-version)
		 (throw*
		   :abort-preflighting-resumable-object
		   (icp-list
		     'sending-a-non-object-by-copy-to-a-pre-release-5-g2-or-gsi
		     (tformat-text-string "~NF is not an object" child-object-or-value)))
		 (let ((exported-attribute-names
			 (get-exported-attribute-names-for-object-passing
			   child-object-or-value
			   includes
			   excludes
			   system-includes)))
		   (setq child-node
			 (make-resumable-object-node
			   child-object-or-value
			   (copy-frame-serial-number serial-number)
			   exported-attribute-names
			   (length exported-attribute-names)
			   attribute-name
			   class-of-attribute
			   current-node))))))
	   (cond
	     (last-attribute-p
	      (setf (current-superiors child-node)
		    (icp-cons grandparent (current-superiors child-node)))
	      (setf (current-trailing-edge-object-p child-node)
		    (current-trailing-edge-object-p current-node)))
	     (t
	      (setf (current-superiors child-node)
		    (icp-cons nil (current-superiors child-node)))
	      (setf (current-trailing-edge-object-p child-node) nil)))
	   child-node))
	(t (make-resumable-value-node
	   attribute-name
	   child-object-or-value
	   current-node))))))  


;;; The function `set-resumable-instance-ascension' arranges for a node to
;;; ascend to the proper ancestor after that node's inferior attributes have all
;;; been traversed.  During the execution of this function, the
;;; current-superiors and current-object-vector-index slots of all intervening
;;; ancestors are set to appropriate values for use by
;;; transmit-resumable-object.

(defun set-resumable-instance-ascension (ascending-node)
  (with-throw-handling set-resumable-instance-ascension
    (let* ((final-attribute?
	     (car (last-cons-in-inferior-attributes? ascending-node)))
	   (final-trailing-edge-object-p
	     (and (current-trailing-edge-object-p ascending-node)
		  (not (resumable-instance-or-complex-value-node-p final-attribute?))))
	   (parent? (resumable-node-parent-node? ascending-node))
	   (superiors? (current-superiors ascending-node)))

      ;; Following cond form deal with grandparents and above, so prepare parent
      ;; and node itself here unconditionally.
      (setf (current-cons-in-inferior-attributes? ascending-node)
	    (inferior-attributes ascending-node))
      (when parent?
	(setf (current-cons-in-inferior-attributes? parent?)
	      (inferior-attributes parent?)))
      (setf (current-superiors ascending-node) nil)
      ;; Only set current-object-vector-index of node itself, since we might be
      ;; ascending to another resumable-object-vector-node that has some more
      ;; elements to go.
      (when (resumable-object-vector-node-p ascending-node)
	(setf (current-object-vector-index ascending-node) 0))
      
      ;; Prepare grandparents and above for transmit-resumable-object, set
      ;; ascension count and target.
      (cond
	(final-trailing-edge-object-p
	 ;; don't need superiors - we're going all the way up in this case
	 (reclaim-icp-list superiors?)
	 (when parent?
	   (loop for superior? = (resumable-node-parent-node? parent?)
			       then (resumable-node-parent-node? superior?)
		 while superior?
		 do
	     (when (resumable-object-vector-node-p superior?)
	       (setf (current-object-vector-index superior?) 0))
	     (setf (current-cons-in-inferior-attributes? superior?)
		   (inferior-attributes superior?))
	     (setf (current-superiors superior?) nil)))
	 (throw* :finished-preflighting-resumable-object t))
	(t (loop for superior? in superiors?
		 for superior-cons? on superiors?
		 with highest-superior? = nil
		 with highest-superior-cons? = nil
		 ;; An ascension-count of 1 represents the parent, to which we
		 ;; ascend when highest-superior? is still nil upon exit from this
		 ;; loop.  So we start with 2 here.
		 for ascension-count from 2 
		 while superior?
		 do
	     (setq highest-superior? superior?)
	     (setq highest-superior-cons? superior-cons?)
	     (setf (current-cons-in-inferior-attributes? superior?)
		   (inferior-attributes superior?))
	     (when (and (cadr superior-cons?)
			(resumable-object-vector-node-p superior?))
	       (setf (current-object-vector-index superior?) 0))
		 finally
		   (cond
		     (highest-superior?
		      (setf (ascension-target? ascending-node) highest-superior?)
		      (setf (resumable-node-ascension-count? ascending-node)
			    ascension-count)
		      (setf (cdr highest-superior-cons?) nil)
		      (when (and parent?
				 (resumable-object-vector-node-p parent?))
			(setf (current-object-vector-index parent?) 0))
		      (reclaim-icp-list-given-tail
			superiors?
			highest-superior-cons?))
		     (t (setf (ascension-target? ascending-node) parent?)
			(setf (resumable-node-ascension-count? ascending-node)
			      1)
			(when superiors?
			  (reclaim-icp-cons superiors?))))))))))

(defmacro object-array-passing-aref (internal-array index)
  (avoiding-variable-capture (&aux contents)
    `(let ((,contents (managed-g2-array-aref ,internal-array (*f ,index 2))))
       (if (evaluation-value-p ,contents)
	   (copy-evaluation-value ,contents)
	   ,contents))))

(defmacro object-array-passing-aset (internal-array index element)
  (avoiding-variable-capture (internal-array element)
    `(let ((index-of-element (*f ,index 2)))
       (setf (managed-g2-array-aref ,internal-array index-of-element) ,element)
       (setf (managed-g2-array-aref ,internal-array (1+f index-of-element))
	     (copy-frame-serial-number (frame-serial-number ,element))))))

(defsetf object-array-passing-aref object-array-passing-aset)

;; jh, 11/14/95.  See note under the :object-list clause in
;; preflight-resumable-object for an explanation of the list-object argument to
;; internal-list-elements-remain-p, as well as the provenance of
;; valid-internal-list-element-p.

(defmacro internal-list-elements-remain-p (internal-list list-object)
  `(eq (list-frame ,internal-list) ,list-object))

(defmacro valid-internal-list-element-p (possible-list-element)
  (avoiding-variable-capture (possible-list-element)
    `(and (simple-vector-p ,possible-list-element)
	  (=f (length (the simple-vector ,possible-list-element)) 4))))

(defmacro list-element-value-for-object-passing (internal-list)
  (avoiding-variable-capture (&aux contents)
    `(let ((,contents (list-element-value ,internal-list)))
       (if (evaluation-value-p ,contents)
	   (copy-evaluation-value ,contents)
	   ,contents))))
  

(defun preflight-resumable-object (resumable-object current-node)
  (with-throw-handling preflight-resumable-object
    (prog ((current-object
	     (resumable-instance-current-object current-node))
	   attribute-name last-attribute-p child)
     check-timeslice
     (when (time-slice-expired-p)
       (throw* :suspend-preflighting-resumable-object current-node))
     (resumable-node-typecase current-node
       ((:object :value-vector :value-list :history)
	(let ((remaining-attribute-names?
		(current-attribute-names current-node)))
	  (cond
	    (remaining-attribute-names?
	     (setq attribute-name (car remaining-attribute-names?)
		   last-attribute-p (null (cdr remaining-attribute-names?))
		   child (g2-get-attribute-for-object-passing
			   current-object
			   attribute-name))
	     (icp-pop (current-attribute-names current-node))
	     (go attach-child-node))
	    (t (go ascend-from-current-node)))))
       #+no
       (:sequence
	 (let ((highest-index
		 (highest-object-vector-index current-node))
	       (current-index
		 (current-object-vector-index current-node))
	       remaining-attribute-names?)
	   (cond
	     ((and (>f current-index highest-index)
		   (null remaining-attribute-names?))
	      (go ascend-from-current-node))
	     ((>f current-index highest-index)
	      (setq attribute-name (car remaining-attribute-names?)
		    last-attribute-p (null (cdr remaining-attribute-names?))
		    child (g2-get-attribute-for-object-passing
			    current-object
			    attribute-name))
	      (icp-pop (current-attribute-names current-node))
	      (go attach-child-node))
	     (t (setq attribute-name (make-resumable-vector-index
				       current-index)
		      last-attribute-p (if remaining-attribute-names?
					   nil
					   (=f current-index highest-index))
		      child (object-array-passing-aref
			      (internal-vector-for-object-passing current-node)
			      current-index))
		(incff (current-object-vector-index current-node))
		(go attach-child-node)))))
       #+no
       (:structure
	 (let ((highest-index
		 (highest-object-vector-index current-node))
	       (current-index
		 (current-object-vector-index current-node))
	       remaining-attribute-names?)
	   (cond
	     ((and (>f current-index highest-index)
		   (null remaining-attribute-names?))
	      (go ascend-from-current-node))
	     ((>f current-index highest-index)
	      (setq attribute-name (car remaining-attribute-names?)
		    last-attribute-p (null (cdr remaining-attribute-names?))
		    child (g2-get-attribute-for-object-passing
			    current-object
			    attribute-name))
	      (icp-pop (current-attribute-names current-node))
	      (go attach-child-node))
	     (t (setq attribute-name (make-resumable-vector-index
				       current-index)
		      last-attribute-p (if remaining-attribute-names?
					   nil
					   (=f current-index highest-index))
		      child (object-array-passing-aref
			      (internal-vector-for-object-passing current-node)
			      current-index))
		(incff (current-object-vector-index current-node))
		(go attach-child-node)))))
       (:object-vector
	 (let ((highest-index
		 (highest-object-vector-index current-node))
	       (current-index
		 (current-object-vector-index current-node))
	       (remaining-attribute-names?
		 (current-attribute-names current-node)))
	   (cond
	     ((and (>f current-index highest-index)
		   (null remaining-attribute-names?))
	      (go ascend-from-current-node))
	     ((>f current-index highest-index)
	      (setq attribute-name (car remaining-attribute-names?)
		    last-attribute-p (null (cdr remaining-attribute-names?))
		    child (g2-get-attribute-for-object-passing
			    current-object
			    attribute-name))
	      (icp-pop (current-attribute-names current-node))
	      (go attach-child-node))
	     (t (setq attribute-name (make-resumable-vector-index
				       current-index)
		      last-attribute-p (if remaining-attribute-names?
					   nil
					   (=f current-index highest-index))
		      child (object-array-passing-aref
			      (internal-vector-for-object-passing current-node)
			      current-index))
		(incff (current-object-vector-index current-node))
		(go attach-child-node)))))
       (:object-list
	 (let* ((internal-list (internal-list-for-object-passing current-node))
		(list-elements-remain-p
		  (internal-list-elements-remain-p
		    internal-list
		    current-object))
		(remaining-attribute-names?
		  (current-attribute-names current-node)))
	   (cond
	     ((and (not list-elements-remain-p)
		   (null remaining-attribute-names?))
	      (go ascend-from-current-node))
	     ((not list-elements-remain-p)
	      (setq attribute-name (car remaining-attribute-names?)
		    last-attribute-p (null (cdr remaining-attribute-names?))
		    child (g2-get-attribute-for-object-passing
			    current-object
			    attribute-name))
	      (icp-pop (current-attribute-names current-node))
	      (go attach-child-node))
	     (t (let ((list-index (resumable-sequence-length current-node))
		      (next-element? (list-next-element-real internal-list)))
		  ;; jh, 11/14/95.  The following form checks that we have a
		  ;; plausible list-element structure.  We could fail to have such
		  ;; a structure if we are removing elements from the list as we
		  ;; are sending it (as in bug HQ-531260).  A related but more
		  ;; serious corruption would be the reuse of a list element by a
		  ;; different frame.  The second argument to
		  ;; internal-list-elements-remain-p allows us to check for this
		  ;; contingency.
		  (unless (valid-internal-list-element-p next-element?)		    
		    (go ascend-from-current-node))
		  (setq attribute-name (make-resumable-list-index list-index)
			last-attribute-p (if remaining-attribute-names?
					     nil
					     (not
					       (internal-list-elements-remain-p
						 next-element?
						 current-object)))
			child (list-element-value-for-object-passing
				internal-list))
		  (setf (internal-list-for-object-passing current-node)
			next-element?)
		  (incff (resumable-sequence-length current-node))
		  (go attach-child-node)))))))
     attach-child-node
     (let ((child-node
	     (handle-throw
	       (get-resumable-child-node
		 attribute-name
		 child
		 current-node
		 resumable-object
		 last-attribute-p))))
       (g2-attach-resumable-child-node-to-parent child-node current-node)
       (when (framep child)
	 (unless (resumable-circular-node-p child-node)
	   (set-index-of-circular-resumable-node
	     child
	     resumable-object
	     child-node)))
       ;; current-node is never a leaf (i.e., a value or circularity reference)
       (when (resumable-instance-or-complex-value-node-p child-node)
	 (setq current-object child)
	 (setq current-node child-node))
     (go check-timeslice))
   ascend-from-current-node
   (handle-throw
     (set-resumable-instance-ascension current-node))
   (setq current-node (ascension-target? current-node))
   (setq current-object
	 (resumable-instance-current-object current-node))
   (go check-timeslice))))

(def-catch-handling-function preflight-resumable-object-with-catch-handlers
    (resumable-object)    
  ((:abort-preflighting-resumable-object (abort-info)
   (let* ((rpc-name? (resumable-object-rpc-name? resumable-object))
	  (error-message (second abort-info))
	  (error-string
	    (if rpc-name?
		(tformat-text-string
		  "The remote procedure call ~NF has been aborted ~
                   while sending: ~A"
		  rpc-name?
		  error-message)
		(tformat-text-string
		  "A remote procedure call has been aborted while sending: ~A"
		  error-message))))
     (receive-object-passing-remote-procedure-error
       resumable-object
       (first abort-info)
       error-string)
     (loop for info in abort-info
	   when (text-string-p info)
	     do (reclaim-text-string info)
	   finally (reclaim-icp-list abort-info))
     (reclaim-text-string error-string)
     (reclaim-sending-and-receiving-resumable-object
       resumable-object)))
   (:finished-preflighting-resumable-object ()
    (setf (current-resumable-node resumable-object)
	  (toplevel-resumable-node resumable-object))
    (cond
      ((time-slice-expired-p)
       (debug-object-passing "(1) scheduling ~s" resumable-object)
       (with-current-scheduling
	   ((resumable-object-task resumable-object)
	    (resumable-object-priority resumable-object)
	    nil
	    nil
	    t)
	 (try-to-transmit-resumable-object resumable-object)))
      (t (try-to-transmit-resumable-object resumable-object))))
   (:suspend-preflighting-resumable-object (new-resumable-node)
    (setf (current-resumable-node resumable-object)
	  new-resumable-node)
    (debug-object-passing "(2) scheduling ~s" resumable-object)
    (with-current-scheduling
	((resumable-object-task resumable-object)
	 (resumable-object-priority resumable-object)
	 nil
	 nil
	 t)
      (try-to-preflight-resumable-object resumable-object))))
  (handle-throw
    (preflight-resumable-object
      resumable-object
      (current-resumable-node resumable-object))))

(defun-allowing-unwind try-to-preflight-resumable-object (resumable-object)
  (debug-object-passing
    "try-to-preflight-resumable-object ~s"
    resumable-object)
  (let ((object (object-or-handle-to-be-passed resumable-object)))
    (if (not (or (consp object)
		 (frame-has-not-been-reprocessed-p
		    object
		    (resumable-object-reference-serial-number resumable-object))))
	(g2-reclaim-sending-resumable-object resumable-object)
	(let ((current-icp-socket
		(resumable-object-icp-socket resumable-object)))
	  (preflight-resumable-object-with-catch-handlers resumable-object)))))






;;;; [11] ICP Writer and Reader for RPC Object Argument

(def-system-variable rpc-object-arguments-to-run-or-schedule? G2-RPC2 nil)

(defun-void send-deferred-rpc-objects-if-any ()
  (when rpc-object-arguments-to-run-or-schedule?
    (loop for rpc-object in rpc-object-arguments-to-run-or-schedule?
	  do (try-to-preflight-resumable-object rpc-object)
	  finally (reclaim-icp-list rpc-object-arguments-to-run-or-schedule?)
		  (setq rpc-object-arguments-to-run-or-schedule? nil))))

(defmacro invoking-remote-procedure-with-deferred-objects
    ((icp-output-port) (invoker &rest args))
  `(progn
     (writing-icp-message-group (,icp-output-port)
       (,invoker ,@args)) ;side-effects rpc-object-arguments-to-run-or-schedule?.
     (send-deferred-rpc-objects-if-any)))

(defun-void send-icp-rpc-start-deferring-objects
    (icp-output-port remote-procedure-name rpc-argument-list)
  (invoking-remote-procedure-with-deferred-objects (icp-output-port)
    (send-icp-rpc-start remote-procedure-name rpc-argument-list)))

(defun-void send-icp-rpc-call-deferring-objects
    (icp-output-port
      remote-procedure-name
      remote-procedure-identifier
      rpc-argument-list)
  (invoking-remote-procedure-with-deferred-objects (icp-output-port)
    (send-icp-rpc-call
      remote-procedure-name
      remote-procedure-identifier
      rpc-argument-list)))

(defun-void send-icp-rpc-return-values-deferring-objects
    (icp-output-port calling-procedure-index return-values-list)
  (invoking-remote-procedure-with-deferred-objects (icp-output-port)
    (send-icp-rpc-return-values calling-procedure-index return-values-list)))

(defun-void g2-write-icp-rpc-value-or-object (rpc-value-or-object)
  (cond
    ((evaluation-value-p rpc-value-or-object)
     (write-icp-remote-value rpc-value-or-object))
    ((not (sending-resumable-object-p rpc-value-or-object))
     #+development
     (cerror "Resume, sending unknown RPC type ~
                (This behavior is what the user would get)"
	     "WRITE-ICP-RPC-VALUE-OR-OBJECT: unexpected thing ~a"
	     rpc-value-or-object)
     (write-icp-byte rpc-unknown-type-tag))
    ((transmit-resumable-object-as-handle-p rpc-value-or-object)
     (let ((kind (transmit-resumable-object-as-handle-p rpc-value-or-object)))
       (if (eq 'reference kind)
	   (write-icp-remote-value (object-or-handle-to-be-passed rpc-value-or-object))
	   (progn
	     (write-icp-byte rpc-object-handle-type-tag)
	     (write-icp-fixnum (object-or-handle-to-be-passed rpc-value-or-object))))
       (g2-reclaim-sending-resumable-object rpc-value-or-object)))
    (t
     (write-icp-byte rpc-object-type-tag)
     (write-icp-unsigned-integer
       (resumable-object-icp-index rpc-value-or-object))
     (debug-object-passing "(3) scheduling ~s" rpc-value-or-object)
     (icp-push rpc-value-or-object rpc-object-arguments-to-run-or-schedule?))))


;;;; [13] Clog Management

;;; All bandwidth computation for resumable objects is in 8-bit bytes as opposed
;;; to 16-bit ICP bytes.

(defun-void g2-resume-clogged-resumable-object-tasks ()
  (let* ((icp-socket current-icp-socket)
	 (first-resumable-object?
	   (car (resumable-objects-waiting-for-unclog icp-socket)))
	 (waiting-object?
	   (and first-resumable-object?
		(<= (resumable-object-bandwidth-denied-by-clog?
		      first-resumable-object?)
		    (available-bandwidth-for-object-passing icp-socket))
		(dequeue
		  (resumable-objects-waiting-for-unclog icp-socket)
		  (resumable-objects-waiting-for-unclog-tail icp-socket)
		  reclaim-icp-cons))))
    (when waiting-object?
      (debug-object-passing "(4) scheduling ~s" waiting-object?)
      (setf (resumable-object-bandwidth-denied-by-clog? waiting-object?) nil)
      (with-current-scheduling
	  ((resumable-object-task waiting-object?)
	   (resumable-object-priority waiting-object?)
	   nil
	   nil
	   t)
	(try-to-transmit-resumable-object waiting-object?)))))

(defvar default-most-recent-bandwidth-per-timeslice 8192)

(defvar minimum-bandwidth-per-timeslice 4096)

;; jh, 2/8/94.  Make most-recent-bandwidth-per-timeslice? more adaptive someday.

(def-system-variable most-recent-bandwidth-per-timeslice? RPC-COMMON2 nil)

(def-substitution-macro allocate-bandwidth-for-resumable-node
    (needed current-resumable-node resumable-object)
  (incff (resumable-object-allocated-bandwidth resumable-object) needed)
  (decff (available-bandwidth-for-object-passing
	   (resumable-object-icp-socket resumable-object))
	 needed))

(def-substitution-macro resumable-object-bandwidth-unavailable-p
    (needed icp-socket)
  (<f (-f (available-bandwidth-for-object-passing icp-socket) needed)
      0))

(def-substitution-macro bandwidth-for-icp-fixnum (fixnum)
  (if (>f fixnum (maximum-icp-byte-unsigned-integer))
      4
      2))

(def-substitution-macro bandwidth-for-icp-float ()
  8)

(def-substitution-macro bandwidth-for-icp-boolean () 2)

(def-substitution-macro bandwidth-for-history-float-array-flags ()
  (*f (bandwidth-for-icp-boolean) 2))

(def-substitution-macro bandwidth-for-history-spec (resumable-node)
  (let* ((history-spec
	   (internal-history-spec-for-object-passing resumable-node))
	 (datapoint-count? (second history-spec))
	 (datapoint-age? (third history-spec)))
    (+f (if datapoint-count?
	    (bandwidth-for-icp-fixnum datapoint-count?)
	    (bandwidth-for-resumable-node-type-tag))
	(if datapoint-age?
	    (bandwidth-for-icp-fixnum datapoint-age?)
	    (bandwidth-for-resumable-node-type-tag)))))

(def-substitution-macro bandwidth-for-resumable-node-type-tag ()
  2)

;;; The substitution macro `bandwidth-for-icp-symbol' returns two values: the
;;; number of octet bytes (not ICP bytes) necessary to transmit the symbol
;;; across the given ICP port, and the corresponding ICP object index of the
;;; symbol relative to that port, or nil if there is no such index.

(def-substitution-macro bandwidth-for-icp-symbol (symbol icp-port)
  (let ((index? (get-icp-object-index-for-symbol symbol icp-port)))
    (if index?
	(values (bandwidth-for-icp-fixnum index?)
		index?)
	(let* ((symbol-name (symbol-name-text-string symbol))
	       (length (twicef		; 2 bytes per ICP byte
			 (text-string-length symbol-name))))
	  (values (+f (bandwidth-for-icp-fixnum length)
		      length)
		  nil)))))

(def-substitution-macro bandwidth-for-evaluation-no-value ()
  2)

;;; The function `bandwidth-for-resumable-attribute-spec' returns two values:
;;; the number of octet bytes (not ICP bytes) necessary to transmit an attribute
;;; across the given ICP port, and the corresponding ICP object index of the
;;; symbol naming that attribute relative to that port, or nil if the attribute
;;; is not named by a symbol (i.e. list or vector elements) or if there is no
;;; such index.

(defun bandwidth-for-resumable-attribute-spec (attribute-spec? icp-port)
      (if attribute-spec?
	  (case (resumable-attribute-type attribute-spec?)
	    (attribute
	     (multiple-value-bind (bandwidth-of-base-name index-of-base-name?)
		 (bandwidth-for-icp-symbol
		   (resumable-attribute-base-name attribute-spec?)
		   icp-port)
	       (let ((qualifier?
		       (resumable-attribute-class-qualifier? attribute-spec?)))
		 (if qualifier?
		     (multiple-value-bind
			 (bandwidth-of-qualifier index-of-qualifier?)
			 (bandwidth-for-icp-symbol
			   qualifier?
			   icp-port)
		       (values
			 (+f (bandwidth-for-resumable-node-type-tag)
			     bandwidth-of-base-name
			     bandwidth-of-qualifier)
			 index-of-qualifier?
			 index-of-base-name?))
		     (values
		       (+f (bandwidth-for-resumable-node-type-tag)
			   bandwidth-of-base-name)
		       nil
		       index-of-base-name?)))))
	    ((vector-element list-element)
	     (values
	       (+f (bandwidth-for-resumable-node-type-tag)
		   (bandwidth-for-icp-fixnum
		     (resumable-vector-or-list-index attribute-spec?)))
	       nil
	       nil)))
	  (values (bandwidth-for-resumable-node-type-tag) nil nil)))

(def-substitution-macro bandwidth-for-resumable-node-index
    (resumable-node)
  (bandwidth-for-icp-fixnum
    (resumable-circular-corresponding-icp-index resumable-node)))

(def-substitution-macro bandwidth-for-icp-text-string (text-string)
  (let ((length (length text-string)))
    (+f (bandwidth-for-icp-fixnum length)
	length)))

(def-substitution-macro bandwidth-for-icp-truth-value (truth-value)
  (bandwidth-for-icp-fixnum truth-value))

;;; The function `bandwidth-for-evaluation-value' returns two values: the number
;;; of octet bytes (not ICP bytes) necessary to transmit the given evaluation
;;; value across the given ICP port, and the corresponding ICP object index of
;;; that value relative to that port, or nil if the value is not a symbol or if
;;; there is no such index.

(def-substitution-macro bandwidth-for-evaluation-value
    (evaluation-value? icp-port)
  (multiple-value-bind (bandwidth corresponding-index?)
      (evaluation-typecase evaluation-value?
	(evaluation-integer
	  (bandwidth-for-icp-fixnum evaluation-integer))
	(evaluation-float
	  (bandwidth-for-icp-float))
	(evaluation-text
	  (bandwidth-for-icp-text-string evaluation-text))
	(evaluation-truth-value
	  (bandwidth-for-icp-truth-value evaluation-truth-value))
	(evaluation-symbol
	  (bandwidth-for-icp-symbol evaluation-symbol icp-port))
	(evaluation-sequence evaluation-sequence (values 0 nil))
	(evaluation-structure evaluation-structure (values 0 nil))
	(evaluation-no-value
	  (bandwidth-for-evaluation-no-value)))
    (values (+f bandwidth (bandwidth-for-resumable-node-type-tag))
	    corresponding-index?)))

(defun bandwidth-for-resumable-node-class-name
    (resumable-node icp-port)
  (bandwidth-for-icp-symbol
    (resumable-instance-class-name resumable-node)
    icp-port))

(def-substitution-macro bandwidth-for-ascension-count (resumable-node)
  (let ((ascension-count? (resumable-node-ascension-count? resumable-node)))
    (if ascension-count?
	(bandwidth-for-icp-fixnum ascension-count?)
	0)))

(def-substitution-macro bandwidth-for-symbolic-attribute-count (resumable-node)
  (bandwidth-for-icp-fixnum (symbolic-attribute-count resumable-node)))

(def-substitution-macro bandwidth-for-sequence-element-description
    (resumable-node)
  (+f (resumable-node-typecase resumable-node ;element-type tag
	((:value-vector :value-list) 2)
	(otherwise 0))
      (resumable-node-typecase resumable-node ;sequence length
	((:object-vector :value-vector :object-list :value-list :history :sequence :structure)
	 (bandwidth-for-icp-fixnum (resumable-sequence-length resumable-node)))
	(otherwise 0))
      (resumable-node-typecase resumable-node
	(:history (+f (bandwidth-for-history-spec resumable-node)
		      (bandwidth-for-history-float-array-flags)))
	(otherwise 0))))
	  



;;;; [13.1] Bandwidth for Resumable Nodes

;;; The function `bandwidth-needed-for-resumable-node' returns the bandwidth
;;; necessary to transmit the node itself, excluding any of the node's
;;; attributes, vector contents, or list contents.

;;; This function side-effects the following slots contained (directly or
;;; indirectly) in the given resumable node.

;;; > The resumable-attribute-corresponding-index? slot of the
;;;   resumable-attribute-spec structure (if any) inside the
;;;   resumable-attribute-spec? slot of the resumable node.

;;; > If the node is a resumable-instance-mixin, its
;;;   resumable-class-name-corresponding-index?  slot.

;;; > If the resumable-node is a resumable-value-node, its
;;;   resumable-value-corresponding-index? slot,

(defun bandwidth-needed-for-resumable-node (resumable-node icp-port)
  (let ((attribute-spec? (resumable-attribute-spec? resumable-node)))
    (multiple-value-bind
	(attribute-bandwidth index-of-qualifier? index-of-base-name?)
	(bandwidth-for-resumable-attribute-spec attribute-spec? icp-port)
      index-of-qualifier? index-of-base-name?
      (resumable-node-typecase resumable-node
        (:value
	  (multiple-value-bind (value-bandwidth corresponding-index?)
	      (bandwidth-for-evaluation-value
		(resumable-attribute-value resumable-node)
		icp-port)
	    (setf (resumable-value-corresponding-index? resumable-node)
		  corresponding-index?)
	    (+f (bandwidth-for-resumable-node-type-tag)
		attribute-bandwidth
		value-bandwidth)))
	(:circular
	  (+f (bandwidth-for-resumable-node-type-tag)
	      attribute-bandwidth
	      (bandwidth-for-resumable-node-index resumable-node)))
	((:sequence :structure))
	((:object
	   :object-vector :value-vector :history
	   :object-list :value-list)
	 (if (node-itself-sent-p resumable-node)
	     0
	     (multiple-value-bind (class-bandwidth corresponding-index?)
		 (bandwidth-for-resumable-node-class-name
		   resumable-node
		   icp-port)
	       (setf (resumable-class-name-corresponding-index? resumable-node)
		     corresponding-index?)
	       (+f (bandwidth-for-resumable-node-type-tag)
		   (bandwidth-for-ascension-count resumable-node)
		   (bandwidth-for-symbolic-attribute-count resumable-node)
		   (bandwidth-for-sequence-element-description resumable-node)
		   attribute-bandwidth
		   class-bandwidth))))))))

;;; The function `get-available-object-passing-bandwidth' computes the amount of
;;; bandwidth available for object-passing in a scheduled task.  This amount is
;;; the minimum of the bandwidth allowed before network clogging and the
;;; bandwidth that is transmissible before the timeslice of the task expires.
;;; It returns a non-nil second value if the limiting factor on the available
;;; bandwidth is the network; if the limiting factor is the time remaining in
;;; the timeslice, the second value is nil.

;;; Get-available-object-passing-bandwidth does not compute the time before the
;;; timeslice expires via a call to get-fixnum-time, since that value is too
;;; coarse-grained (for reasons of efficiency in executing scheduled tasks that
;;; frequently check time-slice-expired-p).  Instead, the time remaining in the
;;; timeslice is estimated by comparing the amount of bandwidth consumed so far
;;; with the amount of bandwidth consumed by the most recent object-passing task
;;; that has completed its timeslice.

(defun get-available-object-passing-bandwidth (resumable-object)
  (cond
    ((resumable-object-guessed-bandwidth-p resumable-object)
     ;; ... abandon entire remaining timeslice?  review!
     0)
    (t (let ((network-bandwidth
	       (available-bandwidth-for-object-passing
		 (resumable-object-icp-socket resumable-object)))
	     (timeslice-bandwidth
	       (-f (or most-recent-bandwidth-per-timeslice?
		       default-most-recent-bandwidth-per-timeslice)
		   (resumable-object-allocated-bandwidth resumable-object))))
	 (cond
	   ((<f network-bandwidth timeslice-bandwidth)
	    (values network-bandwidth t))
	   (t (setf (resumable-object-guessed-bandwidth-p resumable-object) t)
	      (values timeslice-bandwidth nil)))))))




;;;; [13.2] Bandwidth for Resumable Vectors

;;; The function `get-value-vector-transmission-info' returns four
;;; values:

;;; (1) the maximum number of vector elements that can be transmitted before
;;; filling up the bandwidth or before the timeslice will expire,

;;; (2) the bandwidth needed to transmit these vector elements, and

;;; (3) an icp-tree detailing the symbols to be interned across ICP.  This tree
;;; is an icp-list of icp-conses each of whose car is the index in the vector
;;; and whose cdr is the corresponding ICP object index of the symbol at that
;;; index in the vector, relative to the given ICP port.

;;; (4) A non-nil value if the limiting factor on the bandwidth is the network,
;;; nil otherwise.

;; jh, 5/13/94.  Bandwidth-for-resumable-sequence-length actually depends on
;; number-of-elements to be sent in the vector or list range.  If
;; number-of-elements exceeds (maximum-icp-byte-unsigned-integer), then
;; bandwidth-for-resumable-sequence length is 4 rather than 2.  Since
;; (maximum-icp-byte-unsigned-integer) is currently 63000, this seems unlikely
;; at present, but this will need review eventually.  The reason we use a
;; constant now is that otherwise we would need to include an extra arithmetic
;; comparison for every element in the vector or list range.

(defmacro bandwidth-for-resumable-sequence-length ()
  2)

(defmacro value-array-passing-aref (array-to-pass index)
  `(managed-svref ,array-to-pass ,index))

(defun get-value-vector-transmission-info
    (resumable-value-vector-node element-type? resumable-object icp-port)
  (let ((internal-vector
	  (internal-vector-for-object-passing resumable-value-vector-node))
	global-bandwidth
	network-is-limiting-factor-p)
    (multiple-value-setq (global-bandwidth network-is-limiting-factor-p)
      (get-available-object-passing-bandwidth resumable-object))
    (cond
      ((managed-float-array-p internal-vector)
       (let* ((bandwidth-available 
		(-f global-bandwidth
		    (+f (bandwidth-for-resumable-sequence-length)
			(bandwidth-for-resumable-node-type-tag))))
	      (number-of-elements
		(minf (floorf bandwidth-available (bandwidth-for-icp-float))
		      (1+f (highest-empty-value-vector-index
			     resumable-value-vector-node))))
	      (bandwidth-needed
		(*f number-of-elements (bandwidth-for-icp-float))))
	 (values number-of-elements
		 bandwidth-needed
		 nil
		 network-is-limiting-factor-p)))
      (t (loop with bandwidth-needed =
	       (if element-type?
		   (+f (bandwidth-for-resumable-sequence-length)
		       (bandwidth-for-resumable-node-type-tag))
		   (bandwidth-for-resumable-sequence-length))
	       with bandwidth-available =
	       (-f global-bandwidth bandwidth-needed)
	       with interning-details = nil
	       for vector-index
	       downfrom
	       (highest-empty-value-vector-index resumable-value-vector-node)
		   to 0
	       for element
	       = (value-array-passing-aref internal-vector vector-index)
	       with number-of-elements = 0
	       do
	   (multiple-value-bind (bandwidth corresponding-index?)
	       (if element-type?
		   (case element-type?
		     (integer
		      (bandwidth-for-icp-fixnum
			(evaluation-integer-value element)))
		     (|float| (bandwidth-for-icp-float))
		     (text
		      (bandwidth-for-icp-text-string
			(evaluation-text-value element)))
		     (symbol
		      (bandwidth-for-icp-symbol
			(evaluation-symbol-symbol element)
			icp-port))
		     (truth
		      (bandwidth-for-icp-truth-value element))
		     #+development
		     (otherwise
		      (cerror
			"Continue, assuming the element consumes 2 bytes ~
                         (This behavior is what the user would get)"
	 		"GET-VALUE-VECTOR-TRANSMISSION-INFO: ~
                         unknown element type ~s for element ~s"
			element-type?
			element)
		      2))
		   (bandwidth-for-evaluation-value element icp-port))
	     (let ((new-bandwidth-available
		     (-f bandwidth-available bandwidth)))
	       (cond
		 ((>f new-bandwidth-available 0)
		  (incff bandwidth-needed bandwidth)
		  (setq bandwidth-available new-bandwidth-available)
		  (incff number-of-elements)
		  (when corresponding-index?
		    (icp-push (icp-cons vector-index corresponding-index?)
			      interning-details)))
		 (t (loop-finish)))))
	       finally
		 (return
		   (values number-of-elements
			   bandwidth-needed
			   (nreverse interning-details)
			   network-is-limiting-factor-p)))))))


  

;;;; [13.3] Bandwidth for Resumable Lists

(defun abort-object-passing-due-to-list-length-change
    (resumable-value-list-node resumable-object)
  (with-throw-handling abort-object-passing-due-to-list-length-change
    (throw*
      :abort-transmitting-resumable-object
      (let ((current-object
	      (resumable-instance-current-object resumable-value-list-node))
	    (toplevel-object
	      (object-or-handle-to-be-passed resumable-object)))  
	(icp-list
	  'g2-value-list-length-changed
	  (twith-output-to-text-string
	    (tformat
	      "The G2 value-list ~NF" current-object)
	    (if (eq current-object toplevel-object)
		(tformat " at top level in the argument list")
		(tformat ", being sent as a subobject of ~NF, "
			 toplevel-object))
	    (tformat "has had its length changed")))))))

;;; The function `get-value-list-transmission-info' returns five values:
;;;   (1) The maximum number of list elements that can be transmitted before
;;;       filling up the bandwidth or before the timeslice will expire.
;;;   (2) The bandwidth needed to transmit these list elements.
;;;   (3) A non-nil value if the list was completely processed, nil otherwise.
;;;   (4) An icp-tree detailing the symbols to be interned across ICP.  This
;;;       tree is an icp-list of icp-conses each of whose car is the index in
;;;       the list and whose cdr is the corresponding ICP object index of the
;;;       symbol at the index in the list, relative to the given ICP port.
;;;   (5) A non-nil value if the limiting factor on the bandwidth is the
;;;       network, nil otherwise.

;;; This function can throw to :abort-transmitting-resumable-object if the list
;;; has unexpectedly shortened, but does not check for unexpected lengthening.

(defun get-value-list-transmission-info
    (resumable-value-list-node element-type? resumable-object icp-port
     &aux global-bandwidth network-is-limiting-factor-p)
  (with-throw-handling get-value-list-transmission-info
    (multiple-value-setq (global-bandwidth network-is-limiting-factor-p)
      (get-available-object-passing-bandwidth resumable-object))
    (loop with bandwidth-needed =
	  (if element-type?
	      (+f (bandwidth-for-resumable-sequence-length)
		  (bandwidth-for-resumable-node-type-tag))
	      (bandwidth-for-resumable-sequence-length))
	  with bandwidth-available = (-f global-bandwidth bandwidth-needed)
	  with interning-details = nil
	  with length-of-value-list
	    = (resumable-sequence-length resumable-value-list-node)
	  for list-element = (internal-list-for-object-passing
			       resumable-value-list-node)
			   then (list-next-element-real list-element)
	  while (and (internal-list-elements-remain-p
		       list-element
		       (resumable-instance-current-object
			 resumable-value-list-node))
		     (<f (current-value-list-index resumable-value-list-node)
			 length-of-value-list))
	  for element = (list-element-value list-element)
	  with number-of-elements = 0
	  do
      (multiple-value-bind (bandwidth corresponding-index?)
	  (if element-type?
	      (case element-type?
		(integer
		 (bandwidth-for-icp-fixnum (evaluation-integer-value element)))
		(|float| (bandwidth-for-icp-float))
		(text
		 (bandwidth-for-icp-text-string (evaluation-text-value element)))
		(truth
		 (bandwidth-for-icp-truth-value
		   (evaluation-truth-value-value element)))
		(symbol
		 (bandwidth-for-icp-symbol
		   (evaluation-symbol-symbol element)
		   icp-port)))
	      (bandwidth-for-evaluation-value element icp-port))
	(let ((new-bandwidth-available (-f bandwidth-available bandwidth)))
	  (cond
	    ((>f new-bandwidth-available 0)
	     (incff bandwidth-needed bandwidth)
	     (setq bandwidth-available new-bandwidth-available)
	     (incff number-of-elements)
	     (incff (current-value-list-index resumable-value-list-node))
	     (when corresponding-index?
	       (icp-push (icp-cons number-of-elements corresponding-index?)
			 interning-details)))
	    (t (loop-finish)))))
	  finally
	    (let ((list-elements-remain-p
		    (internal-list-elements-remain-p
		      list-element
		      (resumable-instance-current-object
			resumable-value-list-node))))
	      (when (and (not list-elements-remain-p)
			 (<f (current-value-list-index
			       resumable-value-list-node)
			     length-of-value-list))
		(handle-throw
		  (abort-object-passing-due-to-list-length-change
		    resumable-value-list-node
		    resumable-object)))
	      (return
		(values number-of-elements
			bandwidth-needed
			list-elements-remain-p
			(nreverse interning-details)
			network-is-limiting-factor-p))))))




;;;; [13.4] Bandwidth for Resumable Histories

;; jh, 9/13/94.  Rearranging.  For now, this is under [14.3.4.4], "G2 Resumable
;; History Protocol".




;;;; [14.3.4.1] G2 Leaf Protocols

;;;; [14.3.4.1.1] G2 System Attribute Protocol

(defvar-for-macro object-passing-system-attribute-registry nil)

(defmacro all-immediate-object-passing-system-attribute-names ()
  `',(mapcar #'first object-passing-system-attribute-registry))

(defmacro all-object-passing-system-attribute-names ()
  `',(cons 'history (mapcar #'first object-passing-system-attribute-registry)))

(defmacro def-object-passing-system-attribute
    (name-of-attribute (object-var new-value-var system-includes-var)
     &key ((:grammar grammar?)) predicate getter setter)
  (unless (symbolp object-var)
    (error "DEF-OBJECT-PASSING-SYSTEM-ATTRIBUTE: ~
            need symbol for object-var, not ~a"
	   object-var))
  (unless (symbolp system-includes-var)
    (error "DEF-OBJECT-PASSING-SYSTEM-ATTRIBUTE: ~
            need symbol for system-includes-var, not ~a"
	   object-var))
  (let ((name-of-attribute-getter
	  (intern
	    (format nil
              "GET-~a-SYSTEM-ATTRIBUTE-FOR-OBJECT-PASSING"
	      name-of-attribute)))
	(name-of-attribute-spec-structure-creator
	  (intern
	    (format nil
	      "GET-~a-ATTRIBUTE-SPEC-STRUCTURE-FOR-OBJECT-PASSING"
	      name-of-attribute)))
	(name-of-attribute-setter
	  (intern
	    (format nil
	      "SET-~a-SYSTEM-ATTRIBUTE-FOR-OBJECT-PASSING"
	      name-of-attribute))))
    `(progn
       ,@(if grammar?
	     `((add-grammar-rules
		 '((implemented-object-passing-system-attribute
		    ,grammar?
		    ,name-of-attribute))))
	     nil)
       ,@(if (eval-feature :no-macros)
	     nil
	     `((eval-when (:compile-toplevel :load-toplevel :execute)
		 (pushnew
		   (list ',name-of-attribute
			 ',name-of-attribute-getter
			 ',name-of-attribute-spec-structure-creator
			 ',name-of-attribute-setter)
		   object-passing-system-attribute-registry
		   :test #'equal))))
       (defun-simple ,name-of-attribute-getter (,object-var)
	 ,getter)
       (defun-simple ,name-of-attribute-spec-structure-creator
	   (,object-var ,system-includes-var)
	 ,@(if (constantp predicate)
	       (if (eval predicate)
		   `((declare (ignore ,object-var))
		     (if (memq ',name-of-attribute ,system-includes-var)
			 (make-resumable-attribute-name
			   nil ',name-of-attribute)
			 nil))
		   `((declare (ignore ,object-var ,system-includes-var))
		     nil))
	      `((if (and (memq ',name-of-attribute ,system-includes-var)
			 ,predicate)
		    (make-resumable-attribute-name
		      nil ',name-of-attribute)
		    nil))))
       (defun-void ,name-of-attribute-setter (,object-var ,new-value-var)
	 (cond
	   (,predicate ,setter)
	   (t (record-object-building-problem-on-receiving-side
		',(if (eq name-of-attribute 'current-value)
		      'unable-to-set-current-value-because-item-is-not-a-variable-or-parameter
		      'inappropriate-item-for-system-attribute)
		nil
		',name-of-attribute
		(class ,object-var)))))
       ',name-of-attribute)))

(defmacro with-protected-validity-interval ((variable-or-parameter) &body body)
  (avoiding-variable-capture (variable-or-parameter &aux restore-supplied-p)
    `(let ((,restore-supplied-p nil))
       (when (variable-p ,variable-or-parameter)
	 (let ((validity-interval (validity-interval ,variable-or-parameter)))
	   (when (eq validity-interval 'supplied)
	     (setf (validity-interval ,variable-or-parameter) 'indefinite)
	  (setq ,restore-supplied-p t))))
       ,@body
       (when ,restore-supplied-p
	 (setf (validity-interval variable-or-parameter) 'supplied)))))

(defun-void put-current-value-for-object-passing
    (variable-or-parameter new-value collection-time? potential-problem-name)
  (with-protected-validity-interval (variable-or-parameter)
    (let ((problem-string?
	    (put-current-evaluation-value
	      variable-or-parameter
	      new-value
	      nil
	      collection-time?
	      nil)))
      (when problem-string?
	(record-object-building-problem-on-receiving-side
	  potential-problem-name
	  nil
	  'current-value-of-variable-or-parameter
	  (class variable-or-parameter)
	  "~A"
	  #'reclaim-text-string
	  problem-string?)))))

(defun-simple get-default-collection-time-for-put-current-value
    (variable-or-parameter)
  (let ((collection-time-0-points-ago
	  (or
	  (get-collection-time-of-previous-datapoint
	    variable-or-parameter
	    nil
	    0)
	  *some-time-ago*)))
    ;; jh, 10/19/94.  Following code copied from funcalled instruction for
    ;; conclude.    
    ;; jh, 11/11/94.  Update this copied code.  Consider abstracting soon.
    (if (fixnump collection-time-0-points-ago)
	(convert-gensym-time-to-unix-time
	  (+f (clock-get gensym-time-at-start)
	      collection-time-0-points-ago))
	(+e collection-time-0-points-ago
	    (managed-float-value (clock-get g2-time-at-start))))))
    
(def-object-passing-system-attribute current-value
    (variable-or-parameter new-value? system-includes)
  :grammar ('current 'value 'of 'variable-or-parameter)
  :predicate
  (frame-of-class-p variable-or-parameter 'variable-or-parameter)
  :getter
  (let ((*current-computation-frame* variable-or-parameter)
	(current-computation-flags current-computation-flags))
    (setf (force-new-request-for-value) nil)
    (setf (dont-compute-new-variable-values) t)
    (get-current-evaluation-value variable-or-parameter nil))
  :setter
  (when new-value?
    ;; jh, 10/19/94.  Might want to batch entry into the
    ;; with-temporary-gensym-float-creation somehow (the way we do for
    ;; histories).  We need the scope in the first place because
    ;; put-current-evaluation-value requires it.
    (with-temporary-gensym-float-creation value
      (let ((*current-computation-frame* variable-or-parameter))
	(cond
	  ((variable-or-parameter-stored-histories? variable-or-parameter)
	   (let* ((g2-time-at-start
		    (or (remote-g2-time-at-start?
			  current-receiving-resumable-object)
			(clock-get g2-time-at-start)))
		  (collection-time-for-put-current-evaluation-value
		    (get-default-collection-time-for-put-current-value
		      variable-or-parameter))
		  (previous-time-of-most-recent-value
		    (time-of-most-recent-value variable-or-parameter)))
	     (reclaim-evaluation-value previous-time-of-most-recent-value)
	     (setf (time-of-most-recent-value variable-or-parameter)
		   *some-time-ago*)
	     (put-current-value-for-object-passing
	       variable-or-parameter
	       new-value?
	       collection-time-for-put-current-evaluation-value
	       'problem-putting-current-value-into-history-keeper)))
	  (t (put-current-value-for-object-passing
	       variable-or-parameter
	       new-value?
	       nil
	       'problem-putting-current-value-into-variable-or-parameter)))))))

(def-object-passing-system-attribute name (item new-name system-includes)
  :grammar ('name 'of 'item) 
  :predicate t
  :getter
  (let ((name-or-names (name-or-names-for-frame item)))
    (cond
      ((consp name-or-names) (car name-or-names))
      ((symbolp name-or-names) name-or-names)
      #+development
      (t (cerror
	   "Continue, returning NIL ~
            (This behavior is what the user would get)"
	   "G2-GET-ATTRIBUTE-FOR-OBJECT-PASSING: ~
            unexpected thing ~s in name-or-names-for-frame of ~s"
	   name-or-names
	   item)
	 nil)))
  :setter
  ;; A simple setf doesn't update frame notes (such as the duplicate name
  ;; warning).
  (change-slot-value item 'name-or-names-for-frame new-name))

(defun-void set-text-object-passing-system-attribute (item new-text?)
  ;; Adapted from the def-funcalled-instruction for
  ;; change-the-text-of-attribute.
  (when new-text?
    (let*-while-true 
	((text-slot-name?
	   (frame-class-case item
	     (action-button
	       (get-slot-name-for-alias-if-any 'action item))
	     (otherwise
	       (get-slot-name-for-alias-if-any 'text item))))
	 (slot-description?
	   (get-slot-description-of-frame text-slot-name? item nil))
	 (type-of-slot-if-editable?
	   (type-slot-feature-assq-if-editable
	     (slot-features slot-description?))))
      (when (or (attribute-operation-is-allowed-p
		  'edit-attribute
		  item
		  'text
		  (defining-class slot-description?))
		(of-class-p item 'message))
	(unless (parse-and-change-slot
		  item
		  slot-description?
		  new-text?
		  type-of-slot-if-editable?)
	  (reclaim-text-string new-text?))))))

(def-object-passing-system-attribute text (item new-text? system-includes)
  :predicate (or (of-class-p item 'text-box)
		 (of-class-p item 'procedure)
		 (of-class-p item 'action-button)
		 #+java-export-facilities
		 (of-class-p item 'external-java-class))
  :getter
   (let ((text?
	   (frame-class-case item
	     (text-box (box-translation-and-text item))
	     (procedure (procedure-definition item))
	     (action-button
	       (translation-and-text-of-embedded-rule-function item))
	     #+java-export-facilities
	     (external-java-class
	       (get-slot-value-if-any item 'compilation-unit)))))
     (and text? (convert-text-to-text-string text?)))
  :setter
  (set-text-object-passing-system-attribute item new-text?))

#+java-export-facilities
(def-object-passing-system-attribute package-declaration
    (item new-text? system-includes)
  :predicate (of-class-p item 'external-java-class)
  :getter
   (let ((text? (get-slot-value-if-any item 'package-declaration)))
     (and text? (convert-text-to-text-string text?)))
  :setter
  (set-text-object-passing-system-attribute item new-text?))

#+java-export-facilities
(def-object-passing-system-attribute import-declarations
    (item new-text? system-includes)
  :predicate (of-class-p item 'external-java-class)
  :getter
   (let ((text? (get-slot-value-if-any item 'import-declarations)))
     (and text? (convert-text-to-text-string text?)))
  :setter
  (set-text-object-passing-system-attribute item new-text?))

(defmacro body-of-g2-get-system-attribute-for-object-passing
    (object system-attribute-name)
  (avoiding-variable-capture (object)
    `(case ,system-attribute-name
       ,@(loop for (name-of-attribute getter-function)
		   in object-passing-system-attribute-registry
	       collect
	       `(,name-of-attribute (,getter-function ,object)))
       #+development
       (otherwise
	(error "BODY-OF-G2-GET-SYSTEM-ATTRIBUTE-FOR-OBJECT-PASSING: ~
                unknown system attribute ~s"
	       ',system-attribute-name)))))


(defmacro body-of-g2-add-system-attribute-to-remote-object
    (current-subobject attribute-name-or-index leaf)
  (avoiding-variable-capture (current-subobject leaf)
  `(case ,attribute-name-or-index
     ,@(loop for (attribute-name nil nil setter-function)
	     in object-passing-system-attribute-registry
	     collect
	     `(,attribute-name
		 (,setter-function ,current-subobject ,leaf)))
     #+development
     (otherwise
      (error "BODY-OF-G2-ADD-SYSTEM-ATTRIBUTE-TO-REMOTE-OBJECT: ~
                unknown system attribute ~s"
	     ',attribute-name-or-index)))))


;;;; [14.3.4.1.2] G2 User Attribute Protocols

(defmacro body-of-g2-read-icp-attribute-for-list-of-attributes (tag)
  `(case ,tag
     (,qualified-symbolic-attribute-tag
      (let* ((qualifier (read-icp-possibly-interned-symbol))
	     (base-name (read-icp-possibly-interned-symbol)))
	(make-slot-name-denotation
	  base-name
	  qualifier
	  icp-cons)))
     (,unqualified-symbolic-attribute-tag
      (read-icp-possibly-interned-symbol))
     (otherwise
      #+development
      (cerror "Continue, returning nil ~
               (This behavior is what the user would get)"
	      "READ-ICP-LIST-OF-ATTRIBUTES:  unexpected tag ~a"
	      ,tag)
      nil)))
  
(defun-simple g2-read-icp-attribute-for-list-of-attributes (tag)
  (body-of-g2-read-icp-attribute-for-list-of-attributes tag))

(defun-void g2-write-icp-list-of-attributes (list-of-attributes)
  (write-icp-fixnum (length list-of-attributes))
  (loop for attribute in list-of-attributes
	do
    (cond
      ((class-qualified-name-list-p attribute)
       (write-icp-byte qualified-symbolic-attribute-tag)
       (write-icp-possibly-interned-symbol (class-qualifier attribute) nil)
       (write-icp-possibly-interned-symbol (unqualified-name attribute) nil))
      (t (write-icp-byte unqualified-symbolic-attribute-tag)
	 (write-icp-possibly-interned-symbol
	   (unqualified-name attribute)
	   nil)))))

;;; The function `g2-add-leaf-to-remote-object' is called on the receiving side.

;; [ghw writes on 3/21/94:]
;; Is the call to change-slot-value for user-defined slots?  I'm asking this
;; because we would now like to restrict user-defined slot value changes to
;; their declared types.

;; [ghw writes on 3/22/94:]
;; Type Specifications For User-Defined Slots
;; 
;; The grammar for attribute-descriptions now prompts users for an optional
;; attribute type specification and restricts the initial value entered in the
;; editor to that type.  The plan now is to write code to enforce type
;; conformity on changes to that initial attribute value.
;;
;; I have found at least three areas in the code where an attribute value can be
;; changed: editing an attribute value, concluding an attribute value, and
;; changing an attribute value by a remote procedure call.  Do you know of any
;; other areas?
;;
;; I've talked with Mark about editing an attribute value.  One way to go is to
;; refine the present attribute grammar, attribute compiler, and attribute
;; writer to more restricted versions -- that is, keep the present version for
;; the most unrestricted type, item-or-datum, and write grammars, compilers, and
;; writers for these types: datum, number, integer, float, truth-value, symbol,
;; text, and item.  If we put the type specification in the "type" slot feature
;; of the slot description, some good things would "fall out" like refined
;; prompting and type restriction.
;;
;; For conclude actions, Jim suggests conclude-instruction code to compare the
;; new attribute value with the slot description type specification, and issue a
;; stack error when there is a mismatch.
;;
;; I do not have any notions for handling attribute value changes with remote
;; procedure calls.  Ideas on this and other areas would be appreciated.

;; [jra responds on 3/22/94:]
;; I think that there are parts of the code that use the presence of the
;; "attribute" slot type to determine that this is a user defined slot.  We
;; should take care to root out such code if this change is made.

;; [ghw writes on 4/20/94:]
;; It looks like g2-add-leaf-to-remote-object would be a good place to check for
;; type conformance if all attribute value changes from bridges go though this
;; function.
;;
;; We'd need to do something like what I've done in the
;; (def-funcalled-instruction conclude ...) in STACK-ACTS. ...
;;
;; Checking for type conformance is easy -- but you need to decide what sort of
;; error behavior you want to happen when there is a breach of attribute type
;; specification.

;; ... review the violation of the slot-constant abstraction (if any)!
(defun change-slot-value-for-object-passing
    (current-subobject unique-slot-name leaf)
  (evaluation-typecase leaf
    (evaluation-truth-value
      (let ((slot-constant 
	     (slot-value-list evaluation-truth-value 'truth-value)))
       (reclaim-evaluation-truth-value leaf)
       (change-slot-value
	 current-subobject
	 unique-slot-name
	 slot-constant)))
    (otherwise (change-slot-value
		 current-subobject
		 unique-slot-name	 
		 leaf))))

(defun-allowing-unwind change-exported-attribute-for-object-passing
    (object attribute-name attribute-qualifier? new-value?)
  (with-catch-handlers
      (((:stack-error) (passed-top-of-stack error-name error-text)
	(declare (ignore passed-top-of-stack error-name))
	(reclaim-error-text error-text)
	t))
    (if (null new-value?)
	t
	(let* ((component
		 (make-attribute-component-particulars
		   attribute-name
		   nil
		   '*current-computation-frame*))
	       (error-message?
		 (conclude-into-attribute-component
		   object
		   attribute-name
		   attribute-qualifier?
		   new-value?
		   nil
		   component)))
	  (reclaim-attribute-component-particulars-without-recursion component)
	  (cond
	    (error-message?
	     (reclaim-text-string error-message?)
	     nil)
	    (t t))))))

(defun-void g2-list-insert-for-object-passing (thing-to-insert g2-list)
  (when (list-structure g2-list)
    (g2-list-insert-at-end thing-to-insert g2-list)))

(defun g2-add-leaf-to-remote-object
    (current-subobject
      attribute-type
      attribute-qualifier?
      attribute-name-or-index
      leaf)
  (unless (resumable-object-ignoring-input? current-receiving-resumable-object)
    (case attribute-type
      (attribute
       (if (memq attribute-name-or-index
		 (all-immediate-object-passing-system-attribute-names))
	   (body-of-g2-add-system-attribute-to-remote-object
	     current-subobject
	     attribute-name-or-index
	     leaf)
	   (let* ((class-of-current-subobject (class current-subobject))
		  (slot-description?
		    (and (of-class-p current-subobject 'object)
			 (get-slot-description-of-class-description
			   attribute-name-or-index
			   (class-description class-of-current-subobject)
			   attribute-qualifier?))))
	     (cond
	       (slot-description?
		(cond
		  ((type-specification-type-p
		     leaf
		     (slot-type-specification slot-description?))
		   (let ((previous-attribute-contents?
			   (get-slot-description-value
			     current-subobject
			     slot-description?))
			 (unique-slot-name (unique-slot-name slot-description?)))
		     (when (and previous-attribute-contents?
				(framep previous-attribute-contents?)
				(transient-p previous-attribute-contents?))
		       ;; ... review for leaks!
		       (delete-frame previous-attribute-contents?)
		       (set-slot-value
			 current-subobject
			 unique-slot-name
			 nil))
		     (change-slot-value-for-object-passing
		       current-subobject
		       unique-slot-name
		       leaf)))
		  (t (record-object-building-problem-on-receiving-side
			   'leaf-value-inappropriate-for-attribute
			   attribute-qualifier?
			   attribute-name-or-index
			   class-of-current-subobject))))
	       (t (unless (change-exported-attribute-for-object-passing
			    current-subobject
			    attribute-name-or-index
			    attribute-qualifier?
			    leaf)
		    (record-object-building-problem-on-receiving-side
		      'leaf-attribute-name-inappropriate-for-class
		      attribute-qualifier?
		      attribute-name-or-index
		      class-of-current-subobject)))))))
      (vector-element
       (cond
	 ((not (frame-of-class-p current-subobject 'g2-array))
	  (record-object-building-problem-on-receiving-side
	    'add-g2-array-leaf-to-non-g2-array
	    nil
	    attribute-name-or-index
	    (class current-subobject)))
	 ((>=f attribute-name-or-index (g2-array-length current-subobject))
	  (record-object-building-problem-on-receiving-side
	    'leaf-index-out-of-bounds-for-g2-array
	    nil
	    attribute-name-or-index
	    (class current-subobject)))
	 (t
	  (let* ((item-or-datum? leaf)
		 (element-type (g2-array-element-type current-subobject))
		 (allow-no-value-p (or (not (null (class-description element-type)))
				       (eq element-type 'item-or-datum))))
	    (cond ((and allow-no-value-p (null item-or-datum?))
		   (setf (g2-array-aref current-subobject attribute-name-or-index) nil))
		  ((not (or (type-specification-type-p item-or-datum? element-type)
			    (of-class-p item-or-datum? element-type)))
		   (record-object-building-problem-on-receiving-side
		     'incompatible-type-of-g2-array-leaf
		     nil
		     attribute-name-or-index
		     (class current-subobject)))		     
		  (t (setf (g2-array-aref current-subobject attribute-name-or-index)
			   leaf)))))))
      (list-element
       (cond
	 ((not (frame-of-class-p current-subobject 'g2-list))
	  (record-object-building-problem-on-receiving-side
	    'add-g2-list-leaf-to-non-g2-list
	    nil
	    attribute-name-or-index
	    (class current-subobject)))
	 (t
	  (let* ((item-or-datum? leaf)
		 (element-type (list-type current-subobject))
		 (allow-no-value-p (or (not (null (class-description element-type)))
				       (eq element-type 'item-or-datum))))
	    (cond ((and allow-no-value-p (null item-or-datum?)))
		  ((not (or (type-specification-type-p item-or-datum? element-type)
			    (of-class-p item-or-datum? element-type)))
		   (record-object-building-problem-on-receiving-side
		     'incompatible-type-of-g2-list-leaf
		     nil
		     attribute-name-or-index
		     (class current-subobject)))		     
		  (t (g2-list-insert-for-object-passing
		       leaf
		       current-subobject))))))))))






;;;; [14.3.4.2] G2 Resumable Object Protocols

;;; The function `permissible-to-create-object-passing-class-p' returns two
;;; values: a non-nil first value indicates that an instance of the class given
;;; by class-name may be passed as an argument to an RPC or created on the
;;; remote side once the argument has been sent.  If the first value is nil, the
;;; second value is a symbol describing the reason why not.  Eventually (jh,
;;; 2/11/94), this function should consult network restrictions to determine if
;;; the object can be created on the remote side.

(defun permissible-to-create-object-passing-class-p (class-name)
  (cond
    ((not (classp class-name))
     (values nil 'nonexistent-class-for-object-passing))
    (t (values t nil))))

(defun-simple g2-resumable-object-reprocessed-p
    (toplevel-object resumable-object)
  (frame-has-been-reprocessed-p
    toplevel-object
    (resumable-object-reference-serial-number resumable-object)))

(defun g2-add-resumable-circularity (corresponding-index)
  (unless (resumable-object-ignoring-input?
	    current-receiving-resumable-object)
    (let ((current-subobject?
	    (current-resumable-subobject-being-built?
	      current-receiving-resumable-object)))
      (cond
	(current-subobject?
	 (store-corresponding-icp-object
	   corresponding-index
	   current-subobject?)
	 (icp-push corresponding-index
		   (corresponding-indices-of-subobjects
		     current-receiving-resumable-object)))
	(t (record-object-building-problem-on-receiving-side
	     'premature-corresponding-index-transmission
	     nil
	     nil
	     nil))))))

;;; The function `add-to-or-traverse-remote-object' is called on the receiving
;;; side.

;; ...
;; ghw, 3/21/94 writes:
;; In rpc-common2.lisp, is the call to change-slot-value for user-defined slots?
;; I'm asking this because we would now like to restrict user-defined slot value
;; changes to their declared types.

;; ghw, 3/22/94 writes under "Type specifications for user-defined slots":
;;
;; The grammar for attribute-descriptions now prompts users for an optional
;; attribute type specification and restricts the initial value entered in the
;; editor to that type.  The plan now is to write code to enforce type
;; conformity on changes to that initial attribute value.
;;
;; I have found at least three areas in the code where an attribute value can be
;; changed: editing an attribute value, concluding an attribute value, and
;; changing an attribute value by a remote procedure call.  Do you know of any
;; other areas?
;;
;; I've talked with Mark about editing an attribute value.  One way to go is to
;; refine the present attribute grammar, attribute compiler, and attribute
;; writer to more restricted versions -- that is, keep the present version for
;; the most unrestricted type, item-or-datum, and write grammars, compilers, and
;; writers for these types: datum, number, integer, float, truth-value, symbol,
;; text, and item.  If we put the type specification in the "type" slot feature
;; of the slot description, some good things would "fall out" like refined
;; prompting and type restriction.
;;
;; For conclude actions, Jim suggests conclude-instruction code to compare the
;; new attribute value with the slot description type specification, and issue a
;; stack error when there is a mismatch.
;;
;; I do not have any notions for handling attribute value changes with remote
;; procedure calls.  Ideas on this and other areas would be appreciated.

;; jra, 3/22/94, responds:
;;
;; I don't recall the remote procedure call pathway.  Please explain it to me at
;; some point.
;;
;; I think that there are parts of the code that use the presence of the
;; "attribute" slot type to determine that this is a user defined slot.  We
;; should take care to root out such code if this change is made.

(defun add-to-or-traverse-remote-object
    (current-subobject
      attribute-type
      attribute-qualifier?
      attribute-name-or-index
      class-name)
  (case attribute-type
    (attribute
     (unless (memq attribute-name-or-index '(name value))
       (let ((slot-description?
	       (and (of-class-p current-subobject 'object)
		    (get-slot-description-of-class-description
		      attribute-name-or-index
		      (class-description (class current-subobject))
		      attribute-qualifier?))))
	 (cond
	   (slot-description?
	    (let ((attribute-contents?
		    (get-slot-description-value
		      current-subobject
		      slot-description?)))
	      (unless nil ; attribute-contents?
		(setq attribute-contents?
		      (if (transient-p current-subobject)
			  (make-transient-item class-name)
			  (make-frame class-name)))
		(unless (object-passing-info? attribute-contents?)
		  (setf (object-passing-info? attribute-contents?)
			(make-object-passing-info))
		  (setf (g2-rpc-object-handed-off-to-user-p attribute-contents?)
			nil))
		(change-slot-value-for-object-passing
		  current-subobject
		  (unique-slot-name slot-description?)
		  attribute-contents?))
	      (setf (current-resumable-subobject-being-built?
		      current-receiving-resumable-object)
		    attribute-contents?)
	      attribute-contents?))
	   (t (let ((attribute-contents?
		      (if (transient-p current-subobject)
			  (make-transient-item class-name)
			  (make-frame class-name))))
		(cond
		  ((change-exported-attribute-for-object-passing
		     current-subobject
		     attribute-name-or-index
		     attribute-qualifier?
		     attribute-contents?)
		   (unless (object-passing-info? attribute-contents?)
		     (setf (object-passing-info? attribute-contents?)
			   (make-object-passing-info))
		     (setf (g2-rpc-object-handed-off-to-user-p attribute-contents?)
			   nil))
		   attribute-contents?)
		  (t (when attribute-contents?
		       (delete-frame attribute-contents?))
		     (record-object-building-problem-on-receiving-side
		       'attribute-name-inappropriate-for-class
		       attribute-qualifier?
		       attribute-name-or-index
		       class-name)))))))))
    (vector-element
     (cond
       ((not (frame-of-class-p current-subobject 'g2-array))
	(record-object-building-problem-on-receiving-side
	  'add-g2-array-element-to-non-g2-array
	  attribute-qualifier?
	  attribute-name-or-index
	  class-name)
	nil)
       ((>=f attribute-name-or-index (g2-array-length current-subobject))
	(record-object-building-problem-on-receiving-side
	  'index-out-of-bounds-for-g2-array
	  attribute-qualifier?
	  attribute-name-or-index
	  class-name)
	nil)
       (t
	(let ((new-object (make-transient-item class-name)))
	  (unless (object-passing-info? new-object)
	    (setf (object-passing-info? new-object)
		  (make-object-passing-info))
	    (setf (g2-rpc-object-handed-off-to-user-p new-object) nil))
	  (setf (g2-array-aref
		  current-subobject
		  attribute-name-or-index)
		new-object)
	  (icp-push (icp-cons
		      current-receiving-resumable-object
		      current-subobject)
		    (parent-item-lists-or-arrays new-object))
	  (setf (current-resumable-subobject-being-built?
		  current-receiving-resumable-object)
		new-object)
	  new-object))))
    (list-element
     (cond
       ((not (frame-of-class-p current-subobject 'g2-list))
	(record-object-building-problem-on-receiving-side
	  'add-g2-list-element-to-non-g2-list
	  attribute-qualifier?
	  attribute-name-or-index
	  class-name)
	nil)
       (t (let ((new-object (make-transient-item class-name)))
	    (unless (object-passing-info? new-object)
	      (setf (object-passing-info? new-object)
		    (make-object-passing-info))
	      (setf (g2-rpc-object-handed-off-to-user-p new-object) nil))
	    (g2-list-insert-for-object-passing
	      new-object
	      current-subobject)
	    (icp-push (icp-cons
			current-receiving-resumable-object
			current-subobject)
		      (parent-item-lists-or-arrays new-object))
	    (setf (current-resumable-subobject-being-built?
		    current-receiving-resumable-object)
		  new-object)
	    new-object))))))

;;; The function `g2-build-remote-object' is called on the receiving side.

(defun g2-build-remote-object
    (attribute-type attribute-qualifier? attribute-name-or-index class-name)
  (unless (resumable-object-ignoring-input? current-receiving-resumable-object)
    (multiple-value-bind (permissible-p problem)
	(permissible-to-create-object-passing-class-p class-name)
      (cond
	(permissible-p
	 (let ((current-subobject?
		 (current-resumable-subobject-being-built?
		   current-receiving-resumable-object)))
	   (cond
	     (current-subobject?
	      (let ((subobject?
		      (add-to-or-traverse-remote-object
			current-subobject?
			attribute-type
			attribute-qualifier?
			attribute-name-or-index
			class-name)))
		subobject?))
	     (t (let ((toplevel-object (make-transient-item class-name)))
		  (setf (resumable-object-being-built?
			  current-receiving-resumable-object)
			toplevel-object)
		  (frame-serial-number-setf (resumable-object-reference-serial-number
			  current-receiving-resumable-object)
			(frame-serial-number toplevel-object))
		  (setf (current-resumable-subobject-being-built?
			  current-receiving-resumable-object)
			toplevel-object)
		  (unless (object-passing-info? toplevel-object)
		    (setf (object-passing-info? toplevel-object)
			  (make-object-passing-info))
		    (setf (g2-rpc-object-handed-off-to-user-p toplevel-object)
			  nil))
		  toplevel-object)))))
	(t (record-object-building-problem-on-receiving-side
	     problem
	     attribute-qualifier?
	     attribute-name-or-index
	     class-name)
	   nil)))))

(defun get-object-passing-parent (object)
  (or (parent-frame object)
      (let ((parent-item-lists-or-arrays
	      (parent-item-lists-or-arrays object)))
	(gensym-dstruct-bind
	    ((receiving-resumable-object? . parent-object)
	     (first parent-item-lists-or-arrays))
	  (cond
	    ((and receiving-resumable-object?
		  (eq receiving-resumable-object?
		      current-receiving-resumable-object))
	     (reclaim-icp-cons
	       (icp-pop (parent-item-lists-or-arrays object)))
	     parent-object)
	    (receiving-resumable-object?
	     (loop for trailing-cons on parent-item-lists-or-arrays
		   for (receiving-resumable-object . parent-object)
		       in (rest parent-item-lists-or-arrays)
		   when
		     (eq receiving-resumable-object
			 current-receiving-resumable-object)
		     do
		       (let ((reclaimable-cons (cdr trailing-cons)))
			 (setf (cdr trailing-cons) (cddr trailing-cons))
			 (reclaim-icp-cons (car reclaimable-cons))
			 (reclaim-icp-cons reclaimable-cons)
			 (return parent-object))
		   finally
		     (return nil)))
	    (t nil))))))

(defun g2-ascend-to-parent (ascension-count)
  (unless (resumable-object-ignoring-input?
	    current-receiving-resumable-object)
    (let ((current-subobject?
	    (current-resumable-subobject-being-built?
	      current-receiving-resumable-object)))
      (cond
	(current-subobject?
	 (loop repeat ascension-count
	       with ancestor? = current-subobject?
	       do
	   (setq ancestor?
		 (get-object-passing-parent ancestor?))
	   (unless ancestor?
	     (record-object-building-problem-on-receiving-side
	       'attribute-hierarchy-not-isomorphous
	       nil
	       nil
	       nil)
	     (loop-finish))
	       finally
		 (when ancestor?
		   (setf (current-resumable-subobject-being-built?
			   current-receiving-resumable-object)
			 ancestor?))))
	(t (record-object-building-problem-on-receiving-side
	     'premature-ascent-of-attribute-hierarchy
	     nil
	     nil
	     nil))))))



;;;; [14.3.4.3] G2 Resumable Sequence Protocols

(defun-void g2-receive-add-attribute-object-vector
    (attribute-type
      attribute-qualifier?
      attribute-name-or-index
      class-name
      symbolic-attribute-count
      resumable-vector-length)
  (declare (ignore symbolic-attribute-count))
  (cond
    ((or (subclassp class-name 'item-array)
	 (and (subclassp class-name 'g2-array)
	      (not (subclassp class-name 'value-array))))
     (let ((new-object-vector?
	     (g2-build-remote-object
	       attribute-type
	       attribute-qualifier?
	       attribute-name-or-index
	       class-name)))
       (cond
	 ((and (framep new-object-vector?)
	       (or (frame-of-class-p new-object-vector? 'item-array)
		   (and (frame-of-class-p new-object-vector? 'g2-array)
			(not (frame-of-class-p
			       new-object-vector?
			       'value-array)))))
	  (change-slot-value-for-object-passing
	    new-object-vector?
	    'g2-array-length
	    resumable-vector-length))
	 (t (record-object-building-problem-on-receiving-side
	      'item-array-sent-to-non-item-array-attribute
	      nil
	      nil
	      class-name)))))
    (t (record-object-building-problem-on-receiving-side
	 'item-array-sent-to-non-item-array-class-definition
	 nil
	 nil
	 class-name))))

(defun-simple array-element-type-for-class (class-name)
  (let ((element-type (slot-init-form (slot-description-from-class class-name 'g2-array-element-type))))
    (case element-type
      (datum 'value)
      (item-or-datum 'item-or-value)
      (number 'quantity)
      (t element-type))))

(defun-void g2-receive-add-attribute-value-vector
    (attribute-type
      attribute-qualifier?
      attribute-name-or-index
      class-name
      symbolic-attribute-count
      element-type
      resumable-vector-length)
  (declare (ignore symbolic-attribute-count))
  (cond
    ((subclassp class-name 'value-array)
     (cond ((array-or-list-element-type-suitable-p
	      (or element-type 'value)
	      (array-element-type-for-class class-name))
	    (let ((new-value-vector?
		    (g2-build-remote-object
		      attribute-type
		      attribute-qualifier?
		      attribute-name-or-index
		      class-name)))
	      (cond
		((and (framep new-value-vector?)
		      (frame-of-class-p new-value-vector? 'value-array))
		 (change-slot-value-for-object-passing
		   new-value-vector?
		   'g2-array-length
		   resumable-vector-length))
		(t (record-object-building-problem-on-receiving-side
		     'value-array-sent-to-non-value-array-attribute
		     nil
		     nil
		     class-name)))))
	   (t
	    (record-object-building-problem-on-receiving-side
	      'value-array-sent-to-value-array-class-of-wrong-element-type
	      nil
	      nil
	      class-name))))
    (t (record-object-building-problem-on-receiving-side
	 'value-array-sent-to-non-value-array-class-definition
	 nil
	 nil
	 class-name))))

;; ... get object-passing-clears-g2-list-p reviewed!
(defun object-passing-clears-g2-list-p (g2-list)
  (declare (ignore g2-list))
  t)

(defun-void g2-receive-add-attribute-object-list
    (attribute-type
      attribute-qualifier?
      attribute-name-or-index
      class-name 
      symbolic-attribute-count
      resumable-list-length)
  (declare (ignore symbolic-attribute-count resumable-list-length))
  (cond
    ((or (subclassp class-name 'item-list)
	 (and (subclassp class-name 'g2-list)
	      (not (subclassp class-name 'value-list))))
     (let ((new-object-list?
	     (g2-build-remote-object
	       attribute-type
	       attribute-qualifier?
	       attribute-name-or-index
	       class-name)))
       (cond
	 ((and (framep new-object-list?)
	       (or (frame-of-class-p new-object-list? 'item-list)
		   (and (frame-of-class-p new-object-list? 'g2-list)
			(not (frame-of-class-p
			       new-object-list?
			       'value-list)))))
	  (when (object-passing-clears-g2-list-p new-object-list?)
	    (clear-g2-list new-object-list?)))
	 (t (record-object-building-problem-on-receiving-side
	      'item-list-sent-to-non-item-list-attribute
	      nil
	      nil
	      class-name)))))
    (t (record-object-building-problem-on-receiving-side
	 'item-list-sent-to-non-item-list-class-definition
	 nil
	 nil
	 class-name))))

(defun-simple list-element-type-for-class (class-name)
  (let ((element-type (slot-init-form (slot-description-from-class class-name 'list-type))))
    (case element-type
      (datum 'value)
      (item-or-datum 'item-or-value)
      (number 'quantity)
      (t element-type))))	  

(defun-void g2-receive-add-attribute-value-list
    (attribute-type
      attribute-qualifier?
      attribute-name-or-index
      class-name
      symbolic-attribute-count
      element-type
      resumable-list-length)
  (declare (ignore symbolic-attribute-count
		   resumable-list-length))
  (cond
    ((subclassp class-name 'value-list)
     (cond
       ((array-or-list-element-type-suitable-p
	  (or element-type 'value)
	  (list-element-type-for-class class-name))
	(let ((new-value-list?
		(g2-build-remote-object
		  attribute-type
		  attribute-qualifier?
		  attribute-name-or-index
		  class-name)))
	  (cond
	    ((and (framep new-value-list?)
		  (frame-of-class-p new-value-list? 'value-list))
	     (when (object-passing-clears-g2-list-p new-value-list?)
	       (clear-g2-list new-value-list?)))
	    (t (record-object-building-problem-on-receiving-side
		 'value-list-sent-to-non-value-list-attribute
		 nil 
		 nil 
		 class-name)))))
       (t
	(record-object-building-problem-on-receiving-side
	  'value-list-sent-to-value-list-class-of-wrong-element-type
	  nil 
	  nil 
	  class-name))))
    (t (record-object-building-problem-on-receiving-side
	 'value-list-sent-to-non-value-list-class-definition
	 nil
	 nil
	 class-name))))

(defmacro loop-with-or-without (with-or-without-form &rest loop-forms)
  (let ((with-branch nil)
	(without-branch nil))
    (loop for loop-form in loop-forms
	  with with-branch-only-p = nil
	  do
      (cond
	;; Superfluous escapes de-confuse Emacs delimiter balancing.
	((eql loop-form '\[ ) (setq with-branch-only-p t))
	((eql loop-form '\] ) (setq with-branch-only-p nil))
	(t
	 (unless with-branch-only-p
	    (push loop-form without-branch))
	 (push loop-form with-branch))))
    (if (constantp with-or-without-form)
	(if (eval with-or-without-form)
	    `(loop ,@(reverse with-branch))
	    `(loop ,@(reverse without-branch)))
	`(if ,with-or-without-form
	     (loop ,@(reverse with-branch))
	     (loop ,@(reverse without-branch))))))

(def-substitution-macro reclaim-unprocessed-interning-details-if-any
    (interning-details?)
  (when interning-details?
    #+development
    (cerror "Continue, but this is an unexpected leak"
	    "RECLAIM-UNPROCESSED-INTERNING-DETAILS-IF-ANY:~%~
               interning details were ~s, not nil"
	    interning-details?)
    (reclaim-icp-tree interning-details?)))

(defun-void g2-send-add-value-vector-range
    (number-of-elements resumable-node interning-details?)
  (let ((highest-index (highest-empty-value-vector-index resumable-node)))
    (write-icp-fixnum number-of-elements)
    (write-icp-fixnum highest-index)
    (loop-with-or-without interning-details?
          with internal-vector
	  = (internal-vector-for-object-passing resumable-node)
	  repeat number-of-elements
	  for vector-index downfrom highest-index
	  for element = (value-array-passing-aref internal-vector vector-index)
	  with corresponding-index? = nil 
	  [ with next-interning-index? = (caar interning-details?) ]
	  [ if (and next-interning-index?
		    (=f next-interning-index? vector-index))
            do
	      (progn (setq corresponding-index? (cdar interning-details?))
		     (reclaim-icp-cons (icp-pop interning-details?))
		     (setq next-interning-index? (caar interning-details?)))
	    else
	      (setq corresponding-index? nil) ]
	    do
      (write-icp-attribute-value
	element
	corresponding-index?)
      (decff (highest-empty-value-vector-index resumable-node)))
    (reclaim-unprocessed-interning-details-if-any interning-details?)))

;;; We don't need a frame-has-been-reprocessed-p check before each time we start
;;; mutating a g2-array or g2-list, because, in the current design of G2
;;; (2/13/94), it is not possible for a user to delete a subframe.  So the check
;;; we do against the toplevel frame being reprocessed is sufficient.

(defmacro bind-for-vector-range-if-possible
    ((current-subobject?-var) &body body)
  (unless (symbolp current-subobject?-var)
    (error "BIND-FOR-VECTOR-RANGE-IF-POSSIBLE: ~
            current-subobject?-var should be a symbol, not ~s"
	   current-subobject?-var))
  `(let ((,current-subobject?-var
	    (current-resumable-subobject-being-built?
	      current-receiving-resumable-object)))
     (cond
       ((framep ,current-subobject?-var) ;may have been deleted!
	(let ((value-array-p
		(frame-of-class-p ,current-subobject?-var 'value-array)))
	  (cond
	    ((and value-array-p
		  (>=f highest-index (g2-array-length ,current-subobject?-var)))
	     (record-object-building-problem-on-receiving-side
	       'index-out-of-bounds-for-g2-value-array
	       nil
	       highest-index
	       (class ,current-subobject?-var)))
	    (value-array-p nil)
	    (t (record-object-building-problem-on-receiving-side
		 'unexpected-non-value-array
		 nil
		 nil
		 (class ,current-subobject?-var))))))
       ((null ,current-subobject?-var)
	(record-object-building-problem-on-receiving-side
	    'premature-access-to-toplevel-g2-value-array
	    nil
	    nil
	    nil))
       (t (record-object-building-problem-on-receiving-side
	    'g2-value-array-deleted-during-object-passing
	    nil
	    nil
	    nil)))
     (when (resumable-object-ignoring-input?
	     current-receiving-resumable-object)
       (setq ,current-subobject?-var nil))
     ,@body))

(defun-void g2-receive-add-value-vector-range
    (number-of-elements highest-index)
  (bind-for-vector-range-if-possible (current-subobject?)
    (let ((internal-vector
	    (and current-subobject?
		 (get-internal-array-for-object-passing current-subobject?))))
      (if (resumable-object-ignoring-input?
	    current-receiving-resumable-object)
	  (loop repeat number-of-elements
		for index downfrom highest-index
		do
	    (read-icp-attribute-value))
	  (loop with array-element-type = (g2-array-element-type current-subobject?)
		repeat number-of-elements
		for index downfrom highest-index
		for item-or-value? = (value-array-passing-aref internal-vector index)
		for new-value = (read-icp-attribute-value)
		do
	    (cond ((type-specification-type-p new-value array-element-type)
		   (when (and item-or-value?
			      (not (frame-or-deleted-frame-p item-or-value?)))
		     (reclaim-managed-number-or-value item-or-value?))
		   (setf (value-array-passing-aref internal-vector index)
			 new-value))
		  (t
		   (reclaim-managed-number-or-value new-value)
		   (record-object-building-problem-on-receiving-side
		     'value-array-contains-an-element-inappropriate-for-receiving-array
		     nil
		     nil
		     (class current-subobject?)))))))))


(defmacro loop-with-element-type-case
    (element-type-form-with-includes-and-excludes &rest loop-forms)
  (let* ((integer-branch nil)
	 (float-branch nil)
	 (text-branch nil)
	 (truth-branch nil)
	 (symbol-branch nil)
	 (element-type-form
	   (first element-type-form-with-includes-and-excludes))
	 (includes-and-excludes
	   (rest element-type-form-with-includes-and-excludes))
	 (includes? (cdr (memq :include includes-and-excludes)))
	 (excludes? (cdr (memq :exclude includes-and-excludes))))
    (when (and excludes? includes?)
      (error "LOOP-WITH-ELEMENT-TYPE-CASE: ~
              can't have both :INCLUDE and :EXCLUDE in ~s"
	     element-type-form-with-includes-and-excludes))
    (loop for loop-form in loop-forms
	  with element-type-branch-only? = 'all
	  do
      (case loop-form
	;; Superfluous escapes de-confuse Emacs delimiter balancing.
	(\[[integer]  (setq element-type-branch-only? 'integer))
	(\[[float]    (setq element-type-branch-only? 'float))
	(\[[text]     (setq element-type-branch-only? 'text))
	(\[[truth]    (setq element-type-branch-only? 'truth))
	(\[[symbol]   (setq element-type-branch-only? 'symbol))
	(\]           (setq element-type-branch-only? 'all))
	(otherwise
	 (case element-type-branch-only?
	   (integer (push loop-form integer-branch))
	   (float   (push loop-form float-branch))
	   (text    (push loop-form text-branch))
	   (truth   (push loop-form truth-branch))
	   (symbol  (push loop-form symbol-branch))
	   (all (push loop-form integer-branch)
		(push loop-form float-branch)
		(push loop-form text-branch)
		(push loop-form truth-branch)
		(push loop-form symbol-branch))))))
    (flet ((if-expected (type branch)
	     (if (cond (includes? (memq type includes?))
		       (excludes? (not (memq type excludes?)))
		       (t t))
		 `((,type (loop ,@(reverse branch))))
		 nil)))
      `(case ,element-type-form
	 ,@(if-expected 'integer integer-branch)
	 ,@(if-expected '|float| float-branch)
	 ,@(if-expected 'text    text-branch)
	 ,@(if-expected 'truth   truth-branch)
	 ,@(if-expected 'symbol  symbol-branch)))))
	 
(defmacro float-value-array-passing-aref (float-value-array index)
  `(managed-float-aref ,float-value-array ,index))

(defun-void write-icp-add-homogeneous-float-vector-range
     (resumable-node number-of-elements highest-index)
  (with-temporary-gensym-float-creation
      write-icp-add-homogeneous-float-vector-range
    (loop with internal-vector
	  = (internal-vector-for-object-passing resumable-node)
	  repeat number-of-elements
	  for vector-index downfrom highest-index
	  do
      ;; ...  jh, 5/31/94.  Review in translated code the optimization of
      ;; passing a declared double-float to write-icp-double-float.  The intent
      ;; is for Chestnut to use the "double-float" declaration and refrain from
      ;; allocating a float box.  If things look good, we then can dispense with
      ;; the with-temporary-gensym-float-creation wrapper.
      (write-icp-double-float-1
	(float-value-array-passing-aref internal-vector vector-index))
      (decff (highest-empty-value-vector-index resumable-node)))))
  
(defun-void write-icp-add-homogeneous-non-float-vector-range
    (resumable-node
      number-of-elements
      highest-index
      element-type
      interning-details?)
  (loop-with-element-type-case (element-type :exclude |float|)
     with internal-vector
     = (internal-vector-for-object-passing resumable-node)
     repeat number-of-elements
     for vector-index downfrom highest-index
     for element = (value-array-passing-aref internal-vector vector-index)
     [[symbol]
      with next-interning-index? = (caar interning-details?) 
      for corresponding-index? = 
      (if (and next-interning-index?
	       (=f next-interning-index? vector-index))
	  (prog1 (cdar interning-details?)
	    (reclaim-icp-cons (icp-pop interning-details?))
	    (setq next-interning-index? (caar interning-details?)))
	  nil) ]
     do
     [[integer] (write-icp-fixnum element) ]
     [[text]    (write-icp-text-string element) ]
     [[truth]   (write-icp-evaluation-truth-value element) ]
     [[symbol]  (write-icp-possibly-interned-symbol
		  element
		  corresponding-index?) ]
     (decff (highest-empty-value-vector-index resumable-node)))
  (reclaim-unprocessed-interning-details-if-any interning-details?))

(defun-void read-icp-add-homogeneous-float-vector-range
    (number-of-elements highest-index internal-vector)
  ;; ...  jh, 5/31/94.  The with-temporary-gensym-float-creation may not be
  ;; necessary if Jim's macorexpander for the for a setf of managed-float-aref,
  ;; a.k.a.  (setf float-value-array-passing-aref), suppresses float boxing in
  ;; Chestnut.  Needs to be reviewed in translated code.
  (with-temporary-gensym-float-creation
      read-icp-add-homogeneous-float-vector-range
    (if (resumable-object-ignoring-input?
	  current-receiving-resumable-object)
	(loop repeat number-of-elements
	      for index downfrom highest-index
	      do (read-icp-double-float-1))
	(loop repeat number-of-elements
	      for index downfrom highest-index
	      do
	  (setf (float-value-array-passing-aref internal-vector index)
		(read-icp-double-float-1))))))

;; jh, 8/16/94.  Changed the reader for homogeneous truth-value g2-array
;; elements to read integers, because that's the way they are stored.  Oddly
;; enough, the "only" side-effect of putting a full truth-value in the array is
;; the leak of eval-conses that happens when the array is reclaimed and its
;; elements, assumed to be fixnums, are not.

(defun-void read-icp-add-homogeneous-non-float-vector-range
    (number-of-elements highest-index internal-vector element-type)
  (if (resumable-object-ignoring-input? current-receiving-resumable-object)
      (loop-with-element-type-case (element-type :exclude |float|)
        repeat number-of-elements
	for index downfrom highest-index
	do
	[[integer] (read-icp-fixnum) ]
	[[text]    (reclaim-text-string (read-icp-text-string)) ]
	[[truth]   (read-icp-integer) ] ;; yes, integer (see above 8/16/94 note)
	[[symbol]  (read-icp-possibly-interned-symbol) ]
	)
      (loop-with-element-type-case (element-type :exclude |float|)
        repeat number-of-elements
	for index downfrom highest-index
	for element =
	[[integer] (read-icp-fixnum) ]
	[[text]    (prog1 (read-icp-text-string)
		     (reclaim-if-text-string
		       (value-array-passing-aref internal-vector index))) ]
	[[truth]   (read-icp-integer) ] ;; yes, integer (see above 8/16/94 note)
	[[symbol]  (read-icp-possibly-interned-symbol) ]
	do
	(setf (value-array-passing-aref internal-vector index)
	      element))))

(defun-void g2-send-add-homogeneous-value-vector-range
    (number-of-elements element-type resumable-node interning-details?)
  (let ((highest-index (highest-empty-value-vector-index resumable-node)))
    (write-icp-fixnum number-of-elements)
    (write-icp-resumable-sequence-element-type element-type)
    (write-icp-fixnum highest-index)
    (if (eq element-type '|float|)
	(write-icp-add-homogeneous-float-vector-range
	  resumable-node
	  number-of-elements
	  highest-index)
	(write-icp-add-homogeneous-non-float-vector-range
	  resumable-node
	  number-of-elements
	  highest-index
	  element-type
	  interning-details?))))

(defun-void g2-receive-add-homogeneous-value-vector-range
    (number-of-elements element-type highest-index)
  (bind-for-vector-range-if-possible (current-subobject?)
    (let ((internal-vector
	    (and current-subobject?
		 (get-internal-array-for-object-passing current-subobject?))))
      (if (eq element-type '|float|)
	  (read-icp-add-homogeneous-float-vector-range
	    number-of-elements
	    highest-index
	    internal-vector)
	  (read-icp-add-homogeneous-non-float-vector-range
	    number-of-elements
	    highest-index
	    internal-vector
	    element-type)))))

;; End file with [CR]


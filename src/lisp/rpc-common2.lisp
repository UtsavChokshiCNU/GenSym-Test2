;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module RPC-COMMON2

;;; Copyright (c) 1987, 1988, 1989, 1990, 1991, 1992, 1993, 1994 Gensym
;;; Corporation.  All Rights Reserved.

;;; John Hodgkinson and Peter Fandel.

;;; This module implements object- and array-passing via remote procedure calls
;;; for G2 and GSI.

;; jh, 3/16/94.  Changed name of this module from RPC-OBJ to RPC-COMMON2.





;;;; Table of Contents

;;; [1]       Overview
;;; [1.1]     Exception Handling
;;; [1.2]     Reclamation
;;; [1.3]     To Do
;;; [1.3.1]     Features
;;; [1.3.2]     Bugs
;;; [1.3.3]     Tests
;;; [1.3.4]     Documentation
;;; [1.3.5]     Review
;;; [1.3.6]     Performance Issues
;;; [1.3.7]     Wishes
;;; [1.3.8]     Clarity
;;; [1.3.9]     Style

;;; [2]       Forward References
;;; [3]       Testing Switch
;;; [4]       ICP Message Type Codes
;;; [5]        Data Structures for Resumable Object Contents

;;; [6]       Data Structures for RPC Object Arguments
;;; [6.2]       RPC Object Argument Commonality
;;; [6.4]       Receiving Side RPC Object Arguments
;;; [6.4.1]       Current Receiving RPC Object Argument
;;; [6.4.2]       Receiving RPC Object-building Problems
;;; [6.4.3]       Receiving Side RPC Object Container Structure

;;; [7]       RPC Argument Lists That Contain Objects
;;; [7.1]       ICP Object Types to Support Objects in RPC Argument Lists
;;; [7.2]       RPC Argument List Container Structure

;;; [8]       Reclaimers for RPC Object Arguments and Argument Lists
;;; [11]      ICP Writer and Reader for RPC Object Argument
;;; [12]      ICP Writer and Reader for RPC Argument List

;;; [14]      Resumable Object Portion
;;; [14.1]      ICP Tag Groups
;;; [14.2]      ICP Value Protocol
;;; [14.2.1]      Defining ICP Value Protocols
;;; [14.2.2]      Reading in ICP Value Protocols
;;; [14.3]      ICP Value Protocols for Resumable Objects
;;; [14.3.1]      Protocol for Possibly Interned Symbols
;;; [14.3.2]      Attribute Spec Protocol
;;; [14.3.3]      Attribute Value Protocol
;;; [14.3.4]      Resumable Node Protocols
;;; [14.3.4.1]      Leaf Protocols
;;; [14.3.4.2]      Resumable Object Protocols
;;; [14.3.5]      RPC Argument Protocols
;;; [14.4]      ICP Reader and Writer for Resumable Object Portion

;;; [16]      ICP Message to Build Resumable Objects
;;; [17]      New RPC-related ICP messages
;;; [17.1]    Object-passing ICP messages
;;; [17.2]    Item-registration ICP messages




;;;; [1] Overview

;;; In G2 and GSI versions 3.0 and earlier, remote procedure calls (RPCs) were
;;; limited to accepting values (integers, floats, and the like) as argument and
;;; return types.  This module extends the functionality of remote procedure
;;; calls in G2 and GSI to accept "objects" as arguments and return types.  The
;;; general name for this process is `object passing' or `object-passing'.  The
;;; term `object and array passing' is sometimes used to emphasize the fact that
;;; both "things with attributes" and "things with indexes" may now be given to
;;; RPCs.

;; jh, 6/10/94.  Suggest "remote procedure execution (a.k.a. RPE) as an umbrella
;; to cover both calls and starts.

;;; We place scare quotes around "object" because this term means something
;;; different in G2 than it does in GSI.  In either product, however, an `RPC
;;; object' is a data structure that can be passed to an RPC or received as the
;;; returned result of an RPC.  Although the underlying data structure looks
;;; different between G2 and GSI, much of the following discussion can abstract
;;; away from the product that is executing the RPC.  Since the same data
;;; structure serves both as an RPC argument list and an RPC return list, many
;;; times we can even abstract away from the process that originated the RPC.

;;; In G2, an RPC object is more or less identical with "an instance of class
;;; object", although references to non-object items may be passed (see the
;;; discussion of object passing "as handle" below).

;;; In GSI, an RPC object is a structure that the GSI developer accesses through
;;; API functions.  Since GSI lacks the G2 class system, this structure has
;;; little functionality beyond that of a C struct (i.e., a record with named
;;; fields, possibly containing other such records).  GSI does not implement RPC
;;; objects as C structs, and the GSI developer can only access them through API
;;; functions, but the imagery of a simple C struct is a useful conceptual tool.

;;; In both G2 and GSI, an RPC object may have substructure that must be
;;; traversed in order to send or receive the entire object.  This substructure
;;; can be another RPC object or it can be a value.  We may say `RPC value' to
;;; emphasize that a value is being used in an RPC.  RPC values are implemented
;;; as evaluation-values of type evaluation-integer, evaluation-float,
;;; evaluation-text, evaluation-truth-value, or evaluation-symbol.

;;; An `object-passing attribute spec' describes how to access the immediate
;;; substructure of an RPC object.  It expresses the commonality between
;;; symbolic attributes and enclosed lists or arrays.  This substructure is
;;; called the `RPC subobject' of the its `enclosing RPC object'.  Keep in mind
;;; the caveat that a "subobject" may be an RPC value rather than an actual
;;; object.  Another name for enclosing RPC object is `parent RPC object'.

;;; As far as object-passing is concerned, an RPC subobject may be accessed from
;;; its enclosing RPC object in one of three ways: as an `object-passing
;;; attribute name', by an `object-passing vector index', or by an
;;; `object-passing list index'.  (Note that in the case of lists, the term
;;; "index" does not imply that the list is somehow random access.)  The
;;; enclosed RPC subobject is called, respectively, the `object-passing
;;; attribute', the `object-passing vector element', or the `object-passing list
;;; element'.

;;; In the discussion that follows, the `sending side' is the process that wants
;;; to transmit an RPC object across ICP, and the `receiving side' is the
;;; intended destination for that object.  This relationship can happen either
;;; when the sending side wants to call a procedure on the receiving side, or
;;; when the sending side is returning results from one of its procedures to the
;;; receiving side.

;;; Since some RPC objects (those that are not RPC values) can consume an
;;; aribtrarily large amount of memory, RPC objects cannot in general be sent in
;;; a single ICP message.  A `resumable node' is a data structure that stores
;;; the state needed to suspend and resume the task of object passing.  This
;;; structure contains an object-passing attribute spec and a pointer to a
;;; resumable node representing the parent RPC object (if there is one), along
;;; with other information specific to the type of RPC object.  The resumable
;;; node is also a convenient place to store information that allows us to
;;; verify that the RPC object is still "valid" after object-passing resumes.

;;; The complete RPC object is represented by a `resumable node tree'.  Multiple
;;; references to the same RPC object are represented as distinct resumable
;;; nodes, so such a structure is never more complex than a tree.

;;; Note that resumable nodes are created on the sending side, because on the
;;; receiving side we can take advantage of the ICP processing mechanism to do
;;; the scheduling necessary to recreate an RPC object in resumable tasks.

;;; If there is no enclosing RPC object for a given RPC object, we call it a
;;; `toplevel RPC object' and its associated resumable node a `toplevel
;;; resumable node'.

;;; Object-passing can be broken down into three phases: `object-passing
;;; preflight', `object-passing transmission', and `object building'.  The first
;;; two phases occur on the sending side; the final phase occurs on the
;;; receiving side.  The two sending side phases are collectively called
;;; `object-passing tasks', since in G2 they are suspended and resumed by the
;;; scheduler.

;;; No transactional guarantees are in effect if an object-passing task has to
;;; suspend and then resume.  If the user on the sending side mutates an RPC
;;; object between object-passing tasks, results vary from "best guess behavior"
;;; to an abort of the entire RPC.  We are safer on the receiving side: the user
;;; there has limited access to the RPC object until it reaches the RPC or the
;;; site wanting the return list from the RPC.

;; jh, 9/8/94. Changed "no access" to "limited access" because the receiving
;; side can delete an object being built using a "delete any xxx" action.

;;; Object-passing preflight traverses the RPC object, creating a resumable-node
;;; structure for each RPC subobject.  This phase checks for circularity, and
;;; accumulates attribute specs, class names, validity information, and the
;;; like.  Provision is made for preflighting tasks to suspend when the
;;; scheduler timeslice has expired.

;;; Object-passing transmission sends the RPC object to the remote side, after
;;; first detrmining that there is sufficient network bandwidth (i.e., that
;;; enough previous object-passing tasks have completed -- there is currently no
;;; global "push-back" in place).  If the network lacks bandwidth, or if the
;;; scheduler timeslice has expired, the transmission task is suspended.

;;; Object-building recreates the RPC object on the receiving side.  This is
;;; done through the ICP message handling mechanism, enhanced to allow for more
;;; complicated ICP value reader and writer protocols than usual.  Checks are
;;; made for that a "valid" object can be created (for example, that the given
;;; attribute spec is valid for the given class).  If these checks fail, every
;;; effort is made to continue reading (and discarding input) until it it is
;;; "safe" for the receiving side to notify the sending side and stop building
;;; the object.

;;; Each argument to an object-passing RPC, and each result from an
;;; object-passing RPC, is managed by a `resumable object'.  A resumable object
;;; contains links to the other RPC objects in the given RPC that have not yet
;;; finished building their own RPC objects.  When a resumable object has
;;; finished building an RPC object on the receiving side, it checks its links
;;; to see if there are any other unfinished RPC objects.  If so, it splices
;;; itself out of the list of unfinished resumable objects.  If not, the
;;; argument list or result list of the RPC is complete and can be passed to the
;;; appropriate continuation.

;;; An argument to an object-passing RPC may also be sent as a `handled RPC
;;; object', that is, as a corresponding ICP object index that allows multiple
;;; references to the RPC object on the sending side, without the necessity for
;;; multiple object-building.

;;;; [1.1] Exception Handling

;;; normal sending:
;;; --------------
;;; <1s> check argument types
;;; <2s> create resumable object
;;; <3s> send resumable object index
;;; <4s> begin preflighting each object arg
;;; <5s> finish preflighting
;;; <6s> begin transmitting each resumable object
;;; <7s> finish transmitting
;;; <8s> release clogged objects
;;; <9s> release corresponding indexes

;;; normal receiving:
;;; ----------------
;;; <1r> get resumable object index
;;; <2r> create resumable object
;;; <3r> do each object building task
;;; <4r> resume RPC after final object arg is received
;;; <5r> resume RPCs for incomplete handled objects
;;; <6r> release corresponding indices
;;; <7r> tell sender to release indices

;;; sending exceptions:
;;; ------------------
;;; error during arg check or marshalling
;;; error during preflight
;;; RPC uses handle before object is built
;;; deactivates remote procedure declaration
;;; starter or caller of RPC is aborted (incl KB reset?)
;;; RPC denied because of network restrictions?
;;; clogged objects persist after RPC is aborted

;;; receiving exceptions:
;;; --------------------
;;; error during building (e.g. inappropriate class)
;;; sibling object args being sent as handle but incomplete
;;; receiver resets KB
;;; sender aborts RPC
;;; deferred handled object persist after RPC is aborted
;;; resumable objects persist after RPC is aborted

;;;; [1.2]     Reclamation

;;; As far as possible, all reclamation is handled at the level of the
;;; individual objects that are RPC arguments.  If a problem occurs during the
;;; transmission or building of an individual resumable object, that object is
;;; responsible to reclaiming all memory for the other resumable objects in the
;;; argument or result list list of the RPC being executed.

;;; On the sending side ...

;;; Additional memory allocation happens on the sending side when RPC object
;;; arguments encounter a clogged network.  These are stored in a list ...

;;; On the receiving side ...

;;;; [1.3] To Do

;;; 6/13/94

;; [1.3.1] Features
;;   system-attributes
;;     name
;;     current variable or parameter value
;;     variable or parameter history
;;     add other system attributes for 4.1
;;       use those that are permissible in "change the text"?
;;     extend grammar so that system attribute may be excluded or excluded
;;   review item-or-value array (may not be subsumed under item-array behavior)

;; [1.3.2] Bugs
;;   zero-length lists crash
;;   object-building problems fail to signal stack error
;;   heed ghw's request that change-slot-value observe declared types
;;   ml's object-passing during pause bug
;;   vet "call pass-object(obj); delete obj;" for intuitive behavior
;;   empty lists (and possibly other seqs) think that an elt has been deleted
;;   see if paf item-list kb still buggy
;;   move G2-specific machinery out of RPC-COMMON2.  This is considered a bug
;;     because certain GSI stubs (macros and perhaps setf methods) can overwrite
;;     the G2 functionality.

;; [1.3.3] Tests
;;   handle-related sysprocs
;;     test transform from handle to object for arguments as well as results
;;   excludes and excludes
;;     test that remote procedure result spec can exclude and include atts
;;       (similar to how args do it)
;;     test class-qualified attributes here and in general
;;   check for leaks after each ws test in /home/jh/object-passing-4-0-04.kb
;;   make regression test out of /home/jh/object-passing-4-0-09.kb

;; [1.3.4] Documentation
;;   exception handling
;;   reclamation
;;   finish and revise "per toplevel form" doc

;; [1.3.5] review
;;   memory reclamation
;;   error handling
;;   g2 vs gsi abstraction
;;   occurrences of the string ";; ..." mark other places in the code that should
;;     be reviewed or fleshed out

;; [1.3.6] Performance Issues
;;  add defun-simples and -voids where appropriate
;;  ICP fixnums vs unsigned-integers vs corresponding-object-index value types
;;  use fixnum declarations inside loop as well as +f and friends

;; [1.3.7] Wishes
;;   incrementally add special-case "methods" for non-object item classes

;; [1.3.8] Clarity
;;   change "rpc-arglist" to "rpc-arg-or-result-list"
;;   change "read/write-icp-xxx" to "read/write-icp-xxx-for-protocol"
;;     to avoid confusion.
;;   remove "g2-" prefix from g2-only functions in g2-only modules
;;     (such a prefix only helps in shared modules)
;;   change "object" to "item" where appropriate

;; [1.3.9] Style
;;   use reschedule-task instead of the idiomatic voodoo




;;;; [2] Forward References

(declare-forward-references (:suppress-module-checks-for gsi)
  (reason-for-bad-parse-as-string                       function GRAMMAR0)
  (g2-maybe-continue-rpc-after-object-building          function G2-RPC3)
  (g2-reclaim-sending-resumable-object                  function G2-RPC2)
  (rpc-object-handed-off-to-user-p                      function G2-RPC2)
  (g2-add-leaf-to-remote-object                         function G2-RPC2)
  (g2-build-remote-object                               function G2-RPC2)
  (g2-add-resumable-circularity                         function G2-RPC2)
  (add-history-spec-for-object-passing                  function G2-RPC2)
  (make-cascaded-ring-buffer-for-history-object-passing function G2-RPC2)
  (g2-transmit-add-history-range                        function G2-RPC2)
  (g2-receive-add-history-range                         function G2-RPC2)
  (g2-transmit-add-homogeneous-history-range            function G2-RPC2)
  (g2-receive-add-homogeneous-history-range             function G2-RPC2)
  (g2-ascend-to-parent                                  function G2-RPC2)
  (send-icp-update-object-passing-network-resources     function G2-RPC2)
  (check-that-remote-procedure-can-receive-values       function G2-RPC2)
  (g2-write-icp-attribute-value                         function G2-RPC2)
  (g2-write-history-timestamp                           function G2-RPC2)
  (g2-send-add-value-vector-range                       function G2-RPC2)
  (g2-send-add-homogeneous-value-vector-range           function G2-RPC2)
  (g2-receive-add-value-vector-range                    function G2-RPC2)
  (g2-receive-add-homogeneous-value-vector-range        function G2-RPC2)
  (g2-send-add-value-list-range                         function G2-RPC2)
  (g2-receive-add-value-list-range                      function G2-RPC2)
  (g2-send-add-homogeneous-value-list-range             function G2-RPC2)
  (g2-receive-add-homogeneous-value-list-range          function G2-RPC2)
  (g2-read-icp-attribute-for-list-of-attributes         function G2-RPC2)
  (g2-reclaim-single-receiving-resumable-object         function G2-RPC2)
  (g2-write-icp-list-of-attributes                      function G2-RPC2)
  (g2-resumable-object-reprocessed-p                    function G2-RPC2)
  (g2-receive-add-attribute-object-vector               function G2-RPC2)
  (g2-receive-add-attribute-value-vector                function G2-RPC2)
  (g2-receive-add-attribute-history-object              function G2-RPC2)
  (g2-receive-add-attribute-object-list                 function G2-RPC2)
  (g2-receive-add-attribute-value-list                  function G2-RPC2)
  (g2-resume-clogged-resumable-object-tasks             function G2-RPC2)
  (reclaim-evaluation-value-if-any-function             function G2-RPC2)
  (g2-write-icp-rpc-value-or-object                     function G2-RPC2)
  (check-that-remote-procedure-can-be-started-or-called function G2-RPC1)
  (receive-start-or-call-remote-procedure               function G2-RPC1)
  (receive-remote-procedure-values                      function G2-RPC1)
  (receive-remote-procedure-error                       function G2-RPC1)
  (receive-remote-procedure-error-for-caller            function G2-RPC1)
  (plausible-remote-method-call-p                       function G2-RPC1)
  (rpc-argument-list-error                              variable RPC-COMMON3)
  )

(declare-forward-references (:suppress-module-checks-for ab)
  (get-item-from-arguments                        function)
  (gsi-build-item-instance                        function)
  (gsi-add-leaf-to-item-instance                  function)
  (gsi-receive-add-history-range                  function)
  (gsi-receive-add-homogeneous-history-range      function)
  (gsi-type-from-leaf-type                        function)
  (gsi-type-from-g2-element-type                  function)
  (gsi-array-type-from-g2-element-type            function)
  (gsi-list-type-from-g2-element-type             function)
  (gsi-add-resumable-circularity                  function)
  (gsi-send-item                                  function)
  (gsi-preflight-item                             function)
  (gsi-prepare-for-recursive-descent              function)
  (gsi-check-if-all-items-are-built               function)
  (simple-text-string-copy-from-attribute-name    function)
  (gsi-warning                                    function)
  (gsi-incompatible-structure                     variable)
  (gsi-incompatible-type			  variable)
  (gsi-incorrect-argument-count                   variable)
  (gsi-rpc-error-from-g2                          variable)
  (gsi-rpc-error-from-g2-procedure                variable)
  (gsi-unknown-calling-procedure-index            variable)
  (gsi-start-or-call-local-function-or-handle-return-values function)
  (make-gsi-instance                              function)
  (make-gsi-history                               function)
  (gsi-reclaim-contents                           function)
  (gsi-option-is-set-p                            function)
  )



;;;; [3] Testing Switch

#+development
(defvar debug-object-passing-p nil)

(defmacro debug-object-passing (format-string &rest format-args)
  (if (eval-feature :development)
      `(when debug-object-passing-p
	 (format t
	   ,(concatenate 'string "~&" format-string "~%")
	   ,@format-args))
      nil))




;;;; [4] ICP Message Type Codes (see int1.lisp)


;;;; [5] Data Structures for Resumable Object Contents

;;; The `resumable-attribute-spec' structure represents an object-passing
;;; attribute spec, that is, provides details on how the given RPC subobject may
;;; be reached from its enclosing RPC object.  The term "resumable" is related
;;; to the term "resumable node" and indicates that this structure is used to
;;; help make object-passing a scheduled task. This structure is only used on
;;; the sending side.

;;; The `resumable-attribute-type' slot of the resumable-attribute-spec
;;; structure contains a symbol naming the type of access, either
;;; 'symbolic-attribute, 'system-attribute', 'vector-element, or 'list-element.
;;; If the resumable-attribute-type slot is symbolic or system, the slots
;;; resumable-attribute-unique-name, resumable-attribute-class-qualifier?,
;;; resumable-attribute-base-name, resumable-qualifier-corresponding-index?, and
;;; resumable-base-name-corresponding-index?  pertain.  If the
;;; resumable-attribute-type slot is one of 'vector-element or 'list-element,
;;; the slot resumable-vector-or-list-index pertains.

;;; The `resumable-attribute-corresponding-index?' slot of the
;;; resumable-attribute-spec structure contains the corresponding ICP object
;;; index of the object-passing attribute name, considered as an ICP object of
;;; type symbol relative to the ICP socket through which the RPC is being
;;; conducted.  If there is no such symbol (for example, if the RPC subobject is
;;; a vector element or if the symbol has not yet been interned relative to the
;;; given ICP socket), this slot will contain nil.

;;; The `resumable-vector-or-list-index' slot of the resumable-attribute-spec
;;; structure contains a fixnum that is a zero-based index of the RPC subobject
;;; when its enclosing RPC object is a list or array.  If the enclosing RPC
;;; object is a vector, the attribute spec describes an `object-passing vector
;;; element'; if the enclosing object is a list, the attribute spec describes an
;;; `object-passing list element'.

;;; The substitution macro `reclaim-resumable-attribute-spec-if-any' takes a its
;;; single argument.  If the argument is non-nil, it should be a
;;; resumable-attribute-spec structure, which this function reclaims.

(defmacro reclaim-resumable-attribute-spec (resumable-attribute-spec)
  `(reclaim-gensym-list ,resumable-attribute-spec))

(defmacro resumable-attribute-spec-p (resumable-attribute-spec)
  `(consp ,resumable-attribute-spec))

(def-substitution-macro reclaim-resumable-attribute-spec-if-any
    (resumable-attribute-spec?)
  (when (resumable-attribute-spec-p resumable-attribute-spec?)
    (reclaim-resumable-attribute-spec resumable-attribute-spec?)))

(defun-simple reclaim-resumable-attribute-spec-function (x)
  (reclaim-resumable-attribute-spec-if-any x))

(defun-simple reclaim-resumable-attribute-spec-if-any-function (x)
  (reclaim-resumable-attribute-spec-if-any x))

;;; The substitution macro `make-resumable-attribute-name' returns a new
;;; resumable-attribute-spec that represents an object-passing attribute name.

(defmacro make-resumable-attribute-name
    (&optional resumable-attribute-class-qualifier? resumable-attribute-base-name)
  `(gensym-list 'attribute ,resumable-attribute-class-qualifier? ,resumable-attribute-base-name))

;;; The substitution macro `make-resumable-vector-index' takes as its single
;;; argument, an index into an RPC object that is a vector, and returns a new
;;; resumable-attribute-spec structure that represents an object-passing vector
;;; index.

(defmacro make-resumable-vector-index (&optional index)
  `(gensym-list 'vector-element ,index))

;;; The substitution macro `make-resumable-list-index' takes as its single
;;; argument, an index into an RPC object that is a vector, and returns a new
;;; resumable-attribute-spec structure that represents an object-passing list
;;; index.

(defmacro make-resumable-list-index (&optional index)
  `(gensym-list 'list-element ,index))

(defmacro resumable-attribute-type (resumable-attribute-spec)
  (avoiding-variable-capture (resumable-attribute-spec)
    `(cond ((fixnump ,resumable-attribute-spec)
	    'vector-element)
	   ((symbolp ,resumable-attribute-spec)
	    'attribute)
	   ((consp ,resumable-attribute-spec)
	    (let ((type (car-of-cons ,resumable-attribute-spec)))
	      (if (eq type 'class-qualified-name)
		  'attribute
		  type))))))

(defun set-resumable-attribute-type (resumable-attribute-spec value)
  (when (and (consp resumable-attribute-spec)
	     (not (eq (car-of-cons resumable-attribute-spec) 'class-qualified-name)))
    (setf (car resumable-attribute-spec) value)))

(defsetf resumable-attribute-type set-resumable-attribute-type)

(defmacro resumable-vector-or-list-index (resumable-attribute-spec)
  (avoiding-variable-capture (resumable-attribute-spec)
    `(cond ((fixnump ,resumable-attribute-spec)
	    ,resumable-attribute-spec)
	   (t
	    (second ,resumable-attribute-spec)))))

(defmacro set-resumable-vector-or-list-index (resumable-attribute-spec value)
  `(setf (second ,resumable-attribute-spec) ,value))

(defsetf resumable-vector-or-list-index set-resumable-vector-or-list-index)

(defmacro resumable-attribute-base-name (resumable-attribute-spec)
  (avoiding-variable-capture (resumable-attribute-spec)
    `(cond ((consp ,resumable-attribute-spec)
	    (third ,resumable-attribute-spec))
	   (t
	    ,resumable-attribute-spec))))

(defmacro set-resumable-attribute-base-name (resumable-attribute-spec value)
  `(setf (third ,resumable-attribute-spec) ,value))

(defsetf resumable-attribute-base-name set-resumable-attribute-base-name)

(defmacro resumable-attribute-class-qualifier? (resumable-attribute-spec)
  (avoiding-variable-capture (resumable-attribute-spec)
    `(if (consp ,resumable-attribute-spec)
	 (second ,resumable-attribute-spec)
	 nil)))

(defmacro set-resumable-attribute-class-qualifier? (resumable-attribute-spec value)
  `(setf (second ,resumable-attribute-spec) ,value))

(defsetf resumable-attribute-class-qualifier? set-resumable-attribute-class-qualifier?)






;;;; [6] Data Structures for RPC Object Arguments

;;;; [6.2] RPC Object Argument Commonality

;;; Unless the side-comment mentions "share", the contents must be reclaimed.

;;; The `resumable-object-mixin' structure manages the information associated
;;; with a single RPC object, either an argument to an RPC or a result returned
;;; from an RPC.  This structure contains the commonality between resumable
;;; objects on the sending side and on the receiving side.  This structure
;;; itself is never instantiated.

;;; The `resumable-object-rpc-name?' slot of a resumable-object-mixin structure
;;; is a symbol naming the RPC in progress.

;;; The `next-resumable-object-in-rpc-arglist?' and
;;; `previous-resumable-object-in-rpc-arglist?'  slots in a
;;; resumable-object-mixin structure are forward and reversse links to the other
;;; RPC objects involved in the given RPC.

(def-structure resumable-object-mixin
  (resumable-object-rpc-name? nil)                ;a symbol or nil
  transmit-resumable-object-as-handle-p           ;a boolean
  (next-resumable-object-in-rpc-arglist? nil)     ;resumable-object structure or nil
  (previous-resumable-object-in-rpc-arglist? nil) ;resumable-object structure or nil
  (rpc-identifier-for-this-object? nil)           ;shared rpc-identifier or nil
  (resumable-object-reference-serial-number nil)
  )

;;; The `icp-object-map-for-resumable-object' slot of a
;;; resumable-icp-object-mixin structure contains an ICP object map for the ICP
;;; object type resumable-object.  When an object-passing task resumes, this map
;;; provides a corresponding ICP object index that can be used to refer to the
;;; RPC object under construction on the receiving side.

;;; Note that the :reclaimer for the icp-object-map-for-resumable-object slot is
;;; reclaim-gensym-list, not reclaim-icp-object-map-for-corresponding-object.
;;; This is because the receiving side may still be using this index for its
;;; object-building task, and so the sending side may not reuse this index until
;;; the receiving side is finished with it.  So we reclaim the list here and
;;; wait until the handler for update-object-passing-network-resources to remove
;;; the index from its index space.

(def-structure (resumable-icp-object-mixin
		 (:include resumable-object-mixin))
  (icp-object-map-for-resumable-object nil      ;managed by ICP
    :reclaimer
    reclaim-gensym-list))		 




;;; The `resumable-node-mixin' structure contains the information common to all
;;; resumable nodes.  Only structures that :include this structure are ever
;;; instantiated.  This structure is only usd on the sending side.

;;; The `resumable-node-parent-node?' slot of a resumable-node-mixin structure
;;; contains a resumable-node-mixin structure representing the enclosing RPC
;;; object of the given RPC object.  If this slot is nil, this
;;; resumable-node-mixin structure is a toplevel resumable node; otherwise, it
;;; represents some RPC subobject.

;;; The `resumable-attribute-spec?' slot of a resumable-node-mixin contains a
;;; resumable-attribute-spec structure or nil.  If this slot is nil, this
;;; resumable-node-mixin structure is a toplevel resumable node; otherwise it
;;; represents some RPC subobject.

(def-structure resumable-node-mixin
  (resumable-node-parent-node? nil)  ;shared resumable-node-mixin structure or nil
  (resumable-attribute-spec? nil     ;a resumable-attribute-spec structure or nil
   :reclaimer
   reclaim-resumable-attribute-spec-if-any)
  )

;;; The `icp-object-map-for-resumable-instance-node' slot of a
;;; resumable-icp-node-mixin structure contains an ICP object map for the ICP
;;; object type resumable-node.  The index from this map is the same as that
;;; stored in the resumable-circular-corresponding-icp-index slot of any
;;; resumable-circular-nodes corresponding to this resumable node.  This map is
;;; reclaimed when the toplevel RPC object has finished transmission or the
;;; transmission has aborted.  Note that this map should only contain one entry,
;;; namely one for the ICP port through which the RPC is conducted and.

;;; Note that the :reclaimer for the icp-object-map-for-resumable-instance-node
;;; slot is reclaim-gensym-list, not
;;; reclaim-icp-object-map-for-corresponding-object.  This is because the
;;; receiving side may still be using this index for its object-building task,
;;; and so the sending side may not reuse this index until the receiving side is
;;; finished with it.  So we reclaim the list here and wait until the handler
;;; for update-object-passing-network-resources to remove the index from its
;;; index space.

(def-structure (resumable-icp-node-mixin
		 (:include resumable-node-mixin))
  (icp-object-map-for-resumable-instance-node nil ;managed by ICP
    :reclaimer reclaim-gensym-list))




;;;; [6.4] Receiving Side RPC Object Arguments

;;;; [6.4.1] Current Sending RPC Object Argument

(defvar current-receiving-resumable-object)



;;;; [6.4.3] Sending Side RPC Object Container Structure

;;; The `corresponding-indices-of-subobjects' slot of a
;;; receiving-resumable-object structure contains an icp-list of corresponding
;;; ICP object indices of RPC subobjects.  These indices are established in
;;; order to handle circularities in the object-passing tasks.  When the
;;; resumable-object has completely built the RPC object on the receiving side,
;;; the corresponding entries in the ICP object index space are reclaimed along
;;; with the icp-list itself.  Incidentally, the memory allocated on the sending
;;; side is reclaimed by setting up a slot reclaimer for
;;; icp-object-map-for-resumable-object in the sending-resumable-object
;;; structure.

(def-structure (receiving-resumable-object
		 (:include resumable-object-mixin)
		 (:constructor
		   make-receiving-resumable-object
		   ())
		 (:reclaimer reclaim-receiving-resumable-object-internal))
  (resumable-object-being-built? nil)                   ;G2 object or GSI struct
  (current-resumable-subobject-being-built? nil)        ;shared G2 object or GSI struct
  (enclosing-rpc-arglist-structure? nil)                ;receiving-rpc-arglist-structure
  (resumable-object-ignoring-input? nil                 ;an icp-list or nil
   :reclaimer reclaim-object-building-problem-if-any)
  corresponding-index-of-self                           ;a fixnum
  (corresponding-indices-of-subobjects nil)             ;an icp-list of fixnums
  (list-of-rpc-arglists-waiting-for-handle? nil         ;icp-list of
   :reclaimer                                           ; receiving-rpc-arglist-structures
   reclaim-icp-list-of-rpc-arglist-structures)
  (remote-g2-time-at-start? nil                         ;managed-float or nil
   :reclaimer reclaim-evaluation-value-if-any-function) 
  )



;;;; [6.4.2] Receiving RPC Object-building Problems

;;; The `object-building-problem' contains information about problems
;;; encountered during the object-building phase.  It is necessary to store this
;;; information in a structure because we could incur ICP out-of-sync errors if
;;; we simply threw to an error handler the moment we encounterd an error.

(defun reclaim-text-or-gensym-string-if-any (text-string?)
  (when text-string?
    (reclaim-text-or-gensym-string text-string?)))
  
(def-structure (object-building-problem
		 (:constructor
		   make-object-building-problem
		   (object-building-problem-name
		     object-building-problem-attribute?
		     object-building-problem-class-name?
		     object-building-problem-extra-info-format-string?
		     object-building-problem-extra-info-reclaimer?
		     object-building-problem-extra-info)))
  object-building-problem-name                        ;a symbol
  (object-building-problem-attribute? nil             ;a text-string or nil
   :reclaimer reclaim-text-or-gensym-string-if-any )
  object-building-problem-class-name?                 ;a symbol or nil
  object-building-problem-extra-info-format-string?   ;shared text string
  (object-building-problem-extra-info nil)            ;icp-list of fixnums or symbols
  object-building-problem-extra-info-reclaimer?       ;funcallable thing or nil
  )

(defun-void record-object-building-problem-on-receiving-side-1
    (problem-name
      attribute-qualifier?
      attribute-name-or-index?
      class-name
      info-format
      info-args?
      info-reclaimer?)
  (let ((old-problem?
	  (resumable-object-ignoring-input?
	    current-receiving-resumable-object)))
    ;; jh, 2/13/94.  Consider reporting every problem.  For now, protect against
    ;; leaks by reporting just the latest one.
    ;;
    ;; jh, 10/11/94.  Better to report the earliest problem, since later ones
    ;; might be spinoffs of the first error.  Note that memory may have to be
    ;; reclaimed from the problem-info? components.
    (cond
      (old-problem?
       (when info-args?
	 (loop for info-arg in info-args?
	       do (funcall info-reclaimer? info-arg))))
      
      (t (setf (resumable-object-ignoring-input?
		 current-receiving-resumable-object)
	       (let ((attribute-text
		       ;; ...			   
		       ;; jh, 2/27/94.  Consider using
		       ;; write-name-denotation-components here, although its
		       ;; abstraction is not quite right, since
		       ;; attribute-name-or-index? could be a list or array
		       ;; index as well as a symbolic attribute.
		       (cond
			 ((and attribute-qualifier? attribute-name-or-index?)
			  (tformat-text-string
			    "~(~A::~A~)"
			    attribute-qualifier?
			    attribute-name-or-index?))
			 (attribute-name-or-index?
			  (tformat-text-string 
			    "~(~A~)"
			    attribute-name-or-index?))
			 (t (tformat-text-string "top-level")))))
		 (make-object-building-problem
		   problem-name
		   attribute-text
		   class-name
		   info-format
		   info-reclaimer?
		   info-args?)))))))
  
(defmacro record-object-building-problem-on-receiving-side
    (problem-name
      attribute-qualifier?
      attribute-name-or-index?
      class-name
      &rest problem-info?)
  `(record-object-building-problem-on-receiving-side-1
     ,problem-name
     ,attribute-qualifier?
     ,attribute-name-or-index?
     ,class-name
     ,(first problem-info?)
     (icp-list ,@(rest (rest problem-info?)))
     ,(second problem-info?)))

(defun-void reclaim-object-building-problem-if-any (object-building-problem?)
  (when object-building-problem?
    (let ((info-reclaimer?
	    (object-building-problem-extra-info-reclaimer?
	      object-building-problem?)))
      (when info-reclaimer?
	(loop for extra-info-item
	      in (object-building-problem-extra-info object-building-problem?)
	      do
	  (funcall info-reclaimer? extra-info-item))))
    (reclaim-object-building-problem object-building-problem?)))




;;;; [7] RPC Argument Lists That Contain Objects

;;;; [7.1] ICP Object Types to Support Objects in RPC Argument Lists

;;; The def-icp-object-type bodies for resumable-object,
;;; resumable-instance-node, and object-passing are empty because corresponding
;;; ICP objects for these structures are created, directly or indirectly, by the
;;; ICP value writer for rpc-arglist, instead of by something like a
;;; "define-resumable-object" ICP message.

;;; We need resumable-object to be an ICP object type so we can split the
;;; sending of a G2 or GSI object into schedulable tasks that gradually build up
;;; the object on the remote side.  We need resumable-instance-node to be an ICP
;;; object so we can handle circularity in the RPC object.

;;; Since ICP object indices are generated by means other than the usual
;;; "define-xxx" messages, care must be taken to assure that an index reclaimed
;;; on one side is not in use by the other.  A case where this happens is when a
;;; resumable object on the sending side has finished its object-passing
;;; transmission task but the corresponding resumable object on the receiving
;;; side has not yet finished recreating the RPC object there.  Only when this
;;; object-building task is finished is the receiving side able to reclaim the
;;; corresponding ICP object index for the resumable object.  The
;;; update-object-passing-network-resources ICP message therefore takes
;;; additional arguments that describe which indices may be reclaimed for which
;;; ICP object types.  This message is sent by the receiving side which it has
;;; finished building the RPC object associated with the given resumable object.

;;; Corresponding ICP object indices are also used to represent the symbols for
;;; class names and attribute names, but no extraordinary measures are taken to
;;; reclaim these indices.  They therefore persist until their associated ICP
;;; socket is shut down.  This has a tradeoff similar to that of interning
;;; symbols locally: the memory allocated by the intern may not be reclaimed,
;;; but subsequent access of interned symbols is quicker.

(defun reclaim-resumable-object (resumable-object icp-port)
  (case (icp-port-direction icp-port)
    (output (g2-reclaim-sending-resumable-object resumable-object))
    (input (reclaim-single-receiving-resumable-object resumable-object))))

(def-icp-object-type resumable-object
    (standard-icp-object-index-space
      (icp-object-map-for-resumable-object
	resumable-object)
      reclaim-resumable-object)
  resumable-object)

(def-icp-object-type resumable-instance-node
    (standard-icp-object-index-space
      (icp-object-map-for-resumable-instance-node
	resumable-instance-node))
  resumable-instance-node)




;;;; [7.2] RPC Argument List Container Structure

;;; No sending-rpc-arglist-structure is needed, because each RPC object argument
;;; on the sending side is associated with a separate task that undertakes to
;;; build the object on the remote side.  When the last such task is finished,
;;; rpc-arglist-being-built is transformed into an eval-list suitable for
;;; arguments to continuation-when-rpc-argument-list-is-built (this continuation
;;; will be a symbolic tag, one of 'start, 'call, or 'return).

(def-structure receiving-rpc-arglist-structure
  (rpc-arglist-being-built nil                   ;icp-list of receiving-resumable-objects,
   :reclaimer                                    ; handled RPC objects, and
   reclaim-icp-list-with-some-resumable-objects) ; shared evaluation-values
  (continuation-waiting-for-rpc-arglist 'error)  ;one of START, CALL, RETURN, ERROR, OLE
  rpc-name-waiting-for-rpc-arglist               ;shared remote-procedure-name
  rpc-identifier-waiting-for-rpc-arglist         ;shared remote-procedure-identifier
  rpc-index-waiting-for-rpc-arglist              ;a fixnum, for RETURNs
  (incompletely-built-object-args nil            ;icp-list of shared G2 objects
   :reclaimer reclaim-icp-list)
  receiving-rpc-arglist-reclaim-list             ;for GSI only
  (serial-number-of-ole-dragging-context? nil)   ;fixnum or nil
  )

(defun reclaim-icp-list-of-rpc-arglist-structures (rpc-arglist-structures)
  (loop for rpc-arglist-structure in rpc-arglist-structures
	do (reclaim-receiving-rpc-arglist-structure rpc-arglist-structure))
  (reclaim-icp-list rpc-arglist-structures))

(defun reclaim-icp-list-with-some-resumable-objects (icp-list)
  (loop for possible-resumable-object in icp-list
	do
    (when (receiving-resumable-object-p possible-resumable-object)
      (setf (enclosing-rpc-arglist-structure? possible-resumable-object) nil)
      (reclaim-single-receiving-resumable-object possible-resumable-object)))
  (reclaim-icp-list icp-list))
    



;;;; [8] Reclaimers for RPC Object Arguments and Argument Lists

(defmacro mapping-across-resumable-object-siblings
    ((resumable-object-var &key (including-self-p t)) &body body)
  (unless (symbolp resumable-object-var)
    (error "MAPPING-ACROSS-RESUMABLE-OBJECT-SIBLINGS: ~
            expected a symbol, not ~a"
	   resumable-object-var))
  (avoiding-variable-capture (&aux initial-resumable-var)
    `(progn
       ;; Execute body with resumable-object-var rebound to forward links.
       (let ((,initial-resumable-var
		(next-resumable-object-in-rpc-arglist? ,resumable-object-var)))
	 (loop for ,resumable-object-var
	       = ,initial-resumable-var
	       then (next-resumable-object-in-rpc-arglist?
		      ,resumable-object-var)
	       while ,resumable-object-var
	       do
	   (progn ,@body)))
       ;; Execute body with resumable-object-var rebound to reverse links.
       (let ((,initial-resumable-var
		(previous-resumable-object-in-rpc-arglist?
		  ,resumable-object-var)))
	 (loop for ,resumable-object-var
	       = ,initial-resumable-var
		   then (previous-resumable-object-in-rpc-arglist?
			  ,resumable-object-var)
	       while ,resumable-object-var
	       do
	   (progn ,@body)))
       ;; Execute body with resumable-object-var bound to the object itself.
       ,@(if including-self-p
	     body
	     nil))))




(defun reclaim-single-receiving-resumable-object (receiving-resumable-object)
  (runtime-current-system-case
    (ab (g2-reclaim-single-receiving-resumable-object
	  receiving-resumable-object)))
  (let ((rpc-identifier?
	  (rpc-identifier-for-this-object? receiving-resumable-object)))
    (when rpc-identifier?
      (setf (remote-procedure-identifier-resumable-objects rpc-identifier?)
	    (delete-icp-element
	      receiving-resumable-object
	      (remote-procedure-identifier-resumable-objects
		rpc-identifier?)))))
  (reclaim-receiving-resumable-object-internal receiving-resumable-object))
  
(defun reclaim-receiving-resumable-object (receiving-resumable-object)
  (let ((arglist-structure?
	  (enclosing-rpc-arglist-structure? receiving-resumable-object)))
    (if arglist-structure?
	(reclaim-receiving-rpc-arglist-structure arglist-structure?)
	;; Note that when we reclaim a resumable object on the remote side, its
	;; enclosing-rpc-arglist-structure?  must be reclaimed too.  Since there
	;; may be more than one receiving-resumable-object structure for a given
	;; rpc-arglist-structure, the following form removes all pointers to a
	;; given rpc-arglist-structure, so it is only reclaimed once.
	(mapping-across-resumable-object-siblings
	  (receiving-resumable-object)
	  (reclaim-single-receiving-resumable-object
	    receiving-resumable-object)))))




;;;; [11] ICP Writer and Reader for RPC Object Argument

;;; The behavior of the ICP value writer for `rpc-value-or-object' depends on
;;; the entity given it.  If the entity is an evaluation value, the writer
;;; transmits an evaluation value, which is recreated on the other end.  If the
;;; entity is an object (more specifically, a sending-resumable-object structure
;;; representing a G2 object or a GSI object struct that is an argument to a
;;; remote procedure call), the writer transmits a corresponding object index
;;; for an ICP resumable-object.  This index causes the reader to create a
;;; receiving-resumable-object structure, which governs the reading of
;;; subsequent portions of the object through ICP.  Since the object may be of
;;; arbitrary size, this alleviates network clogging.

;;; Note that it is more usual for corresponding ICP object indices to be
;;; transmitted as part of define-<icp-object-type> messages that are sent as
;;; the body of def-icp-object-type forms.  We do it differently here to avoid
;;; the overhead of sending an ICP message for every RPC object argument.

;; jh, 2/3/94.  Remember to put in a similar comment when we do the same
;; "unusal" trick (sending ICP indices outside of a define-<icp-object-type>
;; message) for the interned symbols that are attribute names.  This also avoids
;; the complexity of having to collect every symbol beforehand and do a batch of
;; ICP intern messages before we commence actually passing the contents of the
;; object.

(defun-simple gsi-item-is-value-p (gsi-item)
  (not (or (gsi-instance-class gsi-item)
	   (gsi-item-reference-flag-value gsi-item)
	   (and (gsi-instance-value gsi-item)
		(memq (gsi-instance-value-type gsi-item)
		      '(#.gsi-integer-array-type-tag
			#.gsi-symbol-array-type-tag
			#.gsi-string-array-type-tag
			#.gsi-logical-array-type-tag
			#.gsi-64bit-float-array-type-tag
			#.gsi-item-or-value-array-type-tag
			#.gsi-quantity-array-type-tag
			#.gsi-item-array-type-tag
			#.gsi-value-array-type-tag
			#.gsi-integer-list-type-tag
			#.gsi-symbol-list-type-tag
			#.gsi-string-list-type-tag
			#.gsi-logical-list-type-tag
			#.gsi-64bit-float-list-type-tag
			#.gsi-item-or-value-list-type-tag
			#.gsi-quantity-list-type-tag
			#.gsi-item-list-type-tag
			#.gsi-value-list-type-tag))))))			

(defun-simple class-for-gsi-item (gsi-item)
  (or (gsi-instance-class gsi-item)
      (when (gsi-instance-value gsi-item)
	(let ((class (case (gsi-instance-value-type gsi-item)
		       ;; (#.gsi-item-type-tag 'item)
		       (#.gsi-integer-array-type-tag 'integer-array)
		       (#.gsi-symbol-array-type-tag 'symbol-array)
		       (#.gsi-string-array-type-tag 'text-array)
		       (#.gsi-logical-array-type-tag 'truth-value-array)
		       (#.gsi-64bit-float-array-type-tag 'float-array)
		       (#.gsi-item-or-value-array-type-tag 'g2-array)
		       (#.gsi-quantity-array-type-tag 'quantity-array)
		       (#.gsi-item-array-type-tag 'item-array)
		       (#.gsi-value-array-type-tag 'value-array)
		       (#.gsi-integer-list-type-tag 'integer-list)
		       (#.gsi-symbol-list-type-tag 'symbol-list)
		       (#.gsi-string-list-type-tag 'text-list)
		       (#.gsi-logical-list-type-tag 'truth-value-list)
		       (#.gsi-64bit-float-list-type-tag 'float-list)
		       (#.gsi-item-or-value-list-type-tag 'g2-list)
		       (#.gsi-quantity-list-type-tag 'quantity-list)
		       (#.gsi-item-list-type-tag 'item-list)
		       (#.gsi-value-list-type-tag 'value-list))))
	  (when class
	    (setf (gsi-instance-class gsi-item) class))))))

(def-icp-value-writer rpc-value-or-object
  (runtime-current-system-case
    (ab
      (g2-write-icp-rpc-value-or-object rpc-value-or-object))
    (gsi
      (unless (gsi-instance-p rpc-value-or-object)
	(gsi-connection-error 'write_rpc_argument gsi-incompatible-structure))
      (let ((value-type (gsi-instance-value-type rpc-value-or-object)))
	(if (gsi-item-is-value-p rpc-value-or-object)
	    (let ((gsi-instance-index (gsi-instance-squirrelled-index rpc-value-or-object))
		  (gsi-extension-data? (gsi-extension-data? current-icp-socket)))
	      (write-icp-byte rpc-object-type-tag)
	      (write-icp-unsigned-integer gsi-instance-index)
	      (gsi-push rpc-value-or-object (gsi-outgoing-item-list? gsi-extension-data?)))
	    (let ((value (gsi-instance-value rpc-value-or-object)))
	      (unless value (setq value-type #.gsi-null-type-tag))
	      (case value-type
		(#.gsi-null-type-tag
		 (write-icp-byte gsi-null-type-tag))
		(#.gsi-integer-type-tag
		 (write-icp-byte gsi-integer-type-tag)
		 (write-icp-integer value))
		(#.gsi-logical-type-tag
		 (write-icp-byte gsi-logical-type-tag)
		 (write-icp-integer value))
		(#.gsi-symbol-type-tag
		 (write-icp-byte gsi-symbol-type-tag)
		 (write-icp-text-string (symbol-name-text-string value)))
		((#.gsi-string-type-tag #.gsi-unsigned-short-vector-type-tag)
		 (write-icp-byte gsi-string-type-tag)
		 (converting-gsi-value-to-value (value)
		   (write-icp-text-string value)))
		(#.gsi-64bit-float-type-tag
		 (write-icp-byte gsi-64bit-float-type-tag)
		 (write-icp-managed-double-float value))
		(#.gsi-item-handle-type-tag
		 (write-icp-byte rpc-object-handle-type-tag)
		 (write-icp-fixnum value))
		(t #+development
		   (cerror "Transmit Null GSI value type"
			   "Value type ~a implies item, yet no class specified in WRITE-ICP-RPC-VALUE-OR-OBJECT"
			   (gsi-instance-value-type rpc-value-or-object))
		   (write-icp-byte gsi-null-type-tag)))))))))

(def-icp-value-reader rpc-value-or-object
  (let ((type-tag (peek-icp-byte)))
    (cond
      ((=f type-tag rpc-object-type-tag)
       (read-icp-byte)
       (let* ((remote-object-index (read-icp-unsigned-integer))
	      (receiving-resumable-object (make-receiving-resumable-object)))
	 (store-corresponding-icp-object
	   remote-object-index
	   receiving-resumable-object)
	 (setf (corresponding-index-of-self receiving-resumable-object)
	       remote-object-index)
	 receiving-resumable-object))
      ((=f type-tag rpc-object-handle-type-tag)
       (read-icp-byte)
       (runtime-current-system-case
	 (gsi
	  (make-gsi-instance gsi-item-handle-type-tag (read-icp-fixnum)))
	 (ab ; if the other side was GSI, we can look up the object here
	  (make-evaluation-integer (read-icp-fixnum)))))
      (t
       (read-icp-remote-value)))))




;;;; [12] ICP Writer and Reader for RPC Argument List

(def-icp-value-writer rpc-argument-list ;actually an array for GSI
  (runtime-current-system-case
    (ab
      (write-icp-unsigned-integer (length rpc-argument-list))
      (loop for value-or-object in rpc-argument-list
	    do (write-icp-rpc-value-or-object value-or-object)))
    (gsi
      (let* ((actual-size
	      (or rpc-argument-count-override?
		  (if rpc-argument-list
		      (-f (gsi-managed-array-length rpc-argument-list) gsi-magic-offset)
		      0))))
	(write-icp-unsigned-integer actual-size)
	(loop for i from gsi-magic-offset
		    to actual-size
	      as value-or-object = (gsi-managed-svref rpc-argument-list i)
	      do (write-icp-rpc-value-or-object value-or-object))))))

(defmacro if-object-passing-arguments-let
    ((rpc-arglist-structure-var rpc-argument-list-var) then-form else-form)
  (avoiding-variable-capture (&aux object-argument?)
    `(let* ((,object-argument?
	       (loop for argument in ,rpc-argument-list-var
		     when (receiving-resumable-object-p argument)
		       do (return argument)
		     finally (return nil))))
       (if ,object-argument?
	   (let ((,rpc-arglist-structure-var ;known non-nil
		    (enclosing-rpc-arglist-structure? ,object-argument?)))
	     ,then-form)
	   ,else-form))))

(defun-void reclaim-ignored-rpc-argument-list (rpc-argument-list)
  (runtime-current-system-case
    (ab
      (if-object-passing-arguments-let
	(rpc-arglist-structure rpc-argument-list)
	(progn
	  (loop for arg in rpc-argument-list
		do (reclaim-if-evaluation-value arg))
	  (reclaim-receiving-rpc-arglist-structure rpc-arglist-structure))
	(reclaim-unprocessed-rpc-argument-list rpc-argument-list (frame-serial-number-0))))
    (gsi
      (let ((item-among-arguments?
	      (get-item-from-arguments rpc-argument-list)))
	(cond
	  (item-among-arguments?
	   (let ((rpc-arglist-structure
		   (enclosing-rpc-arglist-structure? item-among-arguments?)))
	     (gsi-reclaim-contents-and-clear-list
	       (receiving-rpc-arglist-reclaim-list rpc-arglist-structure)
	       (default-owner-for-gsi-objects))
	     (reclaim-rpc-argument-list rpc-argument-list nil)
	     (setf (rpc-arglist-being-built rpc-arglist-structure) nil)
	     (reclaim-receiving-rpc-arglist-structure rpc-arglist-structure)))
	  (t (gsi-reclaim-contents-and-clear-list gsi-reclaim-list? (default-owner-for-gsi-objects))
	     (reclaim-rpc-argument-list rpc-argument-list nil)))))))

(def-icp-value-reader rpc-argument-list ;actually an array for GSI
  (let ((length (read-icp-unsigned-integer)))
    (runtime-current-system-case
      (ab
	(if (<=f length 0)
	    nil
	    (loop repeat length
		  for argument = (read-icp-rpc-value-or-object)
		  with argument-list-head? = nil
		  with argument-list-tail
		  with enclosing-arglist-structure? = nil
		  with previous-receiving-resumable-object? = nil
		  do
	      (let ((argument-cons (icp-cons argument nil)))
		(if argument-list-head?
		    (setf (cdr argument-list-tail) argument-cons)
		    (setq argument-list-head? argument-cons))
		(setf argument-list-tail argument-cons))
	      (when (receiving-resumable-object-p argument)
		(unless enclosing-arglist-structure?
		  (setq enclosing-arglist-structure?
			(make-receiving-rpc-arglist-structure)))
		(setf (enclosing-rpc-arglist-structure? argument)
		      enclosing-arglist-structure?)
		(when previous-receiving-resumable-object?
		  (setf (next-resumable-object-in-rpc-arglist?
			  previous-receiving-resumable-object?)
			argument))
		(setf (previous-resumable-object-in-rpc-arglist? argument)
		      previous-receiving-resumable-object?)
		(setq previous-receiving-resumable-object? argument))
		  finally
		    (when enclosing-arglist-structure?
		      (setf (rpc-arglist-being-built
			      enclosing-arglist-structure?)
			    argument-list-head?))
		    (return argument-list-head?))))
      (gsi
       (let* ((actual-size (+f length gsi-magic-offset))
	      (arg-array (gsi-allocate-managed-array actual-size))) 
	 (setf (gsi-managed-svref arg-array 0) gsi-magic-number)
	 (loop for item-count from gsi-magic-offset below actual-size
	       for argument = (read-icp-rpc-value-or-object)
	       with enclosing-arglist-structure? = nil
	       with previous-receiving-resumable-object? = nil
	       do
	   (setf (gsi-managed-svref arg-array item-count) argument)
	   (when (receiving-resumable-object-p argument)
	     (unless enclosing-arglist-structure?
	       (setq enclosing-arglist-structure?
		     (make-receiving-rpc-arglist-structure)))
	     (setf (enclosing-rpc-arglist-structure? argument)
		   enclosing-arglist-structure?)
	     (when previous-receiving-resumable-object?
	       (setf (next-resumable-object-in-rpc-arglist?
		       previous-receiving-resumable-object?)
		     argument))
	     (setf (previous-resumable-object-in-rpc-arglist? argument)
		   previous-receiving-resumable-object?)
	     (setq previous-receiving-resumable-object? argument))
	       finally
		 (when enclosing-arglist-structure?
		   (setf (rpc-arglist-being-built
			   enclosing-arglist-structure?)
			 arg-array))
		 (return arg-array)))))))

;; get-item-from-arguments returns the first item found (if any).  In
;; fact it looks for a receiving-resumable-object as items are not
;; ever enclosed in arg lists with all their contents.  The contents of
;; the item follows asynchronously in future ICP messages.
;; Note, in G2 RPC arguments are read into lists, in GSI they are read
;; into arrays.

(defun-simple get-item-from-arguments (rpc-arguments)
  (runtime-current-system-case
    (gsi
      (loop for i from gsi-magic-offset below (gsi-managed-array-length rpc-arguments)
	    as argument = (gsi-managed-svref rpc-arguments i)
	    when (receiving-resumable-object-p argument)
	      return argument
	finally nil))
    (t rpc-arguments)))



;;;; [14] Resumable Object Portion

;;; On the writing side, a resumable-object-portion? is a
;;; sending-resumable-object structure that contains information on how to
;;; continue sending the contents of an object over ICP.

;;; On the reading side, a resumable-object-portion? is nil until the contents
;;; of the object have been completely received, then it is a
;;; receiving-resumable-object structure.  In the latter case, we check the
;;; links this structure has to other receiving-resumable-object structures,
;;; representing other arguments to the remote procedure call.  If all the
;;; arguments are complete, we create an argument list suitable for executing
;;; the procedure on the reading side and pass that argument list along to the
;;; apprpriate start or call function.

;;;; [14.1] ICP Tag Groups

(defmacro def-icp-tag-group (tag-group-name &body specs)
  `(eval-when (:compile-toplevel :load-toplevel :execute)
    ,@(loop for (name value) in specs
	    collect `(defconstant ,name ,value))
    (defconstant ,tag-group-name
      ',(loop for (nil value) in specs collect value))))

(defmacro proclaim-icp-tags-disjoint
    (tag-group-name &rest disjoint-from-tag-group-names)
  (if (eval-feature :development)
      `(when (intersection
	       (list ,tag-group-name)
	       (list ,@disjoint-from-tag-group-names)
	       :test #'intersection)
	 (warn "ICP tag group ~s collides with tag groups~%~s"
	       ',tag-group-name
	       ',disjoint-from-tag-group-names))
      nil))




;;;; [14.2] ICP Value Protocol

;;;; [14.2.1] Defining ICP Value Protocols

;;; def-icp-value-protocol name icp-value-type unique-tag writer-arglist
;;;                        &key writer reader

;;; The macro `def-icp-value-protocol' is designed to ease the task of
;;; implementing complicated ICP value types.  Typically, such types involve the
;;; writer sending an unsigned integer as a tag, followed by the reader
;;; branching to special-case code based on that tag.  Without abstraction, this
;;; approach can lead to confusion, since the def-icp-value-writer form is
;;; textually distinct from the def-icp-value-reader, and worse, the ICP writes
;;; and reads often appear in widely scattered sub-functions.  So
;;; def-icp-value-protocol allows us to put the relevant writer and reader
;;; branches in one place, thereby improving clarity.  Note that it is still
;;; necessary to maintain separate def-icp-value-reader and -writer definitions
;;; for the toplevel ICP value type, but with judicious use of
;;; def-icp-value-protocol and read-icp-value-using-protocol (q.v.), the bodies
;;; of these definitions become briefer and easier to comprehend.

;;; The icp-value-type argument to def-icp-value-protocol is an unevaluated
;;; symbol naming the toplevel ICP value type, for which a separate ICP value
;;; reader and writer must exist.  This icp-value-type becomes the name of the
;;; protocol.  The unique-tag argument is unevaluated and should be a fixnum.
;;; This fixnum will be sent using send-icp-fixnum before the body of the
;;; :writer, and must must be distinct among every def-icp-value-protocol form
;;; for a given icp-value-type, lest an error be signaled at the time the
;;; def-icp-value-protocol form is evaluated.

;;; The def-icp-value-protocol macro makes these arrangements:

;;; > Defines a writer function named WRITE-ICP-<name>-FOR-<icp-value-type>.
;;;   whose arguments are given by writer-arglist.  When called, the writer
;;;   function performs a write-icp-unsigned-integer of unique-tag and then
;;;   executes the form given by the :writer keyword.  Note that this is a single
;;;   form, not an implicit progn.  Note as well that this form should not send
;;;   unique-tag across ICP, as this has already been done automatically.

;;; > Records a case-clause designed to be used in the reader for the toplevel
;;;   ICP value via the reading-with-icp-protocol macro (q.v.).  This clause
;;;   dispatches on the value of unique-tag to execute the form given by the
;;;   :reader keyword.  Note that this is a single form, not an implicit progn.

;;; Since def-icp-value-protocol records a form for the reader rather than a
;;; funcallable function, a read-icp-value-using-protocol form for a given ICP
;;; value type must occur after the last def-icp-value-protocol for that ICP
;;; value type.  The def-icp-value-protocol and reading-with-icp-protocol macros
;;; cooperate to check this constraint and signal an error if it is violated.

#-no-macros
(eval-when (:compile-toplevel :load-toplevel :execute)
(defvar icp-value-protocol-registry nil)
)

(defun-for-macro check-then-get-icp-value-protocol-entry
    (protocol-name
      previous-protocol-spec?
      name
      unique-tag
      name-for-protocol-reader)
  (let ((new-entry (list name unique-tag name-for-protocol-reader))
	(previous-entry-with-same-tag?
	  (find unique-tag (cdddr previous-protocol-spec?) :key #'second)))
    (cond
      ((null previous-protocol-spec?) new-entry)
      ((and previous-entry-with-same-tag?
	    (equal previous-entry-with-same-tag? new-entry))
       nil)
      (previous-entry-with-same-tag?
       "DEF-ICP-VALUE-PROTOCOL: in protocol ~s~%~
        tag ~s for name ~s~%is already in use by name ~s"
       protocol-name
       unique-tag
       name 
       (first previous-entry-with-same-tag?))
      (t
       (unless (eval-feature :no-macros)
	 (when (second previous-protocol-spec?)
	   (error
	     "DEF-ICP-VALUE-PROTOCOL: in protocol ~s~%~
              new case ~s,~%is being defined ~
              after a use of READING-WITH-ICP-PROTOCOL for that protocol"
	     protocol-name
	     name)))
       new-entry))))
    
(defmacro def-icp-value-protocol
    ((name unique-tag &key protocol-name allowing-unwind-p)
     writer-arglist &key writer reader)

  (unless (typep unique-tag 'fixnum)
    (error "DEF-ICP-VALUE-PROTOCOL:
            ~s in protocol ~s needs a fixnum for a tag, not ~s"
	   name
	   protocol-name
	   unique-tag))

  (let* ((name-for-protocol-reader
	   (intern (format nil "READ-ICP-~a" name)))
	 (name-for-protocol-writer (intern (format nil "WRITE-ICP-~a" name)))
	 (name-for-unique-tag-constant
	   (intern (format nil "~a-FOR-~a" name protocol-name)))
	 (name-for-catcher (intern (format nil "EXIT-FROM-~a" protocol-name))))
    
    `(progn
       (eval-when (:compile-toplevel :load-toplevel :execute)
	 ,@(if (eval-feature :no-macros)
	       nil
	       `((let* ((previous-protocol-spec?
			  (assoc ',protocol-name icp-value-protocol-registry))
			(new-entry?
			  (check-then-get-icp-value-protocol-entry
			    ',protocol-name
			    previous-protocol-spec?
			    ',name
			    ',unique-tag
			    ',name-for-protocol-reader)))
		   (cond
		     ((and previous-protocol-spec? new-entry?)
		      (push new-entry? (cdddr previous-protocol-spec?)))
		     (new-entry?
		      (push (list ',protocol-name
				  nil
				  ',name-for-catcher new-entry?)
			    icp-value-protocol-registry))))))
	 (defconstant ,name-for-unique-tag-constant ,unique-tag))
       (defun ,name-for-protocol-writer ,writer-arglist
	 (write-icp-byte ,name-for-unique-tag-constant)
	 ,writer)
       ,(if allowing-unwind-p
	    `(defun-allowing-unwind ,name-for-protocol-reader () ,reader)
	    `(defun ,name-for-protocol-reader () ,reader))
       ;; So GSI doesn't emit the symbol returned by defun..
       nil)))


(defvar rpc-throw-tag nil)

;;;; [14.2.2] Reading in ICP Value Protocols

;;; read-icp-value-using-protocol icp-protocol

;;; The macro `read-icp-value-using-protocol' provides an endless loop
;;; containing a case statement that dispatches on the tag defined in
;;; def-icp-value-protocol to execute the reader code also specified there.  The
;;; icp-protocol is an unevaluated symbol that names a protocol (i.e., an ICP
;;; value type).  Note that the :reader
;;; forms of a def-icp-value-protocol can exit the endless loop
;;; by calling stop-reading-icp-value-using-protocol.

(defmacro read-icp-value-using-protocol (icp-protocol)
  (let ((protocol-entry? (assoc icp-protocol icp-value-protocol-registry)))

    (unless protocol-entry?
      (error "READ-ICP-VALUE-USING-PROTOCOL empty protocol for ~s"
	     icp-protocol))
    
    ;; Record the fact that this macro has been expanded, so subsequent
    ;; def-icp-value-protocol forms can signal an error.
    (setf (second protocol-entry?) t)

    (avoiding-variable-capture (&aux icp-tag)
      `(let ((rpc-throw-tag nil))
	 (loop
	   (let ((gsi-reclaim-list-level 'rpc-arg-list) ; Let GSI makers know which level of
		                                        ; reclaim list to use by default.
		 (,icp-tag (read-icp-byte)))
	     (case ,icp-tag
	       ,@(loop for (nil tag reader-function-name)
			   in (cdddr protocol-entry?)
		       collect
		       `(,tag (,reader-function-name)))
	       ,@(if (eval-feature :development)
		     `((otherwise
			 (cerror
			   "Continue reading ~
                        (This behavior is what the user gets)"
			   "READ-ICP-VALUE-USING-PROTOCOL: ~
                        unknown tag ~s for protocol ~s"
			   ,icp-tag
			   ',icp-protocol)))
		     nil)))
	    (when rpc-throw-tag (return nil)))))))

(defmacro stop-reading-icp-value-using-protocol (icp-protocol)
  (let ((protocol-entry? (assoc icp-protocol icp-value-protocol-registry)))
    (unless protocol-entry?
      (error "STOP-READING-ICP-VALUE-USING-PROTOCOL: ~
              empty protocol for ~s" icp-protocol))
    `(progn
       (setq rpc-throw-tag ',(third protocol-entry?))
       nil)))
    



;;;; [14.3] ICP Value Protocols for Resumable Objects

;;;; [14.3.1] Protocol for Possibly Interned Symbols

(def-icp-tag-group possibly-interned-symbol-tags
 (possibly-interned-symbol-interned-tag   0)
 (possibly-interned-symbol-uninterned-tag 1)
 (possibly-interned-symbol-uninterned-overflow-tag 2))

(defun write-icp-possibly-interned-symbol
    (possibly-interned-symbol corresponding-index-of-symbol?)
  ;; Have to check again because of the possibility that the symbol has already
  ;; been interned in this resumable object portion (for example, part of a
  ;; symbol vector range).  Note that this makes bandwidth computations provide
  ;; an upper bound instead of an exact assessment.
  (unless corresponding-index-of-symbol?
    (setq corresponding-index-of-symbol?
	  (get-icp-object-index-for-symbol
	    possibly-interned-symbol
	    current-icp-port)))
  (cond
    (corresponding-index-of-symbol?
     (write-icp-byte possibly-interned-symbol-interned-tag)
     (write-icp-fixnum corresponding-index-of-symbol?))
    (t (let ((symbol-name
	       (symbol-name-text-string possibly-interned-symbol)))
	 (multiple-value-bind (symbol-index overflow-count?)
	     (establish-new-object-index-for-symbol
	       possibly-interned-symbol
	       current-icp-port
	       nil)	   
	   (cond
	     (overflow-count?
	      (write-icp-byte possibly-interned-symbol-uninterned-overflow-tag)
	      (write-icp-fixnum overflow-count?))
	     (t (write-icp-byte possibly-interned-symbol-uninterned-tag)))	   
	   (write-icp-fixnum symbol-index)
	   (write-icp-text-string symbol-name))))))

(defun-for-macro interned-symbol-case-for-read-icp-possibly-interned-symbol
    ()
  `(let* ((symbol-index (read-icp-fixnum))
	  (symbol-name (read-icp-text-string))
	  (symbol (intern-text-string symbol-name)))
     (store-corresponding-icp-object
       symbol-index
       symbol)
     symbol))

(defun-for-macro case-clauses-for-read-icp-possibly-interned-symbol ()
  `((,possibly-interned-symbol-interned-tag
       (let* ((symbol-index (read-icp-fixnum))
	      (symbol
		(get-symbol-from-icp-port current-icp-port symbol-index)))
	 symbol))
    (,possibly-interned-symbol-uninterned-tag
       ,(interned-symbol-case-for-read-icp-possibly-interned-symbol))
    ;; jh, 4/24/96.  The following clause copes with the case where the index
    ;; space must be enlarged before the index for the new symbol can be stored.
    ;; Heretofore, the ICP message enlarge-corresponding-icp-object-index-space
    ;; would be sent before the message needing the symbol, but we are already
    ;; reading a message here, namely continue-building-resumable-object.
    (,possibly-interned-symbol-uninterned-overflow-tag
       (let ((new-index-limit-plus-one (read-icp-fixnum)))
	 (handler-for-enlarge-corresponding-icp-object-index-space
	   ',(name-of-corresponding-icp-object-index-space 'symbol)
	   new-index-limit-plus-one)	 
	 ,(interned-symbol-case-for-read-icp-possibly-interned-symbol)))))

(defmacro body-of-read-icp-possibly-interned-symbol ()
  `(let ((tag (read-icp-byte)))
     (case tag
       ,@(case-clauses-for-read-icp-possibly-interned-symbol)
       (otherwise
	,@(if (eval-feature :development)
	      `((cerror "Continue reading, returning NIL as the symbol ~
                         (This behavior is what the user would get)"
			"READ-ICP-POSSIBLY-INTERNED-SYMBOL: ~
                         unknown tag ~s" tag))
	      nil)
	nil))))

(defun read-icp-possibly-interned-symbol ()
  (body-of-read-icp-possibly-interned-symbol))

(defmacro proclaim-icp-tags-disjoint-from-possibly-interned-symbol-tags
    (tag-group-name)
  `(proclaim-icp-tags-disjoint ,tag-group-name possibly-interned-symbol-tags))




;;;; [14.3.2] Attribute Spec Protocol

(def-icp-tag-group attribute-spec?-tags
  (nameless-attribute-spec-tag         2)
  (vector-element-attribute-spec-tag   3)
  (list-element-attribute-spec-tag     4)
  (unqualified-symbolic-attribute-tag 12)
  (qualified-symbolic-attribute-tag   13)
  (unqualified-system-attribute-tag   14)
  (qualified-system-attribute-tag     15)
  )

(defmacro write-icp-named-attribute-spec
    (named-attribute-spec qualified-tag unqualified-tag)
  (avoiding-variable-capture (named-attribute-spec)
    `(let ((class-qualifier?
	     (resumable-attribute-class-qualifier? ,named-attribute-spec))
	   (base-name
	     (resumable-attribute-base-name ,named-attribute-spec)))
       (cond (class-qualifier?
	      (write-icp-byte ,qualified-tag)
	      (write-icp-possibly-interned-symbol class-qualifier? nil))
	     (t
	      (write-icp-byte ,unqualified-tag)))
       (write-icp-possibly-interned-symbol
	 base-name nil))))

(defun-void write-icp-attribute-spec? (attribute-spec?)
  (if attribute-spec?
      (let ((attribute-type (resumable-attribute-type attribute-spec?)))
	(case attribute-type
	  (attribute
	   (if (memq (resumable-attribute-base-name attribute-spec?)
		     '(name current-value))
	       (write-icp-named-attribute-spec
		 attribute-spec?
		 qualified-system-attribute-tag
		 unqualified-system-attribute-tag)
	       (write-icp-named-attribute-spec
		 attribute-spec?
		 qualified-symbolic-attribute-tag
		 unqualified-symbolic-attribute-tag)))
	  (vector-element
	   (write-icp-byte vector-element-attribute-spec-tag)
	   (write-icp-fixnum (resumable-vector-or-list-index attribute-spec?)))
	  (list-element
	   (write-icp-byte list-element-attribute-spec-tag)
	   (write-icp-fixnum (resumable-vector-or-list-index attribute-spec?)))
	  #+development
	  (otherwise
	   (cerror "Continue without sending the attribute ~
                    (This behavior is what the user would get)"
		   "WRITE-ICP-ATTRIBUTE-SPEC?: unknown attribute type ~s"
		   attribute-type))))
      (write-icp-byte nameless-attribute-spec-tag)))

(defmacro body-of-read-icp-attribute-spec? ()
  `(let ((tag (read-icp-byte)))
     (case tag
       (,unqualified-symbolic-attribute-tag
	(let ((base-name (read-icp-possibly-interned-symbol)))
	  (values 'attribute nil base-name)))
       (,qualified-symbolic-attribute-tag
	(let* ((qualifier (read-icp-possibly-interned-symbol))
	       (base-name (read-icp-possibly-interned-symbol)))
	  (values 'attribute qualifier base-name)))
       (,unqualified-system-attribute-tag
	(let ((base-name (read-icp-possibly-interned-symbol)))
	  (values 'attribute nil base-name)))
       (,qualified-system-attribute-tag
	(let* ((qualifier (read-icp-possibly-interned-symbol))
	       (base-name (read-icp-possibly-interned-symbol)))
	  (values 'attribute qualifier base-name)))
       (,vector-element-attribute-spec-tag
	(let ((index (read-icp-fixnum)))
	  (values 'vector-element nil index)))
       (,list-element-attribute-spec-tag
	(let ((index (read-icp-fixnum)))
	  (values 'list-element nil index)))
       ;; The following clause returns nil as an attribute name.  This is
       ;; permissible with the toplevel RPC object.
       (otherwise (values 'attribute nil nil)))))

(defun read-icp-attribute-spec? ()
  (body-of-read-icp-attribute-spec?))

(def-icp-value-writer list-of-attributes
  (runtime-current-system-case
    (ab (g2-write-icp-list-of-attributes list-of-attributes))
    ((gsi telewindows)
     (declare-ignorable-icp-arguments list-of-attributes)
     (write-icp-fixnum 0))))

(defmacro loop-body-of-read-icp-list-of-attributes ()
  `(let ((tag (read-icp-byte)))
     (runtime-current-system-case
       (ab (g2-read-icp-attribute-for-list-of-attributes tag))
       ((gsi telewindows)
	 (case tag
	   (,qualified-symbolic-attribute-tag
	    (let* ((qualifier (read-icp-possibly-interned-symbol))
		   (base-name (read-icp-possibly-interned-symbol)))
	      (icp-list qualifier base-name)))
	   (,unqualified-symbolic-attribute-tag
	    (read-icp-possibly-interned-symbol))
	   (otherwise
	    #+development
	    (cerror "Continue, returning nil ~
                     (This behavior is what the user would get)"
		    "READ-ICP-LIST-OF-ATTRIBUTES:  unexpected tag ~a"
		    tag)
	    nil))))))

(def-icp-value-reader list-of-attributes
  (let ((length (read-icp-fixnum)))
    (loop for count from 1 to length
	  collect
      (loop-body-of-read-icp-list-of-attributes)
	  using icp-cons)))

(def-icp-value-reader list-of-boolean
  (let ((length (read-icp-fixnum)))
    (loop for count from 1 to length
	  collect (read-icp-boolean)
	    using icp-cons)))

(def-icp-value-writer list-of-boolean
  (write-icp-fixnum (length list-of-boolean))
  (loop for value in list-of-boolean
	do (write-icp-boolean value)))

(def-icp-value-writer list-of-lists-of-attributes
  (write-icp-fixnum (length list-of-lists-of-attributes))
  (loop for list-of-attributes in list-of-lists-of-attributes
	do
    (write-icp-list-of-attributes list-of-attributes)))

(def-icp-value-reader list-of-lists-of-attributes
  (let ((length (read-icp-fixnum)))
    (loop for count from 1 to length
	  collect (read-icp-list-of-attributes)
	    using icp-cons)))

(def-icp-value-writer list-of-included-return-attributes
  (with-bifurcated-version-for-output (remote-procedure-include-attribute-icp-version)
    nil
    (write-icp-list-of-lists-of-attributes
      list-of-included-return-attributes)))

(def-icp-value-reader list-of-included-return-attributes
  (with-bifurcated-version-for-input (remote-procedure-include-attribute-icp-version)
    nil
    (read-icp-list-of-lists-of-attributes)))

(def-icp-value-writer list-of-excluded-return-attributes
  (with-bifurcated-version-for-output (remote-procedure-include-attribute-icp-version)
    nil
    (write-icp-list-of-lists-of-attributes
      list-of-excluded-return-attributes)))

(def-icp-value-reader list-of-excluded-return-attributes
  (with-bifurcated-version-for-input (remote-procedure-include-attribute-icp-version)
    nil
    (read-icp-list-of-lists-of-attributes)))

(def-icp-value-writer list-of-included-return-system-attributes
  (with-bifurcated-version-for-output (remote-procedure-include-attribute-icp-version)
    nil
    (write-icp-list-of-lists-of-attributes
      list-of-included-return-system-attributes)))

(def-icp-value-reader list-of-included-return-system-attributes
  (with-bifurcated-version-for-input (remote-procedure-include-attribute-icp-version)
    nil
    (read-icp-list-of-lists-of-attributes)))

(def-icp-value-writer list-of-include-all-return-system-attributes
  (with-bifurcated-version-for-output (remote-procedure-include-all-system-attributes-icp-version)
    nil
    (write-icp-list-of-boolean
      list-of-include-all-return-system-attributes)))

(def-icp-value-reader list-of-include-all-return-system-attributes
  (with-bifurcated-version-for-input (remote-procedure-include-all-system-attributes-icp-version)
    nil
    (read-icp-list-of-boolean)))

(def-icp-value-writer list-of-include-all-return-system-attributes-except
  (with-bifurcated-version-for-output (remote-procedure-include-all-system-attributes-except-icp-version)
    nil
    (write-icp-list-of-lists-of-attributes
      list-of-include-all-return-system-attributes-except)))

(def-icp-value-reader list-of-include-all-return-system-attributes-except
  (with-bifurcated-version-for-input (remote-procedure-include-all-system-attributes-except-icp-version)
    nil
    (read-icp-list-of-lists-of-attributes)))

(def-icp-value-writer list-of-return-kinds
  (with-bifurcated-version-for-output (new-rpc-kinds-icp-version)
    nil
    (write-icp-list-of-attributes
      list-of-return-kinds)))

(def-icp-value-reader list-of-return-kinds
  (with-bifurcated-version-for-input (new-rpc-kinds-icp-version)
    nil
    (read-icp-list-of-attributes)))

(def-icp-value-writer remote-procedure-varargs-p
  (with-bifurcated-version-for-output (remote-procedure-varargs-p-icp-version)
    nil
    (write-icp-boolean remote-procedure-varargs-p)))

(def-icp-value-reader remote-procedure-varargs-p
  (with-bifurcated-version-for-input (remote-procedure-varargs-p-icp-version)
    nil
    (read-icp-boolean)))




;;;; [14.3.3] Attribute Value Protocol

(def-icp-tag-group attribute-value-tags
  (attribute-value-integer-tag                5)
  (attribute-value-float-tag                  6)  
  (attribute-value-symbol-tag                 7) 
  (attribute-value-text-tag                   8)
  (attribute-value-truth-value-tag            9)
  (unknown-value-vector-element-type-tag     11)
  (circular-reference-tag                    12) ; * note follows...
  (attribute-value-null-tag                  13)
  (attribute-value-evaluation-sequence-tag   14)
  (attribute-value-evaluation-structure-tag  15)
  (attribute-value-long-tag                  16)
  )

;; Note, circular is a misnomer here because, although we have a
;; reference to an item or object that has already been received
;; and built, the reference is not necessarilty circular. paf! 11may94

;; Note that attribute-value-symbol-tag is only used for homogeneous vector and
;; list element types.  Evaluation symbol values themselves use tags from
;; possibly-interned-symbol-tags.  The tag chosen depends on whether or not the
;; symbol is interned relative to the current ICP port.

(proclaim-icp-tags-disjoint-from-possibly-interned-symbol-tags
  attribute-value-tags)

(def-icp-value-writer evaluation-truth-value
  (write-icp-fixnum evaluation-truth-value))

(defun-simple reclaim-evaluation-truth-value-if-appropriate
    (maybe-evaluation-truth-value)
  (runtime-current-system-case
    (ab (reclaim-evaluation-truth-value maybe-evaluation-truth-value))
    ((gsi telewindows) maybe-evaluation-truth-value)))

(def-icp-value-reader evaluation-truth-value
  (runtime-current-system-case
    (ab (make-evaluation-truth-value-function (read-icp-fixnum)))
    ((gsi telewindows) (read-icp-fixnum))))

(defun-void write-icp-attribute-value (simple-value corresponding-index?)
  (runtime-current-system-case
    (ab (g2-write-icp-attribute-value simple-value corresponding-index?))
    ((gsi telewindows)
      (declare-ignorable-icp-arguments corresponding-index?)
     (let ((value-type (gsi-instance-value-type simple-value))
	   (value (gsi-instance-value simple-value)))
       (unless value (setq value-type #.gsi-null-type-tag))
       (case value-type
	 (#.gsi-integer-type-tag
	  (write-icp-byte attribute-value-integer-tag)
	  (write-icp-fixnum value))
	 (#.gsi-logical-type-tag
	  (write-icp-byte attribute-value-truth-value-tag)
	  (write-icp-fixnum value))
	 (#.gsi-64bit-float-type-tag
	  (write-icp-byte attribute-value-float-tag)
	  (write-icp-managed-double-float value))
	 ((#.gsi-string-type-tag #.gsi-unsigned-short-vector-type-tag)
	  (write-icp-byte attribute-value-text-tag)
	  (converting-gsi-value-to-value (converted-value value)
            (write-icp-text-string converted-value)))
	 (#.gsi-symbol-type-tag
	  (write-icp-possibly-interned-symbol value nil))
	 (#.gsi-null-type-tag
	  (write-icp-byte attribute-value-null-tag))
	 (#.gsi-long-type-tag
	  (write-icp-byte attribute-value-long-tag)
	  (write-icp-managed-long value))
	 (t
	  (gsi-connection-error 'write_attribute_value
				gsi-incompatible-type
				value-type)))))))
    
;; The following needs a GSI version based on the function
;; body-of-gsi-read-icp-remote-value in rpc-common1.lisp - paf! 9may94
;; ...I don't think so.  Delete comment by release of 4.0 -paf!9jun94

(defmacro body-of-read-icp-attribute-value ()
  `(let* ((tag (read-icp-byte))
	  (symbol?
	    (case tag
	      ,@(case-clauses-for-read-icp-possibly-interned-symbol)
	      (otherwise nil))))
     (values
       (or symbol?
	   (case tag
	     (,attribute-value-integer-tag (read-icp-fixnum))
	     (,attribute-value-long-tag (read-icp-managed-long))
	     (,attribute-value-float-tag (read-icp-managed-double-float))
	     (,attribute-value-text-tag (read-icp-text-string))
	     ;; ... review truth-value creation for leaks
	     ;; (see 3/28/94 note around g2-get-attribute-for-object-passing)
	     (,attribute-value-truth-value-tag (read-icp-evaluation-truth-value))
	     (,attribute-value-evaluation-sequence-tag
	      (read-icp-evaluation-sequence))
	     (,attribute-value-evaluation-structure-tag
	      (read-icp-evaluation-structure))
	     (,attribute-value-null-tag nil)
	     (otherwise
	      ,@(if (eval-feature :development)
		    `((cerror
			"Continue, returning nil ~
                       (This behavior is what the user would get)"
			"READ-ICP-ATTRIBUTE-VALUE: unknown tag ~s"
			tag))
		    nil)
	    nil)))
       tag)))
	   

(defun-void reclaim-icp-attribute-value (icp-attribute-value)
  (cond
    ((text-string-p icp-attribute-value)
     (reclaim-text-or-gensym-string icp-attribute-value))
    ((managed-float-p icp-attribute-value)
     (reclaim-managed-float icp-attribute-value))))

(defun read-icp-attribute-value ()
  (body-of-read-icp-attribute-value))

(def-icp-value-writer history-timestamp
  (runtime-current-system-case
    (ab (g2-write-history-timestamp history-timestamp))
    ((gsi telewindows)
      (declare-ignorable-icp-arguments history-timestamp))))

(defmacro body-of-read-icp-history-timestamp ()
  `(let ((tag (read-icp-byte)))
     (case tag
       (,attribute-value-integer-tag  (read-icp-fixnum))
       (,attribute-value-float-tag (read-icp-managed-double-float))
       (otherwise
	,@(if (eval-feature :development)
	      `((cerror
		  "Continue, returning nil ~
                   (This behavior is what the user would get)"
		  "READ-ICP-HISTORY-TIMESTAMP: unknown tag ~s"
		  tag))
	      nil)))))

(def-icp-value-reader history-timestamp
  (body-of-read-icp-history-timestamp))




;;;; [14.3.4] Resumable Node Protocols

;;;; [14.3.4.1] Leaf Protocols

(def-icp-value-protocol (add-attribute-value 1
                         :protocol-name resumable-object-portion)
    (attribute-spec? attribute-value corresponding-index-of-attribute-value?)
  :writer
  (progn
    (write-icp-attribute-spec? attribute-spec?)
    (write-icp-attribute-value
      attribute-value
      corresponding-index-of-attribute-value?))
  :reader
  (multiple-value-bind (attribute-type attribute-qualifier? attribute-name-or-index)
      (read-icp-attribute-spec?)
    (multiple-value-bind (attribute-value value-type)
	(read-icp-attribute-value)
      (let ((current-subobject?
	      (current-resumable-subobject-being-built?
		current-receiving-resumable-object)))
	(runtime-current-system-case
	  (ab
	    (declare-ignorable-icp-arguments value-type)
	    (cond
	      (current-subobject?
	       (g2-add-leaf-to-remote-object
		 current-subobject?
		 attribute-type
		 attribute-qualifier?
		 attribute-name-or-index
		 attribute-value))
	      (t (record-object-building-problem-on-receiving-side 
		   'premature-attribute-value
		   attribute-qualifier?
		   attribute-name-or-index
		   nil))))
	  ((gsi telewindows)
	    (gsi-add-leaf-to-item-instance
	      current-subobject?
	      attribute-type
	      attribute-qualifier?
	      attribute-name-or-index
	      attribute-value
	      value-type)))))))
  
(def-icp-value-protocol (add-circular-attribute 2
                         :protocol-name resumable-object-portion)
    (attribute-spec? corresponding-index)
  :writer
  (progn
    (write-icp-attribute-spec? attribute-spec?)
    (write-icp-fixnum corresponding-index))
  :reader
  (multiple-value-bind
      (attribute-type attribute-qualifier? attribute-name-or-index)
      (read-icp-attribute-spec?)
    (let ((handle (read-icp-fixnum))
	  (current-subobject? (current-resumable-subobject-being-built?
				current-receiving-resumable-object)))
      (runtime-current-system-case
	(ab
	  (cond
	    (current-subobject?
	     (let ((object-from-handle? 
		    (get-resumable-instance-node-from-icp-port
		      current-icp-port
		      handle)))
	       (cond
		 (object-from-handle?
		  (cond
		    ((memq attribute-type '(vector-element list-element))
		     (g2-add-leaf-to-remote-object
		       current-subobject?
		       attribute-type
		       attribute-qualifier?
		       attribute-name-or-index
		       object-from-handle?))
		    (t (record-object-building-problem-on-receiving-side
			 'circular-object-not-in-list-or-array
			 attribute-qualifier?
			 attribute-name-or-index
			 nil))))
		 (t (record-object-building-problem-on-receiving-side
		      'cannot-locate-network-registered-object
		      attribute-qualifier?
		      attribute-name-or-index
		      nil)))))
	    (t (record-object-building-problem-on-receiving-side 
		 'premature-circular-attribute
		 attribute-qualifier?
		 attribute-name-or-index
		 nil))))
      ((gsi telewindows)
	(gsi-add-leaf-to-item-instance
	  current-subobject?
	  attribute-type
	  attribute-qualifier?
	  attribute-name-or-index
	  (get-resumable-instance-node-from-icp-port
		      current-icp-port
		      handle)
	  circular-reference-tag))))))




;;;; [14.3.4.2] Resumable Object Protocols

(def-icp-value-protocol (add-attribute-object 3
                         :protocol-name resumable-object-portion)
    (attribute-spec?
      class-name
      corresponding-index-of-class-name?
      symbolic-attribute-count)
  :writer
  (progn
    (write-icp-attribute-spec? attribute-spec?)
    (write-icp-possibly-interned-symbol
      class-name
      corresponding-index-of-class-name?)
    (write-icp-fixnum symbolic-attribute-count))
  :reader
  (multiple-value-bind
      (attribute-type attribute-qualifier? attribute-name-or-index)
      (read-icp-attribute-spec?)
    (let* ((class-name (read-icp-possibly-interned-symbol))
	   (symbolic-attribute-count (read-icp-fixnum)))
      (runtime-current-system-case
	(ab
	  (declare-ignorable-icp-arguments symbolic-attribute-count)
	  (g2-build-remote-object
	    attribute-type
	    attribute-qualifier?
	    attribute-name-or-index
	    class-name))
	((gsi telewindows)
	  (gsi-build-item-instance
	    attribute-type
	    attribute-qualifier?
	    attribute-name-or-index
	    class-name
	    gsi-null-type-tag
	    0
	    symbolic-attribute-count))))))

(def-icp-value-protocol (add-resumable-circularity 16
                         :protocol-name resumable-object-portion)
    (corresponding-index)
  :writer
  (write-icp-fixnum corresponding-index)
  :reader
  (let ((corresponding-index (read-icp-fixnum)))
    (runtime-current-system-case
      (ab
	(g2-add-resumable-circularity corresponding-index))
      ((gsi telewindows)
	(gsi-add-resumable-circularity corresponding-index)))))



(def-icp-value-protocol (add-attribute-object-vector 4
                         :protocol-name resumable-object-portion)
    (attribute-spec?
      class-name
      corresponding-index-of-class-name?
      symbolic-attribute-count
      resumable-vector-length)
  :writer
  (progn
    (write-icp-attribute-spec? attribute-spec?)
    (write-icp-possibly-interned-symbol
      class-name
      corresponding-index-of-class-name?)
    (write-icp-fixnum symbolic-attribute-count)
    (write-icp-fixnum resumable-vector-length))
  :reader
  (multiple-value-bind
      (attribute-type attribute-qualifier? attribute-name-or-index)
      (read-icp-attribute-spec?)
    (let* ((class-name (read-icp-possibly-interned-symbol))
	   (symbolic-attribute-count (read-icp-fixnum))
	   (resumable-vector-length (read-icp-fixnum)))
      (runtime-current-system-case
	(ab
	  (g2-receive-add-attribute-object-vector
	    attribute-type
	    attribute-qualifier?
	    attribute-name-or-index
	    class-name
	    symbolic-attribute-count
	    resumable-vector-length))
	((gsi telewindows)
	  (gsi-build-item-instance
	    attribute-type
	    attribute-qualifier?
	    attribute-name-or-index
	    class-name
	    gsi-item-array-type-tag
	    resumable-vector-length
	    symbolic-attribute-count))))))

(defun-void write-icp-resumable-sequence-element-type (element-type)
  (write-icp-byte
    (case element-type
      (integer     attribute-value-integer-tag)
      (long        attribute-value-long-tag)
      (|float|     attribute-value-float-tag)
      (text        attribute-value-text-tag)
      (truth       attribute-value-truth-value-tag)
      (symbol      attribute-value-symbol-tag)
      (otherwise   unknown-value-vector-element-type-tag))))

(defun-simple read-icp-resumable-sequence-element-type ()
  (let ((tag (read-icp-byte)))
    (case tag
      (#.attribute-value-integer-tag     'integer)
      (#.attribute-value-long-tag        'long)
      (#.attribute-value-float-tag       '|float|)
      (#.attribute-value-text-tag        'text)
      (#.attribute-value-truth-value-tag 'truth)
      (#.attribute-value-symbol-tag      'symbol)
      (#.unknown-value-vector-element-type-tag nil)
      #+development
      (otherwise
       (cerror "Continue, returning nil ~
                (This behavior is what the user would get)"
	       "READ-ICP-RESUMABLE-SEQUENCE-ELEMENT-TYPE: unknown tag ~s"
	       tag)
       nil))))
  
(def-icp-value-protocol (add-attribute-value-vector 5
                         :protocol-name resumable-object-portion)
  (attribute-spec?
    class-name
    corresponding-index-of-class-name?
    symbolic-attribute-count
    element-type
    resumable-vector-length)
  :writer
  (progn
    (write-icp-attribute-spec? attribute-spec?)
    (write-icp-possibly-interned-symbol
      class-name
      corresponding-index-of-class-name?)
    (write-icp-fixnum symbolic-attribute-count)
    (write-icp-resumable-sequence-element-type element-type)
    (write-icp-fixnum resumable-vector-length))
  :reader
  (multiple-value-bind
      (attribute-type attribute-qualifier? attribute-name-or-index)
      (read-icp-attribute-spec?)
    (let* ((class-name (read-icp-possibly-interned-symbol))
	   (symbolic-attribute-count (read-icp-fixnum))
	   (element-type (read-icp-resumable-sequence-element-type))
	   (resumable-vector-length (read-icp-fixnum)))
      (runtime-current-system-case
	(ab (g2-receive-add-attribute-value-vector
	      attribute-type
	      attribute-qualifier?
	      attribute-name-or-index
	      class-name
	      symbolic-attribute-count
	      element-type
	      resumable-vector-length))
	((gsi telewindows)
	  (gsi-build-item-instance
	    attribute-type
	    attribute-qualifier?
	    attribute-name-or-index
	    class-name
	    (gsi-array-type-from-g2-element-type element-type)
	    resumable-vector-length
	    symbolic-attribute-count))))))



(defun write-icp-history-spec (history-spec)
  (gensym-dstruct-bind ((nil datapoint-count? datapoint-age? granularity?)
		       history-spec)
    (if datapoint-count?
	(write-icp-fixnum datapoint-count?)
	(write-icp-fixnum no-history-spec-value))
    (if datapoint-age?
	(write-icp-fixnum datapoint-age?)
	(write-icp-fixnum no-history-spec-value))
    (if granularity?
	(write-icp-fixnum granularity?)
	(write-icp-fixnum no-history-spec-value))))

(defun read-icp-history-spec ()
  (let* ((datapoint-count (read-icp-fixnum))
	 (datapoint-age (read-icp-fixnum))
	 (granularity (read-icp-fixnum)))
    (values
      (if (=f no-history-spec-value datapoint-count)
	  nil
	  datapoint-count)
      (if (=f no-history-spec-value datapoint-age)
	  nil
	  datapoint-age)
      (if (=f no-history-spec-value granularity)
	  nil
	  granularity))))
  
(def-icp-value-writer evaluation-quantity-or-nil
  (cond
    ((null evaluation-quantity-or-nil)
     (write-icp-byte attribute-value-null-tag))
    ((fixnump evaluation-quantity-or-nil)
     (write-icp-byte attribute-value-integer-tag)
     (write-icp-fixnum evaluation-quantity-or-nil))
    ((managed-float-p evaluation-quantity-or-nil)
     (write-icp-byte attribute-value-float-tag)
     (write-icp-managed-double-float evaluation-quantity-or-nil))
    ((managed-long-p evaluation-quantity-or-nil)
     (write-icp-byte attribute-value-long-tag)
     (write-icp-managed-long evaluation-quantity-or-nil))
    #+development
    (t (cerror "Continue, writing nothing ~
                (This behavior is what the user would get"
	       "WRITE-ICP-EVALUATION-QUANTITY-OR-NIL: ~
                Unexpected type (neither evaluation-quantity nor nil) for ~a"
	       evaluation-quantity-or-nil))))

(defmacro body-of-read-icp-evaluation-quantity-or-nil ()
  `(let ((tag (read-icp-byte)))
     (case tag
       (,attribute-value-null-tag nil)
       (,attribute-value-integer-tag  (read-icp-fixnum))
       (,attribute-value-float-tag (read-icp-managed-double-float))
       (,attribute-value-long-tag (read-icp-managed-long))
       (otherwise
	,@(if (eval-feature :development)
	      `((cerror
		  "Continue, returning nil ~
                   (This behavior is what the user would get)"
		  "READ-ICP-EVALUATION-QUANTITY-OR-NIL: unknown tag ~s"
		  tag))
	      nil)))))

(def-icp-value-reader evaluation-quantity-or-nil
  (body-of-read-icp-evaluation-quantity-or-nil))

(defun write-icp-dynamic-history-info (dynamic-history-info)
  (gensym-dstruct-bind
      ((base-time? lowest-ever? highest-ever? time-at-start?)
       dynamic-history-info)
    (write-icp-evaluation-quantity-or-nil base-time?)
    (write-icp-evaluation-quantity-or-nil lowest-ever?)
    (write-icp-evaluation-quantity-or-nil highest-ever?)
    (write-icp-evaluation-quantity-or-nil time-at-start?)))

(defun read-icp-dynamic-history-info ()
  (let* ((base-time? (read-icp-evaluation-quantity-or-nil))
	 (lowest-ever? (read-icp-evaluation-quantity-or-nil))
	 (highest-ever? (read-icp-evaluation-quantity-or-nil))
	 (time-at-start? (read-icp-evaluation-quantity-or-nil)))
    (values base-time? lowest-ever? highest-ever? time-at-start?)))




(def-icp-value-protocol (add-attribute-history-object 17
                         :protocol-name resumable-object-portion)
    (attribute-spec?
      class-name
      corresponding-index-of-class-name?
      symbolic-attribute-count
      element-type?
      resumable-history-length
      resumable-history-spec
      dynamic-history-info
      timestamps-use-float-array-p
      values-use-float-array-p
      )
  :writer
  (progn
    (write-icp-attribute-spec? attribute-spec?)
    (write-icp-possibly-interned-symbol
      class-name
      corresponding-index-of-class-name?)
    (write-icp-fixnum symbolic-attribute-count)
    (write-icp-resumable-sequence-element-type element-type?)
    (write-icp-fixnum resumable-history-length)
    (write-icp-boolean timestamps-use-float-array-p)
    (write-icp-boolean values-use-float-array-p)
    (write-icp-history-spec resumable-history-spec)
    (write-icp-dynamic-history-info dynamic-history-info))
  :reader
  (multiple-value-bind
      (attribute-type attribute-qualifier? attribute-name-or-index)
      (read-icp-attribute-spec?)
    (let* ((class-name (read-icp-possibly-interned-symbol))
	   (symbolic-attribute-count (read-icp-fixnum))
	   (element-type? (read-icp-resumable-sequence-element-type))
	   (resumable-history-length (read-icp-fixnum))
	   (timestamps-use-float-array-p (read-icp-boolean))
	   (values-use-float-array-p (read-icp-boolean)))
      (multiple-value-bind (datapoint-count datapoint-age granularity)
	  (read-icp-history-spec)
	(multiple-value-bind
	    (base-time lowest-ever? highest-ever? time-at-start?)
	    (read-icp-dynamic-history-info)
	  (runtime-current-system-case
	    (ab (g2-receive-add-attribute-history-object
		  attribute-type
		  attribute-qualifier?
		  attribute-name-or-index
		  class-name
		  symbolic-attribute-count
		  element-type?
		  resumable-history-length
		  timestamps-use-float-array-p
		  values-use-float-array-p
		  datapoint-count
		  datapoint-age
		  granularity
		  base-time
		  lowest-ever?
		  highest-ever?
		  time-at-start?))
	    ((gsi telewindows)
	      (declare-ignorable-icp-arguments 
		  values-use-float-array-p timestamps-use-float-array-p)
	      (when lowest-ever?
		(reclaim-managed-float lowest-ever?))
	      (when highest-ever?
		(reclaim-managed-float highest-ever?))
	      (when time-at-start?
		(reclaim-managed-float time-at-start?))
	      (let* ((new-history-item (gsi-build-item-instance
					 attribute-type
					 attribute-qualifier?
					 attribute-name-or-index
					 class-name
					 gsi-null-type-tag
					 0
					 symbolic-attribute-count))
		     (type (if element-type?
			       (gsi-type-from-g2-element-type element-type?)
			       gsi-value-type-tag)))
		(set-gsi-instance-value-type new-history-item type)
		(setf (gsi-instance-history new-history-item)
		      (make-gsi-history new-history-item
					resumable-history-length
					nil
					nil
					base-time
					datapoint-count
					datapoint-age
					granularity))))))))))




(def-icp-value-protocol (add-attribute-object-list 6
                         :protocol-name resumable-object-portion)
    (attribute-spec?
      class-name
      corresponding-index-of-class-name?
      symbolic-attribute-count
      resumable-list-length)
  :writer
  (progn
    (write-icp-attribute-spec? attribute-spec?)
    (write-icp-possibly-interned-symbol
      class-name
      corresponding-index-of-class-name?)
    (write-icp-fixnum symbolic-attribute-count)
    (write-icp-fixnum resumable-list-length))
  :reader
  (multiple-value-bind
      (attribute-type attribute-qualifier? attribute-name-or-index)
      (read-icp-attribute-spec?)
    (let* ((class-name (read-icp-possibly-interned-symbol))
	   (symbolic-attribute-count (read-icp-fixnum))
	   (resumable-list-length (read-icp-fixnum)))
      (runtime-current-system-case
	(ab (g2-receive-add-attribute-object-list
	      attribute-type
	      attribute-qualifier?
	      attribute-name-or-index
	      class-name 
	      symbolic-attribute-count
	      resumable-list-length))
	((gsi telewindows)
	  (gsi-build-item-instance
	    attribute-type
	    attribute-qualifier?
	    attribute-name-or-index
	    class-name
	    gsi-item-list-type-tag
	    resumable-list-length
	    symbolic-attribute-count))))))




(def-icp-value-protocol (add-attribute-value-list 7
                         :protocol-name resumable-object-portion)
  (attribute-spec?
    class-name
    corresponding-index-of-class-name?
    symbolic-attribute-count
    element-type
    resumable-list-length)
  :writer
  (progn
    (write-icp-attribute-spec? attribute-spec?)
    (write-icp-possibly-interned-symbol
      class-name
      corresponding-index-of-class-name?)
    (write-icp-fixnum symbolic-attribute-count)
    (write-icp-resumable-sequence-element-type element-type)
    (write-icp-fixnum resumable-list-length))
  :reader
  (multiple-value-bind
      (attribute-type attribute-qualifier? attribute-name-or-index)
      (read-icp-attribute-spec?)
    (let* ((class-name (read-icp-possibly-interned-symbol))
	   (symbolic-attribute-count (read-icp-fixnum))
	   (element-type (read-icp-resumable-sequence-element-type))
	   (resumable-list-length (read-icp-fixnum)))
      (runtime-current-system-case
	(ab (g2-receive-add-attribute-value-list
	      attribute-type
	      attribute-qualifier?
	      attribute-name-or-index
	      class-name
	      symbolic-attribute-count
	      element-type
	      resumable-list-length))
	((gsi telewindows)
	  (gsi-build-item-instance
	    attribute-type
	    attribute-qualifier?
	    attribute-name-or-index
	    class-name
	    (gsi-list-type-from-g2-element-type element-type)
	    resumable-list-length
	    symbolic-attribute-count))))))




(def-icp-value-protocol (add-value-vector-range 8  ; heterogenous arrays only
                         :protocol-name resumable-object-portion)
    (number-of-elements resumable-node interning-details?)
  :writer
  (runtime-current-system-case
    (ab (g2-send-add-value-vector-range
	  number-of-elements
	  resumable-node
	  interning-details?))
    ((gsi telewindows)
	 (declare-ignorable-icp-arguments
	   number-of-elements
	   resumable-node
	   interning-details?)
      ;; ...
      ))
  :reader
  (let* ((number-of-elements (read-icp-fixnum))
	 (highest-index (read-icp-fixnum)))
    (runtime-current-system-case
      (ab (g2-receive-add-value-vector-range number-of-elements highest-index))
      ((gsi telewindows)
	(loop with item = (current-resumable-subobject-being-built?
			    current-receiving-resumable-object)
	      with item-value = (gsi-instance-value item)
	      repeat number-of-elements
	      for index fixnum downfrom (+f highest-index gsi-magic-offset)
	      do 
	  (multiple-value-bind (attribute-value value-type)
	      (read-icp-attribute-value)
	    (setf (gsi-managed-svref item-value index)
		  (make-gsi-instance (gsi-type-from-leaf-type value-type)
				     attribute-value)))
	      finally
		(incff (gsi-element-count item) number-of-elements))))))



(def-icp-value-protocol (add-homogeneous-value-vector-range 14
                         :protocol-name resumable-object-portion)
    (number-of-elements element-type resumable-node interning-details?)
  :writer
  (runtime-current-system-case
    (ab (g2-send-add-homogeneous-value-vector-range
	  number-of-elements
	  element-type
	  resumable-node
	  interning-details?))
    ((gsi telewindows)
	 (declare-ignorable-icp-arguments
	   number-of-elements
	   element-type
	   resumable-node
	   interning-details?)
      ;; ...
      ))
  :reader
  (let* ((number-of-elements (read-icp-fixnum))
	 (element-type (read-icp-resumable-sequence-element-type))
	 (highest-index (read-icp-fixnum)))
    (runtime-current-system-case
      (ab
	(g2-receive-add-homogeneous-value-vector-range
	  number-of-elements
	  element-type
	  highest-index))
      ((gsi telewindows)
	(let* ((item (current-resumable-subobject-being-built?
		       current-receiving-resumable-object))
	       (item-value (gsi-instance-value item)))
	  (macrolet ((typed-read-icp-values-into-array-1 (element-type)
		       `(loop repeat number-of-elements
			      for index fixnum downfrom highest-index		  
			      do
			  (setf (typed-vector-aref ,element-type item-value index)
				(typed-read-icp-value-to-c-element ,element-type)))))
	    (gsi-array-element-type-case (gsi-type-from-g2-element-type element-type)
					 typed-read-icp-values-into-array-1))
	  (incff (gsi-element-count item) number-of-elements))))))




(def-icp-value-protocol (add-history-range 18
                         :protocol-name resumable-object-portion)
    (resumable-node
      number-of-cached-elements
      cached-interning-details?
      ring-index-of-first-uncached-element
      number-of-uncached-elements
      uncached-interning-details?
      timestamps-use-float-array-p
      values-use-float-array-p)
  :writer
  (progn
    (write-icp-boolean timestamps-use-float-array-p)
    (write-icp-boolean values-use-float-array-p)
    (write-icp-fixnum
      (+f number-of-cached-elements number-of-uncached-elements))
    (runtime-current-system-case
      (ab
	(g2-transmit-add-history-range
	  resumable-node
	  number-of-cached-elements
	  cached-interning-details?
	  ring-index-of-first-uncached-element
	  number-of-uncached-elements
	  uncached-interning-details?
	  timestamps-use-float-array-p
	  values-use-float-array-p))
      ((gsi telewindows)
	(declare-ignorable-icp-arguments
	  resumable-node cached-interning-details?
	  ring-index-of-first-uncached-element uncached-interning-details?))))
  :reader
  (let* ((timestamps-use-float-array-p (read-icp-boolean))
	 (values-use-float-array-p (read-icp-boolean))
	 (number-of-elements (read-icp-fixnum)))
    (runtime-current-system-case
      (ab
	(g2-receive-add-history-range
	  timestamps-use-float-array-p
	  values-use-float-array-p
	  number-of-elements))
      ((gsi telewindows)
	(gsi-receive-add-history-range
	  timestamps-use-float-array-p
	  values-use-float-array-p 
	  number-of-elements)))))

(def-icp-value-protocol (add-homogeneous-history-range 19
                         :protocol-name resumable-object-portion)
    (resumable-node
      number-of-cached-elements
      element-type
      cached-interning-details?
      ring-index-of-first-uncached-element
      number-of-uncached-elements
      uncached-interning-details?
      timestamps-use-float-array-p)
  :writer
  (progn
    (write-icp-boolean timestamps-use-float-array-p)
    (write-icp-resumable-sequence-element-type element-type)
    (write-icp-fixnum
      (+f number-of-cached-elements number-of-uncached-elements))
    (runtime-current-system-case
      (ab
	(g2-transmit-add-homogeneous-history-range
	  resumable-node
	  element-type
	  number-of-cached-elements
	  cached-interning-details?
	  ring-index-of-first-uncached-element
	  number-of-uncached-elements
	  uncached-interning-details?
	  timestamps-use-float-array-p))
      ((gsi telewindows)
	(declare-ignorable-icp-arguments
	  resumable-node cached-interning-details?
	  ring-index-of-first-uncached-element uncached-interning-details?))))
  :reader
  (let* ((timestamps-use-float-array-p (read-icp-boolean))
	 (element-type (read-icp-resumable-sequence-element-type))
	 (number-of-elements (read-icp-fixnum)))
    (runtime-current-system-case
      (ab
	(g2-receive-add-homogeneous-history-range
	  timestamps-use-float-array-p
	  element-type
	  number-of-elements))
      ((gsi telewindows)
	(gsi-receive-add-homogeneous-history-range
	  timestamps-use-float-array-p
	  element-type
	  number-of-elements)))))



(def-icp-value-protocol (add-value-list-range 9
                         :protocol-name resumable-object-portion)
    (number-of-elements resumable-node interning-details?)
  :writer
  (runtime-current-system-case
    (ab (g2-send-add-value-list-range
	  number-of-elements
	  resumable-node
	  interning-details?))
    ((gsi telewindows)
	 (declare-ignorable-icp-arguments
	   number-of-elements
	   resumable-node
	   interning-details?)
      ;; ...
      ))
  :reader
  (let ((number-of-elements (read-icp-fixnum)))
    (runtime-current-system-case
      (ab (g2-receive-add-value-list-range number-of-elements))
      ((gsi telewindows)
	(loop with item = (current-resumable-subobject-being-built?
			    current-receiving-resumable-object)
	      with list = (gsi-instance-value item)
	      repeat number-of-elements
	      for index fixnum
	      from (+f (gsi-element-count item) gsi-magic-offset)
	      do
	  (multiple-value-bind (attribute-value value-type)
	      (read-icp-attribute-value)
	    (setf (gsi-managed-svref list index)
		  (make-gsi-instance (gsi-type-from-leaf-type value-type)
				     attribute-value)))
	      finally
		(incff (gsi-element-count item) number-of-elements))))))



(def-icp-value-protocol (add-homogeneous-value-list-range 15
                         :protocol-name resumable-object-portion)
    (number-of-elements element-type resumable-node interning-details?)
  :writer
  (runtime-current-system-case
    (ab (g2-send-add-homogeneous-value-list-range
	  number-of-elements
	  element-type
	  resumable-node
	  interning-details?))
    ((gsi telewindows)
	 (declare-ignorable-icp-arguments
	   number-of-elements
	   element-type
	   resumable-node
	   interning-details?)
      ;; ...
      ))
  :reader
  (let* ((number-of-elements (read-icp-fixnum))
	 (element-type (read-icp-resumable-sequence-element-type)))
    (runtime-current-system-case
      (ab (g2-receive-add-homogeneous-value-list-range
	    number-of-elements
	    element-type))
      ((gsi telewindows)
	(let* ((item (current-resumable-subobject-being-built?
		       current-receiving-resumable-object))
	       (item-value (gsi-instance-value item))
	       (next-index (gsi-element-count item)))
	  (macrolet ((typed-read-icp-values-into-array-2 (element-type)
		       `(loop repeat number-of-elements
			      for index fixnum from next-index
			      do
			  (setf (typed-vector-aref ,element-type item-value index)
				(typed-read-icp-value-to-c-element ,element-type)))))
	    (gsi-array-element-type-case (gsi-type-from-g2-element-type element-type)
					 typed-read-icp-values-into-array-2))
	  (incff (gsi-element-count item) number-of-elements))))))


(def-icp-value-protocol (ascend-to-parent 10
                         :protocol-name resumable-object-portion)
    (ascension-count)
  :writer (write-icp-fixnum ascension-count)
  :reader
  (let ((ascension-count (read-icp-fixnum)))
    (runtime-current-system-case
      (ab
	(g2-ascend-to-parent ascension-count))
      ((gsi telewindows)
	(loop repeat ascension-count
	      with ancestor = (current-resumable-subobject-being-built?
				current-receiving-resumable-object)
	      do
	  (setq ancestor (gsi-superior-item ancestor))
	      finally
		(setf (current-resumable-subobject-being-built?
			current-receiving-resumable-object)
		      ancestor))))))



;;;; [14.3.5] RPC Argument Protocols



(def-icp-value-protocol (suspend-building-object 11
                         :protocol-name resumable-object-portion
			 :allowing-unwind-p t)
    (bandwidth-consumed)
  :writer (progn
	    (write-icp-fixnum bandwidth-consumed))
  :reader
  (let ((bandwidth-consumed (read-icp-fixnum)))
    (when (>f bandwidth-consumed 0)
      (writing-icp-message-group ((icp-output-port current-icp-socket))
	(send-icp-update-object-passing-network-resources
	  bandwidth-consumed
	  no-resumable-object-index
	  nil)))
    (stop-reading-icp-value-using-protocol resumable-object-portion))
  )

(def-icp-value-protocol (finish-building-object 12
                         :protocol-name resumable-object-portion
			 :allowing-unwind-p t)
    (bandwidth-consumed)
  :writer
  (progn
    (write-icp-fixnum bandwidth-consumed))
  :reader
  (let ((bandwidth-consumed (read-icp-fixnum)))
    (receive-finish-building-object bandwidth-consumed)))

(def-icp-value-protocol (abort-building-object 13
                         :protocol-name resumable-object-portion
			 :allowing-unwind-p t)
    (bandwidth-consumed)
  :writer
  (progn 
    (write-icp-fixnum bandwidth-consumed))
  :reader
  (let* ((bandwidth-consumed (read-icp-fixnum))
	 (resumable-object-index
	   (corresponding-index-of-self current-receiving-resumable-object))
	 (resumable-instance-node-indices
	   (corresponding-indices-of-subobjects
	     current-receiving-resumable-object)))
    (writing-icp-message-group ((icp-output-port current-icp-socket))
      (send-icp-update-object-passing-network-resources
	bandwidth-consumed
	resumable-object-index
	resumable-instance-node-indices))
    (reclaim-receiving-resumable-object
      current-receiving-resumable-object)
    (stop-reading-icp-value-using-protocol resumable-object-portion))
  )




;;;; [14.4] ICP Reader and Writer for Partial Resumable Object 

;;; A sending-resumable-object structure is passed to the ICP value writer for
;;; resumable-object-portion.  The ICP value writer sends the corresponding ICP
;;; object index of this structure to the ICP value reader for
;;; resumable-object-portion.  The various ICP message handlers which have
;;; resumable-object-portion arguments locate the corresponding
;;; receiving-resumable-object structure, binds it to the special variable
;;; current-receiving-resumable-object, and accept ICP bytes according to the
;;; resumable-object-portion protocol (defined by the various
;;; def-icp-value-protocol forms in this file) via a
;;; read-icp-value-using-protocol form

(def-icp-value-writer resumable-object-portion
  (write-icp-fixnum
    (runtime-current-system-case
      (ab (get-icp-object-index-for-resumable-object
	    resumable-object-portion ;a sending-resumable-object structure
	    current-icp-port))
      ((gsi telewindows) 
	   (get-icp-object-index-for-gsi-instance
	    resumable-object-portion ;a gsi-instance in fact, hee hee
	    current-icp-port)))))

(def-icp-value-reader resumable-object-portion
  (read-icp-fixnum))

  


;;;; [16] ICP Message to Build Resumable Objects

(def-icp-value-writer resumable-node-indices
  (let ((length (length resumable-node-indices)))
    (write-icp-fixnum length)
    (loop for index in resumable-node-indices
	  do
      (write-icp-fixnum index))))

(def-icp-value-reader resumable-node-indices
  (let ((length (read-icp-fixnum)))
    (loop for count from 1 to length
	  collect (read-icp-fixnum) using icp-cons)))

(defmacro def-icp-index-reclaimer (icp-object-type)
  (let ((name-of-reclaimer
	  (intern (format nil "RECLAIM-INDEX-FOR-~a" icp-object-type)))
	(name-of-index-space
	  (name-of-corresponding-icp-object-index-space icp-object-type)))
    `(defun-void ,name-of-reclaimer (index output-port-p)
       (let* ((index-space-name (index-space-name-for-icp-port
				  ',name-of-index-space
				  current-icp-port))
	      (index-space (index-space-for-icp-port index-space-name current-icp-port)))
	 (if (eq index-space-name 'frame-serial-number)
	     (setf (get-item-from-frame-serial-number index index-space) nil)
	     (setf (get-object-from-index-space index-space index) nil))
	 (when output-port-p
	   (if (eq index-space-name 'frame-serial-number)
	       (delete-item-from-frame-serial-number-table index index-space)
	       (deassign-index-in-index-space index index-space)))))))

(def-icp-index-reclaimer resumable-object)
(def-icp-index-reclaimer resumable-instance-node)

(defun reclaim-indices-associated-with-resumable-object
    (resumable-object-index resumable-instance-node-indices output-port-p)
  (when (/=f resumable-object-index no-resumable-object-index)
    (reclaim-index-for-resumable-object resumable-object-index output-port-p))
  (loop for index in resumable-instance-node-indices
	do (reclaim-index-for-resumable-instance-node index output-port-p))
  (reclaim-icp-list resumable-instance-node-indices))

(defun receive-finish-building-object (bandwidth-consumed)
  (let ((resumable-object-index
	  (corresponding-index-of-self current-receiving-resumable-object))
	(resumable-instance-node-indices
	  (corresponding-indices-of-subobjects
	    current-receiving-resumable-object)))
    (writing-icp-message-group ((icp-output-port current-icp-socket))
      (send-icp-update-object-passing-network-resources
	bandwidth-consumed resumable-object-index
	resumable-instance-node-indices))
    (reclaim-indices-associated-with-resumable-object
      resumable-object-index resumable-instance-node-indices nil))
  (let ((rpc-arglist-structure?
	  (enclosing-rpc-arglist-structure?
	    current-receiving-resumable-object)))
    (cond
      ;; Being built as an RPC object ...
      (rpc-arglist-structure?
       (runtime-current-system-case
	 ((ab)
	  (g2-maybe-continue-rpc-after-object-building rpc-arglist-structure?))
	 ((gsi telewindows)
	  (gsi-check-if-all-items-are-built rpc-arglist-structure?))))
      (t #+development
	 (cerror "Continue, taking no action ~
                    (This behavior is what the user would get)"
		 "READ-ICP-FINISH-BUILDING-OBJECT: ~
                    resumable object ~a has no continuation"
		 current-receiving-resumable-object))))
  (stop-reading-icp-value-using-protocol resumable-object-portion))

(def-icp-message-type update-object-passing-network-resources
    ((fixnum freed) (fixnum resumable-object-index) resumable-node-indices)
  (let ((current-icp-port (icp-output-port current-icp-socket)))
    (reclaim-indices-associated-with-resumable-object
      resumable-object-index resumable-node-indices t))
  (incff (available-bandwidth-for-object-passing current-icp-socket) freed)
  (runtime-current-system-case
    (ab (g2-resume-clogged-resumable-object-tasks))
    ((gsi telewindows)
      ;; ...
      )))


;; jh, 8/16/94.  We now bind do-not-initialize-g2-array-elements-p in
;; body-of-continue-building-resumable-object.  Without this binding, the
;; receiving side will provide initial elements of the passed array, which are
;; then immediately overwritten by the values provided by
;; add-value-vector-range.  In the case of quantity-, truth-value-, or
;; text-arrays, this caused a leak.

(defun-allowing-unwind body-of-continue-building-resumable-object
    (resumable-object-portion)
  (let ((resumable-object? (get-resumable-object-from-icp-port
			     current-icp-port
			     resumable-object-portion)))
    (when resumable-object? ; else out of synch, no?  JH?
      (let ((current-receiving-resumable-object resumable-object?)
	    (do-not-initialize-g2-array-elements-p t)
	    (toplevel-object?
	      (resumable-object-being-built? resumable-object?)))
	(declare (special do-not-initialize-g2-array-elements-p))
	(when (and toplevel-object?
		   (runtime-current-system-case
		     (ab (g2-resumable-object-reprocessed-p
			   toplevel-object?
			   resumable-object?))
		     ((gsi telewindows) t)))
	  (record-object-building-problem-on-receiving-side
		 'toplevel-object-has-been-deleted-on-receiving-side
		 nil
		 nil
		 nil))
	(read-icp-value-using-protocol resumable-object-portion)))))

(def-icp-message-type continue-building-resumable-object
    (resumable-object-portion)
  (body-of-continue-building-resumable-object resumable-object-portion))
  



;;;; [17] New RPC-related ICP messages

;;; [17.1]    Object-passing ICP messages

(defun-void gsi-record-rpc-name-in-all-receiving-resumable-objects
    (remote-procedure-name item)
  (loop for my-item? first item
		     then (next-resumable-object-in-rpc-arglist? my-item?)
	while my-item?
	do
    (setf (resumable-object-rpc-name? my-item?)
	  (remote-procedure-name-symbol remote-procedure-name))))

(defun-void g2-record-rpc-name-in-all-receiving-resumable-objects
    (remote-procedure-name rpc-argument-list)
  (let ((typical-resumable-object?
	  (loop for argument in rpc-argument-list
		when (receiving-resumable-object-p argument)
		  do (return argument))))
    (when typical-resumable-object?
      (mapping-across-resumable-object-siblings (typical-resumable-object?)
        (setf (resumable-object-rpc-name? typical-resumable-object?)
	      (remote-procedure-name-symbol remote-procedure-name))))))

(defun-void twrite-gsi-rpc-backtrace-info ()
  (twrite-string "  RPC: ")
  (twrite (pop-backtrace-information)))

(def-icp-message-type rpc-start
		      (remote-procedure-name rpc-argument-list)
  (runtime-current-system-case
    (ab
      ;; jh, 5/18/95.  Remote-procedure-name-p check necessary to avoid crashes
      ;; caused by GSI 3.0 and 3.1 (see bugs HQ-334071 and HQ-354368).
      (cond
	((not (remote-procedure-name-p remote-procedure-name))
	 (reclaim-unprocessed-rpc-argument-list rpc-argument-list (frame-serial-number-0)))
	(t
	 (let ((remote-procedure-name-symbol
		 (remote-procedure-name-symbol remote-procedure-name))
	       (rpc-argument-list-error nil))
	   (if-object-passing-arguments-let
	     (rpc-arglist-structure rpc-argument-list)
	     ;; ... Not quite right, because values (as opposed to objects) are
	     ;; checked twice, once here and once again when
	     ;; receive-start-or-call-remote-procedure is eventually called.
	     ;;
 	     ;; Note this doesn't leak if
 	     ;; check-that-remote-procedure-can-be-started-or-called fails,
 	     ;; because when the arglist is eventually read, the
 	     ;; continuation-waiting-for-rpc-arglist remains the default, ERROR,
 	     ;; resulting in proper reclamation.
	     (when (or ;; jh, 6/26/96.  The complete check that the method can
		       ;; be called happens after all the objects have been
		       ;; built, in receive-start-or-call-remote-procedure.  It
		       ;; should happen sooner, since we can figure it out
		       ;; sooner.
		       (plausible-remote-method-call-p
			 remote-procedure-name-symbol
			 rpc-argument-list)
		       (check-that-remote-procedure-can-be-started-or-called
			 current-icp-socket
			 remote-procedure-name-symbol
			 rpc-argument-list
			 nil))
	       (setf (rpc-name-waiting-for-rpc-arglist rpc-arglist-structure)
		     remote-procedure-name)
	       (setf (continuation-waiting-for-rpc-arglist rpc-arglist-structure)
		     'start)
	       (g2-record-rpc-name-in-all-receiving-resumable-objects
		 remote-procedure-name
		 rpc-argument-list))
	     (receive-start-or-call-remote-procedure
	       current-icp-socket
	       remote-procedure-name-symbol
	       (icp-cons (frame-serial-number-0) (icp-cons nil rpc-argument-list))
	       nil))))))
    (gsi
     (let ((item-among-arguments? (get-item-from-arguments rpc-argument-list)))
       (cond (item-among-arguments?
	      (let ((rpc-arglist-structure (enclosing-rpc-arglist-structure?
					     item-among-arguments?)))
		(setf (rpc-name-waiting-for-rpc-arglist rpc-arglist-structure)
		      remote-procedure-name)
		(setf (continuation-waiting-for-rpc-arglist rpc-arglist-structure)
		      'start)
		(gsi-record-rpc-name-in-all-receiving-resumable-objects
		  remote-procedure-name
		  item-among-arguments?)
		(setf (receiving-rpc-arglist-reclaim-list rpc-arglist-structure)
		      gsi-reclaim-list?)
		(setf gsi-reclaim-list? nil)))
	     (t
	      (gsi-start-or-call-local-function-or-handle-return-values
		'start
		remote-procedure-name nil rpc-argument-list)
	      (when (eq 'gsi (default-owner-for-gsi-objects))
		(gsi-reclaim-contents-and-clear-list gsi-reclaim-list? 'gsi))))))))

(def-icp-message-type rpc-call
		      (remote-procedure-name
		       remote-procedure-identifier
		       rpc-argument-list)
  (runtime-current-system-case
    (ab
      ;; jh, 5/10/95.  Remote-procedure-identifier-p and -name-p checks
      ;; necessary to avoid crashes caused by GSI 3.0 (see bug HQ-334071).
      (cond
	((and (remote-procedure-identifier-p remote-procedure-identifier)
	      (remote-procedure-name-p remote-procedure-name))
	 (let ((remote-procedure-name-symbol
		 (remote-procedure-name-symbol remote-procedure-name))
	       (rpc-argument-list-error nil))
	   (if-object-passing-arguments-let
	     (rpc-arglist-structure rpc-argument-list)
	     ;; ... Not quite right, because values (as opposed to objects) are
	     ;; checked twice, once here and once again when
	     ;; receive-start-or-call-remote-procedure is eventually called.
	     ;;
 	     ;; jh, 5/23/95.  No leak if
 	     ;; check-that-remote-procedure-can-be-called fails, because when
 	     ;; the arglist is eventually read, the
 	     ;; continuation-waiting-for-rpc-arglist remains the default, ERROR,
 	     ;; resulting in proper reclamation.  We might want to report the
 	     ;; error sooner, however.
	     (when (or ;; jh, 6/26/96.  The complete check that the method can
		       ;; be called happens after all the objects have been
		       ;; built, in receive-start-or-call-remote-procedure.  It
		       ;; should happen sooner, since we can figure it out
		       ;; sooner.
		       (plausible-remote-method-call-p
			 remote-procedure-name-symbol
			 rpc-argument-list)
		       (check-that-remote-procedure-can-be-started-or-called
			 current-icp-socket
			 remote-procedure-name-symbol
			 rpc-argument-list
			 remote-procedure-identifier))
	       (loop for arg in rpc-argument-list
		     when (and (receiving-resumable-object-p arg)
			       (not (transmit-resumable-object-as-handle-p
				      arg)))
		       do (icp-push
			    arg
			    (remote-procedure-identifier-resumable-objects
			      remote-procedure-identifier))
			  (setf (rpc-identifier-for-this-object? arg)
				remote-procedure-identifier))
	       (setf (rpc-name-waiting-for-rpc-arglist rpc-arglist-structure)
		     remote-procedure-name)
	       (setf (rpc-identifier-waiting-for-rpc-arglist
		       rpc-arglist-structure)
		     remote-procedure-identifier)
	       (setf (continuation-waiting-for-rpc-arglist
		       rpc-arglist-structure)
		     'call)
	       (g2-record-rpc-name-in-all-receiving-resumable-objects
		 remote-procedure-name
		 rpc-argument-list))
	     (receive-start-or-call-remote-procedure
	       current-icp-socket
	       remote-procedure-name-symbol
	       (icp-cons (frame-serial-number-0) (icp-cons nil rpc-argument-list))
	       remote-procedure-identifier))))
	(t (reclaim-unprocessed-rpc-argument-list rpc-argument-list (frame-serial-number-0)))))
    (gsi
      (let ((item-among-arguments? (get-item-from-arguments
				     rpc-argument-list)))
	(cond (item-among-arguments?
	       (let ((rpc-arglist-structure (enclosing-rpc-arglist-structure?
					      item-among-arguments?)))
		 (setf (rpc-name-waiting-for-rpc-arglist rpc-arglist-structure)
		       remote-procedure-name)
		 (setf (rpc-identifier-waiting-for-rpc-arglist rpc-arglist-structure)
		       remote-procedure-identifier)
		 (setf (continuation-waiting-for-rpc-arglist rpc-arglist-structure)
		       'call)
		 (gsi-record-rpc-name-in-all-receiving-resumable-objects
		   remote-procedure-name
		   item-among-arguments?)
		 (setf (receiving-rpc-arglist-reclaim-list rpc-arglist-structure)
		       gsi-reclaim-list?)
		 (setf gsi-reclaim-list? nil)))
	      (t
	       (gsi-start-or-call-local-function-or-handle-return-values
		 'call
		 remote-procedure-name remote-procedure-identifier rpc-argument-list)
	       (when (eq 'gsi (default-owner-for-gsi-objects))
		 (gsi-reclaim-contents-and-clear-list gsi-reclaim-list? 'gsi))))))))

(def-icp-message-type rpc-return-values
		      ((unsigned-integer calling-procedure-index)
		       (rpc-argument-list return-values-list))
  (runtime-current-system-case
    (ab
      (if-object-passing-arguments-let
	(rpc-arglist-structure return-values-list)
	;; ... Not quite right, because values (as opposed to objects) are
	;; checked twice, once here and once again when
	;; receive-remote-procedure-values is eventually called.
	;;	
 	;; No leak if check-that-remote-procedure-can-receive-values fails,
 	;; because when the arglist is eventually read, the
 	;; continuation-waiting-for-rpc-arglist remains the default, ERROR,
 	;; resulting in proper reclamation.
	(when (check-that-remote-procedure-can-receive-values
		calling-procedure-index
		return-values-list)
	  (setf (rpc-index-waiting-for-rpc-arglist rpc-arglist-structure)
	      calling-procedure-index)
	  (setf (continuation-waiting-for-rpc-arglist
		  rpc-arglist-structure)
		'return))
	(let ((remote-procedure-identifier
		(lookup-remote-procedure-identifier-from-index calling-procedure-index))
	      (rpc-argument-list-error nil))
	  (when (and remote-procedure-identifier
		     (eq 'outstanding
			 (remote-procedure-identifier-state remote-procedure-identifier)))
	    (setf (remote-procedure-identifier-state remote-procedure-identifier)
		  'returned))
	  (receive-remote-procedure-values
	    remote-procedure-identifier
	    (icp-cons (frame-serial-number-0) (icp-cons nil return-values-list))))))
    (gsi
      (let ((item-among-arguments? (get-item-from-arguments
				     return-values-list))
	    (remote-procedure-identifier
	      (or (lookup-remote-procedure-identifier-from-index calling-procedure-index)
		  (gsi-connection-error 'rpc-return-values
					gsi-unknown-calling-procedure-index))))
	(cond (item-among-arguments?
	       (let ((rpc-arglist-structure (enclosing-rpc-arglist-structure?
					      item-among-arguments?)))
		 (setf (continuation-waiting-for-rpc-arglist rpc-arglist-structure)
		       'return)
		 (setf (rpc-identifier-waiting-for-rpc-arglist rpc-arglist-structure)
		       remote-procedure-identifier)
		 (setf (rpc-index-waiting-for-rpc-arglist rpc-arglist-structure)
		       calling-procedure-index)
		 (setf (receiving-rpc-arglist-reclaim-list rpc-arglist-structure)
		       gsi-reclaim-list?)
		 (setf gsi-reclaim-list? nil)))
	      (t
	       (gsi-start-or-call-local-function-or-handle-return-values
		 'return
		 (gsi-remote-procedure-name-structure
		   (remote-procedure-identifier-caller remote-procedure-identifier))
		 remote-procedure-identifier
		 return-values-list)
	       (when (eq 'gsi (default-owner-for-gsi-objects))
		 (gsi-reclaim-contents-and-clear-list gsi-reclaim-list? 'gsi))))))))

;; RPC-error

(def-icp-message-type rpc-error
                      ((symbol error-name)
                       (unsigned-integer error-level)
                       (text-string error-description)
                       (rpc-argument-list error-argument-list))
  (runtime-current-system-case
    (ab (receive-remote-procedure-error
          current-icp-socket
          error-name
          error-level
          error-description
          error-argument-list))
    ((gsi telewindows)
      (declare-ignorable-icp-arguments error-name)
      (gsi-warning 'rpc_error_handler_1
		 gsi-rpc-error-from-g2
		 error-level
		 error-description)))
  (reclaim-transformed-rpc-argument-list error-argument-list nil))



;; RPC-error-to-caller

(def-icp-message-type rpc-error-to-caller
                      ((unsigned-integer remote-caller-index)
                       (unsigned-integer-or-nil signaller?)
                       (symbol error-name)
                       (unsigned-integer error-level)
                       (text-string error-description)
                       (rpc-argument-list error-argument-list))
  (let ((remote-procedure-identifier
	  (when (<f 0 remote-caller-index)
	    (lookup-remote-procedure-identifier-from-index remote-caller-index))))
    (when (and remote-procedure-identifier
	       (eq 'outstanding
		   (remote-procedure-identifier-state remote-procedure-identifier)))
      (setf (remote-procedure-identifier-state remote-procedure-identifier)
	    'sync-abort))
    (runtime-current-system-case
      (ab error-argument-list
	  (receive-remote-procedure-error-for-caller
	    remote-procedure-identifier
	    signaller?
	    error-name
	    error-level
	    error-description))
      ((gsi telewindows)
       (declare-ignorable-icp-arguments signaller? error-name)
       (let* ((gsi-remote-procedure
		(when remote-procedure-identifier
		  (remote-procedure-identifier-caller
		    remote-procedure-identifier)))
	      (g2-procedure-name
		(procedure-name-in-g2 gsi-remote-procedure)))
	 (gsi-warning 'rpc_error_handler_2
		      gsi-rpc-error-from-g2-procedure
		      g2-procedure-name
		      error-level
		      error-description))))
    (reclaim-transformed-rpc-argument-list error-argument-list nil)))

;;; [17.2]    Item-registration ICP messages (in gsi-common, now)

    

;; End file with [CR]




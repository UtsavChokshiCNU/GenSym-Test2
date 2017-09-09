;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module FRAMES3

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Lowell B. Hawkinson, Stephen R. DeVoy, and Gretchen Wang








;;;; Forward References




(declare-forward-references-to-module
  kb-load1
  frame-flags-revised-function
  (superior-frame-being-cloned? variable))

(declare-forward-references-to-module
  kb-load2
  note-as-preexisting-frame-if-appropriate)

(declare-forward-references-to-module
  kb-save3
  note-change-to-block-2)

(declare-forward-references-to-module
  edit2
  recompile-item)

(declare-forward-references-to-module
  draw
  note-change-to-edges-of-block)

#+development
(declare-forward-references-to-module
  frames5
  get-instance-with-name-if-any)

(declare-forward-references-to-module
  events-g2
  send-ws-representations-item-moved
  send-ws-representations-item-resized)

(declare-forward-references-to-module
  rules
  clear-cached-explanations)

(declare-forward-references-to-module
  grammar7
  explanation-related-features-enabled-func?)




(declare-forward-reference schedule-task-to-invoke-existential-rules function)
(declare-forward-reference called-within-clear-text-loading variable)





;; Improvements and changes, concerning frames, to consider.

;; Consider giving warning messages for slot redefinition by frames not subsummed
;; by the original slot definition.

;; Consider retaining recycled frame vectors when the new class is either the same
;; size or slightly smaller in size than the original. Presently only frame vectors
;; of exactly the right size are retained upon class redefinition.

;;; Defining a class moved to the end of FRAMES1.


 





;;;; Slot Groups and Accessors

;;; Slot groups are a mechanism for collapsing a number of slots in a frame into
;;; one, the value of which is nil when all slots in the group have default
;;; values.  Slot groups are generally implemented as unnamed vector structures.  These 
;;; have 3 words of overhead in the header in Chestnut 1.7, but only one word of
;;; overhead in Chestnut 2.0.  

;;; Define-slot-group-accessor defines accessors and setfs for slots in a slot
;;; group.  Thus, the slots in the slot group can be accessed and set just like
;;; vector and lookup slots.  When converting a group of vector slots to slot
;;; group slots, it is sufficient to use absent slot putters of the form

;;; (def-absent-slot-putter pretty-slot-name (block value)
;;;   (setf (pretty-slot-name block) value))

;;; to convert old kbs to the new slots.

;;; Define-slot-group-accessor should only be used for slot groups in blocks, not
;;; in dependent frames.  This could be extended, if necessary, by noting changes
;;; to dependent frames as well (see expand-class-definition).

;;; Slots in a slot group have some important limitations compared to vector and
;;; lookup slots, however.  All behavior that comes automatically to slots as the
;;; result of features, putters, and reclaimers is not available.  Also, the slots
;;; in a slot group cannot be used in def-class, as vector and lookup slots are,
;;; to define default values for a class.  These are important considerations when
;;; converting vector slots to collapsed slots.

;;; Thus, slot groups should really only be used for slots which do not make much
;;; use of slot features, putters, and reclaimers and which are not often
;;; redefined by def-class.  Such slots typically contain specialized "system"
;;; information, the format of which is simple and relatively stable with regard
;;; to future design changes.  

;;; The icon slot group is a good example of such a group of slots.  Its slots contain information
;;; needed only for graphic representation of icons, and these slots do not make much
;;; use of features, putters, or reclaimers.  It collapses the following slots:

;;; left-edge-of-block
;;; top-edge-of-block
;;; right-edge-of-block
;;; bottom-edge-of-block
;;; subblocks
;;; superblock
;;; connections.

;;; Thus, for blocks which do not have iconic representation (usually a
;;; significant number in a typical knowledge base), 6 words are saved (7 slots
;;; collapsed to one empty one).  For blocks which do have iconic representation,
;;; this technique will increase memory requirements by 2 words for Chestnut 2.0.

;;; In order to save this slot group, the slot-group-for-block?  case has been
;;; added to write-frame-for-kb.  This calls write-slot-group-for-block?  which
;;; writes the subblocks and connections slots of the group.  The superblock slot
;;; is not saved, and the code in write-frame-for-kb which writes the edge of
;;; block slots does not need any changes.
 
;;; In order to read this slot group, the slot-group-for-block?  case has been
;;; added to read-frame-for-kb.  This calls read-slot-group-for-block?  which
;;; reads the subblocks and connections slots of the group.



(defmacro define-slot-group-accessor
	  (accessor-name slot-group-type slot-group-accessor
	   internal-accessor-name default-value slot-is-noteworthy? &optional use-in-cas?)
  (let* ((general-accessor-name
	   (intern (format nil "~a-GENERAL" accessor-name)))
	 (set-name
	   (intern (format nil "SET-~a" accessor-name)))
	 (general-set-name
	   (intern (format nil "SET-~a-GENERAL" accessor-name)))
	 (slot-group-make-name
	   (intern (format nil "MAKE-~a" slot-group-type)))
	 #+SymScale
	 (slot-group-reclaimer-name
	   (when use-in-cas?
	     (intern (format nil "RECLAIM-~a" slot-group-type))))
	 #+SymScale
	 (cas-operator-name
	   (when use-in-cas?
	     (intern (format nil "COMPARE-AND-SWAP-~a" accessor-name)))))
    `(progn

       (defmacro ,general-accessor-name (block)
	 (let ((temp (gensym)))    ; code rearranged; see note below!
	   `(let ((,temp ,@(if ,use-in-cas?
			     `((access-once (,',slot-group-accessor ,block)))
			     `((,',slot-group-accessor ,block)))))
	      (setq ,temp 
		    (if ,temp
			,@(if ,use-in-cas?
			    `((access-once (,',internal-accessor-name ,temp)))
			    `((,',internal-accessor-name ,temp)))
			,,default-value))
	      ,temp)))

       (defmacro ,accessor-name (block)
	 `(,',general-accessor-name ,block))

       (defmacro ,set-name (block value)
	 `(,',general-set-name ,block ,value))

       (defmacro ,general-set-name (block value)
	 (let ((value-of-block (gensym))
	       (value-of-value (gensym)))
	   `(let* ((,value-of-block ,block)
		   ,value-of-value
		   (slot-group? (,',slot-group-accessor ,value-of-block)))
	      ,,(when slot-is-noteworthy?
		  (if (eq slot-is-noteworthy? ':frame)
		      ``(note-change-to-block-or-struct-or-seq
			  ,value-of-block ',',slot-group-accessor)
		      ``(note-change-to-block 
			  ,value-of-block ',',slot-group-accessor)))
	      (setq ,value-of-value ,value)  ; done after note-change-to-block
	      (if slot-group?
		  (setf (,',internal-accessor-name slot-group?) ,value-of-value)
		  (when (not (eql ,value-of-value ,,default-value))
		    (setf (,',slot-group-accessor ,value-of-block)
			  (,',slot-group-make-name))
		    (setf (,',internal-accessor-name
			   (,',slot-group-accessor ,value-of-block))
			  ,value-of-value)))
	      ,value-of-value)))
  
       (defsetf ,accessor-name ,set-name)

       #+SymScale
       ,@(when use-in-cas?
	   `((defun ,cas-operator-name (block old-value new-value)
	       (let ((temp (access-once (,slot-group-accessor block))))
		 (unless temp
		   (setq temp (,slot-group-make-name))
		   (unless (compare-and-swap (,slot-group-accessor block) nil temp)
		     (,slot-group-reclaimer-name temp))
		   (setq temp (access-once (,slot-group-accessor block))))
		 ;; NOTE: at this point, `temp' is the slot group, and
		 ;; the result of CAS is returned directly.
		 (compare-and-swap (,internal-accessor-name temp)
				   old-value new-value)))))
       ',accessor-name)))

(defun note-change-to-block-or-struct-or-seq (block slot-name)
  (when (and noting-changes-to-kb-p (not (consp block))) ; filter out evaluation seqs and structs
     (note-change-to-block-1 block slot-name)))

;; Note: the accessor code above was rearranged just for the sake of a
;; very old GNU C compiler, which could not apparently handle the old
;; code, which had been something more like
;;
;;	   `(let ((,temp (slot-group-for-block? ,block)))
;;	      (if ,temp
;;		  (,',internal-accessor-name ,temp)
;;		  ,,default-value))
;;
;; When we start using a new version of the Chestnut translator, this will
;; likely change the structure of the emitted C code, making this transformation
;; unnecessary.  This change being done for both 3.1 and 3.0 rev. 3.  Note that
;; this affects also the Motorola, which has the same compiler and the same
;; chip, the 88000.  The code identified that could not handle the old
;; version was in rotate-and-reflect-icon, in CONNECT2.  (MHD/JRA 5/13/93)

;; Define-slot-group-accessor currently allows for only one type of slot group in
;; the slot.  The idea of collapsing parent-frame and parent-attribute-name into
;; one slot turned out not to be worthwhile.  This could be extended if there
;; ever is a need for more than one slot group in a collapsed slot.

;; Consider improving the setf to reclaim the slot group structure if all slots
;; have their default values.  This could be implemented efficiently by using a
;; count of transitions from default to non-default and vice-versa.  This is not a
;; high priority because (for icon slot groups) a frame does not switch from
;; having an icon representation to not having one in its lifetime.  Once an
;; object is transferred to a workspace, it does not lose its icon representation
;; until it is deleted.

;; Make this more general by also passing in the slot which holds the slot group
;; cache.  Currently, slot-group-for-block?  is hard coded in.

;; Consider implementing a define-slot-group macro which defines the structure and
;; the slot group accessors.



(def-structure (icon-slot-group (:type vector)
				(:creations-at-a-time 100))
  (left-edge-internal 0)
  (top-edge-internal 0)
  (right-edge-internal 0)
  (bottom-edge-internal 0)
  (subblocks-internal nil)
  (superblock?-internal nil)
  (connections-internal nil))

(defmacro icon-slot-group-p (slot-group?)
  `(=f (length ,slot-group?) 7))


(define-slot-group-accessor left-edge-of-block
    icon-slot-group
    slot-group-for-block?
  left-edge-internal 0 t)

(define-slot-group-accessor top-edge-of-block
    icon-slot-group
    slot-group-for-block?
  top-edge-internal 0 t)

;; Make the defaults for these be as in set-up-icon-for-entity.
;; Then we won't create icon slot groups for every entity.

(define-slot-group-accessor right-edge-of-block
    icon-slot-group
    slot-group-for-block?
  right-edge-internal 0 t)

(define-slot-group-accessor bottom-edge-of-block
    icon-slot-group
    slot-group-for-block?
  bottom-edge-internal 0 t)

(define-slot-group-accessor subblocks
    icon-slot-group
    slot-group-for-block?
  subblocks-internal nil t t)

(define-slot-group-accessor superblock?
    icon-slot-group
    slot-group-for-block?
  superblock?-internal nil nil t)

(define-slot-group-accessor connections
    icon-slot-group
    slot-group-for-block?
  connections-internal nil t t)

;; Consider making the subblocks slot contain a managed array rather than a list.
;; This would save space for workspaces, which typically have many subblocks.

(defun-simple left-edge-of-block-function (block)
  (left-edge-of-block block))

(defun-simple bottom-edge-of-block-function (block)
  (bottom-edge-of-block block))

(defun-simple superblock?-function (block)
  (superblock? block))

(defparameter ws-protocol-handle-moves-from-edge-change-p nil)
(defparameter ws-protocol-trace-p nil)


;;; The function `set-edges-of-block' is designed to be used when a block is
;;; first initialized.  We don't allow any use of the old values of the edges.

(defun set-edges-of-block (block new-left new-top new-right new-bottom)
  #+development (unless (and new-left new-top new-right new-bottom)
		  (error "All arguments to set-edges-of-block must be non-NIL"))
  (setf (left-edge-of-block block) new-left)
  (setf (top-edge-of-block block) new-top)
  (setf (right-edge-of-block block) new-right)
  (setf (bottom-edge-of-block block) new-bottom)
  t)


;;; The function `change-edges-of-block' is designed to be the sole interface
;;; function for changing the edges of a block.  Any new edge supplied as NIL
;;; is left unchanged.  We return non-NIL iff some edge actually changed.


(defun change-edges-of-block (block new-left? new-top? new-right? new-bottom?)
  (let ((changed? nil)
	(delta-x-l 0)
	(delta-x-r 0)
	(delta-y-t 0)
	(delta-y-b 0)
	(old-left (left-edge-of-block block))
	(old-top (top-edge-of-block block))
	(old-right (right-edge-of-block block))
	(old-bottom (bottom-edge-of-block block)))
    
    (when (and new-left?
	       (/=f old-left new-left?))
      (setf (left-edge-of-block block) new-left?
	    changed? t
	    delta-x-l (-w new-left? old-left)))

    (when (and new-top?
	       (/=f old-top new-top?))

      (setf (top-edge-of-block block) new-top?
	    changed? t
	    delta-y-t (-w new-top? old-top)))

    (when (and new-right?
	       (/=f old-right new-right?))
      (setf (right-edge-of-block block) new-right?
	    changed? t
	    delta-x-r (-w new-right? old-right)))

    (when (and new-bottom?
	       (/=f old-bottom new-bottom?))
      (setf (bottom-edge-of-block block) new-bottom?
	    changed? t
	    delta-y-b (-w new-bottom? old-bottom)))

    (when changed?
      (note-change-to-edges-of-block block
				     old-left old-top old-right old-bottom
				     (or new-left? old-left)
				     (or new-top? old-top)
				     (or new-right? old-right)
				     (or new-bottom? old-bottom))
      (when g2-has-v5-mode-windows-p
	(cond
	  ((and (=f delta-x-r delta-x-l)
		(=f delta-y-t delta-y-b))
	   (when ws-protocol-handle-moves-from-edge-change-p
	     (when ws-protocol-trace-p
	       (format t "edge-change implies move (~s ~s) on ~s~%"
		       delta-x-l delta-y-t block))
	     (send-ws-representations-item-moved block delta-x-l delta-y-t)))
	  (t
	   (when ws-protocol-trace-p
	     (format t "edge change implies resize of ~s to (~s ~s ~s ~s)~%"
		      block 
		      (or new-left? old-left)
		      (or new-top? old-top)
		      (or new-right? old-right)
		      (or new-bottom? old-bottom)))
	   (send-ws-representations-item-resized
	     block 
	     (or new-left? old-left)
	     (or new-top? old-top)
	     (or new-right? old-right)
	     (or new-bottom? old-bottom))))))
    
    changed?))


;; Here we can adjust or invalidate the cached or overlapping blocks.

;; Changes for v5-telewindows by pbk 11/3/95
;; Discern whether the new edges require a resize or just a move command and issue
;; such a command to all v5-mode telewindows that contain a ws-representation of this
;; block's workspace.


;;; `Describe-slot-group-for-block' is called by describe frame and displays
;;; the subblock's slots.  Development only.

#+development
(defun describe-slot-group-for-block (frame)
  (format
    t "~&~7T~(~a~) ~v,,,'.a.. ~4D ~4D  ~4D ~4D"
    "*-edge-of-block" (max 0 (- 50 (length (string "*-edge-of-block")))) ""
	  (left-edge-of-block frame)
	  (top-edge-of-block frame)
	  (right-edge-of-block frame)
	  (bottom-edge-of-block frame))
  (let ((slot "subblocks")
	(x (subblocks frame)))
    (format
      t "~&~7T~(~a~) ~v,,,'.a.. ~4S"
      slot (max 0 (- 50 (length slot))) "" x))
  (let ((slot "connections")
	(x (connections frame)))
    (format
      t "~&~7T~(~a~) ~v,,,'.a.. ~4S"
      slot (max 0 (- 50 (length slot))) "" x))
  (let ((slot "superblock?")
	(x (superblock? frame)))
    (format
      t "~&~7T~(~a~) ~v,,,'.a.. ~4S"
      slot (max 0 (- 50 (length slot))) "" x)))







;;;; Fast Slot Group Access Wrappers

;;; Accessors for collapsed slots, as defined by define-slot-group-accessor, are
;;; slightly slower than accessors for vector slots since the collapsed slot
;;; accessors have to access the slot group, check its type, then access the slot
;;; within the slot group.  For cases where tis is too slow (there shouldn't be
;;; too many of these) wrappers are provided to cache the slot groups.

;;; These wrappers are useful when there are multiple accesses to slots in a slot
;;; group in some body of code (edges of blocks for example).  The slot group is
;;; cached by these wrappers and macrolet is used to redefine the accessors to use
;;; the slot group rather than the block.

;;; The wrapper with-fast-icon-slots will expand optimized versions of the slot
;;; group accessors when the argument of the accessor is a symbol which is eq to
;;; the argument of the wrapper.  Note that within the body of the wrapper, the
;;; block arg should not be set or rebound to a new value.  To avoid requiring the
;;; optimized accessors to check whether the slot group exists, the slot-group?
;;; cache is bound to default-icon-slot-group if the slot-group-for-block?  slot
;;; is empty.

;;; Note that a with-fast-icon-slots wrapper nested lexically in another one will
;;; result in optimization only for the innermost wrapper for accessors and setfs
;;; within both (the innermost wrapper overrides the macrolet and caches for outer
;;; ones.

;; Consider improving this to allow for optimization for more than one block.
;; Either, provide a wrapper which takes a list of blocks as its argument and sets
;; up slot group caches for each, or (even better) make a macro-expansion time
;; alist of blocks and corresponding slot groups.  This would allow nesting.



(def-system-variable default-icon-slot-group FRAMES3
  (:funcall initialize-default-icon-slot-group))

(defun initialize-default-icon-slot-group ()
  (make-icon-slot-group))

(defmacro with-fast-icon-slots (block &body body)
  (let ((value-of-block (gensym))
	(block (car block)))
    `(let* ((,value-of-block ,block)
	    (slot-group (or (slot-group-for-block? ,value-of-block)
			    default-icon-slot-group)))
       (macrolet ((left-edge-of-block 
		    (block-arg)
		    (if (eq block-arg ',block)
			`(left-edge-internal slot-group)
			`(left-edge-of-block-general ,block-arg)))
		  (top-edge-of-block 
		    (block-arg)
		    (if (eq block-arg ',block)
			`(top-edge-internal slot-group)
			`(top-edge-of-block-general ,block-arg)))
		  (right-edge-of-block 
		    (block-arg)
		    (if (eq block-arg ',block)
			`(right-edge-internal slot-group)
			`(right-edge-of-block-general ,block-arg)))
		  (bottom-edge-of-block 
		    (block-arg)
		    (if (eq block-arg ',block)
			`(bottom-edge-internal slot-group)
			`(bottom-edge-of-block-general ,block-arg)))
		  (subblocks
		    (block-arg)
		    (if (eq block-arg ',block)
			`(subblocks-internal slot-group)
			`(subblocks-general ,block-arg)))
		  (superblock?
		    (block-arg)
		    (if (eq block-arg ',block)
			`(superblock?-internal slot-group)
			`(superblock?-general ,block-arg)))
		  (connections
		    (block-arg)
		    (if (eq block-arg ',block)
			`(connections-internal slot-group)
			`(connections-general ,block-arg)))
		  (set-left-edge-of-block 
		    (block-arg value)
		    (if (eq block-arg ',block)
			`(if (not (eq slot-group default-icon-slot-group))
			     (setf (left-edge-internal slot-group) ,value)
			     (set-left-edge-of-block-general
			       ,block-arg ,value))))
		  (set-top-edge-of-block 
		    (block-arg value)
		    (if (eq block-arg ',block)
			`(if (not (eq slot-group default-icon-slot-group))
			     (setf (top-edge-internal slot-group) ,value)
			     (set-top-edge-of-block-general
			       ,block-arg ,value))))
		  (set-right-edge-of-block 
		    (block-arg value)
		    (if (eq block-arg ',block)
			`(if (not (eq slot-group default-icon-slot-group))
			     (setf (right-edge-internal slot-group) ,value)
			     (set-right-edge-of-block-general
			       ,block-arg ,value))))
		  (set-bottom-edge-of-block 
		    (block-arg value)
		    (if (eq block-arg ',block)
			`(if (not (eq slot-group default-icon-slot-group))
			     (setf (bottom-edge-internal slot-group) ,value)
			     (set-bottom-edge-of-block-general
			       ,block-arg ,value))))
		  (subblocks
		    (block-arg value)
		    (if (eq block-arg ',block)
			`(if (not (eq slot-group default-icon-slot-group))
			     (setf (subblocks-internal slot-group) ,value)
			     (set-subblocks-general
			       ,block-arg ,value))))
		  (superblock?
		    (block-arg value)
		    (if (eq block-arg ',block)
			`(if (not (eq slot-group default-icon-slot-group))
			     (setf (superblock?-internal slot-group) ,value)
			     (set-superblock?-general
			       ,block-arg ,value)))))
	 ,@body))))



;(defun test-fast (foo-block bar-block)
;  (with-fast-icon-slots (foo-block)
;    (left-edge-of-block foo-block)
;    (left-edge-of-block bar-block)
;    (setf (left-edge-of-block foo-block) 10)
;    (setf (left-edge-of-block bar-block) 10)
;    ))

;; To clearly see expansion, comment out all but one of the accessors and setfs
;; and do meta-shift m on the with-fast-icon-slots form.  The optimizations here
;; are for foo-block but not for bar-block.



;(defun test-fast-2 (foo-block bar-block)
;  (with-fast-icon-slots (foo-block)
;    (with-fast-icon-slots (bar-block)
;      (left-edge-of-block foo-block)
;      (left-edge-of-block bar-block)
;      (setf (left-edge-of-block foo-block) 10)
;      (setf (left-edge-of-block bar-block) 10)	       
;      )))

;; Note that the optimizations for test-fast-2 are for bar-block only, not for
;; foo-block.



;;;; G2-Specific Frame Flags




;;; The `forward-chain' flag enables a variable to initiate forward chaining when
;;; its value is put. The default is to forward-chain named-conditions.

(def-savable-frame-flag forward-chain 1 variable-or-parameter)



(def-savable-frame-flag invocable-via-backward-chaining 1 rule)


;;; savable-kb-workspace is the third overloading of bit 1. There
;;; is no reason to save it, but it will be saved, since bit masking
;;; of frame flags is not class specific. It is used during save-kb
;;; and the menu chooser preceeding that, and makes no assumption about
;;; the state of the flag previously. 

(def-savable-frame-flag savable-kb-workspace 1 kb-workspace)


;;; recent-procedure is used in the package authorization system to
;;; prevent tampering with a saved kb to remove its authorization.
;;; All procedures saved to a file from Version 2.1 on will have this flag
;;; set.

(def-savable-frame-flag recent-procedure 1 procedure)


;;; savable-format-frame is used while saving a KB to mark format-frames
;;; that need to be saved. Its value otherwise is of no significance.


;;; A sketch definition is a ghost definition that has been installed.

(def-savable-frame-flag sketch-definition 1 definition)



(def-obsolete-frame-flag backward-chains-to-old-rule 2 variable)


;;; `Depth-first' backward chain is used for variables

(def-savable-frame-flag depth-first 3 variable)


(def-savable-frame-flag invocable-via-forward-chaining 3 rule)



;;; A sensor variable is `passive' if its data supplier ought not to be polled
;;; for its value.

(def-savable-frame-flag passive 4 variable set-not-passive)



;;; `May-cause-data-seeking' ...

(def-savable-frame-flag may-cause-data-seeking 4 rule)


;;; `always-forward-chain-if-possible' is used for variables and parameters to
;;; indicate that even if their value has not changed with the new update, to
;;; do forward chaining anyway. The default is to only chain when the value has
;;; actually changed.

(def-savable-frame-flag always-forward-chain-if-possible 5 variable-or-parameter)


;;; A `one-shot' sensor variable ought not to be requested for repeated values
;;; from its supplier.

(def-obsolete-frame-flag one-shot 6 variable set-not-one-shot)

;; The one-shot frame flag has been taken out of use for the time being.  It was
;; not documented and Bob and others found its operation confusing and
;; surprising.  If and when we put in an interface to this flag for the user,
;; then mechanisms which use it will be re-enabled.  -jra 3/11/88

;;; journal-reversible-changes

;(def-savable-frame-flag recursive-backward-chain 7 rule clear-recursive-backward-chain)

;;; The recursive-backward-chain flag is no longer needed or used.  -jra  8/3/88




;;; `Opaque-block' is a frame flag used to identify opaque blocks.  See the definition
;;; of workspace below.

(def-savable-frame-flag opaque-block 10 block)

;; Tracing of rules and variables used to be controlled by the trace flag (number 10).
;; That flag is now obsolete (ML, 23 Dec 87).  Presumably, it was never saved in any KB.



;;; `Initial-rule' rules are indistinguishable from rules except by the flag
;;; initial-rule which is placed by the slot-value-compiler for rules. 
;;; When a workspace is activated, its initial rules are scheduled for invocation.

(def-savable-frame-flag initial-rule 11 rule)

;;; `Overlapping-block' is a true of workspace subblocks that overlap
;;; other blocks in the same workspace.  More exactly the rectangle that
;;; encloses the block, it's stubs, and subblock tree overlaps the
;;; rectangle of some other block that is "above" this block in the
;;; drawing order.  When this is true updates to this block may force
;;; refreshing of the overlapping block.

(def-savable-frame-flag overlapping-block 12 block)


;;; The `Manually-disabled' frame flag is set when a user wants to remove an
;;; item from the execution environment of a KB.  It has the effect of
;;; deactivating the item if it was active, and preventing any
;;; running-while-inactive items from executing.

(def-savable-frame-flag manually-disabled 13 block)



;;; `Multiple-compilations' is a property of rules. It is true if there
;;; are multiple compilations for at least one role.

(def-savable-frame-flag multiple-compilations 14 rule)

;;; journal-expiration

(def-savable-frame-flag journal-expiration 14 variable)

;;; The `dont-backward-chain' flag allows users to explicitly control whether or
;;; not backward chaining will be invoked from a particular variable.

(def-savable-frame-flag dont-backward-chain 15 variable)

(def-savable-frame-flag may-cause-forward-chaining 15 rule)



;;; Rules are compiled as new rules when use-old-rule-compiler? is null.

(def-obsolete-frame-flag compiled-as-new-rule 16 rule)





;;; If the immediate class of a frame is user- rather than system-defined,
;;; `class-of-frame-is-user-defined' is set.

(def-savable-frame-flag class-of-frame-is-user-defined 17 block)

#+unused
(defun class-of-frame-is-user-defined-function (block)
  (class-of-frame-is-user-defined-p block))




;;; The `cache-data-for-explanation flag' is a flag set on variables,
;;; parameters, and rules.  This flag indicates that data should be cached for
;;; explanations.  The default is not to cache data for explanations.

(def-savable-frame-flag cache-data-for-explanation 20 block)

(def-savable-frame-flag strip-text 21 block)

(def-savable-frame-flag do-not-strip-text 22 block)



;;; The `table-may-not-be-wysiwyg flag' is set false for instances of the
;;; class table, other than graphs, by make-or-reformat-table.  Update-
;;; text-cell sets this to true when it makes a table be possibly not WYSIWYG.
;;; At present, tables that become non-wysiwyg are always put back to wysiwyg
;;; upon loading from a KB. See the post-loading method for the class table.
;;; And see the module TABLES.

(def-savable-frame-flag table-may-not-be-wysiwyg 23 table)	; (MHD 6/29/92)

;; You might want to think of this as "the dirty bit".




;;; The `runs-while-inactive flag' is set true for rules and procedures that are
;;; enabled for execution while G2 is in the paused or reset state.  Normally
;;; these only run while G2 is running, but turning this bit on causes them to
;;; be run through the real-time scheduler, not the G2 time scheduler.  Since
;;; this applies to rules and procedures, I'm listing the class as block, which
;;; is the join point for their superior class hierarchies.

(def-savable-frame-flag runs-while-inactive 24 block)




;;; The `may-refer-to-inactive-items flag' is set true for rules and procedures
;;; that are allowed to reference inactive items.  This flag will cause these to
;;; be run with the role-serve-inactive-items? flag set to true.  If
;;; `runs-while-inactive' is set, then this flag should generally also be set to
;;; true, though this can be set to true for items which can only run while G2
;;; is running.

(def-savable-frame-flag may-refer-to-inactive-items 25 block)

;;; GENSYMCID-1220: Detecting when a workspace is moved/scaled
;;; GENSYMCID-1283: G2-2011 JUNE 2014 Release gub whenever a workspace is moved
;;;
;;; The `self-referenced flag' indicates that there's a `this-workspace' or
;;; `this-rule' as the role server.

(def-savable-frame-flag self-referenced 26 rule)


;;; All non-savable frame flags follow in bit assignable order.


(def-non-savable-frame-flag block-has-been-written 1 block)

(def-non-savable-frame-flag block-permanently-changed 2 block)

;; Used in PRIMITIVES
(defun set-block-permanently-changed-function (block)
  (set-block-permanently-changed block))

(def-non-savable-frame-flag block-existed-at-start-of-save 3 block)

(def-non-savable-frame-flag item-was-created-by-load 4 item)

(defun set-item-was-created-by-load-function (item)
  (set-item-was-created-by-load item))

;;; A sensor variable is `failed' if it has been polled and doesn't get an
;;; answer.

(def-non-savable-frame-flag failed 5 variable set-not-failed)

;;; During warm boot, a kb-workspace, when read in, has its activation status
;;; at time of save noted.

(def-non-savable-frame-flag workspace-was-active 5 kb-workspace)

;;; has-indexed-attributes is set iff there is some attribute of the
;;; immediate class to which the item belongs which is indexed.

;;; First-definition-mark and second-definition-mark are used for collecting a
;;; list of definitions to save within a kb saving context. First-definition-
;;; mark is, in addition, used in a kb loading context to mark ghost definitions.
;;; These flags must be kept cleared except within a dynamic extent without
;;; interrupts.

(def-non-savable-frame-flag first-definition-mark 5 definition)


;;; Module-information-instance-mark is only used for marking while doing
;;; graph searches in the module hierarchy.  

(def-non-savable-frame-flag module-information-instance-mark 5 module-information)


;;; `Table-collected' is used transiently for testing for membership of table
;;; instances in transiently created collections of tables.  It may be assumed
;;; to be off, and it must always be turned off after transient use.  It is
;;; originally used, and at present only used, by
;;; update-attribute-tables-for-instances.

(def-non-savable-frame-flag table-collected 5 table)



;;; The frame flag `has-indexed-attributes' ...

(def-non-savable-frame-flag has-indexed-attributes 6 item)



;;; The frame flag `currently-evaluating-formula' is used on variables to
;;; dynamically mark those variables which are evaluating their formulas.  This is
;;; used to detect formulas for variables which are recursive.

(def-non-savable-frame-flag currently-evaluating-formula 7 variable)



;;; `Ancestor-not-activatable' ...

(def-non-savable-frame-flag ancestor-not-activatable 8 block)

(defun ancestor-not-activatable-function-p (block)
  (ancestor-not-activatable-p block))

;; see start-rendering-dragging-state-for-move-or-transfer in moves.lisp
(def-non-savable-frame-flag previous-render-state-was-xor 9 block)

;;; `Render-frame-in-xor-overlay' is set on those frames that are currently
;;; being rendered in the XOR overlay, as for example when dragging.

;;; Some classes are always rendered XOR, text-regions for example, such blocks
;;; set this bit when they are created.  Other blocks, those being dragged for
;;; example, have this bit during the approprate extent.  These two uses do not
;;; currently conflict with each other since no directly draggable blocks are
;;; rendered in XOR.

;;; Savable blocks that are permanently XOR'd must have the bit reset on load,
;;; the indicators in meters and dials are the only current example of such
;;; blocks.  This bit is often set in the initially method of the block.

;;; See also defered-xor-drawing, and work-on-drawing-workspace.

(def-non-savable-frame-flag render-frame-in-xor-overlay 10 block)



;;; `Block-is-currently-being-dragged' is set on those frames that are currently
;;; being dragged by some user in some workstation.  Note that such frames
;;; are rendered in the dragging style in all windows.  

(def-non-savable-frame-flag block-is-currently-being-dragged 11 block)

;; This bit replaced the list current-list-of-objects-being-dragged.


;;; `Queued-by-local-data-server' indicates that the variable has been queued 
;;; and will receive a value presently when the remote system responds. Cleared
;;; when the variable is dequeued or upon reset.

(def-non-savable-frame-flag queued-by-local-data-server 12 variable)

;;; See documentation for first-definition-mark.

(def-non-savable-frame-flag second-definition-mark 12 definition)




;;; The KB flag `preexisting-frame' is used when reading a KB.
;;;
;;; When a block is created during the main portion of read-kb other than as one
;;; being read, there is the possibility of giving it a frame-serial-number that
;;; is too low.  This can happen because during incremental save, the highest
;;; frame-serial-number is not known till after the save, and is given in the
;;; plist-at-end.  During the read, saving their frame-serial-numbers and/or
;;; executing frame-has-been-reprocessed-p is problematic.  Therefore, these
;;; frames are noted by pushing them in the list preexisting-frames, and setting
;;; the flag.  After reading, for every frame in this list that has the flag,
;;; and is not a deleted frame, an adjustment is made after reading.

(def-non-savable-frame-flag preexisting-frame 13 block)



;;;  The frame flag `block-overlap-cache', when valid, indicates whether this
;;;  possibly block overlaps other blocks on the the same worksapce.  The
;;;  overlap test is based on the extent of just the block itself, NOT
;;;  including any of its subblocks or connections.  This bit is valid only
;;;  when `block-overlap-cache-valid-p' is true.

;; -fmw, 8/9/94

(def-non-savable-frame-flag block-overlap-cache 14 block)



;;; The frame flag `block-is-transformed' is set on those blocks that have
;;; frame-transforms or who's ancestors in the subblock hierarcy do.  The
;;; rendering harness must be treated such subblocks specially when creating the
;;; for-image-plane dynamic extent.

;;; This bit is not set on workspaces.

(def-non-savable-frame-flag block-is-transformed 15 block)



;;; The frame flag `block-overlap-cache-valid' indicates whether the
;;; block-overlap-cache bit is valid.  Actually, that bit is valid only if the
;;; block's workspace's bit is valid AND the block's bit is valid.  This is so
;;; that there is an O(1) way to invalidate the bits of all of the blocks on a
;;; workspace.

;; -fmw, 8/9/94

(def-non-savable-frame-flag block-overlap-cache-valid 16 block)



;;; The `was-once-permanent flag' is only meaninful on transient blocks.  In a
;;; runtime G2 you may not make any thing containing transient blocks permanent,
;;; unless all the blocks happen to have previously been permanent.  This bit is read
;;; in the implementation of the restrictable-frame-system-operation make-permanent.

;; - ben 4/16/93

(def-non-savable-frame-flag was-once-permanent 17 block)



;;; The `transient frame flag' is a frame flag set on all transient objects.
;;; This flag is needed to distinguish between permanent and transient frames at
;;; reset time, when all transient frames are deleted.  Also, save-kb generally
;;; does not save transient frames, although it does save them when snapshotting
;;; a KB.  (Note that save-kb must NEVER save non-transient/non-permanent items,
;;; i.e., with both the transient and permanent-block flags off.)

(def-non-savable-frame-flag transient 18 block)


;;; The frame-flag `do-not-save-in-kb' is used on frames other than transient
;;; ones that ought not to get saved. These include messages and windows objects.

(def-non-savable-frame-flag do-not-save-in-kb 19 block)


;;; The frame-flag `block-found-in-search' is used during a search to mark that
;;; a frame has already been referenced.  This flag can be used by any facility,
;;; as long as it is used within the descent of one function call, does not
;;; overlap with another use of this flag, and that it clears the flags of the
;;; marked frames after finishing its search (function call).

(def-non-savable-frame-flag block-found-in-search 20 block)

(defun-simple clear-blocks-found-in-search (blocks)
  (loop for block in blocks
	do
    (clear-block-found-in-search block)))


;;; The `item-has-icon-views' flag is set if there is possibility that there
;;; exist "native views" of this item's icon. If so, we must update the views
;;; whenever the item's icon changes appearance (via color change, etc).

;; -fmw, 9/1/05

(def-non-savable-frame-flag item-has-icon-views 21 item)


;;; The frame flag `frame-flags-read' is set on a block by read-frame-for-kb
;;; after that slot value has been read in.  Read-frame-for-kb may be called
;;; both to read in an entire frame and to read in a "frame modification".  If
;;; frame flags have not been read in yet, it sets the block to have the status
;;; "neither permanent nor transient" prior to reading.  Otherwise, it should
;;; leave that status information alone.
;;;
;;; Note that this is only written and read on blocks as they are being read
;;; from a KB file by read-frame-for-kb.

(def-non-savable-frame-flag frame-flags-read 22 block)

;; (MHD 5/23/95)


;;; This flag is used when writing a KB.  

(def-non-savable-frame-flag block-has-been-referenced 23 block)


;;; This allows for the application of consistency analysis to be more predictable

(def-non-savable-frame-flag immutable-consistency-analysis 24 block)

(def-non-savable-frame-flag item-mark 25 item)

(def-non-savable-frame-flag tracking-item-mark 26 item)
(def-non-savable-frame-flag tracking-item-in-set 27 item)

(defmacro transient-or-do-not-save-in-kb-flag ()
  (+f transient-flag do-not-save-in-kb-flag))


(def-substitution-macro transient-or-unsavable-p (kb-frame)
  (/=f 0 (logandf (frame-flags-2 kb-frame)
		  (transient-or-do-not-save-in-kb-flag))))




;;; Summary of frame flags. Please keep up to date.

;;; The following are savable frame flags. The bits are
;;; allocated in frame-flags.

;;; 0 permanent-block			block
;;; 1 forward-chain			variable-or-parameter
;;; 1 invocable-via-backward-chaining	rule
;;; 1 savable-kb-workspace		kb-workspace
;;; 1 recent-procedure			procedure
;;; 1 savable-format-frame		format-frame
;;; 1 sketch-definition			definition
;;; 2 backward-chains-to-old-rule	variable obsolete
;;; 3 depth-first			variable
;;; 3 invocable-via-forward-chaining	rule
;;; 4 passive				variable set-not-passive 
;;; 4 may-cause-data-seeking		rule
;;; 5 always-forward-chain-if-possible	variable-or-parameter
;;; 6 one-shot				variable set-not-one-shot obsolete
;;; 7
;;; 8
;;; 9
;;; 10 opaque-block			block
;;; 11 initial-rule			rule
;;; 12 overlapping-block		block
;;; 13 manually-disabled		block
;;; 14 multiple-compilations		rule
;;; 15 dont-backward-chain		variable
;;; 15 may-cause-forward-chaining	rule
;;; 16 compiled-as-new-rule		rule obsolete and reusable
;;; 17 class-of-frame-is-user-defined	block
;;; 18
;;; 19
;;; 20 cache-data-for-explanation	block
;;; 21 strip-text			block
;;; 22 do-not-strip-text		block
;;; 23 table-may-not-be-wysiwyg		table
;;; 24 runs-while-inactive		block
;;; 25 may-refer-to-inactive-items	block
;;; 26 self-referenced			rule       (binghe 8/13/2014)



;;; The following are non-savable frame flags. The bits are
;;; allocated in frame-flags-2.

;;; 0 active 				block set-inactive
;;; 1 block-has-been-written 		block
;;; 2 permanently-changed 		block
;;; 3 block-existed-at-start-of-save 	block
;;; 4 block-rendering-is-dirty 		block
;;; 5 failed 				variable set-not-failed
;;; 5 workspace-was-active 		kb-workspace
;;; 5 first-definition-mark 		definition
;;; 5 module-information-instance-mark 	module-information
;;; 6 has-indexed-attributes 		block
;;; 7 currently-evaluating-formula 	variable obsolete?
;;; 8 ancestor-not-activatable 		block
;;; 9 frame-being-deleted 		block
;;; 10 render-frame-in-xor-overlay	block
;;; 11 block-is-currently-being-dragged	block
;;; 12 queued-by-local-data-server 	variable
;;; 12 second-definition-mark 		definition
;;; 13 preexisting-frame 		block      (MHD 12/1/93)
;;; 14 block-drawing-is-pending         block
;;; 15 block-is-transformed             block
;;; 16
;;; 17 was-once-permanent-p
;;; 18 transient 			block
;;; 19 do-not-save-in-kb 		block
;;; 20 block-found-in-search            block
;;; 21
;;; 22 frame-flags-read-p               block      (MHD 5/23/95)
;;; 23 block-has-been-referenced 	block
;;; 24 immutable-consistency-analysis	block
;;; 25 item-mark			item
;;; 26 tracking-item-mark		item
;;; 27 tracking-item-in-set		item

#+development
(defun list-bits (n)
  (loop for i from 0
	until (= n 0) do
	(if (oddp n) (format t " ~d" i))
	(setq n (ash n -1))))

(def-slot-putter frame-flags (frame value initializing?)
  (cond (initializing?
	 ;; See the note below about why this is necessary.
	 (let ((adjusted-value
		 (if (frame-flags-revised-function)
		     value
		     (logandf value old-mask-for-saved-frame-flags))))
	   (setf (frame-flags frame)
		 (if (class-of-frame-is-user-defined-p frame)
		     (logiorf adjusted-value
			      class-of-frame-is-user-defined-flag)
		     (logandc2f adjusted-value
				class-of-frame-is-user-defined-flag)))))
	(t
	 (let ((old-value (frame-flags frame)))
	   (setf (frame-flags frame) value)
	   (unless (eq (may-refer-to-inactive-items-of-flag-vector-p old-value)
		       (may-refer-to-inactive-items-of-flag-vector-p value))
	     (funcall-method-if-any
	       'note-may-refer-to-inactive-items-change frame))
	   (unless (eq (runs-while-inactive-of-flag-vector-p old-value)
		       (runs-while-inactive-of-flag-vector-p value))
	     (funcall-method-if-any 'note-runs-while-inactive-change frame))

	   (when (and (frame-of-class-p frame 'rule)
		      (not called-within-clear-text-loading))
	     (when (and (explanation-related-features-enabled-func?)
			(cache-data-for-explanation-of-flag-vector-p old-value)
			(not (cache-data-for-explanation-of-flag-vector-p value)))
	       (clear-cached-explanations frame))
	     (recompile-item frame))
	   value))))

;; When initializing, the frame has been created by make-frame-without-
;; computing-slot-initializations which sets the flag class-of-frame-
;; is-user-defined appropriately.  This flag must not be changed by the
;; following. The flag is defined to be savable, but saved value is ignored by
;; the following code. There are old KBs in which the value is inappropriate. If
;; there is some confidence in newer KBs, then the fix implemented here could be
;; done only for old KBs. There is only a marginal issue of speed while loading
;; here. ML, 10/23/91

;; When loading a KB saved after frame-flags-revised, no masking of bits need be
;; done.  When loading an older file, the mask old-mask-for-saved-frame-flags is
;; used.  It has bits set for all the current saved flags as of the date of
;; transition.  Further, if the Kb was saved before no-more-old-rules, then the
;; flag compiled-as-new-rule-flag, if present as read in, is retained.  This is
;; promptly removed by put-box-translation-and-text-slot-value method for rules
;; in INSTALL.  -ml






;;;; Note-change-to-blocks

;; Moved here to avoid many forward references.


(defconser journal)

(defun-void reclaim-journal-tree-function (tree)
  (reclaim-journal-tree tree))

(defun-void reclaim-journal-list-function (tree)
  (reclaim-journal-list tree))

;; Functions defined for use as structure slot reclaimers.




;;; `note-change-to-block' must be called for any block when (1)
;;; noting-changes-to-kb-p is true; (2) the block is permanent or transient; and
;;; (3) the block is about to have some savable slot changed.  It may be called
;;; multiple times, although this should be avoided when possible.  It may be
;;; called on blocks that are neither transient or savable.  The second argument
;;; is not used at present.

;;; If appropriate, the block is written to a knowledge base within the
;;; recursive extent of note-change-to-block. The conditions for doing so are:

;;; For permanent blocks:
;;;   there must be a save in progress,
;;;   the block has not been written previously,
;;;   the block must have been present when the save started,
;;;   either the whole KB is being saved, or if the save is a backup, then the
;;;      block must be permanently modifed.

;;; For transient blocks
;;;   there must be a save in progress,
;;;   the block has not been written previously,
;;;   the block must have been present when the save started,
;;;   the save must include runtime data,
;;;   either the whole KB is being saved, or if the save is a backup, then the
;;;      block must be permanently modifed.

;;; Because the traversal mechasnism will not again look below this block, it is
;;; neccessary to note the inferiors at this time, and add them to the traversal
;;; state.

;;; Permanent blocks must be marked as permanently changed. (This is needed for
;;; backups.)

;; Transient blocks not processed yet!!


;;;; Noting changes

;; Part of this code is in FRAMES2, because it is needed for expanding slot
;; descriptions slot accessors. 

;; note-change-to-block-1-macro was renamed note-change-to-block-2, changed
;; to a function, and moved to KB-SAVE1.  (MHD 1/10/93)

(defun-simple note-change-to-block-1 (block pretty-slot-name?)
  (note-change-to-block-2 block pretty-slot-name?))


(defun-simple note-change-to-dependent-frame-1 ()
  (when (not (eq 'dependent-frame-has-no-owner
		 current-block-of-dependent-frame))
    (note-change-to-block-2 current-block-of-dependent-frame 'dependent-frame)))


(defmacro note-change-to-runtime-data-for-block (block)
  `(when noting-changes-to-kb-p
     (note-change-to-runtime-data-for-block-1 ,block)))








;;; The three following macros are the interface to funcalling the analyze-for-
;;; consistency method.  These represent the three possible valid combinations
;;; of the add-as-item-referring-to-name? and delete-as-item-referring-to-name?
;;; arguments for this method.

;;;              Method Arguments: item, add?, delete?
;;; assert-consistency-analysis  - item, t,    nil
;;; retract-consistency-analysis - item, nil,  t
;;; check-consistency-analysis   - item, nil,  nil
;;;
;;; not valid                    - item, t,    t

;;; Note that without-consistency-analysis does both an assert and retract of
;;; consistency-analysis.

;;; `the interface is changed' -rdf, 11/29/94
;;; Changing the Consistency analysis now requires that the
;;; immutable-consistency-analysis frame flag be available.

;;; `with-immutable-consistency-analysis' allows users to set up a context in
;;; which consistency analysis is cannnot be changed.
;;; without-consistency-analysis checks this flag before retraction and resets
;;; it upon exit if it is the owner of the flag.

;;; `with-new-consistency-analysis-as-appropriate',
;;; `assert-consistency-analysis-if-allowed'
;;; `retract-consistency-analysis-if-allowed' check that the
;;; immutable-consistency-analysis flag is not set prior to performing their
;;; actions. These, in conjuction with `without-consistency-analysis'and
;;; `with-immutable-consistency-analysis' are now the appropriate interface to
;;; consistency analysis 



;;; 
;;; `Assert-consistency-analysis', a macro, provides a short hand to invoke the
;;; analyze-for-consistency upon a block so as to install any registrations of
;;; names used by that block.

(defmacro assert-consistency-analysis (block)
  `(funcall-method 'analyze-for-consistency ,block t nil))


;;; `Retract-consistency-analysis', a macro, provides a short hand to invoke the
;;; analyze-for-consistency upon a block so as to remove any installed
;;; registrations upon names used by the block.

(defmacro retract-consistency-analysis (block)
  `(funcall-method 'analyze-for-consistency ,block nil t))


;;; `Check-consistency-analysis', a macro, provides a short hand to invoke the
;;; analyze-for-consistency upon a block so as to verify the consistency
;;; analysis of the block.  This macro is useful to analyze an item when
;;; the free-references that it depends on have changed.

(defmacro check-consistency-analysis (block)
  `(funcall-method 'analyze-for-consistency ,block nil nil))


(defmacro with-immutable-consistency-analysis ((block) &body body)
  (avoiding-variable-capture (block &aux current-flag-state? result)
    `(let (,result ,current-flag-state?)
       (setq ,current-flag-state? (immutable-consistency-analysis-p ,block))
       (unless ,current-flag-state?
	 (set-immutable-consistency-analysis ,block))
       (unwind-protect-for-development without-consistency-analysis
	     (setq ,result (progn ,@body)))
       (unless ,current-flag-state?
	 (clear-immutable-consistency-analysis ,block))
       ,result)))

(defun permanently-retract-consistency-analysis (block)
  (progn
    #+development
    (when (immutable-consistency-analysis-p block)
      (cerror "Ok after examined" "Attempt to perform a permanent set on a locked block: ~S" block))
    (retract-consistency-analysis block)
    (set-immutable-consistency-analysis block)))



(defmacro assert-consistency-analysis-if-allowed (item)
  (avoiding-variable-capture (item)
    `(unless (immutable-consistency-analysis-p ,item)
       (assert-consistency-analysis ,item))))

(defmacro retract-consistency-analysis-if-allowed (item)
  (avoiding-variable-capture (item)
    `(unless (immutable-consistency-analysis-p ,item)
       (retract-consistency-analysis ,item))))

(defmacro with-new-consistency-analysis-as-appropriate ((block) &body body)
  (avoiding-variable-capture (block &aux result)
    `(let (,result)
       (with-updates-to-representations-supressed (,block 'frame-status-and-notes)
	 (unless initializing?
	   (retract-consistency-analysis-if-allowed ,block))
	 (unwind-protect-for-development without-consistency-analysis
	     (setq ,result (progn ,@body))
	   (unless initializing?
	     (assert-consistency-analysis-if-allowed ,block))))
       ,result)))


;;; The macro `checking-for-consistency-analysis-p' may be called during the
;;; dynamic extent of consistency analysis.  At that time, it returns T
;;; iff we are checking consistency.  Consistency checking occurs after a 
;;; name we depend on has changed its meaning, or after deferred analysis.

(defmacro checking-for-consistency-analysis-p ()
  `(and (null add-as-item-referring-to-name?)
	(null delete-as-item-referring-to-name?)))



;;; `Without-consistency-analysis' creates an unnamed dynamic extent within
;;; which the consistency analysis for the block is retracted.  This is a good
;;; thing to use in slot putters to enclose the replacement of a slot value that
;;; uses names.

;;; This form returns one and only one value.  It is an error to unwind out of
;;; this form.
;;;
;;; In development only, errors in body are protected to a limited extent by an
;;; unwind-protect-for-development, which reasserts consistency analysis, which
;;; at least gives some hope of maintaining the integrity of the environment.
;;; However, this feature of course should not be relied on for production
;;; versions.

;; ben - 6/08/91

(defmacro without-consistency-analysis ((block) &body body)
  (avoiding-variable-capture (block &aux result current-flag-state?)
    `(let (,result ,current-flag-state?)
       (with-updates-to-representations-supressed (,block 'frame-status-and-notes)
	 (setq ,current-flag-state? (immutable-consistency-analysis-p ,block))
	 (unless ,current-flag-state?
	   (retract-consistency-analysis ,block)
	   (set-immutable-consistency-analysis ,block))

	 (unwind-protect-for-development without-consistency-analysis
	     (setq ,result (progn ,@body))
	   (unless ,current-flag-state?
	     (clear-immutable-consistency-analysis ,block)    
	     (assert-consistency-analysis ,block))))
       ,result)))



;; unwind-protect-for-development added.  (MHD/JED 12/9/93)



;;; The macro `defer-some-consistency-analysis' is used to delay consistency
;;; analysis of all compiled items until all the items have been collected.  The
;;; analysis is then done at the end of the macro.  The purpose of this macro is
;;; to collect a set of items that will then be analyzed only once.

;;; This macro caches and then returns the value of the body argument, after
;;; the deferred analysis is completed.

;;; Because the analysis can be deferred, the original order of analysis is not
;;; preserved.

;;; This macro is used by wrapping a function that can cause consistency
;;; analysis.  For example:
;;;
;;; (defer-some-consistency-analysis
;;;    (loop for name in names-to-analyze
;;;	  do
;;;      (analyze-compiled-items-for-consistency name)))

;;; Note that the method defined by define-analyze-for-consistency checks if the
;;; analysis should be deferred or immediately done.

;;; Currently, only checks of consistency analysis can be deferred, not
;;; asserting or retracting consistency analysis (adding or deleting the items
;;; as referring to name).

;; TO DO: Consider wrapping other callers of analyze-compiled-items-for-
;; consistency.  It was most important for analyze-attributes-of-subclasses-for-
;; consistency which can analyze many attributes.

(def-system-variable compiled-items-deferred-for-analysis install nil)

(def-system-variable defer-consistency-analysis? install nil)

(defmacro defer-some-consistency-analysis (&body consistency-analysis-body)
  (let ((return-value? (gensym)))
    `(let ((defer-consistency-analysis? t)
	   (compiled-items-deferred-for-analysis nil)
	   (,return-value? nil))
       (setq ,return-value?
	     (progn ,@consistency-analysis-body))
       ;; Do the deferred analysis.
       (setq defer-consistency-analysis? nil)
       ;; Currently, only does a check-consistency-analysis, and not assert or
       ;; retract analysis.
       (when compiled-items-deferred-for-analysis
	 (loop for deferred-list-cons? = compiled-items-deferred-for-analysis
				       then (cdr-of-cons deferred-list-cons?)
	       for item = (car-of-cons deferred-list-cons?)
	       unless (deleted-frame-p item)
	       do
	   (if (frame-in-use-p item)
	       (check-consistency-analysis item))
	   (clear-block-found-in-search item)
	       until (null (cdr-of-cons deferred-list-cons?))
	       finally
		 (reclaim-gensym-list-given-tail
		   compiled-items-deferred-for-analysis deferred-list-cons?)))
       ,return-value?)))


;;; The macro `defer-consistency-analysis-of-item-p' checks if the
;;; analysis should be deferred or immediately done.

;;; Note that it is currently only legal to defer analysis when the add and
;;; delete arguments are nil.

;; The above restriction may change if we can prove that assertion (args of
;; item, t, nil) and retraction (args of item, nil, t) can be deferred safely.
;; - cpm, 9/23/93

(def-substitution-macro defer-consistency-analysis-of-item-p
    (compiled-item add-as-item-referring-to-name?
		   delete-as-item-referring-to-name?)
  (and defer-consistency-analysis?
       (null add-as-item-referring-to-name?)
       (null delete-as-item-referring-to-name?)))


;;; The function `defer-consistency-analysis-of-item' schedules the item for
;;; later analysis.  Note that the item is assumed to be deferrable.  See
;;; defer-consistency-analysis-of-item-p.  Also, note that the order of analysis
;;; is not preserved when scheduling the items for later analysis.

(defun defer-consistency-analysis-of-item (compiled-item)
  (unless (block-found-in-search-p compiled-item)
    (set-block-found-in-search compiled-item)
    (gensym-push compiled-item compiled-items-deferred-for-analysis)))

;; Modify this function to take add-as-item-referring-to-name? and
;; delete-as-item-referring-to-name? arguments, if we allow assertion and
;; retraction of analysis to be deferred.  This information is needed when later
;; doing the analysis and so should be saved along with the item.  - cpm,
;; 9/23/93




;;;; Instantiating Classes (Making Frames)





;;; `Make-frame' generates instances of classes. An invocation of make-frame
;;; takes the form
;;;
;;;   (make-frame <class>)
;;;
;;; where <class> is a class as described above which has been defined by
;;; def-class.
;;;
;;; This creates a frame and performs initializations on it.  Initializations
;;; performed on frames being made are described in the next section below.  The
;;; frame is returned as this function's sole value.


(defmacro make-frame-classic (class-description-form)
  (let ((class-description (gensym)))
    `(let* ((,class-description ,class-description-form)
	    (block-p (class-description-of-class-p ,class-description 'block))
	    (frame (make-frame-internal ,class-description nil nil t block-p)))
       ;; frame flags only exist on blocks
       (cond (block-p
	      (with-immutable-consistency-analysis (frame)
		;; Call the system initialize methods.
		(initialize-frame frame))
	      ;; Call the g2 initialize methods.   
	      (assert-consistency-analysis-if-allowed frame))
	     (t
	      ;; Call the system initialize methods.
	      (initialize-frame frame)))
       
       frame)))

(defmacro make-frame-body (class-description)
  `(let ((new-frame (make-frame-classic ,class-description)))
     (schedule-task-to-invoke-existential-rules new-frame 'is-created)
     new-frame))

(defun-simple make-frame (class)
  (make-frame-body (class-description class)))

(defun-simple make-frame-of-class-description (class-description)
  (make-frame-body class-description))


;;; `make-frame-without-computed-initializations' makes a frame without
;;; computing slot initializations or running the initialize method.  If
;;; frame-serial-number?  is non-nil, it is used as the frame serial number for
;;; the resulting frame, provided it is a subclass of BLOCK.
;;;
;;; This is intended for use when recreating frames that have been saved in a
;;; KB, or when cloning frames.  Hence, it is called, at present, from
;;; read-frame-for-kb and from clone-frame.

(defun-simple make-frame-without-computed-initializations
    (class-description frame-serial-number? uuid?)
  (make-frame-internal
    class-description
    frame-serial-number?
    uuid?
    nil
    (class-description-of-class-p class-description 'block)))



;;; The function `make-frame-internal' is the internal function used by
;;; make-frame and by make-frame-without-computed-initializations.
;;;
;;; It creates the basic "frame vector".  Frame vectors are managed through the
;;; frame-vector-pool, defined above.  All frame vectors of the same length are
;;; managed together.
;;;
;;; It initializes the "backbone" of frame as needed per the slot init forms and
;;; the supplied arguments.
;;;
;;; Class, class-description, and lookup-structure are placed into the
;;; appropriate slots in the frame as a special case, and their slot init forms
;;; are ignored.  (Note that lookup-structure should be NIL when there are no
;;; user vector slots.)
;;; 
;;; Vector slots and user vector slot init forms are all initialized with their
;;; unevaluted slot init forms.  If eval-slot-init-forms? is true, those slots
;;; that need evaluation are replaced with the result of evaluating their slot
;;; init forms in the appropriate "frame initialization" context, using
;;; initialize-slots-of-frame-needing-evaluation, q.v.  Thus,
;;; eval-slot-init-forms? controls whether or not the computed (non-trivial)
;;; initializations on slots are performed or not.  If they are not, the slots
;;; that require these initializations are left pointing to their slot init
;;; forms, i.e., (:FUNCALL ...).
;;;
;;; For instances of the class BLOCK, it performs a few more important
;;; initializations: e.g., it makes the frame a member of the of the instance
;;; list of its immediate class
;;;
;;; This is a simple function. It returns the frame it created as its sole
;;; value.  It can only be called from inside of a context where there is a
;;; "current KB"; in development, it signals an error when there is no current
;;; KB.

(defun-simple make-frame-internal
    (class-description frame-serial-number? uuid?
		       eval-slot-init-forms-p
		       block-case-p)
  (let ((frame (allocate-frame
                class-description
                frame-serial-number? uuid?
                eval-slot-init-forms-p
                block-case-p)))
    
    ;; Set the slots and flags that are just for blocks.
    (when block-case-p
      (let ((noting-changes-to-kb-p nil)) ; one of the variables in
					;   the "frame initialization"
					;   dynamic extent needs to be
					;   bound around these calls
	
	
	;; Flag whether frame is of a user defined class.
	(setf (class-of-frame-is-user-defined-p frame)
	      (class-description-is-user-defined-p class-description))
	
	;; Flag whether frame has indexed attributes:
	(setf (has-indexed-attributes-p frame)
	      (get-class-feature-in-class-description-if-any
               class-description 'has-indexed-attributes))))
    
    frame))

;; Consider setting up the slot init form of the class and
;; class-description-slot slots so that they point to the proper value, and so
;; need not be explicitly set, for a tad bit of speed and simplicity
;; improvement.  (MHD 7/6/94)

;; See if the flags can be eliminated as special cases here.  Aren't there
;; others that vary with the class description but that don't need to be set
;; here?  Let's emulate those.  (MHD 4/14/94)

;; This code was derived from make-frame-without-computing-slot-initializations,
;; which is now defined in terms of this function, and which has been renamed
;; make-frame-without-computed-initializations.  (MHD 7/6/94)




;;; `Initialize' is a class method that may be defined for any kb-frame.  It is
;;; called during initializations of a frame, i.e., within make-frame and
;;; clone-frame.  It is not called when a frame is loaded.  See also the cleanup
;;; method and the initialize-after-reading method.  The method takes the frame
;;; being created as an argument.  ...

;;; By convention, method implementations for a given class instance X are
;;; required to do (funcall-superior-method X), usually before doing their own
;;; initializing.

(def-generic-method initialize (kb-frame))

(def-generic-method prepare-to-saving-frame (kb-frame))
(def-generic-method on-frame-saved (kb-frame))

(def-class-method prepare-to-saving-frame (kb-frame)
  (declare (ignore kb-frame))
  nil)

(def-class-method on-frame-saved (kb-frame)
  (declare (ignore kb-frame))
  nil)

;;; The function `initialize-frame' calls the initalize method on frame, if any,
;;; in the appropriate "frame initialization" context.  This is intended for use
;;; as a subfunction of make-frame and clone-frame.
;;; 
;;; As an additional initialization, this always calls
;;; note-as-preexisting-frame-if-appropriate for the following reason. When a
;;; block is created during the main portion of read-kb other than as one being
;;; read, there is the possibility of giving it a frame-serial-number that is
;;; too low.  This can happen because during incremental save, the highest
;;; frame-serial-number is not known till after the save, and is given in the
;;; plist-at-end.  Therefore, these frames are noted, and an adjustemnt is made
;;; after reading.  During the read, saving their frame-serial-numbers and/or
;;; executing frame-has-been-reprocessed-p is problematic.  [-ml '91]

(defun-void initialize-frame (frame)
  (let ((noting-changes-to-kb-p nil)
	(current-block-of-dependent-frame 'dependent-frame-has-no-owner)
	(frame-being-made frame))
    (funcall-simple-method-if-any-macro 'initialize frame)
    (note-as-preexisting-frame-if-appropriate frame)))

;; Consider abstracting/defining "frame initialization" as a dynamic extent,
;; i.e., the special variable let bindings common to the above two functions.
;; Review whether clone-frame and read-frame-for-kb need to set up this same
;; dynamic extent!





;;;; Recreation of Frames Saved in KBs



;;; The recreation of a frame saved in a KB is a three-step process.  All three
;;; steps are performed inside of read-frame-for-kb:
;;; 
;;; (1) Obtaining a frame structure.  This is done by read-frame-for-kb, which
;;; does it by either finding the instance socked away in a hash table, or by
;;; calling make-frame-without-computed-initializations.  (A frame is
;;; socked away into a hash table when a reference to it is read, and it does
;;; not yet exist.  To make it exist for purposes of referencing, it is also
;;; created by make-frame-without-computed-initializations.)
;;;
;;; (2) Reading slots from the KB, and setting them in the frame.  This is done
;;; explicitly by the body of read-frame-for-kb.
;;;
;;; (3) Initializing slots that needed computation, but that were not saved out
;;; in the KB.  (Such slots are rather rare.  They can occur when certain
;;; changed to the definitions of classes or slots take place between the
;;; version of G2 in which the save happened and the version in which the load
;;; is taking place.)









;;;; Reversible changes.

;;; Note-as-kb-state-change? is a variable which is globally nil. It should be
;;; bound to t whenever a kb-savable slot of a frame is modified, and the
;;; modification is a reversible one, that is, one which is noted in
;;; original-kb-state-plist, and will be reset.

;;; This variable is chosen because in many cases it is already bound to t at
;;; the appropriate time.

(defvar note-as-kb-state-change? nil)

;; I should probably review a bit more with ML! (MHD 9/27/91)



;;; Reversible-changes:

;;; A grep on 4/16/91 showed the following calls to note-kb-state-change.
;;; ACTIONS			change-system-attribute
;;; 				now-change-system-attribute needs one!!
;;; BOOKS                       change-text-of-message
;;; BOXES			change-color-of-text-box
;;; CONNECT2			change-color-pattern-of-connection
;;; 				change-color-of-connection
;;; 				rotate-and-reflect-icon
;;; DRAW			change-size-of-workspace-to-minimum
;;; ENTITIES			change-color-of-icon, change-color-of-icon
;;;                             change-color-pattern-of-icon
;;; PANES			change-color-of-workspace
;;; PROC-EVAL			execute-change-system-attribute-instruction
;;; STACK-ACTS			change-system-attribute
;;;                                    (def-funcalled-instruction)
;;; TABLES			change-color-of-text-cell








;;;; Useful Frame Functions for Developers





;;; The function `lookup-structure-histogram' prints a histogram of the number
;;; of frames with particular lookup-structure vector lengths.  It also makes a
;;; guess at how many bytes that consumes.

#+development
(defun lookup-structure-histogram ()
  (let ((counts (make-array 1024 :initial-element 0))
	(total-bytes 0)
	(total 0))
    (loop for frame being each class-instance of 'root
	  do
      (incf total)
      (incf (svref counts (length (lookup-structure frame)))))
    (loop for index from 1 below 1024 do
      (incf total-bytes
	    (*f (bytes-per-simple-vector index) (svref counts index))))
    (format t "~%Lookup Structure Histogram, ~a frames, ~a bytes.~%"
	    total total-bytes)
    (loop for index from 0 below 1024
	  for count = (svref counts index)
	  for bytes = (if (= index 0)
			  0
			  (* (bytes-per-simple-vector index) count))
	  do
      (unless (zerop count)
	(format t "~6d vectors at ~4d elements, ~6d bytes, ~2d% of total, ~2d% of bytes~%"
		count
		index
		bytes
		(floor (* count 100) total)
		(floor (* bytes 100) total-bytes))))))




;;; The function `estimate-default-slot-value-memory-usage' will iterate over
;;; every frame in the system, and over every user-defined slot, and will
;;; determine the counts of defaulted to non-defaulted slot values in each slot
;;; of each frame.

#+development
(defun estimate-default-slot-value-memory-usage ()
  (let ((default-valued 0)
	(non-default-valued 0)
	(total-frames 0)
	(total-slots 0)
	(default-symbols 0))
    (loop for frame being each class-instance of 'root
	  for class-description = (class-description-slot frame)
	  for slot-descriptions = (slot-descriptions class-description)
	  do
      (incff total-frames)
      (loop for slot-description in slot-descriptions
	    do
	(incf total-slots)		; might be bignum?
	(when (user-defined-slot-description-p slot-description)
	  (cond ((eq (get-slot-description-value frame slot-description)
		     (slot-init-form slot-description))
		 (incff default-valued)
		 (when (and (symbolp (slot-init-form slot-description))
			    (get-instance-with-name-if-any
			      'procedure (slot-init-form slot-description)))
		   (incff default-symbols)))
		(t
		 (incff non-default-valued))))))
    (format t "~%Slot Usage Report:  ~a total frames, ~a total slots, ~a user slots~%"
	    total-frames total-slots (+f default-valued non-default-valued))
    (format t "~a default valued, ~a non-default-valued, ~a default symbols~%"
	    default-valued non-default-valued default-symbols)
    (format t "~7d bytes using our approach~%"
	    (*f (+f default-valued non-default-valued) 4))
    (format t "~7d bytes using lookup slots~%"
	    (*f non-default-valued 8))
    (format t "Ignoring defaulted symbols...~%")
    (format t "~7d bytes using our approach~%"
	    (*f (+f (-f default-valued default-symbols) non-default-valued) 4))
    (format t "~7d bytes using lookup slots~%"
	    (*f non-default-valued 8))
    ))




;;; The function `count-class-hash-table-entries' will count the number of
;;; entries in the slot-descriptions-hash-table of every defined class.

#+development
(defun count-class-hash-table-entries (&optional (base-class 'root))
  (loop for class being each subclass of base-class
	for class-description = (class-description class)
	for hash-table = (slot-descriptions-hash-table class-description)
	sum (loop for binary-tree-value being each binary-tree-value of hash-table
		  count hash-table)))
    








;;;; Abstraction Around Subblocks



;;; This section provides a set of facilities that enable
;;; the subblocks data structure to be reengineered.  These
;;; facilities include:
;;;   subblock-memq <subblock> <block> -> <boolean>
;;;   first-subblock <block> -> <subblock>
;;;   has-only-one-subblock-p -> <boolean>
;;;   has-subblocks-p -> <boolean>

;;; After this file it becomes possible to write:
;;;   (loop for subblock being each subblock of block
;;;      do ...)

;; - ben 4/5/93




;;; `Has-subblocks-p' is documented in this section's heading.

(defmacro has-subblocks-p (block)
  #-subblocks-v2
  `(subblocks ,block)
  #+subblocks-v2
  (avoiding-variable-capture (&aux subblocks)
    `(let ((,subblocks (subblocks ,block)))
       (and ,subblocks
	    (constant-queue-non-empty-p ,subblocks)))))

(defmacro empty-subblocks-p (block)
  #-subblocks-v2
  `(null (subblocks ,block))
  #+subblocks-v2
  (avoiding-variable-capture (&aux subblocks)
    `(let ((,subblocks (subblocks ,block)))
       (or (null ,subblocks)
	   (constant-queue-empty-p ,subblocks)))))

;;; `Has-only-one-subblock-p' is documented in this section's heading.

#-subblocks-v2
(defmacro has-only-one-subblock-p (block)
  (avoiding-variable-capture (&aux subblocks)
    `(let ((,subblocks (subblocks ,block)))
       (and ,subblocks
	    (null (cdr ,subblocks))))))

;;; `First-subblock' is documented in this section's heading.

#-subblocks-v2
(defmacro first-subblock (block)
  `(car (subblocks ,block)))

#-subblocks-v2
(defmacro second-subblock (block)
  `(second (subblocks ,block)))

#-subblocks-v2
(defmacro last-subblock (block)
  `(first (last (subblocks ,block))))

;;; `Subblock-memq' is documented in this section's heading.

#-subblocks-v2
(defmacro subblock-memq (subblock block)
  `(memq ,subblock (subblocks ,block)))

;;; The subblock's loop path is documented in this section's heading.

#-subblocks-v2
(defun-for-macro subblocks-path
		 (path-name variable data-type prep-phrases inclusive? allowed-prepositions data)
  (declare (ignore data-type data allowed-prepositions))
  (when (null prep-phrases)
    (error "OF is missing in ~S iteration path of ~S" path-name variable))
  (when inclusive?
    (error "Inclusive stepping is not supported in ~S path of ~S (prep-prase = ~:S)"
	   path-name variable prep-phrases))
  (let* ((iteration-domain (cadar prep-phrases))
	 (remaining-subblocks-variable (loop-gentemp))
	 (generator-bindings `((,remaining-subblocks-variable (subblocks
								,iteration-domain))
			       (,variable nil)))
	 (generator-initialize nil)
	 (generator-eof-p `(null ,remaining-subblocks-variable))
	 (generator-advance
	   `(,variable
	     (car-of-cons ,remaining-subblocks-variable)
	     ,remaining-subblocks-variable
	     (cdr-of-cons ,remaining-subblocks-variable))))
    `(,generator-bindings
      ,generator-initialize
      ,generator-eof-p
      nil
      nil
      ,generator-advance)))

#+subblocks-v2
(defun-for-macro subblocks-path
    (path-name variable data-type prep-phrases inclusive?
               allowed-preposistions data)
  (declare (ignore data-type data allowed-preposistions))
  (when (null prep-phrases)
    (error "OF is missing in ~S iteration path of ~S."
           path-name variable))
  (when inclusive?
    (error "Inclusive stepping is not supported in ~s path of ~s ~
            (prep-phrase = ~s)"
           path-name variable prep-phrases))
  (let* ((block-form-entry (assq 'of prep-phrases))
	 (block-form (second block-form-entry))
	 (queue-form (loop-gentemp 'queue-form-))
         (next-queue-element (loop-gentemp 'next-queue-element-))
         (init-bindings
           `((,queue-form (subblocks ,block-form))
             (,next-queue-element nil)
             (,variable nil)))
         (prologue-forms
           `((when ,queue-form
	       (setq ,next-queue-element
                   #-Lockfree-Deque (constant-queue-head ,queue-form)
                   #+Lockfree-Deque (constant-queue-next
                                      (constant-queue-head ,queue-form) ,queue-form)))))
         (pre-step-tests
	   #-Lockfree-Deque
	   `(eq ,next-queue-element ,queue-form)
	   #+Lockfree-Deque
           `(null ,next-queue-element))
         (steppings nil)
         (post-step-tests nil)
         (post-step-settings
           `(,variable (queue-datum ,next-queue-element)
             ,next-queue-element
             (constant-queue-next ,next-queue-element ,queue-form))))
    `(,init-bindings
      ,prologue-forms
      ,pre-step-tests
      ,steppings
      ,post-step-tests
      ,post-step-settings)))

;; Apparently a loop path returns these values:
;; (values <bindings-for-generator> 
;;	   <prolog-statements>
;;	   <test1-predicate>
;;	   <advance-assignment-pairs2>
;;	   <test2-predicate>
;;	   <advance-assignment-pairs>)
;; That are then inserted into the loop as so:
;;(let <bindings-for-generator>                 ;; Create the generator.
;;  (block nil
;;    (tagbody
;;      <prolog-statements>                     ;; Initialize the generator.
;;     next-loop
;;	(when <test1-predicate> (go end-loop)) 	;; 1. Can the generator advance?
;;	(setq <advance-assignment-pairs>) 	;; 2. Try advancing it.
;;	(when <test2-predicate> (go end-loop))	;; 3. Will is succeed?
;;	(psetq <advance-assignment-pairs-2>)	;; 4. Finish advancing it.
;;      <body>
;;	(go next-loop)
;;     end-loop)))

;;; The subblock's loop path is documented in this section's heading.

(define-loop-path (subblocks subblock)
		  subblocks-path (of))

#+subblocks-v2
(defmacro subblock-memq (subblock block)
  `(loop for b being each subblock of ,block
	 when (eq b ,subblock)
	 return t))

#+subblocks-v2
(defun-simple has-only-one-subblock-p (block)
  (loop with count fixnum = 0
	for subblock being each subblock of block
	do
	  (incff count)
	  (when (>f count 1) (loop-finish))
	finally
	  (if (=f count 1) (return t) (return nil))))

#+subblocks-v2
(defun-simple first-subblock (block)
  (loop for subblock being each subblock of block
	do (return subblock)))

#+subblocks-v2
(defun-simple second-subblock (block)
  (loop with count fixnum = 0
	for subblock being each subblock of block
	do
    (incff count)
    (when (=f count 2)
      (return subblock))))

#+subblocks-v2 ; a fast version is possible by looping reversely
(defun-simple last-subblock (block)
  (loop for subblock being each subblock of block
	finally (return subblock)))

#+subblocks-v2
(defun upgrade-subblocks (blocks)
  (let ((constant-queue (make-empty-constant-queue)))
    (loop for block in blocks do
      (constant-queue-enqueue constant-queue block))
    constant-queue))

;;; `Outline-subblocks' is a development only function that displays
;;; the subblock hierarchy ala outline-tree-of-nodes.

#+development
(defun outline-subblocks (block &key
			   (printer #'princ)
			   ((:print-length *print-length*) 10)
			   ((:print-level *print-level*) 4)
			   (visible-p #'(lambda (node) (declare (ignore node)) t))
			   (inferiors #'(lambda (block) (subblocks block))))
  (outline-tree-of-nodes inferiors block 0 (cons nil nil)
			 visible-p printer)
  block)


#+development
(defun graph-subblocks (block)
  (loop with any
	for super first (superblock? block)
		  then (superblock? super)
	while super
	do (format t "~s~%" super)
	   (setq any t)
	finally
	  (when any
	    (format t "----------------~%")))
  (print-random-tree
    block
    #'(lambda (block) (when (framep block)
			(append (subblocks block) (connections block))))
    :duplicates t))


#+development
(def-emacs-mouse-command outline (object)
  (cond ((and (framep object) (block-p object))
	 (graph-subblocks object))
	(t
	 (format t "Sorry, ~s is not a block." object))))



(def-class-method initialize (system-item)
  (declare (ignore system-item))
  ;;(update-frame-notes-for-duplicate-uuids (item-uuid system-item))
  nil)

(def-class-method initialize-after-reading (system-item)
  ;; Check whether the uuid on the block is indeed unique. If it isn't,
  ;; put frame notes on the affected blocks.
  (funcall-superior-method system-item) ; per convention
  ;;(update-frame-notes-for-duplicate-uuids (item-uuid system-item))
  nil)

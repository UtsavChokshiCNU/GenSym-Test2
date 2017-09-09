;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module MEM-SYSPROC

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved

;;; John Hodgkinson

;; 18 Oct 1993

;; jh, 10/18/93.  Split this file from FILE-IO and changed the name of FILE-IO
;; to FILE-SYSPROC.

;;; This module contains system procedures that allow the G2 user to profile
;;; memory use in knowledge bases.



(declare-forward-reference superior-frame function)
(declare-forward-reference make-transient-item function)



;;;; System Procedures to Walk Memory

;; Notes on frame structure, current as of 8/4/93.

;; Lookup slots with default values do not take up any memory per frame -- the
;; default values are stored in the class definition.  Every non-default lookup
;; slot takes up 3 conses -- 1 to paste it into the slot-description alist of
;; the frame, and 2 to form an alist entry, a 2-list consisting of slot-name and
;; slot-value.  As an interesting aside, the first fact revealed by the
;; prototype is that if a table is created for a variable, it gains a
;; non-defaulted lookup slot at the cost of 3 conses, even after the table is
;; deleted.  There are several similar slots and this is a known problem.

;; Vector slots reside in a simple vector (created using make-array).  Vectors
;; of a given size are kept in pools, and allocated in batches in such a way as
;; to ensure a minimum 75% usage.  I am not sure how we can report this
;; allocation scheme to the user, because it is unclear whether we should charge
;; this to the class definition or to the instance.  The root class vector has
;; three elements.  The first is the name of the class, the second holds the
;; slot description, and the third points to the class description, which in
;; turn contains the default slot description, which shares structure with the
;; slot description.

;; User vector slots are 4.0 improvements that, as far as I can tell,
;; have the same memory characteristics as vector slots.

;; Slot-groups are documented in FRAMES3 as of 8/4/93.  A slot group is a vector
;; containing subslots that some frames lack.  Hence such a frame can be made
;; smaller by declining to allocate a slot-group vector when the frame is
;; allocated.  Note that this ends up partitioning classes in a way orthogonal
;; to the class hierarchy (as an aside, note that this therefore manifests a
;; deficiency in single inheritance protocol).  The only important partition so
;; far is between frames that are visible on some workspace and those that are
;; not (like subtables).  The icon-slot-group, currently the only slot-group in
;; existence, deals with this partition.  The icon-slot-group is only filled for
;; those displayable frames which need the information it contains.  An
;; icon-slot-group is a def-structure with a :type option and without a :named
;; option, which means that its length is equal to the number of slots it has,
;; currently 7.

;; Note that some slots overlap, and some slots are purely informative and do
;; not contribute to the count.  As long as we are walking, though, we might
;; find this information useful.

;; To do:

;; Note that this facility is workspace-based, since a kb-workspace is the most
;; comprehensive frame from which to walk looking for memory usage.  We should
;; consider allowing users to measure memory not based on any workspace, such as
;; procedure invocations.

;; It might be nice to collect all classes walked, so that users can diff
;; successive memory-profile objects and tell what classes they might be
;; creating and not deleting.

;; Consider adding informative slots to the memory-profile class, detailing
;; things at the G2 user's level (like histories, procedure invocations, and GSI
;; value queues).  These slots are not necessary to measure the total memory
;; consumed, but could help with our never-ending battle to convince customers
;; to examine the legitimate memory allocation in their KB before reporting
;; leaks.

(def-class (memory-profile (block))
  (vector-slots
    0 not-user-editable (type attribute) vector-slot)
  (user-vector-slots
    0 not-user-editable (type attribute) vector-slot)
  (lookup-slots
    0 not-user-editable (type attribute) vector-slot)
  (defaulted-vector-slots
    0 not-user-editable (type attribute) vector-slot)
  (defaulted-user-vector-slots
    0 not-user-editable (type attribute) vector-slot)
  (defaulted-lookup-slots
    0 not-user-editable (type attribute) vector-slot)
  (conses
    0 not-user-editable (type attribute) vector-slot)
  (symbols
    0 not-user-editable (type attribute) vector-slot)
  (double-floats
    0 not-user-editable (type attribute) vector-slot)
  (fixnums
    0 not-user-editable (type attribute) vector-slot)
  (characters
    0 not-user-editable (type attribute) vector-slot)
  (functions
    0 not-user-editable (type attribute) vector-slot)
  (immediates
    0 not-user-editable (type attribute) vector-slot)
  (simple-general-arrays
    nil not-user-editable (type simple-general-arrays) vector-slot)
  (simple-unsigned-byte-16-arrays
    nil not-user-editable (type simple-unsigned-byte-16-arrays) vector-slot)
  (simple-unsigned-byte-8-arrays
    nil not-user-editable (type simple-unsigned-byte-8-arrays) vector-slot)
  (double-float-arrays
    nil not-user-editable (type double-float-arrays) vector-slot)
  (adjustable-strings
    nil not-user-editable (type adjustable-strings) vector-slot)
  (simple-strings
    nil not-user-editable (type simple-strings) vector-slot)
  (frame-vectors
    nil not-user-editable (type frame-vectors) vector-slot)
  )

(defparameter single-counter-slots-in-memory-profile
  '(
    vector-slots
    user-vector-slots
    lookup-slots
    defaulted-vector-slots
    defaulted-user-vector-slots
    defaulted-lookup-slots
    conses
    symbols
    double-floats
    fixnums
    characters
    immediates
    ))

(defparameter by-length-slots-in-memory-profile
  '(
    simple-general-arrays
    simple-unsigned-byte-16-arrays
    simple-unsigned-byte-8-arrays
    double-float-arrays
    adjustable-strings
    simple-strings
    frame-vectors
    ))

(defun-void write-slot-value-for-by-length-attribute (by-length-attribute)
  (if (consp by-length-attribute)
      (loop for (length . count) in by-length-attribute
	    for length-and-count-cons on by-length-attribute
	    for last-length-and-count-p = (null (cdr length-and-count-cons))
	    do
	(twrite-string "(" )
	(twrite-fixnum length)
	(twrite-string " . ")
	(twrite-fixnum count)
	(twrite-string ")" )
	(unless last-length-and-count-p
	  (twrite-line-separator)))
      (twrite-string "none")))
    
(defmacro def-slot-value-writer-for-by-length-attribute (slot)
  `(def-slot-value-writer ,slot (by-length-attribute)
     (write-slot-value-for-by-length-attribute by-length-attribute)))

(def-slot-value-writer-for-by-length-attribute simple-general-arrays)

(def-slot-value-writer-for-by-length-attribute simple-unsigned-byte-16-arrays)

(def-slot-value-writer-for-by-length-attribute simple-unsigned-byte-8-arrays)

(def-slot-value-writer-for-by-length-attribute double-float-arrays)

(def-slot-value-writer-for-by-length-attribute adjustable-strings)

(def-slot-value-writer-for-by-length-attribute simple-strings)

(def-slot-value-writer-for-by-length-attribute frame-vectors)

(def-hash-table items-encountered-in-memory-walk-hash-table
		:constructor     make-items-encountered-in-memory-walk
		:accessor        get-item-encountered-in-memory-walk
		:clearer         clear-items-encountered-in-memory-walk
		:key-comparitor  eq
		:size            131 ; use a prime number
		:hash-function-or-macro sxhash-symbol
		)

(def-system-variable items-encountered-in-memory-walk MEM-SYSPROC
  (:funcall make-items-encountered-in-memory-walk))

(defmacro incf-by-lengths-macro
    (list-kept-by-lengths new-length &optional number-of-increments?)
  (avoiding-variable-capture
      (list-kept-by-lengths new-length number-of-increments?)
    `(let ((counter-for-this-length? (assoc ,new-length ,list-kept-by-lengths))
	   (number-of-increments (or ,number-of-increments? 1)))
       (cond
	 (counter-for-this-length?
	  (incff (cdr counter-for-this-length?) number-of-increments)
	  ,list-kept-by-lengths)
	 (t (slot-value-cons (slot-value-cons ,new-length number-of-increments)
			     ,list-kept-by-lengths))))))

;; The old (1.7) Chestnut translator balks at a lambda-expression in a
;; define-modify-macro form.  Hence the seemingly superfluous indirection here.

(define-modify-macro incf-by-lengths
  (new-length &optional number-of-increments?)
  incf-by-lengths-macro)

(defvar subframe-depth 0)
(defvar memory-walk-verbose-p nil)

(defun-simple suppress-verbosity-for-cons-p (thing)
  (cond ((or (null thing) (text-string-p thing) (symbolp thing) (numberp thing))
	 t)
	((not (consp thing)) nil)
	(t (and (suppress-verbosity-for-cons-p (car thing))
		(suppress-verbosity-for-cons-p (cdr thing))))))

(defmacro unless-item-encountered-and (do-encountered-test-p &body body)
  (if (constantp do-encountered-test-p)
      (if (eval do-encountered-test-p)
	  `(let ((already-encountered-item-p
		  (get-item-encountered-in-memory-walk
		    thing-to-walk
		    items-encountered-in-memory-walk)))
	    (unless already-encountered-item-p
	      (setf (get-item-encountered-in-memory-walk
		      thing-to-walk
		      items-encountered-in-memory-walk)
		    t)
	      ,@body))
	  `(progn ,@body))
      (let ((body-tag (make-symbol "BODY-TAG"))
	    (block-tag (make-symbol "BLOCK-TAG")))
	`(block ,block-tag
	   (tagbody
	      (cond
		(,do-encountered-test-p
		 (let ((already-encountered-item?
			 (get-item-encountered-in-memory-walk
			   thing-to-walk
			   items-encountered-in-memory-walk)))
		   (cond
		     (already-encountered-item?
		      (return-from ,block-tag))
		     (t (setf (get-item-encountered-in-memory-walk
				thing-to-walk
				items-encountered-in-memory-walk)
			      t)
			(go ,body-tag)))))
		(t (go ,body-tag)))
	      ,body-tag
	      ,@body)))))

(defvar do-circularity-check-walking-through-conses-p t)

(defvar do-circularity-check-walking-through-simple-vectors-p nil)

(defmacro development-when (test &body body)
  (when (eval-feature :development)
    `(when ,test ,@body)))

(defmacro development-if (test then-form &optional else-form)
  (if (eval-feature :development)
      `(if ,test ,then-form ,else-form)
      else-form))

(defmacro development-let (specs &body body)
  (if (eval-feature :development)
      `(let ,specs ,@body)
      `(progn ,@body)))

(defvar walk-queue-head nil)
(defvar walk-queue-tail nil)

(defmacro data-of-walk-node (walk-node)
  `(svref ,walk-node 0))

(defmacro next-of-walk-node (walk-node)
  `(svref ,walk-node 1))

(defmacro check-cons-of-walk-node (walk-node)
  `(svref ,walk-node 2))

(defmacro check-simple-vector-of-walk-node (walk-node)
  `(svref ,walk-node 3))

(defun make-walk-node (thing-to-walk)
  (let ((walk-node (allocate-managed-simple-vector 4)))
    (setf (data-of-walk-node walk-node) thing-to-walk)
    (setf (next-of-walk-node walk-node) nil)
    (setf (check-cons-of-walk-node walk-node) do-circularity-check-walking-through-conses-p)
    (setf (check-simple-vector-of-walk-node walk-node) do-circularity-check-walking-through-simple-vectors-p)
    walk-node))

(defun reclaim-walk-node (walk-node)
  (reclaim-managed-simple-vector walk-node))

(defun append-to-walk-queue (thing-to-walk)
  (let ((walk-node (make-walk-node thing-to-walk)))
    (cond
      (walk-queue-head
	(setf (next-of-walk-node walk-queue-tail) walk-node)
	(setq walk-queue-tail walk-node))
      (t
	(setq walk-queue-head walk-node)
	(setq walk-queue-tail walk-node)))))

(defun pop-walk-queue ()
  (let ((walk-node walk-queue-head))
    (setq walk-queue-head (next-of-walk-node walk-node))
    walk-node))

(defun-simple walk-for-memory-recursion (thing-to-walk profile-object)
  (let ((walk-queue-head nil)
	(walk-queue-tail nil))
    (append-to-walk-queue thing-to-walk)
    (loop while walk-queue-head
	  for walk-node = (pop-walk-queue)
	  for thing-to-walk =  (data-of-walk-node walk-node)
	  for do-circularity-check-walking-through-conses-p = (check-cons-of-walk-node walk-node)
	  for do-circularity-check-walking-through-simple-vectors-p = (check-simple-vector-of-walk-node walk-node)
	  do
      (development-when memory-walk-verbose-p
	(format t "~&~vtthing: ~s~%" subframe-depth thing-to-walk))
      (reclaim-walk-node walk-node)
      (cond
	;; suspend NIL early
	((null thing-to-walk))
	;; frames
	((framep thing-to-walk)
	 ;; The following use of unless-item-encountered-and assumes that frames can
	 ;; contain references to themselves at any place, so we always perform a
	 ;; circularity check.
	 (unless-item-encountered-and
	   t
	   (walk-frame-for-memory thing-to-walk profile-object)
	   (when (frame-of-class-p thing-to-walk 'variable-or-parameter)
	     (let* ((stored-histories?
		      (variable-or-parameter-stored-histories? thing-to-walk))
		    (history-ring-buffer
		      (and stored-histories?
			   (car (cascaded-ring-buffers stored-histories?)))))
	       (when history-ring-buffer
		 (append-to-walk-queue history-ring-buffer)
		 (append-to-walk-queue (history-value-vector history-ring-buffer))
		 (append-to-walk-queue (history-time-vector history-ring-buffer)))))))
	;; The following clauses for strings and specifically-typed simple numeric
	;; arrays assume that these data structures are never shared, making a
	;; circularity check unnecessary here.  Note that if these particular data
	;; structures are shared, the memory walk does not loop forever, but the
	;; memory measurement is thrown off by the duplication.
	((simple-string-p thing-to-walk)
	 (incf-by-lengths (simple-strings profile-object)
			  (length thing-to-walk)))
	((stringp thing-to-walk) ; text-strings are handled by (simple-array (unsigned-byte 16) (*))
	 (incf-by-lengths (adjustable-strings profile-object)
			  (length thing-to-walk)))
	((typep thing-to-walk '(simple-array (unsigned-byte 8) (*)))
	 (incf-by-lengths (simple-unsigned-byte-8-arrays profile-object)
			  (length thing-to-walk)))
	((typep thing-to-walk '(simple-array (unsigned-byte 16) (*)))
	 (incf-by-lengths (simple-unsigned-byte-16-arrays profile-object)
			  (length thing-to-walk)))
	((typep thing-to-walk '(simple-array double-float (*)))
	 (incf-by-lengths (double-float-arrays profile-object)
			  (length thing-to-walk)))
	((managed-array-p thing-to-walk)
	 (unless-item-encountered-and
	   t
	   (let ((length-of-managed-array (managed-array-length thing-to-walk)))
             ;; jh, 4/15/96.  Managed arrays have a new optimization that avoids
             ;; indirection when the array will fit in the spine of the vector.  So
             ;; now we only compute the memory consumed by the buffers if the length
             ;; of the managed array overflows the length of the spine.
	     (cond
	       ((>f length-of-managed-array maximum-in-place-array-size)
		(let ((number-of-managed-buffers
			(ceilingf-positive
			  length-of-managed-array
			  maximum-managed-array-buffer-size)))
		  (when (>f number-of-managed-buffers 0)
		    (let ((number-of-managed-buffers-minus-one
			    (1-f number-of-managed-buffers)))
		      ;; Measure space actually consumed by the managed array, not
		      ;; just space the user can see.  First, measure the space in
		      ;; the full buffers.
		      (incf-by-lengths (simple-general-arrays profile-object)
				       maximum-managed-array-buffer-size
				       number-of-managed-buffers-minus-one)
		      ;; Next, measure the space in the final, partially-filled
		      ;; buffer.
		      (incf-by-lengths (simple-general-arrays profile-object)
				       (length
					 (managed-array-buffer
					   thing-to-walk
					   number-of-managed-buffers-minus-one))))
		    ;; Measure the space consumed by the enclosing array structure
		    ;; itself.  Currently (jh, 8/7/95), this is the number of
		    ;; buffers plus 1 slot for the unique identifying tag and 1 slot
		    ;; for the array length.
		    (incf-by-lengths (simple-general-arrays profile-object)
				     (+f number-of-managed-buffers
					 managed-array-index-offset)))))
	       ;; Else the array is in the spine itself, and we only use as many
	       ;; elements as we need, plus 1 slot for the unique identifying tag
	       ;; and 1 slot for the array length.
	       (t (incf-by-lengths (simple-general-arrays profile-object)
				   (+f length-of-managed-array
				       managed-array-index-offset))))
	     ;; Finally, recurse only on the legitimate contents of the managed
	     ;; array, since the out-of-bounds contents may not have been cleared
	     ;; from the last time the managed array's buffers were in use.  We
	     ;; don't want to charge the user for those; besides, they may contain
	     ;; discarded pointers to circular or large objects (like the
	     ;; gensym-cons pool).
	     (loop for index from 0 below length-of-managed-array
		   do
	        (append-to-walk-queue (managed-svref thing-to-walk index))))))
	((typep thing-to-walk 'simple-vector)
	 ;; When thing-to-walk is an available-frame-vector we do not
	 ;;   want to recurse -- this is reclaimed memory!!  This can happen
	 ;;  in managed arrays whose elements get reclaimed. If it can be proved
	 ;;  that managed arrays are the ONLY place this could happen, then it
	 ;;  would be safe to move this check earlier to the cond case for managed-arrays,
	 ;;  avoiding the overhead of a recursive call.  The check was put here since it was
	 ;; considered safer. -giba, 2/19/98
	 ;;
	 ;;  Note the residual problem (bug) that if a reclaimed frame-vector is later
	 ;;    re-allocated, it will then be incorrectly counted since the walker will merrily
	 ;;   recurse over it.  -giba, 2/19/98
	 (unless (and (<f 1 (length thing-to-walk))
		      (deleted-frame-p thing-to-walk))
	   ;; jh, 9/1/93.  The folowing use of unless-item-encountered-and used to
	   ;; assume that named def-structures may be shared but that unnamed ones
	   ;; will not be, making a circularity check unnecessary in that case.  Alas,
	   ;; things are not that simple.  The list-structure slot of an instance of
	   ;; the class g2-list contains an unnamed def-structure that can point to
	   ;; itself, either just after initialization, or when the G2 user herself
	   ;; implements circular lists.
	   (unless-item-encountered-and
	     (or (allocated-named-gensym-structure-p thing-to-walk)
		 do-circularity-check-walking-through-simple-vectors-p)
	     (let ((length-of-simple-array (length thing-to-walk)))
	       (incf-by-lengths (simple-general-arrays profile-object)
				length-of-simple-array)
	       (cond
		 ((allocated-named-gensym-structure-p thing-to-walk)
		  (walk-named-g2-structure-for-memory thing-to-walk profile-object))
		 (t
		   (loop for index from 0 below length-of-simple-array
			 do
		     (append-to-walk-queue (svref thing-to-walk index)))))))))
	;; This is special list (xxx . item-reference), do not walk into it.
	((evaluation-item-reference-p thing-to-walk)
	 (incff (conses profile-object)))
	((consp thing-to-walk)
	 ;; The following use of unless-item-encountered-and assumes that conses in
	 ;; slots without a defined slot-value-reclaimer are never shared, making a
	 ;; circularity check unnecessary in that case.
	 (unless-item-encountered-and
	   do-circularity-check-walking-through-conses-p
	   (incff (conses profile-object))
	   (append-to-walk-queue (car thing-to-walk))
	   (append-to-walk-queue (cdr thing-to-walk))))
	((typep thing-to-walk 'double-float)
	 (incff (double-floats profile-object)))
	;; We keep a count of the number of symbols encountered during the walk.
	;; This is not immediately useful for memory measurement in this first pass
	;; implementation, but a finer-grained second pass would address whom to
	;; charge for the memory consumed by symbols.
	((symbolp thing-to-walk)
	 (incff (symbols profile-object)))
	;; We record information about immediate types as long as we're here.  It
	;; might come in handy someday.
	((typep thing-to-walk 'fixnum)
	 (incff (fixnums profile-object)))
	((typep thing-to-walk 'character)
	 (incff (characters profile-object)))
	((functionp thing-to-walk)
	 (incff (functions profile-object)))
	;; We don't expect to reach this clause.  If we reach it in development, we
	;; get a continuable error.  If we reach this clause in distribution, we
	;; cease walking and assume the item is immediate.  This could cause
	;; inaccuracies in the memory measuremnet.
	(t
	  #+development
	  (cerror "WALK-FOR-MEMORY-RECURSION:  unknown thing ~a"
		  "Count as `immediate' and proceed"
		  thing-to-walk)
	  (incff (immediates profile-object)))))))


(defvar special-slot-names-for-memory-walk nil)

(defun-void walk-named-g2-structure-for-memory (g2-structure profile-object)
  (let* ((raw-name (g2-type-name-of-named-simple-vector g2-structure))
	 (type-description?
	   (type-description-of-unique-type-name-of-gensym-structure raw-name))
;	 (type-name (if type-description?
;			(name-of-type-description type-description?)
;			raw-name))
	 (slots (if type-description?
		    (slot-descriptions-of-type-description type-description?)
		    #+development
		    (error "bad assumption about type-descriptions - see JED"))))
    (loop for slot-name-or-description in slots
	  as slot-name = (if (symbolp slot-name-or-description)
			     slot-name-or-description
			     (car slot-name-or-description))
	  as i from 1
	  do
      (let ((special-slot-entry?
	      (assq slot-name special-slot-names-for-memory-walk)))
	(cond (special-slot-entry?
	       (funcall (cdr special-slot-entry?)
			g2-structure
			(svref g2-structure i)
			profile-object))
	      (t
		(append-to-walk-queue (svref g2-structure i))))))))

(defmacro def-special-slot-for-memory-walk (slot-name &body body)
  (let ((function-for-special-slot-value
	  (intern (format nil "WALK-MEMORY-FOR-VALUE-OF-~a" slot-name))))
    `(progn (defun-void ,function-for-special-slot-value
		   (frame slot-value profile-object)
	      ,@body)
	    (pushnew (cons ',slot-name
			   ',function-for-special-slot-value)
		     special-slot-names-for-memory-walk
		     :key #'car
		     :test #'equal))))

(defun-void remove-special-slot-for-memory-walk (slot-name)
  (setq special-slot-names-for-memory-walk
	(remove slot-name
		special-slot-names-for-memory-walk
		:key #'car
		:test #'eql)))


;;; `def-ignorable-structure-slot-for-memory-walk' extends the special slot
;;; notion used in walk-frame-for-memory to provide special cases for structure
;;; slots too.  Currently these special cases are being dispatched solely upon
;;; slot name.  Perhaps there will be some fututre cases that need to dispatch
;;; on the structure type and slot name.  JED 5/10/94

(defmacro def-ignorable-structure-slot-for-memory-walk (name)
  `(def-special-slot-for-memory-walk ,name
     (declare (ignore frame slot-value profile-object))
     nil))

(def-ignorable-structure-slot-for-memory-walk lru-element-next-element)

(def-ignorable-structure-slot-for-memory-walk lru-element-previous-element)

(def-ignorable-structure-slot-for-memory-walk image-plane-for-graph-rendering?)

(def-ignorable-structure-slot-for-memory-walk window-for-graph-rendering)



(def-special-slot-for-memory-walk uuid-block-item-reference-table
    (declare (ignore frame))
  ;; Don't walk into the item-reference-table, just get the length of the table.
  ;; Sometimes this slot is a list, other times it's a simple-vector.
  (if (typep slot-value 'list)
      (incff (conses profile-object)
	     (length slot-value))
      (incf-by-lengths (simple-general-arrays profile-object)
		       (length slot-value))))

(def-special-slot-for-memory-walk icon-description 
  (let* ((class-name (class frame))
	 (icon-description-of-class 
	   (get-icon-description-given-class class-name)))
    (if (eq icon-description-of-class slot-value)
	nil ; charge it to the class definition
	(append-to-walk-queue slot-value))))

(defvar size-of-icon-slot-group 7)

;; def-special-slot-for-memory-walk should require a documentation
;; slot, so we can store our reasoning behind charging or not charging
;; memory to a given item.

(def-special-slot-for-memory-walk slot-group-for-block?
  (when slot-value
    (incf-by-lengths (simple-general-arrays profile-object)
		     size-of-icon-slot-group)
    (append-to-walk-queue (subblocks frame))))

;; following special slots are an approximation until we have systematic
;; heuristics for memory consumption of allied frames

(defmacro def-spine-slot-for-memory-walk (name)
  `(def-special-slot-for-memory-walk ,name
     (declare (ignore frame))
     (cond
       ((relation-instance-tree-p slot-value)
	(incff (conses profile-object))
	(append-to-walk-queue (cdr slot-value)))
       (t
	 (incff (conses profile-object)
		(length slot-value))))))
     
(def-spine-slot-for-memory-walk things-this-variable-is-interested-in)

(def-spine-slot-for-memory-walk things-interested-in-this-variable)

(def-spine-slot-for-memory-walk relation-instances)

(def-spine-slot-for-memory-walk list-elements-for-item)

(def-spine-slot-for-memory-walk subblocks)

(def-spine-slot-for-memory-walk connections)

(def-spine-slot-for-memory-walk backward-chain-new-rules)

;; following ignorables are a rough approximation to get the prototype going

(defmacro def-ignorable-slot-for-memory-walk (slot-name)
  `(def-special-slot-for-memory-walk ,slot-name
     (declare (ignore frame slot-value))
     (incff (vector-slots profile-object))
     nil))

(def-ignorable-slot-for-memory-walk class)

(def-ignorable-slot-for-memory-walk lookup-structure)

(def-ignorable-slot-for-memory-walk class-description-slot)

(def-ignorable-slot-for-memory-walk class-specific-instances-forward-pointer)

(def-ignorable-slot-for-memory-walk class-specific-instances-reverse-pointer)

(def-ignorable-slot-for-memory-walk menus-for-this)

(def-ignorable-slot-for-memory-walk parent-frame)

(def-ignorable-slot-for-memory-walk parent-attribute-name)

(def-ignorable-slot-for-memory-walk cell-array)

(def-ignorable-slot-for-memory-walk superblock?)

(def-ignorable-slot-for-memory-walk image-planes-this-is-on)

(def-ignorable-slot-for-memory-walk currently-up-to-date-image-planes)

(def-ignorable-slot-for-memory-walk kb-state-changes-previous-cons?)



;; jh, 9/1/93.  The variable `slots-containing-circular-unnamed-simple-vectors'
;; lists the exceptions to our heuristic that only named simple-vectors need to
;; be checked for circularity.  See the (typep 'simple-vector) clause in
;; walk-for-memory-recursion above for further details.

;; jh, 3/25/94.  The variable slots-containing-circular-unnamed-simple-vectors
;; is no longer used, since we lack a tight regression test that would tell us
;; when some new slot introduced circularities in simple vectors. So we should
;; take the performance hit and remain on the lookout for a more useful
;; heuristic that allows us to predict when a simple vector will contain
;; circularities.

(defvar slots-containing-circular-unnamed-simple-vectors
  '(
    list-structure
    scheduled-remote-procedure-starts
    procedure-invocations
    chart-initial-update-task?
    ))

;; jh, 9/1/94.  The heuristic embodied in the function
;; charge-attribute-to-frame-p is courtesy of Jim Allard, who noticed that
;; instances of free-text share the same text-box-format sub-frame, but are
;; charged individually for it.

(defun-simple charge-attribute-to-frame-p (attribute containing-frame)
  (or (not (framep attribute))
      (or (frame-of-class-p attribute 'dependent-frame)
	  (eq (superior-frame attribute) containing-frame))))

(defun-simple walk-frame-for-memory (frame profile-object)
  (unless frame
    (return-from walk-frame-for-memory))
  (let* ((class-description-of-frame (class-description (class frame)))
	 (slot-descriptions-of-frame
	  (slot-descriptions class-description-of-frame)))
    (incf-by-lengths (frame-vectors profile-object)
		     (class-vector-length class-description-of-frame))
    (loop for slot-description in slot-descriptions-of-frame
	  as slot-to-walk = (unique-slot-name slot-description)
	  as value-of-slot = (get-slot-description-value frame slot-description)
	  as default-value = (slot-init-form slot-description)
	  as vector-slot-p = (vector-slot-index? slot-description)
	  as user-vector-slot-p = (user-vector-slot-index? slot-description)
	  as undefaulted-slot-p 
	     = (or (and (consp default-value)
			(eq (car-of-cons default-value) :funcall))
		   (not (eq value-of-slot default-value)))
	  do
      (development-when memory-walk-verbose-p
	(format t "~&~vtslot: ~s~%" subframe-depth slot-to-walk))
      
      (cond 
	(vector-slot-p
	 (incff (vector-slots profile-object))
	 (unless undefaulted-slot-p 
	   (incff (defaulted-vector-slots profile-object))))
	(user-vector-slot-p
	 (incff (user-vector-slots profile-object))
	 (unless undefaulted-slot-p 
	   (incff (defaulted-user-vector-slots profile-object))))
	(t (incff (lookup-slots profile-object))
	   (unless undefaulted-slot-p 
	     (incff (defaulted-lookup-slots profile-object)))))
      (when undefaulted-slot-p
	(let ((special-slot-entry?
	       (assq slot-to-walk special-slot-names-for-memory-walk)))
	  (development-when memory-walk-verbose-p
	    (when special-slot-entry?
	      (format t "~&~vtspecial entry: ~s~%"
		      subframe-depth
		      (car special-slot-entry?))))
	  (development-let ((subframe-depth (+f subframe-depth 3)))
	    (let ((do-circularity-check-walking-through-conses-p
		      ;; Per Ben, if an item has a slot-value reclaimer,
		      ;; circularity is possible, otherwise not.
		      (or (compound-slot-descriptor slot-to-walk)
			  (eq slot-to-walk '2d-image-plane-states)
			  (slot-value-reclaimer slot-to-walk)))
		  ;; jh, 3/25/94.  Heuristics that limit circularity checks on
		  ;; simple vectors are the wrong way to go without tighter
		  ;; regression testing.  So we always check the contents of
		  ;; simple vectors for circularity.
		  (do-circularity-check-walking-through-simple-vectors-p
		      t
		      ;;(memq slot-to-walk
		      ;;      slots-containing-circular-unnamed-simple-vectors)
		    ))
	      (cond
		(special-slot-entry?
		 (funcall (cdr special-slot-entry?) 
			  frame
			  value-of-slot
			  profile-object))
		((consp value-of-slot)
		 (development-if memory-walk-verbose-p
		   (let ((memory-walk-verbose-p
			   (cond
			     ((suppress-verbosity-for-cons-p value-of-slot)
			      (format t "~&~vtthing: ~s~%"
				      subframe-depth
				      value-of-slot)
			      nil)
			     (t t))))
		     (append-to-walk-queue value-of-slot))
		   (append-to-walk-queue value-of-slot)))
		(t (when (charge-attribute-to-frame-p value-of-slot frame)
		     (append-to-walk-queue value-of-slot)))))))))))

;;; NOTE: in 64-bit G2, following values are not all true. --binghe

(defun-simple size-of-cons ()
  8)

(defun-simple size-of-immediate ()
  4)

(defun-simple size-of-vector-slot ()
  4)

(defun-simple size-of-double-float ()
  16)

(defun-simple size-of-symbol (print-name-length)
  (+f 20 (*f 4 (floorf-positive print-name-length 4))))

(defun-simple size-of-simple-general-array (array-length)
  (+f 16 (*f 4 array-length)))

(defun-simple size-of-simple-unsigned-byte-16-array (array-length)
  (+f 8 (*f 2 (ceilingf-positive array-length 2))))

(defun-simple size-of-simple-unsigned-byte-8-array (array-length)
  (+f 8 (*f 4 (ceilingf-positive array-length 4))))

(defun-simple size-of-double-float-array (array-length)
  (+f 8 (*f 8 array-length)))

(defun-simple size-of-simple-string (string-length)
  (+f 8 (*f 4 (ceilingf-positive string-length 4))))

(defun-simple size-of-adjustable-string (string-length)
  (+f 16 (*f 4 (ceilingf-positive string-length 4))))

(defvar bytes-consumed-by-one-undefaulted-lookup-slot 8)

(defun-for-system-procedure list-of-subclasses-of-item ()
  (let ((list-frame (make-transient-item 'symbol-list)))
    (loop for class-symbol being each subclass of 'item
	  do (g2-list-insert-at-beginning
	       (make-evaluation-symbol class-symbol)
	       list-frame))
    list-frame))

;;; The system procedure `g2-measure-memory' is implemented by the function
;;; `g2-measure-memory-lisp-side'.  It takes a single argument, a frame, and
;;; returns the number of 8-bit bytes of memory consumed by that frame.  Note
;;; that G2 uses more memory than the sum of calling this function on every G2
;;; item accessible by the end-user.

(defun-for-system-procedure g2-measure-memory-lisp-side (frame)
  (declare (keeps-g2-local-variables-valid t))
  (let ((profile (get-memory-profile-of-item-lisp-side frame)))
    (multiple-value-bind (sum
			  double-floats
			  conses
			  vector-slots
			  user-vector-slots
			  lookup-slots
			  frame-vectors
			  arrays)
	(sum-memory-profile-lisp-side profile)
      (delete-frame profile)
      (values (make-evaluation-integer sum)				; 0
	      (make-evaluation-integer double-floats)			; 1
	      (make-evaluation-integer conses)				; 2
	      (make-evaluation-integer vector-slots)			; 3
	      (make-evaluation-integer user-vector-slots)		; 4
	      (make-evaluation-integer lookup-slots)			; 5
	      (make-evaluation-integer frame-vectors)			; 6
	      (make-evaluation-integer arrays)))))			; 7

(defun-for-system-procedure g2-measure-memory-fields-lisp-side ()
  (values (make-evaluation-symbol 'sum)					; 0
	  (make-evaluation-symbol 'double-floats)			; 1
	  (make-evaluation-symbol 'conses)				; 2
	  (make-evaluation-symbol 'vector-slots)			; 3
	  (make-evaluation-symbol 'user-vector-slots)			; 4
	  (make-evaluation-symbol 'lookup-slots)			; 5
	  (make-evaluation-symbol 'frame-vectors)			; 6
	  (make-evaluation-symbol 'other-arrays)))			; 7

;;; The function `get-memory-profile-of-item' is the Lisp implementation of the
;;; system procedure get-memory-profile-of-item.  It creates an item of class
;;; memory-profile, which the caller must reclaim.

(defun get-memory-profile-of-item-lisp-side (frame)
  (clear-items-encountered-in-memory-walk items-encountered-in-memory-walk)
  (let ((profile-object (make-transient-item 'memory-profile)))
    (walk-for-memory-recursion frame profile-object)
    profile-object))

;;; The function `sum-memory-profile-lisp-side' neither allocates nor reclaims
;;; memory outside of the dynamic scope of its execution.

;; Sum-memory-profile-lisp-side should really return a float.  For now,
;; most-positive-fixnum, about 500 meg, is pretty safe.

(defun sum-memory-profile-lisp-side (profile-object)
  (macrolet ((sum-by-length (accessor memory-function)
	       (avoiding-variable-capture 
		   (&aux array-length number-of-arrays)
		 `(loop for (,array-length . ,number-of-arrays) 
			in (,accessor profile-object)
			sum (* ,number-of-arrays
			       (,memory-function ,array-length))))))
    (let ((double-floats
	   (* (double-floats profile-object) (size-of-double-float)))
	  (conses
	   (* (conses profile-object) (size-of-cons)))
	  (vector-slots
	   (* (vector-slots profile-object) (size-of-vector-slot)))
	  (user-vector-slots
	   (* (user-vector-slots profile-object) (size-of-vector-slot)))
	  (lookup-slots
	   (* (- (lookup-slots profile-object)
		 (defaulted-lookup-slots profile-object))
	      bytes-consumed-by-one-undefaulted-lookup-slot))
	  (frame-vectors
	   (sum-by-length frame-vectors size-of-simple-general-array))
	  (simple-general-arrays
	   (sum-by-length simple-general-arrays size-of-simple-general-array))
	  (simple-unsigned-byte-16-arrays
	   (sum-by-length simple-unsigned-byte-16-arrays
			  size-of-simple-unsigned-byte-16-array))
	  (simple-unsigned-byte-8-arrays
	   (sum-by-length simple-unsigned-byte-8-arrays
			  size-of-simple-unsigned-byte-8-array))
	  (double-float-arrays
	   (sum-by-length double-float-arrays size-of-double-float-array))
	  (adjustable-strings
	   (sum-by-length adjustable-strings size-of-adjustable-string))
	  (simple-strings
	   (sum-by-length simple-strings size-of-simple-string)))
      (values
       (+ double-floats
	  conses
	  vector-slots
	  user-vector-slots
	  lookup-slots
	  frame-vectors
	  simple-general-arrays
	  simple-unsigned-byte-16-arrays
	  simple-unsigned-byte-8-arrays
	  double-float-arrays
	  adjustable-strings
	  simple-strings)
       double-floats
       conses
       vector-slots
       user-vector-slots
       lookup-slots
       frame-vectors
       ;; procedure call has 8 return values' limit.
       (+ simple-general-arrays
	  simple-unsigned-byte-16-arrays
	  simple-unsigned-byte-8-arrays
	  double-float-arrays
	  adjustable-strings
	  simple-strings)))))

(defvar tab-length-for-counter-report 25)

(defun report-significant-single-counter-slot (slot counter-value)
  (unless (zerop counter-value)
    (format t "~&~s:~vt~s~%"
	    slot
	    tab-length-for-counter-report
	    counter-value)))

(defun report-significant-count-by-lengths-slot (slot counter-value?)
  (when counter-value?
    (format t "~&~s:" slot))
  (loop for (count . length) in counter-value?
	for offset = 0 then 2
	do
    (format t "~vt(~s . ~s)~%"
	    (+ tab-length-for-counter-report
	       offset)
	    count
	    length)))

(defun report-significant-counters (counter)
  (macrolet ((report-significant-single-counter-slots (&rest counter-slots)
	       `(progn
		 ,@(loop for slot in counter-slots
			 collect
			 `(report-significant-single-counter-slot
			   ',slot
			   (,slot counter)))))
	     (report-significant-count-by-lengths-slots (&rest counter-slots)
	       `(progn
		 ,@(loop for slot in counter-slots
			 collect
			 `(report-significant-count-by-lengths-slot
			   ',slot
			   ;; Note the slot is side-effected by sort
			   (sort (,slot counter) #'< :key #'car))))))
    (report-significant-single-counter-slots
      vector-slots
      user-vector-slots
      lookup-slots
      defaulted-vector-slots
      defaulted-user-vector-slots
      defaulted-lookup-slots
      conses
      symbols
      double-floats
      fixnums
      characters
      immediates
      )
    (report-significant-count-by-lengths-slots
      simple-general-arrays
      simple-unsigned-byte-16-arrays
      simple-unsigned-byte-8-arrays
      double-float-arrays
      adjustable-strings
      simple-strings
      frame-vectors
      )))




(defun report-diff-in-single-counter-slot (slot count-1 count-2)
  (unless (=f count-1 count-2)
    (format t "~&~s~vt~s/~s~%"
	    slot
	    tab-length-for-counter-report
	    count-1
	    count-2)))

(defun report-diff-in-counter-by-lengths-slot
       (slot list-by-lengths-1 list-by-lengths-2)
  (let ((number-of-lengths-1 (length list-by-lengths-1))
	(number-of-lengths-2 (length list-by-lengths-2)))
    (when (or (/= number-of-lengths-1 number-of-lengths-2)
	      (loop for (length-1 . count-1) in list-by-lengths-1
		    for (length-2 . count-2) in list-by-lengths-2
		    thereis
		    (or (/= length-1 length-2) (/= count-1 count-2))))
      (format t "~&~s:" slot)
      (when (< number-of-lengths-1 number-of-lengths-2)
	(rotatef list-by-lengths-1 list-by-lengths-2))
      (loop for (length-1 . count-1) in list-by-lengths-1
	    with (length-2? . count-2?) = (pop list-by-lengths-2)
	    with offset = 0
	    do
	    (loop while length-2?
		  while (< length-2? length-1)
		  do
		  (format t "~vt(~s . 0/~s)~%"
			  (+ tab-length-for-counter-report
			     offset)
			  length-2?
			  count-2?)
		  (when (zerop offset)
		    (setq offset 2))
		  (destructuring-setq (length-2? . count-2?)
				      (pop list-by-lengths-2)))
	    (cond
	      ((and length-2? (= length-1 length-2?))
	       (format t "~vt(~s . ~s/~s)~%"
		       (+ tab-length-for-counter-report
			  offset)
		       length-1
		       count-1
		       count-2?)
	       (destructuring-setq (length-2? . count-2?)
				   (pop list-by-lengths-2)))
	      (t (format t "~vt(~s . ~s/0)~%"
			 (+ tab-length-for-counter-report
			    offset)
			 length-1
			 count-1)))
	    (when (zerop offset)
	      (setq offset 2))))))

(defun counter-diff (counter-1 counter-2)
  (macrolet ((report-diff-in-single-counter-slots (&rest counter-slots)
	       `(progn
		  ,@(loop for slot in counter-slots
			  collect
			  `(report-diff-in-single-counter-slot
			     ',slot
			     (,slot counter-1)
			     (,slot counter-2)))))
	     (report-diff-in-counter-by-lengths-slots (&rest counter-slots)
	       `(progn
		  ,@(loop for slot in counter-slots
			  collect
			  ;; Note the slot is side-effected by sort
			  `(report-diff-in-counter-by-lengths-slot
			     ',slot
			     (sort (,slot counter-1) #'< :key #'car)
			     (sort (,slot counter-2) #'< :key #'car))))))
    (report-diff-in-single-counter-slots
      vector-slots
      user-vector-slots
      lookup-slots
      defaulted-vector-slots
      defaulted-user-vector-slots
      defaulted-lookup-slots
      conses
      symbols
      double-floats
      fixnums
      characters
      immediates
      )
    (report-diff-in-counter-by-lengths-slots
      simple-general-arrays
      simple-unsigned-byte-16-arrays
      simple-unsigned-byte-8-arrays
      double-float-arrays
      adjustable-strings
      simple-strings
      frame-vectors
      )))


;;;; User Access to G2 Memory Stats

;; jh per bhyde, 10/29/93.  We need system procedures to parcel out the
;; information inherent in "write G2 stats".

;; To do:

;; jh, 10/29/93.  figure out how to compute the size of a structure.  As far as
;; I can tell from looking at def-structure in UTILITIES2, this information is
;; excluded from distribution images.




;;; The system procedure `g2-memory-category-count' returns the integer that is
;;; the number of memory categories.  Memory categories are for internal use
;;; only and are subject to change at any time.

(def-system-variable memory-category-count MEM-SYSPROC
  (:funcall initialize-memory-category-count))

(defun initialize-memory-category-count ()
  (length object-pool-meters))

(defun-for-system-procedure memory-category-count-lisp-side ()
  (make-evaluation-integer memory-category-count))




;; The system procedure `g2-snapshot-memory-levels' records the instantaneous
;; stats of all G2 memory categories.  It always returns the value true.

(def-system-variable last-memory-stats-snapshot MEM-SYSPROC
  (:funcall initialize-last-memory-stats-snapshot))

(defun initialize-last-memory-stats-snapshot ()
  (loop for index from 1 to memory-category-count
	collect (list 0 0)))

(defun-void snapshot-memory-levels ()
  (loop for pool-entry in object-pool-meters
	for cons-holding-levels on last-memory-stats-snapshot
	do
    (setf (first (car cons-holding-levels))
	  (pool-entry-memory-usage-in-bytes pool-entry))
    (setf (second (car cons-holding-levels))
	  (pool-entry-object-count pool-entry))))

(defun-for-system-procedure snapshot-memory-levels-lisp-side ()
  (snapshot-memory-levels)
  (copy-evaluation-truth-value evaluation-true-value))




;;; The system procedure `g2-memory-category-info' returns seven values:

;;; (1) The name of the memory category as a symbol.
;;; (2) The name of the superior memory category as a symbol.
;;; (3) The amount of memory consumed by one element of this memory category as
;;;     an integer, if this amount can be determined.  If this amount cannot be
;;;     determined (for example, if the element has a variable length, such as a
;;;     string), 0 is returned.  The amount is measured in bytes.
;;; (4) The number of memory elements that are currently allocated in this
;;;     category, as an integer.
;;; (5) The current amount of memory allocated in this category as a float.
;;;     This amount is measured in bytes.
;;; (6) The difference between the amount of memory currently allocated and the
;;;     amount allocated as of the last memory snapshot, as a float.  Memory
;;;     snapshots are taken whenever the system procedure
;;;     g2-snapshot-memory-levels is called and whenever "write G2 stats" is
;;;     selected from a file edit box.
;;; (7) The difference between the number of memory elements that are currently
;;;     allocated in this category and the number allocated as of the last
;;;     memory snapshot, as an integer.



;; jh, 10/29/93.  Def-system-object-pool sometimes uses a list for its
;; "enclosing memory category" (since these categories represent Lisp types) so
;; we map it to a symbol with the function
;; map-enclosing-memory-category-to-symbol.  This function is currently full of
;; special cases, though it could be improved to be of general use.

(defun map-enclosing-memory-category-to-symbol (enclosing-memory-category)
  (macrolet ((intern-formatted (control-string &rest args)
	       `(intern-text-string
		  (tformat-text-string ,control-string ,@args))))
    (cond
      ((symbolp enclosing-memory-category)
       enclosing-memory-category)
      ((equal enclosing-memory-category '(vector (unsigned-byte 8)))
       'unsigned-8-bit-vector)
      ((and (consp enclosing-memory-category)
	    (eq (first enclosing-memory-category) 'simple-array))
       (gensym-dstruct-bind
	   ((nil element-type (length?)) enclosing-memory-category)
	 (let ((specific-length?
		 (if (or (null length?) (eq length? '*))
		     nil
		     length?))
	       (specific-element-type?
		 (cond
		   ((eq element-type t) nil)
		   ((symbolp element-type) element-type)
		   ((equal (first element-type) 'unsigned-byte)
		    (intern-formatted "UNSIGNED-BYTE-~a"
				      (second element-type)))
		   (t nil))))
	   (cond
	     ((and specific-element-type? specific-length?)
	      (intern-formatted "SIMPLE-~a-LONG-~a-ARRAY"
				specific-length?
				specific-element-type?))
	     (specific-element-type?
	      (intern-formatted "SIMPLE-~a-ARRAY" specific-element-type?))
	     (specific-length?
	      (intern-formatted "SIMPLE-~a-LONG-ARAY" specific-length?))
	     (t 'simple-array)))))
      (t (intern-formatted "~a" enclosing-memory-category)))))

(defun get-memory-element-byte-size-if-possible (enclosing-memory-category)
  (cond
    ((eq enclosing-memory-category 'cons)
     (size-of-cons))
    ((and (consp enclosing-memory-category)
	  (eq (first enclosing-memory-category) 'simple-array))
     (gensym-dstruct-bind
	 ((nil element-type (length?)) enclosing-memory-category)
       (let ((specific-length?
	       (if (or (null length?) (eq length? '*))
		   nil
		   length?)))
	 (cond
	   ((and specific-length?
		 (consp element-type)
		 (eq (first element-type) 'unsigned-byte))
	    (case (second element-type)
	      (8 (size-of-simple-unsigned-byte-8-array specific-length?))
	      (16 (size-of-simple-unsigned-byte-16-array specific-length?))
	      (otherwise nil)))
	   ((and specific-length?
		 (memq element-type '(double-float gensym-float)))
	    (size-of-double-float-array specific-length?))
	   (t nil)))))
    (t nil)))

(defun-for-system-procedure memory-category-info-lisp-side
                            (g2-category-number)
  (let ((category-number (evaluation-integer-value g2-category-number)))
    (reclaim-evaluation-integer g2-category-number)
    (with-temporary-gensym-float-creation g2-memory-category-info
      (if (and (pluspf category-number)
	       (<=f category-number memory-category-count))
	  (let* ((category-index (1-f category-number))
		 (pool-entry (nth category-index object-pool-meters))
		 (g2-category-name
		   (make-evaluation-symbol (pool-entry-name pool-entry)))
		 (enclosing-category (pool-entry-data-type pool-entry))
		 (g2-enclosing-category-name
		   (map-enclosing-memory-category-to-symbol
		     enclosing-category))
		 (current-level (pool-entry-memory-usage-in-bytes pool-entry))
		 (g2-current-level
		   (make-evaluation-float
		     (coerce-fixnum-to-gensym-float current-level)))
		 (element-byte-size?
		   (get-memory-element-byte-size-if-possible
		     enclosing-category))
		 (g2-element-byte-size
		   (if element-byte-size?
		       (make-evaluation-integer element-byte-size?)
		       (make-evaluation-integer 0)))
		 (element-count
		   (pool-entry-object-count pool-entry))
		 (g2-element-count
		   (make-evaluation-integer element-count))
		 (g2-byte-difference-from-last-stats
		   (make-evaluation-float
		     (coerce-fixnum-to-gensym-float
		       (-f current-level
			   (first
			     (nth category-index
				  last-memory-stats-snapshot))))))
		 (g2-element-difference-from-last-stats
		   (-f element-count
		       (second
			 (nth category-index
			      last-memory-stats-snapshot)))))
	    (values g2-category-name
		    g2-enclosing-category-name
		    g2-element-byte-size
		    g2-element-count
		    g2-current-level
		    g2-byte-difference-from-last-stats
		    g2-element-difference-from-last-stats))
	  (values 'none
		  'none
		  (make-evaluation-integer 0)
		  (make-evaluation-integer 0)
		  (make-evaluation-float 0.0)
		  (make-evaluation-float 0.0)
		  (make-evaluation-integer 0))))))

(defun-for-system-procedure g2-reclaim-symbol (symbol package)
  (unintern symbol package))

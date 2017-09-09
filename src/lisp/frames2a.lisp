;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module FRAMES2A

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; M. Levin (et. al.)

(declare-forward-references
  #+development
  (describe-slot-group-for-block function frames3)
  (releasing-kb? variable kb-save2)
  (reclaim-icp-object-map-for-class-description function g2-rpc2)
  (put-uuid function frames5)
  (put-new-uuid function frames5)
  (show-uuids-in-attribute-tables-function function g2-rpc3)
  (reclaim-name-or-names-for-frame-value function frames5)
  (cleanup-for-stubs-for-class function definitions)
  (frame-being-read? variable kb-load2)
  (tracking-items-p variable sets)
  (note-tracked-item-creation function sets)
  (tracked-items-call-vector-table variable sets)
  (note-possibly-tracked-item-deletion function sets)
  (profiling-structure variable sets)
  (note-possibly-profiled-item-deletion function sets)
  (reading-kb-p variable kb-load2)
  (delete-connection-after-reading-kb function kb-load2)
  (delete-block-after-reading-kb function kb-load2)
  (called-within-clear-text-loading variable kb-save4)
  (set-item-was-created-by-load-function function frames3)
  (in-clear-kb-p variable kb-save2)
  (direct-superiors-preclude-instantiability-p function definitions)
  (send-notification-to-item-internal function conclude)
  )

#-development
(declare-forward-references
  (change-slot-description-value-function function frames5)
  (analyze-compiled-items-for-consistency function install)
  (name-of-defined-class-function function function definitions)
  (do-block-specific-deletion-stuff function frames5)
  (remove-variable-from-simulation function simulate5))

(declare-forward-reference procedure-invocation-currently-being-aborted? variable)
(declare-forward-reference abort-procedure-invocation function)



;;;; The Not So Dreaded System-Item

;; System-item defines common elements shared between G2 and TW items
;; in version 5.


(def-class (system-item root define-predicate)
  (uuid nil (type uuid) vector-slot system save do-not-clone)
  (frame-serial-number
    (:funcall frame-serial-number-recycled-function)
    vector-slot system (attribute-export-comment "Internal"))

  (frame-flags 0 system vector-slot (type nil) do-not-save note-slot-changes
	       (attribute-export-comment "Currently frame-flags is aliased ~
to options. I think individual attribute-mimics should be created for ~
particular flags, and I don't know if options should continue to be supported. This
comment should show up on options, despite it being placed on frame-flags." ))
  (frame-flags-2 0 system vector-slot)

  ;; New slots to replace instances-specific-to-this-class list, they make a
  ;; doubly linked list of all instances of the same class.
  (class-specific-instances-forward-pointer ; next
    nil vector-slot system (attribute-export-comment "Internal"))
  (class-specific-instances-reverse-pointer ; prev
    nil vector-slot system (attribute-export-comment "Internal"))
  
  (parent-frame nil system (attribute-export-comment "Backpointer to frame which holds this item. ~
 Depending on the type of frame this may be of value to export.")) ; nil or a frame with this frame as an attribute value
  (parent-attribute-name nil system (attribute-export-comment "The name of the attribute in the ~
 parent-frame which holds this item."))	; the attribute in question
  
  ;; NOTE WELL: The format of the above slot, parent-attribute-name, has been
  ;; changed (without a corresponding name change).
  ;;
  ;; It previously held the slot name (a symbol) for the slot in the parent
  ;; frame.  (Thus, it was a misnomer already in that it held a slot name,
  ;; rather than a possibly aliased attribute name.)
  ;;
  ;; It now holds its very own data structure, which is either a slot name (a
  ;; symbol), or, if needed, a cons of the slot name and the defining class:
  ;;
  ;;    slot-name
  ;; or
  ;;    (slot-name . defining-class)
  ;;
  ;; The advent of multiple inheritance has necessitated keeping track of the
  ;; defining class, where needed (i.e., where other than the first class in
  ;; the parent frame's inheritance path that defines slot with this name).
  ;;
  ;; This gives us a highly space- and time-efficient means of access to this
  ;; information.  It also is compatible with the the 3.0 KB Save format for
  ;; this information.  It also is the most easy to implement quickly, in time
  ;; for the release.
  ;;
  ;; Ultimately, we feel that this would be best handled as a _slot group_ that
  ;; occupies the same slot in the backbone of blocks as slot-group-for-block?.
  ;; (They would be then, as they are in practice, mutually exclusive values for
  ;; that slot.)  There just isn't time to do this, however.  Perhaps for 4.1.
  ;;
  ;; (MHD, w/JRA, 2/19/94)

  ;; jh, 4/24/94.  The object-passing-info slot enables any block to participate
  ;; in object and array passing.  -- rh, 7/16/96.  Moved to system-item.
  (object-passing-info? nil system lookup-slot do-not-save)

  (attributes-permamently-changed nil system lookup-slot do-not-save)

  (item-is-explicitly-editable nil system lookup-slot do-not-save)

  #+mtg2
  (faction? nil system (attribute-export-comment "The faction this item belongs to.")) ; a faction or nil if the item belongs to the main faction
  )

;;; Sets both `superblock?' and, in case of MTG2, `faction?' slots
(defmacro set-superblock-and-faction (subblock superblock)
  (let ((sub (gensym)) (sup (gensym)))
    `(let ((,sub ,subblock) (,sup ,superblock))
       (setf (superblock? ,sub) ,sup)
       #+mtg2
       (unless (or (null ,sup) (eq 'faction (class ,sub)))
	 (add-faction-member ,sub (faction? ,sup))
	 (propagate-faction-recursively ,sub)))))

(defmacro class-specific-instances-next-element (instance)
  `(class-specific-instances-forward-pointer ,instance))

(defmacro class-specific-instances-previous-element (instance)
  `(class-specific-instances-reverse-pointer ,instance))

(defun uuid-function (item)
  (uuid item))

;;; frame serial-number is reclaimed later, explicitly, in delete-frame.
;;; So don't reclaim it here; other reclaimers may be counting on it.
(def-slot-value-reclaimer frame-serial-number (frame-serial-number frame)
  (declare (ignore frame-serial-number frame)))

;;; Frame Serial numbers have been moved to utilities0.lisp

;;; Only their use in frames is here.


;;; `Frame-hash-Function' is used as a hash function for
;;; binary trees and hash tables of frames. It must return an int, and will be replaced by
;;; something more complex when we have two-word frame serial numbers.

(defmacro frame-hash (block)
  `(frame-serial-number-hash (frame-serial-number ,block)))

(defun-simple frame-hash-function (block)
  (frame-hash block))

(defun-simple frame-serial-number-function (block)
  (frame-serial-number block))


;;; `Frame-in-use-p' returns t if its argument is a frame which is not on a
;;; recycled frame list (that is, a frame which has been made by make frame some
;;; time after its most recent release or a frame which has never been
;;; released).

(defmacro frame-in-use-p (block)
  `(not (frame-serial-number-equal (frame-serial-number ,block) (frame-serial-number-recycled))))




;;; `Frame-has-been-reprocessed-p' given a frame and a serial-number which
;;; was equal to some value assumed by (current-frame-serial-number) during the
;;; time period the frame was considered relevant, returns t if the frame has
;;; since been reprocessed and nil otherwise.

(defmacro frame-has-been-reprocessed-p (block reference-serial-number)
  (let ((frame (gensym))
	(frame-serial-number (gensym))
	(check-type? (eval-feature :development)))
    `(let* (,@(if check-type?
		  `((,frame ,block)))
	      (,frame-serial-number
		 (frame-serial-number ,(if check-type? frame block))))
       ,@(when check-type?
	   `((check-for-non-system-item-has-been-reprocessed-p ,frame)))
       (or (deleted-frame-p ,(if check-type? frame block))
	   (frame-serial-number-equal ,frame-serial-number (frame-serial-number-recycled))
	   (frame-serial-number-> ,frame-serial-number ,reference-serial-number)))))

#+development
(defun-void check-for-non-system-item-has-been-reprocessed-p (frame)
  (unless (or (deleted-frame-p frame)
	      (frame-of-class-p frame 'system-item))
    (warn "Frame-has-been-reprocessed-p was called on a non-system-item frame: ~s"
	   frame)))

(defun-simple frame-has-been-reprocessed-p-function (block reference-serial-number)
  (frame-has-been-reprocessed-p block reference-serial-number))




;;; `Frame-has-not-been-reprocessed-p' given a frame and a serial-number which
;;; was equal to some value assumed by (current-frame-serial-number) during the
;;; time period the frame was considered relevant, returns t if the frame has
;;; not since been reprocessed and nil otherwise.

(defmacro frame-has-not-been-reprocessed-p (block reference-serial-number)
  `(not (frame-has-been-reprocessed-p ,block ,reference-serial-number)))







;; `Frame-less-p', returns t if the frame-serial-number of its first argument
;; is less than the frame-serial-number of its second argument. It is an error
;; to apply frame-less-p to arguments other than frames.

;(defmacro frame-less-p (first-frame second-frame)
;  `(<f (frame-serial-number ,first-frame) (frame-serial-number ,second-frame)))


;; Stubs, to be modified when new frame-serial number implementation is done.



;;;; Class Instance Iteration Paths



;;; `Instances-specific-to-this-class' is the property which points to the set of
;;; all instances of the class (instantiated by `make-frame').
;;; Instances-specific-to-this-class is implemented using the
;;; class-specific-instances-forward-pointer and
;;; class-specific-instances-reverse-pointer slots of a block.  This forms a set
;;; which is non-circular (the forward-pointer of the last block in the set points
;;; to nil and the reverse-pointer of the first block points to nil).  A tail
;;; pointer is maintained to allow for easily adding to the end of the set.

;; Implementation as a circular set was also considered but rejected because the
;; iteration end test becomes more complicated, and iteration over this set should
;; be fast.  A circular set with a header block was also considered but rejected
;; due to the overhead from the header block.

(eval-when (:compile-toplevel :load-toplevel :execute)
(def-kb-specific-property-name instances-specific-to-this-class)

;;; `Instances-specific-to-this-class-tail-pointer' points to the last element in
;;; the set in instances-specific-to-this-class or to nil if there are none.

(def-kb-specific-property-name instances-specific-to-this-class-tail-pointer)

#+SymScale
(defvar class-specific-instances-lock (tx:make-lock)) ; a temporal solution
)


(def-substitution-macro delete-from-instances-if-necessary (class frame)
  (when (or (class-specific-instances-forward-pointer frame)
	    (class-specific-instances-reverse-pointer frame))
    (delete-from-instances-specific-to-this-class class frame)))


;;; `add-to-instances-specific-to-this-class' is currently not called anywhere.
;;; -- Chun Tian (binghe), 2014/12/25.

#-SymScale
(def-substitution-macro add-to-instances-specific-to-this-class (class frame)
  (delete-from-instances-if-necessary class frame)
  (let ((first-instance? (instances-specific-to-this-class class)))
    (if first-instance?
	(setf (class-specific-instances-reverse-pointer first-instance?) frame
	      (class-specific-instances-forward-pointer frame) first-instance?
	      (class-specific-instances-reverse-pointer frame) nil
	      (instances-specific-to-this-class class) frame)
	(setf (instances-specific-to-this-class class) frame
	      (instances-specific-to-this-class-tail-pointer class) frame
	      (class-specific-instances-forward-pointer frame) nil
	      (class-specific-instances-reverse-pointer frame) nil))))

#+SymScale
(defun-simple add-to-instances-specific-to-this-class (class frame)
  (tx:with-lock-held (class-specific-instances-lock)
    (delete-from-instances-if-necessary class frame)
    (let ((first-instance? (instances-specific-to-this-class class)))
      (if first-instance?
	  ;; head insert (pushLeft)
	  (setf (class-specific-instances-reverse-pointer first-instance?) frame
		(class-specific-instances-forward-pointer frame) first-instance?
		(class-specific-instances-reverse-pointer frame) nil
		(instances-specific-to-this-class class) frame)
	(setf (instances-specific-to-this-class class) frame
	      (instances-specific-to-this-class-tail-pointer class) frame
	      (class-specific-instances-forward-pointer frame) nil
	      (class-specific-instances-reverse-pointer frame) nil)))))


;;; `add-to-end-of-instances-specific-to-this-class' is called by `allocate-frame'
;;; and `reclassify-frame'.

#-SymScale
(def-substitution-macro add-to-end-of-instances-specific-to-this-class (class frame)
  (delete-from-instances-if-necessary class frame)
  (let ((last-instance? (instances-specific-to-this-class-tail-pointer class)))
    (if last-instance?
	(setf (class-specific-instances-forward-pointer last-instance?) frame
	      (class-specific-instances-reverse-pointer frame) last-instance?
	      (class-specific-instances-forward-pointer frame) nil
	      (instances-specific-to-this-class-tail-pointer class) frame)
	(setf (instances-specific-to-this-class class) frame
	      (instances-specific-to-this-class-tail-pointer class) frame
	      (class-specific-instances-forward-pointer frame) nil
	      (class-specific-instances-reverse-pointer frame) nil))))

#+SymScale
(defun-simple add-to-end-of-instances-specific-to-this-class (class frame)
  (tx:with-lock-held (class-specific-instances-lock)
    (delete-from-instances-if-necessary class frame)
    (let ((last-instance? (instances-specific-to-this-class-tail-pointer class)))
      (if last-instance?
	  ;; tail insert (pushRight)
	  (setf (class-specific-instances-forward-pointer last-instance?) frame
		(class-specific-instances-reverse-pointer frame) last-instance?
		(class-specific-instances-forward-pointer frame) nil
		(instances-specific-to-this-class-tail-pointer class) frame)
	(setf (instances-specific-to-this-class class) frame
	      (instances-specific-to-this-class-tail-pointer class) frame
	      (class-specific-instances-forward-pointer frame) nil
	      (class-specific-instances-reverse-pointer frame) nil)))))


;;; `delete-from-instances-specific-to-this-class' is called by `delete-frame'
;;; and `reclassify-frame'.

#-SymScale
(def-substitution-macro delete-from-instances-specific-to-this-class (class frame)
  (cond
    ((null (class-specific-instances-reverse-pointer frame))  ; first (and possibly last)
     (let ((next? (class-specific-instances-forward-pointer frame)))
       (if next?
	   (setf (class-specific-instances-forward-pointer frame) nil  ; removed
		 (instances-specific-to-this-class class) next?
		 (class-specific-instances-reverse-pointer next?) nil)
	   (setf (instances-specific-to-this-class class) nil
		 (instances-specific-to-this-class-tail-pointer class) nil))))
    ((null (class-specific-instances-forward-pointer frame))  ; last, but not first
     (let ((previous? (class-specific-instances-reverse-pointer frame)))
       (setf (class-specific-instances-reverse-pointer frame) nil  ; removed
	     (instances-specific-to-this-class-tail-pointer class) previous?
	     (class-specific-instances-forward-pointer previous?) nil)))
    (t 
     (let ((next? (class-specific-instances-forward-pointer frame))
	   (previous? (class-specific-instances-reverse-pointer frame)))
       (setf (class-specific-instances-forward-pointer frame) nil
	     (class-specific-instances-reverse-pointer frame) nil
	     (class-specific-instances-forward-pointer previous?) next?
	     (class-specific-instances-reverse-pointer next?) previous?)))))

#+SymScale
(defun-simple delete-from-instances-specific-to-this-class (class frame)
  (tx:with-lock-held (class-specific-instances-lock)
    (cond
      ((null (class-specific-instances-reverse-pointer frame))  ; first (and possibly last)
       (let ((next? (class-specific-instances-forward-pointer frame)))
	 (if next?
	     (setf (class-specific-instances-forward-pointer frame) nil  ; removed
		   (instances-specific-to-this-class class) next?
		   (class-specific-instances-reverse-pointer next?) nil)
	   (setf (instances-specific-to-this-class class) nil
		 (instances-specific-to-this-class-tail-pointer class) nil))))
      ((null (class-specific-instances-forward-pointer frame))  ; last, but not first
       (let ((previous? (class-specific-instances-reverse-pointer frame)))
	 (setf (class-specific-instances-reverse-pointer frame) nil  ; removed
	       (instances-specific-to-this-class-tail-pointer class) previous?
	       (class-specific-instances-forward-pointer previous?) nil)))
      (t
       (let ((next? (class-specific-instances-forward-pointer frame))
	     (previous? (class-specific-instances-reverse-pointer frame)))
	 (setf (class-specific-instances-forward-pointer frame) nil
	       (class-specific-instances-reverse-pointer frame) nil
	       (class-specific-instances-forward-pointer previous?) next?
	       (class-specific-instances-reverse-pointer next?) previous?))))))


#+development       
(defun print-instances-specific-to-class (class)
  (loop as instance = (instances-specific-to-this-class class)
		    then (class-specific-instances-forward-pointer instance)
	until (null instance)
	do (format t "~%~S" instance)))





;;;; Vector Pool for Frame Instances

;;; Some Frame storage management stuff was brought over to FRAMES2
;;; from FRAMES3 to help in the "objects in TW" project.


;;; The following code defines a pool of vectors for use as frame instances.
;;; This pool is implemented as a global vector stored in `frame-vector-pool-
;;; vector', `largest-frame-vector-size' long, each element of which contains a
;;; chain of the available frame vectors of that size.

(defparameter largest-frame-vector-size 100)

;;; GENSYM-47086 (SymScale), thread-specific frame allocation pool support:
;;; In following code, 1D vector become 2D array, the 2rd dimension is the
;;; thread indexes.  -- Chun Tian (binghe)

(defun create-frame-vector-pool-vector (initial-element)
  (make-array largest-frame-vector-size :initial-element initial-element))

#+SymScale
(defun create-frame-vector-pool-array (initial-element)
  (let ((vector (make-thread-array nil)))
    (loop for i from 0 below g2-max-threads
          do (setf (svref vector i)
                   (create-frame-vector-pool-vector initial-element)))
    vector))

#+SymScale
(declare-special-global frame-vector-pool-array
                        frame-vector-pool-counts-vector)

#-SymScale
(def-system-variable frame-vector-pool-vector frames2a
  (:funcall create-frame-vector-pool-vector nil) nil nil)

#+SymScale
(def-system-variable frame-vector-pool-array frames2a
  (:funcall create-frame-vector-pool-array nil) nil nil)

(def-system-variable frame-vector-pool-counts-vector frames2a
  (:funcall create-frame-vector-pool-vector 0) nil nil)

(def-system-variable frame-vector-count frames2a 0 nil nil)

(def-system-variable outstanding-frame-vector-count frames2a 0 nil nil)

(def-system-variable frame-vector-memory-used frames2a 0 nil nil)

(defun frame-vector-memory-usage ()
  frame-vector-memory-used)

(def-system-object-pool frame-vector-pool simple-vector
  frame-vector-count outstanding-frame-vector-count nil
  frame-vector-memory-usage)

(defparameter frame-vectors-to-make-at-a-time 5)

#+SymScale
(declaim (special frame-vector-pool-vector))

;;; Vectors are allocated by calling the macro `allocate-frame-vector' with the
;;; size of the desired frame.  It will be allocated from a pool of available
;;; vectors of that size, or else a new one will be made.

(defmacro allocate-frame-vector (size-form)
  (let ((size (gensym))
	(available-vectors (gensym))
	(vector-index (gensym))
	(vector (gensym)))
    `(let* ((,size ,size-form)
	    (,vector-index (-f ,size 1))
            #+SymScale
            (frame-vector-pool-vector
             (svref frame-vector-pool-array current-thread-index)))
       (if (>f ,size largest-frame-vector-size)
	   (error "Tried to allocate a frame larger than largest-frame-vector-size,~%~
                   which is ~a.  Increase largest-frame-vector-size!"
		  largest-frame-vector-size))
       (atomic-incff outstanding-frame-vector-count)
       (let* ((,available-vectors
		 (svref frame-vector-pool-vector ,vector-index))
	      (,vector
		 (if ,available-vectors
		     (progn
		       (setf (svref frame-vector-pool-vector ,vector-index)
			     (lookup-structure ,available-vectors))
		       ,available-vectors)
		     (create-frame-vector-and-replenish-pool ,size))))
	 (note-allocate-cons ,vector nil)
	 ,vector))))



;;; New frame vectors are made by calling the function `create-frame-vector-and-
;;; replenish-pool'.  It will make `frame-vectors-to-make-at-a-time', returning
;;; one and putting the others into the pool for later allocation.

;;; Note that this facility uses the lookup-structure slot (element 1) of frame
;;; vectors to chain together reclaimed vectors.  It does not use the class slot
;;; (element 0) for historical reasions: that was required for printing vectors
;;; defined with named-structure-symbols (as they were on the Lispms).  We
;;; cannot use the frame-serial-number slot (element 2), since they are referred
;;; to when checking if a frame on an alist has been reclaimed.

(defun create-frame-vector-and-replenish-pool (size)
  (atomic-incff
    frame-vector-memory-used
    (*f frame-vectors-to-make-at-a-time
        (bytes-per-simple-vector size)))
  (atomic-incff
    frame-vector-count frame-vectors-to-make-at-a-time)
  (let ((size-list (frame-cons-macro size nil))
	(vector-index (-f size 1)))
    (atomic-incff
      (svref frame-vector-pool-counts-vector vector-index)
      frame-vectors-to-make-at-a-time)
    (with-permanent-array-creation
      (loop with last-created-vector = nil
	    with vector-holder
	    repeat (-f frame-vectors-to-make-at-a-time 1)
	    do
	(setq vector-holder (make-array size-list))
	(setf (lookup-structure vector-holder) last-created-vector)
	(setq last-created-vector vector-holder)
	    finally
	      (setf (svref frame-vector-pool-vector vector-index)
		    last-created-vector))
      (prog1
	  (make-array size-list :initial-element nil)
	(reclaim-frame-cons-macro size-list)))))


;;; The variables `do-not-initialize-specializations' and
;;; `do-not-initialize-specializations-for-clone' control whether make-frame
;;; will initialize subitems for which the user has specialized the method
;;; g2-initialize or g2-initialize-for-clone, respectively.

(defvar do-not-initialize-specializations nil)

(defvar uuid-for-next-frame? nil)
(defvar class-description-for-next-frame? nil)

(defun-simple allocate-frame
    (class-description frame-serial-number? uuid?
		       eval-slot-init-forms-p
		       class-known-to-be-system-item-p)
  (when (and (null uuid?)
	     uuid-for-next-frame?
	     (eq class-description-for-next-frame? class-description))
    (setq uuid? uuid-for-next-frame?)
    (setq uuid-for-next-frame? nil)
    (setq class-description-for-next-frame? nil))
  (let* ((class (class-name-of-class-description class-description))
	 (system-item-p
	   (or class-known-to-be-system-item-p
	       (class-description-of-class-p class-description 'system-item)))
	 (frame
	   (if system-item-p
	       (allocate-frame-vector
		 (class-vector-length class-description))
	       (allocate-managed-simple-vector
 		 (class-vector-length class-description))))
	 (lookup-structure		; nil when unneeded (irrelevant)
	   (if (>f (class-user-vector-length class-description) 0)
	       (allocate-frame-lookup-structure-vector
		 (class-user-vector-length class-description)
		 nil))))
    (loop for slot-description in (slot-descriptions class-description)
	  as vector-slot-index? = (vector-slot-index? slot-description)
	  do
      (cond
	(vector-slot-index?
	 (setf (svref frame vector-slot-index?)
	       (slot-init-form slot-description)))
	((user-vector-slot-index? slot-description)
	 (setf (svref lookup-structure
		      (user-vector-slot-index? slot-description))
	       (slot-init-form slot-description)))))
    
    ;; Set the value of the class, class-description-slot, and lookup-structure
    ;; slots here: (This must come after the above loop, which sets them to
    ;; something irrelevant.)
    (setf (class-description-slot frame) class-description)
    (setf (lookup-structure frame) lookup-structure)

    (if eval-slot-init-forms-p
	(initialize-slots-of-frame-needing-evaluation frame))

    ;; Set the slots and flags that are just for system-items, and then link
    ;; the instance into the chain of all instances, which is only maintained
    ;; for system-items:
    (when system-item-p
      ;; Frame-serial-number is set to frame-serial-number?, if that's
      ;; non-nil.  Otherwise, it's set to the value of
      ;; (current-frame-serial-number), after it is incremented here.
      (setf (frame-serial-number frame)
	    (copy-frame-serial-number
	      (or frame-serial-number?
		  (increment-current-frame-serial-number))))
      #+use-a-structure-for-frame-serial-numbers
      (setf (compound-frame-serial-number-owned-by-frame-p (frame-serial-number frame)) frame)
      (when uuid?
	(put-uuid frame uuid? t))
      ;; If uuid? was supplied, but another frame was already
      ;; using that uuid, the previous call to put-uuid won't do anything.
      (unless (and uuid? (uuid frame))
	(put-new-uuid frame))
      ;; Add the frame to the tail end of the instances-specific-to-this-class
      ;; property of the class of the frame and update its tail pointer
      ;; accordingly.
      (add-to-end-of-instances-specific-to-this-class class frame)
      
      (when tracking-items-p
	(note-tracked-item-creation frame))

      (when (or reading-kb-p called-within-clear-text-loading in-clear-kb-p)
	(set-item-was-created-by-load-function frame)))

    frame))








;;;; Initializations on Frames Being Made



;;; Within make-frame, or, more precisely, during the evaluation of slot init
;;; forms and during evaluation of the initialize method, if any, special
;;; variable `frame-being-made' is bound to the frame being made.  This allows
;;; slot-init-forms to refer to the frame being made and and to the values of
;;; previously initialized slots.  It is important to refer only to slots which
;;; have been initialized.  Failure to do this will result in garbage values in
;;; the case of vector slots and is undefined in the case of lookup-slot slots.

;; [However, there has never been a way to know if an initialization took place
;; yet.  Depending on order has never been defined to be reliable.  In fact the
;; order has never been defined. (Note that the only user of the binding of
;; frame-being-made is the G2 simulator. Review uses of frame-being-made in
;; DEFINITIONS, and the way the slots are set when a slot change occurs!.)
;; Review intent of this doc. with ML. (MHD 7/6/94)]
       
;;; Make-frame finishes the initialization process by calling initialize-frame,
;;; which calls the initialize method.  This is called after frame is made with
;;; all slot initializations already performed.  (Read-frame-for-kb and
;;; clone-frame call read-frame-without-initializations to avoid slot
;;; initializations; clone-frame then calls initialize-frame itself;
;;; read-frame-for-kb does its own thing, calling the frame's
;;; initialize-after-reading method.)

(def-system-variable frame-being-made frames2a nil)





;;; `Initialize-slots-of-frame-needing-evaluation' is called as part of creating
;;; a frame with initialializations, i.e., via make-frame, and also as the third
;;; major step in recreating a frame being read in from a KB.  It initializes
;;; slots that need evaluation, but that did have values stored in the KB for
;;; whatever reason, a case that should occur only rarely.

(defun-void initialize-slots-of-frame-needing-evaluation (frame)
  (let* ((noting-changes-to-kb-p nil)
	 (current-block-of-dependent-frame 'dependent-frame-has-no-owner)
	 (frame-being-made frame)
	 (class-of-frame (class frame)))
    (loop for slot-description
	      in (slot-descriptions (class-description-slot frame))
	  as slot-init-form = (slot-init-form slot-description)
	  do
      (when (and (consp slot-init-form)
		 (eq (car-of-cons slot-init-form) ':funcall)
		 (eq slot-init-form
		     (get-slot-description-value-macro
		       frame slot-description)))
	(initialize-slot-description-value
	  frame slot-description
	  (if (class-in-attribute-conforms-to-type-p
		slot-description class-of-frame t)
	      (eval-slot-init-form slot-init-form)
	      nil))))))





;;; Frames are returned by calling the macro `reclaim-frame-vector' with the
;;; vector to be reclaimed as the argument.

;;; Notes: see this (frames1.lisp), slot 1 is also used for class-description
;;;
;;; (defmacro lookup-structure (frame)
;;;   `(svref ,frame 0))
;;; (defmacro class-description-slot (frame)
;;;   `(svref ,frame 1))

(defmacro mark-frame-as-available (frame)
  `(setf (svref ,frame 1) 'available-frame-vector))

(defmacro reclaim-frame-vector (frame-form)
  (let ((frame (gensym))
	(vector-index (gensym)))
    `(let* ((,frame ,frame-form)
	    (,vector-index (-f (length-of-simple-vector ,frame) 1))
            #+SymScale
            (frame-vector-pool-vector
             (svref frame-vector-pool-array current-thread-index)))
       (declare (type simple-vector ,frame)
		(type fixnum ,vector-index))
       (atomic-decff outstanding-frame-vector-count)
       (note-reclaim-cons ,frame nil)
       (mark-frame-as-available ,frame)
       (setf (lookup-structure ,frame)
	     (svref frame-vector-pool-vector ,vector-index))
       (setf (svref frame-vector-pool-vector ,vector-index) ,frame))))




;;;; Iterators



;;; `Strict class instances iteration path':

;;; The following defines an iteration path for LOOP which allows
;;; iteration over all instances specific to a given class.
;;; The following are examples of this extension of LOOP.

;;;    (loop for each-person being each strict-class-instance of 'person
;;;          collecting (name each-person))
;;;     -> (<name of person 1> <name of person 2> ... <name of person N>)
;;;     Where there exist N instances of person.

;;;     (loop for instance being the strict-class-instance of 'vehicle
;;;           thereis (availablep instance))
;;;     -> t if any vehicles are available nil otherwise.

;;; and so on...

;;; The strict class instances iteration path is the preferred method of traversing
;;; instances specific to a class. It is efficient in respect to both space and
;;; time. Note that the class instances iteration path traverses only instances
;;; of its target class which are specific (directly subsumed by) the class.

(defun-for-macro strict-class-instances-path
    (path-name variable data-type prep-phrases inclusive? allowed-prepositions data)
  (let ((bindings nil)
	(prologue nil)
	(instances-variable (loop-gentemp)))
    ;; These variables are not used.
    path-name data-type data allowed-prepositions
    ;; Warn of missing prepositional phrase.
    (if (null prep-phrases)
	(error "OF is missing in ~S iteration path of ~S" path-name variable))
    ;; Inclusive iteration is not supported.
    (if inclusive?
	(error "Inclusive stepping is not supported in ~S path of ~S (prep-prase = ~:S)"
	       path-name variable prep-phrases))
    (setq bindings
	  (list (list instances-variable
		      `(instances-specific-to-this-class
			 ,(cadar prep-phrases)))
		(list variable
		      nil)))
    ;; Return the appropriate items.
    `(,bindings
	,prologue
	(null ,instances-variable)
	nil
	nil
	(,variable
	   ,instances-variable
	   ,instances-variable
	   (class-specific-instances-forward-pointer ,instances-variable)))))



(define-loop-path (strict-class-instances strict-class-instance)
		  strict-class-instances-path (of))

;; OK here, but do not use this path within this file while we are running TI 3.0.
;; This is a new TI bug. (MHD 8/5/87)




;;; `Class instances iteration path':

;;; The following defines an iteration path for LOOP which allows
;;; iteration over all instances of a class. The following are examples
;;; of this extension of LOOP.

;;;    (loop for each-person being each class-instance of 'person
;;;          collecting (name each-person))
;;;     -> (<name of person 1> <name of person 2> ... <name of person N>)
;;;     Where there exist N instances of person.

;;;     (loop for instance being class-instances of 'vehicle
;;;           thereis (availablep instance))
;;;     -> t if any vehicles are available nil otherwise.

;;; and so on...

;;; The class instances iteration path is the perfered method of traversing
;;; the instances of a class. It is efficient in respect to both space and
;;; time. Note that the class instances iteration path traverses all instances
;;; of its target class along with all instances of its subclasses.

;;; The class instances iteration path is an in order traversal. Beginning with the
;;; class to which it is applied, each instance specific to that class is traversed
;;; in the order in which they were defined, then each subclass of the class is
;;; traversed in the order in which they were defined in the same manner in which
;;; the original class was traversed.

;;; This loop path traverses on the list of classes returned by the subclasses
;;; loop path which removes any duplicate classes that can appear using the
;;; inferior-classes global properties under multiple inheritance.

(defun-for-macro class-instances-path
    (path-name variable data-type prep-phrases inclusive?
	       allowed-prepositions data)
  (let ((bindings nil)
	(prologue nil)
        (traversal-state-variable (loop-gentemp))
        (current-instances-variable (loop-gentemp)))
    
    ;; These variables are not used.
    path-name data-type data allowed-prepositions
    
    ;; Warn of missing prepositional phrase.
    (unless prep-phrases
      (error "OF is missing in ~S iteration path of ~S" path-name variable))
    
    ;; Inclusive iteration is not supported.
    (when inclusive?
      (error "Inclusive stepping is not supported in ~S path of ~S (prep-prase = ~:S)"
	     path-name variable prep-phrases))
    
    ;; Prepare bindings list for LOOP.
    (setq bindings
          `((scope-conses scope-conses)
            (,traversal-state-variable nil)
            (,current-instances-variable nil)
            (,variable nil)))

    (setq prologue
	`((setq ,traversal-state-variable
		(collect-subclasses ,(cadar prep-phrases)))))
    
    ;; Return the appropriate form. (See LOOP documentation)
    (list
      bindings
      prologue
      ;; Iteration terminates if there are no more current instances stored
      ;; in the current instances variable and there remain no such instances
      ;; after further searching the tree for such.
      `(when (null ,current-instances-variable)
         ;; Search for more instances.
	 (loop while ,traversal-state-variable do
	   (setq ,current-instances-variable
		 (instances-specific-to-this-class
		   (car-of-cons ,traversal-state-variable)))
	   (setq ,traversal-state-variable (cdr-of-cons ,traversal-state-variable))
	       until ,current-instances-variable)
         (null ,current-instances-variable))
      nil
      nil
      `(,variable 
          ,current-instances-variable
          ,current-instances-variable 
          (class-specific-instances-forward-pointer 
            ,current-instances-variable)))))



;; Moved the loop iteration path definition from here to UTILITIES2, so that GSI
;; could see it.  GSI cannot actually iterate over class instances, of course.
;; That functionality is not present in GSI.  But it should at least know how to
;; macroexpand a loop which refers to this iteration.  Then we can stub out the
;; functionality, and/or give a #+development error if it ever gets called.
;; Giving an error that we don't know how to handle the loop is far too
;; unfriendly, and prevents GSI from compiling in Lisp.  -jv, 12/19/03

;; (define-loop-path (class-instances class-instance) class-instances-path (of))



;;;; Some Funcky Predicates


;;; These predicates are needed for new Telewindows and do not depend
;;; aspects of the class hierarchy particular to G2.

;;; The function `well-instantiated-or-subclassed-class-p' returns t when a
;;; class has more than five instances or has more than three inferior classes
;;; with class as their sole direct-superior class.

(eval-when (:load-toplevel #-chestnut-trans :compile-toplevel :execute)
(defun-simple well-instantiated-or-subclassed-class-p (class)
  (or (>f (loop for instance being each strict-class-instance of class
		count instance)
	  5)
      (>f (loop for inferior-class in (inferior-classes class)
		when (null (cdr (direct-superior-classes inferior-class)))
		  count class)
	  3)))
)



;;; Do-not-put-slot-in-attribute-tables-p ...  Note that this ignores the
;;; DO-NOT-PUT-IN-ATTRIBUTE-TABLES-IF-NULL feature, since that depends on
;;; information about the instance.

;; OBSOLETE: removed the first two args, & fixed all callers to use 3rd.
;; (MHD 2/15/94)
;; ;; Either both class?  and slot-name?  must be non-nil or
;; ;; slot-description-if-known?  must be non-nil.

;; The slot-description here can be a listed capability-slot-description
;; as well as a class-description slot-description, therefore the consp
;; check.  (2/25/93)

;; I'm only guessing since there is no documentation here, but I believe that
;; the formerly-visible? controls whether or not this predicate returns true for
;; those attributes which have been renamed, but for which we have continuing
;; support for change-the-text-of.  -jra 4/17/96
 
(defun do-not-put-slot-in-attribute-tables-p
    (slot-description formerly-visible? &optional frame-for-attribute-table?)
  (if (and (not (user-defined-slot-description-p slot-description))
	   (eq (pretty-slot-name slot-description) 'uuid))
      (not (or (null frame-for-attribute-table?)
	       (of-class-p frame-for-attribute-table? 'unique-identification)
	       (show-uuids-in-attribute-tables-function)))
      (let* ((slot-features (slot-features slot-description))
	     (previously-put-in?
	       (feature-assq-macro
		 'previously-put-in-attribute-tables slot-features))
	     (do-not-put-in-attribute-tables-feature?
		 (or previously-put-in?
		     (feature-assq-macro
		       'do-not-put-in-attribute-tables slot-features))))
	(and (and do-not-put-in-attribute-tables-feature?
		  (or (null (cdr do-not-put-in-attribute-tables-feature?))
		      (case (second do-not-put-in-attribute-tables-feature?)
			(not-ent (not (g2-enterprise-p)))
			(nupec (nupec-authorized-p))
			(not-nupec (not (nupec-authorized-p))))))
	     ;; if we don't normally want to allow it, this gives us a way of
	     ;; allowing it
	     (not (and formerly-visible? previously-put-in?))))))





;;;; Printing Utilities for developement


;;; Describe-frame prints a table of slot names and corresponding slot values
;;; for each slot in the frame.  If uninteresting-slots-too? is supplied non-nil,
;;; then slots known to be for internal use by the frame system and typically
;;; "uninteresting" or transparent to the user are not included in the table.

#+development
(defun describe-frame (frame &optional (uninteresting-slots-too? nil)
		       &aux (*print-pretty* t) (class (class frame)))
  (format t "~2&~a is a Gensym frame of class ~a." frame class)
  (loop for slot-description in (slot-descriptions (class-description class))
	for pretty-slot-name = (pretty-slot-name slot-description)
	for vector-slot-index? = (vector-slot-index? slot-description)
	for user-vector-slot-index? = (user-vector-slot-index? slot-description)
	for slot-value = (get-slot-description-value frame slot-description)
	do
    (when (or uninteresting-slots-too?
	      (not (memq pretty-slot-name
			 '(class lookup-structure frame-serial-number
				 frame-representations frame-serial-number
				 class-description-slot))))
      (describe-slot-in-frame-or-structure
	vector-slot-index? user-vector-slot-index? pretty-slot-name slot-value)
      (when (and (eq 'slot-group-for-block? pretty-slot-name)
		 slot-value)
	(describe-slot-group-for-block frame))))
  (format t "~&")
  frame)


#+development
(defun careful-frame-p (thing)
  (and thing
       (simple-vector-p thing)
       (> (length-of-simple-vector thing) 2)
       (framep thing)))


#+development
(def-development-printer print-gensym-frame (frame stream)
  (when (careful-frame-p frame)
    (let* ((class (case (class frame)
		    (connection 'connection-frame)	    ; In order to distinguish them from structures.
		    (t (class frame))))
	   (name? (and (frame-of-class-p frame 'block)
		       (get-slot-value frame 'name-or-names-for-frame)))
	   (other-name?
	     (cond ((or (frame-of-class-p frame 'table)
			(frame-of-class-p frame 'text-box))
		    (get-format-name frame))
		   ((frame-of-class-p frame 'user-menu-choice)
		    (get-slot-value frame 'user-menu-choice-symbol?)))))
      
      (printing-random-object (frame stream)
	(format stream "~a~@[ ~s~]~@[~( ~a~)~]"
		class
		other-name?
		name?))
      frame)))

#+development
(def-development-describer describe-gensym-frame (frame)
  (when (careful-frame-p frame)
    (describe-frame frame)
    frame))



  
#+development
(defun gensym-structure-or-frame-p (x)
  ;; Framep can die if given a simple-vector whose class-description-slot contains
  ;; a simple vector of length 0.
  (#+Lucid lcl:ignore-errors #-Lucid progn
    (or (careful-frame-p x)
	(allocated-named-gensym-structure-p x))))

;; Recycled frames aren't handled well.

#+development
(defun get-format-name (table-or-text-box)
  (let* ((format (if (frame-of-class-p table-or-text-box 'table)
		     (get-slot-value table-or-text-box 'table-format)
		     (get-slot-value table-or-text-box 'text-box-format)))
	 (format-name (if format (get-slot-value
				   format 'name-or-names-for-frame))))
    (or format-name
	:unknown-format)))




;;;; ITEMS




(def-class (item system-item (foundation-class item) do-not-put-in-menus
		 not-solely-instantiable
		 not-user-instantiable))

;;; don't really want developers to be able to instatiate these either
;;; but since one can't have not-solely-instantiable when there is no
;;; foundation-class, I'm hoping that this definition is safe without
;;; either of those features... (rpenny 3/15/98)
(def-class (ui-client-item item do-not-put-in-menus
			   not-user-instantiable))

(def-class (exported-system-item (item) (foundation-class item)
				 do-not-put-in-menus
				 not-solely-instantiable
				 not-user-instantiable))

(def-class (unique-identification item (foundation-class item) define-predicate
				  not-solely-instantiable
				  do-not-put-in-menus not-user-instantiable))



;;;; Frame Flags


;;; Frame-flags and frame-flags-2 are slots of blocks with an integer value that 
;;; is interpreted as a vector of miscellaneous binary flags.  All such flags 
;;; should be defined here.  In all Common Lisp implementations which we will use, 
;;; at least 24 flags may be defined in each slot without the integer ever 
;;; becoming a bignum.  Note that all flags of a new frame are initially off.

;;; Def-savable-frame-flag defines a set of kb savabled flag-specific operations 
;;; for a flag named flag-name that uses the 2**(bit-index) bit of the frame-flags 
;;; value. Def-non-savable-frame-flag does the same thing for non-kb-savable frame
;;; flags. These operations are:
;;;
;;;    (flag-name-P frame) is true if the flag is on, else nil
;;;
;;;    flag-name-P setf method -- returns the value supplied, and sets the flag
;;;    either true or false.  E.g., so you can say (setf (flag-name-P x) nil)
;;;    NOTE: this makes use of the SET- and CLEAR- macros unnecessary.  It is
;;;    newer, however, so the old forms are supported for compatibility,
;;;    indefinitedly.  They should not be used for new code, however.
;;;
;;;    (flag-name-OF-FLAG-VECTOR-P fixnum) is true if the flag is on, else nil.
;;;    Its argument is a possible value of frame-flags or frame-flags-2 rather
;;;    than a frame. It is the responsibility of the user to have the argument
;;;    be a meaningful value of frame-flags or frame-flags-2 as appropriate
;;;    for the particular flag.
;;;
;;;    (SET-flag-name frame) turns the flag on regardless of its previous value;
;;;
;;;    (CLEAR-flag-name frame) turns the flag off regardless of its previous
;;;    value; and
;;;
;;;    flag-name-FLAG returns an integer with the bit for this flag flipped on,
;;;    which is used in slot value initializations for frame-flags.
;;;
;;; A non-standard name for the CLEAR operation can be optionally specified as a
;;; fourth symbol. Note that the SET and CLEAR operations have no useful values.

;;; All flags defined with def-savable-frame-flag are placed in frame-flags which is a
;;; saved slot. All flags defined with def-non-savable-frame-flag are placed
;;; in frame-flags-2 which is a non-savable slot. Otherwise, the two macros are
;;; identical. 

;;; Note that if a vector of bits is accessed and/or set from one of these
;;; slots, it is the responsibility of the user to have the correct vector
;;; for the flags being manipulated. Thus there is a lack of complete abstraction.
;;; For example, the flags that are processed for variables and rules are all
;;; savable ones, and hence are in frame-flags.





;(defvar mask-for-saved-frame-flags 0)



;; Had the value 7531546 on 3/12/91. Save this info.

;; Remove the block tests when stable!!!




;;; The macro `def-savable-frame-flag' is used to define frame flags that are
;;; savable.  The bits for these flags are all allocated from the vector slot
;;; frame-flags.

(defmacro def-savable-frame-flag
    (flag-name bit-index frame-type &optional clear-operation-name)
  `(define-flag-bit ,flag-name (frame-flags ,frame-type) ,bit-index
		    :clear ,clear-operation-name))


;;; Def-non-savable-frame-flag is used to define frame flags that are not savable.
;;; The bits for these flags are all allocated from the vector slot frame-flags-2.

;;; The macro `def-non-savable-frame-flag' is used to define frame flags that
;;; are not savable.  The bits for these flags are all allocated from the
;;; vector slot frame-flags-2.

(defmacro def-non-savable-frame-flag
    (flag-name bit-index frame-type &optional clear-operation-name)
  `(define-flag-bit ,flag-name (frame-flags-2 ,frame-type) ,bit-index
		    :clear ,clear-operation-name))




;;; The macro `def-obsolete-frame-flag' defines frame-flags which do not exist
;;; except while loading KBs older than the kb-flag version in which the
;;; def-obsolete-frame-flag first appeared. It is functionally equivalent to
;;; def-savable-frame-flag. The differences are documentary.

;;; When a savable frame flag becomes obsolete, the issue of old KBs that may
;;; have it must be addressed. This is done in the slot-putter for frame-flags.

(defmacro def-obsolete-frame-flag (flag-name bit-index frame-type
					     &optional clear-operation)
  `(def-savable-frame-flag ,flag-name ,bit-index ,frame-type
     ,clear-operation))


;;; It is the programmers responsibility to keep track of bit assignments.
;;; All def-savable-frame-flags are done at this point in the source code.

;;; All savable frame-flags follow in bit assignment order:





;;;; Shared Frame Flags

(def-non-savable-frame-flag active 0 block set-inactive)

;;; `Frame-being-deleted' is set when a frame is being deleted.  It is primarily
;;; intended to prevent cycling during deletion.

(def-non-savable-frame-flag frame-being-deleted 9 block)


;;; All blocks written to a kb are permanent.

(def-savable-frame-flag permanent-block 0 block)


;;;; Parent Information



;;; `Parent information' is the information in a block which specifies that is is
;;; an attribute of some other block.  This information is established, updated,
;;; and removed by the slot putter and reclaimer for attributes which follow.

;;; A block has two parent information slots:
;;;
;;;     `parent-frame', which is either nil or the frame of which this block is an
;;;        attribute value, and
;;;
;;;     `parent-attribute-name', either nil or a a slot name (a symbol), or, if
;;;     needed, a cons of the slot name and the defining class. Thus,
;;;
;;;        nil
;;;
;;;     or
;;;
;;;        slot-name
;;;     or
;;;     
;;;       (slot-name . defining-class)
;;;
;;;     This "names" the attribute (i.e., slot) holding the block.
;;;
;;; Note that the contents of parent-attribute-name in each instance of frame's
;;; class need review upon any change to the mapping of the slot name, and
;;; defining class, if any, within the class description of frame's class.
;;; I.e., either a change in the name of the slot, or a shadowing, or
;;; unshadowing, of the name of the slot by the addition, or removal, of a slot
;;; with the same name within the class inheritance path of frame's class.
;;;
;;; Note that the two slots are always either both nil or both non-nil.
;;; 
;;; [The format was changed, upwardly compatibly, for 4.0.  Prior to 4.0, slots
;;; had to be uniquely named, so this only held a slot name.  In 4.0, slots
;;; started to need qualification in some cases, so the format was extended to
;;; allow for the qualifier.  See notes around the definition of the slots under
;;; block for further information. (MHD/JRA 2/19/94)



;;; `Get-kb-parent-information', given a block whose membership in
;;; the kb hierarchy is through some attribute of some other object, returns
;;; (as many as) three values
;;;
;;;    parent-frame?
;;;
;;;    parent-slot-name?
;;;
;;;    class-qualifier?
;;;
;;; In otherwords, a path back to the parent object and the attribute on which
;;; the block sits.  In the case of a block within a kb hierarchy but by virtue
;;; of its subblock relationship to a knowledge block, two values are returned.
;;; They are the parent knowledge block and nil. Finally, if neither, the values
;;; nil and nil are returned.
;;;
;;; None of the values are returned if there is no parent frame.  If there is
;;; one, both the first and second of the two values are always returned.  The
;;; third value is only returned if the class qualifier is needed to uniquely
;;; identify the slot with the returned slot name in the returned frame.

;;; Note that this functionality applied only to entities until it was changed
;;; to apply to blocks on 9/1/88.
;;;
;;; Note that the third return value was added for multiple inheritance, for 4.0,
;;; on 2/19/94.

(defun get-kb-parent-information (block)
  (if (parent-frame block)
      (let ((parent-attribute-name (parent-attribute-name block)))
	(if (consp parent-attribute-name)
	    (values
	      (parent-frame block)
	      (car-of-cons parent-attribute-name)
	      (cdr-of-cons parent-attribute-name))
	    (values
	      (parent-frame block)
	      parent-attribute-name)))))

;; Changed from a macro to a function.  This is not intended to be used in any
;; case for (such) speed-critical purposes.  (MHD 2/19/94)

(defmacro set-parent-information
    (subblock parent-frame parent-pretty-slot-name parent-slot-defining-class?)
  (avoiding-variable-capture
      (subblock parent-frame parent-pretty-slot-name parent-slot-defining-class?)
    (let ((name-for-old-parent-attribute-name (gensym)))
      `(let ((,name-for-old-parent-attribute-name (parent-attribute-name ,subblock)))
	 (setf (parent-frame ,subblock) ,parent-frame)
	 #+mtg2
	 (unless (or (null ,parent-frame) (eq 'faction (class ,subblock)))
	   (setf (faction? ,subblock) (faction? ,parent-frame)))
	 (setq ,name-for-old-parent-attribute-name (parent-attribute-name ,subblock))
	 (setf (parent-attribute-name ,subblock)
	       (if ,parent-slot-defining-class?
		   (slot-value-cons-macro
		     ,parent-pretty-slot-name
		     ,parent-slot-defining-class?)
		   ,parent-pretty-slot-name))
	 (reclaim-slot-value ,name-for-old-parent-attribute-name)))))
			  
(def-slot-value-reclaimer parent-frame (parent-frame? frame)	; unlikely to be used
  (when (and parent-frame? (not (frame-being-deleted-p parent-frame?)))
    (let* ((parent-attribute-name (parent-attribute-name frame))
	   (pretty-slot-name
	     (if (consp parent-attribute-name)
		 (car-of-cons parent-attribute-name)
		 parent-attribute-name))
	   (defining-class
	       (when (consp parent-attribute-name)
		 (cdr-of-cons parent-attribute-name)))
	   (parent-frame-slot-description?
	     (get-slot-description-of-frame
	       pretty-slot-name parent-frame? defining-class)))
      #+development
      (unless parent-frame-slot-description?
	(unless releasing-kb?
	  (cerror "frames4" "no parent-frame slot description")))
      (when parent-frame-slot-description?
	(with-ignored-forward-references (change-slot-description-value-function)
	  (change-slot-description-value-function
	    parent-frame? parent-frame-slot-description? nil nil nil))))))
	  


(defun-simple get-parent-attribute-name-as-symbol (system-item)
  (let ((parent-attribute-name
	  (parent-attribute-name system-item)))
    (if (symbolp parent-attribute-name)
	parent-attribute-name
	(make-unique-slot-name-symbol
	  (cdr-of-cons parent-attribute-name)
	  (car-of-cons parent-attribute-name)))))





;;;; Useful Frame and Class Functions



;;; Instantiated-class-p is true if there are any instances of the class
;;; (including instances of subclasses). A frame being deleted is not considered
;;; an instances of its class. This situation arises only when
;;; instantiated-class-p is called from within the recursive extent of
;;; delete-frame. This happens when the deletion of an instances causes the
;;; deletion of the class definition of a class superior to the immediate class
;;; of the instance. 

(defun instantiated-class-p (class)
  (loop for subclass being each subclass of class
	thereis (loop for instance being each strict-class-instance of subclass
		      thereis (not (frame-being-deleted-p instance)))))

;; Above changed by ML, 5/13/91 to include only instances not being deleted.

;;; The function `essentially-instantiated-class-p' is a variant
;;; of instantiated-class-p useful in some circumstances because of multiple
;;; inheritance. A class is "essentially-instantiated" if changing it to
;;; be non-instantiable would cause problems. A class can be instantiated
;;; but not essentially instantiated, if, for example, all the instances
;;; are instances of subclasses which in addition to inheriting from
;;; this class, also inherit from other superclasses that are instantiable.

(defun essentially-instantiated-class-p (class)
  (or
    (loop for instance being the strict-class-instances of class
	  thereis instance)
    (loop for subclass in (inferior-classes class)
	  thereis (invalidated-by-instantiation-without-superclass
		    subclass class))))

;;; the function `invalidated-by-instantiation-without-superclass'
;;; returns true if the given class could have its inheritance
;;; changed to exclude the given superclass without causing the problem
;;; of there being extant instances of a noninstantiable class as
;;; a result.
(defun invalidated-by-instantiation-without-superclass (class superclass)
  (let ((other-superclasses
	  (loop for other-superclass in (direct-superior-classes class)
		unless (eq other-superclass superclass)
		  collect other-superclass using gensym-cons)))
    (prog1
	(and
	  (or (null other-superclasses)
	      (direct-superiors-preclude-instantiability-p other-superclasses))
	  (essentially-instantiated-class-p class))
      (reclaim-gensym-list other-superclasses))))

;;; `Has-slot-p' returns the slot-description of the given slot if it is a slot
;;; of the given class or frame, otherwise it returns nil.

#+development
(defun has-slot-p
    (class-or-frame unique-or-pretty-slot-name &optional class-if-specific?)
  (if (symbolp class-or-frame)
      (let ((class-description? (class-description class-or-frame)))
	(if class-description?
	    (get-slot-description-of-class-description 
	      unique-or-pretty-slot-name class-description? class-if-specific?)))
      (get-slot-description-of-class-description 
	unique-or-pretty-slot-name (class-description-slot class-or-frame) class-if-specific?)))

;; Consider returning the type of slot if it is a slot!  Consider a function
;; classes-for-which-a-slot which returns a list of all classes for which the
;; slot is applicable!






;;;; Deleting Frames



;;; `Cleanup' is a class method that maybe defined for any kb-frame.  It is ...

(def-generic-method cleanup (kb-frame))




;;; The following five forms make it possible to undefine the user-defined
;;; classes whose definition frames have been deleted on the recursive descent
;;; of delete-frame.


;;; `Queue-of-classes-to-be-undefined', right before exiting the outmost call
;;; to delete-frame, contains a list of the user-defined-class names whose
;;; definition frames have been deleted by delete-frame.  It is reset to nil
;;; immediately before exiting the outermost call.

(def-kb-specific-variable queue-of-classes-to-be-undefined frames2a nil)




;;; 'Within-delete-frame-scope?' is set to t on entering delete-frame on
;;; the outermost call, and is set to nil upon exiting delete-frame from
;;; the outermost call.

(def-system-variable within-delete-frame-scope? frames2a nil)




;;; The function `reclaim-list-of-slot-descriptions' takes a list with members
;;; of the form (<class that has slot description> . <slot-description>) and
;;; reclaims the slot descriptions.  It is up to the caller to determine
;;; that the slot descriptions are unique, and to reclaim the list.

(defun reclaim-list-of-slot-descriptions (slot-descriptions-to-reclaim)
  (loop with reclaimed-slot-init-forms = nil
	with slot-init-form = nil
	for (class . slot-description) in slot-descriptions-to-reclaim
	do
    #+development
    (unless (slot-description-p slot-description)
      (cerror
	"frames5" "slot description reclamation error1"))
    #+development
    (when (and debugging-slot-description-leaks?
	       (not (memq slot-description unreclaimed-slot-descriptions)))
      (cerror "frames5" "slot description reclamation error2"))
    #+development
    (when debugging-slot-description-leaks?
      (delete-slot-description-from-unreclaimed-list slot-description))
    (setq slot-init-form (slot-init-form slot-description))
    ;; GENSYMCID-1845: G2 crashes with the help of player
    (unless (memq slot-init-form reclaimed-slot-init-forms)
      (frame-push slot-init-form reclaimed-slot-init-forms)
      (cond ((icon-description-slot-init-form-p slot-init-form)
	     (when (eq (icon-owner-class-function slot-init-form) class)
	       (setq structure-being-reclaimed slot-init-form)
	       (reclaim-icon-description-of-slot-description slot-init-form)))
	    ((and (consp slot-init-form)
		  (default-slot-constant-p slot-init-form))
	     (let ((slot-value (car slot-init-form)))
	       (reclaim-slot-value-cons
		 (prog1 slot-init-form
		   (setq slot-init-form (cdr slot-init-form))))
	       (reclaim-slot-value slot-value)
	       (reclaim-slot-value slot-init-form)))
	    (t (reclaim-slot-value slot-init-form))))
    (setf (slot-init-form slot-description) nil)
    (setq structure-being-reclaimed slot-description)
    (reclaim-slot-description slot-description)
    (setq structure-being-reclaimed nil)
	finally
	  (when reclaimed-slot-init-forms
	    (reclaim-frame-list reclaimed-slot-init-forms))))




;;; `Reclaim-slot-descriptions-of-class-description', when clearing the kb,
;;; calls reclaim-slot-description on every slot description in the
;;; class-description that is not EQ to any slot description on a
;;; system-defined class; otherwise it reclaims every slot-description on the
;;; class-description that is not EQ to any other slot description in the
;;; system.

(defun-simple reclaim-slot-descriptions-of-class-description (class-description)
  (let ((slot-descriptions (slot-descriptions class-description))
	(class (class-name-of-class-description class-description)))
    (decache-cached-class-data class)
    (loop until (null slot-descriptions)
	  for slot-description = (class-description-pop slot-descriptions)
	  for unique-slot-name = (unique-slot-name slot-description)
	  for owner-class = (owner-class slot-description)
	  do
      (when (eq owner-class class)
	(loop for subclass being each subclass of class
	      for subclass-class-description? = (class-description subclass)
	      for subclass-slot-description? =
	            (unless (eq subclass class)
		      (when subclass-class-description?
			(get-slot-description
			  unique-slot-name
			  (slot-descriptions subclass-class-description?))))
	      do
	  (when (eq subclass-slot-description? slot-description)
	    (delete-class-description-element-from-slot-descriptions
	      subclass-slot-description? subclass-class-description?)
	    (delete-slot-description-from-hash-table
	      subclass-slot-description? subclass-class-description?)))
	(let ((reclaim-argument
		(frame-list (frame-cons class slot-description))))
	  (reclaim-list-of-slot-descriptions reclaim-argument)
	  (reclaim-frame-tree reclaim-argument)))))
  (setf (slot-descriptions class-description) nil))

      


;;; `Reclaim-class-description-of-class' reclaims the class-description
;;; structure, the class-specific slot-description structures, and all
;;; reclaiminable slot values of these structures when a class is being
;;; undefined.  It also reclaims the global properties of class,
;;; direct-superior-classes and inferior-classes.

(defun reclaim-class-description-of-class
       (class class-description old-class-description?)

  (when (and (class-description-p class-description)
             (class-description-is-user-defined-p class-description))

    (reclaim-icp-object-map-for-class-description class-description)
    
    (reclaim-slot-descriptions-of-class-description class-description)
    
    #+development
    (when debugging-class-description-leaks?
      (unless (memq class-description unreclaimed-class-descriptions)
	(cerror "frames1" "reclaim-class-description-of-class"))
      (delete-class-description-from-unreclaimed-list class-description))

    (let ((class-method-table?
            (method-table-of-class-description class-description)))
      (when (and class-method-table?
		 (eq (owner-class-of-method-table class-method-table?)
		     class))
	#+development
	(when debugging-class-description-method-table-leaks?
	  (unless (memq class-method-table?
			unreclaimed-class-description-method-tables)
	    (cerror "frames1" "reclaim class-method table"))
	  (delete-class-description-method-table-from-unreclaimed-list
	    class-method-table?))
	(reclaim-method-table-of-class-description class-method-table?)
	(setf (method-table-of-class-description class-description) nil)))

    ;; See change-superior-of-class for the use of old-class-description.
    (when (not old-class-description?)
      (setq class-bit-numbers-pool
            (frame-cons (class-bit-number class-description) 
                        class-bit-numbers-pool))
      (setf (class-bit-number class-description) nil))

    
    (reclaim-class-description class-description)
    (setf (class-description class) nil)))




;;; `Reset-within-delete-frame-scope' resets within-delete-frame-scope? and
;;; queue-of-classes-to-be-undefined to nil immediately before exiting the
;;; outermost call to delete-frame.

(defun reset-within-delete-frame-scope ()
  (setq within-delete-frame-scope? nil)
  (setq queue-of-classes-to-be-undefined nil))



;;; This form takes care of keeping track of the recursive calls of delete-
;;; frame.

(def-bombout-clean-up-function 'reset-within-delete-frame-scope)

(defparameter classes-to-delete-when-releasing-kb nil)




;;; `Process-classes-queued-by-delete-frame' is called from delete-frame during
;;; delete-frame exit.  When releasing-kb? is t, this function will add the list
;;; of classes queued by delete frame to the master list and, when all frames
;;; have been deleted, the call to delete-classes-queued-by-delete-frame in
;;; release-kb will pass on the master list.  When the kb is not being released,
;;; this function calls delete-classes-queued-by-delete-frame directly.

(defun process-classes-queued-by-delete-frame (class-list)
  (if releasing-kb?
      (setq classes-to-delete-when-releasing-kb
	    (nconc classes-to-delete-when-releasing-kb
		   (copy-list-using-frame-conses class-list)))
      (delete-classes-queued-by-delete-frame class-list)))
	    
	      


;;; `Delete-classes-queued-by-delete-frame' sorts the classes whose definition
;;; frames have been deleted during the recursive descent of delete- frame.  It
;;; sorts them in superior to inferior order to facilitate the reclamation
;;; process.  The list is passed to reclaim-queued-class-descriptions.

(defun delete-classes-queued-by-delete-frame (class-list)
  (let ((sorted-class-list
	  (nreverse
	    (loop for subclass being each subclass of 'item
		  when (memq subclass class-list)
		    collect subclass using frame-cons))))
    #+development
    (when (not (eq (length class-list) (length sorted-class-list)))
      (cerror "frames5" "error in delete-classes-queued-by-delete-frame"))
    (reclaim-queued-class-descriptions sorted-class-list)
    (reclaim-frame-list sorted-class-list)
    (when releasing-kb?
      (reclaim-frame-list class-list))))




;;; `Reclaim-queued-class-descriptions' takes a list of sorted classes from
;;; delete-classes-queued-by-delete-frame and takes care of reclaiming the class
;;; descriptions.  The class-description deletion is done when exiting the
;;; outermost call to delete-frame.

(defun reclaim-queued-class-descriptions (class-list)
  (loop for class in class-list
	for class-description = (class-description class)
	do
    #+development
    (unless (and (class-description-p class-description)
		 (class-description-is-user-defined-p class-description))
      (cerror "FRAMES5" "error in reclaim-queued-class-descriptions"))

    #+development
    (when debugging-class-description-leaks?
      (unless (memq class-description unreclaimed-class-descriptions)
	(cerror "frames5" "reclaim-queued-class-descriptions"))
      (delete-class-description-from-unreclaimed-list class-description))
      
    ;; Slot descriptions and the method tables are reclaimed with special
    ;; code (instead of the automatic class-description member code)
    ;; because there are shared data structures.

    (reclaim-icp-object-map-for-class-description class-description)
    
    (reclaim-slot-descriptions-of-class-description class-description)
      
    (let ((class-method-table?
            (method-table-of-class-description class-description)))
      (when (and class-method-table?
		 (eq (owner-class-of-method-table class-method-table?) class))
	#+development
	(when debugging-class-description-method-table-leaks?
	  (unless (memq class-method-table?
			unreclaimed-class-description-method-tables)
	    (cerror "frames1" "reclaim class-method table"))
	  (delete-class-description-method-table-from-unreclaimed-list
	    class-method-table?))
	(reclaim-method-table-of-class-description class-method-table?)
	(setf (method-table-of-class-description class-description) nil))))

  (loop for class in class-list
	for class-description = (class-description class)
	do
    (frame-push (class-bit-number class-description) class-bit-numbers-pool)
    (setf (class-bit-number class-description) nil)

    (loop with direct-superiors = (direct-superior-classes class)
	  for superior in direct-superiors
	  do
      (setf (inferior-classes superior)
	    (delete-class-description-element
	      class (inferior-classes superior))))
    (reclaim-class-description-list (direct-superior-classes class))
    (setf (direct-superior-classes class) nil)
    (reclaim-class-description-list (inferior-classes class))
    (setf (inferior-classes class) nil)
    (reclaim-class-description class-description)
    (setf (class-description class) nil)
    (with-ignored-forward-references (analyze-compiled-items-for-consistency)
      (analyze-compiled-items-for-consistency class))))
      


 

					

;;; Delete-frame, unless frame is already in the process of being deleted, does the
;;; following, in order. Those marked (*) are done only to blocks.
;;;
;;;  * (1) If within the recursive scope of delete-frame, return doing nothing,
;;;        else set frame-being-deleted.
;;;
;;;  * (2) Remove as block being dragged.
;;;
;;;  * (3) Note deletion for the purpose of saving and journalling if necessary.
;;;
;;;  * (4) If frame is a workspace, deletes any image planes the workspace is on;
;;;
;;;  * (5) If frame is on a workspace, erases it (which erases any connections);
;;;
;;;  * (6) If frame is a subblock, detaches it;
;;;
;;;  * (7) If frame is a block, removes it from any g2-lists that it is a member of;
;;;
;;;  * (8) Deactivates frame (should this be step 2?);
;;;
;;;  * (9) If frame is an item, remove it from any relations it takes part in;
;;;
;;;    (10) Invokes the cleanup method for frame, if any;
;;;
;;;    (11) For each of the slots, other than lookup-structure and class-description-slot,
;;;         whose value is not (eq to) the default value for the slot, a number, or nil:
;;;         if the slot has a slot value reclaimer, invokes that reclaimer with
;;;         the slot's value and the frame, or else if the slot is an attribute slot invokes 
;;;         reclaim-attribute-value, or else if the slot's value is not a
;;;         symbol, invokes reclaim-slot-value;
;;;
;;;  * (10) Set frame-serial-number to -1; remove block from instance list.
;;;
;;;    (11) Release the frame (for recycling).

;;; Deleteing a frame is recursive.  Inferior blocks maybe deleted that
;;; provide foundations for superior blocks (i.e. object definitions may
;;; reside below thier instacnes).  Superior blocks maybe partially
;;; deleted when their inferiors access them (i.e. erasing a subblock may
;;; access the superior block to obtain the background image).

;;; A frame which is an instance of a user defined class may find its definition
;;; being deleted within the dynamic extent of delete-frame on the instance.
;;; The instance continues to need its class-description, however. At present,
;;; the class description is held locally thoughtout the deletion. Deleting the
;;; definition does not destroy this structure, although all references to it
;;; except the local one are removed. Class-descriptions are not reclaimed at
;;; present. We need a method of reclaiming them which happens as the last event
;;; in the outermost of any recursive calls to delete-frame!! ML, 5/15/91 

;;; Delete-frame is universal; it is supposed to do all the right things for all
;;; frames under all possible circumstances.

;;; It is not correct to call delete-frame on a reprocessed vector. (It is ok
;;; to call delete-frame recursively on a BLOCK, but before the vector
;;; reclaiming has occurred. This does nothing.)

;;; While the slot reclaimers are being called, current-block-of-dependent-frame
;;; is bound to NIL, if frame is a block, and to DEPENDENT-FRAME-HAS-NO-OWNER
;;; otherwise.

(defun delete-frame (frame)
  ;; Blocks should not be deleted while frame-being-read? is bound; see fix
  ;; to HQ-4867118 data lost in save/load for details
  (if
    (and (boundp 'frame-being-read?)
	 frame-being-read?
	 (frame-of-class-p frame 'item))
    (if (frame-of-class-p frame 'connection)
	(delete-connection-after-reading-kb frame)
	(delete-block-after-reading-kb frame))
    (progn
      ;; The following sop is only here to catch some of the buggy cases of calling
      ;; delete-frame with an undeleted-frame.  Because of dependent frames and
      ;; recycled system-items, this call can never be more than a sop.  -jallard,
      ;; jed, ajs 6/10/97
      (when (deleted-frame-p frame)
	#+development
	(cerror "ignore"
		"Attempting to delete an available frame vector: ~s" frame)
	(return-from delete-frame nil))
      (let* ((class (class frame))
	     (class-name-of-user-class-definition-frame?
	       (with-ignored-forward-references (name-of-defined-class-function)
		 (and (frame-of-class-p frame 'class-definition)
		      (name-of-defined-class-function frame))))
	     (class-description (class-description-slot frame))
	     (slot-descriptions (slot-descriptions class-description))
	     (frame-is-block? (frame-of-class-p frame 'block))
	     (frame-is-system-item? (frame-of-class-p frame 'system-item))
	     (already-within-delete-frame? within-delete-frame-scope?))

	(when frame-is-system-item?
	  (if (frame-being-deleted-p frame)
	      (return-from delete-frame nil)
	      (set-frame-being-deleted frame))

	  (when tracked-items-call-vector-table
	    (note-possibly-tracked-item-deletion frame))

	  (when profiling-structure
	    (note-possibly-profiled-item-deletion frame)))
	
	(unless already-within-delete-frame?
	  (setq within-delete-frame-scope? t)
	  (when queue-of-classes-to-be-undefined
	    (reclaim-frame-list queue-of-classes-to-be-undefined)
	    (setq queue-of-classes-to-be-undefined nil)))

	(when (and class-name-of-user-class-definition-frame?
		   (classp class-name-of-user-class-definition-frame?)
		   (not (memq class-name-of-user-class-definition-frame?
			      queue-of-classes-to-be-undefined)))
	  ;; TODO: not thread-safe.
	  (setf queue-of-classes-to-be-undefined
		(nconc queue-of-classes-to-be-undefined
		       (frame-list class-name-of-user-class-definition-frame?))))

	(cond
	  (frame-is-block?
	   (with-ignored-forward-references (do-block-specific-deletion-stuff)
	     (do-block-specific-deletion-stuff frame))
	   (when (frame-of-class-p frame 'object-definition)
	     (cleanup-for-stubs-for-class frame))
	   (let ((name-or-names (get-slot-value frame 'name-or-names-for-frame)))
	     (when name-or-names
	       ;; do this first, otherwise it may generate notes, which would leak because
	       ;; name-or-names-for-frame will be reclaimed after frame-status-and-notes,
	       ;; because of the order of the slot-descriptions.
	       ;; This problem may be restricted to method-declaration and tw-method-declaration.
	       (reclaim-name-or-names-for-frame-value name-or-names frame))))
	  (t
	   (funcall-simple-method-if-any-macro 'cleanup frame)))
	
	;; GENSYMCID-1406: Item deleted event
	;; fire callbacks for item delete event
	(send-notification-to-item-internal frame 'delete)

	;; Reclaim slot values that are not null, fixnums, lookup-structures,
	;; or class-description-slots
	(loop with current-block-of-dependent-frame = 'dependent-frame-has-no-owner
	      for slot-description in slot-descriptions
	      as slot-value? = (get-slot-description-value-macro
				 frame slot-description)
	      ;; Note that the following null and fixnum optimizations on reclaiming
	      ;; slot values may be inappropriate if they are in fact neq to the
	      ;; slot-init-form and the slot value reclaimer has side-effects.  This
	      ;; happened when I tried to extend this optimization to symbolp, which
	      ;; broke name-or-names-for-frame.  -jra 5/3/94
	      unless (or (null slot-value?)
			 (fixnump slot-value?)
			 (eq slot-value?
			     (slot-init-form slot-description))
			 (and frame-is-block?
			      (eq (pretty-slot-name slot-description) 'name-or-names-for-frame)))
		do (let ((slot-value-reclaimer?	; see also change-slot-value
			   (slot-description-cached-reclaimer? slot-description)))
		     ;; Update the caching of the reclaimer if necessary.  Note that
		     ;; I'm putting in zero as the marker for a cached value of NIL.
		     ;; I use that because it is faster to do EQ checks vs. fixnums
		     ;; than against symbols.
		     (when (null slot-value-reclaimer?)
		       (setq slot-value-reclaimer?
			     (or (slot-value-reclaimer
				   (pretty-slot-name slot-description))
				 0))
		       (setf (slot-description-cached-reclaimer? slot-description)
			     slot-value-reclaimer?))
		     (cond
		       ((neq slot-value-reclaimer? 0)
			(funcall-simple-compiled-function
			  slot-value-reclaimer? slot-value? frame))
		       ((user-defined-slot-description-p slot-description)
			(reclaim-attribute-value slot-value? frame))
		       ((not (symbolp slot-value?))
			(reclaim-slot-value slot-value?)))))
	(let ((lookup-structure (lookup-structure frame)))
	  (when lookup-structure
	    (reclaim-frame-lookup-structure-vector lookup-structure)
	    (setf (lookup-structure frame) nil)))

	(cond
	  (frame-is-system-item?
	   #+use-a-structure-for-frame-serial-numbers
	   (setf (compound-frame-serial-number-owned-by-frame-p (frame-serial-number frame)) nil)
	   (frame-serial-number-setf (frame-serial-number frame) (frame-serial-number-recycled))
	   (reclaim-frame-serial-number (frame-serial-number frame))
	   (delete-from-instances-specific-to-this-class class frame)
	   (reclaim-frame-vector frame))
	  (t
	   (mark-frame-as-available frame)
	   (reclaim-managed-simple-vector frame)))

	(when class-name-of-user-class-definition-frame?
	  (setf (class-definition class-name-of-user-class-definition-frame?) nil))
	(unless already-within-delete-frame?
	  (when queue-of-classes-to-be-undefined
	    (process-classes-queued-by-delete-frame
	      queue-of-classes-to-be-undefined)
	    (reclaim-frame-list queue-of-classes-to-be-undefined)
	    (setq queue-of-classes-to-be-undefined nil))
      (setq within-delete-frame-scope? nil))))))

;; There is one cleanup method now, which makes object and connection
;; definitions undefine their classes.

;; Consider having this not bother to look for slot value reclaimers for "root
;; slots", but instead have them directly handled in delete-frame.
;; If the frame is a kb-frame, then consider setting the system-variable current-
;; frame-serial-number-at-last-delete to the value (current-frame-serial-number),
;; to enable the functionality of (kb-frames-have-not-been-deleted-p
;; reference-frame-serial-number).




;;; `Delete-instances-specific-to-this-class' calls delete-frame for all strict
;;; instances of class.

(defun delete-instances-specific-to-this-class (class)
  (loop with reference-serial-number = (copy-frame-serial-number (current-frame-serial-number))
	with instance-list =
	  (loop for instance being each strict-class-instance of class
		collect instance using frame-cons)
	for instance in instance-list do
    (when (frame-has-not-been-reprocessed-p instance reference-serial-number)
      (delete-frame instance))
	finally (progn (reclaim-frame-serial-number reference-serial-number)
		       (reclaim-frame-list instance-list))))


;;; `Delete-class-description-element-from-slot-descriptions' removes the
;;; slot-description class-description cons from the slot-descriptions of
;;; class-description.

(defun delete-class-description-element-from-slot-descriptions
    (slot-description-being-deleted class-description)
  (let* ((slot-descriptions (slot-descriptions class-description))
	 (first-slot-description (car slot-descriptions)))
    (if (eq first-slot-description slot-description-being-deleted)
	(reclaim-class-description-cons 
	  (prog1 slot-descriptions
	    (setf (slot-descriptions class-description)
		  (cdr slot-descriptions))))
	(loop for sublist on slot-descriptions
	      for slot-description = (cadr sublist)
	      do
	  (when (eq slot-description slot-description-being-deleted)
	    (reclaim-class-description-cons 
	      (prog1 
		  (cdr sublist) 
		(setf (cdr sublist) (cddr sublist))))
	    (loop-finish))))))




;;; `Delete-slot-description-from-hash-table' deletes a slot description from
;;; the hash table of the class description when a user has deleted an attribute
;;; from the class-specific-attributes slot of a class definition.

;;; See FRAMES1 for a discussion of full and sparse hash tables.

(defun-void delete-slot-description-from-hash-table
    (slot-description class-description)
  (if (class-description-has-full-hash-table-p class-description)
      (delete-slot-description-from-full-hash-table
	slot-description class-description)
      (delete-slot-description-from-sparse-hash-table-if-present
	slot-description class-description)))

(defun-void delete-slot-description-from-full-hash-table
    (slot-description class-description)
  (let* ((pretty-slot-name (pretty-slot-name slot-description))
	 (slot-descriptions-hash-table
	   (slot-descriptions-hash-table class-description))
	 (new-hash-table-value-for-pretty-slot-name?
	   (get-new-default-slot-description-with-pretty-name
	     slot-description class-description)))
    (delete-slot-hash
      (unique-slot-name slot-description) slot-descriptions-hash-table)
    (if new-hash-table-value-for-pretty-slot-name?
	(setf (get-slot-hash pretty-slot-name slot-descriptions-hash-table)
	      new-hash-table-value-for-pretty-slot-name?)
	(delete-slot-hash pretty-slot-name slot-descriptions-hash-table))))

(defun-void delete-slot-description-from-sparse-hash-table-if-present
    (slot-description class-description)
  (let* ((pretty-slot-name (pretty-slot-name slot-description))
	 (unique-slot-name (unique-slot-name slot-description))
	 (slot-descriptions-hash-table
	   (slot-descriptions-hash-table class-description))
	 (new-hash-table-value-for-pretty-slot-name?
	   (get-new-default-slot-description-with-pretty-name
	     slot-description class-description)))
    (when (eq (get-slot-hash pretty-slot-name slot-descriptions-hash-table)
	      slot-description)
      (delete-slot-hash pretty-slot-name slot-descriptions-hash-table)
      (when  new-hash-table-value-for-pretty-slot-name?
	(setf (get-slot-hash pretty-slot-name slot-descriptions-hash-table)
	      new-hash-table-value-for-pretty-slot-name?)))
    (when (eq (get-slot-hash unique-slot-name slot-descriptions-hash-table)
	      slot-description)
      (delete-slot-hash unique-slot-name slot-descriptions-hash-table))))





;;;; Additional Parent Frame Code

;;; This section was moved here to use the iterators strict-class-instance
;;; and friends while still being in the generic section of the frame system
;;; (i.e. FRAMES1, FRAMES2, TYPES, and FRAMES2A).


;;; `Determine-possible-parent-attribute-name-changes' loops though the
;;; subclasses of user-class, examining instance attributes with the new
;;; attribute-name and user-class defining class.  If the slot value for the
;;; attribute is a frame, the parent-attribute-name slot for that frame is
;;; changed to the new-attribute-name, using a class-qualified cons when the
;;; new-attribute-name needs qualification, otherwise using the attribute-name
;;; symbol.

(defun determine-possible-parent-attribute-name-changes
    (user-class new-attribute-name)
  (loop for subclass being each subclass of user-class
	do
    (when (instantiated-class-p subclass)
      (let* ((class-description (class-description subclass))
	     (new-attribute-slot-description
	      (get-slot-description-of-class-description
		new-attribute-name class-description user-class)))
	(loop for instance being each strict-class-instance of subclass
	      for slot-value = (get-slot-description-value
				 instance new-attribute-slot-description)
	      do
	  (when (framep slot-value)
	    (let ((current-parent-attribute-name
		   (parent-attribute-name slot-value))
		  (new-attribute-name-needs-qualification?
		   (slot-name-needs-qualification-p
		     new-attribute-slot-description class-description)))
	      (setf (parent-attribute-name slot-value)
		    (if new-attribute-name-needs-qualification?
			(slot-value-cons new-attribute-name user-class)
			new-attribute-name))
	      (reclaim-slot-value current-parent-attribute-name))))))))




;;; The function `add-class-qualifier-to-parent-attribute-names-if-necessary'
;;; adds a class-qualified name value to the parent-attribute-name slot of any
;;; subframe values of attributes with attribute-name that will no longer be the
;;; default attribute with that name for the subclasses of user-class.

;; This function is called before the new slot-description is added to the
;; hierarchy.  If the current "default" slot-description with attribute-name
;; has a defining-class component that names a class that is less-specific than
;; user-class, the parent-attribute-name of any frame slot values will need
;; class qualification.

(defun add-class-qualifier-to-parent-attribute-names-if-necessary
    (user-class attribute-name)
  (loop for subclass being each subclass of user-class
	for existing-slot-description? =
	      (slot-description-from-class subclass attribute-name)
	do
    (when existing-slot-description?
      (loop with class-inheritance-path = (class-inheritance-path
					    (class-description subclass))
	    for instance being each strict-class-instance of subclass
	    for slot-value = (get-slot-description-value
			       instance
			       existing-slot-description?)
	    do
	(when (and (framep slot-value)
		   (more-specific-class-p
		     user-class (defining-class existing-slot-description?)
		     class-inheritance-path))
	  (let ((current-parent-attribute-name
		 (parent-attribute-name slot-value)))
	    (setf (parent-attribute-name slot-value)
		  (slot-value-cons-macro
		    attribute-name (defining-class existing-slot-description?)))
	    ;; Unless there is an incorrect value from an existing kb, this
	    ;; value should be an unqualified symbol.
	    (reclaim-slot-value current-parent-attribute-name)))))))




;;; The function
;;; `remove-class-qualifier-from-parent-attribute-names-if-necessary'
;;; substitutes an unqualified name reference for a class-qualified name
;;; reference to the parent-attribute-name slot of any subframe values of
;;; attribute name that are now the default attribute with that name for all
;;; subclasses of user-class.

;; This is called after the slot-description is removed from the class
;; hierarchy.  

(defun remove-class-qualifier-from-parent-attribute-names-if-necessary
    (user-class attribute-name)
  (loop for subclass being each subclass of user-class
	for existing-slot-description? =
	      (slot-description-from-class subclass attribute-name)
	do
    (when existing-slot-description?
      (loop for instance being each strict-class-instance of subclass
	    for slot-value = (get-slot-description-value
			       instance
			       existing-slot-description?)
	    do
	(when (framep slot-value)
	  (let ((current-parent-attribute-name
		 (parent-attribute-name slot-value)))
	    (setf (parent-attribute-name slot-value)
		  attribute-name)
	    (reclaim-slot-value current-parent-attribute-name)))))))




;;; Reclaim-attribute-value is used to reclaim attribute-value when the frame
;;; in which it is an attribute slot value is deleted, provided the slot has no
;;; slot value reclaimer and provided the attribute value is not nil, a number,
;;; the value of special variable no-value, or (eq to) the default value for the
;;; slot.  If attribute-value is a variable, reclaim-attribute-value will 
;;; remove it from the list of variables to be simulated.

(defun reclaim-attribute-value (attribute-value frame)
  (declare (ignore frame))
  (with-ignored-forward-references (remove-variable-from-simulation)
    (when (of-class-p attribute-value 'variable-or-parameter)
      (remove-variable-from-simulation attribute-value)))
  (cond
    ((framep attribute-value)
      (set-parent-information attribute-value nil nil nil)	; optimization
      (delete-frame attribute-value))
    (t (reclaim-slot-value attribute-value))))






;;;; Validating Frames and Evaluation Values



;;; This section is being added to FRAMES2A to help make the frame and evaluation
;;; value system more modular, or more precisely, to make it more independent of
;;; the particulars of the classes that are part of AB, but not other systems.


;;; Typically, role servers will not give out inactive objects, however, for the
;;; the simulator and inspector, inactive objects should be served.  This can be
;;; controlled by binding the computation-flag `role-serve-inactive-objects?'.
;;; Its default value is NIL.

;;; Another exception is that designations evaluated from within show and hide
;;; actions will serve inactive items.

(def-concept role-serve-inactive-objects?)

(def-concept attempting-network-write-access-p)

(def-concept attempting-network-read-access-p)

(def-substitution-macro serve-item-p-macro (item)
  (with-local-computation-flags
    (let ((class-description (class-description-slot item)))
      (and (or (class-description-of-class-p class-description 'item)
	       (and (serve-loose-ends-p)
		    (eq (class-name-of-class-description class-description) 'loose-end)))
	   (or (active-p item)
	       ;; Do not serve items that are in the process of creation or initialization.
	       (and (not (frame-serial-number-equal (frame-serial-number item)
						    (frame-serial-number-recycled)))
		    (or (role-serve-inactive-objects?-local)
			;; Kb-workspace is a special case to support
			;; the activate action on subworkspaces
			(class-description-of-class-p
			  class-description 'kb-workspace))))
	   (or (not (serve-only-permanent-items-p-local))
	       (permanent-block-p item))
	   (or (not (attempting-network-write-access-p-local))
	       (item-remotely-modifiable-p item))
	   (or (not (attempting-network-read-access-p-local))
	       (item-remotely-visible-p item))))))

(defun-simple serve-item-p (item)
  (serve-item-p-macro item))

;; Modified serve-item-p to work for network security.  It now consults the
;; predicates item-remotely-modifiable-p and item-remotely-visible-p before
;; returning true, if we are in a context where we should check.  Currently, such
;; contexts only occur in G2-to-G2 connections.  jh, 1/30/91.

;; jh, 6/3/91.  Commented out the clauses in serve-item-p related to network
;; security.  This is being dropped for 3.0.

;; It seems that there are bugs in some of the roles such that they serve
;; objects which are not items.  This can be fixed, though somewhat kludgily) by
;; testing that these things really are items.  -jra 11/19/91

;; edited to activate network security annotation -ncc 18 Jan 1994  

(defun-simple validate-item-or-evaluation-value
	      (value frame-serial-number? type-spec-for-validation?)
  (cond
    ((evaluation-item-reference-p value)
     (evaluation-item-reference-referenced-item value))
    ((null frame-serial-number?)
     value)
    ((frame-or-deleted-frame-p value)
     (and (not (frame-has-been-reprocessed-p value frame-serial-number?))
	  (serve-item-p value)
	  (or (null type-spec-for-validation?)
	      (and (or (eq type-spec-for-validation? 'item-or-datum)
		       (valid-class-type-specification-p
			 type-spec-for-validation?))
		   (type-specification-type-p value type-spec-for-validation?)))
	  value))
    (t
     (let* ((defined-evaluation-value-type?
		(and (consp value)
		     (defined-evaluation-value-type-p (cdr-of-cons value))))
	    (validator? 
	      (and defined-evaluation-value-type?
		   (defined-evaluation-type-validator (cdr-of-cons value)))))
       (cond
	 (validator?
	  (funcall-simple-compiled-function validator? value frame-serial-number?))
	 (type-spec-for-validation?
	  (and (or (eq type-spec-for-validation? 'item-or-datum)
		   (valid-datum-type-specification-p type-spec-for-validation?))
	       (type-specification-type-p value type-spec-for-validation?)
	       value))
	 (t
	  value))))))

#+development
(defun check-user-defined-attribute-values-for-type-conformance ()
  (let ((instance-and-slot-list nil))
    (loop for class being each subclass of 'item
	  when (user-defined-class-p class)
	    do
	      (loop for sd in (slot-descriptions (class-description class))
		    when (user-defined-slot-description-p sd)
		      do
			(loop with type-specification = (slot-type-specification sd)
			      for instance being each strict-class-instance of class
			      for slot-value = (get-slot-description-value
						 instance sd)
			      for slot-value-for-checking =
			            (if (slot-constantp slot-value)
					(cast-slot-constant-into-evaluation-value
					  slot-value)
					slot-value)
			      when (not (type-specification-type-p 
					  slot-value-for-checking
					  type-specification))
				do
				  (setq instance-and-slot-list
					(nconc
					  instance-and-slot-list
					  (frame-list
					    (frame-list
					      instance
					      (unique-slot-name sd))))))))
    instance-and-slot-list))
			      


;; End file with CR.

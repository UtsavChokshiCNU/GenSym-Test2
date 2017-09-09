;; -*- mode: lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module RELATIONS

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Michael Levin, Chris Morel, et al.






;;; In CHAINING

(declare-forward-reference invoke-rules-for-relation-chaining function)

;;; In RUN

(declare-forward-reference break-out-of-debug-messages function)

;;; in KB-LOAD2

(declare-forward-reference loading-kb-p variable)

;;; In KB-SAVE3

(declare-forward-reference note-change-or-deletion function)
(declare-forward-reference note-change-to-runtime-data-for-block-1 function)

;;; In KB-SAVE4

(declare-forward-reference initializing-clear-text-p variable)
(declare-forward-reference traversing-xml-object-p variable)
(declare-forward-reference in-write-module-as-clear-text-p variable)

;;; In FRAMES2A
(declare-forward-reference frame-hash-function function)

(def-frame-note-writer duplicate-uuids (particulars)
  (twrite-string "this is one of ")
  (twrite particulars)
  (twrite-string " distinct items with the same uuid"))


;;; `update-frame-notes-for-duplicate-uuids' manages the frame notes that are placed on
;;; blocks with duplicate uuids. It presumes that the uuid is associated
;;; with at least one frame. If it determines that is is associated
;;; with more than one frame, it returns t and posts the appropriate
;;; notes. Otherwise it returns nil. If block-that-can-not-be-table-entry?
;;; is supplied, then if the uuid is duplicated it additionally checks
;;; whether that block is the one that is stored as the entry for this
;;; uuid in the table, and changes the entry if necessary.

(defun update-frame-notes-for-duplicate-uuids (uuid)
  (when uuid
    ;; This routine is called on all uuid changes, which includes the case of
    ;; the slot value being set to nil.
    (let* ((block-or-block-list (get-item-or-item-list-for-uuid uuid))
	   (number-of-blocks-with-that-uuid
	     (if (listp block-or-block-list)
		 (loop for frame in block-or-block-list
		       unless (frame-of-class-p frame 'remote-item)
			 count 1)
		 (if (frame-of-class-p block-or-block-list 'remote-item)
		     0
		     1))))
      (cond
	((>f number-of-blocks-with-that-uuid 1)
	 (loop for frame in block-or-block-list
	       unless (frame-of-class-p frame 'remote-item)
		 do (add-frame-note 
		      'duplicate-uuids frame number-of-blocks-with-that-uuid))
	 t)
	((=f number-of-blocks-with-that-uuid 1)
	 ;; This block may have had a duplicate uuid before. If so,
	 ;; remove the note that reflected that.
	 (delete-frame-note-if-any
	   'duplicate-uuids (if (listp block-or-block-list)
				(loop for frame in block-or-block-list
				      unless (frame-of-class-p frame 'remote-item)
					return frame)
				block-or-block-list))
	 nil)))))



;;;; Definitions for Relations




;;; A `relation' is a binary relation in the mathematical sense between objects
;;; of one class and objects of another (not necessarily distinct) class.
;;; Relations may be one-to-one, one-to-many, many-to-one, or many-to-many.

;;; A relation has a relation-name, and it may also have an inverse-of-relation,
;;; which is its name for the symmetric relation. 

;;; A relation may be symmetric, in which case the relation-name is used in both
;;; directions and there is no inverse name.

;;; The domain and range of a relation are referred to as the subject and the
;;; object.

;; Options coming presently.

;; (1) Permanent relations: A relation which is not permanent looses its
;; instances upon the item at either end of the instance being deactivated.

;; (2) Relations in which domain or range may be data rather than items.




;;; Role service for the above:

;;; (SERVE-FIRST-VALUE-OF-ROLE (RELATED relation-name) item1) Serves
;;; (non-deterministically) an item of the subject class which is related to
;;; item1.  If there are more than than one such, it serves a continuation.

;;; (SERVE-FIRST-VALUE-OF-ROLE-INVERSE item2 quantifier (RELATED relation-name)
;;; domain-designation) serves an item of the object class related to item2 if
;;; it meets the filtering requirements for inverse service. Inverse service is
;;; available only when there is an inverse-of-relation or the relation is
;;; symmetric.

;; (SERVE-FIRST-VALUE-OF-ROLE (RELATED relation-name)) serves all instances of
;; class1 that participate in the relation.  NOT AVAILABLE YET!

;;; Role service, given the object and the relation-name, serves all subjects.
;;; When a relation has an inverse-of-relation [is symmetric], role service
;;; given the the subject and the inverse-of-relation [relation-name], serve all
;;; objects. Example: If X is parent-of Y, then X is the subject and Y the
;;; object of the instance. Parent-of maps objects to subjects. Given Y, it
;;; gives X which is the parent. This may seem surprising, and follows from the
;;; use of a passive construct in the phrase "X is parent-of Y."

;; Lowell says that Y HAS PARENT X. The grammar used here requires an
;; inverse-of-relation (***) and the use of the phrase "Y is *** of X." Only
;; CHILD-OF seems to fit.




;; To do:

;; Make rules compile a validation predicate.
;; Continuation {after the first) validates it.
;; Also fix non-context alist problem at same time.

;; List of forms (binding-name binding-name relation-name)

;; Write a validation testing macro.

;; Relations with data.

;; Changes while running.  - In version 4.0, cpm, 3/2/94.

;; Consider run-time choice of relations.
;; x that is related by <exp> to y
;; x is related by <exp> to y
;; for any x related-by <exp> to y



;; Note on deactivation:
;; This does not currently cause a relation instance to disappear. It merely
;; hides acess to the instance until it is restored. Clarify and document.
;; Consider using deactivate method!!!    26 Sept. 89 ML


;;;; Data Structures for Relations (#+relation-instances-v2)



;;; There is a slot on every item called relation-instances. 
;;; Its value is a skip-list-or-binary-tree of relation-instance structures as entries:
;;;
;;; 	(relation-name relation instances)
;;;                   or
;;;     (inverse-of-relation relation instances)
;;;
;;; The key of skip-list-or-binary-tree is the relation-name. Its second is the
;;; relation itself (a frame), and next is a constant-queue of items it is paired with.
;;; An item may not appear on the constant-queue of a relation-instance more than once.

;;; NOTE: the tree name is also used by copy-for-slot-value and reclaim-slot-value.

#+relation-instances-v2
(def-skip-list-or-binary-tree relation-instance-tree
  :hash-function sxhash-symbol
  :accessor get-relation-instance ; API
  :key-deleter delete-relation-instance
  :constructor make-relation-instance-tree
  :reclaimer reclaim-relation-instance-tree
  :max-level 7)

(defun-simple relation-instances-empty-p (relation-instances)
  (or (null relation-instances)
      #+relation-instances-v2
      (skip-list-or-binary-tree-empty-p relation-instances)))

(defmacro relation-instances-not-empty-p (relation-instances)
  `(not (relation-instances-empty-p ,relation-instances)))

#-relation-instances-v2
(def-substitution-macro get-relation-instance (name relation-instances)
  (assq name relation-instances))

(defun-simple get-relation-instance-function (key tree)
  (get-relation-instance key tree))

(def-substitution-macro relation-instance-tree-p (relation-instances)
  (and (consp relation-instances)
       (eq (car-of-cons relation-instances) 'relation-instance-tree)))

(defun-simple reclaim-relation-instances (tree) ; must be function
  (when tree
    #+relation-instances-v2
    (reclaim-relation-instance-tree tree) ; TODO: memory leak: related-items
    #-relation-instances-v2
    (reclaim-slot-value-tree tree)))

#+relation-instances-v2
(def-structure (relation-instance
		 (:type vector)
		 (:creations-at-a-time 100)
		 (:constructor
		   make-relation-instance-structure
		   (relation-instance-name
		    relation-instance-relation
		    relation-instance-items))
		 (:reclaimer reclaim-relation-instance-structure))
  relation-instance-name     ; symbol
  relation-instance-relation ; instance of "relation" class
  relation-instance-items)  ; constant queue

#-relation-instances-v2
(defmacro relation-instance-name (relation-instance) ; API
  `(car-of-cons ,relation-instance)) ; first

#-relation-instances-v2
(defmacro relation-instance-relation (relation-instance) ; API
  `(cadr-of-cons ,relation-instance)) ; second

#-relation-instances-v2
(defmacro relation-instance-items (relation-instance) ; API
  ;; returns a list or nil
  `(cddr ,relation-instance)) ; third and rests

#+relation-instances-v2.1
(def-skip-list-or-binary-tree related-item-tree
  :hash-function sxhash-lisp-object
  :accessor get-related-item
  :key-deleter delete-related-item
  :constructor make-related-item-tree
  :reclaimer reclaim-related-item-tree
  :max-level 7)

#+relation-instances-v2
(defun-simple make-relation-instance (name relation object)
  (let ((blocks #+relation-instances-v2.0 (make-empty-constant-queue)
		#+relation-instances-v2.1 (make-related-item-tree)))
    (when object
      #+relation-instances-v2.0
      (constant-queue-filo-enqueue blocks object)
      #+relation-instances-v2.1
      (setf (get-related-item object blocks) object))
    (make-relation-instance-structure name relation blocks)))

#+relation-instances-v2
(defun-simple reclaim-relation-instance (instance)
  (#+relation-instances-v2.0 reclaim-constant-queue
   #+relation-instances-v2.1 reclaim-related-item-tree
   (atomic-exchange (relation-instance-items instance) nil))
  (reclaim-relation-instance-structure instance))

(define-loop-path related-item ; API
  #-relation-instances-v2
  expand-list-loop-iterator
  #+relation-instances-v2.0
  constant-queue-elements-of
  #+relation-instances-v2.1
  expand-skip-list-or-binary-tree-value-loop-iterator (of))

(defun-simple copy-list-of-relation-instance (relation-instance) ; API
  #+relation-instances-v2
  (let* ((head (slot-value-list
		 (relation-instance-name relation-instance)
		 (copy-for-slot-value
		   (relation-instance-relation relation-instance))))
	 (tail (loop for block being each related-item
			       of (relation-instance-items relation-instance)
		     when block
		     collect (copy-for-slot-value block) using slot-value-cons)))
    (nconc head tail))
  #-relation-instances-v2
  (copy-for-slot-value relation-instance))

(def-substitution-macro relation-exist-p (the-block blocks) ; API
  #-relation-instances-v2
  (memq the-block blocks)
  #+relation-instances-v2.0
  (loop for block being each related-item of blocks
	thereis (eq block the-block))
  #+relation-instances-v2.1
  (get-related-item the-block blocks))

(def-substitution-macro related-items-is-empty-p (related-items)
  (or (null related-items)
      #+relation-instances-v2.0
      (constant-queue-empty-p related-items)
      #+relation-instances-v2.1
      (or (skip-list-or-binary-tree-empty-p related-items)
	  (loop for item being each related-item of related-items
		never item))))

(def-substitution-macro related-items-is-not-empty-p (related-items)
  (and related-items
       #+relation-instances-v2.0
       (constant-queue-non-empty-p related-items)
       #+relation-instances-v2.1
       (loop for item being each related-item of related-items
	     thereis item)))

(def-substitution-macro at-least-one-related-item-p (related-items)
  (related-items-is-not-empty-p related-items))

(def-substitution-macro first-related-item (related-items) ; API
  #-relation-instances-v2
  (car related-items)
  #+relation-instances-v2.0
  (constant-queue-peek related-items)
  #+relation-instances-v2.1
  (loop for item being each related-item of related-items
	when item do (return item)
	finally (return nil)))

(def-substitution-macro first-relation-item (relation-instance) ; API
  (first-related-item (relation-instance-items relation-instance)))

#+relation-instances-v2.1
(defun-simple more-than-one-related-item-p (skip-list-or-binary-tree)
  (loop for item being each related-item of skip-list-or-binary-tree
	with count fixnum = 0
	until (=f 2 count)
	when item do (incff count)
	finally (return (=f 2 count))))

#|
(loop for item in '(1 nil nil 3 2)
	with count fixnum = 0
	until (=f 2 count)
	when item do (incff count)
	finally (return (=f 2 count)))
|#

#+relation-instances-v2.0
(defun-simple more-than-one-related-item-p (constant-queue)
  #+Lockfree-Deque
  (let ((head (constant-queue-head constant-queue))
	(tail (constant-queue-tail constant-queue)))
    (neq (constant-queue-next head constant-queue)
	 (constant-queue-previous tail constant-queue)))
  #-Lockfree-Deque
  (neq (constant-queue-head constant-queue)
       (constant-queue-tail constant-queue)))

#-relation-instances-v2
(defmacro more-than-one-related-item-p (list)
  `(cdr-of-cons ,list))

#+relation-instances-v2.1
(defun-simple only-one-related-item-p (skip-list-or-binary-tree)
  (loop for item being each related-item of skip-list-or-binary-tree
	with count fixnum = 0
	when item do (incff count)
	finally
	  (return (=f count 1))))

#+relation-instances-v2.0
(defun-simple only-one-related-item-p (constant-queue)
  #+Lockfree-Deque
  (let ((head (constant-queue-head constant-queue))
	(tail (constant-queue-tail constant-queue)))
    (eq (constant-queue-next head constant-queue)
	(constant-queue-previous tail constant-queue)))
  #-Lockfree-Deque
  (eq (constant-queue-head constant-queue)
      (constant-queue-tail constant-queue)))

#-relation-instances-v2
(defmacro only-one-related-item-p (list)
  `(null (cdr-of-cons ,list)))

(define-loop-path relation-instance
  #+relation-instances-v2 expand-skip-list-or-binary-tree-value-loop-iterator
  #-relation-instances-v2 expand-list-loop-iterator (of))

(defun-simple copy-list-of-relation-instances (relation-instances)
  (when relation-instances
    (loop for instance being each relation-instance of relation-instances
	  for new-entry = (copy-list-of-relation-instance instance)
	  when new-entry
	  collect new-entry using slot-value-cons)))

(defmacro reclaim-related-items (related-items)
  #-relation-instances-v2
  `(reclaim-frame-list ,related-items)
  #+relation-instances-v2.0
  `(reclaim-constant-queue ,related-items)
  #+relation-instances-v2.1
  `(reclaim-related-item-tree ,related-items))

(defun-simple copy-related-items (related-items)
  #+relation-instances-v2
  (loop for related-item being each related-item of related-items
	when related-item
	collect related-item using frame-cons)
  #-relation-instances-v2
  (copy-list-using-frame-conses related-items))

#+relation-instances-v2
(defun upgrade-relation-instances (blocks)
  (when (listp blocks) ; for safety purpose
    (loop for block in blocks do
      (upgrade-relation-instance block))))

(def-substitution-macro old-relation-instances-p (old-relation-instances)
  (or (null old-relation-instances)
      (and (consp old-relation-instances)
	   (neq (car old-relation-instances) 'relation-instance-tree))))

#+relation-instances-v2
(defun upgrade-relation-instance (block)
  (let ((old-relation-instances? (relation-instances block)))
    (when (old-relation-instances-p old-relation-instances?)
      (let ((new-relation-instances (make-relation-instance-tree)))
	(upgrade-relation-instance-internal old-relation-instances? new-relation-instances)
	#-SymScale
	(progn
	  (when old-relation-instances?
	    (reclaim-slot-value-tree old-relation-instances?))
	  (setf (relation-instances block) new-relation-instances))
	#+SymScale
	(if (compare-and-swap (relation-instances block)
			      old-relation-instances?
			      new-relation-instances)
	    (when old-relation-instances?
	      (reclaim-slot-value-tree old-relation-instances))
	  (error "what?!"))))))

#+relation-instances-v2
(defun upgrade-relation-instance-internal (old-relation-instances new-relation-instances)
  ;; NOTE: the following LOOP does nothing if old-relation-instances is NULL
  (loop for old-relation-instance in old-relation-instances
	for name = (car old-relation-instance)
	for relation = (cadr old-relation-instance)
	for new-relation-instance = (make-relation-instance name relation nil)
	for queue-or-tree = (relation-instance-items new-relation-instance)
	do
    (loop for instance in (cddr old-relation-instance) do
      #+relation-instances-v2.0
      (constant-queue-enqueue queue-or-tree instance)
      #+relation-instances-v2.1
      (setf (get-related-item instance queue-or-tree) instance))
    ;; put item into the tree
    (setf (get-relation-instance name new-relation-instances)
	  new-relation-instance)))

;;;; Data Structures for Relations (#-relation-instances-v2)



;;; There is a slot on every item called relation-instances. 
;;; Its value is a possibly empty list of relation-instance-forms as follows:
;;;
;;; 	(relation-name relation . instances)
;;;                   or
;;;     (inverse-of-relation relation . instances)              
;;;
;;; Thus it is an alist whose key is a relation-name. Its second is the
;;; relation itself (a frame), and cddr is a list of items it is paired with.
;;; The form exists only if there are instances. (I.e. its cddr may not
;;; be null.) An item may not appear on cddr of a relation-instance-form more
;;; than once.

;;; When a relation has no inverse-of-relation, and is not symmetric, the
;;; structure described above maps from the object to the subject.
					; But, there is a secret-inverse in this
					; case.  - cpm, 3/3/94


;;; When a relation is symmetric, the structure described above maps in both
;;; directions.
					;I don't think that we can distinguish
					;between the subject and object in this
					;case (by checking the relation-
					;instances of the two items).  This
					;would be useful in updating existing
					;relation instances when a relation
					;definition is modified.  - cpm, 3/3/94

;;; When the relation has an inverse-of-relation, the structure described above
;;; maps from the object to the subject using the relation name, and from the
;;; subject to the object using the inverse-of-relation. When the relation is
;;; symmetric, the relation-name is used in both directions.

;;; When a relation is symmetric, and an item is related to itself, the item
;;; appears only once on its own relation-instance-form for the relation name.
;;; This is to maintain a constraint that an item never appears more than once
;;; on the same relation-instance-form.

;;; Unabstracted reference to these data structures appear only in the basic
;;; functions of this file.






;;;; CLASS RELATION




(def-class (relation (item entity) (foundation-class relation))
  (frame-author-or-authors nil (type authors-with-time-of-last-edit?))
  (frame-change-log nil (type frame-change-log))
  (name-or-names-for-frame		; gets filled in per 
    nil do-not-save (type nil)		;   relation-name
    do-not-put-in-attribute-tables
    (attribute-export-comment
      "Export for convenience, writable = false, relation-name is settable ~
	 and name automatically filled in."))
  (class-of-subject item system user-overridable vector-slot (type class))
  (class-of-object item system user-overridable vector-slot (type class))
  (relation-name
    nil system vector-slot (type relation-name?) do-not-clone
    (attribute-export-comment
      "Type = (or none symbol). writable = true, List of names not permitted."))
  (inverse-of-relation
    nil system vector-slot (type relation-name?) do-not-clone
    (attribute-export-comment "type = (or symbol none), writable = true"))
  (type-of-relation
    many-to-many system vector-slot
    (type oneness-type)
    (attribute-export-comment
      "type = (member one-to-one, one-to-many, many-to-one, many-to-many)"))
  (relation-is-symmetric nil vector-slot
			 (type relation-yes-or-no?)
			 (attribute-export-comment
			   "writable = true, type = (or none boolean)"))
  (relation-is-permanent nil system user-overridable (type yes-or-no)
			 user-overridable
			  (attribute-export-comment
			    "writable = true, type = boolean"))

  (relation-summary nil system lookup-slot not-user-editable
		    do-not-identify-in-attribute-tables
		    (type relation-summary)
		    (attribute-export-comment
		      "writable = false, type = string"))

  ;; The secret-inverse-name is a symbol which is used in lieu
  ;; of an inverse name when there is none, and the relation is
  ;; not symmetric.
  (secret-inverse-name nil system vector-slot)
  
  (icon-description
    (:funcall-at-load-time
      create-icon-description
      60 40 
      ((outline  (15 0) (15 15) (45 15) (45 0) (60 20)
		 (45 40) (45 25) (15 25) (15 40) (0 20))))
    (attribute-export-comment
      "Should we handle exporting of this icon-description, which is defined ~
 on the class rather than inherited, differently from those on most other classes?")))

;; NOTE: modify the function update-relation-instances-if-necessary if the user
;; editable-slots change.  - cpm, 3/1/94


(def-absent-slot-putter relation-is-symetric (relation value)
  (put-relation-is-symmetric relation value t))   ;misspelling


(define-slot-alias first-class class-of-subject relation)
(define-slot-alias second-class class-of-object relation)




;;; The predicate `relation-violates-class-or-permanency-constraints-p'
;;; returns an error string if the relation is found invalid; otherwise it
;;; returns nil.
;;;
;;; This predicate is a helper function for the virtual-attribute relationships
;;; setter.  It does not check for two other relation violations: missing 
;;; relation frames and uniqueness violations.  The former is checked for in the
;;; setter and the latter will be taken care of in the add-to-relation function
;;; when it is called with a non-null now-case? argument (the new relation
;;; overrides the existing relation).

(defun relation-violates-class-or-permanency-constraints-p
    (given-name relation item1 item2)
  (let* ((relation-name relation)
	 (subject-class (class-of-object relation))
	 (object-class (class-of-subject relation))
    	 (other-name nil)
	 (subject nil)
	 (object nil))
	 
    (cond
      ;; If the given name is relation-name
      ((and (eq given-name (relation-name relation))
	    (or (not (relation-is-symmetric relation))
		(and (frame-of-class-p item2 subject-class) ; subject item
		     (frame-of-class-p item1 object-class)) ; object item
		(not (frame-of-class-p item2 object-class)) ; subject item
		(not (frame-of-class-p item1 subject-class)))) ; object item
       (setq other-name
	     (if (relation-is-symmetric relation)
		 relation-name
		 (or (inverse-of-relation relation) (secret-inverse-name relation))))
       (setq subject item2)
       (setq object item1))

	 ;; If given name is inverse name.
      (t
       (setq other-name given-name)
       (setq subject item1)
       (setq object item2)))

    ;; Check item1 and item2 for being of the appropriate classes.
    (let ((error-string?
            (cond
              ((not (frame-of-class-p subject subject-class))
               (tformat-text-string
                 "Cannot establish the relation ~a between ~NF and ~NF.  ~
                  ~NF is not of class ~a."
                 given-name object subject subject subject-class))
              ((not (frame-of-class-p object object-class))
              (tformat-text-string
                 "Cannot establish the relation ~a between ~NF and ~NF.  ~
                  ~NF is not of class ~a."
                 given-name object subject object object-class))
              (t nil))))
      (when error-string?
	(return-from relation-violates-class-or-permanency-constraints-p error-string?)))))


(def-virtual-attribute relationships
    ((class block)
     ;; HQ-2127565:
     ;; No-item type left for backward-compatibility.  The empty sequence is now
     ;; returned for no relation-instances.  (11/5/98)
     (or (no-item)
	 (sequence     
	   (structure
	     ((relation-name-reference symbol)
	      ;; relation-is-inverted is optional for backwards-compatibility
	      ;; and read-only (it's value is ignored in the setter)
	      (relation-is-inverted truth-value)
	      (related-items (sequence (class item) 1)))
	     (and relation-name-reference related-items))))
     ())
  
  :event-updates :within-putter
  :initial ((class) (declare (ignore class)) nil)
  
  :getter
  ((block)
   (let ((relation-instances (relation-instances block)))
     (if relation-instances
	 (loop
	   for relation-instance being each relation-instance of relation-instances
	   for source-name-reference = (relation-instance-name relation-instance)
	   for relation = (relation-instance-relation relation-instance)
	   for relation-name = (relation-name relation)
	   for secret-inverse-name?
	       = (unless (or (relation-is-symmetric relation)
			     (inverse-of-relation relation))
		   (secret-inverse-name relation))
	   ;; Export the same relation-name reference that describe does.
	   for name-reference-to-export
	       = (if (eq source-name-reference secret-inverse-name?)
		     relation-name
		     source-name-reference)
	   ;; Do not serve inactive or disabled items.
	   ;;
	   ;; GENSYMCID-1640: KB-XML load problem: error concluding the relationships
	   ;; also do not serve unsavable blocks when saving XML KBs.
	   ;; -- Chun Tian (binghe), June 24, 2016
	   for related-items? = (loop for related-item being each related-item
					  of (relation-instance-items relation-instance)
				      when (and related-item
						(serve-item-p related-item)
						(if in-write-module-as-clear-text-p
						    (savable-block-p related-item)
						  t))
					collect related-item using frame-cons)
	   when related-items?
	     collect
	     (allocate-evaluation-structure
	       (nconc
		 (eval-list 'relation-name-reference name-reference-to-export)
		 ;; NEW - Let the user know if they have an inverse or not.
		 ;; This is to fix bug HQ-3138429.  Note that we ignore this
		 ;; value in the setter.  -dkuznick, 3/13/00
		 (eval-list 'relation-is-inverted
			    (make-evaluation-boolean-value
			      (and (not (relation-is-symmetric relation))
				   (not (eq source-name-reference
					    secret-inverse-name?)))))
		 (prog1 (eval-list 'related-items
				   (with-list-to-evaluation-sequence-mapping
				       (related-items? item)
				     item))
		   (reclaim-frame-list related-items?))))
	       into relations-eval-list
	       using eval-cons
	   finally (return (allocate-evaluation-sequence relations-eval-list)))
       ;; still need to return something.
       (allocate-evaluation-sequence nil))))

  :setter
  ((block new-value)
   ;; Fix for bug HQ-2171426.  A list of the current relations for the block is
   ;; now consed for use in deciding whether to fire relation rules when a
   ;; relation is added or removed.  Because the setter removes all of the
   ;; current relations before putting in the new value, a check must be made to
   ;; see that we have a genuine removal or addition.  The existing relations-to-
   ;; add-information list is used to determine what relations are in the new value.
   ;; (ghw 11/3/98)
   (let ((old-relations-for-block?
	  (when-let (relation-instances (relation-instances block))
	    (loop for relation-instance being each relation-instance of relation-instances
		  for relation-frame = (relation-instance-relation relation-instance)
		  for related-items = (relation-instance-items relation-instance)
		  collect (nconc (frame-list relation-frame)
				 (copy-related-items related-items))
		  using frame-cons)))
	 (relations-to-add-information? nil)
	 (string-of-errors? nil))
     (unless (or (null new-value) (evaluation-sequence-empty-p new-value))
       ;; The main function of this loop is to check whether any relations in
       ;; the new value are invalid because of a missing relation-frame, class-
       ;; type violation, or permanency constraint.  All invalid-relation error
       ;; strings are concatenated so that full information can be given to the
       ;; user when there is an error.  A stack error will occur if there is any
       ;; invalid relation and the relaiton-instances slot value will maintain
       ;; its current value.
       ;;
       ;; Until there is an error, this loop will also frame-cons a list of
       ;; calling sequences to be used for add-to-relation calls.
       (loop with no-error-condition? = t
	     for relation-structure being each evaluation-sequence-element of new-value
	     for exported-name-reference = (evaluation-structure-slot
					     relation-structure
					     'relation-name-reference)
	     for related-items-sequence = (evaluation-structure-slot
					    relation-structure 'related-items)
	     for related-items
		 = (loop for related-item being each evaluation-sequence-element
						of related-items-sequence
			 when (and related-item (framep related-item))
			   collect related-item using frame-cons)
	     for relation-frame = (get-instance-with-name-if-any
				    'relation exported-name-reference)
	     do
	 (cond ((null relation-frame)
		(reclaim-frame-list related-items)
		(setq string-of-errors?
		      (if string-of-errors?
			  (prog1
			      (tformat-text-string
				"~a~%The value of a relation-name-reference component, ~
                                 ~a, does not name a relation."
				string-of-errors? exported-name-reference)
			    (reclaim-text-string string-of-errors?))
			  (tformat-text-string
			    "The value of a relation-name-reference component, ~a, ~
                             does not name a relation." exported-name-reference))))
	       (t
		(loop with relation-name = (relation-name relation-frame)
		      with relation-is-symmetric? = (relation-is-symmetric relation-frame)
		      with secret-inverse-name?
			= (unless (or relation-is-symmetric?
				      (inverse-of-relation relation-frame))
			    (secret-inverse-name relation-frame))
		      ;; For add-to-relation use the relation-name reference that
		      ;; allows the item to be item1 and the related item to be item2.
		      with relation-reference-for-setting
			= (if (neq exported-name-reference relation-name)
			      relation-name
			      (if (or relation-is-symmetric? secret-inverse-name?) 
				  relation-name
				  (inverse-of-relation relation-frame)))
		      for related-item in related-items ; list
		      for error-result? 
		          = (cond (secret-inverse-name?
				   (let* ((subject-class (class-of-subject
							   relation-frame))
					  (block-is-subject-class-p
					    (frame-of-class-p block subject-class))
					  (relation-direction-ambiguous-p
					    (and block-is-subject-class-p
						 (frame-of-class-p related-item
								   subject-class))))
				     (cond ((if relation-direction-ambiguous-p
						;; Read the following as relation is not inverted
						(let ((relation-is-inverted-eval-val?
							(evaluation-structure-slot
							  relation-structure
							  'relation-is-inverted)))
						  (if (and relation-is-inverted-eval-val?
							   (evaluation-truth-value-p
							     relation-is-inverted-eval-val?))
						      (not (evaluation-truth-value-is-true-p
							     relation-is-inverted-eval-val?))
						      ;; Otherwise use the old test
						      block-is-subject-class-p))
						;; Otherwise use the old test
						block-is-subject-class-p)
					    ;; The mess above is to keep existing
					    ;; "functionality" {allowing you to
					    ;; conclude from the "wrong" side if
					    ;; you can figure out the
					    ;; directionality based on the classes
					    ;; of the two objects} {Comment which
					    ;; led to this below} Sigh...  I knew
					    ;; there would be a problem with just
					    ;; the relation-is-inverted-p
					    ;; test. The old code was trying to be
					    ;; too cute, {frame-of-class-p block
					    ;; {class-of-subject relation-frame}}
					    ;; because when the subject and object
					    ;; were of different types (as
					    ;; specified in the
					    ;; relation-definition), it was trying
					    ;; to use the types of the objects to
					    ;; decide which way the user was
					    ;; trying to do the conclude!  That's
					    ;; completely broken because if the
					    ;; two sides are of the same type,
					    ;; that won't work.  But if I remove
					    ;; that "functionality" and force the
					    ;; use of relation-is-inverted, I'll
					    ;; break existing KBs.  I guess I can
					    ;; go use it in the case when both
					    ;; objects could be the first class.
					    ;; What a frigging MESS!  -dkuznick,
					    ;; 1/25/01
					    (when no-error-condition?
					      (setq relations-to-add-information?
						    (nconc
						      relations-to-add-information?
						      (frame-list
							(frame-list
							  relation-frame
							  relation-reference-for-setting
							  block
							  related-item)))))
					    (relation-violates-class-or-permanency-constraints-p
					      relation-reference-for-setting
					      relation-frame block related-item))
					   (t
					    (when no-error-condition?
					      (setq relations-to-add-information?
						    (nconc
						      relations-to-add-information?
						      (frame-list
							(frame-list
							  relation-frame
							  relation-reference-for-setting
							  related-item block)))))
					    (relation-violates-class-or-permanency-constraints-p
					      relation-reference-for-setting
					      relation-frame related-item block)))))
				  (t
				   (when no-error-condition?
				     (setq relations-to-add-information?
					     (nconc
					       relations-to-add-information?
					       (frame-list
						 (frame-list
						   relation-frame
						   relation-reference-for-setting
						   block related-item)))))
				   (relation-violates-class-or-permanency-constraints-p
				     relation-reference-for-setting relation-frame
				     block related-item)))
		      when error-result?
			do (setq no-error-condition? nil)
			   (setq string-of-errors?
				 (if string-of-errors?
				     (prog1
					 (tformat-text-string
					   "~a~%~a" string-of-errors? error-result?)
				       (reclaim-text-string string-of-errors?))
				     error-result?))
		      finally (reclaim-frame-list related-items))))))

     (cond
       (string-of-errors?
	;; Return the string-of-errors? to generate a stack error.  The current relations
	;; will be retained.
	(reclaim-frame-tree relations-to-add-information?)
	(reclaim-frame-tree old-relations-for-block?)
	string-of-errors?)
       (t
	(when-let (relation-instances (relation-instances block))
	  ;; Remove the relations in the current value.
	  (loop with copy-of-current-value = (copy-list-of-relation-instances relation-instances)
		for relation-instance in copy-of-current-value
		for relation-reference = (car-of-cons relation-instance)
		for relation-frame = (car-of-cons (cdr-of-cons relation-instance))
		for relation-name = (relation-name relation-frame)
		for related-items = (cddr relation-instance)
		for relation-is-symmetric? = (relation-is-symmetric relation-frame)
		for inverse-of-relation? = (inverse-of-relation relation-frame)
		for secret-inverse-name?
		    = (unless (or relation-is-symmetric? inverse-of-relation?)
			(secret-inverse-name relation-frame))
		for relation-reference-for-removing
		    = (if (neq relation-reference relation-name)
			  relation-name
			  (if (or relation-is-symmetric? secret-inverse-name?)
			      relation-name
			      inverse-of-relation?))
		for relation-frame-appears-in-new-value?
		    = (assq relation-frame relations-to-add-information?)

		do
	    ;; A relation is removed because it appears in the current relation-instances,
	    ;; so an error from remove-from-relation is a bug that will be brought to
	    ;; development, not user, attention.
	    (loop for related-item in related-items ; list
#| TODO: removed part from 8.3r1 code base, why?
		  for related-item-appears-in-new-value?
		      = (and relation-frame-appears-in-new-value?
			     (memq related-item relation-frame-appears-in-new-value?))
|#
		  do
	      ;; The last three arguments to remove-from-relation are called-from-procedure?,
	      ;; invoke-rules-for-relation-chaining?, and remove-given-name-direction-only?.
	      (let ((successful-removal?
		      (if secret-inverse-name?
			  (if (eq relation-reference secret-inverse-name?)
			      (remove-from-relation
				relation-reference-for-removing block related-item nil
				(not relation-frame-appears-in-new-value?) nil)
			      (remove-from-relation
				relation-reference-for-removing related-item block nil
				(not relation-frame-appears-in-new-value?) nil))
			  (remove-from-relation
			    relation-reference-for-removing block related-item nil
			    (not relation-frame-appears-in-new-value?) nil))))
		#-development
		(declare (ignore successful-removal?))
		#+development
		(unless successful-removal?
		  (cerror "relations" "error1 in relationships -- tell ghw"))))
		finally
		  #+development
		  (when (relation-instances-not-empty-p (relation-instances block))
		    (cerror "relations" "error2 in relationships"))
		  (reclaim-slot-value copy-of-current-value)))

	(loop for (relation-frame relation-reference item1 item2)
		  in relations-to-add-information?
	      for cons-holding-relation-frame-in-previous-value?
	          = (assq relation-frame old-relations-for-block?)
	      for items-were-in-relation-in-old-value?
	          = (and cons-holding-relation-frame-in-previous-value?
			 (or (memq item1 cons-holding-relation-frame-in-previous-value?)
			     (memq item2 cons-holding-relation-frame-in-previous-value?)))
	      do
	  (let ((error-result?
		  ;; The last three arguments to add-to-relation are now-case?
		  ;; called-from-procedure? and invoke-rules-for-relation-chaining?.
		  (add-to-relation
		    relation-reference item1 item2 t nil
		    (not items-were-in-relation-in-old-value?))))
	    #-development
	    (declare (ignore error-result?))
	    #+development
	    (when error-result?
	      (cerror "relations" "error3 in relationships")))
	      finally (reclaim-frame-tree relations-to-add-information?)
		      (reclaim-frame-tree old-relations-for-block?))

	#+development
	(when (block-relation-instances-violate-class-type-p block)
	  (cerror "relations" "error4 in relationships"))
	
	nil)))))




(def-virtual-attribute items-in-this-relation
    ((class relation)
     (or (no-item)
	 (sequence (class item) 1)) 
     ())
  
  :event-updates :within-putter
  :initial ((class) (declare (ignore class)) nil)
  
  :getter
  ((relation)
   (let* ((relation-name (relation-name relation))
	  (inverse-name
	    (or (inverse-of-relation relation) (secret-inverse-name relation)))
	  (class-of-subject (class-of-subject relation))
	  (class-of-subject-name-reference (or inverse-name relation-name))
	  (class-of-object (class-of-object relation))
	  (items-in-relation?
	    (let ((collector-list nil))
	      (loop for block being each class-instance of class-of-subject
		    for relation-instances = (relation-instances block)
		    when (and relation-instances
			      (get-relation-instance class-of-subject-name-reference relation-instances)
			      (serve-item-p block))
		      do (eval-push block collector-list))
	      (loop for block being each class-instance of class-of-object
		    for relation-instances = (relation-instances block)
		    when (and relation-instances
			      (get-relation-instance relation-name relation-instances)
			      (not (memq block collector-list))
			      (serve-item-p block))
		      do (eval-push block collector-list))
	      collector-list)))
     (when items-in-relation?
       (allocate-evaluation-sequence items-in-relation?)))))





;;; the macros `unique-forward-relation-type' and `unique-forward-relation'
;;; check if the relation-type is unique in the given direction.

(defmacro unique-forward-relation-type (type-of-relation)
  `(memq ,type-of-relation '(one-to-one many-to-one)))

(defmacro unique-reverse-relation-type (type-of-relation)
  `(memq ,type-of-relation '(one-to-one one-to-many)))



;;; The macros `unique-reverse-relation-type', and `unique-reverse-relation'
;;; check that the relation-type of the relation is unique in the given
;;; direction.

(defmacro unique-forward-relation (relation)
  `(unique-forward-relation-type (type-of-relation ,relation)))

(defmacro unique-reverse-relation (relation)
  `(unique-reverse-relation-type (type-of-relation ,relation)))


;;; The macro `valid-symmetric-relation-type'checks if the relation-type is
;;; valid assuming a symmetric relation.

(defmacro valid-symmetric-relation-type (type-of-relation)
  `(memq ,type-of-relation '(one-to-one many-to-many)))






;;;; Constraints on the relation frame.




;;; (1) If relation-name is nil, inverse-of-relation is nil.
;;; (2) Either relation-is-symmetric is nil, or inverse-of-relation
;;; is nil, or both.
;;; (3) Relation-name is the same as the primary name of the relation
;;;     if wither exist. (= name-or-names-for frame or car of same)
;;; (4) Inverse-of-relation is the secondary name of relation if either
;;;     exist. (= second of name-or-names-for-frame).

;;; These are enforced by slot value compilers and slot putters.

;;; A relation is valid iff it has a relation-name. Only a valid
;;; relation may have instances.



;;; Constraints between a relation frame and its instances:

;;; These constraints are maintained by add-to-relation, remove-from
;;; relation, remove-transient-relation-instances, and by changes to
;;; the slots of the relation that are involved in the constraints.

;;; (1) The range and domain must be frames of class class-of-subject and
;;; class-of-object respectively.
;;;     As of version 4.0, for symmetric relations, the range and domain must
;;; be frames of either the classes class-of-subject and class-of-object or
;;; the reverse.
					; The above change regarding subject and
					; object classes of symmetric relations
					; was needed for version 4.0.  This was
					; seen as an error for relations in
					; general and will now be tested in
					; add-to-relation.  - cpm, 3/4/94

;;; (2) The relation-instance-forms must be maintained as specified
;;; above.

;;; These constraints may have the effect of removing or modifying
;;; instances of the relation when either of the names or classes
;;; is modified.

;;; The uniquness of values as specified by type-of-relation is NOT
;;; such a maintained constraint. It is maintained by add-to-relation
;;; only, but can easily be violated by changing the slots of the
;;; relation or incorrect use of add-to-relation when the subject
;;; and object classes intersect and the relation is symmetric.






;;;; Compilers, Writers, and Grammar for Class Relation




;; As of version 4.0, the following slots are no longer restricted and can now
;; be modified while G2 is running or paused, as well as being reset:
;;   relation-name
;;   inverse-of-relation
;;   class-of-subject
;;   class-of-object
;;   type-of-relation
;;   relation-is-symmetric



(defun no-change-while-running ()
  (values bad-phrase
	  (copy-constant-wide-string #w"Reset G2, then make this change.")))



;; The following two defvars are documented in files TABLES
;; and MENUS respectively.

;(defvar grammar-categories-getting-?-in-attribute-table
;	 '(relation-yes-or-no?))
;; See note in Tables near make-text-for-cell-identifying-attribute-in-table

(defvar grammar-categories-getting-yes-no-feature
  '(relation-yes-or-no?))



(def-slot-value-writer relation-yes-or-no? (yes-or-no)
  (if yes-or-no (twrite "yes") (twrite "no")))


;; A yes/no value doesn't get set using the slot-value-compiler??  Currently,
;; the slot-putter for relation-is-symmetric enforces the constraint between the
;; inverse-name and relation-is-symmetric slots.  The slot-putter will not allow
;; the relation to be symmetric if it already has an inverse-name.  In that
;; case, it does not set the symmetric flag to yes, but does not give a warning.
;; - cpm, 3/8/94
;
;(def-slot-value-compiler relation-yes-or-no? (parse-result relation)
;  (if (and parse-result (inverse-of-relation relation))
;      (values
;        bad-phrase
;        (copy-text-string
;          "A symmetric relation may not have an inverse of relation."))
;      parse-result))



(def-slot-value-writer-as-existing-function relation-name?
    write-symbol-from-slot)


(def-slot-value-compiler relation-name? (parse-result relation slot-name)
  (let ((new-name? (if (neq parse-result 'none) parse-result)))
    
    (cond
      
      ;; The forward name may not be set to none if there is a
      ;; reverse name.
      ((and (eq slot-name 'relation-name)
	    (null new-name?)
	    (inverse-of-relation relation))
       (values bad-phrase
	       (copy-constant-wide-string #w"Remove the reverse name first.")))
      
      ;; No change being made.
      ((or (and (eq slot-name 'relation-name)
		(eq new-name? (relation-name relation)))
	   (and (eq slot-name 'inverse-of-relation)
		(eq new-name? (inverse-of-relation relation))))
       new-name?)
      
      ;; If the name is is use, do nothing, return old value.
      ((get-instance-with-name-if-any 'root new-name?)
       (values bad-phrase (copy-constant-wide-string #w"This name is in use.")))
      
      ;; If FORWARD NAME is being edited, set primary name.
      ((eq slot-name 'relation-name)
       (change-primary-name-of-frame relation new-name? nil)
       new-name?)
      
      ;; If the relation is symmetric, a reverse name is not allowed.
      ((relation-is-symmetric relation)
       (values
	 bad-phrase
	 (copy-text-string
	   "A symmetric relation may not have an inverse of relation.")))

      ;; Assume that REVERSE NAME is being edited.
      ;; If there is a primary name, set the secondary name.
      ((name-or-names-for-frame relation)
       (change-secondary-name-of-frame relation new-name? nil)
       new-name?)
      
      ;; If reverse name cannot be added because there is no
      ;; forward name, do nothing, return nil.
      (t
       (values bad-phrase
	       (copy-constant-wide-string #w"Supply the relation name first."))))))



(add-grammar-rules
  '((oneness-type 'one-to-one)
    (oneness-type 'one-to-many)
    (oneness-type 'many-to-one)
    (oneness-type 'many-to-many)

    (relation-name? relation-name)
    (relation-name? 'none)

    (relation-yes-or-no? yes-or-no)
      ;; This had been yes-or-no?, but that expanded into yes-or-no anyway
      ;; and we're expunging yes-or-no? as explained in Tables. ddm 12/18/96
    ))


(def-slot-value-writer oneness-type (value)
  (tformat "~(~a~)" value))

(def-slot-value-compiler oneness-type (parse-result relation)
  (cond
    ((and (relation-is-symmetric relation)
	  (not (valid-symmetric-relation-type parse-result)))
     (values
       bad-phrase
       (copy-text-string
	 "A symmetric relation can only be one-to-one or many-to-many.")))
    (t parse-result)))

(define-category-evaluator-interface (oneness-type
				       :access read-write)
    (member one-to-one one-to-many many-to-one many-to-many)
  ((set-form (evaluation-value))
   evaluation-value)
  ((get-form (slot-value))
   slot-value))

(define-category-evaluator-interface (relation-yes-or-no?
				       :access read-write)
    truth-value
  ((set-form (evaluation-value))
   (evaluation-truth-value-is-true-p evaluation-value))
  ((get-form (slot-value))
   (make-evaluation-boolean-value slot-value)))





(def-slot-value-writer relation-summary (value relation)
  (declare (ignore value))
  (let ((name (relation-name relation))
	(reverse-name (inverse-of-relation relation))
	(forward-class (class-of-subject relation))
	(reverse-class (class-of-object relation))
	(uniqueness-type (type-of-relation relation)))

    (cond
      (name
       (tformat "~(~a~a may be ~a ~a ~a~)"
		(supply-a-or-an forward-class)
		forward-class name
		(if (memq uniqueness-type '(one-to-one many-to-one))
		    "at most one" "more than one")
		reverse-class)
       (tformat ";~%")
       (cond
	 (reverse-name
	  (tformat "~(~a~a may be ~a ~a ~a~)"
		   (supply-a-or-an reverse-class)
		   reverse-class reverse-name
		   (if (memq uniqueness-type '(one-to-one one-to-many))
		       "at most one" "more than one")
		   forward-class))
	 (t (tformat "~(~a ~a may be ~a ~a~a~)"
		     (if (memq uniqueness-type '(one-to-one one-to-many))
			 "at most one" "more than one")
		     forward-class
		     name
		     (supply-a-or-an reverse-class)
		     reverse-class))))
      (t nil))))



;;; Write-relation-instances writes a list of relation instances that
;;; an item participates in.

#+unused
(defun write-relation-instances (relation-instances)
  (loop for listed-relation-instance-form on relation-instances
	for relation-instance-form = (car listed-relation-instance-form) doing
    (tformat "~(~a~): " (car relation-instance-form))
    (loop for listed-item on (cddr relation-instance-form)
	  for item = (car listed-item) doing
      (let ((name? (get-primary-name-for-frame-if-any item)))
	(if name?
	    (tformat "~(~a~)" name?)
	    (let ((class (class item)))
	      (tformat "~(~a~a~)"
		       (supply-a-or-an class)
		       class))))
      (if (cdr listed-item) (twrite ", ")))

    (if (cdr listed-relation-instance-form) (tformat ";~%"))))






;;;; Slot putters




(def-slot-putter relation-name (relation value initializing?)
  (let ((old-value #-SymScale (relation-name relation)
		   #+SymScale (atomic-exchange (relation-name relation) value)))
    #-SymScale
    (setf (relation-name relation) value)

    (when old-value
      (delete-from-directory-of-names old-value 'relation-name))
    (when value
      (add-to-directory-of-names value 'relation-name)
      (setf (secret-inverse-name relation)
	    (intern-text-string (tformat-text-string "~a sEcReT iNvErSe NaMe" value))))

    (cond
      (initializing?
       (change-primary-name-of-frame relation value initializing?))
      (t
       (update-relation-instances-if-necessary
	 relation 'relation-name value old-value)
       (update-representations-of-slot-value relation 'relation-summary)))
    value))

(def-slot-value-reclaimer relation-name (value frame)
  (declare (ignore value))
  (put-relation-name frame nil nil))

(def-slot-putter inverse-of-relation (relation value initializing?)
  (let ((old-value #-SymScale (inverse-of-relation relation)
		   #+SymScale (atomic-exchange (inverse-of-relation relation) value)))
    #-SymScale
    (setf (inverse-of-relation relation) value)

    (when old-value
      (delete-from-directory-of-names old-value 'relation-name))
    (when value
      (add-to-directory-of-names value 'relation-name))

    (cond
      (initializing?
       (change-secondary-name-of-frame relation value initializing?))
      (t
       (update-relation-instances-if-necessary
	 relation 'inverse-of-relation value old-value)
       (update-representations-of-slot-value relation 'relation-summary)))
    value))

(def-slot-value-reclaimer inverse-of-relation (value frame)
  (declare (ignore value))
  (put-inverse-of-relation frame nil nil))

(def-slot-putter class-of-subject (relation value initializing?)
  (let ((old-value #-SymScale (class-of-subject relation)
		   #+SymScale (atomic-exchange (class-of-subject relation) value)))
    #-SymScale
    (setf (class-of-subject relation) value)

    (unless initializing?
      (update-relation-instances-if-necessary
	relation 'class-of-subject value old-value)
      (update-representations-of-slot-value relation 'relation-summary))
    value))


(def-slot-putter class-of-object (relation value initializing?)
  (let ((old-value #-SymScale (class-of-object relation)
		   #+SymScale (atomic-exchange (class-of-object relation) value)))
    #-SymScale
    (setf (class-of-object relation) value)

    (unless initializing?
      (update-relation-instances-if-necessary
	relation 'class-of-object value old-value)
      (update-representations-of-slot-value relation 'relation-summary))
    value))


(def-slot-putter type-of-relation (relation value initializing?)
  (let ((old-value #-SymScale (type-of-relation relation)
		   #+SymScale (atomic-exchange (type-of-relation relation) value)))
    #-SymScale
    (setf (type-of-relation relation) value)

    (unless initializing?
      (update-relation-instances-if-necessary
	relation 'type-of-relation value old-value)
      (update-representations-of-slot-value relation 'relation-summary))
    value))


(def-slot-putter relation-is-symmetric (relation value initializing?)
  (let ((old-value? (relation-is-symmetric relation))
	(new-value?
	  (and value (null (inverse-of-relation relation)))))
    #-SymScale
    (setf (relation-is-symmetric relation) new-value?)
    #+SymScale
    (unless (compare-and-swap (relation-is-symmetric relation) old-value? new-value?)
      (error "what?!"))

    (unless initializing?
      (update-relation-instances-if-necessary
	relation 'relation-is-symmetric new-value? old-value?)
      (update-representations-of-slot-value relation 'relation-summary))
    new-value?))






;;;; Adding and removing relation instances




;;; The function `add-to-relation' adds the given pair to the relation provided
;;; that (i) a relation of the given name exists, (ii) item1 and item2 are of
;;; the correct classes, or (iii) that the uniqueness of the relation (its
;;; uniqueness in a given direction) is not violated.  The value is nil.
;;; Otherwise, the value returned is a t.

;;; If now-case is true, then the uniqueness constraints are not enforced by
;;; doing.  nothing. Instead, the old instance is removed from the relation, and
;;; the new instance replaces it.

;;; To understand the semantics of the code, and the use of "subject"
;;; and "object", consider "conclude that x is father-of y" This establishes
;;; a pointer from y to x, its father. Therefore, item2 is subject of the
;;; relation, and y is object. "Given-name" is the name supplied by the
;;; action. It may be either the relation-name or the inverse-name, and this has
;;; to be determined by inspecting the relation. If the given name is the
;;; inverse-name, then item1 is the subject, etc.

;;; Since this function has been modified to print its own error messages
;;; (instead of printing from the action), a new called-from-procedure?
;;; argument has been added.  If this argument is non-nil, error messages are
;;; not printed.  In the case of an error, an error message string is created
;;; and returned (instead of t).  This should be reclaimed by the caller.

;;; When the relation R is symmetric and the subject and object classes differ,
;;; allow the user to add a new relation in either direction.  For example,
;;; "conclude x is <r> y" or "conclude y is <r> x".
;; The above was added as a fix to version 4.0.  - cpm, 3/8/94

;;; As of version 4.0, there is a new argument that controls whether the
;;; relation change can invoke rules for chaining.

;; This is not complete. The "is now" feature does not remove!!!

;; This should give diagnostics instead!!!

(defun add-to-relation (given-name item1 item2 now-case called-from-procedure?
				   invoke-rules-for-relation-chaining?)
  (note-change-to-runtime-data-for-block item1)
  (note-change-to-runtime-data-for-block item2)
  (let* ((errors nil)
	 relation
	 relation-name
	 other-name
	 subject
	 object
	 subject-class
	 object-class
	 subject-instances
	 object-instances	 
	 subject-instance-form
	 object-instance-form	 
	 (unique-forward? nil)
	 (unique-reverse? nil)
	 (subject-and-object-switched? nil))

    ;; The fast way to access the relation is via item2 if it is there, since
    ;; this has to be looked up anyway.  A by-product is that we get instances
    ;; and an instance-form, but we don't know yet whether these are subject or
    ;; object, since we could have started with either name as given name. This
    ;; is rectified shortly.
    (setq subject-instances (relation-instances item2))
    (when subject-instances
      (setq subject-instance-form (get-relation-instance given-name subject-instances))
      (when subject-instance-form
	(setq relation (relation-instance-relation subject-instance-form))))

    ;; Otherwise get it by its name.
    (unless subject-instance-form
      (setq relation (get-instance-with-name-if-any 'relation given-name)))

    ;; If no relation, error code 0.
    (unless relation
      (let ((error-string
	      (tformat-text-string "There is no relation named ~a."
				   given-name)))
	(if called-from-procedure?
	    (return-from add-to-relation error-string)
	    (progn
	      (warning-message* 1 "~a" error-string)
	      (reclaim-text-string error-string)
	      (return-from add-to-relation 0)))))

    (setq relation-name (relation-name relation))
    ;; These slots were incorrectly named before it was realized that the
    ;; relation went from item2 to item1. They are aliased to "first class" and
    ;; "second class" resepctively.
    (setq subject-class (class-of-object relation)
	  object-class (class-of-subject relation))
    (cond
      ;; If the given name is relation-name
      ((and (eq given-name (relation-name relation))
	    (or (not (relation-is-symmetric relation))
		;; For symmetric relation, don't switch subject and object when
		;; the items fit the subject and object classes, or if switching
		;; would cause a conflict with the classes.  (Not switching when
		;; there is a conflict allows the error message below to be of
		;; the correct form.)
		;; When the relation R is symmetric and the subject and object
		;; classes differ, switching allows the user to "conclude x is
		;; <r> y" or "conclude y is <r> x".
					; These tests for symmetric relations
					; were added as a fix to version 4.0.  -
					; cpm, 3/6/94
		(and (frame-of-class-p item2 subject-class) ; subject item
		     (frame-of-class-p item1 object-class)) ; object item
		(not (frame-of-class-p item2 object-class)) ; subject item
		(not (frame-of-class-p item1 subject-class)))) ; object item

	  (setq other-name
		(if (relation-is-symmetric relation)
		    relation-name
		    (or (inverse-of-relation relation)
			(secret-inverse-name relation)))
		subject item2
		object item1)
	  ;; If subject-instances or subject-instance-form are non-null
	  ;; they have already been set above.
	  ;; Set object-instances and object-instance-form.
	  (setq object-instances (relation-instances object)
		object-instance-form (if object-instances
					 (get-relation-instance other-name object-instances))))
	 ;; If given name is inverse name.
      (t (setq other-name given-name
	       subject item1
	       object item2
	       subject-and-object-switched? t)
	 ;; If subject-instances is non-null, they actually belong to object,
	 ;; because they were lookup up on item2 which is object. Move them.
	 (setq object-instances subject-instances
	       object-instance-form subject-instance-form
	       subject-instances (relation-instances subject)
	       subject-instance-form (if subject-instances
					 (get-relation-instance relation-name subject-instances)))))

    ;; Unique-forward? means that subject may participate in at most or one
    ;; relation instance of this relation.
    (case (type-of-relation relation)
      (one-to-one
       (setq unique-forward? t)
       (setq unique-reverse? t))
      (one-to-many
       (setq unique-forward? t))
      (many-to-one
       (setq unique-reverse? t)))

    ;; Do nothing if relation instance already exists.
    ;;
    ;; TODO: this is the performance bottleneck in UC14. It loops on every related
    ;; items in the constant queue, which is quite large in this case. maybe we
    ;; should really use another tree for `related-items' in the future. But even
    ;; current work has doubled the performance in UC14. -- Chun Tian (binghe).
    (if (and subject-instance-form
	     (relation-exist-p object (relation-instance-items subject-instance-form)))
	(return-from add-to-relation nil))

    ;; Check item1 and item2 for being of the appropriate classes.
    (let ((error-string?
            (cond
              ((not (frame-of-class-p subject subject-class))
               (tformat-text-string
                 "Cannot establish the relation ~a between ~NF and ~NF.  ~
                  ~NF is not of class ~a."
                 given-name object subject subject subject-class))
              ((not (frame-of-class-p object object-class))
	       (tformat-text-string
                 "Cannot establish the relation ~a between ~NF and ~NF.  ~
                  ~NF is not of class ~a."
                 given-name object subject object object-class))
              (t nil))))
      (when error-string?
        (cond (called-from-procedure?
               (setq errors error-string?))
              (t
               (warning-message* 1 "~a" error-string?)
               (reclaim-text-string error-string?)
               (setq errors t)))))

    (cond
      (now-case
       ;; A constraint violation causes the previous instance to be removed.
       (let (previously-related-item)
	 (when (and unique-forward?
		    subject-instance-form
		    (neq object
			 (setq previously-related-item
			       (first-relation-item subject-instance-form))))
	   ;; previously-related-item could be NIL at this point, subject is not NIL
	   (remove-from-relation
	     relation-name previously-related-item subject nil t nil)
	   (setq subject-instances (relation-instances subject))
	   (when subject-instances
	     (setq subject-instance-form
		   (get-relation-instance relation-name subject-instances)))
	   (setq object-instances (relation-instances object))
	   (when object-instances
	     (setq object-instance-form
		   (get-relation-instance other-name object-instances))))

	 (when (and unique-reverse?
		    object-instance-form
		    (neq subject
			 (setq previously-related-item
			       (first-relation-item object-instance-form))))
	   (remove-from-relation
	     relation-name object previously-related-item nil t nil)
	   (setq subject-instances (relation-instances subject))
	   (when subject-instances
	     (setq subject-instance-form
		   (get-relation-instance relation-name subject-instances)))
	   (setq object-instances (relation-instances object))
	   (when object-instances
	     (setq object-instance-form
		   (get-relation-instance other-name object-instances))))))
      (t
       ;; A constraint violation causes the instance not to be added.
       ;; A level 1 warning message is created.
       ;; We want the error message to use given-name, the name
       ;; the user used when referring to the relation. This means
       ;; that we have to refer to the items in the order the
       ;; user did, so we use item1 and item2 here, rather than
       ;; subject and object. That's why we still need 2 cases here,
       ;; where the rest of the code was able to coalesce what used
       ;; to be 2 cases by always using subject and object instead of
       ;; item1 and item2. -alatto, 11/6/03
       (let ((subject-related-items
	      (when subject-instance-form
		(relation-instance-items subject-instance-form)))
	     (object-related-items
	      (when object-instance-form
		(relation-instance-items object-instance-form))))
	  (when (and unique-forward?
		     (and subject-instance-form
			  (related-items-is-not-empty-p subject-related-items)))
	    (let ((error-string?
		    (uniqueness-message 
		      relation-name given-name relation item1 item2
		      (if subject-and-object-switched?
			  item1
			  (first-related-item subject-related-items))
		      (if subject-and-object-switched?
			  (first-related-item subject-related-items)
			  item2)
		      called-from-procedure?)))
	      (setq errors (or error-string? t))))
	  (when (and unique-reverse?
		     (and object-instance-form
			  (related-items-is-not-empty-p object-related-items)))
	    (let ((error-string?
		    (uniqueness-message 
		      relation-name given-name relation item1 item2
		      (if subject-and-object-switched?
			  (first-related-item object-related-items)
			  item1)
		      (if subject-and-object-switched?
			  item2
			  (first-related-item object-related-items))
		      called-from-procedure?)))
	    (setq errors (or error-string? t)))))))

    (if errors
	(return-from add-to-relation errors))
 
    ;; Add relation-instance to subject.
    (cond
      (subject-instance-form
       #-relation-instances-v2
       (nconc subject-instance-form (slot-value-list object))
       #+relation-instances-v2
       (let ((instance-items (relation-instance-items subject-instance-form)))
	 #+relation-instances-v2.0
	 (constant-queue-enqueue instance-items object)
	 #+relation-instances-v2.1
	 (setf (get-related-item object instance-items) object)))
      (t
       (setq subject-instance-form
	     #-relation-instances-v2
	     (slot-value-list relation-name relation object)
	     #+relation-instances-v2
	     (make-relation-instance relation-name relation object))
       #-relation-instances-v2
       (if subject-instances
	   (nconc subject-instances (slot-value-list subject-instance-form))
	   (setf (relation-instances subject)
		 (slot-value-list subject-instance-form)))
       #+relation-instances-v2
       (if subject-instances
	   (setf (get-relation-instance relation-name subject-instances)
		 subject-instance-form)
	 #-SymScale
	 (setf (relation-instances subject)
	       (let ((new-tree (make-relation-instance-tree)))
		 (setf (get-relation-instance relation-name new-tree) subject-instance-form)
		 new-tree))
	 #+SymScale
	 (let ((new-tree (make-relation-instance-tree)))
	   (if (compare-and-swap (relation-instances subject) nil new-tree)
	       (setf (get-relation-instance relation-name new-tree)
		     subject-instance-form)
	     ;; other threads has touched it first, ...
	     (let* ((old-tree (prog1 (relation-instances subject)
				(reclaim-relation-instances new-tree)))
		    (old-instance-form (get-relation-instance relation-name old-tree)))
	       (if old-instance-form
		   (progn ; and with the same relation ...
		     (reclaim-relation-instance subject-instance-form)
		     (setq subject-instance-form old-instance-form)
		     (let ((instance-items (relation-instance-items subject-instance-form)))
		       #+relation-instances-v2.0
		       (constant-queue-enqueue instance-items object)
		       #+relation-instances-v2.1
		       (setf (get-related-item object instance-items) object)))
		 (setf (get-relation-instance relation-name old-tree)
		       subject-instance-form))))))))

    ;; Add relation-instance to object unless (1) it is the subject and
    ;; (2) the relation is symmetric. 
    (when (or (neq item1 item2)
	      (not (relation-is-symmetric relation)))

      ;; If subject is object, then object-instances and object-instance-form
      ;; must be recomputed, because they were modified by adding instance
      ;; to subject in code above.
      (if (eq item1 item2)
	  (setq object-instances (relation-instances object)
		object-instance-form (if object-instances
					 (get-relation-instance other-name object-instances))))

      (cond
	(object-instance-form
	 #-relation-instances-v2
	 (nconc object-instance-form (slot-value-list subject))
	 #+relation-instances-v2
	 (let ((instance-items (relation-instance-items object-instance-form)))
	   #+relation-instances-v2.0
	   (constant-queue-enqueue instance-items subject)
	   #+relation-instances-v2.1
	   (setf (get-related-item subject instance-items) subject)))
	(t
	 (setq object-instance-form
	       #-relation-instances-v2
	       (slot-value-list other-name relation subject)
	       #+relation-instances-v2
	       (make-relation-instance other-name relation subject))
	 #-relation-instances-v2
	 (if object-instances
	     (nconc object-instances (slot-value-list object-instance-form))
	     (setf (relation-instances object)
		   (slot-value-list object-instance-form)))
	 #+relation-instances-v2
	 (if object-instances
	     (setf (get-relation-instance other-name object-instances)
		   object-instance-form)
	   #-SymScale
	   (setf (relation-instances object)
		 (let ((new-tree (make-relation-instance-tree)))
		   (setf (get-relation-instance other-name new-tree) object-instance-form)
		   new-tree))
	   #+SymScale
	   (let ((new-tree (make-relation-instance-tree)))
	     (if (compare-and-swap (relation-instances object) nil new-tree)
		 (setf (get-relation-instance other-name new-tree) object-instance-form)
	       ;; other threads has touched it first, ...
	       (let* ((old-tree (prog1 (relation-instances object)
				  (reclaim-relation-instances new-tree)))
		      (old-instance-form (get-relation-instance other-name old-tree)))
		 (if old-instance-form
		     (progn ; and with the same relation ...
		       (reclaim-relation-instance object-instance-form)
		       (setq object-instance-form old-instance-form)
		       (let ((instance-items (relation-instance-items object-instance-form)))
			 #+relation-instances-v2.0
			 (constant-queue-enqueue instance-items subject)
			 #+relation-instances-v2.1
			 (setf (get-related-item subject instance-items) subject)))
		   (setf (get-relation-instance other-name old-tree)
			 object-instance-form))))))))

      ;; Unless the inverse-name is the secret-name
      (when (and invoke-rules-for-relation-chaining?
		 (neq other-name (secret-inverse-name relation)))
	(invoke-rules-for-relation-chaining other-name subject object t)))

    (when invoke-rules-for-relation-chaining?
      (invoke-rules-for-relation-chaining relation-name object subject t)
      (update-subscriptions-from-virtual-attribute-change
	subject (virtual-attribute 'relationships) nil)
      (update-subscriptions-from-virtual-attribute-change
	object (virtual-attribute 'relationships) nil)
      (update-subscriptions-from-virtual-attribute-change
	relation (virtual-attribute 'items-in-this-relation) nil))

    nil))





;;; The function `uniqueness-message' either writes a level one warning message
;;; if called-from-procedure? is nil.  Otherwise, the warning message is not
;;; printed and the message text string is returned.  If the text string is
;;; returned, this needs to be reclaimed by the caller!

(defun uniqueness-message (relation-name given-name relation item1 item2 item-x
					 item-y called-from-procedure?)
  (let ((error-string
	  (twith-output-to-text-string
	    (tformat
	      "Because the relation ~a is ~a and ~NF is currently ~a ~NF, you ~
               cannot conclude that ~NF is ~a ~NF."
	      relation-name
	      (type-of-relation relation)
	      item-x
	      given-name
	      item-y
	      item1
	      given-name
	      item2))))
    (cond (called-from-procedure?
	   ;; this needs to be reclaimed by the caller!
	   error-string)
	  (t
	   (write-warning-message* 1 "~a" (twrite-string error-string))
	   (reclaim-text-string error-string))))) 



;;; The function `remove-from-relation' deletes the pair from the relation if it
;;; exists and has value t, otherwise has value nil.
;;;
;;; Since this function has been modified to print its own error messages
;;; (instead of printing from the action), a new called-from-procedure? argument
;;; has been added.  If this argument is non-nil, error messages are not
;;; printed.  In the case of an error, an error message string is created and
;;; returned (instead of nil).  This should be reclaimed by the caller.

;;; New arguments for version 4.0:
;;; 1. invoke-rules-for-relation-chaining? controls whether the relation change
;;; can invoke rules for chaining.
;;; 2. remove-given-name-direction-only? specifies that only the relation
;;; instance with the given name (i.e., the relation name, inverse name, or
;;; secret inverse name) will be removed and not the opposite direction.

;; The two new arguments added in version 4.0 were needed to allow runtime
;; changes to relation definitions.  - cpm, 3/8/94

(defun remove-from-relation (given-name item1 item2 called-from-procedure?
					invoke-rules-for-relation-chaining?
					remove-given-name-direction-only?)
  (note-change-to-runtime-data-for-block item1)
  (note-change-to-runtime-data-for-block item2)
  (let (subject-instances
	object-instances	 
	subject-instance-form
	object-instance-form
	other-name
	relation)
    (setq subject-instances (relation-instances item2))
    (when subject-instances
      (setq subject-instance-form (get-relation-instance given-name subject-instances))
      (when subject-instance-form
	(setq relation (relation-instance-relation subject-instance-form))))

    (unless (or (get-instance-with-name-if-any 'relation given-name)
		(and remove-given-name-direction-only?
		     relation
		     (or (eq (relation-name relation) given-name)
			 (eq (inverse-of-relation relation) given-name)
			 (eq (secret-inverse-name relation) given-name))))
      ;; Either no relation with this name or no relation with this inverse (for
      ;; remove-given-name-direction-only?).
      (let ((error-string
	      (tformat-text-string
		"There is no relation named ~a."
		given-name)))
	(if called-from-procedure?
	    ;; This string must be reclaimed by the caller!
	    (return-from remove-from-relation error-string)
	    (progn
	      (warning-message* 1 "~a" error-string)
	      (reclaim-text-string error-string)
	      (return-from remove-from-relation nil)))))

    (unless subject-instances		; Item2 has no relation instances
      (return-from remove-from-relation nil))
    (unless subject-instance-form	; Item2 has no instances of this relation
      (return-from remove-from-relation nil))

    #+relation-instances-v2.1
    (let* ((blocks (relation-instance-items subject-instance-form))
	   (found-item (get-related-item item1 blocks)))
      (when found-item
	(when invoke-rules-for-relation-chaining?
	  (invoke-rules-for-relation-chaining given-name item1 item2 nil))
	(setf (get-related-item item1 blocks) nil)
	(delete-related-item item1 blocks)
	;; Reclaim the entire subject-instance-form if item1 is solo.
	(when (related-items-is-empty-p blocks)
	  (setf (get-relation-instance given-name subject-instances) nil)
	  (delete-relation-instance given-name subject-instances)
	  (reclaim-relation-instance subject-instance-form)
	  (setq subject-instance-form nil))))

    #+relation-instances-v2.0
    (loop with blocks = (relation-instance-items subject-instance-form)
	  for queue-element = #+Lockfree-Deque (constant-queue-next
						 (constant-queue-head blocks) blocks)
			      #-Lockfree-Deque (constant-queue-head blocks)
			 then next-queue-element
	  until (or #+Lockfree-Deque (null queue-element)
		    #-Lockfree-Deque (eq queue-element blocks)
		    (eq (queue-datum queue-element) item1))
	  for next-queue-element = (constant-queue-next queue-element blocks)
	  finally
	    (if #+Lockfree-Deque (null queue-element)
	        #-Lockfree-Deque (eq queue-element blocks)
		(return-from remove-from-relation nil))

	    (when invoke-rules-for-relation-chaining?
	      (invoke-rules-for-relation-chaining given-name item1 item2 nil))

	    ;; Clip out the cons holding item1 if there are other items on list.
	    (constant-queue-delete queue-element blocks)

	    ;; Reclaim the entire subject-instance-form if item1 is solo.
	    (when (related-items-is-empty-p blocks)
	      (setf (get-relation-instance given-name subject-instances) nil)
	      (delete-relation-instance given-name subject-instances)
	      (reclaim-relation-instance subject-instance-form)
	      (setq subject-instance-form nil)))

    #-relation-instances-v2
    (loop for trailing-pointer =
	  (cdr subject-instance-form) then leading-pointer
	  for leading-pointer = (cdr-of-cons trailing-pointer)
	  for count from 0
	  until (or (null leading-pointer)
		    (eq (car-of-cons leading-pointer) item1))
	  finally
	    (if (null leading-pointer)	; Specific instance does not exist.
		(return-from remove-from-relation nil))

	    (when invoke-rules-for-relation-chaining?
	      (invoke-rules-for-relation-chaining given-name item1 item2 nil))

	    (cond
	      ;; Clip out the cons holding item1 if there are other items on list.
	      ((or (>f count 0) (cdr leading-pointer))
	       (setf (cdr trailing-pointer) (cdr leading-pointer))
	       (reclaim-slot-value-cons leading-pointer))

	      ;; Reclaim the entire subject-instance-form if item1 is solo.
	      (t
	       (loop for trailing-pointer-1 = nil then leading-pointer-1
		     for leading-pointer-1 = subject-instances
					   then (cdr-of-cons leading-pointer-1)
		     until (eq (car-of-cons leading-pointer-1)
			       subject-instance-form)
		     finally
		       (if (null trailing-pointer-1)
			   ;; Deleting the first sublist.
			   (setf (relation-instances item2) (cdr leading-pointer-1))
			   ;; Deleting any sublist after first one.
			   (setf (cdr trailing-pointer-1) (cdr leading-pointer-1)))
		       (reclaim-slot-value-list subject-instance-form)
		       (reclaim-slot-value-cons leading-pointer-1)))))

    (when (not remove-given-name-direction-only?)
      (setq other-name
	    (cond
	      ((relation-is-symmetric relation)
	       given-name)
	      ((eq given-name (relation-name relation))
	       (or (inverse-of-relation relation)
		   (secret-inverse-name relation)))
	      (t (relation-name relation))))

      (when (or (neq item1 item2) (neq given-name other-name))
	(when (and (symbol-package other-name)
		   invoke-rules-for-relation-chaining?)
	  (invoke-rules-for-relation-chaining other-name item2 item1 nil))

	(setq object-instances (relation-instances item1))
	(when object-instances
	  (setq object-instance-form (get-relation-instance other-name object-instances)))

	#+(and development (not no-misterious-checks-in-dev)) ;; (it happens frequently, why?)
	(unless object-instance-form
	  (cerror "continue" "Relation symmetry constraint violated."))

	#+relation-instances-v2.1
	(when object-instance-form
	  (let* ((blocks (relation-instance-items object-instance-form))
		 (found-item (get-related-item item2 blocks)))
	    (when found-item
	      (setf (get-related-item item2 blocks) nil)
	      (delete-related-item item2 blocks))
	    (when (related-items-is-empty-p blocks)
	      (setf (get-relation-instance other-name object-instances) nil)
	      (delete-relation-instance other-name object-instances)
	      (reclaim-relation-instance object-instance-form)
	      (setq object-instance-form nil))))

	#+relation-instances-v2.0
	(loop with blocks = (relation-instance-items object-instance-form)
	      for queue-element = #+Lockfree-Deque (constant-queue-next
						     (constant-queue-head blocks) blocks)
				  #-Lockfree-Deque (constant-queue-head blocks)
				then next-queue-element
	      until (or #+Lockfree-Deque (null queue-element)
			#-Lockfree-Deque (eq queue-element blocks)
			(eq (queue-datum queue-element) item2))
	      for next-queue-element = (constant-queue-next queue-element blocks)

	      finally
	        ;; Clip out the cons holding item2 if there are other items on list.
		(when #+Lockfree-Deque queue-element
		      #-Lockfree-Deque (neq queue-element blocks)
		  (constant-queue-delete queue-element blocks))

		;; Reclaim the entire object-instance-form if item2 is solo.
		(when (related-items-is-empty-p blocks)
		  (setf (get-relation-instance other-name object-instances) nil)
		  (delete-relation-instance other-name object-instances)
		  (reclaim-relation-instance object-instance-form)
		  (setq object-instance-form nil)))

	#-relation-instances-v2
	(loop for trailing-pointer-2 = (cdr-of-cons object-instance-form)
				     then leading-pointer-2
	      for leading-pointer-2 = (cdr-of-cons trailing-pointer-2)
	      for count from 0
	      until (eq (car-of-cons leading-pointer-2) item2)

	      finally
		(cond
		  ;; Clip out the cons holding item2 if there are other items on
		  ;; list.
		  ((or (> count 0) (cdr leading-pointer-2))
		   (setf (cdr trailing-pointer-2) (cdr leading-pointer-2))
		   (reclaim-slot-value-cons leading-pointer-2))

		  ;; Reclaim the entire object-instance-form if item2 is solo.
		  (t
		   (loop for trailing-pointer-3 = nil then leading-pointer-3
			 for leading-pointer-3 = object-instances
		           then (cdr-of-cons leading-pointer-3)
			 until (eq (car-of-cons leading-pointer-3)
				   object-instance-form)

			 finally
			   (if (null trailing-pointer-3)
			       ;; Deleting the first sublist.
			       (setf (relation-instances item1)
				     (cdr leading-pointer-3))
			       ;; Deleting sublist after first one.
			       (setf (cdr trailing-pointer-3)
				     (cdr leading-pointer-3)))

			   (reclaim-slot-value-list object-instance-form)
			   (reclaim-slot-value-cons leading-pointer-3)))))))

    (when invoke-rules-for-relation-chaining?
      (update-subscriptions-from-virtual-attribute-change
	item1 (virtual-attribute 'relationships) nil)
      (update-subscriptions-from-virtual-attribute-change
	item2 (virtual-attribute 'relationships) nil)
      (update-subscriptions-from-virtual-attribute-change
	relation (virtual-attribute 'items-in-this-relation) nil)))
  t)






;;;; Predicates for Relatedness




;;; is-related-macro is non-null if there is an instance of RELATION with either
;;; relation-name or inverse-of-relation being given-name and the instance in
;;; the appropriate position. I.e. (1) Given name is relation-name and item1 is
;;; subject and item2 is object. (2) Given-name is relation-name, relation is
;;; symmetric, and item1 is object and item2 is subject, or (3) given-name is
;;; inverse-of-relation, and item1 is object and item2 is subject.

(def-substitution-macro is-related-macro (given-name item1 item2)
  (when-let* ((relation-instances (relation-instances item2))
	      (relation-instance-form
	       (get-relation-instance given-name relation-instances)))
    (relation-exist-p item1 (relation-instance-items relation-instance-form))))



;;; Generic-is-related-macro is non-null if there is any instance of RELATION
;;; where item1 is subject and item2 is object, or item1 is object and item2 is
;;; subject.

(def-substitution-macro generic-is-related-macro (item1 item2)
  (when-let (relation-instances (relation-instances item2))
    (loop for relation-instance-form being each relation-instance of relation-instances
	  thereis (relation-exist-p item1 (relation-instance-items relation-instance-form)))))




;;;; Accessing Related Items

(defmacro related-items (item given-name)
  (let ((item-value (gensym))
	(relation-instances (gensym))
	(instance-form (gensym)))
    `(let ((,item-value ,item))
       (when-let* ((,relation-instances (relation-instances ,item-value))
		   (,instance-form (get-relation-instance ,given-name ,relation-instances)))
	 (relation-instance-items ,instance-form)))))

;; Note that if the representation changed, this could no longer be supported,
;; but at least one can track down all references and alter the access
;; accordingly.






;;;; Updating Existing Relation Instances




;;; Any relation instances need to be updated when there are changes to the
;;; name, inverse-name, first class, second class, type-of-relation, or
;;; relation-is-symmetric slots of the relation-definition.  This capability was
;;; added in version 4.0.  Now users can edit relation definitions at any time
;;; (G2 can be running, paused, or reset) and when there are existing relation
;;; instances.


;;; The following describes the updates required to relation-instances when the
;;; slots of the relation are edited.

;;; 1. Relation-name
;;; 1a. Add relation-name
;;;     No change.  No instances exist because there was no previous name.
;;; 1b. Remove relation-name (changing to NIL):
;;;     Execute cleanup for relation (remove all instances).
;;; 1c. Change relation name:
;;;     Map over OBJECT class and change the name.
;;;     If symmetric, also map SUBJECT;
;;;     else, if no inverse name, also map SUBJECT changing the secret-inverse

;;; 2. Inverse-name
;;;    Note, that the relation should not be symmetric if inverse-name is being
;;;    changed.
;;; 2a. Add inverse name
;;;     Map over SUBJECT class and replace the secret-inverse with the new
;;;    inverse name.
;;; 2b. Remove inverse name
;;;     Map over SUBJECT class and remove the inverse and replace with the
;;;    secret-inverse name.
;;; 2c. Change inverse-name
;;;     Map over SUBJECT class and change.

;;; 3. Subject class
;;;    Note that the class cannot be changed to NONE.
;;; 3a. Change SUBJECT class.
;;;     Map over OBJECT class and remove instances when SUBJECT(S) not in new
;;;   class.
;;;     NOTE: if the relation is symmetric, we cannot always determine from the
;;;     item's relation-instances, which is the subject and object.  So, check
;;;     both directions of the relation, as necessary, using the new-class and
;;;     the class corresponding to the other side of the relation.

;;; 4. Object class
;;;    Note that the class cannot be changed to NONE.
;;; 4a. Change object class
;;;     Map over SUBJECT class and remove instances when OBJECT(S) not in new
;;;   class.
;;;     NOTE: if the relation is symmetric, we cannot always determine from the
;;;     item's relation-instances, which is the subject and object.  So, check
;;;     both directions of the relation, as necessary, using the new-class and
;;;     the class corresponding to the other side of the relation.

;;; 5. Relation type
;;; 5a. one-to-one
;;;     Map over OBJECT class and check it's SUBJECTS for additional related
;;;   OBJECT.  If there are too may related items, delete all but one.
;;;     Map over SUBJECT class and check it's OBJECTS for additional related
;;;   SUBJECT.  If there are too may related items, delete all but one.
;;; 5b. one-to-many
;;;     Map over SUBJECT class and check it's OBJECTS for additional related
;;;   SUBJECT.  If there are too may related items, delete all but one.
;;; 5c. many-to-one
;;;     Map over OBJECT class and check it's SUBJECTS for additional related
;;;   OBJECT.  If there are too may related items, delete all but one.
;;; 5d. many-to-many
;;;     No change.

;;; 6. Relation is symmetric
;;; 6a. yes
;;;     Map over OBJECT class and add to SUBJECT.
;;; 6b. no
;;;     Map over SUBJECT class and remove.
;;;   NOTE: if the relation is symmetric, we cannot always determine from the
;;;   item's relation-instances, which is the subject and object.  So, when
;;;   that happens, check if both are of the object class.  If only one is, then
;;;   remove that relation instance.  Otherwise, remove one arbitrarily.



;; Oneness changes. Reject if not proper.
;; Class changes. Reject if not proper. Need old class.

;; Relation deleted: Remove all from both classes.

;; Object deleted. Remove all and symmetrical. Need the relation to get
;; the reverse name. Note that relational cleanups can be done on
;; any item in any order, but they may not be nested. 

;; Are there relations that can survive a reset? Howabout an option to do that.

;; What happens if deleting a relation that is a member of itself?
;; What happens if deleting a relation subordinate to a member of it, or
;; visa-versa?

;;; If the relation does not have an inversee name and is not-symmetric,
;;; 




;;; The variable `resolving-definitional-name-conflicts?' is temporarily bound
;;; in resolving-definitional-name conflicts, and currently effects code that
;;; deals only with relations.  (ghw 9/23/98)

(defvar resolving-definitional-name-conflicts? nil)



;;; The function `update-relation-instances-if-necessary' is used to update the
;;; relation instances when there has been a change to a user-editable slot of a
;;; relation definition.

;;; Note this function only updates those related items that are affected by
;;; this change.  It does not attempt to cancel or validate any procedure-
;;; invocations are rule-instances than are affected by the relation definition
;;; change.  It does not affect any relation role service that is being served.
;;; Role service continues to serve the old related values, until it's
;;; completed.

;;; This function should be called by the relevant slot-putters when there is a
;;; non-initializing change to the slot.  The change should have already been
;;; made before this function is called.

;;; Currently relation slots that can affect instances are:
;;;   relation-name
;;;   inverse-of-relation
;;;   class-of-subject
;;;   class-of-object
;;;   type-of-relation
;;;   relation-is-symmetric

(defun-void update-relation-instances-if-necessary
    (relation slot-name new-value old-value)
  ;; The resolution of definitional-name conflicts? deletes a later-loaded
  ;; relation frame with the same name as a previously-loaded relation frame.
  ;; This is done before relation frame references have been rendezvoused with
  ;; their frames.  Here we hold off updating any relation-instances because
  ;; the rendezvous code will remove relation-instances that are illegal vis-a-vis
  ;; the remaining relation-frame.  (ghw 9/23/98)
  (unless resolving-definitional-name-conflicts?
    (when (and (not (eq old-value new-value))
	       ;; Only named relations have instances.  Update only when there is
	       ;; a name or the change itself is to the relation name slot.
	       (or (relation-name relation) (eq slot-name 'relation-name)))
      (case slot-name
	(relation-name
	 (update-relation-name-for-relation-instances
	   relation new-value old-value))
	(inverse-of-relation
	 (update-relation-inverse-name-for-relation-instances
	   relation new-value old-value))
	(class-of-subject
	 (update-relation-subject-class-for-relation-instances
	   relation new-value old-value))
	(class-of-object
	 (update-relation-object-class-for-relation-instances
	   relation new-value old-value))
	(type-of-relation
	 (update-type-of-relation-for-relation-instances
	   relation new-value old-value))
	(relation-is-symmetric
	 (update-relation-is-symmetric-for-relation-instances
	   relation new-value old-value))
	(t
	 #+development
	 (cerror
	   "continue"
	   "Invalid slot name given to update-relation-instances-if-necessary.")
	 nil)))))

  ;; Note that the functions called in this function should be made more efficient
;; by not iterating over all items in G2!!  This is iteration is currently
;; necessary because relation-definitions do not record which items are related
;; to each other.  This information is kept on the related items.  There are
;; several ways to improve the efficiency of the update.  One is to keep a count
;; of the relation instances on a relation, so we know when not to do the
;; update.  - cpm, 3/1/94



;;; The function `update-relation-name-for-relation-instances' modifies any
;;; existing relations need to be updated or removed, given the change in
;;; relation name.

;;; Note that this function does not check if the new relation name is already
;;; the name of an existing relation.  This situation is prevented in the
;;; slot-value-compiler for relation-name?.

(defun-void update-relation-name-for-relation-instances
    (relation new-name old-name)
  (cond ((null old-name)
	 ;; Adding a name.  No existing relation instances because there is no
	 ;; old name.
	 nil)
	((null new-name)
	 ;; Removing a name.  The new name is NONE, so remove all relation
	 ;; instances.
	 (remove-all-relations-instances-for-relation relation old-name))
	(t
	 ;; Changing an existing name.  Update the name in the relation-
	 ;; instances of items.  Also, update the "subject" of the relation, if
	 ;; necessary.
	 (change-relation-name-or-inverse-for-relation-instances
	   relation new-name old-name nil))))



;;; The function `update-relation-inverse-name-for-relation-instances' modifies
;;; any existing relations when they need to be removed, added, or updated,
;;; given the change in relation inverse name.

;;; Note that this function does not check if the new inverse name is already
;;; the name of an existing relation.  This situation is prevented in the
;;; slot-value-compiler for the relation-name? grammar category.

(defun-void update-relation-inverse-name-for-relation-instances
    (relation new-inverse-name old-inverse-name)
  (cond ((null new-inverse-name)
	 ;; Removing an inverse name.  The new inverse name is NONE.  So, when
	 ;; there is an old, inverse name, replace it with the secret inverse
	 ;; name.
	 (when old-inverse-name
	   (change-relation-name-or-inverse-for-relation-instances
	     relation (secret-inverse-name relation) old-inverse-name t)))
	((null old-inverse-name)
	 ;; Adding an inverse name.  No old inverses exist, so replace the
	 ;; secret inverse name with the new inverse name.
	 (change-relation-name-or-inverse-for-relation-instances
	   relation new-inverse-name (secret-inverse-name relation) t))
	(t
	 ;; Changing an inverse name.  Iterate over the "subject class" of the
	 ;; relation.  Update the inverse name in the relation-instances of the
	 ;; items. But, don't need to update the "object class" of the relation
	 ;; because, when there is an inverse name, the relation cannot be
	 ;; symmetric.
	 (change-relation-name-or-inverse-for-relation-instances
	   relation new-inverse-name old-inverse-name t))))



;;; The function `change-relation-name-or-inverse-for-relation-instances' is
;;; used to modify the name or inverse name of existing relation instances.

;;; For non-inverse names: Update the relation name and, if there is no inverse
;;; and the relation is not symmetric, the secret-inverse-name.  Note that for
;;; symmetric relations, the corresponding symmetric relation instance is
;;; renamed during a separate pass over the "subject of relation" class.

;;; For inverse names: Only update the inverse or secret name.  (The relation
;;; cannot be symmetric if there is a new inverse-name.)  The new inverse name
;;; replaces either an existing inverse or secret inverse name.

;;; Note that the new name (and secret-inverse-name) or inverse name should have
;;; already been installed before this function is called.

(defun change-relation-name-or-inverse-for-relation-instances
    (relation new-name old-name new-name-is-inverse-p?)
  (let ((relation-is-symmetric-p? (relation-is-symmetric  relation)))
    ;; Modify the relation name and, possibly, the secret-inverse name.
    (loop for item being each class-instance of
	    (if (not new-name-is-inverse-p?)
		(class-of-object relation)
		(class-of-subject relation))
	  for relation-instances? = (relation-instances item)
	  with relation-has-inverse-p? = (inverse-of-relation relation)
	  with other-name? =  nil
	  when relation-instances?
	  do
      (loop for relation-instance-form being each relation-instance of relation-instances?
	    for relation-name-for-item =
	      (relation-instance-name relation-instance-form)
	    for relation-for-item =
	      (relation-instance-relation relation-instance-form)
	    do
	;; Set the new relation name, if the relation and old name match.
	(when (and (eq relation relation-for-item)
		   (eq relation-name-for-item old-name))
	  (#+(and SymScale relation-instances-v2) atomic-exchange
	   #-(and SymScale relation-instances-v2) setf
	   (relation-instance-name relation-instance-form) new-name)
	  (unless (or new-name-is-inverse-p?
		      relation-has-inverse-p?
		      relation-is-symmetric-p?)
	    (setq other-name? (secret-inverse-name relation))
	    ;; Modify the secret name of the "subjects" of the relation.
	    (loop for related-subject-item being each related-item of
		    (relation-instance-items relation-instance-form)
		  for subject-relation-instances? =
		    (relation-instances related-subject-item)
		  while subject-relation-instances?
		  do
	      (loop for subject-relation-instance-form being each relation-instance of
		      subject-relation-instances?
		    for subject-relation-name =
		      (relation-instance-name subject-relation-instance-form)
		    for subject-relation =
		      (relation-instance-relation subject-relation-instance-form)
		    do
		;; Set the name of the subject using the secret inverse name, if
		;; this is the correct relation and name.

		;; Note that it would be better to test for the old secret name,
		;; but the secret name has already been changed at this point.
		;; So, check that the name is not the old or new name.
		(when (and (eq relation subject-relation)
			   (not (or (eq subject-relation-name old-name)
				    (eq subject-relation-name new-name))))
		  #+(and SymScale relation-instances-v2)
		  (unless (compare-and-swap (relation-instance-name subject-relation-instance-form)
					    subject-relation-name other-name?)
		    (error "what?!"))
		  #-(and SymScale relation-instances-v2)
		  (setf (relation-instance-name subject-relation-instance-form)
			other-name?))))))))

    ;; Modify the name for any symmetric relation instances (search over the
    ;; "subject" class of the relation).
    (unless (and (not new-name-is-inverse-p?) relation-is-symmetric-p?)
      (return-from change-relation-name-or-inverse-for-relation-instances))

    (loop for item being each class-instance of (class-of-subject relation)
	  for relation-instances? = (relation-instances item)
	  when relation-instances?
	  do
      (loop for relation-instance-form being each relation-instance of relation-instances?
	    for relation-name-for-item =
	      (relation-instance-name relation-instance-form)
	    for relation-for-item =
	      (relation-instance-relation relation-instance-form)
	    do
	;; Set the new relation name, if the relation and old name match.
	(when (and (eq relation relation-for-item)
		   (eq relation-name-for-item old-name))
	  #+(and SymScale relation-instances-v2)
	  (unless (compare-and-swap (relation-instance-name relation-instance-form)
				    relation-name-for-item new-name)
	    (error "what?!"))
	  #-(and SymScale relation-instances-v2)
	  (setf (relation-instance-name relation-instance-form) new-name))))))

;; NOTE for non-inverse name change, when there is a symmetric relation:
;;
;; It was difficult to also modify the name of the symmetric relation, during
;; the first pass (the pass over the "object of the relation").  One cannot
;; distinguish between the symmetric relation and the original relation.  In
;; fact, a relation-instance form of a relation definition may contain both.  If
;; it is the original relation, then it's symmetric relation instance also needs
;; to be modified.  These complications are more understandable when looking at
;; a graph of possible relations between items.  So, for now, when modifying a
;; symmetric relation, I will make two passes, over the "object" and "subject"
;; classes of the relation.  - cpm, 3/4/94



;;; The function `update-relation-subject-class-for-relation-instances' is used
;;; to verify the existing relation instances with the new subject of relation
;;; class.  Any related items (subjects of the relation) that are not of the
;;; correct class are removed.

(defun update-relation-subject-class-for-relation-instances
    (relation new-subject-class old-subject-class)
  (when (and (not (eq new-subject-class 'item))
	     (not (eq new-subject-class old-subject-class))
	     ;; Check if the new class is either not defined (and the old class
	     ;; was defined), is more restrictive than the old class, or is
	     ;; disjoint for the old class.
	     (or (and (not (classp new-subject-class))
		      (classp old-subject-class))
		 (not (subclassp old-subject-class new-subject-class))))
    ;; The new class is more restrictive than the old one.  So, remove any
    ;; relation instances (both subjects and object) when the "subject of the
    ;; relation" conflicts with the new class.
    (change-subject-or-object-class-for-relation-instances
     relation new-subject-class old-subject-class t)))



;;; The function `update-relation-object-class-for-relation-instances' is used
;;; to verify the existing relation instances with the new object of relation
;;; class.  Any related items (objects of the relation) that are not of the
;;; correct class are removed.

(defun update-relation-object-class-for-relation-instances
    (relation new-object-class old-object-class)
  (when (and (not (eq new-object-class 'item))
	     (not (eq new-object-class old-object-class))
	     ;; Check if the new class is either not defined (and the old class
	     ;; was defined), is more restrictive than the old class, or is
	     ;; disjoint for the old class.
	     (or (and (not (classp new-object-class))
		      (classp old-object-class))
		 (not (subclassp old-object-class new-object-class))))
    ;; The new class is more restrictive than the old one.  So, remove any
    ;; relation instances (both objects and subject) when the "object of the
    ;; relation" conflicts with the new class.
    (change-subject-or-object-class-for-relation-instances
     relation new-object-class old-object-class nil)))



;;; The function `change-subject-or-object-class-for-relation-instances' is used
;;; to update the given relation instances based on the new class (a first-class
;;; or second-class) of the relation.

;;; If the relation's first-class is the new class, the "subject" of the
;;; relation will be tested to be of this class. (To indicate this, specify
;;; non-NIL for the new-class-for-subject-p?  argument.)  Or, if the relation's
;;; second-class is the new class, the "object" of the relation will be tested
;;; to be of this class.  (To indicate this, specify NIL for the new-class-
;;; for-subject-p? argument.)

;;; The relations are update in the following ways:
;;;
;;; 1. For non-symmetric relations, if the above constraints are not met for the
;;; new class, then the relation instance and it's inverse (named inverse or
;;; secret inverse) are both removed.  The relation instance no longer exists
;;; between the subject and object in either direction.
;;;
;;; 2. For symmetric relations, where the subject and object cannot be
;;; distinguished (i.e, they both fit the subject and object classes), test
;;; both.  If only one conflicts with the new class, but the classes don't
;;; conflict when reversing subject and object, then keep the relation.
;;; Otherwise, remove both relation instances.  If both conflict with the new
;;; class, then the relation instance is removed for both.
;;;
;;; 3. For symmetric relations that can distinguish the subject and object,
;;; follow the non-symmetric case.  If there is a conflict with the new class,
;;; both diretions of the relation instance are removed.

;;; Note that the new first or second class should have already been installed
;;; before this function is called.

;;; Note that when any conflicting relation instances are removed, this does
;;; invoke rules for chaining.

;;; Note that the new-class argument is the name of the classed used to validate
;;; the subject or object of the relation.  (The new-class-for-subject-p?
;;; argument controles whether the relation subject or object is validated.)
;;; The iteration-class argument controls which items are tested for this
;;; relation.  For example, if you want to change all tanks in the
;;; tank-relation, pass tank for this.  If you want to change a subset of tanks,
;;; you could pass, for example water-tank.

(defun change-subject-or-object-class-for-relation-instances
    (relation new-class iteration-class new-class-for-subject-p?)
  (let ((relation-is-symmetric-p? (relation-is-symmetric relation))
	(relation-name (relation-name  relation))
	;; The inverse relation instance is on the subject item.
	(check-inverse-first-p? new-class-for-subject-p?))
    (loop for item being each class-instance of iteration-class
	  for relation-instances? = (relation-instances item)
	  for invalid-item-class-p? = nil
	  do
      (when relation-instances?
	#+relation-instances-v2
	(loop for relation-instance-form being each relation-instance of relation-instances?
	      for relation-name-for-item = (relation-instance-name relation-instance-form)
	      for relation-for-item = (relation-instance-relation relation-instance-form)
	      do
	  (when (and (eq relation relation-for-item)
		     ;; Also, test for the correct relation instance.
		     (if (or (not check-inverse-first-p?)
			     relation-is-symmetric-p?)
			 (eq relation-name relation-name-for-item)
			 (not (eq relation-name relation-name-for-item))))
	    (unless (frame-of-class-p item new-class)
	      (setq invalid-item-class-p? t))
	    ;; If the item is not of the correct class.  Remove the relation
	    ;; from both the subject and object of the relation.  For symmetric
	    ;; relations, always check both items.  In that case, we cannot
	    ;; always distinguish the subject and object.
	    (when (or invalid-item-class-p? relation-is-symmetric-p?)
	      ;; Check the items on the opposite side of the relation.

	      #+relation-instances-v2.1
	      (loop with instance-items = (relation-instance-items relation-instance-form)
		    for related-inverse-item being each related-item of instance-items
		    for error-string? = nil
		    for invalid-reverse-item-class-p? = nil
		    for remove-this-relation-instance-p? =
		      (and invalid-item-class-p? (not relation-is-symmetric-p?))
		    with other-class = (if new-class-for-subject-p?
					   (class-of-object relation)
					   (class-of-subject relation))
		    do
		(unless remove-this-relation-instance-p?
		  (when relation-is-symmetric-p?
		    ;; Need to check both items of the symmetric relation,
		    ;; even if the first item was of the correct class.  We
		    ;; may be testing the wrong side of the relation.
		    (setq invalid-reverse-item-class-p?
			  (not (frame-of-class-p
				 related-inverse-item other-class)))
		    (setq remove-this-relation-instance-p?
			  (and (or invalid-item-class-p?
				   invalid-reverse-item-class-p?)
			       ;; Try the other direction of the relation.
			       (or (not (frame-of-class-p item other-class))
				   (not (frame-of-class-p
					  related-inverse-item new-class)))))))
		(when remove-this-relation-instance-p?
		  ;; Remove both sides of the relation, invoking any rules for
		  ;; chaining.
		  (setq error-string?
			(if (not check-inverse-first-p?)
			    ;; item is the "relation object".
			    (remove-from-relation
			      relation-name related-inverse-item item t t nil)
			    ;; item is the "relation subject".
			    (remove-from-relation
			      relation-name item related-inverse-item t t nil)))
		  (when (text-string-p error-string?)
		    #+development
		    (cerror "continue" "Error while remove relation because of conflict with new class.")
		    (reclaim-text-string error-string?))))

	      #+relation-instances-v2.0
	      (loop with queue = (relation-instance-items relation-instance-form)
		    for queue-element = #+Lockfree-Deque (constant-queue-next
							   (constant-queue-head queue) queue)
					#-Lockfree-Deque (constant-queue-head queue)
				   then next-queue-element
		    until #+Lockfree-Deque (null queue-element)
		          #-Lockfree-Deque (eq queue-element queue)
		    for next-queue-element = (constant-queue-next queue-element queue)
		    for related-inverse-item = (queue-datum queue-element)
		    for error-string? = nil
		    for invalid-reverse-item-class-p? = nil
		    for remove-this-relation-instance-p? =
		      (and invalid-item-class-p? (not relation-is-symmetric-p?))
		    with other-class = (if new-class-for-subject-p?
					   (class-of-object relation)
					   (class-of-subject relation))
		    do
		(unless remove-this-relation-instance-p?
		  (when relation-is-symmetric-p?
		    ;; Need to check both items of the symmetric relation,
		    ;; even if the first item was of the correct class.  We
		    ;; may be testing the wrong side of the relation.
		    (setq invalid-reverse-item-class-p?
			  (not (frame-of-class-p
				 related-inverse-item other-class)))
		    (setq remove-this-relation-instance-p?
			  (and (or invalid-item-class-p?
				   invalid-reverse-item-class-p?)
			       ;; Try the other direction of the relation.
			       (or (not (frame-of-class-p item other-class))
				   (not (frame-of-class-p
					  related-inverse-item new-class)))))))
		(when remove-this-relation-instance-p?
		  ;; Remove both sides of the relation, invoking any rules for
		  ;; chaining.
		  (setq error-string?
			(if (not check-inverse-first-p?)
			    ;; item is the "relation object".
			    (remove-from-relation
			      relation-name related-inverse-item item t t nil)
			    ;; item is the "relation subject".
			    (remove-from-relation
			      relation-name item related-inverse-item t t nil)))
		  (when (text-string-p error-string?)
		    #+development
		    (cerror "continue" "Error while remove relation because of conflict with new class.")
		    (reclaim-text-string error-string?))))))
	  ;; (eq relation relation-for-item) should only hit once.
	  (return))

	#-relation-instances-v2
	(loop for relation-instance-form =
	        (car-of-cons relation-instances?) then
	        (and rest-of-relation-instance-list?
		     (car-of-cons rest-of-relation-instance-list?))
	      ;; See note at the end of the function regarding the trailing
	      ;; pointer variable.
	      for rest-of-relation-instance-list? =
	        (cdr-of-cons relation-instances?)
	        then (cdr rest-of-relation-instance-list?)
	      for relation-name-for-item = (relation-instance-name relation-instance-form)
	      for relation-for-item = (relation-instance-relation relation-instance-form)
	      do
	  (when (and (eq relation relation-for-item)
		     ;; Also, test for the correct relation instance.
		     (if (or (not check-inverse-first-p?)
			     relation-is-symmetric-p?)
			 (eq relation-name relation-name-for-item)
			 (not (eq relation-name relation-name-for-item))))
	    (unless (frame-of-class-p item new-class)
	      (setq invalid-item-class-p? t))
	    ;; If the item is not of the correct class.  Remove the relation
	    ;; from both the subject and object of the relation.  For symmetric
	    ;; relations, always check both items.  In that case, we cannot
	    ;; always distinguish the subject and object.
	    (when (or invalid-item-class-p? relation-is-symmetric-p?)
	      ;; Check the items on the opposite side of the relation.
	      (loop with relation-instance-item-list =
		    (relation-instance-items relation-instance-form)
		    for related-inverse-item =
		    (car-of-cons relation-instance-item-list) then
		    (and rest-of-relation-instance-item-list
			 (car-of-cons rest-of-relation-instance-item-list))
		    ;; See note at the end of the function regarding the
		    ;; trailing pointer variable.
		    for rest-of-relation-instance-item-list =
		    (cdr-of-cons relation-instance-item-list) then
		    (cdr-of-cons rest-of-relation-instance-item-list)
		    for error-string? = nil
		    for invalid-reverse-item-class-p? = nil
		    for remove-this-relation-instance-p? =
		    (and invalid-item-class-p? (not relation-is-symmetric-p?))
		    with other-class = (if new-class-for-subject-p?
					   (class-of-object relation)
					   (class-of-subject relation))
		    do
		(unless remove-this-relation-instance-p?
		  (when relation-is-symmetric-p?
		    ;; Need to check both items of the symmetric relation,
		    ;; even if the first item was of the correct class.  We
		    ;; may be testing the wrong side of the relation.
		    (setq invalid-reverse-item-class-p?
			  (not (frame-of-class-p
				 related-inverse-item other-class)))
		    (setq remove-this-relation-instance-p?
			  (and (or invalid-item-class-p?
				   invalid-reverse-item-class-p?)
			       ;; Try the other direction of the relation.
			       (or (not (frame-of-class-p item other-class))
				   (not (frame-of-class-p
					  related-inverse-item new-class)))))))
		(when remove-this-relation-instance-p?
		  ;; Remove both sides of the relation, invoking any rules for
		  ;; chaining.
		  (setq error-string?
			(if (not check-inverse-first-p?)
			    ;; item is the "relation object".
			    (remove-from-relation
			      relation-name related-inverse-item item t t nil)
			    ;; item is the "relation subject".
			    (remove-from-relation
			      relation-name item related-inverse-item t t nil)))
		  (when (text-string-p error-string?)
		    #+development
		    (cerror "continue" "Error while remove relation because of conflict with new class.")
		    (reclaim-text-string error-string?)))
		;; Test for last of related items.
		    until (null rest-of-relation-instance-item-list))))
	  ;; Test for last of relation-instances.
	      until (null rest-of-relation-instance-list?))))))

;; Note that the above LOOPS use a trailing pointer to access the elements of a
;; list.  This is needed because the contents of the list may change as it is
;; being iterated over.  The CONS holding the current element will be removed if
;; remove-from-relation is called from within the loop.  It happens that "just"
;; iterating over the elements with "LOOP for x in <list>", currently works,
;; because the LOOP iteration saves the CDR before doing the iteration.  But, I
;; don't want to rely on this particular side effect of LOOP.  - cpm, 3/10/94



;;; The function `update-type-of-relation-for-relation-instances' is used
;;; to verify the existing relation instances for the new type of relation.

;;; This function removes relations that violate the new relation type.  For
;;; example, if the relation is now "one to one", all but one related instances
;;; are removed to enforce this.  The relation instance that remains is chosen
;;; arbitrarly from among the existing relation instances.  We do not guarantee
;;; which of the instances will remain.

;;; Note that symmetric relations with non-disjoint subject and object classes
;;; are a special class.  This case requires more testing to distinguish between
;;; the subject and object.  If they cannot be distinguished and one needs to be
;;; removed, one is selected arbitrarily.

;;; Note that when any conflicting relation instances are removed, this does
;;; invoke rules for chaining.

(defun update-type-of-relation-for-relation-instances
    (relation new-type-of-relation old-type-of-relation)
  (let* ((relation-name (relation-name relation))
	 (relation-is-symmetric-p? (relation-is-symmetric relation))
	 (subject-class (class-of-subject relation))
	 (object-class (class-of-object relation))
	 (disjoint-classes-p? (not (or (subclassp subject-class object-class)
				       (subclassp object-class subject-class))))
	 (unique-forward? nil)
	 (unique-reverse? nil)
	 (previously-unique-forward? nil)
	 (previously-unique-reverse? nil))
    (case old-type-of-relation
      (one-to-one
       (setq previously-unique-forward? t)
       (setq previously-unique-reverse? t))
      (one-to-many
       (setq previously-unique-forward? t))
      (many-to-one
       (setq previously-unique-reverse? t)))
    (case new-type-of-relation
      (one-to-one
       (setq unique-forward? t)
       (setq unique-reverse? t))
      (one-to-many
       (setq unique-forward? t))
      (many-to-one
       (setq unique-reverse? t)))
    (unless (or (and (null previously-unique-forward?) unique-forward?)
		(and (null previously-unique-reverse?) unique-reverse?))
      ;; No update is needed.  The new relation-type is not more restrictive
      ;; than the old type.
      (return-from update-type-of-relation-for-relation-instances))
    (loop with test-forward? = unique-forward?
	  with test-reverse? = unique-reverse?
	  until (and (null test-forward?) (null test-reverse?))
	  do
      ;; Note that unique-forward is tested first, if necessary, and then
      ;; unique-reverse, if necessary.
      (loop for item being each class-instance of
	    (if test-forward?
		(class-of-object relation)
		(class-of-subject relation))
	    for relation-instances? = (relation-instances item)
	    for item-can-be-subject-and-object-p? =
	    ;; Test opposite class.
	    (frame-of-class-p
	      item (if test-forward? subject-class object-class))
	    do
	(when relation-instances?
	  #+relation-instances-v2.1
	  (loop for relation-instance-form being each relation-instance
					   of relation-instances?
		for relation-name-for-item =
		  (relation-instance-name relation-instance-form)
		for relation-for-item =
		  (relation-instance-relation relation-instance-form)
		for tree = (relation-instance-items relation-instance-form)
		for first-item? = (first-related-item tree)
		do
	    (when (and (eq relation relation-for-item)
		       (if (or test-forward? relation-is-symmetric-p?)
			   (eq relation-name relation-name-for-item)
			   ;; Checking for an inverse or secret-inverse name.
			   (not (eq relation-name relation-name-for-item)))
		       ;; Only enter the loop if there are more than one item in
		       ;; the relation-instance-item-list.
		       (more-than-one-related-item-p tree))
	      ;; Start from the second item.
	      (loop for item2 being each related-item of tree
		    when (neq item2 first-item?) do
		(let* ((item2-is-subject-of-symmetric-relation-p?
			(and relation-is-symmetric-p?
			     (if (or disjoint-classes-p?
				     (not item-can-be-subject-and-object-p?))
				 ;; The first item cannot be subject and object.
				 ;; So, Item2 is Subject, if testing forward;
				 ;; otherwise, it is Object.
				 test-forward?
			      ;; The first item can be both subject or object.
			      ;; So, there are two possibilities: item2 can
			      ;; only be the subject; or item and item2 can be
			      ;; both subject and object.  In these cases,
			      ;; choose item2 as the subject.
			      (frame-of-class-p item2 subject-class))))
		       (error-string?
			(if (or item2-is-subject-of-symmetric-relation-p?
				(and test-forward?
				     (not relation-is-symmetric-p?)))
			    ;; Item2 is the subject, item is the object.
			    (remove-from-relation
			      relation-name item2 item t t nil)
			  ;; Item is the subject, item2 is the object.
			  (remove-from-relation
			    relation-name item item2 t t nil))))
		  (when (and error-string? (text-string-p error-string?))
		    (reclaim-text-string error-string?))))))

	  #+relation-instances-v2.0
	  (loop for relation-instance-form being each relation-instance
					   of relation-instances?
		for relation-name-for-item =
		  (relation-instance-name relation-instance-form)
		for relation-for-item =
		  (relation-instance-relation relation-instance-form)
		for queue = (relation-instance-items relation-instance-form)
		for first-item? = #+Lockfree-Deque (constant-queue-next
						     (constant-queue-head queue) queue)
				  #-Lockfree-Deque (constant-queue-head queue)
		do
	    (when (and (eq relation relation-for-item)
		       (if (or test-forward? relation-is-symmetric-p?)
			   (eq relation-name relation-name-for-item)
			   ;; Checking for an inverse or secret-inverse name.
			   (not (eq relation-name relation-name-for-item)))
		       ;; Only enter the loop if there are more than one item in
		       ;; the relation-instance-item-list.
		       (and first-item?
			    #+Lockfree-Deque (constant-queue-next first-item? queue)
			    #-Lockfree-Deque (neq (queue-next-element first-item?) queue)))
	      ;; Start from the second item.
	      (loop for queue-element = (constant-queue-next first-item? queue)
				      then next-queue-element
		    until #+Lockfree-Deque (null queue-element)
			  #-Lockfree-Deque (eq queue-element queue)
		    for next-queue-element = (constant-queue-next queue-element queue)
		    for item2 = (queue-datum queue-element)
		    for item2-is-subject-of-symmetric-relation-p? =
		      (and relation-is-symmetric-p?
			   (if (or disjoint-classes-p?
				   (not item-can-be-subject-and-object-p?))
			       ;; The first item cannot be subject and object.
			       ;; So, Item2 is Subject, if testing forward;
			       ;; otherwise, it is Object.
			       test-forward?
			       ;; The first item can be both subject or object.
			       ;; So, there are two possibilities: item2 can
			       ;; only be the subject; or item and item2 can be
			       ;; both subject and object.  In these cases,
			       ;; choose item2 as the subject.
			       (frame-of-class-p item2 subject-class)))
		    for error-string? =
		      (if (or item2-is-subject-of-symmetric-relation-p?
			      (and test-forward?
				   (not relation-is-symmetric-p?)))
			  ;; Item2 is the subject, item is the object.
			  (remove-from-relation
			    relation-name item2 item t t nil)
			  ;; Item is the subject, item2 is the object.
			  (remove-from-relation
			    relation-name item item2 t t nil))
		    do
		(when (and error-string? (text-string-p error-string?))
		  (reclaim-text-string error-string?)))))

	  #-relation-instances-v2
	  (loop for relation-instance-form =
	          (car-of-cons relation-instances?) then
	          (and rest-of-relation-instance-list?
		       (car-of-cons rest-of-relation-instance-list?))
		;; See note at the end of the function regarding the trailing
		;; pointer variable.
		for rest-of-relation-instance-list? =
	          (cdr-of-cons relation-instances?) then
	          (cdr rest-of-relation-instance-list?)
		;; Additional trailing pointers (of the trailing pointer)
		for cdr-of-rest-of-relation-instance-list? =
	          (cdr rest-of-relation-instance-list?)
		for cddr-of-rest-of-relation-instance-list? =
	          (cddr rest-of-relation-instance-list?)

		with relation-name-for-item = nil
		with relation-for-item = nil
		do
	    (setq relation-name-for-item (car-of-cons relation-instance-form))
	    (setq relation-for-item
		  (car-of-cons (cdr-of-cons relation-instance-form)))
	    (when (and (eq relation relation-for-item)
		       (if (or test-forward? relation-is-symmetric-p?)
			   (eq relation-name relation-name-for-item)
			   ;; Checking for an inverse or secret-inverse name.
			   (not (eq relation-name relation-name-for-item)))
		       ;; Only enter the loop if there are more than one item in
		       ;; the relation-instance-item-list.
		       (cdr-of-cons
			 (cdr-of-cons (cdr-of-cons relation-instance-form))))
	      (loop with relation-instance-item-list =
		    ;; Remove all related items, but one.  Start from the second
		    ;; item.
		    (cdr-of-cons
		      (cdr-of-cons (cdr-of-cons relation-instance-form)))
		    for item2 = (car-of-cons relation-instance-item-list)
			      then (and rest-of-relation-instance-item-list
					(car-of-cons
					  rest-of-relation-instance-item-list))
		    ;; See note at the end of the function regarding the
		    ;; trailing pointer variable.
		    for rest-of-relation-instance-item-list =
		      (cdr-of-cons relation-instance-item-list) then
		      (cdr-of-cons rest-of-relation-instance-item-list)
		    for item2-is-subject-of-symmetric-relation-p? =
		      (and relation-is-symmetric-p?
			   (if (or disjoint-classes-p?
				   (not item-can-be-subject-and-object-p?))
			       ;; The first item cannot be subject and object.
			       ;; So, Item2 is Subject, if testing forward;
			       ;; otherwise, it is Object.
			       test-forward?
			       ;; The first item can be both subject or object.
			       ;; So, there are two possibilities: item2 can
			       ;; only be the subject; or item and item2 can be
			       ;; both subject and object.  In these cases,
			       ;; choose item2 as the subject.
			       (frame-of-class-p item2 subject-class)))
		    for error-string? =
		      (if (or item2-is-subject-of-symmetric-relation-p?
			      (and test-forward?
				   (not relation-is-symmetric-p?)))
			  ;; Item2 is the subject, item is the object.
			  (remove-from-relation
			    relation-name item2 item t t nil)
			  ;; Item is the subject, item2 is the object.
			  (remove-from-relation
			    relation-name item item2 t t nil))
		    do
		(when (and error-string? (text-string-p error-string?))
		  (reclaim-text-string error-string?))
		;; Test for last of related items.
		    until (null rest-of-relation-instance-item-list)))

	    ;; IMPORTANT test: Need to check if the value after the current
	    ;; value was removed as a side-effect of remove-from-relation.
	    ;; (This trailing pointer itself is needed at the top of the loop in
	    ;; case the cons holding the current value is removed.  But, in some
	    ;; special cases, such as when removing an item that is related to
	    ;; itself, this trailing point could have been reclaimed.)  - cpm,
	    ;; 10/25/96
	    (when (and (not (eq (cdr rest-of-relation-instance-list?)
				cdr-of-rest-of-relation-instance-list?))
		       (eq (cdr cdr-of-rest-of-relation-instance-list?)
				cddr-of-rest-of-relation-instance-list?))
	      ;; The second element (car of the rest of list) was reclaimed, if
	      ;; the second cons does not point to the third and if the third
	      ;; does point to the fourth.  (This verifies that the second, and
	      ;; not the third, was reclaimed.)
	      (setq rest-of-relation-instance-list?
		    cdr-of-rest-of-relation-instance-list?))

	    ;; Test for last of relation-instances.
		until (null rest-of-relation-instance-list?))))
      ;; If both tests are necessary, test forward first and then reverse.
      (if test-forward?
	  (setq test-forward? nil)
	  (if test-reverse?
	      (setq test-reverse? nil))))))

;; An alternative of the above function design was to remove all relation
;; instances when the instances violated the new relation type.  We decided on
;; leaving one relation instance, chosen arbitrarily, to fit the new relation
;; type, when necessary.  - cpm, 3/3/94

;; Note that the above LOOPS use a trailing pointer to access the elements of a
;; list.  This is needed because the contents of the list may change as it is
;; being iterated over.  The CONS holding the current element will be removed if
;; remove-from-relation is called from within the loop.  It happens that "just"
;; iterating over the elements with "LOOP for x in <list>", currently works,
;; because the LOOP iteration saves the CDR before doing the iteration.  But, I
;; don't want to rely on this particular side effect of LOOP.  - cpm, 3/10/94



;;; The function `update-relation-is-symmetric-for-relation-instances' is used
;;; to update the existing relation instances for the new "relation is
;;; symmetric" attribute value.

;;; If the relation is no longer symmetric, all symmetric inverses are removed.
;;; If the relation is newly symmetric, add the symmetric inverse.

;;; Note that relation chaining is invoked, when necessary, based on the type of
;;; relation.  For newly symmetric relations, chaining is only invoked for the
;;; relation instance that is being added.  For newly non-symmetric relations,
;;; chaining is only invoked for the relation instance that is being removed.

(defun update-relation-is-symmetric-for-relation-instances
    (relation new-symmetric-flag old-symmetric-flag)
  (when (not (eq old-symmetric-flag new-symmetric-flag))
    (let ((relation-name (relation-name relation))
	  (new-related-items-list? nil))
      (when (or (and new-symmetric-flag (not (inverse-of-relation relation)))
		(null new-symmetric-flag))
	;;   If Newly SYMMETRIC, there must not have a named inverse.  Iterate
	;; over the "relation object" class and ADD to the relation instances
	;; for the "relation subject" (i.e., the symmetric inverse).
	;;   If Newly NON-SYMMETRIC.  Iterate over the "relation subject" class
	;; and REMOVE the symmetric inverse.  If the subject and object cannot
	;; be distinguished, choose one for removal arbitrarily.
	(loop with relation-object-class = (class-of-object relation)
	      with relation-subject-class = (class-of-subject relation)
	      for item being each class-instance of
	        (if new-symmetric-flag
		    relation-object-class
		    relation-subject-class)
	      for relation-instances? = (relation-instances item)
	      for copy-of-relation-instances? =
	        (copy-list-of-relation-instances relation-instances?)
	      do
	  (loop for relation-instance-form in copy-of-relation-instances?
		for relation-name-for-item =
		  (car-of-cons relation-instance-form)
		for relation-for-item =
		  (car-of-cons (cdr-of-cons relation-instance-form))
		for error-string? = nil
		with relation-subject = nil
		with relation-object = nil
		do
	    (when (and (eq relation relation-for-item)
		       (eq relation-name-for-item relation-name))
	      (loop for item2 in
		      (cdr-of-cons (cdr-of-cons relation-instance-form))
		    do
		;; First, remove the inverse of the relation and then the
		;; forward relation.  Note that the subject and object removals
		;; are done separately because the relation already has its
		;; symmetric slot set to its new value.  Therefore, removing
		;; both the subject and object at once would not delete the
		;; correct inverse (i.e.g, secret-inverse for the former
		;; non-symmetric and symmetric-inverse for the former
		;; symmetric.)
					; This could be optimized by only
					; deleting in one direction and then
					; only adding the relation in one
					; direction (the symmetric relation for
					; newly symmetric and secret-inverse for
					; newly non-symmetric).  But, currently
					; add-to-relation cannot add a relation
					; instance in only one direction.  -
					; cpm, 3/8/94
		(cond (new-symmetric-flag
		       (setq relation-subject item2)
		       (setq relation-object item))
		      ((frame-of-class-p item2 relation-object-class)
		       ;; For newly non-symmetric relation.  
		       ;;   Choose this order of subject and object, since the
		       ;; classes match.  The opposite order may also be true,
		       ;; but choose this one arbitrarily.
		       (setq relation-subject item)
		       (setq relation-object item2))
		      (t
		       (setq relation-subject item2)
		       (setq relation-object item)))
		(setq error-string?
		      (if new-symmetric-flag
			  ;; Remove the secret inverse, but don't trigger any
			  ;; relation chaining.
			  (remove-from-relation
			    (secret-inverse-name relation)
			    relation-object relation-subject t nil t)
			  ;; Remove one side of the symmetric relation and
			  ;; trigger any relation chaining.
			  (remove-from-relation
			    relation-name relation-object relation-subject t t
			    t)))
		(when (and error-string? (text-string-p error-string?))
		  (reclaim-text-string error-string?))
		(setq error-string?
		      ;; Remove the other direction of the relation instance,
		      ;; but do not trigger any relation chaining.
		      (remove-from-relation
			relation-name relation-subject relation-object t nil t))
		(when (and error-string? (text-string-p error-string?))
		  (reclaim-text-string error-string?))
		;; Save information so that the relation can be added below.
		(let ((relation-triplet-form
			(gensym-list
			  (gensym-list
			    relation-name relation-subject relation-object))))
		  (setq new-related-items-list?
			(if new-related-items-list?
			    (nconc
			      new-related-items-list? relation-triplet-form)
			    relation-triplet-form))))))
	      finally (reclaim-slot-value-tree copy-of-relation-instances?))
	(loop for (relation-name relation-subject relation-object)
		  in new-related-items-list?
	      for error-string? = nil
	      do
		;; Add the new relation in both directions.  Don't invoke any
		;; relation chaining here.  Chaining is done, when necessary,
		;; above in REMOVE-FROM-RELATION and below in
		;; INVOKE-RULES-FOR-RELATION-CHAINING.

		;; Note that the relations are added here after all the
		;; necessary relations have been removed above.  They cannot be
		;; added in the loops that do the removal because this could
		;; confuse that process.  The newly added relations could
		;; mistakenly be removed, possibly infinitely.
                (setq error-string?
                      (add-to-relation
                        relation-name relation-subject relation-object nil t nil))
		(cond
		  ((null error-string?)
		   (when new-symmetric-flag
		     ;; Only invoke relation chaining, for a newly symmetric
		     ;; relation, for the direction of the relation that is being
		     ;; newly added.
		     (invoke-rules-for-relation-chaining
		       relation-name relation-object relation-subject t)
		     (update-subscriptions-from-virtual-attribute-change
		       relation-object (virtual-attribute 'relationships) nil)
		     (update-subscriptions-from-virtual-attribute-change
		       relation-subject (virtual-attribute 'relationships) nil)))
		  ((text-string-p error-string?)
		   (reclaim-text-string error-string?)))
	  finally
		(when new-related-items-list?
		  (reclaim-gensym-tree new-related-items-list?))
		(setq new-related-items-list? nil))))))



;;; The function `validate-items-in-all-relations' validates the items contained
;;; in all relations.  It checks whether the items are of the correct "subject"
;;; and "object" class for the given relation.  It does not validate the
;;; relation instances against any of the other, non-class relation attributes.
;;; For example, it does not test if the relation instances are the correct
;;; relation-type, such as one-to-one.

;;; This function is used to validate relation instances when there is a
;;; possible class change to an item in a relation.  It is not used to validate
;;; when there are changes to a relation-definition.  Relation definition
;;; changes are handled by other functions in this section.

;;; The class? and old-class? arguments, if non-NIL, specify the classes of the
;;; list elements that need to be validated.  If both arguments are NIL, then
;;; all instances of relations, will be validated.

(defun-void validate-items-in-all-relations (class? old-class?)
  (let ((relation-needs-validation? nil))
    (when (and (null class?) (null old-class?))
      (setq relation-needs-validation? t))
    ;; If no relations restrict their subject and objects to the given classes
    ;; (or subclasses of them), don't validate.  This saves the iteration costs
    ;; of check the relations of each instance of the class.
    (loop for relation being each class-instance of 'relation
	  for subject-class = (class-of-subject relation)
	  for object-class = (class-of-object relation)
	  until relation-needs-validation?
	  do
      (when (and (not (eq subject-class 'item))
		 (or (and class? (subclassp subject-class class?))
		     (and old-class?
			  ;; EQ test, in case the old-class is no longer
			  ;; defined.
			  (or (eq subject-class old-class?)
			      (subclassp subject-class old-class?)))))
	(setq relation-needs-validation? t))
      (when (and (not (eq object-class 'item))
		 (or (and class? (subclassp object-class class?))
		     (and old-class?
			  ;; EQ test, in case the old-class is no longer
			  ;; defined.
			  (or (eq object-class old-class?)
			      (subclassp object-class old-class?)))))
	(setq relation-needs-validation? t)))
    (when relation-needs-validation?
      (validate-relations-for-class (or class? 'item))))
  nil)



;;; The function `validate-relations-for-class' checks all the instances of the
;;; given class to see if they meet the class requirements of any relations that
;;; they may be in.

(defun validate-relations-for-class (class)
  (loop with class-description? = (class-description class)
	with relation-instance-slot-description? =
	(and class-description?
	     (get-slot-description-of-class-description
	       'relation-instances class-description? nil))
	for item being each class-instance of class
	for relation-instances? =
 	  (and relation-instance-slot-description?
	       (get-slot-description-value
		 item relation-instance-slot-description?))
	for invalid-relation-instance-p? = nil
	do
    (when relation-instances?
      #+relation-instances-v2
      (loop for relation-instance-form being each relation-instance
				       of relation-instances?
	    for relation-instance-name = (relation-instance-name relation-instance-form)
	    for relation = (relation-instance-relation relation-instance-form)
	    for relation-is-symmetric-p? = (relation-is-symmetric relation)
	    with relation-instance-is-inverse-p? = nil
	    with error-string? = nil
	    do
	(unless (eq relation-instance-name (relation-name relation))
	  ;; This is a user-specified inverse-relation or the secret-inverse.
	  ;; In both cases, the item is the relation subject.
	  (setq relation-instance-is-inverse-p? t))

	;; Note that each iteration only tests the item on one side of the
	;; relation.  (This item may be either the subject or object of the
	;; relation.)  If the item on the other side of the relation is of the
	;; class being tested, either it will be tested in another iteration or
	;; it will have already been removed if the relation instance for the
	;; first item is not valid.
	(cond
	  (relation-instance-is-inverse-p?
	   ;; In this case, the item is the SUBJECT of the relation.
	   (unless (frame-of-class-p item (class-of-subject relation))
	     (setq invalid-relation-instance-p? t)))
	  (relation-is-symmetric-p?
	   ;; Test both SUBJECT and OBJECT.
	   (unless (and (frame-of-class-p item (class-of-object relation))
			(frame-of-class-p item (class-of-subject relation)))
	     (setq invalid-relation-instance-p? t)))
	  (t
	   ;; In this case, the item is the OBJECT of the relation.
	   (unless (frame-of-class-p item (class-of-object relation))
	     (setq invalid-relation-instance-p? t))))

	(when invalid-relation-instance-p?
	  ;; Remove both sides of the relation, invoking any rules for chaining.
	  (loop with relation-name = (relation-name relation)
		for related-inverse-item being each related-item
					 of (relation-instance-items relation-instance-form)
		do
	    (setq error-string?
		  (if relation-instance-is-inverse-p?
		      ;; The first item is the relation SUBJECT.
		      (remove-from-relation
			relation-name item related-inverse-item t t nil)
		      ;; The first item is the relation OBJECT.
		      (remove-from-relation
			relation-name related-inverse-item item t t nil)))
	    (when (text-string-p error-string?)
	      #+development
	      (cerror
		"continue"
		"Error removing relation in validate-relations-for-class.")
	      (reclaim-text-string error-string?)))))

      ;; Note that the following LOOP uses a trailing pointer to access the
      ;; elements of a list.  This is needed because the contents of the list
      ;; may change as it is being iterated over.  The CONS holding the current
      ;; element will be removed if remove-from-relation is called from within
      ;; the loop.
      #-relation-instances-v2
      (loop for relation-instance-form = (car-of-cons relation-instances?) then
	    (and rest-of-relation-instance-list?
		 (car-of-cons rest-of-relation-instance-list?))
	    for rest-of-relation-instance-list? =
	    (cdr-of-cons relation-instances?) then
	    (cdr rest-of-relation-instance-list?)
	    with relation-instance-name = nil
	    with relation = nil
	    with relation-is-symmetric-p? = nil
	    with relation-instance-is-inverse-p? = nil
	    with error-string? = nil
	    do
	;; RELATION-INSTANCE-FORM: (name relation . relation-instances)
	(setq relation-instance-name (relation-instance-name relation-instance-form))
	(setq relation (relation-instance-relation relation-instance-form))
	(setq relation-is-symmetric-p? (relation-is-symmetric relation))
	(unless (eq relation-instance-name (relation-name relation))
	  ;; This is a user-specified inverse-relation or the secret-inverse.
	  ;; In both cases, the item is the relation subject.
	  (setq relation-instance-is-inverse-p? t))

	;; Note that each iteration only tests the item on one side of the
	;; relation.  (This item may be either the subject or object of the
	;; relation.)  If the item on the other side of the relation is of the
	;; class being tested, either it will be tested in another iteration or
	;; it will have already been removed if the relation instance for the
	;; first item is not valid.
	(cond
	  (relation-instance-is-inverse-p?
	   ;; In this case, the item is the SUBJECT of the relation.
	   (unless (frame-of-class-p item (class-of-subject relation))
	     (setq invalid-relation-instance-p? t)))
	  (relation-is-symmetric-p?
	   ;; Test both SUBJECT and OBJECT.
	   (unless (and (frame-of-class-p item (class-of-object relation))
			(frame-of-class-p item (class-of-subject relation)))
	     (setq invalid-relation-instance-p? t)))
	  (t
	   ;; In this case, the item is the OBJECT of the relation.
	   (unless (frame-of-class-p item (class-of-object relation))
	     (setq invalid-relation-instance-p? t))))

	(when invalid-relation-instance-p?
	  ;; Remove both sides of the relation, invoking any rules for chaining.
	  (loop with relation-name = (relation-name relation)
		for related-inverse-item being each related-item
		 of (relation-instance-items relation-instance-form)
		do
	    (setq error-string?
		  (if relation-instance-is-inverse-p?
		      ;; The first item is the relation SUBJECT.
		      (remove-from-relation
			relation-name item related-inverse-item t t nil)
		      ;; The first item is the relation OBJECT.
		      (remove-from-relation
			relation-name related-inverse-item item t t nil)))
	    (when (text-string-p error-string?)
	      #+development
	      (cerror
		"continue"
		"Error removing relation in validate-relations-for-class.")
	      (reclaim-text-string error-string?))))

	;; Test for last of relation-instances.
	    until (null rest-of-relation-instance-list?)))))

;; Consider optimizing the above to check if the given relation may contain an
;; instance of the desired class.  This looks like an improvement because
;; subclassp does less than frame-of-class-p.  But, the calling function,
;; validate-items-in-all-relations, sometimes needs to test the relation classes
;; using both the old and new classes.  In that case, two subclassp checks
;; doesn't seem to save much.  On the other hand, when an item is related to
;; more than one item (i.e., has more than one relation instance for the
;; relation) this could be more efficient.  This needs to be reviewed.  - cpm,
;; 7/21/94






;;;; Note Runtime Changes To Relations




;;; When the relations between items are about to change, this information needs
;;; to be noted, in case a KB is currently being saved.  One way this can be
;;; done is by calling note-change-to-runtime-data-for-block.  Currently, this
;;; information is relevant to warmboot saves because the wamboot snapshot KB's
;;; save the dynamic state of the relations between items.

;;; When relations are being added or removed from between items, this
;;; information is currently noted in:
;;;   add-to-relation, remove-from-relation, remove-transient-relation-instances

;;; As of version 4.0, slots of the relation-definition can be changed by the
;;; user while G2 is running or paused, as well as reset, and when there are
;;; relation instances between items.  In this case, the runtime changes are
;;; noted from the function note-change-or-deletion when the relation definition
;;; is modified.  This function calls class the class method handle-change-or-
;;; deletion-fanout, which is defined for relations, and the method calls
;;; note-change-to-all-related-items.



;;; The function `note-change-to-all-related-items' is used to note changes to
;;; all related items, both subject and object, in a relation.  This is needed
;;; when an attribute of a relation is about to change.

(defun-void note-change-to-all-related-items (relation)
  (let* ((relation-name (relation-name relation))
	 (inverse-name (inverse-of-relation relation))
	 (secret-name (secret-inverse-name relation))
	 (subject-class (class-of-subject relation))
	 (object-class (class-of-object relation))
	 (check-one-class-only?
	   ;; Check the most general class, if the subject and object classes
	   ;; are not disjoint.  Don't want to note the same item multiple
	   ;; times.
	   (cond ((eq subject-class object-class) subject-class)
		 ((subclassp subject-class object-class) object-class)
		 ((subclassp object-class subject-class) subject-class)
		 (t nil))))
    (cond (check-one-class-only?
	   (loop for item being each class-instance of check-one-class-only?
		 for relation-instances? = (relation-instances item)
		 when relation-instances?
		 do
	     (loop for relation-instance-form being each relation-instance
					      of relation-instances?
		   for item-relation-name = (relation-instance-name relation-instance-form)
		   for item-relation =
		     (relation-instance-relation relation-instance-form)
		   for relation-found? =
		     (and (eq item-relation relation)
			  (or (eq item-relation-name relation-name)
			      (eq item-relation-name inverse-name)
			      (eq item-relation-name secret-name)))
		   until relation-found?
		   finally
		     (when relation-found?
		       (note-change-or-deletion item t)))))
	  (t
	   (loop for item being each class-instance of subject-class
		 for relation-instances? = (relation-instances item)
		 when relation-instances?
		 do
	     (loop for relation-instance-form being each relation-instance
					      of relation-instances?
		   for item-relation-name = (relation-instance-name relation-instance-form)
		   for item-relation =
		     (relation-instance-relation relation-instance-form)
		   for relation-found? =
		     ;; "Subject" relation instances contain the inverse name.
		     (and (eq item-relation relation)
			  (or (eq item-relation-name inverse-name)
			      (eq item-relation-name secret-name)))
		   until relation-found?
		   finally
		     (when relation-found?
		       (note-change-or-deletion item t))))
	   (loop for item being each class-instance of object-class
		 for relation-instances? = (relation-instances item)
		 when relation-instances?
		 do
	     (loop for relation-instance-form being each relation-instance
					      of relation-instances?
		   for item-relation-name = (relation-instance-name relation-instance-form)
		   for item-relation =
		     (relation-instance-relation relation-instance-form)
		   for relation-found? =
		     ;; "Object" relation instances contain the relation name.
		     (and (eq item-relation relation)
			  (eq item-relation-name relation-name))
		   until relation-found?
		   finally
		     (when relation-found?		   
		       (note-change-or-deletion item t))))))))

;; Note that this function locates all related items by iterating over the
;; instances of the subject and/or object classes, without collecting duplicate
;; items.  An alternative approach is to always iterate over either the subject
;; or object class and then over the related items contained in each item's
;; relation-instances.  In this approach, it would be much more difficult and
;; more costly to not collect duplicate related items.  - cpm, 3/11/94

;; IMPORTANT NOTE: this process of noting changes to related items should be
;; optimized!  It should be replaced by calls to note-change-to-runtime-data-
;; for-block on only those items that are affected by the change to the
;; relation.  We do not need to be iterating over all items in the relation and
;; noting changes to each!  This optimization can be implemented by being
;; certain that all updates to relations caused by update-relation-instances-if-
;; necessary note runtime KB changes.  Currently, the add-to-relation and
;; remove-from-relaion calls do.  Need to also note the runtime changes in
;; remove-relations-instances-for-object-of-relation and in changes that affect
;; the relation and relation-inverse names.  - cpm, 3/11/94






;;;; Deactivation and Deletion




;;; When the system is reset, all transient relation instances must
;;; be removed.

;; Consider this as a macro for speed, but it is called by delete-frame!

;; Explanation of why this works when removing an instance from an item to
;; itself, where the relation is not symmetric: Let the two names for the
;; relation be X and Y, the relation frame be R, and the item be I.
;; The relation-instances slot of I look like:
;;    (   ...  (X R ... I ...) ... (Y R ... I ... ))

;; With leading-pointer above the first form, an operation is done to the second
;; form which modifies or deletes it. If it deletes it, cdr of the cons which is
;; leading-pointer or cdr of a cons further down the list gets modified.
;; The changes being made to the inner loop do not confuse the outer loop
;; because the change is always made further down the list. For example, the
;; inner loop could cause (cdr leading-cons) to be nil. This still would not be
;; a problem.
;; If the two names were the same, there would be a collision of pointer
;; modification, but we have adapted the convention that for a symmetric
;; relation, only one instance pointer is created, and we do not attempt to
;; remove it twice.

#+relation-instances-v2
(defun remove-transient-relation-instances (item called-from-system-reset?)
  (when initializing-clear-text-p
    (return-from remove-transient-relation-instances nil))
  (when (old-relation-instances-p (relation-instances item))
    (return-from remove-transient-relation-instances nil))
  (note-change-to-runtime-data-for-block item)
  (when-let (relation-instances (relation-instances item))
    (loop for relation-instance-form being each relation-instance of relation-instances
	  ;; given-name is potentially useless pre-rendezvous, because if it names an
	  ;; inverse, we have no reference to it {info is in relation instance}
	  with given-name
	  ;; other-name? can be NIL pre-rendezvous if the relation is not (yet) a
	  ;; frame {can be a symbol or UUID - wide-string}
	  with other-name?
	  ;; relation-or-reference can be a symbol or wide-string pre-rendezvous
	  with relation-or-reference
	  with deleted-names = nil
	  doing
      (cond
	((null relation-instance-form)
	 ;; In this case the relation-instance-form has been deleted in inner LOOP,
	 ;; but the hash-table entry is still there. The entry will be deleted in the
	 ;; FINALLY forms. -- Chun Tian (binghe), May 2016.
	 nil)
	;; This function is also called from delete-frame when we want
	;; even permanent relations that contain the deleted frame to
	;; be updated.  (ghw 3/25/95)
	((and called-from-system-reset?
	      ;; must be a frame during reset, so no framep check is needed
	      (relation-is-permanent (relation-instance-relation relation-instance-form)))
	 nil)
	(t
	 ;; Value assignments of `given-name' and `relation-or-reference' are moved here,
	 ;; because `relation-instance-form` could be NIL (captured by the first clause
	 ;; of current COND form). -- Chun Tian (binghe), May 2016.
	 (setq given-name (relation-instance-name relation-instance-form))
	 (setq relation-or-reference
	       (relation-instance-relation relation-instance-form))
	 ;; Remove the other direction of each instance if any.
	 (setq other-name?
	     (when (framep relation-or-reference)
	       ;; If we have a UUID {pre-rendezvous}, we don't know the name
	       ;; of the relation, so we do a special removal below by simply
	       ;; removing all opposite relations which contain item.
	       (if (neq given-name (relation-name relation-or-reference))
		   (relation-name relation-or-reference)
		   (if (relation-is-symmetric relation-or-reference)
		       given-name
		       (or (inverse-of-relation relation-or-reference)
			   (secret-inverse-name relation-or-reference))))))

	 (loop for item2 being each related-item
			       of (relation-instance-items relation-instance-form)
	       ;; item2 can be a symbol or UUID (wide-string) pre-rendezvous
	       for object-instances? = (when (framep item2)
					 (relation-instances item2))
	       for object-instance-forms =
		 (when object-instances?
		   (if (not (framep relation-or-reference))
		       ;; Pre-rendezvous, there may be multiple forms which
		       ;; pass this test, and we need to snip from all of
		       ;; them, not just the first we find.
		       (loop for form being each relation-instance of object-instances?
			     collect form using gensym-cons)
		     (gensym-list (get-relation-instance other-name? object-instances?))))
	       when
		 (if (not (framep relation-or-reference))
		   ;; pre-rendezvous, we never do the snipping if this is a
		   ;; self-relation - it will get cleaned up anyway
		   (neq item2 item)
		   (or (neq item2 item) (neq other-name? given-name)))
	       do
		 (when (framep item2)
		   (note-change-to-runtime-data-for-block item2))

		 (loop for object-instance-form in object-instance-forms
		       when object-instance-form
		       do
		   #+relation-instances-v2.1
		   (let* ((name (relation-instance-name object-instance-form))
			  (tree (relation-instance-items object-instance-form))
			  (found-item (get-related-item item tree)))
		     (cond ((null found-item)
			    #+(and development (not no-misterious-checks-in-dev))
			    (unless reading-kb-p
			      (cerror
			        "continue"
				"Relation symmetry constraint violated.")))
			   (t
			    (setf (get-related-item item tree) nil)
			    (delete-related-item item tree)
			    (when (related-items-is-empty-p tree)
			      (setf (get-relation-instance name object-instances?) nil)
			      ;; GENSYMCID-1715: G2 abort when resetting G2 (UNACEM)
			      ;;
			      ;; Prevent touching hash-table itself, otherwise this will break the
			      ;; outside LOOP. -- Chun Tian (binghe), May 2016.
			      (if (neq item2 item)
				  (delete-relation-instance name object-instances?)
				(slot-value-pushnew name deleted-names))
			      (reclaim-relation-instance object-instance-form)))))

		   #+relation-instances-v2.0
		   (loop with name = (relation-instance-name object-instance-form)
			 with queue = (relation-instance-items object-instance-form)
			 for queue-element = #+Lockfree-Deque (constant-queue-next
							        (constant-queue-head queue) queue)
					     #-Lockfree-Deque (constant-queue-head queue)
					then next-queue-element
			 until (or #+Lockfree-Deque (null queue-element)
				   #-Lockfree-Deque (eq queue-element queue)
				   (eq (queue-datum queue-element) item))
			 for next-queue-element = (constant-queue-next queue-element queue)
			 finally
			   (cond
			     (#+Lockfree-Deque (null queue-element)
			      #-Lockfree-Deque (eq queue-element queue)

			      ;; Specific instance does not exist.
			      #+(and development (not no-misterious-checks-in-dev))
			      ;; pre-rendezvous, this is fine.  The important
			      ;; thing is not to leave reclaimed/recycled
			      ;; frames around on the other side.
			      ;; Symbols/UUIDs will simply get resolved/removed
			      ;; at rendezvous time.
			      (unless reading-kb-p
				(cerror
				  "continue"
				  "Relation symmetry constraint violated.")))

			     ;; Clip out the cons holding item if there are other
			     ;; items on list.
			     (t
			      (constant-queue-delete queue-element queue)

			      ;; Reclaim the entire object-instance-form if item is
			      ;; solo.
			      (when (related-items-is-empty-p queue)
				(setf (get-relation-instance name object-instances?) nil)
				(if (neq item2 item)
				    (delete-relation-instance name object-instances?)
				  (slot-value-pushnew name deleted-names))
				(reclaim-relation-instance object-instance-form)))))

		       finally (reclaim-gensym-list object-instance-forms)))
	 (setf (get-relation-instance given-name relation-instances) nil)
	 (slot-value-push given-name deleted-names)
	 (reclaim-relation-instance relation-instance-form)
	 (setq relation-instance-form nil)))
      finally
	(when deleted-names
	  (loop for name in deleted-names do
	    (delete-relation-instance name relation-instances))
	  (reclaim-slot-value-list deleted-names)))))

#-relation-instances-v2
(defun remove-transient-relation-instances (item called-from-system-reset?)
  (when initializing-clear-text-p
    (return-from remove-transient-relation-instances nil))
  (note-change-to-runtime-data-for-block item)
  (loop with relation-instances = (relation-instances item)
	with relation-instance-form
	with given-name
	;; other-name? can be NIL pre-rendezvous if the relation is not (yet) a
	;; frame {can be a symbol or UUID - wide-string}
	with other-name?
	with relation-or-reference
	with trailing-pointer = nil
	with leading-pointer = relation-instances
	until (null leading-pointer) doing
    (setq relation-instance-form (car leading-pointer))
    ;; given-name is potentially useless pre-rendezvous, because if it names an
    ;; inverse, we have no reference to it {info is in relation instance}
    (setq given-name (relation-instance-name relation-instance-form))
    ;; relation-or-reference can be a symbol or wide-string pre-rendezvous
    (setq relation-or-reference (relation-instance-relation relation-instance-form))
    (cond
      ;; This function is also called from delete-frame when we want
      ;; even permanent relations that contain the deleted frame to
      ;; be updated.  (ghw 3/25/95)
      ((and called-from-system-reset?
	    ;; must be a frame during reset, so no framep check is needed
	    (relation-is-permanent relation-or-reference))
       (setq trailing-pointer leading-pointer)
       (setq leading-pointer (cdr leading-pointer)))

      (t
       ;; Remove the other direction of each instance if any.
       (setq other-name?
	     (when (framep relation-or-reference)
	       ;; If we have a UUID {pre-rendezvous}, we don't know the name
	       ;; of the relation, so we do a special removal below by simply
	       ;; removing all opposite relations which contain item.
	       (if (neq given-name (relation-name relation-or-reference))
		   (relation-name relation-or-reference)
		   (if (relation-is-symmetric relation-or-reference)
		       given-name
		       (or (inverse-of-relation relation-or-reference)
			   (secret-inverse-name relation-or-reference))))))

       (loop for item2 being each related-item
			     of (relation-instance-items relation-instance-form)
	     ;; item2 can be a symbol or UUID (wide-string) pre-rendezvous
	     for object-instances? = (when (framep item2)
				       (relation-instances item2))
	     for object-instance-forms =
		 (when object-instances?
		   (if (not (framep relation-or-reference))
		       ;; Pre-rendezvous, there may be multiple forms which
		       ;; pass this test, and we need to snip from all of
		       ;; them, not just the first we find.
		       (loop for form being each relation-instance of object-instances?
			     collect form using gensym-cons)
		     (gensym-list (get-relation-instance other-name? object-instances?))))
	     when
	       (if (not (framep relation-or-reference))
		   ;; pre-rendezvous, we never do the snipping if this is a
		   ;; self-relation - it will get cleaned up anyway
		   (neq item2 item)
		   (or (neq item2 item) (neq other-name? given-name)))
	       do
		 (when (framep item2)
		   (note-change-to-runtime-data-for-block item2))
		 (loop for object-instance-form in object-instance-forms
		       for name = (relation-instance-name object-instance-form)
		       do
		   (loop for trailing-pointer-2 on (cdr object-instance-form)
			 for leading-pointer-2 on (cddr object-instance-form)
			 for count from 0
			 until (eq (car leading-pointer-2) item)
			 finally
			   (cond
			     ((null leading-pointer-2)
			      ;; Specific instance does not exist.
			      #+(and development (not no-misterious-checks-in-dev))
			      ;; pre-rendezvous, this is fine.  The important
			      ;; thing is not to leave reclaimed/recycled
			      ;; frames around on the other side.
			      ;; Symbols/UUIDs will simply get resolved/removed
			      ;; at rendezvous time.
			      (unless reading-kb-p
				(cerror
				  "continue"
				  "Relation symmetry constraint violated.")))

			     ;; Clip out the cons holding item if there are other
			     ;; items on list.
			     ((or (>f count 0) (cdr leading-pointer-2))
			      (setf (cdr trailing-pointer-2)
				    (cdr leading-pointer-2))
			      (reclaim-slot-value-cons leading-pointer-2))
			     
			     ;; Reclaim the entire object-instance-form if item is
			     ;; solo.
			     (t 	       
			      (loop for trailing-pointer-3 = nil
							   then leading-pointer-3
				    for leading-pointer-3 = object-instances?
							  then (cdr leading-pointer-3)
				    until (eq (car leading-pointer-3)
					      object-instance-form)

				    finally
				      (if (null trailing-pointer-3)
					  ;; Deleting the first sublist.
					  (setf (relation-instances item2)
						(cdr leading-pointer-3))
					  ;; Deleting sublist after first one.
					  (setf (cdr trailing-pointer-3)
						(cdr leading-pointer-3)))

				      (reclaim-slot-value-list
					object-instance-form)
				      (reclaim-slot-value-cons
					leading-pointer-3)))))
		       finally (reclaim-gensym-list object-instance-forms)))

       (reclaim-slot-value-list relation-instance-form)
       (if trailing-pointer
	   (setf (cdr trailing-pointer) (cdr leading-pointer))
	   (setf (relation-instances item) (cdr leading-pointer)))
       (setq leading-pointer
	     (prog1 (cdr leading-pointer)
		    (reclaim-slot-value-cons leading-pointer)))))))




;;; The cleanup for a relation removes all instances.

(def-class-method cleanup (relation)
  (funcall-superior-method relation)
  (unless resolving-definitional-name-conflicts?
    (when-let (relation-name? (relation-name relation))
      (remove-all-relations-instances-for-relation relation relation-name?))))



;;; The function `remove-all-relations-instances-for-relation' removes the
;;; relation between all items for the given relation.  This function is needed,
;;; for example, when a relation is being deleted.

(defun remove-all-relations-instances-for-relation (relation relation-name)
  (unless releasing-kb?
    (loop for item being each class-instance of (class-of-object relation)
          doing
      (unless (old-relation-instances-p (relation-instances item))
        (remove-relations-instances-for-object-of-relation
          relation relation-name item)))))




;;; The function `remove-relations-instances-for-object-of-relation' removes the
;;; relation instances only for the given relation and a possible "object of the
;;; relation".  Note that the item is not necessarily in a relation, but is of
;;; the correct "second class" (i.e., "object" class of the relation).

;;; Note that the relation-name argument is needed in case this function is
;;; cleaning up for a relation whose name has already been removed.

#+relation-instances-v2
(defun remove-relations-instances-for-object-of-relation
    (relation relation-name item)
  (when-let* ((relation-instances (relation-instances item))
	      (relation-instance-form
	       (get-relation-instance relation-name relation-instances)))
    (when (eq (relation-instance-relation relation-instance-form) relation)
      (setf (get-relation-instance relation-name relation-instances) nil)
      (delete-relation-instance relation-name relation-instances)

      (let ((other-name (if (relation-is-symmetric relation)
			    relation-name
			  (or (inverse-of-relation relation)
			      (secret-inverse-name relation)))))

	(loop for item2 being each related-item of (relation-instance-items relation-instance-form)
	      for subject-instances = (relation-instances item2)
	      for subject-instance-form
		= (get-relation-instance other-name subject-instances)
	      doing
	  (when (and (eq (relation-instance-relation subject-instance-form) relation)
		     (or (neq item2 item) (neq other-name relation-name)))

	    #+relation-instances-v2.1
	    (let* ((tree (relation-instance-items subject-instance-form))
		   (found-item (get-related-item item tree)))
	      (cond ((null found-item)
		     #+(and development (not no-misterious-checks-in-dev))
		     (cerror "continue" "Relation symmetry constraint violated."))
		    (t
		     (setf (get-related-item item tree) nil)
		     (delete-related-item item tree)
		     (when (related-items-is-empty-p tree)
		       (setf (get-relation-instance other-name subject-instances) nil)
		       (delete-relation-instance other-name subject-instances)
		       (reclaim-relation-instance subject-instance-form)))))

	    #+relation-instances-v2.0
	    (loop with queue = (relation-instance-items subject-instance-form)
		  for queue-element = #+Lockfree-Deque (constant-queue-next
							 (constant-queue-head queue) queue)
				      #-Lockfree-Deque (constant-queue-head queue)
				 then next-queue-element
		  until (or #+Lockfree-Deque (null queue-element)
			    #-Lockfree-Deque (eq queue-element queue)
			    (eq (queue-datum queue-element) item))
		  for next-queue-element = (constant-queue-next queue-element queue)

	       finally
	         (cond
		   (#+Lockfree-Deque (null queue-element)
		    #-Lockfree-Deque (eq queue-element queue)
		    ;; Specific instance does not exist.
		    #+(and development (not no-misterious-checks-in-dev))
		    (cerror "continue" "Relation symmetry constraint violated."))
		   (t
		    ;; Clip out the cons holding item if there are other
		    ;; items on list.
		    (constant-queue-delete queue-element queue)

		    ;; Reclaim the entire subject-instance-form if item is solo.
		    (when (related-items-is-empty-p queue)
		      (setf (get-relation-instance other-name subject-instances) nil)
		      (delete-relation-instance other-name subject-instances)
		      (reclaim-relation-instance subject-instance-form))))))))
      (reclaim-relation-instance relation-instance-form))))

#-relation-instances-v2
(defun remove-relations-instances-for-object-of-relation
    (relation relation-name item)
  (loop with relation-instances = (relation-instances item)
	with relation-instance-form
	with other-name
	for trailing-pointer = nil then leading-pointer
	for leading-pointer = relation-instances then (cdr leading-pointer)

	;; find the relation-instance-form for this relation if any
	until (or (null leading-pointer)
		  (and (eq (caar leading-pointer) relation-name)
		       (eq (cadar leading-pointer) relation)))
	finally
	  (when leading-pointer
	    (setq relation-instance-form (car leading-pointer))
	    (if trailing-pointer
		(setf (cdr trailing-pointer) (cdr leading-pointer))
		(setf (relation-instances item) (cdr leading-pointer)))
	    (reclaim-slot-value-cons leading-pointer)

	    (setq other-name
		  (if (relation-is-symmetric relation)
		      relation-name
		      (or (inverse-of-relation relation)
			  (secret-inverse-name relation))))

	    (loop for item2 in (cddr relation-instance-form)
		  for subject-instances = (relation-instances item2)
		  for subject-instance-form
		  = (assq other-name subject-instances) doing
	      (when (and (eq (cadr subject-instance-form) relation)
			 (or (neq item2 item) (neq other-name relation-name)))
		(loop for trailing-pointer-2 on (cdr subject-instance-form)
		      for leading-pointer-2 on (cddr subject-instance-form)
		      for count from 0
		      until (eq (car leading-pointer-2) item)
		      do
		  (when (null leading-pointer-2)
		    ;; Specific instance does not exist.
		    #+(and development (not no-misterious-checks-in-dev))
		    (cerror
		      "continue" "Relation symmetry constraint violated."))
		  
		      finally
			(cond
			  ;; Clip out the cons holding item if there are other
			  ;; items on list.
			  ((or (> count 0) (cdr leading-pointer-2))
			   (setf (cdr trailing-pointer-2)
				 (cdr leading-pointer-2))
			   (reclaim-slot-value-cons leading-pointer-2))
			  
			  ;; Reclaim the entire subject-instance-form if item
			  ;; is solo.
			  (t 	       
			   (loop for trailing-pointer-3 =
				 nil then leading-pointer-3
				 for leading-pointer-3 =
				 subject-instances then
				 (cdr leading-pointer-3)
				 until (eq (car leading-pointer-3)
					   subject-instance-form)
				 
				 finally
				   (if (null trailing-pointer-3)
				       ;; Deleting the first sublist.
				       (setf (relation-instances item2)
					     (cdr leading-pointer-3))
				       ;; Deleting sublist after first one.
				       (setf (cdr trailing-pointer-3)
					     (cdr leading-pointer-3)))
				   (reclaim-slot-value-list
				     subject-instance-form)
				   (reclaim-slot-value-cons
				     leading-pointer-3)))))))
	    
	    (reclaim-slot-value-list relation-instance-form))))




;;;; Testing stuff




#+development
(defvar the-names)

#+development
(defun find-frames ()
  (loop for name in the-names do
    (set name (get-instance-with-name-if-any 'root name))))

#+development
(defun r-status ()
  (loop for name in the-names
	do
    (print name)
    (print (symbol-value name))
    (print (relation-instances (symbol-value name)))
    (terpri)))


#+development
(defun r-clear ()
  (loop for name in the-names doing
    (setf (relation-instances (symbol-value name)) nil)))






;;;; Tools to handle invalid relations 





;;; The function `find-and-fix-all-bad-relations' locates all invalid relations
;;; (defined below) and removes them from the relation-instances slot of the
;;; subject and object items.

#+development
(defun find-and-fix-all-bad-relations ()
  (loop for block in (find-all-bad-relations)
	do
    (remove-invalid-relation-instances block)))



;;; The function `find-all-bad-relations' locates all relations that have a
;;; subject or object that is incorrect given the relation subject or object
;;; class.

;;; It returns of list whose elements are relations and relation-instances.

#+development
(defun find-all-bad-relations ()
  (loop for block being each class-instance of 'block
	when (and (relation-instances block)
		  (block-has-bad-relation-classes-p block))
	collect block))

#+development
(defun block-has-bad-relation-classes-p (block)
  (loop with invalid-relations? = nil
	for r in (relation-instances block)
	do
	(setq invalid-relations?
	      (not (valid-relation-instance-classes-p block r)))
	until invalid-relations?
	finally (return invalid-relations?)))



;;; The function `block-relation-instances-violate-class-type-p'
;;; returns non-null when a block has a relation-instance where
;;; the block or one of its related blocks do not conform to the
;;; class-of-subject or class-of-object class types on the
;;; relation.

(defun block-relation-instances-violate-class-type-p (block)
  (when-let (relation-instances (relation-instances block))
    (loop for relation-instance being each relation-instance
	  			of relation-instances
	  thereis (not (valid-relation-instance-classes-p
			 block relation-instance)))))

(defun valid-relation-instance-classes-p (block relation-instance)
  (let* ((related-blocks (relation-instance-items relation-instance))
	 (relation (relation-instance-relation relation-instance))
	 (relation-is-symmetric? (relation-is-symmetric relation))
	 (relation-instance-name (relation-instance-name relation-instance))
	 (inverse-name (if (relation-is-symmetric relation)
			   (relation-name relation)
			   (or (inverse-of-relation relation)
			       (secret-inverse-name relation))))
	 (other-name (if (eq relation-instance-name inverse-name)
			 (relation-name relation)
			 inverse-name)))
    (multiple-value-bind (class-1 class-2?)
	(classes-for-block-containing-relation relation-instance)
      ;; The reciprocal relation-instances for a symmetric relation will
      ;; have the same relation-name as their name-designations so block
      ;; can be either the class-of-object or class-of-subject.  This
      ;; is unlike non-symmetric where the subject and object class frames
      ;; will have different relation-name designations that are meanful
      ;; from a subject-object perspective.
      (if relation-is-symmetric?
	  (let ((class-of-block?
		  (cond ((frame-of-class-p block class-1) 'class-1)
			((frame-of-class-p block class-2?) 'class-2)
			(t nil))))
	    (and class-of-block?
		 (let ((desired-other-block-class
			 (if (eq class-of-block? 'class-1)
			     class-2?
			     class-1)))
		   (loop for other-block being each related-item of related-blocks
			 always (and (frame-of-class-p
				       other-block desired-other-block-class)
				     (is-related-macro
				       relation-instance-name block other-block))))))
	  (and 
	    (and (frame-of-class-p block class-1)
		 (or (null class-2?)
		     (frame-of-class-p block class-2?)))
	    (multiple-value-bind (class-1 class-2?)
		(classes-for-other-blocks-in-relation relation-instance)
	      (loop for other-block being related-item of related-blocks
		    always (and (frame-of-class-p other-block class-1)
				(or (null class-2?)
				    (frame-of-class-p other-block class-2?))
				;; check relation in the opposite direction.
				(is-related-macro
				  other-name block other-block)))))))))

(defun classes-for-block-containing-relation (relation-instance)
  (let* ((relation (relation-instance-relation relation-instance))
	 (relation-instance-name (relation-instance-name relation-instance)))
    (cond
      ((not (eq relation-instance-name (relation-name relation))) ; inverse case
       (class-of-subject relation))
      ((relation-is-symmetric relation)
       (values
	 (class-of-subject relation)
	 (class-of-object relation)))
      (t
       (class-of-object relation)))))

(defun classes-for-other-blocks-in-relation (relation-instance)
  (let* ((relation (relation-instance-relation relation-instance))
	 (relation-instance-name (relation-instance-name relation-instance)))
    (cond
      ((not (eq relation-instance-name (relation-name relation))) ; inverse case
       (class-of-object relation))
      ((relation-is-symmetric relation)
       (values
	 (class-of-object relation)
	 (class-of-subject relation)))
      (t
       (class-of-subject relation)))))



;;; The function `remove-invalid-relation-instances' removes the relation
;;; instances of the given item that do not fit with the relation subject and
;;; object classes.  Both the subject and object of the item's
;;; relation-instances are checked.

;;; This function is useful when fixing up a KB that contains invalid
;;; relation-instances.

(defun remove-invalid-relation-instances (item)
  (let ((copy-of-relation-instances?
	  (copy-list-of-relation-instances (relation-instances item)))
	(invalid-item-p? nil))
    (when copy-of-relation-instances?
      ;; We need to copy relation-instances, as well as the lists
      ;; it is composed of, because deleting relation instances will
      ;; destructively modify relation instances. -alatto, 5/22/03
      (loop for relation-instance-form in copy-of-relation-instances?
	    with relation-instance-name = nil
	    with inverse-name = nil
	    with other-name = nil
	    with relation = nil
	    with relation-is-symmetric-p? = nil
	    with relation-instance-is-inverse-p? = nil
	    with error-string? = nil
	    do
	;; RELATION-INSTANCE-FORM: (name relation . relation-instances)
	(setq relation-instance-name (car-of-cons relation-instance-form))
	(setq relation (car-of-cons (cdr-of-cons relation-instance-form)))
	(setq relation-is-symmetric-p? (relation-is-symmetric  relation))
	(setq inverse-name (if (relation-is-symmetric relation)
			       (relation-name relation)
			       (or (inverse-of-relation relation)
				   (secret-inverse-name relation))))
	(setq other-name (if (eq relation-instance-name inverse-name)
			     (relation-name relation)
			     inverse-name))

	(unless (eq relation-instance-name (relation-name relation))
	  ;; This is a user-specified inverse-relation or the secret-inverse.
	  ;; In both cases, the item is the relation subject.
	  (setq relation-instance-is-inverse-p? t))

	(cond
	  (relation-instance-is-inverse-p?
	   ;; In this case, the item is the SUBJECT of the relation.
	   (unless (frame-of-class-p item (class-of-subject relation))
	     (setq invalid-item-p? t)))
	  (relation-is-symmetric-p?
	   ;; Test both SUBJECT and OBJECT.
	   (unless (and (frame-of-class-p item (class-of-object relation))
			(frame-of-class-p item (class-of-subject relation)))
	     (setq invalid-item-p? t)))
	  (t
	   ;; In this case, the item is the OBJECT of the relation.
	   (unless (frame-of-class-p item (class-of-object relation))
	     (setq invalid-item-p? t))))

	(loop for invalid-inverse-item-p? = nil
	      for related-inverse-item in
	        (cdr-of-cons (cdr-of-cons relation-instance-form))
	      do
	  (when (null invalid-item-p?)
	    ;; Check the other side of the relation.
	    (setq invalid-inverse-item-p?
		  (not (is-related-macro
			 other-name item related-inverse-item)))

	    (when (null invalid-inverse-item-p?)
	      (cond
		(relation-instance-is-inverse-p?
		 ;; In this case, the item is the OBJECT of the relation.
		 (unless (frame-of-class-p
			   related-inverse-item (class-of-object relation))
		   (setq invalid-inverse-item-p? t)))
		(relation-is-symmetric-p?
		 ;; Test both SUBJECT and OBJECT.
		 (unless (and (frame-of-class-p
				related-inverse-item (class-of-object relation))
			      (frame-of-class-p
				related-inverse-item
				(class-of-subject relation)))
		   (setq invalid-inverse-item-p? t)))
		(t
		 ;; In this case, the item is the SUBJECT of the relation.
		 (unless (frame-of-class-p related-inverse-item
					   (class-of-subject relation))
		   (setq invalid-inverse-item-p? t))))))

	  (when (or invalid-item-p? invalid-inverse-item-p?)
	    (setq error-string?
		  (cond
		    (relation-instance-is-inverse-p?
		      ;; The first item is the relation SUBJECT.

		      ;; Relation-instance-name here is the relation name
		      ;; that appears in the relation-instances of the
		      ;; item argument to this function.  Other-name will
		      ;; be the name in the related item. (ghw 8/19/98)
		      (remove-from-relation
			other-name item related-inverse-item t nil t)
		      (remove-from-relation
			relation-instance-name related-inverse-item item
			t nil t))
		    (t
		     ;; The first item is the relation OBJECT.
		     (remove-from-relation
		       relation-instance-name related-inverse-item item t nil t)
		     (remove-from-relation
		       other-name item related-inverse-item
		       t nil t)))))
	  (when (text-string-p error-string?)
	    #+development
	    (cerror
	      "continue"
	      "Error removing relation in validate-relations-for-class.")
	    (reclaim-text-string error-string?)))))
    (loop for sublist in copy-of-relation-instances?
	  do
      (reclaim-gensym-list sublist))
    (reclaim-gensym-list copy-of-relation-instances?)))

#+development
(defun find-missing-reciprocal-relations ()
  (let ((missing-relations-list? nil))
    (loop for block being each class-instance of 'block
	  for relation-instances = (relation-instances block)
	  do
      (when relation-instances
	(loop for relation-instance being each relation-instance of relation-instances
	      for relation-name-reference = (relation-instance-name relation-instance)
	      for relation = (relation-instance-relation relation-instance)
	      for relation-name = (relation-name relation)
	      for other-relation-name-reference =
	            (if (neq relation-name-reference (relation-name relation))
			(relation-name relation)
			(if (relation-is-symmetric relation)
			    relation-name-reference
			    (or (inverse-of-relation relation)
				(secret-inverse-name relation))))
	      for object-frames = (relation-instance-items relation-instance)
	      do
	  (loop for object-frame being each related-item of object-frames
		for corresponding-relation? = (get-relation-instance
					        other-relation-name-reference
						(relation-instances object-frame))
		do
	    (unless (and corresponding-relation?
			 (relation-exist-p block (relation-instance-items corresponding-relation?)))
	      (frame-push (frame-list block relation-name-reference object-frame
				  other-relation-name-reference)
			  missing-relations-list?))))))
    missing-relations-list?))

#+development
(defun find-changed-relation-names ()
  (let ((changed-relations-list? nil))
    (loop for block being each class-instance of 'block
	  for relation-instances = (relation-instances block)
	  do
      (when relation-instances
	(loop for relation-instance being each relation-instance of relation-instances
	      for relation-name-reference = (relation-instance-name relation-instance)
	      for relation = (relation-instance-relation relation-instance)
	      for relation-name = (relation-name relation)
	      for inverse-of-relation = (inverse-of-relation relation)
	      for secret-inverse-name = (secret-inverse-name relation)
	      do
	  (unless (or (eq relation-name-reference relation-name)
		      (eq relation-name-reference inverse-of-relation)
		      (eq relation-name-reference secret-inverse-name))
	    (push block changed-relations-list?)))))
    changed-relations-list?))

#+development
(defun duplicate-relation-instances-p (relation-instances)
  #-relation-instances-v2
  (loop for sublist on relation-instances
	for relation-instance = (car-of-cons sublist)
	for relation-name-reference = (car-of-cons relation-instance)
	for relation = (cadr-of-cons relation-instance)
	thereis
	(loop for other-relation-instance in (cdr sublist)
	      thereis
	      (and (eq relation-name-reference
		       (car-of-cons other-relation-instance))
		   (eq relation
		       (cadr-of-cons other-relation-instance)))))
  #+relation-instances-v2
  (declare (ignore relation-instances))
  #+relation-instances-v2
  nil)

#+development
(defun find-blocks-with-duplicate-relation-instances ()
  (loop for block being each class-instance of 'block
	for relation-instances = (relation-instances block)
	when (duplicate-relation-instances-p relation-instances)
	  collect block using frame-cons))


#+development
(defun find-blocks-with-corrupted-relation-instances ()
  (loop for block being each class-instance of 'block
	for relation-instances = (relation-instances block)
	when 
	  (loop for relation-instance being each relation-instance of relation-instances
		thereis
		(or (not (symbolp (relation-instance-name relation-instance)))
		    (not (frame-of-class-p
			   (relation-instance-relation relation-instance) 'relation))
		    (loop for related-item being each related-item of
						 (relation-instance-items relation-instance)
			  thereis (not (framep related-item)))))
	  collect block))



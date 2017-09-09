;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module LISTS

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Chris Morel




(declare-forward-references
  (g2-array-or-list-default-element-value function arrays)
  (make-transient-item function stack-acts)
  (set-neither-permanent-nor-transient-and-propagate function stack-acts)
  (evaluation-value-type function sets)
  (block-can-be-dependent-p function filters)
  (ancestor-p function activate)
  (item-currently-contains-compiled-value function proc-utils)
  (get-list-contents-as-sequence function grammar4a)
  (evaluation-truth-value-true-p function simulate5)
  (align-selection-command-operations variable) ; COMMANDS2
  (transfer-items-to-mouse-of-window function) ; COMMANDS1
  (move-items-to-mouse-of-window function) ; COMMANDS1
  (map-to-image-plane function)		; CONTROLS
  (map-to-image-plane-or-stack-error function) ; CONTROLS
  )


(declare-forward-reference send-ws-representations-item-moved function)





;;;; G2 Lists




;;; A `g2-list' is a type of object in G2 that has a number of actions and
;;; expressions that support list-like operations.  As you would expect, these
;;; include inserting and removing elements, referencing elements, testing for
;;; membership, and iterating over elements.

;;; An element of a g2-list must be of its defined element-type.  This
;;; restriction is maintained in the evaluators and actions, not in the
;;; operations below.

;;; NOTE THAT as of G2 4.0, the element-type of lists now include value and
;;; item-or-value.  Value-list is a new type of list and contains values.
;;; Value-list is also the superior of all other value lists, such as
;;; symbol-list.  G2-list is an existing class that can now be instantiated and
;;; contains item-or-values.

;;; A g2-list only contain elements when it is active.  When the list is
;;; deactivated, the elements are removed from the list and are not returned
;;; upon re-activation.  Also, if an item element is deactivated, it is no
;;; longer a member of the list and is not returned to the list automatically on
;;; re-activation.  Describing a g2-list in G2 shows the elements that are
;;; present in the list.

;;; Note that g2-arrays were implemented after g2-lists and now have some common
;;; G2 expressions and actions.  See the action, stack-evaluator, and role files
;;; for more information and the implementation of the expressions and actions.



;;; The following terms briefly describes the implementation of g2-lists.

;; Note that, up through G2 version 3.x, g2-list datum elements were implemented
;; using temporary-constants.  In 4.0, they have been re-implemented to use
;; evaluation-values.  - cpm, 10/13/93

;;; Developers wanting to make use of the g2-list operations should refer to the
;;; operations defined in the accessor, insertion, and deletion sections.  See
;;; the actions, stack-eval, and roles modules for uses of these operations.

;;; The g2-list frame is an instance of g2-list that contains a pointer to a
;;; g2-list-structure.  The g2-list-structure is a doublely-linked list of
;;; elements.  The public interface for this file is to use the insert, remove,
;;; etc. operations that work on g2-list frames.

;;; A record is kept of the g2-lists that an item belongs to.  This information
;;; resides on the item and is used to provide fast membership tests for
;;; item-lists.

;;; There are three levels to the design.

;;; 1. The g2-list evaluators and actions call g2-list operations.  They
;;; restrict the list elements to be only of the defined list element type.

;;; 2. The `g2-list operators' call g2-list structure operations, maintain a
;;; record of g2-lists that an item belongs to, and only disallows inactive
;;; items from belonging to a list.

;;; 3. at the lowest level are `g2-list structure operations'.  These operations
;;; define basic linked-list operations, such as insert, delete, and create,
;;; that maninpulate g2-list elements.  This is not part of the public
;;; interface.



;; Open Issues:

;; 1. Currently, the user cannot be an inactive item in a g2-list.  Also,
;; inactive items are removed from the list.  Should we change this restriction
;; from "no active" to "not servable"?  This would allow the user to put
;; inactive kb-workspaces into a list.  This would be consistent with
;; the fact that users can reference inactive kb-workspaces.  Also, the
;; serve-item-p test may be the location for future network security checks of
;; items.  - cpm, 12/8/93







;;;; G2-List Class, Subclasses, and Methods







(def-class (g2-list object (foundation-class g2-list) define-predicate
		    (class-export-comment
		      "The original parts document showed the following attributes for g2-list: reconcile.
<ul>
<LI>element-type: symbol, ; class of element
<LI>allow-duplicate-elements?: boolean, <!--from insert-duplicate-elements, -->
<LI>permanent?: boolean,
<LI>list-structure: ???, 
<LI>list-open-continuations: ???
</ul>"))
  (list-structure nil vector-slot system (type list-structure) save
		  do-not-clone
		  do-not-put-in-attribute-tables not-user-editable)
  (list-type item-or-datum vector-slot (type element-type) system save
	     not-user-editable)
  (insert-duplicate-elements? t vector-slot system user-overridable
			      (type yes-or-no))  ;; see note with alias
  (list-is-permanent nil system user-overridable (type yes-or-no) save)
  (icon-description
    (:funcall-at-load-time
      create-icon-description
      60 60 
      ((outline (0 0) (60 0) (60 60) (0 60))
       (lines (15 15) (45 15))
       (lines (15 20) (45 20))
       (lines (15 25) (45 25))
       (lines (15 30) (45 30))
       (lines (15 35) (45 35))
       (lines (15 40) (45 40))
       (lines (15 45) (45 45)))))
  (list-open-continuations nil vector-slot system do-not-save)
  (list-size 0 vector-slot (type integer) system do-not-save not-user-editable))

;; Note that the list-type slot cannot be edited by the user.  It can only be
;; modified in new subclasses of item-list, using the default-settings slot.


#+unused
(defun-simple list-is-permanent-function (g2-list)
  (list-is-permanent g2-list))


(def-slot-value-reclaimer list-structure (g2-list-structure? g2-list)
  (when (g2-list-structure-p g2-list-structure?)
    (cond
      ((consp g2-list-structure?)
       #+development
       ;; Until the once-only post-loading function convert-saved-list-values-
       ;; to-g2-list-structure has done its work, the saved values will be
       ;; a list.
       (unless (or reading-kb-p
		   currently-automatically-resolving-class-name-conflicts?)
	 (cerror "lists" "suspect list-structure -- please tell ghw"))
       (reclaim-slot-value-tree g2-list-structure?)
       (setf (list-structure g2-list) nil))
      (t
       (delete-g2-list g2-list)))))

(define-slot-alias element-type list-type g2-list)


(define-slot-alias allow-duplicate-elements insert-duplicate-elements? g2-list)

;; Although the name of the alias here is simply allow-duplicate-elements,
;; thanks to grammar-categories-getting-?-in-attribute-table, it gets a
;; question mark appended in the user-visible attribute display.  Hah!

;; The grammar-categories-getting-?-in-attribute-table facility has been removed,
;; but we still need this because that alias symbol will have been saved in old
;; kbs  ddm 12/20/96


(def-slot-putter insert-duplicate-elements? (g2-list new-value initializing?)
  (setf (insert-duplicate-elements? g2-list) new-value)
  (when (and (not initializing?) (null new-value)
	     (not (g2-list-empty-p g2-list)))
    ;; Check for and remove any duplicate elements.  A NIL new-value indicates
    ;; that the list does not allow duplicates.
    (remove-g2-list-duplicate-elements g2-list))
  new-value)



;;; The deactivate-subclass-of-entity method for g2-lists clears the g2-list of
;;; all elements and reclaims elements of type value and not item.  Note that
;;; the elements are not added back to the list on re-activation.

(def-class-method deactivate-subclass-of-entity (g2-list)
  (when (and (list-structure g2-list)
	     (not warmbooting?)
	     (not (list-is-permanent g2-list)))
    (delete-g2-list g2-list)))


;;; The activate-subclass-of-entity method for g2-lists initializes lists by
;;; creating a new g2-list-structure.  Note that initially the list is empty
;;; (contains no elements).

(def-class-method activate-subclass-of-entity (g2-list)
  (if (null (list-structure g2-list))
      (setf (list-structure g2-list) (create-empty-g2-list-structure))))



;;; Subclasses of g2-list can all be instantiated by the user in G2.  They can
;;; only contain elements of the given type.

;;; New to version 4.0:
;;;  G2-list can be instantiated and subclassed.  It contains elements of type
;;; item-or-value.
;;;  Value-list is new type of g2-list and, as you may guess, only can contain
;;; values (non-items).  It is now the superior-class of all other value-lists
;;; (symbol-list, quantity-list, etc.).

(def-class (item-list g2-list (foundation-class item-list))
  (list-type item not-user-editable user-overridable))

(def-class (value-list g2-list (foundation-class value-list))
  (list-type datum))

(def-class (symbol-list value-list (foundation-class symbol-list))
  (list-type symbol))

(def-class (text-list value-list (foundation-class text-list))
  (list-type text))

(def-class (truth-value-list value-list (foundation-class truth-value-list))
  (list-type truth-value))

(def-class (quantity-list value-list (foundation-class quantity-list))
  (list-type number))			;was quantity in version 3.x.

(def-slot-putter list-type (g2-list new-value initializing?)
  ;; To rid us of old quantity symbols from 3.x.  -jra 1/31/95
  (when (eq new-value 'quantity)
    (setq new-value 'number))
  (setf (list-type g2-list) new-value)
  (when (and (not initializing?) (not (g2-list-empty-p g2-list)))
    ;; Check that any existing elements fit with the new element-type.
    (validate-and-fix-g2-item-list-elements g2-list))
  new-value)

(def-class (float-list quantity-list (foundation-class float-list))
  (list-type float))

(def-class (integer-list quantity-list (foundation-class integer-list))
  (list-type integer))






;;;; Items Belonging to G2-Lists




;;; Items contain a slot, list-elements-for-item, which maintains a record of
;;; the g2-lists that the item belongs to.  This information consists of a list
;;; of g2-list-element structures that correspond to it's element position in
;;; the g2-lists.  If an item is a member of a g2-list more than once, then
;;; there is an element-structure in list-elements-for-item for each position in
;;; the g2-list.  This information is useful when deleting items that belong to
;;; a g2-list and when searching for element (item) positions in a g2-list.  The
;;; search is order N, where N is the number of g2-lists that an item belongs
;;; to.  This data structure is maintained in the g2-list operations and in
;;; frame deletion/deactivation.




;;; The uses of `g2-list cons' include record keeping of the g2-lists that an
;;; item belongs to.

(defconser g2-list)



;;; The function `add-to-list-elements-for-item' is used to record the fact that
;;; an item belongs to a g2-list and saves the position (i.e., the
;;; g2-list-element structure) associated with the position in the g2-list.
;;; This provides efficient access back to the list and the position into the
;;; list.

(defun-simple add-to-list-elements-for-item (item g2-list-element-structure)
  #+SymScale
  (g2-list-push-atomic g2-list-element-structure
		       (list-elements-for-item item))
  #-SymScale
  (let ((element-list (list-elements-for-item item)))
    (setf (list-elements-for-item item)
	  (g2-list-cons g2-list-element-structure element-list))))


;;; The function `delete-from-list-elements-for-item' is called when an item is
;;; removed from a g2-list.  It updates the record of g2-lists that an item
;;; belongs to.  Note that by default this only removes the item from the
;;; specified location in the g2-list.  It can still exist in other locations in
;;; the g2-list.  If the remove-all-element-instances? argument is non-nil, then
;;; the item from all locations in the g2-list.

(defun delete-from-list-elements-for-item
       (item g2-list-element-structure
	 &optional (remove-all-element-instances? nil))
  (let ((element-list (list-elements-for-item item))
	(first-element-deleted? nil))
    (when element-list
      (when (eq (first element-list) g2-list-element-structure)
	#+SymScale
	(g2-list-pop-atomic (list-elements-for-item item))
	#-SymScale
	(progn
	  (setf (list-elements-for-item item) (cdr element-list))
	  (reclaim-g2-list-cons element-list))
	(setq first-element-deleted? t))
      (when (or remove-all-element-instances? (null first-element-deleted?))
	(loop for element-sub-list on element-list
	      for element = (second element-sub-list)
	      until (null (cdr element-sub-list))
	      do
	  (when (eq element g2-list-element-structure)
	    (let ((reclaim-cons (cdr element-sub-list)))
	      (setf (cdr element-sub-list) (cddr element-sub-list))
	      (reclaim-g2-list-cons reclaim-cons)
	      (unless remove-all-element-instances?
		(return)))))))
    (list-elements-for-item item)))






;;;; G2 List Support Functions




;;; The g2-list operations build upon the basic g2-list structure operations.
;;; These operations require that the elements be only values or item.  But,
;;; these operations do not check if the element type matches that of the
;;; g2-list.  This is handled in the evaluators and actions.  Also, note that a
;;; record is maintained of the g2-lists that an item is a member of.  (The
;;; record is maintained in a slot of the item.)



;; Note that we don't need to define g2-list-p.  The definition of the g2-list
;; class already does that.


(defun-simple g2-list-empty-p (g2-list)
  (g2-list-structure-empty-p (list-structure g2-list)))



;;; The function `g2-list-length' counts the number of elements in the g2-list.
;;; Note that this function assumes that the list only contains valid elements
;;; and does not check for active or serveable elements.

(defun-simple g2-list-length (g2-list)
  (if (active-p g2-list)
      (let ((g2-list-structure (list-structure g2-list)))
	(loop for element being g2-list-structure-element of g2-list-structure
	      count t))
      0))



;;; The function `g2-list-member-p' is a predicate that tests if an item or
;;; value is found in a g2-list.

(defun-simple g2-list-member-p (item-or-evaluation-value g2-list)
  (not
    (null
      (if (and (evaluation-float-p item-or-evaluation-value)
	       (exceptional-float-p (evaluation-float-value item-or-evaluation-value)))
	  (find-exceptional-float-in-g2-list
	    item-or-evaluation-value g2-list)
	  (find-g2-list-element-structure
	    item-or-evaluation-value g2-list nil t)))))



;;; The function `clear-g2-list' removes all elements from the g2-list.  The
;;; associated g2-list-element structures and any evaluation-values are
;;; reclaimed.  If an item is removed from a list, the record of lists that the
;;; item belongs to is updated.  This function returns T if the g2-list was
;;; initialized (i.e., contained a g2-list-structure); otherwise NIL.

(defun-simple clear-g2-list (g2-list)
  (note-change-to-runtime-data-for-block g2-list)
  (let ((g2-list-structure (list-structure g2-list))
	(initialized-g2-list-cleared? nil))
    (let ((open-continuations (list-open-continuations g2-list)))
      (when open-continuations
	(loop for continuation in open-continuations
	      do
	  (setf (second continuation) nil))
	(reclaim-eval-list-function open-continuations)
	(setf (list-open-continuations g2-list) nil)))
    (when g2-list-structure
      (let ((item-list 
	      (loop for element-structure being g2-list-structure-element of g2-list-structure
		    for item-or-value = (list-element-value element-structure)
		    when (framep item-or-value)
		      collect (progn
				(setf (list-element-value element-structure) nil)
				item-or-value)
			using g2-list-cons)))
	(loop for item in item-list
	      do (loop with first-cons = nil
		       with last-cons = nil
		       for current-cons = (list-elements-for-item item)
					then next-cons
		       while current-cons
		       for (element-structure . next-cons) = current-cons
		       do (cond ((list-element-value element-structure)
				 (setq last-cons current-cons)
				 (unless first-cons
				   (setq first-cons current-cons)))
				(t
				 (if last-cons
				     (setf (cdr last-cons) next-cons)
				     (setf first-cons next-cons))
				 (reclaim-g2-list-cons current-cons)))
		       finally (setf (list-elements-for-item item) first-cons)))
	(reclaim-g2-list-list item-list))
      (g2-list-structure-clear g2-list-structure)
      (setq initialized-g2-list-cleared? t))
    (setf (list-size g2-list) 0)
    (update-representations-of-slot-value g2-list 'list-size)
    initialized-g2-list-cleared?))



;;; The function `delete-g2-list' is similar to clear-g2-list except that the
;;; g2-list-structure is deleted and reclaimed.  The g2-list is no-longer
;;; initialized.

(defun-simple delete-g2-list (g2-list)
  (when (clear-g2-list g2-list)
    (reclaim-g2-list-element-macro (list-structure g2-list))
    (setf (list-structure g2-list) nil)
    (setf (list-size g2-list) 0)
    (update-representations-of-slot-value g2-list 'list-size)))



;;; The function `clone-g2-list-structure-when-necessary' copies the
;;; list-structure and its elements unless the system is reset.  (When reset,
;;; the list-structure is allocated on activation.)

#+unused
(defun-simple clone-g2-list-structure-when-necessary (g2-list target-g2-list)
  (when (or system-has-paused system-is-running)
    (copy-g2-list-structure g2-list target-g2-list)))



;;; The function `copy-g2-list-structure' is used to copy the list-structure and
;;; elements of a g2-list.  (Evaluation-values and pointers to frames are
;;; copied.  New frames are not created.)  A new list-structure is allocated
;;; when necessary.  Note that the list-elements for item-slot for the copied
;;; item-elements is also updated.

#+unused
(defun-simple copy-g2-list-structure (g2-list target-g2-list)
  (let ((list-structure (list-structure g2-list))
	(target-list-structure
	  (or (list-structure target-g2-list)
	      (create-empty-g2-list-structure))))
    (setf (list-structure target-g2-list) target-list-structure)
    (when list-structure
      (loop for element-structure being g2-list-structure-element of list-structure
	    for item-or-value = (list-element-value element-structure)
	    with new-element-item-or-value = nil
	    do
	(setq new-element-item-or-value
	      (copy-if-evaluation-value item-or-value))
	;; Insert the element at the end of the list.  Update the
	;; list-elements-for-item slot when necessary.  Don't check for
	;; duplicates elements.  This function calls note-change-to-runtime-
	;; data-for-block.
	(g2-list-insert-at-end new-element-item-or-value target-g2-list t)))))



;;; The function `find-g2-list-element-structure' searches a g2-list for an
;;; item or value and if found returns the associated g2-list-element-
;;; structure.

;;; If the list can contain duplicate elements, by default, this function
;;; returns the element closest to the start of the list.  (Note that there is
;;; an exception when the item-search-memq-test-returns-any-position? argument
;;; is non-NIL.)  This feature is important for the REMOVE action.  When
;;; iterating over and removing items from a list that contains duplicate items,
;;; the current element is removed and not one later in the list.  In this way,
;;; all elements can be removed in one iteration and the REMOVE action now has a
;;; guaranteed behavior.

;;; Two new arguments were added for the G2 4.0 release:
;;; - search-begins-at-element-structure?
;;; - item-search-memq-test-returns-any-position?

;;; The SEARCH-BEGINS-AT-ELEMENT-STRUCTURE?, if non-NIL, specifies which element
;;; location to begin the search.  Note that this value, if non-NIL, must be a
;;; valid element-structure for the given g2-list and must contain an element.
;;; (Validation is not done because this would involve searching the list, which
;;; defeats the optimization.)  If the argument is nil, all elements are
;;; searched for the given non-item element. Note that a non-NIL value for this
;;; argument causes the function to ignore the value of item-search-memq-test-
;;; returns-any-position? argument.  (In other words, the function returns the
;;; closest element that follows the given element-structure.)

;;; When non-NIL, the ITEM-SEARCH-MEMQ-TEST-RETURNS-ANY-POSITION? argument
;;; specifies that, when searching for an item, this function can return any
;;; element-structure which contains the item.  In this case, the caller is only
;;; interested in knowing that the item is in the list (i.e., a member test) and
;;; does not need to find the element closest to the start of the list.  This
;;; argument can provide an optimization by looking the lists that an item
;;; belongs to, even when the list may contain the item more than once, instead
;;; of searching through the given list.  (IMPORTANT: Note that this argument is
;;; ignored if search-begins-at-element-structure? is non-NIL!)

;;; IMPORTANT: This function should be called from within a TEMPORARY
;;; GENSYM-FLOAT AREA!  This function can access evaluation-float-values of
;;; g2-list elements, which conses a gensym-float.

(defun-simple find-g2-list-element-structure
    (item-or-evaluation-value
      g2-list
      search-begins-at-element-structure?
      item-search-memq-test-returns-any-position?)
  ;; Note that item-search-memq-test-returns-any-position? is not used if
  ;; search-begins-at-element-structure? is non-NIL!
  (let ((search-g2-list? t)
	(element? nil))
    (cond
      ((g2-list-empty-p g2-list)
       (setq search-g2-list? nil))
      ((or search-begins-at-element-structure?
	   (not (framep item-or-evaluation-value)))
       ;; For non-item elements, do the linear search, below.
       nil)
      (t
       ;; When searching for an item element and not starting from a given
       ;; element location, check the g2-lists that the item belongs to.
       (loop with first-element-location? = nil
	     for element-structure in
	       (list-elements-for-item item-or-evaluation-value)
	     until (or element? (null search-g2-list?))
	     do
	 (when (eq (list-frame element-structure) g2-list)
	   (cond
	     ((null first-element-location?)
	       ;; The first instance of the element was found.  Continue
	       ;; checking for other locations in the g2-list, if necessary.
	      (setq first-element-location? element-structure)
	      (when item-search-memq-test-returns-any-position?
		(setq element? first-element-location?)
		(setq search-g2-list? nil)))
	     (t
	      ;; The element is in the g2-list more than once.  Stop searching
	      ;; here.  Continue searching below looking for the first instance
	      ;; of this element.
	      (setq search-g2-list? t)
	      (return))))
	     finally
	       ;; The element was either not found or was found in the g2-list
	       ;; only once.  Don't do the linear search below.
	       (setq element? first-element-location?)
	       (setq search-g2-list? nil))))
    (cond
      ((null search-g2-list?)
       ;; Return either the element found or NIL.
       element?)
      (t
       ;; Linear search from the given location or start of list.
       (let ((g2-list-structure (list-structure g2-list)))
	 (when g2-list-structure
	   (loop for element-structure
		     = (or search-begins-at-element-structure?
			   #-Lockfree-List
			   (g2-list-structure-head g2-list-structure)
			   #+Lockfree-List
			   (g2-list-structure-next
			     (g2-list-structure-head g2-list-structure)
			     g2-list-structure))
		     then (g2-list-structure-next element-structure g2-list-structure)
		 until (or #-Lockfree-List (eq element-structure g2-list-structure)
			   #+Lockfree-List (null element-structure)
			   element?)
		 for element-value = (list-element-value element-structure)
		 do
	     (cond ((framep element-value)
		    (when (eq item-or-evaluation-value element-value)
		      (setq element? element-structure)))
		   ((evaluation-value-= item-or-evaluation-value element-value)
		    (setq element? element-structure)))
		 finally
		   ;; Return either the element or NIL.
		   (return element?))))))))

(defun-simple find-g2-list-element-structure-at-position (g2-list position)
  (let ((g2-list-structure (list-structure g2-list))
	(element? nil))
    (unless (fixnump position)
      (stack-error
	cached-top-of-stack
	"The position given for a list is ~a, but it must be an integer." position))
    (when (and g2-list-structure
	       (>f (g2-list-length g2-list) position))
      (loop for element-structure being g2-list-structure-element of g2-list-structure
	    for index from 0
	    until (>f index position)
	    until element?
	    do
	(when (=f index position)
	  (setq element? element-structure))))
    element?))




;;; `find-exceptional-float-in-g2-list' is just designed to work with exceptional-floats (Nan & +- Inf)
;;; it is necessary because the standard IEEE comparison functions always return false in the face of Nan's

(defun-simple find-exceptional-float-in-g2-list
    (evaluation-float g2-list)
  (let ((search-g2-list? t)
	(element? nil)
	(exceptional-float-byte-1 nil)
	(exceptional-float-byte-2 nil)
	(exceptional-float-byte-3 nil)
	(exceptional-float-byte-4 nil))
    (cond
      ((g2-list-empty-p g2-list)
       (setq search-g2-list? nil))
      ((not (and (evaluation-float-p evaluation-float)
		 (exceptional-float-p (evaluation-float-value evaluation-float))))
       (setq search-g2-list? nil))
      (t
       (multiple-value-setq (exceptional-float-byte-1
			      exceptional-float-byte-2
			      exceptional-float-byte-3
			      exceptional-float-byte-4)
	 (partition-float (evaluation-float-value evaluation-float)))
       (let ((g2-list-structure (list-structure g2-list)))
	 (when g2-list-structure
	   (loop for element-structure being g2-list-structure-element of g2-list-structure
		 for element-value = (list-element-value element-structure)
		 with float-value
		 until element?
		 do
	     (when (evaluation-float-p element-value)
	       (setq float-value (evaluation-float-value element-value))
	       (when (exceptional-float-p float-value)
		 (multiple-value-bind (test-float-byte-1
					test-float-byte-2
					test-float-byte-3
					test-float-byte-4)
		     (partition-float float-value)
		   (when (and (=f exceptional-float-byte-1 test-float-byte-1)
			      (=f exceptional-float-byte-2 test-float-byte-2)
			      (=f exceptional-float-byte-3 test-float-byte-3)
			      (=f exceptional-float-byte-4 test-float-byte-4))
		     (setq element? element-structure)))))
		 finally
		   ;; Return either the element or NIL.
		   (return element?))))))))






;;;; G2-List and G2-Arrays Grammar Support




;; Note that the grammar for g2-lists has been moved to the grammar modules.
;; -27sep89, cpm



;;; Existing g2-list EXPRESSION grammar in version 3.x

;;; <g2-list-or-array> [ <integer-expression> ]
;;; the {first | second | next to last | last} <element-type> in <list>
;;; {the | any | each}  <element-type> [local-name] in {<g2-list-or-array>}
;;; <element-type> is [not] a member of the <list-type> list <list>
;;; the number of elements in <list>
;;; the {sum | product | average | minimum | maximum} over each <element-type> 
;;;   [<local-name>] in <g2-list-or-array> of (<expression>)
;;; the count of each <element-type> in {g2-list-or-array> [such that
;;;   ( <local-expression> )]

;;; Existing g2-list ACTION grammar in version 3.x

;;; change <g2-list-or-array> [ <integer-expression> ] = <item-or-value>
;;; conclude that <g2-item-list-or-arry> [ <integer-expression> ] 
;;;   {= <expression> | is <symbol>}
;;; insert <item-or-value>
;;;   {at the {beginning | end} of |
;;;    {before | after} <item-or-value-element> in}
;;;   the <element-type> list <g2-list>
;;; remove 
;;;   {<item-or-value-element> from the <element-type> list <g2-list> |
;;;   the {first | last} <element-type> from <g2-list>}



;;; Proposed g2-list EXPRESSION grammar in version 4.0:

;;; 1. No change:
;;; <g2-list-or-array> [ <integer-expression> ]

;;; 2. Possibly change: (decided not to change)
;;; the number of elements in <list>
;;;  Change to allow "the number of <element-types> in <list>" ?
;;;    Remove the phrase "elements" from the grammar? (Is this used anywhere
;;;    else? Is it a reserved word in G2?)
;;;    Will not make any changes in this expression.   The user can use
;;;    the "the count of each <element-type> in <g2-list-or-array>" expression.
;;;  Is this expression needed?  Keep it for compatibility.

;;; 3. new <element-type>: value, item-or-value
;;; the {first | second | next to last | last} <element-type> in <list>
;;; {the | any | each}  <element-type> [local-name] in {<g2-list-or-array>}
;;; the {sum | product | average | minimum | maximum} over each <element-type> 
;;;   [<local-name>] in <g2-list-or-array> of (<expression>)
;;; the count of each <element-type> in {g2-list-or-array> [such that
;;;   ( <local-expression> )]

;;; 4. Replace "the <list-type> list <list>" with "<list>".
;;;    Support old grammar.
;;; <element-type> is [not] a member of <list>



;;; Proposed ACTION grammar in version 4.0:

;;; 1. No change:
;;; change <g2-list-or-array> [ <integer-expression> ] = <item-or-value>
;;; conclude that <g2-item-list-or-arry> [ <integer-expression> ] 
;;;   {= <expression> | is <symbol>}

;;; 2. new <element-type>: value, item-or-value
;;; remove the {first | last} <element-type> from <g2-list>}

;;; 3. Replace "the <list-type> list <list>" with "<list>".
;;;    Support old grammar.
;;; insert <item-or-value>
;;;   {at the {beginning | end} of |
;;;   {before | after} <item-or-value-element> in}
;;;   <g2-list>
;;; remove <item-or-value-element> from <g2-list>








;;;; G2 List and Array Element Testing Functions




;;; The function `g2-list-or-array-element-ok-p' is a predicate that tests if a
;;; g2-list or g2-array element is compatible with the list or array's element
;;; type.

;;; Note that the element argument must be an item or evaluation-value.

;;; For item elements, this functions tests if the item is an instance of the
;;; element type or an instance of a subclass of the element type.  For value
;;; elements, this function tests if the evaluation-value is a type of subtype
;;; of the element type.

(defun-simple g2-list-or-array-element-ok-p
    (item-or-evaluation-value g2-list-or-array-element-type)
  (if (framep item-or-evaluation-value)
      (item-ok-for-g2-list-or-array-p
	item-or-evaluation-value g2-list-or-array-element-type)
      (datum-ok-for-g2-list-or-array-p
	item-or-evaluation-value g2-list-or-array-element-type)))



;;; The function `item-ok-for-g2-list-or-array-p' is a predicate that tests if
;;; the given item is compatible with list or array element type.  Compatible
;;; means that the element type is a class and that the item is either an
;;; instance of the class or an instance of a subclass.

(defun-simple item-ok-for-g2-list-or-array-p
    (item g2-list-or-array-element-type)
  (let ((element-type
	 (or (type-specification-for-user-or-datum-type
	       g2-list-or-array-element-type)
	     ;; Otherwise, is a class name and not item-or-datum.
	     g2-list-or-array-element-type)))
    (cond ((eq element-type 'item-or-datum)
	   (frame-of-class-p item 'item)) ; Verify the item arg.
	  ((consp g2-list-or-array-element-type)
	   nil)
	  (t
	   ;; Fails if it is not of the class or if the class is not defined.
	   (frame-of-class-p item g2-list-or-array-element-type)))))



;;; The macro `item-ok-for-item-list-or-item-array-p' is a predicate that tests
;;; if the given item is compatible with the array or list, when we know that
;;; the element type is either item or a subclass of item.

(def-substitution-macro item-ok-for-item-list-or-item-array-p
    (item item-element-type)
  (frame-of-class-p item item-element-type))



;;; The function `datum-ok-for-g2-list-or-array-p' tests that a datum element
;;; (i.e., an evaluation-value) is compatible with the given g2-list or g2-array
;;; element type.

(defun-simple datum-ok-for-g2-list-or-array-p
    (evaluation-value g2-list-or-array-element-type)
  (let ((datum-element-type-specification?
	 ;; Returns valid datum type-specification, item-or-datum, or nil.
	 (type-specification-for-user-or-datum-type
	   g2-list-or-array-element-type)))
    (when (eq datum-element-type-specification? 'item-or-datum)
      ;; Item-or-datum is not an evaluat-value datum-type.
      (setq datum-element-type-specification? 'datum))
    (and datum-element-type-specification?
	 (evaluation-value-p evaluation-value)
	 (evaluation-value-of-type-p
	   evaluation-value datum-element-type-specification?))))






;;;; G2 List and Array Typing-Related Functions




;;; `G2-list-or-array-element-type' returns the element type for
;;; g2-list-or-array, which should be an item either of class g2-list or of
;;; class g2-array.

;;; An `element type' either a base type of evaluation value, or ITEM, or
;;; ITEM-OR-DATUM, or DATUM.  I.e., one of the following symbols:
;;;
;;;    NUMBER, INTEGER, FLOAT
;;;    TEXT, TRUTH-VALUE, SYMBOL
;;;    ITEM, DATUM, ITEM-OR-DATUM

(defun-simple g2-list-or-array-element-type (g2-list-or-array)
  ;; Because this does a of-class-p test:
  ;;  Test integer and float before quantity;
  ;;  Test item-or-datum last, and datum next to last.
  (frame-class-case g2-list-or-array
    ((integer-list integer-array) 'integer)
    ((float-list float-array) 'float) ; note: these are subclasses of quantity
    ((quantity-list quantity-array) 'number)
    ((text-list text-array) 'text)
    ((truth-value-list truth-value-array) 'truth-value)
    ((symbol-list symbol-array) 'symbol)
    ((item-list item-array) type-specification-for-item) ; Is (class item)
    ((value-list value-array) 'datum)
    ((g2-list g2-array) 'item-or-datum)
    (t #+development
       (error "Type of g2-list or g2-array elements unknown for ~a"
	      g2-list-or-array)
       nil)))

;; Review the above function, if we allow the user to edit the element-type
;; of non-item arrays or lists.  - cpm, 11/3/93



;;; The function `g2-list-or-array-class-element-type' takes a symbol which may
;;; name a class of g2-lists.  This function returns a type specification of the
;;; kind of values that may be held in that class of list if it can be
;;; determined, or else it returns nil.

;;; Note that if the second argument is non-nil, it means that the this function
;;; will only return the element type of pre-defined system g2-list or g2-array
;;; classes.  This is useful in non-stable expression compilation, when the
;;; compiler cannot depend on user-defined classes.

(defun-simple g2-list-or-array-class-element-type
    (class-name system-class-only-p?)
  (cond (system-class-only-p?
	 ;; Doesn't test for subclasses of system-defined g2-array and g2-list
	 ;; classes.
	 (case class-name
	   ((integer-list integer-array) 'integer)
	   ((float-list float-array) 'float)
	   ((quantity-list quantity-array) 'number)
	   ((text-list text-array) 'text)
	   ((truth-value-list truth-value-array) 'truth-value)
	   ((symbol-list symbol-array) 'symbol)
	   ((item-list item-array) '(class item))
	   ((value-list value-array) 'datum)
	   ((g2-list g2-array) 'item-or-datum)
	   (t nil)))
	;; Test for subclasses.
	((or (subclassp class-name 'integer-list)
	     (subclassp class-name 'integer-array))
	 'integer)
	((or (subclassp class-name 'float-list)
	     (subclassp class-name 'float-array))
	 'float)
	;; Test integer and float before quantity.
	((or (subclassp class-name 'quantity-list)
	     (subclassp class-name 'quantity-array))
	 'number)
	((or (subclassp class-name 'text-list)
	     (subclassp class-name 'text-array))
	 'text)
	((or (subclassp class-name 'truth-value-list)
	     (subclassp class-name 'truth-value-array))
	 'truth-value)
	((or (subclassp class-name 'symbol-list)
	     (subclassp class-name 'symbol-array))
	 'symbol)
	((or (subclassp class-name 'item-list)
	     (subclassp class-name 'item-array))
	 '(class item))
	;; Test all array and list classes first, except for g2-array and
	;; g2-list.
	((or (subclassp class-name 'value-list)
	     (subclassp class-name 'value-array))
	 'datum)
	;; Test all other array and list types before g2-list and g2-array.
	((or (subclassp class-name 'g2-list)
	     (subclassp class-name 'g2-array))
	 'item-or-datum)
	(t nil)))

;; Review the above function, if we allow the user to edit the element-type
;; of non-item arrays or lists.  - cpm, 11/3/93



;;; The function `g2-list-or-array-class-for-element-type' returns the class of
;;; the given g2-array or g2-list based on the element-type argument.  Note that
;;; non-datum, non-item-or-datum element-types are returned as item-array or
;;; item-list.  The g2-array-p? controls a g2-array or g2-list class is
;;; returned.

(defun-simple g2-list-or-array-class-for-element-type (element-type g2-array-p?)
  (cond (g2-array-p?
	 (case element-type
	   (integer 'integer-array)
	   (float 'float-array)
	   ((number quantity) 'quantity-array)
	   (text 'text-array)
	   (truth-value 'truth-value-array)
	   (symbol 'symbol-array)
	   (item 'item-array)
	   (datum 'value-array)
	   (item-or-datum 'g2-array)
	   (t
	    (if (not (valid-datum-type-specification-p element-type))
		'item-array
		'g2-array))))
	(t
	 (case element-type
	   (integer 'integer-list)
	   (float 'float-list)
	   ((number quantity) 'quantity-list)
	   (text 'text-list)
	   (truth-value 'truth-value-list)
	   (symbol 'symbol-list)
	   (item 'item-list)
	   (datum 'value-list)
	   (item-or-datum 'g2-list)
	   (t
	    (if (not (valid-datum-type-specification-p element-type))
		'item-list
		'g2-list))))))



;;; The function `g2-list-or-array-element-type-may-contain-item-p' is given an
;;; element type and checks if the array or list may contain items.  Note the
;;; element type argument is in the form that is contained in the g2-list or
;;; g2-array element type attribute.  Note that this function does not test if
;;; the class of an item element type is defined.

(defun-simple g2-list-or-array-element-type-may-contain-item-p (element-type)
  (not (symbolic-type-specification-subtype-p element-type 'datum)))



;;; The function `g2-list-or-array-type-ok-p' is a predicate that tests that a
;;; g2-list or g2-array element-type specified in the grammar (required-type) is
;;; compatible with the g2-list type.

;;; By default, compatible means that the required type is a superior of the
;;; list type.  But, if the subtype-of-list-type arg is non-nil, then the
;;; required type can also be a subtype of the list type.  See the functions
;;; called here for more documentation.

(defun-simple g2-list-or-array-type-ok-p
    (required-element-type list-type subtype-of-list-type-ok-p?)
  (or (eq required-element-type list-type)
      (required-datum-type-ok-for-g2-list-or-array-p
	required-element-type list-type subtype-of-list-type-ok-p?)
      (required-item-type-ok-for-g2-list-or-array-p
	required-element-type list-type subtype-of-list-type-ok-p?)))


;;; The functions `required-datum-type-ok-for-g2-list-or-array-p' and
;;; `required-item-type-ok-for-g2-list-or-array-p' test that the required
;;; element type is compatible with the g2-list or g2-array element type.

;;; By default, compatible means that the required type is a superior element
;;; type of the element type.  For example, if an expression requires an element
;;; type of item, then an list or array element-type of variable is okay.

;;; But, if the subtype-of-element-type-ok-p? argument is non-nil, then the
;;; required type can be a subtype, as well as a superior type, of the array or
;;; list type.  This is useful, for example, when iterating over items in a list
;;; by class, such as when serving the water-tanks from a tank list.  Note that
;;; this should not be allowed in "insert x into the integer list
;;; quantity-list-1" where integer is the required type (i.e., specified in the
;;; grammar) and quantity is the list type.

(defun-simple required-datum-type-ok-for-g2-list-or-array-p
       (required-datum-type g2-list-element-type subtype-of-element-type-ok-p?)
  (or (g2-list-or-array-datum-subtype-p
	g2-list-element-type required-datum-type)
      (and subtype-of-element-type-ok-p?
	   (g2-list-or-array-datum-subtype-p
	     required-datum-type g2-list-element-type))))

(defun-simple required-item-type-ok-for-g2-list-or-array-p
    (required-item-type g2-list-element-type subtype-of-element-type-ok-p?)
  (or (eq required-item-type g2-list-element-type)
      (g2-list-or-array-item-subtype-p
	g2-list-element-type required-item-type)
      (and subtype-of-element-type-ok-p?
	   (g2-list-or-array-item-subtype-p
	     required-item-type g2-list-element-type))))



;;; The functions `g2-list-or-array-datum-subtype-p' and
;;; `g2-list-or-array-item-subtype-p' check that the give the type is a subtype
;;; of the superior type.  Note the type arguments are in the form that are
;;; contained in the g2-list or g2-array element type.  Therefore, these
;;; functions validate and convert their arguments to a type-specification
;;; format when necessary.

(defun-simple g2-list-or-array-datum-subtype-p
    (datum-type superior-datum-type)
  (let ((internal-datum-type?
	 ;; Returns valid datum type-specification or item-or-datum.
	 (type-specification-for-user-or-datum-type datum-type))
	(internal-superior-datum-type?
	 ;; Returns valid datum type-specification or item-or-datum.
	 (type-specification-for-user-or-datum-type superior-datum-type)))
    (and internal-datum-type?
	 internal-superior-datum-type?
	 (or (eq internal-datum-type? internal-superior-datum-type?)
	     (type-specification-subtype-p
	       internal-datum-type? internal-superior-datum-type?)))))

(defun-simple g2-list-or-array-item-subtype-p
    (item-type superior-item-type)
  ;; A valid item-type is of the form { <class> | item-or-value }.
  (let* ((internal-datum-type?
	  (type-specification-for-user-or-datum-type item-type))
	 (internal-item-type?
	  (cond ((null internal-datum-type?) item-type)
		((eq internal-datum-type? 'item-or-datum) 'item-or-datum)
		;; Else, datum-type
		(t nil)))
	 (internal-superior-datum-type?
	  (type-specification-for-user-or-datum-type superior-item-type))
	 (internal-superior-item-type?
	  (cond ((null internal-superior-datum-type?) superior-item-type)
		((eq internal-superior-datum-type? 'item-or-datum)
		 'item-or-datum)
		;; Else, datum-type
		(t nil))))
    ;; Cases to check:
    ;;   item-or-datum, item-or-datum: T;
    ;;   <class>, <class>: EQ test;
    ;;   item-or-datum, <class>: if class is ITEM-OR-DATUM, return T;
    ;;   <class>, item-or-datum: subclass check of ITEM;
    ;;   <class>, <class>: subclass check.
    (cond
      ((or (null internal-item-type?) (null internal-superior-item-type?))
       ;; One type is a non-item-or-datum data-type.
       nil)
      ((eq internal-item-type? internal-superior-item-type?)
       ;; Equal classes or both types are item-or-datum.
       t)
      ((eq internal-item-type? 'item-or-datum)
       ;; We already know, based on the first test, that the superior type is
       ;; not item-or-datum.  So, they cannot be subtypes of each other.
       nil)
      ((eq internal-superior-item-type? 'item-or-datum)
       ;; The internal type is not item or datum, so test only for item
       ;; subclasses.
       (subclassp internal-item-type? 'item))
      (t
       ;; Else, both types should be ITEM or a subclass of ITEM.
       (subclassp internal-item-type? internal-superior-item-type?)))))

;; Note that the above function would be easier (and maybe unnecessary) if
;; g2-list and g2-array element-types were the same format as datum and class
;; type-specifications.  See the SETS module.  - cpm, 11/3/93






;;;; Accessing Elements From a G2-List




;;; Given a g2-list, the `g2-list-element iteration' is useful for iterating
;;; over the elements of a g2-list.
;;;   Note that the element value is either an evaluation-value or an item.
;;;   Note that all elements are served.  Item elements are not tested for
;;; servability.  This should be done with server-item-p, if necessary.
;;;   Note that the actual evaluation-values are iterated over.  These should
;;; *not* be reclaimed or held onto.  They can be referenced with evaluation-
;;; value-p, evaluation-value-value, and copy-evaluation-value.
;;;
;;; EXAMPLE:
;;;  (loop for item-or-evaluation-value-element
;;;        being each g2-list-element in my-g2-list
;;;     collect
;;;        (if (evaluation-value-p item-or-evaluation-value-element)
;;;            (copy-evaluation-value element)
;;;            item-or-evaluation-value-element))
;;;     using gensym-cons
;;;   OR
;;;  (loop for x being each g2-list-element in my-g2-list do (foo x)

(defun-for-macro g2-list-element-path
    (path-name variable data-type prep-phrases inclusive? allowed-prepositions
	       data)
  (declare (ignore data-type data allowed-prepositions))
  (when (null prep-phrases)
    (error "IN is missing in ~S iteration path of ~S" path-name variable))
  (when inclusive?
    (error
      "Inclusive stepping is not supported in ~S path of ~S (prep-prase = ~:S)"
      path-name variable prep-phrases))
  (let* ((iteration-domain (cadar prep-phrases))
	 (list-structure-variable (loop-gentemp))
	 (element-structure-variable (loop-gentemp))
	 (generator-bindings `((,list-structure-variable
				  (list-structure ,iteration-domain))
			       (,element-structure-variable nil)
			       (,variable nil)))
	 (generator-initialize
	   `((setq, element-structure-variable
		    (when ,list-structure-variable
		      #-Lockfree-List (g2-list-structure-head ,list-structure-variable)
		      #+Lockfree-List (g2-list-structure-next
				        (g2-list-structure-head ,list-structure-variable)
					,list-structure-variable)))))
	 (generator-end-p
	   #-Lockfree-List
	   `(eq ,element-structure-variable ,list-structure-variable)
	   #+Lockfree-List
	   `(null ,element-structure-variable))
	 (generator-advance
	   ;; Setq variable before element-structure-variable!
	   `(,variable
	       (list-element-value ,element-structure-variable)
	       ,element-structure-variable
	       (g2-list-structure-next ,element-structure-variable
				       ,list-structure-variable))))
    `(,generator-bindings
	,generator-initialize
	nil
	nil
	,generator-end-p
	,generator-advance)))

(define-loop-path (g2-list-elements g2-list-element)
		  g2-list-element-path (in))




;;; `Convert-permanent-list-structure-for-saving' produces a lisp-style list
;;; from the values in the g2-list-structure.  This list will be saved out as
;;; the value of the list-structure slot of g2-lists.

(defun-simple convert-permanent-list-structure-for-saving (g2-list)
  (if (or (list-is-permanent g2-list)
	  (save-runtime-data? current-kb-save))
      (let ((current-module-being-saved? (kb-module-being-saved? current-kb-save)))
	(loop for list-element being each g2-list-element in g2-list
	      for list-element-to-save?
	          = (if (framep list-element)
			(if (collectable-block-p list-element)
			    (let ((frame-denotation-to-save?
				    (if (or (eq (get-module-block-is-in list-element)
						current-module-being-saved?)
					    ;; Kb-module-being-saved?  will be null when the kb is
					    ;; being saved into a single file. See make-saving-
					    ;; context in KB-SAVE3.
					    (null current-module-being-saved?))
					list-element
					(block-denotation-p list-element))))
			      (cond ((framep frame-denotation-to-save?)
				     frame-denotation-to-save?)
				    (frame-denotation-to-save?
				     (slot-value-list
				       'frame-denotation frame-denotation-to-save?))
				    (t nil)))
			    nil)
			(if (deleted-frame-p list-element)
			    nil
			    (copy-for-slot-value list-element)))
	      when list-element-to-save?
		collect list-element-to-save?
		  using slot-value-cons))
      nil))

;;; The post-loading function `convert-saved-list-values-to-g2-list-structure'
;;; converts the lisp list saved as the value of the list-structure slot of
;;; g2-lists into g2-list-structures.  When a list value is an uuid and
;;; there is no corresponding frame reference, the default value is used
;;; instead.

(def-post-loading-function (convert-saved-list-values-to-g2-list-structure
			     :once-only t)
  (loop for g2-list being each class-instance of 'g2-list
	for saved-list-values = (list-structure g2-list)
	do
    (when (and saved-list-values (listp saved-list-values))
      (if warmbooting?
	  ;; We will use the squirrelled data because it covers
	  ;; both permanent and transient lists.  See unsquirrel-data-
	  ;; for-block.
	  (progn
	    (setf (list-structure g2-list) nil)
	    (reclaim-slot-value saved-list-values))
	(progn
	  (setf (list-structure g2-list)
		(create-empty-g2-list-structure))
	  (loop for value in saved-list-values
		for value-to-set? = (cond ((and (consp value)
						(eq (car-of-cons value)
						    'frame-denotation))
					   (find-frame-for-denotation
					     (second value) 'block))
					  ((framep value)
					   value)
					  ((deleted-frame-p value)
					   nil)
					  (t
					   (copy-for-slot-value value)))
		do
	    (g2-list-insert-at-end value-to-set? g2-list t) ; override any test for duplicates
		finally (reclaim-slot-value saved-list-values)))))))




;;; The non-standard macro `do-g2-list-elements' can be used to iterate over the
;;; elements (datum or items) in a g2-list.  This macro is similar to do-list
;;; and do-g2-array-elements.  Here the caller provides a new local variable
;;; name for the element, which is not evaluated, a g2-list, a result-form, and
;;; a body of code for the iteration.  During each iteration of the loop the
;;; element is let bound into the named local variable.  The body of code may,
;;; of course, reference this variable.

;;; The element value is either an item, a evaluation-value, or nil, which means
;;; no-value.  If an item in an item-list is inactive or deleted, the element
;;; value is nil, which means no-value.

;;; IMPORTANT:
;;; 1. Note that the actual element values (items and evaluation-values) are
;;; returned.  The evaluation-values should be copied, when necessary, and not
;;; held onto!
;;; 2. Note that if you are return g2-list-element items to the user, you should
;;; test each item with the predicate serve-item-p.

;;; Example usage:
;;;    (do-g2-list-elements (element-value my-g2-list nil)
;;;      (foo element-value))

;;; The macro is non-standard since only the g2-list argument is evaluated.

(defmacro do-g2-list-elements ((new-local-var g2-list result-form) &body body)
  (let ((g2-list-var (gensym)))
    `(loop with ,g2-list-var = ,g2-list
	   for ,new-local-var being each g2-list-element in ,g2-list-var
	   do
       ,@body
	   finally
	     (return ,result-form))))



;;; The function `g2-list-elements' returns a LISP list of g2-list elements,
;;; which are either items or values.  This list is created using g2-list
;;; conses.
;;; Note the following:
;;;   By default, value elements, which are implemented as evaluation-values,
;;; are not copied.  The actual element value is returned.  Be careful not to
;;; reclaim or hold onto this value!  The evaluation-value element is copied
;;; if the copy-value-elements? argument is non-nil.
;;;   IMPORTANT: This list must be reclaimed by the caller using.  For example,
;;; use reclaim-g2-list-list.



(defun g2-list-elements (g2-list &optional (copy-value-elements? nil))
  (if copy-value-elements?
      (loop for element-value being each g2-list-element in g2-list
	    collect (if (evaluation-value-p element-value)
			(copy-evaluation-value element-value)
			element-value)
	      using g2-list-cons)
      (loop for element-value being each g2-list-element in g2-list
	    collect element-value using g2-list-cons)))



;;; The functions `g2-list-first', `g2-list-second', `g2-list-next-to-last', and
;;; `g2-list-last' return the indicated item or value (evaluation-value) element
;;; from the g2-list.

;;; If element-type? is non-NIL, the element is required to be of the specific
;;; element type.  (This then returns subclasses of the element type also.)
;;; Note that returning the nth element of an element type is not necessarily
;;; the nth element in the list.  It is the nth instance of the element type (or
;;; subclass of the element type) from the beginning of the list.

;;; If return-element-structure? is non-NIL, the element-structure is returned
;;; instead of the element.

;;; IMPORTANT: Note that these accessors return items or evaluation-values.  The
;;; evaluation-values are copies of the element values and so are owned and
;;; should be RECLAIMED by the caller, when necessary.

(defun-simple g2-list-first (g2-list element-type? return-element-structure?)
  (nth-g2-list-element 0 g2-list element-type? return-element-structure?))

(defun-simple g2-list-second (g2-list element-type? return-element-structure?)
  (nth-g2-list-element 1 g2-list element-type? return-element-structure?))

(defun-simple g2-list-last (g2-list element-type? return-element-structure?)
  (nth-from-end-g2-list-element
    0 g2-list element-type? return-element-structure?))

(defun-simple g2-list-next-to-last
    (g2-list element-type? return-element-structure?)
  (nth-from-end-g2-list-element
    1 g2-list element-type? return-element-structure?))


(defun-simple nth-g2-list-item-or-evaluation-value
    (nth g2-list copy-evaluation-value-element?)
  (loop for element-value being each g2-list-element in g2-list
	for element-count = 0 then (1+f element-count)	
	do
    ;; The list is not empty. There is at least one element.
    (when (=f element-count nth)
      (return
	(if (and copy-evaluation-value-element?
		 (evaluation-value-p element-value))
	    (copy-evaluation-value element-value)
	    element-value)))
    ;; Return NIL if the nth element is not found.
	finally (return nil)))


(defun-simple nth-g2-list-element
    (nth g2-list element-type? return-element-structure?)
  (when (g2-list-empty-p g2-list)
    (return-from nth-g2-list-element nil))
  (if (null element-type?)
      ;; Optimized case.  The list is not being filtered by an element-type.
      (loop with g2-list-structure = (list-structure g2-list)
	    for element-structure being g2-list-structure-element of g2-list-structure
	    for element-count = 0 then (1+f element-count)
	    do
	;; The list is not empty. There is at least one element.
	(when (=f element-count nth)
	  (let ((element-value (list-element-value element-structure)))
	    (return
	      (if return-element-structure?
		  element-structure
		  (if (evaluation-value-p element-value)
		      (copy-evaluation-value element-value)
		      element-value)))))
	    finally (return nil))

      ;; Looking for the nth element of a particular element-type.  E.g., the
      ;; 2nd variable in the item list.
      (loop with g2-list-structure = (list-structure g2-list)
	    for element-structure being g2-list-structure-element of g2-list-structure
	    for element-value = (list-element-value element-structure)
	    with element-count = 0
	    do
	;; The list is not empty. There is at least one element.
	;; Test for an element of the required type first.
	(when (g2-list-or-array-element-ok-p element-value element-type?)
	  ;; Found an element of the specified type.
	  (if (=f element-count nth)
	      (return (if return-element-structure?
			  element-structure
			  (if (evaluation-value-p element-value)
			      (copy-evaluation-value element-value)
			      element-value)))
	      ;; Only count elements of the specified element-type.
	      (incff element-count)))
	    finally (return nil))))



(defun-simple nth-from-end-g2-list-element
    (nth g2-list element-type? return-element-structure?)
  (when (g2-list-empty-p g2-list)
    (return-from nth-from-end-g2-list-element nil))
  
  (if (null element-type?)
      ;; Optimized case.  The list is not being filtered by an element-type.
      (loop with g2-list-structure = (list-structure g2-list)
	    for element being g2-list-structure-reverse-element of g2-list-structure
	    for element-value = (list-element-value element)
	    for element-count = 0 then (incff element-count)
	    do
	;; The list is not empty.  There is at least one element.
	(when (=f element-count nth)
	  (return (if return-element-structure?
		      element
		      (if (evaluation-value-p element-value)
			  (copy-evaluation-value element-value)
			  element-value))))
	    finally (return nil))
      
      ;; Looking for the nth element of a particular element-type.  E.g., the
      ;; last variable in the item list.
      (loop with g2-list-structure = (list-structure g2-list)
	    for element being g2-list-structure-reverse-element of g2-list-structure
	    for element-value = (list-element-value element)
	    with element-count = 0
	    do
	;; The list is not empty.  There is at least one element.
	(when (g2-list-or-array-element-ok-p element-value element-type?)
	  ;; Found an element of the specified type.
	  (if (=f element-count nth)
	      (return (if return-element-structure?
			  element
			  (if (evaluation-value-p element-value)
			      (copy-evaluation-value element-value)
			      element-value)))
	      ;; Only count elements of the specified element-type.
	      (incff element-count)))
	    finally (return nil))))

;; Consider removing the active tests and arg!!  Deactivated items are removed
;; from lists.  cpm, 4/16/91



;;;; Inserting Elements Into a G2-List


;;; The function `g2-list-insert-at-beginning' is used to insert an item or
;;; value at the beginning of the g2-list.

;;; The function `g2-list-insert-at-end' is used to insert an item or value at
;;; the end of the specified list.

;;; The elements are not inserted if the element is already in the list and the
;;; list does not allow duplicate elements.  If the element is an item, the
;;; lists that this item belongs to is updated.

;;; If the insert succeeds, the function returns T; otherwise NIL.

(defun-simple g2-list-insert-at-beginning (item-or-evaluation-value g2-list)
  (note-change-to-runtime-data-for-block g2-list)
  (let ((success? nil)
	(new-element-structure nil))
    (unless (and (not (insert-duplicate-elements? g2-list))
		 (g2-list-member-p item-or-evaluation-value g2-list))
      (setq success? t)
      (setq new-element-structure
	    (g2-list-structure-filo-enqueue
	      item-or-evaluation-value (list-structure g2-list) g2-list))
      (atomic-incff (list-size g2-list))
      (update-representations-of-slot-value g2-list 'list-size)
      (when (framep item-or-evaluation-value)
	(add-to-list-elements-for-item
	  item-or-evaluation-value new-element-structure)))
    success?))


;; Modified g2-list-insert-at-end.  Added the optional argument to override any
;; test for duplicate elements.  This is useful, for example, when inserting
;; into the indexed-attribute item-list and we know that there are no duplicate
;; items.  - cpm, 8/1/91

(defun g2-list-insert-at-end
    (item-or-evaluation-value
      g2-list &optional (override-any-test-for-duplicates-p? nil))
  (note-change-to-runtime-data-for-block g2-list)
  (let ((success? nil)
	(new-element-structure nil))
    (when (null (list-structure g2-list))
      (stack-error cached-top-of-stack
		   "~NF is not initialized yet -- start G2 first"
		   g2-list))
    (unless (and (null override-any-test-for-duplicates-p?)
		 (not (insert-duplicate-elements? g2-list))
		 (g2-list-member-p item-or-evaluation-value g2-list))
      (setq success? t)
      (setq new-element-structure
	    (g2-list-structure-enqueue
	      item-or-evaluation-value (list-structure g2-list) g2-list))
      (atomic-incff (list-size g2-list))
      (update-representations-of-slot-value g2-list 'list-size)
      (when (framep item-or-evaluation-value)
	(add-to-list-elements-for-item
	  item-or-evaluation-value new-element-structure)))
    success?))

#+Lockfree-List
(defun-simple g2-list-structure-insert-element-before (thing cursor outer-list)
  (let ((g2-list-structure (list-structure outer-list)))
    (generate-*-insert-before (g2-list-structure-insert-element-before
			       g2-list-structure cursor
			       g2-list-structure-head
			       g2-list-structure-next
			       list-previous-element
			       list-next-element
			       read-deleted-list-node
			       copy-list-node
			       release-list-node
			       help-insert-list-node)
      (create-list-element thing outer-list)
      (g2-list-structure-insert-element-after thing cursor outer-list))))

#+Lockfree-List
(defun-simple g2-list-structure-insert-element-after (thing cursor outer-list)
  (let ((g2-list-structure (list-structure outer-list)))
    (generate-*-insert-after (g2-list-structure-insert-element-after
			      g2-list-structure cursor
			      g2-list-structure-head
			      list-previous-element
			      list-next-element
			      read-deleted-list-node
			      copy-list-node
			      release-list-node
			      help-insert-list-node)
      (create-list-element thing outer-list)
      (g2-list-structure-insert-element-before thing cursor outer-list))))

;;; The function `g2-list-insert-before' is used to insert an item or value
;;; before a specified another item or value element in a g2-list.

;;; The function `g2-list-insert-after' is used to insert an item or value after
;;; a specified value in a g2-list. 

;;; The element is not inserted if the element is already in the list and if the
;;; list does not allow duplicate elements.

;;; Note that the new element is inserted before (or after) the first instance
;;; of the given element in the list.  This first element is found by searching
;;; from the start of the list, which may be necessary when the list allows
;;; duplicate elements.

;;; If the element is an item, the record of g2-lists that this item belongs to
;;; is updated.

;;; Note that the return value of this function is different from most other
;;; g2-list operations.  The return values are:
;;;    1 if the insert succeeds.
;;;   -1 if the insert fails because the "before" (or "after") element cannot
;;;      be found.
;;;   -2 if the insert fails because the g2-list does not allow duplicates and
;;;      the new element would be a duplicate.

(defun-simple g2-list-insert-before (item-or-evaluation-value
				      before-item-or-evaluation-value
				      g2-list
				      before-item-is-an-index?)
  (note-change-to-runtime-data-for-block g2-list)
  (let ((before-element-structure?
	 ;; TODO: in multi-threading environment, it's possible that the value
	 ;; returned here gets obsoleted (or even deleted) on the later calling of
	 ;; `g2-list-structure-insert-element-before'.
	 (if before-item-is-an-index?
	     (find-g2-list-element-structure-at-position
	       g2-list before-item-or-evaluation-value)
	     (find-g2-list-element-structure
	       before-item-or-evaluation-value g2-list nil nil)))
	(new-element-structure nil)
	(success-flag 1))
    ;; Insert the element if the g2-list allows duplicates or if the element is
    ;; not already in the g2-list.
    (cond
      ((null before-element-structure?)
       ;; Missing "before item" error.
       (setq success-flag -1))
      ((and (not (insert-duplicate-elements? g2-list))
	    (g2-list-member-p item-or-evaluation-value g2-list))
       ;; Duplicate element error.
       (setq success-flag -2))
      (t
	;; Add the new element.
	(setq new-element-structure
	      (g2-list-structure-insert-element-before
		item-or-evaluation-value before-element-structure? g2-list))
	(atomic-incff (list-size g2-list))
	(update-representations-of-slot-value g2-list 'list-size)
	;; For items, update record of g2-lists that the item belongs to.
	(when (framep item-or-evaluation-value)
	  (add-to-list-elements-for-item
	    item-or-evaluation-value new-element-structure))))
    success-flag))


(defun-simple g2-list-insert-after (item-or-evaluation-value
				     after-item-or-evaluation-value
				     g2-list
				     after-item-is-an-index?)
  (note-change-to-runtime-data-for-block g2-list)
  (let ((after-element-structure?
	  (if after-item-is-an-index?
	      (find-g2-list-element-structure-at-position
		g2-list after-item-or-evaluation-value)
	      (find-g2-list-element-structure
		after-item-or-evaluation-value g2-list nil nil)))
	(new-element-structure nil)
	(success-flag 1))
    ;; Insert the element if the g2-list allows duplicates or if the element is
    ;; not already in the g2-list.
    (cond 
      ((null after-element-structure?)
       ;; "After element" error.
       (setq success-flag -1))
      ((and (not (insert-duplicate-elements? g2-list))
	    (g2-list-member-p item-or-evaluation-value g2-list))
       ;; Duplicate element error.
       (setq success-flag -2))
      (t
	;; Add the new element.
       (setq new-element-structure
	     (g2-list-structure-insert-element-after
	       item-or-evaluation-value after-element-structure? g2-list))
	(incff (list-size g2-list))
	(update-representations-of-slot-value g2-list 'list-size)
	;; For items, update record of g2-lists that the item belongs to.
	(when (framep item-or-evaluation-value)
	  (add-to-list-elements-for-item
	    item-or-evaluation-value new-element-structure))))
    success-flag))






;;;; Removing Elements From a G2-List




;;; The function `remove-g2-list-element-structure' removes the given element
;;; structure from the g2-list.  If the update-list-elements-for-item? argument
;;; is non-NIL and if the element is an item, the record of g2-lists that it
;;; belongs to is updated.  Note that, in most cases, this argument and the
;;; list-structure argument should be non-NIL.  The reclaim-element-value-if-
;;; necessary? should be non-NIL if the element is not being held onto.

;;; IMPORTANT: This function should be called in a TEMPORARY-AREA because it can
;;; reference an element containing a gensym-float.

(defun-void remove-g2-list-element-structure
    (element-structure g2-list update-list-elements-for-item?
		       note-runtime-change-for-g2-list?
		       reclaim-element-value-if-necessary?)
  (loop with list-structure = (list-structure g2-list)
	for continuation in (list-open-continuations g2-list)
	for list-next-element? = (g2-list-structure-next element-structure list-structure)
	do
    ;; Remove from any continuations (e.g., any roles that are currently serving
    ;; g2-list elements).
    (when (eq element-structure (second continuation))
      (setf (second continuation)
	    (if #-Lockfree-List (eq list-structure list-next-element?)
		#+Lockfree-List (null list-next-element?)
		;; No next element.
		(eval-cons g2-list nil)
		list-next-element?))))
  (let ((element-value (list-element-value element-structure)))
    (when (and update-list-elements-for-item? (framep element-value))
      ;; Update the slot that records which lists this item belongs to.
      (delete-from-list-elements-for-item element-value element-structure)))
  (if reclaim-element-value-if-necessary?
      (g2-list-structure-delete-element element-structure)
      (g2-list-structure-delete-element-without-reclaiming-value
	element-structure))
  (atomic-decff (list-size g2-list))
  (update-representations-of-slot-value g2-list 'list-size)
  (when note-runtime-change-for-g2-list?
    (note-change-to-runtime-data-for-block g2-list)))



;;; The function `g2-list-remove' removes the first instance of the element from
;;; the g2-list that it locates.  Note that this is the instance closest to the
;;; beginning of the list.  If the element is an item, the record of g2-lists
;;; that it belongs to is updated.  Only datum or active items are deleted.

;;; If the remove succeeds, the function returns T, otherwise NIL.

(defun-simple g2-list-remove (item-or-evaluation-value element? g2-list)
  (let* ((element-structure? nil)
	 (element-found? nil))
    (when (not (g2-list-empty-p g2-list))
      (setq element-structure?
	    (cond ((and (evaluation-float-p item-or-evaluation-value)
			(exceptional-float-p (evaluation-float-value item-or-evaluation-value)))
		   (find-exceptional-float-in-g2-list
		     item-or-evaluation-value g2-list))
		  ((eq element? 'element-position)
		   (find-g2-list-element-structure-at-position g2-list item-or-evaluation-value))
		  (element?
		   (find-g2-list-element-structure item-or-evaluation-value g2-list nil nil))
		  (t
		   (find-g2-list-element-structure
		     item-or-evaluation-value g2-list nil nil)))))
    (setq element-found? (not (null element-structure?)))
    (when element-found?
      (remove-g2-list-element-structure element-structure? g2-list t t t))
    element-found?))



;;; The function `g2-list-remove-first' removes the first element from the
;;; g2-list.  If the element is an item, the record of g2-lists that it belongs
;;; to is updated.  Only datum or active items are deleted.  Optionally, the
;;; first element of the required element-type is removed.

;;; If the remove succeeds, the function returns T; otherwise NIL.

(defun g2-list-remove-first (g2-list &optional (required-element-type? nil))
  (let* ((element-structure?
	   (and (not (g2-list-empty-p g2-list))
		(g2-list-first g2-list required-element-type? t)))
	 (element-found? (not (null element-structure?))))
    (when element-found?
      (remove-g2-list-element-structure element-structure? g2-list t t t))
    element-found?))



;;; The function `pop-g2-list' removes the first element from the g2-list and
;;; returns it, not reclaiming the value.  (This differs from
;;; g2-list-remove-first, which removes the value and reclaims it, when
;;; necessary.)  Note that if the element is an item, the record of g2-lists
;;; that it belongs to is updated.  This function returns either an item,
;;; evaluation-value, or NIL (if the list is empty).

(defun-simple pop-g2-list (g2-list)
  (let* ((element-structure?
	   (and (not (g2-list-empty-p g2-list))
		(g2-list-first g2-list nil t)))
	 (element-value?
	   (and element-structure? (list-element-value element-structure?))))
    (when element-value?
      (remove-g2-list-element-structure element-structure? g2-list t t nil))
    element-value?))



;;; The function `g2-list-remove-last' removes the last element from the
;;; g2-list.  If the element is an item, the record of g2-lists that it belongs
;;; to is updated.  Only datum or active items are deleted.  Optionally, the
;;; first element of the required element-type is removed.

;;; If the remove succeeds, the function returns T; otherwise NIL.

(defun g2-list-remove-last (g2-list &optional (required-element-type? nil))
  (let* ((element-structure?
	   (and (not (g2-list-empty-p g2-list))
		(g2-list-last g2-list required-element-type? t)))
	 (element-found? (not (null element-structure?))))
    (when element-found?
       (remove-g2-list-element-structure element-structure? g2-list t t t))
    element-found?))



;;; The function `remove-element-from-all-g2-lists' is useful, for example, when
;;; an item is being deleted, and it needs to be removed from any g2-lists that
;;; it belongs to.  It does not require the item to be active.

(defun-simple remove-element-from-all-g2-lists (item deactivating-item?)
  (when (framep item)
    (loop with element-list = (list-elements-for-item item)
	  for element-structure in element-list
	  for g2-list = (list-frame element-structure)
	  do
      (unless (and deactivating-item? (or warmbooting? (list-is-permanent g2-list)))
      ;; Note that an argument to the following call specifies to not update the
      ;; list-elements-for-item slot.  This is the slot that's reclaimed below.
	(remove-g2-list-element-structure element-structure g2-list t t t)))))









;;;; Validating G2-Lists




;;; G2-list elements may need to be validated when either the list element-type
;;; or the list elements themselves have changed.  The list element-type can
;;; only be modified by changing the default in the item-list object-definition.
;;; The list elements could have been affected by a class-hierarchy change to
;;; their object-definitions.  This could have affected whether the elements are
;;; still subclasses of the g2-list element-type.




;;; The function `validate-all-item-lists' checks that elements of all
;;; item-lists do not conflict with the lists' list-type.  If the item element
;;; does conflict, then that element is removed from the list.

;;; This function is called, for example, when a definition changes at runtime,
;;; such that the classes of item may have changed.

;;; The class? and old-class? arguments, if non-NIL, specify the class or
;;; classes of the list elements that need to be validated.  If both arguments
;;; are NIL, then all elements of item-lists, will be validated.

;;; Note that this function does not attempt to update any role servers that are
;;; currently serving g2-list elements.

(defun-void validate-all-item-lists (class? old-class?)
  (loop for item-list being each class-instance of 'item-list
	for list-element-type = (list-type item-list)
	do
    ;; Validate only those item-lists that could have been affected by the class
    ;; changes, as specified by the arguments.
    (when (and (not (eq list-element-type 'item))
	       (or (and (null class?) (null old-class?))
		   (and class? (subclassp list-element-type class?))
		   (and old-class?
			;; EQ test, in case the old-class is no longer defined.
			(or (eq list-element-type old-class?)
			    (subclassp list-element-type old-class?)))))
      (validate-and-fix-g2-item-list-elements item-list)))
  nil)



;;; The function `validate-and-fix-g2-item-list-elements' will check that all
;;; lists elements are of the correct list element-type.  If an element is not,
;;; then it is removed from the list.  If the element-type is not a defined
;;; class, all elements are removed from the list.

;;; Note that this function does not attempt to update any role servers that are
;;; currently serving g2-list elements.

(defun-void validate-and-fix-g2-item-list-elements (item-list)
  (let ((list-element-type (list-type item-list)))
    (when (not (eq list-element-type 'item))
      (if (not (classp list-element-type))
	  ;; No element could be an instance of this undefined, class type.
	  (clear-g2-list item-list)
	  (loop for item-element being each g2-list-element in item-list
		with removal-list? = nil
		do
	    (unless (item-ok-for-g2-list-or-array-p
		      item-element list-element-type)
	      (setq removal-list?
		    (if (null removal-list?)
			(g2-list-list item-element)
			(g2-list-cons item-element removal-list?))))
		finally
		  (loop for item-to-remove in removal-list?
			do
		    (g2-list-remove item-to-remove nil item-list))
		  (when removal-list?
		    (reclaim-g2-list-list removal-list?))))))
  nil)



;;; The function `remove-g2-list-duplicate-elements' will check for and remove
;;; any duplicate elements in the given g2-list.  Note that it is up the caller
;;; to check the list's insert-duplicate-elements? slot, if necessary.  (A
;;; non-NIL value indicates that duplicates are not allowed.)

;;; Note that this function does not handle exceptional floats, such as NaN,
;;; which are, by definition, not equal to themself.

;;; Note that for non-item-lists this operation is O(n^2).

;;; For item-lists, the efficiency is improved by checking the lists that each
;;; item element belongs to. (Of course, to be more efficient this assumes that
;;; the number of lists that each element belongs to is less than N/2, where N
;;; is the length of the original list.)

(defun-void remove-g2-list-duplicate-elements (g2-list)
  (unless (g2-list-empty-p g2-list)
    (loop with element-type = (list-type g2-list)
	  with item-or-value-element-type? = (eq element-type 'item-or-datum)
	  with item-element-type? = 
	    (and (g2-list-or-array-element-type-may-contain-item-p element-type)
		 (not item-or-value-element-type?))
	  with g2-list-structure = (list-structure g2-list)
	  for element-structure = #-Lockfree-List
				  (g2-list-structure-head g2-list-structure)
				  #+Lockfree-List
				  (g2-list-structure-next
				    (g2-list-structure-head g2-list-structure)
				    g2-list-structure)
	      then next-element-structure
	  for next-element-structure
	      = (g2-list-structure-next element-structure g2-list-structure)
	  for element-value = (list-element-value element-structure)
	  for remove-element? = nil
	  ;; Stop if there are no elements after element-structure.
	  until #-Lockfree-List (eq next-element-structure g2-list-structure)
		#+Lockfree-List (null next-element-structure)
	  do
      (setq remove-element?
	    (if (or item-element-type?
		    (and item-or-value-element-type? (framep element-value)))
		;; Search the g2-lists that the item belongs to.
		(loop for element-structure-for-item in
		      (list-elements-for-item element-value)
		      for duplicate-element-structure? =
		      (if (and (not (eq element-structure-for-item
					element-structure))
			       (eq (list-frame element-structure-for-item)
				   g2-list))
			  ;; Same g2-list and element value, but different
			  ;; position in the g2-list.
			  element-structure-for-item)
		      until duplicate-element-structure?
		      finally (return duplicate-element-structure?))
		(with-temporary-gensym-float-creation
		    remove-g2-list-duplicate-elements
		  (find-g2-list-element-structure
		    element-value g2-list next-element-structure nil))))
      (when remove-element?
	(remove-g2-list-element-structure element-structure g2-list t t t))))
  nil)






;;;; Reading and Writing G2-List and G2-Array Elements for KB




;;; `Read-g2-list-or-array-element-for-kb' ... 

(defun-simple read-g2-list-or-array-element-for-kb (element-type g2-array-p?)
  (cond
    ((not (eq element-type 'truth-value))
      ;; must read either a frame or an evaluation value; note that truth values
      ;; written from untyped arrays or lists are written and get read back in
      ;; as evaluation values (evaluation truth values)
      (read-element-for-kb nil))
    ;; Truth-value for truth-value-array.
    (g2-array-p?
     ;; The truth-value was written and is now read back in as an integer.  This
     ;; value is stored in the truth-value.  It is not converted to an
     ;; evaluation-value.
     (read-element-for-kb nil))
    ;; Truth-value for truth-value-list.
    (t
      ;; Must read a fixnum.  If we're going to have evaluation values in
      ;; truth-value lists, then do this.  Note that in 3.0 truth values in
      ;; truth-value arrays and lists were written as integers, and they are so
      ;; written in 4.0+ KBs for compatibility.
      (make-evaluation-truth-value (read-element-for-kb nil)))))

;; Note that NIL may appear only in item or item-or-value arrays.  Therefore,
;; this handles that ok.



;;; `Write-g2-list-or-array-element-for-kb' ... Element must either be NIL, an
;;; evaluation value, or a frame.  Element-type should be one of the result
;;; types of g2-list-or-array-element-type.
;;;
;;; Note that at present, NIL may only be a legal element of a g2-item-array
;;; or g2-item-or-value-array subclass.

(defun-void write-g2-list-or-array-element-for-kb (element element-type)
  (cond
    ((framep element)
     (if (collectable-block-p element)
	 (write-element-for-kb element)
	 (write-element-for-kb nil)))
    ;; so it's an evaluation value
    ((and (evaluation-truth-value-p element) ; so it's a truth value
	  (eq element-type 'truth-value))
	
     ;; why isn't it implied that the type is not TRUTH-VALUE?  in 3.0, we did
     ;; not keep truth-value evaluation values in truth-value arrays or lists,
     ;; but now for g2-lists (version 4.0) we do -- but CPM is reviewing this.
     ;; (MHD 10/27/93)

      ;; Now then, if the element type is truth-value, you don't have to worry
      ;; about writing a truth value.  But, if this is a truth value, and
      ;; element-type is truth-value, you have to write it as an integer, for
      ;; compatibility with 3.0.
     (write-element-for-kb (evaluation-truth-value-value element)))
    (t
     (write-evaluation-value-for-kb element))))


;(defun write-list-element-for-kb (element) ; obsolete (MHD 10/27/93)
;  (cond 
;                                        ; Note that write-element-for-kb enters
;                                        ; a temporary float creation context
;                                        ; when write a managed-float value.
;;    ((temporary-constant-p element)
;;     (write-element-for-kb (constant-value-internal element)))
;
;    ;; Evaluation-floats are a special case.  We don't want to access the
;    ;; managed-float value here.
;
;                                        ; An alternative is to rely on the fact
;                                        ; that evaluation-floats and
;                                        ; managed-floats have the same
;                                        ; implementation.  Pass the
;                                        ; evaluation-value (float) to
;                                        ; write-element-for-kb and let it enter
;                                        ; a temporary float context and
;                                        ; reference the managed-float-value.  -
;                                        ; cpm, 10/14/93
;    ((evaluation-float-p element)
;                                        ; Check if there is a problem with
;                                        ; nested temporary float contexts!!  -
;                                        ; cpm 10/14/93
;     (with-temporary-gensym-float-creation write-list-float-element-for-kb
;       (write-element-for-kb (evaluation-float-value element))))
;    ((evaluation-value-p element)
;     (write-element-for-kb (evaluation-value-value element)))
;    (t (write-element-for-kb element))))

;; This could be made more efficient.  See notes for write-g2-array-data-for-kb.






;;;; Reading and Writing G2-Lists for KB




;;; `Write-g2-list-data-for-kb' is called by write-runtime-data-for-kb (see
;;; KB-SAVE1).  It is here, rather than in KB-SAVE1, because it uses macros
;;; defined in LISTS.  It is similar to write-g2-list-data-for-kb.

(defun-simple write-g2-list-data-for-kb (g2-list)
  (when (active-p g2-list)
    (let* ((list-length (g2-list-length g2-list))
	   (element-type (g2-list-or-array-element-type g2-list)))
      (when (>f list-length 0)
	(write-left-bracket-if-necessary)
	(write-char-for-kb #\L)
	(write-fixnum-for-kb list-length)
	(do-g2-list-elements (element-value g2-list nil)
	  (write-g2-list-or-array-element-for-kb
	    element-value element-type))))))



;;; `Read-list-data' is called by read-runtime-data-for-block.  It is similar to
;;; read-array-data.  The result is a list that can be saved as squirreled-data,
;;; and handed off to unsquirrel-list-data (q.v., below) for processing.
;;; Therefore, the result is a list in reverse order, which is the order
;;; expected by unsquirrel-list-data.

(defun-simple read-list-data (g2-list)
  (with-temporary-gensym-float-creation read-list-data
    (loop with squirreled-list = nil
	  with element-type = (g2-list-or-array-element-type g2-list)
	  repeat (read-element-for-kb nil) ; list-length
	  do (setq squirreled-list 
		   (gensym-cons
		     (read-g2-list-or-array-element-for-kb element-type nil)
		     squirreled-list))
	  finally (return squirreled-list))))

;; Old KBs (3.0 KBs) definitely have integers for the truth values.  I suppose
;; we could have made new KBs save truth values, but it wouldn't have made the
;; code any simpler, due to the need to preserve compatibility, so I decided to
;; go with the 1-byte-per-truth-value savings of sticking with the
;; raw-truth-value-data format.  CPM/JRA haven't reviewed this, yet, though.
;; (MHD 10/27/93)

;; Note that the squirreled-list is in reverse order.

;; The above may have contained a LEAK when it was creating temporary-constants.
;; (In version 4.0, It now creates evaluation-values.)  Extract-number-or-value
;; copies its argument if it is a text string and make-temporary-constant also
;; copies its text argument.  So, to prevent this problem with
;; evaluation-values, it calls make-evaluation-value-reclaiming-argument.  -
;; cpm, 10/14/93

;; Check if the above can overflow the temporary float area when reading in data
;; for large float or quantity lists containing floats!!  Maybe, it should exit
;; and re-enter the temporary context every N number of values.  - cpm, 10/14/93


;(declare-forward-reference data-type-of-non-logical-datum function)
;
;(defun read-list-data (g2-list)
;  (let ((list-length (read-element-for-kb nil)))
;    (with-temporary-gensym-float-creation read-array-data
;      (loop with squirreled-list = nil
;            with truth-valued? = (frame-of-class-p g2-list 'truth-value-list)
;            for index from 0 below list-length 
;            as value = (extract-number-or-value (read-element-for-kb nil))
;            do
;        (setq squirreled-list 
;              (gensym-cons 
;                (if (framep value)
;                    value
;                    (make-evaluation-value-reclaiming-argument
;                      value
;                      (if truth-valued?
;                          'truth-value
;                          (data-type-of-non-logical-datum value))))
;                squirreled-list))
;            finally (return squirreled-list)))))



;;; `Unsquirrel-list-data' iterates over the squirreled-list, generating
;;; evaluation-values if necessary, and inserting them at the beginning of the
;;; g2-list.  Note that the type is derived individually for each evaluation-
;;; value from the data, not from the g2-list, since g2-lists can have values of
;;; different types (a quantity-list can have integer and float evaluation-
;;; values).  The argument squirreled-list is expected to be in reverse order;
;;; the resulting g2-list ends up in the proper order.

;;; For permanent lists, the post-loading-function convert-saved-list-values-to-
;;; g2-list-structure reclaims the saved list-structure slot value when
;;; warmbooting.

(defun-simple unsquirrel-list-data (g2-list squirreled-list)
  (loop for item-or-evaluation-value in squirreled-list do
    (g2-list-insert-at-beginning
      (if (deleted-frame-p item-or-evaluation-value)
	  nil
	  item-or-evaluation-value)
      g2-list))
  (reclaim-gensym-list squirreled-list))



;;;; System procedures for moving and transferrng, and cloning
;;; These procedures are driven by the desire of the applications group to be
;;; able to operate on a group of items while keeping the connection
;;; relationships intact. Most of this code is based upon functionality
;;; used/discovered/replicated/mutated from the operate on area functionality
;;; -rdf, 3/6/96

;;; `reverse-list-using-dragging-conses' is introduced just to keep the cons
;;; pool use consistent

(defun reverse-list-using-dragging-conses (list)
  (loop with reversed-list = nil
	for l on list
	do (setq reversed-list
		 (dragging-cons (car l) reversed-list))
	finally (return reversed-list)))


;;;  `preflight-check-dragging-list-of-blocks-for-transfer' checks to make sure
;;;  that the proposed transfer is legal prior to takeoff.  If to-workspace? is
;;;  non-nil, it will be checked for validity. Otherwise, the checking is
;;;  presumably being done for a transfer-to-the-mouse type of transfer, so only
;;;  limited checking, i.e., only of the validity of transferring
;;;  objects-being-transferred, is done; final validity checking of the
;;;  destination must be done with the objects finally "land" there.

(defun preflight-check-dragging-list-of-blocks-for-transfer (objects-being-transferred
							      to-workspace?
							      &optional
							      g2-window-for-mouse?)
  (cond ((and g2-window-for-mouse?
	      (or (not (frame-of-class-p
			 g2-window-for-mouse? 'g2-window))
		  (null (workstation-for-g2-window? g2-window-for-mouse?))))
	 ;; more checking needed?  e.g., in modal dialog state?!
	 (reclaim-dragging-list objects-being-transferred)
	 (stack-error
	   cached-top-of-stack
	   "Cannot transfer items to the mouse of ~NF: it's not a connected G2-window instance!"
	   g2-window-for-mouse?))
	((and to-workspace?
	      (non-kb-workspace-p to-workspace?))
	 (reclaim-dragging-list objects-being-transferred)
	 (stack-error
	   cached-top-of-stack
	   "Cannot transfer items to non-KB workspaces!"))
	((and to-workspace?
	      (proprietary-p to-workspace?)
	      (not (eq (get-workspace-if-any (car objects-being-transferred))
		       to-workspace?)))
	 (reclaim-dragging-list objects-being-transferred)
	 (stack-error cached-top-of-stack
		      "Cannot transfer items to proprietary workspaces!"))
	((not (blocks-transferable-p objects-being-transferred))
	 (reclaim-dragging-list objects-being-transferred)
	 (stack-error cached-top-of-stack
		      "Objects are not transferrable")))
  (loop for block in objects-being-transferred
	for invalid-item-for-transfer? = 
	(not (null (or (parent-frame block)
		       (frame-of-class-p block 'simulation-subtable)
		       (frame-of-class-p block 'kb-workspace)
		       (frame-of-class-p block 'connection))))
	do
    (cond
      (invalid-item-for-transfer?
       (cond ((parent-frame block)
	      (reclaim-dragging-list objects-being-transferred)
	      (stack-error cached-top-of-stack
			   "Cannot transfer ~NF because it is an attribute of ~NF."
			   block (parent-frame block)))
	     ((of-class-p block 'kb-workspace)
	      (reclaim-dragging-list objects-being-transferred)
	      (stack-error cached-top-of-stack
			   "Cannot transfer ~NF because it is a kb-workspace.  The make ~
                  subworkspace action can be used to give a transient ~
                  kb-workspace a new superior object."
			   block))
	     (t
	      (reclaim-dragging-list objects-being-transferred)
	      (stack-error cached-top-of-stack
			   "Cannot transfer ~NF because it is a ~a."
			   block (class block)))))
      ((and to-workspace?
	    (ancestor-p block to-workspace?))
       (reclaim-dragging-list objects-being-transferred)
       (stack-error cached-top-of-stack
		    "Cannot transfer ~NF to the workspace ~NF because ~NF is superior to ~
          this workspace."
		    block to-workspace? block))
      ((and to-workspace?
	    (and (block-can-be-dependent-p block)
		 (item-currently-contains-compiled-value block)
		 (not (block-can-be-dependent-p to-workspace?))))
       (reclaim-dragging-list objects-being-transferred)
       (stack-error cached-top-of-stack
		    "Cannot transfer ~NF to the workspace ~NF.  ~NF is a dependent item ~
                         containing a compiled attribute and ~NF is not dependent."
		    block to-workspace? block to-workspace?))
	)))



;;; `get-blocks-for-valid-group-operation' returns 2 values. The first is a dragging-list of
;;; all non-connection frames in the g2-list that is passed to it. The returned list must be
;;; reclaimed by the caller. It ensures that all items in the list are on the same workspace
;;; and and are thus eligible to be transferred, moved, and cloned as a group. The second
;;; value is the (common) workspace of the items. The function is used by the following
;;; three system procedures.

;;; This function was modified to accept either a g2-list or a sequence. The latter
;;; is used when the group operation procedures are called by external processes as
;;; an RPC. In this case, it is impractical for the caller to create and reclaim a
;;; g2-list. A sequence is automatically consumed after it is used. If a list is
;;; passed in, we get the list-contents as newly created sequence, use it and reclaim it.

(def-hash-table duplicates-check-hash-table
		:key-comparitor equal
		:size 50021
		:use-binary-tree t) ; because it's not used cross threads

(defvar duplicates-check-hash (make-duplicates-check-hash-table))

(defun get-blocks-valid-for-group-operation (g2-list-or-sequence)
  (let ((objects-being-collected nil)
	(from-workspace nil)
	(list-contents-sequence-reclaimable-p nil)
	(list-contents nil))
    (clear-duplicates-check-hash-table duplicates-check-hash)
    (macrolet ((cleanup-for-function-abort ()
		 `(progn
		    (when list-contents-sequence-reclaimable-p
		      (reclaim-evaluation-value list-contents))
		    (when objects-being-collected
		      (reclaim-dragging-list
			objects-being-collected)))))
      #+development
      (unless (or (evaluation-sequence-p g2-list-or-sequence)
		  (and (framep g2-list-or-sequence)
		       (frame-of-class-p g2-list-or-sequence 'g2-list)))
	(cerror "go on??" "Thing passed is neither a g2-list or a sequence"))
      (setf list-contents
	    (cond ((evaluation-sequence-p g2-list-or-sequence)
		   g2-list-or-sequence)
		  (t
		   (setf list-contents-sequence-reclaimable-p t)
		   (get-list-contents-as-sequence g2-list-or-sequence))))
      (when (=f (evaluation-sequence-length list-contents) 0)
	(cleanup-for-function-abort)
	(stack-error
	cached-top-of-stack
	"The item list is empty."))
      ;; need to test that all objects are on the same workspace
      (loop for item being each evaluation-sequence-element of list-contents
	    as workspace-of-item? = nil
	    do
	;; Do we need this check? Can these be anything but items?
	(unless (and (framep item)
		     (item-p item))
	  (cleanup-for-function-abort)
	  (stack-error
	    cached-top-of-stack
	    "All members of the list must be items, ~NF is not an item." item))
	(setf workspace-of-item? (superblock? item)) ; Should be get-workspace-of-block-or-connection
	(unless workspace-of-item?
	  (cleanup-for-function-abort)
	  (stack-error
	    cached-top-of-stack
	    "All items in the list must be on a workspace. ~NF is not on one." item))
	(unless				;we don't care about connections
	    (subclassp (class item) 'connection)
	  (cond (from-workspace
		 (unless (eq from-workspace
			     workspace-of-item?)
		   (cleanup-for-function-abort)
		   (stack-error
		     cached-top-of-stack
		     "All items in the list must be on the same workspace. ~
                    ~NF is not on ~NF." item from-workspace)))
		(t (setq from-workspace (superblock? item))))
	  (when (null (get-duplicates-check-hash-table item duplicates-check-hash))
	    (setf (get-duplicates-check-hash-table item duplicates-check-hash) t)
	    (dragging-push item objects-being-collected))))
      (when list-contents-sequence-reclaimable-p
	(reclaim-evaluation-value list-contents))
      (values objects-being-collected from-workspace))))


(defun-simple delete-external-connections-of-blocks (blocks)
  (loop with junction-blocks-not-to-be-deleted = blocks ; Special Variable
	with frame-serial-number = (copy-frame-serial-number (current-frame-serial-number))
	for block in blocks
	when (not (frame-has-been-reprocessed-p block frame-serial-number))
	  do 
	    (loop for connection
		  being each connection of block
		  as block-at-other-end
		     = (get-block-at-other-end-of-connection connection block)
		  when (and (not (memq block-at-other-end blocks))
			    (not (loose-end-p block-at-other-end)))
		    do (delete-connection-to-stub connection))
	  finally (reclaim-frame-serial-number frame-serial-number)))





;;; `g2-transfer-list-contents' transfers the objects in a list to either a
;;; dragging workstation context for a given window, or to a new workspace. If
;;; to-workspace-or-window is a g2-window instance, this attempts to enter a
;;; dragging context to transfer the items "to the mouse", and ignores the
;;; arguments x-offset, y-offset, and delete-external-connections-p.  Otherwise,
;;; that argument is assumed to be a workspace, and this tries to transfer the
;;; items to that workspace.  This checks for various constraints, including
;;; that all objects must be on the same workspace, and all loose ends and
;;; connections between objects are transferred intact.  If there's a violation,
;;; this signals a stack error.  Note that there is no requirement that the
;;; workspace containing the items be showing.

(declare-system-procedure-function g2-transfer-list-contents nil)

(defun-funcallable g2-transfer-list-contents (object-list to-workspace-or-window
							  x-offset y-offset
							  &optional delete-external-connections-p)
  (multiple-value-bind (objects-being-transferred from-workspace)
      (get-blocks-valid-for-group-operation object-list)
    (when (and delete-external-connections-p
	       (evaluation-truth-value-true-p delete-external-connections-p))
      (delete-external-connections-of-blocks objects-being-transferred))
    (preflight-check-dragging-list-of-blocks-for-transfer
      objects-being-transferred
      (if (frame-of-class-p to-workspace-or-window 'workspace)
	  to-workspace-or-window)
      (if (frame-of-class-p to-workspace-or-window 'g2-window)
	  to-workspace-or-window))
    (cond
      ((frame-of-class-p to-workspace-or-window 'g2-window)
       ;; transfer-to-mouse case: enter dragging context, which handles details
       ;; like those dealt with below, such as including loose ends and updating
       ;; "v5 window" workspace subscribers at the end.
       (transfer-items-to-mouse-of-window
	 objects-being-transferred to-workspace-or-window))
      (t
       (let ((to-workspace to-workspace-or-window))
	 ;; grab all the loose ends and take them along for the ride
	 (loop for block in objects-being-transferred
	       do
	   (loop for connection being the connections of block
		 as other-end = (get-block-at-other-end-of-connection connection block)
		 when (loose-end-p other-end)
		   ;; pushnew just in case we get a loose end passed in.
		   do (dragging-pushnew other-end objects-being-transferred)))

	 (let ((saved-position-or-next-lower-thing nil))
	   
	   (shift-blocks-with-their-external-connections
	     objects-being-transferred
	     nil 
	     'just-erase from-workspace 0 0)
	   (let ((reversed-blocks
		   ;;  Reverse the list so that the stacking order is not reversed by
		   ;;  add-subblock. 
		   (reverse-list-using-dragging-conses objects-being-transferred))
		 (transfer-in-progress t))
	     (loop for block in reversed-blocks 
		   do (transfer-workspace-subblock block from-workspace to-workspace))
	     (reclaim-dragging-list reversed-blocks))
	   (shift-blocks-with-their-external-connections
	     objects-being-transferred
	     nil
	     nil
	     to-workspace x-offset (-f y-offset)
	     (neq to-workspace from-workspace)	    ; if true => just draws
	     t)
	   (when g2-has-v5-mode-windows-p
	     (loop for block in objects-being-transferred
		   do
	       (send-ws-representations-item-insert-as-subblock
		 block to-workspace saved-position-or-next-lower-thing)))
	   ;; GENSYMCID-1169: Navigator tree hierarchy issues
	   (loop for block in objects-being-transferred do
		 (when (and to-workspace
			   (neq from-workspace to-workspace)
			   (frame-of-class-p block 'item))
		   (update-subscriptions-for-add-item-to-workspace
		     to-workspace block)))))))
    (reclaim-dragging-list objects-being-transferred)))





;;; `g2-move-list-contents' moves the items in a list, or enters an interactive
;;; context to allow the user to move the items, keeping them on the same
;;; workspace.  If the optional third argument is is supplied, it should either
;;; be a g2-window or the truth-value false.  If it's a g2-window, then this
;;; does not actually move anything immediately, but rather enters a dragging
;;; context to allow the user to move the items within the workspace they're on.
;;; This checks for various constraints, and may signal a stack error if there
;;; are constraint violations.  Note that in the move case, unlike with the
;;; transfer function (above), the workspace containing the items being moved is
;;; required to be showing in the given window.

(declare-system-procedure-function g2-move-list-contents t)

(defun-funcallable g2-move-list-contents
    (object-list delta-x delta-y &optional g2-window-for-mouse-or-false)
  (multiple-value-bind (objects-being-moved from-workspace)
      (get-blocks-valid-for-group-operation object-list)
    (let* ((g2-window-for-mouse?		; don't actually check for false
	     (if (of-class-p g2-window-for-mouse-or-false 'g2-window)
		 g2-window-for-mouse-or-false))
	   (image-plane?
	     (if g2-window-for-mouse?
		 (map-to-image-plane from-workspace g2-window-for-mouse?))))
      (cond
	(g2-window-for-mouse?		; interactive dragging case
	 (when (null image-plane?)
	   ;; Clean up, and then call the mapping function to get the usual
	   ;; stack error.  That will exit nonlocally.
	   (reclaim-dragging-list objects-being-moved)
	   (map-to-image-plane-or-stack-error
	     from-workspace g2-window-for-mouse?))
	 (move-items-to-mouse-of-window
	   objects-being-moved g2-window-for-mouse? image-plane?))
	(t    
	 (move-blocks-with-their-external-connections
	   objects-being-moved  from-workspace delta-x (-f delta-y))
	 (when g2-has-v5-mode-windows-p
	   (loop for block in objects-being-moved
		 do
	     (send-ws-representations-item-moved block delta-x delta-y)))))
      (reclaim-dragging-list objects-being-moved))))



;;; `g2-clone-list-contents' clones the items in the list and transfers the
;;; clones to either a dragging workstation context or to a new workspace at the
;;; specified location. If to-workspace-or-window is a g2-window instance, this
;;; attempts to enter a dragging context to transfer the items "to the mouse",
;;; and ignores the arguments x-offset and y-offset.  Otherwise, that argument
;;; is assumed to be a workspace, and this tries to transfer the items to that
;;; workspace.  All of the original items must be on the same workspace, all
;;; loose ends and connections internal to the group are cloned and tranferred.
;;; In the dragging case, as with the transfer function (above), the original
;;; workspace is not required to be showing in the given window.  This returns a
;;; list of the cloned objects.  However, note that in the dragging case, the
;;; items are not made permanent until they're placed on a workspace, and
;;; subject to deletion if they are placed on an invalid destination workspace
;;; by the user or if the workstation context is aborted by the user.

(declare-system-procedure-function g2-clone-list-contents t)

(defun-funcallable g2-clone-list-contents
    (object-list to-workspace-or-window delta-x delta-y)
  (multiple-value-bind (objects-being-cloned from-workspace)
      (get-blocks-valid-for-group-operation object-list)
    (declare (ignore from-workspace))
    (let ((cloned-objects nil)
	  (item-list-for-user nil)
	  (saved-position-or-next-lower-thing nil))
      ;; grab all the loose ends and take them along for the ride
      (loop for block in objects-being-cloned
	    do
	(loop for connection being the connections of block
	      as other-end = (get-block-at-other-end-of-connection connection block)
	      when (loose-end-p other-end)
		;; pushnew just in case we get a loose end passed in.
		do (dragging-pushnew other-end objects-being-cloned)))
      
      (let ((plist-of-blocks-and-corresponding-clones
	      (loop for block in objects-being-cloned
		    as new-block = (clone-frame block objects-being-cloned)
		    ;; after cloning an item other than a workspace manually,
		    ;; set it to be neither permanent nor transient:
		    do
		(set-neither-permanent-nor-transient-and-propagate
		  new-block nil)
		(dragging-push new-block cloned-objects)
		
		    nconc (dragging-list block new-block))))
	
	;; At this point, all blocks  have been cloned,
	;; stubs have been cloned for external connections and internal output
	;; connections, and plist-of-blocks-and-corresponding-clones has been set up.  
	;; It is now necessary to tie the cloned internal output connections to 
	;; their corresponding cloned output end objects.

	(loop for (block cloned-block)
	      on plist-of-blocks-and-corresponding-clones
		  by #'cddr
	      do
	  (clone-connections-for-block block cloned-block
				       plist-of-blocks-and-corresponding-clones))
	(reclaim-dragging-list plist-of-blocks-and-corresponding-clones))

      (preflight-check-dragging-list-of-blocks-for-transfer
	cloned-objects
	(if (frame-of-class-p to-workspace-or-window 'workspace)
	    to-workspace-or-window)
	(if (frame-of-class-p to-workspace-or-window 'g2-window)
	    to-workspace-or-window))
      
      (loop with new-list = nil
	    for cloned-block in cloned-objects
	    do
	(dragging-pushnew cloned-block new-list)
	(loop for connection being the connections of cloned-block
	      as other-end = (get-block-at-other-end-of-connection connection cloned-block)
	      when (loose-end-p other-end)
		do (dragging-pushnew other-end new-list))
	    finally
	      (reclaim-dragging-list cloned-objects)
	      (setq cloned-objects new-list))

      (cond
	((frame-of-class-p to-workspace-or-window 'g2-window)
	 (transfer-items-to-mouse-of-window
	   cloned-objects to-workspace-or-window))
	(t
	 (let ((workspace to-workspace-or-window))
	   (loop with transfer-in-progress = t
		 for block in cloned-objects
		 do (transfer-workspace-subblock block
						 nil ;from-workspace
						 workspace))
	   (shift-blocks-with-their-external-connections
	     cloned-objects
	     nil
	     nil
	     workspace
	     delta-x
	     (-w delta-y)
	     t
	     t)
	   (when g2-has-v5-mode-windows-p
	     (loop for block in cloned-objects
		   do
	       (send-ws-representations-item-insert-as-subblock
		 block workspace saved-position-or-next-lower-thing)))
	   (reclaim-dragging-list objects-being-cloned))))
      
      ;; create list for user
      (setq item-list-for-user (make-transient-item 'item-list))
      ;; The following line used to appear before the call to
      ;; shift-blocks-with-their-external-connections.  This was causing the
      ;; previous loop to call send-ws-representations-item-insert-as-subblock
      ;; in the wrong order on the blocks.  The previous revision to this file
      ;; changed that call from a simple move, which doesn't depend on ordering,
      ;; to an insert-as-subblock which is very dependent on ordering.  Bug
      ;; HQ-4369427 "TW2 displays objects with different z-order than G2"
      ;; -dkuznick and fmw, 8/16/02
      (setf cloned-objects (nreverse cloned-objects))
      (loop for block in cloned-objects
	    do
	(unless (loose-end-p block)
	  (g2-list-insert-at-beginning block item-list-for-user)))
      (reclaim-dragging-list cloned-objects)
      (values item-list-for-user))))






;;; `g2-align-list-contents' moves the objects in a list, per the horizontal and
;;; vertical alignment specifications, keeping them on the same workspace.

;;; The accepts the symbols in align-selection-command-operations, i.e., the
;;; symbols accepted as the OPERATION argument by the align-selection UI
;;; command.

(declare-system-procedure-function g2-align-list-contents t)

(defun-funcallable g2-align-list-contents (object-list operation)
  (multiple-value-bind (objects-being-aligned from-workspace)
      (get-blocks-valid-for-group-operation object-list)
    (declare (ignore from-workspace))
    (cond
      ((memq operation align-selection-command-operations)
       (align-blocks objects-being-aligned operation)
       (reclaim-dragging-list objects-being-aligned))
      (t
       (reclaim-dragging-list objects-being-aligned)
       (stack-error
	 cached-top-of-stack
	 "The symbol ~a is not a valid alignment operation ~
                  name. It must be one of the symbols ~L,|."
	 operation
	 align-selection-command-operations)))))

;; Unfortunately, the symbols left/right-center and top/bottom-center, i.e.,
;; with / in them, are a bit hard to type in the G2 editor, since / is a
;; punctuation symbol, so they need to be quoted (with the @ character) when
;; typed in for the G2 standard tokenizer to read. Consider accepting some other
;; symbol instead! (MHD 3/30/04)


(defvar distribute-selection-command-operations '(horizontally vertically))

;;; The function `g2-distribute-list-contents' follows the confusing naming
;;; convention used by system procedures in this section. OBJECTS can be either
;;; a g2-list or a sequence.

(defun-for-system-procedure g2-distribute-list-contents (objects operation)
  (multiple-value-bind (valid-objects from-workspace)
      (get-blocks-valid-for-group-operation objects)
    (declare (ignore from-workspace))
    (cond
      ((memq operation distribute-selection-command-operations)
       (distribute-blocks valid-objects operation))
      (t
       (reclaim-dragging-list valid-objects)
       (stack-error
	 cached-top-of-stack
	 "The symbol ~a is not a valid operation name for distribute. ~
                  It must be one of the symbols ~L,|."
	 operation distribute-selection-command-operations)))
    (when (evaluation-sequence-p objects)
      (reclaim-evaluation-sequence objects))
    nil))

(declare-system-procedure-function g2-items-in-area t)



;;; `items-in-area' return a g2-list of the item in the area of the specified
;;; workspace loose ends are not incluced

(defun-funcallable g2-items-in-area (workspace left top right bottom item-list)
  (let ((objects nil))
    (unless (and (workspace-p workspace)
		 (framep item-list) (frame-of-class-p item-list 'item-list)
		 (integerp left)
		 (integerp top)
		 (integerp right)
		 (integerp bottom))
      (stack-error
	cached-top-of-stack
	"Arguments must be workspace, integer, integer, integer, integer, item-list"))
    (setf bottom (-f bottom))
    (setf top (-f top))
    (setq objects (list-blocks-within-area-of-workspace
		    workspace left top right bottom nil nil))
    
    (loop for block in objects
	  do
      (g2-list-insert-at-end block item-list))
    (reclaim-dragging-list objects)))

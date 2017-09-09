;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module ARRAYS

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Chris Morel, Jim Allard




(declare-forward-reference print-designation function)
(declare-forward-reference evaluate-designation function)
(declare-forward-reference *current-computation-frame* variable)
(declare-forward-reference note-item-needing-initialization-function function)

;; In STACK-ACTS:
(declare-forward-reference make-transient-item function)
(declare-forward-reference class-can-be-transient-p function)

;; In ROLES:
(declare-forward-reference generate-designation-for-block function)

(declare-forward-reference set-transient-and-propagate function)




;;; A `g2-array' is an object that implements an array data structure for G2
;;; users.  It allows the user to reference and modify array elements in a
;;; constant amount of time, independent of the array length.

;;; G2-arrays are similar to g2-lists, in that they both contain a sequence of
;;; elements.  Note that g2-list and g2-array share some code in the LISTS
;;; module.  The following compares the two classes.

;;;                                                           G2-Array   G2-List
;;;   Has an element-type  (only modifiable in class           Yes        Yes
;;;    default-settings for item-list-or-array definition)
;;;   Element values are not permanent:                        Yes        Yes
;;;   Saves elements in Warmboot                               Yes        Yes
;;;   Add/delete element causes forward-chaining               No         No
;;;   Has initial values:                                      Yes        No
;;;   Random (constant time) element access                    Yes        No
;;;   Has a fixed length (that can be modified by the user):   Yes        No
;;;   Can automatically restrict duplicate elements:           No         Yes
;;;   Records (internally) which g2-list-or-array an item
;;;    belongs to:                                             No         Yes
;;;   Removes deactivated items (i.e., no longer an element    No         Yes
;;;    when re-activated)


;;; The `g2-array-length' is the number of elements in a g2-array.  The g2-array
;;; can only be one-dimensional.  (It may be multi-dimensional-like by
;;; containing an array of arrays.)  The array is of a fixed length, but this
;;; value can be modified from an action in G2.  Note that the length is a
;;; minimum of 0 and a maximum of g2-array-length-maximum.

;;; The `g2-array-index' is a 0-based index into the g2-array.  G2 actions and
;;; expressions also use this 0-based index.

;;; The `g2-array-element-type' is the element type associated with a g2-array.
;;; All values in the array must be of this type.  These types are: item,
;;; quantity, float, integer, truth-value, text, symbol, subclasses of item,
;;; value (new to version 4.0), and item-or-value (new to version 4.0).

;;; Integer and float arrays are a subclass of quantity-array.

;;; Note that the user can only modify the g2-array-element-type in the
;;; default-settings attribute of class-definitions and object-definitions
;;; which are a subclass of item-array.  The element-type can only be changed
;;; to be a subclass of item.

;;; The `managed-g2-array' is the managed-array within the g2-array object that
;;; stores the array elements.  This can be a managed-array or a managed-float-
;;; array.  This data-structure is internal to this module.

;;; The g2-array actions and expressions are defined in the roles, stack
;;; actions, and stack evaluator modules.  Refer to these for more information.




;;; G2 array expressions:

;;; Note that there is no grammar for a LOCAL-NAME binding for nth-element.
;;;
;;; In the grammar, the array or list designation is restricted to be a
;;; name-reference or a reference to annother array or list.  Some examples are:
;;;
;;; ARRAY-OR-LIST [x]
;;;    (the (nth-element item-or-datum) array-or-list x)
;;;
;;; ARRAY-OR-LIST-OF-ARRAYS-OR-LISTS [x] [y]
;;;    (the (nth-element item-or-datum) 
;;;         (the (nth-element item-or-datum) array-or-list-of-arrays-or-lists x)
;;;         y)
;;;
;;; THE TEMP OF ARRAY-OR-LIST [x]
;;;  Note that the array reference is evaluated first, then the attribute of the
;;;  resulting array element.
;;;    (the Temp (the (nth-element item-or-datum) array-or-list x))
;;;
;;; THE ARRAY-LENGTH OF <G2-ARRAY>
;;;    ('the 'array-length 'of designation)


;;; G2-array actions:

;;;    CHANGE <G2-ARRAY-OR-LIST> [ARRAY-INDEX] = <ITEM> | <VALUE>
;;;
;;;    CHANGE <G2-ARRAY-OR-LIST> [ARRAY-INDEX-1] [ARRAY-INDEX-2] ...
;;;                              = <ITEM> | <VALUE>
;;;
;;;    CHANGE THE ARRAY-LENGTH OF <G2-ARRAY> TO <ARRAY-LENGTH>
;;;      A change-system-attribute action.
;;;
;;;    CHANGE THE TEXT OF THE INITIAL-VALUES OF <G2-ARRAY> TO ...
;;;      A change-attribute-as-text action.


;;; Conclude the value of an variable-or-parameter in an item-array element or
;;; change a non-item element value.  Note that the conclude action can not add
;;; a new item to an array location.

;;;   CONCLUDE THAT <G2-ARRAY> [<ARRAY-INDEX>] = <VALUE>

;;; Conclude the value of a variable in an item-array has no value:

;;;   CONCLUDE THAT <G2-ARRAY> [<ARRAY-INDEX>] has no value.
;;;
;;;   Can conclude a new value or no value into a a variable in the array.
;;;   Doesn't need any modifications to implement this, besides the role-server
;;;   that accesses an array element.


;;; G2-array iterations:

;;;    FOR ANY <ELEMENT-TYPE> [LOCAL-NAME] IN <G2-ARRAY>
;;;    FOR <LOCAL-VARAIBLE> = EACH <ELEMENT-TYPE> [LOCAL-NAME] IN <G2-ARRAY>




;; NOTES:

;; Validate the initial-values, when element-type or initial-values change?
;; Currently, this is only done during initialization of the array (during
;; activation of the array).

;; An element of an item-array that is deactivated are returned on
;; re-activation.  This differs from the behavior of item-list elements which
;; are not returned when re-activated.  This is because when an item-list
;; element is deactivated, we can lookup the lists that the element belongs to
;; and remove the item from those lists.  Item-arrays do not keep such pointers
;; from item-elements to item-arrays.

;; Verify for consistancy: intial-values and element-type.

;; Consider re-implementing truth-value arrays so that each element only
;; contains the raw truth-value (integer) and not the evaluation-value.  If this
;; changes, we still need to be able warmboot values saved in the old format.

;; Internally, item-arrays and item-or-value g2-arrays require 2 elements per
;; value (frame and frame serial number).  Review the implementation of this.
;; The following are some alternate implementation proposals.
;; - cpm, 12/13/93
;;
;; 1. One proposal was to have only one frame-serial number per array and update
;; this number as an item is added to the array.  This is a problem because all
;; the items in the array would need to be re-validated when an item element
;; (and therefore the number) changes.
;;
;; 2. A second proposal (a modification of the first), is to have one
;; frame-serial-number per N elements.  In this way, you would verify only those
;; elements with the N when any of the N elements change.  This would save
;; memory, but slow down array element changes.
;;
;; 3. A third proposal is to have the element contain either a value or a
;; pointer to a structure that contains information for the item element.  This
;; structure would have a pointer to the item and a frame-serial-number slot.
;; In this way, the memory for the frame-serial-number would only be allocated
;; when needed.  This design seems reasonable, but was not used for two reasons.
;; The users would no longer get "locality of reference", which means that
;; item-array memory is no longer contingous or close to it.  Also, with this
;; proposal item-arrays could be allocating memory depending on the element
;; being added to the array.  Item-arrays would no longer have a fixed memory
;; size.  We felt that these features of arrays are more important than the
;; extra memory cost.  Perhaps, we should implement proposal 2 as a memory
;; improvement at some point.


;; Need an efficient managed-array operation for fill starting at position.
;; Currently, setf on an aref is used.

;; Should the expression "the number of elements in <designation>" work for
;; arrays as well as g2-lists and history-datapoints?

;; Consider rewriting element-type slot and element-type operations to use
;; actual type-specifications.  Currently, the element-type and desired
;; element-type is a datum type or name of a class.  This should be done for
;; g2-lists also.  This value saved in KBs, so we would need something that
;; would change this on load for existing KBs.

;; The editor should prompt for "g2-array" in the change array action.

;; Several functions enter TEMPORARY-FLOAT areas.  Could the area overflow for
;; large float-arrays?  Consider re-enterring the area for every N elements.



;; DOCUMENTATION NOTES:

;; Similar to a variable value, can't enter an array element from a type-in box.

;; Values are lost on deactivation.

;; Kb-state changes are not undone on deactivation, but on reset.

;; "the foo of x[i]" parses as the foo of the array element, not the array
;; element of the attribute.






;;;; G2-Array Class Definition




;;; G2-array is the root class of the g2-arrays.  It was not instantiable in
;;; version 3.x, but can now be instantiated and subclassed in version 4.0.  Its
;;; default element-type is item-or-value.  Like item-array, it does not have a
;;; default initial-value.  That is, the default value is "none" (no value).
;;;
;;; The G2-array-element-type slot cannot not be edited by the user.  It can
;;; only be modified through the default-settings attribute of a user-defined
;;; class that inherits from item-array.
;;;
;;; The g2-array-initial-values slot can be edited by the user and receive a new
;;; value in the default-settings attribute of an new g2-array
;;; object-definition or class-definition.


(def-class (g2-array object (foundation-class g2-array) define-predicate
		     (class-export-comment
		       "The original parts document showed the following attributes for g2-array: reconcile.
<ul>
<LI>array length: integer, <!--from g2-array-length -->
<LI>element type: symbol, <!--from g2-array-element-type -->
<LI>initial values: (item-or-value *) <!--from g2-array-initial-values-->
<LI>values (item-or-value *) ; A sequence of the values in the array. <!--from managed-g2-array-->
</ul>"))
  (g2-array-length 0 vector-slot (type g2-array-length) system
		   user-overridable)
  (g2-array-element-type
    item-or-datum vector-slot (type element-type) system not-user-editable)
  (g2-array-initial-values
    nil vector-slot (type list-of-item-and-datum-constants?) system
    user-overridable save)
  (managed-g2-array nil vector-slot system (type list-structure)
		    do-not-clone
		    save do-not-put-in-attribute-tables not-user-editable)
  (array-is-permanent nil vector-slot system user-overridable (type yes-or-no))
  (icon-description
    (:funcall-at-load-time
      create-icon-description
      60 60 
      ((outline (0 0) (60 0) (60 60) (0 60))
       (lines (15 15) (15 45))
       (lines (25 15) (25 45))
       (lines (45 15) (45 45))
       (lines (15 15) (45 15))
       (lines (15 20) (45 20))
       (lines (15 25) (45 25))
       (lines (15 30) (45 30))
       (lines (15 35) (45 35))
       (lines (15 40) (45 40))
       (lines (15 45) (45 45))))))


;; The slot name alias is visible to the user in the g2-array table and
;; can be referenced in G2 expressions.

(define-slot-alias array-length g2-array-length g2-array)
(define-slot-alias element-type g2-array-element-type g2-array)
(define-slot-alias initial-values g2-array-initial-values g2-array)


;;; The function `g2-array-length-function' is  in modules before this one
;;; to access the length of the g2-array.

(defun-simple g2-array-length-function (g2-array)
  (g2-array-length g2-array))


#+unused
(defun-simple array-is-permanent-function (g2-array)
  (array-is-permanent g2-array))


;; Note that a slot value reclaimer for g2-array-initial-values is not needed.
;; Since the managed numbers or values are in a list, the default reclaimer
;; takes care of it.  See reclaim-slot-value.  Also, when the value is eq to the
;; (default) slot init form, no reclamation is done.  cpm, 6/16/91.


;;; The reclaimer for managed-g2-array is called upon deletion of the g2-array.

(def-slot-value-reclaimer managed-g2-array (managed-g2-array? g2-array)
  (when (and managed-g2-array? 
	     (not (eq managed-g2-array? initialization-inhibit)))
    (cond ((consp managed-g2-array?)
	   ;; At load time, before the once-only post-loading-function
	   ;; convert-saved-array-values-to-g2-array-structure is called
	   ;; the value will be a list.
	   (cond ((not (managed-array-p (car-of-cons managed-g2-array?)))
		  #+development
		  (when (and (not reading-kb-p)
			     (not currently-automatically-resolving-class-name-conflicts?))
		    (cerror "arrays" "suspect managed-g2-array -- please tell ghw"))
		  (reclaim-slot-value-tree managed-g2-array?)
		  (atomic-exchange (managed-g2-array g2-array) nil))
		 (t
		  ;; Cloned managed-array.  Initialization not yet finished.
		  (reclaim-managed-g2-array
		    (car-of-cons managed-g2-array?) (g2-array-element-type g2-array))
		  (setf (car managed-g2-array?) nil)
		  (reclaim-slot-value-cons managed-g2-array?))))
	  (t
	   (reclaim-managed-g2-array
	     managed-g2-array? (g2-array-element-type g2-array))))))

;; The check for initialization-inhibit is actually not currently
;; necessary since a knowledge base is started immediately on warmboot.



;;; The `g2-array-length slot-putter' adjusts the managed-g2-array based on the
;;; new array-length.  An array-length of 0 will result in a null managed-array.
;;;
;;; If the managed-array is shrunk, the lost element values are reclaimed when
;;; necessary and the remaining elements keep their current values.  
;;;
;;; If the array grows and the array has been initialized, the new elements will
;;; contain the initial-value, if the initial-values slot contains one value, or
;;; the default value, if any, for that g2-array-element-type.
;;;
;;; Frame note warnings are issued when the new length is not correct for the
;;; number of initial values.  The frame note is removed when this is corrected.
;;;
;;; Note that we don't need to verify the new length with the array maximum.
;;; This is done in the slot-compiler (if this is an edit) or from the change
;;; action.

(def-slot-putter g2-array-length (g2-array new-length initializing?)
  (let* ((element-type (g2-array-element-type g2-array))
	 (old-length (g2-array-length g2-array)))
    ;; When reading a kb, the managed-g2-array is a saved list.  The post-loading
    ;; function, convert-saved-array-values-to-g2-array-structure, has yet to be
    ;; called to convert it to a managed array.

    ;; GENSYMCID-1896: Saving a bundle KB didn't save all required KB modules
    ;;
    ;; Keep in mind that this can be caled during 
    ;; reading, but after `convert-saved-array-values-to-g2-array-structure`
    ;; has already been called, for example, during conflict resolution.
    (cond ((and reading-kb-p
		;; make sure the array is not upgraded yet.
		(consp (managed-g2-array g2-array)))
	   (atomic-exchange (g2-array-length g2-array) new-length))
	  (t
	   (let ((managed-g2-array?
		   ;; NOTE: transient items should be treated the same way, otherwise
		   ;; in `convert-g2-list-to-g2-array', after a transient g2 array is
		   ;; created, the inside managed-g2-array will still be NIL, then
		   ;; the calling of `move-g2-list-elements-to-g2-array' will fail.
		   (if (and (array-is-permanent g2-array)
			    (not initializing?)
			    (null (access-once (managed-g2-array g2-array))))
		       (progn
			 #-SymScale
			 (setf (managed-g2-array g2-array)
			       (allocate-managed-g2-array old-length element-type nil nil))
			 #+SymScale
			 (let ((new-array (allocate-managed-g2-array old-length element-type nil nil)))
			   (if (compare-and-swap (managed-g2-array g2-array) nil new-array)
			       new-array
			     (prog1 (managed-g2-array g2-array) ; from other threads
			       (reclaim-managed-g2-array new-array element-type)))))
		     (managed-g2-array g2-array)))) ; still can be NIL here.

	     (note-change-to-runtime-data-for-block g2-array)

	     ;; Set the new length before initializing array elements.
	     (atomic-exchange (g2-array-length g2-array) new-length)

	     ;; Validate the array-length and the number of initial-values.
	     (if (g2-array-length-and-initial-values-match-p
		   new-length (g2-array-initial-values g2-array))
		 (delete-frame-note-if-any 'g2-array-length-conflict g2-array)
		 (add-frame-note 'g2-array-length-conflict g2-array nil nil nil))

	     ;; When old length and old array is there, 
	     (unless (or initializing?
			 (null managed-g2-array?)
			 (eq managed-g2-array? initialization-inhibit))
	       ;; When shrinking and the array is active, reclaim lost values, if
	       ;; necessary.
	       (when (and (<f new-length old-length) (active-p g2-array))
		 (reclaim-managed-g2-array-elements-if-necessary
		   managed-g2-array? element-type new-length))

	       ;; Adjust the array.
	       (atomic-exchange (managed-g2-array g2-array)
		 (adjust-managed-g2-array
		   managed-g2-array? new-length element-type))

	       ;; When growing and the array is active, initialize new values.  Give
	       ;; warning messages for invalid initial values for item-arrays.
	       (when (and (>f new-length old-length) (active-p g2-array))
		 (initialize-g2-array-at-position g2-array old-length))))))
    new-length))

(def-slot-putter array-is-permanent (g2-array value)
  (atomic-exchange (array-is-permanent g2-array) value))

	

	     

;;; The frame-note-writer `g2-array-length-conflict' writes the frame note
;;; message that warns the user of a conflict between the length and the
;;; number of initial-values of the g2-array.

(def-frame-note-writer g2-array-length-conflict (particulars g2-array)
  (declare (ignore particulars))
  (let ((default? (g2-array-or-list-default-element-value g2-array))
	(array-type (g2-array-element-type g2-array)))
    (tformat "a default initial value of ~NC will be used because ~
              there is more than one initial value and the array-length, ~d, ~
              is not equal to the number of these values, ~d"
	     (or default? 'none)
	     (case array-type
	       (symbol 'symbol)
	       ((quantity number float datum) 'number) ; DATUM default is 0.0
	       (text 'text)
	       (truth-value 'truth-value)
	       ((item item-or-datum) 'symbol) ; the symbol NONE
	       (t array-type))
	     (g2-array-length g2-array)
	     (length (g2-array-initial-values g2-array)))))



;;; The `g2-array-initial-values slot putter' does not affect the values
;;; currently in the g2-array.  Frame note warnings are issued when the number
;;; of new initial values is not correct for the length of the array.  The frame
;;; note is removed when this is corrected.  Initial-values are not validated
;;; with the array element-type here.  This occurs on activation of the array.

(def-slot-putter g2-array-initial-values (g2-array new-initial-values)
  ;; Test initial-values with array length.
  (without-consistency-analysis (g2-array)
    (cond ((g2-array-length-and-initial-values-match-p
	     (g2-array-length g2-array) new-initial-values)
	   (delete-frame-note-if-any 'g2-array-length-conflict g2-array))
	  (t (add-frame-note 'g2-array-length-conflict g2-array nil nil nil)))
    (setf (g2-array-initial-values g2-array) new-initial-values)
    new-initial-values))



;;; The `g2-array-element-type slot-putter' tests that the current element
;;; values fit the new element-type.  This attribute can only be modified
;;; through a class-definition default-settings for a subclass of item-array.
;;; If there are invalid element-values, they are removed.  (No logbook message
;;; is displayed to indicate this.)

(def-slot-putter g2-array-element-type (g2-array new-element-type initializing?)
  ;; In 3.0 the symbol quantity was held in quantity-arrays.  Otherwise these
  ;; symbols are always either valid type specification symbols or else they may
  ;; be presumed to be class names.  -jra 1/31/95
  (when (eq new-element-type 'quantity)
    (setq new-element-type 'number))
  ;; Validate the elements with the new element-type.
  (unless (or initializing? reading-kb-p)
    (let ((managed-g2-array? (access-once (managed-g2-array g2-array))))
      (when managed-g2-array?
	;; Test and remove any invalid elements.
	(validate-and-fix-g2-item-array-elements g2-array new-element-type))))
  (without-consistency-analysis (g2-array)
    (atomic-exchange (g2-array-element-type g2-array) new-element-type))
  new-element-type)






;;;; Subclasses of G2-Array




;;;  The g2-array-element-type slot is the required element type of all elements
;;;  of the array.  It is displayed in all g2-arrays, but can not be editted
;;;  directory or changed through an action.  It can only be modified by the
;;;  user in subclasses of item-array using the default-settings of the
;;;  object-definition.

;; NOTE: The slot-value-writers for the various G2-array-initial-values slot
;; type will call the writer for the most general array:  list-of-item-and-datum-
;; constants?.

;; This has been done for backward-compatibility.  The slot-value compilers for
;; the default-overrides slot in 3.0 and 4.0 allows users to enter array initial
;; values using a reference to a more general class; for example, if the class
;; is an integer array, the default-override parser and compiler will accept
;; "initial values for g2-array: 11.34, the symbol tank, "horrors".

;; However, when an array instance is initialized with initial values, if a
;; value on a list is not a subtype of the element type for the array, the
;; default element value is used instead.  (GHW 8/15/95)

(def-class (item-array g2-array (foundation-class item-array))
  (g2-array-element-type item not-user-editable user-overridable)
  (g2-array-initial-values nil (type constant-designation-list?)))
  

;; Note that value-array is new to G2 version 4.0.

(def-class (value-array g2-array (foundation-class value-array))
  (g2-array-element-type datum)
  (g2-array-initial-values (0.0) (type list-of-datum-constants)))

(def-class (symbol-array value-array (foundation-class symbol-array))
  (g2-array-element-type symbol)
  (g2-array-initial-values (g2) (type symbol-list)))
       
(def-class (text-array value-array (foundation-class text-array))
  (g2-array-element-type text)
  (g2-array-initial-values ("") (type whole-string-list)))

(def-class (truth-value-array value-array (foundation-class truth-value-array))
  (g2-array-element-type truth-value)
  (g2-array-initial-values
    (#.falsity) (type truth-value-list)))

(def-class (quantity-array value-array (foundation-class quantity-array))
  (g2-array-element-type number)
  (g2-array-initial-values (0.0) (type quantity-list)))

(def-class (float-array quantity-array (foundation-class float-array))
  (g2-array-element-type float)
  (g2-array-initial-values (0.0) (type float-list)))

(def-class (integer-array quantity-array (foundation-class integer-array))
  (g2-array-element-type integer)
  (g2-array-initial-values (0) (type integer-list)))

(def-class (long-array quantity-array (foundation-class integer-array))
  (g2-array-element-type long)
  (g2-array-initial-values (0) (type long-list)))




;;;; G2-Array Class Methods




;;; The `activate-subclass-of-entity method for g2-array' initializes the
;;; g2-array upon activation.  If the initial-values are not valid, a WARNING
;;; MESSAGE is displayed and the default-value, if any, is used to initialize.

;; Note that an array with a frame status of "bad" does not get activated.

(def-class-method activate-subclass-of-entity (g2-array)
  (unless (eq (managed-g2-array g2-array) initialization-inhibit) ; warmboot
    (note-item-needing-initialization-function g2-array)))



;;; The `deactivate-subclass-of-entity for g2-array' clears the g2-array
;;; elements and reclaims any managed element values.  The managed-g2-array is
;;; not reclaimed here, but is reclaimed when the g2-array is deleted.

;; Note that an array with a frame status of "bad" gets deactivated.

(def-class-method deactivate-subclass-of-entity (g2-array)
  (let ((managed-g2-array?
	 (access-once (managed-g2-array g2-array))))
    (unless (or (null managed-g2-array?)
		warmbooting?
		(eq managed-g2-array? initialization-inhibit) ; warmboot
		(array-is-permanent g2-array))
      (reclaim-managed-g2-array-elements-if-necessary
	managed-g2-array? (g2-array-element-type g2-array) 0))))






;;;; Managed-G2-Array Operations




;;; The managed-g2-array is the managed-array or managed-float-array within the
;;; g2-array object.  This abstraction is used because of the two different
;;; types of managed-arrays (managed and managed-float) used for the g2-array
;;; and also because arrays that may contain item elements are handled
;;; differently from other arrays.  The elements contained in the
;;; managed-g2-array vary depending on the element-type of the g2-array.  Some
;;; elements values are managed.

;;; Symbol-arrays, truth-value-arrays, and integer-arrays contain symbols,
;;; truth-values, and integers respectively.

;;; Float-arrays are implemented as managed-float-arrays that contain
;;; gensym-floats, not managed-floats.

;;; Quantity-arrays are implemented as managed-arrays and contain either
;;; integers or managed-floats.

;;; Text-arrays contain text-strings which are managed values and therefore
;;; needs to be reclaimed when no longer referenced.

;;; Item-arrays contain consist of elements which are items or "no value".
;;; Internally, each element is implemented as two values (managed-array
;;; elements) per g2-array element, the item and the item's frame-serial-number.
;;; The serial number immediately follows the item in the managed-array.  The
;;; length of the managed-array for the item-array is therefore twice the length
;;; of the item-array.

;;; New to version 4.0: value-array (new class) and g2-array (now instantiable).

;;; Value-arrays are implemented as managed-arrays and contain any of the value
;;; (datum) types.  These are symbol, truth-value, integer, float, and text.

;;; G2-arrays contain items, evaluation-values, and "no values" (NIL).  There
;;; are implemented similar to item-arrays.  Internally, there are two values
;;; per element.  The first contains the item-or-value element.  The second
;;; contains the frame-serial-number for item elements.

;; NOTE that there are several alternate proposal that were considered for
;; item-or-value g2-arrays.  See the section label ";; NOTES:" earlier in this
;; file.  - cpm, 12/13/93






;;;; Managed-G2-Array Allocation and Reclamation




;;; The function `allocate-managed-g2-array' creates a managed-array or
;;; managed-float-array depending on the array element type argument.  The
;;; optional arguments control whether the array will be initialized with NIL
;;; values and whether the array is made to the exact array length.

;;; Note that both item-array and g2-array (item-or-value array) are twice the
;;; length of the other arrays.  There are two slots per element, one for the
;;; item (or value) and one for a frame-serial-number.

(defun allocate-managed-g2-array
       (length g2-array-element-type 
	&optional (dont-initialize nil) (make-exactly nil))
  (cond ((eq g2-array-element-type 'float)
	 (allocate-managed-float-array length make-exactly))
	((g2-list-or-array-element-type-may-contain-item-p g2-array-element-type)
	 ;; Item and item-or-value arrays.
	 (allocate-managed-array (*f 2 length) dont-initialize make-exactly))
	(t
	 ;; Non-float value arrays.
	 (allocate-managed-array length dont-initialize make-exactly))))



;;; The function `reclaim-managed-g2-array' is the function that reclaims any
;;; managed-g2-array.  The elements are reclaimed if they are managed-values,
;;; e.g., text-strings or managed-floats.

(defun reclaim-managed-g2-array (managed-g2-array g2-array-element-type)
  (if (managed-float-array-p managed-g2-array)
      (reclaim-managed-float-array managed-g2-array)
      (progn 
	(unless (memq g2-array-element-type '(symbol truth-value integer))
	  ;; Element-type of symbol, truth-value, integer.  The elements do not
	  ;; need to be reclaimed.
	  #+development 
	  (unless (or (memq g2-array-element-type '(text number quantity datum item-or-datum))
		      (g2-list-or-array-element-type-may-contain-item-p g2-array-element-type))
	    (cerror "Continue" "reclaim-managed-g2-array confused: now calling ~
reclaim-managed-g2-array-elements-if-necessary on a case where it wouldn't earlier."))
	  (reclaim-managed-g2-array-elements-if-necessary
	    managed-g2-array g2-array-element-type 0))
	(reclaim-managed-array managed-g2-array))))
;;Note: inverted conditional logic.  Symbol and truth value used to be caught in
;;a T of a cond, whose other pieces handled the
;;reclaim-managed-g2-array-elements-if-necessary call, and spelled out those
;;element-types needed there.  Now, we are spelling out differently in order not
;;to call g2-list-or-array-element-type-may-contain-item-p multiple times (it
;;will be called in reclaim-managed-g2-array-elements-if-necessary.)  Integer
;;explicitly added to the list of simple types.  yduJ, 11/04


;;; The function `reclaim-managed-g2-array-elements-if-necessary' reclaims any
;;; managed element values in the g2-array starting at the indicated position up
;;; to the end of the array.  (The default starting position is 0.)  The
;;; elements at these positions are set to NIL.  The managed-g2-array itself is
;;; not reclaimed.  This function is useful, for example, when shrinking a
;;; g2-array.

(defun reclaim-managed-g2-array-elements-if-necessary
    (managed-g2-array g2-array-element-type starting-position?)
  (let ((start-index (or starting-position? 0)))
    (cond 
      ((eq g2-array-element-type 'item-or-datum)
       (loop with adjusted-start-index = (*f start-index 2)
	     for i from adjusted-start-index
		   below (managed-array-length managed-g2-array)
	           by 2
	     for item-or-value? = (managed-svref managed-g2-array i)
	     do
	 (when item-or-value?
	   (when (not (frame-or-deleted-frame-p item-or-value?))
	     (reclaim-managed-number-or-value item-or-value?))
	   (setf (managed-svref managed-g2-array i) nil)
	   (frame-serial-number-setf (managed-svref managed-g2-array (+f i 1)) nil))))
      ((memq g2-array-element-type '(text number quantity datum))
       (loop for i from start-index
		   below (managed-array-length managed-g2-array)
	     for item-or-value? = (managed-svref managed-g2-array i)
	     do
	 (when item-or-value?
	   (reclaim-managed-number-or-value item-or-value?)
	   (setf (managed-svref managed-g2-array i) nil))))
      ((g2-list-or-array-element-type-may-contain-item-p g2-array-element-type)
       (loop with adjusted-start-index = (*f start-index 2)
	     for i from adjusted-start-index
		   below (managed-array-length managed-g2-array)
	           by 2
	     do
	 (frame-serial-number-setf (managed-svref managed-g2-array (+f i 1)) nil)))
      (t nil))))



;;; The function `clear-managed-values-from-managed-g2-array' clears the managed
;;; datum elements of a managed-g2-array, without reclaiming them.  This
;;; function is needed to drop references to the managed elements of an
;;; elements, when something else refers to the same managed-values.  This
;;; function only neeeds to clear those managed-g2-arrays which may contain
;;; managed-values.

;;; IMPORTANT: Note that this will cause a leak of the elements containing
;;; managed-values, if they are not being held onto somewhere else (to be
;;; reclaimed later) or are not reclaimed already.

;;; This function is used in special cases, for example, when moving elements
;;; between a g2-array and g2-list, without copying the elements.  After the
;;; copy is done, this function removes references to the managed elements in
;;; the g2-array to prevent double reclaimation.

(defun-void clear-managed-values-from-managed-g2-array
    (managed-g2-array g2-array-element-type)
  (unless (eq g2-array-element-type 'float)
    ;; Don't need to clear managed-float-array of float-array.  It does not
    ;; contain managed-floats.
    (loop for i from 0 below (managed-array-length managed-g2-array)
	  for item-or-value? = (managed-svref managed-g2-array i)
	  do
      (when item-or-value?
	(setf (managed-svref managed-g2-array i) nil)))))






;;;; Managed-G2-Array Element Access and Set




;;; The macro `managed-g2-array-aset' is the setf macro for managed-g2-arrays.
;;; Note, that setting a value into a quantity-array should use
;;; store-managed-number instead.

(def-substitution-macro managed-g2-array-aset (managed-g2-array index value)
  (if (managed-float-array-p managed-g2-array)
      (setf (managed-float-aref managed-g2-array index)
	    (if (managed-float-p value)
		(managed-float-value value)
		value))
      (setf (managed-svref managed-g2-array index) value))
  value)



;;; The function`managed-g2-array-aref' is used to set the value in the managed
;;; array. This function can be used to "setf" the value of the element.

(defun-simple managed-g2-array-aref (managed-g2-array index)
  (if (managed-float-array-p managed-g2-array)
      (managed-float-aref managed-g2-array index)
      (managed-svref managed-g2-array index)))


(defsetf managed-g2-array-aref managed-g2-array-aset)






;;;; Managed-G2-Array Adjust and Fill Operations




;;; The following functions operate on the internal (managed-g2-array) of the
;;; g2-array.  They adjust the sizes of the array or fill values into the
;;; elements.  One or more values can be filled into the array for all elements
;;; or for the elements starting at a given position.



;;; The function `adjust-managed-g2-array' is used to grow or shrink a
;;; managed-g2-array.  By default, the optional arguments specify that the
;;; elements are copied and initialized.

(defun adjust-managed-g2-array
    (managed-g2-array new-length g2-array-element-type
		      &optional (dont-copy nil) (dont-initialize nil))
  (cond ((eq g2-array-element-type 'float)
	 (adjust-managed-float-array managed-g2-array new-length dont-copy))
	((g2-list-or-array-element-type-may-contain-item-p g2-array-element-type)
	 ;; Item or item-or-value g2-array.
	 (adjust-managed-array
	   managed-g2-array (*f 2 new-length) dont-copy dont-initialize))
	(t
	 ;; Non-float value g2-array.
	 (adjust-managed-array
	   managed-g2-array new-length dont-copy dont-initialize))))



;;; The function `copy-and-box-element-value-if-necessary' is used when filling
;;; an array location with a value that is of any type and the value may need to
;;; be copied and boxed (for floats).  This function helps in preserving the
;;; separation between slot-values and evaluation-values, though some of the
;;; slot and evaluation values may have the same implementation.

(defun copy-and-box-element-value-if-necessary (value)
  (cond
    ((or (slot-value-float-p value)
	 (evaluation-float-p value)
	 (gensym-float-p value))
     (allocate-managed-float ; make-evaluation-float
       (if (managed-float-p value)
	   (managed-float-value value)
	   value)))
    ((text-string-p value)
     ;; Copies the text string.
     (make-evaluation-text value))
    ;; truth-values can be slot-value-constants, which contain typing
    ;; information.  This is distinguishes them from integers.
    ((slot-constantp value)
     (cond ((and (consp (cdr value)) (eq (cadr value) 'truth-value))
	    ;; Copy the truth-value slot-value-constant.
	    (make-evaluation-truth-value (car value)))
	   (t
	    #+development
	    (cerror "continue" "Unexpected slot-value-constant in copy-and-box-element-value-if-necessary.")
	    nil)))
    ((symbolp value) (make-evaluation-symbol value))
    ((fixnump value) (make-evaluation-integer value))
    ((evaluation-value-p value) (copy-evaluation-value value))
    ((temporary-constant-p value)
     (make-evaluation-value-from-temporary-constant value))
    (t value)))



;;; The following functions fill all the elements of a managed-g2-array with a
;;; given value.  The functions vary depending on the type of value (and
;;; sometimes type of managed-g2-array) being used.

;;; The function `fill-managed-g2-float-array' takes an integer or float and
;;; fills the array with floats.  It does not reclaim old float elements because
;;; they are over-written.

;;; The function `fill-managed-g2-quantity-array' fills with a float or integer.
;;; New floats are boxed and old float elements reclaimed as needed.
;; The following doc added today. (MHD 3/14/91) 
;;; Quantity can either be a fixnum, a slot value float, or a gensym float.
;;; If it is a gensym float or a slot value float, it is not reclaimed by this
;;; function, but is instead copied once for each element of the array.

;;; The function `fill-managed-g2-text-array' copies the text-string into each
;;; element of the managed-g2-text-array.  Note that the function does not
;;; reclaim any existing element values.

;;; The function `fill-managed-g2-item-array' fills the array with an item.
;;; Note that it fills an item and item frame-serial-number for each item
;;; element.

;;; The function `fill-managed-g2-item-or-value-array' fills the array with an
;;; item or value.  Note that for items, it fills an item and item
;;; frame-serial-number for each element.

;;; The function `fill-managed-g2-value-array' fills the array with a given
;;; value.

;;; The function `fill-managed-g2-array-with-unmanaged-value' is used to fill
;;; managed-arrays with elements that do not need to be copied (non-managed
;;; values).  These values (integers, symbols, and integers of truth-values)
;;; should only be filled into arrays of the same element type.  Note that
;;; truth-value array elements contain only an integer value and not an
;;; evaluation-truth-value.

;;; The function `fill-managed-g2-array' checks the g2-array element-type and
;;; calls the one of the above functions to fill the managed-g2-array.


(defun fill-managed-g2-float-array (managed-float-array float-or-fixnum)
  (with-temporary-gensym-float-creation fill-managed-g2-float-array
    (cond
      ((slot-value-float-p float-or-fixnum)
       (fill-managed-float-array-with-managed-float
	 managed-float-array float-or-fixnum))
      ((gensym-float-p float-or-fixnum)
       (fill-managed-float-array managed-float-array float-or-fixnum))
      ((fixnump float-or-fixnum)
       (fill-managed-float-array
	 managed-float-array (coerce-to-gensym-float float-or-fixnum)))
      (t
       #+development
       (error
	 "Attempting to fill a float array with ~a, which is not an integer or float."
	 float-or-fixnum)))))

(defun fill-managed-g2-quantity-array (managed-g2-quantity-array quantity)
  ;; This function enters a temporary-float area.
  (fill-managed-g2-quantity-array-at-position
    managed-g2-quantity-array quantity 0))

(defun fill-managed-g2-text-array (managed-g2-text-array text-string)
  (fill-managed-g2-text-array-at-position
    managed-g2-text-array text-string 0))

(defun fill-managed-g2-item-array (managed-g2-item-array item?)
  (fill-managed-g2-item-array-at-position managed-g2-item-array item? 0))

(defun fill-managed-g2-value-array (managed-g2-value-array value)
  (fill-managed-g2-value-array-at-position managed-g2-value-array value 0))

(defun fill-managed-g2-item-or-value-array
    (managed-g2-item-or-value-array item-or-value?)
  (fill-managed-g2-item-or-value-array-at-position
    managed-g2-item-or-value-array item-or-value? 0))

(defun fill-managed-g2-array-with-unmanaged-value
    (managed-g2-array unmanaged-value)
  (fill-managed-array managed-g2-array unmanaged-value))

(defun fill-managed-g2-array (managed-g2-array item-or-value? element-type)
  (case element-type
    (float (fill-managed-g2-float-array managed-g2-array item-or-value?))
    ((number quantity)
     (fill-managed-g2-quantity-array managed-g2-array item-or-value?))
    (text (fill-managed-g2-text-array managed-g2-array item-or-value?))
    (datum (fill-managed-g2-value-array managed-g2-array item-or-value?))
    (item-or-datum
     (fill-managed-g2-item-or-value-array managed-g2-array item-or-value?))
    ((symbol integer truth-value)
     (fill-managed-g2-array-with-unmanaged-value
       managed-g2-array item-or-value?))
    ;; Item or subclass of item.
    (t (fill-managed-g2-item-array managed-g2-array item-or-value?))))



;;; The following functions fill the elements of a managed-g2-array starting at
;;; the specified position with a given value.  These functions are useful when
;;; the array has grown and the elements need initial or default values.  The
;;; functions vary depending on the type of value (and sometimes type of
;;; managed-g2-array) being used.

;; Note that we need an efficient managed-array fill at position!!  cpm, 6/18/91

;;; The function `fill-managed-g2-float-array-at-position' takes an integer or
;;; float and fills from the position with floats.

;;; The function `fill-managed-g2-quantity-array-at-position' takes an integer
;;; or and fills from position with that value.  The quanity is boxed as needed.

;;; The function `fill-managed-g2-text-array-at-position' fills from the
;;; position with copies of the text value.

;;; The function `fill-managed-g2-item-array-at-position' fills from the
;;; position with an item.  Note that item arrays alternate elements of items
;;; and item frame-serial-numbers.

;;; The function `fill-managed-g2-value-array-at-position' fills from the
;;; position with a value.

;;; The function `fill-managed-g2-item-or-value-array-at-position' fills from
;;; the position with an item or value.  Note that for items, it fills an item
;;; and item frame-serial-number for each element.

;;; The function `fill-managed-g2-array-at-position-with-unmanaged-value' fills
;;; with an unmanaged value (integer, symbol, integer of a truth-value).  These
;;; values should only be filled into arrays of the same element type.  This
;;; function should not be used to fill in value-arrays or item-or-value
;;; g2-arrays.

;;; The function `fill-managed-g2-array-at-position' tests the g2-array element
;;; type and calls the appropriate function to fill the managed-g2-array at the
;;; given position.


(defun fill-managed-g2-float-array-at-position
       (managed-non-text-g2-array float-or-fixnum start-position)
  (with-temporary-gensym-float-creation fill-managed-g2-float-array-at-position
    (let ((new-value
	   (normalize-to-gensym-float float-or-fixnum)))
      (loop for i from start-position below 
	    (managed-float-array-length managed-non-text-g2-array)
	    do
	(setf (managed-float-aref managed-non-text-g2-array i)
	      new-value)))))

(defun fill-managed-g2-quantity-array-at-position
       (managed-g2-quantity-array quantity start-position)
  (with-temporary-gensym-float-creation
    fill-managed-g2-quantity-array-at-position
    (loop with new-value = quantity
	  for i from start-position below 
	      (managed-array-length managed-g2-quantity-array)
	  do
      ;; Note that store-managed-number either reuses the old managed value or
      ;; creates new managed value and reclaims the old as necessary.
      (store-managed-number (managed-svref managed-g2-quantity-array i)
			    (copy-evaluation-value new-value)))))

(defun fill-managed-g2-text-array-at-position
       (managed-g2-text-array text-string start-position)
  (loop for i from start-position below 
	    (managed-array-length managed-g2-text-array)
	for copied-text-string = (copy-text-string text-string)
	do
    (setf (managed-svref managed-g2-text-array i) copied-text-string)))

(defun fill-managed-g2-item-array-at-position
       (managed-g2-text-array item? start-position)
  (loop with length = (managed-array-length managed-g2-text-array)
	with frame-serial-number? = (and item? (frame-serial-number item?))
	with i = (*f start-position 2)
	until (>=f i length)
	do
    (setf (managed-svref managed-g2-text-array i) item?)
    (setq i (+f i 1))
    (frame-serial-number-setf (managed-svref managed-g2-text-array i) frame-serial-number?)
    (setq i (+f i 1))))

(defun fill-managed-g2-value-array-at-position
       (managed-g2-value-array value start-position)
  (loop for i from start-position below
	      (managed-array-length managed-g2-value-array)
    do
    (setf (managed-svref managed-g2-value-array i)
	  (copy-and-box-element-value-if-necessary value))))

(defun fill-managed-g2-item-or-value-array-at-position
    (managed-g2-item-or-value-array item-or-value start-position)
  (loop with length = (managed-array-length managed-g2-item-or-value-array)
	with frame-p? = (and item-or-value (framep item-or-value))
	with frame-serial-number? =
	  (and frame-p? (frame-serial-number item-or-value))
	with i = (*f start-position 2)
	until (>=f i length)
	do
    (setf (managed-svref managed-g2-item-or-value-array i)
	  (if frame-p?
	      item-or-value
	      (copy-and-box-element-value-if-necessary item-or-value)))
    (setq i (+f i 1))
    ;; Set to the frame-serial-number or NIL (for non-items).
    (frame-serial-number-setf (managed-svref managed-g2-item-or-value-array i) frame-serial-number?)
    (setq i (+f i 1))))

;; Optimize the above function to only test for the value type once, to cache
;; the type, and then use this information when copying a new value for each
;; element.  - cpm, 12/19/93


(defun fill-managed-g2-array-at-position-with-unmanaged-value
    (managed-g2-array unmanaged-value start-position)
  (loop for i from start-position below 
	(managed-array-length managed-g2-array)
	do
    (setf (managed-svref managed-g2-array i) unmanaged-value)))


(defun fill-managed-g2-array-at-position
    (managed-g2-array item-or-value? start-position element-type)
  (case element-type
    (float
     (fill-managed-g2-float-array-at-position
       managed-g2-array item-or-value? start-position))
    ((number quantity)
     (fill-managed-g2-quantity-array-at-position
       managed-g2-array item-or-value? start-position))
    (text
     (fill-managed-g2-text-array-at-position
       managed-g2-array item-or-value? start-position))
    (datum
     (fill-managed-g2-value-array-at-position
       managed-g2-array item-or-value? start-position))
    (item-or-datum
     (fill-managed-g2-item-or-value-array-at-position
       managed-g2-array item-or-value? start-position))
    ((symbol integer truth-value)
     (fill-managed-g2-array-at-position-with-unmanaged-value
       managed-g2-array item-or-value? start-position))
    ;; Item or subclass of item.
    (t
     (fill-managed-g2-item-array-at-position
       managed-g2-array item-or-value? start-position))))




;;; The constant `symbol-initial-value-marker' is used to uniquely identify a
;;; symbol used in the initial-values attribute of value-array and g2-array.
;;; This marker can be used to distinguish these symbolic values from other
;;; designations.

;;; When testing for this value, use an EQUAL check.  (A pointer to this value
;;; is used in the slot-value-compilers, but the value is probably copied before
;;; being inserted into the slot.  Therefore, an EQ test does not work.)

;;; This marker is used in the slot-value-compilers for several grammar
;;; categories related to the initial-values slot for g2-arrays.

;;; Functions in the ARRAYS module tests for this value when initializing and
;;; filling in the inital values of some g2-arrays.

;;; An `initial value symbol' is a data abstraction used to represent an symbol
;;; in a G2 array.  For a given evaluation symbol S this is implemented as a
;;; 2-element slot-value list whose first element is EQUAL to
;;; symbol-initial-value-marker and whose second element is the evaluation value
;;; of S.

;;; Note that a symbol that is an element of an array that may contain items,
;;; i.e., an item array or item-or-value array, must be stored as an evaluation
;;; symbol with an initial value marker.  This distinguishes such a symbol from
;;; symbols used for other purposes, e.g., to refer to items by name.

;;; The macro `make-initial-value-symbol' takes an evaluation symbol and returns
;;; its equivalent representation as an initial value symbol.

;;; The macro `initial-value-symbol-p' takes an initial value (i.e., which is or
;;; could be an initial value in a G2 array) and returns true if it is an
;;; initial value symbol, otherwise nil.

;;; The macro `initial-value-symbol-value' returns the symbol that is the (raw)
;;; value of initial-value-symbol. (To make an evaluation symbol from this value,
;;; use make-evaluation-symbol.)

(defconstant symbol-initial-value-marker-symbol 'symbolic-initial-values)
(defconstant symbol-initial-value-marker (list symbol-initial-value-marker-symbol))

(defmacro make-initial-value-symbol (evaluation-symbol)
  `(slot-value-list-macro
     (slot-value-list-macro symbol-initial-value-marker-symbol)
     (evaluation-symbol-symbol ,evaluation-symbol)))

(def-substitution-macro initial-value-symbol-p (initial-value)
  (and (consp initial-value)
       (consp (car-of-cons initial-value))
       (null (cdr-of-cons (first-of-cons initial-value)))
       (eq (car-of-cons (first-of-cons initial-value))
	   symbol-initial-value-marker-symbol)))

(defmacro initial-value-symbol-value (initial-value-symbol)
  `(second-of-cons ,initial-value-symbol))

;; Implemented initial-value-symbol-p and initial-value-symbol-value today, and
;; then used them to replace explicit code in this module. (MHD 11/6/01)




(defun fill-values-into-managed-g2-float-array
    (managed-float-array list-of-floats? element-type
			 default-element-value)
  (loop for i from 0 below (managed-float-array-length
			     managed-float-array)
	for value in list-of-floats?
	do
    (cond ((slot-value-float-p value)
	   (with-temporary-creation
	       fill-values-into-managed-g2-float-array
	     (mutate-managed-float-array
	       managed-float-array i (slot-value-float-value value))))
	  ((evaluation-value-of-type-p value element-type)
	   (mutate-managed-float-array managed-float-array i value))
	  (t (mutate-managed-float-array
	       managed-float-array i default-element-value)))))
    
(defun fill-values-into-managed-g2-quantity-array 
    (managed-g2-quantity-array list-of-quantities element-type
			       default-element-value)
  (with-temporary-gensym-float-creation
      fill-values-into-managed-g2-quantity-array
    (loop for quantity in list-of-quantities
	  for new-value = (cond ((slot-value-float-p quantity)
				 (slot-value-float-value quantity))
				((evaluation-value-of-type-p
				   quantity element-type)
				 quantity)
				(t default-element-value))
	  for i from 0 below (managed-array-length managed-g2-quantity-array)
	  do
      (store-managed-number
	(managed-svref managed-g2-quantity-array i) new-value)))) ; boxing can be done inside.

(defun fill-values-into-managed-g2-text-array 
       (managed-g2-text-array list-of-text-strings? element-type
			      default-element-value)
  (loop for i from 0 below (managed-array-length managed-g2-text-array)
	for value in list-of-text-strings?
	for copied-text-string = (cond ((evaluation-value-of-type-p
					  value element-type)
					(copy-text-string value))
				       (t
					(copy-text-string
					  default-element-value)))
	do
    (setf (managed-svref managed-g2-text-array i) copied-text-string)))

(defun fill-values-into-managed-g2-item-array
    (managed-g2-array list-of-items? default-element-value)
  (loop with length = (managed-array-length managed-g2-array)
	for i from 0
	until (>=f i length)
	for value in list-of-items?
	for new-value = (cond ((and (framep value)
				    (class-is-subclass-of-item?
				      (class-description-slot value)))
			       value)
			      (t default-element-value))
	for frame-serial-number = (and (framep new-value)
				       (class-is-subclass-of-item?
					 (class-description-slot new-value))
				       (frame-serial-number new-value))
	do
    (setf (managed-svref managed-g2-array i) new-value)
    (setq i (+f i 1))
    (frame-serial-number-setf (managed-svref managed-g2-array i) frame-serial-number)
    (setq i (+f i 1))))

(defun fill-values-into-managed-g2-value-array
    (managed-g2-value-array list-of-values element-type
			    default-element-value)
  (loop for i from 0 below (managed-array-length managed-g2-value-array)
	for value in list-of-values
	for new-value = (cond ((or
				 (evaluation-value-of-type-p value element-type)
				 (and (slot-constantp value)
				      (consp (cdr value))
				      (eq (cadr value) 'truth-value)))
			       (copy-and-box-element-value-if-necessary value))
			      ((initial-value-symbol-p value)
			       (copy-and-box-element-value-if-necessary
				 (initial-value-symbol-value value)))
			      (t (copy-and-box-element-value-if-necessary
				   default-element-value)))
	do
    (setf (managed-svref managed-g2-value-array i) new-value)))

(defun fill-values-into-managed-g2-item-or-value-array
    (managed-g2-item-or-value-array list-of-items-or-values)
  (loop with length = (managed-array-length managed-g2-item-or-value-array)
	for i from 0
	until (>=f i length)
	for item-or-value in list-of-items-or-values
	with frame-p? = (and item-or-value (framep item-or-value))
	with frame-serial-number? =
	  (and frame-p? (frame-serial-number item-or-value))
	do
    (setf (managed-svref managed-g2-item-or-value-array i)
	  (if frame-p?
	      item-or-value
	      (copy-and-box-element-value-if-necessary item-or-value)))
    ;; Set to the frame-serial-number or NIL (for non-items).
    (setq i (+f i 1))
    (frame-serial-number-setf (managed-svref managed-g2-item-or-value-array i) frame-serial-number?)
    (setq i (+f i 1))))

(defun fill-unmanaged-values-into-managed-g2-array
    (managed-g2-array list-of-non-text-datum element-type default-element-value)
  (loop for i from 0 below (managed-array-length managed-g2-array)
	for datum in list-of-non-text-datum
	do
    (setf (managed-svref managed-g2-array i)
	  (cond ((or (evaluation-value-of-type-p datum element-type)
		     (and (eq element-type 'truth-value)
			  (fixnump datum)
			  (<=f datum 1000)
			  (>=f datum -1000)))
		 datum)
		((and (eq element-type 'symbol)
		      (initial-value-symbol-p datum))
		 ;; Symbol value.  The symbol is in this format to
		 ;; destinguish it from designations.
		 (initial-value-symbol-value datum))
		(t
		 default-element-value)))))

(defun fill-values-into-managed-g2-array
    (managed-g2-array list-of-items-or-values element-type
		      default-element-value)
  (case element-type
    (float
     (fill-values-into-managed-g2-float-array
       managed-g2-array list-of-items-or-values element-type
       default-element-value))
    
    ((number quantity)
     (fill-values-into-managed-g2-quantity-array
       managed-g2-array list-of-items-or-values element-type
       default-element-value))
    
    (text
     (fill-values-into-managed-g2-text-array
       managed-g2-array list-of-items-or-values element-type
       default-element-value))

    (datum
     (fill-values-into-managed-g2-value-array
       managed-g2-array list-of-items-or-values element-type
       default-element-value))

    (item-or-datum
     (fill-values-into-managed-g2-item-or-value-array
       managed-g2-array list-of-items-or-values))

    ((symbol integer truth-value)
     (fill-unmanaged-values-into-managed-g2-array
       managed-g2-array list-of-items-or-values element-type
       default-element-value))
    ;; Item or subclass of item.
    (t
     (fill-values-into-managed-g2-item-array
       managed-g2-array list-of-items-or-values default-element-value))))








;;;; G2-Array Operations




;;; The following operations apply to g2-arrays.  Some of these operations
;;; assume that the managed-g2-array is already present within the g2-array.

;;; They *DO NOT CHECK* for invalid array indices during a reference or setf and
;;; they *DO NOT CHECK* for invalid values during a setf!  These tests should be
;;; done in the calling routines, such as actions, evaluators, role-servers,
;;; etc.






;;;; G2-Array Predicates and Operations




;;; See also g2-list-or-array operations, such as g2-list-or-array-element-type
;;; and g2-list-or-array-class-element-type, defined in the LISTS module.



;;; The function `g2-array-or-list-default-element-value' returns the default
;;; element value for a g2-array or g2-list element.  This value depends on the
;;; g2-array-element-type or list-type.  For arrays the default value may be
;;; different from the g2-array-initial-values.  If there is no default value,
;;; nil is returned.

(defun g2-array-or-list-default-element-value (g2-array-or-list)
  (case (if (frame-of-class-p g2-array-or-list 'g2-array)
	    (g2-array-element-type g2-array-or-list)
	    (list-type g2-array-or-list))
    ((quantity number float datum) 0.0)
    (integer 0)
    (symbol 'g2)
    (text #w"")
    (truth-value falsity)
    ;; There is no default for item-array or g2-array.  The elements for these
    ;; arrays are initially "none".
    (t nil)))



;;; The function `g2-array-with-elements-p' tests if a managed-g2-array has been
;;; allocated and that the size is greater than 0.

(def-substitution-macro g2-array-with-elements-p (g2-array)
  (and (managed-g2-array g2-array) (>f (g2-array-length g2-array) 0)))



;;; The macro `g2-array-index-ok-p' tests if a given 0-based index is within the
;;; bounds of the g2-array.  The index argument must be an integer.  A valid
;;; index is >= 0 and < length.

(def-substitution-macro g2-array-index-ok-p (g2-array index)
  (let ((length (g2-array-length g2-array)))
    (and (fixnump index) (>=f index 0) (<f index length))))






;;; The macro `g2-array-length-ok-p' tests if a proposed g2-array length is
;;; valid.  The index argument must be an integer.  A valid length is <= 0 and
;;; <= the maximum length.

(def-substitution-macro g2-array-length-ok-p (g2-array proposed-length)
  (and (integerp proposed-length) (>=f proposed-length 0)
       (<=f proposed-length g2-array-length-maximum)))



;;; The function `g2-array-length-and-initial-values-match-p' is used to detect
;;; potential problems with initializing the array.  It is okay if either:
;;;   the number of initial-values is 1 or 0;
;;;   the array length equals the number of initial-values.

(defun g2-array-length-and-initial-values-match-p (array-length initial-values)
  (let ((initial-values-length (length initial-values)))
    (or (<=f initial-values-length 1) (=f array-length initial-values-length))))






;;;; G2-Array Accessor and Set Operations




;;; The function `g2-array-aset' is used in the setf of g2-array elements.  It
;;; does not check for a valid index or value.

;;; For item-arrays and item elements of g2-arrays, the item and the frame
;;; serial number are stored adjacently in the array.  Therefore, the index
;;; argument for item-arrays is adjusted within this function to account for the
;;; frame serial-number elements.

;;; This function boxes or copies any new values and reclaims any old element
;;; values as needed.  The new values are not evaluation-values.

(defun g2-array-aset (g2-array index item-or-datum?)
  (note-change-to-runtime-data-for-block g2-array)
  (let ((element-type (g2-array-element-type g2-array))
	(managed-g2-array (managed-g2-array g2-array)))
    (case element-type
      ((quantity number)
       (store-managed-number
	 (managed-g2-array-aref managed-g2-array index) item-or-datum?))
      ((float integer symbol truth-value)
       ;; Element-type of symbol, truth-value, integer, or float.  Should
       ;; be storing integers in truth-value array elements.
       (setf (managed-g2-array-aref managed-g2-array index) item-or-datum?))
      (text
       (let ((old-text-element? (managed-g2-array-aref managed-g2-array index)))
	 (when old-text-element? (reclaim-text old-text-element?))
	 (setf (managed-g2-array-aref managed-g2-array index)
	       (copy-text-string item-or-datum?))))
      (datum
       (let ((old-datum-element?
	       (managed-g2-array-aref managed-g2-array index)))
	 (when old-datum-element?
	   (reclaim-if-evaluation-value old-datum-element?))
	 (setf (managed-g2-array-aref managed-g2-array index)
	       (cond
		 ;; Evaluation truth-values are not really slot constants, and
		 ;; if this case was not here they would abort
		 ;; cast-slot-constant-into-evaluation-value.
		 ((evaluation-truth-value-p item-or-datum?)
		  (copy-evaluation-value item-or-datum?))
		 ((slot-constantp item-or-datum?)
		  ;; Text, numbers, and truth-value slot-constants.
		  (cast-slot-constant-into-evaluation-value item-or-datum?))
		 ((not (evaluation-value-p item-or-datum?))
		  (make-evaluation-value-from-non-logical-managed-value
		     item-or-datum?))
		 (t
		  (copy-evaluation-value item-or-datum?))))))
      (item-or-datum
       (let* ((adjusted-index (*f index 2))
	      (frame-p? (framep item-or-datum?))
	      (frame-serial-number?
		(if (and item-or-datum? frame-p?
			 (frame-of-class-p item-or-datum? 'item))
		    (frame-serial-number item-or-datum?)
		    nil))
	      (old-datum-element?
		(managed-g2-array-aref managed-g2-array adjusted-index))
	      (new-element
		(cond
		  (frame-p? item-or-datum?)
		  ;; Evaluation truth-values are not really slot constants, and
		  ;; if this case was not here they would abort
		  ;; cast-slot-constant-into-evaluation-value.
		  ;; Fixed for bug HQ-1095916
		  ;; "permanent g2 array with truth value in it aborts g2 on loading"
		  ;; -ajs (1/2/96)
		  ((evaluation-truth-value-p item-or-datum?)
		   (copy-evaluation-value item-or-datum?))
		  ((slot-constantp item-or-datum?)
		   ;; Text, numbers, and truth-value slot-constants.
		   (cast-slot-constant-into-evaluation-value
		     item-or-datum?))
		  ((not (evaluation-value-p item-or-datum?))
		   (make-evaluation-value-from-non-logical-managed-value
		     item-or-datum?))
		  (t
		   (copy-evaluation-value item-or-datum?)))))
	 (when old-datum-element?
	   (reclaim-if-evaluation-value old-datum-element?))
	 (setf (managed-g2-array-aref managed-g2-array adjusted-index)
	       new-element)
	 (frame-serial-number-setf (managed-g2-array-aref managed-g2-array (+f adjusted-index 1))
	       frame-serial-number?)))
      (t
       ;; Item-arrays.
       (let ((adjusted-index (*f index 2))
	     (frame-serial-number?
	       (if (and item-or-datum? (of-class-p item-or-datum? 'item))
		   (frame-serial-number item-or-datum?)
		   nil)))
	 (setf (managed-g2-array-aref managed-g2-array adjusted-index)
	       item-or-datum?)
	 (frame-serial-number-setf (managed-g2-array-aref managed-g2-array (+f adjusted-index 1))
	       frame-serial-number?))))))



;;; The function `g2-array-aref' is used to access the value in the g2-array.
;;; This function can be used to "setf" the value of the element.  This function
;;; returns a datum, item, or nil.  If the return datum value is managed, e.g.,
;;; managed gensym float, the cached value is returned.

;;; This return value can be nil only for item-arrays or item-or-value
;;; g2-arrays.  This is possible when the element has no value, if the element's
;;; item has been deleted, or if the element's item is not active.  Deleted
;;; items are determined by checking the frame-serial-number which is also
;;; stored in item-arrays.  An item-array index argument is of the same format
;;; as other g2-arrays (e.g., 0, 1, 2, ...), but internally the index is
;;; adjusted to account for the frame serial-number elements stored with the
;;; items in the managed-g2-array.

;;; This function does not do bounds checking on the array.  This function
;;; adjusts the index for item and item-or-value arrays, which have two elements
;;; per value, the item and the frame-serial-number.

;;; See g2-array-aref-item-or-evaluation-value for another type of aref
;;; operation.

(defun-simple g2-array-aref (g2-array index)
  (let ((managed-g2-array? (managed-g2-array g2-array)))
    (when managed-g2-array?
      (if (g2-list-or-array-element-type-may-contain-item-p
	    (g2-array-element-type g2-array))
	  (let ((item-or-value?
		  (managed-g2-array-aref managed-g2-array? (*f index 2)))
		(frame-serial-number?
		  (managed-g2-array-aref
		    managed-g2-array? (+f (*f index 2) 1))))
	    (if (and item-or-value?
		     (or (not (framep item-or-value?))
			 (and (not (deleted-frame-p item-or-value?))
			      (frame-serial-number-equal
				(frame-serial-number item-or-value?)
				frame-serial-number?))))
		item-or-value?
		nil))
	  (let ((datum (managed-g2-array-aref managed-g2-array? index)))
	    (if (managed-float-p datum)
		(cached-managed-float-value datum)
		datum))))))


(defsetf g2-array-aref g2-array-aset)


 
;;; `Convert-permanent-array-structure-for-saving' produces a lisp-style list
;;; from the values in the g2-array-structure.  This list will be saved out as
;;; the value of the managed-g2-array slot of g2-arrays.

(defun-simple convert-permanent-array-structure-for-saving (g2-array)
  (if (and (or (array-is-permanent g2-array)
	       (save-runtime-data? current-kb-save))
	   ;; This case is guarding against saving an initially non-permanent
	   ;; value-array that was changed to permanent while inactive (its
	   ;; elements are nulled out), and the array is not activated before
	   ;; saving.
	   (not (and (frame-of-class-p g2-array 'value-array)
		     (not (zerop (g2-array-length g2-array)))
		     (null (g2-array-aref g2-array 0)))))

      (let* ((current-module-being-saved? (kb-module-being-saved? current-kb-save))
	     (array-length (g2-array-length g2-array))
	     (real-array-length (managed-array-length (managed-g2-array g2-array))))
	;; GENSYMCID-1896: Saving a bundle KB didn't save all required KB modules
	;;
	;; Due to a bug in (def-slot-putter g2-array-length) it's possible that nominal
	;; array length is even larger then the size of underlying managed array. In this
	;; case LOOP only handles all actual array contents. --binghe, 6 Sep 2016
	(loop for index from 0 below (minf array-length real-array-length) ; old: array-length
	      for array-element = (g2-array-aref g2-array index)
	      for array-element-to-save?
	          = (if (framep array-element)
			(if (collectable-block-p array-element)
			    (let ((frame-denotation-to-save?
				    (if (or (eq (get-module-block-is-in array-element)
						current-module-being-saved?)
					    ;; Kb-module-being-saved?  will be null
					    ;; when the kb is being saved into a single file.
					    ;; See make-saving-context in KB-SAVE3.
					    (null current-module-being-saved?))
					array-element
					(block-denotation-p array-element))))
			      (cond ((framep frame-denotation-to-save?)
				     frame-denotation-to-save?)
				    (frame-denotation-to-save?
				     (slot-value-list
				       'frame-denotation frame-denotation-to-save?))
				    (t nil)))
			    nil)
			(if (deleted-frame-p array-element)
			    nil
			    (copy-for-slot-value array-element)))
	      when (or array-element-to-save?
		       (not (frame-of-class-p g2-array 'value-array)))
		collect array-element-to-save? using slot-value-cons))
      nil))


	   


;;; The post-loading function `convert-saved-array-values-to-g2-array-structure'
;;; converts the lisp array saved as the value of the managed-g2-array slot of
;;; g2-arrays into g2-array-structures.  When a array value is an uuid and
;;; there is no corresponding frame reference, the default value is used
;;; instead.

(def-post-loading-function (convert-saved-array-values-to-g2-array-structure
			     :once-only t)
    (loop for g2-array being each class-instance of 'g2-array
	  for saved-array-values = (access-once (managed-g2-array g2-array))
	  when (and saved-array-values (consp saved-array-values))
	    do
	      (let ((managed-g2-array
		      (allocate-managed-g2-array
			(g2-array-length g2-array)
			(g2-array-element-type g2-array)
			nil)))
		(atomic-exchange (managed-g2-array g2-array) managed-g2-array)
		(loop for value in saved-array-values
		      for index from 0 below (g2-array-length g2-array)
		      for value-to-set = (cond ((and (consp value)
						     (eq (car-of-cons value)
							 'frame-denotation))
						(find-frame-for-denotation
						  (second value) 'block))
					       ((framep value)
						value)
					       ((and (managed-float-p value)
						     (managed-float-array-p
						       managed-g2-array))
						value)
					       ((deleted-frame-p value)
						nil)
					       (t
						(copy-for-slot-value value)))
		      do
		  (g2-array-aset g2-array index value-to-set)
		      finally (reclaim-slot-value saved-array-values)))))




;;; The function `g2-array-aref-item-or-evaluation-value' takes a g2-array and
;;; an index, and it fetches the item or value stored at that location in the
;;; array.  Note that the different subclasses of value-array may contain
;;; evaluation-values or values of evaluation-values.

;;; If the value is an evaluation value, it is copied.  If it is a
;;; non-evaluation-value that needs to be managed, a new evaluation-value is
;;; created.  Note that in both cases, when an evaluation-value is returned, the
;;; caller of this function is responsible for reclaiming it.

(declare-side-effect-free-function g2-array-aref-item-or-evaluation-value)

(defun-simple g2-array-aref-item-or-evaluation-value (g2-array index)
  (let ((element-type (g2-array-element-type g2-array)))
    (cond
      ((null (managed-g2-array g2-array))
       ;; array has not been initialized
       nil)
      ((g2-list-or-array-element-type-may-contain-item-p element-type)
       ;; Item-array or item-or-value g2-array.
       (let ((item-or-value?
	       (managed-svref (managed-g2-array g2-array) (*f index 2)))
	     (frame-serial-number?
	       (managed-svref
		 (managed-g2-array g2-array) (+f (*f index 2) 1))))
	 (cond
	   ((null item-or-value?)
	    ;; No value.
	    nil)
	   ((not (frame-or-deleted-frame-p item-or-value?))
	    (copy-evaluation-value item-or-value?))
	   ((deleted-frame-p item-or-value?)
	    ;; deleted frame cannot be served.
	    nil)
	   ((frame-serial-number-equal (frame-serial-number item-or-value?) frame-serial-number?)
	    item-or-value?)
	   ;; A frame that cannot be served.
	   (t nil))))
      (t
       (case element-type
	  (integer
	   (managed-svref (managed-g2-array g2-array) index))
	  (float
	   (let ((managed-array (managed-g2-array g2-array)))
	     (make-evaluation-float
	       (managed-float-aref managed-array index))))
	  ((quantity number)
	   (let ((value (managed-svref (managed-g2-array g2-array) index)))
	     (if (or (evaluation-float-p value) (evaluation-long-p value))
		 (copy-evaluation-value value)
		 value)))
	  (text
	   (let ((text-element?
		   (managed-svref (managed-g2-array g2-array) index)))
	     (if text-element?
		 (copy-evaluation-text text-element?)
		 nil)))
	  (truth-value
	   (let ((value? (managed-svref (managed-g2-array g2-array) index)))
	     (if value?
		 (make-evaluation-truth-value value?)
		 nil)))
	  (datum
	   (let ((datum-element?
		   (managed-svref (managed-g2-array g2-array) index)))
	     (if datum-element?
		 (copy-evaluation-value datum-element?)
		 nil)))
	  ;; Symbols store the value directly.
	  (t
	   (managed-svref (managed-g2-array g2-array) index)))))))



;;; The function `mutate-g2-array-reclaiming-evaluation-values' is used as a
;;; mutator of g2 array elements, similar to g2-array-aset, except that it takes
;;; items or evaluation values as its item-or-datum?  argument, and reclaims or
;;; incorporates evaluation values into the g2-array.  It does not check for a
;;; valid index or value.

;;; For item-arrays and item-or-value g2-arrays, the item and the frame serial
;;; number are stored adjacently in the array.  Therefore, the index argument
;;; for item-arrays is adjusted within this function to account for the frame
;;; serial-number elements.  For item-arrays, if the item-or-datum arg is
;;; non-nil, the frame-serial-number is also added to the array.

(defun mutate-g2-array-reclaiming-evaluation-values
    (g2-array index item-or-datum?)
  (mutate-g2-array g2-array index item-or-datum? t t))

;(defun mutate-g2-array-reclaiming-evaluation-values
;    (g2-array index item-or-datum?)
;  (note-change-to-runtime-data-for-block g2-array)
;  (let ((element-type (g2-array-element-type g2-array)))
;    (cond
;      ((and (g2-list-or-array-element-type-may-contain-item-p element-type)
;            (not (eq element-type 'item-or-datum)))
;       ;; Item-arrays only.
;       (let ((adjusted-index (*f index 2))
;             (frame-serial-number?
;               (if (and item-or-datum? (of-class-p item-or-datum? 'item))
;                   (frame-serial-number item-or-datum?)
;                   nil)))
;         (setf (managed-svref (managed-g2-array g2-array) adjusted-index)
;               item-or-datum?)
;         (frame-serial-number-setf (managed-svref
;                 (managed-g2-array g2-array) (+f adjusted-index 1))
;               frame-serial-number?)))
;      (t
;       (case element-type
;         (float
;          (mutate-managed-float-array
;            (managed-g2-array g2-array) index
;            (evaluation-float-value item-or-datum?))
;          (reclaim-evaluation-float item-or-datum?))
;         ((quantity number)
;          (let* ((managed-array (managed-g2-array g2-array))
;                 (old-value (managed-svref managed-array index)))
;            (when (evaluation-float-p old-value)
;              (reclaim-evaluation-float old-value))
;            (setf (managed-svref managed-array index) item-or-datum?)))
;         (text
;          (let* ((managed-array (managed-g2-array g2-array))
;                 (old-text-element?
;                   (managed-svref managed-array index)))
;            (when old-text-element?
;              (reclaim-evaluation-text old-text-element?))
;            (setf (managed-svref managed-array index)
;                  item-or-datum?)))
;         (truth-value
;          (setf (managed-svref (managed-g2-array g2-array) index)
;                (evaluation-truth-value-value item-or-datum?))
;          (reclaim-evaluation-truth-value item-or-datum?))
;         (item-or-datum
;          (let* ((adjusted-index (*f index 2))
;                 (frame-serial-number?
;                   (if (and item-or-datum? (of-class-p item-or-datum? 'item))
;                       (frame-serial-number item-or-datum?)
;                       nil))
;                 (managed-array (managed-g2-array g2-array))
;                 (old-element? (managed-svref managed-array index)))
;            (when old-element?
;              (reclaim-if-evaluation-value old-element?))
;            (setf (managed-svref managed-array adjusted-index) item-or-datum?)
;            (frame-serial-number-setf (managed-svref managed-array (+f adjusted-index 1))
;                  frame-serial-number?)))
;         ;; Symbols and integers are all that is left, and they store the value
;         ;; directly.
;         (t
;          (setf (managed-svref (managed-g2-array g2-array) index)
;                item-or-datum?))))))
;  nil)



;;; The function `mutate-g2-array' places the given evaluation-value at the
;;; specified g2-array location.  If specified, the old element value is
;;; reclaimed and/or the new evaluation-value element is reclaimed or
;;; encorporated into the array.

;;; This function is useful in the sorting system procedures, when copying
;;; cached elements from a g2-list to a g2-array.  (The elements are still in
;;; the g2-list.

(defun mutate-g2-array
    (g2-array index item-or-datum? reclaim-old-value?
	      reclaim-new-datum-when-necessary?)
  (note-change-to-runtime-data-for-block g2-array)
  (let ((element-type (g2-array-element-type g2-array)))
    (cond
      ((and (g2-list-or-array-element-type-may-contain-item-p element-type)
	    (not (eq element-type 'item-or-datum)))
       ;; Item-arrays only.
       (let ((adjusted-index (*f index 2))
	     (frame-serial-number?
	       (if (and item-or-datum? (of-class-p item-or-datum? 'item))
		   (frame-serial-number item-or-datum?)
		   nil)))
	 (setf (managed-svref (managed-g2-array g2-array) adjusted-index)
	       item-or-datum?)
	 (frame-serial-number-setf
	   (managed-svref
	     (managed-g2-array g2-array) (+f adjusted-index 1))
	   frame-serial-number?)))
      (t
       (case element-type
	 (float
	  (mutate-managed-float-array
	    (managed-g2-array g2-array) index
	    (evaluation-float-value item-or-datum?))
	  (when reclaim-new-datum-when-necessary?
	    (reclaim-evaluation-float item-or-datum?)))
	 ((quantity number datum)
	  (let* ((managed-array (managed-g2-array g2-array))
		 (old-value? (managed-svref managed-array index)))
	    (when (and reclaim-old-value? old-value?)
	      ;; this is quicker that doing evaluation-value-p & then reclaiming
	      (reclaim-if-evaluation-value old-value?))
	    (setf (managed-svref managed-array index) item-or-datum?)))
	 (text
	  (let* ((managed-array (managed-g2-array g2-array))
		 (old-text-element? (managed-svref managed-array index)))
	    (when (and reclaim-old-value? old-text-element?)
	      (reclaim-evaluation-text old-text-element?))
	    (setf (managed-svref managed-array index)
		  item-or-datum?)))
	 (truth-value
	  (setf (managed-svref (managed-g2-array g2-array) index)
		(evaluation-truth-value-value item-or-datum?))
	  (when reclaim-new-datum-when-necessary?
	    (reclaim-evaluation-truth-value item-or-datum?)))
	 (item-or-datum
	  (let* ((adjusted-index (*f index 2))
		 (frame-serial-number?
		   (if (and item-or-datum? (of-class-p item-or-datum? 'item))
		       (frame-serial-number item-or-datum?)
		       nil))
		 (managed-array (managed-g2-array g2-array))
		 (old-element? (managed-svref managed-array adjusted-index)))
	    (when (and old-element? reclaim-old-value?)
	      (reclaim-if-evaluation-value old-element?))
	    (setf (managed-svref managed-array adjusted-index) item-or-datum?)
	    (frame-serial-number-setf
	      (managed-svref managed-array (+f adjusted-index 1))
	      frame-serial-number?)))
	 ;; Symbols and integers are all that is left, and they store the value
	 ;; directly.
	 (t
	  (let ((managed-array (access-once (managed-g2-array g2-array))))
	    (setf (managed-svref managed-array index) item-or-datum?)))))))
  nil)



;;; The non-standard macro `do-g2-array-elements' can be used to iterate over
;;; the elements (datum or items) in a g2-array.
;;;
;;; Body may use RETURN to return (reliably) a single value only from the block
;;; implicitly set up by this iteration loop; in this case, or in case of a
;;; throw or return to an explicit block name, the result form will not be
;;; evaluated.  But normally, at the end of the iteration result-form is
;;; evaluated and all of its values are returned.
;;;
;;; This macro has similarities to dolist. Here the caller provides a variable
;;; for the element, which is not evaluated, a g2-array, a result-form, and a
;;; body of code for the iteration.  The body of code may, of course, reference
;;; the variable that the caller specified for the element.  The element value
;;; is either an item, a cached non-managed value, managed-value, or nil, which
;;; means no-value.  A cached non-managed value should be copied when necessary
;;; and not be held on to.  If an item in the array is inactive or deleted, the
;;; element value is nil, which means no-value.

;;; The macro is non-standard since only the g2-array argument is evaluated.

;;; NOTE: this may or may not invoke with-temporary-gensym-float-creation around
;;; body, one or more times.  The body code should be written to run safely in
;;; all such scenarios.  (The implementation has historically wavered on this,
;;; or had different behaviors based on type. The current rule seems a simple
;;; and acceptable one.)

(defmacro do-g2-array-elements ((var g2-array result-form) &body body)
  (let ((array '#:array)
	(items-possible-p '#:items-possible-p)
	(managed-g2-array '#:managed-g2-array)
	(array-length '#:array-length)
	(managed-step-size '#:managed-step-size)
	(managed-length '#:managed-length)
	(element-type '#:element-type)
	(inner-index '#:inner-index)
	(outer-index '#:outer-index)
	(float-or-quantity-p '#:float-or-quantity-p)
	(max-inner-index '#:max-inner-index)
	(inner-block-name '#:inner-block-name))
    `(loop with ,array = ,g2-array
	   with ,element-type = (g2-array-element-type ,array)
	   with ,items-possible-p
	     = (g2-list-or-array-element-type-may-contain-item-p ,element-type)
	   with ,managed-g2-array
	     = (access-once (managed-g2-array ,array))
	   initially
	     (when (null ,managed-g2-array)
	       (return nil))
	   with ,array-length fixnum
	     = (access-once (g2-array-length ,array))
	   with ,managed-step-size fixnum = (if ,items-possible-p 2 1)
	   with ,managed-length fixnum = (*f ,array-length ,managed-step-size)
	   with ,float-or-quantity-p = (or (eq ,element-type 'float) (eq ,element-type 'quantity))
	   with ,max-inner-index fixnum = (if ,float-or-quantity-p 100 ,managed-length)
	   with ,outer-index fixnum = 0
	   while (<f ,outer-index ,managed-length)
	   do (with-temporary-gensym-float-creation do-g2-array-with-quantity-elements
		(loop
		  ;; We provide an arbitrary non-nil inner loop block name so
		  ;; that the body code may use RETURN to return from the
		  ;; implicit nil block set up by the outer loop.
		  named ,inner-block-name
		     for ,inner-index from 0 below ,max-inner-index
		     as ,var
			= (if (eq ,element-type 'float)
			      (managed-float-aref ,managed-g2-array ,outer-index)
			      (let ((elt (managed-svref ,managed-g2-array ,outer-index)))
				(if (or (not ,items-possible-p)
					(and elt
					     (or (not (frame-or-deleted-frame-p elt))
						 (and (frame-serial-number-equal
							(frame-serial-number elt)
							(managed-svref
							  ,managed-g2-array
							  (+f ,outer-index 1)))
						      (or (active-p elt)
							  (array-is-permanent
							    ,array))))))
				    elt)))
		     do (progn
			  ,@body
			  (incff ,outer-index ,managed-step-size))
		     while (<f ,outer-index ,managed-length)))
	   finally (return ,result-form))))

;; Define DO-G2-ARRAY-ELEMENTS in terms of a new LOOP iteration path.  See the
;; one for g2-lists.  But, there are several difficulties in doing this.  First
;; is that there are several ways of implementing depending on the g2-array
;; element-type.  Second, for float-arrays the iteration needs to enter a
;; temporary float-area to prevent consing, and to exit and then re-enter to
;; prevent overflow of the area.  - cpm, 4/12/94

;; Note: the above was revised and rewritten today to just have one case for all
;; array types. There had been multiple branches all repeating the body,
;; resulting in potentially enormous expansions, not to mention much duplicated
;; code.  The code does very minimal amount of branching in the inner loop, and
;; we doubt the will seriously get in the way of hardware and compiler
;; optimizations.  There is negligeable cost to entering and exiting a temporary
;; float creation context (at least once) in all cases, or having an inner/outer
;; loop structure, so there is no point to dividing these into separate
;; cases.
;;
;; (MHD 10/31/01)






;;;; G2-Array Initialize and Fill Operations




;;; The function `initialize-g2-array' fills the managed-g2-array according to
;;; the initial-value(s) or default-values of the g2-array.  The
;;; managed-g2-array must already be allocated and in the g2-array.  If the
;;; initial-values are not valid, a WARNING MESSAGE is displayed and the
;;; default-value, if any, is used.

;; jh, 8/16/94.  Added the switch do-not-initialize-g2-array-elements-p to
;; initialize-g2-array for the object-passing project.  For further details, see
;; my note this date in the module RPC-COMMON2.

(defvar do-not-initialize-g2-array-elements-p nil)

(defun initialize-g2-array
    (g2-array &aux (length (access-once (g2-array-length g2-array)))
		   (element-type (access-once (g2-array-element-type g2-array))))
  ;; indent is wrong
  (cond
    ((access-once (managed-g2-array g2-array))
     (unless (or (consp (managed-g2-array g2-array))
		 (and (array-is-permanent g2-array)
		      (managed-g2-array g2-array)
		      (or (not (frame-of-class-p g2-array 'value-array))
			  ;; This case is guarding against the possibility
			  ;; of not initializing an inactive non-permanent value array
			  ;; that has been edited to be permanent but not yet activated.
			  (and (not (zerop length))
			       (g2-array-aref g2-array 0))))
		 warmbooting?)
       (when (g2-array-with-elements-p g2-array)
	 (cond ((finish-initialization-of-cloned-g2-array-p g2-array)
		(finish-initialization-of-cloned-g2-array g2-array))
	       (t (unless do-not-initialize-g2-array-elements-p
		    (unless (fill-g2-array-with-initial-values-if-possible
			      g2-array)
		      ;; The initial-values were not valid.  A warning has been
		      ;; displayed.  Fill with the default, if any.
		      (fill-g2-array-with-default-values g2-array))))))))
    (t
     (when (if warmbooting?
	       (zerop length)
	       (not (and (array-is-permanent g2-array) (zerop length))))
       (atomic-exchange (managed-g2-array g2-array)
			(allocate-managed-g2-array length element-type nil nil))
       (when (g2-array-with-elements-p g2-array)
	 (cond ((finish-initialization-of-cloned-g2-array-p g2-array)
		(finish-initialization-of-cloned-g2-array g2-array))
	       (t (unless do-not-initialize-g2-array-elements-p
		    (unless (fill-g2-array-with-initial-values-if-possible g2-array)
		      ;; The initial-values were not valid.  A warning has been
		      ;; displayed.  Fill with the default, if any.
		      (fill-g2-array-with-default-values g2-array)))))))))
   (barrier)
   nil)


;;; The function `finish-initialization-of-cloned-g2-array' completes the
;;; initialization of a g2-array that is being cloned.  The managed-array slot
;;; value is converted from a format (set in clone-frame) that prevents the
;;; regular (non-cloning) initialization code from executing.

(defun finish-initialization-of-cloned-g2-array (g2-array)
  (let ((managed-g2-array-or-cons (access-once (managed-g2-array g2-array))))
    (when (consp managed-g2-array-or-cons)
      (atomic-exchange (managed-g2-array g2-array)
		       (car-of-cons managed-g2-array-or-cons))
      (reclaim-slot-value-cons managed-g2-array-or-cons))))

(defun finish-initialization-of-cloned-g2-array-p (g2-array)
  (let ((managed-g2-array-or-cons (access-once (managed-g2-array g2-array))))
    (and (consp managed-g2-array-or-cons)
	 (eq (cdr-of-cons managed-g2-array-or-cons) 'cloned-managed-array))))



;;; The function `fill-g2-array-with-default-values' fills the elements of the
;;; g2-array with the default values for that element-type.  The default values
;;; are copied for managed-values (e.g., text-strings).  Note that item-arrays
;;; currently have a default of "no value" (NIL).

(defun fill-g2-array-with-default-values (g2-array)
  (fill-managed-g2-array
    (managed-g2-array g2-array)
    (g2-array-or-list-default-element-value g2-array)
    (g2-array-element-type g2-array)))

;; Note that this function needs to be modified if item-arrays have a non-NIL
;; default value.  The non-NIL default would then need to be evaluated as a
;; designation.  - cpm, 1/7/94



;;; The function `fill-g2-array-with-initial-values-if-possible' attempts to
;;; fill the managed-g2-array with the initial-value(s) of the g2-array.  When
;;; filling the array initial-values are copied as necessary (e.g., for
;;; text-strings).

;;; If there is one initial-value, the array is filled with this value and T is
;;; returned.  If there is more than one initial-value, the number of values
;;; must equal the number of array-elements.  If this is true, the values are
;;; placed in the array in order and T is returned.  Otherwise, no initial
;;; values are entered and NIL is returned.  If the initial-values are "none",
;;; for example in item-arrays, NIL is returned.

;;; When filling an item-array, the initial-values are validated with the
;;; g2-array-element-type.  If any values are invalid, a WARNING MESSAGE is
;;; displayed and those elements are given a NIL value, which is no value.

(defun fill-g2-array-with-initial-values-if-possible (g2-array)
  (let ((list-of-initial-values
	  (access-once (g2-array-initial-values g2-array)))
	(managed-g2-array
	  (access-once (managed-g2-array g2-array)))
	(element-type
	  (access-once (g2-array-element-type g2-array)))
	(default-element-value
	  (g2-array-or-list-default-element-value g2-array))
	initial-value
	(result? t))
    (cond ((null list-of-initial-values)
	   ;; Item-arrays and item-or-value g2-arrays may have no
	   ;; initial-values.  By default, the initial-values and the contents
	   ;; of the managed-array are NIL.
	   (setq result? nil))

	  ;; Item-arrays and item-or-value g2-arrays.
	  ((g2-list-or-array-element-type-may-contain-item-p element-type)
	   (fill-g2-item-array-or-g2-array-with-initial-values-if-possible
	     g2-array list-of-initial-values))

	  ;; Fill with the one initial value.
	  ((null (cdr list-of-initial-values))
	   (setq initial-value (first list-of-initial-values))
	   (cond ((or (evaluation-value-of-type-p initial-value element-type)
		      (and (slot-constantp initial-value)
			   (consp (cdr initial-value))
			   (eq (cadr initial-value) 'truth-value))
		      
		      (and (eq element-type 'truth-value)
			   (fixnump initial-value)
			   (<=f initial-value 1000)
			   (>=f initial-value -1000)))
		  (fill-managed-g2-array
		    managed-g2-array initial-value element-type))
		 (t
		  (fill-managed-g2-array
		    managed-g2-array default-element-value element-type))))
	  ;; Fill with list of values.
	  ((=f (access-once (g2-array-length g2-array))
	       (length list-of-initial-values))
	   (fill-values-into-managed-g2-array
	     managed-g2-array list-of-initial-values element-type
	     default-element-value))

	  (t
	   ;; Cannot fill with initial values.  The number of initial values
	   ;; conflicts with the array length.  The array should then be filled
	   ;; with the default value for that type of array.

           ;;; Note that a warning message is not displayed to the user.  But,
           ;;; the array should already contain a frame note describing the
           ;;; array initial values and length conflict.
	   (setq result? nil)))
    result?))



;;; The function
;;; `fill-g2-item-array-or-g2-array-with-initial-values-if-possible' attempts to
;;; fill the item-array or item-or-value g2-array with the initial values.  The
;;; number of initial values must be correct, i.e., a list of one value or a
;;; list of values whose length is equal to the array length.

;;; Each initial value must be a subclass of the element-type.  If this is not
;;; true, a WARNING MESSAGE is displayed and NIL is returned.  Otherwise, T is
;;; returned.

;;; When an initial value can not be filled in for an element, the element value
;;; is set to nil.

(defun fill-g2-item-array-or-g2-array-with-initial-values-if-possible
       (g2-array initial-value-list)
  (cond ((null (cdr initial-value-list))
	 (fill-g2-item-array-or-g2-array-with-initial-value
	   g2-array (car initial-value-list)))
	(t
	 (fill-g2-item-array-or-g2-array-with-initial-value-list
	   g2-array initial-value-list))))



;;; The function `fill-g2-item-array-or-g2-array-with-initial-value' fills the
;;; given item-array or item-or-value g2-array with the one initial-value, if
;;; possible.  Note that the initial-value is a designation that is evaluated.
;;; Also, for item-or-value g2-arrays, it can be a non-designation.

;;; If the initial value is correct for this array T is returned, otherwise NIL
;;; is returned.

;;; Note that item-or-value g2-arrays need to test for "marked" symbols.  This
;;; are symbols that have been converted to a format that distinguishes them
;;; from item designations.

(defun fill-g2-item-array-or-g2-array-with-initial-value
    (g2-array item-designation-or-value?)
  (let* ((item-or-value-array-p?
	   (eq (g2-array-element-type g2-array) 'item-or-datum))
	 (managed-g2-array (access-once (managed-g2-array g2-array)))
	 (designation-p? (designation-p-function item-designation-or-value?))
	 (*current-computation-frame* g2-array)
	 (item-or-temporary-constant?
	   (and designation-p?
		(evaluate-designation item-designation-or-value? nil)))
	 (valid-initial-item-or-value?
	   (cond
	     ((not item-or-value-array-p?)
	      ;; Item-array
	      (and item-or-temporary-constant?
		   (not (temporary-constant-p item-or-temporary-constant?))
		   (of-class-p
		     item-or-temporary-constant?
		     (g2-array-element-type g2-array))
		   item-or-temporary-constant?))
	     ;; Check for valid item or datum for the item-or-value g2-array.
	     ((null item-or-temporary-constant?)
	      (cond (designation-p? nil)
		    ((null item-designation-or-value?) nil)
		    ((initial-value-symbol-p item-designation-or-value?)
		     ;; Symbol value.  The symbol is in this format to
		     ;; destinguish it from designations.
		     (initial-value-symbol-value item-designation-or-value?))
		    (t item-designation-or-value?)))
	     ((temporary-constant-p item-or-temporary-constant?)
	      item-or-temporary-constant?)
	     ((of-class-p item-or-temporary-constant? 'item)
	      ;; Currently, item-or-value g2-arrays can only have an
	      ;; element-type of item-or-datum.  So, only test for item here.
	      item-or-temporary-constant?)
	     ;; Else, item is not of the correct class.
	     (t nil)))
	 (result? t))
    (cond
      ((null valid-initial-item-or-value?)
       (when item-or-temporary-constant?
	 (reclaim-if-temporary-constant item-or-temporary-constant?))
       (setq result? nil))
      (item-or-value-array-p?
       (fill-managed-g2-item-or-value-array
	 managed-g2-array valid-initial-item-or-value?)
       (when item-or-temporary-constant?
	 (reclaim-if-temporary-constant item-or-temporary-constant?)))
      (t
       (fill-managed-g2-item-array
	 managed-g2-array valid-initial-item-or-value?)))
  result?))



;;; The function `fill-g2-item-array-or-g2-array-with-initial-value-list' fills
;;; the given item-array or item-or-value g2-array with the list of
;;; initial-values, if possible.  Note that the initial-values which are
;;; designations that are evaluated.  Initial-values for item-arrays must be
;;; designations.  Initial-values for item-or-value g2-arrays can be item
;;; designations or values.

;;; If the initial values are all correct for this array T is returned,
;;; otherwise NIL is returned.  The value NIL will be used to fill the location
;;; of any element that has an invalid initial-value.

;;; Note that item-or-value g2-arrays need to test for "marked" symbols.  This
;;; are symbols that have been converted to a format that distinguishes them
;;; from item designations.

(defun fill-g2-item-array-or-g2-array-with-initial-value-list
    (g2-array item-designation-or-value-list)
  (let* ((*current-computation-frame* g2-array)
	 (item-or-value-array-p?
	   (eq (g2-array-element-type g2-array) 'item-or-datum))
	 (result? t))
  (loop for item-designation-or-value in item-designation-or-value-list
	for designation-p? =
   	    (designation-p-function item-designation-or-value)
	for item-or-temporary-constant? = 
	    (and designation-p?
		 (evaluate-designation item-designation-or-value nil))
	for valid-initial-item-or-value? =
	   (cond
	     ((not item-or-value-array-p?)
	      ;; Item-array
	      (and item-or-temporary-constant?
		   (not (temporary-constant-p item-or-temporary-constant?))
		   (of-class-p
		     item-or-temporary-constant?
		     (g2-array-element-type g2-array))
		   item-or-temporary-constant?))
	     ;; Check for valid item or datum for the item-or-value g2-array.
	     ((null item-or-temporary-constant?)
	      (cond (designation-p? nil)
		    ((null item-designation-or-value) nil)
		    ((and (consp item-designation-or-value)
			  (equal (car item-designation-or-value)
				 symbol-initial-value-marker))
		     ;; Symbol value.  The symbol is in this format to
		     ;; destinguish it from designations.
		     (cadr item-designation-or-value))
		    (t item-designation-or-value)))
	     ((temporary-constant-p item-or-temporary-constant?)
	      ;; Copy the value because it is being put diretly into the array
	      ;; location.
	      (let ((temporary-constant item-or-temporary-constant?))
		;; Prevent double reclamation.
		(setq item-or-temporary-constant? nil)
		(transform-temporary-constant-into-evaluation-value
		  temporary-constant)))
	     ((of-class-p item-or-temporary-constant? 'item)
	      ;; Currently, item-or-value g2-arrays can only have an
	      ;; element-type of item-or-datum.  So, only test for item here.
	      item-or-temporary-constant?)
	     ;; Else, item is not of the correct class.
	     (t nil))
	for index from 0 below (g2-array-length g2-array)
	;; Array length and length of the initial-values list should be equal.
	do
    ;; Fill the item-array with the initial-values list if possible.
    (when (null valid-initial-item-or-value?)
      (setq result? nil))
    ;; When there is an error initializing an element, the element will
    ;; receive a value of "none" (NIL).  This is the default value for
    ;; item-array and item-or-value g2-array elements.
    (cond ((null valid-initial-item-or-value?)
	   (setf (g2-array-aref g2-array index) nil))
	  (t
	   ;; The setf fills in a datum or an item and an item-serial number.
	   (setf (g2-array-aref g2-array index) valid-initial-item-or-value?)))
    (when item-or-temporary-constant?
      (reclaim-if-temporary-constant item-or-temporary-constant?)))
  result?))



;;; The function `initialize-g2-array-at-position' fills in the managed-g2-array
;;; starting at the 0-based starting-position according to the initial-value(s)
;;; or default-values of the g2-array.  The managed-g2-array must already be
;;; allocated and in the g2-array.  If the initial-values do not contain only
;;; one or no value and the initialization is not starting at the first element,
;;; the default-value is used.  This function is called when the g2-array is
;;; being adjusted to a bigger length.

;;; Note that item-or-value g2-arrays need to test for "marked" symbols.  This
;;; are symbols that have been converted to a format that distinguishes them
;;; from item designations.

(defun-void initialize-g2-array-at-position (g2-array starting-position)
  (let* ((initial-values? (g2-array-initial-values g2-array))
	 (initial-value? (first initial-values?))
	 (element-type (g2-array-element-type g2-array)))
    (cond
      ;; No initialization.  Either there are no elements or no initial-values.
      ((or (not (g2-array-with-elements-p g2-array))
	   (null initial-values?))
       nil)
      ;; More than one initial-value (item or datum).
      ((cdr initial-values?)
       (cond ((and (= starting-position 0)
		   (g2-array-length-and-initial-values-match-p
		     (g2-array-length g2-array) initial-values?))
	      (initialize-g2-array g2-array))
	     ((g2-array-or-list-default-element-value g2-array)
	      ;; Use the default value, if any, because the initialization
	      ;; is not starting at the first element.
	      (fill-g2-array-at-position
		g2-array (g2-array-or-list-default-element-value g2-array)
		starting-position))))
      ;; One non-item initial-value for a value array.
      ((not (g2-list-or-array-element-type-may-contain-item-p element-type))
       (fill-g2-array-at-position
	 g2-array initial-value? starting-position))
      ;; One initial-value for item-array or item-or-value g2-array.
      (t
       (let*
	   ((item-or-value-array-p?
	      (eq (g2-array-element-type g2-array) 'item-or-datum))
	    (designation-p? (designation-p-function initial-value?))
	    (*current-computation-frame* g2-array)
	    (item-or-temporary-constant?
	      (and designation-p? (evaluate-designation initial-value? nil)))
	    (valid-initial-item-or-value?
	      (cond
		((not item-or-value-array-p?)
		 ;; Item-array
		 (and item-or-temporary-constant?
		      (not (temporary-constant-p item-or-temporary-constant?))
		      (of-class-p
			item-or-temporary-constant?
			(g2-array-element-type g2-array))
		      item-or-temporary-constant?))
		;; Check for valid item or datum for the item-or-value g2-array.
		((null item-or-temporary-constant?)
		 (cond (designation-p? nil)
		       ((null initial-value?) nil)
		       ((initial-value-symbol-p initial-value?)
			;; Symbol value.  The symbol is in this format to
			;; destinguish it from designations.
			(initial-value-symbol-value initial-value?))
		       (t initial-value?)))
		 ((temporary-constant-p item-or-temporary-constant?)
		  item-or-temporary-constant?)
		 ((of-class-p item-or-temporary-constant? 'item)
		  ;; Currently, item-or-value g2-arrays can only have an
		  ;; element-type of item-or-datum.  So, only test for item
		  ;; here.
		  item-or-temporary-constant?)
		 ;; Else, item is not of the correct class.
		 (t nil))))
	 ;; If there is an error in initializing for an item or
	 ;; item-or-value g2-array, the elements will be left as "no value"
	 ;; (NIL).  There is no default value in this case.
	 (cond
	   ((null valid-initial-item-or-value?)
	    (when item-or-temporary-constant?
	      (reclaim-if-temporary-constant item-or-temporary-constant?)))
	   (t
	    (fill-g2-array-at-position
	      g2-array valid-initial-item-or-value? starting-position)
	    (when item-or-value-array-p?
	      (reclaim-if-temporary-constant
		valid-initial-item-or-value?)))))))
    (barrier)))

;; Modify the above function if the default for item-array and item-or-value
;; arrays change.  The default is currently "none" (NIL).  If it changes to an
;; item, then the designation needs to be evaluated before initializing the
;; array.  - cpm, 1/7/94



;;; The function `fill-g2-array-at-position' fills a managed-g2-array with the
;;; item or value beginning at the starting position to the end of the array.

;;; Note that the type of the thing (item or value) being put in the array
;;; should match the type of the array.

(defun fill-g2-array-at-position (g2-array item-or-value? starting-position)
  (fill-managed-g2-array-at-position
    (access-once (managed-g2-array g2-array))
    item-or-value?
    starting-position
    (g2-array-element-type g2-array)))



;;; The function `validate-and-fix-g2-item-array-elements' checks that all
;;; item-array elements are either "no value" or of the given element-type
;;; class.  Any invalid elements are fixed by setting that array element to
;;; "none", i.e., NIL.  The element-type is passed as an argument because it may
;;; be a new element-type that is not yet installed in the array.  This function
;;; assumes that the managed-g2-array is already allocated.

;;; If all elements are valid and none are fixed or if there are no elements, T
;;; is returned.  Otherwise, NIL is returned.

(defun validate-and-fix-g2-item-array-elements (g2-array new-element-type)
  (let ((ok? t))
    (loop for i from 0 below (g2-array-length g2-array)
	  for item? = (g2-array-aref g2-array i)
	  do
      (when (and item? (not (of-class-p item? new-element-type)))
	(setq ok? nil)
	(setf (g2-array-aref g2-array i) nil)))
    ok?))






;;;; Validating G2-Arrays




;;; G2-array elements many need to be validated when either the array
;;; element-type or the elements of an array have changed.  Currently, the array
;;; element-type can only be changed by the user for item-arrays, and only when
;;; G2 is reset.  So, only arrays containing elements that can change at runtime
;;; need to be validated.  This is necessary for items-arrays when definitions
;;; change such that the class of an item may have changed.




;;; The function `validate-all-item-arrays' checks that elements of all
;;; item-arrays do not conflict with the arrays' element-type.  If the item
;;; element does conflict, then that array location is set to NIL ("no value").

;;; This function is called, for example, when a definition changes at runtime,
;;; such that the classes of item may have changed.

;;; The class? and old-class? arguments, if non-NIL, specify the class or
;;; classes of the list elements that need to be validated.  If both arguments
;;; are NIL, then all elements of item-arrays, will be validated.

;;; Note that this function does not attempt to update any role servers that are
;;; currently serving array elements.

(defun-void validate-all-item-arrays (class? old-class?)
  (loop for item-array being each class-instance of 'item-array
	for element-type = (g2-array-element-type item-array)
	do
    ;; Validate only those item-arrays that could have been affected by the
    ;; class changes, as specified by the arguments.
    (when (and (not (eq element-type 'item))
	       (or (and (null class?) (null old-class?))
		   (and class? (subclassp element-type class?))
		   (and old-class?
			;; EQ test, in case the old-class is no longer defined.
			(or (eq element-type old-class?)
			    (subclassp element-type old-class?)))))
      (validate-and-fix-g2-item-array-elements item-array element-type)))
  nil)






;;;; Reading and Writing Arrays for KB




;;; `Write-g2-array-data-for-kb' is called by write-runtime-data-for-kb (see
;;; KB-SAVE1).  It is here, rather than in KB-SAVE1, because it uses macros
;;; defined in ARRAYS.

(defun write-g2-array-data-for-kb (g2-array)
  (when (active-p g2-array)
    (let* ((array-length (g2-array-length g2-array))
	   (element-type (g2-list-or-array-element-type g2-array)))
      (when (>f array-length 0)
	(write-left-bracket-if-necessary)
	(write-char-for-kb #\A)
	(write-fixnum-for-kb array-length)
	(do-g2-array-elements (element-value? g2-array nil)
	  (write-g2-list-or-array-element-for-kb
	    element-value? element-type))))))

;; This could be made more efficient by checking the array type and
;; calling more specific functions than write-element-for-kb.  It would
;; be good to have a write-truth-value-for-kb, a write-float-for-kb, and
;; a write-quantity-for-kb.  It could also be made more efficient for
;; managed floats.  Write-element-for-kb currently wraps a
;; with-temporary...  for these.  It would be more efficient to include
;; many writes within such a wrapper.



;;; `Read-array-data' is called by read-runtime-data-for-block.  It allocates a
;;; managed-g2-array as the data structure for squirreling and fills it with the
;;; array values.  The managed-g2-array slot of the g2-array is set to
;;; initialization inhibit which indicates to the activate method that a
;;; managed-g2-array should not be allocated.  This also prevents the activate
;;; method from putting the g2-array into items-needing-initialization.  This
;;; approach is best since it avoids the inefficiencies of squirreling away the
;;; data in an intermediate data structure or of having to reclaim an extra
;;; managed-g2-array allocated at activation.  This also points out that
;;; squirreling isn't really necessary for arrays; it is only necessary to
;;; inhibit the action of the activate method.

(defun read-array-data (g2-array)
  (let ((array-length (read-element-for-kb nil))
	(managed-g2-array nil))
    #+development
    (when (not (=f array-length (g2-array-length g2-array)))
      (cerror
	"Continue"
	"Array-length of existing array not compatible with what was saved."))
    (setq managed-g2-array
	  (allocate-managed-g2-array
	    (g2-array-length g2-array)
	    (g2-array-element-type g2-array)
	    nil nil))
    ;; When the g2-array is a permanent array, the slot will have a list of values
    ;; that need to be reclaimed.  (ghw 10/5/98)
    ;; HQ-2173266
    (reclaim-slot-value (managed-g2-array g2-array))
    (atomic-exchange (managed-g2-array g2-array) managed-g2-array)
    (loop with element-type = (g2-list-or-array-element-type g2-array)
	  with items-present-p
	    = (g2-list-or-array-element-type-may-contain-item-p element-type)
	  with real-index		; for when items-present-p
	  with index = 0
	  while (<f index array-length)
	  do 
      (with-temporary-gensym-float-creation read-array-data
	(loop as element = (read-g2-list-or-array-element-for-kb element-type t)
	      do (cond
		   (items-present-p
		    (setq real-index (twicef index))
		    ;; HQ-2173977 -- Called for reading runtime data.
		    (setf (managed-g2-array-aref managed-g2-array real-index)
			  (if (deleted-frame-p element)
			      nil
			      element))
		    (if (framep element)	; otherwise remains nil
			(frame-serial-number-setf
			  (managed-g2-array-aref
			    managed-g2-array
			    (1+f real-index))
			  (frame-serial-number element))))
		   ((eq element-type 'float)
		    (setf (managed-float-aref managed-g2-array index)
			  (managed-float-value element))
		    (reclaim-managed-float element))
		   (t (setf (managed-g2-array-aref managed-g2-array index)
			    element)))
		 (incff index)
	      while (and (<f index array-length)
			 (not (=f (modf-positive index 500) 0))))))
    managed-g2-array))

;; This has been fixed to handle element-type = float correctly, and to reenter
;; temporary float creation context at most every 500 elements.  Fixed while
;; investigating a warmbooting bug.  Reference KB is
;; /vmsdisc/customer-kbs/exxon/cannot_reset.kb, a 3.0 snapshot which would abort
;; when warmbooted if not for the fix for element-type = float. Note that this
;; code was simpler/different in 3.0, and lacked this problem.  (MHD 8/28/94)

;; This is coded for speed over elegance.  Whenever the representations of g2
;; arrays change, this may need revision.


;(defun read-array-data (g2-array)
;  (let ((array-length (read-element-for-kb nil))
;        (managed-g2-array nil))
;    #+development
;    (when (not (=f array-length (g2-array-length g2-array)))
;      (cerror """Array-length of existing array not compatible with what was saved."))
;    (setq managed-g2-array
;          (allocate-managed-g2-array (g2-array-length g2-array)
;                                     (g2-array-element-type g2-array) nil nil))
;    (setf (managed-g2-array g2-array) managed-g2-array)
;    (with-temporary-gensym-float-creation read-array-data
;      (loop for index from 0 below array-length 
;            as value? = (extract-number-or-value (read-element-for-kb nil))
;            do
;        (g2-array-aset g2-array index value?)))
;    (setf (managed-g2-array g2-array) initialization-inhibit)
;    managed-g2-array))






;;;; G2-Array and G2-list Conversion




;;; The following operations are used to move elements between g2-lists and
;;; g2-arrays.  These functions are needed in the "quick sort"
;;; system-procedures.  This sorting mechanism first converts a g2-list to a
;;; g2-array, sorts the array, and then puts the elements back into the g2-list,
;;; in the sorted order.  The following functions make that process more
;;; efficient by not copying the elements as they are moved between the g2-list
;;; and g2-array.  Note the implementation of elements in g2-lists and g2-arrays
;;; differ.  Currently, g2-list elements contain items or evaluation-values.
;;; G2-array elements can contain item, "no item" (i.e., NIL), evaluation-
;;; values, or unmanaged values (non-evaluation-values).  Float-array is an
;;; example of an array that contains non-evaluation-values.




;;; The function `convert-g2-list-to-g2-array' is used to move the elements from
;;; a g2-list to a newly created, transient g2-array of the same element-type.
;;; Note that the elements are first removed from the g2-list and then added to
;;; the g2-array.  The elements are moved between the two and, when possible,
;;; not copied or reclaimed.  Note that on return of this function g2-list
;;; contains no elements.  The function returns the newly allocated g2-array.

;; Declare because the function is called from the sorting SYSTEM-PROCEDURES.
(declare-system-procedure-function convert-g2-list-to-g2-array t)

(defun convert-g2-list-to-g2-array (g2-list)
  (let* ((g2-list-element-type (list-type g2-list))
	 (g2-list-length (g2-list-length g2-list))
	 (new-g2-array-class
	   (g2-list-or-array-class-for-element-type g2-list-element-type t))
	 (new-g2-array (make-transient-item new-g2-array-class)))
    ;; Note that, if the array is active, changing the array-length will
    ;; cause initialization of the array elements.
    (change-slot-value new-g2-array 'g2-array-length g2-list-length)
    (move-g2-list-elements-to-g2-array g2-list new-g2-array nil)
    ;; Return the newly allocated and filled array.
    new-g2-array))



;;; The function `move-g2-list-elements-to-g2-array' is used to move the actual
;;; elements from g2-list into the g2-array at the same index location.  Note
;;; that the number of elements moved is determined by count-of-elements-to-move
;;; or the actual number of list elements, whichever is smaller.  If count-of-
;;; elements-to-move is NIL, all elements are moved. But, of course, only those
;;; elements that can fit within the current length of the g2-array are moved.

;;; Usually, when the elements are moved, no g2-list elements are reclaimed or
;;; copied.  But, in several cases, depending on whether the element is a
;;; managed value in the g2-list and not the g2-array, the value may be
;;; reclaimed.  Note that before the move is made, the g2-array can contain
;;; element values, which may be reclaimed.

;;; Note that before this function is called the g2-array should already be of
;;; the desired length.  After this function is called the g2-list may still
;;; contain elements.  But, those elements moved from the g2-list are, of
;;; course, no longer members of the list.  The resulting list length is equal
;;; to the original length less the number of elements moved.

(defun-void move-g2-list-elements-to-g2-array
    (g2-list g2-array count-of-elements-to-move?)
    (loop with g2-list-length-before-move = (g2-list-length g2-list)
	  with g2-array-length = (g2-array-length g2-array)
	  with item-or-value = nil
	  for index from 0
	  while (and (or (null count-of-elements-to-move?)
			 (<f index count-of-elements-to-move?))
		     (<f index g2-list-length-before-move)
		     (<f index g2-array-length))
	  do
      ;; Remove the element from the g2-list, without reclaiming the element
     ;; value.
      (setq item-or-value (pop-g2-list g2-list))

      ;; Add the element to the g2-array.  Reclaim the new element if it is a
      ;; managed value for the g2-list and not the g2-array.  Reclaim any old
      ;; g2-array element, when necessary.
      (mutate-g2-array g2-array index item-or-value t t))
    nil)



;;; The function `move-g2-array-elements-to-g2-list' is similar to the function
;;; move-g2-list-elements-to-g2-array, except that it moves elements in the
;;; opposite direction, from a g2-array to a g2-list.

;;; Note that the elements are added to the end of the g2-list, regardless of
;;; whether the g2-list already has any existing elements.

;;; If the g2-list does not allow duplicate elements and the new element is
;;; already in the list, then it is not added and no warning is given.

;;; Note that after the elements are copied out of the g2-array, the g2-array
;;; length is changed to 0.  Before this is done, if the array contains
;;; evaluation-values, the elements are cleared.  This is needed to prevent
;;; double reclamation because the g2-list and g2-array are temporarily sharing
;;; elements.

;; Declare because the function is called from the sorting SYSTEM-PROCEDURES.
(declare-system-procedure-function move-g2-array-elements-to-g2-list t)

(defun move-g2-array-elements-to-g2-list (g2-array g2-list)
  (let* ((truth-value-array-p (frame-of-class-p g2-array 'truth-value-array))
	 (float-value-array-p (frame-of-class-p g2-array 'float-array)))
    ;; Add the element to the end of the g2-list.  The value is converted to
    ;; an evaluation-value, when necessary.  Note that if duplicate elements are
    ;; not allowed and the element is already in the list, the insert fails,
    ;; with no warning.
    (do-g2-array-elements (value g2-array nil)
      (when value
	(g2-list-insert-at-end
	  (cond
	    ;; Truth-arrays and float-arrays contain non-evaluation-value datum.
	    (truth-value-array-p (make-evaluation-truth-value value))
	    (float-value-array-p (make-evaluation-float value))
	    (t value))
	  g2-list)))
    ;; Remove the array elements, so that the g2-array and g2-list do not share
    ;; elements.  Clear the elements of the g2-array before changing the array
    ;; length.
    (clear-managed-values-from-managed-g2-array
      (managed-g2-array g2-array) (g2-array-element-type g2-array))
    (change-slot-value g2-array 'g2-array-length 0)
    nil))






;;;; Quicksort functionality


;;; The macro `partition-1', a submacro of quicksort-1 (below), implements
;;; the partitioning operation of Quicksort. 

;;; Note that all of the arguments are evaluated, once and only once in order,
;;; except for the last, comparison-type, which is not evaluated and is
;;; examined only at macroexpansion time.  Comparison-type should be one of
;;; the symbols INTEGER, FLOAT, or QUANTITY.

;;; The first three arguments must be instances of g2-array or subclasses of
;;; g2-array.  They are not managed arrays.

;;; The first argument, key-array, is an array of the class corresponding
;;; to comparison-type as follows: INTEGER: class integer-array;
;;; FLOAT: class float-array; QUANTITY: class quantity-array.  

;;; Data-array-1 is the user's array to be sorted.

;;; Key-array is either
;;; (Case 1) an identical copy of data-array-1 or a near identical copy; or
;;; (Case 2) a quantity array whose elements are obtained by applying a
;;; key-function to the members of a g2-array or g2-list.  The originating
;;; call might be something like
;;;     g2-sort-list(g2-list, false, key-function, false, structure) .

;;; In Case 1, both key-array and data-array-1 are subclasses of
;;; quantity-array, and further are arrays of the same length and both 
;;; of the class corresponding to comparison-type as follows:
;;; INTEGER: class integer-array; FLOAT: class float-array;
;;; QUANTITY: class quantity-array.

;;; In Case 2 the only requirement is that key-array is a quantity-array
;;; of the same length as data-array-1.

;;; In Case 1, if the sort is in descending order, key-array is an identical
;;; copy of data-array-1.  If the sort is in ascending order, then it
;;; contains the negatives of the values of data-array-1.

;;; The reason for this is that sort comparisons are done only on key-array
;;; with just one comparison test.  Then the moves are performed on both
;;; key-array and data-array-1 in parallel. This way data-array-1 ends up
;;; sorted in the right direction.

;;; Data-array-2? can either be nil or be an array of any type, corresponding
;;; to the users's "aux array", an array that's changed in parallel to
;;; key-array.  It is checked in the cap to be of the same length as key-array.

;;; Left and right are fixnum indices into the arrays giving the beginning
;;; and ending partition indices, respectively.


;;; Improvements 11/26/02: The following improvements have been made 
;;; to the code:

;;; (1) Now uses median-of-3 pivoting:  The median of the first, middle,
;;; and last elements of the subarray being partitioned is used as the 
;;; pivot.  This prevents a predictable worst case running time of O(n^2),
;;; for example, when calling quicksort on an already-sorted input array.  

;;; (2) Places sentinels at each end of the subarray being partitioned.
;;; The leftmost sentinel is >= pivot, the rightmost <= pivot, 'pivot'
;;; being the partitioning pivot.  With the median-of-3 scheme, the
;;; two elements that are not the pivot are used as the sentinels.
;;; This means that we don't have to test whether a pointer has moved
;;; off the end of the array in quicksort's innermost loop.

;;; (3) Uses insertion-sort when subarrays to be sorted are small.
;;; Small here is taken by convention to be <= 7 elements in size.
;;; For such arrays insertion sort is faster than quicksort due to a much
;;; smaller constant overhead.  This also guarantees that there are at
;;; least three elements to use for median-of-3 pivot testing when doing 
;;; the partitioning for quicksort.


;;; The parameter `quicksort-verbose-p' can be set non-nil to enable printing
;;; debugging information at the beginning and end of the call to
;;; partition-1; and at the beginning of the call to insertion-sort.
;;; It is available only in development and is initially nil.

(defparameter quicksort-verbose-p nil)

(defmacro partition-1
    (key-array data-array-1 data-array-2? left right comparison-type)
  (let ((gte (case comparison-type (integer '>=f) (float '>=e) (t '>=)))
	(lte (case comparison-type (integer '<=f) (float '<=e) (t '<=)))
	(less (case comparison-type (integer '<f) (float '<e) (t '<)))
	(number-type (case comparison-type
		       (integer 'fixnum) (float 'gensym-float) (t 'number)))
	(number-init (case comparison-type (integer 0) (float 0.0) (t 0))))
    (avoiding-variable-capture
	(key-array data-array-1 data-array-2? left right)
      `(macrolet ((ref (array index)
		    ,(case comparison-type
		       (integer '`(managed-svref ,array ,index))
		       (float '`(managed-float-aref ,array ,index))
		       (t
			'`(let ((value (managed-svref ,array ,index)))
			    (if (managed-float-p value) (managed-float-value value) value)))))
		  (set-ref (array index value)
		    ,(case comparison-type
		       ((integer float) '`(setf (ref ,array ,index) ,value))
		       (t
			'`(let* ((array ,array) (index ,index) (value ,value)
				 (old-value (managed-svref array index)))
			    (declare (type fixnum index))
			    (if (managed-float-p old-value)
				(if (gensym-float-p value)
				    (mutate-managed-float-value old-value value)
				    (prog1 (setf (managed-svref array index) value)
				      (reclaim-managed-float old-value)))
				(setf (managed-svref array index)
				      (if (gensym-float-p value)
					  (allocate-managed-float value)
					  value)))))))
		  (ref-b (index)
		    `(g2-array-aref-item-or-evaluation-value b ,index))
		  (aux-ref (index)	; probably not worth optimizing aux array access
		    `(g2-array-aref-item-or-evaluation-value data-array-2? ,index))
		  (set-ref-b (index value)
		    `(mutate-g2-array-reclaiming-evaluation-values b ,index ,value))
		  (set-aux-ref (index value)
		    `(mutate-g2-array-reclaiming-evaluation-values data-array-2? ,index ,value))
		  (switch (index-1 index-2)
		    `(progn
		       (let ((temp (ref a ,index-1)))
			 (set-ref a ,index-1 (ref a ,index-2))
			 (set-ref a ,index-2 temp)
			 (setq temp (ref-b ,index-1))
			 (set-ref-b ,index-1 (ref-b ,index-2))
			 (set-ref-b ,index-2 temp))
		       (when data-array-2?
			 (let ((temp (aux-ref ,index-1)))
			   (set-aux-ref ,index-1 (aux-ref ,index-2))
			   (set-aux-ref ,index-2 temp)))))
		  (consing-numbers (&body body)
		    ,(case comparison-type
		       (integer '`(progn . ,body))
		       (t '`(with-temporary-gensym-float-creation partition-1 . ,body))))
		  (trace-at-start ()
		    #+development
		    `(trace-at-start-of-partition-1
		       key-array data-array-1 data-array-2? left right))
		  (trace-at-end ()
		    #+development
		    `(trace-at-end-of-partition-1
		       key-array left right-index)))
	 (consing-numbers		; see note (MHD 8/14/02)
	   (let* ((key-array ,key-array)
		  (data-array-1 ,data-array-1)
		  (a (managed-g2-array ,key-array))
		  (b ,data-array-1)
		  (data-array-2? ,data-array-2?)
		  (left ,left)
		  (right ,right)
		  (k 0)
		  (pivot ,number-init)
		  pivot-b 
		  pivot-b-2? 
		  (left-index (1+f left))
		  (right-index right))
	     (declare (type fixnum left right k left-index right-index)
		      (type ,number-type pivot))
	     (trace-at-start)
	     ;; Choose median of left, center, and right elements 
	     ;; as partitioning element.  Also rearrange so that
	     ;; (ref a left) >= (ref a (1+f left)) >= (ref a right) .
	     (setq k (floorf (+f left right) 2))
	     (switch k left-index)
	     (when (,less (ref a left) (ref a right))
	       (switch left right))
	     (when (,less (ref a left-index) (ref a right))
	       (switch left-index right))
	     (when (,less (ref a left) (ref a left-index))
	       (switch left-index left))
	     (setq pivot (ref a left-index)
		   pivot-b (ref-b left-index)
		   pivot-b-2? (when data-array-2?
				(aux-ref left-index)))

	     ;; The beginning of the innermost loop.

	     (loop do

	       ;; Scan up to find an element <= pivot.
	       (setq left-index 
		     (loop for i fixnum from (1+f left-index)
			   do (if (,lte (ref a i) pivot) (return i))))

	       ;; Scan down to find an element >= pivot.
	       (setq right-index
		     (loop for i fixnum downfrom (1-f right-index)
			   do (if (,gte (ref a i) pivot) (return i))))

	       ;; If the pointers crossed, exit with the
	       ;; partitioning complete.
	       (if (<f right-index left-index) (return))

	       ;; Otherwise, exchange elements.
	       (switch left-index right-index))

	     ;; The end of the innermost loop.

	     ;; Insert the partitioning element.
	     (set-ref a (1+f left) (ref a right-index))
	     (set-ref-b (1+f left) (ref-b right-index))
	     (when data-array-2?
	       (set-aux-ref (1+f left) (aux-ref right-index)))
	     (set-ref a right-index pivot)
	     (set-ref-b right-index pivot-b)
	     (when data-array-2?
	       (set-aux-ref right-index pivot-b-2?))

	     (trace-at-end)
	     right-index))))))

;; Note: the consing-numbers macrolet macro is just used above around the outer
;; loop.  It is a noop when we have an integer array. For float or quantity
;; arrays, it seems it should even be used in a more constrained fashion, i.e.,
;; around each inner loop, and even then with subloops that cannot exceed
;; certain limit on the number of operations that could cons floats.  In
;; practice, the code seems to have relied for quite some time on the fact that
;; in practice there is no practical limit to the temporary area size (for
;; Chestnut) and that this is always called within stack-eval-1, which wraps
;; with-temporary-gensym-float-creation around the call. I think it's still wise
;; to have this here even if it only reduces the possibility of overflow
;; problems, if only as a placeholder. (MHD 8/14/02)


#+development
(defun trace-at-start-of-partition-1
    (key-array data-array-1 data-array-2? left right)
  (when quicksort-verbose-p
    (format t "~% key ~a data1 ~a data2 ~a~% Partition with left right ~a, ~a"
	    key-array data-array-1 data-array-2? left right)))

#+development
(defun trace-at-end-of-partition-1 (key-array left right-index)
  (when quicksort-verbose-p
    (format t "~% Crossed at ~a" right-index)
    (loop with array = (managed-g2-array key-array)
	  with float-p = (frame-of-class-p key-array 'float-array)
	  for i from left below (managed-array-length array)
	  as elt = (if float-p
		       (managed-float-aref array i)
		       (managed-svref array i))
	  as value = (if (managed-float-p elt) (managed-float-value elt) elt)
	  do (format t (if float-p "~% ~d: ~6,4F" "~% ~d: ~a") i value))))

#+development
(defun trace-at-start-of-insertion-sort
    (key-array data-array-1 data-array-2? left right)
  (when quicksort-verbose-p
    (format t "~% key ~a data1 ~a data2 ~a~% Insertion sort with left right ~a, ~a"
	    key-array data-array-1 data-array-2? left right)))

;;; The parameter `insertion-sort-array-size' is the size of the subarrays 
;;; to be sorted by straight insertion.

(defparameter insertion-sort-array-size 7)

;;; The macro `insertion-sort', a submacro of quicksort-1 (below),
;;; implements the insertion-sort operation of Quicksort. 

(defmacro insertion-sort 
    (key-array data-array-1 data-array-2? left right comparison-type)
  (let ((gte (case comparison-type (integer '>=f) (float '>=e) (t '>=)))
	(number-type (case comparison-type
		       (integer 'fixnum) (float 'gensym-float) (t 'number))))
    (avoiding-variable-capture
	(key-array data-array-1 data-array-2? left right)
      `(macrolet ((ref (array index)
		    ,(case comparison-type
		       (integer '`(managed-svref ,array ,index))
		       (float '`(managed-float-aref ,array ,index))
		       (t
			'`(let ((value (managed-svref ,array ,index)))
			    (if (managed-float-p value) (managed-float-value value) value)))))
		  (set-ref (array index value)
		    ,(case comparison-type
		       ((integer float) '`(setf (ref ,array ,index) ,value))
		       (t
			'`(let* ((array ,array) (index ,index) (value ,value)
				 (old-value (managed-svref array index)))
			    (declare (type fixnum index))
			    (if (managed-float-p old-value)
				(if (gensym-float-p value)
				    (mutate-managed-float-value old-value value)
				    (prog1 (setf (managed-svref array index) value)
				      (reclaim-managed-float old-value)))
				(setf (managed-svref array index)
				      (if (gensym-float-p value)
					  (allocate-managed-float value)
					  value)))))))
		  (ref-b (index)
		    `(g2-array-aref-item-or-evaluation-value b ,index))
		  (aux-ref (index)	; probably not worth optimizing aux array access
		    `(g2-array-aref-item-or-evaluation-value data-array-2? ,index))
		  (set-ref-b (index value)
		    `(mutate-g2-array-reclaiming-evaluation-values b ,index ,value))
		  (set-aux-ref (index value)
		    `(mutate-g2-array-reclaiming-evaluation-values data-array-2? ,index ,value))
		  (consing-numbers (&body body)
		    ,(case comparison-type
		       (integer '`(progn . ,body))
		       (t '`(with-temporary-gensym-float-creation insertion-sort . ,body))))
		  (trace-at-start ()
		    #+development
		    `(trace-at-start-of-insertion-sort 
		       key-array data-array-1 data-array-2? left right)))
	 (consing-numbers		; see note (MHD 8/14/02)
	   ;; If we get here we must have at least two elements to sort.
	   (let* ((key-array ,key-array)
		  (data-array-1 ,data-array-1)
		  (a (managed-g2-array ,key-array))
		  (b ,data-array-1)
		  (data-array-2? ,data-array-2?)
		  (left ,left)
		  (right ,right))
	     (declare (type fixnum left right))
	     (trace-at-start)
	     (loop for j fixnum from (1+f left) to right
		   for element-a ,number-type = (ref a j)
		   for element-b = (ref-b j)
		   for element-b-2? = (when data-array-2? (aux-ref j))
		   do (loop for i fixnum from (1-f j) downto left
			    do 
			(when (,gte (ref a i) element-a)
			  (set-ref a (1+f i) element-a)
			  (set-ref-b (1+f i) element-b)
			  (when data-array-2?
			    (set-aux-ref (1+f i) element-b-2?))
			  (return))
			(set-ref a (1+f i) (ref a i))
			(set-ref-b (1+f i) (ref-b i))
			(when data-array-2?
			  (set-aux-ref (1+f i) (aux-ref i)))
			finally 
			  (set-ref a left element-a)
			  (set-ref-b left element-b)
			  (when data-array-2?
			    (set-aux-ref left element-b-2?))))))))))

(defun integer-insertion-sort (key-array data-array-1 data-array-2? left right)
  (declare (type fixnum left right))
  (insertion-sort key-array data-array-1 data-array-2? left right integer))

(defun float-insertion-sort (key-array data-array-1 data-array-2? left right)
  (declare (type fixnum left right))
  (insertion-sort key-array data-array-1 data-array-2? left right float))

(defun quantity-insertion-sort (key-array data-array-1 data-array-2? left right)
  (declare (type fixnum left right))
  (insertion-sort key-array data-array-1 data-array-2? left right quantity))

;;; Insertion-sort-per-array-type dispatches to the most optimized
;;; insertion-sort function.

(defun insertion-sort-per-array-type
    (key-array data-array-1 data-array-2? left right array-type)
  (declare (type fixnum left right))
  (case array-type		; either integer, float or quantity
    (integer (integer-insertion-sort key-array data-array-1 data-array-2? left right))
    (float (float-insertion-sort key-array data-array-1 data-array-2? left right))
    (t (quantity-insertion-sort key-array data-array-1 data-array-2? left right))))


(defun integer-partition (key-array data-array-1 data-array-2? left right)
  (declare (type fixnum left right))
  (partition-1 key-array data-array-1 data-array-2? left right integer))

(defun float-partition (key-array data-array-1 data-array-2? left right)
  (declare (type fixnum left right))
  (partition-1 key-array data-array-1 data-array-2? left right float))

(defun quantity-partition (key-array data-array-1 data-array-2? left right)
  (declare (type fixnum left right))
  (partition-1 key-array data-array-1 data-array-2? left right quantity))


;;; Partition-per-array-type dispatches to the most optimized partition
;;; function.

(defun partition-per-array-type
    (key-array data-array-1 data-array-2? left right array-type)
  (declare (type fixnum left right))
  (case array-type		; either integer, float or quantity
    (integer (integer-partition key-array data-array-1 data-array-2? left right))
    (float (float-partition key-array data-array-1 data-array-2? left right))
    (t (quantity-partition key-array data-array-1 data-array-2? left right))))


;;; `quicksort-1' is an adaption of the quicksort procedure on page 110 of
;;; Algorithms by Robert Sedgewick Addison-Wesley August 1984 edition

(declare-system-procedure-function quicksort-1 nil)

(defun-funcallable quicksort-1
    (g2-key-value-array g2-key-array g2-aux-array
			left-stack-list right-stack-list state-list)
  ;; Sorts g2-key-value-array into descending numerical order.  This array
  ;; and accompanying arrays are replaced by their sorted rearrangements.
  (let* (current-left
	  current-right
	  stack-depth
	  (key-array g2-key-array)
	  (key-value-array g2-key-value-array)
	  (aux-array? nil)
	  (array-type (g2-array-element-type g2-key-value-array))
	  (stack-depth-source nil)
	  (current-right-source nil)
	  (current-left-source nil)
	  (time-of-start (get-fixnum-time)))
    (when (and (framep g2-aux-array) (g2-array-p g2-aux-array))
      (setq aux-array? g2-aux-array))
    (cond ((=f (g2-list-length left-stack-list) 0)
	   ;; We're just starting out.
	   (when (not (eq array-type 'integer))
	     (do-g2-array-elements (element g2-key-value-array nil)
	       (if (nanp (if (managed-float-p element)
			     (managed-float-value element)
			     element))
		   (stack-error
		     cached-top-of-stack
		     "Sorting a list or array containing NaNs with no ~
                      comparison function is undefined."))))
	   (setq current-left 0)
	   (setq current-right (-f (g2-array-length key-array) 1))
	   (insert-fixnum-at-beginning-of-g2-list left-stack-list current-left)
	   (insert-fixnum-at-beginning-of-g2-list right-stack-list current-right)
	   (setq stack-depth 1))
	  (t
	   (setq stack-depth-source (pop-g2-list state-list))
	   (setq stack-depth (evaluation-value-value stack-depth-source))
	   (setq current-left-source (pop-g2-list state-list))
	   (setq current-left (evaluation-value-value current-left-source))
	   (setq current-right-source (pop-g2-list state-list))
	   (setq current-right (evaluation-value-value current-right-source))))
    ;; Save runtime data if necessary for this array, since we bypass this
    ;; step in partition-1 as an optimization:
    (note-change-to-runtime-data-for-block key-value-array)
    ;; Check if we are all done.
    (loop with quit? = nil
	  until (or (=f stack-depth 0) quit?)
	  with partition-point
	  do
      (when (and (>f current-right current-left)
		 (<f (-f current-right current-left)
		     insertion-sort-array-size))
	;; Use insertion sort when the subarray is small enough.
	(insertion-sort-per-array-type 
	  key-value-array key-array aux-array?
	  current-left current-right array-type)
	(setq current-right current-left))
      (cond
	((>f current-right current-left)
	 (setq partition-point
	       (partition-per-array-type
		 key-value-array key-array aux-array?
		 current-left current-right array-type))
	 ;; Push pointers to the larger subarray onto the stack.
	 ;; Process the smaller subarray immediately.
	 (cond
	   ((>f (-f partition-point current-left)
		(-f current-right partition-point))
	    (insert-fixnum-at-beginning-of-g2-list left-stack-list current-left)
	    (insert-fixnum-at-beginning-of-g2-list
	      right-stack-list (-f partition-point 1))
	    (setq current-left (+f partition-point 1)))
	   (t
	    (insert-fixnum-at-beginning-of-g2-list
	      left-stack-list (+f partition-point 1))
	    (insert-fixnum-at-beginning-of-g2-list right-stack-list current-right)
	    (setq current-right (-f partition-point 1))))
	 (incff stack-depth))
	(t
	 ;; Pop the stack and begin a new round of partitioning.
	 (decff stack-depth)
	 (when current-right-source
	   (reclaim-evaluation-value current-right-source))
	 (when current-left-source
	   (reclaim-evaluation-value current-left-source))
	 (setq current-right-source (pop-g2-list right-stack-list))
	 (setq current-right (evaluation-value-value current-right-source))
	 (setq current-left-source (pop-g2-list left-stack-list))
	 (setq current-left (evaluation-value-value current-left-source))))      
      (when (>f (-f (get-fixnum-time) time-of-start) maximum-time-slice-size)
	(setq quit? t)))

    ;; Set up state so it can be passed back in as required.
    (insert-fixnum-at-beginning-of-g2-list state-list current-right)
    (insert-fixnum-at-beginning-of-g2-list state-list current-left)
    (insert-fixnum-at-beginning-of-g2-list state-list stack-depth)
    (when current-right-source
      (reclaim-evaluation-value current-right-source))
    (when current-left-source
      (reclaim-evaluation-value current-left-source))
    (when stack-depth-source
      (reclaim-evaluation-value stack-depth-source))
    (values left-stack-list right-stack-list state-list)))

;; Consider using (time-slice-expired-p) as an alternative to our version above.
;; However, that might introduce a significant performance difference and make
;; the sort seem to be starved for cycles in comparison with its current
;; behavior.  Code to use it had been in place adjacent to the current
;; time-slice code above, but commented out with no explanation. (MHD 8/14/02)



;;;; G2-Array System Procedures 



;;; The `g2-copy-array-elements-to-initial-values system-procedure' is used to
;;; make the current g2-array element values the initial-values of the array.
;;; In this way, the current array elements will survive a reset of G2.

;;; Note, this is a permanent change and not a kb-state-change.

;;; If the array-length was modified as a kb-state-change (e.g., resulting from a
;;; "change the array-length ..." action) and the elements can be successfully
;;; copied to the initial-values attribute, then the array-length is also made
;;; permanent.  It is not undone on reset of G2.

;;; Note that if the current values cannot be copied into the initial-values
;;; then this system-procedure signals a stack-error, aborting this procedure
;;; invocation.  The copy of the current values could fail for g2-arrays (arrays
;;; with element type item-or-value) and item-arrays (arrays with an element
;;; type of item or a subclass of item).

;;; It can fail in these cases if a current element of the item-array or
;;; g2-array cannot be represented as a unique item-or-value reference.
;;; This failure cases occur when the item contains:
;;; 1. no value
;;; 2. an item than cannot be represented in the grammar of the initial-values
;;; slot, which is constant-designation.  This grammar category refers to those
;;; items that can be described in relation to a named item.  This includes
;;;  - <item-name>
;;;  - the <attribute> of constant-designation
;;;  Exceptions that will, even though they are constant-designations are:
;;;  - the workspace {or subworkspace} of a constant-designation
;;;  - the <class> connected {in some way} to a constant-designation
;;;  In these cases, there is not a unique mapping from the frame back to the
;;;  original designation.  Therefore, if the item is not named or is not an
;;;  attribute of a named item, this will cause a failure.

(declare-system-procedure-function g2-copy-array-elements-to-initial-values t)

(defun-funcallable g2-copy-array-elements-to-initial-values (g2-array)
  (when (eql (g2-array-length g2-array) 0)
    ;; No change to the initial-values, if there are no elements.
    ;; GENSYMCID-1489: Bug: g2-array-copy-elements-to-initial-values doesn't
    ;;                 work for empty arrays
    (change-slot-value
      g2-array 'g2-array-initial-values nil)
    (return-from g2-copy-array-elements-to-initial-values))
  (let ((new-initial-values-list nil)
	(all-equal-p t)
	(permanent-array-p nil)
	(element-copy-no-value-error? nil)
	(element-copy-error-in-frame? nil))
    ;; For all arrays, copy the element values in the correct slot-value-list
    ;; format (i.e., the format that results from a parse and slot-value
    ;; compilation).  The copied elements end up as slot-values, not
    ;; evaluation-values.  (There may be differences between these two, in some
    ;; cases.)
    (cond
      ((and (array-is-permanent g2-array) (managed-g2-array g2-array))
       (setq permanent-array-p t))
      (t
       (let* ((tail? nil)
	      (previous-element? nil)
	      (element-type (g2-array-element-type g2-array))
	      (items-possible-p
		(g2-list-or-array-element-type-may-contain-item-p
		  element-type))
	      ;; For g2-array (not a value-array) or item-array, try to create
	      ;; constant-designations:
	      (all-previous-elements-contain-no-value? items-possible-p))
	 (do-g2-array-elements (element g2-array nil)
	   (enqueue-1
	     (case element-type
	       (float (make-slot-value-float-macro element))
	       ((integer truth-value) (copy-evaluation-integer element))
	       (quantity (copy-evaluation-quantity element))
	       (symbol (copy-evaluation-symbol element))
	       (text (copy-evaluation-text element))
	       (t
		;; This clause is for handling the rest of the cases, which
		;; include at least cases that correspond to the classes
		;; g2-array, item-array, and value-array.
		(cond
		  ((and items-possible-p (null element))
		   (unless all-previous-elements-contain-no-value?
		     ;; Cannot copy to initial values when only some of
		     ;; the elements have no value.
		     (setq element-copy-no-value-error? t))
		   nil)
		  (t
		   (when items-possible-p
		     ;; Used to distinguish between all elements having no value
		     ;; and only some elements having no value.
		     (setq all-previous-elements-contain-no-value? nil))
		   (cond
		     ((and items-possible-p (framep element))
		      (let ((designation? (generate-designation-for-block element)))
			(cond
			  (designation?
			   (prog1 (copy-tree-using-slot-value-conses designation?)
			     (reclaim-eval-tree designation?)))
			  (t
			   (setq element-copy-error-in-frame? element)
			   nil))))
		     ((and items-possible-p (evaluation-symbol-p element))
		      ;; Convert symbols to a form that distinguishes them
		      ;; from item designations.
		      (make-initial-value-symbol element))
		     ((evaluation-truth-value-p element)
		      (make-slot-constant
			(evaluation-truth-value-value element)
			'truth-value nil))
		     (t
		      ;; fall through for non-special item-or-value arrays, and for
		      ;; general element types, and any types not handled above:
		      (copy-evaluation-value element)))))))
	     new-initial-values-list tail? slot-value-cons-macro)
	   (when (and all-equal-p
		      ;; "No value" case is not handled here.  See null
		      ;; element case above.
		      element)
	     (when previous-element?
	       (setq all-equal-p
		     (if (eq element-type 'float)
			 (=e element previous-element?)
			 (item-or-value-eql element previous-element?))))
	     (setq previous-element? element)))
	 (when all-previous-elements-contain-no-value?
	   (reclaim-slot-value new-initial-values-list)
	   (setq new-initial-values-list nil)))))
    
    (cond
      ((or element-copy-no-value-error? element-copy-error-in-frame?)
       (reclaim-slot-value new-initial-values-list)
       (setq new-initial-values-list nil)
       ;; Signal a G2 procedure error.  The initial-values list could not be
       ;; created.
       (write-stack-error
	   cached-top-of-stack
	 (tformat
	   "Cannot copy the array elements of ~NF into its initial-values attribute."
	   g2-array)
	 (cond
	   (permanent-array-p
	    ;; this case may be unreachable! was this ever reachable? (MHD 11/8/01)
	    (tformat " A permanent array cannot be initialized."))
	   (element-copy-no-value-error?
	    (tformat "  An array element has no value."))
	   ((and element-copy-error-in-frame?
		 (framep element-copy-error-in-frame?))
	    (tformat
	      "  An array element, ~NF, cannot be an initial value.  It must either ~
                 have a name or be an attribute of a named item."
	      element-copy-error-in-frame?)))))
      (t
       (when (and new-initial-values-list all-equal-p)
	 ;; Only need the first element.  They are all equal.
	 (reclaim-slot-value (cdr new-initial-values-list))
	 (setf (cdr new-initial-values-list) nil))
       ;; Note runtime KB change, in case a save is occurring at the same time.
       (note-change-to-runtime-data-for-block g2-array)
       ;; Note that change-slot-value updates any displays of the slot and also
       ;; reclaims any old slot-value as needed.
       (change-slot-value
	 g2-array 'g2-array-initial-values new-initial-values-list)
       ;; In case, the user did a "change the array-length ...".  Don't want the
       ;; length reverting back to its original value because the length and
       ;; initial-values may then not match.
       (remove-kb-state-variable-record g2-array 'g2-array-length))))
  nil)

;; Note that this system-procedure works by copying the array elements into the
;; expected slot-value-list format (i.e., the format that results from a parse
;; and slot-value compiler).  Other alternative designs are:

;; 1. Create a text string, containing the current elements, in a format based
;; on the expected grammar for that type of list.  Then, use this string to
;; parse the value, like the change text action, as if the value was edited by
;; the user.  (This would need to be a permanent change, not a kb-state change.)
;; This could be an easy implementation, as long as we get the different
;; grammars right, but seemed wasteful to allocate a string, especially for
;; large arrays.
;;  2. Create the resulting parse and pass it through the slot-value-compiler.
;; This did not seem like an easy approach.





;; Two system procedures below to determine the location in a list
;; or array of a given element (item-or-value);
;; Private to Application Technology (vkp 12/29/95)

(defun item-or-value-eql-p (element1 element2)
    (if (framep element1)
	 (and (framep element2) (eq element1 element2))
	 (and (not (framep element2)) (evaluation-value-eql element1 element2))))

(defun-for-system-procedure g2-get-position-in-list-of-element (element g2-list)
  (let ((index 
	  (loop for item-or-value being each g2-list-element in g2-list
		as ii = 0 then (+f ii 1)
		do
	    (when (item-or-value-eql-p item-or-value element)
	      (return ii)))))
    (reclaim-if-evaluation-value element)
    (make-evaluation-integer (if index index -1))))

(defun-for-system-procedure g2-get-position-in-array-of-element (element g2-array)
  (let ((index 0)
	(value-to-match element)
	(unmanaged-float-p nil))
    ; handle the special case of a float and truth-value array.
    ; this code always runs within the scope of stack-eval-1 which is
    ; protected by a with-temporary-gensym-float-creation.
    (when (frame-of-class-p g2-array 'float-array)
      (setf value-to-match (if (managed-float-p element)
                             (managed-float-value element)
                             element)
            unmanaged-float-p t))
    (when (frame-of-class-p g2-array 'truth-value-array)
      (setf value-to-match (if (evaluation-truth-value-p element)
                             (evaluation-truth-value-value element)))
                             element)
    ; return index if any match exists
    (prog1
      (cond
	(unmanaged-float-p
	 (make-evaluation-integer
	   (do-g2-array-elements (item-or-value? g2-array -1)
	     (when (eql item-or-value? value-to-match)
	       (return index))
	     (incff index))))
	((framep value-to-match)
	 (make-evaluation-integer
	   (do-g2-array-elements (item-or-value? g2-array -1)
	     (when (eq item-or-value? value-to-match)
	      (return index))
	     (incff index))))
	(t
	 (make-evaluation-integer
	   (do-g2-array-elements (item-or-value? g2-array -1)
	     (when (and (not (framep item-or-value?))
			(evaluation-value-eql item-or-value? value-to-match))
	       (return index))
	     (incff index)))))
      (reclaim-if-evaluation-value element))))
  





;;;; System Procedures for NOL (approved for 4.1 Rev. 0)




;;;  These are private system procedures for NeuronLine. They implement the evaluator
;;;  for a back-propagation and a radial-basis-function network directly. These
;;;  procedures do no checking of arguments (for example check matrices for
;;;  compatibility before multiplication). They must be passed a valid neural
;;;  network object (class bpn or rbfn), with the internal matrices of proper length.
;;;  The input vector (x) must also be of the right dimension. The output vector (y)
;;;  is modified to contain the result. -- vkp (10/12/96)

(defmacro managed-item-aref (managed-item-array index)
  `(managed-svref ,managed-item-array (*f ,index 2)))



(defun-simple sigmoidal-transfer-function (x)
  (cond ((<e x -40.0d0) -1.0d0)
	((<e 40.0d0 x) 1.0d0)
	(t
	 (-e (/e 2.0d0 (+e 1.0d0 (expe (-e x)))) 1.0d0))))
	 


(defun-for-system-procedure g2-evaluate-bpn (bpn x y)
  (let* ((transfer-function-code-array (get-slot-value bpn 'transfer-fns))
	 (managed-transfer-function-code-array (managed-g2-array transfer-function-code-array))
	 (layer-size-array (get-slot-value bpn 'layer-sizes))
	 (managed-layer-size-array (managed-g2-array layer-size-array))
	 (weights-array (get-slot-value bpn 'weight-array))
	 (managed-weights-array (managed-g2-array weights-array))
	 (number-of-layers (g2-array-length layer-size-array))
	 (managed-x (managed-g2-array x))
	 (length-x (g2-array-length x))
	 (max-nodes-in-layer
	   (+f 1 (loop for i from 0 below number-of-layers
		       maximize (managed-svref managed-layer-size-array i))))
	 (temp1 (allocate-managed-float-array max-nodes-in-layer))
	 (temp2 (allocate-managed-float-array max-nodes-in-layer))
	 managed-y)
    
    (with-temporary-gensym-float-creation g2-evaluate-bpn-optimized
      (cond ((=f (managed-svref managed-transfer-function-code-array 0) 1)
	     (loop for i from 0 below (g2-array-length x)
		   do
	       (mutate-managed-float-array temp2 i
					   (sigmoidal-transfer-function
					     (managed-float-aref managed-x i)))))
	    (t
	     (copy-managed-float-array-portion managed-x 0 length-x temp2 0)))
      (change-slot-value y 'g2-array-length
			 (managed-svref managed-layer-size-array (-f number-of-layers 1)))
      (setf managed-y (managed-g2-array y))
      
      (loop for i from 1 below number-of-layers
	    with input-vector = temp2
	    with output-vector = temp1
	    as number-from = (managed-svref managed-layer-size-array (-f i 1))
	    as number-to = (managed-svref managed-layer-size-array i)
	    as weights-matrix = (managed-item-aref managed-weights-array (-f i 1))
	    as current-layer-transfer-function-code = (managed-svref
							managed-transfer-function-code-array i)
	    do
	;; GENSYMCID-1853: "ntnol.exe has stopped working" error
	(unless weights-matrix 
	  (stack-error cached-top-of-stack "Invalid BPN, missing weights matrix at index ~a" (-f i 1))
	  (return))
	(mutate-managed-float-array input-vector number-from 1.0d0)
	(fill-managed-float-array output-vector 0.0d0)
	(loop for k from 0 to number-from
	      with managed-weights-matrix = (managed-g2-array weights-matrix)
	      as weights-row =  (managed-g2-array (managed-item-aref managed-weights-matrix k))
	      as input-vector-element = (managed-float-aref input-vector k)
	      do
	  (loop for j from 0 to (-f number-to 1)
		do
	    (mutate-managed-float-array output-vector j
					(+e (managed-float-aref output-vector j)
					    (*e (managed-float-aref weights-row j)
						input-vector-element))))
	      finally
		(when (=f current-layer-transfer-function-code 1)
		  (loop for j from 0 to (-f number-to 1)
			do
		    (mutate-managed-float-array output-vector j
						(sigmoidal-transfer-function
						  (managed-float-aref output-vector j))))))
	(setf input-vector output-vector
	      output-vector (if (=f i (-f number-of-layers 2))
				managed-y
				(if (eq output-vector temp1) temp2 temp1)))))
      
    (reclaim-managed-float-array temp1)
    (reclaim-managed-float-array temp2)))



(defun-for-system-procedure g2-evaluate-rbfn (rbfn x y)
  (let* ((weights (get-slot-value rbfn 'weights))
	 (centers (get-slot-value rbfn 'centers))
	 (shapes (get-slot-value rbfn 'shapes))
	 (managed-shapes (managed-g2-array shapes))
	 (managed-centers (managed-g2-array centers))
	 (managed-weights (managed-g2-array weights))
	 (h (g2-array-length centers))
	 (n-out (g2-array-length weights))
	 (n-in (g2-array-length x))
	 (hx (g2-array-length shapes))
	 (hp (g2-array-length (managed-item-aref managed-weights 0)))
	 (managed-diff (allocate-managed-float-array n-in))
	 (managed-ah (allocate-managed-float-array hp))
	 (maximum-activation (allocate-managed-float 0.0d0))
	 (current-activation (allocate-managed-float 0.0d0))
	 (managed-x (managed-g2-array x))
	 (managed-y (managed-g2-array y)))


    (cond ((=f hx h)
	   (loop for i from 0 below h
		 with managed-difference = (allocate-managed-float 0.0d0)
		 as managed-array-2 = (managed-g2-array
					(managed-item-aref (managed-g2-array centers) i))
		 with sqdist = (allocate-managed-float 0.0d0)
		 as shape-factor = (managed-float-aref
				     (managed-g2-array (managed-item-aref managed-shapes i)) 0)
		 do
	     (mutate-managed-float-value sqdist 0.0d0)
	     (loop for j from 0 below n-in
		   do
	       (mutate-managed-float-value managed-difference
					   (-e (managed-float-aref managed-x j)
					       (managed-float-aref managed-array-2 j)))
	       (mutate-managed-float-value sqdist
					   (+e (managed-float-value sqdist)
					       (*e (managed-float-value managed-difference)
						   (managed-float-value managed-difference)))))
	     (mutate-managed-float-value current-activation
					 (expe (/e
						 (-e (managed-float-value sqdist))
						 (*e shape-factor shape-factor))))
	     (mutate-managed-float-array managed-ah i (managed-float-value current-activation))
	     (when (>e (managed-float-value current-activation)
		       (managed-float-value maximum-activation))
	       (mutate-managed-float-value maximum-activation
					   (managed-float-value current-activation)))
		 finally
		   (reclaim-managed-float managed-difference)
		   (reclaim-managed-float sqdist)))
	  (t
	   (loop for i from 0 below h
		 with managed-sum = (allocate-managed-float 0.0d0)
		 as managed-center-vector = (managed-g2-array
					      (managed-item-aref managed-centers i))
		 as s = (*f i n-in)
		 do
	     (loop for j from 0 below n-in
		   do
	       (mutate-managed-float-array managed-diff j
					   (-e (managed-float-aref managed-x j)
					       (managed-float-aref managed-center-vector j))))
	     (mutate-managed-float-value managed-sum 0.0d0)
	     (loop for j from 0 below n-in
		   with f = (allocate-managed-float 0.0d0)
		   as shape-vector = (managed-item-aref managed-shapes (+f s j))
		   as managed-shape-vector = (managed-g2-array shape-vector)
		   do
	       (mutate-managed-float-value f 0.0d0)
	       (loop for k from 0 below n-in
		     do
		 (mutate-managed-float-value f (+e (managed-float-value f)
						   (*e (managed-float-aref managed-shape-vector k)
						       (managed-float-aref managed-diff k)))))
	       (mutate-managed-float-value
		 managed-sum
		 (+e (managed-float-value managed-sum)
		     (*e (managed-float-value f) (managed-float-aref managed-diff j))))
		   finally (reclaim-managed-float f))
	     (mutate-managed-float-value current-activation
					 (expe (-e (managed-float-value managed-sum))))
	     (mutate-managed-float-array managed-ah i (managed-float-value current-activation))
	     (when (>e (managed-float-value current-activation)
		       (managed-float-value maximum-activation))
	       (mutate-managed-float-value maximum-activation
					   (managed-float-value current-activation)))
		 finally
		   (reclaim-managed-float managed-sum))))

    (when (=f hp (+f h 1))
      (mutate-managed-float-array managed-ah h 1.0d0))

    (change-slot-value y 'g2-array-length n-out)

    (loop for i from 0 below n-out
	  with managed-sum = (allocate-managed-float 0.0d0)
	  as weight-vector = (managed-item-aref managed-weights i)
	  as managed-weight-vector = (managed-g2-array weight-vector)
	  do
      (mutate-managed-float-value managed-sum 0.0d0)
      (loop for j from 0 below hp
	    do
	(mutate-managed-float-value managed-sum
				    (+e (managed-float-value managed-sum)
					(*e (managed-float-aref managed-weight-vector j)
					    (managed-float-aref managed-ah j)))))
      (mutate-managed-float-array managed-y i (managed-float-value managed-sum))
	  finally
	    (reclaim-managed-float managed-sum))

    (reclaim-managed-float-array managed-diff)
    (reclaim-managed-float-array managed-ah)
    (reclaim-managed-float current-activation)
    maximum-activation))




;;; `g2-g2-create-by-cloning-no-restrictions' returns a cloned item without enforcing
;;; any proprietary restrictions on the operation.  This allows us to create
;;; system procedures which can clone proprietary items (for example g2-sort).

(defun-for-system-procedure g2-create-by-cloning-no-restrictions
    (symbol item-to-clone)
  (let* ((class-evaluation-symbol symbol)
	 (class (evaluation-symbol-symbol class-evaluation-symbol))
	 (class-description? (class-description class))
	 (newly-cloned-item? nil))
      (cond
	((null class-description?)
	 (stack-error cached-top-of-stack "~a is not a defined class." class))
	((not (class-can-be-transient-p class-description?))
	 (if (subclassp class 'item)
	     (write-stack-error
	       cached-top-of-stack
	       "Attempted to create an instance of ~a, but this class ~
                is not allowed to be created transiently."
	       class)
	     (write-stack-error cached-top-of-stack "~a is not a defined class." class)))
	((not (class-can-be-transient-p
		(class-description-slot item-to-clone)))
	 (write-stack-error
	   cached-top-of-stack
	   "Attempted to create an instance of ~a, but this class ~
            is not allowed to be created transiently."
	   (class item-to-clone)))
	((or (subclassp class 'connection)
	     (of-class-p item-to-clone 'connection))
	 (write-stack-error
	   cached-top-of-stack
	   "When creating transient instances of a subclass ~
            of connection, you must not clone it and must use the additional ~
            CONNECTED grammar to initially connect it to something."
	   class))
	(t
	 ;; Clone a new item and mark the item and all inferior objects and
	 ;; subworkspaces transient.
	 (setq newly-cloned-item? (clone-frame item-to-clone))
	 (cond (newly-cloned-item?
		(set-transient-and-propagate newly-cloned-item? nil)
		(funcall-method
		  'activate-if-possible-and-propagate newly-cloned-item?))
		(t
		(write-stack-error
		  cached-top-of-stack
		  "Error in CREATE BY CLONING of ~NF." item-to-clone)))))
      (reclaim-evaluation-symbol class-evaluation-symbol)
      ;; Return the new cloned item
      newly-cloned-item?))







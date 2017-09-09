;;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module TYPES

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.


;;; The module TYPES is being introduced to be a growing repository of
;;; low-level data structures and definitions of run-time data types and values.
;;; For that reason eval conses, evaluation-values, and parts of the type
;;; specification modules live here.  This is a work in progress and the
;;; modularity that is the goal here, is not fully realized.


;;; Jim Allard (et. al.)

(declare-forward-references  ; to FRAMES2A
  (uuid-function function))

(declare-forward-references  ; to GRAMMMAR6
  (class-instantiation-warning-not-defined function)
  (class-instantiation-warning-incompatible-class function)
  (class-instantiation-warning-undefined-type-specification-class function))

(declare-forward-references		; to TABLES
  (get-or-make-up-designation-for-block function))

(declare-forward-references  ; to ARRAYS
  (item-or-value-eql-p function))

(declare-forward-references ; to SETS
  #+development
  (signal-development-bad-value-for-make-evaluation-value function)
  #+development
  (reclaim-evaluation-float-error function)
  #+development
  (reclaim-evaluation-long-error function)
  #+development
  (warn-about-unrecognized-type function)
  (truth-threshold-parameter-function function))

;;; In SEQUENCES1

(declare-forward-reference get-reference-to-item function)

#-development
(declare-forward-references 
  (warn-about-unrecognized-type function))

(declare-forward-references		; to PLACES
  (make-evaluation-place-reference-to-place function))

(declare-forward-reference		; to PROC-UTILS
  validate-item-or-evaluation-value function)

(declare-forward-references ; to FRAMES2
  (clear-all-evaluator-slot-info function)) 

(declare-forward-references		; to FRAMES4
  (leave-text-representation-as-a-single-line? variable))

(declare-forward-references		; to FRAMES5
  (get-reference-to-item-no-copy function))

(declare-forward-references
  (class-function function)
  (get-instance-with-name-if-any function)
  (get-instance-from-uuid-representation function)
  (frame-or-evaluation-value-user-attribute-value function))






;;;; G2 List Element Structure




;;; G2-lists are implemented as a frame which points to a doublely linked list
;;; of list elements.  The elements are made of g2-list-element structures, and
;;; not conses to save memory.  These structures point to the next and previous
;;; elements, the value, and the g2-list frame.  (Another important piece of
;;; information not kept on the g2-list, but kept on items, is the g2-lists that
;;; the item belong to.  The item keeps a list of the corresponding
;;; g2-list-element structures in the g2-lists.)

;;; The g2-list-element structures are doubly linked because this allows
;;; constant time functions for inserting and removing items from lists.
;;; Actually, these operations are order N, where is the number of lists that an
;;; item belongs to.  The operation is independent of the length of the list.



;;; The `g2-list-element structure' is patterned after the constant-queue
;;; structure, but also has a slot which points back to the list frame to which
;;; this structure element belongs.

;;; Note that these structures are declared explicitly to be of type vector.
;;; This eliminates the name and saves a word of memory per instance.  Note that
;;; because of this there is no predicate for this structure.

(def-structure (g2-list-element
		 (:type vector)
		 (:constructor make-g2-list-element
		  (list-next-element
		   list-previous-element
		   list-element-value
		   list-frame)))
  #+Lockfree-List
  (reserved-slot-for-chaining nil :no-accessor t)
  #+Lockfree-List ; re-use accessor of queue-element
  (reference-count-and-claim-bit 1 :no-accessor t)
  list-next-element
  list-previous-element
  list-element-value
  list-frame)

;; G2-list-structure-p is needed because the structure is of type vector and so
;; does not have a predicate defined for it.  See the structure definition.

(defconstant g2-list-structure-marker '(g2-list-structure-marker))

(def-substitution-macro g2-list-structure-p (thing)
  (and (simple-vector-p thing)
       (=f (length (the simple-vector thing))
	   #-Lockfree-List 4
	   #+Lockfree-List 6)
       (eq (list-element-value thing) g2-list-structure-marker)))

#+Lockfree-List
(defmacro safe-list-read (place)
  (let ((q (gensym)))
    `(loop for ,q = ,place do
       (unless ,q (return nil))
       (atomic-incf (reference-count-and-claim-bit ,place) 2)
       (if (eq ,q ,place)
	   (return ,q)
	 (release-list-node ,q)))))

#+Lockfree-List
(defmacro copy-list-node (node-or-place) ; COPY_NODE
  `(safe-list-read ,node-or-place))

#+Lockfree-List
(defun-simple read-list-node (reference) ; READ_NODE
  (multiple-value-bind (node mark)
      (get-atomic-reference reference)
    (unless mark
      (safe-list-read node))))

#+Lockfree-List ; READ_DEL_NODE
(defun-substitution-macro read-deleted-list-node (reference)
  (let ((node (get-atomic-reference reference)))
    (safe-list-read node)
    node))

#+Lockfree-List
(defun-simple create-list-element (thing outer-list)
  (let ((node (make-g2-list-element-macro nil nil nil outer-list)))	  ; C1
    (setq node (safe-list-read node))
    (clear-lowest-bit (reference-count-and-claim-bit node))
    (setf (list-element-value node) thing)				  ; C2
    node))								  ; C3

(defun release-list-node (node)
  (when (null node)
    (return-from release-list-node))
  #+Lockfree-List
  (when (=f 0 (decrement-and-test-and-set
		(reference-count-and-claim-bit node)))
    (return-from release-list-node))
  #+Lockfree-List
  (release-list-reference node)
  (reclaim-g2-list-element-macro node))

;;; Lockfree versions of API functions for G2-LIST:
;;; - g2-list-structure-next
;;; - g2-list-structure-previous
;;; - g2-list-structure-push-right
;;; - g2-list-structure-push-left
;;; - g2-list-structure-insert-element-before (lists.lisp)
;;; - g2-list-structure-insert-element-after (lists.lisp)
;;; - g2-list-structure-delete




;;;; G2-List Element Structure Operations




;;; These are the linked-list operations defined for g2-list-element structures
;;; and g2-list structures.  These operations are called by g2-list operations
;;; and are not the public interface.  They work on the internal structures of
;;; g2-lists.

;;; G2-list-element and g2-list structures are both the same structure, but have
;;; some different operations.

;;; The g2-list structure is the structure pointed to by the g2-list frame and
;;; which contains information for the doublely-linked list of elements.  (This
;;; may be an empty list.)  This structure points to the head and tail of the
;;; list (this points to the structure itself if the list is empty), and to a
;;; marker which indicates that this is the g2-list structure.

;;; The g2-list-element structures, if any, contain information on the elements
;;; of the list.  They are operations defined on them, which include create,
;;; enqueue, insert, delete, and some predicates.  These operations do not
;;; require the elements to be of a particular type and the do not update the
;;; record of g2-lists that an item belongs to (this is done in g2-list
;;; operations).

#+Lockfree-List
(defconstant g2-list-structure-head-marker '(g2-list-structure-head-marker))
#+Lockfree-List
(defconstant g2-list-structure-tail-marker '(g2-list-structure-tail-marker))

(defmacro list-next-element-real (list-element)
  `(atomic-reference-object
     (list-next-element ,list-element)))

(defmacro list-previous-element-real (list-element)
  `(atomic-reference-object
     (list-previous-element ,list-element)))

#+Lockfree-List
(defun release-list-reference (node)
  (release-list-node (list-previous-element-real node))		  ; RR1
  (release-list-node (list-next-element-real node)))		  ; RR2

(defmacro g2-list-structure-head (g2-list-structure)
  `(list-next-element ,g2-list-structure))

(defmacro g2-list-structure-tail (g2-list-structure)
  `(list-previous-element ,g2-list-structure))

(def-substitution-macro g2-list-structure-head-if (g2-list-structure)
  (when g2-list-structure
    (g2-list-structure-head g2-list-structure)))

(def-substitution-macro g2-list-structure-tail-if (g2-list-structure)
  (when g2-list-structure
    (g2-list-structure-tail g2-list-structure)))

(define-loop-path (g2-list-structure-element) g2-list-structure-elements-of (of))

(defun-for-macro g2-list-structure-elements-of
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
  (let* ((list (make-symbol "LIST"))
	 (next-list-element (make-symbol "NEXT-LIST-ELEMENT"))
	 (init-bindings
	   `((,list ,(second (car prep-phrases)))
	     (,next-list-element nil)
	     (,variable nil)))
	 (prologue-forms
	   `((setq ,next-list-element
		   #-Lockfree-List (g2-list-structure-head ,list)
		   #+Lockfree-List (g2-list-structure-next
				     (g2-list-structure-head ,list) ,list))))
	 (pre-step-tests
	   #-Lockfree-List
	   `(eq ,next-list-element ,list)
	   #+Lockfree-List
	   `(null ,next-list-element))
	 (steppings nil)
	 (post-step-tests nil)
	 (post-step-settings
	   `(,variable ,next-list-element
	     ,next-list-element
	     (g2-list-structure-next ,next-list-element ,list))))
    `(,init-bindings
      ,prologue-forms
      ,pre-step-tests
      ,steppings
      ,post-step-tests
      ,post-step-settings)))

(define-loop-path (g2-list-structure-reverse-element)
		  g2-list-structure-reverse-elements-of (of))

(defun-for-macro g2-list-structure-reverse-elements-of
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
  (let* ((list (make-symbol "LIST"))
	 (next-list-element (make-symbol "NEXT-LIST-ELEMENT"))
	 (init-bindings
	   `((,list ,(second (car prep-phrases)))
	     (,next-list-element nil)
	     (,variable nil)))
	 (prologue-forms
	   `((setq ,next-list-element
		   #-Lockfree-List (g2-list-structure-tail ,list)
		   #+Lockfree-List (g2-list-structure-previous
				      (g2-list-structure-tail ,list) ,list))))
	 (pre-step-tests
	   #-Lockfree-List
	   `(eq ,next-list-element ,list)
	   #+Lockfree-List
	   `(null ,next-list-element))
	 (steppings nil)
	 (post-step-tests nil)
	 (post-step-settings
	   `(,variable ,next-list-element
	     ,next-list-element
	     (g2-list-structure-previous ,next-list-element ,list))))
    `(,init-bindings
      ,prologue-forms
      ,pre-step-tests
      ,steppings
      ,post-step-tests
      ,post-step-settings)))

#+(and development Lockfree-List)
(defun describe-g2-list-structure (g2-list-structure)
  "Display all queue elements in a constant queue (with head and tail), then ~
return the number of elements (not include head and tail)."
  (flet ((print-one (element)
	   (format t "~A: next: ~A, prev: ~A, data: ~A, ref-count: ~D (claim-bit: ~D)~%"
		   (%pointer element)
		   (list-next-element element)
		   (list-previous-element element)
		   (list-element-value element)
		   (reference-count element)
		   (claim-bit element))))
    (let ((element-list nil))
      (print-one (g2-list-structure-head g2-list-structure))
      (loop for element being each g2-list-structure-element of g2-list-structure
	    do
	(print-one element)
	(push (list-element-value element) element-list))
      (print-one (g2-list-structure-tail g2-list-structure))
      (nreverse element-list))))

;;;  The function `create-empty-g2-list-structure' returns a newly allocated
;;;  g2-list structure that is initialized for an empty g2-list (no elements).
;;;  In this case, the head and tail elements point back to the structure
;;;  itself.

;;; A g2-list is represented by a g2-list-structure, where the head of the list
;;; is stored in the next-element slot, the tail of the list is stored in the
;;; previous-element slot, and the datum slot contains the
;;; g2-list-structure-marker.

(defun-simple create-empty-g2-list-structure ()
  (let ((new-list (make-g2-list-element-macro
		    nil nil g2-list-structure-marker nil)))
    #-Lockfree-List
    (setf (list-element-value new-list) g2-list-structure-marker)
    #+Lockfree-List
    (let ((head (make-g2-list-element-macro
		  nil nil g2-list-structure-head-marker nil))
	  (tail (make-g2-list-element-macro
		  nil nil g2-list-structure-tail-marker nil)))
      (setq head (safe-list-read head)
	    tail (safe-list-read tail))
      (clear-lowest-bit (reference-count-and-claim-bit head))
      (clear-lowest-bit (reference-count-and-claim-bit tail))
      (setf (g2-list-structure-head new-list) head
	    (g2-list-structure-tail new-list) tail))
    (initialize-g2-list-structure new-list)
    new-list))

;;; This function simply assume the list is empty.

(defun-simple reclaim-empty-g2-list-structure (g2-list-structure)
  #+Lockfree-List
  (let ((head (g2-list-structure-head g2-list-structure))
	(tail (g2-list-structure-tail g2-list-structure)))
    (reclaim-g2-list-element-macro head)
    (reclaim-g2-list-element-macro tail))
  (reclaim-g2-list-element-macro g2-list-structure))

(def-substitution-macro g2-list-structure-empty-p (g2-list-structure?)
  (or (null g2-list-structure?)
      #-Lockfree-List
      (eq (g2-list-structure-head g2-list-structure?) g2-list-structure?)
      #+Lockfree-List
      (null (g2-list-structure-next
	      (g2-list-structure-head g2-list-structure?)
	      g2-list-structure?))))

#+unused
(defun-simple g2-list-structure-length (g2-list-structure)
  (loop for element = (g2-list-structure-head g2-list-structure)
		    then (list-next-element element)
	for element-value = (list-element-value element)
	until (eq element g2-list-structure)
	count t))

;;; `initialize-g2-list-structure' rewire the internal links of empty lists
#-Lockfree-List
(defun-simple initialize-g2-list-structure (g2-list-structure)
  (setf (g2-list-structure-head g2-list-structure) g2-list-structure)
  (setf (g2-list-structure-tail g2-list-structure) g2-list-structure))

#+Lockfree-List
(defun-simple initialize-g2-list-structure (g2-list-structure)
  (let ((head (g2-list-structure-head g2-list-structure))
	(tail (g2-list-structure-tail g2-list-structure)))
    (setf (list-next-element head) (make-atomic-reference tail)
	  (list-previous-element head) (make-atomic-reference nil))
    (setf (list-next-element tail) (make-atomic-reference nil)
	  (list-previous-element tail) (make-atomic-reference head))))

#+Lockfree-List
(defun-void help-delete-list-node (node)
  (generate-help-delete (node)
    list-previous-element
    list-next-element
    read-list-node
    read-deleted-list-node
    copy-list-node
    release-list-node
    help-delete-list-node))

#+Lockfree-List
(defun-simple help-insert-list-node (prev node)
  (generate-help-insert (prev node)
    list-previous-element
    list-next-element
    read-list-node
    read-deleted-list-node
    copy-list-node
    release-list-node
    help-delete-list-node))

#+Lockfree-List
(defun-void remove-list-cross-reference (node)
  (generate-remove-cross-reference (node)
    list-previous-element
    list-next-element
    read-deleted-list-node
    release-list-node))

#-Lockfree-List
(defmacro g2-list-structure-next (cursor g2-list-structure)
  (declare (ignore g2-list-structure))
  `(list-next-element ,cursor))

#+Lockfree-List
(defun-simple g2-list-structure-next (cursor g2-list-structure)
  (generate-*-next (cursor g2-list-structure)
    g2-list-structure-tail
    list-next-element
    read-deleted-list-node
    release-list-node
    help-delete-list-node))

#-Lockfree-List
(defmacro g2-list-structure-previous (cursor g2-list-structure)
  (declare (ignore g2-list-structure))
  `(list-previous-element ,cursor))

#+Lockfree-List
(defun-simple g2-list-structure-previous (cursor g2-list-structure)
  (generate-*-previous (cursor g2-list-structure)
    g2-list-structure-head
    list-next-element
    list-previous-element
    read-deleted-list-node
    release-list-node
    help-insert-list-node
    g2-list-structure-next))

;;; The macro `g2-list-structure-enqueue' enqueues an element at the end of the
;;; list, for FIFO dequeuing.  It returns the new element-structure.

#-Lockfree-List
(defmacro g2-list-structure-enqueue (thing g2-list-structure outer-list)
  (let* ((list-var
	   (if (symbolp g2-list-structure) g2-list-structure (gensym)))
	 (tail (gensym))
	 (new-element (gensym)))
    `(let* (,@(if (neq list-var g2-list-structure)
		  `((,list-var ,g2-list-structure)))
	    (,tail (g2-list-structure-tail ,list-var))
	    (,new-element
	     (make-g2-list-element-macro ,list-var ,tail ,thing ,outer-list)))
       (setf (list-next-element ,tail) ,new-element)
       (setf (g2-list-structure-tail ,list-var) ,new-element)
       ,new-element)))

#+Lockfree-List
(defun-void g2-list-structure-push-common (node next)
  (generate-*-push-common (node next)
    list-previous-element
    list-next-element
    copy-list-node
    release-list-node
    help-insert-list-node))

#+Lockfree-List ; see `constant-queue-push-right'
(defun-simple g2-list-structure-push-right (g2-list-structure thing outer-list)
  (generate-*-push-right (g2-list-structure
			  g2-list-structure-tail
			  list-previous-element
			  list-next-element
			  copy-list-node
			  read-list-node
			  help-insert-list-node
			  g2-list-structure-push-common)
    (create-list-element thing outer-list)))

#+Lockfree-List
(defmacro g2-list-structure-enqueue (thing g2-list-structure outer-list)
  `(g2-list-structure-push-right ,g2-list-structure ,thing ,outer-list))

;;; The macro `g2-list-structure-filo-enqueue' enqueues an element at the start
;;; of the list, for FILO enqueuing.  It returns the new element structure.

#-Lockfree-List
(defmacro g2-list-structure-filo-enqueue (thing g2-list-structure outer-list)
  (let* ((list-var (if (symbolp g2-list-structure) g2-list-structure (gensym)))
	 (head (gensym))
	 (new-element (gensym)))
    `(let* (,@(if (neq list-var g2-list-structure)
		  `((,list-var ,g2-list-structure)))
	    (,head (g2-list-structure-head ,list-var))
	    (,new-element
	     (make-g2-list-element-macro ,head ,list-var ,thing ,outer-list)))
       (setf (g2-list-structure-head ,list-var) ,new-element)
       (setf (list-previous-element ,head) ,new-element)
       ,new-element)))

#+Lockfree-List
(defun-simple g2-list-structure-push-left (g2-list-structure thing outer-list)
  (generate-*-push-left (g2-list-structure
			 g2-list-structure-head
			 list-previous-element
			 list-next-element
			 copy-list-node
			 read-list-node
			 release-list-node
			 g2-list-structure-push-common)
    (create-list-element thing outer-list)))

#+Lockfree-List
(defmacro g2-list-structure-filo-enqueue (thing g2-list-structure outer-list)
  `(g2-list-structure-push-left ,g2-list-structure ,thing ,outer-list))

;;; The macro `g2-list-structure-insert-element' inserts an element at the given
;;; location in the list.

;;; The macro `g2-list-structure-insert-element-after' inserts an element after
;;; the specified g2-list-element-structure.

;;; The macro `g2-list-structure-insert-element-before' inserts an element
;;; before the specified g2-list-element-structure.

#-Lockfree-List
(defmacro g2-list-structure-insert-element
	  (thing previous-g2-list-element-structure
		 next-g2-list-element-structure outer-list)
  (let* ((new-element (gensym))
	 (previous-element (gensym))
	 (next-element (gensym)))
    `(let* ((,previous-element ,previous-g2-list-element-structure)
	    (,next-element ,next-g2-list-element-structure)
	    (,new-element
	     (make-g2-list-element-macro
	       ,next-element ,previous-element ,thing ,outer-list)))
       (setf (list-next-element ,previous-element) ,new-element)
       (setf (list-previous-element ,next-element) ,new-element)
       ,new-element)))

#-Lockfree-List ; the lockfree version is moved to LISTS
(defmacro g2-list-structure-insert-element-after
	  (thing after-g2-list-element-structure outer-list)
  `(let* ((previous-element ,after-g2-list-element-structure)
	  (next-element (list-next-element previous-element)))
     (g2-list-structure-insert-element
       ,thing previous-element next-element ,outer-list)))

#-Lockfree-List ; the lockfree version is moved to LISTS
(defmacro g2-list-structure-insert-element-before
	  (thing before-g2-list-element-structure outer-list)
  `(let* ((next-element ,before-g2-list-element-structure)
	  (previous-element (list-previous-element next-element)))
     (g2-list-structure-insert-element
       ,thing previous-element next-element ,outer-list)))

;;; The macro `g2-list-structure-delete-element-without-reclaiming-value'
;;; deletes a g2-list-element structure from the g2-list.  It reclaims the
;;; structure, but not the element value that it points to.  This macro is
;;; needed when the caller is holding onto the value and will be responsible for
;;; reclamation.

;;; Note that g2-list-structure-delete-element is more commonly called.

#-Lockfree-List
(defmacro g2-list-structure-delete-element-without-reclaiming-value
    (g2-list-element-structure)
  (let* ((element-var (if (symbolp g2-list-element-structure)
			  g2-list-element-structure
			  (gensym)))
	 (next (gensym))
	 (previous (gensym)))
    `(let* (,@(if (neq element-var g2-list-element-structure)
		  `((,element-var ,g2-list-element-structure)))
	    (,next (list-next-element ,element-var))
	    (,previous (list-previous-element ,element-var)))
       (setf (list-next-element ,previous) ,next)
       (setf (list-previous-element ,next) ,previous)
       (prog1 (list-element-value ,element-var)
	 (reclaim-g2-list-element-macro ,element-var)))))

#+Lockfree-List
(defun g2-list-structure-delete (cursor &optional g2-list-structure)
  (generate-*-delete (cursor g2-list-structure)
		     g2-list-structure-head
		     g2-list-structure-tail
		     list-next-element
		     list-previous-element
		     copy-list-node
		     release-list-node
		     help-delete-list-node
		     help-insert-list-node
		     list-element-value
		     remove-list-cross-reference
		     g2-list-structure-delete))

#+Lockfree-List
(defmacro g2-list-structure-delete-element-without-reclaiming-value
    (g2-list-element-structure)
  `(g2-list-structure-delete ,g2-list-element-structure))

;;; The macro `g2-list-structure-delete-element' deletes a g2-list-element
;;; structure from the g2-list and reclaims the structure and element value that
;;; it points to.  It only reclaims elements of type value and not items.

(defmacro g2-list-structure-delete-element (g2-list-element-structure)
  (let ((element-var (if (symbolp g2-list-element-structure)
			 g2-list-element-structure
			 (gensym))))
    `(let* (,@(if (neq element-var g2-list-element-structure)
		  `((,element-var ,g2-list-element-structure))))
       (reclaim-if-evaluation-value (list-element-value ,element-var))
       (g2-list-structure-delete-element-without-reclaiming-value
	 ,element-var))))

(defun-void g2-list-structure-clear (g2-list-structure)
  (loop with next-element-structure = nil
        for element-structure = #-Lockfree-List
				(g2-list-structure-head g2-list-structure)
				#+Lockfree-List
				(g2-list-structure-next
				  (g2-list-structure-head g2-list-structure)
				  g2-list-structure)
	    then next-element-structure
	until #+Lockfree-List (null element-structure)
	      #-Lockfree-List (eq element-structure g2-list-structure)
	do
    (setf next-element-structure
	  (g2-list-structure-next element-structure g2-list-structure))
    (reclaim-if-evaluation-value-function
      (list-element-value element-structure))
    (reclaim-g2-list-element-macro element-structure))
  (initialize-g2-list-structure g2-list-structure))


;;;; Eval Conses



(defconser eval types)



(defun reclaim-eval-cons-function (cons)
  (reclaim-eval-cons cons))

;;; Cons recycling for EVAL

;;; The following cons recycling set is used for all aspects of the evaluation
;;; that require consing. This includes FOR, all the alists and qlists of EVAL
;;; and FOR, the wake-up pointing, etc. If any EVAL or FOR function supplies
;;; values which are conses, it is the duty of the receiver to release or retain
;;; them. Therefore, the assurance that such conses are from the EVAL pool is
;;; esential. This cons system was moved here from FOR where it previously had
;;; the names FOR-CONS, etc. The add and delete from lists was moved here from
;;; utilities, where it previously used OBTAIN-CONS etc, which is the scheduler
;;; pool.

;;; Note:  The specifically coded conser that was here previously has been
;;; replaced with an invocation of the defconser facility.  -jra 11/15/87



#+unused
(defun reclaim-eval-tree-function (tree)
  (reclaim-eval-tree tree))

;;; A function version of reclaim-eval-list is needed in LISTS.

(defun reclaim-eval-list-function (list)
  (reclaim-eval-list-macro list))




;;; The function `reclaim-eval-alist' reclaims the conses of an alist, returning
;;; them to the eval cons pool.

(defun-simple reclaim-eval-alist (alist)
  (when alist
    (loop for trailer = nil then cons
	  for cons = alist then (cdr-of-cons cons)
	  while cons
	  do
      (reclaim-eval-cons (car-of-cons cons))
	  finally (reclaim-eval-list-given-tail alist trailer)))
  nil)






;;;; Numeric Types


;;; The macro `Numeric-subtype-p' of a symbol returns nil if that symbol is not
;;; a numeric subtype such as a unit-of-measure or 'number or 'seconds.  If it
;;; is such, the value returned is the symbol itself, or the plural of the
;;; symbol if a plural has been defined. Singular forms should not exist in
;;; internal forms of expressions. They are converted at parse and translate
;;; time, and the mapping feature descibed here is for the use of the parser
;;; only.

;;; Note:  These concepts will be defined more thoroughly when we implement a
;;; dimensional theory!  -jra 9/2/87

;;; Well, we should get real here.  We are never going to build a dimensional
;;; theory.  -jra 8/27/91

(def-global-or-kb-specific-property-name numeric-data-type)

(def-substitution-macro number-subtype-p (symbol)
  (or (eq symbol 'number)
      (eq symbol 'integer)
      (eq symbol 'float)
      (eq symbol 'long)
      (numeric-data-type symbol)))

;; Need functional-number-subtype-p for an ICP value reader. (jh, 3/7/90)

#+unused
(defun functional-number-subtype-p (symbol)
  (number-subtype-p symbol))

;;; System supplied types for integer and float are being added to the system as
;;; part of procedures.  They are subtypes of number, but contain their own
;;; subtyping as well.

;; The types integer and float are not going to be released until version 2.1.
;; -jra 6/18/89

;; They are going into Version 3.0.  Note that they will not support subtypes.
;; The useless units of measure declaration will only declare quantities, not
;; integers and floats.  -jra 11/24/90





;;;; Evaluation Values




;;; The following operations define what is available for evaluation values.
;;; Evaluation values are those values that are used as incremental datum values
;;; during execution of the evaluation environments of G2.  These represent the
;;; six types of datum allowed in G2 computations: number, integer, float,
;;; symbol, text, and truth-value.  Besides these six, there is a means of
;;; implementing arbitrary evaluation values, through the def-evaluation-value
;;; macro.  There is These operations document and abstract the representation
;;; and implementations of these values.  Evaluation values are managed values,
;;; in that the floats used here are not temporary, but these representations
;;; are used because (we hope) they are faster at run-time.

;;; The following are the implementation types for evaluation values:

;;;   quantity (represented as a type by the symbol number, but printed to the
;;; user as quantity, confused yet?) is a fixnum or managed-float;

;;;   integer is a fixnum;

;;;   float is a managed-float;

;;;   symbol is a Lisp symbol (though this could be changed in the future when
;;; we are able to reclaim user symbols, the primitives for allocation and
;;; reclaimation are there);

;;;   text is a Lisp string (this differs from the user interface definition of
;;; the type "text" which is a formatted text item, and text-string is what we
;;; have defined here as text); and

;;;   truth-value is a cons whose car is a fixnum between truth (1000) and
;;; falsity (-1000) and whose cdr is the symbol TRUTH-VALUE (more on this
;;; below).

;;; Besides the above six subtypes of datum, there are other kinds of evaluation
;;; values.  They are defined using the macro def-evaluation-value.  For each
;;; type of evaluation value, there must also be definitions for
;;; def-evaluation-value-reclaimer and def-evaluation-value-copier.  Instances
;;; of these types are always eval-conses whose cdr is the symbol naming the
;;; evaluation-value type, and whose car contains Lisp objects specific to the
;;; type.  There are currently three kinds of evaluation value types other than
;;; the datum.

;;; In addition, a deep copier can be provided which recursively copies
;;; any sequences and structures contained in the evaluation value. If
;;; a given evaluation type never contains such embedded sequences and
;;; structures, the deep copier need not be provided, and
;;; deep-copy-evaluation-value and deep-copy-if-evaluation-value will
;;; use the shallow copiers.

;;;   iteration-state is a cons whose car is a continuation for role service,
;;; and whose cdr is the symbol ITERATION-STATE.

;;;   every-state is cons whose car is a list of lists of items, evaluation
;;; values, or nil, and whose cdr is the symbol EVERY-STATE.

;;;   block-component is a cons whose car is a designation of a component of a
;;; frame (whatever it is we decide that will be), and whose cdr is the symbol
;;; BLOCK-COMPONENT

;;; These are the current implementation types for these values.  Each of these
;;; types has make, copy, value-of, predicates, and reclaim macros defined below
;;; (with the exception that iteration-state has no copy).  Even though some of
;;; the macros are currently noops, specifically for the symbol and integer
;;; types, we may want to use different implementations in the future, and so
;;; the abstractions should be used for all evaluation-values.




;;; The macro `def-evaluation-value' is used to define new kinds of evaluation
;;; values.  It takes one symbol, the name of the type, registers a new type
;;; specification for this kind of thing, and defines several functions and
;;; macros for manipulating it.  Each type defined via def-evaluation-value must
;;; have several auxiliary functions defined for it.  They are a reclaimer, a
;;; copier, a writer, and a comparitor.

;;; The type specification for such an evaluation value is a one element long
;;; list containing the name of the type.  The type is a subtype of
;;; evaluation-value.

;;; The generated macro `make-evaluation-X' takes a single value as its argument
;;; and returns an instance of the evaluation value encapsulating the argument.
;;; The format of the returned value will be an eval cons whose cdr is the
;;; symbol naming the type and whose car is the given value.

;;; The generated macro `evaluation-X-value' takes an instance of the evaluation
;;; value and returns the encapsulated value.  Setf can be used with this
;;; fetcher to replace the encapsulated value, though no automatic reclaimation
;;; of the previous encapsulated value will take place.

;;; The generated substitution macro `evaluation-X-p' takes evaluation values
;;; and returns whether or not the given thing is an instance of the subtype of
;;; evaluation values.  This can also be accomplished by
;;; type-specification-type-p, but this macro is more efficient when you know
;;; you are testing for this type.

#-chestnut-trans
(eval-when (:compile-toplevel :load-toplevel :execute)
  (pushnew :evaluation-types-using-binary-tree *features*))

#+evaluation-types-using-binary-tree
(eval-when (:compile-toplevel :load-toplevel :execute)
  (def-skip-list-or-binary-tree evaluation-types
    :constructor make-evaluation-types-tree
    :hash-function sxhash-symbol
    :accessor get-evaluation-types
    :use-binary-tree nil))

#-evaluation-types-using-binary-tree
(eval-when (:compile-toplevel :load-toplevel :execute)
  (defmacro get-evaluation-types (type evaluation-types)
    `(memq ,type ,evaluation-types)))

(eval-when (:compile-toplevel :load-toplevel :execute)

(define-loop-path evaluation-type
  #+(and evaluation-types-using-binary-tree skip-list)
  expand-skip-list-or-binary-tree-value-loop-iterator
  #+(and evaluation-types-using-binary-tree (not skip-list))
  expand-binary-tree-value-loop-iterator
  #-evaluation-types-using-binary-tree
  expand-evaluation-types-loop-iterator (of))

#-evaluation-types-using-binary-tree
(defun-for-macro expand-evaluation-types-loop-iterator
    (path-name variable data-type prep-phrases inclusive? allowed-prepositions data)
  (declare (ignore data-type data allowed-prepositions))
  (when (null prep-phrases)
    (error "OF is missing in ~S iteration path of ~S" path-name variable))
  (when inclusive?
    (error "Inclusive stepping is not supported in ~S path of ~S (prep-prase = ~:S)"
	   path-name variable prep-phrases))
  (let* ((evaluation-types (cadar prep-phrases))
	 (sublist-variable (make-symbol "EVALUATION-TYPES-SUBLIST"))
	 (generator-bindings `((,sublist-variable ,evaluation-types)
			       (,variable nil)))
	 (generator-initialize nil)
	 (generator-eof-p `(null ,sublist-variable))
	 (generator-advance
	   `(,variable (car-of-cons ,sublist-variable)
	     ,sublist-variable (cdr-of-cons ,sublist-variable))))
    `(,generator-bindings
      ,generator-initialize
      ,generator-eof-p
      nil
      nil
      ,generator-advance)))

) ; eval-when

(eval-when (:compile-toplevel :load-toplevel :execute)
  (defvar defined-evaluation-value-types
    #+evaluation-types-using-binary-tree (make-evaluation-types-tree)
    #-evaluation-types-using-binary-tree nil)

  (defvar defined-evaluation-datum-types nil))

;;; The macro `defined-evaluation-value-type-p' tests if the given thing is a
;;; symbol naming a defined type of evaluation value.

(def-substitution-macro defined-evaluation-value-type-p (possible-type-name)
  (and (symbolp possible-type-name)
       (get-evaluation-types possible-type-name defined-evaluation-value-types)))




;;; The macro `valid-evaluation-value-type-specification-p' takes a thing that
;;; is possibly a type specification and returns whether or not it is a valid
;;; type-specification for a defined evaluation-value type.

(def-substitution-macro valid-evaluation-value-type-specification-p (thing)
  (and (consp thing)
       (defined-evaluation-value-type-p (car-of-cons thing))))
  





;;; The macro `defined-evaluation-datum-type-p' tests if the given thing is a
;;; symbol naming a defined type of evaluation value that is also a datum.
;;; See the macro def-evaluation value for the difference between the two.

(defmacro defined-evaluation-datum-type-p (possible-type-name)
  `(memq ,possible-type-name defined-evaluation-datum-types))



(def-global-property-name type-specification-of-defined-evaluation-type t)

(defmacro evaluation-value-cdr-marker (symbol)
  (cond ((eq symbol 'truth-value)
	 `',symbol)
	(t
	 (unless (get-evaluation-types symbol defined-evaluation-value-types)
	   (error "~S is not a defined evaluation-type" symbol))
	 `',symbol)))

(defmacro def-evaluation-value (type-name &optional is-a-datum-p)
  (let ((constructor (intern (format nil "MAKE-EVALUATION-~a" type-name)))
	(fetcher (intern (format nil "EVALUATION-~a-VALUE" type-name)))
	(predicate (intern (format nil "EVALUATION-~a-P" type-name))))
    `(progn
       (eval-when (:compile-toplevel :load-toplevel :execute)
	 #+evaluation-types-using-binary-tree
	 (setf (get-evaluation-types ',type-name defined-evaluation-value-types)
	       ',type-name)
	 #-evaluation-types-using-binary-tree
	 (pushnew ',type-name defined-evaluation-value-types))
       ,@(when is-a-datum-p
	   `((pushnew ',type-name defined-evaluation-datum-types)))
       (defmacro ,constructor (encapsulated-value)
	 `(eval-cons ,encapsulated-value
		     (evaluation-value-cdr-marker ,',type-name)))
       (defmacro ,fetcher (,type-name)
	 (list 'car-of-cons ,type-name))
       (def-substitution-macro ,predicate (item-or-evaluation-value)
	 (and (consp item-or-evaluation-value)
	      (eq (cdr-of-cons item-or-evaluation-value)
		  (evaluation-value-cdr-marker ,type-name))))
       (setf (type-specification-of-defined-evaluation-type ',type-name)
	     '(,type-name))
       ',type-name)))




;;; The macro `def-evaluation-value-reclaimer' is used to define a function
;;; named `reclaim-evaluation-X'.  The arguments to this macro are the type name
;;; and forms to reclaim the encapsulated value.  The evaluation value
;;; is available in the variable given by the type name.  Note that the forms
;;; should only reclaim the encapsulated value, and other code within the
;;; emitted function will reclaim the cons that wraps the encapsulated value.
;;; If you want to manage the reclamation of the entire value yourself, place a
;;; NIL into the type name variable, and the emitted code will then do nothing.

;;; Note that every evaluation value type defined with def-evaluation-value
;;; must have a defined reclaimer.  If the encapsulated value does not need to
;;; be reclaimed (if it is a fixnum, for example) then the forms defined
;;; reclamation code may be omitted.

(def-global-property-name defined-evaluation-type-reclaimer t)

(defmacro def-evaluation-value-reclaimer (type-name &body forms)
  (let ((reclaimer (intern (format nil "RECLAIM-EVALUATION-~a" type-name)))
	#+development
	(predicate (intern (format nil "EVALUATION-~a-P" type-name))))
    `(progn
       (defun-simple ,reclaimer (,type-name)
	 #+development
	 (unless (,predicate ,type-name)
	   (cerror "Continue, not reclaiming value."
		   "Reclaiming ~a as a ~a."
		   ,type-name
		   ',type-name)
	   (return-from ,reclaimer nil))
	 ,@forms
	 (when ,type-name
	   (reclaim-eval-cons-macro ,type-name))
	 nil)
       (setf (defined-evaluation-type-reclaimer ',type-name)
	     #',reclaimer)
       ',reclaimer)))




;;; The macro `def-evaluation-value-copier' is used to define a function named
;;; `copy-evaluation-X'.  The arguments to this macro are the type-name and a
;;; set of forms which will copy the value.  The old value will be bound in a
;;; variable whose name is the type name.

;;; Similarly, the macro `def-evaluation-value-deep-copier' is used to define a
;;; function named `deep-copy-evaluation-X'. The deep copier should recursively
;;; copy any sequences and structures contained in the argument. If no deep
;;; copier is provided for a given evaluation type, deep-copy-evaluation-value
;;; will use the shallow copier instead.

(def-global-property-name defined-evaluation-type-copier t)

(def-global-property-name defined-evaluation-type-deep-copier t)

(defmacro def-evaluation-value-copier (type-name &body forms)
  (let ((copier (intern (format nil "COPY-EVALUATION-~a" type-name)))
	#+development
	(predicate (intern (format nil "EVALUATION-~a-P" type-name))))
    `(progn
       (defun-simple ,copier (,type-name)
	 #+development
	 (unless (,predicate ,type-name)
	   (error
	     "Copying ~a as a ~a, though the predicate doesn't recognize it."
	     ,type-name
	     ',type-name))
	 ,@forms)
       (setf (defined-evaluation-type-copier ',type-name) #',copier)
       ',copier)))

(defmacro def-evaluation-value-deep-copier (type-name &body forms)
  (let ((copier (intern (format nil "DEEP-COPY-EVALUATION-~a" type-name)))
	#+development
	(predicate (intern (format nil "EVALUATION-~a-P" type-name))))
    `(progn
       (defun-simple ,copier (,type-name)
	 #+development
	 (unless (,predicate ,type-name)
	   (error
	     "Copying ~a as a ~a, though the predicate doesn't recognize it."
	     ,type-name
	     ',type-name))
	 ,@forms)
       (setf (defined-evaluation-type-deep-copier ',type-name) #',copier)
       ',copier)))

;;; `copy-evaluation-value' and `copy-if-evaluation-value' are
;;; defined up here so it can be used in the rest of this file.

;;; These do shallow copies. See below for deep-copy versions.

(def-substitution-macro copy-evaluation-value (evaluation-value)
  (if (or (evaluation-integer-p evaluation-value)
	  (evaluation-symbol-p evaluation-value))
      evaluation-value
      (copy-evaluation-value-1 evaluation-value)))

(def-substitution-macro copy-if-evaluation-value (thing)
  (if (or (evaluation-integer-p thing)
	  (evaluation-symbol-p thing)
	  (simple-vector-p thing)) ; frames...
      thing
    (copy-if-evaluation-value-1 thing)))

(def-substitution-macro deep-copy-evaluation-value (evaluation-value)
  (if (or (evaluation-integer-p evaluation-value)
	  (evaluation-symbol-p evaluation-value))
      evaluation-value
      (deep-copy-evaluation-value-1 evaluation-value)))

(def-substitution-macro deep-copy-if-evaluation-value (thing)
  (if (or (evaluation-integer-p thing)
	  (evaluation-symbol-p thing)
	  (simple-vector-p thing)) ; frames...
      thing
      (deep-copy-if-evaluation-value-1 thing)))


;;; The macro `def-evaluation-value-validator' is used to define a function
;;; named `validate-evaluation-X'.  The arguments to this macro are the
;;; type-name and a set of forms which will validate.  The value will be bound
;;; in a variable whose name is the type name, the user of the macro provides a
;;; variable to hold the frame-serial-number used for validation.

(def-global-property-name defined-evaluation-type-validator t)

(defmacro def-evaluation-value-validator (type-name (frame-serial-number-var) &body forms)
  (let ((validator (intern (format nil "VALIDATE-EVALUATION-~a" type-name)))
	#+development
	(predicate (intern (format nil "EVALUATION-~a-P" type-name))))
    (multiple-value-bind (declaration-and-documentation body)
	(split-defun-body forms)    `(progn
       (defun-simple ,validator (,type-name ,frame-serial-number-var)
	 ,@declaration-and-documentation
	 #+development
	 (unless (,predicate ,type-name)
	   (error
	     "Validating ~a as a ~a, though the predicate doesn't recognize it."
	     ,type-name
	     ',type-name))
	 ,@body)
       (setf (defined-evaluation-type-validator ',type-name) #',validator)
       ',validator))))




;;; The macro `def-evaluation-value-comparitor' is used to define a function
;;; which compares instances of a particular evaluation value type for equality.
;;; The generated function is named `evaluation-X-eql'.  The variables available
;;; within the body of the comparitor are X-1 and X-2, where X is the type name.
;;; The body should return NIL or non-NIL, reflecting value equivalence for
;;; types for which this is a meaningful concept.  If no two evaluation values
;;; can ever be considered equivalent within a type, then the body of the
;;; comparitor should declare ignore the arguments and always return NIL.

;;; The macro `def-evaluation-value-=' is used to extend the functionality of
;;; evaluation-value-= in a parallel fashion.  It differs from the EQL version
;;; in that can compare numbers of differing types.

(def-global-property-name defined-evaluation-type-comparitor t)
(def-global-property-name defined-evaluation-type-= t)

(defmacro def-evaluation-value-comparitor (type-name &body forms)
  (let ((comparitor (intern (format nil "EVALUATION-~a-EQL" type-name)))
	(arg-1 (intern (format nil "~a-1" type-name)))
	(arg-2 (intern (format nil "~a-2" type-name))))
    `(progn
       (defun-simple ,comparitor (,arg-1 ,arg-2)
	 ,@forms)
       (setf (defined-evaluation-type-comparitor ',type-name)
	     #',comparitor)
       ',comparitor)))

(defmacro def-evaluation-value-= (type-name &body forms)
  (let ((function (intern (format nil "EVALUATION-~a-=" type-name)))
	(arg-1 (intern (format nil "~a-1" type-name)))
	(arg-2 (intern (format nil "~a-2" type-name))))
    `(progn
       (defun-simple-into-place (,function
				   (defined-evaluation-type-= ',type-name))
	   (,arg-1 ,arg-2)
	 ,@forms)
       ',function)))

(defmacro evaluation-value-of-type-= (type-specification value1 value2)
  `(funcall-simple-compiled-function
     (compiled-function-in-place
       (defined-evaluation-type-= (car-of-cons ,type-specification)))
     ,value1 ,value2))




;;; The macro `def-evaluation-value-writer' takes a type name and a body of
;;; forms, and defines a function called `write-evaluation-X' which is called on
;;; to twrite evaluation values.  The type name symbol is bound to the value.

(def-global-property-name defined-evaluation-type-writer t)

(defmacro def-evaluation-value-writer (type-name &body forms)
  (let ((writer (intern (format nil "WRITE-EVALUATION-~a" type-name)))
	#+development
	(predicate (intern (format nil "EVALUATION-~a-P" type-name))))
    `(progn
       (defun-simple ,writer (,type-name)
	 #+development
	 (unless (,predicate ,type-name)
	   (cerror
	     "Continue"
	     "Writing ~a as a ~a, though the predicate doesn't recognize it."
	     ,type-name
	     ',type-name)
	   (return-from ,writer nil))
	 ,@forms
	 nil)
       (setf (defined-evaluation-type-writer ',type-name) #',writer)
       ',writer)))











;;; Evaluation truth values are represented as an eval cons whose car is a
;;; fixnum representing a truth-value and whose cdr is the symbol TRUTH-VALUE.
;;; Users of evaluation truth-values should use the macro
;;; make-evaluation-truth-value to create them, reclaim-evaluation-value or
;;; reclaim-evaluation-truth-value to reclaim them, and the accessor
;;; evaluation-truth-value to get the fixnum truth value stored within the
;;; evaluation truth value.

;;; As an internal optimization of this facility, there are two special
;;; instances of this data structure to represent true and false.  They are
;;; stored in the constants evaluation-true-value and evaluation-false-value.
;;; The reclaimers will do the right thing when given these values.  These two
;;; values are the only members of a subtype of truth-value called boolean.

;;; The substitution macro `make-evaluation-truth-value' takes a fixnum
;;; representing a truth value and returns an evaluation-truth-value which
;;; represents that value.

;;; The substitution macro `reclaim-evaluation-truth-value' takes an evaluation
;;; truth value and reclaims it.

;;; In some circumstances optimizations can be made if the implementation of a
;;; facility can know that evaluation truth values are implemented as conses.
;;; The following predicate should be used to determine if conses are
;;; evaluation truth values.  The macro `cons-is-evaluation-truth-value-p' is
;;; used as a predicate when you know that the item given is a cons.

;;; The macro `evaluation-truth-value-p' takes an evaluation value and
;;; determines whether or not it is an evaluation-truth-value.

;;; The macro `copy-evaluation-truth-value' takes an evaluation truth value and
;;; returns a newly allocated copy of that value.

;;; The macro `evaluation-truth-value-value' takes an evaluation truth value
;;; and returns that fixnum that is the value of that truth value.

;;; The macro `evaluation-truth-value-not' takes an evaluation truth value
;;; (which is reclaimed by this operation) and returns a new (or possibly
;;; modified version of the given evaluation-truth-value) which contains the
;;; logical not of the given value.

;;; The macro `valid-value-for-managed-truth-value-p' tests whether thing is
;;; valid as the value of a truth value, namely an integer in the range
;;; [falsity..truth].  Managed truth values are stored in slots such as
;;; current-value-of-variable-or-parameter and
;;; initial-value-of-variable-or-parameter (both for class
;;; variable-or-parameter).
;;;
;;; Note that this does not say that thing is necessarily the value of a truth
;;; value: it just says it could be.  This can also be used to determine if
;;; thing would be suitable as the "fixnum-truth-value" arg to
;;; make-evaluation-truth-value.

(defparameter evaluation-true-value (cons truth 'truth-value))

(defparameter evaluation-false-value (cons falsity 'truth-value))

(defmacro make-evaluation-truth-value (fixnum-truth-value)
  (cond ((constantp fixnum-truth-value)
	 (let ((value (eval fixnum-truth-value)))
	   (cond ((=f value truth)
		  'evaluation-true-value)
		 ((=f value falsity)
		  'evaluation-false-value)
		 (t
		  `(eval-cons-macro ,fixnum-truth-value 'truth-value)))))
	((symbolp fixnum-truth-value)
	 `(cond ((=f ,fixnum-truth-value truth)
		 evaluation-true-value)
		((=f ,fixnum-truth-value falsity)
		 evaluation-false-value)
		(t
		 (eval-cons ,fixnum-truth-value 'truth-value))))
	(t
	 (let ((value (gensym)))
	   `(let ((,value ,fixnum-truth-value))
	      (cond ((=f ,value truth)
		     evaluation-true-value)
		    ((=f ,value falsity)
		     evaluation-false-value)
		    (t
		     (eval-cons ,value 'truth-value))))))))




;;; The macro `make-evaluation-boolean-value' takes a true or NIL argument and
;;; returns an evaluation-boolean for truth or falsity as its result.

(defmacro make-evaluation-boolean-value (nil-or-non-null)
  `(if ,nil-or-non-null evaluation-true-value evaluation-false-value))

(defun-simple make-evaluation-truth-value-function (fixnum-truth-value)
  (make-evaluation-truth-value fixnum-truth-value))

(def-substitution-macro reclaim-evaluation-truth-value (evaluation-truth-value)
  (unless (or (eq evaluation-truth-value evaluation-true-value)
	      (eq evaluation-truth-value evaluation-false-value))
    (reclaim-eval-cons evaluation-truth-value))
  nil)

(defmacro reclaim-evaluation-boolean (evaluation-boolean)
  ;; In case this form causes a side effect, we will evaluate it, but the value
  ;; needs no reclaimation.
  `(progn ,evaluation-boolean nil))

(defmacro evaluation-truth-value-value (evaluation-truth-value)
  `(car-of-cons ,evaluation-truth-value))

(defun-simple evaluation-truth-value-value-function (evaluation-truth-value)
  (evaluation-truth-value-value evaluation-truth-value))

(defmacro evaluation-boolean-value (evaluation-boolean)
  `(evaluation-truth-value-value ,evaluation-boolean))

(def-substitution-macro evaluation-truth-value-p (evaluation-value)
  (and (consp evaluation-value)
       (eq (cdr-of-cons evaluation-value) 'truth-value)))

(def-substitution-macro evaluation-boolean-p (evaluation-value)
  (and (evaluation-truth-value-p evaluation-value)
       (let ((value (evaluation-truth-value-value evaluation-value)))
	 (or (eq value truth) (eq value falsity)))))

(defmacro cons-is-evaluation-truth-value-p (cons)
  `(eq (cdr-of-cons ,cons) 'truth-value))

(defmacro cdr-of-evaluation-truth-value-p (cdr)
  `(eq ,cdr 'truth-value))

(defmacro cons-is-evaluation-boolean-p (cons)
  `(evaluation-boolean-p ,cons))

;;; This is the original version.
#+ignore
(def-substitution-macro copy-evaluation-truth-value (evaluation-truth-value)
  (if (or (eq evaluation-truth-value evaluation-true-value)
	  (eq evaluation-truth-value evaluation-false-value))
      evaluation-truth-value
      (eval-cons (car-of-cons evaluation-truth-value) 'truth-value)))

;;; The new version generates less code on special values.
;;; author: Chun Tian (binghe), Mar 2015
;;;
;;; (copy-evaluation-truth-value evaluation-true-value) -> evaluation-true-value
;;; (copy-evaluation-truth-value evaluation-false-value) -> evaluation-false-value
;;;
;;; (copy-evaluation-truth-value a) ->
;;;   (LET NIL
;;;     (COND ((OR (EQ A EVALUATION-TRUE-VALUE)
;;;                (EQ A EVALUATION-FALSE-VALUE))
;;;            A)
;;;           (T (EVAL-CONS (CAR-OF-CONS A) 'TRUTH-VALUE))))
;;;
;;; (copy-evaluation-truth-value (f a)) ->
;;;   (LET ((#1=#:EVALUATION-VALUE (F A)))
;;;     (COND ((OR (EQ #1# EVALUATION-TRUE-VALUE)
;;;                (EQ #1# EVALUATION-FALSE-VALUE)) #1#)
;;;           (T (EVAL-CONS (CAR-OF-CONS #1#) 'TRUTH-VALUE))))

(defmacro copy-evaluation-truth-value (evaluation-truth-value)
  (if (or (eq evaluation-truth-value 'evaluation-true-value)
	  (eq evaluation-truth-value 'evaluation-false-value))
      evaluation-truth-value
    (let ((evaluation-value (if (atom evaluation-truth-value)
				evaluation-truth-value
			      (make-symbol "EVALUATION-VALUE"))))
      `(let (,@(unless (atom evaluation-truth-value)
		 `((,evaluation-value ,evaluation-truth-value))))
	 (cond ((or (eq ,evaluation-value evaluation-true-value)
		    (eq ,evaluation-value evaluation-false-value))
		,evaluation-value)
	       (t
		(eval-cons (car-of-cons ,evaluation-value) 'truth-value)))))))

(defmacro evaluation-boolean-is-true-p (evaluation-boolean)
  `(and (evaluation-truth-value-p ,evaluation-boolean)
	(eq (evaluation-truth-value-value ,evaluation-boolean) truth)))

(defmacro copy-evaluation-boolean (evaluation-boolean)
  evaluation-boolean)

(defun copy-evaluation-truth-value-function (evaluation-truth-value)
  (copy-evaluation-truth-value evaluation-truth-value))

(def-substitution-macro evaluation-truth-value-not (evaluation-truth-value)
  (cond ((eq evaluation-truth-value evaluation-true-value)
	 evaluation-false-value)
	((eq evaluation-truth-value evaluation-false-value)
	 evaluation-true-value)
	(t
	 (setf (car-of-cons evaluation-truth-value)
	       (-f (car-of-cons evaluation-truth-value)))
	 evaluation-truth-value)))

(defmacro evaluation-boolean-not (evaluation-boolean)
  `(if (evaluation-boolean-is-true-p ,evaluation-boolean)
       evaluation-false-value
       evaluation-true-value))

(defun evaluation-truth-value-is-true-p (evaluation-truth-value)
  (>=f (evaluation-truth-value-value evaluation-truth-value)
       (truth-threshold-parameter-function)))

(def-substitution-macro valid-value-for-managed-truth-value-p (thing)
  (and (fixnump thing) (<=f falsity thing truth)))

(defun evaluation-value-is-true-p (evaluation-value)
  (and (evaluation-truth-value-p evaluation-value)
       (evaluation-truth-value-is-true-p evaluation-value)))




;;; The macro `make-evaluation-text-reclaiming-argument' takes a text-string and
;;; transforms it into an evaluation-text.  Note that this is a noop right now,
;;; but it provides the proper abstraction.

;;; The macro `make-evaluation-text' takes a text string and makes a new
;;; evaluation text containing the same characters.  Note that this operation
;;; does not reclaim the text string given.

;;; The macro `reclaim-evaluation-text' reclaims an evaluation text string.

;;; The macro `copy-evaluation-text' takes an evaluation text and returns a
;;; newly allocated copy of it.

;;; The macro `evaluation-text-p' takes an evaluation-value and returns whether
;;; or not it is an evaluation text.

;;; The macro `evaluation-text-value' takes an evaluation-text and returns the
;;; text string stored within it.  This value does not need to be seperately
;;; reclaimed, and gets mutated if the evaluation-text is reclaimed.

(defmacro make-evaluation-text-reclaiming-argument (text-string)
  text-string)

(defmacro make-evaluation-text (text-string)
  `(copy-as-wide-string ,text-string))

(defmacro reclaim-evaluation-text (text)
  `(reclaim-text-string ,text))

(defmacro copy-evaluation-text (evaluation-text)
  `(copy-wide-string ,evaluation-text))

(defmacro evaluation-text-p (evaluation-value)
  `(text-string-p-macro ,evaluation-value))

(defmacro evaluation-text-value (evaluation-text)
  evaluation-text)




;;; Note that the following abstraction for evaluation-integers is all noops
;;; now.  However, after 3.0 we may want to move over to 32 bit integers (just
;;; like all the REAL langauges), and this abstraction would be necessary at
;;; that point.  -jra & cpm 2/27/91

;;; The macro `make-evaluation-integer' takes a fixnum and transforms it into an
;;; evaluation-integer.  Note that this is a noop right now, but it provides the
;;; proper abstraction.

;;; The macro `reclaim-evaluation-integer' reclaims an evaluation integer.
;;; Another noop.

;;; The macro `copy-evaluation-integer' takes an evaluation integer and returns a
;;; newly allocated copy of it.

;;; The macro `evaluation-integer-p' takes an evaluation-value and returns whether
;;; or not it is an evaluation integer.

;;; The macro `evaluation-integer-value' takes an evaluation-integer and returns
;;; the fixnum stored within it.

(defmacro make-evaluation-integer (fixnum)
  fixnum)

(defmacro reclaim-evaluation-integer (evaluation-integer)
  (declare (ignore evaluation-integer))
  nil)

(defmacro copy-evaluation-integer (evaluation-integer)
  evaluation-integer)




;;; The macro `evaluation-integer-p' takes an evaluation-value and returns
;;; whether it is an evaluatio-integer.  Note that on Lisp machines this will
;;; accept bignums as well, as long as they are 29 bits long or less.  This is
;;; done so that Lisp machines can mimic our distribution environments, which
;;; have 30 bit, signed fixnums.

(defmacro evaluation-integer-p (evaluation-value)
  `(fixnump ,evaluation-value))

(defmacro evaluation-integer-value (evaluation-integer)
  evaluation-integer)




;;; The macro `evaluation-float-p' is used to test for evaluation floats.

;;; The macro `cons-is-evaluation-float-p' is an internal to the
;;; evaluation-value facility which provides a predicate to code that is willing
;;; to depend upon the fact that evaluation-floats are encapsulated in conses.
;;; Any code using this predicate may have to be changed if the representation
;;; of evaluation-floats or managed-floats changes.  -jra & cpm 2/27/91

;;; The macro `make-evaluation-float' takes a gensym-float and returns an
;;; evaluation-float.

;;; The macro `evaluation-float-value' takes an evaluation-float and returns a
;;; gensym-float which is the value stored in the evaluation-float.  Setf can be
;;; used to modify the value of an evaluation float, though the preferred
;;; interface is `mutate-evaluation-float-value' which always returns NIL and can
;;; be optimized better.

;;; The macro `reclaim-evaluation-float' takes an evaluation-float and reclaims
;;; it.

;;; The macro `copy-evaluation-float' takes an evaluation-float and returns a
;;; newly allocated evaluation-float which contains the same value.

;;; The macro `transform-evaluation-float-into-managed-float' returns a
;;; managed-float, consuming the evaluation-float.  Note that currently
;;; evaluation-floats are implemented as managed-floats.

(defmacro evaluation-float-p (evaluation-value)
  `(managed-float-p ,evaluation-value))

(defmacro copy-managed-float-into-evaluation-float (managed-float)
  `(copy-managed-float ,managed-float))

#-development
(defmacro make-evaluation-float (gensym-float)
  `(allocate-managed-float ,gensym-float))

#+development
(defun-simple make-evaluation-float (gensym-float)
  (allocate-managed-float gensym-float))

(declare-side-effect-free-function
  make-evaluation-float-from-evaluation-integer)

(defun-simple make-evaluation-float-from-evaluation-integer (evaluation-integer)
  (let ((fixnum (evaluation-integer-value evaluation-integer)))
    (declare (type fixnum fixnum))
    (reclaim-evaluation-integer evaluation-integer)
    (make-evaluation-float
      (coerce-fixnum-to-gensym-float fixnum))))

(defmacro evaluation-float-value (evaluation-float)
  `(managed-float-value ,evaluation-float))

(defmacro mutate-evaluation-float-value (evaluation-float gensym-float)
  `(mutate-managed-float-value ,evaluation-float ,gensym-float))

(defmacro setf-evaluation-float-value (evaluation-float gensym-float)
  `(setf (managed-float-value ,evaluation-float) ,gensym-float))

(defsetf evaluation-float-value setf-evaluation-float-value)

(defmacro reclaim-evaluation-float (evaluation-float)
  (if (eval-feature :development)
      (let ((float (gensym)))
	`(let ((,float ,evaluation-float))
	   (unless (evaluation-float-p ,float)
	     (current-system-case
	       (ab
		 (reclaim-evaluation-float-error ,float -1))))
	   (reclaim-managed-float ,float)))
      `(reclaim-managed-float ,evaluation-float)))

(defmacro reclaim-evaluation-float-macro (evaluation-float)
  `(reclaim-managed-float ,evaluation-float))

(defun-simple reclaim-evaluation-float-function (evaluation-float)
  (reclaim-evaluation-float evaluation-float))

(defmacro copy-evaluation-float (evaluation-float)
  `(copy-managed-float ,evaluation-float))

(defun-simple copy-evaluation-float-from-phrase-float (phrase-float)
  (let ((new-evaluation-float nil))
    (with-temporary-gensym-float-creation copy-evaluation-float-from-phrase-float
      (setq new-evaluation-float
	    (make-evaluation-float (phrase-float-value phrase-float))))
    new-evaluation-float))

;; The function above might be better optimized with mutate-managed-float.  -jra
;; 1/25/92


(defmacro transform-evaluation-float-into-managed-float (evaluation-float)
  evaluation-float)


;;; Evaluation long (int64)

(defmacro evaluation-long-p (evaluation-value)
  `(managed-long-p ,evaluation-value))

(defun-simple make-evaluation-long (integer)
  (cond ((long-p integer)
	 (allocate-managed-long integer))
	(t
	 (let ((long-value (coerce-to-gensym-long integer)))
	   (allocate-managed-long long-value)))))

(defmacro evaluation-long-value (evaluation-long)
  `(managed-long-value ,evaluation-long))

(defmacro mutate-evaluation-long-value (evaluation-long gensym-long)
  `(mutate-managed-long-value ,evaluation-long ,gensym-long))

(defmacro setf-evaluation-long-value (evaluation-long gensym-long)
  `(setf (managed-long-value ,evaluation-long) ,gensym-long))

(defsetf evaluation-long-value setf-evaluation-long-value)

(defmacro reclaim-evaluation-long (evaluation-long)
  (if (eval-feature :development)
      (let ((long (gensym)))
	`(let ((,long ,evaluation-long))
	   (unless (evaluation-long-p ,long)
	     (current-system-case
	       (ab
		 (reclaim-evaluation-long-error ,long -1))))
	   (reclaim-managed-long ,long)))
      `(reclaim-managed-long ,evaluation-long)))

(defun-simple reclaim-evaluation-long-function (evaluation-long)
  (reclaim-evaluation-long evaluation-long))

(defmacro copy-evaluation-long (evaluation-long)
  `(copy-managed-long ,evaluation-long))

(defmacro copy-managed-long-into-evaluation-long (managed-long)
  `(copy-managed-long ,managed-long))

(defun-simple copy-evaluation-long-from-phrase-long (phrase-long)
  (let ((new-evaluation-long nil))
    (with-temporary-creation copy-evaluation-long-from-phrase-long
      (setq new-evaluation-long
	    (make-evaluation-long (phrase-long-value phrase-long))))
    new-evaluation-long))

(defun make-evaluation-float-from-evaluation-long
    (evaluation-long &optional reclaim-argument?)
  (prog1 (make-evaluation-float
	   (coerce-to-gensym-float (evaluation-long-value evaluation-long)))
    (when reclaim-argument? (reclaim-evaluation-long evaluation-long))))

;;; The function DIV-LONG takes two EVALUATION-LONGs, modify the first one and also return it.

(defun-simple div-long (evaluation-long-1 evaluation-long-2)
  (let ((long-1 (evaluation-long-value evaluation-long-1))
	(long-2 (evaluation-long-value evaluation-long-2)))
    (declare (type #.(gensym-long-type) long-1 long-2))
    (mutate-evaluation-long-value
      evaluation-long-1
      (/l-raw long-1 long-2))
    evaluation-long-1))

;;; The macro `make-evaluation-quantity' takes a Common Lisp fixnum or
;;; gensym-float or long, and returns an evaluation-quantity encapsulating that value.

;;; The macro `reclaim-evaluation-quantity' takes an evaluation-quantity and
;;; reclaims it.

;;; The macro `copy-evaluation-quantity' takes an evaluation-quantity and
;;; returns a newly allocated evaluation-quantity which contains the same value.

;;; The function `evaluation-quantity-value' takes an evaluation-quantity and
;;; returns a gensym-float or fixnum which is the value stored in the
;;; evaluation-quantity.  Setf can be used to modify the value of an evaluation
;;; quantity.

;;; The macro `evaluation-quantity-value-as-float' takes an evaluation-quantity
;;; and returns its value, coerced to a gensym-float.

;;; The macro `evaluation-quantity-p' is used to test for evaluation quantities.

(declare-side-effect-free-function make-evaluation-quantity)

(defun-simple make-evaluation-quantity (lisp-number)
  (cond ((fixnump lisp-number)
         lisp-number)
        ((long-p lisp-number)
         (make-evaluation-long lisp-number))
        (t
         (make-evaluation-float lisp-number))))

(defun-simple reclaim-evaluation-quantity (evaluation-quantity)
  (cond ((evaluation-float-p evaluation-quantity)
         (reclaim-evaluation-float evaluation-quantity))
        ((evaluation-long-p evaluation-quantity)
         (reclaim-evaluation-long evaluation-quantity))
        (t
         (reclaim-evaluation-integer evaluation-quantity)))
  nil)

(def-substitution-macro copy-evaluation-quantity (evaluation-quantity)
  (cond ((evaluation-integer-p evaluation-quantity)
	 (copy-evaluation-integer evaluation-quantity))
	((evaluation-long-p evaluation-quantity)
	 (copy-evaluation-long evaluation-quantity))
	(t
	 (copy-evaluation-float evaluation-quantity))))

(declare-side-effect-free-function evaluation-quantity-value)

(defun-simple evaluation-quantity-value (evaluation-quantity)
  (cond
    ((evaluation-integer-p evaluation-quantity)
     (evaluation-integer-value evaluation-quantity))
    ((evaluation-long-p evaluation-quantity)
     (evaluation-long-value evaluation-quantity))
    (t
     (evaluation-float-value evaluation-quantity))))

(def-substitution-macro evaluation-quantity-value-as-float (evaluation-quantity)
  (cond ((evaluation-integer-p evaluation-quantity)
	 (coerce-fixnum-to-gensym-float
	   (evaluation-integer-value evaluation-quantity)))
	((evaluation-long-p evaluation-quantity)
	 (convert-g2longint-to-double
	   (evaluation-long-value evaluation-quantity)))
	(t
	 (evaluation-float-value evaluation-quantity))))

(def-substitution-macro evaluation-quantity-p (evaluation-quantity)
  (or (evaluation-integer-p evaluation-quantity)
      (evaluation-float-p evaluation-quantity)
      (evaluation-long-p evaluation-quantity)))




;;; The macro `def-evaluation-quantity-comparitor' takes as its argument an
;;; unquoted symbol naming a generic numeric comparitor.  This macro expands
;;; into a function defining a function EVALUATION-QUANTITY-<comp> which takes
;;; two evaluation quantities, performs that comparison, and returns T or NIL.
;;; Note that you cannot use (not (< x y)) to compute (>= x y) with this
;;; operators.  IEEE floating point standards require any comparison with a NaN
;;; to returns false.  If you negate the result of a comparison, and one of the
;;; arguments was a NaN, then you will receive an incorrect result.

(defmacro def-evaluation-quantity-comparitor (generic-comparitor)
  (let ((fixnum-comp (intern (format nil "~aF" generic-comparitor)))
	(float-comp (intern (format nil "~aE" generic-comparitor)))
        (long-comp (intern (format nil "~aL" generic-comparitor)))
	(name (intern (format nil "EVALUATION-QUANTITY-~a" generic-comparitor)))
	(long-value-1 (make-symbol "LONG-VALUE-1"))
	(long-value-2 (make-symbol "LONG-VALUE-2")))
    `(progn
       (declare-side-effect-free-function ,name)
       (defun-simple ,name (evaluation-quantity-1 evaluation-quantity-2)
	 (cond
           ((and (evaluation-integer-p evaluation-quantity-1)
		 (evaluation-integer-p evaluation-quantity-2))
	    (,fixnum-comp (evaluation-integer-value evaluation-quantity-1)
			  (evaluation-integer-value evaluation-quantity-2)))
	   ((or (evaluation-float-p evaluation-quantity-1)
		(evaluation-float-p evaluation-quantity-2))
	    (,float-comp (evaluation-quantity-value-as-float evaluation-quantity-1)
			 (evaluation-quantity-value-as-float evaluation-quantity-2)))
	   (t
	    (let ((evaluation-long-1
		   (if (evaluation-integer-p evaluation-quantity-1)
		       (make-evaluation-long evaluation-quantity-1)
		     evaluation-quantity-1))
		  (evaluation-long-2
		   (if (evaluation-integer-p evaluation-quantity-2)
		       (make-evaluation-long evaluation-quantity-2)
		     evaluation-quantity-2)))
	      (prog1
		  (with-temporary-creation name
		    (let ((,long-value-1 (evaluation-long-value evaluation-long-1))
			  (,long-value-2 (evaluation-long-value evaluation-long-2)))
		      (declare (type ,(gensym-long-type) ,long-value-1 ,long-value-2))
		      (,long-comp ,long-value-1 ,long-value-2)))
		(when (evaluation-integer-p evaluation-quantity-1)
		  (reclaim-evaluation-long evaluation-long-1))
		(when (evaluation-integer-p evaluation-quantity-2)
		  (reclaim-evaluation-long evaluation-long-2))))))))))




;;; The functions `evaluation-quantity-=', `evaluation-quantity-/=',
;;; `evaluation-quantity-<', `evaluation-quantity-<=', `evaluation-quantity->',
;;; and `evaluation-quantity->=' are comparitors of two evaluation-quantities.
;;; When only one of the arguments is a float, the other is coerced to float.
;;; These functions should be called within a TEMPORARY-AREA since this coercion
;;; creates a new gensym-float.

(def-evaluation-quantity-comparitor =)

(def-evaluation-quantity-comparitor /=)

(def-evaluation-quantity-comparitor <)

(def-evaluation-quantity-comparitor >=)

(def-evaluation-quantity-comparitor >)

(def-evaluation-quantity-comparitor <=)




;;; The macro `make-evaluation-symbol' takes a symbol and returns a newly
;;; allocated evaluation symbol.

;; Note that is is a noop right now.  In the (not too distant) future,
;; evaluation symbols will increment a reference count on user allocated
;; symbols, and then decrement that count on reclamation.  For now these will do
;; nothing.  These macros are provided at this point in time so that they can be
;; used while implementing the stack evaluator, so we'll have a head start on
;; the problem when we actually implement reclaimable symbols.  -jra & cpm
;; 2/27/91

;;; The macro `evaluation-symbol-symbol' takes an evaluation symbol and returns
;;; the symbol stored within it.

;;; The macro `copy-evaluation-symbol' takes an evaluation symbol and returns a
;;; newly allocated copy of that symbol. 

;;; The macro `reclaim-evaluation-symbol' takes an evaluation symbol and
;;; reclaims it.

;;; The macro `evaluation-symbol-p' tests whether an evaluation value is an
;;; evaluation-symbol.

(defmacro make-evaluation-symbol (symbol)
  symbol)

(defmacro evaluation-symbol-symbol (evaluation-symbol)
  evaluation-symbol)

(defmacro copy-evaluation-symbol (evaluation-symbol)
  evaluation-symbol)

(defmacro reclaim-evaluation-symbol (evaluation-symbol)
  `(progn ,evaluation-symbol nil))

(def-substitution-macro evaluation-symbol-p (evaluation-value)
  (and evaluation-value (symbolp evaluation-value)))

(defmacro reclaim-if-evaluation-symbol (thing)
  `(progn ,thing nil))



;;; Iteration states are evaluation values holding continuations for role
;;; service.  Iteration states are an eval cons whose cdr holds the
;;; symbol iteration-state, and whose car holds an eval cons containing
;;; a reference count in the car and either a continuation or NIL in the
;;; CDR.  Newly created iteration-states have a reference count of one.

;;; The macro `make-evaluation-iteration-state' takes a continuation (or NIL)
;;; and returns an evaluation-iteration-state.

;;; The function `reclaim-evaluation-iteration-state' takes an evaluation
;;; iteration state and reclaims it.  If it holds a "live" continuation, then
;;; that continuation is closed and reclaimed as well.  Note that
;;; reclaiming here is done by first decrementing the reference count.
;;; If the count has been decremented to zero, then the continuation (if
;;; any) is closed and the conses are reclaimed.

;;; The macro `copy-evaluation-iteration-state' takes an iteration state
;;; and returns a copy of it.  Note that the returned item is really the
;;; same iteration state as was passed in, but its reference count has
;;; been incremented.

;;; The macro `evaluation-iteration-state-continuation' takes an evaluation
;;; iteration state and returns the continuation stored within it.  This may be
;;; mutated using setf.

;;; The macro `evaluation-iteration-state-p' takes an evaluation value and
;;; returns whether it is an evaluation iteration state.

;;; The macro `cons-is-evaluation-iteration-state-p' takes a cons and returns
;;; whether or not it is an evaluation-iteration-state.

(defmacro make-evaluation-iteration-state (continuation)
  `(eval-cons (eval-cons 1 ,continuation) 'iteration-state))

(def-substitution-macro copy-evaluation-iteration-state
			(iteration-state)
  (incff (car-of-cons (car-of-cons iteration-state)))
  iteration-state)

;; Reclaim-evaluation-iteration-state has been moved to roles to pick up the
;; macro definition for close-role-value-server.  -jra 4/13/91

(declare-forward-reference reclaim-evaluation-iteration-state function)

(defmacro evaluation-iteration-state-continuation
	  (evaluation-continuation-state)
  `(cdr-of-cons (car-of-cons ,evaluation-continuation-state)))

(defmacro cons-is-evaluation-iteration-state-p (cons)
  `(eq (cdr-of-cons ,cons) 'iteration-state))

(defmacro cdr-of-evaluation-iteration-state-p (cdr)
  `(eq ,cdr 'iteration-state))

(def-substitution-macro evaluation-iteration-state-p (evaluation-value)
  (and (consp evaluation-value)
       (cons-is-evaluation-iteration-state-p evaluation-value)))





;;;; Evaluation Values for Some internal data types
;;;; that we might make public on some fine day in the future.

;;; The `unsigned-vector-16' is only used in remote procedure
;;; arguments and return values currently.  It serves the purpose
;;; of being a binary data type that suffers from none of the
;;; potential ambiguities of interpretation or unicode encoding
;;; hijinx.


(def-evaluation-value unsigned-vector-16 t)

(defvar test-removal-of-unsigned-vector-16 'unknown)

(defun-simple maybe-make-evaluation-unsigned-vector-16 (x)
  (when (eq test-removal-of-unsigned-vector-16 'unknown)
    (let ((string? (get-gensym-environment-variable "TEST_REMOVAL_OF_UNSIGNED_VECTOR_16")))
      (setq test-removal-of-unsigned-vector-16
	    (cond (string?
		   (reclaim-text-string string?)
		   t)
		  (t
		   nil)))))	  
  (if test-removal-of-unsigned-vector-16
      x
      (make-evaluation-unsigned-vector-16 x)))

(def-evaluation-value-reclaimer unsigned-vector-16
  (reclaim-text-string
    (evaluation-unsigned-vector-16-value unsigned-vector-16)))
  
(def-evaluation-value-copier unsigned-vector-16
  (maybe-make-evaluation-unsigned-vector-16
    (copy-wide-string
      (evaluation-unsigned-vector-16-value unsigned-vector-16))))

(def-evaluation-value-comparitor unsigned-vector-16
  (or (eq unsigned-vector-16-1 unsigned-vector-16-2)
      (string=w (evaluation-unsigned-vector-16-value unsigned-vector-16-1)
		(evaluation-unsigned-vector-16-value unsigned-vector-16-2))))

(def-evaluation-value-= unsigned-vector-16
  (or (eq unsigned-vector-16-1 unsigned-vector-16-2)
      (string=w
	(evaluation-unsigned-vector-16-value unsigned-vector-16-1)
	(evaluation-unsigned-vector-16-value unsigned-vector-16-2))))

(def-evaluation-value-writer unsigned-vector-16
  ;; maybe we should make this print as hex...
  (print-constant (evaluation-unsigned-vector-16-value unsigned-vector-16)
		  'text t))


;;;; Evaluation Enumerations






(def-evaluation-value member t)

(def-evaluation-value-reclaimer member
  (unless (or (fixnump member)
	      (symbolp member))
    (reclaim-evaluation-value member)))

(def-evaluation-value-copier member
  (if (or (fixnump member)
	  (symbolp member))
      member
      (copy-evaluation-value member)))

(def-evaluation-value-comparitor member
  (or (eq member-1 member-2)
      (evaluation-value-eql member-1 member-2)))

(def-evaluation-value-= member
  (or (eq member-1 member-2)
      (evaluation-value-= member-1 member-2)))


(def-evaluation-value-writer member
  (write-evaluation-value member))

(defun-simple member-type-specification-intersects-datum-type-p
    (member-type datum-type)
  (loop for elt in (cdr member-type)
	as elt-type = (evaluation-value-type elt)
	thereis
	(type-specifications-could-intersect-in-kb-p
	  elt-type datum-type)))

(defun-simple member-type-specifications-could-intersect-p
    (member-type-1 member-type-2)
  (loop for elt-1 in (cdr member-type-1)
	thereis
	(loop for elt-2 in (cdr member-type-2)
	      thereis (or (eq elt-1 elt-2)
			  (evaluation-value-eql elt-1 elt-2)))))

(defun-simple member-type-specification-subtype-of-symbolic-type-p
    (member-type datum-type)
  (loop for elt in (cdr member-type)
	as elt-type = (evaluation-value-type elt)
	always
	(or (eq elt-type datum-type)
	    (symbolic-type-specification-subtype-p elt-type datum-type))))

(defun-simple member-type-specification-subtype-p (member-type-1 member-type-2)
  (loop for elt-1 in (cdr member-type-1)
	always
	(loop for elt-2 in (cdr member-type-2)
	      thereis (or (eq elt-1 elt-2)
			  (evaluation-value-eql elt-1 elt-2)))))

(defun-simple member-type-specification-not-subtype-of-symbolic-type-p
    (member-type datum-type)
  (loop for elt in (cdr member-type)
	as elt-type = (evaluation-value-type elt)
	thereis
	(not (or (eq elt-type datum-type)
		 (symbolic-type-specification-subtype-p elt-type datum-type)))))


(defun-simple member-type-specification-not-subtype-p (member-type-1 member-type-2)
  (loop for elt-1 in (cdr member-type-1)
	thereis
	(loop for elt-2 in (cdr member-type-2)
	      never (or (eq elt-1 elt-2)
			(evaluation-value-eql elt-1 elt-2)))))





;;;; UUIDs and Item References

;; Note: the core of the UUID facility has been moved to the section "UUIDs for
;; G2 and Telewindows" in PLATFORMS in order to support UUID's in Telewindows,
;; for G2 7.0a2. (MHD 11/6/02)


;;;  Data Structures: 
;;;    A table of type uuid-block-hash named uuid-block-hash-table.
;;;    A structure named uuid-block, 
;;;      containing a table of item-references that is either a list or a vector.      
;;;    An evaluation value type named item-reference, having an value field that
;;;      is a vector with fields: reference-count, uuid-block, uuid-offset, referenced-item.
;;;  The API to item-references is:
;;;    get-item-reference-for-uuid                uuid -> item-reference
;;;    get-item-or-item-list-for-uuid             uuid -> item or nil
;;;    evaluation-item-reference-referenced-item  item-reference -> item or nil
;;;    evaluation-item-reference-uuid             item-reference -> uuid
;;;    uuid                                       item -> item-reference  (does not increment r.c.)
;;;    get-reference-to-item                      item -> item-reference  (increments reference count)
;;;    get-reference-to-item-if-item              item -> item-reference; x -> x for everything else.
;;;    item-uuid                                  item -> uuid

(def-structure (uuid-block
		 (:constructor make-uuid-block
			       (uuid-block-uuid uuid-block-item-reference-table))
		 (:reclaimer reclaim-uuid-block-internal)
		 #+development
		 (:print-function print-uuid-block))
  (uuid-block-reference-count 1)
  (uuid-block-uuid nil) ; don't reclaim here.  also the hash table key.
  (uuid-block-item-reference-table nil :reclaimer reclaim-uuid-block-item-reference-table)
  ;;(corresponding-icp-object-map-for-uuid-block nil) ; for later
  )

(defun-simple copy-uuid-block (uuid-block)
  (incff (uuid-block-reference-count uuid-block))
  uuid-block)

(defun-void reclaim-uuid-block-item-reference-table (table)
  (cond ((consp table)
	 (reclaim-eval-list table))
	((simple-vector-p table)
	 (reclaim-managed-simple-vector table))))

#+development
(defun-void print-uuid-block (uuid-block stream depth)
  (declare (ignore depth))
  (printing-random-object (uuid-block stream)
    (let ((string (twith-output-to-gensym-string
		    (twrite-uuid-printed-representation-as-string
		      (uuid-block-uuid uuid-block)))))
      (format stream "UUID-BLOCK ~a" string)
      (reclaim-gensym-string string))))

(def-skip-list-or-binary-tree uuid-block-hash
    :constructor make-uuid-block-hash
    :reclaimer reclaim-uuid-block-hash
    :key-comparitor uuid=
    :hash-function sxhashw		; use sxhashW, not sxhash, for wide strings
    :key-reclaimer uuid-block-hash-key-reclaimer
    :entry-reclaimer uuid-block-hash-entry-reclaimer
    :set-if-no-entry-given-hash set-string-value-if-no-entry)

(defun-simple make-uuid-block-hash-function ()
  (make-uuid-block-hash))

(defun-void reclaim-uuid-block-hash-table (table)
  (reclaim-uuid-block-hash table))

(defun-void uuid-block-hash-key-reclaimer (uuid)
  (reclaim-wide-string uuid))

(defun-void uuid-block-hash-entry-reclaimer (uuid-block)
  (reclaim-uuid-block-internal uuid-block))

(def-kb-specific-variable uuid-block-hash-table types
  (:funcall make-uuid-block-hash-function) nil reclaim-uuid-block-hash-table)

(defun-void reclaim-uuid-block (uuid-block)
  (decff (uuid-block-reference-count uuid-block))
  (when (=f (uuid-block-reference-count uuid-block) 0)
    (delete-uuid-block-hash (uuid-block-uuid uuid-block) uuid-block-hash-table)))

(def-kb-specific-variable uuid-hash-block-table-for-merge-kb types
  (:funcall make-uuid-block-hash-function) nil reclaim-uuid-block-hash-table)

(def-evaluation-value item-reference t)

(defmacro evaluation-item-reference-vector-reference-count (held-vector)
  `(svref ,held-vector 0))

(defmacro evaluation-item-reference-vector-uuid-block (held-vector)
  `(svref ,held-vector 1))

(defmacro evaluation-item-reference-vector-uuid-offset (held-vector)
  `(svref ,held-vector 2))

(defmacro evaluation-item-reference-vector-referenced-item (held-vector)
  `(svref ,held-vector 3))

(defmacro evaluation-item-reference-reference-count (item-reference)
  `(evaluation-item-reference-vector-reference-count
     (evaluation-item-reference-value ,item-reference)))

(defmacro evaluation-item-reference-referenced-item (item-reference)
  `(evaluation-item-reference-vector-referenced-item
     (evaluation-item-reference-value ,item-reference)))

(defmacro get-evaluation-item-reference-vector-uuid-block (held-vector)
  (let ((vector (make-symbol "VECTOR")))
    `(let ((,vector ,held-vector))
       (unless (svref ,vector 1)
	 (when (evaluation-item-reference-vector-referenced-item ,vector)
	   (get-block-and-offset-for-item-reference ,vector)))	      
       (svref ,vector 1))))

(defmacro ensure-uuid-for-item-reference (item-reference)
  `(get-evaluation-item-reference-vector-uuid-block
     (evaluation-item-reference-value ,item-reference)))

;; This function should be called only by get-item-reference-for-uuid.
;; but it is not so, it is also called from get-item-reference-for-new-uuid -- budden73 2016-09-29
(defun-simple allocate-evaluation-item-reference (uuid-block uuid-offset referenced-item)
  (let* ((held-vector (allocate-managed-simple-vector 4))
	 (new-item-reference (make-evaluation-item-reference held-vector)))
    (setf (evaluation-item-reference-vector-reference-count held-vector) 0)
    (setf (evaluation-item-reference-vector-uuid-block held-vector)
	  (when uuid-block (copy-uuid-block uuid-block))) ; increments reference count
    (setf (evaluation-item-reference-vector-uuid-offset held-vector) uuid-offset)
    (setf (evaluation-item-reference-vector-referenced-item held-vector)
	  referenced-item)
    new-item-reference))

(defmacro get-reference-to-item-if-item (item-or-value)
  (let ((var (make-symbol "ITEM-OR-VALUE")))
    `(let ((,var ,item-or-value))
       (if (framep ,var)
	   (get-reference-to-item ,var)
	   ,var))))

(defun get-reference-to-item-if-item-function (item-or-value)
  (get-reference-to-item-if-item item-or-value))

(defmacro get-item-if-item-reference (item-or-value)
  (let ((var (make-symbol "ITEM-OR-VALUE")))
    `(let ((,var ,item-or-value))
       (if (evaluation-item-reference-p ,var)
	   (evaluation-item-reference-referenced-item ,var)
	   ,var))))

(defconstant uuid-block-table-size 256)
(defconstant item-reference-table-list-length-limit 10)
(defconstant uuid-string-length 8)

(defvar lazy-assignment-of-uuids t)

(defun-simple get-item-reference-for-new-uuid ()
  (if lazy-assignment-of-uuids
      (let ((item-reference (allocate-evaluation-item-reference nil nil nil)))
	(atomic-incff (evaluation-item-reference-reference-count item-reference))
	item-reference)
      (let ((uuid (make-uuid)))
	(prog1 (get-item-reference-for-uuid uuid t t)
	  (reclaim-wide-string uuid)))))

(defun-void get-block-and-offset-for-item-reference (vector)
  (let ((uuid (make-uuid)))
    (prog1 (get-item-reference-for-uuid uuid vector nil)
      (reclaim-wide-string uuid))))

;;; The function `valid-uuid-p' checks that a string can be
;;; converted to a UUID (or may be a UUID already). UUIDs
;;; are also marked as binary at certain times, but not
;;; consistently.

(defun-simple valid-uuid-p (str)
  (and 
    (wide-string-p str)
    (=f (wide-string-length str) uuid-string-length)))

(defun-simple get-item-reference-for-uuid (uuid create-p need-copy-p)
  (when (evaluation-item-reference-p uuid)
    (return-from get-item-reference-for-uuid uuid))
  (unless (valid-uuid-p uuid)
    #+development
    (when (or create-p need-copy-p)
      (error "~S is not a uuid" uuid))
    (return-from get-item-reference-for-uuid nil))
  (let* ((uuid-block-key uuid)
	 (uuid-least-16-bits (wide-character-code (charw uuid 0)))
	 (uuid-offset (logandf uuid-least-16-bits uuid-offset-mask))
	 (uuid-block-least-16-bits (logandc2f uuid-least-16-bits uuid-offset-mask))
	 (uuid-block (progn
		       (setf (charw uuid-block-key 0) (code-wide-character uuid-block-least-16-bits))
		       (get-uuid-block-hash uuid-block-key uuid-block-hash-table)))
	 (item-reference-table (when uuid-block
				 (uuid-block-item-reference-table uuid-block)))
	 (item-reference? nil))
    (cond ((null item-reference-table)
	   nil)
	  ((consp item-reference-table)
	   (loop for table-item-reference in item-reference-table
		 for held-vector = (evaluation-item-reference-value table-item-reference)
		 when (=f uuid-offset
			  (evaluation-item-reference-vector-uuid-offset held-vector))
		   do (setq item-reference? table-item-reference)
		      (return nil)))
	  ((simple-vector-p item-reference-table)
	   (setq item-reference? (svref item-reference-table uuid-offset))))
    (when (and (null item-reference?) create-p)
      (setq item-reference?
	    (cond ((vectorp create-p)
		   (setf (evaluation-item-reference-vector-uuid-block create-p)
			 (when uuid-block (copy-uuid-block uuid-block)))
		   (setf (evaluation-item-reference-vector-uuid-offset create-p) uuid-offset)
		   (get-reference-to-item-no-copy
		     (evaluation-item-reference-vector-referenced-item create-p)))
		  (t
		   (allocate-evaluation-item-reference uuid-block uuid-offset nil))))
      (cond ((null item-reference-table)
	     (cond (uuid-block
		    (setf (uuid-block-item-reference-table uuid-block)
			  (eval-list item-reference?)))
		   (t
		    (let ((actual-uuid-block-key (copy-wide-string uuid-block-key)))
		      (setq uuid-block (make-uuid-block actual-uuid-block-key
							(eval-list item-reference?)))
		      (setf (evaluation-item-reference-vector-uuid-block
			      (evaluation-item-reference-value item-reference?)) 
			    uuid-block)
		      (setf (get-uuid-block-hash actual-uuid-block-key uuid-block-hash-table)
			    uuid-block)))))
	    ((consp item-reference-table)
	     (cond ((<f (length item-reference-table) item-reference-table-list-length-limit)
		    (eval-push item-reference? (uuid-block-item-reference-table uuid-block)))
		   (t
		    (let ((table (allocate-managed-simple-vector uuid-block-table-size)))
		      (loop for index from 0 below uuid-block-table-size
			    do (setf (svref table index) nil))
		      (loop for table-item-reference in item-reference-table
			    for held-vector = (evaluation-item-reference-value table-item-reference)
			    for offset = (evaluation-item-reference-vector-uuid-offset held-vector)
			    do (setf (svref table offset) table-item-reference))
		      (reclaim-eval-list item-reference-table)
		      (setf (svref table uuid-offset) item-reference?)
		      (setf (uuid-block-item-reference-table uuid-block) table)))))
	    ((simple-vector-p item-reference-table)
	     (setf (svref item-reference-table uuid-offset) item-reference?))))
    (setf (charw uuid 0) (code-wide-character uuid-least-16-bits))
    (when (and item-reference? need-copy-p)
      (atomic-incff (evaluation-item-reference-reference-count item-reference?)))
    item-reference?))

(defun-simple evaluation-item-reference-uuid (item-reference)
  (let* ((held-vector (evaluation-item-reference-value item-reference))
	 (uuid-block (or (get-evaluation-item-reference-vector-uuid-block held-vector)
			 (return-from evaluation-item-reference-uuid nil)))
	 (uuid-offset (evaluation-item-reference-vector-uuid-offset held-vector))
	 (uuid-string (copy-wide-string (uuid-block-uuid uuid-block))))
    (setf (charw uuid-string 0)
	  (code-wide-character (logiorf (wide-character-code (charw uuid-string 0))
					uuid-offset)))
    uuid-string))

(defun-simple hash-item-reference (item-reference)
  (let* ((held-vector (evaluation-item-reference-value item-reference))
	 (uuid-block? (get-evaluation-item-reference-vector-uuid-block held-vector))
	 (uuid-offset? (evaluation-item-reference-vector-uuid-offset held-vector))
	 (uuid-string? (if uuid-block? (uuid-block-uuid uuid-block?))))
    (cond ((and uuid-offset? uuid-string?)
	   (+f uuid-offset? (ashf (sxhashw uuid-string?) -1))) ; ashf to avoid fixnum overflow
	  (t
	   ;; This can only happen if the referenced item was deleted before we
	   ;; ever tried to hash its reference. Since we never hashed it, it is
	   ;; not in a hash table, so the hash code returned should not matter.
	   ;; In any case, the way this function is used by the native-icons
	   ;; facility we should never encounter this cerror. -fmw, 12/1/05
	   #+development (cerror "Go on" "Null uuid-offset or block: ~s ~s"
				 uuid-offset? uuid-string?)
	   0))))

(def-evaluation-value-reclaimer item-reference
  (let* ((held-vector (evaluation-item-reference-value item-reference))
	 (ref-count (evaluation-item-reference-vector-reference-count held-vector)))
    (declare (type fixnum ref-count))
    (cond ((=f ref-count 1)
	   (let* ((uuid-block (evaluation-item-reference-vector-uuid-block held-vector))
		  (item-reference-table (when uuid-block
					  (uuid-block-item-reference-table uuid-block)))
		  (uuid-offset (evaluation-item-reference-vector-uuid-offset held-vector)))
	     (cond ((consp item-reference-table)
		    (setf (uuid-block-item-reference-table uuid-block)
			  (delete-eval-element item-reference item-reference-table)))
		   ((simple-vector-p item-reference-table)
		    (setf (svref item-reference-table uuid-offset) nil)))
	     (when uuid-block
	       (reclaim-uuid-block uuid-block) ;decrements its reference count
	       (setf (evaluation-item-reference-vector-uuid-block held-vector) nil))) ; for debugging
	   (reclaim-managed-simple-vector held-vector))
	  ((<f ref-count 1)
	   (error "Item-Reference reference count zero or below in ~a." item-reference))
	  (t
	   (setf (evaluation-item-reference-vector-reference-count held-vector)
		 (1-f ref-count))
	   (setq item-reference nil)))))

(defun reclaim-if-evaluation-item-reference (item-reference?)
  (when (evaluation-item-reference-p item-reference?)
    (reclaim-evaluation-item-reference item-reference?)))

(def-evaluation-value-copier item-reference
  (let ((held-vector (evaluation-item-reference-value item-reference)))
    (atomic-incff (evaluation-item-reference-vector-reference-count held-vector))
    item-reference))

(def-evaluation-value-comparitor item-reference
  (eq item-reference-1 item-reference-2))

(def-evaluation-value-= item-reference
  (eq item-reference-1 item-reference-2))

(def-evaluation-value-writer item-reference
  (tformat "item-reference (")		; space before open paren (MHD 2/26/96)
  (let ((uuid? (evaluation-item-reference-uuid item-reference)))
    (when uuid?
      (twrite-uuid-printed-representation-as-string uuid?)
      (reclaim-wide-string uuid?)))
  (tformat ")"))

(defun-simple item-reference-type-specification-p (thing)
  (and (consp thing)
       (eq (car-of-cons thing) 'item-reference)))

(defun-simple get-item-or-item-list-for-uuid (uuid)
  (let ((item-reference? (get-item-reference-for-uuid uuid nil nil)))
    (when item-reference?
      (evaluation-item-reference-referenced-item item-reference?))))

(defun the-item-having-uuid (class? denotation)
  (let* ((item-or-item-list (if (valid-uuid-p denotation)
				(get-item-or-item-list-for-uuid denotation)
				(get-instance-from-uuid-representation denotation)))
	 (item? (if (consp item-or-item-list)
		    (car-of-cons item-or-item-list)
		    item-or-item-list)))
    (when (and item?
	       (or (null class?)
		   (if (eq class? 'item)
		       (frame-of-class-p item? 'item)
		       (frame-of-class-p item? class?))))
      item?)))

(defvar collecting-denotation-errors-p nil)
(defvar denotation-error-list nil)

(defun find-frame-for-denotation (denotation &optional class)
  (or (cond ((framep denotation)
	     denotation)
	    ((symbolp denotation)
	     (get-instance-with-name-if-any class denotation))
	    ((wide-string-p denotation)
	     (the-item-having-uuid 'item denotation))
	    ((and (consp denotation)
		  (eq (car-of-cons denotation) 'the)
		  (symbolp (second denotation)))
	     (let ((sub-frame? (find-frame-for-denotation (third denotation) nil)))
	       (when sub-frame?
		 (frame-or-evaluation-value-user-attribute-value
		   sub-frame? (second denotation) nil))))
	    ((and (consp denotation)
		  (eq (car-of-cons denotation) 'the-item-having-uuid)
		  (wide-string-p (third denotation)))
	     (the-item-having-uuid (second denotation) (third denotation)))
	    (t
	     nil))
      (when collecting-denotation-errors-p
	(phrase-push denotation denotation-error-list)
	nil)))

(def-gensym-c-function c-uuid-eq (:fixnum-int "g2ext_uuid_eq")
  ((:wide-string uuid1)
   (:wide-string uuid2)))

(defun-simple uuid= (uuid1 uuid2)
  (if (=f (c-uuid-eq uuid1 uuid2) 0) t nil))

(defmacro compare-wide-string-elements (string1 string2 &rest index-list)
  `(block compare
     (let ((c1 0) (c2 0))
       (declare (type fixnum c1 c2))
       ,@(loop for index in index-list
	       collect `(progn
			  (setq c1 (wide-character-code (charw ,string1 ,index)))
			  (setq c2 (wide-character-code (charw ,string2 ,index)))
			  (unless (=f c1 c2)
			    (return-from compare (<f c1 c2)))))
     nil)))

; This compare sorts uuids by time first, then by everything else.		       
(defun uuid< (uuid1 uuid2)
  (compare-wide-string-elements uuid1 uuid2
				3 2 1 0 4 5 6 7))

(defun allocate-new-nonce-internal ()
  (let ((always-use-current-time-for-uuid t))
    (make-uuid)))

;;; A `UUID representation string' is a text string consisting of 32 hex digits.
;;; The 8 sets of 4 hex digits, each set regarded as an integer in hex notation,
;;; correspond to the character codes of the 8 characters of a corresponding
;;; UUID string, the internal representation.
(def-concept uuid-representation-string)

;;; A `compilable UUID representation string' is the same, but any number of
;;; (horizontal) space characters are permitted before, after, or in the middle
;;; of the string.  (This is to reduce hassle for users entering these UUIDs in
;;; editors.)
(def-concept compilable-uuid-representation-string)

;;; `Check-and-trim-uuid-printed-represention' copies the hex digits only from
;;; text-string to the result string, checking for problems along the way.  It
;;; allows hex digits and horizontal spaces, but nothing else.  If there is
;;; anything else, or not enough hex digits to make up a valid result, the
;;; argument text-string is not considered a compilable uuid representation
;;; string, and this returns two values: nil and a freshly created problem
;;; report text string.  If there are no problems, this returns a freshly
;;; created UUID representation string.  This does not under any circumstances
;;; reclaim or mutate its argument text-string.

;;; `Convert-trimmed-uuid-representation-to-internal' converts a UUID printed
;;; representation string to internal form.  Its argument is a text string that
;;; consists of just 32 (= uuid-representation-string-length) characters
;;; corresponding to Hexadecimal digits.  It creates a new wide wide string, of
;;; length 8 (= uuid-string-length), whose elements corresponding to each set of
;;; 4 hex digits regarded as an integer in hex notation.  The argument
;;; uuid-representation-string is reclaimed as a text string.  The resulting
;;; wide string is freshly conses.  Note that it must be noted as a phrase text
;;; string in order to be returned as a parse result, its intended use, by the
;;; caller.

(defun convert-uuid-representation-to-internal (representation-string)
  (convert-binary-string-representation-to-internal
   representation-string uuid-string-length "UUID"))

(defun convert-binary-string-representation-to-internal
    (representation-string required-string-length? use-for-warnings)
  (let* ((hex-digit-count
	  (loop for i from 0 below (lengthw representation-string)
		as character = (charw representation-string i)
		as value-of-hex-digit? = (digit-char-pw character 16)
		when (and (null value-of-hex-digit?)
			  (not (horizontal-space-p character)))
		  do (return-from convert-binary-string-representation-to-internal
		       (values nil
			       (tformat-text-string "illegal character (~c) in a ~a string"
						    character
						    use-for-warnings)))
		when value-of-hex-digit?
		  count t))
	 (string-length (right-shiftf hex-digit-count 2))
	 (wide-string (cond ((and required-string-length?
				  (not (and (=f required-string-length? string-length)
					    (=f 0 (logandf #x3 hex-digit-count)))))
			     (return-from convert-binary-string-representation-to-internal
			       (values nil
				       (tformat-text-string
					"a ~a string must be ~d hex digits, but this has ~d"
					use-for-warnings
					(left-shiftf required-string-length? 2)
					string-length))))
			    ((not (=f 0 (logandf #x3 hex-digit-count)))
			     (return-from convert-binary-string-representation-to-internal
			       (values nil
				       (tformat-text-string
					"a ~a string must have a total number of hex digits that is a multiple of four"
					use-for-warnings))))
			    (t
			     (mark-wide-string-as-binary (make-wide-string string-length))))))
    (loop for j from 0 below (lengthw wide-string)
	  do (setf (charw wide-string j) (code-wide-character 0)))
    (loop with hex-digit-position = 12
	  with wide-string-position = 0
	  for i from 0 below (lengthw representation-string)
	  as character = (charw representation-string i)
	  as value-of-hex-digit? = (digit-char-pw character 16)
	  when value-of-hex-digit?
	    do (setf (charw wide-string wide-string-position)
		     (code-wide-character
		      (+f (wide-character-code (charw wide-string wide-string-position))
			  (left-shiftf value-of-hex-digit? hex-digit-position))))
	       (if (=f hex-digit-position 0)
		   (progn
		     (setq hex-digit-position 12)
		     (incff wide-string-position))
		   (decff hex-digit-position 4)))
    wide-string))

;;; `Twrite-uuid-representation-as-string' writes the printed
;;; representation of a UUID as a string, i.e., including the quotes ("").
;;; The hex digits are printed in lowercase.  This is because lowercase
;;; letters are more easily readable and take up less space in most fonts.
;;;
;;; `Twrite-uuid-printed-representation' does the same, but without the quotes.
;;; UUID is assumed be valid, i.e., a wide string of length 8 with any contents,
;;; OR, in as of G2 6.0, the UUID may also be an evaluation item reference (and
;;; if so, calling this function will create a UUID as a side effect).

(defun-void twrite-uuid-printed-representation-as-string (uuid)
  (let ((string-to-reclaim
	 (when (evaluation-item-reference-p uuid)
	   (setq uuid (evaluation-item-reference-uuid uuid)))))
    (when uuid
      #+development
      (unless (=f (wide-string-length uuid) uuid-string-length)
	(tformat "[bad uuid]"))
      (twrite-character #.%\")
      (twrite-uuid-printed-representation uuid)
      (twrite-character #.%\")
      (when string-to-reclaim
	(reclaim-wide-string string-to-reclaim)))))


;;;; Eq item hash tables

;;; These are hash tables that are like an
;;; eq-hash-table (and are implemented in terms of one), but
;;; stores item-references as keys and/or values when given
;;; items to store. This allows items stored in these tables
;;; to be deleted cleanly. If an item that is a value in an
;;; eq-item-hash-table is deleted, without being deleted from the table first,
;;; then a gethash for the corresponding key will return nil.
;;;
;;; Note that you should still delete items from an eq item hash table
;;; before deleting them if the hash table will be long-lived, since
;;; not doing so will leak memory (the item-reference) which will
;;; be reclaimed when the hash table is deleted.

;;; Eq item hash tables do not support key-reclaimers and value-reclaimers.

(defun eq-item-hash-table-reclaimer (item-reference?)
  (when (evaluation-item-reference-p item-reference?)
    (reclaim-evaluation-item-reference item-reference?)))

(defun make-eq-item-hash-table (size)
  (make-eq-hash-table size
		      #'eq-item-hash-table-reclaimer
		      #'eq-item-hash-table-reclaimer))

(defun reclaim-eq-item-hash-table (table)
  (reclaim-eq-hash-table table))

(defun eq-item-gethash (table key-object default-value?)
  (let ((result-reference (eq-gethash table
				      (if (framep key-object)
					  (uuid-function key-object)
					  key-object)
				      default-value?)))
    (if (evaluation-item-reference-p result-reference)
	(let ((item
		(evaluation-item-reference-referenced-item result-reference)))
	  (or item
	      (progn
		(eq-remhash table key-object)
		default-value?)))
	result-reference)))

;;; The tricky thing here is that if key-object is an item,
;;; and we are adding a new key to the hash-table, then we have
;;; to increase the reference count for the item-reference.
;;; But if we are changing the value for an existing key-object,
;;; we should not increase the reference count.
(defvar-of-special-global bogus-value-for-default (cons nil nil))

(defun eq-item-puthash (table key-object value-object)
  (let* ((key-is-item-p (framep key-object))
	 (internal-key (get-reference-to-item-if-item key-object))
	 (key-is-old-item
	   (and key-is-item-p
		(neq (eq-gethash table key-object bogus-value-for-default)
		     bogus-value-for-default))))
    (eq-puthash table
		internal-key
		(get-reference-to-item-if-item value-object))
    (when key-is-old-item
      (reclaim-if-evaluation-value-function internal-key))))

(defsetf eq-item-gethash eq-item-puthash)

(defun-simple eq-item-remhash (table key-object)
  (eq-remhash table (get-reference-to-item-if-item key-object)))



;;;; Evaluation Sequences




;;; The type `sequence' is an evaluation value that is exposed to users as a
;;; subtype of value.  This type can hold any ordered list of item-or-value
;;; contents.  This evaluation value keeps a reference count as element zero,
;;; and the remaining elements are the contents of the sequence.

;;; In order to avoid circular structures, mutations to these structures must a)
;;; always allocate a new sequence to store the result, or b) allocate a new
;;; sequence to store the mutation whenever the new element being mutated in
;;; contains a pointer within its recursive descent to the sequence being
;;; mutated.  At the moment, we will go with option a).  -jra 4/8/96

(def-evaluation-value sequence t)

(defmacro evaluation-sequence-vector-reference-count (held-vector)
  `(managed-svref ,held-vector 0))

(defmacro evaluation-sequence-first-element-index ()
  1)

(defun allocate-evaluation-sequence (eval-list-of-contents)
  (let* ((length (length eval-list-of-contents))
	 (held-vector (allocate-managed-array
			(+f length (evaluation-sequence-first-element-index))))
	 (new-sequence (make-evaluation-sequence held-vector)))
    (declare (type fixnum length))
    (setf (evaluation-sequence-vector-reference-count held-vector) 1)
    (loop for index from (evaluation-sequence-first-element-index)
	  for new-value in eval-list-of-contents
	  do
      (setf (managed-svref held-vector index) (get-reference-to-item-if-item new-value)))
    (reclaim-eval-list eval-list-of-contents)
    new-sequence))




;;; The macro `evaluation-sequence-length' returns the number of elements in the
;;; given evaluation-sequence.

(defmacro evaluation-sequence-length (evaluation-sequence)
  `(-f (managed-array-length (evaluation-sequence-value ,evaluation-sequence))
       (evaluation-sequence-first-element-index)))




;;; The macro `allocate-new-evaluation-sequence-copy' returns a newly consed
;;; copy of the given sequence, with all elements copied into the new sequence
;;; (paying appropriate attention to evaluation-copies of the elements).

;;; Note however that these are shallow copies. That is, if
;;; allocate-new-evaluation-sequence-copy is called on a sequence of sequences,
;;; the internal sequences are not themselves copied; instead, they
;;; just get their reference count incremented. The callers of this should
;;; be checked to confirm that this is really the desired behavior.
;;; -alatto, 3/29/05
(def-substitution-macro allocate-new-evaluation-sequence-copy (sequence)
  (let* ((length (evaluation-sequence-length sequence))
	 (new-sequence (allocate-empty-evaluation-sequence length)))
    (copy-evaluation-sequence-elements
      sequence 0 length new-sequence 0)
    new-sequence))

(def-substitution-macro allocate-new-evaluation-sequence-deep-copy (sequence)
  (let* ((length (evaluation-sequence-length sequence))
	 (new-sequence (allocate-empty-evaluation-sequence length)))
    (deep-copy-evaluation-sequence-elements
      sequence 0 length new-sequence 0)
    new-sequence))




;;; The macro `evaluation-sequence-ref' is sole property of the evaluators.  Use
;;; in other parts of the code will be punished severely!!!

(defmacro evaluation-sequence-ref (evaluation-sequence index)
  `(managed-svref (evaluation-sequence-value ,evaluation-sequence)
		  (+f ,index (evaluation-sequence-first-element-index))))

(defmacro set-evaluation-sequence-ref (evaluation-sequence index new-value)
  `(setf (managed-svref (evaluation-sequence-value ,evaluation-sequence)
			(+f ,index (evaluation-sequence-first-element-index)))
	 (get-reference-to-item-if-item ,new-value)))

(defsetf evaluation-sequence-ref set-evaluation-sequence-ref)



;;; The macro `mutable-evaluation-sequence-p' takes an evaluation-sequence and
;;; returns whether or not it may be directly modified.  This is only true when
;;; the reference count is one.

(defmacro mutable-evaluation-sequence-p (sequence)
  `(=f (evaluation-sequence-vector-reference-count
	 (evaluation-sequence-value ,sequence))
       1))



;;; The function `obtain-mutable-evaluation-sequence-copy' takes and reclaims
;;; the given sequence and returns a copy of that sequence that is no longer
;;; shared and so may be mutated.

(defun-simple obtain-mutable-evaluation-sequence-copy (sequence)
  (cond ((mutable-evaluation-sequence-p sequence)
	 sequence)
	(t
	 (let ((new-sequence (allocate-new-evaluation-sequence-copy sequence)))
	   (reclaim-evaluation-sequence sequence)
	   new-sequence))))



(defmacro changing-elements-of-evaluation-sequence ((variable sequence-form) &body new-value-forms)
  (let ((sequence (make-symbol "SEQUENCE"))
	(held-vector (make-symbol "HELD_VECTOR"))
	(length (make-symbol "SEQUENCE-LENGTH"))
	(index (make-symbol "INDEX"))
	(elt (make-symbol "ELT"))
	(validated-elt variable))
    `(loop with ,sequence = (obtain-mutable-evaluation-sequence-copy ,sequence-form)
	   with ,held-vector = (evaluation-sequence-value ,sequence)
	   with ,length = (managed-array-length ,held-vector)
	   for ,index fixnum from (evaluation-sequence-first-element-index)
		      below ,length
	   for ,elt = (managed-svref ,held-vector ,index)
	   for ,validated-elt = (validate-item-or-evaluation-value ,elt nil nil)
	   do
       (setf (managed-svref ,held-vector ,index)
	     (when ,validated-elt
	       (get-reference-to-item-if-item
		 (progn ,@new-value-forms))))
	   finally
	     (return ,sequence))))


	     



#+development
(defun sequence-copy-test (sequence)
  (let* ((length (evaluation-sequence-length sequence))
	 (new-sequence (allocate-empty-evaluation-sequence length)))
    (copy-evaluation-sequence-elements sequence 0 length
				       new-sequence 0)
    new-sequence))

(defun-simple allocate-new-evaluation-sequence-from-simple-vector
    (simple-vector first-element-index count)
  (declare (simple-vector simple-vector)
	   (fixnum first-element-index count))
  (let ((held-vector (allocate-managed-array
		       (+f count (evaluation-sequence-first-element-index)))))
    (setf (evaluation-sequence-vector-reference-count held-vector) 1)
    (loop for source-index from first-element-index
	  for n from 0 below count
	  for dest-index from (evaluation-sequence-first-element-index)
	  do (setf (managed-svref held-vector dest-index)
		   (get-reference-to-item-if-item (svref simple-vector source-index))))
    (make-evaluation-sequence held-vector)))

(def-evaluation-value-reclaimer sequence
  (let* ((held-array (evaluation-sequence-value sequence))
	 (ref-count (evaluation-sequence-vector-reference-count held-array)))
    (declare (type fixnum ref-count))
    (cond ((=f ref-count 1)
	   (loop for index from (evaluation-sequence-first-element-index)
			   below (managed-array-length held-array)
		 do (reclaim-if-evaluation-value-function (managed-svref held-array index))
		 finally (reclaim-managed-array held-array)))
	  ((<f ref-count 1)
	   (error "Sequence reference count zero or below in ~a." sequence))
	  (t
	   (setf (evaluation-sequence-vector-reference-count held-array)
		 (-f ref-count 1))))))

(def-evaluation-value-copier sequence
  (let ((held-vector (evaluation-sequence-value sequence)))
    (incff (evaluation-sequence-vector-reference-count held-vector))
    (make-evaluation-sequence held-vector)))

(def-evaluation-value-deep-copier sequence
  (allocate-new-evaluation-sequence-deep-copy sequence))

;;; `evaluation-sequence-elements-of' - used in loop-path defined in UTILITIES2.  See my
;;; comments of this date there and in FRAMES2A for an explanation.  -jv, 12/19/03

(defun-for-macro evaluation-sequence-elements-of
    (path-name variable data-type prep-phrases inclusive? allowed-preps data)
  (declare (ignore data allowed-preps))
  (when (null prep-phrases)
    (error "OF is missing in ~S iteration path of ~S."
           path-name variable))
  (when inclusive?
    (error "Inclusive stepping is not supported in ~s path of ~s ~
            (prep-phrase = ~s)"
           path-name variable prep-phrases))
  (let* ((sequence (gensym))
	 (held-vector (make-symbol "HELD-VECTOR"))
         (next-index (make-symbol "NEXT-INDEX"))
	 (elt (make-symbol "ELT"))
	 (validated-elt (make-symbol "VALIDATED-ELT"))
         (length (make-symbol "LENGTH"))
         (init-bindings
           `((,sequence ,(cadar prep-phrases))
	     (,held-vector nil)
             (,next-index (evaluation-sequence-first-element-index)
			  fixnum)
             (,length 0 fixnum)
             (,variable nil ,@(if data-type (list data-type) nil))))
         (prologue-forms
           `(#+development
	     (unless (evaluation-sequence-p ,sequence)
	       (error "Can't iterate over the evaluation-sequence-elements of ~a, it's not a sequence."
		      ,sequence))
	     (setq ,held-vector (evaluation-sequence-value ,sequence))
	     (setq ,length (managed-array-length ,held-vector))))
	 (pre-step-tests `(>=f ,next-index ,length))
	 (steppings
	   `(,variable
	       (let* ((,elt (managed-svref ,held-vector
					   ,next-index))
		      (,validated-elt (if ,elt
					  (validate-item-or-evaluation-value ,elt nil nil)
					  nil)))
		 (setq ,next-index (+f ,next-index 1))
		 ,validated-elt)))
	 (post-step-tests nil)
	 (post-step-settings nil))
    `(,init-bindings
	,prologue-forms
	,pre-step-tests
	,steppings
	,post-step-tests
	,post-step-settings)))




;;; The system-procedure `g2-get-position-of-element-in-sequence' returns the
;;; index of the first occurrence of element in the sequence if there is one;
;;; otherwise it returns -1.

(defun-for-system-procedure g2-get-position-of-element-in-sequence (element sequence)
  (declare (keeps-g2-local-variables-valid t))
  (let ((index-to-return? 
	  (loop for item-or-value being each evaluation-sequence-element of sequence
		for index = 0 then (+f index 1)
		do
	    (when (item-or-value-eql-p item-or-value element)
	      (return index)))))
    (reclaim-if-evaluation-value-function element)
    (reclaim-evaluation-sequence sequence)
    (make-evaluation-integer (if index-to-return? index-to-return? -1))))




;;; The function `evaluation-sequence-empty-p' returns whether the evaluation-sequence
;;; has no elements.

(defmacro evaluation-sequence-empty-p (evaluation-sequence)
  `(=f (evaluation-sequence-length ,evaluation-sequence) 0))




;;; The function `evaluation-sequence-aref' implements a zero-based index into
;;; the valid elements within a sequence.  If the index is out of range, this
;;; function returns NIL.

(defun-simple evaluation-sequence-aref (evaluation-sequence element)
  (declare (type fixnum element))
  (let ((length (evaluation-sequence-length evaluation-sequence)))
    (declare (type fixnum length))
    (if (and (>=f element 0)
	     (<f element length))
	(let ((value (evaluation-sequence-ref evaluation-sequence element)))
	  (if value
	      (validate-item-or-evaluation-value value nil nil)
	      nil))
	nil)))

(defsetf evaluation-sequence-aref set-evaluation-sequence-aref)

(defmacro set-evaluation-sequence-aref (sequence index new-value)
  `(setf (evaluation-sequence-ref ,sequence ,index) ,new-value))




;;; The functions `allocate-empty-evaluation-sequence' and
;;; `copy-evaluation-sequence-elements' form a pair that support writing
;;; instructions to manipulate sequences (e.g. insert, remove, etc).  Note that
;;; allocate-empty-evaluation-seqeunce DOES NOT initialize its attributes, and
;;; so all its elements must be modified using copy-evaluation-sequence-elements
;;; or evaluation-sequence-ref before it is presumed to be a well formed
;;; sequence.  Also note that copy-evaluation-sequence-elements requires that
;;; the target sequence be newly allocated and not yet have any values in the
;;; locations within the target range.  Failure to observe these rules could
;;; lead to memory leaks and recently created items appearing to not have been
;;; copied.

(defun-simple allocate-empty-evaluation-sequence (length)
  (let ((new-vector (allocate-managed-array
		      (+f length (evaluation-sequence-first-element-index)))))
    (setf (evaluation-sequence-vector-reference-count new-vector) 1)
    (make-evaluation-sequence new-vector)))

(defun-void copy-evaluation-sequence-elements
    (source-sequence source-start source-count
		     destination-sequence destination-start)
  (declare (type fixnum source-start source-count destination-start))
  (loop with source-array = (evaluation-sequence-value source-sequence)
	with dest-array = (evaluation-sequence-value destination-sequence)
	for source-index from (+f source-start
				  (evaluation-sequence-first-element-index))
			 below (+f source-start
				   (evaluation-sequence-first-element-index)
				   source-count)
	for dest-index from (+f destination-start
				(evaluation-sequence-first-element-index))
	do
    (setf (managed-svref dest-array dest-index)
	  (copy-if-evaluation-value
	    (managed-svref source-array source-index)))))

(defun-void deep-copy-evaluation-sequence-elements
    (source-sequence source-start source-count
		     destination-sequence destination-start)
  (declare (type fixnum source-start source-count destination-start))
  (loop with source-array = (evaluation-sequence-value source-sequence)
	with dest-array = (evaluation-sequence-value destination-sequence)
	for source-index from (+f source-start
				  (evaluation-sequence-first-element-index))
			 below (+f source-start
				   (evaluation-sequence-first-element-index)
				   source-count)
	for dest-index from (+f destination-start
				(evaluation-sequence-first-element-index))
	do
    (setf (managed-svref dest-array dest-index)
	  (deep-copy-if-evaluation-value
	    (managed-svref source-array source-index)))))

;;; The function `evaluation-sequence-insert-at-beginning' takes a sequence and
;;; an item-or-value and inserts it at the front, reclaiming the old sequence
;;; and creating and returning a new one.  In cases where the given sequence is
;;; mutable, this may be implemented by modifying the given sequence.

;;; We extend the length of the managed-array in the sequence, shift all
;;; elements up by one, then slam the given element into first index location.

#-Lockfree-List
(defun-simple evaluation-sequence-insert-at-beginning (sequence new-element)
  (if (mutable-evaluation-sequence-p sequence)
      (let* ((managed-array (evaluation-sequence-value sequence))
	     (length (managed-array-length managed-array)))
	(declare (type fixnum length))
	(setq managed-array
	      (adjust-managed-array managed-array (+f length 1) nil t))
	(loop for index from length
			above (evaluation-sequence-first-element-index)
	      do
	  (setf (managed-svref managed-array index)
		(managed-svref managed-array (-f index 1))))
	(setf (managed-svref managed-array
			     (evaluation-sequence-first-element-index))
	      (get-reference-to-item-if-item new-element))
	(setf (evaluation-sequence-value sequence) managed-array)
	sequence)
      (let* ((length (evaluation-sequence-length sequence))
	     (new-sequence (allocate-empty-evaluation-sequence (+f length 1))))
	(copy-evaluation-sequence-elements
	  sequence 0 length new-sequence 1)
	(setf (evaluation-sequence-ref new-sequence 0) new-element)
	(reclaim-evaluation-sequence sequence)
	new-sequence)))

#+Lockfree-List
(defun-simple evaluation-sequence-insert-at-beginning (sequence new-element)
  (if (mutable-evaluation-sequence-p sequence)
      (let* ((managed-array (evaluation-sequence-value sequence))
	     (length (managed-array-length managed-array)))
	(declare (type fixnum length))
	(setq managed-array
	      (adjust-managed-array managed-array (+f length 1) nil t))
	(loop for index from length
			above (evaluation-sequence-first-element-index)
	      do
	  (setf (managed-svref managed-array index)
		(managed-svref managed-array (-f index 1))))
	(setf (managed-svref managed-array
			     (evaluation-sequence-first-element-index))
	      (get-reference-to-item-if-item new-element))
	(setf (evaluation-sequence-value sequence) managed-array)
	sequence)
      (let* ((length (evaluation-sequence-length sequence))
	     (new-sequence (allocate-empty-evaluation-sequence (+f length 1))))
	(copy-evaluation-sequence-elements
	  sequence 0 length new-sequence 1)
	(setf (evaluation-sequence-ref new-sequence 0) new-element)
	(reclaim-evaluation-sequence sequence)
	new-sequence)))




;;; The function `evaluation-sequence-insert-at-end' takes an
;;; evaluation-sequence and a new item-or-datum element, and returns a new
;;; sequence with the new element inserted at the end.  The argument sequence is
;;; reclaimed.  If the argument sequence is mutable, then the given sequence is
;;; mutated and returned.

(defun-simple evaluation-sequence-insert-at-end (sequence new-element)
  (if (mutable-evaluation-sequence-p sequence)
      (let* ((managed-array (evaluation-sequence-value sequence))
	     (length (managed-array-length managed-array)))
	(declare (type fixnum length))
	(setq managed-array
	      (adjust-managed-array managed-array (+f length 1) nil t))
	(setf (managed-svref managed-array length)
	      (get-reference-to-item-if-item new-element))
	(setf (evaluation-sequence-value sequence) managed-array)
	sequence)
      (let* ((length (evaluation-sequence-length sequence))
	     (new-sequence (allocate-empty-evaluation-sequence (+f length 1))))
	(copy-evaluation-sequence-elements
	  sequence 0 length new-sequence 0)
	(setf (evaluation-sequence-ref new-sequence length) new-element)
	(reclaim-evaluation-sequence sequence)
	new-sequence)))




;;; The function `evaluation-sequence-remove-element-at-index' takes a sequence
;;; and an index, and remove the element at that index.  If successful, it
;;; returns the new sequence.  If the index was out of range, then it returns
;;; NIL.

(defun-simple evaluation-sequence-remove-element-at-index
    (sequence index-to-remove)
  (loop with remove fixnum = (evaluation-integer-value index-to-remove)
	for index from 0
	for element being each evaluation-sequence-element of sequence
	unless (=f index remove)
	  collect (copy-if-evaluation-value element) into new-elts
	    using eval-cons
	finally
	  (cond ((not (<f -1 remove index))
		 (reclaim-eval-list-of-item-or-datum new-elts)
		 (return nil))
		(t
		 (reclaim-evaluation-integer index-to-remove)
		 (reclaim-evaluation-sequence sequence)
		 (return (allocate-evaluation-sequence new-elts))))))



;;; The function `search-for-sequence-element-from-back' finds and returns the
;;; value (without copying) that matches the given type-specification (if any)
;;; nth back from the end of the list.  This search actually goes from the back
;;; towards the front to be efficient.

(defun-simple search-for-sequence-element-from-back
    (evaluation-sequence type-spec? nth)
  (loop with held-vector = (evaluation-sequence-value evaluation-sequence)
	for index from (1-f (managed-array-length held-vector))
		  downto (evaluation-sequence-first-element-index)
	for value = (get-item-if-item-reference (managed-svref held-vector index))
	do
    (when (and value
	       (or (null type-spec?)
		   (type-specification-type-p value type-spec?)))
      (if (=f nth 0)
	  (return value)
	  (decff nth)))))




;;; The function `nreverse-evaluation-sequence' destructively reverses the
;;; evaluation-sequence-elements of any evaluation-sequence. It is guaranteed 
;;; not to cons. Returns the modified sequence.

(defun-simple nreverse-evaluation-sequence (evaluation-sequence)
  (loop with managed-array = (evaluation-sequence-value evaluation-sequence)
	with sequence-length = (-f (managed-array-length managed-array)
				   (evaluation-sequence-first-element-index))
	with midpoint = (+f (evaluation-sequence-first-element-index)
			    (floorf-positive sequence-length 2))
	with bottom-index = (-f midpoint 1)
	with top-index = (if (mhd-oddpf sequence-length) (+f midpoint 1) midpoint)
	while (>=f bottom-index (evaluation-sequence-first-element-index))
	as bottom-element = (managed-svref managed-array bottom-index)
	do
    (setf (managed-svref managed-array bottom-index)
	  (managed-svref managed-array top-index)) 
    (setf (managed-svref managed-array top-index)
	  bottom-element)
    (incff top-index)
    (decff bottom-index)
	finally
	  (return evaluation-sequence)))


(def-evaluation-value-comparitor sequence
  (or (eq sequence-1 sequence-2)
      (let* ((es1 sequence-1)
	     (es2 sequence-2)
	     (length1 (evaluation-sequence-length es1))
	     (length2 (evaluation-sequence-length es2)))
	(and (=f length1 length2)
	     (loop for value1 being each evaluation-sequence-element of es1
		   for value2 being each evaluation-sequence-element of es2
		   always (item-or-value-eql value1 value2))))))

(def-evaluation-value-= sequence
  (or (eq sequence-1 sequence-2)
      (let* ((es1 sequence-1)
	     (es2 sequence-2)
	     (length1 (evaluation-sequence-length es1))
	     (length2 (evaluation-sequence-length es2)))
	(and (=f length1 length2)
	     (loop for value1 being each evaluation-sequence-element of es1
		   for value2 being each evaluation-sequence-element of es2
		   always (if (or (framep value1)
				  (framep value2))
			      (eq value1 value2)
			      (evaluation-value-= value1 value2)))))))




;;; The writers for sequence, structure, and text are the only means of showing
;;; deeply nesting, or very long evaluation value data structures.  They share
;;; the global variables, `evaluation-value-indentation-depth' and
;;; `evaluation-value-writing-target-length?'.  The first is used to determine
;;; how many spaces to insert after a newline when printing the elements within
;;; structures and sequences.  The second is used to force the printers to begin
;;; truncating output when the printed value has exceeded the given length.
;;; When truncations occur, an ellipsis should be emitted to indicate that not
;;; all data was shown.

(defvar evaluation-value-indentation-depth 0)

(defvar evaluation-value-writing-target-length? nil)

(defvar indent-sequences-and-structures-p t)

(def-evaluation-value-writer sequence
  (tformat "sequence (")		; space before open paren (MHD 2/26/96)
  (loop with evaluation-value-indentation-depth
	  = (+f evaluation-value-indentation-depth 1)
	for first = t then nil
	for elt being each evaluation-sequence-element of sequence
	do
    (cond
      ((and evaluation-value-writing-target-length?
	    (>f (twriting-accumulated-length)
		evaluation-value-writing-target-length?))
       (unless first (twrite-string ", "))
       (twrite-string "...")
       (loop-finish))
      (t
       (unless first
	 (setq leave-text-representation-as-a-single-line? nil)
	 (when indent-sequences-and-structures-p
	   (tformat ",~%")
	   (loop repeat evaluation-value-indentation-depth do
	     (twrite-string "  "))))
       (when (and (symbolp elt) elt)
	 (twrite-string "the symbol "))
       (write-block-or-evaluation-value elt))))
  (twrite-character #.%\)))






;;;; Type Specifications for sequences




(defmacro sequence-type-specification-has-details-p (type-specification)
  `(cdr-of-cons ,type-specification))

(defmacro sequence-type-specification-element-type (type-specification)
  `(cadr ,type-specification))

(defmacro sequence-type-specification-low-bound (type-specification)
  `(caddr  ,type-specification))

(defmacro sequence-type-specification-high-bound (type-specification)
  `(cadddr  ,type-specification))

;;; `fast-sequence-type-specification-p' can be used on validated
;;; type-specifications only.

(defun-simple fast-sequence-type-specification-p (thing)
  (and (consp thing) (eq (car-of-cons thing) 'sequence)))


(defun-simple sequence-type-specification-p (thing)
  (and (consp thing)
       (eq (car-of-cons thing) 'sequence)
       (or (not (sequence-type-specification-has-details-p thing))
	   (and (valid-type-specification-p
		  (sequence-type-specification-element-type thing))
		(let ((low-bound?
			(sequence-type-specification-low-bound thing))
		      (high-bound?
			(sequence-type-specification-high-bound thing)))
		  (or (null low-bound?)
		      (and (fixnump low-bound?)
			   (>=f low-bound? 0)
			   (or (null high-bound?)
			       (and (fixnump high-bound?)
				    (>=f high-bound? low-bound?))))))))))
	       

(defmacro make-sequence-subtype-predicate (type superior-type in-kb-p)
  (unless (and (symbolp type) (symbolp superior-type))
    (error "this is not a general purpose macro yet.  It assumes args are symbols"))
  `(let* ((type-has-details-p
	    (sequence-type-specification-has-details-p ,type))
	  (superior-type-has-details-p
	    (sequence-type-specification-has-details-p ,superior-type)))
     (cond
       ((or type-has-details-p
	    superior-type-has-details-p)
	(unless type-has-details-p
	  (setf ,type '(sequence item-or-datum)))
	(unless superior-type-has-details-p
	  (setf ,superior-type '(sequence item-or-datum)))
	(and (,(if in-kb-p
		   'type-specification-subtype-in-kb-p
		   'type-specification-subtype-p)
	       (sequence-type-specification-element-type ,type)
	       (sequence-type-specification-element-type ,superior-type))
	     (let ((superior-low-bound?
		     (sequence-type-specification-low-bound ,superior-type))
		   (superior-high-bound?
		     (sequence-type-specification-high-bound ,superior-type)))
	       (and (or (not superior-low-bound?)
			(let ((low-bound?
				(sequence-type-specification-low-bound ,type)))
			  (if (not low-bound?)
			      (=f superior-low-bound? 0)
			      (>=f low-bound? superior-low-bound?))))
		    (or (not superior-high-bound?)
			(let ((high-bound?
				(sequence-type-specification-high-bound ,type)))
			  (if (not high-bound?)
			      (=f superior-high-bound? most-positive-fixnum)
			      (<=f high-bound? superior-high-bound?))))))))
       (t
	t))))

(defun-simple sequence-type-specification-subtype-in-kb-p (type superior-type)
  (make-sequence-subtype-predicate type superior-type t))

(defmacro make-sequence-type-intersection-predicate (type superior-type in-kb-p)
  (unless (and (symbolp type) (symbolp superior-type))
    (error "this is not a general purpose macro yet.  It assumes args are symbols"))
  `(let* ((type-has-details-p
	    (sequence-type-specification-has-details-p ,type))
	  (superior-type-has-details-p
	    (sequence-type-specification-has-details-p ,superior-type)))
     (cond
       ((or type-has-details-p
	    superior-type-has-details-p)
	(unless type-has-details-p
	  (setf ,type '(sequence item-or-datum)))
	(unless superior-type-has-details-p
	  (setf ,superior-type '(sequence item-or-datum)))
	(and (,(if in-kb-p
		   'type-specifications-could-intersect-in-kb-p
		   'type-specifications-could-intersect-p)
	       (sequence-type-specification-element-type ,type)
	       (sequence-type-specification-element-type ,superior-type))
	     (let ((superior-low-bound
		     (or (sequence-type-specification-low-bound ,superior-type)
			 0))
		   (superior-high-bound
		     (or (sequence-type-specification-high-bound ,superior-type)
			 most-positive-fixnum))
		   (low-bound
		     (or (sequence-type-specification-low-bound ,type)
			 0))
		   (high-bound
		     (or (sequence-type-specification-high-bound ,type)
			 most-positive-fixnum)))
	       (or (<=f superior-low-bound high-bound superior-high-bound)
		   (<=f superior-low-bound low-bound superior-high-bound)))))
       (t
	t))))


(defun-simple sequence-type-specifications-could-intersect-in-kb-p (type superior-type)
  (make-sequence-type-intersection-predicate type superior-type t))


(defmacro make-sequence-not-subtype-predicate (type superior-type in-kb-p)
  (unless (and (symbolp type) (symbolp superior-type))
    (error "this is not a general purpose macro yet.  It assumes args are symbols"))
  `(let* ((type-has-details-p
	    (sequence-type-specification-has-details-p ,type))
	  (superior-type-has-details-p
	    (sequence-type-specification-has-details-p ,superior-type)))
     (cond
       ((or type-has-details-p
	    superior-type-has-details-p)
	(unless type-has-details-p
	  (setf ,type '(sequence item-or-datum)))
	(unless superior-type-has-details-p
	  (setf ,superior-type '(sequence item-or-datum)))
	(or (,(if in-kb-p
		  'type-specification-not-subtype-in-kb-p
		  'type-specification-not-subtype-p)
	      (sequence-type-specification-element-type ,type)
	      (sequence-type-specification-element-type ,superior-type))
	   (let ((superior-low-bound
		   (or (sequence-type-specification-low-bound ,superior-type)
		       0))
		 (superior-high-bound
		   (or (sequence-type-specification-high-bound ,superior-type)
		       most-positive-fixnum))
		 (low-bound
		   (or (sequence-type-specification-low-bound ,type)
		       0))
		 (high-bound
		   (or (sequence-type-specification-high-bound ,type)
		       most-positive-fixnum)))
	     (not
	       (<=f superior-low-bound low-bound high-bound superior-high-bound)))))
       (t
	nil))))

(defun-simple sequence-type-specification-not-subtype-in-kb-p (type superior-type)
  (make-sequence-not-subtype-predicate type superior-type t))

(defun-simple detailed-evaluation-sequence-type-p (sequence type-specification)
  (let* ((element-type-specification
	   (sequence-type-specification-element-type type-specification))
	 (low-bound? (sequence-type-specification-low-bound type-specification))
	 (high-bound? (and low-bound?
			   (sequence-type-specification-high-bound type-specification)))
	 (length? (and low-bound?
		       (evaluation-sequence-length sequence))))
    (and (or (not low-bound?)
	     (<=f low-bound? length?))
	 (or (not high-bound?)
	     (<f length? high-bound?))
	 (loop for element being each evaluation-sequence-element of sequence
	       always
	       (type-specification-type-p element element-type-specification)))))
    

#+development
(defparameter validation-suite-for-sequence-type-predicates
  '(((sequence) (sequence) (t t nil))
    ((sequence integer) (sequence) (t t nil))
    ((sequence) (sequence integer) (nil t t))
    ((sequence integer) (sequence integer 0 5) (nil t t))
    ((sequence integer) (sequence datum) (t t nil))
    ((sequence integer 0 5) (sequence integer) (t t nil))
    ((sequence integer 0 7) (sequence datum 3 8) (nil t t))
    ((sequence integer 0 6) (sequence datum 8 20) (nil nil t))))

#+development
(defun validate-sequence-type-predicates ()
  (loop for (ts1 ts2 (subtype-p intersect-p not-subtype-p))
	    in validation-suite-for-sequence-type-predicates
	do
    (format t "For type=~s and superior-type=~s:~%" ts1 ts2)
    (let ((res (sequence-type-specification-subtype-in-kb-p ts1 ts2)))
      (format t "     subtype-in-kb-p => ~s :  ~50T~s~%"
	      res (if (eq res subtype-p) 'good 'bad)))
    (let ((res (sequence-type-specifications-could-intersect-in-kb-p ts1 ts2)))
      (format t "     could-intersect-in-kb-p => ~s :  ~50T~s~%"
	      res (if (eq res intersect-p) 'good 'bad)))
    (let ((res (sequence-type-specification-not-subtype-in-kb-p ts1 ts2)))
      (format t "     not-subtype-in-kb-p => ~s :  ~50T~s~%"
	      res (if (eq res not-subtype-p) 'good 'bad)))))
    





;; Notes from Joe:

;; Stuff to look at
;; 1 copy-evaluation-non-logical-datum-macro
;; 2 the macro evaluation-datum-p-given-register (fanout done 3/12)
;; 3 the function evaluation-value-= (which will bark if misfed)
;; 4 the function evaluation-value-equal-p
;; 5 all of the temporary constant stuff (it affects ICP/RPC/GSI)
;; 6 the function evaluation-value-of-type-p in SETS seems to be wrong
;;   in its final case regarding the type being in a cons
;; 7 the function type-specification-returning-datum-type-or-unknown in SETS

;; Questions for JRA
;; should there be functional accessors yes
;; how should comp/parts be written
;; should there be read-print compatibility
;; should the copier share the outer cons too!
;; validation might be a problem now 
;; are two NILS 






;;;; Evaluation Structures




;;; The evaluation-value structure is a subtype of value.  It is a linear list of
;;; attribute name and attribute value pairs, stored in a managed-array.

(def-evaluation-value structure t)

(defmacro estructure-ref-count-index () 0)

(defmacro estructure-first-attribute-index () 1)




;;; The functions `allocate-evaluation-structure' and
;;; `allocate-evaluation-structure-from-vector' are both used to create new
;;; evaluation structures.  The first takes an eval cons list of attribute keys
;;; to values, written property-list style, and then reclaims the list.  The
;;; second takes a simple vector, an index into it, and a count of the number of
;;; keys and values to copy from the simple vector into the new
;;; evaluation-structure.  The simple vector should contain alternating key
;;; names and values, again in property-list style.  The vector is not
;;; reclaimed.

(defun-simple allocate-evaluation-structure (eval-cons-property-list)
  (let ((held-vector
	  (allocate-managed-array (+f (length eval-cons-property-list)
				      (estructure-first-attribute-index)))))
    (setf (managed-svref held-vector (estructure-ref-count-index)) 1)
    (loop for index fixnum from (estructure-first-attribute-index) by 2
	  for (key value) on eval-cons-property-list by 'cddr
	  do
      (setf (managed-svref held-vector index) key)
      (setf (managed-svref held-vector (1+f index))
	    (get-reference-to-item-if-item value)))
    (reclaim-eval-list eval-cons-property-list)
    (make-evaluation-structure held-vector)))

(defmacro allocate-evaluation-structure-inline (&body keys-and-values)
  (when (oddp (length keys-and-values))  
    (error "number of keys and values must be even"))
  (let ((held-vector (gensym)))
    `(let ((,held-vector (allocate-managed-array
			   (+f ,(length keys-and-values)
			       (estructure-first-attribute-index)))))
       (setf (managed-svref ,held-vector (estructure-ref-count-index)) 1)
       ,@(loop for index from (estructure-first-attribute-index) by 2
	       for (key value) on keys-and-values by 'cddr
	       collect `(progn
			  (setf (managed-svref ,held-vector ,index) ,key)
			  (setf (managed-svref ,held-vector ,(1+ index))
				(get-reference-to-item-if-item ,value))))
       (make-evaluation-structure ,held-vector))))

(defun-simple allocate-evaluation-structure-from-vector
    (simple-vector first-key-index key-count-times-two)
  (let ((held-vector
	  (allocate-managed-array (+f key-count-times-two
				      (estructure-first-attribute-index)))))
    (setf (managed-svref held-vector (estructure-ref-count-index)) 1)
    (loop for source-index from first-key-index by 2
	  for n from 0 below key-count-times-two by 2
	  for dest-index from (evaluation-sequence-first-element-index) by 2
	  do (setf (managed-svref held-vector dest-index)
		   (svref simple-vector source-index))
	     (setf (managed-svref held-vector (1+f dest-index))
		   (get-reference-to-item-if-item (svref simple-vector (1+f source-index)))))
    (make-evaluation-structure held-vector)))




;;; The macro `mutable-evaluation-structure-p' takes an evaluation-structure and
;;; returns whether or not there is one reference to this structure, which
;;; implies that this evaluation-structure may be mutated without copying it.

(defmacro mutable-evaluation-structure-p (evaluation-structure)
  `(=f (managed-svref (evaluation-structure-value ,evaluation-structure)
		      (estructure-ref-count-index))
       1))




;;; The macro `obtain-mutable-evaluation-structure-copy' takes and reclaims an
;;; evaluation structure, returning a copy that has only one reference to it,
;;; and so can be mutated using setf of evaluation-structure-slot.

;;; In cases where the argument only has a single reference to it, the argument
;;; will be the return value after reprocessed frame-values have been nulled out
;;; (just as make-unique-evaluation-structure-copy-1 nulls out reprocessed frames
;;; when copying multi-reference structures.).
;;;
(defmacro obtain-mutable-evaluation-structure-copy (old-structure)
  (let ((old-struct (gensym))
	(old-held-vector (gensym)))
    `(let* ((,old-struct ,old-structure)
	    (,old-held-vector (evaluation-structure-value ,old-struct)))
       (if (=f (managed-svref ,old-held-vector (estructure-ref-count-index)) 1)
	   ,old-struct
	   (prog1 (make-unique-evaluation-structure-copy-1 ,old-held-vector)
	     (reclaim-evaluation-structure ,old-struct))))))

(defmacro make-unique-evaluation-structure-copy
    (evaluation-structure)
  (let ((struct (gensym))
	(held-vector (gensym)))
    `(let* ((,struct ,evaluation-structure)
	    (,held-vector (evaluation-structure-value ,struct)))
       (make-unique-evaluation-structure-copy-1 ,held-vector))))

(defun-simple make-unique-evaluation-structure-copy-1 (old-held-vector)
  (let* ((vector-length (managed-array-length old-held-vector))
	 (held-vector (allocate-managed-array vector-length)))
    (loop for i from (estructure-first-attribute-index) below vector-length by 2
	  as old-attribute-value = (managed-svref old-held-vector (+f i 1))
	  initially
	    (setf (managed-svref held-vector (estructure-ref-count-index)) 1)
	  do
      (setf (managed-svref held-vector i)
	    (managed-svref old-held-vector i))
      (setf (managed-svref held-vector (+f i 1))
	    (copy-if-evaluation-value old-attribute-value)))
    (make-evaluation-structure held-vector)))

(defun-simple make-unique-evaluation-structure-deep-copy-1 (old-held-vector)
  (let* ((vector-length (managed-array-length old-held-vector))
	 (held-vector (allocate-managed-array vector-length)))
    (loop for i from (estructure-first-attribute-index) below vector-length by 2
	  as old-attribute-value = (managed-svref old-held-vector (+f i 1))
	  initially
	    (setf (managed-svref held-vector (estructure-ref-count-index)) 1)
	  do
      (setf (managed-svref held-vector i)
	    (managed-svref old-held-vector i))
      (setf (managed-svref held-vector (+f i 1))
	    (deep-copy-if-evaluation-value old-attribute-value)))
    (make-evaluation-structure held-vector)))

(defmacro evaluation-structure-length (structure)
  `(ashf (-f (managed-array-length (evaluation-structure-value ,structure))
	     (estructure-first-attribute-index))
	 -1))

(def-evaluation-value-reclaimer structure
  (let* ((held-vector (evaluation-structure-value structure))
	 (ref-count (managed-svref held-vector (estructure-ref-count-index))))
    (if (=f ref-count 1)
	(loop for index fixnum from (+f (estructure-first-attribute-index) 1)
			below (managed-array-length held-vector)
			by 2
	      do
	  (reclaim-if-evaluation-value-function
	    (managed-svref held-vector index))
	      finally (reclaim-managed-array held-vector))
	(setf (managed-svref held-vector (estructure-ref-count-index))
	      (-f ref-count 1)))))

(def-evaluation-value-copier structure
  (let ((held-vector (evaluation-structure-value structure)))
    (incff (managed-svref held-vector (estructure-ref-count-index)))
    (make-evaluation-structure held-vector)))

(def-evaluation-value-deep-copier structure
    (make-unique-evaluation-structure-deep-copy-1
      (evaluation-structure-value structure)))

;;; The loop path `evaluation-structure-pair' is used to iterate over the keys and
;;; values within a structure.  All values of the structure that are frames will have
;;; been validated before being served.  Users
;;; of this iteration path should always provide a destructuring pattern of the
;;; attribute name dotted with the value as the binding for the values of this
;;; iteration.  Internally this does not actually make a cons that is then
;;; destructured, but it was the only interface I could find for serving up
;;; more than one value per iteration of this loop path.  For example, the
;;; following code calls frob on each attribute-name symbol and value pair.

;;;   (loop for (attribute . value) being each evaluation-structure-pair of structure
;;;         do
;;;     (frob attribute value))

;;; The loop-path defined in UTILITIES2.  See my comments of this date there and
;;; in FRAMES2A for an explanation.  -jv, 12/19/03

(defun-for-macro evaluation-structure-pairs-of
    (path-name variable-pair data-type prep-phrases inclusive? allowed-preps data)
  (declare (ignore data-type data allowed-preps))
  (when (null prep-phrases)
    (error "OF is missing in ~S iteration path of ~S."
           path-name variable-pair))
  (when inclusive?
    (error "Inclusive stepping is not supported in ~s path of ~s ~
            (prep-phrase = ~s)"
           path-name variable-pair prep-phrases))
  (unless (and (consp variable-pair)
	       (symbolp (car variable-pair))
	       (symbolp (cdr variable-pair)))
    (error "The evaluation-structure-pairs-of iteration path requires a ~
            (key . value) destructuring pattern for its variable, got ~a."
	   variable-pair))
  (let* ((structure (gensym))
	 (attribute-name-var (car variable-pair))
	 (attribute-value-var (cdr variable-pair))
	 (held-vector (make-symbol "HELD-VECTOR"))
         (next-index (make-symbol "NEXT-INDEX"))
	 (attribute-value (make-symbol "ATTRIBUTE-VALUE"))
         (length (make-symbol "LENGTH"))
         (init-bindings
           `((,structure ,(cadar prep-phrases))
	     (,held-vector nil)
             (,next-index (estructure-first-attribute-index) fixnum)
             (,length 0 fixnum)
	     ,@(when attribute-name-var
		 `((,attribute-name-var nil)))
	     ,@(when attribute-value-var
		 `((,attribute-value nil)
		   (,attribute-value-var nil)))))
         (prologue-forms
           `(#+development
	     (unless (evaluation-structure-p ,structure)
	       (error "Can't loop over evaluation-structure-pairs of ~a, it's not a structure."
		      ,structure))
	     (setq ,held-vector (evaluation-structure-value ,structure))
	     (setq ,length (managed-array-length ,held-vector))))
	 (pre-step-tests `(>=f ,next-index ,length))
	 (steppings
	   `(,next-index
	       (progn
		 ,@(when attribute-name-var
		     `((setq ,attribute-name-var
			     (managed-svref ,held-vector ,next-index))))
		 ,@(when attribute-value-var
		     `((setq ,attribute-value
			     (managed-svref ,held-vector (+f ,next-index 1)))
		       (setq ,attribute-value-var
			     (validate-item-or-evaluation-value
			       ,attribute-value nil nil))))
		 (+f ,next-index 2))))
	 (post-step-tests nil)
	 (post-step-settings nil))
    `(,init-bindings
	,prologue-forms
	,pre-step-tests
	,steppings
	,post-step-tests
	,post-step-settings)))

(def-evaluation-value-writer structure
  (twrite-string "structure (")		; space before open paren (MHD 2/26/96)
  (loop with evaluation-value-indentation-depth
	  = (+f evaluation-value-indentation-depth 1)
	for first = t then nil
	for (name . value) being evaluation-structure-pair of structure
	do
    (cond
      ((and evaluation-value-writing-target-length?
	    (>f (twriting-accumulated-length)
		evaluation-value-writing-target-length?))
       (unless first (twrite-string ", "))
       (twrite-string "...")
       (loop-finish))
      (t
       (unless first
	 (setq leave-text-representation-as-a-single-line? nil)
	 (when indent-sequences-and-structures-p
	   (tformat ",~%")
	   (loop repeat evaluation-value-indentation-depth do
	     (twrite-string "  "))))
       (write-evaluation-value name)
       (twrite-string ": ")
       (when (and value (symbolp value))
	 (twrite-string "the symbol "))
       (write-block-or-evaluation-value value))))
  (twrite-character #.%\)))




;;; The definition of equality for evaluation-structures is that two structures have
;;; the same set of attributes each containing matching values.  The order of
;;; the attributes within each structure does not affect whether or not they are
;;; equal.

;;; That said, the implementation of the comparitors will still be optimized for
;;; the case where the attributes are in the same order.  Also, since the
;;; attributes are a set without duplicates, it can be assumed that if the
;;; structures are the same length, and every attribute from one structure can be
;;; found in the other, that the two structures do in fact contain the same set of
;;; attributes.

(defun-simple compare-structure-contents (structure1 structure2 use-eql?)
  (or (eq structure1 structure2)
      (and (=f (managed-array-length (evaluation-structure-value structure1))
	       (managed-array-length (evaluation-structure-value structure2)))
	   (loop for (key1 . val1) being each evaluation-structure-pair of structure1
		 for (key2 . val2) being each evaluation-structure-pair of structure2
		 always
		 (if (eq key1 key2)
		     (if (or (framep val1) (framep val2))
			 (eq val1 val2)
			 (if use-eql?
			     (evaluation-value-eql val1 val2)
			     (evaluation-value-= val1 val2)))
		     ;; Perhaps the keys are in a different order, search the
		     ;; second structure for this key.
		     (loop for (key3 . val3)
			       being each evaluation-structure-pair of structure2
			   do
		       (when (eq key1 key3)
			 (return (if (or (framep val1) (framep val3))
				     (eq val1 val3)
				     (if use-eql?
					 (evaluation-value-eql val1 val3)
					 (evaluation-value-= val1 val3)))))))))))

(def-evaluation-value-comparitor structure
  (compare-structure-contents structure-1 structure-2 t))

(def-evaluation-value-= structure
  (compare-structure-contents structure-1 structure-2 nil))




;;; The macro `structure-slot' is the lowest-level accessor for stuct attributes.
;;; It takes the evaluation-structure-value of an evaluation structure (which happens
;;; to be a managed-array in the current implementation), searches it for the
;;; value associated with the given attribute-name symbol, and returns that
;;; value.  The value is still owned by the structure, and should not be reclaimed.
;;; This macro also takes a default value to be returned if the given attribute
;;; name does not exist within the the given structure.  Note that structure-slot
;;; expands into a function call, but you can get a fully open-coded accessor
;;; using `structure-slot-macro'.

;;; The result of this macro can be one of three types of values.  If the
;;; attribute exists within the structure and the value is valid, then it is
;;; returned.  If the attribute exists, but either contains NIL or contains a
;;; frame that has been deleted since it was inserted into this structure, then
;;; again NIL is returned.  If the attribute does not exist within the given
;;; structure, then the default-value is returned, which defaults to NIL.

;;; This accessor is not setfable, you must use evaluation-structure-slot.

(defmacro structure-slot-index
    (evaluation-structure-value attribute-name)
  (let ((held-vector (gensym))
	(given-name (gensym))
	(search-index (gensym)))
    `(loop with ,held-vector = ,evaluation-structure-value
	   with ,given-name = ,attribute-name
	   for ,search-index fixnum from (estructure-first-attribute-index)
			     below (managed-array-length ,held-vector)
			     by 2
	   when (eq (managed-svref ,held-vector ,search-index) ,given-name)
	     return (+f ,search-index 1))))

(defmacro structure-slot-macro
    (evaluation-structure-value attribute-name &optional default-value)
  (let ((held-vector (gensym))
	(index (gensym)))
    `(let* ((,held-vector ,evaluation-structure-value)
	    (,index (structure-slot-index ,held-vector ,attribute-name)))
       (if ,index
	   (validate-item-or-evaluation-value
	     (managed-svref ,held-vector ,index)
	     nil nil)
	   ,default-value))))

(defun-simple structure-slot-1 (estructure name default)
  (structure-slot-macro estructure name default))

(defmacro structure-slot
    (evaluation-structure-value attribute-name &optional default-value)
  `(structure-slot-1 ,evaluation-structure-value ,attribute-name ,default-value))




;;; The macro `evaluation-structure-slot' takes an evaluation-structure, a symbol
;;; naming an attribute, and optionally a default value.  This function fetches
;;; the value of the given attribute from the given structure.  The result is still
;;; owned by the structure and should not be reclaimed.  See `structure-slot' for more
;;; details about validation and return values.  Note that this version is
;;; executed as an out-of-line function.  For an inlined version, used
;;; `evaluation-structure-slot-macro'.

;;; Both evaluation-structure-slot and evaluation-structure-slot-macro are setfable,
;;; the first calling a function and the second expanding inline.  The semantics
;;; of the setter are as follows.  If an attribute of the given name exists,
;;; then its old value is reclaimed and is replaced with the new value.  If the
;;; attribute does not exist, then it is added to the end of the set of
;;; attributes for the given structure.  NIL is a valid new value for attributes.

;;; The function `overwrite-evaluation-structure-slot' (and its open-coded
;;; version `overwrite-evaluation-structure-slot-macro') is just like the setter
;;; for evaluation-structure-slot, except that any old values in already
;;; existing attributes are not reclaimed, they are simply overwritten with the
;;; new value.

;;; To remove an attribute from an existing structure, see
;;; `remove-evaluation-structure-attribute'.

(defmacro evaluation-structure-slot
    (evaluation-structure attribute-name &optional default-value)
  `(estructure-slot ,evaluation-structure ,attribute-name ,default-value))

(defun-simple estructure-slot (estructure name default)
  (structure-slot (evaluation-structure-value estructure) name default))

(defmacro evaluation-structure-slot-macro
    (evaluation-structure attribute-name &optional default-value)
  `(structure-slot (evaluation-structure-value ,evaluation-structure)
		,attribute-name ,default-value))

(defmacro set-evaluation-structure-slot-macro
    (evaluation-structure attribute-name new-value)
  (let ((structure (gensym))
	(held-vector (gensym))
	(length (gensym))
	(given-name (gensym))
	(value (gensym))
	(search-index (gensym)))
    `(loop with ,structure = ,evaluation-structure
	   with ,held-vector = (evaluation-structure-value ,structure)
	   with ,length fixnum = (managed-array-length ,held-vector)
	   with ,given-name = ,attribute-name
	   with ,value = (get-reference-to-item-if-item ,new-value)
	   for ,search-index fixnum from (estructure-first-attribute-index)
			     below ,length by 2
	   do
       (when (eq (managed-svref ,held-vector ,search-index) ,given-name)
	 (let ((value-index (+f ,search-index 1)))
	   (reclaim-if-evaluation-value-function
	     (managed-svref ,held-vector value-index))
	   (setf (managed-svref ,held-vector value-index) ,value)
	   (return ,value)))
	   finally
	     (setq ,held-vector
		   (adjust-managed-array ,held-vector (+f ,length 2)))
	     (setf (evaluation-structure-value ,structure) ,held-vector)
	     (setf (managed-svref ,held-vector ,length) ,given-name)
	     (setf (managed-svref ,held-vector (+f ,length 1)) ,value)
	     (return ,value))))
	
(defsetf evaluation-structure-slot-macro set-evaluation-structure-slot-macro)

(defun-simple set-evaluation-structure-slot (estructure name new-value)
  (setf (evaluation-structure-slot-macro estructure name) new-value))

(defsetf evaluation-structure-slot set-evaluation-structure-slot)

(defmacro overwrite-evaluation-structure-slot-macro
    (evaluation-structure attribute-name new-value)
  (let ((structure (gensym))
	(held-vector (gensym))
	(length (gensym))
	(given-name (gensym))
	(value (gensym))
	(search-index (gensym)))
    `(loop with ,structure = ,evaluation-structure
	   with ,held-vector = (evaluation-structure-value ,structure)
	   with ,length fixnum = (managed-array-length ,held-vector)
	   with ,given-name = ,attribute-name
	   with ,value = (get-reference-to-item-if-item ,new-value)
	   for ,search-index fixnum from (estructure-first-attribute-index)
			     below ,length by 2
	   do
       (when (eq (managed-svref ,held-vector ,search-index) ,given-name)
	 (let ((value-index (+f ,search-index 1)))
	   (setf (managed-svref ,held-vector value-index) ,value)
	   (return ,value)))
	   finally
	     (setq ,held-vector
		   (adjust-managed-array ,held-vector (+f ,length 2)))
	     (setf (evaluation-structure-value ,structure) ,held-vector)
	     (setf (managed-svref ,held-vector ,length) ,given-name)
	     (setf (managed-svref ,held-vector (+f ,length 1)) ,value)
	     (return ,value))))

#+unused
(defun-simple overwrite-evaluation-structure-slot
    (evaluation-structure attribute-name new-value)
  (overwrite-evaluation-structure-slot-macro
    evaluation-structure attribute-name new-value))




;;; The function `remove-evaluation-structure-attribute' takes an evaluation
;;; structure and a symbol possibly naming an attribute within that structure.
;;; This function will search for that attribute within the given structure, and
;;; if found, this function returns a new structure containing the same
;;; attributes as the given structure, but with the named attribute removed.  If
;;; the given attribute is not found within the structure, then this function
;;; returns NIL.

(defun-simple remove-evaluation-structure-attribute (structure symbol)
  (loop with attribute-found? = nil
	with held-vector = (evaluation-structure-value structure)
	with length fixnum = (managed-array-length held-vector)
	for index fixnum from (estructure-first-attribute-index)
		  below length by 2
	for attribute = (managed-svref held-vector index)
	when (cond ((eq symbol attribute)
		    (setq attribute-found? t)
		    nil)
		   (t t))
	  nconc (eval-list attribute (managed-svref held-vector (+f index 1)))
	    into new-attributes
	finally
	  (cond (attribute-found?
		 (loop for value-cons on (cdr new-attributes) by #'cddr
		       do
		   (setf (car value-cons)
			 (copy-if-evaluation-value (car-of-cons value-cons))))
		 (return (allocate-evaluation-structure new-attributes)))
		(t
		 (reclaim-eval-list new-attributes)
		 (return nil)))))






;;;; Type Specifications for Structures




;;; Type specifications for evaluation-structures can have details that describe
;;; types for attributes within the structure and a predicate to determine which
;;; attributes are required, which must come in pairs, and which are required to
;;; be disjoint.  These details are expressed as extra information in the cdr of
;;; type-specifications whose car is STRUCTURE.

(defmacro structure-type-specification-has-details-p (type-specification)
  `(cdr-of-cons ,type-specification))

(defmacro structure-type-specification-has-details? (type-specification)
  `(cdr-of-cons ,type-specification))

(defmacro structure-type-specification-slot-list (type-specification)
  `(car-of-cons (cdr-of-cons ,type-specification)))

(defmacro structure-type-specification-minimum-contents (type-specification)
  `(caddr ,type-specification))



;;; The variable `maximum-number-of-slots-in-structure-type' sets a limit on the
;;; number of slot specifications in a structure type for it to be considered
;;; valid by structure-type-specification-p. I don't know why there needs to be
;;; a limit, but we're making it a special variable so that it can be rebound by
;;; users that need more slots, i.e., def-type-parameter. -fmw, 9/26/05

(defvar maximum-number-of-slots-in-structure-type 25)


;;; The substitution macro `fast-structure-type-specification-p' can be used on
;;; validated type-specifications only.

(def-substitution-macro fast-structure-type-specification-p (thing)
  (and (consp thing) (eq (car-of-cons thing) 'structure)))

(defun-simple structure-type-specification-p (thing)
  (and (consp thing)
       (eq (car-of-cons thing) 'structure)
       (or (not (structure-type-specification-has-details-p thing))
	   (let ((slot-names-and-types
		   (structure-type-specification-slot-list thing))
		 (minimum-contents
		   (structure-type-specification-minimum-contents thing)))
	     (and (consp slot-names-and-types)
		  (loop for slot-spec in slot-names-and-types
			as i from 0 by 1 
			always
			(and (<f i maximum-number-of-slots-in-structure-type)
			     (valid-structure-slot-specification-p slot-spec)))
		  (or (null minimum-contents)
		      (boolean-composition-over-symbols-p minimum-contents)))))))

(defun-simple valid-structure-slot-specification-p (slot-spec)
  (and (consp slot-spec)
       (symbolp (car slot-spec))
       (let ((tail (cdr-of-cons slot-spec)))
	 (and (consp tail)
	      (null (cdr-of-cons tail))
	      (valid-type-specification-p (car-of-cons tail))))))

(defvar boolean-composition-over-symbols-allows-top-level-symbols-p t)

(defun-simple boolean-composition-over-symbols-p (exp)
  (cond
    ((consp exp)
     (let ((boolean-composition-over-symbols-allows-top-level-symbols-p t))
       (or (and (memq (car-of-cons exp) '(and or))
		(loop for sub-exp in (cdr-of-cons exp)
		      always
		      (boolean-composition-over-symbols-p sub-exp)))
	   (and (eq (car-of-cons exp) 'not)
		(consp (cdr-of-cons exp))
		(boolean-composition-over-symbols-p
		 (car-of-cons (cdr-of-cons exp)))
		(null (cdr-of-cons (cdr-of-cons exp)))))))
    ((and exp (symbolp exp))
     boolean-composition-over-symbols-allows-top-level-symbols-p)
    (t
     nil)))

(defun-simple slot-name-list-meets-minimum-structure-requirements-p
    (minimum-contents slot-names)
  (cond
    ((consp minimum-contents)
     (case (car minimum-contents)
       (and
	(loop for sub-exp in (cdr minimum-contents)
	      always
	      (slot-name-list-meets-minimum-structure-requirements-p
		sub-exp slot-names)))
       (or
	(loop for  sub-exp in (cdr minimum-contents)
	      thereis
	      (slot-name-list-meets-minimum-structure-requirements-p
		sub-exp slot-names)))
       (not
	(not (slot-name-list-meets-minimum-structure-requirements-p
	       (cadr minimum-contents) slot-names)))
       ))
    ((symbolp minimum-contents)
     (memq-macro minimum-contents slot-names))))

(defmacro do-structure-type-specification-tuples ((tuple type-specification-exp) &body body)
  `(loop with type-specification = ,type-specification-exp
	 with slot-list = (structure-type-specification-slot-list
			    type-specification)
	 with minimum-contents = (structure-type-specification-minimum-contents
				   type-specification)
	 with len (integer 0 28) = (length slot-list)
	 for i fixnum from 0 below (expt 2 len) ; result is a fixnum
	 as ,tuple = (loop for j (integer 0 28) from 0 to len
			   as (slot-name) in slot-list
			   when (logtest (ashf 1 j) i)
			     collect slot-name
			       using gensym-cons)
	 when (or (null minimum-contents)
		  (slot-name-list-meets-minimum-structure-requirements-p
		    minimum-contents ,tuple))
	   do (progn ,@body)
	 do (reclaim-gensym-list ,tuple)))

#+development
(defun show-structure-type-specification-tuples (type-specification)
  (do-structure-type-specification-tuples (tuple type-specification)
    (format t "tuple = ~s~%" tuple)))

(defmacro make-structure-subtype-predicate (type superior-type in-kb-p)
  (unless (and (symbolp type) (symbolp superior-type))
    (error "this is not a general purpose macro yet.  It assumes args are symbols"))
  `(let* ((type-has-details-p
	    (structure-type-specification-has-details-p ,type))
	  (superior-type-has-details-p
	    (structure-type-specification-has-details-p ,superior-type)))
     (cond
       (superior-type-has-details-p
	(cond
	  (type-has-details-p ; must do deep comparison
	   (let ((minimum-contents-of-superior
		   (structure-type-specification-minimum-contents ,superior-type))
		 (slot-list-of-type
		   (structure-type-specification-slot-list ,type))
		 (slot-list-of-superior-type
		   (structure-type-specification-slot-list ,superior-type))
		 (slot-type-cache nil)
		 (ok-p t))
	     (block test-loop
	       (do-structure-type-specification-tuples (tuple type)
;		 (format t "tuple=~s~%" tuple)
		 (unless (and (or (null minimum-contents-of-superior)
				  (slot-name-list-meets-minimum-structure-requirements-p
				    minimum-contents-of-superior tuple))
			      (loop for name in tuple
				    as cache-entry? = (assq name slot-type-cache)
				    always
				(cond
				  (cache-entry? (cdr cache-entry?))
				  (t
				   (let* ((type-spec-of-slot
					    (cadr (assq name slot-list-of-type)))
					  (type-spec-of-slot-in-superior?
					    (cadr (assq name slot-list-of-superior-type)))
					  (new-cached-type-test
					    (or (null type-spec-of-slot-in-superior?) ; if not specified then it is permitted
						(,(if in-kb-p
						      'type-specification-subtype-in-kb-p
						      'type-specification-subtype-p)
						  type-spec-of-slot type-spec-of-slot-in-superior?))))
				     (gensym-push
				       (gensym-cons name new-cached-type-test)
				       slot-type-cache)
				     new-cached-type-test)))))
		   (setq ok-p nil)
		   (return-from test-loop nil))))
	     ok-p))
	  (t ; type could have slots not present in superior-type
	   nil)))
       (t ; superior could be any structure
	t))))

(defun-simple structure-type-specification-subtype-in-kb-p (type superior-type)
  (make-structure-subtype-predicate type superior-type t))

(defun-simple make-augmented-structure-type-specification
    (structure-type-specification other-strcture-type-specification)
  (loop with new-type-specification = (copy-tree-using-gensym-conses
					structure-type-specification)
	with original-slot-list = (structure-type-specification-slot-list
				    structure-type-specification)
	for (name type) in (structure-type-specification-slot-list
			     other-strcture-type-specification)
	unless (assq name original-slot-list)
	do
    (gensym-push (gensym-list name
			      (copy-tree-using-gensym-conses '(or item-or-datum (no-item))))
		 (cadr new-type-specification))
	finally
	  (return new-type-specification)))

(defmacro make-structure-type-intersection-predicate (type superior-type in-kb-p)
  (unless (and (symbolp type) (symbolp superior-type))
    (error "this is not a general purpose macro yet.  It assumes args are symbols"))
  `(let* ((type-has-details-p
	    (structure-type-specification-has-details-p ,type))
	  (superior-type-has-details-p
	    (structure-type-specification-has-details-p ,superior-type)))
     (cond
       ((and type-has-details-p superior-type-has-details-p)
	(let* ((minimum-contents-of-superior
		 (structure-type-specification-minimum-contents ,superior-type))
	       (augmented-type
		 (make-augmented-structure-type-specification ,type ,superior-type))
	       (augmented-superior-type
		 (make-augmented-structure-type-specification ,superior-type ,type))
	       (slot-list-of-type
		 (structure-type-specification-slot-list augmented-type))
	       (slot-list-of-superior-type
		 (structure-type-specification-slot-list augmented-superior-type))
	       (slot-type-cache nil)
	       (ok-p nil))
	  (block test-loop
	    (do-structure-type-specification-tuples (tuple augmented-type)
	      (when (and
		      (or (null minimum-contents-of-superior)
			  (slot-name-list-meets-minimum-structure-requirements-p
			    minimum-contents-of-superior tuple))
		      (loop for name in tuple
			    as cache-entry? = (assq name slot-type-cache)
			    always
			    (cond
			      (cache-entry? (cdr cache-entry?))
			      (t
			       (let* ((type-spec-of-slot
					(cadr (assq name slot-list-of-type)))
				      (type-spec-of-slot-in-superior
					(cadr (assq name slot-list-of-superior-type)))
				      (new-cached-type-test
					(,(if in-kb-p
					      'type-specifications-could-intersect-in-kb-p
					      'type-specifications-could-intersect-p)
					  type-spec-of-slot type-spec-of-slot-in-superior)))
				 (gensym-push
				   (gensym-cons name new-cached-type-test)
				   slot-type-cache)
				 new-cached-type-test)))))
		(setf ok-p t)
		(return-from test-loop nil))))
	  (reclaim-gensym-tree augmented-type)
	  (reclaim-gensym-tree augmented-superior-type)
	  ok-p))
       (t
	;; if not details on either type than one type must imply "any structure"
	;; and therefore encompass the other
	t))))

(defun-simple structure-type-specifications-could-intersect-in-kb-p (type superior-type)
  (make-structure-type-intersection-predicate type superior-type t))

(defmacro make-structure-not-subtype-predicate (type superior-type in-kb-p)
  (unless (and (symbolp type) (symbolp superior-type))
    (error "this is not a general purpose macro yet.  It assumes args are symbols"))
  `(let* ((type-has-details-p
	    (structure-type-specification-has-details-p ,type))
	  (superior-type-has-details-p
	    (structure-type-specification-has-details-p ,superior-type)))
     (cond
       (type-has-details-p
	(cond
	  (superior-type-has-details-p
	   (let ((minimum-contents-of-superior
		   (structure-type-specification-minimum-contents ,superior-type))
		 (slot-list-of-type
		   (structure-type-specification-slot-list ,type))
		 (slot-list-of-superior-type
		   (structure-type-specification-slot-list ,superior-type))
		 (slot-type-cache nil)
		 (not-subtype-p nil))
	     (block test-loop
	       (do-structure-type-specification-tuples (tuple type)
;		 (format t "tuple=~s~%" tuple)
		 (when (cond
			 ;; does it meet the min requirements of the type
			 ((or (null minimum-contents-of-superior)
			      (slot-name-list-meets-minimum-structure-requirements-p
				minimum-contents-of-superior tuple))
			  ;; does the set of names have any slots that
			  ;; are not subtype
			  (cond ((loop for name in tuple
				       as cache-entry? = (assq name slot-type-cache)
				       thereis
				       (cond
					 (cache-entry? (cdr cache-entry?))
					 (t
					  (let* ((type-spec-of-slot
						   (cadr (assq name slot-list-of-type)))
						 (type-spec-of-slot-in-superior?
						   (cadr (assq name slot-list-of-superior-type)))
						 (new-cached-type-test
						   ;; if slot is not mentioned in superior
						   ;; slot could be present and have any value
						   ;; therefore type-spec-of-slot is implicitly a subtype
						   ;; therefore (NOT (NOT-subtype-p))
						   ;; therefore the following and
						   (and type-spec-of-slot-in-superior?
							(,(if in-kb-p
							      'type-specification-not-subtype-in-kb-p
							      'type-specification-not-subtype-p)
							  type-spec-of-slot type-spec-of-slot-in-superior?))))
					    (gensym-push
					      (gensym-cons name new-cached-type-test)
					      slot-type-cache)
					    new-cached-type-test))))
				 t)
				(t
				 nil)))
			 (t ; doesn't meet slot requirements so this tuple's not a subtype
			  t))
		   (setf not-subtype-p t)
		   (return-from test-loop nil))))
	     not-subtype-p))
	  (t ; it's (structure <details>) is a subtype of (structure)
	   nil)))
       (superior-type-has-details-p
	;; not all (structure)'s are (structure <details>)
	t)
       (t
	nil))))

(defun-simple structure-type-specification-not-subtype-in-kb-p (type superior-type)
  (make-structure-not-subtype-predicate type superior-type t))


(defun-simple detailed-evaluation-structure-type-p (structure type-specification)
  (let ((slot-specifications
	  (structure-type-specification-slot-list type-specification))
	(minimum-contents
	  (structure-type-specification-minimum-contents type-specification)))
    (and
      ;; test to see if all slots present in structure are specified in
      ;; the type and are of the correct type
      (loop for (name . value) being evaluation-structure-pair of structure
	    as slot-specification? = (assq name slot-specifications)
	    always (and slot-specification?
			(type-specification-type-p
			  value (cadr slot-specification?))))
      ;; see if the structure is as complete as the minimum-contents requires
      (or (null minimum-contents)
	  (eval-minimum-structure-contents minimum-contents structure)))))

(defun-simple eval-minimum-structure-contents (boolean-expression structure)
  (cond ((consp boolean-expression)
	 (case (car-of-cons boolean-expression)
	   (and
	    (loop for conjunct in (cdr-of-cons boolean-expression) 
		  always (eval-minimum-structure-contents conjunct structure)))
	   (or
	    (loop for disjunct in (cdr-of-cons boolean-expression)
		  thereis (eval-minimum-structure-contents disjunct structure)))
	   (not
	    (not (eval-minimum-structure-contents (cadr boolean-expression) structure)))))
	((symbolp boolean-expression)
	 (evaluation-structure-slot structure boolean-expression))
	(t
	 #+development
	 (cerror "go on" "bad minimum-structure-contents expression")
	 nil)))


#+development
(defparameter validation-suite-for-structure-type-predicates
  '(((structure)
     (structure)
     (t t nil))
    ((structure ((slot-a integer)) nil)
     (structure)
     (t t nil))
    ((structure)
     (structure ((slot-a integer)) nil)
     (nil t t))
    ((structure ((slot-a integer)) nil)
     (structure ((slot-a datum)) nil)
     (t t nil))
    ((structure ((slot-a integer)) (and slot-a))
     (structure ((slot-a datum)) nil)
     (t t nil))
    ((structure ((slot-a integer)) nil)
     (structure ((slot-a datum)) (and slot-a))
     (nil t t))
    ((structure ((foo truth-value) (bar (member red green blue))) (and foo bar))
     (structure ((foo truth-value)) (and foo))
     (t t nil))
    ((structure ((foo truth-value)) (and foo))
     (structure ((foo truth-value) (bar (member red green blue))) (and foo bar))
     (nil t t))))

#+development
(defun validate-structure-type-predicates ()
  (loop for (ts1 ts2 (subtype-p intersect-p not-subtype-p))
	    in validation-suite-for-structure-type-predicates
	do
    (format t "For type-specification=~s and ~%         superior-type=~s:~%"
	    ts1 ts2)
    (let ((res (structure-type-specification-subtype-in-kb-p ts1 ts2)))
      (format t "     subtype-in-kb-p => ~s :  ~50T~s~%"
	      res (if (eq res subtype-p) 'good 'bad)))
    (let ((res (structure-type-specifications-could-intersect-in-kb-p ts1 ts2)))
      (format t "     could-intersect-in-kb-p => ~s :  ~50T~s~%"
	      res (if (eq res intersect-p) 'good 'bad)))
    (let ((res (structure-type-specification-not-subtype-in-kb-p ts1 ts2)))
      (format t "     not-subtype-in-kb-p => ~s :  ~50T~s~%"
	      res (if (eq res not-subtype-p) 'good 'bad)))))
   



;;;; Aggregate Value Type Specification and Access.



;;; There are modules of G2 that want somewhat generic access to the internals
;;; of structures and sequnces, e.g. KB save/load.  The following macros and functions
;;; present this low-level interface.


;;; The function `aggregate-value-type-specification-p' is a hack used to note
;;; all uses of the new aggregate value types (lists arrays structures) in the
;;; special cases that currently support their use.

(defun-simple aggregate-value-type-specification-p (type-specification)
  (and (consp type-specification)
       (let ((type-name (car-of-cons type-specification)))
	 (or (eq type-name 'structure)
	     (eq type-name 'sequence)))))
;	 (defined-evaluation-datum-type-p type-name))))

(defmacro aggregate-value-type-specification-has-details-p (type-specification)
  `(cdr-of-cons ,type-specification))

(defun-simple aggregate-evaluation-value-p (thing)
  (and (consp thing)
       (managed-array-p (car-of-cons thing))
       (let ((cdr (cdr-of-cons thing)))
	 (or (eq cdr 'structure)
	     (eq cdr 'sequence)))))

(defmacro aggregate-evaluation-value-type-symbol (evaluation-value)
  `(cdr-of-cons ,evaluation-value))

(defmacro aggregate-evaluation-value-reference-count (x)
  `(managed-svref (car-of-cons ,x) 0))






;;;; Evaluation Values




;;; The macro `make-evaluation-value' takes a value and a type and returns an
;;; evaluation value encapsulating that value.

;;; The function `make-evaluation-value-reclaiming-argument' takes a value and a
;;; type, and makes an evaluation value.  If the value was a raw value which
;;; needs reclaiming (of which text is the only current example), that value is
;;; incorporated into the resulting evaluation-value.

;;; The function `reclaim-evaluation-value' takes an evaluation-value and
;;; reclaims it.

;;; The macro `copy-evaluation-value' takes an evaluation-value and returns a
;;; newly allocated evaluation-value encapsulating the same datum.

;;; The macro `evaluation-value-value' returns returns the value encapsulated
;;; within the evaluation value.  Note that the type of the value must be
;;; extracted separately, since truth-values and integers both return fixnums
;;; from this operation.

;;; The macro `evaluation-value-type' takes an evaluation-value and returns a
;;; symbol naming the type of that value.  The symbols returned are integer,
;;; float, text, symbol, and truth-value.  Note that number will never be
;;; returned since every quantity is actually either a float or an integer
;;; underneath it all.

;;; The macro `evaluation-value-p' takes a thing and returns whether or not it
;;; is an evaluation value.

;;; Note that this will not be conclusive, in that some normal chunks-o-data
;;; sort of look like evaluation-values.  We don't currently forsee a use for
;;; this predicate, and so aren't going the make the representations for
;;; evaluation-values larger in order to support a conclusive version of this
;;; predicate.  -jra & cpm 2/27/91

;;; The function `write-evaluation-value' takes an evaluation value and twrites
;;; it as print-constant would.

;;; The functions `evaluation-value-=' and `evaluation-value-/=' are
;;; evaluation-value comparitors of two evaluation-values which return
;;; evaluation truth values.  When one of the arguments is a float and the other
;;; is an integer, the integer is coerced to float.  These functions should be
;;; called within a TEMPORARY-AREA since this coercion creates a new
;;; gensym-float.  Note, that strings are compared using g2-text comparsions,
;;; such as g2-text-equal.  This allows the comparison of strings that contain
;;; complex G2 characters, such as international characters.

(defun-simple make-evaluation-value-1 (value type)
  #+development
  (let ((type1 (if (and (symbolp type)
			(number-subtype-p type)
			(not (memq type '(number integer float))))
		   'number
		   type)))
    (when (cond ((eq type1 'float)
		 (not (gensym-float-p value)))
		((eq type1 'long)
		 (not (gensym-long-p value)))
		((eq type1 'integer)
		 (not (fixnump value)))
		((eq type1 'number)
		 (not (or (gensym-float-p value)
			  (gensym-long-p value)
			  (fixnump value))))
		((or (eq type1 'boolean) (eq type1 'truth-value))
		 (not (fixnump value)))
		((eq type1 'text)
		 (not (text-string-p value)))
		((eq type1 'symbol)
		 (not (symbolp value)))
		(t
		 t))
      (signal-development-bad-value-for-make-evaluation-value value type -1)))
  (case type
    ((float)
     (make-evaluation-float value))
    ((integer)
     (make-evaluation-integer value))
    ((long)
     (make-evaluation-long value))
    ((number)
     (make-evaluation-quantity value))
    ((truth-value boolean)
     (make-evaluation-truth-value value))
    ((symbol)
     (make-evaluation-symbol value))
    ((text)
     (make-evaluation-text value))
    (t
     (cond ((number-subtype-p type)
	    (make-evaluation-quantity value))
	   (t
	    #+development
	    (error "Invalid type ~a given to make-evaluation-value." type)
	    value)))))

(defmacro make-evaluation-value (value type-of-value)
  (if (constantp type-of-value)
      (let ((type (eval type-of-value)))
	(case type
	  ((number)
	   `(make-evaluation-quantity ,value))
	  ((float)
	   `(make-evaluation-float ,value))
	  ((integer)
	   `(make-evaluation-integer ,value))
          ((long)
	   `(make-evaluation-long ,value))
	  ((symbol)
	   `(make-evaluation-symbol ,value))
	  ((truth-value boolean)
	   `(make-evaluation-truth-value ,value))
	  ((text)
	   `(make-evaluation-text ,value))
	  (t
	   (error "Invalid type ~a given to make-evaluation-value." type))))
      `(make-evaluation-value-1 ,value ,type-of-value)))

;;; `make-evaluation-value-base-on-type' exists to help
;;; system procedures return values of type datum.  Sorry,
;;; but it doesn't handle fuzzy truth values yet.

(defmacro make-evaluation-value-based-on-type (value)
  (avoiding-variable-capture (value)
    `(cond ((fixnump ,value)
	    (make-evaluation-integer ,value))
	   ((null ,value)
	    evaluation-false-value)
	   ((eq ,value t)
	    evaluation-true-value)
	   ((symbolp ,value)
	    (make-evaluation-symbol ,value))
	   ((managed-float-p ,value)
	    (copy-managed-float-into-evaluation-float ,value))
	   ((gensym-float-p ,value)
	    (make-evaluation-float ,value))
           ((managed-long-p ,value)
	    (copy-managed-long-into-evaluation-long ,value))
           ((gensym-long-p ,value)
	    (make-evaluation-long ,value))
	   ((text-string-p ,value)
	    (make-evaluation-text ,value))
	   ((evaluation-truth-value-p ,value)
	    (make-evaluation-truth-value
	      (evaluation-truth-value-value ,value)))
	   (t
	    (error "Bad type ~a for make-evaluation-value-based-on-type."
		   (type-of ,value))))))
	     
(defun-simple make-evaluation-value-from-lisp-value (value)
  (cond ((evaluation-sequence-p value)
	 value)
	((evaluation-structure-p value)
	 value)
	((evaluation-item-reference-p value)
	 (get-item-if-item-reference value))
	((framep value)
	 value)
	(t
	 (make-evaluation-value-based-on-type value))))

(defun-simple make-evaluation-value-reclaiming-argument (value type-of-value)
  (case type-of-value
    ((number)
     (make-evaluation-quantity value))
    ((float)
     (make-evaluation-float value))
    ((long)
     (make-evaluation-long value))
    ((integer)
     (make-evaluation-integer value))
    ((symbol)
     (make-evaluation-symbol value))
    ((truth-value boolean)
     (make-evaluation-truth-value value))
    ((text)
     (make-evaluation-text-reclaiming-argument value))
    (t
     (error "Invalid type ~a given to make-evaluation-value." type-of-value))))

(defun-simple reclaim-evaluation-value (evaluation-value)
  (cond
    ;; The consp check is done with knowledge about the implementation types of
    ;; evaluation-truth-values, etc.  If the representations for these change,
    ;; then this code will need to change.  -jra & cpm 2/27/91
    ((consp evaluation-value)
     (let ((cdr (cdr-of-cons evaluation-value)))
       (cond ((cdr-of-evaluation-truth-value-p cdr)
	      (reclaim-evaluation-truth-value evaluation-value))
	     ((cdr-of-evaluation-iteration-state-p cdr)
	      (reclaim-evaluation-iteration-state evaluation-value))
	     ((defined-evaluation-value-type-p cdr)
	      (funcall-simple-compiled-function
		(defined-evaluation-type-reclaimer cdr)
		evaluation-value))
	     #+development
	     (t
	      (error
		"Unrecognized arg to Reclaim-Evaluation-Value.")))))
    ((evaluation-float-p evaluation-value)
     (reclaim-evaluation-float evaluation-value))
    ((evaluation-long-p evaluation-value)
     (reclaim-evaluation-long evaluation-value))
    ((evaluation-text-p evaluation-value)
     (reclaim-evaluation-text evaluation-value))
    ;; The following are all noops now.  -jra & cpm 2/7/91
    #+development
    ((evaluation-symbol-p evaluation-value)
     (reclaim-evaluation-symbol evaluation-value))
    #+development
    ((evaluation-integer-p evaluation-value)
     (reclaim-evaluation-integer evaluation-value))
    #+development
    (t
     (error "Unrecognized arg to Reclaim-Evaluation-Value.")))
  nil)

;; The above was changed from a macro to a function at least for now.  -jra
;; 3/12/91



#+unused
(defun-simple reclaim-evaluation-value-function (evaluation-value)
  (reclaim-evaluation-value evaluation-value))

(def-substitution-macro reclaim-if-evaluation-value (thing)
  (unless (or (fixnump thing)
	      (symbolp thing)
	      (simple-vector-p thing)) ; Frames.  -jra 8/5/96
    (reclaim-if-evaluation-value-1 thing)))

(defun-simple reclaim-if-evaluation-value-function (thing)
  (reclaim-if-evaluation-value thing))

(defun-simple reclaim-if-evaluation-value-1 (thing)
  (cond
    ;; The consp check is done with knowledge about the implementation types of
    ;; evaluation-truth-values, etc.  If the representations for these change,
    ;; then this code will need to change.  -jra & cpm 2/27/91
    ((consp thing)
     (let ((cdr (cdr-of-cons thing)))
       (cond ((cdr-of-evaluation-truth-value-p cdr)
	      (reclaim-evaluation-truth-value thing))
	     ((cdr-of-evaluation-iteration-state-p cdr)
	      (reclaim-evaluation-iteration-state thing))
	     ((defined-evaluation-value-type-p cdr)
	      (funcall-simple-compiled-function
		(defined-evaluation-type-reclaimer cdr)
		thing)))))
    ((evaluation-float-p thing)
     (reclaim-evaluation-float thing))
    ((evaluation-long-p thing)
     (reclaim-evaluation-long thing))
    ((evaluation-text-p thing)
     (reclaim-evaluation-text thing))
    ;; The following are noops now.  -jra & cpm 2/7/91
    #+development
    ((evaluation-symbol-p thing)
     (reclaim-evaluation-symbol thing))
    #+development
    ((evaluation-integer-p thing)
     (reclaim-evaluation-integer thing)))
  
  nil)

(defun-simple reclaim-eval-list-of-item-or-datum (list)
  (when list
    (loop for trailer = nil then cons
	  for cons = list then (cdr-of-cons cons)
	  while cons
	  do
	    (reclaim-if-evaluation-value (car-of-cons cons))
	  finally
	    (reclaim-eval-list-given-tail list trailer)))
  nil)

(defun-simple copy-evaluation-value-1 (evaluation-value)
  (cond
    ;; The consp check is done with knowledge about the implementation types of
    ;; evaluation-truth-values, etc.  If the representations for these change,
    ;; then this code will need to change.  -jra & cpm 2/27/91
    ((consp evaluation-value)
     (let ((cdr (cdr-of-cons evaluation-value)))
       (cond ((cdr-of-evaluation-truth-value-p cdr)
	      (copy-evaluation-truth-value evaluation-value))
	     ((cdr-of-evaluation-iteration-state-p cdr)
	      (copy-evaluation-iteration-state evaluation-value))
	     ((defined-evaluation-value-type-p cdr)
	      (funcall-simple-compiled-function
		(defined-evaluation-type-copier cdr)
		evaluation-value))
	     #+development
	     (t
	      (error
		"Unrecognized arg to Copy-Evaluation-Value.")))))
    ((evaluation-float-p evaluation-value)
     (copy-evaluation-float evaluation-value))
    ((evaluation-long-p evaluation-value)
     (copy-evaluation-long evaluation-value))
    ((evaluation-text-p evaluation-value)
     (copy-evaluation-text evaluation-value))
    #+development
    (t
     (error "Unrecognized arg to Copy-Evaluation-Value."))
    #-development
    (t evaluation-value)))

(defun-simple deep-copy-evaluation-value-1 (evaluation-value)
  (cond
    ;; The consp check is done with knowledge about the implementation types of
    ;; evaluation-truth-values, etc.  If the representations for these change,
    ;; then this code will need to change.  -jra & cpm 2/27/91
    ((consp evaluation-value)
     (let ((cdr (cdr-of-cons evaluation-value)))
       (cond ((cdr-of-evaluation-truth-value-p cdr)
	      (copy-evaluation-truth-value evaluation-value))
	     ((cdr-of-evaluation-iteration-state-p cdr)
	      (copy-evaluation-iteration-state evaluation-value))
	     ((defined-evaluation-value-type-p cdr)
	      (funcall-simple-compiled-function
		(or (defined-evaluation-type-deep-copier cdr)
		    (defined-evaluation-type-copier cdr))
		evaluation-value))
	     #+development
	     (t
	      (error
		"Unrecognized arg to Copy-Evaluation-Value.")))))
    ((evaluation-float-p evaluation-value)
     (copy-evaluation-float evaluation-value))
    ((evaluation-long-p evaluation-value)
     (copy-evaluation-long evaluation-value))
    ((evaluation-text-p evaluation-value)
     (copy-evaluation-text evaluation-value))
    #+development
    (t
     (error "Unrecognized arg to Copy-Evaluation-Value."))
    #-development
    (t evaluation-value)))

(def-substitution-macro copy-evaluation-non-logical-datum-macro
			(evaluation-value)
  (cond ((evaluation-float-p evaluation-value)
	 (copy-evaluation-float evaluation-value))
        ((evaluation-long-p evaluation-value)
         (copy-evaluation-long evaluation-value))
	((evaluation-text-p evaluation-value)
	 (copy-evaluation-text evaluation-value))
	#+development
	((evaluation-integer-p evaluation-value)
	 (copy-evaluation-integer evaluation-value))
	#+development
	((evaluation-symbol-p evaluation-value)
	 (copy-evaluation-symbol evaluation-value))
	((consp evaluation-value)
	 (let ((cdr (cdr-of-cons evaluation-value)))
	   (cond ((eq cdr 'structure)
		  (copy-evaluation-structure evaluation-value))
		 ((eq cdr 'sequence)
		  (copy-evaluation-sequence evaluation-value))
		 (t
		  #+development
		  (cerror
		    "Continue"
		    "Copy-evaluation-non-logical-datum got an incorrect type ~a."
		    evaluation-value)
		  evaluation-value))))
	#+development
	(t
	 (cerror
	   "Continue"
	   "Copy-evaluation-non-logical-datum got an incorrect type ~a."
	   evaluation-value))
	#-development
	(t evaluation-value)))

(defun-simple copy-if-evaluation-value-1 (thing)
  (cond
    ;; The consp check is done with knowledge about the implementation types of
    ;; evaluation-truth-values, etc.  If the representations for these change,
    ;; then this code will need to change.  -jra & cpm 2/27/91
    ((consp thing)
     (let ((cdr (cdr-of-cons thing)))
       (cond ((cdr-of-evaluation-truth-value-p cdr)
	      (copy-evaluation-truth-value thing))
	     ((cdr-of-evaluation-iteration-state-p cdr)
	      (copy-evaluation-iteration-state thing))
	     ((defined-evaluation-value-type-p cdr)
	      (funcall-simple-compiled-function
		(defined-evaluation-type-copier cdr)
		thing))
	     (t thing))))
    ((evaluation-float-p thing)
     (copy-evaluation-float thing))
    ((evaluation-long-p thing)
     (copy-evaluation-long thing))
    ((evaluation-text-p thing)
     (copy-evaluation-text thing))
    ;; The following are noops now.  -jra & cpm 2/7/91
    #+development
    ((evaluation-symbol-p thing)
     (copy-evaluation-symbol thing))
    #+development
    ((evaluation-integer-p thing)
     (copy-evaluation-integer thing))
    (t
     thing)))

(defun-simple deep-copy-if-evaluation-value-1 (thing)
  (cond
    ;; The consp check is done with knowledge about the implementation types of
    ;; evaluation-truth-values, etc.  If the representations for these change,
    ;; then this code will need to change.  -jra & cpm 2/27/91
    ((consp thing)
     (let ((cdr (cdr-of-cons thing)))
       (cond ((cdr-of-evaluation-truth-value-p cdr)
	      (copy-evaluation-truth-value thing))
	     ((cdr-of-evaluation-iteration-state-p cdr)
	      (copy-evaluation-iteration-state thing))
	     ((defined-evaluation-value-type-p cdr)
	      (funcall-simple-compiled-function
		(or (defined-evaluation-type-deep-copier cdr)
		    (defined-evaluation-type-copier cdr))
		      thing))
	     (t thing))))
    ((evaluation-float-p thing)
     (copy-evaluation-float thing))
    ((evaluation-long-p thing)
     (copy-evaluation-long thing))
    ((evaluation-text-p thing)
     (copy-evaluation-text thing))
    ;; The following are noops now.  -jra & cpm 2/7/91
    #+development
    ((evaluation-symbol-p thing)
     (copy-evaluation-symbol thing))
    #+development
    ((evaluation-integer-p thing)
     (copy-evaluation-integer thing))
    (t
     thing)))

(declare-side-effect-free-function evaluation-value-value)

(defun-simple evaluation-value-value (evaluation-value)
  (cond
    ;; The consp check is done with knowledge about the implementation types of
    ;; evaluation-truth-values, etc.  If the representations for these change,
    ;; then this code will need to change.  -jra & cpm 2/27/91
    ((consp evaluation-value)
     (let ((cdr (cdr-of-cons evaluation-value)))
       (cond ((cdr-of-evaluation-truth-value-p cdr)
	      (evaluation-truth-value-value evaluation-value))
	     ((cdr-of-evaluation-iteration-state-p cdr)
	      (evaluation-iteration-state-continuation evaluation-value))
	     ((defined-evaluation-value-type-p cdr)
	      (car-of-cons evaluation-value))
	     #+development
	     (t
	      (error
		"Unrecognized arg to Evaluation-Value-Value.")))))
    ((evaluation-float-p evaluation-value)
     (evaluation-float-value evaluation-value))
    ((evaluation-long-p evaluation-value)
     (evaluation-long-value evaluation-value))
    ;; The following are all noops now.  -jra & cpm 2/7/91
    #+development
    ((evaluation-text-p evaluation-value)
     (evaluation-text-value evaluation-value))
    #+development
    ((evaluation-symbol-p evaluation-value)
     (evaluation-symbol-symbol evaluation-value))
    #+development
    ((evaluation-integer-p evaluation-value)
     (evaluation-integer-value evaluation-value))
    ;; The following clause for NIL was grudgingly put in to let slide lots and
    ;; lots of bugs which showed up when evaluation-symbol-p was corrected to
    ;; reject NIL.  NIL is not an evaluation value, but it is such a common
    ;; error at this point to call this function with NIL that this function
    ;; will just return NIL for its value.  -jra 8/23/91
    #+development
    ((null evaluation-value)
     nil)
    #+development
    (t
     (error "Unrecognized arg to Evaluation-Value-Value."))
    #-development
    (t evaluation-value)))

(declare-side-effect-free-function evaluation-value-type)

(defun-simple evaluation-value-type (evaluation-value)
  (cond
    ((evaluation-integer-p evaluation-value)
     'integer)
    ;; The consp check is done with knowledge about the implementation types of
    ;; evaluation-truth-values, etc.  If the representations for these change,
    ;; then this code will need to change.  -jra & cpm 2/27/91
    ((consp evaluation-value)
     (let ((cdr (cdr-of-cons evaluation-value)))
       (cond ((cdr-of-evaluation-truth-value-p cdr)
	      'truth-value)
	     ((cdr-of-evaluation-iteration-state-p cdr)
	      '(iteration-state))
	     ((defined-evaluation-value-type-p cdr)
	      (type-specification-of-defined-evaluation-type cdr))
	     #+development
	     (t
	      (error
		"Unrecognized arg to Evaluation-Value-Type.")))))
    ((evaluation-float-p evaluation-value)
     'float)
    ((evaluation-long-p evaluation-value)
     'long)
    ((evaluation-symbol-p evaluation-value)
     'symbol)
    ((evaluation-text-p evaluation-value)
     'text)
    #+development
    (t
     (error "Unrecognized arg to Evaluation-Value-Type."))))




;;; The macro `evaluation-value-p-given-register' is used in the stack evaluator
;;; to implement evaluation-value-p without having it generate new LET bindings.

;; Note that I'm also avoiding OR since its Chestnut compile also generates
;; lots of extra temporary variables.  -jra 7/22/91

(defmacro evaluation-value-p-given-register (value register)
  (if (not (symbolp value))
      `(progn
	 (setq ,register ,value)
	 (evaluation-value-p-given-register ,register ,register))
      `(or (evaluation-integer-p ,value)
	   (evaluation-float-p ,value)
           (evaluation-long-p ,value)
	   (evaluation-symbol-p ,value)
	   (evaluation-text-p ,value)
	   (and (consp ,value)
		(progn
		  (setq ,register (cdr-of-cons ,value))
		  (or (cdr-of-evaluation-truth-value-p ,register)
		      (cdr-of-evaluation-iteration-state-p ,register)
		      (defined-evaluation-value-type-p ,register)))))))

(declare-side-effect-free-function evaluation-value-p-function)

(defmacro evaluation-value-p (evaluation-value)
  (let ((register (gensym)))
    `(let ((,register ,evaluation-value))
       (evaluation-value-p-given-register ,register ,register))))

(defun-simple evaluation-value-p-function (evaluation-value)
  (evaluation-value-p evaluation-value))




;;; The substitution macro `evaluation-datum-p' takes a thing and
;;; determines if it is a evaluation value kind of datum.

(defmacro evaluation-datum-p-given-register (thing register)
  (if (not (symbolp thing))
      `(progn
	 (setq ,register ,thing)
	 (evaluation-datum-p-given-register ,register ,register))
      `(or (evaluation-integer-p ,thing)
	   (evaluation-float-p ,thing)
           (evaluation-long-p ,thing)
	   (evaluation-symbol-p ,thing)
	   (evaluation-text-p ,thing)
	   (and (consp ,thing)
		(progn
		  (setq ,register (cdr-of-cons ,thing))
		  (or (cdr-of-evaluation-truth-value-p ,register)
		      (defined-evaluation-datum-type-p ,register)))))))

(defmacro evaluation-datum-p (thing)
  (let ((register (gensym)))
    `(let ((,register ,thing))
       (evaluation-datum-p-given-register ,register ,register))))

;;; The function `item-or-value-equalp' takes two item-or-values and returns T 
;;; if they are eq frames or equalp evaluation values.  It calls the function
;;; `evaluation-value-=' which takes two evaluation values and tests if they
;;; have equivalent values.  In this sense it is similar to Common Lisp EQUALP.
;;; It differs from `evaluation-value-eql' in that this function will compare
;;; numbers of different types and is case insensitive.

(defun-simple item-or-value-equalp (item-or-value-1 item-or-value-2)
  (or (eq item-or-value-1 item-or-value-2)
      (and (not (framep item-or-value-1))  ;; because it failed the eq test 
	   (evaluation-value-= item-or-value-1 item-or-value-2))))

(defun-simple evaluation-value-= (evaluation-value-1 evaluation-value-2)
  (cond ((null evaluation-value-1)
	 (null evaluation-value-2))
	((null evaluation-value-2)
	 nil)
        ((evaluation-quantity-p evaluation-value-1)
	 (and (evaluation-quantity-p evaluation-value-2)
	      (evaluation-quantity-= evaluation-value-1 evaluation-value-2)))
	((evaluation-symbol-p evaluation-value-1)
	 (and (evaluation-symbol-p evaluation-value-2)
	      (eq (evaluation-symbol-symbol evaluation-value-1)
		  (evaluation-symbol-symbol evaluation-value-2))))
	((evaluation-text-p evaluation-value-1)
	 ;; Strings are compared as g2-text since they may contain complex G2
	 ;; characters, e.g., international characters.
	 (and (evaluation-text-p evaluation-value-2)
	      (g2-text-equal
		   (evaluation-text-value evaluation-value-1)
		   (evaluation-text-value evaluation-value-2))))
	((evaluation-truth-value-p evaluation-value-1)
	 (and (evaluation-truth-value-p evaluation-value-2)
	      (=f (evaluation-truth-value-value evaluation-value-1)
		  (evaluation-truth-value-value evaluation-value-2))))
	((evaluation-iteration-state-p evaluation-value-1)
	 ;; Iteration states are never equal to anything.
	 nil)
	;; The following case will handle the comparison of all new aggregate
	;; datum/value types
	((and (consp evaluation-value-1) ; this may be paranoid
	      (evaluation-datum-p evaluation-value-1))
	 (let* ((type-of-value-1 (type-specification-of-defined-evaluation-type
				   (cdr-of-cons evaluation-value-1))))
	   (and (type-specification-type-p evaluation-value-2 type-of-value-1)
		(evaluation-value-of-type-=
		  type-of-value-1 evaluation-value-1 evaluation-value-2))))
	(t
	 ;; We should not get here unless there are new evaluation-value data
	 ;; types.
	 #+development
	 (cerror "continue" "Unknown evaluation-value type in evaluation-value-=.")
	 nil)))

(defun-simple evaluation-values-can-be-constant-folded-p
	      (evaluation-value-1 evaluation-value-2)
  (evaluation-value-eql evaluation-value-1 evaluation-value-2 t))

;;; The function `evaluation-value-eql' takes two evaluation values and tests if
;;; they are the same evaluation value type and have equivalent values.  In this
;;; sense it is similar to Common Lisp EQL.  It differs from evaluation-value-=
;;; in that this function will not compare numbers of different types, it is
;;; case sensitive, and it returns T or NIL instead of an
;;; evaluation-truth-value.  The function `item-or-value-eql' takes two
;;; item-or-values, and returns if they are eq frames or eql evaluation values.
;;; The function 'evaluation-value-eql' also takes an optional third argument which defaults to nil
;;; This argument if true 't' will do a case sensitive text comparison by using function 'string=w' instead
;;; of the function string-equalw.

(defun-simple item-or-value-eql (item-or-value-1 item-or-value-2)
  (if (framep item-or-value-1)
      (eq item-or-value-1 item-or-value-2)
      (and (not (framep item-or-value-2))
	   (evaluation-value-eql item-or-value-1 item-or-value-2))))

(defun evaluation-value-eql (evaluation-value-1 evaluation-value-2 &optional (is-case-sensitive-p nil))
  (or (eq evaluation-value-1 evaluation-value-2)
      (cond
	;; The consp check is done with knowledge about the implementation types
	;; of evaluation-truth-values, etc.  If the representations for these
	;; change, then this code will need to change.  -jra & cpm 2/27/91
	((consp evaluation-value-1)
	 (let ((cdr (cdr-of-cons evaluation-value-1)))
	   (cond ((cdr-of-evaluation-truth-value-p cdr)
		  (and (evaluation-truth-value-p evaluation-value-2)
		       (=f (evaluation-truth-value-value evaluation-value-1)
			   (evaluation-truth-value-value evaluation-value-2))))
		 ((cdr-of-evaluation-iteration-state-p cdr)
		  nil)
		 ((defined-evaluation-value-type-p cdr)
		  (if (and (consp evaluation-value-2)
			   (eq cdr (cdr-of-cons evaluation-value-2)))
		      (let ((comparitor?
			      (defined-evaluation-type-comparitor cdr)))
			(cond (comparitor?
			       (funcall-simple-compiled-function
				 comparitor? evaluation-value-1
				 evaluation-value-2))
			      (t
			       #+development
			       (cerror
				 "Continue"
				 "Evaluation value type ~a has no comparitor."
				 cdr)
			       nil)))))
		 #+development
		 (t
		  (error
		    "Unrecognized arg to Evaluation-Value-Type.")))))
	((evaluation-float-p evaluation-value-1)
	 (and (evaluation-float-p evaluation-value-2)
	      (=e (evaluation-float-value evaluation-value-1)
		  (evaluation-float-value evaluation-value-2))))
	((evaluation-text-p evaluation-value-1)
	 (and (evaluation-text-p evaluation-value-2)
	      (if is-case-sensitive-p 
		  (string=w (evaluation-text-value evaluation-value-1)                   
			    (evaluation-text-value evaluation-value-2))
		(string-equalw (evaluation-text-value evaluation-value-1)
			       (evaluation-text-value evaluation-value-2)))))
	;; The following clauses for symbols and fixnums are made unnecessary
	;; by the initial EQ test, but are included for completeness when
	;; symbols and integers are made into something other than Lisp
	;; symbols and fixnums.
	((evaluation-symbol-p evaluation-value-1)
	 (eq evaluation-value-1 evaluation-value-2))
	((evaluation-integer-p evaluation-value-1)
	 (and (evaluation-integer-p evaluation-value-2)
	      (=f (evaluation-integer-value evaluation-value-1)
		  (evaluation-integer-value evaluation-value-2))))
	((evaluation-long-p evaluation-value-1)
	 (and (evaluation-long-p evaluation-value-2)
	      (=l (evaluation-long-value evaluation-value-1)
		  (evaluation-long-value evaluation-value-2))))
	#+development
	(t
	 (error "Unrecognized arg to Evaluation-Value-Type.")))))

;;; The function `evaluation-value-equal-p' takes two evaluation values and
;;; tests if they are the same evaluation value type and have equivalent values,
;;; ignoring case for text.  This function returns T or NIL, not an evaluation-
;;; truth-value.

(defun-simple evaluation-value-equal-p (evaluation-value-1 evaluation-value-2)
  (if (evaluation-text-p evaluation-value-1)
      (and (evaluation-text-p evaluation-value-2)
	   (g2-text-equal (evaluation-text-value evaluation-value-1)
			  (evaluation-text-value evaluation-value-2)))
      (evaluation-value-eql evaluation-value-1 evaluation-value-2)))



;;; The macro `managed-value-eql' compares two managed values to see if they
;;; are equivalent values.  Because of current implementation considerations,
;;; it happens that this is exactly the same check evaluation-value-eql, and so
;;; this macro expands into a call to that function.

(defmacro managed-value-eql (managed-value-1 managed-value-2)
  `(evaluation-value-eql ,managed-value-1 ,managed-value-2))




;;; The following functions copy values back and forth between evaluation-value
;;; and temporary-constant formats.  All temporary-constants here are made with
;;; expirations of NEVER.  Note that these operations should be called from
;;; within a temporary consing context.

(defun-simple make-temporary-constant-from-evaluation-value (evaluation-value)
  #+development
  (when (evaluation-iteration-state-p evaluation-value)
    (error "Attempting to copy an iteration state into a temporary constant."))
  (make-temporary-constant-copying-managed-value-no-expiration
    (if (evaluation-truth-value-p evaluation-value)
	(evaluation-truth-value-value evaluation-value)
	evaluation-value)
    (evaluation-value-type evaluation-value)))

(defun-simple transform-evaluation-value-into-temporary-constant (evaluation-value)
  (let* ((type (evaluation-value-type evaluation-value))
	 (managed-value evaluation-value))
    #+development
    (when (iteration-state-type-specification-p type)
      (error
	"Attempting to make an iteration state into a temporary constant."))
    (cond ((eq type 'boolean)
	   (setq managed-value (evaluation-truth-value-value evaluation-value))
	   (setq type 'truth-value))
	  ((eq type 'truth-value)
	   (setq managed-value (evaluation-truth-value-value evaluation-value))
	   (reclaim-evaluation-truth-value evaluation-value)))
    (make-temporary-constant-given-managed-value-no-expiration
      managed-value
      type)))

(defun-simple transform-temporary-constant-into-evaluation-value (temporary-constant)
  (let ((managed-value (constant-value-internal temporary-constant))
	(type (constant-type temporary-constant)))
    (setf (constant-value-internal temporary-constant) nil)
    (reclaim-temporary-constant temporary-constant)
    (when (or (eq type 'truth-value) (eq type 'boolean))
      (setq managed-value (make-evaluation-truth-value managed-value)))
    managed-value))

(defun-simple make-evaluation-value-from-temporary-constant (temporary-constant)
  (let ((type (constant-type temporary-constant)))
    (if (or (eq type 'truth-value) (eq type 'boolean))
	(make-evaluation-truth-value (constant-value-internal temporary-constant))
	(copy-evaluation-value (constant-value-internal temporary-constant)))))

(defun-simple make-evaluation-value-list-from-temporary-constant-list (list)
  (loop for temporary-constant in list
	collect (make-evaluation-value-from-temporary-constant temporary-constant)
	using eval-cons))

(def-substitution-macro make-evaluation-value-from-non-logical-managed-value
    (value)
  (if (wide-string-p value)
      (copy-wide-string value)
      (copy-managed-number-or-value value)))

(def-substitution-macro transform-evaluation-value-into-managed-value
		       (evaluation-value)
  (cond ((evaluation-truth-value-p evaluation-value)
	 (let ((value (evaluation-truth-value-value evaluation-value)))
	   (reclaim-evaluation-truth-value evaluation-value)
	   value))
	(t
	 evaluation-value)))

(def-substitution-macro make-evaluation-value-from-managed-value (logical? value)
  (if logical?
      (make-evaluation-truth-value value)
      (make-evaluation-value-from-non-logical-managed-value value)))

(def-substitution-macro cast-slot-constant-into-evaluation-value (slot-constant)
  (let ((managed-value
	  (get-slot-value-number-or-string-from-slot-constant slot-constant)))
    (if (eq (convert-type-or-unit-of-measure-to-type
	      (get-unit-from-slot-constant slot-constant))
	    'truth-value)
	(make-evaluation-truth-value managed-value)
	(copy-managed-number-or-value managed-value))))





;;; The macro `transform-evaluation-value-into-value' takes an evaluation value
;;; and returns the held value of the evaluation value.  The evaluation value
;;; is reclaimed by this macro.

(def-substitution-macro transform-evaluation-value-into-value
			(evaluation-value type)
  (let ((value (evaluation-value-value evaluation-value)))
    (case type
      (text nil)
      ((list structure)
       (reclaim-eval-cons evaluation-value))
      (t
       (reclaim-evaluation-value evaluation-value)))
    value))





;;;; Obsolete Datum Evaluation Value




;;; The evaluation value obsolete-datum is used in displays to encapsulate a
;;; datum which has expired for displays.  It is used purely as a flag saying
;;; the encapsulated value was a previous value for which no replacement has
;;; currently been found.

(def-evaluation-value obsolete-datum)

(def-evaluation-value-reclaimer obsolete-datum
  (reclaim-evaluation-value (evaluation-obsolete-datum-value obsolete-datum)))

(def-evaluation-value-copier obsolete-datum
  (make-evaluation-obsolete-datum
    (copy-evaluation-value
      (evaluation-obsolete-datum-value obsolete-datum))))

(def-evaluation-value-deep-copier obsolete-datum
  (make-evaluation-obsolete-datum
    (deep-copy-evaluation-value
      (evaluation-obsolete-datum-value obsolete-datum))))

(def-evaluation-value-comparitor obsolete-datum
  (evaluation-value-eql (evaluation-obsolete-datum-value obsolete-datum-1)
			(evaluation-obsolete-datum-value obsolete-datum-2)))




;;; The function `evaluation-value-type-specification-p' takes a thing and tests
;;; if it is a valid defined evaluation-value type.

(defun evaluation-value-type-specification-p (thing)
  (or (eq thing 'evaluation-value)
      (and (consp thing)
	   (or (iteration-state-type-specification-p thing)
	       (and (get-evaluation-types (car-of-cons thing) defined-evaluation-value-types)
		    (or (null (cdr-of-cons thing))
			(memq (car-of-cons thing) '(structure sequence))))))))







;;;; Type Specifications for the Evaluators and Compilers




;;; The following utilites define a type representation system used by the
;;; compilers and intepreters.  Previously, there was only a set of type symbols
;;; used to represent types of datum in run-time systems, and these sometimes
;;; meant subtly different things in the different evaluation environments.
;;; This is being replaced with a system which can represent and manipulate type
;;; specifications which describe the kinds of data which are evaluation and
;;; designation values within computations in the simulator, inference engine,
;;; and procedures.

;;; The new types include the previously existing types for datum (NUMBER,
;;; INTEGER, FLOAT, TEXT, TRUTH-VALUE, and SYMBOL); new type symbols BOOLEAN,
;;; DATUM (a union of the datum types), and ITEM-OR-DATUM (a union of DATUM and
;;; item); unknown-datum and no-item types for variables whose values may be
;;; unknown and designations which may reference nothing;
;;; no-item-implies-unknown type for contexts where expressions requiring datum
;;; or unknown-datum but which get no-item should instead get unknown-datum
;;; (happens in "first of the following expressions that has a value"); a type
;;; for continuations within iteration environments; types for instances of
;;; classes; and combined types which are unions (combined with OR),
;;; intersections (combined with AND), and subsets (clauses of intersections
;;; which provide NOT and SATISFIES).  There is also a def-type-specification
;;; form that adds to the set of types that can be written as (NAMED
;;; <type-name>).

;;; Note that some types previously in the system have been removed as of
;;; release 3.0.  These are pure-number, interval, and time-stamp (or
;;; seconds).  Also, the engineering units declarations will not make new
;;; data types.  These declarations are only used in the data type slot of
;;; variable-or-parameter, and this slot only controls printing the value in
;;; attribute tables.  The type of the value of these variables is determined
;;; by the variable's class.

;;; Functions are supplied here which create type specifications (always out of
;;; phrase conses), test for intersection and subtype between two type
;;; specifications, and provide type testing for things to see if they conform
;;; to the type specification.

;;; All functions which construct type specifications use either constant or
;;; phrase conses to make their specifications, so these functions must be
;;; called with a phrase-consing context.  Type specifications can be copied as
;;; a slot value, and the resulting slot-cons-tree can be reclaimed with
;;; reclaim-slot-value.

;;; Type specifications are cons trees and can be written as quoted
;;; constants in source code.  The types are forms are listed below.

;;; Symbol Types

;;; The following types are implemented as symbols.  Note that these are types
;;; in the user model (except for boolean), and that the datum types correspond
;;; to evaluation values (defined just above this code) and do NOT necessarily
;;; correspond to Common Lisp types.

;;; ITEM-OR-DATUM, DATUM, NUMBER, INTEGER, FLOAT, TEXT, TRUTH-VALUE, BOOLEAN
;;; SYMBOL

;;; Class Types

;;; Specifications for class types are implemented as a two element list whose
;;; first is the symbol CLASS and whose second is the symbol naming the class to
;;; which an instance of this type should belong.






;;;; Type Specifications Internals




;;; The macro `def-type-specification' defines type expansions for names.  It
;;; takes three unevaluated arguments.  The first is the symbol naming the new
;;; type.  The second is a "fairly simple" type specification that should be
;;; used by the compiler in place of references to this named type.  The third
;;; is a "complex" type specification that should be used when configuring user
;;; interfaces or doing other operations that require as specific a type
;;; specification as possible, regardless of its length or complexity.  The
;;; definition of "fairly simple" and "complex" are pretty murky, other than to
;;; say that the simple one should be built from the primitive value and class
;;; types, and not have more than one combiner (AND, OR, or NOT), since that's
;;; what the compiler handles best.  If the complex is not provided, then the
;;; simple will be used in its place.  The macros
;;; `type-specification-simple-expansion' and
;;; `type-specification-complex-expansion' provide accessors, given the type
;;; name symbol.

;;; For example, the set of symbols that name colors could be defined as follows:

;;;   (def-type-specification color-name symbol (member blue green mauve ...))

;;; After this definition, you may use (NAMED COLOR-NAME) as a type
;;; specification.


(def-global-property-name type-specification-simple-expansion t)

(def-global-property-name type-specification-explicit-complex-type t)

(defun define-type-specification-explicit-complex-type (new-name complex-type)
  (setf (type-specification-explicit-complex-type new-name) complex-type)
  #+development
  (unless (valid-type-specification-p complex-type)
    (cerror "Continue"
	    "The type named ~S is not valid.~%~
             To debug, type:~%~
             (trace valid-type-specification-p boolean-composition-over-symbols-p)~%~
             (valid-type-specification-p '(named ~(~S~)))"
	    new-name new-name))
  new-name)

(defmacro def-type-specification (new-name simple-type &optional complex-type)
  `(eval-when (:compile-toplevel :load-toplevel :execute)
    (progn
      (setf (type-specification-simple-expansion ',new-name) ',simple-type)
      ,@(cond (complex-type
	       `((define-type-specification-explicit-complex-type ',new-name
		     ',complex-type)))
	      ((eval-feature :development)
	       `((when (type-specification-explicit-complex-type ',new-name)
		   (setf (type-specification-explicit-complex-type ',new-name)
			 nil)))))
      ',new-name)))

(def-substitution-macro type-specification-complex-expansion (type-name)
  (or (type-specification-explicit-complex-type type-name)
      (type-specification-simple-expansion type-name)
      #+development
      (error "No simple or complex expansion could be found for type ~a"
	     type-name)))




;;; The constant `type-symbols-subtype-alist' contains an alist of system
;;; defined type symbols to the system defined type symbols whose types are
;;; strict subtypes of the key type.  Every system defined type symbol is listed
;;; here, so (not (null (assq symbol type-symbols-subtype-alist))) is an
;;; accurate predicate for whether or not a symbol names a system defined type.

(defconstant type-symbols-subtype-alist
  '((datum
     number integer long float text truth-value boolean symbol)
    (number
     integer float long)
    (integer)
    (long)
    (float)
    (text)
    (truth-value
     boolean)
    (boolean)
    (symbol)
    (item-or-datum
     datum number integer long float text truth-value boolean symbol)
    (evaluation-value
     datum number integer long float text truth-value boolean symbol)))

;;; The function `symbolic-type-specification-p' takes a thing and
;;; returns whether or not that thing is a valid type specification
;;; defined by a symbol.

(def-substitution-macro symbolic-type-specification-p-macro (thing)
  (not (null (assq-macro thing type-symbols-subtype-alist))))

(defun-simple symbolic-type-specification-p (thing)
  (symbolic-type-specification-p-macro thing))




;;; The function `symbolic-type-specification-subtype-p' takes two symbolic
;;; types and determines if one is a subtype of the other.

(defun-simple symbolic-type-specification-subtype-p (type superior-type)
  (or (eq type superior-type)
      (memq-macro
	type
	(cdr (assq-macro superior-type
			 type-symbols-subtype-alist)))))




;;; The function `make-class-type-specification' takes a symbol naming a
;;; class (or a potentially kb-defined class) and it returns a type
;;; specification for the given class.  Note that the returned specification is
;;; constructed using phrase conses, and so this function must be called from
;;; within a phrase-consing context.

;;; The constant `type-specification-for-item' contains a type-specification for
;;; instances of the class item.

;;; The function `make-type-specification-for-iteration-state' takes no
;;; arguments and returns a type specification for an iteration state.

;;; The constant `type-specification-for-unknown' contains a constant 

;;; The function `make-type-specification-for-unknown' takes no arguments and
;;; returns a type-specification for an unknown datum.

;;; The function `make-type-specification-for-no-item' takes no arguments and
;;; returns a type-specification for what gets returned when a designation fails
;;; to reference anything.

;;; The function `make-type-specification-for-no-item-implies-unknown' returns a
;;; type specification that will be used within required types to control
;;; handling of no-item in cases where it should be transformed to unknown.
;;; There are no actual values that are instances of this type, it is only used
;;; to signal that this conversion should be performed.

(defconstant type-specification-for-item '(class item))

(declare-side-effect-free-function make-class-type-specification)

(defun-simple make-class-type-specification (class-name)
  (if (eq class-name 'item)
      type-specification-for-item
      (phrase-list 'class class-name)))

(defconstant type-specification-for-iteration-state '(iteration-state))

(declare-side-effect-free-function make-type-specification-for-iteration-state)

(defun-simple make-type-specification-for-iteration-state ()
  type-specification-for-iteration-state)

(defconstant type-specification-for-unknown '(unknown-datum))

(declare-side-effect-free-function make-type-specification-for-unknown)

(defun-simple make-type-specification-for-unknown ()
  type-specification-for-unknown)

(defconstant type-specification-for-no-item '(no-item))

(declare-side-effect-free-function make-type-specification-for-no-item)

(defun-simple make-type-specification-for-no-item ()
  type-specification-for-no-item)

(declare-side-effect-free-function
  make-type-specification-for-no-item-implies-unknown)

(defun-simple make-type-specification-for-no-item-implies-unknown ()
  '(no-item-implies-unknown))




;;; The functions `class-type-specification-p', `iteration-state-type-
;;; specification-p', `unknown-type-specification-p, 'no-item-type-
;;; specification-p', and `no-item-implies-unknown-type-specification-p' test
;;; whether given type specifications are the named type of specification.  This
;;; test does not search down into combined type specifiers, it only tests the
;;; top level.

(declare-side-effect-free-function valid-class-type-specification-p)

(defun-simple valid-class-type-specification-p (thing)
  (and (consp thing)
       (eq (car-of-cons thing) 'class)
       (let ((class-cons? (cdr-of-cons thing)))
	 (and (consp class-cons?)
	      (null (cdr-of-cons class-cons?))
	      (let ((class? (car-of-cons class-cons?)))
		(and class?
		     (symbolp class?)))))))

(declare-side-effect-free-function class-type-specification-p)

(def-substitution-macro class-type-specification-p-macro (type-specification)
  (and (consp type-specification)
       (eq (car-of-cons type-specification) 'class)))

(defun-simple class-type-specification-p (type-specification)
  (class-type-specification-p-macro type-specification))

(declare-side-effect-free-function iteration-state-type-specification-p)

(defun-simple iteration-state-type-specification-p (type-specification)
  (and (consp type-specification)
       (eq (car-of-cons type-specification) 'iteration-state)
       (null (cdr-of-cons type-specification))))

(declare-side-effect-free-function unknown-type-specification-p)

(defun-simple unknown-type-specification-p (type-specification)
  (and (consp type-specification)
       (eq (car-of-cons type-specification) 'unknown-datum)
       (null (cdr-of-cons type-specification))))

(declare-side-effect-free-function no-item-type-specification-p)

(defun-simple no-item-type-specification-p (type-specification)
  (and (consp type-specification)
       (eq (car-of-cons type-specification) 'no-item)
       (null (cdr-of-cons type-specification))))

(declare-side-effect-free-function no-item-implies-unknown-type-specification-p)

(defun-simple no-item-implies-unknown-type-specification-p (type-specification)
  (and (consp type-specification)
       (eq (car-of-cons type-specification) 'no-item-implies-unknown)
       (null (cdr-of-cons type-specification))))




;;; The macro `type-specification-class' takes a type-specification for a class
;;; and returns the class stored within that spec.

(defmacro type-specification-class (class-type-specification)
  `(car-of-cons (cdr-of-cons ,class-type-specification)))

(declare-side-effect-free-function type-specification-class-function)

(defun-simple type-specification-class-function (class-type-specification)
  #+development
  (unless (valid-class-type-specification-p class-type-specification)
    (error "Non-class type specification ~a when extracting a class name."
	   class-type-specification))
  (type-specification-class class-type-specification))


;;; The function `valid-datum-symbolic-type-specification-p' is like
;;; valid-datum-type-specification-p (see SETS), except that it works
;;; only on symbolic type specifications.

#+obsolete
(defun-simple valid-datum-symbolic-type-specification-p (type)
  #+development
  (cerror "oh, go ahead" "Jim and Joe don't think this should be called")
  (and (valid-type-specification-p type)
       (symbolic-type-specification-subtype-p type 'datum))) ; JED/JRA 2/8/96


;;; The function `datum-type-specification-p' returns whether or not a given
;;; type-specification names a datum type (as opposed to a class type).

(defun-simple datum-type-specification-p (type)
  (type-specification-subtype-in-kb-p type 'datum))


;;; The function `valid-datum-type-specification-p' returns whether or not a
;;; given type-specification names a datum type (as opposed to a class type).

(defun-simple valid-datum-type-specification-p (type)
  (and (valid-type-specification-p type)
       (type-specification-subtype-in-kb-p type 'datum)))

(defun-simple fast-named-type-specification-p (type)
  (and (consp type)
       (eq (car type) 'named)))

(defun-simple named-type-specification-p (type)
  (and (consp type)
       (eq (car type) 'named)
       (valid-type-specification-p
	(type-specification-complex-expansion (cadr type)))))

(defun-simple expand-named-type (type)
  (if (and (consp type)
	   (eq (car type) 'named))
      (type-specification-complex-expansion (cadr type))
      type))


;;; The function `valid-type-specification-p' takes a thing and returns
;;; whether or not it is a well-formed and defined type specification.

(defun-simple valid-type-specification-p (thing)
  (typecase thing
    (symbol
     (symbolic-type-specification-p thing))
    (cons
     (case (car thing)
       (or
	(union-type-specification-p thing))
       (class
	(valid-class-type-specification-p thing))
       (no-item
	(no-item-type-specification-p thing))
       (no-item-implies-unknown
	(no-item-implies-unknown-type-specification-p thing))
       (and
	(intersection-type-specification-p thing))
       (not
	(negation-type-specification-p thing))
       (satisfies
	(filtered-type-specification-p thing))
       (member
	(member-type-specification-p thing))
       (structure
	(structure-type-specification-p thing))
       (sequence
	(sequence-type-specification-p thing))
       (named
	(named-type-specification-p thing))
       (unknown-datum
	(unknown-type-specification-p thing))
       (t
	(evaluation-value-type-specification-p thing))))
    (t nil)))



;;; The functions `union-type-specification-p', `intersection-type-
;;; specification-p', `negation-type-specification-p', and `filtered-type-
;;; specification-p' test whether type specifications are of the named
;;; combination types.

(declare-side-effect-free-function fast-union-type-specification-p)
(declare-side-effect-free-function union-type-specification-p)

(defun-simple fast-union-type-specification-p (type-specification)
  (and (consp type-specification)
       (eq (car-of-cons type-specification) 'or)))

(defun-simple union-type-specification-p (type-specification)
  (and (consp type-specification)
       (eq (car-of-cons type-specification) 'or)
       (valid-type-specification-list-p (cdr-of-cons type-specification))))

(declare-side-effect-free-function valid-type-specification-list-p)

(defun-simple valid-type-specification-list-p (thing)
  (loop with result = t
	for type-cons = thing then (cdr-of-cons type-cons)
	while type-cons
	do
    (setq result (and (consp type-cons)
		      (valid-type-specification-p (car-of-cons type-cons))))
	until (null result)
	finally
	  (return result)))

(declare-side-effect-free-function fast-intersection-type-specification-p)
(declare-side-effect-free-function intersection-type-specification-p)

(defun-simple fast-intersection-type-specification-p (type-specification)
  (and (consp type-specification)
       (eq (car-of-cons type-specification) 'and)))

(defun-simple intersection-type-specification-p (type-specification)
  (and (consp type-specification)
       (eq (car-of-cons type-specification) 'and)
       (valid-type-specification-list-p (cdr-of-cons type-specification))))

(declare-side-effect-free-function fast-negation-type-specification-p)
(declare-side-effect-free-function negation-type-specification-p)

(defun-simple fast-negation-type-specification-p (type-specification)
  (and (consp type-specification)
       (eq (car-of-cons type-specification) 'not)))

(defun-simple negation-type-specification-p (type-specification)
  (and (consp type-specification)
       (eq (car-of-cons type-specification) 'not)
       (let ((type-cons? (cdr-of-cons type-specification)))
	 (and (consp type-cons?)
	      (valid-type-specification-p (car-of-cons type-cons?))
	      (null (cdr-of-cons type-cons?))))))


(declare-side-effect-free-function difference-type-specification-in-kb-p)

(defun-simple difference-type-specification-in-kb-p (type-specification)
  (and (consp type-specification)
       (eq (car-of-cons type-specification) 'and)
       (valid-type-specification-list-p (cdr-of-cons type-specification))
       (=f (length type-specification) 3)
       (negation-type-specification-p
	 (third-of-long-enough-list type-specification))
       (type-specification-subtype-in-kb-p
	 (second-of-long-enough-list (third-of-long-enough-list type-specification))
	 (second-of-long-enough-list type-specification))))

(declare-side-effect-free-function filtered-type-specification-p)

(defun-simple filtered-type-specification-p (type-specification)
  (and (consp type-specification)
       (eq (car-of-cons type-specification) 'satisfies)
       (let ((predicate-cons? (cdr-of-cons type-specification)))
	 (and (consp predicate-cons?)
	      (symbolp (car-of-cons predicate-cons?))
	      (fboundp (car-of-cons predicate-cons?))
	      (null (cdr-of-cons predicate-cons?))))))

(declare-side-effect-free-function member-type-specifiction-p)

(defun-simple member-type-specification-p (type-specification)
  (and (consp type-specification)
       (eq (car-of-cons type-specification) 'member)
       (loop for elt in (cdr-of-cons type-specification)
	     always (evaluation-value-p elt))))


(declare-side-effect-free-function type-specifications-could-intersect-in-kb-p)

(defun-simple type-specifications-could-intersect-in-kb-p (type superior-type)
  (or ;(not (type-specification-not-subtype-p superior-type type))
      ;(not (type-specification-not-subtype-p type superior-type))
      (type-specifications-could-intersect-in-kb-p-1 type superior-type)))

(defun-simple type-specifications-could-intersect-in-kb-p-1 (type superior-type)
  #+development
  (unless (and (valid-type-specification-p type)
	       (valid-type-specification-p superior-type))
    (cerror "Return NIL"
	    "Bad types: ~a ~a" type superior-type)
    (return-from type-specifications-could-intersect-in-kb-p-1 nil))
  (or (equal type superior-type)
      (cond
	((union-type-specification-p superior-type)
	 (loop for subtype in (cdr-of-cons superior-type)
	       thereis (type-specifications-could-intersect-in-kb-p-1 type subtype)))
	((intersection-type-specification-p superior-type)
	 (loop for subtype in (cdr-of-cons superior-type)
	       always (type-specifications-could-intersect-in-kb-p-1 type subtype)))
	((negation-type-specification-p superior-type)
	 (not (type-specification-subtype-in-kb-p
		type (second-of-long-enough-list superior-type))))
	((class-type-specification-p superior-type)
	 (and (class-type-specification-p type)
	      (class-type-specifications-could-intersect-in-kb-p
		superior-type type)))
	((aggregate-value-type-specification-p superior-type)
	 (or (eq type 'datum)
	     (eq type 'item-or-datum)
	     (eq type 'evaluation-value)
	     (and (fast-structure-type-specification-p type)
		  (fast-structure-type-specification-p superior-type)
		  (structure-type-specifications-could-intersect-in-kb-p
		    type superior-type))
	     (and (fast-sequence-type-specification-p type)
		  (fast-sequence-type-specification-p superior-type)
		  (sequence-type-specifications-could-intersect-in-kb-p
		    type superior-type))))
	((member-type-specification-p superior-type)
	 (or (eq type 'item-or-datum)
	     (eq type 'evaluation-value)
	     (eq type 'datum)
	     (and (member-type-specification-p type)
		  (member-type-specifications-could-intersect-p
		    superior-type type))
	     (and (type-specification-subtype-in-kb-p type 'datum)
		  (member-type-specification-intersects-datum-type-p
		    superior-type type))))
	((symbolp superior-type)
	 (or (and (symbolp type)
		  (or (symbolic-type-specification-subtype-p
			type superior-type)
		      (symbolic-type-specification-subtype-p
			superior-type type)))
	     (and (eq superior-type 'item-or-datum)
		  (or (class-type-specification-p type)
		      (aggregate-value-type-specification-p type)))
	     (and (eq superior-type 'evaluation-value)
		  (consp type)
		  (evaluation-value-type-specification-p type))
	     (and (eq superior-type 'datum)
		  (aggregate-value-type-specification-p type)))))
      (cond
	((union-type-specification-p type)
	 (loop for subtype in (cdr-of-cons type)
	       thereis (type-specifications-could-intersect-in-kb-p-1
			 subtype superior-type)))
	((intersection-type-specification-p type)
	 (loop for subtype in (cdr-of-cons type)
	       always (type-specifications-could-intersect-in-kb-p-1
			subtype superior-type)))
	((negation-type-specification-p type)
	 (not (type-specification-subtype-in-kb-p
		superior-type (second-of-long-enough-list type))))
	((member-type-specification-p type)
	 (or (eq superior-type 'item-or-datum)
	     (eq superior-type 'evaluation-value)
	     (eq superior-type 'datum)
	     (and (member-type-specification-p superior-type)
		  (member-type-specifications-could-intersect-p
		    superior-type type))
	     (and (type-specification-subtype-in-kb-p type 'datum)
		  (member-type-specification-intersects-datum-type-p
		    type superior-type))))
	((symbolp type)
	 (or (and (eq type 'item-or-datum)
		  (class-type-specification-p superior-type))
	     (and (eq type 'evaluation-value)
		  (consp superior-type)
		  (evaluation-value-type-specification-p superior-type)))))))

(defun-simple class-type-specifications-could-intersect-in-kb-p (class1 class2)
  (or (not (type-specification-not-subtype-in-kb-p class1 class2))
      (not (type-specification-not-subtype-in-kb-p class2 class1))))
    



;;; The function `type-specification-type-p' takes a thing and a
;;; type-specification and returns whether or not the thing matches the type.

(defun-simple type-specification-type-p (thing type)
  (if (evaluation-item-reference-p thing)
      (type-specification-type-p
	(evaluation-item-reference-referenced-item thing)
	type)
      (if (atom type)
	  (case type
	    ((number) (evaluation-quantity-p thing))
	    ((integer) (evaluation-integer-p thing))
            ((long) (evaluation-long-p thing))
	    ((float) (evaluation-float-p thing))
	    ((symbol) (evaluation-symbol-p thing))
	    ((boolean) (evaluation-boolean-p thing))
	    ((truth-value) (evaluation-truth-value-p thing))
	    ((text) (evaluation-text-p thing))
	    ((item-or-datum)
	     (or (of-class-p thing 'item) (evaluation-datum-p thing)))
	    ((datum) (evaluation-datum-p thing))
	    ((evaluation-value) (evaluation-value-p thing))
	    (t nil))
	  (case (car-of-cons type)
	    ((sequence structure)
	     (and (consp thing)
		  (let ((aggregate-type-name-of-value
			  (aggregate-evaluation-value-type-symbol thing))
			(aggregate-type-name (car-of-cons type)))
		    (and (eq aggregate-type-name-of-value
			     aggregate-type-name)
			 (or (not (aggregate-value-type-specification-has-details-p
				    type))
			     (if (eq aggregate-type-name 'structure)
				 (detailed-evaluation-structure-type-p thing type)
				 (detailed-evaluation-sequence-type-p thing type)))))))
	    (member
	     (and (evaluation-value-p thing)
		  (loop for elt in (cdr type)
			thereis (evaluation-value-eql elt thing))))
	    (class
	     (of-class-p thing (type-specification-class type)))
	    (or
	     (loop for union-type in (cdr-of-cons type)
		   thereis (type-specification-type-p thing union-type)))
	    ((place-reference action-cache obsolete-datum)
	     (and (consp thing)
		  (eq (car-of-cons type)
		      (cdr-of-cons thing))))
	    (and
	     (loop for intersection-type in (cdr type)
		   always (type-specification-type-p thing intersection-type)))
	    (not
	     (not (type-specification-type-p
		    thing (second-of-long-enough-list type))))
	    (no-item
	     (null thing))
	    (no-item-implies-unknown
	     ;; There are no actual members of this type, so it always returns NIL.
	     nil)
	    (satisfies
	     (let ((function-symbol (second-of-long-enough-list type)))
	       (and (fboundp function-symbol)
		    (funcall-symbol function-symbol thing))))
	    (named
	     (if (and (symbolp (cadr type))
	              (eq (cadr type) 'color-or-metacolor))
	       (neq (color-or-metacolor-p thing) nil)
	       (type-specification-type-p
	         thing
	         (type-specification-complex-expansion (cadr type)))))
	    (t
	     #+development
	     (cerror
	       "Continue"
	       "Unhandled type ~a in type-specification-type-p."
	       type)
	  nil)))))



;;; The function `type-specification-subtype-in-kb-p' takes two types and tests
;;; if the first is a subtype of the second, similar to subtype-p without the
;;; in-kb stuff.  However, this function differs in that it is allowed to
;;; reflect subtyping of classes defined within a knowledge base.  Therefore,
;;; this function should be used only to do run-time tests, or to determine
;;; types for compilations within a particular object which cannot significantly
;;; change its type, such as from one foundation class to another.

(declare-side-effect-free-function type-specification-subtype-in-kb-p)

(defun-simple type-specification-subtype-in-kb-p (type superior-type)
  #+development
  (assert (and (valid-type-specification-p type)
	       (valid-type-specification-p superior-type))
	  (type superior-type)
	  "Invalid type-specification argument.")
  (or (equal type superior-type)
      (cond ((union-type-specification-p type)
	     (loop for subtype in (cdr type)
		   always (type-specification-subtype-in-kb-p
			    subtype superior-type)))
	    ((difference-type-specification-in-kb-p type)
	     (type-specification-subtype-in-kb-p
	       (second-of-long-enough-list type)
	       superior-type))
	    ((intersection-type-specification-p type)
	     (loop for intersection-type in (cdr type)
		   thereis (type-specification-subtype-in-kb-p
			     intersection-type superior-type)))
	    ((negation-type-specification-p type)
	     (and (negation-type-specification-p superior-type)
		  (type-specification-subtype-in-kb-p
		    (second superior-type) (second type)))))
      (cond ((symbolp superior-type)
	     (or (and (symbolp type)
		      (symbolic-type-specification-subtype-p
			type superior-type))
		 (and (member-type-specification-p type)
		      (member-type-specification-subtype-of-symbolic-type-p
			type superior-type))
		 (and (eq superior-type 'item-or-datum)
		      (or (class-type-specification-p type)
			  (aggregate-value-type-specification-p type)))
		 (and (eq superior-type 'datum)
		      (aggregate-value-type-specification-p type))
		 (and (eq superior-type 'evaluation-value)
		      (consp type)
		      (evaluation-value-type-specification-p type))))
	    ((aggregate-value-type-specification-p superior-type)
	     ;; only other aggregate value types can be sub types of
	     ;; an aggregate value type
	     (and (aggregate-value-type-specification-p type)
		  (or (and (fast-structure-type-specification-p type)
			   (fast-structure-type-specification-p superior-type)
			   (structure-type-specification-subtype-in-kb-p
			     type superior-type))
		      (and (fast-sequence-type-specification-p type)
			   (fast-sequence-type-specification-p superior-type)
			   (sequence-type-specification-subtype-in-kb-p
			     type superior-type)))))
	    ((member-type-specification-p superior-type)
	     ;; a member type spec. can only be a superior of other member types,
	     ;; or, eventually certain integer ranges.
	     (and (member-type-specification-p type)
		  (member-type-specification-subtype-p
		    type superior-type)))
	    ((class-type-specification-p superior-type)
	     (let ((superior-class (type-specification-class superior-type)))
	       (and (class-type-specification-p type)
		    (let ((class (type-specification-class type)))
		      (or (eq superior-class 'item)
			  (eq superior-class class)
			  (not (null (subclassp class superior-class))))))))
	    ((union-type-specification-p superior-type)
	     (loop for union-type in (cdr superior-type)
		   thereis (type-specification-subtype-in-kb-p
			     type union-type)))
	    ((intersection-type-specification-p superior-type)
	     (loop for intersection-type in (cdr superior-type)
		   always (type-specification-subtype-in-kb-p
			    type intersection-type)))
	    ((negation-type-specification-p superior-type)
	     (not (type-specifications-could-intersect-in-kb-p
		    type (second superior-type)))))
      ;; The filtered case is covered by the equal above.  -jra 4/19/91
;      (and (or (filtered-type-specification-p superior-type)
;	       (filtered-type-specification-p type))
;	   (equal type superior-type))
      ;; The iteration state case is covered by the equal above.  -jra 4/19/91
;      (and (or (iteration-state-type-specification-p type)
;	       (iteration-state-type-specification-p superior-type))
;	   (and (iteration-state-type-specification-p type)
;		(iteration-state-type-specification-p superior-type)))
      ))




;;; The function `type-specification-not-subtype-in-kb-p' is a run-time safe
;;; version of type-specification-not-subtype-p.  See documentation near
;;; its definition for details.

(declare-side-effect-free-function type-specification-not-subtype-in-kb-p)

(defun-simple type-specification-not-subtype-in-kb-p (type superior-type)
  #+development
  (assert (and (valid-type-specification-p type)
	       (valid-type-specification-p superior-type))
	  (type superior-type)
	  "Invalid type-specification argument.")
  (and (not (equal type superior-type))
       (or (cond ((intersection-type-specification-p superior-type)
		  (loop for intersection-type in (cdr superior-type)
			thereis (type-specification-not-subtype-in-kb-p
				  type intersection-type)))
		 ((union-type-specification-p superior-type)
		  (loop for subtype in (cdr superior-type)
			always (type-specification-not-subtype-in-kb-p type subtype)))
		 ((negation-type-specification-p superior-type)
		  ;; This should be the following.  -jra 12/16/93
		  ;; (type-specifications-intersect-p type (second superior-type))
		  (or (type-specification-subtype-in-kb-p
			type (second superior-type))
		      (type-specification-subtype-in-kb-p
			(second superior-type) type))))
	   (cond ((difference-type-specification-in-kb-p type)
		  (type-specification-not-subtype-in-kb-p
		    (second-of-long-enough-list type) superior-type))
		 ((intersection-type-specification-p type)
		  (loop for intersection-type in (cdr type)
			thereis (type-specification-not-subtype-in-kb-p
				  intersection-type superior-type)))
		 ((union-type-specification-p type)
		  (loop for subtype in (cdr type)
			always (type-specification-not-subtype-in-kb-p
				 subtype superior-type)))
		 ((negation-type-specification-p type)
		  (or (type-specification-subtype-in-kb-p
			(second type) superior-type)
		      (type-specification-subtype-in-kb-p
			superior-type (second type)))))
	   ;; Filtered types cannot be proven to be disjoint, since the
	   ;; predicate function can accept or reject values arbitrarily.  Also,
	   ;; the following not-subtype-p predicates depend on the subtypes
	   ;; being simple types.
	   (cond ((or (filtered-type-specification-p superior-type)
		      (filtered-type-specification-p type)
		      (intersection-type-specification-p type)
		      (union-type-specification-p type)
		      (negation-type-specification-p type))
		  nil)
		 ((symbolp superior-type)
		  (cond
		    ((symbolp type)
		     (not (symbolic-type-specification-subtype-p
			    type superior-type)))
		    ((aggregate-value-type-specification-p type)
		     (not (or (eq superior-type 'datum)
			      (eq superior-type 'item-or-datum)
			      (eq superior-type 'evaluation-value))))
		    ((member-type-specification-p type)
		     (member-type-specification-not-subtype-of-symbolic-type-p
		       type superior-type))
		    (t
		     (or (not (class-type-specification-p type))
			 (if (eq superior-type 'evaluation-value)
			     (not (type-specification-subtype-in-kb-p
				    type superior-type))
			     (not (eq superior-type 'item-or-datum)))))))
		 ((member-type-specification-p superior-type)
		  (cond ((member-type-specification-p type)
			 (member-type-specification-not-subtype-p
			   type superior-type))
			(t
			 ;; if type is not another member
			 ;; it may be a subtype if it is a subrange contained
			 ;; by the list of members, but this is not yet implemented
			 t)))
		 ((aggregate-value-type-specification-p superior-type)
		  (cond
		    ((aggregate-value-type-specification-p type)
		     (cond
		       ((and (fast-structure-type-specification-p type)
			     (fast-structure-type-specification-p superior-type))
			(structure-type-specification-not-subtype-in-kb-p
			  type superior-type))
		       ((and (fast-sequence-type-specification-p type)
			     (fast-sequence-type-specification-p superior-type))
			(sequence-type-specification-not-subtype-in-kb-p
			  type superior-type))
		       (t
			t)))
		    (t
		     t)))
;		 ((symbol type)
;		  (if (symbolp type)
;		      (not (symbolic-type-specification-subtype-p
;			     type superior-type))
;		      ;; here see above hax
;		      (or (progn
;			    (when (aggregate-value-type-specification-p type)
;			      (error "unhandled not subtype - JRA"))
;			    nil)
;			  (not (class-type-specification-p type))
;			  (if (eq superior-type 'evaluation-value)
;			      (not (type-specification-subtype-in-kb-p
;				     type superior-type))
;			      (not (eq superior-type 'item-or-datum))))))
		 ;; For evaluation-value, unknown, or no item superior types,
		 ;; not-subtype-p is true if the subtype is not a combined type
		 ;; and it is also not a subtype of the superior type.
		 ((or (evaluation-value-type-specification-p superior-type)
		      (unknown-type-specification-p superior-type)
		      (no-item-type-specification-p superior-type)
		      (no-item-implies-unknown-type-specification-p superior-type))
		  (not (type-specification-subtype-in-kb-p type superior-type)))
		 ((class-type-specification-p superior-type)
		  ;; Note that a class type can only be a superior type of
		  ;; class types.  -jra & cpm 4/17/91
		  (or (not (class-type-specification-p type))
		      (let ((superior-class
			      (type-specification-class superior-type))
			    (inferior-class
			      (type-specification-class type)))
			(cond
			  ((eq inferior-class superior-class)
			   nil)
			  ((and (system-defined-class-p superior-class)
				(system-defined-class-p inferior-class))
			   (not (subclassp inferior-class superior-class)))
			  (t
			   nil)))))))))





;;;; Other Type Functions and Predicates


;;; The function `class-in-attribute-conforms-to-type-p' returns t if the
;;; class in the slot-init-form of the slot-description does not violate
;;; the declared slot type; otherwise it issues a warning and returns nil.

(defun class-in-attribute-conforms-to-type-p
    (slot-description class
		      &optional suppress-warning-messages?
		                slot-init-form-of-override?)
  (let ((slot-type-specification (slot-type-specification slot-description)))
    (cond ((class-type-specification-p slot-type-specification)
	   (let ((type-specification-class
		   (type-specification-class-function slot-type-specification))
		 (class-for-instantiation
		   (if slot-init-form-of-override?
		       (third slot-init-form-of-override?)
		       (third (slot-init-form slot-description)))))
	     (cond ((not (classp class-for-instantiation))
		    (unless suppress-warning-messages?
		      (class-instantiation-warning-not-defined
			class-for-instantiation slot-description class))
		    nil)
		   ((classp type-specification-class)
		    (if (subclassp class-for-instantiation type-specification-class)
			t
			(progn
			  (unless suppress-warning-messages?
			    (class-instantiation-warning-incompatible-class
			      class-for-instantiation slot-description
			      class type-specification-class))
			  nil)))
		   (t
		    (unless suppress-warning-messages?
		      (class-instantiation-warning-undefined-type-specification-class
			class-for-instantiation slot-description
			class type-specification-class))
		    nil))))
	  (t t))))


;;; The variables `g2-element-types-that-can-contain-datum' and
;;; `internal-g2-element-types-that-can-contain-datum' contain a list of the
;;; g2-list and g2-array element types that may contain datum.  The non-inernal
;;; form of the variable contains the element-types that the user sees.  The
;;; internal form of the variable contains the internal versions of the
;;; element-types.  For example, the internal form of item-or-value is
;;; item-or-datum

(defvar internal-g2-element-types-that-can-contain-datum
        '(number integer long float symbol truth-value text datum item-or-datum
	  structure sequence))

(defvar g2-element-types-that-can-contain-datum
	'(quantity integer long float symbol truth-value text value item-or-value
	  structure sequence))


;;; The function `category-is-not-g2-element-datum-type' is used to test the
;;; resulting symbol in a grammar parse.  It checks that the symbol is not one
;;; of the defined datum element-types.  This is useful when determining an
;;; element type of a named class.

(defun category-is-not-g2-element-datum-type (category-symbol)
  (if (not (memq category-symbol g2-element-types-that-can-contain-datum))
      category-symbol
      bad-phrase))

(declare-grammar-transform-can-return-bad-phrase category-is-not-g2-element-datum-type)


(defun non-negative-fixnum-p (x)
  (and (fixnump x)
       (>=f x 0)))



;;;; Writing Evaluation Values

(defun write-evaluation-value (evaluation-value &optional beautifully?)
  (cond ((null evaluation-value)
	 (twrite-string "none"))
	((evaluation-integer-p evaluation-value)
	 (print-constant (evaluation-integer-value evaluation-value)
			 'number
			 beautifully?))
	((evaluation-long-p evaluation-value)
	 (with-temporary-creation write-evaluation-value
	   (print-constant (evaluation-long-value evaluation-value)
			   'number
			   beautifully?)))
	((evaluation-float-p evaluation-value)
	 (with-temporary-gensym-float-creation write-evaluation-value
	   (print-constant (evaluation-float-value evaluation-value)
			   'number
			   beautifully?)))
	((evaluation-truth-value-p evaluation-value)
	 (print-constant (evaluation-truth-value-value evaluation-value)
			 'truth-value
			 beautifully?))
	((evaluation-symbol-p evaluation-value)
	 (print-constant (evaluation-symbol-symbol evaluation-value)
			 'symbol
			 beautifully?))
	((evaluation-text-p evaluation-value)
	 (print-constant (evaluation-text-value evaluation-value)
			 'text
			 beautifully?))
	((evaluation-iteration-state-p evaluation-value)
	 (twrite-string "an iteration state"))
	((and (consp evaluation-value)
	      (defined-evaluation-value-type-p (cdr-of-cons evaluation-value)))
	 ;; At present, place-reference, action-cache, and obsolete-datum have
	 ;; this special writer; should their writers be passed the beautifully?
	 ;; arg?  (Do they have different parsable vs. beautiful written
	 ;; representations?!  (MHD 5/26/92)
	 (funcall-simple-compiled-function
	   (defined-evaluation-type-writer (cdr-of-cons evaluation-value))
	   evaluation-value))
	(t
	 #+development
	 (cerror
	   "Continue" "Printing ~a as an evaluation value, but it's not."
	   evaluation-value)
	 nil)))

;; Changed to support the new optional arg, beautifully?, and therefore also from
;; a defun-simple to a defun.  Note that the only user, at present, of the new
;; arg is the FORMAT (i.e., []'s) evaluator.  (MHD 5/26/92)





;;; The function `write-block-or-evaluation-value' expects
;;; block-or-evaluation-value to be a block or an evaluation value.  If (framep
;;; block-or-evaluation-value) is true, this just writes the designation for it
;;; using get-or-make-up-designation-for-block; otherwise, this just writes the
;;; evaluation value using write-evaluation-value.

(defun write-block-or-evaluation-value (block-or-evaluation-value
					 &optional beautifully?)
  (cond ((not (framep block-or-evaluation-value))
	 (write-evaluation-value block-or-evaluation-value
				 beautifully?))
	(in-text-for-item-or-value-p
	 (twrite-designation-for-item block-or-evaluation-value))
	(t
	 (twrite (get-or-make-up-designation-for-block
		   block-or-evaluation-value)))))

;; This is called by the tformat for the new ~NA directive. (MHD 11/4/91)




;;; Print-constant prints a number, interval, or other constant given the numerical
;;; part and the unit part as separate arguments.  If beautifully? is false, as
;;; it is by default, it can be used to print a constant in a form acceptable as
;;; input for parsing.  This accepts both gensym floats and managed floats for
;;; the constant-value arg.

;;; Note that (print-constant ... 'time-stamp) expects a current time.  If the argument
;;; is a gensym-time, use write-date-and-time.

(def-kb-specific-property-name *singular-of-numeric-data-type*)

(defun print-constant (constant-value constant-type &optional beautifully?)
  (cond
    ((null constant-type)
     (twrite-string "no value"))
    ((eq constant-type 'seconds)
     (print-relative-time constant-value))
    ((eq constant-type 'time-stamp)
     (with-temporary-gensym-float-creation print-constant
       (let* ((subsecond? nil)
	      (unix-time
		(cond ((fixnump constant-value)
		       (+e (managed-float-value (clock-get g2-time-at-start))
			   (coerce-fixnum-to-gensym-float constant-value)))
		      ((gensym-float-p constant-value)
		       (setq subsecond? t)
		       (+e (managed-float-value (clock-get g2-time-at-start)) constant-value))
		      ((managed-float-p constant-value)
		       (setq subsecond? t)
		       (+e (managed-float-value (clock-get g2-time-at-start))
			   (managed-float-value constant-value)))
		      ((integerp constant-value) ; bignum case
		       (+e (managed-float-value (clock-get g2-time-at-start))
			   (coerce-to-gensym-float constant-value)))
		      (t			; shouldn't happen
		       0.0)))
	      (seconds-remainder
		(if subsecond?
		    (-e unix-time (ffloore-first unix-time))
		    0.0)))
	 (declare (type gensym-float unix-time seconds-remainder))
	 (if (or (<e unix-time -2.147483648e9) ; signed 32-bit long bounds
		 (>=e unix-time 2-to-31-plus-62-years))
	     (twrite-string "<time stamp out of bounds>")
	     (multiple-value-bind (second minute hour date month year)
		 (gensym-decode-unix-time unix-time)
	       (print-decoded-time
		 (if subsecond?
		     (+e seconds-remainder (coerce-fixnum-to-gensym-float second))
		     second)
		 minute hour date month year))))))
    ((eq constant-type 'symbol)
     (let ((write-symbols-parsably? (not beautifully?)))
       (cond
	 ((and constant-value (atom constant-value))
	  (twrite constant-value))
	 (t (write-symbol-list constant-value '\, 'and "none")))))
    ((eq constant-type 'truth-value)
     (cond ((=f constant-value 1000) (twrite-string "true"))
	   ((=f constant-value -1000) (twrite-string "false"))
	   (t (let ((negative? (<f constant-value 0)))
		(twrite (if negative? "-." "."))
		;; before Tformat, we had (format t "~3,'0d true" (abs constant-value))
		;;  here instead of the rest of this.  There's probably a better way to
		;;  do this! (MHD 2/3/88)
		(when negative?
		  (setq constant-value (-f constant-value)))	; changes arg!
		(cond ((<f constant-value 10)
		       (twrite-string "00"))
		      ((<f constant-value 100)
		       (twrite-string "0")))	      
		(twrite-positive-fixnum constant-value)
		(twrite-string " true")))))
    ((eq constant-type 'text)
     (let ((minimum-string-length 10)  ; had been 3 -- Lengthened for bug HQ-1124105
	   (length-of-string (lengthw constant-value)))
       (cond
	 ((and evaluation-value-writing-target-length?
	       (>f (+f length-of-string
		       (twriting-accumulated-length))
		   evaluation-value-writing-target-length?)
	       (>f length-of-string minimum-string-length))
	  (let ((small-g2-text
		 (if (and in-text-for-item-or-value-p (binary-wide-string-p constant-value))
		     (copy-text-string "")
		     (copy-partial-wide-string constant-value minimum-string-length)))
		(write-strings-parsably? (not beautifully?)))
	    (tformat "~a..." small-g2-text)
	    (reclaim-text-string small-g2-text)))
	 ((and in-text-for-item-or-value-p (binary-wide-string-p constant-value))
	  (let ((write-strings-parsably? nil))
	    (twrite-string "the binary string \"")
	    (twrite-binary-string-printed-representation constant-value)
	    (twrite-string "\"")))
	 (t
	  (let ((write-strings-parsably? (not beautifully?)))
	    (twrite-string constant-value))))))
    ((number-subtype-p constant-type)
     (with-temporary-gensym-float-creation print-constant--number-case
       (let ((value-to-print
	       (cond ((managed-float-p constant-value)
		      (managed-float-value constant-value))
		     ((managed-long-p constant-value)
		      (managed-long-value constant-value))
		     (t
		      constant-value))))
	 (twrite value-to-print)
	 (when (eq constant-type 'long)
	   (twrite-string "L"))
	 (cond
	   ((eq constant-type 'f)
	    (twrite-string " F"))
	   ((eq constant-type 'c)
	    (twrite-string " C"))
	   ((memq constant-type '(number pure-number integer long float)))
	   (t
	    (twrite-char #.%space)
	    (let ((write-symbols-in-lower-case? nil))
	      (let ((write-symbols-parsably? (not beautifully?)))
		(twrite
		  (or (if (and (fixnump value-to-print)	; "1.0 inches" is correct
			       (=f value-to-print 1))
			  (*singular-of-numeric-data-type* constant-type))
		      constant-type)))))))))
    ((not (valid-type-specification-p constant-type)))
    ((type-specification-subtype-in-kb-p constant-type '(sequence))
     (write-evaluation-sequence constant-value))
    ((type-specification-subtype-in-kb-p constant-type '(structure))
     (write-evaluation-structure constant-value))))


;;; The function `write-type-specification' takes a type specification and
;;; twrites it in an Englishy format (kinda).

(defun-void write-type-specification (type-specification)
  (cond
    ((symbolp type-specification)
     (case type-specification
       ((item-or-datum)
	(twrite-string "item-or-value"))
       ((datum)
	(twrite-string "value"))
       ((evaluation-value)
	(loop for type being each evaluation-type of defined-evaluation-value-types
	      collect (type-specification-of-defined-evaluation-type type)
		into defined-types using eval-cons
	      finally
		(setq defined-types
		      (nconc (eval-list 'datum '(iteration-state))
			     defined-types))
		(write-combined-type-specification 'or defined-types)
		(reclaim-eval-list defined-types)))
       (t
	(twrite-data-type type-specification))))
    ((or (union-type-specification-p type-specification)
	 (intersection-type-specification-p type-specification))
     (write-combined-type-specification
       (car type-specification) (cdr type-specification)))
    ((negation-type-specification-p type-specification)
     (twrite-string "not of the type ")
     (write-type-specification (second type-specification)))
    ((filtered-type-specification-p type-specification)
     (tformat "a thing which satisfies the predicate ~a"
	      (second type-specification)))
    ((iteration-state-type-specification-p type-specification)
     (twrite-string "iteration state"))
    ((unknown-type-specification-p type-specification)
     (twrite-string "unknown"))
    ((no-item-type-specification-p type-specification)
     (twrite-string "none"))
    ((no-item-implies-unknown-type-specification-p type-specification)
     (twrite-string "the value \"none\" treated as unknown"))
    ((class-type-specification-p type-specification)
     (twrite-string "class ")
     (twrite-symbol (type-specification-class type-specification)))
    ((aggregate-value-type-specification-p type-specification)
     (cond ((fast-structure-type-specification-p type-specification)
	    (write-structure-type-specification type-specification))
	   (t
	    (write-sequence-type-specification type-specification))))
    ((and (evaluation-value-type-specification-p type-specification)
	  (consp type-specification)
	  (defined-evaluation-value-type-p (car-of-cons type-specification)))
     (if (eq (car-of-cons type-specification) 'place-reference)
	 (twrite-string
	   "concludable item attribute, g2-array element, or g2-list element")
	 (twrite-symbol (car type-specification))))
    ;; do member case here
    ((member-type-specification-p type-specification)
     (twrite-string "one of ")
     (loop with more-than-two-p = (cddr (cdr type-specification))
           for elt-tail on (cdr type-specification)
	   as elt = (car elt-tail)
	   do
       (cond ((cddr elt-tail)
	      (tformat "~NV, " elt))
	     ((cdr elt-tail)
	      (cond (more-than-two-p
		     (tformat "~NV, or " elt))
		    (t
		     (tformat "~NV or " elt))))
	     (t
	      (tformat "~NV" elt)))))
    ((named-type-specification-p type-specification)
     (write-type-specification
       (type-specification-complex-expansion (cadr type-specification))))
    (t
     (twrite type-specification))))

(defun-simple write-sequence-type-specification (type-specification)
  (twrite-string "sequence")
  (when (aggregate-value-type-specification-has-details-p type-specification)
    (let* ((low-bound? (sequence-type-specification-low-bound type-specification))
	   (high-bound?
	     (and low-bound?
		  (sequence-type-specification-high-bound type-specification))))
      (cond (high-bound?
	     (tformat " with at least ~D, and less than ~D elements of type "
		      low-bound? high-bound?))
	    (low-bound?
	     (tformat " with at least ~D element~a of type "
		      low-bound? (if (/=f low-bound? 1) "s" "")))
	    (t
	     (tformat " with elements of type ")))
      (write-type-specification
	(sequence-type-specification-element-type type-specification)))))

(defun-simple write-structure-type-specification (type-specification)
  (twrite-string "structure")
  (when (aggregate-value-type-specification-has-details-p type-specification)
    (twrite-string ", with slot types (")
    (loop for tail on (structure-type-specification-slot-list type-specification)
          as ((slot-name slot-type-specification) . nil) on tail
	  do
      (tformat "~(~a~): ~NT" slot-name slot-type-specification)
      (cond ((cddr tail)
	     (twrite-string ", "))
	    ((cdr tail)
	     (twrite-string ", and "))))
    (twrite-string ")")
    (let ((minimum-contents?
	    (structure-type-specification-minimum-contents type-specification)))
      (when minimum-contents?
	(twrite-string ", where ")
	(twrite-minimum-structure-contents minimum-contents? t)
	(twrite-string " must be present")))))

(defun-simple twrite-minimum-structure-contents (boolean-expression top-level-p)
  (cond ((consp boolean-expression)
	 (let ((operator (car-of-cons boolean-expression)))
	   (case operator
	     ((and or)
	      (cond
		((null (cddr boolean-expression))
		 (twrite-minimum-structure-contents (cadr boolean-expression) top-level-p))
		(t
		 (unless top-level-p
		   (twrite-string "("))
		 (twrite-minimum-structure-contents (cadr boolean-expression) nil)
		 (loop for sub-expression in (cddr boolean-expression)
		       do
		   (tformat " ~a " operator)
		   (twrite-minimum-structure-contents sub-expression nil))
		 (unless top-level-p
		   (twrite-string ")")))))
	     (not
	      (twrite-string "NOT ")
	      (twrite-minimum-structure-contents (cadr boolean-expression) nil)))))
	(boolean-expression
	 #+development
	 (unless (symbolp boolean-expression)
	   (error "bad type specification minimum-contents ~s" boolean-expression))
	 (twrite-symbol boolean-expression))))
	

(defun twrite-data-type (data-type)
  (cond
    ((and (consp data-type)
	  (eq (car data-type) 'class))
     (twrite-symbol (second data-type)))
    ((not (symbolp data-type))
     (twrite data-type))
    ((eq data-type 'datum) (twrite-string "value"))
    ((eq data-type 'number) (twrite-string "quantity"))
    ((eq data-type 'integer) (twrite-string "integer"))
    ((eq data-type 'long) (twrite-string "long"))
    ((eq data-type 'float) (twrite-string "float"))
    ((eq data-type 'seconds) (twrite-string "interval"))
    ((eq data-type 'time-stamp) (twrite-string "time stamp"))
    ((eq data-type 'truth-value) (twrite-string "truth value"))
    ;; Pure-number case added 4/18/95 (ghw).
    ((eq data-type 'pure-number) (twrite-string "pure number"))
    (data-type (twrite-symbol data-type))
    (t (twrite "none"))))	 

(defun-void write-combined-type-specification (combiner types)
  (let ((types-count (length types)))
    (case types-count
      ((0)
       nil)
      ((1)
       (write-type-specification (first types)))
      ((2)
       (write-type-specification (first types))
       (tformat " ~(~a~) " combiner)
       (write-type-specification (second types)))
      (t
       (loop for count from 1
	     for type in types
	     do
	 (cond ((=f count types-count)
		(tformat ", ~(~a~) " combiner))
	       ((/=f count 1)
		(twrite-string ", ")))
	 (write-type-specification type))))))



;;;; Hash Codes for Evaluation-Values




(defconstant ev-hash-version 1)

(defconstant ev-hash-null-code 1)
(defconstant ev-hash-integer-code 2)
(defconstant ev-hash-float-code 3)
(defconstant ev-hash-symbol-code 4)
(defconstant ev-hash-text-code 5)
(defconstant ev-hash-truth-value-code 6)
(defconstant ev-hash-sequence-code 7)
(defconstant ev-hash-structure-code 8)
(defconstant ev-hash-long-code 9)

;;; `evaluation-value-hash' is written for speed, not beauty.
;;; Knowledge of the representation of evaluation-values is
;;; rampant throughout.  This function is more useful for
;;; evaluation-values that are expected to have sequences and
;;; structures.  More efficient hash-functions could be made
;;; for more constrained data types.

(eval-when (:compile-toplevel :load-toplevel :execute)
  (defconstant ev-hash-buffer-size 8))

(defun-simple evaluation-value-hash (evaluation-value)
  (let ((buffer (mark-wide-string-as-binary
		  (make-wide-string ev-hash-buffer-size :initial-element #.%\0))))
    (setf (charw buffer 0) (code-wide-character ev-hash-version))
    (evaluation-value-hash-1 evaluation-value buffer 1)
    buffer))

(defun-simple evaluation-value-hash-1 (evaluation-value buffer index)
  (macrolet ((advance-ev-hash-buffer (buffer short)
	       `(let* ((current-value
			 (wide-character-code (charw ,buffer index)))
		       (new-value (logxorf current-value ,short)))
		  (setf (charw ,buffer index) (code-wide-character new-value))
		  (if (=f index #.ev-hash-buffer-size)
		      (setf index 0)
		      (incff index)))))
    (cond
      ((null evaluation-value)
       (advance-ev-hash-buffer buffer ev-hash-null-code))
      ((evaluation-integer-p evaluation-value)
       (advance-ev-hash-buffer buffer ev-hash-integer-code)
       (advance-ev-hash-buffer
	 buffer
	 (logandf evaluation-value #xFFFF))
       (advance-ev-hash-buffer
	 buffer
	 (logandf (ashf evaluation-value -16) #xFFFF))
       (advance-ev-hash-buffer
         buffer
	 (logandf (ashf evaluation-value -32) #xFFFF))
       (advance-ev-hash-buffer
         buffer
	 (logandf (ashf evaluation-value -48) #xFFFF)))
      ((or (evaluation-symbol-p evaluation-value) 
	   (wide-string-p evaluation-value)) ; (evaluation-text-p evaluation-value)
       (let (text-string)
	 (cond ((evaluation-symbol-p evaluation-value)
		(advance-ev-hash-buffer buffer ev-hash-symbol-code)
		(setf text-string
		      (get-or-make-symbol-name-wide-string-macro
			evaluation-value)))
	       (t
		(advance-ev-hash-buffer buffer ev-hash-text-code)
		(setf text-string evaluation-value)))
	 (loop for i from 0 below (wide-string-length text-string)
	       do
	   (advance-ev-hash-buffer
	     buffer
	     (wide-character-code (charw text-string i))))))
      ((consp evaluation-value)
       (let ((cdr (cdr-of-cons evaluation-value)))
	 (cond
	   ((eq cdr 'sequence)
	    (advance-ev-hash-buffer buffer ev-hash-sequence-code)
	    (loop for element being each evaluation-sequence-element
		  of evaluation-value
		  do
	      (setf index (evaluation-value-hash-1 element buffer index)))) ; make it positive
	   ((eq cdr 'structure)
	    (advance-ev-hash-buffer buffer ev-hash-structure-code)
	    (loop for (k . v)
		      being each evaluation-structure-pair of evaluation-value
		  do
	      (setf index (evaluation-value-hash-1 k buffer index))
	      (setf index (evaluation-value-hash-1 v buffer index))))
	   ((eq cdr 'truth-value)
	    (advance-ev-hash-buffer buffer ev-hash-truth-value-code)
	    #+development
	    (unless (<=f -1000 (car-of-cons evaluation-value) 1000)
	      (error "Truth Value out of range"))
	    (advance-ev-hash-buffer
	      buffer 
	      (+f 1000 (car-of-cons evaluation-value)))))))

      ((evaluation-float-p evaluation-value)
       (advance-ev-hash-buffer buffer ev-hash-float-code)
       (multiple-value-bind (byte0 byte1 byte2 byte3)
	   (partition-float (evaluation-float-value evaluation-value))
	 (advance-ev-hash-buffer buffer byte0)
	 (advance-ev-hash-buffer buffer byte1)
	 (advance-ev-hash-buffer buffer byte2)
	 (advance-ev-hash-buffer buffer byte3)))

      ((evaluation-long-p evaluation-value)
       (advance-ev-hash-buffer buffer ev-hash-long-code)
       (multiple-value-bind (byte0 byte1 byte2 byte3)
	   (partition-long (evaluation-long-value evaluation-value))
	 (advance-ev-hash-buffer buffer byte0)
	 (advance-ev-hash-buffer buffer byte1)
	 (advance-ev-hash-buffer buffer byte2)
	 (advance-ev-hash-buffer buffer byte3)))

      ((evaluation-iteration-state-p evaluation-value)
       ;; do nothing at present
       ))
    index))




;;;; Miscellaneous Goo

;;; The functiopn `convert-type-or-unit-of-measure-to-type' is used to convert a
;;; datum type or unit of measure into the appropriate data type.  Note that
;;; this punts to number when it can't find a definition for the type.

(defun-simple convert-type-or-unit-of-measure-to-type (unit-of-measure-or-type)
  (cond ((symbolic-type-specification-p-macro unit-of-measure-or-type)
	 unit-of-measure-or-type)
	((number-subtype-p unit-of-measure-or-type)
	 'number)
	(t
	 (warn-about-unrecognized-type unit-of-measure-or-type)
	 'number)))





;;;; Defining New Components




;;; The macro `def-component' is used to introduce a symbolic name for a
;;; collection of parts of the KB.  For example, CELL-ARRAY.  It takes one
;;; required argument, which is the name of the component (the car of a
;;; component particulars) and several keyword arguments defining
;;; characteristics of the component.  Note that when defining a new component,
;;; you must also add a writer clause for the component to
;;; denote-component-of-block-1.

;;; The following characteristics can be given to def-component.

;;;   :SETTER The value for this entry is the simple compiled function which can
;;;   put an evaluation-value into the denoted component.  This function should
;;;   take the following arguments: block, component-particulars, new-value.
;;;   The new evaluation-value should be incorporated into the block or
;;;   reclaimed.  If the value is successfully put, this function should return
;;;   NIL.  If there is a problem, then the component should not be modified,
;;;   the evaluation-value should still be reclaimed, and the function should
;;;   return a text string describing the error.  The text string is reclaimed
;;;   by the caller of the setter form.

;;;   :GETTER The value for this entry is a simple compiled function that can
;;;   get the value of a component.  This function should take two arguments,
;;;   the block and the component particulars, and return a copy of the value in
;;;   that component as an evaluation-value.  It is the responsibility of the
;;;   caller to reclaim the returned evaluation-value.  If the value cannot be
;;;   gotten, then the value of no-component-value should be returned.

;;; E.g. (def-component frobnotz :getter #'get-frobnotz :setter #'set-frobnotz)

(defmacro def-component (name &body keywords-and-characteristics)
  (loop for entry-cons on keywords-and-characteristics by #'cddr do
    (unless (and (consp entry-cons)
		 (member (car entry-cons) '(:setter :getter))
		 (consp (cdr entry-cons)))
      (warn "Def-component ~a had a bad keyword arg, ~a." name entry-cons)))
  `(progn
     (pushnew ',name set-of-all-component-kinds)
     (setf (component-kind-description ',name)
	   (list ,@keywords-and-characteristics))))

(defparameter no-component-value (make-symbol "NO-COMPONENT-VALUE"))

(def-global-property-name component-kind-description t)

(defvar set-of-all-component-kinds ())






;;;; Evaluator Access to Components



;;; These tools provide access to components of items within the G2 evaluators
;;; and user-accessible language.  This works through several pathways, one for
;;; attribute style references, one for logical predicates that work through
;;; implied attribute like facilities, and one that works through an
;;; array-reference like facility.  (For now I'm only implementing the
;;; attribute-like tool.  -jra 6/8/93)

;;; `Attribute-mimics' are a type of component particular used to present an
;;; interface to end users for the internals of frames and subparts of frames.
;;; An attribute-mimic can be refered to within G2 expression grammar as "the
;;; <mimic> of <item-or-place-reference>", and for all practical purposes it
;;; will behave like it is an attribute of the object.  However, a attempt to
;;; reference or conclude a mimic attribute will instead dispatch to the
;;; functions defined with the def-attribute-mimic macro.  These functions can
;;; reference a system slot value, compute a new value, or refer to something
;;; else entirely if needed.  However, to the user it the values stored in an
;;; attribute mimic should behave as they were real attributes.  The things
;;; returned by references to attribute mimics can be any kind of
;;; evaluation-value.  Evaluation values include fixnums, managed-floats,
;;; strings, symbols, evaluation-truth-values, or place-references.  When an
;;; attribute mimic returns a place reference, then further attribute mimic
;;; references can be made on that type 

;;; If a user defines an attribute on one of their own classes that collides
;;; with the name of an attribute mimic, then the user defined attribute will
;;; take precedence for instances of that class, and the attribute mimic will
;;; not be accessible on that class.  The term "attribute mimic" is internal to
;;; G2, and is only intended to be different from all the other weird attribute
;;; like mechanisms we have.  To end users, they can think of them as accessible
;;; system slots.

;;; This section provides the following utilities for attribute mimics:
;;; def-attribute-mimic, lookup-attribute-mimic, get-attribute-mimic-value,
;;; put-attribute-mimic-value,

;;; The global property `attribute-mimic' holds information about defined
;;; attribute mimics.

(def-global-property-name attribute-mimic t)




;;; The global property `attribute-mimics-of-class' contains a list of the
;;; symbols naming attribute mimics defined for the class containing this
;;; property.

(def-global-property-name attribute-mimics-of-class t)




;;; The structure `attribute-mimic' holds a type specification of the values
;;; that an attribute mimic can be applied to and a compiled simple function
;;; that returns the place reference to an attribute mimic location.  This
;;; structure is placed onto the attribute-mimic property of an attribute mimic
;;; name.

(def-structure (attribute-mimic
		(:type vector)
		(:constructor
		 make-attribute-mimic
		 (attribute-mimic-argument-type
		  attribute-mimic-value-type
		  attribute-mimic-initial-value
		  attribute-mimic-features
		  attribute-mimic-place-reference-constructor)))
  attribute-mimic-argument-type
  attribute-mimic-value-type
  attribute-mimic-initial-value
  attribute-mimic-features
  attribute-mimic-place-reference-constructor)




;;; The structure and property name `virtual-attribute' define the storage for
;;; definitional information about virtual attributes.  See
;;; def-virtual-attribute for details.

(def-structure (virtual-attribute
		 (:constructor
		   make-virtual-attribute
		   (virtual-attribute-name
		    virtual-attribute-arg-type
		     virtual-attribute-value-type
		     virtual-attribute-features
		     virtual-attribute-initial
		     virtual-attribute-getter?
		     virtual-attribute-setter?))
		 (:print-function print-virtual-attribute))
  virtual-attribute-name
  virtual-attribute-arg-type
  virtual-attribute-value-type
  virtual-attribute-features
  virtual-attribute-initial
  virtual-attribute-getter?
  virtual-attribute-setter?)

(defun print-virtual-attribute (va stream depth)
  (declare (ignore depth) (eliminate-for-gsi))
  (printing-random-object (va stream)
    (format stream "~s ~s"
	    'virtual-attribute
	    (virtual-attribute-name va))))

(def-global-property-name virtual-attribute t)

(def-global-property-name virtual-attributes-local-to-class t)

(defvar virtual-attributes-not-local-to-a-class nil)

(defvar all-virtual-attributes nil)


(defun-simple class-is-specifically-deprecated-in-features-p (class-name features)
  (loop for (feature value) on features by #'cddr
	thereis (and (eq 'deprecated feature)
		     (memq class-name value))))




;;; The macro `def-virtual-attribute' is used to define code which gets and sets
;;; the values of virtual attributes of frames.  These are interfaces to the G2
;;; KB developer.  This macro takes the name (shown to the end user) of the
;;; attribute, the type specification of the classes containing this attribute,
;;; the type-specification of the value of this attribute, and a list of
;;; features of this virtual attribute, similar to slot features.  This macro
;;; also takes a keyword argument describing event-updates from modifications to
;;; this virtual attribute, and three keyword arguments defining functions,
;;; where the format of each keyword value is an argument list followed by list
;;; of forms.

;;; :initial -- It takes a one element argument list containing a symbol naming
;;; a class.  The body should return an evaluation value that would be the
;;; initial value of this virtual attribute for a newly created instance of this
;;; class.

;;; :getter -- This argument is optional, without it the attribute is
;;; write-only.  It takes a one element argument list containing an item.  The
;;; forms should return an evaluation value representing the current value of
;;; this attribute mimic for this item.  The given item is guaranteed to be an
;;; instance of the argument type-specification defined for this virtual
;;; attribute.  The value returned must be of the type described in the value
;;; type specification for this virtual attribute, or the value of the variable
;;; no-component-value to indicate an error.  Note that NIL can be returned from
;;; this form if the type (no-item) is included in the value type specification.
;;; Note that the value returned will be reclaimed by the caller.

;;; :setter -- This argument is optional, without it the attribute is read-only.
;;; It takes a two element argument list containing an item and an evaluation
;;; value.  The item and value are both guaranteed to be instances of the
;;; argument and value type specifications.  The argument should be incorporated
;;; into the item or reclaimed.  This function must either install the given
;;; value into the given frame and return nil, or it must leave the frame unmodified
;;; and return a text string.  In either case, the value must be reclaimed by
;;; this form.

;; I think the preceding documentation is wrong. Evaluation values must *NOT* be
;; be reclaimed by virtual attribute setters. In fact, they get reclaimed
;; automatically in `conclude-into-attribute-component' (see the call in that
;; function to `reclaim-if-evaluation-value' after the call to
;; `conclude-into-virtual-attribute-component'. Actually, all callers of the
;; latter function do the same thing.)  Moreover, all of the
;; def-virtual-attribute setters I looked at did not reclaim their argument.
;; Possibly, it needs to reclaimed if an error is returned.  -fmw, 7/25/03

;;; :event-updates -- This is a required attribute.  This slot is used to
;;; determine whether or not forward chaining is invoked when changes are made
;;; to the value that this slot exports while generating the automated
;;; documentation.  It can have the value NIL or the value :within-putter.  If
;;; the value is :within-putters, then some combination of slot putters or other
;;; code should call update-subscriptions-from-virtual-attribute-change whenever
;;; a system state change is made that could change the value of this virtual
;;; attribute.  Note that this should be done in some location that will be
;;; traversed whenever the virtual attribute value is modified, whether or not
;;; that happens through the setter here or through some other pathway.  Since
;;; we have a choice per vitual attribute about whether we will trigger
;;; event-updates, for some we will choose to not trigger them at all (and
;;; supply an :event-updates of NIL for this attribute) because the number of
;;; locations that would have to trigger the event-updates are too complex for
;;; us to implement.  (See notes below this function for an alternative to this
;;; implementation of this slot.  -jallard 5/2/97)

(defmacro def-virtual-attribute
    (name (arg-type-spec value-type-spec features)
	  &key (event-updates :unspecified)
	  initial getter setter do-not-include-in-lists-p)
  (clear-all-evaluator-slot-info)
  (let ((initial-name (intern (format nil "INITIAL-~a" name)))
	(getter-name (intern (format nil "GET-~a" name)))
	(setter-name (intern (format nil "SET-~a" name)))
	(push-op (if (eval-feature :translator) 'push 'pushnew))
	(name-for-list (if (and (consp features)
				(class-type-specification-p arg-type-spec)
				(class-is-specifically-deprecated-in-features-p
				  (type-specification-class arg-type-spec)
				  features))
			   (list name 'deprecated)
			   name)))
    (unless (or (null event-updates)
		(eq event-updates :within-putter))
      (warn "~a virtual-attribute must specify an :event-updates argument."
	    name))
    (when (or (null initial)
	      (and (null getter) (null setter)))
      (error "Virtual-attribute ~a must have an initial value function and ~
	      at least a setter or a getter."
	     name))
    (unless (valid-type-specification-p arg-type-spec)
      (error "Virtual-attribute ~S has an invalid arg-type-spec.~%~
             To debug, type:~%~
             (trace valid-type-specification-p boolean-composition-over-symbols-p)~%~
             (valid-type-specification-p '<the-type-spec-goes-here>)"
	      name))
    (unless (or (class-type-specification-p arg-type-spec)
		(class-disjunction-type-specification-p arg-type-spec))
      (error "arg type-specification must be a class or classes"))
    (unless (valid-type-specification-p value-type-spec)
      (error "Virtual-attribute ~S has an invalid value-type-spec.~%~
             To debug, type:~%~
             (trace valid-type-specification-p boolean-composition-over-symbols-p)~%~
             (valid-type-specification-p '<the-type-spec-goes-here>)"
	      name))
    (unless (let ((boolean-composition-over-symbols-allows-top-level-symbols-p nil))
	      (valid-type-specification-p value-type-spec))
      (warn "in v.a. ~A: T2 may not be able to handle minimum-contents as a symbol. Use (AND <symbol>) instead" name))
    `(progn
       ,@(unless do-not-include-in-lists-p
	   `((,push-op ',name all-virtual-attributes)
	     (,push-op ',name-for-list
		       ,(if (class-type-specification-p arg-type-spec)
			    `(virtual-attributes-local-to-class
			       ',(type-specification-class arg-type-spec))
			    'virtual-attributes-not-local-to-a-class))))
       (defun-simple ,initial-name ,@initial)
       ,@(when getter
	   `((defun-simple ,getter-name ,@getter)))
       ,@(when setter
	   `((defun-simple ,setter-name ,@setter)))
       (add-virtual-attribute
	 ',name
	 ',arg-type-spec ',value-type-spec
	 ',(if event-updates
	       (cons :event-updates (cons event-updates features))
	       features)
	 (function ,initial-name)
	 ,(if getter `(function ,getter-name) nil)
	 ,(if setter `(function ,setter-name) nil)))))

(defun-simple add-virtual-attribute (name arg-type-spec value-type-spec features initial getter setter)
  (let ((va (virtual-attribute name)))
    (cond (va
	   (setf (virtual-attribute-arg-type va) arg-type-spec)
	   (setf (virtual-attribute-value-type va) value-type-spec)
	   (setf (virtual-attribute-features va) features)
	   (setf (virtual-attribute-initial va) initial)
	   (setf (virtual-attribute-getter? va) getter)
	   (setf (virtual-attribute-setter? va) setter)
	   va)
	  (t
	   (setf (virtual-attribute name)
		 (make-virtual-attribute name arg-type-spec value-type-spec features initial getter setter)))))
  name)

;; We had considered another approach for :event-updates, where this argument
;; could take a list of symbols naming system attributes, and then cause the
;; change-slot-value code to invoke forward chaining for this virtual attribute
;; whenever any of those attributes was modified, but there would be very few
;; uses of that functionality now, and it would add an extra global
;; property-list lookup for every system attribute setting.  We'll pass for now.
;; -jallard 4/30/97




(defun-for-macro class-disjunction-type-specification-p (type-specification)
  (and (union-type-specification-p type-specification)
       (loop for sub-type in (cdr type-specification)
	     always (class-type-specification-p sub-type))))

#+unused
(defun-simple virtual-attribute-classes (virtual-attribute)
  (let ((arg-type (virtual-attribute-arg-type virtual-attribute)))
    (cond
      ((class-type-specification-p arg-type)
       (gensym-list (type-specification-class arg-type)))
      (t
       (loop for sub-type in (cdr arg-type)
	     collect (type-specification-class sub-type)
	       using gensym-cons)))))

;;; `virtual-attribute-defined-for-class?' tests to see if the given virtual
;;; attribute is defined on a class and additionally return which class
;;; in the def-virtual-attribute definition was used.

(defun-simple virtual-attribute-defined-for-class? (virtual-attribute class)
  (let ((arg-type (virtual-attribute-arg-type virtual-attribute)))
    (cond
      ((class-type-specification-p arg-type)
       (let ((sub-type-class (type-specification-class arg-type)))
	 (and (subclassp class sub-type-class)
	      sub-type-class)))
      (t
       (loop for sub-type in (cdr-of-cons arg-type)
	     as sub-type-class = (type-specification-class sub-type)
	     when (subclassp class sub-type-class)
	       return sub-type-class)))))

;;; The following routines are services provided by virtual functions to the
;;; infrastructure for fetching, assigning, and querying information about
;;; virtual functions.

;;; The `virtual-function global property name' and the type-specification
;;; containing attributes of the `virtual-function structure' are considered
;;; part of the external interface to virtual functions.  The global variable
;;; `all-virtual-attributes' may also be used.

;;; The function `place-reference-of-virtual-attribute?' takes a frame and a
;;; symbol possibly naming a virtual attribute.  If a virtual attribute of the
;;; given name exists for the given frame, a place reference to it is returned.
;;; If no such virtual attribute exists for that frame, NIL is returned.

(defun-simple place-reference-of-virtual-attribute? (frame attribute)
  (let ((virtual-attribute? (virtual-attribute attribute)))
    (when virtual-attribute?
      (let ((frame-type-spec (virtual-attribute-arg-type virtual-attribute?)))
	(when (type-specification-type-p frame frame-type-spec)
	  (make-evaluation-place-reference-to-place
	    (slot-value-list 'virtual-attribute attribute
			     '*current-computation-frame*)
	    frame))))))




;;; The macro `virtual-attribute-component-particulars-p' takes component
;;; particular and checks that it is for a virtual-attribute.  The macro
;;; `virtual-attribute-component-particulars-name' fetches the attribute name
;;; from a virtual attribute component.

(def-substitution-macro virtual-attribute-component-particulars-p
    (component-particulars)
  (and (consp component-particulars)
       (eq (car-of-cons component-particulars) 'virtual-attribute)))

(defmacro virtual-attribute-component-particulars-name (component-particulars)
  `(cadr-of-conses ,component-particulars))

(defmacro virtual-attribute-further-component (component-particulars)
  `(caddr-of-conses ,component-particulars))

(defmacro with-virtual-attribute-component-particulars
    (((name further-component) virtual-attribute-component-particulars)
     &body body)
  (let ((cons-var (gensym)))
    `(let* ((,cons-var (cdr-of-cons ,virtual-attribute-component-particulars))
	    (,name (car-of-cons ,cons-var))
	    (,further-component (cadr-of-conses ,cons-var)))
       ,@body)))




;;; The macros `get-virtual-attribute' and `set-virtual-attribute' implement
;;; calls to the getter and setter functions for virtual attributes.  These
;;; should only be called when the frame has been verified to fit within the
;;; argument type specification, and the setter should only be called when the
;;; new-value fits within the value type-specification.

(defmacro call-get-virtual-attribute-fn (getter? block)
  `(funcall-simple-compiled-function ,getter? ,block))

(def-substitution-macro get-virtual-attribute (block virtual-attribute)
  (let ((getter? (virtual-attribute-getter? virtual-attribute)))
    (if getter?
	(call-get-virtual-attribute-fn getter? block)
	no-component-value)))

(defmacro call-set-virtual-attribute-fn (setter? block new-value)
  `(funcall-simple-compiled-function ,setter? ,block ,new-value))

(def-substitution-macro set-virtual-attribute
    (block name virtual-attribute new-value)
  (let ((setter? (virtual-attribute-setter? virtual-attribute)))
    (if setter?
	(call-set-virtual-attribute-fn setter? block new-value)
	(tformat-text-string "The attribute ~a of ~NF is read-only."
			     name block))))



;;; The functions `get-virtual-attribute-component' and
;;; `set-virtual-attribute-component' are used in the implementation for the
;;; virtual-attribute component.

(defun-simple get-virtual-attribute-component (block component-particulars)
  (let* ((name (virtual-attribute-component-particulars-name
		 component-particulars))
	 (virtual-attribute? (virtual-attribute-macro name)))
    (if virtual-attribute?
	(get-virtual-attribute block virtual-attribute?)
	no-component-value)))

(defun-simple set-virtual-attribute-component
    (block component-particulars new-value)
  (let* ((name (virtual-attribute-component-particulars-name
		 component-particulars))
	 (virtual-attribute? (virtual-attribute-macro name)))
    (if virtual-attribute?
	(set-virtual-attribute block name virtual-attribute? new-value)
	(tformat-text-string "No attribute named ~a exists in ~NF."
			     name block))))




;;; The `virtual-attribute' component is used to implement component particulars
;;; and place references for things that look to users like attributes but are
;;; instead defined via getter and setter forms.  A virtual attribute stores the
;;; symbol naming the virtual attribute.

(def-component virtual-attribute
  :getter #'get-virtual-attribute-component
  :setter #'set-virtual-attribute-component)



;;

;; Operations needed on place-references.

;;   Make
;;   Get
;;   Put
;;   Type-of-gotten-value
;;   Type-of
;;   Denote
;;   Component-particulars-type?
;;   Type-p <place-reference> <component-particulars-symbol-name>

;; Place references have the format
;;   (<component-particulars> <item-or-place-reference> <frame-serial-number>).

;; Place reference A = ((attribute-mimic formatting) #<item 4DAC> 72) and is of
;; type (place-reference (component-particular attribute-mimic)).

;; Type-of-gotten-value of A returns 
;; (place-reference (component-particular formatting)).

;; Get of A returns ((formatting . *current-computation-frame*) #<item 4DAC> 72), a
;; place reference.  Call this place reference B.

;; Type-of-gotten-value of B returns NIL.  (I.e. it is an intermediate structure
;; that you can't get.)

;; Place reference C =
;;   ((attribute-mimic foreground-color) 
;;    ((formatting . *current-computation-frame*) #<item 4DAC> 72)
;;    nil)

;; Type-of-gotten-value of C returns SYMBOL, though in the future it could
;; return (and symbol (member red blue lavender ...)).

;; Get of C returns RED.








;;;; Category <--> Evaluator Interface




;;; This section defines the basics for turning evaluation-values into
;;; slot-values and vice-versa, for system-defined slots that previously only
;;; accessible through get and change the text operations.  The macro
;;; `define-category-evaluator-interface' is the business end of this facility.
;;; The meta-data that it build is placed on top-level grammar categories
;;; (i.e. ones that are used in the (type ...) feature in some system-defined
;;; def-class).  The most important declarative feature of this interface is
;;; that it makes and equivalence between a category and a complex
;;; type-specification.
;;;
;;; An outline of how this takes place is as follows.
;;;
;;; Getting a slot-values as an evaluation-value (Easy)
;;;
;;; 1. Get slot value from slot of frame.
;;;
;;; 2. call (slot-value-to-evaluation-value-function category) on it
;;;
;;; Concluding an evaluation-value into a slot. (Hard)
;;; 
;;; 1 Get an evaluation-value from the user.
;;;
;;; 2 call (evaluation-value-to-category-function category) on it
;;;    2.1 This function checks that the evaluation-value matches the complex
;;;        type-specifcation.  This is done with a predicate that is
;;;        whipped up automatically by define-category-evaluator-interface from
;;;        the type-specification.
;;;    2.2 It makes a parse-result (usually a tree of phrase conses over symbols,
;;;        text-strings, and numbers).  This parse result should be the same
;;;        as what would be generated by the G2 parser if the same grammar
;;;        category successfully parsed a piece of text given by the user.
;;; 
;;; 3 The slot value compiler is called.
;;;    3.1 This is still necessary because grammar rules or
;;;        evaluation-value-to-category-function's only do syntactic verification
;;;        and transformation (with the usual exceptions and disclaimers).
;;; 
;;; 4 Change-slot-value (or the equivalent) is called.
;;;    4.1 Slot-putters, consistency analysis, and other fallout handlers
;;;        are triggered.

#+developments
(eval-when (:compile-toplevel :load-toplevel :execute)
  (pushnew :generate-category-type-predicates *features*))

(def-global-property-name category-evaluator-interface)

(def-structure (category-evaluator-interface
		 (:constructor
		   make-category-evaluator-interface
		   (category-evaluator-interface-name))
		 #+development
		 (:print-function print-category-evaluator-interface))
  category-evaluator-interface-name
  (interface-slot-value-to-evaluation-value-function nil)
  (interface-evaluation-value-to-category-function nil))

#+development
(defun print-category-evaluator-interface (cei stream depth)
  (declare (ignore depth) (eliminate-for-gsi))
  (printing-random-object (cei stream)
    (format stream "~s ~s"
	    'category-evaluator-interface
	    (category-evaluator-interface-name cei))))

(defun get-category-evaluator-interface (name)
  (or (category-evaluator-interface name)
      (setf (category-evaluator-interface name)
	    (make-category-evaluator-interface name))))

(defmacro evaluation-value-to-category-function (name)
  `(let ((category-evaluator-interface
	   (category-evaluator-interface ,name)))
     (and category-evaluator-interface
	  (interface-evaluation-value-to-category-function
	    category-evaluator-interface))))

(defun set-evaluation-value-to-category-function (name value)
  (setf (interface-evaluation-value-to-category-function
	  (get-category-evaluator-interface name))
	value))

(defsetf evaluation-value-to-category-function
    set-evaluation-value-to-category-function)

(defmacro slot-value-to-evaluation-value-function (name)
  `(let ((category-evaluator-interface
	   (category-evaluator-interface ,name)))
     (and category-evaluator-interface
	  (interface-slot-value-to-evaluation-value-function
	    category-evaluator-interface))))

(defun set-slot-value-to-evaluation-value-function (name value)
  (setf (interface-slot-value-to-evaluation-value-function
	  (get-category-evaluator-interface name))
	value))

(defsetf slot-value-to-evaluation-value-function
    set-slot-value-to-evaluation-value-function)

(defmacro category-evaluator-interface-from-slot-type (type)
  `(category-evaluator-interface
     (category-symbol-given-slot-type ,type)))

(defvar last-reason-for-complex-type-rejection)


;;; `parse-complex-type-specification' is an internal function for making type predicates
;;; from complex type specifications.  It walks the spec in a recursive sub-function,
;;; make-predicate, generating lisp code.

(defvar structure-slot-not-bound '(structure-slot-not-bound))

(defun-for-macro symbol-in-tree-p (exp symbol)
  (if (atom exp)
      (eq exp symbol)
      (or (symbol-in-tree-p (car exp) symbol)
	  (symbol-in-tree-p (cdr exp) symbol))))

(defun-for-macro substitute-names-for-predicates (exp env)
  (if (atom exp)
      (or (cdr (assq exp env))
	  exp)
      (cons (car exp)
	    (loop for exp-1 in (cdr exp)
		  collect (substitute-names-for-predicates exp-1 env)))))

(defun-for-macro get-complex-type-structure-table (exp)
  (if (atom exp)
      nil
      (case (car exp)
	((or and not)
	 (mapcan #'get-complex-type-structure-table (cdr exp)))
	(named
	 (get-complex-type-structure-table
	   (get-augmented-type-specification-from-complex
	     (type-specification-complex-expansion (cadr exp)))))
	(sequence
	 (destructuring-lambda-list (sub-type &optional minimum-length maximum-length)
	     (cdr exp)
	   (declare (ignore minimum-length maximum-length))
	   (get-complex-type-structure-table sub-type)))
	(structure
	 (destructuring-lambda-list (name slots &optional minimum-contents)
	     (cdr exp)
	   (declare (ignore minimum-contents))
	   (cons (cons name (mapcar 'car slots))
		 (loop for (name type) in slots
		       nconc (get-complex-type-structure-table type))))))))

;the caller should bind these to nil
(defvar reason-for-type-failure nil)
(defvar type-at-type-failure nil)
(defvar value-at-type-failure nil)
(defvar context-of-type-failure nil)
(defvar last-slot-checked-of-type-failure nil)

(defvar structure-specs-allow-unknown-slots-p nil)
(defvar current-category-name-for-type-specification-type-p nil)

#+development ; something to trace
(defun-simple set-reason-for-type-failure-1 (reason)
  (setq reason-for-type-failure reason))

(defmacro set-reason-for-type-failure (reason)
  #+development
  `(set-reason-for-type-failure-1 ,reason)
  #-development
  `(setq reason-for-type-failure ,reason))

(defun-simple type-specification-type-p--with-explanation (thing type)
  (if (evaluation-item-reference-p thing)
      (type-specification-type-p--with-explanation
       (evaluation-item-reference-referenced-item thing)
       type)
      (case (and (consp type) (car-of-cons type))
	(or
	 (type-specification-type-p--with-explanation--or thing type))
	(and
	 (loop for required-type in (cdr-of-cons type)
	       always (type-specification-type-p--with-explanation thing required-type)))
	(sequence
	 (type-specification-type-p--with-explanation--sequence thing type))
	(structure
	 (type-specification-type-p--with-explanation--structure thing type))
	(named
	 (let* ((name (cadr type))
	        (current-category-name-for-type-specification-type-p name))
	   (if (and (symbolp (cadr type))
	            (eq (cadr type) 'color-or-metacolor))
	     (neq (color-or-metacolor-p thing) nil)
	     (type-specification-type-p--with-explanation
	       thing
	       (type-specification-complex-expansion name)))))
	(t
	 (or (type-specification-type-p thing type)
	     (progn
	       (unless reason-for-type-failure
		 (setq value-at-type-failure thing)
		 (setq type-at-type-failure type)
		 (set-reason-for-type-failure 'type-mismatch))
	       nil))))))

;;;Special cases that are not yet handled
;layer
;line-drawing-element
;line-drawing-elements

;;; Special Cases Involving OR (handled in the OR)
;(1) restrict-proprietary-items-and-configure-user-interface-statement
;  (or (named menu-configurations) (named ...) ...)
;menu-configurations
;  (structure menu-configurations-spec
;    ((operation-type (member workspace-menu item-menu non-menu)) ...)
;    (and operation-type ...))

;(2) default-overrides-for-class-definitions, default-overrides-for-object-definitions
;  (sequence
;   (or (structure override-on-user-defined-slot-spec
;          ((user-attribute-name symbol) ...) (and user-attribute-name))
;       (structure override-on-system-defined-slot-spec
;          ((system-attribute-designation symbol) (and system-attribute-designation)))

(defun type-specification-type-p--with-explanation--or (thing type)
  (or (loop for required-type in (cdr-of-cons type)
	    thereis (type-specification-type-p thing required-type))
      (let* ((type-name current-category-name-for-type-specification-type-p)
	     (discriminant-list
	      (case type-name
		((default-overrides-for-class-definitions default-overrides-for-object-definitions)
		 '(user-attribute-name system-attribute-designation))
		(restrict-proprietary-items-and-configure-user-interface-statement
		 '(operation-type)))))
	(unless reason-for-type-failure
	  (set-reason-for-type-failure
	   (cond ((loop for required-type in (cdr-of-cons type)
			for required-type1 = (expand-named-type required-type)
			for simplified-type = (cond ((not (consp required-type1))
						     required-type)
						    ((eq (car required-type1) 'sequence)
						     '(sequence))
						    ((eq (car required-type1) 'structure)
						     '(structure))
						    (t
						     required-type))
			never (type-specification-type-p thing simplified-type))
		  (setq value-at-type-failure thing)
		  (setq type-at-type-failure type)
		  'simple-type-mismatch)
		 (discriminant-list
		  (loop for required-type in (cdr-of-cons type)
			do (type-specification-type-p--with-explanation
			    thing required-type) ; will return nil.
			unless (and (consp context-of-type-failure)
				    (null (cdr context-of-type-failure))
				    (memq (car context-of-type-failure) discriminant-list))
			  return reason-for-type-failure
			do (setq reason-for-type-failure nil)
			   (setq context-of-type-failure nil)
			   (setq last-slot-checked-of-type-failure nil)
			finally
			  (cond
			    ((cdr discriminant-list)
			     (setq value-at-type-failure thing)
			     (setq type-at-type-failure type)
			     (return 'neither-uan-nor-sad-present))
			    ((eq structure-slot-not-bound
				 (setq value-at-type-failure
				       (evaluation-structure-slot thing (car discriminant-list)
								  structure-slot-not-bound)))
			     (setq value-at-type-failure thing)
			     (setq type-at-type-failure type)
			     (setq last-slot-checked-of-type-failure structure-slot-not-bound)
			     (return 'invalid-operation-type))
			    (t
			     (setq type-at-type-failure
				   (get-combined-type-for-operation-type type))
			     (return 'structure-choose-type-mismatch)))))
		 ((loop with last = (car (last type))
			for required-type in (cdr-of-cons type)
			for sequence-or-structure-p = (and (consp required-type)
							   (or (eq (car required-type) 'sequence)
							       (eq (car required-type) 'structure)))
			always (or (not (consp required-type))
				   (if (eq required-type last)
				       sequence-or-structure-p
				       (not sequence-or-structure-p))))
		  (type-specification-type-p--with-explanation thing (car (last type)))
		  reason-for-type-failure)
		 (t
		  (setq value-at-type-failure thing)
		  (setq type-at-type-failure type)
		  'type-mismatch))))
	nil)))

(defun get-combined-type-for-operation-type (type)
  (eval-cons 'member
	     (loop for choice in (cdr type)
		   for choice-type = (type-specification-complex-expansion (cadr choice))
		   as member-type = (second (first (second choice-type)))
		   nconc (copy-list-using-eval-conses (cdr member-type)))))

(defun type-specification-type-p--with-explanation--sequence (thing type)
  (cond ((not (and (consp thing)
		   (eq 'sequence (aggregate-evaluation-value-type-symbol thing))))
	 (setq value-at-type-failure thing)
	 (setq type-at-type-failure '(sequence))
	 (set-reason-for-type-failure 'simple-type-mismatch)
	 nil)
	((not (aggregate-value-type-specification-has-details-p type))
	 t)
	(t
	 (let* ((element-type (sequence-type-specification-element-type type))
		(low-bound? (sequence-type-specification-low-bound type))
		(high-bound? (and low-bound?
				  (sequence-type-specification-high-bound type)))
		(length? (and low-bound?
			      (evaluation-sequence-length thing))))
	   (and (or (not low-bound?)
		    (<=f low-bound? length?)
		    (progn
		      (setq value-at-type-failure thing)
		      (setq type-at-type-failure type)
		      (set-reason-for-type-failure 'sequence-too-short)
		      nil))
		(or (not high-bound?)
		    (<f length? high-bound?)
		    (progn
		      (setq value-at-type-failure thing)
		      (setq type-at-type-failure type)
		      (set-reason-for-type-failure 'sequence-too-long)
		      nil))
		(loop for element being each evaluation-sequence-element of thing
		      for index from 0
		      always (or (type-specification-type-p--with-explanation element element-type)
				 (progn
				   (eval-push index context-of-type-failure)
				   nil))))))))

;;; Special Cases Involving OR (handled in the enclosing STRUCTURE)
;(1) constrain-movement-of-items
;  (structure constrain-movement-of-items-spec
;    ((type-of-region (member rectangle grid))
;     (constrained-region (or (named rectangle) (named grid))) ...)
;    (and type-of-region constrained-region ...))
;rectangle
;  (structure rectangle-spec
;    ((left-edge integer) ...) (and left-edge ...))
;grid
;  (structure grid-spec
;    ((x-grid-length integer) ...) (and x-grid-length ...))

;(2) object-configuration-spec
; (structure object-configuration-spec
;   ((type (member configure-user-interface ...))
;    (clauses (or (named configure-user-interface) ...))
;   (and type clauses))
;configure-user-interface
; (sequence
;   (structure configure-user-interface-spec
;     ((applicable-user-modes (named applicable-user-modes))
;      (statements (named configure-user-interface-statements)))
;     (and applicable-user-modes statements))
;   1)
;configure-user-interface-statements
; (sequence (named restrict-proprietary-items-and-configure-user-interface-statement) 1)

(defun type-specification-type-p--with-explanation--structure (thing type)
  (cond ((not (and (consp thing)
		   (eq 'structure (aggregate-evaluation-value-type-symbol thing))))
	 (setq value-at-type-failure thing)
	 (setq type-at-type-failure '(structure))
	 (set-reason-for-type-failure 'simple-type-mismatch)
	 nil)
	((not (aggregate-value-type-specification-has-details-p type))
	 t)
	(t
	 (let* ((slot-specifications (second type))
		(minimum-contents (third type))
		(type-name current-category-name-for-type-specification-type-p)
		(slot-containing-structure-type-name?
		 (case type-name
		   (constrain-movement-of-items 'type-of-region)
		   (object-configuration-spec 'type)))
		(slot-containing-structure?
		 (when slot-containing-structure-type-name?
		   (case type-name
		     (constrain-movement-of-items 'constrained-region)
		     (object-configuration-spec 'clauses)))))
	   (and
	    ;; test to see if all slots present in the type are of the correct type
	    (loop for (slot-name slot-type) in slot-specifications
		  as slot-value = (evaluation-structure-slot thing slot-name
							     structure-slot-not-bound)
		  always (or (eq slot-value structure-slot-not-bound)
			     (if (and slot-containing-structure?
				      (eq slot-name slot-containing-structure?))
				 (let* ((type (evaluation-structure-slot
					       thing slot-containing-structure-type-name?))
					(actual-slot-type (eval-list 'named type)))
				   (prog1 (type-specification-type-p--with-explanation
					   slot-value actual-slot-type)
				     (reclaim-eval-list actual-slot-type)))
				 (type-specification-type-p--with-explanation
				  slot-value slot-type))
			     (progn
			       (eval-push slot-name context-of-type-failure)
			       nil)))
	    ;; test to see if all slots present in structure are specified in the type
	    (or structure-specs-allow-unknown-slots-p
		(loop for (slot-name . slot-value) being evaluation-structure-pair of thing
		      as slot-specification? = (assq slot-name slot-specifications)
		      always (or slot-specification?
				 (progn
				   (setq value-at-type-failure thing)
				   (setq type-at-type-failure type)
				   (set-reason-for-type-failure 'unknown-extra-structure-slot)
				   (setq last-slot-checked-of-type-failure slot-name)
				   nil))))
	    ;; see if the structure is as complete as the minimum-contents requires
	    (or (null minimum-contents)
		(if (and (consp minimum-contents)
			 (eq 'and (car-of-cons minimum-contents)))
		    (loop for conjunct in (cdr-of-cons minimum-contents) 
			  always (or (eval-minimum-structure-contents conjunct thing)
				     (progn
				       (setq value-at-type-failure thing)
				       (setq type-at-type-failure type)
				       (set-reason-for-type-failure 'missing-required-structure-slots)
				       (setq last-slot-checked-of-type-failure conjunct)
				       nil)))
		    (or (eval-minimum-structure-contents minimum-contents thing)
			(progn
			  (set-reason-for-type-failure 'missing-required-structure-slots)
			  (setq last-slot-checked-of-type-failure
				(if (and (consp minimum-contents)
					 (eq (car minimum-contents) 'or))
				    (cdr minimum-contents)
				    minimum-contents))
			  nil)))))))))

#+generate-category-type-predicates
(defun-for-macro make-complex-type-predicate--or (exp binding return-reason-p)
  (let* ((structure-slot-info
	   (loop for type in (cdr exp)
		 for expanded-type = (expand-named-type type)
		 for structure-info = (when (consp expanded-type)
					(case (car expanded-type)
					  (structure (cdr expanded-type))
					  (sequence
					   (let ((et (expand-named-type (cadr expanded-type))))
					     (when (and (consp et)
							(eq 'structure (car et)))
					       (cdr et))))))
		 for structure-info1 = (if (and (car structure-info)
						(symbolp (car structure-info)))
					   (cdr structure-info)
					   structure-info)
		 collect structure-info1))
	 (operation-type-in-every-structure-p
	   (loop for structure-info in structure-slot-info
		 collect (when structure-info
			   (let ((slots (car structure-info)))
			     (cadr (assq 'operation-type slots))))))
	 (required-slots-in-every-structure
	   (loop for structure-info in structure-slot-info
		 collect (when structure-info
			   (let ((required (cadr structure-info)))
			     (if (and (consp required)
				      (eq (car required) 'and))
				 (cdr required)
				 (list required))))))
	 (unique-slot-from-every-structure
	   (loop for type in (cdr exp)
		 for required-slots in required-slots-in-every-structure
		 for i from 0
		 collect (if (equal type '(named restrict-proprietary-items))
			     'operation-type
			     (loop for candidate-slot in required-slots
				   when (loop for other-required-slots in required-slots-in-every-structure
					      for j from 0
					      always (or (=f i j)
							 (not (memq candidate-slot other-required-slots))))
				     return candidate-slot)))))
    (cond
      ((not (memq nil operation-type-in-every-structure-p))
       (let ((operation-type (make-symbol "OPERATION-TYPE"))
	     (sequencep (make-symbol "SEQUENCEP")))
	 `(let* ((,sequencep (and (evaluation-sequence-p ,binding)
				  (<f 0 (evaluation-sequence-length ,binding))))
		 (,operation-type (if ,sequencep
				      (evaluation-sequence-aref ,binding 0)
				      ,binding)))		    
	    (setq ,operation-type
		  (if (evaluation-structure-p ,operation-type)
		      (evaluation-structure-slot ,operation-type 'operation-type structure-slot-not-bound)
		      structure-slot-not-bound))
	    (cond
	      ((eq ,operation-type structure-slot-not-bound)
	       ,@(when return-reason-p
		   `((setq value-at-type-failure ,binding)
		     (setq type-at-type-failure ',exp)
		     (setq reason-for-type-failure 'invalid-operation-type)
		     (setq last-slot-checked-of-type-failure ,operation-type)
		     (when ,sequencep
		       (eval-push 0 context-of-type-failure))))
	       nil)		      
	      ,@(loop for sub-exp in (cdr exp)
		      for type in operation-type-in-every-structure-p
		      collect `(,(make-complex-type-predicate type operation-type nil)
				 ,(make-complex-type-predicate sub-exp binding return-reason-p)))
	      (t
	       ,@(when return-reason-p
		   `((setq value-at-type-failure ,operation-type)
		     (setq type-at-type-failure '(member ,@(loop for type in operation-type-in-every-structure-p
								 append (and (consp type)
									     (eq (car type) 'member)
									     (cdr type)))))
		     (setq reason-for-type-failure 'type-mismatch)
		     (eval-push 'operation-type context-of-type-failure)
		     (when ,sequencep
		       (eval-push 0 context-of-type-failure))))
	       nil)))))
      ((not (memq nil unique-slot-from-every-structure))
       (let ((structure (make-symbol "STRUCTURE")))
	 `(let ((,structure (if (and (evaluation-sequence-p ,binding)
				     (<f 0 (evaluation-sequence-length ,binding)))
				(evaluation-sequence-aref ,binding 0)
				,binding)))
	    (cond
	      ,@(loop for unique-slot in unique-slot-from-every-structure
		      for sub-exp in (cdr exp)
		      collect `((neq structure-slot-not-bound
				     (evaluation-structure-slot ,structure ',unique-slot structure-slot-not-bound))
				,(make-complex-type-predicate sub-exp binding return-reason-p)))
	      (t
	       ,@(when return-reason-p
		   `((setq value-at-type-failure ,binding)
		     (setq type-at-type-failure ',exp)
		     (setq reason-for-type-failure 'missing-required-structure-slots)
		     (setq last-slot-checked-of-type-failure ',unique-slot-from-every-structure)))
	       nil)))))
      (t
       (let* ((all-but-last (butlast (cdr exp)))
	      (last (car (last (cdr exp))))
	      (checkp (and (loop for form in all-but-last
				 always (or (symbolp form) (equal form '(no-item))))
			   (consp last))))
	 `(or ,@(loop for sub-exp in all-but-last
		      collect (make-complex-type-predicate sub-exp binding nil))
	      ,(if checkp
		   (make-complex-type-predicate last binding return-reason-p)
		   (make-complex-type-predicate last binding nil))))))))

#+generate-category-type-predicates
(defun-for-macro make-complex-type-predicate (exp binding return-reason-p)
  (macrolet ((maybe-set-type-failure-reason (predicate return-reason-p failure-value failure-type failure-reason)
	       `(if (not ,return-reason-p)
		    ,predicate
		    (let ((typep (make-symbol "TYPEP")))
		      `(let ((,typep ,,predicate))
			 (unless ,typep
			   (setq value-at-type-failure ,,failure-value)
			   (setq type-at-type-failure ',,failure-type)
			   (setq reason-for-type-failure ,',failure-reason))
			 ,typep)))))
    (if (atom exp)
	(maybe-set-type-failure-reason
	  `(type-specification-type-p ,binding ',exp)
	  return-reason-p binding exp 'type-mismatch)
	(case (car exp)
	  (or
	   (make-complex-type-predicate--or exp binding return-reason-p))
	  (and
	   `(and ,@(loop for sub-exp in (cdr exp)
			 collect (make-complex-type-predicate sub-exp binding return-reason-p))))
	  (not
	   `(not ,(make-complex-type-predicate (cadr exp) binding nil)))
	  (named
	   (make-complex-type-predicate
	    (get-augmented-type-specification-from-complex
	     (or (type-specification-complex-expansion (cadr exp))
		 (error "unknown type-specification")))
	    binding
	    return-reason-p))
	  (sequence
	   (destructuring-lambda-list (sub-type &optional minimum-length maximum-length)
	       (cdr exp)
	     (let ((sub-binding (gensym)))
	       `(and
		 ,(maybe-set-type-failure-reason
		   `(type-specification-type-p ,binding '(sequence))
		   return-reason-p binding '(sequence) 'simple-type-mismatch)
		 (let (,@(when (or minimum-length maximum-length)
			   `((length (evaluation-sequence-length ,binding)))))
		   (and
		    ,@(when minimum-length
			`(,(maybe-set-type-failure-reason
			    `(>=f length ,minimum-length)
			    return-reason-p binding exp 'sequence-too-short)))
		    ,@(when maximum-length
			`(,(maybe-set-type-failure-reason
			    `(<=f length ,maximum-length)
			    return-reason-p binding exp 'sequence-too-long)))
		    ,@(when (cdr exp)
			`((loop for ,sub-binding
				    being each evaluation-sequence-element of ,binding
				for index from 0
				always (or ,(make-complex-type-predicate sub-type sub-binding return-reason-p)
					   ,@(when context-of-type-failure
					       `((progn
						   (eval-push index context-of-type-failure)
						   nil)))))))))))))	
	  (structure
	   (destructuring-lambda-list (structure-name slots &optional minimum-contents)
	       (cdr exp)
	     (when (and minimum-contents (symbolp minimum-contents))
	       (warn "in structure ~A: T2 may not be able to handle minimum-contents as a symbol. Use (AND <symbol>) instead"
		     structure-name))
	     (let ((slot-vars
		    (loop for (name type) in slots
			  collect (make-symbol (format nil "~A" name))))
		   (slot-present-p-vars
		    (loop for (name type) in slots
			  collect (make-symbol (format nil "~A-~A" name 'present-p)))))
	       `(and
		 ,(maybe-set-type-failure-reason
		   `(type-specification-type-p ,binding '(structure))
		   return-reason-p binding '(structure) 'simple-type-mismatch)
		 (let ,(loop for (slot-name slot-type) in slots
			     for slot-var in slot-vars
			     collect `(,slot-var
				       (evaluation-structure-slot
					,binding ',slot-name structure-slot-not-bound)))
		   (let ,(loop for (slot-name slot-type) in slots
			       for slot-var in slot-vars
			       for slot-present-p-var in slot-present-p-vars
			       collect `(,slot-present-p-var
					 (neq ,slot-var structure-slot-not-bound)))
		     (and
		      ,@(loop for (slot-name slot-type) in slots
			      for slot-var in slot-vars
			      for slot-present-p-var in slot-present-p-vars
			      for object-configuration-spec-clauses-p
				  = (and (eq slot-name 'clauses)
					 (equal slot-type
						`(or (named configure-user-interface)
						     (named restrict-proprietary-items)
						     (named set-up-network-access)
						     (named declare-properties)
						     (named comment))))
			      collect `(or (not ,slot-present-p-var)
					   ,(if object-configuration-spec-clauses-p
						`(case ,(car slot-vars) ; type
						   ,@(loop for config-type in '(configure-user-interface
										restrict-proprietary-items
										set-up-network-access
										declare-properties
										comment)
							   collect `(,config-type
								     ,(make-complex-type-predicate
								       `(named ,config-type)
								       slot-var
								       return-reason-p))))
						(make-complex-type-predicate
						 slot-type
						 slot-var
						 return-reason-p))
					   ,@(when context-of-type-failure
					       `((progn
						   (eval-push ',slot-name context-of-type-failure)
						   nil)))))
		      ,@(when minimum-contents
			  `(,(maybe-set-type-failure-reason
			      (if (and (consp minimum-contents)
				       (eq (car minimum-contents) 'and)
				       (every #'symbolp (cdr minimum-contents)))
				  `(cond ,@(loop for exp in (cdr minimum-contents)
						 collect (loop for (slot-name slot-type) in slots
							       for slot-present-p-var in slot-present-p-vars
							       when (eq slot-name exp)
								 return `((null ,slot-present-p-var)
									  ,@(when return-reason-p
									      `((setq last-slot-checked-of-type-failure ',slot-name)))
									  nil)
							       finally (return `((null ,exp) nil))))
					 (t t))
				  (substitute-names-for-predicates
				   minimum-contents ; symbol, (or ...)
				   (loop for (name type) in slots
					 for slot-present-p-var in slot-present-p-vars
					 collect (cons name slot-present-p-var))))
			      return-reason-p binding exp 'missing-required-structure-slots))))))))))
	  (otherwise
	   (maybe-set-type-failure-reason
	    `(type-specification-type-p ,binding ',exp)
	    return-reason-p binding exp 'type-mismatch))))))

(defun-for-macro parse-complex-type-specification
    (augmented-type-specification &optional return-reason-p)
  #-generate-category-type-predicates
  (declare (ignore return-reason-p))
  (values (get-complex-type-structure-table augmented-type-specification)
	  #+generate-category-type-predicates
	  (if return-reason-p
	      (let ((result (make-symbol "RESULT")))
		`(let ((,result ,(make-complex-type-predicate
				   augmented-type-specification
				   'evaluation-value
				   t)))
		   (unless ,return-reason-p
		     (when context-of-type-failure
		       (reclaim-eval-list context-of-type-failure)))
		   ,result))
	      (make-complex-type-predicate
	       augmented-type-specification
	       'evaluation-value
	       nil))))

(defun-for-macro parse-structure-spec (structure-spec)
  (gensym-dstruct-bind ((reference-name nil slots) structure-spec)
    (values
      ;; let-form
      (loop for (name type) in slots
	    collect `(,name nil))
      ;; name-setq-forms
      (loop for (name type) in slots
	    collect `(setq ,name (evaluation-structure-slot
				   ,reference-name ',name nil)))
      ;; structure-test-form
      `(or ,@(loop for (name type) in slots
		   collect `(and ,name
				 (not (type-specification-type-p ,name ',type))
				 (setf last-reason-for-complex-type-rejection
				       ,(format
					  nil
					  "structure attribute ~s has bad type"
					  name)))))
      ;; evaluation-value-converson-forms
      (loop for (name type) in slots
	    collect `(if (evaluation-value-p ,name)
			 (evaluation-value-value ,name)
			 ,name)))))

(defun-for-macro get-complex-type-specification-from-augmented (type)
  (if (atom type)
      type
      (cons (get-complex-type-specification-from-augmented
	      (car type))
	    (mapcar #'get-complex-type-specification-from-augmented
		    (if (eq (car type) 'structure)
			(cddr type)
			(cdr type))))))

(defun-for-macro get-augmented-type-specification-from-complex (type)
  (if (atom type)
      type
      (cons (get-augmented-type-specification-from-complex
	      (car type))
	    (let ((tail (mapcar #'get-augmented-type-specification-from-complex
				(cdr type))))
	      (if (eq (car type) 'structure)
		  (cons (gensym) tail)
		  tail)))))

(defun-for-macro get-simple-type-specification-from-complex (type)
  (if (atom type)
      type
      (case (car type)
	(sequence '(sequence))
	(structure '(structure))
	((and or not)
	 (cons (car type)
	       (mapcar #'get-simple-type-specification-from-complex
		       (cdr type))))
	((no-item unknown satisfies) type))))

(def-concept with-new-structure)

(def-concept with-structure)

;;; The for-macro function `expand-structure-pseudo-macros' implements the
;;; following pseudo-macros (a.k.a. local macros) for
;;; define-category-evaluator-interface.  In the doc below, note that the
;;; non-local macro with-evaluation-structure-slots has the effect of a
;;; symbol-macrolet thta converts evaluation-structure place forms to locals.
;;;
;;; with-structure
;;;     like with-evaluation-structure-slots but can use structure tags from
;;;     complex type specification to reduce verbosity in part->attribute
;;;     conversion
;;; with-new-structure
;;;     like with-structure but used in attribute-part mapping

(defun-for-macro expand-structure-pseudo-macros (exp structure-table)
  (if (atom exp)
      exp
      (case (car exp)
	(with-structure
	    (gensym-dstruct-bind (((var-name structure-name) . body) (cdr exp))
	      `(with-evaluation-structure-slots
		   (,var-name
		      ,(or (cdr (assq structure-name structure-table))
			   (error "unknown structure ~s" structure-name)))
		 ,@(expand-structure-pseudo-macros body structure-table))))
	(with-new-structure
	    (gensym-dstruct-bind (((structure-name) . body) (cdr exp))
	      (let ((new-structure (gensym)))
		`(let ((,new-structure (allocate-evaluation-structure nil)))
		   (with-evaluation-structure-slots
		       (,new-structure
			  ,(or (cdr (assq structure-name structure-table))
			       (error "unknown structure ~s" structure-name)))
		     ,@(expand-structure-pseudo-macros body structure-table))
		   ;;(format t "this is the new structure=~S~%" ,new-structure)
		   ,new-structure))))
	(t
	 (cons (expand-structure-pseudo-macros (car exp) structure-table)
	       (expand-structure-pseudo-macros (cdr exp) structure-table))))))


;;; `expand-predicate-for-complex-type' is an exported compile-time function
;;; that can be used in other functions and macros to expand an inline deep
;;; checking predicate for complex types.  The type predicate that this will generate
;;; is not a complete check in some cases where the frame-wide or global information
;;; is needed to say whether a part is acceptable.  This is more of a syntax and
;;; completeness check.  The bottom line for validation in G2 is still the
;;; combination of slot-value-compilers and slot-value-putters.

(defun-for-macro expand-predicate-for-complex-type (complex-type-specification)
  (parse-complex-type-specification complex-type-specification))



;;; `define-category-evaluator-interface' is, as it says, a means of defining
;;; equivalence between the evaluators component "parts" and the grammar categories
;;; that define i/o for the slots of the frame system.  Its purpose is to provide a
;;; informationally dense way of describing this interface.  There are various
;;; macros (available globally) and "pseudo-macros" (available only within the
;;; confines of the get and set forms of this macro) that will aid the user in
;;; creating a dense and readable mapping.  Please meta-shift-g to see some
;;; examples of this facility -- its use is simpler than its description.
;;;
;;; This macro is an extension to def-type-specification that also
;;; defines the means of mapping evaluation values (parts) to slot-values
;;; and vice versa.  See `g2-test-conclude-component' and `g2-test-get-component'
;;; for examples of code that uses the definitions made by this macro to
;;; actually get and conclude system-defined attributes without generating
;;; text or parsing.

;;; General information about the use of define-category-evaluator-interface
;;; (-pga, 5/7/96):

;;; The get and set forms are evaluated as if called with the following args:
;;;   Set form args: (evaluation-value frame slot-description)
;;;   Get form args: (slot-value frame slot-description)
;;; Of the arguments to the Set form, only the evaluation-value is required.
;;; Frame and slot-description are implicitly declared-ignored if not specified
;;; For the get form, no arguments are required, and all missing args will be
;;; implicitly declared ignore.

;;; Given a grammar-category, a choice of <category>-evaluation-setter and
;;; <category>-evaluation-getter is determined.

;;; The input to the setter is an evaluation-value which may come from a
;;; variety of sources, and must be thoroughly type-checked to make sure it
;;; is in the external-api format.  The automatic generation of a complex type
;;; predicate from a type specification will usually, but not always, produce
;;; adequate checking.  
;;;
;;; However, if there is a problem that the setter discovers, it should return
;;; as its first value the value of special variable bad-phrase, and,
;;; optionally, a second value, which should be a recyclable text string
;;; explaining the problem, in the style prescribed for slot value compilers
;;; (see def-slot-value-compiler).
;;;
;;; Once processed by the setter, the value must be a
;;; phrase-cons suitable for input to the slot-value-compiler for the same
;;; grammar category, and must be compatible or identical with the parser
;;; output obtained from parsing the text version of the same input value, if
;;; supported.
;;;
;;; The setter should not reclaim its argument value.  That is done by the
;;; calling mechanism.

;;; The input to the getter is assumed to be a valid slot-value, and
;;; therefore extensive type checking is not needed. The output will be an
;;; evaluation-value which is in the appropriate external api format, and
;;; which may be used directly by the setter.

(defmacro define-category-evaluator-interface (name-and-options
						augmented-type-specification
						&body body-spec)
  (clear-all-evaluator-slot-info)
  (destructuring-lambda-list (category-name &key
					    (access nil)
					    (simple-type-specification nil))
      (if (atom name-and-options) (list name-and-options) name-and-options)
    (let* ((set-function-name (build-ab-symbol category-name 'evaluation-setter))
	   (get-function-name (build-ab-symbol category-name 'evaluation-getter))
	   #+generate-category-type-predicates
	   (type-predicate-name (build-ab-symbol category-name
						 'category-type-predicate))
	   (getter (get-category-evaluator-interface-subform
		     body-spec 'get-form))
	   (getter-args (and getter (cadar getter)))
	   (setter (get-category-evaluator-interface-subform
		     body-spec 'set-form))
	   (setter-args (and setter (cadar setter)))
	   (complex-type-specification
	     (get-complex-type-specification-from-augmented
	       augmented-type-specification))
	   (return-reason-p (make-symbol "RETURN-REASON-P"))
	   (type-has-been-checked-p (gensym)))
      (unless (memq access '(read read-write))
	(error "Access must be read or read-write"))
      (when (and (eq access 'read) setter)
	(error "Cannot define a setter for category with read acesss"))
      (multiple-value-bind (structure-table check-form)
	  (parse-complex-type-specification augmented-type-specification 
					    return-reason-p)
	#-generate-category-type-predicates
	(declare (ignore check-form))
	`(progn
	   #+generate-category-type-predicates
	   (defun ,type-predicate-name (evaluation-value &optional ,return-reason-p)
	     ,check-form)
	   (def-type-specification ,category-name
	       ,(or simple-type-specification
		    (get-simple-type-specification-from-complex
		      complex-type-specification))
	     ,complex-type-specification)
	   ,@(when (eq access 'read-write)
	       `((defun-into-place
		     (,set-function-name
			(evaluation-value-to-category-function ',category-name))
		     (,(car setter-args)
		       ,(or (cadr setter-args) 'frame)
		       ,(or (caddr setter-args) 'slot-description)
		       ,type-has-been-checked-p)
		   ,@(cond ((null (cdr setter-args))
			    `((declare (ignore frame slot-description))))
			   ((null (cddr setter-args))
			    `((declare (ignore slot-description)))))
		   (unless ,type-has-been-checked-p
		     (let ((value-at-type-failure nil)
			   (type-at-type-failure nil)
			   (reason-for-type-failure nil)
			   (context-of-type-failure nil)
			   (last-slot-checked-of-type-failure nil))
		       (unless (progn
				 #+generate-category-type-predicates
				 (,type-predicate-name ,(car setter-args) t)
				 #-generate-category-type-predicates
				 (type-specification-type-p--with-explanation
				  ,(car setter-args) '(named ,category-name)))
			 (return-from ,set-function-name
			   (values
			     bad-phrase
			     (type-error-in-setter
			       ,(car setter-args)
			       ',complex-type-specification
			       value-at-type-failure type-at-type-failure
			       reason-for-type-failure context-of-type-failure
			       last-slot-checked-of-type-failure))))))
		   ,(expand-structure-pseudo-macros
		      (cadr setter)
		      structure-table))))
	   (defun-simple-into-place
	       (,get-function-name
		  (slot-value-to-evaluation-value-function ',category-name))
	       (,(or (car getter-args) 'slot-value)
		 ,(or (cadr getter-args) 'frame)
		 ,(or (caddr getter-args) 'slot-description))
	     ,@(cond ((null (car getter-args))
		      `((declare (ignorable slot-value frame slot-description))))
		     ((null (cdr getter-args))
		      `((declare (ignorable frame slot-description))))
		     ((null (cddr getter-args))
		      `((declare (ignorable slot-description)))))
	     ,(expand-structure-pseudo-macros
		(cadr getter)
		structure-table))
	   )))))

(defun make-simplified-type (type)
  (if (consp type)
      (case (car type)
	(sequence (eval-list 'sequence))
	(structure (eval-list 'structure))
	((and or not) (eval-cons (car type)
				 (loop for type1 in (cdr type)
				       collect (make-simplified-type type1)
					 using eval-cons)))
	(t (copy-tree-using-eval-conses type)))
      type))

(defun type-error-in-setter (value type sub-value sub-type reason context last-slot-checked)
  (let* ((type-string
	  (tformat-text-string "the type ~NT" type))
	 (print-type-p
	   (< (lengthw type-string) 800)))
    (prog1 (twith-output-to-text-string
	     (if (framep value)
		 (tformat "the ~(~A ~NF~)" (class-function value) value)
		 (tformat "the value ~(~NV~)" value))
	     (if print-type-p
		 (tformat "~%is not of ~A" type-string)
		 (tformat "~%is not of the correct type"))
	     (when reason
	       (case reason
		 (sequence-too-short
		  (tformat ",~%because a sequence was too short"))
		 (sequence-too-long
		  (tformat ",~%because a sequence was too long"))
		 (missing-required-structure-slots
		  (cond ((null last-slot-checked)
			 (tformat ",~%because at least one required structure slot was missing"))
			((consp last-slot-checked)
			 (if (and (cadr last-slot-checked) (null (cddr last-slot-checked)))
			     (tformat ",~%because a structure contained neither the slot ~(~a~) nor the slot ~(~a~)"
				      (car last-slot-checked) (cadr last-slot-checked))
			     (tformat ",~%because a structure contained none of the following slots: ~(~L,|~)"
				      last-slot-checked)))
			(t
			 (tformat ",~%because the required structure slot ~(~a~) was missing" last-slot-checked))))
		 (unknown-extra-structure-slot
		  (let ((allowed-slots (loop for (name) in (second sub-type)
					     collect name using eval-cons)))
		    (prog1 (tformat ",~%because the structure slot ~(~a~) was not allowed, ~
                                     because it was not one of ~(~L,|~)" last-slot-checked allowed-slots)
		      (reclaim-eval-list allowed-slots))))
		 (invalid-operation-type
		  (if (eq last-slot-checked structure-slot-not-bound)
		      (tformat ",~%because the required structure slot operation-type was not present")
		      (tformat ",~%because the operation-type slot had an illegal value")))
		 (neither-uan-nor-sad-present
		  (tformat ",~%because neither the structure slot user-attribute-name ~
                            nor the structure system-attribute-designation was present"))
		 (simple-type-mismatch
		  (unless (equal sub-type type)
		    (let ((simplified-type
			   (make-simplified-type sub-type)))
		      (tformat ",~%because ~(~NA~)~%was not of type ~NT" sub-value simplified-type)
		      (reclaim-eval-tree simplified-type))))
		 (structure-choose-type-mismatch
		  (tformat ",~%because ~(~NA~)~%was not of type ~NT" sub-value sub-type)
		  (reclaim-eval-tree sub-type))
		 (type-mismatch
		  (unless (equal sub-type type)
		    (tformat ",~%because ~(~NA~)~%was not of type ~NT" sub-value sub-type)))))
	     (when context
	       (tformat "~%The problem occurred ")
	       (loop for firstp = t then nil
		     for subtype = type then next-subtype
		     for expanded-subtype = (expand-named-type subtype)
		     for expanded-subtype1 = (if (and (consp expanded-subtype)
						      (eq (car expanded-subtype) 'or))
						 (loop for stype in (cdr expanded-subtype)
						       for stype1 = (expand-named-type stype)
						       when (and (consp stype1)
								 (memq (car stype1) '(sequence structure)))
							 return stype1)
						 expanded-subtype)
		     for name in context
		     for next-subtype = (case (if (consp expanded-subtype1)
						  (car expanded-subtype1)
						  expanded-subtype1)
					  (sequence (if (fixnump name)
							(cadr expanded-subtype1)
							nil))
					  (structure (if (fixnump name)
							 nil
							 (cadr (assq name (cadr expanded-subtype1)))))
					  (t nil))
		     do (unless firstp (tformat ", "))
			(if (fixnump name)
			    (tformat "inside element ~D" name)
			    (tformat "inside ~(~a~)" name))
		     finally (when (and expanded-subtype
					(not print-type-p))
			       (case reason
				 (missing-required-structure-slots
				  (unless (consp last-slot-checked)
				    (let ((minimum-contents?
					    (structure-type-specification-minimum-contents expanded-subtype)))
				      (when minimum-contents?
					(twrite-string ", where ")
					(twrite-minimum-structure-contents minimum-contents? t)
					(twrite-string " must be present"))))))))))
      (reclaim-text-string type-string)
      (reclaim-eval-list context))))

(defmacro call-category-setter-fn (fn &rest args)
  `(funcall-simple-multi-valued-compiled-function
     (compiled-function-in-place ,fn)
     ,@args))

(defmacro call-category-setter (category-name &rest args)
  (let ((function (make-symbol "FUNCTION")))
    ;; evaluation-value-to-category-function could return NIL
    `(let ((,function (evaluation-value-to-category-function ,category-name)))
       (when ,function
	 (call-category-setter-fn ,function ,@args)))))

(defmacro call-category-getter-fn (fn &rest args)
  `(funcall-simple-compiled-function
     (compiled-function-in-place ,fn)
     ,@args))

(defmacro call-category-getter (category-name &rest args)
  (let ((function (make-symbol "FUNCTION")))
    ;; slot-value-to-evaluation-value-function could return NIL
    `(let ((,function (slot-value-to-evaluation-value-function ,category-name)))
       (when ,function
	 (call-category-getter-fn ,function ,@args)))))

(defun-for-macro get-category-evaluator-interface-subform (body-spec key)
  (loop for form in body-spec
	when (eq (caar form) key)
	  return form))


;;; Helper Macros for define-category-evaluator-interface:
;;; 1. evaluation-etypecase
;;;     provides type-specification parallel to CLtL's typecase macro
;;; 2. with-evaluation-sequence-to-phrase-list-mapping
;;;     provides sequence to phrase list mapping for part->parse-result conversion.
;;; 3. with-list-to-evaluation-sequence-mapping
;;;     provides (lisp) list to sequence mapping for attribute->part conversion
;;; 4. with-evaluation-structure-slots
;;;     symbol-macrolet's evaluation-structure place forms to locals
;;; pseudo-macros
;;; 5 with-structure
;;;     like with-evaluation-structure-slots but can use structure tags
;;;     from complex type specification to reduce verbosity in part->attribute conversion
;;; 6 with-new-structure
;;;     like with-structure but used in attribute-part mapping



(defmacro evaluation-etypecase (selector-exp &body clauses)
  (let ((selector (gensym)))
    `(let ((,selector ,selector-exp))
       (cond
	 ,@(loop for (type . actions) in clauses
		 collect
		 `((type-specification-type-p ,selector ',type)
		   ,@actions))
	 (t
	  (let ((type-string
		  (twith-output-to-text-string
		    ,@(loop for (type . nil) in clauses
			    collect
			    `(tformat "~NT " ',type)))))
	    (values bad-phrase
		    (tformat-text-string
		      "~NV must be one of the following types: ~a"
		      ,selector type-string))))))))

(defmacro evaluation-quantity-to-phrase-quantity (x)
  `(let ((value (evaluation-value-value ,x)))
     (cond ((fixnump value)
	    value)
	   ((gensym-long-p value)
	    (make-phrase-long value))
	   (t
	    (make-phrase-float value)))))

(defmacro slot-value-number-to-evaluation-quantity (x)
  (avoiding-variable-capture (x)
    `(cond ((fixnump ,x) ,x)
	   ((gensym-long-p ,x)
	    (with-temporary-creation
		slot-value-number-to-evaluation-quantity
	      (make-evaluation-long (managed-long-value ,x))))
	   (t
	    (with-temporary-gensym-float-creation
		slot-value-number-to-evaluation-quantity
	      (make-evaluation-float (managed-float-value ,x)))))))

(defmacro with-evaluation-sequence-to-phrase-list-mapping
    ((evaluation-sequence iteration-variable) &body body)
  `(loop for ,iteration-variable
	     being each evaluation-sequence-element of ,evaluation-sequence
	 collect
	 (progn ,@body)
	   using phrase-cons))

(defmacro with-list-to-evaluation-sequence-mapping
    ((list-source-exp iteration-variable) &body body)
  (let ((eval-list (gensym)))
    `(loop for ,iteration-variable in ,list-source-exp
	   collect (progn ,@body)
	     into ,eval-list
	     using eval-cons
	   finally
	     (return (allocate-evaluation-sequence ,eval-list)))))

(defmacro with-managed-array-to-evaluation-sequence-mapping
    ((source-exp iteration-variable) &body body)
  (let ((eval-list (gensym)))
    `(loop for ,iteration-variable in ,source-exp
	   collect (progn ,@body)
	     into ,eval-list
	     using eval-cons
	   finally
	     (return (allocate-evaluation-sequence ,eval-list)))))

;;; NOTE: `special-variable-used-as-symbol-macrolets' is a static list used only by macro
;;; `with-evaluation-structure-slots' for expand macros. It replaced the problematic
;;; usage of CLTL2 `variable-information' introduced in GENSYMCID-944.
;;;
;;; In the future, if there're more slot symbols used in `define-category-evaluator-interface'
;;; with conflicts on special symbols (by DEFVARs), they can be added into this list.
;;; -- Chun Tian (binghe), 2013/4/22

(eval-when (:compile-toplevel :load-toplevel :execute)
  #-chestnut-trans
  (defvar special-variable-used-as-symbol-macrolets
    '(warning-message-level	; DEBUG
      tracing-message-level
      breakpoint-level
      source-stepping-level
      grid-color		; CHARTS1
      grid-visible
      axis-minimum
      axis-maximum
      axis-crossover
      number-of-significant-digits
      part-index)))

(defmacro with-evaluation-structure-slots ((structure-exp slot-list) &body body)
  (let ((structure (gensym)))
    `(let ((,structure ,structure-exp))
       (symbol-macrolet
	 ,(loop for slot-name in slot-list
		if (memq slot-name special-variable-used-as-symbol-macrolets)
		;; NOTE: if the slot-name is also a global variable (declared as special),
		;; then using SYMBOL-MACROLET will cause a fetal error because ANSI CL do
		;; not allow such usage any more. To solve this problem, we use alternative
		;; names with a %-prefix.  -- Chun Tian (binghe), 2013/3/25
		collect
		  `(,(intern (format nil "%~A" (symbol-name slot-name)))
		    (evaluation-structure-slot ,structure ',slot-name))
		#+development and #+development do
		#+development
		(warn "the slot name ~A is also a global variable, use %~A instead."
		      slot-name slot-name)
		else collect
		  `(,slot-name (evaluation-structure-slot ,structure ',slot-name)))
	 ,@body))))

;;; `setf-non-nil' is, probably misguided, verbosity reduction macro-crappola.
;;; It also evaluates is sub-forms out of order.  The devil made me do it.

(defmacro setf-non-nil (place value-exp)
  `(let ((value ,value-exp))
     (when value
       (setf ,place value))))


(defmacro with-unleashed-and-verified-structure-args (structure-spec &body body-spec)
  (let ((arg-test-results (gensym)))
    (gensym-dstruct-bind ((reference-name no-item-ok? nil) structure-spec)
      (multiple-value-bind (let-form setq-forms structure-test-form evaluation-value-converson-forms)
	  (parse-structure-spec structure-spec)
	`(let* (,@let-form ,arg-test-results)
	   (cond ((type-specification-type-p ,reference-name '(structure))
		  (progn ,@setq-forms)
		  (setq ,arg-test-results ,structure-test-form)
		  (when ,arg-test-results
		    (stack-error cached-top-of-stack "arg ~a is not of the appropriate type "
				 ,arg-test-results))
		  (progn
		    ,@evaluation-value-converson-forms))
		 ((or
		    (null ,no-item-ok?)
		    (not (type-specification-type-p ,reference-name '(no-item))))
		  (stack-error cached-top-of-stack "arg ~a is not of the appropriate type "
			       ,reference-name)))
	   ,@body-spec)))))

(defmacro with-unleashed-and-verified-structure-args-no-stack-errors
    (structure-spec &body body-spec)
  (let ((arg-test-results (gensym)))
    (gensym-dstruct-bind ((reference-name no-item-ok? nil) structure-spec)
      (multiple-value-bind (let-form setq-forms structure-test-form evaluation-value-converson-forms)
	  (parse-structure-spec structure-spec)
	`(let* (,@let-form ,arg-test-results)
	   (cond ((type-specification-type-p ,reference-name '(structure))
		  (progn ,@setq-forms)
		  (setq ,arg-test-results ,structure-test-form)
		  (when ,arg-test-results
		    (error "Cannot continue. arg ~a is not of the appropriate type "
				 ,arg-test-results))
		  (progn
		    ,@evaluation-value-converson-forms))
		 ((or
		    (null ,no-item-ok?)
		    (not (type-specification-type-p ,reference-name '(no-item))))
		  (error "Cannot continue. arg ~a is not of the appropriate type "
			       ,reference-name)))
	   ,@body-spec)))))


;;; `with-safe-category-setter-calling' is a context that must be
;;; wrapped around all calls to `call-category-setter-safely'.
;;; The combination of these two macros allows you to call category
;;; setters inside the setter of a define-category-evaluator-interface
;;; definition, and not have to worry about binding and returning
;;; a possible bad-phrase.

(defmacro with-safe-category-setter-calling (&body body)
  `(block safe-category-setter-calling-block ,@body))

(defmacro call-category-setter-safely
    (category ev &optional frame-var slot-description-var arg3)
  `(multiple-value-bind
       (parse-result-or-bad-phrase error-string?)
       (call-category-setter ,category ,ev ,frame-var ,slot-description-var ,arg3)
     (cond ((eq parse-result-or-bad-phrase bad-phrase)
	    (return-from safe-category-setter-calling-block
	      (values bad-phrase error-string?)))
	   (t
	    parse-result-or-bad-phrase))))

(defmacro safe-category-setter-error (control-string &body args)
  `(return-from safe-category-setter-calling-block
     (values bad-phrase
	     (tformat-text-string ,control-string ,@args))))

(def-global-property-name category-committer-function t)
(def-global-property-name category-extracter-function t)

(defmacro define-category-slot-access (category-name
					&body body-spec)
  (clear-all-evaluator-slot-info)
  (let* ((commit-function-name (build-ab-symbol category-name 'evaluation-committer))
	 (extract-function-name (build-ab-symbol category-name 'evaluation-extracter))
	 (committer (get-category-evaluator-interface-subform
		      body-spec 'commit-form))
	 (committer-args (and committer (cadar committer)))
	 (extracter (get-category-evaluator-interface-subform
		      body-spec 'extract-form))
	 (extracter-args (and extracter (cadar extracter))))
    `(progn
       ,@(when committer
	   `(,(if (and committer-args (symbolp committer-args))
		  `(setf (category-committer-function ',category-name)
			 (#+development quote #-development function
					,committer-args))
		  `(defun-simple-into-place
		       (,commit-function-name
			  (category-committer-function ',category-name))
		       (,(car committer-args)
			 ,(or (cadr committer-args) 'evaluation-value)
			 ,(or (caddr committer-args) 'evaluator-info))
		     ,@(cond ((null (cdr committer-args))
			      `((declare (ignorable evaluation-value evaluator-info))))
			     ((null (cddr committer-args))
			      `((declare (ignorable evaluator-info)))))
		     ,@(cdr committer)))))
       ,@(when extracter
	   `(,(if (and extracter-args (symbolp extracter-args))
		  `(setf (category-extracter-function ',category-name)
			 (#+development quote #-development function
					,extracter-args))
		  `(defun-simple-into-place
		       (,extract-function-name
			  (category-extracter-function ',category-name))
		       (,(car extracter-args)
			 ,(or (cadr extracter-args) 'evaluator-info))
		     ,@(cond ((null (cdr extracter-args))
			      `((declare (ignorable evaluator-info)))))
		     ,@(cdr extracter)))))
       )))

(def-global-property-name text-category-evaluator-interface-p t)

(defun note-text-category-evaluator-interface (category)
  (setf (text-category-evaluator-interface-p category) t))

(defmacro define-text-category-evaluator-interface (category &optional
							     prohibit-no-item
							     read-only-p)
							     
  `(progn
     (note-text-category-evaluator-interface ',category)
     (define-category-evaluator-interface (,category
					     :access
					     ,(if read-only-p 'read 'read-write))
	 ,(if prohibit-no-item 'text '(or text (no-item)))
       ((get-form (text?))
	(if text?
	    (convert-text-to-text-string text?)
	    ,(if prohibit-no-item
		 `(copy-constant-wide-string #w"")
		 `nil)))
       ,@(if read-only-p
	     nil
	     `(((set-form (evaluation-value frame))
		,(if (eq category 'free)
		     nil
		   `(parse-text-string
		      (or evaluation-value #w"")
		      ',category frame))))))

     (define-category-slot-access ,category
       ((extract-form text-category-slot-access-extracter))
       ((commit-form text-category-slot-access-committer)))))

(defmacro define-textof-category-evaluator-interface (category &optional
							     prohibit-no-item
							     read-only-p)
							     
  `(progn
     (note-text-category-evaluator-interface ',category)
     (define-category-evaluator-interface (,category
					     :access
					     ,(if read-only-p 'read 'read-write))
	 ,(if prohibit-no-item 'text '(or text (no-item)))
       ((get-form (slot-value))
	(twith-output-to-text-string
	  (write-slot-value ',category slot-value frame)))
       ,@(if read-only-p
	     nil
	     `(((set-form (evaluation-value frame))
		(parse-text-string
		  (or evaluation-value #w"")
		  ',category frame)))))))


;;; The function `check-type-and-return-error-string' returns NIL if
;;; evaluation-value value has given type. Otherwise, it returns a newly consed
;;; string describing the problem.

(defun check-type-and-return-error-string (value type)
  (assert-for-development (valid-type-specification-p type))
  (unless (type-specification-type-p value type)
    ;; Code extracted from define-category-evaluator-interface
    (let* ((value-at-type-failure nil)
	   (type-at-type-failure nil)
	   (reason-for-type-failure nil)
	   (context-of-type-failure nil)
	   (last-slot-checked-of-type-failure nil))
      (type-specification-type-p--with-explanation value type)
      (type-error-in-setter
	value type
	value-at-type-failure type-at-type-failure reason-for-type-failure
	context-of-type-failure last-slot-checked-of-type-failure))))


#+development
(defvar *maximum-elements-of-sequence-to-describe* 100)

#+development
(defvar *case-for-printing-sequences-and-structures* :upcase)

#+development
(defvar dereference-references-when-printing-p t)

#+development
(def-development-printer print-evaluation-sequence
    (sequence &optional (stream *standard-output*))
  (when (evaluation-sequence-p sequence)
    (let* ((sequence-array (evaluation-sequence-value sequence))
	   (sequence-length (-f (managed-array-length sequence-array)
				(evaluation-sequence-first-element-index))))
      (printing-random-object (sequence stream)
	(format stream "Sequence ~d [~d]"
		sequence-length
		(aggregate-evaluation-value-reference-count sequence))))
    sequence))

#+development
(def-development-describer describe-evaluation-sequence (sequence)
  (when (evaluation-sequence-p sequence)
    (let* ((sequence-array (evaluation-sequence-value sequence))
	   (array-length (managed-array-length sequence-array))
	   (sequence-length (-f array-length
				(evaluation-sequence-first-element-index)))
	   (print-whole-sequence-p
	     (<=f array-length *maximum-elements-of-sequence-to-describe*))
	   (max-index-to-iterate
	     (if print-whole-sequence-p
		 (1-f array-length)
		 *maximum-elements-of-sequence-to-describe*))
	   (*print-case* *case-for-printing-sequences-and-structures*))
      (format t "~s is a Sequence.  It has ~s elements:~%"
	      sequence sequence-length)
      (format t "{")
      (loop for i from (evaluation-sequence-first-element-index)
		  to max-index-to-iterate
	    as firstp = t then nil
	    as value = (managed-svref sequence-array i)
	    as deref-value = (if dereference-references-when-printing-p
				 (get-item-if-item-reference value)
				 value)
	    do
	(unless firstp (format t ", "))
	(format t "~s" deref-value))
      (unless print-whole-sequence-p
	(format t ", ..."))
      (format t "}~%"))
    sequence))

#+development
(def-development-printer print-evaluation-structure (structure &optional (stream *standard-output*))
  (when (evaluation-structure-p structure)
    (let* ((structure-array (evaluation-structure-value structure))
	   (structure-length (-f (managed-array-length structure-array)
				(estructure-first-attribute-index))))
      (printing-random-object (structure stream)
	(format stream "Structure ~d [~d]"
		(/ structure-length 2)
		(aggregate-evaluation-value-reference-count structure))))
    structure))

#+development
(def-development-describer describe-evaluation-structure (structure)
  (when (evaluation-structure-p structure)
    (let* ((structure-array (evaluation-structure-value structure))
	   (array-length (managed-array-length structure-array))
	   (structure-length (-f array-length
				(estructure-first-attribute-index)))
	   (*print-case* *case-for-printing-sequences-and-structures*))
      (format t "~s is a Structure.  It has ~s elements:~%"
	      structure (/ structure-length 2))
      (loop for array-index from (estructure-first-attribute-index) below array-length by 2
	    as key = (managed-svref structure-array array-index)
	    as value = (managed-svref structure-array (1+f array-index))
	    as deref-value = (if dereference-references-when-printing-p
				 (get-item-if-item-reference value)
				 value)
	    as structure-index from 0 do
	(format t " [~d] ~35,,,'.a.. ~s~%" structure-index key deref-value)))
    structure))

#+development
(def-development-describer describe-evaluation-item-reference (item-reference)
  (when (evaluation-item-reference-p item-reference)
    (format t "~s is a ~s~%" item-reference (type-of item-reference))
    (let ((i 0))
      (macrolet ((evaluation-item-reference-uuid-block (i)
		   `(evaluation-item-reference-vector-uuid-block
		      (evaluation-item-reference-value ,i)))
		 (S (slot) `(describe-slot-in-frame-or-structure
			      (incf i) nil ',slot (,slot item-reference))))
	(s evaluation-item-reference-reference-count)
	(s evaluation-item-reference-uuid-block)
	(s evaluation-item-reference-referenced-item)
	item-reference))))

;;;; Simple Type Checking


;;; The function `check-type-error-message' returns an explanatory string if
;;; given evaluation value is not of given type. If allow-other-keys is true,
;;; then extra keys in structure values are permitted.

(defun check-type-error-message (value type &optional allow-other-keys)
  ;; Calling type-specification-type-p is an optimization, but it does not
  ;; support allow-other-keys.
  (let ((maximum-number-of-slots-in-structure-type 50))
    (when (or allow-other-keys
	      (not (type-specification-type-p value type)))
      (explanation-for-type-error? value type allow-other-keys))))


;;; The function `explanation-for-type-error?' returns a newly consed string
;;; explaining the problem if the given evaluation value does not have the given
;;; type, or NIL if it does. If allow-other-keys is true, then extra keys in
;;; structure values are permitted.

(defun explanation-for-type-error? (value type &optional allow-other-keys)
  (assert-for-development (valid-type-specification-p type))
  (let* ((structure-specs-allow-unknown-slots-p allow-other-keys)
	 (value-at-type-failure nil)
	 (type-at-type-failure nil)
	 (reason-for-type-failure nil)
	 (context-of-type-failure nil)
	 (last-slot-checked-of-type-failure nil))
    (unless (type-specification-type-p--with-explanation value type)
      (type-error-in-setter
	value type
	value-at-type-failure type-at-type-failure reason-for-type-failure
	context-of-type-failure last-slot-checked-of-type-failure))))


;;; The macro `def-type-parameter' exists only so that we can check the type
;;; specification for validity at compile time.

(defmacro def-type-parameter (name type)
  (unless (let ((maximum-number-of-slots-in-structure-type 50))
	    (valid-type-specification-p type))
    (warn "Invalid type specification ~A: ~S" name type))
  `(eval-when (:compile-toplevel :load-toplevel :execute)
     (defparameter ,name ',type)))


;;;; Canonical Unboxing of Evaluation Values


;;; The function `unbox-evaluation-value' creates a gensym-tree of strings,
;;; integers, symbols, managed-floats, and items from an evaluation value
;;; consisting of structures, sequences, texts, integers, floats, symbols,
;;; items, or truth-values. Everything in the result is newly consed.

;;; As a random feature, optionally ignore some structure slots, at top-level.

(defun unbox-evaluation-value (ev &optional keys-to-omit)
  (with-temporary-gensym-float-creation unbox-evaluation-value
    (unbox-evaluation-value-1 ev keys-to-omit)))

(defun unbox-evaluation-value-1 (ev keys-to-omit)
  (cond ((evaluation-sequence-p ev)
	 (loop for element being each evaluation-sequence-element of ev
	       collect (unbox-evaluation-value-1 element nil) using gensym-cons))
	((evaluation-structure-p ev)
	 (loop for (slot . value) being each evaluation-structure-pair of ev
	       unless (memq slot keys-to-omit)
		 collect slot using gensym-cons and
		 collect (unbox-evaluation-value-1 value nil) using gensym-cons))
	((evaluation-float-p ev)
	 (allocate-managed-float (evaluation-float-value ev)))
	((evaluation-long-p ev)
	 (allocate-managed-long (evaluation-long-value ev)))
	((evaluation-text-p ev)
	 (copy-text-string (evaluation-text-value ev)))
	((evaluation-integer-p ev)
	 (evaluation-integer-value ev))
	((evaluation-symbol-p ev)
	 (evaluation-symbol-symbol ev))
	((evaluation-truth-value-p ev)
	 (if (evaluation-truth-value-is-true-p ev) t nil))
; May want this later.
;	((evaluation-item-reference-p ev)
;	 (get-item-if-item-reference ev))
	((framep ev)			; Already an item (?)
	 ev)
	((null ev)			; "no-item"
	 nil)
	(t
	 (dwarn "Unrecognized evaluation-value in unbox-evaluation-value-1: ~s" ev))))

;;; The function `reclaim-unboxed-evaluation-value' reclaims something
;;; created by the above function.

(def-tree-reclaimer reclaim-unboxed-evaluation-value (list) :cons-pool gensym)	 

;;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module ATTR-EXPORT

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Jim Allard, Phill Apley


;; To do

;; Need to automatically compute the list-of-user-overridable-system-slots, not
;; leave it as a constant in the code.  -jra 4/17/96

;; Need to do the same with `Runtime-changeable-default-value-lookup-slots' -pga, 4/22/96



;; In commands0:
(declare-forward-reference might-be-writable-slot-p function)
(declare-forward-reference transient-or-permanent-p function)
(declare-forward-reference exclude-from-wildcard-denotation-p function)


;;;; Exporting Attributes for KB Developers


;;; Supporting macros and functions for three G2 functions, which are
;;; actually defined in stack-eval2.lisp:
;;;     attribute-descriptions-of-class (class, symbol) = (sequence)
;;;     attribute-descriptions-of-item (item, symbol) = (sequence)
;;;     attribute-values-of-item (item, symbol) = (structure)

(defvar current-attribute-description-class nil)

(defun-simple defining-class-of-slot (slot-description-or-virtual-attribute)
    (let ((class-specification-for-virtual-attribute
	      (and (virtual-attribute-p slot-description-or-virtual-attribute)
		   (virtual-attribute-arg-type slot-description-or-virtual-attribute))))
       (cond ((slot-description-p slot-description-or-virtual-attribute)
	      (defining-class slot-description-or-virtual-attribute))
	     ((class-type-specification-p class-specification-for-virtual-attribute)
	      (type-specification-class class-specification-for-virtual-attribute))
	     (t
	      (or (virtual-attribute-defined-for-class?
		    slot-description-or-virtual-attribute current-attribute-description-class)
		  #+development
		  (cerror
		    "go on"
		    "Why are we here? Violating assumption. See vkp"))))))
	      

(defun-simple defining-class-of-slot-for-user (slot-description-or-virtual-attribute)
  ;; This differs from defining-class-of-slot because we can't expose internal
  ;; classes to the users.  So we show 'em the next best thing.
  (let ((actual-class
	  (defining-class-of-slot slot-description-or-virtual-attribute)))
    ;; A bit of a hack.  We can do something more subtle later... 
    (if (memq actual-class '(ENTITY BLOCK KB-FRAME PROTO-BLOCK SYSTEM-ITEM ROOT))
	'item
	actual-class)))


(defun-simple sort-pairs-according-to-defining-class (class-name slot-desc-alist)
  ;; The list ends up with the least-specific attributes at the beginning
  ;; of the list, and the most-specific attributes at the end. This now takes
  ;; a symbol, naming the class we are sorting the attributes for, required to
  ;; do the right thing for non-local virtual attributes.
  (let ((current-attribute-description-class class-name))
    (sort-list slot-desc-alist 'superior-class-p 'defining-class-of-attr-pair)))


(defun-simple superior-class-p (symbol class)
  (not (subclassp symbol class)))


(defun-simple defining-class-of-attr-pair (slot-desc-dotted-pair)
  (defining-class-of-slot (cdr-of-cons slot-desc-dotted-pair)))



;;; `applicable-and-not-deprecated-virtual-attribute-p' - returns t if the
;;; virtual attribute whose structure is given is valid for the class whose
;;; symbol is given or one of its superclasses, and it is not marked as
;;; deprecated on the most specific class for which it is defined.  This
;;; function will only work properly with class-type-specifications or
;;; union-type-specifications which contain only class-type-specifications.
;;; It will not work properly for symbolic-types, member-type-specifications,
;;; intersection-type-specifications, etc.  At this time, the only virtual
;;; attributes defined are defined with acceptable type specifications for 
;;; this function to work.  If someone defines a virtual attribute on a
;;; funkier type-specification, this function may need to be adjusted.

(defun-simple applicable-and-not-deprecated-virtual-attribute-p
    (class-description attribute-structure include-deprecated-p)
  (let ((inheritance-path (class-inheritance-path class-description))
	(arg-spec (virtual-attribute-arg-type attribute-structure))
	(features (virtual-attribute-features attribute-structure)))
    (and (consp arg-spec)   ;; no longer using type-specification-subtype-in-kb-p
	 (loop for class-or-superclass in inheritance-path
	       when (and (not include-deprecated-p)
			 (class-is-specifically-deprecated-in-features-p
			   class-or-superclass features))
		 return nil  ;; attribute is deprecated on most specific class
	       when (if (eq 'or (car-of-cons arg-spec))
			(loop for valid-class in (cdr arg-spec)
			      thereis (and (consp valid-class)
					   (eq 'class (car-of-cons valid-class))
					   (eq class-or-superclass
					       (cadr valid-class))))
			(and (eq (car-of-cons arg-spec) 'class)
			     (eq (cadr arg-spec) class-or-superclass)))
		 return t    ;; attribute is defined (and not deprecated) on
                             ;; most specific class				
	       finally  ;; attribute is not defined on any class in the hierarchy
		 (return nil)))))


;;; `get-list-of-all-user-visible-attributes' returns a sorted alist of
;;; user-visible slot descriptions and virtual attributes, keyed by the
;;; attribute names that the user will see -- possibly the aliased slot
;;; name of a system-defined attribute, or the class-qualified name of a
;;; user-defined attribute.
;;;
;;; "Frame" can be nil, for callers such as "attribute-description-of-class",
;;; but if it isn't, this function assumes it is of the class described
;;; by "class-description". 

(defun-simple get-list-of-all-user-visible-attributes-specifying-deprecation
    (class-description include-deprecated-virtual-attributes-p)
  (let* ((class-name (class-name-of-class-description class-description))
	 (virtual-attr-list
	   ;; Potential bug:  users can define attributes with the same
	   ;; name as virtual attributes.  We can't check for that yet.
	   (loop with virtual-attributes = (all-virtual-attributes-for-class
					     class-description
					     include-deprecated-virtual-attributes-p)
		 for attr-name in virtual-attributes
		 collect (eval-cons attr-name (virtual-attribute attr-name))
		   using eval-cons
		 finally (reclaim-eval-list virtual-attributes)))
	 (slot-desc-list
	   (loop for slot-description in (slot-descriptions class-description)
		 for defining-class-name = (defining-class slot-description)
		 for aliased-slot-name = (if (slot-name-needs-qualification-p
					       slot-description
					       class-description)
					     (unique-slot-name slot-description)
					     (alias-slot-name-if-necessary
					       (pretty-slot-name slot-description)
					       defining-class-name))
		 if (and (user-visible-slot-p slot-description)
			 (not (assq aliased-slot-name virtual-attr-list))
			 (or include-deprecated-virtual-attributes-p
			     (not (feature-assq-macro
				    'previously-put-in-attribute-tables
				    (slot-features slot-description)))))
		   collect (eval-cons aliased-slot-name slot-description)
		     using eval-cons))
	 (virtual-attr-list-non-local
	   (when virtual-attributes-not-local-to-a-class
	     (loop with list = (all-non-local-virtual-attributes-for-class
				 class-description
				 include-deprecated-virtual-attributes-p)
		   for name in list
		   collect (eval-cons name (virtual-attribute name))
		     using eval-cons
		   finally (reclaim-eval-list list)))))
    (sort-pairs-according-to-defining-class
      class-name
      (nconc slot-desc-list
	     virtual-attr-list
	     virtual-attr-list-non-local))))

;; Added by SoftServe for Gensym-381
(defun-simple get-list-of-all-user-visible-attributes-for-pane
    (class-description include-deprecated-virtual-attributes-p)
  (let* ((virtual-attr-list
	   ;; Potential bug:  users can define attributes with the same
	   ;; name as virtual attributes.  We can't check for that yet.
	   (loop with virtual-attributes = (all-virtual-attributes-for-class
					     class-description
					     include-deprecated-virtual-attributes-p)
		 for attr-name in virtual-attributes
		 collect (eval-cons attr-name (virtual-attribute attr-name))
		   using eval-cons
		 finally (reclaim-eval-list virtual-attributes)))
	 (slot-desc-list
	   (loop for slot-description in (slot-descriptions class-description)
		 for defining-class-name = (defining-class slot-description)
		 for aliased-slot-name = (if (slot-name-needs-qualification-p
					       slot-description
					       class-description)
					     (unique-slot-name slot-description)
					     (alias-slot-name-if-necessary
					       (pretty-slot-name slot-description)
					       defining-class-name))
		 if (and (user-visible-slot-p slot-description)
			 (not (assq aliased-slot-name virtual-attr-list))
			 (or include-deprecated-virtual-attributes-p
			     (not (feature-assq-macro
				    'previously-put-in-attribute-tables
				    (slot-features slot-description)))))
		   collect (eval-cons aliased-slot-name slot-description)
		     using eval-cons)))
      slot-desc-list))

(defun-simple get-list-of-all-virtual-attributes-for-pane
    (class-description include-deprecated-virtual-attributes-p)
  (let* ((virtual-attr-list
	   ;; Potential bug:  users can define attributes with the same
	   ;; name as virtual attributes.  We can't check for that yet.
	   (loop with virtual-attributes = (all-virtual-attributes-for-class
					     class-description
					     include-deprecated-virtual-attributes-p)
		 for attr-name in virtual-attributes
		 collect (eval-cons attr-name (virtual-attribute attr-name))
		   using eval-cons
		 finally (reclaim-eval-list virtual-attributes)))
	 (virtual-attr-list-non-local
	   (when virtual-attributes-not-local-to-a-class
	     (loop with list = (all-non-local-virtual-attributes-for-class
				 class-description
				 include-deprecated-virtual-attributes-p)
		   for name in list
		   collect (eval-cons name (virtual-attribute name))
		     using eval-cons
		   finally (reclaim-eval-list list)))))
    (nconc virtual-attr-list
           virtual-attr-list-non-local)))
;; End of SoftServe changes		

(defun-simple get-list-of-all-user-visible-attributes (class-description)
  (get-list-of-all-user-visible-attributes-specifying-deprecation
    class-description nil))  

(defvar include-slots-visible-only-to-roles-p t)

(defun user-visible-slot-p (slot-description)
  (or (user-defined-slot-description-p slot-description)
      (and (not (feature-assq
		  'do-not-put-in-attribute-tables
		  (slot-features slot-description)))
	   (let ((category?
		   (category-symbol-given-slot-type
		     (feature-assq
		       'type
		       (slot-features slot-description)))))
	     (and category?
		  (or include-slots-visible-only-to-roles-p
		      (slot-value-to-evaluation-value-function
			category?)))))))
      
(defun all-virtual-attributes-for-class (class-description &optional include-deprecated-p)
  (loop for class in (class-inheritance-path class-description)
	as virtual-attributes = (virtual-attributes-local-to-class class)
	as filtered-virtual-attributes
	   = (loop for attribute in virtual-attributes
		   as valid-attribute
		      = (if (and (consp attribute)
				 (eq 'deprecated (cadr attribute)))
			    (if include-deprecated-p
				(car-of-cons attribute)
				nil)
			    attribute)
		   when valid-attribute
		     collect valid-attribute using eval-cons)
	nconc filtered-virtual-attributes))

(defun all-non-local-virtual-attributes-for-class (class-description &optional include-deprecated-p)
  (loop for non-local-attr in virtual-attributes-not-local-to-a-class
	as attribute-structure = (virtual-attribute non-local-attr)
	when (applicable-and-not-deprecated-virtual-attribute-p
	       class-description attribute-structure
	       include-deprecated-p)
	  collect non-local-attr
	    using eval-cons))


;;; `generate-description-of-attribute' is where a lot of the work is done
;;; for the attribute-description functions.  It returns a structure that
;;; tells KB programmers everything they need to know (theoretically) about
;;; a given attribute of a class or item.
;;;
;;; As with get-list-of-all-user-visible-attributes, the "frame" argument
;;; can be nil, but if it's not, it must be of the type described by
;;; "class-description".

(defun generate-description-of-attribute
    (class-name aliased-slot-name slot-description-or-virtual-attribute class-description frame user-mode expose-internal-classes-p)
  (let* ((current-attribute-description-class class-name)
	 (defining-class-name
	     (defining-class-of-slot slot-description-or-virtual-attribute))
	 (writable-via-restrictions
	   (if frame
	       (frame-or-attribute-operation-is-allowed-for-mode-p
		 'edit-attribute frame aliased-slot-name defining-class-name user-mode)
	       t)))
    
  ;; Could be a slot-description structure...
  (if (eq (g2-type-name-of-named-simple-vector slot-description-or-virtual-attribute)
	  (intern-unique-def-structure-symbol-name 'slot-description))
      (let* ((slot-type (feature-assq
			  'type
			  (slot-features slot-description-or-virtual-attribute)))
	     (system-defined-p (system-defined-attribute-p
				 aliased-slot-name
				 (class-name-of-class-description
				   class-description)))
	     (slot-init-form (slot-init-form slot-description-or-virtual-attribute))
	     (category-symbol? (if slot-type
				  (category-symbol-given-slot-type slot-type)))
	     (category-getter? (if category-symbol?
				  (slot-value-to-evaluation-value-function
				    category-symbol?)))
	     (category-setter? (if category-symbol?
				  (evaluation-value-to-category-function
				    category-symbol?)))
	     (text-readable (and slot-type
				 (not (do-not-put-slot-in-attribute-tables-p
					  slot-description-or-virtual-attribute t))))
	     (text-writable (and writable-via-restrictions
				 (not (feature-assq
					'not-user-editable
					(slot-features
					  slot-description-or-virtual-attribute)))))
	     (returned-structure
	       (allocate-evaluation-structure-inline
		 'attribute-name aliased-slot-name
		 'virtual       (make-evaluation-boolean-value nil)
		 'text-readable (make-evaluation-boolean-value text-readable)
		 'text-writable (make-evaluation-boolean-value text-writable)
		 'value-readable (if system-defined-p
				     (make-evaluation-boolean-value
				       (and text-readable category-getter?))
				     evaluation-true-value)
		 'value-writable (if system-defined-p
				     (make-evaluation-boolean-value
				       (and text-readable
					    writable-via-restrictions
					    (and category-setter?
						 system-defined-p)
					    (if frame
						(user-writable-slot-of-instance-p
						  frame
						  (unique-slot-name
						    slot-description-or-virtual-attribute)
						  (defining-class
						      slot-description-or-virtual-attribute))
						(user-writable-slot-of-class-p
						  (class-name-of-class-description
						    class-description)
						  (unique-slot-name
						    slot-description-or-virtual-attribute)
						  (defining-class
						      slot-description-or-virtual-attribute)))))
				     evaluation-true-value)
		 'is-system-defined (make-evaluation-boolean-value
				      system-defined-p)
		 'defining-class (make-evaluation-symbol
				   (cond (expose-internal-classes-p
					  (defining-class-of-slot
					      slot-description-or-virtual-attribute))
					 (t (defining-class-of-slot-for-user
						slot-description-or-virtual-attribute)))))))

	;; Optional attribute:  initial-value or initial-item-class
	(cond
	  (system-defined-p
	   (cond
	     ((or (null category-getter?)
		  (and (consp slot-init-form)
		       (eq (car-of-cons slot-init-form) :funcall))
		  (and (slot-description-p
			 slot-description-or-virtual-attribute)
		       (compound-slot-descriptor
			 (pretty-slot-name
			   slot-description-or-virtual-attribute))))
	      ;; do nothing
	      nil)
	     (t
	      (let ((initial-value? nil))
		;; Attempt to call the getter, but if it doesn't like it, or
		;; returns NIL, then we won't add the initial-value attribute to
		;; the description.
		(setq initial-value?
		      (call-category-getter
			category-symbol?
			(if (and (text-slot-type-p slot-type)
				 (consp slot-init-form))
			    (car slot-init-form)
			    slot-init-form)
			nil
			slot-description-or-virtual-attribute))
		(when initial-value?
		  (setf (evaluation-structure-slot
			  returned-structure 'initial-value)
			initial-value?))))))
	  
	  ((class-type-specification-p
	     (slot-type-specification slot-description-or-virtual-attribute))
	   (setf (evaluation-structure-slot returned-structure 'initial-item-class)
		 (type-specification-class
		   (slot-type-specification
		     slot-description-or-virtual-attribute))))
	  (t
	   (let* ((value slot-init-form)
		  (evaluation-value?
		    (cond
		      ((slot-constantp value)
		       (cast-slot-constant-into-evaluation-value value))
		      ((framep value)
		       (if (serve-item-p value)
			   value
			   nil))
		      ((and (consp value)
			    (eq (car-of-cons value) :funcall))
		       nil)
		      (t
		       (copy-if-evaluation-value value)))))
	     (if evaluation-value?
		 (setf (evaluation-structure-slot returned-structure 'initial-value)
		       evaluation-value?)))))

	;; Optional attribute:  editor-grammar
	(if text-writable
	    (setf (evaluation-structure-slot returned-structure 'editor-grammar)
		  category-symbol?))

	;; Optional attribute:  superseded
	;; (this may go away)
	(if (do-not-put-slot-in-attribute-tables-p slot-description-or-virtual-attribute nil)
	    (setf (evaluation-structure-slot returned-structure 'superseded)
		  evaluation-true-value))

	;; Optional attribute: type.  Since it is often so large, it is printed
	;; last to not obscure the other, shorter attributes.
	(if system-defined-p
	    (if category-getter?
		(setf (evaluation-structure-slot returned-structure 'type)
		      (generate-type-description-of-attribute
			(type-specification-complex-expansion category-symbol?))))
	    (setf (evaluation-structure-slot returned-structure 'type)
		  (generate-type-description-of-attribute
		    (slot-type-specification slot-description-or-virtual-attribute))))

	returned-structure)

	
      ;; Instead of a slot-description, it could be a virtual attribute.
      (let* ((shadowed-slot (find-slot-shadowed-by-virtual-attribute
			      aliased-slot-name class-description))
	     (text-readable (and shadowed-slot
				 (and (feature-assq
					'type
					(slot-features shadowed-slot))
				      (not (do-not-put-slot-in-attribute-tables-p
					       shadowed-slot nil)))))
	     (text-writable (and shadowed-slot
				 (and writable-via-restrictions
				      (if frame
					  (user-writable-slot-of-instance-p
					    frame
					    (unique-slot-name shadowed-slot)
					    (defining-class shadowed-slot))
					  (user-writable-slot-of-class-p
					    (class-name-of-class-description
					      class-description)
					    (unique-slot-name shadowed-slot)
					    (defining-class shadowed-slot))))))
	     (exclude-from-wildcard-denotation
	       (exclude-from-wildcard-denotation-p aliased-slot-name))
	     (returned-structure
	       (allocate-evaluation-structure-inline
		 'attribute-name aliased-slot-name
		 'virtual       (make-evaluation-boolean-value t)
		 'text-readable (make-evaluation-boolean-value text-readable)
		 'text-writable (make-evaluation-boolean-value text-writable)
		 'value-readable (make-evaluation-boolean-value
				   (virtual-attribute-getter?
				     slot-description-or-virtual-attribute))
		 'value-writable (make-evaluation-boolean-value
				   (and writable-via-restrictions
					(virtual-attribute-setter?
					  slot-description-or-virtual-attribute)))
		 'initial-value (funcall-simple-compiled-function
				  (virtual-attribute-initial
				    slot-description-or-virtual-attribute)
				  (class-name-of-class-description
				    class-description))
		 'is-system-defined evaluation-true-value
		 'defining-class (make-evaluation-symbol
				   (cond (expose-internal-classes-p
					  (defining-class-of-slot
					      slot-description-or-virtual-attribute))
					 (t 
					  (defining-class-of-slot-for-user
					      slot-description-or-virtual-attribute)))))))
	  
	;; Optional attribute:  editor-grammar
	(if text-writable
	    (setf (evaluation-structure-slot returned-structure 'editor-grammar)
		  (second (feature-assq 'type (slot-features shadowed-slot)))))
	(when exclude-from-wildcard-denotation
	  (setf (evaluation-structure-slot returned-structure
					   'exclude-from-wildcard-denotation)
		(make-evaluation-boolean-value t)))
	;; Always put the type slot last, since it can be so large.
	(setf (evaluation-structure-slot returned-structure 'type)
	      (generate-type-description-of-attribute
		(virtual-attribute-value-type
		  slot-description-or-virtual-attribute)))
	returned-structure))))


;;; The next two functions are a partition of what was formerly called
;;; user-writable-slot-p (aka semantically-editable-slot-p).  Much of this
;;; code came from editable-slot-p, in commands0, part of which was abstracted
;;; out into a new function called might-be-writable-slot-p.

(defun user-writable-slot-of-class-p (class-name slot-name defining-class?)
  (let* ((attribute-features
	   (get-attribute-features class-name slot-name defining-class? nil)))
    (if (type-slot-feature-assq-if-editable attribute-features) t nil)))

(defun user-writable-slot-of-instance-p (frame slot-name defining-class?)
  (let* ((attribute-features
	   (get-attribute-features (class frame) slot-name defining-class? nil))
	 (type-of-slot?
	   (type-slot-feature-assq-if-editable attribute-features)))
    (and (user-writable-slot-of-class-p (class frame) slot-name defining-class?)
	 (transient-or-permanent-p frame)
	 (or (not-a-system-slot-name-p slot-name)
	     (feature-assq 'class-of-optional-subframe attribute-features)
	     (might-be-writable-slot-p frame slot-name type-of-slot?))
	 (null (reason-permanent-items-attribute-is-not-editable frame slot-name defining-class?)))))



(defun find-slot-shadowed-by-virtual-attribute (virtual-attribute-name class-description)
  (loop for slot-description in (slot-descriptions class-description)
	for aliased-slot-name = (alias-slot-name-if-necessary
				  (pretty-slot-name slot-description)
				  (defining-class slot-description))
	until (eq aliased-slot-name virtual-attribute-name)
	finally
	  (return (if (eq aliased-slot-name virtual-attribute-name)
		      slot-description
		      nil))))



;;; `generate-type-description-of-attribute':  Returns a structure that
;;; exhaustively describes the type of an attribute, in a form useful to
;;; a KB programmer.

(defun generate-type-description-of-attribute (type-specification)
  ;; Returns a structure that describes the type of an attribute,
  ;; in a form useful to a KB programmer.
  (if (consp type-specification)
      (let ((type-or-operator (car type-specification))
	    (rest-of-spec (cdr type-specification)))
	(case type-or-operator
	 
	  ((or and)
	   (loop  for operand in rest-of-spec
		 collect (generate-type-description-of-attribute operand)
		   into op-list
		   using eval-cons
		 finally
		   (return (allocate-evaluation-structure-inline
			     'type-or-operator type-or-operator
			     'operands (allocate-evaluation-sequence op-list)))))
	 
	  (not
	   (allocate-evaluation-structure-inline
	     'type-or-operator 'not
	     'operand (generate-type-description-of-attribute
			(first rest-of-spec))))

	  (member
	   (allocate-evaluation-structure-inline
	     'type-or-operator 'member
	     'possible-values (allocate-evaluation-sequence
				(copy-list-using-eval-conses rest-of-spec))))

	  ((integer-range float-range quantity-range)
	   (allocate-evaluation-structure-inline
	     'type-or-operator type-or-operator
	     'high '()
	     'low '()))   ;; unfinished
	  
	  (structure
	   (let* ((details? (structure-type-specification-has-details-p
			      type-specification))
		  (slots? (and details?
			       (structure-type-specification-slot-list
				type-specification)))
		  (minimum-contents?
		    (and details?
			 (structure-type-specification-minimum-contents
			   type-specification))))
	     (allocate-evaluation-structure
	       (nconc
		 (eval-list 'type-or-operator 'structure)
		 (if slots?
		     (eval-list
		       'slots
		       (allocate-evaluation-sequence
			 (loop for slot-spec in slots?
			       collect (allocate-evaluation-structure-inline
					 'attribute-name (first slot-spec)
					 'type
					 (generate-type-description-of-attribute
					   (second slot-spec)))
				 using eval-cons)))
		     nil)
		 (if minimum-contents?
		     (eval-list
		       'required-slots
		       (generate-structure-required-attributes-sequences
			 minimum-contents?))
		     nil)))))
	  (sequence
	   (let ((elt-type? (sequence-type-specification-element-type
			      type-specification))
		 (low-bound? (sequence-type-specification-low-bound
			       type-specification))
		 (high-bound? (sequence-type-specification-high-bound
				type-specification)))
	     (allocate-evaluation-structure
	       (nconc
		 (eval-list 'type-or-operator 'sequence)
		 (if elt-type?
		     (eval-list
		       'element-type
		       (generate-type-description-of-attribute elt-type?))
		     nil)
		 (if low-bound?
		     (eval-list 'minimum-elements low-bound?)
		     nil)
		 (if high-bound?
		     (eval-list 'maximum-elements high-bound?))))))

	  (class
	   (allocate-evaluation-structure-inline
	     'type-or-operator 'class
	     'class-name (type-specification-class type-specification)))
	  
	  (no-item
	   (allocate-evaluation-structure-inline
	     'type-or-operator 'none))

	  (named
	   (generate-type-description-of-attribute
	     (type-specification-complex-expansion (first rest-of-spec))))

	  (otherwise
	   (if (and (not rest-of-spec)  ;; of form "(integer)", for example
		    (user-type-for-type-specification type-or-operator))
	       (allocate-evaluation-structure-inline
		 'type-or-operator
		 (user-type-for-type-specification type-or-operator))
	       nil))))
	
      ;; End if...
      ;; Not a cons; must be a simple value type.
      (allocate-evaluation-structure-inline
	'type-or-operator
	(user-type-for-type-specification type-specification))))

(defun-simple generate-structure-required-attributes-sequences (boolean-combo)
  (if (null boolean-combo)
      (error "Can't make sequence showing a null required set of attributes")
      (if (symbolp boolean-combo)
	  boolean-combo
	  (allocate-evaluation-sequence
	    (loop for elt in boolean-combo
		  collect (generate-structure-required-attributes-sequences elt)
		    using eval-cons)))))

#+development
(defun-simple regenerate-structure-attribute-boolean-combo (sequence)
  (if (evaluation-sequence-p sequence)
      (loop for elt being each evaluation-sequence-element of sequence
	    collect (regenerate-structure-attribute-boolean-combo elt)
	      using phrase-cons)
      sequence))
			    




;;; The function `generate-type-specification-from-description' takes a
;;; type-description structure produced by
;;; generate-type-description-of-attribute and will create and return the
;;; corresponding type-specification, constructed from phrase-conses.

#+development
(defun-simple generate-type-specification-from-description (type-description)
  (let* ((type-or-operator
	   (evaluation-structure-slot type-description 'type-or-operator))
	 (symbol-type-spec?
	   (and (neq type-or-operator 'sequence)
		(neq type-or-operator 'structure)
		(type-specification-for-user-type type-or-operator))))
    (when symbol-type-spec?
      (return-from generate-type-specification-from-description
	symbol-type-spec?))
    (case type-or-operator
      ((or and)
       (phrase-cons
	 type-or-operator
	 (loop for subtype being each evaluation-sequence-element of
	       (evaluation-structure-slot type-description 'operands)
	       collect (generate-type-specification-from-description subtype)
		 using phrase-cons)))
      
      ((not)
       (phrase-list
	 type-or-operator
	 (generate-type-specification-from-description
	   (evaluation-structure-slot type-description 'operand))))
      
      ((member)
       (phrase-cons
	 type-or-operator
	 (loop for value being each evaluation-sequence-element of
	       (evaluation-structure-slot type-description 'possible-values)
	       collect (copy-if-evaluation-value value)
		 using phrase-cons)))
      
      ((integer-range float-range quantity-range)
       (phrase-list
	 type-or-operator
	 (evaluation-structure-slot type-description 'low)
	 (evaluation-structure-slot type-description 'high)))
      
      ((structure)
       (let ((slots (evaluation-structure-slot type-description 'slots))
	     (minimum-contents
	       (evaluation-structure-slot type-description 'required-slots)))
	 (if (and (null slots) (null minimum-contents))
	     '(structure)
	     (phrase-list*
	       'structure
	       (loop for slot-spec being each evaluation-sequence-element of slots
		     collect (phrase-list
			       (evaluation-structure-slot slot-spec 'attribute-name)
			       (generate-type-specification-from-description
				 (evaluation-structure-slot slot-spec 'type)))
		       using phrase-cons)
	       (if minimum-contents
		   (phrase-list
		     (regenerate-structure-attribute-boolean-combo
		       minimum-contents))
		   nil)))))

      ((sequence)
       (let* ((elt-desc? (evaluation-structure-slot
			   type-description 'element-type))
	      (elt-type-spec?
		(if elt-desc?
		    (generate-type-specification-from-description elt-desc?)))
	      (low-bound? (evaluation-structure-slot
			    type-description 'minimum-elements))
	      (high-bound? (evaluation-structure-slot
			     type-description 'maximum-elements)))
	 (if (or low-bound? high-bound?)
	     (phrase-list 'sequence elt-type-spec? low-bound? high-bound?)
	     (if elt-type-spec?
		 (phrase-list 'sequence elt-type-spec?)
		 '(sequence)))))

      ((class)
       (make-class-type-specification
	 (evaluation-structure-slot type-description 'class-name)))

      ((none)
       '(no-item))
      
      (t (error "Unrecognized type-or-operator ~a" type-or-operator)))))

	       






;;;; Exporting System Attributes for G2 Developer Use


;;; The development-only function `exported-attribute-description' takes a file
;;; name and will emit text to that file describing all of the exported
;;; attributes currently in effect within the loaded G2 image.  This file is in
;;; HTML format, ready for inclusion into the projects documents.

;;; The slots to be included in the exported attribute description are those
;;; defined on classes inherited into the subclasses of item and which have a
;;; type slot feature where the grammar-category defined in that type has a
;;; defined part-interpretation.  Additionally included are the defined
;;; attribute mimics.  Finally, those slots having a attribute-export-comment
;;; but which do not meet the other criteria are included at the bottom of the
;;; descriptions for a class.

;;; The output is organized by defining class.  Note that this must be run from
;;; within a breakpoint in a G2 process.  Otherwise, it will crash looking for
;;; class-bit-vectors and other environment information.

#+development
(defun exported-attribute-document 
        (&optional
	  (projects-dir nil)
	  (final-name    "lic-0013-attribute-details.html")
	  (prologue-name "lic-0013-attribute-details-prologue.html")
	  (epilogue-name "lic-0013-attribute-details-epilogue.html")
	  (index-name    "lic-0013-attribute-details-index.html")
	  (index-prologue-name "lic-0013-attribute-details-index-prologue.html")
	  (mml-name      "lic-0013-exported-attributes-doc-draft.mml"))
  (unless projects-dir
    (let ((source-sandbox? (get-gensym-environment-variable "SRCBOX")))
      (setq projects-dir
	    (cond (source-sandbox?
		   (format nil "~a/projects/" source-sandbox?))
		  (source-directory-name
		   (format nil "~a/projects/" source-directory-name))
		  (t
		   (error
		     "No SRCBOX or source-directory-name, you must ~
                      provide an explicit projects dir argument to ~
                      exported-attribute-document."))))))
  (with-open-file (html-stream (format nil "~a~a" projects-dir final-name)
			       :direction :output)
    (with-open-file (prologue (format nil "~a~a" projects-dir prologue-name))
      (loop for line = (read-line prologue nil nil)
	    while line do (write-line line html-stream)))
    (with-open-file (index-stream (format nil "~a~a" projects-dir index-name)
				  :direction :output)
      (with-open-file (index-start (format nil "~a~a"
					   projects-dir index-prologue-name))
	(loop for line = (read-line index-start nil nil)
	      while line do (write-line line index-stream)))
      (with-open-file (mml-stream (format nil "~a~a" projects-dir mml-name)
				  :direction :output)
	(exported-attribute-description-new
	  html-stream mml-stream index-stream final-name)
	(terpri mml-stream)
	(terpri index-stream)))
    (with-open-file (epilog (format nil "~a~a" projects-dir epilogue-name))
      (loop for line = (read-line epilog nil nil)
	    while line do (write-line line html-stream)))
    (terpri html-stream)))




;;; The variable `non-item-class-attribute-name-alist' is used to hold the names
;;; of the system classes that will be desribed in the exported attribute
;;; document, along with the names of the "Included Attribute" sets that we will
;;; present as the user myth of what is going on.

#+development
(defvar non-item-class-attribute-name-alist
  `((block      "Standard Attributes")
    (entity     "Iconic Attributes")
    (text-box   "Textual Attributes")
    (workspace  "Workspace Attributes")
    ))

#+development
(defun exported-attribute-description-new
    (ostream end-user-stream index-stream html-file-name)
  (format end-user-stream "<MML>~%<Include mml-include.mml>~2%")
  (format index-stream
	  "<P><B>Index of Exported Attribute Descriptions</B>~%<P>~%<OL>")
  (format t "~%Collecting class descriptions...")
  (loop with attribute-index-list = (list :head)
	with class-list
	  = (loop for class being each subclass of 'item do
	      (unless (system-defined-class-p class)
		(cerror "continue, including it"
			"Non-system classs ~a about to be included in description."
			class))
	          unless (or (subclassp class 'tw-item)
			     (memq class '(tw-resource
					   tw-procedure
					   tw-method-declaration
					   tw-method
					   tw-dispatch-table)))
		    collect (list class (class-description class)
				  (g2-get-attribute-descriptions-of-class
				    class (g2-get-attributes-visible-in-mode
					    class 'administrator))))
	with non-item-class-list
	  = (loop for (class) in non-item-class-attribute-name-alist
		  collect (list class (class-description class)
				(g2-get-attribute-descriptions-of-class
				  class
				  (g2-get-attributes-visible-in-mode
				    class 'administrator))))
	with superior-class-list = (append non-item-class-list class-list)
	for (class class-description attr-sequence)
	    in (append
		 non-item-class-list
		 (sort (the list class-list) #'string<
		       :key #'(lambda (x) (symbol-name (car x)))))
	for class-counter from 1
	do
    (format t "~%Class ~s" class)
    (loop with inherited-attributes = nil
	  for attribute-structure being each evaluation-sequence-element of attr-sequence
	  for name = (evaluation-structure-slot attribute-structure 'attribute-name)
	  unless
	    (loop named superior-search
		  for class in (reverse (cdr (class-inheritance-path class-description)))
		  for superior-attr-sequence? = (third (assq class superior-class-list))
		  do
	      ;; When an equal attribute-description can be found in
	      ;; superior-class, or in the special case of the class attribute
	      ;; inherited from item, suppress showing that attribute, but list
	      ;; it as an inherited attribute.
	      (when (or (and superior-attr-sequence?
			     (not (memq name '(class)))
			     (loop for attr being each evaluation-sequence-element
				   of superior-attr-sequence?
				   thereis (and (eq (evaluation-structure-slot attr 'attribute-name)
						    name)
						(evaluation-value-eql attr attribute-structure))))
			(and (eq class 'item)
			     (memq name '(class))))
		(let ((class-entry (assq class inherited-attributes)))
		  (cond (class-entry
			 (setf (cdr (last class-entry)) (cons name nil)))
			(t
			 (setq inherited-attributes
			       (nconc inherited-attributes (list (list class name))))))
		  (return-from superior-search t))))
	    collect name into new-attributes
	  finally
	    ;; Print a single class' description.
	    (format-attributes-of-class-new
	      end-user-stream ostream
	      attribute-index-list class-counter class class-description
	      attr-sequence inherited-attributes new-attributes
	      html-file-name)
	  )
	finally
	  (sort-attribute-index-list attribute-index-list)
	  (format-attribute-index-list index-stream attribute-index-list)
	  (format index-stream "</UL>~%")))


#+development
(defun format-attributes-of-class-new
    (end-user-stream ostream index-list class-counter class class-description
		     attribute-sequence inherited-attributes new-attributes
		     html-file-name)
  (let* ((item-subclass? (class-description-of-class-p class-description 'item))
	 (monicer (if item-subclass?
		      (string-downcase (symbol-name class))
		      (second (assq class non-item-class-attribute-name-alist)))))
		  
    (format-attribute-export-class
      end-user-stream ostream index-list class-counter class class-description
      inherited-attributes
      html-file-name)

    (when new-attributes
      (format end-user-stream
	      "<ProcH2NoTOC>~%~a~2%"
	      (if item-subclass? "Class-Specific Attributes" "Attributes"))
      (format ostream "<UL>~%")

      (loop with class-text = monicer
	    for name in (if item-subclass?
			    new-attributes
			    (loop for attr in new-attributes
				  unless (or (eq attr 'class)
					     (eq attr 'foundation-class))
				    collect attr))
	    for name-text = (string-downcase name)
	    for struct = (loop for attr being each evaluation-sequence-element of attribute-sequence
			       when (eq (evaluation-structure-slot attr 'attribute-name) name)
				 return attr
			       finally (error "Can't find ~a::~a struct." class name))
	    do
	(if item-subclass?
	    (format
	      end-user-stream
	      "<ProcH3NoTOC>~@
                 <Marker <MType 2> <MText `\\<G2Code\\>~a\\<Default Para Font\\> class: \\<G2Code\\>~a;\\<G2Code\\>~a\\<Default Para Font\\> attribute: \\<G2Code\\>~a'>>~
                 ~a~2%"
	      class-text name-text
	      name-text class-text
	      name-text)
	    (format
	      end-user-stream
	      "<ProcH3NoTOC>~@
                 <Marker <MType 2> <MText `\\<G2Code\\>~a\\<Default Para Font\\>: \\<G2Code\\>~a;\\<G2Code\\>~a\\<Default Para Font\\> attribute: \\<G2Code\\>~a'>>~
                 ~a~2%"
	      class-text name-text
	      name-text class-text
	      name-text))
	(format ostream "<LI><TT>~(~a~)</TT>: " name)

	;; Two by two, write the elements of the attribute description, except for
	;; the initial-value and type descriptions, which are written last and with
	;; different formatting.
	(write-line "<xG2CodeNoBreak1>" end-user-stream)
	(loop with first = t
	      with even-attribute = t
	      for (struct-attr . value) being each evaluation-structure-pair of struct
	      do
	  (unless (memq struct-attr '(attribute-name initial-value type))
	    (cond (first (setq first nil))
		  (t
		   (write-string ", " ostream)
		   ;; Always put a newline before editor grammar and superseded.
		   (when (memq struct-attr '(superseded editor-grammar))
		     (setq even-attribute t))
		   (write-string (if even-attribute ",\\n" ", ") end-user-stream)))
	    (setq even-attribute (not even-attribute))
	    (write-exported-attribute-feature
	      struct-attr value end-user-stream ostream)))
	(format end-user-stream "~2%")

	;; When initial value is present, write it, bolding the name.
	(when (evaluation-structure-slot struct 'initial-value)
	  (write-line "<xG2CodeNoBreak1>" end-user-stream)
	  (write-exported-attribute-feature
	    'initial-value (evaluation-structure-slot struct 'initial-value)
	    end-user-stream ostream)
	  (format end-user-stream "~2%"))

	;; When type is present, write it, bolding the name and using the funky
	;; type-spec writer for the type.
	(when (evaluation-structure-slot struct 'type)
	  (write-line "<xG2CodeNoBreak1>" end-user-stream)
	  (write-string "type = " end-user-stream)
	  (write-string "type = " ostream)
	  (with-phrase-conses
	    (let* ((type-spec
		     (generate-type-specification-from-description
		       (evaluation-structure-slot struct 'type)))
		   (wide-type-text
		     (let ((write-symbols-parsably? nil))
		       (tformat-text-string "~NT" type-spec)))
		   (ascii-type-text (export-text-string wide-type-text 'ascii)))
	      (write-string ascii-type-text ostream)
	      (reclaim-wide-string wide-type-text)
	      (reclaim-gensym-string ascii-type-text)
	      (cond
		((or (sequence-type-specification-p type-spec)
		     (and (structure-type-specification-p type-spec)
			  (structure-type-specification-has-details-p type-spec)))
		 (write-string "\\n" end-user-stream)
		 (indent-for-type-spec 1 end-user-stream)
		 (write-exported-type-spec type-spec 1 end-user-stream))
		(t
		 (write-exported-type-spec type-spec 0 end-user-stream)))))
	  (format end-user-stream "~2%"))
	(terpri ostream))
      (format ostream "</UL>~2%"))
    (terpri end-user-stream)))

#+development
(defmacro twith-output-to-lisp-stream (lisp-stream &rest body)
  (let ((l-stream (gensym)))
    `(let ((,l-stream ,lisp-stream)
	   (gensym-string (twith-output-to-gensym-string
			    ,@body)))
       (write-string gensym-string ,l-stream)
       (reclaim-gensym-string gensym-string))))

#+development
(defun write-exported-attribute-feature
    (struct-attr value end-user-stream ostream)
  (let* ((attr-name (string-downcase (symbol-name struct-attr)))
	 (wide-description
	   (twith-output-to-text-string
	     (let ((write-symbols-parsably? nil))
	       (twrite-string " = ")
	       (write-evaluation-value
		 value
		 (not (evaluation-text-p value))))))
	 (ascii (export-text-string wide-description 'ascii)))
    (write-string attr-name end-user-stream)
    (write-string attr-name ostream)
    (format end-user-stream "~(~a~)" ascii)
    (format ostream "~(~a~)" ascii)
    (reclaim-wide-string wide-description)
    (reclaim-gensym-string ascii)))

#+development
(defun indent-for-type-spec (indent end-user-stream)
  (loop for count from 0 below indent do
    (unless (=f count 0)
      (write-char #\. end-user-stream))
    (write-string "\\t" end-user-stream)))

#+development
(defparameter exported-member-type-names '(color-or-metacolor linear-unit-of-length))

#+development
(defun exported-slot-required-in-minimum-contents (slot-name minimum-contents)
  (or (eq slot-name minimum-contents)
      (and (consp minimum-contents)
	   (eq (car minimum-contents) 'and)
	   (loop for spec in (cdr minimum-contents)
		 thereis (exported-slot-required-in-minimum-contents
			   slot-name spec)))))

#+development
(defun write-exported-type-spec
    (type-spec indent end-user-stream
	       &optional suppress-leading-newline? subsequent-line-extra-spacing?)
  (let ((new-indent (+f indent 1)))
    (cond
      ((sequence-type-specification-p type-spec)
       (let* ((elt-type (or (sequence-type-specification-element-type type-spec)
			    '(item-or-datum)))
	      (low-bound? (sequence-type-specification-low-bound type-spec))
	      (high-bound? (sequence-type-specification-high-bound type-spec))
	      (all-optional? (or (null low-bound?) (eql low-bound? 0))))
	 (when high-bound?
	   (cerror "continue"
		   "Can't export high-bound descriptions of ~s" type-spec))
	 (write-string "sequence\\n" end-user-stream)
	 (indent-for-type-spec new-indent end-user-stream)
	 (write-string "(" end-user-stream)
	 (when all-optional?
	   (write-char #\[ end-user-stream))
	 (write-exported-type-spec
	   elt-type
	   (if (or (union-type-specification-p elt-type)
		   (member-type-specification-p elt-type))
	       indent
	       new-indent)
	   end-user-stream t (if all-optional? "  " " "))
	 (write-string "\\n" end-user-stream)
	 (indent-for-type-spec new-indent end-user-stream)
	 (write-string " [, ...]" end-user-stream)
	 (when all-optional?
	   (write-char #\] end-user-stream))
	 (write-string ")" end-user-stream)))
      ((structure-type-specification-p type-spec)
       (let* ((details? (structure-type-specification-has-details-p type-spec))
	      (slot-list
		(and details?
		     (structure-type-specification-slot-list type-spec)))
	      (min-contents
		(and details?
		     (structure-type-specification-minimum-contents type-spec))))
	 (write-string "structure" end-user-stream)
	 (cond
	   ((null details?)
	    (write-string "()" end-user-stream))
	   (t
	    (loop with first-optional? = nil
		  for slot-spec-cons on slot-list
		  for name = (caar slot-spec-cons)
		  for type = (cadar slot-spec-cons)
		  for required? = (exported-slot-required-in-minimum-contents
				    name min-contents)
		  do
	      (write-string "\\n" end-user-stream)
	      (indent-for-type-spec new-indent end-user-stream)
	      (cond ((eq slot-spec-cons slot-list)
		     (write-char #\( end-user-stream))
		    (first-optional?
		     (write-char #\space end-user-stream)))
	      (cond (required?
		     (when (neq slot-spec-cons slot-list)
		       (write-char #\space end-user-stream)))
		    (t
		     (when (eq slot-spec-cons slot-list)
		       (setq first-optional? t))
		     (write-char #\[ end-user-stream)))
	      (format end-user-stream
		      "<G2CodeBold>~(~a~)<G2CodePlain>: " name)
	      (when (and required?
			 (type-specification-subtype-p '(no-item) type))
		(warn "~%Slot ~a is required and allows no-item" name))
	      (with-phrase-conses
		(write-exported-type-spec
		  (type-specification-minus-type type '(no-item))
		  new-indent end-user-stream))
	      (when (cdr slot-spec-cons)
		(write-char #\, end-user-stream))
	      (when (not required?)
		(write-char #\] end-user-stream)))
	    (write-char #\) end-user-stream)))))
      ((union-type-specification-p type-spec)
       (cond
	 ((null (cddr type-spec))
	  (write-exported-type-spec (second type-spec) indent end-user-stream))
	 (t
	  (with-phrase-conses
	    (let ((reordered-type type-spec))

	      ;; Flatten any nested OR types.
	      (when (loop for type in (cdr reordered-type)
			  thereis (union-type-specification-p type))
		(loop with collected-type = (second reordered-type)
		      for next-type in (cddr reordered-type)
		      do
		  (setq collected-type
			(make-type-specification-union
			  collected-type next-type))
		      finally
			(setq reordered-type collected-type)))

	      ;; The previous and following expressions were in the
	      ;; wrong order before today. - jpg 6/13/01

	      (if (and (type-specification-subtype-p '(no-item)
						     reordered-type)
		       (not (equal (second type-spec) '(no-item))))
		  (setq reordered-type
			(make-type-specification-union
			  '(no-item)
			  (type-specification-minus-type reordered-type 
							 '(no-item)))))

	      ;; Next, emit them.
	      (loop for type-cons on (cdr reordered-type)
		    for subtype = (car type-cons)
		    do
		(unless (eq type-cons (cdr reordered-type))
		  (write-string " |" end-user-stream))
		;; If the subtype will emit a newline, it will also increase the
		;; indent level.  So, emit nested member types at the same
		;; indent level as this union type.
		(cond
		  ((and (member-type-specification-p subtype)
			(cddr subtype)
			(loop for named-type in exported-member-type-names
			      never (equal subtype
					   (type-specification-complex-expansion
					     named-type))))
		   (write-exported-type-spec
		     subtype indent end-user-stream
		     (and suppress-leading-newline?
			  (eq type-cons (cdr reordered-type)))
		     subsequent-line-extra-spacing?))
		  (t
		   (unless (and suppress-leading-newline?
				(eq type-cons (cdr reordered-type)))
		     (write-string "\\n" end-user-stream)
		     (indent-for-type-spec new-indent end-user-stream))
		   (when (and subsequent-line-extra-spacing?
			      (not (eq type-cons (cdr reordered-type))))
		     (write-string subsequent-line-extra-spacing? end-user-stream))
		   (write-exported-type-spec subtype new-indent end-user-stream)))))))))
      ((member-type-specification-p type-spec)
       (cond ((null (cdr type-spec))
	      (write-string "none" end-user-stream))
	     ((null (cddr type-spec))
	      (twith-output-to-lisp-stream
		end-user-stream
		(write-evaluation-value (second type-spec) t)))
	     ;; Perhaps we could do lots more "naming" here, but for now, this
	     ;; is it.
	     ((loop for named-type in exported-member-type-names do
		(when (equal type-spec (type-specification-complex-expansion named-type))
		  (format end-user-stream "<G2CodeItalic>~(~a~)<G2CodePlain>" named-type)
		  (return t)))
	      nil)
	     (t
	      (unless suppress-leading-newline?
		(write-string "\\n" end-user-stream)
		(indent-for-type-spec new-indent end-user-stream))
	      (loop for value-cons on (cdr type-spec)
		    for value = (car value-cons)
		    do
		(twith-output-to-lisp-stream
		  end-user-stream
		  (write-evaluation-value value t))
		(when (cdr value-cons)
		  (write-string " |\\n" end-user-stream)
		  (indent-for-type-spec new-indent end-user-stream)
		  (when subsequent-line-extra-spacing?
		    (write-string subsequent-line-extra-spacing? end-user-stream)))))))
		      
      ((intersection-type-specification-p type-spec)
       (warn "AND type-spec found ~a" type-spec))
      (t
       (let ((gensym-string (twith-output-to-gensym-string
			      (write-type-specification type-spec))))
	 (write-string gensym-string end-user-stream)
	 (reclaim-gensym-string gensym-string)))))
  ;; The following line makes this easier to test, since writing the output to
  ;; *standard-output* and returning zero values causes just the right thing to
  ;; be output to the command line.
  (values))

#+development
(defun sort-attribute-index-list (index-list)
  (setf (cdr index-list)
	(sort (cdr index-list)
	      #'string<
	      :key #'car)))
#+development
(defun format-attribute-index-list (index-stream index-list)
  (loop for (ignore . line) in (cdr index-list)
	do (write-line line index-stream)))
  

#+development
(defun add-attribute-index-entry (index-list string class)
  (setf (cdr index-list)
	(cons (cons class string)
	      (cdr index-list))))

#+development
(defun write-exported-comma-list (symbol-list stream)
  (loop with first = t
	for symbol in symbol-list
	do
    (if first
	(setq first nil)
	(write-string ", " stream))
    (write-string (string-downcase (symbol-name symbol)) stream)))

#+development
(defun write-exported-list (symbol-list stream)
  (cond
    ((null (cdr symbol-list))
     (format stream "~(~a~)" (car symbol-list)))
    ((null (cddr symbol-list))
     (format stream "~(~a and ~a~)" (car symbol-list) (cadr symbol-list)))
    (t
     (loop for symbol-cons on symbol-list do
       (unless (eq symbol-cons symbol-list)
	 (write-string (if (cdr symbol-cons) ", " ", and ") stream))
       (write-string (string-downcase (symbol-name (car symbol-cons)))
		     stream)))))
	  
#+development
(defun format-attribute-export-class
    (end-user-stream ostream index-list class-counter class class-description
		     inherited-attributes html-file-name)
  (let* ((item-subclass? (class-description-of-class-p class-description 'item))
	 (class-name
	   (if item-subclass?
	       (string-downcase (symbol-name class))
	       (second (assq class non-item-class-attribute-name-alist))))
	 (superior-descriptions
	   (class-description-inheritance-path class-description))
	 (item-superiors
	   (loop for superior-desc in (cdr superior-descriptions)
		 when (class-description-of-class-p superior-desc 'item)
		   collect (class-name-of-class-description superior-desc))))

    (if item-subclass?
	(format
	  end-user-stream
	  "<ProcH1TopTOC1>~@
             <Marker <MType 2> <MText `\\<G2Code\\>~a\\<Default Para Font\\> class'>>~
             <Marker <MType 8> <MText `newlink ~a'>>~a~2%"
	  class-name class-name class-name)
	(format
	  end-user-stream
	  "<ProcH1TopTOC1>~@
             <Marker <MType 2> <MText `\\<G2Code\\>~a\\<Default Para Font\\>'>>~
             <Marker <MType 8> <MText `newlink ~a'>>~a~2%"
	  class-name class-name class-name))
    (format ostream "~%<P><BR><BR><A NAME=\"~a\">~d.  <B>~a</B><BR>~%"
	    class class-counter class)
    (add-attribute-index-entry
      index-list
      (format nil "~%<LI><A HREF=\"~a#~a\">~d.  <B>~a</B></A>~%"
	      html-file-name class class-counter class)
      class)

    (when item-subclass?
      (format end-user-stream
	      "<ProcH2NoTOC>~%Class Inheritance Path~@
             <G2Code>~@
             <G2CodeBold>~a<G2CodePlain>"
	      class-name)
      (when item-superiors
	(write-string ", " end-user-stream)
	(write-exported-comma-list item-superiors end-user-stream))
      (when (loop for (superior-class) in inherited-attributes
		  thereis (not (subclassp superior-class 'item)))
	(format end-user-stream "~2%<ProcH2NoTOC>~%Included Attributes~2%")
	(loop for (superior-class . attributes) in inherited-attributes do
	  (when (not (subclassp superior-class 'item))
	    (let ((moniker
		    (second
		      (assq superior-class
			    non-item-class-attribute-name-alist))))
	      (format
		end-user-stream
		"<G2Code>~@
                    <G2CodeBold><Marker <MType 8> <MText `gotolink ~(~a~)'>>~
                    ~(~a~)<G2CodePlain>:  "
		moniker moniker)
	      (write-exported-comma-list attributes end-user-stream)
	      (format end-user-stream "~2%")))))
      
      (format end-user-stream "~2%<ProcH2NoTOC>~%Inherited Attributes~2%")
      (loop for (superior-class . attributes) in inherited-attributes do
	(when (subclassp superior-class 'item)
	  (format
	    end-user-stream
	    "<G2Code>~@
               <G2CodeBold><Marker <MType 8> <MText `gotolink ~(~a~)'>>~
               ~(~a~)<G2CodePlain>:  "
	    superior-class superior-class)
	  (write-exported-comma-list attributes end-user-stream)
	  (format end-user-stream "~2%"))))
    
    (format ostream "Class inheritance path: ")
    (loop for first = t then nil
	  for superior-class
	      in (cdr (class-inheritance-path class-description))
	  do
      (unless first
	(format ostream ", "))
      (if (memq superior-class item-superiors)
	  (format ostream "<B>~(~a~)</B>" superior-class)
	  (format ostream "<I>~(~a~)</I>" superior-class)))
    (terpri ostream)
    (when (feature-assq 'class-export-comment
			(class-features class-description))
      (format ostream "<BR><I>")
      (format ostream
	      (second (feature-assq 'class-export-comment
				    (class-features class-description))))
    (format ostream "</I>~%"))))




;;; The list `global-attribute-features' describes the mapping between internal
;;; slot features and exported attribute-features. The first element of each
;;; list is the exported feature name. The second element is either the source
;;; name, or a keyword describing the source of the feature.

#+development
(defparameter global-attribute-features
  '(
					; Type allowed, including extended type
					; descriptions
    (type type)
					; The grammar-class
    (editor-grammar editor-grammar)
    (attr-export-comment attribute-export-comment)
    (defining-class :computed)
					; Initialization will be found in
					; initial-value, initial-item-class, or
					; neither.
    (initial-value :computed)
    (initial-item-class :computed)
					; Generalized configuration, primarily
					; intended for ui-layout-hints, which
					; may be created through an
					; attribute-configuration item.
    (attribute-configurations attribute-configurations)
					; The user may modify this slot.
    (writable :computed-from (not not-user-editable))
					; Any attribute which is provided by a
					; builtin g2 class rather than a
					; user-defined class.
    (system-defined system)
					; A feature on system-defined attribute
					; descriptions which indicates the user
					; can give that attribute a user-defined
					; default value ( a attribute-init-form
					; that differs from that of the
					; attribute-init-form of the system
					; defining class.
    (user-overridable user-overridable)))

;; Not exported: lookup-slot, vector-slot, no-accessor, save, do-not-save,
;; class-of-optional-subframe, do-not-identify-in-attribute-tables,
;; do-not-put-in-attribute-tables, (do-not-put-in-attribute-tables nupec),
;; (do-not-put-in-attribute-tables not-nupec),
;; do-not-put-in-attribute-tables-if-null, class-slot, edit-only, do-not-clone,
;; select-changes, note-slot-changes, previously-put-in-attribute-tables





;;;; Testing Harness for attribute->part and part->attribute mapping.




(defun-for-system-procedure g2-test-conclude-component
    (frame slot-name-ev class-if-specific-or-false evaluation-value)
  (let ((class-if-specific?
	  (and (evaluation-symbol-p class-if-specific-or-false)
	       (evaluation-symbol-symbol class-if-specific-or-false)))
	(slot-name (prog1 (evaluation-symbol-symbol slot-name-ev)
		     (reclaim-evaluation-value slot-name-ev))))
    (reclaim-if-evaluation-value class-if-specific-or-false)
    (reclaim-evaluation-value slot-name-ev)
    (let* ((unaliased-slot-name
	     (or (get-slot-name-for-alias-if-any slot-name frame)
		   slot-name))
	   (slot-description
	     (get-slot-description-of-frame
	       unaliased-slot-name
	       frame class-if-specific?))
	   (slot-type?
	     (and slot-description
		  (feature-assq 'type (slot-features slot-description)))))
      (unless slot-description
	(stack-error cached-top-of-stack "bogus slot name ~a" slot-name))
      (when slot-type?
	(let* ((category (category-symbol-given-slot-type slot-type?))
	       (text-slot-p (text-slot-type-p slot-type?))
	       (parse-result-maker?
		 (evaluation-value-to-category-function category)))
	  (when parse-result-maker?
	    (with-attribute-export-conclude-context
		frame
	      (multiple-value-bind (parse-result-or-bad-phrase error-string?)
		  (call-category-setter-fn
		    parse-result-maker?
		    evaluation-value frame slot-description nil)
		(cond ((eq parse-result-or-bad-phrase bad-phrase)
		       (stack-error cached-top-of-stack
				    "malformed component:  ~a"
				    error-string?))
		      (t
		       (let ((commit-error-string?
			       (simple-commit-parse-result
				 frame unaliased-slot-name class-if-specific?
				 slot-description nil nil
				 category text-slot-p
				 parse-result-or-bad-phrase nil
				 evaluation-value)))
			 (when commit-error-string?
			   (stack-error cached-top-of-stack
					"bad component contents:  ~a"
					commit-error-string?)))))))))))))




(defun-for-system-procedure g2-test-get-component
    (frame slot-name-ev class-if-specific-or-false)
  (let ((class-if-specific?
	  (and (evaluation-symbol-p class-if-specific-or-false)
	       (evaluation-symbol-symbol class-if-specific-or-false)))
	(slot-name (prog1 (evaluation-symbol-symbol slot-name-ev)
		     (reclaim-evaluation-value slot-name-ev))))
    (reclaim-if-evaluation-value class-if-specific-or-false)
    (reclaim-evaluation-value slot-name-ev)
    (let* ((slot-description
	     (get-slot-description-of-frame
	       (or (get-slot-name-for-alias-if-any slot-name frame)
		   slot-name)
	       frame class-if-specific?))
	   (slot-type?
	     (and slot-description
		  (feature-assq 'type (slot-features slot-description)))))
      (unless slot-description
	(stack-error cached-top-of-stack "bogus slot name ~a" slot-name))
      (when slot-type?
	(let* ((evaluator-info
		 (get-slot-description-evaluator-info slot-description))
	       (getter? (evaluator-slot-info-category-getter evaluator-info)))
	  (when getter?
	    (values
	      (multiple-value-bind (extracted-value reclaim-p)
		  (funcall-simple-multi-valued-compiled-function
		    (evaluator-slot-info-category-extracter evaluator-info)
		    (get-slot-description-value frame slot-description)
		    evaluator-info)
		(prog1 (call-category-getter-fn
			 getter?
			 extracted-value	   
			 frame slot-description)
		  (when reclaim-p
		    (reclaim-slot-value extracted-value)))))))))))





;;;; Additional Run-Time Facilities for Attribute Export



;;; `simple-commit-parse-result' is an internal function that does what
;;; try-to-end-editing has always done, without getting the parse and editor
;;; involved.


(defun simple-commit-parse-result
    (frame slot-name defining-class? slot-description slot-component-name?
	   slot-component-indicator? category? text-type-slot-p
	   parse-result
	   editing-for-runtime-change-p
	   evaluation-value)
  (declare (ignore text-type-slot-p))
  (let ((reason-not-editable?
	  (reason-permanent-items-attribute-is-not-editable frame slot-name defining-class? slot-description)))
    (when reason-not-editable?
      (return-from simple-commit-parse-result
	(tformat-text-string "Cannot edit ~NF, because ~A.  See the saving-parameters."
			     frame reason-not-editable?))))
  (let ((slot-value-compiler? (slot-value-compiler category?)))
    (multiple-value-bind (new-value-or-bad-phrase explanatory-text-string-if-bad-phrase?)
	(if (or (null slot-value-compiler?)
		(eq parse-result bad-phrase))
	    parse-result
	    (with-backtrace-for-internal-error
		(compile
		  (push-backtrace-information slot-name) ; defining-class?
		  twrite-edit-backtrace-info)
	      (funcall-compiled-function
		slot-value-compiler?
		parse-result
		frame
		slot-name
		defining-class?
		slot-component-name?
		(and slot-component-name?
		     (get-slot-component-group
		       frame slot-name
		       slot-component-indicator?)))))
      (cond
	((eq new-value-or-bad-phrase bad-phrase)
	 explanatory-text-string-if-bad-phrase?)
	(t
	 (let* ((evaluator-info
		 (get-slot-description-evaluator-info slot-description))
		(new-value
		 (funcall-compiled-function
		   (evaluator-slot-info-category-committer evaluator-info)
		   (copy-for-slot-value new-value-or-bad-phrase)
		   evaluation-value
		   evaluator-info))
		(do-not-note-permanent-changes-p
		  (or do-not-note-permanent-changes-p editing-for-runtime-change-p)))
	   (when editing-for-runtime-change-p
	     (note-kb-state-change-to-slot-by-saving-text
	       frame slot-description))
	   (change-slot-description-value
	     frame slot-description new-value
	     slot-component-name? slot-component-indicator?)
	   nil)))))) ; indicates no problems

;      (cond
;	((and (eq new-value-or-bad-phrase bad-phrase)
;	      (or (not text-type-slot-p)
;		  (not (feature-assq
;			 'allow-text-slot-to-have-no-value
;			 (if slot-component-name?
;			     (get-slot-component-features
;			       slot-name defining-class? slot-component-name?)
;			     (slot-features slot-description))))))
;	 (unless (eq parse-result bad-phrase)
;	   (let ((problem-string
;		   (tformat-text-string
;		     (if explanatory-text-string-if-bad-phrase?
;			 (prog1 "This is uncompilable.  ~A"
;			   (reclaim-text-string explanatory-text-string-if-bad-phrase?))
;			 "This is uncompilable")
;		     explanatory-text-string-if-bad-phrase?)))
;	     (handle-parsing-or-compilation-problem problem-string)
;	     (reclaim-text-string problem-string))))
;	(t
;	 (let ((new-value
;		 (if (eq new-value-or-bad-phrase bad-phrase)
;		     no-value
;		     (copy-for-slot-value new-value-or-bad-phrase))))
;	   (when editing-for-runtime-change-p
;	     (note-kb-state-change-to-slot-by-saving-text
;	       frame slot-description))
;	   (change-slot-value
;	     frame slot-name new-value
;	     defining-class? slot-component-name? slot-component-indicator?)))))))

(defun text-slot-value-to-evaluation-text (frame slot-value type-of-slot)
  (let* ((text (make-text-representation-for-slot-value-itself
		 frame slot-value type-of-slot))
	 (evaluation-text
	   (convert-text-to-text-string text)))
    (reclaim-text text)
    evaluation-text))

;;; `parse-text-string' is a simple interface to the parser. It must called
;;; inside with-phase-conses or the equivalent.  It returns two values
;;; (like most other parsing functions).  The first is or parse-result tree
;;; or bad-phrase.  The second is an optional error-string?.

(defun parse-text-string (text-string category &optional (frame-being-edited? nil))
  (let* ((previous-edit-state current-edit-state)
	 (type-of-slot (gensym-list 'type category))
	 (string-to-parse
	   (tformat-text-string "~a " text-string))
	 (parsing-context (create-parsing-context nil nil type-of-slot))
	 (parse-result bad-phrase)
	 (parse-result-error-string? nil)
	 (keep-edit-workspace-hidden-no-matter-what? t))
    (setf (frame-being-edited? parsing-context) frame-being-edited?)
    (multiple-value-bind (parse-status error-string?)
	(advance-parsing-context parsing-context string-to-parse)
      (cond
	((eq parse-status 'parsing-context-complete-status)
	 (within-parsing-context (parsing-context)
	   (let ((parse-trees
		   (loop as incomplete-phrase
			    in (parsing-token-incomplete-phrases
				 (parsing-token-previous
				   (parsing-context-cursor-token parsing-context)))
			 when (eq (phrase-rule-completions incomplete-phrase)
				  (phrase-rule-completions-past-instance-of-category
				    parsing-context))
			   collect
			   (car (incomplete-stack-of-constituents incomplete-phrase))
			     using phrase-cons)))
	     (cond ((null parse-trees)
		    (setf parse-result-error-string?
			  (
			   copy-constant-wide-string #w"incomplete phrase"
			   )))
		   ((null (cdr parse-trees))
		    (setf parse-result
			  (let ((current-edit-state previous-edit-state))
			    (copy-for-phrase (car parse-trees)))))
		   (t
		    (setf parse-result-error-string? "ambiguous-phrase"))))))
	((null error-string?)
	 (setf parse-result-error-string? (
	                                   copy-constant-wide-string #w"incomplete phrase"
	                                   )))
	(t
	 (setf parse-result-error-string? error-string?))))
    (delete-parsing-context parsing-context)
    (reclaim-gensym-list type-of-slot)
    (values parse-result parse-result-error-string?)))





;;;; Evaluation Value Interface to Grammar Categories




;;; Grammar categories are the main interface for G2 users to attribute values
;;; within G2.  They provide an interface between textual representations and
;;; values of slots.  The grammar category interpreters provide an interface
;;; between slot values produced by particular grammar categories and evaluation
;;; values.  On the getter side, they are given a slot value that was produced
;;; by a particular grammar category and should return an evaluation value.  On
;;; the setter side, they are given an evaluation value and should produce what
;;; the grammar rules produce (i.e. a phrase-value) before the slot value
;;; compilers are called.

;;; This segment of code implements stack-evaluator interface to these facilities.

;;; The function `get-category-interpreted-attribute' takes a block and a
;;; component particulars of a ...

;;; The funciton `set-category-interpreted-attribute' takes a block, a
;;; component-particulars, and a new value...







;;;; System Procedures for fetching attribute information




;;; The procedures are used to get information about attribute type descriptions
;;; for a class or to get the values of the attributes for an instance as either
;;; evaluation-values or text. There are additional procedures that can be used
;;; as filters to limit the attributes according to various criteria.


(defmacro evaluation-value-in-sequence-p (search-value sequence)
  `(loop for value being each evaluation-sequence-element of ,sequence
	thereis (evaluation-value-equal-p ,search-value value)))

;;; g2-get-attribute-descriptions-of-class takes a symbol naming a class and a
;;; sequence of symbols naming attributes (possibly empty) and returns the
;;; attribute-descriptions of these attributes (or all attributes) as a sequence.

(defun-for-system-procedure g2-get-attribute-descriptions-of-class (class-name specific-attributes)
  (unless (class-description class-name)
    (stack-error cached-top-of-stack
		   "There is no class named ~a."
		   class-name))
  (unless (type-specification-type-p specific-attributes '(sequence symbol))
    (stack-error cached-top-of-stack "Specific Attributes must be a sequence of symbols"))
  (loop with all-attributes-p
	  = (=f (evaluation-sequence-length specific-attributes) 0)
	with name-and-description-alist
	  = (get-list-of-all-user-visible-attributes (class-description class-name))
	for (name . slot) in name-and-description-alist
	when (or all-attributes-p (evaluation-value-in-sequence-p name specific-attributes))
	collect (generate-description-of-attribute class-name
		  name slot (class-description class-name) nil 'administrator nil)
	into struct-list using eval-cons
	finally
	  (reclaim-eval-alist name-and-description-alist)
	  (reclaim-evaluation-value specific-attributes)
	  (return (allocate-evaluation-sequence struct-list))))

(define-system-rpc-access (g2-get-attribute-descriptions-of-class ((sequence)))
    ((class symbol)
     (specific-attributes (sequence)))
  (g2-get-attribute-descriptions-of-class class specific-attributes))


;;; g2-get-attribute-values-of-item returns the values of those attributes of
;;; the frame named in the specific-attributes sequence as a structure. If
;;; an empty sequence is passed in, all attributes with values are included.

(defun-for-system-procedure g2-get-attribute-values-of-item (frame specific-attributes)
  (let* ((class-description (class-description-slot frame))
	 (name-and-description-alist (get-list-of-all-user-visible-attributes class-description)))
    (unless (type-specification-type-p specific-attributes '(sequence symbol))
      (stack-error cached-top-of-stack "Specific Attributes must be a sequence of symbols"))
    (loop for (name . slot-description-or-virtual-attribute) in name-and-description-alist
	  with all-attributes-p = (=f (evaluation-sequence-length specific-attributes) 0)
	  as want-attribute-p = (or all-attributes-p
				  (evaluation-value-in-sequence-p name specific-attributes))
	  as attribute-value? = (and want-attribute-p
				     (get-attribute-description-evaluation-value
				       frame slot-description-or-virtual-attribute))
	  when attribute-value? 
	    collect name into attribute-names-and-values using eval-cons
	    and
	    collect attribute-value? into attribute-names-and-values using eval-cons
	  finally
	    (reclaim-eval-alist name-and-description-alist)
	    (reclaim-evaluation-value specific-attributes)
	    (return (allocate-evaluation-structure attribute-names-and-values)))))

(define-system-rpc-access (g2-get-attribute-values-of-item ((structure)))
    ((item (class item))
     (specific-attributes datum))
  (g2-get-attribute-values-of-item item specific-attributes))

;;; g2-get-attribute-texts-of-item is essentially the same as g2-get-attribute-values-of-item
;;; except that it returns the attribute value as text.

(defun-for-system-procedure g2-get-attribute-texts-of-item (frame specific-attributes)
  (let* ((class-description (class-description-slot frame))
	 (name-and-description-alist (get-list-of-all-user-visible-attributes class-description)))
    (unless (type-specification-type-p specific-attributes '(sequence symbol))
      (stack-error cached-top-of-stack "Specific Attributes must be a sequence of symbols"))
    (loop for (name . slot-description-or-virtual-attribute) in name-and-description-alist
	  with all-attributes-p = (=f (evaluation-sequence-length specific-attributes) 0)
	  as want-attribute-p = (or all-attributes-p
				    (evaluation-value-in-sequence-p name specific-attributes))
	  as attribute-text-value? = (and want-attribute-p
					  (serve-text-of-attribute frame name nil))
	  when attribute-text-value?
	    collect name into attribute-names-and-values using eval-cons
	    and
	    collect attribute-text-value? into attribute-names-and-values using eval-cons
	  finally
	    (reclaim-eval-alist name-and-description-alist)
	    (reclaim-evaluation-value specific-attributes)
	    (return (allocate-evaluation-structure attribute-names-and-values)))))

(define-system-rpc-access (g2-get-attribute-texts-of-item ((structure)))
    ((item (class item))
     (specific-attributes datum))
  (g2-get-attribute-texts-of-item item specific-attributes))

(defun-for-system-procedure g2-get-denoted-attribute-texts (frame
							     denoted-attributes-sequence)
  (loop for denoted-attribute
	    being each evaluation-sequence-element of denoted-attributes-sequence
	as name = (evaluation-structure-slot denoted-attribute 'name)
	as class-qualifier? = (evaluation-structure-slot denoted-attribute
							 'class-qualifier)
	collect (serve-text-of-attribute frame name class-qualifier?)
	  into texts using eval-cons
	finally
	  (reclaim-evaluation-value denoted-attributes-sequence)
	  (return (allocate-evaluation-sequence texts))))

(define-system-rpc-access (g2-get-denoted-attribute-texts ((sequence)))
    ((item (class item))
     (denoted-attributes-sequence (sequence)))
  (g2-get-denoted-attribute-texts item denoted-attributes-sequence))


;;; g2-get-attributes-visible-in-mode is a public filter that can be used to determine
;;; the visibility of attributes of any class or a particular frame (based on user
;;; restrictions). This is primarily for UI purposes.

(defun-for-system-procedure g2-get-attributes-visible-in-mode (class-or-item user-mode)
  (unless (or (symbolp class-or-item)
	      (framep class-or-item))
    (stack-error cached-top-of-stack
		 "The first argument to g2-get-attributes-visible-in-mode must be a symbol or an item."))
  (let ((class-description (if (symbolp class-or-item)
			       (class-description class-or-item)
			       (class-description-slot class-or-item))))
    (unless class-description
      (stack-error cached-top-of-stack
		   "There is no class named ~a."
		   class-or-item))
    (loop with name-and-description-alist
	    = (get-list-of-all-user-visible-attributes class-description)
	  ;; = (get-list-of-all-user-visible-attributes-specifying-deprecation
	  ;; class-description t)  ;; jv
	  for (name . slot-description-or-virtual-attribute) in name-and-description-alist
	  when				; either virtual attribute or visible slot
	    (and (or (virtual-attribute-p slot-description-or-virtual-attribute)
		     (if (framep class-or-item)
			 (let* ((frame class-or-item)
				(slot-description slot-description-or-virtual-attribute)
				(defining-class-name (defining-class slot-description))
				(aliased-slot-name (if (slot-name-needs-qualification-p
							 slot-description
							 class-description)
						       (unique-slot-name slot-description)
						       (alias-slot-name-if-necessary
							 (pretty-slot-name slot-description)
							 defining-class-name))))
			   (include-slot-in-attribute-table-for-mode-p
			     frame aliased-slot-name defining-class-name user-mode))
			 t))			; No filter when looking up visibility from class
		 (not (memq name attribute-names))
		 ;; 6.0 miscellaneous slot determines UUID visibility:
		 (or (not (eq name 'uuid))
		     (and (boundp 'miscellaneous-parameters) ; perhaps overkill?
			  miscellaneous-parameters ; ditto.
			  (get-slot-value	; fwd. ref.
			    miscellaneous-parameters
			    'show-uuids-in-attribute-tables))))
	  collect name into attribute-names using eval-cons
	  finally
	    (reclaim-eval-alist name-and-description-alist)
	    (return (allocate-evaluation-sequence attribute-names)))))

(define-system-rpc-access (g2-get-attributes-visible-in-mode ((sequence)))
    ((class-or-item item-or-datum)
     (user-mode symbol))
  (g2-get-attributes-visible-in-mode class-or-item user-mode))



;;; Private System Procedures

;;; These filters are private because we have not decided on the spec to be
;;; made public. At some point, after reasonable design/usability review,
;;; we can settle on something that everybody can use.
;;; The current implementation is that you pass in a set of filter flags
;;; as a structure. The attributes of the structure determine which flags
;;; are set.

(defun-for-system-procedure g2-get-filtered-attributes (frame filter-flags)
  (let* ((class-description (class-description-slot frame))
	 (filter filter-flags)
	 (attributes-alist (get-list-of-all-user-visible-attributes class-description)))
    (loop for (name . slot-description-or-virtual-attribute) in attributes-alist
	  when (slot-passes-filter-p slot-description-or-virtual-attribute filter)
	  as attribute-value = (get-attribute-description-evaluation-value frame slot-description-or-virtual-attribute)
	  when attribute-value
	    collect name into attribute-names using eval-cons 
	  finally
	    (reclaim-eval-alist attributes-alist)
	    (return (allocate-evaluation-sequence attribute-names)))))


(defun slot-passes-filter-p (slot-description filter)
  (declare (ignore slot-description filter))
  t)
; touch here to recompile.

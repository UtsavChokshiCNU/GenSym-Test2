;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module FRAMES1

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Lowell B. Hawkinson, Stephen R. DeVoy, and Gretchen Wang








;;;; Forward References




(declare-forward-references-to-module
  frames2
  get-slot-name-for-alias-if-any
  reclaim-slot-value
  copy-for-slot-value
  get-slot-description)

(declare-forward-references-to-module
  kb-load2
  (loading-kb-p variable))

#+java-export-facilities
(declare-forward-references-to-module
  java3
  reclaim-class-export-information-if-any)








;;;; Classes



;;; A `class' is a kind of item which is defined by def-class when it is a
;;; system class (except for root, the root class) or is defined by
;;; define-user-class

;;; Classes exist so that frames may be created and/or that other classes may be
;;; defined.  All classes, with the exception of root, have one or more direct
;;; superior classes.  A class is a direct superior of class C when it is
;;; explicitly designated as a superior class in the definition for C.  A class
;;; is a superclass of another class C when it is either a direct superior class
;;; of C or it is the root class or it is a class that lies between the root
;;; class and a direct superior class of C on the directed acyclic graph of the
;;; class hierarchy.  Functionally, a class inherits properties from its set of
;;; superclasses.  A class is an inferior class of class C when it inherits
;;; properties from C.  The set of subclasses for class C consists of all the
;;; inferior classes of C and C itself.  Even though a class is a subclass of
;;; itself, it is not a superclass of itself.

;;; Each class has a class inheritance path which is an ordered list of the
;;; class itself and all of its superclasses.  The classes are ordered from
;;; most-specific (the class itself) to least-specific (the root class).
;;; The class inheritance path is a linearization of all of the paths from the
;;; class to the root class on the directed acyclic graph of the class
;;; hierarchy.  The G2 linearization scheme is a variant of the linearization
;;; scheme of CLOS. 

;;; Classes also have slot definitions, method definitions, and, optionally,
;;; predicates.  These properties of classes are discussed in their code
;;; sections.









;;;; Frames and slots



;;; Creating an instance of a class has been described as the process of making
;;; a frame, but it might be more accurate in G2 to describe instantiation as
;;; the process of making two frames, or two structures with named components or
;;; slots.  The frame lengths, slot accessors, and the initial slot values of
;;; these two structures are determined by the slot descriptions component of
;;; the class description for the class being instantiated.  The resulting
;;; instance object is an instance of the class and all the direct and indirect
;;; superior classes of this class.

;;; System-defined slots defined for a class overshadow (or override) same-named
;;; system-defined slots defined for any superclass of class.  This means that a
;;; class description will contain only one slot definition for a system-defined
;;; slot with a particular slot name.  In contrast, user-defined slots
;;; (frequently referred to as "attributes") are merged.  A class description
;;; for a class will have a slot definition for all of the user-defined slots
;;; defined specifically for the class and for all of the user-defined slots
;;; defined for its superclasses whether the slot names conflict or not.  An
;;; instance of a class contains memory locations for instance-specific values
;;; for all the slot defintions in the class description for its class.

;;; In instances of system-defined classes there are two different slot
;;; implementations: vector slots and lookup slots.  The vector slot values are
;;; the components of the "main" frame structure allocated by make-frame.
;;; Make-frame also allocates a "lookup structure" frame and stores a pointer to
;;; it in the lookup-structure slot of the main frame.  All of the vector slots
;;; have a slot-value slot on the main vector, but the lookup-structure frame
;;; only contains the values of non-default-valued lookup slots.  The values of
;;; default-valued lookup slots are available in the slot-init-form slots of the
;;; slot descriptions.  A pointer to the class description is stored in the
;;; class-description-slot component of the main frame.

;;; At the time of system class definition, accessor functions are defined for
;;; system-defined slots, and this imposes an ordering of vector slots on the
;;; hierarchy of system-defined classes.  If an instance of a system-defined
;;; class has a vector slot named frame-flags and frame-flags is the fourth
;;; vector slot on the main frame, then the frame-flags slots of all the other
;;; system-defined instances in G2, regardless of class, must have frame-flags
;;; as the fourth vector slot.  This problem does not arise with other slot
;;; implementations.

;;; Instances of user-defined classes have three implementations of slots: user
;;; vector slots as well as the vector slots and lookup slots for inherited
;;; system-defined slots.  The lower-indexed portion of the lookup structure has
;;; a slot value for each of the user-defined attributes whether the value is
;;; default or non-default; the higher-indexed portion of the lookup structure
;;; contains the lookup slot values.









;;; Evaluation of Slot Init Forms

;;; Slot init forms of the form (:FUNCALL-AT-LOAD-TIME function .  args) are
;;; evaluated at load time (and compile time), i.e., during the evaluation of a
;;; def-class.  The slot's default initialization value will then become the
;;; resultant value.

;;; Slot init forms of the form (:FUNCALL function . args) are evaluated at frame
;;; instantiation time.

;;; No other form of slot init form is evaluated.  Such a "datum" itself becomes
;;; the default initialization of the slot of the frame.









;;;; Frame Conses



;;; `Frame conses' are used to make up all of the non-permanent list structure in the
;;; frame system. The standard suite of consing functions and variables, as defined in
;;; the subsection "Defining Consers" in module UTILITIES, are defined with the root
;;; name "FRAME".

(defconser frame frames1)





;;; `Class-description conses' is a memory pool currently dedicated to managing the
;;; memory for these components of the class-description structure constructed for
;;; user-defined classes:  the class-inheritance-path list; the slot-value components of
;;; slot-descriptions and the list conses in a list of slot descriptions (the memory
;;; for the slot description structures comes from a separate memory pool); the slots-
;;; local-to-class list; the class
;;; features tree.

;; The final argument to this macro will keep this pool separate from the general
;; gensym-cons pool in distribution images.

(defconser class-description frames1 nil t)




;;;; No-Value

;; Change to "no-translation"!



;;; `No-value' is a unique value used as a slot value to represent the absence of a value.

(defvar no-value (list 'no-value))



;;; `No-value-p' returns t when its argument is not eq to the unique list no-value
;;; otherwise it returns nil.

(defmacro no-value-p (something)
  `(eq ,something no-value))

  




;;;; Global Properties



;;; `Class-methods' is a global property of all classes which holds a list
;;; of all methods which are applicable to the class on which it sits.

(def-global-property-name class-methods)



;;; `Classes-which-define' is a global property of all methods which holds a
;;; list of all classes for which there exists a definition of the method.

(def-global-property-name classes-which-define)	; a frame list








;;;; Knowledge Base Specific Properties



;;; `Slot-name-assigment' is a property of all system-defined slot names.      
;;; The slot-name assigment of a slot name is either a nonnegative integer or nil.
;;; If the slot name assignment of a slot name is nil, the slot named is a lookup
;;; slot.  If the slot name assignment of a slot name is a nonnegative integer,
;;; the integer is the (main) frame vector index by which the slot may be accessed.

(def-global-or-kb-specific-property-name slot-name-assignment nil)
(def-global-or-kb-specific-property-name old-slot-name-assignment nil)


;;; `Class-description' is a property of all classes on which sits the compiled
;;; class description for the class.

(def-global-or-kb-specific-property-name class-description copy-class-description)
(def-kb-specific-property-name old-class-description nil)

(defun reclaim-class-description-list-function (list)
  (reclaim-class-description-list list))

;;; `Direct-superior-classes' is a property of all classes.  The value
;;; associated with this property is an ordered list of classes which determines
;;; the properties a class will inherit.

(def-global-or-kb-specific-property-name direct-superior-classes
    copy-list-using-class-description-conses-function
  nil reclaim-class-description-list-function)

;;; `Inferior-classes' is the property of a class which holds the classes which
;;; have been defined to inherit from said class.

(defun copy-list-using-class-description-conses-function (list)
  (copy-list-using-class-description-conses list))

(def-global-or-kb-specific-property-name inferior-classes
    copy-list-using-class-description-conses-function
  nil reclaim-class-description-list-function)




;;; Each class has the property class-definition which is the form used most
;;; recently to define the class. The class definition of the root class is
;;; intended to be permament. Redefinition of the root class is undefined and
;;; is likely to lead to instability.

(def-global-or-kb-specific-property-name class-definition)




;;; Before a class redefines itself it checks to see whether the 'definition-
;;; state' of its direct superior classes is defined, if it is and the
;;; definition of the class is unchanged, then there is no need to redefine the
;;; class, otherwise the the class is redefined.

(def-global-or-kb-specific-property-name definition-state)







;;; Macros for this Package

;;; Error Message Macros ... Note that these are all substitution macros.  Note
;;; also that the only reason these are all macros is so that the function where
;;; the problem occurred will show up in the error message, rather than some
;;; function that was called in order to signal error.

;;; Note that all the error message macros call the Common Lisp lisp function
;;; error, so it can be assumed that execution does not continue past the call
;;; to the error message macro.

(def-substitution-macro warn-of-invalid-slot-init-form
			(slot-init-form slot-definition)
  (error "~S, the slot init form of ~S, is an invalid slot initialization."
	  slot-init-form slot-definition))



(def-substitution-macro warn-of-invalid-slot-definition (slot-definition)
  (error "~S is an invalid slot definition." slot-definition))



(def-substitution-macro warn-of-invalid-slot-name (pretty-slot-name)
  (error "~S is an invalid slot name." pretty-slot-name))



(def-substitution-macro warn-of-missing-lookup-slot
    (lookup-pretty-slot-name frame)
  (error "Frame ~A has no ~A slot" frame lookup-pretty-slot-name))



(def-substitution-macro warn-of-attempt-to-set-an-invalid-slot (frame slot)
  (error "An attempt was made to set the slot ~S of ~S which has no ~S slot."
	 slot frame slot))



(def-substitution-macro warn-of-attempt-to-get-an-invalid-slot (frame slot)
  (error "An attempt was made to get the slot ~S of ~S which has no ~S slot."
	 slot frame slot))



(def-substitution-macro warn-of-invalid-frame-method-association (frame method)
  (error "Frames of type ~A have no ~A method."
	 frame method))



(def-substitution-macro warn-of-attempt-to-redefine-the-type-of-a-slot (slot new-type)
  (error "An attempt was made to redefine type of slot ~A to ~A."
	  slot new-type))








;;;; Unique Slot Names for Slot Descriptions










;;; A class has only one system-defined slot with a particular name.
;;; System-defined slots are said to override because when a system-defined slot
;;; is defined for more than one of the classes on the class inheritance path
;;; for class C, class C will have only the most specific of those slots.  The
;;; most specific of a group of slots with the same name is the slot that is
;;; defined for the class that is closest to class C on the class inheritance
;;; path for class C, including class C itself.

;;; User-defined slots do not override.  Class C will contain the union of all
;;; of the user-defined slots defined for all of the user-defined classes on the
;;; class inheritance path for Class C.

;;; Because there is code in G2 that relies on the slot-name of a slot
;;; description being unique, the unique-slot-name component of user-defined
;;; slot descriptions will be a unique symbol interned in the keyword package,
;;; and the unique-slot-name component of a system-defined slot description will
;;; be the slot-name symbol from the def-class form.

(defun-substitution-macro make-unique-slot-name-symbol-text-string (defining-class pretty-slot-name)
  (tformat-text-string "~A::~A" defining-class pretty-slot-name))

(defun-substitution-macro intern-unique-slot-name-text-string (text-string)
  (intern-text-string text-string keyword-package-1))

(defun-simple make-unique-slot-name-symbol
    (defining-class pretty-slot-name)
  (intern-unique-slot-name-text-string
    (make-unique-slot-name-symbol-text-string defining-class pretty-slot-name)))

(defun decompose-class-qualified-symbol-1 (symbol)
  (let* ((print-name (symbol-name-text-string symbol))
	 (print-name-length (text-string-length print-name))
	 (separator-position (position-in-text-string #.%\: print-name))
	 (class-string (obtain-simple-text-string separator-position))
	 (name-string-length (-f print-name-length separator-position 2))
	 (name-string (obtain-simple-text-string name-string-length)))
    (loop for index fixnum from 0 below separator-position
	  do
      (setf (charw class-string index) (charw print-name index)))
    (loop for index1 fixnum from (+f separator-position 2)
		     below print-name-length
	  for index2 fixnum from 0 below name-string-length
	  do
      (setf (charw name-string index2) (charw print-name index1)))
    (let ((class-symbol (intern-text-string class-string))
	  (name-symbol (intern-text-string name-string)))
      (gensym-cons class-symbol name-symbol))))

(def-global-property-name decomposed-class-qualified-symbol)

(defun decompose-class-qualified-symbol (symbol)
  (let ((info (or (decomposed-class-qualified-symbol symbol)
		  (setf (decomposed-class-qualified-symbol symbol)
			(decompose-class-qualified-symbol-1 symbol)))))
    (values (car info) (cdr info))))







;;;; Slot Descriptions




;; The following three forms are used for finding slot-description
;; memory leaks.  Slot-descriptions are frame-consed into the
;; unreclaimed-slot-descriptions list in make-slot-description when
;; *there-is-a-current-kb?* and debugging-slot-description-leaks? are both
;; true.  They are removed from the list in delete-attribute-from-
;; user-class and reclaim-slot-descriptions-of-class-description when 
;; debugging-slot-description-leaks? is true.

#+development
(defparameter debugging-slot-description-leaks? nil)

#+development
(def-system-variable unreclaimed-slot-descriptions frames1 nil)

#+development
(defun-void delete-slot-description-from-unreclaimed-list (slot-description)
  (cond ((eq slot-description (car unreclaimed-slot-descriptions))
	 (reclaim-frame-cons 
	   (prog1 unreclaimed-slot-descriptions
		  (setf unreclaimed-slot-descriptions 
			(cdr unreclaimed-slot-descriptions)))))
	(t
	 (loop for sublist on unreclaimed-slot-descriptions
	       do
	   (when (eq slot-description (cadr sublist))
	     (reclaim-frame-cons 
	       (prog1 
		 (cdr sublist) 
		 (setf (cdr sublist) (cddr sublist))))
	     (loop-finish))))))




;;; A `slot-description' is a structure which describes a slot of a class.  Each
;;; slot-description has eight slots accessed by these accessor functions:
;;; unique-slot-name, pretty-slot-name, defining-class, slot-type-specification,
;;; slot-init-form, vector-slot-index?, user-vector-slot-index?, and
;;; slot-features.  The slot-descriptions component of the class-description is
;;; a list of these structurized slot-descriptions.

;;; Because a class can have more than one user-defined slot with the same slot
;;; name, the unique-slot-name component for user-defined slots is a unique
;;; symbol which is interned in the keyword package.

;;; Vector-slot-index?  will return a non-negative integer when the slot is
;;; implemented as a vector slot; otherwise it will return nil.
;;; User-vector-slot-index?  will return a non-negative integer when the slot is
;;; implemented as a user vector slot; otherwise it will return nil.
;;; If both vector-slot-index? and user-vector-slot-index? are nil, the slot is
;;; implemented as a lookup slot.
 
(def-structure (slot-description (:constructor make-slot-description-internal ())
				 #+development (:print-function print-slot-description))  
  (unique-slot-name nil)
  (pretty-slot-name nil)
  (defining-class nil)
  (owner-class nil)
  (slot-type-specification nil :reclaimer reclaim-class-description-tree)
  ;; The slot-init-form must be dealt with on a case by case basis at slot-description
  ;; reclamation time.  It can be class-description conses or a icon-description
  ;; structure.
  (slot-init-form nil)
  (vector-slot-index? nil)
  (user-vector-slot-index? nil)
  ;; Make a new defconser for class-conses and use that instead?  -jra 1/5/93
  (slot-features nil :reclaimer reclaim-class-description-tree)
  (slot-description-evaluator-info? nil :reclaimer reclaim-if-evaluator-slot-info) ; allows for big optimizations jed 10/31/96
  (slot-description-cached-reclaimer? nil)
  (cached-user-vector-slot-location-differs-in-subclass-p nil)
  (timestamp-for-cached-user-vector-slot-location-differs-in-subclass-p nil)
  (slot-description-for-namelike-slot-p nil))   ; new. derived from slot-features in 
                                                ;   make-slot-description. (MHD 5/14/00)

#+development
(defun print-slot-description (slot-description stream depth)
  (declare (ignore depth))
  (printing-random-object (slot-description stream)
    (format stream
	    "~(~s~) slot-description"
	    (unique-slot-name slot-description))))




;;; `System-defined-slot-description-p' is true when the slot-description has
;;; a null user-vector-slot-index? component.

(defmacro system-defined-slot-description-p (slot-description)
  `(null (user-vector-slot-index? ,slot-description)))

;;; `User-defined-slot-description-p' is true when the slot-description has
;;; a non-null user-vector-slot-index? component.

(defmacro user-defined-slot-description-p (slot-description)
  `(user-vector-slot-index? ,slot-description))



;;; Cannot use skip list here. --binghe
(def-binary-tree slot-hash
    :hash-function sxhash-symbol
    :constructor make-slot-hash
    :reclaimer reclaim-slot-hash)




;;; The macro `def-abbreviation-change-function' takes an unevaluated symbol as
;;; its argument.  This symbol should name a function which is called when a
;;; change has occured in slot definitions such that abbreviated slot
;;; denotations may now be invalid.  When a change occurs this function will be
;;; called with two arguments.  Both arguments are lists of 3 element lists,
;;; where the 3 element list is (<class> <pretty-slot-name> <defining-class>)
;;; which denotes a slot defined for a class.  The first argument to the
;;; abbreviation change function is a list of slots which were previously
;;; abbreviated, which now need to be unabbreviated.  So abbreviated references
;;; to the class/pretty-slot-name pairs should be changed to now include the
;;; given defining-class.  The second argument to the abbreviation change is a
;;; list of slots which were previously unabbreviated which may now be
;;; abbreviated.  So fully qualified references to the class/pretty-slot-name/
;;; defining-class triplet may now be changed to just the class/pretty-slot-name
;;; pair.  This function will be called after the slot changes have been
;;; reflected in the class description and slot description structures

;;; When a change occurs in a class hierarchy, every slot naming triplet that
;;; may be affected will be listed, not just the highest class where such a
;;; change is visible.  For example, say we have the following class hierarchy

;;;   C1 -> C2 -> C3

;;; where C1 is the most superior class and C3 the most inferior, and class C1
;;; defines a slot A.  If a slot A becomes defined on C2, then the abbreviation
;;; change functions will be called with a first argument ((c2 a c1) (c3 a c1))
;;; and a second argument of NIL.  If the slot C2::A is now deleted, then the
;;; abbreviation change functions will be called with a first argument of NIL
;;; and a second argument of ((c2 a c1) (c3 a c1)).

;;; Some background: Changes in abbreviation can occur when slots are added,
;;; removed, or renamed.  These slot changes can then require that slot
;;; denotations what were abbreviated become fully specified with the
;;; defining-class, or these changes can require that slots which were fully
;;; specified with the defining class now drop the defining class and use the
;;; abbreviated form.  It is expected that initial users of this mechanism will
;;; be tables and the code that manages the parent-attribute-name slot of
;;; blocks.

;(defvar abbreviation-change-functions nil)

;(defmacro def-abbreviation-change-function (function-name)
;  (cond ((symbolp function-name)
;         `(pushnew ',function-name abbreviation-change-functions))
;        (t
;         (warn "def-abbreviation-change-function argument ~a must be a symbol
;                naming a function."
;               function-name))))




;;; `Notify-abbreviation-change-functions' calls the functions that were
;;; registered with the above def-abbreviation-change-function macro with two
;;; arguments, abbreviation-change-additions and abbreviation-change-removals.
;;; See the documentation above for a description of these arguments.

;(defun notify-abbreviation-change-functions
;    (defining-class-qualification-additions
;        defining-class-qualification-removals)
;  (loop for abbreviation-change-function in abbreviation-change-functions
;        do
;    (funcall-symbol
;      abbreviation-change-function
;      defining-class-qualification-additions
;      defining-class-qualification-removals)))

(defvar any-cached-evaluator-slot-info-p nil)

(def-structure evaluator-slot-info
  (evaluator-slot-info-category nil)
  (evaluator-slot-info-category-setter nil)
  (evaluator-slot-info-category-getter nil)
  (evaluator-slot-info-category-committer nil)
  (evaluator-slot-info-category-extracter nil)
  (evaluator-slot-info-text-slot-p nil)
  (evaluator-slot-info-virtual-attribute nil))

(defun reclaim-if-evaluator-slot-info (evaluator-slot-info?)
  (when evaluator-slot-info?
    (reclaim-evaluator-slot-info evaluator-slot-info?)))




;;;; Class Descriptions



;;; A `class-description' is a structure which describes a class and sits on the
;;; kb-specific property by the same name of a class.

;;; A class description is of the form:

;;; <class-name-of-class-description> is the class symbol the class description
;;; describes.

;;; <class inheritance path> is an ordered list of classes that is used to
;;; determine what slots and methods have precedence for a particular class.
;;; The first element on the list is the class itself, followed by the superior
;;; class whose properties have the greatest inherited precedence for class,
;;; followed by the superior class that has the next inherited precedence for
;;; class, and so on, with the root class being the last element on the list.
;;; Given a class description, `class-inheritance-path' will access this list.

;;; <class vector length> is the length of the main vector which represents an
;;; instance of the class.  The class vector length is exactly equal to the
;;; number of vector slots of the class, including those which are inherited.
;;; Given a class description, `class-vector-length' accesses this integer.

;;; <class feature> can be, for example, define-predicate, not-user-instantiable,
;;; and (foundation-class object).  Given a class description, 'class-features' will
;;; access a list of class features.

;;; <slot description> is described below.  Given a class description, 'slot-
;;; descriptions' will access a list of slot descriptions.

;;; <class is subclass of item?> is t when class is a subclass of item.  Because
;;; this determination is made so often, this component is accessed instead of
;;; using the class bit number/vector method of determining subclass/superclass
;;; relations.  Given a class description, 'class-is-subclass-of-item?' will
;;; access the value of class is subclass of item?.

;;; <class user vector length> is the number of user-defined attributes for the
;;; class.  Because the values of the user-defined attributes reside on the
;;; lower-indexed portion of the lookup-structure, the class user vector length
;;; is an index into the first lookup-slot name/value pair.  Given a class
;;; description, 'class-user-vector-lenth' accesses the class user vector
;;; length.

;;; <slots local to class> is a list of the unique names of slots that are
;;; defined specifically for the class (correspond to the attributes in the
;;; class-specific- attributes slot of its definition), instead of being
;;; inherited from the superiors of class.  Given a class description,
;;; 'slots-local-to-class' will acesss the slot names of the slots local to
;;; class.

;;; <inherited slots this class overrides> is a list of the unique names of
;;; slots that the class overrides.  System slots that have a class-slot-
;;; description-updater are included in this list because unshared class-level
;;; slot-description is allocated for each applicable class.

;;; <slot descriptions hash table> is a hash table of slot names to slot
;;; descriptions for all the slot-descriptions that defined for class and those
;;; inherited slot descriptions that have been redefined.  Given a class
;;; description 'slot-descriptions-hash-table' will access the slot
;;; descriptions hash table.

;;; <class bit number> is a unique number assigned to each class.  See <class
;;; bit vector> below for its use.  Given a class-description, 'class-bit-number'
;;; will access the class bit number.

;;; <class bit vector> for a class has its class number bit and the class
;;; number bits of all of its superior classes set to 1.  It is used to
;;; determine the superclass/subclass relation between two classes.  Given a
;;; class-description, 'class-bit-vector' will access the class bit vector.

;;; The components ending with -tbd are currently place holders only.

(def-structure (class-description
		 (:constructor make-class-description-internal ())
                 #+development
		 (:print-function print-class-description))
  (class-name-of-class-description nil)

  ;; Subtype lattice.
  ;; A list of class symbols, using class-description conses.
  (class-inheritance-path-internal
    nil :reclaimer reclaim-class-description-list)
  ;; A list of class-descriptions, using class-description conses.
  (class-description-inheritance-path-internal
    nil :reclaimer reclaim-class-description-list)
  
  ;; The following two slots are currently unused.  
  (direct-superiors-of-class-description-tbd nil)
  (direct-inferiors-of-class-description-tbd nil)

  ;; Slots.
  ;; Reclaim-slot-descriptions-of-class-description reclaims slot-descriptions.
  (slot-descriptions-internal nil :reclaimer reclaim-class-description-list)

  ;; Slots-local-to-class is a list of unique slot names.
  (slots-local-to-class nil :reclaimer reclaim-class-description-list)

  ;; Slots-this-class-overrides is a list of unique slot-names.  The list will
  ;; always be null for system-defined-classes.
  (inherited-slots-this-class-overrides
    nil :reclaimer reclaim-class-description-list)
  
  ;; See make-slot-descriptions-hash-table for a description of
  ;; the contents of this hash table.
  (slot-descriptions-hash-table nil :reclaimer reclaim-slot-hash)

  ;; Methods
  (direct-methods-of-class-description-tbd nil)
  (method-table-of-class-description nil)

  ;; Other
  (class-features-internal nil
			   :reclaimer
			   reclaim-class-description-tree)
  (class-flags-tbd 0) 
  (class-vector-length-internal nil)
  (class-user-vector-length 0)
  (class-is-subclass-of-item? nil)
  (full-hash-table-class nil)

  ;; Typep and subtypep implementation.
  (class-bit-number nil)
  (class-bit-vector nil :reclaimer reclaim-byte-vector)
  (class-description-is-system-defined-p nil)

  ;; jh, 9/18/97.  The following for memoizing when there is no user-defined
  ;; export-definition item corresonding to this class.
  #+java-export-facilities
  (implicit-class-export-information? nil
   :reclaimer reclaim-class-export-information-if-any)

  (icp-object-map-for-class-description nil)

  (class-description-change-timestamp nil)
  (class-description-subclass-change-timestamp nil))

#+development
(defun print-class-description (class-description stream depth)
  (declare (ignore depth))
  (printing-random-object (class-description stream)
    (format stream "class-description of ~a"
	  (class-name-of-class-description class-description))))




;;; The macro `system-defined-class-p' takes a symbol and returns t when
;;; that symbol names a defined class and is a system-defined class.

(def-substitution-macro system-defined-class-p (symbol)
  (and (class-description symbol)
       (consp (class-definition symbol))))



;;; The macro `class-description-has-full-hash-table-p' returns t when
;;; the slot-descriptions-hash-table of the class-description is full.
;;; For a definition of sparse and full slot-description hash tables see
;;; the documentation  for make-sparse-slot-descriptions-hash-table and make-
;;; full-slot-descriptions-hash-table below.

(defmacro class-description-has-full-hash-table-p (class-description)
  (let ((class-description-arg (gensym)))
    `(let ((,class-description-arg ,class-description))
       (eq (full-hash-table-class ,class-description-arg)
	   (class-name-of-class-description ,class-description-arg)))))




;;; The macro `superior-is-well-spaced-for-full-hash-table-p' returns t
;;; when the superior is more than two-classes removed from class on the class
;;; inheritance path for class.

(defmacro superior-is-well-spaced-for-full-hash-table-p
    (superior class-inheritance-path)
  `(>f (position ,superior ,class-inheritance-path) 1))




;;; The macro `superior-is-desirable-full-hash-table-class-p' returns t when the
;;; superior class is an inheritance merging-point class for class and is more
;;; than two-classes removed from class on the class inheritance path for class.

(defmacro superior-is-desirable-full-hash-table-class-p
    (superior class-inheritance-path)
  (let ((superior-arg (gensym))
	(class-inheritance-path-arg (gensym)))
    `(let ((,superior-arg ,superior)
	   (,class-inheritance-path-arg ,class-inheritance-path))
       (and (equal (memq ,superior-arg ,class-inheritance-path)
		   (class-inheritance-path (class-description ,superior-arg)))
	    (superior-is-well-spaced-for-full-hash-table-p
	      ,superior-arg ,class-inheritance-path-arg)))))




;;; The macro `class-description-is-user-defined-p' takes a class description
;;; and returns whether or not the described class has been defined by the user.

;;; This predicate must now rely on checking the class definition.  The pre-4.0
;;; test could rely on only user-defined classes having a foundation-class class
;;; feature.  In 4.0 both user-defined and system-defined classes have foundation-
;;; class class features.  However, there are times during class deletion that the
;;; class has a class description but not a class definition.  Therefore, this
;;; function assumes that a class with a description but no definition must be
;;; a user-defined class because the definitions of system-defined classes are
;;; never reclaimed.

(defmacro class-description-is-user-defined-p (class-description)
  `(not (class-description-is-system-defined-p ,class-description)))




;;; The macro `user-defined-class-p' takes a symbol and returns t when the
;;; symbol names a non-system-defined class.

(defmacro user-defined-class-p (symbol)
  `(let ((class-description? (class-description ,symbol)))
     (and class-description?
	  (class-description-is-user-defined-p class-description?))))




;; The following three forms are used for debugging class-description
;; memory leaks.  Classs-descriptions are frame-consed into the
;; unreclaimed-class-descriptions list in make-class-description when
;; *there-is-a-current-kb?* and debugging-class-description-leaks? are both
;; true.  They are removed from the list when they are reclaimed
;; in reclaim-class-description-of-class.

#+development
(defparameter debugging-class-description-leaks? nil)

#+development
(def-system-variable unreclaimed-class-descriptions frames1 nil)

#+development
(defun-void delete-class-description-from-unreclaimed-list (class-description)
  (cond ((eq class-description (car unreclaimed-class-descriptions))
	 (reclaim-frame-cons 
	   (prog1 unreclaimed-class-descriptions
		  (setf unreclaimed-class-descriptions 
			(cdr unreclaimed-class-descriptions)))))
	(t
	 (loop for sublist on unreclaimed-class-descriptions
	       do
	   (when (eq class-description (cadr sublist))
	     (reclaim-frame-cons 
	       (prog1 
		 (cdr sublist) 
		 (setf (cdr sublist) (cddr sublist))))
	     (loop-finish))))))




;; The following three forms are used for debugging class-description
;; method table memory leaks.  Method tables are frame-consed into the
;; unreclaimed-method-tables list in make-class-description when
;; *there-is-a-current-kb?* and debugging-class-description-leaks? are both
;; true.  They are removed from the list when they are reclaimed
;; in reclaim-class-description-of-class.

#+development
(defparameter debugging-class-description-method-table-leaks? nil)

#+development
(def-system-variable unreclaimed-class-description-method-tables frames1 nil)

#+development
(defun-void delete-class-description-method-table-from-unreclaimed-list
    (method-table)
  (cond ((eq method-table (car unreclaimed-class-description-method-tables))
	 (reclaim-frame-cons 
	   (prog1 unreclaimed-class-description-method-tables
		  (setf unreclaimed-class-description-method-tables 
			(cdr unreclaimed-class-description-method-tables)))))
	(t
	 (loop for sublist on unreclaimed-class-description-method-tables
	       do
	   (when (eq method-table (cadr sublist))
	     (reclaim-frame-cons 
	       (prog1 
		 (cdr sublist) 
		 (setf (cdr sublist) (cddr sublist))))
	     (loop-finish))))))




(defmacro handle-null-class-test (access-form)
  #-development
  access-form
  #+development
  `(if ,(second access-form)
       ,access-form
       (progn
	 (cerror "continue" "Software bug. Accessor of class-description ~s applied to NIL.~%
Please get backtrace for GHW.  You could try continuing." ',access-form)
	 nil)))

(def-substitution-macro class-inheritance-path (class-description)
  (handle-null-class-test
    (class-inheritance-path-internal class-description)))

(defun class-inheritance-path-function (class-description class-inheritance-path)
  (setf (class-inheritance-path-internal class-description)
        class-inheritance-path))

(defsetf class-inheritance-path class-inheritance-path-function)




;;; The macro `generate-class-description-inheritance-path-if-necessary'
;;; generates and sets the value of the class-description-inheritance-path-
;;; internal component of the class-description when the class-description-
;;; inheritance-path macro is evaluated and the value of the component is nil;
;;; otherwise it returns the component value which is a list of the
;;; class-descriptions of the class symbols on the class-inheritance-path.

(defmacro generate-class-description-inheritance-path-if-necessary
    (existing-class-description-inheritance-path class-description)
  (let ((existing-class-description-path-arg
	  (gensym-make-symbol "EXISTING-CLASS-DESCRIPTION-PATH-ARG"))
	(class-description-arg (gensym-make-symbol "CLASS-DESCRIPTION-ARG")))
    `(let ((,existing-class-description-path-arg
	      ,existing-class-description-inheritance-path)
	   (,class-description-arg ,class-description))
       (if (null ,existing-class-description-path-arg)
	   (setf (class-description-inheritance-path-internal ,class-description-arg)
		 (loop for class in (class-inheritance-path ,class-description-arg)
		       collect (class-description class) using class-description-cons))
	   ,existing-class-description-path-arg))))


(def-substitution-macro class-description-inheritance-path (class-description)
  (generate-class-description-inheritance-path-if-necessary
    (class-description-inheritance-path-internal class-description)
    class-description))

#+unused
(defun class-description-inheritance-path-function
    (class-description class-description-inheritance-path)
  (setf (class-description-inheritance-path-internal class-description)
	class-description-inheritance-path))
#+unused
(defsetf class-description-inheritance-path
    class-description-inheritance-path-function)




(def-substitution-macro class-vector-length (class-description)
  (handle-null-class-test
    (class-vector-length-internal class-description)))

#+unused
(defun class-vector-length-function (class-description class-vector-length)
  (setf (class-vector-length-internal class-description) class-vector-length))
#+unused
(defsetf class-vector-length class-vector-length-function)



(def-substitution-macro class-features (class-description)
  (handle-null-class-test
    (class-features-internal class-description)))
(defun class-features-function (class-description class-features)
  (setf (class-features-internal class-description) class-features))
(defsetf class-features class-features-function)



(def-substitution-macro slot-descriptions (class-description)
  (handle-null-class-test
    (slot-descriptions-internal class-description)))
(defun slot-descriptions-function (class-description slot-descriptions)
  (setf (slot-descriptions-internal class-description) slot-descriptions))
(defsetf slot-descriptions slot-descriptions-function)









;;; `Make-class-description' allocates a class structure and sets its
;;; components, except for the class bit numbers and vectors for system-defined
;;; classes which are set by assign-class-numbers-and-vectors-to-classes.

(defun make-class-description
       (class-name-of-class-description
	class-inheritance-path 
	class-vector-length
	class-features 
	slot-descriptions
	class-is-subclass-of-item?
	class-user-vector-length
	slots-local-to-class
	inherited-slots-this-class-overrides
	slot-descriptions-hash-table
	full-hash-table-class
	class-bit-number
	class-bit-vector
	method-table-of-class-description
	system-defined-class-p)
  
  (let ((class-description (make-class-description-internal)))
    (setf (class-name-of-class-description class-description)
	  class-name-of-class-description)
    (setf (class-inheritance-path-internal class-description)
	  class-inheritance-path)
    (setf (class-vector-length-internal class-description)
	  class-vector-length)
    (setf (class-features-internal class-description)
	  class-features)
    (setf (slot-descriptions-internal class-description)
	  slot-descriptions)
    (setf (class-is-subclass-of-item? class-description)
	  class-is-subclass-of-item?)
    (setf (class-user-vector-length class-description)
	    class-user-vector-length)
    (setf (slots-local-to-class class-description)
	  slots-local-to-class)
    (setf (inherited-slots-this-class-overrides class-description)
	  inherited-slots-this-class-overrides)
    (setf (slot-descriptions-hash-table class-description)
	  slot-descriptions-hash-table)
    (setf (full-hash-table-class class-description)
	  full-hash-table-class)
    (setf (class-bit-number class-description) class-bit-number)
    (setf (class-bit-vector class-description) class-bit-vector)
    (setf (method-table-of-class-description class-description)
	  method-table-of-class-description)
    (setf (class-description-is-system-defined-p class-description)
	  system-defined-class-p)
    class-description))








;;;; Class Membership Testing




;;; The class bit number, class-bit-vector, and class-is-subclass-of-item?
;;; slots of the class description are used to optimize subclass operations and
;;; tests of whether a given frame is a member of a class.  Some of the
;;; optimizations depend on the ability to quickly find the class descriptions
;;; of some often tested classes in the system.  The following definitions work
;;; in conjunction with def-class to define global variables which contain the
;;; class descriptions for these classes.

;;; The macro `declare-optimized-class-description-lookup' takes a rest argument
;;; of symbols which name classes which should have optimized references to
;;; their class descriptions within subclassp, of-class-p, and frame-of-class-p.

;;; The parameter `class-description-variable-alist' is defined by this macro and
;;; contains an alist of class names to names of variables which hold the class
;;; descriptions for these classes.

(defparameter class-description-variable-alist nil)

;;; `add-class-to-class-description-variable-alist' can only
;;; be called and compile or load time and can freely cons.

(defun add-class-to-class-description-variable-alist (class variable-name)
  (unless (assq class class-description-variable-alist)
    (push (cons class variable-name) class-description-variable-alist)))

(defmacro declare-optimized-class-description-lookup (&rest classes)
  (let ((alist (loop for class in classes
		     for variable =
			 (intern (format nil "~a-CLASS-DESCRIPTION" class))
		     collect (cons class variable))))
    `(progn
       ,@(loop for (class . variable) in alist
	       collect
		 `(progn
		    (defvar ,variable)
		    ,@(if (not (eval-feature :no-macros))
			  `((add-class-to-class-description-variable-alist
			      ',class ',variable))))))))





;;; The function `check-class-description-variables' is a development only
;;; function which is used to check that all variables which optimize class
;;; description lookups have been defined.  A call to this development only
;;; function should be included in a file after all classes have been defined.

#+development
(defun check-class-description-variables ()
  (loop for (class . variable) in class-description-variable-alist
	do
    (when (not (boundp variable))
      (warn "~a is referenced in declare-optimized-class-description-lookup, ~
             but was not defined as a class."
	    class))))




;;; Inheritance-path-memq tests whether class is a member of class-inheritance-
;;; path.

(defmacro inheritance-path-memq (class class-inheritance-path)
  `(memq ,class ,class-inheritance-path))



;;; Classp is true if x is a class, and in that case returns the class
;;; description.  Classp is a substitution macro.

(def-substitution-macro classp (x)
  (if (symbolp x) (class-description-macro x)))

(defun-simple classp-function (x)
  (classp x))


;;; The `byte-vector-index' and `byte-mask-for-bit' macros are for
;;; accessing bits on the class bit vector.

(defmacro byte-vector-index (class-bit-number)
  `(ashf ,class-bit-number -3))

(defmacro byte-mask-for-bit (class-bit-number)
  `(ashf 1 (the (integer 0 7) (logandf ,class-bit-number 7))))




;;; The macro `class-description-subclass-of-class-description-p' is used to
;;; determine if a given class-description describes a subclass of the class
;;; described by the second class description.  This macro is used internally
;;; within the more general class testing tools defined below, but can be called
;;; directly.

(defmacro class-description-subclass-of-class-description-p
			(sub-class-description superior-class-description)
  `(let* ((sub-class-bit-vector
	    (class-bit-vector ,sub-class-description))
	  (superior-class-bit-number
	    (class-bit-number ,superior-class-description))
	  (sub-class-vector-index 
	    (byte-vector-index superior-class-bit-number)))
     (declare (type fixnum
		    superior-class-bit-number sub-class-vector-index))
     (and (<f sub-class-vector-index (byte-vector-length sub-class-bit-vector))
	  (pluspf
	    (logandf
	      (byte-vector-aref 
		sub-class-bit-vector sub-class-vector-index)
	      (byte-mask-for-bit superior-class-bit-number))))))

(defun-simple class-description-subclass-of-class-description-p-function
    (sub-class-description superior-class-description)
  (class-description-subclass-of-class-description-p
    sub-class-description superior-class-description))



;;; The macro `class-description-of-class-p' is used to determine if a given
;;; class-description describes a subclass of the class named by the symbol
;;; given as the second argument.  This macro is used internally within several
;;; of the more general class testing tools defined below, but can be called
;;; directly.

(defmacro class-description-of-class-p (class-description symbol)
  (if (constantp symbol)
      (let* ((actual-class (eval symbol))
	     (class-description-var?
	       (cdr (assq actual-class class-description-variable-alist))))
	(cond ((eq actual-class 'item)
	       `(class-is-subclass-of-item? ,class-description))
	      (class-description-var?
	       `(class-description-subclass-of-class-description-p
		 ,class-description ,class-description-var?))
	      (t
	       (let ((superior-class-class-description? (gensym)))
		 `(let ((,superior-class-class-description? 
			 (class-description ,symbol)))
		    (and ,superior-class-class-description?
			 (class-description-subclass-of-class-description-p
			   ,class-description ,superior-class-class-description?)))))))
      (let ((superior-class-class-description? (gensym)))
	`(let ((,superior-class-class-description? 
		 (class-description ,symbol)))
	   (and ,superior-class-class-description?
		(class-description-subclass-of-class-description-p 
		  ,class-description ,superior-class-class-description?))))))




(defmacro unoptimized-class-description-of-class-p (class-description symbol)
  (let ((bindings nil)
	(subclass-description nil)
	(superior-class-name nil))
    (cond ((or (symbolp symbol) (constantp symbol))
	   (setq superior-class-name symbol))
	  (t
	   (setq superior-class-name (gensym))
	   (push (list superior-class-name symbol) bindings)))
    (cond ((symbolp class-description)
	   (setq subclass-description class-description))
	  (t
	   (setq subclass-description (gensym))
	   (push (list subclass-description class-description) bindings)))
    `(let ,bindings
       (if (eq ,superior-class-name 'item)
	   (class-is-subclass-of-item? ,subclass-description)
	   (memq-macro ,superior-class-name
		       (class-inheritance-path ,subclass-description))))))




;;; `Subclassp' is true if symbol is a subclass of class.  Note that a class is taken
;;; to be a subclass of itself.

(defmacro subclassp (symbol class)
  (if (constantp class)
      (let ((subclass-description (gensym)))
	`(let ((,subclass-description (class-description-macro ,symbol)))
	   (and ,subclass-description
		(class-description-of-class-p ,subclass-description ,class))))
      `(unoptimized-subclassp ,symbol ,class)))




;;; Note that in the case where the superior class description lookup cannot be
;;; optimized, it is better to use the old subclassp code to avoid two
;;; class-description lookups.  -jra 7/18/91

(defmacro unoptimized-subclassp (symbol class)
  (let ((class-description? (gensym)))
    `(let ((,class-description? (class-description ,symbol)))
       (if ,class-description?
	   (memq ,class (class-inheritance-path-internal
			  ,class-description?))))))

(defmacro subclassp-old (symbol class)
  (let ((class-description? (gensym)))
    `(let ((,class-description? (class-description ,symbol)))
       (if ,class-description?
	   (memq ,class (class-inheritance-path-internal
			  ,class-description?))))))




;;; (Sub-potential-class-p potential-class1 potential-class2) returns t if
;;; potential-class2 is either potential-class1, has appeared in a definition
;;; as the parent of potential-class1 or if for some x
;;; (sub-potential-class potential-class1 x) is t and
;;; (sub-potential-class x potential-class2) is t.

(defun sub-potential-class-p (potential-class1 potential-class2)
  (or (eq potential-class1 potential-class2)
      (loop for direct-superior in (direct-superior-classes potential-class1)
	    thereis (eq direct-superior potential-class2))))





;;; `Subclassp-function' behaves as does subclassp except that it is a function.

(defun subclassp-function (symbol class)
  (let ((class-description? (class-description symbol)))
    (if class-description?
	(memq class (class-inheritance-path class-description?)))))





;;; `Framep' is true if x is a frame, and in that case returns the class
;;; description for the frame.  (But note that x must not be a simple vector of
;;; length zero and that any simple vector with a class as its zeroeth element
;;; will appear to be a frame.)  Framep is a substitution macro.

;;; Note that framep is false if frame is a deleted frame that has yet to be
;;; recycled.  (In that case, its "class" slot becomes the symbol AVAILABLE-
;;; FRAME-VECTOR, which may not be the name of a class.)  However, since framep
;;; would be true of a frame which has been deleted and then recycled, it
;;; cannot be used to distinuish frames which may or may not have been deleted
;;; from non-frames.  For that, see the following predicate, frame-or-deleted-
;;; frame-p.

(def-substitution-macro framep (x)
  (and (simple-vector-p x)
       (>f (length (the simple-vector x)) 2)
       (neq (svref x 1) 'available-frame-vector)
       (let ((x2 (class-description-slot x)))
	 (and (class-description-p x2)
	      x2))))

;(def-substitution-macro framep-old (x)
;  (if (simple-vector-p x) (classp (svref x 0))))




;;; Frame-or-deleted-frame-p is true if x is a frame or is a deleted frame.

(def-substitution-macro frame-or-deleted-frame-p (x)
  (and (simple-vector-p x)
       (>f (length (the simple-vector x)) 2)
       (or (eq (svref x 1) 'available-frame-vector)
	   (class-description-p (class-description-slot x)))))

;; It does not make sense to me to say that a deleted frame is not framep!
;; In most places, e.g. frame-has-been-reprocessed-p, an argument named FRAME
;; can be a deleted frame.  Consider defining framep the same way as frame-or-
;; deleted-frame-p, flushing this definition completely, and fixing callers
;; appropriately.  Note that this definition was added today, but framep has
;; been around for years and has hundreds of callers.  (MHD 2/1/90)

;; Consider adding "If x is a frame, it returns the class description of x.  If
;; x is a deleted frame, it returns T" to the spec for frame-or-deleted-
;; frame-p.  Consider, alternatively, removing "If x is a frame, it returns the
;; class description of x" from the spec for framep.  Actually, it is usually
;; considered poor style to have a predicate return a value besides true or
;; false, so I recommend that these two as well as classp all change
;; accordingly.  (MHD 2/1/90)

;; Consider changing framep to frame-p everywhere, since "-p" suffixes are
;; much more standard in Gensym software. (MHD 2/1/90)



;;; The substitution macro `deleted-frame-p' is true if x is a frame which has
;;; been deleted and not recycled into something else.  As usual, we assume that
;;; any simple-vector with a class-name or 'available-frame-vector in location 0
;;; is such.

(def-substitution-macro deleted-frame-p (x)
  (and (simple-vector-p x)
       (eq (svref x 1) 'available-frame-vector)))




;;; The macro `frame-of-class-description-p' takes a frame and returns whether
;;; or not it is an instance of a subclass of the class described by the second
;;; argument, a class description.

(defmacro frame-of-class-description-p (frame superior-class-description)
  (if (symbolp superior-class-description)
      (let ((inferior-class-description (gensym)))
	`(let ((,inferior-class-description (class-description-slot ,frame)))
	   (class-description-subclass-of-class-description-p
	     ,inferior-class-description
	     ,superior-class-description)))
      `(class-description-subclass-of-class-description-p
	 (class-description-slot ,frame)
	 ,superior-class-description)))



     
;;; The slot accessors for class, lookup-structure, frame-serial-number, and
;;; class-description-slot are explicitly defined here.

;; jh, 11/10/91.  Moved the macros class, lookup-structure, and
;; class-description-slot here, so the framep form in of-class-p function could
;; compile correctly using the class macro.

(defmacro lookup-structure (frame)
  `(svref ,frame 0))

(defmacro class-description-slot (frame)
  `(svref ,frame 1))




;;; `Of-class-p' is true if x is a frame of class class.  (But note that x must
;;; not be a simple vector of length zero and that any simple vector with a
;;; subclass of class as its zeroeth element will appear to be a frame of class
;;; class.)

(defmacro of-class-p (x class)
  (let ((class-description? (gensym)))
    `(let ((,class-description? (framep ,x)))
       (and ,class-description?
	    (class-description-of-class-p ,class-description? ,class)))))

(declare-side-effect-free-function thing-is-item-p)

(defun-simple thing-is-item-p (thing)
  (if (and (simple-vector-p thing)
	   (>f (length (the simple-vector thing)) 2))
      (let ((class-description? (class-description-slot thing)))
	(if (class-description-p class-description?)
	    (class-is-subclass-of-item? class-description?)
	    nil))
      nil))




;;; The function `of-class-p-function' has the same semantics as of-class-p, but
;;; is a function.

(declare-side-effect-free-function of-class-p-function)

(defun-simple of-class-p-function (x class)
  (of-class-p x class))




;;; `Frame-of-class-p', like of-class-p, tests whether the first argument is an
;;; instance of the second.  Unlike of-class-p the first argument must be a
;;; frame.

(def-substitution-macro frame-of-class-p (frame symbol)
  (assert-for-development
    (framep frame)
    "argument ~s to frame-of-class-p is not a frame"
    frame)
  (class-description-of-class-p
    (class-description-slot frame) symbol))


  

;;; Class-case ... resembles the Common Lisp case macro in syntax.  It evaluates
;;; all of the forms in the cdr of the first clause matching test-class, a
;;; class.  A clause matches test-class if either
;;; 
;;;   (a) its car is either the symbol T or the symbol OTHERWISE; 
;;;   (b) its car the class C and (of-class-p test-class C); or
;;;   (c) its car is a list of classes at least one of whose elements
;;;       is the class C and (of-class-p test-object C)
;;;
;;; Note that C can be literally T or OTHERWISE but only if they are listed as
;;; case (c).

;;; As with CASE, the car of each test object is not evaluated; the cdr of each
;;; clause is evaluated as an implicit progn if and only if it matches; and test-
;;; class is always evaluated and always before any other code.  If no clause
;;; matches, nil is returned.  

;;; For example,
;;;
;;;   (class-case class ((a b) 1) (c 2) (t 3))
;;;
;;; is equivalent to
;;;
;;;   (cond ((or (subclassp class a) (subclassp class b)) 1)
;;;         ((subclassp class c) 2)
;;;         (t 3))
;;;
;;; except that it is slightly more efficient.

(defmacro class-case (test-class &body clauses)
  `(class-description-class-case (class-description ,test-class)
     ,@clauses))




;;; The macro `frame-class-case' is similar to class-case, except it takes a
;;; frame instead of a symbol naming a class as its dispatch value.

(defmacro frame-class-case (test-frame &body clauses)
  `(class-description-class-case (class-description-slot ,test-frame)
     ,@clauses))




;;; The macro `class-description-class-case' is similar to class case, except
;;; that it takes a class description instead of a class symbol.  This macro is
;;; used to implement class-case and frame-class-case.

(defmacro class-description-class-case (class-description &body case-clauses)
  (let ((description (if (symbolp class-description)
			 class-description
			 (gensym))))
    `(,@(if (eq class-description description)
	    '(progn)
	    `(let ((,description ,class-description))))
       (cond
	 ,@(loop for clause in case-clauses
		 collect
		   (cond
		     ((not (atom (car clause)))
		      `((or ,@(loop for class in (car clause)
				    collect
				    `(class-description-of-class-p
				       ,description ',class)))
			,@(cdr clause)))
		     ((not (memq (car clause) '(t otherwise)))
		      `((class-description-of-class-p
			  ,description ',(car clause))
			,@(cdr clause)))
		     (t
		      `(t ,@(cdr clause)))))))))




;;; The macro `class-inheritance-path-class-case' is similar to class-case in
;;; its interface, except it takes a class inheritance path of the dispatching
;;; class instead of the class symbol itself.  Note that this is actually the
;;; low level implementation of class-case and frame-class-case.

(defmacro class-inheritance-path-class-case
	  (class-inheritance-path &body case-clauses)
  (let ((path (gensym)))
    `(let ((,path ,class-inheritance-path))
       (cond
	 ,@(loop for clause in case-clauses
		 collect
		   (cond
		     ((not (atom (car clause)))
		      `((or ,@(loop for class in (car clause)
				    collect `(inheritance-path-memq
					       ',class ,path)))
			,@(cdr clause)))
		     ((not (memq (car clause) '(t otherwise)))
		      `((inheritance-path-memq ',(car clause) ,path)
			,@(cdr clause)))
		     (t				; otherwise clause
		      `(t ,@(cdr clause)))))))))




;;; The value of either evaluate-designation or is always nil, a
;;; temporary-constant, or a frame.  The following test to see if it is a frame
;;; of a given class is faster than using of-class-p, and more convenient than
;;; first testing to see if it is nil or a temporary-constant.  As of 7/2/89, it
;;; is used only in module ROLES.

;; Modified by ML on 1/7/90 to no longer reclaim if a temporary constant.

(defmacro designee-of-class-p (frame-nil-or-temporary-constant symbol)
  (if (and (or (symbolp frame-nil-or-temporary-constant)
	       (constantp frame-nil-or-temporary-constant))
	   (or (symbolp symbol)
	       (constantp symbol)))

      `(cond
	 ((or (null ,frame-nil-or-temporary-constant)
	      (temporary-constant-p ,frame-nil-or-temporary-constant))
	  nil)

	 (t
	  (memq ,symbol
		(class-inheritance-path
		  (class-description-slot ,frame-nil-or-temporary-constant)))))

      (let ((frame-evaled (gensym))
	    (symbol-evaled (gensym)))
	`(let ((,frame-evaled ,frame-nil-or-temporary-constant)
	       (,symbol-evaled ,symbol))
	   (cond
	     ((or (null ,frame-evaled)
		  (temporary-constant-p ,frame-evaled))
	      nil)

	     (t (memq ,symbol-evaled
		     (class-inheritance-path
		       (class-description-slot ,frame-evaled)))))))))




;;; The macro `strict-frame-of-class-p' tests whether the second argument is an
;;; instance of the class named by the first argument.  This macro requires that
;;; the first argument be a symbol naming a class and the second argument be a
;;; frame.


(defmacro strict-frame-of-class-p (class frame)
  `(eq ,class (class ,frame)))

;; Eval-slot-init-form is now used in file DEFINITIONS to create slot-initializations for
;; instances that exist when a class definition is modified. In order to avoid the
;; KLUDGE mentioned in make-frame, I have abstracted its functionality into the
;; predicate slot-init-form-needs-evaluation?. Only the :funcall part of it is
;; really pertinent. ML

(defun slot-init-form-needs-evaluation? (slot-init-form)
  (declare (special loading-kb-p))		; -- part of "kludge" below
  (and (consp slot-init-form)
       (eq (car-of-cons slot-init-form) :funcall)
       (not loading-kb-p))) 		; KLUDGE! (is this used anywhere?)

(def-substitution-macro eval-slot-init-form (slot-init-form)
  (if (and (consp slot-init-form)
	   (eq (car-of-cons slot-init-form) :funcall))
      (apply (car-of-cons (cdr-of-cons slot-init-form))
	     (cdr (cdr-of-cons slot-init-form)))
      slot-init-form))

;; This is used in modules FRAMES2 and OBJECTS.

;; jh, 11/10/91.  Moved the macros class, lookup-structure, and
;; class-description-slot further up this file, so the framep form in of-class-p
;; function could compile correctly using the class macro.



;;; The macro `more-specific-class-p' returns t if the first argument, a class
;;; symbol, appears to the left of the second class-symbol argument on the class-
;;; inheritance path; otherwise it returns nil.

(defmacro more-specific-class-p
    (more-specific-class less-specific-class class-inheritance-path)
  (let ((class-inheritance-path-arg (gensym-make-symbol "CLASS-INHERITANCE-PATH")))
    `(let ((,class-inheritance-path-arg ,class-inheritance-path))
       (<f (position ,more-specific-class ,class-inheritance-path-arg)
	   (position ,less-specific-class ,class-inheritance-path-arg)))))







;;;; Attributes and Attribute Slots



;;; An `attribute slot' is a slot that can be referred to and modified by
;;; knowledge (rules, formulas, function definitions, etc.) in the knowledge
;;; base.  The name of an attribute slot is called an `attribute'.

;;; An `attribute value' (or `attribute slot value') may be:
;;;
;;;    (1) a "slot constant" (see module FRAMES3);
;;;
;;;    (2) an item, often a variable;
;;;
;;;    (3) nil; or
;;;
;;;    (4) a number or a symbol (??).

;;; A user-defined slot is always an attribute slot.  Attribute slots are
;;; always vector slots.



;;; `Slot-category' is a global property of slot names.  It has a non-nil value
;;; for a system slot, and is absent or has a null value for an "attribute slot"
;;; (see below).

(def-global-property-name slot-category)



;;; `Not-a-system-slot-name-p' is true if pretty-slot-name does not name or
;;; describe a system slot, and thus may be assumed to be an attribute.

(defmacro not-a-system-slot-name-p (pretty-slot-name)
  `(null (slot-category-macro ,pretty-slot-name)))




;;; `Authorized-system-slots' is a list of slots that the user may access
;;; from g2 as if they were attributes. 

;;; The present method of access provided by serve-first-value-of-role is
;;; to assq the slot-name on the lookup-structure of the domain of the role
;;; service. For a lookup-slot,this will either be the instance value or the
;;; default value. For a vector-slot, the result is the default value for the
;;; class even if the instance has a value that differs from that. This works
;;; for user attributes because they are always lookup, and it works for CLASS
;;; because the default value is the instance value always. If any other system
;;; slot were to be accessed in this manner, the result would be wrong.
;;; ML - 7/16/90

(defparameter authorized-system-slots

  #+obsolete
  '(gsi-interface-status    ;jh, 9/13/90.
    interface-status        ;jh, 4/24/91.
    file-system file-status	;cpm 27sep90.
    simulation-details      ;agh 5/19/92.
    gsi-interface-name      ;ghw 4/21/95
    gsi-variable-status 	;jra 8/24/95
    data-server-for-messages ; jra 8/24/95
    )
  nil)

;; NB.  Authorized system-slots is OBSOLETE.  If you get the desire to add anything
;; to this lis you really should be defining a category-evaluator interface or a virtual
;; attribute.  Please see JED for details.

;; Note that predefined-user-attributes is a competitor for the role as the
;; "right way" to do this.  At least one of these should be elminiated.  -jra 8/24/95




;;; `Unauthorized-system-slot-p' is true if its argument is a system-slot
;;; to which the user is denied direct access as if it were an attribute.
;;; Provided as a function because its expected use is in compilers, and
;;; not for optimized for runtime speed.

(defun unauthorized-system-slot-p (symbol)
  (declare (ignore symbol))
  ;; For now, we will allow anything while we fix this up.  FIND ME, JRA!  -jra
  ;; 6/10/96
  nil
;  (and (slot-category symbol)
;       (not (memq symbol authorized-system-slots)))
  )







;;;;  Slot description access




;;; `Get-slot-description-of-class-description' takes a unique or pretty slot
;;; name, a class-description, and, optionally, a class qualifier.  It returns
;;; a slot-description from the class-description argument if there is one that
;;; qualifies, otherwise it returns nil.

;;; If there is a qualifying class argument, the class description inheritance
;;; path of the qualifying class is traversed to get a unique slot name to be used
;;; as a key when iterating over the class description inheritance path of the
;;; class-description argument.  

;;; NOTE TO G2 DEVELOPERS: it is not a good idea to call this macro (or the
;;; get-slot-description functions that call this macro) with a system-defined
;;; slot-name and a qualifying class argument.

;;; A class has either no slot description with a particular system-defined
;;; slot name or one slot description with that name, and this macro returns
;;; that first slot description found on the path without checking whether the
;;; qualifying class argument is on the class-inheritance-path of the
;;; class-description or whether the defining-class component of the slot
;;; description is a class that is more refined than the qualifying class
;;; argument.  This is done for efficiency reasons.

;;; When this macro is called with a user-defined unique slot name and a
;;; qualifying class that has either not inherited such a slot or is not even
;;; on the class inheritance path of the class-descripton, this macro returns
;;; nil.

(defvar class-is-undergoing-inheritance-change? nil)

(defmacro get-slot-description-of-class-description
    (unique-or-pretty-slot-name class-description &optional qualifying-class?)
  `(get-slot-description-of-class-description-function
     ,unique-or-pretty-slot-name ,class-description ,qualifying-class?))


(defun unique-slot-name-eq (x slot-description)
  (eq x (unique-slot-name slot-description)))




(defun-simple get-slot-description-of-class-description-function
    (slot-name class-description qualifying-class?)

  ;; The NULL check in (defmacro slot-description-from-class) has been moved there,
  ;; to prevent SBCL compiler warnings. --binghe, 9set2014
  (unless class-description
    (return-from get-slot-description-of-class-description-function))

  (when class-is-undergoing-inheritance-change?
    (return-from get-slot-description-of-class-description-function
      (get-slot-description
	slot-name (slot-descriptions class-description) qualifying-class?)))

  (if qualifying-class?
      
      (let ((qualifying-class-description?
	      (class-description-macro qualifying-class?)))
	(when qualifying-class-description?
	  (let* ((qualifying-class-full-hash-table-class
		   (full-hash-table-class qualifying-class-description?))
		 (unique-slot-name-key?
		   (loop for path-class-description in
			 (class-description-inheritance-path
			   qualifying-class-description?)
			 for class-name = (class-name-of-class-description
					    path-class-description)
			 for slot-description? = (get-slot-hash
						   slot-name
						   (slot-descriptions-hash-table
						     path-class-description))
			 do
		     (if (eq class-name qualifying-class-full-hash-table-class)
			 (return (when slot-description?
				   (unique-slot-name slot-description?)))
			 (when (and slot-description?
				    (or (eq (defining-class slot-description?)
					    class-name)
					(system-defined-slot-description-p
					  slot-description?)
					(eq slot-name
					    (unique-slot-name slot-description?))))
			   (return (unique-slot-name slot-description?))))))
		 (slot-description-to-return?
		   (and unique-slot-name-key?
			(loop for path-class-description in
			      (class-description-inheritance-path
				class-description)
			      for slot-description? = (get-slot-hash
							unique-slot-name-key?
							(slot-descriptions-hash-table
							  path-class-description))
			      when slot-description? return slot-description?))))
	    (when slot-description-to-return?
	      (return-from get-slot-description-of-class-description-function
		slot-description-to-return?)))))

      ;; There is no class qualifier.
      (let ((slot-description-to-return?
	      (loop with gathered-slot-descriptions? = nil
		    with full-hash-table-class = (full-hash-table-class
						   class-description)
		    for path-class-description in (class-description-inheritance-path
						    class-description)
		    for class-name = (class-name-of-class-description
				       path-class-description)
		    for slot-description? = (get-slot-hash
					      slot-name
					      (slot-descriptions-hash-table
						path-class-description))
		    do
		(if (and (eq class-name full-hash-table-class)
			 (null slot-description?))
		    (return nil)
		    (when slot-description?
		      ;; If the slot-name argument is a unique
		      ;; name for a user-defined slot description or is the
		      ;; name of a system-defined slot, the first
		      ;; slot-description found on the path is returned.
		      (cond ((or (eq slot-name
				     (unique-slot-name slot-description?))
				 (system-defined-slot-description-p slot-description?))
			     (reclaim-frame-list-macro gathered-slot-descriptions?)
			     (setq gathered-slot-descriptions? nil)
			     (return slot-description?))
			    ;; The check to see whether the class name is the defining-
			    ;; class component of the slot description avoids picking
			    ;; up a non-default overriding slot description.
			    ((or (eq class-name full-hash-table-class)
				 (eq (defining-class slot-description?) class-name))
			     (setq gathered-slot-descriptions?
				   (nreverse gathered-slot-descriptions?))
			     (let* ((gathered-slot-description?
				      (loop with unique-name = (unique-slot-name
								 slot-description?)
					    for gathered-slot-description
						in gathered-slot-descriptions?
					    when (eq (unique-slot-name gathered-slot-description)
						     unique-name)
					      return gathered-slot-description)))
			       ;; The default slot description is an override. 
			       (cond (gathered-slot-description?
				      (reclaim-frame-list-macro gathered-slot-descriptions?)
				      (return gathered-slot-description?))
				     ;; The default slot description is the defining-
				     ;; class slot description.
				     (t
				      (reclaim-frame-list-macro gathered-slot-descriptions?)
				      (return slot-description?)))))
			    (t (setq gathered-slot-descriptions?
				     (frame-cons-macro
				       slot-description? gathered-slot-descriptions?))))))
		    finally
		      (reclaim-frame-list-macro gathered-slot-descriptions?)
		      (return nil))))
	(return-from get-slot-description-of-class-description-function
	  slot-description-to-return?))))




;;; The macro `get-slot-description-of-frame' takes a unique or pretty slot
;;; name and a frame, and, optionally, a class specifier, and returns the slot
;;; description from the class description of that frame that qualifies;
;;; otherwise it returns nil.  See get-slot-description-of-class-description
;;; for documentation on the class-if-specific? argument.

(defmacro get-slot-description-of-frame
    (unique-or-pretty-slot-name frame &optional class-if-specific?)
  `(get-slot-description-of-class-description
     ,unique-or-pretty-slot-name (class-description-slot ,frame)
     ,class-if-specific?))




;;; `Slot-description-from-class', a macro, takes a class symbol and a unique or
;;; pretty slot name, and, optionally, a class specifier, and returns the slot
;;; description from the class description of class that qualifies; otherwise it
;;; returns nil.  See get-slot-description-of-class-description for
;;; documentation on the class-if-specific? argument.

;;; `Get-slot-description-from-class' is a function version of this macro.

(defmacro slot-description-from-class
    (class unique-or-pretty-slot-name &optional class-if-specific?)
  (let ((class-description-arg? (gensym)))
    `(let ((,class-description-arg? (class-description-macro ,class)))
       (get-slot-description-of-class-description
         ,unique-or-pretty-slot-name ,class-description-arg? ,class-if-specific?))))

(defun get-slot-description-from-class
    (class unique-or-pretty-slot-name &optional class-if-specific?)
  (slot-description-from-class class unique-or-pretty-slot-name class-if-specific?))




;;; `Get-slot-description-with-user-vector-slot-index' returns the item class
;;; slot description that has a user-vector-slot-index? component that equals
;;; the user-vector-slot-index argument.  If there is no slot description
;;; with that index, it returns nil.

(defun-simple get-slot-description-with-user-vector-slot-index
    (user-vector-slot-index item)
  (loop with slot-descriptions
	     = (slot-descriptions (class-description-slot item))
	for slot-description in slot-descriptions
	when (eq user-vector-slot-index
		 (user-vector-slot-index? slot-description))
	  return slot-description))




;;; `Slot-inherited-from-class-p' is true if subclass inherits the slot named
;;; slot-name from class.

(defun slot-inherited-from-class-p (class subclass pretty-slot-name)
  (equal (slot-init-form
	  (get-slot-description-of-class-description
	    pretty-slot-name (class-description class)))
	 (slot-init-form
	   (get-slot-description-of-class-description
	    pretty-slot-name (class-description subclass)))))




;;; The macro `class-has-override-on-slot-p' returns t when the class has
;;; placed a class-level initial-value on the slot referenced by
;;; unique-slot-name.

(defun-simple class-has-override-on-slot-p (class-description unique-slot-name)
  (let ((class-name (class-name-of-class-description class-description)))
    (if (user-defined-class-p class-name)
	(memq unique-slot-name
	      (inherited-slots-this-class-overrides class-description))
	(let ((class-slot-description?
		(get-slot-description-of-class-description
		  unique-slot-name class-description)))
	  (and class-slot-description?
	       (eq (defining-class class-slot-description?) class-name))))))
  



;;; `Most-specific-superior-that-refines-slot' returns the most specific-
;;; superior (not the class itself) on the class inheritance path that has
;;; refined the defining class slot description.  If no class has refined the
;;; slot, the defining class is returned.  Nil may be returned during kb
;;; clearing.

(defun most-specific-superior-that-refines-slot
    (class-inheritance-path slot-description)
  (loop with unique-slot-name = (unique-slot-name slot-description)
	with defining-class = (defining-class slot-description)
	for superior in (cdr class-inheritance-path)
	until (eq superior defining-class)
	for class-description? = (class-description superior)
	do
    (when (and class-description?
	       (class-has-override-on-slot-p
		 class-description? unique-slot-name))
      (return superior))
        finally (if (classp defining-class)
		    (return defining-class)
		    (return nil))))
	



;;; `Slot-description-of-most-specific-superior-refining-slot' returns the slot
;;; description for the most specific superior on the class inheritance path
;;; (not the class itself) that has refined that slot description.  Nil may be
;;; returned during kb clearing.

(defun slot-description-of-most-specific-superior-refining-slot
    (class-inheritance-path slot-description)
  (let ((refining-superior?
	  (most-specific-superior-that-refines-slot
	    class-inheritance-path slot-description)))
    (when refining-superior?
      (get-slot-description
	(unique-slot-name slot-description)
	(slot-descriptions (class-description refining-superior?))))))




;;; `Make-sparse-slot-descriptions-hash-table' 
;;; `Make-full-slot-descriptions-hash-table'

;;; These functions return a hash-table that will be the value of the
;;; slot-descriptions-hash-table slot on the class-description for a class.

;;; The hash table returned by make-full-slot-descriptions-hash-table contains a
;;; key and a slot-description value for the unique slot names of all of the
;;; slot descriptions for the class, plus a key for each pretty slot name
;;; in of the user-defined slot descriptions (if any) where the corresponding
;;; value is the default slot description with that pretty slot name for the
;;; class.

;;; The hash table returned by make-sparse-slot-descriptions-hash-table has
;;; keys and values like that of the full table but it only contains slot
;;; descriptions that are not EQ to a slot description of any superior class.

(defun make-sparse-slot-descriptions-hash-table
    (class slot-descriptions class-inheritance-path)
  (let ((hash-table (make-slot-hash)))
    (loop for slot-description in slot-descriptions
	  for unique-slot-name = (unique-slot-name slot-description)
	  for defining-class = (defining-class slot-description)
	  for differs-from-superior-slot-description? =
	        (unless (eq defining-class class)
		  (loop for superior in (cdr class-inheritance-path)
			for superior-slot-description? =
		              (slot-description-from-class
				superior unique-slot-name)
			until superior-slot-description?
			finally
			  (if (eq slot-description superior-slot-description?)
			      (return nil)
			      (return t))))
	  do
      (when (or (eq defining-class class)
		differs-from-superior-slot-description?)
	(setf (get-slot-hash unique-slot-name hash-table) slot-description)
	(when (user-defined-slot-description-p slot-description)
	  (let* ((pretty-slot-name (pretty-slot-name slot-description))
		 (existing-pretty-name-slot-description?
		   (get-slot-hash pretty-slot-name hash-table)))
	    (when (or (null existing-pretty-name-slot-description?)
		      (more-specific-class-p
			defining-class
			(defining-class existing-pretty-name-slot-description?)
			class-inheritance-path))
	      (setf (get-slot-hash pretty-slot-name hash-table)
		    slot-description))))))
    hash-table))

(defun make-full-slot-descriptions-hash-table
    (slot-descriptions class-inheritance-path)
  (let ((hash-table (make-slot-hash)))
    (loop for slot-description in slot-descriptions
	  do
      (setf (get-slot-hash (unique-slot-name slot-description) hash-table)
	    slot-description)
      (when (user-defined-slot-description-p slot-description)
	(let* ((pretty-slot-name (pretty-slot-name slot-description))
	       (current-slot-value?
		 (get-slot-hash pretty-slot-name hash-table)))
	  (when (or (null current-slot-value?)
		    (<f (position (defining-class slot-description)
				  class-inheritance-path)
			(position (defining-class current-slot-value?)
				  class-inheritance-path)))
	    (setf (get-slot-hash pretty-slot-name hash-table) slot-description)))))
    hash-table))




;;; The `class-bit-numbers-pool' is a list of class bit numbers that can be
;;; recycled.

(defun reclaim-frame-list-function (list)
  (reclaim-frame-list list))

(def-kb-specific-variable class-bit-numbers-pool frames1
  nil t reclaim-frame-list-function)




;;; The function `slot-name-needs-qualification-p' returns a non-null value when
;;; the slot description argument is not the default slot description among the
;;; slot descriptions for that class with the same pretty-slot-name.  This will
;;; be the case when the class has another slot description with the same
;;; pretty-slot-name but whose defining-class component names a class that is
;;; more specific to class for inheritance purposes than the defining-class of
;;; the slot-description argument.

;;; This macro relies on the fact that get-slot-description-of-class-
;;; description, when not given a class-if-specific argument, will return the
;;; default slot-description with pretty-slot-name for that class.
;;;
;;; This is optimized a bit for system-defined slots.  The optimization relies
;;; on the fact that system-defined slots never need qualification, as per the
;;; spec in section "Frames and slots":
;;;
;;;   a class description will contain only one slot definition
;;;   for a system-defined slot with a particular slot name

;;; When it needs qualification, users see it with the double-hyphen (::)
;;; prefix, and, in attribute tables, without hyphens stipped.

(defun-substitution-macro slot-name-needs-qualification-p
    (slot-description class-description)
  (and (not (system-defined-slot-description-p slot-description))
       (not (eq (defining-class slot-description)
		(defining-class (get-slot-description-of-class-description
				  (pretty-slot-name slot-description)
				  class-description))))))




;;; The substitution macro `class-qualifier-of-slot-description' is similar to
;;; slot-name-needs-qualification-p, but in the true case also returns the class
;;; qualifier needed to denote the given slot of the given frame.

(defun-substitution-macro class-qualifier-of-slot-description (frame slot-description)
  (if (not (system-defined-slot-description-p slot-description))
      (let ((defining-class (defining-class slot-description)))
	(if (not (eq defining-class
		     (defining-class
			 (get-slot-description-of-class-description
			   (pretty-slot-name slot-description)
			   (class-description-slot frame)))))
	    defining-class))))

;; There previously existed here the macro class-qualifier-of-slot, which just
;; tooks a frame and a slot-name.  But this was only called from one #+unused
;; function, and it made no sense: a slot-name without a class qualifier
;; ("defining-class") by its nature does not need qualification.  So, it was
;; removed and replaced by class-qualifier-of-slot-description, which is useful.
;; (MHD 5/9/00)





;;;; Class and Slot Features



;;; `Feature-assq' returns the feature specification in features corresponding to
;;; feature-name, if present; otherwise it returns nil.

(defmacro feature-assq (feature-name features)
  `(assq ,feature-name ,features))

(defmacro feature-assq-macro (feature-name features)
  `(assq-macro ,feature-name ,features))




;;; `Vector-slot-from-features-p', given the slot-features of a slot-definition
;;; or a slot-description, returns t if the slot-implementation is a slot
;;; on the frame vector; otherwise it returns nil.

(defmacro vector-slot-from-features-p (slot-features)
  `(feature-assq 'vector-slot ,slot-features))
      



;;; `Lookup-slot-from-features-p', given the slot features of a slot-definition
;;; or the slot features of a slot-description, returns t if the
;;; slot-implementation is a lookup-slot; otherwise it returns nil.
;;; Lookup-slot is the default if neither of the slot-features lookup-slot
;;; or vector-slot are given.

(defmacro lookup-slot-from-features-p (slot-features)
  `(not (feature-assq 'vector-slot ,slot-features)))
  



;;; `Normalize-features' accepts features from a definition (as they are within
;;; a class definition) and normalizes them into an alist.  This function is
;;; called for system-defined classes only.

(defun normalize-features (features)
  (loop for feature in features
	collecting (if (consp feature)
		       (copy-tree feature)
		       ;; Copy tree is used here for the following reasons:
		       ;; (1) It is desired that absolutely no conses which appeared in
		       ;;     quoted forms remain in an internal structure subject to
		       ;;     modification.
		       ;; (2) Features may take arguments. Although no features are yet
		       ;;     defined to take arguments of arbitrary structure, such a
		       ;;     possibility exists for the future. Consequently the Author
		       ;;     chose to make no catagorical assumptions about the form of
		       ;;     such arguments.
		       (cons feature nil))))










;;;; `Global-class-features' is a global list of all class features.





(defparameter global-class-features

    ;; This feature is for system-defined classes only.  The expansion
    ;; of the def-class form will define a macro, <class>-p, which
    ;; tests a frame for class membership.
  '(define-predicate

    ;; A class with this feature will not appear on menus that support
    ;; interactive instantiation.  It will not appear as a choice that
    ;; will be instantiated when it is clicked on, nor will it appear as a
    ;; choice that will bring up a submenu of inferior classes when it is
    ;; clicked on.  This feature has no effect on direct-superior class
    ;; choice menus.  This feature can be set on system-defined classes
    ;; by G2 programmers, and can be set on user-defined classes by
    ;; editing the include-in-menus? attribute on class definitions.
    do-not-put-in-menus

    ;; This feature prevents a class from being programmatically and
    ;; interactively instantiable by a G2 user.  This feature is placed on a
    ;; system class by G2 developers and on a user-defined class by editing the
    ;; instantiate? slot on class-definitions.  It is not inheritable.  If a
    ;; user-defined class has a not-solely instantiable class feature (see the
    ;; next class feature), it will also have a not-user-instantiable class
    ;; feature regardless of the value of the instantiate? attribute.
    not-user-instantiable

    ;; The system-defined class is user subclassable (the class must also have a
    ;; foundation-class feature) but the user-defined class cannot be
    ;; instantiated unless it has at least one direct superior that is
    ;; instantiable.  Unlike not-user-instantiable, this feature inherits down
    ;; to user-defined classes -- if all of the direct superiors of a
    ;; user-defined class have this feature, the class will inherit it.
    ;; A CLASS WITH THIS FEATURE MUST ALSO HAVE THE NOT-USER-INSTANTIABLE FEATURE.
    not-solely-instantiable
    
    ;; A system-defined class must have this feature to be user subclassable.
    ;; Its form is (foundation-class <class>) where class is usually the name of
    ;; the class being defined in the def-class form.  The exceptions are
    ;; system-defined classes that have a not-solely-instantiable class feature;
    ;; then <class> will be a superior class in order to allow the class to
    ;; "mixed-in" with a range of classes (for example, gsi-message-service has
    ;; a foundation class of "item" so that it can be mixed-in with any item
    ;; class).  The foundation class for a user-defined class is always the most
    ;; specific subclassable foundation class on its class inheritance path.
    foundation-class

    ;; Apply only to user-defined classes.
    stubs
    attribute-displays

    ;; Present if the class has indexed attributes, either inherited or
    ;; class-specific.  For user-defined classes only.
    has-indexed-attributes

    ;; Specify the feature in this form (disjoint-from <class1> <class2>
    ;; ... <classn>).  This feature keeps a class from appearing in a class
    ;; inheritance path with any of the classes listed in the disjoint-from
    ;; form.
    disjoint-from

    ;; Restricts a class to a set of direct superiors where the most refined
    ;; foundation class for that set is a member of the only-compatible-with
    ;; list, for example, a class feature of data-service classes is
    ;; (only-compatible-with variable).
    only-compatible-with

    ;; Adds a comment to the emitted HTML file describing the exported classes
    ;; and attributes, from the users perspective.  The comments under this
    ;; feature should describe generally what functionality is represented by
    ;; this class with a target audience of the documentation department here at
    ;; Gensym.  Use as (class-export-comment "Rules make if-then statements."),
    ;; but with more meat.
    class-export-comment

    ;; Restricts transient item creation.  Introduced as a feature to
    ;; help with the re-coding of class-can-be-transient-p
    not-normally-transient
    
    ))






;;; `Get-class-feature-if-any' returns the feature for class specified by
;;; feature-name, if there is one; otherwise it returns nil.

(defun get-class-feature-if-any (class feature-name)
  (let ((class-description? (class-description class)))
    (if class-description?
	(feature-assq feature-name (class-features class-description?)))))



	

(defmacro get-class-feature-in-class-description-if-any
	  (class-description feature-name)
  (if (or (symbolp class-description)
	  (constantp class-description)
	  (symbolp feature-name)
	  (constantp feature-name))
      `(feature-assq ,feature-name (class-features ,class-description))
      (let ((description (gensym)))
	`(let ((,description ,class-description))
	   (feature-assq ,feature-name (class-features ,description))))))





;;; `Slot-feature' is a marking on the definition of a slot found in a 
;;; def-class.  See also: error-check-slot-features, def-class, 
;;; slot-feature-p, get-slot-feature-if-any, and global-slot-features.

;;; One notable slot feature is the slot's type.  A number of useful
;;; things are associated with it the oldest of which is it's
;;; grammar for parsing.  Note that we don't store the representation
;;; type of the slot.  To the best of my knowledge there is no
;;; enumeration of the information stored via the type.

;;; Information about slots is also stored on the slot's pretty name,
;;; for example via def-slot-value-reclaimer.  To the best of my
;;; knowledge there is no enumeration of the information stored on
;;; the pretty name.

(def-concept slot-feature)

(def-concept lookup-slot)
(def-concept vector-slot)



;;; `Global-slot-features' is a global list of all slot features.

(defparameter global-slot-features

  '(
    ;; Lookup-slot specifies that the slot value, if non-default,  will be stored
    ;; on the lookup structure for a frame as a slot name-value pair.  In the
    ;; absence of a name-value pair on the lookup structure, the default value
    ;; is accessed from the class slot description.  The feature takes no
    ;; arguments.
    lookup-slot

    ;; Vector-slot specifies that the slot value, whether non-default or default,
    ;; will be found on the frame at the vector location given by the class slot
    ;; description.  The feature takes no arguments.
    vector-slot

    ;; No-accessor indicates that no accessor macro should be defined for the
    ;; slot.  The feature takes no arguments.
    no-accessor

    ;; Type is most often specified as (type <grammar-category-symbol>) and is
    ;; associated with a slot-value compiler and writer that have the same
    ;; symbol name.  To be user-editable, a slot must have a slot type feature;
    ;; but a slot with both a type feature and a not-user-editable feature
    ;; is not user-editable (the type is useful for slot writing).
    type

    ;; Save indicates that the slot value should be saved in the kb.  The feature
    ;; takes no arguments.
    save

    ;; Do-not-save indicates that the slot value should not be saved in the kb.
    ;; The feature takes no arguments.
    do-not-save

    ;; System specifies that the slot is defined in a def-class form.  All other
    ;; slots are user-defined and are frequently referred to as attributes.  The
    ;; feature takes no arguments.
    system

    ;; (Class-of-optional-subframe <class>) specifies the default value for that
    ;; slot to be an instance of of that class.  The class that is actually
    ;; instantiated is specified by the slot init form on the slot description.
    class-of-optional-subframe

    ;; Do-not-identify-in-attribute-tables causes the slot value to be displayed
    ;; without the slot name.  The feature takes no arguments.
    do-not-identify-in-attribute-tables

    ;; Do-not-put-in-attribute-tables keeps the slot entirely out of tables.
    ;; The feature takes no arguments.
    do-not-put-in-attribute-tables

    ;; (do-not-put-in-attribute-tables nupec):  When G2 is authorized for nupec,
    ;; this feature keeps the slot entirely out of tables.
    (do-not-put-in-attribute-tables nupec)

    ;; (do-not-put-in-attribute-tables no-nupec) keeps the slot entirely out of tables
    ;; unless G2 is authorized for nupec.
    (do-not-put-in-attribute-tables not-nupec)

    ;; (do-not-put-in-attribute-tables no-ent) keeps the slot entirely out of tables
    ;; when not in G2 enterprise version.
    (do-not-put-in-attribute-tables not-ent)

    ;; Do-not-put-in-attribute-tables-if-null keeps the slot entirely out of tables
    ;; when its slot value is NIL.  The feature takes no arguments.
    do-not-put-in-attribute-tables-if-null

    ;; User-overridable is a feature on system-defined slot descriptions which
    ;; indicates that the user can give that slot a class user-defined default
    ;; value (a slot-init-form that differs from that of the slot-init-form of
    ;; the system defining class).
    user-overridable

    ;; Class-slot keeps the default value from being inherited by inferior classes,
    ;; and prevents any non-default instance values.  See the comments above the
    ;; def-class-slot-description-updater for details.
    class-slot

    ;; Not-user-editable prevents the slot from being edited by users.  The feature
    ;; takes no arguments.
    not-user-editable

    ;; Edit-only suppresses all menu choices except edit.  The feature takes no
    ;; arguments.
    edit-only

    ;; Do-not-clone causes the slot to have the default value during cloning instead
    ;; of the value it has on the item being cloned.  The feature takes no arguments.
    do-not-clone

    ;; Select-changes prevents the slot from being user-edited in a run-time G2.  The
    ;; feature takes no arguments.
    select-changes

    ;; Note-slot-changes currently is a slot feature that is only on frame flags.
    ;; If a slot has this feature or the savable feature, it passes the slot-description-
    ;; is-noteworthy test which causes a setf macro to be defined for the slot.
    ;; The feature takes no arguments.
    ;; (ghw 10/25/95) 
    note-slot-changes

    ;; Previously-put-in-attribute-tables is used for backward-compatible support of
    ;; slots that are currently obsolete, allowing suppport of "change the text" and
    ;; "the text of" expressions.  The feature takes no arguments.
    previously-put-in-attribute-tables

    ;; The attribute-export-comment slot feature will contain a string used when
    ;; emitting the exported-attribute-description.  This comment should be a
    ;; draft to documentation of the use of this attribute as exported to G2
    ;; programmers.
    attribute-export-comment

    ;; Namelike Slots

    ;; A `namelike slot' is a slot in a frame that in some sense names a frame.
    ;; Usually, this is just name-or-names-for-frame.  However, in some cases it is
    ;; necessary for this to be some other slot defined for a class.  For example,
    ;; the slot giving the name of a method for procedures.
    ;;
    ;; When a namelike slot in a given frame is updated, it triggers the function
    ;; update-frame-name-references, on that frame and the appropriate subframes,
    ;; to all appropriate levels.
    ;;
    ;; In the case of the name-or-names-for-frame slot (only), this updates the
    ;; name-box and top-bar-of-image-plane if appropriate.
    ;;
    ;; For all slots, it updates table representations of the related class-header
    ;; slot on tables for all subframes that might include the namelike slot's
    ;; former value.
    ;;
    ;; The slot-description-for-namelike-slot-p slot of a slot description is
    ;; true for a slot with the namelike-slot feature.
    ;;
    ;; [Note: the namelike-slot feature supercedes the previous implementation
    ;; of this facility using the declare-namelike-slot and namelike-slot-p
    ;; macros. (MHD 5/14/00)]
    namelike-slot

    ;; Format (output as well as grammar/parsing) overrides are generated at
    ;; present only for user-defined slots. The format override overrides the
    ;; standard writer for the slot's type's category as well as overriding the
    ;; standard parser (grammar category) for the slot's type's category.
    format-override

    ;;; The `local-name-or-names' slot feature is only relevant in the
    ;;; definition of the name-or-names-for-frame slot on a given class.  The
    ;;; idea is that this should be used for something with a name in a local
    ;;; context only, and therefore the name should not be recorded in a
    ;;; non-local directory of names.  Ideally, it could be recorded in some
    ;;; sort of local directory: however, such a facility has yet to be
    ;;; developed.  In addition, this feature suppresses frame notes about
    ;;; multiple instances with the same In addition, this overrides the
    ;;; DO-NOT-CLONE feature, thereby allowing name-or-names-for-frame slots to
    ;;; be cloned, and similarly allows name-box subblocks to be
    ;;; cloned. Ideally, it could still be noted when multiple instances with
    ;;; the same name exist in the same local context; however, this facility
    ;;; does not currently exist.  (MHD 11/8/04)
    local-name-or-names))




;;; `Slot-feature-p' returns non-nil if its argument is a slot feature; otherwise
;;; it returns nil.  Slot-feature-p is a substitution macro.

(def-substitution-macro slot-feature-p (x)
  (memq (if (atom x) x (car x)) global-slot-features))



;;; `Error-check-slot-features', given a list of slot features, checks the slot features
;;; for validity.

(defun error-check-slot-features (slot-features)
  (if (not (or (null slot-features) (consp slot-features)))
      (error "~S is an invalid slot feature list." slot-features)
      (loop for supposed-feature in slot-features
	    doing
	(when (not (slot-feature-p supposed-feature))
	  (error "~S is an invalid slot feature." supposed-feature))))
  slot-features)



;;; `Get-slot-feature-if-any', given a class, a slot-name, and a feature-name,
;;; returns the feature of the slot if it is present.

(defun get-slot-feature-if-any (class unique-or-pretty-slot-name feature-name
				      &optional class-if-specific?)
  (let* ((class-description? (class-description class))
	 (slot-description?
	   (when class-description?
	     (get-slot-description-of-class-description 
	       unique-or-pretty-slot-name class-description?
	       class-if-specific?))))
    (when slot-description?
      (feature-assq feature-name (slot-features slot-description?)))))




;;; `Alias-slot-name-if-necessary' returns the alias for pretty slot name on
;;; class-or- frame?, if there is one; otherwise, it just returns
;;; pretty-slot-name.

(def-substitution-macro alias-slot-name-if-necessary
    (pretty-slot-name class-or-frame?)
  (or (get-alias-for-slot-name-if-any pretty-slot-name class-or-frame?)
      pretty-slot-name))



;;; `Unalias-slot-name-if-necessary' returns the slot-name that alias is the
;;; alias for, if there is one; otherwise, it just returns alias.

(def-substitution-macro unalias-slot-name-if-necessary
    (slot-name-or-alias class-or-frame?)
  (or (get-slot-name-for-alias-if-any slot-name-or-alias class-or-frame?)
      slot-name-or-alias))




;;; The function `attribute-previously-put-in-attribute-tables-p' takes a unique
;;; or pretty slot or aliased name and optionally a class, and returns whether
;;; or not this attribute has a slot-definition with the previously-put-in-
;;; attribute-tables slot feature on it.  This is used when user-accessible
;;; system defined attributes are made obsolete, but we retain an ability to
;;; support existing calls to the "change the text of" and "the text of" for
;;; that name.

(defun attribute-previously-put-in-attribute-tables-p
    (attribute &optional (class? nil))
  (let* ((unaliased-attribute
	   (unalias-slot-name-if-necessary attribute (or class? 'item)))
	 (slot-description?
	   (if class?
	       (slot-description-from-class unaliased-attribute class?)
	       (or (slot-description-from-class 'class-definition unaliased-attribute)
		   (slot-description-from-class 'object-definition unaliased-attribute)
		   (slot-description-from-class 'block unaliased-attribute)
		   (slot-description-from-class 'drawing-parameters unaliased-attribute)))))
    (and slot-description?
	 (feature-assq-macro
	   'previously-put-in-attribute-tables
	   (slot-features slot-description?)))))

;; Note that the hard-coded list of classes in this predicate needs to be
;; updated whenever we add the previously-put-in-attribute-tables slot feature
;; onto a slot in a class that hasn't had it before.  It would be nice if this
;; were better abstracted, but note that this still needs to be a relatively
;; quick check, so iteration over all system-classes every time this function is
;; called is unacceptible.  -jra 2/9/95


;; This is used in DEFINITIONS, ENTITIES, EDIT, MENUS, and GRAMMAR2 as of 7/2/89.







;;;; Slot Definitions



;;; A `slot definition' is the form within a class definition that defines a
;;; slot.  A slot definition is "compiled" into a slot description.  Below are
;;; defined various accessors for the parts of a slot a definition.  They
;;; all assume that their slot-definition argument is a syntactically valid
;;; slot definition.


;;; `Slot-name-given-slot-definition' accesses the slot name of a slot
;;; definition.

(defmacro slot-name-given-slot-definition (slot-definition)
  `(first ,slot-definition))



;;; `Slot-init-form-given-slot-definition' accesses the slot init form of a slot
;;; definition.

(defmacro slot-init-form-given-slot-definition (slot-definition)
  `(second ,slot-definition))



;;; `Slot-features-given-slot-definition' accesses the slot features of a slot
;;; definition.

(defmacro slot-features-given-slot-definition (slot-definition)
  `(cddr ,slot-definition))

;; I simplified these to assume a syntactically valid slot definition.  As of
;; 3/8/91, only slot-name-given-slot-definition is in use, and only in one
;; place.  There is probably some unabstracted accessing of slot definitions,
;; however.  (MHD 3/8/91)





;;; `Make-and-change-class-description' makes the old class-description into the
;;; new one.  If there is no class-description for class, it allocates one.  All
;;; the components are set except for class-number and maximum-class-number-of-
;;; subclass which are set by assign-class-numbers-to-classes.

(defun make-and-change-class-description 
    (class 
     class-inheritance-path
     class-vector-length
     class-features
     slot-descriptions
     class-is-subclass-of-item?
     class-user-vector-length
     slots-local-to-class
     inherited-slots-this-class-overrides
     slot-descriptions-hash-table
     full-hash-table-class
     class-bit-number
     class-bit-vector
     method-table-of-class-description
     system-defined-class-p)

  (let* ((class-description
          (or (class-description class)
              (make-class-description-internal))))

    #+development
    (when (and (not (class-description class))
	       debugging-class-description-leaks? 
	       *there-is-a-current-kb?*)
      (setq unreclaimed-class-descriptions 
	    (frame-cons class-description unreclaimed-class-descriptions)))

    (setf (class-name-of-class-description class-description)
	  class)
    (setf (class-inheritance-path-internal class-description)
	  class-inheritance-path)
    (setf (class-vector-length-internal class-description) class-vector-length)
    (setf (class-features-internal class-description) class-features)
    (setf (slot-descriptions-internal class-description) slot-descriptions)
    (setf (class-is-subclass-of-item? class-description)
	  class-is-subclass-of-item?)
    (setf (class-user-vector-length class-description) class-user-vector-length)
    (setf (slots-local-to-class class-description) slots-local-to-class)
    (setf (inherited-slots-this-class-overrides class-description)
	  inherited-slots-this-class-overrides)
    (setf (slot-descriptions-hash-table class-description)
	  slot-descriptions-hash-table)
    (setf (full-hash-table-class class-description)
	  full-hash-table-class)
    (setf (class-bit-number class-description) class-bit-number)
    (setf (class-bit-vector class-description) class-bit-vector)
    (setf (method-table-of-class-description class-description)
	  method-table-of-class-description)
    (setf (class-description-is-system-defined-p class-description)
	  system-defined-class-p)
    (setf (class-description class) class-description)
    class-description))




;;; `Make-slot-description' returns a slot description structure with
;;; the component values filled in.

(defun make-slot-description 
    (pretty-slot-name defining-class owner-class slot-type-specification
		      slot-init-form vector-slot-index? user-vector-slot-index?
		      slot-features &optional do-not-copy-arguments?)
  (let ((slot-description (make-slot-description-internal))
	(unique-slot-name-to-set
	  (if user-vector-slot-index?
	      (make-unique-slot-name-symbol defining-class pretty-slot-name)
	      pretty-slot-name)))
    
    (setf (unique-slot-name slot-description) unique-slot-name-to-set)
    (setf (pretty-slot-name slot-description) pretty-slot-name)
    (setf (defining-class slot-description) defining-class)
    (setf (owner-class slot-description) owner-class)
    (setf (slot-type-specification slot-description)
	  (if do-not-copy-arguments?
	      slot-type-specification
	      (copy-tree-using-class-description-conses
		slot-type-specification)))
    (setf (slot-init-form slot-description) 
	  (if (or do-not-copy-arguments?
		  (icon-description-slot-init-form-p slot-init-form))
	      slot-init-form
	      (copy-for-slot-value slot-init-form)))
    (setf (vector-slot-index? slot-description) vector-slot-index?)
    (setf (user-vector-slot-index? slot-description) user-vector-slot-index?)
    (setf (slot-features slot-description) 
	  (if do-not-copy-arguments?
	      slot-features
	      (copy-tree-using-class-description-conses slot-features)))
    (setf (slot-description-for-namelike-slot-p slot-description)
	  (if (feature-assq 'namelike-slot slot-features) t nil))
    #+development
    (when (and debugging-slot-description-leaks? 
	       *there-is-a-current-kb?*)
      (setq unreclaimed-slot-descriptions 
	    (frame-cons slot-description unreclaimed-slot-descriptions)))
    slot-description))




;;; `Make-slot-description-with-error-checking', given a slot definition and a
;;; vector slot index, performs error checking on the slot definition before
;;; making a slot description.  Since this function is called only from
;;; expand-class-definition which deals only with system-defined classes, the
;;; fact that do-not-copy-arguments? is set to true does not cause any memory
;;; reclamation problems because system slot-descriptions are not reclaimed.

;;; Note that this now [as of 2/7/96 -- 5.0 development by MHD] copies slot
;;; values in init forms (as slot values).

(defun make-slot-description-with-error-checking 
       (class slot-definition &optional (vector-slot-index nil)
	      (direct-superior-classes? nil))
  (cond ((null slot-definition)
	 (warn-of-invalid-slot-name nil))
       	((consp slot-definition)
	 (if (or (null (slot-name-given-slot-definition slot-definition)) 
		 (not (symbolp (car slot-definition))))
	     (warn-of-invalid-slot-name 
	       (slot-name-given-slot-definition slot-definition))
	     (cond ((or (null (cdr slot-definition))
			(not (consp (cdr slot-definition)))
			(slot-feature-p 
			  (slot-init-form-given-slot-definition slot-definition)))
		    (warn-of-invalid-slot-definition slot-definition))
		   (t
		    (let ((pretty-slot-name
			    (slot-name-given-slot-definition slot-definition)))
		      (make-slot-description 
			pretty-slot-name class class nil
			;; slot-init-form
			(let ((slot-init-form 
				(slot-init-form-given-slot-definition slot-definition)))
			  (if (and (consp slot-init-form)
				   (and
				     (memq (car slot-init-form)
					   '(:funcall :funcall-at-load-time))
				     (or
				       (null (cdr slot-init-form))
				       (and
					 (not (symbolp (cadr slot-init-form)))
					 (not (consp (cadr slot-init-form)))))))
			      (warn-of-invalid-slot-init-form
				slot-init-form slot-definition)
			      slot-init-form))					

			;; vector-slot-index?
			vector-slot-index

			;; user-vector-slot-index?
			nil

			;; slot-features
			;; (Since this function is called only from expand-class-
                        ;; definition, it need not concern itself with user-
                        ;; defined slot reclamation.)
			(let ((normalized-slot-features
				(normalize-features
				  (error-check-slot-features
				    (slot-features-given-slot-definition 
				      slot-definition)))))
			  (unless (feature-assq 'system normalized-slot-features)
			    (setq normalized-slot-features
				  (cons (list 'system) normalized-slot-features)))
			  (when direct-superior-classes?
			    (unless
			      (slot-type-compatible-with-ancestors-p
				(slot-name-given-slot-definition slot-definition)
				(or (and (feature-assq 'vector-slot
						       normalized-slot-features)
					 'vector-slot)
				    (and (feature-assq 'lookup-slot
						       normalized-slot-features)
					 'lookup-slot))
				direct-superior-classes?)
			      (warn-of-attempt-to-redefine-the-type-of-a-slot
				(slot-name-given-slot-definition slot-definition)
				(if (feature-assq 'vector-slot
						  normalized-slot-features)
				    '"VECTOR-SLOT"
				    '"LOOKUP-SLOT"))))
			       normalized-slot-features)

			;; Changed! See note. (MHD 2/7/96)
;			;; do-not-copy-arguments?
;			t
			))))))
       
	(t (warn-of-invalid-slot-definition slot-definition))))


;; Note that this now [as of 2/7/96 -- 5.0 development by MHD] copies slot
;; values in init forms (as slot values), which means that we no longer have
;; either gensym floats or gensym strings in slot init forms.  This was done for
;; 5.0, where it was impractical to have gensym strings in slot init forms; it
;; was not only practical, but also working functionality, to have (constant)
;; gensym floats in slot init forms, but we don't need the space savings that
;; much complexity; and, eventually, we can simplify some code by taking
;; advantage of this simplification. (MHD 2/7/96)




;;; `Eval-slot-init-forms-of-local-slot-descriptions' evaluates the funcall-at-
;;; load-time slot-init-forms in the local slot descriptions of a class that is
;;; being defined.

(defun eval-slot-init-forms-of-slot-descriptions-defined-for-class 
    (user-class slot-descriptions)
  (loop for slot-description in slot-descriptions
	for slot-init-form = (slot-init-form slot-description)
	with funcall-spec = nil
	do
    (when (and (consp slot-init-form)
	       (eq (car slot-init-form) ':funcall-at-load-time))
      (let ((function-to-funcall (second slot-init-form)))
	(setq funcall-spec slot-init-form)
	(setf (slot-init-form slot-description)
	      (apply (cadr slot-init-form) (cddr slot-init-form)))
	(when (eq function-to-funcall 'create-icon-description-if-valid)
	  (set-icon-owner-class user-class (slot-init-form slot-description)))
	;; don't reclaim the whole slot value as some of the components are reused
	(reclaim-slot-value-list-function funcall-spec)))))

	


;;; `Copy-slot-descriptions-evaluating-initialization-if-eval-once'
;;; copies the slot descriptions and evaluates the slot init form.  It is called
;;; from add-class-to-the-environment for system-defined classes.

(defun copy-slot-descriptions-evaluating-initialization-if-eval-once
       (slot-descriptions)
  (loop for slot-description in slot-descriptions
	for slot-init-form = (slot-init-form slot-description)
	for copy-of-slot-description =
	      (make-slot-description
		(pretty-slot-name slot-description)
		(defining-class slot-description)
		(owner-class slot-description)
		(slot-type-specification slot-description)
		(slot-init-form slot-description)
		(vector-slot-index? slot-description)
		(user-vector-slot-index? slot-description)
		(slot-features slot-description)
		t)
	do
    (when (and (consp slot-init-form)
	       (eq (car slot-init-form) ':funcall-at-load-time))
      (setf (slot-init-form copy-of-slot-description)
	    (apply (cadr slot-init-form) (cddr slot-init-form))))

	collect copy-of-slot-description))




(defun slot-type-compatible-with-ancestors-p 
       (pretty-slot-name slot-type direct-superior-classes)
  (if (null slot-type) 
      t
      (let ((slot-description-in-direct-superior?
	      (loop with slot-description = nil
		    for superior in direct-superior-classes
		    until slot-description
		    do
		(setq slot-description
		      (get-slot-description-of-class-description 
			pretty-slot-name (class-description superior)))
		    finally (return slot-description))))
	(if (or (null slot-description-in-direct-superior?)
		(feature-assq slot-type 
			      (slot-features 
				slot-description-in-direct-superior?)))
	    t
	    nil))))









;;; Given a class or a frame, the `attributes iteration' path facilitates
;;; iteration over the attribute slot names of the class or frame.
;;; For example,
;;;    (loop for x being each attribute of 'foo doing (print x)),
;;; will print the slot names of all attribute slots of the class foo.
;;; And,
;;;    (loop for x being each attribute of (make-frame 'foo) doing (print x))
;;; will do the same.

(eval-when (:compile-toplevel :load-toplevel :execute)
(defun-for-macro attributes-path
    (path-name variable data-type
	       prep-phrases inclusive? allowed-preposistions data)
    ;; These variables are not used.
    (declare (ignore data-type data allowed-preposistions))
    (let ((bindings nil)
	  (prologue nil)
	  (slot-descriptions-variable (loop-gentemp))
	  (attribute-slot-description (loop-gentemp))
	  (class-description (loop-gentemp)))
      ;; Warn of missing prepositional phrase.
      (if (null prep-phrases)
	  (error "IN is missing in ~S iteration path of ~S" path-name variable))
      ;; Inclusive iteration is not supported.
      (if inclusive?
	  (error "Inclusive stepping is not supported in ~S path of ~S ~
                  (prep-prase = ~:S)"
		 path-name variable prep-phrases))
      (setq bindings
	    `((,slot-descriptions-variable nil)
	      (,variable nil)
	      (,class-description
		 (let ((class-or-frame ,(cadar prep-phrases)))
		   (if (symbolp class-or-frame)
		       (class-description class-or-frame)
		       (class-description-slot class-or-frame))))))
      (setq prologue
	    `((loop for tail-of-slot-descriptions
			on (slot-descriptions ,class-description)
		    until (user-defined-slot-description-p
			    (car-of-cons tail-of-slot-descriptions))
		    finally
		      (setq ,slot-descriptions-variable
			      tail-of-slot-descriptions))))
      ;; Return the appropriate items.
      `(,bindings
	,prologue
	(null ,slot-descriptions-variable)
	nil
	nil
	(,variable
	   (let ((,attribute-slot-description
		    (car-of-cons ,slot-descriptions-variable)))
	     (if (slot-name-needs-qualification-p
		   ,attribute-slot-description ,class-description)
		 (unique-slot-name ,attribute-slot-description)
		 (pretty-slot-name ,attribute-slot-description)))
	 ,slot-descriptions-variable
	   (cdr ,slot-descriptions-variable))))))


(define-loop-path (attributes attribute)
		  attributes-path (of))

;; OK here, but do not use this path within this file while we are running TI
;; 3.0.  This is a new TI bug. (MHD 8/5/87)








;;;; Slot Putters




;;; A `slot putter' is a specialized function for setting a slot to a value.  A
;;; slot putter, if there is one for a slot, is associated with the slot's name,
;;; except that all "attribute slots" implicitly have the slot putter named
;;; put-attribute-value.  A normal slot putter gets three arguments: the frame,
;;; the new value, and t or nil according to whether this is an initialization
;;; case or not.  Put-attribute-value gets four arguments:  the frame, the slot
;;; name, the new value, and t or nil for the initializing case.

;;; A slot putter
;;;
;;;    (1) must set the slot, though it may complain (via frame notes or
;;;    notifications);
;;;
;;;    (2) must return what it actually stores, which may differ from the
;;;    argument it is given;

;;;    Alternative for (1) and (2):  must either store and return some datum, or
;;;    else return the value that it leaves undisturbed.
;;;					-pto & ml  01dec88
;;;
;;;    (3) may have various (non-cyclic) side effects, including the updating of
;;;    other slots and of frame representation, which side effects are often
;;;    conditional on whether or not this is an initialization case;
;;;
;;;    (4) may use and return the old value of the slot as a whole, but
;;;    otherwise should not use any recyclable part of the old value for the
;;;    slot, unless it returns a non-nil second value (which tells the
;;;    invoker not to reclaim the old value);
;;;
;;;    (5) should reclaim, as appropriate, any unused recyclable parts of the
;;;    value it is given;
;;;
;;;    (6) when the slot must be reclaimed by some mechanism better than
;;;    that provided by reclaim-slot-value, must reclaim the old
;;;    value in the slot putter and return a second non-nil value to
;;;    indicate that it reclaimed the old value.

;;; Slot putters are invoked by make-frame, by read-element-for-kb, and by
;;; change-slot-value (the only non-initialization case).  Remember that
;;; change-slot-value calls slot value reclaimer if and only if the second
;;; value returned by the slot putter is true.  Also, remember that the old
;;; value should never be reclaimed if it is the same as (eq to) the slot's
;;; default value.

;;; The author of a def-slot-putter should bear in mind that slot putters are
;;; called in many contexts.  You can assume very little about the general
;;; state of the world when you are called.  

;;; Here are some flags etc. that you may want to reference in the body of
;;; the slot putter to modify its operation.

;;; `Initializing', an optional parameter, notifies you that the frame
;;; caller was clone-frame (see notes) while filling out the initial
;;; values.  Indirect calls do not have this parameter propagated to
;;; them, e.g., calls from the initialization method.
;;; Note: Amazingly make frame does not generally call slot putters.
;;; Note: There are a few dozen call sites that set initializing to T
;;; when calling the slot putter for particular slots.

;;; `Frame-being-deleted-p', a macro, is true when we are
;;; currently deleting this frame.  The cleanup methods of a frames
;;; often call slot putters.  The slot putter is not called by the
;;; delete-frame directly, rather delete-frame (and only delete-frame)
;;; calls the slot-value reclaimer.

;;; `Reading-kb-p', a special variable, is true when the we are in the
;;; process of reading in the KB.  During this time is is very racy to
;;; assume anything about the status of other frames in the KB.
;;; `Loading-kb-p', a special variable, is true when reading-kb-p is
;;; true, or during the execution of the post loading functions.

;;; `Activation status' can, of course, be determined from frame flags.

;;; Here are some things that are difficult to infer dynamically about the
;;; state of the system, and which you must think thru.

;;; `Clone-frame', a function, (see notes above) provides no dynamic
;;; state to indicate that it is calling the slot putter.

;;; `Consistency analysis' may or may not be "asserted" for the frame you
;;; are working on.  The general rule is that shortly after initialization
;;; the analysis is asserted, and then it is only retracted for short
;;; intervals within slot putters.  Finally, it is retracted during deletion.
;;; There are analogous issues around `frame flags'.

;;; `Visibility' is not conveniently computable.

;;; `Erase state': if a frame's contents effects its on-screen representation
;;; then you must update the drawing when you change the slot value.  This
;;; arises very rarely in G2.  For example, updating table representations is
;;; wired into change-slot-value.  Note that delete-frame erases the frame
;;; prior to calling the cleanup method.


(def-global-property-name slot-putter)
(def-global-property-name class-slot-description-updater)



;;; The macro `get-slot-putter-if-any' returns the slot putter, if any, for the
;;; pretty-slot-name slot.  Note that the version that accepts a slot
;;; description is preferrable for speed reasons.

(def-substitution-macro get-slot-putter-if-any (pretty-slot-name)
  (or (slot-putter pretty-slot-name)
      (if (not-a-system-slot-name-p pretty-slot-name)
	  'put-attribute-value)))

(def-substitution-macro get-slot-description-putter-if-any (slot-description)
  
  ;; Bug fix: replace slightly optimized version below with call to the old
  ;; code; the newer way fails for predefined attributes, e.g., g2-user-mode,
  ;; which must return put-attribute-value in order for chaining to work!  JRA
  ;; will review. (When optimizing, consider putting the putter into the a slot
  ;; in the description as an optimization anyway -- that will save a plist
  ;; lookup in the system-defined-slot case.) (MHD 5/24/95)

  ;; Note that there was a bug here because of the difference between
  ;; system-defined-slot-description-p and not-a-system-slot-name-p.  They do
  ;; not describe the same characteristic!  We'll need to rename or eliminate
  ;; one or the other characteristic in the next release.  -jra 5/25/95
  (if (system-defined-slot-description-p slot-description)
      (get-slot-putter-if-any (pretty-slot-name slot-description))
      'put-attribute-value))




;;; `Def-slot-putter' defines a slot putter for pretty-slot-name.  Such a definition is
;;; of the form
;;;
;;;     (DEF-SLOT-PUTTER pretty-slot-name (frame-var new-value-var
;;;                                 [initialization-case-var])
;;;        . body)
;;;
;;; The body refers to frame-var and new-value-var to do the setting.  It may
;;; also refer to initialization-case-var, when specified, to determine whether
;;; or not the slot putter is being invoked to initialize the slot (rather than
;;; to update its value).  In an initialization case (when the frame is being
;;; first made or is being reconstructed during knowledge base loading), it is
;;; often appropriate, and sometimes necessary, to skip certain side effects of
;;; slot putting.

;;; The name of the defined slot putter for pretty-slot-name is derived by prefixing
;;; pretty-slot-name with "PUT-".

(defmacro def-slot-putter
	  (pretty-slot-name (frame-var new-value-var . listed-initialization-case-var)
	   &body body)
  (let ((putter-name
	  (intern (format nil "PUT-~A" pretty-slot-name)))
	(initialization-case-var
	  (if listed-initialization-case-var
	      (car listed-initialization-case-var)
	      (gensym))))
    `(progn
       (declare-function-type ,putter-name (t t t) (t t))
       (defun ,putter-name (,frame-var ,new-value-var ,initialization-case-var)
	 ,@(if (null listed-initialization-case-var)
	       `((declare (ignore ,initialization-case-var))))
	 ,@body)

       ;; Make these traceable in development. -fmw, 5/24/95
       (setf (slot-putter ',pretty-slot-name)
	     #+development ',putter-name
	     #-development #',putter-name)
       
       ',putter-name)))

;; There is more doc for def-slot-putter up about a page from here.




;;; `Def-class-slot-description-updater' defines an updater that, minimally,
;;; places a new slot-init-form on a system slot-description that has a
;;; class-slot feature.

;;; Each user class that inherits such a slot will redefine it for itself, which
;;; means that it will not share the slot description with any other class.  The
;;; task of making a class-owned slot for class-slot slots is currently done by
;;; define-user-class.

;;; What makes a class-slot different is that a change in value will not inherit
;;; down the class hierarchy, nor will there ever be any non-default instance
;;; values.  Only the updater should change the slot-init-form value, and
;;; update-slot-description should never be called on the slot.

;;; The slot-description should should have these slot features: system,
;;; lookup-slot, not-user-editable, do-not-save, no-accessor, do-not-put-in-
;;; attribute-tables, and class-slot.  The last feature informs developers of
;;; the slot status, and most of the remaining features prevent the slot from
;;; having any user-generated instance values.

;;; Currently only process-default-overrides accesses the class-slot-
;;; description-updater for a slot.  The facility was defined to replace the
;;; class-specific slots on object, connection, and message definitions.  These
;;; three definitions are supported for reasons of backward compatibility; but
;;; the new definition, class-definition, with an expanded default-overrides
;;; facility, can be used to subclass all subclassable item classes.

;;; The class-slot-descriptoin-updater definition is in the form:
;;;
;;;     (DEF-CLASS-SLOT-DESCRIPTION-UPDATER pretty-slot-name
;;;                                            (class-var new-value-var) . body)
;;;
;;; The body refers to class-var and new-value-var to do the setting and handle
;;; any side effects.
;;;
;;; The name of the defined slot-init-form putter for pretty-slot-name is derived
;;; by prefixing pretty-slot-name with "UPDATE-".

(defmacro def-class-slot-description-updater
	  (pretty-slot-name (class-var new-value-var) &body body)
  (let ((updater-name
	  (intern (format nil "UPDATE-~A" pretty-slot-name))))
    `(progn
       (declare-function-type ,updater-name (t t) (t))
       (defun ,updater-name (,class-var ,new-value-var)
	 ,@body)

       (setf (class-slot-description-updater ',pretty-slot-name)
	     #+development ',updater-name
	     #-development #',updater-name)
       ',updater-name)))

(def-substitution-macro get-class-slot-description-updater-if-any
    (pretty-slot-name)
  (class-slot-description-updater pretty-slot-name))

(defmacro class-slot-description-value (pretty-slot-name class)
  `(slot-init-form (slot-description-from-class ,class ,pretty-slot-name)))




;;; The function `change-class-slot-description-value' replaces the slot-init-form
;;; of a slot-description that has a class-specific-value feature with a new
;;; slot-init-form.  The function relies on the fact that slot descriptions with
;;; this feature do not share slot description memory with any other class.

(defun change-class-slot-description-value (pretty-slot-name class new-value)
  (let ((slot-description (slot-description-from-class class pretty-slot-name)))
    (reclaim-slot-value (slot-init-form slot-description))
    (setf (slot-init-form slot-description) (copy-for-slot-value new-value))))




;;; The `unoptimized sub-or-superclasses-path' was found to be a drag on
;;; performance because it omits the duplicate classes of multiple inheritance
;;; by checking each class for membership in a classes-visited flat list.  The
;;; new path, sub-or- superclasses-path, uses the class bit numbers of classes
;;; and a classes-visited byte vector to do the same task.  The unoptimized
;;; path is used only before the the class bit numbers are set up for the
;;; system-class hierarchy.

;;; The `unoptimized-subclasses-iteration-path', given a class, performs a
;;; breadth first traversal of the class-subclass hierarchy beneath and
;;; including the class itself, visiting each class once.  An example of this
;;; iteration path is:

;;; (loop for class being each subclass of 'block doing (print class)).

;;; In this case block will be printed followed by each of its children and then
;;; each of their children and so on.

;;; The `unoptimized-superclasses interation path', given a class, performs a
;;; breadth first traversal of the superclasses of class, visiting each class
;;; once.  Class is not a superclass of class.  Example:

;;; (loop for class being each superclass of 'variable collect class).

(defun-for-macro unoptimized-sub-or-superclasses-path
    (path-name variable data-type prep-phrases inclusive? allowed-prepositions data)
  (let ((bindings nil)
	(prologue nil)
	(argument-class (loop-gentemp))
	(traversal-state-variable (loop-gentemp))
	(current-classes-variable (loop-gentemp))
	(classes-visited (loop-gentemp))
	(more-classes (loop-gentemp)))
    
    ;; These variables are not used.
    data-type data allowed-prepositions
    
    ;; Warn of missing prepositional phrase.
    (if (null prep-phrases)
	(error "OF is missing in ~S iteration path of ~S" path-name variable))
    
    ;; Inclusive iteration is not supported.
    (if inclusive?
	(error "Inclusive stepping is not supported in ~S path of ~S (prep-prase = ~:S)"
	       path-name variable prep-phrases))

    #+development
    (test-assertion
      (member path-name
	      '(unoptimized-subclass unoptimized-subclasses
		unoptimized-superclasses unoptimized-superclass)))
    
    ;; Prepare bindings list for LOOP.
    (setq bindings
	  `((scope-conses scope-conses)
	    (,argument-class ,(second (assq 'of prep-phrases)))
	    (,traversal-state-variable nil)
	    (,classes-visited nil)
	    (,current-classes-variable nil)
	    (,variable nil)))

    ;; Note that this must be done here, rather than in the initial value of the
    ;; bindings above since the bindings expand into a let, rather than a let*,
    ;; and the call to scope-list must be made within the dynamic scope of the
    ;; new bindings of scope-conses.
    (setq prologue
	  `((setq ,current-classes-variable
		  ,(case path-name
		     ((unoptimized-subclass unoptimized-subclasses)
		      `(and (classp ,argument-class)
			    (scope-list ,argument-class)))
		     ((unoptimized-superclass unoptimized-superclasses)
		      `(direct-superior-classes ,argument-class))))))
    
    ;; Return the appropriate form. (See LOOP documentation)
    (list
      bindings
      prologue
      `(null ,current-classes-variable)
      nil					; steps
      nil					; post-step-endtest
      `(,variable				; pseudo-steps
	  (prog1 (car-of-cons ,current-classes-variable)
	    (setq ,classes-visited 
		  (scope-cons (car-of-cons ,current-classes-variable)
			      ,classes-visited))
	    (let ((,more-classes
		     ,(case path-name
			((unoptimized-subclass unoptimized-subclasses)
			 `(inferior-classes
			    (car-of-cons ,current-classes-variable)))
			((unoptimized-superclass unoptimized-superclasses)
			 `(direct-superior-classes
			    (car-of-cons ,current-classes-variable))))))
	      (when ,more-classes
		(setq ,traversal-state-variable
		      ;; Consider using a tail pointer.
		      (nconc
			,traversal-state-variable
			(scope-cons ,more-classes nil))))
	      (setq ,current-classes-variable
		    (cdr-of-cons ,current-classes-variable))
	      (loop with current-classes-variable-set = nil
		    until current-classes-variable-set
		    do
		(loop for sublist on ,current-classes-variable
		      for class-to-add = (car-of-cons sublist)
		      until (null sublist)
		      do
		  ;; The unless form prevents a class from being collected
		  ;; more than once and being collected before its superiors.
		  (unless (or (memq (car-of-cons sublist) ,classes-visited)
			      (loop for superior in (direct-superior-classes
						      class-to-add)
				    thereis
				    (and (subclassp superior ,argument-class)
					 (not (memq superior ,classes-visited)))))
		    (setq ,current-classes-variable sublist)
		    (setq current-classes-variable-set t)
		    (loop-finish))
		      finally
			(when (not current-classes-variable-set)
			  (progn
			    (setq ,current-classes-variable 
				  (car ,traversal-state-variable))
			    (if ,traversal-state-variable
				(setq ,traversal-state-variable
				      (cdr-of-cons ,traversal-state-variable))
				(setq current-classes-variable-set
				      t))))))))))))

(define-loop-path (unoptimized-subclasses unoptimized-subclass
					  unoptimized-superclasses unoptimized-superclass)
		  unoptimized-sub-or-superclasses-path (of))


(defun-for-macro potential-superior-definitions-path
    (path-name variable data-type prep-phrases inclusive? allowed-prepositions data)
  (let ((bindings nil)
	(prologue nil)
	(argument-class (loop-gentemp))
	(traversal-state-variable (loop-gentemp))
	(current-definitions-variable (loop-gentemp))
	(definitions-visited (loop-gentemp))
	(more-definitions (loop-gentemp)))
    
    ;; These variables are not used.
    data-type data allowed-prepositions
    
    ;; Warn of missing prepositional phrase.
    (if (null prep-phrases)
	(error "OF is missing in ~S iteration path of ~S" path-name variable))
    
    ;; Inclusive iteration is not supported.
    (if inclusive?
	(error "Inclusive stepping is not supported in ~S path of ~S (prep-prase = ~:S)"
	       path-name variable prep-phrases))

    #+development
    (test-assertion
      (member path-name
	      '(potential-superior-definition potential-superior-definitions)))
		
    
    ;; Prepare bindings list for LOOP.
    (setq bindings
	  `((scope-conses scope-conses)
	    (,argument-class ,(second (assq 'of prep-phrases)))
	    (,traversal-state-variable nil)
	    (,definitions-visited nil)
	    (,current-definitions-variable nil)
	    (,variable nil)))

    ;; Note that this must be done here, rather than in the initial value of the
    ;; bindings above since the bindings expand into a let, rather than a let*,
    ;; and the call to scope-list must be made within the dynamic scope of the
    ;; new bindings of scope-conses.
    (setq prologue
	  `((setq ,current-definitions-variable
		  (let ((class-definition (class-definition ,argument-class)))
		    (when (framep class-definition)
		      (loop for superior in (direct-superiors-of-defined-class
					      class-definition)
			    for superior-definition = (class-definition superior)
			    when (and (framep superior-definition)
				      (not (classp superior)))
			      collect superior-definition using scope-cons))))))
    
    ;; Return the appropriate form. (See LOOP documentation)
    (list
      bindings
      prologue
      `(null ,current-definitions-variable)
      nil					; steps
      nil					; post-step-endtest
      `(,variable				; pseudo-steps
	  (prog1 (car-of-cons ,current-definitions-variable)
	    (setq ,definitions-visited 
		  (scope-cons (car-of-cons ,current-definitions-variable)
			      ,definitions-visited))
	    (let ((,more-definitions
		     (loop for superior in (direct-superiors-of-defined-class
					     (car-of-cons ,current-definitions-variable))
			   for superior-definition = (class-definition superior)
			   when (and (framep superior-definition)
				     (not (classp superior)))
			     collect superior-definition using scope-cons)))
	      (when ,more-definitions
		(setq ,traversal-state-variable
		      ;; Consider using a tail pointer.
		      (nconc
			,traversal-state-variable
			(scope-cons ,more-definitions nil))))
	      (setq ,current-definitions-variable
		    (cdr-of-cons ,current-definitions-variable))
	      (loop with current-definitions-variable-set = nil
		    until current-definitions-variable-set
		    do
		(loop for sublist on ,current-definitions-variable
		      until (null sublist)
		      do
		  (when (not (memq (car-of-cons sublist) ,definitions-visited))
		    (setq ,current-definitions-variable sublist)
		    (setq current-definitions-variable-set t)
		    (loop-finish))
		      finally
			(when (not current-definitions-variable-set)
			  (progn
			    (setq ,current-definitions-variable 
				  (car ,traversal-state-variable))
			    (if ,traversal-state-variable
				(setq ,traversal-state-variable
				      (cdr-of-cons ,traversal-state-variable))
				(setq current-definitions-variable-set
				      t))))))))))))

(define-loop-path (potential-superior-definition potential-superior-defintions)
		  potential-superior-definitions-path (of))


(defun-for-macro potential-definitions-path
    (path-name variable data-type prep-phrases inclusive? allowed-prepositions data)
  (let ((bindings nil)
	(prologue nil)
	(argument-class (loop-gentemp))
	(traversal-state-variable (loop-gentemp))
	(current-definitions-variable (loop-gentemp))
	(definitions-visited (loop-gentemp))
	(more-definitions (loop-gentemp)))
    
    ;; These variables are not used.
    data-type data allowed-prepositions
    
    ;; Warn of missing prepositional phrase.
    (if (null prep-phrases)
	(error "OF is missing in ~S iteration path of ~S" path-name variable))
    
    ;; Inclusive iteration is not supported.
    (if inclusive?
	(error "Inclusive stepping is not supported in ~S path of ~S (prep-prase = ~:S)"
	       path-name variable prep-phrases))

    ;; Prepare bindings list for LOOP.
    (setq bindings
	  `((scope-conses scope-conses)
	    (,argument-class ,(second (assq 'of prep-phrases)))
	    (,traversal-state-variable nil)
	    (,definitions-visited nil)
	    (,current-definitions-variable nil)
	    (,variable nil)))

    ;; Note that this must be done here, rather than in the initial value of the
    ;; bindings above since the bindings expand into a let, rather than a let*,
    ;; and the call to scope-list must be made within the dynamic scope of the
    ;; new bindings of scope-conses.
    (setq prologue
	  `((setq ,current-definitions-variable
		  (potential-inferior-class-definitions ,argument-class))))
    
    ;; Return the appropriate form. (See LOOP documentation)
    (list
      bindings
      prologue
      `(null ,current-definitions-variable)
      nil					; steps
      nil					; post-step-endtest
      `(,variable				; pseudo-steps
	  (prog1 (car-of-cons ,current-definitions-variable)
	    (setq ,definitions-visited 
		  (scope-cons (car-of-cons ,current-definitions-variable)
			      ,definitions-visited))
	    (let ((,more-definitions
		     (potential-inferior-class-definitions
		       (name-of-defined-class (car-of-cons ,current-definitions-variable)))))
	      (when ,more-definitions
		(setq ,traversal-state-variable
		      ;; Consider using a tail pointer.
		      (nconc
			,traversal-state-variable
			(scope-cons ,more-definitions nil))))
	      (setq ,current-definitions-variable
		    (cdr-of-cons ,current-definitions-variable))
	      (loop with current-definitions-variable-set = nil
		    until current-definitions-variable-set
		    do
		(loop for sublist on ,current-definitions-variable
		      until (null sublist)
		      do
		  (when (not (memq (car-of-cons sublist) ,definitions-visited))
		    (setq ,current-definitions-variable sublist)
		    (setq current-definitions-variable-set t)
		    (loop-finish))
		      finally
			(when (not current-definitions-variable-set)
			  (progn
			    (setq ,current-definitions-variable 
				  (car ,traversal-state-variable))
			    (if ,traversal-state-variable
				(setq ,traversal-state-variable
				      (cdr-of-cons ,traversal-state-variable))
				(setq current-definitions-variable-set
				      t))))))))))))

(define-loop-path (potential-definition potential-defintions)
		  potential-definitions-path (of))

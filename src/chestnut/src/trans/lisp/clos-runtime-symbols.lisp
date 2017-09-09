;;; -*- Mode: Lisp; Package: HOST; Syntax: Common-Lisp -*-
;;;
;;; Copyright (C) 1991 Chestnut Software, Inc.  All Rights Reserved.
;;;

(in-package "HOST")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/clos-runtime-symbols.lisp,v $"
 "$Revision: 1.1 $"
 "$Date: 2006/02/28 21:59:01 $")

(himpl:define-symbols :host t

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Symbols in the TX package
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	
("CALL-COMBINED-METHOD"
    (:symbol
        :package "TCLOSX"
	:export ("TCLOSX" "TX")
	:import-from nil
	)
    (:macro)
    )

("COMBINE-METHODS"
    (:symbol
        :package "TCLOSX"
	:export ("TCLOSX" "TX")
	:import-from nil
	)
    (:macro)
    )

("DEFINE-METHOD-COMBINATION-FUNCTION"
    (:symbol
        :package "TCLOSX"
	:export ("TCLOSX" "TX")
	:import-from nil
	)
    (:macro)
    )

("LOCAL-METHOD"
    (:symbol
        :package "TCLOSX"
	:export ("TCLOSX" "TX")
	:import-from nil
	)
    (:macro)
    ;; CAR of list returned by executing expansion of the macro.
    (:random-syntax)
    )

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Symbols in the TCLOSX package
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

("ADD-DIRECT-SUBCLASS"
    (:symbol
        :package "TCLOSX"
	:import-from nil
	)
    ;; Record subclass as a direct subclass of class.
    (:function
        :lambda-list (class subclass)
	:return-type class
	:generic-function t
	)
    )

("CLASS-DEFAULT-SUPERCLASSES"
    (:symbol
        :package "TCLOSX"
	:import-from nil
	)
    ;; ***
    (:function
        :lambda-list (class)
	:return-type list
	:generic-function t
	)
    )

("CLASS-FINALIZED-P"
    (:symbol
        :package "TCLOSX"
	:import-from nil
	)
    ;; Predicate which returns true if the class has been finalized.
    (:function
        :lambda-list (class)
	:return-type t
	:generic-function t
	)
    )

("COMPUTE-CLASS-DEFAULT-INITARGS"
    (:symbol
        :package "TCLOSX"
	:import-from nil
	)
    ;; Return a list of the default initarg specifiers for the class,
    ;; collecting them from the class and its superclasses.
    (:function
        :lambda-list (class)
	:return-type list
	:generic-function t
	)
    )

("COMPUTE-CLASS-PRECEDENCE-LIST"
    (:symbol
        :package "TCLOSX"
	:import-from nil
	)
    ;; Compute the class precedence list of the class.
    (:function
        :lambda-list (class)
	:return-type list
	:generic-function t
	)
    )

("COMPUTE-EFFECTIVE-SLOT-DEFINITION"
    (:symbol
        :package "TCLOSX"
	:import-from nil
	)
    ;; Return an effective-slot-definition metaobject based on the
    ;; corresponding direct slot definitions.
    (:function
        :lambda-list (class name direct-slotds)
	:return-type list
	:generic-function t
	)
    )

("COMPUTE-EFFECTIVE-SLOT-DEFINITION-INITARGS"
    (:symbol
        :package "TCLOSX"
	:import-from nil
	)
    ;; Compute an initarg list for a call to make-instance for the class of
    ;; the slotd from the direct slot definitions.  The slotd argument is
    ;; typically the class prototype of the effective slot definition class.
    (:function
        :lambda-list (slotd direct-slotds)
	:return-type list
	:generic-function t
	)
    )

("COMPUTE-METHOD-COMBINATION"
    (:symbol
        :package "TCLOSX"
	:import-from nil
	)
    ;; Return a method-combination metaobject determined by the name and
    ;; options.  Name must be a method-combination type name.  Options are
    ;; arguments to be passed to the method-combination function.  The object
    ;; returned may be EQ to some previously computed method-combination
    ;; metaobject, or it may be freshly created.
    (:function
        :lambda-list (name options)
	:return-type method-combination
	)
    )

("COMPUTE-SLOTS"
    (:symbol
        :package "TCLOSX"
	:import-from nil
	)
    ;; Compute the effective slot definitions for class.
    (:function
        :lambda-list (class)
	:return-type list
	:generic-function t
	)
    )

("DEFAULT-INITARGS"
    (:symbol
        :package "TCLOSX"
	:import-from nil
	)
    ;; Augment the specified initargs with the default initargs for the class,
    ;; returning the augmented list.  The defaulted initargs will appear after
    ;; the provided initargs in the resulting list.  The order in which the
    ;; defaulted initargs appear is the same as the order in which the
    ;; corresponding entries appear in the default initargs list.
    (:function
        :entry-name "default_initargs"
	:lambda-list (prototype initargs)
	:return-type list
	:generic-function t
	)
    )

("DIRECT-SLOT-DEFINITION"
    (:symbol
        :package "TCLOSX"
	:import-from nil
	)
    (:class-name)
    (:type-name)
    )

("DIRECT-SLOT-DEFINITION-CLASS"
    (:symbol
        :package "TCLOSX"
	:import-from nil
	)
    ;; Determine the subclass of direct-slot-definition to use for the
    ;; specified class and slot specification.
    ;; (This differs from the Art of MOP, which gives this function the
    ;; syntax "direct-slot-definition-class class &rest initargs").
    (:function
        :lambda-list (class slot-specification)
	:return-type class
	:generic-function t
	)
    )

("EFFECTIVE-SLOT-DEFINITION"
    (:symbol
        :package "TCLOSX"
	:import-from nil
	)
    (:class-name)
    (:type-name)
    )

("EFFECTIVE-SLOT-DEFINITION-CLASS"
    (:symbol
        :package "TCLOSX"
	:import-from nil
	)
    ;; Determine the subclass of effective-slot-definition to use for the
    ;; specified class and direct slot definition metaobjects.
    ;; (This differs from the Art of MOP, which gives this function the
    ;; syntax "effective-slot-definition-class class &rest initargs").
    (:function
        :lambda-list (class direct-slotds)
	:return-type class
	:generic-function t
	)
    )

("ELIDE-ACCESS-METHOD-P"
    (:symbol
        :package "TCLOSX"
	:import-from nil
	)
    ;; This function is part of the slot access protocol.  It is called on
    ;; each effective slot-definition object for a class when the class is
    ;; finalized.  If it returns true, then the specified type of slot access
    ;; may be optimized in such a way that the underlying generic-functions for
    ;; the access might not be called.
    ;;
    ;; Access-type must be either :READ (which affects calls to SLOT-VALUE and
    ;; SLOT-BOUNDP) or :WRITE (which affects SETF of SLOT-VALUE and
    ;; SLOT-MAKUNBOUND).
    (:function
        :lambda-list (class slotd access-type)
	:return-type t
	:generic-function t
	)
    )

("FINALIZE-INHERITANCE"
    (:symbol
        :package "TCLOSX"
	:import-from nil
	)
    ;; ***
    (:function
        :lambda-list (class)
	:return-type t
	:generic-function t
	)
    )

("FIND-EFFECTIVE-SLOT-DEFINITION"
    (:symbol
        :package "TCLOSX"
	:import-from nil
	)
    ;; Return the effective slot-definition for class with the specified name,
    ;; or Nil if no such slot is present in instances of the class.  This could
    ;; be defined as
    ;;
    ;;   (defun find-effective-slot-definition (class slot-name)
    ;;     (car (member slot-name (class-slots class)
    ;;                  :key #'slot-definition-name)))
    (:function
        :lambda-list (class slot-name)
	:return-type t
	)
    )

("INTERNAL-STANDARD-CLASS"
    (:symbol
        :package "TCLOSX"
	:import-from nil
	)
    (:class-name)
    (:type-name)
    )

("LOCAL-SLOT-DEFINITION-P"
    (:symbol
        :package "TCLOSX"
	:import-from nil
	)
    ;; Predicate which returns true if the effective slot definition is for a
    ;; local (:instance) slot.
    (:function
        :lambda-list (slot-definition)
	:return-type t
	:generic-function t
	)
    )

("METHOD-CLASS"
    (:symbol
        :package "TCLOSX"
	:import-from nil
	)
    ;; Name of metaclass for METHOD.
    (:class-name)
    (:type-name)
    )

("NO-PRIMARY-METHOD"
    (:symbol
        :package "TCLOSX"
	:import-from nil
	)
    (:function
        :lambda-list (generic-function &rest arguments)
	:return-type t
	:generic-function t
	)
    )

("OPTIMIZE-SLOT-ACCESS"
    (:symbol
        :package "TCLOSX"
	:import-from nil
	)
    ;; This function is called as part of class finalization.
    ;; Its purpose is to initialize any data structures needed to support
    ;; optimized slot accesses on instances of the class of the indicated slot.
    (:function
        :lambda-list (class slotd)
	:return-type t
	:generic-function t
	)
    )

("OPTIMIZE-SLOT-ACCESSES"
    (:symbol
        :package "TCLOSX"
	:import-from nil
	)
    ;; Optimize accesses for each slot in the class.
    (:function
        :lambda-list (class)
	:return-type t
	:generic-function t
	)
    )

("REMOVE-DIRECT-SUBCLASS"
    (:symbol
        :package "TCLOSX"
	:import-from nil
	)
    ;; Remove record that subclass is a direct subclass of class.
    (:function
        :lambda-list (class subclass)
	:return-type class
	:generic-function t
	)
    )

("SHARED-SLOT-DEFINITION-P"
    (:symbol
        :package "TCLOSX"
	:import-from nil
	)
    ;; Predicate which returns true if the effective slot definition is for a
    ;; shared (:class) slot.
    (:function
        :lambda-list (slot-definition)
	:return-type t
	:generic-function t
	)
    )

("STANDARD-DIRECT-SLOT-DEFINITION"
    (:symbol
        :package "TCLOSX"
	:import-from nil
	)
    (:class-name)
    (:type-name)
    )

("STANDARD-EFFECTIVE-LOCAL-SLOT-DEFINITION"
    (:symbol
        :package "TCLOSX"
	:import-from nil
	)
    (:class-name)
    (:type-name)
    )

("STANDARD-EFFECTIVE-SHARED-SLOT-DEFINITION"
    (:symbol
        :package "TCLOSX"
	:import-from nil
	)
    (:class-name)
    (:type-name)
    )

("STANDARD-EFFECTIVE-SLOT-DEFINITION"
    (:symbol
        :package "TCLOSX"
	:import-from nil
	)
    (:class-name)
    (:type-name)
    )

("VALIDATE-SUPERCLASS"
    (:symbol
        :package "TCLOSX"
	:import-from nil
	)
    ;; ***
    (:function
        :lambda-list (class super)
	:return-type t
	:generic-function t
	)
    )

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Symbols in the TCLOS-RUN package
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

("*GENERIC-FUNCTION-FOR-METHOD-COMBINATION-ERRORS*"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	)
    ;; Dynamic variable bound around the body of a method-combination function
    ;; so that TCL:METHOD-COMBINATION-ERROR and TCL:INVALID-METHOD-ERROR will
    ;; have available the generic-function for which the effective method is
    ;; being computed.
    (:variable
        :return-type t
	;; :initial-value nil
	)
    )

("*METHOD-COMBINATION-EFFECTIVE-METHOD*"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	)
    ;; Dynamic variable bound around the body of a method-combination function
    ;; to the effective-method object being initialized.
    (:variable
        :return-type t
	;; :initial-value nil
	)
    )

("*METHOD-COMBINATION-FOR-METHOD-COMBINATION-ERRORS*"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	)
    ;; Dynamic variable bound around the body of a method-combination function
    ;; so that TCL:METHOD-COMBINATION-ERROR and TCL:INVALID-METHOD-ERROR will
    ;; have available the method-combination for which the effective method is
    ;; being computed.
    (:variable
        :return-type t
	;; :initial-value nil
	)
    )

("ADD-NAMED-CLASS"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	)
    ;; This function is used in the expansion of DEFCLASS.  It accepts keyword
    ;; arguments similar to those accepted by ENSURE-CLASS, but specialized to
    ;; deal with the requirements of DEFCLASS.  Principle difference is in the
    ;; defaulting behavior when the class already exists.
    (:function
        :lambda-list (name &rest keys)
	:return-type class
	)
    )

("ADD-NAMED-GENERIC-FUNCTION"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	)
    ;; This function is used in the expansion of DEFGENERIC.  It accepts
    ;; keyword arguments similar to those taken by ENSURE-GENERIC-FUNCTION, but
    ;; specialized to deal with the requirements of DEFGENERIC and DEFMETHOD.
    (:function
        :lambda-list (name &rest keys)
	:return-type generic-function
	)
    )

("ADD-NAMED-METHOD"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	)
    ;; This function is used in the implementation of method defining forms.
    ;; Name is either the name of the generic-function to which the method is
    ;; being added, or the actual generic-function object.  Function is the
    ;; method-function for the method.  The keywords specify how the method is
    ;; to be created.  In general, the keywords specify initargs for a call to
    ;; make-instance, with the method class determined from the named
    ;; generic-function.  However, the initarg :method-class may be supplied,
    ;; in which case it overrides the class specified by the generic-function.
    ;; This initarg is not included in the initargs to the call to
    ;; make-instance.
    (:function
        :lambda-list (name function &rest keys)
	:return-type method
	)
    )

("ALLOCATION"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:symbol-name "SI_Qallocation"
	)
    ;; Slot name from SLOT-DEFINITION.
    (:slot-name
        :index-name "SI_Sallocation"
	)
    )

("ARGUMENT-PRECEDENCE-MAP"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:symbol-name "SI_Qargument_precedence_map"
	)
    ;; Slot name for GENERIC-FUNCTION.
    (:slot-name
        :index-name "SI_Sargument_precedence_map"
	)
    )

("ARGUMENT-PRECEDENCE-ORDER"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:symbol-name "SI_Qargument_precedence_order"
	)
    ;; Slot name for GENERIC-FUNCTION.
    (:slot-name
        :index-name "SI_Sargument_precedence_order"
	)
    )

("ARGUMENTS"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:symbol-name "SI_Qarguments"
	)
    ;; Lambda-list entry for some generic functions.
    (:random-syntax)
    )

("%ASSIGN-SLOT-INDEX"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "ASSIGN_SLOT_INDEX"
	:lambda-list (name index)
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :void
	)
    )

("%CALL-NEXT-METHOD"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:exists-at-runtime nil
	)
    ;; This function is the primitive used to implement the standard method
    ;; body function CALL-NEXT-METHOD.  It first checks whether a next-method
    ;; is available, and either calls the next method or arranges to call the
    ;; generic-function NO-NEXT-METHOD if none exists.  It returns whatever the
    ;; called method or function returns.
    (:function
        :entry-name "CALL_NEXT_METHOD"
        :lambda-list (effective-method method-index frame argq)
	:return-type (values &rest t)
	:foreign-protocol :foreign-arguments-function
	:foreign-arguments
	    ((:object t) (:object t) (:object t) (:object t))
	:foreign-return-type :object
	)
    )

("%CALL-NEXT-METHOD-ARGUMENTS"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:exists-at-runtime nil
	)
    ;; ***
    (:function
        :entry-name "call_next_method"
        :lambda-list (n effective-method method-index &rest arguments)
	:return-type (values &rest t)
	:foreign-protocol :foreign-arguments-function
	:foreign-arguments ((:int nil) (:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("CLASS-FULLY-DEFINED-P"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	)
    ;; Predicate which returns true if the class is fully defined.
    (:function
        :lambda-list (class)
	:return-type t
	:generic-function t
	)
    )

("CLASS-STATUS-BITS"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	)
    ;; Reader function for CLASS
    (:function
        :lambda-list (class)
	:return-type integer
	:generic-function t
	)
    ;; Writer function for CLASS
    (:setf-function
        :lambda-list (value class)
	:return-type integer
	:generic-function t
	)
    (:setf-place
        :setf-function t
	)
    )

("%CLASS-STATUS-P"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:exists-at-runtime nil
	)
    ;; Predicate which returns true if any of the bits in the mask are set in
    ;; the status bits of the class.  This is essentially the same as
    ;; TRUEP(logtest(class_status_bits(class), mask)).
    (:function
        :entry-name "class_status_p"
	:lambda-list (class mask)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :boolean
	)
    )

("%CLASS-TYPEP"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:exists-at-runtime nil
	)
    ;; Predicate function used by typep optimizer.
    ;; The class argument must be either a class or a class name.
    (:function
        :entry-name "CLASS_TYPEP"
	:lambda-list (object class)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :boolean
	)
    )

("COMPUTE-CLASS-PROTOTYPE"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	)
    ;; Compute the prototype object for the class.  This is used by both
    ;; class-prototype and allocate-instance.
    (:function
        :lambda-list (class)
	:return-type t
	:generic-function t
	)
    )

("COMPUTE-SLOT-DEFINITION-LOCATION"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	)
    ;; ***
    (:function
        :lambda-list (class slotd)
	:return-type t
	:generic-function t
	)
    )

("COMPUTE-SLOT-DEFINITION-LOCATIONS"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	)
    ;; Computes and assigns the locations of the slot definitions in the list,
    ;; using compute-slot-definition-location and set-slot-definition-location.
    (:function
        :lambda-list (class slotds)
	:return-type list
	:generic-function t
	)
    )

("COMPUTE-VALID-CHANGE-CLASS-INITARGS"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	)
    ;; Compute valid change-class initargs by merging slot-initargs with
    ;; explicitly mentioned keywords from applicable methods on
    ;; update-instance-for-different-class, shared-initialize (and change-class
    ;; if it is changed to accept initargs).  If any applicable methods specify
    ;; &allow-other-keys, then return T instead of a merged list, indicating
    ;; that any keywords are valid.
    (:function
        :lambda-list (class)
	:return-type t
	:generic-function t
	)
    )

("COMPUTE-VALID-CREATION-INITARGS"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	)
    ;; Compute valid creation initargs by merging slot-initargs with
    ;; explicitly mentioned keywords from applicable methods on
    ;; allocate-instance, initialize-instance, and shared-initialize.  If any
    ;; applicable methods specify &allow-other-keys, then return T instead of a
    ;; merged list, indicating that any keywords are valid.
    (:function
        :lambda-list (class)
	:return-type t
	:generic-function t
	)
    )

("COMPUTE-VALID-REINITIALIZATION-INITARGS"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	)
    ;; Compute valid reinitialization initargs by merging slot-initargs with
    ;; explicitly mentioned keywords from applicable methods on
    ;; reinitialize-instance and shared-initialize.  If any applicable methods
    ;; specify &allow-other-keys, then return T instead of a merged list,
    ;; indicating that any keywords are valid.
    (:function
        :lambda-list (class);
	:return-type t
	:generic-function t
	)
    )

("CONSTANT-INITFORM-P"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	)
    ;; Slot name from SLOT-DEFINITION.
    (:slot-name
        :index-name "SI_Sconstant_initform_p"
	)
    ;; Initarg for SLOT-DEFINITION.
    (:random-syntax)
    )

("CONSTANTLY-ZERO-INITFUNCTION"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	)
    ;; Function of no arguments returning ZERO.
    ;; Used as initfunction for some early classes.
    (:function
        :lambda-list ()
	:return-type fixnum
	)
    )

("%COPY-METHOD-FRAME"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:exists-at-runtime nil
	)
    ;; Returns a heap allocated frame with the same contents as the argument.
    (:function
        :entry-name "COPY_METHOD_FRAME"
        :lambda-list (frame)
	:return-type t
	:state-changing nil
	:state-using nil
	:foreign-protocol :macro
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	)
    )

("CRITICAL-METHODS"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:symbol-name "SI_Qcritical_methods"
	)
    ;; Slot name for GENERIC-FUNCTION.
    (:slot-name
        :index-name "SI_Scritical_methods"
	)
    )

("DECLARATIONS"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:symbol-name "SI_Qdeclarations"
	)
    ;; Slot name for GENERIC-FUNCTION.
    (:slot-name
        :index-name "SI_Sdeclarations"
	)
    )

("DIRECT-DEFAULT-INITARGS"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:symbol-name "SI_Qdirect_default_initargs"
	)
    ;; Slot name for CLASS.
    (:slot-name
        :index-name "SI_Sdirect_default_initargs"
	)
    )

("DIRECT-SLOTS"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:symbol-name "SI_Qdirect_slots"
	)
    ;; Slot name for CLASS.
    (:slot-name
        :index-name "SI_Sdirect_slots"
	)
    )

("DIRECT-SUBCLASSES"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:symbol-name "SI_Qdirect_subclasses"
	)
    ;; Slot name for CLASS.
    (:slot-name
        :index-name "SI_Sdirect_subclasses"
	)
    )

("DIRECT-SUPERCLASSES"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:symbol-name "SI_Qdirect_superclasses"
	)
    ;; Slot name for CLASS.
    (:slot-name
        :index-name "SI_Sdirect_superclasses"
	)
    )

("DISPLAY-CACHE-STATISTICS"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	)
    ;; Print statistics about generic function cache mechanism to stream.
    ;; Stream is a stream designator.
    (:function
        :lambda-list (&optional stream)
	:return-type t
	)
    )

("DOC-STRING"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:symbol-name "SI_Qdoc_string"
	)
    ;; Slot name for METAOBJECT.
    (:slot-name
        :index-name "SI_Sdoc_string"
	)
    )

("%EFFECTIVE-METHOD-ALLOW-OTHER-KEYS-P"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:exists-at-runtime nil
	)
    ;; Reader for EFFECTIVE-METHOD.
    ;; Returns true if &ALLOW-OTHER-KEYS was specified by the generic function
    ;; or any of the applicable methods that make up the effective method.
    (:function
        :entry-name "EFFECTIVE_METHOD_ALWKYP"
	:lambda-list (effective-method)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :boolean
	)
    )

("EFFECTIVE-METHODS"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:symbol-name "SI_Qeffective_methods"
	)
    ;; Slot name from GENERIC-FUNCTION.
    (:slot-name
        :index-name "SI_Seffective_methods"
	)
    )

("%EFFECTIVE-METHOD-CALL"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:exists-at-runtime nil
	)
    ;; Primitive for invoking a method using the effective-method and index.
    (:function
        :entry-name "EFFECTIVE_METHOD_CALL"
        :lambda-list (effective-method method-index frame argq)
	:return-type t
	:foreign-protocol :foreign-arguments-function
	:foreign-arguments
	    ((:object t) (:object t) (:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("%EFFECTIVE-METHOD-KEYP"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:exists-at-runtime nil
	)
    ;; Reader for the KEYP field of EFFECTIVE-METHOD.
    ;; Returns true if &KEY was specified by the generic function or any of the
    ;; applicable methods that make up the effective method.
    (:function
        :entry-name "EFFECTIVE_METHOD_KEYP"
	:lambda-list (effective-method)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :boolean
	)
    )

("%EFFECTIVE-METHOD-KEYS"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:exists-at-runtime nil
	)
    ;; Reader for the KEYS field of EFFECTIVE-METHOD.
    (:function
        :entry-name "EFFECTIVE_METHOD_KEYS"
        :lambda-list (effective-method)
	:return-type (or null simple-vector)
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	)
    )

("%EFFECTIVE-METHOD-KEYWORD-PERMUTATION"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:exists-at-runtime nil
	)
    ;; Returns the keyword permutation vector for the specified method.
    ;; A value of Nil indicates that the method does not use a permutation
    ;; vector.  Callers must ensure that the KEY-TABLE entry in the
    ;; effective-method contains a vector before calling this function.
    (:function
        :entry-name "EFFECTIVE_METHOD_KEYWORD_PERMUTATION"
        :lambda-list (effective-method method-index)
	:return-type (or null simple-vector)
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("%EFFECTIVE-METHOD-POSITIONAL"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:exists-at-runtime nil
	)
    ;; Reader for the POSITIONAL field of EFFECTIVE-METHOD.
    (:function
        :entry-name "EFFECTIVE_METHOD_POSITIONAL"
        :lambda-list (effective-method)
	:return-type fixnum
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	)
    )

("%EFFECTIVE-METHOD-REQUIRED"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:exists-at-runtime nil
	)
    ;; Reader for the REQUIRED field of EFFECTIVE-METHOD.
    (:function
        :entry-name "EFFECTIVE_METHOD_REQUIRED"
        :lambda-list (effective-method)
	:return-type fixnum
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	)
    )

("%EFFECTIVE-METHOD-RESTP"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:exists-at-runtime nil
	)
    ;; Reader for the RESTP field of EFFECTIVE-METHOD.
    ;; It returns true if the effective-method permits non-positional
    ;; arguments, and Nil otherwise.
    (:function
        :entry-name "EFFECTIVE_METHOD_RESTP"
        :lambda-list (effective-method)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	)
    )

("ENCODED-LAMBDA-LIST"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	)
    ;; Slot name from GENERIC-FUNCTION and METHOD.
    (:slot-name
        :index-name "SI_Sencoded_lambda_list"
	)
    )

("ENSURE-CLASS"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	)
    ;; ***
    (:function
        :lambda-list (name &rest initargs)
	:return-type class
	)
    )

("EQL-SPECIALIZED-METHODS"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:symbol-name "SI_Qeql_specialized_methods"
	)
    ;; Slot name from GENERIC-FUNCTION.
    (:slot-name
        :index-name "SI_Seql_specialized_methods"
	)
    )

("%ESTABLISH-GENERIC-FUNCTION"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:exists-at-runtime nil
	)
    ;; Pseudo-function to make this look like a function to codewalkers using
    ;; the environment access functions.  This thing is *really* a special
    ;; form that only does something in a toplevel context.  The name must be
    ;; a constant.
    (:function
        :lambda-list (name)
	:foreign-protocol :macro
	:foreign-return-type :void
	)
    (:special-form)
    )

("%FINALIZE-EFFECTIVE-METHOD"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:exists-at-runtime nil
	)
    ;; Called within the expansion of a define-method-combination-function form
    ;; to complete the creation of a effective-method.  The arguments are the
    ;; effective-method object being finalized and the index of the first
    ;; method to call when invoking the effective-method.
    (:function
        :entry-name "finalize_effective_method"
        :lambda-list (effective-method start-index)
	:return-type t
	:foreign-protocol :foreign-arguments-function
	:foreign-arguments ((:object nil) (:object nil))
	:return-type :object
	)
    )

("FIND-INSTANCE-KEYWORD"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	)
    ;; Provides the function object for the initfunction for the allocation
    ;; slot of slot definitions.
    (:function
        :lambda-list ()
	:return-type class
	)
    )

("FIND-STANDARD-METHOD-CLASS"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	)
    ;; Provides the function object for the initfunction for the method-class
    ;; slot of generic functions.
    (:function
        :lambda-list ()
	:return-type class
	)
    )

("FIND-STANDARD-METHOD-COMBINATION"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	)
    ;; Provides the function object for the initfunction for the
    ;; method-combination slot of generic functions.
    (:function
	:lambda-list ()
	:return-type method-combination
	)
    )

("GENERIC-FUNCTION"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:symbol-name "SI_Qgeneric_function"
	)
    ;; Slot name for METHOD.
    (:slot-name
        :index-name "SI_Sgeneric_function"
	)
    )

("INITARGS"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:symbol-name "SI_Qinitargs"
	)
    ;; Slot name from SLOT-DEFINITION.
    ;; Slot name from CLASS.
    (:slot-name
        :index-name "SI_Sinitargs"
	)
    )

("INITFORM"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:symbol-name "SI_Qinitform"
	)
    ;; Slot name for SLOT-DEFINITION
    (:slot-name
        :index-name "SI_Sinitform"
	)

    )

("INITFUNCTION"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:symbol-name "SI_Qinitfunction"
	)
    ;; Slot name for SLOT-DEFINITION
    (:slot-name
        :index-name "SI_Sinitfunction"
	)
    )

("%INITIAL-CLASS-INFO"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:exists-at-runtime nil
	)
    ;; This variable is initialized to contain information about the predefined
    ;; class hierarchy, for bootstrapping it at runtime.
    (:variable
        :variable-name "SI_Initial_class_info"
	:return-type list
	:dump-definition-p nil
	)
    )

("%INITIAL-GENERIC-FUNCTION-INFO"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:exists-at-runtime nil
	)
    ;; This variable is initialized to contain information about the predefined
    ;; generic functions, for bootstrapping them at runtime.
    (:variable
        :variable-name "SI_Initial_generic_function_info"
	:return-type list
	:dump-definition-p nil
	)
    )

("INITIAL-METHODS"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:symbol-name "SI_Qinitial_methods"
	)
    ;; Slot name for GENERIC-FUNCTION.
    (:slot-name
        :index-name "SI_Sinitial_methods"
	)
    )

("%INITIALIZE-SLOT-INDEX-TABLE"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:exists-at-runtime nil
	)
    ;; ***
    (:function
        :entry-name "SI_init_slot_index_table"
	:lambda-list ()
	:foreign-protocol :macro
	:foreign-arguments ()
	:foreign-return-type :void
	)
    )

("%INSTANCE-WRAPPER"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:exists-at-runtime nil
	)
    ;; Get the class wrapper from an instance.
    (:function
        :entry-name "INSTANCE_WRAPPER"
        :lambda-list (object)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	)
    )

("KERNEL-GENERIC-FUNCTION"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	)
    (:class-name)
    (:type-name)
    )

("KEYWORD-PARAMETER-MAP"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:symbol-name "SI_Qkeyword_parameter_map"
	)
    ;; Slot name for METHOD.
    (:slot-name
        :index-name "SI_Skeyword_parameter_map"
	)
    )

("LAMBDA-LIST"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:symbol-name "SI_Qlambda_list"
	)
    ;; Slot name for GENERIC-FUNCTION and METHOD.
    (:slot-name
        :index-name "SI_Slambda_list"
	)
    )

("LOCATION"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:symbol-name "SI_Qlocation"
	)
    ;; Slot name from EFFECTIVE-SLOT-DEFINITION.
    (:slot-name
        :index-name "SI_Slocation"
	)
    )

("%MAKE-CALL-NEXT-METHOD-SAFE"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:exists-at-runtime nil
	)
    ;; This function returns a closure over the arguments which implements
    ;; the general form of call-next-method.  It could be defined as
    ;;
    ;; (defun make-call-next-method-safe
    ;;         (effective-method method-index frame argq)
    ;;   (flet ((call-next-method-safe (&rest arguments)
    ;;            (declare (dynamic-extent arguments))
    ;;            (if (atom arguments)
    ;;                (tclos-run:call-next-method
    ;;                     effective-method method-index frame argq)
    ;;                (progn
    ;;                  (tclos-run:check-call-next-method-arguments
    ;;                      effective-method method-index frame argq arguments)
    ;;                  (tclos-run:call-next-method-list
    ;;                      effective-method method-index arguments)))))
    ;;     #'call-next-method-safe))
    (:function
	:entry-name "make_call_next_method_safe"
        :lambda-list (effective-method method-index frame argq)
	:return-type function
	:state-changing nil
	:state-using nil
	:foreign-protocol :foreign-arguments-function
	:foreign-arguments
	    ((:object nil) (:object nil) (:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("%MAKE-CALL-NEXT-METHOD-UNSAFE"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:exists-at-runtime nil
	)
    ;; This function returns a closure over the arguments which implements
    ;; the downward form of call-next-method.  It could be defined as
    ;;
    ;; (defun make-call-next-method-unsafe
    ;;         (effective-method method-index frame argq)
    ;;   (flet ((call-next-method (&rest arguments)
    ;;            (declare (dynamic-extent arguments))
    ;;            (if (atom arguments)
    ;;                (tclos-run:call-next-method
    ;;                     effective-method method-index frame argq)
    ;;                (tclos-run:call-next-method-list
    ;;                     effective-method method-index arguments))))
    ;;     #'call-next-method))
    (:function
        :entry-name "make_call_next_method"
        :lambda-list (effective-method method-index frame argq)
	:return-type function
	:state-changing nil
	:state-using nil
	:foreign-protocol :foreign-arguments-function
	:foreign-arguments
	    ((:object nil) (:object nil) (:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("%MAKE-EFFECTIVE-METHOD"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:exists-at-runtime nil
	)
    ;; Allocate and return a new effective-method object.
    (:function
	:entry-name "make_effective_method"
        :lambda-list (generic-function methods)
	:return-type trun:effective-method
	:state-using nil
	:state-changing nil
	:foreign-protocol :foreign-arguments-function
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("MAKE-GENERIC-FUNCTION"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	)
    ;; Function used by ENSURE-GENERIC-FUNCTION and by GENERIC-FLET and friends
    ;; to create a new generic-function.
    (:function
        :lambda-list (name &rest initargs)
	:return-type generic-function
	)
    )

("%MAKE-INSTANCES-OBSOLETE-SLOTS-TO-FLUSH"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:exists-at-runtime nil
	)
    ;; This variable is initialized to contain a list of slot names whose
    ;; corresponding slots are to be reinitialized by make-instances-obsolete.
    (:variable
        :variable-name "SI_Make_instances_obsolete_slots_to_flush"
	:return-type list
	:dump-definition-p nil
	)
    )

("%MAKE-NEXT-METHOD-P"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:exists-at-runtime nil
	)
    ;; This function returns a closure over the arguments which implements
    ;; the general form of next-method-p.  It could be defined as
    ;;
    ;; (defun make-next-method-p (effective-method method-index)
    ;;   (flet ((next-method-p ()
    ;;            (tclos-run:next-method-p effective-method method-index)))
    ;;     #'next-method-p))
    (:function
	:entry-name "make_next_method_p"
        :lambda-list (effective-method method-index)
	:return-type function
	:state-using nil
	:state-changing nil
	:foreign-protocol :foreign-arguments-function
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("METAOBJECT"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	)
    (:class-name)
    (:type-name)
    )

("METAOBJECT-DOCUMENTATION"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	)
    ;; Reader function for the DOC-STRING slot of METAOBJECT.
    ;; Used by methods on the DOCUMENTATION generic-function.
    (:function
        :lambda-list (metaobject)
	:return-type t
	:generic-function t
	)
    ;; Writer function for the DOC-STRING slot of METAOBJECT.
    ;; Used by methods on the (SETF DOCUMENTATION) generic-function.
    (:setf-function
        :lambda-list (value metaobject)
	:return-type t
	:generic-function t
	)
    (:setf-place
        :setf-function t
	)
    )

("METAOBJECT-NAME"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	)
    ;; Writer function for the METAOBJECT-NAME slot of METAOBJECT.
    (:function
        :lambda-list (metaobject)
	:return-type t
	:generic-function t
	)
    ;; Writer function for the METAOBJECT-NAME slot of METAOBJECT.
    (:setf-function
        :lambda-list (value metaobject)
	:return-type t
	:generic-function t
	)
    (:setf-place
        :setf-function t
	)
    )

("%METHOD-ARGUMENT"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:exists-at-runtime nil
	)
    ;; ***
    (:function
        :entry-name "IMETHOD_ARGUMENT"
        :lambda-list (frame index)
	:return-type t
	:nonconsing t
	:state-changing nil
	:state-using nil
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:int nil))
	:foreign-return-type :object
	)
    )

("%METHOD-ARGUMENT(BOXED)"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:exists-at-runtime nil
	)
    ;; A variation of METHOD-ARGUMENT that takes a boxed index.
    (:function
        :entry-name "METHOD_ARGUMENT"
        :lambda-list (frame index)
	:return-type t
	:nonconsing t
	:state-changing nil
	:state-using nil
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("%METHOD-ARGUMENT-LIST"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:exists-at-runtime nil
	)
    ;; ***
    (:function
        :entry-name "METHOD_ARGUMENT_LIST"
        :lambda-list (effective-method frame argq)
	:return-type list
	:state-changing nil
	:state-using nil
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("METHOD-CLASS"
    (:symbol
        :package "TCLOS-RUN"
	:symbol-name "SI_Qmethod_class"
	:import-from nil
	)
    ;; Slot name for GENERIC-FUNCTION.
    (:slot-name
        :index-name "SI_Smethod_class"
	)
    )

("METHOD-COMBINATION-FUNCTION"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	)
    ;; Reader function for METHOD-COMBINATION.
    (:function
	:lambda-list (method-combination)
	:return-type function
	:nonconsing t
	:state-using nil        ;method-combinations are read-only
	:state-changing nil
	:transforms ((tclos-run:%method-combination-function t))
	)
    )

("%METHOD-COMBINATION-FUNCTION"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:exists-at-runtime nil
	)
    ;; Reader function for METHOD-COMBINATION.
    (:function
        :entry-name "METHOD_COMBINATION_FUNCTION"
	:lambda-list (method-combination)
	:return-type function
	:nonconsing t
	:state-using nil        ;method-combinations are read-only
	:state-changing nil
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	)
    )

("%METHOD-COMBINATION-KEY-VALUE"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:exists-at-runtime nil
	)
    ;; Keyword argument accessor used by method-combination functions.
    (:function
        :entry-name "METHOD_COMBINATION_KEY_VALUE"
	:lambda-list (key-table key key-index frame)
	:return-type t
	:nonconsing t
	:state-changing nil
	:state-using nil
	:foreign-protocol :macro
	:foreign-arguments
	   ((:object nil) (:object nil) (:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("METHOD-COMBINATION-NAME"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	)
    ;; Reader function for METHOD-COMBINATION.
    (:function
        :lambda-list (method-combination)
	:return-type symbol
	:nonconsing t
	:state-using nil        ;method-combinations are read-only
	:state-changing nil
	:transforms ((tclos-run:%method-combination-name t))
	)
    )

("%METHOD-COMBINATION-NAME"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:exists-at-runtime nil
	)
    ;; Reader function for METHOD-COMBINATION.
    (:function
        :entry-name "METHOD_COMBINATION_NAME"
	:lambda-list (method-combination)
	:return-type symbol
	:nonconsing t
	:state-using nil        ;method-combinations are read-only
	:state-changing nil
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	)
    )

("METHOD-COMBINATION"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:symbol-name "SI_Qmethod_combination"
	)
    ;; Slot name for GENERIC-FUNCTION.
    (:slot-name
        :index-name "SI_Smethod_combination"
	)
    )

("METHOD-COMBINATION-OPTIONS"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	)
    ;; Reader for METHOD-COMBINATION.
    (:function
        :lambda-list (method-combination)
	:return-type list
	:nonconsing t
	:state-using nil        ;method-combinations are read-only
	:state-changing nil
	:transforms ((tclos-run:%method-combination-options t))
	)
    )

("%METHOD-COMBINATION-OPTIONS"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:exists-at-runtime nil
	)
    ;; Reader for METHOD-COMBINATION.
    (:function
        :entry-name "METHOD_COMBINATION_OPTIONS"
        :lambda-list (method-combination)
	:return-type list
	:nonconsing t
	:state-using nil        ;method-combinations are read-only
	:state-changing nil
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	)
    )

("%METHOD-KEY-P"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:exists-at-runtime nil
	)
    ;; Predicate which tests the result of a lookup of a keyword argument in
    ;; a method frame, returning true if the value is a supplied value and
    ;; false if it is an unsupplied marker.
    (:function
        :entry-name "METHOD_KEY_P"
        :lambda-list (value)
	:return-type t
	:nonconsing t
	:state-changing nil
	:state-using nil
	:foreign-protocol :macro
	:foreign-arguments ((:object nil))
	:foreign-return-type :boolean
	)
    )

("%METHOD-KEY-VALUE"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:exists-at-runtime nil
	)
    ;; Lookup the value for a keyword in the specified method frame.  The
    ;; key-table is a permutation vector which maps the key-index to the proper
    ;; index in the frame where the associated value is located.
    (:function
        :entry-name "METHOD_KEY_VALUE"
        :lambda-list (frame key-table key-index)
	:return-type t
	:nonconsing t
	:state-changing nil
	:state-using nil
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object nil) (:int nil))
	:foreign-return-type :object
	)
    )

("%METHOD-OPTIONAL-ARGUMENT-P"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:exists-at-runtime nil
	)
    ;; Predicate which is true if the indicated optional argument was supplied,
    ;; and false otherwise.  The index must be an unboxed fixnum.
    (:function
        :entry-name "IMETHOD_OPTIONAL_ARGUMENT_P"
        :lambda-list (argq index)
	:return-type t
	:nonconsing t
	:state-changing nil
	:state-using nil
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:int nil))
	:foreign-return-type :boolean
	)
    )

("%METHOD-OPTIONAL-ARGUMENT-P(BOXED)"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:exists-at-runtime nil
	)
    ;; Predicate which is true if the indicated optional argument was supplied,
    ;; and false otherwise.  The index must be a boxed fixnum.
    (:function
        :entry-name "METHOD_OPTIONAL_ARGUMENT_P"
        :lambda-list (argq index)
	:return-type t
	:nonconsing t
	:state-changing nil
	:state-using nil
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :boolean
	)
    )

("%METHOD-REST-LIST"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:exists-at-runtime nil
	)
    ;; Return the value in the &REST list slot of a method argument frame.
    (:function
        :entry-name "METHOD_REST_LIST"
        :lambda-list (effective-method frame argq)
	:return-type list
	:state-changing nil
	:state-using nil
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object t) (:object t))
	:foreign-return-type :object
	:uses-locals (tclos-run:%method-rest-list)
	)
    )

("METHODS"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:symbol-name "SI_Qmethods"
	)
    ;; Slot name for GENERIC-FUNCTION.
    (:slot-name
        :index-name "SI_Smethods"
	)
    )

("NAME"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:symbol-name "SI_Qname"
	)
    ;; Slot name for METAOBJECT.
    (:slot-name
        :index-name "SI_Sname"
	)
    )
    
("%NEXT-METHOD-P"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:exists-at-runtime nil
	)
    ;; ***
    (:function
        :entry-name "NEXT_METHOD_P"
        :lambda-list (effective-method method-index)
	:return-type t
	:nonconsing t
	:state-using nil
	:state-changing nil
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object t))
	:foreign-return-type :boolean
	)
    )

("OBJECT"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:symbol-name "SI_Qobject"
	)
    ;; Used in lambda-lists for reader and writer functions and methods.
    (:random-syntax)
    )

("OBJECT-CHANGE-CLASS-FUNCTION"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	)
    ;; Subclass of STANDARD-GENERIC-FUNCTION for generic-functions involved in
    ;; the update of objects for a different class whose methods can declare
    ;; additional valid initargs.
    (:class-name)
    (:type-name)
    )

("OBJECT-CREATION-FUNCTION"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	)
    ;; Subclass of STANDARD-GENERIC-FUNCTION for generic-functions involved in
    ;; the creation of objects whose methods can declare additional valid
    ;; initargs.
    (:class-name)
    (:type-name)
    )

("OBJECT-INITIALIZATION-FUNCTION"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	)
    ;; Subclass of STANDARD-GENERIC-FUNCTION for generic-functions involved in
    ;; the initialization of objects whose methods can declare additional valid
    ;; initargs.
    (:class-name)
    (:type-name)
    )

("OBJECT-REINITIALIZATION-FUNCTION"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	)
    ;; Subclass of STANDARD-GENERIC-FUNCTION for generic-functions involved in
    ;; the reinitialization of objects whose methods can declare additional
    ;; valid initargs.
    (:class-name)
    (:type-name)
    )

("PERMIT-METAOBJECT-REINITIALIZATION"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	)
    ;; Predicate which returns true if reinitialization of the metaobject
    ;; argument is permitted.  Called by a :before method on
    ;; reinitialize-instance.
    (:function
        :lambda-list (metaobject)
	:return-type t
	:generic-function t
	)
    )

("QUALIFIERS"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:symbol-name "SI_Qqualifiers"
	)
    ;; Slot name for METHOD.
    (:slot-name
        :index-name "SI_Squalifiers"
	)
    )

("PRECEDENCE-LIST"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:symbol-name "SI_Qprecedence_list"
	)
    ;; Slot name for CLASS.
    (:slot-name
        :index-name "SI_Sprecedence_list"
	)
    )

("PREVIOUS"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:symbol-name "SI_Qprevious"
	)
    ;; Lambda-list entry for some generic functions.
    (:random-syntax)
    )

("PROTOTYPE"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:symbol-name "SI_Qprototype"
	)
    ;; Slot name for CLASS.
    (:slot-name
        :index-name "SI_Sprototype"
	)
    )

("READERS"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:symbol-name "SI_Qreaders"
	)
    ;; Slot name from SLOT-DEFINITION.
    (:slot-name
        :index-name "SI_Sreaders"
	)
    )

("RECORD-METHOD-COMBINATION-FUNCTION"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	)
    ;; Appears in the expansion of define-method-combination-function.
    ;; Record the function to be used by the named method-combination type and
    ;; set the documentation for the name.  Return the name.
    ;; Note that no method-combination objects are created by this function.
    ;; Creation of method-combination objects requires the options specified in
    ;; a generic function defining form, so only occurs when executing such a
    ;; form.
    (:function
        :lambda-list (name function simple &optional documentation)
	:return-type symbol
	)
    )

("%REGISTER-CLASS-STATUS"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:exists-at-runtime nil
	)
    ;; Assigns and returns a mask used to determine whether the named status
    ;; bit of the class is set.  See class-status-p and set-class-status-p.
    (:function
        :entry-name "register_class_status"
        :lambda-list (name)
	:return-type integer
	:foreign-protocol :macro
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	)
    )

("SET-CLASS-DIRECT-SUBCLASSES"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	)
    ;; Writer for CLASS.
    (:function
        :lambda-list (value class)
	:return-type list
	:generic-function t
	)
    )

("SET-CLASS-FINALIZED-P"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	)
    ;; If the value is true, arranges that future calls to class-finalized-p
    ;; will return true, and similarly if value is false.
    (:function
        :lambda-list (class value)
	:return-type t
	:generic-function t
	)
    )

("SET-CLASS-FULLY-DEFINED-P"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	)
    ;; If the value is true, arranges that future calls to
    ;; class-fully-defined-p will return true, and similarly if value is false.
    (:function
        :lambda-list (class value)
	:return-type t
	:generic-function t
	)
    )

("%SET-CLASS-STATUS-P"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:exists-at-runtime nil
	)
    ;; Set or clear the bits specified by mask in the status bits of the class.
    (:function
        :entry-name "set_class_status_p"
	:lambda-list (class mask value)
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object nil) (:boolean nil))
	:foreign-return-type :void
	)
    )

("SET-GENERIC-FUNCTION-INITIAL-METHODS"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	)
    ;; Writer for GENERIC-FUNCTION
    (:function
        :lambda-list (methods generic-function)
	:return-type list
	:generic-function t
	)
    )

("SET-GENERIC-FUNCTION-METHODS"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	)
    ;; Writer for GENERIC-FUNCTION
    (:function
        :lambda-list (methods generic-function)
	:return-type list
	:generic-function t
	)
    )

("SET-METHOD-GENERIC-FUNCTION"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	)
    ;; Writer for METHOD
    (:function
        :lambda-list (value method)
	:return-type t
	:generic-function t
	)
    )

("%SET-SLOT-VALUE-INDEXED"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:exists-at-runtime nil
	)
    ;; ***
    (:function
        :entry-name "SET_SLOT_VALUE_INDEXED"
        :lambda-list (object slot-name value index)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object t) (:object t) (:object t))
	:foreign-return-type :object
	)
    )

("%SET-SLOT-VALUE"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:exists-at-runtime nil
	)
    ;; Direct slot update function for INSTANCE.
    (:function
        :entry-name "SET_SLOT_VALUE"
        :lambda-list (object value index)
	:return-type t
	:nonconsing t
	:state-using nil
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("%SET-SLOT-VALUE-USING-WRAPPER"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:exists-at-runtime nil
	)
    ;; Slot update function for INSTANCE that first validates the update using
    ;; the wrapper.
    (:function
        :entry-name "SET_SLOT_VALUE_USING_WRAPPER"
        :lambda-list (object slot-name value wrapper index)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments
	  ((:object t) (:object t) (:object t) (:object nil) (:object t))
	:foreign-return-type :object
	)
    )

("SET-STANDARD-OBJECT-REF"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	)
    ;; SETF function for STANDARD-OBJECT-REF (which is an l-value).
    (:function
        :entry-name "set_standard_object_ref"
	:object-name "Fset_standard_object_ref"
        :lambda-list (object index new-value)
	:return-type t
	)
    )

("SHARED-SLOT-LOCATIONS"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:symbol-name "SI_Qshared_slot_locations"
	)
    ;; Slot name for CLASS.
    (:slot-name
        :index-name "SI_Sshared_slot_locations"
	)
    )

("%SLOT-BOUNDP-INDEXED"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:exists-at-runtime nil
	)
    ;; ***
    (:function
        :entry-name "SLOT_BOUNDP_INDEXED"
        :lambda-list (object slot-name index)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object t) (:object t))
	:foreign-return-type :boolean
	)
    )

("%SLOT-BOUNDP"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:exists-at-runtime nil
	)
    ;; Direct slot boundp predicate for INSTANCE.
    (:function
        :entry-name "SLOT_BOUNDP"
        :lambda-list (object index)
	:return-type t
	:nonconsing t
	:state-changing nil
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :boolean
	)
    )

("%SLOT-BOUNDP-USING-WRAPPER"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:exists-at-runtime nil
	)
    ;; Slot boundp predicate for INSTANCE that first validates the access using
    ;; the wrapper.
    (:function
        :entry-name "SLOT_BOUNDP_USING_WRAPPER"
        :lambda-list (object slot-name wrapper index)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object t) (:object nil) (:object t))
	:foreign-return-type :boolean
	)
    )

("SLOT-DEFINITION-LOCATION"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	)
    ;; Reader for EFFECTIVE-SLOT-DEFINITION
    (:function
        :lambda-list (slotd)
	:return-type t
	:generic-function t
	)
    ;; Writer for EFFECTIVE-SLOT-DEFINITION
    (:setf-function
        :lambda-list (value slot)
	:return-type t
	:generic-function t
	)
    (:setf-place
        :setf-function t
	)
    )

("%SLOT-EXISTS-P-INDEXED"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:exists-at-runtime nil
	)
    ;; ***
    (:function
        :entry-name "SLOT_EXISTS_P_INDEXED"
        :lambda-list (object slot-name index)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object t) (:object nil))
	:foreign-return-type :boolean
	)
    )

;;; Note: SLOT-EXISTS-P-INSTANCE not needed.

("%SLOT-EXISTS-P-USING-WRAPPER"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:exists-at-runtime nil
	)
    ;; ***
    (:function
        :entry-name "SLOT_EXISTS_P_USING_WRAPPER"
        :lambda-list (object slot-name wrapper index)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments
	    ((:object t) (:object t) (:object t) (:object t))
	:foreign-return-type :boolean
	)
    )

("%SLOT-MAKUNBOUND-INDEXED"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:exists-at-runtime nil
	)
    ;; ***
    (:function
        :entry-name "SLOT_MAKUNBOUND_INDEXED"
        :lambda-list (object slot-name index)
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object t) (:object t))
	:foreign-return-type :void
	)
    )

("%SLOT-MAKUNBOUND"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:exists-at-runtime nil
	)
    ;; ***
    (:function
        :entry-name "SLOT_MAKUNBOUND"
        :lambda-list (object index)
	:nonconsing t
	:state-using nil
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :void
	)
    )

("%SLOT-MAKUNBOUND-USING-WRAPPER"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:exists-at-runtime nil
	)
    ;; ***
    (:function
        :entry-name "SLOT_MAKUNBOUND_USING_WRAPPER"
        :lambda-list (object slot-name wrapper index)
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object t) (:object nil) (:object t))
	:foreign-return-type :void
	)
    )

("SLOT-NAME"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:symbol-name "SI_Qslot_name"
	)
    ;; Slot name for ACCESSOR-METHOD.
    (:slot-name
        :index-name "SI_Sslot_name"
	)
    )

("SLOT-TYPE"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:symbol-name "SI_Qslot_type"
	)
    ;; Slot name from SLOT-DEFINITION.
    (:slot-name
        :index-name "SI_Sslot_type"
	)
    )

("%SLOT-VALUE-INDEXED"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:exists-at-runtime nil
	)
    ;; ***
    (:function
        :entry-name "SLOT_VALUE_INDEXED"
        :lambda-list (object slot-name index)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object t) (:object t))
	:foreign-return-type :object
	:uses-locals (tclos-run:%slot-value)
	)
    )

("%SLOT-VALUE"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:exists-at-runtime nil
	)
    ;; ***
    (:function
        :entry-name "SLOT_VALUE"
        :lambda-list (object slot-name index)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object t) (:object nil))
	:foreign-return-type :object
	:uses-locals (tclos-run:%slot-value)
	)
    )

("%SLOT-VALUE-USING-WRAPPER"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:exists-at-runtime nil
	)
    ;; ***
    (:function
        :entry-name "SLOT_VALUE_USING_WRAPPER"
        :lambda-list (object slot-name wrapper index)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object t) (:object nil) (:object t))
	:foreign-return-type :object
	:uses-locals (tclos-run:%slot-value)
	)
    )

("SLOTTED-CLASS"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	)
    ;; Superclass for STRUCTURE-CLASS and INTERNAL-STANDARD-CLASS.
    ;; Presently this class doesn't do anything useful.  If STRUCTURE-CLASS
    ;; were made to support the slot-access protocol, some methods on
    ;; INTERNAL-STANDARD-CLASS would probably be moved up to this class so
    ;; they could also be inherited by STRUCTURE-CLASS.
    (:class-name)
    (:type-name)
    )

("SLOTS"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:symbol-name "SI_Qslots"
	)
    ;; Slot name for CLASS.
    (:slot-name
        :index-name "SI_Sslots"
	)
    )

("SLOTS-ALIST"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:symbol-name "SI_Qslots_alist"
	)
    ;; Slot name for CLASS.
    (:slot-name
        :index-name "SI_Sslots_alist"
	)
    )

("%SORT-PARSED-METHODS"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:exists-at-runtime nil
	)
    ;; ***
    (:function
        :entry-name "sort_parsed_methods"
        :lambda-list (methods order patterns required)
	:return-type list
	:foreign-protocol :foreign-arguments-function
	:foreign-arguments
	    ((:object nil) (:object nil) (:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("SPECIALIZED-POSITIONS"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:symbol-name "SI_Qspecialized_positions"
	)
    ;; Slot name for GENERIC-FUNCTION.
    (:slot-name
        :index-name "SI_Sspecialized_positions"
	)
    )

("SPECIALIZERS"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:symbol-name "SI_Qspecializers"
	)
    ;; Slot name for METHOD.
    (:slot-name
        :index-name "SI_Sspecializers"
	)
    )

("STANDARD-OBJECT-REF"
    (:symbol
        :package "TCLOSX"
	:import-from nil
	)
    ;; Primitive slot accessor for standard-objects.  Object must be a
    ;; standard-object and index must be a fixnum.
    (:function
        :entry-name "standard_object_ref"
	:object-name "Fstandard_object_ref"
	:lambda-list (object index)
	:return-type t
	:nonconsing t
	:state-changing nil
	:transforms ((tclos-run:%standard-object-ref t))
	)
    (:setf-place)
    )

("%STANDARD-OBJECT-REF"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:exists-at-runtime nil
	)
    ;; Macro version of the primitive slot accessor for standard-objects.
    (:function
        :entry-name "STANDARD_OBJECT_REF"
        :lambda-list (object index)
	:return-type t
	:argument-types (standard-object fixnum)
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("STATUS-BITS"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:symbol-name "SI_Qstatus_bits"
	)
    ;; Slot name for CLASS.
    (:slot-name
        :index-name "SI_Sstatus_bits"
	)
    )

("SUPERCLASS"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:symbol-name "SI_Qsuperclass"
	)
    ;; Lambda-list entry for some generic functions.
    (:random-syntax)
    )

("%UPDATE-EFFECTIVE-METHOD"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:exists-at-runtime nil
	)
    ;; ***
    (:function
        :entry-name "update_effective_method"
        :lambda-list (effective-method method next-methods)
	:return-type fixnum
	:foreign-protocol :foreign-arguments-function
	:foreign-arguments ((:object nil) (:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("UPDATE-INITIAL-METHODS"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	)
    ;; This function is used as part of the expansion for forms which define
    ;; generic functions.  It updates the list of initial-methods for the
    ;; generic-function object by setting the initial-methods slot to the
    ;; specified list of methods, after first removing any methods in the
    ;; original initial-methods list which are not in the new list.
    ;; 
    ;; generic-function -- A generic-function object or the name of a generic
    ;; function.  If it is a name, the function fdefinition is applied to the
    ;; name to get the generic-function object to update.
    ;;
    ;; initial-methods -- List of method metaobjects that are to be included
    ;; in the initial-methods list.
    ;;
    ;; The generic-function object is returned.
    (:function
        :lambda-list (generic-function initial-methods)
	:return-type generic-function
	)
    )

("VALID-CHANGE-CLASS-INITARGS"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	)
    (:function
        :lambda-list (class)
	:return-type list
	:generic-function t
	)
    (:setf-function
        :lambda-list (value class)
	:return-type list
	:generic-function t
	)
    (:setf-place
        :setf-function t
	)
    ;; Slot name for CLASS.
    (:slot-name
        :index-name "SI_Svalid_change_class_initargs"
	)
    )

("VALID-CREATION-INITARGS"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	)
    (:function
        :lambda-list (class)
	:return-type list
	:generic-function t
	)
    (:setf-function
        :lambda-list (value class)
	:return-type list
	:generic-function t
	)
    (:setf-place
        :setf-function t
	)
    ;; Slot name for CLASS.
    (:slot-name
        :index-name "SI_Svalid_creation_initargs"
	)
    )

("VALID-REINITIALIZATION-INITARGS"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	)
    (:function
        :lambda-list (class)
	:return-type list
	:generic-function t
	)
    (:setf-function
        :lambda-list (value class)
	:return-type list
	:generic-function t
	)
    (:setf-place
        :setf-function t
	)
    ;; Slot name for CLASS.
    (:slot-name
        :index-name "SI_Svalid_reinitialization_initargs"
	)
    )

("VALUE"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:symbol-name "SI_Qvalue"
	)
    ;; Used in lambda-lists for reader and writer functions and methods.
    (:random-syntax)
    )

("WRAPPER"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:symbol-name "SI_Qwrapper"
	)
    ;; Slot name for CLASS.
    (:slot-name
        :index-name "SI_Swrapper"
	)
    )

("WRITERS"
    (:symbol
        :package "TCLOS-RUN"
	:import-from nil
	:symbol-name "SI_Qwriters"
	)
    ;; Slot name from SLOT-DEFINITION.
    (:slot-name
        :index-name "SI_Swriters"
	)
    )


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Symbols in the KEYWORD package
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

("ALLOCATION"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    ;; Initarg for SLOT-DEFINITION.
    (:random-syntax)
    )

("ARGUMENT-PRECEDENCE-ORDER"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    ;; Initarg for GENERIC-FUNCTION.
    ;; Argument for ENSURE-GENERIC-FUNCTION.
    (:random-syntax)
    )

("DIRECT-DEFAULT-INITARGS"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    ;; Initarg for CLASS.
    (:random-syntax)
    )

("DIRECT-SLOTS"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    ;; Initarg for CLASS.
    (:random-syntax)
    )

("DIRECT-SUPERCLASSES"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    ;; Initarg for CLASS.
    (:random-syntax)
    )

("DECLARE"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    ;; Initarg for GENERIC-FUNCTION.
    ;; Argument for ENSURE-GENERIC-FUNCTION.
    (:random-syntax)
    )

("DOCUMENTATION"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    ;; Initarg for METAOBJECT.
    ;; Argument for ENSURE-GENERIC-FUNCTION.
    (:random-syntax)
    )

("ENVIRONMENT"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    ;; Argument for ENSURE-GENERIC-FUNCTION.
    (:random-syntax)
    )

("GENERIC-FUNCTION"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    ;; Initarg for METHOD.
    (:random-syntax)
    )

("GENERIC-FUNCTION-CLASS"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    ;; Argument for ENSURE-GENERIC-FUNCTION.
    (:random-syntax)
    )

("INITARGS"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    ;; Initarg for SLOT-DEFINITION.
    (:random-syntax)
    )

("INITFORM"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    ;; Initarg for SLOT-DEFINITION.
    (:random-syntax)
    )

("INITFUNCTION"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    ;; Initarg for SLOT-DEFINITION.
    (:random-syntax)
    )

("INITIAL-METHODS"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    ;; Initarg for GENERIC-FUNCTION.
    (:random-syntax)
    )

("KEYWORD-PARAMETER-MAP"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    ;; Initarg for METHOD.
    (:random-syntax)
    )

("LAMBDA-LIST"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    ;; Initarg for GENERIC-FUNCTION, METHOD.
    ;; Argument for ENSURE-GENERIC-FUNCTION.
    (:random-syntax)
    )

("METACLASS"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    ;; Argument for ENSURE-CLASS.
    (:random-syntax)
    )

("METHOD-CLASS"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    ;; Initarg for GENERIC-FUNCTION.
    ;; Argument for ENSURE-GENERIC-FUNCTION.
    (:random-syntax)
    )

("METHOD-COMBINATION"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    ;; Initarg for GENERIC-FUNCTION.
    ;; Argument for ENSURE-GENERIC-FUNCTION.
    (:random-syntax)
    )

("METHOD-COMBINATION-OPTIONS"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    ;; Argument for ADD-NAMED-GENERIC-FUNCTION.
    ;; Argument for MAKE-GENERIC-FUNCTION.
    (:random-syntax)
    )

("METHOD-COMBINATION-TYPE"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    ;; Argument for ADD-NAMED-GENERIC-FUNCTION.
    ;; Argument for MAKE-GENERIC-FUNCTION.
    (:random-syntax)
    )

("NAME"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    ;; Initarg for METAOBJECT.
    (:random-syntax)
    )

("QUALIFIERS"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    ;; Initarg for METHOD.
    (:random-syntax)
    )

("READ"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    ;; Argument to ELIDE-ACCESS-METHOD-P.
    (:random-syntax)
    )

("READERS"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    ;; Initarg for SLOT-DEFINITION.
    (:random-syntax)
    )

("SLOT-NAME"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    ;; Initarg for STANDARD-ACCESSOR-METHOD.
    (:random-syntax)
    )

("SPECIALIZERS"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    ;; Initarg for METHOD.
    (:random-syntax)
    )

("TYPE"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    ;; Initarg for SLOT-DEFINITION.
    (:random-syntax)
    )

("WRITE"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    ;; Argument to ELIDE-ACCESS-METHOD-P.
    (:random-syntax)
    )

("WRITERS"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    ;; Initarg for SLOT-DEFINITION.
    (:random-syntax)
    )

)

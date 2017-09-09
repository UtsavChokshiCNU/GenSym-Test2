;;; -*- Mode: Lisp; Package: TCLOSI; Syntax: Common-Lisp -*-
;;;
;;; Initialize the environment information for predefined generic functions.
;;; Copyright (C) 1991 Chestnut Software, Inc.  All Rights Reserved.
;;;

(in-package "TCLOSI")

(himpl:note-rcs-revision "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/initialize-generic-functions.lisp,v $"
			 "$Revision: 1.1 $"
			 "$Date: 2006/02/28 21:59:07 $")

;;; First generate generic functions for all the readers and writers for
;;; predefined classes.

(defun initialize-generic-functions
    (&optional (env *default-global-environment*)
     &aux (*current-translated-file*
	   (translated-file
	      ;; This really ought to be *load-truename*
	      (merge-pathnames "initialize-generic-functions.lisp")))
     )

  (flet ((ensure-early-generic-function (name lambda-list &rest keys)
	   (unless (defined-as-function name env)
	     (warn "~S does not have a function entry in the database." name))
	   (apply #'translator-ensure-generic-function
		  name :lambda-list lambda-list :enviroment env keys)
	   (redefinition-record-note-definition-dumped
	        (generic-function-record-redefinition-record
		     (defined-as-generic-function name env)))))

    ;; *** Need to check the generic-function-class for all of these.

    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;; Generic functions in the TCL package.
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    (ensure-early-generic-function
         'TCL:ADD-METHOD
	 '(generic-function method)
	 )

    (ensure-early-generic-function
         'TCL:ALLOCATE-INSTANCE
	 '(class &key &allow-other-keys)
	 :generic-function-class 'tclos-run:object-creation-function
	 )

    (ensure-early-generic-function
         'TCL:CHANGE-CLASS
	 '(object class)
	 ;; Only needed if CHANGE-CLASS accepts initargs.
	 ;; :generic-function-class 'tclos-run:object-change-class-function
	 )

    (ensure-early-generic-function
         'TCL:CLASS-NAME
	 '(class)
	 )

    (ensure-early-generic-function
         '(SETF TCL:CLASS-NAME)
	 '(value class)
	 )

    (ensure-early-generic-function
         'TCL:COMPUTE-APPLICABLE-METHODS
	 '(generic-function arguments)
	 :generic-function-class 'tclos-run:kernel-generic-function
	 :critical-methods '((tclos-run:kernel-generic-function cons))
	 )

    ;; TCL:DESCRIBE-OBJECT (object stream)
    ;; TCL:DOCUMENTATION (object &optional doc-type)
    ;; (SETF TCL:DOCUMENTATION) (value object &optional doc-type)

    (ensure-early-generic-function
         'TCL:FIND-METHOD
	 '(generic-function qualifiers specializers &optional error)
	 )

    (ensure-early-generic-function
         'TCL:FUNCTION-KEYWORDS
	 '(method)
	 )

    (ensure-early-generic-function
         'TCL:INITIALIZE-INSTANCE
	 '(object &key &allow-other-keys)
	 :generic-function-class 'tclos-run:object-creation-function
	 )

    (ensure-early-generic-function
         'TCL:MAKE-INSTANCE
	 '(class &rest initargs)
	 )

    (ensure-early-generic-function
         'TCL:MAKE-INSTANCES-OBSOLETE
	 '(class)
	 )

    ;; TCL:MAKE-LOAD-FORM (object)

    (ensure-early-generic-function
         'TCL:METHOD-QUALIFIERS
	 '(method)
	 :generic-function-class 'tclos-run:kernel-generic-function
	 :critical-methods '((standard-method)
			     (tclos:standard-reader-method))
	 )

    (ensure-early-generic-function
         'TCL:NO-APPLICABLE-METHOD
	 '(generic-function &rest arguments)
	 )

    (ensure-early-generic-function
         'TCL:NO-NEXT-METHOD
	 '(generic-function method &rest arguments)
	 )

    (ensure-early-generic-function
         'TCL:PRINT-OBJECT
	 '(object stream)
	 )

    (ensure-early-generic-function
         'TCL:REINITIALIZE-INSTANCE
	 '(object &key &allow-other-keys)
	 :generic-function-class 'tclos-run:object-reinitialization-function
	 )

    (ensure-early-generic-function
         'TCL:REMOVE-METHOD
	 '(generic-function method)
	 )

    (ensure-early-generic-function
         'TCL:SHARED-INITIALIZE
	 '(object slots &key &allow-other-keys)
	 :generic-function-class 'tclos-run:object-initialization-function
	 )

    (ensure-early-generic-function
         'TCL:SLOT-MISSING
	 '(class object slot-name function &optional value)
	 )

    (ensure-early-generic-function
         'TCL:SLOT-UNBOUND
	 '(class object slot-name)
	 )

    (ensure-early-generic-function
         'TCL:UPDATE-INSTANCE-FOR-DIFFERENT-CLASS
	 '(previous object &key &allow-other-keys)
	 :generic-function-class 'tclos-run:object-change-class-function
	 )

    ;; TCL:UPDATE-INSTANCE-FOR-REDEFINED-CLASS
    ;;    (object added removed plist &rest initargs)

    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;; Generic functions in the TCLOS package.
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    (ensure-early-generic-function
         'TCLOS:CLASS-DEFAULT-INITARGS
	 '(class)
	 )

    (ensure-early-generic-function
         'TCLOS:CLASS-DIRECT-DEFAULT-INITARGS
	 '(class)
	 )

    (ensure-early-generic-function
         'TCLOS:CLASS-DIRECT-SLOTS
	 '(class)
	 )

    (ensure-early-generic-function
         'TCLOS:CLASS-DIRECT-SUBCLASSES
	 '(class)
	 )

    (ensure-early-generic-function
         'TCLOS:CLASS-DIRECT-SUPERCLASSES
	 '(class)
	 )

    (ensure-early-generic-function
         'TCLOS:CLASS-PRECEDENCE-LIST
	 '(class)
	 :generic-function-class 'tclos-run:kernel-generic-function
	 :critical-methods '((standard-class)
			     (tclos:funcallable-standard-class)
			     (tclosx:method-class))
	 )

    (ensure-early-generic-function
         'TCLOS:CLASS-PROTOTYPE
	 '(class)
	 )

    (ensure-early-generic-function
         'TCLOS:CLASS-SLOTS
	 '(class)
	 )

    (ensure-early-generic-function
         'TCLOS:COMPUTE-EFFECTIVE-METHOD
	 '(generic-function method-combination methods)
	 :generic-function-class 'tclos-run:kernel-generic-function
	 :critical-methods '((tclos-run:kernel-generic-function
			      method-combination cons))
	 )

    (ensure-early-generic-function
         'TCLOS:GENERIC-FUNCTION-ARGUMENT-PRECEDENCE-ORDER
	 '(generic-function)
	 )

    (ensure-early-generic-function
         'TCLOS:GENERIC-FUNCTION-DECLARATIONS
	 '(generic-function)
	 )

    (ensure-early-generic-function
         'TCLOS:GENERIC-FUNCTION-INITIAL-METHODS
	 '(generic-function)
	 )

    (ensure-early-generic-function
         'TCLOS:GENERIC-FUNCTION-LAMBDA-LIST
	 '(generic-function)
	 )

    (ensure-early-generic-function
         'TCLOS:GENERIC-FUNCTION-METHOD-CLASS
	 '(generic-function)
	 )

    (ensure-early-generic-function
         'TCLOS:GENERIC-FUNCTION-METHOD-COMBINATION
	 '(generic-function)
	 :generic-function-class 'tclos-run:kernel-generic-function
	 :critical-methods '((tclos-run:kernel-generic-function))
	 )

    (ensure-early-generic-function
         'TCLOS:GENERIC-FUNCTION-METHODS
	 '(generic-function)
	 :generic-function-class 'tclos-run:kernel-generic-function
	 :critical-methods '((tclos-run:kernel-generic-function))
	 )

    (ensure-early-generic-function
         'TCLOS:GENERIC-FUNCTION-NAME
	 '(generic-function)
	 )

    (ensure-early-generic-function
         'TCLOS:METHOD-FUNCTION
	 '(method)
	 )

    (ensure-early-generic-function
         'TCLOS:METHOD-GENERIC-FUNCTION
	 '(method)
	 )

    (ensure-early-generic-function
         'TCLOS:METHOD-LAMBDA-LIST
	 '(method)
	 )

    (ensure-early-generic-function
         'TCLOS:METHOD-SLOT-NAME
	 '(method)
	 )

    (ensure-early-generic-function
         'TCLOS:METHOD-SPECIALIZERS
	 '(method)
	 :generic-function-class 'tclos-run:kernel-generic-function
	 :critical-methods '((standard-method)
			     (tclos:standard-reader-method))
	 )

    (ensure-early-generic-function
         'TCLOS:SLOT-BOUNDP-USING-CLASS
	 '(class object slot-name)
	 )

    (ensure-early-generic-function
         'TCLOS:SLOT-DEFINITION-ALLOCATION
	 '(slot-definition)
	 )

    (ensure-early-generic-function
         'TCLOS:SLOT-DEFINITION-INITARGS
	 '(slot-definition)
	 )

    (ensure-early-generic-function
         'TCLOS:SLOT-DEFINITION-INITFORM
	 '(slot-definition)
	 )

    (ensure-early-generic-function
         'TCLOS:SLOT-DEFINITION-INITFUNCTION
	 '(slot-definition)
	 )

    (ensure-early-generic-function
         'TCLOS:SLOT-DEFINITION-NAME
	 '(slot-definition)
	 )

    (ensure-early-generic-function
         'TCLOS:SLOT-DEFINITION-READERS
	 '(slot-definition)
	 )

    (ensure-early-generic-function
         'TCLOS:SLOT-DEFINITION-TYPE
	 '(slot-definition)
	 )

    (ensure-early-generic-function
         'TCLOS:SLOT-DEFINITION-WRITERS
	 '(slot-definition)
	 )

    (ensure-early-generic-function
         'TCLOS:SLOT-MAKUNBOUND-USING-CLASS
	 '(class object slot-name)
	 )

    (ensure-early-generic-function
         'TCLOS:SLOT-VALUE-USING-CLASS
	 '(class object slot-name)
	 )

    (ensure-early-generic-function
         '(SETF TCLOS:SLOT-VALUE-USING-CLASS)
	 '(value class object slot-name)
	 )

    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;; Generic functions in the TCLOSX package
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    (ensure-early-generic-function
        'TCLOSX:ADD-DIRECT-SUBCLASS
	'(superclass class)
	)

    (ensure-early-generic-function
        'TCLOSX:CLASS-DEFAULT-SUPERCLASSES
	'(class)
	)

    (ensure-early-generic-function
        'TCLOSX:CLASS-FINALIZED-P
	'(class)
	:method-combination-type 'and
	)

    (ensure-early-generic-function
        'TCLOSX:COMPUTE-CLASS-DEFAULT-INITARGS
	'(class)
	)

    (ensure-early-generic-function
        'TCLOSX:COMPUTE-CLASS-PRECEDENCE-LIST
	'(class)
	)

    (ensure-early-generic-function
        'TCLOSX:COMPUTE-EFFECTIVE-SLOT-DEFINITION
	'(class name direct-slots)
	)

    (ensure-early-generic-function
        'TCLOSX:COMPUTE-EFFECTIVE-SLOT-DEFINITION-INITARGS
	'(slot-definition direct-slots)
	)

    (ensure-early-generic-function
        'TCLOSX:COMPUTE-SLOTS
	'(class)
	)

    (ensure-early-generic-function
        'TCLOSX:DEFAULT-INITARGS
	'(prototype initargs)
	)

    (ensure-early-generic-function
        'TCLOSX:DIRECT-SLOT-DEFINITION-CLASS
	'(class initargs)
	)

    (ensure-early-generic-function
        'TCLOSX:EFFECTIVE-SLOT-DEFINITION-CLASS
	'(class direct-slots)
	)

    (ensure-early-generic-function
         'TCLOSX:ELIDE-ACCESS-METHOD-P
	 '(class slot-definition type)
	 )

    (ensure-early-generic-function
        'TCLOSX:FINALIZE-INHERITANCE
	'(class)
	)

    (ensure-early-generic-function
        'TCLOSX:LOCAL-SLOT-DEFINITION-P
	'(slot-definition)
	)

    (ensure-early-generic-function
         'TCLOSX:NO-PRIMARY-METHOD
	 '(generic-function &rest arguments)
	 )

    (ensure-early-generic-function
         'TCLOSX:OPTIMIZE-SLOT-ACCESS
	 '(class slot-definition)
	 )

    (ensure-early-generic-function
         'TCLOSX:OPTIMIZE-SLOT-ACCESSES
	 '(class)
	 )
    
    (ensure-early-generic-function
        'TCLOSX:REMOVE-DIRECT-SUBCLASS
	'(superclass class)
	)

    (ensure-early-generic-function
        'TCLOSX:SHARED-SLOT-DEFINITION-P
	'(slot-definition)
	)

    (ensure-early-generic-function
         'TCLOSX:VALIDATE-SUPERCLASS
	 '(class superclass)
	 )

    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;; Generic functions in the TCLOS-RUN package
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    (ensure-early-generic-function
        'TCLOS-RUN:CLASS-FULLY-DEFINED-P
	'(class)
	:method-combination-type 'and
	)

    (ensure-early-generic-function
        'TCLOS-RUN:CLASS-STATUS-BITS
	'(class)
	)

    (ensure-early-generic-function
        '(SETF TCLOS-RUN:CLASS-STATUS-BITS)
	'(value class)
	)

    (ensure-early-generic-function
        'TCLOS-RUN:COMPUTE-CLASS-PROTOTYPE
	'(class)
	)

    (ensure-early-generic-function
        'TCLOS-RUN:COMPUTE-SLOT-DEFINITION-LOCATION
	'(class slot-definition)
	)

    (ensure-early-generic-function
        'TCLOS-RUN:COMPUTE-SLOT-DEFINITION-LOCATIONS
	'(class slots)
	)

    (ensure-early-generic-function
        'TCLOS-RUN:COMPUTE-VALID-CHANGE-CLASS-INITARGS
	'(class)
	)

    (ensure-early-generic-function
        'TCLOS-RUN:COMPUTE-VALID-CREATION-INITARGS
	'(class)
	)

    (ensure-early-generic-function
        'TCLOS-RUN:COMPUTE-VALID-REINITIALIZATION-INITARGS
	'(class)
	)

    (ensure-early-generic-function
         'TCLOS-RUN:METAOBJECT-DOCUMENTATION
	 '(metaobject)
	 )

    (ensure-early-generic-function
         '(SETF TCLOS-RUN:METAOBJECT-DOCUMENTATION)
	 '(value metaobject)
	 )

    (ensure-early-generic-function
         'TCLOS-RUN:METAOBJECT-NAME
	 '(metaobject)
	 )

    (ensure-early-generic-function
         '(SETF TCLOS-RUN:METAOBJECT-NAME)
	 '(value metaobject)
	 )

    (ensure-early-generic-function
         'TCLOS-RUN:PERMIT-METAOBJECT-REINITIALIZATION
	 '(metaobject)
	 )

    (ensure-early-generic-function
        'TCLOS-RUN:SET-CLASS-DIRECT-SUBCLASSES
	'(value class)
	)

    (ensure-early-generic-function
        'TCLOS-RUN:SET-CLASS-FINALIZED-P
	'(class value)
	:method-combination-type 'progn
	)

    (ensure-early-generic-function
        'TCLOS-RUN:SET-CLASS-FULLY-DEFINED-P
	'(class value)
	:method-combination-type 'progn
	)

    (ensure-early-generic-function
        'TCLOS-RUN:SET-GENERIC-FUNCTION-INITIAL-METHODS
	'(value generic-function)
	)

    (ensure-early-generic-function
        'TCLOS-RUN:SET-GENERIC-FUNCTION-METHODS
	'(value generic-function)
	)

    (ensure-early-generic-function
        'TCLOS-RUN:SET-METHOD-GENERIC-FUNCTION
	'(value method)
	)

    (ensure-early-generic-function
        'TCLOS-RUN:SLOT-DEFINITION-LOCATION
	'(slot-definition)
	)

    (ensure-early-generic-function
        '(SETF TCLOS-RUN:SLOT-DEFINITION-LOCATION)
	'(value slot-definition)
	)

    (ensure-early-generic-function
         'TCLOS-RUN:VALID-CHANGE-CLASS-INITARGS
	 '(class)
	 )

    (ensure-early-generic-function
         '(SETF TCLOS-RUN:VALID-CHANGE-CLASS-INITARGS)
	 '(value class)
	 )

    (ensure-early-generic-function
         'TCLOS-RUN:VALID-CREATION-INITARGS
	 '(class)
	 )

    (ensure-early-generic-function
         '(SETF TCLOS-RUN:VALID-CREATION-INITARGS)
	 '(value class)
	 )

    (ensure-early-generic-function
         'TCLOS-RUN:VALID-REINITIALIZATION-INITARGS
	 '(class)
	 )

    (ensure-early-generic-function
         '(SETF TCLOS-RUN:VALID-REINITIALIZATION-INITARGS)
	 '(value class)
	 )

    )


  ;; Check for missing generic-functions.
  (labels ((check-generic-functions (package)
	     (do-external-symbols (name package)
	       (check-name name)
	       (check-name `(setf ,name))))
	   (check-name (name)
	     (and (defined-as-generic-function name env)
		  (not (translator-find-generic-function-record name nil env))
		  (warn "Generic-function ~S not initialized." name))))

    (check-generic-functions "TCL")
    (check-generic-functions "TCLOS")
    (check-generic-functions "TRUN")
    (check-generic-functions "TCLOS-RUN")

    )
  )

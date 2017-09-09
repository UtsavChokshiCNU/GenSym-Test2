;;; -*- Mode: Lisp; Package: TCLOSI; Syntax: Common-Lisp -*-
;;;
;;; The DEFCLASS macro and translator macro.
;;; Copyright (C) 1991 Chestnut Software, Inc.  All Rights Reserved.
;;;

(in-package "TCLOSI")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/defclass.lisp,v $"
 "$Revision: 1.1 $"
 "$Date: 2006/02/28 21:59:02 $")

;;; This is the expander used in the host environment.
;;; Note that for the slot initfunctions to be correct, uses of this macro
;;; should only appear at toplevel.
(defmacro define-translator-class (name supers slots &rest options)
  (ensure-legal-class-name name)
  `(progn
     (defclass ,name ,supers ,slots ,@options)
     (setf (translator-find-class ',name) (find-class ',name))
     (with-translate-time-initfunctions
       (ensure-translator-class
	    ',name
	    :environment *default-global-environment*
	    ,@(parse-defclass-arguments name
					supers
					slots
					options
					*default-global-environment*)))
     (find-class ',name)))

;;; This is the expander used by the translator.

(define-translator-macro defclass
        (name supers slots &rest options &environment env)
  (expand-defclass name supers slots options env t))

;;; Perform translation time portion of defclass.
;;;
;;; The point of this is to provide information about the class to the
;;; translator when the actual class definition will appear in a non-toplevel
;;; context.

(define-translator-macro declare-class
        (name supers slots &rest options &environment env)
  (expand-defclass name supers slots options env nil))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Processing of a DEFCLASS form
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;; A DEFCLASS form is converted into two forms; one is evaluated at
;;; compile-file time and the other is evaluated at load time.  The
;;; compile-file version is supplied with the :ENVIRONMENT keyword with a value
;;; having indefinite extent which reflects the "compile-fileness" of the
;;; environment of the DEFCLASS macro.  The load-time version does not supply
;;; the environment keyword.
;;;
;;; Most of the conversion from a DEFCLASS form to an ENSURE-CLASS form is
;;; performed by methods specialized on the metaclass.  These methods generate
;;; a canonic class specification.  The canonic class specification will serve
;;; as the keyword and value forms for ENSURE-CLASS.  The representation of a
;;; canonic class specification is as a canonic initarg list.
;;;
;;; The parsing mechanism described here is incompatible with the mechanism
;;; described in the MOP draft dated 6/6/90.  Instead it is based in large part
;;; on a description by Cyphers and Moon of a possibly way that the DEFCLASS
;;; macro could be made extensible by metaclasses, allowing new class options
;;; and new slot options to be added by users.

(defun expand-defclass (name supers slots options env runtimep)
  (ensure-legal-class-name name)
  (with-translator-message `(defclass ,name)
    (let ((initargs (parse-defclass-arguments name
					      supers
					      slots
					      options
					      env)))
      `(progn
	 (eval-when (:compile-toplevel)
	   (print-progress-message
	    ,(if runtimep "Class" "Class declaration")
	    ',name))
	 ,(make-translator-class-form name supers slots options env)
	 (eval-when (:compile-toplevel)
	   (with-translate-time-initfunctions
	       (ensure-translator-class
	        ',name
		:environment ',(translator-environment-name env)
		,@initargs)))
	 ,@(when runtimep
	     (let ((runtime-initargs (filter-defclass-arguments initargs env)))
	       `((eval-when (:load-toplevel :execute)
		   ,@(mapcar #'(lambda (name)
				 `(tclos-run:%assign-slot-index
				   ',name
				   (slot-index ,name)))
			     (collect-defclass-slot-names
			      runtime-initargs env))
		   ,@(mapcar #'(lambda (name)
				 `(generic-function-setup ,name))
			     (collect-defclass-readers runtime-initargs env))
		   ,@(mapcar #'(lambda (name)
				 `(generic-function-setup ,name))
			     (collect-defclass-writers runtime-initargs env))
		   (tclos-run:add-named-class
		    ',name ,@runtime-initargs)))))))))

(defun collect-defclass-slot-names (canonic env)
  (flet ((slot-name (entry)
	   (multiple-value-bind (name therep)
	       (cgetf (cdr entry) :name)
	     (when therep
	       (multiple-value-setq (name therep)
		 (translator-constant-value name env))
	       (when therep (list name))))))
    (mapcan #'slot-name (cdr (cgetf canonic :direct-slots)))))

(defun collect-defclass-accessors (key canonic env)
  (flet ((accessors (entry)
	   (multiple-value-bind (accessors therep)
	       (cgetf (cdr entry) key)
	     (when therep
	       (multiple-value-setq (accessors therep)
		 (translator-constant-value accessors env))
	       (when therep (copy-list accessors))))))
    (mapcan #'accessors (cdr (cgetf canonic :direct-slots)))))

(defun collect-defclass-readers (canonic env)
  (collect-defclass-accessors :readers canonic env))

(defun collect-defclass-writers (canonic env)
  (collect-defclass-accessors :writers canonic env))

(defun make-translator-class-form (name supers slots options env)
  (if *use-remote-classes*
      '(progn)
      `(eval-when (:compile-toplevel)
	 (defclass ,name ,supers ,slots ,@options)
	 (setf (translator-find-class ',name nil
				      ',(translator-environment-name env))
	       (find-class ',name)))))

;;; Invoke the various canonicalizers in the proper order, passing the canonic
;;; initargs built by each canonicalizer to the next canonicalizer in turn.

(defun parse-defclass-arguments (name supers slots options env)
  (let ((class (class-prototype-for-defclass name options env)))
    (canonicalize-defclass-slots
         class
	 slots
	 (canonicalize-defclass-supers
	      class
	      supers
	      (canonicalize-defclass-options
	           class
		   options
		   nil
		   env)
	      env)
	 env)))

;;; Filter defclass initargs

(define-canonic-filter-table defclass)

(defun filter-defclass-arguments (initargs env)
  (filter-initargs 'defclass initargs env))

(defmacro define-defclass-filter (key lambda-list &body body)
  `(define-canonic-filter (,key defclass) ,lambda-list ,@body))

;;; Remove documentation if not requested.
(define-defclass-filter :documentation (initargs env)
  (declare (ignore env))
  (multiple-value-bind (value therep)
      (cgetf initargs :documentation)
    (when (and therep (not (record-documentation-p value)))
      (cremf initargs :documentation))
    initargs))

;;; Remove metaclass if standard-class.
(define-defclass-filter :metaclass (initargs env)
  (multiple-value-bind (value therep)
      (resolve-constant-initarg :metaclass initargs env)
    (when (and therep (eq value 'standard-class))
      (cremf initargs :metaclass))
    initargs))

;;; Remove empty direct-default-initargs.
(define-defclass-filter :direct-default-initargs (initargs env)
  (filter-defclass-empty-list-initarg :direct-default-initargs initargs env))

;;; Remove direct-superclasses if NIL or same as defaults for metaclass.
(define-defclass-filter :direct-superclasses (initargs env)
  (multiple-value-bind (supers therep)
      (resolve-constant-initarg :direct-superclasses initargs env)
    (when therep
      (if (null supers)
	  (cremf initargs :direct-superclasses)
	  (multiple-value-bind (meta value-therep therep)
	      (resolve-constant-initarg :metaclass initargs env)
	    (when (or (when (not therep) (setf meta 'standard-class))
		      value-therep)
	      (when (setf meta (coerce-to-class meta nil env))
		(let ((default
			  (ignore-errors
			    (tclosx:class-default-superclasses
			         (tclos:class-prototype meta)))))
		  (when (and (= (length default) (length supers))
			     (every #'(lambda (c1 c2)
					(eq (coerce-to-class c1 nil env)
					    (or (coerce-to-class c2 nil env)
						'mismatch)))
				    supers default))
		    (cremf initargs :direct-superclasses))))))))
    initargs))

(define-defclass-filter :direct-slots (initargs env)
  ;; There should be something done here to filter out uninteresting stuff from
  ;; the canonic slot specifications.  Such things as
  ;;  :allocation :instance
  ;;  :type t -- or any type if switch says not needed
  ;;  :initform -- if switch says not needed
  ;;  :documentation -- if switch says not needed
  (filter-defclass-empty-list-initarg :direct-slots initargs env))

(defun filter-defclass-empty-list-initarg (initarg initargs env)
  (multiple-value-bind (value therep)
      (cgetf initargs initarg)
    (when therep
      (if (and (consp value)
	       (eq (car value) 'list)
	       (null (cdr value)))
	  (cremf initargs initarg)
	  (multiple-value-bind (value valuep constantp)
	      (translator-constant-value value env)
	    (declare (ignore constantp))
	    (when (and valuep (null value))
	      (cremf initargs initarg)))))
    initargs))

;;; Define canonicalize methods for metaclasses which are subclasses of
;;; internal-standard-class at runtime.  Assumes that the class is the first
;;; argument to the generic function.
;;; *** Note that no method is needed for method-class, since at translation
;;; *** time it is a subclass of standard-class.

(defmacro defcanonic (name lambda-list &body body)
  (let ((class (car lambda-list))
	(tail (cdr lambda-list)))
    `(progn
       (defmethod ,name ((,class standard-class) ,@tail) ,@body)
       (defmethod ,name ((,class tclos:funcallable-standard-class) ,@tail)
	 ,@body))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Determining the metaclass for defclass
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defun class-prototype-for-defclass (name options env)
  (declare (ignore name))
  (tclos:class-prototype
    (find-metaclass (do ((tail options (cdr tail)))
			((endp tail) 'standard-class)
		      (let ((option (car tail)))
			(when (and (consp option) (eq (car option) :metaclass))
			  (destructuring-bind (metaclass) (cdr option)
			    (return metaclass)))))
		    env)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Canonicalizing the defclass options
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;; CANONICALIZE-CLASS-OPTION				[Generic function]
;;;
;;; Arguments:
;;;	class -- an instance of the metaclass.
;;;	option-name -- a symbol.
;;;	option -- a symbol or a list.
;;;	canonic-class-specification -- a canonic initargs list.
;;;	environment -- an environment.
;;;
;;; Values:
;;;	new-canonic-class-specification -- a canonic initargs list.
;;;
;;; Description:  
;;;	Verifies and interprets one class option.  DEFCLASS processes class
;;;	options in the order in which they appear in the DEFCLASS form.  Class
;;;	options are processed before superclasses and slots have been
;;;	processed.
;;;
;;;	The interpretation of the class option is accomplished by adding or
;;;	modifying keywords and values to the returned canonic class
;;;	specification.  Methods are permitted to modify the
;;;	canonic-class-specification argument, but implementations are not
;;;	permitted to depend on this.
;;;
;;; Remarks:
;;;	This definition of CANONICALIZE-CLASS-OPTION is based on the definition
;;;	provided by Scott Cyphers and Dave Moon of Symbolics, in a message sent
;;;	to the MOP mailing list, subject "user interface macros", dated 5/1/90.

(defgeneric canonicalize-class-option (class key option canonic env)
  (:generic-function-class translator-generic-function))

(defun canonicalize-defclass-options (class options canonic env)
  (dolist (option options canonic)
    (when (symbolp option) (setf option (list option)))
    (setf canonic (canonicalize-class-option class
					     (car option)
					     option
					     canonic
					     env))))

;;; Warn about unrecognized options, and ignore them.
;;; *** Perhaps this actually ought to be a program-error?

(defmethod canonicalize-class-option ((class class)
				      key
				      (option cons)
				      (canonic list)
				      env)
  (declare (ignore key env))
  (warn "Ignoring invalid class option ~S." option)
  canonic)

(defmacro with-singleton-option ((&rest args) &body body)
  `(or (ignore-duplicate-option ,@args) (locally ,@body)))

(defun ignore-duplicate-option (canonic key option &optional (search key))
  (when (nth-value 1 (cgetf canonic search))
    (warn "Ignoring duplicate class ~S option ~S." key option)
    canonic))

;;; (:DOCUMENTATION { string or Nil}) => :DOCUMENTATION { string or Nil }

(defmethod canonicalize-class-option ((class class)
				      (key (eql :documentation))
				      (option cons)
				      (canonic list)
				      env)
  (declare (ignore env))
  (with-singleton-option (canonic key option)
    (destructuring-bind (doc) (cdr option)
      (check-type doc (or null string))
      (setf (cgetf canonic :documentation) doc)
      canonic)))

;;; (:METACLASS name) => :METACLASS (QUOTE name)

(defmethod canonicalize-class-option ((class class)
				      (key (eql :metaclass))
				      (option cons)
				      (canonic list)
				      env)
  (declare (ignore env))
  (with-singleton-option (canonic key option)
    (destructuring-bind (metaclass) (cdr option)
      (ensure-legal-class-name metaclass)
      (setf (cgetf canonic :metaclass) `(quote ,metaclass))
      canonic)))

;;; (:DEFAULT-INITARGS {name initform}*) =>
;;;    :DIRECT-DEFAULT-INITARGS
;;;    (LIST { (LIST (QUOTE name) initfunction (QUOTE initform)) }* )

(defcanonic canonicalize-class-option (class
				       (key (eql :default-initargs))
				       (option cons)
				       (canonic list)
				       (env t))
  (with-singleton-option (canonic key option :direct-default-initargs)
    (do ((parsed ())
	 (plist (cdr option) (cddr plist)))
	((endp plist)
	 (setf (cgetf canonic :direct-default-initargs)
	       `(list ,@(mapcar #'(lambda (entry)
				    `(list ',(car entry) ,@(cdr entry)))
			        (nreverse parsed))))
	 canonic)
      (let ((initarg (car plist))
	    (initform (cadr plist)))
	(check-type initarg symbol)
	(if (assoc initarg parsed :test #'eq)
	    (warn "Ignoring duplicate default initarg ~S with initform ~S."
		  initarg initform)
	    (push (list initarg
			(make-initfunction-form initform env)
			`(quote ,initform))
		  parsed))))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Canonicalizing the defclass superclass specification
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;; CANONICALIZE-SUPERCLASSES				[Generic function]
;;;
;;; Arguments:
;;;	class -- an instance of the metaclass.
;;;	superclasses -- the list of superclasses.
;;;	canonic-slot-specification -- a canonic initargs list.
;;;	environment -- an environment.
;;;
;;; Values:
;;;	new-canonic-class-specification -- a canonic initargs list.
;;;      
;;; Description:
;;;	Verifies and interprets the class superclasses.
;;;
;;;	This function ensures that the specified supers is a list of classes or
;;;	(potential) class names.  Note that this function is not responsible
;;;	for defaulting of superclasses when the list of supers is empty.  Such
;;;	defaulting may be performed either here or by ENSURE-CLASS.
;;;
;;;	Class options are processed before superclasses.  Slots are processed
;;;	after superclasses have been processed.  The interpretation of the
;;;	superclasses is accomplished by adding or modifying keywords and values
;;;	to the returned canonic class specification.  Methods are permitted to
;;;	modify the canonic-class-specification argument, but implementations
;;;	are not permitted to depend on this.
;;;
;;; Remarks:
;;;	This definition of CANONICALIZE-SUPERCLASSES is based on the definition
;;;	provided by Scott Cyphers and Dave Moon of Symbolics, in a message sent
;;;	to the MOP mailing list, subject "user interface macros", dated 5/1/90.
;;;	It differs from the Cyphers/Moon description in that it is not required
;;;	to do the defaulting of superclasses when none are specified. 

(defun canonicalize-defclass-supers (class supers canonic env)
  (canonicalize-superclasses class supers canonic env))

(defgeneric canonicalize-superclasses (class supers canonic env)
  (:generic-function-class translator-generic-function))

;;; ({super}*) => :DIRECT-SUPERCLASSES (LIST { (QUOTE super) }* )

(defmethod canonicalize-superclasses ((class class)
				      (supers list)
				      (canonic list)
				      (env t))
  (setf (cgetf canonic :direct-superclasses)
	(flet ((check-super (super)
		 (cond ((symbolp super)
			(ensure-legal-class-name super)
			super)
		       ((translator-typep super 'class env)
			(proper-class-name super env))
		       (t
			(error "Invalid superclass ~S." super)))))
	  `(quote ,(mapcar #'check-super supers))))
  canonic)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Canonicalizing defclass slot specifications
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;; CANONICALIZE-SLOT-SPECIFICATIONS			[Generic function]
;;;
;;; Arguments:
;;;	class -- an instance of the metaclass.
;;;	slot-specifications -- the list of slot specifications appearing
;;;	  in the DEFCLASS form.
;;;	canonic-class-specification -- a canonic initargs list.
;;;	environment -- an environment.
;;;
;;; Values:
;;;	new-canonic-class-specification -- a canonic initargs list.
;;;
;;; Description:  
;;;	Verifies and interprets the slot options.  DEFCLASS processes slot
;;;	options in the order in which they appear in the DEFCLASS form.  Slot
;;;	options are processed after class options and superclasses have been
;;;	processed.  The interpretation of the slot options is accomplished by 
;;;	adding or modifying keywords and values to the returned canonic class
;;;	specification.  Methods are permitted to modify the
;;;	canonic-class-specification argument, but implementations are not
;;;	permitted to depend on this.
;;;
;;;	For the benefit of classes in which slot order is significant, the
;;;	CANONICALIZE-SLOT-SPECIFICATIONS method specialized on STANDARD-CLASS
;;;	puts the canonic slot descriptions in the same order in which they
;;;	appear in the slot-specifications argument (which is the same order
;;;	they appear in the DEFCLASS form).
;;;
;;; Remarks:
;;;	This definition of CANONICALIZE-SLOT-SPECIFICATIONS is based on the
;;;	definition provided by Scott Cyphers and Dave Moon of Symbolics, in a
;;;	message sent to the MOP mailing list, subject "user interface macros",
;;;	dated 5/1/90.
;;;
;;; CANONICALIZE-SLOT-SPECIFICATION			[Generic function]
;;;
;;; Arguments:
;;;	class -- an instance of the metaclass.
;;;	slot-specification -- one slot specification appearing
;;;	  in the DEFCLASS form.
;;;	canonic-class-specification -- a canonic initargs list.
;;;	environment -- an environment.
;;;
;;; Values:
;;;	new-canonic-class-specification -- a canonic initargs list.
;;;
;;; Description:  
;;;	Verifies and interprets one slot specification.  The interpretation of
;;;	the slot specification is accomplished by adding or modifying keywords
;;;	and values to the returned canonic class specification.  Methods are
;;;	permitted to modify the canonic-class-specification argument, but
;;;	implementations are not permitted to depend on this.  All elements of
;;;	the canonic class specification should be forms to be evaluated at
;;;	definition time.
;;;
;;; Remarks:
;;;	This definition of CANONICALIZE-SLOT-SPECIFICATION is based on the
;;;	definition provided by Scott Cyphers and Dave Moon of Symbolics, in a
;;;	message sent to the MOP mailing list, subject "user interface macros",
;;;	dated 5/1/90.
;;;
;;; CANONICALIZE-SLOT-OPTION				[Generic function]
;;;
;;; Arguments:
;;;	class -- an instance of the metaclass.
;;;	canonic-class-specification -- a canonic initargs list.
;;;	option -- a symbol.
;;;	value -- the value of the option.
;;;	canonic-slot-specification -- a canonic initargs list.
;;;	environment -- An environment.
;;;
;;; Values:
;;;	new-canonic-class-specification -- a canonic initargs list.
;;;	new-canonic-slot-specification -- a canonic initargs list.
;;;
;;; Description:  
;;;	Verifies and interprets one slot option. The interpretation of the slot
;;;	option is accomplished by adding or modifying keywords and values to
;;;	the returned canonic class specification and/or the returned canonic
;;;	slot specification.  Methods are permitted to modify the canonic
;;;	specification arguments, but implementations are not permitted to
;;;	depend on this.  All elements of the canonic specification arguments
;;;	should be forms to be evaluated at definition time.
;;;
;;; Remarks:
;;;	This definition of CANONICALIZE-SLOT-OPTION is based on the definition
;;;     provided by Scott Cyphers and Dave Moon of Symbolics, in a message sent
;;;     to the MOP mailing list, subject "user interface macros", dated 5/1/90.

(defun canonicalize-defclass-slots (class slots canonic env)
  (canonicalize-slot-specifications class slots canonic env))

(defgeneric canonicalize-slot-specifications (class slots canonic env)
  (:generic-function-class translator-generic-function))

(defgeneric canonicalize-slot-specification (class slot-spec canonic env)
  (:generic-function-class translator-generic-function))

(defgeneric canonicalize-slot-option
    (class canonic key option canonic-slot env)
  (:generic-function-class translator-generic-function))

;;; ({slot-spec}*) => :DIRECT-SLOTS (LIST {canonicalized-slot-spec}*)
;;;
;;; *** This method should be on slotted-class (rather than
;;; *** internal-standard-class) if the slot access protocol is defined for
;;; *** structure-class.

(defmethod canonicalize-slot-specifications ((class class)
					     (slots list)
					     (canonic list)
					     (env t))
  (setf (cgetf canonic :direct-slots) (list 'list))
  (dolist (slot slots)
    (setf canonic (canonicalize-slot-specification class slot canonic env)))
  canonic)

;;; Listify slot-specifier which is a symbol, and then canonicalize.

(defmethod canonicalize-slot-specification ((class class)
					    (slot symbol)
					    (canonic list)
					    (env t))
  (canonicalize-slot-specification class (list slot) canonic env))

;;; Iterate over the slot description from the defclass form, applying
;;; canonicalize-slot-option to the key/value pairs and collecting the results.

(defmethod canonicalize-slot-specification ((class class)
					    (slot cons)
					    (canonic list)
					    (env t))
  (let ((direct-slots (cgetf canonic :direct-slots)))
    (when (null direct-slots)
      (setf direct-slots (list 'list))
      (setf (cgetf canonic :direct-slots) direct-slots))
    (let ((name (car slot))
	  (canonic-slot (list 'list)))
      (check-type name symbol)
      ;; Check for duplicate slot names
      (dolist (old-slot (cdr direct-slots))
	(multiple-value-bind (value therep)
	    (cgetf (cdr old-slot) :name)
	  (when therep
	    (multiple-value-setq (value therep)
	      (translator-constant-value value env))
	    (when (and therep (eq name value))
	      (warn "Ignoring duplicate slot specification: ~S." slot)
	      (return-from canonicalize-slot-specification canonic)))))
      (setf direct-slots (last direct-slots))
      (setf (cdr direct-slots) (list canonic-slot))
      (setf direct-slots (cdr direct-slots))
      (push :name slot)
      (do ((plist slot (cddr plist)))
	  ((endp plist) canonic)
	(if (endp (cdr plist))
	    (warn "Ignoring final unpaired slot option: ~S." (car plist))
	    (multiple-value-bind (new-canonic new-slot)
		(canonicalize-slot-option class
					  canonic
					  (car plist)
					  (cadr plist)
					  (cdr canonic-slot)
					  env)
	      (setf canonic new-canonic)
	      (setf (cdr canonic-slot) new-slot)
	      (setf (car direct-slots) canonic-slot)))))))

;;; Warn about and ignore unrecognized option.
;;; *** Perhaps this should instead be a program-error?

(defmethod canonicalize-slot-option ((class class)
				     (canonic list)
				     (key t)
				     (value t)
				     (canonic-slot list)
				     env)
  (declare (ignore env))
  (warn "Ignoring unknown slot option ~S with value ~S." key value)
  (values canonic canonic-slot))

(defmacro with-singleton-slot-option ((&rest args) &body body)
  `(unless (ignore-duplicate-slot-option ,@args) (locally ,@body)))

(defun ignore-duplicate-slot-option (canonic key value &optional (search key))
  (when (nth-value 1 (cgetf canonic search))
    (warn "Ignoring duplicate slot option ~S with value ~S." key value)
    t))

;;; :NAME name => :NAME (QUOTE name)

(defmethod canonicalize-slot-option ((class class)
				     (canonic list)
				     (key (eql :name))
				     (value t)
				     (canonic-slot list)
				     env)
  (declare (ignore env))
  (with-singleton-slot-option (canonic-slot key value)
    (check-type value symbol)
    (setf (cgetf canonic-slot key) `(quote ,value)))
  (values canonic canonic-slot))

;;; :DOCUMENTATION {string or Nil} => :DOCUMENTATION {string or Nil}

(defmethod canonicalize-slot-option ((class class)
				     (canonic list)
				     (key (eql :documentation))
				     (value t)
				     (canonic-slot list)
				     env)
  (declare (ignore env))
  (with-singleton-slot-option (canonic-slot key value)
    (check-type value (or string null))
    (setf (cgetf canonic-slot key) value))
  (values canonic canonic-slot))

;;; :TYPE typespec => :TYPE (QUOTE typespec)

(defmethod canonicalize-slot-option ((class class)
				     (canonic list)
				     (key (eql :type))
				     (value t)
				     (canonic-slot list)
				     env)
  (declare (ignore env))
  (with-singleton-slot-option (canonic-slot key value)
    (setf (cgetf canonic-slot key) `(quote ,value)))
  (values canonic canonic-slot))

;;; :ALLOCATION :INSTANCE => :ALLOCATION (QUOTE :INSTANCE)

(defcanonic canonicalize-slot-option (class
				      (canonic list)
				      (key (eql :allocation))
				      (value (eql :instance))
				      (canonic-slot list)
				      env)
  (declare (ignore env))
  (with-singleton-slot-option (canonic-slot key value)
    (setf (cgetf canonic-slot key) `(quote ,value)))
  (values canonic canonic-slot))

;;; :ALLOCATION :CLASS => :ALLOCATION (QUOTE :CLASS)

(defcanonic canonicalize-slot-option (class
				      (canonic list)
				      (key (eql :allocation))
				      (value (eql :class))
				      (canonic-slot list)
				      env)
  (declare (ignore env))
  (with-singleton-slot-option (canonic-slot key value)
    (setf (cgetf canonic-slot key) `(quote ,value)))
  (values canonic canonic-slot))

;;; :INITFORM initform =>
;;;    :INITFUNCTION initfunction-form
;;;    :INITFORM (QUOTE initform)

(defmethod canonicalize-slot-option ((class class)
				     (canonic list)
				     (key (eql :initform))
				     (value t)
				     (canonic-slot list)
				     (env t))
  (with-singleton-slot-option (canonic-slot key value)
    (with-singleton-slot-option (canonic-slot key value :initfunction)
      (multiple-value-bind (slot-name therep)
	  (cgetf canonic-slot :name)
	(when therep
	  (multiple-value-setq (slot-name therep)
	    (translator-constant-value slot-name env)))
	(setf (cgetf canonic-slot :initfunction)
	      (make-initfunction-form value env slot-name))
	(setf (cgetf canonic-slot :initform) `(quote ,value)))))
  (values canonic canonic-slot))

(defun add-multi-canonic-slot (canonic key value)
  (let ((list (cgetf canonic key)))
    (when (null list)
      (setf list (list 'quote nil))
      (setf (cgetf canonic key) list))
    (let ((values (cadr list)))
      (if (member value values :test #'equal)
	  (warn "Ignoring duplicate ~S entry ~S." key value)
	  (setf (cadr list) (nconc values (list value))))
      canonic)))

;;; :READER name => :READERS (QUOTE ({reader}* name))

(defmethod canonicalize-slot-option ((class class)
				     (canonic list)
				     (key (eql :reader))
				     (value t)
				     (canonic-slot list)
				     env)
  (declare (ignore env))
  (check-type value symbol)
  (setf canonic-slot (add-multi-canonic-slot canonic-slot :readers value))
  (values canonic canonic-slot))

;;; :WRITER name => :WRITERS (QUOTE ({writer}* name))

(defmethod canonicalize-slot-option ((class class)
				     (canonic list)
				     (key (eql :writer))
				     (value t)
				     (canonic-slot list)
				     env)
  (declare (ignore env))
  (check-type value (satisfies valid-function-name-p))
  (setf canonic-slot (add-multi-canonic-slot canonic-slot :writers value))
  (values canonic canonic-slot))

;;; :ACCESSOR name =>
;;;    :READERS (QUOTE ({reader}* name))
;;;    :WRITERS (QUOTE ({writer}* (SETF name)))

(defmethod canonicalize-slot-option ((class class)
				     (canonic list)
				     (key (eql :accessor))
				     (value t)
				     (canonic-slot list)
				     env)
  (declare (ignore env))
  (check-type value symbol)
  (setf canonic-slot (add-multi-canonic-slot canonic-slot :readers value))
  (setf canonic-slot
	(add-multi-canonic-slot canonic-slot :writers `(setf ,value)))
  (values canonic canonic-slot))

;;; :INITARG name => :INITARGS (QUOTE ({initarg}* name))

(defmethod canonicalize-slot-option ((class class)
				     (canonic list)
				     (key (eql :initarg))
				     (value t)
				     (canonic-slot list)
				     env)
  (declare (ignore env))
  (check-type value symbol)
  (setf canonic-slot (add-multi-canonic-slot canonic-slot :initargs value))
  (values canonic canonic-slot))



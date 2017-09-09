;;; -*- Mode: Lisp; Package: TCLOSI; Syntax: Common-Lisp -*-
;;;
;;; Copyright (C) 1991 Chestnut Software, Inc.  All Rights Reserved.
;;;

(in-package "TCLOSI")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/class-record.lisp,v $"
 "$Revision: 1.1 $"
 "$Date: 2006/02/28 21:59:01 $")

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Caching information about classes
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;; There are some kinds of information collected at translation time that are
;;; fairly expensive to compute because they involve performing a walk of all
;;; the subclasses of some class.  In order to avoid recomputing them
;;; frequently, we instead cache the results in slots of the appropriate
;;; objects.  The problem is that defining new classes or redefining existing
;;; classes can invalidate the cached information.  To handle this problem,
;;; each cached value has associated with it a key that allows the value to be
;;; validated.  Whenever a new class is defined or an existing class is
;;; redefined in an incompatible fashion, all existing keys are marked invalid.
;;; Whenever an access to a cached value is performed, the key must first be
;;; validated, with recomputation forced if the validation fails.

;;; The current key
(defvar *class-cache-validation-key* (list nil))

;;; Get the current key -- used to initialize or update a recorded key.
(defun class-cache-validation-key ()
  *class-cache-validation-key*)

;;; Predicate which returns true if a recorded key is valid.
(defun class-cache-valid-p (key)
  (eq key *class-cache-validation-key*))

;;; Mark all recorded keys (and the associated values) as invalid.
(defun invalidate-class-cache ()
  (setf *class-cache-validation-key* (list nil)))

;;; Return the value of a cached slot from an object.
;;;   Slot-name is the name of the cached slot.
;;;   Compute is a function of one argument, the object, which computes the
;;;     current value for the slot.
;;;   Check is a function of three arguments, the object, the new value, and
;;;     the old value.  It's purpose is to issue warnings or signal errors as
;;;     appropriate to notify the user of the change.

(defun handle-cached-slot (object slot-name compute check)
  (if (not (slot-boundp object slot-name))
      (cdr (setf (slot-value object slot-name)
		 (cons (class-cache-validation-key)
		       (funcall compute object))))
      (let* ((entry (slot-value object slot-name))
	     (value (cdr entry)))
	(if (class-cache-valid-p (car entry))
	    value
	    (let ((newvalue (setf (car entry) (class-cache-validation-key)
				  (cdr entry) (funcall compute object))))
	      (funcall check object newvalue value)
	      newvalue)))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Internal slot access macros
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;; Some slots have internal access C macros automatically generated for them.
;;; The decision procedure for whether a macro should be defined is:
;;;
;;; 1. Generate a reader iff there is not a generic function reader defined for
;;; the slot.
;;;
;;; 2. A writer should be generated if there is not a generic function writer
;;; and the slot needs to be modified other than via initarg processing in
;;; shared-initialize.
;;;
;;; The macros are actually created by the dump phase.  The runtime's internal
;;; prefix is automatically prepended to the names specified in this form.

(defparameter *internal-slot-accessors* ())
(defvar *internal-slot-accessors-sorted* nil)

(defmacro define-internal-slot (slot-name &key reader writer boundp)
  `(notice-internal-reader ',slot-name ',reader ',writer ',boundp))

(defun notice-internal-reader (slot-name reader-name writer-name boundp-name)
  (check-type slot-name symbol)
  (check-type reader-name (or null string))
  (check-type writer-name (or null string))
  (check-type boundp-name (or null string))
  (setf *internal-slot-accessors-sorted* nil)
  (let ((entry (assoc slot-name *internal-slot-accessors*)))
    (if (null entry)
	(push (list slot-name reader-name writer-name boundp-name)
	      *internal-slot-accessors*)
	(flet ((update (entry index new type)
		 (when (not (equal new (nth index entry)))
		   (cerror "Replace internal ~A name for ~S."
			   "Internal ~A for ~S was ~S, now specified as ~S."
			   type (first entry) (nth index entry) new)
		   (setf (nth index entry) new))))
	  (update entry 1 reader-name "reader")
	  (update entry 2 writer-name "writer")
	  (update entry 3 boundp-name "boundp")))
    slot-name))

(defun internal-slot-accessors ()
  (if *internal-slot-accessors-sorted*
      *internal-slot-accessors*
      (setf *internal-slot-accessors-sorted* t
	    *internal-slot-accessors*
	        (sort *internal-slot-accessors* #'string< :key #'car))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Class records
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;; The class class-record is used in the translation time representation of
;;; classes.  Each class in the translator's environment has an associated
;;; class-record object that actually contains the translator's information
;;; about the class.
;;;
;;; Many of the the generic functions defined below for class records
;;; correspond to class accessors defined in the MOP.  The translation time
;;; definitions of the class accessors find the associated class-record object
;;; and call the corresponding accessor on it.

(defgeneric class-record-related-class (class-record)
  ;; Returns the translation-time class metaobject related to the record.
  (:generic-function-class translator-generic-function))

(defgeneric class-record-metaclass (class-record)
  ;; Returns the supposed metaclass for the related class metaobject.
  ;; This is used to detect changes due to redefinition that might invalidate
  ;; previous information and assumptions.
  (:generic-function-class translator-generic-function))

(defgeneric class-record-name (class-record)
  ;; Corresponds to tclos:class-name.
  ;; Returns the name of the record.  The function class-name is defined in
  ;; terms of this for translation-time class metaobjects.
  (:generic-function-class translator-generic-function))

(defgeneric (setf class-record-name) (value class-record)
  ;; Corresponds to (setf tclos:class-name).
  ;; The corresponding writer function.
  (:generic-function-class translator-generic-function))

(defgeneric class-record-precedence-list (class-record)
  ;; Corresponds to tclos:class-precedence-list.
  ;; Returns the translator's notion of the class precedence list for the
  ;; related class, or Nil if the definition of the class includes forward
  ;; referenced supers (directly or indirectly by inheritance).
  (:generic-function-class translator-generic-function))

(defgeneric class-record-direct-superclasses (class-record)
  ;; Corresponds to tclos:class-direct-superclasses.
  ;; Returns the translator's notion of the direct superclasses for the related
  ;; class.
  (:generic-function-class translator-generic-function))

(defgeneric class-record-direct-subclasses (class-record)
  ;; Corresponds to tclos:class-direct-subclasses.
  ;; Returns the translator's notion of the direct subclasses for the related
  ;; class.
  (:generic-function-class translator-generic-function))

(defgeneric (setf class-record-direct-subclasses) (value class-record)
  ;; The corresponding writer function.
  (:generic-function-class translator-generic-function))

(defgeneric class-record-direct-slots (class-record)
  ;; Corresponds to tclos:class-direct-slots.
  ;; Returns the translator's notion of the direct slot definition objects for
  ;; the related class.
  (:generic-function-class translator-generic-function))

(defgeneric class-record-slots (class-record)
  ;; Corresponds to tclos:class-slots.
  ;; Returns the translator's notion of the effective slot definition objects
  ;; for the related class.
  (:generic-function-class translator-generic-function))

(defgeneric class-record-direct-default-initargs (class-record)
  ;; Corresponds to tclos:class-direct-default-initargs.
  ;; Returns the translator's notion of the direct default initargs for the
  ;; related class.
  (:generic-function-class translator-generic-function))

(defgeneric class-record-default-initargs (class-record)
  ;; Corresponds to tclos:class-default-initargs.
  ;; Returns the translator's notion of the default initargs for the related
  ;; class.
  (:generic-function-class translator-generic-function))

(defgeneric class-record-documentation (class-record)
  (:generic-function-class translator-generic-function))

(defgeneric (setf class-record-documentation) (value class-record)
  (:generic-function-class translator-generic-function))

(defgeneric class-record-prototype (class-record)
  (:generic-function-class translator-generic-function))

(defgeneric class-record-static-p (class-record)
  ;; Returns true if neither the class nor any of its subclasses may be
  ;; redefined at runtime or have additional subclasses defined at runtime
  ;; which were not known to the translator.
  (:generic-function-class translator-generic-function))

(defclass class-record ()
  ((name                        :initarg :name
				:initform nil
				:accessor class-record-name
				:type symbol
				)
   (direct-superclasses         :initarg :direct-superclasses
				:reader class-record-direct-superclasses
				:type list
				)
   (direct-subclasses           :initarg :direct-subclasses
                                :initform nil
				:accessor class-record-direct-subclasses
				:type list
				)
   (direct-slots                :initarg :direct-slots
				:reader class-record-direct-slots
				:type list
				)
   (direct-default-initargs     :initarg :direct-default-initargs
				:initform nil
				:reader class-record-direct-default-initargs
				:type list
				)
   (doc-string                  :initform nil
				:initarg :documentation
				:accessor class-record-documentation
				:type (or null string)
				)
   (precedence-list             :type list
				)
   (slots                       :type list
				)
   (default-initargs            :type list
                                )
   (prototype)
   (related-class               :initarg :related-class
				:reader class-record-related-class
				:type class
				)
   (metaclass                   :initarg :metaclass
				:reader class-record-metaclass
				)
   (static)
   ))

;;; for use by copy-environment.
;;; This should be a generic function, in case subclasses of class-record
;;; are created someday.

(defvar *copying-class-record* nil)

(defun copy-class-record (old-record)
  (let* ((*copying-class-record* t)
	 (new-record
	  (make-instance
	   'class-record
	   :name (class-record-name old-record)
	   :direct-superclasses
	   (copy-list (class-record-direct-superclasses old-record))
	   :direct-subclasses
	   (copy-list (class-record-direct-subclasses old-record))
	   :direct-slots
	   (mapcar #'copy-direct-slot
		   (class-record-direct-slots old-record))
	   :direct-default-initargs
	   (copy-list
	    (class-record-direct-default-initargs old-record))
	   :documentation
	   (class-record-documentation old-record)
	   :related-class
	   (class-record-related-class old-record)
	   :metaclass (class-record-metaclass old-record))))
    ;; don't use accessors for these, since they will
    ;; compute a value if the current value is nil. Use slot-value directly
    ;; instead.
    (when (slot-boundp old-record 'precedence-list)
      (setf (slot-value new-record 'precedence-list)
	    (copy-list (slot-value old-record 'precedence-list))))
    (when (slot-boundp old-record 'slots)
      (setf (slot-value new-record 'slots)
	    (mapcar #'copy-slot (slot-value old-record 'slots))))
    (when (slot-boundp old-record 'default-initargs)
      (setf (slot-value new-record 'default-initargs)
	    (copy-list (slot-value old-record 'default-initargs))))
    (when (slot-boundp old-record 'prototype)
      (setf (slot-value new-record 'prototype)
	    (slot-value old-record 'prototype)))
    ;; leave static unbound; it can get lazily computed when appropriate.
    new-record))
		   
;;; For now, this is certainly good enough, since we only use copy-environment
;;; on the initial environment, and the slots slot in all the instances of
;;; class record is empty anyway.
(defun copy-slot (slot) (copy-direct-slot slot))

;;; The variables *metaobject-slots* and *class-slots* describe the runtime
;;; representation for the classes METAOBJECT and CLASS, respectively.

(defparameter *metaobject-slots*
  '((tclos-run:name
         :initarg :name
         :initform nil
         :accessor tclos-run:metaobject-name
         )
    (tclos-run:doc-string
         :initarg :documentation
         :initform nil
         :accessor tclos-run:metaobject-documentation
         :type (or null string)
         )
    ))

(defparameter *class-slots*
  '((tclos-run:name
         ;; Other information inherited from METAOBJECT.
         :accessor tclos:class-name
         )
    (tclos-run:direct-superclasses
         :initarg :direct-superclasses
         :reader tclos:class-direct-superclasses
         :type list
         )
    (tclos-run:direct-subclasses
         :initform nil
         :reader tclos:class-direct-subclasses
         :writer tclos-run:set-class-direct-subclasses
         :type list
         )
    (tclos-run:direct-slots
         :initarg :direct-slots
         :reader tclos:class-direct-slots
         :type list
         )
    (tclos-run:direct-default-initargs
         :initform nil
         :initarg :direct-default-initargs
         :reader tclos:class-direct-default-initargs
         :type list
         )
    (tclos-run:status-bits
         :type integer
	 :initform 0
	 :initfunction tclos-run:constantly-zero-initfunction
	 :accessor tclos-run:class-status-bits
	 )
    ;; Reset to unbound by make-instances-obsolete
    ;; Computed by finalize-inheritance
    ;; Lazy reader tclos:class-precedence-list
    (tclos-run:precedence-list
         :type list
         )
    ;; Reset to unbound by make-instances-obsolete
    ;; Computed by finalize-inheritance
    ;; Lazy reader tclos:class-slots
    (tclos-run:slots
         :type list
         )
    ;; Alist of slot names and associated effective slot definition
    ;; metaobjects.  This is used to speed up find-effective-slot-definition.
    ;; Reader is %class-slots-alist
    ;; Reset to unbound by make-instances-obsolete
    ;; Computed by finalize-inheritance and find-effective-slot-definition.
    (tclos-run:slots-alist
         :type list
	 )
    (tclos-run:shared-slot-locations
         :initform nil
	 :type list
	 )
    ;; Reset to unbound by make-instances-obsolete
    ;; Computed lazily by class-default-initargs.
    (tclos-run:initargs
         :type list
         )
    ;; Reset to unbound by make-instances-obsolete
    ;; Computed lazily by class-prototype.
    (tclos-run:prototype)
    ;; Reset to Nil by make-instances-obsolete
    ;; Computed by finalize-inheritance
    (tclos-run:wrapper
         :initform nil
	 )
    ;; These are all maintained by finalization.
    ;; Reset to unbound by make-instances-obsolete
    ;; Computed lazily by reader functions with the corresponding names.
    ;; The values are data structures used by the corresponding validation
    ;; procedure (typically lists of valid initargs).
    (tclos-run:valid-change-class-initargs
         :writer (setf tclos-run:valid-change-class-initargs)
         )
    (tclos-run:valid-creation-initargs
         :writer (setf tclos-run:valid-creation-initargs)
         )
    (tclos-run:valid-reinitialization-initargs
         :writer (setf tclos-run:valid-reinitialization-initargs)
         )
    ))

;;; List of slots whose computed values are forgotten by the standard method
;;; on make-instances-obsolete.  This list is passed to the runtime via a list
;;; in the bootstrap information created by dump-clos-bootstrap-info.

(defparameter *make-instances-obsolete-slots-to-flush*
  '(tclos-run:precedence-list
    tclos-run:slots
    tclos-run:slots-alist
    tclos-run:initargs
    tclos-run:prototype
    tclos-run:wrapper
    tclos-run:valid-change-class-initargs
    tclos-run:valid-creation-initargs
    tclos-run:valid-reinitialization-initargs
    ))

(define-internal-slot tclos-run:direct-subclasses
    :reader "CLASS_DIRECT_SUBCLASSES"
    :boundp "CLASS_DIRECT_SUBCLASSES_BOUNDP"
    :writer "SET_CLASS_DIRECT_SUBCLASSES"
    )

(define-internal-slot tclos-run:precedence-list
    :reader "CLASS_PRECEDENCE_LIST"
    :boundp "CLASS_PRECEDENCE_LIST_BOUNDP"
    :writer "SET_CLASS_PRECEDENCE_LIST")

(define-internal-slot tclos-run:slots
    :reader "CLASS_SLOTS"
    :boundp "CLASS_SLOTS_BOUNDP"
    :writer "SET_CLASS_SLOTS")

(define-internal-slot tclos-run:slots-alist
    :reader "CLASS_SLOTS_ALIST"
    :boundp "CLASS_SLOTS_ALIST_BOUNDP"
    :writer "SET_CLASS_SLOTS_ALIST")

(define-internal-slot tclos-run:shared-slot-locations
    :reader "CLASS_SHARED_SLOT_LOCATIONS"
    :boundp "CLASS_SHARED_SLOT_LOCATIONS_BOUNDP"
    :writer "SET_CLASS_SHARED_SLOT_LOCATIONS")

(define-internal-slot tclos-run:initargs
    :reader "CLASS_DEFAULT_INITARGS"
    :boundp "CLASS_DEFAULT_INITARGS_BOUNDP"
    :writer "SET_CLASS_DEFAULT_INITARGS")

(define-internal-slot tclos-run:prototype
    :reader "CLASS_PROTOTYPE"
    :boundp "CLASS_PROTOTYPE_BOUNDP"
    :writer "SET_CLASS_PROTOTYPE")

(define-internal-slot tclos-run:wrapper
    :reader "CLASS_WRAPPER"
    :boundp "CLASS_WRAPPER_BOUNDP"
    :writer "SET_CLASS_WRAPPER")

;;; Provide initforms for forward referenced classes.

(defparameter *forward-referenced-class-slots*
  '((tclos-run:direct-slots
         :initform nil
	 )
    ))
  
;;; Provide initforms for structure classes.

(defparameter *structure-class-slots*
  '((tclos-run:direct-slots
         :initform nil
         )
    ))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Mapping from class objects to the associated class-record objects
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;; Note that this works only because there is exactly one translator
;;; environment, with the property lookup accessor (class-record) defaulting
;;; its environment argument appropriately.  If the translator were reentrent,
;;; this might lose.  Of course, there are other places that have this problem
;;; too.

#-(and lcl4.1 (not lcl4.1.1))
(define-translator-property class-record #'copy-class-record)

#+(and lcl4.1 (not lcl4.1.1))
(progn

(define-translator-property internal-class-record #'copy-class-record)

(eval-when (compile load eval)

(defun class-record (class &optional env)
  (internal-class-record (slot-value class 'clos::name) env))

(defun set-class-record (new-value class &optional env)
  (setf (internal-class-record (slot-value class 'clos::name) env) new-value))

(defsetf class-record (class &optional env) (new-value)
  `(set-class-record ,new-value ,class ,env))

)
)

(defmacro with-class-record ((var class errorp) &body body)
  (let ((class-var (gensym))
	(record-var (gensym)))
    `(let* ((,class-var ,class)
	    (,record-var (class-record ,class-var)))
       (if (and ,errorp (null ,record-var))
	   (class-record-missing-error ,class-var)
	   (let ((,var ,record-var)) ,@body)))))

(defun class-record-missing-error (class)
  (error "The class ~S is not known to the translator." class))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Methods on class-record
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defmethod print-object ((record class-record) stream)
  (print-unreadable-object (record stream :type t :identity t)
    (if (not (slot-boundp record 'name))
	(write-string "<unnamed>" stream)
	(let ((name (class-record-name record)))
	  (if (null name)
	      (write-string "Anonymous" stream)
	      (prin1 name stream))))))

;;; Validate initargs before doing initialization.

(defmethod initialize-instance :before ((record class-record) &rest initargs)
  ;; Might not be supported.
  ;; (declare (dynamic-extent initargs))
  (apply #'validate-class-record-initargs record nil initargs))

(defmethod initialize-instance :after ((record class-record) &rest initargs)
  (declare (ignore initargs))
  (unless (slot-boundp record 'metaclass)
    (setf (slot-value record 'metaclass)
	  (class-of (class-record-related-class record))))
  (ensure-reader/writer-generic-functions record)
  (invalidate-class-cache))

(defmethod reinitialize-instance :before ((record class-record) &rest initargs)
  ;; Might not be supported.
  ;; (declare (dynamic-extent initargs))
  (apply #'validate-class-record-initargs record t initargs))

(defmethod reinitialize-instance ((record class-record) &rest initargs)
  (declare (ignore initargs))
  (let ((metaclass (class-record-metaclass record))
	(supers (class-record-direct-superclasses record))
	(slots (class-record-direct-slots record)))
    (multiple-value-prog1
        (call-next-method)
      (ensure-compatible-class-record-redefinition
           record
	   :metaclass metaclass
	   :direct-superclasses supers
	   :direct-slots slots))))

(defun validate-class-record-initargs
       (record initializedp
	&key (related-class nil rcp)
	     (name nil namep)
	     (direct-superclasses (required-keyword :direct-superclasses))
	     (direct-slots (required-keyword :direct-slots))
	     (direct-default-initargs nil)
	     (documentation nil)
	;; Added because Lucid improperly passes in *&#&*%
	;; 'clos::initargs-validated keyword that we weren't expecting.
	&allow-other-keys)
  (declare (type class-record))
  (if (not initializedp)
      (progn
	(if (not rcp)
	    (required-keyword :related-class)
	    (check-type related-class class))
	(if (not namep)
	    (required-keyword :name)
	    (ensure-legal-class-name name)))
      (progn
	(when rcp
	  (unless (eq related-class (class-record-related-class record))
	    (error "Cannot change the related class for ~S to ~S."
		   record related-class)))
	(when namep
	  (ensure-legal-class-name name))))
  (check-type direct-superclasses list)
  (map nil #'(lambda (super) (check-type super class)) direct-superclasses)
  (check-type direct-slots list)
  (map nil #'(lambda (slotd) (check-type slotd tclos:slot-definition))
       direct-slots)
  (check-type direct-default-initargs list)
  (check-type documentation (or null string)))

;;; This variable is bound to true in places where the the translator is being
;;; bootstrapped.  It is used to inhibit certain kinds of consistency checks
;;; while building the initial class hierarchy.
(defvar *building-initial-class-hierarchy* nil)

;;; This function gets called *after* redefinition, and complains about changes
;;; that are not supported.
(defun ensure-compatible-class-record-redefinition
    (record &key ((:direct-superclasses supers)
		  (required-keyword :direct-superclasses))
	         ((:direct-slots slots) (required-keyword :direct-slots))
		 ((:metaclass metaclass) (required-keyword :metaclass))
		 )
  (let ((name (or (class-record-name record)
		  (class-record-related-class record))))
    (labels ((finish-update ()
	       (flush-lazy-slots-downward record)
	       (return-from ensure-compatible-class-record-redefinition nil))
	     (incompatible-class-record-redefinition
		 (format-string &rest format-arguments)
	       (if *building-initial-class-hierarchy*
		   (invalidate-class-cache)
		   (incompatible-class-record-redefinition-1
		        format-string format-arguments)))
	     (incompatible-class-record-redefinition-1
		 (format-string format-arguments)
	       ;; If in the first pass of the translator, only issue a
	       ;; warning.  In the second pass signal an error, with a
	       ;; restart to ignore the problem and finish the update.
	       (if *compile-time-only*
		   (progn
		     (apply #'warn format-string format-arguments)
		     (invalidate-class-cache))
		   (restart-case
		       (apply #'error format-string format-arguments)
		     (nil ()
		       :report (lambda (s)
				 (format s "Finish update for class ~S." name))
		       (invalidate-class-cache)
		       (finish-update))))))
      (let ((fc (translator-find-class 'tclos:forward-referenced-class nil)))
	(when (and fc (eq fc metaclass))
	  (finish-update)))
      (unless (eq metaclass (class-record-metaclass record))
	(incompatible-class-record-redefinition
	  "The metaclass of the class ~S has been changed from ~S to ~S."
	  name
	  metaclass
	  (class-record-metaclass record)))
      (unless (equal supers (class-record-direct-superclasses record))
	(incompatible-class-record-redefinition
	  "The direct superclasses for the class ~S have been changed.~@
           The new direct superclasses are:~{~%  ~S~}~@
           The old direct superclasses are:~{~%  ~S~}"
	  name
	  (class-record-direct-superclasses record)
	  supers))
      (let ((new-slots (class-record-direct-slots record)))
	(let ((removed (set-difference slots new-slots
				       :key #'tclos:slot-definition-name)))
	  (when removed
	    (incompatible-class-record-redefinition
	      "The following slots have been removed from the class ~S:~
               ~{~%  ~S~}"
	     name (mapcar #'tclos:slot-definition-name removed))))
	(let ((added (set-difference new-slots slots
				     :key #'tclos:slot-definition-name)))
	  (when added
	    (incompatible-class-record-redefinition
	      "The following slots have been added to the class ~S:~
               ~{~%  ~S~}"
	      name (mapcar #'tclos:slot-definition-name added))))
	(dolist (slot slots)
	  (let* ((slot-name (tclos:slot-definition-name slot))
		 (match (find slot-name new-slots
			      :key #'tclos:slot-definition-name)))
	    (when match
	      (unless (equal (tclos:slot-definition-allocation slot)
			     (tclos:slot-definition-allocation match))
		(incompatible-class-record-redefinition
		  "The allocation type for the ~S slot of ~S has been changed~@
                   from ~S to ~S."
		  slot-name name
		  (tclos:slot-definition-allocation slot)
		  (tclos:slot-definition-allocation match)))))))
      (finish-update))))

;;; When reinitializing, flush lazy slots so that they will be recomputed.

;;; List of lazy slot names.
(defparameter *lazy-class-record-slots* nil)

;;; Flush lazy slots of a class record.
(defun flush-lazy-slots (record)
  (declare (type class-record record))
  (mapc #'(lambda (slot-name)
	    (slot-makunbound record slot-name))
	*lazy-class-record-slots*))

;;; Flush lazy slots for a class and all its subclasses.
(defun flush-lazy-slots-downward (record)
  (let ((table (make-hash-table :test 'eq)) ; remember visited records
	(pending nil))                      ; list of records to visit
    (loop
      (unless (gethash record table)        ; unless already visited
	(setf (gethash record table) t)     ; mark it visited
	(flush-lazy-slots record)           ; flush it
	;; collect unvisited subclasses for future visitation
	(dolist (sub (class-record-direct-subclasses record))
	  (with-class-record (record sub t)
	    (unless (gethash record table)
	      (push record pending)))))
      (if (null pending) (return)           ; done
	  (setf record (pop pending))))))   ; visit next pending record

(defmethod reinitialize-instance :after ((record class-record) &rest initargs)
  (declare (ignore initargs))
  (flush-lazy-slots-downward record)
  (ensure-reader/writer-generic-functions record))

;;; This maintains the direct-subclasses slot on class records.
;;; Unfortunately, it's hard to maintain this correctly in different
;;; environments, because functions like add-direct-subclass don't take
;;; an environment argument. So for now we bypass this completely
;;; when copying a class record.
(defmethod shared-initialize :around
  ((record class-record) slots &rest initargs &key direct-superclasses)
  (declare (ignore slots initargs direct-superclasses))
  (if *copying-class-record*
      (call-next-method)
    (let ((old-direct-supers (when (slot-boundp record 'direct-superclasses)
			       (class-record-direct-superclasses record))))
      (multiple-value-prog1
	  (call-next-method)
	(let ((class (class-record-related-class record))
	      (direct-supers (class-record-direct-superclasses record)))
	  ;; Update the direct subclasses of removed direct supers
	  (dolist (old-super old-direct-supers)
	    (unless (member old-super direct-supers)
	      (tclosx:remove-direct-subclass old-super class)))
	  ;; Update the direct subclasses of added direct supers
	  (dolist (super direct-supers)
	    (unless (member super old-direct-supers)
	      (tclosx:add-direct-subclass super class))))
	))))

;;; *** We need some way to invalidate the class-record when the class gets
;;; *** reinitialized or updated.  The invalidation would then be cleared by
;;; *** reinitializing the class-record.  Part of the problem is that doing
;;; *** this seems to require defining methods on the following functions with
;;; *** the specified specializers.
;;; ***
;;; ***  REINITIALIZE-INSTANCE (CLASS)
;;; ***  UPDATE-INSTANCE-FOR-REDEFINED-CLASS (CLASS T T T)
;;; ***  UPDATE-INSTANCE-FOR-DIFFERENT-CLASS (T CLASS)
;;; ***
;;; *** Unfortunately, this cannot be done portably since there is no way to
;;; *** know what method qualifiers might be needed in order to avoid a
;;; *** collision with methods from the implementation or some other
;;; *** application.


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Class accessor functions
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;; These are all the accessor functions defined on classes which are specified
;;; by ANSI or the list of exported CLOS symbols proposed by Moon.  In general,
;;; they are only defined on classes known to the translator (ie. there exists
;;; a class record for the class in the translator environment).  For functions
;;; that are actually in the ANSI standard (ie. not just proposed MOP), these
;;; functions trap out to the host function when the class metaobject is not
;;; known to the translator.

(defgeneric tclos:class-default-initargs (class)
  (:generic-function-class translator-generic-function))

(defgeneric tclos:class-direct-default-initargs (class)
  (:generic-function-class translator-generic-function))

(defgeneric tclos:class-direct-slots (class)
  (:generic-function-class translator-generic-function))

(defgeneric tclos:class-direct-subclasses (class)
  (:generic-function-class translator-generic-function))

(defgeneric tclos:class-direct-superclasses (class)
  (:generic-function-class translator-generic-function))

(defgeneric tclos:class-name (class)
  (:generic-function-class translator-generic-function))

(defgeneric (setf tclos:class-name) (name class)
  (:generic-function-class translator-generic-function))

(defgeneric tclos:class-precedence-list (class)
  (:generic-function-class translator-generic-function))

(defgeneric tclos:class-prototype (class)
  (:generic-function-class translator-generic-function))

(defgeneric tclos:class-slots (class)
  (:generic-function-class translator-generic-function))

(defgeneric tclos:documentation (object &optional doc-type)
  (:generic-function-class translator-generic-function))

(defgeneric (setf tclos:documentation) (value object &optional doc-type)
  (:generic-function-class translator-generic-function))

;;; Define methods on class which resolve into accesses on the corresponding
;;; class-record objects.

(macrolet ((define-class-reader (name record-reader &optional passon)
	     `(defmethod ,name ((class class))
		(with-class-record (record class ,(not passon))
		  ,(if passon
		       ;; If passon is true, then it must be a function that
		       ;; is applied to the class to perform the operation
		       ;; when no class-record is associated with the class.
		       `(if record
			    (,record-reader record)
			    (,passon class))
		       `(,record-reader record)))))
	   (define-class-readers (arglists)
	     `(progn
		,@(mapcar #'(lambda (arguments)
			      `(define-class-reader ,@arguments))
			  arglists))))

  (define-class-readers
    ((tclos:class-default-initargs class-record-default-initargs)
     (tclos:class-direct-default-initargs class-record-direct-default-initargs)
     (tclos:class-direct-slots class-record-direct-slots)
     (tclos:class-direct-subclasses class-record-direct-subclasses)
     (tclos:class-direct-superclasses class-record-direct-superclasses)
     (tclos:class-name class-record-name class-name)
     (tclos:class-precedence-list class-record-precedence-list)
     (tclos:class-prototype class-record-prototype)
     (tclos:class-slots class-record-slots)
     ))
  )

(defmethod (setf tclos:class-name) (name (class class))
  (check-type name symbol)
  (with-class-record (record class nil)
    (if (null record)
	(setf (class-name class) name)
	(setf (class-record-name record) name))))

(defun extraneous-documentation-type-error (object &optional setf)
  (cerror "Ignore second argument to ~S."
  	  "The second argument to ~S must be unsupplied when~@
           the first argument is ~S."
	  (if setf
	      '(setf tclos:documentation)
	      'tclos:documentation)
	  object))

(defmethod tclos:documentation (object &optional (doc-type nil dtp))
  (if dtp
      (documentation object doc-type)
      (documentation object)))

(defmethod (setf tclos:documentation)
        (value object &optional (doc-type nil dtp))
  (if dtp
      (setf (documentation object doc-type) value)
      (setf (documentation object) value)))

(defmethod tclos:documentation ((class class) &optional (doc-type nil dtp))
  (declare (ignore doc-type))
  (with-class-record (record class nil)
    (if (null record)
	(call-next-method)
	(progn
	  (when dtp (extraneous-documentation-type-error class))
	  (class-record-documentation record)))))

(defmethod (setf tclos:documentation)
        (value (class class) &optional (doc-type nil dtp))
  (declare (ignore doc-type))
  (with-class-record (record class nil)
    (if (null record)
	(call-next-method)
	(progn
	  (check-type value (or null string))
	  (when dtp (extraneous-documentation-type-error class t))
	  (setf (class-record-documentation record) value)))))

(macrolet ((define-lazy-reader (name slot compute)
	     `(progn
		(defmethod ,name ((record class-record))
		  (if (slot-boundp record ',slot)
		      (slot-value record ',slot)
		      (setf (slot-value record ',slot)
			    (,compute (class-record-related-class record)))))
		(pushnew ',slot *lazy-class-record-slots*))))

  (define-lazy-reader class-record-precedence-list
                      precedence-list
		      tclosx:compute-class-precedence-list)

  (define-lazy-reader class-record-slots
                      slots
		      tclosx:compute-slots)

  (define-lazy-reader class-record-default-initargs
                      default-initargs
		      compute-default-initargs)

  (define-lazy-reader class-record-prototype
                      prototype
		      allocate-instance)

  )

(defmethod class-record-static-p ((record class-record))
  (handle-cached-slot
       record
       'static
       #'(lambda (record)
	   (compute-static-class-p
	        (class-record-related-class record)))
       #'(lambda (record new-value old-value)
	   (cond ((null new-value)
		  (when old-value
		    (warn "The class ~S used to be considered static.~@
                           Some optimized slot accesses may be invalid."
			  (class-record-related-class record))))
		 ((null old-value)
		  (warn "The class ~S used to be considered modifiable.~@
                         Some slot accesses may not have been optimized."
			(class-record-related-class record)))))))

(defun ensure-reader/writer-generic-functions (record)
  ;; Defer this operation while bootstrapping the translator.
  (when (fboundp 'ensure-translator-defmethod-function)
    (dolist (slotd (class-record-direct-slots record))
      (dolist (reader (tclos:slot-definition-readers slotd))
	(ensure-translator-defmethod-function reader '(object)))
      (dolist (writer (tclos:slot-definition-writers slotd))
	(ensure-translator-defmethod-function writer '(value object))))))


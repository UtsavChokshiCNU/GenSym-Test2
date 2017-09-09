;;; -*- Mode: Lisp; Package: TCLOSI; Syntax: Common-Lisp -*-
;;;
;;; Translator slot definitions.
;;; Copyright (C) 1991 Chestnut Software, Inc.  All Rights Reserved.
;;;

(in-package "TCLOSI")

(himpl:note-rcs-revision "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/slot-definition.lisp,v $"
			 "$Revision: 1.1 $"
			 "$Date: 2006/02/28 21:59:12 $")

(defgeneric tclos:slot-definition-name (slotd)
  (:generic-function-class translator-generic-function))

(defgeneric tclos:slot-definition-initform (slotd)
  (:generic-function-class translator-generic-function))

(defgeneric tclos:slot-definition-initfunction (slotd)
  (:generic-function-class translator-generic-function))

(defgeneric tclos:slot-definition-type (slotd)
  (:generic-function-class translator-generic-function))

(defgeneric tclos:slot-definition-allocation (slotd)
  (:generic-function-class translator-generic-function))

(defgeneric tclos:slot-definition-initargs (slotd)
  (:generic-function-class translator-generic-function))

(defgeneric tclos:slot-definition-readers (slotd)
  (:generic-function-class translator-generic-function))

(defgeneric tclos:slot-definition-writers (slotd)
  (:generic-function-class translator-generic-function))

(defgeneric slot-definition-documentation (slotd)
  (:generic-function-class translator-generic-function))

(defgeneric (setf slot-definition-documentation) (value slotd)
  (:generic-function-class translator-generic-function))

(defgeneric slot-definition-class (slotd)
  (:generic-function-class translator-generic-function))

(defgeneric slot-definition-constant-initform-p (slotd)
  (:generic-function-class translator-generic-function))

(defgeneric tclosx:local-slot-definition-p (slotd)
  (:generic-function-class translator-generic-function))

(defgeneric tclosx:shared-slot-definition-p (slotd)
  (:generic-function-class translator-generic-function))

;;; The class tclos:slot-definition and other classes defined using DEFCLASS
;;; below are used in the translation time representation of slot definitions.
;;;
;;; The variables *slot-definition-slots* and other variables defined below
;;; which look like lists of slot specifications for defclass forms describe
;;; the runtime representation of slot definitions.

(defclass tclos:slot-definition ()
  ((name                :initarg :name
			:reader tclos:slot-definition-name)
   (initform            :initarg :initform
			:initform ()
			:reader tclos:slot-definition-initform)
   (initfunction        :initarg :initfunction
			:initform nil
			:reader tclos:slot-definition-initfunction)
   (constant-initform   :initarg tclos-run:constant-initform-p
			:initform nil
			:reader slot-definition-constant-initform-p)
   (slot-type           :initarg :type
			:initform t
			:reader tclos:slot-definition-type)
   (allocation          :initarg :allocation
			:initform :instance
			:reader tclos:slot-definition-allocation)
   (initargs            :initarg :initargs
			:initform ()
			:reader tclos:slot-definition-initargs)
   (readers             :initarg :readers
			:initform ()
			:reader tclos:slot-definition-readers)
   (writers             :initarg :writers
			:initform ()
			:reader tclos:slot-definition-writers)
   (doc-string          :initarg :documentation
			:initform nil
			:accessor slot-definition-documentation)
   ))

;;; We need to copy slots, since they may have been destructively
;;; modified (by adding more initargs, for example). But the same
;;; slot may (I think be in multiple class-records, so we need to preserve
;;; eq-ness, so we record the old slot to new slot mapping here.
(defvar *slot-copy* (make-hash-table :test #'eq))
  
(defgeneric copy-direct-slot (slotd)
  (:generic-function-class translator-generic-function))

(defmethod copy-direct-slot ((slotd tclos:slot-definition))
  (let ((new-slot (gethash slotd *slot-copy*)))
    (if new-slot
	new-slot
	(setf (gethash slotd *slot-copy*)
    (make-instance 'tclos:slot-definition
		   :name
		   (tclos:slot-definition-name slotd)
		   :initform
		   (tclos:slot-definition-initform slotd)
		   :initfunction
		   (tclos:slot-definition-initfunction slotd)
		   'tclos-run:constant-initform-p
		   (slot-definition-constant-initform-p slotd)
		   :type
		   (tclos:slot-definition-type slotd)
		   :allocation
		   (tclos:slot-definition-allocation slotd)
		   :initargs
		   (copy-list (tclos:slot-definition-initargs slotd))
		   :readers
		   (mapcar #'copy-reader
			   (tclos:slot-definition-readers slotd))
		   :writers
		   (mapcar #'copy-writer
			   (tclos:slot-definition-writers slotd))
		   :documentation
		   (slot-definition-documentation slotd))))))

;;; For now
(defun copy-reader (reader) reader)

(defun copy-writer (writer) writer)
  
(defparameter *slot-definition-slots*
  '((tclos-run:name
         ;; Other information inherited from METAOBJECT.
         :reader tclos:slot-definition-name
         )
    (tclos-run:initform
         :initarg :initform
         :initform nil
	 :reader tclos:slot-definition-initform
	 )
    (tclos-run:initfunction
         :initarg :initfunction
	 :initform nil
         :reader tclos:slot-definition-initfunction
	 )
    (tclos-run:constant-initform-p
         :initarg tclos-run:constant-initform-p
	 :initform nil
	 )
    (tclos-run:slot-type
         :initarg :type
	 :initform t
	 :reader tclos:slot-definition-type
	 )
    (tclos-run:allocation
         :initarg :allocation
	 :initform :instance
         :initfunction tclos-run:find-instance-keyword
         tclos-run:constant-initform-p t
	 :reader tclos:slot-definition-allocation
	 )
    (tclos-run:initargs
         :initarg :initargs
	 :initform ()
	 :reader tclos:slot-definition-initargs
	 )
    (tclos-run:readers
         :initarg :readers
	 :initform ()
	 :reader tclos:slot-definition-readers
	 )
    (tclos-run:writers
         :initarg :writers
	 :initform ()
	 :reader tclos:slot-definition-writers
	 )
    ))

(defparameter *slot-definition-readers*
  '((tclos-run:name tclos:slot-definition-name)
    (tclos-run:initform tclos:slot-definition-initform)
    (tclos-run:initfunction tclos:slot-definition-initfunction)
    (tclos-run:constant-initform-p slot-definition-constant-initform-p)
    (tclos-run:slot-type tclos:slot-definition-type)
    (tclos-run:allocation tclos:slot-definition-allocation)
    (tclos-run:initargs tclos:slot-definition-initargs)
    (tclos-run:readers tclos:slot-definition-readers)
    (tclos-run:writers tclos:slot-definition-writers)
    ))

(define-internal-slot tclos-run:constant-initform-p
    :reader "SLOT_DEFINITION_CONSTANT_INITFORM_P"
    :boundp "SLOT_DEFINITION_CONSTANT_INITFORM_P_BOUNDP"
    :writer "SET_SLOT_DEFINITION_CONSTANT_INITFORM_P")

(defclass tclosx:effective-slot-definition (tclos:slot-definition)
  ((slot-class          :initarg :class
			:reader slot-definition-class)
   ;; These slots are used to cache the results of calls to
   ;; elide-access-method-p, since a full-blown call is pretty expensive.
   (static-read)
   (static-write)
   ))

(defparameter *effective-slot-definition-slots*
  '((tclos-run:location
        :accessor tclos-run:slot-definition-location
        )
    ))

(defclass tclosx:direct-slot-definition (tclos:slot-definition) ())

(defclass tclos:standard-slot-definition (tclos:slot-definition) ())

(defclass tclosx:standard-direct-slot-definition
          (tclos:standard-slot-definition tclosx:direct-slot-definition)
    ()
  )

(defclass tclosx:standard-effective-slot-definition
          (tclos:standard-slot-definition tclosx:effective-slot-definition)
    ()
  )

(defclass tclosx:standard-effective-local-slot-definition
          (tclosx:standard-effective-slot-definition)
    ()
  )

(defclass tclosx:standard-effective-shared-slot-definition
          (tclosx:standard-effective-slot-definition)
    ()
  )


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Methods on slot definitions
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defmethod print-object ((slotd tclos:slot-definition) stream)
  (print-unreadable-object (slotd stream :type t :identity t)
    (prin1 (tclos:slot-definition-name slotd) stream)))

(defmethod reinitialize-instance
      ((slotd tclos:slot-definition) &rest initargs)
  (declare (ignore initargs))
  (error "Cannot reinitialize ~S -- it is immutable." slotd))

(defmethod tclos:documentation
        ((slotd tclos:slot-definition) &optional (doc-type nil dtp))
  (declare (ignore doc-type))
  (when dtp (extraneous-documentation-type-error slotd))
  (slot-definition-documentation slotd))

(defmethod (setf tclos:documentation)
        (value (slotd tclos:slot-definition) &optional (doc-type nil dtp))
  (declare (ignore doc-type))
  (when dtp (extraneous-documentation-type-error slotd t))
  (check-type value (or null string))
  (setf (slot-definition-documentation slotd) value))

(defmacro instance-slot-p (slotd)
  `(tclosx:local-slot-definition-p ,slotd))

(defmacro class-slot-p (slotd)
  `(tclosx:shared-slot-definition-p ,slotd))

(defmethod tclosx:local-slot-definition-p
    ((slotd tclosx:standard-effective-local-slot-definition))
  t)

(defmethod tclosx:local-slot-definition-p
    ((slotd tclosx:standard-effective-shared-slot-definition))
  nil)

(defmethod tclosx:local-slot-definition-p
    ((slotd tclosx:standard-effective-slot-definition))
  (eq (tclos:slot-definition-allocation slotd) :instance))

(defmethod tclosx:local-slot-definition-p
    ((slotd tclosx:effective-slot-definition))
  nil)

(defmethod tclosx:shared-slot-definition-p
    ((slotd tclosx:standard-effective-shared-slot-definition))
  t)

(defmethod tclosx:shared-slot-definition-p
    ((slotd tclosx:standard-effective-local-slot-definition))
  nil)

(defmethod tclosx:shared-slot-definition-p
    ((slotd tclosx:standard-effective-slot-definition))
  (eq (tclos:slot-definition-allocation slotd) :class))

(defmethod tclosx:shared-slot-definition-p
    ((slotd tclosx:effective-slot-definition))
  nil)

(defun bootstrap-slotd-info (slotd)
  (labels ((coerce-to-safe-form (value)
	     (typecase value
	       ((or symbol fixnum character) `',value)
	       (cons `(list ,@(mapcar #'coerce-to-safe-form value)))
	       (t (error "Can't handle ~S in bootstrap slot info." value)))))
    `(list ,@(mapcan #'(lambda (pair)
			 (list (coerce-to-safe-form (car pair))
			       (coerce-to-safe-form
				    (funcall (cadr pair) slotd))))
	             *slot-definition-readers*))))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Slot index constants
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defindex global-slot-index (name &optional env)
  (declare (ignore env))
  (check-type name symbol)
  (multiple-value-bind (string case)
      (string-canonicalize-case (string-trim-stars name))
    (let ((*package* (or (symbol-package name) *package*)))
      (string->c-name string t
		      :case case
		      :prefix "S"
		      :symbol name))))

(defun create-global-slot-index (name &optional c-name env)
  (create-global-index 'global-slot-index name c-name env))

(defun collect-slot-index-constants (&optional env)
  (let ((constants nil))
    (map-global-index-constants
         #'(lambda (index constant)
	     (declare (ignore index))
	     (push constant constants))
	 'global-slot-index
	 env)
    constants))

(in-package "TIMPL")

(define-usage :slot-name (name &key index-name)
  (tclosi:create-global-slot-index name index-name))

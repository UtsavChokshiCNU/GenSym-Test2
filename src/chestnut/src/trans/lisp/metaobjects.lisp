;;; -*- Mode: Lisp; Package: TCLOSI; Syntax: Common-Lisp -*-
;;;
;;; Copyright (C) 1991 Chestnut Software, Inc.  All Rights Reserved.
;;;

(in-package "TCLOSI")

(himpl:note-rcs-revision "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/metaobjects.lisp,v $"
			 "$Revision: 1.1 $"
			 "$Date: 2006/02/28 21:59:09 $")

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Generic-function metaobjects
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;; The class generic-function-record is used in the translation time
;;; representation of generic functions.  Each generic function in the
;;; translator's has an associated generic-function-record object that actually
;;; contains the translator's information about the generic function.
;;;
;;; Some of the following translation time generic functions correspond to
;;; accessor functions on generic functions that are part of the MOP.
;;;
;;; *** Currently the translator does not create generic function metaobjects
;;; *** at translation time.  This is different from the handling of class
;;; *** metaobjects, and I'm not really sure this is right.  At one time I was
;;; *** trying to do so, but ran into problems because it requires that the
;;; *** generic function classes be fully defined at translation time before
;;; *** they can be used.  I now think that the problems I ran into were really
;;; *** problems with the eval-when processing by the translator, and that
;;; *** translation time generic function metaobjects should be reintroduced.
;;; *** This would certainly be more consistant with the MOP, and would allow
;;; *** various useful forms of specialization by users.

(defgeneric generic-function-record-name (record)
  (:generic-function-class translator-generic-function))

(defgeneric generic-function-record-lambda-list (record)
  (:generic-function-class translator-generic-function))

(defgeneric generic-function-record-encoded-lambda-list (record)
  (:generic-function-class translator-generic-function))

(defgeneric generic-function-record-argument-precedence-order (record)
  (:generic-function-class translator-generic-function))

(defgeneric generic-function-record-method-class (record)
  (:generic-function-class translator-generic-function))

(defgeneric generic-function-record-declarations (record)
  (:generic-function-class translator-generic-function))

(defgeneric generic-function-record-documentation (record)
  (:generic-function-class translator-generic-function))

(defgeneric (setf generic-function-record-documentation) (value record)
  (:generic-function-class translator-generic-function))

(defgeneric generic-function-record-function-class (record)
  (:generic-function-class translator-generic-function))

(defgeneric generic-function-record-method-combination-type (record)
  (:generic-function-class translator-generic-function))

(defgeneric generic-function-record-method-combination-options (record)
  (:generic-function-class translator-generic-function))

(defgeneric generic-function-record-critical-methods (record)
  (:generic-function-class translator-generic-function))

(defgeneric generic-function-record-redefinition-record (record)
  (:generic-function-class translator-generic-function))

(defclass generic-function-record ()
  ((name                   :initarg :name
			   :initform nil
			   :reader generic-function-record-name
			   )
   (lambda-list            :initarg :lambda-list
			   :reader generic-function-record-lambda-list
			   )
   (encoded-lambda-list    :reader generic-function-record-encoded-lambda-list
			   )
   (method-class           :initarg :method-class
			   :reader generic-function-record-method-class
			   :initform (translator-find-class 'standard-method)
			   )
   (argument-precedence-order
        :initarg :argument-precedence-order
	:initform nil
	:type list
	:reader generic-function-record-argument-precedence-order
	)
   (argument-precedence-map
        :type simple-vector
	)
   (method-combination-type
        :initform 'standard
        :initarg :method-combination-type
	:reader generic-function-record-method-combination-type
	)
   (method-combination-options
        :initform nil
        :initarg :method-combination-options
	:reader generic-function-record-method-combination-options
	)
   (declarations           :initarg :declare
			   :initform ()
			   :reader generic-function-record-declarations
			   )
   (doc-string             :initarg :documentation
			   :initform nil
			   :accessor generic-function-record-documentation
			   :type (or null string)
			   )
   (function-class         :initarg :generic-function-class
			   :reader generic-function-record-function-class
			   )
   ;; This is primarily for kernel generic functions.
   (critical-methods       :initarg :critical-methods
			   :initform nil
			   :type list
			   :reader generic-function-record-critical-methods)
   (redefinition-record
        :accessor generic-function-record-redefinition-record
	:initarg :redefinition-record
	:initform (compute-redefinition-record)
	)
   ))

(defun copy-generic-function-record (old-record)
  ;; bind *current-translated-file* so that the redefinition record
  ;; will be initialized properly. Note that this assumes that the only
  ;; environment
  (make-instance 'generic-function-record
		 :name
		 (generic-function-record-name old-record)
		 :lambda-list
		 (copy-list (generic-function-record-lambda-list old-record))
		 ;; we can rely on the :after method on shared-initialize
		 ;; to initialize the encoded lambda list and the
		 ;; argument precedence map
		 :method-class
		 (generic-function-record-method-class old-record)
		 :argument-precedence-order
		 (copy-list
		  (generic-function-record-argument-precedence-order
		   old-record))
		 :method-combination-type
		 (generic-function-record-method-combination-type old-record)
		 :method-combination-options
		 (copy-list
		  (generic-function-record-method-combination-options
		  old-record))
		 :declare
		 (copy-list (generic-function-record-declarations old-record))
		 :documentation
		 (generic-function-record-documentation old-record)
		 :generic-function-class
		 (generic-function-record-function-class old-record)
		 ;; This is primarily for kernel generic functions.
		 :critical-methods
		 (mapcar #'copy-method
		  (generic-function-record-critical-methods old-record))
                 :redefinition-record
		 (timpl::copy-redefinition-record
		  (generic-function-record-redefinition-record old-record))
		 ))

;;; For now

(defun copy-method (method) method)

;;; The variable *generic-functions-slots* describes the runtime representation
;;; of generic functions.

(defparameter *generic-function-slots*
  '((tclos-run:name
         ;; Other information inherited from METAOBJECT.
         :reader tclos:generic-function-name
         )
    (tclos-run:lambda-list
         :initarg :lambda-list
         :reader tclos:generic-function-lambda-list
         )
    ;; The value is a cons with the following format:
    ;; cdr -- a list of explicitly mentioned named parameters.
    ;; car -- a fixnum that encodes the following information
    ;;  1. The number of required arguments
    ;;  2. The number of positional arguments
    ;;  3. Are non-positional arguments permitted
    ;;  4. Was &key specified (ie. must have even number of non-positionals)
    ;;  5. If &key was specified, was &allow-other-keys also specified
    ;; See encode-lambda-list for the actual encoding.
    (tclos-run:encoded-lambda-list
         :type cons
         )
    (tclos-run:initial-methods
         :initarg :initial-methods
         :initform ()
         :reader tclos:generic-function-initial-methods
         :writer tclos-run:set-generic-function-initial-methods
         )
    (tclos-run:methods
         :initform ()
         :reader tclos:generic-function-methods
         :writer tclos-run:set-generic-function-methods
         )
    (tclos-run:method-class
         :initarg :method-class
	 :initform (tcl:find-class 'standard-method)
         :initfunction tclos-run:find-standard-method-class
         :reader tclos:generic-function-method-class
         )
    (tclos-run:argument-precedence-order
         :initarg :argument-precedence-order
         :initform nil
	 :reader tclos:generic-function-argument-precedence-order
	 )
    ;; A vector of indices into the required arguments, ordered by the
    ;; precedence order of the indexed arguments.
    (tclos-run:argument-precedence-map
         :type simple-vector
	 )
    (tclos-run:method-combination
         :initarg :method-combination
         :initform (tclosx:compute-method-combination 'standard nil)
         :initfunction tclos-run:find-standard-method-combination
         :reader tclos:generic-function-method-combination
         :type method-combination
         )
    (tclos-run:declarations
         :initarg :declare
         :initform ()
         :reader tclos:generic-function-declarations
         :type list
         )
    ;; Alist of critical method specializers and associated effective methods.
    (tclos-run:critical-methods
	  :initform nil
	  :type list
	  )
    ;; If not NIL, then this is a simple vector with an entry for each required
    ;; argument position.  The elements of the vector are alists whose keys are
    ;; objects for which there are methods on the function which are eql
    ;; specialized on the object when at the argument position corresponding to
    ;; the vector element.  The values in the alist entries are a list of the
    ;; eql specialized methods.  This slot is maintained by add-method and
    ;; remove-method. 
    (tclos-run:eql-specialized-methods
          :initform nil
	  )
    ;; A mapping from lists of applicable methods to the corresponding
    ;; effective method.  This is used to find an existing effective method for
    ;; a particulare set of applicable methods so that it can be reused rather
    ;; than consing up a new one.  This slot is maintained by
    ;; compute-effective-method.
    (tclos-run:effective-methods
          :initform nil
	  )
    ;; A bit vector whose positions correspond to the required argument
    ;; positions for the function.  If a bit is one then there are methods
    ;; specialized on that argument position, with zero indicating no such
    ;; methods.  This slot is initialized by shared-initialize and maintained
    ;; by add-method and remove-method.
    (tclos-run:specialized-positions
          :type simple-bit-vector
          )
    ))

(define-internal-slot tclos-run:encoded-lambda-list
    :reader "ENCODED_LAMBDA_LIST"
    :boundp "ENCODED_LAMBDA_LIST_BOUNDP"
    :writer "SET_ENCODED_LAMBDA_LIST")

(define-internal-slot tclos-run:initial-methods
    :reader "GENERIC_FUNCTION_INITIAL_METHODS"
    :boundp "GENERIC_FUNCTION_INITIAL_METHODS_BOUNDP"
    :writer "SET_GENERIC_FUNCTION_INITIAL_METHODS")

(define-internal-slot tclos-run:methods
    :reader "GENERIC_FUNCTION_METHODS"
    :boundp "GENERIC_FUNCTION_METHODS_BOUNDP"
    :writer "SET_GENERIC_FUNCTION_METHODS")

(define-internal-slot tclos-run:argument-precedence-map
    :reader "GENERIC_FUNCTION_ARGUMENT_PRECEDENCE_MAP"
    :boundp "GENERIC_FUNCTION_ARGUMENT_PRECEDENCE_MAP_BOUNDP"
    :writer "SET_GENERIC_FUNCTION_ARGUMENT_PRECEDENCE_MAP")

(define-internal-slot tclos-run:critical-methods
    :reader "GENERIC_FUNCTION_CRITICAL_METHODS"
    :boundp "GENERIC_FUNCTION_CRITICAL_METHODS_BOUNDP"
    :writer "SET_GENERIC_FUNCTION_CRITICAL_METHODS")

(define-internal-slot tclos-run:eql-specialized-methods
    :reader "GENERIC_FUNCTION_EQL_SPECIALIZED_METHODS"
    :boundp "GENERIC_FUNCTION_EQL_SPECIALIZED_METHODS_BOUNDP"
    :writer "SET_GENERIC_FUNCTION_EQL_SPECIALIZED_METHODS")

(define-internal-slot tclos-run:effective-methods
    :reader "GENERIC_FUNCTION_EFFECTIVE_METHODS"
    :boundp "GENERIC_FUNCTION_EFFECTIVE_METHODS_BOUNDP"
    :writer "SET_GENERIC_FUNCTION_EFFECTIVE_METHODS")

(define-internal-slot tclos-run:specialized-positions
    :reader "GENERIC_FUNCTION_SPECIALIZED_POSITIONS"
    :boundp "GENERIC_FUNCTION_SPECIALIZED_POSITIONS_BOUNDP"
    :writer "SET_GENERIC_FUNCTION_SPECIALIZED_POSITIONS")

(defparameter *kernel-generic-function-slots*
  '((tclos-run:critical-methods
          :initarg tclos-run:critical-methods
	  ;; Other info inherited from generic-function.
	  )
    ))

;;; Some implementations do not yet have a native generic-function class, so
;;; we specify errorp (not *use-remote-classes*) in the call to find-class.
;;; If no host class is found and *use-remote-classes* is true, then the
;;; call to ensure-translator-class will allocate a remote class for it.

(let ((env *default-global-environment*)
      ;; Permit function to be a supertype of generic-function, even if
      ;; function is a built-in.  Also permit metaclass to be specified as
      ;; funcallable-standard-class, even if something different in host.
      (*building-initial-class-hierarchy* t))
  (setf (translator-find-class 'generic-function nil env)
	(find-class 'generic-function (not *use-remote-classes*)))
  (let ((slots (mapcar #'(lambda (slot)
			   (early-parse-slot slot env))
		       *generic-function-slots*)))
    (ensure-translator-class 'generic-function
			     :metaclass 'tclos:funcallable-standard-class
			     :direct-superclasses
			         '(function tclos-run:metaobject)
			     :direct-slots slots
			     :environment env))

  (setf (translator-find-class 'standard-generic-function nil env)
	(find-class 'standard-generic-function))
  (ensure-translator-class 'standard-generic-function
			   :metaclass 'tclos:funcallable-standard-class
			   :direct-superclasses '(generic-function)
			   :direct-slots ()
			   :environment env)
  (note-bootstrap-class 'standard-generic-function)

  (let ((slots (mapcar #'(lambda (slot)
			   (early-parse-slot slot env))
		       *kernel-generic-function-slots*)))
    (ensure-translator-class 'tclos-run:kernel-generic-function
			     :metaclass 'tclos:funcallable-standard-class
			     :direct-superclasses '(standard-generic-function)
			     :direct-slots slots
			     :environment env)
    (note-bootstrap-class 'tclos-run:kernel-generic-function))
  )

(define-translator-class tclos-run:object-creation-function
        (tclos-run:kernel-generic-function)
    ()
  (:metaclass tclos:funcallable-standard-class))

(note-bootstrap-class 'tclos-run:object-creation-function)

(define-translator-class tclos-run:object-reinitialization-function
        (tclos-run:kernel-generic-function)
    ()
  (:metaclass tclos:funcallable-standard-class))

(note-bootstrap-class 'tclos-run:object-reinitialization-function)

(define-translator-class tclos-run:object-change-class-function
        (tclos-run:kernel-generic-function)
    ()
  (:metaclass tclos:funcallable-standard-class))

(note-bootstrap-class 'tclos-run:object-change-class-function)

(define-translator-class tclos-run:object-initialization-function
        (tclos-run:object-creation-function
	 tclos-run:object-reinitialization-function
	 tclos-run:object-change-class-function
	 )
    ()
  (:metaclass tclos:funcallable-standard-class))

(note-bootstrap-class 'tclos-run:object-initialization-function)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Mapping from generic function names to the associated record objects
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;; As with the class record lookup mechanism, this only works because there is
;;; exactly one translator environment, with the property lookup accessor
;;; (generic-function-record) defaulting its environment appropriately.

(define-translator-property generic-function-record
  #'copy-generic-function-record)


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Methods on generic-function-record
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defmethod print-object ((record generic-function-record) stream)
  (print-unreadable-object (record stream :type t :identity t)
    (if (not (slot-boundp record 'name))
	(write-string "<unnamed>" stream)
	(let ((name (generic-function-record-name record)))
	  (if (null name)
	      (write-string "Anonymous" stream)
	      (prin1 name stream))))))

;;; Validate initargs before doing initialization.

(defmethod initialize-instance :before
        ((record generic-function-record) &rest initargs)
  ;; Might not be supported.
  ;; (declare (dynamic-extent initargs))
  (apply #'validate-generic-function-record-initargs record nil initargs))

(defmethod reinitialize-instance :before
        ((record generic-function-record) &rest initargs)
  ;; Might not be supported.
  ;; (declare (dynamic-extent initargs))
  (apply #'validate-generic-function-record-initargs record t initargs)
  (update-redefinition-record
       (generic-function-record-redefinition-record record)))

;;; *** This needs to be fixed.
(defun validate-generic-function-record-initargs (&rest args)
  (declare (ignore args)))

(defmethod shared-initialize :after
        ((record generic-function-record) slots
	 &key ((argument-precedence-order apo) nil apop))
  (declare (ignore slots))
  (let ((lambda-list (generic-function-record-lambda-list record)))
    (setf (slot-value record 'encoded-lambda-list)
	  (encode-lambda-list lambda-list))
    (cond (apop
	   (let ((map (compute-argument-precedence-map lambda-list apo))
		 (old-map (when (slot-boundp record 'argument-precedence-map)
			    (slot-value record 'argument-precedence-map))))
	     (setf (slot-value record 'argument-precedence-order) apo)
	     (unless (or (null old-map)
			 (equal-argument-precedence-maps map old-map))
	       (warn "Changing the argument precedence order for ~S."
		     (generic-function-record-name record)))
	     (setf (slot-value record 'argument-precedence-map) map)))
	  ((not (slot-boundp record 'argument-precedence-order))
	   (let* ((order (collect-required-parms lambda-list))
		  (map (compute-argument-precedence-map lambda-list order)))
	     (setf (slot-value record 'argument-precedence-order) order)
	     (setf (slot-value record 'argument-precedence-map) map)))
	  ))
  )

(defun collect-required-parms (lambda-list)
  (let ((req nil))
    (dolist (parm lambda-list)
      (cond ((member parm lambda-list-keywords :test #'eq) (return))
	    ((symbolp parm) (push parm req))
	    (t
	     (error "Invalid lambda-list: ~S." lambda-list))))
    (nreverse req)))

(defun equal-argument-precedence-maps (map1 map2)
  (equalp map1 map2))

(defun compute-argument-precedence-map (lambda-list apo)
  (let* ((req (collect-required-parms lambda-list))
	 (map (make-array (length req) :initial-element nil))
	 (index 0))
    (dolist (parm apo)
      (setf (svref map index) (position parm req))
      (incf index))
    (if (position nil map)
	(error "Mismatch between lambda-list and argument-precedence-order:~
                ~%  Lambda-list: ~S~%Precedence order: ~S."
	       lambda-list apo)
	map)))

(defmethod tclos:documentation
        ((record generic-function-record) &optional (doc-type nil dtp))
  (declare (ignore doc-type))
  (when dtp (extraneous-documentation-type-error record))
  (generic-function-record-documentation record))

(defmethod (setf tclos:documentation)
        (value (record generic-function-record) &optional (doc-type nil dtp))
  (declare (ignore doc-type))
  (check-type value (or null string))
  (when dtp (extraneous-documentation-type-error record t))
  (setf (generic-function-record-documentation record) value))

;;; Helper function for translation time.
;;; At runtime this function actually gets the method-combination object.
;;; At translation time it just returns the name and options as a list to be
;;; recorded in the generic-function record.

(defun tclosx:compute-method-combination (name options)
  (check-type name symbol)
  (cons name options))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Method metaobjects
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;; Note that there are no method objects created at translation time, so there
;;; is no need for defining generic-functions and methods for them.

(defparameter *method-slots*
  '(;; Removal of this slot specification presumes that the low-level
    ;; representation of methods resembles the representation for functions,
    ;; such that the code and closure environment are in inline fields of the
    ;; instance, rather than being in the slot vector.  One implication of this
    ;; is that the reader method for tclos:method-function on the class method
    ;; simply returns the method. 
    ;;
    ;;(tclos-run:code
    ;;     :initarg :method-function
    ;;     :reader tclos:method-function
    ;;     )
    (tclos-run:generic-function
         :initarg :generic-function
	 :initform nil
         :reader tclos:method-generic-function
         :writer tclos-run:set-method-generic-function
         )
    (tclos-run:lambda-list
         :initarg :lambda-list
         :reader tclos:method-lambda-list
         )
    ;; Initialized by :after method on initialize-instance.
    (tclos-run:encoded-lambda-list)
    ;; Note that the keys in the encoding must be ordered according to the
    ;; order assumed by the method function for doing the keyword permutation
    ;; vector stuff.  If not specified by an initarg, compute one from the
    ;; keywords in the encoded-lambda-list.
    (tclos-run:keyword-parameter-map
         :initarg :keyword-parameter-map
	 :initform nil
	 )
    (tclos-run:specializers
         :initarg :specializers
         :reader tclos:method-specializers
         )
    (tclos-run:qualifiers
         :initarg :qualifiers
         :initform nil
         :reader tclos:method-qualifiers
         )
    ))

(define-internal-slot tclos-run:generic-function
    :reader "METHOD_GENERIC_FUNCTION"
    :boundp "METHOD_GENERIC_FUNCTION_BOUNDP"
    :writer "SET_METHOD_GENERIC_FUNCTION")

(define-internal-slot tclos-run:encoded-lambda-list
    :reader "ENCODED_LAMBDA_LIST"
    :boundp "ENCODED_LAMBDA_LIST_BOUNDP"
    :writer "SET_ENCODED_LAMBDA_LIST")

(define-internal-slot tclos-run:keyword-parameter-map
    :reader "METHOD_KEYWORD_PARAMETER_MAP"
    :boundp "METHOD_KEYWORD_PARAMETER_MAP_BOUNDP"
    :writer "SET_METHOD_KEYWORD_PARAMETER_MAP")

;;; Some implementations do not yet have a native method class, so we specify
;;; errorp (not *use-remote-classes*) in the call to find-class.  If no host
;;; class is found and *use-remote-classes* is true, then the call to
;;; ensure-translator-class will allocate a remote class for it.

(let ((env *default-global-environment*)
      ;; Permit specifying metaclass of method and standard-method to be
      ;; method-class, even if standard-class in host.
      (*building-initial-class-hierarchy* t))
  (unless (translator-find-class 'method nil env)
    (setf (translator-find-class 'method nil env)
	  (find-class 'method (not *use-remote-classes*)))
    (let ((slots (mapcar #'(lambda (slot)
			     (early-parse-slot slot env))
			 *method-slots*)))
      (ensure-translator-class 'method
			       :metaclass 'tclosx:method-class
			       :direct-superclasses
			          '(tclos-run:metaobject)
			       :direct-slots slots
			       :environment env))

    (setf (translator-find-class 'standard-method nil env)
	  (find-class 'standard-method))
    (ensure-translator-class 'standard-method
			     :metaclass 'tclosx:method-class
			     :direct-superclasses '(method)
			     :direct-slots ()
			     :environment env)
    (note-bootstrap-class 'standard-method)
    ))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;; Subclasses of standard-method
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defparameter *accessor-method-slots*
  '((tclos-run:slot-name
         :initarg :slot-name
	 :initform nil
	 :reader tclos:method-slot-name)))

(let* ((env *default-global-environment*)
       (slots (mapcar #'(lambda (slot)
			  (early-parse-slot slot env))
		      *accessor-method-slots*)))
  (ensure-translator-class 'tclos:standard-accessor-method
			   :metaclass 'tclosx:method-class
			   :direct-superclasses '(standard-method)
			   :direct-slots slots
			   :environment env)

  ;; These don't need to be in the let*, but we want them not to
  ;; be at toplevel, so that the compile-time side effects of the defclass
  ;; don't happen.

  (ensure-translator-class 'tclos:standard-reader-method
			   :metaclass 'tclosx:method-class
			   :direct-superclasses '(tclos:standard-accessor-method)
			   :direct-slots nil
			   :environment env)
  
;  (define-translator-class tclos:standard-reader-method
;    (tclos:standard-accessor-method)
;    ()
;    (:metaclass tclosx:method-class)
;    )

  (note-bootstrap-class 'tclos:standard-reader-method)

  (ensure-translator-class 'tclos:standard-writer-method
			   :metaclass 'tclosx:method-class
			   :direct-superclasses '(tclos:standard-accessor-method)
			   :direct-slots nil
			   :environment env)
  
;  (define-translator-class tclos:standard-writer-method
;    (tclos:standard-accessor-method)
;    ()
;    (:metaclass tclosx:method-class)
;    )

  (note-bootstrap-class 'tclos:standard-writer-method)
  )

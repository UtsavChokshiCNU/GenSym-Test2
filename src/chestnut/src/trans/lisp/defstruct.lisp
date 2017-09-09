;;; -*- Mode: Lisp; Package: TIMPL; Syntax: Common-Lisp -*-
;;;
;;; DEFSTRUCT -- definition of DEFSTRUCT macro
;;;
;;; Author : John Gilson
;;;
;;; Copyright (C) 1991, Chestnut Software, Inc. All Rights Reserved.

(in-package "TIMPL")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/defstruct.lisp,v $"
 "$Revision: 1.3 $"
 "$Date: 2007/06/25 21:32:28 $")


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Toplevel entry and parsing
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;; First the DEFSTRUCT is parsed and then the appropriate expansion is created
;;; based on whether this is a "typed" or "untyped" structure.

(define-translator-macro defstruct (name-and-options &rest slot-descriptions
						     &environment env)
  (multiple-value-bind (name conc-name constructors copier predicate
			     include parent-info included-slots print-function
			     type named initial-offset)
      (parse-defstruct-options name-and-options)
    (multiple-value-bind (documentation local-slots)
        (parse-defstruct-slot-options slot-descriptions
				      (get-typed-default-slot-value type))
      (setf named
	    (assign-slot-offsets included-slots local-slots
				 initial-offset named))
      (cond ((null type)
	     (do-untyped-defstruct
	       name conc-name constructors copier predicate include
	       parent-info print-function named initial-offset included-slots
	       local-slots documentation env))
	    ((or (eq type 'vector)
		 (and (consp type) (eq (car type) 'vector))
		 (eq type 'list)) 
	     (do-typed-defstruct
	       name conc-name constructors copier predicate include
	       parent-info print-function named included-slots local-slots
	       documentation type env))))))

;;; Define structures to cache information about the structure type. The dump
;;; phase will use this information.

(defstruct structure-info-root
  (children nil))

(defstruct (structure-info (:include structure-info-root))
  (name                            nil)
  (package                         nil)
  (include                         nil)
  (included-slots                  nil)
  (local-slots                     nil)
  (included-slot-foreign-accessors nil)
  (local-slot-foreign-accessors    nil)
  (foreign-predicate               nil)
  (primitive-predicate             nil)
  (foreign-copier                  nil)
  (primitive-copier                nil))

(defstruct (untyped-structure-info (:include structure-info))
  (foreign-name               nil)
  (foreign-supertype          nil)
  (structure-object-predicate nil)
  (depth                      nil)
  (print-function             nil))

(defstruct (typed-structure-info (:include structure-info))
  (type                          nil)
  (named-name-indices            nil)
  (named-names                   nil)
  (included-slot-foreign-setters nil)
  (local-slot-foreign-setters    nil))

(defstruct (list-structure-info (:include typed-structure-info)))

(defstruct (vector-structure-info (:include typed-structure-info)))

(defstruct slot-info
  (name                        nil)
  (keyword                     nil)
  (c-name                      nil)
  (default-init                nil)
  (type                        nil)
  (read-only                   nil)
  (offset                      nil)
  (native-foreign-accessor     nil)
  (primitive-accessor          nil)
  (native-foreign-setter       nil)
  (primitive-setter            nil))

;;; Parse the name-and-options part of the DEFSTRUCT form and return several
;;; values.

(defun parse-defstruct-options (name-and-options)
  (let* ((name           (if (consp name-and-options)
			     (first name-and-options)
			     name-and-options))
	 (options        (if (consp name-and-options)
			     (rest name-and-options)
			     nil))
	 (conc-name      (sformat "~A-" name))
	 (copier         (intern (sformat "COPY-~A" name)))
	 (predicate      (intern (sformat "~A-P" name)))
	 (predicate-p    nil)
	 (include        nil)
	 (parent-info    nil)
	 (included-slots nil)
	 (print-function nil)
	 (type           nil)
	 (named          nil)
	 (initial-offset nil)
	 (constructors   nil)
	 (default-constructor
	   (list (intern (sformat "MAKE-~A" name))))
	 ;; Indicates that the default constructor should be added to
	 ;; the options list at the end of options processing.
	 (default-constructor-too t))
    (dolist (o options)
      (when (symbolp o) (setf o (list o)))
      (case (first o)
	(:conc-name
	 (if (rest o)
	     (if (second o)
		 (setf conc-name (string (second o)))
	         (setf conc-name ""))))
	(:copier
	 (if (rest o)
	     (if (second o)
		 (setf copier (second o))
	         (setf copier nil))))
	(:predicate
	 (setq predicate-p t)
	 (if (rest o)
	     (setf predicate (second o))))
	(:include
	 (multiple-value-setq (include parent-info included-slots)
	     (parse-defstruct-include (rest o))))
	(:print-function
	 (setf print-function
	       (if (rest o)
		   `(function ,(second o))
		   :default-print-function)))
	(:type
	 (setf type (second o)))
	(:named
	 (setf named t))
	(:initial-offset
	 (setf initial-offset (second o)))
	(:constructor
	 (cond ((null (rest o))
		;;no argument, make the default.
		(push default-constructor constructors))
	       ((null (second o)))
	       ((null (cddr o))
		;; Not a BOA constructor
		(push (rest o)constructors))
	       (t ;make the named constructor
		(push (rest o) constructors)))
	 ;; Never make the default constructor if there are any
	 ;; :constructor options specified, unless
	 ;; (:constructor) is explicitly specified
	 (setq default-constructor-too nil))
	(t
	 (warn "Ignoring unknown DEFSTRUCT option ~S." o))))
    (when default-constructor-too
      (push default-constructor constructors))
    (if (and include
	     (etypecase parent-info
	       (untyped-structure-info type)
	       (list-structure-info (not (eq type 'list)))
	       (vector-structure-info
		(not (or (eq type 'vector)
			 (and (consp type)
			      (eq (first type) 'vector)))))))
	(error ":TYPE mismatch in :INCLUDEd structure."))
    (when (and type (null named) predicate)
      (when predicate-p
	(warn "Cannot have non-nil :predicate when :type is non-nil ~
	    ~%and :named is nil.  Setting predicate to nil."))
      (setq predicate nil))
    ;; if :type is not specified and :predicate is nil, then make a
    ;; predicate (whose name is an uninterned symbol) for use in defining
    ;; the type and for use by TYPEP
    (when (and (null predicate) (or (null type) named))
      ;;(setf predicate (make-symbol (sformat "~A-P" name)))
      (setf predicate (intern (sformat "~A-P internal" name))))
    (values
      name
      conc-name
      constructors
      copier
      predicate
      include
      parent-info
      included-slots
      print-function
      type
      named
      initial-offset)))

;;; Parse slot options.

(defun parse-defstruct-slot-options (slot-descriptions default-default-init)
  (let ((documentation (if (stringp (first slot-descriptions))
			   (pop slot-descriptions)
			   nil)))
    (values
      documentation
      (mapcar #'(lambda (s)
		  (parse-defstruct-slot s default-default-init))
	      slot-descriptions))))

(defun parse-defstruct-slot (description default-default-init)
  (let ((name      nil)
	(default   nil)
	(type      t)
	(read-only nil))
    (if (consp description)
	(let ((options  (cddr description)))
	  (setf name (first description)
		default (second description))
	  (loop
	    (cond ((null options)
		   (return nil))
		  ((eq (first options) :type)
		   (setf type (second options)))
		  ((eq (first options) :read-only)
		   (setf read-only (second options)))
		  (t
		   (warn "Ignoring unknown DEFSTRUCT slot option ~S."
			 (first options))))
	    (setf options (cddr options))))
        (setf name description))
    (make-slot-info :name name
		    :keyword (intern (string name) 'keyword)
		    :default-init (or default default-default-init)
		    :type type
		    :read-only read-only)))

;;; Parse :include information and merge modified slot descriptions.
;;;   * default-init for new always overrides default-init for old
;;;   * type for new must be subtype of type for old
;;;   * the slot is read-only if either new or old specifies it

(defun parse-defstruct-include (include)
  (let* ((name           (first include))
	 (parent-info    (or (defined-as-structure name)
			     (error "Cannot :INCLUDE ~S." name)))
	 (modified-slots (mapcar
			  #'(lambda (s)
			      (parse-defstruct-slot
			       s
			       (if (typed-structure-info-p parent-info)
				   (get-typed-default-slot-value
				     (typed-structure-info-type parent-info))
				   nil)))
			  (rest include)))
	 (parent-slots   (append
			   (structure-info-included-slots parent-info)
			   (structure-info-local-slots parent-info))))
    (values
      name
      parent-info
      (merge-inherited-slots modified-slots parent-slots))))

(defun merge-inherited-slots (modified-slots parent-slots)
  (let ((new-slots nil)
	(new       nil))
    (dolist (old parent-slots)
      (if (setf new
		(dolist (modified-slot modified-slots)
		  (when (or (eq (slot-info-name modified-slot)
				(slot-info-name old))
			    ;; This looks bogus to me; is this
			    ;; really what CLtL2P479 means?
			    (eq (slot-info-name modified-slot)
				(slot-info-keyword old)))
		    (return modified-slot))))
	  (progn
	    (setf modified-slots (delete new modified-slots :test #'eq))
	    (push (make-slot-info
		    :name (slot-info-name old)
		    :keyword (slot-info-keyword old)
		    :default-init (slot-info-default-init new)
		    :type (and-types (slot-info-type new)
				     (slot-info-type old))
		    :read-only (or (slot-info-read-only new)
				   (slot-info-read-only old))
		    :offset (slot-info-offset old)
		    :native-foreign-accessor
		    (slot-info-native-foreign-accessor old)
		    :primitive-accessor (slot-info-primitive-accessor old)
		    :native-foreign-setter (slot-info-native-foreign-setter
					     old)
		    :primitive-setter (slot-info-primitive-setter old))
		  new-slots))
	  (push old new-slots)))
    (if modified-slots
	(error "There are no slots ~S in the :INCLUDEd structure."
	       (mapcar #'slot-info-name modified-slots)))
    (nreverse new-slots)))

;;; Assign offsets to slots. Returns the index of the :named slot,
;;; or nil if :named was not specified.

(defun assign-slot-offsets (oldslots newslots initial-offset named)
  (let ((offset (+ (or initial-offset 0)
		   (if oldslots
		       (1+ (slot-info-offset (first (last oldslots))))
		       0))))
    (when named
      (setf named offset)
      (incf offset))
    (dolist (s newslots named)
      (setf (slot-info-offset s) offset)
      (incf offset))))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Constructor parsing
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;; Parse a constructor specification.  Return four values:
;;;   * The name of the constructor.
;;;   * A list of slot-initfunction bindings that are used for BOA
;;;     constructors. The body of one of these functions is a given slot's
;;;     default initform. These bindings are plugged into a FLET form and the
;;;     FLET is wrapped around the constructor. A call to the appropriate
;;;     thunk is placed in the constructor's lambda list to obtain a certain
;;;     slot's default value. This ensures that default inits are evaluated in
;;;     the correct lexical environment.
;;;   * The actual lambda list for the constructor function.
;;;   * A list of the initialization forms for each "slot".  (The list
;;;     includes placeholders for holes left by :initial-offset and
;;;     :named options.)

(defun parse-constructor (spec slots named-name-indices named-names env)
  (if (rest spec)
      (parse-boa-constructor
        spec slots named-name-indices named-names env)
      (parse-key-constructor
        spec slots named-name-indices named-names)))

;;; Parse a keyword constructor.  Note that the symbols that name slots
;;; are not bound directly as lambda variables; instead we bind gensyms.

(defun parse-key-constructor (spec slots named-name-indices named-names)
  (let ((inits (make-list (1+ (slot-info-offset (first (last slots))))))
	(args  nil))
    (dolist (s slots)
      (let ((var (make-symbol (symbol-name (slot-info-name s))))
	    (key (slot-info-keyword s)))
	(push `((,key ,var) ,(slot-info-default-init s)) args)
	(setf (nth (slot-info-offset s) inits) var)))
    (setf inits
	  (put-named-name-inits named-name-indices named-names inits))
    (values
      (first spec)
      nil
      `(&key ,@(nreverse args))
      inits)))

;;; Parse a BOA constructor.  Here, slot names which appear in the lambda
;;; list are bound as variables.

(defun parse-boa-constructor (spec slots named-name-indices named-names env)
  (let ((inits                   (make-list (1+ (slot-info-offset
						 (first (last slots))))))
	(args                    nil)
	(leftover                (copy-list slots))
	(initfunction-bindings   nil)
	(encountered-lambda-vars nil))
    (flet ((check-slot (name)
	     (let ((slot  (find name leftover :key #'slot-info-name
				:test #'eq)))
	       (if slot
		   (progn
		     (setf leftover (delete slot leftover)
			   (nth (slot-info-offset slot) inits) name)
		     (slot-info-default-init slot))
		   nil)))
	   (encountered-lambda-var (name)
	     (push name encountered-lambda-vars))
	   (check-init (init slot-name)
	     (setf init (apply-macros init env))
	     (if (or (translator-constantp init env)
		     (and (symbolp init)
			  (not (member init encountered-lambda-vars
				       :test #'eq))))
		 init
		 (let ((initfunction-name
			(make-symbol
			 (sformat "~A-INITFUNCTION" slot-name))))
		   (push `(,initfunction-name () ,init)
			 initfunction-bindings)
		   `(,initfunction-name)))))
      (parse-lambda-list
       (second spec)
       :required #'(lambda (name)
		     (push name args)
		     (check-slot name)
		     (encountered-lambda-var name))
       :optional #'(lambda (name default defaultp svar svar-p)
		     (pushnew '&optional args)
		     (let ((default-default (check-slot name)))
		       (cond ((null defaultp)
			      (push
			       `(,name ,(check-init default-default name))
			       args))
			     ((null svar-p)
			      (push `(,name ,default) args))
			     (t
			      (check-slot svar)
			      (push `(,name ,default ,svar) args))))
		     (encountered-lambda-var name))
       :rest #'(lambda (name)
		 (push '&rest args)
		 (push name args)
		 (check-slot name)
		 (encountered-lambda-var name))
       :keyp #'(lambda ()
		 (push '&key args))
       :key #'(lambda  (name keyword default defaultp svar svar-p)
		(let ((default-default (check-slot name)))
		  (cond ((null defaultp)
			 (push `((,keyword ,name)
				 ,(check-init default-default name))
			       args))
			((null svar-p)
			 (push `((,keyword ,name) ,default) args))
			(t
			 (check-slot svar)
			 (push `((,keyword ,name) ,name ,default ,svar)
			       args))))
		(encountered-lambda-var name))
       :allow-other-keys-p #'(lambda  ()
			       (push '&allow-other-keys args))
       :aux #'(lambda (name default defaultp)
		(pushnew '&aux args)
		(check-slot name)
		(encountered-lambda-var name)
		(if defaultp
		    (push `(,name ,default) args)
		    (push `(,name nil) args))))
      (dolist (s leftover)
	(setf (nth (slot-info-offset s) inits)
	      (check-init (slot-info-default-init s)
			  (slot-info-name s)))))
    (setf inits
	  (put-named-name-inits named-name-indices named-names inits))
    (values
     (first spec)
     (nreverse initfunction-bindings)
     (nreverse args)
     inits)))

(defun put-named-name-inits (named-name-indices named-names inits)
  (dolist (index named-name-indices inits)
    (setf (nth index inits) `',(pop named-names))))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Un-typed structures
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defvar untyped-structure-root-name
  (make-symbol "UNTYPED-STRUCTURE-ROOT"))

;;; Minimum size of the class precedence vector (from RTL)

(defparameter *minimum-cpv-size* 10)

(defun do-untyped-defstruct (name conc-name constructors copier predicate
				  include parent-info print-function named
				  initial-offset included-slots local-slots
				  documentation env)
  (if named
      (warn ":NAMED option not useful without :TYPE option in DEFSTRUCT ~S."
	    name))
  (if initial-offset
      (error ":INITIAL-OFFSET option may not be used without :TYPE option."))
  (unless print-function
    (setf print-function
	  (if parent-info
	      (let ((parent-print-function
		     (untyped-structure-info-print-function parent-info)))
		(if (or (eq parent-print-function :print-function)
			(eq parent-print-function :inherited-print-function))
		    :inherited-print-function
		    :default-print-function))
	      :default-print-function)))
  (let* ((slots (append included-slots local-slots))
	 (included-slot-accessors
	  (make-accessor-symbols conc-name included-slots))
	 (local-slot-accessors (make-accessor-symbols conc-name local-slots))
	 (accessors (append included-slot-accessors local-slot-accessors))
	 (included-slot-foreign-accessors
	  (make-foreign-accessor-symbols included-slot-accessors))
	 (local-slot-foreign-accessors
	  (make-foreign-accessor-symbols local-slot-accessors))
	 (foreign-accessors
	  (append included-slot-foreign-accessors
		  local-slot-foreign-accessors))
	 (foreign-setters (make-foreign-setter-symbols accessors))
	 (foreign-predicate (lisp-fn-symbol->foreign-fn-symbol predicate))
	 (depth (untyped-structure-depth parent-info))
	 (primitive-predicate (get-untyped-primitive-predicate depth))
	 (structure-object-predicate 'trun:%structure-object-p)
	 (foreign-copier (if copier
			     (lisp-fn-symbol->foreign-fn-symbol copier)))
	 (primitive-copier 'copy-structure)
	 (supertype (if include include 'structure-object))
	 (foreign-name (lisp-fn-symbol->foreign-fn-symbol name))
	 (foreign-supertype (if parent-info
				(untyped-structure-info-foreign-name
				  parent-info)
			        'structure-object))
	 (constructor (dolist (constructor constructors nil)
			(unless (rest constructor)
			  (return (first constructor)))))
	 (info
	  (make-untyped-structure-info
	    :children nil
	    :name name
	    :package *package*
	    :foreign-name foreign-name
	    :include include
	    :included-slots included-slots
	    :local-slots local-slots
	    :included-slot-foreign-accessors included-slot-foreign-accessors
	    :local-slot-foreign-accessors local-slot-foreign-accessors
	    :foreign-predicate foreign-predicate
	    :primitive-predicate primitive-predicate
	    :structure-object-predicate structure-object-predicate
	    :foreign-copier foreign-copier
	    :primitive-copier primitive-copier
	    :foreign-supertype foreign-supertype
	    :depth depth
	    :print-function (if (or (eq print-function
					:default-print-function)
				    (eq print-function
					:inherited-print-function))
				print-function
			        :print-function))))
    (cache-untyped-structure-slot-info
      local-slot-foreign-accessors local-slots)
    (put-structure-info name parent-info info)
    `(progn
       (eval-when (compile)
	 (print-progress-message "Structure" ',name)
       	 ,(make-structure-type name predicate supertype)
	 (make-foreign-structure ',foreign-name)
	 (make-untyped-foreign-predicate ',foreign-predicate ',name)
	 ,@(if copier
	       `((make-untyped-foreign-copier ',foreign-copier ',name)))
	 (make-untyped-foreign-accessors ',foreign-accessors ',slots ',name)
	 ,@(make-untyped-slot-setters
	     name accessors foreign-accessors foreign-setters slots
	     (if constructors t nil))
	 #+translator-supports-clos
	 (ensure-translator-class ',name
				  :metaclass 'structure-class
				  :direct-superclasses '(,supertype)
				  :direct-slots nil
				  :documentation ,documentation)
	 )
       (eval-when (load eval)
	 ,(make-untyped-predicate predicate foreign-predicate)
	 ,@(if copier
	       `(,(make-untyped-copier copier foreign-copier name)))
	 ,@(make-untyped-accessors accessors foreign-accessors slots name)
	 (make-untyped-constructors
	   ,constructors ,slots ,foreign-setters ,name ,foreign-name ,env)
	 ,(make-structure-class
	    name supertype local-slots print-function
	    constructor documentation)
	 ',name))))

(defun untyped-structure-depth (parent-info)
  (if parent-info
      (1+ (untyped-structure-info-depth parent-info))
      2))

(defun get-untyped-primitive-predicate (depth)
  (if (< depth *minimum-cpv-size*)
      "STRUCTURE_OBJECT_TYPEP"
      "STRUCTURE_OBJECT_COMPLEX_TYPEP"))

(defun make-structure-type (structure predicate supertype)
  ;; define new structure type for translator
  `(define-type-symbol ,structure ,predicate (,supertype)))

(defun make-foreign-structure (foreign-name)
  ;; make C name and variable descriptor for a symbol that represents a
  ;; structure's C typedef
  (setf (c-name-of-global-variable foreign-name) (c-name-of-structure-type
						   foreign-name)
	(defined-as-variable foreign-name) (make-variable-descriptor
					     :constant-p t
					     :foreign-p t
					     :dump-definition-p nil)))

(defun make-untyped-foreign-predicate (foreign-predicate structure)
  ;; make C name and function descriptor for C-macro version of a structure's
  ;; predicate
  (setf (c-name-of-function-entry foreign-predicate) (c-name-of-foreign-fn
						       foreign-predicate)
	(defined-as-function foreign-predicate)
	(make-function-descriptor
	  :lambda-list         `(,(make-symbol "OBJECT"))
	  :state-changing      nil
	  :nonconsing          t
	  :nonrelocating       t
	  :state-using         nil
	  :foreign-protocol    :macro
	  :foreign-arguments   '((:object t))
	  :foreign-return-type :boolean
	  :uses-constants      `(,structure))))

(defun make-untyped-foreign-copier (foreign-copier structure)
  ;; make C name and function descriptor for C-macro version of a structure's
  ;; copier
  (setf (c-name-of-function-entry foreign-copier) (c-name-of-foreign-fn
						    foreign-copier)
	(defined-as-function foreign-copier)
	(make-function-descriptor
	  :lambda-list         `(,structure)
	  :state-changing      nil
	  :nonconsing          nil
	  :foreign-protocol    :macro
	  :foreign-arguments   '((:object nil))
	  :foreign-return-type :object)))

(defun make-untyped-foreign-accessors (foreign-accessors slots structure)
  ;; make C name and function descriptor for C-macro version of each slot
  ;; accessor
  (mapc #'(lambda (foreign-accessor slot)
	    (setf (c-name-of-function-entry foreign-accessor)
		  (c-name-of-foreign-fn foreign-accessor)
		  (defined-as-function foreign-accessor)
		  (make-function-descriptor
		   :lambda-list         `(,structure)
		   :state-changing      nil
		   :nonconsing          t
		   :nonrelocating       t
		   :foreign-protocol    (if (slot-info-read-only slot)
					    :macro
					    :accessor)
		   :foreign-arguments   '((:object nil))
		   :foreign-return-type :object)))
	foreign-accessors
	slots))

(defun make-untyped-slot-setters
    (structure accessors foreign-accessors foreign-setters slots constructors-p
	       &aux slot-setters)
  (mapc #'(lambda (accessor foreign-accessor foreign-setter slot)
	    (if (slot-info-read-only slot)
		(when constructors-p
		  (push (make-untyped-foreign-setter structure
						     foreign-accessor
						     foreign-setter slot)
			slot-setters))
	        (push
		  `(progn
		     ,(make-untyped-foreign-setter structure
						   foreign-accessor
						   foreign-setter slot)
		     (translator-defsetf ,accessor
		       :type :l-value
		       :update-fn ,foreign-setter
		       :new-value-type ,(slot-info-type slot)))
		  slot-setters)))
	accessors
	foreign-accessors
	foreign-setters
	slots)
  (nreverse slot-setters))

(defun make-untyped-foreign-setter (structure foreign-accessor foreign-setter
					      slot)
  `(setf (defined-as-function ',foreign-setter)
	 (make-function-descriptor
	   :lambda-list         '(,structure ,(make-symbol "NEW-VALUE"))
	   :return-type         ',(slot-info-type slot)
	   :foreign-protocol    :lvalue-setter
	   :nonconsing          t
	   :nonrelocating       t
	   :state-using         nil
	   :lvalue              ',foreign-accessor
	   :foreign-arguments   '((:object nil) (:object nil))
	   :foreign-return-type :object)))

(defun cache-untyped-structure-slot-info (foreign-accessors slots)
  (mapc #'(lambda (foreign-accessor slot)
	    (setf (slot-info-native-foreign-accessor slot) foreign-accessor
	          (slot-info-primitive-accessor slot)      "STRUCTURE_FIELD"))
	foreign-accessors
	slots))

(defun make-structure-class (type supertype local-slots print-function
			     constructor doc)
  `(trun:make-structure-class
     ',type
     ',supertype
     ',(mapcar #'slot-info-keyword local-slots)
     ,(make-structure-class-print-function-arg type print-function)
     ,(when constructor
	`#',constructor)
     ,doc))

(defun make-structure-class-print-function-arg (structure print-function)
  (case print-function
    (:inherited-print-function :include)
    (:default-print-function :default)
    (otherwise ; print-function is a FUNCTION form
     (if (atom (second print-function))
	 `',(second print-function)
         (let ((print-function-name
		(make-symbol (sformat "~A-PRINT-FUNCTION" structure)))
	       (lambda-list (second (second print-function)))
	       (body (cddr (second print-function))))
	   `(flet ((,print-function-name ,lambda-list
		     ,@body))
	      (function ,print-function-name)))))))

(defmacro make-translator-defun-form (&rest fn-description)
  (flet ((get-key (name)
	   (if (eq (pop fn-description) name)
	       (pop fn-description)
	       (error "~S expected" name))))
    (let* ((name-form (get-key :name))
	   (lambda-list-form (get-key :lambda-list))
	   (body-form (get-key :body))
	   (lambda-list-sym (make-symbol "LAMBDA-LIST")))
      `(let ((,lambda-list-sym ,lambda-list-form))
	 `(translator-defun ,,name-form ,,lambda-list-sym
	     ,#'(lambda ()
		  (make-function-descriptor :lambda-list ,lambda-list-sym
					    ,@fn-description))
	     ,,body-form)))))

(defun make-untyped-predicate (predicate foreign-predicate)
  ;; define Lisp-callable structure predicate
  (let ((object-param (make-symbol "OBJECT")))
    (make-translator-defun-form
     :name           predicate
     :lambda-list    `(,object-param)
     :body           `(,predicate ,object-param)
     :return-type    t
     :state-changing nil
     :nonconsing     t
     :nonrelocating  t
     :state-using    nil
     :transforms     `((,foreign-predicate t)))))

(defun make-untyped-copier (copier foreign-copier structure)
  ;; define Lisp-callable structure copier
  (make-translator-defun-form
   :name           copier
   :lambda-list    `(,structure)
   :body           `(,copier ,structure)
   :return-type    structure
   :state-changing nil
   :nonconsing     nil
   :transforms     `((,foreign-copier t))))

(defun make-untyped-accessors (accessors foreign-accessors slots structure)
  (mapcar #'(lambda (accessor foreign-accessor slot)
	      (make-translator-defun-form
	       :name           accessor
	       :lambda-list    `(,structure)
	       :body           `(,accessor ,structure)
	       :return-type    (slot-info-type slot)
	       :state-changing nil
	       :nonconsing     t
	       :nonrelocating  t
	       :transforms     `((,foreign-accessor t))))
	  accessors
	  foreign-accessors
	  slots))

(define-translator-macro make-untyped-constructors
    (constructors slots foreign-setters structure foreign-structure env)
  (let ((new-structure (make-symbol (sformat "NEW-~A" structure))))
    `(progn
       ,@(mapcar
	   #'(lambda (constructor)
	       (multiple-value-bind (cname initfunction-bindings lambda-list
					   inits)
		   (parse-constructor constructor slots nil nil env)
		 (let ((cfn
			(make-translator-defun-form
			 :name        cname
			 :lambda-list lambda-list
			 :body
			 `(let ((,new-structure (trun:%make-structure
						 ',structure
						 ,foreign-structure)))
			    ,@(mapcar
			       #'(lambda (foreign-setter init)
				   `(,foreign-setter ,new-structure ,init))
			       foreign-setters
			       inits)
			    ,new-structure)
			 :return-type structure
			 :nonconsing  nil)))
		   (if initfunction-bindings
		       `(flet ,initfunction-bindings
			  ,cfn)
		       cfn))))
	   constructors))))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    :TYPE'd structures
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defvar list-structure-root-name (make-symbol "LIST-STRUCTURE-ROOT"))

(defvar vector-structure-root-name (make-symbol "VECTOR-STRUCTURE-ROOT"))

(defvar struct-primitive-fn-info-table (make-hash-table :test #'eq))

(defstruct (struct-primitive-fn-info (:type list))
  (struct-arg-position      nil)
  (new-value-arg-position   nil)
  (user-foreign-args        nil)
  (user-foreign-return-type nil))

(defmacro get-struct-primitive-fn-info (name)
  `(gethash ,name struct-primitive-fn-info-table))

(defmacro define-struct-primitive-fn (name &rest keys)
  `(setf (get-struct-primitive-fn-info ',name)
	 (make-struct-primitive-fn-info ,@keys)))

(defun get-foreign-args-from-primitive-fn (primitive-fn)
  (let ((foreign-arguments (foreign-function-descriptor-foreign-arguments
			     (defined-as-function primitive-fn)))
	(primitive-fn-info (get-struct-primitive-fn-info primitive-fn)))
    (if foreign-arguments
	(let (position
	      (collected-foreign-arguments nil))
	  (when (setf position (struct-primitive-fn-info-struct-arg-position
				 primitive-fn-info))
	    (push (nth position foreign-arguments)
		  collected-foreign-arguments))
	  (when (setf position (struct-primitive-fn-info-new-value-arg-position
				 primitive-fn-info))
	    (push (nth position foreign-arguments)
		  collected-foreign-arguments))
	  (nreverse collected-foreign-arguments))
        (struct-primitive-fn-info-user-foreign-args primitive-fn-info))))

(defun get-foreign-return-type-from-primitive-fn (primitive-fn)
  (or (let ((descr (defined-as-function primitive-fn)))
	(and (function-descriptor-foreign-protocol descr)
	     (foreign-function-descriptor-foreign-return-type descr)))
      (struct-primitive-fn-info-user-foreign-return-type
        (get-struct-primitive-fn-info primitive-fn))))

(defun get-foreign-locals-from-primitive-fn (primitive-fn)
  (foreign-function-descriptor-uses-locals (defined-as-function primitive-fn)))

;;; Given the structure type, return a legal value to place in a slot.
;;; Use this to fill unspecified slots, so that we don't crash by trying
;;; to put nil into a slot in a typed (vector float) struct
(defun get-typed-default-slot-value (type)
  (when (consp type)
    ;; otherwise nil is fine
    (let ((element-type (translator-upgraded-array-element-type (cadr type))))
      (cond ((eq element-type t) nil)
	    ((eq element-type 'single-float) 0.0s0)
	    ((eq element-type 'character) #\Space)
	    ((eq element-type 'bit) 0)
	    ;; Must be some kind of unsigned-byte or signed-byte.
	    (t 0)))))
       
(defun get-typed-primitive-predicate (type)
  (if (eq type 'list)
      "NAMED_LISTP"
      "NAMED_SIMPLE_VECTOR_P"))

(define-struct-primitive-fn copy-list
  :user-foreign-args        '((:object nil))
  :user-foreign-return-type :object)

(define-struct-primitive-fn copy-seq
  :user-foreign-args        '((:object nil))
  :user-foreign-return-type :object)

(defun get-typed-primitive-copier (type)
  (if (eq type 'list)
      'copy-list
      'copy-seq))

(define-struct-primitive-fn trun:%svref
  :struct-arg-position 0)

(define-struct-primitive-fn trun:%set-svref
  :struct-arg-position    0
  :new-value-arg-position 2)

(define-struct-primitive-fn trun:%sbit-1
  :struct-arg-position 0)

(define-struct-primitive-fn trun:%set-sbit-1
  :struct-arg-position    0
  :new-value-arg-position 2)

(define-struct-primitive-fn trun:%schar
  :struct-arg-position 0)

(define-struct-primitive-fn trun:%set-schar
  :struct-arg-position    0
  :new-value-arg-position 2)

(define-struct-primitive-fn trun:%aref-1
  :user-foreign-args        '((:object nil))
  :user-foreign-return-type :object)

(define-struct-primitive-fn trun:%set-aref-1
  :user-foreign-args        '((:object nil) (:object nil))
  :user-foreign-return-type :object)

(define-struct-primitive-fn trun:%m-first
  :struct-arg-position 0)

(define-struct-primitive-fn trun:%set-first
  :struct-arg-position    0
  :new-value-arg-position 1)

(define-struct-primitive-fn trun:%m-second
  :struct-arg-position 0)

(define-struct-primitive-fn trun:%set-second
  :struct-arg-position    0
  :new-value-arg-position 1)

(define-struct-primitive-fn trun:%m-third
  :struct-arg-position 0)

(define-struct-primitive-fn trun:%set-third
  :struct-arg-position    0
  :new-value-arg-position 1)

(define-struct-primitive-fn trun:%m-fourth
  :struct-arg-position 0)

(define-struct-primitive-fn trun:%set-fourth
  :struct-arg-position    0
  :new-value-arg-position 1)

(define-struct-primitive-fn trun:%m-fifth
  :struct-arg-position 0)

(define-struct-primitive-fn trun:%set-fifth
  :struct-arg-position    0
  :new-value-arg-position 1)

(define-struct-primitive-fn trun:%m-sixth
  :struct-arg-position 0)

(define-struct-primitive-fn trun:%set-sixth
  :struct-arg-position    0
  :new-value-arg-position 1)

(define-struct-primitive-fn trun:%m-seventh
  :struct-arg-position 0)

(define-struct-primitive-fn trun:%set-seventh
  :struct-arg-position    0
  :new-value-arg-position 1)

(define-struct-primitive-fn trun:%m-eighth
  :struct-arg-position 0)

(define-struct-primitive-fn trun:%set-eighth
  :struct-arg-position    0
  :new-value-arg-position 1)

(define-struct-primitive-fn trun:%m-ninth
  :struct-arg-position 0)

(define-struct-primitive-fn trun:%set-ninth
  :struct-arg-position    0
  :new-value-arg-position 1)

(define-struct-primitive-fn trun:%m-tenth
  :struct-arg-position 0)

(define-struct-primitive-fn trun:%set-tenth
  :struct-arg-position    0
  :new-value-arg-position 1)

(define-struct-primitive-fn trun:%m-nth
  :struct-arg-position 1)

(define-struct-primitive-fn trun:%set-nth
  :struct-arg-position    1
  :new-value-arg-position 2)

(defun do-typed-defstruct (name conc-name constructors copier predicate
				include parent-info print-function named
				included-slots local-slots documentation
				type env)
  (declare (ignore documentation))
  (if print-function
      (error ":PRINT-FUNCTION option may not be used with :TYPE option."))
  (if (and predicate (not named))
      (error
        "A predicate can't be defined if the structure isn't \"named\"."))
  (let* ((slots (append included-slots local-slots))
	 (included-slot-accessors
	  (make-accessor-symbols conc-name included-slots))
	 (local-slot-accessors (make-accessor-symbols conc-name local-slots))
	 (accessors (append included-slot-accessors local-slot-accessors))
	 (included-slot-foreign-accessors
	  (make-foreign-accessor-symbols included-slot-accessors))
	 (local-slot-foreign-accessors
	  (make-foreign-accessor-symbols local-slot-accessors))
	 (foreign-accessors
	  (append included-slot-foreign-accessors
		  local-slot-foreign-accessors))
	 included-slot-foreign-setters
	 local-slot-foreign-setters
	 foreign-setters
	 macro-foreign-setters
	 primitive-setter
	 (foreign-predicate (if predicate
				(lisp-fn-symbol->foreign-fn-symbol predicate)))
	 (primitive-predicate (if predicate
				  (get-typed-primitive-predicate type)))
	 (foreign-copier (if copier
			     (lisp-fn-symbol->foreign-fn-symbol copier)))
	 (primitive-copier (if copier (get-typed-primitive-copier type)))
	 (named-name-indices
	  (if parent-info
	      (if named
		  (cons named (typed-structure-info-named-name-indices
			        parent-info))
		  (typed-structure-info-named-name-indices parent-info))
	      (if named
		  (list named)
		  nil)))
	 (named-names
	  (if parent-info
	      (if named
		  (cons name (typed-structure-info-named-names parent-info))
		  (typed-structure-info-named-names parent-info))
	      (if named
		  (list name)
		nil)))
	 primitive-constructor
	 primitive-constructor-only-creates-p
	 primitive-constructor-create&init-fn
	 (info
	  (macrolet ((call-structure-info-constructor (&rest args)
		       `(if (eq type 'list)
			    (make-list-structure-info ,@args)
			    (make-vector-structure-info ,@args))))
	    (call-structure-info-constructor
	      :children nil
	      :name name
	      :package *package*
	      :include include
	      :included-slots included-slots
	      :local-slots local-slots
	      :included-slot-foreign-accessors included-slot-foreign-accessors
	      :local-slot-foreign-accessors local-slot-foreign-accessors
	      :foreign-predicate foreign-predicate
	      :primitive-predicate primitive-predicate
	      :foreign-copier foreign-copier
	      :primitive-copier primitive-copier
	      :type type
	      :named-name-indices named-name-indices
	      :named-names named-names))))
    (if (eq type 'list)
	(cache-list-structure-slot-info local-slot-foreign-accessors
					local-slots)
        (setf primitive-setter
	      (cache-vector-structure-slot-info
	        type local-slot-foreign-accessors local-slots env)))
    (multiple-value-setq (primitive-constructor
			  primitive-constructor-only-creates-p
			  primitive-constructor-create&init-fn)
	(get-typed-primitive-constructor type env))
    primitive-constructor ; eliminate unused variable warning.
    (multiple-value-setq (included-slot-foreign-setters macro-foreign-setters)
	(make-typed-structure-foreign-setter-symbols
	  included-slots
	  included-slot-accessors
	  (and constructors primitive-constructor-only-creates-p)))
    (setf (typed-structure-info-included-slot-foreign-setters info)
	  macro-foreign-setters)
    (multiple-value-setq (local-slot-foreign-setters macro-foreign-setters)
	(make-typed-structure-foreign-setter-symbols
	  local-slots
	  local-slot-accessors
	  (and constructors primitive-constructor-only-creates-p)))
    (cache-typed-structure-slot-native-foreign-setters
      local-slot-foreign-setters local-slots)
    (setf (typed-structure-info-local-slot-foreign-setters info)
	  macro-foreign-setters
	  foreign-setters (append included-slot-foreign-setters
				  local-slot-foreign-setters))
    (put-structure-info name parent-info info)
    `(progn
       (eval-when (compile)
	 (print-progress-message "Structure" ',name)
	 ,@(if predicate
	       `((make-typed-foreign-predicate ',foreign-predicate ',name)))
	 ,@(if copier
	       `((make-typed-foreign-copier ',foreign-copier
					    ',primitive-copier
					    ',name)))
	 (make-typed-foreign-accessors ',foreign-accessors ',slots ',name)
	 ,@(make-typed-slot-setters name accessors foreign-accessors
				    foreign-setters slots
				    (if constructors t nil)))
       (eval-when (load eval)
	 ,@(if predicate
	       `(,(make-typed-predicate predicate foreign-predicate)))
	 ,@(if copier
	       `(,(make-typed-copier copier foreign-copier type name)))
	 ,@(make-typed-accessors accessors foreign-accessors slots name)
	 (make-typed-constructors
	   ,constructors ,type ,name ,primitive-constructor-create&init-fn
	   ,slots ,foreign-setters ,primitive-setter ,named-name-indices
	   ,named-names ,env)
	 ',name))))

(defun cache-vector-structure-slot-info (type foreign-accessors slots env)
  (multiple-value-bind (primitive-accessor primitive-setter)
      (get-vector-accessor&setter-info type env)
    (mapc #'(lambda (foreign-accessor slot)
	      (setf (slot-info-native-foreign-accessor slot) foreign-accessor
		    (slot-info-primitive-accessor slot)      primitive-accessor
		    (slot-info-primitive-setter slot)        primitive-setter))
	  foreign-accessors
	  slots)
    primitive-setter))

(defun get-vector-accessor&setter-info (type env)
  ;; This function takes a vector type and returns two values :
  ;; 1. The primitive accessor for the type.
  ;; 2. The primitive setter for the type.
  (cond ((or (eq type 'vector)
	     (eq (translator-upgraded-array-element-type (second type) env) t))
	 (values 'trun:%svref 'trun:%set-svref))
	((translator-subtypep type '(vector bit))
	 (values 'trun:%sbit-1 'trun:%set-sbit-1))
	((translator-subtypep type '(vector character))
	 (values 'trun:%schar 'trun:%set-schar))
	(t (values 'trun:%aref-1 'trun:%set-aref-1))))

(defun cache-list-structure-slot-info (foreign-accessors slots)
  (let (primitive-accessor
	primitive-setter)
    (mapc #'(lambda (foreign-accessor slot)
	      (setf (slot-info-native-foreign-accessor slot) foreign-accessor)
	      (multiple-value-setq (primitive-accessor primitive-setter)
		  (get-list-accessor&setter-info (slot-info-offset slot)))
	      (setf (slot-info-primitive-accessor slot) primitive-accessor
		    (slot-info-primitive-setter slot)   primitive-setter))
	  foreign-accessors
	  slots)))

(defun get-list-accessor&setter-info (index)
  (case index
    (0 (values 'trun:%m-first   'trun:%set-first))
    (1 (values 'trun:%m-second  'trun:%set-second))
    (2 (values 'trun:%m-third   'trun:%set-third))
    (3 (values 'trun:%m-fourth  'trun:%set-fourth))
    (4 (values 'trun:%m-fifth   'trun:%set-fifth))
    (5 (values 'trun:%m-sixth   'trun:%set-sixth))
    (6 (values 'trun:%m-seventh 'trun:%set-seventh))
    (7 (values 'trun:%m-eighth  'trun:%set-eighth))
    (8 (values 'trun:%m-ninth   'trun:%set-ninth))
    (9 (values 'trun:%m-tenth   'trun:%set-tenth))
    (t (values 'trun:%m-nth     'trun:%set-nth))))

(defun make-typed-structure-foreign-setter-symbols
    (slots accessors setter-needed-for-constructor-p)
  (let ((all-setter-symbols   nil)
	(macro-setter-symbols nil))
    (mapc #'(lambda (slot accessor)
	      (if (and (slot-info-read-only slot)
		       (not setter-needed-for-constructor-p))
		  (push nil all-setter-symbols)
	          (if (lvalue-setter-p (slot-info-primitive-setter slot))
		      (push
		        (lisp-accessor-symbol->foreign-setter-symbol
			  accessor)
			all-setter-symbols)
		      (progn
			(push
			  (lisp-accessor-symbol->foreign-setter-symbol
			    accessor)
			  all-setter-symbols)
			(push (first all-setter-symbols)
			      macro-setter-symbols)))))
	  slots
	  accessors)
    (values (nreverse all-setter-symbols) (nreverse macro-setter-symbols))))

(defun cache-typed-structure-slot-native-foreign-setters (foreign-setters
							  slots)
  (mapc #'(lambda (slot)
	    (unless (lvalue-setter-p (slot-info-primitive-setter slot))
	      (setf (slot-info-native-foreign-setter slot)
		    (pop foreign-setters))))
	slots))

(defun make-typed-foreign-predicate (foreign-predicate structure)
  ;; make C name and function descriptor for C-macro version of a
  ;; typed-structure's predicate
  (setf (c-name-of-function-entry foreign-predicate)
	(c-name-of-foreign-fn foreign-predicate)
	(defined-as-function foreign-predicate)
	(make-function-descriptor
	  :lambda-list         `(,(make-symbol "OBJECT"))
	  :state-changing      nil
	  :nonconsing          t
	  :nonrelocating       t
	  :foreign-protocol    :macro
	  :foreign-arguments   '((:object t))
	  :foreign-return-type :boolean
	  :uses-constants      `(,structure))))

(defun make-typed-foreign-copier (foreign-copier primitive-copier structure)
  ;; make C name and function descriptor for C-macro version of a
  ;; typed-structure's copier
  (setf (c-name-of-function-entry foreign-copier)
	(c-name-of-foreign-fn foreign-copier)
	(defined-as-function foreign-copier)
	(make-function-descriptor
	  :lambda-list         `(,structure)
	  :state-changing      nil
	  :nonconsing          nil
	  :foreign-protocol    :macro
	  :foreign-arguments   (get-foreign-args-from-primitive-fn
				 primitive-copier)
	  :foreign-return-type (get-foreign-return-type-from-primitive-fn
				 primitive-copier)
	  :uses-locals         (get-foreign-locals-from-primitive-fn
				 primitive-copier))))

(defun make-typed-foreign-accessors (foreign-accessors slots structure
						       &aux primitive-accessor)
  ;; make C name and function descriptor for C-macro version of each slot
  ;; accessor
  (mapc
    #'(lambda (foreign-accessor slot)
	(setf (c-name-of-function-entry foreign-accessor)
	      (c-name-of-foreign-fn foreign-accessor)
	      primitive-accessor (slot-info-primitive-accessor slot)
	      (defined-as-function foreign-accessor)
	      (make-function-descriptor
	        :lambda-list         `(,structure)
		:state-changing      nil
		:nonconsing          t
		:nonrelocating       t
		:foreign-protocol    (if (slot-info-read-only slot)
					 :macro
				         :accessor)
		:foreign-arguments   (get-foreign-args-from-primitive-fn
				       primitive-accessor)
		:foreign-return-type (get-foreign-return-type-from-primitive-fn
				       primitive-accessor)
		:uses-locals         (get-foreign-locals-from-primitive-fn
				       primitive-accessor))))
    foreign-accessors
    slots))

(defun make-typed-slot-setters (structure accessors foreign-accessors
					  foreign-setters slots
					  constructors-p
					  &aux slot-setters)
  (mapc #'(lambda (accessor foreign-accessor foreign-setter slot)
	    (if (slot-info-read-only slot)
		(when constructors-p
		  (push (make-typed-foreign-setter structure foreign-accessor
						   foreign-setter slot)
			slot-setters))
	        (push
		  `(progn
		     ,(make-typed-foreign-setter structure foreign-accessor
						 foreign-setter slot)
		     (translator-defsetf ,accessor
		       :type           ,(if (lvalue-setter-p
					     (slot-info-primitive-setter slot))
					    :l-value
					    :store-function-new-value-last)
		       :update-fn      ,foreign-setter
		       :new-value-type ,(slot-info-type slot)))
		  slot-setters)))
	accessors
	foreign-accessors
	foreign-setters
	slots)
  (nreverse slot-setters))

(defun make-typed-foreign-setter
    (structure foreign-accessor foreign-setter slot
	       &aux (primitive-setter (slot-info-primitive-setter slot)))
  (if (lvalue-setter-p primitive-setter)
      `(setf (defined-as-function ',foreign-setter)
	     (make-function-descriptor
	       :lambda-list         '(,structure ,(make-symbol "NEW-VALUE"))
	       :return-type         ',(slot-info-type slot)
	       :nonconsing          t
	       :nonrelocating       t
	       :state-using         nil
	       :foreign-protocol    :lvalue-setter
	       :lvalue              ',foreign-accessor
	       :foreign-arguments   ',(get-foreign-args-from-primitive-fn
				        primitive-setter)
	       :foreign-return-type ,(get-foreign-return-type-from-primitive-fn
				       primitive-setter)
	       :uses-locals         ,(get-foreign-locals-from-primitive-fn
				       primitive-setter)))
      `(setf (c-name-of-function-entry ',foreign-setter) (c-name-of-foreign-fn
							   ',foreign-setter)
	     (defined-as-function ',foreign-setter)
	     (make-function-descriptor
	       :lambda-list         '(,structure ,(make-symbol "NEW-VALUE"))
	       :return-type         ',(slot-info-type slot)
	       :nonconsing          t
	       :nonrelocating       t
	       :state-using         nil
	       :foreign-protocol    :macro
	       :foreign-arguments   ',(get-foreign-args-from-primitive-fn
				        primitive-setter)
	       :foreign-return-type ,(get-foreign-return-type-from-primitive-fn
				       primitive-setter)
	       :uses-locals         ,(get-foreign-locals-from-primitive-fn
				       primitive-setter)))))

(defun make-typed-predicate (predicate foreign-predicate)
  ;; define Lisp-callable structure predicate
  (let ((object-param (make-symbol "OBJECT")))
    (make-translator-defun-form
     :name           predicate
     :lambda-list    `(,object-param)
     :body           `(,predicate ,object-param)
     :return-type    t
     :state-changing nil
     :nonconsing     t
     :nonrelocating  t
     :transforms     `((,foreign-predicate t)))))

(defun make-typed-copier (copier foreign-copier type structure)
  ;; define Lisp-callable structure copier
  (make-translator-defun-form
   :name          copier
   :lambda-list   `(,structure)
   :body          `(,copier ,structure)
   :return-type    type
   :state-changing nil
   :nonconsing     nil
   :transforms     `((,foreign-copier t))))

(defun make-typed-accessors (accessors foreign-accessors slots structure)
  (mapcar #'(lambda (accessor foreign-accessor slot)
	      (make-translator-defun-form
	       :name           accessor
	       :lambda-list    `(,structure)
	       :body           `(,accessor ,structure)
	       :return-type    (slot-info-type slot)
	       :state-changing nil
	       :nonconsing     t
	       :nonrelocating  t
	       :transforms     `((,foreign-accessor t))))
	  accessors
	  foreign-accessors
	  slots))

(defun get-typed-primitive-constructor (type env)
  ;; Function returns three values :
  ;; 1. The primitive constructor for the type.
  ;; 2. If the primitive constructor does only creation (not initialization) of
  ;;    the object then T else NIL.
  ;; 3. A function to return a form that will create and initialize an object
  ;;    of the given type using the primitive constructor.
  (cond ((eq type 'list) (values 'list nil #'make-list-create&init))
	((or (eq type 'vector)
	     (eq (translator-upgraded-array-element-type (second type) env) t))
	 (values 'vector nil #'make-vector-create&init))
	(t (values 'make-array t #'make-make-array-create&init))))

(defun make-list-create&init (type foreign-setters primitive-setter
				   new-value-var inits slots)
  (declare (ignore type foreign-setters primitive-setter new-value-var slots))
  `(list ,@inits))

(defun make-vector-create&init (type foreign-setters primitive-setter
				     new-value-var inits slots)
  (declare (ignore type foreign-setters primitive-setter new-value-var slots))
  `(vector ,@inits))

(defun make-make-array-create&init (type foreign-setters primitive-setter
					 new-value-var inits slots)
  `(let ((,new-value-var (make-array ,(length inits)
				     :element-type ',(second type))))
     ,@(make-make-array-init-form
	 foreign-setters primitive-setter new-value-var inits slots 0)
     ,new-value-var))

(defun make-make-array-init-form (foreign-setters primitive-setter
						  new-value-var inits slots
						  offset)
  (cond ((null inits) nil)
	((null slots)
	 (mapcar #'(lambda (init)
		     (prog1
		       `(,primitive-setter ,new-value-var ,offset ,init)
		       (incf offset)))
		 inits))
	(t
	 (if (eql offset (slot-info-offset (first slots)))
	     (cons `(,(first foreign-setters) ,new-value-var ,(first inits))
		   (make-make-array-init-form
		     (rest foreign-setters) primitive-setter new-value-var
		     (rest inits) (rest slots) (1+ offset)))
	     (cons `(,primitive-setter ,new-value-var ,offset ,(first inits))
		   (make-make-array-init-form
		     foreign-setters primitive-setter new-value-var
		     (rest inits) slots (1+ offset)))))))

(defmacro make-typed-constructors
    (constructors type structure create&init-fn slots foreign-setters
		  primitive-setter named-name-indices named-names env)
  `(progn
     ,@(mapcar
	 #'(lambda (constructor)
	     (multiple-value-bind (cname initfunction-bindings lambda-list
					 inits)
		 (parse-constructor constructor slots named-name-indices
				    named-names env)
	       (let ((cfn
		      (make-translator-defun-form
		       :name cname
		       :lambda-list lambda-list
		       :body (funcall create&init-fn
				      type
				      foreign-setters
				      primitive-setter
				      (make-symbol
				       (sformat "NEW-~A" structure))
				      inits
				      slots)
		       :return-type type
		       :nonconsing  nil)))
		 (if initfunction-bindings
		     `(flet ,initfunction-bindings
			,cfn)
		     cfn))))
	 constructors)))

;;; helper functions

(define-toplevel-form translator-defun
  (name lambda-list function-descr-fn &body body)
  (multiple-value-bind (principal setfp)
      (get-fn-principal-name name)
    (if *toplevel-p*
	(progn
	  (redefine-translator-defun name lambda-list function-descr-fn)
	  (when *compile-time-too*
	    (eval-in-env `(defun ,name ,lambda-list ,@body) *environment*))
	  (unless *compile-time-only*
	    (translate-defun name principal setfp lambda-list body)))
        (translate-non-toplevel-defun name principal setfp lambda-list body))))

(defun redefine-translator-defun (name lambda-list function-descr-fn)
  (declare (ignore lambda-list))
  (macro->fn name)
  (generate-c-names-for-fn name)
  (let ((old (defined-as-function name))
	(new (funcall function-descr-fn)))
    (when (and old (not (argument-descriptors-equal-p old new)))
      (warn "Redefining function ~S with incompatible argument list." name))
    (setf (defined-as-function name) new)))

(defmacro translator-defun (name lambda-list function-descr-fn &body body)
  (declare (ignore function-descr-fn))
  `(defun ,name ,lambda-list
     ,@body))

(defun c-name-of-foreign-fn (name)
  (multiple-value-bind (foreign-fn-p fn-p)
      (foreign-fn-p name)
    (cond (foreign-fn-p (or (name-of-function-entry name)
			    (c-name-of-foreign-fn-aux name)))
	  (fn-p (error "The function ~S is not defined as a foreign function."
		       name))
	  (t (c-name-of-foreign-fn-aux name)))))

(defun c-name-of-foreign-fn-aux (name)
  (multiple-value-bind (name prefix)
      (symbol-for-function-name name)
    (make-upcase-c-name
      (copy-seq (string-trim-stars (subseq (string name) 1)))
      prefix
      name
      nil)))

(defun foreign-fn-p (fn)
  (let ((fn-descriptor (defined-as-function fn)))
    (if fn-descriptor
	(values (function-descriptor-foreign-protocol fn-descriptor)
		fn-descriptor)
        (values nil nil))))

(defun make-upcase-c-name (string prefix symbol globalp)
  (string->c-name (nstring-upcase string) globalp
		  :case :upcase
		  :symbol symbol
		  :prefix prefix))

(defun c-name-of-structure-type (name &aux existing-name)
  (cond ((eq name 'structure-object) "Structure_object")
        ((setf existing-name (name-of-global-variable name))
	 (if (let ((len (length existing-name)))
	       (and (<= 1 len)
		    (upper-case-p (char existing-name 0))
		    (dotimes (i (1- len) t)
		      (declare (fixnum i))
		      (let ((char (char existing-name (1+ i))))
			(unless (or (not (alpha-char-p char))
				    (lower-case-p char))
			  (return nil))))))
	     existing-name
	     (error "~S does not represent a structure." name)))
	(t
	 (setf name
	       (string->legal-c-name
	         (string-downcase (string-trim-stars (subseq (string name) 1)))
		 :downcase
		 ""))
	 (unless (zerop (length name))
	   (setf (char name 0) (char-upcase (char name 0))))
	 (string->c-name name nil :case :downcase))))

(defun lisp-accessor-symbol->foreign-setter-symbol
    (lisp-accessor-symbol &optional package
			  &aux (name (sformat "%SET-~A"
					     lisp-accessor-symbol)))
  (if package
      (intern name package)
      (make-symbol name)))

(defun make-foreign-setter-symbols (accessors &optional package)
  (mapcar #'(lambda (accessor)
	      (lisp-accessor-symbol->foreign-setter-symbol accessor package))
	  accessors))

;;; LISP-FN-SYMBOL->FOREIGN-FN-SYMBOL

;;; This needs to return the same thing when called multiple times (so that
;;; the symbol generated in prepare-file is reused in translate-file),
;;; but we can't put it in a fixed package, or symbol collisions will result,
;;; and we can't intern it in *package*, since we have no business adding
;;; this symbol to the user's package. So we make it an uninterned symbol,
;;; and use a translator property to record the mapping.

(define-translator-property corresponding-foreign-function #'identity)

(defun lisp-fn-symbol->foreign-fn-symbol (lisp-fn-symbol)
  (multiple-value-bind (foreign-symbol therep)
      (corresponding-foreign-function lisp-fn-symbol)
    (if therep
	foreign-symbol
	(setf (corresponding-foreign-function lisp-fn-symbol)
	      (make-symbol (sformat "%~A" lisp-fn-symbol))))))

(defun make-foreign-accessor-symbols (accessors)
  (mapcar #'lisp-fn-symbol->foreign-fn-symbol accessors))

(defun make-accessor-symbols (conc-name slots)
  (mapcar #'(lambda (slot)
	      (intern (sformat "~A~A" conc-name (slot-info-name slot))))
	  slots))

(defun put-structure-info (structure parent-info info)
  (redefine-structure structure)
  (add-child-to-parent structure parent-info info)
  (setf (defined-as-structure structure) info))

(defun redefine-structure (structure &aux structure-info include)
  (when (setf structure-info (defined-as-structure structure))
    (if (setf include (structure-info-include structure-info))
	(let ((included-structure-info (defined-as-structure include)))
	  (setf (structure-info-children included-structure-info)
		(delete structure
			(structure-info-children included-structure-info))))
        (let ((root-info (defined-as-structure
			   (structure-info->root-name structure-info))))
	  (when root-info
	    (setf (structure-info-root-children root-info)
		  (delete structure
			  (structure-info-root-children root-info))))))))

(defun add-child-to-parent (child parent-info info)
  (if parent-info
      (setf (structure-info-children parent-info)
	    (nconc (structure-info-children parent-info) (list child)))
      (let* ((root (structure-info->root-name info))
	     (root-info (defined-as-structure root)))
	(if root-info
	    (setf (structure-info-root-children root-info)
		  (nconc (structure-info-root-children root-info)
			 (list child)))
	    (setf (defined-as-structure root)
		  (make-structure-info-root :children (list child)))))))

(defun structure-info->root-name (structure-info)
  (etypecase structure-info
    (untyped-structure-info untyped-structure-root-name)
    (list-structure-info list-structure-root-name)
    (vector-structure-info vector-structure-root-name)))

;;; Foreign structures (from patch-4)
(defstruct (foreign-structure-info (:include structure-info))
  (foreign-name               nil)
  (structure-object-predicate nil)
  (modulus                    1)
  (remainder                  0))

(defstruct (foreign-slot-info (:include slot-info))
  (foreign-type               nil))

(define-translator-property defined-as-foreign-structure
  #'copy-foreign-structure-info)

(defconstant pointer-size #+x86-64 8 #-x86-64 4) ; also in foreign-pointer.lisp

(defvar *c-type-alignment-alist*
  '(("char" . 1) ("short" . 2) 
    ("int" . 4) ("SI_Long" . pointer-size) ("*" . pointer-size)
    ("float" . 4) ("double" . 8)))

(defun translator-foreign-type-modulus (ft)
  (let* ((ftn (translator-foreign-type-name ft))
	 (fsi (defined-as-foreign-structure ftn)))
    (if fsi
	(foreign-structure-info-modulus fsi)
	(if (consp ftn)
	    (case (car ftn)
	      (:pointer pointer-size)
	      (:array (translator-foreign-type-modulus (cadr ftn)))
	      (t 1))
	    (let* ((c-type (c-type ftn)))
	      (unless (stringp c-type)
		(error "Bad foreign-type ~S" ft))
	      (let* ((sp-pos (position #\space c-type))
		     (tail (if sp-pos
			       (subseq c-type (1+ sp-pos))
			       c-type)))
		(or (cdr (assoc tail *c-type-alignment-alist*
				:test #'string=))
		    1)))))))

(defun translator-foreign-type-remainder (ft)
  (setq ft (translator-foreign-type-name ft))
  (let ((fsi (defined-as-foreign-structure ft)))
    (if fsi
	(foreign-structure-info-remainder fsi)
	0)))

(defun parse-foreign-struct-slot (slot)
  (unless (consp slot)
    (error "def-foreign-struct: a slot description must be a list"))
  (let* ((name (car slot))
	 (type-name (getf (cdr slot) ':type))
	 (type (translator-foreign-type type-name))
	 (overlays (getf (cdr slot) ':overlays))
	 (offset (getf (cdr slot) ':offset)))
    (when (or overlays offset)
      (error "the slot options :overlays and :offset are not supported"))
    (unless (stringp (c-type type))
      (error "Bad foreign-type ~S" type-name))
    (make-foreign-slot-info :name name
			    :keyword (intern (string name) 'keyword)
			    :type (lisp-type type)
			    :foreign-type type)))

(defun make-foreign-slot-setters
    (structure accessors foreign-accessors foreign-setters slots)
  (mapcar #'(lambda (accessor foreign-accessor foreign-setter slot)
	      `(progn
		  ,(make-foreign-foreign-setter structure
						foreign-accessor
						foreign-setter slot)
		  (translator-defsetf ,accessor
				      :type :l-value
				      :update-fn ,foreign-setter
				      :new-value-type ,(slot-info-type slot))))
	  accessors
	  foreign-accessors
	  foreign-setters
	  slots))

(defun make-foreign-foreign-setter (structure foreign-accessor foreign-setter slot)
  (let* ((sft (translator-foreign-type-name (foreign-slot-info-foreign-type slot)))
	 (complex-p (or (and (consp sft) (eq (car sft) ':array))
			(defined-as-foreign-structure sft)))
	 (asft (if complex-p
		   `(:pointer ,sft)
		   sft)))
    `(setf (defined-as-function ',foreign-setter)
	   (make-function-descriptor
	    :lambda-list         '(,structure ,(make-symbol "NEW-VALUE"))
	    :return-type         ',(slot-info-type slot)
	    :foreign-protocol    :lvalue-setter
	    :nonconsing          t
	    :nonrelocating       t
	    :state-using         nil
	    :lvalue              ',foreign-accessor
	    :foreign-arguments   '(((:pointer ,structure) nil) (,asft nil))
	    :foreign-return-type ',asft))))

(defun make-foreign-structure-foreign-accessors (foreign-accessors slots structure)
  ;; make C name and function descriptor for C-macro version of each slot
  ;; accessor
  (mapc #'(lambda (foreign-accessor slot)
	    (let* ((sft (translator-foreign-type-name 
			 (foreign-slot-info-foreign-type slot)))
		   (complex-p (or (and (consp sft) (eq (car sft) ':array))
				  (defined-as-foreign-structure sft)))
		   (asft (if complex-p
			     `(:pointer ,sft)
			     sft)))
	      (setf (c-name-of-function-entry foreign-accessor)
		    (c-name-of-foreign-fn foreign-accessor)
		    (defined-as-function foreign-accessor)
		    (make-function-descriptor
		     :lambda-list         `(,structure)
		     :state-changing      nil
		     :nonconsing          t
		     :nonrelocating       t
		     :foreign-protocol    :accessor
		     :foreign-arguments   `(((:pointer ,structure) nil))
		     :foreign-return-type asft))))
	foreign-accessors
	slots))

(defun make-foreign-structure-accessors 
    (accessors foreign-accessors slots structure)
  (mapcar #'(lambda (accessor foreign-accessor slot)
	      (make-translator-defun-form
	       :name           accessor
	       :lambda-list    `(,structure)
	       :body           `(,accessor ,structure)
	       :return-type    (slot-info-type slot)
	       :state-changing nil
	       :nonconsing     t
	       :nonrelocating  t
	       :transforms     `((,foreign-accessor t))))
	  accessors
	  foreign-accessors
	  slots))

(define-translator-macro define-foreign-structure-predicate (name ft-name)
  `(defun ,name (object)
     (tx:foreign-typep object ',(translator-foreign-type ft-name))))

(define-translator-macro define-foreign-structure-constructor (name ft-name)
  `(defun ,name ()
     (make-foreign-pointer :type ',(translator-foreign-type ft-name))))







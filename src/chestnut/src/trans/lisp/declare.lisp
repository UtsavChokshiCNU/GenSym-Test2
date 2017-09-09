;;; -*- Mode: Lisp; Package: TIMPL; Syntax: Common-Lisp -*-
;;;
;;; declare.lisp -- processing for database information declarations
;;;
;;; Author :  Sandra Loosemore
;;; Date   :  06 Jul 1990
;;;
;;; Copyright (c) 1990, Chestnut Software Inc.
;;;

(in-package "TIMPL")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/declare.lisp,v $"
 "$Revision: 1.3 $"
 "$Date: 2007/06/27 15:49:24 $")

;;;
;;; The general idea of what is going on here is that there is an external
;;; data file that defines all the symbols which are present in the 
;;; run-time library and their associated usages.  The functions defined
;;; here are for manipulating the information in that file and storing it
;;; in the translator's global environment.
;;;
;;; Each entry in the database is a list whose CAR is a string that names
;;; the symbol and whose CDR is a list of usage specifiers.  Each usage
;;; specifier is in turn a list whose CAR is a keyword naming the usage
;;; and whose CDR is a list of keyword/value pairs which specify attributes
;;; of the usage; each usage can have its own set of keywords.
;;;
;;; The :symbol usage is treated rather specially.  The packages that exist
;;; at runtime have to be set up specially in advance, so as part of the
;;; initial loading of the translator the database file is scanned once
;;; to create all of the symbols and put them in the appropriate packages.
;;; The processing in this file happens at a much later point.

;;; Process a file containing a runtime symbols database.

(defun process-file (file)
  (with-open-file (stream file :direction :input)
    (let ((entry   nil))
      (loop
       (if (setq entry (read stream nil nil))
	   (if (and (consp entry)
		    (eq (car entry) 'himpl:note-rcs-revision))
	       (eval entry)
	       (process-entry (car entry) (cdr entry)))
	   (return nil))))))


;;; Define a defining macro for usage processor functions.

(defparameter *usage-processor-table* (make-hash-table :test #'eq))

(defmacro usage-processor-function (usage)
  `(gethash ,usage *usage-processor-table*))

(defmacro define-usage (usage &optional (lambda-list nil lambda-list-p)
			      &body body)
  (if lambda-list-p
      (let ((function-name
	     (intern (format nil "PROCESS-~a-USAGE" (symbol-name usage)))))
	`(progn
	   (defun ,function-name ,lambda-list ,@body)
	   (setf (usage-processor-function ',usage) ',function-name)
	   ',usage))
      `(progn
	 (setf (usage-processor-function ',usage) 'skip)
	 ',usage)))


;;; Process an entry in the runtime symbols database.
;;; First find its :symbol usage and find/create the appropriate symbol.
;;; Then look at other "interesting" usages and attach the attributes
;;; as properties of that symbol in the global environment.

(defun process-entry (symbol-name usages)
  (process-entry-internal (apply #'look-up-symbol-usage
				 symbol-name
				 (or (cdr (assoc :symbol usages))
				     (error "No :symbol usage for symbol ~s."
					    symbol-name)))
			  usages))

(defun process-entry-internal (symbol usages)
  (dolist (u usages)
    (let ((processor (usage-processor-function (car u))))
      (if processor
	  (if (eq processor 'skip)
	      nil
	      (apply processor symbol (cdr u)))
	  (warn "Ignoring unknown usage specifier ~s." u)))))

(defun himpl::process-entry-form (symbol usages)
  (mapcan #'(lambda (u &aux (uspec (car u)) processor)
	      (cond ((eq uspec :symbol)
		     `((look-up-symbol-usage
			,(symbol-name symbol)
			:required-symbol ,symbol
			,@(cdr u))))
		    ((null (setq processor (usage-processor-function uspec)))
		     (warn "Ignoring unknown usage specifier ~s." uspec)
		     nil)
		    ((eq processor 'skip)
		     nil)
		    (t
		     `((,processor ,symbol ,@(cdr u))))))
	  usages))


;;; Process the specification of the :symbol usage.  Attributes are:
;;;   :package -- the package to intern the symbol in.
;;;   :import-from -- what package to try to import the symbol from.
;;;   :symbol-name -- the name of the C variable containing the symbol object
;;;   :export -- list of packages to export from; if not supplied, default
;;;       to its home package
;;;   :exists-at-runtime -- if NIL, the symbol exists only at translation
;;;       time.  if T, the symbol is referenced by the RTL.  if :QUOTED,
;;;       the symbol exists at runtime but is not referenced by the RTL.
;;;       (This distinction is important depending on the value of the
;;;       *initial-symbols* flag.)
;;;   :magicp -- if true, the symbol is initialized and installed "magically"
;;;       at runtime.
;;; Note that we have already (supposedly) created all of the symbols and
;;; exported them, so just do find-symbol to find them.

(defun look-up-symbol-usage (name &key (package (required-keyword :package))
				  (symbol-name nil)
				  import-from
				  (export nil export-p)
				  (exists-at-runtime :quoted)
				  (magicp nil)
				  (required-symbol nil required-symbol-p))
  (declare (ignore import-from))
  (setq package (find-package package))
  (multiple-value-bind (symbol therep)
      (find-symbol name package)
    (when required-symbol-p
      (unless (eq symbol required-symbol)
	(error "~S is not the same as ~S" symbol required-symbol)))
    (cond ((not (eq therep :external))
	   (error "Broken package setup: ~A not external in package ~A."
		  name package))
	  (exists-at-runtime
	   (setf (defined-as-symbol symbol) 
		 (make-symbol-descriptor
		  :package package
		  :magicp magicp
		  :used-by-runtime (eq exists-at-runtime t)))
	   (if symbol-name
	       (setf (c-name-of-quoted-symbol symbol) symbol-name)
	       ;; Accessor updates global name mapping if necessary.
	       (c-name-of-quoted-symbol symbol))
	   (if export-p
	       (dolist (p export)
		 (install-exported-symbol symbol
					  (find-package p) magicp))
	       (install-exported-symbol symbol package magicp)))
	  (t nil))
    symbol))

#+ignore ; binghe, 2009/04/03: duplicated definition
(defun process-function-usage-common (name &key
					   (argument-types nil
							   argument-types-p)
					   (return-type nil return-type-p)
					   (unsupported nil)
					   (entry-name nil)
					   (object-name nil)
					   (lambda-list nil lambda-list-p)
					   (nonconsing nil nonconsing-p)
					   (nonrelocating nil)
					   (state-changing t)
					   (state-using t)
					   (declare nil)
					   (transforms nil)
					   (requires-return-type-declaration
					    nil)
					   (coerce-rationals-to-floats-p nil)
					   (coerce-floats-to-rationals-p nil)
					   (generic-function nil)
					   (foreign-protocol nil)
					   (operator nil)
					   (foreign-arguments nil)
					   (foreign-return-type nil)
					   (uses-locals nil)
					   (uses-constants nil)
					   (documentation nil)
					   (lvalue nil)
					   (rtl-requires-linking nil)
					   (allow-multiple-uses-of-entry-name
					    nil))
  ;(progn (print "process-function-usage-common")())
  (unless (or unsupported
	      #-translator-supports-clos
	      generic-function)
    ;; Check that the right arguments are provided.
    (when (null lambda-list-p)
      (required-keyword :lambda-list))
    (case foreign-protocol
      (:unboxing-macro
       (setq foreign-protocol :macro)
       (unless foreign-arguments
	 (setq foreign-arguments '((:object nil))))
       (unless nonconsing-p
	 (setq nonconsing t))
       (setq argument-types
	     (list (setq return-type
			 (lisp-type foreign-return-type)))))
      (:boxing-macro
       (setq foreign-protocol :macro)
       (setq foreign-return-type :object)
       (setq argument-types
	     (list (setq return-type
			 (lisp-type (caar foreign-arguments)))))
       (unless nonconsing-p
	 (setq nonconsing (translator-subtypep (car argument-types)
					       '(or fixnum character)))))
      (:foreign-arguments-function
       (unless foreign-return-type
	 (setq foreign-return-type :object))
       (when (and lambda-list (null foreign-arguments))
	 (setq foreign-arguments
	       (mapcar #'(lambda (var)
			   (declare (ignore var))
			   '(:object nil))
			lambda-list)))))
    (unless argument-types-p
      (setq argument-types
	    (if foreign-protocol
		(mapcar #'(lambda (foreign-arg)
			    (if (consp foreign-arg)
				(lisp-type (car foreign-arg))
				foreign-arg))
			foreign-arguments)
		(let ((key-p nil))
		  (mapcar #'(lambda (parameter)
			      (when (eq parameter '&key)
				(setq key-p t))
			      (if (member parameter lambda-list-keywords)
				  parameter
				  (if key-p
				      (list parameter 't)
				      't)))
			  lambda-list)))))
    (unless return-type-p
      (setq return-type
	    (if foreign-protocol
		(lisp-type foreign-return-type)
		'(values &rest t))))
    ;; Install the descriptor.
    (setf (defined-as-function name)
	  (if foreign-protocol
	      (progn
		(when generic-function
		  (function-usage-conflict :generic-function t name))
		(when object-name
		  (function-usage-conflict :object-name t name))
		(unless (translator-subtypep
			 return-type
			 (lisp-type foreign-return-type))
		  (setq return-type
			(and-types return-type
				   (lisp-type
				    foreign-return-type))))
		(unless (every #'(lambda (arg-type foreign-arg-spec)
				   (if (consp foreign-arg-spec)
				       (translator-subtypep
					arg-type
					(lisp-type
					 (car foreign-arg-spec)))
				       (eq arg-type foreign-arg-spec)))
			       argument-types foreign-arguments)
		  (setq argument-types
			(mapcar #'(lambda (arg-type foreign-arg-spec)
				    (if (consp foreign-arg-spec)
					(and-types arg-type
						   (lisp-type
						    (car foreign-arg-spec)))
					foreign-arg-spec))
				argument-types foreign-arguments)))
		(when nonconsing (setq nonrelocating t))
		(make-function-descriptor
		 :lambda-list lambda-list :defined-in-rtl-p t
		 :nonconsing nonconsing :nonrelocating nonrelocating
		 :state-changing state-changing :state-using state-using
		 :declare declare
		 :requires-return-type-declaration
		 requires-return-type-declaration
		 :argument-types argument-types :return-type return-type
		 :transforms transforms
		 :foreign-protocol foreign-protocol :operator operator
		 :foreign-return-type foreign-return-type
		 :foreign-arguments foreign-arguments
		 :uses-locals uses-locals :uses-constants uses-constants
		 :documentation documentation :lvalue lvalue
		 :rtl-requires-linking rtl-requires-linking
		 :coerce-rationals-to-floats-p coerce-rationals-to-floats-p
		 :coerce-floats-to-rationals-p coerce-floats-to-rationals-p))
	      (progn
		(when foreign-arguments
		  (function-usage-conflict :foreign-arguments nil name))
		(when foreign-return-type
		  (function-usage-conflict :foreign-return-type nil name))
		(when uses-locals
		  (function-usage-conflict :uses-locals nil name))
		(when uses-constants
		  (function-usage-conflict :uses-constants nil name))
		(when lvalue
		  (function-usage-conflict :lvalue nil name))
		(make-function-descriptor
		 :lambda-list lambda-list :defined-in-rtl-p t
		 :nonconsing nonconsing :nonrelocating nonrelocating
		 :state-changing state-changing :state-using state-using
		 :declare declare
		 :argument-types argument-types :return-type return-type
		 :transforms transforms :generic-function-p generic-function
		 :requires-return-type-declaration
		 requires-return-type-declaration
		 :documentation documentation
		 :rtl-requires-linking rtl-requires-linking
		 :coerce-rationals-to-floats-p coerce-rationals-to-floats-p
		 :coerce-floats-to-rationals-p coerce-floats-to-rationals-p))))
    ;; Name mappings and random proclamations.
    (cond ((not foreign-protocol)
	   (if object-name
	       (setf (c-name-of-function-object name) object-name)
	       (c-name-of-function-object name))
	   (if entry-name
	       (setf (c-name-of-function-entry name) entry-name)
	       (c-name-of-function-entry name)))
	  ((or (eq foreign-protocol :operator)
	       (eq foreign-protocol :secret-special-form))
	   (if entry-name
	       (error "Foreign function type ~s can't have an :entry-name."
		      foreign-protocol)))
	  (t
	   (if entry-name
	       (if (or allow-multiple-uses-of-entry-name
		       *allow-multiple-foreign-functions-per-c-name*)
		   (progn
		     (tutil::record-c-name entry-name t)
		     (setf (name-of-function-entry name) entry-name))
		   (setf (c-name-of-function-entry name) entry-name))
	       (c-name-of-function-entry name))))
    (unless (equal return-type '(values &rest t))
      (translator-proclaim
       `(ftype (function ,argument-types ,return-type) ,name)))))

;;; Process the specification of the :function usage.  Attributes are:
;;;   :argument-types -- the argument types of this function
;;;   :return-type -- the return-type of the function
;;;   :unsupported -- true if the function isn't actually implemented.
;;;   :entry-name -- name of the C entry point for this function
;;;   :object-name -- name of the C variable holding the function object
;;;   :lambda-list  -- the lambda-list for the function
;;;   :nonconsing -- true if the function is nonconsing
;;;   :state-changing -- true if the function changes external state
;;;   :state-using -- true if the function uses external state
;;;   :declare -- optional declarations about lambda parameters.
;;;   :transforms -- list of conditional transformations to apply
;;;   :generic-function -- true if the function is a generic function.
;;;   :foreign-protocol -- see call.lisp for function descriptor info
;;;   :rtl-requires-linking -- symbol must always be linked to function.
;;;   :foreign-arguments
;;;   :foreign-return-type
;;;   :uses-locals
;;;   :uses-constants
;;;   :lvalue
;;;   :operator

(defun process-function-usage-common (name &key
					   (argument-types nil
							   argument-types-p)
					   (return-type nil return-type-p)
					   (unsupported nil)
					   (entry-name nil)
					   (object-name nil)
					   (lambda-list nil lambda-list-p)
					   (nonconsing nil nonconsing-p)
					   (nonrelocating nil)
					   (state-changing t)
					   (state-using t)
					   (declare nil)
					   (transforms nil)
					   (requires-return-type-declaration
					    nil)
					   (coerce-rationals-to-floats-p nil)
					   (coerce-floats-to-rationals-p nil)
					   (generic-function nil)
					   (foreign-protocol nil)
					   (operator nil)
					   (foreign-arguments nil)
					   (foreign-return-type nil)
					   (uses-locals nil)
					   (uses-constants nil)
					   (documentation nil)
					   (lvalue nil)
					   (rtl-requires-linking nil)
					   (allow-multiple-uses-of-entry-name
					    nil)
					   (array-setf-function-p nil)
					   (alias-p nil))
  (unless (or unsupported
	      #-translator-supports-clos
	      generic-function)
    ;; Check that the right arguments are provided.
    (when (null lambda-list-p)
      (required-keyword :lambda-list))
    (case foreign-protocol
      (:unboxing-macro
       (setq foreign-protocol :macro)
       (unless foreign-arguments
	 (setq foreign-arguments '((:object nil))))
       (unless nonconsing-p
	 (setq nonconsing t))
       (setq argument-types
	     (list (setq return-type
			 (lisp-type foreign-return-type)))))
      (:boxing-macro
       (setq foreign-protocol :macro)
       (setq foreign-return-type :object)
       (setq argument-types
	     (list (setq return-type
			 (lisp-type (caar foreign-arguments)))))
       (unless nonconsing-p
	 (setq nonconsing (translator-subtypep (car argument-types)
					       '(or fixnum character)))))
      (:foreign-arguments-function
       (unless foreign-return-type
	 (setq foreign-return-type :object))
       (when (and lambda-list (null foreign-arguments))
	 (setq foreign-arguments
	       (mapcar #'(lambda (var)
			   (declare (ignore var))
			   '(:object nil))
			lambda-list)))))
    (unless argument-types-p
      (setq argument-types
	    (if foreign-protocol
		(mapcar #'(lambda (foreign-arg)
			    (if (consp foreign-arg)
				(lisp-type (car foreign-arg))
				foreign-arg))
			foreign-arguments)
		(let ((key-p nil))
		  (mapcar #'(lambda (parameter)
			      (when (eq parameter '&key)
				(setq key-p t))
			      (if (member parameter lambda-list-keywords)
				  parameter
				  (if key-p
				      (list parameter 't)
				      't)))
			  lambda-list)))))
    (unless return-type-p
      (setq return-type
	    (if foreign-protocol
		(lisp-type foreign-return-type)
		'(values &rest t))))
    ;; Install the descriptor.
    (setf (defined-as-function name)
	  (if foreign-protocol
	      (progn
		(when generic-function
		  (function-usage-conflict :generic-function t name))
		(when object-name
		  (function-usage-conflict :object-name t name))
		(unless (translator-subtypep
			 return-type
			 (lisp-type foreign-return-type))
		  (setq return-type
			(and-types return-type
				   (lisp-type
				    foreign-return-type))))
		(unless (every #'(lambda (arg-type foreign-arg-spec)
				   (if (consp foreign-arg-spec)
				       (translator-subtypep
					arg-type
					(lisp-type
					 (car foreign-arg-spec)))
				       (eq arg-type foreign-arg-spec)))
			       argument-types foreign-arguments)
		  (setq argument-types
			(mapcar #'(lambda (arg-type foreign-arg-spec)
				    (if (consp foreign-arg-spec)
					(and-types arg-type
						   (lisp-type
						    (car foreign-arg-spec)))
					foreign-arg-spec))
				argument-types foreign-arguments)))
		(when nonconsing (setq nonrelocating t))
		(make-function-descriptor-internal
		 :lambda-list lambda-list :defined-in-rtl-p t
		 :nonconsing nonconsing :nonrelocating nonrelocating
		 :state-changing state-changing :state-using state-using
		 :declare declare
		 :requires-return-type-declaration
		 requires-return-type-declaration
		 :argument-types argument-types :return-type return-type
		 :transforms transforms
		 :foreign-protocol foreign-protocol :operator operator
		 :foreign-return-type foreign-return-type
		 :foreign-arguments foreign-arguments
		 :uses-locals uses-locals :uses-constants uses-constants
		 :documentation documentation :lvalue lvalue
		 :rtl-requires-linking rtl-requires-linking
		 :coerce-rationals-to-floats-p coerce-rationals-to-floats-p
		 :coerce-floats-to-rationals-p coerce-floats-to-rationals-p
		 :array-setf-function-p array-setf-function-p
		 :alias-p alias-p))
	      (progn
		(when foreign-arguments
		  (function-usage-conflict :foreign-arguments nil name))
		(when foreign-return-type
		  (function-usage-conflict :foreign-return-type nil name))
		(when uses-locals
		  (function-usage-conflict :uses-locals nil name))
		(when uses-constants
		  (function-usage-conflict :uses-constants nil name))
		(when lvalue
		  (function-usage-conflict :lvalue nil name))
		(make-function-descriptor-internal
		 :lambda-list lambda-list :defined-in-rtl-p t
		 :nonconsing nonconsing :nonrelocating nonrelocating
		 :state-changing state-changing :state-using state-using
		 :declare declare
		 :argument-types argument-types :return-type return-type
		 :transforms transforms :generic-function-p generic-function
		 :requires-return-type-declaration
		 requires-return-type-declaration
		 :documentation documentation
		 :rtl-requires-linking rtl-requires-linking
		 :coerce-rationals-to-floats-p coerce-rationals-to-floats-p
		 :coerce-floats-to-rationals-p coerce-floats-to-rationals-p
		 :array-setf-function-p array-setf-function-p
		 :alias-p alias-p))))
    ;; Name mappings and random proclamations.
    (cond ((not foreign-protocol)
	   (if object-name
	       (setf (c-name-of-function-object name) object-name)
	       (c-name-of-function-object name))
	   (if entry-name
	       (setf (c-name-of-function-entry name) entry-name)
	       (c-name-of-function-entry name)))
	  ((or (eq foreign-protocol :operator)
	       (eq foreign-protocol :secret-special-form))
	   (if entry-name
	       (error "Foreign function type ~s can't have an :entry-name."
		      foreign-protocol)))
	  (t
	   (if entry-name
	       (if (or allow-multiple-uses-of-entry-name
		       *allow-multiple-foreign-functions-per-c-name*)
		   (progn
		     (tutil::record-c-name entry-name t)
		     (setf (name-of-function-entry name) entry-name))
		   (setf (c-name-of-function-entry name) entry-name))
	       (c-name-of-function-entry name))))
    (unless (equal return-type '(values &rest t))
      (translator-proclaim
       `(ftype (function ,argument-types ,return-type) ,name)))))

(defun function-usage-conflict (keyword foreign-protocol name)
  (error "~s can't be specified ~a :FOREIGN-PROTOCOL in :FUNCTION usage for ~s."
	 keyword
	 (if foreign-protocol "with" "without")
	 name))


(define-usage :function (name &rest keys)
  (apply #'process-function-usage-common name keys))

(define-usage :setf-function (reader &rest keys)
  (apply #'process-function-usage-common `(setf ,reader) keys))

;;; Process the specification of the :variable usage and :constant usages.  
;;; Attributes are:
;;;   :variable-name  -- name of the C variable
;;;   :return-type -- the type of the variable
;;;   :unsupported -- true if the variable isn't implemented yet
;;;   :initial-value -- (optional, for constants only) the initial value of
;;;        the variable.  Only included if it can be represented accurately in
;;;        the host and dumped properly by the translator.
;;;   :simple-p -- (optional, for constants only) says that the value of
;;;        the constant is simple even if it can't be represented or dumped.
;;;   :foreign-p -- if true, then this names a C variable or #define only,
;;;        and the corresponding symbol isn't BOUNDP.
;;;   :documentation -- documentation string.
;;;   :dump-definition-p -- true (default) if dump.lisp should generate a
;;;        definition/declaration for the variable

(define-usage :variable (name &rest keys)
    (apply #'process-variable-usage-common name nil keys))

(define-usage :constant (name &rest keys)
    (apply #'process-variable-usage-common name t keys))

(defun process-variable-usage-common (name constant-p
					   &key (variable-name nil)
					   (return-type t)
					   (initial-value nil initp)
					   (unsupported nil)
					   (simple-p nil) 
					   (foreign-p nil)
					   (documentation nil)
					   (dump-definition-p t)
					   (allow-multiple-uses-of-variable-name
					    nil))
  (unless unsupported
    (if constant-p
	(cond (initp
	       (setf constant-p
		     (if (simple-constant-p initial-value)
			 :simple-constant
			 :complex-constant))
	       (setq return-type
		     (and-types return-type
				(translator-type-of initial-value))))
	      (simple-p
	       (setq constant-p :simple-constant)
	       (setq dump-definition-p nil))
	      (t
	       (setq constant-p :complex-constant)))
	(progn
	  (when simple-p
	    (variable-usage-conflict :simple-p name))
	  (when initial-value
	    (variable-usage-conflict :initial-value name))))
    (setf (defined-as-variable name)
	  (make-variable-descriptor
	   :constant-p constant-p
	   :value-p initp
	   :value initial-value
	   :foreign-p foreign-p
	   :documentation documentation
	   :dump-definition-p dump-definition-p))
    (if variable-name
	(if allow-multiple-uses-of-variable-name
	    (progn
	      (tutil::record-c-name variable-name t)
	      (setf (name-of-global-variable name) variable-name))
	    (setf (c-name-of-global-variable name) variable-name))
	(c-name-of-global-variable name))
    (unless (eq return-type t)
      (translator-proclaim `(type ,return-type ,name)))))


(defun variable-usage-conflict (keyword name)
  (error "~s can't be specified in in :VARIABLE usage for ~s."
	 keyword
	 name))

;;; Process the specification of the :setf-place usages.
;;; Attributes are:
;;;   :setf-function -- true if SETF uses a SETF function to handle this place.

(define-usage :setf-place (name &key (setf-function nil))
  (or setf-function
      (defined-as-generalized-variable name)
      (warn "Missing SETF handler for ~S." name)))

;;; Process the specification of the :class-name usages.
;;; There are no attributes here.  Just complain about missing classes when
;;;    clos is supported.

(define-usage :class-name (name &rest more-args)
  (when more-args
    (warn "Ignoring unknown attributes for :class-name of ~S." name))
  #+translator-supports-clos
  (unless (translator-find-class name nil)
    (when (himpl::find-feature :internal-use)
      (warn "No class definition for ~S." name)))
  )

;;; Process the specification of the :package usage.
;;; (This doesn't seem to belong here; note that the name is ignored.
;;;  Perhaps this information should be placed in initenv.lisp.)

(define-usage :package (name &key package-name variable-name)
  (declare (ignore name))
  (let ((package (find-package package-name)))
    (unless package
      (warn "Processing usage for unknown package:  ~A" package-name))
    (if variable-name
	(setf (c-name-of-package package) variable-name)
	(c-name-of-package package))))

;;; For now, all other usages are essentially no-ops.  Perhaps eventually
;;; we will want some of these to make sure that definitions have actually
;;; been provided -- for example, all things that are declared to have a
;;; :setf-place usage actually are known to the SETF code, and things like
;;; that.

(define-usage :symbol)
(define-usage :macro)
(define-usage :special-form)
(define-usage :type-name)
(define-usage :type-specifier-list)
(define-usage :declaration)
(define-usage :lambda-list-keyword)
(define-usage :random-syntax)
(define-usage :optimize-quality)
(define-usage :documentation-type)
(define-usage :restart-name)
(define-usage :method-combination)

;;; A pair of useful predicates:  see whether a symbol or package
;;; is pre-allocated during runtime initialization

(defun initial-symbol-p (symbol &optional (env *default-global-environment*))
  (and (symbolp symbol)
       (defined-as-symbol symbol env)))


(defun initial-package-p (symbol &optional (env *default-global-environment*))
  (and (packagep symbol)
       (defined-as-package symbol env)))

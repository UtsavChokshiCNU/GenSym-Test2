;;; -*- Mode: Lisp; Package: TCLOSI; Syntax: Common-Lisp -*-
;;;
;;; The macro DEFGENERIC and friends.
;;; Copyright (C) 1991 Chestnut Software, Inc.  All Rights Reserved.
;;;

(in-package "TCLOSI")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/defgeneric.lisp,v $"
 "$Revision: 1.1 $"
 "$Date: 2006/02/28 21:59:02 $")

;;; This is the expander used in the host environment.

(defmacro define-translator-generic-function (name lambda-list &rest options)
  (ensure-legal-function-name name)
  `(translator-ensure-generic-function
     ',name
     ,@(parse-defgeneric-arguments name
				   lambda-list
				   options
				   *default-global-environment*
				   nil)))

;;; This is the expander used by the translator.

(define-translator-macro defgeneric
    (name lambda-list &rest options &environment env)
  (ensure-legal-function-name name)
  (with-translator-message `(defgeneric ,name)
    (multiple-value-bind (initargs initial-method-form)
	(parse-defgeneric-arguments name
				    lambda-list
				    options
				    env
				    t)
      (let ((runtime-initargs (filter-defgeneric-arguments initargs env)))
	`(progn
	   (eval-when (:compile-toplevel)
	     (print-progress-message "Generic function" ',name)
	     (translator-ensure-generic-function
	      ',name
	      :environment ',(translator-environment-name env)
	      ,@initargs))
	   (eval-when (:load-toplevel :execute)
	     (generic-function-setup ,name)
	     (tclos-run:add-named-generic-function ',name ,@runtime-initargs)
	     ,initial-method-form))))))

(define-canonic-filter-table defgeneric)

(defun filter-defgeneric-arguments (initargs env)
  (filter-initargs 'defgeneric initargs env))

(defmacro define-defgeneric-filter (key lambda-list &body body)
  `(define-canonic-filter (,key defgeneric) ,lambda-list ,@body))

;;; Remove :documentation if not recording documentation for runtime.
(define-defgeneric-filter :documentation (initargs env)
  (declare (ignore env))
  (multiple-value-bind (value therep)
      (cgetf initargs :documentation)
    (when (and therep (not (record-documentation-p value)))
      (cremf initargs :documentation))
    initargs))

;;; If specified method combination is STANDARD, with no options, then strip
;;; it out since that is the default.
(define-defgeneric-filter :method-combination (initargs env)
  (multiple-value-bind (type type-value-there)
      (resolve-constant-initarg :method-combination-type initargs env)
    (multiple-value-bind (options options-value-there options-there)
	(resolve-constant-initarg :method-combination-options initargs env)
      (when (and type-value-there (eq type 'standard))
	(cond ((not options-there)
	       (cremf initargs :method-combination-type))
	      ((and options-value-there (null options))
	       (cremf initargs :method-combination-type)
	       (cremf initargs :method-combination-options))))
      initargs)))

;;; If specified argument precedence order is just left to right, strip it out
;;; since that is the default.
(define-defgeneric-filter :argument-precedence-order (initargs env)
  (multiple-value-bind (apo apo-value-there)
      (resolve-constant-initarg :argument-precedence-order initargs env)
    (multiple-value-bind (lambda lambda-value-there)
	(resolve-constant-initarg :lambda-list initargs env)
      (when (and apo-value-there
		 lambda-value-there
		 (equal apo (parse-lambda-list-into-components lambda)))
	(cremf initargs :argument-precedence-order))
      initargs)))

(define-defgeneric-filter :generic-function-class (initargs env)
  (multiple-value-bind (gf-class therep)
      (resolve-constant-initarg :generic-function-class initargs env)
    (when (and therep (eq gf-class 'standard-generic-function))
      (cremf initargs :generic-function-class))
    initargs))

(define-defgeneric-filter :method-class (initargs env)
  (multiple-value-bind (method-class therep)
      (resolve-constant-initarg :method-class initargs env)
    (when (and therep (eq method-class 'standard-method))
      (cremf initargs :method-class))
    initargs))

;;; This has to be a special form.  Sigh.
;;; At least try to make it have functional syntax so that user codewalkers
;;; have a chance of handling it properly.  Complain if something confusing
;;; happens.

(define-translator-macro generic-function-setup (name)
  (unless timpl::*toplevel-p*
    (timpl::note-non-toplevel-function-definition name))
  `(eval-when (:load-toplevel)
     (tclos-run:%establish-generic-function ',name)))

(define-toplevel-form tclos-run:%establish-generic-function (name)
  (with-translator-message `(defgeneric ,name)
    (flet ((translate-name (name)
	     (return-from tclos-run:%establish-generic-function
	       (timpl::re-translate-form name)))
	   (translate-toplevel-name (name)
	     (return-from tclos-run:%establish-generic-function
	       (timpl::translate-toplevel-form name
					       timpl::*environment*
					       timpl::*compile-time-too*))))
      (unless timpl::*compile-time-only*
	(when (not timpl::*toplevel-p*)
	  (warn "~S encountered at non-toplevel.~@
               Correct code will be generated, but this should never happen."
		'tclos-run:%establish-generic-function)
	  (translate-name name))
	(let ((env timpl::*environment*)
	      (real-name nil))
	  (multiple-value-bind (name-value therep constantp)
	      (translator-constant-value name env)
	    (unless constantp
	      (error "The argument to ~S is not a constant form: ~S."
		     'tclos-run:%establish-generic-function name))
	    (unless therep
	      (error "The argument to ~S is not a resolvable constant: ~S."
		     'tclos-run:%establish-generic-function name))
	    (ensure-legal-function-name name-value)
	    (setf real-name name-value))
	  (let ((record (defined-as-generic-function real-name env)))
	    (when (null record) (translate-toplevel-name name))
	    (let ((defrec
		      (generic-function-record-redefinition-record record)))
	      (if (redefinition-record-definition-needs-dumping defrec)
		  (prog1
		      (timpl::translate-define-generic-function real-name env)
		    (redefinition-record-note-definition-dumped defrec))
		  (translate-toplevel-name name)))))))))

(defun parse-generic-function-arguments (lambda-list options env methodsp)
  (declare (ignore env))
  (let ((initargs nil)
	(methods ()))
    (setf (cgetf initargs :lambda-list) `',lambda-list)
    (labels ((ensure-single-option (key option)
	       (or (not (nth-value 1 (cgetf initargs key)))
		   (warn "Ignoring duplicate generic function option ~S."
			 option)))
	     (add-option (key value option)
	       (when (ensure-single-option key option)
		 (setf (cgetf initargs key) value))))
      (dolist (option options)
	(if (atom option)
	    (warn "Ignoring invalid generic function option ~S." option)
	    (case (first option)
	      (declare
	       (add-option :declare `',(rest option) option))
	      (:argument-precedence-order
	       (check-argument-precedence-order lambda-list (rest option))
	       (add-option :argument-precedence-order
			   `',(rest option)
			   option))
	      (:documentation
	       (add-option :documentation `',(second option) option))
	      ((:generic-function-class :method-class)
	       (add-option (first option) `',(second option) option))
	      (:method-combination
	       (add-option :method-combination-options `',(cddr option) option)
	       (add-option :method-combination-type `',(second option) option))
	      (:method
	       (when methodsp
		 (push (cdr option) methods)))
	      (t
	       (warn "Ignoring invalid generic function option ~S." option)))))
      (values initargs methods))))

(defun validate-generic-function-lambda-list (lambda-list)
  (let ((new-lambda-list nil)
	(optionalp nil))
    (macrolet ((collect (thing)
		 `(push ,thing new-lambda-list))
	       (ignore-init (var init initp)
		 `(when ,initp
		    (warn "Ignoring initform for ~S: ~S." ,var ,init)))
	       (ignore-svar (var svar-p)
		 `(when ,svar-p
		    (warn "Ignoring suppliedp var for ~S." ,var))))
      (parse-lambda-list 
       lambda-list
       :required #'(lambda (thing)
		     (collect thing))
       :optional #'(lambda (var init initp svar svar-p)
		     (declare (ignore svar))
		     (unless optionalp
		       (setf optionalp t)
		       (collect '&optional))
		     (collect var)
		     (ignore-init var init initp)
		     (ignore-svar var svar-p))
       :rest #'(lambda (var)
		 (collect '&rest)
		 (collect var))
       :keyp #'(lambda ()
		 (collect '&key))
       :key #'(lambda (var key init initp svar svar-p)
		(declare (ignore svar))
		(collect `((,key ,var)))
		(ignore-init key init initp)
		(ignore-svar key svar-p))
       :allow-other-keys-p #'(lambda ()
			       (collect '&allow-other-keys))
       :aux #'(lambda (var init initp)
		(declare (ignore init initp))
		(warn "Ignoring &aux parameter ~S." var)))
      (nreverse new-lambda-list))))

(defun check-argument-precedence-order (lambda-list precedence-order)
  (let* ((required (parse-lambda-list-into-components lambda-list))
	 (length (length required))
	 (map (make-array length :element-type t :initial-element nil)))
    (declare (type list required)
	     (type fixnum length)
	     (type simple-vector map))
    (flet ((mismatch-error (lambda-list precedence-order)
	     (error "The argument precedence order ~S doesn't match ~S."
		    precedence-order lambda-list)))
      (if (/= length (length precedence-order))
	  (mismatch-error lambda-list precedence-order)
	  (do ((args required (cdr args))
	       (argp 0 (1+ argp)))
	      ((endp args))
	    (let ((place (position (car args) precedence-order)))
	      (if (or (null place) (svref map place))
		  (mismatch-error lambda-list precedence-order)
		  (setf (svref map place) argp))))))))

(defun parse-defgeneric-arguments (name lambda-list options env methodsp)
  (setf lambda-list (validate-generic-function-lambda-list lambda-list))
  (multiple-value-bind (initargs methods)
      (parse-generic-function-arguments lambda-list options env methodsp)
    (values initargs
	    `(make-defgeneric-initial-methods ,name ,@methods))))

(define-translator-macro make-defgeneric-initial-methods
    (name &rest method-specs &environment env)
  (multiple-value-bind (bindings declspecs add-forms)
      (collect-initial-methods `',name name method-specs env)
    `(flet ,bindings
       (declare ,@declspecs)
       (tclos-run:update-initial-methods ',name (list ,@add-forms)))))

(defun collect-initial-methods (gf name methods env)
  (let ((bindings ())
	(declspecs ())
	(add-forms ()))
    (mapc #'(lambda (method)
	      (multiple-value-bind (qualifiers lambda-list body)
		  (parse-method-stuff method)
		(multiple-value-bind (binding decls add-form)
		    (make-add-method gf
				     name
				     qualifiers
				     lambda-list
				     body
				     env)
		  (push binding bindings)
		  (setf declspecs (append decls declspecs))
		  (push add-form add-forms))))
	  methods)
    (values bindings declspecs (nreverse add-forms))))

(defun extract-qualifiers-and-specializers (method-tail)
  (multiple-value-bind (qualifiers lambda-list)
      (parse-method-stuff method-tail)
    (values qualifiers (extract-specializer-names lambda-list))))

(in-package "TIMPL")

(defun translate-define-generic-function (name env)
  (let* ((*toplevel-p* nil)
	 (*free-temporaries* nil)
	 (record (make-generic-function-definition-record name env)))
    (translate-leaf-toplevel-form-aux
     (list (make-generic-function-definition-statement record)))))

(defun make-generic-function-definition-statement (record)
  (make-target-form 'function-definition record))

(defun make-generic-function-definition-record (name env)
  (let ((record (new-function-record name :generic-function))
	(descriptor (defined-as-function name env)))
    (update-function-descriptor-for-definition name descriptor)
    (multiple-value-bind (statements value)
	(translate-form `#',name env *value-context*)
      (setf (function-record-statements record)
	    (nreverse (cons value statements))))
    (setf (function-record-documentation record)
	  (function-descriptor-documentation descriptor))
    (let ((info (get-descriptor-lambda-list-info descriptor)))
      (setf (function-record-lambda-list-info record) info)
      (setf (function-record-variadic-p record)
	    (or (lambda-list-info-restp info)
		(lambda-list-info-keyp info))))
    record))




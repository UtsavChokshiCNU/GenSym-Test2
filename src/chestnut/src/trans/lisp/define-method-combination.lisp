;;; -*- Mode: Lisp; Package: TCLOSI; Syntax: Common-Lisp -*-
;;;
;;; The macro DEFINE-METHOD-COMBINATION-FUNCTION
;;; Copyright (C) 1991 Chestnut Software, Inc.  All Rights Reserved.
;;;

(in-package "TCLOSI")

(himpl:note-rcs-revision "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/define-method-combination.lisp,v $"
			 "$Revision: 1.1 $"
			 "$Date: 2006/02/28 21:59:02 $")

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Errors in method combination
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;; These conditions probably should be named something different, since we
;;; aren't supposed to have these names defined as types (re. PACKAGE-CLUTTER).
;;;
;;; *** All this kind of code is needed at runtime.  Since we don't do
;;; *** method-combination at translation, it isn't needed here.

;(define-condition method-combination-error (error)
;    ((generic-function
;       :initarg :generic-function
;       :reader method-combination-error-generic-function)
;     (method-combination
;       :initarg :method-combination
;       :reader method-combination-error-method-combination)
;     (format-control
;       :initarg :format-control
;       :initarg :format-string
;       :reader method-combination-error-format-control)
;     (format-arguments
;       :initarg :format-arguments
;       :reader method-combination-error-format-arguments))
;  (:report
;   (lambda (condition stream)
;     (format stream
;	     "While computing an effective method for ~S using ~S:~%~?"
;	     (method-combination-error-generic-function condition)
;	     (method-combination-error-method-combination condition)
;	     (method-combination-error-format-string condition)
;	     (method-combination-error-format-arguments condition)))))
;
;(define-condition invalid-method-error (method-combination-error)
;    ((method
;       :initarg :method
;       :reader invalid-method-error-method))
;  )

;;; These variables are bound when in a method combination function, in order
;;; to provide additional context for calls to the functions
;;; METHOD-COMBINATION-ERROR and INVALID-METHOD-ERROR.
;;; They need to be in the runtime system.
;
;(defvar tclos-run:*generic-function-for-method-combination-errors*)
;(defvar tclos-run:*method-combination-for-method-combination-errors*)

;;; *** I think these need to be in some other package?
;(defun method-combination-error (format-string &rest arguments)
;  (method-combination-error-internal 'method-combination-error
;				     :format-string format-string
;				     :format-arguments arguments))
;
;(defun invalid-method-error (method format-string &rest arguments)
;  (method-combination-error-internal 'invalid-method-error
;				     :method method
;				     :format-string format-string
;				     :format-arguments arguments))
;
;(defun method-combination-error-internal (condition-name &rest initargs)
;  (let ((gf tclos-run:*generic-function-for-method-combination-errors*)
;	(mc tclos-run:*method-combination-for-method-combination-errors*))
;    (if (or (null gf) (null mc))
;	(error
;	  "~S called outside dynamic extent of a method combination function."
;	  condition-name)
;	(apply #'error condition-name
;	       :generic-function gf
;	       :method-combination mc
;	       initargs))))

(define-translator-macro with-method-combination-errors
          (generic-function method-combination &body body)
  `(let ((tclos-run:*generic-function-for-method-combination-errors*
	    ,generic-function)
	 (tclos-run:*method-combination-for-method-combination-errors*
	    ,method-combination))
     ,@body))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Parsing method group specifiers
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;; method-group-specifier := (variable {{qualifier-pattern}+ | predicate}
;;;                                     [[ ^long-form-option ]]
;;;
;;; long-form-option := :DESCRIPTION format-string (not evaluated) |
;;;                     :ORDER order (evaluated) |
;;;                     :REQUIRED boolean (not evaluated)

(defstruct (parsed-method-group-specifier
	    (:conc-name parsed-mgs-)
	    (:copier nil)
	    (:predicate nil))
  variable
  patterns
  match
  order
  required
  description)

(defvar *method-combination-method-qualifier*   (make-variable "MC-qualifier"))
(defvar *method-combination-method*             (make-variable "MC-method"))

(defun parse-method-group-specifier (specifier)
  (destructuring-bind (variable pattern &rest more)
		      specifier
    (check-type variable symbol)
    (let ((patterns (list pattern))
	  (predicate (and (symbolp pattern) (not (eq pattern '*)) pattern)))
      (unless predicate
	;; If pattern is not a predicate function, then collect any additional
	;; qualifier patterns.
	(do ()
	    ((endp more))
	  (let ((item (car more)))
	    (if (not (or (listp item) (eq item '*)))
		(return)
		(progn
		  (push item patterns)
		  (pop more)))))
	(setf patterns (nreverse patterns)))
      (let ((match
	     #'(lambda (qualifier-var)
		 (if predicate
		     (list predicate qualifier-var)
		     (flet ((make-match-form (pattern)
			      `(qualifier-pattern-match-p ,qualifier-var
							  ,pattern)))
		       (if (endp (cdr patterns))
			   (make-match-form (car patterns))
			   `(or ,@(mapcar #'make-match-form patterns))))))))
	(destructuring-bind (&key description
				  required
				  (order :most-specific-first))
			    more
	  (check-type description (or null string))
	  (make-parsed-method-group-specifier
	     :variable variable
	     :patterns patterns
	     :match match
	     :order order
	     :required required
	     :description description))))))

;;; This may be hairier than it actually needs to be, since qualifiers are
;;; atoms (88-002R, p.1-24).  However, this restriction is only needed so that
;;; DEFMETHOD and friends can distinguish a qualifier from the lambda-list,
;;; and is not needed when the method is created by MAKE-INSTANCE.

(define-translator-macro qualifier-pattern-match-p (qualifier pattern)
  (labels ((pattern-match (pattern qualifier)
	     (cond ((eq pattern '*) `(progn ,qualifier t))
		   ((null pattern) `(null ,qualifier))
		   ((or (atom pattern)
			(not (star-present-p pattern)))
		    `(equal ,qualifier ',pattern))
		   (t (pattern-match-list pattern qualifier))))
	   (pattern-match-list (pattern qualifier)
	     (let ((qvar *method-combination-method-qualifier*)
		   (matchers ()))
	       (do ((p pattern (cdr p)))
		   ((or (atom p)
			(not (star-present-p p)))
		    (push (pattern-match p qvar) matchers)
		    `(let ((,qvar ,qualifier))
		       (and ,@(nreverse matchers))))
		 (push `(consp ,qvar) matchers)
		 (push (pattern-match (car p) `(pop ,qvar)) matchers))))
	   (star-present-p (pattern)
	     ;; Note: Using nsubst-if to perform tree traversal, rather than
	     ;; for actual side effects.
	     (nsubst-if nil
			#'(lambda (item)
			    (when (eq item '*)
			      (return-from star-present-p t)))
			pattern)
	     nil))
    (cond ((null pattern) `(null ,qualifier))
	  ((eq pattern '*) T)
	  ((listp pattern) (pattern-match pattern qualifier))
	  (t
	   (error "Invalid method qualifier pattern ~S." pattern)
	   ;(error 'simple-program-error
	   ;	  :format-string "Invalid method qualifier pattern ~S."
	   ;	  :format-arguments (list pattern))
	   ))))

(define-translator-macro with-parsed-methods
        (group-specifiers methods &body body)	  
  ;; Note that currently we do nothing the the :description options
  (setf group-specifiers
	(mapcar #'parse-method-group-specifier group-specifiers))
  (let ((method *method-combination-method*)
	(qualifier *method-combination-method-qualifier*))
    `(let ,(mapcar #'(lambda (spec) `(,(parsed-mgs-variable spec) nil))
		   group-specifiers)
       (dolist (,method ,methods)
	 (let ((,qualifier (tclos:method-qualifiers ,method)))
	   (cond ,@(mapcar #'(lambda (spec)
			       `(,(funcall (parsed-mgs-match spec) qualifier)
				 ;; Note that the error check for same role
				 ;; for different methods with same specializer
				 ;; is defered to sort-parsed-methods.
				 (push ,method
				       ,(parsed-mgs-variable spec))))
			   group-specifiers)
		 (t
		  (invalid-method-error
		     ,method
		     "The method ~S has invalid qualifiers ~S."
		     ,method ,qualifier)))))
       ,@(mapcar #'(lambda (spec &aux (var (parsed-mgs-variable spec)))
		     `(setf ,var
			    (sort-parsed-methods ,var
						 ,(parsed-mgs-patterns spec)
						 ,(parsed-mgs-order spec)
						 ,(parsed-mgs-required spec))
			    ))
		 group-specifiers)
       ,@body)))

(define-translator-macro sort-parsed-methods (methods patterns order required)
  `(tclos-run:%sort-parsed-methods ,methods ,order ',patterns ',required))

#|

;;; This function needs to be in the runtime system.
;;; Note that the methods list is initially in most-specific-last order.
(defun tclos-run:%sort-parsed-methods (methods order patterns required)
  (cond ((endp methods)
	 (when required
	   (method-combination-error
	        "No methods matched the qualifier pattern~P~
                 ~:[ ~S.~*~;~*~{~%  ~S~}~]"
		(length patterns)
		(cdr patterns)
		(car patterns)
		patterns)))
	((endp (cdr methods)) methods)
	(t
	 (ecase order
	   (:most-specific-first (setf methods (nreverse methods)))
	   (:most-specific-last))
	 (do* ((tail methods)
	       (method (pop tail))
	       (spec (tclos:method-specializers method)))
	      ((endp methods))
	   (let ((next-method (pop tail))
		 (next-spec (tclos:method-specializers method)))
	     (if (not (equal spec next-spec))
		 (setf method next-method spec next-spec)
		 ;; As described in 88-002R, page 2-34, last paragraph of
		 ;; the Arguments section.
		 (method-combination-error
		  "The methods ~S and ~S play the same role and have the~@
                   same specializers, so their order in the effective method ~
                   is not well defined."
		  method
		  next-method))))
	 methods)))

|#

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Creating the effective method
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define-translator-declaration method-combination-effective-method (spec env)
  (declare (ignore env))
  (destructuring-bind (var) (cdr spec)
    (values ()
	    ()
	    ()
	    `((method-combination-effective-method . ,var)))))

(defvar *effective-method-var*  (make-variable "MC-effective-method"))

(define-translator-macro with-effective-method ((var gf methods) &body body)
  `(let* ((,var (tclos-run:%make-effective-method ,gf ,methods))
	  (tclos-run:*method-combination-effective-method* ,var))
     (declare (method-combination-effective-method ,var))
     ,@body))

(defun find-effective-method-var (env)
  (or (translator-declaration-information
           'method-combination-effective-method env)
      (error "Not in a define-method-combination-function body.")))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Parsing :arguments option
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;; There are two versions of this, one for DEFINE-METHOD-COMBINATION and one
;;; for DEFINE-METHOD-COMBINATION-FUNCTION, since they have somewhat different
;;; handling of things.
;;;
;;; [The version for DEFINE-METHOD-COMBINATION has not been implemented, since
;;; we aren't presently supporting it in the translator.  However, I'm pretty
;;; sure it should be able to use most of the mechanisms here as part of such
;;; an implementation.]
;;;
;;; The semantics provided here correspond to those described in the X3J13
;;; proposal METHOD-COMBINATION-ARGUMENTS:CLARIFY.

;;; Parsing LOCAL-METHOD lambda-lists.  These lambda-lists appear as the first
;;; argument in an LOCAL-METHOD form, as it appears in the body of a
;;; DEFINE-METHOD-COMBINATION-FUNCTION form.

;;; Parse the lambda-list for a LOCAL-METHOD form.
;;;
;;; Method-args is a list of the variables that will be bound to the real
;;; arguments to the method being created.
;;;
;;; Two values are returned.
;;;
;;;  * A binding list suitable for LET*, which will bind the variables in the
;;;    lambda-list to the corresponding argument values.
;;;
;;;  * A list of declaration specifiers for internal variables in the binding
;;;    list. 
;;;
;;;  * A list of the keyword specifiers mentioned in the lambda-list.  This is
;;;    used to compute the keyword permutation vector for the method.  The
;;;    order of entries in this list corresponds to the order of entries in the
;;;    permutation vector.
;;;

(defun parse-method-combination-function-arguments (lambda-list method-args)
  (multiple-value-bind (whole required optional rest keys aux)
      (parse-method-combination-arguments-lambda-list lambda-list)
    (collect-method-combination-arguments-binding
     whole required optional rest keys aux method-args)))

;;; Parse the lambda-list into the various sections, with entries in each
;;; section in canonical form.  Returns 6 values:
;;;
;;;  * WHOLE	The &whole variable (if present) or Nil.
;;;
;;;  * REQUIRED	A list of the required variables.
;;;
;;;  * OPTIONAL	A list of the optional parameters.  The format for entries in
;;;		this list is (variable initform [ suppliedp-var ]).
;;;
;;;  * REST	The &rest variable (if present) or Nil.
;;;
;;;  * KEYS	A list of the keyword parameters.  The format for entries in
;;;		this list is ((key variable) initform [ suppliedp-var ]).
;;;
;;;  * AUX	A list of the auxiliary parameters.  The format for entries in
;;;		this list is (variable initform).

(defun parse-method-combination-arguments-lambda-list (lambda-list)
  (let ((whole (when (eq (car lambda-list) '&whole)
		 (prog1 (cadr lambda-list)
		   (setf lambda-list (cddr lambda-list))))))
    (multiple-value-bind (required optional rest keyp keys alwky aux)
	(parse-lambda-list-into-components lambda-list)
      (declare (ignore keyp alwky))
      (values whole required optional rest keys aux))))

;;; Generate the let* binding list for the arguments.
;;;
;;; A second value is returned, which is a list of keyword specifiers present
;;; in the keys argument, ordered by first occurance if a keyword is used more
;;; than once.  The ordering of the keywords is used to generate the keyword
;;; permutation vector for this lambda-list.

;;; These symbols are bound as temporary lexical variables in the binding list
;;; for the arguments.

(defvar *method-combination-index*           (make-variable "MC-index"))
(defvar *method-combination-end*             (make-variable "MC-end"))
(defvar *method-combination-temp*            (make-variable "MC-temp"))
(defvar *method-combination-key-table*       (make-variable "MC-key-table"))

;;; These symbols are assumed to be lexically bound in the scope of the binding
;;; list for the arguments.  They are bound to the following values:
;;;
;;;  * Required	   The number of required argument for the generic-function.
;;;  * Positional  The number of positional arguments for the generic-function.

(defvar *method-combination-required*        (make-variable "MC-req"))
(defvar *method-combination-positional*      (make-variable "MC-pos"))

(defparameter *method-argument-ranges*
  `((,*method-combination-required*
         tclos-run:%effective-method-required fixnum)
    (,*method-combination-positional*
         tclos-run:%effective-method-positional fixnum)))

;;; *** Assumptions about the values in the effective-method:
;;; ***  %effective-method-required: This is the number of required args.
;;; ***  %effective-method-positional: This is the number of positional args.

(define-translator-macro with-method-argument-ranges
    (&body body &environment env)
  (let ((method (find-effective-method-var env)))
    `(let* ,(mapcar #'(lambda (entry)
			`(,(first entry) (,(second entry) ,method)))
	            *method-argument-ranges*)
       (declare ,@(mapcan #'(lambda (entry)
			      (let ((var (first entry))
				    (type (third entry)))
				`((ignorable ,var)
				  ,@(unless (eq type t)
				      `((type ,type ,var))))))
		          *method-argument-ranges*))
       ,@body)))

(defun collect-method-combination-arguments-binding
       (whole required optional rest keys aux method-args)
  (let ((bindings ())
	(index nil)
	(temp-var nil)
	(ordered-keys nil)
	(key-table *method-combination-key-table*)
	(declspecs ()))
    (labels ((bind (var init)
	       (push (list var init) bindings))
	     (bind-temp (&optional init)
	       (when (null temp-var)
		 (bind (setf temp-var *method-combination-temp*) init)))
	     (bind-index (init)
	       (setf index *method-combination-index*)
	       (push `(type fixnum ,index) declspecs)
	       (bind index init))
	     )
      ;; When a &whole var present, bind it to a list of all the arguments.
      (when whole (bind whole '(method-argument-list)))
      ;; Required parameters which match the generic function required
      ;; arguments get bound to the corresponding argument.  If there are more
      ;; required parameters than there are required arguments to the generic
      ;; function, unmatched parameters are bound to Nil.
      (when required
	(let ((index -1))
	  (dolist (var required)
	    (bind var `(when (< ,(incf index) ,*method-combination-required*)
			 (method-argument ,index))))))
      ;; Optional parameters which match the generic function optional
      ;; arguments get bound to the corresponding argument.  If there are more
      ;; optional parameters than there are optional arguments to the generic
      ;; function, unmatched parameters get bound to the result of evaluating
      ;; their initforms.
      (when optional
	(flet ((make-opt (var test index init)
		 (bind var `(if ,test (method-argument ,index) ,init))))
	  (let ((test
		 `(and (< ,(if (endp (cdr optional))
			       ;; If only one optional, position of it (if
			       ;; present) is at the end of the required
			       ;; list.  Don't need any iteration variable
			       ;; for this case.
			       *method-combination-required*
			       ;; Otherwise, bind iteration variable to start
			       ;; position for optionals, and use that in the
			       ;; test.
			       (progn
				 (bind-index *method-combination-required*)
				 index))
			  ,*method-combination-positional*)
		       (method-optional-argument-p
			    ,*method-combination-required*))))
	    (destructuring-bind (var init &optional (svar nil svar-p))
		(car optional)
	      (let ((index (or index *method-combination-required*)))
		(if (not svar-p)
		    (make-opt var test index init)
		    (progn
		      (bind-temp test)
		      (make-opt var temp-var index init)
		      (bind svar temp-var))))))
	  ;; Now bind remaining optional parameters to the corresponding
	  ;; arguments to the generic function.
	  (dolist (parm (cdr optional))
	    (destructuring-bind (var init &optional (svar nil svar-p))
		parm
	      (let ((test `(and (< (incf ,index)
				   ,*method-combination-positional*)
				(method-optional-argument-p ,index))))
		(if (not svar-p)
		    (make-opt var test index init)
		    (progn
		      (if (null temp-var)
			  (progn
			    (bind-temp test)
			    (setf test temp-var))
			  (setf test `(setf ,temp-var ,test)))
		      (make-opt var test index init)
		      (bind svar temp-var))))))))
      (flet ((make-rest-init (method-args)
	       `(when (tclos-run:%effective-method-restp
		           ,(method-arguments-effective-method method-args))
		  (method-rest-list))))
	(when rest
	  ;; A &rest parameter is bound to the &rest arguments to the generic
	  ;; function.  If the generic function's parameter list specifies
	  ;; neither &rest nor &key, then the &rest parameter is bound to Nil.
	  (bind rest (make-rest-init method-args)))
	(when keys
	  ;; When &key parameters are present, bind a variable to the keyword
	  ;; permutation vector if it exists, or to the &rest list if the
	  ;; permutation vector does not exist.  Note that this assumes that
	  ;; the permutation vector will only exist if the set of keys
	  ;; mentioned in the local-method form is a subset of the set of keys
	  ;; mentioned in the applicable methods.  This is required by the
	  ;; definition of method-combination-key-value, which is the accessor
	  ;; that does the keyword parameter lookup here.
	  (bind key-table
		`(or (and (tclos-run:%effective-method-keys
			    ,(method-arguments-effective-method method-args))
		          (tclos-run:%effective-method-keyword-permutation
			    ,(method-arguments-effective-method method-args)
			    ,(method-arguments-method-index method-args)))
		     ,(or rest (make-rest-init method-args))))
	  ;; Now iterate over the keyword parameters, collecting the bindings
	  ;; for them.  Key-map and next-key-index are used to build up the
	  ;; mapping from keywords to indices in the prospective keyword
	  ;; permutation vector.
	  (let ((key-map ())
		(next-key-index 0))
	    (bind-temp)                    ; force temp to be bound
	    (dolist (parm keys)
	      (let* ((key (caar parm))
		     ;; Compute permutation vector index for this key.
		     (key-index (or (assoc key key-map)
				    (prog1 next-key-index
				      (push (cons key next-key-index) key-map)
				      (incf next-key-index))))
		     ;; Form which returns the value for the keyword parameter,
		     ;; or returns the unsupplied cookie.
		     (value-form
		       `(method-combination-key-value ,key-table
						      ',key
						      ,key-index)))
		(multiple-value-bind (var-bind svar-bind)
		    (make-method-key-bindings parm temp-var value-form)
		  (push var-bind bindings)
		  (when svar-bind (push svar-bind bindings)))))
	    ;; Compute the ordered keys from the key map.  Entries in the key
	    ;; map were added to the front of the map in order of increasing
	    ;; index, so need to reverse the result.
	    (setf ordered-keys (nreverse (mapcar #'car key-map))))))
      (when aux
	(dolist (parm aux)
	  (bind (car parm) (cadr parm))))
      (values (nreverse bindings) declspecs ordered-keys))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    The macro LOCAL-METHOD
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;; LOCAL-METHOD expands into a form which returns a list with the
;;; following entries:
;;;
;;; * The symbol LOCAL-METHOD.  This gives the combining mechanism a test for
;;;   whether an object is an local-method.
;;;
;;; * The method function for the method.  This is a function or function name.
;;;
;;; * The ordered list of keywords for this method.  This may get used in the
;;;   construction of a keyword permutation vector for the method.

(define-translator-macro tx:local-method
        (lambda-list &body body &environment env)
  (expand-local-method lambda-list body env))

(defun expand-local-method (lambda-list body env)
  (declare (ignore env))
  (multiple-value-bind (method-args method-decls)
      (make-method-arguments)
    (multiple-value-bind (bindings binding-decls keys)
	(parse-method-combination-function-arguments lambda-list method-args)
      (multiple-value-bind (body body-decls doc) (parse-body body t)
	`(list
	   'tx:local-method
	   #'(lambda ,method-args
	       ,@(when doc (list doc))
	       (declare ,@method-decls)
	       (let* ,bindings
		 (declare ,@binding-decls ,@body-decls)
		 (macrolet ((tx:call-combined-method (method &environment env)
			      (expand-combined-method-call method env)))
		   ,@body)))
	   ',keys)))))

;;; CALL-COMBINED-METHOD expands into an EFFECTIVE-METHOD-CALL form, with the
;;; method index being the result of the method argument (which must be the
;;; result of a COMBINE-METHODS form).

(defun expand-combined-method-call (method env)
  (let ((method-args (method-arguments env)))
    `(tclos-run:%effective-method-call
       ,(method-arguments-effective-method method-args)
       ,method
       ,(method-arguments-frame method-args)
       ,(method-arguments-argq method-args))))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    The macro COMBINE-METHODS
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define-translator-macro tx:combine-methods (method next-methods)
  `(tclos-run:%update-effective-method
      tclos-run:*method-combination-effective-method*
      ,method
      ,next-methods))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    The define-method-combination-function macro
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define-translator-macro tx:define-method-combination-function
       (name lambda-list method-groups &body stuff &environment env)
  (expand-method-combination-function name
				      lambda-list
				      method-groups
				      stuff
				      (null lambda-list)
				      env))

(defvar *method-combination-generic-function* (make-variable "MC-gf"))
(defvar *method-combination-object*           (make-variable "MC-object"))
(defvar *method-combination-methods*          (make-variable "MC-methods"))

(defun method-combination-function-name (name env)
  (declare (ignore env))
  (make-name "~A-method-combination-function" name))

(defun expand-method-combination-function
       (name lambda-list method-groups stuff simplep env)
  (check-type name symbol)
  (let ((function-name (method-combination-function-name name env))
	(gf *method-combination-generic-function*)
	(mc *method-combination-object*)
	(methods *method-combination-methods*)
	(gf-var
	 (when (and (consp stuff)
		    (consp (car stuff))
		    (eq (caar stuff) ':generic-function))
	   (cadr (pop stuff)))))
    (multiple-value-bind (body declspecs doc) (parse-body stuff t)
      (let ((function
	     `(,function-name (,gf ,mc ,methods ,@lambda-list)
	       ,@(when doc (list doc))
	       ,@(when declspecs `((declare ,@declspecs)))
	       (with-method-combination-errors ,gf ,mc
		 (with-parsed-methods ,method-groups ,methods
		   (with-effective-method
		       (,*effective-method-var* ,gf ,methods)
		     (let ,(when gf-var `((,gf-var ,gf)))
		       (tclos-run:%finalize-effective-method
			    ,*effective-method-var*
			    (block ,name
			      (with-method-argument-ranges ,@body))))))))))
	(setf doc (record-documentation-p doc))
	`(progn
	   (eval-when (:compile-toplevel)
	     (print-progress-message "Method combination" ',name))
	   (eval-when (:load-toplevel :execute)
	     (flet (,function)
	       (tclos-run:record-method-combination-function
		    ',name
		    #',function-name
		    ,(when simplep 'T)
		    ,@(when doc (list doc))))))))))

#|

 (defun tclos-run:compute-effective-method (gf mc methods)
  (apply (method-combination-function mc)
	 gf mc methods
	 (tclos-run:generic-function-method-combination-options gf)))

;;; *** This needs to be available at runtime.

 (defun tclos-run:%update-effective-method (effective-method method next-methods)
  (if (null effective-method)
      (error "Call to ~S executed outside the dynamic extent of the body~@
              of a ~S form."
	     'tx:combine-methods 'tx:define-method-combination-function)
      (let* ((method-table (effective-method-method-table effective-method))
	     (function-table (effective-method-function-table effective-method))
	     (next-method (effective-method-next-method-table effective-method))
	     (key-table (effective-method-key-table effective-method))
	     (length (length method-table))
	     ;; During computation of the effective method, the start slot is
	     ;; used as the next available method index.
	     (start-index (effective-method-start effective-method))
	     (index start-index)
	     )
	(declare (type simple-vector method-table function-table key-table)
		 (type simple-bit-vector next-method)
		 (type fixnum length index))
	(macrolet ((add-method-to-tables (method)
		     `(let ((method ,method))
			(when (<= length index)
			  (multiple-value-setq
			    (method-table function-table next-method key-table)
			    (expand-tables effective-method)))
			(cond ((not (consp method))
			       (set-table-entries (method-function method)
						  method))
			      ((eq (car method 'tx:local-method))
			       (set-table-entries (second method)
						  (first method)
						  (third method)))
			      (t
			       (error "~S is not a method." method)))
			(when (endp next-methods)
			  (setf (sbit next-method index) 0)
			  (setf (effective-method-start effective-method)
				(1+ index))
			  (return-from update-effective-method start-index))
			(setf (sbit next-method index) 1)
			(incf index)))
		   (set-table-entries (function method &optional keys)
		     `(progn
			(setf (svref function-table index) ,function)
			(setf (svref method-table index) ,method)
			,@(when keys
			    `((setf (svref key-table index) ,keys))))))
	  (add-method-to-tables method)
	  (loop
	    (add-method-to-tables (pop next-methods)))))))

;;; This needs to be available at runtime.

 (defun tclos-run:%finalize-effective-method (effective-method start-index)
  (let ((method-table (effective-method-method-table effective-method))
	(function-table (effective-method-function-table effective-method))
	(next-method (effective-method-next-method-table effective-method))
	(key-table (effective-method-key-table effective-method))
	)
    (setf (effective-method-start effective-method) start-index)
    (macrolet ((copy-table (accessor table)
		 `(setf (,accessor effective-method) (copy-seq ,table))))
      (copy-table effective-method-method-table method-table)
      (copy-table effective-method-function-table function-table)
      (copy-table effective-method-next-method-table next-method)

      ;; Do something here to build the keyword permutation vectors, when
      ;; necessary.  Note that local-methods do not contribute to the
      ;; set of valid keys, and only get a permutation vector when all of
      ;; their keys are valid.

      ;; Do something here to return adjustable tables to free pool for later
      ;; reuse.

      effective-method
      )))

;;; This needs to be available at runtime.

 (defun tclos-run:%make-effective-method (generic-function methods)
  ...
  )

|#
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    The macro DEFINE-METHOD-COMBINATION
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;; Currently, only the short form of DEFINE-METHOD-COMBINATION is supported,
;;; and then only if the operator is a function.  It is defined in terms of the
;;; DEFINE-METHOD-COMBINATION-FUNCTION macro.

(define-translator-macro define-method-combination
        (name &rest stuff &environment env)
  (if (or (endp stuff)
	  (and (symbolp (car stuff))
	       (not (null (car stuff)))))
      (expand-short-form-define-method-combination name stuff env)
      (error "The long form of ~S is not supported by the translator.~@
              Use ~S instead."
	     'define-method-combination
	     'tx:define-method-combination-function)))

(defun parse-short-form-define-method-combination-options (name options)
  (apply #'(lambda (&key documentation
			 identity-with-one-argument
			 (operator name))
	     (values operator identity-with-one-argument documentation))
	 options))

(defun expand-short-form-define-method-combination (name stuff env)
  (multiple-value-bind (operator one-arg-identity doc)
      (parse-short-form-define-method-combination-options name stuff)
    (unless (member (translator-function-information operator env)
		    '(nil :function))
      (error "The short form of ~S is not supported by the translator when~@
              the operator (~S) is not a function.  Use ~S instead."
	     'define-method-combination
	     operator
	     'tx:define-method-combination-function))
    (expand-method-combination-function
       name
       '(&optional (order :most-specific-first))
       `((around (:around))
	 (primary (,name) :order order))
       `(,@(when doc (list doc))
	 (cond ((endp primary)
		(tx:combine-methods (car around) (cdr around)))
	       ,@(when one-arg-identity
		   `(((endp (cdr primary))
		      (if (endp around)
			  (tx:combine-methods (car primary) ())
			  (tx:combine-methods (car around)
					      (append (cdr around)
						      primary))))))
	       (t
		(let ((primary-method
		       (let ((combined
			      (mapcar #'(lambda (method)
					  (tx:combine-methods method ()))
				      primary)))
			 (tx:local-method ()
			   (apply #',operator
				  (mapcar #'(lambda (method)
					      (tx:call-combined-method method))
					  combined))))))
		  (if (endp around)
		      (tx:combine-methods primary-method ())
		      (tx:combine-methods (car around)
					  (append (cdr around)
						  (list primary-method))))))))
       t
       env)))

#|

;;; We could modify the above definition to do something like this, so that
;;; for some number of argument counts we have specialized functions that
;;; produce effective methods which don't cons and don't use apply.  With
;;; some cooperation from the translator we might be able to do even better,
;;; using some sort of macros to only define the C handlers and using a
;;; C array to hold the function pointers.

(tx:define-method-combination-function +
    (&optional (order :most-specific-first))
    ((around (:around))
     (primary (+) :order order))
  (cond ((endp primary)
	 (tx:combine-methods (car around) (cdr around)))
	((endp (cdr primary))
	 (if (endp around)
	     (tx:combine-methods (car primary) ())
	     (tx:combine-methods (car around)
				 (append (cdr around) primary))))
	(t
	 (let ((primary-method
		(funcall (svref #:+-method-combination-functions
				(min 11 (length primary)))
			 primary)))
	   (if (endp around)
	       (tx:combine-methods primary-method ())
	       (tx:combine-methods (car around)
				   (append (cdr around)
					   (list primary-method))))))))

|#

			 

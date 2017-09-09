;;; -*- Mode: Lisp; Package: TCLOSI; Syntax: Common-Lisp -*-
;;;
;;; Optimizing method bodies.
;;; Copyright (C) 1991 Chestnut Software, Inc.  All Rights Reserved.
;;;

(in-package "TCLOSI")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/make-method-body.lisp,v $"
 "$Revision: 1.1 $"
 "$Date: 2006/02/28 21:59:08 $")

;;; There are two kinds of optimizations that need to be performed on method
;;; bodies.  The first is to optimize slot accesses based on knowing the types
;;; of the specialized arguments.  The second is to optimize calls to method
;;; body functions.  These optimizations are implemented by doing a code walk
;;; on the method body.  There are lots of complications.
;;;
;;; The basic idea is to associate a special record with each interesting
;;; binding, and to transform certain forms based on information contained in
;;; these records.  The method body optimization proceeds in two phases.
;;;
;;; 1. Walk the method body, recording the presence of the certain features by
;;;    updating the appropriate binding records.  During this phase, no actual
;;;    transformations on slot access or method body functions are actually
;;;    performed.  The features being recorded are:
;;;
;;;	* References to specialized variables.
;;;
;;;	* Modification of specialized variables, via SETQ and friends.
;;;
;;;	* References to method body functions (CALL-NEXT-METHOD and
;;;       NEXT-METHOD-P). 
;;;
;;;	* Calls to slot access functions with the object argument being a
;;;       specialized variable and the slot name being a constant symbol.
;;;
;;;    This walk is performed with type declarations present for the
;;;    specialized parameter variables.  This is done so that macros will have
;;;    the type information for specialized variables available, and assumes
;;;    that the modification of these variables (which would invalidate the
;;;    automatic generation of the type declarations) is rare.  If any
;;;    modifications of such variables are detected, the resulting expansion is
;;;    invalid, and the original body is rewalked with the automatic type
;;;    declarations for modified specialized variables removed.
;;;
;;; 2. Walk the result of the first walk of the method body, performing
;;;    optimizations on slot accesses and method body function references.
;;;    This pass may be omitted if the first pass failed to detect any
;;;    references to method body functions or slot accesses on specialized
;;;    variables.
;;;
;;;    A complication that arises here is the possibility that there might be
;;;    nested method definitions.  In such a case, because of the multiple
;;;    expansion passes performed, it is necessary when processing for a nested
;;;    method definition to leave references to bindings established by outer
;;;    methods untransformed.
;;;
;;; [An attempt was made to do this with a single pass of the code walker, with
;;; additional passes occuring only if certain assumptions were detected as
;;; being invalid while the walk was being performed (such as there being no
;;; modifications of specialized variables).  However, it turned out to be
;;; extremely complex and not very robust.  For example, it was closely tied to
;;; the specific behavior of the underlying walker when encountering a FUNCALL
;;; form, and did not operate well under certain conditions, with lots of
;;; effort needed to avoid very obscure pitfalls.  It seemed better to fall
;;; back to a less efficient but more easily understood process, with the
;;; intent that at some future date this might be revisited and improved.]
;;;
;;;   I. Optimizing slot accesses.
;;;
;;;    The basic idea here is to associate a SPECIALIZER structure with each
;;;    specialized variable in the environment.  Various pieces of information
;;;    are recorded in the specializer structure, and its contents are used to
;;;    determine when and how to optimize slot accesses. 
;;;
;;;    The protocol used to implement the optimization is to use the generic
;;;    function ESTABLISH-SLOT-OPTIMIZATION-CONTEXT to establish any necessary
;;;    context for the optimizations and then walk the body by calling the
;;;    continuation function supplied as an argument to it.  The walker
;;;    recognizes slot access forms and applies specific optimizer functions to
;;;    the forms when the object being accessed is recognized as a specializer.
;;;    These optimizer functions may record information in the SPECIALIZER
;;;    structure to pass information back to the corresponding
;;;    ESTABLISH-SLOT-OPTIMIZATION-CONTEXT method, so that it can determine
;;;    exactly what context information needs to be wrapped around the body.
;;;
;;;    The basic constraint here is that the specialized variable must not be
;;;    modified within the method body.  If it is, then the class information
;;;    available from the specializer cannot be relied upon for optimizations.
;;;    The first pass of the code walk is responsible for detecting this
;;;    situation and inhibiting slot access optimizations by removing the
;;;    SPECIALIZER record from the environment used by later passes. 
;;;
;;;    This protocol can be extended by defining additional methods on
;;;    ESTABLISH-SLOT-OPTIMIZATION-CONTEXT and the optimizers for the specific
;;;    slot access functions.
;;;
;;;   II. Optimizing method body functions.
;;;
;;;    The basic idea here is to associate a METHOD-BODY-FUNCTION structure
;;;    with each of the method body functions in the environment.  Various
;;;    pieces of information are recorded in this structure and its contents
;;;    are used to determine when and how to optimize references to the
;;;    functions.
;;;
;;;    Note that this mechanism does not need to be extensible unless there is
;;;    a desire to permit definition of additional method body functions.  This
;;;    has not been done, and the current code is somewhat specific to there
;;;    being just CALL-NEXT-METHOD and NEXT-METHOD-P as method body functions.
;;;    Probably coming up with an extensible protocol here would be a good
;;;    thing, as it might very well result in cleaner code, but that hasn't
;;;    been done yet. 
;;;
;;;    There are lots of complications here, due to the need by
;;;    CALL-NEXT-METHOD to capture the original arguments to the function under
;;;    some circumstances, and by CALL-NEXT-METHOD and NEXT-METHOD-P needing to
;;;    close over some of the internal method arguments.  Consing up a
;;;    collection of the original arguments should be avoided whenever
;;;    possible.  For downward calls, the arguments are still on the stack and
;;;    can be referenced through the internal method arguments.  However, when
;;;    there are upward references, the arguments need to be saved off in a
;;;    heap consed collection for access by later calls to the upward function
;;;    references.  In order to do this, state information about whether a form
;;;    is being processed in an upward or downward context is maintained in the
;;;    environment.  By default, references to the FUNCTION special-form are
;;;    processed in an upward context.  If context information is available to
;;;    determine that a function reference is only downward, then the function
;;;    can instead be processed in the current context.  The major complication
;;;    here is that local function bindings may contain references to method
;;;    body functions, and the local function bindings may be either upward or
;;;    downward.  See the walkers for FLET and friends. 
;;;
;;; [Note: There is currently no support for different method call protocols in
;;; CALL-NEXT-METHOD.  This is conceptually a bug, though I don't  really plan
;;; to fix it.  Note that being able to extend the expansion of CALL-METHOD is
;;; insufficient for this, since the method object being called is not
;;; determined until method combination time (and that's in an implementation
;;; that actually supports CALL-METHOD).]


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Detecting nested method definitions
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;; Some of the things that are done in processing a method body are sensitive
;;; to the existance of nested method definitions.  This stuff provides a
;;; mechanism for detecting such.

(defvar *default-method-level* 0)

(defun method-level (env)
  (or (translator-declaration-information 'method-level env)
      *default-method-level*))

(define-translator-declaration method-level (spec env)
  (declare (ignore spec))
  (values ()
	  ()
	  ()
	  `((method-level . ,(1+ (method-level env))))))

(defmacro with-next-method-level ((env-var env) &body body)
  `(let ((,env-var (translator-augment-environment
		     ,env :declare '((method-level)))))
     ,@body))
      

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Closed method arguments
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;; This is similar to the method arguments.  Essentially, we want one closed
;;; method argument for each real method argument, with the initforms of the
;;; closed arguments being the corresponding real method argument.
;;;
;;; However, there is one additional binding indicated here, which is a data
;;; structure which contains all of the arguments received by the
;;; generic-function, and is initialized by a call to copy-method-frame.
;;;
;;; The point of all this is that references to the internal method arguments
;;; reference either the actual internal method parameters or the closed
;;; parameters, depending on whether the reference is at the same function
;;; level or not.

(define-translator-declaration closed-method-arguments (spec env)
  (declare (ignore env))
  (values () () () (list spec)))

(defun closed-method-arguments (env)
  (or (translator-declaration-information 'closed-method-arguments env)
      (error "Not in a method body context.")))

(defun make-closed-method-arguments ()
  (multiple-value-bind (vars decls)
      (make-method-arguments-internal)
    (let ((arglist (make-variable "Method-arguments")))
      (values `(,@vars ,arglist)
	      `((closed-method-arguments ,@vars ,arglist)
		(type list ,arglist)
		(ignorable ,arglist)
		,@decls)))))

(defmacro closed-method-arguments-upward (args) `(fifth ,args))

(define-translator-macro with-closed-method-arguments
        (closed-vars method-args &body body)
  `(let (,@(mapcar #'list closed-vars method-args)
	 (,(closed-method-arguments-upward closed-vars) (copy-method-frame)))
     ,@body))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Binding records
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;; This record is used to track information about bindings.  The slots have
;;; the following meanings: 
;;;
;;; * NAME		The name of the binding this record is associated with.
;;; * METHOD-LEVEL	The method level at which the binding is established.
;;; * FLAGS		An integer used to record various pieces of information
;;;			about the binding as the body is being processed.  Bits
;;;			in the value of this slot represent various conditions,
;;;			with the interpretation dependent on the actual type of
;;;			record. 
;;; * PLIST		A property list used to record various pieces of
;;;			information about the binding as to body is being
;;;			processed.  Exactly what properties might appear is
;;;			dependent on the actual type of record.

(eval-when (compile load eval)
(defstruct (binding-record
	    (:constructor nil)
	    (:copier nil)
	    (:predicate nil))
  (name            nil  :read-only t   )
  (method-level    0    :read-only t   :type (integer 0))
  ;; Flags bits are inverted, with zero meaning true and one meaning false.
  (flags	   -1   :read-only nil :type integer)
  (plist	   nil  :read-only nil :type list)
  )
)

(defun make-binding-record-declaration (declaration-name record)
  (list declaration-name (binding-record-name record) record))

(defun make-binding-record-declarations (declaration-name records)
  (mapcar #'(lambda (record)
	      (make-binding-record-declaration declaration-name record))
	  records))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Specialized variable records
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;; This record is used to track information about specialized variables, so
;;; that heavily optimized slot accesses can be generated within method bodies.
;;; It includes the BINDING-RECORD structure, and provides the following
;;; additional slots:
;;;
;;; * CLASS	    The class of the specialized variable, a class object.
;;;
;;; The FLAGS slot contains bits to indicate the following conditions.
;;;
;;;   * Referenced	The variable was referenced.
;;;   * Modified	The variable was modified.
;;;   * Slot-value	The specified slot access operation was applied to the
;;;   * Slot-boundp	variable.
;;;   * Set-slot-value
;;;   * Slot-makunbound
;;;   * Slot-exists-p

(eval-when (compile load eval)
(defstruct (specializer
	    (:include binding-record)
	    (:constructor %make-specializer (name class method-level))
	    (:copier nil)
	    (:predicate nil))
  (class        nil    :read-only t #| :type class |#)) ;Lucid issues warning!
)
  
(defun make-specializer (name class env)
  (check-type name symbol)
  (setf class (coerce-to-class class t env))
  (%make-specializer name class (method-level env)))

(define-translator-declaration specializer (spec env)
  (declare (ignore env))
  (destructuring-bind (name specializer) (cdr spec)
    (check-type specializer specializer)
    (values `((,name specializer ,specializer))
	    ()
	    ()
	    ())))

(defun make-specializer-declarations (records)
  ;; Include type declarations for specialized variables.
  (nconc (mapcar #'(lambda (record)
		     `(type ,(specializer-class record)
			    ,(specializer-name record)))
		 records)
	 (make-binding-record-declarations 'specializer records)))

;;; Predicate which is true if variable is a specialized variable in env.  If
;;; true, the value returned is the associated specializer record.

(defun specializerp (variable env)
  (and (symbolp variable)
       (values (variable-information-value variable 'specializer env))))

;;; This ought to be done using macrolet, but some implementations don't
;;; make macrolet pass toplevel through to the body.

(defmacro define-specializer-flag (name bits)
  `(progn
     (declaim (inline ,name))
     (defun ,name (record)
       (zerop (logand (specializer-flags record) ,bits)))
     (defsetf ,name (record) (value)
       `(progn
	  (setf (specializer-flags ,record)
		(if ,value
		    (logandc2 (specializer-flags ,record) ,',bits)
		    (logior (specializer-flags ,record) ,',bits)))
	  ,value))))

(define-specializer-flag specializer-referenced             #b1)
(define-specializer-flag specializer-modified              #b10)
(define-specializer-flag specializer-special              #b100)
(define-specializer-flag specializer-slot-value          #b1000)
(define-specializer-flag specializer-slot-boundp        #b10000)
(define-specializer-flag specializer-set-slot-value    #b100000)
(define-specializer-flag specializer-slot-makunbound  #b1000000)
(define-specializer-flag specializer-slot-exists-p   #b10000000)

;;; This ought to be done using macrolet, but some implementations don't
;;; make macrolet pass toplevel through to the body.

(defmacro define-specializer-or-flag (name bits)
  `(progn
     (declaim (inline ,name))
     (defun ,name (record)
       (not (zerop (logandc2 ,bits (specializer-flags record)))))))

(define-specializer-or-flag specializer-used               #b11)
(define-specializer-or-flag specializer-slot-access  #b11111000)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Method body function records
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(eval-when (compile load eval)
(defparameter *method-body-function-names* '(call-next-method next-method-p))

(defparameter *method-body-function-internal-names* nil)
)

(defun method-body-function-name-p (name)
  (member name *method-body-function-names* :test #'eq))

(eval-when (compile load eval)
(defstruct (method-body-function-record
	    (:include binding-record)
	    (:conc-name method-body-function-)
	    (:constructor %make-method-body-function
		  (name method-level method-arguments
			closed-method-arguments upward-method-arguments))
	    (:copier nil)
	    (:predicate nil))
  (method-arguments        nil :read-only t   :type list)
  (upward-method-arguments nil :read-only nil :type symbol)
  (closed-method-arguments nil :read-only nil :type list))
)

(defun make-method-body-function (name env)
  (check-type name (satisfies method-body-function-name-p))
  (let ((closed-args (closed-method-arguments env)))
    (%make-method-body-function name
				(method-level env)
				(method-arguments env)
				closed-args
				(closed-method-arguments-upward closed-args))))

(defun make-method-body-functions (env)
  (mapcar #'(lambda (name)
	      (make-method-body-function name env))
	  *method-body-function-names*))

(define-translator-declaration method-body-function (spec env)
  (declare (ignore env))
  (destructuring-bind (name record) (cdr spec)
    (check-type record method-body-function-record)
    (values ()
	    `((,name method-body-function ,record))
	    ()
	    ())))

(defun make-method-body-function-declarations (records)
  (make-binding-record-declarations 'method-body-function records))

(defun method-body-function-p (name env &optional errorp)
  (or (and (method-body-function-name-p name)
	   (function-information-value name 'method-body-function env))
      (when errorp
	(error "~S is not bound as a method body function." name))))

(defun current-method-body-function-p (name env &optional errorp)
  (let ((record (method-body-function-p name env errorp)))
    (when (and record
	       (= (method-body-function-method-level record)
		  (method-level env)))
      record)))

;;; This ought to be done using macrolet, but some implementations don't
;;; make macrolet pass toplevel through to the body.

(defmacro define-method-body-function-flag (name bits)
  `(progn
     (declaim (inline ,name))
     (defun ,name (record)
       (zerop (logand (method-body-function-flags record) ,bits)))
     (defsetf ,name (record) (value)
       `(progn
	  (setf (method-body-function-flags ,record)
		(if ,value
		    (logandc2 (method-body-function-flags ,record) ,',bits)
		    (logior (method-body-function-flags ,record) ,',bits)))
	  ,value))))


(define-method-body-function-flag method-body-function-referenced          #b1)


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Defining method body walkers
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defvar *method-walk-passes* 2)

(defvar *method-walkers*
  (let ((tables (make-array *method-walk-passes*)))
    (dotimes (index *method-walk-passes* tables)
      (setf (aref tables index) (make-hash-table :test 'equal)))))

(defun get-method-walker (name pass env)
  (declare (ignore env))
  (values (gethash name (aref *method-walkers* (1- pass)))))

(defun set-method-walker (name pass handler)
  (setf (gethash name (aref *method-walkers* (1- pass))) handler))

(defmacro define-method-walker (name pass lambda-list &body body)
  (multiple-value-bind (body declspecs doc)
      (parse-body body t)
    `(progn
       (eval-when (compile)
	 (print-progress-message
	    ,(sformat "Pass ~D method body walker" pass)
	    ',name))
       (eval-when (load eval)
	 (set-method-walker ',name ,pass
			    #'(lambda ,lambda-list
				,@(when doc (list doc))
				(declare ,@declspecs)
				(block ,(body-block-name name) ,@body)))))))

(defun make-method-body-walker (pass)
  (flet ((walk (form env walker)
	   (cond ((symbolp form)
		  (multiple-value-bind (newform macrop)
		      (translator-symbol-macroexpand-1 form env)
		    (declare (ignore newform))
		    (if (not macrop)
			(walk-method-symbol form env walker pass)
			(values form nil))))
		 ((atom form) (walk-method-atom form env walker pass))
		 ((lambda-expression-p (car form))
		  (walk-method-lambda form env walker pass))
		 (t
		  (let ((local-walker (get-method-walker (car form) pass env)))
		    (if local-walker
			(funcall local-walker form env walker)
			(walk-method-call form env walker pass)))))))
    #'walk))

(defvar *symbol-walker-name* (make-symbol "symbol-walker"))
(defvar *atom-walker-name* (make-symbol "atom-walker"))
(defvar *lambda-walker-name* (make-symbol "lambda-walker"))
(defvar *call-walker-name* (make-symbol "call-walker"))

(defun walk-method-symbol (symbol env walker pass)
  (let ((local-walker (get-method-walker *symbol-walker-name* pass env)))
    (if local-walker
	(funcall local-walker symbol env walker)
	(values symbol nil))))

(defun walk-method-atom (atom env walker pass)
  (let ((local-walker (get-method-walker *atom-walker-name* pass env)))
    (if local-walker
	(funcall local-walker atom env walker)
	(values atom nil))))

(defun walk-method-lambda (form env walker pass)
  (let ((local-walker (get-method-walker *lambda-walker-name* pass env)))
    (if local-walker
	(funcall local-walker form env walker)
	(values form nil))))

(defun walk-method-call (form env walker pass)
  (let ((local-walker (get-method-walker *call-walker-name* pass env)))
    (if local-walker
	(funcall local-walker form env walker)
	(values form nil))))

;;; Helper function for slot access processing.
;;; This function assumes that form has already been walked.
;;; It removes THE forms (recording their presence and the specified type),
;;; resolving the form down to something which is not a THE form, returning the
;;; resolved form.  A second value is returned which is a type specifier
;;; combining any types specified by THE forms that were encountered.

(defun strip-the (form &optional env &aux (type t))
  (loop
    (if (or (atom form) (not (eq (first form) 'the)))
	(return (values form type))
	(progn
	  (setf type (and-types type (second form) env))
	  (setf form (third form))))))

;;; Helper function.
;;; This function assumes that form has already been walked.
;;; It attempts to determine the type of the form, based on declarations and
;;; knowledge of forms.

(defun form-type (form &optional env)
  (multiple-value-bind (form type)
      (strip-the form env)
    (setf type (single-value-type type env))
    (cond ((symbolp form) (and-types type (variable-type form env) env))
	  ;; *** This could be made lots smarter, by doing a code walk.
	  (t type))))

;;; Wrap the form with a THE form using the specified type specifier.

(defun wrap-the (form type)
  (if (eq type T) form
      `(the ,type ,form)))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Pass 1 method body walk
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(set-method-walker *symbol-walker-name* 1
		   #'(lambda (symbol env walker)
		       (declare (ignore walker))
		       (let ((specializer (specializerp symbol env)))
			 (when specializer
			   (setf (specializer-referenced specializer) t))
			 (values symbol nil))))

(macrolet ((define-slot-access-walker (name specializer-reference)
	     `(define-method-walker ,name 1 (form env walker)
		(let* ((args (walk:walk-arguments (cdr form) env walker))
		       (instance (strip-the (car args) env))
		       (specializer (and (symbolp instance)
					 (specializerp instance env))))
		  (when specializer
		    (setf (,specializer-reference specializer) t))
		  (values (cons ',name args) t)))))

  (define-slot-access-walker TRUN:SET-SLOT-VALUE specializer-set-slot-value)
  (define-slot-access-walker SLOT-BOUNDP specializer-slot-boundp)
  (define-slot-access-walker SLOT-EXISTS-P specializer-slot-exists-p)
  (define-slot-access-walker SLOT-MAKUNBOUND specializer-slot-makunbound)
  (define-slot-access-walker SLOT-VALUE specializer-slot-value)

  )

(macrolet ((define-method-body-function-walker (name)
	     `(define-method-walker ,name 1 (form env walker)
		(let ((args (walk:walk-arguments (cdr form) env walker))
		      (record (method-body-function-p ',name env)))
		  (when record
		    (setf (method-body-function-referenced record) t))
		  (values (cons ',name args) t)))))

  (define-method-body-function-walker CALL-NEXT-METHOD)
  (define-method-body-function-walker NEXT-METHOD-P)

  )

(macrolet ((define-generic-function-walker (name)
	     `(define-method-walker ,name 1 (form env walker)
	        (declare (ignore walker))
	        (multiple-value-bind (newform macrop)
		    (translator-macroexpand-1 form env)
		  (if macrop
		      (values newform nil)
		      (error "Translator bug: Expected ~S to be a macro."
			     ',name))))))

  ;; These are all implemented as macros by the translator.  Define walkers
  ;; that force the macroexpansion of the form and then walk the result.

  (define-generic-function-walker GENERIC-FUNCTION)
  (define-generic-function-walker GENERIC-FLET)
  (define-generic-function-walker GENERIC-LABELS)
  
  )

(define-method-walker FUNCTION 1 (form env walker)
  (declare (ignore walker))
  (destructuring-bind (ignore function) form
    (declare (ignore ignore))
    (and (not (lambda-expression-p function))
	 (setf function (method-body-function-p function env))
	 (setf (method-body-function-referenced function) t))
    (values form nil)))

(labels ((process-setq (form env)
	   (do ()
	       ((not (symbolp form)))
	     (multiple-value-bind (newform macrop)
		 (translator-symbol-macroexpand-1 form env)
	       (if macrop
		   (setf form newform)
		   (let ((specializer (specializerp form env)))
		     (when specializer
		       (setf (specializer-modified specializer) t))
		     (return nil))))))
	 (process-setq-pairs (pairs env)
	   (do ((pairs pairs (cdr pairs)))
	       ((endp pairs))
	     (process-setq (pop pairs) env))))

  (define-method-walker SETQ 1 (form env walker)
    (declare (ignore walker))
    (process-setq-pairs (cdr form) env)
    (values form nil))

  (define-method-walker PSETQ 1 (form env walker)
    (declare (ignore walker))
    (process-setq-pairs (cdr form) env)
    (values form nil))

  (define-method-walker MULTIPLE-VALUE-SETQ 1 (form env walker)
    (declare (ignore walker))
    (dolist (place (cadr form) (values form nil))
      (process-setq place env)))

  )


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Pass 2 method body walk
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;; Remember that subforms have already been expanded, so walker functions for
;;; this pass do not need to walk subforms in order to expand and simplify
;;; them before examining them more closely.

;;; UPWARD-CONTEXT
;;;
;;; This declaration is used to indicate that the forms may be referenced in
;;; an upward fashion.  Some optimization methods may conditionalize their
;;; results depending on whether the form is referenced upward (and therefore
;;; may require closures over certain bindings) or only downward.

(define-translator-declaration upward-context (spec env)
  (declare (ignore spec env))
  (values ()
	  ()
	  ()
	  '((upward-context . t))))

(defun upward-context-p (env)
  (translator-declaration-information 'upward-context env))

(defun make-upward-context (env)
  (translator-augment-environment env :declare '((upward-context))))

(defmacro with-upward-context ((env-var env) &body body)
  `(let ((,env-var (make-upward-context ,env)))
     ,@body))

(defun upward-reference-p (name env &optional (function-info nil infop))
  (when (upward-context-p env)
    (unless infop
      (multiple-value-bind (usage boundp info)
	  (translator-function-information name env)
	(declare (ignore usage boundp))
	(setf function-info info)))
    ;; Believe a dynamic-extent declaration on the function.
    (not (cdr (assoc 'dynamic-extent function-info)))))

;;; UPWARD-REFERENCE
;;;
;;; This declaration is used to indicate that a function was referenced in an
;;; upward context.  This is used when walking forms which establish local
;;; function bindings, so that it can be determined whether to walk the bodies
;;; of the bindings in an upward or downward context.

(define-translator-declaration upward-reference (spec env)
  (declare (ignore env))
  (destructuring-bind (name) (cdr spec)
    (values ()
	    (list (list name 'upward-reference (list nil)))
	    ()
	    ())))

(defun function-referenced-upward (name env)
  (multiple-value-bind (usage boundp info)
      (translator-function-information name env)
    (declare (ignore usage boundp))
    (car (cdr (assoc 'upward-reference info)))))

(defun notice-upward-reference (name env)
  (multiple-value-bind (usage boundp info)
      (translator-function-information name env)
    (declare (ignore usage boundp))
    (let ((place (assoc 'upward-reference info)))
      ;; If no upward-reference record, then not bound in the scope of walk
      ;; so don't care that it is referenced upward since its body cannot
      ;; reference anything this stuff is concerned with.
      (when place (setf (car place) t)))))

(defmacro noticing-upward-references ((env-var env names) &body body)
  `(let ((,env-var (translator-augment-environment
		     ,env
		     :declare (mapcar #'(lambda (name)
					  `(upward-reference ,name))
				      ,names))))
     ,@body))

;;; The pass 2 walkers.

(macrolet ((define-method-body-function-walker (name)
	     `(define-method-walker ,name 2 (form env walker)
		(let ((record (current-method-body-function-p ',name env)))
		  (if (null record)
		      (values form nil)
		      (optimize-method-body-function ',name
						     record
						     form
						     env
						     walker)))))
	   (define-all-method-body-function-walkers ()
	     `(progn
		,@(mapcar #'(lambda (name)
			      `(define-method-body-function-walker ,name))
			  *method-body-function-names*))))
  (define-all-method-body-function-walkers))

(flet ((optimizable-slot-access (form env)
	 (destructuring-bind (instance slot-name &rest args) (cdr form)
	   (let ((instance-temp (strip-the instance env)))
	     (when (and (symbolp instance-temp)
			(translator-constantp slot-name env))
	       (multiple-value-bind (value therep)
		   (translator-constant-value slot-name env)
		 (let ((specializer (specializerp instance-temp env)))
		   (when (and specializer therep
			      (= (specializer-method-level specializer)
				 (method-level env)))
		     (let ((class (specializer-class specializer)))
		       (values
			    class
			    (tclosx:find-effective-slot-definition class value)
			    (list* (car form) instance-temp slot-name args)
			    ))))))))))

  (macrolet ((define-slot-access-walker (name optimizer)
	       `(define-method-walker ,name 2 (form env walker)
		  (declare (ignore walker))
		  (if (function-notinline-p ',name env)
		      (values form nil)
		      (multiple-value-bind (class slotd new-form)
			  (optimizable-slot-access form env)
			(if (or (null class) (null slotd))
			    (values form nil)
			    (let ((optimized
				    (,optimizer class slotd new-form env)))
			      (if (eq optimized new-form)
				  (values form nil)
				  (values optimized nil)))))))))

    (define-slot-access-walker TRUN:SET-SLOT-VALUE optimize-set-slot-value)
    (define-slot-access-walker SLOT-BOUNDP optimize-slot-boundp)
    (define-slot-access-walker SLOT-EXISTS-P optimize-slot-exists-p)
    (define-slot-access-walker SLOT-MAKUNBOUND optimize-slot-makunbound)
    (define-slot-access-walker SLOT-VALUE optimize-slot-value)

    ))

(set-method-walker *call-walker-name* 2
		   #'(lambda (form env walker)
		       (declare (ignore walker))
		       (let ((name (car form)))
			 (when (upward-reference-p name env)
			   (notice-upward-reference name env))
			 (values form nil))))

(flet ((walk-function-reference (form env walker direction)
	 (let ((name (second form)))
	   ;; If currently in an upward context, local direction doesn't matter
	   ;; and should always walk subforms in upward direction.
	   (let ((walk-env (if (or (upward-context-p env)
				   (eq direction :downward))
			       env
			       (make-upward-context env))))
	     (if (lambda-expression-p name)
		 (values `(function ,(walk:walk-function name walk-env walker))
			 t)
		 (let ((record (current-method-body-function-p name walk-env)))
		   (if (null record)
		       (let ((name (car form)))
			 (when (upward-reference-p name walk-env)
			   (notice-upward-reference name walk-env))
			 (values form nil))
		       (efunctuate-method-body-function name
							record
							form
							walk-env
							walker))))))))

  (define-method-walker FUNCTION 2 (form env walker)
    (walk-function-reference form env walker :upward))

  (flet ((walk-call (form env walker)
	   (let ((function (cadr form)))
	     (if (and (consp function)
		      (eq (car function) 'function))
		 (values (list* (car form)
				(walk-function-reference function
							 env
							 walker
							 :downward)
				(walk:walk-arguments (cddr form)
						     env
						     walker))
			 t)
		 (values form nil)))))

    (define-method-walker FUNCALL 2 (form env walker)
      (walk-call form env walker))

    (define-method-walker APPLY 2 (form env walker)
      (walk-call form env walker))

    (define-method-walker MULTIPLE-VALUE-CALL 2 (form env walker)
      (walk-call form env walker))

    ))

(define-method-walker FLET 2 (form env walker)
  (if (upward-context-p env)
      ;; If already in an upward context, don't need to do anything special.
      ;; Normal walk of the form will do everything that is needed.
      (values form nil)
      (destructuring-bind (bindings &body body) (cdr form)
	(multiple-value-bind (body declspecs)
	    (parse-body body nil)
	  (let ((names (mapcar #'car bindings)))
	    (noticing-upward-references (f-env env names)
	      (let* ((b-env (translator-augment-environment
			      f-env :declare declspecs))
		     ;; Walk the body, noticing any upward references to any of
		     ;; the functions being bound.
		     (body (walk:walk-progn body b-env walker)))
		(with-upward-context (u-env env)
		  (flet ((walk-binding (binding)
			   (if (function-referenced-upward (car binding) f-env)
			       (walk:walk-function binding u-env walker)
			       (walk:walk-function binding env walker))))
		    ;; Now walk the bodies of the bindings, in either an
		    ;; upward or downward context, depending on whether it was
		    ;; referenced upward or not.
		    (values `(flet ,(mapcar #'walk-binding bindings)
			       ,@(when declspecs `((declare ,@declspecs)))
			       ,@body)
			    t))))))))))

;;; This code depends on it being ok to walk a form multiple times during the
;;; third pass.  This can happen due to detecting an upward reference to one of
;;; the bound names after the associated body has been walked in a downward
;;; context.

(define-method-walker LABELS 2 (form env walker)
  (if (upward-context-p env)
      ;; If already in an upward context, don't need to do anything special.
      ;; Normal walk of the form will do everything that is needed.
      (values form nil)
      (destructuring-bind (bindings &body body) (cdr form)
	(multiple-value-bind (body declspecs)
	    (parse-body body nil)
	  (let ((names (mapcar #'car bindings)))
	    (multiple-value-bind (bound free)
		(split-declarations-for-functions names env declspecs)
	      (let ((f-env (translator-augment-environment env
							   :function names
							   :declare bound)))
		(noticing-upward-references (f-env f-env names)
		  (let* ((b-env (translator-augment-environment f-env
								:declare free))
			 (body (walk:walk-progn body b-env walker))
			 ;; Entries in upward are simple function bindings.
			 (upward ())
			 ;; Entries in downward are (name walked . unwalked)
			 (downward ())
			 (pending (copy-list bindings)))
		    (with-upward-context (u-env f-env)
		      (flet ((upward-binding-p (binding)
			       (function-referenced-upward (car binding)
							   f-env))
			     (walk-downward (binding)
			       (push (list* (car binding)
					    (walk:walk-function binding
								f-env
								walker)
					    binding)
				     downward))
			     (walk-upward (binding)
			       (push (walk:walk-function binding u-env walker)
				     upward)))
		        (loop
			  ;; Loop until there are no pending bindings and none
			  ;; of the bindings that have been walked in a
			  ;; downward context have since been noticed in an
			  ;; upward context.
			  (when (endp pending)
			    ;; No more bindings pending.  Look for invalidated
			    ;; downward bindings.
			    (let ((really-downward ()))
			      (do ()
				  ((endp downward))
				(let ((next (pop downward)))
				  (if (upward-binding-p next)
				      ;; Noticed upward reference after walking
				      ;; it downward, so rewalk.
				      (push (cddr next) pending)
				      ;; Still downward.
				      (push next really-downward))))
			      ;; Update downward to only include those bindings
			      ;; that have been walked downward and not
			      ;; invalidated.
			      (setf downward really-downward)
			      ;; If still nothing pending, then with loop.
			      (when (endp pending) (return))))
			  ;; Search the pending list for a binding which is
			  ;; referenced upward.
			  (let ((next (find-if #'upward-binding-p pending)))
			    (if (null next)
				;; No upward references in pending list, so
				;; walk the next pending binding in a downward
				;; context and add a record to the downward
				;; list.
				(walk-downward (pop pending))
				(progn
				  ;; Remove the binding entry from pending, and
				  ;; walk it in an upward context, adding the
				  ;; result to the list of upward bindings.
				  (setf pending (delete next pending))
				  (walk-upward next)))))
			;; Finished loop (finally).
			(values `(labels (,@upward
					  ,@(mapcar #'cadr downward))
				   ,@(when declspecs `((declare ,@declspecs)))
				   ,@body)
				t))))))))))))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Optimizing method-body functions
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;; There are 5 `bits' of information that are used to determine what name to
;;; transform a reference to a method-body function into.  These bits are:
;;;
;;; * Arguments		If the function might be called with arguments, this is
;;;			true.  Under some circumstances it may not be possible
;;;			to determine for certain whether arguments are going to
;;;			be passed or not, in which case this is assumed to be
;;;			true.
;;; * Upward		True if the reference is in an (potentially) upward
;;;			context.
;;; * Safety		True if the point of reference is `safe', ie. the
;;;			SAFETY optimization quality is at its highest level.
;;; * Notinline		True if the function is declared NOTINLINE at the point
;;;			of reference.
;;; * Dynamic-extent	True if the function is declared to have dynamic
;;;			extent.

(defun method-body-function-variable (record name)
  (or (cdr (assoc name (method-body-function-transformations record)))
      (error "~S is not a bound method-body function." name)))

(defun method-body-function-transformations (record)
  (getf (method-body-function-plist record) 'transforms))

(defsetf method-body-function-transformations (record) (value)
  `(setf (getf (method-body-function-plist ,record) 'transforms) ,value))

(defun optimize-method-body-function (name record form env walker)
  (transform-method-body-function (method-body-function-optimizer name)
				  record
				  form
				  env
				  walker))


(defun efunctuate-method-body-function (name record form env walker)
  (transform-method-body-function (method-body-function-efunctuator name)
				  record
				  form
				  env
				  walker))

(defun transform-method-body-function (handler record form env walker)
  (funcall handler record form env walker))

(defvar *method-body-function-transformations* ())

(defmacro add-transformation (name transformation)
  `(let ((entry (assoc ',name *method-body-function-transformations*)))
     (when (null entry)
       (setf entry (list ',name))
       (push entry *method-body-function-transformations*))
     (push ',transformation (cdr entry))))

(defvar *method-body-function-variable-names* ())

(defun make-method-body-function-variable-name (name)
  (setf name (string name))
  (with-output-to-string (stream)
    (do ((p 0))
	((null (setf p (position-if #'alphanumericp name :start p))))
      (write-char (char name p) stream)
      (unless (setf p (position-if (complement #'alphanumericp) name :start p))
	(return)))
    (write-string "-fn" stream)))

(defun make-method-body-function-bindings (records env)
  (let ((bindings ())
	(binding-decls ()))
    (dolist (record records)
      (let* ((name (method-body-function-name record))
	     (transformations
	      (mapcar
	       #'(lambda (name)
		   (let ((vname
			  (cdr (assoc name
				      *method-body-function-variable-names*))))
		     (when (null vname)
		       (setf vname
			     (make-method-body-function-variable-name name))
		       (push (cons name vname)
			     *method-body-function-variable-names*))
		     (cons name (make-variable vname))))
		   (cdr (assoc name *method-body-function-transformations*)))))
	(setf (method-body-function-transformations record) transformations)
	(dolist (transform transformations)
	  (multiple-value-bind (binding decls)
	      (funcall (method-body-function-constructor (car transform))
		       record
		       env)
	    (push binding bindings)
	    (setf binding-decls (append decls binding-decls))))))
    (values bindings binding-decls)))

(defvar *method-body-function-optimizers* ())
(defvar *method-body-function-efunctuators* ())
(defvar *method-body-function-constructors* ())

(defun method-body-function-optimizer (name)
  (or (cdr (assoc name *method-body-function-optimizers*))
      (error "Optimizer missing for ~S." name)))

(defun method-body-function-efunctuator (name)
  (or (cdr (assoc name *method-body-function-efunctuators*))
      (error "Reference generator missing for ~S." name)))

(defun method-body-function-constructor (name)
  (or (cdr (assoc name *method-body-function-constructors*))
      (error "Binding constructor missing for ~S." name)))

(defmacro define-method-body-function (name type lambda-list &body body)
  (let ((entry (gensym))
	(list (ecase type
		(:optimize '*method-body-function-optimizers*)
		(:function '*method-body-function-efunctuators*)
		(:construct '*method-body-function-constructors*))))
    (multiple-value-bind (body declspecs doc)
	(parse-body body t)
      (declare (ignore doc))
      `(progn
	 (eval-when (compile)
	   (print-progress-message
	     ,(sformat "Method-body function ~A"
		      (case type
			(:optimize "optimizer")
			(:function "reference generator")
			(:construct "binding generator")))
	     ',name))
	 (let ((,entry (assoc ',name ,list)))
	   (when (null ,entry)
	     (setf ,entry (list ',name))
	     (push ,entry ,list))
	   (setf (cdr ,entry)
		 #'(lambda ,lambda-list
		     (declare ,@declspecs)
		     (block ,(body-block-name name) ,@body)))
	   ',name)))))

;;; NEXT-METHOD-P =>
;;;
;;;   NEXT-METHOD-P
;;;	Used if declared NOTINLINE or might be called with arguments.
;;;
;;;   NEXT-METHOD-P-INLINE
;;;	Replaces NEXT-METHOD-P if in the CAR of the form and no arguments are
;;;	present.  This `function' is really a translator special-form.  The
;;;	calling form references both the normal and closed bindings of the
;;;	effective method and the method index.  The special-form handler
;;;	determines which set of bindings to reference to get the arguments to
;;;	pass to the actual runtime function that implements this function.  It
;;;	basically transforms into a call to EFFECTIVE-METHOD-NEXT-METHOD-P,
;;;	with the appropriate choice of variables.
;;;
;;; Note that there is no specialization of NEXT-METHOD-P based on SAFETY.

(pushnew 'NEXT-METHOD-P *method-body-function-internal-names*)

(define-method-body-function next-method-p :function (record form env walker)
  (declare (ignore form env walker))
  (values (method-body-function-variable record 'next-method-p) nil))

(define-method-body-function next-method-p :optimize (record form env walker)
  (declare (ignore walker))
  (multiple-value-bind (usage boundp info)
      (translator-function-information 'next-method-p env)
    (declare (ignore usage boundp))
    (if (or (cdr form) (eq (cdr (assoc 'inline info)) 'notinline))
	(values `(funcall ,(method-body-function-variable record
			                                  'next-method-p)
		          ,@(cdr form))
		nil)
	(let ((method-args (method-body-function-method-arguments record))
	      (closed-args
	        (method-body-function-closed-method-arguments record)))
	  (values `(next-method-p-inline
		     ,(method-arguments-effective-method method-args)
		     ,(method-arguments-method-index method-args)
		     ,(method-arguments-effective-method closed-args)
		     ,(method-arguments-method-index closed-args))
		  nil)))))

(add-transformation next-method-p next-method-p)

(define-method-body-function next-method-p :construct (record env)
  (declare (ignore env))
  (let ((method-args (method-body-function-method-arguments record))
	(variable (method-body-function-variable record 'next-method-p)))
    (values `(,variable (tclos-run:%make-next-method-p
			     ,(method-arguments-effective-method method-args)
			     ,(method-arguments-method-index method-args)))
	    `((ignorable ,variable)
	      (type (function () t) ,variable)))))

;; (next-method-p ()
;;   (tclos-run:%next-method-p method index))

(deftranslate next-method-p-inline (cm index closed-cm closed-index)
  (timpl::re-translate-form
    (if (timpl::variable-bound-at-current-function-level cm)
	`(tclos-run:%next-method-p ,cm ,index)
	`(tclos-run:%next-method-p ,closed-cm ,closed-index))))

(define-internal-function next-method-p-inline
      (cm index closed-cm closed-index))

;;; CALL-NEXT-METHOD =>
;;;
;;;   CALL-NEXT-METHOD
;;;	Used if declared NOTINLINE, or might be called with arguments and the
;;;	point of reference is SAFE.  The latter permits checking for a change
;;;	in the set of applicable methods.  This function is a closure over the
;;;	closed bindings of the effective method and method index and the list
;;;	of actual method arguments.
;;;
;;;   CALL-NEXT-METHOD-UPWARD
;;;	Replaces CALL-NEXT-METHOD if efunctuated in a potentially upward
;;;	context.  This function is a closure over the closed bindings of the
;;;	effective method and method index and the list of actual method
;;;	arguments.  It is identical to CALL-NEXT-METHOD except that the
;;;	checking for a change in the set of applicable methods is elided.
;;;
;;;   CALL-NEXT-METHOD-UPWARD-ARGUMENTS
;;;	Replaces CALL-NEXT-METHOD if in the CAR of the form in a potentially
;;;	upward context and there are arguments supplied in the call.  This
;;;	global function is variadic.  It takes the effective method, the method
;;;	index, and the arguments supplied in the call.  It does not check for a
;;;	change in the set of applicable methods.  The calling form references
;;;	the closed bindings for the effective method and the method index.
;;;
;;;   CALL-NEXT-METHOD-UPWARD-NO-ARGUMENTS
;;;	Replaces CALL-NEXT-METHOD if in the CAR of the form in a potentially
;;;	upward context without arguments.  This global function takes as
;;;	arguments the effective-method, the method index, an upwardly
;;;	referenced copy of the argument frame, and the argument quantity.  It
;;;	does not check for a change in the set of applicable methods, since
;;;	such a check is unnecessary.  The calling form references the closed
;;;	bindings of the argument variables.
;;;
;;;   CALL-NEXT-METHOD-DOWNWARD
;;;	Replaces CALL-NEXT-METHOD if efunctuated in a downward context.  This
;;;	function is a closure over the closed bindings of the effective method,
;;;	method index, argument pointer, and argument count.  It is identical to
;;;	CALL-NEXT-METHOD-UPWARD-FUNCTION, except that it assumes that the
;;;	arguments are already on the stack.
;;;
;;;	[Note: If the translator does not support closures over unboxed values,
;;;	then rather than taking the closed frame and argq, this should take the
;;;	closed list of arguments, in which case it is completely identical to
;;;	the function CALL-NEXT-METHOD-UPWARD, and perhaps a name change should
;;;	occur.]
;;;
;;;   CALL-NEXT-METHOD-DOWNWARD-ARGUMENTS
;;;	Replaces CALL-NEXT-METHOD if in the CAR of the form in a downward
;;;	context with arguments.  This `function' is really a translator
;;;	special-form.  The calling form references both the normal and closed
;;;	bindings for the effective method and the method index, plus the
;;;	arguments to the call.  The special-form handler determines which set
;;;	of bindings to reference to get the arguments to pass to the actual
;;;	runtime function that implements this function.  It basically
;;;	transforms into a call to CALL-NEXT-METHOD-ARGUMENTS, with the
;;;	appropriate choice of effective-method and method-index variables.
;;;	
;;;   CALL-NEXT-METHOD-DOWNWARD-NO-ARGUMENTS
;;;	Replaces CALL-NEXT-METHOD if called in a downward context without
;;;	arguments.  This `function' is really a translator special-form.  The
;;;	calling form references both the normal and closed bindings for the
;;;	effective method, the method index, the argument stack pointer, and the
;;;	argument quantity.  The special-form handler determines which set of
;;;	bindings to reference to get the arguments to pass to the actual
;;;	runtime function that implements this function.  It basically
;;;	transforms into a call to EFFECTIVE-METHOD-CALL-NEXT-METHOD, with the
;;;	appropriate choice of variables.

(pushnew 'CALL-NEXT-METHOD *method-body-function-internal-names*)
(pushnew 'CALL-NEXT-METHOD-UPWARD *method-body-function-internal-names*)
(pushnew 'CALL-NEXT-METHOD-DOWNWARD *method-body-function-internal-names*)

(define-method-body-function call-next-method :function
      (record form env walker)
  (declare (ignore form walker))
  (multiple-value-bind (usage boundp info)
      (translator-function-information 'call-next-method env)
    (declare (ignore usage boundp))
    (let ((name (cond ((or (eq (cdr (assoc 'inline info)) 'notinline)
			   (safe-code-p env))
		       'call-next-method)
		      ((upward-reference-p 'call-next-method env info)
		       'call-next-method-upward)
		      (t
		       'call-next-method-downward))))
      (values (method-body-function-variable record name) nil))))

(define-method-body-function call-next-method :optimize
        (record form env walker)
  (declare (ignore walker))
  (multiple-value-bind (usage boundp info)
      (translator-function-information 'call-next-method env)
    (declare (ignore usage boundp))
    (if (or (eq (cdr (assoc 'inline info)) 'notinline)
	    (and (cdr form) (safe-code-p env)))
	(values `(funcall ,(method-body-function-variable record
			                                  'call-next-method)
		          ,@(cdr form))
		nil)
	(let* ((method-args (method-body-function-method-arguments record))
	       (closed-args
	         (method-body-function-closed-method-arguments record))
	       (closed-cm (method-arguments-effective-method closed-args))
	       (closed-index (method-arguments-method-index closed-args))
	       (closed-argq (method-arguments-argq closed-args))
	       (closed-upward (closed-method-arguments-upward closed-args)))
	  (values
	   (cond ((upward-reference-p 'call-next-method env info)
		  (if (cdr form)
		      `(tclos-run:%call-next-method-arguments
			    ,(+ 2 (length (cdr form)))
			    ,closed-cm ,closed-index ,@(cdr form))
		      `(tclos-run:%call-next-method
			    ,closed-cm
			    ,closed-index
			    ,closed-upward
			    ,closed-argq)))
		 ((cdr form)
		  `(call-next-method-downward-arguments
		     ,(method-arguments-effective-method method-args)
		     ,(method-arguments-method-index method-args)
		     ,closed-cm
		     ,closed-index
		     ,@(cdr form)))
		 (t
		  `(call-next-method-downward-no-arguments
		     ,@method-args
		     ,closed-cm
		     ,closed-index
		     ,(method-arguments-frame closed-args)
		     ,closed-argq)))
	   nil)))))

(add-transformation call-next-method call-next-method-downward)

(define-method-body-function call-next-method-downward :construct (record env)
  (declare (ignore env))
  (let ((method-args (method-body-function-method-arguments record))
	(variable (method-body-function-variable record
						 'call-next-method-downward)))
    (values `(,variable (tclos-run:%make-call-next-method-unsafe
			     ,(method-arguments-effective-method method-args)
			     ,(method-arguments-method-index method-args)
			     ,(method-arguments-frame method-args)
			     ,(method-arguments-argq method-args)))
	    `((ignorable ,variable)
	      (type (function (&rest t) t) ,variable)
	      (dynamic-extent ,variable)))))

(add-transformation call-next-method call-next-method-upward)

(define-method-body-function call-next-method-upward :construct (record env)
  (declare (ignore env))
  (let ((method-args (method-body-function-method-arguments record))
	(upward-frame (method-body-function-upward-method-arguments record))
	(variable (method-body-function-variable record
						 'call-next-method-upward)))
    (values `(,variable (tclos-run:%make-call-next-method-unsafe
			     ,(method-arguments-effective-method method-args)
			     ,(method-arguments-method-index method-args)
			     ,upward-frame
			     ,(method-arguments-argq method-args)))
	    `((ignorable ,variable)
	      (type (function (&rest t) t) ,variable)))))

(add-transformation call-next-method call-next-method)

(define-method-body-function call-next-method :construct (record env)
  (declare (ignore env))
  (let ((method-args (method-body-function-method-arguments record))
	(upward-frame (method-body-function-upward-method-arguments record))
	(variable (method-body-function-variable record 'call-next-method)))
    (values `(,variable (tclos-run:%make-call-next-method-safe
			     ,(method-arguments-effective-method method-args)
			     ,(method-arguments-method-index method-args)
			     ,upward-frame
			     ,(method-arguments-argq method-args)))
	    `((ignorable ,variable)
	      (type (function (&rest t) t) ,variable)))))

(deftranslate call-next-method-downward-arguments
	(cm index closed-cm closed-index &rest arguments)
  (timpl::re-translate-form
    `(tclos-run:%call-next-method-arguments
          ,(+ 2 (length arguments))
          ,@(if (timpl::variable-bound-at-current-function-level cm)
		(list cm index)
		(list closed-cm closed-index))
          ,@arguments)))

(deftranslate call-next-method-downward-no-arguments
	(cm index frame argq closed-cm closed-index closed-frame closed-argq)
  (timpl::re-translate-form
    (if (timpl::variable-bound-at-current-function-level cm)
	`(tclos-run:%call-next-method ,cm ,index ,frame ,argq)
	`(tclos-run:%call-next-method ,closed-cm
				      ,closed-index
				      ,closed-frame
				      ,closed-argq))))

(define-internal-function call-next-method-downward-arguments
      (cm index closed-cm closed-index &rest arguments))

(define-internal-function call-next-method-downward-no-arguments
      (cm index frame argq closed-cm closed-index closed-frame closed-argq))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Parsing specialized lambda-lists
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;; There are three things that need to be computed from a specialized
;;; lambda-list:
;;;
;;; 1. The unspecialized lambda-list.
;;; 2. The list of specializers, with T included where no explicit specializer
;;;    was specified for a required parameter.
;;; 3. An indication of which required parameter were actually specialized.
;;;    This is needed so that the parameters which were explicitly specialized
;;;    can be setup in such a way that a compiler warning does not occur if the
;;;    body of the method does not refer to it, as per 88-002R p.2-40.
;;;
;;; The function parse-specialized-lambda-list takes a specialized lambda-list
;;; and returns three values, the unspecialized lambda-list, the list of
;;; specializers, and a list whose entries correspond to the required parameter
;;; and are true if the parameter was explicitly specialized and false if not.

(defun parse-specialized-lambda-list (specialized-lambda-list)
  (let ((required ())
	(specializers ())
	(specialized ()))
    (loop
      (if (endp specialized-lambda-list)
	  (return)
	  (let ((next (pop specialized-lambda-list)))
	    (etypecase next
	      (symbol
	       (if (lambda-keyword-p next)
		   (return (push next specialized-lambda-list))
		   (progn
		     (push next required)
		     (push t specializers)
		     (push nil specialized))))
	      (cons
	       (push (car next) required)
	       (let ((specializer (cadr next)))
		 (cond ((atom specializer)
			(push specializer specializers))
		       ((not (valid-specializer-p specializer))
			(warn "Ignoring invalid specializer ~S." specializer)
			(push t specializers))
		       (t
			(push specializer specializers))))
	       (push t specialized))
	      ))))
    (values (nreconc required specialized-lambda-list)
	    (nreverse specializers)
	    (nreverse specialized))))

(defun extract-specializer-names (specialized-lambda-list)
  (nth-value 1 (parse-specialized-lambda-list specialized-lambda-list)))

(defun extract-lambda-list (specialized-lambda-list)
  (values (parse-specialized-lambda-list specialized-lambda-list)))

;;; Encoded lambda list information
;;;
;;; Some of the lambda-list information gets encoded into a more compact
;;; format.  This makes it easier to process when performing congruency checks
;;; and the like, and also provides a way to elide the actual lambda-lists at
;;; runtime while still providing the necessary information.

(defstruct (encoded-lambda-list
	    (:constructor %make-encoded-lambda-list)
	    )
  (required 0 :type fixnum :read-only t)
  (positional 0 :type fixnum :read-only t)
  (bits 0 :type fixnum :read-only t)
  (keys nil :type list :read-only t))

(defconstant encoded-lambda-list-non-positional-mask  #x1)
(defconstant encoded-lambda-list-key-mask             #x2)
(defconstant encoded-lambda-list-alwky-mask           #x4)

(defmacro encoded-lambda-list-non-positional-p (encoded)
  `(logtest (encoded-lambda-list-bits ,encoded)
            encoded-lambda-list-non-positional-mask))

(defmacro encoded-lambda-list-keyp (encoded)
  `(logtest (encoded-lambda-list-bits ,encoded)
            encoded-lambda-list-key-mask))

(defmacro encoded-lambda-list-alwkyp (encoded)
  `(logtest (encoded-lambda-list-bits ,encoded)
            encoded-lambda-list-alwky-mask))

(defun encode-lambda-list (lambda-list)
  (multiple-value-bind (req opt rest keyp keys allow)
      (parse-lambda-list-into-components lambda-list)
    (let ((bits 0)
	  (required (length req)))
      (macrolet ((ior (test mask)
		   `(when ,test (setf bits (logior bits ,mask)))))
	(ior (or rest keyp) encoded-lambda-list-non-positional-mask)
	(ior keyp encoded-lambda-list-key-mask)
	(ior allow encoded-lambda-list-alwky-mask))
      (%make-encoded-lambda-list :required required
				 :positional (+ required (length opt))
				 :bits bits
				 :keys (mapcar #'caar keys)))))

(defun congruent-encoded-lambda-lists (gf-encoded method-encoded)
  ;; First match required count, positional count, and non-positional bit.
  (and (= (encoded-lambda-list-required gf-encoded)
	  (encoded-lambda-list-required method-encoded))
       (= (encoded-lambda-list-positional gf-encoded)
	  (encoded-lambda-list-positional method-encoded))
       (if (not (encoded-lambda-list-non-positional-p gf-encoded))
	   (not (encoded-lambda-list-non-positional-p method-encoded))
	   (and (encoded-lambda-list-non-positional-p method-encoded)
		;; The method must permit all of the keys explicitly mentioned
		;; by the generic function, either by specifying &rest but not
		;; &key, by specifying &allow-other-keys, or by explicitly
		;; mentioning them.
		(let ((gfk (encoded-lambda-list-keys gf-encoded)))
		  (or (null gfk)
		      (not (encoded-lambda-list-keyp method-encoded))
		      (encoded-lambda-list-alwkyp method-encoded)
		      (subsetp gfk (encoded-lambda-list-keys method-encoded))
		      ))))))


;;; MAKE-METHOD-FUNCTION					[Function]
;;;
;;; Syntax:
;;;	make-method-function name specialized-lambda-list body environment
;;;
;;; Arguments:
;;;	name -- A function name.
;;;
;;;	specialized-lambda-list -- A specialized lambda-list.
;;;
;;;	body -- A list of forms, possibly including declarations and a
;;;	documentation string.
;;;
;;;	environment -- A syntactic environment.
;;;
;;; Values:
;;;	method-lambda -- A lambda expression.
;;;
;;;	initarg list -- A list of initarg names and value forms
;;;
;;; Description:
;;;	The function MAKE-METHOD-FUNCTION is called to produce a lambda
;;;	expression which can be used to produce a method function for a method.
;;;	
;;;	Either the function COMPILE, the special form FUNCTION, or the
;;;	functions COERCE or ENCLOSE must be used to convert the lambda
;;;	expression to such a method function.  The method function cannot
;;;	itself be called directly.  The results are undefined if the method
;;;	function is applied to arguments using the APPLY or FUNCALL functions
;;;	or the MULTIPLE-VALUE-CALL special form.
;;;
;;;	The body of a DEFMETHOD macro, the bodies of :METHOD arguments in a
;;;	DEFGENERIC or GENERIC-FUNCTION macro, and the bodies of :METHOD
;;;	arguments in a GENERIC-FLET or GENERIC-LABELS special form must be
;;;	converted into a method function.  This conversion is a two step
;;;	process. 
;;;
;;;	The first step occurs during macroexpansion of the macro form.  In this
;;;	step, the method body is converted into a form which will evaluate to a
;;;	method function.  Production of the method lambda proceeds by calling
;;;	MAKE-METHOD-FUNCTION.  The arguments for this call are:
;;;
;;;	* The name of the generic-function for which the method is being
;;;	  generated.  This argument may be Nil if the generic-function is
;;;	  anonymous.  If the name is non-Nil then a BLOCK with a name
;;;	  determined from this argument will surround the body forms.  The name
;;;	  may also be used in errors and warnings signaled during the
;;;	  construction of the method lambda.
;;;
;;;	* The specialized lambda list for the method.
;;;
;;;	* The body forms of the method, which may include declarations and a
;;;	  documentation string.
;;;
;;;	* The syntactic environment available at the time the form is being
;;;	  processed. 
;;;
;;;	The function MAKE-METHOD-FUNCTION returns to values.
;;;
;;;	* A method lambda.
;;;
;;;	* A list of initialization argument names (symbols) and value forms.
;;;	  These will be included in the initialization arguments when the
;;;	  method is created.  Note that because these initialization arguments
;;;	  appear in the expansion of the macro form, and because this can
;;;	  happen as part of a file compilation, all of the initialization
;;;	  argument values must have applicable methods for the generic-function
;;;	  MAKE-LOAD-FORM.
;;;
;;; Notes:
;;;	The description of this function is based in part on the description of
;;;	the generic-function MAKE-METHOD-LAMBDA in the 6/6/90 draft of the
;;;	Metaobject Protocol (specifically, the section titled `Processing
;;;	Method Bodies' and the function pages for MAKE-METHOD-LAMBDA).
;;;	However, the protocol specified here for MAKE-METHOD-FUNCTION differs
;;;	in a number of ways from the current specification of
;;;	MAKE-METHOD-LAMBDA, so I chose to use a different name.  Note that all
;;;	of the differences are changes that I feel are needed for
;;;	MAKE-METHOD-LAMBDA to actually do what it is supposed to do, so these
;;;	could actually converge in some later draft of the Metaobject Protocol.
;;;
;;;	The differences between MAKE-METHOD-FUNCTION and MAKE-METHOD-LAMBDA are
;;;	primarily in the arguments they recieve.  The following points discuss
;;;	the differences between the two functions.
;;;
;;;	* MAKE-METHOD-LAMBDA is described as being a generic-function, with the
;;;	  first two arguments being a generic-function object and a method
;;;	  object, with methods specialized on these arguments.  The problem
;;;	  with this is that it requires too much information to be available at
;;;	  compile-time, and more consistancy between compile-time and runtime
;;;	  than is specified in the Standard.
;;;
;;;	* Name -- The name needs to be explicitly supplied so that the body can
;;;	  be wrapped in a BLOCK form with the appropriate name.  This argument
;;;	  is needed even by MAKE-METHOD-LAMBDA, since it cannot be reliably
;;;	  obtained from the generic-function or method arguments since it is
;;;	  explicitly stated that these may not be the actual generic-function
;;;	  or method objects for which the method lambda is being computed.
;;;	  This requirement could be removed if the lambda argument passed to
;;;	  MAKE-METHOD-LAMBDA was required to have the block already installed,
;;;	  but this requirement is not stated or implied.
;;;
;;;	* Specialized-Lambda-List -- Information about the specializers is
;;;	  needed so that optimizations may be made on the body forms.  This
;;;	  argument could be eliminated if the lambda argument passed to
;;;	  MAKE-METHOD-LAMBDA were specified as including the specializers in
;;;	  the lambda list, but this requirement is not stated or implied. 
;;;
;;;	* Environment -- This is needed in order to perform any interesting
;;;	  transformations on the body of the method in the process of creating
;;;	  the method lambda.  This argument is simply missing from the
;;;	  description of MAKE-METHOD-LAMBDA.
;;;
;;;	In addition, all references to APPLY-METHOD-FUNCTION have been removed.
;;;	I don't believe this is the right interface.  Certainly it is the wrong
;;;	interface for this implementation.  I have not yet figured out a better
;;;	extensible interface though.  One point about APPLY-METHOD-FUNCTION
;;;	though is that it seems to me that it is at the wrong time.  What is
;;;	needed is to be able to specialize the expander of CALL-METHOD, rather
;;;	than specializing the caller of methods.  Unfortunately, that also
;;;	doesn't work well, because I can't think of any way to make
;;;	CALL-NEXT-METHOD work efficiently in such a situation.

(defun make-method-function (name specialized-lambda-list body env)
  (multiple-value-bind (lambda-list specializers specialized)
      (parse-specialized-lambda-list specialized-lambda-list)
    (multiple-value-bind (body declspecs doc)
	(parse-body body t)
      (multiple-value-bind (method-arguments method-declspecs)
	  (make-method-arguments)
	(multiple-value-bind (closed-method-arguments closed-declspecs)
	    (make-closed-method-arguments)
	  (let* ((env (translator-augment-environment
		        env
			:variable (append method-arguments
					  closed-method-arguments)
			:declare `((method-level)
				   ,@method-declspecs
				   ,@closed-declspecs)))
		 (specializer-records
    		      (multiple-value-bind (records newdeclspecs)
			  (make-specializers lambda-list
					     specializers
					     specialized
					     env)
			(setf declspecs (append newdeclspecs declspecs))
			records))
		 (method-body-function-records
		      (make-method-body-functions env))
		 walked-lambda-list
		 walked-body
		 (initargs nil))
	    (setf (cgetf initargs :name) `',name)
	    (setf (cgetf initargs :lambda-list)
		  (make-lambda-list-initarg-form lambda-list))
	    (setf (cgetf initargs :specializers)
		  (make-specializer-initarg-form specializers env))
	    (when (record-documentation-p doc)
	      (setf (cgetf initargs :documentation) doc))
	    (loop
	      (multiple-value-setq (walked-lambda-list walked-body)
		  ;; Do first pass to collect usage information.
		  (perform-pass-1-method-walk name
					      lambda-list
					      specializer-records
					      body
					      method-body-function-records
					      declspecs
					      env))
	      ;; Remove unnecessary specializer records.
	      (multiple-value-bind (records decls modified-specializers)
		  (process-specializers specializer-records)
		(setf specializer-records records)
		(setf declspecs (append decls declspecs))
		;; Repeat until no specializers are modified.
		(when (not modified-specializers) (return))))
	    (setf method-body-function-records
		  (process-method-body-functions method-body-function-records))
	    (multiple-value-setq (walked-body initargs)
	      (perform-pass-2-method-walk name
					  walked-lambda-list
					  specializer-records
					  walked-body
					  method-body-function-records
					  declspecs
					  initargs
					  env))
	    (values `(lambda ,method-arguments
		       ,@(when doc (list doc))
		       (declare ,@method-declspecs)
		       (with-closed-method-arguments
			   ,closed-method-arguments
			   ,method-arguments
			 (declare ,@closed-declspecs)
			 ,@walked-body))
		    initargs)))))))

(defun make-lambda-list-initarg-form (lambda-list)
  (multiple-value-bind (req opt rest keyp keys alwky)
      (parse-lambda-list-into-components lambda-list)
    `'(,@req
       ,@(when opt (cons '&optional (mapcar #'car opt)))
       ,@(when rest (list '&rest rest))
       ,@(when keyp
	   `(&key
	     ,@(mapcar #'(lambda (keyparm) (list (car keyparm))) keys)
	     ,@(when alwky (list '&allow-other-keys)))))))

;;; Most of the hair in this is so that as much of the tail of the list can be
;;; generated as a quoted constant as possible.  Everything following the last
;;; non-constant eql specializer will be a list consed up at macroexpand time,
;;; which will allow it to be statically allocated in the remote environment.
;;; This means that for the really common case of no eql specializers, the
;;; entire list can be statically consed.

(defun make-specializer-initarg-form (specializers env)
  (labels ((collect-specializers (specializers env)
	     (if (endp specializers)
		 (values nil nil)
		 (multiple-value-bind (tail evaluatep)
		     (collect-specializers (cdr specializers) env)
		   (multiple-value-bind (form form-evaluatep)
		       (make-specializer (car specializers) env)
		     (cond (evaluatep
			    (if form-evaluatep
				(values (cons form tail) evaluatep)
				(values (cons `',form tail) evaluatep)))
			   (form-evaluatep
			    (cond ((null tail)
				   (values (list form) 'list))
				  ((null (cdr tail))
				   (values (list form `',(car tail)) 'list))
				  (t
				   (values (list form `',tail) 'list*))))
			   (t
			    (values (cons form tail) nil)))))))
	   (make-specializer (specializer env)
	     (if (consp specializer)
		 (let ((value (walk:walk-form (second specializer))))
		   (or (multiple-value-bind (constant-value therep)
			   (translator-constant-value value env)
			 (and therep
			      (typep constant-value
				     '(or number character symbol))
			      `(eql ,constant-value)))
		       (values `(list 'eql ,value) t)))
		 (values (proper-class-name specializer env) nil))))
    (multiple-value-bind (specializer-list list-constructor)
	(collect-specializers specializers env)
      (if list-constructor
	  (cons list-constructor specializer-list)
	  (list 'quote specializer-list)))))
		     
(defun make-specializers (lambda-list specializers specialized env)
  (let ((ignorable ()))
    (values (mapcan #'(lambda (var specializer specialized)
			(if (and specialized
				 ;; Sort of a quick (or symbolp classp)
				 (not (consp specializer)))
			    (list (make-specializer var specializer env))
			    (progn (push var ignorable) nil)))
		    lambda-list
		    specializers
		    specialized)
	    (when ignorable `((ignorable ,@ignorable))))))

(defun collect-lambda-list-variables (lambda-list &aux (variables nil))
  (parse-lambda-list lambda-list
		     :required #'(lambda (arg)
				   (push arg variables))
		     :optional #'(lambda (var init initp svar svar-p)
				   (declare (ignore init initp))
				   (push var variables)
				   (when svar-p (push svar variables)))
		     :rest #'(lambda (arg)
			       (push arg variables))
		     :key #'(lambda (var key init initp svar svar-p)
			      (declare (ignore key init initp))
			      (push var variables)
			      (when svar-p (push svar variables)))
		     :aux #'(lambda (arg init initp)
			      (declare (ignore init initp))
			      (push arg variables)))
  variables)

(defun perform-pass-1-method-walk
       (name lambda-list specializers body mbf-records declspecs env)
  (declare (ignore name))
  (let* ((walker (make-method-body-walker 1))
	 (sdecls (make-specializer-declarations specializers))
	 (mdecls (make-method-body-function-declarations mbf-records))
	 (walked-lambda-list
	  (walk-method-lambda-list lambda-list env
				   :declare (append sdecls declspecs)
				   :walk-function walker)))
    (values walked-lambda-list
	    (walk:walk-progn
	      body
	      (translator-augment-environment
	        env
		:variable (collect-lambda-list-variables walked-lambda-list)
		:function *method-body-function-names*
		:declare (append sdecls mdecls declspecs))
	      walker))))

(defun walk-method-lambda-list (lambda-list env &key declare walk-function)
  (second (walk:walk-function
	   `(lambda ,lambda-list (declare ,@declare)
	      (macrolet ((notice-special-specializers-macro (&environment env)
			   (notice-special-specializers ',lambda-list env)
			   '(progn)))
		(notice-special-specializers-macro)))
	   env
	   walk-function)))

(defun notice-special-specializers (lambda-list env)
  (dolist (name lambda-list)
    (if (lambda-keyword-p name)
	(return nil)
	(multiple-value-bind (usage boundp info)
	    (translator-variable-information name env)
	  (declare (ignore boundp info))
	  (when (eq usage :special)
	    (let ((specializer (specializerp name env)))
	      (when specializer
		(setf (specializer-special specializer) t))))))))

(defun process-specializers (specializer-records)
  (let ((specializer-modified-p nil)
	(ignored-specializer-names ())
	(retained-specializers ()))
    (flet ((optimization-failure-warning (record reason)
	     (when (specializer-slot-access record)
	       ;; *** This should be a style warning.
	       (warn "The specialized variable ~S ~A, which may prevent~@
                      slot access optimizations from being performed."
		     (specializer-name record) reason))))
      (dolist (specializer specializer-records)
	(cond ((specializer-special specializer)
	       ;; Remove specializers for which the variable is special.  This
	       ;; is done because it is hard to determine whether special
	       ;; variables are modified by the method body, so just assume
	       ;; they might be and inhibit optimization.
	       (optimization-failure-warning specializer "is SPECIAL"))
	      ((not (specializer-used specializer))
	       (push (specializer-name specializer) ignored-specializer-names))
	      ((specializer-modified specializer)
	       (setf specializer-modified-p t)
	       (optimization-failure-warning specializer "is modified"))
	      (t
	       (push specializer retained-specializers))))
      (values retained-specializers
	      (when ignored-specializer-names
		`((ignore ,@ignored-specializer-names)))
	      specializer-modified-p))))

(defun process-method-body-functions (records)
  (mapcan #'(lambda (record)
	      (when (method-body-function-referenced record)
		(list record)))
	  records))

(defun perform-pass-2-method-walk
       (name lambda-list specializers body mbf-records declspecs initargs env)
  (let* ((walker (make-method-body-walker 2))
	 (body-continuation
	  #'(lambda (env declspecs)
	      (perform-pass-2-body-walk name
					body
					mbf-records
					declspecs
					initargs
					env
					walker))))
    (perform-pass-2-method-lambda-list-walk lambda-list
					    specializers
					    declspecs
					    initargs
					    env
					    walker
					    body-continuation)))

(defun perform-pass-2-method-lambda-list-walk
       (lambda-list specializers declspecs initargs env walker continuation)
  (let ((required ()))
    (do ()
	((endp lambda-list))
      (let ((next (pop lambda-list)))
	(if (lambda-keyword-p next)
	    (return (push next lambda-list))
	    (push next required))))
    (setf required (nreverse required))
    (multiple-value-bind (bound free)
	(split-declarations-for-variables required env declspecs)
      (labels ((make-continuation (specializers)
		 (if (endp specializers)
		     #'(lambda (env &aux form)
			 ;; establish-slot-optimization-context doesn't deal
			 ;; with initargs, so update closed binding here.
			 (multiple-value-setq (form initargs)
			   (walk-remaining-lambda-list lambda-list
						       free
						       initargs
						       (length required)
						       env
						       walker
						       continuation))
			 form)
		     (let ((specializer (pop specializers))
			   (c (make-continuation specializers)))
		       (if (specializer-slot-access specializer)
			   #'(lambda (env)
			       (establish-slot-optimization-context
				 (specializer-class specializer)
				 (specializer-name specializer)
				 env
				 c))
			   c)))))
	(let ((form (funcall (make-continuation specializers)
			     (translator-augment-environment
			        env
				:variable required
				:declare
				(append
				  (make-specializer-declarations specializers)
				  bound)))))
	  (values `((let* ,(make-required-method-bindings required env)
		      (declare ,@bound
			       ;; Add type declarations for specialized vars
			       ,@(make-specializer-type-declarations
				    specializers env))
		      ,form))
		  initargs))))))

(defun make-required-method-bindings (variables env)
  (declare (ignore env))
  (let ((index -1))
    (mapcar #'(lambda (variable)
		`(,variable (method-argument ,(incf index))))
	    variables)))

(defun make-specializer-type-declarations (specializer-records env)
  (labels ((type-decl (record)
	     (let* ((class (specializer-class record))
		    (name (tclos:class-name class)))
	       (and name
		    (eq (translator-find-class name nil env) class)
		    `((type ,name ,(specializer-name record)))))))
    (mapcan #'type-decl specializer-records)))

(defun walk-remaining-lambda-list
    (lambda-list declspecs initargs position env walker body-continuation)
  (declare (ignore initargs))
  (let* ((walked-lambda-list
	  (walk-method-lambda-list lambda-list env
				   :declare declspecs
				   :walk-function walker))
	 (variables (collect-lambda-list-variables walked-lambda-list)))
    (multiple-value-bind (bound free)
	(split-declarations-for-variables variables env declspecs)
      (multiple-value-bind (body initargs)
	  (funcall body-continuation
		   (translator-augment-environment env
						   :variable variables
						   :declare bound)
		   free)
	(let ((bindings ())
	      (temp nil)
	      (keytable nil)
	      (keymap ())
	      (keyindex -1)
	      (restp nil))
	  (macrolet ((bind (var &optional init)
		       `(push (list ,var ,init) bindings)))
	    (flet ((bind-temp (&optional (init nil initp))
		     (cond ((null temp)
			    (setf temp (make-variable "TEMP"))
			    (bind temp init))
			   (initp
			    (error "Temp already added to bindings."))))
		   (bind-using-test (var test access init)
		     (bind var `(if ,test ,access ,init)))
		   (bind-keytable ()
		     (let ((margs (method-arguments env)))
		       (setf keytable (make-variable "KEYTABLE"))
		       (bind
			keytable
			`(tclos-run:%effective-method-keyword-permutation
			  ,(method-arguments-effective-method margs)
			  ,(method-arguments-method-index margs))))))
	      (parse-lambda-list walked-lambda-list
				 :required #'(lambda (var)
					       (declare (ignore var))
					       (error
						"Should have already processed required parameters."))
				 :optional #'(lambda (var init initp svar svar-p)
					       (declare (ignore initp))
					       (let ((test `(method-optional-argument-p ,position))
						     (access `(method-argument ,position)))
						 (incf position)
						 (cond ((not svar-p)
							(bind-using-test var test access init))
						       ((null temp)
							(bind-temp test)
							(bind-using-test var temp access init)
							(bind svar temp))
						       (t
							(setf test `(setf ,temp ,test))
							(bind-using-test var test access init)
							(bind svar temp)))))
				 :rest #'(lambda (var)
					   (bind var `(method-rest-list))
					   (setf restp t))
				 :key #'(lambda (var key init initp svar svar-p)
					  (declare (ignore initp))
					  (unless keytable (bind-keytable))
					  (let ((index (cdr (assoc key keymap)))
						(key-parm `((,key ,var) ,init
							    ,@(when svar-p (list svar))))
						(value-form nil))
					    (when (null index)
					      (setf index (incf keyindex))
					      (push (cons key keyindex) keymap))
					    (setf value-form `(method-key-value ,keytable ,index))
					    (when (null temp)
					      (bind-temp value-form)
					      (setf value-form temp))
					    (multiple-value-bind (vbind sbind)
						(make-method-key-bindings key-parm
									  temp
									  value-form)
					      (push vbind bindings)
					      (when sbind (push sbind bindings)))))
				 :allow-other-keys-p #'(lambda () nil)
				 :aux #'(lambda (var init initp)
					  (declare (ignore initp))
					  (bind var init)))))
	  (unless (null keymap)
	    ;; Reorder from low to high.
	    (setf keymap (nreverse keymap))
	    (setf (cgetf initargs :keyword-parameter-map)
		  `',(coerce (mapcar #'car keymap) 'vector)))
	  (values `(let* ,(nreverse bindings)
		     (declare ,@bound)
		     ,@body)
		  initargs))))))

(defun perform-pass-2-body-walk
    (name body mbf-records declspecs initargs env walker)
  (let* ((mdecls (make-method-body-function-declarations mbf-records))
	 (body-env (translator-augment-environment
		     env
		     :function *method-body-function-internal-names*
		     :declare (append mdecls declspecs))))
    (multiple-value-bind (function-bindings function-binding-decls)
	(make-method-body-function-bindings mbf-records body-env)
      (setf body `((let ,function-bindings
		     (declare ,@declspecs ,@function-binding-decls)
		     ,@body)))
      ;; If named, wrap named block around the body.
      (when name (setf body `((block ,(body-block-name name) ,@body))))
      (values (walk:walk-progn body body-env walker)
	      initargs
	      ))))

(defun split-declarations-for-variables (names env declspecs)
  (let ((bound ())
	(free ()))
    (multiple-value-bind (v-decls f-decls set-r-decls r-decls)
	(translator-parse-declarations declspecs env :variable names)
      (dolist (decl v-decls)
	(if (member (car decl) names)
	    (push decl bound)
	    (push decl free)))
      (values `((tx:variable-information ,@(nreverse bound)))
	      (mapcan #'(lambda (decl-symbol decls)
			  (when decls
			    (list `(,decl-symbol ,@decls))))
		      '(tx:variable-information tx:function-information
			tx:set-declaration-information
			tx:declaration-information)
		      (list (nreverse free) f-decls set-r-decls r-decls))))))

(defun split-declarations-for-functions (names env declspecs)
  (let ((bound ())
	(free ()))
    (multiple-value-bind (v-decls f-decls set-r-decls r-decls)
	(translator-parse-declarations declspecs env :function names)
      (dolist (decl f-decls)
	(if (member (car decl) names :test #'equal)
	    (push decl bound)
	    (push decl free)))
      (values `((tx:function-information ,@(nreverse bound)))
	      (mapcan #'(lambda (decl-symbol decls)
			  (when decls
			    (list `(,decl-symbol ,@decls))))
		      '(tx:variable-information tx:function-information
			tx:set-declaration-information
			tx:declaration-information)
		      (list v-decls (nreverse free) set-r-decls r-decls))))))

;;; WITH-ACCESSORS

(define-translator-macro with-accessors
    (slots object &body body &environment env)
  "The macro WITH-ACCESSORS creates a lexical environment in which specified
slots are lexically available through their accessors as if they were
variables.  The macro WITH-ACCESSORS invokes the appropriate accessors to
access the specified slots.  Both SETF and SETQ can be used to set the value of
the slot.  The result returned is that obtained by executing the body forms.

Syntax:
  with-accessors ({slot-entry}*) instance-form {declaration}* {form}*

  slot-entry ::= (variable-name accessor-name)
"
  (expand-with-accessors slots object body env))

;;; *** This function for generating the expansion of with-accessors could be
;;; *** made a bit smarter about the introduction of a temp variable.  See the
;;; *** comment below for WITH-SLOTS.

(defun expand-with-accessors (slots object body env)
  (let ((instance-form (walk:walk-form object :environment env)))
    (let ((stripped-instance-form (strip-the instance-form env)))
      (when (and (symbolp stripped-instance-form)
		 (specializerp stripped-instance-form env))
	(return-from expand-with-accessors
	  (expand-specialized-with-accessors slots instance-form body env))))
    (let ((type (form-type instance-form env))
	  (ovar (make-variable "OBJECT")))
      `(let ((,ovar ,object))
	 (declare (ignorable ,ovar))
	 (declare (type ,type ,ovar))
	 (symbol-macrolet ,(make-with-accessors-bindings slots ovar)
	   ,@body)))))

(defun make-with-accessors-bindings (slots object)
  (mapcar #'(lambda (slot-entry)
	      `(,(car slot-entry) (,(cadr slot-entry) ,object)))
	  slots))

;;; If object form is a reference to a specialized variable, then it is
;;; guaranteed to be unmodified, so no temp variable is needed.

(defun expand-specialized-with-accessors (slots object body env)
  (declare (ignore env))
  `(symbol-macrolet ,(make-with-accessors-bindings slots object)
     ,@body))

;;; WITH-SLOTS
;;;
;;; Define the macro WITH-SLOTS, using the same code walking techniques as used
;;; in the optimization of method bodies above.

(define-translator-macro with-slots (slots object &body body &environment env)
  "The macro WITH-SLOTS creates a lexical context for referring to specified
slots as though they were variables.  Within such a context the value of the
slot can be specified by using its slot name, as if it were a lexically bound
variable.  Both SETF and SETQ can be used to set the value of the slot.  The
macro WITH-SLOTS translates an appearance of the slot name as a variable into a
call to SLOT-VALUE.  The result returns is that obtained by executing the body
forms. 

Syntax:
  with-slots ({slot-entry}*) instance-form {declaration}* {form}*

  slot-entry ::= slot-name | (variable slot-name)
"
  (expand-with-slots slots object body env))

(defun expand-with-slots (slots object body env)
  (setf slots (canonicalize-with-slots-slots slots))
  (let ((instance-form (walk:walk-form object :environment env)))
    (let ((stripped-instance-form (strip-the instance-form env)))
      (when (and (symbolp stripped-instance-form)
		 (specializerp stripped-instance-form env))
	(return-from expand-with-slots
	  (expand-specialized-with-slots slots instance-form body env))))
    (let ((class (class-of-type (form-type instance-form env) env)))
      (if (null class)
	  (expand-with-slots-default slots object body env)
	  (optimize-with-slots slots instance-form class body env)))))

(defun canonicalize-with-slots-slots (slots)
  (mapcar #'(lambda (slot-entry)
	      (cond ((symbolp slot-entry)
		     (list slot-entry slot-entry))
		    ((and (consp slot-entry)
			  (symbolp (car slot-entry))
			  (consp (cdr slot-entry))
			  (symbolp (cadr slot-entry))
			  (null (cddr slot-entry)))
		     slot-entry)
		    (t
		     (error "Invalid slot specification ~S." slot-entry))))
	  slots))

(defun make-with-slots-bindings (slots object)
  (mapcar #'(lambda (slot-entry)
	      `(,(car slot-entry) (slot-value ,object ',(cadr slot-entry))))
	  slots))

;;; If the object form is a reference to a specialized variable then it is
;;; guaranteed to be unmodified, so no temp variable is needed.

(defun expand-specialized-with-slots (slots object body env)
  (declare (ignore env))
  `(symbol-macrolet ,(make-with-slots-bindings slots object)
     ,@body))

;;; *** These functions for generating the expansion of with-slots could be
;;; *** made a bit smarter.  If the object form is a lexical variable
;;; *** reference, it could try walking the body using the variable directly
;;; *** rather than consing up a temp, and then check to see if the body
;;; *** modifies the variable.  The temp binding for the object would then only
;;; *** need to be introduced when the object form is something more complex
;;; *** than a lexical variable reference or when the variable is modified by
;;; *** the body.  Of course, any reasonable temp removal phase in the
;;; *** translator could also accomplish this.

(defun expand-with-slots-default (slots object body env)
  (declare (ignore env))
  (let ((ovar (make-variable "OBJECT")))
    `(let ((,ovar ,object))
       (declare (ignorable ,ovar))
       (symbol-macrolet ,(make-with-slots-bindings slots ovar)
	 ,@body))))

(defun optimize-with-slots (slots object class body env)
  (setf env (translator-augment-environment env :declare '((method-level))))
  (multiple-value-bind (real-body declspecs) (parse-body body nil)
    (let* ((var (make-variable "OBJECT"))
	   (specializers (list (make-specializer var class env)))
	   (sdecls (make-specializer-declarations specializers))
	   (macros (make-with-slots-bindings slots var))
	   (senv (translator-augment-environment
		   env
		   :variable (list var)
		   :symbol-macro macros
		   :declare (append sdecls declspecs))))
      (setf real-body
	    (walk:walk-progn real-body senv (make-method-body-walker 1)))
      (setf specializers (process-specializers specializers))
      (if (or (null specializers)
	      (not (specializer-slot-access (car specializers))))
	  (expand-with-slots-default slots object body env)
	  `(let ((,var ,object))
	     (declare ,@(make-specializer-type-declarations specializers env))
	     (symbol-macrolet ,macros
	       (declare ,@declspecs)
	       ,(establish-slot-optimization-context
		  class
		  var
		  senv
		  #'(lambda (env)
		      (walk:walk-form
		           `(progn ,@real-body)
			   :environment env
			   :walk-function (make-method-body-walker 2))))))))))

;;; DEFINE-METHOD-FUNCTION
;;;
;;; This macro is used to define bootstrapping methods for predefined
;;; generic-functions.  They are defined as global functions but with
;;; arguments and such like methods.

(define-translator-macro define-method-function
    (name lambda-list &body body &environment env)
  (multiple-value-bind (lambda initargs)
      (make-method-function name lambda-list body env)
    (declare (ignore initargs))
    `(defun ,name ,@(cdr lambda))))

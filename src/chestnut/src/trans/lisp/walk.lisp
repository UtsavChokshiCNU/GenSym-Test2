;;; -*- Mode: Lisp; Package: WALK; Syntax: Common-Lisp -*-
;;;
;;; Copyright (C) 1991 Chestnut Software, Inc.  All Rights Reserved.
;;;
;;; ===========================================================================
;;;
;;; 1. The external interface to this walker is through the following set of
;;; functions, the names of which are all exported from the WALK package.
;;;
;;; WALK-FORM							[Function]
;;;
;;;  Syntax:
;;;	walk-form form &key environment walk-function
;;;
;;;  Arguments:
;;;	form -- A form.
;;;
;;;	environment -- A translator environment.
;;;
;;;	walk-function -- A function or function-name.
;;;
;;;  Values:
;;;	A form.
;;;
;;;  Description:
;;;	This is the primary entry point for the code walker.  It takes as
;;;	arguments a form to walk, a translator environment in which to process
;;;	the form, and a function that is called on each form before it gets
;;;	walked.
;;;
;;;	If the environment argument is unsupplied, the default global
;;;	translator environment is used.
;;;
;;;	The walk-function argument is called with three arguments, a form, an
;;;	environment, and a walk function.  It should return two values.  The
;;;	first value is a form (possibly the argument form, possibly a
;;;	transformed form).  The second argument is a flag.  If true, it
;;;	indicates that no further walking should be done on the form that was
;;;	returned as the first value.  If it is false, then if the new form is
;;;	different (not EQ) from the original form then walking is recursively
;;;	invoked on the new form.  Otherwise, subforms of the new form are
;;;	walked and collected into a new form to return as the result.
;;;
;;;	If the walk-function is unsupplied or Nil, walk-form behaves as if
;;;	called with a function that simply returns two values, its first
;;;	argument (the form) and nil.
;;;
;;;  Notes:
;;;	Since determination of subforms may require macroexpansion of the form,
;;;	the result form will typically have macro calls expanded.  However, if
;;;	the walk-function argument terminates subform processing prematurely,
;;;	full macroexpansion will not occur.  Also, some macro calls may remain
;;;	unexpanded if the walker has specialized knowledge of the form and
;;;	treats it as a special form.  The set of macros treated in this fashion
;;;	is unspecified.
;;;
;;; WALK-FUNCTION						[Function]
;;;
;;;  Syntax:
;;;	walk-function function environment walk-function
;;;
;;;  Arguments:
;;;	function -- A function definition.
;;;
;;;	environment -- A translator environment.
;;;
;;;	walk-function -- A function or function-name.
;;;
;;;  Values:
;;;	A function definition.
;;;
;;;  Description:
;;;	Walks a function definition, which has the format of a lambda
;;;	expression, except that the CAR of the form may be a function name
;;;	rather than the symbol LAMBDA.
;;;
;;;	It is as if the function WALK-FORM were applied to subforms of the
;;;	function definition, using the specified environment and walk-function,
;;;	with the results being used to construct an equivalent function
;;;	definition to be returned as the result of this function.
;;;
;;; WALK-ARGUMENTS						[Function]
;;;
;;;  Syntax:
;;;	walk-arguments arguments environment walk-function
;;;
;;;  Arguments:
;;;	arguments -- A list of forms.
;;;
;;;	environment -- A translator environment.
;;;
;;;	walk-function -- A function or function-name.
;;;
;;;  Values:
;;;	A list of forms corresponding to each of the argument forms.
;;;
;;;  Description:
;;;	This is a convenience function, used to walk a list of forms as if they
;;;	were arguments to a function call, returning a list of the walked
;;;	forms.
;;;
;;;	It is as if the function WALK-FORM were applied to each of the forms in
;;;	the arguments list, using the specified environment and walk-function,
;;;	with the result of each call collected into a list to be returned.
;;;
;;; WALK-PROGN							[Function]
;;;
;;;  Syntax:
;;;	walk-progn forms environment walk-function &optional side-effect-only
;;;
;;;  Arguments:
;;;	forms -- A list of forms.
;;;
;;;	environment -- A translator environment.
;;;
;;;	walk-function -- A function or function name.
;;;
;;;	side-effect-only -- True or false.
;;;
;;;  Values:
;;;	A list of forms.
;;;
;;;  Description:
;;;	This function may be used to process a list of forms that are to be
;;;	treated as if they were in a PROGN context.
;;;
;;;	It is as if the function WALK-FORM were applied to each of the forms in
;;;	the list, using the specified environment and walk-function, to compute
;;;	a new list of forms for the PROGN context.  Further transformations may
;;;	then be performed, based on the knowledge that all of the forms appear
;;;	in a PROGN context.
;;;
;;;	The side-effect-only argument permits certain transformations of the
;;;	resulting forms, and should only be specified as true when the PROGN
;;;	context in which the argument forms appear is to be executed for
;;;	side-effect rather than for value.
;;;
;;;  Notes:
;;;	This function differs from WALK-ARGUMENTS in that some transformations
;;;	involving interaction between the seperate forms may occur, due to the
;;;	knowledge that the forms appear in a PROGN context.  For example,
;;;	embedded PROGN forms might be spliced directly into the list, and
;;;	constant forms might be removed.
;;;
;;; ===========================================================================
;;;
;;; 2. There is no notion of the distinction between toplevel and non-toplevel,
;;; or compile-time-too evaluation, or similar issues.  It effectivly treats
;;; EVAL-WHEN forms as if they were in a non-toplevel position, walking the
;;; body forms regardless of the situations specified, and it is assumed that
;;; this walker will only be called when such behavior is appropriate.
;;;
;;; Correctly handling these issues would complicate the definition and usage
;;; of this walker without significant benefit, since it is not intended for
;;; use in situations where these issues are relevent.
;;;
;;; ===========================================================================
;;;
;;; 3. There is no attempt here to remove side-effect-free non-constant forms
;;; in void contexts, and similar transformations.  This is because this walker
;;; is intended to operate as a prepass on source forms, and such code removing
;;; transformations might result in spurious warnings being issued by later
;;; phases of the translation process (unreferenced variables not declared
;;; IGNORE, for example).
;;;
;;; ===========================================================================
;;;
;;; 4. This code walker assumes ANSI semantics for declaration scoping.  There
;;; has been no attempt to support both ANSI and CLtL declarations scoping
;;; based on a switch.
;;;
;;; ===========================================================================
;;;
;;; External references
;;;
;;;  body-block-name
;;;  define-translator-macro
;;;  lambda-expression-p
;;;  lambda-keyword-p
;;;  parse-body
;;;  parse-lambda-list
;;;  transform-lambda-to-let
;;;  translator-environment-p
;;;  translator-augment-environment
;;;  translator-compiler-macroexpand-1
;;;  translator-constantp
;;;  translator-enclose
;;;  translator-function-information
;;;  translator-get-setf-method
;;;  translator-macroexpand-1
;;;  translator-parse-macro
;;;  translator-parse-declarations
;;;  translator-subtypep
;;;  translator-symbol-macroexpand-1
;;;
;;;  tx:declaration-information
;;;  tx:function-information
;;;  tx:variable-information
;;;  tx:set-declaration-information

(in-package "WALK")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/walk.lisp,v $"
 "$Revision: 1.11 $"
 "$Date: 2007/06/26 19:48:38 $")

;(define-condition walk-error (program-error) ())
;
;(define-condition simple-walk-error (simple-condition walk-error) ())

(defun walk-error (datum &rest arguments)
  (if (stringp datum)
      ;(error 'simple-walk-error
      ;	     :format-string datum
      ;	     :format-arguments arguments)
      (apply #'error datum arguments)
      (apply #'error datum arguments)))

(defvar *variable-binding-declarations-hook* nil)

(defvar *walk-added-declarations-hook* nil)

(defvar *walk-setq-hook* nil)

;;; WALK-FORM

(defvar *function-binding-declarations-hook* nil)

(defvar *walk-bound-functions-hook* nil)

(defun ensure-translator-environment (environment)
  (setf environment (coerce-to-environment environment))
  (when (null environment) (setf environment *default-global-environment*))
  environment)

(defun WALK-FORM (form &key environment walk-function
		       ((:setq-hook *walk-setq-hook*) nil)
		       ((:added-declarations-hook
			 *walk-added-declarations-hook*) nil)
		       ((:variable-binding-declarations-hook
			 *variable-binding-declarations-hook*) nil)
		       ((:function-binding-declarations-hook
			 *function-binding-declarations-hook*) nil)
		       ((:walk-bound-functions-hook
			 *walk-bound-functions-hook*) nil))
  (walk-form-1 form
	       (ensure-translator-environment environment)
	       walk-function))
       
(defun walk-form-1 (form env walker &aux name handler)
  (when walker
    ;; When walker supplied, give it first shot at the form.
    (multiple-value-bind (newform finishedp)
	(funcall walker form env walker)
      (cond (finishedp 
	     ;; If walker says all done, then return its result
	     (return-from walk-form-1 newform))
	    ((not (eq form newform))
	     ;; If a new form was returned by the walker, return the result
	     ;; of walking it.  Note that there is a danger here that if
	     ;; some losing walker function conses up an equal form to be
	     ;; returned then we'll get into an infinite regress.  However,
	     ;; the walker function is supposed to return the original (EQ)
	     ;; form if it isn't going to actually change anything, just like
	     ;; a compiler macro expander.
	     (return-from walk-form-1 (walk-form-1 newform env walker)))
	    ;; else walk the original form
	    )))
  (cond ((symbolp form)
	 (multiple-value-bind (newform macrop)
	     (translator-symbol-macroexpand-1 form env)
	   (if macrop
	       ;; If form names a symbol-macro, walk the expansion
	       (walk-form-1 newform env walker)
	       ;; else return the symbol
	       form)))
	;; handle atomic constants
	((atom form) form)
	((not (symbolp (setf name (car form))))
	 (if (not (lambda-expression-p name))
	     (walk-error "~S is not recognized as a valid form by ~S."
			 form 'walk-form)
	     (multiple-value-bind (newform macrop)
		 ;; See if translator can do something with lambda forms.
		 (translator-compiler-macroexpand-1 form env)
	       (if macrop
		   ;; If translator compiler macroexpanded form, walk expansion
		   (walk-form-1 newform env walker)
		   (walk-lambda form env walker)))))
	((setf handler (special-form-walker name env))
	 ;; If the walker treats name as a special form, then use the walker's
	 ;; handler to process the form.
	 (funcall handler form env walker))
	(t
	 (multiple-value-bind (newform macrop)
	     ;; Try using a compiler macro if available.
	     (translator-compiler-macroexpand-1 form env)
	   (if macrop
	       ;; If compiler-macro expanded form, walk expansion.
	       (walk-form-1 newform env walker)
	       ;; Otherwise, dispatch on the usage type for the name.
	       (ecase (translator-function-information name env)
		 ((nil :function)
		  ;; Walk the form as a function call.
		  (walk-call name (cdr form) env walker))
		 (:macro
		  ;; Walk the result of macroexpanding the form.
		  (walk-form-1 (translator-macroexpand-1 form env)
			       env
			       walker))
		 (:special-form
		  (unknown-special-form-error name))))))))


;;; WALK-ARGUMENTS
;;;
;;; A convenience function.  Walk a list of forms as if they were arguments to
;;; a function call, returing the list of walked forms.

(defun WALK-ARGUMENTS (arguments env walker &key
		       ((:setq-hook *walk-setq-hook*) nil)
		       ((:added-declarations-hook
			 *walk-added-declarations-hook*) nil)
		       ((:variable-binding-declarations-hook
			 *variable-binding-declarations-hook*) nil)
		       ((:function-binding-declarations-hook
			 *function-binding-declarations-hook*) nil)
		       ((:walk-bound-functions-hook
			 *walk-bound-functions-hook*) nil))
  (setf env (ensure-translator-environment env))
  (walk-arguments-1 arguments env walker))

(defun walk-arguments-1 (arguments env walker)
  (mapcar #'(lambda (argument)
	      (walk-form-1 argument env walker))
	  arguments))

(defun walk-call (walked-function arguments env walker)
  (cons walked-function (walk-arguments-1 arguments env walker)))

(defun walk-add-declarations (declspecs variables env)
  (if *walk-added-declarations-hook*
      (append (funcall *walk-added-declarations-hook* variables nil env)
	      declspecs)
      declspecs))(defun walk-add-function-declarations (declspecs functions env)
  (if *walk-added-declarations-hook*
      (append (funcall *walk-added-declarations-hook* nil functions env)
	      declspecs)
      declspecs))

(defun default-walk-bound-functions (bindings function-env walker body-env)
  (declare (ignore body-env))
  (mapcar #'(lambda (binding)
	      (walk-function-1 binding function-env walker))
	  bindings))

(defun walk-function-1 (lambda env walker &optional info)
  
  (destructuring-bind (name lambda-list &body body) lambda
    (setq env (translator-augment-environment env 
					      :function-name name
					      :function-info info))
    (multiple-value-bind (body declspecs doc) (parse-body body t)
      (let ((variables (collect-lambda-list-variables lambda-list)))
	(multiple-value-bind (v-decls f-decls set-r-decls r-decls)
	    (translator-parse-declarations declspecs env :variable variables)
	  (multiple-value-bind (walked-lambda-list v-decls env)
	      (walk-lambda-list lambda-list env walker v-decls)
	    (let* ((declare 
		    (mapcan #'(lambda (decl-symbol decls)
				(when decls
				  (list `(,decl-symbol ,@decls))))
			    '(tx:variable-information
			      tx:function-information
			      tx:set-declaration-information
			      tx:declaration-information)
			    (list v-decls f-decls set-r-decls r-decls)))
		   (body-env
		    (if declare
			(translator-augment-environment
			 env :declare declare)
			env))
		   (walked-body
		    (if (member name '(nil lambda))
			(walk-progn-1 body body-env walker)
			(walk-block (body-block-name name)
				    body body-env walker))))
	      (setq declspecs (walk-add-declarations declspecs variables env))
	      `(,name ,walked-lambda-list
		  ,@(when doc (list doc))
		  ,@(make-declarations declspecs)
		  ,@walked-body))))))))

(defun walk-lambda-list (lambda-list env walker v-decls)
  ;; Make a copy of the variable declarations, so we can operate on it
  ;; destructively when extracting the declarations for bound variables.
  (setf v-decls (copy-list v-decls))
  (let ((new-lambda-list ())
	(optionalp nil)
	(auxp nil))
    (labels ((bind-var (var)
	       (multiple-value-bind (var-decls remaining)
		   (ncollect-applicable-decls var v-decls)
		 (setf v-decls remaining)
		 (setf env
		       (translator-augment-environment
			env
			:variable (list var)
			:declare
			`((tx:variable-information
			   ,@(when *variable-binding-declarations-hook*
			       (funcall *variable-binding-declarations-hook*
					var))
			   ,@var-decls))))))
	     (add-binding (var init &optional svar-p svar (key nil keyp))
	       (setf init (walk-form-1 init env walker))
	       (bind-var var)
	       (when keyp (setf var (list key var)))
	       (push (list* var init (when svar-p (list svar)))
		     new-lambda-list)
	       (when svar-p 
		 (bind-var svar)
		 (walk-form-1 svar env walker))))
      (parse-lambda-list 
       lambda-list
       :required #'(lambda (var)
		     (push var new-lambda-list)
		     (bind-var var))
       :optional #'(lambda (var init initp svar svar-p)
		     (declare (ignore initp))
		     (unless optionalp
		       (push '&optional new-lambda-list)
		       (setf optionalp t))
		     (add-binding var init svar-p svar))
       :rest #'(lambda (var)
		 (push '&rest new-lambda-list)
		 (push var new-lambda-list)
		 (bind-var var))
       :keyp #'(lambda ()
		 (push '&key new-lambda-list))
       :key #'(lambda (var key init initp svar svar-p)
		(declare (ignore initp))
		(add-binding var init svar-p svar key)) 
       :allow-other-keys-p #'(lambda ()
			       (push '&allow-other-keys new-lambda-list))
       :aux #'(lambda (var init initp)
		(declare (ignore initp))
		(unless auxp
		  (push '&aux new-lambda-list)
		  (setf auxp t))
		(add-binding var init)))
      (values (nreverse new-lambda-list) v-decls env))))

(defun collect-lambda-list-variables (lambda-list)
  (let ((vars ()))
    ;; Collect all the variables bound by this lambda list, for the call to
    ;; parse-declarations.
    (parse-lambda-list 
     lambda-list
     :required #'(lambda (var) (push var vars))
     :optional #'(lambda (var init initp svar svar-p)
		   (declare (ignore init initp))
		   (push var vars)
		   (when svar-p (push svar vars)))
     :rest #'(lambda (var) (push var vars))
     :keyp #'(lambda () nil)
     :key #'(lambda (var key init initp svar svar-p)
	      (declare (ignore key init initp))
	      (push var vars)
	      (when svar-p (push svar vars)))
     :allow-other-keys-p #'(lambda () nil)
     :aux #'(lambda (var init initp)
	      (declare (ignore init initp))
	      (push var vars)))
    (nreverse vars)))

(defun ncollect-applicable-decls (name parsed-decls)
  (do ((applicable ())
       (nonapplicable ()))
      ((endp parsed-decls)
       (values (nreverse applicable) (nreverse nonapplicable)))
    (if (equal name (caar parsed-decls))
	(rotatef parsed-decls (cdr parsed-decls) applicable)
	(rotatef parsed-decls (cdr parsed-decls) nonapplicable))))

(eval-when (compile load eval)

(defun make-declarations (declspecs)
  (when declspecs `((declare ,@declspecs))))

)

(defun walk-lambda (form env walker)
  (let ((newform (transform-lambda-to-let form
					  env
					  nil
					  #'(lambda (form env)
					      (walk-form-1 form env walker)))))
    (if (eq newform form)
	(walk-call (walk-function-1 (car form) env walker)
		   (cdr form)
		   env
		   walker)
	(walk-form-1 newform env walker))))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Defining walk handlers
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define-translator-property walker-function #'identity)

(defun special-form-walker (name &optional env)
  (multiple-value-bind (usage boundp info)
      (translator-function-information name env)
    ;; If name is locally bound or it is a notinline function, don't use
    ;; specialized walker.
    (unless (or boundp
		(and (member usage '(nil :function))
		     (eq 'notinline (cdr (assoc 'inline info)))))
      (or (walker-function name env)
	  (when (eq usage :special-form)
	    (unknown-special-form-error name))))))

;;; This is not a walk-error, this is a bug in the walker itself.
(defun unknown-special-form-error (name)
  (error "~S doesn't know how to process the special form ~S."
	 'walk-form name))

(defmacro defwalk (name lambda-list &body body)
  (let ((fname (intern (format nil "Walk ~S" name))))
    `(progn
       (eval-when (compile)
	 (print-progress-message "Walker" ',name))
       (defun ,fname ,@(cdr (expand-defwalk name lambda-list body)))
       (setf (walker-function ',name) #',fname))))

(eval-when (compile load eval)

(defvar *whole-var* (gensym))
(defvar *env-var* (gensym))
(defvar *walk-var* (gensym))

(defun expand-defwalk (name lambda-list body)
  (let ((whole nil)
	(env nil)
	(walker nil)
	(ignored-variables ())
	(destructure `((cdr ,*whole-var*))))
    (do ((new ()))
	((atom lambda-list)
	 (setf lambda-list (nreconc new lambda-list)))
      (let ((item (pop lambda-list)))
	(case item
	  (&whole (setf whole (pop lambda-list)))
	  (&environment (setf env (pop lambda-list)))
	  (&walk (setf walker (pop lambda-list)))
	  (t (push item new)))))
    (if (null walker)
	(push *walk-var* ignored-variables)
	(progn
	  (push walker lambda-list)
	  (push *walk-var* destructure)))
    (if (null env)
	(push *env-var* ignored-variables)
	(progn
	  (push env lambda-list)
	  (push *env-var* destructure)))
    (unless (null whole)
      (push whole lambda-list)
      (push *whole-var* destructure))
    (if (cdr destructure)
	(push 'list* destructure)
	(setf destructure (car destructure)))
    (multiple-value-bind (body declspecs doc)
	(parse-body body t)
      `(,name (,*whole-var* ,*env-var* ,*walk-var*)
	   ,@(when doc (list doc))
	   ,@(when ignored-variables
	       `((declare (ignore ,@ignored-variables))))
	   (destructuring-bind ,lambda-list
	       ,destructure
	     ,@(make-declarations declspecs)
	     (block ,(body-block-name name) ,@body))))))
  )


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    The list of special forms in CLtL II
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;  BLOCK
;;;  CATCH
;;;  COMPILER-LET			; removed by X3J13
;;;  DECLARE
;;;  EVAL-WHEN
;;;  FLET
;;;  FUNCTION
;;;  GENERIC-FLET                       ; assumed to be a translator macro
;;;  GENERIC-LABELS                     ; assumed to be a translator macro
;;;  GO
;;;  IF
;;;  LABELS
;;;  LET
;;;  LET*
;;;  LOAD-TIME-VALUE
;;;  LOCALLY
;;;  MACROLET
;;;  MULTIPLE-VALUE-CALL
;;;  MULTIPLE-VALUE-PROG1
;;;  PROGN
;;;  PROGV
;;;  QUOTE
;;;  RETURN-FROM
;;;  SETQ
;;;  SYMBOL-MACROLET
;;;  TAGBODY
;;;  THE
;;;  THROW
;;;  UNWIND-PROTECT
;;;  WITH-ADDED-METHODS			; removed by X3J13

;;; BLOCK
;;;
;;; *** If walked body is constant or variable, block can be eliminated.

(defwalk block (name &body body &environment env &walk walker)
  (check-type name symbol)
  (let ((cenv (translator-augment-environment
	       env :conditional-execution-p t)))
    `(block ,name ,@(walk-progn-1 body cenv walker))))

;;; It is important that walk-block be defined in terms of the walker for
;;; block, rather than the other way around, so that the walker function will
;;; see the whole block form.

(defun walk-block (name body env walker)
  (walk-block-helper name body env walker))

(defun walk-block-helper (name body env walker)
  (let ((form (walk-form-1 `(block ,name ,@body) env walker)))
    (if (and (consp form)
	     (eq (car form) 'block)
	     (consp (cdr form))
	     (eql (cadr form) name))
	(cddr form)
	(list form))))

;;;  CATCH
;;;
;;; *** If walked body is constant or variable, catch can be eliminated, though
;;; *** must of course still evaluate tag.

(defwalk catch (tag &body body &environment env &walk walker)
  (let ((cenv (translator-augment-environment
	       env :conditional-execution-p t)))
    `(catch ,(walk-form-1 tag env walker)
       ,@(walk-progn-1 body cenv walker))))

;;;  COMPILER-LET			; removed by X3J13
;*** commented out to be consistent with translator kernel
;(defwalk compiler-let (bindings &body body &environment env &walk walker)
;  (let ((vars ())
;	(vals ()))
;    (dolist (binding bindings)
;      (if (symbolp binding)
;	  (push binding vars)
;	  (destructuring-bind (var init) binding
;	    (push var vars)
;	    (push init vals))))
;    (setf vars (nreverse vars))
;    (setf vals (nreverse vals))
;    (do ((vals vals (cdr vals)))
;	((endp vals))
;      (setf (car vals)
;	    (funcall (translator-enclose `(lambda () ,(car vals)) env))))
;    (progv vars vals
;      `(compiler-let ,bindings
;	 ,@(walk-progn body env walker)))))

;;;  DECLARE

(defwalk declare (&rest declspecs)
  (declare (ignore declspecs))
  (walk-error "DECLARE form in invalid place."))

;;;  EVAL-WHEN
;;;
;;; *** This is not be right.  Consider that the eval-when may appear in a
;;; *** context where the body is going to be evaluated in the compile time
;;; *** environment.  This code would result in expanding macros using the
;;; *** remote environment's expander functions, and then executing the results
;;; *** in the compile time environment, which is pretty clearly wrong.
;;;
;;; *** Maybe this should only walk in load-eval situations.  But should only
;;; *** walk in load situation when at toplevel.

;;; Just assume that we aren't at top-level.

(defwalk eval-when (situations &body body &environment env &walk walker)
  (if (or (member 'eval situations)
	  (member ':execute situations))
      `(eval-when ,situations ,@(walk-progn-1 body env walker))
      `(eval-when ,situations ,@body)))

;;;  FLET

(defwalk flet (bindings &body body &environment env &walk walker)
  (multiple-value-bind (body declspecs)
      (parse-body body nil)
    (let* ((functions (mapcar #'car bindings))
	   (body-declspecs
	    `(,@(when *function-binding-declarations-hook*
		  (let ((info (mapcan *function-binding-declarations-hook*
				      functions)))
		    (when info
		      `((tx:function-information ,@info)))))
		,@declspecs))
	   (body-env 
	    (translator-augment-environment 
	     env
	     :function (mapcar #'car bindings)
	     :declare body-declspecs))
	   (walked-body 
	    (walk-progn-1 body body-env walker))
	   (walked-bindings 
	    (funcall (or *walk-bound-functions-hook*
			 #'default-walk-bound-functions)
		     bindings env walker body-env)))
      (setq declspecs (walk-add-function-declarations 
		       declspecs functions body-env))
      `(flet ,walked-bindings
	 ,@(make-declarations declspecs)
	 ,@walked-body))))
					   
;;;  FUNCTION

(defwalk function (&whole whole function &environment env &walk walker)
  (if (lambda-expression-p function)
      `(function ,(walk-function-1 function env walker))
      whole))

;;;  GENERIC-FLET
;;;
;;; *** It is assumed that generic-flet and friends are implemented as
;;; *** translator macros.  To do these right requires making use of the method
;;; *** body expansion protocol, which is not well defined at this time.
;
;(defwalk generic-flet (bindings &body body &environment env &walk walker)
;  (let ((walked-bindings
;	 (mapcar #'(lambda (binding)
;		     (walk-generic-function-binding binding env walker))
;		 bindings)))
;    (multiple-value-bind (body declspecs)
;	(parse-body body nil)
;      `(generic-flet ,walked-bindings
;	 ,@(make-declarations declspecs)
;	 ,@(walk-progn body
;		       (translator-augment-environment
;			 env
;			 :function (mapcar #'car walked-bindings)
;			 :declare declspecs)
;		       walker)))))
;
;(defun walk-generic-function-binding (binding env walker)
;  (destructuring-bind (name lambda-list &rest stuff) binding
;    (multiple-value-bind (options methods)
;	(parse-generic-function-options stuff)
;      (list* name lambda-list
;	     (append options
;		     (mapcar #'(lambda (method)
;				 (list* :method
;					(walk-generic-function-method-option
;					     name
;					     (cdr method)
;					     env
;					     walker)))
;			     methods))))))
;
;(defun parse-generic-function-options (stuff)
;  (let ((options ())
;	(methods ()))
;    (dolist (option stuff)
;      (cond ((atom option)
;	     (error "Invalid generic-function option ~S." option))
;	    ((eq (car option) :method)
;	     (push option methods))
;	    (t
;	     (push option options))))
;    (values (nreverse options) (nreverse methods))))
;
;(defun walk-generic-function-method-option (name method-option env walker)
;  (let ((qualifiers ())
;	specialized-lambda-list
;	body
;	lambda-list
;	specializers
;	(unspecialized (list nil)))
;    (loop
;      (cond ((endp method-option)
;	     (error "Invalid method option."))
;	    ((and (car method-option) (atom (car method-option)))
;	     (push (pop method-option) qualifiers))
;	    (t
;	     (setf specialized-lambda-list (pop method-option))
;	     (setf body method-option)
;	     (setf qualifiers (nreverse qualifiers))
;	     (return))))
;    (loop
;      (if (endp specialized-lambda-list) (return)
;	  (let ((parm (pop specialized-lambda-list)))
;	    (cond ((consp parm)
;		   (push (car parm) lambda-list)
;		   (push (cadr parm) specializers))
;		  ((lambda-keyword-p parm)
;		   (setf specializers (nreverse specializers))
;		   (setf lambda-list
;			 (nreconc lambda-list
;				  (cons parm specialized-lambda-list)))
;		   (return))
;		  (t
;		   (push parm lambda-list)
;		   (push unspecialized specializers))))))
;    (let ((lambda (walk-function `(,name ,lambda-list ,@body) env walker)))
;      (setf lambda-list nil)
;      (do ((tail (cadr lambda))
;	   (spec specializers))
;	  ((endp spec)
;	   `(,@qualifiers ,(nreconc lambda-list tail) ,@(cddr lambda)))
;	(let ((parm (pop tail))
;	      (spec (pop spec)))
;	  (cond ((eq spec unspecialized)
;		 (push parm lambda-list))
;		((and (consp spec) (eq (car spec) 'eql))
;		 (push (list parm `(eql ,(walk-form-1 (cadr spec) env walker)))
;		       lambda-list))
;		(t
;		 (push (list parm spec) lambda-list))))))))
;
;;;  GENERIC-LABELS
;
;(defwalk generic-labels (bindings &body body &environment env &walk walker)
;  (let ((names (mapcar #'car bindings)))
;    (multiple-value-bind (body declspecs)
;	(parse-body body nil)
;      (multiple-value-bind (v-decls f-decls r-decls)
;	  (translator-parse-declarations declspecs env :function names)
;	(setf f-decls (copy-list f-decls))
;	(let ((bound-decls ()))
;	  (dolist (name names)
;	    (multiple-value-bind (bound free)
;		(ncollect-applicable-decls name f-decls)
;	      (setf f-decls free)
;	      (setf bound-decls (nconc bound bound-decls))))
;	  (setf env (translator-augment-environment
;		      env
;		      :function names
;		      :declare `((tx:function-information ,@bound-decls))))
;	  `(generic-labels
;	       ,(mapcar #'(lambda (binding)
;			    (walk-generic-function-binding binding
;							   env
;							   walker))
;			bindings)
;	     ,@(make-declarations declspecs)
;	     ,@(walk-progn body
;			   (translator-augment-environment
;			     env
;			     :declare `((tx:declaration-information ,@r-decls)
;					(tx:variable-information ,@v-decls)
;					(tx:function-information ,@f-decls)))
;			   walker)))))))

;;;  GO

(defwalk go (&whole whole tag)
  (if (form-tag-p tag)
      whole
      (walk-error "Invalid GO tag ~S." tag)))

;;;  IF

(defwalk if (test then &optional else &environment env &walk walker)
  (let ((cenv (translator-augment-environment
	       env :conditional-execution-p t)))
    `(if ,(walk-form-1 test env walker)
	 ,(walk-form-1 then cenv walker)
	 ,(walk-form-1 else cenv walker))))

;;;  LABELS

(defwalk labels (bindings &body body &environment env &walk walker)
  (multiple-value-bind (body declspecs)
      (parse-body body nil)
    (let ((bound-decls ())
	  (functions (mapcar #'car bindings)))
      (multiple-value-bind (v-decls f-decls set-r-decls r-decls)
	  (translator-parse-declarations declspecs env
					 :function functions)
	(setf f-decls (copy-list f-decls))
	(dolist (binding bindings)
	  (multiple-value-bind (fn-decls remaining)
	      (ncollect-applicable-decls (car binding) f-decls)
	    (setf f-decls remaining)
	    (setf bound-decls (nconc bound-decls fn-decls))))
	(let* ((info
		(when *function-binding-declarations-hook*
		  (mapcan *function-binding-declarations-hook* functions)))
	       (env 
		(translator-augment-environment
		 env
		 :function functions
		 :declare `((tx:function-information ,@info ,@bound-decls))))
	       (walked-body 
		(walk-progn-1 body
			      (translator-augment-environment
			       env
			       :declare
			       `((tx:variable-information ,@v-decls)
				 (tx:function-information ,@f-decls)
				 (tx:set-declaration-information ,@set-r-decls)
				 (tx:declaration-information ,@r-decls)))
			      walker))
	       (walked-bindings
		(funcall (or *walk-bound-functions-hook*
			     #'default-walk-bound-functions)
			 bindings env walker env)))
	  (setq declspecs (walk-add-function-declarations 
			   declspecs functions env))
	  `(labels ,walked-bindings
	     ,@(make-declarations declspecs)
	     ,@walked-body))))))

;;;  LET
;;;
;;; *** If body is constant or variable not bound by this LET, the bindings can
;;; *** be eliminated.  If body is just a reference to one of the bound
;;; *** variables, just keep and return its initform as a single value.  For
;;; *** both of these, bound declarations have to be stripped out of the set of
;;; *** specified declarations.



(defwalk let (bindings &body body &environment env &walk walker)
  (setf bindings (canonicalize-let/let*-bindings bindings))
  (multiple-value-bind (body declspecs)
      (parse-body body nil)
    (let* ((walked-bindings
	    (mapcar #'(lambda (binding)
			(list (car binding)
			      (walk-form-1 (cadr binding) env walker)))
		    bindings))
	   (variables (mapcar #'car bindings))
	   (body-declspecs
	    `(,@(when *variable-binding-declarations-hook*
		  (let ((info (mapcan *variable-binding-declarations-hook*
				      variables)))
		    (when info
		      `((tx:variable-information ,@info)))))
	      ,@declspecs))
	   (body-env (translator-augment-environment
		      env
		      :variable variables
		      :declare body-declspecs))
	   (walked-body (walk-progn-1 body body-env walker))
	   (variables (mapcar #'car bindings)))
      (setq declspecs (walk-add-declarations declspecs variables body-env))
      `(let ,walked-bindings
	 ,@(make-declarations declspecs)
	 ,@walked-body))))

(defun canonicalize-let/let*-bindings (bindings)
  (mapcar #'(lambda (binding)
	      (if (atom binding)
		  (list binding nil)
		  (if (null (cdr binding))
		      (list (car binding) nil)
		      binding)))
	  bindings))

;;;  LET*
;;;
;;; *** If body is constant or variable not bound by let*, the last initform
;;; *** can be moved into the body.  This process could iterate.  If body is
;;; *** just the last variable bound, then initform can be moved into the body
;;; *** and returned as a single value.  For body of these, bound declarations
;;; *** have to be stripped out of the set of specified declarations.

(defwalk let* (bindings &body body &environment env &walk walker)
  (setf bindings (canonicalize-let/let*-bindings bindings))
  (multiple-value-bind (body declspecs)
      (parse-body body nil)
    (multiple-value-bind (v-decls f-decls set-r-decls r-decls)
	(translator-parse-declarations declspecs env
				       :variable (mapcar #'car bindings))
      (setf v-decls (copy-list v-decls))
      (let ((walked-bindings ()))
	(dolist (binding bindings)
	  (destructuring-bind (var init) binding
	    (push `(,var ,(walk-form-1 init env walker)) walked-bindings)
	    (multiple-value-bind (bound free)
		(ncollect-applicable-decls var v-decls)
	      (setf v-decls free)
	      (setf env (translator-augment-environment
			 env
			 :variable (list var)
			 :declare
			 `((tx:variable-information
			    ,@(when *variable-binding-declarations-hook*
				(funcall *variable-binding-declarations-hook*
					 var))
			    ,@bound)))))))
	(let* ((body-env (translator-augment-environment
			  env
			  :declare
			  `((tx:variable-information ,@v-decls)
			    (tx:function-information ,@f-decls)
			    (tx:set-declaration-information ,@set-r-decls)
			    (tx:declaration-information ,@r-decls))))
	       (walked-body (walk-progn-1 body body-env walker))
	       (variables (mapcar #'car bindings)))
	  (setq declspecs (walk-add-declarations declspecs variables body-env))
	  `(let* ,(nreverse walked-bindings)
	     ,@(make-declarations declspecs)
	     ,@walked-body))))))

;;;  LOAD-TIME-VALUE

(defwalk load-time-value
    (form &optional read-only-p &environment env &walk walker)
  `(load-time-value ,(walk-form-1 form env walker) ,read-only-p))

;;;  LOCALLY
;;;
;;; *** If body is just constant, transform into progn without declarations.
;;; *** Similarly if body is variable without applicable declarations in the
;;; *** specified declarations (except may need to be careful about safety
;;; *** declaration if variable is special).

(defwalk locally (&body body &environment env &walk walker)
  (multiple-value-bind (body declspecs)
      (parse-body body nil)
    (if (endp declspecs)
	(walk-form-1 `(progn ,@body) env walker)
	`(locally
	     (declare ,@declspecs)
	   ,@(walk-progn-1 body
			   (translator-augment-environment
			    env :declare declspecs)
			   walker)))))

;;;  MACROLET
;;;
;;; *** If body is constant or variable, turn into locally.

(defwalk macrolet (bindings &body body &environment env &walk walker)
  (if (null bindings)
      (walk-form-1 `(locally ,@body) env walker)
      (multiple-value-bind (body declspecs)
	  (parse-body body nil)
	(flet ((make-macro-binding (binding)
		 (destructuring-bind (name lambda-list &body body) binding
		   (list* name
			  (translator-enclose
			   (translator-parse-macro name
						   lambda-list
						   body
						   env)
			   env)
			  (cdr binding)))))
	  `(macrolet ,bindings
	     ,@(make-declarations declspecs)
	     ,@(walk-progn-1 body
			     (translator-augment-environment
			      env
			      :macro (mapcar #'make-macro-binding bindings)
			      :declare declspecs)
			     walker))))))

;;;  MULTIPLE-VALUE-CALL

(defwalk multiple-value-call
         (function &rest arguments &environment env &walk walker)
  `(multiple-value-call ,(walk-form-1 function env walker)
			,@(walk-arguments-1 arguments env walker)))

;;;  MULTIPLE-VALUE-PROG1
;;;
;;; *** If empty body, eliminate mv-prog1.

(defwalk multiple-value-prog1 (result &body body &environment env &walk walker)
  `(multiple-value-prog1
       ,(walk-form-1 result env walker)
     ,@(walk-progn-1 body env walker t)))

;;;  PROGN

(defwalk progn (&body body &environment env &walk walker)
  (cond ((endp body) nil)            ; (progn) => nil
	((endp (cdr body))
	 ;; (progn form) => form
	 (walk-form-1 (car body) env walker))
	(t
	 (let ((forms (mapcar #'(lambda (form)
				  (walk-form-1 form env walker))
			      body)))
	   (flet ((progn-form-p (form)
		    (and (consp form) (eq (car form) 'progn))))
	     (when (member-if #'progn-form-p forms)
	       ;; Flatten out nested progn forms.
	       (do ((newforms ()))
		   ((endp forms) (setf forms (nreverse newforms)))
		 (let ((form (pop forms)))
		   (if (progn-form-p form)
		       (setf newforms (revappend (cdr form) newforms))
		       (push form newforms)))))
	     ;; Remove constants in void positions.
	     (labels ((remove-constants (forms)
			(do ((head forms))
			    ((endp (cdr forms)) head)
			  (if (constant-form-in-progn-p (car forms) env)
			      (return (nconc (ldiff head forms)
					     (remove-constants (cdr forms))))
			      (pop forms)))))
	       (setf forms (remove-constants forms))
	       (if (endp (cdr forms))
		   ;; If only one form left, return it.
		   (car forms)
		   ;; Else collect forms into a progn.
		   `(progn ,@forms))))))))

(defun constant-form-in-progn-p (form env)
  (do ()
      ((not (and (consp form) (eq (car form) 'the)))
       (translator-constantp form env))
    (setf form (third form))))

;;; WALK-PROGN
;;;
;;; A convenience function.  Call this with a list of forms that are to be
;;; treated as if they were in a PROGN context, the environment, and the walk
;;; function.  Returns a list of walked forms. 
;;;
;;; [It is important that walk-progn be defined in terms of the walker for
;;; progn, rather than the other way around, so that the walker function will
;;; see the whole progn form.]

(defun WALK-PROGN (forms env walker &optional (side-effect-only nil) &key
			 ((:setq-hook *walk-setq-hook*) nil)
			 ((:added-declarations-hook
			   *walk-added-declarations-hook*) nil)
			 ((:variable-binding-declarations-hook
			   *variable-binding-declarations-hook*) nil)
			 ((:function-binding-declarations-hook
			   *function-binding-declarations-hook*) nil)
			 ((:walk-bound-functions-hook
			   *walk-bound-functions-hook*) nil))
  (setf env (ensure-translator-environment env))
  (walk-progn-1 forms env walker side-effect-only))

(defun walk-progn-1 (forms env walker &optional (side-effect-only nil))
  (let ((walked (walk-form-1 `(progn ,@forms) env walker)))
    (cond ((not (and (consp walked)
		     (eq (car walked) 'progn)))
	   (if (or (not side-effect-only)
		   (not (constant-form-in-progn-p walked env)))
	       (list walked)
	       ;; If in a non-value location and form is a constant,
	       ;; return no forms as the result.
	       nil))
	  ((or (not side-effect-only)
	       (not (constant-form-in-progn-p (car (last walked)) env)))
	   (cdr walked))
	  (t
	   ;; If in a non-value location and last form is a constant,
	   ;; return list of all but the last form.
	   (butlast (cdr walked))))))

;;;  PROGV

(defwalk progv (vars vals &body body &environment env &walk walker)
  `(progv ,(walk-form-1 vars env walker)
	  ,(walk-form-1 vals env walker)
     ,@(walk-progn-1 body env walker)))

;;;  QUOTE

(defwalk quote (&whole whole form)
  (declare (ignore form))
  whole)

;;;  RETURN-FROM

(defwalk return-from (name &optional value &environment env &walk walker)
  (check-type name symbol)
  `(return-from ,name ,(walk-form-1 value env walker)))

;;;  SETQ

(defwalk setq (&rest pairs &environment env &walk walker)
  (let ((length (length pairs)))
    (cond ((oddp length)
	   (walk-error "Odd number of arguments to ~S." 'setq))
	  ((/= length 2)
	   (walk-form-1 `(progn
			   ,@(do ((pairs pairs)
				  (result () (cons `(setq ,(pop pairs)
							  ,(pop pairs))
						   result)))
				 ((endp pairs) (nreverse result))))
			env
			walker))
	  ((not (symbolp (car pairs)))
	   (walk-error "~S is not a valid place to ~S." (car pairs) 'setq))
	  (t
	   (multiple-value-bind (place macrop)
	       (translator-symbol-macroexpand-1 (car pairs) env)
	     (if macrop
		 (walk-form-1 `(setf ,place ,(cadr pairs)) env walker)
		 (progn
		   (when *walk-setq-hook*
		     (funcall *walk-setq-hook* (car pairs) env))
		   `(setq ,(car pairs)
			  ,(walk-form-1 (cadr pairs) env walker)))))))))

;;;  SYMBOL-MACROLET
;;;
;;; *** If body is constant or variable, turn into locally.

(defwalk symbol-macrolet (bindings &body body &environment env &walk walker)
  (if (null bindings)
      (walk-form-1 `(locally ,@body) env walker)
      (multiple-value-bind (body declspecs)
	  (parse-body body nil)
	`(symbol-macrolet ,bindings
	     ,@(make-declarations declspecs)
	   ,@(walk-progn-1 body
			   (translator-augment-environment
			    env
			    :symbol-macro bindings
			    :declare declspecs)
			   walker)))))

;;;  TAGBODY

(defwalk tagbody (&body body &environment env &walk walker)
  (do ((walked-body ())
       (tagbody-env ())
       (pending ()))
      ((endp body)
       (if (null walked-body)
	   ;; If no tags, then equivelent to progn returning nil.
	   (walk-form-1 `(progn ,@(nreverse pending) nil) env walker)
	   `(tagbody
	      ,@(nreverse walked-body)
	      ,@(when pending
		  (when (and walked-body (null tagbody-env))
		    (setq tagbody-env (translator-augment-environment 
				       env :multiple-execution-p t)))
		  ;; When there are pending forms, walk them in a progn
		  ;; context.  However, ensure that expanded forms don't
		  ;; inadvertently get interpreted as tags, by searching the
		  ;; walked forms for tags and wrapping the forms in a progn
		  ;; if any such appear in the expanded forms.
		  (let ((tail (walk-progn-1 (nreverse pending)
					    (or tagbody-env env) walker t)))
		    (if (some #'form-tag-p tail)
			`((progn ,@tail))
			tail))))))
    (let ((form (pop body)))
      (if (not (form-tag-p form))
	  (push form pending)
	  (progn
	    (when (and walked-body (null tagbody-env))
	      (setq tagbody-env (translator-augment-environment 
				 env :multiple-execution-p t)))
	    ;; Walk pending forms as a progn and add to the walked body,
	    ;; ensuring that there is a progn around the forms (see above).
	    (let ((tail (walk-progn-1 (nreverse pending)
				      (or tagbody-env env) walker t)))
	      (if (some #'form-tag-p tail)
		  (push `(progn ,@tail) walked-body)
		  (setf walked-body (revappend tail walked-body))))
	    ;; Add tag to the walked body.
	    (push form walked-body)
	    (setf pending nil))))))

(defun form-tag-p (form)
  (or (symbolp form)
      (integerp form)))

;;; It is important that walk-tagbody be defined in terms of the walker for
;;; tagbody, rather than the other way around, so that the walker function will
;;; see the whole tagbody form.

(defun walk-tagbody (forms env walker &optional (value-producing t))
  (let ((walked (walk-form-1 `(tagbody ,@forms) env walker)))
    (if (not (consp walked))
	(list walked)
	(case (car walked)
	  (tagbody (cdr walked))
	  (progn
	    ;; When result is a progn, it indicates that there were no tags in
	    ;; the body.  In such a case, the result is a walked progn with a
	    ;; final form of Nil.  If not in a value producing position, strip
	    ;; off that final Nil.  If the result is a single-form progn,
	    ;; return just a list of that final form.  However, if anything
	    ;; that looks like a tag is present, leave the progn in place.
	    (flet ((handle-tags (body)
		     (if (some #'form-tag-p body)
			 `((progn ,@body))
			 body)))
	      (handle-tags (if value-producing
			       (cdr walked)
			       (butlast (cdr walked))))))
	  (otherwise (list walked))))))

;;;  THE

(defwalk the (type form &environment env &walk walker)
  `(the ,type ,(walk-form-1 form env walker)))

;;;  THROW

(defwalk throw (tag &optional value &environment env &walk walker)
  `(throw ,(walk-form-1 tag env walker)
	  ,(walk-form-1 value env walker)))

;;;  UNWIND-PROTECT
;;;
;;; *** If cleanup is constant, eliminate unwind-protect.

(defwalk unwind-protect (protected &body cleanup &environment env &walk walker)
  `(unwind-protect
       ,(walk-form-1 protected env walker)
     ,@(walk-progn-1 cleanup env walker t)))

;;;  with-added-methods			; removed by X3J13



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Additional walker special forms
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;; Note that in general we should have a walker here for anything that the
;;; translator defines as either a special form (by using deftranslate) or a
;;; toplevel form (by using define-toplevel-form).
;;;
;;; The following names have deftranslate definitions without a walker entry
;;; being defined here.  I believe these are all ok since they only appear as
;;; part of the expansion of some other deftranslate.  However, perhaps there
;;; should be something here to generate a warning if they get encountered.
;;;
;;;  DONT-RETURN
;;;  NAMED-FUNCTION
;;;
;;; The following Common Lisp macros are treated as special forms by the
;;; translator.  Give the translator handlers a chance at them by treating them
;;; as special forms here too.
;;;
;;;  AND
;;;  COND
;;;  DEFUN
;;;  DO
;;;  DO*
;;;  LOOP
;;;  MULTIPLE-VALUE-BIND
;;;  MULTIPLE-VALUE-LIST
;;;  MULTIPLE-VALUE-SETQ
;;;  NTH-VALUE
;;;  OR
;;;  PROG1
;;;  PROG2
;;;
;;; The following Common Lisp macros are treated as special forms by this
;;; walker, even though the translator does not currently treat them as
;;; special forms.
;;;
;;;  CASE
;;;  DOLIST
;;;  DOTIMES
;;;  ECASE
;;;  ETYPECASE
;;;  PSETQ
;;;  TYPECASE
;;;  UNLESS
;;;  WHEN
;;;
;;; The following Common Lisp functions are treated as special forms by this
;;; walker.
;;;
;;;  FUNCALL
;;;
;;; The following Chestnut specific special forms, provided to the user
;;; as extensions to common lisp, are handled by this walker.
;;;
;;;  TX:C-LINES
;;;  TX:CPP-CONDITIONAL
;;;  TRUN:WITH-AREA
;;;  TX:WITH-LOCAL-ALLOCATION
;;;
;;; The following Chestnut specific special forms, which occur in the
;;; translator macroexpansions of Common Lisp macros, are handled
;;; by this walker.
;;;
;;; TRUN:ESTABLISH-SPECIAL-VARIABLE
;;; TRUN:UNBOUND-SPECIAL-P
;;; TIMPL::TRANSLATOR-DEFUN
;;; TIMPL::WHILE
;;;
;;; The following Chestnut specific special forms, which occur in the
;;; deftranslate expansions of Common Lisp macros, are handled
;;; by this walker.
;;;
;;; TRUN:LINK-VARIABLE
;;; TRUN:LINK-FUNCTION
;;; TRUN:LINK-SETF-FUNCTION
;;;
;;; The following Common Lisp macros are not treated as special forms by the
;;; this code walker.
;;;
;;;  ASSERT                        ;setf must receive unexpanded places
;;;  CALL-METHOD
;;;  CCASE                         ;setf must receive unexpanded place
;;;  CHECK-TYPE                    ;setf must receive unexpanded place
;;;  CTYPECASE                     ;setf must receive unexpanded place
;;;  DECF                          ;setf must receive unexpanded place
;;;  DECLAIM
;;;  DEFCLASS
;;;  DEFCONSTANT
;;;  DEFGENERIC
;;;  DEFINE-COMPILER-MACRO
;;;  DEFINE-CONDITION
;;;  DEFINE-DECLARATION
;;;  DEFINE-METHOD-COMBINATION
;;;  DEFINE-MODIFY-MACRO
;;;  DEFINE-SETF-METHOD
;;;  DEFMACRO
;;;  DEFMETHOD
;;;  DEFPACKAGE
;;;  DEFPARAMETER
;;;  DEFSETF
;;;  DEFSTRUCT
;;;  DEFTYPE
;;;  DEFVAR
;;;  DESTRUCTURING-BIND
;;;  FORMATTER
;;;  GENERIC-FUNCTION
;;;  HANDLER-BIND
;;;  HANDLER-CASE
;;;  IGNORE-ERRORS
;;;  IN-PACKAGE
;;;  INCF                          ;setf must receive unexpanded place
;;;  LOOP-FINISH
;;;  POP                           ;setf must receive unexpanded place
;;;  PPRINT-EXIT-IF-LIST-EXHAUSTED
;;;  PPRINT-LOGICAL-BLOCK
;;;  PPRINT-POP
;;;  PRINT-UNREADABLE-OBJECT
;;;  PROG
;;;  PROG*
;;;  PSETF                         ;setf must receive unexpanded places
;;;  PUSH                          ;setf must receive unexpanded place
;;;  PUSHNEW                       ;setf must receive unexpanded place
;;;  REMF                          ;setf must receive unexpanded place
;;;  RESTART-BIND
;;;  RESTART-CASE
;;;  RETURN
;;;  ROTATEF                       ;setf must receive unexpanded places
;;;  SETF                          ;setf must receive unexpanded places
;;;  SHIFTF                        ;setf must receive unexpanded places
;;;  STEP
;;;  TIME
;;;  TRACE
;;;  UNTRACE
;;;  WITH-ACCESSORS
;;;  WITH-COMPILATION-UNIT
;;;  WITH-CONDITION-RESTARTS
;;;  WITH-HASH-TABLE-ITERATOR
;;;  WITH-INPUT-FROM-STRING
;;;  WITH-OPEN-FILE
;;;  WITH-OPEN-STREAM
;;;  WITH-OUTPUT-TO-STRING
;;;  WITH-PACKAGE-ITERATOR
;;;  WITH-SIMPLE-RESTART
;;;  WITH-SLOTS
;;;  WITH-STANDARD-IO-SYNTAX

;;;  AND

(defwalk and (&rest forms &environment env &walk walker)
  (cond ((endp forms) (walk-form-1 't env walker))
	((endp (cdr forms)) (walk-form-1 (car forms) env walker))
	(t 
	 (let ((cenv (translator-augment-environment
		      env :conditional-execution-p t)))
	   `(and ,(walk-form-1 (car forms) env walker)
		 ,@(walk-arguments-1 (cdr forms) cenv walker))))))

;;;  TX:C-LINES

(defwalk tx:c-lines (&whole form &rest strings)
  (declare (ignore strings))        ;*** perhaps should error check the strings
  form)

;;;  CASE

(defun walk-case-form (name item clauses env walker)
  (let ((cenv (translator-augment-environment
	       env :conditional-execution-p t)))
    (when (and clauses (cdr clauses)
	       (or (symbolp item)
		   (translator-constantp item env)))
      ;; Without this, the read-once optimization is confused
      (walk-form-1 item env walker))
    (list* name
	   (walk-form-1 item env walker)
	   (mapcar #'(lambda (clause)
		       (destructuring-bind (key &body body) clause
			 (cons key (walk-progn-1 body cenv walker))))
		   clauses))))

(defwalk case (item &rest clauses &environment env &walk walker)
  (walk-case-form 'case item clauses env walker))

;;;  COND

(defwalk cond (&rest clauses &environment env &walk walker)
  (cond ((endp clauses)
	 `(cond))
	((and (endp (cdr clauses)) (null (cdar clauses)))
	 `(cond (,(walk-form-1 (caar clauses) env walker))))
	(t
	 (let ((cenv (translator-augment-environment
		      env :conditional-execution-p t)))
	   `(cond (,(walk-form-1 (caar clauses) env walker)
		   ,@(when (cdar clauses)
		       (walk-progn-1 (cdar clauses) cenv walker)))
		  ,@(mapcar #'(lambda (clause)
				(destructuring-bind (test &rest forms)
				    clause
				  (cons (walk-form-1 test cenv walker)
					(when forms 
					  (walk-progn-1 forms cenv walker)))))
			    (cdr clauses)))))))

;;;  TX:CPP-CONDITIONAL

(defwalk tx:cpp-conditional (&rest clauses &environment env &walk walker)
  `(tx:cpp-conditional
     ,@(mapcar #'(lambda (clause)
		   (cons (car clause)    ;*** error check conditional?
			 (walk-progn-1 (cdr clause) env walker)))
	       clauses)))

;;;  DEFUN

(defwalk defun (name lambda-list &body body &environment env &walk walker)
  `(defun ,@(walk-function-1 (list* name lambda-list body)
			     (translator-augment-environment
			      env
			      :function (list name))
			     walker)))

;;;  DO
;;;
;;; This is kind of awkward.  The problem is that the BLOCK should be seen by
;;; the walker, but it is desirable to avoid actually expanding the macro since
;;; the translator performs idiomatic handling of DO, producing more readable
;;; translated code than is currently possible when operating on the expansion.
;;;
;;; The way this problem is solved is to define a translator macro called
;;; DO-UNBLOCKED, whose expansion is an appropriate expansion for implementing
;;; the portion of DO that appears inside the BLOCK, along with a walker for
;;; DO-UNBLOCKED.  The walker for DO effectively walks the form
;;;   `(block nil (do-unblocked . <do arguments>))
;;; and looks at the result.  If the result has the same pattern, then the
;;; BLOCK is stripped off and the DO-UNBLOCKED is replaced with DO.  Otherwise,
;;; the walked form is returned.

(defmacro declare-blocked-form (name unblocked-name)
  (let ((entry (gensym)))
    `(let ((,entry (assoc ',unblocked-name *blocked-forms*)))
       (when (null ,entry)
	 (setf ,entry (list ',unblocked-name))
	 (push ,entry *blocked-forms*))
       (setf (cdr ,entry) (list ',name)))))

(defparameter *blocked-forms* nil)

(defun transform-blocked-form (form env)
  (declare (ignore env))
  (let ((entry (and (consp form)
		    (assoc (car form) *blocked-forms*))))
    (if (null entry)
	(values form nil)
	(values `(,(cadr entry) ,@(cdr form)) t))))

(defun walk-blocked-form (form env walker)
  (let ((walked (walk-block-helper nil (list form) env walker)))
    (if (or (atom walked) (cdr walked))
	walked
	(multiple-value-bind (new transformedp)
	    (transform-blocked-form (car walked) env)
	  (if transformedp
	      new
	      `(block nil ,@walked))))))

(defwalk do (bindings (test &rest result) &body body
		      &environment env &walk walker)
  (walk-blocked-form `(do-unblocked ,bindings (,test ,@result) ,@body)
		     env
		     walker))

(declare-blocked-form do do-unblocked)

(define-translator-macro do-unblocked
      (bindings (test &rest result) &body body &environment env)
  (expand-unblocked-do-macro bindings test result body env 'let 'psetq))

(defun expand-unblocked-do-macro (bindings test result body env binder stepper)
  (declare (ignore env))
  (setf bindings (canonicalize-do/do*-bindings bindings))
  (multiple-value-bind (body declspecs) (parse-body body nil)
    (let ((loop-label (make-symbol "LOOP")))
      `(,binder ,(mapcar #'(lambda (binding)
			     (destructuring-bind (var &optional init step)
				 binding
			       (declare (ignore step))
			       (list var init)))
			 bindings)
	 ,@(make-declarations declspecs)
	 (tagbody
	   ,loop-label
	   (when (not ,test)
	     (tagbody ,@body)
	     (,stepper ,@(mapcan #'(lambda (binding)
				     (destructuring-bind
					 (var &optional init (step nil stepp))
					 binding
				       (declare (ignore init))
				       (when stepp (list var step))))
				 bindings))
	     (go ,loop-label)))
	 ,@(or result '(nil))))))

(defwalk do-unblocked
    (bindings (test &rest result) &body body &environment env &walk walker)
  (setf bindings (canonicalize-do/do*-bindings bindings))
  (multiple-value-bind (body declspecs) (parse-body body nil)
    (let* ((variables (mapcar #'car bindings))
	   (body-declspecs
	    `(,@(when *variable-binding-declarations-hook*
		  `((tx:variable-information
		     ,@(mapcan *variable-binding-declarations-hook*
			       variables))))
	      ,@declspecs))
	   (body-env (translator-augment-environment
		      env
		      :variable variables
		      :declare body-declspecs
		      :multiple-execution-p t)))
      (flet ((process-binding (binding)
	       (destructuring-bind (var &optional init (step nil stepp))
		   binding
		 (list* var
			(walk-form-1 init env walker)
			(when stepp
			  (when *walk-setq-hook*
			    (funcall *walk-setq-hook* var body-env))
			  (list (walk-form-1 step body-env walker)))))))
	(let* ((walked-bindings (mapcar #'process-binding bindings))
	       (walked-end-form `(,(walk-form-1 test body-env walker)
				  ,@(walk-progn-1 result body-env walker)))
	       (walked-body (walk-tagbody body body-env walker nil))
	       (vars (mapcar #'car bindings)))
	  (setq declspecs (walk-add-declarations declspecs vars body-env))
	  `(do-unblocked ,walked-bindings
	       ,walked-end-form
	     ,@(make-declarations declspecs)
	     ,@walked-body))))))

(defun canonicalize-do/do*-bindings (bindings)
  (mapcar #'(lambda (binding)
	      (if (symbolp binding)
		  (list binding nil)
		  binding))
	  bindings))

;;;  DO*
;;;
;;; This has the same awkwardness as DO, and is treated the same way.

(defwalk do* (bindings (test &rest result) &body body
		       &environment env &walk walker)
  (walk-blocked-form `(do*-unblocked ,bindings (,test ,@result) ,@body)
		     env
		     walker))

(declare-blocked-form do* do*-unblocked)

(define-translator-macro do*-unblocked
      (bindings (test &rest result) &body body &environment env)
  (expand-unblocked-do-macro bindings test result body env 'let* 'setq))

(defwalk do*-unblocked
    (bindings (test &rest result) &body body &environment env &walk walker)
  (setf bindings (canonicalize-do/do*-bindings bindings))
  (multiple-value-bind (body declspecs) (parse-body body nil)
    (multiple-value-bind (var-decls fun-decls set-decls decls)
	(translator-parse-declarations declspecs env
				       :variable (mapcar #'car bindings))
      (setf var-decls (copy-list var-decls))
      (let ((walked-bindings ()) (mep-p t))
	(dolist (binding bindings)
	  (destructuring-bind (var &optional init (step nil stepp))
	      binding
	    (push (list* var
			 (walk-form-1 init env walker)
			 (when stepp (list step)))
		  walked-bindings)
	    (multiple-value-bind (bound free)
		(ncollect-applicable-decls var var-decls)
	      (setq var-decls free)
	      (setq env (translator-augment-environment
			 env
			 :variable (list var)
			 :declare
			 `((tx:variable-information
			    ,@(when *variable-binding-declarations-hook*
				(funcall *variable-binding-declarations-hook*
					 var))
			    ,@bound))
			 :multiple-execution-p (prog1 mep-p 
						 (setq mep-p nil)))))))
	(setq env (translator-augment-environment
		   env
		   :declare `((tx:variable-information ,@var-decls)
			      (tx:function-information ,@fun-decls)
			      (tx:set-declaration-information ,@set-decls)
			      (tx:declaration-information ,@decls))
		   :multiple-execution-p (prog1 mep-p 
					   (setq mep-p nil))))
	(setq walked-bindings (nreverse walked-bindings))
	;; Walk the update forms
	(dolist (binding walked-bindings)
	  (when (cddr binding)
	    (when *walk-setq-hook*
	      (funcall *walk-setq-hook* (car binding) env))
	    (setf (caddr binding)
		  (walk-form-1 (caddr binding) env walker))))
	(let* ((walked-end-form `(,(walk-form-1 test env walker)
				  ,@(walk-progn-1 result env walker)))
	       (walked-body (walk-tagbody body env walker nil))
	       (vars (mapcar #'car bindings)))
	  (setq declspecs (walk-add-declarations declspecs vars env))
	  `(do*-unblocked ,walked-bindings
	       ,walked-end-form
	     ,@(make-declarations declspecs)
	     ,@walked-body))))))

;;;  DOLIST
;;;
;;; This has the same awkwardness as DO, and is treated the same way.

(defwalk dolist ((item list &optional result) &body body
		 &environment env &walk walker)
  (walk-blocked-form `(dolist-unblocked (,item ,list ,result) ,@body)
		     env
		     walker))

(declare-blocked-form dolist dolist-unblocked)

(define-translator-macro dolist-unblocked
    ((item list &optional result) &body body)
  (let ((tail (make-symbol "TEMP")))
    `(do*-unblocked ((,tail ,list)
		     (,item (car ,tail)))
         ((atom ,tail) ,result)
       ,@body)))

(defwalk dolist-unblocked
    ((item list &optional result) &body body &environment env &walk walker)
  (multiple-value-bind (body declspecs) (parse-body body nil)
    (let* ((list (walk-form-1 list env walker))
	   (vars (list item))
	   (bind-declspecs
	    `(,@(when *variable-binding-declarations-hook*
		  `((tx:variable-information
		     ,@(mapcan *variable-binding-declarations-hook*
			       vars))))
	      ,@declspecs))
	   (env (translator-augment-environment env
						:variable vars
						:declare bind-declspecs))
	   (walked-result
	    (progn
	      (when *walk-setq-hook*
		(funcall *walk-setq-hook* item env))
	      (walk-form-1 result env walker)))
	   (body-env (translator-augment-environment
		      env :multiple-execution-p t))
	   (walked-body (walk-tagbody body body-env walker nil)))
      (setq declspecs (walk-add-declarations declspecs vars env))
      `(dolist-unblocked (,item ,list ,walked-result)
	 ,@(make-declarations declspecs)
	 ,@walked-body))))

;;;  DOTIMES
;;;
;;; This has the same awkwardness as DO, and is treated the same way.

(defwalk dotimes ((item end &optional result) &body body
		  &environment env &walk walker)
  (walk-blocked-form `(dotimes-unblocked (,item ,end ,result) ,@body)
		     env
		     walker))

(declare-blocked-form dotimes dotimes-unblocked)

(define-translator-macro dotimes-unblocked
    ((item end &optional result) &body body &environment env)
  (if (translator-constantp end env)
      `(do-unblocked ((,item 0 (1+ ,item)))
	   ((<= ,end ,item) ,result)
	 ,@body)
      (let ((end-var (make-symbol "TEMP")))
	`(do-unblocked ((,end-var ,end)
			(,item 0 (1+ ,item)))
	     ((<= ,end-var ,item) ,result)
	   ,@body))))

(defwalk dotimes-unblocked
    ((index end &optional result) &body body &environment env &walk walker)
  (multiple-value-bind (body declspecs) (parse-body body nil)
    (let* ((end (walk-form-1 end env walker))
	   (vars (list index))
	   (bind-declspecs
	    `(,@(when *variable-binding-declarations-hook*
		  `((tx:variable-information
		     ,@(mapcan *variable-binding-declarations-hook*
			       vars))))
	      ,@declspecs))
	   (env (translator-augment-environment env
						:variable vars
						:declare bind-declspecs))
	   (walked-result
	    (progn
	      (when *walk-setq-hook*
		(funcall *walk-setq-hook* index env))
	      (walk-form-1 result env walker)))
	   (body-env (translator-augment-environment
		      env :multiple-execution-p t))
	   (walked-body (walk-tagbody body body-env walker nil)))
      (setq declspecs (walk-add-declarations declspecs vars env))
      `(dotimes-unblocked (,index ,end ,walked-result)
	 ,@(make-declarations declspecs)
	 ,@walked-body))))

;;;  ECASE

(defwalk ecase (item &rest clauses &environment env &walk walker)
  (walk-case-form 'ecase item clauses env walker))

;;; ESTABLISH-SPECIAL-VARIABLE

(defwalk trun:establish-special-variable
  (variable &environment env &walk walker)
  `(trun:establish-special-variable ,(walk-form-1 variable env walker)))

;;;  ETYPECASE

(defwalk etypecase (item &rest clauses &environment env &walk walker)
  (walk-case-form 'etypecase item clauses env walker))

;;; TIMPL::FOREVER
(defwalk timpl::forever (&body body &environment env &walk walker)
  `(timpl::forever ,@(walk-tagbody body env walker nil)))

;;;  FUNCALL

(defwalk funcall (function &rest arguments &environment env &walk walker)
  (let ((walked-function (walk-form-1 function env walker)))
    (cond ((not (consp walked-function))
	   `(funcall ,walked-function
		     ,@(walk-arguments-1 arguments env walker)))
	  ((and (member (car walked-function) '(function quote))
		(symbolp (cadr walked-function)))
	   (let ((name (cadr function)))
	     (multiple-value-bind (usage boundp info)
		 (translator-function-information name env)
	       (declare (ignore info))
	       (if (and (member usage '(:function nil))
			(or (not boundp)
			    (eq (car walked-function) 'function)))
		   ;; (funcall #'name . args) => (name . args).  Similarly
		   ;; (funcall 'name . args) => (name . args) when name is not
		   ;; locally bound.
		   (walk-form-1 (cons name arguments) env walker)
		   ;; Form is (funcall 'name . args) and there is a local
		   ;; binding of name (or name is not a function, and the form
		   ;; is invalid).  I'd like to be able to try compiler
		   ;; macroexpanding the form, but that isn't really safe,
		   ;; since the expansion could be in terms of the original
		   ;; function with simpler arguments.  An example where we
		   ;; could potentially get such a situation is
		   ;; (+ a b c) => (+ (+ a b) c)
		   `(funcall ,walked-function
			     ,@(walk-arguments-1 arguments env walker))))))
	  ((eq (car walked-function) 'function)
	   (multiple-value-bind (newform macrop)
	       (translator-compiler-macroexpand-1
		 `(funcall ,walked-function ,@arguments) env)
	     (cond (macrop (walk-form-1 newform env walker))
		   ((lambda-expression-p (cadr walked-function))
		    (let* ((lambda-form `(,(cadr walked-function) ,@arguments))
			   (newform (transform-lambda-to-let
				      lambda-form
				      env
				      nil
				      #'(lambda (form env)
					  (walk-form-1 form env walker)))))
		      (if (eq lambda-form newform)
			  `(funcall ,walked-function
				    ,@(walk-arguments-1 arguments env walker))
			  (walk-form-1 newform env walker))))
		   (t
		    `(funcall ,walked-function
			      ,@(walk-arguments-1 arguments env walker))))))
	  (t
	   `(funcall ,walked-function
		     ,@(walk-arguments-1 arguments env walker))))))

;;; TIMPL::HARD-BLOCK

(defwalk timpl::hard-block (name catch-tag &body body
			    &environment env &walk walker)
  (check-type name symbol)
  `(timpl::hard-block ,name ,catch-tag ,@(walk-progn-1 body env walker)))

;;; TRUN:LINK-VARIABLE
;;; TRUN:LINK-FUNCTION
;;; TRUN:LINK-SETF-FUNCTION

(defmacro defwalk-ignore (name)
  `(defwalk ,name (&whole whole &rest forms)
     (declare (ignore forms))
     whole))

(defwalk-ignore TRUN:LINK-VARIABLE)
(defwalk-ignore TRUN:LINK-FUNCTION)
(defwalk-ignore TRUN:LINK-SETF-FUNCTION)
(defwalk-ignore timpl::translator-foreign-size-of)
(defwalk-ignore timpl::dont-return)
(defwalk-ignore tx:foreign-function)
(defwalk-ignore tx:function-object)

;;;  LOOP
;;;
;;; This has the same awkwardness as DO, and is treated the same way.

(defwalk loop (&whole loop &body body &environment env &walk walker)
  (if (notany #'form-tag-p body)
      (walk-blocked-form `(loop-unblocked ,@body)
			 env
			 walker)
      ;; Let us pray.
      (walk-form-1 (translator-macroexpand-1 loop env) env walker)))
      
(declare-blocked-form loop loop-unblocked)

(define-translator-macro loop-unblocked (&body body)
  (let ((loop (make-symbol "LOOP")))
    `(tagbody ,loop ,@body (go ,loop))))

(defwalk loop-unblocked (&body body &environment env &walk walker)
  `(loop-unblocked ,@(walk-tagbody body env walker nil)))


;;;  MULTIPLE-VALUE-BIND

(defwalk multiple-value-bind (vars init &body body
				   &environment env &walk walker)
  (cond ((endp vars)
	 ;; Wrap with let to hoist out of top-level.
	 (walk-form-1 `(let () ,init (locally ,@body)) env walker))
	((endp (cdr vars))
	 (walk-form-1 `(let ((,(car vars) ,init)) ,@body) env walker))
	(t
	 (multiple-value-bind (body declspecs)
	     (parse-body body nil)
	   (let* ((walked-values (walk-form-1 init env walker))
		  (bind-declspecs
		   `(,@(when *variable-binding-declarations-hook*
			 `((tx:variable-information
			    ,@(mapcan *variable-binding-declarations-hook*
				      vars))))
		       ,@declspecs))
		  (body-env (translator-augment-environment
			     env
			     :variable vars
			     :declare bind-declspecs))
		  (walked-body (walk-progn-1 body body-env walker)))
	     (setq declspecs (walk-add-declarations declspecs vars body-env))
	     `(multiple-value-bind ,vars
		  ,walked-values
		,@(make-declarations declspecs)
		,@walked-body))))))

;;;  MULTIPLE-VALUE-LIST

(defwalk multiple-value-list (form &environment env &walk walker)
  `(multiple-value-list ,(walk-form-1 form env walker)))

;;;  MULTIPLE-VALUE-SETQ

(defwalk multiple-value-setq
         ((&rest vars) value-form &environment env &walk walker)
  (cond ((endp vars)
	 (walk-form-1 `(values ,value-form) env walker))
	((endp (cdr vars))
	 (walk-form-1 `(setq ,(car vars) ,value-form) env walker))
	(t
	 (let* ((macrop nil)
		(non-symbols nil)
		(places (mapcar #'(lambda (var)
				    (check-type var symbol)
				    (multiple-value-bind (expanded macro)
					(translator-symbol-macroexpand-1 var
									 env)
				      (when macro
					(setf macrop t)
					(when (not (symbolp expanded))
					  (setf non-symbols t)))
				      expanded))
				vars)))
	   (labels ((process-places (places stores setters env)
		      (if (endp places)
			  `(multiple-value-bind
			       ,(setf stores (nreverse stores))
			       ,value-form
			     (prog1 ,(car stores)
			       ,@(nreverse setters)))
			  ;; *** Does this need to do anything about multiple
			  ;; *** store variables?
			  (multiple-value-bind (vars vals store setter)
			      (translator-get-setf-method (car places) env)
			    `(let ,(mapcar #'list vars vals)
			       ,(process-places (cdr places)
						(cons (car store) stores)
						(cons setter setters)
						env))))))
	     (cond ((not macrop)
		    (when *walk-setq-hook*
		      (dolist (var vars)
			(funcall *walk-setq-hook* var env)))
		    `(multiple-value-setq ,vars
		       ,(walk-form-1 value-form env walker)))
		   ((not non-symbols)
		    (walk-form-1 `(multiple-value-setq ,places ,value-form)
				 env
				 walker))
		   (t
		    (walk-form-1 (process-places vars () () env)
				 env
				 walker))))))))

;;;  NTH-VALUE

(defwalk nth-value (index value-form &environment env &walk walker)
  `(nth-value ,(walk-form-1 index env walker)
	      ,(walk-form-1 value-form env walker)))

;;;  OR

(defwalk or (&rest forms &environment env &walk walker)
  (cond ((endp forms) (walk-form-1 'nil env walker))
	((endp (cdr forms)) (walk-form-1 (car forms) env walker))
	(t 
	 (let ((cenv (translator-augment-environment
		      env :conditional-execution-p t)))
	   `(or ,(walk-form-1 (car forms) env walker)
		,@(walk-arguments-1 (cdr forms) cenv walker))))))

;;;  PROG1

(defwalk prog1 (value-form &rest forms &environment env &walk walker)
  (setf forms (walk-progn-1 forms env walker t))
  (if (endp forms)
      (walk-form-1 `(values ,value-form) env walker)
      `(prog1 ,(walk-form-1 value-form env walker) ,@forms)))

;;;  PROG2

(defwalk prog2 (form1 value-form &rest forms &environment env &walk walker)
  (let ((first (walk-form-1 form1 env walker)))
    (if (constant-form-in-progn-p first env)
	(walk-form-1 `(prog1 ,value-form ,@forms) env walker)
	`(prog2
	   ,first
	   ,(walk-form-1 value-form env walker)
	   ,@(walk-progn-1 forms env walker t)))))
  
;;;  PSETQ

(defwalk psetq (&rest pairs &environment env &walk walker)
  (let ((length (length pairs)))
    (cond ((oddp length)
	   (walk-error "Odd number of arguments to ~S." 'psetq))
	  ((zerop length) '(progn nil))
	  ((eql length 2) (walk-form-1 `(setq ,@pairs) env walker))
	  (t
	   (let* ((places ())
		  (values ()))
	     ;; Collect places and values, checking places for expansion into
	     ;; non-symbols.
	     (do ((tail pairs))
		 ((endp tail))
	       (let ((place (pop tail))
		     (value (pop tail)))
		 (when (not (symbolp place))
		   (walk-error "~S used to update non-symbol ~S."
			       'psetq place))
		 (push place places)
		 (push value values)
		 ;; Repeatdly expand place until it is either not a macro or
		 ;; it is not a symbol.  If not a macro then we can still use
		 ;; psetq for the update.  If expansion is not a symbol then
		 ;; transform form into a PSETF form and walk that instead.
		 (loop
		   (multiple-value-bind (newplace macrop)
		       (translator-symbol-macroexpand-1 place env)
		     (when (not macrop) (return))
		     (when (not (symbolp (setf place newplace)))
		       (return-from psetq
			 (walk-form-1 `(psetf ,@pairs) env walker)))))))
	      (when *walk-setq-hook*
		(dolist (var places)
		  (funcall *walk-setq-hook* var env)))
	     `(psetq ,@(mapcan #'(lambda (place value)
				   (list place (walk-form-1 value env walker)))
			       places
			       values)))))))

;;;  TIMPL::SWITCH

(defwalk timpl::switch (item foreign-type &rest clauses
			     &environment env &walk walker)
  (let ((cenv (translator-augment-environment
	       env :conditional-execution-p t)))
    (list* 'timpl::switch
	   (walk-form-1 item env walker)
	   foreign-type
	   (mapcar #'(lambda (clause)
		       (destructuring-bind (key &body body) clause
			 (cons key (walk-progn-1 body cenv walker))))
		   clauses))))

;;;  TIMPL::TRANSLATOR-DEFUN

(defwalk timpl::translator-defun (name lambda-list make-fdescr-fn &body body
				       &environment env &walk walker)
  (let ((fn (walk-function-1 (list* name lambda-list body)
			     (translator-augment-environment
			      env
			      :function (list name))
			     walker)))
    `(timpl::translator-defun ,(first fn) ,(second fn) ,make-fdescr-fn
			      ,@(cddr fn))))

;;;  TYPECASE

(defwalk typecase (item &rest clauses &environment env &walk walker)
  (walk-case-form 'typecase item clauses env walker))


;;; UNBOUND-SPECIAL-P

(defwalk trun:unbound-special-p
  (variable &environment env &walk walker)
  `(trun:unbound-special-p ,(walk-form-1 variable env walker)))

;;;  UNLESS

(defwalk unless (test &body body &environment env &walk walker)
  (let ((cenv (translator-augment-environment
	       env :conditional-execution-p t)))
    `(unless ,(walk-form-1 test env walker)
       ,@(walk-progn-1 body cenv walker))))

;;;  WHEN

(defwalk when (test &body body &environment env &walk walker)
  (let ((cenv (translator-augment-environment
	       env :conditional-execution-p t)))
    `(when ,(walk-form-1 test env walker)
       ,@(walk-progn-1 body cenv walker))))

;;;  WHILE

;;;  TRUN:WITH-AREA

(defwalk trun:with-area (area &body body &environment env &walk walker)
  (multiple-value-bind (body declspecs) (parse-body body nil)
    `(trun:with-area ,area
       ,@(make-declarations declspecs)
       ,@(walk-progn-1 body
		       (translator-augment-environment env :declare declspecs)
		       walker))))

;;;  TX:WITH-LOCAL-ALLOCATION

(defwalk TX:WITH-LOCAL-ALLOCATION
    (&body body &environment env &walk walker)
  (multiple-value-bind (body declspecs) (parse-body body nil)
    `(tx:with-local-allocation
       ,@(make-declarations declspecs)
       ,@(walk-progn-1 body
		       (translator-augment-environment env :declare declspecs)
		       walker))))

(defwalk timpl::do-body (variables end-test result-form step-form
			 tagbody-form
			 &environment env &walk walker)
  (setq env (translator-augment-environment
	     env :multiple-execution-p t))
  `(timpl::do-body ,variables
     ,(walk-form-1 end-test env walker)
     ,(walk-form-1 result-form env walker)
     ,(walk-form-1 step-form env walker)
     ,(walk-form-1 tagbody-form env walker)))

#+ignore ; binghe, 2009/04/03: duplicated definition
(defwalk timpl::forever (&body body &environment env &walk walker)
  `(timpl::forever ,(walk-progn-1 body env walker)))

(defwalk tx:foreign-variable-pointer (string &optional foreign-type
						   &environment env 
						   &walk walker)
  `(tx:foreign-variable-pointer ,string 
				,(walk-form-1 foreign-type env walker)))


(defwalk tx:variadic-foreign-call (function &rest arguments
				   &environment env &walk walker)
  `(tx:variadic-foreign-call ,(walk-form-1 function env walker)
			     ,@(walk-arguments-1 arguments env walker)))

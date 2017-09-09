;;; -*- Mode: Lisp; Package: TIMPL; Syntax: Common-Lisp -*-
;;;
;;; call.lsp -- walk function calls
;;;
;;; Author :  Sandra Loosemore
;;; Date   :  14 May 1990
;;;
;;; Copyright (c) 1990, Chestnut Software Inc.
;;;
;;;

(in-package "TIMPL")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/call.lisp,v $"
 "$Revision: 1.9 $"
 "$Date: 2007/07/13 18:16:52 $")


;;; The general idea here is that we walk the arguments, do any 
;;; generic-to-specific transformations on the call that are appropriate 
;;; for the inferred argument types, and then figure out how to spit
;;; out an appropriate piece of target language based on information
;;; stored about the call protocol for the specific function.
;;;
;;; The translator supports a number of distinct call protocols.  There are
;;; two main divisions:
;;; 
;;; - The normal Lisp call protocol.  All arguments are passed as tagged 
;;; Objects and the arguments passed to the C function match those in the
;;; original Lisp call.  There is one catch, namely functions that are
;;; defined to be variadic (as with &optional, &rest, or &key) require the
;;; argument count to be passed as a C int before any of the real arguments.
;;; Functions that are defined with only required arguments do not take a
;;; count parameter.  Functions that follow the Lisp call protocol return
;;; a Lisp object and set the value return count properly.
;;; 
;;; - A call protocol for C functions and macros.  Currently this can
;;; only deal with passing untagged objects as required parameters, although
;;; the return value can also be untagged.  Calls using this
;;; protocol are assumed to return a single value and not to set the value
;;; return count (except for foreign-call, which doesn't follow the Lisp call
;;; protocol but does follow the Lisp return protocol).  Both a Lisp type 
;;; and a C type must be declared for each argument the return value so 
;;; that we can arrange to do the proper tagging and untagging.  These are 
;;; not Lisp functions and cannot be efunctuated (there is no corresponding
;;; "function object").  We also need flags to indicate whether the call 
;;; might evaluate its arguments more than once (some macros do this), 
;;; whether the call can be used as an l-value, whether the "call" 
;;; is actually a built-in C operator with its own weird syntax, or whether
;;; the call is a macro that requires some hidden temporaries to be declared.
;;; The specific call protocol is encoded in the :foreign-protocol slot of the 
;;; function descriptor.
;;; 
;;; Note that a single "function" can have only one kind of definition.
;;; However, the :transforms attribute can be used to specify that calls
;;; ought to be transformed into another function which has a different
;;; kind of definition.

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Call argument checking
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;; See if the actual arguments to a function call match its lambda-list.

;;; Lambda-list-info -- This structure is used to cache information about at
;;; lambda-list that is used in the argument checking process, in order to
;;; avoid recomputing the information every time a call to a given function is
;;; encountered.

(defstruct (lambda-list-info
	     (:constructor %make-lambda-list-info))
  (required           0   :read-only t :type (integer 0))
  (positional         0   :read-only t :type (integer 0))
  (keys               ()  :read-only t :type list)
  (flags              0   :read-only t :type fixnum)
  )

(define-flags lambda-list-info- lambda-list-info-flags
  (restp              nil :read-only t :type (member t nil))
  (keyp               nil :read-only t :type (member t nil))
  (allow-other-keys-p nil :read-only t :type (member t nil)))

(defmacro make-lambda-list-info (&rest args)
  (let ((new-args nil)
	(new-flags nil)
	(flags-var (make-symbol "FLAGS")))
    (loop (unless args (return nil))
	  (let ((key (pop args))
		(form (pop args)))
	    (if (member key *lambda-list-info-flags*)
		(progn (push key new-flags) (push form new-flags))
		(progn (push key new-args)  (push form new-args)))))
    (setq new-args `(:flags ,flags-var ,@(nreverse new-args)))
    `(let ((,flags-var (make-lambda-list-info-flags
			,@(nreverse new-flags))))
       (%make-lambda-list-info ,@new-args))))

;;; Compute a lambda-list-info structure from the lambda-list.

(defun compute-lambda-list-info (lambda-list)
  (let ((required 0)
	(optional 0)
	(restp nil)
	(keyp nil)
	(keys ())
	(allow-other-keys-p nil))
    (parse-lambda-list 
     lambda-list
     :required #'(lambda (var)
		   (declare (ignore var))
		   (incf required))
     :optional #'(lambda (var init initp svar svar-p)
		   (declare (ignore var init initp svar svar-p))
		   (incf optional))
     :rest #'(lambda (var)
	       (declare (ignore var))
	       (setf restp t))
     :keyp #'(lambda ()
	       (setf restp t)
	       (setf keyp t))
     :key #'(lambda (var key init initp svar svar-p)
	      (declare (ignore var init initp svar svar-p))
	      (push key keys))
     :allow-other-keys-p #'(lambda ()
			     (setf allow-other-keys-p t)))
    (make-lambda-list-info :required required
			   :positional (+ required optional)
			   :restp restp
			   :keyp keyp
			   :keys keys
			   :allow-other-keys-p allow-other-keys-p)))

;;; Compare a list of arguments to the pattern specified by lambda-list-info,
;;; signaling warnings about mismatches.

(defun check-argument-match (name lambda-list-info actual-arguments)
  (when (environment-entry-p name) (setq name (environment-entry-name name)))
  (let ((arg-count (length actual-arguments))
	(positional (lambda-list-info-positional lambda-list-info)))
    (cond ((< arg-count (lambda-list-info-required lambda-list-info))
	   (warn "Too few arguments in call to ~S." name))
	  ((<= arg-count positional) nil)
	  ((not (lambda-list-info-restp lambda-list-info))
	   (warn "Too many arguments in call to ~S." name))
	  ((not (lambda-list-info-keyp lambda-list-info)) nil)
	  ((oddp (- arg-count positional))
	   (warn "Odd length keylist in call to ~S." name))
	  (t
	   (check-argument-keyword-match name
					 lambda-list-info
					 (nthcdr positional actual-arguments)
					 )))))

;;; *** Note: This code assumes the forms in the keyword-arguments list have
;;; *** already been fully macroexpanded.

(defun check-argument-keyword-match (name lambda-list-info keyword-arguments)
  (when (environment-entry-p name) (setq name (environment-entry-name name)))
  (labels ((ensure-symbolic-keys (arguments)
	     (unless (endp arguments)
	       (multiple-value-bind (key-value therep)
		   (resolve-value (car arguments))
		 (when therep
		   (unless (symbolp key-value)
		     (warn "Non-symbolic keyword in call to ~S: ~S."
			   name key-value))))
	       (ensure-symbolic-keys (cddr arguments))))
	   (resolve-value (keyform)
	     (translator-constant-value keyform *environment*))
	   (ensure-legal-keys (arguments legal bad alwky)
	     (if (null arguments)
		 (dolist (key bad)
		   (warn "Unmatched keyword in call to ~S: ~S." name key))
		 (multiple-value-bind (value therep)
		     (resolve-value (car arguments))
		   (cond ((not therep)
			  ;; If keyword is not a constant, with a value that
			  ;; can be determined at compile time, don't do any
			  ;; further checking, since it might be
			  ;; :allow-other-keys.
			  nil)
			 ((not (symbolp value))
			  ;; If not a symbol then skip it, since a warning has
			  ;; already been generated for it.
			  (ensure-legal-keys (cddr arguments) legal bad alwky))
			 ((eq value :allow-other-keys)
			  ;; If key is :allow-other-keys, there hasn't been
			  ;; another occurance of it to the left, and its value
			  ;; is resolvable to Nil, then continue checking.
			  ;; Otherwise, treat it as if it were true, and don't
			  ;; do any further checking.
			  (when (or alwky
				    (progn
				      (multiple-value-setq (value therep)
					(resolve-value (cadr arguments)))
				      (and therep (null value))))
			    (ensure-legal-keys (cddr arguments) legal bad t)))
			 (t
			  (ensure-legal-keys
			       (cddr arguments)
			       legal
			       ;; If key is not in the legal list, add it to
			       ;; the bad list for the possible warning at the
			       ;; end.  Don't warn yet, since there might be
			       ;; an :allow-other-keys to the right.
			       (if (member value legal)
				   bad
				   (adjoin value bad))
			       alwky))))))
	   )
    (ensure-symbolic-keys keyword-arguments)
    (unless (lambda-list-info-allow-other-keys-p lambda-list-info)
      (ensure-legal-keys keyword-arguments
			 (lambda-list-info-keys lambda-list-info)
			 nil
			 nil))))

;;; Argument checking handlers for functions which have a function-descriptor.

(defun get-descriptor-lambda-list-info (descriptor)
  (or (function-descriptor-lambda-list-info descriptor)
      (setf (function-descriptor-lambda-list-info descriptor)
	    (compute-lambda-list-info
	         (function-descriptor-lambda-list descriptor)))))

(defun check-argument-descriptor-match (name descriptor actual-arguments)
  (check-argument-match name
			(get-descriptor-lambda-list-info descriptor)
			actual-arguments))



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    FUNCALL
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;; The handling of funcall is intimately tied in with the handling of direct
;;; function calls.  There are a lot of possible conversions between the two,
;;; which are supposed to all settle down eventually.

(deftranslate funcall (function &rest arguments)
  (let ((expanded (apply-macros function *environment*)))
    (case (and (consp expanded) (car expanded))
      (function (translate-funcall-of-function-form expanded arguments))
      (quote (translate-funcall-of-quote-form expanded arguments))
      ;; Note: It might appear that there should also be funcall translation
      ;; handlers for SYMBOL-FUNCTION and possibly for FDEFINITION, but it
      ;; turns out that that is the wrong way to try to optimize funcalls to
      ;; such forms.  Instead, there should be compiler-macros on these
      ;; functions which transform them into FUNCTION forms when the name is a
      ;; constant with an appropriate value, and the name is neither lexically
      ;; fbound nor declared notinline.
      (otherwise (translate-funcall expanded arguments)))))

;;; This gets used when the functional argument to funcall is a FUNCTION form.

(defun translate-funcall-of-function-form (function-form arguments)
  (let ((name (cadr function-form)))
    (cond ((lambda-expression-p name)
	   ;; Try to transform lambda calls into let and let* forms.
	   (let* ((lambda (cons name arguments))
		  (transform (transform-lambda-to-let lambda
						      *environment*
						      nil
						      #'apply-macros)))
	     (if (eq lambda transform)
		 (translate-funcall function-form arguments)
		 (re-translate-form transform))))
	  ((not (valid-function-name-p name))
	   ;; Invalid call, but let FUNCTION special form do the reporting.
	   (translate-funcall function-form arguments))
	  (t
	   ;; Otherwise, try compiler-macroexpanding the funcall form.
	   (multiple-value-bind (newform macrop)
	       (translator-compiler-macroexpand-1
		  `(funcall #',name ,@arguments)
		  *environment*)
	     (if macrop
		 ;; If compiler-macroexpanded, translate the new form.
		 (re-translate-form newform)
		 (multiple-value-bind (usage boundp info)
		     (translator-function-information name *environment*)
		   (if (not (member usage '(nil :function)))
		       ;; Invalid call, but let FUNCTION special form do the
		       ;; reporting.
		       (translate-funcall function-form arguments)
		       (let ((return-type (function-return-type info)))
			 (cond (boundp
				;; If name is a local function, give the same
				;; treatment as in translate-function-call, ie.
				;; generate a funcall through the function
				;; object.
				(translate-funcall function-form
						   arguments
						   return-type))
			       ((or (function-notinline info)
				    (undefined-function-reference-p
				      name usage))
				(re-translate-form
				  `(funcall (fdefinition ',name) ,@arguments)))
			       ((symbolp name)
				;; If name is a symbol, remove the funcall, so
				;; that (funcall #'fn . args) => (fn . args).
				;; We run this through re-translate-form rather
				;; than to translate-function-call-default in
				;; case there is a special-form handler for
				;; name.  Even if there weren't the possibility
				;; of a special-form we would still not go
				;; directly to translate-inline-function-call,
				;; since there might be transformations
				;; present.
				(re-translate-form (cons name arguments)))
			       (t
				;; If name is a SETF function name we can't
				;; remove the funcall.  Since there aren't any
				;; special-forms or transformations for these,
				;; generate a direct call to the corresponding
				;; C function.
				(translate-inline-function-call name
								arguments
								return-type))
			       ))))))))))

(defun translate-funcall-of-quote-form (function-form arguments)
  (let ((name (cadr function-form)))
    (if (not (symbolp name))
	(let ((fn `',name))
	  (unless (and (lambda-expression-p name)
		       (not *ansi-semantics*))
	    (warn "Invalid function argument for funcall: ~S." fn))
	  (translate-funcall fn arguments))
	(multiple-value-bind (usage boundp decls)
	    (translator-function-information name *environment*)
	  (declare (ignore usage decls))
	  (if boundp
	      (translate-funcall `',name arguments)
	      ;; If name is locally bound, fail to transform, generating a
	      ;; call through the symbol-function of the name (calls to quoted
	      ;; SETF function names are not permitted).  It is not correct to
	      ;; try to generate a direct call to the global function when
	      ;; locally bound, since there may be a notinline declaration on
	      ;; the global function that we can't see because the binding is
	      ;; shadowed by the local function.
	      ;;
	      ;; Otherwise, translate (<name> . args).
	      (re-translate-form (cons name arguments)))))))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Ordinary function calls
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;;; At this point we know "form" is an ordinary function call and not
;;;    a macro call or special form.
;;; For calls to globally-defined functions, first see if there are 
;;;    any transformations which can be applied to the call.
;;;    See pattern.lsp.
;;; A NOTINLINE declaration forces the call to be treated like a
;;;    call to SYMBOL-FUNCTION.  It is as though everything that is
;;;    known about the function at translation time is forgotten.

;;; Note that translate-function-call must cooperate with the FUNCALL special
;;; form.  In particular, the following cases must be handled compatibly:
;;;
;;; * The function being called is a lexically bound function.  This is
;;;   currently translated as a call through the Lisp functional object.  For
;;;   functions which don't require a closure environment, this could be
;;;   improved at some point, in which case both places would need to be
;;;   updated. 
;;;
;;; * The function being called is a global function which is declared
;;;   notinline.  This is translated as a call through the result of applying
;;;   symbol-function to the name of the function.

(defvar needs-values-wrapping-callback nil)

(defun translate-function-call (form)
  ;(progn (print "translate-function-call") (print form))
  (if (and (multiple-value-context-p *context*)
	   needs-values-wrapping-callback
	   (funcall needs-values-wrapping-callback
		    (car form) *reason-for-multiple-values-context*))
      (re-translate-form `(values ,form))
      (multiple-value-bind (usage bound-p decls)
	  (translator-function-information (car form) *environment*)
	(let ((return-type (and-value-types (function-return-type decls)
					    *result-type*
					    *environment*))
	      (function (car form))
	      (argforms (cdr form)))
	  (cond ((and bound-p (cdr (assoc 'tx:function-needs-environment decls)))
		 (translate-funcall `(function ,function) argforms return-type))
		((and bound-p (eq *context* ':result-type-only))
		 return-type)
		(bound-p
		 (translate-simple-bound-function-call  
		   (cdr (assoc 'function-record decls))
		   argforms return-type))
		((or (function-notinline decls)
		     (undefined-function-reference-p function usage))
		 ;; Don't provide return-typep info here, since we `forget' info
		 ;; about notinline globals.
		 (translate-funcall `',function argforms *result-type*))
		(t ; direct call to internal entry point
		 (translate-inline-function-call 
		   function argforms return-type)))))))

(defvar temp-values-wrapper-patch-loaded t)

(defun translate-simple-bound-function-call (record argforms return-type)
  (multiple-value-bind (statements arg-values arg-types temps)
      (translate-arguments 
       argforms 
       (mapcar #'get-first-result-type argforms))
    (declare (ignore arg-types))
    (handle-context
     statements
     (let* ((fn (make-target-form 'function-name record)))
       (if (function-record-variadic-p record)
	   (apply-make-target-form 'variadic-values-c-call fn arg-values)
	   (apply-make-target-form 'values-c-call fn arg-values)))
     return-type
     temps
     (translator-foreign-type :object))))

;;; This is primarily intended as a helper function, taking a form that should
;;; evaluate to a functional object, plus a list of arguments, and generates
;;; the appropriate funcall, without having to go through all the mechanism of
;;; dealing with a form whose first element is FUNCALL.  This gets used by the
;;; FUNCALL special form when it can't find anything better to do, and is also
;;; used by translate-function-call when it knows that the FUNCALL special-form
;;; cannot improve on the situation.
;;; The handling for the special cases for FUNCALL has to be done here
;;; instead of with a compiler-macro because you can't define compiler-macros
;;; on FUNCALL.  Also its definition as a special form would shadow any
;;; compiler macro that you did provide.
;;; *** Should define more special cases here eventually.

(defun translate-funcall (function arguments &optional
				   (return-type '(values &rest t)))
  (translate-inline-function-call
    (case (length arguments)
      (0  'trun:%funcall-0)
      (1  'trun:%funcall-1)
      (2  'trun:%funcall-2)
      (3  'trun:%funcall-3)
      (4  'trun:%funcall-4)
      (5  'trun:%funcall-5)
      (t  'funcall))
    (cons function arguments)
    return-type))

(defun inline-function-call-setup (name argforms)
  (unless (environment-entry-p name)
    (setq name (environment-entry name nil t)))
  (let ((descriptor (find-descriptor name))
	(argforms (mapcar #'(lambda (form)
			      (apply-macros form *environment*))
			  argforms)))
    (check-argument-descriptor-match name descriptor argforms)
    (values name descriptor argforms)))

;;; OK, now we know we are going to emit some kind of inline function 
;;; call and not do a FUNCALL.
;;; Walk the function arguments, look for generic-to-specific 
;;; transformations, and figure out if this call uses the Lisp call
;;; protocol or the foreign call protocol.

(defun translate-inline-function-call (name argforms return-type)
  (multiple-value-bind (name descriptor argforms)
      (inline-function-call-setup name argforms)
    (if (and (eq *context* *ignore-context*)
	     (function-descriptor-ignorable-p descriptor))
	(translate-ignored-function-arguments argforms)
	(multiple-value-bind (name descriptor argforms arg-types return-type)
	    (do-inline-call-transformations name descriptor argforms
					    return-type)
	  (unless descriptor
	    (return-from translate-inline-function-call
	      (re-translate-form name)))
	  (when (eq *context* ':result-type-only)
	    (return-from translate-inline-function-call
	      (values nil nil return-type)))
	  (if (function-descriptor-foreign-protocol descriptor)
	      (let* ((length (length arg-types))
		     (aft (adjust-list-for-rest-arg
			   length
			   (foreign-function-arguments-foreign-types
			    descriptor)))
		     (abadp (adjust-list-for-rest-arg
			     length 
			     (foreign-function-arguments-badp descriptor))))
		(setq aft (mapcar #'compute-foreign-type arg-types aft))
		(multiple-value-bind (statements arg-values arg-types temps)
		    (translate-arguments argforms arg-types nil aft abadp)
		  (declare (ignore arg-types))
		  (note-local-temps
		   (foreign-function-descriptor-uses-locals descriptor))
		  (translate-foreign-function-call
		   name descriptor statements arg-values temps return-type)))
	      (multiple-value-bind (statements arg-values arg-types temps)
		  (translate-arguments argforms arg-types)
		(declare (ignore arg-types))
		(translate-lisp-function-call
		 name descriptor statements arg-values temps return-type)))))))

(defun translate-ignored-function-arguments (argforms)
  (re-translate-form `(progn ,@argforms nil)))

;;; This predicate is used to determine whether a function call appearing in
;;; an *ignore-context* context can be transformed into a progn that evaluates
;;; the argument forms in an *ignore-context* context.
;;; *** This definition might not be best, because it changes the Lisp source
;;; *** to C source mapping fairly drasticly.  Perhaps there should be another
;;; *** property of function-descriptors to control this specific behavior.

(defun function-descriptor-ignorable-p (descriptor)
  (not (function-descriptor-state-changing descriptor)))


;;; Do transformations on inline calls, maybe substituting another
;;; function to call instead.  Currently, we look for:
;;; (1) Unconditional inline-to transformations.
;;; (2) Generic-to-specific transformations based on types of actual arguments.
;;; Return the actual function name, descriptor, and result type.

;;; The transforms slot of the descriptor contains a list of
;;; (new-name safe-p) lists.  If (1) safe-p is true, or the Lisp types
;;; of the actual arguments match those required by new-name, and
;;; (2) new-name does not require a return-type-declaration (most common case),
;;; or the Lisp return type matches that required by new-name, then
;;; call the function named new-name instead.  The transformations are
;;; tested sequentially so put the most specific ones first.

(defun do-inline-call-transformations (name descriptor argforms return-type)
  (let ((argtypes (mapcar #'get-first-result-type argforms))
	#||(safety (safety-level *environment*))||#)
    (loop (when (function-descriptor-coerce-rationals-to-floats-p
		 descriptor)
	    (multiple-value-setq (argforms argtypes)
	      (maybe-coerce-rationals-to-floats argforms argtypes)))
	  (when (eq ':secret-special-form
		    (car (function-descriptor-foreign-protocol descriptor)))
	    (let* ((form (apply-macros `(,(if (environment-entry-p name)
					      (environment-entry-name name)
					      name)
					  ,@argforms) *environment*)))
	      (when (atom form)
		(return-from do-inline-call-transformations
		  (values form nil nil nil nil)))
	      (multiple-value-setq (name descriptor argforms)
		(inline-function-call-setup (car form) (cdr form)))
	      (setq argtypes (mapcar #'get-first-result-type argforms))))
	  (dolist (transform (function-descriptor-transforms descriptor)
		   (return-from do-inline-call-transformations
		     (values name descriptor argforms argtypes
			     (and-value-types
			      (function-descriptor-return-type descriptor)
			      return-type
			      *environment*))))
	    (multiple-value-bind (new-descriptor new-name)
		(do-transform-p transform argforms argtypes return-type)
	      (when new-descriptor
		(setq name new-name)
		(setq descriptor new-descriptor)
		(setq return-type
		      (and-value-types
		       (function-descriptor-return-type descriptor)
		       return-type
		       *environment*))
		(return nil)))))))

(defmacro simple-sequence-predicate (found-value negate-predicate-p
				     predicate &rest lists)
  (let ((tail-vars (mapcar #'(lambda (list-var)
			       (intern (format nil "~A-TAIL" list-var)))
			   lists)))
    `(progn
       (setq ,@(mapcan #'list tail-vars lists))
       (loop (unless (and ,@tail-vars) (return ,(not found-value)))
	     (,(if negate-predicate-p 'unless 'when)
	       (,(cadr predicate)
		 ,@(mapcar #'(lambda (var) `(car ,var))
			   tail-vars))
	       (return ,found-value))
	     ,@(mapcar #'(lambda (var) `(setq ,var (cdr ,var)))
		       tail-vars)))))

(defmacro simple-every (predicate &rest lists)
  `(simple-sequence-predicate nil t ,predicate ,@lists))

(defmacro simple-some (predicate &rest lists)
  `(simple-sequence-predicate t nil ,predicate ,@lists))

(defmacro simple-notany (predicate &rest lists)
  `(simple-sequence-predicate nil nil ,predicate ,@lists))

(defmacro simple-notevery (predicate &rest lists)
  `(simple-sequence-predicate t t ,predicate ,@lists))

(defun do-transform-p (transform argforms argtypes return-type)
  (unless (environment-entry-p (first transform))
    (setf (first transform)
	  (environment-entry (first transform) nil t)))
  (unless (cddr transform)
    (setf (cddr transform) (defined-as-function (first transform))))
  (let* ((new-name (first transform))
	 (transform-condition (second transform))
	 (new-descriptor (cddr transform))
	 (argforms-length (length argforms))
	 (required-number-of-arguments
	  (length
	   (or (function-descriptor-argument-types new-descriptor)
	       (function-descriptor-lambda-list new-descriptor))))
	 (required-argument-types
	  (unless (eq transform-condition t)
	    (function-descriptor-argument-types new-descriptor)))
	 (number-of-results-used-by-context (number-of-values return-type))
	 (number-of-results-returned
	  (number-of-values (function-descriptor-return-type new-descriptor)))
	 (required-result-type
	  (if (function-descriptor-requires-return-type-declaration
	       new-descriptor)
	      (function-descriptor-return-type new-descriptor)
	      't))
	 argforms-tail argtypes-tail required-argument-types-tail)
    (cond ((not (= argforms-length required-number-of-arguments))
	   (values nil :wrong-number-of-arguments 
		   argforms-length required-number-of-arguments))
	  ((and number-of-results-returned
		(or (null number-of-results-used-by-context)
		    (> number-of-results-used-by-context
		       number-of-results-returned)))
	   (values nil :returns-too-few-values
		   number-of-results-used-by-context 
		   number-of-results-returned))
	  ((and (eq transform-condition ':boolean)
		(eq *context* *predicate-context*))
	   (values new-descriptor new-name))
	  ((simple-notevery #'translator-subtypep
			    argtypes required-argument-types)
	   (values nil :unsuitable-argument-types
		   (car argtypes-tail) (car required-argument-types-tail)))
	  ((and (eq transform-condition :single)
		(simple-some #'(lambda (argtype req-arg-type)
				 (and (eq req-arg-type 'single-float)
				      (not (eq argtype 'single-float))))
			     argtypes required-argument-types))
	   (values nil :some-argument-was-not-single-float
		   (car argtypes-tail) (car required-argument-types-tail)))
	  ((and (not (eq required-result-type 't))
		(not (translator-subtypep return-type required-result-type)))
	   (values nil :unsuitable-result-type
		   return-type required-result-type))
	  ((and (eq transform-condition ':no-longs)
		(simple-some #'form-returning-long-p argforms argtypes))
	   (values nil :some-argument-returned-long
		   (car argforms-tail) (car argtypes-tail)))
	  ((and (eq transform-condition ':no-doubles)
		(simple-some #'form-returning-double-p argforms argtypes))
	   (values nil :some-argument-returned-double
		   (car argforms-tail) (car argtypes-tail)))
	  ((and (eq transform-condition ':some-longs)
		(simple-notany #'form-returning-long-p argforms argtypes))
	   (values nil :no-argument-returned-long
		   (car argforms-tail) (car argtypes-tail)))
	  ((and (eq transform-condition ':all-int64)
		(simple-notany #'form-returning-int64-p argforms argtypes))
	   (values nil :no-argument-returned-int64
		   (car argforms-tail) (car argtypes-tail)))
	  (t
	   (values new-descriptor new-name)))))

(defun number-of-values (type)
  (if (and (consp type) (eq (car type) 'values))
      (if (memq '&rest (cdr type))
	  nil
	  (length (cdr type)))
      1))

(defvar *asume-complicated-forms-return-c-type-p* t)

(defun simple-form-foreign-type (form &optional (return-type t) env
				      &aux fn ft-fn)
  (unless env (setq env *environment*))
  (cond ((symbolp form)
	 (multiple-value-bind (usage bound-p decls)
	     (translator-variable-information form env)
	   (declare (ignore bound-p))
	   (case usage
	     (:lexical
	      (variable-record-foreign-type 
	       (cdr (assoc 'variable-record decls))))
	     ((:special :constant nil)
	      (translator-foreign-type :object))
	     (:symbol-macro
	      nil))))
	((trun:fixnump form)
	 (translator-foreign-type :fixnum))
	((characterp form)
	 (translator-foreign-type :char))
	((or (not (consp form)) 
	     (consp (setq fn (car form))))
	 nil)
	((setq ft-fn (foreign-type-function fn))
	 (funcall ft-fn form return-type))
	(t
	 (multiple-value-bind (usage bound-p decls)
	     (translator-function-information fn env)
	   (unless (or bound-p (function-notinline decls)
		       (not (eq usage ':function)))
	     (multiple-value-bind (fn fd argforms)
		 (inline-function-call-setup fn (cdr form))
	       (multiple-value-bind (fn fd)
		   (do-inline-call-transformations fn fd argforms return-type)
		 (declare (ignore fn))
		 (when fd 
		   (if (function-descriptor-foreign-protocol fd)
		       (foreign-function-descriptor-foreign-return-type fd)
		       (translator-foreign-type :object))))))))))

(defun form-returning-long-p (form type)
  (when (and (not (trun:fixnump form))
	     (translator-subtypep type 'integer))
    (let* ((ft (simple-form-foreign-type form type))
	   (c-type (and ft (c-type ft))))
      (or (equal c-type "SI_Long") (equal c-type "long") (equal c-type "int")))))

(defun form-returning-int64-p (form type)
  (when (and (not (trun:fixnump form))
	     (translator-subtypep type 'integer))
    (let* ((ft (simple-form-foreign-type form type))
	   (c-type (and ft (c-type ft))))
      (equal c-type "SI_int64"))))

(defun form-returning-double-p (form type)
  (when (translator-subtypep type 'float)
    (or (floatp form)
	(let* ((ft (simple-form-foreign-type form type))
	       (c-type (and ft (c-type ft))))
	  (equal c-type "double")))))

(defun maybe-coerce-rationals-to-floats (argforms argtypes)
  (let ((double-float-seen-p nil))
    (when (let ((float-seen-p nil)
		(rational-seen-p nil))
	    (dolist (type argtypes
		     (and float-seen-p rational-seen-p))
	      (cond ((translator-subtypep type 'rational)
		     (setq rational-seen-p t))
		    ((translator-subtypep type 'float)
		     (setq float-seen-p t)
		     (when (or (eq type 'double-float)
			       (eq type 'long-float)
			       (and (consp type) (eq (car type) 'member)))
		       (setq double-float-seen-p t)))
		    (t
		     (return nil)))))
      (maplist #'(lambda (argforms-tail argtypes-tail)
		   (let ((argtype (car argtypes-tail)))
		     (when (translator-subtypep argtype 'rational)
		       (setf (car argtypes-tail) 'float)
		       (let ((argform (car argforms-tail)))
			 (multiple-value-bind (value valuep)
			     (translator-constant-value argform *environment*)
			   (setf (car argforms-tail)
				 (cond (valuep
					(float value 1d0))
				       (double-float-seen-p
					`(float ,argform 1d0))
				       (t
					`(float ,argform)))))))))
	       argforms argtypes))
    (values argforms argtypes)))


;;; For functions that use the Lisp call protocol, make sure that the
;;; actual arguments match the lambda-list noted in the descriptor.
;;; Produce either a "call" or "variadic-call", depending on whether
;;; the function takes only required arguments.  All arguments are
;;; passed as Objects so we do not need to do any type conversion.

(defun translate-lisp-function-call (name descriptor statements arg-values
					  temps return-type)
  (handle-context
    statements
    (if (function-descriptor-variadic descriptor)
	(if (function-descriptor-generic-function-p descriptor)
	    (apply-make-target-form 'variadic-call-generic name arg-values)
	    (apply-make-target-form 'variadic-call name arg-values))
	(let* ((lambda-list-info (get-descriptor-lambda-list-info descriptor))
	       (num-unsupplied-markers (- (lambda-list-info-positional 
					   lambda-list-info)
					  (length arg-values)))
	       (args `(,name
		       ,@arg-values
		       ,@(make-unsupplied-markers num-unsupplied-markers))))
	  (if (function-descriptor-generic-function-p descriptor)
	      (apply-make-target-form 'call-generic args)
	      (apply-make-target-form 'call args))))
    return-type
    temps
    (translator-foreign-type :object)))

(defun translate-generic-function-call (name descriptor arg-values)
  (let ((info (get-descriptor-lambda-list-info descriptor)))
    (multiple-value-bind (variadicp num-unsupplied-markers)
	(if (or (lambda-list-info-restp info)
		(lambda-list-info-keyp info))
	    (values t 0)
	    (values nil
		    (max 0
			 (- (lambda-list-info-positional info)
			    (length arg-values)))))
      (let ((args (append arg-values
			  (make-unsupplied-markers num-unsupplied-markers))))
	(if variadicp
	    (apply-make-target-form 'variadic-call-generic name args)
	    (apply-make-target-form 'call-generic name args))))))

(defun make-unsupplied-markers (num &aux (markers nil))
  (dotimes (i num markers)
    (push (nth-value 1 (translate-form 'trun:%unsupplied-marker
				       *environment*
				       *value-context*))
	  markers)))

(defun translate-rtl-lisp-function-call (name descriptor arg-values)
  (let* ((lambda-list-info (get-descriptor-lambda-list-info descriptor))
	 (variadic (or (lambda-list-info-restp lambda-list-info)
		       (lambda-list-info-keyp lambda-list-info)))
	 (num-of-unsupplied-markers
	  (unless variadic
	    (- (lambda-list-info-positional lambda-list-info)
	       (length arg-values))))
	 (generic (function-descriptor-generic-function-p descriptor))
	 (args (if variadic
		   (cons name arg-values)
		   `(,name
		     ,@arg-values
		     ,@(make-unsupplied-markers num-of-unsupplied-markers)))))
    (if generic
	(if variadic
	    (apply-make-target-form 'variadic-call-generic args)
	    (apply-make-target-form 'call-generic args))
	(if variadic
	    (apply-make-target-form 'variadic-call args)
	    (apply-make-target-form 'call args)))))

;;; If the foreign-protocol slot of the function descriptor is non-nil, 
;;; generate a foreign call of some sort.  We need to do some additional
;;; processing on the arguments to make sure that they get evaluated only
;;; once and to make sure that the appropriate c-type conversions are made.
;;; Then dispatch to an appropriate handler to construct the return 
;;; expression. These handlers also do things like c-type conversions on
;;; the return values where appropriate.

(defmacro foreign-call-handler (key-name)
  `(get ,key-name 'foreign-call-handler))

(defmacro define-foreign-call-handler (key-name lambda-list &body body)
  (let ((name (intern (format nil "~A-~A" key-name 'foreign-call-handler))))
    `(progn
       (defun ,name ,lambda-list ,@body)
       (setf (foreign-call-handler ',key-name) #',name)
       ',key-name)))

(defun fix-foreign-arguments (fa)
  (mapcar #'(lambda (ft+badp)
	      (if (consp ft+badp)
		  (list (translator-foreign-type (car ft+badp))
			(cadr ft+badp))
		  ft+badp))
	  fa))

(defun fix-foreign-return-type (frt)
  (translator-foreign-type frt))

(defun fix-foreign-protocol (fp)
  (when (consp fp) (setq fp (car fp)))
  (cons fp 
	(or (foreign-call-handler fp)
	    (error "Unknown call protocol ~s." fp))))

(defun fix-foreign-operator (op)
  (if (and op (symbolp op))
      (get-c-operator op)
      op))

(defun copy-transform (transform)
  (let ((name (car transform))
	(safe-p (cadr transform)))
    (cons (if (environment-entry-p name)
	      (environment-entry-name name)
	      name)
	  (cons safe-p nil))))

(defun foreign-function-arguments-foreign-types (descriptor)
  (mapcar #'(lambda (ft+badp)
	      (if (consp ft+badp)
		  (car ft+badp)
		  ft+badp))
	  (foreign-function-descriptor-foreign-arguments descriptor)))

(defun foreign-function-arguments-badp (descriptor)
  (mapcar #'(lambda (ft+badp)
	      (if (consp ft+badp)
		  (cadr ft+badp)
		  ft+badp))
	  (foreign-function-descriptor-foreign-arguments descriptor)))

(defun translate-foreign-function-call
    (name descriptor statements arg-values temps return-type)
  (let ((key-name (function-descriptor-foreign-protocol descriptor)))
    (multiple-value-bind (value foreign-type)
	(funcall (or (and (consp key-name) (cdr key-name))
		     (error "Unknown call protocol ~s for function ~s."
			    key-name (if (environment-entry-p name)
					 (environment-entry-name name)
					 name)))
		 name
		 descriptor
		 arg-values
		 return-type)
      (handle-context statements value return-type temps foreign-type))))


;;; The emitter has to emit declarations for all local temps implicitly
;;; referenced in foreign calls.  Note which ones this call uses in the
;;; current function.

(defun note-local-temps (local-temps)
  (if local-temps
      (setf (function-record-local-temps *current-function*)
	    (unionq local-temps
		    (function-record-local-temps *current-function*)))))


(defun compute-foreign-type (lisp-type foreign-type)
  ;(progn (print "compute-foreign-type")(print lisp-type)(print foreign-type))
  (let ((foreign-type-name (translator-foreign-type-name foreign-type)))
    (cond ((and (or (eq foreign-type-name :long)
		    (eq foreign-type-name :int))
		(translator-subtypep lisp-type 'fixnum))
	   (translator-foreign-type :fixnum))
	  ((and (eq foreign-type-name :float)
		(translator-subtypep lisp-type 'float))
	   (translator-foreign-type :double-float))
	  (t
	   foreign-type))))

;;; Here are the foreign call protocols currently known to the translator.

(define-foreign-call-handler :foreign-arguments-function
    (name descriptor arg-values return-type)
  (declare (ignore descriptor return-type))
  (values 
   (apply-make-target-form 'foreign-call name arg-values)
   (translator-foreign-type :object)))

(define-foreign-call-handler :macro (name descriptor arg-values return-type)
  (values
   (apply-make-target-form 'macro-call name arg-values)
   (compute-foreign-type
    return-type
    (foreign-function-descriptor-foreign-return-type descriptor))))

(define-foreign-call-handler :accessor (name descriptor arg-values return-type)
  (values
   (apply-make-target-form 'accessor-call name arg-values)
   (compute-foreign-type
    return-type
    (foreign-function-descriptor-foreign-return-type descriptor))))

(define-foreign-call-handler :operator (name descriptor arg-values return-type)
  (values
   (apply-make-target-form 'operator-call name arg-values)
   (compute-foreign-type
    return-type
    (foreign-function-descriptor-foreign-return-type descriptor))))

(define-foreign-call-handler :secret-special-form
    (name descriptor arg-values return-type)
  (declare (ignore descriptor arg-values return-type))
  (error "Internal error: ~s is supposed to be treated like a special form."
	 name))

(define-foreign-call-handler :lvalue-setter
    (name descriptor arg-values return-type)
  (declare (ignore name))
  (reset-read-once-setqs *environment*)
  (values
   (make-target-form
    'setq
    (apply-make-target-form 'accessor-call
			    (foreign-function-descriptor-lvalue descriptor)
			    (butlast arg-values))
    (first (last arg-values)))
   (compute-foreign-type
    return-type
    (foreign-function-descriptor-foreign-return-type descriptor))))

(defun lvalue-setter-p (name)
  (let ((f-p (function-descriptor-foreign-protocol
	      (defined-as-function name))))
    (and (consp f-p) (eq (car f-p) :lvalue-setter))))

;;; Helper functions for the above

(defun function-return-type (decls)
  (let ((ftype (cdr (assoc 'ftype decls))))
      (if (and (consp ftype) (eq (car ftype) 'function)
	       (cddr ftype))
	  (third ftype)
	  '(values &rest t))))

(defun function-notinline (decls)
  (let ((inline (cdr (assoc 'inline decls))))
    (eq inline 'notinline)))


(defun find-descriptor (name)
  (multiple-value-bind (name entry)
      (name-and-environment-entry name)
    (or (defined-as-function entry)
	;; Functions not known to the translator should never get here.
	;; They should be caught by translate-function-call and generate
	;; out-of-line call through name.
	(error "Translator bug -- Attempt to generate inline call ~
                to unknown function ~S."
	       name))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Argument processing
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;;; Process the list of function arguments.  Returns three values:
;;; a list of side-effecting statements, a list of expressions for each
;;; argument value, and a list of result types.
;;;
;;; There are two reasons why we need to use temporaries here.
;;; (1) We have to make sure that all of the argument computation happens
;;;     in left-to-right order.  Unlike Lisp, C doesn't guarantee the
;;;     order of evaluation of arguments to function calls.
;;;     Specifically, a temp must be used for left-to-right evaluation
;;;     if:
;;;         * accidentally evaluating any of the arguments to the right
;;;           first might affect the value of the argument.
;;;         * evaluating this argument has side-effects that arguments to
;;;           the right depend on.
;;;         * evaluating this argument has side-effects that may
;;;           not commute with the side-effects of arguments to the right.
;;; (2) We must make sure that if there is an argument that might invoke the
;;;     GC, then all the other arguments must be non-relocatable.
;;;
;;; The approach taken here is to walk the arguments in right-to-left
;;; order in a :value context.  If we find that an argument really needs 
;;; a temp, then we re-walk the form in an l-value context.
;;;
;;; Of course, none of this hair is needed unless there are multiple arguments.
;;;
;;; force-temp (if supplied) is a predicate of three arguments: the value
;;; expression from an argument form, a list of statements from rightward
;;; arguments, and list of value expressions from rightward arguments.  If
;;; true, then the current value expression must be temped.  This argument
;;; provides a mechanism for specifying additional reasons for temping
;;; arguments, in addition to those specified above.

(defmacro make-null-target-form-info ()
  (let ((variable (type-info-variable 'null-statement)))
    `(make-target-info (locally (declare (special ,variable)) ,variable))))

(defun remove-setq-statement (record setq-statement)
  (let ((binder (variable-record-binder record)))
    (if binder
	(setf (second binder)
	      (delete record (second binder)))
	(setf (function-record-local-variables *current-function*)
	      (delete record
		      (function-record-local-variables *current-function*)))))
  (setf (car setq-statement) (make-null-target-form-info))
  (setf (cdr setq-statement) nil))

(defun translate-arguments (argform-list type-list &optional (force-temp nil)
					 foreign-types badp-list)
  (let* ((relocatable-value-index (compute-relocatable-value-index
				   type-list foreign-types))
	 (do-side-effect-checking-p
	  (not (compute-skip-side-effect-checking-p argform-list)))
	 (all-statements   nil)
	 (value-list       nil)
	 (result-type-list nil)
	 (all-temps        nil)
	 (function-may-gc (function-may-gc *current-function*))
	 (length (length argform-list))
	 (length-1 (1- length)))
    (dotimes (i length)
      (let ((pos (- length-1 i)))
	(multiple-value-bind (statements value type temps)
	    (translate-argument (nth pos argform-list)
				(nth pos type-list)
				(nth pos foreign-types)
				(nth pos badp-list)
				pos relocatable-value-index
				do-side-effect-checking-p
				function-may-gc force-temp
				all-statements value-list)
	  (setq all-temps (nconc all-temps temps))
	  (setq all-statements (nconc all-statements statements))
	  (push value value-list)
	  (push type result-type-list))))
    (values all-statements
	    value-list result-type-list all-temps)))

(defun translate-argument (form &optional (type 't)
				foreign-type badp pos
				relocatable-value-index
				do-side-effect-checking-p
				function-may-gc force-temp
				all-statements value-list
				&aux var-form)
  (unless foreign-type (setq foreign-type *value-context*))
  (multiple-value-bind (statements value type temps)
      (translate-form form *environment* foreign-type type)
    (cond ((and (not do-side-effect-checking-p)
		(setq var-form (local-variable-form-p value)))
	   (let ((record (cadr var-form)))
	     (multiple-value-bind (rhs-value setq-statement)
		 (do-read-once-optimization record foreign-type)
	       (when (and setq-statement
			  (not (need-to-use-a-temporary-variable-p
				rhs-value
				all-statements value-list
				pos relocatable-value-index
				function-may-gc
				force-temp badp
				do-side-effect-checking-p)))
		 (remove-setq-statement record setq-statement)
		 (setq value rhs-value)))
	     (values statements value type temps)))
	  ((need-to-use-a-temporary-variable-p
	    value all-statements value-list
	    pos relocatable-value-index
	    function-may-gc
	    force-temp badp
	    do-side-effect-checking-p)
	   (handle-lvalue-context statements value type temps
				  foreign-type))
	  (t
	   (values statements value type temps)))))

(defun do-read-once-optimization (record &optional foreign-type)
  (when *do-read-once-optimization*
    (let ((setq-statement (variable-record-setq-statement record))
	  (variable-foreign-type (variable-record-foreign-type record)))
      (when (consp setq-statement)
	(let ((rhs (caddr setq-statement)))
	  (if (and foreign-type (not (eq foreign-type variable-foreign-type)))
	      (let ((*context* foreign-type))
		(multiple-value-bind (rhs-statements rhs-value)
		    (handle-context nil rhs t nil variable-foreign-type)
		  (unless rhs-statements
		    (values rhs-value setq-statement))))
	    (values rhs setq-statement)))))))

(defun local-variable-form-p (value)
  (case (target-form-type value)
    (local-variable value)
    ((box-value unbox-value) (local-variable-form-p (caddr value)))
    (t nil)))

(defun adjust-list-for-rest-arg (length list)
  (let ((rest (member '&rest list)))
    (if (null rest)
	list
	(let ((first (ldiff list rest)))
	  (append first
		  (make-list (- length (length first))
			     :initial-element (cadr rest)))))))

;nil means no values are relocatable
;t means more than one value is relocatable
;an integer means only one value is relocatable, the integer is its index

(defun compute-relocatable-value-index (type-list foreign-types)
  (let ((i 0) (index nil))
    (dolist (type type-list index)
      (when (relocatable-type-p type (pop foreign-types))
	(if index
	    (return t)
	    (setq index i)))
      (incf i))))

(defun compute-skip-side-effect-checking-p (argform-list)
  (or (every #'not-affected-by-side-effects-p argform-list)
      (every #'will-not-cause-side-effects-p argform-list)))

(defun not-affected-by-side-effects-p (argform)
  (or (translator-constantp argform *environment*)
      (if (atom argform)
	  (multiple-value-bind (usage boundp info)
	      (translator-variable-information argform *environment*)
	    (declare (ignore boundp))
	    (and (eq usage :lexical)
		 (cdr (assoc 'tx:unwritten-variable info))))
	  (let ((fn (car argform)))
	    (and (symbolp fn)
		 (if (eq fn 'the)
		     (not-affected-by-side-effects-p (caddr argform))
		     (let ((fd (defined-as-function fn)))
		       (and fd
			    (not (function-descriptor-state-using fd))
			    (dolist (subform (cdr argform) t)
			      (unless (not-affected-by-side-effects-p
				       (apply-macros subform *environment*))
				(return nil)))))))))))

; apply-macros has already processed argform
(defun will-not-cause-side-effects-p (argform) 
  (or (atom argform)
      (let ((fn (car argform)))
	(and (symbolp fn)
	     (case fn
	       (quote
		t)
	       (the
		(will-not-cause-side-effects-p (caddr argform)))
	       ((let let*)
		(and (dolist (binding (cadr argform) t)
		       (unless (or (not (consp binding))
				   (will-not-cause-side-effects-p
				    (apply-macros (cadr binding)
						  *environment*)))
			 (return nil)))
		     (dolist (subform (cddr argform) t)
		       (unless (or (not (consp subform))
				   (eq 'declare (car subform))
				   (will-not-cause-side-effects-p
				    (apply-macros subform *environment*)))
			 (return nil)))))
	       (t
		(let ((fd (defined-as-function fn)))
		  (and fd
		       (not (function-descriptor-state-changing fd))
		       (dolist (subform (cdr argform) t)
			 (unless (will-not-cause-side-effects-p
				  (apply-macros subform *environment*))
			   (return nil)))))))))))

(defun need-to-use-a-temporary-variable-p (value all-statements value-list
					   index relocatable-value-index
					   function-may-gc
					   force-temp badp
					   do-side-effect-checking-p)
  (cond ((and do-side-effect-checking-p
	      (value-might-be-affected value all-statements value-list))
	 ':value-might-be-affected)
	((target-form-simple-p value)
	 nil)
	((and do-side-effect-checking-p
	      (value-might-affect-others value all-statements value-list))
	 ':value-might-affect-others)
	((and function-may-gc
	      (not (nonrelocating-expression-p value))
	      relocatable-value-index
	      (not (eql index relocatable-value-index)))
	 ':value-might-be-relocated)
	((and force-temp 
	      (funcall force-temp value all-statements value-list))
	 ':values-changing-or-relocating)
	(badp
	 ':maybe-evaluated-twice)
	(t nil)))

(defun relocatable-type-p (type &optional foreign-type)
  (and (or (null foreign-type)
	   (eq foreign-type (translator-foreign-type :object)))
       (relocating-type-p type)))

;not used
(defun relocatable-form-p (form)
  (multiple-value-bind (value valuep)
      (translator-constant-value form)
    (and valuep (relocating-type-p (translator-type-of value)))))

;;; A helper function:  determine if the value of the expression "value" 
;;; might be affected by executing any of the other statements or values.
;;; *** Obviously, this function could be made a lot smarter.
;;; *** For example, it could recognize references to local variables that 
;;; *** are not modified anywhere.  This would require doing some kind of
;;; *** a walk of the other-statements and other-values.

(defun value-might-be-affected (value other-statements other-values)
  (and (state-using-expression-p value)
       (or (notevery #'expression-p other-statements)
	   (some #'state-changing-expression-p other-statements)
	   (some #'state-changing-expression-p other-values))))



;;; The inverse:  determine if any of the other-values might depend on value.
;;; Also check here if we might evaluate two state-changing expressions
;;; out of order, since this is also verboten. In other words, the
;;; "others" the value might effect include the global state after
;;; execution.
(defun value-might-affect-others (value other-statements other-values)
  ;; used to return nil if other-values was nil. This worked, but only
  ;; because other-values was nonnil whenever other-statements was nonnil
  (and (state-changing-expression-p value)
       (or (some #'state-using-expression-p other-values)
	   (some #'state-changing-expression-p other-values)
	   ;; *** Be conservative.  If some statements are not expressions,
	   ;; *** assume some of them are state-using.
	   (notevery #'expression-p other-statements)
	   (some #'state-using-expression-p other-statements)
	   (some #'state-changing-expression-p other-statements))))

;;; Determine whether the value might be relocated, or whether it might
;;; cause other argument values already computed to be relocated.  These
;;; functions are actually pretty pessimistic.


(defun value-might-be-relocated (value other-values)
  (and (function-may-gc *current-function*)
       (not (nonrelocatable-expression-p value))
       (notevery #'nonrelocating-expression-p other-values)))

(defun value-might-relocate-others (value other-values)
  (and (function-may-gc *current-function*)
       (not (nonrelocating-expression-p value))
       other-values))

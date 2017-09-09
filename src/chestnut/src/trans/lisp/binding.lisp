;;; -*- Mode: Lisp; Package: TIMPL; Syntax: Common-Lisp -*-
;;;
;;; binding.lsp -- variable and function name binding and reference
;;;
;;; Author :  Sandra Loosemore
;;; Date   :  16 May 90
;;;
;;; Copyright (c) 1990, Chestnut Software Inc.
;;;
;;;

(in-package "TIMPL")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/binding.lisp,v $"
 "$Revision: 1.13 $"
 "$Date: 2007/07/13 18:16:52 $")

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Support
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;; Given a list of variable names, parse the decl-specs, returning
;;; a list of bound-decls for each name and a list of leftover "free"
;;; decl-specs.

(defun parse-variable-declarations (names decl-specs env)
  (multiple-value-bind (var-info fun-info set-decl-info decl-info)
      (translator-parse-declarations decl-specs env :variable names)
    (let ((alist    (mapcar #'list names))
	  (free     nil))
      (dolist (d var-info)
	(if (member (car d) names)
	    (push d (cdr (assoc (car d) alist)))
	    (push d free)))
      (values
       (mapcar #'(lambda (entry)
		   (list `(tx:variable-information
			   ,@(nreverse (cdr entry)))))
	       alist)
       (mapcan #'(lambda (decl-symbol decls)
		   (when decls
		     (list `(,decl-symbol ,@decls))))
	       '(tx:variable-information tx:function-information
		 tx:set-declaration-information
		 tx:declaration-information)
	       (list (nreverse free) fun-info set-decl-info decl-info))))))


;;; Similar, but for function bindings.

(defun parse-function-declarations (names decl-specs env)
  (multiple-value-bind (var-info fun-info set-decl-info decl-info)
      (translator-parse-declarations decl-specs env :function names)
    (let ((alist    (mapcar #'list names))
	  (free     nil))
      (dolist (d fun-info)
	(if (member (car d) names :test #'equal)
	    (push d (cdr (assoc (car d) alist :test #'equal)))
	    (push d free)))
      (values
       (mapcar #'(lambda (entry)
		   (list `(tx:function-information
			   ,@(nreverse (cdr entry)))))
	       alist)
       (mapcan #'(lambda (decl-symbol decls)
		   (when decls
		     (list `(,decl-symbol ,@decls))))
	       '(tx:variable-information tx:function-information
		 tx:set-declaration-information
		 tx:declaration-information)
	       (list var-info (nreverse free) set-decl-info decl-info))))))


;;; Under CLtL common lisp, free declarations applied to the entire
;;; form in which they appeared.  Under ANSI common lisp, they apply
;;; only to the "body" of the form.  These two functions provide
;;; some abstraction about this.

(defun initialize-environment (env free-decls)
  (if *ansi-semantics*
      env
      (translator-augment-environment env :declare free-decls)))

(defun finalize-environment (env free-decls)
  (if *ansi-semantics*
      (translator-augment-environment env :declare free-decls)
      env))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Reference
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;; What looks like a variable reference might actually be a reference 
;;;    to a symbol-macro or a symbolic constant.  Otherwise turn it 
;;;    into a LOCAL-VARIABLE or SPECIAL-VARIABLE expression.

(defun translate-variable-reference (name)
  (multiple-value-bind (place type foreign-type)
      (variable-place name nil)
    (if place
	(handle-context nil place type nil foreign-type)
        (re-translate-form
	  (translator-symbol-macroexpand-1 name *environment*)))))


;;; Try to reduce SETQ to the 2-argument case.

(deftranslate setq (&rest stuff)
  (cond ((null stuff)
	 (re-translate-form nil))
	((null (cdr stuff))
	 (error "Wrong number of arguments to SETQ."))
	((null (cddr stuff))
	 (setq-aux (car stuff) (cadr stuff)))
	(t
	 (re-translate-form
	  `(progn ,@(expand-setq stuff))))))

(defun expand-setq (stuff)
  (cond ((null stuff)
	 nil)
	((null (cdr stuff))
	 (error "Wrong number of arguments to SETQ."))
	(t
	 (cons `(setq ,(car stuff) ,(cadr stuff))
	       (expand-setq (cddr stuff))))))


;;; SETQ proceeds a lot like a variable reference as far as the
;;; interpretation of the variable argument is concerned, but
;;; what's done with it is very different.

(defun setq-aux (name form)
  (multiple-value-bind (place type foreign-type)
      (variable-place name t)
    (cond ((null place)
	   ;; it was a symbol-macro
	   (re-translate-form
	    `(setf ,(translator-symbol-macroexpand-1 name *environment*)
		   ,form)))
	  ((and (consp place) (eq (target-form-type place) 'macro-call))
	   ;; it was a call to an unproclaimed SPECIAL
	   (re-translate-form
	    `(set ',name ,form)))
	  (t
	   (multiple-value-call #'handle-context
	     (translate-form form *environment*
			     (if (eq *context* :result-type-only)
				 *context*
				 place)
			     (and-value-types type
					      *result-type*
					      *environment*))
	     foreign-type)))))


;;; A helper function for variable reference, SETQ, and MULTIPLE-VALUE-SETQ.
;;; Return the "place" (an expression) corresponding to the named variable,
;;; and its type.
;;; *** Maybe the handling for reference to unbound variable ought to provide
;;; *** a hook for some recovery action (like signalling a cerror instead of
;;; *** a warning and making one of the restarts proclaim it special).

(defun variable-place (name setq-p)
  (multiple-value-bind (usage bound-p decls)
      (translator-variable-information name *environment*)
    (declare (ignore bound-p))
    (let ((type            (or (cdr (assoc 'type decls)) t))
	  (variable-record (cdr (assoc 'variable-record decls))))
      (case usage
	(:lexical
	 (let* ((type (and-types type
				 (variable-record-lisp-type variable-record)))
		(foreign-type (variable-record-foreign-type variable-record)))
	   (cond (setq-p
		  (values (local-variable-assignment variable-record)
			  type foreign-type))
		 ((eq *context* *ignore-context*)
		  ;; Since this reference won't actually appear in the output
		  ;; code, we don't want to mark the variable-record as being
		  ;; referenced or possibly closed.  On the other hand, we
		  ;; do want it to count as being referenced for the purposes
		  ;; of suppressing complaints about unreferenced variables.
		  ;;*** This has the side-effect of permitting the binding
		  ;;*** to be removed.  Maybe what we should do instead is
		  ;;*** to have *two* referenced-p slots, one for "referenced
		  ;;*** in the input code" and one for "referenced in the
		  ;;*** output code"?  Or maybe we should just not complain
		  ;;*** about variables that are bound but not referenced?
		  (setf (variable-record-ignorable-p variable-record) t)
		  (values (make-target-form 'local-variable variable-record)
			  type foreign-type))
		 (t
		  (values (local-variable-reference variable-record)
			  type foreign-type)))))
	(:special
	 (values (make-target-form 'special-variable name)
		 type
		 (translator-foreign-type :object)))
	(:symbol-macro			; can't handle this way; give up.
	 (values nil type (translator-foreign-type :object)))
	(:constant			; keyword or symbolic constant
	 (cond (setq-p
		(error "The constant symbol ~s cannot be SETQed." name))
	       ((keywordp name)
		(values (or (eq *context* :result-type-only)
			    (translate-constant-aux name))
			(and-types type 'keyword)
			nil))
	       (t
		(values
		 ;; Might want to treat non-simple constants like
		 ;; special variable references here....
		 (make-target-form 'symbolic-constant name)
		 type
		 (translator-foreign-type :object)))))
	(t ; undeclared free variable, treat like SPECIAL.
	 (warn "Variable ~s has not been bound or declared SPECIAL." name)
	 (values
	  (or (eq *context* :result-type-only)
	      (make-target-form 'macro-call 'trun:%symbol-value
				(translate-constant-aux name)))
	  type
	  (translator-foreign-type :object)))))))



;;; The FUNCTION special form can either be a function reference or
;;; a function definition.  Handle on the reference case here and
;;; the definition case down at the end of the file.

(deftranslate function (arg)
  (cond ((valid-function-name-p arg)
	 (translate-function-reference arg))
	((lambda-expression-p arg)
	 (translate-function-definition nil (cadr arg) (cddr arg)))
	(t
	 (error "Bad syntax in FUNCTION special form: ~s" arg))))

(deftranslate tx:function-object (arg)
  (cond ((valid-function-name-p arg)
	 (translate-function-reference arg ':object))
	((lambda-expression-p arg)
	 (translate-function-definition nil (cadr arg) (cddr arg)))
	(t
	 (error "Bad syntax in FUNCTION special form: ~s" arg))))

;;; A small extension to support FLET and LABELS.
;;; NAMED-FUNCTION is like FUNCTION but it lets you specify a name for
;;; the function (to name the BLOCK, etc).  See translate-function-definition
;;; below.

(deftranslate named-function (name lambda-list &body body)
  (translate-function-definition name lambda-list body))

(defun translate-bound-function-reference (name type decls)
  (when (eq type :foreign)
    (when (cdr (assoc 'tx:function-needs-environment decls))
      (error "~S has an environment" name))
    (let ((function-record (cdr (assoc 'function-record decls))))
      (return-from translate-bound-function-reference
	(translate-foreign-function-internal
	 (function-record-lambda-list-info function-record)
	 function-record))))
  (let ((ftype           (or (cdr (assoc 'ftype decls)) 'function))
	(variable-record (cdr (assoc 'variable-record decls))))
    (handle-context nil
		    (local-variable-reference variable-record)
		    ftype
		    nil
		    (variable-record-foreign-type variable-record))))

(defun translate-free-function-reference (name type decls &optional usage)
  (when (eq type :foreign)
    (let ((descriptor (defined-as-function name *environment*)))
      (unless descriptor
	(error "There is no function named ~S" name))
      (return-from translate-free-function-reference
	(translate-foreign-function-internal
	 (function-descriptor-lambda-list-info descriptor)
	 name))))
  (when (or (function-notinline decls)
	    ;; Note: Check for notinline before checking for undefined.  
	    ;; This means that notinline declarations inhibit undefined 
	    ;; function warnings (hopefully a feature and not a bug).
	    (undefined-function-reference-p name usage))
    ;; For this to be correct, the following must be true:
    ;; 1. Neither of these functions (symbol-function and 
    ;;    setf-function) may be defined as translator special-forms.
    ;; 2. The compiler-macros and transforms for these functions 
    ;;    don't do anything when the argument name is declared 
    ;;    notinline or is undefined.
    ;; Note that this is necessary to prevent circularity when the
    ;; function symbol-function is declared notinline.
    (let ((reader (cond ((symbolp name) 'symbol-function)
			((setf-function-name-p name)
			 (setf name
			       (principal-name-of-function-name name))
			 'trun:setf-function)
			(t
			 (error "~S not valid in FUNCTION special form."
				name)))))
      (return-from translate-free-function-reference
	(translate-inline-function-call reader `(',name) t))))
  (let ((ftype (or (cdr (assoc 'ftype decls)) 'function))
	(descriptor (defined-as-function name *environment*)))	
    (when (function-descriptor-foreign-protocol descriptor)
      (error "Cannot efunctuate ~s because it is a foreign function."
	     name))
    (handle-context nil
		    (make-target-form 'global-function name)
		    ftype
		    nil
		    (translator-foreign-type :object))))

(defun translate-function-reference (name &optional type)
  (multiple-value-bind (usage bound-p decls)
      (translator-function-information name *environment*)
    (when (or (eq usage :macro)
	      (eq usage :special-form))
      (error "Cannot efunctuate ~s because it is a macro or special form."
	     name))
    (if bound-p
	(translate-bound-function-reference name type decls)
	(translate-free-function-reference name type decls usage))))

(defun translate-foreign-function-internal (ll-info function)
  (let* ((nreq (if ll-info
		   (lambda-list-info-required ll-info)
		   0))
	 (arg-types (make-list nreq :initial-element ':object)))
    (handle-context nil
		    (make-target-form 'function-name function)
		    t
		    nil
		    (translator-foreign-type 
		     `(:pointer (:function ,arg-types :values))))))

(defun undefined-function-reference-p (name &optional (usage nil usagep))
  (unless usagep
    (setf usage (translator-function-information name *environment*)))
  (when (null usage)
    (flag-undefined-function name)
    t))

(defun function-exists-at-runtime (name)
  (let ((descriptor (defined-as-function name *environment*)))
    (and descriptor
	 (cond ((null (function-descriptor-foreign-protocol descriptor))
		t)
	       ((tutil::function-descriptor-funcallable-p descriptor)
		:foreign)))))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Variable binding
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;; LET and LET* are conceptually very similar.  The difference
;;; is that LET* bindings are made sequentially, immediately after
;;; evaluating the init form for that binding, while for LET the
;;; bindings are not made until all the init forms have been evaluated.

;;; Since the handling for special binding (etc) is pretty hairy,
;;; LET* is implemented by a source-to-source transformation to nested
;;; LETs to avoid having to deal with it twice.

;;; *** There is a question about whether the *ansi-semantics* is
;;; *** interacting correctly with the delcaration processing in
;;; *** convert-let*-to-lets.

(deftranslate let* (bindings &body body)
  (if bindings
      (multiple-value-bind (real-body decls doc message)
	  (parse-body body)
	(declare (ignore doc))
	(with-translator-message message
	  (multiple-value-bind (names init-forms)
	      (canonicalize-let-bindings bindings) 
	    (multiple-value-bind (bound-decls free-decls)
		(parse-variable-declarations names decls *environment*)
	      (when (and bound-decls (not *ansi-semantics*))
		(setq bound-decls
		      (cons (append free-decls (car bound-decls)) 
			    (cdr bound-decls)))
		(setq free-decls nil))
	      (multiple-value-call #'compress-bindings
		names
		(re-translate-form
		 (convert-let*-to-lets names init-forms bound-decls
				       free-decls real-body)))))))
      (re-translate-form `(locally ,@body))))

(defun convert-let*-to-lets (names init-forms bound-decls free-decls body)
  (if names
      `(let ((,(car names) ,(car init-forms)))
	 (declare ,@(car bound-decls))
	 ,(convert-let*-to-lets (cdr names) (cdr init-forms)
				(cdr bound-decls) free-decls body))
      `(locally
	 (declare ,@free-decls)
	 ,@body)))


;;; The purpose of compress-bindings is to turn the nested
;;; WITH-LEXICAL-BINDING forms produced by walking the nested LETs
;;; into a single WITH-LEXICAL-BINDING form.  It can fail if any of the 
;;; LETs introduce special bindings, in which case this will just give up.
;;; This function is used by handling of things like DO*, which wants to
;;; produce binding code that looks like what DO would produce when possible
;;; so that it can recognize various idioms appearing in the target language.

(defun compress-bindings (names statements value type temps)
  (when (eq *context* ':result-type-only)
    (return-from compress-bindings
      (values nil nil type nil)))
  (let ((records nil)
	(init    nil)
	(tail    statements))
    (dolist (n names)
      (if (and tail
	       (null (cdr tail))
	       (eq (target-form-type (setq tail (car tail)))
		   'with-lexical-bindings)
	       (or (null (cadr tail))	; unused binding already removed
		   (eq n (variable-record-name (car (cadr tail))))))
	  (progn
	    (if (cadr tail)
		(push (car (cadr tail)) records))
	    (setq init (nconc init (butlast (cddr tail))))
	    (setq tail (last (cddr tail))))
	  (return-from compress-bindings
	    (values statements value type temps))))
    (setq statements (nconc init tail))
    (values
     (if records
	 (list (apply-make-target-form 'with-lexical-bindings
				       (nreverse records)
				       statements))
	 (nreverse statements))
     value type temps)))
    

;;; Destructuring-bind expands into a LET*.

(define-translator-macro destructuring-bind
    (lambda-list expression &body body)
  (let* ((whole  (make-symbol "WHOLE"))
	 (bindings (nreverse
		     (destructure-aux lambda-list whole
				      (list `(,whole ,expression)) nil))))
    `(let* ,bindings
       ,@(unless (cdr bindings)
	   `((declare (ignore ,whole))))
       ,@body)))


;;; This is the top-level processing for LET.  Walk the init forms in the
;;; outer lexical environment, then add the bindings to the environment
;;; and process the body.

(deftranslate let (bindings &body body)
  (if bindings
      (multiple-value-bind (names init-forms)
	  (canonicalize-let-bindings bindings)
	(multiple-value-bind (real-body decls doc message)
	    (parse-body body)
	  (declare (ignore doc))
	  (with-translator-message message
	    (multiple-value-bind (bound-decls free-decls)
		(parse-variable-declarations names decls *environment*)
	      (translate-let-aux
	       names bound-decls free-decls real-body *environment*
	       #'(lambda (records outer-env)
		   (translate-let-init-forms
		    init-forms records outer-env)))))))
      (translate-locally body)))

(defun check-translator-type (type env)
  (unless (translator-type-specifier-p type env)
    (warn "The type ~S is not known to the translator" type)
    (setq type t))
  type)

;;; Here's where the hair starts.  Add each binding to the environment and
;;; note which bindings are SPECIAL.  These need still more hair once all
;;; the lexical bindings have been processed.
;;; Note that this is also the hook for MULTIPLE-VALUE-BIND and
;;; lambda-binding.
(defun translate-let-aux (names bound-decls free-decls body outer-env
				init-fn &optional force-p)
  (setq outer-env (initialize-environment outer-env free-decls))
  (let* ((bind-one-variable-env outer-env)
	 (records   (mapcar #'bind-one-variable names bound-decls))
	 (specials  (mapcan #'variable-special-info records))
	 (inner-env (finalize-environment bind-one-variable-env free-decls)))
    (declare (special bind-one-variable-env))
    (multiple-value-bind (actual-records init-statements)
	(unless (eq *context* ':result-type-only)
	  (funcall init-fn records outer-env))
      (multiple-value-bind (body-statements body-value body-type body-temps)
	  (if (and specials (not (eq *context* ':result-type-only)))
	      (make-special-bindings (nreverse specials) body inner-env
				     *context* *result-type*)
	      (translate-progn-body body inner-env *context*
				    nil *result-type*))
	(values
	 (let ((statements (nconc body-statements init-statements)))
	   (if (or actual-records force-p)
	       (list (apply-make-target-form
		      'with-lexical-bindings
		      actual-records
		      (nreverse statements)))
	       statements))	     
	 body-value
	 body-type
	 body-temps)))))

(defun bind-one-variable (name bound-decl)
  (declare (special bind-one-variable-env))
  (setq bind-one-variable-env (bind-variable-name name bound-decl
						  bind-one-variable-env))
  (multiple-value-bind (usage bound-p decls)
      (translator-variable-information name bind-one-variable-env)
    (declare (ignore bound-p))
    (macrolet ((declared-p (decl-name)
		 `(not (null (cdr (assoc ,decl-name decls))))))
      (let* ((type-cons (assoc 'type decls))
	     (lisp-type (if (consp type-cons)
			    (check-translator-type (cdr type-cons)
						   bind-one-variable-env)
			    't))
	     (declared-foreign-type-cons (assoc 'tx:foreign-type decls))
	     (declared-foreign-type (and (consp declared-foreign-type-cons)
					 (translator-foreign-type
					  (cdr declared-foreign-type-cons))))
	     (nonrelocatable-p (declared-p 'nonrelocatable))
	     (closed-p (and (eq usage :lexical)
			    (declared-p 'tx:closed-variable)))
	     (special-p (eq usage :special))
	     (unread-p (and (eq usage :lexical)
			    (declared-p 'tx:unread-variable)))
	     (unwritten-p (and (eq usage :lexical)
			       (declared-p 'tx:unwritten-variable)))
	     (read-once-p (and (eq usage :lexical)
			       (declared-p 'tx:read-once-variable)))
	     (type-from-element-type-cons
	      (and unwritten-p
		   (assoc 'tx:type-from-element-type decls))))
	(when type-from-element-type-cons
	  (let ((etype (get-element-type-from-array-variable
			(cdr type-from-element-type-cons)
			bind-one-variable-env)))
	    (setq lisp-type (and-types lisp-type etype))))
	(multiple-value-bind (possible-foreign-type nonrelocating-p)
	    (if declared-foreign-type
		(progn
		  (setq lisp-type (and-types lisp-type
					     (lisp-type declared-foreign-type)
					     *environment*))
		  (values declared-foreign-type
			  (not (relocating-type-p lisp-type))))
		(lisp-type->foreign-type lisp-type))
	  (setf (cdr (assoc 'variable-record decls))
		(make-variable-record
		 :name name
		 :in-function *current-function*
		 :lisp-type lisp-type
		 :nonrelocatable-p nonrelocatable-p
		 :nonrelocatable-type (or nonrelocatable-p
					  nonrelocating-p)
		 :closed-p closed-p
		 :foreign-type (if (or closed-p special-p)
				   (translator-foreign-type :object)
				   possible-foreign-type)
		 :ignore-p (declared-p 'ignore)
		 :ignorable-p (declared-p 'ignorable)
		 :special-p special-p
		 :unread-p unread-p
		 :unwritten-p unwritten-p
		 :read-once-p read-once-p
		 :allow-type-from-init-p (not declared-foreign-type-cons))))))))

(defun get-element-type-from-array-variable (array-name env)
  (multiple-value-bind (array-usage array-bound-p array-decls)
      (translator-variable-information array-name env)
    (declare (ignore array-usage array-bound-p))
    (let* ((record (cdr (assoc 'variable-record array-decls)))
	   (array-type (and record (variable-record-lisp-type record)))
	   etype)
      (if (and array-type
	       (consp (setq array-type 
			    (tutil::fully-expand-type array-type env)))
	       (or (eq (car array-type) 'array)
		   (eq (car array-type) 'simple-array))
	       (setq etype (cadr array-type))
	       (not (eq etype '*)))
	  etype
	  t))))

(defun variable-special-info (record)
  (when (variable-record-special-p record)
    (list (cons (variable-record-name record) record))))


;;; OK, here is the hair for SPECIAL bindings.  There are a few different
;;; things going on here.
;;;
;;; First of all, we have to note the special bindings in the environment
;;; so that we can detect when somebody is trying to do a transfer of 
;;; control (as by GO or RETURN-FROM) that passes through the special 
;;; bindings, and do something to undo the bindings on the way.
;;;
;;; Related to this, the return context needs to be fiddled with, since 
;;; :return is not valid here and a temporary needs to be allocated in 
;;; some of the other cases.  
;;;
;;; Finally, the body statements need to be wrapped with code to bind 
;;; and unbind the specials.  What happens is that we evaluate the initial
;;; values into temporaries at the appropriate place required to preserve
;;; left-to-right order of evaluation of the init forms, and then make all
;;; the bindings after all of the init forms have been evaluated but before
;;; the body is evaluated.

(defun make-special-bindings (specials body env context return-type)
  (setq env (bind-special-variables (mapcar #'car specials) env))
  (case context
    (:result-type-only
     (translate-progn-body body env context nil))
    ((:return)
     (multiple-value-bind (body-statements body-value body-type body-temps)
	 (make-special-bindings-recursive specials body
					  env :values return-type)
       (declare (ignore body-value body-temps))
       (values (cons (make-target-form 'return-stored-values) body-statements)
	       nil body-type nil)))
    (t
     (if (or (eq context *value-context*)
	     (eq context *predicate-context*))
	 (with-temporary-for-value context
	   (make-special-bindings-recursive specials body
					    env context return-type))
	 (make-special-bindings-recursive specials body
					  env context return-type)))))

(defun make-special-bindings-recursive (specials body
						 env context return-type)
  (if specials
      (multiple-value-bind (body-statements body-value body-type body-temps)
	  (make-special-bindings-recursive (cdr specials) body
					   env context return-type)
	(values (list (apply-make-target-form
		       'with-special-binding
		       nil
		       (car (car specials))
		       (local-variable-reference (cdr (car specials)))
		       (nreverse body-statements)))
		body-value body-type body-temps))
      (translate-progn-body body env context nil return-type)))


;;; A helper function:  parse a binding list for LET or LET*, returning
;;; a list of variable names and a list of init forms.

(defun canonicalize-let-bindings (bindings)
  (let ((names  nil)
	(init-forms nil))
    (dolist (b bindings)
      (cond ((symbolp b)
	     (push b names)
	     (push nil init-forms))
	    ((consp b)
	     (push (car b) names)
	     (push (cadr b) init-forms))
	    (t (error "Bad LET binding syntax: ~s" b))))
    (values (nreverse names) (nreverse init-forms))))


(defun type-from-init-simple-p (form env)
  (or (atom (setq form (apply-macros form env)))
      (let ((fn (car form)))
	(and (symbolp fn)
	     (case fn
	       (the
		(type-from-init-simple-p (caddr form) env))
	       ((tx:typed-foreign-aref tx:foreign-function)
		t)
	       (t
		(not (defined-as-special-form fn))))))))

;;; Another helper function:  translate the init forms for the variables
;;; being bound by a LET.  Returns a list of records that are actually
;;; "used", and a list of the initialization statements.

(defun translate-let-init-forms (init-forms records outer-env)
  (let ((actual-records   nil)
	(init-statements  nil))
    (do* ((records records (cdr records))
	  (record (car records) (car records))
	  (init-forms init-forms (cdr init-forms)))
	 ((null records) nil)
      (let* ((init-form (car init-forms))
	     (bind-var-p (generate-lexical-variable-binding-p record))
	     (context
	      (if bind-var-p
		  (progn
		    (check-ignore-used-variable record "Variable")
		    (push record actual-records)
		    (make-target-form 'local-variable record))
		  (progn
		    (check-ignore-unused-variable record "Variable")
		    *ignore-context*))))
	(when (and bind-var-p
		   (variable-record-unwritten-p record)
		   (not (variable-record-special-p record))
		   (not (variable-record-closed-p record))
		   (variable-record-allow-type-from-init-p record))
	  (if (type-from-init-simple-p init-form outer-env)
	      (setf (variable-record-type-from-init-p record) t)
	      (multiple-value-bind (statements value type)
		  (translate-form init-form
				  outer-env
				  :result-type-only
				  (variable-record-lisp-type record))
		(declare (ignore statements value))
		(setq type (and-types (single-value-type type)
				      (variable-record-lisp-type record)))
		(setf (variable-record-lisp-type record) type)
		(multiple-value-bind (possible-foreign-type nonrelocating-p)
		    (lisp-type->foreign-type type)
		  (setf (variable-record-foreign-type record)
			possible-foreign-type)
		  (setf (variable-record-nonrelocatable-type record)
			(or (variable-record-nonrelocatable-p record)
			    nonrelocating-p))))))
	(let ((statements (translate-form init-form
					  outer-env
					  context
					  (variable-record-lisp-type record))))
	  (setq init-statements (nconc statements init-statements)))))
    (values (nreverse actual-records) init-statements)))

;;; Determine whether a variable binding is actually "used".

#||
 (defmacro variable-binding-used-p (record)
   (once-only (record)
     `(or (variable-record-referenced-p ,record)
	  (variable-record-modified-p ,record))))
||#

(defmacro variable-binding-used-p (record)
  (once-only (record)
    `(or (variable-record-special-p ,record)
	 (not (and (variable-record-unread-p ,record)
	       (variable-record-unwritten-p ,record))))))

#||
 (defun generate-lexical-variable-binding-p (record &aux temp)
   (or (and (setf temp (variable-record-referenced-p record))
	    (not (eq temp :ignore)))
       (some #'(lambda (function-record)
		 (not (eq (function-record-classification function-record)
			  :ignore)))
	     (the list (variable-record-modified-p record)))))
||#

(defun generate-lexical-variable-binding-p (record)
  (variable-binding-used-p record))

;;; Complain about references/modifications to variables declared IGNORE, and
;;; about variables not referenced or modified but not declared IGNORABLE.

(defun check-ignore-used-variable (record binding-type)
  (when (variable-record-ignore-p record)
    (warn "~A ~S is declared IGNORE but is used anyway."
	  binding-type
	  (variable-record-name record))))

(defun check-ignore-unused-variable (record binding-type)
  (unless (or (variable-record-ignore-p record)
	      (variable-record-ignorable-p record)
	      (eq (variable-record-referenced-p record) :ignore))
    ;; This should be a style-warning, not a "real" warning.
    (warn "~A ~S is bound but not used or declared IGNORE."
	  binding-type
	  (variable-record-name record))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Function binding
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;; FLET and LABELS are very similar.  The only difference is whether
;;; the environment in which the function bodies are walked includes
;;; the function name bindings or not.  In effect, FLET is like LET
;;; and LABELS is like binding the function names to undefined initial
;;; values and then immediately setq'ing them inside the scope of the
;;; name bindings but before any of the body forms.
;;;
;;; The tricky thing to remember here is that each function name binding
;;; maps onto a C variable name binding, so there is a variable record
;;; as well as a function record associated with each of the local
;;; functions.


(deftranslate flet (bindings &body body)
  (translate-flet-labels bindings body nil))

(deftranslate labels (bindings &body body)
  (translate-flet-labels bindings body t))

(defun new-function-record-for-function (binding)
  (make-function-record 
   :name (car binding)
   :lambda-list-info (compute-lambda-list-info (cadr binding))))

(defun translate-flet-labels (bindings body labels-p)
  (if bindings
      (let ((names (mapcar #'car bindings)))
	(multiple-value-bind (real-body decls doc message)
	    (parse-body body)
	  (declare (ignore doc))
	  (with-translator-message message
	    (multiple-value-bind (bound-decls free-decls)
		(parse-function-declarations names decls *environment*)
	      (translate-flet-labels-aux
	       names
	       bound-decls
	       (mapcar #'new-variable-record-for-function names)
	       (mapcar #'new-function-record-for-function bindings)
	       bindings
	       real-body
	       free-decls
	       *environment*
	       labels-p
	       message)))))
      (translate-locally body)))

(defun new-variable-record-for-function (name)
  (new-variable-record (principal-name-of-function-name name)))


;;; This is similar to LET except there is no hair for special bindings.

(defun translate-flet-labels-aux (names bound-decls vrecords frecords bindings
					body free-decls outer-env labels-p
					&optional message)
  (setq outer-env (initialize-environment outer-env free-decls))
  (let ((inner-env        outer-env))
    ;; First set up the environment containing the function name bindings.
    (do ((names names (cdr names))
	 (bound-decls bound-decls (cdr bound-decls))
	 (vrecords vrecords (cdr vrecords))
	 (frecords frecords (cdr frecords)))
	((null names) nil)
      (setq inner-env
	    (bind-function-name (car names) (car bound-decls)
				(car vrecords) (car frecords)
				inner-env)))
    (setq inner-env (finalize-environment inner-env free-decls))
    (multiple-value-bind (actual-records init-statements)
	(unless (eq *context* ':result-type-only)
	  (translate-flet-labels-init-forms
	   vrecords frecords bindings
	   (if labels-p inner-env outer-env)
	   inner-env
	   message))
      (multiple-value-bind (body-statements body-value body-type body-temps)
	  (translate-progn-body body inner-env *context* nil *result-type*)
	(values
	 (list (apply-make-target-form
		'with-lexical-bindings
		actual-records
		(nreconc init-statements
			 (nreverse body-statements))))
	 body-value body-type body-temps)))))

;;; Now walk the function definitions in the appropriate environment.
;;; Propagate declarations applying to function name bindings to
;;; the function-records corresponding to their definitions.
;;; *** This isn't really handling the global-p stuff right.  As
;;; *** well as setting the flag in the function-definition, it
;;; *** should generate code differently -- storing the function into
;;; *** the global-function instead of the local-variable, etc.

(defun translate-bound-function (vrecord frecord binding env inner-env message)
  (let ((name (car binding)))
    (multiple-value-bind (usage bound-p decls)
	(translator-function-information name inner-env)
      (declare (ignore usage bound-p))
      (let* ((classification (if (rest (assoc 'global-function decls))
				 ':bound-global ':local)))
	(setf (function-record-classification frecord) classification)
	(translate-function-definition-aux
	 frecord
	 (cadr binding)			; lambda-list
	 (cddr binding)			; body
	 classification
	 env
	 message)
	(let ((fname-cons (assoc 'function-name decls)))
	  (when fname-cons
	    (setf (function-record-name frecord) (cdr fname-cons))))
	(unless (or (cdr (assoc 'tx:function-needs-environment decls))
		    (cdr (assoc 'tx:function-needs-object decls)))
	  (return-from translate-bound-function
	    (values nil (list (make-target-form 'function-definition
						frecord)))))
	(when (cdr (assoc 'tx:closed-function decls))
	  (setf (variable-record-closed-p vrecord) t))
	(when (cdr (assoc 'ignore decls))
	  (setf (variable-record-ignore-p vrecord) t))
	(when (cdr (assoc 'ignorable decls))
	  (setf (variable-record-ignorable-p vrecord) t))
	(values vrecord
		(list (make-target-form 'function-definition frecord)
		      (make-target-form
		       'setq
		       (make-target-form 'local-variable vrecord)
		       (make-target-form 'function-object frecord))))))))

(defun translate-flet-labels-init-forms (vrecords frecords bindings 
						  env inner-env
						  &optional message)
  (let ((variable-records nil)
	(statements nil))
    (loop (unless bindings (return nil))
	  (multiple-value-bind (variable-record init-statements)
	      (translate-bound-function (pop vrecords) (pop frecords)
					(pop bindings)
					env inner-env message)
	    (when variable-record
	      (push variable-record variable-records))
	    (setq statements (nreconc init-statements statements))))
    (values (nreverse variable-records) statements)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Function definition
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;; Function definitions are processed by binding the formal parameters
;;; to the C function (the required arguments to the Lisp function) like 
;;; LET and the remaining parameters from the lambda-list as an explicit 
;;; LET*.  The only tricky thing is rebinding *current-function* before 
;;; walking any of the bindings or the body.

(defun translate-function-definition (name lambda-list body)
  (let ((function-record
	 (unless (eq *context* ':result-type-only)
	   (translate-function-definition-aux
	    name lambda-list body
	    (if (eq *context* *ignore-context*) :ignore :local)))))
      (handle-context
	(list (make-target-form 'function-definition function-record))
	(make-target-form 'function-object function-record)
	(if (eq *context* *ignore-context*) nil 'function)
	nil
	(translator-foreign-type :object))))

(defun find-nonrelocating-declaration (name decls)
  (dolist (decl decls nil)
    (when (and (consp decl) (eq (car decl) 'tx:nonrelocating))
      (dolist (n (cdr decl))
	(when (eq n name)
	  (return-from find-nonrelocating-declaration t))))))

(defun translate-function-definition-aux (name lambda-list body
					       classification
					       &optional (env *environment*)
					       message)
  (translate-function-internal name lambda-list body
			       classification env message))

(defun translate-function-internal (name lambda-list body
					 classification env message
					 &optional foreign-p
					 argument-types return-type
					 sets-values-count-p
					 &aux new-function)
  (when (function-record-p name)
    (setq new-function name)
    (setq name (function-record-name new-function)))
  (with-translator-message (unless message name)
    (setq env (translator-augment-environment env :function-name name))
    (unless new-function
      (setq new-function
	    (new-function-record (or name (make-symbol "LOCAL_FN"))
				 classification)))
    (unless (function-record-lambda-list-info new-function)
      (setf (function-record-lambda-list-info new-function)
	    (compute-lambda-list-info lambda-list)))
    (multiple-value-bind (real-body decls doc) (parse-body body t)
      (when name
	(setq real-body `((block ,(body-block-name name) ,@real-body))))
      (setf (function-record-documentation new-function) doc)
      (multiple-value-bind (usage boundp info)
	  (translator-function-information name env)
	(declare (ignore usage))
	(let ((nonrelocating-p 
	       (or (not (relocating-function-p* name boundp info))
		   (and name (find-nonrelocating-declaration name decls))))
	      (one-value-p
	       (or (and foreign-p (not sets-values-count-p))
		   (returns-one-value-function-p* name boundp info)
		   (and name (find-returns-one-value-declaration name decls))))
	      (needs-environment-p
	       (cdr (assoc 'tx:function-needs-environment info))))
	  (when (and one-value-p needs-environment-p)
	    (error "Function ~S needs an environment, so cannot be declared ~S"
		   name 'tx:returns-one-value))
	  (setf (function-record-nonrelocating-p new-function) nonrelocating-p)
	  (setf (function-record-returns-one-value-p new-function) one-value-p)
	  (when (cdr (assoc 'dllexport info))
	    (setf (function-record-classification new-function)
		  (setq classification
			(case classification
			  (:global ':global-dllexport)
			  (:callable ':callable-dllexport)
			  (t classification)))))
	  (multiple-value-bind (required-args bindings 
					      variadic-p simple-variadic-p)
	      (parse-function-lambda-list lambda-list nonrelocating-p)
	    (setf (function-record-variadic-p new-function) variadic-p)
	    (when foreign-p
	      (when variadic-p
		(error "Attempt to translate variadic foreign-callable ~
                        function ~A" name))
	      (setq decls (nconc (mapcar #'(lambda (arg type)
					     `(tx:foreign-type ,type ,arg))
					 required-args argument-types)
				 decls)))
	    (multiple-value-bind (bound-decls free-decls)
		(parse-variable-declarations required-args decls env)
	      (setq real-body `((let* ,bindings (declare ,@free-decls)
				   ,@(when simple-variadic-p
				       `((trun:%nr-end-args)))
				   ,@real-body)))
	      (setq return-type (translator-foreign-type 
				 (or return-type :object)))
	      (setf (function-record-foreign-return-type new-function)
		    return-type)
	      (setf (function-record-foreign-argument-types new-function)
		    argument-types)
	      (let* ((*current-function* new-function)
		     (void-p (equal "void" (c-type return-type)))
		     (return-variable
		      (when (and one-value-p (not void-p))
			(make-variable-record
			 :name (make-symbol "RESULT")
			 :in-function *current-function*
			 :foreign-type return-type
			 :read-once-p t)))
		     (*context*
		      (cond (return-variable
			     (make-target-form 'local-variable return-variable))
			    (void-p
			     *ignore-context*)
			    (t
			     :return)))
		     (*reason-for-multiple-values-context*
		       (when (eq *context* :return)
			 (list :tail-call
			       (current-function-name env)))))
		(multiple-value-bind (arguments statements)
		    (mung-closed-arguments
		     (translate-let-aux 
		      required-args bound-decls nil real-body
		      env
		      #'(lambda (records env)
			  (declare (ignore env))
			  (values records nil))
		      t)
		     argument-types)
		  (when return-variable
		    (multiple-value-bind (value setq)
			(do-read-once-optimization return-variable)
		      (if setq
			  (progn
			    (remove-setq-statement return-variable setq)
			    (setq return-variable nil))
			  (setq value (local-variable-reference
				       return-variable)))
		      (push (make-target-form 'return-value value)
			    statements)))
		  (setq statements (nreverse statements))
		  (setf (function-record-statements new-function)
			(if return-variable
			    (list (apply-make-target-form
				   'with-lexical-bindings
				   (list return-variable)
				   statements))
			    statements))
		  (setf (function-record-argument-variables new-function)
			arguments)))))))))
  new-function)

(defun find-returns-one-value-declaration (name decls)
  (dolist (decl decls nil)
    (when (and (consp decl) (eq (car decl) 'tx:returns-one-value))
      (dolist (n (cdr decl))
	(when (eq n name)
	  (return-from find-returns-one-value-declaration t))))))

;;; apparently unused: from patch 27. -alatto, 6/26/07
(defun returns-one-value-function-p (name &optional env)
  (multiple-value-bind (usage boundp info)
      (translator-function-information name env)
    (declare (ignore usage))
    (returns-one-value-function-p* name boundp info)))

(defun returns-one-value-function-p* (name boundp info)
  (or (eql 1 (cdr (assoc 'values-count info)))
      (let ((descriptor (unless boundp (defined-as-function name))))
	(and descriptor
	     (not (function-descriptor-sets-values-count-p descriptor))))))

;; used only in make-method-body.lisp and slot-access-std-class.lisp
(defun variable-bound-at-current-function-level (var)
  (multiple-value-bind (usage locally-bound-p declarations
			contour inner-fn-contour)
      (translator-variable-information var *environment* t)
    (declare (ignore locally-bound-p declarations contour))
    (and (eq usage :lexical)
	 (null inner-fn-contour))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Defcallable definition
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;; defcallables are just like other function definitions, except that
;;; we generate target code to box the arguments and unbox the return
;;; value.

(defun translate-defcallable-aux (lisp-name lambda-list body
					    argument-types return-type
					    sets-values-count-p)
  (destructuring-bind (ignore lisp-name lambda-list &body body)
      (note-closed-variables `(defun ,lisp-name ,lambda-list ,@body)
			     *value-context*)
    (declare (ignore ignore))
    (translate-function-internal lisp-name lambda-list body
				 ':callable *environment* nil
				 t argument-types return-type 
				 sets-values-count-p)))


;;; If any of the argument variables are closed, we've got problems, since
;;; the caller is passing initialization values and we need to have the
;;; function allocate and initialize a binding object.  This function is
;;; necessary because of the weird way the bindings of the required 
;;; arguments to the function are being handled.
;;; Note that this function knows that it gets a list consisting
;;; of a single WITH-LEXICAL-BINDINGS construct as its argument.

(defun mung-closed-arguments (statements &optional foreign-types)
  (declare (special *fix-closed-variable-setqs*))
  (let ((real-arguments   nil)
	(records          (cadr (car statements)))
	result-exp
	(real-statements  (cddr (car statements)))
	(real-records     nil)
	(foreign-types-rev (reverse foreign-types)))
    (dolist (r (nreverse records))
      (let ((foreign-type (or (pop foreign-types-rev)
			      (translator-foreign-type :object))))
	(if (or (if *fix-closed-variable-setqs*
		    (variable-record-actual-closed-p r)
		    (variable-record-closed-p r))
		(not (eq (variable-record-foreign-type r)
			 foreign-type)))
	    (let* ((name (symbol-name (variable-record-name r)))
		   (arg (new-variable-record
			 (make-symbol (sformat "~a-INIT" name))
			 foreign-type)))
	      (push arg real-records)
	      (push arg real-arguments)
	      (multiple-value-setq (real-statements result-exp)
		(foreign-type-coerce real-statements
				     (local-variable-reference arg)
				     foreign-type
				     (variable-record-foreign-type r)))
	      (push (make-target-form 'setq
				      (make-target-form 'local-variable r)
				      result-exp)
		    real-statements))
	    (push r real-arguments)))	      
      (push r real-records))
    (values
     real-arguments
     (list (apply-make-target-form
	    'with-lexical-bindings
	    real-records
	    real-statements)))))


;;; Parse a lambda-list for a function definition.  Return a list of
;;; the required arguments, a list of bindings in LET* syntax, and a
;;; boolean indicating whether the function accepts variable numbers
;;; of arguments.
;;;*** Note that this isn't quite correct, since X3J13 has clarified
;;;*** that svars must be bound *after* the corresponding &optional
;;;*** or &key parameter.  The reason for not doing so here is that
;;;*** it requires introducing ugly temporaries.

(defun parse-function-lambda-list (lambda-list &optional non-relocating-p)
  (let* ((required-args  nil)
	 (bindings     nil)
	 (variadic-p   nil)
	 (simple-variadic-p (and non-relocating-p
				 (not (or (memq '&rest lambda-list)
					  (memq '&key lambda-list))))))
    (multiple-value-bind (optional-arg-p optional-arg)
	(if simple-variadic-p
	    (values '(trun:%nr-optional-arg-p) '(trun:%nr-optional-arg))
	    (values '(trun:%optional-arg-p) '(trun:%optional-arg)))
      (parse-lambda-list
       lambda-list
       :required #'(lambda (name)
		     (push name required-args))
       :optional #'(lambda (name default defaultp svar svar-p)
		     (declare (ignore defaultp svar-p))
		     (setq variadic-p t)
		     (if svar
			 (progn
			   (push `(,svar ,optional-arg-p) bindings)
			   (push `(,name (if ,svar
					     ,optional-arg
					     ,default))
				 bindings))
			 (push `(,name
				 (if ,optional-arg-p
				     ,optional-arg
				     ,default))
			       bindings)))
       :rest     #'(lambda (name)
		     (setq variadic-p t)
		     (push `(,name  (trun:%rest-arg)) bindings))
       :keyp     #'(lambda ()
		     (setq variadic-p t))
       :key      #'(lambda (name keyword default defaultp svar svar-p)
		     (declare (ignore defaultp svar-p))
		     (unless svar
		       (setq svar (make-symbol (sformat "~a-P" name))))
		     (push `(,svar (trun:%keyword-arg-p ,keyword)) bindings)
		     (push `(,name (if ,svar
				       (trun:%keyword-arg ,svar)
				       ,default))
			   bindings))
       :aux      #'(lambda (name default defaultp)
		     (declare (ignore defaultp))
		     (push `(,name ,default) bindings)))
      (values (nreverse required-args)
	      (nreverse bindings)
	      variadic-p
	      (and variadic-p simple-variadic-p)))))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    macrolet & symbol-macrolet
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define-toplevel-form macrolet (bindings &body body)
  (multiple-value-bind (real-body decls doc message)
      (parse-body body nil)
    (declare (ignore doc))
    (with-translator-message message
      (let* ((defs (mapcar #'canonicalize-macrolet-binding bindings))
	     (env (translator-augment-environment *environment*
						  :macro defs :declare decls)))
	(if *toplevel-p*
	    (translate-toplevel-body real-body env *compile-time-too*)
	    (translate-progn-body real-body env *context*
				  nil *result-type*))))))

(defun canonicalize-macrolet-binding (binding)
  (list* (car binding)
	 (translator-enclose
	  (translator-parse-macro (car binding) (cadr binding) (cddr binding))
	  *environment*)
	 (cdr binding)))

(define-toplevel-form symbol-macrolet (bindings &body body)
  (multiple-value-bind (real-body decls doc message)
      (parse-body body nil)
    (declare (ignore doc))
    (with-translator-message message
      (let ((env (translator-augment-environment *environment*
		    :symbol-macro bindings :declare decls)))
	(if *toplevel-p*
	    (translate-toplevel-body real-body env *compile-time-too*)
	    (translate-progn-body real-body env *context*
				  nil *result-type*))))))

;;; -*- Mode: Lisp; Package: TIMPL; Syntax: Common-Lisp -*-
;;;
;;; codewalk.lsp -- code walker protocol
;;;
;;; Author :  Sandra Loosemore
;;; Date   :  14 May 1990
;;;
;;; Copyright (c) 1990, Chestnut Software Inc.
;;;
;;;

(in-package "TIMPL")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/codewalk.lisp,v $"
 "$Revision: 1.16 $"
 "$Date: 2007/11/15 20:05:33 $")

;;; Code walker functions are passed three arguments:
;;;    (1) the form to be walked
;;;    (2) the syntactic environment in which to walk it
;;;        (see env.l for definitions)
;;;    (3) a context flag indicating how the return value is to be used.
;;;        (see handle-context below)
;;; Three values are returned:
;;;    (1) A list of target-language statements to be executed 
;;;        for side-effect, in reverse order.  This list can be 
;;;        destructively modified by the caller.
;;;    (2) A target-language expression which provides the return value 
;;;        from the form.  This result is NIL if the form is being executed 
;;;        for side-effect only.
;;;    (3) The type of the return value.
;;; Top-level forms and EVAL-WHEN processing are handled using a slightly
;;;    different mechanism.

;;; Some preliminary declarations.
;;; The environment and context arguments passed to translate-form are
;;; stored in these globals instead of being passed as arguments to the
;;; individual translator handlers.  They should be treated as read-only
;;; within the handlers.

(defvar *environment* nil)
(defvar *context* nil)
(defvar *result-type* '(values &rest t))

(define-forward-variable-reference *value-context*) 
(define-forward-variable-reference *predicate-context*)
(define-forward-variable-reference *ignore-context*)

;;; These variables are used to hold the accumulated results from processing
;;; the top-level forms and other initialization code in the file.  Eventually
;;; the values are transferred to the function object representing the
;;; init code for the file.

(defvar *initcode-locals* nil)
(defvar *initcode-catches* 0)
(defvar *initcode-specials* 0)
(defvar *initcode-areas* 0)
(defvar *initcode-frontiers* 0)
(defvar *initcode-statements* nil)
(defvar *initcode-statements-last* nil)
(defvar *initcode-local-constants* nil)
(defvar *initcode-local-constants-last* nil)
(defvar *initcode-functions* nil)
(defvar *initcode-functions-last* nil)

;;; Translation of toplevel forms happens a little differently than
;;; translation of non-toplevel forms, mostly with regard to things
;;; like PROGN and EVAL-WHEN.

;;; The translator's own macro expansions might include references 
;;; to things that cannot be executed in the host Lisp in
;;; compile-time-too situations.  So we just execute the body
;;; immediately using the host Lisp's expansion for any global macro
;;; references, and then re-process the body.

(defun translate-toplevel-form (form *environment* *compile-time-too*)
  (let ((function  nil)
	(temp      nil)
	(new-form  nil)
	(macro-env nil))
    (cond ((symbolp form)
	   (if *environment*
	       (multiple-value-bind (expansion macro-p)
		   (translator-macroexpand-1 form *environment*)
		 (when macro-p
		   (translate-toplevel-form expansion *environment*
					    *compile-time-too*)))))
	  ((not (consp form))
	   nil)
	  ((lambda-expression-p
	    (loop (setq function (car form))
		  (unless (and (eq function 'funcall)
			       (consp (cadr form))
			       (eq (caadr form) 'function))
		    (return function))
		  (setq form `(,(cadadr form) ,@(cddr form)))))
	   (translate-leaf-toplevel-form form))
	  ((not (symbolp function))
	   (error "Invalid form syntax: ~s" form))
	  ((setq temp (defined-as-toplevel-form function))
	   (funcall temp form))
	  ((defined-as-special-form function)
	   (translate-leaf-toplevel-form form))
	  ((when (and (not (function-notinline-p function *environment*))
		      (setq temp
			    (translator-compiler-macro-function function
								*environment*))
		      (not (eq form
			       (setq new-form
				     (call-macro-function temp form
							  *environment*))))))
	   (if (and *compile-time-too*
		    (defined-as-compiler-macro function
			*initial-global-environment*))
	       (progn
		 (eval-in-env form *environment*)
		 (translate-toplevel-form new-form *environment* nil))
	       (translate-toplevel-form new-form *environment*
					*compile-time-too*)))
	  ((multiple-value-setq (temp macro-env)
	     (translator-macro-function function *environment*))
	   (setq new-form (call-macro-function temp form macro-env))
	   (if (and *compile-time-too*
		    (defined-as-macro function *initial-global-environment*))
	       (progn
		 (eval-in-env form *environment*)
		 (translate-toplevel-form new-form *environment* nil))
	       (translate-toplevel-form new-form *environment*
					*compile-time-too*)))
	  (t
	   (translate-leaf-toplevel-form form)))))


(defstruct var-info
  (flags 0)
  (type-from-element-type-var nil))

(define-flags var-info- var-info-flags
  (closed-p nil)
  (has-a-reference-p nil)
  (has-a-setq-p nil)
  (has-multiple-references-p nil)
  (function-p nil)
  (needs-environment-p nil)
  (needs-function-object-p nil)
  (known-closed-p nil)
  (known-needs-environment-p nil))

;walk::*variable-binding-declarations-hook*
(defun make-variable-binding-declarations (name)
  (list (list name 'var-info (make-var-info))))

(defstruct (fun-info
	     (:include var-info))
  (callers-alist nil)
  (closed-function-declaration nil)
  (needs-environment-declaration nil))

(defun make-function-binding-declarations (name)
  (let ((var-info (make-fun-info)))
    (setf (var-info-function-p var-info) t)
    (list (list name 'var-info var-info))))

(defun ncv-walk-bound-functions (bindings function-env walker body-env)
  (let ((walked nil))
    (loop (let ((changed-p nil)
		(next nil))
	    (dolist (binding bindings)
	      (multiple-value-bind (usage locally-bound-p declarations)
		  (translator-function-information (car binding) body-env)
		(declare (ignore usage locally-bound-p))
		(let ((info (cdr (assq 'var-info declarations))))
		  (if (and info (var-info-has-a-reference-p info))
		      (progn
			(push (walk:walk-function-1 binding function-env 
						    walker info)
			      walked)
			(setq changed-p t))
		      (push binding next)))))
	    (unless changed-p 
	      (return (nreverse walked)))
	    (setq bindings (nreverse next))))))

(defun note-closed-variables (toplevel-form &optional *context*)
  ;; Currently, *context* isn't actually used.
  (walk:walk-form toplevel-form
		  :environment *environment*
		  :walk-function #'note-closed-variables-walk
		  :setq-hook #'note-variable-setq
		  :added-declarations-hook
		  #'make-closed-variables-declarations
		  :variable-binding-declarations-hook
		  #'make-variable-binding-declarations
		  :function-binding-declarations-hook
		  #'make-function-binding-declarations
		  :walk-bound-functions-hook
		  #'ncv-walk-bound-functions))

#+ignore ; binghe, 2009/04/03: duplicated definitions
(defun make-function-binding-declarations (name)
  (let ((var-info (make-var-info)))
    (setf (var-info-function-p var-info) t)
    (list (list name 'var-info var-info))))

(defun note-closed-variables-walk (form environment function)
  (declare (ignore function))
  (cond ((symbolp form)
	 (note-variable-use form nil environment))
	((not (consp form)))
	((or (eq (car form) 'function)
	     (eq (car form) 'tx:function-object))
	 (when (or (symbolp (cadr form))
		   (and (consp (cadr form))
			(eq (caadr form) 'setf)))
	   (note-function-use (cadr form) environment 'object)))
	((eq (car form) 'tx:foreign-function)
	 (note-function-use (cadr form) environment 'foreign))
	((eq (car form) 'return-from)
	 (let* ((name (cadr form))
		(record (block-binding name environment nil nil)))
	   (tagbody
	      repeat
	      (when record
		(cond ((block-record-hard-p record)
		       (note-variable-use (block-record-hard-p record)
					  nil environment))
		      ((block-record-break-p record)
		       (setq record (block-binding name environment t nil))
		       (go repeat)))))))
	(t
	 (let ((fd (defined-as-function (car form)))
	       array-var value-var)
	   (when (and fd 
		      (function-descriptor-array-setf-function-p fd)
		      (symbolp (setq array-var (cadr form)))
		      (symbolp (setq value-var (car (last form)))))
	     (note-variable-type-from-element-type array-var value-var 
						   environment)))
	 (note-function-use (car form) environment 'call)))
  (values form nil))

(defun note-variable-type-from-element-type (array-var value-var environment)
  (multiple-value-bind (usage locally-bound-p declarations)
      (translator-variable-information value-var environment)
    (declare (ignore locally-bound-p))
    (when (eq usage :lexical)
      (let ((info (cdr (assq 'var-info declarations))))
	(when info
	  (setf (var-info-type-from-element-type-var info) array-var))))))

(defun note-variable-setq (variable env)
  (note-variable-use variable t env))

(defun note-function-use (name environment use-type)
  (note-variable-use-internal name nil environment use-type))

(defun note-variable-use (name setq-p environment)
  (note-variable-use-internal name setq-p environment 'variable))

(defun note-variable-use-internal (name setq-p environment use-type)
  (let ((var-p (eq use-type 'variable)))
    (multiple-value-bind (usage boundp declarations)
	(if var-p
	    (translator-variable-information name environment)
	    (translator-function-information name environment))
      (when (and (eq usage (if var-p ':lexical ':function)) boundp)
	(let ((binding-env (cdr (assoc 'tx:binding-environment declarations)))
	      (info (cdr (assq 'var-info declarations))))
	  (when info
	    (note-variable-use-internal-1 
	     name setq-p info 
	     environment binding-env use-type)))))))



(defun note-variable-use-internal-1 (name setq-p info 
					  use-env binding-env use-type)
  (declare (ignore name))
  (when (or (var-info-has-a-setq-p info)
	    (var-info-has-a-reference-p info)
	    (function-or-multiple-execution-env-p use-env binding-env))
    (setf (var-info-has-multiple-references-p info) t))
  (if setq-p
      (setf (var-info-has-a-setq-p info) t)
      (setf (var-info-has-a-reference-p info) t))
  (let ((closed-p nil))
    (map-over-enclosing-functions 
     #'(lambda (function-name function-info)
	 (case use-type
	   ((variable object)
	    (when function-info
	      (setf (var-info-needs-environment-p function-info) t))
	    (setq closed-p t))
	   (function
	    (unless (assq function-info (fun-info-callers-alist info))
	     (push (cons function-name function-info)
		   (fun-info-callers-alist info))))))
     use-env binding-env)
    (when closed-p
      (setf (var-info-closed-p info) t)))
  (when (eq use-type 'object)
    (setf (var-info-needs-function-object-p info) t))
  t)

(defun make-closed-variables-declarations (vars functions env)
  (let ((closed-vars nil)
	(functions-needing-object nil)
	(vars-without-references nil)
	(vars-without-setqs nil)
	(vars-with-one-reference nil)
	(type-from-element-type-declarations nil)
	(function-info-alist nil)
	(closed-function-declaration nil)
	(needs-environment-declaration nil))
    (dolist (var vars)
      (multiple-value-bind (usage locally-bound-p declarations)
	  (translator-variable-information var env)
	(declare (ignore usage locally-bound-p))
	(let ((info (cdr (assq 'var-info declarations))))
	  (when info
	    (when (var-info-closed-p info)
	      (push var closed-vars))
	    (if (var-info-has-a-reference-p info)
		(unless (var-info-has-multiple-references-p info)
		  (push var vars-with-one-reference))
		(push var vars-without-references))
	    (unless (var-info-has-a-setq-p info)
	      (push var vars-without-setqs))
	    (when (var-info-type-from-element-type-var info)
	      (push `(tx:type-from-element-type 
		      ,(var-info-type-from-element-type-var info)
		      ,var)
		    type-from-element-type-declarations))))))
    (dolist (function functions)
      (multiple-value-bind (usage locally-bound-p declarations)
	  (translator-function-information function env)
	(declare (ignore usage locally-bound-p))
	(let ((info (cdr (assq 'var-info declarations))))
	  (when info
	    (push (cons function info) function-info-alist)
	    (when (var-info-needs-function-object-p info)
	      (push function functions-needing-object))))))
    (when function-info-alist
      (setq closed-function-declaration (list 'tx:closed-function))
      (setq needs-environment-declaration 
	    (list 'tx:function-needs-environment))
      (dolist (function+info function-info-alist)
	(let ((info (cdr function+info)))
	  (setf (fun-info-closed-function-declaration info)
		closed-function-declaration)
	  (setf (fun-info-needs-environment-declaration info)
		needs-environment-declaration)))
      (add-function-declarations function-info-alist))
    `(,@(when closed-vars
	  `((tx:closed-variable ,@closed-vars)))
      ,@(when closed-function-declaration
	  `(,closed-function-declaration))
      ,@(when vars-without-references
	  `((tx:unread-variable ,@vars-without-references)))
      ,@(when vars-without-setqs
	  `((tx:unwritten-variable ,@vars-without-setqs)))
      ,@(when vars-with-one-reference
	  `((tx:read-once-variable ,@vars-with-one-reference)))
      ,@(when needs-environment-declaration
	  `(,needs-environment-declaration))
      ,@(when functions-needing-object
	  `((tx:function-needs-object ,@functions-needing-object)))
      ,@type-from-element-type-declarations)))

(defun add-function-declarations (function-info-alist)
  ;; if a function f needs an env and f has callers,
  ;;    then the variable for f is closed, and
  ;;         the callers of f need an environment.
  (labels ((note-closed-p (function+info)
	     (let ((function (car function+info))
		   (info (cdr function+info)))
	       (when (and (var-info-closed-p info)
			  (not (var-info-known-closed-p info)))
		 (let ((decl (fun-info-closed-function-declaration info)))
		   (when decl
		     (setf (var-info-known-closed-p info) t)
		     (push function (cdr decl)))))))
	   (note-needs-environment-p (function+info)
	     (let ((function (car function+info))
		   (info (cdr function+info)))
	       (when (and (var-info-needs-environment-p info)
			  (not (var-info-known-needs-environment-p info)))
		 (let ((decl (fun-info-needs-environment-declaration info)))
		   (when decl
		     (setf (var-info-known-needs-environment-p info) t)
		     (push function (cdr decl))))
		 (let ((callers (fun-info-callers-alist info)))
		   (when callers
		     (note-closed-p function+info)
		     (update-needs-environment-p callers))))))
	   (update-needs-environment-p (alist)
	     (mapc #'note-needs-environment-p alist)))
    (mapc #'note-closed-p function-info-alist)
    (update-needs-environment-p function-info-alist)))

;;; Do handling for a leaf toplevel form:
;;; - Do compile-time-too evaluation if required.
;;; - Invoke the codewalker on the form.  
;;; - Do the closure/constant analysis phase.
;;; - Emit code for any function definitions.
;;; - Save other things for later processing.

(defun translate-leaf-toplevel-form (form)
  (when *compile-time-too*
    (eval-in-env form *environment*))
  (unless *compile-time-only*
    (translate-leaf-toplevel-form1 form)))
         
         
  
  

(defun translate-leaf-toplevel-form1 (form)
   (let ((*toplevel-p* nil))
    (translate-leaf-toplevel-form-aux 
     (nreverse 
      (let ((*free-temporaries* nil))
	(translate-form (note-closed-variables form :ignore)
			*environment* *ignore-context*))))))

#+lucid
(defvar user::*collect-call-information-p* nil)

(defun translate-leaf-toplevel-form-aux (statements)
  #+lucid ; see translator.lisp
  (when user::*collect-call-information-p*
    (collect-call-information statements))
  (let ((pregather-info (pregather-info-list statements nil)))
    (when (do-constant-processing
	   (pregather-info-local-constants pregather-info)
	   (pregather-info-global-constants pregather-info))
      (error "Internal bug -- unresolved constants...."))
    (process-variable-links (pregather-info-variables pregather-info))
    (merge-initcode statements pregather-info)))

;;; The pregather phase does a traversal of the target language produced for
;;; each top-level form and returns a pregather-info struct.
;;; The contents of the fields of this struct for all top-level forms are
;;; merged together to make the initialization function for the file.

(defun add-list (new old old-last)
  (let ((new-last (if new (last new) old-last)))
    (when old-last
      (setf (cdr old-last) new))
    (values (or old new) new-last)))

(defun merge-initcode (statements pregather-info)
  (multiple-value-setq
      (*initcode-local-constants* *initcode-local-constants-last*)
    (add-list (pregather-info-local-constants pregather-info)
	      *initcode-local-constants* *initcode-local-constants-last*))
  (multiple-value-setq
      (*initcode-statements* *initcode-statements-last*)
    (add-list statements
	      *initcode-statements* *initcode-statements-last*))
  (multiple-value-setq
      (*initcode-functions* *initcode-functions-last*)
    (add-list (copy-list (pregather-info-local-functions pregather-info))
	      *initcode-functions* *initcode-functions-last*))
  (emit-variables (pregather-info-variables pregather-info))
  (do-backend-processing
    (pregather-info-global-functions pregather-info)
    (pregather-info-local-functions pregather-info)
    (pregather-info-closed-locals pregather-info))
  (emit-variables (pregather-info-variables pregather-info)))

(define-translator-parameter *gc-after-init-function-translation-p*
  nil)

(define-translator-parameter *maybe-gc-after-function-translation-p*
  nil)

#+(and lucid (not translating))
(defun maybe-gc-after-translation (init-function-p)
  (when *maybe-gc-after-function-translation-p*
    (if (and init-function-p
	     *gc-after-init-function-translation-p*)
	(lcl:gc)
	(let ((state (lcl:egc-state)))
	  (when (and state
		     (> (caar state) (* .50 (cdar state))))
	    (lcl:ephemeral-gc))))))

(defvar *do-backend-processing-function*
  #-lucid nil
  #+lucid #'maybe-gc-after-translation)

(defun do-backend-processing (all-functions toplevel-functions
					    initcode-closed-locals)
  (declare (special *processing-constants-p*))
  (when toplevel-functions
    (generate-initcode-closed-variable-names initcode-closed-locals))
  (dolist (f all-functions)
    (optimize-function f nil)
    (gather-function-definition f))
  ;; Only emit the toplevel functions: the emitter takes care
  ;; of recursively emitting nested functions.
  (dolist (f toplevel-functions)
    (emit-function f))
  (when (and *do-backend-processing-function*
	     (not *processing-constants-p*))
    (funcall *do-backend-processing-function* nil)))

;;; The stuff collected from running the gather phase on top-level forms
;;; is stored into these variables instead of into the function-record
;;; corresponding to the init function.  Have to move this all into the
;;; function record before emitting the init code.

(defvar *enter-function-callback* nil)
(defvar *enter-function-callback-data* nil)
(defvar *enter-function-callback-file-data* nil)
(defvar *enter-function-use-index-p* nil)
(defvar *enter-function-use-file-index-p* nil)
(defvar *enter-function-index* 0)
(defvar *enter-function-file-index* 0)
(defvar *enter-function-last-file-sequence-number* nil)
(defvar *enter-function-maximum-index-callback* nil)

(defun do-init-function-backend-processing ()
  (setf (function-record-statements *current-function*)
	*initcode-statements*)
  (setf (function-record-constants *current-function*)
	*initcode-local-constants*)
  (setf (function-record-nested-functions *current-function*)
	*initcode-functions*)
  (optimize-function *current-function* t)
  (when (gather-function-definition *current-function*)
    (error "Internal bug -- externals referenced by top-level form."))
  (emit-function-definition-aux *current-function* nil t)
  (when *do-backend-processing-function*
    (funcall *do-backend-processing-function* t))
  (when *enter-function-use-file-index-p*
    (when (< 0 *enter-function-index*)
      (push *enter-function-index*
	    *enter-function-callback-file-data*)
      (incf *enter-function-file-index*))))

;;; This helper function is used for the toplevel form walkers for things
;;; like PROGN.

(defun translate-toplevel-body (body env ctt)
  (let ((statements nil))
    (dolist (b body)
      (setq statements (nconc (translate-toplevel-form b env ctt) statements)))
    statements))


;;; Here's the entry point for processing of non-toplevel forms.  This
;;; function is called recursively to walk subforms.

(defun translate-form (form *environment* *context* &optional
			    (*result-type* '(values &rest t)))
   (re-translate-form form))


;;; This function might be called directly from within individual translate
;;;     functions, in cases where they construct an equivalent piece of code
;;;     and want to walk it in the same environment as the original form.
;;;     Doing so avoids the overhead of passing all of the flags and rebinding
;;;     the corresponding special variables.

(defun re-translate-form (form)
  (let ((temp nil)(macro-env nil)(fn nil))
    (cond ((symbolp form)
	   (translate-variable-reference form))
	  ((not (consp form))
	    (translate-constant form))
	  ((lambda-expression-p (setq fn (car form)))
	   (translate-lambda-application form))
	  ((not (symbolp fn))
	   (error "Invalid form syntax: ~s" form))
	  ((and (setq temp (defined-as-special-form fn))
		(not (and (defined-as-function fn *environment*)
			  (function-notinline-p fn *environment*))))
	   (funcall temp form))
	  ;; Don't just look for a compiler-macro for the car of form, 
	  ;; because of the hair with funcall, non-symbolic function names.
	  ((multiple-value-bind (newform macrop)
	       (translator-compiler-macroexpand-1 form *environment*)
	     (when macrop 
	       (return-from re-translate-form
		 (re-translate-form newform)))))
	  ((multiple-value-setq (temp macro-env)
	     (translator-macro-function fn *environment*))
	   (re-translate-form (call-macro-function temp form macro-env)))
	  (t
	   (translate-function-call form)))))


(defun get-result-type (form &optional (env *environment*))
  (multiple-value-bind (statements value result-type temps)
      (translate-form form env :result-type-only)
    (declare (ignore statements value temps))
    result-type))

(defun get-first-result-type (form &optional (env *environment*))
  (multiple-value-bind (statements value result-type temps)
      (translate-form form env :result-type-only t)
    (declare (ignore statements value temps))
    result-type))


;;; Define the translator functions for the random bits of syntax
;;;    that are called directly above.


;;; Translate a constant object; also the hook for QUOTE.
;;; There are three possibilities:
;;; * The object is a symbol that is predefined in the runtime library.
;;; * The object is an immediate constant such as a fixnum or character.
;;; * The object is a structured constant that has to be built up in
;;;   init code.

(defun translate-constant (value)
  (if (eq *context* ':result-type-only)
      (values nil nil `(member ,value))
      (multiple-value-bind (expression foreign-type)
	  (translate-constant-internal value)
	(handle-context nil expression
			`(member ,value)
			nil
			foreign-type))))

(defun translate-constant-internal (value)
  (cond ((initial-symbol-p value)
	 (mark-quoted-symbol value)
	 (values (make-target-form 'initial-symbol value)
		 (translator-foreign-type :object)))
	((initial-package-p value)
	 (values (make-target-form 'initial-package value)
		 (translator-foreign-type :object)))
	(t
	 (multiple-value-bind (foreign-type real-value)
	     (immediate-constant-p value)
	   (if foreign-type
	       (values (make-target-form 'c-constant foreign-type real-value)
		       foreign-type)
	       (values (make-target-form 'constant value nil)
		       (translator-foreign-type :object)))))))

;;; Forward references
(defun translate-constant-aux (value)
  (let ((*context* *value-context*))
    (multiple-value-bind (statements expression type temps)
	(translate-constant value)
      (declare (ignore statements type temps))
      expression)))


;;; Lambda applications.
;;;
;;; This should NOT call transform-lambda-to-let.  That is done by the funcall
;;; handler.  If done here and fails, that would just mean an extra wasted try.

(defun translate-lambda-application (form)
  (re-translate-form `(funcall (function ,(car form)) ,@(cdr form))))

;;; Here is the mechanism for defining translator functions for various
;;;     things which are handled as special forms.
;;; The syntax supports destructuring of the lambda-list.

(defmacro deftranslate (name structured-lambda-list &body body)
  (deftranslate-aux name structured-lambda-list body nil))

;;; Special forms that can pass toplevel-ness on to subforms need to
;;; be defined with this macro.  Generally, anything that looks at
;;; *toplevel-p* ought to be defined with define-toplevel-form instead
;;; of deftranslate.

(defmacro define-toplevel-form (name structured-lambda-list &body body)
  (deftranslate-aux name structured-lambda-list body t))


;;; Here's the helper function for both of the above.
;;; *** This is real similar to parse-macro and friends, maybe we can
;;; *** do something to allow them all to share.

(defun deftranslate-aux (name structured-lambda-list body top-level-p)
  (let ((function-name  (intern (sformat "TRANSLATE-~a-FORM" name))))
    (multiple-value-bind (real-body decls doc) (parse-body body t)
      (multiple-value-bind (bindings whole-var) 
	  (destructure structured-lambda-list)
	`(progn
	   (defun ,function-name (,whole-var)
	     ,@(unless bindings
		 `((declare (ignore ,whole-var))))
	     ,@(when doc
		 `(,doc))
	     (let* ,bindings
	       (declare ,@decls)
	       (block ,name
		 ,@real-body)))
	   (setf (defined-as-special-form ',name) #',function-name)
	   ,@(when top-level-p
	       `((setf (defined-as-toplevel-form ',name) #',function-name)))
	   ',name)))))

(defun add-translator-macro (name function)
  (setf (defined-as-macro name) (if (symbolp function)
				    (symbol-function function)
				    function)))

;;; Many things are most easily defined as macros, but we can't simply
;;; use DEFMACRO since that would redefine the macros in the Lisp the
;;; translator is running in.  TRANSLATOR-MACRO-FUNCTION will look first
;;; for TRANSLATOR-MACROs and then for ordinary Lisp-defined macros.

(defmacro define-translator-macro (name structured-lambda-list &body body)
  (let ((function-name  (intern (sformat "TRANSLATE-MACRO-~a" name)))
	(lambda-exp     (translator-parse-macro name structured-lambda-list
						body)))
    `(progn
       (defun ,function-name ,@(cdr lambda-exp))
       (add-translator-macro ',name ',function-name)
       ',name)))


;;; Several translator handlers and translator macros try to do a little
;;; pre-analysis on their source subforms in order to avoid binding
;;; unnecessary temporary variables.  Here's a couple helper functions.

;;; Expand compiler macros until no further expansion occurs.  Then try one
;;; normal macroexpansion.  If that fails then done.  Otherwise, start over on
;;; the expansion.  Note that this does not expand macros which are also
;;; defined as special-forms in the translator.

(defun apply-macros (form env &aux (really-macro nil) newform macrop)
  (values
    ;; expanded form
    (loop
     (cond ((symbolp form)
	    (multiple-value-setq (newform macrop)
	      (translator-macroexpand-1 form env))
	    (if macrop
		;; If symbol-macro, reprocess expansion.
		(setf form newform really-macro t)
		;; Otherwise, return form.
		(return form)))
	   ((or (atom form) (eq (car form) 'quote))
	    (return form))
	   ((progn
	      (multiple-value-setq (newform macrop)
		(translator-compiler-macroexpand-1 form env))
	      macrop)
	    ;; If compiler-macro expanded, reprocess expansion.
	    (setf form newform really-macro t))
	   (t
	    (let ((name (car form)))
	      (if (or (not (symbolp name))
		      (defined-as-special-form name env)
		      (progn
			(multiple-value-setq (newform macrop)
			  (translator-macroexpand-1 form env))
			(not macrop)))
		  ;; If car of form is not a symbol (presumably a
		  ;; lambda expression), is a translator special-form,
		  ;; or is not a translator macro, return the form.
		  (return form)
		  ;; Otherwise, reprocess expansion.
		  (setf form newform really-macro t))))))
    ;; flag indicating whether any expansion occured
    really-macro))

(defun really-atom (form env)
  (atom (apply-macros form env)))
  
;;; Expand the form (using apply-macros) and return true if it is a symbol
;;; or a constant.

(defun variable-or-constant-p (form env)
  (let ((transform (apply-macros form env)))
    (or (symbolp transform)
	(translator-constantp transform env))))


;;; A utility function for handling the processing context.  Walker functions
;;; must either handle the context directly or "pass the buck" to the
;;; walker functions for value-returning subforms.
;;; Munges its arguments and returns the munged values.
;;; Note that the caller of the walk function is responsible for doing
;;; any unboxing operations.  The code walker assumes that everything
;;; returns boxed values.
;;; The defined keywords are:
;;;     :value -- Normal single-value return result.
;;;     :predicate -- Only truth/falsity of result matters.
;;;     :ignore -- Discard the result value (the form is being executed
;;;         for side-effect only)
;;;     :return -- Function return context; multiple value return.
;;;     :save-values -- Save multiple values on the stack.
;;;     :more-values -- Save more values on the stack (for mv-funcall).
;;;     :values -- Other multiple-value return context.
;;;     anything else -- store the return value in the place indicated.
;;; Note that :value and :predicate are fundamentally different from
;;; the other cases because the value-producing expression is returned.  In
;;; all the other cases, the expression is executed for side-effect and
;;; is appended to the list of statements instead.  The caller of the
;;; code walk function should be careful about what values to expect
;;; back in these cases.
;;; *** We might want to explicitly check for valid l-value contexts 
;;; *** instead of just having a "t" case, so that we can detect bad
;;; *** contexts that get introduced....

;;; Define some predicates on contexts.

; includes: *value-context* *predicate-context* *ignore-context*
(defun value-context-p (context)
  (and (not (eq context *ignore-context*))
       (translator-foreign-type-p context)))

(defun side-effecting-context-p (context)
  (or (eq context *ignore-context*) 
      (not (value-context-p context))))

(defun lvalue-context-p (context)
  (and (target-form-p context)
       (member (target-form-type context)
	       '(local-variable special-variable accessor-call
		 constant-label))))

(defun multiple-value-context-p (context)
  (or (eq context :values) (eq context :return)))

(defun value-saving-context-p (context)
  (or (eq context :save-values) (eq context :more-values)))

(defmacro foreign-type-context-p (context)
  `(translator-foreign-type-p (get-translator-foreign-type ,context nil)))

(defun lvalue-context-foreign-type (context)
  (ecase (target-form-type context)
    (local-variable (variable-record-foreign-type (cadr context)))
    (special-variable *value-context*)
    (accessor-call  (foreign-function-descriptor-foreign-return-type
		     (find-descriptor (cadr context))))
    (constant-label *value-context*)))

(defun context-foreign-type (context)
  (cond ((or (eq context *ignore-context*)
	     (translator-foreign-type-p context))
	 context)
	((lvalue-context-p context)
	 (lvalue-context-foreign-type context))
	(t
	 (translator-foreign-type :object))))

(defun with-bound-temporary-variables (temporaries statements)
  (if temporaries
      (prog1 (list (apply-make-target-form 'with-lexical-bindings
					   temporaries
					   (nreverse statements)))
	 (mapc #'free-temporary temporaries))
      statements))


;;; Whenever :context is one that indicates that multiple values are
;;; significant (that is, :values, :save-values, :more-values, or :return),
;;; *reason-for-multiple-values-context* is bound to one of the following,
;;; indicating the reason we want multiple values:

;;; (:tail-call function-name) -- all results will eventually be returned
;;;         from specified function.
;;; (:explicit-multiple-values function-name) -- an enclosing
;;;         multiple-value-setq, multiple-value-bind, or the like,
;;;         contained in function-name.
;;; (:unwind-protect) -- if an unwind-protect is translated in
;;;         a single-value context, we still translate the protected forms
;;;         (wrapped in a (values <protected-form>) in a
;;;         multiple-values context, because multiple values contexts
;;;         are our only way of saving values on the value stack while
;;;         we evaluate the cleanup forms.
;;; (:throw <enclosing-function-name> &optional <tag-value>)
;;;         -- argument to throw, which returns all
;;;         values to the matching catch. argument is the enclosing
;;;         function name, and the tag expression. Tag-value is
;;;         omitted if it cannot be determined at compile-time.

(defvar *reason-for-multiple-values-context* nil)

;;; If non-nil, this is called for every function call evaluated
;;; in an mv context, with arguments the function name (or the symbol
;;; :catch, since we also report catches in mv-context) and the reason.
(defvar *report-mv-context-callback* nil)

;;; If current function is defined by defun or def-foreign-callable, this
;;; is just the function name. If it is a foreign-callable, or a nested
;;; function defined by labels or flet, it is a list, which should
;;; identify the function uniquely as long as we compare with #'equal.
;;; actually this is probably wrong; multiple labels in the same function
;;; with the same name will probably get confused, but this will result
;;; in conservative behavior, so it's OK for now.
;;; 
(defun current-function-name (&optional (env *environment*))
    (let ((names (tutil::translator-environment-function-names
		   env)))
      #+readability-is-more-important-than-accuracy
      (if (null (cdr names))
	  (car names)
	  names)
      #-readability-is-more-important-than-accuracy
      (car names)))
    
(defun report-tail-call (result-expression)
  (when *report-mv-context-callback*
    (unless (and (consp result-expression) (eq (car result-expression) :catch))
      (setq result-expression
	    (loop
	      (unless (eq (target-form-type result-expression)
			  'comma-operator)
		(return result-expression))
	      (setq result-expression (car (last result-expression))))))
      (when (or (eq (car result-expression) :catch)
		(and (memq (target-form-type result-expression)
			   '(call call-generic variadic-call variadic-call-generic foreign-call macro-call))
		     (setq result-expression
			   (environment-entry-name
			     (environment-entry (cadr result-expression))))))
	(funcall *report-mv-context-callback*
		 result-expression
		 *reason-for-multiple-values-context*))))


(defun handle-context (statements result-exp result-type &optional
				  result-temps result-foreign-type)
  (setq result-type (and-value-types result-type *result-type* *environment*))
  (when (eq *context* ':result-type-only)
    (return-from handle-context
      (values nil nil (single-value-type result-type *environment*) nil)))
  (when (memq *context* '(:return :save-values :values :more-values))
    (report-tail-call result-exp))
  (when (and (lvalue-context-p *context*)
	     (not (target-form-equal *context* result-exp))
	     (consp statements)
	     (eq (target-form-type (car statements)) 'setq)
	     (target-form-equal (cadr (car statements)) result-exp)
	     (not (side-effecting-context-p *context*)))
    ;; try to cascade onto previous SETQ unless the context has
    ;; side-effects (since order of evaluation in the C assignment
    ;; operator is unspecified)
    (setq result-exp (pop statements)))
  (when (and (lvalue-context-p *context*)
	     (eq (target-form-type *context*) 'local-variable)
	     (variable-record-type-from-init-p (cadr *context*)))
    (let* ((record (cadr *context*))
	   (old-type (variable-record-lisp-type record)))
      (setq result-type (and-value-types result-type old-type *environment*))
      (setf (variable-record-lisp-type record) result-type)
      (unless (or (not (eq (variable-record-foreign-type record)
			   (translator-foreign-type :object)))
		  (null result-foreign-type)
		  (variable-record-closed-p record)
		  (variable-record-special-p record))
	(setf (variable-record-foreign-type record)
	      result-foreign-type))))
  
  (multiple-value-setq (statements result-exp result-temps)
    (foreign-type-coerce statements result-exp result-foreign-type nil
			 result-type result-temps))
  (case *context*
    (:return
      (values (with-bound-temporary-variables result-temps
		(cons (if (needs-explicit-values result-exp)
			  (make-target-form 'return-value result-exp)
			  (make-target-form 'return-values result-exp))
		      statements))
	      nil
	      result-type nil))
    (:values
     ;; (STORE-VALUES <expr>) is currently emitted as "result = <expr>";
     ;; this is because the code walker cannot assign temporary variables
     ;; to expressions which are supposed to retain multiple values.
     ;; We should really fix the code walker to enable applications
     ;; to use local temps for this purpose!
     (note-local-temps (list 'trun:%store-value-temp-declaration))
     (values (with-bound-temporary-variables result-temps
	       (cons (if (needs-explicit-values result-exp)
			 (make-target-form 'store-value result-exp)
			 (make-target-form 'store-values result-exp))
		     statements))
	     (first-multiple-value)
	     result-type nil))
    (:save-values
     (values (with-bound-temporary-variables result-temps
	       (cons (make-target-form
		      'save-values 
		      (if (needs-explicit-values result-exp)
			  (make-target-form 'values result-exp)
			  result-exp))
		     statements))
	     (make-target-form 'restore-values)
	     result-type nil))
    (:more-values
     (values (with-bound-temporary-variables result-temps
	       (cons (make-target-form
		      'save-more-values
		      (if (needs-explicit-values result-exp)
			  (make-target-form 'values result-exp)
			  result-exp))
		     statements))
	     (make-target-form 'restore-values)
	     result-type nil))
    (t
     (if (and result-exp
	      (or (lvalue-context-p *context*)
		  (let ((name
			 (case (target-form-type result-exp)
			   (box-value
			    (boxer (cadr result-exp)))
			   (unbox-value
			    (unboxer (cadr result-exp)))
			   ((macro-call accessor-call)
			    (cadr result-exp)))))
		    (and name
			 (not (eq name :nonstandard))
			 (macro-uses-temp-p name)))))
	 (handle-lvalue-context statements result-exp result-type result-temps
				*context*)
	 (values statements
		 result-exp
		 (single-value-type result-type *environment*)
		 result-temps)))))

(defun macro-uses-temp-p (name)
  (when (environment-entry-p name)
    (setq name (environment-entry-name name)))
  (eq name 'trun:unbox%d))

;;; This is similar to handle-context, but is used when value returning
;;; subforms were forced to be evaluated in a :values context rather than the
;;; actual context because of the need for cleanup code and such.  Calling
;;; this presumes that the values are in the values buffer.

(defun handle-context-multiple-values (statements value type temps)
  (case *context*
    (:result-type-only (values nil nil type nil))
    (:return (values (with-bound-temporary-variables temps
		       (cons (make-target-form 'return-stored-values)
			     statements))
		     nil type nil))
    (:values (values (with-bound-temporary-variables temps
		       statements)
		     value type nil))
    (:save-values
     (values (with-bound-temporary-variables temps
	       (cons (make-target-form 'save-values value)
		     statements))
	     (make-target-form 'restore-values) type nil))
    (:more-values
     (values (with-bound-temporary-variables temps
	       (cons (make-target-form 'save-more-values value) statements))
	     (make-target-form 'restore-values)
	     type nil))
    (t (handle-context statements value type temps
		       (translator-foreign-type :object)))))

;;; Some things (THROW, RETURN-FROM, GO) don't return a value, but we
;;; have to construct three reasonable values anyway because some
;;; branching constructs depend on this behavior.

(defun handle-nonreturning-context (statements temps)
  (values
   (with-bound-temporary-variables temps
     statements)
   (case *context*
     (:return
      nil)
     (:values
      (first-multiple-value))
     ((:save-values :more-values)
      (make-target-form 'restore-values))
     (t
      (cond ((eq *context* *ignore-context*)
	     nil)
	    ((or (value-context-p *context*)
		 (eq *context* ':result-type-only))
	     (translate-constant-aux 'nil))
	    (t
	     *context*))))
   'null
   nil)) 

(defun handle-lvalue-context (statements result-exp result-type result-temps
					 context-or-foreign-type)
  (declare (special *fix-closed-variable-setqs*))
  (let* ((record (and (consp context-or-foreign-type)
		      (eq (target-form-type context-or-foreign-type)
			  'local-variable)
		      (cadr context-or-foreign-type)))
	 (bound-temps (delq record result-temps)))
    (mapc #'free-temporary bound-temps)
    (setq result-temps nil)
    (let ((context (if (consp context-or-foreign-type)
		       (copy-target-form context-or-foreign-type)
		       (make-target-form
			'local-variable
			(prog1 (setq record (allocate-temporary
					     context-or-foreign-type))
			  (setf (variable-record-unwritten-p record) t)
			  (push record result-temps))))))
      (unless (target-form-equal context result-exp)
	(unless (and record (variable-record-unwritten-p record))
	  (reset-read-once-setqs *environment*))
	(push (if (and (not *fix-closed-variable-setqs*)
		       record
		       (variable-record-closed-p record)
		       (not (nonrelocating-expression-p result-exp)))
		  (let ((temp (allocate-temporary)))
		    (prog1 (make-target-form
			    'compound-statement
			    (make-target-form
			     'setq
			     (make-target-form 'local-variable temp)
			     result-exp)
			    (make-target-form
			     'setq
			     (copy-target-form context)
			     (make-target-form 'local-variable temp)))
		      (free-temporary temp)
		      (push temp bound-temps)))
		  (let ((stmt (make-target-form 'setq
						(copy-target-form context)
						result-exp)))
		    (when (and *do-read-once-optimization*
			       record
			       (variable-record-read-once-p record)
			       (not (variable-record-closed-p record)))
		      (setf (variable-record-setq-statement record)
			    (if (variable-record-setq-statement record)
				(setf (variable-record-read-once-p record) nil)
				stmt)))
		    stmt))
	      statements))
      (values (if bound-temps
		  (list (apply-make-target-form 'with-lexical-bindings
						bound-temps
						(nreverse statements)))
		  statements)
	      context
	      (single-value-type result-type *environment*)
	      result-temps))))

(defmacro with-temporary-for-value (new-context &body forms)
  (let* ((temp (make-symbol "TEMP"))
	 (extras (if (consp new-context) (cdr new-context) nil))
	 (new-context (if (consp new-context) (car new-context) new-context)))
    `(let* ((,temp (allocate-temporary (context-foreign-type *context*)))
	    (,new-context (make-target-form 'local-variable ,temp)))
       (multiple-value-bind (statements value type temps ,@extras)
	   (progn ,@forms)
	 (values statements value type (cons ,temp temps) ,@extras)))))


;;; In a few places, we want to indicate that the first multiple value is
;;; returned.

(defun first-multiple-value ()
  (make-target-form 'first-multiple-value))


;;; Lots of constructs involve implicit PROGN situations.  Here is a 
;;; function to handle them all.

(defun translate-progn-body (forms environment context statements
				   &optional (return-type '(values &rest t)))
  (if (eq *context* ':result-type-only)
      (translate-form (car (last forms)) environment context return-type)
      (loop (unless (cdr forms)
	      (multiple-value-bind (new-statements result-exp type temps)
		  (translate-form (car forms) environment context return-type)
		(setq statements (nconc new-statements statements))
		(return (values statements result-exp type temps))))
	    (setq statements
		  (nconc (translate-form (pop forms) environment
					 *ignore-context*)
			 statements)))))

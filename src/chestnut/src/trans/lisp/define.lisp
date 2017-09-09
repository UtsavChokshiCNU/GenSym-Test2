;;; -*- Mode: Lisp; Package: TIMPL; Syntax: Common-Lisp -*-
;;;
;;; define.lsp -- defining macros (defun, defmacro, defvar, etc.)
;;;
;;; Author :  Sandra Loosemore
;;; Date   :  11 Jun 1990
;;;
;;;
;;; Copyright (c) 1990, Chestnut Software Inc.
;;;
;;; This file defines handling for all macros that are treated
;;; magically by the translator when they appear at toplevel.
;;;

(in-package "TIMPL")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/define.lisp,v $"
 "$Revision: 1.10 $"
 "$Date: 2007/07/12 18:29:34 $")

;;; There are two possible approaches here.  The first is to use
;;; define-translator-macro to define an expansion that includes an
;;; eval-when, that is called for both toplevel and non-toplevel
;;; calls to the macro.
;;; The second approach is to define a toplevel form handler that
;;; explicitly checks to see whether the call appears at toplevel.

;;; Most of these defining macros make definitions that are only of
;;; interest at compile time -- macro definitions, special variable
;;; proclamations, and the like.  While these definitions have to be
;;; around in order to *translate* the code, they don't need to be
;;; around at runtime unless the program calls EVAL or hooks used by
;;; EVAL such as SYMBOL-FUNCTION or MACROEXPAND.  Since we don't (yet)
;;; support an interpreter anyway, generally these things don't make
;;; any attempt to produce run-time definitions.  All of this stuff
;;; will have to be tweaked later if and when we want to support an
;;; interpreter.


;;; Compiler macros

;;; DEFINE-TRANSLATOR-COMPILER-MACRO is used to predefine any compiler macros
;;; we want to have around.

(defmacro define-translator-compiler-macro (name lambda-list &body body)
  (let ((lambda (translator-parse-compiler-macro name lambda-list body)))
    `(progn
       (tutil::set-defined-as-compiler-macro #',lambda ',name)
       ',name)))


;;; This is the translator macro for handling calls to define-compiler-macro.
;;; This is not complete because it only makes the compiler-macro definition
;;; available at translation-time and not at runtime.  Probably there ought
;;; to be some user-specifiable translator option to control this, possibly
;;; common with a switch for defmacro.

(define-translator-macro define-compiler-macro
        (name lambda-list &body body)
  `(progn
     (eval-when (:compile-toplevel)
       (print-progress-message "Compiler macro" ',name)
       (define-translator-compiler-macro ,name ,lambda-list ,@body)
       ;; (c-name-of-quoted-symbol ',name)
       )
     ;; For now, not available at runtime.
     ;; (setf (tcl:compiler-macro-function ',name) #',lambda)
     ',name))

#+lucid
(define-translator-macro lcl:def-compiler-macro (name lambda-list &body body)
  `(define-compiler-macro ,name ,lambda-list ,@body))

;;; declaim
;;; This definition is correct according to ANSI CL but may break in
;;; the translator, since it depends on having PROCLAIM defined at
;;; run-time.

(define-translator-macro declaim (&rest decl-specs &environment env)
  `(progn
     (eval-when (compile)
       ,@(mapcar #'(lambda (d) `(translator-proclaim ',d)) decl-specs))
     ,@(mapcan #'proclaim-variable-definitions decl-specs)
     ,@(when (defined-as-function 'tcl:proclaim env)
	 `((eval-when (load eval)
	     (let ()
	       ,@(mapcar #'(lambda (d) `(tcl:proclaim ',d)) decl-specs)))))))

(defun proclaim-variable-definitions (decl-spec)
  ;(when t (print "_proclaim_variable_def")(print decl-spec))
  (when (eq (car decl-spec) 'special)
    (mapcar #'(lambda (symbol) `(defvar-setup ,symbol))
	    (cdr decl-spec))))

;;; proclaim
;;; Attempt to apply non-ANSI semantics to top-level calls with
;;; constant arguments
;;; Note:  The "LOCALLY / NOTINLINE" declaration is present
;;;   so that the expansion doesn't infinite-loop.  However,
;;;   because of the way we do NOTINLINE, this will generate
;;;   FUNCALL_0(Qproclaim, ...) rather than proclaim(...).  - kab
;;;   Since PROCLAIM isn't supported now as a function, this is moot now.
;;;   Possible fixes:  Distinguish between "notinline" and "dynamic"
;;;     functions; ignore "notinline" for RTL functions, since it's
;;;     illegal to modify their function cell.  - wb

(define-translator-compiler-macro tcl:proclaim
    (&whole form proclamation &environment env)
  (setf proclamation (apply-macros proclamation env))
  (multiple-value-bind (value valuep constantp)
      (translator-constant-value proclamation env)
    (declare (ignore constantp))
    (cond ((not valuep)
	   form)
	  (*ansi-semantics*
	   (when *toplevel-p*
	     (warn "Top Level Call to PROCLAIM:  ~S~
	          ~%To ensure that this declaration is correctly recognized~
	          ~%by the Translator, use ~S."
		   form
		   `(declaim ,value)))
	   form)
	  (t
	   `(progn
	      (eval-when (:compile-toplevel)
		(translator-proclaim ',value))
	      ,@(proclaim-variable-definitions value)
	      ,@(when (defined-as-function 'tcl:proclaim env)
		  `((eval-when (:load-toplevel :execute)
		      (locally
			  (declare (notinline tcl:proclaim))
			,form)))))))))

;;; in-package
;;; This definition is correct.
;;; It attempts to recover, with a warning message, from non-ANSI calls.

(define-translator-macro in-package (&whole whole name &rest keys
					    &environment env)
  (when (or keys (not (or (symbolp name) (stringp name))))
    (if (or *ansi-semantics*
	    (multiple-value-bind (value valuep)
		(translator-constant-value
		 (setq name (apply-macros name env))
		 env)
	      (not (and valuep
			(or (symbolp (setq name value))
			    (stringp name))))))
	(error "Incompatible call to the macro IN-PACKAGE:~
              ~%~s~
              ~%The new ANSI definition allows exactly one argument,~
              ~%a string or (unquoted) symbol." whole)
      #|
      (warn "Incompatible call to the macro IN-PACKAGE:~
           ~%~s~
           ~%The new ANSI definition allows exactly one argument,~
           ~%a string or (unquoted) symbol.~
           ~%Processing as (IN-PACKAGE ~S)." whole (string name))
      |#
      ))
  (setf name (string name))
  `(progn
     (eval-when (compile)
       (in-package-compile-time ,name))
     (eval-when (load eval)
       (trun:set-package ,name))))

(defun in-package-compile-time (name)
  (let ((package (find-package name)))
    (unless package
      (error "The package ~A, specified in a call to IN-PACKAGE,~
		 ~%does not currently exist.  You should create this package~
		 ~%by placing a DEFPACKAGE form in your source code ~
                   before this call." name))
    (let ((remote-package-name (find-remote-package-name package)))
      (when remote-package-name
	(warn "Encountered the form:  (IN-PACKAGE ~S)~
                  ~%To translate this code in package ~A, replace this by:~
                  ~%(IN-PACKAGE ~S)"
	      name remote-package-name remote-package-name)))
    (setf *package* package)))


;;; defconstant, defparameter, defvar
;;; These definitions are incomplete in that they do not make the
;;; proclamations about the variables at run-time (only at compile-time).

;;; For defconstant, attempt to evaluate the initform at compile time and stash
;;; its value.  There are various optimizations that might want to look at it
;;; (although we are generally careful to preserve references to symbolic
;;; constants); see translator-constant-value.
;;;
;;; If the constant value is something that is an immediate or pre-initialized
;;; object, we'll make a #define to that object; otherwise we'll declare a C
;;; variable and handle references in the same way that references to specials
;;; are treated.  Seel simple-constant-p and dumping of :simple-constant vs
;;; :complex-constant.

(defun proclaim-special-form (name)
  (cond ((defined-as-function 'tx:proclaim-special)
	 `((eval-when (load eval)
	     (tx:proclaim-special ',name))))
	((defined-as-function 'tcl:proclaim)
	 `((eval-when (load eval)
	     (let () (proclaim '(special ,name))))))
	(t
	 nil)))

(define-translator-macro defconstant
    (name initial-value &optional doc &environment env)
  `(progn
     (eval-when (:compile-toplevel)
       (print-progress-message "Constant" ',name)
       (defconstant-compile-time ',name ',initial-value ',doc
				 (coerce-to-environment
				  ',(translator-environment-name env))))
     (eval-when (:load-toplevel :execute)
       (defconstant-setup ,name)
       (defconstant-initialize ,name ,initial-value)
       ,@(when (record-documentation-p doc)
	   `((setf (documentation ',name 'variable) ',doc)))
       ,@(proclaim-special-form name)
       ',name)))

(defun defconstant-compile-time (name initial-value doc env)
  (multiple-value-bind (value therep)
      (evaluate-defconstant-initializer initial-value env)
    (update-variable-descriptor name env
				:constant-p (if (and therep (simple-constant-p value))
						:simple-constant
						:complex-constant)
				:value-p therep
				:value value
				:documentation doc)
    (when therep
      (translator-proclaim `(type ,(translator-type-of value) ,name)
			   env))
    (assign-C-names-for-global-variable name)))

;;; Because eval-in-env (used by eval-when-compile) cannot be depended upon to
;;; properly deal with the remote environment, we only evaluate the initform if
;;; it is sufficiently simple (recognizable as a constant by the translator).
;;; Perhaps we should have a host-dependent conditionalization that can be used
;;; to determine whether eval-in-env is reliable.
;;;
;;; If this problem didn't exist, we could simply have the eval-when-compile
;;; portion of the expansion include a (LET ((var <<initial-value>>)) ...) form
;;; in order to compute the compile-time value.

(defun evaluate-defconstant-initializer (initform env)
  (setf env (coerce-to-environment env))
  (translator-constant-value (apply-macros initform env) env))

;;; This is split out into a separate macro because the specific 
;;; DEFCONSTANT expansion has to be computed *after* the EVAL-WHEN COMPILE
;;; actions have been executed.

(define-translator-macro defconstant-setup (name &environment env)
  (when (and *special-symbols*
	     (forward-defined-as-symbol name))
    (mark-quoted-symbol name))
  (let ((info  (defined-as-variable name env)))
    (if (and info
	     (not (eq (variable-descriptor-constant-p info) :simple-constant)))
	`(trun:establish-special-variable ',name)
	'(progn nil))))

(define-translator-macro defconstant-initialize (name initial-value)
  `(trun:%set-symbol-value ',name ,initial-value))


;;; For defparameter and defvar, generate a corresponding C variable.
;;; Have to do some magic to install a pointer to that variable in the
;;; value cell of the symbol.

(defun define-variable-compile-time (name doc &optional env)
  (proclaim `(special ,name))
  (update-variable-descriptor name env
			      :constant-p nil
			      :documentation doc)

  ;;; set special-p flag from default (T) to NIL, for emit-variables-aux-h (dump.lisp)
  #+translator-supports-thread
  (when (cdr (assoc 'tx:global-variable
		    (variable-proclamations name env)))
    (setf (variable-descriptor-special-p (defined-as-variable name env))
	  nil))

  (assign-C-names-for-global-variable name))

(define-translator-macro defparameter (name initial-value &optional doc)
  `(progn
     (eval-when (compile)
       (print-progress-message "Parameter" ',name)
       (define-variable-compile-time ',name ',doc))
     (eval-when (load eval)
       (defvar-setup ,name)
       (setq ,name ,initial-value)
       ,@(if (record-documentation-p doc)
	     `((setf (documentation ',name 'variable) ',doc)))
       ,@(proclaim-special-form name)
       ',name)))

(define-translator-macro defvar (name &optional (initial-value nil init-p) doc)
  `(progn
     (eval-when (compile)
       (print-progress-message "Variable" ',name)
       (define-variable-compile-time ',name ',doc))
     (eval-when (load eval)
       (defvar-setup ,name)
       ,@(if init-p
	     `((if (trun:unbound-special-p ',name)
		   (setq ,name ,initial-value))))
       ,@(if (record-documentation-p doc)
	     `((setf (documentation ',name 'variable) ',doc)))
       ,@(proclaim-special-form name)
       ',name)))

;;; unbound-special-p is a special form. Its argument must be a
;;; quoted symbol. It is used so that the Translator can emit
;;; (Foo == UNBOUND) instead of boundp(Qfoo), so that the defvar does
;;; not require the presence of the symbol at runtime if *special-symbols* is
;;; true. Since this produces an unboxed C boolean, we box it here.
;;; The deftranslate for if will unbox it in the occurence in defvar.

;;; At least try to make it have functional syntax so that user
;;; codewalkers have a chance of handling it properly.  Complain if
;;; something confusing happened.


(deftranslate trun:unbound-special-p (var)
  (if (and (consp var)
	   (eq (car var) 'quote)
	   (symbolp (cadr var)))
      (setq var (cadr var))
      (error "The argument to UNBOUND-SPECIAL-P, ~s, is not a~
              quoted symbol." var))
  (handle-context
   nil
   (make-target-form 'unbound-special-p
		      (make-target-form 'special-variable var))
   '(member t nil)
   nil
   (translator-foreign-type :object)))
  
;;; Establish the connection to a C variable for a special only if the
;;; DEFVAR/DEFPARAMETER appeared at top-level.

(define-translator-macro defvar-setup (name &environment env)
  (when (and *special-symbols*
	     (forward-defined-as-symbol name))
    (mark-quoted-symbol name))
  (let ((info (defined-as-variable name env)))
    (if (and info
	     (variable-descriptor-global-p info))
	`(trun:establish-special-variable ',name)
	nil)))


;;; This has to be a special form, sigh.
;;; At least try to make it have functional syntax so that user
;;; codewalkers have a chance of handling it properly.  Complain if
;;; something confusing happened.


(deftranslate trun:establish-special-variable (symbol)
  (if (and (consp symbol)
	   (eq (car symbol) 'quote)
	   (symbolp (cadr symbol)))
      (setq symbol (cadr symbol))
      (error "The argument to ESTABLISH-SPECIAL-VARIABLE, ~s, is not a~
              quoted symbol." symbol))
  (unless (defined-as-variable symbol)
    (error
     "Internal error:  No descriptor for special variable ~S"
     symbol))
  (handle-context
   (list (make-target-form 'variable-definition symbol))
   (translate-constant-aux nil)
   'null
   nil
   (translator-foreign-type :object)))

;;; Generate init code to link variables to symbols
;;; It's assumed that the linking code and the actual variable definition
;;; are always dumped at the same point (i.e., at the site of the first
;;; reference to the variable); that's why only one redefinition record
;;; is stored in the variable descriptor.
;;; This is called by translate-leaf-toplevel-form-aux, on the list of
;;; variables collected by the pregatherer.

(defun process-variable-links (variables)
  (let ((statements nil))
    (dolist (variable variables)
      (multiple-value-bind (symbol-record therep)
	  (defined-as-quoted-symbol variable)
	;; Get rid of the redefinition-record stuff for now
	;;(when (and (redefinition-record-definition-needs-dumping
	;;             redefinition-record)
	;;            (variable-descriptor-linked-locally-p descriptor)))
	(unless therep
	  (setf symbol-record
		(setf (defined-as-quoted-symbol variable)
		      (make-symbol-record :name variable))))
	(when (and (not (symbol-record-variable-exists symbol-record))
		   (or *special-symbols*
		       (symbol-record-exists-at-runtime symbol-record)))
	  (push (make-target-form
		 'set-symbol-value-location variable)
		statements)
	  (defined-as-variable variable)
	  (setf (symbol-record-exists-at-runtime symbol-record) t))
	(setf (symbol-record-variable-exists symbol-record) t)))
    (when statements
      (translate-leaf-toplevel-form-aux (nreverse statements)))))

;;; This special form is used to generate set-symbol-value-location
;;; from withing the constant dumper when *special-symbols* is
;;; false and the first occurence of the symbol occurs after the
;;; first occurence of the special variable.

(deftranslate trun::link-variable (name)
  (defined-as-variable name)
  (values (list (make-target-form 'set-symbol-value-location name))
	  (translate-constant-aux nil)
	  'null
	  nil))


;;;*** at some point support for a foreign-type slot ought to be added.

;;; defmacro
;;; This is complete.

(define-translator-parameter *define-macros-in-host-environment-p* t)

(define-translator-macro defmacro (name lambda-list &body body
					            &environment env)
  `(progn
     (eval-when (compile)
       (print-progress-message "Macro" ',name)
       (redefine-macro ',name)
       (define-translator-macro ,name ,lambda-list ,@body)
       ,@(when *define-macros-in-host-environment-p*
	   `((defmacro ,name ,lambda-list ,@body)))
       ;; (c-name-of-quoted-symbol ',name)
       )
     (eval-when (load eval)
       ,(multiple-value-bind (type localp decl-info)
	    (translator-function-information name env)
	  (declare (ignore type localp))
	  (when (or (rest (assoc 'tx:include-at-runtime decl-info))
		    (and (not (rest (assoc 'tx:omit-at-runtime decl-info)))
			 *include-macro-expanders*))
	    (let* ((expander (translator-parse-macro-for-expander
			      name lambda-list body))
		   (expander-name
		    (make-symbol (sformat "MACRO-~A-EXPANDER" name)))
		   (expander-lambda-list (second expander))
		   (expander-body (cddr expander)))
	      `(flet ((,expander-name ,expander-lambda-list
			,@expander-body))
		 (setf (tcl:macro-function ',name)
		       (function ,expander-name))))))
       ',name)))

(defvar *translating-translator-p* nil)

(defun redefine-macro (name)
  (when (and (defined-as-function name)
	     (not *translating-translator-p*))
    (warn "Redefining function ~s as a macro." name)
    (setf (defined-as-function name) nil)))

;;; defun
;;; This is complete.  Basically, top-level DEFUNs are treated specially
;;; so that we can do more inlining on calls.

(define-toplevel-form defun (&whole form name lambda-list &body body)
  (multiple-value-bind (principal setfp) (get-fn-principal-name name)
    (if *toplevel-p*
	(let ((message `(defun ,name)))
	  (with-translator-message message
	    (print-progress-message "Function" name)
	    (when *compile-time-too*
	      (eval-in-env form *environment*))
	    (multiple-value-bind (real-body decls doc)
		(parse-body body t)
	      (declare (ignore real-body decls))
	      (redefine-function name lambda-list :documentation doc)
	      (when *prepare-stream*
		(write-prepare-form
		  `(redefine-function ',name ',lambda-list)))
	      (unless *compile-time-only*
		(translate-defun name principal setfp lambda-list body
				 message)))))
	(translate-non-toplevel-defun
	 name principal setfp lambda-list body))))

(defun get-fn-principal-name (name)
  (cond ((symbolp name) (values name nil))
	((setf-function-name-p name)
	 (values (principal-name-of-function-name name) t))
	(t
	 (error "~S is not a valid name for DEFUN." name))))

(defun redefine-function (name lambda-list
			       &key (generic-function-p nil)
			            (documentation nil))
  (macro->fn name)
  ;; Generate C names for the function.
  (generate-c-names-for-fn name)
  ;; Compare old descriptor (if it exists) with new one, to determine whether
  ;; there have been changes that might invalidate already translated code.
  (let* ((old (defined-as-function name))
	 (defined-in-rtl-p (and old
				(function-descriptor-defined-in-rtl-p old)))
	 (new (make-function-descriptor
	       :lambda-list lambda-list
	       :generic-function-p generic-function-p
	       :documentation documentation
	       :defined-in-rtl-p defined-in-rtl-p)))
    (update-function-descriptor-properties new name)
    (when old
      (when (and (boundp '*initial-global-environment*)
		 (defined-as-function name *initial-global-environment*))
	(warn "Redefining RTL function ~S" name))
      (unless (argument-descriptors-equal-p old new)
	(warn "Redefining function ~s with incompatible argument list." name))
      (let ((old-gfp (function-descriptor-generic-function-p old))
	    (new-gfp (function-descriptor-generic-function-p new)))
	(cond ((null old-gfp)
	       (when new-gfp
		 (warn "Redefining function ~S as a generic function." name)))
	      ((null new-gfp)
	       (warn "Redefining generic function ~S as a normal function."
		     name)))))
    (setf (defined-as-function name) new)))

(defun update-function-descriptor-properties (fd name)
  (when (function-information-value name 'tx:nonrelocating)
    (setf (function-descriptor-nonrelocating fd) t))
  (when (function-information-value name 'tx:non-state-changing)
    (setf (function-descriptor-state-changing fd) nil))
  (when (function-information-value name 'tx:non-state-using)
    (setf (function-descriptor-state-using fd) nil))
  (when (eql 1 (function-information-value name 'values-count))
    (setf (function-descriptor-sets-values-count-p fd) nil))
  (when (function-information-value name 'dllexport)
    (setf (function-descriptor-dllexport-p fd) t)))

(defun macro->fn (name)
  (when (or (defined-as-macro name) (and (symbolp name) (macro-function name)))
    (warn "Redefining macro ~s as a function." name)
    (setf (defined-as-macro name) nil)))

(defun generate-c-names-for-fn (name &optional (c-name nil c-name-p))
  (c-name-of-function-object name)
  (if c-name-p
      (setf (c-name-of-function-entry name) c-name)
      (c-name-of-function-entry name))
  (c-name-of-quoted-symbol (principal-name-of-function-name name)))

(defun translate-defun (name principal setfp lambda-list body
			     &optional message)
  (destructuring-bind (ignore name lambda-list &body body)
      (note-closed-variables `(defun ,name ,lambda-list ,@body)
			     *value-context*)
    (declare (ignore ignore))
    (let ((*toplevel-p*  nil)
	  (*free-temporaries* nil))
      (let ((record  (translate-function-definition-aux
		      name lambda-list body :global *environment* message))
	    (descriptor (defined-as-function name)))
	(if (null descriptor)
	    (error "Internal error:  No descriptor for function ~S" name)
	    (update-function-descriptor-for-definition name descriptor))
	(translate-leaf-toplevel-form-aux
	 (list (make-target-form 'function-definition record)))
	(make-function-links name principal setfp record)))))

(defun make-function-links (name principal setfp record)
  (record-need-for-linking principal record setfp)
  (let ((decl-info (translator-set-declaration-information name nil))
	(*compile-time-too* nil))
    (when (or (symbol-exists-at-runtime principal)
	      (or (rest (assoc 'tx::include-symbol-at-runtime decl-info))
		  (and (not (rest (assoc 'tx::omit-symbol-at-runtime
					 decl-info)))
		       *function-symbols*)))		
      (translate-leaf-toplevel-form
       (if setfp
	   `(trun:link-setf-function ,name ,principal)
	   `(trun:link-function ,name))))))

(defun symbol-exists-at-runtime (symbol)
  (multiple-value-bind (record therep)
      (defined-as-quoted-symbol symbol)
    (and therep (symbol-record-exists-at-runtime record))))

(deftranslate trun:link-function (symbol)
  (let* ((translated-principal (translate-constant-aux symbol))
	 (record (symbol-record-function-to-link
		  (defined-as-quoted-symbol symbol)))
	 (function-object-expression
	  (make-target-form 'function-object record)))
    (setf (symbol-record-function-requires-linking
	   (defined-as-quoted-symbol symbol))
	  nil)
    (defined-as-function symbol) ; Needed for emit-user-functions-h.
    (values
     `(,@(when (record-documentation-p
		(function-record-documentation record))
	   (list (make-target-form
		  'call-generic
		  '(setf tcl:documentation)
		  (translate-constant-aux
		   (function-record-documentation record))
		  (translate-constant-aux symbol)
		  (translate-constant-aux 'function))))
	 ,(make-target-form
	   'macro-call
	   'trun:%set-symbol-function
	   translated-principal
	   function-object-expression))
     (translate-constant-aux nil)
     'null
     nil)))

(deftranslate trun:link-setf-function (name principal)
  (let* ((translated-principal (translate-constant-aux principal))
	 (record (symbol-record-setf-function-to-link
		  (defined-as-quoted-symbol principal)))
	 (function-object-expression
	  (make-target-form 'function-object record)))
    (setf (symbol-record-setf-function-requires-linking
	   (defined-as-quoted-symbol principal))
	  nil)
    (defined-as-function name) ; Needed for emit-user-functions-h.
    (values
     `(,@(when (record-documentation-p
		(function-record-documentation record))
	   (list (make-target-form
		  'call-generic
		  '(setf tcl:documentation)
		  (translate-constant-aux
		   (function-record-documentation record))
		  (translate-constant-aux name)
		  (translate-constant-aux 'function))))
	 ,(make-target-form
	   'call
	   'trun:set-setf-function
	   translated-principal
	   function-object-expression))
     (translate-constant-aux nil)
     'null
     nil)))

(defun record-need-for-linking (name function-record setfp)
  (multiple-value-bind (symbol-record therep)
      (defined-as-quoted-symbol name)
    (unless therep
      (setf symbol-record (make-symbol-record :name name))
      (setf (defined-as-quoted-symbol name) symbol-record))      
    (cond (setfp
	   (setf (symbol-record-setf-function-to-link symbol-record)
		 function-record)
	   (setf (symbol-record-setf-function-requires-linking symbol-record)
		 t))
	  (t
	   (setf (symbol-record-function-to-link symbol-record)
		 function-record)
	   (setf (symbol-record-function-requires-linking symbol-record)
		 t)))))


(defun update-function-descriptor-for-definition (name descriptor)
  (setf (function-descriptor-linked-locally-p descriptor) t)
  (let ((name (principal-name-of-function-name name)))
    (when (and *function-symbols*
	       (forward-defined-as-symbol name))
      ;; Ensure that symbol is dumped globally
      (mark-quoted-symbol name))))

(defun translate-non-toplevel-defun (name principal setfp lambda-list body)
  (re-translate-form
    `(progn
       (setf ,(if setfp
		  `(trun:setf-function ',principal)
	          `(symbol-function ',name))
	     (named-function ,name ,lambda-list ,@body))
       ',name)))

(define-translator-parameter *funcallable-foreign-functions-p* nil)

;;; def-foreign-callable.
;;; This is like defun, except that:
;;; 1. It generates extra code to box arguments and unbox return value
;;; 2. It sets up the foreign-arguments and foreign-return-types in the
;;;    descriptor, so that it can be called from lisp
;;; 3. It does not set up a function object or a symbol.
;;; 
;;; Possibly the redefine-callable-function (which does part 2) should be
;;; changed to
;;; a translate-form of a def-foreign-function which does the same
;;; thing, since functions defined with def-foreign-callable should
;;; be just like other foreign functions as far as calling from lisp
;;; is concerned, except that externs for them are dumped in callables.h

(define-toplevel-form tx:def-foreign-callable
    (&whole form
	    name-and-options arguments
	    &body body)
  (with-translator-message `(tx:def-foreign-callable
				,(if (atom name-and-options)
				     name-and-options
				     (car name-and-options)))
    (multiple-value-bind (lisp-name name return-type)
	(if (atom name-and-options)
	    (values name-and-options nil nil)
	    (destructuring-bind (lisp-name &rest options)
		name-and-options
	      (let ((name nil)
		    (return-type :object)
		    (macro nil))
		(dolist (option options)
		  (unless (consp option)
		    (error "Illegal option ~S" option))
		  (ecase (car option)
		    (:name (setq name (cadr option)))
		    (:return-type (setq return-type (cadr option)))
		    (:language
		     (unless (eq (cadr option) ':c)
		       (error "~S argument must be ~S" ':language ':c)))))
		(values lisp-name name return-type macro))))
      (unless *toplevel-p*
	(error "def-foreign-callable for function ~S encountered when not ~
            at top level" lisp-name))
      (print-progress-message "Foreign-callable Function" lisp-name)
      (multiple-value-bind (real-body decls doc) (parse-body body t)
	(declare (ignore real-body decls))
	(redefine-callable-function name lisp-name arguments return-type doc)
	(when *prepare-stream*
	  (write-prepare-form
	   `(redefine-callable-function ',name ',lisp-name ',arguments
	                                ',return-type)))
	(unless *compile-time-only*
	  (translate-defcallable lisp-name return-type arguments body))))))

(defun redefine-callable-function (c-name lisp-name arguments return-type
					  &optional documentation)
  (macro->fn lisp-name)
  ;; Generate C names for the function.
  (declare-function-entry-c-name lisp-name c-name)
  ;; Compare old descriptor (if it exists) with new one, to determine whether
  ;; there have been changes that might invalidate already translated code.
  (let ((old  (defined-as-function lisp-name))
	(new  (make-function-descriptor
	       :lambda-list         (mapcar #'car arguments)
	       :documentation       documentation
	       :argument-types      (mapcar #'(lambda (arg-spec)
						(lisp-type (cadr arg-spec)))
					    arguments)
	       :return-type         (foreign-type->lisp-type
				     (if (eq return-type ':values)
					 ':object
					 return-type))
	       :foreign-protocol    (if (eq return-type ':values)
					:foreign-arguments-function
					:macro)
	       :foreign-arguments   (mapcar #'(lambda (arg-spec)
						`(,(second arg-spec) nil))
					    arguments)
	       :foreign-return-type (if (eq return-type ':values)
					:object
					return-type)
	       :extern-required     t
	       :funcallable-p       *funcallable-foreign-functions-p*
	       :sets-values-count-p (eq return-type ':values))))
    (update-function-descriptor-properties new lisp-name)
    (when (and old (not (argument-descriptors-equal-p old new)))
      (warn "Redefining function ~s as a foreign-callable function with ~
        incompatible argument list." lisp-name))
    (when (and old (function-descriptor-generic-function-p old))
      (warn "Redefining generic function ~S as a foreign-callable function."
		     lisp-name))
    (setf (defined-as-function lisp-name) new)))

(defun translate-defcallable (lisp-name return-type arguments body)
  (let ((*toplevel-p*  nil)
	(*free-temporaries* nil)
	(sets-values-count-p (eq return-type ':values)))
    (when sets-values-count-p
      (setq return-type ':object))
    (let* ((lambda-list (mapcar #'car arguments))
	   (argument-types (mapcar #'cadr arguments))
	   (record (translate-defcallable-aux
		    lisp-name lambda-list body
		    (mapcar #'(lambda (ft) (translator-foreign-type ft))
			    argument-types)
		    (translator-foreign-type return-type)
		    sets-values-count-p)))
      (when (some #'(lambda (arg)
		      (or (not (symbolp arg))
			  (member arg translator-lambda-list-keywords)))
		  lambda-list)
	(error "Error in compiling ~A: only required arguments are ~
         permitted in def-foreign-callable: no destructuring or ~
         lambda-list keywords are permitted" lisp-name))
      (translate-leaf-toplevel-form-aux
       `(,(make-target-form 'function-definition record)
	 ,@(if (record-documentation-p
		(function-record-documentation record))
	       (list (make-target-form
		      'call-generic
		      '(setf tcl:documentation)
		      (translate-constant-aux
		       (function-record-documentation record))
		      (translate-constant-aux lisp-name)
		      (translate-constant-aux 'function)))))))))

;;; end def-foreign-callable.

;;; Deftype.  This currently only makes the type expander defined at
;;; translation-time, not at run-time.

(define-translator-macro deftype (name lambda-list &body body)
  `(progn
     (eval-when (:compile-toplevel)
       (print-progress-message "Type" ',name)
       (define-translator-type ,name ,lambda-list ,@body)
       (c-name-of-quoted-symbol ',name))
     ',name))

;;; Define-declaration.  This currently only makes the declaration handler
;;; defined at translation time, not at runtime.

(define-translator-macro define-declaration (name lambda-list &body body)
  `(progn
     (eval-when (:compile-toplevel)
       (print-progress-message "Declaration" ',name)
       (define-translator-declaration ,name ,lambda-list ,@body)
       (c-name-of-quoted-symbol ',name))
     ',name))


;;; TX:DEF-FOREIGN-FUNCTION
;;; (TX:DEF-FOREIGN-FUNCTION (<lisp-name> (:NAME <c-name>)
;;;                                       (:RETURN-TYPE <return-type>))
;;;   (<argument-name> <argument-type>)*)
;;; lisp-name     ::= a symbol naming a lisp function
;;; c-name        ::= a string naming a c function
;;; argument-name ::= symbol naming an argument
;;; argument-type ::= see foreign types defined for the translator (unboxing
;;;                   macros)
;;; return-type   ::= see foreign types defined for the translator (boxing
;;;                   macros)

(defun make-dff-function-descriptor (argument-specs return-type funcallable-p
						    macro protocol)
  (setq argument-specs
	(mapcar #'(lambda (spec)
		    (if (consp spec)
			spec
			(if (member spec '(&optional &rest &key))
			    spec
			    (list spec :object)))) ; should warn here
		argument-specs))
  (make-function-descriptor
   :lambda-list         (mapcar #'(lambda (arg-spec)
				    (if (consp arg-spec)
					(let ((name (car arg-spec)))
					  (if (consp name)
					      (car name)
					      name))
					arg-spec))
				argument-specs)
   :argument-types      (mapcar #'(lambda (foreign-arg)
				    (if (consp foreign-arg)
					(lisp-type (cadr foreign-arg))
					foreign-arg))
				argument-specs)
   :return-type         (foreign-type->lisp-type return-type)
   :foreign-protocol    protocol
   :foreign-arguments   
   (mapcar #'(lambda (arg-spec)
	       (cond ((consp arg-spec)
		      `(,(second arg-spec)
			 ,(or (third arg-spec)
			      macro)))
		     ((eq arg-spec '&rest)
		      arg-spec)
		     (t
		       (error "arg-spec ~S is not supported" arg-spec))))
	   argument-specs)
   :foreign-return-type return-type
   :funcallable-p       funcallable-p))

(define-translator-parameter *allow-multiple-foreign-functions-per-c-name* nil)

(setq *remove-leading-underscore-from-foreign-string-p* :warn)

(defvar *foreign-function-name-p* nil)

(defun declare-function-entry-c-name (lisp-name c-name &optional
						allow-multiple-p)
  (when *funcallable-foreign-functions-p*
    (c-name-of-function-object lisp-name)
    (c-name-of-quoted-symbol (principal-name-of-function-name lisp-name)))
  (when (and (null c-name)
	     *lisp-symbol-to-foreign-string-method*)
    (setq c-name 
	  (funcall *lisp-symbol-to-foreign-string-method* lisp-name ':c)))
  (when (and c-name *remove-leading-underscore-from-foreign-string-p*)
    (setq c-name (string c-name))
    (when (zerop (length c-name))
      (error "c-name is ~S" c-name))
    (when (char= (char c-name 0) #\_)
      (when (eq *remove-leading-underscore-from-foreign-string-p* ':warn)
	(setq *remove-leading-underscore-from-foreign-string-p* t)
	(warn "Removing one leading underscore from function names~@
               (for compatibility with C).~@
               Set ~S to T~@
               to avoid the warning, or to NIL to inhibit the removal."
	       '*remove-leading-underscore-from-foreign-string-p*))
      (setq c-name (subseq c-name 1))))
  (let ((existing-name (name-of-function-entry lisp-name)))
    (when (and c-name existing-name (not (string= c-name existing-name)))
      (error "Function ~S already has the c-name ~S, instead of ~S"
	     lisp-name existing-name c-name))
    (or existing-name
	;; *** It is necessary to make this C name
	;; *** "reserved" before any name-mapping is done.
	(if c-name
	    (if (or allow-multiple-p
		    *allow-multiple-foreign-functions-per-c-name*)
		(progn
		  (tutil::record-c-name c-name t)
		  (setf (name-of-function-entry lisp-name) c-name))
		(let ((*foreign-function-name-p* t))
		  (setf (c-name-of-function-entry lisp-name) c-name)))
	    (c-name-of-function-entry lisp-name)))))

(define-toplevel-form tx:def-foreign-function
    (name-and-options &rest argument-specs)
  (with-translator-message `(tx:def-foreign-function
				,(if (atom name-and-options)
				     name-and-options
				     (car name-and-options)))
    (multiple-value-bind (lisp-name c-name return-type macro funcallable-p
				    max-rest-args protocol)
	(if (atom name-and-options)
	    (values name-and-options nil nil nil nil 10 :macro)
	    (destructuring-bind (lisp-name &rest options)
		name-and-options
	      (let ((name nil)
		    (return-type :object)
		    (macro nil)
		    (funcallable-p *funcallable-foreign-functions-p*)
		    (max-rest-args 10)
		    (protocol :macro))
		(dolist (option options)
		  (unless (consp option)
		    (error "Illegal option ~S" option))
		  (ecase (car option)
		    (:name (setq name (cadr option)))
		    (:return-type (setq return-type (cadr option)))
		    (:max-rest-args (setq max-rest-args (cadr option)))
		    (:language
		     (unless (eq (cadr option) ':c)
		       (error "~S argument must be ~S" ':language ':c)))
		    (:funcallable-p
		     (setq funcallable-p (cadr option)))
		    (:macro
		     (setq macro (cadr option)))
		    (:protocol
		     (setq protocol (cadr option)))))
		(values lisp-name name return-type macro funcallable-p
			max-rest-args protocol))))
      (declare (ignore max-rest-args))
      (print-progress-message "Foreign Function" lisp-name)
      (unless *toplevel-p*
	(warn "~S must be at toplevel" 'tx:def-foreign-function))
      (redefine-foreign-function lisp-name c-name argument-specs
				 return-type funcallable-p macro protocol)
      (when *prepare-stream*
	(write-prepare-form
	 `(redefine-foreign-function
	   ',lisp-name ',c-name ',argument-specs ',return-type
	   ',funcallable-p ',macro ',protocol)))
      (unless *compile-time-only*
	(when funcallable-p
	  (let ((function-record (new-function-record lisp-name :global))
		(lambda-list (mapcar #'(lambda (spec)
					 (if (consp spec)
					     (car spec)
					     spec))
				     argument-specs)))
	    (setf (function-record-lambda-list-info function-record)
		  (compute-lambda-list-info lambda-list))
	    (make-function-links lisp-name lisp-name nil function-record)))))))

(defun redefine-foreign-function (lisp-name c-name argument-specs return-type
					    funcallable-p macro protocol)
  (declare-function-entry-c-name lisp-name c-name)
  (let ((fd (make-dff-function-descriptor argument-specs return-type
					  funcallable-p macro protocol)))
    (when (function-information-value lisp-name 'dllexport)
      (setf (function-descriptor-dllexport-p fd) t))
    (when (function-information-value lisp-name 'dllimport)
      (setf (function-descriptor-dllimport-p fd) t))
    (setf (defined-as-function lisp-name) fd)))

(define-translator-macro tx:def-foreign-synonym-type (name existing-name)
  `(progn
     (eval-when (:compile-toplevel)
       (print-progress-message "Foreign Synonym Type" ',name)
       (define-translator-foreign-synonym-type ,name ,existing-name))
     (eval-when (:load-toplevel :execute)
       (tx:define-foreign-synonym-type ',name ',existing-name))
     ',name))

(define-translator-macro def-foreign-struct
    (name-and-options &rest slot-descriptions)
  (let* ((name (if (consp name-and-options)
		   (car name-and-options)
		   name-and-options))
	 (constructor-info (when (consp name-and-options)
			     (assoc :constructor (cdr name-and-options))))
	 (constructor (if constructor-info
			  (cadr constructor-info)
			  (intern (format nil "MAKE-~A" name))))
	 (predicate (intern (format nil "~A-P" name)))
	 (alignment-info (when (consp name-and-options)
			   (assoc :alignment (cdr name-and-options))))	 
	 (slots (mapcar #'parse-foreign-struct-slot slot-descriptions))
	 (modulus (or (when alignment-info
			(getf (cadr alignment-info) ':modulus))
		      (apply #'lcm 
			     (mapcar #'(lambda (fsi)
					 (translator-foreign-type-modulus
					   (foreign-slot-info-foreign-type fsi)))
				     slots))))
	 (remainder (or (when alignment-info
			  (getf (cadr alignment-info) ':remainder))
			0))
	 (conc-name (format nil "~A-" name))
	 (foreign-name (lisp-fn-symbol->foreign-fn-symbol name))
	 (accessors (make-accessor-symbols conc-name slots))
	 (foreign-accessors (make-foreign-accessor-symbols accessors))
	 (foreign-setters (make-foreign-setter-symbols accessors))
	 (info (make-foreign-structure-info
		:name name
		:package *package*
		:foreign-name foreign-name
		:local-slots slots
		:local-slot-foreign-accessors foreign-accessors
		:modulus modulus
		:remainder remainder)))
    (setf (defined-as-foreign-structure name) info)
    `(progn
       (eval-when (:compile-toplevel)
	 (print-progress-message "Foreign Structure" ',name)
	 (make-foreign-structure ',foreign-name)
	 (define-translator-foreign-type ,name
	   :lisp-type tx:foreign-pointer
	   :boxer :make-foreign-pointer
	   :unboxer :foreign-pointer-address
	   :c-type ,(c-name-of-structure-type foreign-name))
	 (make-foreign-structure-foreign-accessors 
	  ',foreign-accessors ',slots ',name)
	 ,@(make-foreign-slot-setters
	     name accessors foreign-accessors foreign-setters slots))
       (eval-when (:load-toplevel :execute)
	 (define-foreign-structure-predicate ,predicate ,name)
	 ,@(make-foreign-structure-accessors accessors foreign-accessors slots name)
	 (define-foreign-structure-constructor ,constructor ,name)
	 ',name))))

;;; The rest of the defining macros will go elsewhere.
;;; Here's a list of them, just for completeness.

;;; CLOS-related things:
;;; defclass
;;; defgeneric
;;; define-condition
;;; define-method-combination
;;; defmethod

;;; SETF-related things:
;;; define-modify-macro
;;; define-setf-method
;;; defsetf

;;; Miscellaneous:
;;; defpackage
;;; defstruct

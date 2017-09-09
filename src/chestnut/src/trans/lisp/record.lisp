;;; -*- Mode: Lisp; Package: TIMPL; Syntax: Common-Lisp -*-
;;;
;;; record.lisp -- variable/function records code walker utilities
;;;
;;; Author :  Sandra Loosemore
;;; Date   :  19 Dec 1990
;;;
;;; Copyright (c) 1990, Chestnut Software Inc.
;;;
;;;

(in-package "TIMPL")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/record.lisp,v $"
 "$Revision: 1.8 $"
 "$Date: 2007/06/26 19:48:37 $")

;;; Variable and function name bindings have a "record" associated
;;; with them to store various bits of information about the binding,
;;; such as whether or not it is closed.  This information is used
;;; in code generation.  Each function definition processed by
;;; the translator has a list of records corresponding to the 
;;; variables and functions that are bound within that function,
;;; and references to lexically bound variables and functions include
;;; a pointer to the corresponding record.  Most of this information
;;; is filled in after the code walk is complete.






;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;; Function definition records
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;; Note that this is information about a function *definition*, not
;;; a function name binding.
;;; In the generated C code, all variables used within the function are
;;; declared at the head of the function.

(defun print-function-record (record stream depth)
  (declare (ignore depth))
  (format stream "#<Function-record ~s>" (function-record-name record)))

(defstruct (function-record
	     (:constructor %make-function-record)
	     (:print-function print-function-record))
  (name               nil)    ; the Lisp function-name
  (unique-name        nil)    ; the name of the C entry point, a string
  (lambda-list-info   nil)    ; lambda-list-info structure
  (documentation      nil)    ; the doc-string or nil
  (closure-state      nil)    ; holds closure information
  (classification     nil)    ; value is one of the following keywords that
			      ; describes the function:
			      ;  :global (toplevel defun)
			      ;  :callable (toplevel def-foreign-callable)
			      ;  :generic-function (toplevel generic function)
			      ;  :local  (locally-defined or anonymous fn)
			      ;  :init   (init function)
			      ;  :ignore (fn will be processed but not emitted)
  (variadic-p         nil)    ; does the fn take variable numbers of args?

  (external-variables nil)    ; records of closed-over variables referenced
  (nested-functions   nil)    ; function-records for nested functions
  (constants          nil)    ; structured constants referenced in the fn
  (info               nil)

  (returns-one-value-p nil))

(defmacro define-function-record-info (conc-name info-slot-name &rest slots)
  `(progn
     (defstruct ,info-slot-name ,@slots)
     ,@(mapcar #'(lambda (slot)
		   (let* ((slot-name (if (consp slot) (car slot) slot))
			  (info (intern (sformat "~A-~A"
						info-slot-name slot-name)))
			  (extern (intern (sformat "~A~A"
						  conc-name slot-name))))
		     `(defmacro ,extern (object)
			`(,',info (,',info-slot-name ,object)))))
	       slots)
     (eval-when (compile load eval)
       (defparameter ,(intern (sformat "*~A-~A*" info-slot-name 'slots))
	 ',(mapcar #'(lambda (slot)
		       (let ((slot-name (if (consp slot) (car slot) slot)))
			 (intern (string slot-name) :keyword)))
		   slots)))))

(define-function-record-info function-record- function-record-info
  (argument-variables nil)    ; records for required argument variables
  (local-variables    nil)    ; records for locally bound variables
  (statements         nil)    ; the body of the function
  (catchframe-count   0)      ; max depth of nested catches
  (specialframe-count 0)      ; max depth of nested special bindings
  (areaframe-count    0)      ; max depth of nested with-foo-area/allocation
  (frontierframe-count  0)    ; max depth of nested with-local-allocation
  (local-temps        nil)    ; list of keywords for local temps used here
  (uses-stack-p       nil)    ; does the fn stack-allocate things?
  (gc-protects-p      nil)    ; does the fn gc-protect locals?
  (flow-entry         nil)    ; Start of control flow graph
  (flow-exit          nil)    ; End of control flow graph
  (variables-requiring-protection nil)
			      ; This includes locals, externals, and
			      ; arguments
  (foreign-argument-types nil) ; Nil or list of types. If list of types,
			      ; must be equal to length of lambda-list,
			      ; which must be all required arguments.
  (foreign-return-type nil)   ; C type returned by function (actually
			      ; contents of this and previous slot are
			      ; keywords, defined by
			      ; define-foreign-type) 
  (nonrelocating-p    nil)    ; was the fn declared nonrelocating?
  )

(defmacro make-function-record (&rest args)
  (let ((new-args nil)
	(new-info-args nil))
    (loop (unless args (return nil))
	  (let ((key (pop args))
		(form (pop args)))
	    (if (member key *function-record-info-slots*)
		(progn (push key new-info-args) (push form new-info-args))
		(progn (push key new-args)  (push form new-args)))))
    `(%make-function-record
      :info (make-function-record-info ,@(nreverse new-info-args))
      ,@(nreverse new-args))))

(defun new-function-record (name classification)
  (make-function-record :name name
			:classification classification))

(defun clear-function-record (record &optional init-p)
  (setf (function-record-info record) nil)
  (mapc #'clear-variable-record (function-record-closure-state record))
  (mapc #'clear-variable-record	(function-record-external-variables record))
  (when init-p (clear-function-record-final record))
  nil)

(defun clear-function-record-final (record)
  (mapc #'clear-function-record-final
	(function-record-nested-functions record))
  (setf (function-record-nested-functions record) nil)
  (setf (function-record-closure-state record) nil)
  (setf (function-record-external-variables record) nil)
  (mapc #'clean-target-form (function-record-constants record))
  (setf (function-record-constants record) nil))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Variable/function binding records
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;; Definitions for variable-records.  These are used to represent bindings
;;; of C variables -- in Lisp terms, both variable and function bindings
;;; have an associated variable-record.

(defun print-variable-record (record stream depth)
  (declare (ignore depth))
  (format stream "#<Variable-record ~s~@[ ~X~]>"
	   (variable-record-name record)
	   #-(and lucid (not translating)) nil
	   #+(and lucid (not translating)) (lucid::%pointer record)))

(declaim (special *object-translator-foreign-type*))

(defstruct (variable-record (:print-function print-variable-record)
			    (:constructor %make-variable-record))
  (name                           nil) ; the Lisp name of the variable
				       ; or function
  (unique-name                    nil) ; the name of the C variable
  (static-variable-name           nil) ; the name of the C temp which
				       ; holds the "body" of the constant
  (in-function                    nil) ; the function-record owning this
				       ; binding
  (flags                          0)
  (foreign-type                   *object-translator-foreign-type*)
  (lisp-type                      t)   ; the lisp type of the variable
  (closure-state                  nil) ; holds closure information
  (binder                         nil) ; the with-lexical-variables
				       ; target form that binds this
				       ; variable (if any)
  (referenced-p                   nil) ; if referenced then either t or
				       ; :ignore if the reference will
				       ; not appear in generated code
				       ; else nil
  (modified-p                     nil) ; list of function-records
  (needs-gc-protection            nil)   ; a boolean
  (references                     nil) ; list of local-variable
				       ; target forms referencing
				       ; this variable that occur in
				       ; non-lvalue-context
  (setters                        nil) ; list of local-variable
				       ; target forms referencing
				       ; this variable that occur in
				       ; lvalue-context
  ;;(live-statements               nil)     ; where in the target language
				       ; code is this variable "live"?
				       ; That is, where would changes
				       ; to its value affect code
				       ; semantics?
  ;; The above slot is obsolete. To avoid manipulating long lists of
  ;; live-statements, we only keep track of those live statements
  ;; that might be relevant later.
  (live-setter-statements        nil)  ; Any setq or values-assign
				       ; statement at which this variable
				       ; is live, whether it sets this
				       ; variable or some other one.
  (live-relocating-statements    nil)  ; for use in determining
  (live-setjmp-statements        nil)  ; protection requirements.
  (coalesced-to                  nil)
  (coalesced-from                nil)  ; List of variables that will
				       ; be coalesced to this one
  (setq-statement                nil) 
  (try-coalescing-to              nil) ; hint from the codewalkers
				       ; to the optimizer about
				       ; how to eliminate this temp.
  (dangerous-setjmps              nil) ; setjmps such that this variable
				       ; may be modified between the
				       ; setjmp and the corresponding
				       ; longjmp; each is represented
				       ; by a flow-graph node such that
				       ; if the variable is live at
				       ; that node, trouble can result.
  (initializer                    nil)
  (needs-setjmp-protection        nil)
  )

(define-flags variable-record- variable-record-flags
  (closed-p                       nil)     ; a boolean
  (actual-closed-p                nil)     ; a boolean
  (nonrelocatable-type            nil)     ; known to contain only
                                           ; objects of nonrelocatable type.
  (ignore-p                       nil)     ; declared ignore?
  (ignorable-p                    nil)     ; declared ignorable?
  (pending-constant-p             nil)     ; holds uninitialized constant?
  (constant-declaration-emitted-p nil)     ; holds a constant whose decl
                                           ; has been emitted?
  (special-p                      nil)
  (unread-p                       nil)
  (unwritten-p                    nil)
  (nonrelocatable-p               nil)     ; declared to contain only
                                           ; objects of nonrelocatable type.
  (type-from-init-p               nil)
  (allow-type-from-init-p         t)
  (read-once-p                    nil)
  (compiler-generated-temp-p      nil)); was this variable introduced
				       ; by the compiler (includes
				       ; those introduced by our
				       ; translator-macros and
				       ; translator-compliler-macros)?


(define-forward-variable-reference *current-function*)

(defmacro make-variable-record (&rest args)
  (let ((new-args nil)
	(new-flags nil))
    (loop (unless args (return nil))
	  (let ((key (pop args))
		(form (pop args)))
	    (if (member key *variable-record-flags*)
		(progn (push key new-flags) (push form new-flags))
		(progn (push key new-args)  (push form new-args)))))
    `(%make-variable-record
      :flags (make-variable-record-flags ,@(nreverse new-flags))
      ,@(nreverse new-args))))

(defun clear-variable-record (record)
  (setf (variable-record-binder record) nil)
  (setf (variable-record-references record) nil)
  (setf (variable-record-setters record) nil)
  (setf (variable-record-live-setter-statements record) nil)
  (setf (variable-record-live-relocating-statements record) nil)
  (setf (variable-record-coalesced-to record) nil)
  (setf (variable-record-coalesced-from record) nil)
  (setf (variable-record-try-coalescing-to record) nil))

(define-forward-variable-reference *object-translator-foreign-type*)

(defun new-variable-record 
    (name &optional (foreign-type *object-translator-foreign-type*))
  (make-variable-record :name name
			:in-function *current-function*
			:foreign-type foreign-type))


(defun print-symbol-record (record stream depth)
  (declare (ignore depth))
  (format stream "#<symbol-record ~s>" (symbol-record-name record)))

(defstruct (symbol-record (:print-function print-symbol-record)
			  (:constructor %make-symbol-record))
  (name               nil)      ; the symbol itself
  (function-to-link   nil)      ; function record of a function which needs
			        ; to be linked to this symbol, if the symbol
                                ; is generated.
  (setf-function-to-link   nil) ; function record of a setf function which
                                ; needs to be linked to this symbol, if the
                                ; symbol is generated.
  (cookie nil)                  ; This record is invalid (left over from
                                ; a previous translation) if this is not
                                ; eq to *current-translation-cookie*
  (flags 0))

(define-flags symbol-record- symbol-record-flags
  (variable-exists nil)         ; The code contains a reference to a special
                                ; variable by this name.
  (function-requires-linking nil)
  (setf-function-requires-linking nil)
  (variable-requires-linking nil)
  (exists-at-runtime nil)       ; Object Qsymbol-name has been emitted for
                                ; this symbol.
  )

(defmacro make-symbol-record (&rest args)
  (let ((new-args nil)
	(new-flags nil))
    (loop (unless args (return nil))
	  (let ((key (pop args))
		(form (pop args)))
	    (if (member key *symbol-record-flags*)
		(progn (push key new-flags) (push form new-flags))
		(progn (push key new-args)  (push form new-args)))))
    `(%make-symbol-record
      :flags (make-symbol-record-flags ,@(nreverse new-flags))
      ,@(nreverse new-args))))

;;; In many places involving a :value context, the value of a processed
;;; form needs to be stored in a temporary.

;;; rebound to nil whenever *toplevel-p* is bound to nil
(defvar *free-temporaries* nil)
(defvar *allocated-temporaries*)
(defparameter *realocate-temporaries-p* nil)

(defmacro allocate-temporary-internal ()
  `(make-variable-record :name (make-symbol "TEMP")
			 :in-function *current-function*
			 :compiler-generated-temp-p t
			 :foreign-type foreign-type))

(defun allocate-temporary (&optional 
			   (foreign-type *object-translator-foreign-type*))
  (macrolet ((check-record (record update)
	       `(when (and (eq (variable-record-foreign-type ,record)
			       foreign-type)
			   (eq (variable-record-in-function ,record)
			       *current-function*))
		  ,update
		  (return-from allocate-temporary ,record))))
    (when *free-temporaries*
      (let ((temp (car *free-temporaries*)))
	(check-record temp (pop *free-temporaries*))
	(let* ((tail *free-temporaries*)
	       next)
	  (loop (setq next (cdr tail))
		(unless next (return nil))
		(setq temp (car next))
		(check-record temp (setf (cdr tail) (cdr next)))
		(setq tail next)))))
    (let ((vr (allocate-temporary-internal)))
      (when (and *realocate-temporaries-p*
		 (boundp '*allocated-temporaries*))
	(push vr *allocated-temporaries*))
      vr)))

(defun free-temporary (temp)
  (when *realocate-temporaries-p*
    (when (boundp '*allocated-temporaries*)
      (setq *allocated-temporaries* (delq temp *allocated-temporaries*)))
    (pushnew temp *free-temporaries*))
  temp)

(defmacro with-temporary-variables (&body forms)
  `(let ((*allocated-temporaries* nil))
     (multiple-value-prog1 (progn ,@forms)
       (when *realocate-temporaries-p*
	 (dolist (temp *allocated-temporaries*)
	   (pushnew temp *free-temporaries*))))))

;;; ***** 
;;; The functions local-variable-reference and local-variable-assignment
;;; have been moved to target.lisp because make-target-form is now a macro.


;;; Actually add variable and function name bindings to the environment.
;;; The binding is decorated with its "record" which is used in handling
;;; references to that binding.
;;; *** Style issue:  manipulating parsed declarations directly is
;;; *** kind of ugly.

;called only by bind-one-variable.  The variable-record gets filled in later.
(defun bind-variable-name (name decls env)
  (translator-augment-environment env
    :variable (list name)
    :declare (cons `(tx:variable-information
		     (,name variable-record nil))
		   decls)))

;called only by translate-flet-labels-aux
(defun bind-function-name (name decls vrecord frecord env)
  (translator-augment-environment env
      :function (list name)
      :declare (cons `(tx:function-information
		          (,name variable-record ,vrecord)
			  (,name function-record ,frecord))
		     decls)))



;;; Redefinition records
;;;
;;; This stuff is used to control the emitting of the C entry functions for
;;; variadic generic functions.  See also establish-generic-function.
;;;
;;; It's also used to control the emitting of definitions of global variables.

(defstruct (redefinition-record
	     (:constructor %make-redefinition-record (file cookie)))
  file
  cookie
  (definition-dumped nil)
  )

(define-forward-variable-reference *current-translated-file*)

(defun compute-redefinition-record ()
  (let ((file *current-translated-file*))
    (%make-redefinition-record file (translated-file-cookie file))))

(defun update-redefinition-record (record)
  (let* ((file *current-translated-file*)
	 (cookie (translated-file-cookie file)))
    (when (and (eq file (redefinition-record-file record))
	       (not (eql cookie (redefinition-record-cookie record))))
      (setf (redefinition-record-cookie record) cookie)
      (setf (redefinition-record-definition-dumped record) nil))))

(defun redefinition-record-note-definition-dumped (record)
  (setf (redefinition-record-definition-dumped record) t)
  (let ((file *current-translated-file*))
    (setf (redefinition-record-file record) file
	  (redefinition-record-cookie record) (translated-file-cookie file))))

(defun redefinition-record-definition-needs-dumping (record)
  (or (not (redefinition-record-definition-dumped record))
      (let ((file *current-translated-file*))
	(and (eq file (redefinition-record-file record))
	     (not (eql (redefinition-record-cookie record)
		       (translated-file-cookie file)))))))

(defun redefinition-record-definition-dumped-in-this-file (record)
  (eq *current-translated-file* (redefinition-record-file record)))





;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Other codewalker state
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;;; Some other random bits of information (such as a list of the lexically
;;; visible special bindings) are also stored in the environment.
;;; *** Same problems with manipulating parsed declarations.

(defun get-codewalker-state (name env)
  (translator-declaration-information name env))

(defun add-codewalker-state (new name env)
  (translator-augment-environment env
    :declare `((tx:declaration-information
		(,name .
		 ,(cons new
			(translator-declaration-information name env)))))))

;;; binghe, 2009/4/12, moved from util.lisp
(in-package "TUTIL")

(defun reset-read-once-setqs (env)
  (when timpl::*do-read-once-optimization*
    (dolist (contour (translator-environment-lexical-part env))
      (when (and (variable-information-contour-p contour)
		 (eq ':lexical (variable-information-contour-usage contour)))
	(let* ((decls (variable-information-contour-declarations contour))
	       (record (cdr (assoc 'timpl::variable-record decls))))
	  (when (eq (timpl::variable-record-setq-statement record) ':none)
	    (return-from reset-read-once-setqs nil))
	  (setf (timpl::variable-record-setq-statement record) ':none))))))

(in-package "TIMPL")

;;; Note special bindings in the environment.

(defun bind-special-variables (names env)
  (reset-read-once-setqs env)
  (add-codewalker-state names 'special-bindings env))


;;; Note catches and unwind-protects in the environment.

(defun bind-catcher (tag env)
  (reset-read-once-setqs env)
  (add-codewalker-state tag 'catchers env))


;;; Tagbody and block names also have records associated with them.
;;; The shared slots are used to detect "hard" situations that have to
;;; be converted to catches and throws.

(defstruct tagbody-block-record
    (in-function   nil)
    (in-catchers   nil)
    (in-bindings   nil)
    (stack-level   nil)
    (hard-p        nil))       ; catch tag value

(defstruct (tagbody-record (:include tagbody-block-record))
    (names         nil)        ; the labels in the tagbody
    (labels        nil))       ; the corresponding unique C labels

(defstruct (block-record (:include tagbody-block-record))
    (name          nil)        ; the block name
    (label         nil)        ; the corresponding unique C label
    (break-p       nil)        ; exit with break instead of goto?
    (context       nil)        ; propagate context to returns
    (returns       nil))       ; merged type from all returns


;;; The binder functions for BLOCK and TAGBODY return the new environment
;;; and a record as values.

(defun bind-tagbody-names (names env)
  (reset-read-once-setqs env)
  (let ((record  (make-tagbody-record
		  :names names
		  :labels (mapcar
			   #'(lambda (name)
			       (make-symbol
				(if (symbolp name)
				    (symbol-name name)
				    (sformat "LABEL-~a" name))))
			   names))))
    (initialize-tagbody-block-record record env)
    (values
     (add-codewalker-state (cons names record) 'tagbody-binding env)
     record)))

(defun bind-block-name (name env context)
  (reset-read-once-setqs env)
  (let ((record  (make-block-record
		  :name name
		  :label (make-symbol
			  (if name
			      (sformat "END-~a" name)
			      "END"))
		  :context context)))
    (initialize-tagbody-block-record record env)
    (values
     (add-codewalker-state (cons name record) 'block-binding env)
     record)))


;;; Find the tagbody record binding NAME.

(defun tagbody-binding (name env)
  (let ((state  (get-codewalker-state 'tagbody-binding env)))
    (or (cdr (assoc name state :test #'member))
	(error "No TAGBODY label ~s is visible here." name))))


;;; If ignore-break-p is true, ignore any binding of the name to a record
;;; that has the break-p flag set.

(defun block-binding (name env &optional ignore-break-p (error-p t))
  (let ((state  (get-codewalker-state 'block-binding env)))
    (or (cdr (if ignore-break-p
		 (car (member-if
		       #'(lambda (e)
			   (and (not (block-record-break-p (cdr e)))
				(eq name (car e))))
		       state))
		 (assoc name state)))
	(when error-p
	  (error "No BLOCK named ~s is visible here."  name)))))
					       

;;; Used to detect stuff being pushed onto the stack.  Modified by such things
;;; as multiple-value-call, multiple-value-prog1, and unwind-protect, which
;;; temporarily save values on the stack.

(defvar *stack-level* 0)

(defmacro with-stack-level (&body body)
  `(let ((*stack-level* (1+ *stack-level*)))
     ;; Record stack usage for current function.
     (setf (function-record-uses-stack-p *current-function*) t)
     (locally ,@body)))

;;; Set up the information in the tagbody or block record that is used
;;; to detect "hard" transfers of control.

(defun initialize-tagbody-block-record (record env)
  (setf (tagbody-block-record-in-function record)
	*current-function*)
  (setf (tagbody-block-record-in-catchers record)
	(get-codewalker-state 'catchers env))
  (setf (tagbody-block-record-in-bindings record)
	(get-codewalker-state 'special-bindings env))
  (setf (tagbody-block-record-stack-level record) *stack-level*)
  record)



;;; A predicate to detect a "hard" transfer of control.

(defun hard-tagbody-block-p (record env)
  (or (tagbody-block-record-hard-p record)
      (not (and (eq (tagbody-block-record-in-function record)
		    *current-function*)
		(not (memq 'unwind-protect 
			   (tagbody-block-catch-frames record env)))
		(= (tagbody-block-record-stack-level record) *stack-level*)))))

(defun tagbody-block-catch-frames (record env)
  (ldiff (get-codewalker-state 'catchers env)
	 (tagbody-block-record-in-catchers record)))

;;; Count how many special bindings have to be undone when doing
;;; a transfer of control.
;;; The idea is that "current" and "original" are lists of lists of
;;; variables that are bound specially, and they share a common tail.
;;; Count the variables that are in "current" but not in "original".

(defun tagbody-block-special-bindings (record env)
  (let ((current (get-codewalker-state 'special-bindings env))
	(block   (tagbody-block-record-in-bindings record))
	(result  0))
    (loop (when (eq current block) (return result))
	  (unless current (error "~S error" 'tagbody-block-special-bindings))
	  (incf result (length (pop current))))))

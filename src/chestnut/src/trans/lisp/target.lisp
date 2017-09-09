;;; -*- Mode: Lisp; Package: TIMPL; Syntax: Common-Lisp -*-
;;;
;;; target.lisp -- target language utilities
;;;
;;; Author :  Sandra Loosemore
;;; Date   :  05 Jul 1990
;;;
;;; Copyright (c) 1990, Chestnut Software Inc.
;;;
;;;

(in-package "TIMPL")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/target.lisp,v $"
 "$Revision: 1.4 $"
 "$Date: 2007/07/10 16:57:58 $")

(defstruct type-info
  name
  statement-handler
  expression-handler
  emit-statement-function
  emit-expression-function
  gatherer
  pregatherer)

(defmacro target-info (form)
  `(car ,form))

(defmacro target-info-type (target-info)
  `(type-info-name (target-info-type-info ,target-info)))

(defmacro target-form-type (form)
  `(target-info-type (target-info ,form)))

(defmacro target-info-handler (target-info)
  `(type-info-statement-handler (target-info-type-info ,target-info)))

(defmacro target-info-expression-handler (target-info)
  `(type-info-expression-handler (target-info-type-info ,target-info)))

(defmacro target-form-emit-statement-function (form)
  `(type-info-emit-statement-function
     (target-info-type-info (target-info ,form))))

(defmacro target-form-emit-expression-function (form)
  `(type-info-emit-expression-function
     (target-info-type-info (target-info ,form))))

(defmacro target-form-gatherer (form)
  `(type-info-gatherer 
     (target-info-type-info (target-info ,form))))

(defmacro target-form-pregatherer (form)
  `(type-info-pregatherer 
     (target-info-type-info (target-info ,form))))

(defvar *type-info-table* (make-hash-table :test 'eq))

(eval-when (compile load eval)
(defun type-info-variable (name)
  (intern (format nil "*~A-~A*" name 'type-info) "TIMPL"))
)

(defun get-type-info (name)
  (or (gethash name *type-info-table*)
      (setf (gethash name *type-info-table*)
	    (make-type-info :name name))))  

(defmacro statement-handler-def (name)
  `(type-info-statement-handler (get-type-info ,name)))

(defmacro expression-handler-def (name)
  `(type-info-expression-handler (get-type-info ,name)))

(defmacro gatherer (name)
  `(type-info-gatherer (get-type-info ,name)))

(defmacro pregatherer (name)
  `(type-info-pregatherer (get-type-info ,name)))

(defmacro emit-expression-function (name)
  `(type-info-emit-expression-function (get-type-info ,name)))

(defmacro emit-statement-function (name)
  `(type-info-emit-statement-function (get-type-info ,name)))

(defmacro define-statement (name &rest keys)
  (let ((variable (type-info-variable name)))
    `(progn
       (declaim (special ,variable))
       (setq ,variable (get-type-info ',name))
       (setf (statement-handler-def ',name)
	     (make-statement-handler :type ',name ,@keys)))))

(defmacro define-expression (name &rest keys)
  (let ((variable (type-info-variable name)))
    `(progn
       (declaim (special ,variable))
       (setq ,variable (get-type-info ',name))
       (setf (expression-handler-def ',name)
             (make-expression-handler :name ',name ,@keys)))))

(defmacro target-form-args (form)
  `(cdr ,form))

;;; New target form syntax; the car of a target form is now a target-info
;;; struct instead of a symbol. Call target-info-type on the struct, or
;;; target-form-type on the form, to get the symbol identifying the
;;; type of target form (it used to be obtained using (car target-form))
;;;

(defstruct (statement-handler (:print-function print-statement-handler))
  (type nil)
  (flow-function nil)
  (substatements-function #'constantly-nil)
                                ; Returns a list (possibly freshly consed,
                                ; possibly not) of all immediate substatements
                                ; of this statement.
  (expression nil)		; Is this type of statement an expression?
  (l-value nil)			; Can it be an lvalue?
  (initializer nil)             ; Either nil, or a function of one
                                ; variable, to be called on
                                ; a target form as soon as it is made.
                                ; If initializer is present, make-target-form
                                ; returns what the initializer returns,
                                ; so initializers should return their argument,
                                ; unless they actually want to return a from
                                ; different from that requested by
                                ; make-target-form.
  (replace-function             ; how to replace a subform
   #'nsubstitute)               ; (should be a three argument function, with
                                ; argument order like nsubstitute)
  (value-subforms-function      ; Returns list of all substatements
    nil)                        ; which are expressions whose values are used
                                ; by this statement.
  (statement-subforms-function  ; Returns list of all substatements
   nil)                         ; which may legitimately be replaced
                                ; by nonexpression substatments
  (relocating-statement-function; Can execution of this statement
                    nil)        ; (considered as a node
                                ; in the control flow graph; that is, not
                                ; including all of its subexpressions)
                                ; trigger a gc?
  (state-changing-function      ; Will execution of this statement
                   nil)         ; change state?
  (gc-ok-function               ; a function of two variables;
                                ; called with the form and a subform as
                                ; arguments, returns t if the subform can
                                ; be replaced by a form that GC's without
                                ; resulting in gc-unsafe code.
   #'constantly-nil)
  ;; The expression handlers should all get moved to here eventually.
  ;; And functions that call them (all in this file)
  ;; will get changed to look at the
  ;; statement handler instead of the expression handler, after
  ;; checking the value of the expression slot to make sure that
  ;; the argument is an expression.
)

(defun print-statement-handler (record stream depth)
  (declare (ignore depth))
  (format stream "#<handler for ~s>" (statement-handler-type record)))

(defmacro handler (statement)
  `(target-info-handler (target-info ,statement)))

(defmacro statement-flow-function (s)
  `(statement-handler-flow-function (handler ,s)))

(defstruct basic-flow-node 
  (in nil)    ; Statements that might have just been executed
  (out nil)   ; Statements that might be executed next
  (live-variables nil)) ; What local variables are live here? 

(defstruct (target-info (:print-function print-target-info)
			(:constructor %make-target-info)
			(:include basic-flow-node))
  (type-info            nil)    ; The type-info struct for the type of form
  (enclosing-statement  nil)    ; For a statement that is directly on
                                ; the statement list of a function, this
                                ; points to the function record.
  (flags                0))

(define-flags target-info- target-info-flags
  (lvalue-p 	        nil)   	; Does this occur in lvalue context?
                                ; The following slots consider a target
                                ; statement in its role as a node
                                ; in the control flow graph; that is, not
                                ; including all of its subexpressions.
                                ; They are currently used only for calls.
  (nonrelocating        nil)    ; Is this target statement known from
                                ; declarations to be nonrelocating?
  (state-changing       t)
  (state-using          t))

(defvar *first-free-target-info* nil)

(defmacro make-target-info (type-info)
  `(if *first-free-target-info*
       (let ((.result.
	      (shiftf *first-free-target-info*
		      (target-info-type-info *first-free-target-info*))))
	 (setf (target-info-type-info .result.) ,type-info)
	 (setf (target-info-flags .result.) (make-target-info-flags))
	 .result.)
       (progn ; with-static-area ; since some might not get freed.
	 (%make-target-info
	  :flags (make-target-info-flags)
	  :type-info ,type-info))))

(defmacro free-target-info (target-info)
  `(shiftf (target-info-type-info ,target-info)
	   *first-free-target-info* ,target-info))

(defun print-target-info (record stream depth)
  (declare (ignore depth))
  (format stream "#<~s-statement-info~@[ ~X~]>"
	  (let ((type-info (target-info-type-info record)))
	    (when type-info
	      (type-info-name type-info)))
	  #-(and lucid (not translating)) nil
	  #+(and lucid (not translating)) (lucid::%pointer record)))

(defmacro target-form-p (s)
  (once-only (s)
    `(and (consp ,s)
	  (target-info-p (car ,s)))))

(defun substatements (s)
  (let ((fn (statement-handler-substatements-function (handler s))))
    (cond ((eq fn #'cddr) (cddr s))
	  ((eq fn #'cdr) (cdr s))
	  ((eq fn #'constantly-nil) nil)
	  (t (funcall fn s)))))

;;; This regards a statement as a node in the flow graph, not
;;; including nested statements.

;;; Maybe we should give functions with this semantics names like
;;; relocating-node-p, to make this clearer.
(defun relocating-statement-p (s)
  ;; Flow nodes and call nodes are not relocating
  (and (consp s)
       (funcall (statement-handler-relocating-statement-function
		 (handler s))
		s)))

;;; This, on the other hand, regards it as a C statement, including
;;; all nested statements.

;;; Does a statement (potentially) change any state information?
;;; If not, this might permit other statements that would normally
;;; be evaluated in sequence with this expression to be evaluated in
;;; parallel with it.  It also permits the expression to be removed
;;; entirely in contexts where its return values are ignored.
;;;
;;; Any expression that performs destructive updates to its arguments
;;; or that has side-effects such as setting or modifying global 
;;; variables or changing internal state such as the package
;;; system state, i/o system state, readtable state (etc) is
;;; state-changing-expression-p.  However, consing by itself is not
;;; considered state-changing since the internal state of the storage
;;; allocator is supposed to be semantically transparent; see
;;; nonconsing-expression-p.

(defun state-changing-statement-p (s)
  (if (expression-p s)
      (state-changing-expression-p s)
      (or (funcall (statement-handler-state-changing-function
		    (handler s))
		   s)
	  (some #'state-changing-statement-p (substatements s)))))

;;; Usually we want to access all of these slots, not from the
;;; target-info slot, but directly from the statement. To do this,
;;; for each accessor function target-info-<foo>, we will define
;;; another function or macro, called either target-form-<foo> or just <foo>,
;;; which takes a form, rather than a target-info struct, as an argument.

(defmacro expression-handler (statement)
  `(target-info-expression-handler (target-info ,statement)))

(defmacro enclosing-statement (statement)
  `(target-info-enclosing-statement (target-info ,statement)))

(defun lvalue-p (statement)
  (and (target-form-p statement)
       (target-info-lvalue-p (target-info statement))))

(defun set-lvalue-p (statement value)
  (if (target-form-p statement)
      (setf (target-info-lvalue-p (target-info statement)) value)
      (error "Attempt to set lvalue for non-statement ~A" statement)))

(defsetf lvalue-p set-lvalue-p)
       
(defmacro live-variables (statement)
  `(target-info-live-variables (target-info ,statement)))

(defun clean-target-info (info)
  (setf (target-info-type-info info) nil
	(target-info-in info) nil
	(target-info-out info) nil
	(target-info-enclosing-statement info) nil
	(target-info-live-variables info) nil)
  (free-target-info info)
  nil)

(defun partly-clean-target-info (info)
  (setf (target-info-in info) nil
	(target-info-out info) nil
	(target-info-enclosing-statement info) nil
	(target-info-live-variables info) nil)
  info)

(defun clean-target-form (form)
  (clean-target-info (car form)))

;;; Most target-info structs can be deallocated when they have
;;; been emitted.  Constants are still in use, though,
;;; since they are still in some function-record, and will be used by
;;; generate-function-record-per-file-names during init-function processing.
;;; So don't deallocate these.

(defun maybe-deallocate-target-form (form)
  (let ((info (car form)))
    (if (eq (target-info-type info) 'constant)
	(partly-clean-target-info info)
	(clean-target-info info))))

(define-forward-variable-reference *context*)

;;; A performance optimization for translation

(defvar *throw-if-statements-are-generated-p* nil)

(defmacro with-statements-excluded (&body forms)
  `(if *throw-if-statements-are-generated-p*
       (progn ,@forms)
       (catch 'exclude-statements
	 (let ((*throw-if-statements-are-generated-p* t))
	   ,@forms))))

(defmacro with-statements-allowed (&body forms)
  `(let ((*throw-if-statements-are-generated-p* nil))
     ,@forms))

(defun make-target-form-internal (type-info args)
  (when (and *throw-if-statements-are-generated-p*
	     (not (type-info-expression-handler type-info)))
    (throw 'exclude-statements nil))
  (when (eq *context* ':result-type-only)
    (return-from make-target-form-internal t))
  (let* ((info (make-target-info type-info))
	 (initializer
	  (statement-handler-initializer (target-info-handler info)))
	 (form (cons info args)))
    (if initializer
	(funcall initializer form)
	form)))

(defmacro make-target-form (type &rest args)
  (if (constantp type)
      (let ((variable (type-info-variable (eval type))))
	`(make-target-form-internal 
	   (locally (declare (special ,variable)) ,variable)
	   (list ,@args)))
      `(make-target-form-internal (get-type-info ,type) (list ,@args))))

(defmacro apply-make-target-form (type &rest args)
  (if (constantp type)
      (let ((variable (type-info-variable (eval type))))
	`(make-target-form-internal
	   (locally (declare (special ,variable)) ,variable)
	   (list* ,@args)))
      `(make-target-form-internal (get-type-info ,type) (list* ,@args))))

(defun copy-target-form (form)
  (make-target-form-internal (target-info-type-info (target-info form))
			     (cdr form)))

;;; Replace the target form old with the target form new. Assumes that
;;; enclosing-statement has already been set up, and maintains it.
;;; Does not maintain control flow or data flow information.

(defun target-form-replace (old new)
  (let ((encloser (enclosing-statement old)))
    (target-form-replace-aux old new encloser)
    #||(clean-target-form old)||#
    (record-encloser new encloser)))

;;; Target-form-replace-aux is used when enclosing-statement information
;;; has not been set up, and need not be maintained.
(defun target-form-replace-aux (old new encloser)
  (if (function-record-p encloser)
      (setf (function-record-statements encloser)
	    (nsubstitute new old (function-record-statements encloser)))
      (funcall (statement-handler-replace-function (handler encloser))
	       new old encloser)))

;;; Is a given expression in a context where the returned value is utilized?
(defun setq-in-value-context-p (expression)
  (let ((encloser (enclosing-statement expression)))
    (and (not (function-record-p encloser))
	 (member expression
		 (funcall
		  (statement-handler-value-subforms-function
		   (handler encloser))
		  encloser)))))

;;; Can the given expression be legitimately replaced by a statement?
(defun statement-context-p (expression)
  (let ((encloser (enclosing-statement expression)))
    (or (function-record-p encloser)
	(and
	 (not (expression-p encloser))
	 (member expression
		 (funcall
		  (statement-handler-statement-subforms-function
		   (handler encloser))
		  encloser))))))

;;; Remove a form from the containing target-language expression. Should
;;; Only be called on expressions for which value-context-p returns nil
(defun remove-form (s)
  (let ((encloser (enclosing-statement s)))
    (if (function-record-p encloser)
	(progn
	  (setf (function-record-statements encloser)
		(delete s (function-record-statements encloser)))
	  #||(clean-target-form s)||#)
	(case (target-form-type encloser)
	  ((comma-operator with-lexical-bindings with-special-binding
			     compound-statement)
	   (setq encloser (delete s encloser))
	   #||(clean-target-form s)||#)
	  ((preprocessor-conditional)
	   (setf (third encloser)
		 (mapcar #'(lambda (list) (delete s list))
			 (third encloser)))
	   #||(clean-target-form s)||#)
	  (otherwise
	   (target-form-replace s (make-target-form 'null-statement)))))))

;;; Use this predicate to check for equality of target forms or lists
;;; of target forms, in place
;;; of equal.
;;; This does the same thing that equal would have done on old
;;; format target language, (where target-info structs are replaced
;;; by symbols); whether this is the right thing or not for your
;;; application is your problem.
(defun target-form-equal (s1 s2)
  (cond ((or (target-info-p s1)
	     (target-info-p s2))
	 (and (target-info-p s1)
	      (target-info-p s2)
	      (eq (target-info-type s1) (target-info-type s2))))
	((and (consp s1) (consp s2))
	 (and (target-form-equal (car s1) (car s2))
	      (target-form-equal (cdr s1) (cdr s2))))
	(t (equal s1 s2))))

;see match-argvalues-to-parameters in util.lisp
(defun tutil::match-argvalues-to-parameters-internal (construct)
  (if (or (eq (target-form-type construct) 'initial-symbol)
	  (eq (target-form-type construct) 'constant))
      (values (cadr construct) t)
      (values nil nil)))

;;; **** Formerly in record.lisp
;;; This function builds a local-variable expression.  It notes whether
;;; or not the reference to the variable is closed.
;;; *** I am not 100% sure we are always using this function when necessary,
;;; *** instead of just consing up the expression directly.  This function
;;; *** should *not* be used when consing up a local-variable expression
;;; *** to pass as an l-value context.  (Just making a context doesn't count
;;; *** as a reference, and contexts are never passed through function
;;; *** boundaries anyway.)

(defun local-variable-reference (record &aux classification)
  (when (eq *context* ':result-type-only)
    (return-from local-variable-reference t))
  (unless (or (eq (variable-record-in-function record) *current-function*)
	      (eq (setf classification
			(function-record-classification *current-function*))
		  :ignore))
    (setf (variable-record-actual-closed-p record) t))
  (if (eq classification :ignore)
      (unless (variable-record-referenced-p record)
	(setf (variable-record-referenced-p record) :ignore))
      (setf (variable-record-referenced-p record) t))
  (make-target-form 'local-variable record))


;;; This function is similar but is for an assignment reference.
;;; *** Again, I am not 100% sure we are calling this function every time
;;; *** it is necessary to do so.  The idea is that it is supposed to be
;;; *** used only for explicit assignments, not for initializations.

(defun local-variable-assignment (record)
  (when (eq *context* ':result-type-only)
    (return-from local-variable-assignment t))
  (unless (or (eq (variable-record-in-function record) *current-function*)
	      (eq (function-record-classification *current-function*) :ignore))
    (setf (variable-record-actual-closed-p record) t))
  (pushnew *current-function* (variable-record-modified-p record))
  (make-target-form 'local-variable record))


;;; Functions for use as define-statement arguments (statement-handler
;;; slot fillers)

;;; substatements function for statements with no substatements.
(defun constantly-nil (&rest args)
  (declare (ignore args))
  nil)

;;; Initializers. Note that if one is present, make-target-form will return
;;; whatever the initializer returns, so it should return its argument
;;; except in unusual circumstances.
(defun labeled-init (s)
  (let ((label (cadr s)))
    (unless (or (numberp label) (characterp label))
      (setf (get label 'labeled-statement) s)))
  s)

;;; Return an expression when possible instead of a statement.
;;; Note that we return a statement when there are no variables being
;;; bound at all. This is so that mung-closed-arguments will always
;;; have a with-lexical-bindings target form to mung. (the form it gets is
;;; created via a call to (make-target-form 'with-lexical-bindings foo ...)
;;; where foo is a list of variables, none of which are compiler-generated
;;; temps, but foo is possibly a null list.
;;;
;;; This is a crock; the right thing is to fix mung-closed-arguments to
;;; be more flexible, or (better) to do more of the handling of closed
;;; variables in target language, instead of the emitter, so that things
;;; like mung-closed-arguments don't need to exist.

(defun lexical-bindings-init (s)
  (if (and (cadr s)
	   (every #'variable-record-compiler-generated-temp-p (cadr s))
	   (null (cdddr s)))
      (progn
	(appendf (function-record-local-variables *current-function*)
		 (cadr s))
	(caddr s))
      (dolist (variable (cadr s) s)
	(setf (variable-record-binder variable) s))))

(defun call-init (s)
  (when (function-information-value (cadr s) 'tx:nonrelocating)
    (setf (target-info-nonrelocating (car s)) t))
  (when (function-information-value (cadr s) 'tx:non-state-changing)
    (setf (target-info-state-changing (car s)) nil))
  (when (function-information-value (cadr s) 'tx:non-state-using)
    (setf (target-info-state-using (car s)) nil))
  s)

(defun c-call-init (s)
  (setf (target-info-nonrelocating (car s)) nil)
  (setf (target-info-state-changing (car s)) t)
  (setf (target-info-state-using (car s)) t)
  s)

;;; The cddr of a preprocessor conditional form is a list of lists
;;; of statements.
(defun preprocessor-conditional-substitute (new old s)
  (mapc #'(lambda (sequence) (nsubstitute new old sequence)) (cddr s)))

;;; Control Flow stuff
;;; 
;;; Entries in the flow graph are either target statements, or structures
;;; of type flow-node, call-entry, or call-exit. We will collectively call
;;; such objects "Nodes"

;;; Calling do-flow on a statement causes the in and out field of the
;;; target record of the statement and all its executable substatements.
;;; It returns two values, a node and a list of nodes.
;;; The first is the first executable statement in the form; the
;;; second is a list of nodes that may transfer control to the
;;; immediately following statement.

(defun do-flow (s)
  (if s
      (funcall (statement-flow-function s) s)
      (null-flow)))

(defun print-flow-node (record stream depth)
  (declare (ignore depth #-lucid record))
  (format stream "#<flow-node~@[ ~X~]>"
	  #-(and lucid (not translating)) nil
	  #+(and lucid (not translating)) (lucid::%pointer record)))

(defstruct (flow-node (:print-function print-flow-node)
		      (:include basic-flow-node))
  (corresponding-entry nil)     ; If this is a flow node whose out
                                ; goes to a call-exit node, this is a node
                                ; (not necessarily a flow-node; any kind
                                ; of flow-graph node is possible here)
                                ; that is the on the out or maybe-out of the
                                ; corresponding call-entry node. Otherwise,
                                ; this is nil.
)

(defun print-call-entry (record stream depth)
  (declare (ignore depth #-lucid record))
  (format stream "#<call-entry~@[ ~X~]>"
	  #-(and lucid (not translating)) nil
	  #+(and lucid (not translating)) (lucid::%pointer record)))

(defstruct (call-entry (:print-function print-call-entry)
		       (:include basic-flow-node))
  ;; Nodes that might have just been executed, not including the
  ;; corresponding call-exit node
  ;;(in			nil)    
  ;; Corresponding call-exit node (special type of in node)
  (call-exit		nil)
  ;; Flow out to argument expressions that are guaranteed to be evaluated
  ;; at least once
  ;;(out		nil)
  ;; Flow out to arguments that may not be evaluated
  (maybe-out            nil)
  ;;(live-variables     nil)    ; Never used, but needed so that
  ;;			        ; Data flow will never infinite loop. Sigh.
)

(defun print-call-exit (record stream depth)
  (declare (ignore depth #-lucid record))
  (format stream "#<call-exit~@[ ~X~]>"
	  #-(and lucid (not translating)) nil
	  #+(and lucid (not translating)) (lucid::%pointer record)))

(defstruct (call-exit (:print-function print-call-exit)
		      (:include basic-flow-node))  
  ;; Flow in from argument expressions that are guaranteed to be evaluated
  ;; at least once
  ;;(in			nil)
  ;; Flow in from arguments that may not be evaluated
  (maybe-in             nil)
  ;; Corresponding call-entry node (special type of out node)
  (call-entry		nil)
  ;; Flow nodes that might be executed next, not including the
  ;; corresponding call-entry node
  ;;(out			nil)
  ;;(live-variables       nil)    ; Never used, but needed so that
  ;;                              ; Data flow will never infinite loop. Sigh. 
)

;;; These three specials must be bound to flow-nodes during flow-analysis
(defvar *function-entry*)
(defvar *function-exit*)
(defvar *nonlocal-entries*)		; List of places a throw might go.

;;; During flow analysis, this holds the innermost enclosing switch
;;; statement
(defvar *switch-expression-outs*)

    
;;; (Misplaced comment)
;;; Note that when we call
;;; side-effect-free and the like on *statements*, we
;;; are considering them as flow-graph
;;; nodes, not as statements that "contain" other statements.
;;; This means that side-effecting-expression-p and side-effecting-statement-p
;;; may return different things on the same statement.

;;; Bound during flow analysis, to the place where a break would transfer
;;; control if encountered in the current form or any of its subforms;
;;; that is, set to a flow-node that immediately follows the
;;; innermost enclosing do-while-statement, while-statement, forever-statement,
;;; for-statement, or switch-statement.
(defvar *break-destination*)

;;; These are generic setf'able functions on nodes

(defmacro flow-out (node)
  (once-only (node)
    `(basic-flow-node-out (if (consp ,node)
			      (target-info ,node)
			      ,node))))

(defmacro set-flow-out (node value)
  `(setf (basic-flow-node-out (if (consp ,node)
			          (target-info ,node)
			          ,node))
         ,value))

(defsetf flow-out set-flow-out)

(defmacro flow-in (node)
  (once-only (node)
    `(basic-flow-node-in (if (consp ,node)
			     (target-info ,node)
			     ,node))))

(defmacro set-flow-in (node value)
  `(setf (basic-flow-node-in (if (consp ,node)
			         (target-info ,node)
			         ,node))
         ,value))

(defsetf flow-in set-flow-in)
			 
;;; Record the information that there is a possible flow path from
;;; Node from to node to.

(defmacro record-flow (from to)
  (once-only (from to)
    `(progn
       (push ,from (flow-in ,to))
       (push ,to (flow-out ,from)))))

(defmacro record-flows (froms to)
  (once-only (to)
    `(dolist (from ,froms)
       (record-flow from ,to))))


;;; Flow functions return two values, both lists; the places to which incoming
;;; flow should be attached, and the places to which outgoing
;;; flow should be attached.

;;; Helper function for all flow functions that do straight-line flow
;;; through a list of substatements

(defun do-straight-flow (statements)
  (if statements
      (multiple-value-bind (in current-outs)
	  (do-flow (car statements))
	(dolist (statement (cdr statements))
	  (multiple-value-bind (statement-in statement-outs)
	      (do-flow statement)
	    (record-flows current-outs statement-in)
	    (setq current-outs statement-outs)))
	(values in current-outs))
      (null-flow)))

;;; Lots of target statements have a flow that either does or does not
;;; include the statement itself, then does straight line flow through
;;; a sequence of imbedded statements

(defun substatements-flow (s)
  (do-straight-flow (substatements s)))

(defun substatements-then-self-flow (s)
  (let ((statements (substatements s)))
    (multiple-value-bind (in outs)
	(do-straight-flow statements)
      (record-flows outs s)
      (values in (list s)))))

(defun self-then-substatements-flow (s)
  (let ((statements (substatements s)))
    (multiple-value-bind (in outs)
	(do-straight-flow statements)
      (record-flow s in)
      (values s outs))))

(defun flow-straight-thru (s)
  (values s (list s)))

;;; When do-flow is called on nil (which can happen, since target forms
;;; like for-statement may have nil in place of one of their
;;; expressions), we create a flow-node, and have the flow go straight
;;; through it.

(defun null-flow (&optional s)
  (declare (ignore s))
  (flow-straight-thru (make-flow-node)))

(defun substatement-self-and-return (s)
  (let ((substatement (car (substatements s))))
    (multiple-value-bind (in outs)
	(do-flow substatement)
      (record-flows outs s)
      (record-flow s *function-exit*)
      (values in nil))))

(defun substatement-and-return  (s)
  (let ((substatement (car (substatements s))))
    (multiple-value-bind (in outs)
	(do-flow substatement)
      (record-flows outs *function-exit*)
      (values in nil))))

;;; Special flows for special statements

(defun values-assign-flow (s)
  (let ((entry (make-call-entry))
	(exit (make-call-exit)))
    (setf (call-entry-call-exit entry) exit)
    (setf (call-exit-call-entry exit) entry)
    (record-flow exit s)
    (dolist (arg (cdr s))
      (multiple-value-bind (in outs)
	  (do-flow arg)
	(record-flow entry in)
	(let ((exit-node (make-flow-node)))
	  (setf (flow-node-corresponding-entry exit-node) in)
	  (record-flows outs exit-node)
	  (record-flow exit-node exit))))
    (values entry (list s))))

(defun special-binding-flow (s)
  (multiple-value-bind (in outs)
      ;; All but the init-expression
      (do-straight-flow (cdr (substatements s)))
    (let  ((init (fourth s)))
      (multiple-value-bind (init-in init-outs)
	  (do-flow init)
	(record-flows init-outs s)
	(record-flow  s in)
	(values init-in outs)))))
	
;;; Note that labeled statement is just substatement-and-return, with
;;; accessor #'caddr; that way the label becomes dead code if there are
;;; no branches to it.
(defun goto-flow (s)
  (record-flow s (label-to-statement (cadr s)))
  (values s nil))

(defun label-to-statement (label)
  (get label 'labeled-statement))

(defun switch-flow (s)
  (multiple-value-bind (exp-in *switch-expression-outs*)
	(do-flow (cadr s))
    (let ((*break-destination* (make-flow-node)))
      (multiple-value-bind (statement-in statement-outs)
	  (do-flow (caddr s))
	(declare (ignore statement-in))
	(record-flows statement-outs *break-destination*)
	(values exp-in (list *break-destination*))))))

;;; We arrange for the flow from code that falls through the
;;; label to skip the label statement, so that if there are no
;;; branches to the label, it can be eliminated.
(defun labeled-flow (s)
  (multiple-value-bind (in outs)
      (do-flow (caddr s))
    (record-flow s in)
    ;; If this is a switch label, come here from the switch statement
    (when (let ((label (cadr s)))
	    (or (integerp label)
		(characterp label)
		(eq label :default)))
      (record-flows *switch-expression-outs* s))
    (values in outs)))

(defun break-flow (s)
  (record-flow s *break-destination*)
  (values s nil))

;;; Used for call, variadic-call, c-call, and variadic-call-generic.
;;; call-generic is different, since it guarantees left-to-right evaluation
(defun call-flow-internal (s accessorp arglist &optional arginfolist)
  (let ((entry (make-call-entry))
	(exit (make-call-exit)))
    (setf (call-entry-call-exit entry) exit)
    (setf (call-exit-call-entry exit) entry)
    (unless accessorp
      (dolist (catch *nonlocal-entries*)
	(record-flow s catch))
      (record-flow s *function-exit*))
    (record-flow exit s)
    (let ((rest-p nil))
      (do* ((arglist arglist (cdr arglist))
	    (arg (car arglist) (car arglist))
	    (arginfolist
	     arginfolist
	     (if rest-p
		 arginfolist
		 (cdr arginfolist))))
	   ((null arglist))
	(when (and arginfolist (eq (car arginfolist) '&rest))
	  (setq rest-p t)
	  (setq arginfolist (cdr arginfolist)))
	(let ((nonstandard-arg (and arginfolist
				    (cadar arginfolist))))
	  (multiple-value-bind (in outs)
	      (do-flow arg)
	    (if nonstandard-arg
		(progn
		  (push entry (flow-in in))
		  (push in (call-entry-maybe-out entry)))
		(record-flow entry in))
	    (let ((exit-node (make-flow-node)))
	      (setf (flow-node-corresponding-entry exit-node) in)
	      (record-flows outs exit-node)
	      (if nonstandard-arg
		  (progn
		    (push exit (flow-out exit-node))
		    (push exit-node (call-exit-maybe-in exit)))
		  (record-flow exit-node exit)))))))
    (values entry (list s))))

(defun call-flow (s &optional accessorp)
  (call-flow-internal 
   s accessorp (cddr s) 
   (let ((descriptor (defined-as-function (second s))))
     (and (function-descriptor-foreign-protocol descriptor)
	  (foreign-function-descriptor-foreign-arguments descriptor)))))

;;; We assume that accessor functions do not throw, but always exit
;;; normally.
(defun accessor-call-flow (s)
  (call-flow s t))

(defun call-generic-flow (s)
  (multiple-value-bind (in outs)
      (do-straight-flow (substatements s))
    (record-flows outs s)
    (dolist (catch *nonlocal-entries*)
      (record-flow s catch))
    (record-flow s *function-exit*)
    (values in (list s))))

(defun c-call-flow (s)
  (call-flow-internal s nil (cdr s) nil))
;;; Far from clear what is correct here. The issue is what sorts
;;; of c-lines we consider legal; is "continue;" a legal c-lines,
;;; for example? For now, we assume that the C-code has a single entry
;;; and exit.

(defun c-lines-flow (s)
  (values s (list s)))

;;; The preprocessor conditional itself is not actually executable, but
;;; we use it as a flow node, so that this form, like all others, has
;;; a single entry point.
(defun preprocessor-conditional-flow (s)
  (let ((outs nil))
    (dolist (statement-list (caddr s))
      (multiple-value-bind (list-in list-outs)
	  (do-straight-flow statement-list)
	(record-flow s list-in)
	(setq outs (append list-outs outs))))
    (values s outs)))

;;; Also works for conditional-operator!
(defun if-flow (s)
  (let ((test (cadr s))
	(then (caddr s))
	(else (cadddr s)))
    (multiple-value-bind (test-in test-outs)
	(do-flow test)
      (multiple-value-bind (then-in then-outs)
	  (do-flow then)
	(record-flows test-outs then-in)
	(if else
	    (multiple-value-bind (else-in else-outs)
		(do-flow else)
	      (record-flows test-outs else-in)
	      (values test-in (append then-outs else-outs)))
	    (values test-in (append test-outs then-outs)))))))

;;; The catch or unwind-protect statement itself in the next two functions
;;; is used to represent the
;;; point immediately after the longjmp has been executed. This is
;;; the point at which an automatic nonvolatile variable set after
;;; the setjmp may have undefined value.

;;; Note that this is conservative for unwind-protect; it's actually
;;; OK for the variable to be live at this point, as long as it
;;; isn't actually accessed withing the cleanup form.

;;; Should work for unwind-protect as well
;;; No; unwind-protect is different, since after the protected form is
;;; executed, we might do a rethrow.

(defun catch-flow (s)
  (let ((tag (third s))
	(body (fourth s))
	(catch-statement (fifth s)))
    (multiple-value-bind (tag-in tag-outs)
	(do-flow tag)
      (multiple-value-bind (body-in body-outs)
	  (let ((*nonlocal-entries* (cons s *nonlocal-entries*)))
	    (do-flow body))
	(record-flows tag-outs body-in)
	(if catch-statement
	    (multiple-value-bind (catch-in catch-outs)
		(do-flow catch-statement)
	      (record-flow s catch-in)
	      (values tag-in (append catch-outs body-outs)))
	    (values tag-in (cons s body-outs)))))))

(defun unwind-flow (s)
  (let ((body (third s))
	(protected (fourth s)))
    (multiple-value-bind (body-in body-outs)
	  (let ((*nonlocal-entries* (list s)))
	    (do-flow body))
      (multiple-value-bind (protected-in protected-outs)
	  (do-flow protected)
	(record-flows body-outs protected-in)
	(record-flow s protected-in)
	(dolist (catch *nonlocal-entries*)
	  (record-flows protected-outs catch))
	(values body-in protected-outs)))))


;;; Do we need a progv flow? Depends on whether symbols, then values, then
;;; body is guaranteed, which it probably is. We need one anyway, to indicate
;;; that the order is symbols, then values, then binding, then body.

(defun progv-flow (s)
  (multiple-value-bind (symbols-in symbols-outs)
      (do-flow (third s))
    (multiple-value-bind (values-in values-outs)
	(do-flow (fourth s))
      (record-flows symbols-outs values-in)
      (record-flows  values-outs s))
    (multiple-value-bind (body-in body-outs)
	(do-flow (fifth s))
      (record-flow s body-in)
      (values symbols-in body-outs))))

(defun forever-flow (s)
  (let ((*break-destination* (make-flow-node)))
    (multiple-value-bind (in outs)
	(do-flow (cadr s))
      (record-flows outs in)
      (values in (list *break-destination*)))))

(defun for-flow (s)
  ;; Do flow on finally-statement before binding *break-destination*
  (multiple-value-bind (finally-in finally-outs)
      (do-flow (sixth s))
    (let ((init (second s))
	  (test (third s))
	  (step (fourth s))
	  (body (fifth s))
	  (finally (sixth s))
	  (*break-destination* (make-flow-node)))
      ;; Already calculated flow for finally
      (declare (ignore finally))
      (multiple-value-bind (init-in init-outs)
	  (do-flow init)
	(multiple-value-bind (test-in test-outs)
	    (do-flow test)
	  (multiple-value-bind (step-in step-outs)
	      (do-flow step)
	    (multiple-value-bind (body-in body-outs)
		(do-flow body)
	      (record-flows init-outs test-in)
	      (record-flows test-outs body-in)
	      (record-flows body-outs step-in)
	      (record-flows step-outs test-in)
	      (record-flows test-outs *break-destination*)
	      (record-flow  *break-destination* finally-in)
	      (values init-in finally-outs))))))))

;;; Used for both while and do-while statements    
(defun while-flow (s test-first)
  (let ((test (if test-first (second s) (third s)))
	(body (if test-first (third s) (second s)))
	(*break-destination* (make-flow-node)))
    (multiple-value-bind (test-in test-outs)
	(do-flow test)
      (multiple-value-bind (body-in body-outs)
	  (do-flow body)
	(record-flows test-outs body-in)
	(record-flows body-outs test-in)
	(record-flows test-outs *break-destination*)
	(values (if test-first test-in body-in) (list *break-destination*))))))

;;; May need to do flow-analysis on the embedded function here; may not.
;;; The real question is who invokes the entire optimization phase
;;; (compute closed-over variables, flow analysis, temp-elimination),
;;; and how to arrange that this happens for embedded functions.
;;; defun function-definition-flow 

;;; Like call-flow.

(defun setq-flow (s)
  (let ((entry (make-call-entry))
	(exit (make-call-exit))
	(lvalue (second s))
	(rvalue (third s))
        (lvalue-out-node (make-flow-node))
        (rvalue-out-node (make-flow-node)))
    (setf (call-entry-call-exit entry) exit)
    (setf (call-exit-call-entry exit) entry)
    (multiple-value-bind (lvalue-in lvalue-outs)
	(do-flow lvalue)
      (multiple-value-bind (rvalue-in rvalue-outs)
	  (do-flow rvalue)
	(record-flow entry lvalue-in)
	(record-flow entry rvalue-in)
	(record-flows lvalue-outs lvalue-out-node)
	(record-flows rvalue-outs rvalue-out-node)
	(record-flow lvalue-out-node exit)
	(record-flow rvalue-out-node exit)
	(setf (flow-node-corresponding-entry lvalue-out-node) lvalue-in)
	(setf (flow-node-corresponding-entry rvalue-out-node) rvalue-in)
	(record-flow exit s)
	(values entry (list s))))))

(defun and-or-or-flow (s)
  (if s
      (let ((outs nil))
	(multiple-value-bind (in current-outs)
	    (do-flow (cadr s))
	  (setq outs current-outs)
	  (dolist (statement (cddr s))
	    (multiple-value-bind (statement-in statement-outs)
		(do-flow statement)
	      (record-flows current-outs statement-in)
	      (setq current-outs statement-outs)
	      (setq outs (append statement-outs outs))))
	  (values in outs)))
      (null-flow)))

(defun simple-lvalue-flow (s)
  (values s (list s)))

(defun expression-handlers-for (expression &optional (errorp t))
  (or (expression-handler expression)
      (when errorp
	(error "~S is not an expression." expression))))
  
(defstruct (expression-handler
	     (:predicate nil)
	     (:copier nil)
	     (:print-function print-expression-handler))
  name
  (needs-values    (required-keyword :needs-values))
  (state-changing  (required-keyword :state-changing))
  (state-using     (required-keyword :state-using))
  (nonrelocating   (required-keyword :nonrelocating))
  (nonrelocatable  (required-keyword :nonrelocatable))
  (values-changing (required-keyword :values-changing))
  )  

(defun print-expression-handler (object stream depth)
  (declare (ignore depth))
  (format stream "#<Expression-handler ~S>"
	  (expression-handler-name object)))

;;; Is a statement really an expression?

(defun expression-p (statement)
  (and (expression-handlers-for statement nil) t))

(defun relocating-p (s)
  (when s
    (if (relocating-statement-p s)
	s
	(dolist (ss (substatements s) nil)
	  (when (relocating-p ss)
	    (return-from relocating-p ss))))))

;;; Does an expression need to be wrapped with a call to VALUES in order
;;; to ensure that it sets the multiple value count explicitly?  This is
;;; generally true of everything except calls to functions using the Lisp
;;; call protocol and the VALUES target-language expression.

(defun needs-explicit-values (expression)
  (funcall (expression-handler-needs-values
	        (expression-handlers-for expression))
	   expression))


;;; Does an expression (potentially) change any state information?
;;; If not, this might permit other expressions that would normally
;;; be evaluated in sequence with this expression to be evaluated in
;;; parallel with it.  It also permits the expression to be removed
;;; entirely in contexts where its return values are ignored.
;;;
;;; Any expression that performs destructive updates to its arguments
;;; or that has side-effects such as setting or modifying global 
;;; variables or changing internal state such as the package
;;; system state, i/o system state, readtable state (etc) is
;;; state-changing-expression-p.  However, consing by itself is not
;;; considered state-changing since the internal state of the storage
;;; allocator is supposed to be semantically transparent; see
;;; nonconsing-expression-p.

(defun state-changing-expression-p (expression)
  (funcall (expression-handler-state-changing
	    (expression-handlers-for expression))
	   expression))


;;; Does an expression (potentially) depend on any state information?
;;; If not, this might permit other expressions that would normally
;;; be evaluated in sequence with this expression to be evaluated in
;;; parallel with it.
;;;
;;; Any expression that examines components of its arguments (such as
;;; primitive data structure accessors), references global variables,
;;; uses internal state such as the package system state, i/o system
;;; state, readtable state (etc) is state-using-expression-p.

(defun state-using-expression-p (expression)
  (funcall (expression-handler-state-using
	    (expression-handlers-for expression))
	   expression))


;;; Does an expression (potentially) overwrite the multiple-values storage?

(defun values-changing-expression-p (expression)
  (funcall (expression-handler-values-changing
	    (expression-handlers-for expression))
	   expression))


;;; Is an expression guaranteed not to cons?

;;; This function used to be used for
;;; GC-protection analysis, though the new function nonrelocating-expression-p
;;; is the right one to use for this purpose.

;;; This was removed, since it was the easiest way to implement
;;; nonrelocating-expression-p. It could be reimplemented if
;;; it was actually required at some point (for example, in
;;; order to determine whether to temp arguments to CONS
;;; if we get smarter about when to temp arguments).


(defun nonconsing-expression-p (expression)
  (declare (ignore expression))
  (error "Are you sure you want to use nonconsing-expression-p and ~
    not nonrelocating-expression-p? If so, you'll have to implement it"))

;;; Is an expression guaranteed not to GC?  This function is used for
;;; GC-protection analysis.

;;; Calls to this should generally first check if the current function
;;; is declared nonrelocating, and just return t in that case.

(defun nonrelocating-expression-p (expression)
  (funcall (expression-handler-nonrelocating
	        (expression-handlers-for expression))
	   expression))

;;; Is the value of the expression an object that cannot be relocated
;;; by the garbage collector?  This function is used for GC-protection
;;; analysis.

(defun nonrelocatable-expression-p (expression)
  (funcall (expression-handler-nonrelocatable
	        (expression-handlers-for expression))
	   expression))



;;; In some value-returning contexts, it's desirable to treat a list 
;;; of expression statements as a comma operator instead of as a 
;;; compound statement.  Also treat assignments as expressions instead
;;; of statements.  This function does it if it can be done.

;;; This could be improved; other commaize-able expressions include
;;; compound statements, each statement of which is comma-izeable,
;;; and (with-lexical-bindings <whatever> &rest comma-ize-able statement),
;;; though this case needs a slightly different interface, so it can
;;; put these lexical bindings somewhere else.

;;; However, since even mild amounts of comma-ization causes many
;;; broken C compilers to die horribly, it's not clear that making
;;; this function smarter is a win; we may want to make it dumber,
;;; instead, or provide a switch that allows the user to make
;;; it dumber.

(define-forward-variable-reference *avoid-comma-operator*)

(defun comma-ize (statements value type temps
			     &optional (value-from-statements-p t))
  (when value-from-statements-p
    (multiple-value-setq (statements value type temps)
      (expression-ize statements value type temps)))
  (when (and (not *avoid-comma-operator*)
	     value
	     statements
	     (every #'expression-p statements))
    (setq value (apply-make-target-form 'comma-operator
					(nreconc statements (list value)))
	  statements nil))
  (values statements value type temps))


;;; This is a more restricted version of the above, that does only the
;;; stuff with assignments and doesn't build comma-operators.

(defun expression-ize (statements value type temps)
  (when (and statements
	     (can-expression-ize-p (car statements) value))
    (setq value (pop statements)))
  (values statements value type temps))
	       

;;; A helper function for the above.

(defun can-expression-ize-p (exp value)
  (and (expression-p exp)
       (or (null value)
	   (and (eq (target-form-type exp) 'setq)
		(equal (cadr exp) value)))))


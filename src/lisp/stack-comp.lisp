;;; -*- Mode: LISP; Syntax: Common-Lisp; Base: 10; Package: AB -*-
(in-package "AB")

;;;; Module STACK-COMP

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All rights reserved. 

;;; Jim Allard and Chris Morel






;;;; Stack Evaluator Compiler




;;; The stack evaluator compiler is used to compile expressions which will be
;;; evaluated by the new stack evaluator.  Eventually, portions of this will be
;;; extended to include compiling procedure bodies, rule executions, and groups
;;; of simulator variable values.

;;; The functions in this module which may be used by other modules are
;;; compile-stack-expression-into-nodes, emit-stack-node-tree,
;;; convert-expression-into-stack-node-tree, and
;;; compile-expression-into-byte-code-body.


(declare-forward-reference most-general-primary-type function)
(declare-forward-reference truth-value-phrase-p function)
(declare-forward-reference truth-value-phrase-value function)

;;;; Generating Byte Code Bodies



(defmacro declare-instruction-for-optimizer (&rest forms)
  (declare (ignore forms))
  nil)

(defmacro declare-optimizer-stack-instruction (&rest forms)
  (declare (ignore forms))
  nil)

;;; The function `compile-function-definition-for-stack' takes a
;;; function-definition frame, a parsed expression, and a list of arguments.
;;; This function compiles the expression and returns a new byte-code-body if
;;; the compile is successful, else it returns NIL.

(defun-allowing-unwind compile-function-definition-for-stack
		       (function-name function-definition expression arguments)
  (declare (ignore function-definition))
  (let ((name-resolution-compile? expression)
	(unknown-allowed-var '|unknown-allowed|)
	(no-item-allowed-var '|no-item-allowed|)
	(byte-code-vector nil)
	(byte-codes-count nil)
	(byte-code-constants nil)
	(byte-code-body-to-return nil)
	(code-body-entry nil))
    (when name-resolution-compile?
      (with-compiler-environment
	(enter-new-code-body nil
	  (setq code-body-entry (car-of-cons lexically-visible-code-bodies))
	  (let* ((expression-bound-local-names
		   (phrase-cons
		     (phrase-cons
		       no-item-allowed-var
		       (generate-new-stack-arg-var-spot
			 0
			 'truth-value))
		     (phrase-cons
		       (phrase-cons
			 unknown-allowed-var
			 (generate-new-stack-arg-var-spot
			   1
			   'truth-value))
		       (loop for argument in arguments
			     for arg-number from (1+f (length arguments)) by -1
			     collect
			       (phrase-cons
				 argument
				 (generate-new-stack-arg-var-spot
				   arg-number 'item-or-datum))
					    using phrase-cons))))
		 (unknown-allowed
		   (compile-stack-expression-into-nodes
		     name-resolution-compile?
		     '(or datum (unknown-datum))))
		 (known-only-compile? nil)
		 (known-only-no-item-allowed-compile? nil)
		 (unknown-no-item-allowed-compile? nil))
	    (unless compiler-errors
	      (let ((inhibit-free-reference-recording t))
		;; Only record free refences in the unknown-allowed
		;; cases above.  We do not want warnings for variable
		;; references.
		(setq unknown-no-item-allowed-compile?
		      (compile-stack-expression-into-nodes
			name-resolution-compile?
			'(or datum (unknown-datum) (no-item))))
		(unless compiler-errors
		  (setq known-only-compile?
			(compile-stack-expression-into-nodes
			  name-resolution-compile?
			  'datum))
		  (when compiler-errors
		    (clear-compiler-errors)
		    (setq known-only-compile? nil))
		  (setq known-only-no-item-allowed-compile?
			(compile-stack-expression-into-nodes
			  name-resolution-compile?
			  '(or datum (no-item))))
		  (when compiler-errors
		    (clear-compiler-errors)
		    (setq known-only-no-item-allowed-compile? nil)))))
	    (unless compiler-errors
	      (let ((known-only-tag (generate-new-goto-tag))
		    (known-and-item-tag (generate-new-goto-tag))
		    (unknown-and-item-tag (generate-new-goto-tag)))
		(emit-branch-or-jump-if-not-true
		  (compile-stack-expression-into-nodes
		    unknown-allowed-var 'truth-value)
		  known-only-tag)
		;; Unknown allowed, test for no-item.
		(emit-branch-or-jump-if-not-true
		  (compile-stack-expression-into-nodes
		    no-item-allowed-var 'truth-value)
		  unknown-and-item-tag)

		;; CASE 1. Unknown and no-item allowed.
		(emit-instruction
		  'return-from-function unknown-no-item-allowed-compile?)

		;; CASE 2. Unknown allowed, no-item not allowed.
		(emit-instruction 'tag-statement unknown-and-item-tag)
		(emit-instruction 'return-from-function unknown-allowed)

		;; Known only, test for no-item.
		(emit-instruction 'tag-statement known-only-tag)
		(emit-branch-or-jump-if-not-true
		  (compile-stack-expression-into-nodes
		    no-item-allowed-var 'truth-value)
		  known-and-item-tag)

		;; CASE 3. Unknown not allowed, no-item allowed.
		(if known-only-no-item-allowed-compile?
		    (emit-instruction
		      'return-from-function known-only-no-item-allowed-compile?)
		    (emit-instruction
		      'signal-error
		      (compile-stack-expression-into-nodes
			'(quote function-can-return-unknown)
			'symbol)
		      (compile-stack-expression-into-nodes
			"This function can only be called in contexts where unknown is allowed."
			'text)))

		;; CASE 4. Unknown and no-item not allowed.
		(emit-instruction 'tag-statement known-and-item-tag)
		(if known-only-compile?
		    (emit-instruction 'return-from-function known-only-compile?)
		    (emit-instruction
		      'signal-error
		      (compile-stack-expression-into-nodes
			'(quote function-can-return-unknown)
			'symbol)
		      (compile-stack-expression-into-nodes
			"This function can only be called in contexts where unknown is allowed."
			'text)))))))
	(unless compiler-errors
	  (let ((byte-code-stream (make-byte-code-stream))
		(instructions (nreverse
				(compiler-code-body-instructions-so-far
				  (car code-body-entries-in-compilation)))))
	    (let ((lexically-visible-code-bodies
		    (generate-list-of-lexically-visible-code-bodies code-body-entry)))
	      (emit-byte-code-vector-for-procedure byte-code-stream instructions))
	    
	    (when (null compiler-errors)
	      (multiple-value-setq (byte-code-vector byte-codes-count)
		(resolve-procedure-byte-code-addresses byte-code-stream)))
	    
	    (when (null compiler-errors)
	      (setq byte-code-constants
		    (make-procedure-byte-code-constants byte-code-stream)))
	    
	    (reclaim-byte-code-stream byte-code-stream)))

	;; Did we get one?
	(cond (compiler-errors
	       (setq byte-code-body-to-return nil))
	      (t
	       (setq byte-code-body-to-return
		     (make-byte-code-body
		       byte-codes-count byte-code-vector byte-code-constants
		       nil
		       nil))))
	(when (memq function-name *built-in-functions*)
	  (compiler-warning
	    "~a is also the name of a system-defined function.  The system ~
             function will be used if ~a is called."
	    function-name function-name))
	(when byte-code-body-to-return
	  (when compiler-free-references
	    (setq compiler-free-references
		  (remove-spurious-free-references-for-function-compilation
		    compiler-free-references)))
	  (install-free-references-in-byte-code-body
	    byte-code-body-to-return compiler-free-references)))
      (analyze-compiled-items-for-consistency function-name)
      byte-code-body-to-return )))


;; This function seems to leak byte-code-vectors and byte-code-constants
;; when there are errors late in the emitting stage.  Fix someday.
;; Yeah, right.  -jra 2/4/92



;;; The function `remove-spurious-free-references-for-function-compilation' is
;;; used to remove unnecessary free-references collected during compilation of a
;;; G2 (user-defined) function-definition.

;;; The reference-list is the same format as for the variable compiler-free-
;;; references.  It is a list of elements, where each element is of the form
;;; (kind-of-free-reference . free-reference).

;;; Note that this function may destructively modify the reference-list
;;; argument, which is returned as the value of this function.  The function
;;; *does not* reclaim the dropped conses from the list because they are assumed
;;; to be phrase-conses.  (It also does some phrase-consing.)  Therefore, this
;;; function must be called in a context where phrase-consing is permitted!

(defun-simple remove-spurious-free-references-for-function-compilation
    (reference-list)
  (let ((references-to-delete nil))
    (loop for reference in reference-list
	  do
      (when (redundant-parameter-free-reference? reference reference-list)
	(phrase-push reference references-to-delete)))
    (loop for ref in references-to-delete
	  do
      (setq reference-list (delq ref reference-list 1)))
    reference-list))



;;; The function `compile-simulation-formula-for-stack' takes an expression that
;;; has already been compiled by compile-expression.  This function compiles the
;;; expression for the stack evaluator and returns a byte-code-body for a
;;; successful compile, and NIL otherwise.

;;; Note that the functions which execute simulation formulas expect the
;;; first four values of the environment vector to be as follows:
;;; element 0 - recache needed flag,
;;; element 1 - result,
;;; element 2 - number of bindings cached,
;;; element 3 - focal entity for the simulation formula, if there is one.

;;; The recache needed flag is controlled (set) by
;;; initialize-simulation-environment-vector and is only accessed by the stack
;;; evaluator.  Compile-simulation-formula-for-stack does not emit any
;;; instructions which cause the stack evaluator to change this flag.

;;; If the simulation formula has no focal entity, then the rest of the
;;; environment vector begins with element 3.

;;; If the recache needed flag is true, then only recaching of bindings is done;
;;; the expression itself is not actually evaluated.  On the other hand, if the
;;; recache needed flag is false, then only the expression, and any uncacheable
;;; bindings, are evaluated.  Recaching and evaluation are always done separately
;;; because initialize-simulation-environment-vector must compute supporting
;;; structures after recaching (see initialize-simulation-environment-vector).

;;; Note that some bindings in the top-level let form may not be cacheable.  As
;;; the top level let form is processed, bindings that are not cacheable are
;;; detected by simulation-designation-can-be-cached?  and are deferred for later
;;; compilation.  Thus, only cacheable bindings are in the code which is skipped
;;; if the recaching-needed flag is false.  Uncacheable bindings are always
;;; evaluated when the code body is stack-evaluated.

;; Consider optimizing simulation formula compiles by having two separate
;; byte code bodies for caching and execution.  This would save a stack-eval
;; branch.

(defun-allowing-unwind compile-simulation-formula-for-stack
		       (expression focus-name? focus-class-name?
				   initial-value-expression?)
  (let ((recaching-needed-var '|recache-needed|)
	(result-var-spot nil)
	(number-of-bindings-cached-var-spot nil)
	(focus-type-specification?
	  (when focus-class-name?
	    (make-class-type-specification focus-class-name?)))
	(byte-code-vector nil)
	(byte-codes-count nil)
	(byte-code-constants nil)
	(byte-code-body-to-return nil)
	(cached-bindings nil)
	(uncached-bindings nil)
	environment
	code-body-entry)
    (with-compiler-environment
      (enter-new-code-body nil
	(setq code-body-entry (car-of-cons lexically-visible-code-bodies))
	;; Make variables to hold the recaching needed flag, a variable for the
	;; final result, a variable for number of bindings cached, and a
	;; variable for the focus object.  Note that the order of the following
	;; calls to generate-new-variable-spot must be preserved for the
	;; simulator to be able to find these locations.  Also note that the
	;; caller of the recaching operation will manually set the recaching
	;; flag, so there is no need to hang on to the recaching var spot.
	(generate-new-variable-spot 'truth-value recaching-needed-var)
	(setq result-var-spot
	      (generate-new-variable-spot 'datum))
	(setq number-of-bindings-cached-var-spot
	      (generate-new-variable-spot 'number))
	(when focus-name?
	  (generate-new-variable-spot focus-type-specification? focus-name?))

	(cond
	  ((not initial-value-expression?)
	   ;; Strip off any let forms, generating variables for the bindings to
	   ;; cache, and emit instructions to recache when necessary.
	   (let ((end-of-recache-tag (generate-new-goto-tag))
		 (unknown-tag (generate-new-goto-tag)))
	     (emit-branch-or-jump-if-not-true
	       (compile-stack-expression-into-nodes
		 recaching-needed-var 'truth-value)
	       end-of-recache-tag)
	     
	     (loop while (and (consp expression) (eq (car expression) 'let))
		   do
	       (let ((binding-list (second expression))
		     (inner-expression (third expression)))
		 (loop with binding-var-spot
		       for (binding designation) in binding-list
		       do
		   (cond
		     ((simulation-designation-can-be-cached?
			designation cached-bindings uncached-bindings)
		      (phrase-push
			(phrase-list binding designation)
			cached-bindings)
		      (setq binding-var-spot
			    (generate-new-variable-spot 'item-or-datum binding))
		      (emit-instruction
			'assign-local-var
			binding-var-spot
			(compile-stack-expression-into-nodes
			  designation '(or item-or-datum (no-item)))))
		     (t
		      (setq uncached-bindings
			    (nconc uncached-bindings
				   (phrase-list (phrase-list binding designation))))
		      )))
		 (setq expression inner-expression)))

	     (emit-instruction
	       'assign-local-var
	       number-of-bindings-cached-var-spot
	       (compile-stack-expression-into-nodes 
		 (length cached-bindings) 'integer))
	     
	     ;; Done after caching.
	     (emit-instruction 'pause)
	     
	     (emit-instruction 'tag-statement end-of-recache-tag)

	     ;; Compile uncacheable designations.
	     (loop for (binding designation) in uncached-bindings
		   as binding-var-spot 
		      = (generate-new-variable-spot 'item-or-datum binding)
		   do
	       (when designation  ; may be nil for there-exists-literal
		 (emit-instruction
		   'assign-local-var
		   binding-var-spot
		   (compile-stack-expression-into-nodes
		     designation '(or item-or-datum (no-item))))))
	     
	     ;; Compile the expression, dealing appropriately with unknowns.
	     
;	     (emit-instruction
;	       'assign-local-var
;	       result-var-spot
;	       (compile-stack-expression-into-nodes
;		 expression
;		 '(or datum (unknown-datum))))

	     (emit-instruction
	       'execute-simulation-formula
	       (compile-stack-expression-into-nodes
		 expression
		 '(or datum (unknown-datum)))
	       result-var-spot
	       unknown-tag)

	     (emit-instruction 'complete-simulation-variable-evaluation t)
	     (emit-instruction 'pause)

	     (emit-instruction 'tag-statement unknown-tag)
	     (emit-instruction 'complete-simulation-variable-evaluation nil)
	     (emit-instruction 'pause)))
	  (t  ; initial value expression (no caching)

	   (let ((unknown-tag (generate-new-goto-tag)))
	     (emit-instruction
	       'execute-simulation-formula
	       (compile-stack-expression-into-nodes
		 expression
		 '(or datum (unknown-datum)))
	       result-var-spot
	       unknown-tag)

	     (emit-instruction 'complete-simulation-variable-evaluation t)
	     (emit-instruction 'pause)

	     (emit-instruction 'tag-statement unknown-tag)
	     (emit-instruction 'complete-simulation-variable-evaluation nil)
	     (emit-instruction 'pause))))

	(setq environment (compiler-code-body-environment-description
			    (current-compiler-code-body))))
      (unless compiler-errors
	(let ((byte-code-stream (make-byte-code-stream))
	      (instructions (nreverse
			      (compiler-code-body-instructions-so-far
				(car code-body-entries-in-compilation)))))
	  (let ((lexically-visible-code-bodies
		  (generate-list-of-lexically-visible-code-bodies code-body-entry)))
	    (emit-byte-code-vector-for-procedure byte-code-stream instructions))
	  
	  (when (null compiler-errors)
	    (multiple-value-setq (byte-code-vector byte-codes-count)
	      (resolve-procedure-byte-code-addresses byte-code-stream)))
	  
	  (when (null compiler-errors)
	    (setq byte-code-constants
		  (make-procedure-byte-code-constants byte-code-stream)))
	  
	  (reclaim-byte-code-stream byte-code-stream)))
      
      ;; Did we get one?
      (cond (compiler-errors
	     (setq byte-code-body-to-return nil))
	    (t
	     (setq byte-code-body-to-return
		   (make-byte-code-body
		     byte-codes-count byte-code-vector byte-code-constants
		     (convert-description-list-to-managed-array environment)
		     nil))
	           (install-free-references-in-byte-code-body
	byte-code-body-to-return compiler-free-references)))
      

      byte-code-body-to-return)))

(defun simulation-designation-can-be-cached? 
       (designation alist uncacheable-alist)
  (cond
    ((null designation)  ; let for local name in there exists expression
     nil)
    ((consp designation)
     ;; Car is either "the" or "giver-of-value".
     (when (eq (car designation) 'the)
       (let ((role (second designation))
	     (domain? (third designation)))
	 (cond
	   ((consp role)
	    ;; domain? should not be nil here
	    (if (role-can-be-cached? (car role))
		(simulation-designation-can-be-cached? 
		  domain? alist uncacheable-alist)))
	   ((null domain?)
	    ;; role should be on the alist or should be a class.
	    (or (assq role alist)
		(subclassp role 'item)))
	   ;; At this point, role is a symbol and domain? is non-nil.
	   ;; It is assumed that if the role has no role server, it is
	   ;; an attribute name, in which case it can be cached
	   ;; (or at least it is ok to attempt an evaluate-designation).
	   ((or (not (role-server-exists-p role))  ; attribute name
		(role-can-be-cached? role))
	    (simulation-designation-can-be-cached? 
	      domain? alist uncacheable-alist))
	   (t
	    ;; Role can't be cached.
	    nil)))))
    (t
     ;; If not a cons, then a domain symbol which either designates a
     ;; global kb object or a local name.  If a local name, have to 
     ;; check if bound on alist and if cacheable.
     
     (not (assq designation uncacheable-alist)))))




;;; The system variable `conclude-parent-attribute-bindings' is used during
;;; compiles of rules.  It contains a list of let style bindings which must be
;;; emitted after the rule let bindings.  Bindings will be introduced into this
;;; list when parent designations of attribute conclude references need to
;;; explicitly bind their parent frames.  The system variable
;;; `local-name-to-cached-designation-alist' contains an alist of local names in
;;; a rule to designations which were cached to produce that local name within
;;; the rule.

(def-system-variable conclude-parent-attribute-bindings stack-comp nil)

(def-system-variable local-name-to-cached-designation-alist stack-comp nil)




;;; The system variables `rule-certainty-var' and `rule-expiration-var' are
;;; bound during rule compilation.  They are initially NIL, but are set to
;;; non-null symbols when values for them are needed by conclude actions.  If
;;; the variables are present, then the execute-antecedent pseudo-instruction
;;; should emit instructions to set thier var spots.

(def-system-variable rule-certainty-var stack-comp nil)

(def-system-variable rule-expiration-var stack-comp nil)




;;; The interned symbol supply `temp-conclude-attribute-binding' is used to
;;; generate local names for concludes into attribute designations, where the
;;; conclude was referencing a local name for the attribute binding, and the
;;; domain of the attribute designation was itself something more complex than a
;;; name rooted set of attribute fetches.  This is all needed to make concludes
;;; into constant attributes.

(def-interned-symbol-supply "CONCLUDE-ATTRIBUTE-BINDING")




;;; The function `compile-rule-for-stack' takes a rule frame and a successful
;;; result of the focus compilation pass.  This function compiles the rule for
;;; the stack, modifies the rule to contain any newly generated byte code body,
;;; and returns the passed compilation, modified to contain environment vector
;;; locations within the focus compilation specifications.

(defun-allowing-unwind compile-rule-for-stack
    (rule parse-and-compilations)
  (let* ((rule-certainty-var nil)
	 (certainty-var-spot nil)
	 (rule-expiration-var nil)
	 (expiration-var-spot nil)
	 (byte-code-vector nil)
	 (byte-codes-count nil)
	 (byte-code-constants nil)
	 (byte-code-body-to-return nil)
	 (initial-environment nil)
	 (compiled-rule-body (second parse-and-compilations))
	 (context-list (cddr parse-and-compilations))
	 (universal-context (car context-list))
	 (rule-bindings-executed? nil)
	 (restart-tag nil)
	 (action-list nil)
	 (in-order? nil)
	 (context-length (length (cdr universal-context)))
	 (push-stack-frame-vars-instruction
	   (phrase-list 'allocate-stack-frame-vars 0))
	 (environment nil)
	 (environment-length nil)
	 (local-name-to-cached-designation-alist nil)
	 (conclude-parent-attribute-bindings nil)
	 (antecedent-or-bindings-could-be-unknown? nil))

    (loop for context-element in (cdr universal-context)
	  for (quantifier role binding domain?) = context-element
	  for cached-designation =
	  (if domain?
	      (phrase-list quantifier role domain?)
	      (phrase-list quantifier role))
	  for type-specification =
	  (or (type-specification-of-designation cached-designation)
	      'item-or-datum)
	  collect (phrase-list binding :type type-specification)
	    into vars using phrase-cons
	  collect (phrase-list binding cached-designation)
	    into cached-bindings using phrase-cons
	  finally
	    (setq initial-environment vars)
	    (setq local-name-to-cached-designation-alist cached-bindings))
    
    (with-compiler-environment
      (with-interned-conclude-attribute-binding-symbols 
	(enter-new-code-body initial-environment
	  (with-stack-frame-variables
	    (setq restart-tag (generate-new-goto-tag))
	    (emit-instruction 'tag-statement restart-tag)
	    (emit-already-consed-instruction push-stack-frame-vars-instruction)
	    (emit-instruction 'open-wake-up-collection)
	    ;; Emit instructions to set the non-context bindings.
	    (loop while (eq (car compiled-rule-body) 'rule-let)
		  for binding-list = (second compiled-rule-body)
		  for inner-body = (third compiled-rule-body)
		  do
	      (setq rule-bindings-executed? t)
	      (loop for (binding designation) in binding-list
		    for var-spot =
		    (generate-new-variable-spot
		      (or (type-specification-of-designation designation)
			  'item-or-datum)
		      binding)
		    do
		(when designation
		  (phrase-push
		    (phrase-list binding designation)
		    local-name-to-cached-designation-alist)
		  (let ((compiled-binding-expression
			  (compile-stack-expression-into-nodes
			    designation
			    '(or item-or-datum (unknown-datum) (no-item)))))
		    (setq antecedent-or-bindings-could-be-unknown?
			  (or antecedent-or-bindings-could-be-unknown?
			      ;; Must prove no unknown values for optimization.
			      (not (type-specification-not-subtype-p
				     '(unknown-datum)
				     (stack-node-value-type
				       compiled-binding-expression)))))
		    (emit-instruction
		      'assign-local-var
		      var-spot
		      compiled-binding-expression))))
	      (setq compiled-rule-body inner-body))
	    
	    (let* ((antecedent (second compiled-rule-body))
		   (true-tag (generate-new-goto-tag))
		   (close-rule-tag (generate-new-goto-tag))
		   (unknown-tag (generate-new-goto-tag)))
	      (setq action-list (third compiled-rule-body))
	      (setq in-order? (eq (car action-list) 'in-order))
	      (setq action-list (cdr action-list))

	      (setq action-list
		    (rewrite-conclude-actions-in-action-list
		      action-list in-order?))

	      (loop for (binding designation) in
		    conclude-parent-attribute-bindings
		    for compiled-binding-designation
			= (compile-stack-expression-into-nodes
			    designation
			    '(or (class item) (unknown-datum) (no-item)))
		    do
		(setq antecedent-or-bindings-could-be-unknown?
		      (or antecedent-or-bindings-could-be-unknown?
			  ;; Must prove no unknown values for optimization.
			  (not (type-specification-not-subtype-p
				 '(unknown-datum)
				 (stack-node-value-type
				   compiled-binding-designation)))))
		(emit-instruction
		  'assign-local-var
		  (generate-new-variable-spot
		    (or (type-specification-of-designation designation)
			'(class item))
		    binding)
		  compiled-binding-designation))
	      
	      (when (and rule-bindings-executed?
			 antecedent-or-bindings-could-be-unknown?)
		(let ((known-rule-let-tag (generate-new-goto-tag)))
		  (emit-instruction 'branch-if-known known-rule-let-tag)
		  (emit-branch-or-jump unknown-tag)
		  (emit-instruction 'tag-statement known-rule-let-tag)))
	      (when rule-certainty-var
		(setq certainty-var-spot
		      (generate-new-variable-spot
			'truth-value rule-certainty-var)))
	      (when rule-expiration-var
		(setq expiration-var-spot
		      (generate-new-variable-spot 'datum rule-expiration-var)))

	      (let ((compiled-logical-expression
		      (compile-stack-expression-into-nodes
			antecedent '(or truth-value (unknown-datum)))))
		(setq antecedent-or-bindings-could-be-unknown?
		      (or antecedent-or-bindings-could-be-unknown?
			  ;; Must prove no unknown values for optimization.
			  (not (type-specification-not-subtype-p
				 '(unknown-datum)
				 (stack-node-value-type
				   compiled-logical-expression)))))
		(if antecedent-or-bindings-could-be-unknown?
		    (emit-instruction
		      'execute-antecedent
		      compiled-logical-expression
		      certainty-var-spot expiration-var-spot
		      true-tag close-rule-tag unknown-tag)
		    (emit-instruction
		      'execute-antecedent
		      compiled-logical-expression
		      certainty-var-spot expiration-var-spot
		      true-tag close-rule-tag)))
	      
	      ;; Note that the wake ups are not being set when the value is false,
	      ;; and so are cleared by the close of the collection environment.
	      (when antecedent-or-bindings-could-be-unknown?
		(emit-instruction 'tag-statement unknown-tag)
		(emit-instruction 'set-wake-ups)
		(emit-instruction 'close-wake-up-collection)
		(emit-instruction 'complete-rule-instance nil)
		(emit-branch-or-jump restart-tag))
	      
	      ;; The antecedent was true, so start processing the actions.  Note
	      ;; that they are processed differently for in-order vs. simultaneous
	      ;; actions.
	      (emit-instruction 'tag-statement true-tag)
	      (cond
		(in-order?
		 ;; For in order actions, the antecedent and each action clear
		 ;; their wakeups before moving on to the next state.  This is a
		 ;; side-effect of begin-rule-actions, but it should be done
		 ;; explicitly between each in-order action.  Note that wake up
		 ;; collection shouldn't be closed until the end of the rule or a
		 ;; pause, since that performs postponed clean ups.  The following
		 ;; instruction clears wake ups from the antecedent.
		 (emit-instruction
		   'begin-activity (activity-index "begin rule actions"))
		 (emit-instruction 'begin-rule-actions)
		 (compile-in-order-actions
		   action-list expiration-var-spot
		   push-stack-frame-vars-instruction))
		(t
		 (let ((known-tag (generate-new-goto-tag))
		       (prolog-stream (make-pseudo-instruction-stream))
		       (epilog-stream (make-pseudo-instruction-stream))
		       (action-count (length action-list)))
		   (compile-simultaneous-actions
		     action-list prolog-stream epilog-stream action-count nil)
		   (merge-pseudo-instruction-stream prolog-stream)
		   (emit-instruction 'branch-if-known known-tag)
		   (emit-instruction 'set-wake-ups)
		   (emit-instruction 'close-wake-up-collection)
		   (emit-instruction 'complete-rule-instance nil)
		   (emit-branch-or-jump restart-tag)
		   (emit-instruction 'tag-statement known-tag)
		   (emit-instruction
		     'begin-activity (activity-index "begin rule actions"))
		   (emit-instruction 'begin-rule-actions)
		   (merge-pseudo-instruction-stream epilog-stream))))
	      
	      (emit-instruction 'tag-statement close-rule-tag)
	      (emit-instruction 'close-wake-up-collection)
	      (emit-instruction 'complete-rule-instance t))
	    
	    ;; Process all the contexts to add indexes to environment vector
	    ;; locations.
	    (setq context-list
		  (rewrite-contexts-for-stack-compile context-list))
	    
	    ;; Change the instruction allocating stack frame vars to hold the
	    ;; correct count.
	    (setf (second push-stack-frame-vars-instruction)
		  next-stack-frame-var-location)
	    
	    (setq environment
		  (compiler-code-body-environment-description
		    (current-compiler-code-body)))
	    (setq environment-length (length environment))
	    ))
	(unless compiler-errors
	  (let* ((byte-code-stream (make-byte-code-stream))
		 (code-body-entry (car code-body-entries-in-compilation))
		 (instructions (nreverse
				 (compiler-code-body-instructions-so-far
				   code-body-entry)))
		 (maximum-received-values
		   (compiler-code-body-maximum-received-value-count
		     code-body-entry)))
	    
	    ;; added by rdf 1/18/94
	    
	    (setq instructions
		  (optimize-procedure-instructions instructions
						   (car code-body-entries-in-compilation)))
	    (unless compiler-errors
	      (let ((lexically-visible-code-bodies
		      (generate-list-of-lexically-visible-code-bodies code-body-entry)))
	      (emit-byte-code-vector-for-procedure byte-code-stream instructions)))
	    
	    (when (null compiler-errors)
	      (multiple-value-setq (byte-code-vector byte-codes-count)
		(resolve-procedure-byte-code-addresses byte-code-stream)))
	    
	    (when (null compiler-errors)
	      (setq byte-code-constants
		    (make-procedure-byte-code-constants byte-code-stream)))
	    
	    (reclaim-byte-code-stream byte-code-stream)
	    (change-slot-value rule 'rule-maximum-received-value-count
			       maximum-received-values)
	    (change-slot-value rule 'rule-return-value-position
			       (-f environment-length maximum-received-values))))
	
	;; Did we get one?
	(cond (compiler-errors
	       (setq byte-code-body-to-return
		     (make-byte-code-body
		       4 (allocate-byte-vector 4) nil nil nil)))
	      (t
	       (setq byte-code-body-to-return
		     (make-byte-code-body
		       byte-codes-count byte-code-vector byte-code-constants
		       (convert-description-list-to-managed-array environment)
		       nil))))
	(install-free-references-in-byte-code-body
	  byte-code-body-to-return compiler-free-references)
	(change-slot-value rule 'rule-byte-code-body byte-code-body-to-return)
	(change-slot-value rule 'rule-context-length context-length)
	(change-slot-value rule 'rule-environment-length environment-length)
	
	
	(phrase-cons
	  (first parse-and-compilations)
	  (phrase-cons
	    (second parse-and-compilations)
	    context-list))))))

(defun rewrite-contexts-for-stack-compile (context-list)
  (loop with universal-context = (car context-list)
	with universal-prefix = (cdr universal-context)
	for (focus-spec . current-prefix) in context-list
	for prefix = (if (eq current-prefix 'universal-compilation)
			 universal-prefix
			 current-prefix)
	for focus-name? =
	    (if (consp focus-spec) (first focus-spec) focus-spec)
	for binding? =
	    (if (consp focus-spec) (second focus-spec) focus-spec)
;	for first-quantifier? = (caar prefix)
	for focus-index? =
	(if focus-spec
	    (lookup-or-generate-var-spot-index-for-local-name binding?))
;	    (when binding?
;	      (case first-quantifier?
;		((the-inverse-no-bind the-inverse any-inverse)
;		 (lookup-or-generate-var-spot-index-for-local-name binding?))
;		(otherwise
;		 (var-spot-index-for-local-name binding?))))
	;; An attempt was made in the code above to catch circumstances where
	;; focuses were being made to local names which hadn't been registered.
	;; However, this is exactly what happens when a chaining focus gets
	;; compiled to a reference generated by an "if for every valve v...".  A
	;; chaining focus is made for valve, which is bound to V, but that
	;; binding is only declared locally within the for every.  So, for now,
	;; I will never issue error messages about undefined bindings.  Need to
	;; talk to Andy about this.  -jra 10/10/91
	collect
	  (phrase-cons
	    (if focus-index?
		(phrase-list focus-name? binding? focus-index?)
		nil)
	    (loop for iterator in prefix
		  for quantifier = (car iterator)
		  collect
		    (case quantifier
		      ((the any)
		       (gensym-dstruct-bind ((nil role range-binding domain?)
					    iterator)
			 (record-free-references-of-role-given-domain-name
			   role domain?)
			 (nconc
			   (phrase-list
			     quantifier role range-binding domain?
			     (lookup-or-generate-var-spot-index-for-local-name range-binding))
			   (when domain?
			     (phrase-list
			       (var-spot-index-or-global-name domain?))))))
		      ((any-inverse the-inverse)
		       (gensym-dstruct-bind
			 ((nil range-binding role short-designation
			       domain-binding)
			  iterator)
			 (record-free-references-of-role-given-domain-name
			   role domain-binding)
			 (phrase-list
			   quantifier range-binding role short-designation
			   domain-binding
			   (lookup-or-generate-var-spot-index-for-local-name range-binding)
			   (if (eq short-designation domain-binding)
			       domain-binding
			       ;; some indirect references e.g. "giving the value of"
			       ;; would occasionaly fail here when it wasn't a lookup or generate
			       (lookup-or-generate-var-spot-index-for-local-name domain-binding)))))
		      ((the-inverse-no-bind)
		       (gensym-dstruct-bind
			 ((nil range-binding role short-designation
			       domain-binding)
			  iterator)
			 (record-free-references-of-role-given-domain-name
			   role domain-binding)
			 (phrase-list
			   quantifier range-binding role short-designation
			   domain-binding
			   (lookup-or-generate-var-spot-index-for-local-name
			     range-binding)
			   (if (eq domain-binding short-designation)
			       domain-binding
			       (lookup-or-generate-var-spot-index-for-local-name
				 domain-binding)))))
		      
		      (otherwise
		       (compiler-bug
			 "rule context rewriter"
			 "Unrecognized context quantifier ~a."
			 quantifier)))
				 using phrase-cons))
		       using phrase-cons))

(defun record-free-references-of-role-given-domain-name (role domain-name?)
  (if (symbolp role)
;      (if domain-name?
;          (let* ((domain-type? (type-of-global-or-local-name domain-name?))
;                 (domain-class?
;                   (if (valid-class-type-specification-p domain-type?)
;                       (type-specification-class domain-type?))))
;            (record-free-reference
;              'attribute-of-class (phrase-cons role domain-class?)))
;          (record-free-reference 'class role))
      ;; Note that the attribute-of-class free-reference is no longer recorded
      ;; here.  This analysis is included in the cached-attribute reference
      ;; which is recorded in the stack-instruction emitter for
      ;; cached-attribute-value.  - cpm, 7/29/93
      (when (null domain-name?)
	(record-free-reference 'class role))
      (record-free-references-of-role role)))

(defun type-of-global-or-local-name (possible-local-name)
  (multiple-value-bind (var-spot? description?)
      (variable-spot-and-description-for-local-name possible-local-name)
    (declare (ignore var-spot?))
    (or (and description?
	     (getfq (cdr description?) :type))
	'(class item))))

(defun var-spot-index-for-local-name (local-name)
  (let ((var-spot? (variable-spot-and-description-for-local-name local-name)))
    (cond (var-spot?
	   (var-spot-index-of-var-spot var-spot?))
	  (t
	   (compiler-bug
	     "rule context rewrite"
	     "The local name ~a hadn't been registered."
	     local-name)
	   0))))

(defun var-spot-index-or-global-name (local-or-global-name)
  (let ((var-spot? (variable-spot-and-description-for-local-name
		     local-or-global-name)))
    (cond (var-spot?
	   (var-spot-index-of-var-spot var-spot?))
	  (t
	   local-or-global-name))))

(defun lookup-or-generate-var-spot-index-for-local-name (local-name)
  (let ((var-spot? (variable-spot-and-description-for-local-name local-name)))
    (cond (var-spot?
	   (var-spot-index-of-var-spot var-spot?))
	  (t
	   (var-spot-index-of-var-spot
	     (generate-new-variable-spot 'item-or-datum local-name))))))




;;; The function `rewrite-conclude-actions-in-action-list' takes an action list
;;; and returns an action list with all conclude action rewritten to propagate
;;; antecedent truth values and expirations and to conclude constant attributes
;;; where a local name has been used in the conclude and the local name caches
;;; the value of an attribute.

(defun rewrite-conclude-actions-in-action-list (action-list in-order-rule?)
  (loop for action in action-list
	for action-name = (car action)
	collect
	  (case action-name
	    ((every let-action)
	     (phrase-list*
	       action-name (second action)
	       (rewrite-conclude-actions-in-action-list
		 (cddr action) in-order-rule?)))
	    ((conclude conclude-not)
	     (when (eq action-name 'conclude-not)
	       (setq rule-certainty-var '|certainty-var|)
	       (setq action-name 'conclude)
	       (setq action
		     (phrase-list*
		       'conclude
		       (second action)
		       (phrase-list 'not rule-certainty-var)
		       (cddr action))))
	     (gensym-dstruct-bind ((nil place value . other-args) action)
	       (when in-order-rule?
		 (setq rule-expiration-var '|expiration-var|))
	       (when (null value)
		 (setq rule-certainty-var '|certainty-var|)
		 (setq value rule-certainty-var))
	       (cond
		 ((not (symbolp place))
		  (phrase-list*
		    action-name place value other-args))
		 (t
		  (let ((cached-designation?
			  (second (assq place local-name-to-cached-designation-alist))))
		    (cond
		      ((not (and (consp cached-designation?)
				 (=f (length cached-designation?) 3)
				 (eq (car cached-designation?) 'the)
				 (symbolp (second cached-designation?))))
		       (phrase-list*
			 action-name place value other-args))
		      ((name-rooted-attribute-only-designation-p
			 (third cached-designation?))
		       (phrase-list*
			 action-name cached-designation? value other-args))
		      (t
		       (let ((parent-designation (third cached-designation?))
			     (generated-local-name
			       (interned-conclude-attribute-binding-symbol)))
			 (phrase-push
			   (phrase-list generated-local-name parent-designation)
			   conclude-parent-attribute-bindings)
			 (phrase-list*
			   action-name
			   (phrase-list
			     'the (second cached-designation?)
			     generated-local-name)
			   value
			   other-args)))))))))
	    (t action))
	using phrase-cons))

(defun compile-in-order-actions
       (action-list expiration-var-spot? push-stack-frame-vars-instruction)
  (loop for action-list-cons on action-list
	for action = (car action-list-cons)
	for action-name = (car action)
	do
    (cond ((eq action-name 'every)
	   (compile-in-order-every-action
	     action expiration-var-spot?
	     push-stack-frame-vars-instruction))
	  ((eq action-name 'let-action)
	   (compile-in-order-let-action
	     action expiration-var-spot?
	     push-stack-frame-vars-instruction))
	  (t
	   ;; Also check for shutdown g2 and reset-kb?  -jra 2/1/92
	   (when (and (eq action-name 'pause-kb)
		      (cdr action-list-cons))
	     (compiler-error
	       "Pause knowledge-base must be the last action in a rule."))
	   (compile-in-order-action
	     action expiration-var-spot?
	     push-stack-frame-vars-instruction)))))

(defun compile-in-order-every-action
       (action expiration-var-spot
	push-stack-frame-vars-instruction)
  (gensym-dstruct-bind ((nil (role binding . domain-list) . inner-action-list)
		       action)
    (let* ((iteration-designation
	     (phrase-cons 'any (phrase-cons role domain-list)))
	   (iteration-type
	     (or (type-specification-of-designation iteration-designation)
		 'item-or-datum))
	   (iteration-spot
	     (generate-new-variable-spot iteration-type binding))
	   (continuation-spot
	     (generate-new-variable-spot
	       (make-type-specification-for-iteration-state)))
	   (required-domain-types
	     (if (not (symbolp role))
		 (required-domain-types-of-role
		   (role-name-of-non-atomic-role
		     role))))
	   (next-iteration-tag (generate-new-goto-tag))
	   (end-of-every-tag (generate-new-goto-tag)))
      (when (/=f (length required-domain-types) (length domain-list))
	(write-compiler-error
	  (twrite-string "The number of arguments to ")
	  (print-role role)
	  (tformat ", ~a, did not match the required count, ~a"
		   (length domain-list)
		   (length required-domain-types))))
      (if domain-list
	  (emit-already-consed-instruction
	    (nconc
	      (phrase-list
		'open-role-iteration role continuation-spot iteration-spot
		iteration-type iteration-type end-of-every-tag)
	      (loop for domain in domain-list
		    for type-cons = required-domain-types then (cdr type-cons)
		    for type = (or (car type-cons) 'item-or-datum)
		    collect
		      (compile-stack-expression-into-nodes
			domain type)
			     using phrase-cons)))
	  (emit-instruction
	    'open-role-iteration-no-domain role continuation-spot iteration-spot
	    iteration-type iteration-type end-of-every-tag))
      (emit-instruction 'tag-statement next-iteration-tag)
      (compile-in-order-actions
	inner-action-list expiration-var-spot push-stack-frame-vars-instruction)
      (emit-instruction
	'serve-next-iteration-value continuation-spot iteration-spot
	iteration-type iteration-type end-of-every-tag)
      (emit-branch-or-jump next-iteration-tag)
      (emit-instruction 'tag-statement end-of-every-tag)
      (emit-instruction 'close-iteration continuation-spot))))

(defvar current-let-action-bindings nil)

(defun compile-in-order-let-action
       (action expiration-var-spot
	push-stack-frame-vars-instruction)
  (let ((current-let-action-bindings current-let-action-bindings))
    (gensym-dstruct-bind ((nil bindings . inner-actions) action)
      (loop for binding in bindings
	    for binding-name = (car binding)
	    for expression? = (second binding)
	    for compiled-expression? =
	    (when expression?
	      (compile-stack-expression-into-nodes
		expression? '(or item-or-datum (unknown-datum) (no-item))))
	    for expression-type? =
	    (when compiled-expression?
	      (stack-node-value-type compiled-expression?))
	    for var-spot-type =
	    (cond ((null expression-type?)
		   'item-or-datum)
		  (t
		   (type-specification-minus-type
		     (type-specification-minus-type
		       expression-type?
		       '(unknown-datum))
		     '(no-item))))
	    for var-spot = (generate-new-variable-spot var-spot-type binding-name)
	    do
	(when compiled-expression?
	  (emit-instruction
	    'assign-local-var
	    var-spot
	    compiled-expression?)
	  ;; Current-let-action-bindings are used to rebuild deep expressions for
	  ;; the left hand side of assignment actions like conclude and change.
	  ;; These associate the local-name with the original expression used to
	  ;; initialize it.
	  (setq current-let-action-bindings
		(phrase-cons binding current-let-action-bindings))))
      (compile-in-order-actions
	inner-actions expiration-var-spot
	push-stack-frame-vars-instruction))))

(defun compile-in-order-action (action expiration-var-spot
				push-stack-frame-vars-instruction)
  (let* ((action-name (car-of-cons action))
	 (action-compiler? (action-compiler action-name))
	 (resume-tag (generate-new-goto-tag)))
    (emit-instruction 'tag-statement resume-tag)
    (when expiration-var-spot
      (emit-instruction 'set-expiration expiration-var-spot))
    (cond
      (action-compiler?
       (let ((prolog-stream (make-pseudo-instruction-stream))
	     (epilog-stream (make-pseudo-instruction-stream))
	     (epilog-tag (generate-new-goto-tag)))
	 (funcall-simple-compiled-function
	   (compiled-function-in-place action-compiler?)
	   action t t prolog-stream epilog-stream)
	 (merge-pseudo-instruction-stream prolog-stream)
	 (emit-instruction 'branch-if-known epilog-tag)
	 (emit-instruction 'set-wake-ups)
	 (emit-instruction 'close-wake-up-collection)
	 (emit-instruction 'complete-rule-instance nil)
	 (emit-already-consed-instruction
	   push-stack-frame-vars-instruction)
	 (emit-instruction 'open-wake-up-collection)
	 (emit-branch-or-jump resume-tag)
	 ;; If all arguments had values, clear any wake up
	 ;; residuals and execute the action.
	 (emit-instruction 'tag-statement epilog-tag)
	 (emit-instruction 'clear-wake-ups)
	 (merge-pseudo-instruction-stream epilog-stream)))
      (t
       (compiler-bug
	 "rule action compiler"
	 "No compiler for action ~a." action-name)))))

(defun compile-simultaneous-actions
       (action-list prolog-stream epilog-stream action-count action-cache?)
  (loop for action-list-cons on action-list
	for action = (car action-list-cons)
	for action-name = (car action)
	for action-compiler? = (action-compiler action-name)
	do
    (cond ((eq action-name 'every)
	   (compile-simultaneous-every-action
	     action prolog-stream epilog-stream action-count action-cache?))
	  ((eq action-name 'let-action)
	   (compile-simultaneous-let-action
	     action prolog-stream epilog-stream action-count action-cache?))
	  (action-compiler?
	   (when (and (eq action-name 'pause-kb)
		      (cdr action-list-cons))
	     (compiler-error
	       "Pause knowledge-base must be the last action in a rule."))
	   (if action-cache?
	       (let* ((action-epilog-stream (make-pseudo-instruction-stream))
		      (epilog-next-iteration-tag (generate-new-goto-tag))
		      (epilog-action-cache-empty-tag (generate-new-goto-tag))
		      (var-spot-block 
			(funcall-simple-compiled-function
			  (compiled-function-in-place action-compiler?)
			  action t nil prolog-stream action-epilog-stream)))
		 (emit-instruction-to-stream
		   prolog-stream 'add-to-action-cache
		   action-cache? var-spot-block)
		 (emit-instruction-to-stream
		   epilog-stream 'tag-statement epilog-next-iteration-tag)
		 (emit-instruction-to-stream
		   epilog-stream 'restore-from-action-cache-or-branch
		   action-cache? var-spot-block epilog-action-cache-empty-tag)
		 (merge-pseudo-instruction-streams
		   epilog-stream action-epilog-stream)
		 (emit-instruction-to-stream
		   epilog-stream 'branch epilog-next-iteration-tag)
		 (emit-instruction-to-stream
		   epilog-stream 'tag-statement epilog-action-cache-empty-tag))
	       (funcall-simple-compiled-function
		 (compiled-function-in-place action-compiler?)
		 action t (=f action-count 1) prolog-stream epilog-stream)))
	  (t
	   (compiler-bug
	     "rule action compiler"
	     "No compiler for action ~a." action-name)))))


(defun compile-simultaneous-every-action
       (action prolog-stream epilog-stream action-count previous-action-cache?)
  (gensym-dstruct-bind ((nil (role binding . domain-list) . inner-action-list)
		       action)
    (let* ((iteration-designation
	     (phrase-cons 'any (phrase-cons role domain-list)))
	   (iteration-type
	     (or (type-specification-of-designation iteration-designation)
		 'item-or-datum))
	   (iteration-spot
	     (generate-new-variable-spot iteration-type binding))
	   (continuation-spot
	     (generate-new-variable-spot
	       (make-type-specification-for-iteration-state)))
	   (required-domain-types
	     (if (not (symbolp role))
		 (required-domain-types-of-role
		   (role-name-of-non-atomic-role
		     role))))
	   (next-iteration-tag (generate-new-goto-tag))
;	   (epilog-next-iteration-tag (generate-new-goto-tag))
	   (action-cache
	     (or previous-action-cache?
		 (generate-new-variable-spot '(action-cache))))
	   (end-of-every-tag (generate-new-goto-tag))
;	   (epilog-end-of-every-tag (generate-new-goto-tag))
	   )
      (when (/=f (length required-domain-types) (length domain-list))
	(write-compiler-error
	  (twrite-string "The number of arguments to ")
	  (print-role role)
	  (tformat ", ~a, did not match the required count, ~a"
		   (length domain-list)
		   (length required-domain-types))))
      ;; Clear the action cache in case a previous attempt at this rule filled
      ;; it with anything.
      (unless previous-action-cache?
	(emit-instruction-to-stream
	  prolog-stream 'clear-action-cache action-cache))
      ;; Emit the prolog stream instructions for iteration.
      (if domain-list
	  (emit-already-consed-instruction-to-stream
	    prolog-stream
	    (nconc
	      (phrase-list
		'open-role-iteration role continuation-spot iteration-spot
		iteration-type iteration-type end-of-every-tag)
	      (loop for domain in domain-list
		    for type-cons = required-domain-types then (cdr type-cons)
		    for type = (or (car type-cons) 'item-or-datum)
		    collect
		      (compile-stack-expression-into-nodes
			domain type)
			     using phrase-cons)))
	  (emit-instruction-to-stream
	    prolog-stream
	    'open-role-iteration-no-domain role continuation-spot iteration-spot
	    iteration-type iteration-type end-of-every-tag))
      (emit-instruction-to-stream
	prolog-stream 'tag-statement next-iteration-tag)
      ;; Emit a tag statement for epilog iterations.
;      (emit-instruction-to-stream
;	epilog-stream 'tag-statement epilog-next-iteration-tag)
      ;; Compile the action.
      (compile-simultaneous-actions 
	inner-action-list prolog-stream epilog-stream action-count action-cache)
      ;; Emit the prolog completion of iteration.
      (emit-instruction-to-stream
	prolog-stream
	'serve-next-iteration-value continuation-spot iteration-spot
	iteration-type iteration-type end-of-every-tag)
      (emit-instruction-to-stream prolog-stream 'branch next-iteration-tag)
      (emit-instruction-to-stream prolog-stream 'tag-statement end-of-every-tag)
      (emit-instruction-to-stream
	prolog-stream 'close-iteration continuation-spot)
      ;; Emit the epilog completion of iteration.
;      (emit-instruction-to-stream
;	epilog-stream 'branch epilog-next-iteration-tag)
;      (emit-instruction-to-stream
;	epilog-stream 'tag-statement epilog-end-of-every-tag)
      )))

(defun compile-simultaneous-let-action
       (action prolog-stream epilog-stream action-count action-cache?)
  (let ((current-let-action-bindings current-let-action-bindings))
    (gensym-dstruct-bind ((nil bindings . inner-actions) action)
      (loop for binding in bindings
	    for binding-name = (car binding)
	    for expression? = (second binding)
	    for compiled-expression? =
	    (when expression?
	      (compile-stack-expression-into-nodes
		expression? '(or item-or-datum (unknown-datum) (no-item))))
	    for expression-type? =
	    (when compiled-expression?
	      (stack-node-value-type compiled-expression?))
	    for var-spot-type =
	    (cond ((null expression-type?)
		   'item-or-datum)
		  (t
		   (type-specification-minus-type
		     (type-specification-minus-type
		       expression-type?
		       '(unknown-datum))
		     '(no-item))))
	    for var-spot
		= (generate-new-variable-spot var-spot-type binding-name)
	    do
	(when compiled-expression?
	  (emit-instruction-to-stream
	    prolog-stream
	    'assign-local-var
	    var-spot
	    compiled-expression?)
	  (setq current-let-action-bindings
		(phrase-cons binding current-let-action-bindings))))
      (compile-simultaneous-actions
	inner-actions prolog-stream epilog-stream action-count action-cache?))))




;;; The function 

;(defun-allowing-unwind compile-generic-formula-for-stack
;		       (domain compiled-body)
;  (let ((byte-code-vector nil)
;	(byte-codes-count nil)
;	(byte-code-constants nil)
;	(byte-code-body-to-return nil))
;    (with-compiler-environment
;      (enter-new-code-body
;	(phrase-list
;	  (phrase-list domain :type (make-class-type-specification domain)))
;	(let* ((result-var-spot (generate-new-variable-spot 'datum))
;	       (compiled-expression-stack-nodes
;		 (compile-stack-expression-into-nodes
;		   compiled-body
;		   '(or datum (unknown-datum)))))
;	  (unless compiler-errors
;	    (emit-instruction
;	      'assign-local-var result-var-spot
;	      compiled-expression-stack-nodes)
;	    (emit-instruction 'complete-generic-formula result-var-spot))))
;      (unless compiler-errors
;	(let ((byte-code-stream (make-byte-code-stream))
;	      (instructions (nreverse
;			      (compiler-code-body-instructions-so-far
;				(car code-body-entries-in-compilation)))))
;	  (emit-byte-code-vector-for-procedure byte-code-stream instructions)
	  
;	  (when (null compiler-errors)
;	    (multiple-value-setq (byte-code-vector byte-codes-count)
;	      (resolve-procedure-byte-code-addresses byte-code-stream)))
	  
;	  (when (null compiler-errors)
;	    (setq byte-code-constants
;		  (make-procedure-byte-code-constants byte-code-stream)))
	  
;	  (reclaim-byte-code-stream byte-code-stream)))
      
;      ;; Did we get a good one?
;      (setq byte-code-body-to-return
;	    (if compiler-errors
;		(make-byte-code-body 4 (allocate-byte-vector 4) nil nil nil)
;		(make-byte-code-body
;		  byte-codes-count byte-code-vector byte-code-constants
;		  nil nil)))
;      (install-free-references-in-byte-code-body
;	byte-code-body-to-return compiler-free-references)
;      byte-code-body-to-return)))

(defun-allowing-unwind compile-expression-cell-for-stack
		       (expression arguments-and-types result-type)
  (let* ((byte-code-vector nil)
	 (byte-codes-count nil)
	 (byte-code-constants nil)
	 (byte-code-body-to-return nil)
	 (environment nil)
	 (expression-type
	   (type-specification-minus-type result-type '(obsolete-datum)))
	 (variable-type
	   (type-specification-minus-type expression-type '(unknown-datum)))
	 (code-body-entry nil))
    (with-compiler-environment
      (enter-new-code-body nil
	(setq code-body-entry (car-of-cons lexically-visible-code-bodies))
	(let ((result-var-spot (generate-new-variable-spot variable-type)))
	  (loop for (binding-name type) in arguments-and-types do
	    (generate-new-variable-spot type binding-name))
	  (emit-instruction
	    'assign-local-var result-var-spot
	    (compile-stack-expression-into-nodes
	      expression
	      expression-type))
	  (emit-instruction 'complete-cell-expression result-var-spot))
	(setq environment (compiler-code-body-environment-description
			    (current-compiler-code-body))))
      (unless compiler-errors
	(let ((byte-code-stream (make-byte-code-stream))
	      (instructions (nreverse
			      (compiler-code-body-instructions-so-far
				(car code-body-entries-in-compilation)))))
	  ;; added by rdf 1/18/94
	  (setq instructions (optimize-procedure-instructions instructions
							      (car code-body-entries-in-compilation)))
	  (unless compiler-errors
	    (let ((lexically-visible-code-bodies
		    (generate-list-of-lexically-visible-code-bodies code-body-entry)))
	      (emit-byte-code-vector-for-procedure byte-code-stream instructions)))
	  
	  (when (null compiler-errors)
	    (multiple-value-setq (byte-code-vector byte-codes-count)
	      (resolve-procedure-byte-code-addresses byte-code-stream)))
	  
	  (when (null compiler-errors)
	    (setq byte-code-constants
		  (make-procedure-byte-code-constants byte-code-stream)))
	  
	  (reclaim-byte-code-stream byte-code-stream)))
      
      ;; Did we get a good one?
      (setq byte-code-body-to-return
	    (if compiler-errors
		nil ;(make-byte-code-body 4 (allocate-byte-vector 4) nil nil nil)
		(make-byte-code-body
		  byte-codes-count byte-code-vector byte-code-constants
		  (convert-description-list-to-managed-array
		    environment)
		  nil)))
      (when byte-code-body-to-return
	  (install-free-references-in-byte-code-body
	    byte-code-body-to-return compiler-free-references))
      byte-code-body-to-return)))








;;;






;;;; Generating Stack Node Trees




;;; The function `compile-stack-expression-into-nodes' takes a parsed expression
;;; from procedures and compiles it into a tree of stack-compiler-nodes.  The
;;; instructions for these nodes will be emitted later.  This function will be
;;; called by the stack-procedure compiler.

(defun-allowing-unwind compile-stack-expression-into-nodes
		       (expression required-type)
  #+development
  (when (null required-type)
    (cerror "Continue with item-or-datum"
	    "No required type to stack compiler!")
    (setq required-type 'item-or-datum))
  ;; If we're about to gen a stack-node-tree for an expression which has an
  ;; annotation, emit the annotation instruction -dkuznick, 2/3/99
  (let ((annotation? (and generate-source-annotation-info
			  (consp expression)
			  (get-current-annotation-context expression))))
    (when annotation?
      (emit-instruction 'annotation annotation?)))
  (with-stack-frame-variables
    (let ((stack-node-tree
	    (convert-expression-to-stack-node-tree expression)))
      (setq stack-node-tree
	    (choose-stack-node-instructions-and-types
	      stack-node-tree required-type))
      (ensure-argument-types-satisfy-operators nil stack-node-tree)
      (setq stack-node-tree
	    (rewrite-stack-node-trees-for-unknown stack-node-tree))
      (when outermost-stack-frame-var-binding?
	(setf (stack-node-stack-frame-vars-needed stack-node-tree)
	      next-stack-frame-var-location))
      (check-ensure-type-nodes stack-node-tree)
      #+compiler-debug
      (cerror "Continue" "Finished compiling ~a" stack-node-tree)
      stack-node-tree)))






;;;; Byte Code Body Compiler




;;; Within many parts of G2, single expressions are compiled to produce an
;;; executable entity which returns a value from its computation.  The function
;;; `compile-expression-into-byte-code-body' implements this compilation step.
;;; This function takes an expression, a list of names which are bound 

;;;






;;;; Expression Compiler Design




;;; The most difficult aspect of this compiler is the replication of the
;;; semantics of unknown values.  There are different semantics for each of the
;;; three evaluation systems in G2 at this point in time.  Though we may make
;;; some adjustments to bring the simulator and inference engine unknown
;;; semantics into agreement, procedures will still be different.  Currently,
;;; all three are different.  The semantics of unknown have never been broadly
;;; defined for G2, and so this project will have to retrofit a design onto the
;;; existing implementation.  Further, many of the characteristics of the
;;; semantics of unknown were built because it was easy within the old
;;; implementation.  These will not necessarily be so easy within the new
;;; compiler and implementation of the evaluator.  The following discussion of
;;; expression evaluation in G2 is mainly to define terms for use in the design
;;; of the compiler.




;;; Compiling Trees

;;; The goal of compilation of all these trees is to produce an executable
;;; stream of instructions such that after execution of the final instruction
;;; emitted for an expression, the value of the expression will be on the top of
;;; the stack and the expiration of that value in the global variable for
;;; expirations.  If the expiration is NIL, then the value on the top of the
;;; stack will also be NIL.

;;; The process of compiling an expression tree into instructions could be
;;; carried out as follows.  First the input s-expression should be traversed
;;; transforming each expression and subexpression into structure instances
;;; which can be augmented as the compile proceeds.  During this transformation,
;;; nodes should be marked with their types.  Hopefully, even more information
;;; can be cached during this phase about the operator, including some data
;;; structure that represents all compiler information about an operator so the
;;; lookup from symbol to compiler data structure need not be done many times. 
;;; As the transformation returns back up the tree, subtrees should be
;;; classified as much as is possible (can they be completely classified at this
;;; point?).  Each node should be marked with the type of subtree below it. 
;;; This way, classification of a node can be done only by checking the
;;; classifications of the subnodes immediately below it, instead of having the
;;; traverse the entire subtree.  After this classification, optimizations could
;;; be performed on the tree, including things like common subexpression
;;; collapsing.  Note that any common sub-expression collapsing will also have
;;; to deal with expirations of the collapsed subexpression in the secondary
;;; usage points.  After optimizations have been performed, then the tree should
;;; be traversed top down, applying compilation functions as appropriate to each
;;; tree type.







;;;; Preferred Instruction Choosers




;;; The following definitions are for all of the stack node instructions which
;;; get generated into stack node trees as an internal part of the compiler.
;;; This should set the return-type and register and free references.

;;; The dummy-instruction is used when a stack-node needs to be made in an error
;;; situation.

(def-preferred-instruction-chooser dummy-instruction
  (declare (ignore required-type extra-info))
  (setf (stack-node-value-type stack-node-instruction) 'item-or-datum))



(declare-instruction-for-optimizer
  'no-op
  '(no-wait-states
    cannot-write-local-variables
    cannot-read-local-variables
    cannot-write-roles
    cannot-read-roles))

;;; The no-op instruction is used when a node is needed, but it should emit
;;; nothing.

(def-preferred-instruction-chooser no-op
  (declare (ignore extra-info))
  (setf (stack-node-value-type stack-node-instruction)
	required-type))




(declare-instruction-for-optimizer
  'push-constant
  '(no-wait-states
    cannot-read-local-variables
    cannot-write-local-variables
    cannot-read-roles
    cannot-write-roles
    cost 1))

;;; The push-constant instruction holds an evaluation value in the extra-info
;;; slot.

(def-preferred-instruction-chooser push-constant
  (let ((float-required?
	  (type-specification-subtype-p
	    required-type
	    '(or float (unknown-datum) (no-item)))))
    (when (and float-required?
	       (evaluation-integer-p extra-info))
      (with-temporary-gensym-float-creation push-constant-chooser
	(let ((new-constant
		(make-evaluation-float
		  (coerce-fixnum-to-gensym-float
		    (evaluation-integer-value extra-info)))))
	  (reclaim-evaluation-integer extra-info)
	  (setq extra-info new-constant)
	  (setf (stack-node-instruction-extra-info stack-node-instruction)
		new-constant))))
    ;added by SoftServe
    (when (and float-required?
	       (evaluation-long-p extra-info))
	(let ((new-constant
               (make-evaluation-float-from-evaluation-long extra-info)))
	  (reclaim-evaluation-long extra-info)
	  (setq extra-info new-constant)
	  (setf (stack-node-instruction-extra-info stack-node-instruction)
		new-constant)))
    ;end of SoftServe changes
    (when (and (evaluation-text-p extra-info)
	       (>f (lengthw (evaluation-text-value extra-info))
		   maximum-length-for-user-text-strings))
      (let ((small-text (text-string-substring 
			  (evaluation-text-value extra-info)
			  0 20)))
	(compiler-error
	  "The text beginning with \"~a...\" contains more than ~a characters."
	  small-text maximum-length-for-user-text-strings)
	(reclaim-text-string small-text)))
    (setf (stack-node-value-type stack-node-instruction)
	  (evaluation-value-type extra-info))))





(declare-instruction-for-optimizer
  'name-reference
  '(no-wait-states
    cannot-read-local-variables
    cannot-write-local-variables
    cannot-write-roles))

;;; The name reference instruction holds a symbol which is a name in the
;;; extra-info slot.

;; This code will be obsolete when named item references compile into the
;; cached-item instruction instead of the name-reference instruction.  - cpm,
;; 7/20/93

(def-preferred-instruction-chooser name-reference
  (let* ((name extra-info)
	 (unknown-allowed?
	   (type-specification-subtype-p '(unknown-datum) required-type))
	 (no-item-allowed?
	   (type-specification-subtype-p '(no-item) required-type))
	 (no-item-implies-unknown-allowed?
	   (type-specification-subtype-p '(no-item-implies-unknown) required-type))
	 (stripped-type
	   (type-specification-minus-type 
	     (type-specification-minus-type 
	       (type-specification-minus-type required-type '(unknown-datum))
	       '(no-item))
	     '(no-item-implies-unknown)))
	 (stable-item? (stable-name-p name))
	 (stable-item-of-class?
	   (when stable-item?
	     (stable-name-of-class-p
	       name (class stable-item?) *current-computation-frame*))))
    (cond (stable-item-of-class?
	   (setf (stack-node-value-type stack-node-instruction)
		 (make-class-type-specification (class stable-item?)))
	   (record-free-reference
	     'stable-name-of-class-instance
	     (phrase-cons name (class stable-item-of-class?))))
	  (stable-item?
	   (setf (stack-node-value-type stack-node-instruction)
		 (make-class-type-specification 'item))
	   (record-free-reference 'stable-name name))
	  (t
	   (setf (stack-node-value-type stack-node-instruction)
		 (maybe-add-unknown
		   (maybe-add-no-item
		     (make-class-type-specification 'item) no-item-allowed?)
		   no-item-implies-unknown-allowed?))
	   (if (datum-type-specification-p stripped-type)
	       (record-free-reference
		 'name-of-type
		 (phrase-cons
		   name
		   (if unknown-allowed?
		       (type-specification-returning-datum-type-or-unknown
			 stripped-type t)
		       (type-specification-returning-datum-type
			 stripped-type t))))
	       (record-free-reference
		 'name-of-type (phrase-cons name stripped-type)))))))




;;; The push-cached-item instruction holds a symbol and a flag in the extra-info
;;; slot.  The symbol is the item name and the flag indicates if the named thing
;;; is stable and depended upon.

(declare-instruction-for-optimizer
  'push-cached-item
  '(no-wait-states
    cannot-read-local-variables
    cannot-write-local-variables
    reads-only-roles-specified-by-argument
    role-read-accessor get-stack-node-extra-info
    cannot-write-roles
    cost 1))

(def-preferred-instruction-chooser push-cached-item
  (let* ((name extra-info)
	 (stable-item? (if (dependent-compilation-p)
			   (stable-name-p name)
			   nil))
	 (stable-item-of-class?
	   (when stable-item?
	     (stable-name-of-class-p
	       name (class stable-item?) *current-computation-frame*)))
	 (class (if stable-item-of-class?
		    (class stable-item-of-class?)
		    'item))
	 (no-item-allowed?
	   (type-specification-subtype-p '(no-item) required-type)))
    (setf (stack-node-value-type stack-node-instruction)
	  (maybe-add-no-item
	    (make-class-type-specification class)
	    (and (not stable-item?)
		 no-item-allowed?)))

    ;; Note that the cached-name and name-of-type free-references are not
    ;; recorded here, but are recorded in the emitter for the cached-name
    ;; instruction.  This is necessary because the free reference needs the
    ;; constant index which is computed in the emitter and non-stable type
    ;; references for names should only be registered after the compiler and
    ;; optimizer have stopped changing the required type for this stack node.
    (when stable-item?
      (record-free-reference
	'stable-name-of-class-instance (phrase-cons name class)))))


(declare-instruction-for-optimizer
  'evaluate-role-with-no-domain
  '(no-wait-states
    cannot-write-local-variables
    cannot-read-local-variables
    cannot-write-roles
    reads-only-roles-specified-by-argument
    role-read-accessor get-stack-node-extra-info))

;;; The evaluate-role-with-no-domain instruction holds a simple role in the
;;; extra-info slot.

(def-preferred-instruction-chooser evaluate-role-with-no-domain
  (let ((no-item-allowed?
	  (type-specification-subtype-p '(no-item) required-type)))
    (cond ((symbolp extra-info)
	   (record-free-reference 'class extra-info)
	   (setf (stack-node-value-type stack-node-instruction)
		 (maybe-add-no-item 
		   (make-class-type-specification extra-info)
		   no-item-allowed?)))
	  ((required-domain-types-of-role
	     (role-name-of-non-atomic-role extra-info))
	   (write-compiler-error
	     (twrite-string "The role ")
	     (print-role extra-info)
	     (twrite-string " requires a domain, but received none."))
	   (setf (stack-node-value-type stack-node-instruction)
		 'item-or-datum))
	  (t
	   (record-free-references-of-role extra-info)
	   (setf (stack-node-value-type stack-node-instruction)
		 (maybe-add-no-item
		   (or (type-specification-of-role extra-info)
		       'item-or-datum)
		   no-item-allowed?))))))




;;; The evaluate-role instruction holds a simple role in the extra info slot,
;;; and has an argument, the domain of the role.

;;; Note that this chooser will rewrite the role in one case right now.  When
;;; the role is an attribute reference, and the required type includes
;;; place-reference, then the role will be changed to attribute-frame-or-
;;; place-reference.  This is used when concluding constants or changing
;;; attributes of objects.  This role is further recognized in the emitter and
;;; emitted as a call to an optimized instruction.

;; Modified the indirect-attribute role, attribute-value, to instead use
;; attribute-frame-or-place-reference when possible.  Also, modified the
;; g2-array or g2-list element role, nth-element, to instead use
;; element-frame-or-place-reference when possible.  - cpm, 12/12/91


(defvar sorted-static-evaluate-role-dispatchers nil)
(def-global-property-name unique-value-of-role-instruction-name)
(def-global-property-name static-evaluate-role-dispatch-predicate)
(def-global-property-name static-evaluate-role-dispatch-parent)

(defun-for-system-procedure g2-toggle-evaluate-role-inline
    (ev-truth-value)
  (setq allow-inline-evaluate-role-instructions-p
	(not (eq ev-truth-value evaluation-false-value))))
	 
  

;;; `def-unique-value-of-role-dispatcher' is the form that allows one do define
;;; an agenda of predicates to be used in the preferred instruction chooser of
;;; evaluate role to perform static dispatches to various optimized
;;; unique-value-of-role-servers (see ROLES).  Because some of the servers
;;; operate upon subsets of data that others could operate on (eg. integer-array
;;; vs value-array), the agenda is sorted.  Each evaluation of a
;;; def-unique-value-of-role-dispatcher therefore invalidates this sort.
;;; The need for invalidation is only real during development, the sorted
;;; agenda is created once-and-for-all for builds during the loading/initting
;;; of the module G2-FINAL.

(defmacro def-unique-value-of-role-dispatcher
    ((role-spec &key instruction-name next-most-general-instruction
	            refined-value-type)
      arg-list-for-dispatcher
      &body body)
  (let* ((role-name (if (consp role-spec) (car role-spec) role-spec))
	 (dispatch-predicate-name
	   (build-ab-symbol role-name 'dispatch-predicate)))
    (unless (and t ; (= (length arg-list-for-dispatcher) 5)
		 (every 'symbolp arg-list-for-dispatcher))
      (error
	"bad args for dispatch function of unique-value-of-role-instruction"))
    (unless (and (symbolp role-name)
		 (unique-value-of-role-server-function role-name))
      (error
	"role name must be a symbol have a defined unique-value-of-role-server  ~s"
	role-name))
    `(progn
       (setf (unique-value-of-role-instruction-name ',role-name)
	     ',instruction-name)
       (setf (static-evaluate-role-dispatch-parent
	       ',role-name)
	     ',next-most-general-instruction)
       ;; For every eval of def-static-evaluate-role-dispatcher
       ;; invalidate the sorted-dispatchers because the partial
       ;; ordering defined by static-evaluate-role-dispatch-parent
       ;; may change.
       (setf sorted-static-evaluate-role-dispatchers nil)
       (defun-into-place
	   (,dispatch-predicate-name
	      (static-evaluate-role-dispatch-predicate ',role-name))
	   ,arg-list-for-dispatcher
	 (when (progn ,@body)
	   (values (copy-for-phrase ',role-spec)
		   ',instruction-name
		   ',refined-value-type))))))



;;; `sort-the-static-evaluate-role-dispatcher' uses the transitive closure of
;;; the property static-evaluate-role-dispatch-parent to define a less-than
;;; predicate to sort the dispatchers so that the most specific cases of
;;; evaluate-role are always selected in preference to more general ones
;;; whenever possible.

(defun invalidate-static-evaulate-role-dispatcher ()
  (setq sorted-static-evaluate-role-dispatchers nil))

;;; `validate-static-evaulate-role-dispatcher' must not be called
;;; in a temporary-consing extent.  In a production situation
;;; it is conses the sorted-static-evaluate-role-dispatchers list
;;; on the first call only.  To make sure this happens
;;; safely a call to it is placed in G2-FINAL.

(defun validate-static-evaulate-role-dispatcher ()
  (unless sorted-static-evaluate-role-dispatchers
    (setq unique-value-roles
	  (let ((pair-list
		  (loop for role in unique-value-roles
			collect (pair-role-with-depth role))))
	    (setq pair-list (sort pair-list 'cdr-greater-p))
	    (loop for pair in pair-list
		  collect (car pair))))
    ;; (sort unique-value-roles #'static-role-dispatcher-less-than))
    (setq
      sorted-static-evaluate-role-dispatchers
      (loop with result = nil
	    for role-name in unique-value-roles
	    as function? =
	    (static-evaluate-role-dispatch-predicate role-name)
	    do
	(cond
	  (function?
	   (push function? result))
	  (t
	   (error "No dispatcher defined for unique-role-server ~s"
		  role-name)))
	    finally
	      (return (nreverse result))))))

(defun cdr-greater-p (p1 p2)
  (> (cdr p1) (cdr p2)))

(defun pair-role-with-depth (role-name)
  (loop with res = 0
	for role-name-1 = role-name
		      then (static-evaluate-role-dispatch-parent role-name-1)
	while role-name-1
	do (incff res)
    finally (return (cons role-name res))))

(defun static-role-dispatcher-less-than (role-name-1 role-name-2)
  (loop for role-name = role-name-1 then next-name?
        for next-name? = (static-evaluate-role-dispatch-parent role-name)
	while next-name?
	when (eq next-name? role-name-2)
	  return t))

;;; `choose-optimized-evaluate-role-instruction' side-effects the
;;; stack-node-instruction-chosen-instruction slot of the given
;;; stack-node-instruction with a more refined role if applicable.
;;; It also returns a refinement of the given value-type.


(defun choose-optimized-evaluate-role-instruction
    (stack-node-instruction argument-list value-type
			    no-item-allowed? unknown-allowed?)
  (validate-static-evaulate-role-dispatcher)
  (loop with role-constant
	= (stack-node-instruction-extra-info stack-node-instruction)
;	with role-name = (if (consp role-constant)
;			     (car role-constant)
;			     role-constant)
	with domain-1-arg = (first argument-list)
	with domain-2-arg = (and (cdr argument-list)
				 (second argument-list))
	for dispatcher
	    in sorted-static-evaluate-role-dispatchers
       do
;    (format t "dispatcher=~s role=~s~%" dispatcher role-constant)
    (multiple-value-bind
	(specialized-role? instruction-name? refined-value-type?)
        (cond ((null (cdr argument-list))    ; 1-domain case
	       (funcall dispatcher
			role-constant no-item-allowed? unknown-allowed?
			(stack-node-value-type domain-1-arg)
			nil))
	      (t                                     ; 2-domain case
	       (funcall dispatcher
			role-constant no-item-allowed? unknown-allowed?
			(stack-node-value-type domain-1-arg)
			(stack-node-value-type domain-2-arg))))
;      (format t " -> ~s ~s ~s~%"
;	      specialized-role? instruction-name? refined-value-type?)
      (when specialized-role?
	(setf (stack-node-instruction-chosen-instruction
		stack-node-instruction)
	      (phrase-list specialized-role? instruction-name?))
	(return (or refined-value-type? value-type))))
	finally
	  (setf (stack-node-instruction-chosen-instruction
		  stack-node-instruction)
		nil)
	  (return value-type)))

(def-unique-value-of-role-dispatcher (named-by-symbol)
    (role-constant no-item-allowed? unknown-allowed?
		   domain-arg-type? ingored-domain?)
  no-item-allowed? unknown-allowed? ingored-domain?
  (and (consp role-constant)
       (eq (role-name-of-non-atomic-role role-constant)
	   'named-by)
       (type-specification-subtype-p domain-arg-type? 'symbol)))

(def-unique-value-of-role-dispatcher (name-of-item)
    (role-constant no-item-allowed? unknown-allowed?
		   domain-arg-type? ingored-domain?)
  no-item-allowed? unknown-allowed? domain-arg-type?
  ingored-domain?
  (and (consp role-constant)
       (eq (role-name-of-non-atomic-role role-constant)
	   'name)
       (type-specification-subtype-p domain-arg-type?
				     '(class item))))

(def-unique-value-of-role-dispatcher (related-to-item)
    (role-constant no-item-allowed? unknown-allowed?
		   domain-arg-type? ingored-domain?)
  no-item-allowed? unknown-allowed? ingored-domain?
  (and (consp role-constant)
       (eq (role-name-of-non-atomic-role role-constant) 'related)
       (type-specification-subtype-p
	 domain-arg-type? '(class item))))

(def-unique-value-of-role-dispatcher (nth-element-of-integer-array
				       :next-most-general-instruction
				       nth-element-of-value-array
				       :instruction-name
				       nth-integer-array-element)
    (role-constant no-item-allowed? unknown-allowed?
		   array-arg-type? index-arg-type?)
  unknown-allowed?
  (and (consp role-constant)
       (eq (role-name-of-non-atomic-role role-constant) 'nth-element)
       (not no-item-allowed?)
       (type-specification-subtype-p array-arg-type?
					 '(class integer-array))
       (type-specification-subtype-p index-arg-type?
					 'integer)))

(def-unique-value-of-role-dispatcher (nth-element-of-float-array
				       :next-most-general-instruction
				       nth-element-of-value-array
				       :instruction-name
				       nth-float-array-element)
    (role-constant no-item-allowed? unknown-allowed?
		   array-arg-type? index-arg-type?)
  unknown-allowed?
  (and (consp role-constant)
       (eq (role-name-of-non-atomic-role role-constant) 'nth-element)
       (not no-item-allowed?)
       (type-specification-subtype-p array-arg-type?
					 '(class float-array))
       (type-specification-subtype-p index-arg-type?
					 'integer)))

(def-unique-value-of-role-dispatcher (nth-element-of-value-array)
    (role-constant no-item-allowed? unknown-allowed?
		   array-arg-type? index-arg-type?)
  unknown-allowed?
  (and (consp role-constant)
       (eq (role-name-of-non-atomic-role role-constant) 'nth-element)
       (not no-item-allowed?)
       (type-specification-subtype-p array-arg-type?
					 '(class value-array))
       (type-specification-subtype-p index-arg-type?
					 'integer)))


(declare-instruction-for-optimizer
  'evaluate-role
  '(no-wait-states
    cannot-write-local-variables
    cannot-read-local-variables
    reads-only-roles-specified-by-argument
    role-read-accessor get-stack-node-extra-info
    cannot-write-roles))


(def-preferred-instruction-chooser evaluate-role
  (let* ((unknown-allowed?
	   (type-specification-subtype-p '(unknown-datum) required-type))
	 (place-reference-allowed?
	   (type-specification-subtype-p '(place-reference) required-type))
	 (no-item-allowed?
	   (type-specification-subtype-p '(no-item) required-type))
	 (no-item-implies-unknown-allowed?
	   (type-specification-subtype-p
	     '(no-item-implies-unknown) required-type))
	 (unknown-argument? nil)
	 (value-type nil)
	 (role extra-info)
	 (role-name (if (consp role) (role-name-of-non-atomic-role role)))
	 (cons-role-p (consp role))
	 (symbol-role-p (symbolp role))
	 (attribute-value-role-p
	   (and cons-role-p (eq (car-of-cons role) 'attribute-value)))
	 (class-qualified-name-role-p
	   (and cons-role-p (eq (car-of-cons role) 'class-qualified-name)))
	 (nth-element-role-p
	   (and cons-role-p (eq (car-of-cons role) 'nth-element)))
	 (domain-required-type-list
	   (if cons-role-p
	       (required-domain-types-of-role role-name)
	       (if place-reference-allowed?
		   '((or (class item) (place-reference)))
		   '((or (class item) (structure))))))
	 (type-count (length domain-required-type-list))
	 (argument-list (stack-node-argument-nodes stack-node-instruction))
	 (arg-count (length argument-list)) )
    (when (and nth-element-role-p place-reference-allowed?)
      (setq domain-required-type-list
	    (phrase-cons
	      (make-type-specification-union
		(car domain-required-type-list) '(place-reference))
	      (cdr domain-required-type-list))))
    (cond ((and (not (symbolp role)) (null role-name))
	   (compiler-bug
	     "role compiler"
	     "Unknown role type ~a." role))
	  ((/=f type-count arg-count)
	   (write-compiler-error
	     (twrite-string "The role \"")
	     (print-role role)
	     (tformat "\" requires ~a arguments, but received ~a."
		      type-count arg-count))))
    (loop for domain-node-cons on argument-list
	  for type-cons? = domain-required-type-list then (cdr type-cons?)
	  for type = (or (car type-cons?) 'item-or-datum)
	  do
      (setq type (maybe-add-unknown
		   (maybe-add-no-item
		     (maybe-add-no-item-implies-unknown
		       type
		       no-item-implies-unknown-allowed?)
		     no-item-allowed?)
		   unknown-allowed?))
      (setf (car domain-node-cons)
	    (choose-stack-node-instructions-and-types
	      (car-of-cons domain-node-cons)
	      type))
      (when (type-specification-subtype-p
	      '(unknown-datum)
	      (stack-node-value-type (car-of-cons domain-node-cons)))
	(setq unknown-argument? t)))
    (let ()
      (if (or symbol-role-p attribute-value-role-p
	      class-qualified-name-role-p nth-element-role-p)
	  ;; Attribute or indirect-attribute reference.
	  (let* ((domain-type
		   (type-specification-minus-type
		     (type-specification-minus-type 
		       (stack-node-value-type (car argument-list))
		       '(no-item))
		     '(unknown-datum)))
		 (domain-class? (if (class-type-specification-p domain-type)
				    (type-specification-class domain-type)
				    nil)))
	    ;; Note that the attribute-of-class free-reference is no longer
	    ;; recorded here.  This analysis is included in the cached-attribute
	    ;; reference which is recorded in the stack-instruction emitter for
	    ;; cached-attribute-value.  - cpm, 7/29/93
	    ;; It is also recorded below for one of the place-reference roles.
	    ;; - cpm, 7/15/94
;            (when symbol-role-p
;              (record-free-reference
;                'attribute-of-class (phrase-cons role domain-class?)))
	    (cond
	      (place-reference-allowed?
	       (when no-item-allowed?
		 (compiler-bug
		   "attribute place reference"
		   "Cannot compile concludes or changes on attributes when the ~
                  frame containing the attribute is permitted to be missing.  ~
                  Required type = ~NT, attribute = ~a."
		   required-type role))
	       (setq role
		     (cond ((symbolp role)
			    ;; Record the attribute free-reference here because
			    ;; the role is being changed (and so won't be
			    ;; recorded in the cached-attribute emitter).  See
			    ;; note above.
			    (unless (type-specifications-could-intersect-p
				      domain-type '(structure))
			      (record-free-reference
				'attribute-of-class
				(phrase-cons role domain-class?)))
			    (compiler-warning-if-superseded-attribute role)
			    (setf (cdr argument-list)
				  (stack-cons
				    (choose-stack-node-instructions-and-types
				      (make-stack-node-instruction
					'push-constant role)
				      'symbol)
				    nil))
			    (incff arg-count)
			    (phrase-list
			      'attribute-frame-or-place-reference nil))
			   (class-qualified-name-role-p
                            (record-free-reference
                              'class-qualified-attribute-of-class
                              (phrase-list
                                (third role) (second role) domain-class?))
			    (compiler-warning-if-superseded-attribute
			      (third role))
			    (phrase-cons
			      'class-qualified-name-frame-or-place-reference
			      (cdr-of-cons role)))
			   ;; Replaces the attribute-value role with the frame
			   ;; or place reference.  The second of the role is set
			   ;; to nil since it is specifies the type of the
			   ;; attribute and not the attribute name.  The
			   ;; attribute name is the second domain of the
			   ;; attribute-value role.
			   ;; The attribute free-reference is not recorded
			   ;; because attribute-value role is an indirect
			   ;; attribute reference.  (The name of the attribute
			   ;; is evaluated.)
			   (attribute-value-role-p
			    (phrase-list
			      'attribute-frame-or-place-reference nil))
			   (nth-element-role-p
			    (phrase-list 'element-frame-or-place-reference nil))
			   (t role)))
	       (setf (stack-node-instruction-extra-info
		       stack-node-instruction)
		     role)
	       (setq value-type '(or (class item) (place-reference))))
	      (nth-element-role-p
	       (setq value-type
		     (or (and domain-class?
			      (g2-list-or-array-class-element-type
				domain-class? t))
			 'item-or-datum)))
              (attribute-value-role-p
               (setq value-type
                     (or (type-specification-of-role role)
                         'item-or-datum)))
	      (t
	       (setq value-type 'item-or-datum))))
	  (let ((result-type? (type-specification-of-role role))
		(domain-types
		  (loop for argument in argument-list
			collect (primary-type-of-type-specification
				  (stack-node-value-type argument))
			  using phrase-cons)))
	    (record-free-references-of-role role domain-types)
	    (setq value-type (or result-type? 'item-or-datum)))))
    
    ;; new harness here
    (setq value-type
	  ;; The optimized role servers do not have the role inverses
	  ;; required for rules.  (ghw/rh 8/19/98)
	  (cond ((of-class-p *current-computation-frame* 'rule)
		 (setf (stack-node-instruction-chosen-instruction
			 stack-node-instruction)
		       nil)
		 value-type)
		(t (choose-optimized-evaluate-role-instruction
		     stack-node-instruction argument-list value-type
		     no-item-allowed? unknown-allowed?))))
    (setq value-type
	  (maybe-add-unknown
	    (maybe-add-no-item value-type no-item-allowed?)
	    unknown-argument?))
    (setf (stack-node-value-type stack-node-instruction)
	  value-type)))
 




;;; The function `compiler-warning-if-superseded-attribute' issues a compiler
;;; warning if the given attribute is a system attribute that has been renamed.

;;; The note is issued as a compiler warning because we don't want to have a
;;; frame note for KB's that had previously loaded without warning (i.e., before
;;; the attribute was renamed).  Therefore, the warning is only given when the
;;; item referring to the attribute is compiled again.
	     
(defun compiler-warning-if-superseded-attribute (attribute)
  (when (attribute-previously-put-in-attribute-tables-p attribute)
    (compiler-warning
      "the attribute ~a ~a" attribute
      frame-note-for-superseded-attributes-1)))






(declare-instruction-for-optimizer
  'giver-of-value
  '(no-wait-states
    cannot-read-local-variables
    cannot-write-local-variables
    cannot-read-roles
    cannot-write-roles))

;;; The giver-of-value instruction holds a class name in the extra info slot.
;;; This instruction ensures that its argument is of the given class, and
;;; registers its own type as the return type of its argument.

(def-preferred-instruction-chooser giver-of-value
  (let* ((no-item-allowed?
	   (type-specification-subtype-p '(no-item) required-type))
	 (unknown-allowed?
	   (type-specification-subtype-p '(unknown-datum) required-type))
	 (no-item-implies-unknown-allowed?
	    (type-specification-subtype-p '(no-item-implies-unknown) required-type))
	 (type
	   (maybe-add-no-item-implies-unknown
	     (maybe-add-unknown
	       (maybe-add-no-item
		 (make-class-type-specification extra-info)
		 no-item-allowed?)
	       unknown-allowed?)
	     no-item-implies-unknown-allowed?))
	 (argument-list (stack-node-argument-nodes stack-node-instruction)))
    (record-free-reference 'class extra-info)
    (setf (car argument-list)
	  (choose-stack-node-instructions-and-types
	    (car-of-cons argument-list)
	    type))
    (setf (stack-node-value-type stack-node-instruction)
	  (stack-node-value-type (car-of-cons argument-list)))))




;;; first attempt at declaring instruction action for the optimizer


(declare-instruction-for-optimizer
  'push-from-surrounding-local-var
  '(no-wait-states
    cannot-write-local-variables
    reads-only-local-variables-specified-by-argument
    local-var-read-accessor get-stack-node-extra-info
    cannot-read-roles
    cannot-write-roles
    cost 1))

;;; The push-from-surrounding-local-var instruction holds a local var
;;; specification in the extra-info slot.

;;; Note that the var-spot to be pushed from is stored in the extra-info slot of
;;; this instruction.

(def-preferred-instruction-chooser push-from-surrounding-local-var
  (let* ((type? (var-spot-type
		  extra-info
		  lexically-visible-code-bodies))
	 (no-item-allowed?
	   (type-specification-subtype-p '(no-item) required-type)))
    (when (null type?)
      (compiler-bug
	"instruction chooser"
	"No type could be determined for var-spot ~a."
	extra-info)
      (setq type? required-type))
    (setf (stack-node-value-type stack-node-instruction)
	  (maybe-add-no-item type? no-item-allowed?))))

(declare-instruction-for-optimizer
  'copy-into-surrounding-local-var
  '(no-wait-states
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor get-stack-node-extra-info
    cannot-read-local-variables
    cannot-read-roles
    cannot-write-roles))




;;; The `copy-into-surrounding-local-var' stack node instruction takes as its
;;; argument a stack-node.  It will copy the value returned by that stack-node
;;; into a local var, and then return the value from this stack node.  The
;;; specification for which local var to copy into is held within the extra-info
;;; slot of the stack node instruction.

(def-preferred-instruction-chooser copy-into-surrounding-local-var
  (let* ((type? (var-spot-type
		  extra-info
		  lexically-visible-code-bodies))
	 (argument-list (stack-node-argument-nodes stack-node-instruction)))
    (when (null type?)
      (compiler-bug
	"copy into surrounding local var instruction chooser"
	"No type could be determined for var-spot ~a."
	extra-info)
      (setq type? required-type))
    (setf (car argument-list)
	  (choose-stack-node-instructions-and-types
	    (car-of-cons argument-list)
	    (make-type-specification-intersection
	      required-type
	      (add-secondary-type-specifications type? required-type))
	    nil
	    (stack-node-free-reference-type stack-node-instruction)))
    (setf (stack-node-value-type stack-node-instruction)
	  (stack-node-value-type (car argument-list)))))




;;; Within assign-local-var statements, if in the expression a single reference
;;; is made to the value of the local var being assigned, then that reference is
;;; implemented using this instruction.  Instead of copying the value inthe
;;; local var, this instruction moves that value onto the stack, clearing out
;;; the value within the local var as it does so.

(declare-instruction-for-optimizer
  'move-from-surrounding-local-var
  '(no-wait-states
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor get-stack-node-extra-info
    reads-only-local-variables-specified-by-argument
    local-var-read-accessor get-stack-node-extra-info
    cannot-read-roles
    cannot-write-roles))



;;; The `move-from-surrounding-local-var' stack node instruction takes no
;;; arguments, but contains a var-spot in its extra info that holds the location
;;; from which to take its value.  It pushes the value from the var-spot
;;; location onto the top of the stack, then sets a NIL into the var-spot
;;; location from which it came.  Note that the value on the stack is not a
;;; copy, but is the actual object that had previously been in the var-spot
;;; location.

(def-preferred-instruction-chooser move-from-surrounding-local-var
  (let* ((type? (var-spot-type
		  extra-info
		  lexically-visible-code-bodies))
	 (no-item-allowed?
	   (type-specification-subtype-p '(no-item) required-type)))
    (when (or (null type?)
	      no-item-allowed?)
      (compiler-bug
	"instruction chooser"
	"In move-from-surrounding-local-var, no type could be determined or  ~
           no-item allowed.  Var-spot ~a, type = ~a."
	extra-info
	required-type)
      (setq type? required-type))
    (setf (stack-node-value-type stack-node-instruction) type?)))




;;; The coerce-to-datum instruction is emitted by the add-ensure-type function.
;;; This instruction should ensure that its argument is a variable-or-parameter
;;; if unknown is allowed as a return type, or that the argument is a parameter,
;;; if unknown is not allowed.

;;; The return type of this instruction is either datum, or (or datum
;;; (unknown-datum)).  If the class of the argument to this function is known to
;;; be a subclass of variable-or-parameter, then the type of datum returned by
;;; this instruction should determined by the types of datum that can be held in
;;; that argument.

;;; In the implementation below there is a problem.  I would like to be able to
;;; push down into the arguments to this operation the fact that it must be an
;;; instance of a class which could produce the required datum type.  This could
;;; offer users messages about obviously incorrect class results.  However, the
;;; ensure type instruction cannot handle complex and/or/not class type
;;; specifications, especially when they combine class and datum types.  So,
;;; this function can only propagate downward the requirement that arguments be
;;; item-or-datum, when the argument could be a datum.  Weird.  The
;;; coerce-to-datum instruction itself must then be prepared to accept
;;; item-or-datum, and do the right thing at run-time.  -jra 4/24/91


(declare-instruction-for-optimizer
  'coerce-to-datum
  '(no-wait-states
    cannot-write-local-variables
    cannot-read-local-variables
    cannot-write-roles
    cannot-read-roles))

(def-preferred-instruction-chooser coerce-to-datum
  (declare (ignore extra-info))
  (let* ((stripped-required-type
	   (primary-type-of-type-specification required-type))
	 (argument-list (stack-node-argument-nodes stack-node-instruction))
	 (argument-node (car-of-cons argument-list))
	 (argument-type (stack-node-value-type argument-node))
	 (unknown-allowed?
	   (type-specification-subtype-p '(unknown-datum) required-type))
	 (no-item-allowed?
	   (type-specification-subtype-p '(no-item) required-type))
	 (no-item-implies-unknown?
	   (type-specification-subtype-p '(no-item-implies-unknown) required-type))
	 (argument-could-be-datum?
	   (type-specifications-could-intersect-p 'datum argument-type))
	 (stripped-desired-value-type (if (eq stripped-required-type 'float)
					  'number
					  stripped-required-type))
	 (desired-primary-type-of-sub-node?
	   (when (datum-type-specification-p stripped-required-type)
	     (if unknown-allowed?
		 (type-specification-returning-datum-type-or-unknown
		   stripped-desired-value-type t)
		 (type-specification-returning-datum-type
		   stripped-desired-value-type t))))
	 (required-type-of-sub-node
	   (maybe-add-no-item-implies-unknown 
	     (maybe-add-no-item
	       (maybe-add-unknown
		 (cond (argument-could-be-datum?
			'item-or-datum)
		       ((class-type-specification-p
			  desired-primary-type-of-sub-node?)
			desired-primary-type-of-sub-node?)
		       (unknown-allowed?
			'(class variable-or-parameter))
		       (t
			'(class parameter)))
		 unknown-allowed?)
	       no-item-allowed?)
	     no-item-implies-unknown?)))
    (setq argument-node
	  (choose-stack-node-instructions-and-types
	    argument-node required-type-of-sub-node t
	    desired-primary-type-of-sub-node?))
    (setf (car argument-list) argument-node)
    (setq argument-type (stack-node-value-type argument-node))
    (let ((held-type? (type-specification-held-in-type argument-type)))
      (setf (stack-node-value-type stack-node-instruction)
	    (if (null held-type?)
		(if unknown-allowed?
		    '(or datum (unknown-datum))
		    (maybe-add-no-item 'datum no-item-allowed?))
		held-type?)))))

(declare-instruction-for-optimizer
  'coerce-no-item-to-unknown
  '(no-wait-states
    cannot-write-local-variables
    cannot-read-local-variables
    cannot-write-roles
    cannot-read-roles))


;;; The coerce-no-item-to-unknown instruction is used to ensure that expressions
;;; allowing unknown and no-item which receive no-item as arguments do not try
;;; to execute an evaluator with no-item as the argument.

(def-preferred-instruction-chooser coerce-no-item-to-unknown
  (declare (ignore extra-info))
  (let ((argument-list (stack-node-argument-nodes stack-node-instruction)))
    (setf (car argument-list)
	  (choose-stack-node-instructions-and-types
	    (car argument-list)
	    required-type
	    t
	    (stack-node-free-reference-type stack-node-instruction)))
    (let ((value-type (stack-node-value-type (car argument-list))))
      (setf (stack-node-value-type stack-node-instruction)
	    (type-specification-minus-type
	      (maybe-add-unknown
		value-type
		(and (type-specification-not-subtype-p '(unknown-datum) value-type)
		     (type-specification-subtype-p '(no-item) value-type)))
	      '(no-item))))))




;;; The ensure-type instruction is used to type-check or coerce its argument
;;; into its required type.  At chooser time, this instruction should just
;;; propagate its required value type down the tree.


(declare-instruction-for-optimizer
  'ensure-type
  '(no-wait-states
    cannot-write-local-variables
    cannot-read-local-variables
    cannot-write-roles
    cannot-read-roles))


(def-preferred-instruction-chooser ensure-type
  (declare (ignore extra-info))
  (let ((argument-node
	  (car-of-cons (stack-node-argument-nodes stack-node-instruction)))
	(return-type nil))
    (setq argument-node
	  (choose-stack-node-instructions-and-types
	    argument-node required-type t
	    (stack-node-free-reference-type stack-node-instruction)))
    (setf (car (stack-node-argument-nodes stack-node-instruction))
	  argument-node)
    (setq return-type (stack-node-value-type argument-node))
    (cond
      ((type-specification-subtype-p return-type required-type)
       (setf (stack-node-value-type stack-node-instruction) return-type))
      ((and (type-specification-subtype-p '(no-item) return-type)
	    (type-specification-subtype-p
	      (type-specification-minus-type return-type '(no-item))
	      required-type))
       (setf (stack-node-value-type stack-node-instruction)
	     (type-specification-union-minus-type return-type '(no-item))))
      (t
       (setq required-type
	     (type-specification-minus-type required-type '(no-item-implies-unknown)))
       (when (and (type-specification-subtype-p '(unknown-datum) required-type)
		  (type-specification-not-subtype-p
		    '(unknown-datum) return-type))
	 (setq required-type
	       (type-specification-minus-type required-type '(unknown-datum))))
       (when (and (type-specification-subtype-p '(no-item) required-type)
		  (type-specification-not-subtype-p
		    '(no-item) return-type))
	 (setq required-type
	       (type-specification-minus-type required-type '(no-item))))
       ;; This didn't work since it removed integer when the required type was
       ;; float.  -jra 2/1/92

       ;; Fixes have been made to type-specifictaion-minimal-required-type,
       ;; reintroducing it.  -jra 9/26/96
       (setq required-type
	     (type-specification-minimal-required-type
	       required-type return-type))
       (setf (stack-node-value-type stack-node-instruction)
	     required-type)))))




;;; The function `type-specification-minimal-required-type' takes a required
;;; type and a return type of an expression, where the return type and required
;;; type can intersect.  This function will return a required type with the
;;; portions of the previous required type which could not intersect and could
;;; not be be coerced removed.

(defun-simple type-specification-minimal-required-type (required-type return-type)
  (if (union-type-specification-p required-type)
      (loop with subsetted-required-type = required-type
	    for sub-required-type in (cdr required-type)
	    do
	(unless (or (type-specifications-could-intersect-p
		      sub-required-type return-type)
		    (and (valid-datum-type-specification-p sub-required-type)
			 (if (union-type-specification-p return-type)
			     (loop for sub-return-type in (cdr return-type)
				   thereis (datum-type-specifications-could-be-coerced-p
					     sub-return-type sub-required-type))
			     (datum-type-specifications-could-be-coerced-p
			       return-type sub-required-type))))
	  (setq subsetted-required-type
		(type-specification-minus-type
		  subsetted-required-type sub-required-type)))
	    finally
	      (return subsetted-required-type))
      required-type))



(def-preferred-instruction-chooser execute-normal-form-tree
  (declare (ignore extra-info))
  
  (let ((argument-nodes (stack-node-argument-nodes stack-node-instruction))
	(primary-value-type nil)
	(unknown-allowed?
	  (type-specification-subtype-p '(unknown-datum) required-type)))
    (loop for argument-cons on argument-nodes
	  with argument-type = nil	  
	  do
      (setf (car argument-cons)
	    (choose-stack-node-instructions-and-types
	      (car-of-cons argument-cons)
	      required-type
	      nil
	      (stack-node-free-reference-type stack-node-instruction)))
      
      (setq argument-type (stack-node-value-type (car-of-cons argument-cons)))

      ;; If no primary type or existing primary value type is a subtype of this
      ;; argument type, then replace the primary type with this argument type.
      (setq primary-value-type
	    (most-general-primary-type argument-type primary-value-type))
      (when (type-specification-subtype-p '(unknown-datum) argument-type)
	(setq unknown-allowed? t)))
    (cond (unknown-allowed?
	   (setf (stack-node-value-type stack-node-instruction)
		 (make-type-specification-union
		   primary-value-type '(unknown-datum))))
	  (t
	   (setf (stack-node-value-type stack-node-instruction)
		 primary-value-type)))))

;added by SoftServe

;Declaration: preferred instruction chooser for the call-procedure instruction

;Type: Lisp function (after macroexpansion)

;Purpose: choose instructions and their types for the whole stack-node tree

;Arguments: stack node tree

;Return behavior: returns top stack node instruction

;Users: byte code compiler

;Side effects: None

;Memory impact: None

(def-preferred-instruction-chooser call-procedure
  (declare (ignore required-type extra-info))
  (let* ((sub-nodes (stack-node-argument-nodes stack-node-instruction))
	 #+unused
	 (extra-info-second?
	   (and extra-info (consp extra-info) (cdr-of-cons extra-info)
		(car-of-cons (cdr-of-cons extra-info))))
	 #+unused
	 (symbol-designation?
	   (and (symbolp extra-info-second?) extra-info-second?))
	 (argument-nodes (cdr sub-nodes)))
    (setf (car sub-nodes)
	  (choose-stack-node-instructions-and-types
	    (car sub-nodes)
		'(or (class item) (unknown-datum))))
    (loop for arg-cons on argument-nodes do
      (setf (car arg-cons)
	    (choose-stack-node-instructions-and-types
	      (car arg-cons)
	      'item-or-datum)))
    (setf (stack-node-value-type stack-node-instruction) 'item-or-datum) 
))
;end of changes

;;; The call-function instruction is used to dispatch to user defined functions.
;;; Its result is of type datum, combined with unknown if it is allowed in the
;;; required type.  All of its arguments are of type item-or-datum, again
;;; allowing unknown when it is allowed of the function itself.

(def-preferred-instruction-chooser call-function
  (let* ((unknown-allowed?
	   (type-specification-subtype-p '(unknown-datum) required-type))
	 (no-item-implies-unknown-allowed?
	   (type-specification-subtype-p '(no-item-implies-unknown) required-type))
	 (no-item-allowed?
	   (type-specification-subtype-p '(no-item) required-type))
	 (arg-type
	   (maybe-add-no-item-implies-unknown
	     (maybe-add-no-item
	       (maybe-add-unknown 'item-or-datum unknown-allowed?)
	       no-item-allowed?)
	     no-item-implies-unknown-allowed?))
	 (unknown-arg? nil)
	 (sub-nodes (stack-node-argument-nodes stack-node-instruction))
	 (extra-info-second?
	   (and extra-info (consp extra-info) (cdr-of-cons extra-info)
		(car-of-cons (cdr-of-cons extra-info))))
	 (symbol-designation?
	   (and (symbolp extra-info-second?) extra-info-second?))
	 (argument-nodes (cdr sub-nodes)))
    (setf (car sub-nodes)
	  (choose-stack-node-instructions-and-types
	    (car sub-nodes)
	    (if unknown-allowed?
		'(or (class item) (unknown-datum))
		'(class item))))
    (when (and unknown-allowed?
	       (type-specification-subtype-p
		 '(unknown-datum)
		 (stack-node-value-type (car sub-nodes))))
      (setq unknown-arg? t))
    (loop for arg-cons on argument-nodes do
      (setf (car arg-cons)
	    (choose-stack-node-instructions-and-types
	      (car arg-cons)
	      arg-type))
      (when (and unknown-allowed?
		 (type-specification-subtype-p
		   '(unknown-datum)
		   (stack-node-value-type (car arg-cons))))
	(setq unknown-arg? t)))
    (when unknown-arg?
      (if (and extra-info (consp extra-info)
	       (setf (first extra-info)
		     (generate-new-stack-frame-var-spot 'datum)))
	  (setf (stack-node-instruction-extra-info stack-node-instruction)
		(phrase-list
		  (generate-new-stack-frame-var-spot 'datum)
		  nil))))
    (when (and symbol-designation?
	       ;; the next check ensures that we aren't issuing a free reference
	       ;; for a local name.
	       (eq (stack-node-operation (car sub-nodes))
		   'push-cached-item))
      (record-free-reference
	'function-call
	(phrase-list
	  symbol-designation?
	  (loop for argument-node in argument-nodes
		collect (type-specification-minus-type 
			  (type-specification-minus-type
			    (stack-node-value-type argument-node)
			    '(unknown-datum))
			  '(no-item))
		  using phrase-cons))))


    (setf (stack-node-value-type stack-node-instruction)
	  (maybe-add-unknown
	    (maybe-add-no-item	    
	      (maybe-add-unknown 'datum unknown-allowed?)
	      no-item-allowed?)
	    no-item-implies-unknown-allowed?))))


;;;





;;;; Stack Node Instruction Emitters




;;; The following declarations are for the stack node instruction emitters.

(def-stack-node-instruction-emitter dummy-instruction
  (declare (ignore stack-node-instruction extra-info byte-code-stream))
  nil)

(def-stack-node-instruction-emitter no-op
  (declare (ignore stack-node-instruction byte-code-stream extra-info))
  nil)

(def-stack-node-instruction-emitter push-constant
  (call-stack-instruction-emitter push-constant byte-code-stream extra-info)
  ;; we need to do this so that the push constant reclaimer doesn't
  ;; try to reclaim a recycled value
  (setf (stack-node-instruction-extra-info stack-node-instruction) nil))

;;; an extra reclaimer is necessary because evaluation-values are used
;;; in the extra info
(def-stack-node-instruction-reclaimer push-constant
    (reclaim-if-evaluation-value extra-info))

(def-stack-node-instruction-extra-info-copier push-constant
    (copy-if-evaluation-value (stack-node-instruction-extra-info instruction-original)))

(def-stack-node-instruction-emitter name-reference
  (call-stack-instruction-emitter name-reference
    byte-code-stream
    extra-info
    (type-specification-subtype-p
      '(no-item)
      (stack-node-value-type stack-node-instruction))))

(def-stack-node-instruction-emitter push-cached-item
  (let* ((name extra-info)
	 (stable-item? (if (dependent-compilation-p) (stable-name-p name) nil))
	 (required-type (stack-node-required-value-type stack-node-instruction)))
    (call-stack-instruction-emitter push-cached-item
      byte-code-stream
      extra-info
      (type-specification-subtype-p
	'(no-item)
	(stack-node-value-type stack-node-instruction)))
    ;; If this is not a stable reference, then record a free reference about the
    ;; types required for this node.  This recording was deferred to here from
    ;; the type chooser for push-cached-item so that we would know more
    ;; explicitly what the required type is.
    (unless stable-item?
      (record-free-reference
	'name-of-type
	(phrase-cons
	  name
	  (or (stack-node-free-reference-type stack-node-instruction)
	      (type-specification-minus-type 
		(type-specification-minus-type 
		  (type-specification-minus-type required-type '(unknown-datum))
		  '(no-item))
		'(no-item-implies-unknown))))))))

(defun get-denoted-item-name-if-any (stack-node-tree)
  (when (stack-node-instruction-p stack-node-tree)
    (let ((operation (stack-node-operation stack-node-tree)))
      (case operation
	((name-reference)
	 (stack-node-instruction-extra-info stack-node-tree))
	((push-cached-item)
	 (stack-node-instruction-extra-info stack-node-tree))
	((ensure-type)
	 (and (type-specifications-could-intersect-p
		(stack-node-required-value-type stack-node-tree)
		'(class item))
	      (get-denoted-item-name-if-any
		(car-of-cons (stack-node-argument-nodes stack-node-tree)))))
	(t nil)))))

(def-stack-node-instruction-emitter push-from-surrounding-local-var
  (if (type-specification-subtype-p
	'(no-item)
	(stack-node-required-value-type stack-node-instruction))
      (call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	byte-code-stream extra-info)
      (call-stack-instruction-emitter push-from-surrounding-local-var
	byte-code-stream extra-info)))




;;; The emitter for the stack node instruction `copy-into-surrounding-local-var'
;;; takes the argument on the stack, pushes a copy onto the stack, and then pops
;;; that copy off the stack and into the given var spot.  Note that this
;;; instruction has no trouble with values of type no-item, and that it doesn't
;;; change or worry about caching the stack-expiration.

(def-stack-node-instruction-emitter copy-into-surrounding-local-var
  (emit-stack-node-tree
    byte-code-stream
    (car (stack-node-argument-nodes stack-node-instruction)))
  (emit-instruction-byte-code byte-code-stream 'push-copy-of-top-of-stack)
  (call-stack-instruction-emitter pop-into-surrounding-local-var
    byte-code-stream extra-info))

(def-stack-node-instruction-emitter move-from-surrounding-local-var
  (declare (ignore stack-node-instruction))
  (call-stack-instruction-emitter move-from-surrounding-local-var
    byte-code-stream extra-info))




;;; The emitters for roles right now emit a generic role interpreter
;;; instruction.  They should be optimized to emit instructions for more
;;; specific roles in the future.  -jra 4/1/91

(def-stack-node-instruction-emitter evaluate-role-with-no-domain
  (call-stack-instruction-emitter evaluate-role-with-no-domain
    byte-code-stream
    extra-info
    (type-specification-subtype-p
      '(no-item)
      (stack-node-value-type stack-node-instruction))))

(def-stack-node-instruction-emitter evaluate-role
  (let ((argument-nodes (stack-node-argument-nodes stack-node-instruction))
	(domain-1-item-name? nil)
	(domain-1-value-type nil))
    (loop for argument-node in argument-nodes
          with first-domain? = t
	  do
      (emit-stack-node-tree byte-code-stream argument-node)
      (when first-domain?
	;; Note that the item name and domain class are needed when emitting the
	;; cached-attribute-value instruction.
	(setq domain-1-item-name?
	      (get-denoted-item-name-if-any argument-node))
	(setq domain-1-value-type
	      (stack-node-value-type argument-node)))
      (setq first-domain? nil))
    (call-stack-instruction-emitter evaluate-role
      byte-code-stream
      extra-info
      (length argument-nodes)
      (type-specification-subtype-p
	'(no-item)
	(stack-node-value-type stack-node-instruction))
      domain-1-item-name?
      domain-1-value-type
      (stack-node-instruction-chosen-instruction stack-node-instruction))))


;;; evaluate-role-implicit-scope
;;; pushes a copy of the top of stack into the appropriate var-spot
;;; which has been stored in extra info   --rdf 6/2/93
(def-stack-node-instruction-emitter evaluate-role-implicit-scope
  (let ((argument-nodes (stack-node-argument-nodes stack-node-instruction))
	var-spot last-val)
    (loop for argument-node in argument-nodes
	  do
      (emit-stack-node-tree byte-code-stream argument-node))

    (emit-instruction-byte-code byte-code-stream 'push-copy-of-top-of-stack)
    (setq var-spot extra-info)
    (setq last-val (call-stack-instruction-emitter pop-into-surrounding-local-var byte-code-stream var-spot))
    last-val
    ))



;;; The emitter for giver-of-value only emits the instructions for its
;;; arguments.  This instruction primarily has an effect during the type
;;; chooser phase of compilation.

(def-stack-node-instruction-emitter giver-of-value
  (declare (ignore extra-info))
  (loop for argument-node in (stack-node-argument-nodes stack-node-instruction)
	do
    (emit-stack-node-tree byte-code-stream argument-node)))




;;; The instruction `coerce-to-datum' emits one of several stack instructions,
;;; depending on its required and argument types.

;;; If the return type of the argument is a subtype of class parameter, emit a
;;; parameter value instruction.  If the return type of the argument is a
;;; subtype of class variable-or-parameter, and (unknown-datum) is a subtype of
;;; the required type, then emit a variable-value-or-unknown instruction.  If
;;; (unknown-datum) is a subtype of the required type, emit a
;;; coerce-to-datum-or-unknown instruction.  Finally, if none of the above were
;;; true, emit a coerce-to-datum instruction.

(def-expiration-source-operator coerce-to-datum)

(def-stack-node-instruction-emitter coerce-to-datum
  (declare (ignore extra-info))
  (let* ((argument-type
	   (stack-node-value-type
	     (car (stack-node-argument-nodes stack-node-instruction))))
	 (required-type (stack-node-required-value-type stack-node-instruction))
	 (no-item-allowed?
	   (type-specification-subtype-p '(no-item) required-type)))
    (loop for argument-node in (stack-node-argument-nodes stack-node-instruction)
	  do
      (emit-stack-node-tree byte-code-stream argument-node))
    (cond ((type-specification-subtype-p argument-type '(class parameter))
	   (emit-instruction-byte-code byte-code-stream 'parameter-value))
	  ((and (type-specification-subtype-p
		  argument-type '(class variable-or-parameter))
		(type-specification-subtype-p '(unknown-datum) required-type))
	   (emit-instruction-byte-code
	     byte-code-stream 'variable-value-or-unknown))
	  ((type-specification-subtype-p '(unknown-datum) required-type)
	   (call-stack-instruction-emitter coerce-to-datum-or-unknown
	     byte-code-stream
	     no-item-allowed?))
	  (t
	   (call-stack-instruction-emitter coerce-to-datum
	     byte-code-stream no-item-allowed?)))))




;;; The instruction `coerce-no-item-to-unknown' emits a machine instruction
;;; which looks at the value on the top of the stack.  If the value is no-item,
;;; then the global expiration is set to unknown.

(def-expiration-source-operator coerce-no-item-to-unknown)

(def-stack-node-instruction-emitter coerce-no-item-to-unknown
  (declare (ignore extra-info))
  (let ((argument-node (car (stack-node-argument-nodes stack-node-instruction))))
    (emit-stack-node-tree byte-code-stream argument-node)
    (unless (type-specification-not-subtype-p
	      '(no-item)
	      (stack-node-value-type argument-node))
      (call-stack-instruction-emitter funcall-instruction
	byte-code-stream 'coerce-no-item-to-unknown))))

;;;




;;; The instruction ensure-type is used to check that a value is an instance of
;;; a required type, or it is used to coerce one datum type to another.  Note
;;; that it cannot currently check for all kinds of type specifications.  The
;;; ones it can check are the datum-types, class types, the type item-or-datum,
;;; or an and of these types.

;;; The types that it can coerce are quantity to float, or integer to float.

;;; Further note that the rewriting of the stack-node-tree to perform unknown
;;; checking will ensure that this instruction never receives the type unknown
;;; datum, and therefore will never have to produce a value of the type unknown
;;; datum.

;;; Note that if this emitter changes, then the function check-ensure-type-nodes
;;; must change to mirror this function.

;;; Also note that the type check should be performed to ensure that the value
;;; is a subtype of the stack-node-value-type of this node, not the
;;; stack-node-required-value-type.  This is because the ensure-type chooser can
;;; occasionally determine a more strict return type for this node than the
;;; required type.  The more strict return type is always a subtype of the
;;; required type and so performing the more strict test can be done.  -jra
;;; 12/6/91

(def-stack-node-instruction-emitter ensure-type
  (declare (ignore extra-info))
  (let* ((argument-nodes (stack-node-argument-nodes stack-node-instruction))
	 (raw-argument-type
	   (stack-node-value-type (car-of-cons argument-nodes)))
	 (argument-type
	   (type-specification-minus-type raw-argument-type '(unknown-datum)))
	 (raw-required-type
	   (stack-node-value-type stack-node-instruction))
	 (required-type
	   (type-specification-minus-type
	     (type-specification-minus-type raw-required-type '(unknown-datum))
	     '(no-item-implies-unknown))))
    ;; If the argument type includes no-item, and the remainder of the argument
    ;; type without the no-item is a subtype of the required type, then change
    ;; the required type to be the remainder of the argument type.  This
    ;; effectively makes the type check more stringent, but preserves the
    ;; specific type information from the argument.
    (when (and (type-specification-subtype-p '(no-item) argument-type)
	       (not (type-specification-subtype-p '(no-item) required-type)))
      (let ((argument-remainder
	      (type-specification-minus-type argument-type '(no-item))))
	(when (type-specification-subtype-p argument-remainder required-type)
	  (setq required-type argument-remainder))))
    (loop for argument-node in argument-nodes do
      (emit-stack-node-tree byte-code-stream argument-node))
    (cond
      ((type-specification-subtype-p argument-type required-type)
       nil)
      ((and (type-specification-subtype-p argument-type 'integer)
	    (type-specification-subtype-p required-type 'float))
       (emit-instruction-byte-code byte-code-stream 'coerce-integer-to-float))
      ((and (type-specification-subtype-p argument-type 'number)
	    (type-specification-subtype-p required-type 'float))
       (emit-instruction-byte-code byte-code-stream 'coerce-quantity-to-float))
     ;added by SoftServe
       ((and (type-specification-subtype-p argument-type 'integer)
	    (type-specification-subtype-p required-type 'long))
       (emit-instruction-byte-code byte-code-stream 'coerce-integer-to-long))
     ;end of changes
      ((or (type-specifications-could-intersect-p argument-type required-type)
	   (and (type-specification-subtype-p required-type 'float)
		(type-specifications-could-intersect-p argument-type 'number)))
       (call-stack-instruction-emitter type-check byte-code-stream required-type))
      (t
       ;; In this case we know that this call to ensure type will result in an
       ;; error being signalled at runtime.  This can occur in valid code when
       ;; the optimizer tightens the known type of the argument type, and we
       ;; then emit dead code that is never executed due to user logic that
       ;; keeps us out of this branch.  In a perfect world, the optimizer would
       ;; be symmetric about type proofs and branching proofs, in which case
       ;; this code would be eliminated by dead-code analysis.  Somewhere over
       ;; the rainbow...  -jra, 5/9/95
       (call-stack-instruction-emitter type-check byte-code-stream required-type)))))




;;; The function `check-ensure-type-nodes' is called as the last thing the
;;; compiler does to a stack node tree.  This function examines all
;;; "ensure-type" stack instructions, which get emitted when there is possible
;;; doubt as to whether an argument type will match a required type.  This
;;; function checks that the types are OK, but calls compiler-error if there is
;;; a problem.  Note that the implementation of this function must mirror the
;;; emitter for ensure-type, defined just above.

(defun check-ensure-type-nodes (stack-node)
  (loop for argument-node in (stack-node-argument-nodes stack-node)
	do
    (check-ensure-type-nodes argument-node))
  (when (and (stack-node-instruction-p stack-node)
	     (eq (stack-node-operation stack-node) 'ensure-type))
  
    (let* ((argument-nodes (stack-node-argument-nodes stack-node))
	   (raw-argument-type
	     (stack-node-value-type (car-of-cons argument-nodes)))
	   (argument-type
	     (type-specification-minus-type raw-argument-type '(unknown-datum)))
	   (raw-required-type
	     (stack-node-value-type stack-node))
	   (required-type
	     (type-specification-minus-type
	       (type-specification-minus-type raw-required-type '(unknown-datum))
	       '(no-item-implies-unknown))))
      ;; If the argument type includes no-item, and the remainder of the
      ;; argument type without the no-item is a subtype of the required
      ;; type, then change the required type to be the remainder of the
      ;; argument type.  This effectively makes the type check more
      ;; stringent, but preserves the specific type information from the
      ;; argument.
      (when (type-specification-subtype-p '(no-item) argument-type)
	(let ((argument-remainder
		(type-specification-minus-type argument-type '(no-item))))
	  (when (type-specification-subtype-p argument-remainder required-type)
	    (setq required-type argument-remainder))))
      (cond
	((type-specification-subtype-p argument-type required-type)
	 ;; No problem.
	 nil)
	((and (type-specification-subtype-p argument-type 'integer)
	      (type-specification-subtype-p required-type 'float))
	 ;; Coercion to float from integer, no problem.
	 nil)
       ;added by SoftServe
       	((and (type-specification-subtype-p argument-type 'integer)
	      (type-specification-subtype-p required-type 'long))
	 ;; Coercion to long from integer, no problem.
	 nil)
       ;end of changes
	((and (type-specification-subtype-p argument-type 'number)
	      (type-specification-subtype-p required-type 'float))
	 ;; Coercion to float from number, no problem.
	 nil)
	((or (type-specifications-could-intersect-p argument-type required-type)
	     (and (type-specification-subtype-p required-type 'float)
		  (type-specifications-could-intersect-p argument-type 'number)))
	 ;; Runtime type check, which could be no problem.
	 nil)
	(t
	 ;; Big problem.
	 (compiler-error
	   "The result of an expression was required to be of type ~NT, but it returned type ~NT."
	   required-type argument-type))))))


(declare-instruction-for-optimizer
  'execute-normal-form-tree
  '(no-wait-states
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor get-stack-node-extra-info
    cannot-read-local-variables
    cannot-read-roles
    cannot-write-roles
    normal-form-tree-like-flow))

;;; The instruction `execute-normal-form-tree' has as its argument nodes, a
;;; trivial tree which is the computed result of this expression, and the rest
;;; of the list contains expiration returning trees which were the leaves of
;;; this normal form tree.  The extra-info slot contains a list of variables for
;;; caching the values of the expiration nodes.  Note that the variable list is
;;; in reverse order to the argument list, which will turn out to be useful.

;;; The argument nodes should be executed.  If the global expiration is unknown
;;; after their evaluation, all values returned by the nodes should be popped
;;; off the stack, a NIL should be pushed, and we should branch past the end of
;;; this instruction.  Otherwise, the values should be popped into the given
;;; variables.  Note that the values are now in reverse order on the stack, so
;;; the already reversed variable list is traversed directly to emit the pop
;;; instructions.  After the values have been cached, we should execute the
;;; instructions in the trivial tree.

(def-stack-node-instruction-emitter execute-normal-form-tree
  (let* ((known-tag (generate-new-goto-tag))
	 (end-of-expression-tag (generate-new-goto-tag))
	 (reversed-variables extra-info)
	 (arg-nodes (stack-node-argument-nodes stack-node-instruction))
	 (trivial-tree (car arg-nodes))
	 (expiration-nodes (cdr arg-nodes)))
    (cond
      ((or (null reversed-variables) (null expiration-nodes))
       (compiler-bug
	 "normal form tree emitter"
	 "Normal form tree has no arguments with expirations."))
      (t
       ;; Emit the expiration expressions, and push all of their values onto the
       ;; stack.
       (loop for node in expiration-nodes do
	 (emit-stack-node-tree byte-code-stream node))
       ;; If the global expiration has not been minimized to nil in the
       ;; execution of the above expressions, branch to the completion of the
       ;; trivial tree execution.
       (call-stack-instruction-emitter branch-long-if-known byte-code-stream known-tag)
       ;; Else, if the value is unknown, pop all of the values off the stack,
       ;; push a NIL in thier place, and branch to the end of the expression.
       (call-stack-instruction-emitter pop-values
	 byte-code-stream (length expiration-nodes))
       (call-stack-instruction-emitter push-nones byte-code-stream 1)
       (call-stack-instruction-emitter branch-long byte-code-stream end-of-expression-tag)
       ;; If the values are known, pop the values of the expiration expressions
       ;; into their variables.  Note that the values are on the stack in
       ;; reverse order, and so are popped off into the variables in reverse
       ;; order.
       (register-tag-in-byte-code-stream byte-code-stream known-tag)
       (loop for var-spot? in reversed-variables do
	 (when var-spot?
	   (call-stack-instruction-emitter pop-into-surrounding-local-var
	     byte-code-stream var-spot?)))
       ;; Evaluate the computation tree, leaving its value on the top of the
       ;; stack, and branch to the end of this expression's code.
       (emit-stack-node-tree byte-code-stream trivial-tree)
       ;; Register the unknown tag location, pop off all the values computed by
       ;; the expiration source expressions, and push NIL as the final value.
       (register-tag-in-byte-code-stream
	 byte-code-stream end-of-expression-tag)))))

;added by SoftServe
(def-expiration-special-form call-procedure)

;Declaration: instruction emitter for the call-procedure instruction

;Type: Lisp function (after macroexpansion)

;Purpose: emit the call-procedure instruction and its arguments

;Arguments: instruction node to emit

;Return behavior: implicit Nil

;Side effects: none

;Memory impact: none

(def-stack-node-instruction-emitter call-procedure
  (declare (ignore extra-info))
  (let* ((sub-nodes (stack-node-argument-nodes stack-node-instruction))
	 (argument-nodes (cdr sub-nodes))
	 #+unused
	 (expiration-cache?
	   (and extra-info (consp extra-info) (car-of-cons extra-info))))
    (loop for arg-node in argument-nodes do
      (emit-stack-node-tree byte-code-stream arg-node))
    
    (emit-stack-node-tree byte-code-stream (car sub-nodes))

    (emit-instruction-byte-code byte-code-stream 'call-procedure)
    (write-byte-code-to-stream byte-code-stream (length argument-nodes))))

;end of changes

;;; The instruction `call-function' calls a user-defined, tabular, or foreign
;;; function and returns its value.

(declare-instruction-for-optimizer
     'call-function
     '(no-wait-states
       cannot-write-local-variables
       cannot-read-local-variables
       cannot-write-roles
       cannot-read-roles
       evaluate-first-arg-last))

(def-expiration-special-form call-function)

(def-stack-node-instruction-emitter call-function
  (let* ((sub-nodes (stack-node-argument-nodes stack-node-instruction))
	 (argument-nodes (cdr sub-nodes))
	 (unknown-allowed?
	   (type-specification-subtype-p
	     '(unknown-datum)
	     (stack-node-required-value-type stack-node-instruction)))
	 (no-item-allowed?
	   (type-specification-subtype-p
	     '(no-item)
	     (stack-node-required-value-type stack-node-instruction)))
	 (expiration-cache?
	   (and extra-info (consp extra-info) (car-of-cons extra-info)))
	 (end-of-function-tag
	   (when expiration-cache? (generate-new-goto-tag)))
	 (known-args-tag
	   (when expiration-cache? (generate-new-goto-tag))))
    ;; Cache the global expiration if the args or the function fetch itself can
    ;; be unknown.
    (when expiration-cache?
      (emit-instruction-byte-code byte-code-stream 'push-expiration)
      (call-stack-instruction-emitter pop-into-surrounding-local-var
	byte-code-stream expiration-cache?)
      (emit-instruction-byte-code byte-code-stream 'reset-expiration))
    ;; Push the arguments
    (loop for arg-node in argument-nodes do
      (emit-stack-node-tree byte-code-stream arg-node))
    ;; Push the unknown allowed? flag.
    (call-stack-instruction-emitter push-constant
      byte-code-stream
      (if unknown-allowed?
	  (make-evaluation-truth-value truth)
	  (make-evaluation-truth-value falsity)))
    ;; Push the no-item-allowed? flag.
    (call-stack-instruction-emitter push-constant
      byte-code-stream
      (if no-item-allowed?
	  (make-evaluation-truth-value truth)
	  (make-evaluation-truth-value falsity)))
    ;; Was; push the argument count.
    ;; Argument count is now in the instruction stream, not
    ;; on the stack. -alatto, 8/13/98
    ;; (call-stack-instruction-emitter push-constant
    ;;  byte-code-stream
    ;;  (make-evaluation-integer (length argument-nodes)))
    ;; Push the function itself.
    (emit-stack-node-tree byte-code-stream (car sub-nodes))
    ;; If the args or function itself can be unknown, check the stack
    ;; expiration.  If expired pop all values but one off the stack and branch
    ;; to the end.  Note that we don't have to put the global expiration back
    ;; since we know the total expiration is unknown.
    (when expiration-cache?
      (call-stack-instruction-emitter branch-long-if-known byte-code-stream known-args-tag)
      (call-stack-instruction-emitter pop-values
	byte-code-stream (+f (length argument-nodes) 2))
      (call-stack-instruction-emitter branch-long byte-code-stream end-of-function-tag)
      (register-tag-in-byte-code-stream byte-code-stream known-args-tag))
    ;; Call the function.
    (emit-instruction-byte-code byte-code-stream 'call-function)
    (write-byte-code-to-stream byte-code-stream (length argument-nodes))
    ;; Push the cached global expiration, if any, back into the result.
    (when expiration-cache?
      (call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	byte-code-stream expiration-cache?)
      (emit-instruction-byte-code byte-code-stream 'minimize-expiration)
      (register-tag-in-byte-code-stream
	byte-code-stream end-of-function-tag))))

;;;






;;;; Stack Node Tree Emitting



;;; The function `emit-stack-node-tree' takes a byte-code-stream and a tree of
;;; stack nodes already compiled with compile-expression-into-stack-nodes.  This
;;; is the interface to the procedure instruction emitters which need to emit
;;; stack node trees.

;;; It will emit the bytes for this node tree into the byte-code-stream such
;;; that the value computed by the stack node is left on the top of the stack at
;;; the end of the execution of this tree.  Note that the stack-expiration
;;; should be NEVER (the default) at the beginning of execution of this tree.

(defun emit-stack-node-tree (byte-code-stream stack-node)
  (let ((stack-frame-vars (stack-node-stack-frame-vars-needed stack-node)))
    (when (>f stack-frame-vars 0)
      (call-stack-instruction-emitter push-nones byte-code-stream stack-frame-vars))
    (if (stack-node-instruction-p stack-node)
	(let* ((operation (stack-node-operation stack-node))
	       (emitter (stack-node-instruction-emitter operation)))
	  (if emitter
	      (funcall-simple-compiled-function
		emitter stack-node byte-code-stream
		(stack-node-instruction-extra-info stack-node))
	      (compiler-bug
		"stack node emitter"
		"The stack node instruction ~a had no byte code emitter."
		operation)))
	(let* ((chosen-description (stack-node-chosen-evaluator stack-node))
	       (no-item-possible nil)
	       tag-after-evaluator)
	  (loop for argument-node in (stack-node-argument-nodes stack-node)
		do
	    (emit-stack-node-tree byte-code-stream argument-node)
	    (when (type-specification-subtype-p '(no-item)
						(stack-node-value-type
						  argument-node))
	      (setq no-item-possible t)))
	  (when (and no-item-possible
		     (not (can-accept-no-item-args chosen-description)))
	    (setq tag-after-evaluator (generate-new-goto-tag))
	    (call-stack-instruction-emitter allow-no-item-for-evaluator
					    byte-code-stream
					    (length (stack-node-argument-nodes stack-node))
					    tag-after-evaluator))
	  (cond
	    ((null chosen-description)
	     (compiler-bug
	       "stack node emitter"
	       "A preferred evaluator had not been chosen for ~a.")
	     (stack-node-operation stack-node))
	    ;; An in-line evaluator.
	    ((evaluator-in-line-p chosen-description)
	     (write-byte-code-to-stream
	       byte-code-stream
	       (evaluator-number chosen-description)))
	    ;; Else, its a funcalled evaluator.
	    (t
	     (call-stack-instruction-emitter funcall-evaluator
					     byte-code-stream (evaluator-number chosen-description))))
	  (when tag-after-evaluator
	    (register-tag-in-byte-code-stream
	      byte-code-stream tag-after-evaluator))))
    (when (>f stack-frame-vars 0)
      (call-stack-instruction-emitter pop-copy-down-the-stack
				      byte-code-stream stack-frame-vars))))

(defun-simple can-accept-no-item-args (chosen-description)
  (memq (evaluator-name chosen-description)
	'(receives-a-value is-moved is-moved-by-the-user is-moved-by-g2 is-resized-by-the-user
	  is-activated is-deactivated is-enabled is-disabled loses-its-value
	  is-created generic-event generic-directly-disconnected-from
	  directly-disconnected-from indirectly-connected-to
	  indirectly-disconnected-from is-of-class)))

;;; The function `emit-stack-node-tree-or-nil' is used to emit stack node trees
;;; or the evaluation value nil.  This is used to improve the readability of the
;;; emitters.

(defun emit-stack-node-tree-or-nil (byte-code-stream stack-node?)
  (if stack-node?
      (emit-stack-node-tree byte-code-stream stack-node?)
      (call-stack-instruction-emitter push-constant
	byte-code-stream (make-evaluation-symbol nil))))




;;; The function `emit-operator-of-type' takes a symbol naming an operation and
;;; a type specification (which must be a subtype of number) and emits the
;;; instructions to execute the given operation on the given type.  This
;;; function is used in the emitters for aggregators when determining which
;;; operation to emit to combine aggregated results.

(defun emit-operator-of-type (byte-code-stream operator type-specification-1)
  (let ((preferred-evaluator? nil)
	(type-specification
	  (type-specification-minus-type
	    (type-specification-minus-type
	      type-specification-1
	      '(unknown-datum))
	    '(no-item))))
    (loop for evaluator-description in (stack-evaluators operator)
	  do
      (when (and (type-specification-subtype-p
		   type-specification
		   (evaluator-result-type evaluator-description))
		 (or (null preferred-evaluator?)
		     (<=f (evaluator-instruction-precedence evaluator-description)
			  (evaluator-instruction-precedence preferred-evaluator?))))
	(setq preferred-evaluator? evaluator-description)))
    (cond ((null preferred-evaluator?)
	   (compiler-bug
	     "op-code-for-operator-of-type"
	     "Can't find evaluator for ~a of ~NT." operator type-specification))
	  ((evaluator-in-line-p preferred-evaluator?)
	   (write-byte-code-to-stream
	     byte-code-stream (evaluator-number preferred-evaluator?)))
	  (t
	   (call-stack-instruction-emitter funcall-evaluator
	     byte-code-stream (evaluator-number preferred-evaluator?))))))






;;;; Converting Expressions to Stack Node Trees




;;; The function `convert-expression-to-stack-node-tree' takes a parsed
;;; s-expression and converts it into a stack-node tree.  This function should
;;; be called from special form converters, to convert sub-expressions into node
;;; trees.

;;; FUNCTIONALITY CHANGE: Note that the converter for user defined functions
;;; recurses the name back into convert-designation-to-stack-node-tree.  This
;;; means that if there is a local name in this scope which matches the name of
;;; the called function, then the local name will provide the value.  In 2.0,
;;; function calls always ignored all local variables and always looked globally
;;; for a function with that name.  This makes it conform with procedures and
;;; all other name reference semantics.  -jra 5/30/91

(defvar already-mutated-evaluators nil)

(defun convert-expression-to-stack-node-tree (expression)
  (let ((expression-bound-local-names expression-bound-local-names))
    (cond
      ((phrase-float-p expression)
       (make-stack-node-instruction
	 'push-constant
	 (copy-evaluation-float-from-phrase-float expression)))
      ((phrase-long-p expression)
       (make-stack-node-instruction
	 'push-constant
         (copy-evaluation-long-from-phrase-long expression)))
      ((or (phrase-sequence-p expression) ; phrase sequence/structure as constant
	   (phrase-structure-p expression)) ;   (c.f., special forms for same)
       (make-stack-node-instruction
	 'push-constant
	 (let ((evaluation-sequence-or-structure
		 (copy-for-slot-value expression)))
	   #+development
	   (test-assertion
	     (or (evaluation-sequence-p evaluation-sequence-or-structure)
		 (evaluation-structure-p evaluation-sequence-or-structure)))
	   evaluation-sequence-or-structure)))
      ;; this case can occur only when compiling substituted
      ;; parse trees for inlining purposes
      ((or (evaluation-sequence-p expression)
	   (evaluation-structure-p expression))
       (make-stack-node-instruction
	 'push-constant
	 (let ((evaluation-sequence-or-structure
		 (copy-evaluation-value expression)))
	   #+development
	   (test-assertion
	     (or (evaluation-sequence-p evaluation-sequence-or-structure)
		 (evaluation-structure-p evaluation-sequence-or-structure)))
	   evaluation-sequence-or-structure)))
      ((truth-value-phrase-p expression)
       (make-stack-node-instruction
	 'push-constant
	 (let ((value (truth-value-phrase-value expression)))
	   (cond
	     ((eq value truth) evaluation-true-value)
	     ((eq value falsity) evaluation-false-value)
	     (t (make-evaluation-truth-value value))))))
      ((consp expression)
       (let ((operator (car expression)))
	 (cond
	   ((designation-p expression)
	    (convert-designation-to-stack-node-tree expression))
	   ((symbolp operator)
	    (let* ((special-form-converter?
		     (stack-special-form-converter operator))
		   (stack-evaluator-descriptions?
		     (stack-evaluators operator)))
	      (cond
		(special-form-converter?
		 (funcall-simple-compiled-function
		   (compiled-function-in-place special-form-converter?)
		   expression))
		(stack-evaluator-descriptions?
		 (let ((node nil)
		       (current-evaluator-number 0) 
		       (first-evaluator (first stack-evaluator-descriptions?)))
		   (setq current-evaluator-number (evaluator-number first-evaluator))
		   (when (>f current-evaluator-number dispatch-instruction-number)
		     (setf (evaluator-number first-evaluator) dispatch-instruction-number)
		     (setf (evaluator-arguments first-evaluator) 
			   (nconc (copy-list-using-gensym-conses
				    (evaluator-arguments first-evaluator))
				  (gensym-list 'integer)))
		     (setf (evaluator-dispatch-code first-evaluator)
			   (-f current-evaluator-number dispatch-instruction-number))	
		     (setq already-mutated-evaluators
			   (nconc (gensym-list operator) already-mutated-evaluators)))
		   (setq node (make-stack-node
			        operator
				stack-evaluator-descriptions?))
		   (setf (stack-node-argument-nodes node)
			 (make-stack-argument-nodes
			   operator
			   (if (member operator already-mutated-evaluators)
			       (nconc (copy-list-using-gensym-conses (cdr expression))
				      (gensym-list (evaluator-dispatch-code first-evaluator)))
			     (cdr expression))
			   stack-evaluator-descriptions?))
		   node))
		(t
		 (loop with node = (make-stack-node-instruction
				     'call-function
				     (phrase-list
				       nil
				       (if (symbolp operator) operator nil)))
		       for argument in (cdr expression)
		       collect (convert-expression-to-stack-node-tree argument)
			 into arg-nodes using stack-cons
		       finally
			 (setf (stack-node-argument-nodes node)
			       (stack-cons
				 (convert-designation-to-stack-node-tree
				   operator)
				 arg-nodes))
			 (return node))))))
	   ((numberp operator)
	    (make-stack-node-instruction
	      'push-constant
	      (make-evaluation-quantity operator)))
	   ((phrase-float-p operator)
	    (make-stack-node-instruction
	      'push-constant
	      (copy-evaluation-float-from-phrase-float operator)))
	   ((phrase-long-p operator)
	    (make-stack-node-instruction
	      'push-constant
	      (copy-evaluation-long-from-phrase-long operator)))
	   (t
	    (mal-formed-stack-expression expression)
	    ;; Return a dummy node.
	    (make-dummy-stack-node)))))
      ((fixnump expression)
       (make-stack-node-instruction
	 'push-constant (make-evaluation-integer expression)))
      ((text-string-p expression)
       (make-stack-node-instruction
	 'push-constant (make-evaluation-text expression)))
      ;; The following makes my skin crawl.  There is no type specific copier
      ;; from Common Lisp strings into wide strings, so we'll dig ourselves
      ;; further into the inescapable hole in the following.  -jra 6/10/96
      ((stringp expression)
       (make-stack-node-instruction
	 'push-constant (make-evaluation-text expression)))
      ((gensym-float-p expression)
       (make-stack-node-instruction
	 'push-constant (make-evaluation-float expression)))
      ((gensym-long-p expression)
       (make-stack-node-instruction
	 'push-constant (make-evaluation-long expression)))
      ((eq expression 'does-not-exist)
       (make-stack-node-instruction
	 'push-constant nil))
      
      ;; Only needed for a few legacy situations, e.g., the grammar in QUERIES
      ;; -- try entering "show on a workspace every item".  The prospect of
      ;; fixing the so-called G2-LAMBDA expressions is not tremendously
      ;; exciting.  (MHD 5/16/97)
      ((eq expression 'true)
       ;; (dwarn "STACK-COMP: Raw TRUE expression obsolete!")
       (make-stack-node-instruction
 	 'push-constant evaluation-true-value))
      ((eq expression 'false)
       ;; (dwarn "STACK-COMP: Raw FALSE expression obsolete!")
       (make-stack-node-instruction
 	 'push-constant evaluation-false-value))
      
      ((symbolp expression)
       (convert-designation-to-stack-node-tree expression))
      (t
       (mal-formed-stack-expression expression)
       (make-dummy-stack-node)))))



;;; The variable `compile-reference-to-system-slot' is bound to non-nil
;;; when it is ok to compile a designation which contains a reference to
;;; a system-defined slot.  In most cases, it is not ok.  An exception is the
;;; the change-the-text-of-attribute action.  The compiler for this
;;; action will bind this variable to non-nil.  Note that there are
;;; other expressions that allow references to system-slots, but don't
;;; need to bind this variable because they have special parses.  These
;;; include "text of <slot>" and "the <system-attribute> of
;;; <designation>".

(defvar compile-reference-to-system-slot nil)



;;; The function `convert-designation-to-stack-node-tree' takes a designation
;;; and converts it into a stack-node-tree representation, and then returns that
;;; stack node.  This is an interval function of the converter.

;;; During the conversion local-names are converted into var-spot reference
;;; nodes, and role service is converted to individual instructions.


;; The following is a switch to turn off the cached-name optimization in
;; development.  It does not always work with cell-arrays.  - cpm, 9/7/93 It
;; does now.  -jra 12/1/94

#+development
(defvar turn-off-cached-name nil)

(defun convert-designation-to-stack-node-tree (designation)
  (cond
    ((not (designation-p designation))
     (mal-formed-stack-designation designation)
     (make-dummy-stack-node)))

  (cond
    ((symbolp designation)
     (let ((var-spot-or-symbol (resolve-stack-name-reference designation)))
       (cond 
	 ((not (symbolp var-spot-or-symbol))
	  (make-stack-node-instruction
	    'push-from-surrounding-local-var var-spot-or-symbol))
	 #+development
	 (turn-off-cached-name
	  (make-stack-node-instruction 'name-reference designation))
	 (t
	  (make-stack-node-instruction 'push-cached-item designation)))))
    
    ((not (simple-role-p (role-of-designation designation)))
     (let* ((role (role-of-designation designation))
	    role-node
	    (role-name (get-name-provided-by-role role))
	    (new-designation
	      (stack-cons (car designation)
			  (stack-cons (simple-role-of-role role)
				      (cddr designation))))
	    (stack-list (stack-list
			  (convert-designation-to-stack-node-tree
			    new-designation))))
       (reclaim-stack-cons (cdr new-designation))
       (reclaim-stack-cons new-designation)
       (unless (variable-spot-and-description-for-local-name role-name)
	 (generate-new-variable-spot
	   (if (valid-type-specification-p
		 (type-specification-of-role (role-of-designation designation)))
	       (type-specification-of-role (role-of-designation designation))
	       'item-or-datum) role-name))
       (setq role-node
	     (make-stack-node-instruction
	       'copy-into-surrounding-local-var	       
	       (variable-spot-and-description-for-local-name role-name)))
       (setf (stack-node-argument-nodes role-node) stack-list)
       role-node))
     
    ((=f (length designation) 2)
     (let ((role (role-of-designation designation)))
       (cond ((not (simple-role-p role))
	      (let ((simple-role (simple-role-of-role role))) 
		(compiler-error
		  "All local names for procedures must be declared at ~
                   the top of the procedure definition.  This ~
                   designation could not be compiled: ~ND."
		  designation)
		(record-free-references-of-role simple-role)
		(make-dummy-stack-node)))
	     ((and (quantifier-requires-previous-reference-p
		     (car designation))
		   (symbolp role))
	      (let ((bound-reference?
		      (assoc designation expression-bound-local-names
			     :test 'equal)))
		(if bound-reference?
		    (let ((var-spot (cdr bound-reference?)))
		      (make-stack-node-instruction
			'push-from-surrounding-local-var
			var-spot))
		    (progn
		      (compiler-error
			"No local name could be found for \"~ND\"."
			designation)
		      (make-dummy-stack-node)))))

	     (t

	      (make-stack-node-instruction
		'evaluate-role-with-no-domain
		role)))))
    (t
     (gensym-dstruct-bind ((quantifier role . domain-list) designation)
       (when (not (simple-role-p role)) 
	 (compiler-error
	   "All local names for procedures must be declared at the top of the ~
            procedure definition.  This designation could not be ~
            compiled: ~ND."
	   designation)
	 (setq role (simple-role-of-role role)))
       (let* ((domain-stack-node-arguments
		(loop for domain in domain-list
		      collect 
			(convert-expression-to-stack-node-tree domain)
				 using stack-cons))
	      (role-node
		(if (eq quantifier 'giver-of-value)
		    (make-stack-node-instruction 'giver-of-value role)
		    (make-stack-node-instruction 'evaluate-role role))))
	 (when (and (neq quantifier 'giver-of-value)
		    (null compile-reference-to-system-slot)
		    (symbolp role)
		    (=f (length domain-list) 1)
		    (unauthorized-system-slot-p role)
		    ;; or is it an alias that we should worry about?
		    )
	   (compiler-error
	     "The reference \"~ND\" cannot be compiled because it references a ~
              system defined attribute, ~a.  You can use \"the text of\" ~
              around references to system defined attributes to get the text ~
              that is visible in attribute tables for that attribute."
	     designation
	     role))
	 (setf (stack-node-argument-nodes role-node)
	       domain-stack-node-arguments)
	 role-node)))))











;;; The function `resolve-stack-name-reference' takes a symbol found in an
;;; expression or designation which may be a local name.  If it is a generated
;;; local or a symbol naming a local name, this function will return a phrase
;;; cons var-spot reference.  If the given symbol is not a local name, then the
;;; name itself is returned.  This function can also accept references to
;;; compiler generated local names, which are conses.  This function uses EQ to
;;; check name equality, so the same cons must be passed in to get a reference
;;; to a generated local name.

(defun resolve-stack-name-reference (possible-local-name)
  (let ((bound-var-spot? (assq possible-local-name
			       expression-bound-local-names)))
    (when bound-var-spot?
      (return-from resolve-stack-name-reference
	(cdr bound-var-spot?))))
  (or (variable-spot-and-description-for-local-name possible-local-name)
      possible-local-name))




;;; The functions `mal-formed-stack-expression', `mal-formed-stack-designation',
;;; and `make-dummy-stack-node' are used to signal compiler-errors
;;; about errors in the format seen by the converter and make a stack-node which
;;; will fool the remainder of the compile into believing it is there for some
;;; reason.

(defun mal-formed-stack-expression (expression)
  (if (consp expression)
      (let* ((operator (car expression))
	     (message
	       (twith-output-to-text-string 
		 (tformat "The malformed expression ~a (" operator)
		 (loop for thing = (cdr expression) then (cdr thing)
		       do
		   (cond ((null thing)
			  (twrite-string ")"))
			 ((consp thing)
			  (tformat " ~a" (car thing)))
			 (t
			  (tformat " . ~a" thing)))
		       until (atom thing))
		 (twrite-string " could not be compiled."))))
	(compiler-bug
	  "stack node converter"
	  message)
	(reclaim-text-string message))
      (compiler-bug
	"stack node converter"
	"The malformed expression ~a could not be compiled."
	expression)))

(defun mal-formed-stack-designation (designation)
  (compiler-bug
    "stack node converter"
    "The malformed designation ~a could not be compiled."
    designation))

(defun make-dummy-stack-node ()
  (make-stack-node-instruction 'dummy-instruction nil))




;;; Some operations are parsed such that they are combined in nary versions.
;;; The stack evaluator must execute them as fixed argument length operations,
;;; and so they are cut down into binary operations.  The function
;;; `nary-operator-stack-implemented-as-binary' is a predicate which identifies
;;; those operations whose nary arguments should be split up into binary
;;; operators.

(defun nary-operator-stack-implemented-as-binary (operator)
  (not (null (memq operator '(+ * max min)))))




;;; The functiom `make-stack-argument-nodes' takes an operator symbol, a list of
;;; argument expressions, a list of evaluator-descriptions for the operator, and
;;; possibly a function-template for the operation.  This function returns a
;;; stack-cons list of stack-nodes representing the arguments.  If the operator
;;; is an nary operator which is implemented as a binary operator, this function
;;; will split arguments lists longer than two into nary operators, combining
;;; from left to right.  The list of evaluator-descriptions is for the nodes
;;; generated to perform binary combinations of nary operators.

(defun make-stack-argument-nodes
       (operator argument-expressions evaluator-descriptions)
  (if (and (nary-operator-stack-implemented-as-binary operator)
	   (>f (length argument-expressions) 2))
      (make-binary-stack-argument-nodes
	operator argument-expressions evaluator-descriptions)
      (loop for argument in argument-expressions
	    collect (convert-expression-to-stack-node-tree argument)
			 using stack-cons)))




;;; The function `make-binary-stack-argument-nodes' takes an operator, an
;;; argument-list greater than two elements long, and a list of
;;; evaluator-descriptions for the operator.  This function returns a stack-cons
;;; list of two stack-nodes which combine all the given arguments in
;;; left-to-right order.  This function is what actually converts nary arguments
;;; lists for operations into binary encodings of that operation.

(defun make-binary-stack-argument-nodes
       (operator argument-list evaluator-descriptions)
  (let ((arguments-length (length argument-list)))
    (stack-list
      (make-stack-node-combining-arguments
	operator argument-list evaluator-descriptions
	arguments-length (-f arguments-length 2))
      (convert-expression-to-stack-node-tree (car (last argument-list))))))

(defun make-stack-node-combining-arguments
       (operator argument-list evaluator-descriptions argument-count
	combine-index)
  (let ((new-node (make-stack-node operator evaluator-descriptions)))
    (setf (stack-node-argument-nodes new-node)
	  (stack-list
	    (if (=f combine-index 1)
		(convert-expression-to-stack-node-tree (first argument-list))
		(make-stack-node-combining-arguments
		  operator argument-list evaluator-descriptions argument-count
		  (-f combine-index 1)))
	    (convert-expression-to-stack-node-tree
	      (nth combine-index argument-list))))
    new-node))

(defun most-general-argument-type-list (stack-node)
  (let* ((most-general nil)
	 (required-type (stack-node-required-value-type stack-node))
	 (unknown-allowed?
	   (type-specification-subtype-p '(unknown-datum) required-type))
	 (no-item-allowed?
	   (type-specification-subtype-p '(no-item) required-type))
	 (no-item-implies-unknown-allowed?
	    (type-specification-subtype-p '(no-item-implies-unknown) required-type)))
    (loop with evaluator-descriptions =
	    (stack-node-evaluator-descriptions stack-node)
	  with argument-list-length =
	    (length (stack-node-argument-nodes stack-node))
	  for description in evaluator-descriptions
	  for argument-types = (evaluator-arguments description)
	  do
      (when (=f (length argument-types) argument-list-length)
	(when (or (null most-general)
		  (more-general-argument-list-description-p
		    argument-types
		    most-general))
	  (setq most-general argument-types))))
    (if (or no-item-allowed? unknown-allowed? no-item-implies-unknown-allowed?)
	(loop for type in most-general
	      collect (maybe-add-no-item-implies-unknown
			(maybe-add-no-item
			  (maybe-add-unknown type unknown-allowed?)
			  no-item-allowed?)
			no-item-implies-unknown-allowed?)
		       using phrase-cons)
	most-general)
;    (if (type-specification-subtype-p
;	  '(unknown-datum)
;	  (stack-node-required-value-type stack-node))
;	(loop for type in most-general
;	      collect (make-type-specification-union
;			type '(unknown-datum))
;		       using phrase-cons)
;	most-general)
    ))

(defun more-general-argument-list-description-p
       (superior-arg-list inferior-arg-list)
  (and (=f (length superior-arg-list) (length inferior-arg-list))
       (loop for superior-arg-type in superior-arg-list
	     for inferior-arg-type in inferior-arg-list
	     always (type-specification-subtype-p
		      inferior-arg-type superior-arg-type))))




;;; The function `choose-preferred-stack-evaluator' is used to select from
;;; amongst the set of evaluator-descriptions for the operation called for.  The
;;; choice is made based on the preference of the evaluator implementation and
;;; compatibility of the produced type with the desired type, compatibility of
;;; the evaluator argument desired types and the argument node produced types,
;;; and propagation of float types between the arguments of type contagion
;;; obeying operations.

;;; The effect of this function is to mutate the given stack-node to set the
;;; chosen-evaluator and value-type slots.

;;; First, if the required type allows unknown-datum, that fact is noted, and
;;; the required type for any argument is also allowed to contain unknown datum.
;;; Second, the known required type is cached by removing unknown-datum from the
;;; required type, if it is present.

;;; A preferred evaluator is chosen in one of the following ways.  If the
;;; evaluator has floating point type contagion, the known-required-type is
;;; a subtype of float, and the evaluator has an operator which returns float,
;;; then the floating point returning operator is used, 

(defun choose-preferred-stack-evaluator (stack-node)
  (let* ((operation (stack-node-operation stack-node))
	 (required-type (stack-node-required-value-type stack-node))
	 (evaluator-descriptions (stack-node-evaluator-descriptions stack-node))
	 (unknown-allowed?
	   (type-specification-subtype-p '(unknown-datum) required-type))
	 (no-item-allowed?
	   (type-specification-subtype-p '(no-item) required-type))
	 (no-item-implies-unknown-allowed?
	   (type-specification-subtype-p '(no-item-implies-unknown) required-type))
	 (known-required-type (primary-type-of-type-specification required-type))
	 (argument-nodes (stack-node-argument-nodes stack-node))
	 (argument-count (length (the list argument-nodes)))
	 (preferred-evaluator? nil))
    (loop for description in evaluator-descriptions
	  for argument-types = (evaluator-arguments description)
	  do
      ;; If the result type of the evaluator is acceptible, the arg-nodes are
      ;; acceptible to the evaluator, and this evaluator is at least as
      ;; preferable as any other, then this evaluator is the most preferrable so
      ;; far.
      (when (and (=f (length (the list argument-types)) argument-count)
		 (stack-evaluator-nodes-produce-types-p
		   argument-nodes argument-types
		   unknown-allowed?
		   no-item-allowed? no-item-implies-unknown-allowed?)
		 (or (null preferred-evaluator?)
		     (<=f (evaluator-instruction-precedence description)
			  (evaluator-instruction-precedence
			    preferred-evaluator?))))
	(setq preferred-evaluator? description)))
    ;; Note that integer operators have a greater precedence than float
    ;; operators, and so will stop coercion from proceeding down through an
    ;; integer instruction tree.
    (let* ((arg-float-type (if (float-contagion-stack-operator-p operation)
			       (maybe-add-no-item
				 (maybe-add-unknown 'float unknown-allowed?)
				 no-item-allowed?)
			       nil))
	   (float-contagion-evaluator?
	     (when (and arg-float-type
			(or (type-specification-subtype-p
			      known-required-type 'float)
			    (loop for node in argument-nodes
				  thereis
				  (type-specification-subtype-p
				    (stack-node-value-type node)
				    arg-float-type))))
	       (loop for description in evaluator-descriptions
		     for evaluator-arguments = (evaluator-arguments description)
		     do
		 (when (and (=f (length evaluator-arguments) argument-count)
			    (loop for arg-type in evaluator-arguments
				  always
				  (type-specification-subtype-p
				    arg-type 'float)))
		   (return description)))))
	   (integer-contagion-evaluator?
	     (when (and (float-contagion-stack-operator-p operation)
			(type-specification-subtype-p
			  known-required-type 'integer))
	       (loop for description in evaluator-descriptions
		     for evaluator-arguments = (evaluator-arguments description)
		     do
		 (when (and (=f (length evaluator-arguments) argument-count)
			    (loop for arg-type in evaluator-arguments
				  always (type-specification-subtype-p
					   arg-type 'integer)))
		   (return description)))))
	   (arg-integer-type
	     (and integer-contagion-evaluator?
		  (maybe-add-no-item
		    (maybe-add-unknown 'integer unknown-allowed?)
		    no-item-allowed?)
		  ))
           ;added by SoftServe
      	   (long-contagion-evaluator?
	     (when (and (float-contagion-stack-operator-p operation)
			(type-specification-subtype-p
			  known-required-type 'long))
	       (loop for description in evaluator-descriptions
		     for evaluator-arguments = (evaluator-arguments description)
		     do
		 (when (and (=f (length evaluator-arguments) argument-count)
			    (loop for arg-type in evaluator-arguments
				  always (type-specification-subtype-p
					   arg-type 'long)))
		   (return description)))))
	   (arg-long-type
	     (and long-contagion-evaluator?
		  (maybe-add-no-item
		    (maybe-add-unknown 'long unknown-allowed?)
		    no-item-allowed?)
		  )))
      (when (and long-contagion-evaluator?
		 (or (null preferred-evaluator?)
		     (<f (evaluator-instruction-precedence
			   long-contagion-evaluator?)
			 (evaluator-instruction-precedence
			   preferred-evaluator?))))
	(loop for arg-node-cons on argument-nodes do
	  (setf (car arg-node-cons)
		(choose-stack-node-instructions-and-types
		  (car arg-node-cons) arg-long-type)))
	(setq preferred-evaluator? long-contagion-evaluator?))
      ;end of SoftServe changes
      (when (and integer-contagion-evaluator?
		 (or (null preferred-evaluator?)
		     (<f (evaluator-instruction-precedence
			   integer-contagion-evaluator?)
			 (evaluator-instruction-precedence
			   preferred-evaluator?))))
	(loop for arg-node-cons on argument-nodes do
	  (setf (car arg-node-cons)
		(choose-stack-node-instructions-and-types
		  (car arg-node-cons) arg-integer-type)))
	(setq preferred-evaluator? integer-contagion-evaluator?))
      (when (and float-contagion-evaluator?
		 (or (null preferred-evaluator?)
		     (<f (evaluator-instruction-precedence
			   float-contagion-evaluator?)
			 (evaluator-instruction-precedence
			   preferred-evaluator?))))
	(loop for arg-node-cons on argument-nodes do
	  (setf (car arg-node-cons)
		(choose-stack-node-instructions-and-types
		  (car arg-node-cons) arg-float-type)))
	(setq preferred-evaluator? float-contagion-evaluator?))
      (cond
	(preferred-evaluator?
	 (setf (stack-node-chosen-evaluator stack-node)
	       preferred-evaluator?)
	 (loop with unknown-arguments? = nil
	       for node-cons on argument-nodes
	       for node = (car-of-cons node-cons)
	       for node-type = (stack-node-value-type node)
	       for evaluator-argument-type in
	       (evaluator-arguments preferred-evaluator?)
	       do
	   (when (type-specification-subtype-p '(unknown-datum) node-type)
	     (setq unknown-arguments? t))
	       finally
		 (setf (stack-node-value-type stack-node)
		       (maybe-add-unknown
			 (evaluator-result-type preferred-evaluator?)
			 unknown-arguments?))))
	(t
	 (compiler-bug
	   "preferred evaluation chooser"
	   "No evaluator was choosen for ~a."
	   operation)) ))))

(defun stack-evaluator-nodes-produce-types-p
       (argument-nodes argument-types unknown-allowed? no-item-allowed?
		       no-item-implies-unknown-allowed?)
  (loop for arg-type in argument-types
	for arg-node in argument-nodes
	for node-type = (stack-node-value-type arg-node)
	do
    (when unknown-allowed?
      (setq node-type
	    (type-specification-minus-type node-type '(unknown-datum))))
    (when no-item-allowed?
      (setq node-type
	    (type-specification-minus-type node-type '(no-item))))
    (when no-item-implies-unknown-allowed?
      (setq node-type
	    (type-specification-minus-type node-type '(no-item-implies-unknown))))
	always
	  (node-type-produces-argument-type-p node-type arg-type)))

(defun node-type-produces-argument-type-p (node-type argument-type)
  (or (type-specification-subtype-p node-type argument-type)
      (and (type-specification-subtype-p argument-type '(class item))
	   (type-specifications-could-intersect-p
	     node-type argument-type))))

;; It seems confusing that we don't accept all type intersections here, but I'm
;; too frightened to touch this function right now.  -jra 9/2/94




;;; The function `choose-preferred-stack-instruction' takes a
;;; stack-instruction-node and performs an operation analagous to what
;;; choose-preferred-stack-evaluator does, but does it to instructions.  Mostly
;;; what this means is that the value-type of the node is set, since
;;; optimizations to particular instructions are done in the emitting phase.
;;; The other thing done is that free references get registered.

(defun choose-preferred-stack-instruction (stack-node-instruction)
  (let* ((operation (stack-node-operation stack-node-instruction))
	 (chooser-function (preferred-instruction-chooser operation)))
    (cond (chooser-function
	   (funcall-simple-compiled-function
	     (compiled-function-in-place chooser-function)
	     stack-node-instruction)
	   nil)
	  (t
	   (compiler-bug
	     "preferred evaluator instruction chooser"
	     "The stack node instruction ~a had no preferred instruction ~
              chooser."
	     operation)
	   (setf (stack-node-value-type stack-node-instruction)
		 nil)))
    nil))




;;; The function `choose-stack-node-instructions-and-types' takes a stack-node
;;; tree and a required type for the value to be returned from evaluation of
;;; that tree.  This function will modify the required type slot of the given
;;; node, the value type slot of the given node, and will recurse onto the
;;; argument nodes of the given node.  If the value type of this node is not
;;; determined to be a subtype of the required type, then the given node will be
;;; wrapped with a new stack node to perform the runtime type check.  This
;;; behavior can be suppressed with the supress-ensure-type? argument.  In all
;;; cases, this function will return either its argument stack node or the stack
;;; ensure type node wrapped around the given node.

;;; This function first finds the most general required argument
;;; type pattern of the evaluator descriptions for this operation.  Once the
;;; type requirements have been determined this function then recurses on the
;;; arguments to this node.  If all nodes have compiled correctly (check
;;; compiler-errors) it attempts to find an evaluator description for
;;; this node which will operate on the actual return types of the node
;;; arguments.  If more than one evaluator will work, it chooses amongst them
;;; based on the instruction preferences in the evaluator descriptions.  Once
;;; this is done a result type is determined for this node.  If the result type
;;; satisfies the required type, then this operation is done and the node is
;;; returned.  If the result type does not satisfy the required type but can be
;;; coerced such that it does, then a new node is created to do the coercion
;;; operation.  This node is inserted as an argument to the new node, and the
;;; new node is returned as the result of this operation.

;;; added the force-reevaluation? optional argument so that the optimizer could
;;; do nifty  things with type propagation. This required assuring that all
;;; choosers could be run multiple times without causing untoward effects.

;;; This required modifying the following choosers
;;; and
;;; or
;;; has-a-current-value
;;; has-a-value
;;; current-value-of
;;; value-of
;;; first-that-has-a-current-value
;;; first-that-has-a-value
;;; simulated-value-of

;;; and all aggregator-instruction-choosers
;;; * there-exists-literal
;;; * for-every-literal
;;; * sum
;;; * product
;;; * count
;;; * aggregated-average
;;; * maximum
;;; * minimum

(defun choose-stack-node-instructions-and-types
    (node-tree required-type &optional called-from-ensure-type? free-reference-type?)
  #+development
  (assert (valid-type-specification-p required-type)
	  (required-type)
	  "Bad type ~a given to choose-stack-node-instructions-and-types."
	  required-type)
  (setf (stack-node-required-value-type node-tree) required-type)
  (setf (stack-node-free-reference-type node-tree) free-reference-type?)
  (cond ((stack-node-instruction-p node-tree)
	 (choose-preferred-stack-instruction node-tree))
	(t
	 (unless (loop for node in (stack-node-argument-nodes node-tree)
		       always (stack-node-value-type node))
	   (loop for sub-node-cons on (stack-node-argument-nodes node-tree)
		 for sub-type-cons?
		 = (most-general-argument-type-list node-tree)
		     then (cdr sub-type-cons?)
		 for sub-type
		 = (or (car sub-type-cons?)
		       '(or item-or-datum (unknown-datum) (no-item)))
		 do
	     (setf (car sub-node-cons)
		   (choose-stack-node-instructions-and-types
		     (car sub-node-cons) sub-type))))
	 (choose-preferred-stack-evaluator node-tree)))
  (when (null (stack-node-value-type node-tree))
    (compiler-bug
      "instruction and type chooser"
      "No value type chosen for operation ~a."
      (stack-node-operation node-tree))
    (setf (stack-node-value-type node-tree) 'item-or-datum))
  (when (and (not called-from-ensure-type?)
	     (or (not (type-specification-subtype-p
			(stack-node-value-type node-tree) required-type))
		 (and (type-specification-subtype-p
			'(no-item-implies-unknown) required-type)
		      (type-specification-subtype-p
			'(no-item) (stack-node-value-type node-tree)))))
    (setq node-tree
	  (add-ensure-type-stack-node-instruction node-tree required-type)))
  node-tree)




;;; The function `add-ensure-type-stack-node-instruction' takes a stack-node
;;; tree and a required-type, and either adds a node to the tree which will
;;; ensure that the required type is returned from the tree, or else this
;;; function mutates an existing ensure type node to contain the new type.

;;; Two nodes can actually be added to this node.  If the required type is a
;;; subtype of (or datum (unknown-datum)) and the value type is a subtype of (or
;;; (class item) (no-item), then a coerce-to-datum instruction is wrapped around
;;; the argument node.

(defun add-ensure-type-stack-node-instruction (stack-node required-type)
  (let ((coerce-to-datum-added? nil))
    (when (and (type-specification-subtype-p
		 '(no-item-implies-unknown) required-type)
	       (type-specification-subtype-p
		 '(no-item) (stack-node-value-type stack-node)))
      (let ((new-node
	      (make-stack-node-instruction 'coerce-no-item-to-unknown nil)))
	(setf (stack-node-argument-nodes new-node) (stack-list stack-node))
	(setq stack-node
	      (choose-stack-node-instructions-and-types
		new-node required-type t
		(stack-node-free-reference-type stack-node)))))
    (when (and (type-specification-subtype-p
		 (type-specification-minus-type 
		   (type-specification-minus-type required-type '(no-item))
		   '(no-item-implies-unknown))
		 '(or datum (unknown-datum)))
	       (type-specifications-could-intersect-p
		 '(class item) (stack-node-value-type stack-node)))
      (let ((new-node (make-stack-node-instruction 'coerce-to-datum nil)))
	(setq coerce-to-datum-added? t)
	(setf (stack-node-argument-nodes new-node) (stack-list stack-node))
	(setq stack-node
	      (choose-stack-node-instructions-and-types
		new-node required-type t
		(stack-node-free-reference-type stack-node)))))
    (when (or coerce-to-datum-added?
	      (not (or (type-specification-subtype-p
			 (stack-node-value-type stack-node)
			 required-type)
		       (and (stack-node-instruction-p stack-node)
			    (eq (stack-node-operation stack-node)
				'ensure-type)))))
      (let ((new-node (make-stack-node-instruction 'ensure-type nil)))
	(setf (stack-node-argument-nodes new-node)
	      (stack-list stack-node))
	(setq stack-node 
	      (choose-stack-node-instructions-and-types
		new-node required-type t
		(stack-node-free-reference-type stack-node)))))
    stack-node))



;;; The function `ensure-argument-types-satisfy-operators' takes a stack-node
;;; and checks that the value return types and required types for each node are
;;; compatible, or that they could be compatiable and the node which they differ
;;; on is an ensure-type stack-node-instruction, or one of its brethern,
;;; coerce-to-datum or coerce-no-item-to-unknown.

(defun ensure-argument-types-satisfy-operators (parent-node? stack-node)
  (loop for argument-node in (stack-node-argument-nodes stack-node)
	do
    (ensure-argument-types-satisfy-operators stack-node argument-node))
  (let* ((required-type (stack-node-required-value-type stack-node))
	 (return-type (stack-node-value-type stack-node))
	 (operation (stack-node-operation stack-node))
	 (returns-unknown?
	   (type-specification-subtype-p '(unknown-datum) return-type)))
    ;; Determine if all of the type requirements can be met.
    (unless (type-specification-subtype-p return-type required-type)
      (unless (cond ((eq (stack-node-operation stack-node) 'ensure-type)
		     (or (type-specifications-could-intersect-p
			   return-type required-type)
			 (datum-type-specifications-could-be-coerced-p
			   return-type required-type)))
		    ((eq (stack-node-operation stack-node) 'coerce-to-datum) 
		     (or (type-specifications-could-intersect-p
			   return-type required-type)
			 (type-specifications-could-be-coerced-p
			   return-type required-type)
			 (and parent-node?
			      (eq (stack-node-operation parent-node?)
				  'ensure-type))))
		    ((eq (stack-node-operation stack-node)
			 'coerce-no-item-to-unknown)
		     t)
		    (parent-node?
		     (or (eq (stack-node-operation parent-node?)
			     'ensure-type)
			 (eq (stack-node-operation parent-node?)
			     'coerce-to-datum)
			 (eq (stack-node-operation parent-node?)
			     'coerce-no-item-to-unknown)))
		    (t nil))

	(if parent-node?
	    (compiler-error
	      "An argument to ~a, which is required to be of type ~NT, was of ~
               type ~NT."
	      (stack-node-operation parent-node?)
	      required-type
	      return-type)
	    (compiler-error
	      "The operation ~a is required to produce a value of type ~NT, ~
               but instead produces values of type ~NT."
	      (stack-node-operation stack-node)
	      required-type
	      return-type))))
    ;; Set the node type and tree type for this node.
    (cond ((expiration-source-operator-p operation)
	   (setf (stack-node-type stack-node) 'source)
	   (cond ((not returns-unknown?)
		  (setf (stack-node-tree-type stack-node) 'trivial-tree))
		 ((loop for arg in (stack-node-argument-nodes stack-node)
			always
			  (eq (stack-node-tree-type arg) 'trivial-tree))
		  (setf (stack-node-tree-type stack-node) 'single-source-tree))
		 (t
		  (setf (stack-node-tree-type stack-node) 'source-tree))))
	  ((expiration-special-form-operator-p operation)
	   (setf (stack-node-type stack-node) 'special)
	   (if returns-unknown?
	       (setf (stack-node-tree-type stack-node) 'special-tree)
	       (setf (stack-node-tree-type stack-node) 'trivial-tree)))
	  (t
	   (setf (stack-node-type stack-node) 'minimizing)
	   (if returns-unknown?
		 (setf (stack-node-tree-type stack-node) 'normal-tree)
	       (setf (stack-node-tree-type stack-node) 'trivial-tree))))))




;;; The function `type-specifications-could-be-coerced-p' takes a value-type and
;;; a required-type which have already been determined to not possibly intersect
;;; and returns whether or not the value type could possibly be coerced to the
;;; required type.

;;; The possible coercions are a parameter to a datum, a variable-or-parameter
;;; to datum or unknown, an integer to a float, or a quantity or unknown to a
;;; float or unknown.  Note that when coercing any variable-or-parameter to a
;;; datum, we also have to check that the values possibly produced by that
;;; variable or parameter could intersect with or be coerced to the required
;;; value.

(defun type-specifications-could-be-coerced-p (value-type required-type)
  (cond
    ((type-specification-subtype-p required-type 'datum)
     (and (type-specifications-could-intersect-p
	    value-type '(class parameter))
	  (let ((held-type? (type-specification-held-in-type value-type)))
	    (or (null held-type?)		; Can't prove value type.
		(type-specifications-could-intersect-p
		  held-type? required-type)
		(datum-type-specifications-could-be-coerced-p
		  held-type? required-type)))))
    ((type-specification-subtype-p required-type '(or datum (unknown-datum)))
     (and (type-specifications-could-intersect-p
	    value-type '(class variable-or-parameter))
	  (let ((held-type? (type-specification-held-in-type value-type)))
	    (or (null held-type?)
		(type-specifications-could-intersect-p
		  held-type? required-type)
		(datum-type-specifications-could-be-coerced-p
		  held-type? required-type)))))))

(defun-simple datum-type-specifications-could-be-coerced-p
       (datum-value-type datum-required-type)
  (and (type-specification-subtype-p
	 datum-required-type '(or float (unknown-datum)))
       (type-specification-subtype-p
	 datum-value-type '(or number (unknown-datum)))
       (or (not (type-specification-subtype-p '(unknown-datum) datum-value-type))
	   (type-specification-subtype-p '(unknown-datum) datum-required-type))))






;;;; Transforming Stack Nodes Trees Whose Value May Be Unknown




;;; The following definitions will be useful in describing the behavior of the
;;; compiler and what happens when expressions whose values may be unknown are
;;; evaluated.  We will represent expressions as trees, where individual
;;; computations are nodes in the tree and values returning from these nodes are
;;; arcs.  The sub-arcs of a node are arguments to the node.  The goal of this
;;; discussion is to design a run-time model where most operations need not
;;; expend CPU time computing expirations or testing for argument types.  We'll
;;; define two kinds of leaf nodes within these trees (i.e.  nodes with no
;;; sub-arcs) and two kinds of nodes which contain subtrees (i.e.  intermediate
;;; nodes).

;;; Expression Tree and Node Definitions

;;; Leaf nodes always produce their expirations locally (i.e.  do not depend on
;;; the expirations of other nodes in the tree).  An example of this sort of
;;; node is a call to GET-CURRENT-VALUE on a variable.  We'll call these nodes
;;; `expiration source nodes'.

;;; There is a second kind of leaf node whose expiration is always NEVER.
;;; Constants in a expression, as well as operations like "the count of every
;;; <class>" fall in this category.  All leaf nodes in procedures actually fall
;;; into this category, since these will always have a value, or else signal an
;;; error.  Because these nodes cannot affect the expirations within larger
;;; trees of expirations (a call to minimum-expiration with one argument of
;;; "NEVER" always returns the other expiration), we'll call these nodes
;;; `expiration no-op nodes'.

;;; The first kind of intermediate node is one whose expiration is completely
;;; determined by the expirations of its arguments, with the node merely
;;; minimizing the argument expirations.  "+" is one example of this kind of
;;; operator, and it turns out that the vast majority of operators are of this
;;; sort.  Because these operators do not add anything unique to the expiration,
;;; we will be able to optimize them so that they do not perform expiration
;;; computations at all.  We'll call these nodes `expiration minimizing nodes'.

;;; Another type of intermediate node produces its expiration as a function of
;;; the values and expirations of its arguments, but computes its own expiration
;;; in some way more complicated than minimum.  These nodes will have to be
;;; handled specially by the compiler.  An example of this kind of node is the
;;; AND operation.  The expiration of AND is either: the expiration of the first
;;; FALSE argument, unknown if no argument is FALSE and the value of any
;;; argument is unknown, or the minimum of all arguments if all are TRUE.  We'll
;;; call these nodes `expiration special form nodes'.

;;; Given these node definitions we can make definitions about collections of
;;; these nodes -- tree definitions.  A typical collection of special interest
;;; is a tree containing only expiration no-op nodes as its leaves.  This tree
;;; will always have a value, and may be computed without regard to expirations,
;;; no matter what kinds of intermediate nodes are used.  We'll call these kinds
;;; of trees `trivial expiration trees'.  Note that compilations of expiration
;;; special form nodes can be simplified within these trees, since they don't
;;; have to compute expirations.

;;; Trees which contain only a single expiration source node at thier root and
;;; trivial trees below are handled specially, and are called `single source
;;; node trees'.

;;; Trees which contain an expiration source node at their root and trees other
;;; than trival trees below are called `source node trees'.

;;; Trees which contain any expiration source leaf nodes are more complicated.
;;; However, we can optimize these trees when all of the intermediate nodes are
;;; expiration minimizing nodes.  We'll call trees which have at least one
;;; expiration source leaf, any number (including zero) of expiration no-op
;;; nodes, at least one expiration minimizing intermediate node, and no
;;; expiration special form nodes `normal-form expiration trees'.

;;; The most complicated type of tree is one which contains some special form
;;; nodes and expiration source nodes.  These will be called `special-form
;;; trees'.  The following discussions cover the ways different types of trees
;;; should be compiled.

;;; Trivial expiration trees should be compiled as a normal stack machine would
;;; compile them.  If the global expiration is set to NEVER before the execution
;;; of expressions starts, then trival trees need never touch that value.

;;; Compilations of single expiration source node trees may also be done in the
;;; trivial way, since the source node can minimize its expiration against the
;;; global value and then be done.  When an expiration source node executes, it
;;; should push its value onto the top of the stack and minimize its expiration
;;; into the global expiration variable.

;;; Source node trees (i.e.  source nodes with arguments that may return
;;; unknown) are handled in the same way as normal form trees, except that the
;;; execution of the source node at the root of this tree can minimize its
;;; additional expiration with the global expiration variable.

;;; Compilations of normal form trees should be handled as follows.  First, all
;;; expiration source nodes for the sub-tree should be evaluated.  If the global
;;; expiration has been minimized down to unknown after all expiration source
;;; nodes have been attempted, then all but one of the values should be popped
;;; off the stack and branch should be executed to the end of the set of
;;; instructions for this tree.  (This leaves one value on the stack, as
;;; specified above.  How do we get type consistency?  See comment above about
;;; correct type of unknown values.  -jra 11/20/90) Note that this approach will
;;; cause data seeking to occur for all variables whose values were sought at
;;; the leaves of the tree, but avoids the execution time of traversing the
;;; computations in the tree (the intermediate nodes), since we already know
;;; that the result will be unknown.

;;; If after executing all expiration source nodes the global expiration is
;;; something other than unknown, then the values received from the expiration
;;; source nodes should be popped off the stack into local stack variables, and
;;; the execution of the intermediate nodes should proceed.  Where there were
;;; references to the expiration source nodes in the original tree, these
;;; references should be replaced with references to the values cached in the
;;; stack frame variables.  Note it might be nice to try and optimize this so
;;; that the popping off into stack variables and pushing back onto the top of
;;; the stack need not happen when it is possible for the evaluation to just
;;; consume the values right off the top of the stack.  After execution of the
;;; last instruction in the tree, the result of the computation should now be on
;;; top of the stack, and the correct expiration should still reside in the
;;; global expiration variable.

;;; Compilation of special form trees will have to be handled specially per
;;; special form (duh).  The characteristics of the compilation should be as
;;; follows.  If the special form is being executed as a sub-part of some other
;;; expression, then the global expiration should be cached into a stack frame
;;; variable and the final expiration of this form should be minimized with that
;;; cached value and eventually left back in the global expiration.  If the
;;; special form is the top level expression, then the global expiration is
;;; NEVER, minimizing this expiration with the global expiration would be a
;;; no-op, and so we could forgo the caching and re-minimizing with the global
;;; expiration value.  (We have not yet done this optimization.  -jra 1/31/92)
;;; In any case, when the last instruction associated with this form has
;;; completed execution, the global expiration should contain the expiration of
;;; this form minimized with the previous global expiration, and the value of
;;; this form should have been left pushed onto the top of the stack.

;;; As an example of special form compiling, the compilation of AND will be
;;; described here.  On entrance to this form, the global expiration is cached
;;; out of the global variable into a newly allocated stack frame variable.  The
;;; global expiration variable is reset to NEVER as a side effect of this
;;; operation.  Next, stack frame variables are reserved for the accumulator for
;;; AND.  These are set to TRUE (i.e.  1000) and NEVER.

;;; For each of the arguments to AND, do the following.  Insert the instructions
;;; for the argument.  Insert instructions to process the result of the argument
;;; as follows.

;;; If the result of the argument is unknown, set the expiration accumulator to
;;; unknown, reset the global expiration to NEVER, pop the stack, and continue
;;; to the next argument.

;;; Else if the result of the argument is known and the resulting value is
;;; FALSE, leave the FALSE on top of the stack, branch to the end of the AND,
;;; minimize the previously cached global expiration with the expiration of this
;;; argument, and branch to the end of the AND.

;;; Else if the result of the argument is known and is not false, then perform a
;;; fuzzy-and between the argument result and the accumulator truth value (i.e.
;;; do a MIN on them back into the accumulator), minimize the expiration of the
;;; value back in with the accumulated expiration, reset the global expiration
;;; variable back to NEVER, and continue on to the next argument.

;;; After the last argument has been executed and its value processed as
;;; described above, if the FALSE branch has not been done, then instructions
;;; should be emitted to push the accumulated truth-value onto the top of the
;;; stack and to minimized the accumulated expiration with the previously cached
;;; global expiration variable.

;;; Special form trees should be compiled such that from a parent node, the
;;; special form tree can be handled as if it were a normal form tree.

;;; The function `rewrite-stack-node-trees-for-unknown' takes a stack-node-tree
;;; and reorganizes the trees to be able to compute unknowns, per the
;;; documentation above.

;;; Trivial trees are left as is.

;;; The root nodes of special trees and source trees are left as is, except that
;;; the argument nodes are themselves rewritten.

;;; The root nodes of normal form trees are rewritten as follows.  A new stack
;;; node instruction is generated whose operation is execute-normal-form-tree.
;;; The subtree of this node is traversed to find the nodes which are not
;;; themselves normal-tree or trivial tree nodes.  For each of these subtrees, a
;;; variable is generated, the subtree is replaced in its parent's argument list
;;; with a node which pushes the value of the generated variable.  The
;;; execute-normal-form-tree instruction is emitted with the orginal root as the
;;; first stack-node-argument.  The remainder of the arguments are the special
;;; or source trees found below the root node.  At emitter time, these will be
;;; emitted into instructions which will will execute all the special or source
;;; trees, branch to the end if the expiration is now unknown, else it will
;;; cache all the values into the generated variables and execute the original
;;; tree.

(defun rewrite-stack-node-trees-for-unknown (stack-node)
  (when (and (type-specification-subtype-p
	       '(unknown-datum)
	       (stack-node-value-type stack-node))
	     (type-specification-not-subtype-p
	       '(unknown-datum)
	       (stack-node-required-value-type stack-node))
	     ;; The following operations given their own compiler warnings in
	     ;; the instruction-choosers if the required type included
	     ;; unknown-datum.
	     (not (memq (stack-node-operation stack-node)
			'(first-that-has-a-value
			   has-a-value value-of
			   first-that-has-a-current-value))))
    (compiler-error
      "The value of an expression could possibly be unknown.  This expression ~
       must be executed within a COLLECT DATA or WAIT UNTIL statement."))
  (case (stack-node-tree-type stack-node)
    ((special-tree single-source-tree trivial-tree)
     (loop for argument-node-cons on (stack-node-argument-nodes stack-node)
	   do
       (setf (car argument-node-cons)
	     (rewrite-stack-node-trees-for-unknown (car argument-node-cons))))
     stack-node)
    ((normal-tree source-tree)
     (loop with reverse-var-spot-list = nil
	   with new-node =
	     (make-stack-node-instruction 'execute-normal-form-tree nil)
	   with var-spot-to-tree-alist =
	     (collect-special-and-source-subtree-alist
	       (stack-node-argument-nodes stack-node)
	       t)
	   for alist-cons in var-spot-to-tree-alist
	   for (nil . expiration-node) = alist-cons	; car is the var-spot
	   do
       (setf (cdr alist-cons) reverse-var-spot-list)
       (setf reverse-var-spot-list alist-cons)
       (setq expiration-node
	     (rewrite-stack-node-trees-for-unknown expiration-node))
	   collect expiration-node into expiration-nodes using stack-cons
	   finally
	     (setf (stack-node-required-value-type new-node)
		   (stack-node-required-value-type stack-node))
	     (setf (stack-node-value-type new-node)
		   (stack-node-value-type stack-node))
	     (setf (stack-node-instruction-extra-info new-node)
		   reverse-var-spot-list)
	     (setf (stack-node-argument-nodes new-node)
		   (stack-cons stack-node expiration-nodes))
	     (return new-node)))
    (t
     (compiler-bug
       "unknown value stack node tree rewrite"
       "Unknown tree type ~a."
       (stack-node-tree-type stack-node))
     stack-node)))




;;; The function `collect-special-and-source-subtree-alist' is used to collect the
;;; subtrees of a normal form tree which can produce unknown values.  This
;;; function should return an alist of the var-spots to stack nodes, where
;;; references to the values of the variables have replaced the associated stack
;;; node tree.  Note that the alist returned is in the same order left to right
;;; as the original order of the nodes in the argument list subtree.  This is
;;; needed to keep left to right argument evaluation order.

;;; Note that for the very first nodes executed, the push can be optimized away
;;; by the normal form tree executer.  The argument optimize-push? will be T for
;;; nodes which are still within the bounds that can be optimized.

;; Note that the optimized-push code below only works for stack-machine style
;; implementations of the runtime engine.  It will not work for cases like a
;; C-code emitter, and we will have to deal with that!!!  -jra 7/12/93

(defun collect-special-and-source-subtree-alist (argument-nodes optimize-push?)
  (let ((alist-so-far nil))
    (loop for argument-node-cons on argument-nodes
	  for argument-node = (car argument-node-cons)
	  for tree-type = (stack-node-tree-type argument-node)
	  do
      (case tree-type
	((normal-tree)
	 (setq alist-so-far
	       (nconc
		 alist-so-far
		 (collect-special-and-source-subtree-alist
		   (stack-node-argument-nodes argument-node)
		   optimize-push?)))
	 (setq optimize-push? nil))
	((trivial-tree)
	 (setq optimize-push? nil))
	((special-tree source-tree single-source-tree)
	 (let* ((arg-value-type (stack-node-value-type argument-node))
		(new-var-type?
		  (and (union-type-specification-p arg-value-type)
		       (type-specification-subtype-p
			 '(unknown-datum) arg-value-type)
		       (type-specification-union-minus-type
			 arg-value-type '(unknown-datum))))
		(new-var-spot?
		  (when (not optimize-push?)
		    (if (and new-var-type?
			     (type-specification-subtype-p new-var-type? 'datum))
			(generate-new-stack-frame-var-spot new-var-type?)
			(generate-new-stack-frame-var-spot 'item-or-datum))))
		(new-node (make-stack-node-instruction
			    (if new-var-spot?
				'push-from-surrounding-local-var
				'no-op)
			    new-var-spot?)))
	   (setf (stack-node-required-value-type new-node)
		 (stack-node-required-value-type argument-node))
	   (setf (stack-node-value-type new-node)
		 (stack-node-value-type argument-node))
	   (setf (car argument-node-cons) new-node)
	   (setq alist-so-far
		 (nconc alist-so-far
			(phrase-list
			  (phrase-cons new-var-spot? argument-node))))))
	(t
	 (setq optimize-push? nil)
	 (compiler-bug
	   "unknown subtree search"
	   "Unknown tree type ~a." tree-type))))
    alist-so-far))

;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module NEW-RULES

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Michael Levin


;; To QUERIES

(declare-forward-reference
  add-rule-instance-to-dynamic-rule-displays function)

(declare-forward-reference
  add-rule-instance-to-generic-rule-displays function)

;; To EXPLAIN

(declare-forward-reference
  update-backward-chaining-displays-function function)

(declare-forward-reference backward-chaining-displays variable)

;; To CELLS

(declare-forward-reference current-computation-style variable)

;; To CHAINING

(declare-forward-reference add-rule-instance-to-variable-interests function)

;; To PROC-UTILS

(declare-forward-reference valid-item-or-evaluation-value-p function)
(declare-forward-reference schedule-computation-instance-execution function)
(declare-forward-reference clear-computation-context-variables function)
(declare-forward-reference evaluating-simulator-procedure? variable)
(declare-forward-reference var-type-from-index-function function)
(declare-forward-reference var-count function)

;;; In G2-RPC2

(declare-forward-reference
  g2-rpc-object-handed-off-to-user-p-function function)

;;; To GRAMMAR6B
(declare-forward-reference
  write-list-in-chicago-style-given-format function)

;;; To GRAMAR7
(declare-forward-reference
  explanation-related-features-enabled-func? function)





;;;; Contexts for rules




;;; A `rule context' is an associative store between a symbol and a
;;; value. The value is always a frame or a temporary-constant.
;;; Contexts within expressions (but nor rule contexts) can also have a
;;; null value.  Alists and vectors with precomputed locations are
;;; implementations of rule context. Two contexts are equivalent if they
;;; bind the same set of symbols, and corresponding values are both
;;; temporary-constants, or both the same frame.

;;; A `rule-instance' is the application of a rule within a given rule
;;; context. Rule-instances are in 1-1 correspondence with equivalence
;;; classes of rule contexts. A major use of the notion of equivalence
;;; defined above is to prevent the simultaneous scheduling of two
;;; applications of a rule which are known to be operationally equivalent.

;;; The issue of what symbols are bound in a rule context is somewhat
;;; complicated, and is related to the linguistic assumptions behind
;;; forward chaining, backward chaining and focusing, as well as the
;;; need to generate instances of a rule by iteration as indicated by
;;; the use of ANY. 

;;; If ANY were the only consideration, then it would be necessary to
;;; include exactly those binding generated from roles iterated by the
;;; quantifier ANY, and those bindings generated from roles iterated by
;;; the quantifier THE upon which an ANY quantifier is dependent.

;;; Focusing and chaining may occur on objects that are not bound in the
;;; context. It may be possible to follow an inverse role path (using
;;; only invertible roles) to get into the context. Provided that the
;;; roles being inverted are "fixed" (such as connectivity), this path
;;; is traversed in the prefix for such a rule invocation, but the
;;; values are not saved. They are always "THE" in the forward direction
;;; in any case, and so at most a unique thread must be recomputed.)
;;; This sort of path is indicated in the prefix by THE-INVERSE-NO-BIND.

;;; However any inverse role service path (or the tail end of any such
;;; path) that begins with a dynamic role is treated differently. The
;;; linguistics of a focus or forward chain require that the dynamic
;;; roles that served as purposes to invoke an instance are valid at the
;;; time the instance is executed or continued. (Example: If you invoke
;;; a rule workstations for workstation-3 because widget-7 is at
;;; workstation-3, this relation should be valid at the time the rule
;;; executes.) This is done by including the entire path (or tail of a
;;; path) within the binding context, and by re-testing the relation
;;; after any delay using the `validation predicate' of the rule.  (In
;;; the example, the widget is bound in the context, and the relation of
;;; widget to workstation must hold when the rule is invoked. The
;;; validation predicate tests that the location relation holds for the
;;; bound workstation and widget.)





;;;; Internal Rule Syntax for New Rules

;;; box-translation-and text ::= (translation . text)

;;; translation ::= (parsed-rule body . alist-of-prefix-pairs)

;;; prefix-pair ::= (role . prefix) | ((role binding-name) . prefix)

;;; prefix ::= ordered-list-of-iterators
;;; prefix ::= UNIVERSAL-COMPILATION

;;; iterator ::= 
;;;	(ANY role range-binding [domain])
;;;	(THE role range-binding [domain])
;;;	(ANY-INVERSE range-binding role short-designation domain-binding)
;;;	(THE-INVERSE range-binding role short-designation domain-binding)
;;;     (THE-INVERSE-NO-BIND range-binding role short-designation domain-binding)

;;; body ::= inner-body
;;; body ::= (RULE-LET ({(binding designation)}) inner-body)

;;; inner-body ::= (IF|WHEN|WHENEVER antecedent
;;;             (AND|IN-ORDER|SIMULTANEOUSLY {action}))




;;; Example:

;;; ((FOR (ANY (BAR . BAR1))
;;;    (FOR (ANY ((CONNECTED-TO FOO) . FOO1) BAR1)
;;;       (IF (> (THE X FOO1) 3) (CONCLUDE (GLITCH BAR1)))))    ;parse
;;;
;;;  (IF (> (THE X FOO1) 3) (CONCLUDE (GLITCH BAR1)))           ;body

;;;  (NIL . ((ANY BAR BAR1)   
;;;          (ANY (CONNECTED-TO FOO) FOO1 BAR)))                ;prefix for univ.
;;;  ((BAR FORWARD-CHAINING BAR1) .
;;;          ((ANY (CONNECTED-TO FOO) FOO1 BAR1)))              ;prefix for bar 
;;;  ((FOO FORWARD-CHAINING FOO1) .
;;;          ((ANY-INVERSE FOO1 (CONNECTED-TO FOO) (ANY BAR) BAR1))))   ;prefix for foo

;;; Comments on the parameters of iterators:

;;; ANY and THE:
;;; (1) Role is the role to be applied to the domain if any, or the role
;;; to be applied without a domain (which presently is only members of a class).
;;; (2) Range-binding is either the class or attribute name of the role, or the local
;;; name supplied by the user.
;;; (3) Domain is a symbol which must be contextually bound to the context or if not
;;; it must be the proper name of the object.

;;; ANY-INVERSE, THE-INVERSE and THE-INVERSE-NO-BIND
;;; (1) The distinction between ANY-INVERSE and the other two, is that ANY-INVERSE
;;; does not require that the role being inverted be unique if traversed in the forward
;;; direction again.
;;; (2) THE-INVERSE-NO-BIND is used when an initial train of role inversions is used
;;; to arrive at the first value to be bound. These are found only at the front of the
;;; statement before any other FOR iterators occur. The first symbol (temporally)
;;; to be bound in the context is the domain-binding of the LAST occurance of a
;;; THE-INVERSE-NO-BIND iterator. The others, including the focal-role? are not used
;;; as part of the context. 
;;; (2) The binding is the name (local or otherwise) to which the object to have its
;;; role inverted is bound.
;;; (3) The role is the one being inverted.
;;; (4) The short designation specifies the name of the inverse object being sought,
;;; if it is a symbol.
;;; Otherwise its form is (ANY class-or-attribute-name). This is a needed argument for
;;; serve-first-value-of-role-inverse.
;;; (5) Domain-binding is the local name or name derived from the short designation
;;; to use to bind the inverse value.



;;; Internal syntax for Quantifiers (which are literals) and Aggregators (which are factors).
;;; there-exists-literal ::=
;;;      (THERE-EXISTS-LITERAL aggregator-phrase logical-expression)
;;; for-every-literal ::=
;;;      (FOR-EVERY-LITERAL aggregator-phrase logical-expression)

;;; aggregator-phrase ::= (class-phrase-role [immediate-designation])

;;; aggregator-phrase ::= (role binding [domain])

;;; Examples:
;;;    (THERE-EXISTS (FURNACE) (IS (THE FURNACE 'HOT)))

;;;    (THERE-EXISTS (FURNACE)
;;;      (THERE-EXISTS ((CONNECTED-TO VALVE) V1 (THE FURNACE))
;;;        (IS V1 'BROKEN)))





;;;; Every in Actions




;;; Within the new implementation of rules and actions, a different means of
;;; caching the arguments to actions when iterated over by every had to be
;;; devised.  This is handled now with a new kind of evaluation value called
;;; action-cache.  An action cache holds an eval cons list, where each list
;;; element is a cons whose car is a number of cached values, and whose cdr is
;;; NIL if no elements were cached or a managed simple vector with at least
;;; enough elements to hold the cached values.

;;; When an every action wraps an in order action of a rule, the compilation of
;;; every will cause a loop to be emitted which iterates over the designation
;;; that every was applied to.  Within the loop, the action will attempt to
;;; evaluate its arguments.  If they are known the action is executed and
;;; another iteration is taken.  If they are unknown, all values for the action
;;; are popped off the stack and the rule is put to sleep.  On wake up, the
;;; action is retried and the rule either goes back to sleep or the action
;;; succeeds and the iteration is asked to serve the next value.

;;; When an every action wraps a simultaneous rule, then the situation is more
;;; complex.  An iteration is generated by every within the action prolog.  This
;;; will iterate over all of the values generated by every.  Within the
;;; iteration, the action prolog generates its values and places them local
;;; variables.  Then an instruction needs to fetch those values from the local
;;; variables and cache them into an action cache local var.  As the iteration
;;; proceeds many sets of values will be placed into the action cache.  After
;;; the full set of action prologs are complete, if all values were known, then
;;; the action epilogs will begin to execute within the epilog for every, an
;;; iteration needs to be made which restores a set of values from the action
;;; cache, executes epilog of the action embedded within the every iteration,
;;; and then attempts to fetch another set of values from the action cache.
;;; After the values in the action cache have been depleted, the rule should
;;; proceed to execute any remaining action epilogs.

;;; Note that the values within the action cache must be handled the same way
;;; that local variable bindings are handled by the delete action.  If any
;;; frames cached within an action cache are deleted, the delete action must
;;; find them and set that location in the action cache to NIL.  The action
;;; epilog will discover that this has occurred after the values are decached
;;; back into the local variables from which they came.

;;; The evaluation value `action-cache' is used to store caches of action
;;; values.  These values are stored as an eval cons whose car holds a count of
;;; values and whose cdr holds a managed simple vector containing the cache.

(def-evaluation-value action-cache)

(def-evaluation-value-reclaimer action-cache
  (let ((first-cons (evaluation-action-cache-value action-cache)))
    (when first-cons
      (loop for trailer = nil then current-cons
	    for current-cons = first-cons then (cdr-of-cons current-cons)
	    while current-cons
	    for element-cons = (car-of-cons current-cons)
	    do
	(when (/=f (car-of-cons element-cons) 0)
	  (reclaim-environment-vector (cdr-of-cons element-cons)))
	(reclaim-eval-cons-macro element-cons)
	    finally
	      (reclaim-eval-list-given-tail first-cons trailer)))))

(def-evaluation-value-copier action-cache
  (make-evaluation-action-cache
    (loop for element-cons in (evaluation-action-cache-value action-cache)
	  for count = (car-of-cons element-cons)
	  collect
	    (eval-cons
	      count
	      (if (/=f count 0)
		  (copy-environment-vector (cdr-of-cons element-cons))
		  nil))
		    using eval-cons)))

(def-evaluation-value-comparitor action-cache
  (declare (ignore action-cache-1 action-cache-2))
  nil)

(def-evaluation-value-writer action-cache
  (let ((count (length (evaluation-action-cache-value action-cache))))
    (tformat "~a cached action argument~a"
	     count
	     (if (=f count 1)
		 ""
		 "s"))))

(def-evaluation-value-validator action-cache (frame-serial-number)
  (loop for cache-cons in (evaluation-action-cache-value action-cache)
	for count = (car-of-cons cache-cons)
	for vector? = (cdr-of-cons cache-cons)
	do
    (loop for index from 0 below count
	  do
      (setf (svref vector? index)
	    (validate-item-or-evaluation-value
	      (svref vector? index) frame-serial-number nil))))
  action-cache)



;;; Modified valid-rule-context-vector-p and validate-rule-context-vector to
;;; optionally validate the class of items in the environment.  This change is
;;; needed to validate rule-instances after there has been a runtime change to
;;; KB definitions.  In this case, the class of an item may have changed.  -
;;; cpm, 3/17/94

(defun-simple valid-rule-context-vector-p
    (context-vector environment-length frame-serial-number rule
		    also-validate-item-classes?)
  (let ((current-computation-flags current-computation-flags))
    (setf (role-serve-inactive-objects?) (may-refer-to-inactive-items-p rule))
    (if (null also-validate-item-classes?)
	(loop for index from 0 below environment-length
	      for value? = (svref context-vector index)
	      always (or (null value?)
			 (valid-item-or-evaluation-value-p
			   value? frame-serial-number nil)))
	(loop with rule-byte-code-body = (rule-byte-code-body rule)
	      with descriptions = (byte-code-body-environment-description
				    rule-byte-code-body)
	      for description-index from 0 below (var-count descriptions)
	      for index from 0 below environment-length
	      for value? = (svref context-vector index)
	      for item-type? = (if (framep value?)
				   (var-type-from-index-function
				     descriptions description-index)
				   nil)
	      always (or (null value?)
			 (valid-item-or-evaluation-value-p
			   value? frame-serial-number item-type?))))))

(defun-simple validate-rule-context-vector
    (context-vector environment-length frame-serial-number rule
		    also-validate-item-classes?)
  (let ((current-computation-flags current-computation-flags))
    (setf (role-serve-inactive-objects?) (may-refer-to-inactive-items-p rule))
    (if (null also-validate-item-classes?)
	(loop for index from 0 below environment-length
	      for value? = (svref context-vector index)
	      do
	  (when value?
	    (setf (svref context-vector index)
		  (validate-item-or-evaluation-value
		    value? frame-serial-number nil))))
	(loop with rule-byte-code-body = (rule-byte-code-body rule)
	      with descriptions = (byte-code-body-environment-description
				    rule-byte-code-body)
	      for description-index from 0 below (var-count descriptions)
	      for index from 0 below environment-length
	      for value? = (svref context-vector index)
	      for item-type? = (if (framep value?)
				   (var-type-from-index-function
				     descriptions description-index)
				   nil)
	      do
	  (when value?
	    (setf (svref context-vector index)
		  (validate-item-or-evaluation-value
		    value? frame-serial-number item-type?)))))))



;;; The function `validate-all-rule-instances' locates all rule-instances and
;;; validates the corresponding rule-context-vectors.  If a location in the
;;; rule-context is invalid, it is set to NIL, and, depending on the
;;; rule-instance state, the rule-instance may be dismissed.

;;; Note that the validation differs from normal rule-instance validation, in
;;; that it checks for items of the wrong class, as well as deleted items.

;;; This function is needed when there has been a change to a running or paused
;;; KB, and, therefore, some rule-instances may no longer be valid.

(defun-void validate-all-rule-instances ()
  (loop for rule being each class-instance of 'rule
	for rule-instance-hash-table? = (hash-table-of-rule-instances rule)
	do
    (when rule-instance-hash-table?
      (loop for rule-instance being each hash-value of rule-instance-hash-table?
	    for rule-instance-state = (ri-state rule-instance)
            for context-vector = (invocation-local-var-vector rule-instance)
	    for environment-length = (rule-environment-length rule)
	    for frame-serial-number = (copy-frame-serial-number (ri-frame-serial-number rule-instance))
	    with rule-instances-to-dismiss? = nil
	    do
	(cond
	  ((=f rule-instance-state 0)
	   ;; The rule antecedent has not yet completed.
	   (when (not (valid-rule-context-vector-p
			context-vector environment-length frame-serial-number
			rule t))
	     ;; The rule-instance should be dismissed because the invalid
	     ;; local-variable in the context will be accessed when the
	     ;; antecedent is evaluated.  These rule-instances are collected and
	     ;; dismmissed outside of this LOOP.  Don't want to remove from the
	     ;; hash-table while the LOOP is still iterating over the hash-table
	     ;; values.
	     (setq rule-instances-to-dismiss?
		   (if (null rule-instances-to-dismiss?)
		       (gensym-list rule-instance)
		       (gensym-cons
			 rule-instance rule-instances-to-dismiss?)))))
	  (t
	   ;; The rule antecedent has completed.  Replace any invalid values
	   ;; with NIL.  Do not dismiss the rule-instance.  If a value is
	   ;; invalid and later referenced, the rule will receive an error.
	   (validate-rule-context-vector
	     context-vector environment-length frame-serial-number rule t)))

	    finally
	      (reclaim-frame-serial-number frame-serial-number)
	      (loop for rule-instance in rule-instances-to-dismiss?
		    do
		(delete-hashed-rule-instance
		  (ri-context rule-instance) rule-instance-hash-table?)
		finally
		      (when rule-instances-to-dismiss?
			(reclaim-gensym-list rule-instances-to-dismiss?))))))
  nil)



;;; (get-rule-instance-with-equivalent-context-if-any rule context)

(defmacro get-rule-instance-with-equivalent-context-if-any (context rule)
  `(get-hashed-rule-instance ,context (hash-table-of-rule-instances ,rule)))



;;; A rule instance refers to the execution of the body of a rule with a
;;; particular binding context, and includes any continuation of that
;;; rule. At the time the execution of the rule starts, and at the time
;;; a continuation resumes, it must be the case that all frames
;;; referenced by the context exist (have not been deleted and possibly
;;; recycled), and that all relations implied by the roles used to
;;; generate the context hold, except those that are classified as
;;; quasi-static, as distinct from dynamic. (Currently the only dynamic
;;; role is "named by." This is before dynamic relations have been
;;; introduced.) Execute-rule-instance-from-context has no useful value. 

;;; The computation flag `final-evaluation-attempt?' has a default value of NIL
;;; and reflects whether or not this is the last attempt to execute a rule
;;; instance.  This flag is defined by def-computation-flag in TYPES.

(def-concept final-evaluation-attempt?)


(defun-simple enter-or-reclaim-rule-instance-context
    (rule-instance dont-validate-environment)
  (let* ((rule (ri-rule rule-instance))
	 (context-vector (invocation-local-var-vector rule-instance))
	 (environment-length (rule-environment-length rule))
	 (frame-serial-number (copy-frame-serial-number (ri-frame-serial-number rule-instance)))
	 (rule-instance-state (ri-state rule-instance))
	 (rule-purpose
	   (when (consp (ri-purposes rule-instance))
	     (car (ri-purposes rule-instance)))))
    (setq current-computation-flags
	  (make-computation-flags
	    :cache-explanation-variables? (and (explanation-related-features-enabled-func?)
					       (cache-data-for-explanation-p rule))
	    :role-serve-inactive-objects? (may-refer-to-inactive-items-p rule)
	    :default-dont-compute-new-variable-values (not (may-cause-data-seeking-p rule))
	    :dont-compute-new-variable-values (not (may-cause-data-seeking-p rule))
	    :dont-forward-chain-from-rule (not (may-cause-forward-chaining-p rule))
	    ))
    (setq current-computation-activity 0)
    (setq current-computation-component-particulars nil)
    (setq *current-computation-frame* rule)
    (setq current-computation-instance rule-instance)
    (setq current-computation-style nil)
    (setq current-environment 'inference-engine)
    ;; profiling is currently undergoing revision ---rdf 7/8/93
;    (setq current-profile-structure? nil)

    (setq evaluating-simulator-procedure? nil)
    (when explanation-variables
      (reclaim-explanation-variables))
    (setq stack-expiration 'never)
    (setq *variables-that-did-not-have-values* nil)
    
    ;; Insert something here which can print the context contents.  -jra
    ;; 7/8/91
    (enter-tracing-and-breakpoint-context
      rule
      (tformat-text-string "Invoking-rule ~NF." rule))
    
    ;; Check that the rule context is valid when we have not yet succeeding in
    ;; completing the rule antecedent.  If it is not valid, then dismiss the
    ;; rule, since we can be certain that the invalid binding in the context
    ;; will be accessed, and then the rule would get an error anyway.  This
    ;; behavior is consistent with pre-3.0 handling of this case.  -jra & cpm
    ;; 2/5/92
    (cond
      ((and (=f rule-instance-state 0)
	    (not dont-validate-environment)
	    (not (valid-rule-context-vector-p
		   context-vector environment-length
		   frame-serial-number rule nil)))
       ;; Remove instance from the rule
       (delete-hashed-rule-instance
	 (ri-context rule-instance) (hash-table-of-rule-instances rule))
       (exit-tracing-and-breakpoint-context
	 rule
	 (tformat-text-string
	   "Terminating invocation of rule ~NF because either some item in ~
              its invocation has been deleted or some dynamic relation among ~
              these items no longer holds."
	   rule))
       (clear-computation-context-variables))
      
      (t
       ;; When the rule is being returned to after having completed the
       ;; antecedent, validate the context by replacing deleted and reprocessed
       ;; frames with NIL.  This is suppressed when a called procedure is
       ;; returning to this rule, since the return-values instruction already
       ;; revalidated this environement, and in fact it may have modified this
       ;; environement with returned values, which themselves are not now valid
       ;; with the cached frame serial number in the rule context.  When the
       ;; dont-validate-environment argument is given, then we must not
       ;; reattempt the validation here.
       (when (and (/=f rule-instance-state 0)
		  (not dont-validate-environment))
	 (validate-rule-context-vector
	   context-vector environment-length frame-serial-number rule nil))
       ;; Highlight if in highlight mode.
       (cond ((highlight-invoked-rules-mode debugging-parameters)
	      (setf (ri-highlighted? rule-instance) t)
	      (highlight-or-unhighlight-for-slot
		rule 'box-translation-and-text nil
		'foreground
		nil)
	      (force-process-drawing))
	     (t
	      (setf (ri-highlighted? rule-instance) nil)))
       
       ;; If this rule instance has timed out, or if ri-hurry-and-repeat-priority
       ;; is non null, set final-evaluation-attempt?.  Rule cannot be continued
       ;; in this case.
       (let ((timeout (timeout-for-rule-completion rule)))
	 (when (eq timeout 'default)
	   (setq timeout (timeout-for-wakeups inference-engine-parameters)))
	 ;; Note that timeout is taken first from the rule, and if defaulted,
	 ;; then from inference engine parameters.  If nil, there is no
	 ;; completion.
	 (when (or (ri-hurry-and-repeat-priority rule-instance)
		   (and timeout
			(<=f (+f (ri-initiation-time rule-instance)
				 timeout)
			     gensym-time)))
	   (setf (final-evaluation-attempt?) t)))))
    (reclaim-frame-serial-number frame-serial-number)

    ;; GENSYMCID-1349: Procedure execution limit now applies to action-buttons as well
    (when (eq rule-purpose 'action-button)
      (return-from enter-or-reclaim-rule-instance-context))

    ;;; Return execution time limit of rule
    (let ((fixnum-time-limit (timeout-for-rule-completion rule)))
      (when (eq fixnum-time-limit 'default)
	(setq fixnum-time-limit (timeout-for-wakeups inference-engine-parameters)))
      (setq fixnum-time-limit (*f fixnum-time-limit 1000))
      fixnum-time-limit)))

(defun exit-last-rule-instance-context (stack-program-counter)

  ;; This rule will not be continued either when this was the final attempt, or
  ;; when there is a symbolic rule state.  The two symbols which are placed into
  ;; the rule state are error and completed.  The numeric states are 0 for still
  ;; attempting antecedent and 1 for in the middle of executing actions.
  (let* ((rule-instance current-computation-instance)
	 (rule (ri-rule rule-instance))
	 (continue-rule?
	   (not (or (final-evaluation-attempt?)
		    (symbolp (ri-state rule-instance))
		    (null (ri-things-this-rule-instance-is-interested-in
			    rule-instance))
		    (null (ri-purposes rule-instance))))))
    
    ;; The first time a rule is to be continued, set up a final-continuation-task.
    (when (and continue-rule?
	       (not (schedule-task-in-place-p
		      (ri-final-continuation-task rule-instance))))
      (let ((timeout? (timeout-for-rule-completion rule)))
	(when (eq timeout? 'default)
	  (setq timeout? (timeout-for-wakeups inference-engine-parameters)))
	;; Note that timeout is taken first from the rule, and if defaulted,
	;; then from inference engine parameters.  If nil, there is no
	;; time out on this rule instance.
	(when timeout?
	  (with-future-scheduling
	      ((ri-final-continuation-task rule-instance)
	       (ri-priority rule-instance)
	       (g2-future-interval
		 (-f (+f (ri-initiation-time rule-instance) timeout?)
		     gensym-time)))
	    (schedule-computation-instance-execution
	      rule-instance (ri-priority rule-instance) rule)))))
    
    (cond
      ((ri-hurry-and-repeat-priority rule-instance)
       ;; The following code is for the case where a rule instance has forward
       ;; chained, or caused some other call to generate-and-schedule-rule-
       ;; instances, which has called for the invocation of a rule with the same
       ;; context as the currently executing one.  So, this code is intended to
       ;; represent the closing of one rule instance and the generation and
       ;; scheduling of a new one.  However, this code does not seem to handle
       ;; all of the clean-up which is done in dismiss-rule-instance.  In
       ;; particular it does not address getting rid of existing wake ups from
       ;; variables to this rule instance, nor does it handle resetting the
       ;; purposes list so purposes from the old rule instance are not carried
       ;; forward in the new rule instance.  Ideally one would think that this
       ;; code should be isomorphic to dismissing the old instance and
       ;; scheduling the new.  Review and redesign this implementation so that
       ;; it is not so confusing!!!  -jra 1/29/90
       (cond ((not continue-rule?)
	      (schedule-computation-instance-execution
		rule-instance (ri-hurry-and-repeat-priority rule-instance) rule)
	      (setf (ri-hurry-and-repeat-priority rule-instance) nil)
	      ;; Must reclaim and reset the explainable variables slot
	      ;; of rules instances here.  -jra 1/18/90
	      (let ((variable-list (ri-explanation-variables
				     rule-instance)))
		(when variable-list
		  (reclaim-evaluation-variables-list variable-list)
		  (setf (ri-explanation-variables rule-instance) nil)))
	      (update-backward-chaining-displays rule-instance)
	      
	      ;; State must be set to 0 because the following scheduling is
	      ;; for a new execution.  The non-context binding must be
	      ;; re-evaluated at that time.  Note that we are not resetting
	      ;; the interest lists under the belief that these interests will
	      ;; just be reestablished on first run of the rule instance.
	      (setf (ri-state rule-instance) 0)
	      (when profiling-enabled?
		(increment-profiling-calls
		  (ri-rule rule-instance)))
	      (frame-serial-number-setf (ri-frame-serial-number rule-instance)
					(current-frame-serial-number))
	      (setf (invocation-stack-program-counter rule-instance) 0)
	      (setf (ri-initiation-time rule-instance) gensym-time)
	      (cancel-task (ri-final-continuation-task rule-instance)))
	     
	     (t
	      (frame-serial-number-setf (ri-frame-serial-number rule-instance)
					(current-frame-serial-number))
	      (setf (invocation-stack-program-counter rule-instance) stack-program-counter)
	      (update-backward-chaining-displays rule-instance)

	      (schedule-computation-instance-execution
		rule-instance
		(highest-priority
		  (ri-hurry-and-repeat-priority rule-instance)
		  (ri-priority rule-instance))
		rule))))
      
      ((not continue-rule?)
       ;; Remove instance from the rule.  Note that deleting a rule instance
       ;; from the hash table will automatically update the backward chaining
       ;; displays from within dismiss-rule-instance.  -jra 1/29/90
       (progn
	 (delete-hashed-rule-instance
	   (ri-context rule-instance)
	   (hash-table-of-rule-instances rule))))
      (t
       ;; Update the stored frame serial number and the program counter, and let
       ;; the rule sleep.
       (frame-serial-number-setf (ri-frame-serial-number rule-instance)
				 (current-frame-serial-number))
       (setf (invocation-stack-program-counter rule-instance) stack-program-counter)
       (update-backward-chaining-displays rule-instance)))
    
    (when (ri-highlighted? rule-instance)
      (c-uninterruptible-sleep 50)
      (highlight-or-unhighlight-for-slot
	rule 'box-translation-and-text nil
	'foreground
	t)
      (force-process-drawing)
      (setf (ri-highlighted? rule-instance) nil))
    
    (when (and continue-rule?
	       (=f (ri-state rule-instance) 0)
	       (explanation-related-features-enabled-func?))
      ;; Clear and reset the cached explanation variables when the rule
      ;; antecedent needs to be re-evaluated. 
      (let ((cached-variables (ri-explanation-variables rule-instance)))
	(when cached-variables
	  (reclaim-evaluation-variables-list cached-variables)
	  (setf (ri-explanation-variables rule-instance) nil))))
    
    (exit-tracing-and-breakpoint-context
      rule
      (tformat-text-string
	(cond
	  (continue-rule?
	   "Rule ~NF did not complete and is being continued.")
	  ((final-evaluation-attempt?)
	   "Rule ~NF did not complete.  Its time for completion has expired.")
	  (t
	   "Rule ~NF has completed."))
	rule))
    (clear-computation-context-variables)
    nil))




;;; (generate-rule-alists rule focal-role? focal-entity?)
;;; Finds all appropriate contexts for the rule, based on the focal-role,
;;; focal-entity, and purpose.

;;; Generate-rule-instances finds the appropriate prefixes if any. The value is
;;; an eval-list of them.

(def-system-variable list-of-generated-contexts new-rules nil)

(def-system-variable list-of-generated-contexts-tail new-rules nil)




;; Problem for universal invocation here is that deletion of objects and/or
;; mutation of dynamic roles will invalidate the recursively bound layers of the
;; role service.  This is difficult to check in any reasonable way. Might be
;; better to schedule all invocations.  The Braunshwieger assumption still
;; holds, but its efficiency is O(n*m) because it lacks early filtering.  The
;; efficiency is only somewhat improved by generating and executing on the spot.


;;; Generate-rule-alists has as value a list of alists used to form rule contexts.
;;; Its first argument is a rule. For a universal focus, all the rest of the 
;;; are null. For a more specific focus, focal-entity? (should be focal item)
;;; is supplied, and either focal-role? or local-name? or both. Note that
;;; a local name is often more specific and results in a narrower focus. 

;;; Constraint-alist is used to further narrow the extent of a focus. It is
;;; an (often empty) alist of (binding . item) pairs. Each recursive level
;;; of generate-rule-alists-1 has a specific binding name for which it is 
;;; generating alist pairs. If this binding name appears in the constraint alist,
;;; then that level will generate only the pair given by the constraint alist
;;; if it would otherwise have been generated, and none otherwise. 

;;; It is a requirement that all serve-item-p be true for items in generated
;;; alists. Note that role-serve-inactive-objects? is bound to nil in
;;; generate-and-schedule-rule-instances. This is to insure uniform behavior
;;; of sevre-item-p. Focal-role? is tested for servability, and all
;;; other evaluations within generate-rule-alists should do likewise.

(defun generate-rule-context-vectors
       (rule focal-role? local-name? focal-entity? constraint-alist)
  (let* ((prefix 'none)
	 focal-specifier
	 role-for-prefix
	 index-for-prefix
	 (environment-length (rule-environment-length rule))
	 (initial-environment?
	   (when (>f environment-length 0)
	     (allocate-environment-vector environment-length)))
	 (rule-contexts
	   (let ((definition? (car-of-cons (box-translation-and-text rule))))
	     (if (neq definition? no-value)
	       (cdr-of-cons
		 (cdr-of-cons definition?)))))
	 (*current-computation-frame* rule)
	 (current-computation-component-particulars nil)
	 (current-computation-flags current-computation-flags))

    (setf (no-wake-ups-during-role-serving) t)
    (setf (role-serve-inactive-objects?) (may-refer-to-inactive-items-p rule))
    
    (setq list-of-generated-contexts nil)
    (setq list-of-generated-contexts-tail nil)

    (unless (and (runnable-p rule)
		 ;; GENSYMCID-1047: Abort on editing rule (re-worked)
		 ;; Suspend the function if rule-contexts is NULL, this could happen when
		 ;; the rule being editing was affected by itself (a whenever rule).
		 ;; -- Chun Tian (binghe), July 22, 2013.
		 (not (null rule-contexts))
		 (or (null focal-entity?) (serve-item-p focal-entity?)))
      (when initial-environment?
	(reclaim-managed-simple-vector initial-environment?))
      (return-from generate-rule-context-vectors nil))
    
    ;; Find all prefixes applicable to the way the rule was invoked.
    (cond
      ((or local-name? (null focal-role?) (not (multiple-compilations-p rule)))
       ;; There is at most one applicable prefix if (i) the rule is invoked
       ;; universally, or (ii) it is invoked with a local name, or (iii) there
       ;; are no multiple compilations for any role name.  Note that could be
       ;; more efficient for u-compilation!
       (if local-name?
	   ;; Where a local name is provided, find only the compilation whose
	   ;; specifier contains that local name.
	   (loop for pair in rule-contexts
		 doing
	     (setq focal-specifier (car-of-cons pair))
	     (when (and (consp focal-specifier)
			(eq local-name?
			    (car-of-cons (cdr-of-cons focal-specifier))))
	       (setq index-for-prefix
		     (car-of-cons (cdr-of-cons (cdr-of-cons focal-specifier))))
	       (setq prefix (cdr-of-cons pair))
	       (return nil)))
	   
	   ;; Otherwise find the compilation for the given role, which may have
	   ;; an atomic or compound specifier.
	   (loop for pair in (cddar (box-translation-and-text rule))
		 doing
	     (setq focal-specifier (car-of-cons pair))
	     (cond
	       ((symbolp focal-specifier)
		(when (eq focal-specifier focal-role?)
		  (setq role-for-prefix focal-specifier)
		  (setq index-for-prefix 0)
		  (setq prefix (cdr-of-cons pair))
		  (return nil)))
	       (t
		(setq role-for-prefix (car-of-cons focal-specifier))
		(when (eq role-for-prefix focal-role?)
		  (setq index-for-prefix (car-of-cons (cdr-of-cons (cdr-of-cons focal-specifier))))
		  (setq prefix (cdr-of-cons pair))
		  (return nil))))))
       
       (cond ((eq prefix 'none)
	      (warning-message
		3 "The rule ~NF was invoked via the focal role ~a, which was ~
                   not in its list of focal roles."
		rule
		focal-role?))
	     (t
	      (when focal-role?
		(setf (svref initial-environment? index-for-prefix)
		      focal-entity?))
	      (generate-rule-context-vectors-1
		rule prefix initial-environment? constraint-alist))))
      
      (t
       ;; There may be several prefixes for the rule, and they must all be found.
       (loop with prefixes-found? = nil
	     for pair in (cdr rule-contexts)
	     do
	 (setq focal-specifier (car-of-cons pair))
	 (cond
	   ((symbolp focal-specifier)
	    (setq role-for-prefix focal-specifier)
	    (setq index-for-prefix 0))
	   (t
	    (setq role-for-prefix (car-of-cons focal-specifier))
	    (setq index-for-prefix
		  (car-of-cons (cdr-of-cons (cdr-of-cons focal-specifier))))))
	 
	 ;; local-name? is nil if you are here.
	 (when (eq role-for-prefix focal-role?)
	   
	   (setq prefix (cdr-of-cons pair))
	   
	   (setf (svref initial-environment? index-for-prefix)
		 focal-entity?)
	   
	   (generate-rule-context-vectors-1
	     rule prefix initial-environment? constraint-alist)
	   (setq prefixes-found? t))
	     finally
	       (unless prefixes-found?
		 (warning-message
		   3
		   "The rule ~NF was invoked via the focal role ~a, which ~
                    was not in its list of focal roles."
		   rule
		   focal-role?)))))
   
    (when initial-environment?
      ;; Note that each new binding reclaimed as it is made in
      ;; generate-rule-context-vectors-1, so this reclaimer need not find those
      ;; bindings to attempt to reclaim evaluation values.  Further, the focus
      ;; here is always a frame, and so it never needs to be reclaimed.  Only
      ;; reclaim the vector itself.
      (reclaim-managed-simple-vector initial-environment?))
    
    ;; List of generated alists is built up by generate-rule-context-vectors-1
    list-of-generated-contexts))


(defun copy-environment-to-generated-list (rule environment?)
  (let ((new-environment
	  (eval-list-macro
	    (when environment?
	      (let* ((context-length (rule-context-length rule))
		     (environment-length (length-of-simple-vector environment?))
		     (new-environment (allocate-managed-simple-vector
					environment-length)))
		(declare (type fixnum context-length environment-length)
			 (type simple-vector new-environment))
		(loop for index from 0 below context-length
		      for value = (svref environment? index)
		      do
		  (setf (svref new-environment index)
			(copy-if-evaluation-value value)))
		(loop for index from context-length below environment-length
		      do
		  (setf (svref new-environment index) nil))
		new-environment)))))

    (cond (list-of-generated-contexts-tail
	   (setf (cdr list-of-generated-contexts-tail) new-environment)
	   (setq list-of-generated-contexts-tail new-environment))
	  (t
	   (setq list-of-generated-contexts new-environment)
	   (setq list-of-generated-contexts-tail new-environment)))
    nil))

(defun generate-rule-context-vectors-1
       (rule prefix initial-environment? constraint-alist)
  (when (null prefix)
    (copy-environment-to-generated-list rule initial-environment?)
    (return-from generate-rule-context-vectors-1 nil))
  (let* ((iterator (car-of-cons prefix))
	 (iteration-keyword (car-of-cons iterator)))
    (case iteration-keyword	    
      (the
       (gensym-dstruct-bind ((nil role binding nil role-index domain-index-or-name?) iterator)	 
	 (let* ((domain-value?
		  (when domain-index-or-name?
		    (cond ((fixnump domain-index-or-name?)
			   (svref initial-environment? domain-index-or-name?))
			  (t
			   ;; Name reference only returns items, so this
			   ;; domain-value? never needs to be reclaimed.
			   (evaluate-designation domain-index-or-name? nil)))))
		(constraint-pair?
		  (when constraint-alist
		    (assq binding constraint-alist))))
	   (when (and domain-index-or-name? (null domain-value?))
	     (return-from generate-rule-context-vectors-1 nil))
	   
	   (multiple-value-bind (role-value role-expiration)
	       (if constraint-pair?
		   (if (value-of-role-p
			 (cdr-of-cons constraint-pair?)
			 'the role domain-value?)
		       (values (cdr-of-cons constraint-pair?) nil 'never)
		       (values nil nil nil))
		   (serve-unique-item-or-evaluation-value-of-role
		     role domain-value? nil nil))
	     (when role-expiration
	       (setf (svref initial-environment? role-index) role-value)
	       (let ((new-prefix? (cdr-of-cons prefix)))
		 (if new-prefix?
		     (generate-rule-context-vectors-1
		       rule new-prefix? initial-environment?
		       constraint-alist)
		     (copy-environment-to-generated-list
		       rule initial-environment?)))
	       (setf (svref initial-environment? role-index) nil)
	       (reclaim-if-evaluation-value role-value))))))
      
      (any
       (loop with second-cons = (cdr-of-cons iterator)
	     with role = (car-of-cons second-cons)
	     with third-cons = (cdr-of-cons second-cons)
	     with binding = (car-of-cons third-cons)
	     ;; Fourth is the domain name, which we don't need.
	     with fifth-cons = (cdr-of-cons (cdr-of-cons third-cons))
	     with role-index = (car-of-cons fifth-cons)
	     ;; Note that the domain-index cons may be absent, thus the call
	     ;; to car instead of car-of-cons.  -jra 7/7/91
	     with domain-index-or-name? = (car (cdr-of-cons fifth-cons))
	     with domain-value? =
	       (when domain-index-or-name?
		 (cond ((fixnump domain-index-or-name?)
			(svref initial-environment? domain-index-or-name?))
		       (t
			;; Since name evaluation cannot return an
			;; evaluation-value, domain-value? need not be
			;; reclaimed.
			(evaluate-designation domain-index-or-name? nil))))
	     with role-value
	     with role-continuation
	     with role-expiration
	     with reclaim-role-value?
	     with new-prefix = (cdr-of-cons prefix)
	     with constraint-pair? =
	       (when constraint-alist
		 (assq binding constraint-alist))
	     
	     initially
	       (when (and domain-index-or-name? (null domain-value?))
		 (return-from generate-rule-context-vectors-1 nil))
	       
	       (multiple-value-setq
		 (role-value role-continuation role-expiration)
		 (if constraint-pair?
		     (if (value-of-role-p (cdr-of-cons constraint-pair?)
					  'any role domain-value?)
			 (values (cdr constraint-pair?) nil 'never)
			 (values nil nil nil))
		     (serve-first-item-or-evaluation-value-of-role
		       role domain-value? nil nil)))
	       
	       (unless role-expiration
		 (return-from generate-rule-context-vectors-1 nil))
	       
	       (when (evaluation-value-p role-value)
		 (setq reclaim-role-value? t))
	       
	       (setf (svref initial-environment? role-index)
		     role-value)
	       
	     doing
	 (if new-prefix
	     (generate-rule-context-vectors-1
	       rule new-prefix initial-environment? constraint-alist)
	     (copy-environment-to-generated-list rule initial-environment?))
	 (when reclaim-role-value?
	   (reclaim-evaluation-value role-value))
	 
	     while role-continuation do
	 
	 (multiple-value-setq (role-value role-continuation role-expiration)
	   (serve-next-item-or-evaluation-value-of-role role-continuation))
	 
	     while role-expiration do

	 (setq reclaim-role-value?
	       (evaluation-value-p role-value))
	 (setf (svref initial-environment? role-index) role-value)
	 
	     finally
	       
	       (setf (svref initial-environment? role-index) nil)))
      
      ((any-inverse the-inverse the-inverse-no-bind)		       
       ;; Note that these really mean inverse of a role quantified by ANY or THE
       ;; respectively.  The "no-bind" one really means that the index generated
       ;; for the role is not within the portion of the environment vector that
       ;; is the context.  Also, the term "range" below is the same as role, so
       ;; we are traversing from the range to the domain.
       (loop with quantifier-of-range =
	       (if (eq iteration-keyword 'any-inverse) 'any 'the)
	     ;; The second is the role (or range) binding name, which isn't
	     ;; needed here.
	     with third-cons = (cdr-of-cons (cdr-of-cons iterator))
	     with role-to-invert = (car-of-cons third-cons)
	     with fourth-cons = (cdr-of-cons third-cons)
	     with short-designation = (car-of-cons fourth-cons)
	     with fifth-cons = (cdr-of-cons fourth-cons)
	     with domain-binding = (car-of-cons fifth-cons)
	     with sixth-cons = (cdr-of-cons fifth-cons)
	     with range-index = (car-of-cons sixth-cons)
	     with domain-index-or-name = (car-of-cons (cdr-of-cons sixth-cons))
	     with range-value? = (svref initial-environment? range-index)
	     with inverse-role-value
	     with role-continuation
	     with role-expiration
	     with new-prefix = (cdr-of-cons prefix)
	     with constraint-pair? =
	       (when constraint-alist
		 (assq domain-binding constraint-alist))
	     initially
	       (when (and range-index (null range-value?))
		 (return-from generate-rule-context-vectors-1 nil))
	     
	       (if constraint-pair?
		   (if (value-of-role-p
			 range-value? quantifier-of-range
			 role-to-invert (cdr-of-cons constraint-pair?))
		       (setq inverse-role-value (cdr-of-cons constraint-pair?)
			     role-continuation nil
			     role-expiration 'never)
		       (setq inverse-role-value nil
			     role-continuation nil
			     role-expiration nil))
		   
		   (multiple-value-setq
		     (inverse-role-value role-continuation role-expiration)
		     (serve-first-value-of-role-inverse
		       range-value? quantifier-of-range
		       role-to-invert short-designation)))
	       
	       (unless role-expiration
		 (return-from generate-rule-context-vectors-1 nil))

	       (when (fixnump domain-index-or-name)
		 (setf (svref initial-environment? domain-index-or-name)
		       inverse-role-value))
	       
	     doing
	 
	 (if new-prefix
	     (generate-rule-context-vectors-1
	       rule new-prefix initial-environment? constraint-alist)
	     (copy-environment-to-generated-list
	       rule initial-environment?))
	 
	 (reclaim-if-evaluation-value inverse-role-value)
	 
	     while role-continuation do
	 
	 (multiple-value-setq
	   (inverse-role-value role-continuation role-expiration)
	   (serve-next-item-or-evaluation-value-of-role role-continuation))
	 
	     while role-expiration do

	 (when (fixnump domain-index-or-name)
	   (setf (svref initial-environment? domain-index-or-name)
		 inverse-role-value))
	 
	     finally

	       (when (fixnump domain-index-or-name)
		 (setf (svref initial-environment? domain-index-or-name)
		       nil)))))))







;;; (invoke-rule-universally rule) finds all applicable contexts of the rule.
;;; As each context is generated, it is executed immediately (unless a 
;;; rule-instance with an equivalent context exists). However, if the time slice is used
;;; up before this process has completed, then the remaining contexts are generated
;;; and (unless a rule instance with an equivalent context exists) a rule-instance is
;;; created and scheduled for execution. 

(defun-simple invoke-rule-universally (rule)
  (generate-and-schedule-rule-instances rule nil nil nil 'scanning nil nil nil))








;;; The hash for a rule context is an arithmetic process on the values which are
;;; frames, ignoring those which are temporary-constants.

(defparameter minus-of-logcount-most-positive-fixnum-minus-4
  (-f (-f (logcount most-positive-fixnum) 4)))

(defparameter most-positive-fixnum-ash-minus-4
  (ashf most-positive-fixnum -4))

(defmacro hash-rule-context-vector
	  (context-elements context-vector)
  `(loop with hash fixnum = 0
	 for index from 0 below ,context-elements
	 with vector = ,context-vector
	 for value = (svref vector index)
	do
    (when (framep value)
      (setq hash (+f (ashf hash minus-of-logcount-most-positive-fixnum-minus-4)
		     (ashf (logandf hash most-positive-fixnum-ash-minus-4) 3)))
      (setq hash (logxorf hash (frame-hash value))))
	 finally
	   (return hash)))




;;; (Generate-and-schedule-rule-instances rule focal-role? local-name?  
;;; focal-object? purpose interested-party? priority?)  generates each context
;;; based on the rule, focal-role and focal-object. (1) If there is a validated
;;; instance for this context, the purpose and interested party are added to the
;;; purposes for the instance. If the instance is not scheduled, then it is
;;; scheduled at the rule priority or the specified priority if it is higher. If
;;; it is scheduled, then it may have to be rescheduled at a higher priority.
;;; (2) If there is no instance, then one is created and scheduled at the
;;; indicated priority, or the rule priority, whichever is higher.

;;; The value is the number of instances scheduled, which may be 0. This is the
;;; count of the number of new instances created and scheduled, and the existing
;;; instances not previously scheduled and now scheduled. however, if the
;;; rule was called for initializing, then the number of previous instances to
;;; which this purpose was added are also counted.

;; Note that an existing-rule-instance equivalent to an existing rule-instance
;; could only be invalid for reason of recycled and reassigned frames that
;; happen to mimic the existiting valid context.

;; It appears that generate-rule-alist may return duplicates, and that this
;; function does not filter them out. Try invoking a rule for every valve when
;; there are two valves connected by a pipe.

;;; Documentation describing which contexts get generated, and how the arguemnts
;;; controling the context are used is found preceeding generate-rule-alists.

(defun-simple generate-and-schedule-rule-instances
    (rule focal-role? local-name? focal-object? purpose interested-party?
	  priority? constraint-alist)
  (when (not (runnable-p rule))
    (return-from generate-and-schedule-rule-instances 0))
  (loop with list-of-rule-context-vectors =
	(generate-rule-context-vectors
	  rule focal-role? local-name? focal-object? constraint-alist)
	with body = (second (car (box-translation-and-text rule)))
	with maximized-priority =
	(if priority?
	    (highest-priority priority? (rule-priority rule))
	    (rule-priority rule))
	with hash-table = (hash-table-of-rule-instances rule)
	with context-length fixnum = (rule-context-length rule)
	with scheduled-instance-count fixnum = 0
	for rule-context-vector in list-of-rule-context-vectors
	for rule-context = (eval-cons-macro
			     (hash-rule-context-vector
			       context-length rule-context-vector)
			     (eval-cons-macro
			       context-length
			       rule-context-vector))
	for rule-instance = (make-rule-instance)
	for existing-or-new-rule-instance =
	(set-hashed-rule-instance-if-no-entry
	  rule-context hash-table rule-instance)

	doing
    (when (neq rule-instance existing-or-new-rule-instance)
      ;; There was an old rule instance. Delete it if it is no longer valid.

      ;; If the rule-instance being deleted is current-computation-instance,
      ;; then there will be a bombout.  To make sure that this does not happen,
      ;; it should not be the case that the rule context is invalid and the new
      ;; generated context is valid, and they are equal-rule-context, and the
      ;; rule-context is currently being executed.  Proof that this should not
      ;; happen:

      ;; (1) If either context has a null value or a temporary-constant value,
      ;; they are not equivalent.  (2) At the time that current computation
      ;; instance was invoked or resumed, all items in its context were not
      ;; reprocessed.  If one of them has been deleted since then, there would
      ;; be a null in the context of current computation instance, and it could
      ;; not be equivalent to any other context.  (3) However, there could be
      ;; subsequently deactivated items.  (4) Alist validation requires that
      ;; serve-item-p be true for all items in it.  If it is the case that
      ;; serve-item-p is true for all items in generated alists, then it follows
      ;; that a context of a rule-instance retrieved from a hash table (because
      ;; it is equivalent to a generated alist) cannot be invalidated for having
      ;; inactive items.  This completes the proof.

      ;; It is still the case that a rule-instance can be dismissed because it
      ;; is equivalent to a generated one, but has unreprocessed frames. This is
      ;; a valid thing to do, and cannot happen to current-computation-instance.

      ;; The requirement that generate-rule-alists not serve items for which
      ;; serve-item-p is false is discussed in its documentation.

      ;; Note in the so-called proof above the deactivated case INVALIDATES THE
      ;; PROOF!!!  -jra 7/7/91

      ;; We are currently changing deactivate so that any deactivated frames in
      ;; the context vector will be replaced with NIL when they are deactivated.
      ;; This makes the proof above valid again.  -jra & cpm 2/5/92

      ;; By checking that the 

      (unless (or (eq existing-or-new-rule-instance current-computation-instance)
		  (let ((context-vector
			 (invocation-local-var-vector existing-or-new-rule-instance)))
		    (valid-rule-context-vector-p
			   context-vector
			   (rule-environment-length rule)
			   (ri-frame-serial-number existing-or-new-rule-instance)
			   rule
			   nil)))
	(setq existing-or-new-rule-instance rule-instance)
	(setf (get-hashed-rule-instance rule-context hash-table)
	      rule-instance)))

    (cond
      ((eq rule-instance existing-or-new-rule-instance)
       (incff scheduled-instance-count)
       (setf (ri-rule rule-instance) rule)
       (setf (ri-rule-workspace? rule-instance) (superblock? rule))
       (let ((byte-code-body (rule-byte-code-body rule)))
	 (setf (invocation-byte-code-body rule-instance) byte-code-body)
	 (setf (invocation-constant-vector rule-instance)
	       (byte-code-body-constant-vector byte-code-body)))
       (setf (invocation-return-value-count rule-instance)
	     (rule-maximum-received-value-count rule))
       (setf (invocation-return-value-position rule-instance)
	     (rule-return-value-position rule))
		   
       (setf (ri-body rule-instance) body)
       (setf (ri-context rule-instance) rule-context)
       (setf (invocation-local-var-vector rule-instance) rule-context-vector)
       (when (explanation-related-features-enabled-func?)
	 (setf (ri-cached-context-hash-number rule-instance)
	       (rule-context-stored-hash-number rule-context)))
       (frame-serial-number-setf (ri-frame-serial-number rule-instance)
				 (current-frame-serial-number))
;       (setf (ri-validation-predicate rule-instance) nil)
       (setf (ri-priority rule-instance) maximized-priority)
       (cond
	 ((eq purpose 'backward-chaining)
	  (setf (ri-purposes rule-instance)
		(eval-cons (eval-cons 'backward-chaining interested-party?)
			   nil))
	  (add-rule-instance-to-variable-interests interested-party? rule-instance))
	 (t (setf (ri-purposes rule-instance)
		  (eval-cons purpose nil))))
       (when profiling-enabled?
	       (increment-profiling-calls
		 (ri-rule existing-or-new-rule-instance)))
       (setf (ri-state rule-instance) 0)
       (setf (invocation-stack-program-counter rule-instance) 0)
       (setf (ri-hurry-and-repeat-priority rule-instance) nil)
       (setf (ri-initiation-time rule-instance) gensym-time)
       ;; If the scheduling occurs within a window context,
       ;; store that window in the rule-instance.
       (setf (ri-window-for-rule? rule-instance)
	     window-instigating-this-rule-instance?)

       ;; Note that the special variable above will have to be handled
       ;; separately when we finally allow interruptible rule scheduling.  -jra
       ;; 7/7/91
       
       ;added by SoftServe
       (setf (in-lhs-call? rule-instance) nil)
       (setf (return-value-position-after-lhs-call rule-instance) nil)
       ;end of changes 
       
       ;; Also note that there is a bug with the hurry-up-and-repeat stuff and
       ;; the handling of this variable.  Two button clicks from different
       ;; windows could merge, either with or without the hurry up and repeat
       ;; facility.  This should be handled via a context binding.  -jra 7/8/91

       ;; Add this rule instance to any ongoing dynamic displays which
       ;; should be showing it, either because the rule is being
       ;; monitored, or because an object in the rule's context is being
       ;; monitored.
       (add-rule-instance-to-dynamic-rule-displays rule-instance)
       (add-rule-instance-to-generic-rule-displays rule-instance)

       (when current-ri-completion-notification-collection?
	 (eval-push rule-instance
		    (car-of-cons
		      current-ri-completion-notification-collection?))
	 (setf (ri-completion-notification-collection? rule-instance)
	       current-ri-completion-notification-collection?))

       ;; It seems as though there is no difference between a first scheduling,
       ;; and a continuation.
       (schedule-computation-instance-execution
	 rule-instance maximized-priority rule))

      (t
       (reclaim-rule-context rule-context)
       (reclaim-rule-instance rule-instance)
       (let ((scheduled?
	       (future-schedule-task-in-place-p
		 (invocation-schedule-task existing-or-new-rule-instance)))
	     (now? (eq existing-or-new-rule-instance current-computation-instance)))

	 ;; Establish purpose and variable interests.
	 (cond
	   ((eq purpose 'backward-chaining)
	    (setf (ri-purposes existing-or-new-rule-instance)
		  (eval-cons (eval-cons 'backward-chaining  interested-party?)
			     (ri-purposes existing-or-new-rule-instance)))
	    (add-rule-instance-to-variable-interests
	      interested-party? existing-or-new-rule-instance))
	   (t
	    ;; When a rule is scheduled for the purpose of initializing, then
	    ;; the value of generate-and-schedule-rule-instances must be not
	    ;; only the number of new instances, but the number of merged
	    ;; instances.  It is possible for a rule-instance to be established
	    ;; for forward-chaining, and to have the purpose of initializing
	    ;; merged into it.  When this happens, scheduled-instance-count must
	    ;; be incremented, unless the rule was not sheduled, which ought not
	    ;; to occur here.  (If the instance were not scheduled, it will be
	    ;; scheduled later in this code and scheduled-instance-count will be
	    ;; incremented at that point.)
	    (when (and scheduled?
		       (eq purpose 'initializing))
	      (incff scheduled-instance-count))
	    (add-to-set (ri-purposes existing-or-new-rule-instance) purpose)))

	 (cond
	   ((/=f 0 (ri-state existing-or-new-rule-instance))
	    ;; If an in-order rule is already in progress, then the present
	    ;; request is not satisfied by this instance.  The instance must be
	    ;; completed at the highest of the applicable priorities, and a new
	    ;; instance scheduled at the highest of the rule priority, and the
	    ;; priority of the new request(s).  For this purpose, a slot
	    ;; ri-hurry-and-repeat-priority is used.
	    (cond
	      ((not scheduled?)
	       ;; Control the priority of the subsequent execution.
	       (setf (ri-hurry-and-repeat-priority
		       existing-or-new-rule-instance)
		     maximized-priority)
	       (let ((ri-priority (ri-priority existing-or-new-rule-instance)))
		 (cond
		   ((higher-priority-p maximized-priority ri-priority)
		    ;; The final execution occurs at the new priority because it
		    ;; is higher.
		    (setf (ri-priority existing-or-new-rule-instance)
			  maximized-priority)
		    (schedule-computation-instance-execution
		      existing-or-new-rule-instance
		      maximized-priority
		      rule))
		   (t
		    ;; The final execution occurs at its current priority
		    ;; because that is at least as high as the new priority.
		    (schedule-computation-instance-execution
		      existing-or-new-rule-instance
		      ri-priority
		      rule)))))

	      (now?
	       ;; Setting hurry and repeat causes a final execution if this is
	       ;; not final, and then a new invocation after that.
	       (let ((old-hurry-and-repeat-priority
		       (ri-hurry-and-repeat-priority
			 existing-or-new-rule-instance)))
		 (setf (ri-hurry-and-repeat-priority
			 existing-or-new-rule-instance)		     
		       (if (null old-hurry-and-repeat-priority)
			   maximized-priority
			   (highest-priority maximized-priority
					     old-hurry-and-repeat-priority)))))

	      ((higher-priority-p maximized-priority
				  (ri-priority existing-or-new-rule-instance))
	       ;; The rule is already scheduled, but now it must be scheduled at
	       ;; a higher priority.  This will be a final execution, followed
	       ;; by a new one.
	       (setf (ri-priority existing-or-new-rule-instance)
		     maximized-priority)
	       (let ((old-hurry-and-repeat-priority
		       (ri-hurry-and-repeat-priority
			 existing-or-new-rule-instance)))
		 (setf (ri-hurry-and-repeat-priority
			 existing-or-new-rule-instance)		     
		       (if (null old-hurry-and-repeat-priority)
			   maximized-priority
			 (highest-priority maximized-priority
					   old-hurry-and-repeat-priority))))
	       (schedule-computation-instance-execution
		 existing-or-new-rule-instance maximized-priority rule))))

	   ((not scheduled?)
	    ;; Schedule the rule instance.
	    (incff scheduled-instance-count)
	    (let ((ri-priority (ri-priority existing-or-new-rule-instance)))
	      (cond
		((higher-priority-p maximized-priority ri-priority)
		 (setf (ri-priority existing-or-new-rule-instance)
		       maximized-priority)
		 (schedule-computation-instance-execution
		   existing-or-new-rule-instance maximized-priority rule))
		(t
		 (schedule-computation-instance-execution
		   existing-or-new-rule-instance ri-priority rule)))))

	   ((or now?
		(lower-or-equal-priority
		  maximized-priority
		  (ri-priority existing-or-new-rule-instance)))
	    ;; Rule is scheduled and at the appropriate priority.  Nothing to
	    ;; do.
	    nil)

	   (t
	    ;; Rule is scheduled. Up the priority and reschedule.
	    (setf (ri-priority existing-or-new-rule-instance)
		  maximized-priority)
	    (schedule-computation-instance-execution
	      existing-or-new-rule-instance maximized-priority rule))))))

	finally
	  (reclaim-eval-list-macro list-of-rule-context-vectors)
	  (return scheduled-instance-count)))


(defun remove-request-for-rule-instance-invocation (rule-instance variable)
  ;; Remove (BACKWARD-CHAINING variable) from ri-purposes
  (loop for trailing-cons = nil then leading-cons
	for leading-cons on (ri-purposes rule-instance)	
	for item = (car-of-cons leading-cons)
	doing
    (when (and (consp item)
	       (eq (cdr-of-cons item) variable))
      (if trailing-cons
	  (setf (cdr trailing-cons) (cdr-of-cons leading-cons))
	  (let ((cdr (cdr-of-cons leading-cons)))
	    (setf (ri-purposes rule-instance) cdr)
	    ;; If ri-purposes has just been set to nil, then rule has no
	    ;; more purposes.  When this is the case, and the rule is
	    ;; not currently executing, dismiss the rule instance.
	    (unless (or cdr (eq rule-instance current-computation-instance))
	      ;; Remove instance from the rule
	      (delete-hashed-rule-instance
		(ri-context rule-instance)
		(hash-table-of-rule-instances (ri-rule rule-instance))))))
      (reclaim-eval-cons-macro leading-cons)
      (reclaim-eval-cons-macro item)
      (return nil))))

(defun-void maximize-priority-of-rule-instance (rule-instance new-priority)
  (when (higher-priority-p new-priority (ri-priority rule-instance))
    (setf (ri-priority rule-instance) new-priority)
    (change-priority-of-task
      (invocation-schedule-task rule-instance) new-priority)
    (loop for variable
	      in (ri-things-this-rule-instance-is-interested-in rule-instance)
	  do
      (maximize-priority-of-variable variable new-priority))))








;; Third value for role service isn't used.





;; In order: Save the nested state of an every-action

;; The EVERY case of actions IN-ORDER and otherwise.

;; Note that evaluate-designation is more elaborate than is needed for
;; evaluating domains. The domain is (1) bound on the alist or (2)
;; a proper name, in that order. It is important that an alist binding
;; of nil shadow a proper name. A macro for a small piece of evaluate-designation
;; would suffice.


;; 3 August 88



;; Consider a cancel-task-macro

;; New rules must trace.


;; Tracing for rules, provide information for antecedent evaluation,
;; rule processing, rule actuating.



;; August 11

;; Need to use two new flags on rules.


;; August 16

;; Further note on evaluate-designation in ALL iterators! It will copy an existing 
;; alist t-constant, thereby requiring reclaiming of these roles
;; which probably isn't hapening.


#+development
(defun tree-size (tree)
  (if (atom tree) 0
      (+f (tree-size (car tree))
	  (tree-size (cdr tree))
	  1)))

;; Initial rules with for dont work.

;; Where is the cons leak?

;; Use of true and false as values for a symbolic attribute.

;; August 19

;; Connectivity and role serving of deactivated connections.

;; Displays -- Why not edit w/.o table.
;; Displays -- Delete, no ask


;; Sept. 12, 88
;; The assumption in all iterations is that domain-value is not
;; a t-constant. This is because a t-constant does not appear to have 
;; a legitimate use as a domain for a role-server. But it could be
;; called erroneously, and there is no reclaiming of domain-value at present.

;; "if any valve connected to the color of any pump" is an example.




;;; Notes on a scheduling instances of a rule within execution of one of its
;;; instances.

;; The possibility of deleting an instance within its own execution has not been
;; eliminated.  This can happen when the context is invalid, but generated by
;; schedule-rule-alists nonetheless.

;; The firt fix was to correct validate-rule-alist-macro to use serve-item-p.
;; As long as the focal-item was valid, it should not be possible to generate
;; alists that are not valid except in the case of a reprocessed frame appearing
;; in two different incarnations.  This obscure case could be dealt with by not
;; reincarnating frames except at the top level.



;;;; Rule validation
(def-concept rule-validation)
(def-concept rule-conflict-analysis)
(def-concept rule-analysis)


;;;
;;; Format of box-translation-and-text of a rule:
;;;
;;; IF rule:
;;; (((<parse containing 'ANY's>)
;;;   (<parse without the ANY's>) <-- In a FOR-ANY rule, this is in IF form!!
;;;   (NIL (ANY CLASS1 C1 NIL 0) (ANY CLASS2 C2 NIL 1)) <-- THE can be in place of ANY.
;;;   ((CLASS1 C1 0) (ANY CLASS2 C2 NIL 1)) <-- N of these = length of cdr of above?
;;;   ((CLASS2 C2 1) (ANY CLASS1 C1 NIL 0)) <-- THE can be in place of ANY.
;;;   ...)
;;;   &rest text)
;;;
;;; So the CAR is the parse-related stuff and the CDR is the text.
;;; Elements 1-3 of the CAR are, parse-with-any, parse-without-any, bindings?
;;; The rest are also related to the bindings.
;;;
;;; WHERE/HOW DO THE COMPILER LOCALS SHOW UP?
;;; Answer: when using the same attribute name/role for different classes:
;;;
;;; (((IF (AND (> (THE (ATTR1 . COMPILER-ATTR1-1) (ANY CLASS1)) 0)
;;;            (= (THE ATTR2 (THE CLASS1)) #w"hi")
;;;            (< (THE (ATTR1 . COMPILER-ATTR1-2) (ANY CLASS2)) 0))
;;;       (SIMULTANEOUSLY (INFORM (THE OPERATOR) #w"rule2")))
;;;   (RULE-LET
;;;    ((COMPILER-ATTR1-1 (THE ATTR1 CLASS1))
;;;     (COMPILER-ATTR1-2 (THE ATTR1 CLASS2)))
;;;    (IF (AND (> COMPILER-ATTR1-1 0)
;;;             (= (THE ATTR2 CLASS1) #w"hi")
;;;             (< COMPILER-ATTR1-2 0))
;;;        (SIMULTANEOUSLY (INFORM OPERATOR #w"rule2"))))
;;;   (NIL (ANY CLASS1 CLASS1 NIL 0) (ANY CLASS2 CLASS2 NIL 1))
;;;   ((CLASS1 CLASS1 0) (ANY CLASS2 CLASS2 NIL 1))
;;;   ((CLASS2 CLASS2 1) (ANY CLASS1 CLASS1 NIL 0)))
;;;  (LOST-SPACES . 0) #w"if the attr1 of any class1 > 0 and"
;;;  #w"\u2028    the attr2 of the class1 = \"hi\" and the attr1" 53
;;;  (LOST-SPACES . 0) #w"of any class2 < 0" 0 (LOST-SPACES . 0)
;;;  #w"\u2028then post \"rule2\"")

(defun-simple rule-antecedent-parse (rule)
  (gensym-dstruct-bind
      ;; first nil = the parse, second nil = the text
      (((nil (if-or-rule-let antecedent-or-bindings
			     consequent-or-normalized-parse
			     . nil))
	. nil)
       (box-translation-and-text rule))
    (if (eq if-or-rule-let 'if)
	antecedent-or-bindings
	;; RULE-LET case.  So far it's working, but some investogation may need
	;; to be done to try and break it.  Print out
	;; (second (first (box-translation-and-text rule))) to track down
	(second consequent-or-normalized-parse))))

(defun-simple rule-consequent-parse (rule)
  (gensym-dstruct-bind
      ;; first nil = the parse, second nil = the text
      (((nil (if-or-rule-let nil
			     consequent-or-normalized-parse
			     . nil))
	. nil)
       (box-translation-and-text rule))
    (if (eq if-or-rule-let 'if)
	consequent-or-normalized-parse
	;; RULE-LET case.  So far it's working, but some investogation may need
	;; to be done to try and break it.  Print out
	;; (second (first (box-translation-and-text rule))) to track down
	(third consequent-or-normalized-parse))))

;;; `rule-bindings-parse' returns the bindings that typically look like this:
;;; (NIL (ANY CLASS1 C1 NIL 0) (ANY CLASS2 C2 NIL 1))

(defun-simple rule-bindings-parse (rule)
  (gensym-dstruct-bind
      (((nil nil bindings . nil))
       (box-translation-and-text rule))
    bindings))


;; Look at compile-rule and the def-slot-value-compiler for rule.  Also stuff
;; in install.lisp like analyze-compiled-form and friends.  Also walk-rule and
;; friends.  Though if the parse we're looking at is the result of the walk
;; (there's some side-effecting that goes on), can we re-walk, or do we need to
;; re-parse first?  Probably better to re-parse, if possible.  For now, work
;; with what we already have.

;;; `normalize-rule-parse' returns a fresh gensym list of three elements given a
;;; rule: an antecedent, a consequent and bindings.  The contents of the list
;;; are not not owned by this list so must not be modified/reclaimed.

(defun normalize-rule-parse (rule)
  (slot-value-list (rule-antecedent-parse rule)
		   (rule-consequent-parse rule)
		   (rule-bindings-parse rule)))


;; rule conflict = same antecedent, different consequent
;; rule collision = diferent antecedent, same consequent
;; rule redundancy = same antecedent, same consequent

;; rule overlap = antecedent of rule X is "more general" then rule Y
;; incomplete coverage = antecendents don't account for all possibilities

(defun-simple all-clauses-congruent-p (clauses1 clauses2 test)
  (if (and (listp clauses1) (listp clauses2))
      (loop for elt1 in clauses1
	    always
	    (loop for elt2 in clauses2
		  ;; This isn't really the right test as it's considering (= a
		  ;; b) to be different from (= b a).  That will need more
		  ;; infrastructure to fix.  It's also inefficient since we
		  ;; should probably remove elt2's as we find them.
		  if (funcall test elt1 elt2)
		    return t))
      ;; This is the case for uncondiitionally rules which have the symbol TRUE
      ;; as their antecedent.
      (eq clauses1 clauses2)))

(defun-simple rule-parse-antecedents-equivalent-p (normalized-parse1 normalized-parse2)
  (let ((antecedent1 (first normalized-parse1))
	(antecedent2 (first normalized-parse2))
	(bindings1 (third normalized-parse1))
	(bindings2 (third normalized-parse2)))
    (and (all-clauses-congruent-p antecedent1 antecedent2 #'slot-value-equal-p)
	 ;; This part is terribly inefficient since we will be refinding
	 ;; found clauses.  We could copy antecedent2 and remove clauses as
	 ;; we find them, but that takes time too.  At some point if we could
	 ;; figure out how to do it nicely, we'd sort the entire antecedents
	 ;; and then just do a simple comparison, but that was turning into a
	 ;; pain.  For now we'll live with it being slow.  Rules tend not to
	 ;; have more than a handful of clauses anyway.  We could also hash
	 ;; the found things and skip them, but for small numbers of clauses
	 ;; that isn't likely to gain much (and may cost actually).
	 (all-clauses-congruent-p antecedent2 antecedent1 #'slot-value-equal-p)
	 ;; Bindings lists should only contain lists of symbols and integers.
	 ;; We could make this test faster by using a more specific test, but
	 ;; this test is a small part of the overall processing.
	 (and (all-clauses-congruent-p bindings1 bindings2 #'equal)
	      ;; See comment in function above about inefficiency of this.
	      (all-clauses-congruent-p bindings2 bindings1 #'equal)))))

(defun-simple rule-parse-consequents-equivalent-p (normalized-parse1 normalized-parse2)
  ;; Since consequents are side-effecting, the order is significant.
  ;; Do the bindings needs to be considered here?
  (slot-value-equal-p (second normalized-parse1)
		      (second normalized-parse2)))



(defun-simple rule-parses-redundant-p (normalized-parse1 normalized-parse2)
  ;; Since consequents are side-effecting, the order is significant.
  (and (rule-parse-antecedents-equivalent-p normalized-parse1
					    normalized-parse2)
       ;; Do the bindings needs to be considered here?
       (rule-parse-consequents-equivalent-p normalized-parse1
					    normalized-parse2)))
    


;;;
;;; The idea is to create groupings of all the rules involved in analysis into
;;; a list of lists, where each sublist corresponds to a single rule and the
;;; set of rules which are related to that rule in a certain way (say a
;;; conflict/collision) but not related to each other that way, because they
;;; must be redundant with each other.  Then we take this gouping for each
;;; rule, and if there is more than one sublist, output the cliques for that
;;; rule, where each clique is a set of rules that share the relationship among
;;; themselves.
;;;
;;; Redundancy needs to be handled seperately since if rule1 is redundant with
;;; rule2 and rule3, then rule 2 must also be redundant with rule3, so there is
;;; no need to look for cliques, since all rules that are redundant with a
;;; particular rule are always a clique.  This is handled by never trying to
;;; put rules into groups once the row is found.  A somehwat more efficient
;;; method could be used, but it would require a lot of duplicated code.  Doing
;;; it this way allows us to use the same code for all three types of analysis.
;;;
;;; If the recursion blows the stack, which it shouldn't unless the input sets
;;; get VERY large, this will need to be re-written to not be recursive.
;;;
(defun-simple create-cliques-from-groupings (groups)
  (let ((results nil))
    (loop for (starter nil) in (car groups)
	  do
      (let ((partials (create-cliques-from-groupings (cdr groups))))
	(if partials
	    (loop for partial in partials
		  do (eval-push (eval-cons starter partial)
				results)
		  finally (reclaim-eval-list partials))
	    (eval-push (eval-list starter)
		       results))))
    results))


(defun-void sanity-check-rules-for-validation (seq)
  ;; Check that all elements are rules, and have an OK status.  If this check
  ;; winds up being too expensive, we can simply incorporate it into the actual
  ;; processing loop below where it tries to normalize the parses.  -dkuznick,
  ;; 7/27/06 
  (loop for elt being each evaluation-sequence-element of seq
	if (not (framep elt))
	  collect elt into non-frames using gensym-cons
	else
	  if (not (rule-p elt))
	    collect elt into non-rules using gensym-cons
	  else
	    if (not (frame-ok-p elt))
	      collect elt into not-ok using gensym-cons
	finally
	  (when (or non-frames non-rules not-ok)
	    (write-stack-error cached-top-of-stack
	      (tformat "All elements of ~NV must be rules and have a ~
                             status of OK.~%~%"
		       seq)
	      (when non-frames
		(tformat "The following elements are not items: ")
		(write-list-in-chicago-style-given-format
		  non-frames "and" "~NV")
		(tformat ".~%~%"))
	      (when non-rules
		(tformat "The following elements are items but not rules: ")
		(write-list-in-chicago-style-given-format
		  non-rules "and" "~NF")
		(tformat ".~%~%"))
	      (when not-ok
		(tformat "The following elements are rules which are not OK: ")
		(write-list-in-chicago-style-given-format not-ok "and" "~NF")
		(tformat "."))
	      (reclaim-gensym-list non-frames)
	      (reclaim-gensym-list non-rules)
	      (reclaim-gensym-list not-ok)
	      (reclaim-evaluation-sequence seq)))))


(defun-simple gather-normalized-rule-parses-for-validation (seq)
  (loop for rule being each evaluation-sequence-element of seq
	collect (eval-list rule (normalize-rule-parse rule))
	  using eval-cons))


(defun-simple contruct-rule-validation-return-value (clique-groups)
  (loop with elts = nil
	for cliques in clique-groups
	do (loop for clique in cliques
		 do (eval-push (allocate-evaluation-sequence clique)
			       elts)
		 finally (reclaim-eval-list cliques))
	finally
	  (progn
	    (reclaim-eval-list clique-groups)
	    (return (allocate-evaluation-sequence elts)))))

(defun-simple get-rules-according-to-parse-criteria
    (seq row-selector group-selector?)

  (sanity-check-rules-for-validation seq)
  
  (loop with results = nil
	with normalized-parses = (gather-normalized-rule-parses-for-validation
				   seq)
	for (rule parse) in normalized-parses
	do (let ((candidates?
		   ;; Find the "row" in the results for this rule
		   (loop for row in results
			 for (((nil possibly-row-equivalent-parse) . nil) . nil) = row
			 when (funcall row-selector
				       parse
				       possibly-row-equivalent-parse)
			   return row
			   ;; Need to make a new row if we didn't find one
			 finally
			   (let ((new-row
				   (eval-list
				     (eval-list
				       (eval-list rule parse)))))
			     (eval-push new-row results)))))
	     (when candidates?
	       (if group-selector?
		   (loop for group in candidates?
			 for ((candidate-rule candidate-parse) . nil) = group
			 when (funcall group-selector?
				       parse
				       candidate-parse)
			   return (eval-push (eval-list rule parse)
					     (cdr group))
			   ;; If we haven't found the right group yet, start a
			   ;; new one
			 finally
			   (eval-push (eval-list (eval-list rule parse))
				      (cdr candidates?)))
		   ;; If no group-selector, always make a new group.  This is
		   ;; used for the rule-redundancy anlysis
		   (eval-push (eval-list (eval-list rule parse))
			      (cdr candidates?)))))
		   
	     finally
	  (return
	    (prog1
		(loop for groupings in results
		      ;; We only have a clique when there are multiple
		      ;; groupings
		      when (cdr groupings)
			collect
			(create-cliques-from-groupings groupings)
			  into clique-groups using eval-cons
		      finally (return
				(contruct-rule-validation-return-value
				  clique-groups)))
	      ;; clean up
	      (loop for row in results
		    do (loop for group in row
			     do (loop for entry in group
				      do (reclaim-eval-list entry)
				      finally (reclaim-eval-list group))
			     finally (reclaim-eval-list row))
		    finally (reclaim-eval-list results))
	      
	      (loop for rule-parse-pair in normalized-parses
		    for (nil normalized-parse) =  rule-parse-pair
		    do (reclaim-eval-list normalized-parse)
		       (reclaim-eval-list rule-parse-pair)
		    finally (reclaim-eval-list normalized-parses))))))



(defmacro define-g2-rule-analysis-system-procedure
    (name row-selector &optional group-selector?)
  (let ((seq-var (gensym)))
    `(defun-for-system-procedure ,name ((,seq-var sequence))
       (declare (values sequence)
		(keeps-g2-local-variables-valid t))
       (prog1 (get-rules-according-to-parse-criteria ,seq-var
						     #',row-selector
						     ,(and group-selector?
							   `#',group-selector?))
	 (reclaim-evaluation-sequence ,seq-var)))))


(define-g2-rule-analysis-system-procedure g2-get-colliding-rules
    rule-parse-consequents-equivalent-p
  ;; The following will be used to group rules that are NOT colliding with
  ;; one another, hence the inverse of the correct test.
  rule-parse-antecedents-equivalent-p
    )


(define-g2-rule-analysis-system-procedure g2-get-conflicting-rules
    rule-parse-antecedents-equivalent-p
  ;; The following will be used to group rules that are NOT in conflict with
  ;; one another, hence the inverse of the correct test.
  rule-parse-consequents-equivalent-p)


(define-g2-rule-analysis-system-procedure g2-get-redundant-rules
    rule-parses-redundant-p)




;; We probably need to be smarter than just not getting tricked by ordering.
;; If two rules are the same modulo different names for locals, those should be
;; considered equivalent.  We can solve this when we normalize them: we can
;; substitute our own ordered locals.  Then a simple equality test will work.
;; For now we are relying on the BRMS KB level to always supply rules with
;; normalized locals.


;; Component-definition location.  -jra 5/9/96




;;; The slot putter for rule priority sets the new value into the slot of the
;;; frame, and propagates the new priority to any scan task and existing rule
;;; instances.  Whatever the new priority, the scan task will be updated to
;;; reflect it.  For existing instances of rules, the priority will only be
;;; increased, and we'll let any existing instances of these rules to complete
;;; themselves at the old, higher priority.  This must be done since we can't
;;; tell if a high priority has occurred from propagation of the rule priority
;;; or the priority has been upped by some backward chaining.

(def-slot-putter rule-priority (rule new-priority)
  (let ((old-priority (rule-priority rule))
	(rule-scan-interval? (rule-scan-interval rule))
	(hash-table? (hash-table-of-rule-instances rule)))
    (setf (rule-priority rule) new-priority)
    (when (and (runnable-p rule)
	       (/=f old-priority new-priority))
      (when (and rule-scan-interval?
		 (schedule-task-in-place-p (rule-scan-task? rule)))
	(change-priority-of-task (rule-scan-task? rule) new-priority))
      ;; The rule could be runnable but have no hash-table-of-rule-instances
      ;; when we are initializing.
      (when hash-table?
	(loop for rule-instance being each hash-value of hash-table?
	      do
	  (when (higher-priority-p new-priority (ri-priority rule-instance))
	    (setf (ri-priority rule-instance) new-priority)
	    (schedule-computation-instance-execution
	      rule-instance new-priority rule)
	    (if (schedule-task-in-place-p
		  (ri-final-continuation-task rule-instance))
		(change-priority-of-task
		  (ri-final-continuation-task rule-instance)
		  new-priority))))))
    new-priority))

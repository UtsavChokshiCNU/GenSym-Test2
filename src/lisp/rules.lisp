;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module RULES

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Michael Levin





;;;; Note on Actions In Order


;;; We just had a discussion in which we we talking about how bindings would be
;;; used in actions, both in the all at once case and in the actions in order
;;; case.  The conclusion was that all at once actions would be nested at the
;;; deepest level in rule bodies, and that "every" in action designations would
;;; be bound around the actions but would not be part of the defining context
;;; for a rule.

;;; There was a question about what to do for the in-order style of actions,
;;; since some of these actions might be performed outside of the recursive
;;; dynamic extent of the antecedent execution.  The conclusion was that a
;;; continuation of in-order actions would save the environment and execute the
;;; remainder of the actions within that environment.  Note that this has
;;; implications on the execution environments of in-order actions.  If
;;; something is bound to a local name or used in the short name form (using
;;; "the temp" after "the temp of F2") then the second form will use the bound
;;; object.  If the temp in this case was a variable, note that the variable
;;; will be bound, and further references to it will produce the current value.
;;; However, in cases where local names are given to the services of roles which
;;; return temporary constants, then the constant will be bound and the value of
;;; that constant will be used in subsequent roles.  The user needs to be
;;; informed of which cases are which, and in fact it would be nice if we gave
;;; users the ability to exploit these features.  A further clarification of
;;; this discussion needs to be presented to the documentation people.  -jra
;;; 7/14/88

;; To CHAINING

(declare-forward-reference backward-chaining-link-p-function function)
(declare-forward-reference backward-link-focus-function function)
(declare-forward-reference forward-chaining-link-p-function function)
(declare-forward-reference forward-link-focus-function function)
(declare-forward-reference forward-link-second-focus-function function)
(declare-forward-reference install-chaining-links function)
(declare-forward-reference deinstall-chaining-links function)
(declare-forward-reference generate-forward-and-backward-chaining-links function)
(declare-forward-reference rule-instance-completed function)

;; To GRAMMAR0

(declare-forward-reference truth-value-phrase-p function)

;; To GRAMMAR7

(declare-forward-reference explanation-related-features-enabled-func? function)

;; To ACTIVATE

(declare-forward-reference handle-completion-of-initial-rule function)
(declare-forward-reference in-suspend-resume-p variable)

;; To EXPLAIN

(declare-forward-reference
  update-backward-chaining-displays-function function)

(declare-forward-reference
  backward-chaining-displays variable)

;; To QUERIES

(declare-forward-reference
  remove-rule-instance-from-dynamic-rule-displays function)

(declare-forward-reference
  remove-rule-instance-from-generic-rule-displays function)

;; To PROC-UTILS

(declare-forward-reference
  schedule-computation-instance-execution function)

(declare-forward-reference
  wake-up-code-body-invocation function)

(declare-forward-reference
  clean-up-ri-completion-notification-collection-back-pointer function)

;; To STACK-COMP

(declare-forward-reference compile-rule-for-stack function)

(declare-forward-reference delete-dynamic-rule-displays-for-rule-or-object function)
(declare-forward-reference generate-and-schedule-rule-instances function)




;;;; IF rules



;;; The internal format of an IF rule is:
;;; (IF antecedent conclusions-and-actions)
;;; The internal syntax of the WHEN rule is the same except for the word THEN.
;;; The difference between these two types of rules is that an IF rule may be
;;; invoked whenever it appears on an active concurrent background, because it
;;; represents general knowledge which is relevent at that time. A WHEN rule is
;;; regarded as an active timing mechanism rather than a piece of general
;;; knowledge. Under the same circumstances, a WHEN rule is invoked when its
;;; antecedent becomes true because it is time to do something.




;;; An `initial rule' differs from a rule only in that it is executed promptly
;;; at start time, and then deactivated.

;;; When there is a focal role, there must be a focal-entity. A global rule
;;; execution has a null focal role and a null focal entity. There is a rule
;;; instance for each pair of focal role and focal entity that the rule has
;;; encountered. It is probably unusual for an entity to be focal in more than
;;; one role.  Therefore, accessing instances based on entities is the most
;;; efficient way to get one.


;;; (invoke-rule rule focal-role? focal-entity? wake-up-mode alist purpose local-name?)
;;; 1. Find or create an instance.

;;; 2. Bind all contextual variables and the alist which gets 
;;; the pair of the role and entity if they exist. 

;;; 3a. The antecedent is not FOR: If the rule evaluates with a truth-value >=
;;; truth-threshold then execute actions.  Actions are executed with a
;;; contextual certainty (that of the truth-value or its negation if an else
;;; action), and an expiration from the antecedent.

;;; If the antecedent fails to evaluate, then any variables that failed during
;;; its invocation are put on wake-up. If any of them get a value, the instance
;;; will be invoked again. A wake-up invocation is characterized as such by a
;;; parameter of invoke-rule. But in this case, it does not differ from any
;;; other invocation.


;;; The slot rule-scan-interval of a rule is either nil or an
;;; interval in seconds.

;;; In the latter case, the rule is put on scan. 

;;; There are 2 possible ways for global execution of generic rules, all at
;;; once, and distributed. At present, only the all at once method is used.

;;; A rule may have either IF or WHEN as its keyword. This may effect the
;;; defaulting of the ability to backward chain.

;;; Purpose (an argument of invoke-rule) can be FORWARD-CHAINING,
;;; BACKWARD-CHAINING, FOCUSING, INVOKING, SCANNING, or INITIALIZING.
;;; It is no longer used as a qualifier for selecting compilations,
;;; but it is placed in rule instances for informational purposes. Note that
;;; the first purpose may prevail, making it not very useful.


;;; ** NUPEC MODIFICATION TO RULES **

;;; The following changes are only available when compiling with NUPEC in the
;;; *features* list.

;;; This software development was funded by NUPEC.

;;; To facilitate the emphasis of essential information in rules and to hide the
;;; details of procedure invocation, display management, etc. within rules, a
;;; new slot, nupec-extra-actions, has been added to rules.  This slot can
;;; contain additional actions to be carried out when a rule fires.  The
;;; contents of this slot is not visible in the rule text.  It is only visible
;;; in the rule table, and is user editable.  During rule firing, these extra
;;; actions are executed after the main actions (using the same ordering of
;;; actions, e.g., in order or simultaneous).


;;; NUPEC-extra-actions slot grammar:
;;;   "action {and action}"
;;;   e.g.,   "conclude that x = 123 and conclude that valve1 is off and focus
;;;            on x and focus on valve1"


;;; This new slot was implemented by modifying the slot-value-compiler for rules
;;; (i.e., box-translation-and-text slot-value-compiler) so that the value of
;;; the NUPEC-extra-actions slot (if any) is added to the rule parse (in
;;; the box-translation-and-text slot) when the rule is modified.  A
;;; slot-value-compiler was written for the NUPEC-extra-actions slot, but the
;;; the rule translation update is not done there.  (It would be complicated).
;;; When the nupec-extra-actions slot is modified, the slot-putter calls the
;;; editor using the current rule text.  The editor invokes the rule compiler
;;; which reparses the rule with the extra actions, as described above.
;;;
;;;
;;; The slot-value-compilers modify the rule translation in
;;; box-translation-and-text.  The format of this slot is:
;;;
;;;    box-translation-and text ::= (translation . text)
;;;
;;;    translation ::= (parsed-rule body . alist-of-prefix-pairs)
;;;
;;; The translation is modified to contain the NUPEC-extra-actions at the end of
;;; the current rule actions in the parsed-rule.  This modification does not
;;; change the format of parsed-rule.




(def-class (rule statement (foundation-class rule) define-predicate
		 (class-export-comment
		   "From the original document the following attributes were shown exported from rule: reconcile.
<ul>
; Most of these are from computation-style, and should proably be subsumed.
<LI>invocable-via-backward-chaining: logical-value,
<LI>invocable-via-forward-chaining: logical-value,
<LI>may-cause-data-seeking: logical-value,
<LI>may-cause-forward-chaining: logical-value,
<LI>notes: ( [ source: symbol, note: text ] * ),
<LI>authors: ([ name: name, date: gensym-time ] * ),
<LI>text,
<LI>scan-interval: time-interval-part,		; rule-scan-interval

<li>focal-classes: ( class-name *),
<LI>focal-objects: ,
<LI>categories,		; rule-categories,
<LI>rule-priority: priority,
<LI>depth-first-backward-chaining-precedence,
<LI>timeout-for-rule-completion,
<!-- nupec-extra-actions,-->
<LI>rule-scan-task?,
<LI>focal-roles-for-chaining,
<LI>rule-keyword
</ul>"))
  ;; initialize method now deals with initial setup -- this slot's init form
  ;; will now be nil, and inherited. (MHD 7/18/94)
;  (frame-status-and-notes (:funcall slot-value-cons-function incomplete nil))
  (frame-flags #.(+ invocable-via-backward-chaining-flag
		    invocable-via-forward-chaining-flag
		    may-cause-data-seeking-flag
		    may-cause-forward-chaining-flag)
	       vector-slot system (type rule-frame-flags))
  (frame-author-or-authors nil (type authors-with-time-of-last-edit?))
  (frame-change-log nil (type frame-change-log))
  ;; Added the rule slot-feature to box-translation-and-text.  cpm, 4/19/91
  (box-translation-and-text nil
     (type rule text rule) vector-slot system select-changes)
  ;; Only displayed in the attributes table when nupec is authorized.
  (nupec-extra-actions
    nil (type nupec-extra-action-list text) 
    (do-not-put-in-attribute-tables not-nupec) lookup-slot system)

  ;; This must be a constant. 0 means no scan interval.
  (rule-scan-interval nil vector-slot system user-overridable
		      (type positive-quantity-interval?))
  (rule-scan-task? nil vector-slot system)
  (focal-classes nil vector-slot system user-overridable (type focal-classes))
  (focal-objects nil system user-overridable vector-slot (type focal-objects))
  (rule-categories nil system user-overridable vector-slot (type categories))
  (focal-roles-for-chaining nil system vector-slot save)
  (rule-priority 6 system user-overridable vector-slot (type priority))
  (tracing-and-breakpoints
    nil system user-overridable lookup-slot save (type tracing-and-breakpoints))
  (hash-table-of-rule-instances nil vector-slot system)
  (backward-chaining-precedence 1 vector-slot system user-overridable
				(type positive-integer))
  (timeout-for-rule-completion
    default vector-slot system user-overridable (type interval?-or-default))
  ;; do-not-clone feature added to chaining links slot, 6/26/91, cpm & jra.
  (rule-chaining-links nil vector-slot system save do-not-clone)
  (rule-byte-code-body nil vector-slot system save do-not-clone)
  ;; The rule keyword is if, initially, when, or whenever.
  (rule-keyword nil vector-slot system save)
  (rule-context-length 0 vector-slot system save)
  (rule-environment-length 0 vector-slot system save)
  (rule-return-value-position 0 vector-slot system save)
  (rule-maximum-received-value-count 0 vector-slot system save)
  )

(define-slot-alias depth-first-backward-chaining-precedence backward-chaining-precedence)


(def-substitute-for-old-class if-rule rule)	; keep this until 1989, at least

(declare-side-effect-free-function backward-chaining-precedence-function)

(defun-simple backward-chaining-precedence-function (rule)
  (backward-chaining-precedence rule))

(declare-side-effect-free-function rule-chaining-links-function)

(defun-simple rule-chaining-links-function (rule)
  (rule-chaining-links rule))

(declare-side-effect-free-function rule-byte-code-body-function)

(defun-simple rule-byte-code-body-function (rule)
  (rule-byte-code-body rule))


 
;(def-structure (rule-instance
;		 (:constructor make-rule-instance
;			       (focal-entity? focal-role? compiled-rule-pair generic-rule
;					      purpose-of-rule-instance)))
;  focal-entity?
;  focal-role?
;  compiled-rule-pair
;  generic-rule
;  purpose-of-rule-instance

;  (rule-instance-time-of-most-recent-invocation? nil)

;  (variables-that-can-wake-up-this-rule-instance nil)
;  rule-instance-wake-up-time

;  task-to-complete-rule-instance
;  pamo-structure

;  things-this-rule-instance-is-interested-in
;  task-to-wake-up-rule-instance
;  )



;;; A `rule-context' is an eval cons list containing a cached hash value for
;;; this context, a count of the number of elements of the environment vector
;;; that are considered part of the context, and a vector which is the
;;; environment (i.e. local-var) vector for the rule.  The vector may be quite a
;;; bit longer than the number of elements that are part of the context.  These
;;; extra elements hold values of local variables for the rule that are not part
;;; of the context, i.e. part of the identity of this invocation of the rule.

(defmacro rule-context-stored-hash-number (rule-context)
  `(car-of-cons ,rule-context))

(defmacro rule-context-element-count (rule-context)
  `(car-of-cons (cdr-of-cons ,rule-context)))

(defmacro rule-context-vector? (rule-context)
  `(cdr-of-cons (cdr-of-cons ,rule-context)))




;;; Two rule contexts are equal if there are no temporary-constants as values
;;; and corresponding values are eq.  It is assumed that both contexts have the
;;; same set of symbols.  Equal-rule-context should not be considered a valid
;;; test if either context is not valid.

;; Note that JRA and ML recently (10/20/89) decided that temporary-constants are
;; never considered equal.  Previously, they always were.  It is now the case
;; that one can iterate over a list of data with duplicates, creating distinct
;; rule invocations.

(defun equal-rule-context (rule-context-1 rule-context-2)
  (or (eq rule-context-1 rule-context-2)
    (when (=f (rule-context-element-count rule-context-1)
	      (rule-context-element-count rule-context-2))
      (loop with context-vector-1 = (rule-context-vector? rule-context-1)
	    with context-vector-2 = (rule-context-vector? rule-context-2)
	    for index from 0 below
		(rule-context-element-count rule-context-1)
	    for value1 = (svref context-vector-1 index)
	    for value2 = (svref context-vector-2 index)
	    always (and (eq value1 value2)
			value1
			(not (evaluation-value-p value1)))))))

(defun-void handle-rule-category-completion-notification (rule-instance)
  (let ((completion-notification-collection?
	  (ri-completion-notification-collection? rule-instance)))
    (when completion-notification-collection?
      ;; always nil out the slot so if it comes back to life it will be ok.
      (setf (ri-completion-notification-collection? rule-instance) nil)
      (unless (setf (car completion-notification-collection?)
		    (delete-eval-element
		      rule-instance
		      (car completion-notification-collection?)))
	;; If we get here, it means the last rule-instance of the set started
	;; via invoke-with-wait has just completed, so it's time to wake up the
	;; code-body which did the initial invoke, and clean up the list
	;; completely. -dkuznick, 7/25/05
	(let ((code-body-invocation? (cadr completion-notification-collection?)))
	  ;; The only time there won't be one is when it has been aborted
	  ;; between the time it started waiting and "now". -dkuznick, 8/15/05
	  (when code-body-invocation?
	    ;; To keep the code-body-invocation "clean" before it gets
	    ;; scheduled again since it's no longer waiting. -dkuznick, 8/15/05
	    (clean-up-ri-completion-notification-collection-back-pointer
	      code-body-invocation?)
	    (wake-up-code-body-invocation code-body-invocation?)))
	(reclaim-eval-list completion-notification-collection?)))))

(defun dismiss-rule-instance (rule-instance)
  ;; The rule context has already been reclaimed by the hash table key
  ;; reclaimer.
  (setf (ri-context rule-instance) nil)
  (setf (invocation-local-var-vector rule-instance) nil)
  (let ((purposes (ri-purposes rule-instance)))
    (when purposes
      (setf (ri-purposes rule-instance) nil)
      (loop for purpose in purposes
	    doing
	(cond
	  ((consp purpose)
	   (rule-instance-completed (cdr-of-cons purpose) rule-instance)
	   (reclaim-eval-cons-macro purpose))
	  ((eq purpose 'initializing)
	   (handle-completion-of-initial-rule rule-instance))))
      (reclaim-eval-list-macro purposes)))
  (let ((interesting-variables
	  (ri-things-this-rule-instance-is-interested-in rule-instance)))
    (when interesting-variables
      (setf (ri-things-this-rule-instance-is-interested-in rule-instance) nil)
      (loop for variable in interesting-variables
	    do
	(remove-request-for-variable-value variable rule-instance))
      (reclaim-eval-list-macro interesting-variables)))

  (update-backward-chaining-displays rule-instance)
  (remove-rule-instance-from-dynamic-rule-displays rule-instance)
  (remove-rule-instance-from-generic-rule-displays rule-instance)
  (let ((variable-list? (ri-explanation-variables rule-instance)))
    (when variable-list?
      (reclaim-evaluation-variables-list variable-list?)
      (setf (ri-explanation-variables rule-instance) nil)))
  
  (cancel-task (ri-final-continuation-task rule-instance))
  (cancel-task (invocation-schedule-task rule-instance))
  ;; Handle completion-notification if necessary
  (handle-rule-category-completion-notification rule-instance)
  (reclaim-rule-instance rule-instance))

(defun reclaim-rule-context (rule-context)
  (let* ((second-cons (cdr-of-cons rule-context))
         (vector? (cdr-of-cons second-cons)))
    (when vector?
      (reclaim-environment-vector vector?))
    (reclaim-eval-list-given-tail rule-context second-cons)))


(def-hash-table hashed-rule-instance
    :hash-function-or-macro rule-context-stored-hash-number
    :key-comparitor equal-rule-context
    :key-reclaimer reclaim-rule-context
    :entry-reclaimer dismiss-rule-instance)






;;;; Activate methods for rules



;;; Within-activate-for-kb-workspace is t when rules are activated within a
;;; kb-workspace. This causes activate-for-rule not to schedule a scan task
;;; because one will be scheduled by activate-for-kb-workspace. However,
;;; when a rule is activated for some other reason, such as after editing or
;;; because it has individually been deactivated, then activate-for-rule should
;;; schedule a cyclic task.

(def-system-variable within-activate-for-kb-workspace rules nil)

(def-class-method activate (rule)
  (unless (active-p rule)
    (funcall-superior-method rule)
    (unless in-suspend-resume-p
      (startup-rule-execution-if-appropriate rule 'activate))))

(def-class-method deactivate (rule)
  (when (active-p rule)
    (funcall-superior-method rule)
    (unless in-suspend-resume-p
      (startup-rule-execution-if-appropriate rule 'activate))))

(def-class-method manually-enable (rule)
  (funcall-superior-method rule)
  (startup-rule-execution-if-appropriate rule 'edit))

(def-class-method manually-disable (rule)
  (funcall-superior-method rule)
  (shutdown-rule-execution-if-appropriate rule nil))

(def-class-method note-runs-while-inactive-change (rule)
  (funcall-superior-method rule)
  (if (runs-while-inactive-p rule)
      (startup-rule-execution-if-appropriate rule 'edit)
      (shutdown-rule-execution-if-appropriate rule 'edit)))

(def-class-method initialize (rule)
  (funcall-superior-method rule)
  (when (hash-table-of-rule-instances rule)
    (reclaim-hashed-rule-instance (hash-table-of-rule-instances rule)))
  (setf (hash-table-of-rule-instances rule) (make-hashed-rule-instance))
  (startup-rule-execution-if-appropriate rule 'initialize))

(def-class-method initialize-after-reading (rule)
  (funcall-superior-method rule)
  ;; The following is just a KB fixup for a potential corruption in embedded
  ;; rules present in KBs that were saved in 1.11B. -mhd, 10/24/91
  (if (and (not new-saved-kb-format-p)
	   (get-kb-parent-information rule)
	   (frame-representations rule))
      (setf (frame-representations rule) nil))
  (when (hash-table-of-rule-instances rule) 
    (reclaim-hashed-rule-instance (hash-table-of-rule-instances rule)))
  (setf (hash-table-of-rule-instances rule) (make-hashed-rule-instance))
  (startup-rule-execution-if-appropriate rule 'initialize))

(def-class-method cleanup (rule)
  (funcall-superior-method rule)
  (delete-dynamic-rule-displays-for-rule-or-object rule)
  (cancel-task (rule-scan-task? rule))
  (when (hash-table-of-rule-instances rule)	
    (reclaim-hashed-rule-instance (hash-table-of-rule-instances rule))
    (setf (hash-table-of-rule-instances rule) nil))
  (change-slot-value rule 'rule-chaining-links nil))




;;; The function `startup-rule-execution-if-appropriate' takes a rule and a
;;; symbol naming the kind of tevent that this function should respond to.  The
;;; kinds of events are INITIALIZE, ACTIVATE, and EDIT.  This function will
;;; launch an scanning of this (as appropriate) and will schedule invocations of
;;; initially rules that are also running-while-inactive.

;;; Note that when activating, the rule will not yet be active.  Therefore, this
;;; operation cannot check runnable-p, but instead must instead check the
;;; runs-while-inactive and manually-disabled flags instead.  Also note that the
;;; scanning task is scheduled regardless of whether or not the rule is OK.
;;; This task will do nothing if the rule does not have a valid compilation.

;;; Running while inactive initially rules are invoked when they are loaded in
;;; from KBs.  This function gets called from both the initialize and
;;; initialize-after-reading methods, but the rule can only be runnable within
;;; the initialize-after-reading method, since it will be incomplete when first
;;; created.  Therefore, if we are not activating? and the rule runs-while-inactive
;;; and is runnable, then invoke it for it initial execution.

(defun-void startup-rule-execution-if-appropriate (rule event)
  (let ((runs-while-inactive? (runs-while-inactive-p rule)))
    (when (or (and (not runs-while-inactive?)
		   (eq event 'activate)
		   (not within-activate-for-kb-workspace))
	      (and runs-while-inactive? (not (eq event 'activate))))
      (let ((scan-interval (rule-scan-interval rule)))
	(when scan-interval
	  (with-future-scheduling
	      ((rule-scan-task? rule)
	       (rule-priority rule)
	       (g2-future-interval 1)
	       (if (fixnump scan-interval)
		   (coerce-fixnum-to-gensym-float scan-interval)
		   (managed-float-value scan-interval))
	       nil
	       runs-while-inactive?)
	    (invoke-rule-universally rule)))))
    (when (and runs-while-inactive?
	       (eq event 'initialize)
	       (initial-rule-p rule)
	       (runnable-p rule))
      (generate-and-schedule-rule-instances
	rule nil nil nil 'initializing nil (rule-priority rule) nil))))





;;; The function `shutdown-rule-execution-if-appropriate' takes a rule and a
;;; flag indicating if the rule is being deactivated or not.  Depending on
;;; whether or not this is a rule enabled for running while inactive and whether
;;; this is just being deactivated, any existing rule-instances will be cleared.

(defun-void shutdown-rule-execution-if-appropriate (rule deactivating?)
  (unless (and deactivating?
	       (runs-while-inactive-p rule))
    (cancel-task (rule-scan-task? rule))
    #-SymScale
    (when (hash-table-of-rule-instances rule)
      (reclaim-hashed-rule-instance (hash-table-of-rule-instances rule)))
    #-SymScale
    (setf (hash-table-of-rule-instances rule) (make-hashed-rule-instance))

    ;; this version makes sure other threads never see a reclaimed hash table
    #+SymScale
    (let* ((old? (hash-table-of-rule-instances rule))
	   (new (when old? (make-hashed-rule-instance))))
      (when old?
	(if (compare-and-swap (hash-table-of-rule-instances rule) old? new)
	    (reclaim-hashed-rule-instance old?)
	  (reclaim-hashed-rule-instance new))))))



;;; The function `rule-translation-keyword' takes the parsed translation (in
;;; other words, the parse of a rule) and returns one of the symbols, IF, WHEN,
;;; WHENEVER, or INITIALLY.

(defun rule-translation-keyword (translation)
  (loop for body = translation then (third body)
	until (neq (car body) 'for)
	finally
	  (return (car body))))

(def-slot-putter rule-scan-interval (rule new-value)
  (let* ((old-value (rule-scan-interval rule))
	 (rule-keyword (rule-keyword rule)))
    (when (or (memq rule-keyword '(whenever initially))
	      (initial-rule-p rule))
      (reclaim-slot-value new-value)
      (setq new-value nil))
    (setf (rule-scan-interval rule) new-value)
    (when (and (runnable-p rule)
	       (not (equal-scan-intervals old-value new-value)))
      (when old-value
	(cancel-task (rule-scan-task? rule)))
      (when new-value
	(with-future-scheduling
	    ((rule-scan-task? rule) (rule-priority rule) (g2-future-interval 1)
	     (if (fixnump new-value)
		 (coerce-fixnum-to-gensym-float new-value)
		 (managed-float-value new-value))
	     nil
	     (runs-while-inactive-p rule))
	  (invoke-rule-universally rule))))
    new-value))

(defun-simple equal-scan-intervals (value1 value2)
  (or (eq value1 value2)
      (and (fixnump value1) (fixnump value2) (=f value1 value2))
      (and (managed-float-p value1) (managed-float-p value2)
	   (=e (managed-float-value value1) (managed-float-value value2)))))






;;;; Rule Walker




;;; The following section implements a walker for rules.  The function
;;; `walk-rule' copies the given rule and then calls the given walker function
;;; on every expression and designation within the rule.  The returned values
;;; from the walker are spliced back into the rule in the location of the
;;; expression or designation that was given to each invocation of the walker.
;;; The function `walk-rule-without-copying' does the same thing, but by
;;; modifying the given rule parse.

(defun walk-rule (rule-parse-to-walk walker)
  (walk-rule-without-copying (copy-for-phrase rule-parse-to-walk) walker))

(defun walk-rule-without-copying (rule walker)
  (cond ((eq (car rule) 'for)
	 (setf (second rule)
	       (walk-designation (second rule) walker))
	 (setf (third rule)
	       (walk-rule-without-copying (third rule) walker)))
	(t
	 (setf (second rule)
	       (walk-expression (second rule) walker))
	 (setf (third rule)
	       (walk-rule-actions (third rule) walker))))
  rule)

(defun walk-rule-actions (action walker)
  (cond ((memq (car action) '(and in-order simultaneously))
	 (loop for subaction-cons on (cdr action) do
	   (setf (car subaction-cons)
		 (walk-rule-actions (car subaction-cons) walker))
	       finally (return action)))
	(t
	 (setf (cdr action)
	       (walk-action-body-given-template
		 (cdr action)
		 (or (cdr (assq
			    (car action)
			    '((conclude place-reference-expression
			       . expression-list)
			      (conclude-not place-reference-expression
			       . expression-list)
			      (change-the-text-of-attribute
			       place-reference-expression
			       . expression-list))))
		     (cdr (lookup-action-template (car action)))
		     '(designation . expression-list))
		 walker))
	 action)))

(defun walk-action-body-given-template (given-body template walker)
  ;; First recurse onto any conses in the template.
  (loop with body = given-body
	with body-trailer = nil
	while (and (consp template) (consp body))
	do
    (setf (car body)
	  (walk-action-body-given-template
	    (car-of-cons body) (car-of-cons template) walker))
    (setq template (cdr-of-cons template))
    (setq body-trailer body)
    (setq body (cdr-of-cons body))
	finally
	  ;; We get down to here given the final cdr of the template (which may not be
	  ;; NIL) or if the argument was not a cons in the first place.  The other case
	  ;; is where we ran out of body before we ran out of template, which we decided
	  ;; is ok in these template things, since they have no way of describing
	  ;; optional arguments.
	  (let ((final-body
		  (if (symbolp template)
		      (case template
			((expression message-text)
			 (walk-expression body walker))
			((designation)
			 (walk-designation body walker))
			((place-reference-expression)
			 ;; Ignore the outermost roles of place-reference
			 ;; expressions, since adding local names gags the
			 ;; type-based transformations of evaluating the
			 ;; expressions for place-reference.  -jra 6/27/95
			 (when (and (consp body)
				    (memq-p-macro
				      (car-of-cons body) '(any the)))
			   (loop for domain-cons on (cddr body) do
			     (setf (car domain-cons)
				   (walk-expression
				     (car-of-cons domain-cons) walker))))
			 body)
			((expression-list)
			 (loop for expression-cons on body do
			   (setf (car expression-cons)
				 (walk-expression (car-of-cons expression-cons) walker)))
			 body)
			((designation-list)
			 (loop for designation-cons on body do
			   (setf (car designation-cons)
				 (walk-designation (car-of-cons designation-cons) walker)))
			 body)
			((message-designation)
			 ;; First argument to inform
			 (if (or (equal body '(the operator))
				 (eq body 'operator))
			     body
			     (walk-designation body walker)))
			((inform-option)
			 (setf (second body)
			       (if (eq (car body) 'duration)
				   (walk-expression (second body) walker)
				   (walk-designation (second body) walker)))
			 body)
			((show-or-hide-argument-list)
			 (loop for expr?-cons on body do
			   (when (car expr?-cons)
			     (setf (car expr?-cons)
				   (walk-expression (car expr?-cons) walker))))
			 body)
			((color-changes)
			 ;; Punt
			 body)
			((create-connection-spec)
			 ;; Punt
			 body)
			((other nil)
			 body)
			(t
			 #+development
			 (cerror "Continue" "Unknown action template type ~A" template)
			 body))
		      body)))
	    (return
	      (cond (body-trailer
		     (setf (cdr body-trailer) final-body)
		     given-body)
		    (t
		     final-body))))))

(defun walk-expression (expression walker)
  (cond
    ((phrase-float-p expression)
     (funcall walker expression))
    ((or (phrase-sequence-p expression)
	 (phrase-structure-p expression)
	 (truth-value-phrase-p expression))
     (funcall walker expression))
    ((consp expression)
     (let ((operator (car expression)))
       (cond
	 ((designation-p expression)
	  (walk-designation expression walker))
	 ((symbolp operator)
	  (let ((function-template (lookup-function-template operator)))
	    (cond (function-template
		   (walk-expression-given-template
		     expression function-template walker))
		  (t
		   (loop for sub-expr-cons on (cdr-of-cons expression)
			 do
		     (setf (car sub-expr-cons)
			   (walk-expression (car sub-expr-cons) walker)))
		   (funcall walker expression)))))
	 ((or (numberp operator) (phrase-float-p operator))
	  (funcall walker operator))
	 (t
	  #+development
	  (cerror "continue" "Malformed expression in walker, ~a" expression)
	  expression))))
    ((symbolp expression)
     (walk-designation expression walker))
    (t
     (funcall walker expression))))

(defun walk-expression-given-template (expression template walker)
  (loop for expr-arg-cons on (cdr expression)
	for expr-arg = (car-of-cons expr-arg-cons)
	for template-type in (cdr template)
	do
    (case template-type
      ((expression)
       (setf (car expr-arg-cons)
	     (walk-expression expr-arg walker)))
      ((designation)
       (setf (car expr-arg-cons)
	     (walk-designation expr-arg walker)))
      ((scope)
       (let ((new-designation (gensym-cons 'any expr-arg)))
	 (setf (car expr-arg-cons)
	       (cdr (walk-designation new-designation walker)))
	 (reclaim-gensym-cons new-designation)))
      ((other)
       ;; Quoted constants and the like.  Don't walk them.
       nil)
      (t
       #+development
       (cerror "continue" "Unknown template type ~A." template-type)
       nil)))
  (funcall walker expression))

(defun walk-designation (designation walker)
  (when (consp designation)
    (loop for domain-cons on (cddr designation)
	  do
      (setf (car domain-cons)
	    (walk-expression (car-of-cons domain-cons) walker))))
  (funcall walker designation))




;;; The function `maybe-add-more-local-names' takes a parse of a rule and
;;; returns a new phrase cons rule that may have more local names declared and
;;; used within the rule.  It happens in cases where there is more than one
;;; designation with the same implicit local name (typically a class, maybe an
;;; attribute).  In this case, the forward chaining compilations can become
;;; confused about which designation is the focal point within a chaining
;;; compilation, and the compilations are then confused.  This function will
;;; return a parse with more local names inserted, where necessary.

(defvar rule-local-name-references)

(defvar current-rule-local-name-reference-info)

(defun get-rule-local-name-reference-info (implicit-local-name)
  (or (assq implicit-local-name rule-local-name-references)
      (let ((new-info (phrase-list
			implicit-local-name
			0		; defining expressions count
			nil		; defined explicit local names
			0)))		; implicit references count
	(phrase-push new-info rule-local-name-references)
	new-info)))

;; TODO: use DEF-STRUCTURE instead. --binghe

(defmacro rlnri-implicit-local-name (reference-info)
  `(car ,reference-info))

(defmacro rlnri-defining-expressions-count (reference-info)
  `(second ,reference-info))

(defmacro rlnri-defined-explicit-local-names (reference-info)
  `(third ,reference-info))

(defmacro rlnri-implicit-references-count (reference-info)
  `(fourth ,reference-info))

(defun collect-local-name-reference-info (expr)
  (when (and (consp expr)
	     (not (phrase-sequence-p expr))
	     (not (phrase-structure-p expr))
	     (not (truth-value-phrase-p expr))
	     (or (eq (car-of-cons expr) 'the)
		 (eq (car-of-cons expr) 'any))
	     (not (ignore-role-in-walk-p
		    (simple-role-of-role (second expr)))))
    (let* ((role (second expr))
	   (implicit-local-name (atomic-naming-element-of-role role))
	   (reference-info
	     (get-rule-local-name-reference-info implicit-local-name))
	   (implicit-reference?
	     (and (eq (car-of-cons expr) 'the)
		  (symbolp (second-of-long-enough-list expr))
		  (null (cdr-of-cons (cdr-of-cons expr)))))
	   (explicit-local-name?
	     (get-explicitly-specified-local-name-of-role-if-any role)))
      (if implicit-reference?
	  (incff (rlnri-implicit-references-count reference-info))
	  (incff (rlnri-defining-expressions-count reference-info)))
      (when (and (not implicit-reference?)	; unneeded check?
		 explicit-local-name?)
	(phrase-push
	  explicit-local-name?
	  (rlnri-defined-explicit-local-names reference-info)))))
  expr)




;;; The following roles are being ignored when adding local names since they
;;; either can't have local names in normal parses (which increases the
;;; likelyhood that there is a bug handling them) or they can't receive forward
;;; chaining.  This fixes a bug in the change-nth-element action, and makes us
;;; more conservative about throwing this monkey wrench at the compiler.  -jra &
;;; cpm 6/27/95

(defun-simple ignore-role-in-walk-p (simple-role)
  (let ((role-symbol (if (consp simple-role)
			 (car-of-cons simple-role)
			 simple-role)))
    ;; TODO: use a static binary tree instead. --binghe
    (memq-p-macro
      role-symbol
      '(role-server
	name
	named-by-debugging-name
	icon-color
	item-color
	item-x-position
	item-y-position
	icon-heading
	item-width
	item-height
	system-attribute-as-text
	text-of-attribute
	this-workspace
	this-window
	this-rule
	this-procedure
	this-procedure-invocation
	nth-element
	indexed-attribute
	attribute-frame-or-place-reference
	element-frame-or-place-reference
	class-qualified-name-frame-or-place-reference
	class-qualified-method
	next-procedure-method))))



(defun add-local-names-for-current-reference-info (expr)
  (when (and (consp expr)
	     (not (phrase-sequence-p expr))
	     (not (phrase-structure-p expr))
	     (not (truth-value-phrase-p expr))
	     (or (eq (car-of-cons expr) 'the)
		 (eq (car-of-cons expr) 'any)))
    (let* ((current-implicit-local-name
	     (rlnri-implicit-local-name
	       (car current-rule-local-name-reference-info)))
	   (role (second-of-long-enough-list expr))
	   (implicit-local-name (atomic-naming-element-of-role role)))
      (when (and (eq current-implicit-local-name implicit-local-name)
		 (null
		   (get-explicitly-specified-local-name-of-role-if-any role))
		 (not (ignore-role-in-walk-p (simple-role-of-role role)))
		 (invertible-designation-p expr))
	(if (and (eq (car-of-cons expr) 'the)
		 (symbolp role)
		 (null (cdr-of-cons (cdr-of-cons expr))))
	    (setq expr (intern-text-string
			 (tformat-text-string
			   "COMPILER-~A-1"
			   current-implicit-local-name)))
	    (loop for current-name-count
		  from (1+f (cdr current-rule-local-name-reference-info))
		  for new-local-name
		      = (intern-text-string
			  (tformat-text-string
			    "COMPILER-~A-~A"
			    current-implicit-local-name
			    current-name-count))
		  while (loop for name-reference in rule-local-name-references
			      thereis (memq new-local-name
					    (rlnri-defined-explicit-local-names
					      name-reference)))
		  finally
		    (setf (second expr) (phrase-cons role new-local-name))
		    (setf (cdr current-rule-local-name-reference-info)
			  current-name-count))))))
  expr)

(defun maybe-add-more-local-names (original-rule-parse)
  (let ((rule-local-name-references nil)
	(rule-parse original-rule-parse))
    (walk-rule-without-copying rule-parse #'collect-local-name-reference-info)
    (loop with copying-done? = nil
	  for reference-info in rule-local-name-references do
      (when (and (>f (rlnri-defining-expressions-count reference-info) 1)
		 (<f (length (rlnri-defined-explicit-local-names reference-info))
		     (rlnri-defining-expressions-count reference-info))
		 (or (=f (rlnri-implicit-references-count reference-info) 0)
		     (=f (length (rlnri-defined-explicit-local-names
				   reference-info))
			 (1-f (rlnri-defining-expressions-count
				reference-info)))))
	(let ((current-rule-local-name-reference-info
		(phrase-cons reference-info 0)))
	  (setq rule-parse
		(if copying-done?
		    (walk-rule-without-copying
		      rule-parse
		      #'add-local-names-for-current-reference-info)
		    (walk-rule
		      rule-parse
		      #'add-local-names-for-current-reference-info)))
	  (setq copying-done? t))))
    rule-parse))







;;;; Compilation, Installation, Deletion, and Update for Rules



;added by SoftServe

;Declaration: extract-assignments-section-from-for-rule (rule-translation)

;Type: Lisp function

;Purpose: Split the "for" rule on the legacy rule and the assignment section if any

;Arguments: For-rule translation as S-expression

;Return behavior: returns list whose first element is the assignments-section
;or nil in case when it is not present in the rule, and second element is the 
;"for" rule text without the assignment section

;Side effects: None

;Memory impact: None

(defun extract-assignments-section-from-for-rule (rule-translation)
  (let ((assignments-section nil) (rule-text nil) (result nil) (temp nil))
       (loop for rule-element in rule-translation
             do
             ;simplest rule case
             (if (and (listp rule-element) (listp (car rule-element)) (eq (caar rule-element) 'using))
                 (progn (setq assignments-section (car rule-element))
                   (setq rule-text (nconc rule-text (cdr rule-element)))
                   )      
                 (if (and (not (null rule-element)) (listp rule-element))
                       (if (not (eq (car rule-element) 'for))
                           (setq rule-text (nconc rule-text (phrase-list rule-element)))
                           ;complex rule case, handled recursively 
                           (progn   
                             (setq temp (extract-assignments-section-from-for-rule rule-element))
                             (setq assignments-section (first temp))
                             (setq rule-text (nconc rule-text (phrase-list (second temp))))
                             )              
                       )    
                     (setq rule-text (phrase-list rule-element)) ;first FOR keyword
                     )     
                 )    
       )
  (setq result (phrase-list assignments-section rule-text))
  result  
  ))  

;Declaration: extract-assignments-section-if-any (rule-translation)

;Type: Lisp function

;Purpose: split generic rule on the legacy rule and optional assignments section

;Arguments: Rule translation as S-expression

;Users: Rule slot compiler

;Return behavior: returns list of form (assignments-section rt), where 
; assignments-section - assignments-section (or null if there isn't), 
;rt - modified rule without the assignment section. 

;Side effects: None

;Memory impact: None

(defun extract-assignments-section-if-any (rule-translation)
  (let ((assignments-section nil) (rt nil) (result nil) (temp nil))
    (if (listp (car rule-translation))
        ;first we will handle the simplest if, initially and when rules
        (when (eq (caar rule-translation) 'using)
          (setq assignments-section (car rule-translation))
          (setq rt (second rule-translation)))
         ;the next case is the FOR rule
        (when (eq (car rule-translation) 'for)
           (setq temp (extract-assignments-section-from-for-rule rule-translation))
           (setq assignments-section (first temp))
        (setq rt (second temp))))   
  (setq result (phrase-list assignments-section rt))
    result))

;end of changes



;;; Slot-compilers for rule

;;; The slot compilers for rule, focal-classes, focal-objects, and nupec extra
;;; actions are responsible for maintaining a translation (the car of
;;; box-translation-and-text) which is has the form:

;;;  (translation (nil . compilation-without-focal-object) . alist-of-other-compilations)

;;;  where the alist is pairs. Each pair is either
;;;    (role-name . compilation),
;;;    ((role-name . backward-chaining) . compilation), or
;;;    ((role-name . forward-chaining)  . compilation).

;;; This needs to happen only when the slot is edited, not when installed.

;;; There can be only one slot-value-compiler per slot type.  Therefore, the
;;; slot type of box-translation-and-text will be different for each type of
;;; statement.

;;; Individual compilations for particular roles may fail, and these will simply
;;; not be available.  Hopefully, the compiler will adequetly warn for this.
;;; But if the null compilation fails, then the rule will be placed not-in-use.
;;; This can happen when editing the rule text but not focal-classes.

(def-slot-value-compiler rule (translation rule)
  ;changed by SoftServe
  (let ((rule-data (extract-assignments-section-if-any translation)))
    ;;(unless (null (car rule-data))
    ;; (setq translation (second rule-data)))    
  ;end of changes
  
  ;; Make sure that there are not currently scheduled invocations of the
  ;; byte-code-body that we are about to replace.
  #-SymScale
  (when (hash-table-of-rule-instances rule)
    (reclaim-hashed-rule-instance (hash-table-of-rule-instances rule))
    (setf (hash-table-of-rule-instances rule)
	  (make-hashed-rule-instance)))
  #+SymScale
  (let* ((old? (hash-table-of-rule-instances rule))
	 (new (when old? (make-hashed-rule-instance))))
    (when old?
      (if (compare-and-swap (hash-table-of-rule-instances rule) old? new)
	  (reclaim-hashed-rule-instance old?)
	(reclaim-hashed-rule-instance new))))

  ;; NUPEC MODIFICATION:
  ;; If NUPEC-extra-actions slot has a value, part of this list (without 
  ;; the 'and) is copied using phrase-conses and inserted in the rule
  ;; translation parse.  The rule is then compiled as usual with this
  ;; modified parse.
  (when (nupec-authorized-p)
    ;; The action-list in the slot is of the form: 
    ;;  (({(action)}) . text)
    (let ((nupec-extra-actions?
	    (car (nupec-extra-actions rule))))
      (when nupec-extra-actions?
	;; Copy the action-list to phrase conses since it is being added to the
	;; rule parse.  (This is reclaimed when the rule is edited.)
	(let ((nupec-extra-actions-copy
		(copy-for-phrase nupec-extra-actions?))
	      ;; Find the action list in the translation parse.
	      (translation-action-list?
		(loop with rule-translation-list = translation
		      until (null rule-translation-list)
		      do
		  (cond 
		    ((and (consp rule-translation-list)
			  (eq (first rule-translation-list) 'for))
		     (setq rule-translation-list
			   (third rule-translation-list)))
		    (t (return (third rule-translation-list)))))))
	  
	  (when translation-action-list?
	    ;; Modify the translation parse to include the extra actions.
	    (nconc translation-action-list? nupec-extra-actions-copy))))))
  
  ;; An `initial rule' has the word INITIALLY replaced by IF, and the flag
  ;; initial-rule is then set.  This flag is saved in a kb.  If the rule is
  ;; reparsed as non-initial, the compiler resets the flag.
  
  ;; A WHEN or WHENEVER rule must not be forward or backward chained to.  These
  ;; flags are parsed and the slot redisplayed if visible.
  
  (let* ((rule-keyword
	   (rule-translation-keyword translation))
	 (needs-to-be-reactivated? (and (initial-rule-p rule)
					(not (active-p rule))
					(not (runs-while-inactive-p rule)))))
    (setf (rule-keyword rule) rule-keyword)
    (case rule-keyword
      (initially
       (set-initial-rule rule)
       (setq needs-to-be-reactivated? nil)
       (if (eq (second translation) 'for)
	   ;; The initial rule with FOR iteration translates as
	   ;; (INITIALLY FOR ...)
	   (setq translation (cdr translation))
	   (setf (car translation) 'if)))
      ((when whenever)
       (clear-initial-rule rule)
       (clear-invocable-via-backward-chaining rule)
       (clear-invocable-via-forward-chaining rule)
       (update-representations-of-slot-value rule 'frame-flags))
      (otherwise
       (clear-initial-rule rule)))
    
    ;; Some kinds of rules cannot have scan intervals.  If this is one of those
    ;; kinds, clear the scan interval.  Note that the method of setting used
    ;; here bypasses the slot putter.  This is done since the slot putter for
    ;; the scan interval looks at the box translation and text, which is still
    ;; being compiled here.
    
    (when (and (or (eq rule-keyword 'initially)
		   (eq rule-keyword 'whenever))
	       (rule-scan-interval rule))
      (set-slot-value-and-update-representations
	rule 'rule-scan-interval nil))

    ;; There are bugs between the focus compilations and the compilations
    ;; required for forward and backward chaining.  The following code inserts
    ;; extra local names into designations within the rule that could suffer
    ;; from these problems.  This is a workaround to fixing the code in COMPILE1
    ;; through COMPILE3.  -jra 5/30/95
    (setq translation (maybe-add-more-local-names translation))
    
    (let* ((original-compile nil)
	   (*current-computation-frame* rule)
	   (current-computation-component-particulars nil)
	   (focal-classes (focal-classes rule))                   ;added by SoftServe
	   (general-compilation (compile-rule translation nil nil (car rule-data)))
	   (chaining-links
	     (when general-compilation
	       (generate-forward-and-backward-chaining-links rule translation)))
	   (general-compilation-context
	     (second general-compilation))
	   (chaining-roles
	     (loop with collected-roles = nil
		   for (nil . link) in chaining-links
		   for focus-role? =
		     (cond #-chestnut-trans
			   ((forward-chaining-link-p-function link)
			    (forward-link-focus-function link))
			   #+chestnut-trans
			   ((forward-chaining-link-p link)
			    (forward-link-focus link))
			   #-chestnut-trans
			   ((backward-chaining-link-p-function link)
			    (backward-link-focus-function link))
			   #+chestnut-trans
			   ((backward-chaining-link-p link)
			    (backward-link-focus link)))
		   for second-focus-role? =
		     (when #-chestnut-trans (forward-chaining-link-p-function link)
		           #+chestnut-trans (forward-chaining-link-p link)
		       #-chestnut-trans
		       (forward-link-second-focus-function link)
		       #+chestnut-trans
		       (forward-link-second-focus link))
		   do
	       (when (and focus-role?
			  (not (memq focus-role? collected-roles)))
		 (phrase-push focus-role? collected-roles))
	       (when (and second-focus-role?
			  (not (memq second-focus-role? collected-roles)))
		 (phrase-push second-focus-role? collected-roles))
		   finally (return collected-roles)))
	   (focus-compilations nil))
      (change-slot-value rule 'rule-chaining-links chaining-links)
      (when general-compilation
	(loop for name in focal-classes
	      for focus-compilation = (compile-rule
					translation name            ;added by SoftServe
					general-compilation-context (car rule-data))
	      do
	  (if (and (consp focus-compilation)
		   (consp (car-of-cons focus-compilation))
		   (eq (cdr-of-cons (car-of-cons focus-compilation))
		       'universal-compilation))
	      (add-to-frame-note-particulars-list-if-necessary
		name 'focus-class-compilation-failed rule)
	      (setq focus-compilations
		    (nconc focus-compilations focus-compilation))))

	(loop for name in chaining-roles do
	  (setq focus-compilations
		(nconc focus-compilations
		       (compile-rule                                  ;added by SoftServe
			 translation name general-compilation-context (car rule-data)))))
	(setq original-compile
	      (phrase-cons translation
			   (nconc general-compilation focus-compilations))))
      (without-consistency-analysis (rule)
	(cond ((not (bad-status-compiler-frame-notes? rule))
	       (setq original-compile
		     (compile-rule-for-stack rule original-compile)))
	      ;; If errors were detected during compile-rule, call the function
	      ;; which removes errors established by compile-rule-for-stack and
	      ;; remove the byte code body.
	      (t
	       (remove-compiler-error-and-warning-frame-notes)
	       (change-slot-value rule 'rule-byte-code-body nil))))

      (update-frame-status
	rule
	(when (or (get-particulars-of-frame-note-if-any 'compiler-errors rule)
		  (bad-status-compiler-frame-notes? rule))
	  'bad)
	nil)
      (when needs-to-be-reactivated?
	(funcall-method 'activate-if-possible-and-propagate rule))
        original-compile))))
    
    
        



;;; The `NUPEC-Extra-Actions Slot Value Compiler' converts a value of no action,
;;; a single action, and a list of actions to the correct format: ({(action)}).

(def-slot-value-compiler nupec-extra-action-list
			 (nupec-extra-action-list? rule)
  (declare (ignore rule))
  (cond ((null nupec-extra-action-list?)
	 nil)
	((eq nupec-extra-action-list? 'none)
	 nil)
	((eq (car nupec-extra-action-list?) 'and)
	 ;; Remove the 'and in (and action action ...) to become ({(action)})
	 (cdr nupec-extra-action-list?))
	(t
	 ;; Else, is of the form (action), convert to ((action))
	 (phrase-cons nupec-extra-action-list? nil))))




;;; The `NUPEC-Extra-Actions Slot Putter' sets the nupec-extra-actions slot
;;; value, reparses and recompiles the rule translation, and returns the
;;; nupec-extra-actions value.  The rule is reparsed and recompiled so that the extra
;;; actions will be included in the rule compilation.  This is started by
;;; invoking the editor with the current rule text.  The editor invokes the rule
;;; compiler which reparses and recompiles the rule with the extra actions, as
;;; described in the slot-value-compiler for rule translation.

(def-slot-putter nupec-extra-actions
		 (rule nupec-extra-actions initializing?)
  (prog1
      (setf (nupec-extra-actions rule) nupec-extra-actions)
      (when (not initializing?)
	;; When compiling (not loading), recompile even if the previous and new
	;;   action-lists are equal.  (This is how rule editing behaves.)
	;; Call the editor for the rule slot box-translation and text.
	;;   This will cause the rule to be reparsed and recompiled (using the
	;;   NUPEC extra actions).
	(let ((rule-text? (cdr (box-translation-and-text rule))))
	  (when rule-text?
	    (parse-text-for-slot
	      (copy-text rule-text?)
	      rule
	      (get-slot-description-of-frame 'box-translation-and-text rule)))))))




;;; Note that the compiled forms for a rule are kept up to date by the slot
;;; putter.  If a new value is being placed into the slot (i.e.  putting a value
;;; when not initializing) then recompile item gets called on the rule.
  
(def-slot-value-compiler focal-classes (translation)
  ;; The raw translation may be the symbol 'none, a name or a list
  ;; of names beginning with 'and. This must be normalized, and returned as value.
  (let ((compiled-focal-classes
	  (cond ((eq translation 'none) nil)
		((symbolp translation) (phrase-cons translation nil))
		(t (cdr translation)))))
    compiled-focal-classes))

(define-category-evaluator-interface (focal-classes
				       :access read-write)
    (or (no-item)
	(sequence (named unreserved-symbol) 
		  1)) 
  ((set-form (evaluation-value))
   (with-safe-category-setter-calling
       (evaluation-etypecase
	 evaluation-value
	 ((no-item) 'none)
	 ((sequence) 
	  (phrase-cons
	    'and
	    (with-evaluation-sequence-to-phrase-list-mapping
		(evaluation-value rule-category)
	      (call-category-setter-safely 'unreserved-symbol
					   rule-category)))))))
  ((get-form (slot-value))
   (cond
     (slot-value
      (with-list-to-evaluation-sequence-mapping
	  (slot-value rule-category)
	  rule-category))
     (t
      nil))))


;;; The slot putter for `rule-chaining-links' is responsible for installing new
;;; links on chaining properties and removing old links before reclaiming them.

(def-slot-putter rule-chaining-links (rule new-links initializing?)
  (when (and initializing?
	     (not (compilations-up-to-date-p rule))
	     loading-kb-p)
    (reclaim-slot-value new-links)
    (setq new-links nil)
    (note-frame-with-compilation-removed rule))
  (let ((old-links (rule-chaining-links rule)))
    (setf (rule-chaining-links rule) new-links)
    (deinstall-chaining-links old-links)
    (install-chaining-links new-links)
    new-links))




;;; The slot putter for rule-byte-code-body is responsible for installing the
;;; free references that have been listed in the byte code body.

(def-slot-putter rule-byte-code-body (rule new-byte-code-body initializing?)
  (when (and initializing?
	     (not (compilations-up-to-date-p rule))
	     loading-kb-p)
    (reclaim-slot-value new-byte-code-body)
    (setq new-byte-code-body nil)
    (note-frame-with-compilation-removed rule))
  (setf (rule-byte-code-body rule) new-byte-code-body)
  new-byte-code-body)





;;;; Frame flags for rules




(add-grammar-rules
  '((rule-frame-flags (invocable-via-backward-chaining '\,
		       invocable-via-forward-chaining)
     (1 3))

    (rule-frame-flags (invocable-via-backward-chaining '\,
		       invocable-via-forward-chaining '\,
		       may-cause-data-seeking '\,
		       may-cause-forward-chaining)
     (1 3 5 7))

    (rule-frame-flags (invocable-via-backward-chaining '\,
		       invocable-via-forward-chaining '\,
		       may-cause-data-seeking '\,
		       may-cause-forward-chaining '\,
		       cache-explanation-spec)
     (1 3 5 7 9))

    (invocable-via-backward-chaining
      ('invocable 'via 'backward 'chaining) invocable-via-backward-chaining)
    (invocable-via-backward-chaining
     ('not 'invocable 'via 'backward 'chaining)
     not-invocable-via-backward-chaining)

    (invocable-via-forward-chaining
     ('invocable 'via 'forward 'chaining) invocable-via-forward-chaining)
    (invocable-via-forward-chaining
     ('not 'invocable 'via 'forward 'chaining)
     not-invocable-via-forward-chaining)

    (may-cause-data-seeking
     ('may 'cause 'data 'seeking) may-cause-data-seeking)
    (may-cause-data-seeking
     ('may 'not 'cause 'data 'seeking) may-not-cause-data-seeking)

    (may-cause-forward-chaining
     ('may 'cause 'forward 'chaining) may-cause-forward-chaining)
    (may-cause-forward-chaining
     ('may 'not 'cause 'forward 'chaining) may-not-cause-forward-chaining)
    ))




;;; When-or-whenever-rule-p returns nil unless the rule translation exists
;;; and has a body beginning with 'when or 'whenever

(defmacro when-or-whenever-rule-p (rule)
  (let ((keyword (gensym)))
    `(let ((,keyword (rule-keyword ,rule)))
       (or (eq ,keyword 'when)
	   (eq ,keyword 'whenever)))))




(define-category-evaluator-interface (rule-frame-flags
				       :access read-write)
    (structure rule-frame-flags-spec
	       ((backward-chain truth-value)
		(forward-chain truth-value)
		(data-seeking truth-value)
		(cause-forward truth-value)
		(explanation-data truth-value))
	       (and backward-chain forward-chain))
  ((set-form (evaluation-value))
   (with-structure (evaluation-value rule-frame-flags-spec)
     (let ((backward-chaining-phrase
	     (if (evaluation-boolean-is-true-p backward-chain)
		 'invocable-via-backward-chaining
		 'not-invocable-via-backward-chaining))
	   (forward-chaining-phrase 
	     (if (evaluation-boolean-is-true-p forward-chain)
		 'invocable-via-forward-chaining
		 'not-invocable-via-forward-chaining))
	   ;; Grammar allows you to specify only backward-chaining and
	   ;; forward-chaining, which would set remaining slots of
	   ;; rule-frame-flags-spec to nil, so be sure to set to default
	   ;; value if nil.
	   (data-seeking-phrase 
	     (if (evaluation-boolean-is-true-p data-seeking)
		 'may-cause-data-seeking
		 'may-not-cause-data-seeking)) ; default value
	   (cause-forward-phrase 
	     (if (evaluation-boolean-is-true-p cause-forward)
		 'may-cause-forward-chaining
		 'may-not-cause-forward-chaining)) ; default value
	   (explanation-phrase 
	     (when (and (explanation-related-features-enabled-func?)
			(evaluation-boolean-is-true-p explanation-data))
	       'cache-data-for-explanation-flag)))
       (phrase-list backward-chaining-phrase forward-chaining-phrase
		    data-seeking-phrase cause-forward-phrase explanation-phrase))))
  ((get-form (slot-value))
   (when slot-value
     (with-new-structure (rule-frame-flags-spec)
       (setf backward-chain (make-evaluation-boolean-value
			      (invocable-via-backward-chaining-of-flag-vector-p slot-value)))
       (setf forward-chain (make-evaluation-boolean-value
			     (invocable-via-forward-chaining-of-flag-vector-p slot-value)))
       (when (may-cause-data-seeking-of-flag-vector-p slot-value)
	 (setf data-seeking (make-evaluation-boolean-value t)))
       (when (may-cause-forward-chaining-of-flag-vector-p slot-value)
	 (setf cause-forward (make-evaluation-boolean-value t)))
       (when (cache-data-for-explanation-of-flag-vector-p slot-value)
	 (setf explanation-data (make-evaluation-boolean-value t)))))))




;;; Note that in the slot putter for frame flags, when the frame is a rule,
;;; recompile item will be called to propagate the effects of the flags into the
;;; rule compilations.

(def-slot-value-compiler rule-frame-flags (parse-result rule)
  (macrolet ((set-flag (flag) `(setq flags (logiorf flags ,flag)))
	     (clear-flag (flag) `(setq flags (logandc2f flags ,flag))))
    (let ((flags (frame-flags rule)))
      ;; If the rule is WHEN or WHENEVER, then force the first two flags.
      (cond ((when-or-whenever-rule-p rule)
	     (clear-flag invocable-via-backward-chaining-flag)
	     (clear-flag invocable-via-forward-chaining-flag))
	    (t
	     (if (eq (first parse-result) 'invocable-via-backward-chaining)
		 (set-flag invocable-via-backward-chaining-flag)
		 (clear-flag invocable-via-backward-chaining-flag))
	     (if (eq (second parse-result) 'invocable-via-forward-chaining)
		 (set-flag invocable-via-forward-chaining-flag)
		 (clear-flag invocable-via-forward-chaining-flag))))
      
      ;; If the length of the parsed list is 2, then don't modify the status of
      ;; any of the other flags.  This is a compatibility case for an old
      ;; grammar for options of rules.
      (when (cddr parse-result)
	(if (memq 'may-cause-data-seeking parse-result)
	    (set-flag may-cause-data-seeking-flag)
	    (clear-flag may-cause-data-seeking-flag))
	(if (memq 'may-cause-forward-chaining parse-result)
	    (set-flag may-cause-forward-chaining-flag)
	    (clear-flag may-cause-forward-chaining-flag))
	(if (memq 'cache-data-for-explanation-flag parse-result)
	    (set-flag cache-data-for-explanation-flag)
	    (clear-flag cache-data-for-explanation-flag)))
      flags)))

(defun-void clear-cached-explanations (rule)
  (loop for rule-instance
	    being each hash-value of (hash-table-of-rule-instances rule)
	for cached-variables? = (ri-explanation-variables rule-instance)
	do
    ;; Reclaim any cached variables.
    (when cached-variables?
      (reclaim-evaluation-variables-list cached-variables?)
      (setf (ri-explanation-variables rule-instance) 
	    nil))))





(def-slot-value-writer rule-frame-flags (value rule)
  (declare (ignore value))
  
  (twrite-string (if (invocable-via-backward-chaining-p rule)
		     "invocable via backward chaining, "
		     "not invocable via backward chaining, "))

  (twrite-string (if (invocable-via-forward-chaining-p rule)
		     "invocable via forward chaining, "
		     "not invocable via forward chaining, "))

  (twrite-string (if (may-cause-data-seeking-p rule)
		     "may cause data seeking, "
		     "may not cause data seeking, "))

  (twrite-string (if (may-cause-forward-chaining-p rule)
		     "may cause forward chaining"
		     "may not cause forward chaining"))

  (when (or (explanation-related-features-enabled-func?)
	    (cache-data-for-explanation-p rule))
    (twrite-string
      (if (cache-data-for-explanation-p rule)
	  ", cache data for explanation"
	  ", do not cache data for explanation")))
  )

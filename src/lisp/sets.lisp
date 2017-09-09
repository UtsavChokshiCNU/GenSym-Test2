;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module SETS

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Michael Levin




;; This file now has nothing to do with sets. It is a bunch of miscellaneous
;; items related to the inference engine. -ML-, 2 July, 1988x

(declare-forward-reference system-pause function)
(declare-forward-reference system-resume function)

;; In ROLES

(declare-forward-reference type-of-role function)

;; In CELLS

(declare-forward-reference
  initialize-set-of-all-permanent-computation-style function)

;; In PLACES

(declare-forward-reference denote-component-of-block function)

;; In PROC-UTILS

(declare-forward-reference install-procedure-invocation-completion-form-function function)
(declare-forward-reference procedure-invocation-of-code-body-function function)
(declare-forward-reference procedure-definition-of-code-body-function function)
(declare-forward-reference allow-internal-procedure-environment-printing? variable)
(declare-forward-reference get-procedure-methods-of-class function)
(declare-forward-reference find-procedure-invocation-in-module function)
(declare-forward-reference find-calling-procedure-invocation-in-module function)
(declare-forward-reference get-annotation-for-address-if-any function)
(declare-forward-reference get-call-sequence function)


;; in LISTS
(declare-forward-reference g2-list-insert-at-end  function)

(declare-forward-reference g2-list-insert-at-beginning  function)
(declare-forward-reference g2-list-or-array-class-for-element-type function)

;;; in STACK-ACTS

(declare-forward-reference make-transient-item function)

(declare-forward-reference modules-with-unsaved-changes function)

;;; in FILTERS

(declare-forward-reference validate-as-possible-user-mode function)

;;; in CONTROLS

(declare-forward-reference map-to-gensym-window-or-stack-error function)



;;;; System variables for the expression evaluator and rule interpreter



;;; The system variable `stack-expiration' is used to pass around expiration
;;; values.  When an expression needs to return an expiration, instead of
;;; returning, as used to happen, it should be set into this global variable.

(def-system-variable stack-expiration sets nil)

(def-system-variable multiplier-for-turning-off-data-collection sets 5)

(def-system-variable message-completion-interval sets 15)






;;;; Inference Engine Parameters System Table



;;; The 'inference-engine-parameters' is a system table that provides
;;; access, for the user, to in
;;;     recursion-limit
;;;     timeout-for-variables
;;;     timeout-for-wakeups
;;;     retry-interval-after-sensor-timeout
;;;     truth-threshold
;;; Some entries are not user acessible directly.
;;;     falsity-threshold

;;; The sot `set-of-all-computation-styles' is now kept in a kb-specific
;;; variable, rather than in the system tables.  This was determined to
;;; be safer from the point of view of kb saving.  Further documentation
;;; for set-of-all-computation-styles maybe found in the module CELLS.

(def-system-frame inference-engine-parameters sets
  (recursion-limit 50 vector-slot system (type integer))
  (timeout-for-variables 30 vector-slot system (type interval?))
  (timeout-for-wakeups 30 vector-slot system (type interval?))
  (retry-interval-after-sensor-timeout 60 vector-slot system
				       (type interval-for-retry))
;  (use-old-rule-compiler? nil vector-slot system (type yes-or-no?))
  (truth-threshold 800 vector-slot system (type truth-value))
  (falsity-threshold -800 vector-slot system)
;  (set-of-all-computation-styles 
;    (:funcall initialize-set-of-all-permanent-computation-style)
;    vector-slot 
;    save
;    system)
  )

(def-absent-slot-putter set-of-all-computation-styles (inference-engine-parameters value)
  (declare (ignore value)))

(def-absent-slot-putter use-old-rule-compiler? 
			(inference-engine-parameters value)
  (declare (ignore value)))

;; Use-old-rule-compiler? is an obsolete slot.  - agh, 4/19/89


(def-absent-slot-putter truth-threshhold (inference-engine-parameters value)
  (setf (truth-threshold inference-engine-parameters) value)
  (setf (falsity-threshold inference-engine-parameters) (-f value)))


(define-slot-alias use-old-rule-compiler use-old-rule-compiler?)

(define-slot-alias timeout-for-inference-completion timeout-for-wakeups)

;(def-slot-alias truth-threshhold truth-threshold)


(def-slot-putter truth-threshold (inference-engine-parameters-instance value)
  (setq value (absf value))
  (setf (falsity-threshold inference-engine-parameters-instance) (-f value))
  (setf (truth-threshold inference-engine-parameters-instance) value))


(def-absent-slot-putter default-debugging-message-level
			(inference-engine-parameters value)
  (declare (ignore value)))

(def-absent-slot-putter timeout-for-wake-ups (inference-engine-parameters value)
  (change-slot-value inference-engine-parameters 'timeout-for-wakeups value)
  value)

(define-slot-alias retry-interval-after-timeout retry-interval-after-sensor-timeout)




;;; The system variable `recursive-depth' records how many levels of recursion deep
;;; we are in variable formulas and user function invocations.  The value of this
;;; variable will compared with the recursion-limit inference-engine-parameter
;;; whenever entering a formula evaluation or function invocation, and if the
;;; recursive depth is greater than the limit, an error message will be given and
;;; NILs returned.


(def-system-variable recursive-depth sets 0)


(defun truth-threshold-parameter-function ()
  (truth-threshold inference-engine-parameters))


;;; The `interval-for-retry' specifies how often a sensor should probed after it
;;; has failed.


(add-grammar-rules
  `((interval-for-retry interval)
    (interval-for-retry ('do 'not 'retry))))


(def-slot-value-writer interval-for-retry (interval?)
  (if (null interval?)
      (twrite-string "do not retry")
      (print-constant interval? 'seconds)))

(def-slot-value-compiler interval-for-retry (parse-result)
  (cond ((consp parse-result)
	 (cond ((eq (car parse-result) 'do)
		nil)
	       ((numberp (car parse-result))
		(car parse-result))
	       ;; Otherwise don't know what this is, but this shouldn't happen, so
	       ;; just return NIL.
	       (t nil)))
	((numberp parse-result)		; always an integer, <= three-months
	 parse-result)
	;; Again, somethings wrong if we're here, just return NIL.
	(t nil)))





;;;; Stack System Variables




;;; The system variable `current-environment' is used to tell the stack
;;; instructions which environment is being used.  It is bound to one of the
;;; symbols simulator, procedure, or inference-engine.

(def-system-variable current-environment utilities0 nil)




;;; The system variable `cached-top-of-stack' is used to hold the value of the
;;; top-of-stack when this binding is not available.  This value is needed, for
;;; example, when signaling a stack error from a funcalled evaluator or within a
;;; "system-call".  Note that this value is not always cached before an
;;; instruction is being executed.  So far, it is only set in two cases where
;;; the binding of top of stack is not available.  The dispatch to
;;; funcalled-evalutors will set this variable to the current top of stack.  The
;;; dispatch to the system-call will set this variable to the top of stack
;;; decremented by the number of arguments to the system call.  This is because
;;; the system-call is responsible for reclaim its arguments.

(def-system-variable cached-top-of-stack sets nil)




;;; The following variables, along with cached-top-of-stack, are used to cache
;;; the state of the stack evaluator as it returns out of its inner loop to
;;; clear the temporary areas and check if time limits have been exceeded.  They
;;; are also used in the error handling mechanisms.  See stack-eval for their
;;; use.

(def-system-variable cached-stack-program-counter sets 0)

(def-system-variable cached-fixnum-start-time sets 0)

(def-system-variable cached-stack-frame-base sets 0)

(def-system-variable cached-byte-code-body sets nil)

(def-system-variable cached-fixnum-time-limit? sets 0)

;;






;;;; Rule Instance Structure




;;; The following def-structure for rule-instances has been moved here to make
;;; its macros available to all the evaluation controlling files.


(def-structure (rule-instance
		 (:include computation-instance)
		 (:constructor make-rule-instance))
  ri-rule
  ri-body
  ri-context
  (ri-frame-serial-number nil :reclaimer reclaim-frame-serial-number)
  ri-validation-predicate
  ri-final-continuation-task
  ri-priority
  ;; Hurry-and-repeat-priority is used to indicate that the rule instance should
  ;; be given a final execution and then rescheduled. This happens when a rule
  ;; with in-order actions has a non-initial state and another request for
  ;; execution comes along.
  ri-hurry-and-repeat-priority 
  ; what kind of time do we need?

  ;; The purposes slot stores a list of the reasons that this rule instance is
  ;; currently running.  If all items are removed from this list then the
  ;; invocation of this instance should be stopped and the instance reclaimed.
  ri-purposes
  ;; The things-this-rule-instance-is-interested-in slot stores a list of the
  ;; things which this rule instance is interested in seeing run.  These will
  ;; always be variables which have wake-ups set to this rule instance.
  ri-things-this-rule-instance-is-interested-in

  ;; the time when the rule instance is created
  ri-initiation-time

  ;; the state of an in-order rule-instance is 0 if the antecedent has not been
  ;; evaluated, and n (>0) if the nth action is the first one not executed.  The
  ;; state can also be the symbol error or completed when exiting the invocation
  ;; but before it has been reclaimed.
  ri-state

  ;; This slot should be removed and replaced with a focus on a
  ;; window-for-button role when invoking a rule from a button.  This is set
  ;; from a global variable which could get screwed up when the button is hit
  ;; near-simultaneously in two different windows.  -jra 7/13/91
  ri-window-for-rule?

  ;; When a rule is explainable, this slot is used to save the variables
  ;; used in the explanation.  The rule execution called get-current-value for
  ;; these variables.
  ri-explanation-variables
  ri-cached-context-hash-number
  ;; The stack evaluator caches lists of variables whose clean-ups have been
  ;; postponed here.
  ri-postponed-clean-ups
  ;; Stores whether the rule was highlighted on entry.
  ri-highlighted?
  ;; Stores workspace decrementing counts from initially rules.
  ri-rule-workspace?
  ;; Used to implement the completion notification facility.  It is a list of
  ;; two elements - the first is a list of rule-instances.  The second is a
  ;; code-body-invocation to wake up when the car becomes nil {when the last
  ;; rule-instance of the set invoked via the invoke-with-wait instruction is
  ;; dismissed}.  In the future, this may become a structure or list containing
  ;; a hashtable if performance becomes an issue.
  ri-completion-notification-collection?
  
  ;added by SoftServe
  in-lhs-call? ;T when this instance has pending LHS call
  return-value-position-after-lhs-call ;top-of-stack when procedure returns
  ;end of changes
  )

(defun reclaim-evaluation-variables-list (variables)
  (loop for var in variables
	do
    (reclaim-frame-serial-number (cdr var))
    (reclaim-eval-cons var))
  (reclaim-eval-list variables))

(defun copy-variables-list (variables)
  (loop for var in variables
	collect (eval-cons (car var) (copy-frame-serial-number (cdr var))) using eval-cons))

;;; The special variable `current-ri-completion-notification-collection?' is
;;; used to support notification upon completion of rule invocations.  It gets
;;; let-bound during execution of the invoke-with-wait stack-instruction and
;;; used in generate-and-schedule-rule-instances to set up a shared value to be
;;; stored in all rule-instances in their
;;; ri-completion-notification-collection? slot.  See the documentation by that
;;; slot in the rule-instance structure (rules.lisp) for more info.  It should
;;; never have a global value other than nil.

(defvar current-ri-completion-notification-collection? nil)

;;;; Reading and Writing Evaluation Values in KBs

;;; This section would prefer to be in the KB saving and loading modules,
;;; but is here due to macro forward referencing difficulties.


;;; Evaluation values are written to the KB as regular KB elements except in the
;;; case of truth values.  There, they are written as special truth-value
;;; elements, which are not handled by write-element-for-kb directly.
;;; Read-element-for-kb does read all types of evaluation values back as regular
;;; evaluation values.  These conventions are strictly private to the evaluation
;;; value and kb reading and writing modules.  They are subject to change at any
;;; time, although KB forward compatibility must always be preserved.  The
;;; conventions are embodied in the operations below.



;;; `Read-evaluation-value-for-kb' ...

(defun-simple read-evaluation-value-for-kb ()
  (read-element-for-kb nil))



;;; The function `read-truth-value-for-kb' is called after the U character in a
;;; KB, and returns an evaluation truth value.  It read past one KB element,
;;; which must be a fixnum.

;;; The function `read-past-truth-value-for-kb' reads past a truth-value kb
;;; element.

(defun-simple read-truth-value-for-kb ()
  (let ((value (read-element-for-kb nil)))
    (if (not (fixnump value))
	(abort-on-bad-kb)	     
	(make-evaluation-truth-value value))))

(defun-void read-past-truth-value-for-kb (print?)
  (read-past-element-for-kb print?))

;; This element was not present until 4.0, at least not in 3.0 KBs.



;;; `Write-evaluation-value-for-kb' ...

(defun-void write-evaluation-value-for-kb (evaluation-value)
  (if (evaluation-truth-value-p evaluation-value)
      (write-truth-value-for-kb evaluation-value)
      ;; This function knows that the evaluation value the equivalent slot value
      ;; are represented the same way.  If this changes, this function would
      ;; have to be rewritten.  Note that managed floats are handled by
      ;; write-element-for-kb.
      (write-element-for-kb evaluation-value)))


;;; The function `write-evaluation-truth-value' writes evaluation-truth-value, a
;;; truth value, or, more properly, an evaluation value that's a truth value, to
;;; the current KB.

(defun-void write-truth-value-for-kb (evaluation-truth-value)
  (write-char-for-kb #\U)
  (write-element-for-kb (evaluation-truth-value-value evaluation-truth-value)))




;;;; Continuation of Evaluation Value Stuff From module TYPES


(declare-side-effect-free-function evaluation-value-of-type-p) ; But it's not - JED

(defun-simple evaluation-value-of-type-p (evaluation-value type)
  #+development
  (assert (type-specification-subtype-p type 'evaluation-value)
	  (type)
	  "~a should have been a subtype of evaluation-value"
	  type)
  (case type
    ((integer)
     (evaluation-integer-p evaluation-value))
    ((long)
     (evaluation-long-p evaluation-value))    
    ((float)
     (evaluation-float-p evaluation-value))
    ((number)
     (evaluation-quantity-p evaluation-value))
    ((symbol)
     (evaluation-symbol-p evaluation-value))
    ((text)
     (evaluation-text-p evaluation-value))
    ((boolean)
     (evaluation-boolean-p evaluation-value))
    ((truth-value)
     (evaluation-truth-value-p evaluation-value))
    ((datum)
     (evaluation-datum-p evaluation-value))
    (t
     (or (and (iteration-state-type-specification-p type)
	      (evaluation-iteration-state-p evaluation-value))
	 (and (symbolp type)
	      (number-subtype-p type)
	      (evaluation-quantity-p evaluation-value))
	 (and (consp type)
	      (defined-evaluation-value-type-p (car-of-cons type))
	      (consp evaluation-value)
	      (eq (car-of-cons type)
		  (cdr-of-cons evaluation-value)))))))





(defun-simple write-evaluation-value-to-text-string (evaluation-value)
  (twith-output-to-text-string (write-evaluation-value evaluation-value)))

#+development
(defun-simple write-evaluation-value-to-gensym-string (evaluation-value)
  (twith-output-to-gensym-string (write-evaluation-value evaluation-value)))

(def-evaluation-value-writer obsolete-datum
  (write-evaluation-value (evaluation-obsolete-datum-value obsolete-datum))
  (twrite-char #.%\*))






;;;; Continuation of Type Stuff From module TYPES




;;; See module TYPES for some useful documentation.  The low-level data
;;; structures of the type-specification were moved into a more early and
;;; independent module in the hope of eventual, greater modularity.  JED 1/21/96





;;; The function `make-type-specification-union' takes two type specifications
;;; and returns a type which is the union of the given types.  The returned type
;;; is therefor a superior type of all argument types and any thing which is an
;;; instance of any of the argument types is an instance of the generated type.
;;; This is an OR.

;;; The macro `make-type-specification-intersection' takes a set of type
;;; specifications and returns a type specification which is the intersection of
;;; the given types.  This means that for a thing to be a member of the
;;; generated type, it must be a member of all of the types which are arguments
;;; to this function.  This is an AND.

;;; The function `make-type-specificaton-negation' takes a type specification and
;;; returns a type specification which excludes all things in the argument type
;;; specification.  This is a NOT.

;;; The function `make-type-specification-filtered' takes a a symbol naming a
;;; predicate function of one argument and returns a type specification which
;;; includes all things for which the function returns non-nil, and excludes all
;;; things which return NIL.  This is similar to the SATISFIES specifier in
;;; Common Lisp type systems.

(defun-simple make-type-specification-union (type1 type2)
  (cond ((type-specification-subtype-p type1 type2)
	 type2)
	((type-specification-subtype-p type2 type1)
	 type1)
	(t
	 (let ((collected-types nil))
	   (if (union-type-specification-p type1)
	       (loop for union-type in (cdr type1) do
		 (setq collected-types
		       (possibly-add-type-to-union-list
			 union-type collected-types)))
	       (setq collected-types
		     (possibly-add-type-to-union-list
		       type1 collected-types)))
	   (if (union-type-specification-p type2)
	       (loop for union-type in (cdr type2) do
		 (setq collected-types
		       (possibly-add-type-to-union-list
			 union-type collected-types)))
	       (setq collected-types
		     (possibly-add-type-to-union-list
		       type2 collected-types)))
	   (phrase-cons 'or collected-types)))))

(defun-simple possibly-add-type-to-union-list (type-to-add union-list)
  (loop for type-cons on union-list
	for type = (car-of-cons type-cons)
	do
    (cond ((type-specification-subtype-p type-to-add type)
	   (return union-list))
	  ((type-specification-subtype-p type type-to-add)
	   (setf (car-of-cons type-cons) type-to-add)
	   (return union-list)))
	finally
	  (return (nconc union-list (phrase-list type-to-add)))))

(defun-simple make-type-specification-intersection (type1 type2)
  (let ((unknown-allowed?
	  (and (type-specification-subtype-p '(unknown-datum) type1)
	       (type-specification-subtype-p '(unknown-datum) type2)))
	(no-item-allowed?
	  (and (type-specification-subtype-p '(no-item) type1)
	       (type-specification-subtype-p '(no-item) type2)))
	(no-item-implies-unknown-allowed?
	  (and (type-specification-subtype-p '(no-item-implies-unknown) type1)
	       (type-specification-subtype-p '(no-item-implies-unknown) type2)))
	(primary-type1 (primary-type-of-type-specification type1))
	(primary-type2 (primary-type-of-type-specification type2)))
    (maybe-add-no-item-implies-unknown
      (maybe-add-no-item
	(maybe-add-unknown
	  (cond ((type-specification-subtype-p primary-type1 primary-type2)
		 primary-type1)
		((type-specification-subtype-p primary-type2 primary-type1)
		 primary-type2)
		(t
		 (phrase-list 'and primary-type1 primary-type2)))
	  unknown-allowed?)
	no-item-allowed?)
      no-item-implies-unknown-allowed?)))

(declare-side-effect-free-function make-type-specification-negation)

(defun-simple make-type-specification-negation (type-specification)
  (phrase-list 'not type-specification))

(declare-side-effect-free-function make-type-specification-filtered)

(defun-simple make-type-specification-filtered (function-name-symbol)
  (phrase-list 'satisfies function-name-symbol))




;;; The function `type-specification-for-user-type' takes a symbol and returns
;;; the type-specification that corresponds to the user visible type for that
;;; name.  For example, quantity is transformed to number.  If no type
;;; specification exists for that symbol, then NIL is returned.  Note that this
;;; function does not treat class names specially; they will all return NIL.

(defun-simple type-specification-for-user-type (symbol)
  (case symbol
    ((quantity) 'number)
    ((value) 'datum)
    ((item-or-value) 'item-or-datum)
    ((sequence) '(sequence))
    ;; Grandfather in the transform from struct to structure.  FIND ME, JRA!
    ;; -jra 8/8/96
    ((struct structure) '(structure))
    (otherwise
     (if (and (not (eq symbol 'datum))
	      (valid-datum-type-specification-p symbol))
	 symbol
	 nil))))

;;; `user-type-for-type-specification' translates from type-specifications
;;; to user type symbols. It does NOT guarantee that it can make a user
;;; type for any type-specification; cetain type-specifications are outside
;;; the users' model.  It has undefined results if misfed.

(defun-simple user-type-for-type-specification (type-specification)
  (cond
    ((symbolic-type-specification-p type-specification)
     (case type-specification
       (number 'quantity)
       (float 'float)
       (integer 'integer)
       (long 'long)
       (item-or-datum 'item-or-value)
       (datum 'value)
       (symbol 'symbol)
       (text 'text)
       (truth-value 'truth-value)))
    ((class-type-specification-p type-specification)
     (type-specification-class type-specification))
    ((aggregate-value-type-specification-p type-specification)
     (car-of-cons type-specification))
    (t
     'item-or-value)))


;;; The function `type-specification-for-user-or-datum-type' is similar to
;;; type-specification-for-user-type, in that can take a symbol and can return
;;; the type-specification that corresponds to the user visible type for that
;;; name.  It differs in that this function also tests for and returns the
;;; internal item-or-datum and datum type specifications.

;;; This function is used, for example, when testing if a symbol should be
;;; allowed as the name of a user-defined class.  For example, item-or-value,
;;; item-or-datum, value, datum, etc. are not allowed.

;;; If the type specification for that symbol does not exist or it is a class
;;; name for that symbol, then NIL is returned.

(defun-simple type-specification-for-user-or-datum-type (symbol-or-type-spec)
  (cond ((symbolp symbol-or-type-spec)
	 (case symbol-or-type-spec
	   ((quantity) 'number)
	   ((value) 'datum)
	   ((item-or-value) 'item-or-datum)
	   ((item-or-datum) 'item-or-datum)
	   ((sequence) '(sequence))
	   ((struct structure) '(structure))
	   (otherwise
	    (if (valid-datum-type-specification-p symbol-or-type-spec)
		symbol-or-type-spec
		nil))))
	((valid-type-specification-p symbol-or-type-spec)
	 symbol-or-type-spec)
	(t nil)))




;;; The function `print-user-or-datum-type' takes an argument similar to what is
;;; given to the function above twrites a suitable presentation of it for user
;;; viewing.

(defun-void print-user-or-datum-type (symbol-or-type-spec)
  (let ((type-spec?
	  (type-specification-for-user-or-datum-type symbol-or-type-spec)))
    (cond (type-spec?
	   (write-type-specification type-spec?))
	  ((symbolp symbol-or-type-spec)
	   (twrite-symbol symbol-or-type-spec))
	  (t
	   ;; This shouldn't happen, but just print it.
	   (twrite symbol-or-type-spec)))))




;;; The function `maybe-add-unknown' takes a type and a flag indicating if the
;;; type unknown-datum should be unioned with the given type.  If the flag is
;;; NIL, the original type is returned.

(declare-side-effect-free-function maybe-add-unknown)

(defun-simple maybe-add-unknown (type add-unknown-datum?)
  (if add-unknown-datum?
      (make-type-specification-union type '(unknown-datum))
      type))




;;; The function `maybe-add-no-item' takes a type and a flag indicating if the
;;; type no-item should be unioned with the given type.  The resulting type,
;;; unioned or not, is returned.

(declare-side-effect-free-function maybe-add-no-item)

(defun-simple maybe-add-no-item (type add-no-item?)
  (if add-no-item?
      (make-type-specification-union type '(no-item))
      type))




;;; The function `maybe-add-no-item-implies-unknown' takes a type and a flag
;;; indicating if the type no-item should be unioned with the given type.  The
;;; resulting type, unioned or not, is returned.

(declare-side-effect-free-function maybe-add-no-item-implies-unknown)

(defun-simple maybe-add-no-item-implies-unknown (type add-no-item-implies-unknown?)
  (if add-no-item-implies-unknown?
      (make-type-specification-union type '(no-item-implies-unknown))
      type))




(declare-side-effect-free-function difference-type-specification-p)

(defun-simple difference-type-specification-p (type-specification)
  (and (consp type-specification)
       (eq (car-of-cons type-specification) 'and)
       (valid-type-specification-list-p (cdr-of-cons type-specification))
       (=f (length type-specification) 3)
       (negation-type-specification-p
	 (third-of-long-enough-list type-specification))
       (type-specification-subtype-p
	 (second-of-long-enough-list (third-of-long-enough-list type-specification))
	 (second-of-long-enough-list type-specification))))


;;; The function `type-specification-union-minus-type' takes a type
;;; specification union and a type to be removed from the union, and returns a
;;; type which is the first type, minus the second.  Note that this function
;;; requires that the type be a union type, and that the given second type be a
;;; subtype of the first type.

(defun-simple type-specification-union-minus-type (union type-to-remove)
  #+development
  (assert (and (union-type-specification-p union)
	       (type-specification-subtype-p type-to-remove union))
	  (union type-to-remove)
	  "Bad arguments to Union-minus-type.")
  (if (=f (length union) 3)
      (if (type-specification-subtype-p (third union) type-to-remove)
	  (second union)
	  (if (type-specification-subtype-p (second union) type-to-remove)
	      (third union)
	      (progn
		#+development
		(cerror "Continue" "Confusing error #1 in union-minus-type.")
		union)))
      (loop for type in (cdr union)
	    unless (type-specification-subtype-p type type-to-remove)
	      collect type into result-types using phrase-cons
	    finally
	      (cond ((null result-types)
		     #+development
		     (cerror "Continue"
			     "Confusing error #2 in union-minus-type.")
		     (return nil))
		    ((null (cdr result-types))
		     (return (car result-types)))
		    (t
		     (return (phrase-cons 'or result-types)))))))




;;; The function `type-specification-minus-type' takes a type and another type
;;; to possibly remove, and returns the first type minus the second type, if the
;;; second type was a subtype of the first at all.

(defun-simple type-specification-minus-type (type type-to-remove)
  (if (and (union-type-specification-p type)
	   (type-specification-subtype-p type-to-remove type))
      (type-specification-union-minus-type type type-to-remove)
      type))




;;; The function `primary-type-of-type-specification' takes a type specification
;;; and removes the types unknown-datum and no-item if they are included.

(defun-simple primary-type-of-type-specification (type-specification)
  (type-specification-minus-type
    (type-specification-minus-type
      (type-specification-minus-type
	type-specification
	'(no-item-implies-unknown))
      '(no-item))
    '(unknown-datum)))




;;; The function `add-secondary-type-specifications' takes a type to be added to
;;; and a type to copy.  This function will add those "secondary" types found
;;; in the second argument into the type given as the first argument.  The
;;; secondary types are unknown-datum, no-item, and no-item-implies-unknown.

(defun-simple add-secondary-type-specifications (to-type from-type)
  (maybe-add-no-item-implies-unknown
    (maybe-add-no-item
      (maybe-add-unknown
	to-type
	(type-specification-subtype-p '(unknown-datum) from-type))
      (type-specification-subtype-p '(no-item) from-type))
    (type-specification-subtype-p '(no-item-implies-unknown) from-type)))




;;; Aggregate Value / Part Component Type Predicates
;;;
;;; See the module TYPES for details.  There is macro there that can generate
;;; the kb and non-kb versions of all of the type predicate comparisons


(defun-simple sequence-type-specification-subtype-p (type superior-type)
  (make-sequence-subtype-predicate type superior-type nil))


(defun-simple sequence-type-specifications-could-intersect-p (type superior-type)
  (make-sequence-type-intersection-predicate type superior-type nil))

(defun-simple sequence-type-specification-not-subtype-p (type superior-type)
  (make-sequence-not-subtype-predicate type superior-type nil))

(defun-simple structure-type-specification-subtype-p (type superior-type)
  (make-structure-subtype-predicate type superior-type nil))

(defun-simple structure-type-specifications-could-intersect-p (type superior-type)
  (make-structure-type-intersection-predicate type superior-type nil))

(defun-simple structure-type-specification-not-subtype-p (type superior-type)
  (make-structure-not-subtype-predicate type superior-type nil))




;;; The function `type-specification-subtype-p' takes two type specifications
;;; and returns true when the first is always a proper subtype of the second.
;;; In the case where classes mentioned in the type specification are not system
;;; defined classes, this may not be determinable, and this function will then
;;; return NIL.  See the predicate type-specification-subtype-in-kb-p to cope
;;; with user defined classes.  This predicate can be used to determine if type
;;; checking code needs to be emitted when the second type argument is a
;;; required value and the first type argument is the returned value of an
;;; argument.

;; Note that I've had trouble implementing the general case of this operation.
;; I know that it will work if the only kind of compound in the first type is
;; intersection (AND) and the only kind of combination used in the second
;; argument is union (OR).  The following paragraphs describe what I have been
;; able to determine.  -jra 3/24/91

;; I now think I've got it.  The trick is to make the outermost clause of this
;; function an or of the simple decomposition rules for the the combined types
;; of both the superior and inferior.  In some cases, decomposing the superior
;; is the only way to make it work, and in some cases it is decomposing the
;; inferior which is the only way.  This is not predictible beforehand, and so
;; each decomposition which is possible must be tried.  -jra 4/20/91

;; Note that this a classicly difficult problem.  Common Lisp has recognized
;; this in that the function subtypep returns a second value which reflects the
;; "certainty" with which a subtype determination was made (CLtL, second
;; edition, pp. 97-99).  In Common Lisp, subtypep is allowed to "give up" when
;; one of the types contains AND, OR, NOT, SATISFIES, or (a qualifier which we
;; don't use) MEMBER.  We have the same problems with these qualifiers that
;; combine type definitions.

;; We also have the additional problem of user-defined (and therefore mutable)
;; class definitions.  Currently, compilations are not allowed to emit anything
;; which would have to be recompiled on a change to some user-defined entity,
;; other than the compiled thing itself.  This means that in compilations, we
;; cannot depend on user-defined classes keeping the same superior class, or
;; even being defined.  This predicate is built with these considerations in
;; mind, in that it will not depend on any characteristics of classes which are
;; not system-defined, with two exceptions.  If the superior-type is class item,
;; then any subtype which describes a class is a subtype.  Also, if the two
;; classes are EQ, then the class types are necessarily subtypes of each other.

;; For the purposes of this discussion, simple type specifications are those
;; which are not constructed with any of the combined type specifications.  With
;; simple type specifications that are symbols or system-defined (i.e.  G2
;; built-in) classes, one can always conclusively tell whether one type is a
;; subtype of another type.  We can also conclusively determine subtype in the
;; special case where the superior type is the class item, in that all classes
;; are subclasses of item.

;; There is one trivial test, which is if the two types are EQUAL, then one is
;; certainly the subtype of the other.

;; There are decidable special cases for some of the combined types.  When a
;; superior type is a union (OR), then the other type is a subtype of the
;; superior if the other type is a subtype of any of the types in the superior's
;; union.  When a superior type is an interestion (AND), then the other type is
;; a subtype of the superior if the other type is a subtype of all of the types
;; in the superior's intersection.

;; There are other decidable special cases when the superior type is known to
;; not be a combined type (union or intersection).  When the superior is a
;; simple type and when the possible subtype is an intersection, then it is a
;; subtype when any of the intersection types are a subtype of the superior
;; type.  Also, when the superior is simple, and the possible subtype is a
;; union, then it is a subtype only when all union types are subtypes of the
;; superior.

;; Combined types can also be subtypes when the superior and possible subtype
;; use the same kind of combination, and all the combined types of the possible
;; subtype are subtypes of the corresponding combined type of the superior.
;; This is a trivial case of this comparison, though somewhat difficult to
;; compute efficiently, unless there is a canonical form and ordering of
;; combined types.  Since I don't believe we are currently using any such cases,
;; I'll leave these problems unresolved for now.  Those who need such features
;; in the future are left to extend it.

(declare-side-effect-free-function type-specification-subtype-p)

(defun-simple type-specification-subtype-p (type superior-type)
  #+development
  (assert (and (valid-type-specification-p type)
	       (valid-type-specification-p superior-type))
	  (type superior-type)
	  "Invalid type-specification argument.")
  (if (and (equal type '(obsolete-datum)) (equal superior-type '(or truth-value (unknown-datum)))) nil
   (or (equal type superior-type)
       (cond ((union-type-specification-p type)
	     (loop for subtype in (cdr type)
		   always (type-specification-subtype-p subtype superior-type)))
	    ((difference-type-specification-p type)
	     (type-specification-subtype-p
	       (second-of-long-enough-list type)
	       superior-type))
	    ((intersection-type-specification-p type)
	     (loop for intersection-type in (cdr type)
		   thereis (type-specification-subtype-p
			     intersection-type superior-type)))
	    ((negation-type-specification-p type)
	     (and (negation-type-specification-p superior-type)
		  (type-specification-subtype-p
		    (second superior-type) (second type)))))
      (cond ((symbolp superior-type)
	     (or (and (symbolp type)
		      (symbolic-type-specification-subtype-p
			type superior-type))
		 (and (member-type-specification-p type)
		      (member-type-specification-subtype-of-symbolic-type-p
			type superior-type))
		 (and (eq superior-type 'item-or-datum)
		      (or (class-type-specification-p type)
			  (aggregate-value-type-specification-p type)))
		 (and (eq superior-type 'datum)
		      (aggregate-value-type-specification-p type))
		 (and (eq superior-type 'evaluation-value)
		      (consp type)
		      (evaluation-value-type-specification-p type))))
	    ((aggregate-value-type-specification-p superior-type)
	     ;; only other aggregate value types can be sub types of
	     ;; an aggregate value type
	     (and (aggregate-value-type-specification-p type)
		  (or (and (fast-structure-type-specification-p type)
			   (fast-structure-type-specification-p superior-type)
			   (structure-type-specification-subtype-p
			     type superior-type))
		      (and (fast-sequence-type-specification-p type)
			   (fast-sequence-type-specification-p superior-type)
			   (sequence-type-specification-subtype-p
			     type superior-type)))))
	    ((member-type-specification-p superior-type)
	     ;; a member type spec. can only be a superior of other member types,
	     ;; or, eventually certain integer ranges.
	     (and (member-type-specification-p type)
		  (member-type-specification-subtype-p
		    type superior-type)))
	    ((class-type-specification-p superior-type)
	     (let ((superior-class (type-specification-class superior-type)))
	       (and (class-type-specification-p type)
		    (let ((class (type-specification-class type)))
		      (or (eq superior-class 'item)
			  (eq superior-class class)
			  (cond
			    ((and (system-defined-class-p superior-class)
				  (system-defined-class-p class))
			     (not (null (subclassp class superior-class))))
			    ((and (dependent-compilation-p)
				  (stable-class-p superior-class)
				  (stable-class-p class))
			     (cond ((subclassp class superior-class)
				    (record-free-reference
				      'stable-subclass
				      (phrase-cons superior-class class))
				    t)
				   (t
				    (record-free-reference
				      'stable-not-subclass
				      (phrase-cons superior-class class))
				    nil)))
			    (t nil)))))))
	    ((union-type-specification-p superior-type)
	     (loop for union-type in (cdr superior-type)
		   thereis (type-specification-subtype-p type union-type)))
	    ((intersection-type-specification-p superior-type)
	     (loop for intersection-type in (cdr superior-type)
		   always (type-specification-subtype-p
			    type intersection-type)))
	    ((negation-type-specification-p superior-type)
	     (not (type-specifications-could-intersect-p
		    type (second superior-type)))))
      ;; The filtered case is covered by the equal above.  -jra 4/19/91
;      (and (or (filtered-type-specification-p superior-type)
;	       (filtered-type-specification-p type))
;	   (equal type superior-type))
      ;; The iteration state case is covered by the equal above.  -jra 4/19/91
;      (and (or (iteration-state-type-specification-p type)
;	       (iteration-state-type-specification-p superior-type))
;	   (and (iteration-state-type-specification-p type)
;		(iteration-state-type-specification-p superior-type)))
      )))








;;; The function `type-specification-not-subtype-p' takes a type and a possible
;;; superior type and returns true only when it can prove that the inferior type
;;; is NOT a subtype of the possible superior type.

(declare-side-effect-free-function type-specification-not-subtype-p)

(defun-simple type-specification-not-subtype-p (type superior-type)
  #+development
  (assert (and (valid-type-specification-p type)
	       (valid-type-specification-p superior-type))
	  (type superior-type)
	  "Invalid type-specification argument.")
  (and (not (equal type superior-type))
       (or (cond ((intersection-type-specification-p superior-type)
		  (loop for intersection-type in (cdr superior-type)
			thereis (type-specification-not-subtype-p
				  type intersection-type)))
		 ((union-type-specification-p superior-type)
		  (loop for subtype in (cdr superior-type)
			always (type-specification-not-subtype-p type subtype)))
		 ((negation-type-specification-p superior-type)
		  ;; This should be the following.  -jra 12/16/93
		  ;; (type-specifications-intersect-p type (second superior-type))
		  (or (type-specification-subtype-p
			type (second superior-type))
		      (type-specification-subtype-p
			(second superior-type) type))))
	   (cond ((difference-type-specification-p type)
		  (type-specification-not-subtype-p
		    (second-of-long-enough-list type) superior-type))
		 ((intersection-type-specification-p type)
		  (loop for intersection-type in (cdr type)
			thereis (type-specification-not-subtype-p
				  intersection-type superior-type)))
		 ((union-type-specification-p type)
		  (loop for subtype in (cdr type)
			always (type-specification-not-subtype-p
				 subtype superior-type)))
		 ((negation-type-specification-p type)
		  (or (type-specification-subtype-p
			(second type) superior-type)
		      (type-specification-subtype-p
			superior-type (second type)))))
	   ;; Filtered types cannot be proven to be disjoint, since the
	   ;; predicate function can accept or reject values arbitrarily.  Also,
	   ;; the following not-subtype-p predicates depend on the subtypes
	   ;; being simple types.
	   (cond ((or (filtered-type-specification-p superior-type)
		      (filtered-type-specification-p type)
		      (intersection-type-specification-p type)
		      (union-type-specification-p type)
		      (negation-type-specification-p type))
		  nil)
		 ((symbolp superior-type)
		  (cond
		    ((symbolp type)
		     (not (symbolic-type-specification-subtype-p
			    type superior-type)))
		    ((aggregate-value-type-specification-p type)
		     (not (or (eq superior-type 'datum)
			      (eq superior-type 'item-or-datum)
			      (eq superior-type 'evaluation-value))))
		    ((member-type-specification-p type)
		     (member-type-specification-not-subtype-of-symbolic-type-p
		       type superior-type))
		    (t
		     (or (not (class-type-specification-p type))
			 (if (eq superior-type 'evaluation-value)
			     (not (type-specification-subtype-p
				    type superior-type))
			     (not (eq superior-type 'item-or-datum)))))))
		 ((member-type-specification-p superior-type)
		  (cond ((member-type-specification-p type)
			 (member-type-specification-not-subtype-p
			   type superior-type))
			(t
			 ;; if type is not another member
			 ;; it may be a subtype if it is a subrange contained
			 ;; by the list of members, but this is not yet implemented
			 t)))
		 ((aggregate-value-type-specification-p superior-type)
		  (cond
		    ((aggregate-value-type-specification-p type)
		     (cond
		       ((and (fast-structure-type-specification-p type)
			     (fast-structure-type-specification-p superior-type))
			(structure-type-specification-not-subtype-p
			  type superior-type))
		       ((and (fast-sequence-type-specification-p type)
			     (fast-sequence-type-specification-p superior-type))
			(sequence-type-specification-not-subtype-p
			  type superior-type))
		       (t
			t)))
		    (t
		     t)))
;		 ((symbolp superior-type)
;		  (if (symbolp type)
;		      (not (symbolic-type-specification-subtype-p
;			     type superior-type))
;		      (or (progn
;			    (when (aggregate-value-type-specification-p type)
;			      (error "unhandled not subtype - JRA"))
;			    nil)
;			  (not (class-type-specification-p type))
;			  (if (eq superior-type 'evaluation-value)
;			      (not (type-specification-subtype-p
;				     type superior-type))
;			      (not (eq superior-type 'item-or-datum))))))
		 ;; For evaluation-value, unknown, or no item superior types,
		 ;; not-subtype-p is true if the subtype is not a combined type
		 ;; and it is also not a subtype of the superior type.
		 ((or (evaluation-value-type-specification-p superior-type)
		      (unknown-type-specification-p superior-type)
		      (no-item-type-specification-p superior-type)
		      (no-item-implies-unknown-type-specification-p superior-type))
		  (not (type-specification-subtype-p type superior-type)))
		 ((class-type-specification-p superior-type)
		  ;; Note that a class type can only be a superior type of
		  ;; class types.  -jra & cpm 4/17/91
		  (or (not (class-type-specification-p type))
		      (class-type-specification-not-subtype-p
			(type-specification-class type)
			(type-specification-class superior-type))))))))

(defun-simple class-type-specification-not-subtype-p (inferior-class superior-class)
  (cond
    ((eq inferior-class superior-class)
     nil)
    ((and (system-defined-class-p superior-class)
	  (system-defined-class-p inferior-class))
     (not (subclassp inferior-class superior-class)))
    ((or (not (dependent-compilation-p))
	 (not (stable-class-p superior-class))
	 (not (stable-class-p inferior-class)))
     nil)
    ((subclassp inferior-class superior-class)
     (record-free-reference
       'stable-subclass
       (phrase-cons superior-class inferior-class))
     nil)
    (t
     (record-free-reference
       'stable-not-subclass
       (phrase-cons superior-class inferior-class))
     t)))




;;; The function `type-specifications-could-intersect-p' takes a type and a
;;; superior-type with possibly intersecting subparts.  This function
;;; will return t if the first type is a subtype, or is of a type which
;;; could intersect with the superior-type.

;;; This function is used to determine if a the type returned by a subexpression
;;; could possibly return a value which is suitable to a operation.  So, if
;;; there is a possibility that an instance of the subtype could meet the type
;;; specification given as the superior type, this operation will return t.

;;; The gist of the difference between this function and type-specification-
;;; subtype-p is that subtype-p returns true only when it can prove that the one
;;; type is a subtype of the other, and this function returns false only when it
;;; can prove that each type is neither a subtype of the other, nor do the
;;; subtypes of the given types overlap in any way.

(declare-side-effect-free-function type-specifications-could-intersect-p)

(defun-simple type-specifications-could-intersect-p (type superior-type)
  (or ;(not (type-specification-not-subtype-p superior-type type))
      ;(not (type-specification-not-subtype-p type superior-type))
      (type-specifications-could-intersect-p-1 type superior-type)))

(defun-simple type-specifications-could-intersect-p-1 (type superior-type)
  #+development
  (unless (and (valid-type-specification-p type)
	       (valid-type-specification-p superior-type))
    (cerror "Return NIL"
	    "Bad types: ~a ~a" type superior-type)
    (return-from type-specifications-could-intersect-p-1 nil))
  (or (equal type superior-type)
      (if (atom superior-type)
	  (or (and (symbolp type)
		   (or (symbolic-type-specification-subtype-p
			 type superior-type)
		       (symbolic-type-specification-subtype-p
			 superior-type type)))
	      (and (eq superior-type 'item-or-datum)
		   (or (class-type-specification-p type)
		       (aggregate-value-type-specification-p type)))
	      (and (eq superior-type 'datum)
		   (aggregate-value-type-specification-p type))
	      (and (eq superior-type 'evaluation-value)
		   (consp type)
		   (evaluation-value-type-specification-p type)))
	  (case (car superior-type)
	    (or
	     (loop for subtype in (cdr-of-cons superior-type)
		   thereis (type-specifications-could-intersect-p-1 type subtype)))
	    (and
	     (loop for subtype in (cdr-of-cons superior-type)
		   always (type-specifications-could-intersect-p-1 type subtype)))
	    (not
	     (not (type-specification-subtype-p
		    type (second-of-long-enough-list superior-type))))
	    (class
	     (and (class-type-specification-p type)
		  (class-type-specifications-could-intersect-p superior-type type)))
	    ((sequence structure)
	     (or (eq type 'datum)
		 (eq type 'item-or-datum)
		 (eq type 'evaluation-value)
		 (and (fast-structure-type-specification-p type)
		      (fast-structure-type-specification-p superior-type)
		      (structure-type-specifications-could-intersect-p
			type superior-type))
		 (and (fast-sequence-type-specification-p type)
		      (fast-sequence-type-specification-p superior-type)
		      (sequence-type-specifications-could-intersect-p
			type superior-type))))
	    (member
	     (or (eq type 'item-or-datum)
		 (eq type 'evaluation-value)
		 (eq type 'datum)
		 (and (member-type-specification-p type)
		      (member-type-specifications-could-intersect-p
			superior-type type))
		 (and (type-specification-subtype-in-kb-p type 'datum)
		      (member-type-specification-intersects-datum-type-p
			superior-type type))))))
      (if (atom type)
	  (or (and (eq type 'item-or-datum)
		   (class-type-specification-p superior-type))
	      (and (eq type 'evaluation-value)
		   (consp superior-type)
		   (evaluation-value-type-specification-p superior-type)))
	  (case (car-of-cons type)
	    (or
	     (loop for subtype in (cdr-of-cons type)
		   thereis (type-specifications-could-intersect-p-1
			     subtype superior-type)))
	    (and
	     (loop for subtype in (cdr-of-cons type)
		   always (type-specifications-could-intersect-p-1
			    subtype superior-type)))
	    (not
	     (not (type-specification-subtype-p
		    superior-type (second-of-long-enough-list type))))
	    (member
	     (or (eq superior-type 'item-or-datum)
		 (eq superior-type 'evaluation-value)
		 (eq superior-type 'datum)
		 (and (member-type-specification-p superior-type)
		      (member-type-specifications-could-intersect-p
			superior-type type))
		 (and (type-specification-subtype-in-kb-p type 'datum)
		      (member-type-specification-intersects-datum-type-p
			type superior-type))))))))

(defun-simple class-type-specifications-could-intersect-p (class-spec1 class-spec2)
  (let ((class1 (type-specification-class class-spec1))
	(class2 (type-specification-class class-spec2)))
    (or (eq class1 class2)
	(and (eq class1 'item)
	     (let ((class-description2 (class-description class2)))
	       (and class-description2
		    (class-description-of-class-p class-description2 'item))))
	(and (eq class2 'item)
	     (let ((class-description1 (class-description class1)))
	       (and class-description1
		    (class-description-of-class-p class-description1 'item))))
	(not (class-type-specification-not-subtype-p class1 class2))
	(not (class-type-specification-not-subtype-p class1 class2))
	(not (stable-class-p class1))
	(not (stable-class-p class2))
	(let ((foundation1? (get-foundation-class-for-class class1))
	      (foundation2? (get-foundation-class-for-class class2)))
	  (if (and foundation1? foundation2?)
	      (or (subclassp foundation1? foundation2?)
		  (subclassp foundation2? foundation1?))
	      ;; The following is overly permissive, but safe.  Our brains
	      ;; hurt, and we can't quite figure out the implementation of
	      ;; checking for disjointness between classes which are not
	      ;; user-extensible (i.e. have no foundation-class), but which
	      ;; might have subclasses which are extensible.  Run away!!!
	      ;; -jallard & rh 5/20/97
	      t)))))




;;; The function `type-specification-of-role-result' takes a role and returns a
;;; type specification for the values that can be returned from that role, if
;;; any can be determined.

(defun-simple type-specification-of-role-result (non-atomic-role)
  (let ((type? (type-of-role non-atomic-role)))
    (when type?
      (if (valid-datum-type-specification-p type?)
	  type?
	  (make-class-type-specification type?)))))




;;; The function `type-specification-returning-datum-type-or-unknown' takes a
;;; type specification for a datum and returns a type specification for the
;;; classes which can return that datum or unknown as values.  This function
;;; also takes an optional argument indicating if this function can make
;;; allowances for type coercions when returning type specifications that would
;;; return the given type.  This is specifically needed for the float case,
;;; where coercion can turn integers into floats.

(defun type-specification-returning-datum-type-or-unknown
    (datum-subtype &optional allow-coercions?)
  #+development
  (assert (valid-datum-type-specification-p datum-subtype)
	  (datum-subtype)
	  "Datum-subtype argument ~a was not a subtype of datum."
	  datum-subtype)
  (cond
    ((type-specification-subtype-p datum-subtype 'text)
     '(or (class text-parameter)
	  (class text-variable)
	  (class sensor)))
    ((type-specification-subtype-p datum-subtype 'symbol)
     '(or (class symbolic-parameter)
	  (class symbolic-variable)
	  (class sensor)))
    ((type-specification-subtype-p datum-subtype 'truth-value)
     '(or (class logical-parameter)
	  (class logical-variable)
	  (class sensor)))
    ((type-specification-subtype-p datum-subtype 'integer)
     '(or (and (class quantitative-variable) (not (class float-variable)))
	  (and (class quantitative-parameter) (not (class float-parameter)))
	  (class sensor)))
    ((type-specification-subtype-p datum-subtype 'float)
     (if allow-coercions?
	 '(or (class quantitative-variable)
	      (class quantitative-parameter)
	      (class sensor))
	 '(or (and (class quantitative-variable) (not (class integer-variable)))
	      (and (class quantitative-parameter)
	           (not (class integer-parameter)))
	      (class sensor))))
    ((type-specification-subtype-p datum-subtype 'number)
     '(or (class quantitative-variable)
	  (class quantitative-parameter)
	  (class sensor)))
    (t '(class variable-or-parameter))))




;;; The function `type-specification-returning-datum-type' takes a type
;;; specification for a datum and returns a type specification for the classes
;;; which can return that datum as values.  This function
;;; also takes an optional argument indicating if this function can make
;;; allowances for type coercions when returning type specifications that would
;;; return the given type.  This is specifically needed for the float case,
;;; where coercion can turn integers into floats.

(defun type-specification-returning-datum-type
    (datum-subtype &optional allow-coercions?)
  #+development
  (assert (valid-datum-type-specification-p datum-subtype)
	  (datum-subtype)
	  "Datum-subtype argument ~a was not a subtype of datum."
	  datum-subtype)
  (cond
    ((type-specification-subtype-p datum-subtype 'text)
     '(class text-parameter))
    ((type-specification-subtype-p datum-subtype 'symbol)
     '(class symbolic-parameter))
    ((type-specification-subtype-p datum-subtype 'truth-value)
     '(class logical-parameter))
    ((type-specification-subtype-p datum-subtype 'integer)
     '(and (class quantitative-parameter)
	   (not (class float-parameter))))
    ((type-specification-subtype-p datum-subtype 'float)
     (if allow-coercions?
	 '(class quantitative-parameter)
	 '(and (class quantitative-parameter)
	       (not (class integer-parameter)))))
    ((type-specification-subtype-p datum-subtype 'number)
     '(class quantitative-parameter))
    (t '(class parameter))))




;;; The function `type-specification-held-in-variable-or-parameter' takes a
;;; variable-or-parameter and returns the most specific type specification
;;; possible describing the values held in the given frame.

(defun-simple type-specification-held-in-variable-or-parameter
       (variable-or-parameter)
   (frame-class-case variable-or-parameter
    ((integer-parameter)
     'integer)
    ((float-parameter)
     'float)
    ((quantitative-parameter)
     'number)
    ((symbolic-parameter)
     'symbol)
    ((text-parameter)
     'text)
    ((logical-parameter)
     'truth-value)
    ((parameter)
     'datum)
    ((integer-variable)
     '(or integer (unknown-datum)))
    ((float-variable)
     '(or float (unknown-datum)))
    ((quantitative-variable)
     '(or number (unknown-datum)))
    ((symbolic-variable)
     '(or symbol (unknown-datum)))
    ((text-variable)
     '(or text (unknown-datum)))
    ((logical-variable)
     '(or truth-value (unknown-datum)))
    ((variable)
     '(or datum (unknown-datum)))))

;;;




;;; The function `type-specification-held-in-type' takes a type specification
;;; and returns the most specific data type which can be proven to be held in
;;; items which conform to that type specification, or NIL if it cannot be
;;; proven that a particular type is held.

(defun-simple type-specification-held-in-type (type-specification)
  (or (and (type-specification-subtype-p type-specification '(class sensor))
	   '(or datum (unknown-datum)))
      (loop for type in '(text symbol truth-value integer float number datum)
	    do
	(when (type-specification-subtype-p
		type-specification
		(type-specification-returning-datum-type type))
	  (return type)))
      (loop for type in '(text symbol truth-value integer float number datum)
	    do
	(when (type-specification-subtype-p
		type-specification
		(type-specification-returning-datum-type-or-unknown type))
	  (return (make-type-specification-union type '(unknown-datum)))))))






;;;; Data Types




;;; The following section is some old type defining code taken from variables.
;;; All of this stuff should be replaced with the type code written above.  -jra
;;; 3/29/91

;;; `Data types' include units of measure. They form a hierarchy. The unrelated
;;; types of the hierarcy are NUMBER, TRUTH-VALUE, and SYMBOL.

;;; INTERVAL, PURE-NUMBER, TIME-STAMP and all `units of measure' are subtypes of
;;; NUMBER.  New numeric subtypes are declared with the function
;;; `def-numeric-subtype'.

;;; When eliminating this stuff, don't forget number-subtype-p.  -jra 3/29/91

(defun def-numeric-subtype (type &optional plural-of-type)
  (setf (numeric-data-type type)
        (or plural-of-type type)))




;; At some point it was possible for the symbol quantity to get into the
;; data type slot of variables, and so this def-numeric-type was added to
;; fix the bug.  There seems to be no reason to remove it now.  Also, no
;; date was put on the comment attached to this "temporary" fix, and so
;; we can't tell now when it was added.  -jra 4/12/89

(def-numeric-subtype 'quantity)




;;; The types integer and float are added as subtypes of number as well, though
;;; they can have their own subtype hierarchies.  See integer-data-type and
;;; float-data-type in definitions.

;; The types integer and float are not going to be released until Verson 2.1 or
;; such time as we have a type checking compiler which can give notifications of
;; errors in type combination.  -jra 6/18/89

;; The type checking compiler is being added in Version 3.0.  The types integer
;; and float have been added explicitly as part of the numeric-subtype-p test,
;; and so do not need to be declared as numeric-subtypes.  -jra 11/24/90




;;; The macro `value-type-compatible' takes two types and returns non-null if
;;; they are the same type, or if one of the types is 'number and the other is a
;;; numeric subtype, i.e. 'interval, 'pure-number, 'time-stamp, or a defined
;;; unit of measure.

(def-substitution-macro value-type-compatible (type1 type2)
  (or (eq type1 type2)
      (and (eq type1 'number)
	   (number-subtype-p type2))
      (and (eq type2 'number)
	   (number-subtype-p type1))
      (and (or (eq type1 'integer)
	       (memq type1 '(seconds interval)))
	   (or (eq type2 'integer)
	       (memq type2 '(seconds interval))))))




;;; The macro `type-and-datum-compatible-p' takes a G2 type and a datum and
;;; returns whether or not the datum is of the given type.  Note that the datum
;;; is not an evaluation value, but instead is a raw value.

(def-substitution-macro type-and-datum-compatible-p (type datum)
  (case type
    ((integer)
     (fixnump datum))
    ((long)
     (gensym-long-p datum))
    ((float)
     (gensym-float-p datum))
    ((symbol)
     (and datum (symbolp datum)))
    ((text)
     (text-string-p datum))
    ((truth-value)
     (and (fixnump datum)
	  (<=f falsity datum)
	  (<=f datum truth)))
    ((boolean)
     (and (fixnump datum)
	  (or (=f datum falsity)
	      (=f datum truth))))
    (t
     (and (number-subtype-p type)
	  (or (gensym-float-p datum)
	      (fixnump datum))))))




;;; The function `data-type-of-non-logical-datum' takes a value and returns the
;;; G2 data type which that value is an instance of, or else returns NIL.  This
;;; is used at compile time to determine the type of user entered constants
;;; arriving from the parser.

(defun-simple data-type-of-non-logical-datum (datum)
  (cond ((symbolp datum)
	 'symbol)
	((text-string-p datum)
	 'text)
	((fixnump datum)
	 'integer)
	((gensym-float-p datum)
	 'float)
	((phrase-float-p datum)
	 'float)
	((gensym-long-p datum)
	 'long)
	((phrase-long-p datum)
	 'long)
	((numberp datum)			; Unnecessary.  -jra 11/24/90
	 'number)
	(t
	 nil)))

(defun warn-about-unrecognized-type (unit-of-measure-or-type)
  (warning-message*
      1
      "Fetching a value of type ~a, an unrecognized type or unit of ~
       measure."
    unit-of-measure-or-type))



;;; The function `data-type-of-variable-or-parameter-datum' returns the type of
;;; a datum as it relates to the variable or paremter.  This function is used by
;;; some callers of put-current-value to determine the type of the
;;; non-evaluation datum values.

(declare-forward-reference
  type-specification-of-variable-or-parameter-value function)	;in VARIABLES

(defun-simple data-type-of-variable-or-parameter-datum (datum variable-or-parameter)
  (let ((type-spec
	  (type-specification-of-variable-or-parameter-value
	    variable-or-parameter)))
    (cond 
      ((and (not (eq type-spec 'truth-value)) (not (eq type-spec 'boolean)))
       (data-type-of-non-logical-datum datum))
      ((type-and-datum-compatible-p 'truth-value datum)
       'truth-value)
      (t
       ;; Should have a truth-value, but don't.
       (data-type-of-non-logical-datum datum)))))
;;;






;;;; Byte Code Body Free Reference Analysis




;;; The function `analyze-byte-code-body-for-free-reference-consistency' takes a
;;; byte-code-body and analyzes each free reference in it.

(defun analyze-byte-code-body-for-free-reference-consistency (parent byte-code-body)
  (when (and byte-code-body (byte-code-body-p byte-code-body))
    (let ((free-reference-vector?
	   (byte-code-body-free-references byte-code-body)))
      (when free-reference-vector?
	(loop for index from 0 by 2
	   below (length-of-simple-vector free-reference-vector?)
	   by 2
	   for type = (svref free-reference-vector? index)
	   for reference = (svref free-reference-vector? (+f index 1))
	   do (analyze-single-free-reference-for-consistency
	       parent type reference))))))




;;; The function `write-byte-code-body-free-references' takes a byte-code-body
;;; and twrites it.  Note that this function is only used during disassembles
;;; now.

(defun write-byte-code-body-free-references (byte-code-body)
  (let ((free-reference-vector?
	  (byte-code-body-free-references byte-code-body)))
    (if free-reference-vector?
	(loop for index from 0 below (length free-reference-vector?) by 2
	      for type = (svref free-reference-vector? index)
	      for reference = (svref free-reference-vector? (+f index 1))
	      do
	  (tformat "~%  ")
	  (twrite-single-free-reference-for-consistency type reference))
	(tformat "~%  None"))))






;;;; Environment Vector Allocation




;;; Rules, procedures, and simulations should use the following macro to
;;; allocate vectors for hold local var values at run time.  It uses an
;;; allocation policy which helps reduce fragmentation of vectors in the simple
;;; vector pool.

;;; The parameter `environment-allocation-schemes' contains an allocation scheme
;;; alist for use in determining appropriate rounding for environment vector
;;; sizes.  See the documentation around managed-array-allocation-schemes for a
;;; further description of allocation schemes.

(def-memory-allocation-schemes environment-allocation-schemes
    (64 8 1) (128 32 5))




;;; The parameter `maximum-environment-vector-length' is used by the compiler to
;;; ensure that environment vector descriptions don't get compiled which are
;;; longer than what we can produce.  This is currently limited by the maximum
;;; managed simple vector size at 1024.

;;; Note that this value must agree with the constant `maximum-var-spot-local-
;;; index', which should be one less than this number.  -jra 2/3/92

(defparameter maximum-environment-vector-length 1024)

;;




;;; The function `allocate-environment-vector' takes a fixnum of how long the
;;; environment vector has to be, and this function returns a simple vector
;;; which is long enough to hold that many values.  The maximum length is 2048.

#-development
(defmacro allocate-environment-vector
	  (needed-length &optional dont-initialize?)
  (if (constantp dont-initialize?)
      (if (eval dont-initialize?)
	  `(allocate-managed-simple-vector
	     (buffer-size-for-partial-buffer
	       ,needed-length
	       environment-allocation-schemes))
	  `(let ((new-vector (allocate-managed-simple-vector
			       (buffer-size-for-partial-buffer
				 ,needed-length
				 environment-allocation-schemes))))
	     (loop for index from 0 below (length-of-simple-vector new-vector)
		   do
	       (setf (svref new-vector index) nil))
	     new-vector))
      `(let ((new-vector (allocate-managed-simple-vector
			   (buffer-size-for-partial-buffer
			     ,needed-length
			     environment-allocation-schemes))))
	 (unless ,dont-initialize?
	   (loop for index from 0 below (length-of-simple-vector new-vector)
		 do
	     (setf (svref new-vector index) nil)))
	 new-vector)))

#+development ; a function version of above macro.
(defun allocate-environment-vector (needed-length &optional dont-initialize?)
  (when (>f needed-length maximum-environment-vector-length)
    (error "needed-length is too long"))
  (let ((new-vector (allocate-managed-simple-vector
		      (buffer-size-for-partial-buffer
		       needed-length
		       environment-allocation-schemes))))
    (unless dont-initialize?
      (loop for index from 0 below (length-of-simple-vector new-vector)
	    do
	(setf (svref new-vector index) nil)))
    new-vector))


;;; The function `reclaim-environment-vector' should be called to reclaim the
;;; vector and any remaining values within the environment vector.

(defun-simple reclaim-environment-vector (environment-vector)
  (let ((length (length-of-simple-vector environment-vector)))
    #+development
    (when (>f length maximum-environment-vector-length)
      (error "needed-length is too long"))

    (loop for index fixnum from 0 below length
	  for value = (svref environment-vector index)
	  do
      (reclaim-if-evaluation-value value))
    (reclaim-managed-simple-vector environment-vector)
    nil))



;;; The function `copy-environment-vector' takes a vector used as an environment
;;; vector and returns a copy of that vector containing the same elements, but
;;; with all evaluation values copied.

(defun-simple copy-environment-vector (environment-vector)
  (let ((length (length-of-simple-vector environment-vector)))
    #+development
    (when (>f length maximum-environment-vector-length)
      (error "needed-length is too long"))

    (loop with new-vector = (allocate-managed-simple-vector length)
	  for index from 0 below length
	  for value = (svref environment-vector index)
	  do
      (setf (svref new-vector index)
	    (copy-if-evaluation-value value))
	  finally
	    (return new-vector))))





;;;; Maintaining sets in locations.




;;; (add-to-set location item &optional pool) adds the item to the set in the
;;; location The set is actually a list, and so the behavior is like pushnew.
;;; The set is represented uniquely, using an eq test.  The value is the item if
;;; added, or nil if already present.

;;; (delete-from-set location item &optional pool) removes the item eq to the
;;; specified item from the set. The value is the item if removed, and nil if it
;;; never was there. Aditional copies will not be removed because they should
;;; never have been there.

;;; (clear-set location &optional pool) causes the value to be the empty set
;;; (nil).

;;; These functions recycle all conses. The locations that they reference should
;;; be initialized to nil, updated only by these functions.

;;; Each of these functions has an optional cons pool argument. If the set is
;;; made of slot value conses, for example, this should be SLOT-VALUE
;;; (unquoted).  The default is EVAL, for eval-conses.




(defun-for-macro find-pool-cons-macro (pool)
  (intern (format nil "~a-CONS-MACRO" pool)))


(defun-for-macro find-pool-cons-reclaimer-macro (pool)
  (intern (format nil "RECLAIM-~a-CONS-MACRO" pool)))


(defun-for-macro find-pool-list-reclaimer-macro (pool)
  (intern (format nil "RECLAIM-~a-LIST-MACRO" pool)))


(defmacro add-to-set (location item &optional (pool 'eval))
  (let ((set-in-location (gensym))
	(value-of-item (gensym)))
    `(let ((,set-in-location ,location)
	   (,value-of-item ,item))
       (unless (memq ,value-of-item ,set-in-location)
	 (prog1 ,value-of-item
		(setf ,location
		      (,(find-pool-cons-macro pool) 
		       ,value-of-item ,set-in-location)))))))


(defmacro delete-from-set (location item &optional (pool 'eval))
  (let ((value-of-item (gensym))
	(trailing-pointer (gensym))
	(leading-pointer (gensym)))
    `(loop with ,value-of-item = ,item
	   for ,trailing-pointer = nil then ,leading-pointer
	   for ,leading-pointer = ,location then (cdr ,leading-pointer)
	   until (null ,leading-pointer) doing
	   (when (eq (car ,leading-pointer) ,value-of-item)
	     (if ,trailing-pointer
		 (setf (cdr ,trailing-pointer) (cdr ,leading-pointer))
		 (setf ,location (cdr ,leading-pointer)))	     
	     (return (prog1 (car ,leading-pointer)
			    (,(find-pool-cons-reclaimer-macro pool)
			     ,leading-pointer)))))))



(defmacro clear-set (location &optional (pool 'eval))
  `(prog1 (,(find-pool-list-reclaimer-macro pool) ,location)
	  (setf ,location nil)))






;;;; Explanation Update Scheduling




(declare-forward-reference backward-chaining-displays variable)	; EXPLAIN


;;; The following facilities are for scheduling updates to backward
;;; chaining displays.

;;; The macro `update-backward-chaining-displays' takes a thing, either a
;;; variable or a rule-instance, and will cause any backward chaining
;;; displays which this is displayed upon to be updated.  This macro should be
;;; called whenever the things-this-variable-is-interested slot of a variable,
;;; or the ri-things-this-rule-instance-is-interested-in slot of a
;;; rule-instance is modified.  Note that this is a NON-STANDARD MACRO!  If
;;; there are no displays, the argument will not be evaluated.

(defmacro update-backward-chaining-displays (thing)
  `(when backward-chaining-displays
     (update-backward-chaining-displays-function ,thing)))






;;;; Procedure Errors




;;; The function `raw-stack-error' takes the top of stack, an evaluation symbol,
;;; a text (the symbol and text will be reclaimed by the error handler), and an
;;; optional suppress-debugging-info?  flag and signals an error.  Note that no
;;; extra descriptions of the error are added to the error text, it is up to
;;; callers of this macro to do this.

;; unused?
(defun-void raw-stack-error (top-of-stack error-name error-text) ;suppress-debugging-info? = nil
  (throw :stack-error
	 (values top-of-stack error-name error-text nil)))

(defun-void raw-stack-error-named-error (top-of-stack error-text) ;suppress-debugging-info? = nil
  (throw :stack-error
	 (values top-of-stack 'error error-text nil)))

(defun-void raw-stack-error-1 (top-of-stack error-name error-text) ;suppress-debugging-info? = t
  (throw :stack-error
	 (values top-of-stack error-name error-text t)))

;; Error-text is now an "error-text" object, which is currently either a string
;; or a list.


;; Stuff to support finding leaks and corruptions in stack-error usage:

;; Notice this still doesn't catch problems like bug HQ-4820539 "access-error
;; leak if there are subscription problems" because that's leaking the argument
;; to the format-string! -dkuznick, 7/2/04

#+development
(progn

(defparameter-for-macro find-stack-error-leaks t)

;;; `non-leaking-stack-error-callers' is used to get around the fact that there
;;; are sometimes false-positives in us trying to catch a leak in stack-error.
(defconstant non-leaking-stack-error-callers
  '(
    find-network-interface-for-icp-socket
    g2-set-text-of-trend-chart-component
    stack-eval-handle-transient-connection-error?
    transfer-action-internal
    g2-register-login-handler
    call-dialog-update-callback
    handle-dialog-dismissed
    handle-miscellaneous-dialog
    handle-dialog-gesture
    ))

;;; Use `unfixed-leaking-stack-error-callers' as a place to put a caller of
;;; stack-error which you know is leaking its format-string argument, but is
;;; too hard to fix (right now...).
(defconstant unfixed-leaking-stack-error-callers
  '(
    ;; leaks modification-while-executing?
    funcall-change-the-text-of-attribute-inst

    ;; leaks error-string? in some cases!  Go check parse-text-string, which
    ;; seems to sometimes copy and sometimes return a constant second value.
    make-inspect-command-or-signal-error

    g2-set-icon-variable-value

    ;; Find by meta-. g2-subdirectories-in-directory
    g2-subdirectories-in-directory-system-rpc-internal

    ;; Find by meta-. g2-delete-file
    g2-delete-file-system-rpc-internal
    ))

(defun-for-macro find-notifier-problems (notifier control-string)
  (when (and (not (gensym-string-p control-string))
             (not (and (constantp control-string)
                       (gensym-string-p (eval control-string))))
	     (not (memq most-recent-defun-name
			unfixed-leaking-stack-error-callers))
	     (not (memq most-recent-defun-name
			non-leaking-stack-error-callers)))
    (warn "Possible format-string leak of ~s argument in ~s ~
           usage in ~s - If it's leaking go fix it, if not add it ~
           to non-leaking-stack-error-callers."
	  notifier
	  control-string
	  most-recent-defun-name)))

)


;;; The macro `stack-error' is used to signal errors within stack instructions.
;;; It takes the top-of-stack as its first argument, a tformat control string as
;;; its second argument, and the rest of its arguments are arguments to
;;; formatting directives in the control string.  This macro will evaluate all
;;; of its arguments, then perform a throw to the handler for stack evaluator
;;; errors.

;;; The formatted error description should be a sentence or set of sentences
;;; which describe the error.  Information will be added to the error message by
;;; this facility which describes the current location within the thing being
;;; executed, so the error description should only describe the error and maybe
;;; the instruction or action name that had a problem, but not the current
;;; computation frame.

;;; Within the error handler, all of the values still on the stack (as given by
;;; top-of-stack) will be reclaimed by reclaim-if-evaluation-value.  If the
;;; caller of stack error has already reclaimed some of the values on the stack,
;;; then the caller must be sure to either set those stack locations to NIL, or
;;; to reclaim the rest of stack arguments to the instruction, and return a
;;; decremented value for top of stack.  Writers of instructions signalling
;;; errors are encouraged to leave all argument values to the instruction on the
;;; stack if possible.  This makes it easier for KB developers to examine the
;;; values being used by the instruction when it received an error, and to debug
;;; the problem.  However, if efficiency or some other consideration makes this
;;; inconvenient, it is ok to pop the values off the stack, as long as the
;;; recycling issues are handled correctly.

;;; The macro `write-stack-error' is used to signal errors within stack
;;; instructions, just like stack-error.  The difference is that this form
;;; encloses a body of tformat and twrite statements.  The output of these forms
;;; is collected into a string which is used as the error description.

(defmacro stack-error (top-of-stack tformat-control-string &rest
				    tformat-printed-args)
  (when (gensym-string-or-wide-string-p top-of-stack)
    ;; See bug HQ-4825252 "Corruptions in calls to stack error"
    (warn "You are passing ~s as the top-of-stack argument to ~
           stack-error in ~a - This is a corruption!!!"
	   top-of-stack
	   most-recent-defun-name))
  #+development
  (when find-stack-error-leaks
    (find-notifier-problems 'stack-error tformat-control-string))
  (let ((top-of-stack-var (make-symbol "TOP-OF-STACK"))
	(message-var (make-symbol "MESSAGE")))
    `(let* ((,top-of-stack-var ,top-of-stack)
	    (,message-var (tformat-stack-error-text-string
			    ,tformat-control-string ,@tformat-printed-args)))
       (raw-stack-error-named-error ,top-of-stack-var ,message-var))))

(defmacro write-stack-error (top-of-stack &body twriting-forms)
  (let ((top-of-stack-var (make-symbol "TOP-OF-STACK"))
	(message-var (make-symbol "MESSAGE")))
    `(let* ((,top-of-stack-var ,top-of-stack)
	    (,message-var
	     (twith-output-to-error-text
	       ,@twriting-forms)))
       (raw-stack-error-named-error ,top-of-stack-var ,message-var))))

(declare-side-effect-free-function tformat-stack-error-text-string)

(defun tformat-stack-error-text-string
       (control-string &optional arg1 arg2 arg3 arg4 arg5 arg6 arg7 arg8 arg9)
  (twith-output-to-error-text
    (tformat control-string arg1 arg2 arg3 arg4 arg5 arg6 arg7 arg8 arg9)))

(defmacro def-stack-error (name args format-control-string &rest format-args)
  (let ((message-function (intern (format nil "~A-~A" name 'message)))
	(message-args (remove 'top-of-stack args)))
    `(progn
       (defun ,message-function ,message-args
	 (tformat-stack-error-text-string
	   ,format-control-string
	   ,@format-args))
       (def-substitution-macro ,name ,args
	 (raw-stack-error-named-error
	    top-of-stack
	    (,message-function ,@message-args))))))


(defun cause-stack-error ()
  (stack-error
    cached-top-of-stack "Error explicitly triggered from the C debugger."))




;;; Note that we are removed disassembling from the product, but leave it in the
;;; code for development purposes.  The following variable can turn on
;;; disassembles in describe in all compiles of G2.  -jra 6/12/91

;; For the moment, disassembling will be turned on, pre Brian's request at the
;; release meeting today.  -jra 10/2/91

;; Turned it off again, per Lowell and Dave's request.  -jra 1/28/92

(defvar disassemble-enabled?
  #+development t
  #-development nil)




;; allow the potential for it to be turned on an off by system -rdf 11/17/93

(declare-system-procedure-function g2-enable-disassembler t)

(defun-funcallable g2-enable-disassembler ()
  (setq disassemble-enabled? t)
  (setq allow-internal-procedure-environment-printing? t))

(declare-system-procedure-function g2-disable-disassembler t)

(defun-funcallable g2-disable-disassembler ()
  (setq disassemble-enabled? nil)
  (setq allow-internal-procedure-environment-printing? nil))



;;; The function `signal-floating-point-exception-stack-error' takes no arguments
;;; and throws to the stack-error handler.  This function is called from the G2
;;; signal handler for FPE defined in PRIMITIVES when arithmetic-errors-are-stack-
;;; errors-p is true.

(defun signal-floating-point-exception-stack-error ()
  (stack-error
    cached-top-of-stack
    "A floating point exception has occurred.  Floating point exceptions are ~
     arithmetic errors such as dividing by zero, or overflowing or ~
     underflowing floating point number representations."))




;;; The function `signal-development-bad-value-for-make-evaluation-value' is a
;;; development only function used to signal errors for make-evaluation-value.
;;; It has been placed here so that there is no forward reference to the
;;; stack-error macro.

#+development
(defun signal-development-bad-value-for-make-evaluation-value
       (value type top-of-stack)
  (stack-error
    top-of-stack
    "Cannot make an evaluation value of the named type from the given ~
     object.  The object and type are ~a and ~a.  Please report this bug ~
     to Gensym software support."
    value type))

#+development
(defun reclaim-evaluation-float-error (evaluation-float top-of-stack)
  (stack-error
    top-of-stack
    "Non-evaluation-float given to reclaim-evaluation-float.  Please ~
     report this bug to Gensym software support.  The value given was ~a."
    evaluation-float))

#+development
(defun reclaim-evaluation-long-error (evaluation-long top-of-stack)
  (stack-error
    top-of-stack
    "Non-evaluation-long given to reclaim-evaluation-long.  Please ~
     report this bug to Gensym software support.  The value given was ~a."
    evaluation-long))

;;; Error Objects in G2

;;; The Error Hierarchy.
;;; This is just a bare bones hierarchy.  What is required is a full analysis
;;; of the types of errors generated from within G2.


;;; Top Level Class - error

(def-class (error  object
		   (foundation-class error)
		   define-predicate
		   do-not-put-in-menus)
  (error-description
    nil
    (type free text)
    system
    user-overridable
    )
  ;; The following are hooks into the annotation information. Consider making these read-only. -dkuznick, 3/3/99
  (error-source-item
    nil (type read-only-procedure-name?) system user-overridable not-user-editable)
  (error-source-line
    default-error-source-line (type integer) system user-overridable not-user-editable)
  (error-source-column
     default-error-source-column (type integer) system user-overridable not-user-editable)
  ;; We hold the chain of history of the error here, so when we re-signal a
  ;; handled error, we can expose the earlier state of G2 when the error was
  ;; signalled.  The things captured here are:
  ;;
  ;; error-source-description/item/line/column.  At some point a copy of the
  ;; stack might be here, but that would be overkill at this point.
  ;;
  ;; This is currently exposed via the error-source-trace virtual-attribute.
  (error-trace
    nil (type nil) system do-not-save)	;maybe want to save someday
)

;;; The slot putter `put-error-description' will accept two kinds of arguments
;;; a text, or an error text.  In the case of an error text the string
;;; component is converted to a text.

(def-slot-putter error-description (error error-text initializing-p)
  (declare (ignore initializing-p))
    (setf (error-description error)
	  (if (error-text-p error-text)
	       (convert-text-string-to-text
		(error-text-string error-text))
	       error-text)))


;; Move?
(def-virtual-attribute error-source-trace
    ((class error) (sequence) ())
  :event-updates nil
  :initial ((class) (declare (ignore class)) nil)
  :getter ((error)
	   (allocate-evaluation-sequence
	     (loop for (error-text? error-source-item error-source-line
				    error-source-column)
		   in (error-trace error)
		   collect (allocate-evaluation-structure-inline
			     'error-trace-description
			     (if error-text?
				 (convert-text-to-text-string error-text?)
				 ;; Technically this should be left as a nil
				 ;; {to be exposed as none}, but it's easier to
				 ;; deal with like this
				 (make-evaluation-text #w""))
			     'error-trace-source-item error-source-item
			     'error-trace-source-line error-source-line
			     'error-trace-source-column error-source-column)
		     using eval-cons))))
	     
	     
					
	       

;;; Subclass - default-error
;;; Error objects created by converting old style symbol and text errors to
;;; new style 

(def-class (default-error  error
	       define-predicate
	     not-user-instantiable
	     do-not-put-in-menus)
)


;;; Subclass - g2-error

(def-class (g2-error  error
		      define-predicate
		      not-user-instantiable
		      do-not-put-in-menus)
)

;;; g2-rpc-error.  Errors produced by remote procedure calls.

(def-class (g2-rpc-error  g2-error
		      define-predicate
		      not-user-instantiable
		      do-not-put-in-menus)
)

(def-class (g2-deadlock-error  g2-error
		      define-predicate
		      not-user-instantiable
		      do-not-put-in-menus))

;;; Operations involving Error objects


;;; The function `map-error-symbol-to-class-name' maps a symbol to the
;;; name of the class that it can be mapped to.
;;; The symbols 'error' and 'rpc-error' are treated as special cases
;;; because they are produced internally by G2 and can be mapped
;;; respectively to objects of type 'g2-error' and 'g2-rpc-error'.
;;; For all other symbols if there is a class of that name then that
;;; name will be returned.
;;; For symbols that do not correspond to an existing class and are
;;; not 'error' or 'rpc-error' then 'default-error is returned.
;;; This function is used by `convert-symbol-text-to-error-object'
;;; and by `find-error-handler-for-code-body-invocation'

(defun map-error-symbol-to-class-name (error-symbol)
  (cond ((eq 'error error-symbol) 'g2-error)
	((eq 'rpc-error error-symbol) 'g2-rpc-error)
	((and (classp error-symbol)
	      (subclassp error-symbol 'error))
	 error-symbol)
	(t 'default-error)))


(defun-void add-source-info-to-error-trace (error-object)
  ;; Probably need to store (and hence get passed the object) a reference to the
  ;; real item (here the item is just a name), so we can make sure it hasn't
  ;; been deleted, or recompiled since we stored this info when we go to expose
  ;; it
  (slot-value-push (slot-value-list (copy-text (error-description error-object))
				    (error-source-item error-object)
				    (error-source-line error-object)
				    (error-source-column error-object))
		   (error-trace error-object)))

;;; The function `setup-source-info-for-error-object' is used to initialize the
;;; apropriate slots on an error object.
;;;
;;; Note: in releases prior to 8.1b0, this stored the first two values returned
;;; by get-annotation-for-address-if-any as the error-source-line and
;;; error-source-column of the error object.  Those were unreliable in a few
;;; ways. The line number would be thrown off if the text stored in the
;;; procedure happened to be word-wrapped when it was lst edited.  And the
;;; column position was zero-based and would be thrown off by the presence of a
;;; linebreak character, or the sequence of the two linebreak characters CR and
;;; LF, which would appear on lines after a explicit ("hard") linebreak.  As of
;;; 8.0b0, we regard the old positions as symptoms of the bug HQ-4958380
;;; "breakpoint line/char indexes are for word-wrapped text".

(defun-void setup-source-info-for-error-object (error-object)
  (when (and current-computation-instance
	     (ok-to-get-source-code-lookup-info-p current-computation-instance))
    (let ((program-counter? (invocation-stack-program-counter
			      current-computation-instance))
	  (code-body (code-body-of-invocation-function current-computation-instance)))
      (when program-counter?
	(multiple-value-bind
	    (line-number? character-number
             non-wrapped-line-index non-wrapped-character-index
	     non-wrapped-user-column-position)
	    (get-annotation-for-address-if-any program-counter? code-body)
	  (declare (ignore character-number non-wrapped-character-index))
	  ;; Do we also want to do this if we don't have a program-counter?
	  ;; Why wouldn't we have one?  I'm prety sure we always do.
	  ;; -dkuznick, 10/31/06 
	  (setf (error-source-item error-object)
		(name-or-names-for-frame
		  (procedure-definition-of-code-body-function code-body)))
	  (setf (error-source-line error-object)
		(if line-number?
		    non-wrapped-line-index
		    default-error-source-line))
	  (setf (error-source-column error-object)
		(if line-number?
		    non-wrapped-user-column-position
		    default-error-source-column))
	  ;; In the future, we may want to add stack-trace info (like
	  ;; calling code-bodies, local bindings, etc).
	  (add-source-info-to-error-trace error-object))))))


;;; The function `convert-symbol-text-to-error-object' is used to map
;;; old style errors in the form of symbol and text into error objects.
;;; The type of error object to be created is determined by the symbol,
;;; using the function `map-error-symbol-to-class-name'.
;;; The error text is placed in the error-description attribute of the
;;; error object.  All error objects created in this way will be transient.

(defun-simple convert-symbol-text-to-error-object (error error-text)
  (let* ((class-to-create (map-error-symbol-to-class-name
			    error))
	 (error-object (make-transient-item class-to-create)))
    (put-error-description error-object error-text nil)
    ;; Put the annotation information into the error-object -dkuznick, 3/3/99
    (setup-source-info-for-error-object error-object)
    error-object))

;;; The function `convert-error-object-to-symbol-text' converts
;;; an error object in to symbol and text. 

(defun convert-error-object-to-symbol-text (error)
  ;; Return the symbol for the name of the error type
  ;; and a copy of the error-text if there is any.
   
  (let* ((class-of-error (class error))
	 (error-text (error-description error))
	 (text-to-return (if error-text
			     (convert-text-to-text-string error-text)
			     (make-wide-string 0))))
     (values class-of-error text-to-return)
    ))


;;; The function `map-between-error-styles' is used to convert between
;;; symbol, text and error object types of error depending upon the
;;; type of handler the error will be passed to.  The arguments
;;; new-style-error? and new-style-handler? are used to indicate the
;;; type of error, and type of handler respectively.   This function
;;; is used in `handle-error-in-code-body-invocation' in the PROC-UTILS
;;; module.

(defun map-between-error-styles (error-name-or-error-object error-message
							    new-style-error? new-style-handler?)
  (cond ((and new-style-error?
	      (not new-style-handler?))
	 (convert-error-object-to-symbol-text error-name-or-error-object))
	((and (not new-style-error?)
	      new-style-handler?)
	 (convert-symbol-text-to-error-object
	   error-name-or-error-object
	   error-message))
	(t (values error-name-or-error-object
		   error-message))))

;;; Throwing an Error Object from within G2.


;;; The macro `raw-stack-error-throw-object' signal errors
;;; by throwing an error object.  Whether the object is handled
;;; as an error object or not will depend upon the the argument types of the
;;; handler.


(defmacro raw-stack-error-throw-object (top-of-stack error-object)
  `(let ((error-description? (error-description ,error-object)))
     (raw-stack-error-1
       ,top-of-stack
       ,error-object
       (if error-description?
	   (convert-text-to-text-string error-description?)
	   (make-wide-string 0)))))

(defun raw-stack-error-throw-object-function (top-of-stack error-object)
  (raw-stack-error-throw-object top-of-stack error-object))

;; This is just here for testing until the new signal is in place,
;; and the new stack error macro to throw error objects has been completed.

#+development
(defun-for-system-procedure g2-signal-error-object
    ()
 (let ((error (make-transient-item 'default-error)))
    (raw-stack-error-throw-object cached-top-of-stack error)))


;;; The function `check-type-or-stack-error' signals a stack error if given
;;; evaluation value is not of given type. If allow-other-keys is true, then
;;; extra keys in structure values are permitted.

(defun check-type-or-stack-error (value type &optional allow-other-keys)
  (let ((error-message? (check-type-error-message value type allow-other-keys)))
    (when error-message?
      (write-stack-error cached-top-of-stack
	(tformat "~A" error-message?)
	(reclaim-text-string error-message?)))))


;;;; Profiling KBs


(def-concept profiler)

;;; `Profiling of KBs' is a feature that allows the user to measure the
;;; execution characteristics of a KB.  For example, the user can collect
;;; information regarding the runtime execution of rules, procedures, and other
;;; statements.  With this information, the user can determine what parts of the
;;; KB are being executed most frequently and for the longest periods of time.
;;; Based on this, they can determine what parts of the KB to optimize.

;;; Profiling data is collected for a KB when G2 is running and when profiling
;;; is enabled by the user.  Note that profiling data is not automatically
;;; cleared when profiling is enabled or disabled.  This allows the user the
;;; option of measuring different parts of the KB at various times without
;;; losing data.



;;; Profiling of KBs works as follows.  There is a lookup slot on kb-frames
;;; called profiling-structure? which usually is NIL.  If the variable
;;; profiling-enabled? is true when entering computation for a kind of thing,
;;; then the function which enters computation for that thing will create a
;;; structure, place it into the frame, and put that structure into the
;;; computation-context-variable current-profile-structure?.  At this point,
;;; all functions which profile different operations in G2 will register their
;;; information in this structure.

;;; Users of G2 access profiling information by called system procedures
;;; provided by us for this purpose.  The available system procedures are:

;;;   G2-ENABLE-PROFILING () - Turns on KB profiling.  New profiling data that
;;;   is collected will be added to any existing profiling data.  The profiling
;;;   begins immediately after this system-procedure returns.  For example, if
;;;   the call to this system-procedure is within a procedure that has
;;;   statements that follow it, then those statements are profiled.  Note that
;;;   start, pause, reset, and restart of G2 do not affect whether profiling is
;;;   enabled.  When G2 is reset or paused, profiling remains enabled, but no
;;;   additional profiling data is collected until G2 is running again.  When G2
;;;   then resumes running, any new profiling data is added to existing data.
 
;;;   G2-DISABLE-PROFILING () - Turns off KB profiling.  Profiling ends
;;;   immediately after this procedure returns.  Note that disabling profiling
;;;   does not clear the existing profiling data that has been collected.  If
;;;   profiling is re-enabled without calling g2-clear-profiling, then new
;;;   profiling data will be added to the existing data.

;;;   G2-CLEAR-PROFILING () - Clears the existing profiling data.  This is
;;;   necessary because disabling profiling does not clear this information.
;;;   Note that this procedure can be called when profiling is either enabled or
;;;   disabled.

;;;   G2-PROFILING-DATA () => (class g2-profiling-report) - Collect
;;;   the profiling data into a format that is accessible to the user.

;;    How about calling the above g2-create-profiling-report??  - cpm, 6/21/93

;;;   G2-WRITE-PROFILING-REPORT (class g2-profiling-report, text) - Writes a
;;;   profiling report to a file.  The first argument is a g2-profiling-report
;;;   that is returned from g2-generate-profiling-data.  The text argument
;;;   specifies a file name.

;; Do the above system-procedures need to contain wait states??  - cpm, 6/21/93



;;; Four kinds of profiling information are kept.  They are:

;;;   time used in system facilities such as data servers, network servers, user
;;;   interface servers, and process idle times;

;;;   time spent in individual user-defined computations including rules,
;;;   procedures, formulas, simulation-formulas, readout-tables, dials, meters,
;;;   graphs, and charts;

;;;   counts of the rules, procedures, and functions called by user-defined
;;;   computations; and

;;;   counts of each action and statement executed within rules and procedures.

;; Do we also want to record the reason for execution, for example, forward
;; chaining, rule scanning, user-interface, simulation, failed rules, etc.??  -
;; cpm, 6/21/93


;;; The begin-activity instruction is used, when profiling is enabled, to record
;;; the profiling data.  This instruction is emitted during the compilation of
;;; many actions and procedure statements.  See registered-activities-array, for
;;; a list of the profiled activies.


;;; The utilities for registering and collecting profiling information are
;;; defined below.

;;; The `profile' structure is used within the profiling-structure? slot of
;;; frames that have profiling information registered upon them.

;;; Hmmm.  This project was just cancelled, but I'll leave the comments here.
;;; -jra 6/10/92


;; Should transient-items, such as transient procedures or rules, be profiled??
;; - cpm, 6/21/93

;;; `The structures for profiling were moved to utilities4.lisp' -rdf, 12/21/94



(defun clear-basic-profiling-structure (s)
  (mutate-managed-float-value (basic-total-time s) 0.0)
  (setf (basic-total-calls s) 0)
  (loop with count-array = (profiling-activity-count-array s)
	for i from 0 below (length count-array)
	do
    (setf (svref count-array i) 0)))

;;; `make-basic-profiling-structure' calls makes a structure and clears it with
;;; clear-basic-profiling-structure. This assures that new and recycled
;;; structures look the same

(defun make-basic-profiling-structure ()
  (let ((new-structure (make-basic-profiling-structure1)))
    (clear-basic-profiling-structure new-structure)
    (values new-structure)))







;;; `clear-global-profiling-structure' clears the profiling structure. If
;;; profiling is currently enabled, it gets turned off during the clear. This
;;; prevents the profiling structure from getting in an interesting state.

(defun-void clear-global-profiling-structure (s)
  (let ((restart-profiling? nil))
    #+development
    (assert (global-profiling-structure-p s) nil
	    "~a is not a global-profiling-structure" s)
    (when profiling-enabled?
      (g2-toggle-system-profiling)
      (setq restart-profiling? t))
    (mutate-managed-float-value (total-clock-ticks-profiled s) 0.0)
    (mutate-managed-float-value (profiling-gensym-time-of-last-start s) 0.0)
    ;;this should only help things -rdf, 7/22/96
    (mutate-managed-float-value (start-time-of-last-profile-change s) 0.0)
    (mutate-managed-float-value (profiling-idle-time s) 0.0)
    (mutate-managed-float-value (profiling-clock-tick-time s) 0.0)
    (mutate-managed-float-value (profiling-redraw-time s) 0.0)
    (mutate-managed-float-value (profiling-icp-time s) 0.0)
    (clear-call-hash (profiling-call-information s))
    (when restart-profiling?
      (g2-toggle-system-profiling)) ))


;;; The system variable `current-profile-structure?' is part of the computation
;;; context and holds NIL or the profiling structure of the current computation
;;; frame when profiling is enabled.

(def-system-variable current-profile-structure? sets nil)



#+development
(defun print-profiling-structure (s &optional (stream *terminal-io*))
  (cond
    ((and s (basic-profiling-structure-p s))
     (format stream "~% ~a" (basic-profiling-name s))
     (when (and 
	    (numberp (basic-total-calls s)))
       (format stream "~%total time ~6,4f ~tcalls ~a ~ttime/call ~6,4f"
	       (managed-float-value (basic-total-time s)) (basic-total-calls s)
	       (if (= (basic-total-calls s) 0)
		   0
		   (/ (managed-float-value (basic-total-time s))
		      (basic-total-calls s)))))
     (loop for index from 0 below (length registered-activities-array)
	   for  potential-registrations from 1
	   with calls = (profiling-activity-count-array s)
	   with registration-count = 0
	   do
       (when (> (managed-svref calls index) 0)
	 (format stream "~%~a ~30tcalls ~a"
		 (string-upcase
		  (format nil "~a" (svref registered-activities-array index)))
		 (svref calls index))
	 (incf registration-count))
	   finally
	     (format stream "~%~a call types of ~a registered"
		     registration-count potential-registrations)))
    (t
     (format stream "~% ~a is not a basic profiling structure" s))))



;;; `insert-item-text-at-end-of-g2-list' and
;;; `insert-item-text-at-beginning-of-g2-list' are interfaces to the
;;; g-list-insert-at--- performing the evaluation-value conversions etc.

(defmacro insert-item-text-at-end-of-g2-list (g2-list format-string item)
  `(g2-list-insert-at-end
     (make-evaluation-text-reclaiming-argument
       (twith-output-to-text-string (tformat ,format-string ,item)))
     ,g2-list))

(defmacro insert-item-text-at-beginning-of-g2-list (g2-list format-string item-1)
  `(g2-list-insert-at-beginning
     (make-evaluation-text-reclaiming-argument
       (twith-output-to-text-string (tformat ,format-string ,item-1)))
     ,g2-list))

(defmacro insert-float-at-end-of-g2-list (g2-list gensym-float)
  `(g2-list-insert-at-end (make-evaluation-float ,gensym-float) ,g2-list))

(defmacro insert-float-at-beginning-of-g2-list (g2-list gensym-float)
  `(g2-list-insert-at-beginning (make-evaluation-float ,gensym-float) ,g2-list))

(defmacro insert-fixnum-at-end-of-g2-list (g2-list fixnum)
  `(g2-list-insert-at-end (make-evaluation-integer ,fixnum) ,g2-list))

(defmacro insert-symbol-at-end-of-g2-list (g2-list symbol)
  `(g2-list-insert-at-end (make-evaluation-symbol ,symbol) ,g2-list))

(defmacro insert-item-at-end-of-g2-list (g2-list item)
  `(g2-list-insert-at-end ,item ,g2-list))

(defmacro insert-fixnum-at-beginning-of-g2-list (g2-list fixnum)
  `(g2-list-insert-at-beginning (make-evaluation-integer ,fixnum) ,g2-list))

(defmacro insert-two-items-text-at-end-of-g2-list
    (g2-list format-string item-1 item-2)
  `(g2-list-insert-at-end
     (make-evaluation-text-reclaiming-argument
       (twith-output-to-text-string
	 (tformat ,format-string ,item-1 ,item-2)))
     ,g2-list))


(defmacro insert-three-items-text-at-end-of-g2-list
    (g2-list format-string item-1 item-2 item-3)
  `(g2-list-insert-at-end
     (make-evaluation-text-reclaiming-argument
       (twith-output-to-text-string
	 (tformat ,format-string ,item-1 ,item-2 ,item-3)))
     ,g2-list))

;;; `add-profiling-structure-to-g2-list' add information on the profiling
;;; structure to the end of the items on a g2-list of text items
(defun-void add-profiling-structure-to-g2-list (s call-list)
  #+development
  (assert (basic-profiling-structure-p s) nil
	  "~a is not a basic-profiling-structure" s)
  (let ((item-list (make-transient-item 'g2-list))
	(float-time-units-per-second
	  (coerce-fixnum-to-gensym-float fixnum-time-units-per-second)))
    (when (numberp (basic-total-calls s))
      (loop for index from 0 below (length registered-activities-array) 
	    for  potential-registrations from 1
	    with calls = (profiling-activity-count-array s)
	    with registration-count = 0
	    with call-data
	    do
	(when (> (svref calls index) 0)
	  (setq call-data (make-transient-item 'g2-list))
	  (insert-item-text-at-beginning-of-g2-list
	    call-data "~a"
	    (svref registered-activities-array index))
	  (insert-fixnum-at-end-of-g2-list
	    call-data
	    (svref calls index))
	  (g2-list-insert-at-end call-data item-list)
	  (incf registration-count))
	    finally
	      (progn
		(insert-fixnum-at-beginning-of-g2-list
		  item-list potential-registrations)
		(insert-fixnum-at-beginning-of-g2-list
		  item-list registration-count)))
      (insert-float-at-beginning-of-g2-list item-list
	(if (= (basic-total-calls s) 0)
	    0.0
	    (/e (managed-float-value (basic-total-time s))
		(*f (basic-total-calls s)
		    float-time-units-per-second))))
      (insert-float-at-beginning-of-g2-list
	item-list (/e (managed-float-value (basic-total-time s))
		      float-time-units-per-second))
      (insert-fixnum-at-beginning-of-g2-list
	item-list (basic-total-calls s))
      (insert-item-text-at-beginning-of-g2-list
	item-list "~a" (basic-profiling-name s))
      (g2-list-insert-at-beginning item-list call-list))))


;;; The structure `profiling-structure' holds profiling information for
;;; individual items within G2.  This structure holds a binary tree relating
;;; activity numbers to execution counts, hash tables of items to invocations
;;; kinds and counts, etc.

(def-system-variable profiling-structure sets nil)


;;; `print-global-profiling-information' prints a summary of the
;;; global profiling information

#+development
(defun print-global-profiling-information (&optional (stream *terminal-io*))
  (let ((profiler profiling-structure))
    (cond ((null profiler)
	   (format stream "~% No global profiling structure"))
	  (t
	   (format stream "~%Clock ticks monitored ~6,4f"
		   (managed-float-value (total-clock-ticks-profiled profiler)))
	   (format stream "~%Idle time ~6,4f"
		   (managed-float-value (profiling-idle-time profiler)))
	   (format stream "~%Clock tick time ~6,4f"
		   (managed-float-value (profiling-clock-tick-time profiler)))
	   (format stream "~%ICP time ~6,4f"
		   (managed-float-value (profiling-icp-time profiler)))
	   (format stream "~%Redraw time ~6,4f"
			   (managed-float-value (profiling-redraw-time profiler)))
	   (loop for x being each hash-value of (profiling-call-information profiler)
		 with profile-count fixnum = 0 
		 do
	     (format stream "~%")
	     (print-profiling-structure x)
	     (incff profile-count)
		 finally
		   (format stream "~% ~a Items profiled" profile-count))))))





;;; in SETS

(declare-forward-reference code-body-invocation? function)



;;; `g2-profiled-call-information' returns a g2-list of text items describing
;;; the time spent during  g2 system calls. Time values are in seconds.

(defun-funcallable g2-profiled-call-information ()
  (let ((call-data (make-transient-item 'g2-list))
	(profiler profiling-structure)
	(verbose nil))
    #+development
    (setq verbose t)
    (cond
      ((null profiler)
       (when verbose
	 (format t "~% no profiling structure"))
       (insert-item-text-at-end-of-g2-list
	call-data "No Profiling Information~a" " "))
      (t
       (loop for x being each hash-value of (profiling-call-information profiler)
	     with profile-count fixnum = 0 
	     do
	 (when verbose
	   (format t "~%Adding profile ~a" profile-count))
	 (add-profiling-structure-to-g2-list x call-data)
	 (incff profile-count)
	     finally
	       (progn
		 (insert-item-text-at-beginning-of-g2-list
		   call-data " ~a Items profiled" profile-count)))))
   call-data))

;;; the following lists provide a way for the profiler to abstract g2-internals
;;; for presentation to the user. There are used in `g2-system-profile' below.
;;; note that `unsorted-kb-profiling-names' are not used by this function but
;;; are listed here so that they are easy to find

(defconstant display-profiling-names
  '(execute-message-removal-task
    redraw-solid-rectangles-without-overlap
    refresh-window
    scheduled-display-update
    unhighlight-recent-message
    update-chart
    update-display-if-not-reprocessed
    scheduled-update-button
    scrolling-heartbeat
    update-display-for-digital-clock
    update-display-for-graph
    update-trend-chart-task
    verify-and-set-variable-per-non-action-button
    work-on-schedule-of-table-updates-a-little
    resume-search-task-in-workstation))

(defconstant scheduling-profiling-names 
  '(attempt-expression-cell-execution
    execute-backward-chaining-for-rules
    execute-computation-instance
    invoke-rule-universally
    schedule-computation-instance-execution
    schedule-initial-rules-from-activated-kb-workspace
    wake-up-code-body-invocation
    complete-initial-rules
    gfi-output-event-log-values-periodically-task
    gfi-output-spreadsheet-values-periodically-task
    propagate-variable-value-expiration
    safe-invoke-rules-for-existential-chaining
    immediately-return-from-breakpoint
    execute-scheduled-remote-procedure-start
    receive-start-or-call-remote-procedure-1
    receive-nupec-synchronize-task))

(defconstant data-service-profiling-names 
  '(accept-data-and-reschedule-if-necessary
    call-data-server-accept-data-functions
    collect-one-shot-data-for-g2-meters
    collect-one-shot-data-for-gfi-data-service
    continue-data-server-data-acceptance
    enqueue-gsi-request-for-sensor
    g2ds-begin-collecting-data
    g2ds-collect-one-shot-data
    initiate-inter-g2-set-value-request
    initiate-inter-g2-data-service-request
    kill-foreign-image-process-unconditionally
    perform-background-collection-for-inference-engine
    process-g2ds-variable-values
    process-gsi-sensor-values
    process-requests-for-gsi-interfaces
    return-values-to-g2ds-client-task
    task-to-detect-failure
    task-to-probe-failed-variable))

(defconstant kb-io-profiling-names
  '(continuation-task-for-current-backup ; run by execute-task-out-of-order
    continue-current-kb-save-or-backup
    terminate-kb-save-or-backup
    sys-proc-read-kb))

(defconstant icp-profiling-names
  '(handle-queued-icp-messages-task
    handle-read-event-function
    handle-write-event-function
    handle-close-event
    send-I-am-alive-message
    handle-unclogged-connection-if-necessary
    resumable-icp-write-callback
    time-out-icp-socket
    icp-connection-timeout-task-1
    icp-connection-timeout-task-2
    try-to-preflight-resumable-object
    try-to-transmit-resumable-object
    send-queued-reclaim-index-space-messages
    send-new-trend-chart-data-task
    socket-close-cleanups))

(defconstant workstation-profiling-names
  '(propagate-all-workspace-changes-to-image-planes
    propagate-allow-scheduled-drawing-1
    run-selection-callbacks
    run-area-selected-callbacks
    run-workspace-callbacks
    service-workstations-final
    service-workstation))

(defconstant overhead-kb-profiling-names
  '(completely-shut-down-g2 ; no point in profiling this!    
    #-development warn-user-of-previously-aborted-g2
    call-post-prominent-notification ; licensing
    do-legacy-multisecond-heartbeat-adjustments ; licensing
    do-legacy-subsecond-heartbeat-adjustments ; licensing
    initialize-for-asian-languages ; run only once, before profiling could have begun
    native-window-heartbeat ; licensing
    service-background-processes ; printing
    warn-about-editing-item ; source code control
    system-state-change-from-scheduler-1
    detect-and-break-deadlocks
    ))

(defconstant g2gl-profiling-lists
  '(continue-execution-of-thread
    continue-scheduled-process-invocation))

(defun-for-macro check-scheduled-task-names-function ()
  (note-scheduled-function-name 'continuation-task-for-current-backup) ; run by execute-task-out-of-order
  (loop with copy = (copy-list scheduled-function-name-list)
	for list-name in '(display-profiling-names scheduling-profiling-names data-service-profiling-names
			   kb-io-profiling-names icp-profiling-names workstation-profiling-names
			   overhead-kb-profiling-names g2gl-profiling-lists)
	do (loop for name in (symbol-value list-name)
		 do
	     (setq copy (delete name copy))
	     (when all-binaries-were-deleted-before-recompile-p
	       (unless (memq name scheduled-function-name-list)
		 (warn "The scheduled-task name ~s (from ~s) is not scheduled at all in G2"
		       name list-name))))
	finally (loop for name in copy
		      do (warn "The scheduled-task name ~s is not in any profiling list"
			       name))))

(defmacro check-scheduled-task-names ()
  (check-scheduled-task-names-function)
  nil)

;;; `g2-system-profile' returns a quantity list of the system items profiled.
;;; Some of the items are explicitly gathered by the profiler. Others are
;;; implicitly derived during the execution of this function

;;; The explicit items are
;;; quantity  0: clock ticks
;;; quantity  1: idle  time
;;; quantity  2: clock tick time
;;; quantity  3: icp    time
;;; quantity  4: workstation time

;;; The implicit items are
;;; quantity  5: display    time
;;; quantity  6: scheduling time
;;; quantity  7: data-service time
;;; quantity  8: kb-io      time
;;; quantity  9: overhead   time
;;; quantity 10: processing time
;;; quantity 11: total      time

;;; to add more functions to the current set of times add their names to the
;;; repsective lists

;;; to add a new type of implicit time add a cond clause within the hash loop
;;; and add another item to the finally (progn ... construct
;;; Also appropriately increment the item-count local variable so that the
;;; calling procedure gets back the right number of items, even if profiling
;;; has not been enabled

(defmacro increment-managed-float-with-managed-float (base-float increment-float)
  (let ((base-name (gensym))
	(increment-name (gensym)))
    `(let ((,base-name ,base-float)
	   (,increment-name ,increment-float))
       (mutate-managed-float-value
	     ,base-name
	     (+e (managed-float-value ,base-name)
		 (managed-float-value ,increment-name))))))

(defun-void disable-and-clear-system-profiling ()
  (when profiling-enabled?
    (g2-disable-system-profiling))
  (g2-clear-profiling-inner))

(declare-system-procedure-function g2-system-profile nil)

(defun-funcallable g2-system-profile ()
  (let ((system-data (make-transient-item 'quantity-list))
	(profiler profiling-structure)
	(restart? nil)
	(item-count 11))
    
    (when profiling-enabled?
      (g2-disable-system-profiling)
      (setq restart? t))
    (cond (profiler
	   (loop for x being each hash-value of (profiling-call-information profiler)
		 with scheduling-time =   (coerce-fixnum-to-gensym-float 0)
		 with data-service-time = (coerce-fixnum-to-gensym-float 0)
		 with kb-io-time =        (coerce-fixnum-to-gensym-float 0)
		 with overhead-time =     (coerce-fixnum-to-gensym-float 0)
		 with workstation-time =  (coerce-fixnum-to-gensym-float 0)
		 with display-time =     (managed-float-value (profiling-redraw-time profiler))
		 with icp-time =         (managed-float-value (profiling-icp-time profiler))
		 with idle-time =        (managed-float-value (profiling-idle-time profiler))
		 with clock-tick-time =  (managed-float-value (profiling-clock-tick-time profiler))
		 with total-time =       (managed-float-value (total-clock-ticks-profiled profiler))
		 with system-time = (+e display-time icp-time workstation-time idle-time clock-tick-time)
		 for name = (basic-profiling-name x)
		 for duration = (managed-float-value (basic-total-time x))
		 do
	     ;; schedule blocks have name, and are associated with system functions
	     (unless (numberp name)
	       (setq system-time (+e system-time duration))
	       (cond
		 ((member name display-profiling-names)
		  (setq display-time (+e display-time duration)))
		 ((member name scheduling-profiling-names)
		  (setq scheduling-time (+e scheduling-time duration)))
		 ((member name data-service-profiling-names)
		  (setq data-service-time (+e data-service-time duration)))
		 ((member name kb-io-profiling-names)
		  (setq kb-io-time (+e kb-io-time duration)))
		 ((member name icp-profiling-names)
		  (setq icp-time (+e icp-time duration)))
		 ((member name workstation-profiling-names)
		  (setq workstation-time (+e workstation-time duration)))
		 (t
		  (setq overhead-time (+e overhead-time duration)))))
		 finally
		   (progn
		     ;;quantity 0	   
		     (insert-float-at-end-of-g2-list system-data idle-time)
		     ;;quantity 1	   
		     (insert-float-at-end-of-g2-list system-data clock-tick-time)
		     ;;quantity 2
		     (insert-float-at-end-of-g2-list system-data icp-time)
		     ;;quantity 3
		     (insert-float-at-end-of-g2-list system-data workstation-time)
		     ;;quantity 4
		     (insert-float-at-end-of-g2-list system-data display-time)
		     ;;quantity 5
		     (insert-float-at-end-of-g2-list system-data scheduling-time)
		     ;;quantity 6
		     (insert-float-at-end-of-g2-list system-data data-service-time)
		     ;;quantity 7
		     (insert-float-at-end-of-g2-list system-data kb-io-time)
		     ;;quantity 8
		     (insert-float-at-end-of-g2-list system-data overhead-time)
		     ;;quantity 9
		     (insert-float-at-end-of-g2-list system-data (-e total-time system-time))
		     ;;quantity 10
		     (insert-float-at-end-of-g2-list system-data total-time))))
	  (t				;no profiler just stuff with zeros
	   (loop for i from 0 to item-count		 
		 initially
		   (insert-fixnum-at-end-of-g2-list system-data 0)
		 do
	     (insert-float-at-end-of-g2-list system-data  0.0))))
    (when restart?
      (g2-enable-system-profiling))
    (values system-data)))
 
;;; `g2-procedure-detail' returns a quantity list of the calls, total time and
;;; time/call for the named procedure



(declare-system-procedure-function g2-procedure-detail nil)

(defun-funcallable g2-procedure-detail (item)
  (let ((procedure-data (make-transient-item 'quantity-list))
	(profiler profiling-structure)
	(profiled-data nil)
	(execution-time 0.0))
    (declare (type gensym-float execution-time))
    (when profiler
      (setq profiled-data
	    (find-profiled-data-given-item item)))
    (cond ((and profiler profiled-data)
	   (setq execution-time
		 (managed-float-value (basic-total-time profiled-data)))  
	   ;;quantity 0
	   (insert-fixnum-at-end-of-g2-list
	     procedure-data (basic-total-calls profiled-data))
	   ;;quantity 1
	   (insert-float-at-end-of-g2-list
	     procedure-data execution-time)
	   ;;quantity 2
	   (insert-float-at-end-of-g2-list
	     procedure-data
	     (if (= (basic-total-calls profiled-data) 0)
		 0.0
		 (/e execution-time
		     (coerce-fixnum-to-gensym-float
		       (basic-total-calls profiled-data)))))) 
	  (t ;; no information
	   (insert-fixnum-at-end-of-g2-list
	     procedure-data 0)
	   (insert-float-at-end-of-g2-list
	     procedure-data 0.0)
	   (insert-float-at-end-of-g2-list
	     procedure-data 0.0)))
      (values procedure-data)))



;;; `registered-activities-symbol-array' is an array of the registered
;;; activities as symbols rather than strrings. The goal being to speed up the
;;; activity index given symbol search

(defvar registered-activities-symbol-array nil)

;;; `create-registered-activities-symbol-array' creates the array using the
;;; predefined registered-activities-array

(defun create-registered-activities-symbol-array ()
  (setq registered-activities-symbol-array
	(make-array (length registered-activities-array)))
  (loop for index from 0 below (length registered-activities-array)
	do
    (setf (svref registered-activities-symbol-array index)
	  (intern
	    (nstring-upcase  ; handles these US-ASCII strings
	      (substitute #\- #\Space
			  (aref registered-activities-array index)))))))

(create-registered-activities-symbol-array)



#+development
(defun print-registered-activities-symbol-array ()
  (loop for index from 0 below (length registered-activities-symbol-array)
	do
    (format t "~% index ~a: ~a"
	    index (svref registered-activities-symbol-array index))))

;;; `activity-index-given-symbol' is a very simpel linear search through the
;;; activity symbol list

(defun activity-index-given-symbol (activity-symbol)
  (loop for index from 0 below (length registered-activities-symbol-array)
	with matched-index = nil
	until matched-index
	do
    (when (eq activity-symbol
	      (svref registered-activities-symbol-array index))
      (setq matched-index index))
	finally
	  (return matched-index)))

(defun find-profiled-data-given-item (item)
  (let ((profiled-data nil))
    (loop for x being each hash-value of (profiling-call-information profiling-structure)
	  until profiled-data
	  do
      (when (and (eq (basic-profiling-item x) item)
		 (frame-serial-number-equal (basic-profiling-serial-number x)
					    (frame-serial-number item)))
	(setq profiled-data x)))
    profiled-data))

;;; `g2-procedure-activity-list' generates a list of the activities profiled in a
;;; procedure. It returns a symbol list whose members can later be handed back
;;; to the function `procedure-activity-calls' to get a count of the number of
;;; activity calls generated by the procedure

(declare-system-procedure-function g2-procedure-activity-list nil)

(defun-funcallable g2-procedure-activity-list (item)
  (let ((procedure-activities (make-transient-item 'symbol-list))
	(profiler profiling-structure)
	(profiled-data nil))
    (when profiler
      (setq profiled-data (find-profiled-data-given-item item))
      (when profiled-data
	(loop for index from 0 below (length registered-activities-array)
	      with calls = (profiling-activity-count-array profiled-data)
	      do
	  (when (> (svref calls index) 0)
	    (insert-symbol-at-end-of-g2-list
	      procedure-activities
	      (svref registered-activities-symbol-array index))))))
    (values procedure-activities)))


(defvar limit-profiling-based-on-licence-level-p t)

(defmacro defun-for-profiling  (name arguments &body body)
  `(progn
     (declare-system-procedure-function ,name nil)
     (defun-funcallable ,name ,arguments
       (when (and
	       #+runtime-functionality-without-a-license
	       t
	       #-runtime-functionality-without-a-license
	       (g2-limited-to-this-license-level-or-more restricted-use)
	       limit-profiling-based-on-licence-level-p)
	 (stack-error
	   cached-top-of-stack
	   "Attempt to invoke unlicensed system procedure."))
       ,@body)))


(declare-system-procedure-function g2-allow-profiling-regardless-of-license nil)

(defun-funcallable g2-allow-profiling-regardless-of-license ()
  (setq limit-profiling-based-on-licence-level-p nil))


(declare-system-procedure-function g2-user-name-for-frame t)

(defun-funcallable g2-user-name-for-frame (a-frame)
  (let (designation
	name-for-user)

    (setq designation (get-or-make-up-designation-for-block a-frame)) 
    (cond ((symbolp designation)
	   (setq name-for-user (make-evaluation-value designation 'symbol)))
	  (t
	   (setq name-for-user (make-evaluation-value designation 'text))))
    name-for-user))
    
(defun-for-profiling g2-procedure-activity-calls (item activity-symbol)
  (let ((profiler profiling-structure)
	(activity-calls (make-transient-item 'quantity-list))
	(profiled-data nil)
	(index nil)
	(calls nil))
    (when profiler
      (setq profiled-data (find-profiled-data-given-item item))
      (when profiled-data
	(setq index (activity-index-given-symbol activity-symbol)))
      (when index
	(setq calls
		(float
		  (svref (profiling-activity-count-array profiled-data)
				    index))) 
	(insert-float-at-end-of-g2-list activity-calls calls)))

    ;; calls is nil if any of the above tests fail
    (unless calls
      (insert-float-at-end-of-g2-list activity-calls 0.0))
    (values activity-calls)))


;;; `g2-system-profiled-items' returns a symbol list of items (and their serial
;;; numbers) which have been profiled by the system
;;; this list is then passed back into `procedure-activity-list' and
;;; `procedure-detail' for more detailed information

(defun-for-profiling g2-system-profiled-items ()
  (let ((system-data (make-transient-item 'g2-list))
	(profiler profiling-structure)
	table)
    (when profiler
      (setq table (profiling-call-information profiler))
      (loop for x being each hash-value of table
	    for name = (basic-profiling-name x)
	    do
	;; only those with a number are shown to the user
	(when (and (not (symbolp name))
		   (>f (basic-total-calls x) 0))
	  (cond ((frame-serial-number-equal (frame-serial-number (basic-profiling-item x))
					    (basic-profiling-serial-number x))
		 (insert-item-at-end-of-g2-list
		   system-data
		   (basic-profiling-item x)))
		(t
		 ;; Shouldn't get here now but fixing below to show incorrect logic.
		 #+development (break "Go tell DBK that he was wrong")
		 (delete-call-hash (basic-profiling-item x) table)))
	  )))
    (values system-data)))

#+development
(defun show-profiling-info ()
  (let ((profiler profiling-structure))
    (when profiler
      (loop for x being each hash-value of (profiling-call-information profiler)
	    do
	(format t "~% structure name item ~a, ~a, ~a ~a"
		x
		(basic-profiling-name x)
		(basic-profiling-item x)
		(basic-total-calls x) )))))


;;; `g2-enable-system-profiling' starts up system profiling if it is not already
;;; enabled.

(defun-for-profiling g2-enable-system-profiling ()
  (unless profiling-enabled?
    (let ((current-time (gensym-get-unix-time)))
      (unless profiling-structure
	(setq profiling-structure (make-global-profiling-structure)))
      (mutate-managed-float-value
	(profiling-gensym-time-of-last-start profiling-structure)
	current-time)
      ;;this should only help things -rdf, 7/22/96
      (mutate-managed-float-value
	(start-time-of-last-profile-change profiling-structure)
	current-time))
    
    (setq profiling-enabled? profiling-structure)))



;; `exit-current-profiling-context' clears the current context to avoid double
;; charging of time. Some of the system data is not charged to
;; profiling-structures 
(defun-void exit-current-profiling-context (current-time)
  (when (and profiling-enabled? current-profile-structure?)
    (incf (managed-float-value (basic-total-time current-profile-structure?))
	  (-e (managed-float-value current-time)
	      (managed-float-value (start-time-of-last-profile-change profiling-enabled?))))
    (setf (managed-float-value (start-time-of-last-profile-change profiling-enabled?))
	  (managed-float-value current-time))
    (setq current-profile-structure? nil)))

;;; `g2-disable-system-profiling' shuts down up system profiling if it is enabled.
;;; It also increments the total time

(defun-for-profiling g2-disable-system-profiling ()
  (when profiling-enabled?
    (let* ((current-time (allocate-managed-float
			   (gensym-get-unix-time))))
      (mutate-managed-float-value
	(total-clock-ticks-profiled profiling-structure)
	(+e
	  (managed-float-value (total-clock-ticks-profiled profiling-structure))
	  (-e (managed-float-value current-time)
	      (managed-float-value
		(profiling-gensym-time-of-last-start profiling-structure)))))
      (exit-current-profiling-context current-time)
      (mutate-managed-float-value
	(profiling-gensym-time-of-last-start profiling-structure) 0.0)
      (setq profiling-enabled? nil)
      (reclaim-managed-float current-time))))






;;; `g2-toggle-system-profiling' toggles profiling-enabled? calling
;;; enable-system-profiling or disable-system-profiling as appropriate
;;;  creates a global-profiling-structure for  profiling-structure
;;;  if none currently exists

(defun-funcallable g2-toggle-system-profiling ()
  (cond (profiling-enabled? (g2-disable-system-profiling))
	(t (g2-enable-system-profiling))))

;;; `g2-clear-profiling' is the external interface to
;;; clear-global-profiling-structure. It only performs the call if there is a
;;; structure to clear

(defun-for-profiling g2-clear-profiling ()
  (g2-clear-profiling-inner))

(defun g2-clear-profiling-inner ()
  (when profiling-structure
    (clear-global-profiling-structure profiling-structure)))

(defun-simple find-or-create-profiling-structure (thing-to-profile hash-table)
  (let* ((profiling-structure? (get-call-hash thing-to-profile hash-table)))
    (when (and profiling-structure?
	       (not (symbolp thing-to-profile))
	       (not (frame-serial-number-equal
		      (frame-serial-number thing-to-profile)
		      (basic-profiling-serial-number profiling-structure?))))
      (delete-call-hash profiling-structure? hash-table)
      (setq profiling-structure? nil))
    (unless profiling-structure?
      (setq profiling-structure? (make-basic-profiling-structure))
      (unless (symbolp thing-to-profile)
	(frame-serial-number-setf
	  (basic-profiling-serial-number profiling-structure?)
	  (frame-serial-number thing-to-profile)))
      (setf (basic-profiling-name profiling-structure?)
	    (if (symbolp thing-to-profile)
		thing-to-profile
		(copy-frame-serial-number
		  (frame-serial-number thing-to-profile))))
      (setf (basic-profiling-item profiling-structure?) thing-to-profile)
      (setf (get-call-hash thing-to-profile hash-table)
	    profiling-structure?))
    profiling-structure?))
  
(defun-void increment-profiling-calls (item-to-profile)
  (let* ((call-hash-table (profiling-call-information profiling-enabled?))
	 (profiling-structure
	   (find-or-create-profiling-structure
	     item-to-profile call-hash-table)))
    (setf (basic-total-calls profiling-structure)
	  (+f (basic-total-calls profiling-structure) 1))))

(declare-forward-reference item-to-profile-of-formula-invocation function)

(declare-forward-reference is-a-formula-invocation? function)

					
;;; `note-possibly-profiled-item-deletion' is used to remove profiled items from
;;; the hash-table before they get deleted to avoid problems later. 
(defun-void note-possibly-profiled-item-deletion (item)
  (let ((call-hash (profiling-call-information profiling-structure)))
    (when (get-call-hash item call-hash)
      (delete-call-hash item call-hash))))

;;; `posit-profiling-structure' is currently a function which places a top
;;; level profiling structure in the global variable current-profile-structure?


(defun-void posit-profiling-structure (item)
  (when (and item
	     (not (code-body-invocation? item)))
    ;; this is a hack to get us around some temporary problems
    (let ((thing-to-profile
	    (cond
	      ((symbolp item) item)
	      ((schedule-task-p item) (schedule-task-function-name item))
	      ((is-a-formula-invocation? item)
	       (item-to-profile-of-formula-invocation item))
	      ;; new on 2/2/94 rdf
	      ((rule-instance-p item) (ri-rule item))
	      ;; new on 9/8/93 rdf
	      ((of-class-p item 'block) item)
	      #+development
	      (t
	       (cerror "Posit Profiling" "unknown item type ~a" item)))))
      (when thing-to-profile
	(let ((call-hash-table (profiling-call-information profiling-enabled?))
	      (current-time (allocate-managed-float (gensym-get-unix-time))))
	  (exit-current-profiling-context current-time)
	  (setq current-profile-structure?
		(find-or-create-profiling-structure thing-to-profile call-hash-table))
	  ;; make one if there isn't one
	  (mutate-managed-float-value
	    (start-time-of-last-profile-change profiling-enabled?)
	    (managed-float-value current-time))
	  (reclaim-managed-float current-time))))))






;;;; System Procedures for Save




;; These have been moved here from WARMBOOT because they use evaluation value
;; macros defined above.

;;; G2-save-kb is the system procedure for starting save of kbs for
;;; warmboot.  The arguments are a pathname string, a symbol indicating
;;; the type of the save (whether to save runtime data, etc.), a flag
;;; indicating whether notifications should be suppressed, and a
;;; G2-window.  It returns nil if the save was successful, otherwise, an
;;; error flag (integer).
;;;
;;; G2-save-module is the system procedure for starting saves of one
;;; or more modules of a KB (which are KBs themselves).  It is just
;;; like G2-save-kb, but has two additional arguments past the first
;;; three (past the g2-window arg): a module name (a symbol) and a flag
;;; indicating whether to include the required modules of the KB.

;;; G2-continue-save-kb and g2-finish-save-kb are the system
;;; procedures for continuing and finishing save of kbs for warmboot.
;;; G2-save-kb, g2-continue-save-kb, and g2-finish-save-kb are
;;; all called from the save-kb g2 system procedure in the knowledge
;;; base.  The g2 procedure controls scheduling of these procedures
;;; (rather than having these schedule themselves) so that g2-save-kb,
;;; g2-continue-save-kb, and g2-finish-save-kb can return a value to
;;; the g2 procedure indicating whether the save succeeded.

;;; G2-save-kb returns an integer.  If the integer is 0, the save can
;;; proceed.  If the integer is not 0, it is an error code.
;;; G2-continue-save-kb returns two values: a truth value indicating
;;; whether it is finished, and an integer error code the same as the
;;; one for g2-save-kb G2-finish-save-kb returns the same integer
;;; value as g2-save-kb.

;;; The g2 procedure runs at its own priority when calling g2-save-kb,
;;; g2-continue-save-kb, and g2-finish-save-kb.  Thus, the
;;; default-priority-for-runtime-saving slot in saving-parameters is
;;; ignored (overridden).  The g2 procedure checks the error codes and
;;; returns two values: a truth value indicating whether the save was
;;; successful, and an integer error code.

;;; `G2-save-kb-without-other-processing' and
;;; `g2-save-module-without-other-processing' are the lisp-side functions to
;;; support three new system procedures introduced in G2 5.1r5 and in 6.0:
;;;
;;;    g2-save-kb-without-other-processing
;;;    g2-snapshot-without-other-processing
;;;    g2-save-module-without-other-processing
;;;
;;; These system procedures use the original, non-interruptable mode of saving
;;; KBs.  Originally, we could do things this way when we were paused or reset
;;; because we lacked a scheduler.  However, some users have expressed the
;;; desire or demand for these features because of bugs while saving while
;;; running.  Saving in this non-interruptable mode has these advantages: not
;;; saving-while-running bugs; runs faster; saves in a normal (more stable)
;;; manner that cause less diffs for source code control systems.
;;;
;;; NOTE: at this time there is no analogous procedure for XML (clear text) KBs
;;; because there is no time or resources to do that, though saving them in this
;;; way would seem logical.  (MHD 3/2/00)


(def-system-variable return-from-save-to-caller-for-continuation? SETS nil)

(def-system-variable kb-save-termination-reason? SETS nil)

(def-system-variable suppress-notification-for-kb-save? SETS nil)

(def-system-variable terminate-kb-save-stream-error-message? SETS nil)

(def-system-variable save-kb-state-for-system-procedure-save SETS nil)

(declare-system-procedure-function g2-save-module-extended nil)

(defun-funcallable g2-save-module-extended
    (pathname-string module-name g2-window? options)
  (when current-saving-context?
    (notify-user "Save is already in progress.")
    (return-from
      g2-save-module-extended
      (values (make-evaluation-symbol 'in-progress)
	      (make-evaluation-text-reclaiming-argument
		(copy-constant-wide-string #w"Save is already in progress.")))))

  (when current-computation-instance ;; can be nil for system-rpc
    (install-procedure-invocation-completion-form-function
      (procedure-invocation-of-code-body-function current-computation-instance)
      '(cleanup-kb-save-or-backup-if-necessary)))

  (let ((display?
	 (evaluation-boolean-is-true-p (evaluation-structure-slot options 'file-progress-display)))
	(include-required?
	 (evaluation-boolean-is-true-p (evaluation-structure-slot options 'include-required-modules)))
	(using-clear-text?
	 (evaluation-boolean-is-true-p (evaluation-structure-slot options 'using-clear-text)))
	(emitting-c-code?
	 (evaluation-boolean-is-true-p (evaluation-structure-slot options 'emitting-c-code)))
	(log-message-for-commit-after-saving?
	 (copy-if-text-string (evaluation-structure-slot options 'log-message-for-commit-after-saving))))

    (setq return-from-save-to-caller-for-continuation? t
	  kb-save-termination-reason? nil
	  suppress-notification-for-kb-save? (not display?))
    (update-terminate-kb-save-stream-error-message nil)

    (let ((file-command (make-command-frame 'file-command))
	  (attempting-save-via-system-procedure? t)
	  (g2-window-for-save-via-system-procedure?
	    (if (of-class-p g2-window? 'g2-window)
		g2-window?))
	  evaluation-error-text-string
	  (option-list
	    (slot-value-list 'including-all-required-modules include-required?
			     'using-clear-text using-clear-text?
			     'emitting-c-code emitting-c-code?
			     'commit-after-saving log-message-for-commit-after-saving?))
	  (read-only-modules? nil))


      (setf (car (box-translation-and-text file-command))
	    (slot-value-list (slot-value-list 'save-module module-name)
			     pathname-string option-list))
      (setq kb-save-termination-reason? 'failed)
      (execute-file-command file-command)
      (delete-frame file-command)

      (setq read-only-modules?
	(and current-saving-context?
	     (loop for file-progress
		       in (saving-context-kb-file-progress-displays
			    current-saving-context?)
		   thereis
		   (eq (status-of-file-progress? file-progress) 'read-only))))
      
      (when (and current-saving-context?
		 (eq (need-to-call-terminate-kb-save? current-saving-context?) t))
	(notify-user-at-console "Terminating save")
	(terminate-kb-save-or-backup
	  current-saving-context? kb-save-termination-reason?
	  (copy-text-string terminate-kb-save-stream-error-message?)))
      (when (and current-saving-context?
		 (neq (need-to-call-terminate-kb-save? current-saving-context?)
		      'never-opened))
	(setq save-kb-state-for-system-procedure-save 'continue))

      (setq evaluation-error-text-string
	    (make-evaluation-text-reclaiming-argument
	      (or terminate-kb-save-stream-error-message?
		  (copy-constant-wide-string #w""))))
      (setq terminate-kb-save-stream-error-message? nil)

      (values
	(make-evaluation-symbol
	  ;; Failure to save because a file is read-only generates only a warning,
	  ;; not a stack error.  The read-only assignment below allows the kb-side
	  ;; of g2-save-module to return a false value when a module is
	  ;; unsavable because of read-only permissions.  When there is any
	  ;; other kind of save error, it signals a stack-error; otherwise it
	  ;; returns true.  (ghw 7/23/98)
	  (or kb-save-termination-reason?
	      (and read-only-modules? 'read-only)
	      'ok))
	evaluation-error-text-string))))

(defvar g2-save-module-list nil)
(defvar g2-save-module-flag nil)

(declare-system-procedure-function set-g2-save-module-flag nil)
(defun-funcallable set-g2-save-module-flag ()
  (setq g2-save-module-flag t))

(declare-system-procedure-function reset-g2-save-module-flag nil)
(defun-funcallable reset-g2-save-module-flag ()
  (setq g2-save-module-flag nil))

(declare-system-procedure-function is-g2-save-module-flag-set nil)
(defun-funcallable is-g2-save-module-flag-set ()
  g2-save-module-flag)

;;; To save g2 module in clear text (.xml), system procedures are used in sys-mod.kb
#+ignore
(progn
(defparameter g2-save-module-clear-text-flag nil)

(declare-system-procedure-function set-g2-save-module-clear-text-flag nil)
(defun-funcallable set-g2-save-module-clear-text-flag ()
  (setq g2-save-module-clear-text-flag t))

(declare-system-procedure-function reset-g2-save-module-clear-text-flag nil)
(defun-funcallable reset-g2-save-module-clear-text-flag ()
  (setq g2-save-module-clear-text-flag nil))

(declare-system-procedure-function is-g2-save-module-clear-text-flag-set nil)
(defun-funcallable is-g2-save-module-clear-text-flag-set ()
  g2-save-module-clear-text-flag)
) ; end of progn

(declare-system-procedure-function g2-save-module nil)

(defun-funcallable g2-save-module
    (pathname-string file-progress-display? g2-window?
		     module-name include-required-modules?)
  (let ((options (allocate-evaluation-structure-inline
		  'file-progress-display file-progress-display?
		  'include-required-modules include-required-modules?)))
    (multiple-value-bind (status-symbol error-text?)
	(g2-save-module-extended pathname-string module-name g2-window? options)
      (reclaim-evaluation-value options)
      (values status-symbol error-text?))))

(defun is-empty-page (page)
  (loop for block being each subblock of page do
    (when (frame-of-class-p block 'message)
          (return-from is-empty-page nil)))
    t)

(declare-system-procedure-function g2-reclaim-save-module-memory nil)

(defun-funcallable g2-reclaim-save-module-memory ()
  (provide-current-logbook)
  (loop for id in g2-save-module-list do
      (loop for page in (stack-of-pages current-logbook?) do
          (loop for block being each subblock of page do
	      (when (and (frame-of-class-p block 'message)
			 (eql (message-serial-number? block) id))
		(delete-frame block)))))
  (loop for page in (stack-of-pages current-logbook?) do
      (when (is-empty-page page) (delete-frame page)))
      
  (reclaim-gensym-list g2-save-module-list)
  (setq g2-save-module-list nil))

(declare-system-procedure-function g2-save-kb nil)

(defun-funcallable g2-save-kb
    (pathname-string type-of-file file-progress-display? g2-window?)

  (when current-saving-context?
    (notify-user "Save is already in progress.")
    (return-from
      g2-save-kb
      (values (make-evaluation-symbol 'in-progress)
	      (make-evaluation-text-reclaiming-argument
		(copy-constant-wide-string #w"Save is already in progress.")))))

  (case type-of-file
    (save-kb (setq type-of-file 'kb-save))
    (save-kb-with-runtime-data (setq type-of-file 'kb-save-with-runtime-data))
    (t (return-from g2-save-kb
	 (values
	   (make-evaluation-symbol 'failed)
	   (make-evaluation-text-reclaiming-argument
	     (tformat-text-string
	       "The symbol ~a is not a valid argument for SAVE-KB." type-of-file))))))

  (when current-computation-instance ;; can be nil for system-rpc
    (install-procedure-invocation-completion-form-function
      (procedure-invocation-of-code-body-function current-computation-instance)
      '(cleanup-kb-save-or-backup-if-necessary)))

  (let ((display? (evaluation-boolean-is-true-p file-progress-display?)))
    (reclaim-evaluation-truth-value file-progress-display?)

    (setq return-from-save-to-caller-for-continuation? t
	  kb-save-termination-reason? nil
	  suppress-notification-for-kb-save? (not display?))
    (update-terminate-kb-save-stream-error-message nil)

    (let ((file-command (make-command-frame 'file-command))
	  (attempting-save-via-system-procedure? t)
	  (g2-window-for-save-via-system-procedure?
	    (if (of-class-p g2-window? 'g2-window)
		g2-window?))
	  evaluation-error-text-string)
      (setf (car (box-translation-and-text file-command))
	    (slot-value-list type-of-file pathname-string))
      (setq kb-save-termination-reason? 'failed)
      (execute-file-command file-command)
      (delete-frame file-command)
      (when (and current-saving-context?
		 (eq (need-to-call-terminate-kb-save? current-saving-context?) t))
	(terminate-kb-save-or-backup
	  current-saving-context? kb-save-termination-reason?
	  (copy-text-string terminate-kb-save-stream-error-message?)))
      (when (and current-saving-context?
		 (neq (need-to-call-terminate-kb-save? current-saving-context?)
		      'never-opened))
	(setq save-kb-state-for-system-procedure-save 'continue))

      (setq evaluation-error-text-string
	    (make-evaluation-text-reclaiming-argument
	      (or terminate-kb-save-stream-error-message?
		  (copy-constant-wide-string #w""))))
      (setq terminate-kb-save-stream-error-message? nil)
      (values
	(make-evaluation-symbol
	  (or kb-save-termination-reason? 'ok))
	evaluation-error-text-string))))

;; The pathname-string argument is reclaimed (as a result of
;; delete-frame).  Execute-lisp-call-stack-instruction makes copies of
;; string arguments before passing them to the system procedure lisp
;; code so it is the responsibility of this code to reclaim them.

;; Note that the pathname string doesn't go through the parser.  As can
;; be seen from the grammar for file-saving-spec in KB-LOAD1, a
;; file-name is a string or a symbol and does not get any parsing.  This
;; can be a string exactly like the one entered via a menu save.

;; Unfortunately, currently, it is always necessary for this procedure
;; to have a g2-window argument.  This is needed in order for pane
;; descriptions to be saved (save-kb calls find-or-make-saving-context
;; which makes a pane description.  The only other alternative currently
;; is to pick a g2-window at random (bad).  Ben and I (AGH) discussed
;; using saved-detail-pane-description, but this leads to failing to
;; save pane description changes since the last load.  Eventually, when
;; a save of runtime data only is implemented, it will not be necessary
;; to pass the g2-window.  Thus, a new system procedure could be
;; implemented, or, if optional args are available, the g2-window arg
;; could be made optional.  For this reason, it is at the end.

;; Consider providing an option to use/access existing pathname from
;; system table?  Should "default" be allowed to indicate using the
;; default?
       


(declare-system-procedure-function g2-continue-save-kb nil)

(defun-funcallable g2-continue-save-kb (file-progress-display?)
  (reclaim-evaluation-truth-value file-progress-display?)
  (let ((finish? t) evaluation-error-text-string)
    (when current-saving-context?
      (continue-current-kb-save-or-backup current-saving-context?)
      (when (and current-saving-context?
		 (need-to-call-terminate-kb-save? current-saving-context?))
	(terminate-kb-save-or-backup
	  current-saving-context? kb-save-termination-reason?
	  (copy-text-string terminate-kb-save-stream-error-message?)))
      (setq finish? 
	    (or kb-save-termination-reason?
		(null current-saving-context?)
		(not (not-ready-to-finish-kb-save current-saving-context?))))
      (setq save-kb-state-for-system-procedure-save
	    (if finish? 'finish 'continue)))

    (setq evaluation-error-text-string
	  (make-evaluation-text-reclaiming-argument
	    (or terminate-kb-save-stream-error-message?
		(copy-constant-wide-string #w""))))
    (setq terminate-kb-save-stream-error-message? nil)
    (values
      (make-evaluation-symbol
	(cond
	  (kb-save-termination-reason? kb-save-termination-reason?)
	  (finish? 'finished)
	  (t 'continue)))
      evaluation-error-text-string)))



(declare-system-procedure-function g2-finish-save-kb nil)

(defun-funcallable g2-finish-save-kb (file-progress-display?)
  (reclaim-evaluation-truth-value file-progress-display?)
  (let (evaluation-error-text-string)
    (when current-saving-context?
      (finish-current-kb-save-or-backup current-saving-context?)
      (when (and current-saving-context?
		 (need-to-call-terminate-kb-save? current-saving-context?))
	(terminate-kb-save-or-backup
	  current-saving-context? kb-save-termination-reason?
	  (copy-text-string terminate-kb-save-stream-error-message?)))
      (setq save-kb-state-for-system-procedure-save nil))
    (setq evaluation-error-text-string
	  (make-evaluation-text-reclaiming-argument
	    (or terminate-kb-save-stream-error-message?
		(copy-constant-wide-string #w""))))
    (setq terminate-kb-save-stream-error-message? nil)
    (values
      (make-evaluation-symbol
	(or kb-save-termination-reason? 'ok))
      evaluation-error-text-string)))







;;; System procedures that save without other processing (as though paused):

(defmacro call-save-function-without-other-processing ((function-name-symbol) &rest args)
  (let ((v1 (gensym)) (v2 (gensym)))
    `(multiple-value-bind (,v1 ,v2)
	 (,function-name-symbol . ,args)
       (cond
	 ((not (eq ,v1 'ok))
	  (values ,v1 ,v2))
	 (t
	  (system-pause)
	  (multiple-value-setq (,v1 ,v2)
	    (g2-continue-save-kb evaluation-true-value))
	  (system-resume)
	  (cond
	    ((eq ,v1 'finished)
	     (g2-finish-save-kb evaluation-true-value))
	    (t
	     (values ,v1 ,v2))))))))


(declare-system-procedure-function g2-save-kb-without-other-processing nil)

(defun-funcallable g2-save-kb-without-other-processing
    (pathname-string type-of-file file-progress-display? g2-window?)
  (call-save-function-without-other-processing
    (g2-save-kb)
    pathname-string type-of-file file-progress-display? g2-window?))


(declare-system-procedure-function g2-save-module-extended-without-other-processing nil)

(defun-funcallable g2-save-module-extended-without-other-processing
    (pathname-string module-name g2-window? options)
  (call-save-function-without-other-processing
    (g2-save-module-extended)
    pathname-string module-name g2-window? options))

(declare-system-procedure-function g2-save-module-without-other-processing nil)

(defun-funcallable g2-save-module-without-other-processing
    (pathname-string file-progress-display? g2-window?
		     module-name include-required-modules?)
  (call-save-function-without-other-processing
    (g2-save-module)
    pathname-string file-progress-display? g2-window?
    module-name include-required-modules?))






;;;; G2 System Procedures for Modules and for Loading/Merging




;;; `With-lisp-booleans-for-truth-values*' ... Each value in bindings should be
;;; a "raw" truth value value, i.e., an integer in the range [falsity .. truth],
;;; i.e., [-1000..1000].

(defmacro with-lisp-booleans-for-truth-values* (bindings &body body)
  `(let* ,(loop for (variable value) in bindings
		collect `(,variable
			    (=f ,value truth)))	; should be a primitive for this.
     . ,body))




;;; `G2-delete-module' ...

(defun-for-system-procedure g2-delete-module
    ((module symbol)
     (also-delete-associated-workspaces?-boolean truth-value))
  (declare (values)
	   (keeps-g2-local-variables-valid nil))
  (let* ((deleting-associated-workspaces?
	   (with-lisp-booleans-for-truth-values*
	       ((also-delete-associated-workspaces?
		  also-delete-associated-workspaces?-boolean))
	     also-delete-associated-workspaces?)))
    (when (and (eq module 'uilroot) deleting-associated-workspaces?)
      (stack-error
	cached-top-of-stack
	"The system procedure g2-delete-module cannot be called with ~
         the module set to UILROOT and delete-associated-workspaces? ~
         set to TRUE because g2-delete-module will also be deleted. ~
         The call should be successful when delete-associated-workspaces? ~
         is set to FALSE."))

    (let ((procedure-of-invocation?
	    (find-procedure-invocation-in-module 
	      current-computation-instance module)))
      (when (and
	      deleting-associated-workspaces?
	      current-computation-instance
	      (code-body-invocation? current-computation-instance)
              procedure-of-invocation?	      
	      (eq module
		  (module-this-is-part-of?
		    (superblock?
		      procedure-of-invocation?))))
	(stack-error
	  cached-top-of-stack
	  "The system procedure g2-delete-module cannot be called to delete a module which contains the calling procedure.")))

    (let* ((g2-delete-module-procedure
	     (get-instance-with-name-if-any 'procedure 'g2-delete-module))
	   (procedure-on-calling-stack-to-be-deleted?
	     (find-calling-procedure-invocation-in-module g2-delete-module-procedure module)))
      (when procedure-on-calling-stack-to-be-deleted?
	(if (eq procedure-on-calling-stack-to-be-deleted?
		g2-delete-module-procedure)
	    (stack-error
	      cached-top-of-stack
	      "The system procedure g2-delete-module cannot be called with ~
               the module set to ~A and delete-associated-workspaces? ~
               set to TRUE because g2-delete-module will also be deleted. ~
               The call should be successful when delete-associated-workspaces? ~
               is set to FALSE." module)
	    (stack-error
	      cached-top-of-stack
	      "Cannot call g2-delete-module to delete module ~a with ~
               delete-associated-workspaces? set to TRUE because ~
               a procedure in the calling chain, ~a, is in ~a. ~
               The call should be successful when ~
               delete-associated-workspaces? is set to FALSE."
	      module procedure-on-calling-stack-to-be-deleted? module))))
    (do-deletion-of-module-after-confirmation
	module deleting-associated-workspaces?)))



;;; `G2-create-module' either creates a module whose name is given by the
;;; argument, module, or signals an error and reporting the reason for the
;;; failure.  This returns no values.
;;;
;;; This is being added at this time to the sources for 5.0, along with one
;;; other function in parallel, create-new-module.  Both are considered likely
;;; additions to a revision of 4.0, if such a revision is to happen.  This also
;;; requires a change in sysmod/system-procedures, giving access to the
;;; function.  (MHD 8/6/96)

(declare-system-procedure-function g2-create-module
				   nil) ; seen note

;; Note: I'm not 100 % certain that this invalidates the environment, but I
;; assume there's no reason to care unless optimal speed of calling overhead is
;; an issue, which it certainly couldn't be for this kind of a function. (MHD
;; 8/6/96)


(defun-for-system-procedure g2-create-module
    ((module symbol))
  (declare (values)
	   (keeps-g2-local-variables-valid nil))
  (let ((result (create-new-module module)))
    (cond
      ((symbolp result)
       (stack-error
	 cached-top-of-stack
	 "Creation of module with name ~a failed; ~a"
	 module
	 (case result
	   #+pre-g2-v5-licensing
	   (runtime-system
	    "you cannot create a module in a runtime system.")
	   #+pre-g2-v5-licensing
	   (embedded-system
	    "you cannot create a module in an embedded system.")
	   (module-name-in-use
	    "the name is already in use.")
	   (module-name-is-reserved-word
	    "the name is a reserved word.")
	   (module-name-unspecified
	    "a module's name cannot be unspecified unless it's the top-level module")
	   (t
	    ;; module-creation-failed-for-unknown-reason
	    "reason unknown."))))
      (t
       #+development
       (test-assertion
	 (frame-of-class-p result 'module-information))
       nil))))				; don't return any values

(defun-for-system-procedure g2-modules-with-unsaved-changes ()
  (declare (values sequence)
	   (keeps-g2-local-variables-valid t))
  (allocate-evaluation-sequence
    (let ((list (modules-with-unsaved-changes)))
      (prog1 (copy-list-using-eval-conses list)
	(reclaim-gensym-list list)))))





;;; The functions G2-load-kb, g2-merge-kb, and g2-warmboot-kb all return truth
;;; or falsity depending on the result of doing a probe-file on the pathname
;;; string supplied.  However, in all but the merge-without-clear-kb case, the
;;; truth case is never seen because the KB is cleared and the calling procedure
;;; stack is effectively aborted.  Further specifics appear below.

;;; `G2-load-kb' changes the environment radically.  It pauses the KB, just to
;;; get G2 into the state in which "loading" is legal, i.e., in which the
;;; Load-KB menu choice is offered.  It then tries to load the desired KB, which
;;; will actually do clear-kb and reset, as long as it finds a KB to begin
;;; loading.  If it doesn't actually change the KB, this function returns
;;; resumes, and then returns the result, as a boolean value: false for failure;
;;; true for success is not returned.  If it succeeds, it aborts because it's in
;;; a different KB and the calling procedure can no longer be active.  So, this
;;; actually either aborts or returns false.
;;;
;;; This will create a loading schedule and merge required modules as necessary.

(defun-for-system-procedure g2-load-kb-extended
    ((pathname-string text)
     (options structure))
  (declare (values truth-value)
	   (keeps-g2-local-variables-valid nil))
    (let ((auto-merge-case?
	   (evaluation-boolean-is-true-p (evaluation-structure-slot options 'resolve-conflicts-automatically)))
	  (reformat-as-appropriate?
	   (evaluation-boolean-is-true-p (evaluation-structure-slot options 'bring-formats-up-to-date)))
	  (update-before-loading?
	   (evaluation-boolean-is-true-p (evaluation-structure-slot options 'update-before-loading))))
    (start-read-kb-for-system-procedure
      pathname-string
      t t
      reformat-as-appropriate? auto-merge-case? nil
      update-before-loading?)))

(defun-for-system-procedure g2-load-kb
    ((pathname-string text)
     (auto-merge-case?-truth-value truth-value)	; resolve-conflicts-automatically
     (reformat-as-appropriate?-truth-value truth-value)) ; bring-formats-up-to-date
  (declare (values truth-value)
	   (keeps-g2-local-variables-valid nil))
  (with-lisp-booleans-for-truth-values*
      ((auto-merge-case? auto-merge-case?-truth-value)
       (reformat-as-appropriate? reformat-as-appropriate?-truth-value))
    (start-read-kb-for-system-procedure
      pathname-string
      t t
      reformat-as-appropriate? auto-merge-case? nil
      nil
      )))

;; Could be improved by supporting restart after loading, or being able to
;; suppress restart after loading!

;; Review abort handling with Jim -- want this to be like the clear-kb
;; or reset action semantically! (MHD 8/17/94)

;; Talk to Jim about obviating the need for this with some work in
;; defun-for-system-procedure.  This is an annoying macro to have to write as
;; well as use, but better than having explicit code in system procedures!
;; (MHD 2/4/95)



(def-type-parameter merge-kb-ex-options-type
    (structure ((resolve-conflicts-automatically truth-value)
		(bring-formats-up-to-date truth-value)
		(merge-kb truth-value)
		(install-system-tables truth-value)
		(file-progress-display truth-value)
		(restore-workspaces truth-value)
		(post-logbook-messages truth-value)
		(show-conflicts truth-value)
		(disable-ui-during-load truth-value))))

(defun get-ev-bool (ev-structure name &optional default)
  (evaluation-boolean-is-true-p
    (evaluation-structure-slot ev-structure name
			       (if default evaluation-true-value evaluation-false-value))))

;;; The function `g2-merge-kb-ex' is a lot like g2-merge-kb-extended, but is
;;; documented and exposed directly to users. Four options have been added, and
;;; update-before-loading? has been removed, since it seems to be unused (or,
;;; used only by SCC).

(defun-allowing-unwind-for-system-procedure g2-merge-kb-ex
    ((pathname-string text)
     (options structure))
  (declare (values truth-value)
	   (keeps-g2-local-variables-valid nil))
  (check-type-or-stack-error options merge-kb-ex-options-type)
  (let ((auto-merge-case?
	  (get-ev-bool options 'resolve-conflicts-automatically t))
	(reformat-as-appropriate?
	  (get-ev-bool options 'bring-formats-up-to-date))
	(clear-kb?
	  (not (get-ev-bool options 'merge-kb t)))
	(install-system-tables?
	  (get-ev-bool options 'install-system-tables))
	(do-not-update-file-progress-display?
	    (not (get-ev-bool options 'file-progress-display t)))
	(do-not-restore-image-planes?
	    (not (get-ev-bool options 'restore-workspaces t)))
	(do-not-notify-user-during-kb-load?
	    (not (get-ev-bool options 'post-logbook-messages t)))
	(do-not-show-conflicts-during-kb-load?
	    (not (get-ev-bool options 'show-conflicts t)))
	(do-not-allow-user-interactions-during-kb-load?
	    (get-ev-bool options 'disable-ui-during-load t)))
    (start-read-kb-for-system-procedure
      pathname-string
      clear-kb?
      install-system-tables?
      reformat-as-appropriate? auto-merge-case? nil
      nil)))


;;; `G2-merge-kb' is just the same as g2-load-kb, but gives the choice as
;;; additional arguments as to whether the KB should first be cleared and
;;; whether system tables of the final module should be installed.  (These
;;; choices always true in the load case.)  This also differs in that it may
;;; either true or false.  Note that it may still do an abort (non-local exit,
;;; non-returning) in the case where it does a clear kb prior to merging.

(defun-for-system-procedure g2-merge-kb-extended
    ((pathname-string text)
     (options structure))
  (declare (values truth-value)
	   (keeps-g2-local-variables-valid nil))
    (let ((auto-merge-case?
	   (evaluation-boolean-is-true-p (evaluation-structure-slot options 'resolve-conflicts-automatically)))
	  (reformat-as-appropriate?
	   (evaluation-boolean-is-true-p (evaluation-structure-slot options 'bring-formats-up-to-date)))
	  (clear-kb?
	   (not (evaluation-boolean-is-true-p (evaluation-structure-slot options 'merge-kb))))
	  (install-system-tables?
	   (evaluation-boolean-is-true-p (evaluation-structure-slot options 'install-system-tables)))
	  (update-before-loading?
	   (evaluation-boolean-is-true-p (evaluation-structure-slot options 'update-before-loading))))	   
    (start-read-kb-for-system-procedure
      pathname-string
      clear-kb?
      install-system-tables?
      reformat-as-appropriate? auto-merge-case? nil
      update-before-loading?)))

(defun-for-system-procedure g2-merge-kb
    ((pathname-string text)
     (auto-merge-case?-truth-value truth-value)	; resolve-conflicts-automatically
     (reformat-as-appropriate?-truth-value truth-value) ; bring-formats-up-to-date
     (clear-kb?-truth-value truth-value)
     (install-system-tables?-truth-value truth-value))
  (declare (values truth-value)
	   (keeps-g2-local-variables-valid nil))
  (with-lisp-booleans-for-truth-values*
      ((auto-merge-case? auto-merge-case?-truth-value)
       (reformat-as-appropriate? reformat-as-appropriate?-truth-value)
       (clear-kb? clear-kb?-truth-value)
       (install-system-tables? install-system-tables?-truth-value))
    (start-read-kb-for-system-procedure
      pathname-string
      clear-kb?
      install-system-tables?
      reformat-as-appropriate? auto-merge-case? nil nil)))

(defun-for-system-procedure g2-warmboot-kb
    ((pathname-string text) (catch-up?-truth-value truth-value))
  (declare (values truth-value)
	   (keeps-g2-local-variables-valid nil))
  (with-lisp-booleans-for-truth-values*
      ((catch-up? catch-up?-truth-value))
    (start-read-kb-for-system-procedure
      pathname-string
      t t
      nil
      nil
      (if catch-up?
	  'WARMBOOT-AFTERWARDS-WITH-CATCH-UP
	  'WARMBOOT-AFTERWARDS)
      nil)))

(defun-for-system-procedure g2-load-runtime-data ; GENSYMCID-1258 (BCDR)
    ((pathname-string text) (option structure))
  (declare (values truth-value)
	   (keeps-g2-local-variables-valid nil))
  option
  (start-read-kb-for-system-procedure
    pathname-string
    t t ; clear-kb? install-system-tables?
    nil
    nil
    'WARMBOOT-AFTERWARDS
    nil))

;;; `Start-read-kb-for-system-procedure' .... handles three basic cases:
;;;
;;;    (1) warmbooting, i.e., clearing, loading a snapshot, and starting to run;
;;;    (2) loading, i.e., clearing and loading a KB; and
;;;    (3) merging, i.e., merging KBs on top of the current on without clearing
;;;
;;; In cases (1) and (2) the system is paused, and will be effectively reset
;;; upon clearing. In case (3) the system is paused, and then after merging, is
;;; resumed.
;;;
;;; In all cases it returns false immediately if there is no file corresponding
;;; to pathname-string.  In cases (1) and (2) it returns immediatly with truth
;;; but after calling system-pause; this has the effect on the stack evaluator
;;; of not letting the calling stack ever see this result; i.e., an immediate
;;; abort of the stack takes place.
;;;
;;; In case (3), where the pathname exists, the result of attempting the merge
;;; is returned, i.e., truth or falsity.  Since a file corresponding to the KB
;;; or at least its top-level module is now known to exist, this should usually
;;; return true; however, in some cases, e.g., when required modules cannot be
;;; found, it returns false as well.  Before it is called, a system-pause is
;;; performed, but after it completes, a system-resume is performed.
;;;
;;; Note that when warmboot-case? is true, the preceeding args other than
;;; pathname-string are ignored; in particular, note that warmboot-case? always
;;; implies clear-kb?, effectively overriding its value.
;;;
;;; What-to-do-after-loading-kb? is as documented for read-kb-or-group-thereof,
;;; q.v. in KB-MERGE.

(defun-allowing-unwind start-read-kb-for-system-procedure
    (pathname-string
      clear-kb? install-system-tables?
      bring-formats-up-to-date? resolve-conflicts-automatically?
      what-to-do-after-loading-kb?
      update-before-loading?)
  (let* ((truename? (probe-for-kb-named-by-text-string pathname-string))
	 (client? (get-current-workstation-or-ui-client-interface-if-any)))
    (cond
      (truename?
       (cond
	 (clear-kb?
	  ;; Note: the body of the next form is just going to get scheduled;
	  ;; therefore, the following form after that, call to system-pause,
	  ;; actually runs before the call to sys-proc-read-kb.
	  (with-immediate-scheduling (nil)
	    (sys-proc-read-kb
	      truename?
	      (gensym-list
		clear-kb? install-system-tables?
		bring-formats-up-to-date? resolve-conflicts-automatically?
		what-to-do-after-loading-kb?
		update-before-loading?
		client?
		do-not-update-file-progress-display?	 ; Capture some specvars
		do-not-restore-image-planes?
		do-not-notify-user-during-kb-load?
		do-not-show-conflicts-during-kb-load?
		do-not-allow-user-interactions-during-kb-load?)))
	  (system-pause)
	  truth)
	 (t
	  (system-pause)
	  (let ((kb-serial-number current-kb-serial-number))
	    (prog1 (if (read-kb-or-group-thereof
			 truename?    
			 clear-kb? install-system-tables?
			 bring-formats-up-to-date? resolve-conflicts-automatically?
			 what-to-do-after-loading-kb?
			 update-before-loading?
			 client?)
		       truth
		       falsity)
	      (reclaim-gensym-pathname truename?)
	      (unless (>f current-kb-serial-number kb-serial-number) ; for safety; nec?! 
		(system-resume)))))))
      (t falsity))))

;; The probe-file test is incomplete! It should be improved by having it do as
;; complete a job as read-kb-or-group-thereof or warmboot-kb will eventually do.
;; I.e., merging of the pathname with the (global) defaults, and checking of all
;; required modules.  Do this by abstracting that code out.  We can live with
;; this for now.  (MHD 5/20/95)


(defun-simple sys-proc-read-kb
    (gensym-pathname gensym-list-of-read-kb-args)
  (gensym-dstruct-bind
      ((clear-kb? install-system-tables?
		  bring-formats-up-to-date? resolve-conflicts-automatically?
		  what-to-do-after-loading-kb?
		  update-before-loading?
		  client?
		  do-not-update-file-progress-display?   ; Special
		  do-not-restore-image-planes?           ; Special
		  do-not-notify-user-during-kb-load?	 ; Special
		  do-not-show-conflicts-during-kb-load?	 ; Special
		  do-not-allow-user-interactions-during-kb-load?) ; Special
       gensym-list-of-read-kb-args)
    (prog1 (read-kb-or-group-thereof
	     gensym-pathname    
	     clear-kb? install-system-tables?
	     bring-formats-up-to-date? resolve-conflicts-automatically?
	     what-to-do-after-loading-kb?
	     update-before-loading?
	     client?)
      (reclaim-gensym-pathname gensym-pathname)
      (reclaim-gensym-list gensym-list-of-read-kb-args))))

;; Number of args limited to be funcallable in scheduler.

;; Error case?  Logbook message?  Resume-kb?  Who knows.  -jra 4/19/95








;;;; System Procedure to Get Connection Vertices




;; Moved here from CONNECT5 because of the use evaluation-value macros defined
;; above.


(declare-forward-reference check-args-for-connection-evaluator function)
(declare-forward-reference clear-g2-list function)
(declare-forward-reference get-connection-vertices-backward-compatibility-p function)



;;; `g2-get-connection-vertices' is the lisp function for the system procedure
;;; g2-get-connection-vertices.  The vertices are put into the integer-list arg.
;;; The vertices are computed based on direction away from the object.  The
;;; integers are thus consistent with the integers passed in via the "vertices"
;;; option when creating transient connections.


;;; The original 3.0 implementation of this system procedure was 
;;; consistent but produces too many vertices for being passed to the create
;;; connection action.

;;; In 4.0 the behavior of this procedure was split - into a backwards
;;; compatable behavior (`g2-connection-vertices') and a new behavior
;;; (`g2-get-connection-vertices-accurately').  The intention of the
;;; new behavior was to make it easier to interface with the create connection
;;; procedure.

;;; Bugs found in 4.0:
;;; - The backwards compatability feature was not backwards compatable. It
;;; failed to adjust the order and the signs of the vertices with respect to
;;; the item argument.

;;; In 5.0  the original 3.0 behavior is restored for the backwards
;;; compatability feature.


(declare-system-procedure-function g2-get-connection-vertices t)

(defun-funcallable g2-get-connection-vertices (item connection integer-list)  
  (check-args-for-get-connection-vertices item connection cached-top-of-stack)
  (cond ((get-connection-vertices-backward-compatibility-p)
	 (get-connection-vertices-original item connection integer-list))
	(t
	 (get-connection-vertices-accurately connection integer-list))))


;;; `get-connection-vertices-original' is the original 3.0 implementation, which is
;;; now supported by the backwards compatability feature.

;;; The 3.0 implementation adheres to the following spec:
;;; - All vertices are returned;
;;; - Vertices start from the item specified;
;;; - The sign of vertices are determined:
;;;    east is negative
;;;    west is positive
;;;    north is positive
;;;    south is negative
;;; - Directionality of connection is irrelevant to the results
;;;   (although directionality is not irrelevant to the calculation of
;;;    the result because of the way that connection vertices are stored).
;;; - Spurious 0, 0 vertices at the end of the vertices list are never
;;;   returned to the user.

(defun get-connection-vertices-original (item connection integer-list)
  (let* ((connection-structure 
	   (connection-for-this-connection-frame connection))
	 (dont-include-offset-for-end-position? t)
	 (connection-deltas
	   (add-missing-deltas-to-connection connection-structure))
	 (from-output-item? (eq (output-end-object-internal connection-structure)
				item)))
    (put-connection-deltas-into-integer-list
      connection-structure connection-deltas integer-list from-output-item?)
    (remove-redundant-deltas-from-connection connection-structure)
    nil))


;;; The new implementation of `g2-get-connection-vertices-accurately' adheres to
;;; a more complicated spec, one which is entirely consistent with the create
;;; connection action.  

(defun get-connection-vertices-accurately (connection integer-list)
  (let* ((connection-structure 
	   (connection-for-this-connection-frame connection))
	 (connection-deltas (delta-or-deltas-internal connection-structure))
	 (deltas-added? nil))
    (cond ((and (null connection-deltas)
		;; we're relying on the fact that the item is connected to the
		;; other end -rdf, 6/8/95
		(or (loose-end-p (output-end-object-internal connection-structure))
		    (loose-end-p (input-end-object-internal connection-structure))))
	   (add-missing-deltas-to-connection connection-structure)
	   (setq deltas-added? t))
	  ((and (not (null connection-deltas))
		(not (consp connection-deltas)))
	   (add-missing-deltas-to-connection connection-structure)
	   (remove-last-delta-from-connection connection-structure)
	   (setq deltas-added? t)))
    (setq connection-deltas (delta-or-deltas-internal connection-structure))
    (setq integer-list (put-connection-deltas-into-integer-list
			 connection-structure connection-deltas integer-list nil))
    (when deltas-added?
      (remove-last-delta-from-connection connection-structure)))
  (when (listp integer-list)
    integer-list))

(defun put-connection-deltas-into-integer-list 
    (connection connection-deltas integer-list starting-at-output?)
  (unless (listp integer-list)
    (clear-g2-list integer-list))
  (when connection-deltas
    (let ((reclaim-deltas-on-exit? nil))
      (unless (consp connection-deltas)
	(setq connection-deltas (slot-value-list connection-deltas))
	(setq reclaim-deltas-on-exit? t))
      (with-connection 
	  connection t t nil nil
	input-end-x-position
	input-end-y-position
	output-end-x-position
	output-end-y-position
	;; essentially the list must be reversed with a sign swap
	(if starting-at-output?
	    (loop for delta in connection-deltas
		  for item-count from 1
		  with delta-count = (length connection-deltas)
		  with delta-count-minus-1 = (-f delta-count 1)
		  with value-to-insert
		  with omit-last-two-values? =
		  (when (> delta-count 1)
		    (loop for a-delta in connection-deltas
			  for count from 1
			  with last-value and next-to-last-value
			  do
		      (cond ((=f count delta-count-minus-1)
			     (setq next-to-last-value a-delta))
			    ((=f count delta-count)
			     (setq last-value a-delta)))
			  finally
			    (return
			      (and (=f next-to-last-value 0)
				   (=f last-value 0)))))
		  as direction-multiplier
		     = (if (initial-orientation-horizontal-p input-end-side)
			   1 -1)
		     then (*f direction-multiplier -1) do
	      (unless
		  (and omit-last-two-values?
		       (or (=f item-count delta-count-minus-1)
			   (=f item-count delta-count)))
		(setq value-to-insert (*w (-w delta) direction-multiplier))
		(if (listp integer-list)
		    (eval-push value-to-insert integer-list)
		    (g2-list-insert-at-beginning
		      value-to-insert
		      integer-list))))
	    (loop for delta in connection-deltas
		  for item-count from 1
		  with delta-count = (length connection-deltas)
		  with delta-count-minus-1 = (-f delta-count 1)
		  with omit-last-two-values? =
		  (when (> delta-count 1)
		    (loop for a-delta in connection-deltas
			  for count from 1
			  with last-value and next-to-last-value
			  do
		      (cond ((=f count delta-count-minus-1)
			     (setq next-to-last-value a-delta))
			    ((=f count delta-count)
			     (setq last-value a-delta)))
			  finally
			    (return
			      (and (=f next-to-last-value 0)
				   (=f last-value 0)))))
		  as direction-multiplier
		     = (if (initial-orientation-horizontal-p input-end-side)
			   1 -1)
		     then (*f direction-multiplier -1) do
	      (unless
		  (and omit-last-two-values?
		       (or (=f item-count delta-count-minus-1)
			   (=f item-count delta-count)))
		(let ((last-value (*w delta direction-multiplier)))
		  (if (listp integer-list)
		      (setq integer-list (nconc integer-list (eval-list last-value)))
		      (g2-list-insert-at-end last-value integer-list)))))))
      (when reclaim-deltas-on-exit?
	(reclaim-slot-value-list connection-deltas))))
  integer-list)




(defun check-args-for-get-connection-vertices (item connection top-of-stack)
  (check-args-for-connection-evaluator 
    item connection "GET-CONNECTION-VERTICES" top-of-stack))

;; Checks to make sure that item, connection, and integer-list are of these types
;; are done in system procedure in G2 itself.






;;;; System Procedure To Get Items Connected To A Port




;; Moved here from CONNECT5 because of the use evaluation-value and stack-error
;; macros defined above.



;;; `G2-get-items-connected-to-port' is the lisp function for the system
;;; procedure g2-get-items-connected-to-port.  This procedure references any
;;; instances of a class connected to a given item at the specified port.  If
;;; any instances are found they are added to the end of the item-list that is
;;; passed as an argument to this procedure.  This procedure is useful because
;;; the port name is given by an expression that is evaluated at runtime.

;;; Note that the argument ordering is consistent with the g2-get-connection-
;;; vertices system procedure.  G2-get-items-connected-to-port differs in that
;;; it adds items to the end of the list without clearing it first.  Handling
;;; the item-list in this way is consistent with the insert-indexed-attribute-
;;; items-in-list system procedure.

;;; This function does not test the type of its arguments because the system
;;; procedure already does that.  Note that the non-items arguments to this
;;; function are evaluation values and are reclaimed, as necessary, by this
;;; function.

;;; NON-ERRORS (similar to role-service for AT-PORT):
;;; 1. If no items are found connected to the port then no items are added to
;;; the list.
;;; 2. If the list does not allow duplicate elements and if the connected item
;;; is already present in the list, the item is not added to the list and no
;;; warning is given.
;;; 3. If the given port does not belong to the item then an error is not
;;; signaled and no items are added to the list.

;;; ERRORS (similar to role-service for AT-PORT):
;;; 1. If the connected class does not exist, an error is signaled.

;; The grammar "any <class> connected at the <port> of <item>" performs a
;; similar function, but the port name is given by a constant symbol.
;; Hopefully, we will extend the grammar to also allow evaluation of a port
;; name expression.  We are not able to do this for G2 3.0 Rev.1, so we are
;; implementing this system procedure.  It is needed by the GDA group for
;; performance reasons.  - cpm, 11/6/92

;; Note that this function does used cached-roles as does the AT-PORT
;; role-serve.

;; This function tests that items are servable.

;; In ROLES:
(declare-forward-reference search-for-directly-connected-entities function)


(declare-system-procedure-function g2-get-items-connected-to-port t)

(defun-funcallable g2-get-items-connected-to-port
    (connected-item connected-class-name port-name
		    connected-items-item-list)
  (let* ((class (evaluation-symbol-symbol connected-class-name))
	 (class-description? (class-description class))
	 (port (evaluation-symbol-symbol port-name))
	 (direction? nil))
    (cond ((or (null class-description?)
	       (not (class-description-of-class-p class-description? 'item)))
	   (stack-error
	     cached-top-of-stack
	     "Could not reference the ~a connected to ~NF at ~a.  ~a is not a ~a"
	     class connected-item port class
	     (if (subclassp class 'item)
		 "class that can have connections."
		 "defined class.")))
	  (t
	   (let ((connected-items?
		   (search-for-directly-connected-entities
		     connected-item class port nil nil nil nil nil)))
	     (loop for connected-item-at-port in connected-items?
		   do
	       (cond
		 ((and (frame-of-class-p connected-item-at-port 'connection)
		       (serve-item-p connected-item-at-port))
		  (if (eq direction? nil)
		      (cond
			((eq (output-end-object-internal
			       (connection-for-this-connection-frame
				 connected-item-at-port))
			     connected-item)
			 (setf direction? 'input))
			(t (setf direction? 'output))))
		  (g2-get-items-connected-to-port-1
		    connected-item-at-port class port direction? connected-items-item-list))

		 ((serve-item-p connected-item-at-port)
		  (g2-list-insert-at-end
		    connected-item-at-port connected-items-item-list))))
	     (when connected-items?
	       (reclaim-eval-list connected-items?)))))
    ;; Reclaim the non-item evaluation-value arguments.
    (reclaim-evaluation-symbol connected-class-name)
    (reclaim-evaluation-symbol port-name)))


(defun g2-get-items-connected-to-port-1
    (connected-item class port direction? connected-items-item-list)
  (loop with temp-list
	  = (search-for-directly-connected-entities
	      connected-item class port direction? direction?
	      nil nil nil)
	for connected-item-at-port in temp-list
	do
    (cond
      ((and
	 (frame-of-class-p connected-item-at-port 'connection)
	 (serve-item-p connected-item-at-port))
       (g2-get-items-connected-to-port-1
	 connected-item-at-port class port direction? connected-items-item-list))
      ((serve-item-p connected-item-at-port)
       (g2-list-insert-at-end
	 connected-item-at-port connected-items-item-list)))
	finally
	  (reclaim-eval-list temp-list)))



;;; The funcallable function `system-predicate' (and the system procedure of the
;;; same name) is used to implement predicate hacks for items.  We had planned
;;; in 4.0 to make available a set of predicates on items through the components
;;; projects.  These were cancelled to shorten our release schedule.  To fill
;;; the vacuum, this system procedure will be provided to internal Gensym
;;; product development groups to provide a set of such predicates.  This
;;; function will be called with an item and a symbol.  Each different symbol
;;; will implement a different predicate on the item.  This function will run
;;; the predicate and return an evaluation truth value reflecting the result.
;;; If the given symbol does not name a predicate, this function returns false
;;; (what do you expect for a Friday afternoon hack? -jra 4/1/94).  The
;;; following symbols/predicates are provided:

;;;   exposed : whether the given item is a workspace showing on any g2-window,
;;;     or is an item on a workspace showing on any g2-window
;;;   transient : whether the given item is currently transient
;;;   permanent : whether the given item is currently permanent

(declare-system-procedure-function system-predicate t)

(defun-funcallable system-predicate (item symbol)
  (if (case symbol
	((showing exposed)
	 (showing-p item nil))
	((transient)
	 (transient-p item))
	((permanent)
	 (permanent-block-p item))
	(t nil))
      (make-evaluation-truth-value truth)
      (make-evaluation-truth-value falsity)))





;;;; System Procedures to Get Information about user attributes.

;;; These procedures are for GDA only!
(defun-for-system-procedure g2-get-attributes-for-class
    (class-name array-frame specific-attributes-flag)
  (unless (classp class-name)
    (stack-error cached-top-of-stack "~a is not a valid class name." class-name))
  (let* (array-length
	  managed-array
	  (attr-info-list '())
	  (all-attributes-p
	    (not (evaluation-truth-value-is-true-p specific-attributes-flag))))
    
    (loop for attribute-name being each attribute of class-name
	  as slot-description = (slot-description-from-class class-name attribute-name)
	  as defining-class = (defining-class slot-description)
	  as attribute-type-specification = (slot-type-specification slot-description)
	  as slot-init-form = (slot-init-form slot-description)
	  do
      (when (or all-attributes-p
		(eq defining-class class-name))
	(slot-value-push attribute-name attr-info-list)
	(slot-value-push (defining-class slot-description) attr-info-list)
	
	(multiple-value-bind (attribute-type-generic attribute-type-specific empty-allowed-p)
	    (if (symbolic-type-specification-p attribute-type-specification)
		(values 'value
			(user-type-for-symbolic-type-specification attribute-type-specification)
			evaluation-false-value)
		(if (class-type-specification-p attribute-type-specification)
		    (values 'object
			    (type-specification-class attribute-type-specification)
				   evaluation-false-value)
		    (values 'item-or-value
			    'none
			    evaluation-true-value)))
	  (slot-value-push attribute-type-generic attr-info-list)
	  (slot-value-push attribute-type-specific attr-info-list)
	  (slot-value-push empty-allowed-p attr-info-list))

	(multiple-value-bind (initial-type initial-value-or-class)
	    (cond ((null slot-init-form)
		   (values 'none 'none))
		  ((symbolp slot-init-form)
		   (values 'value (copy-evaluation-symbol slot-init-form)))
		  ((slot-constantp slot-init-form)
		   (let* ((slot-value
			    (get-slot-value-number-or-string-from-slot-constant
			      slot-init-form))
			  (slot-units
			    (get-unit-from-slot-constant
			      slot-init-form)))
		     (case slot-units
		       ((number)
			(if (fixnump slot-value)
			    (values 'value (copy-evaluation-integer slot-value))
			    (values 'value (copy-evaluation-float slot-value))))
		       ((truth-value)
			(values 'value (make-evaluation-truth-value slot-value)))
		       ((text)
			(values 'value (make-evaluation-text slot-value)))
		       (otherwise
			(values slot-units
				(if (evaluation-integer-p slot-value)
				    (copy-evaluation-integer slot-value)
				    (copy-evaluation-float slot-value)))))))
		  ((evaluation-value-p slot-init-form)
		   (values 'value (copy-evaluation-value slot-init-form)))
		  ((not (eq (car slot-init-form) ':funcall))
		    (reclaim-slot-value-list attr-info-list)
		    (stack-error cached-top-of-stack "Inconsistency Found. Non-simple and non-funcalled attribute initialization in user-defined attribute slot [~a] of class ~a." attribute-name class-name))
		   (t (values 'object (caddr slot-init-form))))
	  
	  (slot-value-push initial-type attr-info-list)
	  (slot-value-push initial-value-or-class attr-info-list))
	(slot-value-push (owner-class slot-description) attr-info-list)))
    
    (setf array-length (length attr-info-list))
    (change-slot-value array-frame 'g2-array-length array-length)
    (setf managed-array (get-slot-value array-frame 'managed-g2-array))	; fwd. ref. (MHD 8/18/95)
    (loop for x in attr-info-list
	  as index from (-f array-length 1) downto 0
	  do
      (reclaim-managed-number-or-value (managed-svref managed-array index))
      (setf (managed-svref managed-array index) (slot-value-pop attr-info-list)))
    (reclaim-slot-value-list attr-info-list)))


(defun-for-system-procedure g2-get-enumerations-for-symbolic-attribute
    (class-name pretty-slot-name symbol-list)
  (unless (classp class-name)
    (stack-error cached-top-of-stack "~a is not a valid class name." class-name))
  (let* ((defining-class
	     (defining-class
		 (get-slot-description-of-class-description
		   pretty-slot-name (class-description class-name))))
	 (class-specific-attributes-of-defining-class
	   (class-specific-attributes
	     (class-definition defining-class)))
	 enumerations)
    (loop for attribute-description in class-specific-attributes-of-defining-class
	  as attribute-name = (attribute-name attribute-description)
	  until (eq attribute-name pretty-slot-name)
	  finally
	    (setf enumerations (attribute-range attribute-description)))
    (when enumerations
      (loop for allowed-symbol in enumerations
	    do
	(g2-list-insert-at-end allowed-symbol symbol-list)))))


(defun user-type-for-symbolic-type-specification (symbol)
  (case symbol
    ((number) 'quantity)
    ((datum) 'value)
    ((boolean) 'truth-value)
    (otherwise symbol)))






;;;; System Procedure for Float to Text Conversion




;;; The `g2-float-to-text-using-decimal-format function' is used to convert a
;;; float value to a text value, formatting the float as specified.

;;; Note that the formatting is similar to the "dd.ddd" format in the
;;; concatentation expression, "[F1 as dd.ddd]".  The exceptions are that the
;;; integral and fraction sizes are expressions (not constants), the float can
;;; be forced to exponent format, and that the float can be forced to have
;;; trailing zeros removed.

(declare-system-procedure-function g2-float-to-text-using-decimal-format t)
(defun g2-float-to-text-using-decimal-format
    (float-arg-as-evaluation-value
      max-integral-size-as-evaluation-value
      max-fraction-size-as-evaluation-value
      always-format-as-exponent-p-truth-value-as-evaluation-value
      suppress-trailing-zeros-p-truth-value-as-evaluation-value)
  (let* ((float-arg
	   (evaluation-float-value float-arg-as-evaluation-value))
	 (max-integral-size
	   (evaluation-integer-value max-integral-size-as-evaluation-value))
	 (max-fraction-size
	   (evaluation-integer-value max-fraction-size-as-evaluation-value))
	 (always-format-as-exponent-p-truth-value
	   (evaluation-truth-value-value always-format-as-exponent-p-truth-value-as-evaluation-value))
	 (suppress-trailing-zeros-p-truth-value
	   (evaluation-truth-value-value suppress-trailing-zeros-p-truth-value-as-evaluation-value))
	 (value-1
	   (with-lisp-booleans-for-truth-values*
	       ((always-format-as-exponent-p
		  always-format-as-exponent-p-truth-value)
		(suppress-trailing-zeros-p
		  suppress-trailing-zeros-p-truth-value))
	     (twith-output-to-text-string
	       (write-floating-point-number
		 float-arg max-integral-size max-fraction-size
		 16 suppress-trailing-zeros-p always-format-as-exponent-p
		 nil 	; don't always force small numbers to exponent
		 nil)))))    ; no fixed exponent subfield width
    (reclaim-evaluation-float float-arg-as-evaluation-value)
    (reclaim-evaluation-integer max-integral-size-as-evaluation-value)
    (reclaim-evaluation-integer max-fraction-size-as-evaluation-value)
    (reclaim-evaluation-truth-value always-format-as-exponent-p-truth-value-as-evaluation-value)
    (reclaim-evaluation-truth-value suppress-trailing-zeros-p-truth-value-as-evaluation-value)
    value-1))

;; This function, G2-float-to-text-using-decimal-format, was added in G2 4.0
;; rev.2, but it is not currently released as a (public) system-procedure.  If
;; we decide to allow users another way of formatting floats in the "ddd" style,
;; this function would be useful.  But, currently, we are going toward a "C
;; printf" type format.  (See g2-float-to-text, below.)  -cpm, 1/8/96



;;; The `g2-float-to-text system-procedure' is used to convert a float value to
;;; a text value, using a simple version of "C" formatting.

;;; This function uses a precision and format-type (float, exponent, or best,
;;; which are equivalent to f,e, and g in "C").

(declare-system-procedure-function g2-float-to-text t)

(defun g2-float-to-text
   (float-arg-as-evaluation-value
     minimum-width-as-evaluation-value
     precision-as-evaluation-value output-format-as-evaluation-value
     suppress-trailing-zeros-p-truth-value-as-evaluation-value)
 (let* ((float-arg
	   (evaluation-float-value float-arg-as-evaluation-value))
	 (minimum-width
	   (evaluation-integer-value minimum-width-as-evaluation-value))
	 (precision
	   (evaluation-integer-value precision-as-evaluation-value))
	 (output-format
	   (evaluation-symbol-symbol output-format-as-evaluation-value))
	 (suppress-trailing-zeros-p-truth-value
	   (evaluation-truth-value-value suppress-trailing-zeros-p-truth-value-as-evaluation-value))
	 (value-1
	   (with-lisp-booleans-for-truth-values*
	       ((suppress-trailing-zeros-p
		  suppress-trailing-zeros-p-truth-value))
	     (twith-output-to-text-string
	       (write-floating-point-number-simple-c-format
		 float-arg
		 precision
		 output-format
		 minimum-width
		 suppress-trailing-zeros-p)))))
   (reclaim-evaluation-float float-arg-as-evaluation-value)
   (reclaim-evaluation-integer minimum-width-as-evaluation-value)
   (reclaim-evaluation-integer precision-as-evaluation-value)
   (reclaim-evaluation-symbol output-format-as-evaluation-value)
   (reclaim-evaluation-truth-value suppress-trailing-zeros-p-truth-value-as-evaluation-value)
   value-1))

;; G2-float-to-text was added in G2 4.0 rev.2.  - cpm, 1/3/96

;; We should consider adding another version of g2-float-to-text, perhaps called
;; g2-float-to-text-with-format, that makes use of other printf features
;; (minimum width, left justification, padding character, etc.)  - cpm, 1/3/96

;; Add to the above a MEMQ check of the output-format.  It should be one of
;; float, exponent, or best.  Currently, this test is done in the system
;; procedure.  Note that if a stack-error is signalled the arguments need to be
;; reclaimed.  - cpm, 1/9/96






(defun-for-system-procedure g2-run-trace
    ((text-arg text))
  (declare (values truth-value)
	   (keeps-g2-local-variables-valid t))
  (if (run-trace text-arg)
      truth
      falsity))


(declare-system-procedure-function g2-start-tracking-items t)
(declare-system-procedure-function g2-stop-tracking-items t)
(declare-system-procedure-function g2-clear-tracked-items t)

(defvar tracked-items-call-depth 0)
(defvar tracking-items-p nil)

(def-hash-table tracked-items-call-vector-table
    :hash-function-or-macro frame-hash-function
    :entry-reclaimer reclaim-if-evaluation-value-function)

(defvar tracked-items-call-vector-table nil)

(defun-void note-tracked-item-creation (item)
  (when (<f 0 tracked-items-call-depth)
    (unless tracked-items-call-vector-table
      (setq tracked-items-call-vector-table (make-tracked-items-call-vector-table)))
    (when (and *current-computation-frame* current-computation-instance cached-stack-frame-base)
      (setf (get-tracked-items-call-vector-table item tracked-items-call-vector-table)
	    (get-call-sequence
	      tracked-items-call-depth
	      *current-computation-frame* current-computation-instance cached-stack-frame-base)))))

(defun-void note-possibly-tracked-item-deletion (item)
  (when tracked-items-call-vector-table
    (delete-tracked-items-call-vector-table item tracked-items-call-vector-table)))

(defun-for-system-procedure g2-get-tracked-item-call-sequence
    ((item item))
  (declare (values sequence)
	   (keeps-g2-local-variables-valid t))
  (or (when tracked-items-call-vector-table
	(copy-if-evaluation-value
	  (get-tracked-items-call-vector-table item tracked-items-call-vector-table)))
      (allocate-evaluation-sequence nil)))

(defun-for-system-procedure g2-get-tracked-items-call-depth
    ()
  (declare (values integer)
	   (keeps-g2-local-variables-valid t))
  tracked-items-call-depth)

(defun-for-system-procedure g2-set-tracked-items-call-depth
    ((max-depth integer))
  (declare (values integer)
	   (keeps-g2-local-variables-valid t))
  (when (and (<=f 0 max-depth)
	     (<= max-depth 100))
    (setq tracked-items-call-depth max-depth))
  tracked-items-call-depth)

(defun-funcallable g2-start-tracking-items ()
  (setq tracking-items-p t)
  (loop for item being each class-instance of 'item
	do (set-tracking-item-mark item))
  nil)

(defvar tracking-items-grammar-installed-p nil)

(defun-funcallable g2-stop-tracking-items ()
  (setq tracking-items-p nil)
  (unless tracking-items-grammar-installed-p
    (setq tracking-items-grammar-installed-p t)
    (with-permanent-gensym-float-creation
      (add-grammar-rules
	'((query-restriction ('in 'the 'tracked 'item 'set)
	   (in-the-tracked-item-set :argument-1))))))
  (loop for item being each class-instance of 'item
	unless (tracking-item-mark-p item)
	  do (set-tracking-item-mark item)
	     (set-tracking-item-in-set item))
  nil)

(defun-funcallable g2-clear-tracked-items ()
  (loop for item being each class-instance of 'item
	do (clear-tracking-item-mark item)
	   (clear-tracking-item-in-set item))
  (when tracked-items-call-vector-table
    (clear-tracked-items-call-vector-table tracked-items-call-vector-table))
  nil)





;;;; System Procedure for Text to Symbol Conversion Check.




;;; The `g2-text-to-symbol-test system-procedure' returns true if the given text
;;; value can be converted to a symbol in G2.  Note that similar to the SYMBOL
;;; G2 function, this procedure checks if the text begins with a symbol and
;;; follows the format for G2 symbols.

(defun-for-system-procedure g2-text-to-symbol-test
    ((text-arg text))
  (declare (values truth-value)
	   (keeps-g2-local-variables-valid t))
  (if (read-symbol-from-text-string text-arg)
      truth
      falsity))

;; G2-text-to-symbol-test was added in G2 4.0 rev.2.  - cpm, 10/29/95

;;




(declare-system-procedure-function g2-list-of-user-visible-attributes t)

(defun-funcallable g2-list-of-user-visible-attributes (class-name)
  (let* ((new-g2-list-class
	  (g2-list-or-array-class-for-element-type 'symbol nil))
	(g2-list (make-transient-item new-g2-list-class)))

    (loop with class-description = (class-description class-name)
	  with slot-descriptions = (slot-descriptions class-description)
	  as slot-description in slot-descriptions
	  as slot-name = (pretty-slot-name slot-description)
	  as defining-class-var? ; get this faster?!
	     = (unless (eq slot-name 'class)
		 (when (slot-name-needs-qualification-p
			 slot-description class-description)
		   (defining-class slot-description)))
	  as slot-features = (slot-features slot-description)
	  as type-of-slot = (feature-assq 'type slot-features)
	  do
      
	  (when (and type-of-slot
		    (not (do-not-put-slot-in-attribute-tables-p
			     slot-description nil))
		    (category-symbol-given-slot-type
		      type-of-slot))
	    (g2-list-insert-at-end slot-name g2-list)))
    g2-list))

(declare-system-procedure-function g2-get-methods t)

(defun-funcallable g2-get-methods (class-name)
  (let* ((new-g2-list-class
	   (g2-list-or-array-class-for-element-type 'symbol nil))
	 (g2-list (make-transient-item new-g2-list-class)))
    (loop for (name method) in (get-procedure-methods-of-class class-name)
	  do
      (g2-list-insert-at-end method g2-list))
    g2-list))


;;; `g2-text-time-interval-to-unix-time' and
;;; `g2-text-time-stamp-to-unix-time' are functions designed to be called
;;;  from sytem procedures. They are not designed to be particularly efficient.
;;;  They crank up the whole editor parser machinery to assure that what gets
;;;  passed in gets treated the same way as text entered in the editor.
;;;  Anything else is  sure to lead to inconsistenties that would have to be fixed
;;;  in the long run.
;;;  All of this is especially true with time parseing becuause of local
;;;  idiosyncracies in time representation.


(declare-system-procedure-function g2-text-time-interval-to-unix-time t)

(defun-funcallable g2-text-time-interval-to-unix-time (text-interval)
  (let* ((frame-type 'quantitative-variable)
	 (slot-name  'validity-interval)
	 (the-frame (make-frame frame-type))
	 
	 the-value)
    (multiple-value-bind (successp error-string?)
	(parse-text-for-slot (convert-text-string-to-text text-interval)
			     the-frame
			     (get-slot-description-of-frame
			       slot-name the-frame)
			     nil nil nil nil t)
      (declare (ignore successp))
      (setq the-value (get-slot-value the-frame slot-name))
      (delete-frame the-frame)
      (unless (numberp the-value)
	(stack-error cached-top-of-stack "G2 could not parse interval: ~a" error-string?)))
    (with-temporary-gensym-float-creation g2-convert-string-timestamp-to-time     
      (make-evaluation-float
	(coerce-to-gensym-float the-value)))))


(declare-system-procedure-function g2-text-time-stamp-to-unix-time t)


(defun-funcallable g2-text-time-stamp-to-unix-time (text-timestamp)
  (let* ((frame-type 'procedure)
	 (slot-name  'frame-author-or-authors)
	 (the-frame (make-frame frame-type))
	 (new-text (twith-output-to-text-string
		     (tformat "timestamp (~a)" text-timestamp)))
	 (the-text (convert-text-string-to-text new-text))
	 the-value
	 (the-value-as-float 0.0)
	 (time-of-frame-edit-base-time 0.0)
	 (text-time-stamp-seconds 0.0))
    (declare (type gensym-float the-value-as-float))
    (multiple-value-bind (successp error-string?)
	(parse-text-for-slot the-text
			     the-frame
			     (get-slot-description-of-frame
			       slot-name the-frame)
			     nil nil nil nil t)
      (declare (ignore successp))
      (setq the-value (cdr (get-slot-value the-frame slot-name)))
      (delete-frame the-frame)
      (reclaim-text-string text-timestamp)
      (cond ((fixnump the-value)
	     (setq the-value-as-float (coerce-to-gensym-float the-value)))
	    ((floatp the-value)
	     (setq the-value-as-float the-value))
	    (t
	     (stack-error cached-top-of-stack "G2 could not parse timestamp: ~a" error-string?))))
    (make-evaluation-float
      (+e (*e 60.0 the-value-as-float) text-time-stamp-seconds))))


(declare-system-procedure-function g2-clear-history nil)

(declare-forward-reference clear-histories function)

(defun-funcallable g2-clear-history (var-or-param-with-history)
  (clear-histories var-or-param-with-history))







;;;; Miscelaneous System Procedures that query Licensing information


;;; `g2-floating-licenses-remaining' returns the number of licenses on
;;; this G2 server that have not already been used to authorize either
;;; tw or t2 connections/sessions. Which the pool is checked depends
;;; on the kind of ui-client-item it is passed. The cap on this procedure
;;; in sys-mod is responsible for ensuring that its argument is a
;;; ui-client-item. 

(defun-for-system-procedure g2-floating-licenses-remaining (ui-client-item)
  (declare (keeps-g2-local-variables-valid t))
  (macrolet ((tw-p? (ui-client-item)
	       `(cond
		  ((of-class-p ,ui-client-item 'g2-window)
		   t )
		  ((of-class-p ,ui-client-item 'ui-client-session)
		   nil )
		  (t (stack-error cached-top-of-stack
				 "~NF is not a g2-window or ui-client-session"
				 ,ui-client-item)))))

    (if (tw-p? ui-client-item)
	(make-evaluation-integer (count-available-floating-telewindows))
	(make-evaluation-integer (count-available-floating-tw2s)))))




;;; `g2-floating-client-p' is used to determine whether a given ui-client-item
;;; (either a connected tw or a t2) was authorized via its own ok file and
;;; so is a 'dedicated' connection (false), or was authorized by using one
;;; of the floating license on the G2 (true).

(defun-for-system-procedure g2-floating-client-p (ui-client-item)
  (declare (keeps-g2-local-variables-valid t))
  (macrolet
      ((license-level (ui-client-item)
	 `(cond
	    ((of-class-p ,ui-client-item 'g2-window)
	     (telewindows-license-level-of-gensym-window 
	       (map-to-gensym-window-or-stack-error ,ui-client-item)))
	    
	    ((of-class-p ,ui-client-item 'ui-client-session)
	     (unless (ui-client-session-valid-p ,ui-client-item)
	       (stack-error cached-top-of-stack
			    "~NF is not a valid ui-client-session."
			    ,ui-client-item))
	     (ui-client-session-license-level?-function ,ui-client-item))
	    
	    (t (stack-error cached-top-of-stack
			    "~NF is not a g2-window or ui-client-session."
			    ,ui-client-item)))))

    (let ((level (license-level ui-client-item)))
      (when (=f level #.unauthorized-lic-level)
	(stack-error cached-top-of-stack "~NF is unauthorized." ui-client-item))

      (make-evaluation-boolean-value
	(=f level #.floating-lic-level)))))




;;; In a secure G2, A user that is logged in (i.e. that already has some
;;; password) can use `g2-set-user-password' to change their password.
;;; Also, someone else, by intent the administrator, can use this to set
;;; the password of a user that is in the OK file but that doesn't yet
;;; have a password (i.e. the password they have in the OK file is "").

(defun-for-system-procedure g2-set-user-password
    (user-name clear-old-password clear-new-password)
  (declare (keeps-g2-local-variables-valid t))
  (multiple-value-bind (success? error-symbol?)
      (set-user-password
	user-name clear-old-password clear-new-password)
    (make-evaluation-symbol
      (if success?
	  'ok
	  error-symbol?))))



;;; `g2-validate-user-and-password' is a predicate that says whether that
;;; user has that password. It is safe to use because there is a timer in
;;; valid-user-and-password-p that keeps it from being run more than once
;;; per second.

(defun-for-system-procedure g2-validate-user-and-password
    ((user-name symbol) (clear-password text))
  (declare (values symbol))
  (let ((error-symbol? (valid-user-and-password-p user-name clear-password)))
    (make-evaluation-symbol
      (or error-symbol?
	  'ok))))




;;; `g2-authorized-modes-for-user' returns a sequence of symbols.
;;; If there is no user with that name it returns an empty sequence.
;;; (If there is a user there has to be at least one mode or else
;;; the initial processing of the OK file would have failed.)

(defun-for-system-procedure g2-authorized-modes-for-user (user-name)
  (declare (keeps-g2-local-variables-valid t))
  (let* ((modes? (authorized-modes-for-user user-name)))
    (cond (modes?
	   (allocate-evaluation-sequence
	     (copy-list-using-eval-conses modes?)))
	  (t (allocate-evaluation-sequence nil)))))



;;; `g2-add-user' modifies the OK file that authorized this G2 to
;;; have a new user entry with the data given in these arguments.
;;; If we added an (additional) entry for a user who was already
;;; in the OK file.

(defun-simple invalid-user-name-p (user-name-string)
  (let ((wchar (charw user-name-string 0)))
    (when (not (alpha-char-pw wchar))
      (return-from invalid-user-name-p t)))
  (loop for i from 0 below (wide-string-length user-name-string)
      do (let ((wchar (charw user-name-string i)))
           (unless (or (alpha-char-pw wchar)
                       (digit-char-pw wchar)
                       (char=w %\- wchar)
                       (char=w %\_ wchar)
                       (char=w %\. wchar)
                       (char=w %\? wchar))
             (return t)))
      finally (return nil)))

(defun-for-system-procedure g2-add-user
    ((user-name symbol)
     (clear-password text)
     (modes sequence) ; of symbols
     (password-expiration-date sequence)) ; of day month year fixnums
  (declare (keeps-g2-local-variables-valid t))
  
  (if (authorized-modes-for-user user-name)
      ;; The user already exists, so they need to do something different.
      (progn
	(reclaim-evaluation-sequence modes)
	(reclaim-evaluation-sequence password-expiration-date)
	(stack-error cached-top-of-stack
		     "The user ~a already exists." user-name))
      (let* ((scope-conses scope-conses)
	     (date-list
	       (loop for number being each evaluation-sequence-element
		     of password-expiration-date
		     collect number using scope-cons)))

	(cond ((and (=f (length date-list) 1)
		    (eql (first date-list) 0)) ;; value for 'always valid'
	       (setq date-list 0))
	      ((or (/=f (length date-list) 3)
		   ;; Really  (notevery #'integerp date-list) , but the
		   ;; CL function NOTEVERY does not exist! - jpg 11/1/02
		   (loop for date in date-list
			 when (not (integerp date)) return t))
	       (reclaim-evaluation-sequence modes)
	       (write-stack-error cached-top-of-stack 
		 (prog1
		     (tformat "The password-expiration-date ~NV should ~
                               be a sequence of three integers."
			      password-expiration-date)
		   (reclaim-evaluation-sequence password-expiration-date))))
	      (t 
	       (setq date-list
		     ;; This converts it to a universal-date if it succeeds.
		     (check-that-pswd-decay-date-is-in-the-future
		       (first date-list) (second date-list) (third date-list)))))

	(let ((list-of-modes
		(loop for mode being each evaluation-sequence-element
		      of modes
		      collect mode using gensym-cons))
	      (error-symbol? nil))
	  
	  ;; check that the modes are valid
	  (loop for mode in list-of-modes
		do
	    ;; The validator returns a symbol if something's wrong.
	    (when (setq error-symbol?
			(validate-as-possible-user-mode mode))
	      (reclaim-gensym-list list-of-modes)
	      (reclaim-evaluation-sequence modes)
	      (reclaim-evaluation-sequence password-expiration-date)
	      (stack-error cached-top-of-stack
			   "~a is not a valid user mode because ~a"
			   mode error-symbol?)))

	  (setq error-symbol?
		(add-new-user-encoding-as-needed
		  user-name clear-password list-of-modes date-list))
	  
	  (when error-symbol?
	    (reclaim-gensym-list list-of-modes)
	    (reclaim-evaluation-sequence modes)
	    (reclaim-evaluation-sequence password-expiration-date)
	    (stack-error cached-top-of-stack
			 "Problem: ~a" error-symbol?))))) ; i18n !!!

  (reclaim-evaluation-sequence modes)
  (reclaim-evaluation-sequence password-expiration-date))

;;; < documentation >

(defun-for-system-procedure g2-delete-user
    ((user-name symbol))
  (unless (authorized-modes-for-user user-name)
    (stack-error cached-top-of-stack
		 "There is no user with the name ~a" user-name))
  (let ((error-symbol? (delete-user user-name)))
    (when error-symbol?
      (stack-error cached-top-of-stack
		   "Problem: ~a" error-symbol?))))
  


(defun check-that-pswd-decay-date-is-in-the-future (day month year)
  (let* ((today (get-universal-date))
	 (expiration-date (encode-universal-date day month year)))
    (unless (>=f expiration-date
		 today)
      (stack-error
	cached-top-of-stack
	"The date provided for when the password should ~
               expire, ~a/~a/~a, is in the past"
	;; localize this order someday: month/day/year
	month day year))
    expiration-date))


;;; < documentation >

(defun-for-system-procedure g2-change-password-expiration-date
    ((user-name symbol)
     (day integer)
     (month integer)
     (year integer))
  (declare (keeps-g2-local-variables-valid t))

  (unless (authorized-modes-for-user user-name)
    (stack-error cached-top-of-stack
		 "There is no user with the name ~a" user-name))

  (let* ((universal-date ;; stack error if date is earlier than today
	  (check-that-pswd-decay-date-is-in-the-future day month year))
	(error-symbol?
	  (change-users-password-decay-date user-name universal-date)))

    (when error-symbol?
      (stack-error cached-top-of-stack
		   "Problem: ~a" error-symbol?))))


;;; GENSYMCID-1306: Update G2's license without ReStarting

(defun-for-system-procedure g2-update-license ()
  (declare (values truth-value))
  (setq cached-machine-id? nil)
  (setq cached-matching-machine-id? nil)
  (let ((unevaluated-expression within-side-limits))
    (if (authorize-ab)
	truth
      falsity)))


;;; These really belong in utilities0, with the rest of the
;;; stuff for mallocing strings, but they have to be after the
;;; macro definition for defun-for-system-procedure. Sigh.


(defun-for-system-procedure free-malloced-arrays-on-reclaim ()
  #+translator
  (setf free-malloced-arrays t)
  #+translator
  (free-malloced-byte-vector-16s)
  #+translator
  (free-malloced-strings)
  (values))

(defun-for-system-procedure free-malloced-arrays-on-request ()
  #+translator
  (setf free-malloced-arrays nil)
  (values))

(defun-for-system-procedure free-all-malloced-arrays ()
  #+translator
  (free-malloced-byte-vector-16s)
  #+translator
  (free-malloced-strings)
  (values))



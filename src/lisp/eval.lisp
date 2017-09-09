;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module EVAL

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Michael Levin



;;; Note that this module had previously been split up into three files (EVAL,
;;; EVAL2, and EVAL3).  But, now EVAL2 and EVAL3 are obsolete and the remaining
;;; "old" evaluator code is in this module, EVAL.  The declarations are still
;;; needed for those old evaluators that have printers specifically defined for
;;; them.  Note that evaluate-designation and place-evaluate are still used.

;;; The documentation sections of this module should be reviewed.

;;; The new evaluators are in STACK-EVAL1 and STACK-EVAL2.  - cpm, 10/25/95





(declare-forward-reference write-expression function) ; In GRAMMAR7 
(declare-forward-reference print-var-spot-for-stack function)	; In PROC-UTILS






;;;; Evaluator interface to variables




;; NOTE: that DATUM-EVALUATE is obsolete and has been replace by stack-eval.
;; - cpm, 10/25/95
;;
;; Datum-evaluate interfaces to variables by calling (get-current-value
;; variable).  The argument is a variable.  All expression evauation having
;; already been done.



;;; How wake-up works:

;;; When a variable fails to provide an answer, it should push itself (uniquely)
;;; onto the dynamically bound LISP variable
;;; *variables-that-did-not-have-values*.  The frame requesting the value can
;;; then if it choses, push itself onto frames-to-wake-up of that variable.
;;; There is a two-way reference that must be maintained in that if A is on
;;; frames-to-wake-up of B, then B must be on a list of variables that can wake
;;; it up. The types of things that can be woken up include rule-instances,
;;; action-instances and variables. Each must have its own slot for things
;;; waking it up, and each needs a different wake-up logic.

;;; When a variable gets a value, if frames-to-wake-up is non empty, then the
;;; appropriate wake-up is executed for each thing. The wake-up consists of
;;; scheduling a current event.  If A is waking up the set of frames Bi, and if
;;; each Bi has wake-ups from set of variables Cij (these are not neccessarily
;;; distinct), then after executing the wake up procedure of A without
;;; interupts, frames-to-wake-up of A should be empty, and
;;; variables-that-can-wake-up-this-rule-instance of each Bi must be empty, and
;;; all Cij should have no occurances of Bi on their variables-to-wake-up.

;;; Wake-up executions are not subject to the rule of not executing twice per
;;; clock tick.

;;; History accessing functions can take forms such as (get-average-value
;;; variable begin-time end-time minimum-number-of-values) or something like
;;; that. If such a history is not available, there is the issue of how to cause
;;; a wake up to happen.

;;; If a frame is woken up and it is not active, then the wake-up should not
;;; happen, and need not even be scheduled.  When a block becomes inactive,
;;; wake-up references of all its subsiduaries should be removed.






;;;; Forms interpreted by EVAL




;;; There are three evaluators:

;;; (EVALUATE-DESIGNATION <entity-expression> <alist>) returns a single value
;;; which is an entity or temporary-constant. It does not look for the value of
;;; a variable when it is not needed.  If a current value is required,
;;; (get-current-value <variable> <wake-up?>) can be used to get the current
;;; value.

;;; The forms it evaluates are open ended, but presently only include symbols
;;; (which must be the permanent names of entities or be a list bound to
;;; entities, constants, or temporary-constants, and (THE <role-name>
;;; <entity-expression>) which requests the unique value of a role.

;;; If there is no value, it returns NIL.

;;; (PLACE-EVALUATE <entity-expression> <alist>) is like evaluate-designation,
;;; except that its value is restricted (by examination when it is obtained) to
;;; be a variable.  It is used to evaluate to something settable.

;; NOTE: that DATUM-EVALUATE is OBSOLETE and has been replace by stack-eval.
;; - cpm, 10/25/95
;;
;; (DATUM-EVALUATE expression alist) evaluates to a datum, which is not an
;; entity or a temporary-constant.  Thus its range is mutually exclusive with
;; evaluate-designation.  It returns three values (1) value if any or else NIL;
;; (2) an expiration, and if no value then NIL.  An expiration is a time or
;; 'never.  Testing for a null expiration is the only correct way to determine
;; if `datum-evaluate' returned a value. (3) A type.  The type is always a
;; symbol.
;;
;; Datum-evaluate will unpack any temporary-constant #<value type> and return
;; value, 'never and type.
;;
;; Datum-evaluate will evaluate a wide variety of expressions dispatched
;; through the keyword which is first of the expression. These are open-ended
;; and defined with def-evaluator.






;;;; Dynamic Variables for Evaluation




;;; This is a summary of the variables that must be dynamically bound in order
;;; that evaluate-designation, place-evaluate or datum-evaluate can occur.

;;; The truth-threshold controls the extent to which evaluation of AND, OR,
;;; FOR-ALL and THERE-EXISTS must persist. Specifically, in any context, it is
;;; sufficient to prove that an OR or THERE-EXISTS is at least as true as the
;;; truth-threshold.  Thus if it is 700, then once one term that is at least
;;; that true is found, the evaluator is not obligated to try to find terms that
;;; are more [certainly] true. The dual of this explanation works for the
;;; falsity of AND.

;;; truth-threshhold is the minimum [certainty of] truth necessary for a
;;; consequence to occur. This includes the consequent actions of an IF or WHEN
;;; rule, and the body of a WHEN clause in a FOR form. In order to execute ELSE
;;; actions and consequences of a rule, falsity-threshhold is used.
;;; These are attributes of inference-engine-parameters.

;;; *variables-that-did-not-have-values* is bound to NIL at the beginning of an
;;; evaluation, and aquires a list of all variables that were unable to supply
;;; values during the evaluation. It may be used to establish wake-ups.

;;; *earliest-valid-data-time?* if not NIL, requires variables to establish
;;; values that are no older than that time, even though the variable may
;;; otherwise consider such values to be current.
;;;
;;; Note that earliest-valid... has been replaced with
;;; force-new-request-for-value, documented in variables.  -jra 1/15/88

;;; *smallest-divisor* is a system parameter. It is the absolute value of the
;;; smallest number that the evaluator will permit as a divisor. The default is
;;; currently .00000001 or 1e-8. The purpose is to prevent floating point
;;; overflow.






;;;; Alists, Temporary Constants and Recycling




;;; 1. The possible values of evaluate-designation as well as the possible
;;; values on a G2 alist are entites and temporary-constants.

;;; 2. When the value of evaluate-designation is a temporary-constant, the
;;; caller must dispose of it eventually.

;;; 3. When a temporary-constant is looked up on an alist, references to it must
;;; not be propogated. For example, evaluate-designation will copy it, and
;;; datum-evaluate will access its slots but not the entire structure.

;;; 4. Whatever builds an alist must arrange for it to be released. This
;;; includes releasing its temporary-constants.

;;; 5. Whatever adds to the beginning of an alist must rebind it and must
;;; eventually release its head (see
;;; reclaim-eval-alist-head-and-temporary-constants). The reason for rebinding
;;; is that in the case of an abort or other throw, the alist will be reverted
;;; although not released.






;;;; Print Designations and Roles




;;; The function `print-designation' takes the internal form for a designation
;;; and prints to standard-output an acceptable English form for that
;;; designation.  The output may not be exactly the same as what the user
;;; entered to generate it, but it will approximate it.  If new quantifiers are
;;; added in grammar1, the ability to print them should be added here.

(defun print-designation (designation)
  (let ((second? (if (and (consp designation)
			  (consp (cdr-of-cons designation)))
		     (second designation)))
	(designation-length (if (consp designation)
				(length designation)
				0)))
    
    ;; Just print names.
    (cond ((atom designation)
	   (if (symbolp designation)
	       (twrite-symbol designation)
	       (twrite "!!!")))
	  ;; Unwrap giver of value calls, and recurse on designations.
	  ((eq (first designation) 'giver-of-value)
	   (twrite-string "the ")
	   (if (symbolp second?)
	       (twrite-symbol second?)
	       ;; (class . local-name)
	       (progn (twrite-symbol (car second?))
		      (twrite-string " ")
		      (twrite-symbol (cdr second?))))
	   (twrite-string " giving ")
	   (print-designation (third designation)))
	  ;; Special cases for procedure designations.
	  ((and (=f designation-length 2)
		(consp second?)
		(eq (car second?) 'var-spot))
	   (print-var-spot-for-stack second? nil))
	  ((and (or (=f designation-length 2)
		    (=f designation-length 3))
		(eq (car designation) 'var-spot))
	   (print-var-spot-for-stack designation nil))
	  ;; Special case for class-qualified-names
	  ((and (=f designation-length 2)
		(consp (second designation))
		(eq (car (second designation)) 'class-qualified-method))
	   (twrite-symbol (second (second designation)))
	   (twrite-string "::")
	   (twrite-symbol (third (second designation))))
	  ;; Things like (any sensor).
	  ((and (=f designation-length 2) (symbolp second?))
	   (twrite-symbol (first designation))
	   (twrite-string " ")
	   (twrite-symbol second?))
	  
	  ((and (consp second?)
		(or (eq (first second?) 'this-workspace)
		    (and (consp (cdr second?))
			 (eq (second second?) 'this-workspace))))	  
	   (twrite "this workspace"))

	  ((and (consp second?)
		(or (eq (first second?) 'this-window)
		    (and (consp (cdr second?))
			 (eq (second second?) 'this-window))))	  
	   (twrite "this window"))
	  
	  ((and (consp second?)
		(or (eq (first second?) 'this-rule)
		    (and (consp (cdr second?))
			 (eq (second second?) 'this-rule))))	  
	   (twrite "this rule"))

	  ((and (consp second?)
		(or (eq (first second?) 'this-procedure)
		    (and (consp (cdr second?))
			 (eq (second second?) 'this-procedure))))	  
	   (twrite "this procedure"))

	  ((and (consp second?)
		(or (eq (first second?) 'this-procedure-invocation)
		    (and (consp (cdr second?))
			 (eq (second second?) 'this-procedure-invocation))))
	   (twrite "this procedure-invocation"))

	  ((=f (length designation) 2)
	   (twrite-symbol (first designation))
	   (twrite-string " ")
	   (print-role second?))
	  ;; Down here, must be 3 long designation, this is the generic case.
	  (t
	   (print-role-or-role-and-designation
	     second? (first designation) (cddr designation))))))

(defun print-role-or-role-and-designation
       (role designation-quantifier domains)
  (let* ((role-name
	   (role-name-of-role
	     (simple-role-of-role role)))
	 (role-and-designation-printer?
	   (role-and-designation-printer role-name)))
    (cond
      (role-and-designation-printer?
       (funcall-compiled-function
	 role-and-designation-printer?
	 role (first domains) (second domains)))
      (t
       (twrite-symbol designation-quantifier)
       (twrite-char #.%space)
       (print-role role)
       (twrite-char #.%space)
       (print-designation (first domains))))))


;;; The function `print-role' takes the internal form for a role as its argument
;;; and prints a more acceptable user representation of that form.  If new roles
;;; are added in grammar1, the ability to print them should be added here.

(defun print-role (role)
  (cond ((atom role)
	 (twrite-symbol role)
	 (twrite-string " of"))
	(t (let ((local-variable 
		   (get-explicitly-specified-local-name-of-role-if-any role))
		 (role (simple-role-of-role role)))
	     (print-role-1 role local-variable)))))




;;; Print-role-1 is useful when role and local-name do not happen to be consed.
;;; This occurs in print-for-iterator.


(defun print-role-1 (role local-variable?)
  (cond
    ((atom role)
     (twrite-symbol role)
     (when local-variable? (twrite " ") (twrite local-variable?))
     (twrite-string " of"))

    (t 
     (let ((role-server-printer?
	     (role-server-printer
	       (role-name-of-non-atomic-role role))))
       (if role-server-printer?
	   (funcall-simple-compiled-function
	     (compiled-function-in-place role-server-printer?)
	     role local-variable?)

	   ;; If we get down here, this form doesn't know how to print 
	   ;; this role, just show the internal format.
	   (twrite role))))))






;;;; Evaluate Designation and Place




;;; Evaluate-designation evaluates a designation in the context of an alist.
;;; Any name in the designation is looked for first in the alist, and then as
;;; the name of an item.  The value is always nil, an item, or a
;;; temporary-constant, In the latter case, the caller owns it.

;;; Modified by ML, 13 July, 89 not to serve "unservable" items.  See
;;; serve-item-p.  Because role service now rejects unservable items, the only
;;; changes were to the evaluation of symbols, and forms (THE symbol), for the
;;; case that the symbol is on an alist.  Note that datum-evaluate need not be
;;; modified, because if successful, it calls get-current-value which already
;;; checks for active.

(defun-simple evaluate-designation (designation alist)
  #+development
  (unless (and (boundp '*current-computation-frame*)
	       (of-class-p *current-computation-frame* 'block))
    (error "Evaluate-designation was called without a block in *current-computation-frame*.~@
            It value was ~a."
	   (if (boundp '*current-computation-frame*)
	       *current-computation-frame*
	       "not bound")))
  (cond
    ((atom designation)
     (cond ((symbolp designation)
	    (let ((item-or-constant (assq designation alist)))
	      (setq item-or-constant
		    (if item-or-constant
			(cdr item-or-constant)
			(get-instance-with-name-if-any
			  'item designation)))
	      (cond
		((null item-or-constant)
		 (write-warning-message* 3
		   (tformat "The name ~ND, which occurred in ~NF, does not designate anything."
			    designation *current-computation-frame*))
		 nil)
		((temporary-constant-p item-or-constant)
		 (copy-temporary-constant item-or-constant))
		;; Assume to be an item
		((serve-item-p item-or-constant)	; assume to be an entity
		 item-or-constant)
		(t nil))))
	   (t
	    (write-warning-message* 1
	      (tformat "Very strange designation ~ND found in ~NF.  It should not be ~
                        possible to create an atomic, but non-symbolic designation!  ~
                        Please call Gensym Software Support."
		       designation *current-computation-frame*))
	    nil)))

    ((eq (car-of-cons designation) 'the)
     (let ((designation-length (length designation)))
       (declare (type fixnum designation-length))
       (case designation-length
	 ((2)
	  ;; If we get here, we have a designation with "(the x)" where x is
	  ;; some (possibly non-atomic) role.  This should denote an entity
	  ;; bound on the passed alist, or a singular instance of a role.  This
	  ;; is the zero domain case.
	  (let ((role (second designation))
		alist-entry)
	    (if (and (symbolp role)
		     (setq alist-entry (assq role alist)))
		(cdr alist-entry)
		(multiple-value-bind (role-value role-expiration too-many-objects?)
		    (serve-unique-value-of-role (simple-role-of-role role) nil)
		  (cond (role-expiration
			 role-value)
			(too-many-objects?
			 (write-warning-message* 3
			   (tformat "Two entities were designated by ~ND in ~NF, ~
                                     the quantifier \"the\" requires that it designate only one."
				    designation *current-computation-frame*))
			 nil)
			(t
			 (write-warning-message* 3
			   (tformat
			     "There are no objects which match the designation ~ND in ~NF."
			     designation *current-computation-frame*))
			 nil))) )))
	 ((3)
	  ;; The one domain case.
	  (let ((domain-value (evaluate-designation 
				(third designation) alist)))
	    (if domain-value
		(multiple-value-bind (role-value role-expiration too-many-objects?)
		    (serve-unique-value-of-role
		      (simple-role-of-role (second designation)) domain-value)
		  (reclaim-if-temporary-constant domain-value)
		  (cond (role-expiration
			 role-value)
			(too-many-objects?
			 (write-warning-message* 3
			   (tformat "Two entities were designated by ~ND ~
			             in ~NF, the quantifier \"the\" requires ~
                                     that it designate only one."
				    designation *current-computation-frame*))
			 nil)
			(t
			 (write-warning-message* 3
			   (tformat
			     "There are no objects which match the designation ~ND ~
			          in ~NF, though there is an object matching ~ND."
			     designation *current-computation-frame*
			     (third designation)))
			 nil)))
		;; If there was no domain value, that error would have already been
		;; noted for the engineer by the preceding call to evaluate-designation.
		nil)))
	 (t
	   ;; This is the two or more domain case.  We currently cannot handle
	   ;; that here, and so emit a warning message and return nil.
	   (warning-message*
	     3
	     "The expression \"~ND\" could not be evaluated." designation)
	   nil))))
    
    ((eq (car designation) 'giver-of-value)
     ;; The form (giver-of-value <class> <designation>)
     ;; must yield an item of the specified class.
     ;; The semantics also suggest that that class should be a
     ;; subclass of variable.
     (let ((item
	     (evaluate-designation (third designation) alist)))
       (cond
	 ((null item) nil)
	 ((temporary-constant-p item)
	  (warning-message 1
	    "A constant was specified as the ~a giving a value in ~NF."
	    (second designation)
	    *current-computation-frame*)
	  nil)
	 ((not (frame-of-class-p item (second designation)))
	  (warning-message 1
	    "The item ~NF specified in ~NF as giving a value, is not a ~a."
	    item
	    *current-computation-frame*
	    (second designation))
	  nil)
	 (t item))))

    (t
     (write-warning-message* 1
       (tformat "The designation ~ND in ~NF could not be evaluated."
		designation *current-computation-frame*))
     nil)))




;;; The macro `unique-attribute-of-class-with-potential-symbolic-value' takes a
;;; target-class and a symbolic-value and returns the name of the unique
;;; attribute of the target class for which the symbolic value is a possible
;;; value.  If there is no such unique attribute, nil is returned.

(defmacro unique-attribute-of-class-with-potential-symbolic-value
	  (target-class symbolic-value)
  (let ((class (gensym))
	(attribute (gensym))
	(desired-unique-attribute? (gensym))
	(target-class-evaluated (gensym))
	(symbolic-value-evaluated (gensym))
	(target-class-description (gensym))
	(target-class-inheritance-path (gensym)))
    `(loop with ,target-class-evaluated = ,target-class
	   with ,symbolic-value-evaluated = ,symbolic-value
	   with ,target-class-description =
	     (class-description ,target-class-evaluated)
	   with ,target-class-inheritance-path = 
	     (if ,target-class-description
		 (class-inheritance-path ,target-class-description))
	   with ,desired-unique-attribute? =  nil
	   for (,class . ,attribute)
	       in (attribute-value ,symbolic-value-evaluated)
	   doing
       (when (memq ,class ,target-class-inheritance-path)
	 (if ,desired-unique-attribute?
	     (progn
	       (warning-message 1
		 "More than one attribute of class ~a has ~a as a possible ~
                  value.  The implied attributes feature cannot be used when ~
                  this is the case.  Attributes found so far are ~a and ~a."
		 ,class
		 ,symbolic-value-evaluated
		 ,desired-unique-attribute?
		 ,attribute)
	       (return nil))
	     (setq ,desired-unique-attribute? ,attribute)))
	   finally (return ,desired-unique-attribute?))))




;;; The macro `place-evaluate' takes a place designation, an environment alist,
;;; and an optional symbolic value which could be used to resolve an implied
;;; attribute.  This macro will return a variable-or-parameter as denoted by the
;;; place and the optional symbolic value.  Note that even if the thing denoted
;;; by the place is a variable and if the symbolic-value is given, an attempt
;;; will be made to find an attribute of the variable which could receive that
;;; value before the original variable is returned.  If the place does not
;;; denote a variable-or-parameter or an object with an attribute which could
;;; take on the given symbolic value, then this macro will return NIL.

;; This macro does not behave as described.  If an implied attribute is found
;; that is not a variable or parameter, nil is returned even if the parent
;; object is a variable or parameter!!  cpm, 4/3/91

;; When the implied attribute code is modified for multiple inheritance for
;; users, this macro will need to be changed as well to accommodate class-
;; specific user-defined slots.  (ghw 10/15/93)

(defmacro place-evaluate
	  (place alist &optional (value-if-incomplete-place-but-symbolic-value nil))
  (let ((result-of-evaluate-designation (gensym))
	(symbolic-value-evaluated (gensym))
	(class (gensym))
	(attribute? (gensym))
	(implied-place (gensym)))
    `(let ((,result-of-evaluate-designation (evaluate-designation ,place ,alist))
	   ,@(if value-if-incomplete-place-but-symbolic-value
		 `((,symbolic-value-evaluated
		    ,value-if-incomplete-place-but-symbolic-value))
		 nil))
       ;; If the designation denotes nothing or a temporary-constant (i.e. a
       ;; parameter attribute of an object), then return NIL.  Reclaim any
       ;; constant.
       (cond ((null ,result-of-evaluate-designation)
	      nil)
	     ((temporary-constant-p ,result-of-evaluate-designation)
	      (reclaim-temporary-constant ,result-of-evaluate-designation)
	      nil)
	     ,@(if value-if-incomplete-place-but-symbolic-value
		   ;; If the result was not NIL or a temporary constant, then it
		   ;; must be a frame.  First check if the given symbolic value
		   ;; further specializes to an attribute of the frame.
		   `((t
		       (let* ((,class (class ,result-of-evaluate-designation))
			      (,attribute?
			       (unique-attribute-of-class-with-potential-symbolic-value
				 ,class ,symbolic-value-evaluated)))
			 (cond (,attribute?
				(let ((,implied-place
				       (get-slot-value
					 ,result-of-evaluate-designation
					 ,attribute?)))
				  (if (and (of-class-p
					     ,implied-place
					     'variable-or-parameter)
					   (active-p ,implied-place))
				      ,implied-place
				      nil)))
			       ;; If there is no implied attribute, then if this
			       ;; frame is a variable and is active, return it.
			       ((and (variable-or-parameter-p
				       ,result-of-evaluate-designation)
				     (active-p ,result-of-evaluate-designation))
				,result-of-evaluate-designation)
			       (t nil)))))
		   ;; If the result was not NIL or a temporary constant, then it
		   ;; must be a frame.  If this frame is a variable and active,
		   ;; then return it.
		   `(((and (variable-or-parameter-p ,result-of-evaluate-designation)
			   (active-p ,result-of-evaluate-designation))
		      ,result-of-evaluate-designation)
		     (t nil)))))))




;;; (datum-equal value1 type1 value2 type2) is an internal test for
;;; equality of data consistent with th users view. The types are
;;; the numeric subtypes, symbol, text and truth-value.
;;; For comparisons of truth values, a fuzzy equality is defined to be
;;; 1000 - |x - y|. This coincides with the standard notion of equality
;;; on true and false. This functions returns t if the fuzzy equality
;;; >= truth-threshhold, and nil otherwise.

(defun datum-equal (value1 type1 value2 type2)
  (and (value-type-compatible type1 type2)
       (case type1
	 ((number float integer)
	  (= value1 value2))
	 (text (g2-text-equal value1 value2))
	 (truth-value
	  (let ((fuzzy-equality
		  (-f 1000 (absf (-f value1 value2)))))
	    (>=f fuzzy-equality (truth-threshold inference-engine-parameters))))
	 (otherwise	 
	  (eql value1 value2)))))






;;;; Built-In Functions




(defparameter *built-in-functions*
  '(arctan abs ceiling cos exp expt floor ln log max min
    quotient random remainder round sin sqrt truncate
    tan					; Left out until version 4.0.
    great-circle-distance
    rgb-symbol 
    truth-value quantity
    year month day-of-the-month day-of-the-week
    average
    hour minute second time
    text-begins-with-quantity
    is-contained-in-text length-of-text position-of-text
    upper-case-text lower-case-text  
    capitalize-words insert-in-text omit-from-text get-from-text replace-in-text
    find-next-pattern find-next-substring-matching-pattern
    find-and-replace-pattern get-next-token lexeme
    ;; new to 3.0
    call-function
    symbol
    text-to-symbol
    connection-direction
    connection-portname
    connection-position
    connection-side
    connection-style
    ;; new to 4.0
    bitwise-and bitwise-or bitwise-not bitwise-xor
    bitwise-right-shift bitwise-left-shift bitwise-test bitwise-set
    ;; Had been left out of this list until 4.0
    false not
    ;; New to 5.0
    items-are-connected
    items-are-connected-with-direction
    items-are-connected-at-ports

    sequence
    remove
    insert-at-beginning
    insert-at-end
    insert-before
    insert-after
    insert-before-element
    insert-after-element
    change-element
    concatenate
    portion

    evaluated-structure
    change-attribute
    change-evaluated-attribute
    remove-attribute
    remove-evaluated-attribute
    
    character-codes-to-text
    text-to-character-codes
    is-uppercase
    is-titlecase
    is-lowercase
    to-uppercase
    to-titlecase
    to-lowercase
    is-digit
    is-readable-digit
    is-readable-digit-in-radix
    readable-text-for-value
    readable-text
    readable-symbol-text
    compare-text
    import-text
    export-text
    transform-text-for-unicode-comparison
    transform-text-for-g2-4.0-comparison
    find-java-class
    format-numeric-text
    div-long 
    is-nan
    native-integer-array-set
    native-integer-array-get
    native-integer-array-alloc
    native-integer-array-free
    native-float-array-alloc
    native-float-array-free
    native-float-array-set
    native-float-array-get
    kbf-g2nke-count-history-matching-op-and-eventflag
    count-datapoints-that-evaluate-true-with-eventflag
    kbf-g2nke-count-history-matching-op
    count-datapoints-that-evaluate-true

    ;; GENSYMCID-752: Improve the performance of UC15 (Washington River)
    vector-add
    vector-multiply
    vector-scalar-multiply

    number-of-arguments-for-procedure))

;;; Call-function takes at least one argument, specifying the
;;; function-definition, and any number of arguments which will be passed to
;;; that function.


(defun add-built-in-functions-to-directory (category-symbol)
  (loop for function-name in *built-in-functions*
	do (add-to-directory-of-names function-name category-symbol)))



;;; The property argument-range, if it exists for the name of a function,
;;; is either a fixnum specifying the exact number of arguments, or else
;;; it is a consed pair of fixnums specifying the inclusive range of the
;;; number of arguments permitted for the function.

;;; There is no automatic mechanism for setting argument-range of
;;; built-in functions, so this must be done individually. There is also
;;; no reason to do this for functions that are not written as
;;; "fn(args...)" in source. But there is a mechanism for user defined
;;; functions. See files FUNCTIONS and EXTERNAL.

(def-global-or-kb-specific-property-name argument-range)


;;; The global property `get-built-in-function-argument-names' stores the
;;; argument names or types for a built-in G2 function (exported to users as
;;; such).  Some special forms with function-like aspects, e.g., structure
;;; and sequence, are also here.
;;;
;;; Each element is a symbol.  Generally a "descriptive" type should be used.
;;; To indicate n-aryness, the symbol whose print name is ... (coded in Lisp as
;;; |...|) should be used. Optionality can be indicated using a square bracket
;;; in the symbol
;;;
;;; Examples:
;;;
;;;   TRUTH-VALUE-1  QUANTITY   ITEM   OBJECT  |...|
;;;   => truth-value-1, quantity, item, object, ...
;;;
;;;   function [arg |...]|
;;;   => function, [arg, ...]

(def-global-property-name built-in-function-argument-names)

(defun-simple get-built-in-function-argument-names (symbol)
  (when (symbolp symbol)
    (built-in-function-argument-names symbol)))

(loop for function-name in '(sin cos sqrt abs ceiling floor round
			     tan exp ln log truncate)
      doing (setf (argument-range function-name) 1)
	    (setf (built-in-function-argument-names function-name) '(quantity)))

(setf (argument-range 'great-circle-distance) 5)
(setf (built-in-function-argument-names 'great-circle-distance)
      '(latitude-1-quantity longitude-1-quantity
	latitude-2-quantity longitude-2-quantity
	radius-quantity))

(setf (argument-range 'rgb-symbol) 3)
(setf (built-in-function-argument-names 'rgb-symbol)
      '(red-value-integer green-value-integer
	blue-value-integer))

(loop for function-name in '(expt quotient remainder)
      doing (setf (argument-range function-name) 2))
(setf (built-in-function-argument-names 'expt) '(base-quantity power-quantity))
(setf (built-in-function-argument-names 'quotient) '(dividend-quantity divisor-quantity))
(setf (built-in-function-argument-names 'remainder) '(dividend-quantity divisor-quantity))

(setf (argument-range 'random) '(1 . 2))
(setf (built-in-function-argument-names 'random)
      '((upper-bound-quantity)
	(lower-bound-quantity upper-bound-quantity)))
(setf (argument-range 'is-contained-in-text) 2)
(setf (built-in-function-argument-names 'is-contained-in-text) '(text containing-text))
(setf (argument-range 'length-of-text) 1)
(setf (built-in-function-argument-names 'length-of-text) '(text))
(setf (argument-range 'position-of-text) 2)
(setf (built-in-function-argument-names 'position-of-text) '(text containing-text))
(setf (argument-range 'upper-case-text) 1)
(setf (built-in-function-argument-names 'upper-case-text) '(text))
(setf (argument-range 'lower-case-text) 1)
(setf (built-in-function-argument-names 'lower-case-text) '(text))
(setf (argument-range 'capitalize-words) 1)
(setf (built-in-function-argument-names 'capitalize-words) '(text))
(setf (argument-range 'insert-in-text) 3)
(setf (built-in-function-argument-names 'insert-in-text)
      '(text-to-insert text position))
(setf (argument-range 'omit-from-text) 3)
(setf (built-in-function-argument-names 'omit-from-text)
      '(text begin end))
(setf (argument-range 'replace-in-text) 4)
(setf (built-in-function-argument-names 'replace-in-text)
      '(text-to-substitute source-text start-index end-index))
(setf (argument-range 'get-from-text) 3)
(setf (built-in-function-argument-names 'get-from-text)
      '(text start-index end-index))
(setf (argument-range 'find-next-pattern) '(3 . 4))
(setf (built-in-function-argument-names 'find-next-pattern)
      '((search-pattern source-text start-position)
	;;(search-pattern source-text start-position flags)
	))
(setf (argument-range 'find-next-substring-matching-pattern) '(3 . 4))
(setf (built-in-function-argument-names 'find-next-substring-matching-pattern)
      '((search-pattern source-text start-position)
	;;(search-pattern source-text start-position flags)
	))
(setf (argument-range 'find-and-replace-pattern) '(5 . 6))
(setf (built-in-function-argument-names 'find-and-replace-pattern)
      '((search-pattern text-to-substitute source-text start-position end-position)
	(search-pattern text-to-substitute source-text start-position end-position flags)
	))
(setf (argument-range 'get-next-token) '(3 . 4))
(setf (built-in-function-argument-names 'get-next-token)
      '(tokenizer source-text start-position))
(setf (argument-range 'lexeme) 2)
(setf (built-in-function-argument-names 'lexeme) '(source-text token))
;;; arctan may have one or two arguments
(setf (argument-range 'arctan) '(1 . 2))
(setf (built-in-function-argument-names 'arctan)
      '((y) (y x)))
(setf (argument-range 'truth-value) 1)
(setf (built-in-function-argument-names 'truth-value) '(value))
(setf (argument-range 'quantity) 1)
(setf (built-in-function-argument-names 'quantity) '(value))
(setf (argument-range 'text-begins-with-quantity) 1)
(setf (built-in-function-argument-names 'text-begins-with-quantity) '(text))
(setf (argument-range 'symbol) 1)
(setf (built-in-function-argument-names 'symbol) '(text))
(setf (argument-range 'text-to-symbol) 1)
(setf (built-in-function-argument-names 'text-to-symbol) '(text))
(setf (argument-range 'not) 1)
(setf (built-in-function-argument-names 'not) '(truth-value))
(setf (argument-range 'false) 1)
(setf (built-in-function-argument-names 'false) '(truth-value))
(setf (argument-range 'year) 1)
(setf (built-in-function-argument-names 'year) '(time))
(setf (argument-range 'month) 1)
(setf (built-in-function-argument-names 'month) '(time))
(setf (argument-range 'day-of-the-month) 1)
(setf (built-in-function-argument-names 'day-of-the-month) '(time))
(setf (argument-range 'day-of-the-week) 1)
(setf (built-in-function-argument-names 'day-of-the-week) '(time))
(setf (argument-range 'hour) 1)
(setf (built-in-function-argument-names 'hour) '(time))
(setf (argument-range 'minute) 1)
(setf (built-in-function-argument-names 'minute) '(time))
(setf (argument-range 'second) 1)
(setf (built-in-function-argument-names 'second) '(time))
(setf (argument-range 'time) 6)
(setf (built-in-function-argument-names 'time) '(year month date hour minute second))
;; new for 5.0:
(setf (argument-range 'remove) 2)
(setf (built-in-function-argument-names 'remove) '(sequence index-to-remove))
(setf (argument-range 'insert-at-beginning) 2)
(setf (built-in-function-argument-names 'insert-at-beginning) '(sequence item-or-value-to-add))
(setf (argument-range 'insert-at-end) 2)
(setf (built-in-function-argument-names 'insert-at-end) '(sequence item-or-value-to-add))
(setf (argument-range 'insert-before) 3)
(setf (built-in-function-argument-names 'insert-before) '(sequence new-element existing-element))
(setf (argument-range 'insert-after) 3)
(setf (built-in-function-argument-names 'insert-after) '(sequence new-element existing-element))
(setf (argument-range 'insert-before-element) 3)
(setf (built-in-function-argument-names 'insert-before-element) '(sequence index new-element))
(setf (argument-range 'insert-after-element) 3)
(setf (built-in-function-argument-names 'insert-after-element) '(sequence index new-element))
(setf (argument-range 'change-element) 3)
(setf (built-in-function-argument-names 'change-element) '(sequence index new-element))
(setf (argument-range 'portion) 3)
(setf (built-in-function-argument-names 'portion) '(sequence start-index number-to-copy))

(setf (argument-range 'change-attribute) 3)
(setf (built-in-function-argument-names 'change-attribute) '(structure attribute-name item-or-value))
(setf (argument-range 'change-evaluated-attribute) 3)
(setf (built-in-function-argument-names 'change-evaluated-attribute) '(structure symbol-expression item-or-value))
(setf (argument-range 'remove-attribute) 2)
(setf (built-in-function-argument-names 'remove-attribute) '(structure attribute-name))
(setf (argument-range 'remove-evaluated-attribute) 2)
(setf (built-in-function-argument-names 'remove-evaluated-attribute) '(structure symbol-expression))

(setf (argument-range 'attribute-descriptions-of-item-as-structure) 2)
(setf (argument-range 'attribute-descriptions-of-class-as-structure) 2)

(setf (argument-range 'character-codes-to-text) 1)
(setf (built-in-function-argument-names 'character-codes-to-text) '(character-codes))
(setf (argument-range 'text-to-character-codes) 1)
(setf (built-in-function-argument-names 'text-to-character-codes) '(text))
(setf (argument-range 'is-uppercase) 1)
(setf (built-in-function-argument-names 'is-uppercase) '(character-code))
(setf (argument-range 'is-titlecase) 1)
(setf (built-in-function-argument-names 'is-titlecase) '(character-code))
(setf (argument-range 'is-lowercase) 1)
(setf (built-in-function-argument-names 'is-lowercase) '(character-code))
(setf (argument-range 'to-uppercase) 1)
(setf (built-in-function-argument-names 'to-uppercase) '(character-code))
(setf (argument-range 'to-titlecase) 1)
(setf (built-in-function-argument-names 'to-titlecase) '(character-code))
(setf (argument-range 'to-lowercase) 1)
(setf (built-in-function-argument-names 'to-lowercase) '(character-code))
(setf (argument-range 'is-digit) 1)
(setf (built-in-function-argument-names 'is-digit) '(character-code))
(setf (argument-range 'is-readable-digit) 1)
(setf (built-in-function-argument-names 'is-readable-digit)
      '(character-code))
(setf (argument-range 'is-readable-digit-in-radix) 2)
(setf (built-in-function-argument-names 'is-readable-digit-in-radix)
      '(character-code radix))
(setf (argument-range 'readable-text-for-value) 1)
(setf (built-in-function-argument-names 'readable-text-for-value) '(value))
(setf (argument-range 'readable-text) 1)
(setf (built-in-function-argument-names 'readable-text) '(printed-text))
(setf (argument-range 'readable-symbol-text) 1)
(setf (built-in-function-argument-names 'readable-symbol-text) '(printed-text))
(setf (argument-range 'compare-text) 2)
(setf (built-in-function-argument-names 'compare-text) '(text-1 text-2))
(setf (argument-range 'import-text) 2)
(setf (built-in-function-argument-names 'import-text) '(external-text conversion-style))
(setf (argument-range 'export-text) 2)
(setf (built-in-function-argument-names 'export-text) '(unicode-text conversion-style))
(setf (argument-range 'transform-text-for-unicode-comparison) 2)
(setf (built-in-function-argument-names 'transform-text-for-unicode-comparison)
      '(text-to-transform consider-case))
(setf (argument-range 'transform-text-for-g2-4.0-comparison) 2)
(setf (built-in-function-argument-names 'transform-text-for-g2-4.0-comparison)
      '(text-to-transform consider-case))
(setf (argument-range 'find-java-class) 1)
;(setf (built-in-function-argument-names 'find-java-class) '(java-class-name-as-text))
(setf (built-in-function-argument-names 'format-numeric-text)
      '(number-as-text ddd.dddd-format-text))
(setf (argument-range 'format-numeric-text) 2)

;; Additions to finish 6.0. I hope this can be done in an easier-to-maintain and
;; more space efficient manner in the future, and with less Lisp-symbol
;; kludgery (see below)! (MHD 1/10/01)

(setf (built-in-function-argument-names 'bitwise-and) '(integer-1 integer-2))
(setf (built-in-function-argument-names 'bitwise-or) '(integer-1 integer-2))
(setf (built-in-function-argument-names 'bitwise-not) '(integer))
(setf (built-in-function-argument-names 'bitwise-xor) '(integer-1 integer-2))
(setf (built-in-function-argument-names 'bitwise-right-shift) '(integer-1 integer-2))
(setf (built-in-function-argument-names 'bitwise-left-shift) '(integer-1 integer-2))
(setf (built-in-function-argument-names 'bitwise-test) '(integer-1 integer-2))
(setf (built-in-function-argument-names 'bitwise-set) '(integer-1 integer-2))

(setf (built-in-function-argument-names 'max) '(quantity-1 quantity-2 |...|)) ; n-ary, n >= 2
(setf (built-in-function-argument-names 'min) '(quantity-1 quantity-2 |...|)) ; n-ary, n >= 2

(setf (built-in-function-argument-names 'connection-direction) '(item   connection))
(setf (built-in-function-argument-names 'connection-portname) '(item   connection))
(setf (built-in-function-argument-names 'connection-position) '(item   connection))
(setf (built-in-function-argument-names 'connection-side) '(item   connection))
(setf (built-in-function-argument-names 'connection-style) '(connection))
(setf (built-in-function-argument-names 'items-are-connected) '(item-1   item-2))
(setf (built-in-function-argument-names 'items-are-connected-with-direction) '(item-1   item-2   item-1-direction))
(setf (built-in-function-argument-names 'items-are-connected-at-ports) '(item-1   item-2   portname-1   portname-2))

(setf (built-in-function-argument-names 'average) '(quantity-1 quantity-2 |...|)) ; n-ary, n >= 2
(setf (built-in-function-argument-names 'call-function) ; n-ary, n >= 1
      '(function-definition-expression [argument |...]|))
(setf (built-in-function-argument-names 'sequence) '([item-or-value |...]|)) ; n-ary, n >= 0
(setf (built-in-function-argument-names 'concatenate) ; n-ary, n >= 0
      '([sequence |...]|))
(setf (built-in-function-argument-names 'structure) ; n-ary, n >= 0
      '(|[[attribute-name: item-or-value]| |...]|)) ; ultrakludge!
(setf (built-in-function-argument-names 'evaluated-structure) ; n-ary, n >= 0
      '([[symbol-expression item-or-value] |...]|)) ; ditto.
(setf (built-in-function-argument-names 'is-nan) '(float))
(setf (built-in-function-argument-names 'div-long) '(long-1 long-2))
(setf (built-in-function-argument-names 'native-array-set) '(handle value index))
(setf (built-in-function-argument-names 'native-array-get) '(handle index))
(setf (built-in-function-argument-names 'native-array-alloc) '(size))
(setf (built-in-function-argument-names 'native-float-array-alloc) '(size))
(setf (built-in-function-argument-names 'native-float-array-free) '(handle))
(setf (built-in-function-argument-names 'native-float-array-set) '(handle index value))
(setf (built-in-function-argument-names 'native-float-array-get) '(handle index))
(setf (built-in-function-argument-names 'native-array-set) '(handle value index))
(setf (built-in-function-argument-names 'native-array-get) '(handle index))
(setf (built-in-function-argument-names 'native-array-alloc) '(size))
(setf (built-in-function-argument-names 'native-float-array-alloc) '(size))
(setf (built-in-function-argument-names 'native-float-array-free) '(handle))
(setf (built-in-function-argument-names 'native-float-array-set) '(handle index value))
(setf (built-in-function-argument-names 'native-float-array-get) '(handle index))
(setf (built-in-function-argument-names 'native-array-set) '(handle value index))
(setf (built-in-function-argument-names 'native-array-get) '(handle index))
(setf (built-in-function-argument-names 'native-array-alloc) '(size))
(setf (built-in-function-argument-names 'native-float-array-alloc) '(size))
(setf (built-in-function-argument-names 'native-float-array-free) '(handle))
(setf (built-in-function-argument-names 'native-float-array-set) '(handle index value))
(setf (built-in-function-argument-names 'native-float-array-get) '(handle index))
(setf (argument-range 'number-of-arguments-for-procedure) 1)
(setf (built-in-function-argument-names 'number-of-arguments-for-procedure) '(procedure))
;end of changes


;;; The development-only function ev prints information about functions
;;; in G2.

#+development
(defun ev (&optional just-if-missing-args-p)
  (let ((result nil)
	(instance-number 0))
    (loop for symbol in *built-in-functions*
	  do
      (when (and (not (assoc symbol result))
		 (member symbol *built-in-functions*)
		 (or (not just-if-missing-args-p)
		     (null (built-in-function-argument-names symbol))))
	(push (cons symbol (stack-evaluators symbol))
	      result)
	(format t "~&(#~d:) Function: ~a~%" (incf instance-number) symbol)
	(if (null (stack-evaluators symbol))
	    (format t "  (nothing known about args)~%")
	    (loop for xx in (stack-evaluators symbol)
		  do (format t "  Args[~D]: "  (length (evaluator-arguments xx)))
		     (loop for arg in (evaluator-arguments xx)
			   do (format t "~(~a~)   " arg))
		     (terpri)))
	(when (null (built-in-function-argument-names symbol))
	  (format t "  *** NOTE:  NO  BUILT-IN-FUNCTION-ARGUMENT-NAMES! *** ~%"))
	(terpri)))
    (reverse result)))




;; Running (ev t) indicated that the following functions are missing argument
;; declarations: max min average call-function connection-direction
;; connection-portname connection-position connection-side connection-style
;; bitwise-and bitwise-or bitwise-not bitwise-xor bitwise-right-shift
;; bitwise-left-shift bitwise-test bitwise-set items-are-connected
;; items-are-connected-with-direction items-are-connected-at-ports sequence
;; concatenate evaluated-structure find-java-class
;;
;; (MHD 1/9/01)
;;
;; -- UPDATE: defined args for all the above functions except find-java-class.
;; (MHD 1/10/01)





;;;; Evaluator Declarations




;;; An inference-evaluator of a symbol is a global property of symbol which is
;;; compiled-function which is executed to evaluate a form whose car is that
;;; symbol.  The function is given the entire expression as an argument, so it
;;; is responsible for causing nested evaluation of arguments when suitable.
;;; The evaluator does not neccessarily have the same name as the car of the
;;; expression.


;;; (def-evaluator name form) defines an evaluator for a particular symbol
;;; and makes a compiled definition accessible as a property (at load time).
;;; The forms of the evaluator will become the body of a lambda whose
;;; arguments are expression and alist. It should return the standard 2 values
;;; discussed above.

;;; Def-evaluator also supplies other pertinent information about the operator
;;; being defined. After the name of the opertator, there may be several
;;; keywords followed by values. These will not be taken as parts of the body of
;;; the evaluator.
;;; They are:
;;;     :form-writer	The name of a function of 1 argument that writes
;;;                     "source language" for the form given by "expression."
;;;     :type-info      This is a symbol which informs the compiler about the
;;;                     argument and value types for the evaluator. See the
;;;                     compiler for documentation.



;;; The system variable list-of-evaluators contains all defined
;;; inference engine evaluators.  It is defined for development only.

#+development
(defvar list-of-evaluators nil)


(def-global-property-name evaluator-form-writer)

;; jv removed some long-commented out code; see -r1.51 or earlier

(defmacro def-evaluator (name &body body)
  (let (form-writer type-info
	)
    (loop for tail-of-body = body then (cddr tail-of-body)
	  until (not (memq (car tail-of-body) '(:form-writer :type-info))) do
      (when (eq (car tail-of-body) :form-writer)
	(setq form-writer (second tail-of-body)))
      (when (eq (car tail-of-body) :type-info)
	(setq type-info (second tail-of-body)))
	  finally
	    (return

	      `(progn

		 #+development
		 (pushnew ',name list-of-evaluators)

		 ,@(if form-writer `((setf (evaluator-form-writer ',name) ',form-writer)))

		 )))))




;;; The following are some of the old evaluator declarations (those that
;;; included :FORM-WRITER).  These are needed for the printer declarations.
;;; - cpm, 10/25/95


(def-evaluator fuzzy-< :form-writer fuzzy-writer)
(def-evaluator fuzzy-> :form-writer fuzzy-writer)
(def-evaluator fuzzy-= :form-writer fuzzy-writer)
(def-evaluator fuzzy-not-= :form-writer fuzzy-writer)
(def-evaluator is-more-true-than :form-writer fuzzy-logic-comparitor-writer)
(def-evaluator is-not-more-true-than :form-writer fuzzy-logic-comparitor-writer)
(def-evaluator is-less-true-than :form-writer fuzzy-logic-comparitor-writer)
(def-evaluator is-not-less-true-than :form-writer fuzzy-logic-comparitor-writer)
;; False is identical to not operationally, but may be passed through a
;; quantifier by the compiler.
(def-evaluator false :form-writer false-writer)
(def-evaluator quote :form-writer quote-expression-writer)
(def-evaluator if-expression :form-writer if-expression-writer)
(def-evaluator interpolated-value :form-writer historic-function-writer)
(def-evaluator historic-value :form-writer historic-function-writer)
(def-evaluator value-of-previous-datapoint
  :form-writer historic-function-writer)
(def-evaluator collection-time-of-previous-datapoint
  :form-writer historic-function-writer)
(def-evaluator maximum-value :form-writer historic-function-writer)
(def-evaluator minimum-value :form-writer historic-function-writer)
(def-evaluator average-value :form-writer historic-function-writer)
(def-evaluator sum-of-values :form-writer historic-function-writer)
(def-evaluator standard-deviation :form-writer historic-function-writer)
(def-evaluator number-of-datapoints :form-writer historic-function-writer)
(def-evaluator rate-of-change :form-writer historic-function-writer)
(def-evaluator integral :form-writer historic-function-writer)

;;; The evaluator `has-current-value' is an obsolete version of the has-a-value
;;; evaluator.  There is also a has-a-current-value evaluator which will check
;;; if a variable or expression has a value without updating any variable
;;; values.
(def-evaluator has-current-value :form-writer postfix-writer)

;;; The operator `has-a-value' checks if an expression or variable has a value,
;;; making sure that any variables that do not have values attempt to compute a
;;; new one.
(def-evaluator has-a-value :form-writer postfix-writer)
(def-evaluator has-no-value :form-writer postfix-writer)

(def-evaluator has-a-name :form-writer postfix-writer)
(def-evaluator has-no-name :form-writer postfix-writer)

(def-evaluator has-a-current-value :form-writer postfix-writer)
(def-evaluator has-no-current-value :form-writer postfix-writer)

(def-evaluator value-of :form-writer prefix-writer)
(def-evaluator current-value-of :form-writer prefix-writer)
(def-evaluator simulated-value-of :form-writer prefix-writer)

(def-evaluator expiration-time-of :form-writer prefix-writer)
(def-evaluator collection-time-of :form-writer prefix-writer)

(def-evaluator is-not :form-writer write-is)
(def-evaluator is :form-writer write-is)

;;; The evaluator for the `attribute-name' function returns the symbol which is
;;; attribute name within which the given argument frame is an attribute.

(def-evaluator attribute-name :form-writer attribute-name-function-writer)

(def-evaluator current-time :form-writer write-the-current-time)
(def-evaluator current-real-time :form-writer write-the-current-real-time)
(def-evaluator current-subsecond-time :form-writer 
	       write-the-current-subsecond-time)

(def-evaluator receives-a-value :form-writer postfix-writer)
(def-evaluator fails-to-receive-a-value :form-writer postfix-writer)
(def-evaluator is-moved :form-writer postfix-writer)
(def-evaluator is-moved-by-the-user :form-writer postfix-writer)
(def-evaluator is-moved-by-g2 :form-writer postfix-writer)
(def-evaluator is-resized-by-the-user :form-writer postfix-writer)
(def-evaluator becomes-related :form-writer write-relation-event-literal)
(def-evaluator ceases-to-be-related :form-writer write-relation-event-literal)
(def-evaluator has-generic-event :form-writer write-generic-event-literal)

(def-evaluator nupec-synchronization-occurs
  :form-writer write-nupec-synchronization-occurs)

;;; The evaluator `distance-between' returns the distance in workspace pixels
;;; between two objects on the same workspace.

(def-evaluator distance-between :form-writer write-in-binary-role-style)

;;; The evaluator `distance-between-and-the-nearest' returns an integer
;;; approximation to the distance between a designated entity and the nearest
;;; instance of a given class to that entity.

(def-evaluator distance-between-and-the-nearest
  :form-writer write-distance-between-and-the-nearest)

(def-evaluator same-as :form-writer write-same-as)
(def-evaluator not-same-as :form-writer write-same-as)

(def-evaluator is-of-class :form-writer write-is-a)
(def-evaluator is-not-of-class :form-writer write-is-a)

(def-evaluator is-active :form-writer write-is-active)
(def-evaluator is-not-active :form-writer write-is-active)

(def-evaluator name :form-writer write-as-if-role)

(def-evaluator is-related :form-writer relation-writer)
(def-evaluator is-not-related :form-writer relation-writer)

(def-evaluator format-form :form-writer write-format-form)       

(def-evaluator g2-list-or-sequence-length
  :form-writer write-g2-list-or-sequence-length)

(def-evaluator network-interface-for
  :form-writer write-network-interface-for)

(def-evaluator let :form-writer write-let)

(def-evaluator there-exists-literal :form-writer write-new-quantified-form)
(def-evaluator for-every-literal :form-writer write-new-quantified-form)
(def-evaluator sum :form-writer write-aggregator)
(def-evaluator product :form-writer write-aggregator)
(def-evaluator aggregated-average :form-writer write-aggregator)
(def-evaluator maximum :form-writer write-aggregator)
(def-evaluator minimum :form-writer write-aggregator)
(def-evaluator count :form-writer write-aggregator)






;;;; Evaluator Printers - needed for evaluator declarations




(defun fuzzy-writer (form)
  (write-expression (second form))
  (twrite
    (cond ((eq (car form) 'fuzzy-<) " < ")
	  ((eq (car form) 'fuzzy->) " > ")
	  ((eq (car form) 'fuzzy-=) " = ")
	  (t " /= ")))  
  (write-expression (third form))
  (twrite " (+- " )
  (write-expression (fourth form))
  (twrite ")" ))

(defun fuzzy-logic-comparitor-string-name (name)
  (case name
    ((is-more-true-than)
     " is more true than ")
    ((is-not-more-true-than)
     " is not more true than ")
    ((is-less-true-than)
     " is less true than ")
    ((is-not-less-true-than)
     " is not less true than ")
    (t " ??? ")))

(defun fuzzy-logic-comparitor-writer (expression)
  (write-expression (second expression))
  (twrite-string (fuzzy-logic-comparitor-string-name (car expression)))
  (write-expression (third expression)))

(defun false-writer (exp)
  (let* ((negated-exp (second exp))
	 (keyword (if (consp negated-exp) (car negated-exp))))
    (case keyword
      (value-of
	(twrite "the value of ")
	(write-expression (second negated-exp))
	(twrite " is false"))
      (current-value-of
	(twrite "the current value of ")
	(write-expression (second negated-exp))
	(twrite " is false"))
      (otherwise
	(write-expression (second exp))
	(twrite " is false")))))

(defun quote-expression-writer (form)
  (tformat "the symbol ~(~a~)" (second form)))

(defun if-expression-writer (form)
  (twrite "(if " )
  (write-expression (second form))
  (twrite " then ")
  (write-expression (third form))
  (twrite " else ")
  (write-expression (fourth form))
  (twrite ")" ))

(defun historic-function-writer (form)
  (let* ((name (first form))
	 (prefix
	   (case name
	     (interpolated-value "the interpolated value ")
	     ((historic-value value-of-previous-datapoint) "the value ")
	     (collection-time-of-previous-datapoint "the collection time ")
	     (maximum-value "the maximum value")
	     (minimum-value "the minimum value ")
	     (average-value "the average value ")
	     (sum-of-values "the sum of the values ")
	     (standard-deviation "the standard deviation ")
	     (integral "the integral ")
	     (rate-of-change "the rate of change ")
	     (otherwise "the unknown function ")))
	 (designation (second form))
	 interval-1 interval-2 time-unit)
    
    (if (memq name '(integral rate-of-change))
	(setq time-unit (second (third form))	       ;(quote symbol)
	      interval-1 (fourth form)
	      interval-2 (fifth form))
	(setq interval-1 (third form)
	      interval-2 (fourth form)))
    
    (twrite prefix)
    
    (case name
      (integral
	(twrite "in ") (twrite-symbol time-unit) (twrite " of "))
      (rate-of-change
	(twrite "per ") (twrite-symbol time-unit) (twrite " of "))
      (otherwise
	(twrite "of ")))

    (print-designation designation)
    
    (cond
      ((memq name '(value-of-previous-datapoint 
		     collection-time-of-previous-datapoint))
       (twrite " as of ")
       (write-expression interval-1)
       (twrite " datapoints ago"))
      (interval-2
       (cond ((eq interval-2 'true)
	      (twrite " during the ")
	      (write-expression interval-1)
	      (twrite " ending with the collection time"))
	     (t (twrite " between ")
		(write-expression interval-1)
		(twrite " ago and ")
		(write-expression interval-2)
		(twrite " ago"))))
      ((eq name 'historic-value)
       (twrite " as of ")
       (write-expression interval-1)
       (twrite " ago"))
      (t (twrite " during the last ")
	 (write-expression interval-1)))))

(defun postfix-writer (exp)
  (write-expression (second exp))
  (twrite (case (first exp)
	   ((has-a-value has-current-value) " has a value")
	   (has-no-value " has no value")
	   (has-a-current-value " has a current value")
	   (has-no-current-value " has-no-current-value")
	   (receives-a-value " receives a value")
	   (fails-to-receive-a-value " fails to receive a value")
	   (is-moved " is moved")
	   (is-moved-by-the-user " is moved by the user")
	   (is-moved-by-g2 " is moved by G2")
	   (is-resized-by-the-user " is resized by the user")
	   (has-a-name " has a name")
	   (has-no-name " has no name")
	   )))

(defun prefix-writer (exp)
  (twrite (case (first exp)
	   (value-of "the value of ")
	   (current-value-of "the current value of ")
	   (expiration-time-of "the expiration time of ")
	   (collection-time-of "the collection time of ")))
  (write-expression (second exp)))

(defun write-is (form)
  (write-expression (second form))
  (twrite-string (if (eq (first form) 'is) " is " " is not "))
  (tprin (second (third form)) nil))

(defun attribute-name-function-writer (expression)
  (twrite-string "the attribute-name of ")
  (print-designation (second expression))) 

(defun-simple write-the-current-time (expression)
  (declare (ignore expression))
  (twrite-string "the current time"))

(defun-simple write-the-current-real-time (expression)
  (declare (ignore expression))
  (twrite-string "the current real time"))

(defun-simple write-the-current-subsecond-time (expression)
  (declare (ignore expression))
  (twrite-string "the current subsecond time"))

(defun write-relation-event-literal (exp)
  (print-designation (third exp))
  (twrite (if (eq (first exp) 'becomes)
	      " becomes "
	      " ceases to be "))
  (twrite-symbol (second exp))
  (twrite " ")
  (print-designation (fourth exp)))

(defun write-generic-event-literal (exp)
  (print-designation (second exp))
  (twrite " has a ")
  (twrite-symbol (third exp)
  (twrite " event")))

(defun write-nupec-synchronization-occurs (expression)
  (declare (ignore expression))
  (twrite-string "NUPEC synchronization occurs"))

(defun write-in-binary-role-style (exp)
  (twrite (case (car exp)
	   (distance-between "the distance between ")))
  (print-designation (second exp))
  (twrite " and ")
  (print-designation (third exp)))

(defun write-distance-between-and-the-nearest (expression)
  (twrite-string "the distance between ")
  (print-designation (second expression))
  (tformat " and the nearest ~(~a~)" (second (third expression))))

(defun write-same-as (exp)
  (print-designation (second exp))
  (twrite (if (eq (first exp) 'same-as) " is the same object as "
	     " is not the same object as "))
  (print-designation (third exp)))

;;; The function `write-is-a' is the writer for the is-of-class and
;;; is-not-of-class expressions.  It handles two types of parses, the "is a
;;; class" and "is an instance of the class named by" expressions.

(defun write-is-a (exp)
  (let ((operator (first exp))
	(designation (second exp))
	(class-exp-or-quoted-name (third exp)))
    (print-designation designation)
    (if (eq operator 'is-of-class)
	(twrite " is ")
	(twrite " is not "))
    (cond ((and (consp class-exp-or-quoted-name)
		(eq (car class-exp-or-quoted-name) 'quote))
	   (write-symbol-with-a-or-an
	     (second class-exp-or-quoted-name) nil))
	  (t
	   (twrite "an instance of the class named by (")
	   (write-expression class-exp-or-quoted-name)
	   (twrite ")")))))

(defun write-is-active (exp)
  (print-designation (second exp))
  (twrite (if (eq (car exp) 'is-active) " has been activated"
	      " has not been activated")))

(defun write-as-if-role (exp)
  (twrite "the ")
  (twrite-symbol (first exp))
  (twrite " of ")
  (print-designation (second exp)))

(defun relation-writer (exp)
  (print-designation (third exp))
  (twrite-string
    (case (first exp)
      (is-related " is ")
      (is-not-related " is not ")))
  (let ((relation (second exp)))
    (cond ((symbolp relation)
	   (twrite-symbol relation))
	  ((and (consp relation)
		(eq (car-of-cons relation) 'quote))
	   (twrite-symbol (second relation)))
	  (t
	   (write-expression relation))))
  (twrite-string " ")
  (print-designation (fourth exp)))

(defun write-format-form (form)
  (loop for listed-component on (cddr form)
	for component = (car listed-component)
	until (null (cdr listed-component))
	initially
	  (twrite '\" )
	  (twrite (second form))
	  (twrite '[ )
	  do
    (cond
      ((text-string-p component)
       (twrite '] )
       (twrite component)
       (twrite '[ ))
      (t (write-expression component)))
    finally
      (twrite '] )
      (twrite component)
      (twrite '\" )))

(defun write-g2-list-or-sequence-length (exp)
  (twrite "the number of elements in ")
  (print-designation (second exp)))

(defun write-network-interface-for (exp)
  (twrite "the network interface for ")
  (print-designation (second exp)))

(defun write-let (form)
  (twrite '\( )
  (write-expression (third form))
  (twrite " where ")
  (loop for ((var binding) . rest) on (second form) do
    (twrite-symbol var)
    (twrite " = ")
    (write-expression binding)
    (if rest (twrite "; ")))
  (twrite '\) ))

(defun write-aggregator (form)
  (let* ((scope (second form))
	 (aggregated-expression (third form))
	 (role (first scope))
	 (name-from-role (get-name-provided-by-role role))
	 (atomic-name-for-role
	   (atomic-naming-element-of-simple-role (simple-role-of-role role)))
	 (binding (second scope))
	 (domain (third scope)))

    (tformat "the ~(~a~) over each "
	     (if (eq (car form) 'aggregated-average)
		 'average
		 (car form)))

    (cond (domain
	   (print-role-1 role (if (neq name-from-role binding) binding))
	   (twrite-string " ")
	   (print-designation domain))
	  (t
	   (cond ((symbolp atomic-name-for-role)
		  (twrite-symbol atomic-name-for-role))
		 ((consp atomic-name-for-role)
		  (twrite-symbol (car atomic-name-for-role)))
		 (t #+development
		    (cerror "Unexpected role form" "Continue")
		    (twrite-symbol 'none)))
	   (when (neq role binding)
	     (twrite-string " ")
	     (twrite binding))))

    (twrite-string " of (")
    (write-expression aggregated-expression)
    (twrite-string ")")))



;;; Write-new-quantified-form is the expression writer for quantifiers
;;; and aggregates. They have the form (name scope quantified-expression).
;;; It may be called upon to write either a compiled or raw scope. These are:
;;;   Raw scope:
;;;   1.    (role domain)
;;;   2.    (role)
;;;   3.    ((role . local-name) domain)
;;;   4.    ((role . local-name))
;;;   Compiled scope:
;;;   5.    (role binding)
;;;   6.    (role binding domain)
;;; There is no way to distinguish 1 and 5 in all cases. A binding is a symbol
;;; or (VAR-SPOT symbol). A domain may be a symbol. For the present, the
;;; ambiguous case will be treated as 5. This could cause a confusing message to
;;; print.

;; Consider having the caller identify whether the form is a raw form.!

(defun write-new-quantified-form (form)
  (let* ((scope (second form))
	 (quantified-expression (third form))
	 role name-from-role binding domain atomic-name-for-role)

    (cond
      ;; Cases 2,4.
      ((null (cdr scope))
       (if (simple-role-p (car scope))
	   ;; Case 2.
	   (setq role (car scope)
		 binding (get-name-provided-by-role role)
		 domain nil)
	   ;; Case 4.
	   (setq role (caar scope)
		 binding (cdar scope)
		 domain nil)))
      ;; Case 3
      ((not (simple-role-p (car scope)))
       (setq role (caar scope)
	     binding (cdar scope)
	     domain (second scope)))
      ;; Case 1 as far as it can be recognized.
      ((and (null (cddr scope))
	    (not (atom (second scope)))
	    (not (eq (car (second scope)) 'var-spot)))
       (setq role (first scope)
	     binding (get-name-provided-by-role (first scope))
	     domain (second scope)))
      ;; Cases 5 and 6, which are for all compiled forms.
      (t (setq role (first scope)
	       binding (second scope)
	       domain (third scope))))
    
    (setq name-from-role (get-name-provided-by-role role))
    (setq atomic-name-for-role
	  (atomic-naming-element-of-simple-role (simple-role-of-role role)))

    (case (car form)
	(there-exists-literal
	 (twrite "there exists ")
	 (twrite (supply-a-or-an name-from-role)))	 
	(for-every-literal (twrite "for every ")))

    (cond (domain
	   (print-role-1 role (if (neq name-from-role binding) binding))
	   (twrite-string " ")
	   (print-designation domain))
	  (t
	   (twrite-symbol atomic-name-for-role)
	   (when (neq role binding)
	     (twrite-string " ")
	     (twrite binding))))

    (twrite
      (case (car form)
	(there-exists-literal " such that (" )
	(for-every-literal " (")))

    (write-expression quantified-expression)

    (twrite ")" )))






;;;; Warnings




(defun warn-of-big-bignum (negative?)
  (warning-message 1 "A number was computed that is too big to store in ~
                      floating point format.  It was ~A, and ~D is being ~
                      stored instead."
    (if negative? "negative" "positive")
    (if negative? -1 1))
  (if (and (boundp '*current-computation-frame*) *current-computation-frame*)
      (warning-message 1 "The preceding occurred within ~NF."
	*current-computation-frame*)))
;;


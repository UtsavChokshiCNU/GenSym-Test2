;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module GRAMMAR2

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Michael Levin and Mark H. David



;;; To GRAMMAR3







;;; simplify-*-and-/ transforms a valid expression in pre-compiled internal form
;;; into another such, without altering any list structure. It simplifies any
;;; nested tree of expressions with the operator "*" at the top level into a single
;;; list, and does the same for any nested expression of this type which is nested only
;;; within expressions beginning with the operator "/".

(defun simplify-*-and-/ (term)
  (if (atom term) term
      (case (car term)
	(* (phrase-cons
	     '*
	     (loop for item in (cdr term)
		   nconcing
		     (cond ((and (consp item) (eq (car item) '*))
			    (loop for item1 in (cdr item)
				  collecting
				    (simplify-*-and-/ item1) using phrase-cons))
			   ((and (consp item) (eq (car item) '/))
			    (phrase-list (simplify-*-and-/ item)))
			   (t (phrase-list item))))))
	(/ (phrase-list '/
			(simplify-*-and-/ (second term))
			(simplify-*-and-/ (third term))))
	(otherwise term))))




;;; The property argument-range, if it exists for the name of a function,
;;; is either a fixnum specifying the exact number of arguments, or else
;;; it is a consed pair of fixnums specifying the inclusive range of the
;;; number of arguments permitted for the function.

;; Modified check-number-of-args to not validate user-defined function calls.
;; These calls now always will pass this test.  This change was made because
;; there is now consistency analysis of function calls.  - cpm, 1/13/93

(defun check-number-of-args (function-form)
  (let* ((function-name (car function-form))
	 (built-in? (memq function-name *built-in-functions*))
	 (argument-range? (argument-range function-name)))
    (cond
      (built-in?
       (if argument-range?
	   (let* ((number-of-args (length (cdr function-form)))
		  (minimum-number-of-args-permitted
		    (if (consp argument-range?)
			(car argument-range?)
			argument-range?))
		  (maximum-number-of-args-permitted
		    (if (consp argument-range?)
			(cdr argument-range?)
			argument-range?)))
	     (cond
	       ((<f number-of-args minimum-number-of-args-permitted)
		(values bad-phrase 'too-few-arguments))
	       ((>f number-of-args maximum-number-of-args-permitted)
		(values bad-phrase 'too-many-arguments))
	       ((not (<=f minimum-number-of-args-permitted
			  number-of-args
			  maximum-number-of-args-permitted))
		(values bad-phrase 'wrong-number-of-arguments))
	       (t function-form)))
	   function-form))
      ((eq function-name 'structure)
       ;; This name has special grammar defined for it in GRAMMAR1A that
       ;; transforms it into a call to evaluated-structure.  If it is also allowed
       ;; to be parsed as a function name, then we have an ambiguous parse.  If
       ;; structure becomes a reserved word, then we could drop it from this
       ;; parser-rewriter function.
       bad-phrase)
      (t
       ;; This clause makes all calls to user defined functions explicitly use
       ;; the call-function operation.  This is needed since many little bits of
       ;; grammar expand into what look like function calls, and calls to user
       ;; defined functions were being confused with calls to these system
       ;; defined functions.  This is a problem when the system defined function
       ;; was never intended to be directly exposed to the users, for example
       ;; the distance-between operation.  -jra 5/31/95
       (phrase-cons 'call-function function-form)))))

(declare-grammar-transform-can-return-bad-phrase check-number-of-args)





(defun translate-role-and-preposition (phrase)
  (let* ((role (first phrase))
	 (preposition (second phrase)))
    (cond
      ((eq preposition 'of) role)
      ((consp preposition)
       (case (car preposition)
	 ((at-port related)
	  (phrase-list (car preposition) (second preposition) role))
	 ;; Add other more complicated roles here
	 ))
      (t (phrase-list preposition role)))))




(defun translate-role-local-name-and-preposition (phrase)
  (let* ((role (first phrase))
	 (local-name (second phrase))
	 (preposition (third phrase)))
    
    (phrase-cons
      ;; This form is identical to the one in translate-role-and-preposition.
      (cond
	((eq preposition 'of) role)
	((consp preposition)
	 (case (car preposition)
	   ((at-port related)
	    (phrase-list (car preposition) (second preposition) role))
	   ;; Add other more complicated roles here
	   ))
	(t (phrase-list preposition role)))
      
      local-name)))




(defun-simple convert-history-interval-maybe-cdr (x)
  (if (consp x) (cdr x) nil))

(defun convert-history-interval (form)
  (let ((expression (first form))
	(unit (second form)))
    (cond ((integerp expression)
	   (phrase-cons (* expression (units-to-integer unit)) 'seconds))
	  ((and (consp expression)
		(find 'seconds expression
		      :key #'convert-history-interval-maybe-cdr))
	   ;; This fixes Bug HQ-5097838 "'This is ambiguous in G2'
	   ;; message when using 'during' history expressions".
	   ;; An example is an expression such as:
	   ;; if (the average value of FLOAT-VAR during the last
	   ;;     1 minute - 10 seconds > 20)
	   ;;   then post "YES";
	   ;; - jpg 8/31/05
	   bad-phrase)
	  ((eq unit 'seconds) expression)
	  (t (phrase-list '* (units-to-integer unit) expression)))))

(defun reject-text-of-attribute-reference (form)
  (let* ((nested-designation (third form))
	 (nested-simple-role?
	   (when (consp nested-designation)
	     (simple-role-of-role (role-of-designation nested-designation)))))
    (if (and nested-simple-role?
	     (or (symbolp nested-simple-role?)
		 (and (consp nested-simple-role?)
		      (eq (car-of-cons nested-simple-role?) 'class-qualified-name)))
	     (third nested-designation))
	bad-phrase
	form)))

(declare-grammar-transform-can-return-bad-phrase reject-text-of-attribute-reference)

(defun convert-class-qualified-list-to-keyword-symbol (parse-result)
  (make-unique-slot-name-symbol
    (class-qualifier parse-result)
    (unqualified-name parse-result)))



(add-parallel-grammar-rules (unique-)
			    (literal expression sum signed-sum term signed-term term-or-signed-term
					quotient exponential factor designation quantifier
					argument-list preposition parenthesized-logical-expression
					parenthesized-expression previous-datapoint-expression)
  
  
  (literal (expression fuzzy-comparator expression '\( '+- expression '\) ) (2 1 3 6)
	   fuzzy-comparator-reparser)
  

  (literal truth-value-attribute)
  ;; Above entry replaces the following commented out entries. (MHD 5/9/97)
;  (literal 'true)
;  (literal 'false)

  
  (literal designation)
  
  (literal (designation 'has 'a 'name) (has-a-name 1))
  (literal (designation 'has 'no 'name) (not (has-a-name 1)))
  (literal (expression 'is symbol) (is 1 '3)
	   symbol-cannot-be-true-false-or-not choose-is-or-=)

  (literal (designation 'is relation-name designation)
	   (is-related '3 1 4))
  (literal (designation 'is 'not relation-name designation)
	   (is-not-related '4 1 5))

;  (literal (designation 'is 'connected 'to designation)
;	   (is-connected 1 5))
;  (literal (designation 'is 'not 'connected 'to designation)
;	   (is-not-connected 1 6))
  
  (literal (designation 'is 'false) (false 1))
  (literal ('the 'value 'of designation 'is 'false) (false (value-of 4)))
  (literal ('the 'current 'value 'of designation 'is 'false)
	   (false (current-value-of 5)))
  (literal ('the 'simulated 'value 'of designation 'is 'false) 
	   (false (simulated-value-of 5)))

  (literal ('the 'value 'of designation 'as 'of
	    ago-interval 'ago) (historic-value 4 7))
  (literal ('the 'value 'of designation 'as 'of
	    ago-interval 'ago 'is 'true) (historic-value 4 7))
  (literal ('the 'value 'of designation 'as 'of
	    ago-interval 'ago 'is 'false) (false (historic-value 4 7)))

  (literal ('the 'value 'of designation 'as 'of 
	   previous-datapoint-expression datapoint-or-datapoints 'ago)
	  (value-of-previous-datapoint 4 7))
  (literal ('the 'value 'of designation 'as 'of 
	   previous-datapoint-expression datapoint-or-datapoints 'ago 'is 'true)
	  (value-of-previous-datapoint 4 7))
  (literal ('the 'value 'of designation 'as 'of 
	   previous-datapoint-expression datapoint-or-datapoints 'ago 'is 'false)
	  (false (value-of-previous-datapoint 4 7)))
  
  (literal (designation 'is 'true) 1)
  (literal ('the 'value 'of designation 'is 'true) (value-of 4))
  (literal ('the 'current 'value 'of designation 'is 'true)
	   (current-value-of 5))
  (literal ('the 'simulated 'value 'of designation 'is 'true) 
	   (simulated-value-of 5))
  
  (literal (expression 'is 'not symbol) (is-not 1 '4)
	   symbol-cannot-be-true-false-or-not  choose-is-or-=)

  (literal (designation 'is a-or-an class-or-value-type)
	   (is-of-class 1 '4) flatten-is-of-class-type-spec)
  (literal (designation 'is 'not a-or-an class-or-value-type)
	   (not (is-of-class 1 '5)) flatten-is-of-class-type-spec)
  (literal (designation 'is 'an 'instance 'of 'the 'class 'named 'by
			'\( expression '\))
	   (is-of-class 1 11))
  (literal (designation 'is 'not 'an 'instance 'of 'the 'class 'named 'by 
			'\( expression '\))
	   (not (is-of-class 1 12)))
  (literal (designation 'is 'the 'same 'object 'as designation)
	   (same-as 1 7))
  (literal (designation 'is 'not 'the 'same 'object 'as designation)
	   (not (same-as 1 8)))

  (literal (designation 'has 'been 'activated) (is-active 1))
  (literal (designation 'has 'not 'been 'activated)
	   (not (is-active 1)))
  
  (literal (designation 'exists) (exists 1))
  (literal (color-factor 'exists) (exists 1))
  
  (literal (designation 'does 'not 'exist) (not (exists 1)))
  (literal (color-factor 'does 'not 'exist) (not (exists 1)))

  (literal ('the 'value 'of designation) (value-of 4))
  (literal ('the 'value 'of parenthesized-logical-expression) (value-of 4))

  (literal ('the 'current 'value 'of parenthesized-logical-expression)
	   (current-value-of 5))
  (literal ('the 'current 'value 'of designation) (current-value-of 5))

  (literal ('the 'simulated 'value 'of parenthesized-logical-expression)
	   (simulated-value-of 5))
  (literal ('the 'simulated 'value 'of designation) (simulated-value-of 5))
  
  (literal ('the 'first 'of 'the 'following expressions-that-has-a 'current 'value
	    logical-argument-list)
	   (first-that-has-a-current-value . 9))
  
  
  (factor constant)
  
  (factor ('the 'value 'of designation) (value-of 4))
  (factor ('the 'value 'of parenthesized-expression) (value-of 4))
  
  (factor ('the 'current 'value 'of designation) (current-value-of 5))
  (factor ('the 'current 'value 'of parenthesized-expression)
	  (current-value-of 5))

  (factor ('the 'simulated 'value 'of designation) (simulated-value-of 5))
  ;; The evaluator for simulated-value-of could actually take an expression
  ;; rather than a designation as argument (displays, except for graphs,
  ;; take general expressions).  The grammar category would, however,
  ;; have to be simulation-expression rather than just expression.

  (factor ('the 'expiration 'time 'of designation)
	  (expiration-time-of 5))
  (factor ('the 'collection 'time 'of designation)
	  (collection-time-of 5))
	  
  ;  (factor ('the 'expiration 'time 'of parenthesized-expression)
  ;	  (expiration-time 5))

  ;; Consider having a semi-open category for atomic roles. They would be
  ;; entered into a directory. The category would be nominally open, but
  ;; would reject anything not on the predefined list. It would leave the
  ;; reason-for-rejection unchanged, perhaps. What is the name of the category?
  ;; There are currently class names, attribute names; these would be built in roles.
  ;; ... NOW DONE! (See below.)

  (color-factor
    ('the color-attribute 'of designation)
    (the 2 4))

  (color-factor
    ('the color-attribute local-name 'of designation)
    (the (2 . 3) 5)
    (filter-out-region-icon-color))

  (color-factor
    ('the region icon-or-stripe-color 'of designation)
    (the (item-color 2 symbol) 5))

  (color-factor
    ('the region icon-or-stripe-color local-name 'of designation)
    (the ((item-color 2 symbol) . 4) 6))

  (factor
    ('the system-attribute 'of designation)
    (the 2 4))
    
  ;; To deal with the attribute "instantiate" 
  (factor
    ('the system-attribute-instantiate 'of designation)
    (the 2 4))
 
  (system-attribute-instantiate 'instantiate)
  
  ;; system-or-user-defined-attribute-name is new -- had been attribute-name.
  ;; (MHD 11/25/91)
  (factor
    ('the 'text 'of 'the system-or-user-defined-attribute-name 'of
     designation)
    (the (text-of-attribute 5 text) 7))
    
  #+no
  (factor
    ('the 'text 'of 'the class-name '\:\: system-or-user-defined-attribute-name 'of
     designation)
    (the (text-of-attribute (class-qualified-name 5 7) text) 9))


  ;; The following two forms were added because user-defined-or-built-in-
  ;; attribute refuses to include gsi-interface-name and array-length.
  (factor
    ('the 'text 'of 'the 'gsi-interface-name 'of designation)
    (the (text-of-attribute gsi-interface-name text) 7))

  (factor
    ('the 'text 'of 'the 'array-length 'of designation)
    (the (text-of-attribute array-length text) 7))

  ;; The text of unnamed system attribute.  E.g., the text of procedures, rules,
  ;; or messages.  Note that the reparser function rejects those parses which
  ;; will be handled by the previous parsing rule.  -jra &cpm 9/12/91
  (factor
    ('the 'text 'of designation)
    (the (text-of-attribute text text) 4)
    reject-text-of-attribute-reference)
  
  (parenthesized-expression ( '\( expression '\) ) 2)
 
  ;; Made "the name" a class-phrase role so that it can serve multiple-names.
  ;; The following is not needed.  cpm, 8/11/91.
  ;  (factor ('the 'name 'of designation) (the (role-server name) 4))

  ;; Changed superior-class from factor to class-phrase-role.  Now that there is
  ;; multiple-inheritace in version 4.0, this is needed to serve multiple
  ;; superior classes.  - cpm, rdf 2/23/94

  (factor ('the 'attribute 'name 'of designation) (attribute-name 5))
  
  (factor ('the 'first 'of 'the 'following expressions-that-has-a 'current 'value
	   argument-list)
	  (first-that-has-a-current-value . 9))
  (factor ('the 'distance 'between designation 'and designation)
	  (distance-between 4 6))
  (factor ('the 'distance 'between designation 'and 'the 'nearest class)
	  (distance-between-and-the-nearest 4 (quote 8)))
  (factor ('the 'symbol standard-or-class-qualified-symbol) (quote 3))

  (preposition ('named 'by) named-by)

  (preposition ('named 'by) named-by)
  (preposition ('that 'is 'of 'the 'class 'named 'by)
	       class-instances-named-by)

  (literal (unique-expression 'is 'a 'member 'of 'the g2-datum-type
		       'list designation)
	   (g2-list-or-sequence-member-p 9 1))

  (literal (unique-expression 'is 'not 'a 'member 'of 'the g2-datum-type
		       'list designation)
	   (not (g2-list-or-sequence-member-p 10 1)))

  (literal (unique-literal 'is 'a 'member 'of 'the g2-datum-type
		       'list designation)
	   (g2-list-or-sequence-member-p 9 1))

  (literal (unique-literal 'is 'not 'a 'member 'of 'the g2-datum-type
		       'list designation)
	   (not (g2-list-or-sequence-member-p 10 1)))

  (literal (designation 'is 'a 'member 'of 'the class 'list designation)
	   (g2-list-or-sequence-member-p 9 1))

  (literal (designation 'is 'not 'a 'member 'of 'the class 'list designation)
	   (not (g2-list-or-sequence-member-p 10 1)))

  ;; New grammar for version 4.0, not containing "the <type> list <g2-list>"
  ;; grammar.
  (literal (unique-expression 'is 'a 'member 'of designation)
	   (g2-list-or-sequence-member-p 6 1))

  (literal (unique-expression 'is 'not 'a 'member 'of designation)
	   (not (g2-list-or-sequence-member-p 7 1)))

  (literal (unique-literal 'is 'a 'member 'of designation)
	   (g2-list-or-sequence-member-p 6 1))

  (literal (unique-literal 'is 'not 'a 'member 'of designation)
	   (not (g2-list-or-sequence-member-p 7 1)))

  (literal (designation 'is 'a 'member 'of designation)
	   (g2-list-or-sequence-member-p 6 1))

  (literal (designation 'is 'not 'a 'member 'of designation)
	   (not (g2-list-or-sequence-member-p 7 1)))
  )




;;; When parsing the is-of-class expression, some listed type-specifications
;;; such as (sequence) and (structure) will end up being arguments of quote.
;;; G2's quote cannot handle arbitrary Lisp trees, and so these type specs must
;;; be flattened back into symbols.  The funcalled instruction for is-of-class
;;; will convert these back into valid type-specifications at run-time.  (Yes, I
;;; know this is inefficient, and yes, we should do better at some point.  -jra
;;; 9/20/96)

(defun flatten-is-of-class-type-spec (is-of-class-expr)
  (cond
    ((and (consp is-of-class-expr) (eq (car-of-cons is-of-class-expr) 'not))
     (phrase-list 'not
		  (flatten-is-of-class-type-spec (second is-of-class-expr))))
    ;; The following check is merely a paranoia-based saftey test.
    ((and (consp is-of-class-expr)
	  (eq (car-of-cons is-of-class-expr) 'is-of-class))
     (let ((type-expr (third is-of-class-expr)))
       (if (and (consp type-expr)
		(eq (car-of-cons type-expr) 'quote)
		(consp (cadr-of-conses type-expr))
		(symbolp (caadr-of-conses type-expr))
		(null (cdadr-of-conses type-expr)))
	   (phrase-list 'is-of-class (cadr-of-conses is-of-class-expr)
			(phrase-list 'quote (caadr-of-conses type-expr)))
	   is-of-class-expr)))
    (t is-of-class-expr)))




(add-grammar-rules
  '((conditional-expression expression)
    (conditional-expression unique-conditional-expression)

    (unique-conditional-expression unique-expression)
    
    (unique-conditional-expression
      ('if unique-logical-expression 'then unique-expression 'else unique-conditional-expression)
      (if-expression 2 4 6))
    (unique-conditional-expression
      ('if unique-logical-expression 'then unique-expression)
      (if-expression 2 4)
      (restrict-if-slot-edit-feature procedure conditional-expression))
    ))

;; The special-designation forms for array-length and gsi-interface-name
;; are added because the grammar will not accept those slots as
;; e-designations for purposes of change-the-text of text-of grammar.
;; This special casing is not appealing, but it fixes a couple of bugs
;; without jeopardizing other grammar.  (ghw 4/21/95)

(add-grammar-rules
  '((special-designation ('the 'array-length 'of e-designation) (the array-length 4))
    (special-designation ('the 'gsi-interface-name 'of e-designation)
		       (the gsi-interface-name 4))))


;;; E-designations are designations with EVERY but not ANY.
;;; They are used to express iterations over individual actions.

(def-concept e-designation)

(add-grammar-rules
  '((e-designation item-name)

;    (e-designation (class '\:\: method-name) (the (class-qualified-method 1 3)))
    (e-designation class-qualified-method)

    (e-designation ('the class))
    (e-designation ('every class)  (1 2)
		   (restrict-if-slot-edit-feature procedure e-designation))
    (e-designation ('every class local-name) (1 (2 . 3))
		   (restrict-if-slot-edit-feature procedure e-designation))

    #+no
    (e-designation ('the attribute-name))

    (e-designation
      ('the system-or-user-defined-attribute-name-unconverted 'of e-designation)
     (the 2 4)
     filter-out-the-text-of-as-a-special-case)
    (e-designation
      ('the system-or-user-defined-attribute-name-unconverted local-name 'of e-designation)
      (the (2 . 3) 5)
     filter-out-the-text-of-and-region-icon-color)

    #+no
    (e-designation
     ('the class '\:\: attribute-name 'of e-designation)
     (the (class-qualified-name 2 4) 6)
     )
    #+no
    (e-designation
     ('the class '\:\: attribute-name local-name 'of e-designation)
     (the ((class-qualified-name 2 4) . 5) 7)
     )

    ;; Added for 3.0. cpm, 8/16/91
    (e-designation
      ('the class-or-value-type 'that 'is 'an 'attribute 'of e-designation 'named 'by 
       e-designation)
      (the (attribute-value 2) 8 11))
    (e-designation
      ('the class-or-value-type local-name 'that 'is 'an 'attribute 'of e-designation
       'named 'by designation)
      (the ((attribute-value 2) . 3) 9 12))

    (e-designation (e-quantifier class-phrase-role e-designation))
    (e-designation (e-quantifier class-phrase-role special-designation))

;    (e-designation ('every class-phrase-role e-designation) (1 2 3)
;		   (restrict-if-slot-edit-feature procedure e-designation))
  
    (e-designation ('the class 'giving
			 'the system-or-user-defined-attribute-name-unconverted
			 'of e-designation)
		   (giver-of-value 2 (4 5 7)))

    #+no
    (e-designation ('the class 'giving 'the class '\:\: attribute-name 'of e-designation)
		   (giver-of-value 2 (4 (class-qualified-name 5 7) 9)))

    (e-designation ('this 'workspace)
		   (the (role-server this-workspace kb-workspace)))

    (e-designation ('this 'window) (the (role-server this-window ui-client-item)))

    (e-designation ('this 'rule) (the (role-server this-rule rule))
		   (restrict-if-not-slot-edit-feature rule this-rule))

    (e-designation ('this 'procedure) (the (role-server this-procedure procedure))
		   (restrict-if-not-slot-edit-feature procedure this-procedure))

    (e-designation ('this 'procedure-invocation)
		   (the (role-server this-procedure-invocation procedure-invocation))
		   (restrict-if-not-slot-edit-feature
		     procedure this-procedure-invocation))
    
    ;; This is a 1.11B compatibility rule. Consider limiting it in some way.
    
    ;; To fix BUG-059-5435, I am commenting out this obsolete grammar.  Selecting
    ;; the grammar gave a compiler error.  "The form THE WORKSPACE NAMED is obsolete."
    ;; I have removed the workspace-named-is-obsolete transformation function from
    ;; 
    ;; (ghw 1/26/99)
    ;(e-designation ('the 'workspace 'named workspace-name)     ; workspace-name was object-name (MHD 6/7/90)
    ;		   (the (named 4 kb-workspace)) workspace-named-is-obsolete)

    (e-designation ('the list-role-keyword element-type 'in e-designation)
	       (the (2 3) 5))
    
    (e-designation ('the list-role-keyword element-type local-name 'in e-designation)
	       (the ((2 3 ) . 4) 6))

    
    (e-designation (e-quantifier element-type 'in e-designation)
		 (1 (element-iterator 2) 4))

    (e-designation (e-quantifier element-type local-name 'in e-designation)
		 (1 ((element-iterator 2) . 3) 5))

    (e-quantifier 'the)
    (e-quantifier 'every 1 (restrict-if-slot-edit-feature procedure e-designation))

    (e-class-phrase-role (class preposition) (1 2) translate-role-and-preposition)

  ))







;; New definition above makes workspace name not be enterable anymore,
;; in 3.0.  Next step, next major release (3.1 or 4.0), is to remove the
;; grammar altogether.  (MHD 9/25/91)  Done for G2 5.2 (ghw 1/26/99)
;; 
;; Old definition, which was in 2.1, is as follows:   (MHD 9/25/91)
;; 
;; (defun workspace-named-is-obsolete (form)
;;   (notify-engineer
;;     "The form THE WORKSPACE NAMED is obsolete and will not be maintained ~
;;      in future versions of G2.")
;;   form)





(add-grammar-rules
  '((rule for-rule)
    (rule simple-rule)
    (rule initial-rule)
    
    (initial-rule ('initially action-list) (initially true 2) fix-action-list)
    (initial-rule ('initially 'if antecedent 'then action-list)
		  (initially 3 5) fix-action-list)
    (initial-rule ('initially 'for for-phrase initial-rule-1))

    (initial-rule-1 ('for for-phrase initial-rule-1))
    (initial-rule-1 if-rule)
    (initial-rule-1 unconditional-rule)

    (for-rule ('for for-phrase for-rule))
    (for-rule simple-rule)

    (simple-rule if-rule)
    (simple-rule when-rule)
    (simple-rule whenever-rule)
    (simple-rule unconditional-rule)
    
    ;added by SoftServe
    (rule (assignment-section initial-rule))
    (simple-rule (assignment-section if-rule))
    (simple-rule (assignment-section when-rule))
    (simple-rule (assignment-section whenever-rule))
    
    ;end of changes

    (if-rule ('if antecedent 'then action-list) (if 2 4) fix-action-list)
    (when-rule ('when antecedent 'then action-list) (when 2 4) fix-action-list)
    (whenever-rule ('whenever event-antecedent 'then action-list)
		   (whenever 2 4) fix-action-list)
    (unconditional-rule ('unconditionally action-list) (if true 2) fix-action-list)
 

    (embedded-rule ('when antecedent 'then action-list) (when 2 4) fix-action-list)
    (embedded-rule action-list)
    (embedded-rule ('for for-phrase embedded-rule-1))

    (embedded-rule-1 ('for for-phrase embedded-rule-1))
    (embedded-rule-1 when-rule)
    (embedded-rule-1 unconditional-rule)

    
    (antecedent logical-expression)
    
    ;added by SoftServe
    

    (generic-call-expression 
      (unreserved-symbol '= function-name '\( '\)) (3 1) 
        check-number-of-args reject-if-sequence-constant)
    (generic-call-expression 
      (unreserved-symbol '= function-name argument-list) (3 4 1) 
        check-number-of-args reject-if-sequence-constant)
    (assignment-section ('using assignment-section-body))
    (assignment-section-body generic-call-expression)
    (assignment-section-body (generic-call-expression '\, assignment-section-tail) (1 3))
    (assignment-section-tail generic-call-expression)
    (assignment-section-tail (generic-call-expression '\, assignment-section-tail) (1 3))
    
    
    ;end of changes
    
    (r-paren '\) )                         
                             
    (for-phrase ('any class) (1 2))
    (for-phrase ('any class local-name) (any (2 . 3)))
    (for-phrase ('any class-phrase-role designation) (1 2 3))
    (for-phrase ('the class-phrase-role designation) (1 2 3))

    (for-phrase ('the system-or-user-defined-attribute-name-unconverted 'of designation) (the 2 4)
     filter-out-the-text-of-as-a-special-case)
    (for-phrase ('the system-or-user-defined-attribute-name-unconverted local-name 'of designation) (the (2 . 3) 5)
     filter-out-the-text-of-and-region-icon-color)

    #+no
    (for-phrase ('the attribute-name '\:\: class-name 'of designation)
     (the (class-qualified-name 2 4) 6))
    #+no
    (for-phrase ('the attribute-name '\:\: class-name local-name 'of designation)
     (the ((class-qualified-name 2 4) . 5) 7))

    (for-phrase (quantifier element-type 'in designation)
		(1 (element-iterator 2) 4))
    (for-phrase (quantifier element-type local-name 'in designation)
		(1 ((element-iterator 2) . 3) 5))

    (for-phrase ('the list-role-keyword element-type 'in designation)
		(the (2 3) 5))
    (for-phrase ('the list-role-keyword element-type local-name 'in designation)
		(the ((2 3) . 4) 6))

    ; These could be put above in the parallel grammar section.
    (literal there-exists-literal)
    (literal for-every-literal)

    (unique-literal there-exists-literal)
    (unique-literal for-every-literal)

    (there-exists-literal
      ('there 'exists a-or-an aggregator-phrase 'such 'that '\( unique-logical-expression '\) )
      (there-exists-literal 4 8) patch-aggregator-scope)

    (there-exists-literal
      ('there 'exists a-or-an aggregator-phrase)
      (there-exists-literal 4 true) patch-aggregator-scope)

    (for-every-literal
      ('for 'every aggregator-phrase '\( unique-logical-expression '\) )
      (for-every-literal 3 5) patch-aggregator-scope)

    (aggregator-phrase class)
    (aggregator-phrase (class local-name) ((1 . 2)))
    (aggregator-phrase (class-phrase-role immediate-designation))

    (immediate-designation item-name)

    (immediate-designation ('the class))
    (immediate-designation ('the local-name))
    (immediate-designation ('the attribute-name))

    ))



(add-parallel-grammar-rules (unique- )
			    (factor expression)
  ; Simulator needs its own copy because logical-expression is distinct!!!
  
  (factor ('the aggregator 'over 'each aggregator-phrase 'of '\( unique-expression '\) )
	  (2 5 8)  patch-aggregator-scope)

  (aggregator 'sum)
  (aggregator 'product)
  (aggregator 'maximum)
  (aggregator 'minimum)
  (aggregator 'average)

  (factor ('the 'count 'of 'each aggregator-phrase)
	  (2 5 true)  patch-aggregator-scope)

  (factor ('the 'count 'of 'each aggregator-phrase 'such
	   'that '\( unique-logical-expression '\) )
	  (2 5 9)  patch-aggregator-scope)  

  )


(add-grammar-rules
  '((simulation-factor
      ('the aggregator 'over 'each simulation-aggregator-phrase
       'of '\( simulation-expression '\) )
	  (2 5 8)  patch-aggregator-scope)

    (simulation-factor ('the 'count 'of 'each simulation-aggregator-phrase)
	    (2 5 true)  patch-aggregator-scope)

    (factor ('the 'count 'of 'each simulation-aggregator-phrase 'such
	     'that '\( simulation-logical-expression '\) )
	    (2 5 9)  patch-aggregator-scope)


    (simulation-literal
      ('there 'exists a-or-an simulation-aggregator-phrase 'such 'that
       '\( simulation-logical-expression '\) )
      (there-exists-literal 4 8) patch-aggregator-scope)

    (simulation-literal
      ('there 'exists a-or-an simulation-aggregator-phrase)
      (there-exists-literal 4 true) patch-aggregator-scope)

    (simulation-literal
      ('for 'every simulation-aggregator-phrase '\( simulation-logical-expression '\) )
      (for-every-literal 3 5) patch-aggregator-scope)

    (simulation-literal 
      (simulation-designation 'is 'the 'same 'object 'as simulation-designation)
      (same-as 1 7))
    (simulation-literal 
      (simulation-designation 'is 'not 'the 'same 'object 'as simulation-designation)
      (not (same-as 1 8)))
    (simulation-literal (simulation-designation 'exists) (exists 1))
    (simulation-literal (simulation-designation 'is a-or-an class-or-value-type)
			(is-of-class 1 '4) flatten-is-of-class-type-spec)
    (simulation-literal (simulation-designation 'is 'not a-or-an class-or-value-type)
			(not (is-of-class 1 '5)) flatten-is-of-class-type-spec)
    (simulation-literal
      (simulation-designation 'is 'an 'instance 'of 'the 'class 'named 'by
			      '\( simulation-expression '\) )
      (is-of-class 1 11))
    (simulation-literal
      (simulation-designation 'is 'not 'an 'instance 'of 'the 'class 'named 'by
			      '\( simulation-expression '\) )
      (not (is-of-class 1 12)))

    (simulation-aggregator-phrase class)
    (simulation-aggregator-phrase (class local-name) ((1 . 2)))
    (simulation-aggregator-phrase (simulation-class-phrase-role immediate-designation))


    ;; G2-List simulation membership expressions:

    ;; Note that pre-version 4.0 grammar contained "the <class-or-type> list
    ;; <g2-list>".

    (simulation-literal
      (simulation-expression 'is 'a 'member 'of 'the g2-datum-type 'list
			     simulation-designation)
      (g2-list-or-sequence-member-p 9 1))

    (simulation-literal
      (simulation-expression 'is 'not 'a 'member 'of 'the g2-datum-type 'list
			     simulation-designation)
      (not (g2-list-or-sequence-member-p 10 1)))

    (simulation-literal
      (simulation-designation 'is 'a 'member 'of 'the class 'list
			      simulation-designation) 
      (g2-list-or-sequence-member-p 9 1))

    (simulation-literal
      (simulation-designation 'is 'not 'a 'member 'of 'the class 'list
			      simulation-designation) 
      (not (g2-list-or-sequence-member-p 10 1)))

    ;; Fixed a bug in version 4.0 to allow the test of logicals in a g2-list.
    ;; But, the simulator still does not allow TRUE and FALSE values.  Are these
    ;; available at all in the simulator?  - cpm, 12/7/94

    (simulation-literal
      (simulation-literal 'is 'a 'member 'of 'the g2-datum-type 'list
			     simulation-designation)
      (g2-list-or-sequence-member-p 9 1))

    (simulation-literal
      (simulation-literal 'is 'not 'a 'member 'of 'the g2-datum-type
       'list simulation-designation)
      (not (g2-list-or-sequence-member-p 10 1)))

    ;; Note that in version 4.0, the simulator MEMBER expression that does not
    ;; require a g2-list element-type in the grammar.

    (simulation-literal
      (simulation-expression 'is 'a 'member 'of simulation-designation)
      (g2-list-or-sequence-member-p 6 1))

    (simulation-literal
      (simulation-expression 'is 'not 'a 'member 'of simulation-designation)
      (not (g2-list-or-sequence-member-p 7 1)))

    (simulation-literal
      (simulation-designation 'is 'a 'member 'of simulation-designation) 
      (g2-list-or-sequence-member-p 6 1))

    (simulation-literal
      (simulation-designation 'is 'not 'a 'member 'of simulation-designation) 
      (not (g2-list-designation-p 7 1)))

    (simulation-literal
      (simulation-literal 'is 'a 'member 'of simulation-designation)
      (g2-list-or-sequence-member-p 6 1))

    (simulation-literal
      (simulation-literal 'is 'not 'a 'member 'of
       simulation-designation)
      (not (g2-list-or-sequence-member-p 7 1)))
    ))



(defun patch-aggregator-scope (form)
  (if (eq (car form) 'average) (setf (car form) 'aggregated-average))

  (if (symbolp (second form))
      (phrase-list (first form) (phrase-list (second form)) (third form))
      form))









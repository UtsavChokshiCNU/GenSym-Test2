;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module GRAMMAR3

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Michael Levin and Mark H. David


(declare-forward-references
  (button-frame-status          function CONTROLS))



(add-grammar-rules
  '((simulation-factor number)    
    
    (simulation-conditional-expression simulation-expression)    
    (simulation-conditional-expression
      ('if simulation-logical-expression
       'then simulation-expression 'else simulation-conditional-expression)
      (if-expression 2 4 6))
    (simulation-conditional-expression
      ('if simulation-logical-expression 'then simulation-expression)
      (if-expression 2 4)) 
    
    (ago-interval interval)
    (ago-interval unique-expression 1 reject-if-float-interval)
    (ago-interval (unique-expression plural-time-unit)
                  (1 2) convert-history-interval)

    ;; I don't see why the interval expressions in ago-interval and other interval
    ;; expression grammars are limited to unique expressions.  I think this is an
    ;; arbitrary limitation restricting what could be a useful grammatical
    ;; construction.  Since we are just before 1.1 release I don't think we have time
    ;; to test the removal of the restriction, but as soon as possible after 1.1 we
    ;; should remove it.  -jra 9/6/88
    
    (last-interval interval)
    (last-interval (unique-expression plural-time-unit)
                   (1 2) convert-history-interval)
    
    (previous-datapoint-expression unique-expression)
    
    (unique-ago-interval interval)
    (unique-ago-interval unique-expression 1 reject-if-float-interval)
    (unique-ago-interval (unique-expression plural-time-unit)
			 (1 2) convert-history-interval)
    
    (unique-last-interval interval)
    (unique-last-interval (unique-expression plural-time-unit)
			  (1 2) convert-history-interval)
    
    (unique-previous-datapoint-expression unique-expression)
    
    (simulation-ago-interval interval)
    (simulation-ago-interval simulation-expression 1 reject-if-float-interval)
    (simulation-ago-interval (simulation-expression plural-time-unit)
			     (1 2) convert-history-interval)
    
    (simulation-last-interval interval)
    (simulation-last-interval (simulation-expression plural-time-unit)
			      (1 2) convert-history-interval)
    
    (simulation-previous-datapoint-expression simulation-expression)

    (datapoint-or-datapoints 'datapoint)
    (datapoint-or-datapoints 'datapoints)
    
    ))

;;; The function `reject-if-float-interval' returns bad-phrase iff
;;; ago-interval, a phrase resulting from the parse of the grammar
;;;
;;;   <ago-interval> ::=
;;;        <unique-expression> <plural-time-unit>
;;;           => (1 2) 
;;;           -> convert-history-interval  |
;;;        <interval> |
;;;        <unique-expression>
;;;
;;; or of a <unique-ago-interval>, <simulation-ago-interval>,
;;; <last-interval>, <unique-last-interval>, or a
;;; <simulation-last-interval>
;;;
;;; represents a (managed-float . SECONDS) situation.
;;;
;;; This is to avoid an ambiguous grammar situation.
;;; See Bug HQ-5008254 "Float time-intervals in 'as of' history
;;; expressions lead to ambiguous grammar". - jpg and mhd 5/5/05

(defun reject-if-float-interval (ago-interval)
  (if (and (consp ago-interval)
	   (eq (cdr ago-interval) 'seconds)
	   (phrase-float-p (car ago-interval)))
      bad-phrase
      ago-interval))



;; Following is the version of logical-expression that allows
;; ANY and EVERY. 

(add-grammar-rules
  '((logical-expression disjunct)
    (logical-expression (unique-disjunct 'or unique-logical-expression)
			(or 1 3) simplify-associative-operation)

;    (logical-expression designation)
;    (logical-expression v-logical-expression)

;    ;; v-logical-expression is a boolean expression formed from variable
;    ;; names only. 
;    (v-logical-expression (v-disjunct 'or v-logical-expression)
;			  (or 1 3) simplify-associative-operation)
;    (v-logical-expression v-disjunct)

;    (v-disjunct (v-literal 'and  v-disjunct)
;		(and 1 3) simplify-associative-operation)
;    (v-disjunct v-literal)

;    (v-literal ('not '\( v-logical-expression '\) ) (not 3))
;    (v-literal variable-or-parameter-name)

;    (v-literal ( '\( v-logical-expression '\) ) 2)

    (parenthesized-logical-expression ( '\( logical-expression '\) ) 2)
    (parenthesized-logical-expression ('not '\( unique-logical-expression '\) ) (not 3))
    
    (disjunct conjunct)
    (disjunct (conjunct 'and disjunct)
	      (and 1 3) simplify-associative-operation)
    
    (conjunct literal)
    
;    (literal designation)   ;This is a repetition
    (literal ('\( logical-expression '\) ) 2)
    (literal ('not '\( unique-logical-expression '\) ) (not 3))

    ;; Note that arguments may not be logical expressions for now!
    (literal (function-name '\( r-paren ) (1) check-number-of-args reject-if-sequence-constant)
    (literal (function-name argument-list) (1 . 2) check-number-of-args reject-if-sequence-constant)
    
    (literal (expression fuzzy-comparator expression) (2 1 3))
    (literal (delimited-logical-expression fuzzy-equivicator delimited-logical-expression) (2 1 3))   

    (literal (expression '<= expression) (2 1 3))
    (literal (expression '>= expression) (2 1 3))
    (literal (designation qualifier) (1 . 2) put-designation-in-qualifier)
    (literal (parenthesized-expression-or-logical-expression 'has 'a 'value)
	     (has-a-value 1))
    (literal (parenthesized-expression-or-logical-expression 'has 'a 'current 'value)
	     (has-a-current-value 1))
    
    (literal ('the 'first 'of 'the 'following expressions-that-has-a 'value
	      unique-logical-argument-list)
	     (first-that-has-a-value . 8))
    
    (literal ( '\( 'if unique-logical-expression 'then
	      unique-logical-expression 'else unique-logical-expression '\) )
	     (if-expression 3 5 7))
    (literal ( '\( 'if unique-logical-expression 'then
	      unique-logical-expression '\) )
	     (if-expression 3 5))

    (delimited-logical-expression designation)
    (delimited-logical-expression ( '\( logical-expression '\) ) 2)
    
    (qualifier ('has 'a 'value) (has-a-value foo))
    (qualifier ('has 'no 'value) (has-no-value foo))
    (qualifier ('has 'a 'current 'value) (has-a-current-value foo))
    (qualifier ('has 'no 'current 'value) (has-no-current-value foo))
    
    (parenthesized-expression-or-logical-expression ('\( expression '\)) 2)
    (parenthesized-expression-or-logical-expression ('\( logical-expression '\)) 2)
    (parenthesized-expression-or-logical-expression ('not '\( unique-logical-expression '\)) (not 3))
    
    (logical-argument-list ( '\( logical-expression '\) ) (2))
    (logical-argument-list ( '\( logical-expression '\, logical-argument-list-tail) (2 . 4))
    
    
    (logical-argument-list-tail (logical-expression '\) ) (1))
    (logical-argument-list-tail (logical-expression '\, logical-argument-list-tail) (1 . 3))
    
    (designation ('the class local-name 'giving 'the attribute-name 'of designation)
		 (giver-of-value (2 . 3) (5 6 8)))

    (designation ('the class local-name 'giving 'the class '\:\: attribute-name 'of designation)
		 (giver-of-value (2 . 3) (5 (class-qualified-name 6 8) 10)))

    (fuzzy-equivicator '=)
    (fuzzy-equivicator '/=)
    (fuzzy-equivicator ('is 'more 'true 'than) is-more-true-than)
    (fuzzy-equivicator ('is 'not 'more 'true 'than) is-not-more-true-than)
    (fuzzy-equivicator ('is 'less 'true 'than) is-less-true-than)
    (fuzzy-equivicator ('is 'not 'less 'true 'than) is-not-less-true-than)
 
    ))











;; Following for simulation version of logical-expression

(add-grammar-rules
  '((simulation-logical-expression simulation-disjunct)
    (simulation-logical-expression (simulation-disjunct 'or simulation-logical-expression)
			(or 1 3) simplify-associative-operation)
    
    (simulation-disjunct simulation-conjunct)
    (simulation-disjunct (simulation-conjunct 'and simulation-disjunct)
	      (and 1 3) simplify-associative-operation)
    
    (simulation-conjunct simulation-literal)

    (simulation-literal ('\( simulation-logical-expression '\) ) 2)
    (simulation-literal ('not '\( simulation-logical-expression '\) ) (not 3))
    
    (simulation-literal (function-name '\( r-paren ) (1) check-number-of-args reject-if-sequence-constant)
    (simulation-literal (function-name argument-list) (1 . 2) check-number-of-args reject-if-sequence-constant)
    
    (simulation-literal (simulation-expression fuzzy-comparator simulation-expression) (2 1 3))
    (simulation-literal (simulation-expression '<= simulation-expression) (2 1 3))
    (simulation-literal (simulation-expression '>= simulation-expression) (2 1 3))
    (simulation-literal (simulation-designation simulation-qualifier) (1 . 2) put-designation-in-qualifier)
    (simulation-literal (simulation-parenthesized-expression-or-logical-expression 'has 'a 'value)
	     (has-a-value 1))
    
    (simulation-literal ('the 'first 'of 'the 'following expressions-that-has-a 'value
	      simulation-logical-argument-list)
	     (first-that-has-a-value . 8))

    (simulation-literal ( '\( 'if simulation-logical-expression 'then
			 simulation-logical-expression
			 'else simulation-logical-expression '\) )
			(if-expression 3 5 7))
    (simulation-literal ( '\( 'if simulation-logical-expression 'then
			 simulation-logical-expression '\) )
			(if-expression 3 5))

    
    (simulation-literal 
      (simulation-designation 'is relation-name simulation-designation)
      (is-related '3 1 4))
    (simulation-literal 
      (simulation-designation 'is 'not relation-name simulation-designation)
      (is-not-related '4 1 5))

;    (literal (designation 'is 'connected 'to designation)
;	     (is-connected 1 5))
;    (literal (designation 'is 'not 'connected 'to designation)
;	     (is-not-connected 1 6))

    (simulation-literal simulation-designation)
    
    (simulation-qualifier ('has 'a 'value) (has-a-value foo))
    (simulation-qualifier ('has 'no 'value) (has-no-value foo))
    
    (simulation-parenthesized-expression-or-logical-expression
      ('\( simulation-expression '\)) 2)
    (simulation-parenthesized-expression-or-logical-expression
      ('\( simulation-logical-expression '\)) 2)
    (simulation-parenthesized-expression-or-logical-expression
      ('not '\( simulation-logical-expression '\)) (not 3))
    
    (simulation-logical-argument-list ( '\( simulation-logical-expression '\) ) (2))
    (simulation-logical-argument-list ( '\( simulation-logical-expression '\,
				       simulation-logical-argument-list-tail) (2 . 4))
    
    
    (simulation-logical-argument-list-tail (simulation-logical-expression '\) ) (1))
    (simulation-logical-argument-list-tail
      (simulation-logical-expression '\,
				     simulation-logical-argument-list-tail) (1 . 3))
    
    (simulation-designation ('the class local-name 'giving 'the attribute-name
			     'of simulation-designation)
		 (giver-of-value (2 . 3) (5 6 8)))

    (simulation-designation ('the class local-name 'giving 'the class '\:\: attribute-name
			     'of simulation-designation)
		 (giver-of-value (2 . 3) (5 (class-qualified-name 6 8) 10)))
    (simulation-designation ('the 'symbol symbol) (quote 3))

    ))



;; Following is unique version of logical-expression


(add-grammar-rules
  '((unique-logical-expression unique-disjunct)
    (unique-logical-expression (unique-disjunct 'or unique-logical-expression)
			(or 1 3) simplify-associative-operation)
;    (unique-logical-expression unique-designation)
;    (unique-logical-expression v-logical-expression)

    (unique-parenthesized-logical-expression ( '\( unique-logical-expression '\) ) 2)
    (unique-parenthesized-logical-expression ('not '\( unique-logical-expression '\) ) (not 3))

    (unique-disjunct unique-conjunct)
    (unique-disjunct (unique-conjunct 'and unique-disjunct)
	      (and 1 3) simplify-associative-operation)
    
    (unique-conjunct unique-literal)

    (unique-literal (unique-delimited-logical-expression
		      fuzzy-equivicator unique-delimited-logical-expression) (2 1 3))    
    (unique-literal unique-designation)
    (unique-literal ('\( unique-logical-expression '\) ) 2)
    (unique-literal ('not '\( unique-logical-expression '\) ) (not 3))
    
    (unique-literal (function-name '\( r-paren ) (1) check-number-of-args reject-if-sequence-constant)
    (unique-literal (function-name argument-list) (1 . 2) check-number-of-args reject-if-sequence-constant)
    
    (unique-literal (unique-expression fuzzy-comparator unique-expression) (2 1 3))
    (unique-literal (unique-expression '<= unique-expression) (2 1 3))
    (unique-literal (unique-expression '>= unique-expression) (2 1 3))
    (unique-literal (unique-designation unique-qualifier) (1 . 2) put-designation-in-qualifier)
    (unique-literal (unique-parenthesized-expression-or-logical-expression 'has 'a 'value)
	     (has-a-value 1))
    (unique-literal (unique-parenthesized-expression-or-logical-expression 'has 'a 'current 'value)
	     (has-a-current-value 1))
    (unique-literal (unique-parenthesized-expression-or-logical-expression 'has 'no 'value)
		    (has-no-value 1))
    (unique-literal (unique-parenthesized-expression-or-logical-expression
		      'has 'no 'current 'value)
	     (has-no-current-value 1))
    
    (unique-literal ('the 'first 'of 'the 'following expressions-that-has-a 'value
	      unique-logical-argument-list)
	     (first-that-has-a-value . 8))

    (unique-literal
      ('\( 'if unique-logical-expression 'then
       unique-logical-expression 'else unique-logical-expression '\) )
      (if-expression 3 5 7))
    (unique-literal
      ('\( 'if unique-logical-expression 'then unique-logical-expression '\) )
      (if-expression 3 5)
      (restrict-if-slot-edit-feature procedure conditional-expression))

    (unique-literal unique-designation)))

(add-grammar-rules
  '((unique-qualifier ('has 'a 'value) (has-a-value foo))
    (unique-qualifier ('has 'no 'value) (has-no-value foo))
    (unique-qualifier ('has 'a 'current 'value) (has-a-current-value foo))
    (unique-qualifier ('has 'no 'current 'value) (has-no-current-value foo))

    
    (unique-parenthesized-expression-or-logical-expression
      ('\( unique-expression '\)) 2)
    (unique-parenthesized-expression-or-logical-expression
      ('\( unique-logical-expression '\)) 2)
    (unique-parenthesized-expression-or-logical-expression
      ('not '\( unique-logical-expression '\)) (not 3))
    
    (unique-logical-argument-list ( '\( unique-logical-expression '\) ) (2))
    (unique-logical-argument-list ( '\( unique-logical-expression '\,
				       unique-logical-argument-list-tail) (2 . 4))
    
    
    (unique-logical-argument-list-tail (unique-logical-expression '\) ) (1))
    (unique-logical-argument-list-tail
      (unique-logical-expression '\,
				     unique-logical-argument-list-tail) (1 . 3))
    
    (unique-designation ('the class local-name 'giving 'the attribute-name
			     'of unique-designation)
		 (giver-of-value (2 . 3) (5 6 8)))

    (unique-designation ('the class local-name 'giving 'the class '\:\: attribute-name
			     'of unique-designation)
		 (giver-of-value (2 . 3) (5 (class-qualified-name 6 8) 10)))

    ;; changed by ML, 7/9/90 to be unique-expression!
    (unique-delimited-logical-expression unique-designation)
    (unique-delimited-logical-expression ( '\( unique-logical-expression '\) ) 2)

    (user-menu-choice-expression unique-logical-expression)
    (user-menu-choice-expression 'none)		; added. (MHD 7/5/90)

    (user-menu-choice-expression-initialization user-menu-choice-expression)
    ))

;;;; End of GRAMMAR1A



(def-slot-value-compiler unique-logical-expression (parse-result frame)  
  (let* ((*current-computation-frame* frame)
	 (compiled-condition?
	   (compile-expression parse-result nil nil)))
    (if compiled-condition?
	(update-frame-status frame nil nil)
	(update-frame-status frame 'bad nil))
    compiled-condition?))




;;; The system variable `fake-attribute' is a gentemp used in the
;;; user-menu-choice-expression slot-value-compiler.  This prevents any
;;; conflicts with symbols specified in the expression.

(def-system-variable fake-attribute grammar3 (:funcall gentemp "fake-attribute"))


;;; The slot-value-compiler for user-menu-choice-expression tricks the
;;; expression-compiler into not complaining about references to "the item".
;;; "The item" has special meaning in expressions and actions for
;;; user-menu-choices.  It refers to the selected item (i.e., the item
;;; associated with the menu).  

;; This hack was added because user-menu-choice conditions are now being
;; compiled.  10apr90, cpm/agh.

;(def-slot-value-compiler user-menu-choice-expression (parse-result frame)
;  (if (eq parse-result 'none)				; added. (MHD 7/5/90)
;      nil
;      (let* ((*current-computation-frame* frame)
;	     (compiled-condition
;	       (compile-expression parse-result 
;				   (phrase-list 'the fake-attribute
;						(phrase-list 'any 'item)) 
;				   (gensym-list 'item))))
;	(if compiled-condition
;	    (update-frame-status frame nil nil)
;	    (update-frame-status frame 'bad nil))
;	compiled-condition)))

(def-slot-value-compiler user-menu-choice-expression
			 (parse-result user-menu-choice)
  (let* ((*current-computation-frame* user-menu-choice)
	 (current-computation-component-particulars nil)
	 (current-computation-style the-only-dynamic-computation-style)
	 (current-block-of-dependent-frame user-menu-choice)
	 (cell-array? (cell-array user-menu-choice))
	 (expression-cell?
	   (when cell-array?
	     (managed-svref (g2-cell-array-managed-array cell-array?) 0)))
	 (expression? (if (eq parse-result 'none) nil parse-result)))
    (without-consistency-analysis (user-menu-choice)
      (cond
	(expression?
	 (when (not (and cell-array? expression-cell?))
	   (setq cell-array? (make-frame 'g2-cell-array))
	   (change-slot-value user-menu-choice 'cell-array cell-array?)
	   (make-empty-expression-cell cell-array?)
	   (setf expression-cell?
		 (managed-svref (g2-cell-array-managed-array cell-array?) 0))
	   (when (runnable-p user-menu-choice)
	     (activate-g2-cell-array cell-array?)))
	 (with-part-description ((get-default-computation-style-of-class))
	   (register-expression-cell-during-compilation
	     cell-array? 0 t
	     (phrase-list
	       'g2-lambda
	       '((item (class item)))
	       expression?)
	     '(or truth-value (unknown-datum))
	     'item
	     'g2-fake-user-menu-choice-attribute)
	   
	   (cond ((expression-cell-able-to-compute-p expression-cell?)
		  (update-frame-status
		    user-menu-choice
		    (button-frame-status user-menu-choice)
		    nil)
		  t)
		 (t
		  (update-frame-status user-menu-choice 'bad nil)
		  'bad))))
	(t
	 (when cell-array?
	   (when (runnable-p user-menu-choice)
	     (deactivate-g2-cell-array cell-array?))
	   (change-slot-value user-menu-choice 'cell-array nil))
	 (update-frame-status
	   user-menu-choice
	   (button-frame-status user-menu-choice)
	   nil)
	 nil)))))

(def-slot-value-compiler user-menu-choice-expression-initialization
			 (parse-result user-menu-choice)
  (declare (ignore user-menu-choice))
  parse-result)





;;; The transformation-function, `add-layering-preservation-to-show-details'
;;; is used by the show action grammar to add a flag to the show details
;;; of the parse to indicate to the action compiler that the workspace should
;;; not be raised to the top, but should maintain its current layering position.

(defun add-layering-preservation-to-show-details (parse)
  (setf (cddr parse) (phrase-cons t (cddr parse)))
  parse)







;;;; Grammar for statements



(add-grammar-rules
  '(

; Has a history is commented out because there is no evaluator has-history.
; If there is one, there should also be has-no-history

; If these are ever put back in, one must make unique- and possibly simulation-
; versions of them. See me. ML. 16 Aug, 1988

;    (qualifier ('has 'a 'history 'during 'the 'last interval) (has-history foo 7))
;    (qualifier ('has 'no 'history 'during 'the 'last interval) (has-no-history foo 7))
;
;    (qualifier ('has 'a 'history 'between interval 'ago 'and interval 'ago)
;	       (has-history foo 5 8))
;    (qualifier ('has 'no 'history 'between interval 'ago 'and interval 'ago)
;	       (has-no-history foo 5 8))

    (designation ('any class local-name) (1 (2 . 3)))

    (fuzzy-comparator '=)			; If this list changes, so must
    (fuzzy-comparator '/=)			;   the fuzzy-comparator-reparser
    (fuzzy-comparator '<)			;   function written below.
    (fuzzy-comparator '>)

    (comparator '=)
    (comparator '/=)
    (comparator '<)
    (comparator '<=)
    (comparator '>)
    (comparator '>=)



    ;; An `event-antecedent' is a logical expression whose first conjunct is an
    ;; `event-logical-expression', and whose further conjuncts are logical
    ;; expressions.  An event-logical-expression is a disjunct of
    ;; event-literals.

    (event-antecedent event-logical-expression)
    (event-antecedent (event-logical-expression 'and 'when logical-expression)
		      (and 1 4) simplify-associative-operation)

    (event-logical-expression event-disjunct)
    (event-logical-expression (event-disjunct 'or event-logical-expression)
			      (or 1 3) simplify-associative-operation)

    (event-disjunct event-literal)

    (event-literal (designation 'receives 'a 'value) (receives-a-value 1))
    (event-literal (designation 'fails 'to 'receive 'a 'value)
		   (fails-to-receive-a-value 1))
    (event-literal (designation 'is 'moved) (is-moved 1))
    (event-literal (designation 'is 'moved 'by 'the 'user)
		   (is-moved-by-the-user 1))
    (event-literal (designation 'is 'moved 'by 'g2) (is-moved-by-g2 1))
    (event-literal (designation 'is 'resized 'by 'the 'user) (is-resized-by-the-user 1))
    (event-literal (designation 'becomes relation-name designation)
		   (becomes-related '3 1 4))
    (event-literal (designation 'ceases 'to 'be relation-name designation)
		   (ceases-to-be-related '5 1 6))

    (event-literal (designation 'is 'activated)
                   (is-activated 1))
    (event-literal (designation 'is 'deactivated)
                   (is-deactivated 1))
    (event-literal (designation 'is 'enabled)
                   (is-enabled 1))
    (event-literal (designation 'is 'disabled)
                   (is-disabled 1))
    (event-literal (designation 'loses 'its 'value)
                   (loses-its-value 1))

    ;; The following grammar for detecting when instances are created is
    ;; intended to be consistent with the create action grammar.
    (event-literal ('any 'instance 'of class 'is 'created)
                   (is-created (any 4)))
    (event-literal ('any 'instance 'of class local-name 'is 'created)
                   (is-created (any (4 . 5))))

;    (event-literal ('an 'instance 'of 'the 'class 'named 'by
;                    unique-expression 'is 'created)
;                   (is-created-indirect 8))
   
    (event-literal (designation 'becomes 'related 'to designation)
		   (generic-becomes-related 1 5))
    (event-literal (designation 'ceases 'to 'be 'related 'to designation)
		   (generic-ceases-to-be-related 1 7))

    ;; The following grammar for detecting when connections are created and
    ;; broken is intended to be consistent with the create connection action
    ;; grammar.

    (event-literal (event-connection-designation 'is 'directly 'connected 'to designation)
                   (generic-directly-connected-to 1 'no-filter 6))
    (event-literal (event-connection-designation 'is 'directly 'connected 'to
		    connection-target-filter designation)
                   (generic-directly-connected-to (any connection) '6 7))
    
;    (event-literal ('a 'connection 'is 'directly 'connected 'to
;		    designation)
;                   (generic-directly-connected-to (any connection) 'no-filter 7))
;    (event-literal ('a 'connection 'is 'directly 'connected 'to
;		    connection-target-filter designation)
;                   (generic-directly-connected-to (any connection) '7 8))
    
    (event-literal ('a 'connection 'is 'directly 'disconnected 'from
		    designation)
                   (generic-directly-disconnected-from 'no-filter 7))
    (event-literal ('a 'connection 'is 'directly 'disconnected 'from
		    connection-target-filter designation)
                   (generic-directly-disconnected-from '7 8))

    (event-literal ('a 'connection simple-connection-class-specifier
		    'is 'directly 'connected 'to designation)
                   (directly-connected-to (any 3) 'no-filter 8))
    (event-literal ('a 'connection simple-connection-class-specifier
		    'is 'directly 'connected 'to connection-target-filter designation)
                   (directly-connected-to (any 3) '8 9))
    (event-literal ('a 'connection simple-connection-class-specifier
		    'is 'directly 'disconnected 'from
		    designation)
                   (directly-disconnected-from (quote 3) 'no-filter 8))
    (event-literal ('a 'connection simple-connection-class-specifier
		    'is 'directly 'disconnected 'from
		    connection-target-filter designation)
                   (directly-disconnected-from (quote 3) '8 9))
    (event-literal ('a 'connection local-name simple-connection-class-specifier
		    'is 'directly 'connected 'to designation)
                   (directly-connected-to (any (4 . 3)) 'no-filter 9))
    (event-literal ('a 'connection local-name simple-connection-class-specifier
		    'is 'directly 'connected 'to connection-target-filter designation)
                   (directly-connected-to (any (4 . 3)) '9 10))

    (event-connection-designation ('a 'connection) (any 2))
    (event-connection-designation ('a 'connection local-name) (any (2 . 3)))

    (simple-connection-class-specifier
      ('of 'class connection-class) 3)

    (connection-target-filter (port-name 'of) 1)
    (connection-target-filter ('an 'input 'to) at-an-input)
    (connection-target-filter ('an 'output 'of) at-an-output)

    (event-literal (designation 'is 'connected 'to designation)
                   (indirectly-connected-to 1 5))
    (event-literal (designation 'is 'disconnected 'from
		    designation)
                   (indirectly-disconnected-from 1 5))

    
    

    ;; In the target G2 when a NUPEC synchronization has finished, the event
    ;; proposition "whenever nupec synchronization occurs..." should be
    ;; executed.

;;   Moved to authorize-nupec.  cpm, 3/15/91
;    #+nupec
;    (event-literal ('nupec 'synchronization 'occurs)
;		   (nupec-synchronization-occurs))

    ;; An `expression' is something that can denote a value which is a datum.
    ;; It is a candidate first argument for datum-evaluate. A datum can be a
    ;; number, a truth-value, a symbol, and presently some other things.

    ;; A `designation' as used here is an expression for denoting primarily an
    ;; entity. Grammatically, designation is a subset of expression.


    ;; Consider having a let or where operation as a general feature of
    ;; expressions.
    ;;
    ;; At the moment the only kinds of roles that we have available are class
    ;; name driven roles and attribute name roles.  So, in order to not present
    ;; the menu choice "role-name" to users, the category attribute-name was
    ;; used to replace role-name.  This may need to change in the future, but
    ;; the documentation should also change at that time.  -jra, ml, mwa
    ;; 10/13/87

    (quantifier 'the)
    (quantifier 'any)
    (unique-quantifier 'the)

    (simulation-quantifier 'the)

    ;; Upon extending the syntax of QUANTIFIER or DESIGNATION, fix up the definition 
    ;; of the macro DESIGNATION-P in file COMPILE1.

    ;; Upon adding any new designations or non-atomic roles, the ability to
    ;; print them should be added to PRINT-DESIGNATION and PRINT-ROLE in file EVAL.

    ;; Consider putting exponentiation as an infix operator.

    (function-name 'average)			; these need to be explicit because
    (function-name 'hour)			;   they are reserved words, at present
    (function-name 'minute)			; NOTE: If you add any more function names
    (function-name 'second)			;   here, you must add them to the quoted
    (function-name 'symbol)			;   list in add-menu-items-for-category
						;   in module PARSE!!! (MHD/BAH 8/28/91)


    (function-name unreserved-symbol)

    ;; Simultaneous actions:
    (action-list (action 'and action-list-3) (and 1 3) simplify-associative-operation)
    (action-list action)

    (action-list-3 (action 'and action-list-3) (and 1 3) simplify-associative-operation)
    (action-list-3 action)
    
    ;; In order actions:
    (action-list ('in 'order action) (in-order 3))
    (action-list ('in 'order action-list-1) (in-order 3) fix-in-order-action-list)

    (action-list-1 (action 'and action-list-2)
		   (and 1 3) simplify-associative-operation)
    (action-list-2 (action 'and action-list-2)
		   (and 1 3) simplify-associative-operation)
    (action-list-2 action)

;; This modification to "conclude" grammar rules supports the new conclude options
;; of expiration and collection times.  7/14/89, cpm.

    (conclude-time ('with 'expiration unique-expression) 
			  (3 nil nil nil)) 
    (conclude-time ('with 'collection 'time unique-expression)
			  (nil 4 nil nil))
    (conclude-time ('with 'expiration unique-expression 'with
				  'collection 'time unique-expression) 
			  (3 7 nil nil)) 
    (conclude-time ('with 'collection 'time unique-expression 'with
				  'expiration unique-expression) 
			  (7 4 nil nil))

    ;; GENSYMCID-1331: Implement KB level atomic CONCLUDE for SymScale
    (conclude-time ('compare unique-expression) (nil nil 2 nil))
    (conclude-time ('compare unique-expression 'resulting local-name) (nil nil 2 4))
    
;    (action ('conclude 'that e-designation) (conclude 3))
;    (action ('conclude 'that 'not e-designation) (conclude-not 4))
;    (action ('conclude 'that e-designation 'is 'false) (conclude-not 3))
;    (action ('conclude 'that e-designation 'is 'true) (conclude 3))


    (action ('conclude 'that e-designation 'has 'no 'current 'value)
	    (conclude-has-no-current-value 3))
    (action ('conclude 'that e-designation 'has 'no 'value)
	    (conclude-has-no-value 3))
    (action ('conclude 'that e-designation 'does 'not 'exist)
	    (conclude-has-no-value 3))

;    (action ('conclude 'that e-designation '= unique-expression) (conclude 3 5))
;    (action ('conclude 'that e-designation '=
;	     unique-parenthesized-logical-expression) (conclude 3 5))
;    (action ('conclude 'that e-designation 'is symbol) (conclude 3 '5)
;	    symbol-cannot-be-true-false-or-not)



    (action ('conclude 'that e-designation) (conclude 3 nil nil nil nil nil))
    (action ('conclude 'that 'not e-designation)
            (conclude-not 4 nil nil nil nil))
    (action ('conclude 'that e-designation 'is 'false)
            (conclude-not 3 nil nil nil nil))
    (action ('conclude 'that e-designation 'is 'true)
            (conclude 3 nil nil nil nil nil))


    (action ('conclude 'that e-designation '= unique-expression)
	    (conclude 3 5 nil nil nil nil))
    (action ('conclude 'that e-designation '= unique-literal)
	    (conclude 3 5 nil nil nil nil))
    (action ('conclude 'that e-designation 'is standard-or-class-qualified-symbol) 
	    (conclude 3 '5 nil nil nil nil)
	    symbol-cannot-be-true-false-or-not)

    (action ('conclude 'that e-designation conclude-time) (conclude 3 nil . 4))
    (action ('conclude 'that 'not e-designation conclude-time)
            (conclude-not 4 . 5))
    (action ('conclude 'that e-designation 'is 'false conclude-time)
            (conclude-not 3 . 6))
    (action ('conclude 'that e-designation 'is 'true conclude-time)
            (conclude 3 nil . 6))

    (action ('conclude 'that e-designation '= unique-expression conclude-time)
	    (conclude 3 5 . 6))
    (action ('conclude 'that e-designation '=
	     unique-literal conclude-time)
	    (conclude 3 5 . 6))
    (action ('conclude 'that e-designation 'is symbol conclude-time) 
	    (conclude 3 '5 . 6)
	    symbol-cannot-be-true-false-or-not)



    (action ('focus 'on e-designation) (focus 3 nil))
    (action ('invoke category-list the-word-rules)
     (invoke 2 nil nil) category-hack)
    (action ('invoke category-list the-word-rules 'for e-designation)
     (invoke 2 5 nil) category-hack)

    ;; Special form of invoke only applicable to procedures
    (proc-specific-action
     ('invoke category-list the-word-rules '\, 'awaiting 'completion)
     (invoke 2 nil t)
     category-hack)
    (proc-specific-action
     ('invoke category-list the-word-rules 'for e-designation '\,
      'awaiting 'completion)
     (invoke 2 5 t)
     category-hack)

    ;; Special form of focus only available to procedures
    (proc-specific-action
     ('focus 'on e-designation '\, 'awaiting 'completion)
     (focus 3 t))

;    (action ('break whole-string))

    (action ('halt 'with whole-string 'if 'breakpoints 'are 'enabled) (halt 3))
    (action ('halt 'if 'breakpoints 'are 'enabled) (halt))
    
    ;; Temporarily, the destinations for an inform are restricted to their being one!!!
    ;; ML, 29 Oct. 87. (But this designation may have an "every" iterator".)

    (action ('inform e-designation 'that message-text)
	    (inform 2 4))

    (action ('inform e-designation inform-features 'that message-text)
	    (inform 2 5 . 3))

    (action ('inform 'the 'operator 'that message-text)
	    (inform (the operator) 5))

    (action ('post message-text)
	    (inform (the operator) 2))

    (action ('post inform-duration-feature message-text)
     (inform (the operator) 3 . 2))
     

    (action ('inform 'the 'operator inform-features 'that message-text)
	    (inform (the operator) 6 . 4))

    (inform-features inform-on-feature)
    (inform-features (inform-on-feature inform-features-1) (1 . 2) unlist-1)
    (inform-features inform-features-1)

    (inform-features-1 inform-near-feature)
    (inform-features-1 inform-duration-feature)
    (inform-features-1 (inform-near-feature inform-duration-feature) (1 2) unlist-1-2)

    (inform-duration-feature ('for 'the 'next interval) ((duration 4)) car-2-1)

    (inform-on-feature ('on unique-designation) ((on 2)))

    (inform-near-feature (below-or-above unique-designation) ((1 2)))

    (below-or-above 'below)
    (below-or-above 'above)

;    (action ('inform e-designation 'for 'the 'next interval 'that message-text)
;	    (inform 2 8 (duration 6)) fix-duration)


;    (action ('inform 'the 'operator 'for 'the 'next interval 'that message-text)
;	    (inform (the operator) 9 (duration 7)) fix-duration) 


;    (action ('inform designation 'that message-text inform-options)
;	    (inform 2 4 . 5))

;    (action ('inform designation-list 'for 'the 'next interval 'that
;	     message-text inform-options)
;	    (inform 2 8 (duration 6) . 9) fix-duration)
    (action ('set e-designation 'to unique-expression) (set 2 4))

    (action ('activate 'the 'subworkspace 'of e-designation) (1 5))
    (action ('deactivate 'the 'subworkspace 'of e-designation) (1 5))

;    (action ('show e-designation))
;    (action ('show e-designation in-window-designation))
;    (action ('show e-designation scaling-details))
;    (action ('show e-designation in-window-designation scaling-details))
;    (action ('show e-designation screen-positioning-details))
;    (action ('show e-designation in-window-designation screen-positioning-details))
;    (action ('show e-designation
;             scaling-details workspace-positioning-details
;             screen-positioning-details))

    ;; The show action has three major optional details.  The three details
    ;; in-window-designation (w), scaling-details (s), and positioning-details
    ;; (p), are all optional, and, where they appear, must be in this order:
    ;;
    ;;   wsp
    ;;
    ;; This gives rise to the following combinations:
    ;; 
    ;;    - w ws wp wsp s sp p

    ;; Added grammar for preserving the current layering of the workspace.
    ;; The default behavior is to bring the workspace to the top.  (ghw 5/8/98).

    (action ('show e-designation)
     (show-new 2))

    ; w
    (action
     ('show e-designation in-window-designation)
     (show-new 2 3))

    ; ws
    (action ('show e-designation in-window-designation scaling-details)
     (show-new 2 3 4))
    (action ('show e-designation in-window-designation scaling-details
	     'preserving 'workspace 'layering)
     (show-new 2 3 4) add-layering-preservation-to-show-details)

    ;wp
    (action ('show e-designation in-window-designation positioning-details)
     (show-new 2 3 . 4))
    (action ('show e-designation in-window-designation positioning-details
	     'preserving 'workspace 'layering)
     (show-new 2 3 . 4) add-layering-preservation-to-show-details)

    ;wsp
    (action ('show e-designation in-window-designation scaling-details positioning-details)
     (show-new 2 3 4 . 5))
    (action ('show e-designation in-window-designation scaling-details positioning-details
	     'preserving 'workspace 'layering)
     (show-new 2 3 4 . 5) add-layering-preservation-to-show-details)

    ;s
    (action
     ('show e-designation scaling-details)
     (show-new 2 3))
    (action
     ('show e-designation scaling-details 'preserving 'workspace 'layering)
     (show-new 2 3) add-layering-preservation-to-show-details)

    ;sp
    (action ('show e-designation scaling-details positioning-details) ; screen and workspace
     (show-new 2 3 . 4))
    (action ('show e-designation scaling-details positioning-details ; screen and workspace
	     'preserving 'workspace 'layering)
     (show-new 2 3 . 4) add-layering-preservation-to-show-details)

    ;p
    (action ('show e-designation positioning-details)
     (show-new 2 . 3))
    (action ('show e-designation positioning-details
	     'preserving 'workspace 'layering)
     (show-new 2 . 3) add-layering-preservation-to-show-details)

    ;; Note: positioning-details includes both workspace and screen positioning
    ;; details.  They are listed.  Workspace-positioning details are optional.
    ;; If they are provided, screen-positioning details are required.
    ;; Otherwise, screen-positioning details are just provided alone.  The
    ;; grammar is further below.
    
    (action ('hide e-designation))
    (action ('hide e-designation in-window-designation))
    
    (action ('conclude 'that e-designation 'is relation-name e-designation)
	    (add-relation 5 3 6))
    (action ('conclude 'that e-designation 'is 'not relation-name e-designation)
	    (remove-relation 6 3 7))

    (action ('conclude 'that e-designation 'is 'now relation-name e-designation)
	    (add-relation 6 3 7 now))

    ;; New actions for G2 version 3.0: abort, shut down, reset, pause, and print.
    (action ('abort e-designation) (1 2))
    (action ('shut 'down 'g2) (shut-down-g2))
    (action ('reset 'knowledge-base) (reset-kb))
    (action ('pause 'knowledge-base) (pause-kb))
    (action ('print e-designation))
    
    #+development
    (action ('start 'knowledge-base) (start-kb))

    #+development
    (action ('resume 'knowledge-base) (resume-kb))    
    
    (in-window-designation ('on window-designation) (in 2))
    ;; Can't use 'in here because this will result in ambiguity with
    ;; 'in as used for lists.  For example, in "show every pump in foo"
    ;; there is an ambiguity as to whether foo designates a list or a g2-window.

    (window-designation e-designation)



    ;; New grammar for 4.0, positioning-details, combines workspace and
    ;; screen positioning details into one:
    (positioning-details screen-positioning-details (1))
    (positioning-details
     (workspace-positioning-details screen-positioning-details)
     (1 2))     
    

    ;; This new grammar for 4.0 enables language like
    ;;   show ... with (x-in-workspace, y-in-workspace)
    ;;     at (x-in-window, y-in-window)
    (workspace-positioning-details
      ('with 'focal 'point '\( unique-expression '\, unique-expression '\) )
      (workspace-position (5 7)))
    (screen-positioning-details
      ('at  '\( unique-expression '\, unique-expression '\) 'in 'the 'screen)
      (screen-position (at 3 5)))
    
    
    


    (scaling-details
      scaling-subdetails
      (scale 1))
    
    ;; scaling subdetails can yield a parse result of one
    ;; of the folling:
    ;;
    ;;   ONE-QUARTER
    ;;   HALF
    ;;   THREE-QUARTER
    ;;   FULL
    ;;   (FULL <numeric expression>)     ; scale covers both x
    ;;   (CURRENT <numeric expression>)  ;   and y
    ;;   (FULL <numeric expression> <numeric expression>)     ; individual x
    ;;   (CURRENT <numeric expression> <numeric expression>)  ;   and y scales

    (scaling-subdetails
     ('at scale-spec 'scale)
     2)
    (scale-spec 'one-quarter)
    (scale-spec 'half)
    (scale-spec 'three-quarter)
    (scale-spec 'full)
    
    (scaling-subdetails
     ('scaled 'by scale-factor-spec)
     (full . 3))
    (scaling-subdetails
     ('scaled 'by 'its 'current 'scale 'times scale-factor-spec)
     (current . 7))
    (scale-factor-spec
     unique-expression
     (1))
    (scale-factor-spec
     ('\( unique-expression '\, unique-expression '\))
     (2 4))
    

    (screen-positioning-details
      (location-preposition 'the reference-point-details 'of 'the 'screen)
      (screen-position 1 3))
    
    (reference-point-details 'center)
    (reference-point-details (center-details 'center))
    (reference-point-details (corner-details 'corner) 1)

    (hand-side 'left)
    (hand-side 'right)
    
    (top-or-bottom 'top)
    (top-or-bottom 'bottom)
    
    (center-details hand-side)
    (center-details top-or-bottom)
    
    (corner-details (top-or-bottom hand-side))

    (location-preposition 'at)
    (location-preposition offset-spec)

    (offset-spec
      (offset-units horizontal-direction)
      (2 1))
    (offset-spec
      (offset-units vertical-direction)
      (2 1))
    (offset-spec
      (offset-units horizontal-direction 'and offset-units vertical-direction)
      (2 1 5 4))

    ;; This new grammar for 4.0 replaces the grammar rule
    ;;    (offset-units (integer 'units) 1)
    ;; prior to 11/4/93, prior to 4.0.  It enables expressions
    ;; to be evaluated where only numbers could appear previously.
    (offset-units (unique-expression 'units) 1)
    
    (vertical-direction 'above)
    (vertical-direction 'below)
    (horizontal-direction ('to 'the hand-side 'of) 3)





    (workspace-positioning-details
      ('with 'its reference-point-details)
      (workspace-position 3))
    






;    (inform-options ('with 'details 'being 'to 'display designation)
;		    ((details (display 6))))
;    (inform-options ('with 'details 'being 'to 'graph designation-list)
;		    ((details (graph 6))))
;    (inform-options ('with 'details 'being 'to 'display designation 'and
;		     'to 'graph designation-list)
;	     ((details (display 6) (graph 10))))

    (message-text whole-string)
    (message-text (left-string open-message-text) (and 1 2) simplify-associative-operation)

    (open-message-text (message-expression right-string)
		       (and 1 2) simplify-associative-operation)
    (open-message-text (message-expression message-text-tail)
		       (and 1 2) simplify-associative-operation)

    (message-text-tail (middle-string open-message-text)
		       (and 1 2) simplify-associative-operation)

;    (left-string string)
;    (right-string string)
;    (middle-string string)

    (message-expression unique-expression)


    ;; "a-or-an" in the following two rules used to be 'a and 'an, respectively,
    ;; but that was too cute; when users selected "an" they would get a different
    ;; grammar than if they had selected "a", since the two rules contributed
    ;; different endings following "a" and "an".  (MHD 1/11/91)
    (message-expression
      (unique-expression 'as a-or-an 'time 'stamp) (format 1 'time-stamp))
    (message-expression
      (unique-expression 'as a-or-an 'interval) (format 1 'seconds))
    (message-expression
      (unique-expression 'as ddd.dddd-format) (ddd.dddd-format 1 3) check-ddd-dddd-format)

    ;; Removed -- was redundant with ddd.dddd-format.  Usage replaced with
    ;; ddd.dddd-format for above message-expression grammar and also for
    ;; the format-expression grammar. (MHD 11/8/04)
;    (format unreserved-symbol)

;    (message-expression ('the 'name 'of designation) (name 4))

;    (designation-list designation)
;    (designation-list (designation 'and designation) (and 1 3))
;    (designation-list (designation '\, designation-list-tail)
;		   (and 1 3) simplify-associative-operation)
;
;    (designation-list-tail (designation '\, 'and designation) (and 1 4))
;    (designation-list-tail (designation '\, designation-list-tail)
;			(and 1 3) simplify-associative-operation)

    (send-list (whole-string '\, send-list) (and 1 3) simplify-associative-operation)

    (ddd.dddd-format unreserved-symbol)
   
;    (destination-list destination)
;    (destination-list (destination 'and destination) (and 1 3))
;    (destination-list (destination '\, destination-list-tail)
;		   (and 1 3) simplify-associative-operation)
;
;    (destination-list-tail (destination '\, 'and destination) (and 1 4))
;    (destination-list-tail (destination '\, destination-list-tail)
;			(and 1 3) simplify-associative-operation)

    (destination unreserved-symbol)
    (destination ('the unreserved-symbol) 2)

    (category-list rule-category-name)
    (category-list (rule-category-name 'and rule-category-name) (and 1 3))
    (category-list (rule-category-name '\, category-list-tail)
		   (and 1 3) simplify-associative-operation)

    (category-list-tail (rule-category-name '\, 'and rule-category-name) (and 1 4))
    (category-list-tail (rule-category-name '\, category-list-tail)
			(and 1 3) simplify-associative-operation)

    (rule-category-name unreserved-symbol)

    (port-name unreserved-symbol)

    ))





;;; The open category `ddd.dddd-format', which is defined as unreserved-symbol,
;;; has a registered name directory, since it wants to be prompted for
;;; explicitly.  In fact, there is no facility to record any local names (i.e.,
;;; used as local variables in rules or procedures).  The spelling pattern of
;;; the symbol determines if it's acceptable and, if so, its meaning.

;;; Similarly, the open category `rule-category-name' has a registered name
;;; directory.  It is also defined as unreserved-symbol.  It is a true directory
;;; of names, and does get instances.  However, it should be prompted for
;;; whether or not there are instances in the directory.

(def-registered-directory-of-names ddd.dddd-format)
(def-registered-directory-of-names rule-category-name)

;; Note that "directory of names" is really a misnomer in this case.  Consider
;; renaming the term "registered open category" or something.  (MHD 11/8/04)

;; Above defs added to fix bug bug HQ-4753913 "wrong category menu displayed
;; sometimes" (and related bug HQ-951010 "Prompting: editor only prompts for
;; relation names if one exists"). (MHD 11/8/04)






(defun-for-system-procedure add-generic-rule-grammar ()
  (with-permanent-gensym-float-creation
    (add-grammar-rules
      '((event-literal
	 (designation 'has a-or-an unreserved-symbol 'event)
	 (generic-event 1 '4 (any item)))
	(event-literal
	 (designation 'has a-or-an unreserved-symbol 'event local-name)
	 (generic-event 1 '4 (any (item . 6))))))
    (copy-evaluation-truth-value evaluation-true-value)))


(defun-for-system-procedure extend-action-grammar ()
  (with-permanent-gensym-float-creation
    (add-grammar-rules
      '((action ('start 'knowledge-base) (start-kb))
	(action ('resume 'knowledge-base) (resume-kb)))))
      (copy-evaluation-truth-value evaluation-true-value))



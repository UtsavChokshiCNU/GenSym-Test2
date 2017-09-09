;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module GRAMMAR1

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Michael Levin and Mark H. David



;;; To GRAMMAR2


;;;; Parallel grammar facility




(defmacro add-parallel-grammar-rules (list-of-parallel-grammars
				       categories-for-parallel-grammars
				       &body grammar-rules)
  (loop with list-of-prefixes =
	  (loop for grammar in list-of-parallel-grammars collecting (symbol-name grammar))
	for rule in grammar-rules
	nconcing
	  (cons
	    rule
	    (loop for prefix in list-of-prefixes
		  nconcing
		    (if (or (memq (car rule) categories-for-parallel-grammars)
			    (if (symbolp (second rule))
				(memq (second rule) categories-for-parallel-grammars) 
				(loop for constituent in (second rule)
				      thereis
					(memq constituent
					      categories-for-parallel-grammars))))
			(list
			  (list*
			    (if (memq (car rule) categories-for-parallel-grammars)
				(intern (format nil "~A~A" prefix
						(symbol-name (car rule))))
				(car rule))
			    
			    (if (symbolp (second rule))
				(if (memq (second rule)
					  categories-for-parallel-grammars)
				    (intern (format nil "~A~A" prefix
						    (symbol-name (second rule))))
				    (second rule))
				(loop for constituent in (second rule)
				      collecting				   
					(if (memq
					      constituent
					      categories-for-parallel-grammars)
					    (intern (format nil "~A~A" prefix
							    (symbol-name constituent)))
					    constituent)))
			    (cddr rule)))))) into result
	finally (return `(add-grammar-rules  ',result))))




(add-grammar-rules
  '((standard-or-class-qualified-symbol (class '\:\: attribute-name)
     (class-qualified-name 1 3)
     convert-class-qualified-list-to-keyword-symbol)
    (standard-or-class-qualified-symbol symbol)
    (standard-or-class-qualified-symbol? standard-or-class-qualified-symbol)
    (standard-or-class-qualified-symbol? 'none)
    (class-qualified-method (class '\:\: method-name)
     (class-qualified-name 1 3)
     convert-class-qualified-list-to-keyword-symbol)))








;;;; Statement and expression grammar



(defun filter-out-the-text-of-as-a-special-case (form)
  (let* ((role (role-of-designation form))
	 (role-is-simple? (simple-role-p role))
	 (simple-role (if role-is-simple?
			  role
			  (simple-role-of-role role))))
    (if (eq simple-role 'text)
	bad-phrase
	form)))

(declare-grammar-transform-can-return-bad-phrase filter-out-the-text-of-as-a-special-case)


(defun filter-out-region-icon-color (form)
  (let* ((role (role-of-designation form))
	 (role-is-simple? (simple-role-p role))
	 (local-name? (and (not role-is-simple?)
			   (get-explicitly-specified-local-name-of-role-if-any
			     role))))
    (if (or (eq local-name? 'icon-color)	    
	    (eq local-name? 'stripe-color))
	bad-phrase
	form)))

(declare-grammar-transform-can-return-bad-phrase filter-out-region-icon-color)


(defun filter-out-the-text-of-and-region-icon-color (form)
  (let* ((role (role-of-designation form))
	 (role-is-simple? (simple-role-p role))
	 (simple-role (if role-is-simple?
			  role
			  (simple-role-of-role role)))
	 (local-name? (and (not role-is-simple?)
			   (get-explicitly-specified-local-name-of-role-if-any
			     role))))
    (if (or (eq simple-role 'text)
	    (eq local-name? 'icon-color)
	    (eq local-name? 'stripe-color))
	bad-phrase
	form)))

(declare-grammar-transform-can-return-bad-phrase filter-out-the-text-of-and-region-icon-color)





(add-parallel-grammar-rules (unique- simulation-)
			    (expression
			      sum sum-1 signed-sum term signed-term
			      term-or-signed-term term-1
			      exponential series-of-exponentials
			      operator-and-exponential
			      factor designation quantifier
			      argument-list conditional-expression
			      argument-list-tail
			      class-phrase-role preposition
			      ago-interval last-interval
			      expression-or-logical-expression
			      logical-expression)

  (expression sum)
  
  (sum term-or-signed-term)
  (sum (term-or-signed-term '+ sum-1) (+ 1 3) transpose-sum)
  (sum (term-or-signed-term '- sum-1) (- 1 3) transpose-sum)

  (sum-1 term)
  (sum-1 (term '+ sum-1) (|+plus+| 1 3))
  (sum-1 (term '- sum-1) (|-minus-| 1 3))
  
  (term-or-signed-term term)
  (term-or-signed-term signed-term)
  
  (signed-term ('+ term) 2)
  (signed-term ('- term) (- 2))


  (term exponential)
  (term (exponential '* term-1) (* 1 3) transpose-term)
  (term (exponential '/ term-1) (/ 1 3) transpose-term)

  (term-1 exponential)
  (term-1 (exponential '* term-1) (|*times*| 1 3))
  (term-1 (exponential '/ term-1) (|/slash/| 1 3))

  (exponential factor)
  (exponential (factor '^ factor) (^ 1 3))
  
  (factor designation)
  (factor color-factor)
  (factor ( '\( conditional-expression '\) ) 2)  
  
  (factor (function-name '\( r-paren )
	  (1)
	  check-number-of-args
	  reject-if-sequence-constant)
  (factor (function-name argument-list)
	  (1 . 2)
	  check-number-of-args
	  reject-if-sequence-constant)

  (factor ('structure '\( r-paren )
	  (evaluated-structure)
	  reject-if-structure-constant)
  (factor ('structure structure-argument-list)
	  (evaluated-structure . 2)
	  reject-if-structure-constant)
  
  (factor ('the 'current 'time) (current-time))
  (factor ('the 'current 'real 'time) (current-real-time))
  (factor ('the 'current 'subsecond 'time) (current-subsecond-time))
  (factor ('the 'current 'subsecond 'real 'time) (current-subsecond-real-time))
  (factor ('the 'current 'system 'time) (current-system-time))
  (factor ('the 'current 'system 'real 'time) (current-system-real-time))
  (factor ('the 'current 'year) (year (current-time)))
  (factor ('the 'current 'month) (month (current-time)))
  (factor ('the 'current 'day 'of 'the 'month)
	  (day-of-the-month (current-time)))
  (factor ('the 'current 'day 'of 'the 'week) (day-of-the-week (current-time)))
  (factor ('the 'current 'hour) (hour (current-time)))
  (factor ('the 'current 'minute) (minute (current-time)))
  (factor ('the 'current 'second) (second (current-time)))
  
  (factor ('the 'first 'of 'the 'following expressions-that-has-a
	   'value argument-list)
	  (first-that-has-a-value . 8))

  (factor ('the 'interpolated 'value 'of designation 'as 'of
	   ago-interval 'ago) (interpolated-value 5 8))
  
  (factor ('the 'value 'of designation 'as 'of
	   ago-interval 'ago) (historic-value 4 7))

  (factor ('the 'value 'of designation 'as 'of 
	   previous-datapoint-expression datapoint-or-datapoints 'ago)
	  (value-of-previous-datapoint 4 7))

  (factor ('the 'collection 'time 'of designation 'as 'of 
	   previous-datapoint-expression datapoint-or-datapoints 'ago)
	  (collection-time-of-previous-datapoint 5 8))

  ;;; The three forms of history intervals in the following grammar are:
  ;;;
  ;;; (1) during the last <time-interval>
  ;;; (2) between <time-interval> ago and <time-interval> ago
  ;;; (3) during the <time-interval> ending with the collection time
  ;;;
  ;;; For ease of implementation, form (3) has been implemented in a way
  ;;; that produces the same parse result as the otherwise meaningless
  ;;; grammar  "between <time-interval> ago and true ago".  As a result,
  ;;; entering this grammar in the editor, which previously was an error
  ;;; since the second time-interval would have had to evaluate to a
  ;;; quantitative expression, will now result in this being interpreted
  ;;; as though the user had typed "during the <time-interval> ending
  ;;; with the collection time".
  ;;;
  ;;; Another way to implement this might be using an additional
  ;;; argument and have `def-history-special-form-converter' in
  ;;; stack-eval1.lisp sort it out but this was considered to be
  ;;; too complex to attempt at this time.  We also did not want to
  ;;; add seven new def-funcalled-instructions for the new form (3).
  ;;; The best approach may be to use grammar transformations and
  ;;; restrictions as in grammar3.lisp.  This should be looked into.
  ;;; We can document what "between <time-interval> ago and true ago"
  ;;; now does if that seems necessary. - jpg 2/9/07

  (factor ('the 'maximum 'value 'of designation 'during 'the 'last 
	   last-interval) (maximum-value 5 9))
  
  (factor ('the 'maximum 'value 'of designation 'during 'the ago-interval 
	   'ending 'with 'the 'collection 'time) (maximum-value 5 8 true))

  (factor ('the 'maximum 'value 'of designation 'between
	   ago-interval 'ago 'and ago-interval 'ago) (maximum-value 5 7 10))

  (factor ('the 'minimum 'value 'of designation 'during 'the 'last  
	   last-interval) (minimum-value 5 9))
  
  (factor ('the 'minimum 'value 'of designation 'during 'the ago-interval 
	   'ending 'with 'the 'collection 'time) (minimum-value 5 8 true))

  (factor ('the 'minimum 'value 'of designation 'between
	   ago-interval 'ago 'and ago-interval 'ago) (minimum-value 5 7 10))
  
  (factor ('the 'average 'value 'of designation 'during 'the 'last 
	   last-interval) (average-value 5 9))

  (factor ('the 'average 'value 'of designation 'during 'the ago-interval  
	   'ending 'with 'the 'collection 'time) (average-value 5 8 true))
  
  (factor ('the 'average 'value 'of designation 'between
	   ago-interval 'ago 'and ago-interval 'ago) (average-value 5 7 10))

  (factor ('the 'sum 'of 'the 'values 'of designation 'during 'the 'last 
	   last-interval) (sum-of-values 7 11))

  (factor ('the 'sum 'of 'the 'values 'of designation 'during 'the ago-interval
	   'ending 'with 'the 'collection 'time) (sum-of-values 7 10 true))
  
  (factor ('the 'sum 'of 'the 'values 'of designation 'between
	   ago-interval 'ago 'and ago-interval 'ago) (sum-of-values 7 9 12))
  
  (factor ('the 'standard 'deviation 'of designation 'during 'the 'last
	   last-interval) (standard-deviation 5 9))
  
  (factor ('the 'standard 'deviation 'of designation 'during 'the ago-interval 
	   'ending 'with 'the 'collection 'time) (standard-deviation 5 8 true))

  (factor ('the 'standard 'deviation 'of designation 'between
	   ago-interval 'ago 'and ago-interval 'ago) (standard-deviation 5 7 10))
  
  (factor ('the 'rate 'of 'change 'per singular-time-unit 'of designation
	   'during 'the 'last last-interval) (rate-of-change 8 '6 12))

  (factor ('the 'rate 'of 'change 'per singular-time-unit 'of designation 
	   'during 'the ago-interval 'ending 'with 'the 'collection 'time)
	  (rate-of-change 8 '6 11 true))
  
  (factor ('the 'rate 'of 'change 'per singular-time-unit
	   'of designation 'between
	   ago-interval 'ago 'and ago-interval 'ago) (rate-of-change 8 '6 10 13))
  
  (factor ('the 'integral 'in plural-time-unit 'of designation 'during
	   'the 'last last-interval) (integral 6 '4 10))

  (factor ('the 'integral 'in plural-time-unit 'of designation 'during
	   'the ago-interval 'ending 'with 'the 'collection 'time)
	  (integral 6 '4 9 true))  
  
  (factor ('the 'integral 'in plural-time-unit 'of designation 'between
	   ago-interval 'ago 'and ago-interval 'ago) (integral 6 '4 8 11))

  (factor ('the 'number 'of 'history 'datapoints 'in designation)
	  (number-of-datapoints 7))

  (factor ('the 'number 'of 'history 'datapoints 'in designation 'during 'the 'last 
	   last-interval) (number-of-datapoints 7 11))

  (factor ('the 'number 'of 'history 'datapoints 'in designation 'during 'the
	   ago-interval 'ending 'with 'the 'collection 'time)
	  (number-of-datapoints 7 10 true))
  
  (factor ('the 'number 'of 'history 'datapoints 'in designation 'between
	   ago-interval 'ago 'and ago-interval 'ago) (number-of-datapoints 7 9 12))

  (factor ('the 'number 'of 'elements 'in designation)
	  (g2-list-or-sequence-length 6))

  #+later ; 5.1
  (designation ('the 'network 'interface 'for designation)
	       (network-interface-for 5))

  ;; NOTE: If "expressions that has a" (the following phrase) could ever
  ;; come before a vowel sound, the "'a" must be changed to "a-or-an".  At
  ;; present, it can only come before "current" or "value", so there is
  ;; no problem.  (MHD 1/11/91)
  (expressions-that-has-a ('expressions 'that 'has 'a) 1)
  
  (designation item-name)

;  (designation (class '\:\: method-name) (the (class-qualified-method 1 3)))
  (designation class-qualified-method)

  (designation (quantifier class) (1 2))

  (designation ('the attribute-name))

  (designation (quantifier class-phrase-role designation) (1 2 3))

  (designation
    ('the attribute-name 'of designation)
    (the 2 4)
    (filter-out-the-text-of-as-a-special-case))
  
  (designation
    ('the attribute-name local-name 'of designation)
    (the (2 . 3) 5)
    (filter-out-the-text-of-and-region-icon-color))

  (designation
    ('the class '\:\: attribute-name 'of designation)
    (the (class-qualified-name 2 4) 6)
    )
  (designation
    ('the class '\:\: attribute-name local-name 'of designation)
    (the ((class-qualified-name 2 4) . 5) 7)
    )

  ;; Added for 3.0. cpm, 8/16/91
  (designation
    ('the class-or-value-type 'that 'is 'an 'attribute 'of designation 'named 'by
	  designation)
    (the (attribute-value 2) 8 11))
  (designation
    ('the class-or-value-type local-name 'that 'is 'an 'attribute 'of designation 'named
	  'by designation)
    (the ((attribute-value 2) . 3) 9 12))

;  (designation (quantifier element-type 'in designation)
;	       (1 (element-iterator 2) 4))

;  (designation (quantifier element-type local-name 'in designation)
;	       (1 ((element-iterator 2) . 3) 5))

  (factor				
    ('the graphic-attribute 'of designation)
    (the 2 4))

  (factor
    ('the graphic-attribute local-name 'of designation)
    (the (2 . 3) 5)
    (filter-out-region-icon-color))

  (designation ('the class 'giving 'the attribute-name 'of designation)
	       (giver-of-value 2 (4 5 7)))

  (designation ('the class 'giving 'the class '\:\: attribute-name 'of designation)
	       (giver-of-value 2 (4 (class-qualified-name 5 7) 9)))

  (designation ('this 'workspace) (the (role-server this-workspace kb-workspace)))

  #+mtg2
  (designation ('this 'faction) (the (role-server this-faction faction)))

  (designation ('this 'window) (the (role-server this-window ui-client-item)))

  (designation ('this 'rule) (the (role-server this-rule rule))
	       (restrict-if-not-slot-edit-feature rule this-rule))

  (designation ('this 'procedure) (the (role-server this-procedure procedure))
	       (restrict-if-not-slot-edit-feature procedure this-procedure))

  (designation ('this 'procedure-invocation)
	       (the (role-server this-procedure-invocation procedure-invocation))
	       (restrict-if-not-slot-edit-feature
		 procedure this-procedure-invocation))

  ;; To fix BUG-059-5435 -- Commenting out obsolete grammar (ghw 1/26/99)
  ;(designation ('the 'workspace 'named object-name)
  ;	        (the (named 4 kb-workspace)) workspace-named-is-obsolete)

  (designation ('the list-role-keyword element-type 'in designation)
	       (the (2 3) 5))

  (designation ('the list-role-keyword element-type local-name 'in designation)
	       (the ((2 3 ) . 4) 6)))





;;; The function `quoted-symbol-phrase-p' returns true iff phrase represents a
;;; quoted symbol expression in the G2 language, i.e., an expression with
;;; surface grammar "the symbol <symbol>".

(defun-simple quoted-symbol-phrase-p (phrase)
  (and (consp phrase)
       (eq (car-of-cons phrase) 'quote)
       (consp (cdr-of-cons phrase))
       (null (cdr (cdr-of-cons phrase)))
       (symbolp (cadr-of-cons phrase))))


;;; The function `reject-if-sequence-constant' returns bad-phrase iff
;;; function-and-args, a phrase resulting from the parse of the grammar rule
;;;
;;;    factor => function-name argument-list
;;;
;;; represents a sequence that can be a constant.  That is, if
;;; all of the elements of argument-list do not evaluation by
;;; G2's evaluator in order to be realized as final values.
;;;
;;; Similarly, the function `reject-if-structure-constant' returns bad-phrase
;;; iff function-and-args, a phrase resulting from the parse of the grammar rule
;;;
;;;    factor => STRUCTURE ( r-paren
;;;
;;; represents a structure that can be be a constant.

(defun-simple reject-if-sequence-constant (function-and-args)
  #+development
  (test-assertion
    (and (consp function-and-args)
	 (symbolp (car function-and-args))))
  (if (and (eq (car-of-cons function-and-args) 'sequence)
	   (loop for arg in (cdr function-and-args)
		 always (or (quoted-symbol-phrase-p arg)
			    (phrase-for-constant-p arg))))
      ;; then it should be interpretted as a constant, not as this (an special-form
      ;; expression), so reject it:
      bad-phrase
      ;; otherwise, pass it right along, accept it as a special-form expression
      function-and-args))

(declare-grammar-transform-can-return-bad-phrase reject-if-sequence-constant)

(defun reject-if-structure-constant (function-and-args)
  #+development
  (test-assertion
    (and (consp function-and-args)
	 (symbolp (car function-and-args))))
  (if (and (eq (car-of-cons function-and-args) 'evaluated-structure)
	   (loop for (indicator-arg-phrase value-arg-phrase)
		 on (cdr function-and-args) by #'cddr
		 always (or (quoted-symbol-phrase-p value-arg-phrase)
			    (phrase-for-constant-p value-arg-phrase))))
      bad-phrase
      function-and-args))

(declare-grammar-transform-can-return-bad-phrase reject-if-structure-constant)



(defun transpose-sum (phrase)
  (let ((third (third phrase)))
    (if (and (consp third)
	     (memq (car third) '(|+plus+| |-minus-|)))
	(transpose-sum-1 (first phrase) (second phrase) third)
	phrase)))



(defun transpose-sum-1 (op construct destruct)
  (cond
    ((or (atom destruct)
	 (not (memq (first destruct) '(|+plus+| |-minus-|))))
     (phrase-list op construct destruct))

    (t (transpose-sum-1
	 (if (eq (first destruct) '|+plus+|) '+ '-)
	 (phrase-list op construct (second destruct))
	 (third destruct)))))





(defun transpose-term (phrase)
  (let ((third (third phrase)))
    (if (and (consp third)
	     (memq (car third) '(|*times*| |/slash/|)))
	(transpose-term-1 (first phrase) (second phrase) third)
	phrase)))



(defun transpose-term-1 (op construct destruct)
  (cond
    ((or (atom destruct)
	 (not (memq (first destruct) '(|*times*| |/slash/|))))
     (phrase-list op construct destruct))

    (t (transpose-term-1
	 (if (eq (first destruct) '|*times*|) '* '/)
	 (phrase-list op construct (second destruct))
	 (third destruct)))))



;; End file with CR


;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module GRAMMAR4A

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Michael Levin and Mark H. David

;;;; NUPEC Synchronize Action Grammar



;;; To GRAMMAR5
(declare-forward-reference compile-quantity-for-slot function)

;;; To GRAMMAR6
(declare-forward-reference write-list-in-chicago-style function)

;;; To CONTROLS
(declare-forward-reference action-button-priority-function function)

;; A useful way to get rid of an unwanted grammar rule while developing
;; grammar is to recompile it with a transform that inhibits its use.
;; A grammar rule will always supercede and replace an earlier one if
;; the term being rewritten and the rewrite are identical. But the
;; transformation form and transforming functions may be changed.

#+development
(defun bad-phrase-function (x)
  (declare (ignore x))
  bad-phrase)

;; Function named bad-phrase was removed by ML. 2/1/91

				    
(reserve-words '(if then else when that
		 the first any every one all a an
		 of for at with between on in upon per during over until
		 across
		 via connected by above below down
		 and or not
		 true false
		 second seconds minute minutes hour hours day days week weeks
		 focus invoke set conclude send
;		    rule
		 rules value values
		 ago past current last
		 interpolated maximum minimum
		 average sum product count
		 standard deviation rate change integral
		 is to be has becomes was were will could should
		 format name
		 undefined moved
		 no yes
		 none
                 ; time
		 input output
		 ; state
		 this 	     	; needed to make actions parse correctly! ML
		 nearest named
		 ;; Keywords follwing a quantifier must be reserved! ML
		 symbol giving nearest same connected expiration collection
;		    icon-color stripe-color
		 there exists nothing everything
		 nil   			;Not a permitted word in user vocabulary
		 subworkspace workspace faction
		 begin end return call start infer repeat exit go
		 wait checking
		 do case
		 -
		 color-pattern
		 simulated
		 available-frame-vector	; prevent this from being a class
                 using ;added by SoftServe for new Rule LHS syntax   
		 ))

;; Plase do not unreserve any words unless I have  authorized this.  Generally
;; they have to be put back in after a time consuming effort to deal with a
;; gramatical ambiguity or nonsensical menu  offering.

;; Presently we will have a way to organize the system attributes
;; and pseudo-attributes with semi-open categories. This will clear up some
;; of the problems. For now, WORKSPACE and SUBWORKSPACE must be reserved.

;; The procedure statement names DO NOT need to be reserved words as far as I
;; can tell, and if they do then the list above is far out of date.  Please
;; review this, Michael, and remove or update the list.  -jra 10/15/89




(reserve-words-as-instances-of-category
  singular-time-unit
  (second minute hour day week))

(reserve-words-as-instances-of-category
  plural-time-unit
  (seconds minutes hours days weeks))


;(defun reserve-punctuation (punct-alist)
;  (loop for association in punct-alist
;	do (reserve-words (list (cadr association)))
;	   (reserve-punctuation (cddr association))))

;(reserve-punctuation punctuation-alist)        ; no longer necessary -- see module EDIT



;;;; Notes on delimiting

;;; An expression can be delimited by any of the following. This list
;;; can grow.  Delimiting means that encountering this token in a
;;; context where an expression has been parsed and the expression might
;;; be continued definitely ends the expression.

;;; THEN		; end of antecedent
;;; AND 		; end of set action or send action, another action follows
;;; AND OR		; end of expression within a logical-expression
;;; any comparator	; same
;;; )                   ; expression within parens or argument list
;;; ,                   ; listed expression in argument list, or list
;;;                     ; for send, possibly others
;;; IS                  ; after designation within logical-expression
;;; TO                  ; in send expression


;;; An expression can begin with:
;;; + - ( THE 
;;; a function name     a variable name

;;; An expression can continue with:
;;; + - * / OF

;;; Note that a logical-expression is different than an expression and so far
;;; is used only as an antecedent of a rule.

;;; Actions are strung together with AND; the else actions are separated from
;;; the first list of actions by ELSE.

;;; Actions may end in expressions (SET, SEND), designations (ADD,
;;; REMOVE, FOCUS, INVOKE), or names or lists of names (SEND, SET,
;;; EXIT). Some actions end in reserve words. (For example, INVOKE may
;;; end in RULES.) Some of these lists separated by commas, but at least
;;; one ("send <message>" to engineer and log") makes use of AND. Unless
;;; we change this, it is important that actions begin with reserved
;;; words. (E.g.  if "log the result" was a valid action, then "send
;;; "foo" to engineer and log the result" would not disambiguate itself
;;; until after "THE" was parsed.  This would result in confusing menus,
;;; inefficiency, and complexity in making further extensions to the
;;; language. 

;;; We need to decide if the category of initial words for actions is
;;; open or closed. Having it closed and reserving these words is
;;; simplest. Having it open allows procedure names to be used as action
;;; verbs, e.g. "cool the furnace" instead of "call cool the furnace."
;;; But then COOL would have to made a reserve word. 





;;;; Synopsis of internal-grammar for rule

;;; This is an overly broad description of the internal language, which is not
;;; suitable for defining its correctness, but is completely suitable for parsing
;;; all constituents of a syntactically correct form. 

;;; Note that "designation" is a subset of "expression" and not visa versa.
;;; For example, it would be inappropriate to substitue an expression which is not
;;; a designation (such as (+ A 3)) in place of a designation to be concluded.

;;; Iteration over intenal forms is performed by the compiler, various installation
;;; functions, the WHERE substitution mechanism and possibly other pieces of software.

;;; Anyone making use of the documentation below in such a way that extensions to
;;; the internal form language requires changes to your code should sign on below.
;;; Indicate name, date, file and function(s).



;;; rule: (if logical-expression actions)

;;; logical-expression:
;;;    (AND {logical-expression})
;;;    (OR {logical-expression})
;;;    (op expression expression) where op is < > = /= <= >= is
;;;    (IS designation (QUOTE symbol))
;;;    designation
;;;    (integer . TRUTH-VALUE), where -1000 <= integer <= 1000
;;;       [Replacement for the obsolete: TRUE | FALSE  (MHD 5/13/97)]
;;;    (function-name {expression})
;;;    (has-current-value designation)
;;;    (has-history designation interval [interval])

;;; expression:
;;;    designation
;;;    (op {expression}) where op is + - * / ^
;;;    (function-name {expression})
;;;    constant

;;; constant:
;;;    number
;;;    (number . unit)

;;; designation:
;;;    (quantifier role) where quantifier is THE EVERY ANY EACH and others to come
;;;    (quantifier role designation)
;;;    (giver-of-value class designation) 
;;;    symbol

;;; role:
;;;    symbol
;;;    (at-port port-name class)
;;;    (at-an-input class)
;;;    (at-an-output class)
 
;;; actions:
;;;     action
;;;     (AND {action})

;;; action:
;;;    (CONCLUDE designation)
;;;    (CONCLUDE-NOT designation)
;;;    (CONCLUDE designation expression)
;;;    (FOCUS designation)
;;;    (INVOKE list-of-categories expression)
;;;    (INFORM destination-list message-text {message-option})
;;;    (SET designation expression)

;;; list-of-categories
;;;    category
;;;    (AND {category}

;;; message-text:
;;;    string
;;;    (AND { string | expression } )

;;; message-option
;;;    (DURATION number) 





;;; A `constant designation' is a type of designation ...

;;; CONSTANT-DESIGNATION is the name of the grammar category.  Since it may be used as
;;; a slot type, a slot value writer is provided for it.  Constant prepositions
;;; exclude named by and nearest to.

(add-grammar-rules
  '((constant-designation item-name)

;    (constant-designation (class '\:\: method-name) (the (class-qualified-method 1 3)))
    (constant-designation class-qualified-method)
    
    (constant-designation ('the constant-class-phrase-role constant-designation))

    ;; add two to take care of the 'of case
    (constant-designation ('the attribute-name 'of constant-designation)
     (the 2 4)
     filter-out-the-text-of-as-a-special-case)
    (constant-designation ('the attribute-name local-name 'of constant-designation)
     (the (2 . 3) 5)
     filter-out-the-text-of-and-region-icon-color)
    (constant-designation ('the class '\:\: attribute-name 'of constant-designation)
     (the (class-qualified-name 2 4) 6))
    (constant-designation ('the class '\:\: attribute-name local-name 'of constant-designation)
     (the ((class-qualified-name 2 4) . 5) 7))
    
    (constant-class-phrase-role 
     (class constant-preposition) (1 2) translate-role-and-preposition)

    (constant-class-phrase-role 
     (class local-name constant-preposition) 
     (1 2 3) translate-role-local-name-and-preposition)

    ;; The following were commented out when I added the rules above for
    ;; attributes.  Attribute reference should not be a class-phrase role since
    ;; it prompts the user for phrases like "the <class> of
    ;; <constant-designation>".  Delete these comments and commented out code
    ;; after this has all worked out for a while.  -jra 2/11/94
;    (constant-class-phrase-role 
;      (attribute-name constant-preposition) (1 2) translate-role-and-preposition)

;    (constant-class-phrase-role 
;      (attribute-name local-name constant-preposition) 
;      (1 2 3) translate-role-local-name-and-preposition)

    (constant-class-phrase-role ('workspace 'of) (role-server workspace kb-workspace))

    (constant-class-phrase-role ('workspace local-name 'of) ((role-server workspace kb-workspace) . 2))

    #+mtg2
    (constant-class-phrase-role ('faction 'of) (role-server faction faction))

    #+mtg2
    (constant-class-phrase-role ('faction local-name 'of) ((role-server faction faction) . 2))
    
    (constant-class-phrase-role ('subworkspace 'of) (role-server subworkspace kb-workspace))

    (constant-class-phrase-role ('subworkspace local-name 'of)
     ((role-server subworkspace kb-workspace) . 2))
    
    #+rdf				; (MHD 3/9/98)
    (class-phrase-role (designation local-name 'that 'contains)
     ((member-iterator 1) . 2))
    #+rdf				; (MHD 3/9/98)
    (class-phrase-role (designation 'that 'contains)
     (member-iterator 1))
    ;; Above (#+rdf) was wrong.  Did not work, and broke the expression grammar.
    ;; This grammar replaces it: (with its counterpart grammar in GRAMMAR1A for
    ;; category PREPOSITION, q.v.)  Note that the member-iterator role was
    ;; already implemented, and is assumed correct, and appears to work under
    ;; very light testing by me.  By the way, this is is new 5.0
    ;; grammar/functionality and is documented as grammar for iterating over
    ;; lists in the lists section of the 5.0 manual.  (MHD 3/9/98)
    (constant-preposition ('that 'contains) member-iterator)
    
;    (constant-preposition 'of)
    (constant-preposition ('connected 'to) connected-to)
    (constant-preposition ('connected 'at 'the port-name 'of) (at-port 4))
    
    (constant-preposition ('connected 'at 'the 'input 'to) at-an-input)
    (constant-preposition ('connected 'at 'an 'input 'to) at-an-input)
    (constant-preposition ('connected 'at 'the 'input 'of) at-an-input)
    (constant-preposition ('connected 'at 'an 'input 'of) at-an-input)
    
    (constant-preposition ('connected 'at 'the 'output 'of) at-an-output)
    (constant-preposition ('connected 'at 'an 'output 'of) at-an-output)
    
    (constant-preposition ('at 'the 'input 'end 'of) at-input-end)
    (constant-preposition ('at 'an 'input 'end 'of) at-input-end)
    (constant-preposition ('at 'the 'output 'end 'of) at-output-end)
    (constant-preposition ('at 'an 'output 'end 'of) at-output-end)
    (constant-preposition ('at 'either 'end 'of) at-either-end)
    (constant-preposition ('at 'an 'end 'of) at-either-end)
    
    (constant-designation? constant-designation)
    (constant-designation? 'none)
    ))

;; Why aren't the roles superior-item, attribute-of-class, or upon acceptable in
;; constant designations?  Seems to be an oversight that they are missing.  - agh,
;; 2/10/91



(def-slot-value-writer constant-designation (value)
  (print-designation value))


; The following are commented out only because they are presently not used.
; They are useful, and should not be expunged.

;(def-slot-value-compiler constant-designation? (parse-result)
;  (if (eq parse-result 'none)
;      nil
;      parse-result))



;(def-slot-value-writer constant-designation? (value)
;  (if value
;      (print-designation value)
;      (twrite-string "none")))




(add-grammar-rules
  '((constant-variable-designation variable-or-parameter-name)
    (constant-variable-designation
     ('the constant-class-phrase-role constant-designation))
    (constant-variable-designation
     ('the constant-attribute-phrase-role constant-designation))
    (constant-attribute-phrase-role 
     (attribute-name 'of) (1 2) translate-role-and-preposition)
    (constant-attribute-phrase-role
     (class '\:\: attribute-name 'of)
     (class-qualified-name 1 3) translate-role-and-preposition)
    (constant-attribute-phrase-role 
     (attribute-name local-name 'of) 
     (1 2 3) translate-role-local-name-and-preposition)
    (constant-attribute-phrase-role
     (class '\:\: attribute-name local-name 'of)
     (class-qualified-name 1 3) translate-role-and-preposition)
    (constant-variable-designation? constant-variable-designation)
    (constant-variable-designation? 'none)
    ))



(def-slot-value-compiler constant-variable-designation? (parse-result)
  (if (eq parse-result 'none)
      nil
      parse-result))



(def-slot-value-writer constant-variable-designation? (value)
  (if value
      (print-designation value)
      (twrite-string "none")))




;;; Note on reversing this into release 1.0
;;; The function print-designation exists in release 1.0 and is textually
;;; identical to the one in 1.1. But the subsidiary function print-role is different.
;;; It does not have a sub function print-role-1, for example.

;;; I think it is best not to copy print-role from 1.1 into release 1.1
;;; because I don't know what it would do. But you should patch the existing
;;; print-role function by modifying two strings:
;;;	"connected at an input of"    	to 	" connected at an input of"
;;;	"connected at an output of"	to	" connected at an output of"

;;; This fixes a bug manifesting as: "... the barconnected at ...".






;;;; Constant-Designation, Constant-Datum Lists




;;; The following grammar implements a list of values or designations of the
;;; form: (a [,b] ...)

;;; This grammar is used in g2-array-initial-values.

;; jh, 7/20/94.  Modified the add-grammar-rules-for-list for the categories
;; involved in the g2-array-initial-values attribute of g2-array:
;; constant-designation-list?, quantity-list, integer-list, float-list,
;; whole-string-list, truth-value-list, symbol-list, symbol-list-with-and,
;; list-of-item-and-datum-constants?, and list-of-datum-constants.  These forms
;; now cause the parser to decline to simplify each associative operation one at
;; a time, thereby saving on temporary phrase-consing.  See my 7/18/94 note
;; under def-simplifying-slot-value-compiler below for further details.

;; For INITIAL-VALUES of ITEM-ARRAY.

(add-grammar-rules-for-list
  'constant-designation-list? 'constant-designation '\, nil 'none nil)

;; For INITIAL-VALUES of QUANTITY-ARRAY, INTEGER-ARRAY, FLOAT-ARRAY, TEXT-ARRAY,
;; and TRUTH-VALUE-ARRAY.

(add-grammar-rules-for-list 'quantity-list        'quantity     '\, nil  nil nil)
(add-grammar-rules-for-list 'integer-list         'integer      '\, nil  nil nil)
(add-grammar-rules-for-list 'long-list            'long         '\, nil  nil nil)
(add-grammar-rules-for-list 'float-list           'float        '\, nil  nil nil)
(add-grammar-rules-for-list 'whole-string-list    'whole-string '\, nil  nil nil)
(add-grammar-rules-for-list 'truth-value-list
			    ;; truth-value => truth-value-attribute (MHD 5/13/97)
			    'truth-value-attribute
			    '\, nil  nil nil)
(add-grammar-rules-for-list 'symbol-list          'symbol       '\, nil  nil nil)
(add-grammar-rules-for-list 'symbol-list-with-and 'symbol       '\, 'and nil nil)


;; For INITIAL-VALUES of G2-ARRAY, which contains item-or-values.  Allows a
;; value of "none".
(add-grammar-rules-for-list 'list-of-item-and-datum-constants?
	    'constant-designation-quoted-symbol-list-and-datum '\, nil 'none nil)

;; For INITIAL-VALUES of VALUE-ARRAY.  Does not allow a value of "none".
(add-grammar-rules-for-list 'list-of-datum-constants
	    'quoted-symbol-list-and-datum '\, nil nil nil)


;;; Note that the list-of-item-and-datum-constants? and list-of-datum-constants
;;; grammar categories need to distinguish between symbols and item
;;; designations.  There are two changes that implement this.

;;; The first is visible to the user.  For these categories, the user "quotes"
;;; the symbol or list of symbols by using the phrase "the symbol <symbol>" or,
;;; for example, "the symbols <s1>, <s2>, and <s3>".

;;; The second change is internal.  The parse needs to distinguish between item
;;; designations and symbols.  See the slot-value-compiler for
;;; list-of-datum-constants and list-of-item-and-datum-constants?.

(add-grammar-rules
  '((constant-designation-quoted-symbol-list-and-datum constant-designation)
    (constant-designation-quoted-symbol-list-and-datum
     quoted-symbol-list-and-datum)

    ;; Note that the slot-value-compiler needs to distinguish between
    ;; designations and symbols.
    (quoted-symbol-list-and-datum quoted-symbol-list)
    (quoted-symbol-list-and-datum constant-non-symbol-datum)

    (quoted-symbol-list ('the 'symbol symbol) (\, 3))

    ;; The following grammar for quoted-symbol-list is not used.  It caused two
    ;; errors.
    ;; 1. The simplifying-slot-value-compilers for list-of-datum-constants and
    ;; list-of-item-and-datum-constants? does not handle simplify-associative-
    ;; operations on sublists (e.g., a symbol sublist within another list).
    ;; 2. The grammar category list-of-item-and-datum-constants? had a bug when
    ;; entering a symbol list of one element.  "the symbols s1, x1, x2" is
    ;; written as "the symbol s1, x1, x2", which is a symbol and three name
    ;; designations.  This is confusing to the user.

    ; (quoted-symbol-list ('the 'symbols symbol-list-with-and) 3)

  
    ;; Note that the order of the following rules is important.  A bug occurred
    ;; when the whole-string rule was not last.  In that case, the editor did
    ;; not prompt for text (i.e., whole-string).  Putting the rule last is a
    ;; workaround for the problem.  See notes in QUERIES for a similar bug
    ;; related to the whole-string category.  - cpm, 1/25/94
    (constant-non-symbol-datum integer)
    (constant-non-symbol-datum long)
    (constant-non-symbol-datum float)

    (constant-non-symbol-datum truth-value-attribute) ; (n . truth-value), (-1000<=n<=1000)
    ;; Obsolete:  -- replaced by the rule above. (MHD 5/13/97)
    ;; (constant-non-symbol-datum truth-value) ; true, false, or (<number> 'true)

    
    (constant-non-symbol-datum whole-string)

    ;; additions for 5.0:   (MHD 6/18/97)
    (constant-non-symbol-datum sequence)
    (constant-non-symbol-datum structure)))

;; I observe that constant-non-symbol-datum is quite similar to the definition
;; for constant, except that units of measure are not allowed for the former.
;; (MHD 6/18/97)

;; Not currently needed for g2-arrays.  - cpm 1/9/94
;(add-grammar-rules
;  '((constant-datum-quoted-symbols constant-non-symbol-datum)
;    (constant-datum-quoted-symbols quoted-symbol)
;    (constant-datum constant-non-symbol-datum)
;    (constant-datum symbol)
;    (quoted-symbol ('the 'symbol symbol) (quote 3))))



(def-slot-value-compiler constant-designation-list? (parse-result)
  ;; This should just take the cdr of the parse-list, but there is a
  ;; problem that 'none isn't being transformed into nil!!  See
  ;; constant-designation-list?.  cpm, 7/10/91
; (cdr parse-result)
  (cond
    ((eq parse-result 'none)
     nil)
    ((consp parse-result)
     (cond
       ((eq (car parse-result) 'normalized)
	(cdr parse-result))
       (t
	(simplify-associative-list-operation-all-at-once parse-result)
	(cdr parse-result))))))

(def-simplifying-slot-value-compiler constant-designation-list (parse-result)
  (cdr parse-result))

(def-simplifying-slot-value-compiler quantity-list (parse-result)
  (loop for quantity in (cdr parse-result)
	collect	(compile-quantity-for-slot quantity nil nil)
	  using phrase-cons))
	

(def-simplifying-slot-value-compiler integer-list (parse-result)
  (if (consp parse-result)
      (cdr parse-result)
      ;;This is to patch a bug in the rules for integer-list.  For some reason,
      ;;single values are not being returned as a list.  This is not a problem
      ;;in symbol-list, float-list, etc.  cpm, 8/9/91
      (phrase-list parse-result)))

(def-simplifying-slot-value-compiler float-list (parse-result)
  (cdr parse-result))

(def-simplifying-slot-value-compiler whole-string-list (parse-result)
  (cdr parse-result))

(def-slot-value-compiler truth-value-list (parse-result)
  (cond
    ((eq (car parse-result) 'normalized)
     (cdr parse-result))
    (t
     (simplify-associative-list-operation-all-at-once parse-result)
     (loop with truth-value-phrases = (cdr parse-result)
	   for remaining-truth-value-phrases on truth-value-phrases
	   do (setf (car remaining-truth-value-phrases)
		    (truth-value-phrase-value
		      (car remaining-truth-value-phrases)))
	   finally (return truth-value-phrases)))))

;; Note that the grammar now generates truth-value phrases, not TRUE, FALSE, or
;; (n . TRUTH-VALUE), [-1<=n<=1], as before.  Note that the compiler, in turn,
;; will turn these into truth-value values, integer in the range
;; [-1000..1000]. (MHD 5/13/97)


(def-simplifying-slot-value-compiler symbol-list (parse-result)
  (if (consp parse-result)
      (cdr parse-result)
      ;; The same problem that occurs for integer-list is now showing up for
      ;; symbol-list.  cpm, 10/22/91.
      (phrase-list parse-result)))

(def-simplifying-slot-value-compiler quoted-symbol-list
    (parse-result)
  (cdr parse-result))



(def-slot-value-compiler list-of-item-and-datum-constants?
    (parse-result)
  (cond
    ((eq (car parse-result) 'normalized)
     (cdr parse-result))
    (t
     (simplify-associative-list-operation-all-at-once parse-result)
     (compile-constant-designation-or-datum-list parse-result nil))))

(def-slot-value-compiler list-of-datum-constants
    (parse-result)
  (cond
    ((eq (car parse-result) 'normalized)
     (cdr parse-result))
    (t
     (simplify-associative-list-operation-all-at-once parse-result)
     (compile-constant-designation-or-datum-list parse-result t))))


;;; Note that the function `compile-constant-designation-or-datum-list' compiles
;;; into a list of constant designations, truth-value slot-constants, text
;;; strings, phrase-numbers, and symbols ("marked" or unmarked symbols).  Note
;;; that for item-or-datum lists, symbols are handled specially to distinguish
;;; them from item designations.  In this case, each symbol is converted to a
;;; list of symbol marker and the symbol value.  Datum-lists have the usual
;;; symbols.

(defun compile-constant-designation-or-datum-list (parse-result datum-only-p?)
  (loop for designation-or-datum-cons on (cdr parse-result)
	for cons-value = (car designation-or-datum-cons)
	do
    (cond
      ((eq cons-value 'none)
       (setf (car designation-or-datum-cons) nil))
      ((truth-value-phrase-p cons-value)
       (setf (car designation-or-datum-cons)
	     (mutate-truth-value-phrase-into-slot-constant cons-value)))
      ((or (symbolp cons-value) (phrase-number-p cons-value) (text-string-p cons-value))
       ;; no change.
       nil)
      ((not (consp cons-value))
       #+development
       (cerror "continue"
	       "Unexpected non-cons value in compile-constant-designation-or-datum-list.")
       nil)
      ((eq (car cons-value) '\,)
       (loop with cons-pointer-for-splice = (cdr designation-or-datum-cons)
	     for symbol-element in (cdr cons-value)
	     for new-symbol-element =
	     (if datum-only-p?
		 symbol-element
		 (phrase-list symbol-initial-value-marker symbol-element))
	     for top-level-cons = designation-or-datum-cons
				then (phrase-cons new-symbol-element nil)
	     with previous-top-level-cons = nil
	     do
	 (cond ((null previous-top-level-cons)
		(setf (car designation-or-datum-cons) new-symbol-element))
	       (t
		(setf (cdr previous-top-level-cons) top-level-cons)))
	 (setq previous-top-level-cons top-level-cons)
	     finally
	       ;; Splice the new symbol list into the original list.  Note that the
	       ;; orphaned conses from the original list of symbols are phrase conses
	       ;; and so are automatically reclaimed
	       (setf (cdr previous-top-level-cons) cons-pointer-for-splice)))
      ((slot-value-number-p (car cons-value))
       #+development    	; Remove later; this case should never come up now! (MHD 5/15/97)
       (cerror "continue" "Expected truth-value in slot-value-compiler for constant-designation-or-datum-list.")
       nil)
      (t
       ;; Non-symbolic designation.  No change.
       nil)))
  ;; return value
  (cdr parse-result))






;;; Slot-value-writers for constant-designation and constant-datum lists.

(def-slot-value-writer constant-designation-list?
    (constant-designation-list? frame)
  (if (null constant-designation-list?)
      (twrite 'none)
      (print-item-and-datum-constant-list constant-designation-list? frame)))
;      (print-designation-list constant-designation-list?)))

(def-slot-value-writer constant-designation-list (constant-designation-list)
  (print-designation-list constant-designation-list))

(def-slot-value-writer quantity-list (number-list frame)
  (if (null number-list)
      (twrite 'none)
      (print-item-and-datum-constant-list number-list frame)))
;      (print-constant-list number-list 'number))

(def-slot-value-writer integer-list (integer-list frame)
  (if (null integer-list)
      (twrite 'none)
      (print-item-and-datum-constant-list integer-list frame)))
;  (print-constant-list integer-list 'integer))

(def-slot-value-writer float-list (float-list frame)
  (if (null float-list)
      (twrite 'none)
      (print-item-and-datum-constant-list float-list frame)))
;  (print-constant-list float-list 'float))

(def-slot-value-writer whole-string-list (whole-string-list frame)
  (if (null whole-string-list)
      (twrite 'none)
      (print-item-and-datum-constant-list whole-string-list frame)))
;  (print-constant-list whole-string-list 'text))

(def-slot-value-writer truth-value-list (truth-value-list frame)
  (if (null truth-value-list)
      (twrite 'none)
      (print-item-and-datum-constant-list truth-value-list frame)))
;  (print-constant-list truth-value-list 'truth-value))

(def-slot-value-writer symbol-list (symbol-list frame)
  (if (null symbol-list)
      (twrite 'none)
      (print-item-and-datum-constant-list symbol-list frame)))
;  (print-constant-list symbol-list 'symbol))

(def-slot-value-writer quoted-symbol-list (symbol-list)
  (print-quoted-symbol-list symbol-list))

(defun print-quoted-symbol-list (symbol-list)
  (if (cdr symbol-list)
      (twrite-string "the symbols ")
      (twrite-string "the symbol "))
  (write-list-in-chicago-style symbol-list "and"))

(defun print-designation-list (designation-list)
  (loop for designations on designation-list
	do
    (print-designation (first designations))
    (when (cdr designations)
      (twrite-string ", "))))

(defun print-constant-list (constant-list constant-type)
  (loop for constant-values on constant-list
	do
    (print-constant (first constant-values) constant-type)
    (when (cdr constant-values)
      (twrite-string ", "))))



(def-slot-value-writer list-of-item-and-datum-constants?
    (constant-or-datum-designation-list? frame)
  (if (null constant-or-datum-designation-list?)
      (twrite 'none)
      (print-item-and-datum-constant-list
	constant-or-datum-designation-list? frame)))

(def-slot-value-writer list-of-datum-constants
    (constant-designation-list? frame)
  (if (null constant-designation-list?)
      (twrite 'none)
      (print-item-and-datum-constant-list constant-designation-list? frame)))
;      (print-datum-constant-list constant-designation-list?)))

(defun print-item-and-datum-constant-list
    (item-and-datum-constant-list &optional frame?)
  (loop for cons-of-list on item-and-datum-constant-list
	for item-datum-or-marked-symbol = (car cons-of-list)
	with immediately-preceeding-symbol-count = 0
	do
    (cond
      ((and (symbolp item-datum-or-marked-symbol)
	    frame?
	    (eq (get-foundation-class-for-class (class frame?)) 'value-array))
       ;; Unlike symbol-arrays, value-arrays have quoted symbols in the printed
       ;; form of their initial-values.
       (tformat "the symbol ~a" item-datum-or-marked-symbol)
       (when (cdr cons-of-list)
	 (twrite-string ", ")))
      ((initial-value-symbol-p item-datum-or-marked-symbol)
       (if (and frame?
		(eq (get-foundation-class-for-class (class frame?))
		    'symbol-array))
	   (print-item-or-datum-constant
	     (initial-value-symbol-value item-datum-or-marked-symbol))
	   (tformat "the symbol ~a" (initial-value-symbol-value item-datum-or-marked-symbol)))
       (when (cdr cons-of-list)
	 (twrite-string ", ")))
      ((and frame?
	    (eq (get-foundation-class-for-class (class frame?))
		'truth-value-array))
       (print-constant item-datum-or-marked-symbol 'truth-value)
       (when (cdr cons-of-list)
	 (twrite-string ", ")))
      (t
       (print-item-or-datum-constant item-datum-or-marked-symbol)
       (when (cdr cons-of-list)
	 (twrite-string ", "))
       (setq immediately-preceeding-symbol-count 0)))))

(defun print-datum-constant-list (datum-constant-list)
  (loop for cons-of-list on datum-constant-list
	for datum-element = (car cons-of-list)
	with immediately-preceeding-symbol-count = 0
	do
    (cond
      ((symbolp datum-element)

       (tformat "the symbol ~a" datum-element)
       (when (cdr cons-of-list)
	 (twrite-string ", "))

       ;; Not currently used.  Can print symbol lists of the form:
       ;; the symbols one, two, and three.
;       (let* ((next-cons (cdr cons-of-list))
;              (next-thing? (and next-cons (consp next-cons) (car next-cons)))
;              (symbol-is-next? (and next-thing? (symbolp next-thing?))))
;         (cond
;           ((=f immediately-preceeding-symbol-count 0)
;            (if symbol-is-next?
;                (twrite-string "the symbols ")
;                (twrite-string "the symbol ")))
;           (symbol-is-next?
;           (twrite-string ", "))
;           ((=f immediately-preceeding-symbol-count 1)
;            ;; Last symbol of two symbols.
;            (twrite-string " and "))
;           (t
;            ;; Last symbol of more than two symbols.
;            (twrite-string ", and ")))
;         (tformat "~a" datum-element)
;         (incff immediately-preceeding-symbol-count)
;         (when (and next-cons (not symbol-is-next?))
;           (twrite-string ", ")))
       )
      (t
       (print-item-or-datum-constant datum-element)
       (when (cdr cons-of-list)
	 (twrite-string ", "))
       (setq immediately-preceeding-symbol-count 0)))))

(defun print-item-or-datum-constant (item-or-datum-constant)
  (cond
    ((null item-or-datum-constant) (twrite-string "none"))
    ((managed-float-p item-or-datum-constant)
     (print-constant item-or-datum-constant 'number))
    ((slot-value-number-p item-or-datum-constant)
     (print-constant item-or-datum-constant 'number))
    ((symbolp item-or-datum-constant)
     (print-constant item-or-datum-constant 'symbol))
    ((text-string-p item-or-datum-constant)
     (tformat "~s" item-or-datum-constant)) ; writes parsably
    ((slot-constantp item-or-datum-constant)
     (print-constant
       (get-slot-value-number-or-string-from-slot-constant
	 item-or-datum-constant)
       (get-unit-from-slot-constant item-or-datum-constant)))
    ((evaluation-value-p item-or-datum-constant)
     (write-evaluation-value item-or-datum-constant))
    (t
     (print-designation item-or-datum-constant))))






;;;; G2-Array Definition Grammar




;;; G2-ARRAY-LENGTH grammar

(add-grammar-rules
  '((g2-array-length non-negative-integer)))

(def-slot-value-compiler g2-array-length (parse-result)
  (cond ((<f parse-result 0)
	 (values
	   bad-phrase
	   (copy-constant-wide-string #w"This value must be a non-negative integer.")))
	((>f parse-result g2-array-length-maximum)
	 (values
	   bad-phrase
	   (copy-text-string
             "This value is greater than the maximum g2-array length.")))
	(t parse-result)))

(def-slot-value-writer g2-array-length (n)
  (twrite n))






;;;; G2-Array and G2-List Nth-Element Reference




;;; The following grammar implements NTH-ELEMENT for g2-lists and g2-arrays.
;;; Nth-element is implemented as a role server and allows the random access of
;;; an element.  Only the g2-array element reference is a constant time
;;; operation.  The g2-list element access is an order N operation.

;;; The nth-element role-server checks at run-time whether the type of the item
;;; domain is g2-array or g2-list.  The role requires two domains, the g2-array
;;; or g2-list item and the index expression.  The role has a return type of
;;; item-or-datum.

;;; Note that there is no grammar for a LOCAL-NAME binding for nth-element.

;;; In the grammar, the array or list designation is restricted to be a
;;; name-reference or a reference to an array or list.  Some examples are:
;;;
;;; ARRAY-OR-LIST [x]
;;;    (the (nth-element item-or-datum) array-or-list x)
;;;
;;; ARRAY-OR-LIST-OF-ARRAYS-OR-LISTS [x] [y]
;;;    (the (nth-element item-or-datum) 
;;;         (the (nth-element item-or-datum) array-or-list-of-arrays-or-lists x)
;;;         y)
;;;
;;; THE TEMP OF ARRAY-OR-LIST [x]
;;;    (the Temp (the (nth-element item-or-datum) array-or-list x))



;;; Note that, in some cases, generic references which contain a nth-element
;;; reference (which is itself generic or not generic) are not allowed!  This is
;;; prevented during compilation of the expression or statement, not in the
;;; grammar.  This restriction occurs in rule antecedent.  An example is:
;;;   "if any pump connected to x [y] ..."
;;; This cannot be allowed because generate-and-schedule-rule-instances does not
;;; allow wait-states.  Accessing the nth-element may require a wait-state for
;;; the index expression.  In this case, a frame-note is added to the rule and
;;; the rule status is changed to BAD.


;; The following is a PROPOSED design change for nth-element array-or-list
;; reference.  We need to decide if these generic-references will be useful and
;; not confusing to the user.  - cpm, 5/8/91
;;
;; Should the nth-element grammar contain generic references for the array
;; designation or the index expression?  For example:
;;   "if any foo-array [i] > 0"
;;   "if x [any index-var] > 0"
;; Note that for this proposal only the left-most array designation of an array
;; of arrays reference coule be a generic reference.  For example, "any
;; foo-array [x][y]" is okay.




;;; Nth-Element Designation, unique-designation, e-designation.

(add-grammar-rules
  '((designation nth-element-designation)
    (unique-designation nth-element-designation)
    (e-designation nth-element-designation)

    (nth-element-designation (local-name subscript-expression)
			     (the (nth-element item-or-datum) 1 2)
			     reparse-nth-element-designation)

    (nth-element-designation ( '\( unique-designation '\) subscript-expression)
			     (the (nth-element item-or-datum) 2 4)
			     reparse-nth-element-designation)

    (subscript-expression bracketed-expression)
    (subscript-expression (bracketed-expression subscript-expression))

    (bracketed-expression ('[ unique-expression ']) (1 2))
    ))



;;; Nth-Element Simulation-designation

(add-grammar-rules
  '((simulation-designation simulation-nth-element-designation)

    (simulation-nth-element-designation 
      (local-name simulation-subscript-expression)
      (the (nth-element item-or-datum) 1 2)
      reparse-nth-element-designation)

    (simulation-nth-element-designation 
      ( '\( simulation-designation '\) simulation-subscript-expression)
      (the (nth-element item-or-datum) 2 4)
      reparse-nth-element-designation)

    (simulation-subscript-expression simulation-bracketed-expression)
    (simulation-subscript-expression
      (bracketed-expression simulation-subscript-expression))

    (simulation-bracketed-expression ('[ simulation-expression ']) (1 2))
    ))



;;; The function `reparse-nth-element' is used to correct the ordering of the
;;; parse for nested array references.  An example is ARRAY-1 [x] [y].  Since
;;; the grammar can not be left-recursive the order is corrected here.

;; The commented out functions were written by ml.  They have been modified
;; below to handle quantifiers and to be a little more abstract.  cpm, 5/8/91

;(defun reparse-nth-element-designation (parse)
;  (reparse-nth-element-designation-1 (second parse) (third parse)))

;(defun reparse-nth-element-designation-1 (construct destruct)
;  (cond
;    ((eq (car destruct) '[)
;     (phrase-list '(nth-element item-or-datum) construct (second destruct)))
;    ((and (consp (car destruct))
;	  (eq (caar destruct) '[))
;     (cond
;       ((null (cdr destruct))
;	(phrase-list
;	  '(nth-element item-or-datum) construct (second (first destruct))))
;       (t (reparse-nth-element-designation-1
;	    (phrase-list
;	      '(nth-element item-or-datum) construct (second (first destruct)))
;	    (second destruct)))))))

(defun reparse-nth-element-designation (parse)
  (gensym-dstruct-bind ((quantifier role domain expression) parse)
    (reparse-nth-element-designation-1 quantifier role domain expression)))

(defun reparse-nth-element-designation-1 (quantifier role construct destruct)
  (cond
    ;; Superfluous escapes de-confuse Emacs delimiter balancing.
    ((eq (car destruct) '\[)
     (phrase-list quantifier role construct (second destruct)))
    ((and (consp (car destruct))
	  (eq (caar destruct) '\[))
     (cond
       ((null (cdr destruct))
	(phrase-list quantifier role construct (second (first destruct))))
       (t (reparse-nth-element-designation-1
	    quantifier role
	    (phrase-list quantifier role construct (second (first destruct)))
	    (second destruct)))))))






;;;; Function Templates




;;; These are the function template declarations for inference engine functions.
;;; They are currently only used in chaining analysis, but should soon be used
;;; as part of the compiler.  Any functions which do not have templates defined
;;; here have a template with an indeterminate number of expression arguments.
;;; The argument type designation means that this spot holds a designation which
;;; is only entity evaluated and never datum evaluated.  A scope is a non-atomic
;;; designation with the quantifier removed.  An other type means that it is
;;; something other than an expression, designation, or scope and should be
;;; passed through chaining analysis and compilation unchanged.


(def-function-template '(has-a-name designation))

;(def-function-template '(has-no-name designation))

(def-function-template '(is designation expression))

(def-function-template '(is-not designation expression))

(def-function-template '(is-of-class designation expression))

;(def-function-template '(is-not-of-class designation expression))

(def-function-template '(same-as designation designation))

(def-function-template '(not-same-as designation designation))

(def-function-template '(exists designation))

(def-function-template '(icon-color-of designation))

(def-function-template '(distance-between designation designation))

(def-function-template '(quote other))

(def-function-template '(distance-between-and-the-nearest designation other))

(def-function-template '(sum scope expression))

(def-function-template '(product scope expression))

(def-function-template '(maximum scope expression))

(def-function-template '(minimum scope expression))

(def-function-template '(count scope expression))

(def-function-template '(aggregated-average scope expression))

(def-function-template '(there-exists-literal scope expression))

(def-function-template '(for-every-literal scope expression))

(def-function-template '(g2-list-or-sequence-length expression))

(def-function-template '(g2-list-or-sequence-member-p expression expression))

(def-function-template '(format expression expression))

(def-function-template '(is-related expression designation designation))

(def-function-template '(is-not-related expression designation designation))

(def-function-template '(interpolated-value designation expression))

(def-function-template '(historic-value designation expression))

(def-function-template '(value-of-previous-datapoint designation expression))

(def-function-template 
  '(collection-time-of-previous-datapoint designation expression))

(def-function-template '(average-value designation expression expression))

(def-function-template '(sum-of-values designation expression expression))

(def-function-template '(maximum-value designation expression expression))

(def-function-template '(minimum-value designation expression expression))

(def-function-template '(standard-deviation designation expression expression))

(def-function-template '(integral designation expression expression expression))

(def-function-template '(rate-of-change designation expression expression expression))

(def-function-template '(number-of-datapoints designation expression expression))

(def-function-template '(is-of-class designation expression))

;(def-function-template '(is-not-of-class designation expression))

(def-function-template '(exists designation))

(def-function-template '(same-as designation designation))

(def-function-template '(not-same-as designation designation))

(def-function-template '(which-has-the-focal-object designation other))

(def-function-template '(which-has-the-focal-class designation other))

(def-function-template '(in-the-category designation other))

(def-function-template '(found-on-the-workspace designation other))

(def-function-template '(name designation))

(def-function-template '(with-notes designation))

(def-function-template '(fails-to-receive-a-value designation))

(def-function-template '(containing-symbol designation other))

(def-function-template '(containing-string designation other))

(def-function-template '(becomes-related expression designation designation))

(def-function-template '(ceases-to-be-related expression designation designation))

(def-function-template '(attribute-name designation))

(def-function-template '(in-the-tracked-item-set designation))

(def-function-template '(with-unsaved-changes designation))





;;;; Action Templates



;;; Action templates are defined here for actions that need them
;;; (for actions that do not conform to the default action template,
;;; see also documentation for def-action-template).

(def-action-template '(invoke other designation))

;; If we ever extend invoke-with-wait to be useable in rules, we will need to
;; add an action-template for it. -dkuznick, 7/20/05

(def-action-template '(halt expression))

(def-action-template '(inform message-designation message-text
			      inform-option inform-option inform-option))

(def-action-template '(show designation . show-or-hide-argument-list))

(def-action-template '(hide designation . show-or-hide-argument-list))

;(def-action-template '(change-icon-color designation color-expression))

(def-action-template '(change-item-color designation expression expression))

;(def-action-template '(change-color-pattern designation . color-changes))

(def-action-template '(change-item-color-pattern designation . color-changes))

;; The templates for change-color-pattern and change-icon-color are
;; obsolete.  -jra & ml 8/1/89

(def-action-template '(start designation expression-list
			     expression expression designation))

(def-action-template '(start-thread designation expression-list
			     expression expression designation))

(def-action-template '(kb-change designation expression expression))

(def-action-template '(add-relation other designation designation other))

(def-action-template '(remove-relation other designation designation))

(def-action-template '(create expression designation))


(def-action-template '(delete designation other))

; In version 4.0, replaced by g2-list-insert.  - cpm, 11/18/93
;(def-action-template
;  '(g2-list-insert-expression designation other expression other expression))
;
;(def-action-template
;  '(g2-list-insert-designation designation other designation other designation))

(def-action-template
  '(g2-list-insert designation expression expression other))

; In version 4.0, replaced by g2-list-remove.  - cpm, 11/18/93
;(def-action-template
;  '(g2-list-remove-expression designation other other expression))
;
;(def-action-template
;  '(g2-list-remove-designation designation other other designation))

(def-action-template
  '(g2-list-remove designation expression other other))

(def-action-template
  '(transfer designation designation expression expression))

(def-action-template
  '(update designation))

(def-action-template
  '(nupec-synchronize designation designation-list other))

(def-action-template '(create-connection other create-connection-spec designation))

(def-action-template '(create-explanation designation designation))

(def-action-template '(create-by-cloning expression designation))

(def-action-template '(make-subworkspace designation designation))

(def-action-template '(make-permanent designation))

(def-action-template '(make-transient designation))

(def-action-template '(print designation))

(def-action-template '(call-action designation expression-list
		                   designation))

(def-action-template '(call-assignment-action designation-list
		       designation expression-list designation))

; imported from the def-object-passing-system-attribute, in g2-rpc2.lisp



(def-virtual-attribute evaluation-attributes
    ((or (class procedure)
	 (class rule)
	 (class generic-action-button)
	 (class user-menu-choice)
	 (class dial)
	 (class meter)
	 (class readout-table)
	 (class freeform-table)
	 (class simulation-subtable)
	 (class trend-chart)
	 (class chart)
	 (class generic-formula)
	 (class non-action-button)
	 (class network-interface)
	 (class variable-or-parameter))
     (or (no-item)
	 (structure (;(priority                    (member 1 2 3 4 5 6 7 8 9 10))
		     ;(scan-interval               number)
		     ;(initial-scan-wait-interval  number)
		     ;(value-domain                (member
		;				    inference-engine g2-simulator))
		     ;(update-only-when-shown      truth-value)
		     ;(trace-message-level         (member 0 1 2 3))
		     ;(warning-message-level       (member 0 1 2 3))
		     ;(break-message-level         (member 0 1 2 3))
		     ;(time-out-when-requesting-data-seeking
		     ;                             integer)
		     ;(may-request-data-seeking    truth-value)
		     ;(may-request-event-updates   truth-value)
		     ;(may-provide-data-on-request truth-value)
		     ;(may-provide-event-updates   truth-value)
		     (may-refer-to-inactive-items truth-value)
		     (may-run-while-inactive      truth-value))))
     ())
  :event-updates nil
  :initial ((class) (declare (ignore class)) nil)
  :getter  ((item)
	    (let ((structure (allocate-evaluation-structure nil)))
	      (add-5.0-evaluation-settings item structure)
	      structure))
;	    (frame-class-case item
;	      (procedure
;		(get-procedure-evaluation-attributes item))
;	      (rule
;		(get-rule-evaluation-attributes item))
;	      (generic-action-button
;		(get-generic-action-button-evaluation-attributes item))
;	      (user-menu-choice
;		(get-user-menu-choice-evaluation-attributes item))
;	      ((dial meter readout-table)
;	       (get-display-evaluation-attributes item))
;	      (new-table
;		(get-new-table-evaluation-attributes item))
;	      (simulation-subtable
;		(get-simulation-subtable-evaluation-attributes item))
;	      ((trend-chart chart generic-formula non-action-button
;			    network-interface variable-or-parameter)
;	       (let ((structure (allocate-evaluation-structure nil)))
;		 (add-5.0-evaluation-settings item structure)
;		 structure)))
;	    )
  :setter
  ((item new-value)
   (when new-value
     (let ((runs-while-inactive?
	     (evaluation-structure-slot new-value 'may-run-while-inactive))
	   (refers-to-inactive-items?
	     (evaluation-structure-slot new-value 'may-refer-to-inactive-items))
	   (frame-flags (frame-flags item)))
       (setq frame-flags
	     (if (and runs-while-inactive?
		      (evaluation-truth-value-true-p runs-while-inactive?))
		 (logiorf frame-flags runs-while-inactive-flag)
		 (logandc2f frame-flags runs-while-inactive-flag)))
       (setq frame-flags
	     (if (and refers-to-inactive-items?
		      (evaluation-truth-value-true-p refers-to-inactive-items?))
		 (logiorf frame-flags may-refer-to-inactive-items-flag)
		 (logandc2f frame-flags may-refer-to-inactive-items-flag)))
       (change-slot-value item 'frame-flags frame-flags)))
   nil))

(defun-void add-5.0-evaluation-settings (item structure)
  (setf (evaluation-structure-slot structure 'may-refer-to-inactive-items)
	(make-evaluation-value-based-on-type
	  (may-refer-to-inactive-items-p item)))
  (setf (evaluation-structure-slot structure 'may-run-while-inactive)
	(make-evaluation-value-based-on-type
	  (runs-while-inactive-p item))))

;;unused except in unused add-tracing-and-breakpoint-evaluation-settings?
(defun breakdown-tracing-and-breakpoints-levels (value)
  (if value
      (let ((warning-level
	      (ash (logandf value #.(ash message-field-mask warning-shift))
		   #.(- warning-shift)))
	    (tracing-level
	      (ash (logandf value #.(ash message-field-mask tracing-shift))
		   #.(- tracing-shift)))
	    (breakpoint-level-1
	      (ash (logandf value #.(ash message-field-mask breakpoint-shift))
		   #.(- breakpoint-shift))))
	(values
	  (if (=f tracing-level message-field-mask) nil tracing-level)
	  (if (=f warning-level message-field-mask) nil warning-level)
	  (if (=f breakpoint-level-1 message-field-mask) nil breakpoint-level-1)))
      (values nil nil nil)))

;;unused except in unused functions below?
(defun-void add-tracing-and-breakpoint-evaluation-settings (item structure)
  (multiple-value-bind (tracing-level warning-level breakpoint-level)
      (breakdown-tracing-and-breakpoints-levels
	(tracing-and-breakpoints item))
    (setf (evaluation-structure-slot structure 'break-message-level)
	  breakpoint-level)
    (setf (evaluation-structure-slot structure 'tracing-message-level)
	  tracing-level)
    (setf (evaluation-structure-slot structure 'warning-message-level)
	  warning-level)))

;;unused?
(defun get-new-table-evaluation-attributes (new-table)
  (let* ((default-evaluation-setting (default-evaluation-setting new-table))
	 (feature-list
	   (loop for (feature-name feature-value) on (cdr default-evaluation-setting)
						  by #'cddr
		 collect (get-user-spelling feature-name 'part-feature) using eval-cons
		 collect (make-evaluation-value-based-on-type feature-value)
		   using eval-cons))
	 (structure (allocate-evaluation-structure feature-list)))
    (add-5.0-evaluation-settings new-table structure)
    structure))

;;unused?
(defun get-procedure-evaluation-attributes (procedure)
  (let ((structure (allocate-evaluation-structure nil)))
    (add-5.0-evaluation-settings procedure structure)
    (add-tracing-and-breakpoint-evaluation-settings procedure structure)
    structure))

;;unused?
(defun get-simulation-subtable-evaluation-attributes (subtable)
 (let ((structure (allocate-evaluation-structure nil)))
    (add-5.0-evaluation-settings subtable structure)
    (add-tracing-and-breakpoint-evaluation-settings subtable structure)
    structure))

;;unused?
(defun get-rule-evaluation-attributes (rule)
  (let ((structure
	  (allocate-evaluation-structure
	    (nconc
	      (eval-list 'priority (rule-priority rule))
	      (and
		(rule-scan-interval rule)
		(eval-list
		  'scan-interval (copy-evaluation-quantity (rule-scan-interval rule))))
	      (eval-list
		'may-request-event-updates
		(if (invocable-via-forward-chaining-p rule)
		    (make-evaluation-truth-value truth)
		    (make-evaluation-truth-value falsity)))
	      (eval-list
		'may-request-data-seeking
		(if (may-cause-data-seeking-p rule)
		    (make-evaluation-truth-value truth)
		    (make-evaluation-truth-value falsity)))
	      (eval-list
		'may-provide-data-on-request
		(if (invocable-via-backward-chaining-p rule)
		    (make-evaluation-truth-value truth)
		    (make-evaluation-truth-value falsity)))
	      (eval-list
		'may-provide-event-updates
		(if (may-cause-forward-chaining-p rule)
		    (make-evaluation-truth-value truth)
		    (make-evaluation-truth-value falsity)))))))
    (add-5.0-evaluation-settings rule structure)
    (add-tracing-and-breakpoint-evaluation-settings rule structure)
    structure))
	
;;unused?
(defun get-generic-action-button-evaluation-attributes (generic-action-button)
  (let ((structure
	  (allocate-evaluation-structure-inline
	    'priority
	    (action-button-priority-function generic-action-button))))
    (add-5.0-evaluation-settings generic-action-button structure)
    structure))

;;unused?
(defun get-user-menu-choice-evaluation-attributes (user-menu-choice)
  (let ((structure
	  (allocate-evaluation-structure-inline
	    'priority (user-menu-choice-priority user-menu-choice))))
    (add-5.0-evaluation-settings user-menu-choice structure)
    structure))

;;unused?
(defun get-display-evaluation-attributes (display)
  (let ((structure
	  (allocate-evaluation-structure
	    (nconc
	      (eval-list
		'priority (display-update-priority display))
	      (and (display-update-interval display)
		   (let ((display-update-interval? (display-update-interval display)))
		     (eval-list
		       'scan-interval
		       (if (managed-float-p display-update-interval?)
			   (copy-managed-float-into-evaluation-float
			     display-update-interval?)
			   display-update-interval?))))
	      (and (display-wait-interval display)
		   (let ((display-wait-interval? (display-wait-interval display)))
		     (eval-list
		       'initial-scan-wait-interval
		       (if (managed-float-p display-wait-interval?)
			   (copy-managed-float-into-evaluation-float
			     display-wait-interval?)
			   display-wait-interval?))))))))
    (add-tracing-and-breakpoint-evaluation-settings display structure)
    (add-5.0-evaluation-settings display structure)
    structure))

(defun get-evaluation-value-of-variable-or-parameter (variable-or-parameter
						       use-unix-time-p)
  (let* ((variable-p (variable-p variable-or-parameter))
	 (expiration-time (if variable-p
			      (expiration-time-of-current-value variable-or-parameter)
			      nil))
	 (value-is-current-p
	   (or (null expiration-time)
	       (eq expiration-time 'never)
	       (>=i expiration-time gensym-time)))
	 (current-value
	   (when value-is-current-p
	     (get-current-evaluation-value-of-variable-or-parameter
	       variable-or-parameter)))
	 (collection-time (time-of-most-recent-value variable-or-parameter)))
    (cond (use-unix-time-p
	   (when (fixnump expiration-time)
	     (setq expiration-time
		   (if (eql expiration-time *some-time-ago*)
		       nil
		       (allocate-managed-float
			(convert-gensym-time-to-unix-time expiration-time)))))
	   (setq collection-time
		 (and (managed-float-p collection-time)
		      (copy-managed-float collection-time))))
	  (t
	   (when (fixnump expiration-time)
	     (setq expiration-time
		   (if (eql expiration-time *some-time-ago*)
		       nil
		       expiration-time)))
	   (setq collection-time
		 (and (managed-float-p collection-time)
		      (allocate-managed-float
			(-e (managed-float-value collection-time)
			    (managed-float-value (clock-get g2-time-at-start))))))))
    (when (or current-value collection-time expiration-time)
      (allocate-evaluation-structure
	(nconc (and current-value
		    (eval-list 'data-point-value current-value))
	       (and collection-time
		    (eval-list 'data-point-collection-time collection-time))
	       (and expiration-time
		    (eval-list 'data-point-expiration-time expiration-time)))))))

(defun put-evaluation-value-of-variable-or-parameter (variable-or-parameter new-value use-unix-time-p)
  (let ((current-value
	  (when new-value
	    (evaluation-structure-slot new-value 'data-point-value)))
	(current-value-is-copy nil)
	(collection-time
	  (when new-value
	    (evaluation-structure-slot new-value 'data-point-collection-time)))
	(collection-time-is-new-p nil)
	(expiration-time
	  (when new-value
	    (evaluation-structure-slot new-value 'data-point-expiration-time)))
	(restore-supplied-p (and (variable-p variable-or-parameter)
				 (eq 'supplied (validity-interval variable-or-parameter))))
	(stored-type (data-type-of-variable-or-parameter variable-or-parameter)))
    (cond ((null current-value))
	  ((type-specification-type-p current-value stored-type))
	  ((and (evaluation-integer-p current-value)
		(eq stored-type 'float))
	   (setq current-value (allocate-managed-float
				 (coerce-fixnum-to-gensym-float current-value)))
	   (setq current-value-is-copy t))
	  ((and (evaluation-float-p current-value)
		(eq stored-type 'integer))
	   (setq current-value (floore-first (managed-float-value current-value)))
	   (setq current-value-is-copy t))
	  (t
	   (return-from put-evaluation-value-of-variable-or-parameter
	     (tformat-text-string "Trying to set the current value of ~NF to ~NV, which is not a ~NT"
				  variable-or-parameter current-value stored-type))))
    (when restore-supplied-p
      (setf (validity-interval variable-or-parameter) 'indefinite))
    (cond (use-unix-time-p
	   (when (managed-float-p expiration-time)
	     (setq expiration-time (convert-unix-time-to-gensym-time
				     (managed-float-value expiration-time)))))
	  (t
	   (setq collection-time
		 (when (fixnump collection-time)
		   (setq collection-time-is-new-p t)
		   (allocate-managed-float
		     (+e (coerce-fixnum-to-gensym-float collection-time)
			 (managed-float-value (clock-get g2-time-at-start))))))))
    (if collection-time
	(prog1 (with-temporary-gensym-float-creation value
		 (let ((*current-computation-frame* variable-or-parameter)
		       (old-collection-time (time-of-most-recent-value variable-or-parameter)))
		   (when (managed-float-p old-collection-time)
		     (reclaim-managed-float old-collection-time))
		   (setf (time-of-most-recent-value variable-or-parameter)
			 *some-time-ago*)
		   (if current-value
		       (put-current-evaluation-value
			 variable-or-parameter
			 (if current-value-is-copy
			     current-value
			     (copy-evaluation-value current-value))
			 expiration-time
			 collection-time
			 nil) ; override-validity-interval?
		       (put-has-no-value variable-or-parameter))))
	  (when collection-time-is-new-p
	    (reclaim-evaluation-value collection-time))
	  (when restore-supplied-p
	    (setf (validity-interval variable-or-parameter) 'supplied)))
	(prog1 (put-current-value-for-virtual-attribute variable-or-parameter current-value)
	  (when current-value-is-copy
	    (reclaim-evaluation-value current-value))))))

(def-virtual-attribute value-structure
    ((class variable-or-parameter)
     (or (no-item)
	 (structure ((data-point-value datum)
		     (data-point-collection-time number)
		     (data-point-expiration-time (or number (member never))))))
     ())
  :event-updates nil
  :initial ((class) (declare (ignore class)) nil)
  :getter ((variable-or-parameter)
	   (get-evaluation-value-of-variable-or-parameter variable-or-parameter nil))
  :setter ((variable-or-parameter new-value)
	   (put-evaluation-value-of-variable-or-parameter variable-or-parameter new-value nil)))

(def-virtual-attribute value-structure-using-unix-time
    ((class variable-or-parameter)
     (or (no-item)
	 (structure ((data-point-value datum)
		     (data-point-collection-time number)
		     (data-point-expiration-time (or number (member never))))))
     ())
  :event-updates nil
  :initial ((class) (declare (ignore class)) nil)
  :getter ((variable-or-parameter)
	   (get-evaluation-value-of-variable-or-parameter variable-or-parameter t))
  :setter ((variable-or-parameter new-value)
	   (put-evaluation-value-of-variable-or-parameter variable-or-parameter new-value t)))

(defun put-current-value-for-virtual-attribute (variable-or-parameter new-value)
  (cond
    (new-value
      (with-temporary-gensym-float-creation value
	(let ((*current-computation-frame* variable-or-parameter))
	  (cond
	    ((variable-or-parameter-stored-histories? variable-or-parameter)
	     (let* ((g2-time-at-start
		      (or ;;(remote-g2-time-at-start? current-receiving-resumable-object)
			(clock-get g2-time-at-start)))
		    (collection-time-for-put-current-evaluation-value
		      (get-default-collection-time-for-put-current-value
			variable-or-parameter))
		    (previous-time-of-most-recent-value
		      (time-of-most-recent-value variable-or-parameter)))
	       (reclaim-evaluation-value previous-time-of-most-recent-value)
	       (setf (time-of-most-recent-value variable-or-parameter)
		     *some-time-ago*)
	       (put-current-value-for-virtual-attribute-1
		 variable-or-parameter
		 new-value
		 collection-time-for-put-current-evaluation-value
		 'problem-putting-current-value-into-history-keeper)))
	    (t (put-current-value-for-virtual-attribute-1
		 variable-or-parameter
		 new-value
		 nil
		 'problem-putting-current-value-into-variable-or-parameter))))))
    ((variable-p variable-or-parameter)
     (put-has-no-value variable-or-parameter))
    (t
     (tformat-text-string "Can't assign No Value to parameter ~NF"
			  variable-or-parameter))))

(defun put-current-value-for-virtual-attribute-1
    (variable-or-parameter new-value collection-time? potential-problem-name)
  (declare (ignore potential-problem-name))
  (let ((restore-supplied-p (and (variable-p variable-or-parameter)
				 (eq 'supplied (validity-interval variable-or-parameter)))))
    (when restore-supplied-p
      (setf (validity-interval variable-or-parameter) 'indefinite))
    (prog1 (put-current-evaluation-value
	     variable-or-parameter
	     (copy-evaluation-value new-value)
	     nil
	     collection-time?
	     nil)
      (when restore-supplied-p
	(setf (validity-interval variable-or-parameter) 'supplied)))))

(def-virtual-attribute last-recorded-value-text
    ((class variable-or-parameter)
     (or (no-item)
	 text)
     ())
  :event-updates nil
  :initial ((class) (declare (ignore class)) nil)
  ;; Consider abstracting part of write-entity-in-slot and using that
  ;; -dkuznick, 3/2/05 
  :getter ((variable-or-parameter)
	   (let ((text-to-return
		   ;; Special case for after a restart. -dkuznick, 3/4/05
		   (when (and (variable-p variable-or-parameter)
			      (eql (time-of-most-recent-value
				     variable-or-parameter)
				   *some-time-ago*))
		     (make-evaluation-text #w"****"))))
	     (if text-to-return
		 text-to-return
		 (let ((value?
			 (get-current-evaluation-value-of-variable-or-parameter
			   variable-or-parameter)))
		   (prog1
		       (twith-output-to-text-string
			 (if value?
			     (write-evaluation-value value?)
			     (twrite #w"****"))
			 (when (and value?
				    (variable-p variable-or-parameter)
				    (not (value-of-variable-is-current
					   variable-or-parameter)))
			   (twrite #w"*")))
		     (reclaim-if-evaluation-value value?)))))))

(def-virtual-attribute effective-data-type
    ((or (class variable-or-parameter) (class simulation-subtable))
     symbol
     ())
  :event-updates nil
  :initial ((class) (declare (ignore class)) nil)
  :getter ((item)
	   (let ((variable-or-parameter
		   (frame-class-case item
		     (variable-or-parameter item)
		     (simulation-subtable (parent-variable item)))))
	     (when variable-or-parameter
	       (let ((stored-data-type
		       (data-type-of-variable-or-parameter variable-or-parameter)))
		 ;;see type-specification-of-variable-or-parameter-value
		 (cond ((symbolic-type-specification-subtype-p stored-data-type 'datum)
			(case stored-data-type
			  (datum 'value)
			  (number 'quantity)
			  (t stored-data-type)))
		       ((number-subtype-p stored-data-type)
			'quantity)
		       (t
			'value)))))))



;;; `Get-item-history-information'  returns nil if item can not store a history;
;;;  otherwise it returns these four values:
;;;
;;;    (1) simulated-value-p (true iff history values are simulated);
;;;    (2) data-type (see the effective-data-type virtual-attribute)
;;;    (3) history-specification (might be nil)
;;;    (4) history-enclosure (the "cascade" argument to history iterators)
;;;        when the argument make-history-enclosure-if-not-present-p is non-NIL,
;;;        a history-enclosure will be created if it doesn't already exist.
;;;
;;; At present, this is a private subfunction of get-item-history-information
;;; and set-item-history-information.  However, it may be further generalized
;;; and then exported at some future point in time.

(defun get-item-history-information (item make-history-enclosure-if-not-present-p)
  (let* ((storing-simulated-value?
	   (frame-class-case item
	     (variable-or-parameter nil)
	     (simulation-subtable t)
	     (t (return-from get-item-history-information nil))))
	 (item-for-specs
	   (if storing-simulated-value?
	       (parent-variable item)
	       item)))
    (when (and storing-simulated-value?
	       (not (of-class-p item-for-specs 'variable-or-parameter)))
      (return-from get-item-history-information nil))
    (let ((history-specification
	    (variable-or-parameter-history-specification? item-for-specs)))
      (values storing-simulated-value?
	      (type-specification-of-variable-or-parameter-value item-for-specs)
	      history-specification
	      (when history-specification
		(if make-history-enclosure-if-not-present-p
		    (get-or-make-history-buffer item history-specification)
		    (if storing-simulated-value?
			(simulation-stored-histories? item)
			(variable-or-parameter-stored-histories? item))))))))

(defun-simple get-history-evaluation-structure (item use-unix-time-p)
  (multiple-value-bind (storing-simulated-value? data-type
			history-specification history-enclosure?)
      (get-item-history-information item nil)
    (declare (ignore history-specification))
    (when history-enclosure?
      (get-history-evaluation-structure-from-cascade
	history-enclosure? data-type storing-simulated-value? use-unix-time-p nil nil))))

;;; There is now an optimized version of this called:
;;; get-trend-chart-history-evaluation-structure-from-cascade.
;;; please consider that function when making any changes to
;;; this one.

(defun-simple get-history-evaluation-structure-from-cascade
    (history-enclosure? data-type storing-simulated-value? use-unix-time-p
			start-index end-index)
  (let ((history-elements nil))
    (unless (cascaded-ring-buffer-empty? history-enclosure?)
      (iterate-over-history-using-evaluation-values
	(history-value history-collection-time)
	(history-enclosure? (eq data-type 'truth-value) use-unix-time-p storing-simulated-value?
			    start-index end-index)
	(eval-push
	  (allocate-evaluation-structure-inline
	    'history-value history-value
	    'history-collection-time history-collection-time)
	  history-elements))
      (allocate-evaluation-sequence (nreverse history-elements)))))

(defun-simple set-history-evaluation-structure (item use-unix-time-p new-value)
  (multiple-value-bind (storing-simulated-value? data-type
			history-specification history-enclosure?)
      (get-item-history-information item t)
    (when history-specification
      (clear-history-buffer history-enclosure?)
      (when new-value
	(loop for history-element being each evaluation-sequence-element of new-value
	      for value = (evaluation-structure-slot history-element 'history-value)
	      unless (or (type-specification-type-p value data-type)
			 (and (evaluation-integer-p value)
			      (eq data-type 'float))
			 (and (evaluation-float-p value)
			      (eq data-type 'integer)))
		do (return-from set-history-evaluation-structure
		     (tformat-text-string
		       "Trying to set a history value of ~NF to ~NV, which is not a ~NT"
		       item value data-type)))
	(loop with logicalp = (eq data-type 'truth-value)
	      for firstp = t then nil
	      for history-element being each evaluation-sequence-element of new-value
	      for value = (evaluation-structure-slot history-element 'history-value)
	      for timestamp = (evaluation-structure-slot history-element 'history-collection-time)
	      for value-is-copy = (cond ((type-specification-type-p value data-type)
					 nil)
					((and (evaluation-integer-p value)
					      (eq data-type 'float))
					 (setq value (allocate-managed-float
						       (coerce-fixnum-to-gensym-float value)))
					 t)
					((and (evaluation-float-p value)
					      (eq data-type 'integer))
					 (setq value (floore-first (managed-float-value value)))
					 t))
	      do
	  ;; The history subtest (and other subtests, too) of itempass.kb fails
	  ;; without this.
	  (when firstp
	    (setf (cascaded-ring-buffer-base-time? history-enclosure?)
		  (copy-managed-float timestamp)))
	  (unless (or (evaluation-integer-p timestamp)
		      (evaluation-float-p timestamp))
	    (setq timestamp 0))
	  (unless use-unix-time-p
	    (let ((gensym-time-since-start
		    (cond ((evaluation-integer-p timestamp)
			   (coerce-fixnum-to-gensym-float timestamp))
			  ((evaluation-float-p timestamp)
			   (evaluation-float-value timestamp))
			  (t 0.0d0)))) ; make compiler happy
	      (declare (type gensym-float gensym-time-since-start))
	      (setq timestamp (allocate-managed-float
				(+e (managed-float-value (clock-get g2-time-at-start))
				    gensym-time-since-start)))))
	  (store-history-value history-enclosure? history-specification
			       (if logicalp
				   (evaluation-truth-value-value value)
				   value)
			       timestamp
			       storing-simulated-value?)
	  (when value-is-copy
	    (reclaim-evaluation-value value))
	  (unless use-unix-time-p
	    (reclaim-managed-float timestamp)))
	nil))))

(def-virtual-attribute history
    ((or (class variable-or-parameter) (class simulation-subtable))
     (or (no-item)
	 (sequence
	   (structure ((history-value datum)
		       (history-collection-time float))
		      (and history-value history-collection-time))
	   1))
     (exclude-from-wildcard-denotation t))
  :event-updates nil
  :initial ((class) (declare (ignore class)) nil)
  :getter  ((item)
	    (get-history-evaluation-structure item nil))
  :setter  ((item new-value)
	    (set-history-evaluation-structure item nil new-value)
	    nil))

(def-virtual-attribute history-using-unix-time
    ((or (class variable-or-parameter) (class simulation-subtable))
     (or (no-item)
	 (sequence
	   (structure ((history-value datum)
		       (history-collection-time float))
		      (and history-value history-collection-time))
	   1))
     (exclude-from-wildcard-denotation t))
  :event-updates nil
  :initial ((class) (declare (ignore class)) nil)
  :getter  ((item)
	    (get-history-evaluation-structure item t))
  :setter  ((item new-value)
	    (set-history-evaluation-structure item t new-value)))

(def-virtual-attribute g2-array-sequence
    ((class g2-array)
     ;; inactive arrays, or perm. arrays that have not been initialized 
     ;; return no-item (aka nil)
     (or (no-item) (sequence))
     (exclude-from-wildcard-denotation t))
  :event-updates nil
  :initial ((class) (declare (ignore class)) nil)
  :getter  ((g2-array)
	    (if (or (array-is-permanent g2-array)
		    (active-p g2-array))
		(allocate-evaluation-sequence
		  (when (managed-g2-array g2-array) ; not necessary, because it it's null, length will be 0
		    (loop for index from 0 below (g2-array-length g2-array)
			  for value = (g2-array-aref-item-or-evaluation-value g2-array index)
			  collect (if (or (not (framep value))
					  (serve-item-p value))
				      value
				      nil)
			    using eval-cons)))
		nil))
  :setter
  ((g2-array new-value)
   (cond
     ((null new-value) ; conclude has no-value case
      (if (managed-g2-array g2-array)
	  (tformat-text-string
	    "cannot reset/disable array ~NF by concluding no-value in g2-array-sequence"
	    g2-array)
	  nil))
     ((not (or (array-is-permanent g2-array)
	       (active-p g2-array)))
      (tformat-text-string
	"Cannot set the g2-array-sequence of ~NF because it is neither a permanent array nor active"
	g2-array))
     (t
      (let ((element-type (g2-array-element-type g2-array))
	    (length 0)
	    (length-sd (get-slot-description-of-frame 'g2-array-length g2-array))
	    (error-string nil))
	(loop with allow-no-value-p = (or (not (null (class-description element-type)))
					  (eq element-type 'item-or-datum))
	      for item-or-datum? being each evaluation-sequence-element of new-value
	      do
	  (unless (or (and allow-no-value-p (null item-or-datum?))
		      (type-specification-type-p item-or-datum? element-type)
		      (of-class-p item-or-datum? element-type))
	    (setq error-string (tformat-text-string
				 "element ~D, ~NA, is not of type ~S" length
				 item-or-datum?
				 (case element-type
				   (item-or-datum 'item-or-value)
				   (datum 'value)
				   (number 'quantity)
				   (t element-type))))
	    (return nil))
	  (incff length))
	(cond
	  (error-string
	   error-string)
	  (t
	   (let* ((existing-length (get-slot-description-value g2-array length-sd))
		  (desired-length (if append-into-arrays-and-lists
				      (+f existing-length length)
				      length)))
	     (unless (=f existing-length desired-length)
	       (change-slot-description-value g2-array length-sd desired-length))
	     (loop with delete-p = delete-old-elements-from-arrays-and-lists
		   for index from (if append-into-arrays-and-lists
				      existing-length
				      0)
		   for current-element = (when delete-p
					   (g2-array-aref-item-or-evaluation-value g2-array index))
		   for item-or-datum? being each evaluation-sequence-element of new-value
		   do
	       (mutate-g2-array g2-array index (copy-if-evaluation-value item-or-datum?) t t)
	       (when (framep current-element)
		 (delete-frame-for-rpc current-element)))
	     nil))))))))
   
   
(defun-simple get-list-contents-as-sequence (g2-list)
  (allocate-evaluation-sequence
    (and (not (g2-list-empty-p g2-list))
	 (loop for item-or-evaluation-value-element
		   being each g2-list-element in g2-list
	       when (or (not (framep item-or-evaluation-value-element))
			(serve-item-p item-or-evaluation-value-element))
		 collect (copy-if-evaluation-value item-or-evaluation-value-element)
		   using eval-cons))))

(def-virtual-attribute g2-list-sequence
    ((class g2-list) (sequence) (exclude-from-wildcard-denotation t))
  :event-updates nil
  :initial ((class) (declare (ignore class)) nil)
  :getter  ((g2-list)
	    (get-list-contents-as-sequence g2-list))
  :setter ((g2-list new-value)
	   (let ((element-type (list-type g2-list))
		 (error-string nil))
	     (loop with allow-no-value-p = (or (not (null (class-description element-type)))
					       (eq element-type 'item-or-datum))
		   for item-or-datum? being each evaluation-sequence-element of new-value
		   for length from 0
		   do
	       (unless (or (and allow-no-value-p (null item-or-datum?))
			   (type-specification-type-p item-or-datum? element-type)
			   (of-class-p item-or-datum? element-type))
		 (setq error-string (tformat-text-string "element ~D, ~NA, is not of type ~S"
							 length
							 item-or-datum?
							 (case element-type
							   (item-or-datum 'item-or-value)
							   (datum 'value)
							   (number 'quantity)
							   (t element-type))))
		 (return nil)))
	     (cond
	       (error-string
		error-string)
	       (t
		(unless append-into-arrays-and-lists
		  (when delete-old-elements-from-arrays-and-lists
		    (loop with frames-to-delete
			  = (loop for item-or-evaluation-value-element
				      being each g2-list-element in g2-list
				  when (framep item-or-evaluation-value-element)
				    collect item-or-evaluation-value-element
				      using gensym-cons)
			  for frame? in frames-to-delete
			  do (delete-frame frames-to-delete)
			  finally (reclaim-gensym-list frames-to-delete)))
		  (clear-g2-list g2-list))
		(loop for element being each evaluation-sequence-element of new-value
		      do
		  (g2-list-insert-at-end (copy-if-evaluation-value element)
					 g2-list t)) ;override-any-test-for-duplicates-p?
		nil)))))

(define-category-evaluator-interface (g2-array-length
				       :access read-write)
    integer
  ((set-form (evaluation-value))
   evaluation-value)
  ((get-form (slot-value))
   slot-value))

(define-category-evaluator-interface (element-type
				       :access read)
    (member value item-or-value quantity text truth-value
	    item integer float symbol)
  ((get-form (slot-value))
   (case slot-value
     (datum 'value)
     (item-or-datum 'item-or-value)
     (number 'quantity)
     (t slot-value))))

;(define-category-evaluator-interface (yes-or-no?
;				       :access read-write)
;    truth-value
;  ((set-form (evaluation-value))
;   (evaluation-truth-value-is-true-p evaluation-value))
;  ((get-form (slot-value))
;   (make-evaluation-boolean-value slot-value)))
;
;; Category expunged 12/18/96. See Tables.

;;; `Copy-evaluation-constant-to-phrase' is not as general as its name sounds.
;;; In fact, it is only used in the setters of a few category-evaluator
;;; interfaces.  It performs obtuse manipulations of data to get the phrase-cons
;;; tree "just-right" to be copied to the slot-value pool.  This means it must
;;; handle sequences and structures and the weird quotation of symbols with
;;; symbol-initial-value-marker (to distinguish them from item names).

(defun copy-evaluation-constant-to-phrase (element top-level-p items-allowed-p)
  (cond
    ((evaluation-symbol-p element)
     (if (and top-level-p items-allowed-p)
	 (phrase-list symbol-initial-value-marker element)
	 element))
    ((evaluation-integer-p element)
     element)
    ;; I (MHD) don't see why the copying as a phrase does go down to all levels
    ;; -- I believe this is at best a leak, if not a source of corruption. But
    ;; should be studied further.  (MHD 5/13/97)
    ((evaluation-float-p element)
     (if top-level-p
	 (evaluation-quantity-to-phrase-quantity element)
	 (copy-evaluation-value element)))
    ((evaluation-text-p element)
     (if top-level-p
	 (copy-for-phrase element)
	 (copy-evaluation-value element)))
    ((evaluation-truth-value-p element)
     (if top-level-p
	 (make-slot-constant-using-phrase-conses
	   (evaluation-truth-value-value element)
	   'truth-value)
	 (copy-evaluation-value element)))
    ((evaluation-structure-p element)
     (copy-evaluation-structure-to-phrase element))
    ((evaluation-sequence-p element)
     (copy-evaluation-sequence-to-phrase element))
    ((framep element)
     (let ((designation? (generate-designation-for-block element)))
       (cond
	 (designation?
	  designation?)
	 (t
	  (values
	    bad-phrase
	    (tformat-text-string
	      "There is no g2 expression that names ~NF" element))))))
    (t
     #+development
     (cerror "go on"
	     "unexpected thing in list-of-item-and-datum-constants? setter")
     nil)))



;;; `Copy-evaluation-structure-to-phrase' is similar, but starts with an
;;; evaluation value specifically of type evaluation-structure.

(defun copy-evaluation-structure-to-phrase (evaluation-structure)
  (loop with value-as-phrase
	with error-string?
	for (name . value)
	    being each evaluation-structure-pair of evaluation-structure
	do (multiple-value-setq (value-as-phrase error-string?)
	     (copy-evaluation-constant-to-phrase value nil nil))
	when (eq value-as-phrase bad-phrase)
	  return (values bad-phrase error-string?)
	collect name into plist using phrase-cons 
	collect value-as-phrase into plist using phrase-cons
	finally
	  (return
	    (make-phrase-structure plist))))



;;; `Copy-evaluation-sequence-to-phrase' is similar, but starts with an
;;; evaluation value specifically of type evaluation-sequence.

(defun copy-evaluation-sequence-to-phrase (evaluation-sequence)  
  (loop with element-as-phrase
	with error-string?
	for element
	    being each evaluation-sequence-element of evaluation-sequence
	do (multiple-value-setq (element-as-phrase error-string?)
	     (copy-evaluation-constant-to-phrase element nil nil))
	when (eq element-as-phrase bad-phrase)
	  return (values bad-phrase error-string?)
	collect element-as-phrase into list-of-elements using phrase-cons
	finally
	  (return
	    (make-phrase-sequence list-of-elements))))


(defvar array-initialization-evaluation-values-use-designations-p t)
(defvar designation-marker (list 'designation-marker))

(defun-simple symbol-or-class-qualified-name-to-evaluation-value (name)
  (if (consp name)
      (when (eq (car name) 'class-qualified-name)
	(allocate-evaluation-structure-inline
	  'class (cadr name)
	  'name (caddr name)))
      name))

(defun-simple constant-designation-to-evaluation-value (designation)
  (or (symbol-or-class-qualified-name-to-evaluation-value designation)
      (when (and (consp designation) (eq (car designation) 'the))
	(allocate-evaluation-structure-inline
	  'name (or (symbol-or-class-qualified-name-to-evaluation-value (cadr designation))
		    (and (consp (cadr designation))
			 (symbol-or-class-qualified-name-to-evaluation-value (caadr designation))))
	  'item (constant-designation-to-evaluation-value (caddr designation))))))

(defun-simple evaluation-value-to-symbol-or-class-qualified-name-phrase (value)
  (cond ((symbolp value)
	 value)
	((evaluation-structure-p value)
	 (let ((class (evaluation-structure-slot value 'class))
	       (name  (evaluation-structure-slot value 'name)))
	   (when (and class name)
	     (phrase-list 'class-qualified-name class name))))))

(defun evaluation-value-to-constant-designation-phrase (value)
  (cond ((evaluation-value-to-symbol-or-class-qualified-name-phrase value))
	((not (evaluation-structure-p value))
	 (values nil (copy-constant-wide-string #w"not a legal designation")))
	(t
	 (let ((name  (evaluation-structure-slot value 'name))
	       (item  (evaluation-structure-slot value 'item)))
	   (cond ((and name item)
		  (phrase-list
		    'the
		    (evaluation-value-to-symbol-or-class-qualified-name-phrase name)
		    (evaluation-value-to-constant-designation-phrase item)))
		 (t
		  (values nil (copy-constant-wide-string #w"not a legal designation"))))))))

(defun initial-values-to-evaluation-value (slot-value values-allowed-p items-allowed-p)
  (cond
    ((null slot-value)
     nil)
    (t
     (loop with any-designation-p = nil
	   with any-value-p = nil
	   with use-designations-p = array-initialization-evaluation-values-use-designations-p
	   for element in slot-value
	   for evaluation-value
	       = (cond
		   ((text-string-p element)
		    (make-evaluation-text element))
		   ((managed-float-p element)
		    (copy-managed-float-into-evaluation-float element))
		   ((and (consp element)
			 (consp (cdr element))
			 (eq (cadr element) 'truth-value))
		    (make-evaluation-truth-value (car element)))
		   ((initial-value-symbol-p element)
		    (make-evaluation-symbol (initial-value-symbol-value element)))
		   ((fixnump element)
		    element)
		   ((or (evaluation-sequence-p element)
			(evaluation-structure-p element))
		    (copy-evaluation-value element))
		   ((not items-allowed-p)
		    element)
		   (use-designations-p
		    designation-marker)
		   (t
		    (or (evaluate-designation element nil)
			(tformat-text-string "Could not find item for ~ND" element))))
	   for designation-p = (eq evaluation-value designation-marker)
	   do (if designation-p
		  (setq any-designation-p t)
		  (setq any-value-p t))
	   collect (if designation-p nil evaluation-value)
	     into values-list using eval-cons
	   collect (if designation-p (constant-designation-to-evaluation-value element) nil)
	     into designations-list using eval-cons
	   finally (let ((values-sequence
			   (if (and any-value-p
				    (or values-allowed-p (not use-designations-p)))
			       (allocate-evaluation-sequence values-list)
			       (progn (reclaim-eval-list values-list) nil)))
			 (designations-sequence
			   (if (and any-designation-p items-allowed-p)
			       (allocate-evaluation-sequence designations-list)
			       (progn (reclaim-eval-list designations-list) nil))))
		     (return
		       (if (and values-allowed-p items-allowed-p designations-sequence)
			   (allocate-evaluation-structure
			     (nconc (when values-sequence
				      (eval-list 'values values-sequence))
				    (eval-list 'items designations-sequence)))
			   (or values-sequence designations-sequence))))))))

(defun sequences-to-initial-values-phrase (values items values-allowed-p items-allowed-p)
  (declare (ignore values-allowed-p))
  (block setter
    (phrase-cons
      'normalized
      (loop with values-length = (if values
				     (evaluation-sequence-length values)
				     0)
	    with items-length = (if items
				    (evaluation-sequence-length items)
				    0)
	    for index from 0 below (maxf values-length items-length)
	    for value? = (when (<f index values-length)
			   (evaluation-sequence-ref values index))
	    for item-designation? = (when (<f index items-length)
				      (evaluation-sequence-ref items index))
	    collect (or (when value?
			  (multiple-value-bind (phrase-value error-string?)
			      (copy-evaluation-constant-to-phrase value? t items-allowed-p)
			    (cond
			      ((eq phrase-value bad-phrase)
			       (return-from setter
				 (values bad-phrase error-string?)))
			      (t
			       phrase-value))))
			(evaluation-value-to-constant-designation-phrase item-designation?))
	      using phrase-cons))))

(defun evaluation-value-to-initial-values-phrase (evaluation-value values-allowed-p items-allowed-p)
  (evaluation-etypecase evaluation-value
    ((no-item) 'nil)
    ((sequence)
     (sequences-to-initial-values-phrase
       (when values-allowed-p
	 evaluation-value)
       (when (and items-allowed-p (not values-allowed-p))
	 evaluation-value)
       values-allowed-p
       items-allowed-p))
    ((structure)
     (let ((values (evaluation-structure-slot evaluation-value 'values))
	   (items  (evaluation-structure-slot evaluation-value 'items)))
       (sequences-to-initial-values-phrase values items values-allowed-p items-allowed-p)))))

(define-category-evaluator-interface (list-of-item-and-datum-constants?
				       :access read-write)
    (or (no-item)
	(sequence item-or-datum 1)
	(structure items-and-values
		   ((values (sequence (or item-or-datum (no-item)) 1))
		    (items (sequence (or datum (no-item)) 1)))
		   (and items)))
  ((set-form (evaluation-value))
   (evaluation-value-to-initial-values-phrase evaluation-value t t))
  ((get-form (slot-value frame))
   (let ((*current-computation-frame* frame))
     (initial-values-to-evaluation-value slot-value t t))))

(define-category-evaluator-interface (constant-designation-list?
				       :access read-write)
     (or (no-item)
	 (sequence (class item) 1)
	 (sequence datum 1))
  ((set-form (evaluation-value))
   (evaluation-value-to-initial-values-phrase evaluation-value nil t))
  ((get-form (slot-value frame))
   (let ((*current-computation-frame* frame))
     (initial-values-to-evaluation-value slot-value nil t))))

(define-category-evaluator-interface (list-of-datum-constants
				       :access read-write)
   (sequence datum 1)
  ((set-form (evaluation-value))
   (evaluation-value-to-initial-values-phrase evaluation-value t nil))
  ((get-form (slot-value))
   (initial-values-to-evaluation-value slot-value t nil)))

(define-category-evaluator-interface (symbol-list
					:access read-write)
    (sequence symbol 1)
  ((set-form (evaluation-value))
   (let ((thing))
     (with-evaluation-sequence-to-phrase-list-mapping (evaluation-value element)
       (if (null thing)
	   (setf thing (phrase-list '\, element))
	   (setf thing (phrase-list '\, thing element))))
     thing))
  ((get-form (slot-value))
   (with-list-to-evaluation-sequence-mapping (slot-value element)
     element)))

(define-category-evaluator-interface (whole-string-list
					:access read-write)
    (sequence text 1)
  ((set-form (evaluation-value))
   (let (thing)
     (with-evaluation-sequence-to-phrase-list-mapping (evaluation-value element)
       (if (null thing)
	   (setf thing (phrase-list '\, (copy-for-phrase (evaluation-text-value element))))
	   (setf thing (phrase-list '\, thing (copy-for-phrase (evaluation-text-value element))))))
     thing))
  ((get-form (slot-value))
   (with-list-to-evaluation-sequence-mapping (slot-value element)
     (make-evaluation-text element)))) 
     
    
(define-category-evaluator-interface (truth-value-list
				       :access read-write)
    (sequence truth-value 1)
  ((set-form (evaluation-sequence))
   (block set-form-for-truth-value-list
     (phrase-cons
       'normalized			; see note
       (with-evaluation-sequence-to-phrase-list-mapping
	   (evaluation-sequence evaluation-value)
	 (unless (evaluation-truth-value-p evaluation-value)
	   (return-from set-form-for-truth-value-list
	     (values bad-phrase
		     (tformat-text-string
		       "Illegal value, ~NV; it should be of type truth-value"
		       evaluation-value))))
	 (evaluation-truth-value-value evaluation-value)))))
  ((get-form (slot-value))
   (with-list-to-evaluation-sequence-mapping (slot-value element)
     (make-evaluation-truth-value element))))

;; Note that we are generating a normalized result, so we need to put it in
;; terms of the result of a compilation for truth-value-list, which means as a
;; flat list of integers in the range [-1000..1000]; see the compiler for
;; truth-value-list, which works hand in glove with this.  (MHD 5/13/97)



(define-category-evaluator-interface (quantity-list
				       :access read-write)
    (sequence number 1)
  ((set-form (evaluation-value))
   (let ((thing))
     (with-evaluation-sequence-to-phrase-list-mapping (evaluation-value element)
       (if (null thing)
	   (setf thing (phrase-list '\, (evaluation-quantity-to-phrase-quantity element)))
	   (setf thing (phrase-list '\, thing (evaluation-quantity-to-phrase-quantity
						element)))))
     thing))   
  ((get-form (slot-value))
   (with-list-to-evaluation-sequence-mapping (slot-value element)
     (if (managed-float-p element)
	 (copy-managed-float-into-evaluation-float element)
	 element))))

(define-category-evaluator-interface (float-list
				       :access read-write)
    (sequence float 1)
  ((set-form (evaluation-value))
   (let ((thing))
     (with-evaluation-sequence-to-phrase-list-mapping (evaluation-value element)
       (if (null thing)
	   (setf thing (phrase-list '\, (evaluation-quantity-to-phrase-quantity element)))
	   (setf thing (phrase-list '\, thing (evaluation-quantity-to-phrase-quantity
						element)))))
     thing))
  ((get-form (slot-value))
   (with-list-to-evaluation-sequence-mapping (slot-value element)
     (copy-managed-float-into-evaluation-float element))))

(define-category-evaluator-interface (integer-list
				       :access read-write)
    (sequence integer 1)
 ((set-form (evaluation-value))
  (let ((thing))
    (with-evaluation-sequence-to-phrase-list-mapping (evaluation-value element)
      (if (null thing)
	  (setf thing (phrase-list '\, element))
	  (setf thing (phrase-list '\, thing element))))
    thing))
 ((get-form (slot-value))
  (with-list-to-evaluation-sequence-mapping (slot-value element)
    element)))


;;;; Category Evaluator Interfaces for Menu-parameters


(define-category-evaluator-interface (alignment
				       :access read-write)
    (member left center right)
  ((set-form (evaluation-value))
   evaluation-value)
  ((get-form (slot-value))
   slot-value))
    
(define-category-evaluator-interface (when-to-allow-multiple-menus
				       :access read-write)
   (member never always for-different-selections)
  ((set-form (evaluation-value)) 
   (if (eq evaluation-value 'for-different-selections)
       'if-different
       evaluation-value))
  ((get-form (slot-value))
   (if (eq slot-value 'if-different)
       'for-different-selections
       slot-value)))


;;;; Category Evaluator Interfaces for Language-parameters


(define-category-evaluator-interface (current-language
				       :access read-write)
    symbol
  ((set-form (evaluation-value))
   evaluation-value)
  ((get-form (slot-value))
   (cond
     (slot-value
      slot-value)
     (t
      default-language))))



;;;; Category Evaluator Interfaces for Color-parameters


(define-category-evaluator-interface (color-menu-ordering
				       :access read-write)
    (member intensity alphabetic hue)
  ((set-form (evaluation-value))
   evaluation-value)
  ((get-form (slot-value))
   slot-value))

(define-category-evaluator-interface (color-set-spec
				       :access read-write)
    (or (member all none standard-set)
	(sequence (named color-or-metacolor) 1))
  ((set-form (evaluation-value))
   (evaluation-etypecase evaluation-value
    (symbol
     evaluation-value)
    ((sequence)
     (nconc
       (phrase-list '\,)
       (with-evaluation-sequence-to-phrase-list-mapping
	   (evaluation-value element)
	 element)))))
  ((get-form (slot-value))
   (cond
     (slot-value
      (if (consp slot-value)
	  (with-list-to-evaluation-sequence-mapping (slot-value element)
	    element)
	  slot-value))
     (t
      'none))))

(define-category-evaluator-interface (number-of-menu-columns-spec
				       :access read-write)
    (member 1 2 3 4 5 6 7)
  ((set-form (evaluation-value))
   evaluation-value)
  ((get-form (slot-value))
   slot-value))


;;;; Category Evaluator interfaces for Drawing-parameters


(define-category-evaluator-interface (image-palette
				       :access read-write)
    (or (member black-and-white standard-grays standard-colors
		extended-grays extended-colors)
	(structure image-palette-spec
		   ((palette-name (member custom-grays custom-colors))
		    (image-name symbol))
		   (and palette-name image-name)))
  ((set-form (evaluation-value))
   (evaluation-etypecase evaluation-value
    (symbol
     evaluation-value)
    ((structure)
     (with-structure (evaluation-value image-palette-spec)
       (phrase-list palette-name image-name)))))
  ((get-form (slot-value))
   (cond
     ((consp slot-value)
      (with-new-structure (image-palette-spec)
	(setf palette-name (first slot-value))
	(setf image-name (second slot-value))))
     (t
      slot-value))))




;;;; Category Evaluator interfaces for Debugging-Parameters



(define-category-evaluator-interface (warning-message-level
				       :access read-write)
    (member 0 1 2 3)
  ((set-form (evaluation-value))
   evaluation-value)
  ((get-form (slot-value))
   slot-value))

(define-category-evaluator-interface (tracing-message-level
				       :access read-write)
    (member 0 1 2 3)
  ((set-form (evaluation-value))
   evaluation-value)
  ((get-form (slot-value))
   slot-value))

(define-category-evaluator-interface (breakpoint-level
				       :access read-write)
    (member 0 1 2 3)
  ((set-form (evaluation-value))
   evaluation-value)
  ((get-form (slot-value))
   slot-value))

(define-category-evaluator-interface (source-stepping-level
				       :access read-write)
    (member 0 1)
  ((set-form (evaluation-value))
   evaluation-value)
  ((get-form (slot-value))
   slot-value))


(define-category-evaluator-interface (interface-warning-message-level
				       :access read-write)
    (member warning-message-level 0 1 2 3)
  ((set-form (evaluation-value))
   evaluation-value)
  ((get-form (slot-value))
   slot-value))

;; The define-category-evaluator-interface for NUPEC-TRACE-FILE-PATHNAME was
;; moved to grammar5 because it depends on the category evaluator for
;; whole-string.  - cpm, 7/1/96



;cell-expression-and-text
;(define-text-category-evaluator-interface command)
;(define-text-category-evaluator-interface generic-file-pathname)
;(define-text-category-evaluator-interface file-command)
;(define-text-category-evaluator-interface init-file-command)
;(define-text-category-evaluator-interface query-command)

;(define-text-category-evaluator-interface gesture-definition)
;nil  ; search for "(type nil text" boxes books edit1
;(define-text-category-evaluator-interface plot-expression)
;(define-text-category-evaluator-interface resource-definition)
;(define-text-category-evaluator-interface simple-formatted-text)
;(define-text-category-evaluator-interface statement)

(define-text-category-evaluator-interface display-expression)
(define-text-category-evaluator-interface embedded-rule t)
(define-text-category-evaluator-interface expression)
(define-text-category-evaluator-interface foreign-function-declaration)
(define-text-category-evaluator-interface function-definition)
(define-text-category-evaluator-interface generic-formula)
(define-text-category-evaluator-interface generic-simulation-formula)
(define-text-category-evaluator-interface gfi-output-values)
(define-text-category-evaluator-interface instance-formula)
(define-text-category-evaluator-interface item-designations-for-model) ;simulate5
(define-text-category-evaluator-interface language-translation)
(define-text-category-evaluator-interface list-of-graph-expressions)
(define-text-category-evaluator-interface logical-instance-formula)
(define-text-category-evaluator-interface procedure-definition)
(define-text-category-evaluator-interface remote-procedure-declaration)
(define-text-category-evaluator-interface rule)
(define-text-category-evaluator-interface specific-simulation-formula)
(define-text-category-evaluator-interface text-conversion-style-name)
(define-text-category-evaluator-interface units-declaration)
(define-text-category-evaluator-interface user-menu-choice-expression)

(define-text-category-evaluator-interface free)


(define-textof-category-evaluator-interface user-menu-choice-expression-initialization)
(define-textof-category-evaluator-interface constant-variable-designation?)
(define-textof-category-evaluator-interface gfi-interface-object)
(define-textof-category-evaluator-interface gfi-file-pathname)

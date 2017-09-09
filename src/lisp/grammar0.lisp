;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module GRAMMAR0

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Michael Levin and Mark H. David




;;;; `Units-of-measure' and `constants'




;;; Add-units-of-measure adds a unit of measure both for the grammar
;;; and for the predicate numeric-type-p which uses a kb-specific-property.
;;; Thus, add-units-of-measure is kb-specific and must be executed in a kb
;;; environment.  The list consists of symbols or dotted pairs. A pair specifies
;;; a singular and plural unit, e.g. (pound .  pounds), otherwise the unit is
;;; called neutral.

;;; Defining units of measure has several effects. (1) It adds to the grammar
;;; for `constant' phrases such as "1 pound", "3.2 pounds", "2.4 psi".  If
;;; singular and plural forms are given, the grammar is restrictive so as to use
;;; them properly.  The singular is used with 1 (fixed or floating) and the
;;; plural is used elsewhere including 0 and -1.  (2) Mappings are set up between
;;; the singular and plural forms.  The internal representation of a constant is
;;; always (number . plural-or-neutral-unit).  (3) Print-constant uses the
;;; conversion from plural to singular, where it exists to print forms identical
;;; to what is parsed.

(defun add-units-of-measure (list-of-symbols)
  (loop for symbol-or-pair in list-of-symbols doing
    (cond
      ((symbolp symbol-or-pair)
       (def-numeric-subtype symbol-or-pair)
       (add-kb-specific-symbol-token symbol-or-pair 'neutral-unit-of-measure))
      (t (def-numeric-subtype (car symbol-or-pair)
			      (cdr symbol-or-pair))
	 (def-numeric-subtype (cdr symbol-or-pair))
	 (add-kb-specific-symbol-token (car symbol-or-pair) 'singular-unit-of-measure)
	 (add-kb-specific-symbol-token (cdr symbol-or-pair) 'plural-unit-of-measure)
	 (setf (*singular-of-numeric-data-type* (cdr symbol-or-pair))
	       (car symbol-or-pair))))))

(def-numeric-subtype 'seconds)
(def-numeric-subtype 'time-stamp)
(def-numeric-subtype 'pure-number)
(def-numeric-subtype 'interval)

(defun convert-singular-constant (pair)
  (setf (cdr pair) (number-subtype-p (cdr pair)))
  pair)









;;; Convert-interval-phase converts phrase, an `unnormalized interval phrase',
;;; which is of the form (n . units) into a `normalized interval phrase', which
;;; is of the form (m . SECONDS), where m is the number of seconds equivalent
;;; to the n units.  For example, it converts (3 . minutes) to (180 . seconds).
;;; It expects the car of the phrase to be a fixnum integer.  It also rejects
;;; phrase if it results in an interval longer than the number of seconds given
;;; by the variable ten-years.

(defun convert-interval-phrase (phrase)
  (let* ((number (car phrase))
	 (unit (cdr phrase))
	 (interval-in-seconds
	   (*f-safe number
		    (case unit
		      ((second seconds) 1)
		      ((minute minutes) 60)
		      ((hour hours) 3600)
		      ((day days) 86400)
		      ((week weeks) 604800)))))
    (if (or (null interval-in-seconds)
	    (>f interval-in-seconds ten-years))
	(values bad-phrase 'interval-too-long)
	(phrase-cons interval-in-seconds 'seconds))))

(declare-grammar-transform-can-return-bad-phrase convert-interval-phrase)

(defun convert-quantity-interval-phrase (phrase)
  (let* ((number (car phrase))
	 (unit (cdr phrase))
	 (conversion (case unit
		       ((second seconds) 1)
		       ((minute minutes) 60)
		       ((hour hours) 3600)
		       ((day days) 86400)
		       ((week weeks) 604800)))
	 (interval-in-seconds? nil))
    (cond ((phrase-float-p number)
	   (with-temporary-gensym-float-creation convert-quantity-interval-phrase
	     (setq interval-in-seconds?
		   (make-phrase-float
		     (*e (phrase-float-value number)
			 (coerce-fixnum-to-gensym-float conversion))))
	     (when (>e (phrase-float-value interval-in-seconds?)
		       (coerce-fixnum-to-gensym-float ten-years))
	       (setq interval-in-seconds? nil))))
	  (t
	   (setq interval-in-seconds? (*f-safe number conversion))
	   (when (and interval-in-seconds?
		      (>f interval-in-seconds? ten-years))
	     (setq interval-in-seconds? nil))))
    (if interval-in-seconds?
	(phrase-cons interval-in-seconds? 'seconds)
	(values bad-phrase 'interval-too-long))))

(declare-grammar-transform-can-return-bad-phrase convert-quantity-interval-phrase)




;;; Convert-compound-interval converts phrase, which it expects to be of the
;;; form
;;;
;;;    ((n . seconds) m . seconds)
;;;
;;; into a normalized interval phrase, a phrase of the form
;;;
;;;    (n+m . seconds)
;;;
;;; For example, it converts ((60 . seconds) 10 . seconds) to (70 . seconds).
;;; It expects n and m to be fixnum integers.  It also rejects phrase if it
;;; results in an interval longer than the number of seconds given by the
;;; variable ten-years

(defun convert-compound-interval (phrase)
  (let ((result
	  (phrase-cons (+f (caar phrase) (cadr phrase)) 'seconds)))
    (if (>f (car result) ten-years)
	(values bad-phrase 'interval-too-long)
	result)))

(declare-grammar-transform-can-return-bad-phrase convert-compound-interval)

(defun convert-compound-quantity-interval (phrase)
  (let* ((value-1 (caar phrase))
	 (value-2 (cadr phrase))
	 (result? nil))
    (with-temporary-gensym-float-creation convert-compound-quantity-interval
      (setq result?
	    (if (fixnump value-1)
		(if (fixnump value-2)
		    (+f value-1 value-2)
		    (make-phrase-float
		      (+e (coerce-fixnum-to-gensym-float value-1)
			  (phrase-float-value value-2))))
		(make-phrase-float
		  (+e (phrase-float-value value-1)
		      (if (fixnump value-2)
			  (coerce-fixnum-to-gensym-float value-2)
			  (phrase-float-value value-2))))))
      (unless (or (and (fixnump result?)
		       (<=f result? ten-years))
		  (and (phrase-float-p result?)
		       (<=e (phrase-float-value result?)
			    (coerce-fixnum-to-gensym-float ten-years))))
	(setq result? nil)))
    (if result?
	(phrase-cons result? 'seconds)
	(values bad-phrase 'interval-too-long))))

(declare-grammar-transform-can-return-bad-phrase convert-compound-quantity-interval)




;;; `Twrite-unix-time' takes a unix time, and writes it to the current output
;;; string, i.e., using twrite-char, et al.

(defun twrite-unix-time (unix-time &optional subsecond?)
  (with-temporary-gensym-float-creation twrite-unix-time
    (let ((gensym-float-unix-time (managed-float-value unix-time)))
      (if (or (<e gensym-float-unix-time -2.147483648e9) ; signed 32-bit long bounds
	      (>=e gensym-float-unix-time 2-to-31-plus-62-years))
	  (twrite-string "<time stamp out of bounds>")
	  (multiple-value-bind (second minute hour date month year)
	      (gensym-decode-unix-time gensym-float-unix-time)
	    (print-decoded-time
	      (if subsecond?
		  (-e gensym-float-unix-time (ffloore-first gensym-float-unix-time))
		  second)
	      minute hour date month year))))))

;; The previous function should be adapted to call this one, rather than
;; having as much code in common!  That process is being deferred for the
;; time being.  (MHD 4/3/95)





;;; Writes time and date a gensym-time rather than current time.

(defun write-date-and-time (gensym-time)
  (print-constant (-f gensym-time (clock-get gensym-time-at-start)) 'time-stamp))




;;; Restricting grammar by means of slot edit features is done by putting
;;; (restrict-if-slot-edit-feature slot-edit-feature reason) as a transforming
;;; function of the grammar rule. If the feature is present, the value
;;; is bad-phrase, otherwise, the parse is returned intact.

;;; Reason may be nil or a symbol. If it is not nil, then a more textual
;;; explanation must be provided as a case of the function
;;; reason-for-bad-parse-as-string (below).

;;; Restrict-if-not-slot-edit-feature does the opposite. It prevents the parse
;;; only if the slot edit feature is not present.

(defun restrict-if-slot-edit-feature (parse slot-edit-feature reason)
  (let* ((type-of-slot?
	   (if current-edit-state
	       (type-of-slot-being-edited current-edit-state)))
	 (feature-is-present?
	   (if type-of-slot?
	       (slot-edit-feature-p slot-edit-feature type-of-slot?))))
    (if feature-is-present? (values bad-phrase reason) parse)))

(declare-grammar-transform-can-return-bad-phrase restrict-if-slot-edit-feature)


(defun restrict-if-not-slot-edit-feature (parse slot-edit-feature reason)
  (let* ((type-of-slot?
	   (if current-edit-state
	       (type-of-slot-being-edited current-edit-state)))
	 (feature-is-present?
	   (if type-of-slot?
	       (slot-edit-feature-p slot-edit-feature type-of-slot?))))
    (if feature-is-present? parse (values bad-phrase reason))))

(declare-grammar-transform-can-return-bad-phrase restrict-if-not-slot-edit-feature)




;;;; Reasons for Bad Parses



(defun reason-for-bad-parse-as-string (reason)
  (case reason
    (this-rule
     "`This rule' is only permitted within rules.")
    (this-procedure
     "`This procedure' is only permitted within procedures.")
    (this-procedure-invocation
     "`This procedure-invocation' is only permitted within procedures.")
						       ; The procedure compiler
						       ; now determines when
						       ; has-a-value, etc.  can
						       ; be used within
						       ; procedures.  cpm, 5/15/91
;    (has-a-value
;     "`Has a value' and `has no value' are not permitted within procedures.")
;    (current-value-of
;     "`The current value' is not permitted within procedures.")
;    (first-that-has-a-value
;     "`The first of the following' is not permitted in procedures.")
    (has-a-current-value
     "`Has a current value' and `Has no current value' may not be applied to composite expressions.") 

    (e-designation
     "`Every' is not permitted within procedures.")

    (conditional-expression
     "Conditional expressions within procedures must terminate in an `else' clause.")


    ;; From filter-out-illegal-region-names:
    
    (region-cannot-be-a-color-or-metacolor
     "A region cannot be a color or metacolor.")
    (region-cannot-be-the-symbol-copy
     "A region cannot be the symbol COPY.")
    (region-cannot-be-the-symbol-inherited
     "A region cannot be the symbol INHERITED.")


    ;; From filter-out-illegal-color-names:
    
    (color-cannot-be-the-symbol-copy
     "A color cannot be the symbol INHERITED.")
    

    (interval-too-long				; Added today. (MHD 2/27/91)
     ;; Saying "three months" here would be too vague. (MHD)
     "you cannot enter an interval longer than 10 years")

    (too-few-arguments				; Added today. (MHD 2/27/91)
     "too few arguments")
    (too-many-arguments				; Added today. (MHD 2/27/91)
     "too many arguments")
    (wrong-number-of-arguments			; Added today. (MHD 2/27/91)
     "wrong number of arguments")


    ((otherwise)
     "`Otherwise' may be used only after at least one other case choice and only as the last choice.")
    
    ;; For fixing BUG-059-5435: This case is no longer needed because the workspace-
    ;; named grammar is being commented out in GRAMMAR1.
    ;; (ghw 1/26/99)
    ;(THE-WORKSPACE-NAMED-is-obsolete
    ;"The form THE WORKSPACE NAMED is obsolete.")

    (cannot-replace-in-runtime-or-embedded-g2
     "The replace feature is not available in runtime or embedded G2.")

    (non-object-must-be-passed-as-handle
      "This class is not a subclass of object and so must be passed `as handle'")
    (change-nth-element-no-array-or-list "The change element action must refer to a g2-array or g2-list.  Note that the array or list expression may need to be within parentheses.")


    (reserved-java-word "")
    
    (t (if (or (stringp reason)
	       (wide-string-p reason))
	   reason
	   "[Internal error in bad parse explanation.]"))))

;; Make the sentence structure, punctuation, and capitalization consistent internally
;; herein as well as consistent with other bad-phrase explanation messages!
;; (MHD 2/27/91)




;;; The category `evaluation-value-constant' is the subcategories of constant
;;; that can be evaluation values.  This is every subcategory except for
;;; quantity-interval and unit-of-measure-constant.

(def-grammar-category evaluation-value-constant ()
  (number)
  (whole-string)

  ;; New additions to grammar for CONSTANT for 5.0:   (MHD 4/8/97)
  (truth-value-attribute)
  (sequence)
  (structure))


;;; The category `constant' is used throughout G2.  It has these subcategories:
;;;
;;;   number
;;;   quantity-interval
;;;   unit-of-measure-constant
;;;   whole-string truth-value-attribute
;;;   sequence
;;;   structure

;;; The predicate function `phrase-for-constant-p' is true iff phrase might have
;;; been derived from the grammar for the category CONSTANT.

(def-grammar-category constant ()
  (unit-of-measure-constant
    1 reject-truth-value-as-unit-of-measure-constant)
  (quantity-interval)
  (evaluation-value-constant))

(defun-simple phrase-for-constant-p (phrase)
  (or (phrase-number-p phrase)
      (text-string-p phrase)
      (phrase-sequence-p phrase)
      (phrase-structure-p phrase)
      (truth-value-phrase-p phrase)
      (phrase-for-unit-of-measure-constant-p phrase)))

;;; The category `attribute-constant' is exclusively for use in the grammar for
;;; attribute definitions.  It is nearly equivalent to the category constant,
;;; except that it includes the category SYMBOL in addition to CONSTANT.

(def-grammar-category attribute-constant ()
  (constant)
  (symbol 1 reject-truth-value-as-symbol))

(defun reject-truth-value-as-symbol (symbol-phrase)
  (if (memq-p-macro symbol-phrase '(true false))
      bad-phrase
      symbol-phrase))

(declare-grammar-transform-can-return-bad-phrase reject-truth-value-as-symbol)



;;; The category `old-attribute-constant' is exclusively for use
;;; in the old grammar for attribute definitions.  It is for now
;;; defined as equivalent to the category constant.
;;;
;;; This should only be used by grammar reachable from
;;; old-attribute-descriptions.
;;;
;;; If we ever flush support for changing the text of the 3.0 user-visible
;;; attribute attributes-specific-to-class, which type symbol is
;;; old-attribute-descriptions, this can and should be flushed at that time.
;;;
;;; This is identical to the pre-5.0 definition for the grammar category
;;; constant.  But since that category is being extended and used elsewhere,
;;; this serves as a snapshot of that category.

(def-grammar-category old-attribute-constant ()
  (number)
  (quantity-interval)
  ((number singular-unit-of-measure)
   (1 . 2) 
   convert-singular-constant)
  ((number plural-unit-of-measure)
   (1 . 2))
  ((number neutral-unit-of-measure)
   (1 . 2))
  (whole-string))

;; This was adopted from the definition in the 5.0 repository as of today
;; (4/14/97).  There were no known compatibility bugs with that grammar, but I
;; have not reconfirmed that this grammar works exactly the same as the the 3.0
;; grammar. (MHD 4/14/97)



;;; The category `quantity-interval' ...

;;; `Quantity-interval-unit-p' is true if x is one of the units used in a
;;; quantity interval.

(defmacro quantity-interval-unit-p (x)
  `(memq-p-macro
     ,x
     '(second seconds minute minutes hour hours day days week weeks)))




;;; The category `unit-of-measure-constant' ...

;;; The predicate function `phrase-for-unit-of-measure-constant-p' is true if
;;; phrase is a unit-of-measure-constant.  This does reject truth-value phrases,
;;; but this does not tell if the unit of measure is actually of the category
;;; singular-, plural-, or neutral-unit-of-measure, but that should not be
;;; necessary, or this should not be used if it is.  (There is currently nothing
;;; with that functionality.  Note that these categories are added to
;;; dynamically at run time; a symbol may not appear to be of the category now,
;;; but may so appear later due to changes in the KB.)

;;; The function `reject-truth-value-as-unit-of-measure-constant' is needed to
;;; disambiguate language such as .3 TRUE, where TRUE (or FALSE) might be
;;; interpreted as a unit of measure, which could be any symbol. 

(def-grammar-category unit-of-measure-constant ()
  ((number singular-unit-of-measure) (1 . 2) convert-singular-constant)
  ((number plural-unit-of-measure) (1 . 2))
  ((number neutral-unit-of-measure) (1 . 2)))

(defun-simple phrase-for-unit-of-measure-constant-p (phrase)
  (and (consp phrase)
       (phrase-number-p (car-of-cons phrase))
       (symbolp (cdr-of-cons phrase))
       (not (eq (cdr-of-cons phrase) 'truth-value))
       (not (quantity-interval-unit-p (cdr-of-cons phrase)))))


(defun reject-truth-value-as-unit-of-measure-constant
    (unit-of-measure-expression-phrase)
  (if (truth-value-phrase-p unit-of-measure-expression-phrase)
      bad-phrase
      unit-of-measure-expression-phrase))

(declare-grammar-transform-can-return-bad-phrase reject-truth-value-as-unit-of-measure-constant)

;; Consider that this might also be solved by making true or false be rejected
;; as units of measure.



;;; `Mutate-unit-of-measure-phrase-phrase-into-slot-constant' is a substitution
;;; macro.  It is based on make-slot-constant-using-phrase-conses: given a
;;; unit-of-measure-phrase, p, it returns the same result as would
;;;
;;;    (make-slot-constant-using-phrase-conses (car p) (cdr p))
;;;
;;; where (car p) is the value, and (cdr p) is the unit.  It does so
;;; "reclaiming its argument", meaning that the list structure in the argument
;;; unit-of-measure phrase is mutated and returned in the result.

(def-substitution-macro mutate-unit-of-measure-phrase-phrase-into-slot-constant
    (unit-of-measure-phrase)
  ;; It comes in looking like this:
  ;;   (n . unit)
  ;; and it goes out looking like this:
  ;;   (n . (unit . nil)), i.e., (n unit)
  (setf (cdr unit-of-measure-phrase)
	(phrase-cons (cdr unit-of-measure-phrase) nil))
  unit-of-measure-phrase)
  



;;; The category `aggregate-constant' includes constant, and additionally
;;; allows "quoted symbol" expressions, i.e., language of the form
;;;
;;;   THE SYMBOL <symbol>
;;;
;;; However, note that <symbol> is here the category
;;; system-or-user-defined-attribute-name, which allows both simple
;;; symbols and class-qualified symbols (class::symbol).
;;;
;;; This category is used for the elements of sequences and for the
;;; values of the fields of structure.

(def-grammar-category aggregate-constant ()
  (evaluation-value-constant)
  (('the 'symbol standard-or-class-qualified-symbol) 3))

;; Note that constant does not include any way to express a symbol.  This adds
;; it using the G2 "quoting" idiom, "THE SYMBOL symbol".  Note that symbol here
;; must be of the category system-or-user-defined-attribute-name, in order to
;; allow "symbols" such as FOO::BAR.




;;; The category `truth-value-attribute' accepts true, true with a certainty
;;; factor (e.g., ".2 true"), or false.  It always parses as a truth-value
;;; phrase.
;;;
;;; The category `truth-value-attribute?' is the same, except that it accepts in
;;; addition the symbol NONE, which is parsed as itself, the symbol NONE.

(def-grammar-category truth-value-attribute ()
  ('true 1 check-and-scale-certainty-factor)
  ('false 1 check-and-scale-certainty-factor)
  ((number 'true) (1 . true) check-and-scale-certainty-factor))

(def-grammar-category truth-value-attribute? ()
  ('none)
  (truth-value-attribute))



;;; The category `truth-value-constant' has the same surface grammar as
;;; truth-value-attribute, but the phrase that results from it is a truth-value
;;; slot-constant phrase, rather than a truth-value phrase. It was created
;;; to solve a problem (see get-type-of-slot-if-any-for-variable) where the
;;; work that had been being done by a slot-compiler now has to be done
;;; by the transform associated with this rule. 

(def-grammar-category truth-value-constant ()
  (truth-value-attribute 1 transform-truth-value-phrase-into-slot-constant))




;;; The macro `make-truth-value-phrase' returns a `truth value phrase',
;;; a cons whose car is truth-value-phrase-value and whose cdr is the symbol
;;; TRUTH-VALUE.  The argument truth-value-phrase-value must be an integer
;;; in the range [-1000..1000].  Note that the constants falsity (-1000)
;;; and truth (1000) are convenient and clear ways to specify falsity and
;;; truth, respectively.
;;;
;;; Note that a truth value phrase differs from a truth value slot constant
;;; in that the phrase has TRUTH-VALUE as its cdr, while the constant has
;;; TRUTH-VALUE as its CADR.

(defmacro make-truth-value-phrase (truth-value-phrase-value)
  `(phrase-cons ,truth-value-phrase-value 'truth-value))


;;; `Mutate-truth-value-phrase-into-slot-constant' is a substitution macro.  It
;;; is based on make-slot-constant-using-phrase-conses: given a truth-value
;;; phrase, tvp, it returns the same result as would
;;;
;;;    (make-slot-constant-using-phrase-conses
;;;      (truth-value-phrase-value tvp)
;;;      'truth-value)
;;;
;;; but it does so "reclaiming its argument", meaning that the list structure
;;; in the argument truth-value phrase is mutated and returned in the result.

(def-substitution-macro mutate-truth-value-phrase-into-slot-constant
    (truth-value-phrase)
  ;; It comes in looking like this:
  ;;   (n . TRUTH-VALUE)
  ;; and it goes out looking like this:
  ;;   (n . (truth-value . nil)), i.e., (n TRUTH-VALUE)
  (setf (cdr truth-value-phrase)
	(phrase-cons (cdr truth-value-phrase) nil))
  truth-value-phrase)


;;; `Transform-truth-value-phrase-into-slot-constant' is similar but is intended
;;; for use as a transformation function.  See the category truth-value-constant
;;; to see how it's used.

(defun transform-truth-value-phrase-into-slot-constant
    (truth-value-phrase)
  (mutate-truth-value-phrase-into-slot-constant truth-value-phrase))
  
  



;;; `Make-message-rejecting-certainty-factor' is just called by the phrase
;;; transformation check-and-scale-certainty-factor in the case of an invalid
;;; certaintly factor.  The argument wrong-certainty-factor can be either a
;;; fixnum integer, a gensym float, or a managed float.  This should be called
;;; in a temporary gensym float creation context order to deal with any
;;; temporary number consing that happens when printing floating point numbers.

(defun make-message-rejecting-certainty-factor (wrong-certainty-factor)
  (tformat-text-string
    "~s is an invalid certainty factor; it must be a number between -1 and 1, inclusive"
    wrong-certainty-factor))

(defun check-and-scale-certainty-factor (true-false-or-certainty-factor-cons)
  (cond
    ((eq true-false-or-certainty-factor-cons 'true)
     (make-truth-value-phrase truth))
    ((eq true-false-or-certainty-factor-cons 'false)
     (make-truth-value-phrase falsity))
    (t
     #+development
     (test-assertion
       (and (consp true-false-or-certainty-factor-cons)
	    (phrase-number-p (car true-false-or-certainty-factor-cons))))
     (with-temporary-gensym-float-creation
	 check-and-scale-certainty-factor
       (let ((certainty-factor
	       (phrase-number-value
		 (car-of-cons true-false-or-certainty-factor-cons))))
	 (if (<= -1 certainty-factor 1)
	     (progn
	       ;; Change in place:  -- saves a cons -- i.e., vs. copying
	       (setf (car-of-cons true-false-or-certainty-factor-cons)
		     (round (* truth certainty-factor)))
	       (setf (cdr-of-cons true-false-or-certainty-factor-cons)
		     'truth-value)
	       true-false-or-certainty-factor-cons)
	     (values
	       bad-phrase
	       (make-message-rejecting-certainty-factor
		 certainty-factor))))))))

(declare-grammar-transform-can-return-bad-phrase check-and-scale-certainty-factor)



;;; `Valid-untransformed-truth-value-phrase-p' is true of a phrase for the
;;; grammar category truth-value-attribute which has not yet undergone its
;;; transformation, but will be acceptable as a truth value.

#+unused
(defun-simple valid-untransformed-truth-value-phrase-p (phrase)
  (or (eq phrase 'true)
      (eq phrase 'false)
      (and (consp phrase)
	   (eq (cdr phrase) 'truth-value)
	   (with-temporary-gensym-float-creation truth-value-phrase
	     (<= -1 (phrase-number-value (car phrase)) 1)))))


;;; `Truth-value-phrase-p' is true of a phrase for the grammar category
;;; truth-value-attribute which has undergone its transformation.  This phrase
;;; is specifically designed such that it will look like an evaluation truth
;;; value (only the conses are phrase conses, not evaluation conses) and will be
;;; copied as an evaluation truth value by copy-for-slot-value.  

(defun-simple truth-value-phrase-p (phrase)
  (and (consp phrase)
       (eq (cdr-of-cons phrase) 'truth-value)))

;; Note: this definition is essentially identical to that of
;; evaluation-truth-value-p. Note that this does not check the type or numeric
;; range of (car phrase), the certainty factor; it should be between -1000 and
;; 1000, inclusive.


(defun-simple truth-value-phrase-value (truth-value-phrase)
  (car-of-cons truth-value-phrase))
	       

#+unused
(defun-simple phrase-for-aggregate-constant-p (phrase)
  (or (phrase-for-constant-p phrase)
      (symbolp phrase)))


(def-grammar-category number ()
  (integer)
  (float)
  (long))

(add-grammar-rules

  '((interval week-phrase)
    (interval (week-phrase 'and day-phrase) (1 . 3) convert-compound-interval)
    (interval (week-phrase 'and hour-phrase) (1 . 3) convert-compound-interval)
    (interval (week-phrase 'and minute-phrase) (1 . 3) convert-compound-interval)
    (interval (week-phrase 'and second-phrase) (1 . 3) convert-compound-interval)
    (interval (week-phrase '\, continued-day-interval) (1 . 3) convert-compound-interval)
    (interval day-interval)

    (day-interval day-phrase)
    (day-interval (day-phrase 'and hour-phrase) (1 . 3) convert-compound-interval)
    (day-interval (day-phrase 'and minute-phrase) (1 . 3) convert-compound-interval)
    (day-interval (day-phrase 'and second-phrase) (1 . 3) convert-compound-interval)
    (day-interval (day-phrase '\, continued-hour-interval) (1 . 3) convert-compound-interval)
    (day-interval hour-interval)

    (continued-day-interval (day-phrase '\, continued-hour-interval)
			    (1 . 3) convert-compound-interval)
    (continued-day-interval (day-phrase '\, 'and hour-phrase)
			    (1 . 4) convert-compound-interval)
    (continued-day-interval (day-phrase '\, 'and minute-phrase)
			    (1 . 4) convert-compound-interval)
    (continued-day-interval (day-phrase '\, 'and second-phrase)
			    (1 . 4) convert-compound-interval)
    (continued-day-interval continued-hour-interval)

    (hour-interval hour-phrase)
    (hour-interval (hour-phrase 'and minute-phrase) (1 . 3) convert-compound-interval)
    (hour-interval (hour-phrase 'and second-phrase) (1 . 3) convert-compound-interval)
    (hour-interval (hour-phrase '\, continued-minute-interval)
		   (1 . 3) convert-compound-interval)
    (hour-interval minute-interval)
    
    (continued-hour-interval (hour-phrase '\, continued-minute-interval)
			    (1 . 3) convert-compound-interval)
    (continued-hour-interval (hour-phrase '\, 'and minute-phrase)
			     (1 . 4) convert-compound-interval)
    (continued-hour-interval (hour-phrase '\, 'and second-phrase)
			     (1 . 4) convert-compound-interval)
    (continued-hour-interval continued-minute-interval)

    (minute-interval minute-phrase)
    (minute-interval (minute-phrase 'and second-phrase) (1 . 3) convert-compound-interval)
    (minute-interval second-phrase)

    (continued-minute-interval (minute-phrase '\, 'and second-phrase)
				(1 . 4) convert-compound-interval)

    (week-phrase (non-negative-integer week-or-weeks)
		 (1 . 2) convert-interval-phrase)
    (week-or-weeks 'week)
    (week-or-weeks 'weeks)

    (day-phrase (non-negative-integer day-or-days)
		   (1 . 2) convert-interval-phrase)
    (day-or-days 'day)
    (day-or-days 'days)

    (hour-phrase (non-negative-integer hour-or-hours)
		   (1 . 2) convert-interval-phrase)
    (hour-or-hours 'hour)
    (hour-or-hours 'hours)

    (minute-phrase (non-negative-integer minute-or-minutes)
		   (1 . 2) convert-interval-phrase)
    (minute-or-minutes 'minute)
    (minute-or-minutes 'minutes)

    (second-phrase (non-negative-integer second-or-seconds)
		   (1 . 2) convert-interval-phrase)

    (second-or-seconds 'second)
    (second-or-seconds 'seconds)

    ;; quantity-interval returns either an integer or a float interval.
    (quantity-interval quantity-week-phrase)
    (quantity-interval (quantity-week-phrase 'and quantity-day-phrase)
     (1 . 3) convert-compound-quantity-interval)
    (quantity-interval (quantity-week-phrase 'and quantity-hour-phrase)
     (1 . 3) convert-compound-quantity-interval)
    (quantity-interval (quantity-week-phrase 'and quantity-minute-phrase)
     (1 . 3) convert-compound-quantity-interval)
    (quantity-interval (quantity-week-phrase 'and quantity-second-phrase)
     (1 . 3) convert-compound-quantity-interval)
    (quantity-interval (quantity-week-phrase '\, continued-quantity-day-interval)
     (1 . 3) convert-compound-quantity-interval)
    (quantity-interval quantity-day-interval)

    (quantity-day-interval quantity-day-phrase)
    (quantity-day-interval (quantity-day-phrase 'and quantity-hour-phrase)
     (1 . 3) convert-compound-quantity-interval)
    (quantity-day-interval (quantity-day-phrase 'and quantity-minute-phrase)
     (1 . 3) convert-compound-quantity-interval)
    (quantity-day-interval (quantity-day-phrase 'and quantity-second-phrase)
     (1 . 3) convert-compound-quantity-interval)
    (quantity-day-interval (quantity-day-phrase '\, continued-quantity-hour-interval)
     (1 . 3) convert-compound-quantity-interval)
    (quantity-day-interval quantity-hour-interval)

    (continued-quantity-day-interval
     (quantity-day-phrase '\, continued-quantity-hour-interval)
     (1 . 3) convert-compound-quantity-interval)
    (continued-quantity-day-interval
     (quantity-day-phrase '\, 'and quantity-hour-phrase)
     (1 . 4) convert-compound-quantity-interval)
    (continued-quantity-day-interval
     (quantity-day-phrase '\, 'and quantity-minute-phrase)
     (1 . 4) convert-compound-quantity-interval)
    (continued-quantity-day-interval
     (quantity-day-phrase '\, 'and quantity-second-phrase)
     (1 . 4) convert-compound-quantity-interval)
    (continued-quantity-day-interval continued-quantity-hour-interval)

    (quantity-hour-interval quantity-hour-phrase)
    (quantity-hour-interval (quantity-hour-phrase 'and quantity-minute-phrase)
     (1 . 3) convert-compound-quantity-interval)
    (quantity-hour-interval (quantity-hour-phrase 'and quantity-second-phrase)
     (1 . 3) convert-compound-quantity-interval)
    (quantity-hour-interval
     (quantity-hour-phrase '\, continued-quantity-minute-interval)
     (1 . 3) convert-compound-quantity-interval)
    (quantity-hour-interval quantity-minute-interval)
    
    (continued-quantity-hour-interval
     (quantity-hour-phrase '\, continued-quantity-minute-interval)
     (1 . 3) convert-compound-quantity-interval)
    (continued-quantity-hour-interval
     (quantity-hour-phrase '\, 'and quantity-minute-phrase)
     (1 . 4) convert-compound-quantity-interval)
    (continued-quantity-hour-interval
     (quantity-hour-phrase '\, 'and quantity-second-phrase)
     (1 . 4) convert-compound-quantity-interval)
    (continued-quantity-hour-interval continued-quantity-minute-interval)

    (quantity-minute-interval quantity-minute-phrase)
    (quantity-minute-interval
     (quantity-minute-phrase 'and quantity-second-phrase)
     (1 . 3) convert-compound-quantity-interval)
    (quantity-minute-interval quantity-second-phrase)

    (continued-quantity-minute-interval
     (quantity-minute-phrase '\, 'and quantity-second-phrase)
     (1 . 4) convert-compound-quantity-interval)

    (quantity-week-phrase (non-negative-number week-or-weeks)
     (1 . 2) convert-quantity-interval-phrase)

    (quantity-day-phrase (non-negative-number day-or-days)
     (1 . 2) convert-quantity-interval-phrase)

    (quantity-hour-phrase (non-negative-number hour-or-hours)
     (1 . 2) convert-quantity-interval-phrase)

    (quantity-minute-phrase (non-negative-number minute-or-minutes)
     (1 . 2) convert-quantity-interval-phrase)

    (quantity-second-phrase (non-negative-number second-or-seconds)
     (1 . 2) convert-quantity-interval-phrase)
    ))

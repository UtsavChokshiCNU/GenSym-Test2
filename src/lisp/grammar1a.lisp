;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module GRAMMAR1a

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Michael Levin, Mark H. David, Chris Morel


(declare-forward-reference decode-format function) ; GRAMMAR4
(declare-forward-reference decode-normalized-time-of-day function) ; GRAMMAR6B
(declare-forward-reference decode-normalized-time-of-day-with-subseconds function) ; GRAMMAR6B
(declare-forward-reference finish-edit-timestamp-transform function) ; GRAMMAR6B





;;; The grammar category `sequence-attribute' is used as the category symbol in
;;; the slot type feature for a (user-defined) attribute whose type is declared
;;; as sequence.  Note that the slot value writer is hanging off of this symbol.

(def-grammar-category sequence-attribute () (sequence-allowing-items))


;;; The grammar category `structure-attribute' is used as the category symbol in
;;; the slot type feature for a (user-defined) attribute whose type is declared
;;; as structure.  Note that the slot value writer is hanging off of this
;;; symbol.

(def-grammar-category structure-attribute () (structure-allowing-items))


(def-grammar-category sequence ()
  (('sequence '\( '\)) (1) make-empty-phrase-sequence-kludge) ; empty sequence case
  (('sequence '\( sequence-component-list '\)) 3 cdr make-phrase-sequence-from-sequence-component-list))

(defun-simple make-phrase-sequence-from-sequence-component-list
    (sequence-component-list)
  (make-phrase-sequence sequence-component-list))

(add-grammar-rules-for-list 'sequence-component-list 'sequence-component '\,)

(def-grammar-category sequence-component ()
  (aggregate-constant))


(def-grammar-category structure ()
  (('structure '\( '\)) (1) make-empty-phrase-structure-kludge) ; empty structure case
  (('structure '\( structure-component-list '\)) 3 cdr
   make-phrase-structure-from-structure-component-list))

(defun make-empty-phrase-sequence-kludge (nothing)
  (declare (ignore nothing))
  (make-phrase-sequence '()))

(defun make-empty-phrase-structure-kludge (nothing)
  (declare (ignore nothing))
  (make-phrase-structure '()))

;; There's no way to specify nil as the transformation template.  Specifying nil
;; itself implies that the parse result should be the arg to the tranformation
;; operation.  This is our workaround, hence the "kludge" in the name. (MHD
;; 4/15/97)



;;; `Make-phrase-structure-from-structure-component-list' nondestructively
;;; creates a phrase structure with field/value pairs corresponding to the
;;; key/value pairs from the a-list structure-component-list.
  
(defun-simple make-phrase-structure-from-structure-component-list
    (structure-component-list)
  (make-phrase-structure
    (loop for (i . v) in structure-component-list
	  collect i using phrase-cons
	  collect v using phrase-cons)))

(add-grammar-rules-for-list 'structure-component-list 'structure-component '\,)

(def-grammar-category structure-component ()
  ((unreserved-symbol '\: aggregate-constant) (1 . 3)))



(def-grammar-category evaluation-value-constant-allowing-items ()
  ('none)
  (number)
  (whole-string)
  (truth-value-attribute)
  (sequence-allowing-items)
  (structure-allowing-items)
  (item-denotation)
  (('the 'symbol standard-or-class-qualified-symbol) 3))

;c.e.i. uuid, v.a. image-data, v.a. media-bin-data
(def-grammar-category evaluation-value-constant-allowing-binary-data ()
  ('none)
  (number)
  (whole-string)
  (binary-data)
  (truth-value-attribute)
  (sequence-allowing-binary-data)
  (structure-allowing-binary-data)
  (('the 'symbol standard-or-class-qualified-symbol) 3))

(def-grammar-category binary-data ()
  (('the 'binary 'string whole-string) 4 convert-binary-string-for-parsing))

(defun convert-binary-string-for-parsing (string)
  (multiple-value-bind (uuid? problem-report?)
      (convert-binary-string-representation-to-internal string nil "binary")
    (cond (uuid?
	   (note-use-of-text-string-in-phrase uuid?)
	   uuid?)
	  (t
	   (values bad-phrase problem-report?)))))

(declare-grammar-transform-can-return-bad-phrase convert-binary-string-for-parsing)

(def-grammar-category constant-allowing-items ()
  (unit-of-measure-constant
    1 reject-truth-value-as-unit-of-measure-constant)
  (quantity-interval)
  (evaluation-value-constant-allowing-items))

(def-grammar-category constant-allowing-contained-items ()
  (unit-of-measure-constant
    1 reject-truth-value-as-unit-of-measure-constant)
  (quantity-interval)
  ('none)
  (number)
  (whole-string)
  (truth-value-attribute)
  (sequence-allowing-items)
  (structure-allowing-items)
  (('the 'symbol standard-or-class-qualified-symbol) 3))

(def-grammar-category item-denotation ()
  (item-name
    1 make-phrase-item-denotation-from-parse)
  (('the standard-or-class-qualified-symbol 'of item-denotation)
   (1 2 4) make-phrase-item-denotation-from-parse)
  (('the class 'having 'uuid whole-string)
   (the-item-having-uuid 2 5) make-phrase-item-denotation-from-parse))

(defun make-phrase-item-denotation-from-parse (parse)
  (make-phrase-item-denotation parse))

(def-grammar-category sequence-allowing-items ()
  (('sequence '\( '\)) (1) make-empty-phrase-sequence-kludge) ; empty sequence case
  (('sequence '\( sequence-component-allowing-items-list '\)) 3 cdr make-phrase-sequence-from-sequence-component-list))

(add-grammar-rules-for-list 'sequence-component-allowing-items-list 'sequence-component-allowing-items '\,)

(def-grammar-category sequence-component-allowing-items ()
  (evaluation-value-constant-allowing-items))

(def-grammar-category structure-allowing-items ()
  (('structure '\( '\)) (1) make-empty-phrase-structure-kludge) ; empty structure case
  (('structure '\( structure-component-allowing-items-list '\)) 3 cdr
   make-phrase-structure-from-structure-component-list))

(add-grammar-rules-for-list 'structure-component-allowing-items-list 'structure-component-allowing-items '\,)

(def-grammar-category structure-component-allowing-items ()
  ((unreserved-symbol '\: evaluation-value-constant-allowing-items) (1 . 3)))


(def-grammar-category sequence-allowing-binary-data ()
  (('sequence '\( '\)) (1) make-empty-phrase-sequence-kludge) ; empty sequence case
  (('sequence '\( sequence-component-allowing-binary-data-list '\)) 3 cdr make-phrase-sequence-from-sequence-component-list))

(add-grammar-rules-for-list 'sequence-component-allowing-binary-data-list 'sequence-component-allowing-binary-data '\,)

(def-grammar-category sequence-component-allowing-binary-data ()
  (evaluation-value-constant-allowing-binary-data))

(def-grammar-category structure-allowing-binary-data ()
  (('structure '\( '\)) (1) make-empty-phrase-structure-kludge) ; empty structure case
  (('structure '\( structure-component-allowing-binary-data-list '\)) 3 cdr
   make-phrase-structure-from-structure-component-list))

(add-grammar-rules-for-list 'structure-component-allowing-binary-data-list 'structure-component-allowing-binary-data '\,)

(def-grammar-category structure-component-allowing-binary-data ()
  ((unreserved-symbol '\: evaluation-value-constant-allowing-binary-data) (1 . 3)))




(add-parallel-grammar-rules (unique- simulation-)
			    (expression
			      sum sum-1 signed-sum term signed-term
			      term-or-signed-term term-1
			      exponential series-of-exponentials
			      operator-and-exponential
			      factor designation quantifier
			      argument-list conditional-expression
			      argument-list-tail
			      structure-argument-list-tail
			      class-phrase-role preposition
			      ago-interval last-interval
			      expression-or-logical-expression
			      logical-expression)

  (class-phrase-role (class preposition) (1 2) translate-role-and-preposition)

  (class-phrase-role (class local-name preposition) (1 2 3)
		     translate-role-local-name-and-preposition)

  (class-phrase-role ('workspace 'of) (role-server workspace kb-workspace))

  (class-phrase-role ('workspace local-name 'of) ((role-server workspace kb-workspace) . 2))

  #+mtg2
  (class-phrase-role ('faction 'of) (role-server faction faction))

  #+mtg2
  (class-phrase-role ('faction local-name 'of) ((role-server faction faction) . 2))

  (class-phrase-role ('subworkspace 'of) (role-server subworkspace kb-workspace))

  (class-phrase-role ('subworkspace local-name 'of) ((role-server subworkspace kb-workspace) . 2))

  (class-phrase-role (element-type 'in) (element-iterator 1))

  (class-phrase-role (element-type local-name 'in) ((element-iterator 1) . 2))


  ;; Note that (element-type 'in) can and should be made into a
  ;; class-phrase-role!! ML and JRA, 10/14/89. Apparently not true because
  ;; "any first pump in list-3" is wrong. ML, 3/14/90


  (class-phrase-role ('name 'of) (role-server name))
  (class-phrase-role ('name local-name 'of) ((role-server name) . 2))

  (class-phrase-role ('symbol 'that 'is a-or-an 'user-defined 'attribute 'name 'of)
		     (user-attribute-names 1))
  (class-phrase-role ('symbol local-name 'that 'is a-or-an 'user-defined
			      'attribute 'name 'of)
		     ((user-attribute-names 1) . 2))
  (class-phrase-role ('symbol 'that 'is a-or-an 'attribute 'name 'of)
		     (attribute-names 1))
  (class-phrase-role ('symbol local-name 'that 'is a-or-an 'attribute 'name 'of)
		     ((attribute-names 1) . 2))

  (class-phrase-role ('symbol 'that 'is 'an 'inferior-class 'of)
		     (inferior-class 1))
  (class-phrase-role ('symbol local-name 'that 'is 'an 'inferior-class 'of)
		     ((inferior-class 1) . 2))

  (class-phrase-role ('symbol 'that 'is 'a 'superior-class 'of)
		     (superior-class 1))
  (class-phrase-role ('symbol local-name 'that 'is 'a 'superior-class 'of)
		     ((superior-class 1) . 2))

  ;; preposition and constant-preposition are defined in parallel, except that
  ;; constant-preposition excludes named by and nearest to.  If you add a new preposition
  ;; that does not evoke an inference process, add it to constant-preposition also.
  ;; ML, 1/18/89

; (preposition 'of)
  (preposition ('connected 'to) connected-to)
  (preposition ('connected 'at 'the port-name 'of) (at-port 4))

  (preposition ('connected 'at 'the 'input 'to) at-an-input)
  (preposition ('connected 'at 'an 'input 'to) at-an-input)
  (preposition ('connected 'at 'the 'input 'of) at-an-input)
  (preposition ('connected 'at 'an 'input 'of) at-an-input)

  (preposition ('connected 'at 'the 'output 'of) at-an-output)
  (preposition ('connected 'at 'an 'output 'of) at-an-output)

  (preposition ('at 'the 'input 'end 'of) at-input-end)
  (preposition ('at 'an 'input 'end 'of) at-input-end)
  (preposition ('at 'the 'output 'end 'of) at-output-end)
  (preposition ('at 'an 'output 'end 'of) at-output-end)
  (preposition ('at 'either 'end 'of) at-either-end)
  (preposition ('at 'an 'end 'of) at-either-end)
  (preposition ('nearest 'to) nearest)

  (preposition ('superior 'to) superior-item)
  (preposition ('that 'is 'an 'attribute 'of) attribute-of-class)
  (preposition 'upon)

  (preposition ('that 'is relation-name) (related 3))

  ;; new: (see discussion under counterpart subgrammar for
  ;; constant-preposition!) (MHD 3/9/98)
  (preposition ('that 'contains) member-iterator)

  (local-name unreserved-symbol)

  (relation-name unreserved-symbol)
    
  (argument-list ( '\( expression-or-logical-expression '\) ) (2))
  (argument-list ( '\( expression-or-logical-expression '\, argument-list-tail)
		 (2 . 4))
  
  (argument-list-tail (expression-or-logical-expression '\) ) (1))
  (argument-list-tail (expression-or-logical-expression '\, argument-list-tail)
		      (1 . 3))

  (structure-argument-list ( '\( symbol '\: expression-or-logical-expression '\) )
			   ((quote 2) 4))
  (structure-argument-list ( '\( symbol '\: expression-or-logical-expression '\,
				 structure-argument-list-tail)
			   ((quote 2) 4 . 6))
  (structure-argument-list-tail (symbol '\: expression-or-logical-expression '\) )
				((quote 1) 3))
  (structure-argument-list-tail (symbol '\: expression-or-logical-expression
				      '\, structure-argument-list-tail)
			     ((quote 1) 3 . 5))

  (expression-or-logical-expression expression)
  (expression-or-logical-expression logical-expression)

  (list-role-keyword 'first first-of-list)
  (list-role-keyword 'last last-of-list)
  (list-role-keyword 'second second-of-list)
  (list-role-keyword ('next 'to 'last) next-to-last-of-list))





;;; The open categories `relation-name' and `local-name', which are defined as
;;; unreserved-symbol, have registered name directories, since they want to be
;;; prompted for always.  In the case of relation-name, you want to be prompted
;;; even if there are no definitions of any relations, just so you know what you
;;; can do.  In the case of local-name, in fact, there is currently no facility
;;; to record any local names (i.e., used as local variables in rules or
;;; procedures).

(def-registered-directory-of-names relation-name)
(def-registered-directory-of-names local-name)

;; Above def's added to fix bug HQ-951010 "Prompting: editor only prompts for
;; relation names if one exists" and related bug HQ-4753913 "wrong category menu
;; displayed sometimes". (MHD 11/8/04)






;;;; Element-type Grammar




;; The `element-type grammar category' defines the type of item and values that
;; can be contained in g2-arrays and g2-lists.

;; Note that the `g2-datum-type grammar category' only includes the basic datum
;; types (not time-stamp, pure-number, etc.)  For a full set of types, see the
;; data-type grammar category (used by variables and parameters) in grammar5.

;; The `g2-non-logical-datum-type grammar category' is used in some g2-list
;; actions (e.g., insert and remove).

;; NOTE:
;;   item-or-value has an internal name of item-or-datum.
;;   value has an internal name of datum.
;;   quantity has an internal name of number.

(add-grammar-rules
  '((element-type class-or-value-type)

    (class-or-value-type class 1 category-is-not-g2-element-datum-type)
    (class-or-value-type g2-meta-type)
    (class-or-value-type g2-datum-type)

    (g2-meta-type 'item-or-value item-or-datum)

    (g2-non-logical-datum-type 'value datum)
    (g2-non-logical-datum-type 'quantity number)
    (g2-non-logical-datum-type 'integer)
    (g2-non-logical-datum-type 'long)
    (g2-non-logical-datum-type 'float)
    (g2-non-logical-datum-type 'symbol)
    (g2-non-logical-datum-type 'text)
    (g2-non-logical-datum-type 'structure (structure))
    (g2-non-logical-datum-type 'sequence (sequence))
    ))

(def-grammar-category g2-datum-type ()
  ('value datum)
  ('quantity number)
  ('integer)
  ('long)
  ('float)
  ('symbol)
  ('truth-value)
  ('text)
  ('structure (structure))
  ('sequence (sequence)))


(def-grammar-category g2-datum-or-meta-type ()
  (g2-datum-type)
  (g2-meta-type))

(def-grammar-category attribute-definition-type ()
  (g2-datum-or-meta-type)
  ((g2-datum-or-meta-type '\, attribute-type-modification-list)
   (#.type-and-modifications-tag 1 3)
   fix-up-attribute-type-and-modifications-phrase))

(def-grammar-category attribute-definition-type-for-meta-type-only ()
  (g2-meta-type)
  ((g2-meta-type '\, attribute-type-modification-list)
   (#.type-and-modifications-tag 1 3)
   fix-up-attribute-type-and-modifications-phrase))

(defun fix-up-attribute-type-and-modifications-phrase (phrase)
  (when (and (listp phrase)
	     (third phrase))
    (setf (third phrase) (remove-noise-at-head-of-list-phrase (third phrase))))
  phrase)

(defun attribute-definition-type-specification (attribute-definition-type)
  (if (and (consp attribute-definition-type)
	   (eq (car attribute-definition-type) type-and-modifications-tag))
      (second attribute-definition-type)
      attribute-definition-type))

(defun attribute-definition-type-modifications (attribute-definition-type)
  (if (and (consp attribute-definition-type)
	   (eq (car attribute-definition-type) type-and-modifications-tag))
      (third attribute-definition-type)
      nil))

(add-grammar-rules-for-list 'attribute-type-modification-list 'attribute-type-modification '\, '\, nil)



;;; The attribute type modification `format-override' determines the slot type
;;; for the attribute, and so it affects the grammar, slot value writer, and
;;; slot value compiler for the attribute.

(def-concept format-override)

(def-grammar-category attribute-type-modification ()
  (('formatted 'as a-or-an 'time 'stamp) (format-override time-stamp))
  (('formatted 'as a-or-an 'interval) (format-override interval))
  (('formatted 'as ddd.dddd-format)
   (format-override 3)
   decode-ddd.dddd-format-in-format-override)
  (('formatted 'as 'free 'text) (format-override free-text)))

(def-grammar-category time-stamp ()
  ((date time-of-day-optionally-with-seconds)
   (1 2)
   transform-date-phrase-and-time-of-day-into-g2-time-stamp))

(def-grammar-category time-stamp-optionally-with-subseconds ()
  ((date time-of-day-optionally-with-seconds-or-subseconds)
   (1 2)
   ;; The following transform may return either float or fixnum, based on
   ;; contagion, i.e., float seconds => float time stamp.
   transform-date-phrase-and-time-of-day-into-g2-time-stamp))

(def-grammar-category time-stamp-optionally-with-subseconds-as-float ()
  ((date time-of-day-optionally-with-seconds-or-subseconds)
   (1 2)
   transform-date-phrase-and-time-of-day-into-g2-time-stamp
   ;; The following additional transform ensures the result is a float.
   coerce-phrase-number-to-float))


(def-grammar-category float-interval ()
  (quantity-interval
   1
   ;; The following additional transform ensures the result is a float interval.
   coerce-quantity-interval-to-float-interval))

(defun coerce-quantity-interval-to-float-interval (quantity-interval)
  (phrase-cons
    (coerce-phrase-number-to-float (car quantity-interval))
    (cdr quantity-interval)))


(defun coerce-phrase-number-to-float (phrase-number)
  (if (phrase-float-p phrase-number)
      phrase-number
      (make-phrase-float
	(coerce-to-gensym-float
	  (phrase-number-value phrase-number)))))

;; The above function is so general it should be moved to PARSE!!


;;; The function `transform-date-phrase-and-time-of-day-into-g2-time-stamp'
;;; ... returns a fixnum representing the time stamp.

(defun transform-date-phrase-and-time-of-day-into-g2-time-stamp
    (date-and-time-of-day-as-seconds-since-midnight)  
  (with-temporary-gensym-float-creation convert-local-date-to-edit-timestamp
    (with-temporary-bignum-creation
      (let* ((universal-date
	       (first date-and-time-of-day-as-seconds-since-midnight))
	     (time-of-day-as-seconds-since-midnight
	       (second date-and-time-of-day-as-seconds-since-midnight))
	     (g2-time-at-start-float-value
	       (managed-float-value (clock-get g2-time-at-start))))
	(multiple-value-bind (day month year)
	    (decode-universal-date universal-date)
	  (multiple-value-bind (seconds minutes hours)
	      (if (fixnump time-of-day-as-seconds-since-midnight)
		  (decode-normalized-time-of-day
		    time-of-day-as-seconds-since-midnight)
		  (decode-normalized-time-of-day-with-subseconds
		    time-of-day-as-seconds-since-midnight))
	    (if (fixnump seconds)
		(floore-first
		  (-e (gensym-encode-unix-time
			seconds minutes hours day month year)
		      g2-time-at-start-float-value))
		(- (+ (rem seconds 1)
		      (gensym-encode-unix-time
			(floor seconds) minutes hours day month year))
		   g2-time-at-start-float-value))))))))





(defun decode-ddd.dddd-format-in-format-override (phrase)
  (let (left right)
    (if (and (listp phrase)
	     (cdr phrase)
	     (second phrase)
	     (symbolp (second phrase))
	     (multiple-value-setq (left right)
	       (decode-format (second phrase))))
	;; (format-override dd.ddd)  ; i.e., a particular ddd.dddd-format instance
	;;   => (format-override ddd.dddd-format dd.ddd)
	(phrase-list 'format-override 'ddd.dddd-format (phrase-cons left right))
	(values bad-phrase (tformat-text-string "bad attribute format")))))

(def-grammar-category built-in-attribute-parsing-category ()
  (('free 'text) free-text))

(defun write-attribute-type-modifications (modifications)
  (loop for (mod . more?) on modifications
	do (write-one-attribute-type-modification mod)
	when more?
	  do (tformat ", ")))

(defun write-one-attribute-type-modification (modification)
  (case (first modification)
    (format-override
     ;; form is:  
     ;;   (format-override format? [ddd.dddd-format-instance])
     (tformat "formatted as~a "
	      (case (second modification)
		(interval " an")
		(time-stamp " a")
		(t "")))
     ;; invoke the slot value writer for FORMAT?:
     (write-slot-value
       'format?
       (if (eq (second modification) 'ddd.dddd-format)
	   (third modification)
	   (if (eq (second modification) 'interval)
	       'seconds
	       (second modification)))
       nil))
    #+development
    (t
     (cerror "continue anyway" "Unrecognized type modification: ~a" modification))))
  





(def-slot-value-compiler element-type (parse-result)
  (if (or system-is-running system-has-paused)
      (no-change-while-running)
      parse-result))

(def-slot-value-writer element-type (value)
  (cond ((null value) (twrite "none"))
	((eq value 'item-or-datum) (twrite-string "item-or-value"))
	((eq value 'datum) (twrite-string "value"))
	((eq value 'number) (twrite-string "quantity"))
        (t (tformat "~(~A~)" value))))



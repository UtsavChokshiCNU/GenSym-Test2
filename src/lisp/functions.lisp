;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module FUNCTIONS

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Jim Allard


;; In STACK-COMP

(declare-forward-reference compile-function-definition-for-stack function)

;; In Install

(declare-forward-reference analyze-compiled-items-for-consistency function)






;;;; Function Definitions



;;; `Function definitions' are statements which allow a user to specify a
;;; function to be used in knowledge base expressions.  Function specifications
;;; are given by the user as prefix functions with parenthasized formal parameter
;;; lists, e.g "square(x) = x * x".
;;;
;;; The symbol `function-definition' refers to three different portions of the
;;; function definition facility.  It is the name of the class whose frames
;;; hold function definitions, it is a grammar category which is used to parse
;;; function definitions, and it is the name of the KB specific property which
;;; relates names of functions to their defining frames.


(def-class (function-definition statement (foundation-class function-definition)
				define-predicate)
  (frame-author-or-authors nil (type authors-with-time-of-last-edit?))
  (frame-change-log nil (type frame-change-log))
  (name-or-names-for-frame nil (type nil))
  
  ;; initialize method now deals with initial setup -- this slot's init form
  ;; will now be nil, and inherited. (MHD 7/18/94)
;  (frame-status-and-notes
;    (:funcall slot-value-cons-function incomplete nil))
  
  (box-translation-and-text nil (type function-definition text) select-changes)
  (function-definition-byte-code-body nil vector-slot system save)
  (function-definition-parse-result nil system save)
  (function-parse-results? nil system save)
  (function-md5-identifier? nil system save))


;(def-slot-alias name-or-names-for-frame name function-definition)

;; This alias definition exposed a bug, in that it caused all other frames to
;; show name-or-names-for-frame in the table where it should say names.  If and
;; when the alias system is fixed so that an alias may be overridden in a
;; subclass, as opposed to requiring aliases to be within unique sub-branches of
;; the class hierarchy, then this alias should be commented back in.  -jra 1/26/88




(add-grammar-rules
  '((function-definition
      (new-function-name formal-parameter-list '= unique-expression)
      (1 2 4))
    (function-definition
      (new-function-name formal-parameter-list '= unique-logical-expression)
      (1 2 4))

    (formal-parameter-list ( '\( '\) ))
    (formal-parameter-list ( '\( formal-parameter-name '\) ) (2))
    (formal-parameter-list ( '\( formal-parameter-name '\, formal-parameter-list-tail) (2 . 4))

    (formal-parameter-list-tail (formal-parameter-name '\) ) (1))
    (formal-parameter-list-tail (formal-parameter-name '\, formal-parameter-list-tail) (1 . 3))

    (formal-parameter-name unreserved-symbol)

    (new-function-name unreserved-symbol)
    
    ))

; (def-kb-specific-property-name function-definition)  ; moved to COMPILE1 by ML




;;; The slot value compiler for function-definitions will call
;;; compile-expression on the parsed expression that has been passed in and will
;;; check that this is not a duplicate definition of this function name.

(declare-forward-reference no-inlining? variable)

(def-slot-value-compiler function-definition (translation function-definition)
  (let* ((name (first translation))
	 (old-definition? (car (box-translation-and-text function-definition)))
	 (old-name? (if (and old-definition? (neq old-definition? no-value))
			(first old-definition?)))
	 (var-list
	   (unless (eq (car (second translation)) '\( )
	     (second translation)))
	 (raw-body (third translation))
	 (*current-computation-frame* function-definition)
	 (compilation-status nil)
	 (compiled-body?
	   (compile-expression
	     raw-body nil (copy-list-using-gensym-conses var-list)))
	 (byte-code-body? nil))

    (cond (compiled-body?

	   ;; Update the argument range before function is compiled.  These
	   ;; values are need for consistency analysis (i.e., the correct name
	   ;; of arguments passed to a function).

	   ;; Note that this update is also done below in the put-box-
	   ;; translation-and-text-slot-value method.  - cpm, 1/7/93

	   (when (and old-name? (neq old-name? name))
	     (setf (argument-range old-name?) nil))
	   (setf (argument-range name) (length var-list))

	   (without-consistency-analysis (function-definition)
	     ;; Change the name within the scope of the without-consistency-
	     ;; analysis, so that the function's consistency-analysis is first
	     ;; retracted, and before compiling the function.  In this way, the
	     ;; notes of recursive functions will be accurate.
	     (change-slot-value
	       function-definition 'name-or-names-for-frame name)

	     (setq byte-code-body?
		   (compile-function-definition-for-stack
		     name
		     function-definition compiled-body? var-list))

	     (change-slot-value
	       function-definition 'function-definition-byte-code-body
	       byte-code-body?))
	   (cond (byte-code-body? ;compilation OK
		  ;; don't save yet
		  (unless no-inlining?
		    (change-slot-value
		      function-definition 'function-definition-parse-result
		      (copy-for-slot-value translation))))
		 (t (setq compilation-status 'bad)))
	   (update-frame-status function-definition compilation-status nil)
	   (analyze-compiled-items-for-consistency name)
	   (phrase-list name var-list compiled-body?))
	  (t
	   (change-slot-value
	     function-definition 'function-definition-byte-code-body nil)
	   (update-frame-status function-definition 'bad nil)
	   (phrase-list name var-list)))))




;;; The `put-box-translation-and-text-slot-value' method for
;;; function-definitions installs a pointer to the frame that represents the
;;; function definition onto the function-definition KB specific property for
;;; the name of the function.  If there was an old function definition in this
;;; frame and its name is different than the name for the new function,
;;; deinstall that definition from the old name.

(def-class-method put-box-translation-and-text-slot-value
		  (function-definition box-translation-and-text initializing?)
  ;; Remove old compilation if necessary.
  (when (and initializing?
	     (not (compilations-up-to-date-p function-definition))
	     loading-kb-p)
    (reclaim-slot-value (car box-translation-and-text))
    (setf (car box-translation-and-text) no-value)
    (note-frame-with-compilation-removed function-definition)
    (update-frame-status function-definition 'incomplete initializing?))

  (let* ((old-definition? (if (not initializing?)
			      (car (box-translation-and-text function-definition))))
	 (old-name? (if (and old-definition? (neq old-definition? no-value))
			(first old-definition?)))
	 (raw-definition (car box-translation-and-text))
	 (parsed-definition? (if (neq raw-definition no-value)
				 raw-definition
				 nil))
	 (name (first parsed-definition?))
	 (arglist (second parsed-definition?)))

    (when (and initializing?
	       loading-kb-p)
      (when (compiler-errors? function-definition)
	(update-frame-status function-definition 'bad initializing?)))
    
    ;; When initializing, the frame will already have its name.  Otherwise,
    ;; change the frame name to conform to the new definition.
    (unless initializing?
      (change-slot-value function-definition 'name-or-names-for-frame name))

    (when (and old-name? (neq old-name? name))
      (setf (argument-range old-name?) nil))

    (if parsed-definition?
	(setf (argument-range name) (length arglist))
	(change-slot-value function-definition 'function-definition-byte-code-body nil))
    (setf (box-translation-and-text function-definition)
	  box-translation-and-text)
    (values box-translation-and-text nil)))




;;; The slot putter for function-definition-byte-code-body changes the
;;; byte-code-body within a window for consistency analysis changes.  Note that
;;; the old byte-code-body is not reclaimed until after the setf of the value,
;;; so that any journalling is able to complete.

(def-slot-putter function-definition-byte-code-body
		 (function-definition new-byte-code-body initializing?)
  (when (and initializing?
	     (not (compilations-up-to-date-p function-definition))
	     loading-kb-p)
    (reclaim-slot-value new-byte-code-body)
    (setq new-byte-code-body nil)
    (note-frame-with-compilation-removed function-definition))
  (without-consistency-analysis (function-definition)
    (setf (function-definition-byte-code-body function-definition)
	  new-byte-code-body))
  new-byte-code-body)




;;; The cleanup method for a function-definition sets the box translation and
;;; text for the frame to nil in order to deinstall the analyze-for-consistency
;;; properties.

(def-class-method cleanup (function-definition)
  (funcall-superior-method function-definition)
  (change-slot-value function-definition 'box-translation-and-text nil)
  (change-slot-value function-definition 'function-definition-byte-code-body nil))








;;;; Units declarations

(def-class (units-of-measure-declaration
	     statement (foundation-class units-of-measure-declaration) define-predicate)
  (frame-author-or-authors nil (type authors-with-time-of-last-edit?))
  (frame-change-log nil (type frame-change-log))
  (box-translation-and-text nil (type units-declaration text) select-changes))


(def-substitute-for-old-class engineering-units-declaration
			      units-of-measure-declaration)


(add-grammar-rules
  '((units-declaration ( 'units 'of 'measure 'are '\: units-declaration-list)
		      (6))

    (units-declaration-list unit-declaration)
    (units-declaration-list (unit-declaration '\, units-declaration-list)
			   (2 1 3) simplify-associative-operation)

    (unit-declaration unreserved-symbol)
    (unit-declaration (unreserved-symbol '\( 'singular unreserved-symbol '\) )
		      (4 . 1))
    ))



(def-slot-value-compiler units-declaration (translation)
  (if (and (consp (car translation)) (eq (caar translation) '\,))
      (cdar translation)
      translation))




(declare-forward-reference add-units-of-measure function)

(def-class-method put-box-translation-and-text-slot-value
	    (units-of-measure-declaration box-translation-and-text initial?)
  (declare (ignore initial?))
  (let ((translation?
	  (if (not (eq (car box-translation-and-text) no-value))
	      (car box-translation-and-text))))
    (when translation?
      (add-units-of-measure translation?)
      (update-frame-status units-of-measure-declaration nil nil))
    (setf (box-translation-and-text units-of-measure-declaration)
	  box-translation-and-text)))










;;;; Tabular Functions



(def-class (tabular-function (item entity) (foundation-class tabular-function)
			     define-predicate not-solely-instantiable
			     not-user-instantiable do-not-put-in-menus)
  
  (frame-author-or-authors nil (type authors-with-time-of-last-edit?))
  (frame-change-log nil (type frame-change-log))

  (icon-description
    (:funcall-at-load-time
      create-icon-description
      60 60					; change size if possible
      ((outline (0 0) (60 0) (60 60) (0 60))
;       (outline (10 10) (50 10) (50 22) (36 22) (36 50) (24 50) (24 22) (10 22)) ; a "T"
       (lines (0 15) (60 15))
       (lines (0 30) (60 30))
       (lines (0 45) (60 45))
       (lines (30 0) (30 60))))))



(def-class (tabular-function-of-1-arg tabular-function
				      (foundation-class tabular-function-of-1-arg)
				      define-predicate)

  (add-or-delete-rows
    nil (type add-or-delete-rows) system lookup-slot
    do-not-put-in-attribute-tables edit-only do-not-save)

  (type-of-tabular-function-arg			; NUMBER, SYMBOL, or STRING
    number system vector-slot)			; (type tabular-function-data-type)!
  (type-of-tabular-function-value		; NUMBER, SYMBOL, or STRING
    number system vector-slot)			; (type tabular-function-data-type)!

  (keep-tabular-function-sorted?		; nil, ARGS, or VALUES
    args (type keep-tabular-function-sorted?) system user-overridable vector-slot)
  (tabular-function-interpolation?		; default nil?  "linear" instead of "yes"?
    t (type yes-or-no) system user-overridable vector-slot) ; ignored unless sorted by args
           ;; had been yes-or-no? See note with alias
  (column-of-args nil system vector-slot save)	  ; a series of values -- 
  (column-of-values nil system vector-slot save)  ; a series of values

  (number-of-rows-in-table			; length of both column slots
    0 system vector-slot save))

;; Have clicking on a representation of an add-or-delete-rows slot choose the edit option
;; directly, without a menu choice!

;; At present, type-of-tabular-function-arg and type-of-tabular-function-value are not
;; used.  Consider eliminating them.

;; Consider "managing" args and values that are numbers.

;; Consider changing the restriction on the add-or-delete-rows from do-not-put-in-
;; attribute-tables to do-not-describe-in-attribute-tables.

;; Note that the slot feature do-not-describe-in-attribute-tables has been changed
;; to do-not-identify-in-attribute-tables.  (ghw 10/25/95)

;; Consider remembering the last add-or-delete-rows request text in add-or-delete-rows,
;; so that it can be available for editing in forming the next request.



(define-slot-alias type-of-arg type-of-tabular-function-arg tabular-function)

(define-slot-alias type-of-value type-of-tabular-function-value tabular-function)

(define-slot-alias keep-sorted keep-tabular-function-sorted? tabular-function)    ; "?" removed (MHD 11/7/88)

(define-slot-alias interpolate tabular-function-interpolation? tabular-function)  ; (type yes-or-no?) (MHD 11/7/88)

;; Consider defining aliases for name-or-names-for-frame.



(def-slot-putter column-of-args (tabular-function-of-1-arg slot-value-list-of-values)
  (let ((series-of-values (convert-list-to-series-of-values slot-value-list-of-values)))
    (reclaim-series-of-values-and-values (column-of-args tabular-function-of-1-arg))
    (setf (column-of-args tabular-function-of-1-arg) series-of-values)
    (reclaim-slot-value-list slot-value-list-of-values)
    (values series-of-values t)))

(def-slot-putter column-of-values (tabular-function-of-1-arg slot-value-list-of-values)
  (let ((series-of-values (convert-list-to-series-of-values slot-value-list-of-values)))
    (reclaim-series-of-values-and-values (column-of-values tabular-function-of-1-arg))
    (setf (column-of-values tabular-function-of-1-arg) series-of-values)
    (reclaim-slot-value-list slot-value-list-of-values)
    (values series-of-values t)))

;; See the kludges in module FILES for cloning and saving series-of-values slot values.

(def-slot-value-reclaimer column-of-args (column-of-args)
  (reclaim-series-of-values-and-values column-of-args))


(def-slot-value-reclaimer column-of-values (column-of-values)
  (reclaim-series-of-values-and-values column-of-values))


(def-class-method initialize-after-reading (tabular-function-of-1-arg)
  (funcall-superior-method tabular-function-of-1-arg)
  (unless (tabular-functions-of-1-arg-sorted-by-Unicodes-p)
    (sort-tabular-function-if-necessary tabular-function-of-1-arg)))



;;; Grammar for Tabular Functions

;;; Note that nil is not a valid tabular function datum.

(add-grammar-rules

  '((add-or-delete-rows (add-or-delete positive-integer row-or-rows) (1 2))
    (add-or-delete-rows (add-or-delete positive-integer row-or-rows row-position) (1 2 4))
    (add-or-delete-rows (add-or-delete positive-integer row-or-rows row-data) (1 2 nil 4))
    (add-or-delete-rows (add-or-delete positive-integer row-or-rows row-position row-data)
			(1 2 4 5))
    (add-or-delete-rows (add-or-delete 'unfinished row-or-rows) (1 2))
    (add-or-delete-rows (add-or-delete 'unfinished row-or-rows row-position) (1 2 4))
    (add-or-delete-rows (add-or-delete 'unfinished row-or-rows row-data) (1 2 nil 4))
    (add-or-delete-rows (add-or-delete 'unfinished row-or-rows row-position row-data)
			(1 2 4 5))
    (add-or-delete-rows (add-or-delete row-or-rows) (1))
    (add-or-delete-rows (add-or-delete row-or-rows row-position) (1 nil 3))
    (add-or-delete-rows (add-or-delete row-or-rows row-data) (1 nil nil 3))
    (add-or-delete-rows (add-or-delete row-or-rows row-position row-data) (1 nil 3 4))

    (add-or-delete 'add)
    (add-or-delete 'delete)

    (row-position ('at 'the 'beginning) beginning)
    (row-position ('at 'the 'end) end)
    (row-position ('before 'x '= tabular-function-datum) (before 4))
    (row-position ('after 'x '= tabular-function-datum) (after 4))

    (row-data ('with 'x '= tabular-function-data) (with 4))	; "with" is redundant
    (row-data
      ('with 'x '= tabular-function-data 'and 'f '\( 'x '\) '= tabular-function-data)
      (with 4 11))

    (row-or-rows 'row)
    (row-or-rows 'rows)

    (tabular-function-data-type 'number)
    (tabular-function-data-type 'symbol)
    (tabular-function-data-type 'string)

    (tabular-function-data tabular-function-datum)
    (tabular-function-data
      (tabular-function-datum '\, tabular-function-data)
      (\, 1 3) simplify-associative-operation)
    (tabular-function-data (tabular-function-datum '\, 'etc.) (\, 1 3))

    (tabular-function-datum number)
    (tabular-function-datum symbol)
    (tabular-function-datum whole-string)

    (keep-tabular-function-sorted? 'no)
    (keep-tabular-function-sorted? ('by 'args) 2)
    (keep-tabular-function-sorted? ('by 'values) 2)))

;; Instead of, or in addition to, this add-or-delete-rows functionality, have a more
;; interactive, menu-driven way to edit tables of values!

;; Consider tightening up the add-or-delete-rows grammar, eliminating confusing cases.
;; For example, consider not treating "row" and "rows" as equivalent, restricting their
;; use and recording which was used, and consider restricting row-data in an "add
;; unfinished" case.

;; Consider renaming tabular-function-data "series-of-values".

;; Replace tabular-function-datum by an equivalent category, if there is one.



;;; Tabular-function-datum-equal ... The args datum1 and datum2 must be
;;; either symbols, fixnums, slot value floats, or strings.

(defun tabular-function-datum-equal (datum1 datum2)
  (or (eq datum1 datum2)			; opt.
      (cond
	;; the first clause is an optimization for fixnums, which
	;; would be handled as well by the subsequent clauses.
	((and (fixnump datum1) (fixnump datum2))
	 (=f datum1 datum2))
        ((and (evaluation-long-p datum1)
	      (evaluation-long-p datum2))
         (=l (evaluation-long-value datum1)
	     (evaluation-long-value datum2)))
	((slot-value-number-p datum1)
	 (and (slot-value-number-p datum2)
	      (with-temporary-gensym-float-creation
		tabular-function-datum-equal
		(= (slot-value-number-value datum1)
		   (slot-value-number-value datum2)))))
	((slot-value-number-p datum2)
	 nil)
	(t
	 (string-equalw (stringw datum1) (stringw datum2)))))) ; not string=; see note

;; This could be optimized a bit more.  It got a bit slower with the slot
;; value floats abstraction.  And much fatter.  Is more optimization
;; worthwhile?  Also, consider making this a function?   Same comments
;; apply for lessp variation below, etc.  (MHD 9/12/91)

;; Note that this function has some similarities with slot-value-equal-p,
;; q.v. (MHD 1/29/92)

;; I changed this to be string-equal, not string=, for release 3.0.
;; Strings never really worked until this release, so there's no compatibility
;; issue, and in general G2 is NOT case-sensitive.  (MHD 1/29/92)





;;; Tabular-function-phrase-datum-equal is just like tabular-function-datum-equal
;;; except that the first argument is to be interpreted as a phrase.  Phrase can
;;; thus be either a symbol, fixnum, phrase float, or string.  Datum can be either
;;; a symbol, fixnum, slot value float, or string.

(defun tabular-function-phrase-datum-equal (phrase datum)
  (or (eq phrase datum)			; opt.
      (cond
	;; the first clause is an optimization for fixnums, which
	;; would be handled as well by the subsequent clauses.
	((and (fixnump phrase) (fixnump datum))
	 (=f phrase datum))
        ((and (evaluation-long-p phrase)
	      (evaluation-long-p datum))
	 (=l (evaluation-long-value phrase)
	     (evaluation-long-value datum)))
	((phrase-number-p phrase)
	 (and (slot-value-number-p datum)
	      (with-temporary-gensym-float-creation
		tabular-function-datum-equal
		(= (phrase-number-value phrase)
		   (slot-value-number-value datum)))))
	((slot-value-number-p datum)
	 nil)
	(t
	 (string-equalw (stringw phrase) (stringw datum)))))) ; not string=; see note

;;; Tabular-function-datum-lessp ...

(def-substitution-macro tabular-function-datum-lessp (datum1 datum2)
  (cond
    ;; the first clause is an optimization for fixnums, which
    ;; would be handled as well by the subsequent clauses.
    ((and (fixnump datum1) (fixnump datum2))
     (<f datum1 datum2))
    ((and (evaluation-long-p datum1)
	  (evaluation-long-p datum2))
     (<l (evaluation-long-value datum1)
	 (evaluation-long-value datum2)))
    ((and (evaluation-long-p datum1)
	  (fixnump datum2))
     (with-temporary-creation tabular-function-datum-lessp-1
       (<l (evaluation-long-value datum1) datum2)))
    ((and (fixnump datum1)
	  (evaluation-long-p datum2))
     (with-temporary-creation tabular-function-datum-lessp-2
       (<l datum1 (evaluation-long-value datum2))))
    ((slot-value-number-p datum1)
     (or (not (slot-value-number-p datum2))
	 (with-temporary-gensym-float-creation
	   tabular-function-datum-lessp
	   (< (slot-value-number-value datum1)
	      (slot-value-number-value datum2)))))
    ((slot-value-number-p datum2)
     nil)
    (t
     (string-lesspw (stringw datum1) (stringw datum2)))))

(def-slot-value-compiler tabular-function-data-type
			 (parse-result tabular-function-of-1-arg)
  (if (=f (number-of-rows-in-table tabular-function-of-1-arg) 0)  ; or if same?
      parse-result
      (values
	bad-phrase
	(copy-text-string
	  "Types of args and values cannot be changed once the table has rows."))))



(def-slot-value-compiler keep-tabular-function-sorted?
			 (parse-result tabular-function-or-class-definition)
  (declare (use-for-default-overrides))
  (cond
    ((eq parse-result 'no) nil)
    ((frame-of-class-p tabular-function-or-class-definition 'class-definition)
     (let ((class-name? (name-of-defined-class tabular-function-or-class-definition)))
       (if (and (classp class-name?)
		(loop for instance being each class-instance of class-name?
		      thereis
		      (not (or (eq (keep-tabular-function-sorted? instance)
				   parse-result)
			       (=f (number-of-rows-in-table instance) 0)))))
	   (values
	     bad-phrase
	     (tformat-text-string
	       "The sort specification cannot be changed because ~
                there is an instance of this class with table rows."))
	   parse-result)))
    ((or (eq (keep-tabular-function-sorted? tabular-function-or-class-definition)
	     parse-result)
	 (=f (number-of-rows-in-table tabular-function-or-class-definition) 0))
     parse-result)
    (t (values
	 bad-phrase
	 (copy-text-string
	   "The sort specification cannot be so changed once the table has rows.")))))

(def-slot-value-writer keep-tabular-function-sorted? (keep-tabular-function-sorted?)
  (twrite-string
    (if (null keep-tabular-function-sorted?)
	"no"
	(case keep-tabular-function-sorted?
	  (args "by args")
	  (values "by values")))))

(define-category-evaluator-interface (keep-tabular-function-sorted?
				      :access read-write)
    (member no args values)
  ((set-form (evaluation-value))
   evaluation-value)
  ((get-form (slot-value))
   (or slot-value 'no)))


(def-slot-value-writer add-or-delete-rows (add-or-delete-rows)
  (declare (ignore add-or-delete-rows))
  (twrite-string "add or delete rows"))

(defun tabular-function-car-tester (pair1 pair2)
  (tabular-function-datum-lessp
    (car pair1) (car pair2)))

(defun tabular-function-cdr-tester (pair1 pair2)
  (tabular-function-datum-lessp
    (cdr pair1) (cdr pair2)))







;;; The def-virtual-attribute `values-for-table-of-values' gets and sets the x and
;;; f(x) fields in a tabular-function-of-1-arg.  Its type specification
;;; conforms to the add-or-delete-rows grammar category of the add-or-delete
;;; -rows slot which is not a user-visible slot.  The getter forms its return
;;; value from the column-of-args and column-of-values slots.  The setter uses
;;; the add-or-delete-rows compiler to delete the previous values from those
;;; slots, but bypasses the compiler when setting the new value because it can
;;; rely on the type specification to catch illegal values.

;;; Note that the empty sequence (sequence()) is used instead of nil (no value).

(def-virtual-attribute values-for-table-of-values
    ((class tabular-function-of-1-arg)
     (sequence
       (structure
	 ((x (or (no-item) symbol integer long float text))
	  (f-of-x (or (no-item) symbol integer long float text)))))
     ())
  
  :event-updates nil
  :initial ((class) (declare (ignore class)) nil)

  :getter
  ((tabular-function-of-1-arg)            
   (let* ((length (number-of-rows-in-table tabular-function-of-1-arg))
	  (tabular-args
	    (convert-series-of-values-to-list
	      (column-of-args tabular-function-of-1-arg) length))
	  (tabular-values
	    (convert-series-of-values-to-list
	      (column-of-values tabular-function-of-1-arg) length)))
     (loop for arg in tabular-args
	   for value in tabular-values
	   collect
	   (allocate-evaluation-structure
	     (eval-list 'x (and arg (copy-evaluation-value arg))
			'f-of-x (and value (copy-evaluation-value value))))
	     into tabular-function-eval-list
	     using eval-cons
	   finally
	     ;; Convert-series-of-values-to-list is called without copy-args?.
	     (reclaim-slot-value-list tabular-args)
	     (reclaim-slot-value-list tabular-values)
	     (return (allocate-evaluation-sequence tabular-function-eval-list)))))

  :setter
  ((tabular-function-of-1-arg new-value)
   
   (let* ((current-length (number-of-rows-in-table tabular-function-of-1-arg))
	  (delete-current-value-phrase (gensym-list 'delete current-length)))
     ;; Let the compiler delete the current value.
     (compile-add-or-delete-rows-for-slot
       delete-current-value-phrase tabular-function-of-1-arg t)
     (reclaim-gensym-list delete-current-value-phrase))

   (loop for arg-value-struct being each evaluation-sequence-element of new-value  
	 for x-arg = (evaluation-structure-slot arg-value-struct 'x)
	 for x-of-f-value = (evaluation-structure-slot arg-value-struct 'f-of-x) 
	 collect (copy-for-slot-value x-arg) into new-args using gensym-cons
	 collect (copy-for-slot-value x-of-f-value) into new-values using gensym-cons
	 finally (progn
		   (let ((new-length (length new-args)))
		     (when new-args
		       (multiple-value-bind (sorted-args sorted-values)
			 (sort-args-or-values-for-tabular-function-if-necessary
			   tabular-function-of-1-arg new-args new-values)
		       (setf (column-of-args tabular-function-of-1-arg)
			     (convert-list-to-series-of-values sorted-args))
		       (setf (column-of-values tabular-function-of-1-arg)
			     (convert-list-to-series-of-values sorted-values))
		       (reclaim-gensym-list sorted-args)
		       (reclaim-gensym-list sorted-values)))
		     (setf (number-of-rows-in-table tabular-function-of-1-arg)
			   new-length))))))




;;; The function `sort-args-or-values-for-tabular-function' is called by the
;;; compiler for add-or-delete-rows and the virtual-attribute
;;; values-for-table-of-values to sort the values or args as specified by the
;;; keep-tabular-function-sorted?  slot of the tabular-function-of-1-arg.

(defun sort-args-or-values-for-tabular-function-if-necessary
    (tabular-function-of-1-arg args values)
  (when (keep-tabular-function-sorted? tabular-function-of-1-arg)
    (loop for l on values
	  as m = args then next-m?
	  as next-m? = (cdr m)
	  do (setf (cdr m) (car l))
	     (setf (car l) m))
    (setq values
	  (sort-list
	    values
	    (case (keep-tabular-function-sorted? tabular-function-of-1-arg)
	      (args #'tabular-function-car-tester)
	      (values
	       #'tabular-function-cdr-tester))
	    nil))
    (setq args (car values))
    (loop with last-m? = nil
	  as l on values
	  do (if last-m? (setf (cdr last-m?) (car l)))
	     (setf last-m? (car l))
	     (setf (car l) (cdr last-m?))
	     (setf (cdr last-m?) nil)))
  (values args values))


;;; `Sort-tabular-function-if-necessary' is a stand-alone sorting routine
;;; used in the initialize-after-reading method. It just unpacks the
;;; arguments and values and calls the regular sorting routine that the
;;; slot-value compilers use.

(defun sort-tabular-function-if-necessary (tabular-function-of-1-arg)
  (when (keep-tabular-function-sorted? tabular-function-of-1-arg)
    (let* ((length (number-of-rows-in-table tabular-function-of-1-arg))
	   (args (convert-series-of-values-to-list
		   (column-of-args tabular-function-of-1-arg) length t))
	   (values (convert-series-of-values-to-list
		    (column-of-values tabular-function-of-1-arg) length t)))
      (multiple-value-bind (sorted-args sorted-values)
	  (sort-args-or-values-for-tabular-function-if-necessary
	    tabular-function-of-1-arg args values)
	(change-slot-value tabular-function-of-1-arg 'column-of-args sorted-args)
	(change-slot-value tabular-function-of-1-arg 'column-of-values sorted-values)))))




(def-slot-value-compiler add-or-delete-rows
    (parse-result tabular-function-of-1-arg
		  called-from-values-for-table-of-values-virtual-attribute?)
  (let* ((length (number-of-rows-in-table tabular-function-of-1-arg))
	 (args
	   (convert-series-of-values-to-list
	     (column-of-args tabular-function-of-1-arg) length))
	 (values
	   (convert-series-of-values-to-list
	     (column-of-values tabular-function-of-1-arg) length))
	 (delete-case? (eq (first parse-result) 'delete))
	 (unfinished-case? (eq (second parse-result) 'unfinished))	 
	 (number-of-rows?
	   (if (not unfinished-case?)
	       (second parse-result)))
	 (row-position? (third parse-result))
	 (row-position-relation? (if (consp row-position?) (first row-position?)))
	 (row-data? (fourth parse-result))
	 (arg-data? (second row-data?))
	 (arg-data-is-atomic?
	   (atomic-phrase-p arg-data?))
	 (value-data? (third row-data?))
	 (position-for-change
	   (cond
	     ((eq row-position? 'beginning) 0)
	     ((or (memq row-position-relation? '(before after)) row-data?)
	      (loop with x = (if row-position-relation?
				 (second row-position?)
				 (let ((arg-or-arg-list (second row-data?)))
				   (if (atomic-phrase-p arg-or-arg-list)
				       arg-or-arg-list
				       (second arg-or-arg-list))))
		    as i from 0
		    as y in args
		    when (or (tabular-function-datum-equal x y)
			     (if (and (slot-value-number-p x)
				      (slot-value-number-p y))
				 (with-temporary-gensym-float-creation
				     add-or-delete-rows-1
				   (< (slot-value-number-value x)
				      (slot-value-number-value y)))))
		      return
		      (cond
			((and (eq row-position-relation? 'after)
			      (or (not (slot-value-number-p x))
				  (not (slot-value-number-p y))
				  (with-temporary-gensym-float-creation
				      add-or-delete-rows-2
				    (= (slot-value-number-value x)
				       (slot-value-number-value y)))))
			 (if (null number-of-rows?)
			     (setq number-of-rows? 1))
			 (+f i 1))
			((and (eq row-position-relation? 'before)
			      delete-case?)
			 (if (or unfinished-case? (null number-of-rows?))
			     (progn
			       (setq number-of-rows? 1)
			       (-f i 1))
			     (-f i number-of-rows?)))	; do others like this!!!
			(t i))
		    finally	   ; REALLY FOR A "BEFORE" OR "WITH" ERROR!
		      (return length)))
	     (t (if delete-case?       ; on "at the end" or no row position or data
		    (if (or unfinished-case? (null number-of-rows?))
			0
			(-f length number-of-rows?))
		    length)))))
    (if delete-case?
	(loop with number-left-to-delete
		= (or number-of-rows?
		      (if (or unfinished-case? row-position?)
			  length
			  1))
	      as i from 0
	      as arg? in args
	      as value? in values
	      as delete-this?
		 = (and (>f number-left-to-delete 0)
			(>=f i position-for-change)
			(or (not unfinished-case?) (null arg?) (null value?))
			(or (null row-data?)

			    ;; The following tested with EQ in the atomic case.  This
			    ;; never would work for string matching, which happened not
			    ;; to work for other reasons.  The non-atomic case tested
			    ;; with equal, which would case with case-sensitivity.  Neither
			    ;; would have worked with slot value floats.  Changing to
			    ;; use tabular-function-datum-equal fixes these problems.
			    ;; (MHD 1/29/92)
			    (if arg-data-is-atomic?
				(tabular-function-phrase-datum-equal arg? arg-data?)
				(member
				  arg? arg-data?
				  :test #'tabular-function-phrase-datum-equal))))
	      unless delete-this?
		collect arg? into new-args using slot-value-cons
	      unless delete-this?
		collect value? into new-values using slot-value-cons
	      when delete-this?
		do (decff number-left-to-delete)
		   (reclaim-slot-value arg?)
		   (reclaim-slot-value value?)
	      finally
		(reclaim-slot-value-list args)
		(setq args new-args)
		(reclaim-slot-value-list values)
		(setq values new-values))	; convert!
	(loop with arg-cons-to-insert-after?
		= (if (not (=f position-for-change 0))
		      (nthcdr (-f position-for-change 1) args))
	      with rest-of-arg-data?
		= (if (not arg-data-is-atomic?) (cdr arg-data?))
	      with previous-arg? = nil
	      with previous-arg-difference?
	      with value-cons-to-insert-after?
		= (if arg-cons-to-insert-after?
		      (nthcdr (-f position-for-change 1) values))
	      with rest-of-value-data?
		= (if (not (atomic-phrase-p value-data?)) (cdr value-data?))
	      with previous-value? = nil
	      with previous-value-difference?
	      as i from 1
		   to (or number-of-rows?
			  (if (not arg-data-is-atomic?) (length (cdr arg-data?)))
			  1)
	      collect
	      (let ((new-arg
		      (setq previous-arg?
			    (cond
			      (arg-data-is-atomic? arg-data?)
			      ((eq (car rest-of-arg-data?) 'etc.)		   
			       (if previous-arg-difference?
				   (cond
				     ((and (fixnump previous-arg?)
					   (fixnump previous-arg-difference?))
				      (+f previous-arg?
					  previous-arg-difference?))
				     (t
				      (with-temporary-gensym-float-creation
					  add-or-delete-rows
					(make-phrase-float
					  (+ (phrase-number-value previous-arg?)
					     (phrase-number-value
					       previous-arg-difference?))))))
				   previous-arg?))
			      (t (setq previous-arg-difference?
				       (cond
					 ((and (fixnump (car rest-of-arg-data?))
					       (fixnump previous-arg?))
					  (-f (car rest-of-arg-data?)
					      previous-arg?))
					 ((and (phrase-number-p (car rest-of-arg-data?))
					       (phrase-number-p previous-arg?))
					  (with-temporary-gensym-float-creation
					      add-or-delete-rows-2
					    (make-phrase-float
					      (- (phrase-number-value
						   (car rest-of-arg-data?))
						 (phrase-number-value
						   previous-arg?)))))))
				 (pop rest-of-arg-data?))))))
		(copy-for-slot-value new-arg))
		into new-args using slot-value-cons
	      collect
	      (let ((new-value
		      (setq previous-value?
			    (cond
			      ((atomic-phrase-p value-data?) value-data?)
			      ((eq (car rest-of-value-data?) 'etc.)
			       (if previous-value-difference?
				   (cond
				     ((and (fixnump previous-value?)
					   (fixnump previous-value-difference?))
				      (+f previous-value?
					  previous-value-difference?))
				     (t
				      (with-temporary-gensym-float-creation
					  add-or-delete-rows
					(make-phrase-float
					  (+ (phrase-number-value previous-value?)
					     (phrase-number-value
					       previous-value-difference?))))))
				   previous-value?))
			      (t (setq previous-value-difference?
				       (cond
					 ((and (fixnump (car rest-of-value-data?))
					       (fixnump previous-value?))
					  (-f (car rest-of-value-data?)
					      previous-value?))
					 ((and (phrase-number-p (car rest-of-value-data?))
					       (phrase-number-p previous-value?))
					  (with-temporary-gensym-float-creation
					      add-or-delete-rows-2
					    (make-phrase-float
					      (- (phrase-number-value
						   (car rest-of-value-data?))
						 (phrase-number-value
						   previous-value?)))))))
				 (pop rest-of-value-data?))))))
		(copy-for-slot-value new-value))
		into new-values using slot-value-cons
	      finally
		(if arg-cons-to-insert-after?
		    (setf (cdr arg-cons-to-insert-after?)
			  (nconc new-args (cdr arg-cons-to-insert-after?)))
		    (setq args (nconc new-args args)))
		(if value-cons-to-insert-after?
		    (setf (cdr value-cons-to-insert-after?)
			  (nconc new-values (cdr value-cons-to-insert-after?)))
		    (setq values (nconc new-values values)))
	        (multiple-value-bind
		    (sorted-args sorted-values)
		    (sort-args-or-values-for-tabular-function-if-necessary
		      tabular-function-of-1-arg args values)
		  (setq args sorted-args)
		  (setq values sorted-values))))
		    
    (setf (number-of-rows-in-table tabular-function-of-1-arg) (length args))
    (reclaim-series-of-values (column-of-args tabular-function-of-1-arg))
    (setf (column-of-args tabular-function-of-1-arg)
	  (convert-list-to-series-of-values args))
    (reclaim-slot-value-list args)
    (reclaim-series-of-values (column-of-values tabular-function-of-1-arg))
    (setf (column-of-values tabular-function-of-1-arg)
	  (convert-list-to-series-of-values values))
    (reclaim-slot-value-list values)
    (loop with tables    ; frame representations are assumed to be tables
	    = (copy-for-slot-value
		(frame-representations tabular-function-of-1-arg))
	  as table in tables
	  when (eq (class table) 'table-of-values)
	    do (loop with workspace? = (get-workspace-if-any table)
		     as image-plane
			in (if workspace? (image-planes-this-is-on workspace?))
		     do (unless called-from-values-for-table-of-values-virtual-attribute?
			  (put-up-table-of-values	; put right on top of image-plane (?)
			    tabular-function-of-1-arg
			    (halfr
			      (+r (left-edge-of-workspace-area-in-window image-plane)
				  (right-edge-of-workspace-area-in-window image-plane)))
			    (top-edge-of-workspace-area-in-window image-plane))))
	       (delete-frame table)
	  finally (reclaim-slot-value-list tables))
    nil))					; result of "compilation"



(def-slot-value-writer tabular-function-data-type (tabular-function-data-type)
  (cond
    ((null tabular-function-data-type)
     (twrite-string "none"))
    ((or (slot-value-float-p tabular-function-data-type)
	 (floatp tabular-function-data-type))	; floats legal? check later! (MHD 9/12/91)
     (with-temporary-gensym-float-creation
       writer-for-tabular-function-data-type
       (twrite-float
	 (slot-value-number-value tabular-function-data-type))))
    ((evaluation-long-p tabular-function-data-type)
     (write-evaluation-value tabular-function-data-type)
     )
    ((symbolp tabular-function-data-type)
     (princ-lowercase tabular-function-data-type))	; "write-name-in-lower-case"?
    ((text-string-p tabular-function-data-type)
     (tformat "~s" tabular-function-data-type) ; writes string parsably, with quotes ("")
     )
    (t (twrite tabular-function-data-type))))	; for integers, etc?






(def-class (table-of-values table-item not-user-instantiable))

;; Note that table-of-values tables use attribute-table-format as the
;; class of their table format; this prevents their class format from being
;; used exclusively to type them (or attribute tables)! 
;;
;; So there has to be a predicate attribute-table-p that tests the format in
;; addition to the class of its table arg.  (MHD 1/29/92)





;;; The function `put-up-table-of-values' ...

(defun put-up-table-of-values
    (tabular-function-of-1-arg x-in-window y-in-window)
  (let* ((class-format
	   (choose-font-format-per-fonts-table
	     'class-format			; table-of-values-title-format?
	     'font-for-attribute-tables))
	 (attribute-value-format
	   (choose-font-format-per-fonts-table
	     'attribute-value-format
	     'font-for-attribute-tables))
	 (table-rows
	   (loop with column-of-args = (column-of-args tabular-function-of-1-arg)
		 with column-of-values = (column-of-values tabular-function-of-1-arg)
		 as i from 0
		      below (number-of-rows-in-table tabular-function-of-1-arg)
		 collect
		 (slot-value-list
		   (let ((text-cell
			   (make-text-cell
			     (make-text-representation-for-slot-value-itself
			       tabular-function-of-1-arg	; irrelevant
			       (get-value-from-series-of-values	; a bit ineffic.
				 column-of-args i)
			       '(type tabular-function-data-type))
			     attribute-value-format)))	; table-of-values-entry-format?
		     (note-slot-represented-by-text-cell
		       text-cell tabular-function-of-1-arg (-f (-f i) 1)
		       nil)
		     text-cell)
		   (let ((text-cell
			   (make-text-cell
			     (make-text-representation-for-slot-value-itself
			       tabular-function-of-1-arg	; irrelevant
			       (get-value-from-series-of-values	; a bit ineffic.
				 column-of-values i)
			       '(type tabular-function-data-type))
			     attribute-value-format))) ; table-of-values-entry-format?
		     (note-slot-represented-by-text-cell
		       text-cell tabular-function-of-1-arg i
		       nil)
		     text-cell))
		   using slot-value-cons))
	 (table-of-values
	   (make-or-reformat-table
	     (nconc
	       (unless new-g2-classic-ui-p
		 (slot-value-list
		   (slot-value-list
		     nil
		     (make-text-cell		; class-format for "go-away" feature!
		       (slot-value-list
			 (
			  copy-constant-wide-string #w"Table of values"
			  ))
		       class-format))))
	       (slot-value-list		       ; table-of-values-title-format?
		 (slot-value-list
		   nil
		   (make-text-cell-for-slot
		     tabular-function-of-1-arg 'add-or-delete-rows nil
		     (get-type-of-slot-if-any
		       tabular-function-of-1-arg 'add-or-delete-rows nil)
		     attribute-value-format))	; table-of-values-entry-format?
		 (slot-value-list
		   (make-text-cell
		     (slot-value-list (
		                        copy-constant-wide-string #w" x "
		                       ))	; "Args"?
		     attribute-value-format)	; table-of-values-column-head-format?
		   (make-text-cell
		     (slot-value-list
		       (tformat-text-string
			 " ~(~A~) (x)"		; "~(~A~)"?
			 (or (get-primary-name-for-frame-if-any tabular-function-of-1-arg)
			     'f)))
		     attribute-value-format)))	; table-of-values-column-head-format?
	       table-rows)
	     (if new-g2-classic-ui-p	; table-of-values-format?
		 (get-ui-parameter 'attributes-table-format)
		 'attributes-table-format)
	     nil 'table-of-values t)))		; specify table class?
    (add-frame-representation-if-necessary	; similar code in put-up-attributes-table
      table-of-values tabular-function-of-1-arg)
    (let ((workspace (make-workspace 'temporary-workspace nil table-of-values 2)))
      (when new-g2-classic-ui-p
	(setf (stretch-new-image-planes-for-caption-p workspace) t)
	(setf (title-bar-caption-text workspace)
	      (twith-output-to-text (tformat "Table of values"))))
      (post-workspace-in-pane
	workspace
	current-workstation-detail-pane x-in-window y-in-window))))

;; Rather than having a table cell directly edited, consider making a table-cell frame to
;; represent the cell, with a slot putter to change the table.  This would require
;; special code in MENUS and in EDIT for highlighting the table cell and deleting the
;; table-cell frame.  In any case, some documentation in modules BOXES and TABLES needs
;; changing.

;; When the user clicks on the add-or-delete-rows entry, the editor should be directly
;; entered!

;; Generalize this and the following function to handle, as the first arg, other
;; tabular functions and attribute tables representing tabular functions!



;;; Compute-value-of-tabular-function-if-any either returns a symbol, string,
;;; fixnum, gensym float, or slot-value float.  Or else it returns nil if there
;;; is no value for arg.  If it returns a gensym float, it will have been freshly
;;; created, and the caller owns it.  Otherwise, anything this returns, i.e., a
;;; slot value float or a string, should be copied by the caller if it is to be
;;; kept around longer than transiently.  This should only be used in a temporary
;;; gensym-float creation environment.  

(defun compute-value-of-tabular-function-if-any (tabular-function-of-1-arg arg)
  (cond
    ((=f (number-of-rows-in-table tabular-function-of-1-arg) 0)
     nil)
    ((eq (keep-tabular-function-sorted? tabular-function-of-1-arg) 'args)
     (loop with column-of-args = (column-of-args tabular-function-of-1-arg)
	   with i = 0
	   with j = (number-of-rows-in-table tabular-function-of-1-arg)
	   as k = (halff (+f i j))		; assumed equiv. to (floor (+f i j) 2)
	   as arg-k				; sometimes at the end, k will repeat
	      = (get-value-from-series-of-values column-of-args k)
	   until (=f k i)
	   do (if (tabular-function-datum-lessp arg arg-k)
		  (setq j k)
		  (setq i k))
	   finally				; now i = k = j - 1
	     (return
	       (cond
		 ((tabular-function-datum-equal arg arg-k)
		    (get-value-from-series-of-values
		      (column-of-values tabular-function-of-1-arg) k))
		 ((and (tabular-function-interpolation? tabular-function-of-1-arg)
		       (slot-value-number-p arg)
		       (slot-value-number-p arg-k)
		       (or (>f k 0) (not (tabular-function-datum-lessp arg arg-k)))
		       (<f j (number-of-rows-in-table tabular-function-of-1-arg)))
		  (let* ((arg-j (get-value-from-series-of-values column-of-args j))
			 (column-of-values (column-of-values tabular-function-of-1-arg))
			 (value-k (get-value-from-series-of-values column-of-values k))
			 (value-j (get-value-from-series-of-values column-of-values j)))
		    (if (and (slot-value-number-p arg-j)
			     (slot-value-number-p value-k)
			     (slot-value-number-p value-j))
			(let* ((arg-k-as-gensym-float
				 (coerce-to-gensym-float
				   (slot-value-number-value arg-k)))
			       (denominator
				 (- (slot-value-number-value arg-j)
				    arg-k-as-gensym-float)))
			  (if (not (= denominator 0))
			      (+ (slot-value-number-value value-k)
				 (* (/ (- (slot-value-number-value arg)
					  arg-k-as-gensym-float)
				       denominator)  
				    (- (slot-value-number-value value-j)
				       (coerce-to-gensym-float
					 (slot-value-number-value value-k))))))))))))))
    (t (loop with column-of-args = (column-of-args tabular-function-of-1-arg)
	     as k from 0 below (number-of-rows-in-table tabular-function-of-1-arg)
	     when (tabular-function-datum-equal
		    (get-value-from-series-of-values column-of-args k) arg)
	       return (get-value-from-series-of-values
			  (column-of-values tabular-function-of-1-arg) k)))))

;; Also compute-inverse-of-tabular-function!  (For this case, it would be helpful to have
;; a "by args and values" sort specification for monotonically increasing functions.)

;; Where arg and all elements of column-of-args are known to be numbers, this could use
;; < in place of tabular-function-datum-lessp.

;; This returns a float whenever it interpolates, even if arg, arg-j, arg-k, value-j,
;; and value-k are all integers.  That seems wierd.  (MHD 1/6/92)

;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module GRAMMAR6B

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Michael Levin and Mark H. David 



(declare-forward-references-to-module
  grammar7
  write-data-server-map-from-slot
  compile-data-server-map-for-slot
  compile-format?-for-slot
  compile-display-interval-for-slot
  write-format?-from-slot
  write-display-interval-from-slot
  compile-horizontal-graph-ruling-parameter?-for-slot
  compile-vertical-graph-ruling-parameter?-for-slot
  compile-yes-or-no-for-slot
  compile-dial-ruling-parameter-for-slot
  compile-meter-ruling-parameter-for-slot
  compile-horizontal-gridline-interval?-for-slot
  compile-extra-grid-line-specs-for-slot
  write-horizontal-graph-ruling-parameter?-from-slot
  write-vertical-graph-ruling-parameter?-from-slot
  write-yes-or-no-from-slot
  write-horizontal-gridline-interval?-from-slot
  write-extra-grid-line-specs-from-slot
  write-dial-ruling-parameter-from-slot
  write-meter-ruling-parameter-from-slot
  compile-type-in-box-format?-for-slot
  write-type-in-box-format?-from-slot
  map-system-slot-name-to-alias
  transform-input-phrase-into-universal-date
  explanation-related-features-enabled-func? ;-dkuznick, 7/15/98
  get-initial-evaluation-value-for-default-override-1)

(declare-forward-references-to-module
  controls
  ;compile-embedded-rule-for-slot
  write-when-to-show-value-from-slot)

(declare-forward-references-to-module
  g2-foreign
  compile-foreign-function-timeout-interval-for-slot
  write-foreign-function-timeout-interval-from-slot)

(declare-forward-references-to-module
  g2-gsi
  compile-gsi-interface-name-for-slot
  write-gsi-interface-name-from-slot
  compile-process-initialization-string-for-slot
  write-process-initialization-string-from-slot
  compile-gsi-variable-grouping-specification-for-slot
  write-gsi-variable-grouping-specification-from-slot
  compile-attributes-which-identify-a-network-item-reference-for-slot
  write-attributes-which-identify-a-network-item-reference-from-slot
  write-options-for-item-reference-from-slot
  compile-options-for-item-reference-for-slot
  compile-timeout-interval-or-default-for-slot
  write-timeout-interval-or-default-from-slot
  write-interface-warning-message-level-from-slot)

(declare-forward-references-to-module
  g2ds
  compile-g2-to-g2-interface-name-for-slot
  write-g2-to-g2-interface-name-from-slot)

(declare-forward-references-to-module
  g2-meters
  compile-g2-meter-name-for-slot
  write-g2-meter-name-from-slot)

(declare-forward-references-to-module
  gfi-stubs
  compile-gfi-interface-object-for-slot
  write-gfi-interface-object-from-slot
  compile-gfi-output-file-update-frequency-for-slot
  write-gfi-output-file-update-frequency-from-slot
  write-gfi-time-stamp-format-from-slot
  compile-gfi-file-format-for-slot
  write-gfi-file-format-from-slot
  compile-gfi-file-pathname-for-slot
  write-gfi-file-pathname-from-slot
  write-gfi-yes-or-no?-from-slot
  compile-gfi-input-variables-update-mode-for-slot
  write-gfi-input-variables-update-mode-from-slot)

;; The section "Icon Description Grammar, Compiler, and Writer" has been removed
;; to a new module, GRAMMAR6C.  The forward references above were not
;; reconciled, and therefore some may be redundant. The category evaluator
;; interface for icon descriptions, which had appeared further below, was also
;; removed there. (MHD 12/11/96)

(def-slot-value-compiler connections? (parse-result)
  (fix-up-connections? parse-result))

;; Inherited means that it gets its connections from its superior, none means that
;; there are no connections. The choice of the internal representation nil for inherited,
;; and none for none is not the most natural, but is necessary for compatibility.

(defun fix-up-connections? (connections?)
  (cond ((eq connections? 'inherited)
	 ;; note: this used to match 'none-inherited here too, but that
	 ;; is no longer accepted by the grammar. (MHD 6/28/91)
	 nil)
	((eq connections? 'none) 'none)
	;; Fix up list, then check for non-positive coordinates.
	(t (let ((result
		   (cond
		     ((eq (car connections?) '\;)
		      ;; GENSYMCID-1204: Errors loading kb files stored as .xml and .kbx
		      ;; Remove attribute `line-pattern' and `arrows'
		      ;; when they means nothing,to resolve conflict when reading external
		      ;; definitions from a xml kb file.
		      (loop for stub in (cdr connections?)
			    when (listp stub)
			    do (loop for trailing-pointer = nil then leading-pointer
				     for leading-pointer = stub then (cdr leading-pointer)
				     for i from 0
				     until (null leading-pointer)
				     do (when (=f i 6)
					  (when (and (cdr leading-pointer)
						     (eq 'none (cadr leading-pointer)))
					    (setf (cdr leading-pointer)
						  (cddr leading-pointer))
					    (when (null (car leading-pointer)) 
					      (setf (cdr trailing-pointer)
						    (cdr leading-pointer))))
					  (loop-finish))))

		      (phrase-cons 'stubs (cdr connections?)))
		     (t (phrase-cons 'stubs (phrase-cons connections? nil))))))
	     (if
	       (loop for stub in (cdr result)
		     ;; Stubs should not be drawn if they do not lie on the perimeter!!!
		     ;; 0 is apparently a legal value.  It is used in tests/simulat2.kb
		     always (<=f 0 (fifth stub) 1000))
	       result
	       (values bad-phrase
		       (copy-text-string
			 "Coordinates must be positive and of reasonable size")))))))



(def-slot-value-writer attribute-descriptions
    (list-of-attribute-descriptions definition)
  (if list-of-attribute-descriptions
      (loop for listed-description on list-of-attribute-descriptions
	    doing (write-attribute-description
		    (car listed-description) definition definition)
	    when (cdr listed-description) do (tformat ";~%"))
      (twrite-string "none")))





;;; `write-attribute-description' reverses the grammar for writing an attribute
;;; description. It needs access to another slot of the definition,
;;; indexed-attributes-for-definition, in order to put ", with an index" as
;;; appropriate. 

(defun write-attribute-description
    (description definition-of-description definition &optional defining-class?)
  (let* ((attribute-name (attribute-name description))
	 (attribute-type-specification
	   (attribute-type-specification description))
	 (attribute-type-modifications
	   (attribute-type-modifications description))
	 (attribute-type-specification-for-printing
	   (case attribute-type-specification
	     (datum 'value) (number 'quantity)
	     (item-or-datum 'item-or-value) (t attribute-type-specification)))
	 (initial-value? (attribute-initial-value description))
	 (initial-type? (attribute-initial-type description))
	 (attribute-range? (attribute-range description))
	 (indexed-attributes
	   (indexed-attributes-for-definition definition-of-description))
	 (name-of-defined-class (name-of-defined-class definition)))

    ;; Print the attribute name.
    (if defining-class?
      (tformat "~(~a::~a~)" defining-class? attribute-name)
      (let ((write-symbols-parsably? t))
	(twrite-symbol attribute-name)))

    ;; Print the attribute type specification when it is not the default
    ;;  (or item-or-datum (no-item)).
    (cond ((consp attribute-type-specification-for-printing)
	   (cond
	     ((eq (car attribute-type-specification) 'class)
	      (let ((class (cadr attribute-type-specification)))
		(if (and initial-value?
			 (eq (second initial-value?) 'instantiate-variable))
		    (twrite " is given by ")
		    (twrite " is an instance of "))
		(twrite (supply-a-or-an class)) (twrite-symbol class)
		(when (or initial-value? attribute-range?) (twrite ","))))
	     ((structure-type-specification-p attribute-type-specification)
	      (twrite " is a structure,"))
	     ((sequence-type-specification-p attribute-type-specification)
	      (twrite " is a sequence,"))))
	  (t
	   (twrite " is ")
	   (twrite (supply-a-or-an attribute-type-specification-for-printing))
	   (twrite-symbol attribute-type-specification-for-printing) (twrite ",")))

    (when attribute-type-modifications
      (twrite " ")
      (write-attribute-type-modifications attribute-type-modifications)
      (twrite ","))

    ;; Print the "has values" phrase when there is an attribute range.
    (when attribute-range?
      (let ((write-symbols-parsably? t))
	(cond ((=i (length attribute-range?) 2)
	       (tformat "~( has values ~a or ~a~)" (fifth description)
			(sixth description)))
	      (t
	       (twrite " has values ")
	       (write-list-in-chicago-style (cddddr description) "or")))
	(when initial-value? (tformat ","))))
      
    ;; Print the initially clause when there is an initial value.
    ;; The inherited value may be from an override.
    (let ((default-initialization-value?
	      (unless (eq definition-of-description definition)
		(let* ((slot-description
			 (get-slot-description-of-class-description
			   attribute-name
			   (class-description
			     (name-of-defined-class
			       definition-of-description))))
		       (override?
			 (when (and slot-description
				    (classp name-of-defined-class))
			   (get-next-most-specific-override-on-slot-description
			     (name-of-defined-class definition)
			     slot-description))))
		  (when override? (second override?))))))
      (when (or initial-value? default-initialization-value?)
	(let* ((write-symbols-parsably? t)
	       (initial-value-to-print
		 (if default-initialization-value?
		     (if (or (aggregate-evaluation-value-p
			       default-initialization-value?)
			     (and (consp default-initialization-value?)
				  (eq (car default-initialization-value?)
				      :funcall)))
			 default-initialization-value?
			 (car default-initialization-value?))
		     initial-value?))
	       (initial-type-for-printing
		 (if (and default-initialization-value?
			  (not (aggregate-evaluation-value-p
				 initial-value-to-print)))
		     (cadr default-initialization-value?)
		     initial-type?)))
	  (cond ((and (consp initial-value-to-print)
		      (eq (car initial-value-to-print) :funcall))
		 (twrite (if (eq (second initial-value-to-print)
				 'instantiate-variable)
			     " initially is given by "
			     " initially is an instance of "))
		 (write-symbol-with-a-or-an
		   (third initial-value-to-print)))
		((aggregate-evaluation-value-p initial-value-to-print)
		 (twrite " initially is ")
		 (write-evaluation-value initial-value-to-print))
		(t
		 (twrite " initially is ")
		 (case initial-type-for-printing
		   (symbol
		    (print-constant initial-value-to-print 'symbol))
		   (text
		    (let ((write-strings-parsably? t))
		      (twrite-string initial-value-to-print)))
		   (t
		    (print-constant initial-value-to-print
				    initial-type-for-printing))))))))

      ;; Print the index phrase when the attribute is indexed.
    (when (memq attribute-name indexed-attributes)
      (twrite ", with an index"))))

(def-slot-value-writer connections? (value definition)
  (cond
    ((null value)
     (twrite "inherited")
     ;; the above today replaces the following. (MHD 6/28/91)
;     (let* ((class (name-of-defined-class definition))
;	    (connections-feature?
;	      (if class (get-slot-feature-if-any 
;			  class 'slot-group-for-block? 'stubs))))
;       (twrite (if connections-feature? "inherited" "none inherited")))
     )

    ((eq value 'none) (twrite-string "none"))

    (t
     (loop for ((name? class direction? edge coordinate
		       style? pattern? connection-arrows?) . more?) on (cdr value)
	   do
       (tformat
	 "~(~a~a~a~a~a located at ~a ~d~)"
	 (supply-a-or-an (or direction? class))
	 (cond ((eq direction? 'input) "input ")
	       ((eq direction? 'output) "output ")
	       (t ""))
	 class
	 (if name? " " "")
	 (if name? name? "")
	 edge
	 coordinate)
       (when style?
	 (tformat "~( with style ~a~)" style?))
       (when pattern?
	 (when style?
	   (tformat " and"))
	 (tformat " with line-pattern ")
	 (write-slot-value 'connection-line-pattern pattern? definition))
       (when connection-arrows?
	 (when (or style? pattern?)	; FIXME ?
	   (tformat " and"))
	 (tformat " with connection-arrows ")
	 (write-slot-value 'connection-arrows connection-arrows? definition))
       (if more?
	   (tformat ";~%"))))))



;;; Name-or-names. Just one name for now



(add-grammar-rules-for-list
  'name-or-names 'item-name '\, nil 'none)

;; The above replaces the following; Item-name used to be object-name.
;; Fix up more of the grammar to be generated this way, esp. in this
;; file!!  Also see if write-symbol-list can be used for writing in
;; a number of places! (MHD 6/7/90) 

;(add-grammar-rules
;  '((name-or-names 'none)
;    (name-or-names names-tail)

;    (names-tail object-name)
;    (names-tail (object-name '\, names-tail)
;		      (and 1 3) simplify-associative-operation)
;    ))


(def-slot-value-compiler name-or-names (translation)
  (cond
    ((eq translation 'none) nil)
    ((symbolp translation) translation)
    ((null (cddr translation)) (second translation))
    (t (cdr translation))))



(def-slot-value-writer name-or-names (name-or-names)
  (cond
    ((null name-or-names)
     (twrite-string "none"))
    ((atom name-or-names)
     (write-name-for-frame name-or-names))
    (t (loop as (name . rest-of-names)
		= name-or-names
		      then rest-of-names
	     do (write-name-for-frame name)
		(if (null rest-of-names) (loop-finish))
		(twrite-string ", ")))))



;;; Focal-classes is a slot of rules
 
(add-grammar-rules
  '((focal-classes 'none)
    (focal-classes focal-classes-tail)

    (focal-classes-tail class)
    (focal-classes-tail (class '\, focal-classes-tail)
			(and 1 3) simplify-associative-operation)
    ))


;; Slot-value-compiler for above in file RULES

(def-slot-value-writer focal-classes (value)
  (cond ((null value) (twrite-string "none"))
	(t (loop for (name . rest?) on value doing
	     (twrite-symbol name)
	     (if rest? (twrite ", "))))))




;;; The function `write-list-in-chicago-style' writes follows the Chicago
;;; Manual of Style's serial comma convention.  The second argument should be
;;; "and" or "or".

(defun write-list-in-chicago-style
       (list and-or-or &optional list-of-blocks?)
  (write-list-in-chicago-style-given-format
    list and-or-or
    (if list-of-blocks? "~(~NF~)" "~(~A~)"))
  nil)

	 


;;; The function `write-list-in-chicago-style-given-format' is like write-list-
;;; in-chicago-style, but it takes the tformat string that should be used when
;;; writing the elements of the given list.

(defun-void write-list-in-chicago-style-given-format
	    (list and-or-or tformat-string)
  (cond
    ((null list) (twrite-string "none"))
    ((null (cdr-of-cons list)) 
     (tformat tformat-string (car-of-cons list)))
    ((null (cdr-of-cons (cdr-of-cons list)))
     (tformat tformat-string (car-of-cons list))
     (twrite-character #.%space)
     (twrite-string and-or-or)
     (twrite-character #.%space)
     (tformat tformat-string (car-of-cons (cdr-of-cons list))))
    (t (loop for listed-element on list do
	 (tformat tformat-string (car-of-cons listed-element))
	 (cond ((cddr listed-element)
		(twrite-string ", "))
	       ((cdr listed-element)
		(tformat ", ~a " and-or-or)))))))


;; n.b. The two 'chicago-style' routines above and the 'end-punctuation'
;; below could be grouped into a section with all the other helper functions
;; that slot and note writers use should the work be put in to gather them
;; in one place. It would save time in the future and avoid redundancy.
;; ddm 4/22/98


;;; `Sentence-end-punctuation?' returns either nil or the wide character at the
;;; end of symbol-or-string that represents sentence-end punctuation, such as
;;; '?', '.', or '!'.  If there is none, this returns nil.

(defun sentence-end-punctuation? (symbol-or-string)
  (let ((string (stringw symbol-or-string)))
    (first (wide-character-member
	     (charw string (1-w (lengthw string)))
	     sentence-end-punctuation-characters))))

;; Strip off whitespace at end?





;;; Grammar for focal objects


(add-grammar-rules
  '((focal-objects 'none)
    (focal-objects focal-objects-tail)

    (focal-objects-tail object-name)
    (focal-objects-tail (object-name '\, focal-objects-tail)
			(and 1 3) simplify-associative-operation)
    ))


(def-slot-value-compiler focal-objects (translation)
  (cond
    ((eq translation 'none) nil)
    ((symbolp translation) (phrase-cons translation nil))
    (t (cdr translation))))

(define-category-evaluator-interface (focal-objects
				       :access read-write)
    (or (no-item)
	(sequence symbol 1))
  ((set-form (evaluation-value))
   (call-category-setter 'focal-classes evaluation-value nil nil nil))
  ((get-form (slot-value))
   (call-category-getter 'focal-classes slot-value nil nil)))

(def-slot-value-writer focal-objects (value)
  (cond ((null value) (twrite-string "none"))
	(t (loop for (name . rest?) on value doing
	     (twrite-symbol name)
	     (if rest? (twrite ", "))))))



;;; Grammar for categories

(add-grammar-rules
  '((categories 'none)
    (categories categories-tail)

    (categories-tail rule-category-name)
    (categories-tail (rule-category-name '\, categories-tail)
			(and 1 3) simplify-associative-operation)
    ))


(def-slot-value-compiler categories (translation)
  (compile-symbol-list translation))

(defun compile-symbol-list (translation)
  (cond
    ((eq translation 'none) nil)
    ((symbolp translation) (phrase-cons translation nil))
    (t (cdr translation))))

(define-category-evaluator-interface (categories
				       :access read-write)
    (or (no-item)
	(sequence symbol 1))
  ((set-form (evaluation-value))
   (call-category-setter 'focal-classes evaluation-value nil nil nil))
  ((get-form (slot-value))
   (call-category-getter 'focal-classes slot-value nil nil)))

(def-slot-value-writer categories (value)
  (write-symbol-list value))




;;; `Fix-default-override-on-user-defined-slot' expects a phrase of the
;;; form
;;;
;;;    (attribute-designation initial-value-phrase . junk)
;;;
;;; and mutates the argument phrase to be
;;;
;;;    (attribute-designation fixed-initial-value-phrase . (USER-DEFINED))
;;;
;;; where fixed-initial-value-phrase is the result of calling the subfunction
;;; `fix-override-initial-value' on initial-value-phrase.  That function
;;; generally turns the initial-value phrase into a slot constant, but may
;;; have a few peculiarities beyond that.
;;;
;;; Both of these function generally avoid copying of conses to a greater or
;;; lesser extent, including by means of sharing cons cells pointers and
;;; mutating cars and cdrs of conses.  If there are any cases where conses may
;;; not be shared, this function has to know about them and treat them with
;;; care.  (Note that this is normal for transformation functions.)

(defun fix-default-override-on-user-defined-slot (phrase)
  (let* ((initialization-phrase (second phrase)))
    (setf (second phrase)
	  (fix-override-initial-value initialization-phrase))
    (setf (cddr phrase) (phrase-list 'user-defined))
    phrase))

(defun fix-override-initial-value (initialization-phrase)  
  (cond
    ((consp initialization-phrase)
     (cond ((eq (car-of-cons initialization-phrase) :funcall)
	    (phrase-list initialization-phrase))
	   ((truth-value-phrase-p initialization-phrase)
	    (phrase-list (car initialization-phrase) 'truth-value))
	   ((and (phrase-number-p (car initialization-phrase))
		 (symbolp (cdr initialization-phrase)))
	    ;; (phrase-number . unit-of-measure) case
	    ;; initialization-phrase is a unit-of-measure phrase
	    (phrase-list
	      (car initialization-phrase)
	      (cdr initialization-phrase)))
	   ((or (phrase-structure-p initialization-phrase)
		(phrase-sequence-p initialization-phrase))
	    initialization-phrase)))
    ((null initialization-phrase)
     (phrase-list nil nil))
    ((phrase-number-p initialization-phrase)
     (phrase-list initialization-phrase 'number))
    ((symbolp initialization-phrase)
     (phrase-list initialization-phrase 'symbol))
    ((text-string-p initialization-phrase)
     (phrase-list initialization-phrase 'text))))

;; Compare with fix-attribute-description-initial-value and see combination is
;; worthwhile!  (MHD 5/15/97)


(defun-simple definition-subclassp (definition class)
  (loop for superclass in (direct-superiors-of-defined-class definition)
	thereis (subclassp superclass class)))

(defun compile-default-override (override slot-name? defining-class definition report-error?)
  (let* ((grammar-category?
	  (get-grammar-category-for-default-override
	   slot-name? defining-class t))
	 (slot-value-compiler?
	  (when (use-slot-value-compiler-for-default-overrides-p
		 grammar-category?)
	    (slot-value-compiler grammar-category?))))
    (when slot-value-compiler?
      (multiple-value-bind (compilation error-text?)
	  (funcall-compiled-function
	     slot-value-compiler?
	     (second override)
	     definition slot-name? defining-class
	     nil nil)
	(cond
	  ((or error-text? (eq compilation bad-phrase))	   
	   (when error-text?
	     (when report-error?
	       (tformat "~a" error-text?))
	     (reclaim-text-string error-text?))
	   t)
	  (t
	   (setf (second override) compilation)
	   nil))))))



(def-slot-value-compiler default-overrides-for-class-definitions
    (translation definition)

  ;; The following form is added to catch nested bad-phrases in overrides.
  ;; This occurs when a default override is concluded through components.
  (unless (or (null translation) (eq translation 'none))
    (let ((problem-override?
	   (if (eq (car translation) '\;)
	       (loop for override in (cdr translation)
		     when (eq (second override) bad-phrase)
		       return override)
	       (and (eq (second translation) bad-phrase)
		    translation))))
      (when problem-override?
	(return-from compile-default-overrides-for-class-definitions-for-slot
	  (values bad-phrase
		  (tformat-text-string
		   "The initial value for ~a could not be compiled."
		   (map-system-slot-name-to-alias (first problem-override?) definition)))))))

  (let* ((direct-superior-classes?
	  (direct-superiors-of-defined-class definition))
	 (direct-superiors-are-defined?
	  (direct-superiors-are-defined-p direct-superior-classes?))
	 (bad-attribute-name? nil)
	 (badly-formed-attribute-name? nil)
	 (problems? nil)
	 (g2-array-length-problems? nil)
	 (interface-timeout-period-problems? nil)
	 (fixed-translation
	  (cond
	    ((or (null translation) (eq translation 'none)) nil)
	    ((eq (car translation) '\;)
	     (loop for override
		       in (cdr (copy-for-phrase translation))					
		   collect override using phrase-cons))
	    (t (phrase-cons (copy-for-phrase translation) nil))))
	 (foundation-class?
	  (when direct-superiors-are-defined?
	    (most-refined-foundation-class-of-direct-superiors
	     direct-superior-classes?)))
	 (class-inheritance-path?
	  (and direct-superiors-are-defined?
	       (class-inheritance-path-of-definition definition)))
	 (system-slot-override-but-no-foundation-class? nil)
	 annotation
	 (initial-value-incompatible? nil))

    (loop for listed-default-override on fixed-translation
	  for default-override = (car listed-default-override)
	  for error-or-default-value = (second default-override)
	  do
      (cond ((member (car default-override)
		     (cdr listed-default-override) :test 'car-equal)
	     (return-from compile-default-overrides-for-class-definitions-for-slot
	       (values bad-phrase
		       (copy-text-string
			"This attribute initialization list has duplicate attribute names."))))
	    ((and (consp error-or-default-value)
		  (eq (car-of-cons error-or-default-value) bad-phrase))
	     (return-from compile-default-overrides-for-class-definitions-for-slot
	       (values bad-phrase
		       (if (cdr error-or-default-value)
			   (copy-text-string (cdr error-or-default-value))
			   (tformat-text-string
			    "The initial value for ~a could not be compiled."
			    (map-system-slot-name-to-alias
			     (car-of-cons default-override) definition))))))
	    (t nil)))

    (setq annotation
	  (twith-output-to-text-string
	    (loop for override in fixed-translation
		  for slot-name-or-alias = (car override)
		  for slot-name-is-qualified? = (consp slot-name-or-alias)
		  for class-check-or-user-defined? = (third override)
		  for override-on-user-defined-slot?
		      = (eq class-check-or-user-defined? 'user-defined)
		  for alias-or-slot-name?
		      = (unless override-on-user-defined-slot?
			  (map-system-slot-name-to-alias
			   slot-name-or-alias definition))
		  for slot-name?
		      = (if override-on-user-defined-slot?
			    slot-name-or-alias
			    (map-alias-to-system-slot-name
			     alias-or-slot-name? definition))
		  for possibly-acceptable-classes? =
		  (and (not override-on-user-defined-slot?)
		       (first class-check-or-user-defined?))
		  for possibly-acceptable-class? =
		  (if class-inheritance-path?
		      (loop for superior in (cdr class-inheritance-path?)
			    thereis
			    (loop for class in possibly-acceptable-classes?
				  when (subclassp superior class)
				    return t
				  finally (return nil)))
		      (when (and loading-kb-p direct-superiors-are-defined?)
			(loop for superior in direct-superior-classes?
			      thereis
			      (loop for class in possibly-acceptable-classes?
				    thereis (subclassp superior class)))))
		  for unacceptable-classes? =
		  (and (not override-on-user-defined-slot?)
		       (second class-check-or-user-defined?))
		  for unacceptable-class? =
		  (when unacceptable-classes?
		    (if class-inheritance-path?
			(loop for superior in (cdr class-inheritance-path?)
			      when (memq superior unacceptable-classes?)
				return t)
			(when (and loading-kb-p direct-superiors-are-defined?)
			  (loop for superior in direct-superior-classes?
				when (memq superior unacceptable-classes?)
				  return t))))
		  for class-check-bad? =
		  (and (not override-on-user-defined-slot?)
		       (or (not possibly-acceptable-class?)
			   unacceptable-class?))
		  for inheritable-slot-description?
		      = (slot-description-from-superior-class
			 slot-name? definition)
		  for slot-defining-class?
		      = (when inheritable-slot-description?
			  (defining-class inheritable-slot-description?))
		  do
	      ;; Now perform the fixups that would be done by other
	      ;; compilers, in particular those for options
	      ;; and initial-value-of-sensor.
	      (cond (override-on-user-defined-slot?
		     (let ((unqualified-name (unqualified-name (first override))))
		       (cond ((symbolp unqualified-name)
			      (when (reserved-system-slot-name-p 
				     definition unqualified-name)
				(setq bad-attribute-name? unqualified-name)
				(loop-finish)))
			     (t
			      (setq badly-formed-attribute-name? unqualified-name)
			      (loop-finish)))))
		    ((null foundation-class?)
		     (setq system-slot-override-but-no-foundation-class?
			   slot-name-or-alias)
		     (setq problems? t))
		    (t (case slot-name?
			 (frame-flags
			  (let ((flags (second override)))
			    (setf
			     (second override)
			     (if (memq 'variable possibly-acceptable-classes?)
				 (+f (case (first flags)
				       (forward-chain-flag #.forward-chain-flag)
				       (otherwise 0))
				     (if (eq (second flags)
					     'always-forward-chain-if-possible-flag)
					 #.always-forward-chain-if-possible-flag
					 0)
				     (case (third flags)
				       (passive-flag (+f #.passive-flag 
							 #.dont-backward-chain-flag))
				       (dont-backward-chain-flag 
					#.dont-backward-chain-flag)
				       (depth-first-flag #.depth-first-flag)
				       (otherwise 0))
				     (case (fourth flags)
				       (cache-data-for-explanation-flag 
					#.cache-data-for-explanation-flag)
				       (otherwise 0)))
				 (+f #.passive-flag
				     #.dont-backward-chain-flag
				     (case (first flags )
				       (forward-chain-flag #.forward-chain-flag)
				       (otherwise 0))
				     (if (eq (second flags)
					     'always-forward-chain-if-possible-flag)
					 #.always-forward-chain-if-possible-flag
					 0)
				     (case (third flags)
				       (cache-data-for-explanation-flag 
					#.cache-data-for-explanation-flag)
				       (otherwise 0)))))))
			 
			 (initial-value-of-variable-or-parameter
			  (setf
			   (second override)
			   (let* ((defining-class
				      (if inheritable-slot-description?
					  (defining-class inheritable-slot-description?)
					  (first (first (third override)))))
				  (grammar-category?
				   (get-grammar-category-for-default-override
				    slot-name? defining-class t))
				  (compiled-value
				   (funcall-compiled-function
				    (slot-value-compiler grammar-category?)
				    (second override)
				    nil slot-name? defining-class
				    nil nil)))
			     (unless (check-initial-value-of-variable-or-parameter
				      compiled-value fixed-translation definition)
			       (tformat "The initial value, ")
			       (write-slot-value grammar-category? compiled-value definition)
			       (tformat ", is not compatible ~
                                         with the type of the variable, ~NT."
					(get-data-type-of-variable-or-parameter-from-frame
					 definition fixed-translation))
			       (setq problems? t))
			     compiled-value)))
			 
			 (interface-timeout-period
			  (when (compile-default-override
				 override slot-name?
				 (or slot-defining-class?
				     (first (first (third override))))
				 definition
				 t)
			    (setq interface-timeout-period-problems? t)))
			 
			 (g2-array-length
			  (multiple-value-bind (compilation error-text?)
			      (compile-g2-array-length-for-slot
			       (second override) nil nil)
			    (cond ((eq compilation bad-phrase)
				   (setq g2-array-length-problems? t)
				   (twrite-string 
				    (or error-text? "Bad g2-array length.")))
				  (t (setf (second override) compilation)))))
			 
			 (g2-array-element-type
			  ;; Disallow the datum types as symbols here.  Note
			  ;; that this can be removed when the grammar category
			  ;; for class disallows these symbols itself.
			  (let ((element-type (second override)))
			    (when (type-specification-for-user-or-datum-type
				   element-type)
			      (tformat
			       "You cannot use ~a, since it names a value type, and ~
                            so cannot be a class name."
			       element-type)
			      (setq problems? t))))
			 
			 (list-type
			  (let ((element-type (second override)))
			    (when (type-specification-for-user-or-datum-type
				   element-type)
			      (tformat
			       "You cannot use ~a, since it names a value type, and ~
                            so cannot be a class name."
			       element-type)
			      (setq problems? t))))
			 
			 (t
			  (when (compile-default-override
				 override slot-name?
				 (or slot-defining-class?
				     (first (first (third override))))
				 definition
				 t)
			    (setq problems? t))))))

	      ;; Check that class sensitive slots are defaulted for a subclass
	      ;; of the class for which they are specified as third of override.

	      ;; The variable, class-check-bad?, will not be set when there are
	      ;; undefined direct superiors.
	      (when (and (not override-on-user-defined-slot?)
			 (or (null inheritable-slot-description?)
			     class-check-bad?))
		(unless problems?
		  (tformat
		   "The following are not inheritable system attributes ~
                     for this class: "))
		(when problems? (twrite ", "))
		(tformat "~(~a~)" alias-or-slot-name?)
		(setq problems? t)))))
    (cond
      (bad-attribute-name?
       (bad-attribute-name bad-attribute-name?))
      (badly-formed-attribute-name?
       (badly-formed-attribute-name))
      ((and problems? system-slot-override-but-no-foundation-class?)
       (system-slot-override-but-no-foundation-class
	system-slot-override-but-no-foundation-class?))
      ((or problems? g2-array-length-problems?) 
       (values bad-phrase annotation))
      (interface-timeout-period-problems?
       (values bad-phrase
	       (copy-text-string
		"interface-timeout-period should be a value between 1 and 16 seconds")))
      (initial-value-incompatible?
       (reclaim-text-string annotation)
       (values bad-phrase
	       (copy-constant-wide-string #w"The initial value is not consistent with the data type.")))
      (t (reclaim-text-string annotation)
	 ;; Prune the third and fourth elements (acceptable and unacceptable class lists
	 ;; from system overrides.
	 (loop for override in fixed-translation
	       collect (if (override-is-for-user-defined-slot-p override)
			   override
			   (phrase-list (first override) (second override)
					(first (first (third override)))))
		 using phrase-cons)))))



(def-slot-value-compiler default-overrides-for-object-definitions
    (translation definition)
  (let* ((direct-superior-classes?
	  (direct-superiors-of-defined-class definition))
	 (direct-superiors-are-defined?
	  (direct-superiors-are-defined-p direct-superior-classes?))
	 (bad-attribute-name? nil)
	 (badly-formed-attribute-name? nil)
	 (problems? nil)
	 (g2-array-length-problems? nil)
	 (fixed-translation
	  (cond
	    ((or (null translation) (eq translation 'none)) nil)
	    ((eq (car translation) '\;)
	     (loop for override
		       in (cdr (copy-for-phrase translation))					
		   collect override using phrase-cons))
	    (t (phrase-cons (copy-for-phrase translation) nil))))
	 (foundation-class?
	  (when direct-superiors-are-defined?
	    (most-refined-foundation-class-of-direct-superiors
	     direct-superior-classes?)))
	 (system-slot-override-but-no-foundation-class? nil)
	 annotation
	 (initial-value-incompatible? nil))

    (setq annotation
	  (twith-output-to-text-string
	    (loop for override in fixed-translation
		  for slot-name-or-alias = (car override)
		  for slot-name-is-qualified? = (consp slot-name-or-alias)
		  for class-check-or-user-defined? = (third override)
		  for override-on-user-defined-slot?
		      = (eq class-check-or-user-defined? 'user-defined)
		  for alias-or-slot-name?
		      = (unless override-on-user-defined-slot?
			  (map-system-slot-name-to-alias
			   slot-name-or-alias definition))
		  for slot-name?
		      = (if override-on-user-defined-slot?
			    slot-name-or-alias
			    (map-alias-to-system-slot-name
			     alias-or-slot-name? definition))
		  for class-check-bad? =
		  (and class-check-or-user-defined?
		       foundation-class?
		       (not (eq class-check-or-user-defined?
				'user-defined))
		       (if (eq slot-name-or-alias 'initial-value)
			   (not (eq foundation-class?
				    class-check-or-user-defined?))
			   (not (subclassp foundation-class?
					   class-check-or-user-defined?))))
		  for foundation-class-slot-description
		      = (slot-description-from-superior-class
			 slot-name? definition)
		  for slot-defining-class?
		      = (when foundation-class-slot-description
			  (defining-class foundation-class-slot-description))
		  do
	      ;; Now perform the fixups that would be done by other
	      ;; compilers, in particular those for options
	      ;; and initial-value-of-sensor.
	      (cond ((eq class-check-or-user-defined? 'user-defined)
		     (let ((unqualified-name (unqualified-name (first override))))
		       (cond ((symbolp unqualified-name)
			      (when (reserved-system-slot-name-p
				     definition unqualified-name)
				(setq bad-attribute-name? unqualified-name)
				(loop-finish)))
			     (t
			      (setq badly-formed-attribute-name? unqualified-name)
			      (loop-finish)))))
		    ((null foundation-class?)
		     (setq system-slot-override-but-no-foundation-class?
			   slot-name-or-alias)
		     (setq problems? t))
		    (t (case slot-name?
			 (frame-flags
			  (let ((flags (second override)))
			    (setf
			     (second override)
			     (if (eq class-check-or-user-defined? 'variable)
				 (+f (case (first flags)
				       (forward-chain-flag #.forward-chain-flag)
				       (otherwise 0))
				     (if (eq (second flags)
					     'always-forward-chain-if-possible-flag)
					 #.always-forward-chain-if-possible-flag
					 0)
				     (case (third flags)
				       (passive-flag (+f #.passive-flag 
							 #.dont-backward-chain-flag))
				       (dont-backward-chain-flag 
					#.dont-backward-chain-flag)
				       (depth-first-flag #.depth-first-flag)
				       (otherwise 0))
				     (case (fourth flags)
				       (cache-data-for-explanation-flag 
					#.cache-data-for-explanation-flag)
				       (otherwise 0)))
				 (+f #.passive-flag
				     #.dont-backward-chain-flag
				     (case (first flags)
				       (forward-chain-flag #.forward-chain-flag)
				       (otherwise 0))
				     (if (eq (second flags)
					     'always-forward-chain-if-possible-flag)
					 #.always-forward-chain-if-possible-flag
					 0)
				     (case (third flags)
				       (cache-data-for-explanation-flag 
					#.cache-data-for-explanation-flag)
				       (otherwise 0)))))))

			 (initial-value-of-variable-or-parameter
			  (setf
			   (second override)
			   (let* ((defining-class
				      (if foundation-class-slot-description
					  (defining-class foundation-class-slot-description)
					  (third override)))
				  (grammar-category?
				   (get-grammar-category-for-default-override
				    slot-name? defining-class t))
				  (compiled-value
				   (funcall-compiled-function
				    (slot-value-compiler grammar-category?)
				    (second override)
				    nil slot-name? defining-class
				    nil nil)))
			     (unless (check-initial-value-of-variable-or-parameter
				      compiled-value fixed-translation definition)
			       (tformat "The initial value, ")
			       (write-slot-value grammar-category? compiled-value definition)
			       (tformat ", is not compatible ~
                                         with the type of the variable, ~NT."
					(get-data-type-of-variable-or-parameter-from-frame
					 definition fixed-translation))
			       (setq problems? t))
			     compiled-value)))

			 (g2-array-length
			  (multiple-value-bind (compilation error-text?)
			      (compile-g2-array-length-for-slot
			       (second override) nil nil)
			    (cond ((eq compilation bad-phrase)
				   (setq g2-array-length-problems? t)
				   (twrite-string 
				    (or error-text? "Bad g2-array length.")))
				  (t (setf (second override) compilation)))))
			 
			 (g2-array-element-type
			  ;; Disallow the datum types as symbols here.  Note
			  ;; that this can be removed when the grammar category
			  ;; for class disallows these symbols itself.
			  (let ((element-type (second override)))
			    (when (type-specification-for-user-or-datum-type
				   element-type)
			      (tformat
			       "You cannot use ~a, since it names a value type, and ~
                            so cannot be a class name."
			       element-type)
			      (setq problems? t))))
			 
			 (list-type
			  (let ((element-type (second override)))
			    (when (type-specification-for-user-or-datum-type
				   element-type)
			      (tformat
			       "You cannot use ~a, since it names a value type, and ~
                            so cannot be a class name."
			       element-type)
			      (setq problems? t))))

			 (t
			  (when (compile-default-override
				 override slot-name?
				 (or slot-defining-class? (third override))
				 definition
				 t)
			    (setq problems? t))))))

	      ;; Check that class sensitive slots are defaulted for a subclass
	      ;; of the class for which they are specified as third of override.

	      ;; The variable, class-check-bad?, will not be set when there are
	      ;; undefined direct superiors.
	      (when (and (not (eq class-check-or-user-defined? 'user-defined))
			 (or (null foundation-class-slot-description)
			     class-check-bad?))
		(unless problems?
		  (tformat "The following are not attributes of ~(~A~): "
			   foundation-class?))
		(when problems? (twrite ", "))
		(tformat "~(~a~)" alias-or-slot-name?)
		(when class-check-bad?
		  (tformat " for ~(~a~)" class-check-or-user-defined?))
		(setq problems? t)))))

    (cond
      (bad-attribute-name?
       (bad-attribute-name bad-attribute-name?))
      (badly-formed-attribute-name?
       (badly-formed-attribute-name))
      ((and problems? system-slot-override-but-no-foundation-class?)
       (system-slot-override-but-no-foundation-class
	system-slot-override-but-no-foundation-class?))
      ((or problems? g2-array-length-problems?)
       (values bad-phrase annotation))
      (initial-value-incompatible?
       (reclaim-text-string annotation)
       (values bad-phrase
	       (copy-constant-wide-string #w"The initial value is not consistent with the data type.")))
      (t (reclaim-text-string annotation)
	 fixed-translation))))




(def-slot-value-compiler default-overrides-for-connection-definitions
    (translation definition)
  (let* ((fixed-translation
	   (cond
	    ((or (null translation) (eq translation 'none)) nil)
	    ((eq (car translation) '\;)
	     (loop for override in (cdr (copy-for-phrase translation))					
		   collect override using phrase-cons))
	    (t (phrase-cons (copy-for-phrase translation) nil))))
	 (bad-attribute-name? nil)
	 (badly-formed-attribute-name? nil))
    (loop for override in fixed-translation
	  for slot-name-or-alias = (car override)
	  for slot-name-is-qualified? = (consp slot-name-or-alias)
	  for unqualified-name = (unqualified-name (first override))
	  for slot-description?
	      = (unless slot-name-is-qualified?
		  (possibly-aliased-slot-description-from-superior-class
		   slot-name-or-alias definition))
	  for defining-class?
	      = (when slot-description?
		  (defining-class slot-description?))
	  for unaliased-slot-name?
	      = (when slot-description?
		  (pretty-slot-name slot-description?))
	  do
      (cond ((symbolp unqualified-name)
	     (when (reserved-system-slot-name-p definition unqualified-name)
	       (setq bad-attribute-name? unqualified-name)
	       (loop-finish))
	     (when defining-class?
	       (compile-default-override
		override unaliased-slot-name?
		defining-class?
		definition
		nil)))
	    (t
	     (setq badly-formed-attribute-name? unqualified-name)
	     (loop-finish))))

    (cond (bad-attribute-name?
	   (bad-attribute-name bad-attribute-name?))
	  (badly-formed-attribute-name?
	   (badly-formed-attribute-name))
	  (t fixed-translation))))





(def-slot-value-compiler default-overrides-for-message-definitions
    (translation definition)
  (let* ((fixed-translation
	   (cond
	    ((or (null translation) (eq translation 'none)) nil)
	    ((eq (car translation) '\;)
	     (loop for override
		       in (cdr (copy-for-phrase translation))					
		   collect override using phrase-cons))
	    (t (phrase-cons (copy-for-phrase translation) nil))))
	 (bad-attribute-name? nil)
	 (badly-formed-attribute-name? nil))
    (loop for override in fixed-translation
	  for slot-name-or-alias = (car override)
	  for slot-name-is-qualified? = (consp slot-name-or-alias)
	  for unqualified-name = (unqualified-name (first override))
	  for slot-description?
	      = (unless slot-name-is-qualified?
		  (possibly-aliased-slot-description-from-superior-class
		   slot-name-or-alias definition))
	  for defining-class?
	      = (when slot-description?
		  (defining-class slot-description?))
	  for unaliased-slot-name?
	      = (when slot-description?
		  (pretty-slot-name slot-description?))
	  do
      (cond ((symbolp unqualified-name)
	     (when (reserved-system-slot-name-p definition unqualified-name)
	       (setq bad-attribute-name? unqualified-name)
	       (loop-finish))
	     (when defining-class?
	       (compile-default-override
		override unaliased-slot-name?
		defining-class?
		definition
		nil)))
	    (t
	     (setq badly-formed-attribute-name? unqualified-name)
	     (loop-finish))))

    (cond (bad-attribute-name?
	   (bad-attribute-name bad-attribute-name?))
	  (badly-formed-attribute-name?
	   (badly-formed-attribute-name))
	  (t fixed-translation))))





;;; Data-type-from-class, given a class which is
;;; a variable or parameter class, gives the default type for that class.
;;; If the argument is not a variable or parameter clas, the value is NIL.

;;; It must not be called for an argument which is not a class. The information
;;; comes from the class-description, not the class definition.

(defun data-type-from-class (class)
  (if (subclassp class 'variable-or-parameter)
      (slot-init-form
	(get-slot-description-of-class-description
	  'data-type-of-variable-or-parameter (class-description class)))))
		  


(defun write-default-overrides (value frame)
  (cond
    ((null value) (twrite-string "none"))
    (t 
     (loop for (override . rest?) on value
	   do (write-default-override override frame)
	      (when rest?
		(tformat ";~%")))
     (if (cdr value)
	 ;; If writing > 1 override, setq'd the following var to nil,
	 ;; since we will explicitly line linebreaks & do not want a
	 ;; single line:  (If only 1, we let write-default-override
	 ;; decide to change it if wants to.)
	 (setq leave-text-representation-as-a-single-line?
	       nil)))))
  
(def-slot-value-writer default-overrides-for-class-definitions
    (value frame)  
  (write-default-overrides value frame))

(def-slot-value-writer default-overrides-for-object-definitions
    (value frame)  
  (write-default-overrides value frame))

(def-slot-value-writer default-overrides-for-connection-definitions
    (value frame)  
  (write-default-overrides value frame))

(def-slot-value-writer default-overrides-for-message-definitions
    (value frame)  
  (write-default-overrides value frame))




;;; The following categories (that might be used for attribute-initializations)
;;; seem to require an instance as the last argument to the slot-value-writer.
;;; I believe this list is complete.  rh -- 21 June 2000

;; g2-array (might need to use "the symbol")
;constant-designation-list? (item-array)
;truth-value-list (truth-value-array)
;symbol-list (symbol-array)
;list-of-datum-constants (value-array)
;list-of-item-and-datum-constants? (g2-array)

;; variable-or-parameter (units)
;initial-sensor-value? (sensor)
;  The following writers all call the preceding writer.
;initial-value-integer? (integer-variable)
;initial-value-integer (integer-parameter)
;initial-value-float? (float-variable)
;initial-value-float (float-parameter)
;initial-value-long? (long-variable)
;initial-value-long (long-parameter)
;initial-value-integer? (integer-variable)
;initial-value-integer (integer-parameter)
;quantity? (quantitative-variable)
;quantity (quantitative-parameter)

(defun write-default-override (override frame)
  (multiple-value-bind (unaliased-slot-name user-defined-p class-of-override grammar-category?)
      (decode-default-override override frame t)
    (let ((override-value (second override))
	  (class-definition-p (eq (class frame) 'class-definition))
	  (aliased-slot-name (unless user-defined-p
			       (alias-slot-name-if-necessary unaliased-slot-name class-of-override)))
	  (class-inheritance-path (class-inheritance-path-of-definition frame)))
      (cond (user-defined-p
	     (let* ((initial-value (car override-value))
		    (slot-name unaliased-slot-name))
	       (let ((write-symbols-parsably? t))
		 (cond ((class-qualified-name-denotation-p slot-name)
			(twrite-symbol (class-qualifier slot-name))
			(twrite-string "::")
			(twrite-symbol (unqualified-name slot-name)))
		       (t (twrite-symbol slot-name))))
	       (unless (null initial-value)
		 (cond ((and (consp override-value)
			     (consp (car-of-cons override-value))
			     (eq (car-of-cons (car-of-cons override-value)) :funcall))
			(let ((funcall-form (car-of-cons override-value)))
			  (twrite (if (eq (second funcall-form)
					  'instantiate-variable)
				      " initially is given by "
				      " initially is an instance of "))
			  (write-symbol-with-a-or-an (third funcall-form))))
		       ((evaluation-value-p override-value)
			(twrite-string " initially is ")
			(write-evaluation-value override-value))
		       (t
			(let ((initial-type (cadr override-value)))
			  (cond
			    ((eq initial-type 'symbol)
			     (tformat "~( initially is ~a~)" initial-value))
			    ((eq initial-type 'text)
			     (twrite " initially is ")
			     (let ((write-strings-parsably? t))
			       (twrite-string initial-value)))
			    (t
			     (twrite " initially is ")
			     (print-constant initial-value initial-type)))))))))

	    (t (case unaliased-slot-name
		 (data-type-of-variable-or-parameter
		  (if class-definition-p
		      (tformat "data-type for ~(~a~): "
			       (cond ((memq 'quantitative-variable
					    class-inheritance-path)
				      'quantitative-variable)
				     ((memq 'quantitative-parameter
					    class-inheritance-path)
				      'quantitative-parameter)
				     (t 'sensor)))
		      (tformat "data-type for ~(~a~): " (third override)))
		  (write-slot-value grammar-category? override-value nil))

		 (validity-interval
		  (twrite "validity-interval: ")
		  (if (numberp override-value)	
		      (print-constant override-value 'seconds)
		      (twrite-symbol override-value)))

		 (simulation-details
		  (if (eq (second override-value)
			  'make-simulation-subtable-with-specific-class-and-install)
		      (tformat "supply-simulation-subtable: ~(~a~)"
			       (third override-value))
		      (twrite "supply-simulation-subtable: simulation-subtable")))

		 (attribute-displays-for-class
		  (twrite "attribute-displays: ")
		  (write-attribute-displays-for-class override-value))   

		 (cross-section-pattern-for-class
		  (twrite "cross-section-pattern: ")
		  (write-cross-section-pattern-from-slot
		    override-value frame))

		 (insert-duplicate-elements?
		  (tformat "allow-duplicate-elements-for-g2-list: ~a"
			   (if override-value "yes" "no")))

		 (frame-flags
		  (let ((class
			 (if (memq 'variable class-inheritance-path)
			     'variable
			     'parameter)))
		    (tformat "options-for-~(~a~): " class)
		    (case class
		      (variable
		       (write-variable-frame-flags-from-slot override-value nil))
		      (parameter
		       (write-parameter-frame-flags-from-slot override-value nil)))))

		 ((variable-or-parameter-history-specification?
		   history-specification-for-simulation-subtables?)
		  (twrite "history-keeping-spec for ")
		  (if (eq unaliased-slot-name 'history-specification-for-simulation-subtables?)
		      (twrite "simulation-subtable: ")
		      (twrite "variable-or-parameter: "))
		  (write-history-specification-from-slot override-value nil))

		 ((user-menu-choice-priority action-button-priority)
		  (twrite "action-priority for ")
		  (if (eq unaliased-slot-name 'action-button-priority)
		      (twrite "action-button: ")
		      (twrite "user-menu-choice: "))
		  (write-slot-value grammar-category? override-value nil))

		 ((percentage-extra-space-to-leave
		   value-on-activation? off-value-for-check-box
		   on-value-for-check-box value-for-radio-button)
		  (case unaliased-slot-name
		    (on-value-for-check-box
		     (twrite "on-value for check-box: "))
		    (value-for-radio-button
		     (twrite "on-value for radio-button: "))
		    (off-value-for-check-box
		     (twrite "off-value for check-box: "))
		    (t
		     (tformat "~(~A~): " aliased-slot-name)))
		  (write-attribute-from-slot override-value nil))

		 ((initial-value-of-variable-or-parameter)
		  (tformat "initial-value for ~(~a~): " (third override))
		  (if (or (slot-constantp override-value)
			  (not (slot-value-number-p override-value)))
		      (write-attribute override-value)
		      (let ((data-type?
			     (when frame
			       (second (assq 'data-type-of-variable-or-parameter
					     (default-overrides frame))))))
			(if (and data-type?
				 (not (memq data-type? '(truth-value number))))
			    (print-constant override-value data-type?)
			    (write-attribute-from-slot override-value nil)))))
		 
		 (g2-array-initial-values
		  (let ((array-class (third override)))
		    (tformat "initial-values for ~(~a~): " array-class)
		    (if (null override-value)
			(twrite-string "none")
			(case array-class
			  (quantity-array
			   (print-constant-list override-value 'number))
			  (float-array (print-constant-list override-value 'float))
			  (integer-array
			   (print-constant-list override-value 'integer))
			  (symbol-array (write-symbol-list-from-slot
					 override-value frame))
			  (text-array (print-constant-list override-value 'text))
			  (truth-value-array
			   (print-constant-list override-value 'truth-value))
			  (item-array (print-designation-list override-value))
			  (value-array (print-datum-constant-list override-value))
			  (g2-array
			   (print-item-and-datum-constant-list override-value frame))
			  (t (twrite-string "none"))))))

		 (list-type
		  (tformat "element-type for item-list: ~(~a~)" override-value))

		 (g2-array-element-type
		  (tformat "element-type for item-array: ~(~a~)" override-value))
		 
		 (g2-array-length
		  (tformat "array-length for g2-array: ~(~a~)" override-value))

		 (stubs-for-class ; for some reason, there is no alias for this
		  (twrite "stubs: ")
		  (write-connections?-from-slot override-value frame))

		 ;; any slot-value-writers that require the instance can't use this
		 ;; since the instance is an instance of this definition.
		 ;; But they are all covered by the preceding cases.
		 ;; See the comment before this function for the list of categories.
		 (t 
		  (tformat "~(~A~): " aliased-slot-name)
		  (write-slot-value grammar-category? override-value nil))))))))






;;; Grammars and writers for simulator

(add-grammar-rules
  '((simulator-class ('discrete 'state) discrete-state)
    (simulator-class ('continuous 'state) continuous-state)
    (simulator-class 'dependent)
    (simulator-class 'input)))

(def-slot-value-writer simulator-class (value)
  (twrite-symbol value))

;; The above looks wrong: if you typed in "discrete state", it would write
;; back at you "discrete-state".  It also looks to me like this grammar
;; is not even in use!  AGH should check and eliminate if possible.
;; (MHD 2/21/91) 




;;;; Grammar, Writer, and Compiler for Authors (authors-with-time-of-last-edit?)

(add-grammar-rules
  '((authors-with-time-of-last-edit?
     'none)
    (authors-with-time-of-last-edit?
     first-author-and-date)
    (authors-with-time-of-last-edit?
     (first-author-and-date '\, authors-list)
     (1 3))
    (first-author-and-date author)
    (first-author-and-date
     (author '\( frame-edit-timestamp '\))
     (1 . 3))
    (frame-edit-timestamp
     (date time-of-day-optionally-with-seconds)
     (1 2)
     transform-date-phrase-and-time-of-day-into-frame-edit-timestamp)
    ;; The following category is obsolete for frame edit timestamps, but is
    ;; still used for the Inspect grammar in QUERIES. (MHD 3/8/01)
    (date-as-edit-timestamp date 1 convert-local-date-to-edit-timestamp)
    (author symbol)))

(add-grammar-rules-for-list 'authors-list 'author '\, nil nil)

(defun transform-date-phrase-and-time-of-day-into-frame-edit-timestamp
    (date-and-time-of-day-as-seconds-since-midnight)  
  (with-temporary-gensym-float-creation convert-local-date-to-edit-timestamp
    (with-temporary-bignum-creation
      (let* ((universal-date
	       (first date-and-time-of-day-as-seconds-since-midnight))
	     (time-of-day-as-seconds-since-midnight
	       (second date-and-time-of-day-as-seconds-since-midnight)))
	(multiple-value-bind (day month year)
	    (decode-universal-date universal-date)
	  (multiple-value-bind (seconds minutes hours)
	      (decode-normalized-time-of-day time-of-day-as-seconds-since-midnight)
	    (finish-edit-timestamp-transform
	      (gensym-encode-unix-time
		seconds minutes hours day month year))))))))

(declare-grammar-transform-can-return-bad-phrase
  transform-date-phrase-and-time-of-day-into-frame-edit-timestamp)


(defun convert-local-date-to-edit-timestamp (universal-date)
  (with-temporary-gensym-float-creation convert-local-date-to-edit-timestamp
    (with-temporary-bignum-creation
      (let* ((unix-time
	       (multiple-value-bind (date month year)
		   (decode-universal-date universal-date)
		 (gensym-encode-unix-time 0 0 0 date month year))))
	
	(finish-edit-timestamp-transform unix-time)))))

(declare-grammar-transform-can-return-bad-phrase convert-local-date-to-edit-timestamp)



(defun finish-edit-timestamp-transform (unix-time)
  (cond
    ((<=e unix-time time-of-frame-edit-base-time)
     (values
       bad-phrase
       ;; It should print the min and max dates!!
       ;; "Timestamps cannot be earlier than September 2, 1993."))
       "Bad date: can't go back that far in time"))
    ((>e unix-time time-of-last-allowable-frame-edit-time)
     ;; This case never comes up, because the transformation function
     ;; for date, transform-input-phrase-into-universal-date, calls
     ;; convert-input-to-universal-date, which rejects any year greater
     ;; than 2399 (for unexplained reasons.)  On platforms with 29 bit
     ;; fixnums, time-of-last-allowable-frame-edit-time is some time 
     ;; during June 6, 3014.  - jv
     (values
       bad-phrase 
       "Bad date: can't go forward that far in time"))
    (t
     (multiple-value-bind (minutes seconds)
	 (floor (-e unix-time time-of-frame-edit-base-time) 60)
       (setq text-time-stamp-seconds seconds)
       (values minutes seconds)))))

	 
	 
		    

(defun transform-date-and-time-of-day-into-frame-edit-timestamp (phrase)
  (let ((date-as-edit-timestamp (first phrase))
	(time-of-day-as-seconds-since-midnight (second phrase)))
    ;; both of the above have already been checked for validity
    (+ date-as-edit-timestamp
       (floor time-of-day-as-seconds-since-midnight 60))))


(def-slot-value-compiler authors-with-time-of-last-edit? (parse-result)
  (cond
    ((eq parse-result 'none)		; only atom possible
     nil)
    ((atom parse-result)
     parse-result)
    (t
     (let ((date?
	     (if (and (consp parse-result)
		      (atom (cdr parse-result)))
		 (cdr parse-result)
		 (if (consp (first parse-result))
		     (cdr (first parse-result))))))
       (cond
	 ((and date? (<f date? frame-edit-base-timestamp))
	  (values
	    bad-phrase
	    (twith-output-to-text-string
	      (tformat "Bad date: ")
	      (twrite-frame-edit-timestamp date?)
	      (tformat ".  It cannot be earlier than ")
	      (twrite-frame-edit-timestamp
		frame-edit-base-timestamp))))
	 ;; ok.  Now, just strip off the \, in (\, ...), if nec.
	 ((and (cdr parse-result)
	       (consp (cdr parse-result))
	       (eq (first (second parse-result)) '\,))
	  ;; (x (\, . y)) => (x . y)
	  (phrase-cons
	    (first parse-result)
	    (cdr (second parse-result))))
	 (t
	  parse-result))))))
    


(def-slot-value-writer authors-with-time-of-last-edit? (value)
  (let ((first-author?
	  (if (consp value)
	      (if (consp (first value))
		  (car (first value))
		  (first value))
	      value))
	(last-edit-timestamp?
	  (if (consp value)
	      (if (consp (first value))
		  (cdr (first value))
		  (if (not (listp (cdr value)))
		      (cdr value)))
	      nil)))	      
    (cond
      ((or first-author? last-edit-timestamp?)
       (when first-author?
	 (twrite-symbol first-author?))
       (when last-edit-timestamp?
	 (when first-author?
	   (twrite-string " "))
	 (twrite-string "(")
	 (twrite-frame-edit-timestamp last-edit-timestamp?)
	 (twrite-string ")"))
       (when (and (consp value)
		  (listp (cdr value)))
	 (loop for author in (cdr value)
	       do (twrite-string ", ")
		  (twrite-symbol author))))
      (t
       (twrite-string "none")))))


(define-category-evaluator-interface (authors-with-time-of-last-edit?
				       :access read-write)
    (or (no-item)
	(structure authors-spec
		   ((timestamp (structure timestamp
					  ((year integer)
					   (month integer)
					   (date integer)
					   (hours integer)
					   (minutes integer))
					  (and year month date
					       hours minutes)))
		    (authors (sequence symbol 0)))
		   (and authors)))
  ((set-form (evaluation-value))
   (evaluation-etypecase evaluation-value
    ((no-item) 'none)
    ((structure)
     (block setter
       (let ((author-sequence
	       (evaluation-structure-slot evaluation-value 'authors))
	     (timestamp-structure
	       (evaluation-structure-slot evaluation-value 'timestamp))
	     (encoded-timestamp? nil))
	 (when timestamp-structure
	   (with-structure (timestamp-structure timestamp)
	     (unless (and (<=f 0 minutes 59)
			  (<=f 0 hours 23)
			  (<=f 1 date 31)
			  (<=f 1 month 12)
			  (<=f 1993 year))
	       (return-from setter
		 (values bad-phrase
			 (copy-text-string "timestamp out of range"))))
	     (let ((date-phrase
		     (phrase-list date
				  (nth (1-f month) months-of-the-year)
				  year)))
	       (multiple-value-bind
		   (transform-result error?)
		   (transform-input-phrase-into-universal-date
		     date-phrase)
		 (cond
		   ((eq transform-result bad-phrase)
		    (return-from setter (values bad-phrase (copy-text-string error?))))
		   (t
		    (multiple-value-bind
			(convert-result convert-error?)
			(convert-local-date-to-edit-timestamp
			  transform-result)
		      (cond
			((eq convert-result bad-phrase)
			 (return-from setter (values bad-phrase (copy-text-string convert-error?))))
			(t
			 (setf
			   encoded-timestamp?
			   (transform-date-and-time-of-day-into-frame-edit-timestamp
			     (phrase-list
			       convert-result
			       (+f (*f hours 3600) (*f minutes 60))))))))))))))
	 (let ((authors-list
		 (with-evaluation-sequence-to-phrase-list-mapping
		     (author-sequence x)
		   x)))
	   (cond ((and (not encoded-timestamp?)
		       (null (cdr authors-list)))
		  (car authors-list))
		 ((and encoded-timestamp?
		       (null authors-list))
		  (values bad-phrase
			  (copy-text-string "there cannot be a timestamp without an author")))
		 ((null (cdr authors-list))
		  (if encoded-timestamp?
		      (phrase-cons (car authors-list) encoded-timestamp?)
		      (car authors-list)))
		 (t
		  (let ((head (if encoded-timestamp?
				  (phrase-cons (car authors-list) encoded-timestamp?)
				  (car authors-list)))
			(tail (if (cdr authors-list)
				  (phrase-list (phrase-cons '\, (cdr authors-list)))
				  nil)))
		    (if (null tail)
			head
			(phrase-cons head tail)))))))))))
  ((get-form (value))
   (cond
     (value
      (let* ((first-author?
	       (or (if (consp value)
		       (if (consp (first value))
			   (car (first value))
			   (first value))
		       value)
		   'unknown)) ; compensate for a bug
	     (last-edit-timestamp?
	       (if (consp value)
		   (if (consp (first value))
		       (cdr (first value))
		      (if (not (listp (cdr value)))
			  (cdr value)))
		   nil))
	     (other-authors?
	       (if (and (consp value)
			(listp (cdr value)))
		   (cdr value)
		   nil))
	     (authors-sequence
	       (allocate-evaluation-sequence
		 (if other-authors?
		     (eval-cons first-author?
				(copy-list-using-eval-conses other-authors?))
		     (eval-list first-author?))))
	     (result
	       (allocate-evaluation-structure
		 (eval-list 'authors authors-sequence))))
	(when last-edit-timestamp?
	  (with-temporary-bignum-creation
	    (multiple-value-bind (seconds minutes hours date month year)
		(gensym-decode-unix-time
		  (+ time-of-frame-edit-base-time
		     (* last-edit-timestamp? 60)))
	      (declare (ignore seconds))
	      (setf (evaluation-structure-slot result 'timestamp)
		    (allocate-evaluation-structure-inline
		      'year year
		      'month month
		      'date date
		      'hours hours
		      'minutes minutes)))))
	result))
     (t
      (allocate-evaluation-structure
	(eval-list 'authors
		   (allocate-evaluation-sequence nil)))))))
  

;;; A bare-bones `time-of-day' grammar.  This will be developed further
;;; presently (at some point), e.g., for trend charts.
;;;
;;; For now, we only allow time of day to be expressed as
;;;
;;;    <hh>:<mm> a.m.|p.m.
;;;

(add-grammar-rules
  '((time-of-day
     (hour '\: minute side-of-meridian)
     (1 3 4)
     filter-and-normalize-time-of-day)
    (hour positive-integer)
    (minute positive-integer)
    (second positive-integer)
    (second-with-subsecond float)	; define/use "positive-float"?!
    (side-of-meridian 'a.m.)
    (side-of-meridian 'p.m.)))

(add-grammar-rules
  '((time-of-day-with-seconds
     (hour '\: minute '\: second side-of-meridian)
     (1 3 6 5)
     filter-and-normalize-time-of-day)))

(add-grammar-rules
  '((time-of-day-optionally-with-seconds time-of-day)
    (time-of-day-optionally-with-seconds time-of-day-with-seconds)))

(add-grammar-rules
  '((time-of-day-with-subseconds
     (hour '\: minute '\: second-with-subsecond side-of-meridian)
     (1 3 6 5)
     filter-and-normalize-time-of-day)))

(add-grammar-rules
  '((time-of-day-optionally-with-seconds-or-subseconds time-of-day)
    (time-of-day-optionally-with-seconds-or-subseconds time-of-day-with-seconds)
    (time-of-day-optionally-with-seconds-or-subseconds time-of-day-with-subseconds)))


(defun filter-and-normalize-time-of-day (time-of-day-phrase)
  (let* ((hour (first time-of-day-phrase))
	 (minutes (second time-of-day-phrase))
	 (side-of-meridian (third time-of-day-phrase))
	 (seconds
	   (or (fourth time-of-day-phrase)
	       (copy-for-phrase 0))) 	; too pedantic?!
	 (twenty-four-hour-clock (fifth time-of-day-phrase)))
    (cond
      ((and (not twenty-four-hour-clock) (not (<=f 1 hour 12)))
       (values bad-phrase "Hours must be between 1 and 12"))
      ((and twenty-four-hour-clock (not (<=f 0 hour 23)))
       (values bad-phrase "Hours must be between 0 and 23"))
      ((not (<=f 0 minutes 59))
       (values bad-phrase "Minutes must be between 0 and 59"))
      ((with-temporary-gensym-float-creation
	   filter-and-normalize-time-of-day
	 (not (<= 0 (phrase-number-value seconds) 59)))
       (values bad-phrase "Seconds must be between 0 and 59"))
      (t
       (let ((minutes-in-seconds
	       ;; first, get the number of minutes in the day, in terms of
	       ;; seconds:       
	       (* 60				; seconds
		  (+ minutes			; minutes
		     (* 60			; hours
			(if twenty-four-hour-clock
			    hour
			    (if (eq side-of-meridian 'p.m.)
				(+f (mod hour 12)
				    12)
				(mod hour 12))))))))
	 (if (phrase-float-p seconds)
	     (with-temporary-gensym-float-creation
		 filter-and-normalize-time-of-day
	       (copy-for-phrase		; make a phrase float
		 (+ (phrase-float-value seconds) minutes-in-seconds)))
	     (+ seconds minutes-in-seconds)))))))

(declare-grammar-transform-can-return-bad-phrase filter-and-normalize-time-of-day)

;; To test, this should be true:
;; 
;;   (= (+ (filter-and-normalize-time-of-day '(11 59 a.m.)) 60)
;;      (filter-and-normalize-time-of-day '(12 00 p.m.))
;;      (- (filter-and-normalize-time-of-day '(12 01 p.m.)) 60))




;;; decode-normalized-time-of-day ... does no checking, since assumes it's
;;; dealing with the (non-bad-phrase) result of the above.  Returns three
;;; values: seconds, minutes, and hours.

(defun decode-normalized-time-of-day (time-of-day-as-seconds-since-midnight)
  (multiple-value-bind (total-minutes seconds)
      (floorf time-of-day-as-seconds-since-midnight 60)
    (multiple-value-bind (hours minutes)
	(floorf total-minutes 60)
    (values seconds minutes hours))))

;; (decode-normalized-time-of-day (filter-and-normalize-time-of-day '(3 13 p.m.)))
;; => (values 0 13 15)
;; (decode-normalized-time-of-day (filter-and-normalize-time-of-day '(12 13 a.m.)))
;; => (values 0 13 0)


;;; The function `decode-normalized-time-of-day-with-subseconds' is like
;;; decode-normalized-time-of-day, but it does generic arithmetic, so it can
;;; handle its argument being a floating point number (or an integer).  Note
;;; that this does NOT set up temporary gensym-float creation context; so it
;;; should be called in such a context, lest it cons floats.
;;;
;;; The first value will be a float if the argument is a float.  The second and
;;; third values are always fixnums.

(defun decode-normalized-time-of-day-with-subseconds
    (time-of-day-as-seconds-since-midnight)
  (multiple-value-bind (total-minutes seconds)
      (floor time-of-day-as-seconds-since-midnight 60)
    (multiple-value-bind (hours minutes)
	(floor total-minutes 60)
    (values seconds minutes hours))))
		 
       
       
   




;;; Perhaps all aliases can be put here. 

;;; Aliases for all kb-frames

(define-slot-alias names name-or-names-for-frame)
(define-slot-alias notes frame-status-and-notes)
(define-slot-alias time-of-latest-change frame-timestamp?)
(define-slot-alias authors frame-author-or-authors)
(define-slot-alias change-log frame-change-log)
(define-slot-alias attribute-initializations default-overrides)
(define-slot-alias categories rule-categories)

;;; Aliases for variables

(define-slot-alias data-type data-type-of-variable-or-parameter)
(define-slot-alias last-recorded-value current-value-of-variable-or-parameter)
(define-slot-alias default-update-interval background-collection-interval?)
(define-slot-alias formula formula?)
(define-slot-alias initial-value-for-simulation non-default-initial-simulated-value?)
(define-slot-alias history-keeping-spec variable-or-parameter-history-specification?
  variable-or-parameter)
(define-slot-alias history-keeping-spec simulation-stored-history-specification?
  simulation-subtable)

;;; Aliases for simulator-frame
(define-slot-alias time-increment-for-update time-increment-for-update?)
(define-slot-alias simulation-formula simulation-formulas? simulation-subtable)


;;; Alias for statements


(define-slot-alias statement-text box-translation-and-text)
(define-slot-alias scan-interval rule-scan-interval)








;;; Grammar for history specification

(add-grammar-rules
  '((history-specification ('do 'not 'keep 'history) no)
    ;; Users should never be allowed to keep history without
    ;; specifying some limit. This caused a serious problem at Exxon.
;    (history-specification ('keep 'history) (history))
    (history-specification ('keep 'history 'with history-tail-1)
			   (history 4))

    (history-tail-1
     ('maximum 'number 'of 'data 'points '= integer)
     (7))
    (history-tail-1
     ('maximum 'number 'of 'data 'points '= integer '\, history-tail-2)
     (7 nil 9))
    (history-tail-1
     ('maximum 'age 'of 'data 'points '= interval)
     (nil 7))
    (history-tail-1
     ('maximum 'age 'of 'data 'points '= interval '\, history-tail-2)
     (nil 7 9))

    (history-tail-1
     ('maximum 'number 'of 'data 'points '= integer 'and
      'maximum 'age 'of 'data 'points '= interval)
     (7 15))
    (history-tail-1
     ('maximum 'number 'of 'data 'points '= integer 'and
      'maximum 'age 'of 'data 'points '= interval
      '\, history-tail-2)
     (7 15 17))

    (history-tail-2
     ('with 'minimum 'interval 'between 'data 'points '= quantity-interval)
     8)
    ))

;;; Note that both the compiler and writer for history specification are used
;;; by the compiler and writer for default-overrides.

(def-slot-value-compiler history-specification (parse-result)
  (let* ((new-value
	   (cond
	     ((eq parse-result 'no) nil)
	     ((and parse-result (consp (second parse-result)))
	      (prog1 parse-result
		     (setf (cdr parse-result) (second parse-result))
		     (if (third parse-result)
			 (setf (third parse-result) (car (third parse-result))))
		     (if (fourth parse-result)
			 (setf (fourth parse-result)
			       (car (fourth parse-result))))
		     ))
	     (t parse-result)))
	 (maximum-number-of-data-points (second new-value))
	 (minimum-data-point-interval? (fourth new-value)))
    (cond
      ((and maximum-number-of-data-points
	    (<=f maximum-number-of-data-points 0))
       (values bad-phrase
	       (copy-text-string
		 "Maximum number of data points must be positive.")))
      ((and maximum-number-of-data-points
	    (>f maximum-number-of-data-points largest-ring-buffer-vector-size))
       (values
	 bad-phrase
	 (tformat-text-string
	   "Maximum number of data points must be less than or equal to ~d."
	   largest-ring-buffer-vector-size)))
      (minimum-data-point-interval?
       (cond
       	 ((and (fixnump minimum-data-point-interval?)
	       (<f minimum-data-point-interval? 0))
	  (values
	    bad-phrase
	    (copy-text-string
	      "The minimum interval between data points must be greater than or equal to zero.")))
	 (t
	  (let ((millisecond-interval-or-bad-phrase? nil)
		(bad-phrase-text-string? nil))
	    (cond
	      ((and (fixnump minimum-data-point-interval?)
		    (=f minimum-data-point-interval? 0))
	       (setq millisecond-interval-or-bad-phrase? 0))
	      (t
	       (multiple-value-setq
		   (millisecond-interval-or-bad-phrase? bad-phrase-text-string?)
		 (adjust-scheduling-interval minimum-data-point-interval?))))
	    (cond ((null millisecond-interval-or-bad-phrase?)
		   bad-phrase)
		  ((eq millisecond-interval-or-bad-phrase? bad-phrase)
		   (values millisecond-interval-or-bad-phrase?
			   bad-phrase-text-string?))
		  (t
		   (setf (fourth new-value) millisecond-interval-or-bad-phrase?)
		   new-value))))))
      (t
       new-value))))



(def-slot-value-writer history-specification (value)
  (if (null value) (twrite "do not keep history")
      (progn
	(twrite "keep history")
	(if (cdr value) (twrite " with "))
	(when (second value)
	       (tformat "maximum number of data points = ~d" (second value))
	       (if (third value) (twrite " and ")))
	(when (third value)
	  (twrite "maximum age of data points = ")
	  (print-constant (third value) 'seconds))
	(let ((minimum-interval? (fourth value)))
	  (when minimum-interval?
	    (twrite ", with minimum interval between data points = ")
	    (cond
	      ((=f (modf-positive minimum-interval? 1000) 0)
	       (print-constant
		 (floorf-positive minimum-interval? 1000) 'seconds))
	      (t
	       (with-temporary-gensym-float-creation write-min-sched-interval
		 (print-constant
		   (/e (coerce-fixnum-to-gensym-float minimum-interval?) 1000.0)
		   'seconds)))))))))






;;;; Specific Category-Evaluator Interfaces




;;; `fix-attribute-initial-value' and `make-initial-value-for-user'
;;; are helper functions for the evaluator interface for the attribute-descriptions
;;; category.  They make up for some of the shenannigans that go on
;;; in the grammar-rule transforms that implement the parser this slot/category.
;;;
;;; Modified on 5-14-97 to take 2 args; the second one is a symbol that
;;; represents the class of embedded object to be created (or nil if that's
;;; inapplicable).  Either the first or second arg should be nil.  If neither
;;; are nil, the first one wins.   -jtidwell


(defun-allowing-unwind fix-attribute-initial-value
    (attribute-initial-value attribute-initial-item-class &optional attribute-initial-type?
			     attribute-initial-item-class-restricted-to-variable-or-parameter)
  (with-catch-handlers
      (((:convert-to-phrase-failure) (error-string)
	(values bad-phrase error-string)))
    (cond (attribute-initial-value
	   (let ((phrase (convert-initial-value-to-phrase attribute-initial-value)))
	     (if (and (symbolp attribute-initial-type?)
		      (numeric-data-type attribute-initial-type?))
		 (phrase-cons phrase attribute-initial-type?)
		 phrase)))
	  (attribute-initial-item-class
	   (phrase-list :funcall
			(if attribute-initial-item-class-restricted-to-variable-or-parameter
			    'instantiate-variable
			    'instantiate-object-in-attribute)
			attribute-initial-item-class))
	  (t
	   nil))))

;;; `fix-attribute-initial-value-or-return-from' is some trivial dung
;;; for calling the above function somewhat more conveniently in category
;;; evaluator setters.  The right thing to do would have been to change all
;;; error reporting in the parser/editor/category-evaluator-setter symbiotic
;;; thingy to report ALL errors by throwing.  

(defmacro fix-attribute-initial-value-or-return-from
    (block-tag attribute-initial-value attribute-initial-item-class &optional
	       attribute-initial-type attribute-initial-item-class-restricted-to-variable-or-parameter)
  `(multiple-value-bind (result error-string?)
       (fix-attribute-initial-value
	 ,attribute-initial-value ,attribute-initial-item-class ,attribute-initial-type
	 ,attribute-initial-item-class-restricted-to-variable-or-parameter)
     (cond ((eq result bad-phrase)
	    (return-from ,block-tag (values bad-phrase error-string?)))
	   (t
	    result))))


(defun convert-initial-value-to-phrase (element)
  (cond
    ((evaluation-symbol-p element)
     element)
    ((evaluation-integer-p element)
     element)
    ((evaluation-float-p element)
     (evaluation-quantity-to-phrase-quantity element))
    ((evaluation-text-p element)
     (copy-for-phrase element))
    ((evaluation-truth-value-p element)
     (phrase-cons 
       (evaluation-truth-value-value element)
       'truth-value))
    ((evaluation-structure-p element)
     (loop for (name . value)
	       being each evaluation-structure-pair of element
	   collect name into plist using phrase-cons 
	   collect (convert-initial-value-to-phrase value) into plist using phrase-cons 
	   finally
	     (return
	       (make-phrase-structure plist))))
    ((evaluation-sequence-p element)
     (loop for sub-element
	       being each evaluation-sequence-element of element
	   collect (convert-initial-value-to-phrase sub-element)
	   into list-of-elements using phrase-cons
	   finally
	     (return
	       (make-phrase-sequence list-of-elements))))
    ((framep element)
     (throw :convert-to-phrase-failure
       (copy-constant-wide-string #w"initial-values cannot contain items")))))

(defun make-initial-value-for-user (initial-value)
  (cond
    ((and (listp initial-value)
          (eq (car initial-value) :funcall)
	  (=f 3 (length initial-value))
	  (or (eq (cadr initial-value) 'instantiate-object-in-attribute)
	      (eq (cadr initial-value) 'instantiate-variable)))
     nil)
    ((slot-constantp initial-value)
     (cast-slot-constant-into-evaluation-value initial-value))
    (t
     (make-evaluation-value-from-managed-value
       nil ; maybe truth-values are slot-constants
       initial-value))))
  
(defun-simple make-initial-value-for-user-given-type (initial-value initial-type)
  (if (eq initial-type 'truth-value)
      (let* ((substitute-value
	       (slot-value-list initial-value 'truth-value))
	     (answer
	       (make-initial-value-for-user substitute-value)))
	(reclaim-slot-value-list substitute-value)
	answer)
      (make-initial-value-for-user initial-value)))


(defun make-initial-item-class-for-user (initial-value)
  (when (and (listp initial-value)
             (eq (car initial-value) :funcall)
	     (=f 3 (length initial-value))
	     (or (eq (cadr initial-value) 'instantiate-object-in-attribute)
		 (eq (cadr initial-value) 'instantiate-variable)))
    (caddr initial-value)))

(defun initial-item-class-restricted-to-variable-or-parameter-for-user-p (initial-value)
  (and (listp initial-value)
       (eq (car initial-value) :funcall)
       (=f 3 (length initial-value))
       (eq (cadr initial-value) 'instantiate-variable)))



(define-category-evaluator-interface (attribute-descriptions
				       :access read-write)
    (or (no-item)
	(sequence (structure
		    attribute-spec
		    ((attribute-name symbol)
		     (attribute-type-specification symbol)
		     (attribute-format (or symbol
					   (structure
					     float-format-spec
					     ((whole-number-precision integer)
					      (fraction-precision integer))
					     (and whole-number-precision fraction-precision))))
		     (attribute-initial-value datum)
		     (attribute-initial-item-class symbol)
		     (attribute-initial-item-class-restricted-to-variable-or-parameter truth-value)
		     (attribute-initial-type symbol)
		     (attribute-range (sequence symbol 1))
		     (attribute-is-indexed truth-value))
		    (and attribute-name)) ; required(minimum)-contents
		  1)) ; minimum-length 
  ((set-form (evaluation-value))
   (evaluation-etypecase evaluation-value
    ((no-item) 'none)
    ((sequence)
     (block setter
       (phrase-cons
	 'normalized-parse
	 (with-evaluation-sequence-to-phrase-list-mapping (evaluation-value attribute-info)
;	 (format t "loop top eval=~s~%" attribute-info)
	   (with-structure (attribute-info attribute-spec)
	     (let* ((fixed-attribute-initial-value
		      (fix-attribute-initial-value-or-return-from setter
                        attribute-initial-value
			attribute-initial-item-class
			attribute-initial-type
			(and attribute-initial-item-class-restricted-to-variable-or-parameter
			     (evaluation-boolean-is-true-p
			       attribute-initial-item-class-restricted-to-variable-or-parameter))))
		    (fixed-attribute-description
		      (fix-attribute-description
			(phrase-list
			  (phrase-list
			    attribute-name fixed-attribute-initial-value
			    ;;; the initial-type is no longer used - Yippee!
			    attribute-initial-item-class)
			  (and attribute-type-specification
			       (let ((type-spec
				       (or (type-specification-for-user-type
					     attribute-type-specification)
					   (phrase-list 'class attribute-type-specification))))
				 (if attribute-format
				     (phrase-list
				       type-and-modifications-tag
				       type-spec
				       (phrase-list
					 (if (symbolp attribute-format)
					     (phrase-list
					       'format-override
					       attribute-format)
					     (phrase-list
					       'format-override
					       'ddd.dddd-format
					       (with-structure
						   (attribute-format float-format-spec)
						 (phrase-cons
						   whole-number-precision
						   fraction-precision))))))
				     type-spec))))
			(and attribute-is-indexed
			     (evaluation-boolean-is-true-p attribute-is-indexed))))
		    (fixed-attribute-type
		      (attribute-definition-type-specification
			(second fixed-attribute-description)))
		    (attribute-range-list
		      (and attribute-range
			   (type-specification-subtype-p
			     'symbol fixed-attribute-type)
			   (with-evaluation-sequence-to-phrase-list-mapping
			       (attribute-range range-elt)
			     range-elt))))
	       (if attribute-format
		   (if (symbolp attribute-format)
		       (unless (or (memq attribute-format '(interval time-stamp free-text))
				   (date-format-description attribute-format))
			 (return-from setter (values bad-phrase
						     (twith-output-to-text-string
						       (tformat "Bad attribute format ~s for attribute ~s" attribute-format attribute-name)))))
		       (multiple-value-bind (bad-phrase? error-message)
			   (call-category-setter 'float-format attribute-format nil nil nil)
			 (when (eq bad-phrase? bad-phrase)
			   (return-from setter (values bad-phrase error-message))))))
	       
	       (unless (compatible-initial-attribute-value-p
			 attribute-initial-value
			 ;; the following line gets the "fixed" type-specification
			 fixed-attribute-type)
		 (return-from setter
		   (values bad-phrase
			   (twith-output-to-text-string
			     (tformat "Incompatible initial-value for attribute ~s"
			     attribute-name)))))
	       (if (null attribute-range-list)
		   fixed-attribute-description
		   (nconc fixed-attribute-description
			  (loop for i from (length fixed-attribute-description)
				      below (if (equal (car (last fixed-attribute-description)) '(indexed))
						5
						4)
				collect nil using phrase-cons)
			  attribute-range-list))))))))))
  ((get-form (slot-value frame))
   (cond
     (slot-value
      (with-list-to-evaluation-sequence-mapping (slot-value attribute-info)
	(with-new-structure (attribute-spec)
	  (gensym-dstruct-bind ((source-attribute-name
				 source-attribute-type-specification
				 source-attribute-initial-value 
				 source-attribute-initial-type
				 . source-attribute-range)
			       attribute-info)
	    (setf attribute-name source-attribute-name)
	    (unless (equal source-attribute-type-specification
			   '(OR ITEM-OR-DATUM (NO-ITEM)))
	      (setf attribute-type-specification
		    (user-type-for-type-specification
		      (attribute-definition-type-specification
			source-attribute-type-specification))))
	    (let*
		((attribute-type-modifications
		   (attribute-definition-type-modifications source-attribute-type-specification))
		 (format (cdr (assq 'format-override attribute-type-modifications))))
	      (when format
		(setf attribute-format
		      (if (eql (car format) 'ddd.dddd-format)
			  (call-category-getter 'float-format (second format) nil nil)
			  (car format)))))
	    (setf-non-nil attribute-initial-value
			  (make-initial-value-for-user-given-type
			    source-attribute-initial-value
			    source-attribute-initial-type))
	    (setf-non-nil attribute-initial-item-class
			  (make-initial-item-class-for-user
			    source-attribute-initial-value))
	    (when (initial-item-class-restricted-to-variable-or-parameter-for-user-p
		    source-attribute-initial-value)
	      (setf attribute-initial-item-class-restricted-to-variable-or-parameter
		    (make-evaluation-boolean-value t)))
	    (when (and (symbolp source-attribute-initial-type)
		       (numeric-data-type source-attribute-initial-type))
	      (setf-non-nil attribute-initial-type source-attribute-initial-type))
	    (when (and frame
		       (memq source-attribute-name
			     (indexed-attributes-for-definition frame)))
	      (setf attribute-is-indexed evaluation-true-value))
	    (when source-attribute-range
	      (setf attribute-range
		    (with-list-to-evaluation-sequence-mapping
			(source-attribute-range range-elt)
		      range-elt)))))))
     (t
      nil))))

(defun-simple compatible-initial-attribute-value-p (initial-value
						     type-specification)
  (cond
    ((type-specification-subtype-p type-specification 'datum)
     (type-specification-type-p initial-value type-specification))
    ((class-type-specification-p type-specification)
     (null initial-value))
    (t
     ;; assume its the universal type '(or item-or-datum (no-item))
     t)))
      

(define-category-evaluator-interface (inherited-attributes
				       :access read)
    (or (no-item)
	(sequence (structure
		    attribute-spec
		    ((attribute-name symbol)
		     (attribute-type-specification symbol)
		     (attribute-initial-value datum)
		     (attribute-initial-item-class symbol)
		     (attribute-initial-type symbol)
		     (attribute-range (sequence symbol 1))
		     (attribute-is-indexed truth-value))
		    (and attribute-name)) ; required(minimum)-contents
		  1)) ; minimum-length 
  ((get-form (slot-value frame?))
   (let* ((class-inheritance-path?
	    (if frame? (class-inheritance-path-of-definition frame?)))
	  (copied-superior-attribute-descriptions?
	    (and class-inheritance-path?
		 (loop with pretty-slot-names-encountered? =
		       (loop for attribute in (class-specific-attributes frame?)
			     collect (attribute-name attribute)
			       using gensym-cons)
		       with working-list-of-attribute-descriptions? = nil
		       for superior in (cdr class-inheritance-path?)
		       until (eq superior 'item)
		       do
		   (when (user-defined-class-p superior)
		     (loop with copied-attribute-descriptions =
			   (copy-for-slot-value
			     (class-specific-attributes
			       (class-definition superior)))
			   for copied-attribute in copied-attribute-descriptions
			   for attribute-name
			       = (attribute-name copied-attribute)
			   do
		       (if (memq attribute-name pretty-slot-names-encountered?)
			   (setf (attribute-name copied-attribute)
				 (unique-slot-name
				   (slot-description-from-class
				     superior attribute-name)))
			   (setq pretty-slot-names-encountered?
				 (gensym-cons
				   attribute-name
				   pretty-slot-names-encountered?)))
			   finally
			     (setq working-list-of-attribute-descriptions?
				   (nconc working-list-of-attribute-descriptions?
					  copied-attribute-descriptions))))
		       finally
			 (progn
			   (reclaim-gensym-list
			     pretty-slot-names-encountered?)
			   (return working-list-of-attribute-descriptions?))))))
     (setq slot-value copied-superior-attribute-descriptions?)
     (cond (slot-value
	    (prog1
		(with-list-to-evaluation-sequence-mapping
		    (slot-value attribute-info)
		  (with-new-structure (attribute-spec)
		    (let ((source-attribute-name (attribute-name attribute-info))
			  (source-attribute-type-specification (attribute-type-specification attribute-info))
			  (source-attribute-initial-value (attribute-initial-value attribute-info))
			  (source-attribute-initial-type (attribute-initial-type attribute-info))
			  (source-attribute-range (attribute-range attribute-info)))
		      (setf attribute-name source-attribute-name)
		      (unless (equal source-attribute-type-specification
				     '(OR ITEM-OR-DATUM (NO-ITEM)))
			(setf attribute-type-specification
			      (user-type-for-type-specification
				source-attribute-type-specification)))
		      (setf-non-nil attribute-initial-value
				    (make-initial-value-for-user
				      source-attribute-initial-value))
		      (setf-non-nil attribute-initial-item-class
				    (make-initial-item-class-for-user
				      source-attribute-initial-value))
		      (when (and (symbolp source-attribute-initial-type)
				 (numeric-data-type source-attribute-initial-type))
			(setf-non-nil attribute-initial-type source-attribute-initial-type))
		      (when (and frame?
				 (memq source-attribute-name
				       (indexed-attributes-for-definition frame?)))
			(setf attribute-is-indexed evaluation-true-value))
		      (when source-attribute-range
			(setf attribute-range
			      (with-list-to-evaluation-sequence-mapping
				  (source-attribute-range range-elt)
				range-elt))))))
	      (reclaim-slot-value slot-value)))
	   (t nil)))))




(define-category-evaluator-interface (history-specification
				       :access read-write)
    (or (no-item)
	(structure history-spec
		   ((maximum-number-of-data-points integer)
		    (maximum-age-of-data-points integer)
		    (minimum-interval-between-data-points number))
		   (or maximum-number-of-data-points maximum-age-of-data-points)))
  ((set-form (evaluation-value))
   (if evaluation-value
       (with-structure (evaluation-value history-spec)
	 (nconc
	   (phrase-list 'history)
	   (when (or maximum-number-of-data-points
		     maximum-age-of-data-points
		     minimum-interval-between-data-points)
	     (phrase-list maximum-number-of-data-points))
	   (when (or maximum-age-of-data-points
		     minimum-interval-between-data-points)
	     (phrase-list maximum-age-of-data-points))
	   (when minimum-interval-between-data-points
	     (phrase-list (invert-adjusted-scheduling-interval
			    minimum-interval-between-data-points)))))
       'no))
       
  ((get-form (slot-value))
   (if slot-value
       (gensym-dstruct-bind
	   ((nil maximum-number maximum-age minimum-interval) slot-value)
	 (when (or maximum-number maximum-age minimum-interval)
	   (allocate-evaluation-structure
	     (nconc
	       (when maximum-number
		 (eval-list 'maximum-number-of-data-points maximum-number))
	       (when maximum-age
		 (eval-list 'maximum-age-of-data-points maximum-age))
	       (when minimum-interval
		 (eval-list 'minimum-interval-between-data-points minimum-interval))))))
       nil)))

(define-category-evaluator-interface (list-of-classes
				       :access read-write)
    (or (no-item)
	(sequence symbol 1))
  ((set-form (evaluation-value))
   (evaluation-etypecase evaluation-value
    ((no-item) 'none)
    ((sequence) 
     (phrase-cons
       nil
       (with-evaluation-sequence-to-phrase-list-mapping (evaluation-value class-name)
	 class-name)))))
  ((get-form (slot-value))
   (cond
     (slot-value
      (with-list-to-evaluation-sequence-mapping (slot-value class-name)
	  class-name))
     (t
      nil))))

(define-category-evaluator-interface (list-of-object-classes
				       :access read-write)
    (or (no-item)
	(sequence symbol 1))
  ((set-form (evaluation-value))
   (evaluation-etypecase evaluation-value
    ((no-item) 'none)
    ((sequence) 
     (phrase-cons
       nil
       (with-evaluation-sequence-to-phrase-list-mapping (evaluation-value class-name)
	 class-name)))))
  ((get-form (slot-value))
   (cond
     (slot-value
      (with-list-to-evaluation-sequence-mapping (slot-value class-name)
	  class-name))
     (t
      nil))))

(define-category-evaluator-interface (list-of-connection-classes
				       :access read-write)
   (or (no-item)
	(sequence symbol 1))
  ((set-form (evaluation-value))
   (evaluation-etypecase evaluation-value
    ((no-item) 'none)
    ((sequence) 
     (phrase-cons
       nil
       (with-evaluation-sequence-to-phrase-list-mapping (evaluation-value class-name)
	 class-name)))))
  ((get-form (slot-value))
   (cond
     (slot-value
      (with-list-to-evaluation-sequence-mapping (slot-value class-name)
	  class-name))
     (t
      nil))))

(define-category-evaluator-interface (list-of-message-classes
				       :access read-write)
   (or (no-item)
	(sequence symbol 1))
  ((set-form (evaluation-value))
   (evaluation-etypecase evaluation-value
    ((no-item) 'none)
    ((sequence) 
     (phrase-cons
       nil
       (with-evaluation-sequence-to-phrase-list-mapping (evaluation-value class-name)
	 class-name)))))
  ((get-form (slot-value))
   (cond
     (slot-value
      (with-list-to-evaluation-sequence-mapping (slot-value class-name)
	  class-name))
     (t
      nil))))

(define-category-evaluator-interface (class-inheritance-path-of-definition
				       :access read)
    (or (no-item)
	(sequence symbol 1))
  ((get-form (slot-value))
   (cond 
     (slot-value
      (loop for class-name in slot-value
	    when (subclassp class-name 'item)
	      collect class-name into my-list using eval-cons
	    finally
	      (return (allocate-evaluation-sequence my-list))))
     (t
      nil))))

(define-category-evaluator-interface (attribute-displays-spec?
				       :access read-write)
    (or (no-item)
	(member inherited)
	(sequence
	  (structure attr-display-spec
		     ((attribute-list
			(sequence
			  (structure attr-spec
				     ((attribute symbol)
				      (qualified-class symbol)
				      (display-with-name truth-value))
				     (and attribute
					  display-with-name))
			  1))
		      (position (or (member at-standard-position)
				    (structure position-spec
					       ((x-offset integer)
						(y-offset integer))
					       (and x-offset y-offset)))))
		     (and attribute-list position))
	  1))
  ((set-form (evaluation-value))
   (evaluation-etypecase evaluation-value
     ((no-item) 'none)
     (symbol evaluation-value)
     ((sequence)
      (phrase-cons
	'\;
	(with-evaluation-sequence-to-phrase-list-mapping (evaluation-value attr-display-info)
	  (with-structure (attr-display-info attr-display-spec)
	    (let ((attr-list
		    (with-evaluation-sequence-to-phrase-list-mapping (attribute-list attr-info)
		      (with-structure (attr-info attr-spec)
			(let ((result (if (null qualified-class)
					  attribute
					  (phrase-list 'class-qualified-name qualified-class attribute))))
			  (if (evaluation-truth-value-is-true-p display-with-name)
			      
			      (phrase-list result)
			      result))))))
	      (phrase-list (phrase-cons '\, attr-list)
			   (if (evaluation-structure-p position)
			       (with-structure (position position-spec)
				 (phrase-list x-offset y-offset))
			       position)))))))))
  ((get-form (slot-value))
   (cond
     (slot-value 
      (cond ((consp slot-value)
	     (with-list-to-evaluation-sequence-mapping (slot-value attr-display-info)
	       (with-new-structure (attr-display-spec)
		 (gensym-dstruct-bind ((source-attr-list source-position)
				      attr-display-info)
		   (setf attribute-list
			 (with-list-to-evaluation-sequence-mapping (source-attr-list source-attr)
			   (with-new-structure (attr-spec)
			     (cond
			       ((consp source-attr)
				(cond
				  ((class-qualified-name-denotation-p source-attr)
				   (setf attribute (third source-attr))
				   (setf qualified-class (second source-attr))
				   (setf display-with-name evaluation-false-value))
				  ((class-qualified-name-denotation-p (car source-attr))
				   (setf attribute (third (car source-attr)))
				   (setf qualified-class (second (car source-attr)))
				   (setf display-with-name evaluation-true-value))
				  (t
				   (setf attribute (car source-attr))
				   (setf display-with-name evaluation-true-value))))
			       (t
				(setf attribute source-attr)
				(setf display-with-name evaluation-false-value))))))
		   (setf position
			 (if (consp source-position)
			     (with-new-structure (position-spec)
			       (gensym-dstruct-bind ((source-x-position source-y-position)
						    source-position)
				 (setf x-offset source-x-position)
				 (setf y-offset source-y-position)))
			     (setf position source-position)))))))
	    (t nil)))
     (t
      (make-evaluation-symbol 'inherited)))))








					
			


(define-category-evaluator-interface (new-class
				       :access read-write)
    (or (no-item) symbol)
  ((set-form (evaluation-value))
   (if (eq evaluation-value 'none)
       nil
       evaluation-value))
  ((get-form (slot-value))
   (or slot-value 'none)))

(define-category-evaluator-interface (list-of-slots
				       :access read)
    (or (no-item)
	(sequence symbol 1))
  ((get-form (slot-value))
   (cond
     (slot-value
      (with-list-to-evaluation-sequence-mapping (slot-value class-name)
	  class-name))
     (t
      nil))))

(define-category-evaluator-interface (connections?
				       :access read-write)
    (or (no-item)
	(member inherited)
	(sequence (structure stub-spec
			     ((portname symbol)
			      (connection-class symbol)
			      (stub-direction (member input output))
			      (edge-location (member top bottom right left))
			      (coordinate-location integer)
			      (style (member diagonal orthogonal))
			      (connection-arrows (named connection-arrows))
			      (line-pattern (named connection-line-pattern))))
		  1))
  ((set-form (evaluation-value))
   (with-safe-category-setter-calling
       (cond
	 ((eq evaluation-value 'inherited) 'inherited)
	 ((null evaluation-value) 'none)
	 (t
	  (phrase-cons
	    '\;
	    (with-evaluation-sequence-to-phrase-list-mapping
		(evaluation-value stub-info)
	      (with-structure (stub-info stub-spec)
		(phrase-list portname
			     connection-class
			     stub-direction
			     edge-location
			     coordinate-location
			     style
			     (call-category-setter-safely 'connection-line-pattern line-pattern)
			     (call-category-setter-safely 'connection-arrows connection-arrows)))))))))
  ((get-form (slot-value))
   (cond
     (slot-value
      (cond ((or (eq slot-value 'none)
		 (and (consp slot-value) ; flow.kb has two definitions
		      (null (cdr slot-value)))) ; that need this check
	     nil)
	    ((symbolp slot-value)
	     slot-value)
	    (t
	     (setq slot-value (cdr slot-value))
	     (with-list-to-evaluation-sequence-mapping (slot-value stub-info)
	       (with-new-structure (stub-spec)
		 (gensym-dstruct-bind ((source-portname
					source-connection-class
					source-stub-direction
					source-edge-location
					source-coordinate-location
					source-style
					source-line-pattern
					source-connection-arrows)
				      stub-info)
		   (setf-non-nil portname source-portname)
		   (setf-non-nil connection-class source-connection-class)
		   (setf-non-nil stub-direction source-stub-direction)
		   (setf-non-nil edge-location source-edge-location)
		   (setf-non-nil coordinate-location source-coordinate-location)
		   (setf-non-nil style source-style)
		   (setf-non-nil connection-arrows source-connection-arrows)
		   (let ((line-pattern-value
			   (call-category-getter
			     'connection-line-pattern
			     source-line-pattern
			     nil nil)))
		     (unless (eq line-pattern-value 'solid)
		       (setf-non-nil line-pattern line-pattern-value)))))))))
     (t nil))))

(define-category-evaluator-interface (stub-length
				       :access read-write)
    (or symbol number)
  ((set-form (evaluation-value))
   (if (eq evaluation-value 'inherited)
       nil
       (copy-evaluation-value evaluation-value)))
  ((get-form (slot-value))
   (if slot-value
       (copy-evaluation-value slot-value)
       'inherited)))

(define-category-evaluator-interface (junction-class
				       :access read-write)
    (or (no-item) symbol)
  ((set-form (evaluation-value))
   (if (eq evaluation-value 'none)
       nil
       evaluation-value))
  ((get-form (slot-value))
   (or slot-value 'none)))

(define-category-evaluator-interface (class
				       :access read-write)
    (or (no-item) symbol)
  ((set-form (evaluation-value))
   (if (eq evaluation-value 'none)
       nil
       evaluation-value))
  ((get-form (slot-value))
   (or slot-value 'none)))

(define-category-evaluator-interface (relation-name?
				       :access read-write)
    (or (no-item) symbol)
  ((set-form (evaluation-value))
   (if evaluation-value
       evaluation-value
       'none))
  ((get-form (slot-value))
   slot-value))

;; End file with CR.






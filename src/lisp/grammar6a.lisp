;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module GRAMMAR6A

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Michael Levin and Mark H. David




(declare-forward-references-to-module
  grammar6b
  write-region-specification-list
  make-bad-region-text-string
  compile-default-overrides-for-object-definitions-for-slot
  write-default-override)




;;;; grammar and writers for class definitions



  


(add-grammar-rules
  '((a-or-an 'a)
    (a-or-an 'an)

    ;; Grammar for the class-specific-attributes slot of definitions.

    ;; Parsed attribute descriptions are in the form:
    ;; (attribute-name attribute-type-specification attribute-initial-value
    ;;  attribute-initial-type attribute-range)

    ;; The input to fix-attribute-description is in this form:
    ;; ((attribute-name attribute-initial-value [attribute-initial-type])
    ;;   attribute-type-specification)

    (attribute-descriptions 'none)
    (attribute-descriptions attribute-descriptions-1)
    
    (attribute-descriptions-1 attribute-description)
    (attribute-descriptions-1 (attribute-description '\; attribute-descriptions-1)
			      (2 1 3) simplify-associative-operation)

    ;; item-or-value or no-item
    (attribute-description
      attribute-name (1 (or item-or-datum (no-item))))
    
    

    ;; g2-datum-types are:
    ;; value (datum), truth-value, quantity (number), integer, float, symbol,
    ;; text, structure, and sequence.
    ;; g2-meta-type is item-or-datum (item-or-value)

    ;; values, quantities, integers, floats, text, symbols, sequences, structures, truth values
    (attribute-description
     (attribute-name 'is a-or-an attribute-definition-type '\, 'initially 'is attribute-constant)
     ((1 8 4) 4)
     check-value-attribute-initialization-type (fix-attribute-description nil))
    (attribute-description
     (attribute-name 'is a-or-an attribute-definition-type)
     ((1 4) 4) add-initial-value-for-declared-type (fix-attribute-description nil))
    (attribute-description
     (attribute-name 'initially 'is attribute-constant)
     ((1 4)) (fix-attribute-description nil))

    ;; variable or parameter
    (attribute-description
     (attribute-name 'is 'given 'by a-or-an variable-or-parameter-class '\,
      'initially 'is 'given 'by a-or-an variable-or-parameter-class)
     (1 (class 6) (:funcall instantiate-variable 13) 13))
    (attribute-description
     (attribute-name 'is a-or-an attribute-definition-type-for-meta-type-only '\,
      'initially 'is 'given 'by a-or-an variable-or-parameter-class)
     (1 item-or-datum (:funcall instantiate-variable 11) 11))
    (attribute-description
     (attribute-name 'is 'given 'by a-or-an variable-or-parameter-class)
     (1 (class 6) (:funcall instantiate-variable 6) 6))
    (attribute-description
     (attribute-name 'initially 'is 'given 'by a-or-an
      variable-or-parameter-class)
     (1 (or item-or-datum (no-item)) (:funcall instantiate-variable 7) 7))

    ;; object class
    (attribute-description
     (attribute-name 'is 'an 'instance 'of a-or-an object-class '\, 'initially 'is 'an
      'instance 'of a-or-an object-class)
     (1 (class 7) (:funcall instantiate-object-in-attribute 15) 15))
    (attribute-description
     (attribute-name 'is a-or-an attribute-definition-type-for-meta-type-only '\, 'initially 'is 'an
      'instance 'of a-or-an object-class)
     (1 item-or-datum (:funcall instantiate-object-in-attribute 12) 12))
    (attribute-description
     (attribute-name 'is 'an 'instance 'of a-or-an object-class)
     (1 (class 7) (:funcall instantiate-object-in-attribute 7) 7))
    (attribute-description
     (attribute-name 'initially 'is 'an 'instance 'of a-or-an object-class)
     (1 (or item-or-datum (no-item))
      (:funcall instantiate-object-in-attribute 8) 8))

    (symbol-or-value-user-type 'symbol symbol)
    (symbol-or-value-user-type 'value datum)
     
    
    ;; symbol from symbol-or-symbol choices (range)
    (attribute-description
     (attribute-name 'is 'a symbol-or-value-user-type '\, 'has 'values
      symbolic-value 'or symbolic-value '\, 'initially 'is symbolic-value)
     (1 4 14 symbol 8 10) memq-3-cddddr)
    (attribute-description
     (attribute-name 'has 'values symbolic-value 'or symbolic-value)
     (1 (or item-or-datum (no-item)) nil symbol 4 6))
    (attribute-description
     (attribute-name 'has 'values symbolic-value 'or symbolic-value '\,
      'initially 'is symbolic-value)
     (1 (or item-or-datum (no-item)) 10 symbol 4 6) memq-3-cddddr)

    ;; symbol from symbol-list choices (range)
    (attribute-description
     (attribute-name 'is 'a symbol-or-value-user-type
      '\, 'has 'values symbolic-value-list
      '\, 'initially 'is symbolic-value)
     (1 4 12 symbol . 8) memq-3-cddddr cut-out-fifth-element)
    (attribute-description
     (attribute-name 'has 'values symbolic-value-list)
     (1 (or item-or-datum (no-item)) nil symbol . 4) cut-out-fifth-element)
    (attribute-description
     (attribute-name 'has 'values symbolic-value-list '\, 'initially 'is
      symbolic-value)
     (1 (or item-or-datum (no-item)) 8 symbol . 4) memq-3-cddddr
     cut-out-fifth-element)

    ;; variable or parameter supplying a symbol from symbol-or-symbol choices
    ;; (range)
    (attribute-description
     (attribute-name 'is 'given 'by a-or-an variable-or-parameter-class
      '\, 'has 'values symbolic-value 'or symbolic-value '\,
      'initially 'is 'given 'by a-or-an variable-or-parameter-class)
     (1 (class 6) (:funcall instantiate-variable 19) 19 10 12))
    (attribute-description
      (attribute-name 'has 'values symbolic-value 'or symbolic-value '\,
       'initially 'is 'given 'by a-or-an variable-or-parameter-class)
      (1 (or item-or-datum (no-item)) (:funcall instantiate-variable 13)
        13 4 6))

    ;; variable or parameter supplying a symbol from symbol-list choices (range)
    (attribute-description
     (attribute-name 'is 'given 'by a-or-an variable-or-parameter-class
      '\, 'has 'values symbolic-value-list '\,
      'initially 'is 'given 'by a-or-an variable-or-parameter-class)
     (1  (class 6) (:funcall instantiate-variable 17) 17 . 10) cut-out-fifth-element)
    (attribute-description
     (attribute-name 'has 'values symbolic-value-list
      '\, 'initially 'is 'given 'by a-or-an variable-or-parameter-class)
     (1 (or item-or-datum (no-item)) (:funcall instantiate-variable 11) 11 . 4)
     cut-out-fifth-element)

    ;; indexed attribute descriptions
    
    ;; item-or-value
    (attribute-description
      (attribute-name '\, 'with 'an 'index)
      (1 (or item-or-datum (no-item)) nil nil (indexed)))

    ;; values, quantities, integers, floats, text, symbols, sequences, structures, truth values
    (attribute-description
     (attribute-name 'is a-or-an attribute-definition-type '\, 'initially 'is attribute-constant
      '\, 'with 'an 'index)
     ((1 8 4) 4)
     check-value-attribute-initialization-type (fix-attribute-description t))
    (attribute-description
     (attribute-name 'is a-or-an attribute-definition-type '\, 'with 'an 'index)
     ((1 4) 4) add-initial-value-for-declared-type
     (fix-attribute-description t))
    (attribute-description
     (attribute-name 'initially 'is attribute-constant  '\, 'with 'an 'index)
     ((1 4)) (fix-attribute-description t))

    ;; variable or parameter
    (attribute-description
     (attribute-name 'is 'given 'by a-or-an variable-or-parameter-class '\,
      'initially 'is 'given 'by a-or-an variable-or-parameter-class
      '\, 'with 'an 'index)
     (1 (class 6) (:funcall instantiate-variable 13) 13 (indexed)))
    (attribute-description
     (attribute-name 'is a-or-an attribute-definition-type-for-meta-type-only '\,
      'initially 'is 'given 'by a-or-an variable-or-parameter-class
      '\, 'with 'an 'index)
     (1 item-or-datum (:funcall instantiate-variable 11) 11 (indexed)))
    (attribute-description
     (attribute-name 'is 'given 'by a-or-an variable-or-parameter-class
      '\, 'with 'an 'index)
     (1 (class 6) (:funcall instantiate-variable 6) 6 (indexed)))
    (attribute-description
     (attribute-name 'initially 'is 'given 'by a-or-an
      variable-or-parameter-class '\, 'with 'an 'index)
     (1 (or item-or-datum (no-item)) (:funcall instantiate-variable 7) 7
      (indexed)))

    ;; object class
    (attribute-description
     (attribute-name 'is 'an 'instance 'of a-or-an object-class '\, 'initially 'is 'an
      'instance 'of a-or-an object-class '\, 'with 'an 'index)
     (1 (class 7) (:funcall instantiate-object-in-attribute 15) 15 (indexed)))
    (attribute-description
     (attribute-name 'is a-or-an attribute-definition-type-for-meta-type-only '\, 'initially 'is 'an
      'instance 'of a-or-an object-class '\, 'with 'an 'index)
     (1 item-or-datum (:funcall instantiate-object-in-attribute 12) 12 (indexed)))
    (attribute-description
     (attribute-name 'is 'an 'instance 'of a-or-an object-class  '\, 'with 'an 'index)
     (1 (class 7) (:funcall instantiate-object-in-attribute 7) 7 (indexed)))
    (attribute-description
     (attribute-name 'initially 'is 'an 'instance 'of a-or-an object-class
      '\, 'with 'an 'index)
     (1 (or item-or-datum (no-item))
      (:funcall instantiate-object-in-attribute 8) 8 (indexed)))

    ;; symbol from symbol-or-symbol choices (range)
    (attribute-description
     (attribute-name 'is 'a 'symbol '\, 'has 'values
      symbolic-value 'or symbolic-value '\, 'initially 'is symbolic-value
      '\, 'with 'an 'index)
     (1 symbol 14 symbol (indexed) 8 10) memq-3-cdr-cddddr)
    (attribute-description
     (attribute-name 'has 'values symbolic-value 'or symbolic-value
      '\, 'with 'an 'index)
     (1 (or item-or-datum (no-item)) nil symbol (indexed) 4 6))
    (attribute-description
     (attribute-name 'has 'values symbolic-value 'or symbolic-value '\,
      'initially 'is symbolic-value  '\, 'with 'an 'index)
     (1 (or item-or-datum (no-item)) 10 symbol (indexed) 4 6) memq-3-cdr-cddddr)

    ;; symbol from symbol-list choices (range)
    (attribute-description
     (attribute-name 'is 'a 'symbol '\, 'has 'values symbolic-value-list
      '\, 'initially 'is symbolic-value '\, 'with 'an 'index)
     (1 symbol 12 symbol (indexed) . 8) memq-3-cdr-cddddr cut-out-sixth-element)
    (attribute-description
     (attribute-name 'has 'values symbolic-value-list '\, 'with 'an 'index)
     (1 (or item-or-datum (no-item)) nil symbol (indexed) . 4)
     cut-out-sixth-element)
    (attribute-description
     (attribute-name 'has 'values symbolic-value-list '\, 'initially 'is
      symbolic-value  '\, 'with 'an 'index)
     (1 (or item-or-datum (no-item)) 8 symbol (indexed) . 4) memq-3-cddddr
     cut-out-sixth-element)

    ;; variable or parameter supplying a symbol from symbol-or-symbol choices
    ;; (range)
    (attribute-description
     (attribute-name 'is 'given 'by a-or-an variable-or-parameter-class
      '\, 'has 'values symbolic-value 'or symbolic-value '\,
      'initially 'is 'given 'by a-or-an variable-or-parameter-class
      '\, 'with 'an 'index)
     (1  (class 6) (:funcall instantiate-variable 19) 19 (indexed) 10 12))
    (attribute-description
      (attribute-name 'has 'values symbolic-value 'or symbolic-value '\,
       'initially 'is 'given 'by a-or-an variable-or-parameter-class
       '\, 'with 'an 'index)
      (1 (or item-or-datum (no-item)) (:funcall instantiate-variable 13)
        13 (indexed) 4 6))

    ;; variable or parameter supplying a symbol from symbol-list choices (range)
    (attribute-description
     (attribute-name 'is 'given 'by a-or-an variable-or-parameter-class
      '\, 'has 'values symbolic-value-list '\,
      'initially 'is 'given 'by a-or-an variable-or-parameter-class
      '\, 'with 'an 'index)
     (1  (class 6) (:funcall instantiate-variable 17) 17 (indexed) . 10)
     cut-out-sixth-element)
    (attribute-description
     (attribute-name 'has 'values symbolic-value-list
      '\, 'initially 'is 'given 'by a-or-an variable-or-parameter-class
      '\, 'with 'an 'index)
     (1 (or item-or-datum (no-item)) (:funcall instantiate-variable 11) 11
      (indexed) . 4)
     cut-out-sixth-element)))

    ;; instantiate-variable and instantiate-object-in-atribute are
    ;; executed during the instantiation of an object that is presently
    ;; being defined. It happens well after the grammar is active. 


(add-grammar-rules
  '((symbolic-value symbol)
    
    (symbolic-value-list (symbolic-value '\, symbolic-value-list-tail)
			 (or 1 3) simplify-associative-operation)
    
    (symbolic-value-list-tail (symbolic-value '\, 'or symbolic-value) (or 1 4))
    (symbolic-value-list-tail (symbolic-value '\, symbolic-value-list-tail)
			      (or 1 3) simplify-associative-operation)
    

    						; grammar for stubs
    (connections? 'none)
    (connections? 'inherited)
    ;; We used to allow "none inherited" as a synonym for "none", but
    ;; we no longer do that, making the grammar simpler and also consistent
    ;; with other class definition slots, e.g., icon description. (MHD 6/28/91)
;    (connections? ('none 'inherited) none-inherited)
    (connections? connections-list)
    
    (connections-list (stub-info '\; connections-list)
		      (2 1 3) simplify-associative-operation)
    (connections-list stub-info)
    
    (stub-info stub-info-without-style (1 nil) fix-stub-info)
    (stub-info (stub-info-without-style connection-style-stub-spec) 
	       (1 2) fix-stub-info)
    (stub-info (stub-info-without-style connection-line-pattern-stub-spec) 
	       (1 nil 2) fix-stub-info)
    (stub-info (stub-info-without-style connection-style-stub-spec 'and
		connection-line-pattern-stub-spec) 
	       (1 2 4) fix-stub-info)

    ;; This is getting unwieldy.
    (stub-info (stub-info-without-style connection-arrows-stub-spec) 
	       (1 nil nil 2) fix-stub-info)
    (stub-info (stub-info-without-style connection-style-stub-spec 'and
		connection-arrows-stub-spec) 
	       (1 2 nil 4) fix-stub-info)
    (stub-info (stub-info-without-style connection-line-pattern-stub-spec 'and
		connection-arrows-stub-spec)
	       (1 nil 2 4) fix-stub-info)
    (stub-info (stub-info-without-style connection-style-stub-spec 'and
		connection-line-pattern-stub-spec 'and
		connection-arrows-stub-spec) 
	       (1 2 4 6) fix-stub-info)

    (stub-info-without-style
      (a-or-an connection-class port-name 'located 'at edge integer)
      (3 2 nil 6 7))
    (stub-info-without-style
      (a-or-an connection-class 'located 'at edge integer)
      (nil 2 nil 5 6))
    
    ;; "a-or-an" in the following two rules used to be 'an, but that was too
    ;; cute; when users selected "an" they would get a subset of the grammar
    ;; they would have gotten if they had selected "a", since the above rules
    ;; contribute additional grammar that can begin with "a". (MHD 1/11/91)
    (stub-info-without-style
      (a-or-an direction connection-class port-name 'located 'at edge integer)
      (4 3 2 7 8))
    (stub-info-without-style
      (a-or-an direction connection-class 'located 'at edge integer)
      (nil 3 2 6 7))
    
    (connection-style-stub-spec
      ('with 'style connection-style) 3 fix-connection-style-stub-spec)

    (connection-line-pattern-stub-spec
      ('with 'line-pattern connection-line-pattern) 3 fix-connection-line-pattern-stub-spec)

    (connection-arrows-stub-spec
      ('with 'connection-arrows connection-arrows) 3 fix-connection-arrows-stub-spec)
    
    (port-name unreserved-symbol)
    
    (connection-class unreserved-symbol)
    
    (direction 'input)
    (direction 'output)
    (direction? direction)
    (direction? 'none)
    
    (edge 'top)
    (edge 'bottom)
    (edge 'right)
    (edge 'left)
    
    ;; grammar for connection style
    (connection-instance-style connection-style)))


;;; A `stub-info' is a list of the form:
;;;  (port-name-or-names class direction side position style? line-pattern? arrows?)

(def-concept stub-info)

(defun fix-stub-info (form)
  (nconc (copy-list-using-phrase-conses (car form))
	 (copy-list-using-phrase-conses (cdr form))))

(defun fix-connection-line-pattern-stub-spec (line-pattern)
  (if (eq line-pattern 'solid) nil line-pattern))

(defun fix-connection-arrows-stub-spec (connection-arrows)
  (if (eq connection-arrows 'default) nil connection-arrows))

(defun fix-connection-style-stub-spec (style)
  (if (eq style 'orthogonal) nil style))


(define-category-evaluator-interface (connection-instance-style
				       :access read-write)
    (member orthogonal diagonal)
  ((set-form (evaluation-value))
   (evaluation-symbol-symbol evaluation-value))
  ((get-form (slot-value))
   (make-evaluation-symbol slot-value)))

(def-slot-value-writer connection-instance-style (connection-instance-style)
  (twrite connection-instance-style))



(def-slot-value-writer cross-section-pattern (cross-section-pattern)
  (cond
    ((null cross-section-pattern)
     (tformat "inherited"))
    (t
     (let ((cross-section-regions
	     (get-cross-section-regions cross-section-pattern))
	   (cross-section-stripes
	     (get-cross-section-stripes cross-section-pattern)))
       (if cross-section-regions
	   (write-region-specification-list cross-section-regions))
       (if (atom (car cross-section-stripes))	; in old kbs?
	   (write-cross-section-component cross-section-stripes)
	   (loop as (cross-section-component . more?)
		    on cross-section-stripes
		 do (write-cross-section-component cross-section-component)
		    (if more? (tformat ", "))))))))


(defun write-cross-section-component (cross-section-component)
  (tformat
    "~(~a ~a~)" (cdr cross-section-component) (car cross-section-component)))



(def-slot-value-writer stub-length (stub-length)
  (if (null stub-length)
      (tformat "inherited")
      (write-number?-from-slot stub-length nil)))

(def-slot-value-compiler stub-length (parse-result)
  (if (eq parse-result 'inherited)	
      nil				
      parse-result))




;;; The slot value compiler for cross-section-pattern ...

(def-slot-value-compiler cross-section-pattern (parse-result definition)
  (declare (use-for-default-overrides))
  (cond
    ((eq parse-result 'inherited)
     nil)
    (t
     (when (integerp parse-result)
       (setq parse-result (phrase-cons 'foreground parse-result)))
     (let* ((compiled-cross-section-pattern
	      (if (and (consp parse-result) (eq (car parse-result) 'copy))
		  (let ((superior-definition? nil))
		    ;; jv, 2/2/99, 5/11/99; rh, 7/3/00
		    (if (and (of-class-p definition 'definition)
			     (loop for superior?
				       in (direct-superiors-of-defined-class definition)
				   do (setq superior-definition? (class-definition superior?))
				   when (and (framep superior-definition?)
					     (connection-definition-p superior-definition?))
				     return t
				     finally (return nil)))
			(cross-section-pattern-for-connection superior-definition?)
			;; (ghw 2/15/96)
			(slot-value-list (slot-value-cons 'foreground 1))))		  
		  (fix-up-cross-section-pattern parse-result)))
	    (cross-section-regions
	      (get-cross-section-regions compiled-cross-section-pattern))
	    (cross-section-stripes
	      (get-cross-section-stripes compiled-cross-section-pattern))
	    (bad-region-or-color-or-metacolor?
	      (loop for (region-or-color . nil)
			in cross-section-stripes  
		    thereis
		    (if (and (not (color-or-metacolor-p region-or-color))
			     (or (null cross-section-regions)
				 (null (assq region-or-color cross-section-regions))))
			region-or-color))))
       (cond
	 (bad-region-or-color-or-metacolor?
	  (values
	    bad-phrase
	    (make-bad-region-text-string
	      bad-region-or-color-or-metacolor?)))
	 (t compiled-cross-section-pattern))))))




(defun fix-up-cross-section-pattern (cross-section-pattern?)
  (cond ((null cross-section-pattern?) nil)
	((eq cross-section-pattern? 'inherited) nil)
	((eq (car cross-section-pattern?) '\,)
	 (cdr cross-section-pattern?))
	((atom (car cross-section-pattern?))
	 (phrase-cons cross-section-pattern? nil))
	((eq (car (car cross-section-pattern?)) 'polychrome)	; keep as a region
	 (phrase-cons						;   specification?
	   (fix-up-cross-section-pattern
	     (cdr (car cross-section-pattern?)))
	   (fix-up-cross-section-pattern
	     (cdr cross-section-pattern?))))
	(t cross-section-pattern?)))



;;;; Connection Line Patterns



;;; A `connection-line-pattern', as output by the parser and stored in the slot,
;;; is either:
;;;    NIL       meaning solid
;;;    a symbol, meaning the stock dash pattern for that symbol
;;;    a list of symbols, meaning the concatenation of their dash patterns
;;;    an even length list of integers, meaning a sequence of on, off lengths.
;;;    a list whose car is :absolute, followed by the above.

(def-concept connection-line-pattern)




;;; Typical phrases:
;;;  "solid"
;;;  "dash, dot, dot"
;;;  "long dash, short dash"
;;;  "fine dot"
;;;  "coarse dot"
;;;  "5 on, 5 off"
;;;  "5 on, 5 off, not scaled by line width"

(def-grammar-category connection-line-pattern ()
  ('solid nil)
  (connection-line-pattern-dots)
  (connection-line-pattern-on-offs)
  ((connection-line-pattern-on-offs '\, 'not 'scaled 'by 'line 'width) (:absolute . 1)))

(def-grammar-category connection-line-pattern-dots ()
  (connection-line-pattern-dot (1))
  ((connection-line-pattern-dot '\, connection-line-pattern-dots) (1 . 3)))

(def-grammar-category connection-line-pattern-dot ()
  ('dash)
  ('dot)
  (('long 'dash)  long-dash)
  (('short 'dash) short-dash)
  (('coarse 'dot) coarse-dot)
  (('fine 'dot)   fine-dot))

(def-grammar-category connection-line-pattern-on-offs ()
  (connection-line-pattern-on-off)
  ((connection-line-pattern-on-off '\, connection-line-pattern-on-offs) (1 . 3) flatten-phrase-tree))

(def-grammar-category connection-line-pattern-on-off ()
  ((integer 'on '\, integer 'off) (1 4)))


(defun flatten-phrase-tree (tree)
  (cond ((null tree) nil)
	((atom tree) (phrase-list tree))
	((consp tree)
	 (nconc (flatten-phrase-tree (car tree))
		(flatten-phrase-tree (cdr tree))))))


;;; The function `lookup-stock-line-pattern-element' defines the meaning of the
;;; various elements in a line pattern, as produced by the grammar.

(defun lookup-stock-line-pattern-element (symbol)
  (case symbol
    (dash '(5 2))
    (dot '(1 2))
    (long-dash '(7 3))
    (short-dash '(3 1))
    (coarse-dot '(1 5))
    (fine-dot '(1 1))))

(defun-simple twrite-line-pattern-element (element)
  (case element
    (long-dash (twrite-string "long dash"))
    (short-dash (twrite-string "short dash"))
    (coarse-dot (twrite-string "coarse dot"))
    (fine-dot (twrite-string "fine dot"))
    (t (twrite element))))


(defun connection-line-pattern-dashes (connection-line-pattern)
  (cond ((null connection-line-pattern)
	 nil)
	((atom connection-line-pattern)
	 (lookup-stock-line-pattern-element connection-line-pattern))
	((eq (car connection-line-pattern) ':absolute)
	 (cdr connection-line-pattern))
	(t
	 connection-line-pattern)))


;;; The function `connection-line-pattern-explicit-p' is true if user specified
;;; an explicit list of on, off lengths.

(defun connection-line-pattern-explicit-p (connection-line-pattern)
  (and (consp connection-line-pattern)
       (if (eq (car connection-line-pattern) ':absolute)
	   (fixnump (cadr connection-line-pattern))
	   (fixnump (car connection-line-pattern)))))

(defun connection-line-pattern-absolute-p (connection-line-pattern)
  (and (consp connection-line-pattern)
       (eq (car connection-line-pattern) ':absolute)))


(defun valid-dash-length (length)
  (and (>f length 0)
       (<=f length maximum-connection-dash-length)))

(defun valid-dash-symbol (symbol)
  (memq symbol (cddr stock-line-pattern-type)))

(defun valid-dash-element (element)
  (cond ((fixnump element)
	 (valid-dash-length element))
	((symbolp element)
	 (valid-dash-symbol element))
	(t
	 nil)))


;;; The slot-value-compiler `connection-line-pattern' compiles the parse result
;;; into either a symbol (as an optimization) or the parse-result, after
;;; checking it for validity.

(def-slot-value-compiler connection-line-pattern (parse-result)
  (cond ((or (null parse-result)
	     (equal parse-result '(solid))) ; Default value
	 nil)
	((atom parse-result)
	 parse-result)
	((null (cdr parse-result))	; Be thrifty
	 (car parse-result))
	((>f (length (connection-line-pattern-dashes parse-result))
	     maximum-connection-dash-count)
	 (values bad-phrase
		 (tformat-text-string "At most ~a line pattern elements are allowed."
				      maximum-connection-dash-count)))
	((loop for element in (connection-line-pattern-dashes parse-result)
	       thereis (and (numberp element)
			    (not (valid-dash-length element))))
	 (values
	   bad-phrase
	   (tformat-text-string
	     "Each length must be a positive integer less than ~a."
	     (1+f maximum-connection-dash-length))))
	(t
	 parse-result)))


(def-slot-value-writer connection-line-pattern (line-pattern)
  (cond ((null line-pattern)
	 (twrite-string "solid"))
	((atom line-pattern)
	 (twrite-line-pattern-element line-pattern))
	(t
	 (let ((dashes (connection-line-pattern-dashes line-pattern)))
	   (cond ((numberp (first dashes))
		  (loop for (on off . more) on dashes by 'cddr
			doing
		    (tformat "~d on, ~d off" on off)
		    (when more
		      (twrite-string ", "))))
		 (t
		  (twrite-list dashes :separator ", " :conjoiner ", "
			       :element-writer #'twrite-line-pattern-element)))
	   (when (connection-line-pattern-absolute-p line-pattern)
	     (twrite-string ", not scaled by line width"))))))


(def-slot-putter line-pattern (connection-frame value initializing?)
  (setf (line-pattern connection-frame) value)
  (unless initializing?
    (let* ((connection
	     (connection-for-this-connection-frame connection-frame))
	   (workspace?
	     (workspace-of-connection? connection)))
      (update-connection-images t workspace? connection)
      (change-connection-attribute connection 'line-pattern (copy-for-slot-value value))

      #+ignore				; Copied from connection-style slot-putter
      (when (and g2-has-v5-mode-windows-p
		 (not ws-protocol-handle-moves-from-edge-change-p))
	(send-ws-representations-item-change-macro
	  connection-for-connection-frame
	  (allocate-evaluation-structure-inline
	    'attribute-name 'line-pattern 'new-value value))
	;; Hasn't moved, is this call needed?
	(send-ws-representations-connection-moved connection-for-connection-frame))
      
      (update-connection-images nil workspace? connection)))
  value)


(define-category-evaluator-interface (connection-line-pattern :access read-write)
    (or (no-item)
	#.stock-line-pattern-type
	(sequence symbol 1)
	(sequence integer 1)
	(structure line-pattern
		   ((pattern (sequence integer 1))
		    (not-scaled-by-line-width truth-value))))
  ((get-form (line-pattern))
   (cond ((null line-pattern)
	  'solid)
	 ((atom line-pattern)
	  line-pattern)
	 ((null (cdr line-pattern))
	  (car line-pattern))
	 ((connection-line-pattern-absolute-p line-pattern)
	  (allocate-evaluation-structure
	    (eval-list 'pattern
		       (allocate-evaluation-sequence
			 (copy-list-using-eval-conses (cdr line-pattern)))
		       'not-scaled-by-line-width evaluation-true-value)))
	 (t
	  (with-list-to-evaluation-sequence-mapping
	      (line-pattern elt)
	    elt))))
  ((set-form (evaluation-value))
   ;; Maybe rewrite using evaluation-etypecase -dkuznick, 6/19/02
   (cond ((eq evaluation-value 'solid)
	  nil)
	 ((atom evaluation-value)
	  evaluation-value)
	 ((evaluation-structure-p evaluation-value)
	  (with-structure (evaluation-value line-pattern)
	    (cond ((not (evaluation-sequence-p pattern))
		   (values bad-phrase
			   (tformat-text-string "A line-pattern specified with a structure must contain a pattern attribute which must be a sequence.")))
		  ((oddp (evaluation-sequence-length pattern))
		   (values bad-phrase
			   (tformat-text-string "A pattern in a line-pattern structure must contain an even number of elements")))
		  ((not (evaluation-truth-value-p not-scaled-by-line-width))
		   (values bad-phrase
			   (tformat-text-string "A line-pattern specified with a structure must contain a not-scaled-by-line-width attribute which must be a truth-value.")))
		  (t
		   (let ((phrase (with-evaluation-sequence-to-phrase-list-mapping
				     (pattern elt)
				   elt)))
		     (if (evaluation-truth-value-is-true-p not-scaled-by-line-width)
			 (phrase-cons ':absolute phrase)
			 phrase))))))
	 ((not (evaluation-sequence-p evaluation-value))
	  nil)
	 ((and (numberp (evaluation-sequence-ref evaluation-value 0))
	       (oddp (evaluation-sequence-length evaluation-value)))
	  (values bad-phrase
		  (tformat-text-string "A numeric line-pattern must have even length.")))
	 ((loop for element being each evaluation-sequence-element of evaluation-value
		thereis (not (valid-dash-element element)))
	  (values bad-phrase
		  (tformat-text-string "The line-pattern contains invalid elements.")))
	 (t
	  (with-evaluation-sequence-to-phrase-list-mapping
	      (evaluation-value elt)
	    elt)))))


;;;; Connection Arrows


;;; `Connection arrows' are decorations glued to the input end, output end, or
;;; line segments of a connection. They rotate with the connection's orientation
;;; and scale with the connection's width.

;;; The grammar is intended to be a sequence of specifications for arrows at
;;; the input, output, and line-segments of the connection.

;;; The currently implemented grammar:
;;;    DEFAULT                   -- Classic behavior (fins along the length, if directed)
;;;    NONE                      -- No arrows anywhere, ever.
;;;    <arrow> | <arrow>, <arrows>
;;;    <arrow> = <shape> |                -- Basic shape
;;;              <adjectives> <shape> |   -- Modify the geometry of shape.
;;;              <shape> <placement>  |   -- Which end of connection to attach to
;;;              <adjectives> <shape> <placement>
;;;    <adjectives> = (<adjective> | <adverb> <adjective>) <adjectives>
;;;
;;; Shapes: ARROW TRIANGLE DIAMOND CIRCLE
;;; Adjectives: FILLED, OPEN, WIDE, NARROW, LARGE, SMALL, THIN, THICK
;;; Adverbs: VERY
;;; Places: OUTPUT, INPUT, BOTH ENDS, #+tbd ALONG LENGTH

(def-grammar-category connection-arrows ()
  ('default nil)			; Means "fins along length, if directed"
  ('none none)				; No arrows of any kind, ever.
  (connection-arrow-list))

(def-grammar-category connection-arrow-list ()
  (connection-arrow (1))
  ((connection-arrow '\, connection-arrow-list) (1 . 3)))

(def-grammar-category connection-arrow ()
  (connection-arrow-shape 1)
  ((connection-arrow-shape connection-arrow-placement) (2 1))
  ((shape-adjectives connection-arrow-shape) (default 2 . 1))
  ((shape-adjectives connection-arrow-shape connection-arrow-placement) (3 2 . 1)))

(def-grammar-category connection-arrow-shape ()
  . #.basic-arrow-shapes)

(def-grammar-category connection-arrow-placement ()
  (('at 'the 'output 'end) output)
  (('at 'the 'input 'end)  input)
  (('at 'both 'ends)       both)
  #+tbd (('along 'the 'length)   along))

(def-grammar-category geometric-adjective ()
  small large thick thin wide narrow)

(defun antonym-of (adjective)
  (case adjective
    (narrow 'wide)
    (wide 'narrow)
    (small 'large)
    (large 'small)
    (thin 'thick)
    (thick 'thin)
    (filled 'open)
    (open 'filled)
    (t (dwarn "Teach antonym-of about ~s" adjective))))

;; TODO: color = color name or stripe name
(def-grammar-category shape-adjective ()
  filled
  open
  (geometric-adjective)
  (('very geometric-adjective) (very 2)))

;; Just a space separator is simpler, I hope, for users, and still unambiguous.
(def-grammar-category shape-adjectives ()
  (shape-adjective (1) flatten-phrase-tree)
  ((shape-adjective shape-adjectives) (1 . 2) flatten-phrase-tree))


;;; The slot-value-compiler `connection-arrows' compiles the parse result into
;;; either a symbol (as an optimization) or the parse-result, after checking it
;;; for validity.

(def-slot-value-compiler connection-arrows (parse-result)
  (cond ((atom parse-result)
	 parse-result)
	((and (null (cdr parse-result))	     ; Optimize to single symbol.
	      (atom (car parse-result)))
	 (car parse-result))
	(t
	 (loop for arrow in parse-result
	       as (placement shape . adjectives) = (and (consp arrow) arrow)
	       as ellipse? = (and (eq shape 'circle)
				  (or (memq 'narrow adjectives)
				      (memq 'wide adjectives)))
	       if ellipse?
		 return (values bad-phrase
				(tformat-text-string "Wide or narrow used with circle."))
	       as duplicate? = (loop for (adj . rest) on adjectives
				     when (and (neq adj 'very)
					       (memq adj rest))
				       return adj)
	       if duplicate?
		 return (values bad-phrase
				(tformat-text-string "The modifier ~a is duplicated." duplicate?))

	       as conflict? = (loop for (adj . rest) on adjectives
				    when (and (neq adj 'very)
					      (memq (antonym-of adj) rest))
				      return adj)
	       if conflict?
		 return (values bad-phrase
				(tformat-text-string "The modifiers ~a and ~a conflict."
						     conflict? (antonym-of conflict?)))
	       finally
		 (return parse-result)))))

(def-slot-value-writer connection-arrows (arrows)
  (cond ((null arrows)
	 (twrite-string "default"))
	((eq arrows 'none)
	 (twrite-string "none"))
	((atom arrows)
	 (twrite-symbol arrows))
	(t
	 (loop for (arrow . more) on arrows doing
	   (twrite-connection-arrow arrow)
	   (when more
	     (twrite-string ", "))))))

(defun twrite-connection-arrow (arrow)
  (if (atom arrow)
      (twrite-symbol arrow)
      (gensym-dstruct-bind ((placement shape . adjectives) arrow)
	(when adjectives
	  (write-symbol-list adjectives "")
	  (twrite-string " "))
	(twrite-symbol shape)
	(twrite (case placement
		  (output " at the output end")
		  (input " at the input end")
		  (both " at both ends")
		  #+tbd (along " along the length")
		  (default ""))))))

(def-slot-putter connection-arrows (connection-frame value initializing?)
  (setf (connection-arrows connection-frame) value)
  (unless initializing?
    (let* ((connection
	     (connection-for-this-connection-frame connection-frame))
	   (workspace?
	     (workspace-of-connection? connection)))
      (update-connection-images t workspace? connection)
      (change-connection-attribute connection 'connection-arrows (copy-for-slot-value value))
      (update-connection-images nil workspace? connection)))
  value)
  

(defparameter connection-arrow-permitted-scales '(0.25 0.5 1.0 2.0 4.0))

(define-category-evaluator-interface (connection-arrows :access read-write)
    (or (no-item)
	(member default none . #.basic-arrow-shapes)
	(sequence
	  (structure arrow
		     ((shape (member . #.basic-arrow-shapes))
		      (filled truth-value)
		      (scale float)
		      (aspect-ratio float)
		      (line-weight float)
		      (placement (member default output input both #+tbd along)))
		     (or shape))))	; Required slot.
  ((get-form (spec))
   (cond ((null spec)
	  'default)
	 ((atom spec)
	  spec)
	 (t
	  (allocate-evaluation-sequence
	    (loop for arrow in spec
		  collect (compute-connection-arrows-structure arrow) using eval-cons)))))
  ((set-form (evaluation-value))
   (cond ((null evaluation-value)	; "the symbol none" gets turned into NIL!
	  'none)
	 ((eq evaluation-value 'default)
	  nil)
	 ((atom evaluation-value)
	  evaluation-value)
	 ((evaluation-sequence-p evaluation-value)
	  (loop for struct being each evaluation-sequence-element of evaluation-value
		as arrow? = (compute-connection-arrows-spec struct)
		if (text-string-p arrow?)
		  return (values bad-phrase arrow?)
		if arrow?
		  collect it using phrase-cons)))))

(defun compute-connection-arrows-structure (arrow)
  (with-temporary-gensym-float-creation connection-arrows
    (multiple-value-bind (shape placement thick width height filled)
	(decode-arrow-spec-1 arrow)
      (allocate-evaluation-structure
	(eval-list 'shape shape
		   'placement placement
		   'filled (make-evaluation-boolean-value filled)
		   'scale (allocate-managed-float (expt2 width))
		   'aspect-ratio (allocate-managed-float
				   (/e (expt2 height) (expt2 width)))
		   'line-weight (allocate-managed-float (expt2 thick)))))))

(defun compute-connection-arrows-spec (struct)
  (with-temporary-gensym-float-creation connection-arrows
    (let* ((shape (evaluation-structure-slot struct 'shape))
	   (placement (evaluation-structure-slot struct 'placement 'default))
	   (filled (evaluation-structure-slot struct 'filled))
	   (scale? (connection-arrows-scale-index
		     (evaluation-structure-slot struct 'scale 1.0)))
	   (aspect-ratio? (connection-arrows-scale-index
			    (evaluation-structure-slot struct 'aspect-ratio 1.0)))
	   (line-weight? (connection-arrows-scale-index
			   (evaluation-structure-slot struct 'line-weight 1.0)))
	   (offending-slot?
	     (cond ((null scale?) 'scale)
		   ((null aspect-ratio?) 'aspect-ratio)
		   ((null line-weight?) 'line-weight))))
      (cond (offending-slot?
	     (twith-output-to-text-string
	       (tformat "The ~a must be one of " offending-slot?)
	       (twrite-list connection-arrow-permitted-scales)))
	    ((and (memq placement '(output default))
		  (null filled)
		  (=f scale? aspect-ratio? line-weight? 0))
	     shape)
	    ((null shape)		; This should not happen. Just insurance.
	     nil)
	    (t
	     (phrase-list*
	       placement shape
	       (nconc
		 (if (evaluation-boolean-is-true-p filled)
		     (phrase-list 'filled))
		 (connection-arrows-adjective-phrase 'large scale?)
		 (connection-arrows-adjective-phrase 'wide aspect-ratio?)
		 (connection-arrows-adjective-phrase 'thick line-weight?))))))))

(defun connection-arrows-adjective-phrase (adjective index)
  (assert-that-within-temporary-float-scope)
  (case index
    (-2 (phrase-list 'very (antonym-of adjective)))
    (-1 (phrase-list (antonym-of adjective)))
    (0 nil)
    (1 (phrase-list adjective))
    (2 (phrase-list 'very adjective))))

(defun connection-arrows-scale-index (scale)
  (let ((pos? (position-in-float-list
		scale connection-arrow-permitted-scales 0.01)))
    (when pos?
      (-f pos? 2))))

(defun expt2 (n)
  (assert-that-within-temporary-float-scope)
  (cond ((=f n 0) 1.0)
	((>f n 0) (coerce-to-gensym-float (ashf 1 n)))
	(t (/e (coerce-to-gensym-float (ashf 1 (-f n)))))))

(defun position-in-float-list (float list eps)
  (assert-that-within-temporary-float-scope)
  (loop with f = (if (managed-float-p float)
		     (managed-float-value float)
		     float)
	for v in list
	as n from 0
	when (and (gensym-float-p v)
		  (<e (-e v eps) f (+e v eps)))
	  return n))



;;;; Defaulted Attributes




;;; A `defaulted-attribute' is a system slot that can have a value defaulted at
;;; the class level within a definition, e.g.  validity-interval.  This category
;;; is used in the change slot of a definition to permit the changing of a
;;; system slot to its default value.

(def-semi-open-category defaulted-attribute-name
  data-type data-server validity-interval 
  default-update-interval history-keeping-spec initial-value
  allow-duplicate-elements list-type simulation-details
  g2-array-element-type g2-array-length g2-array-initial-values)





;;; If more grammar is added below for new slots, be sure to add them to
;;; defaulted-attribute-name above.

;;; This facility does not extend to supply-simulation-subtable or options at
;;; present.  These cannot be treated as slots.

(add-grammar-rules

  '((default-overrides-for-connection-definitions 'none)
    (default-overrides-for-connection-definitions
	list-of-default-overrides-for-connection-definitions)
    (list-of-default-overrides-for-connection-definitions
     override-for-connection-definition)
    (list-of-default-overrides-for-connection-definitions
     (override-for-connection-definition
      '\; list-of-default-overrides-for-connection-definitions)
     (2 1 3) simplify-associative-operation)

    ;; initializations of user-defined slots for connection definitions
    (override-for-connection-definition
     attribute-name (1 nil user-defined)
     fix-default-override-on-user-defined-slot)
    (override-for-connection-definition
     (class '\:\: attribute-name) ((class-qualified-name 1 3) nil user-defined)
     fix-default-override-on-user-defined-slot)
    (override-for-connection-definition
     (class '\:\: attribute-name 'initially
      'is standard-or-class-qualified-symbol)
     ((class-qualified-name 1 3) 6 user-defined)
     fix-default-override-on-user-defined-slot)
    (override-for-connection-definition
     (attribute-name 'initially 'is attribute-constant)
     (1 4 user-defined)
     fix-default-override-on-user-defined-slot)
    (override-for-connection-definition
     (class '\:\: attribute-name 'initially 'is attribute-constant)
     ((class-qualified-name 1 3) 6 user-defined)
     fix-default-override-on-user-defined-slot)

    (override-for-connection-definition
     (attribute-name 'initially 'is 'given 'by a-or-an
      variable-or-parameter-class)
     (1 (:funcall instantiate-variable 7) user-defined)
     fix-default-override-on-user-defined-slot)
    (override-for-connection-definition
     (class '\:\: attribute-name 'initially 'is 'given 'by a-or-an
      variable-or-parameter-class)
     ((class-qualified-name 1 3) (:funcall instantiate-variable 9)
      user-defined) fix-default-override-on-user-defined-slot)
    (override-for-connection-definition
     (attribute-name 'initially 'is 'an 'instance 'of a-or-an object-class)
     ( 1 (:funcall instantiate-object-in-attribute 8) user-defined)
     fix-default-override-on-user-defined-slot)
    (override-for-connection-definition
     (class '\:\: attribute-name 'initially 'is 'an 'instance 'of a-or-an object-class)
     ((class-qualified-name 1 3) (:funcall instantiate-object-in-attribute 10)
      user-defined) fix-default-override-on-user-defined-slot)))


(add-grammar-rules
  '((default-overrides-for-message-definitions 'none)
    (default-overrides-for-message-definitions
	list-of-default-overrides-for-message-definitions)
    (list-of-default-overrides-for-message-definitions
     override-for-message-definition)
    (list-of-default-overrides-for-message-definitions
     (override-for-message-definition
      '\; list-of-default-overrides-for-message-definitions)
     (2 1 3) simplify-associative-operation)

    ;; initializations of user-defined slots for message definitions
    (override-for-message-definition
     attribute-name (1 nil user-defined)
     fix-default-override-on-user-defined-slot)
    (override-for-message-definition
     (class '\:\: attribute-name) ((class-qualified-name 1 3) nil user-defined)
     fix-default-override-on-user-defined-slot)
    (override-for-message-definition
     (attribute-name 'initially 'is attribute-constant)
     (1 4 user-defined)
     fix-default-override-on-user-defined-slot)
    (override-for-message-definition
     (class '\:\: attribute-name 'initially 'is attribute-constant)
     ((class-qualified-name 1 3) 6 user-defined)
     fix-default-override-on-user-defined-slot)

    (override-for-message-definition
     (attribute-name 'initially 'is 'given 'by a-or-an
      variable-or-parameter-class)
     (1 (:funcall instantiate-variable 7) user-defined)
     fix-default-override-on-user-defined-slot)
    (override-for-message-definition
     (class '\:\: attribute-name 'initially 'is 'given 'by a-or-an
      variable-or-parameter-class)
     ((class-qualified-name 1 3) (:funcall instantiate-variable 9)
      user-defined) fix-default-override-on-user-defined-slot)
    (override-for-message-definition
     (attribute-name 'initially 'is 'an 'instance 'of a-or-an object-class)
     ( 1 (:funcall instantiate-object-in-attribute 8) user-defined)
     fix-default-override-on-user-defined-slot)
    (override-for-message-definition
     (class '\:\: attribute-name 'initially 'is 'an 'instance 'of a-or-an object-class)
     ((class-qualified-name 1 3) (:funcall instantiate-object-in-attribute 10)
      user-defined) fix-default-override-on-user-defined-slot)))

(add-grammar-rules
  '((default-overrides-for-object-definitions 'none)
    (default-overrides-for-object-definitions
	list-of-default-overrides-for-object-definitions)
    (list-of-default-overrides-for-object-definitions
     override-for-object-definition)
    (list-of-default-overrides-for-object-definitions
     (override-for-object-definition
      '\; list-of-default-overrides-for-object-definitions)
     (2 1 3) simplify-associative-operation)

    ;; initializations of user-defined slots for object definitions
    (override-for-object-definition
     attribute-name (1 nil user-defined)
     fix-default-override-on-user-defined-slot)
    (override-for-object-definition
     (class '\:\: attribute-name) ((class-qualified-name 1 3) nil user-defined)
     fix-default-override-on-user-defined-slot)
    (override-for-object-definition
     (attribute-name 'initially 'is attribute-constant)
     (1 4 user-defined)
     fix-default-override-on-user-defined-slot)
    (override-for-object-definition
     (class '\:\: attribute-name 'initially 'is attribute-constant)
     ((class-qualified-name 1 3) 6 user-defined)
     fix-default-override-on-user-defined-slot)

    
    (override-for-object-definition
     (attribute-name 'initially 'is 'given 'by a-or-an
      variable-or-parameter-class)
     (1 (:funcall instantiate-variable 7) user-defined)
     fix-default-override-on-user-defined-slot)
    (override-for-object-definition
     (class '\:\: attribute-name 'initially 'is 'given 'by a-or-an
      variable-or-parameter-class)
     ((class-qualified-name 1 3) (:funcall instantiate-variable 9)
      user-defined) fix-default-override-on-user-defined-slot)
    (override-for-object-definition
     (attribute-name 'initially 'is 'an 'instance 'of a-or-an object-class)
     ( 1 (:funcall instantiate-object-in-attribute 8) user-defined)
     fix-default-override-on-user-defined-slot)
    (override-for-object-definition
     (class '\:\: attribute-name 'initially 'is 'an 'instance 'of a-or-an object-class)
     ((class-qualified-name 1 3) (:funcall instantiate-object-in-attribute 10)
      user-defined) fix-default-override-on-user-defined-slot)

    (initial-sensor-value? 'none)
    (initial-sensor-value? truth-value)    
    (initial-sensor-value? quantity)
    (initial-sensor-value? symbol)
    (initial-sensor-value? whole-string)))

(defparameter system-class-overrides-for-object-definition
  (optimize-constant
   '((override-for-object-definition
      ('array-is-permanent '\: yes-or-no)
      (array-is-permanent 3 g2-array))
     (override-for-object-definition
      ('list-is-permanent '\: yes-or-no)
      (list-is-permanent 3 g2-list))

     (override-for-object-definition
      ('data 'type 'for 'sensor '\: data-type)
      (data-type 6 sensor))
     (override-for-object-definition
      ('data-type 'for 'sensor '\: data-type)
      (data-type 5 sensor))
     
     (override-for-object-definition
      ('data 'type 'for 'quantitative-variable '\: quantitative-data-type)
      (data-type 6 quantitative-variable))
     (override-for-object-definition
      ('data-type 'for 'quantitative-variable '\: quantitative-data-type)
      (data-type 5 quantitative-variable))

     (override-for-object-definition
      ('data 'type 'for 'quantitative-parameter '\: quantitative-data-type)
      (data-type 6 quantitative-parameter))
     (override-for-object-definition
      ('data-type 'for 'quantitative-parameter '\: quantitative-data-type)
      (data-type 5 quantitative-parameter))

     (override-for-object-definition
      ('validity 'interval '\: validity-interval)
      (validity-interval 4))
     (override-for-object-definition
      ('validity-interval '\: validity-interval) 
      (validity-interval 3))
     
     (override-for-object-definition
      ('supply 'simulation 'subtable)
      (simulation-details (:funcall make-simulation-subtable-and-install)))
     (override-for-object-definition
      ('supply-simulation-subtable '\: simulation-subtable-class)
      (simulation-details
       (:funcall make-simulation-subtable-with-specific-class-and-install 3)))
     
     (override-for-object-definition
      ('data 'server '\: data-server-map)
      (data-server-map 4))
     (override-for-object-definition
      ('data-server '\: data-server-map)
      (data-server-map 3))
     
     (override-for-object-definition
      ('default 'update 'interval '\: positive-quantity-interval?)
      (default-update-interval 5) second-none)
     (override-for-object-definition
      ('default-update-interval '\: positive-quantity-interval?)
      (default-update-interval 3) second-none)
     
     (override-for-object-definition
      ('history 'keeping 'spec '\: history-specification)
      (history-keeping-spec 5))
     (override-for-object-definition
      ('history-keeping-spec 'for 'variable-or-parameter '\: history-specification)
      (history-keeping-spec 5))
     
     (override-for-object-definition
      ('history 'keeping 'spec 'for 'simulation 'subtable '\: history-specification)
      (history-keeping-spec-for-simulation-subtables 8))
     (override-for-object-definition
      ('history-keeping-spec 'for 'simulation-subtable '\: history-specification)
      (history-keeping-spec-for-simulation-subtables 5))
     
     (override-for-object-definition
      ('options 'for 'variable '\, variable-frame-flags)
      (frame-flags 5 variable))
     (override-for-object-definition
      ('options-for-variable '\: variable-frame-flags)
      (frame-flags 3 variable))
     
     (override-for-object-definition
      ('options 'for 'parameter '\: parameter-frame-flags)
      (frame-flags 5 parameter))
     (override-for-object-definition
      ('options-for-parameter '\: parameter-frame-flags)
      (frame-flags 3 parameter))
     
     (override-for-object-definition
      ('initial 'value 'for 'logical-variable '\: truth-value?)
      (initial-value 6 logical-variable))
     (override-for-object-definition
      ('initial-value 'for 'logical-variable '\: truth-value?)
      (initial-value 5 logical-variable))
     
     (override-for-object-definition
      ('initial 'value 'for 'quantitative-variable '\: quantity?)
      (initial-value 6 quantitative-variable))
     (override-for-object-definition
      ('initial-value 'for 'quantitative-variable '\: quantity?)
      (initial-value 5 quantitative-variable))

     (override-for-object-definition
      ('initial 'value 'for 'float-variable '\: initial-value-float?)
      (initial-value 6 float-variable))
     (override-for-object-definition
      ('initial-value 'for 'float-variable '\: initial-value-float?)
      (initial-value 5 float-variable))

     (override-for-object-definition
      ('initial 'value 'for 'long-variable '\: initial-value-long?)
      (initial-value 6 long-variable))
     (override-for-object-definition
      ('initial-value 'for 'long-variable '\: initial-value-long?)
      (initial-value 5 long-variable))

     (override-for-object-definition
      ('initial 'value 'for 'integer-variable '\: initial-value-integer?)
      (initial-value 6 integer-variable))
     (override-for-object-definition
      ('initial-value 'for 'integer-variable '\: initial-value-integer?)
      (initial-value 5 integer-variable))
     
     (override-for-object-definition
      ('initial 'value 'for 'symbolic-variable '\: standard-or-class-qualified-symbol?)
      (initial-value 6 symbolic-variable))
     (override-for-object-definition
      ('initial-value 'for 'symbolic-variable '\: standard-or-class-qualified-symbol?)
      (initial-value 5 symbolic-variable))
     
     (override-for-object-definition
      ('initial 'value 'for 'text-variable '\: whole-string?)
      (initial-value 6 text-variable))
     (override-for-object-definition
      ('initial-value 'for 'text-variable '\: whole-string?)
      (initial-value 5 text-variable))

     (override-for-object-definition
      ('initial 'value 'for 'logical-parameter '\: truth-value)
      (initial-value 6 logical-parameter))
     (override-for-object-definition
      ('initial-value 'for 'logical-parameter '\: truth-value)
      (initial-value 5 logical-parameter))
     
     (override-for-object-definition
      ('initial 'value 'for 'quantitative-parameter '\: quantity)
      (initial-value 6 quantitative-parameter))
     (override-for-object-definition
      ('initial-value 'for 'quantitative-parameter '\: quantity)
      (initial-value 5 quantitative-parameter))
     
     (override-for-object-definition
      ('initial 'value 'for 'float-parameter '\: initial-value-float)
      (initial-value 6 float-parameter))
     (override-for-object-definition
      ('initial-value 'for 'float-parameter '\: initial-value-float)
      (initial-value 5 float-parameter))

     (override-for-object-definition
      ('initial 'value 'for 'long-parameter '\: initial-value-long)
      (initial-value 6 long-parameter))
     (override-for-object-definition
      ('initial-value 'for 'long-parameter '\: initial-value-long)
      (initial-value 5 long-parameter))

     (override-for-object-definition
      ('initial 'value 'for 'integer-parameter '\: initial-value-integer)
      (initial-value 6 integer-parameter))
     (override-for-object-definition
      ('initial-value 'for 'integer-parameter '\: initial-value-integer)
      (initial-value 5 integer-parameter))
     
     (override-for-object-definition
      ('initial 'value 'for 'symbolic-parameter '\: standard-or-class-qualified-symbol)
      (initial-value 6 symbolic-parameter))
     (override-for-object-definition
      ('initial-value 'for 'symbolic-parameter '\: standard-or-class-qualified-symbol)
      (initial-value 5 symbolic-parameter))
     
     (override-for-object-definition
      ('initial 'value 'for 'text-parameter '\: whole-string)
      (initial-value 6 text-parameter))
     (override-for-object-definition
      ('initial-value 'for 'text-parameter '\: whole-string)
      (initial-value 5 text-parameter))
     
     (override-for-object-definition
      ('initial 'value 'for 'sensor '\: initial-sensor-value?)
      (initial-value 6 sensor))
     (override-for-object-definition
      ('initial-value 'for 'sensor '\: initial-sensor-value?)
      (initial-value 5 sensor))

     (override-for-object-definition
      ('element 'type 'for 'item-list '\: class)
      (list-type 6 item-list))
     (override-for-object-definition
      ('element-type 'for 'item-list '\: class)
      (list-type 5 item-list))

     (override-for-object-definition
      ('allow 'duplicate 'elements 'for 'g2-list '\: yes-or-no)
      (insert-duplicate-elements? 7 g2-list))
     (override-for-object-definition
      ('allow-duplicate-elements-for-g2-list '\: yes-or-no)
      (insert-duplicate-elements? 3 g2-list))

     (override-for-object-definition
      ('element 'type 'for 'item-array '\: class)
      (g2-array-element-type 6 item-array))
     (override-for-object-definition
      ('element-type 'for 'item-array '\: class)
      (g2-array-element-type 5 item-array))

     (override-for-object-definition
      ('array-length 'for 'g2-array '\: g2-array-length)
      (g2-array-length 5 g2-array))

     (override-for-object-definition
      ('initial 'values 'for 'g2-array '\: list-of-item-and-datum-constants?)
      (g2-array-initial-values 6 g2-array))
     (override-for-object-definition
      ('initial-values 'for 'g2-array '\: list-of-item-and-datum-constants?)
      (g2-array-initial-values 5 g2-array))

     (override-for-object-definition
      ('initial 'values 'for 'value-array '\: list-of-datum-constants)
      (g2-array-initial-values 6 value-array))
     (override-for-object-definition
      ('initial-values 'for 'value-array '\: list-of-datum-constants)
      (g2-array-initial-values 5 value-array))

     (override-for-object-definition
      ('initial 'values 'for 'item-array '\: constant-designation-list?)
      (g2-array-initial-values 6 item-array))
     (override-for-object-definition
      ('initial-values 'for 'item-array '\: constant-designation-list?)
      (g2-array-initial-values 5 item-array))

     (override-for-object-definition
      ('initial 'values 'for 'quantity-array '\: quantity-list)
      (g2-array-initial-values 6 quantity-array))
     (override-for-object-definition
      ('initial-values 'for 'quantity-array '\: quantity-list)
      (g2-array-initial-values 5 quantity-array))
     
     (override-for-object-definition
      ('initial 'values 'for 'integer-array '\: integer-list)
      (g2-array-initial-values 6 integer-array))
     (override-for-object-definition
      ('initial-values 'for 'integer-array '\: integer-list)
      (g2-array-initial-values 5 integer-array))

     (override-for-object-definition
      ('initial 'values 'for 'float-array '\: float-list)
      (g2-array-initial-values 6 float-array))
     (override-for-object-definition
      ('initial-values 'for 'float-array '\: float-list)
      (g2-array-initial-values 5 float-array))
     
     (override-for-object-definition
      ('initial 'values 'for 'symbol-array '\: symbol-list)
      (g2-array-initial-values 6 symbol-array))
     (override-for-object-definition
      ('initial-values 'for 'symbol-array '\: symbol-list)
      (g2-array-initial-values 5 symbol-array))
     
     (override-for-object-definition
      ('initial 'values 'for 'text-array '\: whole-string-list)
      (g2-array-initial-values 6 text-array))
     (override-for-object-definition
      ('initial-values 'for 'text-array '\: whole-string-list)
      (g2-array-initial-values 5 text-array))
     
     (override-for-object-definition
      ('initial 'values 'for 'truth-value-array '\: truth-value-list)
      (g2-array-initial-values 6 truth-value-array))
     (override-for-object-definition
      ('initial-values 'for 'truth-value-array '\: truth-value-list)
      (g2-array-initial-values 5 truth-value-array)))))

(add-grammar-rules system-class-overrides-for-object-definition)



(add-grammar-rules
  '((default-overrides-for-class-definitions 'none)
    (default-overrides-for-class-definitions
	list-of-default-overrides-for-class-definitions)
    (list-of-default-overrides-for-class-definitions
     override-for-class-definition)
    (list-of-default-overrides-for-class-definitions
     (override-for-class-definition
      '\; list-of-default-overrides-for-class-definitions)
     (2 1 3) simplify-associative-operation);; initializations of user-defined slots for class definitions
    (override-for-class-definition
     attribute-name (1 nil user-defined)
     fix-default-override-on-user-defined-slot)
    (override-for-class-definition
     (class '\:\: attribute-name) ((class-qualified-name 1 3) nil user-defined)
     fix-default-override-on-user-defined-slot)
    
    (override-for-class-definition
     (attribute-name 'initially 'is attribute-constant)
     (1 4 user-defined)
     fix-default-override-on-user-defined-slot)
    (override-for-class-definition
     (class '\:\: attribute-name 'initially 'is attribute-constant)
     ((class-qualified-name 1 3) 6 user-defined)
     fix-default-override-on-user-defined-slot)

    (override-for-class-definition
     (attribute-name 'initially 'is 'given 'by a-or-an
      variable-or-parameter-class)
     (1 (:funcall instantiate-variable 7) user-defined)
     fix-default-override-on-user-defined-slot)
    (override-for-class-definition
     (class '\:\: attribute-name 'initially 'is 'given 'by a-or-an
      variable-or-parameter-class)
     ((class-qualified-name 1 3) (:funcall instantiate-variable 9)
      user-defined) fix-default-override-on-user-defined-slot)
    (override-for-class-definition
     (attribute-name 'initially 'is 'an 'instance 'of a-or-an object-class)
     ( 1 (:funcall instantiate-object-in-attribute 8) user-defined)
     fix-default-override-on-user-defined-slot)
    (override-for-class-definition
     (class '\:\: attribute-name 'initially 'is 'an 'instance
      'of a-or-an object-class)
     ((class-qualified-name 1 3)
      (:funcall instantiate-object-in-attribute 10) user-defined)
     fix-default-override-on-user-defined-slot)))

(defparameter system-class-overrides-for-class-definition
  (optimize-constant
   '((override-for-class-definition
      ('relation-is-permanent '\: yes-or-no)
      (relation-is-permanent 3 ((relation) ())))

     (override-for-class-definition
      ('array-is-permanent '\: yes-or-no)
      (array-is-permanent 3 ((g2-array) ())))

     (override-for-class-definition
      ('list-is-permanent '\: yes-or-no)
      (list-is-permanent 3 ((g2-list) ())))

     (override-for-class-definition
      ('instantiate '\: yes-or-no)
      (instantiate? 3 ((class-definition) ())))

     (override-for-class-definition
      ('include-in-menus '\: yes-or-no)
      (include-in-menus? 3 ((class-definition) ())))

     (override-for-class-definition
      ('element-type 'for 'item-list '\: class)
      (list-type 5 ((item-list) ())))

     (override-for-class-definition
      ('element-type 'for 'item-array '\: class)
      (g2-array-element-type 5 ((item-array) ())))

     (override-for-class-definition
      ('data-type 'for 'sensor '\: data-type)
      (data-type-of-variable-or-parameter 5 ((sensor) ())))
     
     (override-for-class-definition
      ('data-type 'for 'quantitative-variable '\: quantitative-data-type)
      (data-type-of-variable-or-parameter 5 ((quantitative-variable) ())))

     (override-for-class-definition
      ('data-type 'for 'quantitative-parameter '\: quantitative-data-type)
      (data-type-of-variable-or-parameter 5 ((quantitative-parameter) ())))
     
     (override-for-class-definition
      ('validity-interval '\: validity-interval)
      (validity-interval 3 ((variable) ())))
     
     (override-for-class-definition
      ('supply-simulation-subtable '\: simulation-subtable-class)
      (simulation-details
       (:funcall make-simulation-subtable-with-specific-class-and-install 3)
       ((variable) ())))
     
     (override-for-class-definition
      ('data-server '\: data-server-map)
      (data-server-map 3 ((variable) ())))

     (override-for-class-definition
      ('data-server-for-messages '\: symbol)
      (data-server-for-messages 3 ((gsi-message-service) ())))
     
     (override-for-class-definition
      ('default-update-interval '\: positive-quantity-interval?)
      (background-collection-interval? 3 ((variable) ())))
     
     (override-for-class-definition
      ('history-keeping-spec 'for 'variable-or-parameter '\: history-specification)
      (variable-or-parameter-history-specification?
       5
       ((variable-or-parameter) ())))

     (override-for-class-definition
      ('history-keeping-spec 'for 'simulation-subtable '\: history-specification)
      (history-specification-for-simulation-subtables? 5 ((variable) ())))

     (override-for-class-definition
      ('options-for-variable '\: variable-frame-flags)
      (frame-flags 3 ((variable) ())))
     
     (override-for-class-definition
      ('options-for-parameter '\: parameter-frame-flags)
      (frame-flags 3 ((parameter) ())))
     
     (override-for-class-definition
      ('initial-value 'for 'logical-variable '\: truth-value?)
      (initial-value-of-variable-or-parameter 5 ((logical-variable) ())))
     
     (override-for-class-definition
      ('initial-value 'for 'quantitative-variable '\: quantity?)
      (initial-value-of-variable-or-parameter 5 ((quantitative-variable) ())))
     
     (override-for-class-definition
      ('initial-value 'for 'float-variable '\: initial-value-float?)
      (initial-value-of-variable-or-parameter 5 ((float-variable) ())))
     
     (override-for-class-definition
      ('initial-value 'for 'long-variable '\: initial-value-long?)
      (initial-value-of-variable-or-parameter 5 ((long-variable) ())))
     
     (override-for-class-definition
      ('initial-value 'for 'integer-variable '\: initial-value-integer?)
      (initial-value-of-variable-or-parameter 5 ((integer-variable) ())))
     
     (override-for-class-definition
      ('initial-value 'for 'symbolic-variable '\: standard-or-class-qualified-symbol?)
      (initial-value-of-variable-or-parameter 5 ((symbolic-variable) ())))
     
     (override-for-class-definition
      ('initial-value 'for 'text-variable '\: whole-string?)
      (initial-value-of-variable-or-parameter 5 ((text-variable) ())))
     
     (override-for-class-definition
      ('initial-value 'for 'logical-parameter '\: truth-value)
      (initial-value-of-variable-or-parameter 5 ((logical-parameter) ())))
     
     (override-for-class-definition
      ('initial-value 'for 'quantitative-parameter '\: quantity)
      (initial-value-of-variable-or-parameter 5 ((quantitative-parameter) ())))
     
     (override-for-class-definition
      ('initial-value 'for 'float-parameter '\: initial-value-float)
      (initial-value-of-variable-or-parameter 5 ((float-parameter) ())))

     (override-for-class-definition
      ('initial-value 'for 'long-parameter '\: initial-value-long)
      (initial-value-of-variable-or-parameter 5 ((long-parameter) ())))

     (override-for-class-definition
      ('initial-value 'for 'integer-parameter '\: initial-value-integer)
      (initial-value-of-variable-or-parameter 5 ((integer-parameter) ())))
     
     (override-for-class-definition
      ('initial-value 'for 'symbolic-parameter '\: standard-or-class-qualified-symbol)
      (initial-value-of-variable-or-parameter 5 ((symbolic-parameter) ())))
     
     (override-for-class-definition
      ('initial-value 'for 'text-parameter '\: whole-string)
      (initial-value-of-variable-or-parameter 5 ((text-parameter) ())))

     (override-for-class-definition
      ('initial-value 'for 'sensor '\: initial-sensor-value?)  ; no interface
      (initial-value-of-variable-or-parameter 5 ((sensor) ())))

     (override-for-class-definition
      ('allow-duplicate-elements-for-g2-list '\: yes-or-no)
      (insert-duplicate-elements? 3 ((g2-list) ())))

     (override-for-class-definition
      ('array-length 'for 'g2-array '\: g2-array-length)
      (g2-array-length 5 ((g2-array) ())))

     (override-for-class-definition
      ('initial-values 'for 'g2-array '\: list-of-item-and-datum-constants?)
      (g2-array-initial-values 5 ((g2-array)())))

     (override-for-class-definition
      ('initial-values 'for 'value-array '\: list-of-datum-constants)
      (g2-array-initial-values 5 ((value-array) ())))

     (override-for-class-definition
      ('initial-values 'for 'item-array '\: constant-designation-list?)
      (g2-array-initial-values 5 ((item-array) ())))

     (override-for-class-definition
      ('initial-values 'for 'quantity-array '\: quantity-list)
      (g2-array-initial-values 5 ((quantity-array) ())))

     (override-for-class-definition
      ('initial-values 'for 'integer-array '\: integer-list)
      (g2-array-initial-values 5 ((integer-array)())))

     (override-for-class-definition
      ('initial-values 'for 'float-array '\: float-list)
      (g2-array-initial-values 5 ((float-array) ())))

     (override-for-class-definition
      ('initial-values 'for 'symbol-array '\: symbol-list)
      (g2-array-initial-values 5 ((symbol-array) ())))

     (override-for-class-definition
      ('initial-values 'for 'text-array '\: whole-string-list)
      (g2-array-initial-values 5 ((text-array) ())))

     (override-for-class-definition
      ('initial-values 'for 'truth-value-array '\: truth-value-list)
      (g2-array-initial-values 5 ((truth-value-array) ())))

     (override-for-class-definition
      ('attribute-displays '\: attribute-displays-spec?)
      (attribute-displays-for-class
       3
       ((object image-definition relation frame-style-definition user-menu-choice
		tabular-function procedure dial meter procedure-invocation
		model-definition external-simulation-definition action-button
		check-box radio-button slider) ())))

     (override-for-class-definition
      ('stubs '\: connections?)
      (stubs-for-class
       3
       ((object image-definition relation frame-style-definition user-menu-choice
		tabular-function procedure dial meter procedure-invocation
		model-definition external-simulation-definition action-button
		check-box radio-button slider) ())))

     (override-for-class-definition
      ('initial-width '\: positive-integer)
      (kb-workspace-initial-width 3 ((kb-workspace) ())))
     (override-for-class-definition
      ('initial-height '\: positive-integer)
      (kb-workspace-initial-height 3 ((kb-workspace) ())))
     (override-for-class-definition
      ('foreground-color '\:
			 extant-color-or-metacolor)
      (workspace-foreground-color? 3 ((kb-workspace) ())))
     (override-for-class-definition
      ('background-color '\:
			 extant-color-or-metacolor)
      (workspace-background-color? 3 ((kb-workspace) ())))
     (override-for-class-definition
      ('workspace-margin '\: non-negative-integer)
      (workspace-margin 3 ((kb-workspace) ())))
     (override-for-class-definition
      ('frame-style '\: frame-style-name?)
      (frame-style 3 ((kb-workspace) ())))
     (override-for-class-definition
      ('title-bar-text '\: workspace-title-bar-text)
      (title-bar-text 3 ((kb-workspace) ())))
     (override-for-class-definition
      ('module-assignment '\: module-name?)
      (module-this-is-part-of? 3 ((kb-workspace) ())))

     (override-for-class-definition
      ('cross-section-pattern '\: cross-section-pattern)
      (cross-section-pattern-for-class 3 ((connection) ())))

     (override-for-class-definition
      ('stub-length '\: stub-length)
      (stub-length-for-class 3 ((connection) ())))

     (override-for-class-definition
      ('junction-block '\:  junction-class)
      (junction-block-class-for-class 3 ((connection) ())))

     (override-for-class-definition
      ('default-message-properties '\: message-properties)
      (default-message-properties-for-class 3 ((message) ())))

     (override-for-class-definition
      ('default-text-box-colors '\: text-cell-colors)
      (default-text-box-colors-for-class 3 ((text-box) ())))

     (override-for-class-definition
      ('tracing-and-breakpoints '\: tracing-and-breakpoints)
      (tracing-and-breakpoints
       3
       ((procedure variable-or-parameter generic-simulation-formula rule
		   simulation-subtable dial meter readout-table)
	(method-declaration digital-clock))))
     (override-for-class-definition
      ('class-of-procedure-invocation '\: class-of-procedure-invocation?)
      (class-of-procedure-invocation 3 ((procedure) (method-declaration))))
     (override-for-class-definition
      ('default-procedure-priority '\: priority)
      (default-procedure-priority 3 ((procedure) (method-declaration))))
     (override-for-class-definition
      ('uninterrupted-procedure-execution-limit '\: execution-interval?-or-default)
      (uninterrupted-procedure-execution-limit?
       3
       ((procedure) (method-declaration))))
     (override-for-class-definition
      ('display-format '\: format?)
      (format-for-readout-table 3 ((readout-table) (digital-clock))))
     (override-for-class-definition
      ('display-update-interval '\: display-interval)
      (display-update-interval 3 ((readout-table dial meter graph) ())))
     (override-for-class-definition
      ('display-wait-interval '\: display-interval)
      (display-wait-interval 3 ((readout-table dial meter graph) ())))
     (override-for-class-definition
      ('display-update-priority '\: priority)
      (display-update-priority 3 ((readout-table dial meter graph) ())))
     (override-for-class-definition
      ('show-simulated-values '\: yes-or-no)
      (display-evaluation-should-use-simulated-values?
       3
       ((readout-table dial meter graph) (digital-clock))))
     (override-for-class-definition
      ('low-value-for-dial-ruling '\: dial-ruling-parameter)
      (low-value-for-dial-ruling 3 ((dial) ())))
     (override-for-class-definition
      ('increment-per-dial-ruling '\: dial-ruling-parameter)
      (increment-per-dial-ruling 3 ((dial) ())))
     (override-for-class-definition
      ('low-value-for-meter-ruling '\: meter-ruling-parameter)
      (low-value-for-meter-ruling 3 ((meter) ())))
     (override-for-class-definition
      ('increment-per-meter-ruling '\: meter-ruling-parameter)
      (increment-per-meter-ruling 3 ((meter) ())))
     (override-for-class-definition
      ('desired-range-for-horizontal-axis '\: horizontal-graph-ruling-parameter?)
      (desired-range-for-horizontal-axis? 3 ((graph) ())))
     (override-for-class-definition
      ('desired-range-for-vertical-axis '\: vertical-graph-ruling-parameter?)
      (desired-range-for-vertical-axis? 3 ((graph) ())))
     (override-for-class-definition
      ('scroll-continuously? '\: yes-or-no)
      (scroll-continuously? 3 ((graph) ())))
     (override-for-class-definition
      ('percentage-extra-space-to-leave '\: integer)
      (percentage-extra-space-to-leave 3 ((graph) ())))
     (override-for-class-definition
      ('show-grid-lines? '\: yes-or-no)
      (show-grid-lines? 3 ((graph) ())))
     (override-for-class-definition
      ('interval-between-horizontal-grid-lines? '\: horizontal-gridline-interval?)
      (interval-between-horizontal-grid-lines? 3 ((graph) ())))
     (override-for-class-definition
      ('extra-grid-lines? '\: extra-grid-line-specs)
      (extra-grid-lines? 3 ((graph) ())))
     (override-for-class-definition
      ('background-colors '\: graph-background-colors)
      (background-colors 3 ((graph) ())))
     (override-for-class-definition
      ('chart-style '\: chart-style)
      (chart-style 3 ((chart) ())))
     (override-for-class-definition
      ('data-series '\: data-series-descriptions)
      (data-series 3 ((chart) ())))
     (override-for-class-definition
      ('annotations '\: chart-annotations)
      (annotations 3 ((chart) ())))
     (override-for-class-definition
      ('table-size '\: table-dimensions)
      (cell-annotations 3 ((freeform-table) ())))
     (override-for-class-definition
      ('default-cell-format '\: cell-format-or-none)
      (default-cell-format 3 ((freeform-table) ())))
     (override-for-class-definition
      ('default-evaluation-setting '\: computation-style-or-none)
      (default-evaluation-setting 3 ((freeform-table) ())))
     (override-for-class-definition
      ('file-name-of-image '\: whole-string?)
      (file-name-of-image? 3 ((image-definition) ())))
     (override-for-class-definition
      ('save-image-data-with-kb '\: yes-or-no)
      (save-image-data-with-kb 3 ((image-definition) ())))
     (override-for-class-definition
      ('width-of-image '\: positive-integer?)
      (width-of-image 3 ((image-definition) ())))
     (override-for-class-definition
      ('height-of-image '\: positive-integer?)
      (height-of-image 3 ((image-definition) ())))
     (override-for-class-definition
      ('depth-of-image '\: positive-integer?)
      (depth-of-image 3 ((image-definition) ())))
     (override-for-class-definition
      ('applicable-class '\: user-instantiable-kb-class?)
      (class-for-user-menu-choice? 3 ((user-menu-choice) ())))
     (override-for-class-definition
      ('condition '\: user-menu-choice-expression)
      (condition-for-using-user-menu-choice? 3 ((user-menu-choice) ())))
     (override-for-class-definition
      ('action-priority 'for 'user-menu-choice '\: priority)
      (user-menu-choice-priority 5 ((user-menu-choice) ())))
     (override-for-class-definition
      ('keep-sorted '\: keep-tabular-function-sorted?)
      (keep-tabular-function-sorted? 3 ((tabular-function-of-1-arg) ())))
     (override-for-class-definition
      ('interpolate '\: yes-or-no)
      (tabular-function-interpolation? 3 ((tabular-function-of-1-arg) ())))
     (override-for-class-definition
      ('first-class '\: class)
      (class-of-subject 3 ((relation) ())))
     (override-for-class-definition
      ('second-class '\: class)
      (class-of-object 3 ((relation) ())))
     (override-for-class-definition
      ('description-of-frame '\: frame-description)
      (description-of-frame 3 ((frame-style-definition) ())))
     (override-for-class-definition
      ('timeout-interval '\: foreign-function-timeout-interval)
      (timeout-interval 3 ((foreign-function-declaration) ())))
     (override-for-class-definition
      ('default-simulation-time-increment '\: simulation-time-increment)
      (default-simulation-time-increment-for-model 3 ((model-definition) ())))
     (override-for-class-definition
      ('integration-algorithm '\: integration-algorithm-specification)
      (integration-algorithm-for-model 3 ((model-definition) ())))
     (override-for-class-definition
      ('simulation-procedure '\: procedure-name?)
      (simulation-procedure-for-model 3 ((model-definition) ())))
     (override-for-class-definition
      ('send-all-values-at-beginning-of-cycle '\: yes-or-no)
      (send-all-values-at-beginning-of-cycle-for-model? 3 ((model-definition) ())))
     (override-for-class-definition
      ('simulation-control-specifications '\: simulation-control-specification)
      (simulation-control-specifications 3 ((model-definition) ())))
     (override-for-class-definition
      ('class-of-object-computed-by-this '\: new-class)
      (class-of-object-computed-by-this 3 ((external-simulation-definition) ())))
     (override-for-class-definition
      ('gfi-input-interface-object '\: gfi-interface-object)
      (gfi-input-interface-object 3 ((gfi-data-service) ())))
     (override-for-class-definition
      ('gsi-interface-name '\: gsi-interface-name)
      (gsi-interface-name 3 ((gsi-data-service gsi-message-service) ())))
     (override-for-class-definition
      ('g2-to-g2-interface-name '\: g2-to-g2-interface-name)
      (g2-to-g2-interface-name 3 ((g2-to-g2-data-service) ())))
     (override-for-class-definition
      ('g2-meter-name '\: g2-meter-name)
      (g2-meter-name 3 ((g2-meter-data-service) ())))
     (override-for-class-definition
      ('maximum-number-of-output-lines '\: positive-integer?)
      (maximum-number-of-output-lines 3 ((gfi-output-interface) ())))
     (override-for-class-definition
      ('gfi-output-file-update-frequency '\: gfi-output-file-update-frequency)
      (gfi-output-file-update-frequency 3 ((gfi-output-interface) ())))
     (override-for-class-definition
      ('gfi-output-time-stamp-format '\: gfi-time-stamp-format)
      (gfi-output-time-stamp-format 3 ((gfi-output-interface) ())))
     (override-for-class-definition
      ('gfi-output-file-format '\: gfi-file-format)
      (gfi-output-file-format 3 ((gfi-output-interface) ())))
     (override-for-class-definition
      ('renamed-gfi-output-file-pathname '\: gfi-file-pathname)
      (renamed-gfi-output-file-pathname? 3 ((gfi-output-interface) ())))
     (override-for-class-definition
      ('gfi-output-file-pathname '\: gfi-file-pathname)
      (gfi-output-file-pathname 3 ((gfi-output-interface) ())))
     (override-for-class-definition
      ('ignore-gfi-input-base-time '\: gfi-yes-or-no?)
      (ignore-gfi-input-base-time? 3 ((gfi-input-interface) ())))
     (override-for-class-definition
      ('gfi-input-variables-update-mode '\: gfi-input-variables-update-mode)
      (gfi-input-variables-update-mode 3 ((gfi-input-interface) ())))
     (override-for-class-definition
      ('gfi-input-time-stamp-format '\: gfi-time-stamp-format)
      (gfi-input-time-stamp-format 3 ((gfi-input-interface) ())))
     (override-for-class-definition
      ('gfi-input-file-format '\: gfi-file-format)
      (gfi-input-file-format 3 ((gfi-input-interface) ())))
     (override-for-class-definition
      ('gfi-input-file-pathname '\: gfi-file-pathname)
      (gfi-input-file-pathname 3 ((gfi-input-interface) ())))
     (override-for-class-definition
      ('external-system-has-a-scheduler '\: yes-or-no)
      (external-system-has-a-scheduler 3 ((gsi-interface) ())))
     (override-for-class-definition
      ('poll-external-system-for-data '\: yes-or-no)
      (poll-external-system-for-data 3 ((gsi-interface) ())))
     (override-for-class-definition
      ('remote-process-initialization-string '\: process-initialization-string)
      (remote-process-initialization-string 3 ((gsi-interface) ())))
     (override-for-class-definition
      ('grouping-specification '\: gsi-variable-grouping-specification)
      (grouping-specification 3 ((gsi-interface) ())))
     (override-for-class-definition
      ('identifying-attributes '\: attributes-which-identify-a-network-item-reference)
      (identifying-attributes 3 ((network-interface) ())))
     (override-for-class-definition
      ('interface-warning-message-level '\: interface-warning-message-level)
      (interface-warning-message-level 3 ((network-interface) ())))
     (override-for-class-definition
      ('interface-timeout-period '\: timeout-interval-or-default)
      (interface-timeout-period 3 ((gsi-interface g2-to-g2-data-interface) ())))
     (override-for-class-definition
      ('interface-initialization-timeout-period '\: timeout-interval-or-default-or-none)
      (interface-initialization-timeout-period 3 ((gsi-interface g2-to-g2-data-interface) ())))
     (override-for-class-definition
      ('interval-to-poll-external-system '\: timeout-interval-or-default)
      (interval-to-poll-external-system 3 ((gsi-interface) ())))
     (override-for-class-definition
      ('disable-interleaving-of-large-messages '\: yes-or-no)
      (disable-interleaving-of-large-messages 3 ((network-interface) ())))
     #+text-converted-to-show-encoding
     (override-for-class-definition
      ('text-converted-to-show-encoding? '\: yes-or-no)
      (text-converted-to-show-encoding? 3 ((borderless-free-text) ())))
     #+text-converted-to-show-encoding
     (override-for-class-definition
      ('text-converted-to-show-encoding? '\: yes-or-no)
      (text-converted-to-show-encoding? 3 ((free-text) ())))
     (override-for-class-definition
      ('action-priority 'for 'action-button '\: priority)
      (action-button-priority 5 ((action-button) ())))
     (override-for-class-definition
      ('value-on-activation '\: attribute)
      (value-on-activation? 3 ((non-action-button) ())))
     (override-for-class-definition
      ('variable-or-parameter '\: constant-variable-designation?) ; no interface
      (associated-variable-designation? 3 ((non-action-button) ())))
     (override-for-class-definition
      ('on-value 'for 'check-box '\: attribute)
      (on-value-for-check-box 5 ((check-box) ())))
     (override-for-class-definition
      ('off-value 'for 'check-box '\: attribute)
      (off-value-for-check-box 5 ((check-box) ())))
     (override-for-class-definition
      ('on-value 'for 'radio-button '\: attribute)
      (value-for-radio-button 5 ((radio-button) ())))
     (override-for-class-definition
      ('maximum-value '\: number?)
      (maximum-value-for-slider 3 ((slider) ())))
     (override-for-class-definition
      ('minimum-value '\: number?)
      (minimum-value-for-slider 3 ((slider) ())))
     (override-for-class-definition
      ('set-value-while-sliding? '\: yes-or-no)
      (set-value-while-sliding? 3 ((slider) ())))
     (override-for-class-definition
      ('when-to-show-value '\: when-to-show-value)
      (when-to-show-value 3 ((slider) ())))
     (override-for-class-definition
      ('format-for-type-in-box '\: type-in-box-format?)
      (format-for-type-in-box 3 ((type-in-box) ())))
     (override-for-class-definition
      ('blank-for-type-in? '\: yes-or-no)
      (blank-for-type-in? 3 ((type-in-box) ())))
     (override-for-class-definition
      ('have-edit-option-buttons-for-type-in? '\: yes-or-no)
      (have-edit-option-buttons-for-type-in? 3 ((type-in-box) ())))
     (override-for-class-definition
      ('scan-interval '\: positive-quantity-interval?)
      (rule-scan-interval 3 ((rule) ())))
     (override-for-class-definition
      ('focal-classes '\: focal-classes)
      (focal-classes 3 ((rule) ())))
     (override-for-class-definition
      ('focal-objects '\: focal-objects)
      (focal-objects 3 ((rule) ())))
     (override-for-class-definition
      ('categories '\: categories)
      (rule-categories 3 ((rule) ())))
     (override-for-class-definition
      ('rule-priority '\: priority)
      (rule-priority 3 ((rule) ())))
     (override-for-class-definition
      ('depth-first-backward-chaining-precedence '\: positive-integer)
      (backward-chaining-precedence 3 ((rule) ())))
     (override-for-class-definition
      ('timeout-for-rule-completion '\: interval?-or-default)
      (timeout-for-rule-completion 3 ((rule) ())))
     (override-for-class-definition
      ('time-increment-for-update '\: simulation-time-increment?)
      (time-increment-for-update? 3 ((simulation-subtable) ())))
     )))

(add-grammar-rules system-class-overrides-for-class-definition)



#+development
(progn


(defparameter object-override-name-alist
  ;;alias slot-name-for-rule alias in words
  '((data-type
     data-type
     data type)
    (validity-interval
     validity-interval
     validity interval)
    (initial-value
     initial-value
     initial value)
    (initial-values
     g2-array-initial-values
     initial values)
    (data-server
     data-server-map
     data server)
    (default-update-interval
     default-update-interval
     default update interval)
    (allow-duplicate-elements-for-g2-list
     insert-duplicate-elements?
     allow duplicate elements for g2-list)
    (array-is-permanent)
    (frame-flags)
    (element-type
     g2-array-element-type)
    (initial-values
     g2-array-initial-values)
    (array-length
     g2-array-length)
    (history-keeping-spec)
    (history-keeping-spec
     history-keeping-spec-for-simulation-subtables)
    (allow-duplicate-elements
     insert-duplicate-elements?)
    (list-is-permanent)
    (element-type
     list-type)
    (simulation-details)))

(defun write-grammar-rules-for-definition-overrides (class-definition-p)
  (loop for rule in (grammar-rules-for-definition-overrides class-definition-p)
	do (write-override-grammar-rule rule)))

(defun grammar-rules-for-definition-overrides (class-definition-p)
  (loop with info = (info-for-grammar-rules-for-definition-overrides)
	for (slot-name alias include exclude) in info
	for alias-for-hand-rules
	    = (if (eq slot-name 'insert-duplicate-elements?)
		  'allow-duplicate-elements-for-g2-list
		  alias)
	for only-slot-with-this-alias-p
	    = (loop for (other-slot-name other-alias) in info
		    always (or (not (eq alias other-alias))
			       (eq slot-name other-slot-name)))
	for only-slot-with-this-alias-p-for-hand-rules
	    = (and only-slot-with-this-alias-p
		   (not (memq alias '(array-length initial-values data-type off-value))))
	for categories-all-the-same-p
	    = (loop with first-category = (second (first include))
		    for (nil category) in (rest include)
		    always (eq category first-category))
	nconc
	(if categories-all-the-same-p
	    (grammar-rule-for-definition-override
	     class-definition-p slot-name alias-for-hand-rules
	     (unless only-slot-with-this-alias-p-for-hand-rules
	       (when (cdr include)
		 (warn "problem with ~S" slot-name))
	       (first (first include)))
	     (second (first include))
	     (loop for (class) in include collect class)
	     (loop for (class) in exclude collect class))
	    (loop for (class category) in include
		  for alias-for-hand-rules-1
		      = (if (eq slot-name 'frame-flags)
			    (case category
			      (variable-frame-flags
			       'options-for-variable)
			      (parameter-frame-flags
			       'options-for-parameter))
			    alias-for-hand-rules)
		  nconc
		  (grammar-rule-for-definition-override
		   class-definition-p slot-name alias-for-hand-rules-1
		   (when (eq alias-for-hand-rules-1 alias-for-hand-rules)
		     class)
		   category
		   (list class)
		   nil)))))

(defun grammar-rule-for-definition-override
    (class-definition-p slot-name alias class-for-name? category
			acceptable unacceptable)
  (if class-definition-p
      (list (grammar-rule-for-definition-override-1
	     class-definition-p slot-name alias class-for-name? category
	     acceptable unacceptable))
      (let* ((a (loop for a in object-override-name-alist
		      for (a-alias a-slot-name-for-rule) = a
		      when (and (eq alias a-alias)
				(or (eq a-alias a-slot-name-for-rule)
				    (eq slot-name a-slot-name-for-rule)))
			return a))
	     (slot-name-for-rule (or (second a) alias))
	     (alias-in-words (cddr a)))
	(when a
	  (nconc
	   (list (grammar-rule-for-definition-override-1
		  class-definition-p slot-name-for-rule
		  alias
		  class-for-name? category
		  acceptable unacceptable))
	   (when alias-in-words
	     (list (grammar-rule-for-definition-override-1
		    class-definition-p slot-name-for-rule
		    alias-in-words
		    class-for-name? category
		    acceptable unacceptable))))))))

(defun grammar-rule-for-definition-override-1
    (class-definition-p slot-name alias class-for-name? category
			acceptable unacceptable)
  `(,(if class-definition-p
	 `override-for-class-definition
	 `override-for-object-definition)
     (,@`(,@(if (atom alias)
		`(',alias)
		(loop for word in alias
		      collect `',word))
	    ,@(when class-for-name?
		`('for ',class-for-name?)))
	'\: ,category)
     (,slot-name
       ,(+ 2 (+ (if (atom alias) 1 (length alias))
		(if class-for-name? 2 0)))
       ,(if class-definition-p
	    `(,acceptable ,unacceptable)
	    `,(first acceptable)))))

(defun compare-override-grammar-rules (rule1 rule2)
  (and (eq (first rule1) (first rule2))
       (equal (second rule1) (second rule2))
       (eq (first (third rule1)) (first (third rule2)))
       (eql (second (third rule1)) (second (third rule2)))
       (if (symbolp (third (third rule1)))
	   (eq (third (third rule1)) (third (third rule2)))
	   (and (class-set-equal (first (third (third rule1)))
				 (first (third (third rule2))))
		(class-set-equal (second (third (third rule1)))
				 (second (third (third rule2))))))))

(defun class-set-equal (cset1 cset2)
  (and (loop for c1 in cset1
	     always (memq c1 cset2))
       (loop for c2 in cset2
	     always (memq c2 cset1))))

(defun key-for-matching-override-rules (rule class-definition-p)
  (declare (ignore class-definition-p))
  (ldiff (second rule)
	 (member ''\: (second rule) :test 'equal)))	  

(defun find-matching-override-rule (key-to-find rule-list class-definition-p)
  (loop for rule in rule-list
	for rule-key = (key-for-matching-override-rules rule class-definition-p)
	when (equal rule-key key-to-find)
	  return rule))

(defun compare-generated-rules-to-hand-written-rules (class-definition-p)
  (let ((generated-grammar-rules
	 (grammar-rules-for-definition-overrides class-definition-p)))
    (loop with missing-rules = nil
	  for rule in generated-grammar-rules
	  for rule-key = (key-for-matching-override-rules rule class-definition-p)
	  for hand-written-rule
	      = (find-matching-override-rule
		 rule-key
		 (if class-definition-p
		     system-class-overrides-for-class-definition
		     system-class-overrides-for-object-definition)
		 class-definition-p)
	  do
      (cond (hand-written-rule
	     (unless (compare-override-grammar-rules rule hand-written-rule)
	       (format t "~&~%rule mismatch:~%generated~%")
	       (write-override-grammar-rule rule)
	       (format t "~%hand~%")
	       (write-override-grammar-rule hand-written-rule)))
	    (t
	     (push rule missing-rules)))
	  finally (loop for rule in missing-rules
			do
		    (format t "~&~%missing rule:~%generated~%")
		    (write-override-grammar-rule rule)))
    (loop for rule in (if class-definition-p
			  system-class-overrides-for-class-definition
			  system-class-overrides-for-object-definition)
	  for rule-key = (key-for-matching-override-rules rule class-definition-p)
	  for generated-rule
	      = (find-matching-override-rule
		 rule-key
		 generated-grammar-rules
		 class-definition-p)
	  do
      (unless generated-rule
	(format t "~&~%missing rule:~%hand~%")
	(write-override-grammar-rule rule)))))

(defun write-override-grammar-rule (rule)
  (format t "~&(~(~A~)~%  (" (first rule))
  (loop for x in (second rule)
	for firstp = t then nil
	do (unless firstp (format t " "))
	   (if (and (consp x) (eq (car x) 'quote))
	       (format t "'~(~A~)" (cadr x))
	       (format t "~(~A~)" x)))
  (format t ")~%  ~(~A~))" (third rule)))	       

(defun info-for-grammar-rules-for-definition-overrides ()
  (loop with collected-slots = nil
	for class being each subclass of 'root
	for class-description = (class-description class)
	for class-is-user-subclassable-p
	    = (feature-assq 'foundation-class (class-features class-description))
	do
    (when class-is-user-subclassable-p
      (loop for slot in (slots-local-to-class class-description)
	    for slot-description = (get-slot-description-of-class-description
				    slot class-description)
	    for slot-type?
		= (feature-assq 'type
				(slot-features slot-description))
	    for category = (case slot
			     (data-type-of-variable-or-parameter
			      (if (or (subclassp class 'quantitative-variable)
				      (subclassp class 'quantitative-parameter))
				  'quantitative-data-type
				  (category-symbol-given-slot-type slot-type?)))
			     (list-type
			      (if (eq class 'item-list)
				  'class
				  (category-symbol-given-slot-type slot-type?)))
			     (g2-array-element-type
			      (if (eq class 'item-array)
				  'class
				  (category-symbol-given-slot-type slot-type?)))
			     (t
			      (category-symbol-given-slot-type slot-type?)))
	    for user-overridable-p
		= (feature-assq 'user-overridable
				(slot-features slot-description))
	    for collected-info-for-slot = (assq slot collected-slots)
	    for class-to-use
		= (cond ((not (eq slot 'frame-flags))
			 class)
			((subclassp class 'variable)
			 'variable)
			((subclassp class 'parameter)
			 'parameter)
			(t
			 class))
	    for collected-category
		= (loop for (collected-class collected-category)
			    in (third collected-info-for-slot)
			when (subclassp class-to-use collected-class)
			  return collected-category)
	    do (cond ((and (not user-overridable-p)
			   (not collected-category)))
		     ((and (or (null category)
			       (not user-overridable-p))
			   user-overridable-p)
		      (when (and collected-category
				 (loop for (collected-class)
					   in (third collected-info-for-slot)
				       thereis (subclassp class-to-use collected-class)))
			(setf (fourth collected-info-for-slot)
			      (nconc (fourth collected-info-for-slot)
				     (list (list class-to-use nil))))))
		     ((eq category collected-category))
		     (t
		      (unless collected-info-for-slot
			(setq collected-info-for-slot
			      (list slot
				    (alias-slot-name-if-necessary slot class-to-use)
				    nil
				    nil))
			(push collected-info-for-slot collected-slots))
		      (setf (third collected-info-for-slot)
			    (nconc (loop for (collected-class collected-category)
					     in (third collected-info-for-slot)
					 unless (and (subclassp collected-class class-to-use)
						     (eq collected-category category))
					   collect (list collected-class collected-category))
				   (list (list class-to-use category))))))))
	finally (return (nreverse collected-slots))))

)






;; the following is because interval? does not change none to nil.

(defun second-none (form)
  (if (eq (second form) 'none)
      (phrase-list (first form) nil)
      form))

#+unused
(defun change-quantity-to-number (data-type)
  (if (eq (second data-type) 'quantity) (setf (second data-type) 'number))
  data-type)

;;; Make-simulation-subtable-and-install is called upon instantiation of a variable
;;; initialized to have a simulation frame by the above grammar. It calls
;;; put-simulation-frame? because this slot putter is evidently not being 
;;; called upon creation. If this convention is changed, the following code
;;; will be redundant and probably not harmful. I assume that for now,
;;; make-simulation-subtable-and-install will be called, and will place and install
;;; the subframe using the slot putter. Then the subframe will be placed again
;;; without calling the slot putter. The variable frame-being-made is declared in FRAMES3.

(define-category-evaluator-interface (simulation-frame?
				       :access read)
    (class simulation-subtable)
  ;; this does not have a setter because we are not prepared to
  ;; have unattached simulation-subtables flying around on the loose.
  ((get-form (slot-value))
   slot-value))


(defun make-simulation-subtable-and-install ()
  (let ((simulation-subtable (make-frame 'simulation-subtable)))
    (body-of-put-for-simulation-frame
      frame-being-made simulation-subtable t)))

(defun make-simulation-subtable-with-specific-class-and-install (class)
  (when (subclassp class 'simulation-subtable)
    (let ((simulation-subtable (make-frame class)))
      (body-of-put-for-simulation-frame
	frame-being-made simulation-subtable t))))

#+unused
(defun make-simulation-frame-and-install ()
  (make-simulation-subtable-and-install))

;; Necessary for old saved kbs where the simulation-frame?  slot has
;; simulation-frame rather than simulation-subtable as the subframe.  This could
;; be eliminated if simulation-frame?  were made obsolete.



(defun class-instantiation-warning-not-defined
    (class-for-instantiation slot-description class)
  (warning-message 1
      "The class ~A cannot be instantiated within ~
       attribute ~NS because it is not a defined class."
    class-for-instantiation slot-description
    (class-description class)))

(defun class-instantiation-warning-incompatible-class
     (class-for-instantiation slot-description class type-specification-class)
    (warning-message 1
	"The class ~A cannot be instantiated within attribute ~
         ~NS because it is not a subclass of the type ~
         specification for this attribute, class ~A."
      class-for-instantiation slot-description
      (class-description class) type-specification-class))

(defun class-instantiation-warning-undefined-type-specification-class
    (class-for-instantiation slot-description class type-specification-class)
  (warning-message 1
      "The class ~A cannot be instantiated within attribute ~
       ~NS because the type-specification class, ~A,  has not yet ~
       been defined."
    class-for-instantiation slot-description
    (class-description class) type-specification-class))



;;; Instantiate variable creates a variable of the specified class, or returns nil.
;;; This function occurs in the init for (:funcall instantiate-variable <class>)
;;; created by attribute-definition grammar in file GRAMMAR2.

;;; If the definition of a variable instantiates an attribute containing a variable,
;;; there is the possibility of an infinite recursive instantiation of variables in
;;; atributes. This is solved by having a recursion count for instantiate-variable.



(def-system-variable attribute-nesting-depth grammar6a 1) ; special

(declare-special-global recursive-attribute-nesting-has-occurred?)
(def-system-variable recursive-attribute-nesting-has-occurred? grammar6a nil)

;; Improve the messages, and consider making this one function!


;;; This function now instantiates variables and parameters. Its name cannot be changed
;;; because it is saved in kbs. (Consider having two identical functions after 2.0 alpha.

(defun instantiate-variable (class)
  (instantiate-object-in-attribute-1 class t))

(defun instantiate-object-in-attribute (class)
  (instantiate-object-in-attribute-1 class nil))

(defun instantiate-object-in-attribute-1 (class variable-or-parameter-p)
  (cond (recursive-attribute-nesting-has-occurred? nil)
	((>= attribute-nesting-depth attribute-nesting-limit)
	 (setq recursive-attribute-nesting-has-occurred? t)
	 (warning-message 1
	     "An infinite set of ~A nested inside each other cannot ~
            be instantiated as attributes. The process has been stopped ~
            at a depth of ~d.  This ~A is of class ~A."
	   (if variable-or-parameter-p
	       "variables or parameters"
	       "objects")
	   attribute-nesting-limit
	   (if variable-or-parameter-p
	       "variable or parameter"
	       "object")
	   class)
	 nil)
	((get-class-feature-if-any class 'not-user-instantiable)
	 (warning-message 1
	     "The class ~a is not instantiable." class)
	 nil)
	((if variable-or-parameter-p
	     (subclassp class 'variable-or-parameter)
	     (subclassp class 'object))
	 (prog1
	     (let ((attribute-nesting-depth (+f attribute-nesting-depth 1)))
	       (make-frame class))
	   (if (=f attribute-nesting-depth 1)
	       (setq recursive-attribute-nesting-has-occurred? nil))))
	((classp class)
	 (if variable-or-parameter-p
	     (warning-message 1
		 "The class ~a cannot be instantiated because it is not an ~
              instantiable variable or parameter.  If ~a is an instantiable ~
              object class that is not a variable or parameter, You may want ~
              to change the attribute declaration to use the IS AN INSTANCE ~
              OF syntax instead of the IS GIVEN BY syntax." class class)
	     (warning-message 1
		 "~A cannot instantiated as an attribute because it is not ~
            an instantiable object class." class))
	 nil)
	(t
	 (warning-message 1
	     "~A cannot be instantiated within an attribute because ~
              it is not a defined class." class)
	 nil)))




;;; The following compiler and writer for CLASS have the effect of making
;;; several restrictions on the modification to the class of definitions.  If
;;; class is used as a slot grammar elsewhere, this will have no effect. Note
;;; that while the initial value may be "none", the user may not enter this.
;;; As of (ghw 4/4/94), the user may revert to NONE

;; I (MHD) believe the above comment applies to the compiler for CLASS further
;; below, and I do not believe that the compilers below are reachable, and
;; therefore I believe they should not be defined.  Would GHW please check
;; and/or speak to me, or to David McDonald who reviewed this with me, but has
;; no particular opinion.  (MHD 5/2/97)

(def-slot-value-compiler new-class (parse-result frame slot-name)
  (compile-class-for-slot parse-result frame slot-name))

(def-slot-value-compiler item-class (parse-result frame slot-name)
  (compile-class-for-slot parse-result frame slot-name))

(def-slot-value-compiler connection-class (parse-result frame slot-name)
  (compile-class-for-slot parse-result frame slot-name))

(def-slot-value-compiler object-class (parse-result frame slot-name)
  (compile-class-for-slot parse-result frame slot-name))

(def-slot-value-compiler message-class (parse-result frame slot-name)
  (compile-class-for-slot parse-result frame slot-name))

(defparameter classes-for-object-definition
	      '(object))

(defparameter classes-for-class-definition
              '(item))




;; Note that as of version 4.0, the CLASS slot of definitions is no longer
;; restricted from being modified while G2 is running or paused, or when there
;; are instances.  - cpm, 3/14/94

(def-slot-value-compiler class (parse-result frame slot-name)
  (declare (ignore slot-name))
  (cond
    ((of-class-p frame 'class-definition)
     (let* ((name-of-defined-class (name-of-defined-class frame))
	    (direct-superior-classes?
	      (direct-superiors-of-defined-class frame))
	    (undefined-direct-superior?
	      (loop for superior in direct-superior-classes?
		    when (not (classp superior))
		      return superior))
	    (possible-class-inheritance-path?
	      (when (and direct-superior-classes?
			 (not undefined-direct-superior?))
		(make-class-inheritance-path-for-user-defined-class
		  parse-result direct-superior-classes?)))
	    (foundation-class?
	      (unless undefined-direct-superior?
		(most-refined-foundation-class-of-direct-superiors
		  direct-superior-classes?)))
	    (specialized-definition-class
	      (get-specialized-definition-class frame))
	    (class-primary-foundation-class
	      (case specialized-definition-class
		(object-definition 'object)
		(message-definition 'message)
		(connection-definition 'connection)
		(t 'item)))
	    (potential-definition? nil)
	    (potential-definition-definition-type? nil)
	    (potential-specialized-definition-class? nil)
	    (prohibited-superior? nil)
	    (preceding-superior? nil)
	    (following-superior? nil)
	    (first-foundation-class? nil)
	    (second-foundation-class? nil)
	    (colliding-superior? nil)
	    (problem-inferior-class? nil)
	    (inferior-potential-definition? nil))

       (cond
	 ((eq parse-result 'none)
	  (reclaim-slot-value possible-class-inheritance-path?)
	  (if (and (classp name-of-defined-class)
		   (instantiated-class-p name-of-defined-class))
	      (values
		bad-phrase
		(tformat-text-string
		  "The name of an instantiated class cannot revert to NONE. ~
                   To make this change, the instances must be deleted first."))
	      (setq parse-result nil)))
	      
	 ((and
	    (let ((definition-with-this-name
		    (get-instance-with-name-if-any 'class-definition parse-result)))
	      (and definition-with-this-name
		   (neq definition-with-this-name frame))))
	  (reclaim-slot-value possible-class-inheritance-path?)
	  (values bad-phrase
		  (copy-constant-wide-string #w"There is another definition with this name.")))

	 ((system-defined-class-p parse-result)
	  (reclaim-slot-value possible-class-inheritance-path?)
	  (values bad-phrase
		  (copy-constant-wide-string #w"It is the name of a system-defined class.")))

	 ;; There is a potential definition that has both the current name and the
	 ;; new name (parse-result) in its list of direct superiors.  Because the name
	 ;; change code does a direct-substitution of the old name for the new
	 ;; in the direct superiors, this would result in duplicate direct superiors.
	 ((and (not (eq parse-result 'none))
	       (loop for potential-definition in (potential-inferior-class-definitions
						   name-of-defined-class)
		     when (memq parse-result
				(direct-superiors-of-defined-class potential-definition))
		       return (setq potential-definition? potential-definition)))
	  (values bad-phrase
		  (if (name-of-defined-class potential-definition?)
		      (tformat-text-string
			"This class cannot be named ~A because then the class-definition for ~A ~
                         would have two direct superiors named ~A."
			parse-result (name-of-defined-class potential-definition?)
			parse-result)
		      (tformat-text-string
			"This class cannot be named ~A because then an unnamed class-definition ~
                         would have two direct superiors named ~A."
			parse-result parse-result))))
					      
	 ((and (null (superblock? frame))
	       (subclassp name-of-defined-class 'default-junction))
	  (reclaim-slot-value possible-class-inheritance-path?)
	  (values bad-phrase
		  (tformat-text-string "You may not edit the attributes of an ~
                     automatically created junction block")))

	 ((type-specification-for-user-or-datum-type parse-result)
	  (reclaim-slot-value possible-class-inheritance-path?)
	  (values
	    bad-phrase
	    (tformat-text-string
	      "You may not use ~a as the name of a class because it specifies a type in G2."
	      parse-result)))

	 ;; There is a circularity in inheritance for two potential
	 ;; definitions.  Two definitions have the name of defined class of the
	 ;; other definition as a superior class.
	 ((loop for potential-definition being each potential-definition of parse-result
		for potential-definition-name? =
		(name-of-defined-class potential-definition)
		do
	    (when (and potential-definition-name?
		       (memq potential-definition-name? direct-superior-classes?))
	      (return (setq prohibited-superior? potential-definition-name?))))
	  (reclaim-slot-value possible-class-inheritance-path?)
	  (values bad-phrase
		  (circularity-in-potential-definition-inheritance
		    prohibited-superior?)))
	 
      ;; Merging paths rule 1 violation for potential-inferior classes.
      ((loop for potential-definition being each potential-definition of parse-result
	     for direct-superiors = (direct-superiors-of-defined-class
				      potential-definition)
	     thereis
	     (loop for sublist on direct-superiors
		   until (null (second sublist))
		   for preceding-superior = (first sublist)
		   for following-superior = (second sublist)
		   for following-superior-inheritance-path? =
		   (if (eq following-superior parse-result)
		       possible-class-inheritance-path?
		       (let ((class-description nil))
			 (and (setq class-description
				    (class-description following-superior))
			      (class-inheritance-path class-description))))
		   thereis
		   (and following-superior-inheritance-path?
			(memq preceding-superior
			      following-superior-inheritance-path?)
			(setq preceding-superior? preceding-superior)
			(setq following-superior? following-superior)
			(setq prohibited-superior?
			      (name-of-defined-class potential-definition)))))
       (reclaim-slot-value possible-class-inheritance-path?)
       (values bad-phrase
	       (subclass-appears-after-superior-for-potential-definition
		 preceding-superior? following-superior? prohibited-superior?)))

      ;; The foundation class for this class would invalidate the direct superiors
      ;; of a potential definition.
      ((loop for potential-definition being each potential-definition of parse-result
	     for direct-superiors = (direct-superiors-of-defined-class
				      potential-definition)
	     thereis
	     (and (cdr direct-superiors)
		  (loop for sublist on direct-superiors
			until (null (cdr sublist))
			for superior = (car sublist)
			for superior-foundation-class? =
			      (or (and (eq superior parse-result)
				       foundation-class?)
				  (and (classp superior)
				       (get-foundation-class-for-class superior)))
			thereis
			(and superior-foundation-class?
			     (loop for other-superior in (cdr sublist)
				   for other-superior-foundation-class? =
				   (or (and (eq other-superior parse-result)
					    foundation-class?)
				       (and (classp other-superior)
					    (get-foundation-class-for-class
					      other-superior)))
				   thereis
				   (and other-superior-foundation-class?
					(not (subclassp
					       superior-foundation-class?
					       other-superior-foundation-class?))
					(not (subclassp
					       other-superior-foundation-class?
					       superior-foundation-class?))
					(setq first-foundation-class?
					      superior-foundation-class?)
					(setq second-foundation-class?
					      other-superior-foundation-class?)))))))
       (reclaim-slot-value possible-class-inheritance-path?)
       (values bad-phrase
	       (invalidates-direct-superiors-for-potential-definition
		 parse-result first-foundation-class? second-foundation-class?)))

      ;; A potential-definition has a definition class that is incompatible with
      ;; this frame.
      ((loop for potential-definition being each potential-definition of parse-result
	     do
	 (unless (or (definition-classes-are-compatible-p
			 frame potential-definition)
		     (eq specialized-definition-class 'class-definition)
		     (eq (get-specialized-definition-class potential-definition)
			 'class-definition))
	   (setq potential-definition? potential-definition) 	    
	   (return (setq potential-definition-definition-type?
			 (get-specialized-definition-class potential-definition)))))
       (reclaim-slot-value possible-class-inheritance-path?)
       (values bad-phrase
	       (potential-definition-class-type-is-incompatible
		 potential-definition? potential-definition-definition-type?
		 'subclass)))

      ;; There is a direct-superior on a potential-definition with a foundation-class
      ;; that is not supported by this definition.
      ((loop for potential-definition being each potential-definition of parse-result
	     for direct-superiors? = (direct-superiors-of-defined-class
				       potential-definition)
	     do
	 (setq prohibited-superior?
	       (and direct-superiors?
		    (incorrect-foundation-class-for-this-definition-p
		      direct-superiors? class-primary-foundation-class nil)))
	 (when prohibited-superior?
	   (return (setq potential-definition? potential-definition))))
       (reclaim-slot-value possible-class-inheritance-path?)
       (values bad-phrase
	       (if (frame-of-class-p potential-definition? 'class-definition)
		   (potential-definition-superior-not-the-mixed-hierarchy-type
		     frame potential-definition? prohibited-superior?)
		   (potential-definition-has-different-class-type
		     parse-result specialized-definition-class potential-definition?))))

      ;; There is a direct-superior on this definition that is not inheritable
      ;; by a potential-inferior class.
      ((and direct-superior-classes?
	    (loop for potential-definition being each potential-definition of parse-result
		  for potential-specialized-definition-class
		      = (get-specialized-definition-class potential-definition)
		  for potential-primary-foundation-class
		      = (case potential-specialized-definition-class
			  (object-definition 'object)
			  (message-definition 'message)
			  (connection-definition 'connection)
			  (t 'item))
		  do
	      (setq prohibited-superior?
		    (incorrect-foundation-class-for-this-definition-p
		      direct-superior-classes? potential-primary-foundation-class nil))
	      (when prohibited-superior?
		(setq potential-specialized-definition-class?
		      potential-specialized-definition-class)
		(return (setq potential-definition? potential-definition)))))
       (values bad-phrase
	       (potential-definition-cannot-inherit-foundation-class
		 prohibited-superior? potential-definition?
		 potential-specialized-definition-class?)))

       ;; Merging paths rules 2 for subclasses or potential inferior-classes
       ;; of class.
       ((and possible-class-inheritance-path?
	     (loop for potential-inferior-definition in
		   (potential-inferior-class-definitions parse-result)
		   for direct-superiors =
                           (direct-superiors-of-defined-class
                             potential-inferior-definition)
		   for other-direct-superiors-not-defined? =
		         (loop for superior in direct-superiors
			       thereis 
			       (not (or (eq superior parse-result)
					(classp superior))))
		   do
	       (unless (or (null (cdr direct-superiors))
			   other-direct-superiors-not-defined?)
		 (let* ((class-inheritance-paths
			  (let ((paths nil))
			    (loop for superior in direct-superiors
				  do
			      (if (eq superior parse-result)
				  (setq paths
					(nconc paths
					       (frame-list
						 possible-class-inheritance-path?)))
				  (setq paths
					(nconc paths
					       (frame-list
						 (class-inheritance-path
						   (class-description superior)))))))
			    paths)))
		   (multiple-value-setq
		       (prohibited-superior? colliding-superior?)
		     (merging-paths-common-ancestor-rule-2-violation-p
		       class-inheritance-paths))
		   (reclaim-frame-list class-inheritance-paths)
		   prohibited-superior?))))
	(reclaim-slot-value possible-class-inheritance-path?)
	(values bad-phrase
		(direct-superiors-give-ancestors-different-precedence
		  prohibited-superior? colliding-superior?
		  problem-inferior-class?
		  inferior-potential-definition?)))

       (t
	(reclaim-slot-value possible-class-inheritance-path?)
	parse-result))))
      
    (t parse-result)))




;;; `List-of-classes' is a grammar type for the direct-superiors-of-defined-
;;; class slot of object, connection, and message definitions to support
;;; multiple inheritance for user-defined classes.
;;;
;;; There are also four more specific related lists: `list-of-item-classes',
;;; `list-of-object-classes', `list-of-connection-classes',
;;; and `list-of-message-classes'.
;;;
;;; These grammar types are all contained in the list `grammar-categories-
;;; getting-choose-existing-class-feature', which referred to by the menu
;;; construction logic in module FACILITIES for giving class choice menus,
;;; the `choose-existing-class feature'.

(defvar grammar-categories-getting-choose-existing-class-feature
  '(list-of-classes list-of-item-classes list-of-object-classes
    list-of-connection-classes list-of-message-classes))

;; Note that this list substutes for a hard-wired quoted list that used to
;; be in the def-menu for table in FACILITIES, and used to be 
;; '(object-class connection-class message-class).  (MHD 9/10/93)

;; There are two lists analagous to this, i.e., grammar-categories-getting-
;; yes-no-feature and grammar-categories-getting-?-in-attribute-table, in
;; RELATIONS for some reason.  (MHD 9/10/93)


;;; NOTE: List-of-classes should more properly be called list-of-foundation-classes,
;;; but it is not for historical reasons.  It is actually a directory of names of
;;; foundation classes and their subclasses.
;;;
;;; NOTE: I don't believe the list-of-item-classes list grammar is reachable.
;;; Review!  (MHD 5/5/97)

(add-grammar-rules-for-list 'list-of-classes 'foundation-class '\, nil 'none)
(add-grammar-rules-for-list 'list-of-item-classes 'foundation-class '\, nil 'none)
(add-grammar-rules-for-list 'list-of-object-classes 'foundation-object-class '\, nil 'none)
(add-grammar-rules-for-list 'list-of-connection-classes 'foundation-connection-class '\, nil 'none)
(add-grammar-rules-for-list 'list-of-message-classes 'foundation-message-class '\, nil 'none)

(def-slot-value-writer list-of-classes (class-list)
  (write-symbol-list class-list '\, nil 'none))
(def-slot-value-writer list-of-item-classes (class-list)
  (write-symbol-list class-list '\, nil 'none)) 					      
(def-slot-value-writer list-of-object-classes (class-list)
  (write-list-of-classes-from-slot class-list nil))
(def-slot-value-writer list-of-connection-classes (class-list)
  (write-list-of-classes-from-slot class-list nil))
(def-slot-value-writer list-of-message-classes (class-list)
  (write-list-of-classes-from-slot class-list nil))




(def-slot-value-writer class-inheritance-path-of-definition (class-list)
  ;; The car of the class-list will be nil when there is no
  ;; name-of-defined-class.
  (if class-list
      (let ((item-class?
	      (let ((first-superior-foundation-class
		      (second (get-class-feature-if-any
				(second class-list) 'foundation-class))))
		(subclassp first-superior-foundation-class 'item)))
	    (list-to-write
	      (if (car class-list)
		  (frame-list (car class-list))
		  (frame-list 'this-unnamed-class))))
	(loop for class in (cdr class-list)
	      until (if item-class?
			(eq class 'item)
			(null (feature-assq 'foundation-class
					    (class-features (class-description
							      class)))))
	      do
	  (setq list-to-write
		(nconc list-to-write (frame-list class))))
	(when item-class?
	  (setq list-to-write
		(nconc list-to-write (frame-list 'item))))
	(write-list-of-classes-from-slot list-to-write nil)
	(reclaim-frame-list list-to-write))
      (twrite "none")))


(def-slot-value-writer list-of-slots (slot-list)
  (if slot-list
      (let ((write-symbols-parsably? t))
	(loop with first-slot-name? = t
	      for slot-name in slot-list
	      do
	  (if first-slot-name?
	      (setq first-slot-name? nil)
	      (tformat ",~%"))
	  (twrite-symbol slot-name)))
      (twrite "none")))
    
	
      
  



;;;; Forms for supporting pre-4.0 change-the-text-of roles




;;; The following forms are for supporting "the text of" roles and
;;; "change the text of" actions in pre-4.0 kbs for four user-editable
;;; system-defined slots on class definitions that have changed name and
;;; functionality or been discontinued.

;;; slot-name                            alias
;;; ------------------------------------------------------------------
;;; capabilities-of-class                capabilities-and-restrictions
;;;   (discontinued)

;;; default-overrides-of-system-slots    default-settings
;;; (system name is now default-settings)
;;;   (changed to default-overrides,
;;;    aliased to attribute-initializations)

;;; superior-of-defined-class            superior-class
;;;   (changed to direct-superiors-of-defined-class,
;;;    aliased to direct-superior-classes)

;;; attribute-descriptions-for-class     attributes-specific-to-class
;;;   (changed to class-specific-attributes
;;;    (no alias))




;;;; Support for pre 4.0 capabilities and restrictions


(add-grammar-rules
  '((previous-capability 'activatable-subworkspace)
    (previous-capability 'external-simulation)
    (previous-capability 'g2-meter-data-service)
    (previous-capability 'g2-to-g2-data-interface)
    (previous-capability 'g2-to-g2-data-service)
    (previous-capability 'gfi-data-service)
    (previous-capability 'gfi-input-interface)
    (previous-capability 'gfi-output-interface)
    (previous-capability 'gsi-data-service)
    (previous-capability 'gsi-interface-configuration)
    (previous-capability 'gsi-message-service)
    (previous-capability 'no-manual-connection)
    (previous-capability 'subworkspace-connection-posts)))

(add-grammar-rules
  '((previous-capabilities 'none)
    (previous-capabilities previous-capability-list)
    (previous-capability-list previous-capability)
    (previous-capability-list (previous-capability '\, previous-capability-list)
		     (\, 1 3) simplify-associative-operation)))

(def-slot-putter capabilities-and-restrictions (definition new-value)
  (process-pre-4.0-capabilities-of-class
    definition (name-of-defined-class definition) new-value t))

(def-slot-value-writer previous-capabilities (null-value definition)
  (declare (ignore null-value))
  (let* ((direct-superiors? (direct-superiors-of-defined-class definition))
	 (capabilities?
	   (loop for superior in direct-superiors?
		 when (memq
			superior '(gsi-interface g2-to-g2-data-interface
				   gfi-input-interface gfi-output-interface
				   gsi-data-service gsi-message-service
				   gfi-data-service g2-to-g2-data-service
				   g2-meter-data-service))
		   collect superior using frame-cons))
	 (instance-configuration? (instance-configuration definition))
	 (instance-configuration-property-declarations?
	   (loop for clause in instance-configuration?
		 when (eq (car clause) 'declaration)
		   collect clause using frame-cons)))
    (when instance-configuration-property-declarations?
      (loop for declaration in
	          instance-configuration-property-declarations?
	    for activatable-subworkspace-declaration? =
	          (memq 'activatable-subworkspace declaration)
	    for external-simulation-declaration? =
	          (memq 'external-simulation declaration)
	    for manual-connections-declaration? =
	          (memq 'manual-connections declaration)
	    for subworkspace-connection-posts-declaration? =
	          (memq 'subworkspace-connection-posts declaration)
	    do
	(when (and activatable-subworkspace-declaration?
		   (second activatable-subworkspace-declaration?)
		   (not (memq 'activatable-subworkspace capabilities?)))
	  (setq capabilities?
		(nconc capabilities? (frame-list 'activatible-subworkspace))))
	(when (and external-simulation-declaration?
		   (second external-simulation-declaration?)
		   (not (memq 'external-simulation capabilities?)))
	  (setq capabilities?
		(nconc capabilities? (frame-list 'external-simulation))))
	(when (and manual-connections-declaration?
		   (null (second manual-connections-declaration?))
		   (not (memq 'no-manual-connections capabilities?)))
	  (setq capabilities?
		(nconc capabilities? (frame-list 'no-manual-connections))))
	(when (and subworkspace-connection-posts-declaration?
		   (second subworkspace-connection-posts-declaration?)
		   (not (memq 'subworkspace-connection-posts capabilities?)))
	  (setq capabilities?
		(nconc capabilities? (frame-list 'subworkspace-connection-posts))))))
    (write-symbol-list capabilities? '\, nil 'none)))

(def-slot-value-compiler previous-capabilities (translation definition)
  (declare (ignore definition))
  (let ((declared-capabilities
	  (cond
	    ((eq translation 'none) nil)
	    ((symbolp translation) (phrase-cons translation nil))
	    (t (cdr translation)))))
    (if declared-capabilities
	(phrase-list declared-capabilities)
	nil)))




;;;; Support for pre 4.0 default-settings


(add-grammar-rules
  '((old-default-settings 'none)
    (old-default-settings list-of-old-default-settings)

    (list-of-old-default-settings old-default-setting)
    (list-of-old-default-settings (old-default-setting '\; list-of-old-default-settings)
     (2 1 3) simplify-associative-operation)

    (old-default-setting ('data 'type 'for 'sensor '\: data-type)
     (data-type 6 sensor))
    (old-default-setting ('data 'type 'for 'quantitative-variable '\: quantitative-data-type)
     (data-type 6 quantitative-variable))
    (old-default-setting ('data 'type 'for 'quantitative-parameter '\: quantitative-data-type)
     (data-type 6 quantitative-parameter))

    (old-default-setting ('validity 'interval '\: interval) (validity-interval 4))
    (old-default-setting ('validity 'interval '\: 'indefinite) (validity-interval 4))
    (old-default-setting ('validity 'interval '\: 'supplied) (validity-interval 4))
    (old-default-setting ('supply 'simulation 'subtable)
     (simulation-details (:funcall make-simulation-subtable-and-install)))
    (old-default-setting ('data 'server '\: data-server-map) (data-server-map 4))
    (old-default-setting ('default 'update 'interval '\: interval?)
     (default-update-interval 5) second-none)
    (old-default-setting ('default 'update 'interval '\: 'none)
     (default-update-interval nil))
    (old-default-setting ('history 'keeping 'spec '\: history-specification)
     (history-keeping-spec 5))
    (old-default-setting ('options 'for 'variable '\: variable-frame-flags)
			  (frame-flags 5 variable))

    (old-default-setting ('initial 'value 'for 'logical-variable '\: truth-value?)
     (initial-value 6 logical-variable))
    (old-default-setting ('initial 'value 'for 'quantitative-variable '\: number?)
     (initial-value 6 quantitative-variable))
    (old-default-setting ('initial 'value 'for 'float-variable '\: float?)
     (initial-value 6 float-variable))
    (old-default-setting ('initial 'value 'for 'integer-variable '\: integer?)
     (initial-value 6 integer-variable))
    (old-default-setting ('initial 'value 'for 'symbolic-variable '\: symbol?)
     (initial-value 6 symbolic-variable))
    (old-default-setting ('initial 'value 'for 'text-variable '\: whole-string?)
     (initial-value 6 text-variable))

    (old-default-setting ('initial 'value 'for 'logical-parameter '\: truth-value)
     (initial-value 6 logical-parameter))
    (old-default-setting ('initial 'value 'for 'quantitative-parameter '\: number)
     (initial-value 6 quantitative-parameter))
    (old-default-setting ('initial 'value 'for 'float-parameter '\: float)
     (initial-value 6 float-parameter))
    (old-default-setting ('initial 'value 'for 'integer-parameter '\: integer)
     (initial-value 6 integer-parameter))
    (old-default-setting ('initial 'value 'for 'symbolic-parameter '\: symbol)
     (initial-value 6 symbolic-parameter))
    (old-default-setting ('initial 'value 'for 'text-parameter '\: whole-string)
     (initial-value 6 text-parameter))

    (old-default-setting ('initial 'value 'for 'sensor '\: initial-sensor-value?)
     (initial-value 6 sensor))


    (old-default-setting ('element 'type 'for 'item-list '\: class)
     (list-type 6 item-list))

    (old-default-setting ('allow 'duplicate 'elements 'for 'g2-list '\: yes-or-no)
     (insert-duplicate-elements? 7 g2-list))

    (old-default-setting ('element 'type 'for 'item-array '\: class)
     (g2-array-element-type 6 item-array))

    (old-default-setting ('array-length 'for 'g2-array '\: g2-array-length)
     (g2-array-length 5 g2-array))

    (old-default-setting ('initial 'values 'for 'item-array '\: constant-designation-list?)
     (g2-array-initial-values 6 item-array))

    (old-default-setting ('initial 'values 'for 'quantity-array '\: quantity-list)
     (g2-array-initial-values 6 quantity-array))

    (old-default-setting ('initial 'values 'for 'integer-array '\: integer-list)
     (g2-array-initial-values 6 integer-array))

    (old-default-setting ('initial 'values 'for 'float-array '\: float-list)
     (g2-array-initial-values 6 float-array))

    (old-default-setting ('initial 'values 'for 'symbol-array '\: symbol-list)
     (g2-array-initial-values 6 symbol-array))

    (old-default-setting ('initial 'values 'for 'text-array '\: whole-string-list)
     (g2-array-initial-values 6 text-array))

    (old-default-setting ('initial 'values 'for 'truth-value-array '\: truth-value-list)
     (g2-array-initial-values 6 truth-value-array))

    ;; Removed -- duplicate of grammar above. (MHD 5/14/97)
;    (initial-sensor-value? 'none)
;    (initial-sensor-value? truth-value)    
;    (initial-sensor-value? quantity)
;    (initial-sensor-value? symbol)
;    (initial-sensor-value? whole-string)
    ))

(def-slot-value-compiler old-default-settings (translation definition)
  (compile-default-overrides-for-object-definitions-for-slot
    translation definition nil))

(def-slot-putter default-settings (definition new-value)
  (process-pre-4.0-attribute-descriptions-and-default-overrides
    definition (name-of-defined-class definition) nil
    (direct-superiors-of-defined-class definition)
    new-value nil t))

(def-slot-value-writer old-default-settings
    (null-value definition)
  (declare (ignore null-value))
  (let ((value
	  (loop for override in (default-overrides definition)
		when (not (override-is-for-user-defined-slot-p override))
		  collect (copy-tree-using-frame-conses override) using frame-cons)))
    (cond
      ((null value) (twrite-string "none"))
      (t 
       (loop for (override . rest?) on value
	     do (write-default-override override definition)
		(when rest?
		  (tformat ";~%")))
       (if (cdr value)
	   (setq leave-text-representation-as-a-single-line?
		 nil))
       (reclaim-frame-tree value)))))




;;;; Support for pre 4.0 superior-class


(def-grammar-category old-superior-class ()
  (unreserved-symbol))

(def-slot-putter superior-class (definition parse-value)
  (change-slot-value
    definition 'direct-superiors-of-defined-class parse-value))

(def-slot-value-compiler old-superior-class (parse-result frame)
  ;; Parse-result is an unreserved symbol.  Compile-list-of-classes-for-slot
  ;; expects a CONS whose car is the symbol with print name ",", and whose cdr a
  ;; list of unreserved symbols, the names of the desired superior classes.  It
  ;; wants direct-superiors-of-defined-class as the slot name.
  (compile-list-of-classes-for-slot
    (phrase-list '\, parse-result)
    frame
    'direct-superiors-of-defined-class))

(def-slot-value-writer old-superior-class (null-value definition)
  (declare (ignore null-value))
  (let ((direct-superiors? (direct-superiors-of-defined-class definition)))
    (cond ((null direct-superiors?)
	   (twrite-string "none"))
	  (t
	   (let ((symbol-to-write
		   (if (null (cdr direct-superiors?))
		       (let ((superior-class (car direct-superiors?)))
			 (if (memq superior-class
				   '(gsi-interface g2-to-g2-data-interface
				     gfi-input-interface gfi-output-interface))
			     'object
			     superior-class))
		       (loop for superior in direct-superiors?
			     do
			 (unless (memq superior
				       '(gsi-interface g2-to-g2-data-interface
					 gfi-input-interface gfi-output-interface
					 gsi-data-service gsi-message-service
					 gfi-data-service g2-to-g2-data-service
					 g2-meter-data-service))
			   (return superior))))))
	     (twrite-symbol symbol-to-write))))))
		 
		  
		 
    
;;;; Support for pre 4.0 attributes-specific-to-class


(def-slot-putter attributes-specific-to-class (definition new-value)
  (process-pre-4.0-attribute-descriptions-and-default-overrides
    definition (name-of-defined-class definition) new-value
    (direct-superiors-of-defined-class definition) nil t nil))

(def-slot-value-writer old-attribute-descriptions
    (null-value definition)
  (declare (ignore null-value))
  (let* ((class-specific-attributes (class-specific-attributes definition))
	 (default-overrides (default-overrides definition))
	 (overrides-for-user-defined-attributes?
	   (loop for override in default-overrides
		 when (eq (third override) 'user-defined)
		   return t)))
    (if (or class-specific-attributes overrides-for-user-defined-attributes?)
	(let ((old-descriptions-to-write nil))
	  (loop for attribute-description in class-specific-attributes
		for attribute-name = (attribute-name attribute-description)
		for cddr-of-attribute-description = (cddr attribute-description)
		do
	    (setq old-descriptions-to-write
		  (nconc old-descriptions-to-write
			 (frame-list
			   (frame-cons attribute-name
				       (copy-tree-using-frame-conses
					 cddr-of-attribute-description))))))
	  (loop for override in default-overrides
		do
	    (when (eq (third override) 'user-defined)
	      (let* ((name-denotation (first override))
		     (attribute-name (unqualified-name name-denotation))
		     (second-component (second override))
		     (funcalled-attribute?
		       (and (consp (car second-component))
			    (eq (first (car second-component)) ':funcall)))
		     (attribute-value
		       (if funcalled-attribute?
			   (copy-list-using-frame-conses (car second-component))
			   (let ((value (first second-component)))
			     (if (consp value)
				 (copy-list-using-frame-conses value)
				 value))))
		     (attribute-type
		       (if funcalled-attribute?
			   nil
			   (second second-component))))
		(setq old-descriptions-to-write
		      (nconc old-descriptions-to-write
			     (frame-list
			       (frame-list attribute-name attribute-value attribute-type)))))))
	  (loop for sublist on old-descriptions-to-write
		doing (write-old-attribute-description (car sublist) definition)
		when (cdr sublist) do (tformat ";~%"))
	  (reclaim-frame-tree old-descriptions-to-write))
	(twrite-string "none"))))

(defun write-old-attribute-description (description definition)
  (let* ((name (first description))
	 (value (second description))
	 (funcalled-value?
	   (and (consp value) (eq (car value) :funcall)))
	 (type (third description))
	 (indexed-attributes (indexed-attributes-for-definition definition)))

    (twrite-symbol name)
 
    (cond
      ((eq type 'symbol)
       (let ((write-symbols-parsably? t))	; (MHD 2/10/92)
	 (cond
	   ((=i (length description) 3)
	    (if value 
		(progn (twrite " is ") (twrite-symbol value))
		(twrite " is a symbol")))
	   ((=i (length description) 5)
	    (tformat
	      "~( has values ~a or ~a~)" (fourth description) (fifth description))
	    (if (and value (not (consp value)))
		(tformat " (default is ~A)" value)))
	   (t (twrite " has values ")
	      (write-list-in-chicago-style (cdddr description) "or")
	      (if (and value (not (consp value)))
		  (tformat " (default is ~A)" value))))))

      ((eq type 'text)
       (twrite " is ")
       (let ((write-strings-parsably? t))	; (MHD 2/10/92)
	 (twrite-string value)))
      
      (type
       (unless funcalled-value?
	 (twrite " is ")
	 (print-constant value type))))

    (if (and (eq type 'symbol) (consp value)) (twrite " and"))

    (when (and (consp value) (eq (car value) :funcall))
      (twrite (if (eq (second value) 'instantiate-variable)
		  " is given by " " is an instance of "))
      (write-symbol-with-a-or-an (third value)))

    (when (memq name indexed-attributes)
      (twrite ", with an index"))

    ))

(defun fix-old-attribute-description (phrase indexed?)
  (let
    ((fixed-description
       (phrase-cons
	 (car phrase)
	 (cond
	   ((phrase-number-p (cdr phrase))
	    (phrase-list (cdr phrase) 'number))
	   ((memq (cdr phrase) '(true false))
	    (phrase-list (case (cdr phrase) (true 1000) (t -1000))
			 'truth-value))  
	   ((symbolp (cdr phrase))
	    (phrase-list (cdr phrase) 'symbol))
	   ((text-string-p (cdr phrase))
	    (phrase-list (cdr phrase) 'text))
	   #+development
	   ((atom (cdr phrase))
	    (error "~s is not expected in the cdr of the phrase ~s."
		   (cdr phrase) phrase))
	   ;; (cdr phrase) is a cons
	   ((and (phrase-number-p (car (cdr phrase)))
		 (eq (cdr (cdr phrase)) 'truth-value))
	    (phrase-list
	      (with-temporary-gensym-float-creation fix-attribute-description
		(round (* 1000 (phrase-number-value (car (cdr phrase))))))
	      'truth-value))
	   ((and (phrase-number-p (car (cdr phrase)))
		 (symbolp (cdr (cdr phrase))))
	    ;; (attribute-name phrase-number . unit-of-measure) case
	    (phrase-list
	      (car (cdr phrase))
	      (cdr (cdr phrase))))
	   #+development
	   (t
	    (error "~s is not a valid phrase here." phrase))))))
    (if indexed?
	(nconc fixed-description (phrase-list (phrase-list 'indexed)))
	fixed-description)))

(add-grammar-rules
  '((a-or-an 'a)
    (a-or-an 'an)
    
    (old-attribute-descriptions 'none)
    (old-attribute-descriptions old-attribute-descriptions-1)
    
    (old-attribute-descriptions-1 old-attribute-description)
    (old-attribute-descriptions-1 (old-attribute-description '\; old-attribute-descriptions-1)
			      (2 1 3) simplify-associative-operation)
    
    (old-attribute-description
      attribute-name)
    (old-attribute-description
      (attribute-name 'is old-attribute-constant)
      (1 . 3) (fix-old-attribute-description nil))
    (old-attribute-description
      (attribute-name 'is number 'true)
      (1 3 .  truth-value) (check-range-of-element 2 -1 1) (fix-old-attribute-description nil))
    (old-attribute-description
      (attribute-name 'is symbol)
      (1 . 3) (fix-old-attribute-description nil))
    (old-attribute-description
      (attribute-name 'is 'given 'by a-or-an variable-or-parameter-class)
      (1 (:funcall instantiate-variable 6) nil))
    (old-attribute-description
      (attribute-name 'is 'an 'instance 'of a-or-an class)
      (1 (:funcall instantiate-object-in-attribute 7) nil))
    (old-attribute-description
      (attribute-name 'has 'values symbolic-value 'or symbolic-value)
      (1 nil symbol 4 6))
    (old-attribute-description
      (attribute-name 'has 'values symbolic-value-list)
      (1 nil symbol . 4) cut-out-fourth-element)
    (old-attribute-description
      (attribute-name 'has 'values symbolic-value 'or symbolic-value
		      '\( 'default 'is symbolic-value '\) )
      (1 10 symbol 4 6) memq-2-cdddr)
    (old-attribute-description
      (attribute-name 'has 'values symbolic-value-list
		      '\( 'default 'is symbolic-value '\) )
      (1 8 symbol . 4) cut-out-fourth-element memq-2-cdddr)
    (old-attribute-description
      (attribute-name 'has 'values symbolic-value 'or symbolic-value
		      'and 'is 'given 'by a-or-an variable-or-parameter-class)
      (1 (:funcall instantiate-variable 12) symbol 4 6))
    (old-attribute-description
      (attribute-name 'has 'values symbolic-value-list
		      'and 'is 'given 'by a-or-an variable-or-parameter-class)
      (1 (:funcall instantiate-variable 10) symbol . 4) cut-out-fourth-element)

    ;; Indexed Attributes

    (old-attribute-description (attribute-name '\, 'with 'an 'index)
			   (1 nil nil (indexed)))
    (old-attribute-description
      (attribute-name 'is old-attribute-constant '\, 'with 'an 'index)
      (1 . 3) (fix-old-attribute-description t))
    (old-attribute-description
      (attribute-name 'is number 'true '\, 'with 'an 'index)
      (1 3 .  truth-value) (check-range-of-element 2 -1 1) (fix-old-attribute-description t))
    (old-attribute-description
      (attribute-name 'is symbol '\, 'with 'an 'index)
      (1 . 3) (fix-old-attribute-description t ))

    (old-attribute-description
      (attribute-name 'is 'given 'by a-or-an variable-or-parameter-class
		      '\, 'with 'an 'index)
      (1 (:funcall instantiate-variable 6) nil (indexed)))
    (old-attribute-description
      (attribute-name 'is 'an 'instance 'of a-or-an class
		      '\, 'with 'an 'index)
      (1 (:funcall instantiate-object-in-attribute 7) nil (indexed)))

    (old-attribute-description
      (attribute-name 'has 'values symbolic-value 'or symbolic-value
		      '\, 'with 'an 'index)
      (1 nil symbol (indexed) 4 6))
    (old-attribute-description
      (attribute-name 'has 'values symbolic-value-list '\, 'with 'an 'index)
      (1 nil symbol (indexed) . 4) cut-out-fifth-element)
    (old-attribute-description
      (attribute-name 'has 'values symbolic-value 'or symbolic-value
		      '\( 'default 'is symbolic-value '\)
		      '\, 'with 'an 'index)
      (1 10 symbol (indexed) 4 6) memq-2-cddddr)
    (old-attribute-description
      (attribute-name 'has 'values symbolic-value-list
		      '\( 'default 'is symbolic-value '\)
		      '\, 'with 'an 'index)
      (1 8 symbol (indexed) . 4) cut-out-fifth-element memq-2-cddddr)

    (old-attribute-description
      (attribute-name 'has 'values symbolic-value 'or symbolic-value
		      'and 'is 'given 'by a-or-an variable-or-parameter-class
		      '\, 'with 'an 'index)
      (1 (:funcall instantiate-variable 12) symbol (indexed) 4 6))
    (old-attribute-description
      (attribute-name 'has 'values symbolic-value-list
		      'and 'is 'given 'by a-or-an variable-or-parameter-class
		      '\, 'with 'an 'index)
      (1 (:funcall instantiate-variable 10) symbol (indexed) . 4) cut-out-fifth-element)))

(def-slot-value-compiler old-attribute-descriptions (parse-result definition)
  (let ((transformed-value
	  (cond
	    ((eq parse-result 'none) nil)
	    ((symbolp parse-result)
	     (phrase-list (phrase-list parse-result nil nil)))
	    
	    ((eq (car parse-result) '\;)
	     (prog1
		 (cdr parse-result)
	       (loop for listed-attribute-description on (cdr parse-result) do
		 (if (symbolp (car listed-attribute-description))
		     (setf (car listed-attribute-description)
			   (phrase-list (car listed-attribute-description) nil nil)
			   )))))
	    
	    (t (phrase-cons parse-result nil)))))
    
    (loop for listed-attribute-description on transformed-value
	  for attribute-description = (car listed-attribute-description) doing
      (if (member (car attribute-description)
		  (cdr listed-attribute-description) :test 'car-eq)
	  (return-from compile-old-attribute-descriptions-for-slot
	    (values bad-phrase
		    (copy-constant-wide-string #w"This attribute list has duplicate names.")))))
    
    (loop for attribute-description in transformed-value
	  for (attribute-name nil nil indexed? . rest) = attribute-description
	  when (equal indexed? '(indexed))
	    collect attribute-name into indexed-attributes
	      using slot-value-cons and
	    (setf (cdddr attribute-description) rest)
	  finally
	    ;; I'd like to replace this with a call to
	    ;; prepare-for-indexed-attributes-moveage, but that does a reclaim of
	    ;; the old-value-of-indexed-attributes. Maybe a reclaim should be
	    ;; done here too, or maybe it's not being done on purpose.  Anyway,
	    ;; I think this compiler and friends are around mostly for backwards
	    ;; compatibility, so I'm just going to leave it alone. -dkuznick, 3/2/01
	    (setf (old-value-of-indexed-attributes definition)
		  (indexed-attributes-for-definition definition))
	    (setf (indexed-attributes-for-definition definition)
		  indexed-attributes))
    
    transformed-value))



(def-slot-value-compiler list-of-item-classes (parse-result frame slot-name)
  (compile-list-of-classes-for-slot parse-result frame slot-name))
(def-slot-value-compiler list-of-object-classes (parse-result frame slot-name)
  (compile-list-of-classes-for-slot parse-result frame slot-name))
(def-slot-value-compiler list-of-connection-classes (parse-result frame slot-name)
  (compile-list-of-classes-for-slot parse-result frame slot-name))
(def-slot-value-compiler list-of-message-classes (parse-result frame slot-name)
  (compile-list-of-classes-for-slot parse-result frame slot-name))


;; Note that as of version 4.0, the "list-of-classes" slot of definitions is no
;; longer restricted from being modified while G2 is running or paused, or when
;; there are instances.  - cpm, 3/14/94

(def-slot-value-compiler list-of-classes (parse-result definition slot-name)
  (declare (ignore slot-name))
  (let* ((direct-superior-classes?
	   (if (consp parse-result) (cdr parse-result) nil)))
    (cond
      ((equal direct-superior-classes?
	      (direct-superiors-of-defined-class definition))
       ;; If new = previous direct superiors, then OK
       direct-superior-classes?)
      (t
       (let* ((possible-class-inheritance-path?
		(if (direct-superiors-are-defined-p direct-superior-classes?)
		    (make-class-inheritance-path-for-user-defined-class
		      (name-of-defined-class definition)
		      direct-superior-classes?)))
	      (error-string?
		(do-valid-superior-tests
		    direct-superior-classes?
		  definition
		  possible-class-inheritance-path?)))
	 (if error-string?
	     (values bad-phrase error-string?)
	     direct-superior-classes?))))))

;; Most of the code previously above moved to the new subsection "Testing for
;; Valid Superior Classes" in DEFINITIONS, which in turn was pulled out of
;; invalid-set-of-direct-superior-classes-p, a subfunction of the putter
;; for direct-superior-classes. (MHD 10/26/01)




(add-grammar-rules
    '((new-class unreserved-symbol)		; replace uses with class?! (MHD)
      (new-class 'none)
      (class unreserved-symbol)
      (g2-window-class unreserved-symbol)
      (object-class unreserved-symbol)
      (message-class unreserved-symbol)
      (item-class unreserved-symbol)
      (junction-class unreserved-symbol)
      (simulation-subtable-class unreserved-symbol)
      (connection-class unreserved-symbol)

    (item-name unreserved-symbol)
    (g2-window-name unreserved-symbol)    
    (object-name unreserved-symbol)
    (procedure-name unreserved-symbol)
    (method-name unreserved-symbol)
;    (variable-or-parameter-name variable-name)
;    (variable-or-parameter-name parameter-name)
;    (variable-name unreserved-symbol)
;    (parameter-name unreserved-symbol)
    ;; Replaced above 4 entries with the following 1 entry:  (MHD 5/31/90)
    ;;   Also see add-or-delete-name-for-frame in FRAMES4. -mhd
    ;;   Note that the use of parameter-name here conflicted with its
    ;;     use for the function declaration grammar, elsewhere; this change
    ;;     makes that moot point.  -mhd
    (variable-or-parameter-name unreserved-symbol)
;    (variable-class unreserved-symbol)
;    (parameter-class unreserved-symbol)
;    (variable-or-parameter-class variable-class)
;    (variable-or-parameter-class parameter-class)
    ;; The previous four forms have been superceded by the
    ;;   following one form:          (MHD 6/1/90)
    (variable-or-parameter-class unreserved-symbol)
    (workspace-name unreserved-symbol)


    ;; Item-name unites all of the name categories that
    ;;   are used for all of the various types of designations: designation,
    ;;   e-designation, constant-designation, etc.
    ;;
    ;; Review this list.  The minimal thing to make it is simply item-name.
    ;; Consider also: connection-name, g2-window-name, message-name, etc.
    ;; (MHD 6/7/90) 

    (item-name workspace-name)
    (item-name message-name)
    (item-name object-name)
    (item-name procedure-name)
    (item-name g2-window-name)
    (object-name variable-or-parameter-name)
    (object-name g2-window-name)
    ))	; added. (MHD 6/14/90)
    

;; ;; Obsolete - only object-class and message-class needed for DEFINITIONS.
;; ;; (Note that class used to be called class-name; If this were reactivated
;; ;; now that class-name was renamed class, the type feature for class slots
;; ;; would have to be changed to some new name other than CLASS (say X), and
;; ;; the writer for CLASS in TABLES would have to be made the write for X.)
;; ;; (MHD 6/6/90)
;; ;;
;; -- NOT OBSOLETE ANYMORE! CLASS, used as the type feature for
;; the class slot, was changed to CLASS-INSTANCE-HEADER, and this has been
;; reactivated because the writer is needed for the first-class and second-
;; class slots of relations.  (MHD 6/19/90)

(def-slot-value-writer-as-existing-function
  class write-symbol-from-slot)

(def-slot-value-writer-as-existing-function
  item-class write-symbol-from-slot)

(def-slot-value-writer-as-existing-function
  message-class write-symbol-from-slot)

(def-slot-value-writer-as-existing-function
  object-class write-symbol-from-slot)

(def-slot-value-writer-as-existing-function
  junction-class write-symbol-from-slot)

(def-slot-value-writer-as-existing-function
  simulation-subtable-class write-symbol-from-slot)  

(def-slot-value-writer-as-existing-function
  new-class write-symbol-from-slot)

(def-slot-value-writer-as-existing-function
  connection-class write-symbol-from-slot)



(def-slot-value-writer-as-existing-function
  object-name write-symbol-from-slot)




(defun cut-out-fourth-element (list)
  (nconc
    (phrase-list (first list) (second list) (third list))
    (copy-list-using-phrase-conses (cddddr list))))

(defun cut-out-fifth-element (list)
  (nconc
    (phrase-list (first list) (second list) (third list) (fourth list))
    (copy-list-using-phrase-conses (cdddr (cddr list)))))

(defun cut-out-sixth-element (list)
  (nconc
    (phrase-list (first list) (second list) (third list)
		 (fourth list) (fifth list))
    (copy-list-using-phrase-conses (cdddr (cdddr list)))))

#+unused
(defun cut-out-fourth-element-and-initialize (list)
  (prog1 list
	 (setf (cdddr list) (cddddr list))
	 (setf (second list) (fourth list))
	 ))

(defun memq-2-cdddr (list)
  (if (memq (second list) (cdddr list)) list bad-phrase))

(defun memq-2-cddddr (list)
  (if (memq (second list) (cddddr list)) list bad-phrase))

(defun memq-3-cddddr (list)
  (if (memq (third list) (cddddr list)) list bad-phrase))

(defun memq-3-cdr-cddddr (list)
  (if (memq (third list) (cdr (cddddr list))) list bad-phrase))


;;; `Check-truth-value-range' checks the value for attribute descriptions.
;;; The input list is in the form:
;;;  ((attribute-name initial-value truth-value) [truth-value])

#+unused
(defun-simple check-truth-value-range (list minimum maximum)
  (let ((initial-value (second (car list))))
    (with-temporary-gensym-float-creation check-range-of-element
      (let* ((element-value
	       (phrase-number-value initial-value)))
	(if (or (< element-value (phrase-number-value minimum))
		(> element-value (phrase-number-value maximum)))
	    bad-phrase
	    list)))))


;;; `Check-truth-value-range-for-override' checks the value for default
;;; overrides on user-defined inherited slots.
;;; The input list is in the form:
;;;  (attribute-name (initial-value . truth-value) user-defined)

#+unused
(defun-simple check-truth-value-range-for-override (list minimum maximum)
  (let ((initial-value (car (second list))))
    (with-temporary-gensym-float-creation check-range-of-element
      (let* ((element-value
	       (phrase-number-value initial-value)))
	(if (or (< element-value (phrase-number-value minimum))
		(> element-value (phrase-number-value maximum)))
	    bad-phrase
	    list)))))
	 




;;; Compiling attribute descriptions checks for duplicate names, and for
;;; system names, both of which are illegal. It also moves the  spec for
;;; an indexed attribute elsewhere. If an attribute description has
;;; '(listed) as its fourth element, this is excised. The names of such
;;; attributes are collected and put on a list in
;;; indexed-attributes-for-definition of the definition. The only ways to
;;; change the attribute descriptions are to edit this slot or to rename
;;; an attribute using change. Code to maintain
;;; indexed-attributes-for-definition has been put into rename-attribute.

;; Note that as of version 4.0, the ATTRIBUTE-DESCRIPTIONS slot of definitions
;; is no longer restricted from being modified while G2 is running or paused, or
;; when there are instances.  - cpm, 3/14/94

(def-slot-value-compiler attribute-descriptions (parse-result definition)
  (let ((transformed-value
	  (cond
	    ((eq parse-result 'none) nil)
	    ((symbolp parse-result)
	     (phrase-list (phrase-list parse-result nil nil)))
	    ((eq (car parse-result) 'normalized-parse)
	     (cdr parse-result))
	    ((eq (car parse-result) '\;)
	     (prog1
		 (cdr parse-result)
	       (loop for listed-attribute-description on (cdr parse-result) do
		 (if (symbolp (car listed-attribute-description))
		     (setf (car listed-attribute-description)
			   (phrase-list (car listed-attribute-description) nil nil)
			   )))))
	    
	    (t (phrase-cons parse-result nil)))))

    (loop for listed-attribute-description on transformed-value
	  for attribute-description = (car listed-attribute-description) doing
      (if (member (car attribute-description)
		  (cdr listed-attribute-description) :test 'car-eq)
	  (return-from compile-attribute-descriptions-for-slot
	    (values bad-phrase
		    (copy-constant-wide-string #w"This attribute list has duplicate names.")))))
    
    
    (let ((bad-attribute-name? nil)
	  (not-a-variable-or-parameter? nil)
	  (type-not-a-variable-or-parameter? nil)
	  (not-an-instantiable-variable-or-parameter-class? nil)
	  (not-an-object? nil)
	  (type-not-an-object?)
	  (not-an-instantiable-object-class? nil)
	  (initial-value-does-not-conform-to-type? nil)
	  (non-type-conforming-class-value? nil)
	  (class-type-designation-specifies-a-g2-type nil))
      
      (loop for (name attribute-definition-type initial-value initial-type . nil)
		in transformed-value
	    as type-specification = (attribute-definition-type-specification attribute-definition-type)
	    do
	(cond ((not (parsed-attribute-initial-value-matches-type-p
		      initial-value type-specification))
	       (setq initial-value-does-not-conform-to-type? name)
	       (loop-finish))
	      ((reserved-system-slot-name-p definition name)
	       (setq bad-attribute-name? name) (loop-finish))
	      ((and (consp initial-value)
		    (eq (car-of-cons initial-value) ':funcall))
	       (let ((initial-value-is-defined-class? (classp initial-type))
		     (class-type?
		       (and (consp type-specification)
			    (eq (car-of-cons type-specification) 'class)
			    (second type-specification))))
		 (cond ((type-specification-for-user-or-datum-type initial-type)
			(setq class-type-designation-specifies-a-g2-type
			      initial-type)
			(loop-finish))
		       ((eq (second initial-value) 'instantiate-variable)
			(cond ((and (classp class-type?)
				    (or (not (subclassp
					       class-type?
					       'variable-or-parameter))
					(get-class-feature-if-any
					  class-type? 'not-user-instantiable)))
			       (setq type-not-a-variable-or-parameter? name)
			       (setq not-an-instantiable-variable-or-parameter-class?
				     class-type?)
			       (loop-finish))
			      (initial-value-is-defined-class?
			       (cond ((or (not (subclassp initial-type
							  'variable-or-parameter))
					  (get-class-feature-if-any
					    initial-type 'not-user-instantiable))
				      (setq not-a-variable-or-parameter? name)
				      (setq not-an-instantiable-variable-or-parameter-class?
					    initial-type)
				      (loop-finish))
				     ((and (classp class-type?)
					   (not (subclassp initial-type class-type?)))
				      (setq non-type-conforming-class-value? name)
				      (loop-finish))
				     (t nil)))
			      (t nil)))
		       (t
			(cond ((and (classp class-type?)
				    (or (not (subclassp class-type? 'object))
					(get-class-feature-if-any
					  class-type? 'not-user-instantiable)))
			       (setq type-not-an-object? name)
			       (setq not-an-instantiable-object-class? class-type?)
			       (loop-finish))
			      (initial-value-is-defined-class?
			       (cond ((or (not (subclassp initial-type 'object))
					  (get-class-feature-if-any
					    initial-type 'not-user-instantiable))
				      (setq not-an-object? name)
				      (setq not-an-instantiable-object-class?
					    initial-type)
				      (loop-finish))
				     ((and (classp class-type?)
					   (not (subclassp initial-type class-type?)))
				      (setq non-type-conforming-class-value? name)
				      (loop-finish))
				     (t nil)))
			      (t nil))))))
	      (t nil)))

      (cond
	(bad-attribute-name?
	 (bad-attribute-name bad-attribute-name?))
	(not-a-variable-or-parameter?
	 (values
	   bad-phrase
	   (tformat-text-string
	     "The class given for attribute ~A (~(~a~)) is not an ~
                  instantiable variable or parameter."
	     not-a-variable-or-parameter?
	     not-an-instantiable-variable-or-parameter-class?)))
	(type-not-a-variable-or-parameter?
	 (values
	   bad-phrase
	   (tformat-text-string
	     "The class type-specification given for attribute ~A ~
                  (~(~a~)) is not an instantiable variable or parameter."
	     type-not-a-variable-or-parameter?
	     not-an-instantiable-variable-or-parameter-class?)))
	(initial-value-does-not-conform-to-type?
	 (values
	   bad-phrase
	   (tformat-text-string
	     "The initial value for attribute ~A does not conform to ~
                the given type specification."
	     initial-value-does-not-conform-to-type?)))
	(non-type-conforming-class-value?
	 (values
	   bad-phrase
	   (tformat-text-string
	     "The initial value for attribute ~A is not a subclass ~
                  of its declared type."
	     non-type-conforming-class-value?)))
	(not-an-object?
	 (values
	   bad-phrase
	   (tformat-text-string
	     "The class given for attribute ~A (~(~a~)) is not an ~
                  instantiable object."
	     not-an-object?
	     not-an-instantiable-object-class?)))
	(type-not-an-object?
	 (values
	   bad-phrase
	   (tformat-text-string
	     "The class type-specification given for attribute ~A ~
                  (~(~a~)) is not an instantiable object."
	     type-not-an-object?
	     not-an-instantiable-object-class?)))
	(class-type-designation-specifies-a-g2-type
	 (values
	   bad-phrase
	   (tformat-text-string
	     "~A cannot be the name of a class because it specifies a ~
                  type in G2." class-type-designation-specifies-a-g2-type)))
	(t
	 (loop for attribute-description in transformed-value
	       for (attribute-name nil initial-value nil indexed? . rest)
		   = attribute-description
	       when (equal indexed? '(indexed))
		 collect attribute-name into indexed-attributes
		   using slot-value-cons and
		 (setf (cddddr attribute-description) rest)
	       finally
		 (prepare-for-indexed-attributes-moveage
		   definition
		   (indexed-attributes-for-definition definition)
		   indexed-attributes))
	 transformed-value)))))



(defun system-class-is-not-user-subclassable-p (class)
  (loop for subclass being each subclass of class
	never (get-foundation-class-for-class subclass)))

(def-global-property-name cached-system-slot-is-present-only-on-non-user-subclassable-system-slots)

(defun system-slot-is-present-only-on-non-user-subclassable-system-slots (symbol)
  (let ((value (cached-system-slot-is-present-only-on-non-user-subclassable-system-slots symbol 'unknown)))
    (when (eq value 'unknown)
      (setq value (not (system-slot-is-user-subclassable-1 'item symbol)))
      (setf (cached-system-slot-is-present-only-on-non-user-subclassable-system-slots symbol) value))
    value))

(defun system-slot-is-user-subclassable-1 (class symbol)
  (unless (or (user-defined-class-p class)
	      (system-class-is-not-user-subclassable-p class))
    (or (slot-description-from-class class symbol)
	(loop for subclass in (inferior-classes class)
	      thereis (system-slot-is-user-subclassable-1 subclass symbol)))))


;;; The function `reserved-system-slot-name-p' is used to check whether a
;;; user-defined attribute can have the symbol as a name.  It will return a
;;; non-null value when the symbol is any unaliased system-defined slot name or
;;; is an aliased slot name for any class that can be user-subclassed on
;;; the class type of definition being used.  Note that three non-object/message/
;;; connection classes (item, unique-identification, gsi-message-service)
;;; can be mixed into their corresponding definitions, but their slots are
;;; not aliased.

(defun reserved-system-slot-name-p (definition symbol)
  (or (eq symbol 'class)
      (and (slot-category-macro symbol)
	   (not (system-slot-is-present-only-on-non-user-subclassable-system-slots symbol)))
      (let* ((object-definition?
	       (frame-of-class-p definition 'object-definition))
	     (message-definition?
	       (frame-of-class-p definition 'message-definition))
	     (connection-definition?
	       (frame-of-class-p definition 'connection-definition)))
	(loop for (class . nil) in (slot-names-for-alias symbol)
	      thereis
	      (or (null class)
		  (loop for class being each subclass of class
			for class-description = (class-description class)
			thereis
			(and class-description
			     (cond (object-definition?
				    (subclassp class 'object))
				   (message-definition?
				    (subclassp class 'message))
				   (connection-definition?
				    (subclassp class 'connection))
				   (t t))
			     ;; This makes unreachable system slot aliases
			     ;; (for example, x, y, height, width) available
			     ;; for user-defined attribute names.  Hopefully
			     ;; there are few semi-reachable aliases.
			     (feature-assq
			       'foundation-class
			       (class-features class-description)))))))))




(defun badly-formed-attribute-name ()
  (values
    bad-phrase
    (tformat-text-string
      "There is a badly formed class-qualified attribute name.")))

(defun bad-attribute-name (attribute-name)
  (values
    bad-phrase
    (tformat-text-string
      "~A is the name of a G2 system attribute and cannot be a user-defined attribute."
      attribute-name)))

(defun system-slot-override-but-no-foundation-class (slot-name)
  (values
    bad-phrase
    (tformat-text-string "The direct superiors of a class must be complete before ~
                          placing an initialization on ~a because it is a built-in ~
                          attribute that requires specific built-in class inheritance."
			 slot-name)))




;;; The function `attribute-initial-value-matches-type-p' returns a non-null
;;; value when the initial value conforms to the type specification in a
;;; parsed definition for a class-specific-attribute.  Note that initial values can
;;; be phrase constants.

(defun-simple parsed-attribute-initial-value-matches-type-p
    (initial-value type-specification)
  (cond
    ;; Check object initial-values.
    ((and (consp initial-value) (eq (car-of-cons initial-value) :funcall))
     (cond ((class-type-specification-p type-specification)
	    (let ((type-specification-class
		    (type-specification-class type-specification))
		  (class-for-instantiation (third initial-value)))
	      (or (not (classp class-for-instantiation))
		  (not (classp type-specification-class))
		  (subclassp class-for-instantiation type-specification-class))))
	   (t
	    (or (equal type-specification '(or item-or-datum (no-item)))
		(eq type-specification 'item-or-datum)))))
    ((phrase-structure-p initial-value)
     (or (structure-type-specification-p type-specification)
	 (eq type-specification 'datum)
	 (eq type-specification 'item-or-datum)
	 (equal type-specification '(or item-or-datum (no-item)))))
    ((phrase-sequence-p initial-value)
     (or (sequence-type-specification-p type-specification)
	 (eq type-specification 'datum)
	 (eq type-specification 'item-or-datum)
	 (equal type-specification '(or item-or-datum (no-item)))))
    ((eq type-specification 'truth-value)
     (<=f -1000 initial-value 1000))
    (t (type-specification-type-p initial-value type-specification))))






;;; `Check-value-attribute-initialization-type' determines whether the
;;; initialization type of a value attribute description is a subtype of the
;;; attribute type specification.  If it is not, it issues a bad phrase message
;;; in the compiler.

;; The input to this function is in this form:
;; ((attribute-name initial-value initial-type) type-specification)


(defun check-value-attribute-initialization-type (list)
  (let* ((attribute-name (first (car list)))
	 (initial-value-phrase (second (car list)))
	 (initial-value
	   ;; units-of-measure are a consed constant
	   (if (and (consp initial-value-phrase)
		    (not (phrase-sequence-p initial-value-phrase))
		    (not (phrase-structure-p initial-value-phrase))
		    (not (truth-value-phrase-p initial-value-phrase)))
	       (car-of-cons initial-value-phrase)
	       initial-value-phrase))
	 (attribute-definition-type (second list))
	 (type-specification
	   (attribute-definition-type-specification attribute-definition-type))
	 (type-matches-initial-value-p
	   (cond
	     ((phrase-structure-p initial-value)
	      (or (structure-type-specification-p type-specification)
		  (eq type-specification 'datum)
		  (eq type-specification 'item-or-datum)))
	     ((phrase-sequence-p initial-value)
	      (or (sequence-type-specification-p type-specification)
		  (eq type-specification 'datum)
		  (eq type-specification 'item-or-datum)))
	     ((eq type-specification 'truth-value)
	      ;; "truth-value-type-specification-p"?
	      (truth-value-phrase-p initial-value))
	     ;; In the above cases, phrase constants don't look like evaluation
	     ;; values, but in the rest of the possible cases, they do, so we
	     ;; can use the following test, which only really works for
	     ;; evaluation values.  We could use something like this that works
	     ;; for phrase values!
	     (t (type-specification-type-p initial-value type-specification)))))
    (if type-matches-initial-value-p
	list
	(values
	  bad-phrase
	  (tformat-text-string		; see notes below
	    "The initial value for attribute ~A does not conform to ~
                the given type specification."
	    attribute-name)))))

(declare-grammar-transform-can-return-bad-phrase check-value-attribute-initialization-type)

;; Note: the string is the similar to one in the compiler.  This is hopefully to keep us
;; from getting that far when we can see the problem here already.
;;
;; Note: the way the parser/editor works now, if the bad phrase still leaves other
;; goal phrases to pursue, the problem string will not be shown; even if the user hits
;; end then, the problem will be "this cannot be parsed".  If it's the only possibility,
;; the warning will be shown.  For example, entering
;;
;;   foo is a quantity, initially is true
;;
;; and hitting end causes "this is incomplete" to be displayed, while
;;
;;   foo is a quantity, initially is true, with an index
;;
;; causes "The initial value for attribute FOO does not conform to the given
;; type specification" to be displayed.  This is not a bug, but is admittedly a
;; disappointment.  It's hard to think of an easy way to solve this.
;;
;; (MHD 5/15/97)




;; The input to this function is in this form:
;; ((attribute-name initial-type) type-specification) and the return is
;; ((attribute-name initial-value initial-type) type-specification)

(defun add-initial-value-for-declared-type (list)
  (let* ((attribute-definition-type (cadr list))
	 (type-specification
	   (attribute-definition-type-specification attribute-definition-type))
	 (initial-value
	   (cond ((symbolic-type-specification-p type-specification)
		  (case type-specification
		    (text (copy-for-phrase #w""))
		    (truth-value (make-truth-value-phrase truth))
		    (symbol 'g2)
		    (integer 'zero)
		    (t (make-phrase-float 0.0))))
		 ((structure-type-specification-p type-specification)
		  (make-phrase-structure '()))
		 ((sequence-type-specification-p type-specification)
		  (make-phrase-sequence '()))
		 (t
		  (make-phrase-float 0.0))))) ; isn't life stupid
    (phrase-list
      (phrase-list (car (car list)) initial-value attribute-definition-type)
      attribute-definition-type)))




;;; `Fix-attribute-description' is called with some of the attribute-description
;;; phrases. When its second argument is t, it is indexed.
;;;
;;; Fix-attribute-description now gets a second argument that specifies whether
;;; ", with an index" was present in the original grammar. For those grammar rules
;;; which call fix-attribute-description, this information is not found in the
;;; parsed form. If present, '(indexed) is added as the fifth element of the
;;; attribute-description. (But note that the slot compiler takes it out again,
;;; and stores it elsewhere in a different form.)

;;; The phrase argument is in this form:
;;;    ((attribute-name initial-value [initial-type]) [type-specification])

(defun fix-attribute-description (phrase indexed?)
  (let* ((initialization-phrase (car phrase))
	 (attribute-name (car initialization-phrase))
	 (initial-value
	   (if (eq (second initialization-phrase) 'zero)
	       0
	       (second initialization-phrase)))
	 ;; (initial-type (third initialization-phrase))
	 (type-specification
	   (or (second phrase)
	       (copy-list-using-phrase-conses '(or item-or-datum (no-item))))))
    (nconc
      (phrase-list attribute-name)
      (phrase-list type-specification)
      (fix-attribute-description-initial-value initial-value indexed?)
      (if indexed? (phrase-list (phrase-list 'indexed))))))


;;; Fix-attribute-description-initial-value is a subfunction of
;;; fix-attribute-description.  Generally, the initial-value phrase is turned
;;; into a slot constant.  But there are also a few peculiar subtleties.

(defun-simple fix-attribute-description-initial-value (initial-value indexed?)
  (cond
    ((truth-value-phrase-p initial-value)
     (phrase-list (car initial-value) 'truth-value))
    ((phrase-number-p initial-value)
     (phrase-list initial-value 'number))
    ((null initial-value)
     (if indexed?
	 (phrase-list nil nil)
	 nil))
    ((symbolp initial-value)
     (phrase-list initial-value 'symbol))    
    ((text-string-p initial-value)
     (phrase-list initial-value 'text))    
    ((and (consp initial-value)
	  (phrase-number-p (car initial-value))
	  (symbolp (cdr initial-value)))
     ;; (attribute-name phrase-number . unit-of-measure) case
     ;; initial-value is a unit-of-measure phrase
     (phrase-list
       (car initial-value)
       (cdr initial-value)))

    ((phrase-sequence-p initial-value)
     (phrase-list
       initial-value
       (copy-for-phrase '(sequence))))	; can copy be avoided?
    ((phrase-structure-p initial-value)
     (phrase-list
       initial-value
       (copy-for-phrase '(structure))))	; can copy be avoided?
    
    ((and (consp initial-value)
	  (eq (car initial-value) :funcall)
	  (consp (cdr initial-value))
	  (or (eq (cadr initial-value) 'instantiate-object-in-attribute)
	      (eq (cadr initial-value) 'instantiate-variable))
	  (consp (cddr initial-value))
	  (null (cdddr initial-value)))
     (phrase-list initial-value (caddr initial-value)))
    
    ((and (listp initial-value)
	  (eq 'truth-value (cadr initial-value)))
     initial-value)

    #+development
    (t
     (cerror "Continue"
	     "~s is not a valid initial value phrase." initial-value))))




(def-slot-value-compiler symbolic-value-list (parse-result)
  (fix-up-symbolic-value-list parse-result))


(defun fix-up-symbolic-value-list (symbolic-value-list)
  (cond ((null symbolic-value-list) nil)
	((eq symbolic-value-list 'none) nil)
	((eq (car symbolic-value-list) '\,)
	 (cdr symbolic-value-list))
	(t (phrase-cons symbolic-value-list nil))))



(defun variable-spec-transform (variable-specification-list)
  (loop with result = nil
	with spec-list = (cdr variable-specification-list)
	for (name value) in spec-list
	do
    (phrase-push name result)
    (phrase-push value result)
	finally
	  (return (nreverse result))))
	
  

#+development
(defun variable-spec-transform2 (variable-specification-list)
  (break)
  variable-specification-list)

;; End file with CR.




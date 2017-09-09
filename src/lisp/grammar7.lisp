;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module GRAMMAR7

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Michael Levin and Mark H. David






(declare-forward-references-to-module
  g2-meters
  (g2-meter-names-and-forms variable))

(declare-forward-references
  (initialize-ui-options-on-all-workstations function commands2)
  (set-deadlock-detection-frequency function STACK-UTILS)
  (get-property-value-in-object-configuration function FILTERS))


;;;; Grammar for data-server-map

(add-grammar-rules
  '(

    (data-server-map data-server-alias)

    (data-server-alias unreserved-symbol)

    (data-server-spec ('inference 'engine) computation)
    (data-server-map ('inference 'engine) computation)

    (data-server-spec ('g2 'simulator) simulator-data-server)
    (data-server-map ('g2 'simulator) simulator-data-server)

    (data-server-spec ('g2 'meter) g2-meter-data-server)
    (data-server-map ('g2 'meter) g2-meter-data-server)))

;; The above grammar has been modified so that menus will be correctly
;; generated.  There needs to be a grammar category which names only the valid
;; true data server names, but to get the menus we need a grammar category
;; symbol which directly has all the defined names and a category for the
;; aliases.  What this all means, is that for the alias grammar and the map
;; grammar to be correct and get the right menus, data server names need to be
;; defined as members of the grammar categories data-server-map and
;; data-server-spec.  The menu heuristics should be changed to eliminate this
;; necessity!!!  -jra 1/26/88


(define-category-evaluator-interface (data-server-map
				       :access read-write)
    (or (member inference-engine g2-simulator g2-meter
		gfi-data-server gsi-data-server g2-data-server)
	symbol) ;; some user-defined data server name
  ((set-form (evaluation-value))
   (case evaluation-value
     (inference-engine 'computation)
     (g2-simulator 'simulator-data-server)
     (g2-meter 'g2-meter-data-server)
     (gfi-data-server 'gfi-data-server)
     (gsi-data-server 'gsi-data-server)
     (t (if (reserved-word-p evaluation-value)
	    'computation
	    evaluation-value))))
  ((get-form (slot-value))
   (case slot-value
     (computation 'inference-engine)
     (simulator-data-server 'g2-simulator)
     (g2-meter-data-server 'g2-meter)
     (t slot-value))))




;;; Both the compiler and writer for data-server-map are used by the compiler
;;; and writer for default-overrides. The compiler for data-server-map has been
;;; modified to expect a frame which is either a variable or a definition.

(def-slot-value-compiler data-server-map (parse-result variable-or-definition)
  (declare (ignore variable-or-definition))
  (cond ((atom parse-result) parse-result)
	((eq (car parse-result) '\;)
	 (loop for form in (cdr parse-result)
	       collect
		 (if (atom (cdr form))
		     (prog1 form
			    (setf (cdr form) (phrase-cons (cdr form) nil)))
		     form)
			using phrase-cons))
	(t
	 (phrase-cons
	   (if (atom (cdr parse-result))
	       (prog1
		 parse-result
		 (setf (cdr parse-result) (phrase-cons (cdr parse-result) nil)))
	       parse-result)
	   nil))))
  




(def-slot-value-writer data-server-map (value)
  (cond
    ((eq value 'computation) (twrite "inference engine"))
    ((eq value 'simulator-data-server) (twrite "G2 simulator"))
    ((eq value 'g2-meter-data-server) (twrite "G2 meter"))
    ((symbolp value)
     (let ((defined-pretty-name? (cdr (assq value data-server-pretty-name-alist))))
       (if defined-pretty-name?
	   (twrite defined-pretty-name?)
	   (tformat "~(~a~)" value))))

    (t (loop for ((mode server-name . rest-of-server-spec) . more?) on value
	     do
	 (tformat "~(if ~a use ~a~)" mode server-name)
	 (when rest-of-server-spec
	   (twrite " with ")
	   (loop for (item . more-items?) on rest-of-server-spec doing
	     (tformat "~(~a~)" item)
	     (cond
	       ((cdr more-items?) (twrite ", "))
	       (more-items? (twrite ", and ")))))
	 (if more? (twrite "; "))))))








;;;; Grammar for Definitions


(add-grammar-rules
  '(
    ;; changes for both kinds of definition
    (definition-change ('rename 'attribute attribute-name 'to attribute-name)
	    (rename-attribute 3 5))
;    (definition-change ('add 'attribute '\: attribute-description)
;	    (add-attribute 4) attribute-fix-2)
;    (definition-change ('change 'attribute '\: attribute-description)
;	    (change-attribute 4) attribute-fix-2)

;    (definition-change ('delete 'attribute attribute-name)
;	    (delete-attribute 3))
;    (definition-change ('change 'the 'superior 'of 'the 'class 'to class)
;	    (change-superior-object 8))
;    (definition-change ('change 'the 'name 'of 'the 'class 'to class)
;	    (change-object-name 8))
    (definition-change
      ('change 'the 'attribute standard-or-class-qualified-symbol
       'of 'each 'instance 'to 'the 'default 'value)
      (change-instance-values 4))

    ;; New: (MHD 7/25/91)
    (definition-change
      ('change 'the 'attribute attribute-or-defaulted-attribute-name
       'of 'each 'instance 'to 'the 'default 'value
       '\, 'preserving 'non-default 'values
       'when 'switching 'to 'or 'from 'values
       'given 'by 'a 'variable-or-parameter)
      (change-instance-values-preserving-non-default-values-in-some-cases 4))

    (definition-change ('merge 'all 'instances 'and 'subclasses
			'into 'definition 'for class)
		       (merge-definitions 9))

    ;; move attribute
    (definition-change ('move 'attribute attribute-name 'to class)
	(move-attribute 3 5))

    ;; To fix bug HQ-2138076, the following definition-change relation-addition
    ;; and relation-removal grammar has been commented out.  It was never
    ;; implemented so G2 does absolutely nothing when this grammar is selected.
    ;; Relations added and removed through actions and the relationship virtual
    ;; attribute. (ghw 1/26/99)
    
    ;; one to one relation instances
;    (definition-change (item-name 'is relation-name item-name)
;	(relation-addition 3 1 4))
;    (definition-change (item-name 'is 'not relation-name item-name)
;	(relation-removal 4 1 5))
;    (definition-change (item-name 'is 'now relation-name item-name)
;	(relation-addition 4 1 5 now))

    ;; one to many relation instances
;    (definition-change (item-name 'is relation-name 'every class)
;	(relation-addition 3 1 5))
;    (definition-change (item-name 'is 'not relation-name 'every class)
;	(relation-removal 4 1 6))
;    (definition-change (item-name 'is 'now relation-name 'every class)
;	(relation-addition 4 1 6 now))

    ;; many to one relation instances
;    (definition-change ('every class 'is relation-name item-name)
;	(relation-addition 4 2 5))
;    (definition-change ('every class 'is 'not relation-name item-name)
;	(relation-removal 5 2 6))
;    (definition-change ('every class 'is 'now relation-name item-name)
;	(relation-addition 5 2 6 now))

    ;; many to many relation instances
;    (definition-change ('every class 'is relation-name 'every class)
;	(relation-addition 4 2 6))
;    (definition-change ('every class 'is 'not relation-name 'every class)
;	(relation-removal 5 2 7))
;    (definition-change ('every class 'is 'now relation-name 'every class)
;	(relation-addition 5 2 7 now))
        
    (definition-change 'none)

    
    ;; changes for objects only
    (object-change definition-change)
    (object-change ('copy 'inherited 'icon 'description)
		       (copy-inherited-icon-description))
    (object-change		  ; keep in synch w/similar message-change below
      ;; Alt:
      ;;   update each instance per the <attr> specification in its definition
      ;;   update each instance per the <attr> of this definition
      ;;   update each instance per the <attr> for this class
      ;;   update each instance to reflect the <attr> for this class
      ;;   update each instance to reflect the <attr> of its definition
      ;;   update each instance to reflect the <attr> specification in its definition
      ;;   update each instance per the <attr> specification in its definition
      ;;   update each instance per <attr>
      ('update 'each 'instance 'per updatable-object-definition-attribute)
      (update-definition-attribute 5))
    (updatable-object-definition-attribute 'attribute-displays)
    ;; do later for stubs -- deferred for now (MHD 5/6/92)
    ; (updatable-object-definition-attribute 'stubs)
    
    (object-change stub-change)
    (stub-change ('add stub-info) (add-stub 2))
    (stub-change ('delete stub-designation) (delete-stub 2))
    (stub-change ('move stub-designation 'by integer) (move-stub 2 by 4))
    (stub-change ('move stub-designation 'to positive-integer) (move-stub 2 to 4))
    (stub-change ('change 'the 'portname 'of stub-designation 'to port-name)
		   (change-portname 5 7))
    (stub-change ('change 'the 'direction 'of stub-designation 'to direction?)
		   (change-direction 5 7))
    (stub-change 
      ('change 'the 'connection 'class 'of stub-designation 'to connection-class)
      (change-connection-class 6 8))

    (stub-designation ('the 'connection 'at port-name) 4)
    (stub-designation ('the 'connection 'located 'at edge integer) (5 6))

    (stub-designation-or-none stub-designation)
    (stub-designation-or-none 'none)

    ;; changes for connection only
    (connection-change definition-change)

;    (connection-change
;      ('update 'each 'instance 'per
;       updatable-connection-definition-attribute)
;      (update-definition-attribute 5))
;    (updatable-connection-definition-attribute 'stub-length)
    ;; do later for stub-length -- deferred for now (MHD 5/6/92)
    
    (message-change  definition-change)
    
    (message-change
      ('update 'each 'instance 'per
       updatable-message-definition-attribute)
      (update-definition-attribute 5))
    (updatable-message-definition-attribute 'default-message-properties)

    (attribute-or-defaulted-attribute-name attribute-name)
    (attribute-or-defaulted-attribute-name defaulted-attribute-name)

    ;; changes for class-definitions
    (class-definition-change definition-change)
    (class-definition-change object-change)
    (class-definition-change message-change)

    ;; specification for connection cross section patterns (before compiler)
    ;; One of:
    ;;   INHERITED  (NOTE: disabled for 2.0 Alpha)
    ;;   (COPY INHERITED PATTERN)
    ;;   ((POLYCHROME . region-specification-list) . stripe-pattern)
    ;;   stripe-pattern
    ;; After compiling, "(copy inherted pattern)" puts in the superior
    ;; class's pattern, and "((polychrome . region-specification-list) ...)"
    ;; becomes "(region-specification-list ...)".
    (cross-section-pattern 'inherited)
    (cross-section-pattern ('copy 'inherited 'pattern))	; note: this functionality
    (cross-section-pattern cross-section-pattern-1)	;   is done in the CHANGE
							;   slot for object defintions
							;   But this is better, per ML
							;   But even better would be to
    							;   have it be on a menu! (MHD/ML)
    (cross-section-pattern integer)
    
    (cross-section-pattern-1 stripe-pattern)
    (cross-section-pattern-1			; this one new for 2.0 (MHD)
      (region-specification-list '\; stripe-pattern)
      ((polychrome . 1) . 3))

    (stripe-pattern stripe-component)
    (stripe-pattern (stripe-component '\, stripe-pattern)
		    (2 1 3) simplify-associative-operation)

    (stripe-component (integer color-or-metacolor) (2 . 1))
    (stripe-component (integer region) (2 . 1))

    (stub-length integer)
    (stub-length 'inherited)

    ;; attribute-initialization appears to be unreachable. ML 1/4/88
    ;; -- therefore commented out (finally!). (MHD 4/17/97)
;    (attribute-initialization constant)
;    (attribute-initialization unreserved-symbol)

    ))

(def-slot-value-writer-as-existing-function
  unreserved-symbol write-symbol-from-slot)



#+unused
(defun attribute-fix-2 (form)
  (if (symbolp (second form))
      (setf (second form) (phrase-cons (second form)
				       (phrase-cons nil
						    (phrase-cons nil nil)))))
  form)



(def-slot-value-compiler color-for-class? (parse-result)
  (if (eq parse-result 'inherited)		; This has been added because the grammar 
      nil					;   rule transformation that's supposed
      parse-result))				;   to do this has not been working!
						;   (MHD 4/28/92)


(def-slot-value-writer color-for-class? (value)	; used in DEFINITIONS (for object 
  (if value
      (twrite-color value)
      (twrite 'inherited)))		        ;   definitions -- used to use color)
						;   (MHD 8/3/89)

(def-slot-value-writer color (color)		; used to print "BLACK" for nil -- now
  (twrite-color (or color 'black)))	;   should never REALLY see nil! (MHD
					;   8/3/89)



(def-slot-value-compiler class-definition-change
    (parse-result definition)
  (compile-definition-changes parse-result definition))

(def-slot-value-compiler object-change (parse-result definition)
  (compile-definition-changes parse-result definition))

(def-slot-value-compiler connection-change (parse-result definition)
  (compile-definition-changes parse-result definition))

(def-slot-value-compiler message-change (parse-result definition)
  (compile-definition-changes parse-result definition))



(defun compile-definition-changes (change? definition)
  ;; Note that as of version 4.0, this function no longer restricts a
  ;; rename-attribute change from occuring while G2 is running or paused, or
  ;; when there are instances.  - cpm, 3/14/94
  (let ((class (name-of-defined-class definition)))
    (if (classp class)
	
	(cond ((null change?) nil)
	      
	      ((eq change? 'none) nil)

	      (t
	       (case (car change?)
		 (move-attribute
		  ;; (move <attribute-name> <class>)
		  (let ((attribute-name (second change?))
			(target-class (third change?)))
		    (cond ((not (member attribute-name
					(class-specific-attributes definition)
					:test 'car-eq))
			   (values
			     bad-phrase
			     (copy-text-string
			       "The attribute is not defined for this class")))
			  ((eq class target-class)
			   (values
			     bad-phrase
			     (copy-text-string
			       "An attribute cannot be moved to the same class.")))
			  ((not (classp target-class))
			   (values
			     bad-phrase
			     (copy-constant-wide-string #w"The target class must be defined.")))
			  ((system-defined-class-p target-class)
			   (values
			     bad-phrase
			     (copy-text-string
			       "The target class cannot be a system-defined class.")))
			  ;; built-in => system-defined above (MHD 5/12/95)
			  ((not (or (subclassp class target-class)
				    (subclassp target-class class)))
			   (values
			     bad-phrase
			     (copy-text-string
			       "The target class must be an inferior or superior class.")))
			  ((member attribute-name
				   (class-specific-attributes
				     (class-definition target-class))
				   :test 'car-eq)
			   (values
			     bad-phrase
			     (copy-text-string
			       "The target class already has this attribute.")))
		       (t change?))))
	      
		 ((add-stub delete-stub move-stub change-portname change-direction
			    change-connection-class)
		  (if (and (frame-of-class-p definition 'class-definition)
			   (not (class-definition-defines-user-editable-icon-class-p
				  definition)))
		      (values
			bad-phrase
			(copy-text-string
			  "The class defined by this definition cannot have connections."))
		      change?))

		 (copy-inherited-icon-description
		  (if (and (frame-of-class-p definition 'class-definition)
			   (not (class-definition-defines-user-editable-icon-class-p
				  definition)))
		      (values
			bad-phrase
			(copy-text-string
			  "The class defined by this definition cannot have an icon."))
		      change?))

		 (update-definition-attribute
		  (if (eq (second change?) 'default-message-properties)
		      (if (subclassp class 'message)
			  change?
			  (values
			    bad-phrase
			    (copy-text-string
			      "The class defined by this definition cannot have default message properties.")))
		      change?))
	      
		 (add-attribute
		  (if (reserved-system-slot-name-p
			definition (first (second change?)))
		      (bad-attribute-name (first (second change?)))
		      change?))

		 (rename-attribute
		  (if (reserved-system-slot-name-p definition (third change?))
		      (bad-attribute-name (third change?))
		      change?))
	      
		 (t change?))))
	
	(values
	  bad-phrase
	  (copy-text-string
	    "You cannot make changes to a class before it exists.")))))



;;; The slot value compiler for stub-designation-or-none expects parse-result to
;;; be either the symbol NONE or a stub designation.  If parse-result is NONE,
;;; nil is returned; otherwise, parse-result is returned.

(def-slot-value-compiler stub-designation-or-none (parse-result)
  (if (eq parse-result 'none) nil parse-result))

(def-slot-value-writer stub-designation-or-none (stub-designation-or-none)
  (cond
    ((null stub-designation-or-none) (tformat "none"))
    ((consp stub-designation-or-none)
     (tformat "the connection located at ~(~a~) ~d"
	      (first stub-designation-or-none) 
	      (second stub-designation-or-none)))
    (t
     (tformat "the connection at ~(~a~)" stub-designation-or-none))))

(define-category-evaluator-interface (stub-designation-or-none :access read-write)
    (or (no-item)
	symbol
	(structure stub-designation-spec
		   ((edge (member top bottom right left))
		    (position integer))
		   (and edge position)))
  ((set-form (evaluation-value))
   (block blocky-block-block
     (evaluation-etypecase evaluation-value
      ((no-item) 'none)
      (symbol
	(let ((s (evaluation-symbol-symbol evaluation-value)))
	  (when (reserved-word-p evaluation-value)
	    (return-from blocky-block-block
	      (values bad-phrase
		      (tformat-text-string "~a is a reserved word" s))))
	  s))
      ((structure)
       (with-structure (evaluation-value stub-designation-spec)
	 (phrase-list edge position))))))
  ((get-form (slot-value))
   (cond ((null slot-value) nil)
	 ((symbolp slot-value) slot-value)
	 ((consp slot-value)
	  (allocate-evaluation-structure-inline
	    'edge (car slot-value)
	    'position (cadr slot-value))))))
	

(def-slot-value-writer class-definition-change (change)
    (declare (ignore change))
    (twrite "none"))

(def-slot-value-writer object-change (change)
  (declare (ignore change))
  (twrite "none"))
;  (write-changes-for-definition change object))

(def-slot-value-writer connection-change (change)
    (declare (ignore change))
    (twrite "none"))

(def-slot-value-writer message-change (change)
    (declare (ignore change))
    (twrite "none"))




(add-grammar-rules
  '((menu-option ('a 'final 'menu 'choice) (2))
    (menu-option ('not 'a 'final 'menu 'choice) (not-a-final-choice))
    (menu-option ('never 'a 'menu 'choice) (never-a-choice))))

(def-slot-value-compiler menu-option (parse-result)
  (unless (eq (car parse-result) 'final) (car parse-result)))

(def-slot-value-writer menu-option (slot-value frame)
  (declare (ignore slot-value))
  (let ((instantiate? (instantiate? frame))
	(include-in-menus? (include-in-menus? frame)))
    (if instantiate?
	(if include-in-menus?
	    (twrite "a final menu choice")
	    (twrite "never a menu choice"))
	(twrite "not a final menu choice"))))




(define-slot-alias class-name name-of-defined-class definition)

;; The above alias was changed from class to class-name today.  (MHD 6/21/91)


(define-slot-alias direct-superior-classes direct-superiors-of-defined-class definition)

(define-slot-alias stubs connections-for-class? definition)

(define-slot-alias icon-description icon-description-for-class? definition)

(define-slot-alias menu-option definition-menu-option)

(define-slot-alias cross-section-pattern cross-section-pattern-for-connection)

(define-slot-alias stub-length stub-length-for-connection)

(define-slot-alias junction-block junction-block-class-for-connection)



;;;; Grammar for Slots of Displays

;; Modified by Ml, 1/6/89 to add time stamp and interval as formats.
;; See modification to slot writer for value-for-readout-table also.

(add-grammar-rules
  '((format? ddd.dddd-format)
    (format? ('time 'stamp) time-stamp)
    (format? ('free 'text) free-text)	; new in 6.0r2 (MHD 12/5/01)
    (format? 'interval)
    (format? 'default)))

(def-slot-value-compiler format? (parse-result)
  (case parse-result
    (default nil)
    (interval 'seconds)
    ((time-stamp free-text) parse-result)
    (t (cond ((and (symbolp parse-result)
		   (date-format-description parse-result))
	      parse-result)
	     (t
	      (multiple-value-bind (left right)
		  (decode-format parse-result)
		(if left
		    (phrase-cons left right)
		    bad-phrase)))))))



(define-category-evaluator-interface (float-format :access read-write)
    (structure float-format-spec
	       ((whole-number-precision integer)
		(fraction-precision integer))
	       (and whole-number-precision fraction-precision))
  ((set-form (evaluation-value))
   (with-structure (evaluation-value float-format-spec)
     (cond ((or (<f whole-number-precision 0)
		(>f whole-number-precision float-format-precision-limit))
	    (values bad-phrase
		    (tformat-text-string "The whole-number-precision ~D is not between 0 and ~D"
					 whole-number-precision
					 float-format-precision-limit)))
	   ((or (<f fraction-precision 0)
		(>f fraction-precision float-format-precision-limit))
	    (values bad-phrase
		    (tformat-text-string "The fraction-precision ~D is not between 0 and ~D"
					 fraction-precision
					 float-format-precision-limit)))
	   (t
	    (let ((fstring (twith-output-to-text-string
			     (loop for i from 1 to whole-number-precision do
			       (twrite "d"))
			     (twrite ".")
			     (loop for i from 1 to fraction-precision do
			       (twrite "d")))))
	      (intern-text-string fstring))))))
  ((get-form (slot-value))
   (with-new-structure (float-format-spec)
     (setf whole-number-precision (car slot-value))
     (setf fraction-precision (cdr slot-value)))))

(define-category-evaluator-interface (format? :access read-write)
    (or (member default interval time-stamp free-text)
	symbol
	(named float-format))
  ((set-form (evaluation-value))
   (case evaluation-value
     ((default interval time-stamp free-text) evaluation-value)
     (t
      (if (and (symbolp evaluation-value)
	       (date-format-description evaluation-value))
	  evaluation-value
	  (call-category-setter 'float-format evaluation-value nil nil nil)))))
  ((get-form (slot-value))
   (cond ((null slot-value) 'default)
	 (t
	  (case slot-value
	    (seconds 'interval)
	    ((time-stamp free-text) slot-value)
	    (t
	     (if (and (symbolp slot-value)
		      (date-format-description slot-value))
		 slot-value
		 (call-category-getter 'float-format slot-value nil nil))))))))
	  
(def-slot-value-writer format? (value)
  (cond
    ((null value) (twrite "default"))
    ((eq value 'time-stamp) (twrite "time stamp"))
    ((eq value 'free-text) (twrite "free text"))
    ((eq value 'seconds) (twrite "interval"))
    ((and (symbolp value) (date-format-description value))
     (twrite (date-format-name-string (date-format-description value)))) 
    ;; This looks very odd; should it really be
    ;; (twrite value) rather than just value? -alatto, 2/10/07
    ((atom value) value) ;unit-of-measure 
    (t (loop for i from 1 to (car value) do (tprin "d" nil))
       (tprin "." nil)
       (loop for i from 1 to (cdr value) do (tprin "d" nil)))))




(add-grammar-rules
  '((type-in-box-format? format?)))

;; Note: time-stamp, free-text, and interval new in G2 6.0r2. See about unifying
;; this code further with that above for displays!  For now, we just at least
;; use the function generated by the above code. (MHD 12/5/01)


(def-slot-value-compiler type-in-box-format? (parse-result)
  (compile-format?-for-slot parse-result nil nil nil nil nil))

(define-category-evaluator-interface (type-in-box-format? :access read-write)
    (or (member default interval time-stamp free-text)
	(named float-format))
  ((set-form (evaluation-value))
   (funcall
     (evaluation-value-to-category-function 'format?)
     evaluation-value nil nil nil))
  ((get-form (slot-value))
   (funcall
     (slot-value-to-evaluation-value-function 'format?)
     slot-value nil nil)))
	  
(def-slot-value-writer type-in-box-format? (value)
  (write-format?-from-slot value nil))






(add-grammar-rules
  '((display-expression unique-expression)
    (display-expression unique-logical-expression)
    (list-of-display-expressions display-expression)
    (list-of-display-expressions 
      (display-expression '\; list-of-display-expressions) 
      (2 1 3) simplify-associative-operation)
    
    (list-of-graph-expressions graph-expression)
    (list-of-graph-expressions
      (graph-expression '\; list-of-graph-expressions) 
      (2 1 3) simplify-associative-operation)

    (graph-expression unique-designation)

    ;; combinations with one extra plot phrase
    (graph-expression (unique-designation plot-color-phrase) (\, 1 2))
    (graph-expression (unique-designation plot-marker-phrase) (\, 1 nil 2))
    (graph-expression (unique-designation plot-range-phrase) (\, 1 nil nil 2))

    ;; combinations with two extra plot phrases
    (graph-expression (unique-designation plot-color-phrase plot-marker-phrase)
		      (\, 1 2 3))
    (graph-expression (unique-designation plot-color-phrase plot-range-phrase) 
		      (\, 1 2 nil 3))
    (graph-expression (unique-designation plot-marker-phrase plot-range-phrase) 
		      (\, 1 nil 2 3))

    ;; all plot phrases
    (graph-expression (unique-designation plot-color-phrase
					  plot-marker-phrase plot-range-phrase)
		      (\, 1 2 3 4))

    (plot-color-phrase ('in color) 2)
    (plot-range-phrase ('with 'range 'from number 'to number) (4 . 6))

    (plot-marker-phrase marker-phrase)
    (plot-marker-phrase ('using 'shading) 2)
    (plot-marker-phrase plot-line-width-phrase)
    (plot-marker-phrase (marker-phrase 'and plot-line-width-phrase) (1 . 3))

    (plot-line-width-phrase ('using 'line 'width positive-integer) 4)

    (marker-phrase ('using plot-marker 'plot 'marker) 2)
    (plot-marker 'square)
    (plot-marker 'triangle)
    (plot-marker 'plus-sign)

    (yes-or-no 'yes t)
    (yes-or-no 'no nil nil-function)
    ;(yes-or-no? yes-or-no) ;; expunged this category 12/18/96 see Tables
    (text-box-format-name? unreserved-symbol)
    (display-interval quantity-interval)
    (dial-ruling-parameter number)
    (meter-ruling-parameter number)

    (horizontal-graph-ruling-parameter? 'none)
    (vertical-graph-ruling-parameter? 'none)
    (vertical-graph-ruling-parameter? number)
    (vertical-graph-ruling-parameter? 
      (number 'with 'all 'intervals 'the 'same) (1 . 6))
    (horizontal-graph-ruling-parameter? interval)
    (vertical-graph-ruling-parameter? (number 'to number) (\; 1 3))
    (vertical-graph-ruling-parameter? 
      (number 'to number 'with 'all 'intervals 'the 'same) (\; 1 3 8))
    (horizontal-graph-ruling-parameter? (interval 'to interval 'after 'start) (\; 1 3))

    ;; Define the 'without-tickmark-labels' version of each rule above. This could be automated.
    (vertical-graph-ruling-parameter?   (number 'without 'tickmark 'labels)
				        (without-tickmark-labels . 1))
    (vertical-graph-ruling-parameter?   (number 'to number 'without 'tickmark 'labels)
				        (without-tickmark-labels \; 1 3))
    (horizontal-graph-ruling-parameter? (interval 'without 'tickmark 'labels)
					(without-tickmark-labels . 1))
    (horizontal-graph-ruling-parameter? (interval 'to interval 'after 'start 'without 'tickmark 'labels)
					(without-tickmark-labels \; 1 3))
    (vertical-graph-ruling-parameter? 
      (number 'with 'all 'intervals 'the 'same 'without 'tickmark 'labels) (without-tickmark-labels 1 . 6))
    (vertical-graph-ruling-parameter? 
      (number 'to number 'with 'all 'intervals 'the 'same 'without 'tickmark 'labels) (without-tickmark-labels \; 1 3 8))

    (horizontal-gridline-interval? ('compute 'automatically) none)
    (horizontal-gridline-interval? number)
    (horizontal-gridline-interval? (number 'beginning 'at number) (1 . 4))

    (extra-grid-line-specs extra-grid-line-spec)
    (extra-grid-line-specs
      (extra-grid-line-spec '\, extra-grid-line-specs)
      (2 1 3) simplify-associative-operation)
    (extra-grid-line-spec ('at number) 2)
    (extra-grid-line-spec ('at number 'in color) (2 . 4))
    (extra-grid-line-spec 'none)

    (graph-background-colors 
      ('graph 'background '\: color '\, 'grid 'background '\: color) (4 . 9))
			      
    ))

;; In the case of display expressions, there should only be one
;; expression.  Consider enforcing this in the grammar.  If there is
;; more than one, the form will be a list beginning with '\; followed by
;; the expressions and the update function will use the first
;; expression.


#+graphs-are-good
(define-category-evaluator-interface (graph-background-colors
				       :access read-write)
    (structure graph-colors
	       ((background-color (named color-or-metacolor))
		(grid-color (named color-or-metacolor))))
  ((set-form (evaluation-value))
   (with-structure (evaluation-value graph-colors)
     (phrase-cons background-color grid-color)))
  ((get-form (slot-value))
   (with-new-structure (graph-colors)
     (setf background-color (car slot-value))
     (setf grid-color (cdr slot-value)))))
   
  


(def-slot-value-compiler extra-grid-line-specs (parse-result)
  (if (eq parse-result 'none) nil parse-result))

#+graphs-are-good
(define-category-evaluator-interface (extra-grid-line-specs
				       :access read-write)
    (or number
	(no-item)
	(structure
	  extra-grid-line-color-spec
	  ((grid-line-number number)
	   (grid-line-color symbol)))
	(sequence (or number
		      extra-grid-line-color-spec)
		  2))
  ((set-form (evaluation-value))
   (evaluation-etypecase evaluation-value
    ((no-item) 'none)
    ((structure)
     (with-structure (evaluation-value extra-grid-line-color-spec) 
       (phrase-cons grid-line-number grid-line-color)))
    ((sequence)
     (phrase-cons '\,
		  (with-evaluation-sequence-to-phrase-list-mapping
		      (evaluation-value specification)
		    (if (numberp specification)
			specification
			(with-structure (specification extra-grid-line-color-spec)
			  (phrase-cons grid-line-number grid-line-color))))))
    (t (copy-for-phrase evaluation-value))))
  ((get-form (slot-value))
   (cond ((managed-float-p slot-value)
	  (copy-managed-float-into-evaluation-float slot-value))
	 ((fixnump slot-value) slot-value)
	 ((consp slot-value)
	  (if (eq (car-of-cons slot-value) '\,)
	      (let ((value (cdr slot-value)))
		(with-list-to-evaluation-sequence-mapping
		    (value specification)
		  (cond ((managed-float-p specification)
			 (copy-managed-float-into-evaluation-float specification))
			((fixnump specification) specification)
			(t (with-new-structure (extra-grid-line-color-spec)
			     (let ((number-value (car specification)))
			       (setf grid-line-number
				     (if (managed-float-p number-value)
					 (copy-managed-float-into-evaluation-float
					   number-value)
					 number-value))
			       (setf grid-line-color (cdr specification))))))))
	      (with-new-structure (extra-grid-line-color-spec)
		(let ((number-value (car slot-value)))
		  (setf grid-line-number
			(if (managed-float-p number-value)
			    (copy-managed-float-into-evaluation-float
			      number-value)
			    number-value))
		  (setf grid-line-color (cdr slot-value))))))
	 (t nil))))
	      
	      


(def-slot-value-writer extra-grid-line-specs (extra-grid-line-specs)
  (if (null extra-grid-line-specs)
      (twrite "none")
      (if (and (consp extra-grid-line-specs)
	       (eq (car extra-grid-line-specs) '\,))
	  (loop for grid-line-spec in (cdr extra-grid-line-specs)
		as first-time? = t then nil
		do (when (not first-time?)
		     (twrite ", "))
		   (print-grid-line-spec grid-line-spec))
	  (print-grid-line-spec extra-grid-line-specs))))


(defun print-grid-line-spec (grid-line-spec)
  (with-temporary-gensym-float-creation grid-line-spec
    (cond
      ((slot-value-number-p grid-line-spec)
       (twrite "at ")
       (print-ruling-parameter-number 
	 (slot-value-number-value grid-line-spec)))
      (t
       (twrite "at ")
       (print-ruling-parameter-number 
	 (slot-value-number-value (car grid-line-spec)))
       (twrite " in ") 
       (twrite 
	 (cdr grid-line-spec))))))



(defun print-ruling-parameter-number (ruling-parameter-number) 
  (if (floatp ruling-parameter-number) 
      (twrite-float ruling-parameter-number)
      (twrite ruling-parameter-number)))



(def-slot-value-writer dial-ruling-parameter (dial-ruling-parameter)
  (with-temporary-gensym-float-creation dial-ruling-parameter
    (print-ruling-parameter-number (slot-value-number-value dial-ruling-parameter))))

(def-slot-value-writer meter-ruling-parameter (meter-ruling-parameter)
  (with-temporary-gensym-float-creation meter-ruling-parameter
    (print-ruling-parameter-number (slot-value-number-value meter-ruling-parameter))))

(def-slot-value-compiler dial-ruling-parameter
			 (parse-result dial slot-name)
  (declare (ignore dial))
  (cond
    ((and (eq slot-name 'increment-per-dial-ruling)
	  (with-temporary-gensym-float-creation dial-ruling-parameter
	    (minusp (phrase-number-value parse-result))))
     (values
       bad-phrase
       (copy-text-string
	 "Increment per dial ruling must be positive.")))
    (t
     parse-result)))

(define-category-evaluator-interface (dial-ruling-parameter
				       :access read-write)
    number
  ((set-form (evaluation-value))
   (if (evaluation-float-p evaluation-value)
       (make-phrase-float (evaluation-float-value evaluation-value))
       evaluation-value))
  ((get-form (slot-value))
   (cond ((fixnump slot-value)
	  slot-value)
	 (t
	  (copy-managed-float slot-value)))))

(def-slot-value-compiler meter-ruling-parameter
			 (parse-result meter slot-name)
  meter
  (cond
    ((and (eq slot-name 'increment-per-meter-ruling)
	  (with-temporary-gensym-float-creation meter-ruling-parameter
	    (minusp (phrase-number-value parse-result))))
     (values
       bad-phrase
       (copy-text-string
	 "Increment per meter ruling must be positive.")))
    (t
     parse-result)))

(define-category-evaluator-interface (meter-ruling-parameter
				       :access read-write)
    number
  ((set-form (evaluation-value))
   (call-category-setter
     'dial-ruling-parameter evaluation-value nil nil nil))
  ((get-form (slot-value))
   (call-category-getter
     'dial-ruling-parameter slot-value nil nil)))

(def-slot-value-writer graph-background-colors (graph-background-colors)
  (twrite "graph background: ")
  (twrite-color (car graph-background-colors))
  (twrite ", grid background: ")
  (twrite-color (cdr graph-background-colors)))


(def-slot-value-writer horizontal-graph-ruling-parameter? 
		       (horizontal-graph-ruling-parameter?)
 (let ((without-labels? nil))
  (multiple-value-setq (horizontal-graph-ruling-parameter? without-labels?)
    (remove-tickmark-label-annotation horizontal-graph-ruling-parameter?))
  (cond						
    ((null horizontal-graph-ruling-parameter?) (twrite "none"))
    ((numberp horizontal-graph-ruling-parameter?)	; implies fixnump here
     (twrite "none"))

    ;; Horizontal-graph-ruling-parameter? must be a cons at this point.
    ((not (eq (car horizontal-graph-ruling-parameter?) '\;))
     (print-constant (car horizontal-graph-ruling-parameter?) 'seconds))
    ((not (consp (second horizontal-graph-ruling-parameter?)))
     (twrite "none"))
    (t
     (print-constant 
       (car (second horizontal-graph-ruling-parameter?)) 'seconds)
     (twrite " to ")
     (print-constant 
       (car (third horizontal-graph-ruling-parameter?)) 'seconds)
     (twrite " after start")))
  (when without-labels? (twrite " without tickmark labels"))))

(def-slot-value-writer vertical-graph-ruling-parameter? 
		       (vertical-graph-ruling-parameter?)
 (let ((without-labels? nil))
  (multiple-value-setq (vertical-graph-ruling-parameter? without-labels?)
     (remove-tickmark-label-annotation vertical-graph-ruling-parameter?))
  (with-temporary-gensym-float-creation vertical-graph-ruling-parameter?
    (cond 
      ((null vertical-graph-ruling-parameter?) (twrite "none"))
      ((slot-value-number-p vertical-graph-ruling-parameter?) 
       (print-ruling-parameter-number 
	 (slot-value-number-value vertical-graph-ruling-parameter?)))
      
      ;; Vertical-graph-ruling-parameter? must be a cons at this point.
      ((slot-value-number-p (car vertical-graph-ruling-parameter?))
       (print-ruling-parameter-number 
	 (slot-value-number-value (car vertical-graph-ruling-parameter?)))
       (twrite " with all intervals the same"))
      (t
       (print-ruling-parameter-number
	 (slot-value-number-value (second vertical-graph-ruling-parameter?)))
       (twrite " to ")
       (print-ruling-parameter-number
	 (slot-value-number-value (third vertical-graph-ruling-parameter?)))
       (when (fourth vertical-graph-ruling-parameter?)
	 (twrite " with all intervals the same")))))
  (when without-labels? (twrite " without tickmark labels"))))

(def-slot-value-writer horizontal-gridline-interval? (horizontal-gridline-interval?)
  (with-temporary-gensym-float-creation horizontal-gridline-interval?
    (cond 
      ((null horizontal-gridline-interval?) (twrite "compute automatically"))
      (t
       (print-ruling-parameter-number 
	 (slot-value-number-value (car horizontal-gridline-interval?)))
       (twrite " beginning at ")
       (print-ruling-parameter-number 
	 (slot-value-number-value (cdr horizontal-gridline-interval?)))))))



;;; The slot value compiler for horizontal-graph-ruling-parameter?
;;; ensures that the range specified is positive and also that it
;;; is less than 24 weeks.

(def-slot-value-compiler horizontal-graph-ruling-parameter?
			 (parse-result graph slot-name)
  slot-name graph
 (let ((original-parse parse-result)
       without-labels?)
  (multiple-value-setq (parse-result without-labels?)
    (remove-tickmark-label-annotation parse-result))
  (cond
    ((eq parse-result 'none)
     (cond ((not without-labels?) nil)
	   (t (setf (cdr original-parse) nil)	; here parse is (without-tickmark-labels . none)
	       original-parse)))
    
    ;; Parse-result must be a cons at this point.
    ((not (eq (car parse-result) '\;))
     ;; moving window format
     (if (> (car parse-result) 14515200)	; 24 weeks
	 (values
	   bad-phrase
	   (copy-text-string
	     "Horizontal axis range can not be greater than 24 weeks."))
	 original-parse))
    (t						; absolute format
     (let ((range
	     (- (car (third parse-result))
		(car (second parse-result)))))
       (cond
	 ((> range 14515200)			; 24 weeks
	  (values
	    bad-phrase
	    (copy-text-string
	      "Horizontal axis range can not be greater than 24 weeks.")))
	 ((<= range 0)
	  (values
	    bad-phrase
	    (copy-text-string
	      "Horizontal axis range must be greater than 0.")))
	 (t original-parse)))))))

#+graphs-are-good
(define-category-evaluator-interface (horizontal-graph-ruling-parameter?
				       :access read-write)
    (or (no-item)
	(structure
	  horizontal-graph-ruling-spec
	  ((from-interval integer)
	   (to-interval integer)
	   (without-tickmark-labels symbol))))
  ((set-form (evaluation-value))
   (if evaluation-value
       (with-structure (evaluation-value horizontal-graph-ruling-spec)
	 (if to-interval
	     (if (eq without-tickmark-labels 'yes)
		 (phrase-list
		   'without-tickmark-labels '\;
		   (phrase-cons from-interval 'seconds)
		   (phrase-cons to-interval 'seconds))
		 (phrase-list
		   '\; (phrase-cons from-interval 'seconds)
		   (phrase-cons to-interval 'seconds)))
	     (if (eq without-tickmark-labels 'yes)
		 (nconc
		   (phrase-list 'without-tickmark-labels)
		   (phrase-cons from-interval 'seconds))
		 (phrase-cons from-interval 'seconds))))
       'none))
  ((get-form (slot-value))
   (cond (slot-value
	  (multiple-value-bind (value without-labels?)
	      (remove-tickmark-label-annotation slot-value)
	    (with-new-structure (horizontal-graph-ruling-spec)
	      (cond ((eq (car value) '\;)
		     (setf from-interval (car (second value)))
		     (setf to-interval (car (third value))))
		    (t
		     (setf from-interval (car value))))
	      (setf without-tickmark-labels (if without-labels? 'yes 'no)))))
	  (t nil))))

	       



(def-substitution-macro check-vertical-axis-range
			(range value-to-return-if-ok)
  (if (minusp range)
      (values
	bad-phrase
	(copy-text-string
	  "Vertical axis range can not be less than 0."))
      value-to-return-if-ok))



;;; The slot value compiler for vertical-graph-ruling-parameter?
;;; ensures that the range specified is non-negative.

(def-slot-value-compiler vertical-graph-ruling-parameter?
			 (parse-result)
  (with-temporary-gensym-float-creation vertical-graph-ruling-parameter?
 (let ((original-parse parse-result)
       without-labels?)
   (multiple-value-setq (parse-result without-labels?)
     (remove-tickmark-label-annotation parse-result))
   (cond
      ((eq parse-result 'none)
       (cond ((not without-labels?) nil)
	     (t (setf (cdr original-parse) nil)	; here parse is (without-tickmark-labels . none)
		original-parse)))
      ((phrase-number-p parse-result)		       ; moving window format
       (check-vertical-axis-range
	 (phrase-number-value parse-result) original-parse))
      ;; Parse-result must be a cons at this point.
      ((phrase-number-p (car parse-result))	       ; moving window format
       (check-vertical-axis-range
	 (phrase-number-value (car parse-result))
	 original-parse))
      (t					       ; absolute format
       (let ((range
	       (- (phrase-number-value (third parse-result))
		  (phrase-number-value (second parse-result)))))
	 (check-vertical-axis-range
	   range original-parse)))))))

;; In the case of absolute format, consider just switching numbers and
;; not putting up note!

#+graphs-are-good
(define-category-evaluator-interface (vertical-graph-ruling-parameter?
				       :access read-write)
    (or (no-item)
	(structure
	  vertical-graph-ruling-spec
	  ((from-value integer)
	   (to-value integer)
	   (without-tickmark-labels symbol)
	   (with-all-intervals-the-same symbol))))
  ((set-form (evaluation-value))
   (if (eq evaluation-value 'none)
       'none
       (with-structure (evaluation-value vertical-graph-ruling-spec)
	 (if to-value
	     (nconc
	       (when (eq without-tickmark-labels 'yes)
		 (phrase-list 'without-tickmark-labels))
	       (phrase-list '\,)
	       (phrase-list (copy-evaluation-value from-value))
	       (phrase-list (copy-evaluation-value to-value))
	       (when (eq with-all-intervals-the-same 'yes)
		 (phrase-list 'same)))
	     (cond
	       ((and (eq without-tickmark-labels 'yes)
		     (eq with-all-intervals-the-same 'yes))
		(nconc
		  (phrase-list 'without-tickmark-labels)
		  (phrase-cons (copy-evaluation-value from-value) 'same)))
	       ((eq without-tickmark-labels 'yes)
		(phrase-cons
		  'without-tickmark-labels (copy-evaluation-value to-value)))
	       (t
		(copy-evaluation-value to-value)))))))
  ((get-form (slot-value))
   (cond (slot-value
	  (multiple-value-bind (value without-labels?)
	      (remove-tickmark-label-annotation slot-value)
	    (with-new-structure (vertical-graph-ruling-spec)
	      (cond ((and (consp value) (eq (car value) '\;))
		     (setf from-value (copy-evaluation-value (second value)))
		     (setf to-value (copy-evaluation-value (third value)))
		     (setf without-tickmark-labels (if without-labels? 'yes 'no))
		     (setf with-all-intervals-the-same
			   (if (fourth value) 'yes 'no)))
		    ((phrase-number-p value)
		     (setf from-value (copy-evaluation-value value))
		     (setf without-tickmark-labels 'no)
		     (setf with-all-intervals-the-same 'no))
		    ((phrase-number-p (car value))
		     (setf from-value (copy-evaluation-value (car value)))
		     (setf without-tickmark-labels (if without-labels? 'yes 'no))
		     (setf with-all-intervals-the-same
			   (if (cdr value) 'yes 'no))) 
		    (t nil)))))
		     
	  (t nil))))



(def-slot-value-compiler horizontal-gridline-interval? 
			 (parse-result)
  (cond
    ((eq parse-result 'none) nil)		       ; automatically computed
    (t
     (with-temporary-gensym-float-creation horizontal-gridline-interval?-compiler
       (let* ((number (phrase-number-value
			(cond ((phrase-number-p parse-result)
			       parse-result)
			      (t
			       (car parse-result))))))
	 (cond
	   ((cond ((fixnump number) (<=f number 0))
		  (t (<=e number 0.0)))
	    (values bad-phrase
		    (copy-constant-wide-string #w"The interval must be greater than zero.")))
	   (t
	    (cond
	      ((phrase-number-p parse-result)
	       (phrase-cons parse-result 0))
	      ;; If "beginning at" is left out, it is defaulted to 0.
	      (t parse-result)))))))))

#+graphs-are-good
(define-category-evaluator-interface (horizontal-gridline-interval?
				       :access read-write)
    (or (no-item)
	(structure
	  horizontal-gridline-interval-spec
	  ((interval-between number)
	   (start-number number))))
  ((set-form (evaluation-value))
   (cond ((null evaluation-value) 'none)
	 (t (with-structure (evaluation-value horizontal-gridline-interval-spec)
	      (phrase-cons (copy-for-phrase interval-between)
			   (copy-for-phrase start-number))))))
  ((get-form (slot-value))
   (cond ((consp slot-value)
	  (let ((between-value (car slot-value))
		(start-value (cdr slot-value)))
	    (with-new-structure (horizontal-gridline-interval-spec)
	      (setf interval-between
		  (if (managed-float-p between-value)
		      (copy-managed-float-into-evaluation-float between-value)
		      between-value))
	      (setf start-number
		  (if (managed-float-p start-value)
		      (copy-managed-float-into-evaluation-float start-value)
		      start-value)))))
	 (t nil))))

   
	     

;(def-slot-value-writer value-for-readout-table (value-and-type readout-table)
;  (setq leave-text-representation-as-a-single-line? t)
;  (if (null value-and-type)
;      (twrite "****")
;      (let ((value (extract-cached-number-or-value (first value-and-type)))
;	    (type (second value-and-type))
;	    (format (format-for-readout-table readout-table)))
;	(when (eq type 'text)
;	  (setq leave-text-representation-as-a-single-line? nil))
;	(cond
;	  ((number-subtype-p type)
;	   (typecase value
;	     (float
;	      (if (consp format)
;		  (write-floating-point-number value (car format) (cdr format)
;					       6)
;		  (write-float value)))
;	     (integer
;	      (case format
;		(time-stamp (print-constant value 'time-stamp))
;		(seconds (print-constant value 'seconds))
;		(t (tformat "~d" value))))))
;	  (t
;	   (print-constant value type)))
;	(if (cddr value-and-type)
;	    (twrite " *")
;;	    (twrite "  ")
;	    ))))

(defun write-readout-table-value-per-format (evaluation-value format)
  (cond ((evaluation-obsolete-datum-p evaluation-value)
	 (write-readout-table-value-per-format
	   (evaluation-obsolete-datum-value evaluation-value)
	   format)
	 (twrite-string " *"))
	((consp format)
	 (if (evaluation-float-p evaluation-value)
	     (write-floating-point-number
	       (evaluation-float-value evaluation-value)
	       (car-of-cons format) (cdr-of-cons format) 6
	       nil nil nil) ;suppress-trailing-zeros-p
	     ;; Else, inapplicable format, just write the value.
	     (write-evaluation-value evaluation-value)))
	((memq format '(time-stamp seconds free-text))
	 (if (evaluation-quantity-p evaluation-value)
	     (print-constant (evaluation-quantity-value evaluation-value)
			     format
			     (eq format 'free-text))
	     ;; Else, bad format, just print it.
	     (write-evaluation-value evaluation-value (eq format 'free-text))))
	((and (symbolp format) (date-format-description format))
	 (write-slot-value (date-format-quantity-attribute
			     (date-format-description format))
			   evaluation-value
			   nil))
	;; Else, bad format.  Just print it, but CERROR in development.
	(t
	 #+development
	 (cerror "Continue" "Bad format ~a in readout-table." format)
	 (write-evaluation-value evaluation-value))))

(def-slot-value-writer value-for-readout-table (ignored-value readout-table)
  (declare (ignore ignored-value))
  (let ((evaluation-value?
	  (get-cached-value-for-cell-based-display readout-table)))
    (unless (evaluation-text-p evaluation-value?)
      (setq leave-text-representation-as-a-single-line? t))
    (let ((format? (format-for-readout-table readout-table)))
      (cond ((null evaluation-value?)
	     (twrite-string "****"))
	    ((null format?)
	     ;; GENSYMCID-1181: Readout-table format
	     (let ((default-float-to-text-format nil))
	       (write-evaluation-value evaluation-value?)))
	    (t
	     (write-readout-table-value-per-format
	       evaluation-value? format?))))))

;; Modified by ML, 1/6/89 to accept time-stamp and interval
;; from format-for-readout-table.

;; The format is either nil (default), a dd.ddd type format represented as
;; a cons of two integers, seconds (meaning interval), or time-stamp.
;; The dd.ddd type is only examined for floats; the interval or time-stamp
;; is only examined for integers.

;; Setting leave-text-representation-as-a-single-line? causes format-text
;; to be more efficient.

;; Note that extract-cached-number-or-value, rather than 
;; extract-number-or-value is used so that there is no leakage of text strings.

;; Mike will implement print-formatted-constant at some point to allow 
;; passing of formats in case the constant is a floating point number.
;; This will allow simplification of the slot writer to just a call to
;; this function.


(def-slot-value-writer value-for-digital-clock (value)
  (setq leave-text-representation-as-a-single-line? t)
  (if value
      (print-constant value 'time-stamp)
      (twrite-string "time")))


(def-slot-value-writer display-interval (display-interval)
  (print-constant display-interval 'seconds))

(def-slot-value-compiler display-interval (parse-result)
  (let ((interval-number-specified (car-of-cons parse-result)))
    (if (or (and (fixnump interval-number-specified)
		 (pluspf interval-number-specified))
	    (and (phrase-float-p interval-number-specified)
		 (with-temporary-gensym-float-creation compile-display-interval
		   (>e (phrase-float-value interval-number-specified) 0.0))))
	interval-number-specified
	(values bad-phrase
		(copy-constant-wide-string #w"The interval must be greater than zero.")))))

(define-category-evaluator-interface (display-interval
				       :access read-write)
    number
  ((set-form (evaluation-value))
   (call-category-setter 
     'positive-quantity-interval? evaluation-value nil nil nil))
  ((get-form (slot-value))
   (call-category-getter 'positive-quantity-interval? slot-value nil nil)))

(def-slot-value-writer-as-existing-function
  text-box-format-name? write-symbol-from-slot)


(def-slot-value-compiler yes-or-no (parse-result)
  parse-result)

;(def-slot-value-compiler yes-or-no? (parse-result)  ;; category expunged. see Tables
;  parse-result)


;; Review the need for the above two compilers -- what turns yes-or-no into
;; nil?!  This probably devolved.  (MHD 2/26/91)


(def-slot-value-writer yes-or-no (yes-or-no)
  (twrite-string (if yes-or-no "yes" "no")))

;(def-slot-value-writer yes-or-no? (yes-or-no)  ;; category expunged. see Tables
;  (twrite-string (if yes-or-no "yes" "no")))


(def-slot-value-compiler display-expression (parse-result display-frame)
  (let* ((*current-computation-frame* display-frame)
	 (current-computation-component-particulars nil)
	 (current-computation-style the-only-dynamic-computation-style)
	 (current-block-of-dependent-frame display-frame)
	 (cell-array? (cell-array display-frame))
	 (expression-cell?
	   (when cell-array?
	     (managed-svref (g2-cell-array-managed-array cell-array?) 0)))
	 (expression? parse-result))
    (cond
      (expression?
       (when (not (and cell-array? expression-cell?))
	 (setq cell-array? (make-frame 'g2-cell-array))
	 (change-slot-value display-frame 'cell-array cell-array?)
	 (make-empty-expression-cell cell-array?)
	 (setf expression-cell?
	       (managed-svref (g2-cell-array-managed-array cell-array?) 0))
	 (when (runnable-p display-frame)
	   (activate-g2-cell-array cell-array?)))
       (without-consistency-analysis (display-frame)
	 (with-part-description ((get-default-computation-style-of-class))
	   ;; Next update the computation style with the values in the
	   ;; display which affect scheduling and execution of the
	   ;; expression.
	   (update-computation-style-with-display-settings
	     current-computation-style display-frame)
	   (register-expression-cell-during-compilation
	     cell-array? 0 t
	     expression?
	     (if (frame-of-class-p display-frame 'readout-table)
		 `(or datum (unknown-datum) (obsolete-datum))
		 `(or number (unknown-datum) (obsolete-datum))))
	   (cond ((expression-cell-able-to-compute-p expression-cell?)
		  (update-frame-status display-frame nil nil)
		  t)
		 (t
		  (update-frame-status display-frame 'bad nil)
		  nil)))))
      (t
       (without-consistency-analysis (display-frame)
	 (when cell-array?
	   (when (runnable-p display-frame)
	     (deactivate-g2-cell-array cell-array?))
	   (change-slot-value display-frame 'cell-array nil)))
       nil))))


;(def-slot-value-compiler display-expression
;			 (parse-result display-frame slot-name)
;  (declare (ignore slot-name))
;  (let* ((*current-computation-frame* display-frame)
;	 (compiled-display-expression
;	   (compile-expression parse-result nil nil)))
;    (if compiled-display-expression
;	(update-frame-status display-frame nil nil)
;	(update-frame-status display-frame 'bad nil))
;    compiled-display-expression))


(def-slot-value-compiler list-of-display-expressions (parse-result)
  parse-result)

;; The slot value compiler for list of display expressions checks if the
;; expressions-to-display-should-be-kept-as-variables? of the display
;; frame is set.  If so, it will make a variable for the expression and
;; push it into the variables-for-expressions-to-display slot of the
;; display frame.  Implement this!



(defvar graph-expression-uses-local-name?)

(def-slot-value-compiler list-of-graph-expressions
			 (parse-result graph slot-name)
  (declare (ignore slot-name))
  (with-updates-to-representations-supressed
    (graph 'frame-status-and-notes)
    (let* ((graph-expression-uses-local-name? nil)
	   (*current-computation-frame* graph)
	   (compiled-expression-or-expressions-with-info
	     (progn 
	       (delete-all-frame-notes-for-rule-or-expression t)
	       (cond
		 ((and (consp parse-result)
		       (eq (car parse-result) '\;))
		  ;; if list of expressions
		  (let ((compiled-graph-expressions
			  (loop with problem? = nil
				with compiled-expression?
				with current-computation-component-particulars
				  = (slot-value-cons 'graph-expression 1)
				for graph-expression-with-info in (cdr parse-result)
				for expression-index from 1
				do
			    (setf (cdr current-computation-component-particulars)
				  expression-index
				  compiled-expression?
				  (compile-graph-expression-with-info 
				    graph-expression-with-info))
			    (when (null compiled-expression?)
			      (setf problem? t))
				collect compiled-expression? 
				  into collected-compilations using phrase-cons
				finally
				  (reclaim-slot-value-cons 
				    current-computation-component-particulars)
				  (return
				    (if problem?
					nil
					collected-compilations)))))
		    (when compiled-graph-expressions
		      (phrase-cons '\; compiled-graph-expressions))))
		 (t
		  (let* ((current-computation-component-particulars
			   (slot-value-cons 'graph-expression 1))
			 (compilation-result
			   (compile-graph-expression-with-info
			     parse-result)))
		    (reclaim-slot-value-cons 
		      current-computation-component-particulars)
		    compilation-result))))))
      (cond
	(graph-expression-uses-local-name?
	 (values bad-phrase 
		 (copy-text-string
		   "Local names are not allowed in display expressions for graphs.")))
	(t
	 (if compiled-expression-or-expressions-with-info
	     (update-frame-status graph nil nil)
	     (update-frame-status graph 'bad nil))
	 compiled-expression-or-expressions-with-info)))))

;;; Compile-graph-expression-with-info returns nil if the compile fails.

(defun compile-graph-expression-with-info (graph-expression-with-info)
  (cond
    ((and (consp graph-expression-with-info)
	  (eq (car graph-expression-with-info) '\,))
     (let ((compiled-expression?
	     (compile-expression 
	       (second graph-expression-with-info) nil nil)))
       (setf (second graph-expression-with-info) compiled-expression?)
       (return-compiled-graph-expression-if-ok 
	 compiled-expression? graph-expression-with-info)))
    (t
     (let ((compiled-expression?
	     (compile-expression graph-expression-with-info nil nil)))
       (return-compiled-graph-expression-if-ok 
	 compiled-expression? compiled-expression?)))))

(defun graph-expression-uses-local-name-p (compiled-graph-expression)
  (and (consp compiled-graph-expression)
       (eq (car compiled-graph-expression) 'let)))

(defun return-compiled-graph-expression-if-ok (compiled-expression? form-to-return)
  (when compiled-expression?
    (cond
      ((graph-expression-uses-local-name-p compiled-expression?)
       (setq graph-expression-uses-local-name? t)
       nil)
      (t
       form-to-return))))




;;;; Expression writing



(defun write-expression (exp)
  (if (symbolp exp)
      (twrite exp)			; capitalize a single name.
      (write-exp exp 0)))


#+unused
(defun write-expression-with-state (exp alist)
  (write-expression exp)
  (when alist
    (twrite " where ")
    (write-alist alist nil)))


;;; The function `write-alist' writes a list of bindings and values suitable
;;; for messages and tracing. If tail is not nil, it stops writing just before
;;; the cons which is (eq to) tail.

#+unused
(defun write-alist (alist tail)
  (loop for cons on alist
	until (eq cons tail)
	for ((symbol . value) . rest) = cons doing
    (twrite-symbol symbol)
    (cond
      (value
       (twrite " = ")
       (if (framep value)
	   (tformat "~nf" value)
	   (tformat "~nc" (constant-value value) (constant-type value))))
      (t
       (twrite-string " has no value")))
    (unless (eq rest tail) (twrite ", "))))




(defconstant precedence-table '((or . 20) (and . 20) (not . 30)
				(= . 50) (/= . 50) (< . 50) (<= . 50) (> . 50) (>= . 50) 
				(+ . 100) (- . 100) (* . 110) (/ . 110) (^ . 120)
			  
  ))




(defun write-exp (exp external-precedence)
  (cond
    ((symbolp exp) (twrite-symbol exp))
    ((managed-float-p exp)
     (with-temporary-gensym-float-creation write-exp
       (twrite-float (managed-float-value exp))
       nil))
    ((floatp exp) (twrite-float exp))
    ((numberp exp) (twrite exp))
    ((text-string-p exp)
     (tformat "~s" exp)
     ;; previous was wrong!  fixed. (MHD 2/15/96)
;     (twrite '\") (twrite exp) (twrite '\")
     )

    ((atom exp) (twrite "!!!"))

    ((numberp (car exp)) (print-constant (car exp) (cdr exp)))
    ((managed-float-p (car exp))
     (with-temporary-gensym-float-creation write-exp
       (print-constant
	 (managed-float-value (car exp))
	 (cdr exp))
       nil))
    
    ((and (consp exp)
	  (or (evaluation-sequence-p exp)
	      (evaluation-structure-p exp)))
     (write-evaluation-value exp))

    ;; The following clause is necessary because some callers of
    ;; write-exp pass in parse-phrases rather than simply
    ;; evaluation-values.
    ((and (consp exp)
	  (or (phrase-structure-p exp)
	      (phrase-sequence-p exp)))
     (let ((temporary-for-writing (copy-for-slot-value exp)))
       (write-exp temporary-for-writing 0)
       (reclaim-slot-value temporary-for-writing)))
    
    (t (let* ((op (car exp))
	      (op-precedence (cdr (assq op precedence-table)))
	      (form-writer (evaluator-form-writer op)))
	 (cond
	   (op-precedence
	    (unless (> op-precedence external-precedence) (twrite '\( ))
	    (write-infix-or-prefix-expression op (cdr exp) op-precedence)
	    (unless (> op-precedence external-precedence) (twrite '\) )))

	   ((designation-p exp) (print-designation exp))

	   (form-writer
	    (funcall-compiled-function form-writer exp))

	   (t (twrite-symbol (car exp))
	      (twrite '\( )
	      (loop for listed-arg on (cdr exp) do
		(write-exp (car listed-arg) 0)
		(if (cdr listed-arg) (twrite ", ")))
	      (twrite '\) )))))))




(defun write-infix-or-prefix-expression (op args op-precedence)
  (cond ((null (cdr args))
	 (twrite op) (twrite " ") 
	 (write-exp (car args) op-precedence))
	(t
	 (loop for listed-arg on args do
	   (write-exp (car listed-arg) op-precedence)
	   (when (cdr listed-arg) (twrite " ") (twrite op) (twrite " "))))))


; designation-p print-designation, print-constant forward reference!!!







;#+development					; ML's
;(defparameter num-test-suite
;	      '(0.0 .09 .1 .11 1.0 1.5 1.2 4325435.34 .0000543
;		      .0004 .00004 .000004
;		    .303 .3003 .30003 .300003 .0303 .03003 .030003
;		    .0300003 .03000003 .003006 .00300006 .003000006 
;		    .0030000057 .0030000006 34.053 -5342.0 -4524354.0e12
;		    -.0000004504)) 

;#+development					; ML's
;(defun test-floating-numbers ()
;  (terpri)
;  (loop for num in num-test-suite doing
;    (format t "~S~16T" num)
;    (write-string (twith-output-to-text-string (write-float num)))
;    (terpri)))







;;;; Grammar for dates

;(defconstant map-month-to-number-code
;	     '((Jan 1 31)
;	       (Feb 2 28)
;	       (Mar 3 31)
;	       (Apr 4 30)
;	       (May 5 31)
;	       (Jun 6 30)
;	       (Jul 7 31)
;	       (Aug 8 31)
;	       (Sep 9 30)
;	       (Oct 10 31)
;	       (Nov 11 30)
;	       (Dec 12 31)))


(def-grammar-category date? ()
  ('none)
  (date))

(def-grammar-category date ()
  ((day month year) (1 2 3) transform-input-phrase-into-universal-date))

(def-grammar-category day () (positive-integer))

(def-grammar-category month ()
  ('jan)
  ('feb)
  ('mar) 
  ('apr)
  ('may)
  ('jun)
  ('jul) 
  ('aug)
  ('sep)
  ('oct)
  ('nov)
  ('dec))

(def-grammar-category year ()
  (positive-integer))

#+obsolete
(add-grammar-rules
  '((date? 'none)
    (date? date)
    (date (day month year) (1 2 3) transform-input-phrase-into-universal-date)

    (day positive-integer)

    (month 'jan)
    (month 'feb)
    (month 'mar) 
    (month 'apr)
    (month 'may)
    (month 'jun)
    (month 'jul) 
    (month 'aug)
    (month 'sep)
    (month 'oct)
    (month 'nov)
    (month 'dec)

    (year positive-integer)
    ))




;;; `Transform-input-phrase-into-universal-date' is a grammar rule
;;; transformation function that either returns a universal date encoding or the
;;; values bad-phrase and a string, "date outside of legal range".  The
;;; non-bad-phrase return value is the non-nil result of calling
;;; convert-input-to-universal-date with list passed through in the format
;;; defined for it.  See convert-input-to-universal-date in module SEQUENCES1
;;; for further information.

(defun transform-input-phrase-into-universal-date (list)
  (or (convert-input-to-universal-date list)
      (values bad-phrase "date outside of legal range")))

(declare-grammar-transform-can-return-bad-phrase transform-input-phrase-into-universal-date)

(def-slot-value-compiler date? (translation)
  (if (eq translation 'none) nil translation))

(def-slot-value-writer date? (value)
  (if (null value)
      (twrite "none")
      (multiple-value-bind (day month year)
	  (decode-universal-date value)
	(print-decoded-date day month year))))




;;;; Formats


(add-grammar-rules
  '(;(format-form whole-string)
    (format-form (left-string open-format-expression)
		       (format-form 1 2) simplify-associative-operation)

    (open-format-expression (format-expression right-string)
		       (format-form 1 2) simplify-associative-operation)
    (open-format-expression (format-expression format-expression-tail)
		       (format-form 1 2) simplify-associative-operation)

    (format-expression-tail (middle-string open-format-expression)
		       (format-form 1 2) simplify-associative-operation)

    (format-expression expression)

    ;; "a-or-an" in the following two rules used to be 'a and 'an, respectively,
    ;; but that was too cute; when users selected "an" they would get a different
    ;; grammar than if they had selected "a", since the two rules contributed
    ;; different endings following "a" and "an".  (MHD 1/11/91)
    (format-expression
      (expression 'as a-or-an 'time 'stamp) (format 1 'time-stamp))
    (format-expression
      (expression 'as a-or-an 'interval) (format 1 'seconds))
    (format-expression
      (expression 'as ddd.dddd-format) (ddd.dddd-format 1 3) check-ddd-dddd-format)

    ;; Removed -- was redundant with ddd.dddd-format.  Usage replaced with
    ;; ddd.dddd-format for above format-expression grammar and also for the
    ;; message-expression and unique-expression grammar (below).  (MHD 11/8/04)
;    (format unreserved-symbol)

    (expression format-form)

    ;; Unique version of above

    ;(unique-format-form whole-string)
    (unique-format-form (left-string unique-open-format-expression)
		       (format-form 1 2) simplify-associative-operation)

    (unique-open-format-expression (unique-format-expression right-string)
		       (format-form 1 2) simplify-associative-operation)
    (unique-open-format-expression (unique-format-expression unique-format-expression-tail)
		       (format-form 1 2) simplify-associative-operation)

    (unique-format-expression-tail (middle-string unique-open-format-expression)
		       (format-form 1 2) simplify-associative-operation)

    (unique-format-expression unique-expression)

    ;; "a-or-an" in the following two rules used to be 'a and 'an, respectively,
    ;; but that was too cute; when users selected "an" they would get a different
    ;; grammar than if they had selected "a", since the two rules contributed
    ;; different endings following "a" and "an".  (MHD 1/11/91)
    (unique-format-expression
      (unique-expression 'as a-or-an 'time 'stamp) (format 1 'time-stamp))
    (unique-format-expression
      (unique-expression 'as a-or-an 'interval) (format 1 'seconds))
    (unique-format-expression
      (unique-expression 'as ddd.dddd-format) (ddd.dddd-format 1 3) check-ddd-dddd-format)

    (unique-expression unique-format-form)

    ))




;;;; Miscellaneous system parameters

(def-system-frame miscellaneous-parameters grammar7
  (repeat-random-function-on-reset? nil vector-slot system (type yes-or-no))
  (initial-margin-for-workspaces
    (:funcall-at-load-time
      get-slot-init-form kb-workspace workspace-margin)
    vector-slot system (type initial-margin-for-workspaces))

  ;; Added, jh, 7/23/91.
  (start-kb-after-load? nil vector-slot system (type yes-or-no))

  ;; The g2-run-state attribute holds the symbols reset, running, or paused.
  (g2-run-state (:funcall current-g2-run-state) vector-slot system
		do-not-save not-user-editable (type g2-run-state))

  (confirm-run-state-changes nil system (type yes-or-no)) ; Added for 8.3b0 -fmw, 2/14/07

  ;; Added cpm, 1/19/95.  Users can specify feature behavior that has changed
  ;; from an earlier version of G2.  For example, the user may not want a
  ;; specific bug fix, such as the insert action, in all cases, signaling an
  ;; error for duplicate elements.
  (backward-compatibility-features
    nil vector-slot system (type backward-compatible-g2-feature-list))

  ;; Next 3: to be moved to item-reference-parameters (g2-rpc3), in a future release?
  (show-uuids-in-attribute-tables nil (system) (save) (type yes-or-no))
  (interface-home-attribute
    names system do-not-save (do-not-put-in-attribute-tables)
    (type interface-home-attribute))
  (local-item-home
    nil system do-not-save (do-not-put-in-attribute-tables)
    (type local-item-home))

  ;; Toggle to activiate previously NUPEC-only features -dkuznick, 7/14/98
  (explanation-related-features-enabled? nil lookup-slot system (type yes-or-no))

  (connection-caching-enabled? nil lookup-slot system (type yes-or-no))
  
  ;; Maybe add later?!  (MHD 6/15/90)
;  (kb-name
;    nil vector-slot (type symbol?))

;  (initial-width-for-workspaces
;    700
;    vector-slot system (type initial-width-or-height-for-workspaces))
;  (initial-height-for-workspaces
;    500
;    vector-slot system (type initial-width-or-height-for-workspaces))

  ;; This slot overrides the default for the KB. This slot has a specially
  ;; handled default: when G2 5.x KBs are loaded, this is initialized to G2-5.X
  ;; by a post-loading function.  Otherwise, the default is nil, meaning check
  ;; further down. Added for G2 6.0b1. (MHD 3/28/01)
  (default-window-style nil vector-slot system (type g2-window-style-override))

  ;; Covers both login and password-change dialogs.
  (prefer-native-login-dialog t (type yes-or-no) vector-slot system save)
  (automatic-deadlock-detection-frequency nil (type deadlock-detection-frequency-type) vector-slot system save)
  
  ;; Default values to be used for all float number to text transformations (abto 09/17/08)
  (float-to-text-default-format default (type floating-point-number-text-style-name) vector-slot system)
  (float-to-text-default-precision 3 (type floating-point-number-precision) vector-slot system)
  (calculate-time-of-called-procedures true vector-slot system (type yes-or-no))
  (charting-library gigasoft (type charting-library-type-select) (vector-slot) (system) (save))
  (write-extended-memory-report? nil vector-slot system (type yes-or-no))
  (ignore-inlineable-declaration-for-items? nil vector-slot system (type yes-or-no))
  (allow-only-one-table-display-for-item? nil (system) (save) (type yes-or-no))
  (disconnect-dead-connections? nil (system) (save) (type yes-or-no))
  (dead-connection-timeout 200 (vector-slot) (system) (save) (type positive-integer))
  (use-unicode-for-filenames? t (system) (save) (type yes-or-no)))


(add-grammar-rules
 '((charting-library-type-select 'gigasoft)
   (charting-library-type-select 'jfreechart)))
   
(def-slot-value-compiler charting-library-type-select (parse-result)
  parse-result)
  
(def-slot-value-writer charting-library-type-select (value)
  (cond
    ((eq value 'gigasoft) (twrite "gigasoft"))
    ((eq value 'jfreechart) (twrite "jfreechart"))
    (t (twrite "gigasoft"))))
    
(define-category-evaluator-interface (charting-library-type-select
				       :access read-write)
    (member gigasoft jfreechart)
  
  ((set-form (evaluation-value))
   evaluation-value)
  ((get-form (slot-value))
   slot-value))
   
  
(add-grammar-rules
 '((deadlock-detection-frequency-type interval) ; If this fails, go  back to (float 'seconds) 1)
   (deadlock-detection-frequency-type 'never)))

(def-slot-value-writer deadlock-detection-frequency-type (value)
  (cond
    ((fixnump value)
     (tformat "~f seconds" value))
    ((null value)
     (tformat "never"))
     #+development ; unknown thing if this happens!
     (t (tformat "??? ~s ???" value))))

(define-category-evaluator-interface (deadlock-detection-frequency-type
				       :access read-write)
    (or (member never) integer)
  ((set-form (evaluation-value))
   (case evaluation-value
     ((never) 'never)
     (t       
      (phrase-cons evaluation-value 'seconds))))
  ((get-form (slot-value))
   (case slot-value
     ((nil) 'never)
     (t slot-value))))

;;; Assumes interval is in seconds, and just stores it as an integer.
(def-slot-value-compiler deadlock-detection-frequency-type (parse-result)
  (cond
   ((eq parse-result 'never)
    nil)
   ((not (<f 0 (car parse-result)))
    (values
      bad-phrase
      (copy-text-string "The interval must be at least 1 second")))
   (t (car parse-result))))

(def-slot-putter automatic-deadlock-detection-frequency (miscellaneous-parameters-frame new-value)
  (setf (automatic-deadlock-detection-frequency miscellaneous-parameters-frame) new-value)
  (when (eq miscellaneous-parameters miscellaneous-parameters-frame)
    (set-deadlock-detection-frequency new-value nil))
  new-value)

(def-class-method activate (miscellaneous-parameters)
  (when (system-table-installed-p miscellaneous-parameters)
    (set-deadlock-detection-frequency
      (automatic-deadlock-detection-frequency miscellaneous-parameters) t)))

(define-slot-alias enable-explanation-controls explanation-related-features-enabled?
  miscellaneous-parameters)

(def-class-method install-system-table (miscellaneous-parameters)
  (use-role-caching (connection-caching-enabled? miscellaneous-parameters))
  (setq cached-name-for-local-home nil)  ; pertains to local-item-home slot
  (when servicing-workstation?
    (reset-current-workstation-new-g2-classic-ui-p))
  (set-deadlock-detection-frequency (automatic-deadlock-detection-frequency miscellaneous-parameters) nil)
  nil)

(def-class-method deinstall-system-table (miscellaneous-parameters)
  (use-role-caching nil)
  (setq cached-name-for-local-home nil)  ; pertains to local-item-home slot
  (when servicing-workstation?
    (reset-current-workstation-new-g2-classic-ui-p))
  nil)

;; Propagate a right-click-lifts-to-top-in-native-ui change to all clients.
(def-slot-putter backward-compatibility-features (miscellaneous-parameters value)
  ;; Only 8.2r1 prerelease KBs could have this flag.
  #+development
  (when (memq 'right-click-lifts-to-top-in-native-ui value)
    (dwarn "Discarding backward-compatibility flag ~S" 'right-click-lifts-to-top-in-native-ui))

  (setf (backward-compatibility-features miscellaneous-parameters)
	(delete-slot-value-element 'right-click-lifts-to-top-in-native-ui value))

;  (let ((old (right-click-lifts-to-top-in-native-ui-p)))
;    (setf (backward-compatibility-features miscellaneous-parameters) value)
;    (when (and (system-table-installed-p miscellaneous-parameters)
;	       (not (eql (right-click-lifts-to-top-in-native-ui-p) old)))
;      (initialize-ui-options-on-all-workstations)))
  value)

(def-slot-putter connection-caching-enabled? (miscellaneous-parameters value)
  (if (system-table-installed-p miscellaneous-parameters)
      (use-role-caching value))
  (setf (connection-caching-enabled? miscellaneous-parameters) value))

(defun start-kb-after-load-from-system-table? ()
  (start-kb-after-load? miscellaneous-parameters))
  
(defun float-to-text-default-format-from-system-table ()
  (float-to-text-default-format miscellaneous-parameters))

(defun allow-only-one-table-display-for-item?-from-system-table ()
  (allow-only-one-table-display-for-item? miscellaneous-parameters))

(defun float-to-text-default-precision-from-system-table ()
  (float-to-text-default-precision miscellaneous-parameters))

(defun disconnect-dead-connections?-from-system-table ()
  (disconnect-dead-connections? miscellaneous-parameters))

(defun dead-connection-timeout-from-system-table ()
  (dead-connection-timeout miscellaneous-parameters))

(defun use-unicode-for-filenames?-from-system-table ()
  (use-unicode-for-filenames? miscellaneous-parameters))


;;; The function `explanation-related-features-enabled-func?' is needed to
;;; forward reference explanation-related-features-enabled? (a macro) in various
;;; places (DEBUG, FRAMES2A, etc) -dkuznick, 7/15/98

(defun-simple explanation-related-features-enabled-func? ()
  (explanation-related-features-enabled? miscellaneous-parameters))


;;; The attribute `g2-run-state' is used to inform the user what G2's current
;;; running state is, either reset, running or paused.  Whenever a change to the
;;; system-is-running or system-has-paused variables occurs, the function
;;; `update-g2-run-state' should be called to update the
;;; miscellaneous-parameters system-tables.

(def-slot-value-writer g2-run-state (value)
  (twrite-symbol value))

(define-category-evaluator-interface (g2-run-state
				       :access read
				       :simple-type-specification symbol)
    (member reset running paused abort)
  ((get-form (slot-value))
   slot-value))

(defun-void update-g2-run-state ()
  (let ((run-state (current-g2-run-state)))
    (loop for system-frame being each class-instance of 'miscellaneous-parameters
	  do
      (change-slot-value system-frame 'g2-run-state run-state))))


(defun confirm-run-state-changes-p ()
  (confirm-run-state-changes miscellaneous-parameters))



(add-grammar-rules-for-list
  'backward-compatible-g2-feature-list 'backward-compatible-g2-feature-list-item nil nil 'none)

(define-category-evaluator-interface (backward-compatible-g2-feature-list
				       :access read-write)
   (or (no-item) (sequence (member ignore-duplicate-list-element-error
				   extra-vertices-in-g2-get-connection-vertices
				   print-means-print-to-server-in-configurations
;				   right-click-lifts-to-top-in-native-ui
				   inconsistent-behavior-of-move-in-configurations
				   ignore-snap-grid-in-transfer-operations
				   first-value-ok-for-the-named-by-grammar)
			   0))
  
  ((set-form (evaluation-value))
   (if (evaluation-sequence-p evaluation-value)
       (with-evaluation-sequence-to-phrase-list-mapping
	   (evaluation-value element)
	 element)
       ;; The following is the no-value case
       evaluation-value))
  ((get-form (slot-value))
   (when slot-value
     (allocate-evaluation-sequence
       (copy-list-using-eval-conses slot-value)))))

(define-category-evaluator-interface (initial-margin-for-workspaces
				       :access read-write)
    integer
  ((set-form (evaluation-value))
   evaluation-value)
  ((get-form (slot-value))
   slot-value))

(add-grammar-rules
  '((initial-margin-for-workspaces integer)
    ;; Maybe add later?! (MHD 6/15/90)
;    (initial-margin-for-workspaces 'standard)
;    (initial-width-or-height-for-workspaces integer)
;    (initial-margin-for-workspaces 'standard)
    (backward-compatible-g2-feature-list-item
     ('ignore 'duplicate 'list 'element 'error)
     ignore-duplicate-list-element-error)
    (backward-compatible-g2-feature-list-item
     ('extra 'vertices 'in 'g2-get-connection-vertices)
     extra-vertices-in-g2-get-connection-vertices)
    (backward-compatible-g2-feature-list-item
     ('print 'means 'print-to-server 'in 'configurations)
     print-means-print-to-server-in-configurations)
;    (backward-compatible-g2-feature-list-item
;     ('right 'click 'lifts 'to 'top 'in 'native 'ui)
;     right-click-lifts-to-top-in-native-ui)
    (backward-compatible-g2-feature-list-item
     ('inconsistent 'behavior 'of 'move 'in 'configurations)
     inconsistent-behavior-of-move-in-configurations)
    (backward-compatible-g2-feature-list-item
     ('ignore 'snap 'grid 'in 'transfer 'operations)
     ignore-snap-grid-in-transfer-operations)
    (backward-compatible-g2-feature-list-item
     ('first 'value 'ok 'for 'the 'named-by 'grammar)
     first-value-ok-for-the-named-by-grammar)))


(def-slot-value-writer initial-margin-for-workspaces (value)
  (tformat "~d" value))

(def-slot-value-writer initial-width-or-height-for-workspaces (value)
  (tformat "~d" value))


(def-slot-value-compiler backward-compatible-g2-feature-list (parse-result variable-or-definition)
  (declare (ignore variable-or-definition))
  (let ((result nil))
    (loop for an-item in parse-result
	  do
      (unless (or (eq an-item '\,)
		  (memq an-item result))
	(phrase-push an-item result)))
    (nreverse result)))
    
(defun-simple twrite-backward-compatible-g2-feature-list-item (symbol)
  (case symbol
    (ignore-duplicate-list-element-error
     (tformat "ignore duplicate list element error"))
    (extra-vertices-in-g2-get-connection-vertices
     (tformat "extra vertices in g2-get-connection-vertices"))
    (print-means-print-to-server-in-configurations
     (tformat "print means print-to-server in configurations"))
;    (right-click-lifts-to-top-in-native-ui
;     (tformat "right click lifts to top in native ui"))
    (inconsistent-behavior-of-move-in-configurations
     (tformat "inconsistent behavior of move in configurations"))
    (ignore-snap-grid-in-transfer-operations
     (tformat "ignore snap grid in transfer operations"))
    (first-value-ok-for-the-named-by-grammar
     (tformat "first value ok for the named-by grammar"))
    (t
     (dwarn "Unknown symbol ~s in backward-compatible-g2-feature-list" symbol)
     (twrite "unknown"))))

(def-slot-value-writer backward-compatible-g2-feature-list (value)
  (twrite-list value :empty "none" :conjoiner ", "
	       :element-writer #'twrite-backward-compatible-g2-feature-list-item))


(defmacro backward-compatibility-features-check (feature-name)
  `(memq ,feature-name
	 (backward-compatibility-features miscellaneous-parameters)))


;;; The function `insert-action-duplicate-element-backward-compatibility-p'
;;; returns T if the insert action should have the version 3.0 behavior, when
;;; attempting to insert duplicate elements into a list.  In version 3.0, the
;;; insert action would silently not add duplicate elements to the beginning or
;;; end of the list, if restricted by the list.  (No error was signaled.)  In
;;; version 4.0, the default is to signal an error.

;;; Note that in both versions 3.0 and 4.0, insertion of duplicate elements,
;;; when duplicates are not allowed, BEFORE and AFTER another element does
;;; signal an error.  (The version 4.0 fix was to make all versions of the
;;; insert action behave the same and signal an error when duplicates are not
;;; allowed.)

;;; This option was made available to KB's, including GDA and GUIDE, that rely
;;; on the version 3.0 behavior.

(defun insert-action-duplicate-element-backward-compatibility-p ()
  (backward-compatibility-features-check 'ignore-duplicate-list-element-error))



;;; The function `set-ignore-insert-action-duplicate-element' sets a slot of the
;;; miscellaneous parameters system-table to indicate that the insert duplicate
;;; list element error should be ignored as in version 3.0 (for the insert at
;;; the beginning and the end of the g2-list).

(defun set-ignore-insert-action-duplicate-element ()
  (slot-value-pushnew
    'ignore-duplicate-list-element-error
    (backward-compatibility-features miscellaneous-parameters)))



(defun get-connection-vertices-backward-compatibility-p ()
  (backward-compatibility-features-check 'extra-vertices-in-g2-get-connection-vertices))

(defun set-get-connection-vertices-backward-compatibility ()
  (slot-value-pushnew
    'extra-vertices-in-g2-get-connection-vertices
    (backward-compatibility-features miscellaneous-parameters)))



(defun print-means-print-to-server-in-configurations-p ()
  (backward-compatibility-features-check 'print-means-print-to-server-in-configurations))

(defun set-print-means-print-to-server-in-configurations ()
  (slot-value-pushnew
    'print-means-print-to-server-in-configurations
    (backward-compatibility-features miscellaneous-parameters)))


;(defun right-click-lifts-to-top-in-native-ui-p ()
;  (backward-compatibility-features-check 'right-click-lifts-to-top-in-native-ui))

;(defun set-right-click-lifts-to-top-in-native-ui ()
;  (slot-value-pushnew
;    'right-click-lifts-to-top-in-native-ui
;    (backward-compatibility-features miscellaneous-parameters)))


(defun inconsistent-behavior-of-move-in-configurations-p ()
  (backward-compatibility-features-check 'inconsistent-behavior-of-move-in-configurations))

(defun set-inconsistent-behavior-of-move-in-configurations ()
  (slot-value-pushnew
    'inconsistent-behavior-of-move-in-configurations
    (backward-compatibility-features miscellaneous-parameters)))


(defun ignore-snap-grid-in-transfer-operations-p ()
  (backward-compatibility-features-check 'ignore-snap-grid-in-transfer-operations))

(defun set-ignore-snap-grid-in-transfer-operations ()
  (slot-value-pushnew
    'ignore-snap-grid-in-transfer-operations
    (backward-compatibility-features miscellaneous-parameters)))


(defun first-value-ok-for-the-named-by-grammar-p ()
  (backward-compatibility-features-check 'first-value-ok-for-the-named-by-grammar))

(defun set-first-value-ok-for-the-named-by-grammar ()
  (slot-value-pushnew
    'first-value-ok-for-the-named-by-grammar
    (backward-compatibility-features miscellaneous-parameters)))


;;; The slot value compiler for initial-margin-for-workspaces expects parse-
;;; result to be either the symbol STANDARD or a fixnum integer.  If parse-
;;; result is STANDARD, the default slot value for the workspace-margin slot
;;; of the class kb-workspace is returned; if parse-result is not in the
;;; range [0,100], then bad-phrase and a text string explaining the problem
;;; are returned; otherwise, parse-result is returned.

(def-slot-value-compiler initial-margin-for-workspaces (parse-result)
  (if (eq parse-result 'standard)
      (get-slot-init-form
	'kb-workspace 'workspace-margin)
      (if (or (<f parse-result 0) (>f parse-result 100))
	  (values
	    bad-phrase
	    (copy-text-string
	      "Please choose an integer between 0 and 100."))
	  parse-result)))

;; Note that parse-result can actually only be integer at present.  Standard is
;; an idea to "maybe add later?!" (MHD 6/15/90)



;; Maybe add later?! (MHD 6/15/90)
;(def-slot-value-compiler initial-width-or-height-for-workspaces
;			 (parse-result frame slot-name)
;  (declare (ignore frame))
;  (if (eq parse-result 'standard)
;      (get-slot-init-form
;	'miscellaneous-parameters slot-name)
;      (if (or (<f parse-result 0) (>f parse-result 100))
;	  (values
;	    bad-phrase
;	    (copy-text-string
;	      "Please choose an integer between 1 and 3000."))
;	  parse-result)))

;; Consider changing "for-workspaces" to "for-kb-workspaces".


(defun repeat-random-function-on-reset?-function (miscellaneous-parameters)
  (repeat-random-function-on-reset? miscellaneous-parameters))

;;Move this function after the definition of miscellaneous-parameters
(defun block-can-be-inlined-p (block)
  (if (and miscellaneous-parameters
           (ignore-inlineable-declaration-for-items? miscellaneous-parameters))
      nil 
      (get-property-value-in-object-configuration block 'inlineable nil)))


(def-slot-putter default-window-style (miscellaneous-parameters value initializing-p)
  (prog1 (setf (default-window-style miscellaneous-parameters) value)
    (when (and servicing-workstation?
	       (not initializing-p)
	       (system-table-installed-p miscellaneous-parameters))
      (reset-current-workstation-new-g2-classic-ui-p))))
      
      
      
;;; Floating Point Default Style


(add-grammar-rules
  '((floating-point-number-text-style-name 'default)
    (floating-point-number-text-style-name 'float)
    (floating-point-number-text-style-name 'exponent)
    (floating-point-number-text-style-name 'best)
    (floating-point-number-text-style-name 'force-zero)
    (floating-point-number-precision non-negative-integer)))
  
(def-slot-value-compiler floating-point-number-text-style-name (parse-result)
  parse-result)
  
(def-slot-value-writer floating-point-number-text-style-name (value)
  (cond
    ((eq value 'default) (twrite "default"))
    ((eq value 'float) (twrite "float"))
    ((eq value 'exponent) (twrite "exponent"))
    ((eq value 'best) (twrite "best"))
    ((eq value 'force-zero) (twrite "force-zero"))
    (t (twrite "none"))))
    
(define-category-evaluator-interface (floating-point-number-text-style-name
				       :access read-write)
    (member default float exponent best force-zero)
  
  ((set-form (evaluation-value))
   evaluation-value)
  ((get-form (slot-value))
   slot-value))
   
(def-slot-value-compiler floating-point-number-precision (parse-result)
  (cond
    ; 0 >= precision >= 16
    ; See also comments on write-floating-point-number-simple-c-format (abto 09/17/08)
    ((not (<=f 0 parse-result 16))
     (values
       bad-phrase
       (twith-output-to-text-string
	 (tformat
	   "Floating point number precision must be a number between 0 and 16."))))
    (t parse-result)))
    
(def-slot-value-writer floating-point-number-precision (value)
  (twrite value))
  
(define-category-evaluator-interface (floating-point-number-precision
				       :access read-write)
    (named non-negative-integer)
  ((set-form (evaluation-value))
   (call-category-setter 'non-negative-integer evaluation-value nil nil nil))
  ((get-form (slot-value))
   (call-category-getter 'non-negative-integer slot-value nil nil)))


;;;; Log File




(add-grammar-rules
  '((log-file-directory 'default )
    (log-file-directory whole-string)
    (log-file-name whole-string)
    (log-file-maximum positive-integer?)

    (close-log-file update-log-file)
    (back-up-log-file 'never)
    (back-up-log-file update-log-file)

    (update-log-file ('after log-file-message-count) (2))
    (update-log-file ('after interval) (2))
    (update-log-file ('after log-file-message-count 'or interval
		      '\, 'whichever 'comes 'first)
		    (2 4))
    (update-log-file ('after interval 'or log-file-message-count
		      '\, 'whichever 'comes 'first)
		    (2 4))
    (log-file-message-count (integer 'messages) 1)
    (log-file-message-count (integer 'message) 1)))



;; In BOOKS

(declare-forward-reference log-file-outputting? variable)



(def-slot-value-writer log-file-directory (thing)
  (cond ((null thing)
	 (twrite 'default))
	(t (twrite-parsably thing))))

(define-category-evaluator-interface (log-file-directory
				       :access read-write)
    (or (member default)
	(named whole-string))
  ((set-form (evaluation-value))
   (if (eq evaluation-value 'default)
       evaluation-value
       (call-category-setter 'whole-string evaluation-value nil nil nil)))
  ((get-form (slot-value))
   (if slot-value
       (call-category-getter 'whole-string slot-value nil nil)
       'default)))

(def-slot-value-compiler log-file-directory (parse-result)
  (cond
    ((or log-file-outputting?
	 (log-file-enabled? log-file-parameters))
     (values
       bad-phrase
       (twith-output-to-text-string
	 (twrite-string
	   "You can not change this value while Log File is enabled."))))
    ((eq parse-result 'default) nil)
    (t parse-result)))


(def-slot-value-writer log-file-name (thing)
  (tformat "~s" (if (text-string-p thing) thing #w"")))

(define-category-evaluator-interface (log-file-name
				       :access read-write)
    (named whole-string)
  ((set-form (evaluation-value))
   (call-category-setter 'whole-string evaluation-value nil nil nil))
  ((get-form (slot-value))
   (call-category-getter
     'whole-string
     (if (text-string-p slot-value)
	 slot-value
	 #w"")
     nil nil)))

(def-slot-value-compiler log-file-name (parse-result)
  (cond
    ((or log-file-outputting?
	 (log-file-enabled? log-file-parameters))
     (values
       bad-phrase
       (twith-output-to-text-string
	 (twrite-string
	   "You can not change this value while Log File is enabled."))))
    (t parse-result)))


(def-slot-value-writer log-file-maximum (thing)
  (cond ((null thing)
	 (twrite 'none))
	(t (twrite thing))))

(define-category-evaluator-interface (log-file-maximum
				       :access read-write)
    (named positive-integer?)
  ((set-form (evaluation-value))
   (call-category-setter 'positive-integer? evaluation-value nil nil nil))
  ((get-form (slot-value))
   (call-category-getter 'positive-integer? slot-value nil nil)))

(def-slot-value-compiler log-file-maximum (parse-result)
  (cond
    ((eq parse-result 'none)
     nil)
    ((not (<f 0 parse-result 1000))
     (values
       bad-phrase
       (twith-output-to-text-string
	 (tformat
	   "The maximum number of log files must be either none or a number ~
            between 1 and 999."))))
    (t parse-result)))



(define-category-evaluator-interface (update-log-file
				       :access read-write)
    (or (no-item) ; see uiltdlg.kb for an example of this
	(structure log-file-spec
		   ((after-messages integer)
		    (after-interval integer))
		   (or after-messages after-interval)))
  ((set-form (evaluation-value))
   (when evaluation-value
     (with-structure (evaluation-value log-file-spec)
       (nconc
	 (when after-messages
	   (phrase-list after-messages))
	 (when after-interval
	   (phrase-list (phrase-cons after-interval 'seconds)))))))
  ((get-form (slot-value))
   (gensym-dstruct-bind ((value-1? value-2?) slot-value)
     (let* ((interval-first? (consp value-1?))
	    (source-maximum-interval
	      (cond
		(interval-first? (car-of-cons value-1?))
		(value-2? (car-of-cons value-2?))
		(t nil)))
	    (source-maximum-messages
	      (if (not interval-first?)
		  value-1?
		  value-2?)))
       (when (or source-maximum-messages source-maximum-interval)
	 (with-new-structure (log-file-spec)
	   (setf-non-nil after-messages source-maximum-messages)
	   (setf-non-nil after-interval source-maximum-interval)))))))

(def-slot-value-writer close-log-file (message-count-and-interval)
  (update-log-file-slot-value-writer message-count-and-interval))

(define-category-evaluator-interface (close-log-file
				       :access read-write)
    (named update-log-file)
  ((set-form (evaluation-value))
   (call-category-setter 'update-log-file evaluation-value nil nil nil))
  ((get-form (slot-value))
   (call-category-getter 'update-log-file slot-value nil nil)))

(def-slot-value-compiler close-log-file (message-count-and-interval)
  (update-log-file-slot-value-compiler message-count-and-interval))


(def-slot-value-writer back-up-log-file (message-count-and-interval)
  (if (null message-count-and-interval)
      (twrite-symbol 'never)
      (update-log-file-slot-value-writer message-count-and-interval)))

(define-category-evaluator-interface (back-up-log-file
				       :access read-write)
    (or (member never)
	(named update-log-file))
  ((set-form (evaluation-value))
   (if (eq evaluation-value 'never)
       'never
       (call-category-setter 'update-log-file evaluation-value nil nil nil)))
  ((get-form (slot-value))
   (if slot-value
       (call-category-getter 'update-log-file slot-value nil nil)
       'never)))

(def-slot-value-compiler back-up-log-file (message-count-and-interval)
  (cond ((eq message-count-and-interval 'never) nil)
	(t (update-log-file-slot-value-compiler message-count-and-interval))))



(defun update-log-file-slot-value-writer (message-count-and-interval)
  (let* ((interval-count-first? (consp (first message-count-and-interval)))
	 (message-count? (when message-count-and-interval
			   (if interval-count-first?
			       (second message-count-and-interval)
			       (first message-count-and-interval))))
	 (interval? (when message-count-and-interval
			    (if interval-count-first?
				(first message-count-and-interval)
				(second message-count-and-interval)))))
    (cond ((null message-count-and-interval) (twrite-symbol 'none))
	  ((and interval-count-first? interval?)
	   (twrite-string "after ")
	   (print-constant (first interval?) 'seconds)
	   (when message-count?
	     (tformat " or ~d" message-count?)
	     (if (=f message-count? 1)
		 (twrite-string " message")
		 (twrite-string " messages"))
	     (twrite-string ", whichever comes first")))
	  (message-count?
	   (twrite-string "after ")
	   (twrite message-count?)
	   (if (=f message-count? 1)
	       (twrite-string " message")
	       (twrite-string " messages"))
	   (when interval?
	     (twrite-string " or ")
	     (print-constant (first interval?) 'seconds)
	     (twrite-string ", whichever comes first")))
	  #+development
	  (t
	   (twrite-string " [unknown value in update log file grammar]")))))


(defun update-log-file-slot-value-compiler (message-count-and-interval?)
  (let* ((interval-count-first? (consp (first message-count-and-interval?)))
	 (message-count? (when message-count-and-interval?
			   (if interval-count-first?
			       (second message-count-and-interval?)
			       (first message-count-and-interval?))))
	 (interval? (when message-count-and-interval?
		      (if interval-count-first?
			  (first message-count-and-interval?)
			  (second message-count-and-interval?))))
	 bad-message-count?
	 bad-interval?)

    (when (and message-count? (null (<f 0 message-count? 10000)))
      (setq bad-message-count? t))

    (when (and interval? (<=i (first interval?) 0))
      (setq bad-interval? t))

    (cond ((and bad-message-count? bad-interval?)
	   (values 
	     bad-phrase
	     (twith-output-to-text-string
	       (tformat
		 "The message count, ~d, must be between 1 and 9999."
		 message-count?)
	       (twrite-string "  The interval, ")
	       (print-constant (first interval?) 'seconds)
	       (twrite-string ", must be greater than 0."))))
	  (bad-interval?
	   (values 
	     bad-phrase
	     (twith-output-to-text-string
	       (twrite-string "The interval, ")
	       (print-constant (first interval?) 'seconds)
	       (twrite-string ", must be greater than 0."))))
	  (bad-message-count?
	   (values 
	     bad-phrase
	     (twith-output-to-text-string
	       (tformat
		 "The message count, ~d, must be between 1 and 9999."
		 message-count?))))
	  (t message-count-and-interval?))))

;; This could be written much more simply! (MHD 10/11/91)




(define-category-evaluator-interface (cross-section-pattern
				       :access read-write)
    (or (no-item)
	(structure cross-section-pattern-spec
		   ((cross-section-regions
		      (sequence
			(structure regions-spec
				   ((region-name symbol)
				    (region-color (named color-or-metacolor))))
			1))
		    (cross-section-stripes
		      (sequence
			(structure stripes-spec
				   ((region-name symbol)
				    (region-size integer)))
			1)))
		   (and cross-section-stripes)))
  ((set-form (evaluation-value))
   (evaluation-etypecase
     evaluation-value
     ((no-item) 'inherited)
     ((structure)
      (with-structure (evaluation-value cross-section-pattern-spec)
	(if cross-section-regions
	    (let ((first-part-of-phrase-value
		   (phrase-list
		     (phrase-cons
		       'polychrome
		       (with-evaluation-sequence-to-phrase-list-mapping
			   (cross-section-regions regions-info)
			 (with-structure (regions-info regions-spec)
			   (phrase-cons region-name region-color))))
		     '\,))
		  (second-part-of-phrase-value
		   (with-evaluation-sequence-to-phrase-list-mapping
		       (cross-section-stripes stripes-info)
		     (with-structure (stripes-info stripes-spec)
		       (phrase-cons region-name region-size)))))
	      (nconc first-part-of-phrase-value second-part-of-phrase-value))
	    (let ((stripes-information
		   (with-evaluation-sequence-to-phrase-list-mapping
		       (cross-section-stripes stripes-info)
		     (with-structure (stripes-info stripes-spec)
		       (phrase-cons region-name region-size)))))
	      stripes-information))))))
  ((get-form (slot-value))
   (when slot-value
     (if (cross-section-regions-specified? slot-value)
	 (with-new-structure (cross-section-pattern-spec)
	   (gensym-dstruct-bind
		 ((source-cross-section-regions . source-cross-section-stripes)
		  slot-value)
	       (setf cross-section-regions
		     (with-list-to-evaluation-sequence-mapping
			 (source-cross-section-regions region-info)
		       (with-new-structure (regions-spec)
			 (gensym-dstruct-bind
			     ((source-region-name . source-region-color)
			      region-info)
			   (setf region-name source-region-name)
			   (setf region-color source-region-color)))))
	       (setf cross-section-stripes
		     (with-list-to-evaluation-sequence-mapping
			 (source-cross-section-stripes stripe-info)
		       (with-new-structure (stripes-spec)
			 (gensym-dstruct-bind
			     ((source-region-name . source-region-size)
			      stripe-info)
			   (setf region-name source-region-name)
			   (setf region-size source-region-size)))))))
	   (with-new-structure (cross-section-pattern-spec)
	     (setf cross-section-stripes
		   (with-list-to-evaluation-sequence-mapping
		       (slot-value stripe-info)
		     (with-new-structure (stripes-spec)
		       (gensym-dstruct-bind
			   ((source-region-name . source-region-size)
			    stripe-info)
			 (setf region-name source-region-name)
			 (setf region-size source-region-size))))))))))


(define-category-evaluator-interface (g2-meter-name
				       :access read-write)
    ;; The compiler will catch symbols that are not meter names.
    (or (no-item) symbol)
  ((set-form (evaluation-value))
   (if evaluation-value
       evaluation-value
       'none))
  ((get-form (slot-value))
   (if slot-value
       (loop for name-and-symbol-pair in g2-meter-names-and-forms
	     when (equal slot-value (second name-and-symbol-pair))
	       return (first name-and-symbol-pair)
	       finally (return (first slot-value)))
       nil)))

(define-category-evaluator-interface (gfi-yes-or-no?
				       :access read-write)
    truth-value
  ((set-form (evaluation-value))
   (evaluation-truth-value-is-true-p evaluation-value))
  ((get-form (slot-value))
   (make-evaluation-boolean-value slot-value)))

(define-category-evaluator-interface (gfi-file-format :access read-write)
    (or (no-item) (member event-log spreadsheet))
  ((set-form (evaluation-value))
   (if evaluation-value
       evaluation-value
       'none))
  ((get-form (slot-value))
   slot-value))

(define-category-evaluator-interface (gfi-time-stamp-format
				       :access read-write)
    (member explicit-time-stamp relative-time-stamp)
  ((set-form (evaluation-value))
   (if (eq evaluation-value 'explicit-time-stamp)
       'explicit
       'relative))
  ((get-form (slot-value))
   (if (eq slot-value 'explicit)
       'explicit-time-stamp
       'relative-time-stamp)))

(define-category-evaluator-interface (gfi-output-file-update-frequency
				       :access read-write)
    (or (no-item)
	integer
	(member when-variables-receive-values when-activated
		when-activated-without-interruption))
  ((set-form (evaluation-value))
   (if (fixnump evaluation-value)
       (phrase-list 'write-interval
		    (phrase-cons evaluation-value 'seconds))
       (case evaluation-value
	 (when-variables-receive-values 'when-received-value)
	 (when-activated 'output-one-shot-when-activated)
	 (when-activated-without-interruption
	  'output-one-shot-when-activated-without-interruption)
	 (t 'none))))
  ((get-form (slot-value))
   (if (consp slot-value)
       ;; return seconds as integer
       (car (second slot-value))
       (case slot-value
	 (when-received-value 'when-variables-receive-values)
	 (output-one-shot-when-activated 'when-activated)
	 (output-one-shot-when-activated-without-interruption
	  'when-activated-without-interruption)
	 (t nil)))))

(define-category-evaluator-interface (attributes-which-identify-a-network-item-reference
				       :access read-write)
    (or (no-item)
	(sequence
	  (or symbol
	      (structure class-identifying-attributes-spec
			 ((class symbol)
			  (class-identifying-attributes
			    (sequence
			      (or symbol
				  (structure attribute-translation
					     ((attribute symbol)
					      (name-for-network symbol))))
			      1)))))
	  1))
  ((set-form (evaluation-value))
   (block att-w-iden-s-form-block
    (cond ((null evaluation-value)
	  'none)
	 (t
	  (phrase-cons
	    '\,
	    (with-evaluation-sequence-to-phrase-list-mapping
		(evaluation-value attribute-name)
	      (cond ((symbolp attribute-name)
	                attribute-name)
		    ((null (estructure-slot attribute-name 'class-identifying-attributes nil))
		     (return-from att-w-iden-s-form-block
		      (values bad-phrase (copy-text-string "Incorrect - empty configuration parameters for interface"))))
		    (t
		     (with-structure (attribute-name class-identifying-attributes-spec)
		      (phrase-list 'class
				 class
				 (phrase-cons
				   '\,
				   (with-evaluation-sequence-to-phrase-list-mapping
				       (class-identifying-attributes attribute)
				     (if (symbolp attribute)
					 attribute
					 (with-structure (attribute attribute-translation)
					   (phrase-list attribute name-for-network)))))))))))))))
  ((get-form (slot-value))
   (when slot-value
     (with-list-to-evaluation-sequence-mapping (slot-value attribute-name)
       (if (symbolp attribute-name)
	   attribute-name
	   (with-new-structure (class-identifying-attributes-spec)
	     (gensym-dstruct-bind ((spec-class . spec-class-identifying-attributes)
				  attribute-name)
	       (setf class spec-class)
	       (setf class-identifying-attributes
		     (with-list-to-evaluation-sequence-mapping
			 (spec-class-identifying-attributes attribute)
		       (gensym-dstruct-bind ((spec-attribute . spec-name-for-network)
					    attribute)
			 (if (null spec-name-for-network)
			     spec-attribute
			     (with-new-structure (attribute-translation)
			       (setf attribute spec-attribute)
			       (setf name-for-network spec-name-for-network)))))))))))))

(define-category-evaluator-interface (options-for-item-reference
				       :access read-write)
    (or (no-item)
	(structure options-for-item-reference
		   ((home (member convert-home-to-local no-conversion))
		    (name (member name-includes-home name-includes-home-unless-local no-conversion))
		    (remote-class-prefix (or (no-item) text))
		    (default-remote-class (or (no-item) symbol))
		    (reference-lookup (member look-up-references do-not-look-up-references))
		    (reference-creation (member create-references do-not-create-references)))))
  ((set-form (evaluation-value))
   (if (null evaluation-value)
       nil
       (phrase-cons
	 '\;
	 (with-structure (evaluation-value options-for-item-reference)
	   (phrase-list
	     (nconc
	       (when home
		 (phrase-list 'convert-home-to-local
			      (case home
				(convert-home-to-local 't)
				(no-conversion 'nil))))
	       (when name
		 (phrase-list 'add-home-to-name
			      (case name
				(name-includes-home 't)
				(name-includes-home-unless-local 'unless-local)
				(no-conversion 'nil))))
	       (unless (and (eq 'unsupplied
				(evaluation-structure-slot
				  evaluation-value 'default-remote-class 'unsupplied))
			    (eq 'unsupplied
				(evaluation-structure-slot
				  evaluation-value 'remote-class-prefix 'unsupplied)))
		 (phrase-list 'non-local-item-class
			      default-remote-class
			      remote-class-prefix))
	       (when reference-lookup
		 (phrase-list 'reference-lookup
			      (case reference-lookup
				(look-up-references 't)
				(do-not-look-up-references 'nil))))
	       (when reference-creation
		 (phrase-list 'reference-creation
			      (case reference-lookup
				(create-references 't)
				(do-not-create-references 'nil))))))))))
  ((get-form (slot-value))
   (if (null slot-value)
       nil
       (allocate-evaluation-structure
	 (let ((home nil) (name nil)
	       (default-remote-class nil) (remote-class-prefix nil)
	       (reference-lookup nil)
	       (reference-creation nil))
	   (loop for option in slot-value
	       do (case (first option)
		    (convert-home-to-local
		     (setf home (if (second option)
				    'convert-home-to-local
				    'no-conversion)))
		    (add-home-to-name
		     (setf name (case (second option)
				  ((t)            'name-includes-home)
				  ((unless-local) 'name-includes-home-unless-local)
				  ((nil)          'no-conversion))))
		    (non-local-item-class
		     (when (second option)
		       (setf default-remote-class (second option)))
		     (when (third option)
		       (setf remote-class-prefix (third option))))
		    (reference-lookup
		     (setf reference-lookup (if (second option)
						'look-up-references
						'do-not-look-up-references)))
		    (reference-creation
		     (setf reference-creation (if (second option)
						  'create-references
						  'do-not-create-references)))))
	   (nconc (when home
		    (eval-list 'home home))
		  (when name
		    (eval-list 'name name))
		  (when remote-class-prefix
		    (eval-list 'remote-class-prefix remote-class-prefix))
		  (when default-remote-class
		    (eval-list 'default-remote-class default-remote-class))
		  (when reference-lookup
		    (eval-list 'reference-lookup reference-lookup))
		  (when reference-creation
		    (eval-list 'reference-creation reference-creation))))))))

(define-category-evaluator-interface (gsi-variable-grouping-specification
				       :access read-write)
    (or (no-item)
	(sequence symbol 1))
  ((set-form (evaluation-value))
   (if evaluation-value
       (phrase-cons
	 '\,
	 (with-evaluation-sequence-to-phrase-list-mapping
	     (evaluation-value attribute-name)
	   attribute-name))
       'no-grouping))
  ((get-form (slot-value))
   (if (consp slot-value)
       (with-list-to-evaluation-sequence-mapping (slot-value attribute-name)
	 attribute-name)
       nil)))

(define-category-evaluator-interface (when-to-show-value
					:access read-write)
    (member only-while-sliding always never)
  ((set-form (evaluation-value))
   (if (eq evaluation-value 'only-while-sliding)
       'while-sliding
       evaluation-value))
  ((get-form (slot-value))
   (if (eq slot-value 'while-sliding)
       'only-while-sliding
       (or slot-value
	   'always)))) ; 'nil means 'always

(define-category-evaluator-interface (gfi-input-variables-update-mode
				       :access read-write)
    (or (no-item)
	(member asynchronous-input asynchronous-input-ignoring-the-data-server
		input-on-request-preserving-time-stamps input-on-request-sample-and-hold
		input-when-activated input-when-activated-without-interruption))
  ((set-form (evaluation-value))
   (case evaluation-value
     (asynchronous-input 'asynchronous)
     (asynchronous-input-ignoring-the-data-server
      'asynchronous-ignoring-data-server)
     (input-on-request-preserving-time-stamps 'on-request)
     (input-on-request-sample-and-hold 'on-request-sample-and-hold)
     (input-when-activated 'input-one-shot-when-activated)
     (input-when-activated-without-interruption
      'input-one-shot-when-activated-without-interruption)
     (t nil)))
  ((get-form (slot-value))
   (case slot-value
     (asynchronous 'asynchronous-input)
     (asynchronous-ignoring-data-server
      'asynchronous-input-ignoring-the-data-server)
     (on-request
      'input-on-request-preserving-time-stamps)
     (on-request-sample-and-hold
      'input-on-request-sample-and-hold)
     (input-one-shot-when-activated 'input-when-activated)
     (input-one-shot-when-activated-without-interruption
      'input-when-activated-without-interruption)
     (t nil))))




;;;many callers of most-refined-foundation-class-of-direct-superiors are
;;;confused, and in fact they might fail to acquire the correct slot definition
;;;if the foundation-class of the class defining the slot is not equal to itself
;;;(e.g. it's variable in GSI-data-service)
;;;
;;; NOTE: Yes, well it turns out THIS caller of
;;; most-refined-foundation-class-of-direct-superiors was confused as well
;;; until today since it wasn't checking to see if the direct-superiors were
;;; acceptable first as the doc says they should be.  Note also that this
;;; function can return NIL, and all callers are already prepared for that.
;;; -dkuznick, 6/9/04

(defun slot-description-from-superior-class (unaliased-slot-name class-definition)
  (let ((direct-superiors-of-defined-class
	  (direct-superiors-of-defined-class class-definition)))
    ;; It's kind of unfortunate to have to make the following test, as in at
    ;; least two callers of slot-description-from-superior-class {the
    ;; slot-value-compilers for default-overrides-for-object-definitions and
    ;; default-overrides-for-class-definitions} we already know if the
    ;; superiors are ok or not {but they were not using that info to avoid
    ;; calling this}.  But classes tend not to have a huge numebr of direct
    ;; superiors, so this should not be terribly expensive, and it will likely
    ;; avoid bugs in the future. -dkuznick, 6/10/04
    (when (direct-superiors-are-defined-p direct-superiors-of-defined-class)
      (slot-description-from-class
	(most-refined-foundation-class-of-direct-superiors
	  direct-superiors-of-defined-class unaliased-slot-name)
	unaliased-slot-name))))


(defun possibly-aliased-slot-description-from-superior-class (possibly-aliased-slot-name class-definition)
  (let* ((direct-superiors-of-defined-class
	   (direct-superiors-of-defined-class class-definition))
	 (unaliased-slot-name
	  (or (loop for superior in direct-superiors-of-defined-class
		    thereis (get-slot-name-for-alias-if-any possibly-aliased-slot-name superior))
	      possibly-aliased-slot-name))
	 (foundation-class
	   (most-refined-foundation-class-of-direct-superiors
	     direct-superiors-of-defined-class unaliased-slot-name)))
    (slot-description-from-class foundation-class unaliased-slot-name)))

(defun map-system-slot-name-to-alias (slot-name frame)
  (let ((slot-description?
	 (slot-description-from-superior-class slot-name frame)))
    (if slot-description?
	(let ((class (defining-class slot-description?)))
	  (values (alias-slot-name-if-necessary slot-name class) class))
	slot-name)))

(defun map-alias-to-system-slot-name (alias frame)
  (let ((slot-description?
	 (possibly-aliased-slot-description-from-superior-class alias frame)))
    (if slot-description?
	(let ((class (defining-class slot-description?)))
	  (values (unalias-slot-name-if-necessary alias class) class))
	alias)))

;;Stages in the life of an initial-value-of-variable-or-parameter

; Parsing (1)
;   (variables have an ending "?", parameters do not)
;   (the categories with "?" all include the symbol NONE as a parse result)
; logical      truth-value           true, false, or (1 . truth-value)
; quantitative quantity              number, (number . units)
; float        initial-value-float   float, (float . units)
; integer      initial-value-integer integer, (integer . units)
; symbolic     standard-or-class-qualified-symbol symbol
; text         whole-string          whole-string

; sensor       initial-sensor-value? none, truth-value, quantity, symbol, whole-string

; Ambiguous cases: NONE, TRUE, FALSE

; Compiling (2)
; attribute
;   item-or-datum-or-no-item-attribute: NONE -> NIL
;   item-or-datum-attribute
;   datum-attribute -> value, or slot-constant

; Ambiguous cases: NIL, TRUE, FALSE

; Writing (2a)
; attribute  (no need to resolve the ambiguous cases)
; write-attribute

; Exporting (2b)
; attribute
; get-evaluation-value-for-attribute
;    must resolve the ambiguous cases, using the data-type or the category from step (1)
;    => Note that the units get lost at this step!

; Importing (2b, inverse)
; attribute
; NULL -> NONE, copy-evaluation-value-to-phrase
; (followed by the s.v.compiler for attribute)

; Making the slot-init-form (3)
; get-slot-init-form-for-override-value
;    ('INITIAL-VALUE-OF-VARIABLE-OR-PARAMETER override-value-form override-class? slot-defining-class? definition)
;    must resolve the ambiguous cases
;    the result must be in the same format as the result of the slot value compilers
;    for the category-symbol-given-slot-type of the slot's type
;    (see the comments before get-slot-init-form-for-override-value)

; Making the slot value (4)
; eval-slot-init-form

; Writing the slot value (5a)
; write-slot-value using the category in step (1), and the slot value from step (4)

; Exporting the slot-value (5b)
; Call the c.e.i. getter using the category in step (1), and the slot value from step (4)

(defun get-grammar-category-for-default-override
    (unaliased-slot-name class-or-class-definition readp)
  (let* ((slot-description
	  (if (symbolp class-or-class-definition)
	      (get-slot-description-from-class class-or-class-definition unaliased-slot-name)
	      (slot-description-from-superior-class unaliased-slot-name class-or-class-definition)))
	 (slot-type?
	   (and slot-description
		(feature-assq 'type (slot-features slot-description))))
	 (default-category? (category-symbol-given-slot-type slot-type?))
	 (category?
	   (case unaliased-slot-name
	     (stubs-for-class
	      'connections?)
	     (attribute-displays-for-class
	      'attribute-displays-spec?)
	     (cross-section-pattern-for-class
	      'cross-section-pattern)
	     (cell-annotations
	      'table-dimensions)
	     (stub-length-for-class
	      'stub-length)
	     (junction-block-for-class
	      'junction-class)
	     (default-message-properties-for-class
		 'message-properties)
	     (default-text-box-colors-for-class
		 'text-cell-colors)
	     (initial-value-of-variable-or-parameter
	      'attribute)
	     (condition-for-using-user-menu-choice?
	      'user-menu-choice-expression-initialization)
	     (t
	      default-category?))))
    (when (and category?
	       (if readp
		   (slot-value-to-evaluation-value-function category?)
		   (evaluation-value-to-category-function category?)))
      category?)))

(defun make-acceptable-classes-phrase-for-default-override
    (aliased-slot-name defining-class grammar-category?)
  (case aliased-slot-name
    (show-simulated-values
     (phrase-list
       (phrase-list 'readout-table 'dial 'meter 'graph)
       (phrase-list 'digital-clock)))
    ((display-update-interval display-wait-interval display-update-priority)
     (phrase-list (phrase-list 'readout-table 'dial 'meter 'graph) ()))
    (display-format
     (phrase-list (phrase-list 'readout-table) (phrase-list 'digital-clock)))
    ((class-of-procedure-invocation default-procedure-priority
      uninterrupted-procedure-execution-limit)
     (phrase-list (phrase-list 'procedure) (phrase-list 'method-declaration)))
    (tracing-and-breakpoints
     (phrase-list
       (phrase-list
	 'procedure 'variable-or-parameter 'generic-simulation-formula 'rule
	 'simulation-subtable 'dial 'meter 'readout-table)
       (phrase-list 'method-declaration 'digital-clock)))
    ((stubs attribute-displays attribute-displays-for-class)
     (phrase-list
       (phrase-list
	 'object 'image-definition 'relation 'frame-style-definition
	 'user-menu-choice 'tabular-function 'procedure 'dial 'meter
	 'procedure-invocation 'model-definition 'external-simulation-definition
	 'action-button 'check-box 'radio-button 'slider 'network-wire)
       ()))
    (t
     (phrase-list (phrase-list (case grammar-category?
				 (variable-frame-flags 'variable)
				 (parameter-frame-flags 'parameter)
				 (t defining-class)))
		  ()))))

(defun get-initial-evaluation-value-for-default-override-1
    (initialization definition grammar-category?)
  (unless grammar-category?
    #+development
    (cerror "Continue"
	    "no exported grammar category for getter, for frame ~S"
	    definition)
    (return-from get-initial-evaluation-value-for-default-override-1 nil))
  (call-category-getter grammar-category? initialization definition nil))

(defun get-initial-evaluation-value-for-default-override
    (unaliased-slot-name defining-class definition initialization)
  (when (eq unaliased-slot-name 'simulation-details)
    (return-from get-initial-evaluation-value-for-default-override
      (third initialization)))
  ;; The getter requires a frame for
  ;;   uuid (item)
  ;;   g2-array-initial-values (g2-array value-array)
  ;;           (but it is only used to bind *current-computation-frame*)
  ;;   {...} (trend-chart)
  ;;           (but it is only used to pass to other slot-value-writers)
  ;;   initial-value-of-variable-or-parameter
  ;;           (used, but not required)
  (when (and (null definition)
	     (eq unaliased-slot-name 'uuid))
    (return-from get-initial-evaluation-value-for-default-override nil))
  (get-initial-evaluation-value-for-default-override-1
   initialization
   definition
   (get-grammar-category-for-default-override
    unaliased-slot-name defining-class t)))

(define-category-evaluator-interface (default-overrides-for-class-definitions
					 :access read-write)
    (or (no-item)
	(sequence (or (structure
			override-on-user-defined-slot-spec
			((user-attribute-name symbol)
			 (initialization
			   (structure
			     initialization-on-user-defined-slot-spec
			     ((initial-value datum)
			      (initial-item-class symbol)
			      (initial-type symbol)))))
			(and user-attribute-name))
		      (structure
			override-on-system-defined-slot-spec
			((system-attribute-designation symbol)
			 (initialization
			   ;; The as yet unwritten category-evaluation interfaces are:
			   ;; initial-sensor-value? (class: sensor)
			   ;; user-menu-choice-expression (class: user-menu-choice)
			   ;; keep-tabular-function-sorted?
			   ;;   (class: tabular-function-of-1-arg)
			   ;; integration-algorithm-specification (class: model-definition)
			   ;; procedure-name? (class: model-definition)
			   ;; simulation-control-specification (class: model-definition)
			   ;; gfi-interface-object (class: gfi-data-service)
			   ;; gfi-file-pathname (class: gfi-input-interface)
			   ;; constant-variable-designation? (class: non-action-button)
			   (or (named chart-style)
			       ;; (named data-series-descriptions)
			       ;; (named chart-annotations)
			       (named table-dimensions)
			       (named cell-format-or-none)
			       (named computation-style-or-none)
			       (named user-instantiable-kb-class?)
			       (named oneness-type)
			       (named relation-yes-or-no?)
			       (named frame-description)
			       (named focal-classes)
			       (named list-of-item-and-datum-constants?)
			       (named simulation-time-increment?)
			       (named focal-objects)
			       (named categories)
			       (named type-in-box-format?)
			       (named when-to-show-value)
			       (named gsi-variable-grouping-specification)
			       (named attributes-which-identify-a-network-item-reference)
			       (named gfi-output-file-update-frequency)
			       (named gfi-time-stamp-format)
			       (named gfi-file-format)
			       (named gfi-input-variables-update-mode)
			       (named relation-name?)
			       (named list-of-datum-constants)
			       (named constant-designation-list?)
			       (named quantity-list)
			       (named integer-list)
			       (named float-list)
			       (named symbol-list)
			       (named whole-string-list)
			       (named truth-value-list)
			       #+graphs-are-good
			       (named horizontal-gridline-interval?)
			       #+graphs-are-good
			       (named extra-grid-line-specs)
			       #+graphs-are-good
			       (named graph-background-colors)
			       #+graphs-are-good
			       (named horizontal-graph-ruling-parameter?)
			       #+graphs-are-good
			       (named vertical-graph-ruling-parameter?)
			       (named display-interval)
			       (named dial-ruling-parameter)
			       (named meter-ruling-parameter)
			       (named format?)
			       (named execution-interval?-or-default)
			       (named priority)
			       (named class-of-procedure-invocation?)
			       (named tracing-and-breakpoints) 
			       (named text-cell-colors) 
			       (named message-properties)
			       (named frame-style-name?)
			       (named module-name?)
			       (named non-negative-integer) 
			       (named extant-color-or-metacolor)
			       (named positive-integer?)
			       (named connections?) 
			       (named attribute-displays-spec?)
			       (named attribute)
			       (named g2-array-length)
			       (named g2-meter-name)
			       (named truth-value?)
			       (named quantity?)
			       (named initial-value-float?)
			       (named initial-value-long?)
			       (named initial-value-integer?)
			       (named standard-or-class-qualified-symbol?)
			       (named whole-string?)
			       (named positive-quantity-interval?)
			       (named variable-frame-flags)
			       (named parameter-frame-flags)
			       (named validity-interval)
			       (named cross-section-pattern)
			       (named stub-length)
			       (named junction-class)
			       (named yes-or-no)
			       (named number?)
			       (named gfi-yes-or-no?)
			       (named data-type)
			       (named quantitative-data-type)
			       (named data-server-map)
			       (named history-specification)
			       (named symbol)
			       (named class)
			       (named new-class))))
			(and system-attribute-designation)))))
  ((set-form (evaluation-value frame))
   (cond ((and evaluation-value
	       (<f 0 (evaluation-sequence-length evaluation-value)))
	  ;; System slot overrides depend on inheritance information.  The
	  ;; definition must have a set of defined direct superior classes.
	  (with-safe-category-setter-calling
	      (block block-default-overrides-for-class-definitions-setter
		
		(let* ((list-of-system-names?
			 (with-evaluation-sequence-to-phrase-list-mapping
			     (evaluation-value override-info)
			   (and (eq (evaluation-structure-slot override-info 'user-attribute-name no-value)
				    no-value)
				(with-structure
				    (override-info override-on-system-defined-slot-spec)
				  system-attribute-designation))))
		       (system-slot-aliased-names?
			 (loop for name? in list-of-system-names?
			       when name? collect name? using phrase-cons)))
		  (when system-slot-aliased-names?
		    (let ((direct-superiors? (direct-superiors-of-defined-class frame)))
		      (when (or (null direct-superiors?)
				(not (direct-superiors-are-defined-p direct-superiors?)))
			(return-from block-default-overrides-for-class-definitions-setter 
			  (values
			    bad-phrase
			    (tformat-text-string
			      "The class-definition must first have a defined set of direct ~
                           superior classes."))))
		      (loop for aliased-name in system-slot-aliased-names?
			    for slot-description?
				= (possibly-aliased-slot-description-from-superior-class
				   aliased-name frame)
			    do
			(unless slot-description?
			  (return-from block-default-overrides-for-class-definitions-setter
			    (values
			      bad-phrase
			      (tformat-text-string
				"The inheritance for this class does not include an attribute named ~a."
				aliased-name))))))))
		(phrase-cons
		  '\;
		  (with-evaluation-sequence-to-phrase-list-mapping
		      (evaluation-value override-info)
		    (cond ((not (eq (evaluation-structure-slot override-info 'user-attribute-name no-value)
				    no-value))
			   (with-structure (override-info override-on-user-defined-slot-spec)
			     (let ((attribute-name
				     (if (class-qualified-symbol-p
					   user-attribute-name) 
					 (multiple-value-bind (class-symbol name-symbol)
					     (decompose-class-qualified-symbol
					       user-attribute-name)
					   (phrase-list
					     'class-qualified-name class-symbol name-symbol))
					 user-attribute-name))
				   (value-type-phrase
				     (with-structure
					 (initialization
					   initialization-on-user-defined-slot-spec)
				       (let ((fixed-initial-value
					       (fix-attribute-initial-value-or-return-from
						 block-default-overrides-for-class-definitions-setter
						 initial-value initial-item-class)))
					 (fix-override-initial-value fixed-initial-value)))))
			       
			       (phrase-list attribute-name value-type-phrase 'user-defined))))
			  (t
			   (with-structure (override-info override-on-system-defined-slot-spec)
			     (multiple-value-bind (unaliased-slot-name defining-class)
				 (map-alias-to-system-slot-name 
				  system-attribute-designation
				  frame)
			       (let* ((grammar-category?
				       (get-grammar-category-for-default-override
					unaliased-slot-name defining-class nil))
				      (initialization-phrase
				       (cond ((eq unaliased-slot-name 'simulation-details)
					      (slot-value-list
					       ':funcall
					       'make-simulation-subtable-with-specific-class-and-install
					       initialization))
					     ;; overridable iff it's an item-list or item-array
					     ((case unaliased-slot-name
						(g2-array-element-type
						 (definition-subclassp frame 'item-array))
						(list-type
						 (definition-subclassp frame 'item-list)))
					      (case initialization
						(value 'datum)
						(item-or-value 'item-or-datum)
						(quantity 'number)
						(t initialization)))
					     (grammar-category?
					      (call-category-setter-safely
					       grammar-category? initialization nil nil nil))
					     (t
					      (return-from
					       block-default-overrides-for-class-definitions-setter
						(values bad-phrase
							(tformat-text-string
							 "the attribute, ~NQ, is not concludable"
							 system-attribute-designation nil))))))
				      (acceptable-classes-phrase
				       (make-acceptable-classes-phrase-for-default-override
					system-attribute-designation
					defining-class
					grammar-category?)))
				 (phrase-list
				  unaliased-slot-name initialization-phrase
				  acceptable-classes-phrase)))))))))))
	 (t 'none)))
  
  ((get-form (slot-value frame))
   (allocate-evaluation-sequence
    (loop for default-override in slot-value
	  for user-defined-p = (override-is-for-user-defined-slot-p default-override)
	  for slot-name = (first default-override)
	  for specified-class-of-override? = (third default-override)
	  for override-alias
	      = (unless user-defined-p
		  (if specified-class-of-override?
		      (alias-slot-name-if-necessary slot-name specified-class-of-override?)
		      (map-system-slot-name-to-alias slot-name frame)))
	  for slot-description?
	      = (unless user-defined-p
		  (possibly-aliased-slot-description-from-superior-class override-alias frame))
	  for unaliased-slot-name
	      = (if user-defined-p
		    slot-name
		    (if specified-class-of-override?
			(unalias-slot-name-if-necessary override-alias specified-class-of-override?)
			(map-alias-to-system-slot-name override-alias frame)))
	  when (or user-defined-p
		   ;; used to be (not (eq override-alias 'data-type))
		   ;; but it is overridable for sensors, and for numeric v-or-p types
		   (and slot-description?
			(feature-assq 'user-overridable (slot-features slot-description?))))
	    collect
	    (if user-defined-p
		(with-new-structure (override-on-user-defined-slot-spec)
		  (let* ((source-attribute-name (car default-override))
			 (source-value-type-phrase (cadr default-override))
			 (source-initial-value
			  (and source-value-type-phrase
			       (if (or (evaluation-sequence-p source-value-type-phrase)
				       (evaluation-structure-p source-value-type-phrase))
				   source-value-type-phrase
				   (car-of-cons source-value-type-phrase))))
			 (source-initial-item-class
			  (when (and (consp source-initial-value)
				     (eq (car-of-cons source-initial-value) ':funcall))
			    (third source-initial-value)))
			 (source-initial-type
			  (when source-value-type-phrase
			    (cond ((or (evaluation-sequence-p source-value-type-phrase)
				       (evaluation-structure-p source-value-type-phrase))
				   (cdr source-value-type-phrase))
				  (source-initial-item-class source-initial-item-class)
				  (t (cadr-of-cons source-value-type-phrase))))))
		    (setf user-attribute-name
			  (if (class-qualified-name-denotation-p source-attribute-name)
			      (convert-class-qualified-list-to-keyword-symbol
			       source-attribute-name)
			      source-attribute-name))
		    (setf initialization
			  (with-new-structure (initialization-on-user-defined-slot-spec)
			    (setf-non-nil initial-value
					  (make-initial-value-for-user-given-type
					   source-initial-value source-initial-type))
			    (setf-non-nil initial-item-class
					  (make-initial-item-class-for-user source-initial-value))))))
		(with-new-structure (override-on-system-defined-slot-spec)
		  (setf system-attribute-designation
			override-alias)
		  (let ((evaluation-value?
			 (get-initial-evaluation-value-for-default-override
			  unaliased-slot-name
			  specified-class-of-override?
			  frame
			  (cadr default-override))))
		    (when evaluation-value?
		      (setf initialization evaluation-value?)))))
	      using eval-cons))))



(define-category-evaluator-interface (default-overrides-for-object-definitions
					 :access read-write)
    (or (no-item)
	(sequence (or (structure
			override-on-user-defined-slot-spec
			((user-attribute-name symbol)
			 (initialization
			   (structure
			     initialization-on-user-defined-slot-spec
			     ((initial-value datum)
			      (initial-item-class symbol)
			      (initial-type symbol)))))
			(and user-attribute-name))
		      (structure
			override-on-system-defined-slot-spec
			((system-attribute-designation symbol)
			 (initialization
			   ;; initial-sensor-value? 
			   (or (named list-of-item-and-datum-constants?)
			       (named list-of-datum-constants)
			       (named constant-designation-list?)
			       (named quantity-list)
			       (named integer-list)
			       (named float-list) 
			       (named symbol-list)
			       (named whole-string-list)
			       (named truth-value-list)
			       (named g2-array-length)
			       (named truth-value)
			       (named quantity?)
			       (named initial-value-float?)
			       (named initial-value-long?)
			       (named initial-value-integer?)
			       (named standard-or-class-qualified-symbol?)
			       (named whole-string?)
			       (named positive-quantity-interval?)
			       (named variable-frame-flags)
			       (named parameter-frame-flags)
			       (named validity-interval)
			       (named yes-or-no)
			       (named data-type)
			       (named data-server-map)
			       (named history-specification))))
			(and system-attribute-designation)))))
  ((set-form (evaluation-value frame))
   (cond ((and evaluation-value
	       (<f 0 (evaluation-sequence-length evaluation-value)))
	  ;; System slot overrides depend on inheritance information.  The
	  ;; definition must have a set of defined direct superior classes.
	  (with-safe-category-setter-calling
	      (block block-default-overrides-for-object-definitions-setter
		(let* ((list-of-system-names?
			 (with-evaluation-sequence-to-phrase-list-mapping
			     (evaluation-value override-info)
			   (and (eq (evaluation-structure-slot override-info 'user-attribute-name no-value)
				    no-value)
				(with-structure
				    (override-info override-on-system-defined-slot-spec)
				  system-attribute-designation))))
		       (system-slot-aliased-names?
			 (loop for name? in list-of-system-names?
			       when name? collect name? using phrase-cons)))
		  (when system-slot-aliased-names?
		    (let ((direct-superiors? (direct-superiors-of-defined-class frame)))
		      (when (or (null direct-superiors?)
				(not (direct-superiors-are-defined-p direct-superiors?)))
			(return-from block-default-overrides-for-object-definitions-setter 
			  (values
			    bad-phrase
			    (tformat-text-string
			      "The class-definition must first have a defined set of direct ~
                           superior classes."))))
		      (loop for aliased-name in system-slot-aliased-names?
			    for slot-description?
				= (possibly-aliased-slot-description-from-superior-class
				   aliased-name frame)
			    do
			(when (null slot-description?)
			  (return-from block-default-overrides-for-object-definitions-setter
			    (values
			      bad-phrase
			      (tformat-text-string
				"The inheritance for this class does not include an attribute named ~a."
				aliased-name))))))))
		(phrase-cons
		  '\;
		  (with-evaluation-sequence-to-phrase-list-mapping
		      (evaluation-value override-info)
		    (cond ((not (eq (evaluation-structure-slot override-info 'user-attribute-name no-value)
				    no-value))
			   (with-structure (override-info override-on-user-defined-slot-spec)
			     (let ((attribute-name
				     (if (class-qualified-symbol-p user-attribute-name) 
					 (multiple-value-bind (class-symbol name-symbol)
					     (decompose-class-qualified-symbol
					       user-attribute-name)
					   (phrase-list
					     'class-qualified-name class-symbol name-symbol))
					 user-attribute-name))
				   (value-type-phrase
				     (with-structure
					 (initialization
					   initialization-on-user-defined-slot-spec)
				       (let ((fixed-initial-value
					       (fix-attribute-initial-value-or-return-from
						 block-default-overrides-for-object-definitions-setter
						 initial-value initial-item-class)))
					 (fix-override-initial-value fixed-initial-value)))))
					  
			       (phrase-list attribute-name value-type-phrase 'user-defined))))
			  (t
			   (with-structure (override-info override-on-system-defined-slot-spec)
			     (multiple-value-bind (unaliased-slot-name defining-class)
				 (map-alias-to-system-slot-name 
				  system-attribute-designation
				  frame)
			       (let* ((slot-name-to-use
				       ;; For backward compatibility, the internal-representation
				       ;; of the default-overrides slot for object-definitions
				       ;; must be 'initial-value.  (ghw 11/24/98)
				       (if (eq unaliased-slot-name 'initial-value-of-variable-or-parameter)
					   'initial-value
					   unaliased-slot-name))
				      (grammar-category?
				       (get-grammar-category-for-default-override
					unaliased-slot-name defining-class nil))
				      (initialization-phrase
				       (cond ((eq slot-name-to-use 'simulation-details)
					      (slot-value-list
					       ':funcall
					       'make-simulation-subtable-and-install))
					     ;; overridable iff it's an item-list or item-array
					     ((case slot-name-to-use
						(g2-array-element-type
						 (definition-subclassp frame 'item-array))
						(list-type
						 (definition-subclassp frame 'item-list)))
					      (case initialization
						(value 'datum)
						(item-or-value 'item-or-datum)
						(quantity 'number)
						(t initialization)))
					     (grammar-category?
					      (call-category-setter-safely grammar-category?
									   initialization nil nil nil))
					     (t
					      (return-from
					       block-default-overrides-for-object-definitions-setter
						(values
						 bad-phrase
						 (tformat-text-string
						  "the attribute, ~NQ, is not concludable"
						  system-attribute-designation nil)))))))
				 (phrase-list slot-name-to-use initialization-phrase
					      (case grammar-category?
						(variable-frame-flags 'variable)
						(parameter-frame-flags 'parameter)
						(t defining-class)))))))))))))
	 (t 'none)))
  
  ((get-form (slot-value frame))
   (allocate-evaluation-sequence
    (loop for default-override in slot-value
	  for user-defined-p = (override-is-for-user-defined-slot-p default-override)
	  for slot-name = (first default-override)
	  for specified-class-of-override? = (third default-override)
	  for override-alias
	      = (unless user-defined-p
		  (if specified-class-of-override?
		      (alias-slot-name-if-necessary slot-name specified-class-of-override?)
		      (map-system-slot-name-to-alias slot-name frame)))
	  for slot-description?
	      = (unless user-defined-p
		  (possibly-aliased-slot-description-from-superior-class override-alias frame))
	  for unaliased-slot-name
	      = (if user-defined-p
		    slot-name
		    (if specified-class-of-override?
			(unalias-slot-name-if-necessary override-alias specified-class-of-override?)
			(map-alias-to-system-slot-name override-alias frame)))
	  when (or user-defined-p
		   ;; used to be (not (eq override-alias 'data-type))
		   ;; but it is overridable for sensors, and for numeric v-or-p types
		   (and slot-description?
			(feature-assq 'user-overridable (slot-features slot-description?))))
	    collect
	    (if user-defined-p
		(with-new-structure (override-on-user-defined-slot-spec)
		  (let* ((source-attribute-name (car default-override))
			 (source-value-type-phrase (cadr default-override))
			 (source-initial-value
			  (and source-value-type-phrase
			       (if (or (evaluation-sequence-p source-value-type-phrase)
				       (evaluation-structure-p source-value-type-phrase))
				   source-value-type-phrase
				   (car-of-cons source-value-type-phrase))))
			 (source-initial-item-class
			  (when (and (consp source-initial-value)
				     (eq (car-of-cons source-initial-value) ':funcall))
			    (third source-initial-value)))
			 (source-initial-type
			  (when source-value-type-phrase
			    (cond ((or (evaluation-sequence-p source-value-type-phrase)
				       (evaluation-structure-p source-value-type-phrase))
				   (cdr source-value-type-phrase))
				  (source-initial-item-class source-initial-item-class)
				  (t (cadr-of-cons source-value-type-phrase))))))
		    (setf user-attribute-name
			  (if (class-qualified-name-denotation-p source-attribute-name)
			      (convert-class-qualified-list-to-keyword-symbol
			       source-attribute-name)
			      source-attribute-name))
		    (setf initialization
			  (with-new-structure (initialization-on-user-defined-slot-spec)
			    (setf-non-nil initial-value
					  (make-initial-value-for-user-given-type
					   source-initial-value source-initial-type))
			    (setf-non-nil initial-item-class
					  (make-initial-item-class-for-user source-initial-value))))))
		(with-new-structure (override-on-system-defined-slot-spec)
		  (setf system-attribute-designation override-alias)
		  (let ((evaluation-value?
			 (if (eq slot-name 'simulation-details)
			     'supply-simulation-subtable
			     (get-initial-evaluation-value-for-default-override
			      unaliased-slot-name
			      (or specified-class-of-override?
				  (defining-class slot-description?))
			      frame
			      (cadr default-override)))))
		    (when evaluation-value?
		      (setf initialization evaluation-value?)))))
	      using eval-cons))))



(define-category-evaluator-interface (default-overrides-for-message-definitions
					 :access read-write)
    (or (no-item)
	(sequence (structure
		    override-on-user-defined-slot-spec
		    ((user-attribute-name symbol)
		     (initialization
		       (structure
			 initialization-on-user-defined-slot-spec
			 ((initial-value datum)
			  (initial-item-class symbol)
			  (initial-type symbol)))))
		    (and user-attribute-name))))
  ((set-form (evaluation-value))
   (block setter
     (if (and evaluation-value
	      (<f 0 (evaluation-sequence-length evaluation-value)))
	 (phrase-cons
	   '\;
	   (with-evaluation-sequence-to-phrase-list-mapping
	       (evaluation-value override-info)
	     (with-structure (override-info override-on-user-defined-slot-spec)
	       (let ((attribute-name
		       (if (class-qualified-symbol-p
			     user-attribute-name) 
			   (multiple-value-bind (class-symbol name-symbol)
			       (decompose-class-qualified-symbol
				 user-attribute-name)
			     (phrase-list
			       'class-qualified-name class-symbol name-symbol))
			   user-attribute-name))
		     (value-type-phrase
		       (with-structure
			   (initialization
			     initialization-on-user-defined-slot-spec)
			 (let ((fixed-initial-value
				 (fix-attribute-initial-value-or-return-from
				   setter initial-value initial-item-class)))
			   (fix-override-initial-value fixed-initial-value)))))
		 
		 (phrase-list attribute-name value-type-phrase 'user-defined)))))
	 'none)))
  ((get-form (slot-value))
   (with-list-to-evaluation-sequence-mapping
       (slot-value default-override)
     (with-new-structure (override-on-user-defined-slot-spec)
       (let* ((source-attribute-name (car default-override))
	      (source-value-type-phrase (cadr default-override))
	      (source-initial-value
	       (and source-value-type-phrase
		    (if (or (evaluation-sequence-p source-value-type-phrase)
			    (evaluation-structure-p source-value-type-phrase))
			source-value-type-phrase
			(car-of-cons source-value-type-phrase))))
	      (source-initial-item-class
	       (when (and (consp source-initial-value)
			  (eq (car-of-cons source-initial-value) ':funcall))
		 (third source-initial-value)))
	      (source-initial-type
	       (when source-value-type-phrase
		 (cond ((or (evaluation-sequence-p source-value-type-phrase)
			    (evaluation-structure-p source-value-type-phrase))
			(cdr source-value-type-phrase))
		       (source-initial-item-class source-initial-item-class)
		       (t (cadr-of-cons source-value-type-phrase))))))
	 (setf user-attribute-name
	       (if (class-qualified-name-denotation-p source-attribute-name)
		   (convert-class-qualified-list-to-keyword-symbol
		    source-attribute-name)
		   source-attribute-name))
	 (setf initialization
	       (with-new-structure (initialization-on-user-defined-slot-spec)
		 (setf-non-nil initial-value
			       (make-initial-value-for-user-given-type
				source-initial-value source-initial-type))
		 (setf-non-nil initial-item-class
			       (make-initial-item-class-for-user source-initial-value)))))))))

(define-category-evaluator-interface (default-overrides-for-connection-definitions
					   :access read-write)
    (or (no-item)
	(sequence (structure
		    override-on-user-defined-slot-spec
		    ((user-attribute-name symbol)
		     (initialization
		       (structure
			 initialization-on-user-defined-slot-spec
			 ((initial-value datum)
			  (initial-item-class symbol)
			  (initial-type symbol)))))
		    (and user-attribute-name))))
  ((set-form (evaluation-value))
   (block setter
     (if (and evaluation-value
	      (<f 0 (evaluation-sequence-length evaluation-value)))
	 (phrase-cons
	   '\;
	   (with-evaluation-sequence-to-phrase-list-mapping
	       (evaluation-value override-info)
	     (with-structure (override-info override-on-user-defined-slot-spec)
	       (let ((attribute-name
		       (if (class-qualified-symbol-p
			     user-attribute-name) 
			   (multiple-value-bind (class-symbol name-symbol)
			       (decompose-class-qualified-symbol
				 user-attribute-name)
			     (phrase-list
			       'class-qualified-name class-symbol name-symbol))
			   user-attribute-name))
		     (value-type-phrase
		       (with-structure
			   (initialization
			     initialization-on-user-defined-slot-spec)
			 (let ((fixed-initial-value
				 (fix-attribute-initial-value-or-return-from
				   setter initial-value initial-item-class)))
			   (fix-override-initial-value fixed-initial-value)))))
		 
		 (phrase-list attribute-name value-type-phrase 'user-defined)))))
	 'none)))
  ((get-form (slot-value))
   (with-list-to-evaluation-sequence-mapping
       (slot-value default-override)
     (with-new-structure (override-on-user-defined-slot-spec)
       (let* ((source-attribute-name (car default-override))
	      (source-value-type-phrase (cadr default-override))
	      (source-initial-value
	       (and source-value-type-phrase
		    (if (or (evaluation-sequence-p source-value-type-phrase)
			    (evaluation-structure-p source-value-type-phrase))
			source-value-type-phrase
			(car-of-cons source-value-type-phrase))))
	      (source-initial-item-class
	       (when (and (consp source-initial-value)
			  (eq (car-of-cons source-initial-value) ':funcall))
		 (third source-initial-value)))
	      (source-initial-type
	       (when source-value-type-phrase
		 (cond ((or (evaluation-sequence-p source-value-type-phrase)
			    (evaluation-structure-p source-value-type-phrase))
			(cdr source-value-type-phrase))
		       (source-initial-item-class source-initial-item-class)
		       (t (cadr-of-cons source-value-type-phrase))))))
	 (setf user-attribute-name
	       (if (class-qualified-name-denotation-p source-attribute-name)
		   (convert-class-qualified-list-to-keyword-symbol
		    source-attribute-name)
		   source-attribute-name))
	 (setf initialization
	       (with-new-structure (initialization-on-user-defined-slot-spec)
		 (setf-non-nil initial-value
			       (make-initial-value-for-user-given-type
				source-initial-value source-initial-type))
		 (setf-non-nil initial-item-class
			       (make-initial-item-class-for-user source-initial-value)))))))))








;;;; Trend Chart Category Evaluator Interfaces




(define-category-evaluator-interface (plot-update-interval-spec
				       :access read-write)
    (structure plot-update-spec
	       ((update-interval (named display-interval))
		(granularity number))
	       (and update-interval))
  ((set-form (evaluation-value))
   (block block-3.1415926
     (with-temporary-gensym-float-creation plot-update-interval-spec
       (cond ((evaluation-structure-slot evaluation-value 'granularity)
	      (phrase-list
		'interval-with-granularity
		(multiple-value-bind (value-or-bad-phrase error-string?)
		    (call-category-setter
		      'display-interval
		      (evaluation-structure-slot evaluation-value 'update-interval)
		      nil nil nil)
		  (when (eq value-or-bad-phrase bad-phrase)
		    (return-from block-3.1415926
		      (values bad-phrase error-string?)))
		  value-or-bad-phrase)
		(evaluation-quantity-to-phrase-quantity
		  (evaluation-structure-slot evaluation-value 'granularity))))
	     (t
	      (call-category-setter
		'display-interval
		(evaluation-structure-slot evaluation-value 'update-interval)
		nil nil nil))))))
  ((get-form (slot-value))
   (with-temporary-gensym-float-creation plot-update-interval-spec
     (cond
       ((and (consp slot-value)
	     (eq (car-of-cons slot-value) 'interval-with-granularity))
	(allocate-evaluation-structure-inline
	  'update-interval (call-category-getter
			     'display-interval (cadr slot-value) nil nil)
	  'granularity (make-evaluation-value-based-on-type (caddr slot-value))))
       (t
	(allocate-evaluation-structure-inline
	  'update-interval (call-category-getter
			     'display-interval slot-value nil nil)))))))

(def-slot-component-alias point-visible?
  markers-visible? trend-chart point-format)

(def-slot-component-alias point-color
   marker-color trend-chart point-format)

(def-slot-component-alias point-style
   marker-style trend-chart point-format)

(def-slot-component-alias point-frequency
   marker-frequency trend-chart point-format)

(defun make-parse-result-for-multiple-compound-slot (evaluation-value frame compound-type)
  (let ((header nil)
	(default-seen-p nil)
	(length (evaluation-sequence-length evaluation-value))
	(triples '()))
    (multiple-value-bind (header-or-bad-phrase error-string?)
	(get-multiple-compound-slot-parse-result-header evaluation-value)
      (cond ((eq header-or-bad-phrase bad-phrase)
	     (return-from make-parse-result-for-multiple-compound-slot
	       (values bad-phrase error-string?)))
	    (t
	     (setf header header-or-bad-phrase))))
    (loop with id-list = '()
	  with index = 0
	  for struct being each evaluation-sequence-element of evaluation-value
	  as id = (get-component-group-id-from-structure struct)
	  do
      (cond ((and id (memq id id-list))
	     (return-from make-parse-result-for-multiple-compound-slot
	       (values bad-phrase (tformat-text-string "multiple use of names"))))
	    (t
	     (phrase-push id id-list)))
      (cond
	((eq id 'default)
	  (setf default-seen-p t))
	(t
	  (incff index)))
      (multiple-value-bind (new-triples-or-bad-phrase error-string?)
	  (add-triples-for-compound-slot-structure-parse-result
	    frame struct (compound-type-descriptor compound-type)
	    (or id index) t)
	(cond
	  ((eq new-triples-or-bad-phrase bad-phrase)
	   (return-from make-parse-result-for-multiple-compound-slot
	     (values bad-phrase error-string?)))
	  (t
	   (setf triples
		 (nconc triples new-triples-or-bad-phrase))))))
    (phrase-list (phrase-list
		   (if default-seen-p (1-f length) length)
		   header)
		 (phrase-cons '\; triples))))

(defun make-parse-result-for-single-compound-slot (evaluation-value frame compound-type)
  (multiple-value-bind (triples-or-bad-phrase error-string?)
      (add-triples-for-compound-slot-structure-parse-result
	frame evaluation-value (compound-type-descriptor compound-type) 'single
	nil)
    (cond
      ((eq triples-or-bad-phrase bad-phrase)
       (values bad-phrase error-string?))
      (t
       (phrase-list nil
		    (phrase-cons '\; triples-or-bad-phrase))))))
 
(define-category-evaluator-interface (trend-chart-point-formats-grammar-spec
				       :access read-write)
    (sequence (structure point-format
			 ((names (or (no-item) symbol (sequence symbol 1)))
			  (chart-element-uid (or symbol integer))
			  (markers-visible? (named yes-or-no))
			  (marker-color (named color-or-metacolor))
			  (marker-style (named 2d-plot-marker-shape))
			  (marker-frequency (named 2d-plot-marker-frequency))))
	      1)
  ((set-form (evaluation-value frame))
   (let ((x (make-parse-result-for-multiple-compound-slot
	      evaluation-value frame 'point-format)))
     ;; (pprint x)
     x)) 
  ((get-form  (slot-value frame))
   (make-evaluation-sequence-from-multiple-compound-slot
     frame slot-value (compound-type-descriptor 'point-format) nil)))

(define-category-evaluator-interface (trend-chart-connector-formats-grammar-spec
				       :access read-write)
    (sequence (structure connector-format
			 ((names (or (no-item) symbol (sequence symbol 1)))
			  (chart-element-uid (or symbol integer))
			  (connectors-visible? (named yes-or-no))
			  (connector-line-color (named color-or-metacolor))
			  (connector-interpolation (named 2d-line-style))
			  (connector-line-width integer)
			  (connector-shading-target (named 2d-shading-target-spec))))
	      1)
  ((set-form (evaluation-value frame))
   (let ((x (make-parse-result-for-multiple-compound-slot
	      evaluation-value frame 'connector-format)))
     ;; (pprint x)
     x)) 
  ((get-form  (slot-value frame))
   (make-evaluation-sequence-from-multiple-compound-slot
     frame slot-value (compound-type-descriptor 'connector-format) nil)))

(define-category-evaluator-interface (trend-chart-value-axes-grammar-spec
				       :access read-write)
    (sequence (structure value-axis
			 ((names (or (no-item) symbol (sequence symbol 1)))
			  (chart-element-uid (or symbol integer))
			  (value-axis-visible? (named yes-or-no))
			  (value-axis-position (named value-axis-position))
			  (range-mode (named 2d-range-mode))
			  (range-bounds (named 2d-value-axis-bounds-spec))
			  (range-slack-percentage (named range-slack-spec))
			  (labels-visible? (named yes-or-no))
			  (label-color (named 2d-tickmark-label-color))
			  (label-frequency (named 2d-value-axis-tickmark-frequency-spec))
			  (show-labels-as-percent? (named yes-or-no))
			  (significant-digits-for-labels (named significant-digit-spec))
			  (grid-lines-visible? (named yes-or-no))
			  (grid-line-color (named color-or-metacolor))
			  (grid-lines-per-label (named grid-line-ratio)) 
			  (extra-grid-lines (named extra-value-grid-lines)) 
			  (baseline-visible? (named yes-or-no))
			  (baseline-color (named color-or-metacolor))
			  ))
	      1)
  ((set-form (evaluation-value frame))
   (let ((x (make-parse-result-for-multiple-compound-slot
	      evaluation-value frame 'value-axis)))
     ;; (pprint x)
     x))
  ((get-form  (slot-value frame))
   (make-evaluation-sequence-from-multiple-compound-slot
     frame slot-value (compound-type-descriptor 'value-axis) nil)))

(define-category-evaluator-interface (trend-chart-format-grammar-spec
				       :access read-write)
    (structure trend-chart-format
	       ((outer-border-visible? (named yes-or-no))
		(outer-border-color (named color-or-metacolor))
		(outer-background-color (named color-or-metacolor))
		(data-window-border-visible? (named yes-or-no))
		(data-window-border-color (named color-or-metacolor))
		(data-window-background-color (named color-or-metacolor))
		(legend-visible? (named yes-or-no))
		(legend-color (named trend-chart-legend-color-spec)) 
		(legend-position (named trend-chart-legend-position))
		(title-visible? (named yes-or-no))
		(title-color (named color-or-metacolor))
		(title-position (named trend-chart-legend-position))))
  ((set-form (evaluation-value frame))
   ;; must make cases for single and test
   (let ((x (make-parse-result-for-single-compound-slot
	      evaluation-value frame 'trend-chart-format)))
     ;; (pprint x)
     x)) 
  ((get-form (slot-value frame))
   (make-evaluation-structure-from-slot-component
     frame slot-value (compound-type-descriptor 'trend-chart-format) t nil)))

(define-category-evaluator-interface (trend-chart-time-axis-grammar-spec
				       :access read-write)
    (structure trend-chart-format
	       ((data-window-time-span (named 2d-time-span-spec))
		(total-time-span (named 2d-total-time-span-spec))
		(end-time (named 2d-end-time-spec)) 
		(display-update-interval (named display-interval))
		(jump-scroll? (named yes-or-no))
		(jump-scroll-interval (named trend-chart-scroll-interval))
		(absolute-labels-visible? (named yes-or-no))
		(relative-labels-visible? (named yes-or-no))
		(label-frequency (named 2d-time-axis-tickmark-frequency-spec))
		(label-alignment (named time-axis-label-alignment))
		(time-format (named time-axis-label-format-spec))
		(label-color (named color-or-metacolor))
		(grid-lines-visible? (named yes-or-no))
		(grid-line-color (named color-or-metacolor))
		(grid-lines-per-label (named grid-line-ratio)) 
		(baseline-visible? (named yes-or-no))
		(baseline-color (named color-or-metacolor))
		))
  ((set-form (evaluation-value frame))
   ;; must make cases for single and test
   (let ((x (make-parse-result-for-single-compound-slot
	      evaluation-value frame 'time-axis)))
     ;; (pprint x)
     x)) 
  ((get-form (slot-value frame))
   (make-evaluation-structure-from-slot-component
     frame slot-value (compound-type-descriptor 'time-axis) t nil)))


(define-category-evaluator-interface (trend-chart-plots-grammar-spec
				       :access read-write)
    (sequence (structure plot
			 ((names (or (no-item) symbol (sequence symbol 1)))
			  (chart-element-uid (or symbol integer))
			  (use-local-history? (named yes-or-no))
			  (value-axis-name-or-number (named component-reference))
			  (point-format-name-or-number (named component-reference))
			  (connector-format-name-or-number (named component-reference))
			  (update-interval (named plot-update-interval-spec))
			  (wait-interval (named display-interval))
			  (update-priority (named priority))
			  (may-request-data-seeking? (named yes-or-no))
			  (may-request-event-updates? (named yes-or-no)) 
			  (use-simulator? (named yes-or-no))
			  (tracing-and-breakpoints (named tracing-and-breakpoints)) 
			  (include-in-legend? (named yes-or-no))
			  (expression text) ; needs major work
			  ))
	      1)
  ((set-form (evaluation-value frame))
   (let ((x (make-parse-result-for-multiple-compound-slot
	      evaluation-value frame 'plot)))
     ;; (pprint x)
     x))
  ((get-form (slot-value frame))
   (make-evaluation-sequence-from-multiple-compound-slot
     frame slot-value (compound-type-descriptor 'plot) nil)))

(define-category-slot-access trend-chart-plots-grammar-spec
  ((commit-form (slot-value evaluation-value))
   (loop with plot-list = (multiple-compound-slot-value-real-instances slot-value)
	 with the-plot = nil
	 for struct being each evaluation-sequence-element of evaluation-value
	 as id = (get-component-group-id-from-structure struct)
	 do
     (unless (eq id 'default)
       (setf the-plot (pop plot-list))
       (let ((expression-text? (evaluation-structure-slot struct 'expression)))
	 (when expression-text?
	   (let* ((plot-expression
		    (cadr (assq 'plot-expression (cddr the-plot))))
		  (old-text (cdr plot-expression)))
	     (setf (cdr plot-expression)
		   (convert-text-string-to-text
		     (copy-text-string expression-text?)))
	     (reclaim-text old-text))))))
  slot-value)
  )





;;;; Workspace Title Bar Text



;;; This section deals with the external/user interface to the text on a
;;; workspace's title bar.  

;;; Here we define the slot value writer, putter, compiler, and category
;;; evaluator associated with the title-bar-text slot, whose type is
;;; workspace-title-bar-text, on the class workspace.

;;; The syntax (user/external text format) for workspace-title-bar-text is of
;;; this form:
;;;
;;;   DEFAULT
;;;   | simple-option
;;;   | conditional-option [IF ANY, OTHERWISE simple-option]
;;;
;;; where simple-option is one of
;;;
;;;   string | THE CLASS | THE TABLE HEADER
;;;
;;; and where conditional-option is
;;;
;;;   THE NAME
;;;
;;; The symbol DEFAULT is used to indicate that G2 should use its default
;;; setting. This default is currently set at the factory, and is equivalent to
;;; "the name if any, otherwise the class"; at some future point, we may allow
;;; the default setting to be changed by the user.
;;;
;;; The phrase "the class" puts the class of the workspace into the title bar.
;;; The class is printed without hyphens and in title case, i.e., with initial
;;; capitalization and most other characters in lowercase.  (However, note that
;;; G2 has "special" knowledge of how to capitalize "KB"; that's why "KB
;;; Workspace" is not capitalized as "Kb Workspace".)  This is the same way that
;;; the titles of workspace menus are printed.
;;;
;;; The phrase "the table header" puts the table header of the workspace into
;;; the title bar. This is the same text that would appear in the header of a
;;; table for the workspace.
;;;
;;; The phrase "the name" puts the name, if any, of the workspace into the title
;;; bar.  If there is more than one name, the first name is used. If there are
;;; no names, then blank text appears unless an addition option is specified
;;; using the phrase "if any, otherwise <simple-option>".
;;;
;;; When simple-option is just a string, it is always printed literally as is.
;;; Note that no evaluated portions of the text using []'s are possible.



;;; The internal form of title-bar-text as a slot value is of the form
;;;
;;;   one of the following atoms
;;;
;;;     NIL | text-string | NAME | CLASS | TABLE-HEADER
;;;
;;;   or a list (at present, at most two element long) of the form
;;;
;;;     ( NAME
;;;       text-string | CLASS | TABLE-HEADER )
;;;
;;;   that is, a list whose first element is the symbol NAME and whose second
;;;   element is either a text string or one of the symbols CLASS or
;;;   TABLE-HEADER.
;;;
;;; Here, NIL corresponds to the user/external phrase "default"; the rest of the
;;; the atomic cases correspond to the case of a single simple-option or a
;;; single conditional-option; and the non-atomic, list case corresponds to the
;;; case of a conditional-option combined with a simple-option (the "if any,
;;; otherwise ..."  case).
;;;
;;; Design note: this attribute export format was chosen (a) to be somewhat
;;; similar to the name-or-for-frame slot format, and (b) because it could be
;;; expanded easily to accomodate other formats.  For example, we could allow a
;;; list of named formats, some of which might be "conditional" (like "the
;;; name").  Then we'd use the text of the first one that has a value.  We might
;;; also wish to have more complex text construction, e.g., with constant text
;;; combined with computed text, as with G2's formatted text expressions.
;;;
;;; The grammar defined here includes templates and transformations that manage
;;; the transformation from the external form into the internal form described
;;; above.  Therefore, no compiler is even necessary.

;;; Note that the `slot-value-compiler for workspace-title-bar-text' does not
;;; (should not) really need to be defined because it actually has nothing to
;;; do: by the time the transformations in the grammar rules have run, or the
;;; category evaluator setter has run, the parse-result arg to the compiler
;;; would already be in its desired final form.

(def-slot-value-compiler workspace-title-bar-text (parse-result)
  parse-result)

(add-grammar-rules
  '((workspace-title-bar-text 'default nil nil-function)
    (workspace-title-bar-text title-bar-text-option)

    (title-bar-text-option simple-title-bar-text-option)
    (title-bar-text-option conditional-title-bar-text-option)    
    (simple-title-bar-text-option whole-string)
    (simple-title-bar-text-option ('the 'class) class)
    (simple-title-bar-text-option ('the 'table 'header) table-header)
    
    (conditional-title-bar-text-option
     ('the 'name 'if 'any '\, 'otherwise simple-title-bar-text-option)
     (name 7))
    (conditional-title-bar-text-option ('the 'name) name)))



;;; The `slot-value-writer for workspace-title-bar-text' writes the
;;; user/external text format based on value, in the slot-value form
;;; described above.  

(def-slot-value-writer workspace-title-bar-text (value)
  (cond
    ((null value)
     (tformat "default"))
    (t
     (if (atom value)
	 (twrite-title-bar-text-directive-or-string value) ; a text string or symbol
	 (loop for (x . more?) on value ; a 1- or 2-long list
	       do (twrite-title-bar-text-directive-or-string x)
		  (if more? (twrite " if any, otherwise ")))))))


;;; Twrite-title-bar-text-directive-or-string is a subfuction of the writer for
;;; workspace-title-bar-text. It writes either a string or a "directive" symbol
;;; (NAME, CLASS, or TABLE-HEADER) in the user/external text format.

(defun twrite-title-bar-text-directive-or-string (directive-or-string)
  (if (text-string-p directive-or-string)
      (twrite-parsably directive-or-string)
      (twrite-string
	(case directive-or-string
	  (name "the name")
	  (class "the class")
	  (table-header "the table header")))))





;;; The `slot-putter for title-bar-text' sets the value of the title-bar-text
;;; slot workspace. Where necessary, it may call code to refresh the title bar
;;; of the workspace on all image planes where it is displayed. The refresh is
;;; NOT done, avoided, for reasons of efficiency, in any of the following cases:
;;;
;;;   (a) the initializing-p flag is true;
;;;   (b) the workspace is not showing; or
;;;   (c) the new value is the same as the old value

(def-slot-putter title-bar-text (workspace value initializing-p)
  (let ((original-value (title-bar-text workspace)))
    (prog1 (setf (title-bar-text workspace) value)
      (unless (or initializing-p
		  (not (workspace-showing-p workspace t))
		  (equalw value original-value)) ; see note 1
	(refresh-title-bar workspace)))))

;; Note 1: note that equalw must be used to get text strings compared
;; correctly. An equal/equalw test is normally considered too costly, but here
;; it is most convenient and quite moderate in cost because the possible values
;; are either atoms or list of quite small length and depth.





;;; The `category evaluator interface for workspace-title-bar-text' defines the
;;; attribute import/export format for the workspace-title-bar-text
;;; slot/attribute.  The export format is one of the follow forms:
;;;
;;;   (no-item) ; not really an external form; set using "conclude ... does not exist"
;;;   text      ; a text string
;;;   CLASS | TABLE-HEADER | NAME    ; symbols, like "the class", "the table header", "the name"
;;;   sequence(); same as (no-item) / "conclude ... does not exist"
;;;   sequence(text | CLASS | TABLE-HEADER | NAME)  ; same as first element not in a sequence
;;;   sequence(NAME, text | CLASS | TABLE-HEADER)   ; like "the name if any, otherwise ..."

(define-category-evaluator-interface (workspace-title-bar-text :access read-write)
    (or symbol
	text
	(sequence (or symbol text) 0)
	(no-item))
  ((set-form (new-value))
   (cond ((null new-value)		; (no-item) case
	  nil)				; attribute text is default in this case
	 ((evaluation-sequence-p new-value)
	  (let ((length (evaluation-sequence-length new-value)))
	    (cond 
	      ((=f length 1)
	       (let ((x (evaluation-sequence-aref new-value 0)))
		 (if (not (title-bar-directive-or-string-p x))
		     (values-for-bad-title-bar-directive-or-string x)
		     ;; use copy-for-phrase, here and below, to copy text string
		     (copy-for-phrase x))))
	      ((>f length 2)
	       (values
		 bad-phrase
		 (tformat-text-string
		   "workspace-title-bar-text had ~d elements, but it ~
                    cannot have more than two elements"
		   length)))
	      ((>f length 0)
	       (copy-and-check-workspace-title-bar-sequence new-value))
	      (t
	       nil))))			; empty sequence is like (no-item) case
	 (t
	  (if (not (title-bar-directive-or-string-p new-value))
	      (values-for-bad-title-bar-directive-or-string new-value)
	      (copy-for-phrase new-value)))))
  ((get-form (slot-value))
   ;; We use make-evaluation-value-based-on-type here to convert symbols or text
   ;; strings to evaluation symbols or evaluation texts. In practice, this just
   ;; copies the text strings.
   (cond ((consp slot-value)
	  (allocate-evaluation-sequence
	    (loop for spec-element in slot-value
		  collect (make-evaluation-value-based-on-type spec-element)
		    using eval-cons)))
	 (t
	  (if slot-value
	      (make-evaluation-value-based-on-type slot-value))))))





;;; Values-for-bad-title-bar-directive-or-string is a subfunction of the
;;; category evaluation interface for workspace-title-bar-text. It's used for
;;; returning bad-phrase and creating a descriptive problem report text string.

(defun values-for-bad-title-bar-directive-or-string (element)
  (values
    bad-phrase
    (tformat-text-string
      "workspace-title-bar-text contains illegal element ~s"
      element)))





;;; Copy-and-check-workspace-title-bar-sequence is a subfunction of the category
;;; evaluation interface for workspace-title-bar-text.  It is called in the case
;;; where new-value (in the caller) is a sequence. As it is checking for errors,
;;; it does some copying/conversion of the new value into a phrase in the
;;; expected format. If it finds errors, it may abandon its copying and return
;;; bad-phrase as well as a descriptive text string.  Note that abandoning
;;; copying and creation should create no garbage, since it is doing phrase
;;; consing.

(defun copy-and-check-workspace-title-bar-sequence (new-value-as-sequence)
  (loop with length = (evaluation-sequence-length new-value-as-sequence)
	for spec-element
	    being each evaluation-sequence-element of new-value-as-sequence
	collect (copy-for-phrase spec-element)
	  into result using phrase-cons
	finally
	  (return
	    (if (and (>f length 1)
		     (not (eq (first result) 'name)))
		(values
		  bad-phrase
		  (tformat-text-string
		    "workspace-title-bar-text had ~d elements, but it cannot ~
                     have more than one element unless the first is the ~
                     symbol NAME"
		    length))
		(loop for x in result
		      as first-time-p = t then nil
		      when (not (title-bar-directive-or-string-p x))
			return (values-for-bad-title-bar-directive-or-string x)
		      when (and (eq x 'name) (not first-time-p))
			return (values
				 bad-phrase
				 (tformat-text-string
				   "workspace-title-bar-text cannot have ~
                                    the symbol NAME as its second element"))
		      finally
			;; finally, we know the sequence is OK. return it:
			(return result))))))





;;; Title-bar-directive-or-string-p is a subfunction of the category evaluation
;;; interface for workspace-title-bar-text.  It returns true if
;;; directive-or-string is either a text string or one of the symbols NAME,
;;; CLASS, or TABLE-HEADER.

(defun title-bar-directive-or-string-p (directive-or-string)
  (or (text-string-p directive-or-string)
      (member directive-or-string '(name class table-header))))



;;; Related source code:
;;;
;;;  (a) in FRAMES4, the def-class for workspace, which holds the slot
;;;  description for title-bar-text;
;;;
;;;  (b) in FRAMES2, the def-system-variable for
;;;  list-of-user-overridable-system-slots, which has an entry for
;;;  title-bar-text to allow it to be overridden on user-defined subclasses of
;;;  kb-workspace;
;;;
;;;  (c) in GRAMMAR6A, the defparameter for
;;;  system-class-overrides-for-class-definition, which has an entry for
;;;  title-bar-text adding the grammar to allow it to be overridden on
;;;  user-defined subclasses of kb-workspace;
;;;
;;;  (d) in FRAMES5, the def-class for kb-workspace, which holds the overriding
;;;  slot description for title-bar-text that includes the important slot
;;;  feature USER-OVERRIDABLE -- note that this must be defined on the slot
;;;  description of an item subclass: otherwise, the loop in G2-FINAL which
;;;  sets lookup-slot-optimizable-default, will cause overrides to fail
;;;  (*in production only*!); and
;;;
;;;  (e) in DRAW, function project-title-bar-for-frame interprets the
;;;  value of this slot to draw the title bar.


;;;; View Preferences Grammar

;; This file must be recompiled whenever view-preferences change!
(add-grammar-rules
  '#.(loop for (name type grammar parse) in known-view-preferences
	   collect `(view-preference ,grammar ,parse)))

(add-grammar-rules-for-list 'view-preferences 'view-preference '\; nil 'none)

(def-slot-value-compiler view-preferences (parse)
  (unless (eq parse 'none)
    (when (eq (car parse) '\;)
      (pop parse))
    (loop for (p . v) in parse
	  when v
	    unless (getf result p)
	      collect p into result using phrase-cons and
	      collect v into result using phrase-cons
	  finally
	    (return result))))

(defun twrite-boolean-plist (plist)
  (cond ((null plist)
	 (twrite "none"))
	(t
	 (loop for sublist on plist by #'cddr
	       as (p v) = sublist
	       doing
	   (when v
	     (twrite-symbol-name p :first t nil nil)
	     (unless (eq v t)
	       (twrite ": ")
	       (twrite v)))
	   (when (cddr sublist)
	     (twrite "; "))))))

(def-slot-value-writer view-preferences (plist)
  (twrite-boolean-plist plist))

(define-category-evaluator-interface (view-preferences :access read-write)
    (or (no-item)
	(structure view-preferences-spec
		   #.(loop for (name type grammar parse) in known-view-preferences
			   collect `(,name ,type))))
  ((set-form (evaluation-value))
   (when evaluation-value		; evaluation-structure-to-phrase-plist
     (loop for (name . value) being each evaluation-structure-pair of evaluation-value
	   as lisp-value = (cond ((evaluation-truth-value-p value)
				  (evaluation-truth-value-is-true-p value))
				 (t
				  value)) ; TODO: Convert to lisp value.
	   when lisp-value
	     collect (phrase-cons name lisp-value) using phrase-cons)))

  ((get-form (slot-value))
   (allocate-evaluation-structure	; plist-to-evaluation-structure
     (loop for (p v) on slot-value by #'cddr
	   when v
	     collect p using eval-cons and
	     collect (make-evaluation-value-from-lisp-value v) using eval-cons))))


;;;; Menu Parameters


;;; The attribute `automatically-show-developer-menu-bar' determines when G2
;;; will automatically switch the native menu bar on a particular connection to
;;; the built-in developer menu bar. The slot-value is of the form:
;;;    (ON events {modes})
;;; If modes is omitted, then it means any user mode. The default is:
;;;    (ON (PAUSE RESET CONNECT))

(def-grammar-category automatically-show-developer-menu-bar ()
  (('on interesting-ui-events) (on 2))
  (('on interesting-ui-events '\, 'only 'in mode-spec) (on 2 6))
  ('never (on nil)))

(def-grammar-category interesting-ui-event ()
  pause
  reset
  (('initial 'connection) connect))

(def-grammar-list-category interesting-ui-events (interesting-ui-event)
  :separator \, :conjunction or)

(def-slot-value-compiler automatically-show-developer-menu-bar (parse-result)
  (gensym-dstruct-bind ((events modes) (cdr parse-result))
    (nconc (phrase-list 'on)
	   (phrase-list 
	     (loop for event in '(pause reset connect)
		   when (memq event events)
		     collect event using phrase-cons))
	   (when modes
	     (phrase-list (remove-noise-at-head-of-list-phrase modes))))))
	       
(defun-simple twrite-interesting-ui-event (event)
  (case event
    (connect (twrite "initial connection"))
    (t (twrite-symbol event))))

(def-slot-value-writer automatically-show-developer-menu-bar (value)
  (gensym-dstruct-bind ((events modes) (cdr value))
    (cond ((null events)
	   (twrite "never"))
	  (t
	   (twrite "on ")
	   ;; twrite-list doesn't quite do what we want.
	   (cond ((=f (length events) 2)
		  (twrite-interesting-ui-event (first events))
		  (twrite " or ")
		  (twrite-interesting-ui-event (second events)))
		 (t
		  (twrite-list events :element-writer #'twrite-interesting-ui-event
			       :conjoiner ", or ")))
	   (when modes
	     (twrite ", only in ")
	     (write-symbol-list modes nil 'or "nothing")
	     (tformat " mode"))))))

(define-category-evaluator-interface (automatically-show-developer-menu-bar :access read-write)
    (structure event-mode-spec
	       ((events (sequence symbol))
		(modes (sequence symbol))))
  ((set-form (value))
   (let ((events (evaluation-structure-slot value 'events))
	 (modes  (evaluation-structure-slot value 'modes)))
     (nconc (phrase-list 'on)
	    (phrase-list
	      (loop for event being each evaluation-sequence-element of events
		    collect event using phrase-cons))
	    (unless (evaluation-sequence-empty-p modes)
	      (phrase-list
		(loop for mode being each evaluation-sequence-element of modes
		      collect mode using phrase-cons))))))
  ((get-form (value))
   (gensym-dstruct-bind ((events modes) (cdr value))
     (allocate-evaluation-structure
       (nconc
	 (eval-list 'events
		    (allocate-evaluation-sequence (copy-list-using-eval-conses events)))
	 (eval-list 'modes
		    (allocate-evaluation-sequence (copy-list-using-eval-conses modes))))))))

(defun show-developer-menu-bar-p (gensym-window event)
  (let ((value (automatically-show-developer-menu-bar menu-parameters))
	(mode (g2-user-mode-for-this-workstation?
		(workstation-this-is-on gensym-window))))
    (gensym-dstruct-bind ((events modes) (cdr value))
      (and (memq event events)
	   (if modes (memq mode modes) t)))))

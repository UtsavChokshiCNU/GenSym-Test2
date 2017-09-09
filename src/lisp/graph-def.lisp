;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module GRAPH-DEF (Trend Charts, aka "new graphs")

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Author(s): Joseph E. Devlin


(declare-forward-references
  (parse-graph-expression-with-info function install)
  (color-or-metacolor-p function grammar4)
  (text-slot-value-to-evaluation-text function attr-export)
  (clear-incomplete-painting-actions function graphs)
  (parse-text-string function attr-export))



;;;; Basic Data Structures for trend-chart

;;; This section contains component-type definitions,
;;; grammar categories, slot-value-writers/compilers,
;;; classes, reclaimers, and other storage-related definitions.
;;; The slot-putters and some special expression compilers
;;; are in a sections called Installing a trend-chart.

(defmacro def-frame-like-category-interface ((name &key selector-name) &body cases)
  `(define-category-evaluator-interface (,name :access read-write)
       (structure name
		  ((,selector-name (member ,@(loop for (user-tag . ignore) in cases
						   collect user-tag)))
		   ,@(loop with res = nil
			   for (user-tag internal-tag . properties) in cases
			   do

		       (loop for (user-name internal-name type-specification . ignore)
				 in properties
			     do
			 (push `(,user-name ,type-specification) res))
		       finally
			     (return (nreverse res))))
		  (and ,selector-name))
     ((set-form (evaluation-value))
      (let ((,selector-name
	      (evaluation-symbol-symbol
		(evaluation-structure-slot evaluation-value ',selector-name))))
	(case ,selector-name
	  ,@(loop for (user-case-tag internal-tag . properties)
		     in cases
		  collect
		  `(,user-case-tag
		      ,(if properties
			   `(let (,@(loop for (user-name . ignore) in properties
					  collect
					  `(,user-name (evaluation-structure-slot
							 evaluation-value ',user-name))))
			      (cond
				((and ,@(mapcar 'car properties))
				 (make-frame-like-category-parse-result
				   ',name
				   ',internal-tag
				   (phrase-list
				     ,@(loop for (user-name internal-name
							    type-specification style)
						 in properties
					     collect `',internal-name
					     collect
					     `(evaluation-value-to-frame-like-value-property
						,user-name ',type-specification ',style)))))
				 (t
				  (values bad-phrase
					  (copy-text-string
					    ,(format nil "must specify all of (~{~a~^, ~})"
						     (mapcar 'car properties)))))))
			   `(make-frame-like-category-parse-result
			      ',name ',internal-tag nil)))))))
     ((get-form (slot-value))
      (case (frame-like-value-key slot-value)
	,@(loop for (user-case-tag internal-tag . properties) in cases
	       collect
	       `(,internal-tag
		  (allocate-evaluation-structure-inline
		    ',selector-name (make-evaluation-symbol ',user-case-tag)
		    ,@(loop for (user-name internal-name type-specification style)
				in properties
			    collect `',user-name
			    collect
			    `(frame-like-value-property-to-evaluation-value
			       (frame-like-value-property slot-value ',internal-name)
			       ',type-specification ',style)))))))))

(defun evaluation-value-to-frame-like-value-property (evaluation-value
						      type-specification style)
  (let ((value
	  (cond
	    ((type-specification-subtype-p type-specification 'number)
	     (evaluation-quantity-to-phrase-quantity evaluation-value))
	    ((type-specification-subtype-p type-specification 'symbol)
	     (evaluation-symbol-symbol evaluation-value))
	    ((type-specification-subtype-p type-specification 'text)
	     (copy-text-string (evaluation-text-value evaluation-value)))
	    (t
	     (error "unsupported frame-like-value-property type-specification")))))
    (cond ((eq style 'interval)
	   (phrase-cons value 'seconds))
	  (t
	   value))))
	
;;; HERE
;;; 3.5 single compound slot value infrastructure
;;; 4 test a little bit for each
;;; 5 talk to Jared

(defun frame-like-value-property-to-evaluation-value (slot-value type-specification style)
  (declare (ignore type-specification))
  (let ((value (cond ((eq style 'interval)
		      (car slot-value))
		     (t
		      slot-value))))
    (make-evaluation-value-based-on-type value)))


(add-grammar-rules
  '(
    (significant-digit-spec integer)
    (grid-line-ratio integer)
    (absolute-time-spec ('not 'yet 'implemented))
    (range-slack-spec integer)
    (plot-expression unique-expression)
    (extant-color-or-metacolor color-or-metacolor)
    (extra-value-grid-line ('at number 'in color) (2 . 4))
    (extra-value-grid-line ('at number) (2 . default))))

(add-grammar-rules-for-list
  'extra-value-grid-lines 'extra-value-grid-line
  '\, nil 'none)

(def-slot-value-compiler extant-color-or-metacolor (parse-result)
  (cond ((color-or-metacolor-p parse-result)
	 parse-result)
	(t
	 (values bad-phrase
		 (tformat-text-string
		   "Unknown color requested: ~NV" parse-result)))))

(define-category-evaluator-interface (extant-color-or-metacolor
				       :access read-write)
    symbol
  ((set-form (evaluation-value))
   (if (eq evaluation-value 'none)
       nil
       evaluation-value))
  ((get-form (slot-value))
   (or slot-value 'none)))

(def-slot-value-writer extant-color-or-metacolor (slot-value)
  (twrite-color slot-value))

(def-frame-like-grammar-category 2d-shading-target-spec
  ((none)                     (none)
   (top)                      (constant target 'top)
   (bottom)                   (constant target 'bottom)))
;  ((unreserved-symbol 1))           (plot target 1))

(define-category-evaluator-interface (2d-shading-target-spec :access read-write)
    (or (no-item) symbol)
  ((set-form (evaluation-value))
   (evaluation-etypecase evaluation-value
     ((no-item)
      (make-frame-like-category-parse-result
	'2d-shading-target-spec 'none nil))
     (symbol
       (let ((symbol (evaluation-symbol-symbol evaluation-value)))
	 (cond
	   ((or (eq symbol 'top) (eq symbol 'bottom))
	    (make-frame-like-category-parse-result
	      '2d-shading-target-spec 'constant (phrase-list 'target symbol)))
	   ((eq symbol 'none)
	    (make-frame-like-category-parse-result
	      '2d-shading-target-spec 'none nil))
	   (t
	    (values bad-phrase
		    (tformat-text-string
		      "shading target, ~a, must be TOP, or BOTTOM"))))))))
  ((get-form (slot-value))
   (case (frame-like-value-key slot-value)
     (none 'none)
     (constant
	(make-evaluation-symbol (frame-like-value-property slot-value 'target))))))

(def-frame-like-grammar-category 2d-plot-marker-shape
  ((triangle)                               (standard shape 'triangle)
   (plus-sign)                              (standard shape 'plus-sign)
   (square)                                 (standard shape 'square)
   (current value)                    (standard shape 'current-value)
   (icon of (object-class 1))         (custom icon-class 1)))

(define-category-evaluator-interface (2d-plot-marker-shape :access read-write)
   (structure plot-marker
	      ((standard-shape symbol) ; should be member
	       (icon-of-class symbol))
	      (or standard-shape icon-of-class))
  ((set-form (evaluation-value))
   (let ((standard-shape? (evaluation-structure-slot evaluation-value 'standard-shape)))
     (cond (standard-shape?
	    (make-frame-like-category-parse-result
	      '2d-plot-marker-shape
	      'standard
	      (phrase-list 'shape (evaluation-symbol-symbol standard-shape?))))
	   (t
	    (make-frame-like-category-parse-result
	      '2d-plot-marker-shape
	      'custom
	      (phrase-list
		'icon-class
		(evaluation-symbol-symbol
		  (evaluation-structure-slot evaluation-value 'icon-of-class))))))))
  ((get-form (slot-value))
   (case (frame-like-value-key slot-value)
     (standard
      (allocate-evaluation-structure-inline
	'standard-shape
	(make-evaluation-symbol (frame-like-value-property slot-value 'shape))))
     (custom
      (allocate-evaluation-structure-inline
	'icon-of-class
	(make-evaluation-symbol (frame-like-value-property slot-value 'icon-class)))))))
	     
(def-frame-like-grammar-category 2d-location-spec
  ((none)                (none)
   (above data window)   (relative-to-window position 'above)
   (below data window)   (relative-to-window position 'below)))
    
(def-frame-like-grammar-category 2d-tickmark-label-color
  (((color-or-metacolor 1))              (absolute color 1)
   (match plot color)       (matching target 'plot-color))
  (funcalled-check (absolute color) color-or-metacolor-p
		   (copy-text-string
		     "Unknown color requested")))

(define-category-evaluator-interface (2d-tickmark-label-color :access read-write)
   (structure label-color
	      ((label-color-type (member absolute matching-plot-color))
	       (color (named extant-color-or-metacolor)))
	      (and label-color-type))
  ((set-form (evaluation-value))
   (let ((label-color-type
	   (evaluation-symbol-symbol
	     (evaluation-structure-slot evaluation-value 'label-color-type))))
     (case label-color-type
       (matching-plot-color
	(make-frame-like-category-parse-result
	  '2d-tickmark-label-color
	  'matching
	  (phrase-list 'target 'plot-color)))
       (absolute
	(let ((color (evaluation-structure-slot evaluation-value 'color)))
	  (cond
	    (color
	     (make-frame-like-category-parse-result
	       '2d-tickmark-label-color
	       'absolute
	       (phrase-list
		 'color (evaluation-symbol-symbol color))))
	    (t
	     (values
	       bad-phrase
	       (tformat-text-string "Unknown color requested: ~NV" color)))))))))
  ((get-form (slot-value))
   (case (frame-like-value-key slot-value)
     (absolute 
      (allocate-evaluation-structure-inline
	'label-color-type 'absolute
	'color 
	(make-evaluation-symbol (frame-like-value-property slot-value 'color))))
     (matching
      (allocate-evaluation-structure-inline
	'label-color-type
	(make-evaluation-symbol 'matching-plot-color))))))
	     

(def-frame-like-grammar-category 2d-time-span-spec
  ((show all history)              (all-history)
   ((interval 1))                  (interval length 1))
  (interval-check (interval length) 1 nil
		  (copy-constant-wide-string #w"Must specify interval of at least 1 second")))

(def-frame-like-category-interface (2d-time-span-spec
				     :selector-name data-window-time-span-mode)
  (show-all-history all-history)
  (interval interval
	    (number-of-seconds length integer interval)))

(def-frame-like-grammar-category 2d-total-time-span-spec
  ((same as data window)       (data-window)
   ((interval 1))              (interval length 1))
  (interval-check (interval length) 1 nil
		  (copy-constant-wide-string #w"Must specify interval of at least 1 second")))

(def-frame-like-category-interface (2d-total-time-span-spec
				     :selector-name total-time-span-mode)
  (same-as-data-window data-window)
  (interval interval
	    (number-of-seconds length integer interval)))

(def-frame-like-grammar-category 2d-end-time-spec
  ((current time)              (current-time) ; a 4.0 mode
   (last sample)               (last-sample)  ; a 3.0 mode
   ((interval 1) after start)  (start-relative interval 1) ; a 3.0 mode
   ;(at (absoulte-time-spec 1)) (absolute       time     1) ; a 4.0 mode
   ))

(def-frame-like-category-interface (2d-end-time-spec
				     :selector-name end-time-mode)
  (current-time current-time)
  (last-sample last-sample)
  (start-relative start-relative
		  (number-of-seconds interval integer interval)))

(def-frame-like-grammar-category 2d-scrolling-alignment-spec
  ((none)                   (none)
   ((interval 1))            (interval length 1))
  (interval-check (interval length) 1 86400
		  (copy-text-string
		    "Must use an interval between 1 seconds and one-day")))

(def-frame-like-grammar-category 2d-time-axis-tickmark-frequency-spec
    ((none)                           (none)
     (automatic)                      (synchronized)
; show time labels synchronized to scrolling) (synchronized)
     (every (interval 1))   (interval length 1))
  (interval-check (interval length) 1 86400
		  (copy-text-string
		    "Must use an interval between 1 second and one-day")))

(def-frame-like-category-interface (2d-time-axis-tickmark-frequency-spec
				     :selector-name label-frequency-mode)
  (no-labels none)
  (synchronized synchronized)
  (interval interval
	    (number-of-seconds length integer interval)))
    

(def-frame-like-grammar-category 2d-plot-marker-frequency
  ((every (integer 1) points) (ratio number 1))
  (range-check (ratio number) 1 1000
	       (copy-text-string 
		 "Must specify a ratio between 1 and 1000")))


(define-category-evaluator-interface (2d-plot-marker-frequency :access read-write)
    (structure plot-marker-frequency
	       ((points-per-marker integer)) ; really an integer range 1 1000
	       (and points-per-marker))
  ((set-form (evaluation-value))
   (let ((points-per-marker? (evaluation-structure-slot evaluation-value 'points-per-marker)))
     (cond
       (points-per-marker?
	(let ((points-per-marker (evaluation-integer-value points-per-marker?)))
	  (cond ((<=f 1 points-per-marker 1000)
		 (make-frame-like-category-parse-result
		   '2d-plot-marker-frequency
		   'ratio
		   (phrase-list 'number points-per-marker)))
		(t
		 (values bad-phrase
			 (copy-text-string
			   "Must specify a ratio of between 1 and 1000 points per marker"))))))
       (t
	;; cannot reach this case until point format supports some other features
	))))
  ((get-form (slot-value))
   (case (frame-like-value-key slot-value)
     (ratio
      (allocate-evaluation-structure-inline
	'points-per-marker
	(make-evaluation-integer (frame-like-value-property slot-value 'number))))
     ;; there could be other cases eventually
     )))
     

(defun-simple positive-value-p (number)
  (cond ((managed-float-p number)
	 (with-temporary-gensym-float-creation check-positive-value
	   (>e (managed-float-value number) 0.0)))
	(t
	 (>f number 0))))

(def-frame-like-grammar-category 2d-value-axis-tickmark-frequency-spec
  (; (none)                             (none)
   (automatic)                        (automatic)
   ((integer 1) labels)            (fraction count 1)
   (every (number 1))              (interval width 1 origin 0.0)
   (every (number 1)
	 beginning at (number 2))     (interval width 1 origin 2))
  (funcalled-check (interval width) positive-value-p
		   (copy-text-string
		     "Must specify a positive label interval"))
  (range-check (fraction count) 1 1000
	       (copy-text-string
		 "Must specify between 1 and 1000 labels")))

(define-category-evaluator-interface (2d-value-axis-tickmark-frequency-spec
				       :access read-write)
   (structure tickmark-frequency
	      ((label-layout-mode (member automatic grid-division interval))
	       (number-of-grid-divisions integer) ; 1 1000
	       (interval-width number)
	       (interval-origin number))
	      (and label-layout-mode))
  ((set-form (evaluation-value))
   (let ((label-layout-mode
	   (evaluation-symbol-symbol
	     (evaluation-structure-slot evaluation-value 'label-layout-mode))))
     (case label-layout-mode
       (automatic
	(make-frame-like-category-parse-result
	  '2d-value-axis-tickmark-frequency-spec
	  'automatic
	  nil))
       (grid-division
	(let ((number-of-grid-divisions
		(evaluation-structure-slot evaluation-value 'number-of-grid-divisions)))
	  (cond
	    (number-of-grid-divisions
	     (make-frame-like-category-parse-result
	       '2d-value-axis-tickmark-frequency-spec
	       'fraction
	       (phrase-list
		 'count
		 (evaluation-quantity-to-phrase-quantity number-of-grid-divisions))))
	    (t
	     (values
	       bad-phrase (copy-text-string
			    "must specify number-of-grid-divisions"))))))
       (interval
	(let ((interval-width (evaluation-structure-slot
				evaluation-value 'interval-width))
	      (interval-origin? (evaluation-structure-slot
				  evaluation-value 'interval-origin)))
	  (cond
	    (interval-width
	     (make-frame-like-category-parse-result
	       '2d-value-axis-tickmark-frequency-spec
	       'interval
	       (phrase-list
		 'width (evaluation-quantity-to-phrase-quantity interval-width)
		 'origin (if interval-origin?
			     (evaluation-quantity-to-phrase-quantity interval-origin?)
			     (make-phrase-float 0.0)))))
	    (t
	     (values
		 bad-phrase (copy-text-string
			      "must specify interval-width")))))))))
  ((get-form (slot-value))
   (case (frame-like-value-key slot-value)
     (automatic
      (allocate-evaluation-structure-inline
	'label-layout-mode (make-evaluation-symbol 'automatic)))
     (fraction
      (allocate-evaluation-structure-inline
	'label-layout-mode (make-evaluation-symbol 'grid-division)
	'number-of-grid-divisions (make-evaluation-integer
				    (frame-like-value-property slot-value 'count))))
     (interval
      (allocate-evaluation-structure-inline
	'label-layout-mode (make-evaluation-symbol 'interval)
	'interval-width  (make-evaluation-value-based-on-type
			   (frame-like-value-property slot-value 'width))
	'interval-origin (if (frame-like-value-property slot-value 'origin)
			     (make-evaluation-value-based-on-type
			       (frame-like-value-property slot-value 'origin))
			     (with-temporary-gensym-float-creation label-freq-setter
			       (make-evaluation-float 0.0))))))))

(def-frame-like-grammar-category 2d-value-axis-bounds-spec
  ((none)                           (none)
   (from (number 1) to (number 2))  (specified lower 1 upper 2))
  (funcalled-check (specified lower upper) value-axis-bounds-check
		   (tformat-text-string "Lower bound must be less than upper bound and greater than ~%~a. Upper bound must be less than ~a"
					(most-negative-value)
					(most-positive-value))))

(define-category-evaluator-interface (2d-value-axis-bounds-spec
				       :access read-write)
    (or (no-item)
	(structure bounds
		   ((lower-bound number)
		    (upper-bound number))
		   (and lower-bound upper-bound)))
  ((set-form (evaluation-value))
   (evaluation-etypecase evaluation-value
     ((no-item)
      (make-frame-like-category-parse-result
	'2d-value-axis-bounds-spec
	'none
	nil))
     ((structure)
      (make-frame-like-category-parse-result
	'2d-value-axis-bounds-spec
	'specified
	(phrase-list
	  'lower
	  (evaluation-quantity-to-phrase-quantity
	    (evaluation-structure-slot evaluation-value 'lower-bound))
	  'upper
	  (evaluation-quantity-to-phrase-quantity
	    (evaluation-structure-slot evaluation-value 'upper-bound)))))))
  ((get-form (slot-value))
   (case (frame-like-value-key slot-value)
     (none
      nil)
     (specified
      (allocate-evaluation-structure-inline
	'lower-bound
	(make-evaluation-value-based-on-type
	  (frame-like-value-property slot-value 'lower))
	'upper-bound
	(make-evaluation-value-based-on-type
	  (frame-like-value-property slot-value 'upper)))))))

(defun value-axis-bounds-check (low high)
  (with-temporary-gensym-float-creation value-axis-bounds-check
    (let ((low-float (cond ((managed-float-p low)
			    (managed-float-value low))
			   (t
			    (coerce-fixnum-to-gensym-float low))))
	  (high-float (cond ((managed-float-p high)
			    (managed-float-value high))
			   (t
			    (coerce-fixnum-to-gensym-float high)))))
      (and (<e low-float high-float)
	   (<e high-float (most-positive-value))
	   (>e low-float (most-negative-value))))))

(def-frame-like-grammar-category trend-chart-legend-color-spec
  ((match plot colors)                     (matching)
   ((color-or-metacolor 1))                (absolute color 1))
  (funcalled-check (absolute color) color-or-metacolor-p
		   (copy-text-string
		     "Unknown color requested")))


(define-category-evaluator-interface (trend-chart-legend-color-spec
				       :access read-write)
   (structure legend-color
	      ((legend-color-type (member absolute matching-plot-color))
	       (color (named extant-color-or-metacolor)))
	      (and legend-color-type))
  ((set-form (evaluation-value))
   (let ((legend-color-type
	   (evaluation-symbol-symbol
	     (evaluation-structure-slot evaluation-value 'legend-color-type))))
     (case legend-color-type
       (matching-plot-color
	(make-frame-like-category-parse-result
	  'trend-chart-legend-color-spec
	  'matching
	  nil))
       (absolute
	(let ((color (evaluation-structure-slot evaluation-value 'color)))
	  (cond
	    (color
	     (make-frame-like-category-parse-result
	       'trend-chart-legend-color-spec
	       'absolute
	       (phrase-list
		 'color (evaluation-symbol-symbol color))))
	    (t
	     (values
	       bad-phrase
	       (tformat-text-string "Unknown color requested: ~NV" color)))))))))
  ((get-form (slot-value))
   (case (frame-like-value-key slot-value)
     (absolute 
      (allocate-evaluation-structure-inline
	'legend-color-type 'absolute
	'color 
	(make-evaluation-symbol (frame-like-value-property slot-value 'color))))
     (matching
      (allocate-evaluation-structure-inline
	'legend-color-type
	(make-evaluation-symbol 'matching-plot-color))))))
	     


(def-enumeration-grammar-category value-axis-position
  right
  left)

(def-enumeration-grammar-category trend-chart-legend-position
  above
  below)

(def-enumeration-grammar-category 2d-line-style
  ((sample and hold \, without risers) sample-and-hold)
  ((sample and hold) sample-and-hold-with-risers)
  ((linear) interpolated))

(def-enumeration-grammar-category time-axis-label-alignment
  left
  right
  center)

(def-enumeration-grammar-category time-axis-label-format-spec
  hh-mm
  ((hh-mm as an interval) hh-mm-interval)
  hh-mm-am-pm
  hh-mm-ss
  ((hh-mm-ss as an interval) hh-mm-ss-interval)
  hh-mm-ss-am-pm
  mm-ss
  ((mm-ss as an interval) mm-ss-interval)
  ((dd-hh-mm as an interval) dd-hh-mm-interval)
  mmm-dd-hh-mm
  ((mm-dd-hh-mm) mm/dd-hh-mm)
  mm-yy
  mm-dd-yy
  yy-mm-dd    
  dd-mm-yy
  dd-mmm-yyyy
  mmm-dd-yyyy
  mmm-yyyy
  ((hh.hh as an interval) hh.hh-interval))

(def-enumeration-grammar-category 2d-range-mode
  fixed
  ((autoranging on data window) automatic)
  ((autoranging on all past values) high-water-marking))


(def-slot-value-compiler extra-value-grid-lines (parse-result)
  ;; range check them colors
  (loop for (number . color-spec) in (cdr parse-result)
	do
    (unless (or (eq color-spec 'default)
		(color-or-metacolor-p color-spec))
      (return (values bad-phrase
		      (copy-text-string
			"unknown color specified"))))
	finally
	  (return parse-result)))

(define-category-evaluator-interface (extra-value-grid-lines
				       :access read-write)
    (or (no-item)
	(sequence (structure extra-grid-line
			     ((value number)
			      (color symbol))
			     (and value))
		  1))
  ((set-form (evaluation-value))
   (evaluation-etypecase evaluation-value
     ((no-item)
      nil)
     ((sequence)
      (phrase-cons
	'\,
	(with-evaluation-sequence-to-phrase-list-mapping
	    (evaluation-value extra-grid-line)
	  (phrase-cons (evaluation-quantity-to-phrase-quantity
			 (evaluation-structure-slot extra-grid-line 'value))
		       (or (evaluation-structure-slot extra-grid-line 'color)
			   'default)))))))
  ((get-form (slot-value))
   (cond
     (slot-value
      (with-list-to-evaluation-sequence-mapping
	  ((cdr slot-value) value-color-pair)
	(allocate-evaluation-structure-inline
	  'value (make-evaluation-value-based-on-type (car value-color-pair))
	  'color (make-evaluation-symbol (cdr value-color-pair)))))
     (t
      nil))))
    
(def-slot-value-writer extra-value-grid-lines (slot-value)
  (if slot-value
      (loop for (number . color-spec) in (cdr slot-value)
	    as first-p = t then nil
	    do
	(unless first-p
	  (twrite ", "))
	(twrite "at ")
	(twrite number)
	(unless (eq color-spec 'default)
	  (twrite " in ")
	  (twrite color-spec)))
      (twrite-string "none")))

(defmacro define-integer-range-category (name (low high) complaint)
  `(progn
     (def-slot-value-compiler ,name (parse-result)
       (cond ((<=f ,low parse-result ,high)
	      parse-result)
	     (t
	      (values bad-phrase (copy-text-string ,complaint)))))
     (define-category-evaluator-interface (,name
					    :access read-write)
	 integer
       ((set-form (evaluation-value))
	(evaluation-integer-value evaluation-value))
;	(let ((value (evaluation-integer-value evaluation-value)))
;	  (cond ((<=f ,low value ,high)
;		 value)
;		(t
;		 (values bad-phrase (copy-text-string ,complaint))))))
       ((get-form (slot-value))
	(make-evaluation-integer slot-value)))
     (def-slot-value-writer ,name (slot-value)
       (twrite slot-value))))

(define-integer-range-category significant-digit-spec (1 15)
  "Must specify between 1 and 15 significant digits")


(define-integer-range-category range-slack-spec (0 100)
  "Must specify a range slack of 0 to 100 percent")

(define-integer-range-category grid-line-ratio (0 50)
  "Must specify between 0 and 50 grid lines per label")


;;; we can re-write this when def-frame-like-grammar-category
;;; has a notion of a null slot
  
(add-grammar-rules
  '((trend-chart-scroll-interval positive-quantity-interval)
    (trend-chart-scroll-interval
     'automatic
     compute-automatically)
    (plot-update-interval-spec
     display-interval)
    (plot-update-interval-spec
     (display-interval '\,
      'with 'minimum 'interval 'between 'data 'points '= quantity-interval)
     (interval-with-granularity 1 10))))

;;; The grammar category `plot-update-interval-spec' is being defined
;;; in terms of the categories display-interval and quantity-interval
;;; rather than through def-frame-like-grammar-category for backward
;;; compatibility with 4.0b1 which was filling this slot with a simple
;;; display interval.

(def-slot-value-compiler plot-update-interval-spec (parse-result)
  (cond
    ((and (consp parse-result)
	  (eq (car parse-result) 'interval-with-granularity))
     (multiple-value-bind (display-interval-parse-result error?)
	 (funcall (slot-value-compiler 'display-interval)
		  (cadr parse-result)
		  nil nil nil nil nil)
       (cond
	 ((eq display-interval-parse-result bad-phrase)
	  (values bad-phrase error?))
	 (t
	  (multiple-value-bind (quantity-interval-parse-result error?)
	      (funcall (slot-value-compiler 'quantity-interval)
		       (caddr parse-result)
		       nil nil nil nil nil)
	    (cond ((eq quantity-interval-parse-result bad-phrase)
		   (values bad-phrase error?))
		  (t
		   (slot-value-list 'interval-with-granularity
				    display-interval-parse-result
				    quantity-interval-parse-result))))))))
    (t
     (funcall (slot-value-compiler 'display-interval)
	      parse-result
	      nil nil nil nil nil))))

(def-slot-value-writer plot-update-interval-spec (slot-value frame)
  (cond
    ((and (consp slot-value)
	  (eq (car slot-value) 'interval-with-granularity))
     (funcall (slot-value-writer 'display-interval)
	      (cadr slot-value) frame)
     (twrite-string ", with minimum interval between data points = ")
     (funcall (slot-value-writer 'quantity-interval)
	      (caddr slot-value) frame))
    (t
     (funcall (slot-value-writer 'display-interval)
	      slot-value frame))))

(defun plot-update-interval-period (plot-update-interval)
  (cond ((and (consp plot-update-interval)
	      (eq (car plot-update-interval) 'interval-with-granularity))
	 (cadr plot-update-interval))
	(t
	 plot-update-interval)))

(defun plot-update-interval-granularity? (plot-update-interval)
  (cond ((and (consp plot-update-interval)
	      (eq (car plot-update-interval) 'interval-with-granularity))
	 (caddr plot-update-interval))
	(t
	 nil)))

(def-slot-value-compiler trend-chart-scroll-interval (parse-result)
  (cond ((eq parse-result 'compute-automatically)
	 nil)
	((if (managed-float-p (car parse-result))
	     (with-temporary-gensym-float-creation trend-chart-scroll-interval
	       (<e (managed-float-value (car parse-result)) 1.0))
	     (<f (car parse-result) 1))
	 (values bad-phrase
		 (copy-text-string
		   "Must specify interval of at least 1 second.")))
	(t
	 parse-result)))
(define-category-evaluator-interface (trend-chart-scroll-interval
				       :access read-write)
    (structure scroll-interval
	      ((scroll-interval-type (member automatic interval))
	       (interval integer))
	      (and scroll-interval-type))
  ((set-form (evaluation-value))
   (let ((scroll-interval-type
	   (evaluation-structure-slot evaluation-value 'scroll-interval-type)))
     (case scroll-interval-type
       (automatic 'compute-automatically)
       (interval
	(let ((seconds? (evaluation-structure-slot evaluation-value 'interval)))
	  (cond
	    (seconds?
	     (phrase-cons seconds? 'seconds))
	    (t
	     (values bad-phrase
		     (copy-constant-wide-string #w"Must specify interval")))))))))
  ((get-form (slot-value))
   (cond
     (slot-value
      (allocate-evaluation-structure-inline
	'scroll-interval-type 'interval
	'interval (car slot-value)))
     (t
      (allocate-evaluation-structure-inline
	'scroll-interval-type 'automatic)))))

(def-slot-value-writer trend-chart-scroll-interval (slot-value)
  (cond ((eq slot-value nil)
	 (twrite-string "automatic"))
	(t
	 (print-constant (car slot-value) 'seconds))))

(def-slot-component-alias time-axis-base-line-visible?
   baseline-visible? trend-chart time-axis)

(def-slot-component-alias color-for-time-axis-base-line
    baseline-color trend-chart time-axis)

(def-slot-component-alias color-for-time-grid-lines
   grid-line-color trend-chart time-axis)

(def-slot-component-alias time-axis-label-format
   time-format trend-chart time-axis)

(def-slot-component-alias time-axis-label-alignment
    label-alignment trend-chart time-axis)

(def-slot-component-alias time-axis-absolute-labels-visible?
    absolute-labels-visible? trend-chart time-axis)

(def-slot-component-alias time-axis-relative-labels-visible?
    relative-labels-visible? trend-chart time-axis)

(def-slot-component-alias time-axis-tickmark-frequency
    label-frequency trend-chart time-axis)

(def-slot-component-alias color-for-time-tickmarks
    label-color trend-chart time-axis)

(def-slot-component-alias ratio-of-grid-lines-to-time-axis-tickmarks
    grid-lines-per-label trend-chart time-axis)

(def-slot-component-alias time-axis-update-interval
    display-update-interval trend-chart time-axis)

(def-slot-component-alias time-axis-jump-scroll?
    jump-scroll? trend-chart time-axis)

(def-slot-component-alias time-axis-scroll-interval
    jump-scroll-interval trend-chart time-axis)

(def-slot-component-alias time-grid-lines-visible?
    grid-lines-visible? trend-chart time-axis)

(def-compound-type time-axis
  (data-window-time-span
    (:funcall-at-load-time
      make-frame-like-category-default
      2d-time-span-spec interval (length (300 . seconds)))
    (type 2d-time-span-spec))
  (total-time-span
    (:funcall-at-load-time
      make-frame-like-category-default
      2d-total-time-span-spec data-window nil)
    (type 2d-total-time-span-spec))
  (end-time
    (:funcall-at-load-time
      make-frame-like-category-default
      2d-end-time-spec last-sample nil)
    (type 2d-end-time-spec))
  (time-axis-update-interval 2 (type display-interval))
  (time-axis-jump-scroll? t (type yes-or-no))
  (time-axis-scroll-interval nil (type trend-chart-scroll-interval))
  (time-axis-absolute-labels-visible? t (type yes-or-no))
  (time-axis-relative-labels-visible? nil (type yes-or-no))
  (time-axis-tickmark-frequency
    (:funcall-at-load-time
      make-frame-like-category-default
      2d-time-axis-tickmark-frequency-spec synchronized nil)
    (type 2d-time-axis-tickmark-frequency-spec))
  (time-axis-label-alignment
    right
    (type time-axis-label-alignment))
  (time-axis-label-format
    hh-mm-ss-am-pm
    (type time-axis-label-format-spec))
  (color-for-time-tickmarks	
    black (type extant-color-or-metacolor))
  (time-grid-lines-visible? t (type yes-or-no))
  (color-for-time-grid-lines		; alt.: time-grid-line-color
    gray (type extant-color-or-metacolor))
  (ratio-of-grid-lines-to-time-axis-tickmarks ; alt.: time-grid-line-ratio
    1 (type grid-line-ratio))
  (time-axis-base-line-visible? t (type yes-or-no))
  (color-for-time-axis-base-line black (type extant-color-or-metacolor))
  )

(def-slot-component-alias value-axis-label-significant-digits
    significant-digits-for-labels
  trend-chart value-axis)

(def-slot-component-alias color-for-value-axis-tickmarks
    label-color trend-chart value-axis)

(def-slot-component-alias value-axis-tickmark-frequency
    label-frequency trend-chart value-axis)

(def-slot-component-alias ratio-of-grid-lines-to-value-axis-tickmarks
    grid-lines-per-label trend-chart value-axis)

(def-slot-component-alias value-axis-bounds
  range-bounds trend-chart value-axis)

(def-slot-component-alias value-axis-range-mode
   range-mode trend-chart value-axis)

(def-slot-component-alias color-for-value-axis-base-line
   baseline-color trend-chart value-axis)

(def-slot-component-alias value-axis-labels-visible?
   labels-visible? trend-chart value-axis)

(def-slot-component-alias value-axis-base-line-visible?
   baseline-visible? trend-chart value-axis)

(def-slot-component-alias show-value-labels-as-percent?
   show-labels-as-percent? trend-chart value-axis)

(def-slot-component-alias color-for-value-grid-lines
   grid-line-color trend-chart value-axis)

(def-slot-component-alias value-grid-lines-visible?
   grid-lines-visible? trend-chart value-axis)

(def-slot-component-alias extra-value-grid-lines
   extra-grid-lines trend-chart value-axis)

(def-slot-component-alias value-axis-names
    names trend-chart value-axis)

(def-slot-component-alias value-axis-range-slack
    range-slack-percentage trend-chart value-axis)

;;; hack: done here because def-compound-type can't do it
(defmacro chart-element-uid (slot-component-group)
  (slot-component-group-indicator slot-component-group))

(def-compound-type (value-axis :named t)
  (chart-element-uid nil (not-user-editable do-not-put-in-attribute-tables))
  (value-axis-visible? t (type yes-or-no)
		       not-editable-in-default)
  (value-axis-position right (type value-axis-position))
  (value-axis-range-mode automatic (type 2d-range-mode))
  (value-axis-bounds
    (:funcall-at-load-time
      make-frame-like-category-default
      2d-value-axis-bounds-spec none nil)
    (type 2d-value-axis-bounds-spec))
  (value-axis-range-slack 10 (type range-slack-spec))
  (value-axis-labels-visible? t (type yes-or-no))
  (color-for-value-axis-tickmarks
    (:funcall-at-load-time
      make-frame-like-category-default
      2d-tickmark-label-color absolute (color black))
    (type 2d-tickmark-label-color))
  (value-axis-tickmark-frequency
    (:funcall-at-load-time
      make-frame-like-category-default
      2d-value-axis-tickmark-frequency-spec automatic nil)
    (type 2d-value-axis-tickmark-frequency-spec))
  (show-value-labels-as-percent? nil (type yes-or-no))
  (value-axis-label-significant-digits
    4
    (type significant-digit-spec))
  (value-grid-lines-visible? t (type yes-or-no))
  (color-for-value-grid-lines
    gray (type extant-color-or-metacolor))
  (ratio-of-grid-lines-to-value-axis-tickmarks
    1 (type grid-line-ratio))
  (extra-value-grid-lines nil (type extra-value-grid-lines))
  (value-axis-base-line-visible? t (type yes-or-no))
  (color-for-value-axis-base-line black (type extant-color-or-metacolor))

  ;; internal slots
  (value-axis-lower-bound? nil (internal))
  (value-axis-upper-bound? nil (internal))
  (value-axis-high-value nil (internal))
  (value-axis-low-value nil (internal))
  ;; the next two slots are used for telewindows2 only
  (value-axis-last-sent-high-value nil (internal)) ; managed-float
  (value-axis-last-sent-low-value nil (internal))) ; managed-float

(def-slot-component-alias trend-chart-legend-visible?
   legend-visible? trend-chart trend-chart-format)

(def-slot-component-alias trend-chart-legend-color
   legend-color trend-chart trend-chart-format)

(def-slot-component-alias trend-chart-legend-position
   legend-position trend-chart trend-chart-format)

(def-slot-component-alias trend-chart-label-visible?
   title-visible? trend-chart trend-chart-format)

(def-slot-component-alias trend-chart-label-position
   title-position trend-chart trend-chart-format)

(def-slot-component-alias trend-chart-label-color
   title-color trend-chart trend-chart-format)

(def-compound-type trend-chart-format
  (outer-border-visible? t (type yes-or-no))
  (outer-border-color black (type extant-color-or-metacolor))
  (outer-background-color smoke (type extant-color-or-metacolor))
  (data-window-border-visible? nil (type yes-or-no))
  (data-window-border-color black (type extant-color-or-metacolor))
  (data-window-background-color smoke (type extant-color-or-metacolor))
  (trend-chart-legend-visible? t (type yes-or-no))
  (trend-chart-legend-color
    (:funcall-at-load-time
      make-frame-like-category-default
      trend-chart-legend-color-spec
      matching nil)
    (type trend-chart-legend-color-spec))
  (trend-chart-legend-position
    below
    (type trend-chart-legend-position))
  (trend-chart-label-visible? t (type yes-or-no))
  (trend-chart-label-color black (type extant-color-or-metacolor))
  (trend-chart-label-position
    above
    (type trend-chart-legend-position))
  )
;  (show-name-in-legend?  t (type yes-or-no))
;  (use-plot-colors-and-markers-in-legend?  t (type yes-or-no))
;  (show-expression-in-legend? t (type yes-or-no))

;  (end-time-display
;    (:funcall make-frame-like-category-default
;	      2d-location-spec none nil)
;    (type 2d-location-spec))
;  (plot-bounds-display 
;    (:funcall make-frame-like-category-default
;	      2d-location-spec none nil)
;    (type 2d-location-spec))
;  (current-value-display
;    (:funcall make-frame-like-category-default
;	      2d-location-spec none nil)
;    (type 2d-location-spec)))


(def-slot-component-alias point-visible?
  markers-visible? trend-chart point-format)

(def-slot-component-alias point-color
   marker-color trend-chart point-format)

(def-slot-component-alias point-style
   marker-style trend-chart point-format)

(def-slot-component-alias point-frequency
   marker-frequency trend-chart point-format)

(def-slot-component-alias point-format-names
    names trend-chart point-format)

(def-compound-type (point-format :named t)
  (chart-element-uid nil (not-user-editable do-not-put-in-attribute-tables))
  (point-visible? nil (type yes-or-no))
  (point-color black (type extant-color-or-metacolor))
  (point-style
    (:funcall-at-load-time
      make-frame-like-category-default
      2d-plot-marker-shape standard (shape triangle))
    (type 2d-plot-marker-shape))
  (point-frequency
    (:funcall-at-load-time
      make-frame-like-category-default
      2d-plot-marker-frequency ratio (number 1))
    (type 2d-plot-marker-frequency)))

(def-slot-component-alias connector-line-style
   connector-interpolation trend-chart connector-format)

(def-slot-component-alias connector-visible?
    connectors-visible? trend-chart connector-format)

(def-slot-component-alias connector-format-names
    names trend-chart connector-format)

(def-compound-type (connector-format :named t)
  (chart-element-uid nil (not-user-editable do-not-put-in-attribute-tables))
  (connector-visible? t (type yes-or-no))
  (connector-line-color black (type extant-color-or-metacolor))
  (connector-line-style interpolated (type 2d-line-style))
  (connector-line-width 1 (type integer))
;  (connector-shading-color gray (type color))
  (connector-shading-target
    (:funcall-at-load-time
      make-frame-like-category-default
      2d-shading-target-spec none nil)
    (type 2d-shading-target-spec)))


(def-slot-component-alias plot-names
    names trend-chart plot)

(def-compound-type (plot :named t)
  (chart-element-uid nil (not-user-editable do-not-put-in-attribute-tables))
  (plot-use-local-history? t (type yes-or-no))
  (plot-axis 1 (reference trend-chart-value-axes component-reference))
  (plot-point-format 1 (reference trend-chart-point-formats component-reference))
  (plot-connector-format 1
			 (reference trend-chart-connector-formats component-reference))

  ;; Computation attributes
  (plot-update-interval 5 (type plot-update-interval-spec))
  (plot-wait-interval   2 (type display-interval))
  (plot-update-priority 2 (type priority))
  (plot-request-data-seeking?  t (type yes-or-no))
  (plot-request-event-updates? t (type yes-or-no))
  (plot-use-simulator? nil (type yes-or-no))
  (plot-tracing-and-breakpoints nil (type tracing-and-breakpoints))
  (include-in-legend? t (type yes-or-no))
  (plot-expression nil (type plot-expression text)
		   not-editable-in-default) ; Some day, (0 "0") by default?

  ;; internals
  (plot-history nil (internal))
  ;; the next three slots are used for telewindows2 only
  ;; They are the "absolute" indices from the history
  ;; (so that they always increase under normal updates)
  (plot-data-last-tc-representation-send-time? nil (internal))
  (plot-data-tc-representation-end-index? nil (internal))
  (plot-data-tc-representation-earliest-index? nil (internal))
  (plot-variable-or-parameter? nil (internal))
  (plot-number-cell-index nil (internal))
  (plot-v-or-p-cell-index nil (internal))
  (plot-index nil (internal))) ; used to index per-plot arrays in state


(def-slot-component-alias plot-update-interval
    update-interval trend-chart plot)
(def-slot-component-alias plot-wait-interval
    wait-interval trend-chart plot)
(def-slot-component-alias plot-update-priority
    update-priority trend-chart plot)
(def-slot-component-alias plot-request-data-seeking?
    may-request-data-seeking? trend-chart plot)
(def-slot-component-alias plot-request-event-updates?
    may-request-event-updates? trend-chart plot)
(def-slot-component-alias plot-use-simulator?
    use-simulator? trend-chart plot)
(def-slot-component-alias plot-use-local-history?
    use-local-history? trend-chart plot)
(def-slot-component-alias plot-tracing-and-breakpoints
    tracing-and-breakpoints trend-chart plot)

(def-slot-component-alias plot-expression
    expression trend-chart plot)
(def-slot-component-alias plot-axis
    value-axis-name-or-number trend-chart plot)
(def-slot-component-alias plot-point-format
    point-format-name-or-number trend-chart plot)
(def-slot-component-alias plot-connector-format
    connector-format-name-or-number trend-chart plot)


(def-class (2d-image-plane-state dependent-frame define-predicate)
  (2d-state-rendering nil vector-slot system) ; a graph-rendering structure (contains image-plane)
  (2d-state-base-time nil vector-slot system)    ; a managed-float
  (2d-state-grid-width nil vector-slot system) ; inner (borderless) measure
  (2d-state-grid-height nil vector-slot system) ; ditto
  (2d-state-grid-timespan nil vector-slot system) ; a managed-float
  (2d-state-position-shift nil vector-slot system)
  (2d-state-latest-event-indices nil vector-slot system) ; managed array
  (2d-state-latest-event-times nil vector-slot system)   ; managed array of managed float
  (2d-state-virtual-origin-x nil vector-slot system)
  (2d-state-raster-width-to-right nil vector-slot system)
  (2d-state-grid-data-height nil vector-slot system)
  (2d-state-latest-current-data-time nil vector-slot system)    ; a managed float
  (2d-state-end-time nil vector-slot system)                    ; a managed float
  (2d-incomplete-painting-actions nil vector-slot system)
  (2d-state-last-tickmark-time nil vector-slot system)
  (2d-state-label-counter nil vector-slot system)
  (2d-state-last-painting-time nil vector-slot system))

;; all of the slot values for the above class are reclaimed by
;; the default reclaimer correctly! managed-arrays managed-floats, and arrays thereof

(def-slot-value-reclaimer 2d-incomplete-painting-actions (value frame)
  (declare (ignore value))
  (clear-incomplete-painting-actions frame))
    

;; display-panes are run-time structures that are created for
;; display objects (currently only trend charts).  They represent
;; a rectangular partition of the display's block for
;; the purposes of layout and mouse tracking.  Display panes
;; contain the structures needed to support the draw methods
;; of a display. If sub-panes exist for a pane, then they partition
;; the area of the parent completely, minus the borders of the parent if any
;; 

(def-structure display-pane
  (display-pane-type   nil)
  (display-pane-left   0)
  (display-pane-top    0)
  (display-pane-width  0)
  (display-pane-height 0)
  (display-pane-background-color 'white)
  (display-pane-border-style? nil) ; nil/'hairline/<integer>
  (display-pane-border-color 'black)
  (display-pane-component-group? nil)
  (display-pane-parent nil)
  (display-pane-sub-panes nil :reclaimer reclaim-slot-value-list))

(defmacro new-display-pane (pane-type parent-expr left top width height)
  (let ((make-name (build-ab-symbol 'make pane-type))
	(parent (gensym)))
    `(let ((new-display-pane
	     (,make-name))
	   (,parent ,parent-expr))
       (setf (display-pane-type new-display-pane) ',pane-type)
       (setf (display-pane-parent new-display-pane) ,parent)
       (setf (display-pane-left new-display-pane) ,left)
       (setf (display-pane-top new-display-pane) ,top)
       (setf (display-pane-width new-display-pane) ,width)
       (setf (display-pane-height new-display-pane) ,height)
       (when ,parent
	 (slot-value-push new-display-pane
			  (display-pane-sub-panes ,parent)))
       new-display-pane)))

(defun reclaim-pane-tree (display-pane)
  (loop for sub-pane in (display-pane-sub-panes display-pane)
	do
          (reclaim-pane-tree sub-pane)
	finally
	  (reclaim-structure display-pane)))

(def-structure (axis-pane (:include display-pane))
  (axis-pane-interval nil :reclaimer reclaim-slot-value)
  (axis-pane-text-color 'black)
  (axis-pane-position 'left)
  (axis-pane-maximum-tickmarks 0)
  (axis-pane-label-height 0)
  (axis-pane-number-format nil)
  (axis-pane-fixed-decimal-offset 0)
  (axis-pane-floating-decimal-offset 0)
  (axis-pane-fixed-left-digits 0)
  (axis-pane-fixed-right-digits 0)
  (axis-pane-currently-has-scientific-notation-p nil)
  (axis-pane-textual-elements nil :reclaimer reclaim-slot-value)
  (axis-pane-base-line-left-offset? nil)
  (axis-pane-base-line-color nil)
  (axis-pane-clip-height nil))

(def-structure (trend-chart-pane (:include display-pane))
  (trend-chart-pane-time-is-on-grid-p t))

(def-structure (legend-pane (:include display-pane))
  (legend-pane-lines nil :reclaimer reclaim-slot-value)
  (legend-pane-interline-spacing nil))

(def-structure (relative-time-pane (:include display-pane))
  (relative-time-label-color nil)
  (relative-time-labels nil :reclaimer reclaim-slot-value)) ; pairs left-offset str

(def-structure (grid-pane (:include display-pane))
  (grid-data-height nil)
  (grid-separator-height nil)
  (grid-label-height nil)
  (grid-end-time-mode nil)
  (grid-timespan nil)                                ; these are not
  (grid-end-time? nil :reclaimer reclaim-slot-value) ; the master slots
  (grid-time-alignment? nil :reclaimer reclaim-slot-value)
  (grid-scroll-timespan? nil :reclaimer reclaim-slot-value)
  (grid-tickmark-interval? nil :reclaimer reclaim-slot-value)
  (grid-label-ratio nil)
  (grid-grid-line-ratio nil)
  (grid-label-interval? nil)
  (grid-time-label-color nil))

(defvar current-display-pane-left)
(defvar current-display-pane-top)
(defvar current-display-pane-right)
(defvar current-display-pane-bottom)
(defvar current-display-pane-height)
(defvar current-display-pane-width)

(defun focus-on-display-pane (display display-pane)
  (let ((display-pane-list '()))
    (loop for pane = display-pane
		   then (display-pane-parent pane)
	  while pane
	  do
      (slot-value-push pane display-pane-list))
    (loop with left = (left-edge-of-block display)
	  with top = (top-edge-of-block display)
	  with right = (right-edge-of-block display)
	  with bottom = (bottom-edge-of-block display)
	  for pane in display-pane-list
	   as border-style? = (display-pane-border-style?
				pane)
	  do
            (incfw left (display-pane-left pane))
	    (incfw top (display-pane-top pane))
	    (setf right (+w left (display-pane-width pane)))
	    (setf bottom (+w top (display-pane-height pane)))
	    (when border-style?
	      (let ((border-width
		      (if (eq border-style? 'hairline) 1 border-style?)))
		(incfw left border-width)
		(incfw top border-width)
		(decfw right border-width)
		(decfw bottom border-width)))
	  finally
	    (reclaim-slot-value-list display-pane-list)
	    (return
	      (values left top right bottom
		      (-w bottom top) (-w right left))))))

(defmacro with-focused-display-pane ((display pane-to-focus-upon) &body body)
  `(multiple-value-bind
       (current-display-pane-left current-display-pane-top
	current-display-pane-right current-display-pane-bottom
        current-display-pane-height current-display-pane-width)
       (focus-on-display-pane ,display ,pane-to-focus-upon)
     ,@body))

(define-slot-alias title trend-chart-label-to-display trend-chart)
(define-slot-alias plots trend-chart-plots trend-chart)
(define-slot-alias value-axes trend-chart-value-axes trend-chart)
(define-slot-alias time-axis trend-chart-time-axis trend-chart)
(define-slot-alias point-formats trend-chart-point-formats trend-chart)
(define-slot-alias connector-formats trend-chart-connector-formats trend-chart)
(define-slot-alias plotting-conditions trend-chart-plotting-conditions trend-chart)

(define-compound-slot-value-writer plot
    trend-chart-plots plot plots)

(define-compound-slot-value-writer time-axis
    trend-chart-time-axis time-axis time-axes)

(define-compound-slot-value-writer trend-chart-format
    trend-chart-format trend-chart-format trend-chart-formats)

(define-compound-slot-value-writer value-axis
    trend-chart-value-axes value-axis value-axes)

(define-compound-slot-value-writer point-format
    trend-chart-point-formats point-format point-formats)

(define-compound-slot-value-writer connector-format
    trend-chart-connector-formats connector-format connector-formats)

(defparameter minimum-data-window-size 20) ; workspace units
(defparameter minimum-data-window-margin 10) ; workspace units
(defparameter default-trend-chart-height 200)
(defparameter default-trend-chart-width  300)
(defparameter maximum-plots-per-trend-chart 20) ; *** must enforce in compiler
(defparameter trend-chart-plot-slot-increment 10)

(add-grammar-rules
  '((fake-conditional-plotting-spec integer))) ; FRIDAY
;    (conditional-plotting-spec
;     (conditional-plotting-binding-list conditional-plotting-condition-list))
;    (conditional-plotting-binding-list
;     )
;    (conditional-plotting-binding
;     )
;    (conditional-plotting-condition-list
;     )
;    (conditional-plotting-condition
;     ('use unique-expression 'for 'the
;      point-or-connector 'of conditional-plotting-plot-reference))
;    (conditional-plotting-plot-reference
;     ('plot integer)
;     (number 2))
;    (conditional-plotting-plot-reference
;     ('the 'plot 'named unreserved-symbol)
;     (name 4))))

;; NOTE: since a 'trend-chart' is not a 'entity', it doesn't have subworkspaces.

(def-class-using-compound-types (trend-chart (item block)
					     (foundation-class trend-chart) define-predicate)
  (frame-flags #.opaque-block-flag)

  ;; User Slots
  (trend-chart-label-to-display
    nil (type free text) vector-slot system)
  (trend-chart-plots
    (compound-type plot multiple at-least-one-element)
    vector-slot system)
  (trend-chart-value-axes
    (compound-type value-axis multiple at-least-one-element)
    vector-slot system)
  (trend-chart-time-axis
    (compound-type time-axis)
    vector-slot system)
  (trend-chart-point-formats
    (compound-type point-format multiple at-least-one-element)
    vector-slot system)
  (trend-chart-connector-formats
    (compound-type connector-format multiple at-least-one-element)
    vector-slot system)
  (trend-chart-format
    (compound-type trend-chart-format)
    vector-slot system)
;  (trend-chart-plotting-conditions
;    nil (type fake-conditional-plotting-spec text) vector-slot system)

  ;; Internal slots
  (trend-chart-update-task? nil vector-slot system)
  (2d-substructure-serial-number 0 vector-slot system save) ; for internal bookkeeping
  (2d-dirty-bit     t   vector-slot system)    ; modified if any values values set
  (2d-image-plane-states nil vector-slot system)    ; contains rendering (which has rasters
                                                    ; and color-values) and state info
  (trend-chart-pane-tree nil vector-slot system)
  ;; Master State
  (trend-chart-plot-maxima nil vector-slot system)
  (trend-chart-plot-minima nil vector-slot system)
  (trend-chart-plot-end-times nil vector-slot system)
  (trend-chart-end-time nil vector-slot system)
  (trend-chart-active-p nil vector-slot system)
  (trend-chart-axis-update-time nil vector-slot system)
  (trend-chart-timespan nil vector-slot system)
  (trend-chart-last-update-time nil vector-slot system)
  (trend-chart-current-update-time nil vector-slot system)
  (trend-chart-most-recent-update-rect nil vector-slot system)
  ;; the next two slots are used for telewindows2 only
  (trend-chart-last-sent-end-time nil vector-slot system)
  (trend-chart-last-sent-timespan nil vector-slot system)
  (trend-chart-plot-slot-count 20 vector-slot system save)
  ;; a now defunct slot that will be retired soon
  (trend-chart-paint-buffer-limit? nil vector-slot system save)
  (trend-chart-representation-task? nil vector-slot system))
;  (trend-chart-plot-condition-indices nil vector-slot system save))

(def-slot-value-reclaimer trend-chart-pane-tree (pane-tree trend-chart)
  (declare (ignore trend-chart))
  (reclaim-pane-tree pane-tree))


(defun trend-chart-component-name (slot-component-group)
  (let ((name-or-names
	  (slot-component-group-name-or-names
	    slot-component-group
	    (component-type slot-component-group))))
    (cond ((consp name-or-names)
	   (car name-or-names))
	  (t
	   name-or-names))))

;;;; Trend Chart Frame Notes

(defparameter trend-chart-component-type-slot-name-map
  '((plot . trend-chart-plots)
    (value-axis . trend-chart-value-axes)
    (time-axis . trend-chart-time-axis)
    (point-format . trend-chart-point-formats)
    (connector-format . trend-chart-connector-formats)
    (trend-chart-format . trend-chart-format)))

(defun add-or-delete-trend-chart-note (trend-chart slot-component-group-or-name
				       note-type add-p)
  ;; when add-p signal operator
  (cond
    ((or (null slot-component-group-or-name)
	 (symbolp slot-component-group-or-name))
     (cond (add-p
	    (add-frame-note note-type trend-chart))
	   (t
	    (delete-frame-note-if-any note-type trend-chart))))
    (t
     (let* ((component-type (component-type slot-component-group-or-name))
	    (indicator (slot-component-group-indicator slot-component-group-or-name))
	    (slot-name (cdr (assoc component-type
				   trend-chart-component-type-slot-name-map))))
       (let ((current-computation-component-particulars
	       (slot-value-list 'slot-component slot-name nil indicator)))
	 (cond
	   (add-p
	    (add-frame-note note-type trend-chart))
	   (t
	    (delete-frame-note-if-any
	      note-type trend-chart)))
	 ;; perhaps issue operator message here indicating frame
	 ;; notes should be checked in table for trend chart
	 (reclaim-slot-value-list 
	   current-computation-component-particulars))))))

(defun delete-all-frame-notes-of-type-from-trend-chart
    (trend-chart type-of-note components-p)
  (cond 
    (components-p
     (delete-frame-note-from-all-component-particulars-of-frame
       type-of-note trend-chart ))
    (t
     (delete-frame-note-if-any type-of-note trend-chart))))

(defun delete-all-frame-notes-of-trend-chart-component-group
    (trend-chart slot-component-group)
  (let* ((component-type (component-type slot-component-group))
	 (indicator (slot-component-group-indicator slot-component-group))
	 (slot-name (cdr (assoc component-type
				trend-chart-component-type-slot-name-map))))
    (let ((current-computation-component-particulars
	    (slot-value-list 'slot-component slot-name nil indicator)))
      (delete-all-frame-notes-for-component-particular
	current-computation-component-particulars
	trend-chart)
      (reclaim-slot-value-list current-computation-component-particulars))))

(def-frame-note-writer defaulting-total-timespan (ignore-me)
  (declare (ignore ignore-me))
  (twrite-string "total timespan not specified -- using maximum age of 1 day"))






;;;; Component Access for Trend Charts





(defun get-multiple-compound-slot-parse-result-header (sequence)
  (loop with res = '()
	for struct being each evaluation-sequence-element of sequence
	for i from 1 by 1
	as names-slot-value? = (evaluation-structure-slot struct 'names)
	do
    (when names-slot-value?
      (let ((primary-name
	      (if (symbolp names-slot-value?)
		  names-slot-value?
		  (evaluation-sequence-aref names-slot-value? 0))))
	(cond ((null primary-name)
	       nil)
	      ((eq primary-name 'default)
	       ;; don't include the default in the index count
	       (decff i))
	      ((reserved-word-p primary-name)
	       (return (values bad-phrase
			       (tformat-text-string
				 "~a is a reserved symbol" primary-name))))
	      (t
	       (phrase-push (phrase-list i primary-name) res)))))
	finally
	  (return (and res
		       (phrase-cons '\, (nreverse res))))))

(defun-simple get-component-group-id-from-structure (struct)
  (let ((name-or-names?
	  (evaluation-structure-slot struct 'names))
	id)
    (cond
      ((symbolp name-or-names?)
       (setf id name-or-names?))
      ((evaluation-sequence-p name-or-names?)
       (evaluation-sequence-aref name-or-names? 0))
      (t
       nil))))
		 


(defun add-triples-for-compound-slot-structure-parse-result (frame struct
							   compound-type-descriptor
							   component-group-id
							   multiple-p)
  ;; loop through struct slots
  ;; 1 converting alias to internal slot-component-names 
  ;; 2 lispifying the slot-value
  ;; 3 completing the triple with a name-or-number doo-hickey
  (let ((class (class frame))
	(compound-type-name (compound-type-name compound-type-descriptor)))
    (loop with parse-result = nil
	  with triples = '()
          for (name . value) being each evaluation-structure-pair of struct
	  as slot-component-name
	     =  (or (get-slot-component-name-for-alias-if-any
		      name class compound-type-name)
		    name)
	  as slot-component-descriptor
	     = (compound-type-slot-if-any compound-type-descriptor slot-component-name)
	  as type-of-slot-component?
	     = (feature-assq 'type (slot-component-features slot-component-descriptor))
	  as category = (and type-of-slot-component?
			     (category-symbol-given-slot-type type-of-slot-component?))
	  when (and type-of-slot-component? ; should this ever be false
		    (not (or (eq name 'names)
			     (eq name 'chart-element-uid))))
	    do
	      (cond
		;; names come in through header
		((text-slot-type-p type-of-slot-component?)
		 (setf parse-result
		       (parse-text-string (evaluation-text-value value) category)))
		((null (evaluation-value-to-category-function category))
		 #+development
		   (error "no setter for category ~a" category)
		   (setf parse-result bad-phrase))
		(t
		 (setf parse-result
		       (call-category-setter category value frame nil nil))))
	      (phrase-push
		(phrase-list
		  slot-component-name
		  parse-result
		  (cond ((eq component-group-id 'default)
			 (phrase-list 'any))
			((symbolp component-group-id)
			 (if multiple-p
			     (phrase-list 'named component-group-id)
			     (phrase-list 'single)))
			(t
			 (phrase-list 'numbered component-group-id))))
		triples)
	  finally
	    (return (nreverse triples)))))

(defun make-evaluation-sequence-from-multiple-compound-slot
    (frame slot-value compound-type-descriptor expand-inherited-slots-p)
  (loop with res = '()
        for slot-component-group
	    in (multiple-compound-slot-value-instances slot-value)
	do
    (eval-push
      (make-evaluation-structure-from-slot-component
	frame slot-component-group compound-type-descriptor expand-inherited-slots-p t)
      res)
	finally
	  (return (allocate-evaluation-sequence (nreverse res)))))


(defun make-evaluation-structure-from-slot-component
    (frame slot-component-group compound-type-descriptor expand-inherited-slots-p multiple-p)
  (loop with indicator = (slot-component-group-indicator slot-component-group)
	with slot-component-name-for-names
	  = (slot-component-name-for-names compound-type-descriptor)
	with reversed-plist = (if multiple-p
				  (eval-list (make-evaluation-value indicator 'integer)
					     'chart-element-uid)
				  '())
	for slot-component-descriptor
	    in (slot-component-descriptors compound-type-descriptor)
	as slot-component-name = (slot-component-name slot-component-descriptor)
	as slot-component-features
	   = (progn ; (describe slot-component-descriptor)
		    (slot-component-features slot-component-descriptor))
	as best-slot-component-name
	   =  (or (slot-component-alias slot-component-name)
		  slot-component-name)
	as type-of-slot-component = (feature-assq 'type slot-component-features)
	as category = (category-symbol-given-slot-type type-of-slot-component)
	as slot-component-indicator?
	   = (slot-component-group-indicator slot-component-group)
	when (and type-of-slot-component
		  (not (eq slot-component-name 'component-type))
;		  (or (not (feature-assq
;			     'do-not-put-in-attribute-tables-if-null
;			     slot-component-features))
;		      slot-component-value)
		  category
		  (or (eq slot-component-name slot-component-name-for-names)
		      (not (feature-assq
			     'not-editable-in-default slot-component-features))
		      (not (eq slot-component-indicator? 'default))))
	  do
	    (let ((non-default-value? 
		    (component-group-slot slot-component-group slot-component-name
					  compound-type-slot-not-present))
		  (add-attribute-to-struct-p t)
		  slot-component-value evaluation-value)
	      (cond
		((eq non-default-value? compound-type-slot-not-present)
		 (cond ((or (eq indicator 'default) ; default-slot-component-group-p
			    expand-inherited-slots-p)
			(setf slot-component-value
			      (compound-type-instance-component-value
				slot-component-group slot-component-name)))
		       (t
			(setf add-attribute-to-struct-p nil))))
		(t
		 (setf slot-component-value non-default-value?)))
	      (when add-attribute-to-struct-p
		;; transform value by category to evaluation-value
		(cond
		  ;; temp hack
		  ((eq category 'name-or-names)
		   (cond
		     (slot-component-value
		      (setf evaluation-value
			    (if (consp slot-component-value)
				(allocate-evaluation-sequence
				  (copy-list-using-eval-conses slot-component-value))
				slot-component-value)))
		     (t
		      (setf add-attribute-to-struct-p nil))))
		  ((text-slot-type-p type-of-slot-component)
		   ;; hacking a special case for expressions because
		   ;; compilation of comp. slot-values does not preserve
		   ;; spacing.  Therefore if the spacing is normallized
		   ;; in the evaluation-value-getter, there is a chance
		   ;; that things will be seen as evaluation-value-= later.
;		   (cond ((memq category '(unique-expression logical-expression))
;			  (setf evaluation-value
;				(tformat-text-string "~NE " (car slot-component-value))))
;			 ;; God save me!
;			 ((eq category 'plot-expression)
;			  (setf evaluation-value
;				(tformat-text-string "~NE " (caar slot-component-value))))
;			 (t
			  (setf evaluation-value 
				(text-slot-value-to-evaluation-text
				  frame slot-component-value type-of-slot-component)))
;		   ))
		  ((null (slot-value-to-evaluation-value-function category))
		   #+development
		   (error "no getter for category ~a" category)
		   (setf evaluation-value evaluation-false-value))
		  ;; text type slot case		
		  (t
		   (setf evaluation-value
			 (call-category-getter category slot-component-value nil nil))
		   ;; if evaluation-value is nil after calling getter,
		   ;; then don't add it to the result
		   (unless evaluation-value
		     (setf add-attribute-to-struct-p nil))))
		(when add-attribute-to-struct-p
		  (eval-push best-slot-component-name reversed-plist)
		  (eval-push evaluation-value reversed-plist))))
	finally
	  (return
	    (allocate-evaluation-structure (nreverse reversed-plist)))))



(defun set-tracing-and-breakpoints-for-trend-chart (block new-value)
  (loop for slot-component-group
	    in (multiple-compound-slot-value-real-instances
		 (trend-chart-plots block))
	for indicator = (slot-component-group-indicator slot-component-group)
	unless (eq (get-slot-component-value-if-any
		     block 'trend-chart-plots nil
		     'plot-tracing-and-breakpoints indicator)
		   new-value)
	  do (change-slot-value block 'trend-chart-plots new-value nil
				'plot-tracing-and-breakpoints indicator)))

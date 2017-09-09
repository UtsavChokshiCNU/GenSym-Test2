;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module GRAMMAR6C

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Paul B. Konigsberg, Michael Levin, and Mark H. David, et al

;; This file was split off from GRAMMAR6B. It contains the icon description
;; grammar, compiler, and writer, as well as the category evaluator interface. I
;; didn't bother removing any forward references, just copied the whole lot from
;; '6B. (MHD 12/11/96)

(declare-forward-references-to-module
  grammar7
  ;write-data-server-map-from-slot
  ;compile-data-server-map-for-slot
  ;compile-display-expression-for-slot
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
  write-type-in-box-format?-from-slot)

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
  compile-gsi-variable-grouping-specification-for-slot
  write-gsi-variable-grouping-specification-from-slot
  compile-attributes-which-identify-a-network-item-reference-for-slot
  write-attributes-which-identify-a-network-item-reference-from-slot
  write-options-for-item-reference-from-slot
  compile-options-for-item-reference-for-slot
  compile-timeout-interval-or-default-for-slot
  write-timeout-interval-or-default-from-slot)

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


;;;; Icon Description Grammar, Compiler, and Writer



(add-grammar-rules			; grammar for line drawing
  '((point ( '\( point-expression '\, point-expression '\) ) (2 4))
    (arc-point ('arc '\( point-expression '\, point-expression '\) ) (arc (3 5)))    
    
    (points point)
    (points (points point))

    (line-drawing-element ('point point))
    (line-drawing-element ('circle point point point))
    
    (line-drawing-element ('filled 'rectangle point point)
     (SOLID-RECTANGLE 3 4))
    
    (line-drawing-element ('filled 'circle point point point)
     (FILLED-CIRCLE 3 4 5))
    
    (line-drawing-element ('lines lines-point-tree)
     (LINES . 2))
    (line-drawing-element ('outline outline-point-tree)
     (OUTLINE . 2))
    (line-drawing-element ('filled 'polygon filled-polygon-point-tree)
     (FILLED-POLYGON . 3))

    ;; Stippled area added. -mhd 3/13/01
    (line-drawing-element stipple-line-drawing-element)
    (stipple-line-drawing-element ('stippled 'area stipple)
     (STIPPLED-AREA 3))			; implies entire area
    (stipple-line-drawing-element ('stippled 'area stipple point point)
     (STIPPLED-AREA 3 4 5))
    
      ; Added -pbk 1/11/95
    (line-drawing-element text-drawing-element)
    (icon-font-symbol 'small)
    (icon-font-symbol 'large)
    (icon-font-symbol 'extra-large)
    
    (icon-font-symbol-or-variable icon-font-symbol)
    (icon-font-symbol-or-variable unreserved-symbol)
    
    ;; Added -fmw, 12/21/93
    (line-drawing-element image-drawing-element)

    (icon-description? 'inherited)
    (icon-description? 
     ('width positive-integer '\;
      'height positive-integer '\;
      icon-description-header-and-body)
     (2 5 . 7))

    (icon-description-header-and-body
     icon-description-header-and-body-2)
    (icon-description-header-and-body
     (region-specification-list '\;
      icon-description-header-and-body-2)
     ((polychrome . 1) . 3))

    (icon-description-header-and-body-2
     icon-description-header-and-body-3)
    (icon-description-header-and-body-2
     (variable-specification-list '\;
      icon-description-header-and-body-3)
     ((variables . 1) . 3))

    (icon-description-header-and-body-3
     icon-description-header-and-body-4)
    (icon-description-header-and-body-3
     (icon-background-layer-element '\;
      icon-description-header-and-body-4)
     ((background-layer . 1) . 3))

    (icon-description-header-and-body-4
     label-and-element-list)
    (icon-description-header-and-body-4
     ('stipple '\: stipple '\;
      label-and-element-list)
     ((stipple 3) . 5))
    
    (icon-background-layer-element
     ('icon-background-layer '\: 'color background-image-drawing-element)
     (4))

    (icon-background-layer-element
     ('icon-background-layer '\: color-or-metacolor)
     (3))
    
    (label-and-element-list			; => (\; {E})
      (line-drawing-element
	'\; label-and-element-list)
      (2 1 3)
      simplify-associative-operation)
    (label-and-element-list			; => (\; L {E})
      (region-or-color-or-metacolor
	'\:
	line-drawing-element '\;
	label-and-element-list)
      (4 1 3 5)
      simplify-last-of-nary-associative-operator)
    (label-and-element-list			; => (\; L E)
      (region-or-color-or-metacolor '\: line-drawing-element)
      (\; 1 3))
    (label-and-element-list			; => E
      line-drawing-element)
    
      ; pbk added variables to icon-descriptions
    (variable-specification-list ('variables '\:  variable-specification-list-1)
     3 variable-spec-transform)  

    (variable-specification-list-1
     variable-specification
     (\, 1))
    
    (variable-specification-list-1
      (variable-specification '\, variable-specification-list-1)
     (2 1 3)
     simplify-associative-operation)
    
    (variable-name unreserved-symbol) 
    
    (variable-specification (variable-name '= integer) (1 3))  ; points
    (variable-specification (variable-name '= whole-string) (1 3)) ;text-drawing-element
    (variable-specification (variable-name '= icon-font-symbol) (1 3)) ;text-drawing-element
    (variable-specification (variable-name '= image-name) (1 3)) ;image-drawing-element
;    (variable-type positive-integer)

    
    (region-specification-list region-specification-list-1 1 cdr)
    
    (region-specification-list-1
      region-specification
      (\, 1))
    (region-specification-list-1
      (region-specification '\, region-specification-list-1)
      (2 1 3)
      simplify-associative-operation)
    
    (region-specification (region '= color-or-metacolor) (1 . 3))))


(def-grammar-category stipple ()
  . #.all-stipples)


  

;;; The grammar rules for `lines-point-tree', `outline-point-tree', and
;;; `fill-polygon-point-tree' define the grammar for the points (and arc
;;; points) that follow the LINES, OUTLINE, and FILLED POLYGON directives,
;;; respectively.
;;;
;;; This grammar is new for 4.0 [introduced 7/13/94].  While it is the same
;;; on the surface, it parses into a quite different result, and is used very
;;; differently than the previous grammar at this level.
;;;
;;; The phrase that results from of a parse of these three categories is a
;;; point tree.  A `point tree' is a phrase of the form
;;;
;;;   constant-point-or-arc
;;;
;;; or
;;;
;;;   (point-tree constant-point-or-arc)
;;;
;;; where constant-point-or-arc is either an arc point, i.e., (ARC (x y)), or a
;;; point, i.e., (x y), where x and y are integers.  Note that computed points
;;; (or computed arc points) are not handled at present.
;;;
;;; Note that the grammar may impose certain surface restrictions, e.g., where
;;; arc points may or may not be allowed, and how many points are required.
;;;
;;; A point tree is readily converted into a flat list of points, in their
;;; proper order, i.e., the order in which they were entered, by listing the
;;; constant-point-or-arc elements visited in the order in which they are
;;; encountered in a depth-first, left-to-right traversal of the point tree.
;;;
;;; Point trees are much more efficient to maintain for large numbers of points
;;; because they do not have to be created via transormations, with associated
;;; phrase-consing costs, after reading each token.  Instead of converting
;;; tokens parsed into flat lists as they are parsed, that process can be
;;; deferred until compilation time, which is the first time at which it
;;; really needs to be done.
;;;
;;; The function `flatten-point-tree-phrase-into-list' takes a point tree phrase
;;; and returns it as a flat list, with elements in their proper order.  The
;;; resulting list contains entirely new phrase conses.  This is intended to be
;;; called in the compiler.

(add-grammar-rules
  ;; {point}+ {{arc-point}? {point}+}+ => lines-point-tree
  '((lines-point-tree points)
    (lines-point-tree lines-point-arc-tree)
    (lines-point-arc-tree-leader (points arc-point))
    (lines-point-arc-tree-leader (lines-point-arc-tree arc-point))
    (lines-point-arc-tree (lines-point-arc-tree-leader point))
    (lines-point-arc-tree (lines-point-arc-tree point))))

(add-grammar-rules
  ;; {point}+ {{arc-point}? {point}+}+ => outline-point-tree
  '((outline-point-tree points)
    (outline-point-tree outline-point-arc-tree)
    (outline-point-arc-tree-leader (points arc-point))
    (outline-point-arc-tree-leader (outline-point-arc-tree arc-point))
    (outline-point-arc-tree (outline-point-arc-tree-leader point))
    (outline-point-arc-tree (outline-point-arc-tree point))))

(add-grammar-rules
  ;; {point}+ point point    => point-tree
  '((filled-polygon-point-tree (filled-polygon-point-tree-1 point))
    (filled-polygon-point-tree-1 (filled-polygon-point-tree-2 point))
    (filled-polygon-point-tree-2 point)
    (filled-polygon-point-tree-2 (filled-polygon-point-tree-2 point))))


(defun flatten-point-tree-phrase-into-list (point-tree)
  (nreverse-canonically (flatten-point-tree-phrase-into-reverse-list point-tree)))

(defun flatten-point-tree-phrase-into-reverse-list (point-tree)
  (if (or (and (arc-point-p point-tree)
	       (constant-point-p (cadr point-tree)))
	  (constant-point-p point-tree)
	  (power-point-p point-tree)) 
      
      (phrase-list point-tree)
      (phrase-cons
	(second point-tree)
	(flatten-point-tree-phrase-into-reverse-list (car point-tree)))))

(def-copy-tree-including-leaves-using-x-conses phrase)

;;; `point-tree-phrase'
;;; Returns a tree of new phrase cons that must be reclaimed by the caller

(defun point-tree-phrase (points)
  (cond ((eq (length points) 1)
	 (copy-tree-including-leaves-using-phrase-conses (car points)))
	(t
	 (loop with result
		 = (phrase-list
		     (copy-tree-including-leaves-using-phrase-conses
		       (car points))
		     (copy-tree-including-leaves-using-phrase-conses
		       (cadr points)))
	       for point in (cddr points)
	       do
	   (setf result
		 (phrase-list
		   result
		   (copy-tree-including-leaves-using-phrase-conses
		     point)))
	       finally
		 (return result)))))
	
;; NOTE: this has only been developed to handle constant points and constant arc
;; points; if computed points are handled, as planned and as suggested by the
;; code and comments below, this must be reviewed.



;; For now:

(add-grammar-rules			; Point-expression grammar
  '((point-expression point-factor)
    (point-factor integer)
    (point-factor unreserved-symbol))) ;pbk power points



;; For later:  (MHD 5/26/94)

(add-grammar-rules                      ; Point-expression grammar
  '((point-expression point-sum)
    (point-sum point-term-or-signed-point-term)
    (point-sum (point-term-or-signed-point-term signed-point-sum) (+ 1 2))
   
    (signed-point-sum signed-point-term)
    (signed-point-sum (signed-point-term signed-point-sum) (+ 1 2))
    
    (point-term-or-signed-point-term point-term)
    (point-term-or-signed-point-term signed-point-term)
   
    (signed-point-term ('+ point-term) 2)
    (signed-point-term ('- point-term))
   
    (point-term point-factor)
;;    (point-term (point-factor '* point-term) (2 1 3) simplify-associative-operation)
;;   (point-term (point-factor '/ point-term) (2 1 3) simplify-associative-operation)
    (point-factor ('\( point-expression '\)) 2)))
   
;    (point-factor 'width)
;    (point-factor 'height)
;    (point-factor integer)))
     
  


(def-grammar-category image-name ()
  (unreserved-symbol))

(def-grammar-category image-name? ()
  (image-name)
  ('none nil))

(def-grammar-category image-specification ()
  (image-name (image 1))
  ((image-name 'at point) (image 1 3)))

(def-grammar-category image-specification? ()
  (image-specification)
  ('none nil))

(def-grammar-category image-drawing-element ()
  (('image image-specification) 2))




(add-grammar-rules			
  '((static-point ( '\( integer '\, integer '\) ) (2 4))))
  
(def-grammar-category background-image-specification ()
  (image-name (image 1))
  ((image-name 'at static-point) (image 1 3)))

(def-grammar-category background-image-drawing-element ()
  (('image background-image-specification) 2))




(def-substitution-macro write-image-specification (spec)
  ;; nil or (image <name> <point>)
  (cond ((null spec)
	 (twrite-string "none"))
	((atom spec)					    ; An error
	 (twrite spec))
	(t
	 (tformat "~(~a~)" (second spec))
	 (when (third spec)
	   (tformat " at ")
	   (write-point (third spec))))))


#+text-element-reflection-rotation
(def-grammar-category icon-rotation-and-reflection ()
  (('rotated '90-degrees-clockwise)
    clockwise-90)
  (('rotated '90-degrees-counterclockwise)
    clockwise-270)
  (('rotated '180-degrees)
   clockwise-180)
  
  (('reflected 'left-right)
   reflected)
  (('reflected 'up-down)
   reflected-clockwise-180)
  
  (('rotated '90-degrees-clockwise 'reflected 'left-right)
   reflected-clockwise-270)
  (('rotated '90-degrees-counterclockwise 'reflected 'left-right)
   reflected-clockwise-90)
  (('rotated '180-degrees 'reflected 'left-right)
   reflected-clockwise-180)
  
 (('rotated '90-degrees-clockwise 'reflected 'up-down)
   reflected-clockwise-90)
  (('rotated '90-degrees-counterclockwise 'reflected 'up-down)
   reflected-clockwise-270)
  (('rotated '180-degrees 'reflected 'up-down)
   reflected)
  
  (('reflected 'left-right 'rotated '90-degrees-clockwise)
   reflected-clockwise-270)
  (('reflected 'left-right 'rotated '90-degrees-counterclockwise)
   reflected-clockwise-90)
  (('reflected 'left-right 'rotated '180-degrees)
   reflected-clockwise-180)
  
  (('reflected 'up-down rotated '90-degrees-clockwise)
   reflected-clockwise-90)
  (('reflected 'up-down 'rotated '90-degrees-counterclockwise)
   reflected-clockwise-270)
  (('reflected 'up-down 'rotated '180-degrees)
   reflected)
  ('none nil)) ;; need a better solution for nil case


(def-grammar-category text-specification ()
  ((whole-string 'at point 'in icon-font-symbol-or-variable)
     (TEXT 1 3 5))
  ((unreserved-symbol 'at point 'in icon-font-symbol-or-variable)
     (TEXT 1 3 5)))

#+text-element-reflection-rotation
(def-grammar-category text-specification ()
  ((unreserved-symbol 'at point 'in icon-font-symbol-or-variable icon-rotation-and-reflection)
     (TEXT 1 3 5 6)))

(def-grammar-category text-specification? ()
  (text-specification)
  ('none nil))
    
(def-grammar-category text-drawing-element()
  (('text text-specification) 2))

(defun write-text-specification-for-icon-editor-table-info-frame (spec)
  ;; nil or (text <whole-string> at <point> in <font-spec>)
   (let* ((text-box-format-name 'statement-format)
	 (text-box-format (get-or-make-format-frame-function text-box-format-name))
	 (text-string (twith-output-to-text-string
			(write-text-specification spec))) ; ?? is this a copy or not???
	 (text-within-region
	   (convert-text-string-to-text-within-region   ; this reclaims the text arg
	       text-string 360 100
	     text-box-format nil))
	 (clipped-text-string ; this is a copy and it does not reclaim
	   (convert-text-to-text-string text-within-region)))
    (tformat "~a" clipped-text-string)
;    (reclaim-text-string text-string)
    (reclaim-text text-within-region)
    (reclaim-text-string clipped-text-string)))

#+text-element-reflection-rotation
(defun write-icon-rotation-and-reflection (reflection-and-rotation)
  (case reflection-and-rotation
    (clockwise-90 (tformat "rotated 90-degrees-clockwise"))
    (clockwise-270 (tformat "rotated 90-degrees-counterclockwise"))
    (clockwise-180 (tformat "rotated 180-degrees"))
    
    (reflected (tformat "reflected left-right"))
    ;; OR (('rotated '180-degrees 'reflected 'up-down)
    
    (reflected-clockwise-90
     (tformat "rotated 90-degrees-counterclockwise reflected left-right"))
    ;; OR (('rotated '90-degrees-clockwise 'reflected 'up-down)

    (reflected-clockwise-180 (tformat "reflected up-down"))
    ;; OR (('rotated '180-degrees 'reflected 'left-right)

    (reflected-clockwise-270 (tformat "rotated 90-degrees-clockwise reflected left-right"))
    ;; OR (('rotated '90-degrees-counterclockwise 'reflected 'up-down)
    ))
  
 
(defun write-text-specification  (spec)    ;pbk
  ;; nil or (text <whole-string> at <point> in <font-spec>)
  (cond ((null spec)
	 (twrite-string "none"))
;	((atom spec)					    ; An error
;	 (twrite spec))
	(t
	 (cond ((symbolp (second spec))
		(twrite-symbol (second spec)))
	       (t (tformat " \"~a\" " (second spec))))
	 (tformat "~%")  ; want to wrap the last line (do this for now)
	 (tformat " at ")
	 (write-point (third spec))
	 (tformat " in ")
	 (tformat " ~(~a~) " (fourth spec))
	 #+text-element-reflection-rotation
	 (write-icon-rotation-and-reflection (fifth spec))
	 )))



(def-grammar-category global-stipple-specification? () ;
  (stipple)
  ('none nil))

(def-grammar-category stipple-specification? ()
  (stipple
   (STIPPLED-AREA 1))
  ((stipple point point)
   (STIPPLED-AREA 1 2 3))
  ('none nil))

(def-slot-value-writer global-stipple-specification? (value)
  (write-stipple-specification value))


(def-slot-value-writer stipple-specification? (value)
  (write-stipple-specification value))



(defun write-stipple-specification-for-icon-editor-table-info-frame (spec)
  ;; Handles both global and non-global specs.
  ;; nil or <stipple>
  ;;   or (for non-global specs)
  ;;   (STIPPLED-AREA <stipple> top-left-corner-as-point bottom-right-corner-as-point)
  (write-stipple-specification spec))

(defun write-stipple-specification (spec)
  (cond
    ((null spec)
     (twrite-string "none"))
    ((atom spec)
     (tformat "~(~a~)" spec))
    (t
     (tformat "~(~a~)" (second spec))
     (if (cddr spec)
	 (tformat " (~d, ~d) (~d, ~d)"
		  (point-x (third spec)) (point-y (third spec))
		  (point-x (fourth spec)) (point-y (fourth spec)))))))

			     



   


(def-slot-value-writer-as-existing-function image-name? write-symbol-from-slot)
(def-slot-value-writer-as-existing-function image-name write-symbol-from-slot)


(def-slot-value-compiler image-name? (parse-result)
  (if (eq parse-result 'none)
      nil
      parse-result))

(def-slot-value-writer image-specification? (image-specification?)
  (write-image-specification image-specification?))


;; This is used to write into the table within the icon-editor that displays
;; the text of the current layer.  This writer performs text clipping in the
;; cases when the text gets "too large".

(def-slot-value-writer text-specification? (text-specification?) ;pbk
  (write-text-specification-for-icon-editor-table-info-frame
    text-specification?))





(defun fix-line-list (x)
  (phrase-cons (car x) (cddr x)))

;; still used in GRAMMAR4




;(defparameter g2-color
; defconstant?!
;	      '(white red orange yellow green blue purple black
;		      brown light-gray gray dark-gray))

;(defparameter g2-metacolors			; defconstant?!
;	      '(transparent foreground default))

;(defun color-or-metacolor-p (thing)
;  (or (color-p thing)
;      (metacolor-p thing)))

;(defun color-p (thing)
;  (memq thing g2-colors))

;(defun metacolor-p (thing)
;  (memq thing g2-metacolors))

;;; Move elsewhere?!

;;; Document!

;;; Make these macros?!

;; Added.  (MHD 7/31/89)

;;; The above replaced by ML with a usage of the new facility semi open category.

(defmacro def-semi-open-category-color ()
  `(def-semi-open-category color
     . ,(loop for (color) in standard-gensym-color-alist
	      collect color)))

;; THE CALL TO THE ABOVE MACRO IS TOO SLOW TO EXECUTE AND CONSUMES TOO MUCH 
;; SPACE!!  FIX!!  (MHD 1/6/90)

(def-semi-open-category-color)

(def-semi-open-category metacolor
  transparent foreground)			; add DEFAULT?


;; ([meta]color-p symbol) replaced with
;; (semi-open-category-p symbol '<[meta]color | (color metacolor)>) in all occurances. 

(defun point-expression-contains-bad-variable-p
    (point-expression variable-spec-list)
  (cond ((null point-expression)
	 nil)
	((integerp point-expression)
	 nil)
	((or (eq point-expression '+) (eq point-expression '-))
	 nil)
	((symbolp point-expression)
	 (cond ((memq point-expression '(width height))
		nil)
	       (t
		(let ((value? (getfq variable-spec-list point-expression)))
		  (or (and (null value?)
			   (gensym-list #w"is undefined" point-expression))
		      (and (not (integerp value?))
			   (gensym-list #w"is not an integer" point-expression)))))))
	((consp point-expression)
	 (or (point-expression-contains-bad-variable-p
	       (car-of-cons point-expression)
	       variable-spec-list)
	     (point-expression-contains-bad-variable-p
	       (cdr-of-cons point-expression)
	       variable-spec-list)))))
		 	
(defun point-contains-bad-variable-p
    (point variable-specification?)
  (cond ((arc-point-p point)
	 (point-contains-bad-variable-p (second-of-cons point)
					variable-specification?))
	((constant-point-p point)
	 nil)
	((power-point-p point)
	 (or (point-expression-contains-bad-variable-p
	       (car-of-cons point) variable-specification?)
	     (point-expression-contains-bad-variable-p
	       (second-of-cons point) variable-specification?)))
	((button-point-p point)
	 ;; buttons contain point-expressions of the form
	 ;; (- width 2) while power-point are stored solely as
	 ;; sums of positive or negative terms, ie (+ width (- 2))
	 ;; someone should unify buttons with the new model
	 nil)
	(t ; this should be a hard error
	 (let ((error-string
		 (twith-output-to-text-string
		   (tformat " contains an invalid point. Report the problem to Gensym.~% "))))
	   #+development
	   (cerror "continue as in production" "Invalid point specification ~s"  point)
	   (gensym-list
	     error-string
	     nil)))))
	 

(defun points-contain-bad-variable-p
    (list-of-points variable-specification)
  (loop for point in list-of-points
	thereis
	(point-contains-bad-variable-p
	  point variable-specification)))

(defun text-drawing-element-label-contains-bad-variable-p
    (label variable-spec-list)
  (cond ((text-string-p label)
	 nil)
	(t
	 (or (and (null (getfq variable-spec-list label))
		  (gensym-list #w"is undefined" label))
	     (and (not (text-string-p (getfq variable-spec-list label)))
		  (gensym-list #w"is not a string" label))))))

(defun text-drawing-element-fontsize-contains-bad-variable-p
    (font-or-variable variable-spec-list)
  (cond ((memq font-or-variable '(small large extra-large))
	 nil)
	(t
	 (let ((font (getfq variable-spec-list font-or-variable)))
	   (or (and (null font)
		    (gensym-list #w"is undefined" font-or-variable))
	       (and (not (memq font '(small large extra-large)))
		    (gensym-list #w"is not a valid font" font-or-variable)))))))

(defun image-drawing-element-image-name-contains-bad-variable-p
    (image-name variable-spec-list)
  (cond ((integerp (getfq variable-spec-list image-name))
	 (gensym-list #w"has an integer value instead of a symbol naming an image-definition"
		      image-name))
	((text-string-p (getfq variable-spec-list image-name))
	 (gensym-list #w"has a string value instead of a symbol naming an image-definition"
		      image-name))
	(t nil)))
  
(defun element-contains-bad-variable?
    (element variable-spec-list)
  (cond ((not (consp element)) nil)
	((text-drawing-element-p element)
	 (or (text-drawing-element-label-contains-bad-variable-p
	       (second element) variable-spec-list)
	     (point-contains-bad-variable-p (third element)
					    variable-spec-list)
	     (text-drawing-element-fontsize-contains-bad-variable-p
	       (fourth element) variable-spec-list)))
	((image-drawing-element-p element)
	 (or (image-drawing-element-image-name-contains-bad-variable-p
	       (second element) variable-spec-list)
	     (and (third element)
		  (point-contains-bad-variable-p (third element)
						 variable-spec-list))))
	((eq (first element) 'SOLID-RECTANGLE)
	 (or (point-contains-bad-variable-p (second element)
						  variable-spec-list)
	     (point-contains-bad-variable-p (third element)
						  variable-spec-list)))
	((eq (first element) 'FILLED-CIRCLE)
	 (or (point-contains-bad-variable-p (second element)
						  variable-spec-list)
	     (point-contains-bad-variable-p (third element)
						  variable-spec-list)
	     (point-contains-bad-variable-p (fourth element)
						  variable-spec-list)))
	((eq (first element) 'stippled-area)
	 (if (cddr element)
	     (points-contain-bad-variable-p
	       (cddr element) variable-spec-list)))
	((eq (first element) 'filled-polygon)
	 (cond ((>f (length (second element)) 2)
		(points-contain-bad-variable-p
		  (second element) variable-spec-list))
	       (t
		(points-contain-bad-variable-p
		  (cdr element) variable-spec-list))))
	(t ; lines  point circle outline
	 (points-contain-bad-variable-p
	   (cdr element) variable-spec-list))))
		
;;;
;;; A `region specification' is a cons of the form
;;;
;;;   (POLYCHROME . region-specification-list)
;;;

;;; A `region specification list' is a list of the form
;;;
;;;   ( { (region . color-or-metacolor) } )
;;;
;;; where each entry contains a region that is not specified by any other
;;; entry.

;;; A `label' in an icon description is either a region, a metacolor, or a
;;; color.  It is followed by one or more line drawing elements and marks
;;; the start of new layer in the drawing.

;;; A line drawing element in an icon description is sometimes referred
;;; to simply as an `element'.

;;; Note that a region specification header differs from a "polychrome header"
;;; (q.v. in ENTITIES) in that the latter has
;;;
;;;     (color-or-metacolor . color-or-metacolor)
;;;
;;; to match those elements among the description elements that are not regions,
;;; but rather are colors or metacolors.  That is, a region specification header
;;; has elements one to one with the named regions of an icon, whereas
;;; a polychrome header has elements one to one with the layers of a polychrome
;;; icon.

;;; The slot value compiler returns a list of the form
;;;
;;;    (<width> <height> . line-drawing-description)
;;;
;;; Note that the car of line-drawing-description may be a polychrome header.
;;; Note also that line-drawing-description must undergo validity checking via
;;; valid-line-drawing-description-p.   Note, however, that some validity checking,
;;; in particular for polygon directives, is done here.





;;; `bad-variable-in-element-message-string'
;;; Returns a new string of the following format:
;;;  "The <bad-element> [<verb> the local variable <variable-name>
;;;   [ = <variable-value?>]], which <reason-for-rejection>."
;;; An example might be the following:
;;;  "The text "text-label" at (FOO,5) in large contains the local variable
;;;   FOO = "some-text", which is not an integer."

(defun bad-variable-in-element-message-string
    (bad-element verb variable-name variable-value? reason-for-rejection)
  (twith-output-to-text-string
    (tformat "~% The ")
    (write-drawing-element
      (if (eq (car bad-element) 'filled-polygon)
	  (phrase-list 'filled-polygon (cdr bad-element))
	  bad-element))
    (when variable-name
      (tformat "~%")
      (twrite-string verb)
      (tformat " the local variable ~s"
	        variable-name)
      (when variable-value?  (tformat " = ~s" variable-value?))
      (twrite-string ", which "))
    (twrite-string reason-for-rejection)
    (twrite-string ".")))

(defun bad-variable-in-element-message
    (bad-element variable-name variable-value? reason-for-rejection)
  (values bad-phrase
	  (bad-variable-in-element-message-string
	    bad-element #w"contains" variable-name variable-value? reason-for-rejection)))


(defparameter reserved-icon-variable-names '(width height small large extra-large))

(defmacro reserved-icon-variable-name-p (variable-name)
  `(memq ,variable-name reserved-icon-variable-names))

(defun reserved-icon-variable-message (bad-variable-name?)
  (values
    bad-phrase
    (twith-output-to-text-string
      (tformat "~s is a reserved icon variable name.~%" bad-variable-name?)
      (tformat "The reserved icon variable names are ~%")
      (loop for (name next? next-next?) on reserved-icon-variable-names
	    do
	(unless next?
	  (twrite " and "))
	(twrite-symbol name)
	(when next-next?
	  (twrite ", ")))
      (twrite "."))))




;; Notes from the suggestion: 6.0 Customer support reported, "this suggestion
;; has been filed as a result of issue HQ-3798540 and HQ-3805223.  Bottomline:
;; The documentation clearly states an upper limit of 1000, however, because of
;; a 5.0 bug the customer was able to exceed the upper limit. Now they want to
;; keep their current 5000 upper limit.
;;
;; MHD replied: We should raise it to 5000x5000.  It's compatible with what we
;; used to do, spec or not, and this will help avoid compatibility issues, and
;; also because the old limit matched radically slower machines with much lower
;; memory than we commonly encounter these days.
;;
;; The change that resulted in the 1000 limit being enforced was for bug
;; HQ-1380760 "Power icon does not limit size of icon"; previously, the checking
;; was done for regular icon edits, but just not for programmatic changes to
;; icons using "power icon" features.  (MHD 2/22/01)


;; The previous limit of 5000 was somewhat arbitrary. The constraints are:

;;  (1) 16-bit drawing coordinates on X Windows (and Windows 98)
;;  (2) most-positive-fixnum in intermediate computations (addressed in this commit)
;;  (3) available bitmap memory (120-300?MB on Win2K/NT/XP, ? on X Windows).

;; We aren't doing anything about the first constraint. There have always been
;; drawing problems on X for very large icons or connections, and this commit
;; does not make the problem any worse. See HQ-4552308 and HQ-4308342.

;; CTC needs one dimension to be as large as 64000. This works on Windows
;; NT/2K/XP platforms which have 32-bit coordinates for drawing. We need icon
;; coordinates, when scaled up by 64x, to not exceed most-positive-fixnum, which
;; means 2^29/64-1 = 8388607. We conservatively choose a round number of 100000.

;; We ought to be able to go much higher in one dimension, but
;; `compute-tile-size-given-required-area' yields 400x400 tiles when one
;; dimension is much larger than the other. Because of this I could not even
;; create a 1x1000000 one layer icon on my 512MB Win2K machine without causing
;; an abort, since G2 was actually allocating enough space for a 400x1000000
;; icon.

;; We aren't doing anything yet about constraint (3). The limit on Windows is
;; the maximum pageable kernel memory size, described in MSDN knowledge base
;; entry Q126402.  My 512MB Win2K machine actually chokes at around 160MB
;; according to task manager, after starting from 40MB, so G2 was able to get
;; only 120MB before aborting. This has been a problem even with the previous
;; max icon size of 5000. Raising it to 100000 just makes it easier to reach the
;; abort. To be addressed in another commit.

;; We choose a maximum icon area somewhat arbitrarily. 40E6 is chosen so that
;; you can create a 400x100000 icon, which fits nicely with our maximum tile
;; size of 400. For an icon that size, each layer requires 5MB. In fact, a
;; 1x100000 icon uses the same amount of space as a 400x100000 icon.

;; -fmw, 4/25/03


;;; The function `check-icon-size' returns a newly consed error string if the
;;; given width and height are not allowed, otherwise NIL.

(defun check-icon-size (width height)
  (cond ((or (<f width 1) (<f height 1))
	 (tformat-text-string "Width and height must be a positive integer."))
	((or (>f width max-icon-size) (>f height max-icon-size))
	 (tformat-text-string
	   "Width and height must be less than or equal to ~d." max-icon-size))
	((with-temporary-gensym-float-creation check-icon-size
	   (> (* (coerce-to-gensym-float width)
		 (coerce-to-gensym-float height))
	      (coerce-to-gensym-float max-icon-area)))
	 (tformat-text-string
	   "The product of width and height must be less than or equal to ~d."
	   max-icon-area))))

	
(def-slot-value-compiler icon-description? (parse-result item)
  (unless (class-definition-defines-user-editable-icon-class-p item)
    (return-from compile-icon-description?-for-slot
      (values bad-phrase
	      (tformat-text-string
		"Cannot change the icon-description of ~NF.  The value ~
                 of the direct-superior-classes attribute on the ~
                 class-definition does not indicate that the class has a ~
                 changeable icon-description." item))))
  (case parse-result
    ((inherited nil) nil)
    (t (let* ((width (first parse-result))
	      (height (second parse-result))
	      (rest (cddr parse-result))
	      (region-specification?
		(if (and (consp (car rest)) (eq (caar rest) 'polychrome))
		    (let ((unfixed-region-specification-list (car rest)))
		      ;; If there is one color, the form may be
		      ;;   (polychrome red . red) or
		      ;;   (polychrome |,| (border . red))
		      ;; otherwise the form is:
		      ;; (polychrome . list-of-elts.)
		      (cond
			((not (true-non-empty-list-p unfixed-region-specification-list))
			 (phrase-list 'polychrome (cdr unfixed-region-specification-list)))
			
			((symbolp (second unfixed-region-specification-list))
			 (phrase-cons 'polychrome (cddr unfixed-region-specification-list)))
			
			(t unfixed-region-specification-list)))))
	      (variable-specification?
		(get-variable-specification-if-any rest))
	      (icon-background-layer?
		(get-icon-background-layer-if-any rest))
	      (icon-background-layer-spec?
		(second icon-background-layer?))	      
	      (stipple? (get-icon-stipple-if-any rest))
	      (unfixed-element-list		; either (\; {L|E}) or E
		(get-element-list rest
				  region-specification?
				  variable-specification?
				  icon-background-layer?
				  stipple?)) 
	      (element-list 
		(let ((element-list-1
			(if (eq (car unfixed-element-list) '\;)
			    (cdr unfixed-element-list)
			    (phrase-list unfixed-element-list))))
		  ;; do the flattening of the points in certain elements --
		  ;; this used to be done in the transformations, but that was
		  ;; too expensive for long lists of points! (MHD 7/13/94)
		  (normalize-line-drawing-elements-from-parse element-list-1)))
	      (bad-background-layer?
		(when (and (symbolp icon-background-layer-spec?)
			   (not (color-or-metacolor-p icon-background-layer-spec?))
			   (or (null region-specification?)
			       (null (assq icon-background-layer-spec?
					   (cdr region-specification?)))))
		  icon-background-layer-spec?))
	      (bad-variable-name?
		(loop with variable-spec-list
		      = (cdr variable-specification?)
		      for (name value) on variable-spec-list by 'cddr
		      as bad-name?
			 = (reserved-icon-variable-name-p name)
		      thereis
		      (when bad-name?
			name)))
	      (bad-variable-in-element?
		(loop with variable-spec-list
		      = (cdr variable-specification?)
		      for element in element-list
		      as bad-variable? 
			 = (element-contains-bad-variable?
			     element
			     variable-spec-list)
		      thereis
		      (when bad-variable?
			(gensym-list bad-variable? element)))) ;pbk leak?
	      (bad-polygon?			; Why is this here instead of in
		(unless bad-variable-in-element?
		  (loop for element		;   valid-line-drawing-
			    in element-list	;   description-p ?!!! (MHD)
			thereis			; Next pass: FIX!
			(when (and (consp element)
				   (eq (car element) 'filled-polygon))
			  (cond ((not (evaluating-icon-elements
					(width height (cdr variable-specification?) nil)
					(simple-polygon-p (cdr element))))
				 (gensym-list element 'not-simple-polygon))
				((>f (length (cdr element)) maximum-polygon-points)
				 (gensym-list element 'too-many-points)))))))
	      (bad-region-or-color-or-metacolor?
		(loop for element in element-list
		      thereis
		      (if (and (symbolp element)
			       (not (color-or-metacolor-p element))
			       (or (null region-specification?)
				   (null (assq element
					       (cdr region-specification?)))))
			  element)))
	      (error-text? nil))
	 (cond
	   (bad-background-layer?
	    (values
	      bad-phrase
	      (make-bad-region-text-string
		bad-background-layer?)))
	   (bad-region-or-color-or-metacolor?
	    (values
	      bad-phrase
	      (make-bad-region-text-string
		bad-region-or-color-or-metacolor?)))
	   (bad-polygon?
	    (let ((polygon (car bad-polygon?))
		  (reason (cadr bad-polygon?)))
	      (reclaim-gensym-list bad-polygon?)
	      (values
		bad-phrase
		(twith-output-to-text-string
		  (twrite "The ")
		  (write-drawing-element
		    (if (eq (car polygon) 'filled-polygon)
			(phrase-list 'filled-polygon (cdr polygon))
			polygon))
		  (cond ((eq reason 'not-simple-polygon)
			 (twrite " crosses itself or has two identical vertices."))
			((eq reason 'too-many-points)
			 (tformat " contains ~s points. ~s is the maximum."
				  (length (cdr polygon)) maximum-polygon-points))
			(t 
			 (twrite " is not valid.")))))))
	   (bad-variable-name?
	    (reserved-icon-variable-message bad-variable-name?))
	   (bad-variable-in-element?
	    (let* ((bad-variable (first bad-variable-in-element?))
		   (reason-for-rejection (first bad-variable))
		   (variable-name (second bad-variable))
		   (variable-value?
		     (getfq (cdr variable-specification?) variable-name))
		   (bad-element (second bad-variable-in-element?)))
	      (reclaim-gensym-cons bad-variable-in-element?)
	      (bad-variable-in-element-message
		bad-element variable-name variable-value? reason-for-rejection)))
	   ((setq error-text? (check-icon-size width height))
	    (values bad-phrase error-text?))
	   (t
	    ;; Compile all filled-polygons in the icon-description by making
	    ;;   them clockwise, and incorporating their triangular
	    ;;   decompositions.
	    (loop for element in element-list
		  do (when (and (consp element) (eq (car element) 'filled-polygon))
		       (unless (evaluating-icon-elements
				   (width height (cdr variable-specification?) nil)
				 (clockwise-polygon-p (cdr element)))
			 (setf (cdr element) (nreverse (cdr element))))
		       (setf (cdr element)
			     (phrase-cons
			       (cdr element)
			       (evaluating-icon-elements
				   (width height (cdr variable-specification?) nil)
				 (decompose-polygon (cdr element)))))))
	    
	    ;; Return it (with a polychrome header, if needed)
	    (let ((polychrome-header
		    (or region-specification? (phrase-list 'polychrome)))
		  (variable-header
		    (or variable-specification? (phrase-list 'variables)))
		  (background-header
		    (or icon-background-layer? (phrase-list 'background-layer))))

	      ;; For now, duplicates are unfortunately not removed -- consider
	      ;; fixing to allow identical duplicates and delete them here, and
	      ;; to disallow conflicting here.  Tiny but noticeable changes in
	      ;; behavior would result if we made any change at this time, and
	      ;; it would not be risk-free.  (MHD 6/8/95)

	      
	      ;; Add entries in the polychrome header for explicit colors
	      ;; found among the elements.
	      (loop for element in element-list
		    when (and (symbolp element)
			      (null (assq element (cdr polychrome-header))))
		      do (setf (cdr polychrome-header)
			       (phrase-cons
				 (phrase-cons element element)
				 (cdr polychrome-header))))
	      
	      ;; If there are elements implicitly drawn in foreground, then if
	      ;; other regions are defined in the header, then foreground must
	      ;; be explicitly present in header, so we put in (foreground .
	      ;; foreground) to pick up the initial elements; in the case where
	      ;; there is only one region, and it's implicitly foreground, this
	      ;; is not done to save a little space, and the icon painters (for
	      ;; screen drawing and for printing) handle it as they would
	      ;; a polychrome header of (polychrome (foreground . foreground)).
	      (when (and (not (symbolp (car element-list)))
			 (cdr polychrome-header)
			 (null (assq 'foreground (cdr polychrome-header))))
		(setf (cdr polychrome-header)
		      (phrase-cons
			(phrase-cons 'foreground 'foreground)
			(cdr polychrome-header))))
	      (phrase-cons
		width
		(phrase-cons
		  height
		  (phrase-cons  polychrome-header
				(phrase-cons variable-header
					     (phrase-cons
					       background-header
					       (nconc
						 (if stipple? ; stipples -- new in 6.0 (MHD 3/7/01)
						     (phrase-list (phrase-list 'stipple stipple?)))
						 element-list)))))))))))))

;; Consider moving all of the valid-line-drawing-description-p checking here, or
;; moving all of the checking done here there!





;;; `Normalize-line-drawing-elements-from-parse' is used to convert the
;;; filled-polygon, outline, and lines line drawing directives from their
;;; "point-tree" format to their final more normal flat-list format, using
;;; flatten-point-tree-phrase-into-list, q.v.  This to be called from the
;;; compiler for icon descriptions.  The result is a new phrase, with some
;;; conses new, and some conses shared with the argument.
;;;
;;; The parse-result-element-list should be that portion of an icon description
;;; parse result that contains a list of either atom elements or elements that
;;; are of the form
;;;
;;;    (<name> . x)
;;;
;;; where <name> is one of the line drawing directive names.

(defun normalize-line-drawing-elements-from-parse
    (parse-result-element-list)
  (loop for element in parse-result-element-list
	collect (or (if (consp element)
			(case (car element)
			  ((filled-polygon outline lines)
			   (phrase-cons
			     (car element)
			     (flatten-point-tree-phrase-into-list (cdr element))))))
		    element)
	  using phrase-cons))



;;; Make-bad-region-text-string ... to be used as the second value when returning
;;; bad-phrase from the slot value compiler for icon-description? and cross-
;;; section-pattern.

(defun make-bad-region-text-string (symbol)
  (tformat-text-string
    "The symbol ~a does not belong here, since it ~
     is not a declared region, a color, or a metacolor."
    symbol))



;;; Write-region-specification-list ... region-specification may also be the
;;; `layer specification list' (the cdr) of a polychrome header, which
;;; differs from a region specification list in that it has entries of the
;;; form
;;;
;;;    (color-or-metacolor . color-or-metacolor)
;;;
;;; When entries of this form are encountered, they are not written.

;;; A semicolon and a newline escape sequence are written at the end of
;;; the specification if and only if some entries were written.

(defun write-region-specification-list (region-specification-list)
  (loop with wrote-some? = nil
	for ((region-or-color-or-metacolor . color-or-metacolor))
	    on region-specification-list
	when (not (eq region-or-color-or-metacolor color-or-metacolor))
	  do (when wrote-some? (twrite-string ", "))
	     (twrite-symbol region-or-color-or-metacolor)
	     (twrite-string " = ")
	     (twrite-color color-or-metacolor)
	     (setq wrote-some? t)
	finally (when wrote-some?
		  (tformat ";~%"))))

(defun write-variable-name-and-value (name value)
  (twrite-symbol name)
  (twrite-string " = ")
  (cond ((text-string-p value)
	 (tformat " \"~a\" " value)) 
	(t (twrite value))))

;;; Write-variable-specification-list ...
;;; A semicolon and a newline escape sequence are written at the end of
;;; the specification if and only if some entries were written.

(defun write-variable-specification-list (variable-specification-list)
  (tformat "variables :~%    ")
  (loop with wrote-some? = nil
	for (variable-name  value . more?) on variable-specification-list by 'cddr
	do
    (write-variable-name-and-value variable-name value)
    (if more? (twrite-string ", "))
    (setq wrote-some? t)
	finally (if wrote-some?
		    (tformat ";~%"))))

(defun write-icon-background-layer (background-layer)
  (tformat "icon-background-layer : ")
  (cond ((image-drawing-element-p background-layer)
	 (tformat "color image ")
	 (write-image-specification background-layer))
	(t (twrite-symbol background-layer)))
  (tformat "; ~%"))

(def-slot-value-writer icon-description? (icon-description?)
  (if (null icon-description?)
      (twrite "inherited")      
      (let* ((width (first icon-description?))
	     (height (second icon-description?))
	     (line-drawing-description (cddr icon-description?))
	     (polychrome-header?		; NOT a region specification header
	       (if (and (consp (car line-drawing-description))
			(eq (caar line-drawing-description) 'polychrome))
		   (car line-drawing-description)))
	     (variable-header?
	       (get-variable-specification-if-any line-drawing-description))
	     (background-header?
	       (get-icon-background-layer-if-any line-drawing-description))
	     (stipple? (get-icon-stipple-if-any line-drawing-description))
	     (element-list
	       (get-element-list
		 line-drawing-description
		 polychrome-header?
		 variable-header?
		 background-header?
		 stipple?)))
	(tformat "width ~d; " width)
	(tformat "height ~d;~%" height)

	(if polychrome-header?
  	    (write-region-specification-list
	      (cdr polychrome-header?)))
	(if (cdr variable-header?)
	    (write-variable-specification-list
	      (cdr variable-header?)))
	(if (cdr background-header?)
	    (write-icon-background-layer
	      (second background-header?)))
	(if stipple?
	    (tformat "stipple: ~(~a~);~%" stipple?))
	
	(loop for (element . more?) on element-list
	      do (if (symbolp element)
		     (twrite-symbol element)
		     (progn	
		       (twrite "    ")
		       (write-drawing-element element)))		 
		 (if more?
		     (tformat (if (symbolp element) ":~%" ";~%")))))))



(defun write-drawing-element (element)
  (case (car element)
    (stippled-area
     (tformat "stippled area ~(~a~)" (second element))
     (loop for point in (cddr element)
	   doing (write-point point)))
    ((point lines outline solid-rectangle circle filled-polygon filled-circle)
     (case (car element)
       (solid-rectangle
	(twrite "filled rectangle"))
       (filled-polygon
	(twrite "filled polygon"))
       (filled-circle
	(twrite "filled circle"))
       (t (twrite-symbol (car element))))
     (loop for point in (if (eq (car element) 'filled-polygon) (second element) (cdr element))
	   doing (write-point point)))
    (text
     (twrite-string "text ")
     (write-text-specification element))
    (image
     (twrite-string "image ")
     (write-image-specification element))))

;;; `resolve-constants'
;;; Returns an integer representing the sum/difference of all constants
;;; within an expression, ignoring any variables it encounters.
;;; Does NOT modify the original expression.

(defun resolve-constants (expression)
  (cond  ((typep expression 'fixnum)
	  expression)
	 ((symbolp expression) 0)
	 (t (let* ((function (car expression))
		   (arg1 (resolve-constants (second expression)))
		   (arg2?(third expression))
		   (arg2 (if arg2? (resolve-constants arg2?)))
		   (args (if arg2? (slot-value-list arg1 arg2)
			     (slot-value-list 0 arg1)))
		   (result (simple-apply-for-icon function args)))
	      (reclaim-slot-value args)
	      result))))



;;; `distribute-minus-sign'
;;; Creates a NEW expression that must be reclaimed by the caller.
;;; Takes flat, infix lists ONLY.
;;; Reclaims the given expression.

(defun distribute-minus-sign (expression) 
  (loop with new-expression = nil
	with reverse-expression = (nreverse expression)
	for symbol-or-sign in reverse-expression
	do
    (cond
      ((eq symbol-or-sign '+)
       (slot-value-push '- new-expression))
      ((eq symbol-or-sign '-)
       (slot-value-push '+ new-expression))
      (t ;(symbolp symbol-or-sign)
       (slot-value-push symbol-or-sign new-expression)))
	finally
	  (reclaim-slot-value reverse-expression)
	  (return new-expression)))

;;; `add-plus-to-front'
;;; Ensures that the first element of expression is
;;; either '+ or '-
;;; The special case of '(-3) is changed to '(- 3)
;;; Modifies the original expression.

(defun add-plus-to-front (expression)
  (cond ((null expression)
	 expression)
	((or (eq (car expression) '+)
	     (eq (car expression) '-))
	 expression)
	((and (integerp (car expression))
	      (<f (car expression) 0))
	  (let ((neg-num (slot-value-pop expression)))
	    (nconc
	      (slot-value-list '-  (*f -1 neg-num))
	      expression)))
	(t
	 (slot-value-push '+ expression))))

(defun remove-plus-from-front (expression)
  (cond ((eq (car expression) '+)
	 (cdr expression))
	(t 
	 expression)))

;;; `extract-constants'
;;; Creates a NEW, flat list of ONLY the variables in the expression.
;;; Does NOT modify or reclaim expression.
;;; The caller is responsible for reclaiming the return value.

(defun extract-constants (expression)
  (cond ((typep expression 'fixnum) nil)
	((symbolp expression) (slot-value-list expression))
	((and (eq (first expression) '-)
	      (third expression))
	 (let* ((third-expression
		  (add-plus-to-front
		    (extract-constants (third expression))))
		(result 
		  (nconc
		    (extract-constants (second expression))
		    (distribute-minus-sign
		      (copy-for-slot-value third-expression)))))
	   (reclaim-slot-value third-expression)
	   result))
	((eq (first expression) '-)
	 (let* ((second-expression
		  (add-plus-to-front
		    (extract-constants (second expression))))
		(result  
		  (remove-plus-from-front
		    (distribute-minus-sign (copy-for-slot-value second-expression)))))
	   (reclaim-slot-value second-expression)
	   result))
	(t (nconc
	     (extract-constants (second expression))
	     (add-plus-to-front
	       (extract-constants (third expression)))))))


;;; `eval-point-expression'
;;; Creates a new list that must be reclaimed by the caller.
;;; Does NOT modify the original expression.

(defun eval-point-expression (expression)
  (let ((resolved-constants (resolve-constants expression))
	(variables (remove-plus-from-front (extract-constants expression))))
    (cond ((null variables)
	   resolved-constants)
	  ((eq resolved-constants 0)
	   (if (cdr variables) variables
	       (let ((result (car variables)))
		 (reclaim-slot-value-cons variables)
		 result)))
	  ((eq (car variables) '-)
	   (slot-value-push resolved-constants variables))
	  (t (loop with result = (add-plus-to-front (slot-value-list resolved-constants))
		   with reverse-variables
		     = (nreverse variables)
		   for elt in reverse-variables
		   do
	       (slot-value-push elt result)
		   finally
		     (reclaim-slot-value reverse-variables)
		     (return result))))))
		     

	
  
(defun write-point (point)   
  (cond ((or  (constant-point-p point)) ; ie not a expression
	 (if (eq (car point) 'arc)
	     (tformat " arc (~A, ~A)" (first (second point)) (second (second point)))
	     (tformat " (~A, ~A)" (first point) (second point))))
	(t ;(power-point-p point)
	 (let* ((non-arc-point (if (eq (car point) 'arc) (second point) point))
		(eval-point-x  (eval-point-expression (first non-arc-point)))
		(eval-point-y  (eval-point-expression (second non-arc-point))))
	   (if (eq (car point) 'arc)  
	       (tformat " arc (~A, ~A)" eval-point-x eval-point-y)
	       (tformat " (~A, ~A)" eval-point-x eval-point-y))
	   (reclaim-slot-value eval-point-x)
	   (reclaim-slot-value eval-point-y)))))

	       

;; Need an "icon point printer"! (MHD 5/26/94)


;;; Category-evaluator-interface for `icon-description?'
;;; corresponding slot is icon-description-for-class?
;;;
;;;

  
(define-category-evaluator-interface (region-specification
				       :access read-write)
    (structure region-specification
	       ((region-name symbol)
		(color-name (named color-or-metacolor)))
	       (and region-name color-name))
  ((set-form (evaluation-value))
   (with-safe-category-setter-calling
       (with-structure (evaluation-value region-specification)
	 (phrase-cons
	   region-name
	   (call-category-setter-safely 'color-or-metacolor color-name)))))
  ((get-form (slot-value))
   (unless (eq (car slot-value) (cdr slot-value))
     (with-new-structure (region-specification)
       (setf region-name (car slot-value))
       (setf color-name
	     (call-category-getter 'color-or-metacolor
				   (cdr slot-value)
				   nil nil))))))

(define-category-evaluator-interface (region-specification-list
				       :access read-write)
    (or (no-item)
	(sequence
	  (named region-specification)
	  1))
  ((set-form (evaluation-value))
   (when evaluation-value
     (with-safe-category-setter-calling
	 (with-evaluation-sequence-to-phrase-list-mapping
	     (evaluation-value region-specification)
	   (call-category-setter-safely 'region-specification
					region-specification)))))
  ((get-form (slot-value))
   (loop with result = nil
	 for region-specification in slot-value
	 as region-info?
	    = (call-category-getter 'region-specification
				    region-specification nil nil)
	 do
     (when region-info?
       (eval-push region-info? result))
	 finally
	   (return
	     (when result
	       (allocate-evaluation-sequence (nreverse result)))))))

(define-category-evaluator-interface (variable-specification
				       :access read-write)
    (structure variable-specification
	       ((variable-name symbol)
		(initial-value (or integer symbol text)))
	       (and variable-name initial-value))
  ((set-form (evaluation-value))
   nil) ;; DONT CALL THE SETTER
  ((get-form (name value))
   (with-new-structure (variable-specification)
     (setf variable-name name)
     (setf initial-value
	   (make-evaluation-value-based-on-type value)))))

(define-category-evaluator-interface (variable-specification-list
				       :access read-write)
    (sequence
      (named variable-specification)
      1)
  ((set-form (evaluation-value))
   (loop with plist = nil
	 for variable-spec being each evaluation-sequence-element of evaluation-value
	 do
     (with-evaluation-structure-slots (variable-spec (variable-name initial-value))
       (phrase-push variable-name plist)
       (phrase-push initial-value plist))
	 finally
	   (return (nreverse plist))))
  ((get-form (slot-value))
   (loop with eval-list = nil
	 for (name value) on slot-value by 'cddr
	 do
     (eval-push
       (call-category-getter 'variable-specification
			     name value nil)
       eval-list)
     	 finally
	   (return (if eval-list
		       (allocate-evaluation-sequence (nreverse eval-list)))))))
	
(define-category-evaluator-interface (font-size
				       :access read-write)
    (or (member small large extra-large)
	(named unreserved-symbol))
  ((set-form (evaluation-value))
   evaluation-value)
  ((get-form (slot-value))
   slot-value))

(define-category-evaluator-interface (point-factor
				       :access read-write)
    (or integer
	(named unreserved-symbol))
  ((set-form (evaluation-value))
   (with-safe-category-setter-calling
       (cond ((symbolp evaluation-value)
	      (call-category-setter-safely 'unreserved-symbol evaluation-value))
	     (t evaluation-value))))
  ((get-form (slot-value))
   slot-value))

(define-category-evaluator-interface (point-sum
				       :access read-write)
    text
  ((set-form (evaluation-value))
   (parse-text-string evaluation-value 'point-sum))
  ((get-form (slot-value))
   (let*((evaluated-expression (eval-point-expression slot-value))
	 (result (twith-output-to-text-string
		     (tformat "~A" evaluated-expression))))
     (reclaim-slot-value evaluated-expression)
     result)))

(defmacro point-factor-p (evaluation-value)
  `(or (integerp ,evaluation-value) (symbolp ,evaluation-value)))

(define-category-evaluator-interface (point-expression
				       :access read-write)
    (or (named point-factor)
	(named point-sum))
  ((set-form (evaluation-value))
   (with-safe-category-setter-calling
       (cond ((point-factor-p evaluation-value)
	      (call-category-setter-safely 'point-factor evaluation-value))
	     (t
	      (call-category-setter-safely 'point-sum evaluation-value)))))
  ((get-form (slot-value))
   (cond ((point-factor-p slot-value)
	  (call-category-getter 'point-factor slot-value nil nil))
	 (t
	  (call-category-getter 'point-sum slot-value nil nil)))))
       
(define-category-evaluator-interface (point
				       :access read-write)
    (structure point
	       ((x (named point-expression))
		(y (named point-expression)))
	       (and x y))
  ((set-form (evaluation-value))
   (with-safe-category-setter-calling
       (with-structure (evaluation-value point)
	 (phrase-list
	   (call-category-setter-safely 'point-expression x)
	   (call-category-setter-safely 'point-expression y)))))
  ((get-form (slot-value))
   (when slot-value
     (with-new-structure (point)
       (setf x (call-category-getter 'point-expression
				     (car slot-value) nil nil))
       (setf y (call-category-getter 'point-expression
				     (cadr slot-value) nil nil))))))

(define-category-evaluator-interface (point-or-arcpoint
				       :access read-write)
    (structure point-or-arcpoint
	       ((arc (named truth-value))
		(x (named point-expression))
		(y (named point-expression)))
	       (and x y))
  ((set-form (evaluation-value))
   (with-safe-category-setter-calling
       (with-structure (evaluation-value point-or-arcpoint)
	 (let ((point
		 (phrase-list
		   (call-category-setter-safely 'point-expression x)
		   (call-category-setter-safely 'point-expression y))))
	   (cond ((and (evaluation-truth-value-p arc)
		       (evaluation-truth-value-true-p arc))
		  (phrase-list 'arc point))
		 (t point))))))
  ((get-form (slot-value))
   (when slot-value
     (with-new-structure (point-or-arcpoint)
       (cond ((arc-point-p slot-value)
	      (setf arc (call-category-getter 'truth-value truth nil nil))
	      (setf x (call-category-getter 'point-expression
					    (caadr slot-value) nil nil))
	      (setf y (call-category-getter 'point-expression
					    (cadadr slot-value) nil nil)))
	     (t
	      (setf x (call-category-getter 'point-expression
					    (car slot-value) nil nil))
	      (setf y (call-category-getter 'point-expression
					    (cadr slot-value) nil nil))))))))


(define-category-evaluator-interface (static-point
				       :access read-write)
    (structure static-point
	       ((x integer)
		(y integer))
	       (and x y))
  ((set-form (evaluation-value))
   (with-safe-category-setter-calling
       (with-structure (evaluation-value static-point)
	 (phrase-list x y))))
  ((get-form (slot-value))
   (when slot-value
     (with-new-structure (static-point)
       (setf x (car slot-value))
       (setf y (cadr slot-value))))))

(define-category-evaluator-interface (points
				       :access read-write)
    (sequence (named point)
	      1)
  ((set-form (evaluation-value))
   (with-safe-category-setter-calling
       (with-evaluation-sequence-to-phrase-list-mapping (evaluation-value point)
	 (call-category-setter-safely 'point point))))
  ((get-form (slot-value))
   (with-list-to-evaluation-sequence-mapping (slot-value point)
     (call-category-getter 'point point nil nil))))

(define-category-evaluator-interface (points-or-arcpoints
				       :access read-write)
    (sequence (named point-or-arcpoint)
	      1)
  ((set-form (evaluation-value))
   (with-safe-category-setter-calling
       (with-evaluation-sequence-to-phrase-list-mapping (evaluation-value point-or-arcpoint)
	 (call-category-setter-safely 'point-or-arcpoint point-or-arcpoint))))
  ((get-form (slot-value))
   (with-list-to-evaluation-sequence-mapping (slot-value point-or-arcpoint)
     (call-category-getter 'point-or-arcpoint point-or-arcpoint nil nil))))



(define-category-evaluator-interface (filled-polygon-point-tree
				       :access read-write)
    (sequence (named point)
	      3)
  ((set-form (evaluation-value))
   (with-safe-category-setter-calling
       (point-tree-phrase
	 (call-category-setter-safely 'points evaluation-value))))
  ((get-form (slot-value))
   (with-list-to-evaluation-sequence-mapping (slot-value point)
     (call-category-getter 'point point nil nil))))


(defun valid-points-for-lines-point-tree-p (points)
  (cond ((arc-point-p (car points))
	 nil)
	(t
	 (loop for (point1 point2) on points
	       when (and (arc-point-p point1)
			 (or (arc-point-p point2)
			     (null point2)))
		 do
		   (return nil)
	       finally
		 (return t)))))
		 
(define-category-evaluator-interface (lines-point-tree
				       :access read-write)
    (sequence (named point-or-arcpoint) 
	      2)
  ((set-form (evaluation-value))
   (with-safe-category-setter-calling
       (let ((points
	       (call-category-setter-safely 'points-or-arcpoints evaluation-value)))
	 (cond ((valid-points-for-lines-point-tree-p points)
		(point-tree-phrase points))
	       (t
		(values
		  bad-phrase
		  (twith-output-to-text-string
		    (tformat
		      "~%The structure (type: the symbol lines, points: ~NV) contains an invalid use of arc points."
		      evaluation-value))))))))
  ((get-form (slot-value))
   (call-category-getter 'points-or-arcpoints slot-value nil nil)))



(defun valid-points-for-outline-point-tree-p (points)
  (cond ((arc-point-p (car points))
	 nil)
	(t
	 (loop for (point1 point2) on points
	       when (and (arc-point-p point1)
			 (arc-point-p point2))
		 do
		   (return nil)
	       finally
		 (return t)))))

(define-category-evaluator-interface (outline-point-tree
				       :access read-write)
    (sequence (named point-or-arcpoint) 
	      2)
  ((set-form (evaluation-value))
   (with-safe-category-setter-calling
       (let ((points
	       (call-category-setter-safely 'points-or-arcpoints evaluation-value)))
	 (cond ((valid-points-for-outline-point-tree-p points)
		(point-tree-phrase points))
	       (t
		(values
		  bad-phrase
		  (twith-output-to-text-string
		    (tformat
		      "~%The structure(type: the symbol outline, points: ~NV) contains an invalid use of arc points."
		       evaluation-value))))))))
  ((get-form (slot-value))
   (call-category-getter 'points-or-arcpoints slot-value nil nil)))

(define-category-evaluator-interface (text-drawing-element
				       :access read-write)
    (structure text-drawing-element
	       ((type (member text))
		(label (or symbol text))
		(point (named point))
		(font-size (named font-size)))
	       (and type label point font-size))
  ((set-form (evaluation-value))
   (with-safe-category-setter-calling
       (with-structure (evaluation-value text-drawing-element)
	 (phrase-list
	   type
	   (copy-for-phrase label)
	   (call-category-setter-safely 'point point)
	   (call-category-setter-safely 'font-size font-size)))))
  ((get-form (slot-value))
   (with-new-structure (text-drawing-element)
     (setf type 'text)
     (setf label (copy-evaluation-value (cadr slot-value)))
     (setf point
	   (call-category-getter 'point (caddr slot-value) nil nil))
     (setf font-size
	   (call-category-getter 'font-size (cadddr slot-value) nil nil)))))

(define-category-evaluator-interface (image-drawing-element
				       :access read-write)
    (structure image-drawing-element
	       ((type (member image))
		(image-name symbol)
		(point (named point)))
	       (and type image-name))
  ((set-form (evaluation-value))
   (with-safe-category-setter-calling
       (with-structure (evaluation-value image-drawing-element)
	 (nconc (phrase-list
		  type
		  image-name)
		(when point (phrase-list
			      (call-category-setter-safely 'point point)))))))
  ((get-form (slot-value))
   (with-new-structure (image-drawing-element)
     (setf type 'image)
     (setf image-name  (cadr slot-value))
     (setf-non-nil point
		   (call-category-getter 'point (caddr slot-value) nil nil)))))

(define-category-evaluator-interface (background-image-drawing-element
				       :access read-write)
    (structure background-image-drawing-element
	       ((type (member image))
		(image-name symbol)
		(point (named static-point)))
	       (and type image-name))
  ((set-form (evaluation-value))
   (with-safe-category-setter-calling
       (with-structure (evaluation-value background-image-drawing-element)
	 (nconc (phrase-list
		  type
		  image-name)
		(when point
		  (phrase-list
		    (call-category-setter-safely 'static-point point)))))))
  ((get-form (slot-value))
   (with-new-structure (background-image-drawing-element)
     (setf type 'image)
     (setf image-name  (cadr slot-value))
     (setf-non-nil
       point
       (call-category-getter 'static-point (caddr slot-value) nil nil)))))
  
(define-category-evaluator-interface (icon-background-layer-element
				       :access read-write)
    (or (named background-image-drawing-element)
	(named color-or-metacolor))
  ((set-form (evaluation-value))
   (with-safe-category-setter-calling
       (cond ((symbolp evaluation-value)
	      (call-category-setter-safely 'color-or-metacolor
					   evaluation-value))
	     (t
	      (call-category-setter-safely 'background-image-drawing-element
					   evaluation-value)))))
  ((get-form (slot-value))
   (cond ((symbolp slot-value)
	  (call-category-getter 'color-or-metacolor slot-value nil nil))
	 (t
	  (call-category-getter 'background-image-drawing-element
				slot-value nil nil)))))

(define-category-evaluator-interface (point-drawing-element
				       :access read-write)
    (structure point-drawing-element
	       ((type (member point))
		(points (named point)))
	       (and type points))
  ((set-form (evaluation-value))
   (with-safe-category-setter-calling
       (with-structure (evaluation-value point-drawing-element)
	 (phrase-list
	   type
	   (call-category-setter-safely 'point points)))))
  ((get-form (slot-value))
   (with-new-structure (point-drawing-element)
     (setf type 'point)
     (setf points
	   (call-category-getter 'point (cadr slot-value) nil nil)))))

(define-category-evaluator-interface (circle-drawing-element
				       :access read-write)
    (structure circle-drawing-element
	       ((type (member circle))
		(points (named points))) 
	       (and type points))
  ((set-form (evaluation-value))
   (with-safe-category-setter-calling
       (with-structure (evaluation-value circle-drawing-element)
	 (cond ((=f (evaluation-sequence-length points) 3)
		(phrase-cons
		  type
		  (call-category-setter-safely 'points points)))
	       (t (values
		    bad-phrase
		    (twith-output-to-text-string
		      (tformat "The circle ~s should have exactly 3 points"
			       evaluation-value))))))))
  ((get-form (slot-value))
   (with-new-structure (circle-drawing-element)
     (setf type 'circle)
     (setf points
	   (call-category-getter 'points (cdr slot-value) nil nil)))))
  
(define-category-evaluator-interface (solid-rectangle-drawing-element
				       :access read-write)
    (structure solid-rectangle-drawing-element
	       ((type (member filled-rectangle))
		(points (named points))) ; 2
	       (and type points))
  ((set-form (evaluation-value))
   (with-safe-category-setter-calling
       (with-structure (evaluation-value solid-rectangle-drawing-element)
	 (cond ((=f (evaluation-sequence-length points) 2)
		(phrase-cons
		  'solid-rectangle
		  (call-category-setter-safely 'points points)))
	       (t (values
		    bad-phrase
		    (twith-output-to-text-string
		      (tformat "The filled-rectangle ~s should have exactly 2 points"
			       evaluation-value))))))))
  ((get-form (slot-value))
   (with-new-structure (solid-rectangle-drawing-element)
     (setf type 'filled-rectangle)
     (setf points
	   (call-category-getter 'points (cdr slot-value) nil nil)))))
  		
(define-category-evaluator-interface (filled-circle-drawing-element
				       :access read-write)
    (structure filled-circle-drawing-element
	       ((type (member filled-circle))
		(points (named points))) 
	       (and type points))
  ((set-form (evaluation-value))
   (with-safe-category-setter-calling
       (with-structure (evaluation-value filled-circle-drawing-element)
	 (cond ((=f (evaluation-sequence-length points) 3)
		(phrase-cons
		  type
		  (call-category-setter-safely 'points points)))
	       (t (values
		    bad-phrase
		    (twith-output-to-text-string
		      (tformat "The filled-circle ~s should have exactly 3 points"
			       evaluation-value))))))))
  ((get-form (slot-value))
   (with-new-structure (filled-circle-drawing-element)
     (setf type 'filled-circle)
     (setf points
	   (call-category-getter 'points (cdr slot-value) nil nil)))))

(define-category-evaluator-interface (lines-drawing-element
				       :access read-write)
    (structure lines-drawing-element
	       ((type (member lines))
		(points (named lines-point-tree)))
	       (and type points))
  ((set-form (evaluation-value))
   (with-safe-category-setter-calling
       (with-structure (evaluation-value lines-drawing-element)
	 (phrase-cons
	   type
	   (call-category-setter-safely 'lines-point-tree points)))))
  ((get-form (slot-value))
   (with-new-structure (lines-drawing-element)
     (setf type 'lines)
     (setf points
	   (call-category-getter 'lines-point-tree (cdr slot-value) nil nil)))))
  
(define-category-evaluator-interface (outline-drawing-element
				       :access read-write)
    (structure outline-drawing-element
	       ((type (member outline))
		(points (named outline-point-tree))) 
	       (and type points))
  ((set-form (evaluation-value))
   (with-safe-category-setter-calling
       (with-structure (evaluation-value outline-drawing-element)
	 (phrase-cons
	   type
	   (call-category-setter-safely 'outline-point-tree points)))))
  ((get-form (slot-value))
   (with-new-structure (outline-drawing-element)
     (setf type 'outline)
     (setf points
	   (call-category-getter 'outline-point-tree (cdr slot-value) nil nil)))))

(define-category-evaluator-interface (filled-polygon-drawing-element
				       :access read-write)
    (structure filled-polygon-drawing-element
	       ((type (member filled-polygon))
		(points (named filled-polygon-point-tree))) 
	       (and type points))
  ((set-form (evaluation-value))
   (with-safe-category-setter-calling
       (with-structure (evaluation-value filled-polygon-drawing-element)
	 (phrase-cons
	   type
	   (call-category-setter-safely 'filled-polygon-point-tree points)))))
  ((get-form (slot-value))
   (with-new-structure (filled-polygon-drawing-element)
     (setf type 'filled-polygon)
     (setf points
	   (call-category-getter 'points (cadr slot-value) nil nil)))))

(define-category-evaluator-interface (stippled-area-drawing-element
				       :access read-write)
    (structure stippled-area-drawing-element
	       ((type (member stippled-area))
		(stipple (member . #.all-stipples))
		(points (named points))) ; 2
	       (and type stipple))
  ((set-form (evaluation-value))
   (with-safe-category-setter-calling
       (with-structure (evaluation-value stippled-area-drawing-element)
	 (cond ((or (null points)
		    (=f (evaluation-sequence-length points) 2))
		(phrase-cons
		  'stippled-area
		  (phrase-cons
		    stipple
		    (if points
			(call-category-setter-safely 'points points)))))
	       (t (values
		    bad-phrase
		    (twith-output-to-text-string
		      (tformat "The stippled-area ~s should have no points or exactly 2 points"
			       evaluation-value))))))))
  ((get-form (slot-value))
   (with-new-structure (stippled-area-drawing-element)
     (setf type 'stippled-area)
     (setf stipple (second slot-value))
     (when (cddr slot-value)
       (setf points
	     (call-category-getter 'points (cddr slot-value) nil nil))))))

(defun map-line-drawing-element-type-to-category-name (type)
  (cond ((memq type '(text image point circle filled-circle
		      lines outline filled-polygon solid-rectangle stippled-area))
	 (intern-text-string
	   (tformat-text-string "~a-~a" type 'drawing-element)))
	((eq type 'filled-rectangle) 'solid-rectangle-drawing-element)
	(t 'bad-element-type-error)))

(define-category-evaluator-interface (line-drawing-element
				       :access read-write)
    (or (named text-drawing-element)
	(named image-drawing-element)
	(named point-drawing-element)
	(named circle-drawing-element)
	(named solid-rectangle-drawing-element)
	(named filled-circle-drawing-element)
	(named lines-drawing-element)
	(named outline-drawing-element)
	(named filled-polygon-drawing-element)
	(named stippled-area-drawing-element))
	       
  ((set-form (evaluation-value))
    (evaluation-etypecase
     evaluation-value
     ((no-item) (values bad-phrase
			(twith-output-to-text-string
			  (tformat "a line-drawing-element can not be empty"))))
     ((structure)
      (with-safe-category-setter-calling
	(let* ((type (evaluation-structure-slot evaluation-value 'type))
	       (category-name
		 (map-line-drawing-element-type-to-category-name type)))
	  (cond ((eq category-name 'bad-element-type-error)
		 (values bad-phrase
			 (twith-output-to-text-string
			   (tformat "~s is not a valid drawing-element type."
				    type))))
		(t
		 (call-category-setter-safely category-name evaluation-value))))))))
  ((get-form (slot-value))
   (let* ((line-drawing-element-type (car slot-value))
	  (category-name
	   (map-line-drawing-element-type-to-category-name line-drawing-element-type)))
     (call-category-getter category-name slot-value nil nil))))

(define-category-evaluator-interface (line-drawing-elements
				       :access read-write)
    (sequence
      (named line-drawing-element)
      1)
  ((set-form (evaluation-value))
   (evaluation-etypecase
     evaluation-value
     ((no-item) (values bad-phrase
			(twith-output-to-text-string
			  (tformat "a layer must have at least one element"))))
     ((sequence)
      (with-safe-category-setter-calling
	  (with-evaluation-sequence-to-phrase-list-mapping
	      (evaluation-value line-drawing-element)
	    (call-category-setter-safely 'line-drawing-element
					 line-drawing-element))))))
  ((get-form (slot-value))
   (with-list-to-evaluation-sequence-mapping (slot-value line-drawing-element)
     (call-category-getter 'line-drawing-element line-drawing-element nil nil))))
  
(define-category-evaluator-interface (region-or-color-or-metacolor
				       :access read-write)
    (or (no-item) symbol)
  ((set-form (evaluation-value))
   (or evaluation-value 'foreground))
  ((get-form (slot-value))
   (or slot-value 'foreground)))

(define-category-evaluator-interface (layer
				       :access read-write)
    (structure layer
	       ((region-or-color (named region-or-color-or-metacolor))
		(line-drawing-elements (named line-drawing-elements)))
	       (and region-or-color line-drawing-elements))
  ((set-form (evaluation-value))
   (evaluation-etypecase
     evaluation-value
     ((no-item)
      (values bad-phrase (twith-output-to-text-string
			   (tformat "A layer should not be empty."))))
     ((structure)
      (with-safe-category-setter-calling
	  (with-structure (evaluation-value layer)
	    (phrase-cons
	      (call-category-setter-safely 'region-or-color-or-metacolor
					   region-or-color)
	      (call-category-setter-safely 'line-drawing-elements
					   line-drawing-elements)))))))
  ((get-form (slot-value))
   (with-new-structure (layer)
     (let ((region? (car slot-value)))
       (setf-non-nil region-or-color
		     (call-category-getter 'region-or-color-or-metacolor
					   (and (symbolp region?) region?)
					   nil nil))
       (setf line-drawing-elements
	     (call-category-getter 'line-drawing-elements
				   (cond ((symbolp region?)
					  (cdr slot-value))
					 (t slot-value))
				   nil nil))))))

(defun convert-list-of-layers-to-slot-value-layers (layers)
    (with-safe-category-setter-calling
	(loop with result = nil
	      for layer
		  being each evaluation-sequence-element of layers
	      as layer-info
		 = (call-category-setter-safely 'layer layer)
	      do
	  (setf result (nconc result layer-info))
	      finally
		(return result))))

(define-category-evaluator-interface (label-and-element-list
				       :access read-write)
    (sequence
      (named layer)
      1)
  ((set-form (evaluation-value))
   (evaluation-etypecase
     evaluation-value
     ((no-item) (values bad-phrase (twith-output-to-text-string
				     (tformat "layers can not be empty"))))
     ((sequence)
      (convert-list-of-layers-to-slot-value-layers evaluation-value))))
  ((get-form (slot-value))
   (with-list-to-evaluation-sequence-mapping (slot-value layer)
     (call-category-getter 'layer layer nil nil))))




;;; `convert-slot-value-layers-to-list-of-layers'
;;; Chops up an icon-descriptions label and element list into
;;; seperate layers,ie
;;; ((label1 elt1-1 elt1-2 ...)(label2 elt2-1 elt2-2 ...)...)
;;; NOTE that the caller must reclaim the return value using the
;;; function reclaim-list-of-layers, since this functions does
;;; NOT copy the elements within the slot-value-layers.

(defun convert-slot-value-layers-to-list-of-layers (slot-value-layers)
  (loop while slot-value-layers
	for layer = (loop for first = t then nil
			  while (or first (consp (car slot-value-layers)))
			  collect (pop slot-value-layers) using gensym-cons)
	collect layer using gensym-cons))

(defun reclaim-list-of-layers (list-of-layers)
  (loop for layer in list-of-layers
	do (reclaim-gensym-list layer)
	finally (reclaim-gensym-list list-of-layers)))


(define-category-evaluator-interface (icon-description?
				       :access read-write)
    (or (no-item) 
	(structure icon-description-spec
		   ((width integer)
		    (height integer)
		    (regions (named region-specification-list))
		    (variables (named variable-specification-list))
		    (icon-background-layer (named icon-background-layer-element))
		    (stipple (member . #.all-stipples))
		    (layers (named label-and-element-list)))
		   (and width height
			layers)))
  ((set-form (evaluation-value))
   (evaluation-etypecase
     evaluation-value
     ((no-item) 'inherited)
     ((structure)
      (with-structure (evaluation-value icon-description-spec)
	(with-safe-category-setter-calling
	    (let ((layers-info
		    (phrase-cons '\; (call-category-setter-safely
				       'label-and-element-list layers))))
	      (when stipple
		(phrase-push
		  (phrase-list 'stipple stipple)
		  layers-info))
	      (when icon-background-layer
		(phrase-push
		  (phrase-list
		    'background-layer
		    (call-category-setter-safely
		      'icon-background-layer-element
		      icon-background-layer))
		  layers-info))
	      (when variables
		(phrase-push
		  (phrase-cons 'variables
			       (call-category-setter-safely
				 'variable-specification-list variables))
		  layers-info))
	      (when regions
		(phrase-push
		  (phrase-cons
		    'polychrome
		    (phrase-cons '\,(call-category-setter-safely
				      'region-specification-list
				      regions)))
		  layers-info))
	      (phrase-push height layers-info)
	      (phrase-push width layers-info)
	      layers-info))))))
  ((get-form (slot-value))
   (cond
     (slot-value 
      (with-new-structure (icon-description-spec)
	(let* ((regions-header?
		 (get-polychrome-header-if-any
		   (cddr slot-value)))
	       (variables-header?
		 (get-variable-specification-if-any slot-value))
	       (background-header?
		 (get-icon-background-layer-if-any slot-value))
	       (stipple?
		 (get-icon-stipple-if-any slot-value))
	       (list-of-layers
		 (convert-slot-value-layers-to-list-of-layers
		   (get-element-list (cddr slot-value)
				     regions-header?
				     variables-header?
				     background-header?
				     stipple?))))
	  
	(setf width (first slot-value))
	(setf height (second slot-value))
	(setf-non-nil regions
		      (call-category-getter 'region-specification-list
					    (cdr regions-header?)
					    ;;(cdr (third slot-value))
					    nil nil))
	(setf-non-nil variables 
		      (call-category-getter 'variable-specification-list
					    (cdr variables-header?)
					    ;;(cdr (fourth slot-value))
					    nil nil))
	(setf-non-nil icon-background-layer 
		      (call-category-getter 'icon-background-layer-element
					    (cadr background-header?)
					    ;;(cadr (fifth slot-value))
					    nil nil))
	(setf-non-nil stipple stipple?)
		      
	(setf layers
	      (call-category-getter 'label-and-element-list
				    list-of-layers
				      ;;;(cdr (cddddr slot-value)))
				    nil nil))
	(reclaim-list-of-layers list-of-layers)))))))

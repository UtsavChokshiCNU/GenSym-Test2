;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module ICONS3 -- The Events Translator for the Icon Editor

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Ong, Peng Tsin





;;;; Icons3 - The Icon Editor's Events Translator






;; To ICONS4

(declare-forward-reference enqueue-icon-editor-engine-event function)

#+development
(declare-forward-reference check-memory function)






;; MOVE TO SOME ICONS-x ENGINE FILE......

;;; The function `point-in-draw-area-of-view-pad-p' returns nil if the given
;;; point (in workspace coordinates) is not in the engine pad.  Non-nil is
;;; returned otherwise.  Only entities that belong in the view pad should be
;;; placed there(???) ... 

;; This should be inproved for efficiency!!!  It shouldn't have
;; to call point-in-view-pad-p.  -pto 06oct89

(defun point-in-draw-area-of-view-pad-p
       (x-in-workspace y-in-workspace engine view-pad)
  (and (<=w (icon-editor-view-pad-x-origin-in-workspace view-pad) x-in-workspace)
       (<=w x-in-workspace
	    (+w (delta-x-in-workspace-from-view-pad
		  (icon-editor-engine-icon-width engine) view-pad)
		(icon-editor-view-pad-x-origin-in-workspace view-pad)))
       (<=w (icon-editor-view-pad-y-origin-in-workspace view-pad) y-in-workspace)
       (<=w y-in-workspace
	    (+w (delta-y-in-workspace-from-view-pad
		  (icon-editor-engine-icon-height engine) view-pad)
		(icon-editor-view-pad-y-origin-in-workspace view-pad)))))


;;; The function `snap-to-limits-of-width-and-height-if-necessary' returns
;;; the x and y values limited by 0 from below and the icon width or height
;;; from above.

(defun snap-to-limits-of-width-and-height-if-necessary
       (x-in-view-pad y-in-view-pad icon-width icon-height)
  (values
    (cond ((<w x-in-view-pad 0) 0)
	  ((>w x-in-view-pad icon-width) icon-width)
	  (t x-in-view-pad))
    (cond ((<w y-in-view-pad 0) 0)
	  ((>w y-in-view-pad icon-height) icon-height)
	  (t y-in-view-pad))))












(defun clip-x-in-workspace-to-engine (x-in-workspace engine view-pad)
  (let* ((min-x-view-pad-in-workspace
	   (icon-editor-view-pad-x-origin-in-workspace view-pad))
	 (max-x-view-pad-in-workspace
	   (+w (delta-x-in-workspace-from-view-pad
		 (icon-editor-engine-icon-width engine) view-pad)
	       min-x-view-pad-in-workspace)))
    (if (<=w x-in-workspace min-x-view-pad-in-workspace)
	min-x-view-pad-in-workspace
	(if (>=w x-in-workspace max-x-view-pad-in-workspace)
	    max-x-view-pad-in-workspace
	    x-in-workspace))))


;(defun y-in-engine-p
;	(y-in-workspace engine view-pad)
;  (and (>=w y-in-workspace (icon-editor-view-pad-y-in-workspace view-pad))
;       (<=w y-in-workspace
;	    (+w (delta-y-in-workspace-from-view-pad
;		  (icon-editor-engine-icon-height engine) view-pad)
;		(icon-editor-view-pad-y-origin-in-workspace view-pad)))))

(defun clip-y-in-workspace-to-engine (y-in-workspace engine view-pad)
  (let* ((min-y-view-pad-in-workspace
	   (icon-editor-view-pad-y-origin-in-workspace view-pad))
	 (max-y-view-pad-in-workspace
	   (+w (delta-y-in-workspace-from-view-pad
		 (icon-editor-engine-icon-height engine) view-pad)
	       min-y-view-pad-in-workspace)))
    (if (<=w y-in-workspace min-y-view-pad-in-workspace)
	min-y-view-pad-in-workspace
	(if (>=w y-in-workspace max-y-view-pad-in-workspace)
	    max-y-view-pad-in-workspace
	    y-in-workspace))))






;;;; State Information Stacks




(defun push-icon-editor-translator-state-information
       (translator new-state-information)
  (setf (icon-editor-translator-state-information translator)
	(icon-editor-cons
	  new-state-information
	  (icon-editor-translator-state-information translator))))


(defun enqueue-icon-editor-translator-state-information
       (translator new-state-information)
  (let ((state-information-list
	  (icon-editor-translator-state-information translator)))
    (if state-information-list
	(loop for state-information on state-information-list
	      until (null (cdr state-information))
	      finally
		(setf (cdr state-information) 
		      (icon-editor-cons new-state-information nil)))
	(setf (icon-editor-translator-state-information translator)
	      (icon-editor-cons new-state-information nil)))))


(defun clear-icon-editor-translator-state-information (translator)
  (let ((state-information?
	  (icon-editor-translator-state-information translator)))
    (when state-information?
      (reclaim-icon-editor-slot-value state-information?)
      (setf (icon-editor-translator-state-information translator) nil))))


;; ... pop the stack, reclaim the cons, and return the popped state.

(defun pop-icon-editor-translator-state-information (translator)
  (let ((state-information?
	  (icon-editor-translator-state-information translator)))
    (when state-information?
      (let ((popped-state-info (first state-information?)))
	(setf (icon-editor-translator-state-information translator)
	      (cdr state-information?))
	(reclaim-icon-editor-cons state-information?)
	popped-state-info))))






(defun pop-last-marker-if-drawn (icon-editor translator)
  (let* ((last-marker-drawn?
	   (icon-editor-translator-last-marker-drawn? translator)))
    (when (and last-marker-drawn?
	       (neq last-marker-drawn? 'special))
      (enqueue-icon-editor-visual-event
	icon-editor				; pop last cross/line marker
	(icon-editor-visual-event 'pop-marker-from-view-pad)
	nil nil))))







;; NOTE:  The code for computing maximum and minimum bounds of layers
;; and drawing elements should be generalized and moved to ENTITIES!!!
;; -pto 20oct89.

(def-substitution-macro choose-maximums-and-minimums
    (x1 y1 min-x2 min-y2 max-x2 max-y2)
  (values
    (minf x1 min-x2)
    (minf y1 min-y2)
    (maxf x1 max-x2)
    (maxf y1 max-y2)))


;;; Must be wrapped inside 'evaluating-icon-points if points
;;; contain variables.
(defun compute-maximums-and-minimums-for-points
    (list-of-points-or-arcs min-x min-y max-x max-y)
  ;;
  ;; MORE WORK HERE
  ;; Do the actual compuations for arcs and circles.
  ;;
  (loop for point-or-arc in list-of-points-or-arcs
	do
    (cond
      ((arc-point-p list-of-points-or-arcs)
       (multiple-value-setq (min-x min-y max-x max-y)
	 (compute-maximums-and-minimums-for-points
	   (cdr point-or-arc) min-x min-y max-x max-y)))

      ((or (power-point-p point-or-arc) (constant-point-p point-or-arc))
       (multiple-value-setq (min-x min-y max-x max-y)
	 (choose-maximums-and-minimums
	   (point-x point-or-arc)(point-y point-or-arc) 
	   min-x min-y max-x max-y)))))
  (values min-x min-y max-x max-y))
 
(defun compute-maximums-and-minimums-for-drawing-elements
    (drawing-elements variable-spec-list
		      min-x min-y max-x max-y
		      icon-width icon-height)
 (evaluating-icon-elements (icon-width icon-height variable-spec-list nil)
  (loop for drawing-element in drawing-elements
	do
    (case (car drawing-element)
      ((point outline solid-rectangle filled-circle)
       (multiple-value-setq (min-x min-y max-x max-y)
	 (compute-maximums-and-minimums-for-points
	   (cdr drawing-element) min-x min-y max-x max-y)))

      ;; Images need to be accounted for, if their definitions exists.
      ;; Otherwise, the limits on the dragging of layers gets screwed up.
      (image						    ; (image name &optional (x y))
       (let* ((image-name (simple-eval-for-icon (second drawing-element)))
	      (point? (third drawing-element))
	      (x0 (if point? (point-x point?) 0))
	      (y0 (if point? (point-y point?) 0))
	      (image-data? (find-image-data image-name))
	      (width (if image-data? (image-data-width image-data?) 0))
	      (height (if image-data? (image-data-height image-data?) 0)))

	 (multiple-value-setq (min-x min-y max-x max-y)
	   (choose-maximums-and-minimums
	     x0 y0 min-x min-y max-x max-y))
	 (multiple-value-setq (min-x min-y max-x max-y)
	   (choose-maximums-and-minimums
	     (+f x0 width) (+f y0 height) min-x min-y max-x max-y))))
      (text
       (multiple-value-bind (left top right bottom)
	   (compute-edges-for-text-drawing-element drawing-element)
	 (multiple-value-setq (min-x min-y max-x max-y)
	   (choose-maximums-and-minimums
	     left top min-x min-y max-x max-y))
	 (multiple-value-setq (min-x min-y max-x max-y)
	   (choose-maximums-and-minimums
	     right bottom min-x min-y max-x max-y))))
	      

      (lines
       (cond
	 ((and (eq (first (third drawing-element)) 'arc)
	       (=f (length drawing-element) 4))
	  ;; (lines (x y) (arc (x y)) (x y))
	  (let* ((point-1 (second drawing-element))
		 (point-2 (second (third drawing-element)))
		 (point-3 (fourth drawing-element)))
	    (multiple-value-bind (arc-min-x? arc-min-y? arc-max-x? arc-max-y?)
		(compute-arc-bounding-box
		  (point-x point-1) (point-y point-1)
		  (point-x point-2) (point-y point-2)
		  (point-x point-3) (point-y point-3))
	      (cond
		(arc-min-x?
		 (multiple-value-setq (min-x min-y max-x max-y)
		   (choose-maximums-and-minimums
		     arc-min-x? arc-min-y? 
		     min-x min-y max-x max-y))
		 (multiple-value-setq (min-x min-y max-x max-y)
		   (choose-maximums-and-minimums
		     arc-max-x? arc-max-y?
		     min-x min-y max-x max-y)))
		(t
		 (multiple-value-setq (min-x min-y max-x max-y)
		   (compute-maximums-and-minimums-for-points
		     (cdr drawing-element) min-x min-y max-x max-y)))))))
	 (t
	  (multiple-value-setq (min-x min-y max-x max-y)
	    (compute-maximums-and-minimums-for-points
	      (cdr drawing-element) min-x min-y max-x max-y)))))
      (circle
       (let* ((point-1 (second drawing-element))
	      (point-2 (third drawing-element))
	      (point-3 (fourth drawing-element)))
	 (multiple-value-bind (fixnum-x-center? fixnum-y-center? fixnum-radius?)
	     (calculate-center-and-radius-of-circle
	       (point-x point-1) (point-y point-1)
	       (point-x point-2) (point-y point-2)
	       (point-x point-3) (point-y point-3))
	   (cond
	     (fixnum-radius?
	      (multiple-value-setq (min-x min-y max-x max-y)
		(choose-maximums-and-minimums
		  (-f fixnum-x-center? fixnum-radius?)
		  (-f fixnum-y-center? fixnum-radius?)
		  min-x min-y max-x max-y))
	      (multiple-value-setq (min-x min-y max-x max-y)
		(choose-maximums-and-minimums
		  (+f fixnum-x-center? fixnum-radius?)
		  (+f fixnum-y-center? fixnum-radius?)
		  min-x min-y max-x max-y)))
	     (t
	      (multiple-value-setq (min-x min-y max-x max-y)
		(compute-maximums-and-minimums-for-points
		  (cdr drawing-element) min-x min-y max-x max-y)))))))
      (filled-polygon
       (multiple-value-setq (min-x min-y max-x max-y)
	 (compute-maximums-and-minimums-for-points
	   (second drawing-element) min-x min-y max-x max-y))
       (loop for triangle in (cddr drawing-element)
	     do
	 (multiple-value-setq (min-x min-y max-x max-y)
	   (compute-maximums-and-minimums-for-points
	     triangle min-x min-y max-x max-y))))))
  (if (<f min-x 0) (setq min-x 0))
  (if (<f min-y 0) (setq min-y 0))
  (if (>f max-x icon-width) (setq max-x icon-width))
  (if (>f max-y icon-height) (setq max-y icon-height))
  (values min-x min-y max-x max-y)))




(defun compute-maximum-and-minimum-bounds-for-layer
    (layer variable-spec-list icon-width icon-height)
  (let* ((drawing-elements (drawing-elements-of-layer layer))
	 (icon-min-x icon-width)
	 (icon-min-y icon-height)
	 (icon-max-x 0)
	 (icon-max-y 0))
    (cond
      (drawing-elements
       (multiple-value-setq (icon-min-x icon-min-y icon-max-x icon-max-y)
	 (compute-maximums-and-minimums-for-drawing-elements
	   drawing-elements variable-spec-list
	   icon-min-x icon-min-y icon-max-x icon-max-y
	   icon-width icon-height))
       (values icon-min-x icon-min-y icon-max-x icon-max-y))
      (t					; no elements thus no offsets
       (values 0 0 icon-width icon-height)))))



(defun make-entity-with-icon-description-for-moving-layer
       (icon-editor layer icon-width-in-workspace icon-height-in-workspace
	region-and-name-alist)
  (declare (type fixnum icon-width-in-workspace icon-height-in-workspace))
  (let* ((view-pad (icon-editor-view-pad icon-editor))
	 (label-of-layer (label-of-layer layer))
	 (color-of-layer (get-color-of-region-in-icon-editor
			   icon-editor label-of-layer))
	 (list-of-layers
	   (icon-editor-cons
	     ;(copy-tree-including-leaves-using-icon-editor-conses layer) nil))
	     layer nil))
	 (entity nil)
	 (variable-spec-list
	   (icon-editor-variable-spec-list icon-editor))
	 (background-layer
	   (icon-editor-icon-background-image icon-editor))
	 (stipple-spec
	   (icon-editor-stipple-spec icon-editor)))
    
    (if (or (eq color-of-layer 'white)
	    (eq color-of-layer 'transparent))
	(setf (label-of-layer layer) 'foreground))
    (setq entity
	  (make-entity-with-specific-icon-description
	    'iconic-entity
	    (convert-list-of-layers-to-line-drawing-description
	      list-of-layers region-and-name-alist
	      variable-spec-list
	      background-layer
	      icon-width-in-workspace icon-height-in-workspace
	      (icon-editor-view-pad-x-scale view-pad)
	      (icon-editor-view-pad-y-scale view-pad)
	      t t stipple-spec)
	    icon-width-in-workspace icon-height-in-workspace))
    (reclaim-icon-editor-cons list-of-layers)
    (setf (label-of-layer layer) label-of-layer)
    entity))




(defun create-and-place-icon-of-current-layer-for-view-pad
       (icon-editor layer icon-width icon-height region-and-name-alist)
    (declare (type fixnum icon-width icon-height))
    (let* ((view-pad (icon-editor-view-pad icon-editor)))
    (delete-icon-editor-view-pad-icon-for-current-layer view-pad)
    (let* ((icon-width-in-workspace
	     (delta-x-in-workspace-from-view-pad icon-width view-pad))
	   (icon-height-in-workspace
	     (delta-y-in-workspace-from-view-pad icon-height view-pad))
	   (color-of-layer (get-color-of-region-in-icon-editor
			     icon-editor (label-of-layer layer)))
	   (layer-icon
	     (make-entity-with-icon-description-for-moving-layer
	       icon-editor layer
	       icon-width-in-workspace icon-height-in-workspace
	       region-and-name-alist))
	   (xored-layer-icon?
	     (if (not (or (eq color-of-layer 'white)
			  (eq color-of-layer 'transparent)))
		 (make-entity-with-icon-description-for-moving-layer
		   icon-editor layer
		   icon-width-in-workspace icon-height-in-workspace
		   region-and-name-alist)))
	   (variable-spec-list
	     (cdr (icon-editor-variable-spec-list icon-editor))))
      
      (declare (type fixnum icon-width-in-workspace icon-height-in-workspace))  
      (multiple-value-bind (icon-min-x icon-min-y icon-max-x icon-max-y)
 	  (evaluating-icon-elements (icon-width icon-height variable-spec-list nil)
	    (compute-maximum-and-minimum-bounds-for-layer
	      layer variable-spec-list icon-width icon-height))
	(let* (
	       (min-x-in-workspace
		 (x-in-workspace-from-view-pad icon-min-x view-pad))
	       (min-y-in-workspace
		 (y-in-workspace-from-view-pad icon-min-y view-pad))
	       (max-x-in-workspace
		 (x-in-workspace-from-view-pad icon-max-x view-pad))
	       (max-y-in-workspace
		 (y-in-workspace-from-view-pad icon-max-y view-pad))
;	     (layer-width (-w max-x-in-workspace min-x-in-workspace))
;	     (layer-height (-w max-y-in-workspace min-y-in-workspace))
	       (inner-left-edge
		 (icon-editor-view-pad-x-origin-in-workspace view-pad))
	       (inner-right-edge
		 (+w inner-left-edge
		     (delta-x-in-workspace-from-view-pad
		       icon-width view-pad)))
	       (inner-top-edge
		 (icon-editor-view-pad-y-origin-in-workspace view-pad))
	       (inner-bottom-edge
		 (+w inner-top-edge
		     (delta-y-in-workspace-from-view-pad
		       icon-height view-pad)))
	       (left-edge-of-icon-to-right-edge-of-layer-in-workspace
		 (-w max-x-in-workspace inner-left-edge))
	       (top-edge-of-icon-to-bottom-edge-of-layer-in-workspace
		 (-w max-y-in-workspace inner-top-edge))
	       (left-edge-of-icon-to-left-edge-of-layer-in-workspace
		 (-w min-x-in-workspace inner-left-edge))
	       (top-edge-of-icon-to-top-edge-of-layer-in-workspace
		 (-w min-y-in-workspace inner-top-edge)))
;	(format t "~&l,t,r,b=~a,~a,~a,~a;  ~a,~a~%" inner-left-edge inner-top-edge
;		inner-right-edge inner-bottom-edge
;		(view-pad-width view-pad) (view-pad-height view-pad))
	  ;; The following are limits of movement for the top left hand corner
	  ;; of the layer being moved.  The top, left hand corner starts out
	  ;; as being the same as for the icon in the view pad.
	  (setf (icon-editor-view-pad-left-bound-of-current-layer-in-workspace
		  view-pad)
		(+w 1
		    (-w inner-left-edge
			left-edge-of-icon-to-right-edge-of-layer-in-workspace)))
	  (setf (icon-editor-view-pad-top-bound-of-current-layer-in-workspace
		  view-pad)
		(+w 1
		    (-w inner-top-edge
			top-edge-of-icon-to-bottom-edge-of-layer-in-workspace)))
	  (setf (icon-editor-view-pad-right-bound-of-current-layer-in-workspace
		  view-pad)
		(-w inner-right-edge
		    1
		    left-edge-of-icon-to-left-edge-of-layer-in-workspace))
	  (setf (icon-editor-view-pad-bottom-bound-of-current-layer-in-workspace
		  view-pad)
		(-w inner-bottom-edge
		    1
		    top-edge-of-icon-to-top-edge-of-layer-in-workspace))))
      (setf (icon-editor-view-pad-icon-for-current-layer? view-pad) layer-icon)
      (frame-serial-number-setf (icon-editor-view-pad-serial-number-of-icon-for-current-layer view-pad)
	    (current-frame-serial-number))
      (when xored-layer-icon?
	(setf (icon-editor-view-pad-xored-icon-for-current-layer? view-pad)
	      xored-layer-icon?)
	(add-to-workspace xored-layer-icon?
			  (icon-editor-view-pad-workspace view-pad)
			  (icon-editor-view-pad-x-origin-in-workspace view-pad)
			  (icon-editor-view-pad-y-origin-in-workspace view-pad)
			  t))
      (add-to-workspace layer-icon
			(icon-editor-view-pad-workspace view-pad)
			(icon-editor-view-pad-x-origin-in-workspace view-pad)
			(icon-editor-view-pad-y-origin-in-workspace view-pad)
			t))))





(defun compute-bounded-point-in-workspace
       (cursor-x-in-workspace cursor-y-in-workspace view-pad cursor-x-offset cursor-y-offset)
  (let* ((x-in-workspace
	   (-w cursor-x-in-workspace cursor-x-offset))
	 (y-in-workspace
	   (-w cursor-y-in-workspace cursor-y-offset)))
;    (format t "~&~a:~a,~a,~a:~a : ~a:~a,~a,~a:~a~%"
;	    (view-pad-left-edge view-pad)
;	    (icon-editor-view-pad-left-bound-of-current-layer-in-workspace view-pad) 
;	    x-in-workspace
;	    (icon-editor-view-pad-right-bound-of-current-layer-in-workspace view-pad)
;	    (view-pad-right-edge view-pad)
;	    (view-pad-top-edge view-pad)
;	    (icon-editor-view-pad-top-bound-of-current-layer-in-workspace view-pad)
;	    y-in-workspace
;	    (icon-editor-view-pad-bottom-bound-of-current-layer-in-workspace view-pad)
;	    (view-pad-bottom-edge view-pad)
;	    )
    (values
      (cond
	((<w x-in-workspace 
	     (icon-editor-view-pad-left-bound-of-current-layer-in-workspace view-pad))
	 (+w (icon-editor-view-pad-left-bound-of-current-layer-in-workspace view-pad)
	     cursor-x-offset))
	((>w x-in-workspace
	     (icon-editor-view-pad-right-bound-of-current-layer-in-workspace view-pad))
	 (+w (icon-editor-view-pad-right-bound-of-current-layer-in-workspace view-pad)
	     cursor-x-offset))
	(t
	 cursor-x-in-workspace))
      (cond
	((<w y-in-workspace
	     (icon-editor-view-pad-top-bound-of-current-layer-in-workspace view-pad))
	 (+w (icon-editor-view-pad-top-bound-of-current-layer-in-workspace view-pad)
	     cursor-y-offset))
	((>w y-in-workspace
	     (icon-editor-view-pad-bottom-bound-of-current-layer-in-workspace view-pad))
	 (+w (icon-editor-view-pad-bottom-bound-of-current-layer-in-workspace view-pad)
	     cursor-y-offset))
	(t
	 cursor-y-in-workspace)))))



;;;; Mouse Event Handlers




;;; `Distance-to-snap-points-together-in-view-pad' defines a distance in
;;; view-pad workspace units in which points can be "snapped" (joined)
;;; together when placing points in the view-pad.  This is currently used when
;;; creating polygons.  When the mouse reaches within snapping distance of the
;;; first polygon point, the figure is closed (and completed when the mouse is
;;; pressed).

;(defmacro-for-constant distance-to-snap-points-together-in-view-pad 2)
(defvar  distance-to-snap-points-together-in-view-pad 2)	;Changed for chestnut blm 2/23/91


(defun handle-move-layer-in-xy-plane-in-translator (icon-editor translator)
  (let* ((drawing-elements
	   (drawing-elements-of-layer
	     (icon-editor-engine-current-layer
	       (icon-editor-engine icon-editor)))))
    (cond
      (drawing-elements
       (delete-icon-editor-view-pad-icon-for-current-layer
	 (icon-editor-view-pad icon-editor))
       (setf (icon-editor-translator-state translator)
	     (icon-editor-state 'moving-layer-in-xy-plane))
       (enqueue-icon-editor-visual-event
	 icon-editor
	 (icon-editor-visual-event 'inform-user)
	 (icon-editor-state 'moving-layer-in-xy-plane)
	 nil))
      (t
       (enqueue-icon-editor-visual-event
	 icon-editor
	 (icon-editor-visual-event 'inform-user)
	 (copy-constant-wide-string #w"You can't move an empty layer.")
	 nil)))))




(defun handle-translator-view-pad-mouse-down-event
    (x-in-workspace
      y-in-workspace
      icon-editor
      translator
      state
      state-information?)
  #+development
  (check-memory-for-development 'handle-translator-view-pad-mouse-down-event_0)
  (let* ((view-pad (icon-editor-view-pad icon-editor))
	 (engine (icon-editor-engine icon-editor))
	 (x-in-view-pad (x-in-view-pad x-in-workspace view-pad))
	 (y-in-view-pad (y-in-view-pad y-in-workspace view-pad)))
    (icon-editor-state-case state
      (drawing-point
	(when (point-in-draw-area-of-view-pad-p
		x-in-workspace y-in-workspace engine view-pad)
	  (enqueue-icon-editor-engine-event
	    icon-editor
	    (icon-editor-engine-event 'draw-point)
	    x-in-view-pad
	    y-in-view-pad
	    nil nil)))
      (drawing-points
	(when (and (point-in-draw-area-of-view-pad-p
		     x-in-workspace y-in-workspace engine view-pad)
		   (not
		     (loop for point in state-information?
			   thereis (and (=f (car point) x-in-view-pad)
					(=f (cdr point) y-in-view-pad)))))
	  (enqueue-icon-editor-visual-event
	    icon-editor
	    (icon-editor-visual-event 'put-point-marker-in-view-pad)
	    x-in-view-pad y-in-view-pad)
	  (push-icon-editor-translator-state-information
	    translator
	    (icon-editor-cons x-in-view-pad y-in-view-pad))))

      (drawing-line
	;; only process mouse-down when inside engine (icon) area of the
	;; view-pad.
	(when (point-in-draw-area-of-view-pad-p
		x-in-workspace y-in-workspace engine view-pad)
	  (if state-information?
	      ;; THEN
	      (let* ((x0-in-view-pad
		       (car (first state-information?)))
		     (y0-in-view-pad
		       (cdr (first state-information?))))
		(declare (type fixnum x0-in-view-pad y0-in-view-pad))
		(setf (icon-editor-translator-state-information translator) nil)
		(reclaim-icon-editor-tree state-information?)
		(enqueue-icon-editor-visual-event
		  icon-editor
		  (icon-editor-visual-event 'clear-markers-from-view-pad)
		  nil nil)
		#+development
		(gensym-assert (and (typep x0-in-view-pad 'fixnum)
				    (typep y0-in-view-pad 'fixnum)
				    (typep x-in-view-pad 'fixnum)
				    (typep y-in-view-pad 'fixnum)))
;		(format t "~%~a,~a,~a,~a"
;			x0-in-view-pad y0-in-view-pad x-in-view-pad y-in-view-pad)
		(enqueue-icon-editor-engine-event
		  icon-editor
		  (icon-editor-engine-event 'draw-line)
		  x0-in-view-pad y0-in-view-pad x-in-view-pad y-in-view-pad))
	      ;; ELSE
	      (progn
		(enqueue-icon-editor-visual-event
		  icon-editor
		  (icon-editor-visual-event 'put-cross-marker-in-view-pad)
		  x-in-view-pad
		  y-in-view-pad)
		;; a second cross marker is needed since mouse-motion handler
		;; pops the current marker (the cross or line).
		(enqueue-icon-editor-visual-event
		  icon-editor
		  (icon-editor-visual-event 'put-cross-marker-in-view-pad)
		  x-in-view-pad y-in-view-pad)
		(setf (icon-editor-translator-last-marker-drawn? translator) t)
		(push-icon-editor-translator-state-information
		  translator
		  (icon-editor-cons x-in-view-pad y-in-view-pad))))))

      (drawing-lines
	;; only process mouse-down inside or outsie engine (icon) area of the
	;; view-pad by snapping to limits if outside limits.
	(when (point-in-draw-area-of-view-pad-p
		x-in-workspace y-in-workspace engine view-pad)
;	(multiple-value-setq (x-in-view-pad y-in-view-pad)
;	  (snap-to-limits-of-width-and-height-if-necessary
;	    x-in-view-pad y-in-view-pad
;	    (icon-editor-engine-icon-width engine)
;	    (icon-editor-engine-icon-height engine)))
	  (if state-information?
	      ;; THEN
	      (progn
		(pop-last-marker-if-drawn icon-editor translator)
		(enqueue-icon-editor-visual-event
		  icon-editor
		  (icon-editor-visual-event 'put-line-marker-in-view-pad)
		  (copy-list-using-icon-editor-conses (first state-information?))
		  (icon-editor-cons x-in-view-pad y-in-view-pad))
		;; The interface does the line drawing until line(s) input is
		;; finished.  (Draw information is NOT sent to the engine until
		;; then.)
		(enqueue-icon-editor-visual-event
		  icon-editor
		  (icon-editor-visual-event 'put-cross-marker-in-view-pad)
		  x-in-view-pad y-in-view-pad)
		;; a second cross marker is needed since mouse-motion handler
		;; pops the current marker (the cross or line).
		(enqueue-icon-editor-visual-event
		  icon-editor
		  (icon-editor-visual-event 'put-cross-marker-in-view-pad)
		  x-in-view-pad y-in-view-pad)
		(setf (icon-editor-translator-last-marker-drawn? translator) t)
		(push-icon-editor-translator-state-information
		  translator
		  (icon-editor-cons x-in-view-pad y-in-view-pad)))
	      ;; ELSE
	      (progn
		(enqueue-icon-editor-visual-event
		  icon-editor
		  (icon-editor-visual-event 'put-cross-marker-in-view-pad)
		  x-in-view-pad
		  y-in-view-pad)
		;; a second cross marker is needed since mouse-motion handler
		;; pops the current marker (the cross or line).
		(enqueue-icon-editor-visual-event
		  icon-editor
		  (icon-editor-visual-event 'put-cross-marker-in-view-pad)
		  x-in-view-pad y-in-view-pad)
		(setf (icon-editor-translator-last-marker-drawn? translator) t)
		(push-icon-editor-translator-state-information
		  translator
		  (icon-editor-cons x-in-view-pad y-in-view-pad))))))

      (drawing-arc
	;; test for point within the engine can be removed, when mouse-down
	;; events are no longer sent to the translator!!
	(when (point-in-draw-area-of-view-pad-p x-in-workspace y-in-workspace
						engine view-pad)
	  (if state-information?
	      ;; THEN
	      (if (second state-information?)
		  (progn
		    (enqueue-icon-editor-visual-event
		      icon-editor
		      (icon-editor-visual-event
			'clear-markers-from-view-pad)
		      nil nil)
		    (enqueue-icon-editor-engine-event
		      icon-editor
		      (icon-editor-engine-event 'draw-arc)
		      (first state-information?)
		      (second state-information?)
		      (icon-editor-cons x-in-view-pad y-in-view-pad)
		      nil)
		    
		    ;; only the cons is reclaimed here, since the engine eats
		    ;; its args (e.g, first and second of state-information).
		    (reclaim-icon-editor-cons state-information?)
		    (setf (icon-editor-translator-state-information translator) nil))
		  
		  (progn
		    (enqueue-icon-editor-visual-event
		      icon-editor
		      (icon-editor-visual-event 'put-cross-marker-in-view-pad)
		      x-in-view-pad
		      y-in-view-pad)
		    ;; need 2 crosses, since one is popped when the mouse is moved.
		    ;; (it pops the top marker which is either a cross or an arc.)
		    (enqueue-icon-editor-visual-event
		      icon-editor
		      (icon-editor-visual-event 'put-cross-marker-in-view-pad)
		      x-in-view-pad
		      y-in-view-pad)
		    (enqueue-icon-editor-translator-state-information
		      translator
		      (icon-editor-cons x-in-view-pad y-in-view-pad))))
	      ;; ELSE
	      (progn
		(enqueue-icon-editor-visual-event
		  icon-editor
		  (icon-editor-visual-event 'put-cross-marker-in-view-pad)
		  x-in-view-pad
		  y-in-view-pad)
		(enqueue-icon-editor-translator-state-information
		  translator
		  (icon-editor-cons x-in-view-pad y-in-view-pad))))))
      
      ((drawing-outlined-rectangle
	 drawing-filled-rectangle)
       ;; only process mouse-down inside or outsie engine (icon) area of the
       ;; view-pad by snapping to limits if outside limits.
       
       (if state-information?
	   (progn
	     (multiple-value-setq (x-in-view-pad y-in-view-pad)
	       (snap-to-limits-of-width-and-height-if-necessary
		 x-in-view-pad y-in-view-pad
		 (icon-editor-engine-icon-width engine)
		 (icon-editor-engine-icon-height engine)))
	     (let*  ((x0-in-view-pad (car (first state-information?)))
		     (y0-in-view-pad (cdr (first state-information?)))
		     (x1-in-view-pad x-in-view-pad)
		     (y1-in-view-pad y-in-view-pad))
	       (enqueue-icon-editor-visual-event
		 icon-editor
		 (icon-editor-visual-event
		   'clear-markers-from-view-pad)
		 nil nil)
	       (enqueue-icon-editor-engine-event
		 icon-editor
		 (if (=f state (icon-editor-state 'drawing-outlined-rectangle))
		     (icon-editor-engine-event 'draw-outlined-rectangle)
		     (icon-editor-engine-event 'draw-filled-rectangle))
		 x0-in-view-pad y0-in-view-pad x1-in-view-pad y1-in-view-pad)
	       
	       (reclaim-icon-editor-slot-value state-information?)
	       (setf (icon-editor-translator-state-information translator)
		     nil)))
	   (when (point-in-draw-area-of-view-pad-p
		   x-in-workspace y-in-workspace engine view-pad)
	     (enqueue-icon-editor-visual-event	; first and base +
	       icon-editor
	       (icon-editor-visual-event 'put-cross-marker-in-view-pad)
	       x-in-view-pad			;hack
	       y-in-view-pad)
	     (enqueue-icon-editor-visual-event	; second +
	       icon-editor
	       (icon-editor-visual-event 'put-cross-marker-in-view-pad)
	       x-in-view-pad			;hack
	       y-in-view-pad)
	     (push-icon-editor-translator-state-information
	       translator
	       (icon-editor-cons x-in-view-pad y-in-view-pad)))))
      
      ((drawing-outlined-circle
	 drawing-filled-circle)
       (if state-information?
	   (let*  ((x0-in-view-pad (car (first state-information?)))
		   (y0-in-view-pad (cdr (first state-information?)))
		   (x1-in-view-pad x-in-view-pad)
		   (y1-in-view-pad y-in-view-pad)
		   (radius-in-view-pad (fixnum-vector-distance 
					 (-f x1-in-view-pad x0-in-view-pad)
					 (-f y1-in-view-pad y0-in-view-pad))))
	     (enqueue-icon-editor-visual-event
	       icon-editor
	       (icon-editor-visual-event
		 'clear-markers-from-view-pad)
	       nil nil)
	     (enqueue-icon-editor-engine-event
	       icon-editor
	       (if (=f state (icon-editor-state 'drawing-outlined-circle))
		   (icon-editor-engine-event 'draw-outlined-circle)
		   (icon-editor-engine-event 'draw-filled-circle))
	       x0-in-view-pad y0-in-view-pad radius-in-view-pad nil)
	     
	     (reclaim-icon-editor-slot-value state-information?)
	     (setf (icon-editor-translator-state-information translator)	;hack
		   nil))
	   (when (point-in-draw-area-of-view-pad-p
		   x-in-workspace y-in-workspace engine view-pad)
	     (enqueue-icon-editor-visual-event	; first and base +
	       icon-editor
	       (icon-editor-visual-event 'put-cross-marker-in-view-pad)
	       x-in-view-pad			;hack
	       y-in-view-pad)
	     (enqueue-icon-editor-visual-event	; second +
	       icon-editor
	       (icon-editor-visual-event 'put-cross-marker-in-view-pad)
	       x-in-view-pad			;hack
	       y-in-view-pad)
	     (push-icon-editor-translator-state-information
	       translator
	       (icon-editor-cons x-in-view-pad y-in-view-pad)))))
      
      ((drawing-outlined-polygon
	 drawing-filled-polygon
	 drawing-outlined-filled-polygon)
       ;; only process mouse-down when inside engine (icon) area of the
       ;; view-pad.
       (when (point-in-draw-area-of-view-pad-p
	       x-in-workspace y-in-workspace engine view-pad)
	 (cond
	   (state-information?
	    ;; THEN
	    ;;   If the most recent point has "snapped" to the first point,
	    ;;     (the points are equal) complete the polygon.
	    (cond ((eq (first state-information?) t)	; snapped state
		   (setq state-information? (cdr state-information?))
		   (pop-icon-editor-translator-state-information translator)	; returns t
		   (translator-end-current-state
		     icon-editor translator state state-information? t))
		  
		  ;; Else, the interface does the line drawing until line(s)
		  ;; input is finished.  (Draw information is NOT sent to the
		  ;; engine until then.)
		  
		  (t (pop-last-marker-if-drawn icon-editor translator)
		     (enqueue-icon-editor-visual-event
		       icon-editor
		       (icon-editor-visual-event 'put-line-marker-in-view-pad)
		       (copy-list-using-icon-editor-conses (first state-information?))
		       (icon-editor-cons x-in-view-pad y-in-view-pad))
		     (enqueue-icon-editor-visual-event
		       icon-editor
		       (icon-editor-visual-event 'put-cross-marker-in-view-pad)
		       x-in-view-pad
		       y-in-view-pad)
		     ;; a second cross marker is needed since mouse-motion handler
		     ;; pops the current marker (the cross or line).
		     (enqueue-icon-editor-visual-event
		       icon-editor
		       (icon-editor-visual-event 'put-cross-marker-in-view-pad)
		       x-in-view-pad
		       y-in-view-pad)
		     (setf (icon-editor-translator-last-marker-drawn? translator) t)
		     (push-icon-editor-translator-state-information
		       translator
		       (icon-editor-cons x-in-view-pad y-in-view-pad)))))
	   (t
	    ;; ELSE
	    (enqueue-icon-editor-visual-event
	      icon-editor
	      (icon-editor-visual-event 'put-cross-marker-in-view-pad)
	      x-in-view-pad
	      y-in-view-pad)
	    ;; a second cross marker is needed, since the mouse-motion handler
	    ;; pops the top marker (which is a cross or a marker).
	    (enqueue-icon-editor-visual-event
	      icon-editor
	      (icon-editor-visual-event 'put-cross-marker-in-view-pad)
	      x-in-view-pad
	      y-in-view-pad)
	    (setf (icon-editor-translator-last-marker-drawn? translator) t)
	    (push-icon-editor-translator-state-information
	      translator
	      (icon-editor-cons x-in-view-pad y-in-view-pad))))))

      (moving-layer-in-xy-plane			; consider putting "waiting" here
	(if (=f state (icon-editor-state 'waiting))
	    (handle-move-layer-in-xy-plane-in-translator icon-editor translator)
	    (enqueue-icon-editor-visual-event
	      icon-editor
	      (icon-editor-visual-event 'inform-user)
	      (icon-editor-state 'moving-layer-in-xy-plane)
	      nil))
	;; The state-information is in the form ((x1 . y1) (xoffset . yoffset)).
	;; We will update the icon representation as the user has moved the layer.
	;; If state information is nil, then we do not have a layer picked.
	(when (point-in-draw-area-of-view-pad-p
		x-in-workspace y-in-workspace engine view-pad)
	  (let* ((view-pad (icon-editor-view-pad icon-editor)) 
		 (engine (icon-editor-engine icon-editor))
		 (current-layer (icon-editor-engine-current-layer engine)))
	    (when (null state-information?)
	      (push-icon-editor-translator-state-information	; store offset
		translator
		(icon-editor-cons
		  (-w x-in-workspace
		      (icon-editor-view-pad-x-origin-in-workspace view-pad))
		  (-w y-in-workspace
		      (icon-editor-view-pad-y-origin-in-workspace view-pad))))
	      (push-icon-editor-translator-state-information	; store offset
		translator
		(icon-editor-cons x-in-workspace y-in-workspace)))
	    (create-and-place-icon-of-current-layer-for-view-pad
	      icon-editor current-layer
	      (icon-editor-engine-icon-width engine)
	      (icon-editor-engine-icon-height engine)
	      (icon-editor-region-and-name-alist icon-editor)))))))
  #+development
  (check-memory-for-development 'handle-translator-view-pad-mouse-down-event_99))






(defun translator-end-moving-layer-in-xy-plane
       (icon-editor translator state-information?)
  (delete-icon-editor-view-pad-icon-for-current-layer
    (icon-editor-view-pad icon-editor))
  ;; The state-information is in the form ((x1 . y1-in-workspace) (xoffset . yoffset))
  ;; or ((xoffset . yoffset)).  In former case, we will update the icon 
  ;; representation as the user has moved the layer, and in the latter case,
  ;; we will not, as the user has not yet picked up the layer.  If state
  ;; information is nil, then we do not have a layer picked.
  (when (cdr state-information?)
    (let* ((view-pad (icon-editor-view-pad icon-editor))
	   (new-coord (first state-information?))
	   (offset-coord (second state-information?))
	   (x-offset-in-workspace (car offset-coord))
	   (y-offset-in-workspace (cdr offset-coord)))
      (multiple-value-bind (new-x-in-workspace new-y-in-workspace)
	  (compute-bounded-point-in-workspace
	    (car new-coord) (cdr new-coord) view-pad
	    x-offset-in-workspace y-offset-in-workspace)
	(let* ((new-delta-x-in-workspace
		 (-w new-x-in-workspace
		     (icon-editor-view-pad-x-origin-in-workspace view-pad)))
	       (new-delta-y-in-workspace
		 (-w new-y-in-workspace
		     (icon-editor-view-pad-y-origin-in-workspace view-pad))))
	  (when (or (/=w new-delta-x-in-workspace x-offset-in-workspace)
		    (/=f new-delta-y-in-workspace y-offset-in-workspace))
	    (enqueue-icon-editor-engine-event
	      icon-editor
	      (icon-editor-engine-event 'move-layer-in-xy-plane)
	      (delta-x-in-view-pad (-w new-delta-x-in-workspace
				       x-offset-in-workspace)
				   view-pad)
	      (delta-y-in-view-pad (-w new-delta-y-in-workspace
				       y-offset-in-workspace)
				   view-pad)
	      nil nil))))))
  (clear-icon-editor-translator-state-information translator))






(defun-substitution-macro handle-translator-view-pad-mouse-up-event
    (x-in-workspace 
      y-in-workspace 
      icon-editor
      translator
      state
      state-information?)
  translator
  (let* ()
    (icon-editor-state-case state
      #+drag-to-draw
      ((drawing-outlined-rectangle
	 drawing-filled-rectangle)
       ;; only process mouse-up when inside engine (icon) area of the
       ;; view-pad.
       (when state-information?
	 ;; only process mouse-down inside or outsie engine (icon) area of the
	 ;; view-pad by snapping to limits if outside limits.
	 (let*  ((x0-in-view-pad (car (first state-information?)))
		 (y0-in-view-pad (cdr (first state-information?)))
		 (x1-in-view-pad (x-in-view-pad x-in-workspace view-pad))
		 (y1-in-view-pad (y-in-view-pad y-in-workspace view-pad)))
	   (multiple-value-setq (x1-in-view-pad y1-in-view-pad)
	     (snap-to-limits-of-width-and-height-if-necessary
	       x1-in-view-pad y1-in-view-pad
	       (icon-editor-engine-icon-width engine)
	       (icon-editor-engine-icon-height engine)))
	   (enqueue-icon-editor-visual-event
	     icon-editor
	     (icon-editor-visual-event
	       'clear-markers-from-view-pad)
	     nil nil)
	   (enqueue-icon-editor-engine-event
	     icon-editor
	     (if (=f state (icon-editor-state 'drawing-outlined-rectangle))
		 (icon-editor-engine-event 'draw-outlined-rectangle)
		 (icon-editor-engine-event 'draw-filled-rectangle))
	     x0-in-view-pad y0-in-view-pad x1-in-view-pad y1-in-view-pad)
	   
	   ;; only the cons is reclaimed here, since the engine eats
	   ;; its args (e.g, first and second of state-information).
	   (reclaim-icon-editor-cons state-information?)
	   (setf (icon-editor-translator-state-information translator)
		 nil))))
      #+drag-to-draw
      ((drawing-outlined-circle
	 drawing-filled-circle)
       (when state-information?
	 (let*  ((x0-in-view-pad (car (first state-information?)))
		 (y0-in-view-pad (cdr (first state-information?)))
		 (x1-in-view-pad (x-in-view-pad x-in-workspace view-pad))
		 (y1-in-view-pad (y-in-view-pad y-in-workspace view-pad))
		 (radius-in-view-pad (fixnum-vector-distance 
				       (-f x1-in-view-pad x0-in-view-pad)
				       (-f y1-in-view-pad y0-in-view-pad))))
	   (enqueue-icon-editor-visual-event
	     icon-editor
	     (icon-editor-visual-event
	       'clear-markers-from-view-pad)
	     nil nil)
	   (enqueue-icon-editor-engine-event
	     icon-editor
	     (if (=f state (icon-editor-state 'drawing-outlined-circle))
		 (icon-editor-engine-event 'draw-outlined-circle)
		 (icon-editor-engine-event 'draw-filled-circle))
	     x0-in-view-pad y0-in-view-pad radius-in-view-pad nil)
	   
	   ;; only the cons is reclaimed here, since the engine eats
	   ;; its args (e.g, first and second of state-information).
	   (reclaim-icon-editor-cons state-information?)
	   (setf (icon-editor-translator-state-information translator) ;hack
		 nil))))
      (moving-layer-in-xy-plane
	;;
	;; MORE WORK HERE:  CHECK FOR BOUNDS, SNAP IF REQUIRED
	;;
	(when (cdr state-information?)
	  (let* ((new-coord (first state-information?)))
	    (setf (car new-coord) x-in-workspace)
	    (setf (cdr new-coord) y-in-workspace)))
	(translator-end-moving-layer-in-xy-plane
	  icon-editor translator state-information?)))))









;;;; Events Translator




#+development
(defvar last-iconic-entity)




;;; The function `enqueue-icon-editor-translator-event' ...
;;; Eat the argument (eg. (x . y)) using icon-editor-cons.

#+development
(eval-when (:compile-toplevel :load-toplevel :execute)
  (delete-feature :ignore-view-pad-limits))


(defun enqueue-icon-editor-translator-event (icon-editor 
					     translator-event arg-1? arg-2?)
  #+development (assert (and (icon-editor-p icon-editor)
			     (icon-editor-translator-event-p translator-event)))
  #+development
  (check-memory-for-development 'enqueue-icon-editor-translator-event_0)
   (let* ((translator
	   (icon-editor-translator icon-editor))
	 (state 
	   (icon-editor-translator-state translator)))
    (when (or (/=f state (icon-editor-state 'in-layers-pad))
	      (handle-layers-pad-translator-event
		icon-editor translator-event arg-1? arg-2?))
      
      (let ((state-information?
	       (icon-editor-translator-state-information translator)))
	
	#+development (assert (icon-editor-state-p state))
	(icon-editor-translator-event-case translator-event
	  
	  (mouse-motion				       ;args: x-in-workspace,
						       ; y-in-workspace
	    ;; Mouse motion should be handled in-line here for the fastest
	    ;; possible response.
	    (let* ((view-pad (icon-editor-view-pad icon-editor))
		   (engine (icon-editor-engine icon-editor)))
	      (enqueue-icon-editor-visual-event
		icon-editor
		(icon-editor-visual-event 'change-x-y-position-box-values)
		(x-in-view-pad arg-1? view-pad)
		(y-in-view-pad arg-2? view-pad))

	      (icon-editor-state-case state
		  
		  ((drawing-line drawing-lines)
		   ;; move marker only when inside engine (icon) area of the
		   ;; view-pad.
		   (when state-information?
		     (let*  ((x0-in-view-pad (car (first state-information?)))
			     (y0-in-view-pad (cdr (first state-information?)))
			     (point-in-view-pad?
			       (point-in-draw-area-of-view-pad-p
				 arg-1? arg-2? engine view-pad))
			     (x1-in-view-pad
			       (x-in-view-pad
				 (clip-x-in-workspace-to-engine
				   arg-1? engine view-pad)
				 view-pad))
			     (y1-in-view-pad
			       (y-in-view-pad
				 (clip-y-in-workspace-to-engine
				   arg-2? engine view-pad)
				 view-pad)))
		       (pop-last-marker-if-drawn icon-editor translator)

		       #+ignore-view-pad-limits
		       (setq point-in-view-pad? t)

		       (if point-in-view-pad?
			   (progn
			     (enqueue-icon-editor-visual-event
			       icon-editor
			       (icon-editor-visual-event
				 'put-line-marker-in-view-pad)
			       (icon-editor-cons x0-in-view-pad y0-in-view-pad)
			       (icon-editor-cons x1-in-view-pad y1-in-view-pad))
			     (setf (icon-editor-translator-last-marker-drawn?
				     translator) t))
			   (setf (icon-editor-translator-last-marker-drawn?
				     translator) nil)))))

		  ((drawing-outlined-polygon
		     drawing-filled-polygon
		     drawing-outlined-filled-polygon)
		    ;; move marker only when inside engine (icon) area of the
		    ;; view-pad.
		   (when state-information?
		     (when (eq (first state-information?) t)   ; snapped state
		       (pop-last-marker-if-drawn icon-editor translator)
		       (setq state-information? (cdr state-information?))
		       ;; pop the snapping state
		       (pop-icon-editor-translator-state-information translator))

		     (let*  ((x0-in-view-pad (car (first state-information?)))
			     (y0-in-view-pad (cdr (first state-information?)))
			     (point-in-view-pad?
			       (point-in-draw-area-of-view-pad-p
				 arg-1? arg-2? engine view-pad))
			     (x1-in-view-pad
				(x-in-view-pad (clip-x-in-workspace-to-engine
						 arg-1? engine view-pad)
					       view-pad))
			     (y1-in-view-pad
				(y-in-view-pad (clip-y-in-workspace-to-engine
						 arg-2? engine view-pad)
					       view-pad)))
		       (if (or point-in-view-pad?
			       (and (not point-in-view-pad?)
				    (neq (icon-editor-translator-last-marker-drawn?
					   translator)
					 'special)))
			   (enqueue-icon-editor-visual-event
			     icon-editor	; pop last cross/line marker
			     (icon-editor-visual-event 'pop-marker-from-view-pad)
			     nil nil))
		       (if point-in-view-pad?
			   (progn
			     (when (icon-editor-snapping-on? icon-editor)
			       (let* ((first-point (first (last state-information?)))
				      (xn-in-view-pad (car first-point))
				      (yn-in-view-pad (cdr first-point)))
				 (when (and (<=f (absf (-f xn-in-view-pad
							   x1-in-view-pad))
						 distance-to-snap-points-together-in-view-pad)
					    (<=f (absf (-f yn-in-view-pad
							   y1-in-view-pad))
						 distance-to-snap-points-together-in-view-pad))
				   (setq x1-in-view-pad xn-in-view-pad
					 y1-in-view-pad yn-in-view-pad)
				   (push-icon-editor-translator-state-information
				     translator t)
				   (enqueue-icon-editor-visual-event
				     icon-editor
				     (icon-editor-visual-event 'put-cross-marker-in-view-pad)
				     x1-in-view-pad
				     y1-in-view-pad))))
			     (enqueue-icon-editor-visual-event
			       icon-editor
			       (icon-editor-visual-event 'put-line-marker-in-view-pad)
			       (icon-editor-cons x0-in-view-pad y0-in-view-pad)
			       (icon-editor-cons x1-in-view-pad y1-in-view-pad))
			     (setf (icon-editor-translator-last-marker-drawn?
				     translator) t))
			   (when (neq (icon-editor-translator-last-marker-drawn?
					translator)
				      'special)
			      (let* ((first-point
				       (if (or (null (cdr state-information?))	; length < 2
					       (cddr state-information?))	; if length > 2
					   (first (last state-information?))
					   (first state-information?)))
				     (xn-in-view-pad (car first-point))
				     (yn-in-view-pad (cdr first-point)))
				(enqueue-icon-editor-visual-event
				  icon-editor
				  (icon-editor-visual-event 'put-line-marker-in-view-pad)
				  (icon-editor-cons x0-in-view-pad y0-in-view-pad)
				  (icon-editor-cons xn-in-view-pad yn-in-view-pad))
				(setf (icon-editor-translator-last-marker-drawn? translator)
				      'special)))))))
		  
		  (drawing-arc
		    (when (second state-information?)
		      ;; if there are already 2 arc points placed on the viewpad
		      (let*  ((x0-in-view-pad (car (first state-information?)))
			      (y0-in-view-pad (cdr (first state-information?)))
			      (x1-in-view-pad (car (second state-information?)))
			      (y1-in-view-pad (cdr (second state-information?)))
			      (x2-in-view-pad
				(x-in-view-pad (clip-x-in-workspace-to-engine
						 arg-1? engine view-pad)
					       view-pad))
			      (y2-in-view-pad
				(y-in-view-pad (clip-y-in-workspace-to-engine
						 arg-2? engine view-pad)
					       view-pad)))
			(enqueue-icon-editor-visual-event
			  icon-editor		; pop last cross/arc marker
			  (icon-editor-visual-event 'pop-marker-from-view-pad)
			  nil nil)
			(enqueue-icon-editor-visual-event
			  icon-editor
			  (icon-editor-visual-event
			    'put-arc-marker-in-view-pad)
			  (icon-editor-list 
			    (icon-editor-cons x0-in-view-pad y0-in-view-pad)
			    (icon-editor-cons x1-in-view-pad y1-in-view-pad))
			  (icon-editor-cons x2-in-view-pad y2-in-view-pad)))))

		  ((drawing-outlined-rectangle
		     drawing-filled-rectangle
		     drawing-outlined-filled-rectangle)
		    ;; move marker only when inside engine (icon) area of the
		    ;; view-pad.
		   (when state-information?
		     (let*  ((x0-in-view-pad (car (first state-information?)))
			     (y0-in-view-pad (cdr (first state-information?)))
			     (x1-in-view-pad
			       #+ignore-view-pad-limits
			       (x-in-view-pad arg-1? view-pad)
			       #-ignore-view-pad-limits
			       (x-in-view-pad (clip-x-in-workspace-to-engine
						arg-1? engine view-pad)
					      view-pad)
			       )
			     (y1-in-view-pad
			       #+ignore-view-pad-limits
			       (y-in-view-pad arg-2? view-pad)
			       #-ignore-view-pad-limits
			       (y-in-view-pad (clip-y-in-workspace-to-engine
						arg-2? engine view-pad)
					      view-pad)
				))
		       (enqueue-icon-editor-visual-event
			 icon-editor		       ; pop last rectangle/cross marker
			 (icon-editor-visual-event 'pop-marker-from-view-pad)
			 nil nil)
		       (enqueue-icon-editor-visual-event
			 icon-editor
			 (icon-editor-visual-event 'put-rectangle-marker-in-view-pad)
			 (icon-editor-cons x0-in-view-pad y0-in-view-pad)
			 (icon-editor-cons x1-in-view-pad y1-in-view-pad)))))

		  ((drawing-outlined-circle
		     drawing-filled-circle
		     drawing-outlined-filled-circle)
		   (when state-information?
		     (let*  ((x0-in-view-pad (car (first state-information?)))
			     (y0-in-view-pad (cdr (first state-information?)))
			     (x1-in-view-pad (x-in-view-pad arg-1? view-pad))
			     (y1-in-view-pad (y-in-view-pad arg-2? view-pad))
			     (radius-in-view-pad (fixnum-vector-distance
						   (-f x1-in-view-pad x0-in-view-pad)
						   (-f y1-in-view-pad y0-in-view-pad))))
		       (enqueue-icon-editor-visual-event
			 icon-editor		       ; pop last circle/cross marker
			 (icon-editor-visual-event 'pop-marker-from-view-pad)
			 nil nil)
		       (enqueue-icon-editor-visual-event
			 icon-editor
			 (icon-editor-visual-event 'put-circle-marker-in-view-pad)
			 (icon-editor-cons x0-in-view-pad y0-in-view-pad)
			 radius-in-view-pad))))
		  (moving-layer-in-xy-plane
		    (handle-mouse-motion-for-moving-layer
		      icon-editor view-pad state translator state-information?
		      arg-1? arg-2?)))))
	  
	  (change-icon-width-from-bounding-box	       ; args: new-unscaled-width, nil
	    (let* ((view-pad (icon-editor-view-pad icon-editor))
		   (new-width (delta-x-in-view-pad arg-1? view-pad)))
	      (when (not (= new-width (icon-editor-engine-icon-width
					(icon-editor-engine icon-editor))))
		(when (<=f new-width 0)
		  (setq new-width 1)
		  (enqueue-icon-editor-visual-event
		    icon-editor
		    (icon-editor-visual-event 
		      'change-view-pad-bounding-box-width)
		    (delta-x-in-workspace-from-view-pad
		      new-width (icon-editor-view-pad icon-editor))
		    nil))
		(enqueue-icon-editor-visual-event
		  icon-editor
		  (icon-editor-visual-event 'change-width-in-table)
		  new-width nil)
		(enqueue-icon-editor-engine-event
		  icon-editor
		  (icon-editor-engine-event 'change-icon-width)
		  new-width nil nil nil))))
	  
	  ;; Change height and with should be in-line for speed
	  (change-icon-height-from-bounding-box	       ; args: new-unscaled-height, nil
	    (let* ((view-pad (icon-editor-view-pad icon-editor))
		   (new-height (delta-y-in-view-pad arg-1? view-pad)))
	      (when (not (=f new-height (icon-editor-engine-icon-height
					  (icon-editor-engine icon-editor))))
		(when (<=f new-height 0)
		  (setq new-height 1)
		  (enqueue-icon-editor-visual-event
		    icon-editor
		    (icon-editor-visual-event 
		      'change-view-pad-bounding-box-height)
		    (delta-y-in-workspace-from-view-pad
		      new-height (icon-editor-view-pad icon-editor))
		    nil))
		(enqueue-icon-editor-visual-event
		  icon-editor
		  (icon-editor-visual-event 'change-height-in-table)
		  new-height nil)
		(enqueue-icon-editor-engine-event
		  icon-editor
		  (icon-editor-engine-event 'change-icon-height)
		  new-height nil nil nil))))

	  (end-changing-icon-size-from-bounding-box
	    (enqueue-icon-editor-engine-event
	      icon-editor
	      (icon-editor-engine-event 'end-changing-icon-size)
	      nil nil nil nil))

	  (change-icon-width-from-table		       ; args: new-scaled-width, nil
	    (translator-end-current-state
	      icon-editor translator state state-information?)
	    (when (not (=w arg-1? (icon-editor-engine-icon-width
				    (icon-editor-engine icon-editor))))
	      (enqueue-icon-editor-visual-event
		icon-editor
		(icon-editor-visual-event 'change-view-pad-bounding-box-width)
		(delta-x-in-workspace-from-view-pad arg-1? (icon-editor-view-pad icon-editor))
		nil)
	      (enqueue-icon-editor-engine-event
		icon-editor
		(icon-editor-engine-event 'change-icon-width)
		arg-1? nil nil nil)
	      (enqueue-icon-editor-engine-event
		icon-editor
		(icon-editor-engine-event 'end-changing-icon-size)
		nil nil nil nil)))
	  
	  (change-icon-height-from-table	       ; args: new-scaled-height, nil
	    (translator-end-current-state
	      icon-editor translator state state-information?)
	    (when (not (=w arg-1? (icon-editor-engine-icon-height
				    (icon-editor-engine icon-editor))))
	      (enqueue-icon-editor-visual-event
		icon-editor
		(icon-editor-visual-event 'change-view-pad-bounding-box-height)
		(delta-y-in-workspace-from-view-pad arg-1? (icon-editor-view-pad icon-editor))
		nil)
	      (enqueue-icon-editor-engine-event
		icon-editor
		(icon-editor-engine-event 'change-icon-height)
		arg-1? nil nil nil)
	      (enqueue-icon-editor-engine-event
		icon-editor
		(icon-editor-engine-event 'end-changing-icon-size)
		nil nil nil nil)))
	  
	  (change-icon-size-from-engine		       ; args: icon-width, icon-height
	    (enqueue-icon-editor-visual-event
	      icon-editor
	      (icon-editor-visual-event 'change-view-pad-bounding-box-width)
	      (delta-x-in-workspace-from-view-pad arg-1? (icon-editor-view-pad icon-editor))
	      nil)
	    (enqueue-icon-editor-visual-event
	      icon-editor
	      (icon-editor-visual-event 'change-view-pad-bounding-box-height)
	      (delta-y-in-workspace-from-view-pad arg-2? (icon-editor-view-pad icon-editor))
	      nil)
	    (enqueue-icon-editor-visual-event
	      icon-editor
	      (icon-editor-visual-event 'change-width-in-table) arg-1? nil)
	    (enqueue-icon-editor-visual-event
	      icon-editor
	      (icon-editor-visual-event 'change-height-in-table) arg-2? nil))

	  ((view-pad-mouse-up non-view-pad-mouse-up)	; args: x-in-workspace, y-in-workspace
	   (handle-translator-view-pad-mouse-up-event
	     arg-1? arg-2? icon-editor translator state state-information?))

	  ((view-pad-mouse-down			       ; args: x-in-workspace, y-in-workspace
	     non-pad-mouse-down
	     )
	    (handle-translator-view-pad-mouse-down-event
	      arg-1? arg-2? icon-editor translator state state-information?)) 

	  (layers-pad-mouse-down		       ; args: x-in-workspace, y-in-workspace
	    (if (=f state (icon-editor-state 'moving-layer-in-xy-plane))
		(progn
		  (clear-icon-editor-translator-state-information translator)
		  (setq state (icon-editor-translator-state translator))
		  (setq state-information?
			(icon-editor-translator-state-information translator)))
		(translator-end-current-state
		  icon-editor translator state state-information?))
	    (handle-layers-pad-translator-event icon-editor translator-event
						arg-1? arg-2?))

	  (end-editing				       ; no args
	    (translator-end-current-state
	      icon-editor translator state state-information?)
	    (enqueue-icon-editor-engine-event
	      icon-editor
	      (icon-editor-engine-event 'end-editing)
	      nil nil nil nil))
	  (cancel-editing				       ; no args
	    (translator-cancel-current-state
	      icon-editor translator state state-information?)
	    (enqueue-icon-editor-engine-event
	      icon-editor
	      (icon-editor-engine-event 'cancel-editing)
	      nil nil nil nil))

	  ((view-pad-scale-1-to-1 view-pad-scale-2-to-1 view-pad-scale-3-to-1)
	   ;; NOTE:
	   ;; Must clear marker stack here and end or cancel previous drawing state.
	   ;; -pto 01oct89

	   (translator-end-current-state
	     icon-editor translator state state-information?)

	   (let* ((scale (*f (icon-editor-normalized-scale-factor)
			     (icon-editor-translator-event-case translator-event
			       (view-pad-scale-1-to-1 1)
			       (view-pad-scale-2-to-1 2)
			       (view-pad-scale-3-to-1 3)
			       (otherwise 0))))
		  (view-pad (icon-editor-view-pad icon-editor)))
	     (setf (icon-editor-view-pad-x-scale view-pad) scale)
	     (setf (icon-editor-view-pad-y-scale view-pad) scale))
	   (let* ((engine (icon-editor-engine icon-editor)))
	     (enqueue-icon-editor-translator-event
	       icon-editor			       ; cheat here by not going thru
						       ;   the engine
	       (icon-editor-translator-event 'change-icon-size-from-engine)
	       (icon-editor-engine-icon-width engine)
	       (icon-editor-engine-icon-height engine))
	     (enqueue-icon-editor-visual-event
	       icon-editor
	       (icon-editor-visual-event 'redraw-view-pad-icon)
	       nil nil)))
	  (redraw
	    (enqueue-icon-editor-visual-event
	      icon-editor
	      (icon-editor-visual-event 'redraw-view-pad-icon)
	      nil nil)
	    (enqueue-icon-editor-visual-event
	      icon-editor
	      (icon-editor-visual-event 'resize-layer-boxes-if-necessary)
	      nil nil))
	  
	  (draw-points
	    (translator-end-current-state
	      icon-editor translator state state-information?)
	    (setf (icon-editor-translator-state translator)
		  (icon-editor-state 'drawing-points))
	    (enqueue-icon-editor-visual-event 
	      icon-editor
	      (icon-editor-visual-event 'inform-user)
	      (icon-editor-state 'drawing-points)
	      nil))
	  
	  (draw-line
	    (translator-end-current-state
	      icon-editor translator state state-information?)
	    (setf (icon-editor-translator-state translator)
		  (icon-editor-state 'drawing-line))
	    (enqueue-icon-editor-visual-event 
	      icon-editor
	      (icon-editor-visual-event 'inform-user)
	      (icon-editor-state 'drawing-line)
	      nil))
	  (draw-lines
	    (translator-end-current-state
	      icon-editor translator state state-information?)
	    (setf (icon-editor-translator-state translator)
		  (icon-editor-state 'drawing-lines))
	    (enqueue-icon-editor-visual-event 
	      icon-editor
	      (icon-editor-visual-event 'inform-user)
	      (icon-editor-state 'drawing-lines)
	      nil))
	  
	  (draw-arc
	    (translator-end-current-state
	      icon-editor translator state state-information?)
	    (setf (icon-editor-translator-state translator)
		  (icon-editor-state 'drawing-arc))
	    (enqueue-icon-editor-visual-event 
	      icon-editor
	      (icon-editor-visual-event 'inform-user)
	      (icon-editor-state 'drawing-arc)
	      nil))
	  
	  (draw-outlined-rectangle
	    (translator-end-current-state
	      icon-editor translator state state-information?)
	    (setf (icon-editor-translator-state translator)
		  (icon-editor-state 'drawing-outlined-rectangle))
	    (enqueue-icon-editor-visual-event 
	      icon-editor
	      (icon-editor-visual-event 'inform-user)
	      (icon-editor-state 'drawing-outlined-rectangle)
	      nil))
	  
	  (draw-outlined-polygon
	    (translator-end-current-state
	      icon-editor translator state state-information?)
	    (setf (icon-editor-translator-state translator)
		  (icon-editor-state 'drawing-outlined-polygon))
	    (enqueue-icon-editor-visual-event 
	      icon-editor
	      (icon-editor-visual-event 'inform-user)
	      (icon-editor-state 'drawing-outlined-polygon)
	      nil))
	  
	  (draw-outlined-circle
	    (translator-end-current-state
	      icon-editor translator state state-information?)
	    (setf (icon-editor-translator-state translator)
		  (icon-editor-state 'drawing-outlined-circle))
	    (enqueue-icon-editor-visual-event 
	      icon-editor
	      (icon-editor-visual-event 'inform-user)
	      (icon-editor-state 'drawing-outlined-circle)
	      nil))
	  
	  (draw-filled-rectangle
	    (translator-end-current-state
	      icon-editor translator state state-information?)
	    (setf (icon-editor-translator-state translator)
		  (icon-editor-state 'drawing-filled-rectangle))
	    (enqueue-icon-editor-visual-event 
	      icon-editor
	      (icon-editor-visual-event 'inform-user)
	      (icon-editor-state 'drawing-filled-rectangle)
	      nil))
	  
	  (draw-filled-polygon
	    (translator-end-current-state
	      icon-editor translator state state-information?)
	    (setf (icon-editor-translator-state translator)
		  (icon-editor-state 'drawing-filled-polygon))
	    (enqueue-icon-editor-visual-event 
	      icon-editor
	      (icon-editor-visual-event 'inform-user)
	      (icon-editor-state 'drawing-filled-polygon)
	      nil))
	  
	  (draw-filled-circle
	    (translator-end-current-state
	      icon-editor translator state state-information?)
	    (setf (icon-editor-translator-state translator)
		  (icon-editor-state 'drawing-filled-circle))
	    (enqueue-icon-editor-visual-event 
	      icon-editor
	      (icon-editor-visual-event 'inform-user)
	      (icon-editor-state 'drawing-filled-circle)
	      nil))
	  
;	  (draw-outlined-filled-rectangle
;	    (translator-end-current-state
;	      icon-editor translator state state-information?)
;	    (enqueue-icon-editor-visual-event 
;	      icon-editor
;	      (icon-editor-visual-event 'inform-user)
;	      (icon-editor-state 'drawing-outlined-filled-rectangle)
;	      nil))
	  
;	  (draw-outlined-filled-polygon
;	    (translator-end-current-state
;	      icon-editor translator state state-information?)
;	    (setf (icon-editor-translator-state translator)
;		  (icon-editor-state 'drawing-outlined-filled-polygon))
;	    (enqueue-icon-editor-visual-event 
;	      icon-editor
;	      (icon-editor-visual-event 'inform-user)
;	      (icon-editor-state 'drawing-outlined-filled-polygon)
;	      nil))
	  
;	  (draw-outlined-filled-circle
;	    (translator-end-current-state
;	      icon-editor translator state state-information?)
;	    (setf (icon-editor-translator-state translator)
;		  (icon-editor-state 'drawing-outlined-circle))
;	    (enqueue-icon-editor-visual-event 
;	      icon-editor
;	      (icon-editor-visual-event 'inform-user)
;	      (icon-editor-state 'drawing-outlined-filled-circle)
;	      nil))
	  
	  (delete-most-recent-drawing-element
	    (when (=f state (icon-editor-state 'moving-layer-in-xy-plane))
	      (translator-cancel-current-state
		icon-editor translator state state-information?)
	      (setq state (icon-editor-translator-state translator))
	      (setq state-information?
		    (icon-editor-translator-state-information translator)))
	    (if (null state-information?)
		(enqueue-icon-editor-engine-event
		  icon-editor
		  (icon-editor-engine-event 'delete-most-recent-drawing-element)
		  arg-1? nil nil nil))
	    (translator-cancel-current-state
	      icon-editor translator state state-information?))

	  (outside-event
;      #+development
;      (if (not (key-code-equivalent-p arg-1? 'mouse-motion))
;	  (format t "~%Icon Editor:  An outside event (~a) occurred."
;		  arg-1?))
						       ; HACK:
	    (progn
	      ;; ignore the event (e.g., key press)
;
;	      	      (translator-end-current-state
;		icon-editor translator state state-information?)
;	      (setf (icon-editor-translator-state translator)
;		    (icon-editor-state 'waiting))	       ;hack
;	      (enqueue-icon-editor-visual-event 
;		icon-editor
;		(icon-editor-visual-event 'inform-user)
;		(icon-editor-state 'waiting)
;		nil)
	      )
	    )
	  
	  (show-grid
	    (translator-end-current-state
	      icon-editor translator state state-information?)
	    (enqueue-icon-editor-visual-event
	      icon-editor (icon-editor-visual-event 'show-grid) nil nil))
	  
	  (hide-grid
	    (translator-end-current-state
	      icon-editor translator state state-information?)
	    (enqueue-icon-editor-visual-event
	      icon-editor (icon-editor-visual-event 'hide-grid) nil nil))
	  
	  (new-layer
	    (translator-end-current-state
	      icon-editor translator state state-information?)
	    (enqueue-icon-editor-engine-event
	      icon-editor
	      (icon-editor-engine-event 'new-layer)
	      arg-1? nil nil nil))
	  
	  (done-drawing-element
	    (translator-end-current-state
	      icon-editor translator state state-information?))
	  
	  (set-main-color			       ; args: new-color, nil
						       ; cancel current state???
	    (enqueue-icon-editor-engine-event
	      icon-editor
	      (icon-editor-engine-event 'set-main-color)
	      arg-1? nil nil nil))
	  (set-main-region			       ;cancel current state???
	    (enqueue-icon-editor-engine-event
	      icon-editor
	      (icon-editor-engine-event 'set-main-region)
	      arg-1? nil nil nil))
	  (group
	    (translator-end-current-state
	      icon-editor translator state state-information?)
	    (enqueue-icon-editor-engine-event
	      icon-editor
	      (icon-editor-engine-event 'group) nil nil nil nil))
	  (ungroup-current-layer
	    (translator-end-current-state
	      icon-editor translator state state-information?)
	    (enqueue-icon-editor-engine-event
	      icon-editor
	      (icon-editor-engine-event 'ungroup-current-layer) nil nil nil nil))
	  (delete-current-layer
	    (translator-cancel-current-state
	      icon-editor translator state state-information?)
	    (enqueue-icon-editor-engine-event
	      icon-editor
	      (icon-editor-engine-event 'delete-current-layer) nil nil nil nil))
	  (change-current-layer-to-layer-above
	    (translator-end-current-state
	      icon-editor translator state state-information?)
	    (enqueue-icon-editor-engine-event
	      icon-editor
	      (icon-editor-engine-event 'change-current-layer-to-layer-above)
	      nil nil nil nil))
	  (change-current-layer-to-layer-below
	    (translator-end-current-state
	      icon-editor translator state state-information?)
	    (enqueue-icon-editor-engine-event
	      icon-editor
	      (icon-editor-engine-event 'change-current-layer-to-layer-below)
	      nil nil nil nil))
	  (change-current-layer			; args: new-layer-index, nil
	    (translator-end-current-state
	      icon-editor translator state state-information?)
	    (enqueue-icon-editor-engine-event
	      icon-editor
	      (icon-editor-engine-event 'change-current-layer)
	      arg-1? nil nil nil))
	  
	  (update-class-definition
	    (translator-end-current-state
	      icon-editor translator state state-information?)
	    (enqueue-icon-editor-engine-event
	      icon-editor
	      (icon-editor-engine-event 'update-class-definition)
	      nil nil nil nil))
	  
	  (move-layer-along-z-axis
	    (translator-end-current-state
	      icon-editor translator state state-information?)
	    (enqueue-icon-editor-engine-event
	      icon-editor
	      (icon-editor-engine-event 'move-layer-along-z-axis)
	      arg-1? arg-2? nil nil))

	  (move-layer-in-xy-plane		; args: none
	    (translator-end-current-state
	      icon-editor translator state state-information?)
	    (handle-move-layer-in-xy-plane-in-translator
	      icon-editor translator))

	  (clone-current-layer
	    (translator-end-current-state
	      icon-editor translator state state-information?)
	    (enqueue-icon-editor-engine-event
	      icon-editor
	      (icon-editor-engine-event 'clone-current-layer)
	       nil nil nil nil))

	  (fill-current-layer
	    (translator-end-current-state
	      icon-editor translator state state-information?)
	    (enqueue-icon-editor-engine-event
	      icon-editor
	      (icon-editor-engine-event 'fill-current-layer)
	       nil nil nil nil))

	  (outline-current-layer
	    (translator-end-current-state
	      icon-editor translator state state-information?)
	    (enqueue-icon-editor-engine-event
	      icon-editor
	      (icon-editor-engine-event 'outline-current-layer)
	       nil nil nil nil))

	  (set-main-image
	    (enqueue-icon-editor-engine-event
	      icon-editor
	      (icon-editor-engine-event 'set-main-image)
	      arg-1? nil nil nil))
	  (set-text       ; (pbk 2/6/96)
	    (enqueue-icon-editor-engine-event
	      icon-editor
	      (icon-editor-engine-event 'set-text)
	      arg-1? nil nil nil))
	  (set-stipple
	    (enqueue-icon-editor-engine-event
	      icon-editor
	      (icon-editor-engine-event 'set-stipple)
	      arg-1? nil nil nil))
	  (set-global-stipple
	    (enqueue-icon-editor-engine-event
	      icon-editor
	      (icon-editor-engine-event 'set-global-stipple)
	      arg-1? nil nil nil))
	  (edit-name-of-image
	    #+development (format t "Edit name of image~%"))
	  
	  ;; This notify-user is dying for some reason.
	  #+(and ignore development)
	  (t
	    (if (and (>=f translator-event 0)
		     (<=f translator-event 
			  icon-editor-translator-event-largest-index))
		(notify-user "Icon editor translator option (~a of ~a) not yet implemented."
			     translator-event
			     arg-1?)
		(cerror "Continue, anyway."
			"enqueue-icon-editor-translator-event received an ~
	           illegal translator event, ~a."
			translator-event)))))))
  #+development
  (check-memory-for-development 'enqueue-icon-editor-translator-event_99))



;;; The function `handle-mouse-motion-for-moving-layer' handles the dragging
;;; of a layer in xy.  We will have a non-NIL layer-icon only when the mouse
;;; is being dragged (a button is down).

(defun handle-mouse-motion-for-moving-layer
    (icon-editor view-pad state translator state-information? x y)
  (let ((layer-icon?
	  (icon-editor-view-pad-icon-for-current-layer?
	    view-pad)))
    (when layer-icon?
      (let ((serial-number
	      (icon-editor-view-pad-serial-number-of-icon-for-current-layer
		view-pad)))
	(cond
	  ((frame-has-not-been-reprocessed-p layer-icon? serial-number)
	   (let* ((offset-coord (second state-information?))
		  (x-offset-in-workspace (car offset-coord))
		  (y-offset-in-workspace (cdr offset-coord)))
	     (multiple-value-bind (bounded-x-in-workspace
				    bounded-y-in-workspace)
		 (compute-bounded-point-in-workspace
		   x y view-pad
		   x-offset-in-workspace y-offset-in-workspace)
	       (let* ((last-coord (first state-information?))
		      (old-cursor-x-in-workspace (car last-coord))
		      (old-cursor-y-in-workspace (cdr last-coord))
		      (delta-x-in-workspace
			(-w bounded-x-in-workspace	; new-cursor-x-in-workspace 
			    old-cursor-x-in-workspace))
		      (delta-y-in-workspace
			(-w bounded-y-in-workspace	; new-cursor-y-in-workspace
			    old-cursor-y-in-workspace)))

		 (move-blocks-with-their-external-connections
		   layer-icon? (icon-editor-workspace icon-editor)
		   delta-x-in-workspace delta-y-in-workspace)
		 (setf (car last-coord)
		       (+w (left-edge-of-block layer-icon?)	; reality check
			   x-offset-in-workspace))
		 ;; Could have set to bounded-x-in-workspace
		 (setf (cdr last-coord)
		       (+w (top-edge-of-block layer-icon?)
			   y-offset-in-workspace))))))
	  (t
	   (translator-cancel-current-state
	     icon-editor translator state state-information?)))))))


;;;; Translator End-<State> Operations




(defun-substitution-macro translator-end-drawing-point
    (icon-editor)
  icon-editor)

(defun-substitution-macro translator-end-drawing-points
				    (icon-editor translator state-information?)
  (when state-information?
    (enqueue-icon-editor-engine-event
      icon-editor
      (icon-editor-engine-event 'draw-points)    ; draw-points ??
      state-information?			       ; arg is reclaimed.
      nil nil nil)
    (setf (icon-editor-translator-state-information translator) nil)))



(defun-substitution-macro translator-end-drawing-line
				    (icon-editor translator state-information?)
  icon-editor
  (when state-information?
    (reclaim-icon-editor-cons state-information?))
  (setf (icon-editor-translator-state-information translator) nil))


(defun-substitution-macro translator-end-drawing-lines
				    (icon-editor translator state-information?)
  (when (cdr state-information?)
    (enqueue-icon-editor-engine-event
      icon-editor
      (icon-editor-engine-event 'draw-lines)
      state-information?			       ; arg is reclaimed.
      nil nil nil))
  (setf (icon-editor-translator-state-information translator) nil))


(defun-substitution-macro translator-end-drawing-arc
				    (icon-editor)
  (enqueue-icon-editor-visual-event 
    icon-editor
    (icon-editor-visual-event 'inform-user)
    (copy-constant-wide-string #w"End drawing arc.")
    nil))



(defun-substitution-macro translator-end-drawing-outlined-rectangle
				    (icon-editor) 
  (enqueue-icon-editor-visual-event 
    icon-editor
    (icon-editor-visual-event 'inform-user)
    (copy-constant-wide-string #w"End drawing outlined rectangle.")
    nil))



(defun-substitution-macro translator-end-drawing-outlined-circle
				    (icon-editor) 
  (enqueue-icon-editor-visual-event 
    icon-editor
    (icon-editor-visual-event 'inform-user)
    (copy-constant-wide-string #w"End drawing outlined circle.")
    nil))



(defun-substitution-macro translator-end-drawing-outlined-polygon
				    (icon-editor translator state-information?
						 keep-current-state?) 
  (when state-information?
    (if (cddr state-information?)
	;; a polygon requires >= 3 points
	(progn
	  (enqueue-icon-editor-engine-event
	    icon-editor
	    (icon-editor-engine-event 'draw-outlined-polygon)
	    state-information?			; arg is reclaimed.
	    nil nil nil)
	  (setf (icon-editor-translator-state-information translator) nil))
	(clear-icon-editor-translator-state-information translator)))
  (unless keep-current-state?
    (enqueue-icon-editor-visual-event 
      icon-editor
      (icon-editor-visual-event 'inform-user)
      (copy-constant-wide-string #w"End drawing outlined polygon.")
      nil)))



(defun-substitution-macro translator-end-drawing-filled-rectangle
				    (icon-editor)
  (enqueue-icon-editor-visual-event 
    icon-editor
    (icon-editor-visual-event 'inform-user)
    (copy-constant-wide-string #w"End drawing filled rectangle.")
    nil))



(defun-substitution-macro translator-end-drawing-filled-circle
				    (icon-editor) 
  (enqueue-icon-editor-visual-event 
    icon-editor
    (icon-editor-visual-event 'inform-user)
    (copy-constant-wide-string #w"End drawing filled circle.")
    nil))



(defun-substitution-macro translator-end-drawing-filled-polygon
				    (icon-editor translator state-information?
						 keep-current-state?)
  (let* ((failed-p nil))
    (when state-information?
      (if (cddr state-information?)
	  ;; a polygon requires >= 3 points
	  (progn
	    (setq failed-p
		  (enqueue-icon-editor-engine-event
		    icon-editor
		    (icon-editor-engine-event 'draw-filled-polygon)
		    state-information?		; arg is reclaimed
		    nil nil nil))
	    (setf (icon-editor-translator-state-information translator) nil))
	  (clear-icon-editor-translator-state-information translator)))
    
    (unless (or failed-p keep-current-state?)
      (enqueue-icon-editor-visual-event
	icon-editor
	(icon-editor-visual-event 'inform-user)
	(copy-constant-wide-string #w"End drawing filled polygon.")
	nil))))



(defun-substitution-macro translator-end-drawing-outlined-filled-rectangle
				    (icon-editor) 
  (enqueue-icon-editor-visual-event 
    icon-editor
    (icon-editor-visual-event 'inform-user)
    (copy-constant-wide-string #w"End drawing outlined filled rectangle.")
    nil))



(defun-substitution-macro translator-end-drawing-outlined-filled-circle
				    (icon-editor) 
  (enqueue-icon-editor-visual-event 
    icon-editor
    (icon-editor-visual-event 'inform-user)
    (copy-constant-wide-string #w"End drawing outlined filled circle.")
    nil))




(defun-substitution-macro translator-end-drawing-outlined-filled-polygon
				    (icon-editor translator state-information?
						 keep-current-state?) 
  (when state-information?
    (enqueue-icon-editor-engine-event
      icon-editor
      (icon-editor-engine-event 'draw-outlined-filled-polygon)
      state-information?
      nil nil nil)
    (setf (icon-editor-translator-state-information translator) nil))
  (unless keep-current-state?
    (enqueue-icon-editor-visual-event 
      icon-editor
      (icon-editor-visual-event 'inform-user)
      (copy-constant-wide-string #w"End drawing outlined filled polygon.")
      nil)))




(defun translator-end-current-state (icon-editor translator state
				     state-information?
				     &optional (keep-current-state? nil))
  ;; Clear-markers needs to be at the start of this function, since some of the
  ;;   states will send draw events to the engine.
  (enqueue-icon-editor-visual-event
    icon-editor (icon-editor-visual-event 'clear-markers-from-view-pad)
    nil nil)
  (enqueue-icon-editor-visual-event 
    icon-editor
    (icon-editor-visual-event 'inform-user)
    (icon-editor-state 'waiting)
    nil)
  (icon-editor-state-case state
    (drawing-point
      (translator-end-drawing-point icon-editor)
      (enqueue-icon-editor-visual-event 
	icon-editor
	(icon-editor-visual-event 'inform-user)
	(copy-constant-wide-string #w"End drawing points.")
	nil))
    (drawing-points
      (translator-end-drawing-points icon-editor translator state-information?)
      (enqueue-icon-editor-visual-event 
	icon-editor
	(icon-editor-visual-event 'inform-user)
	(copy-constant-wide-string #w"End drawing points.")
	nil))
    (drawing-line
      (translator-end-drawing-line
	icon-editor translator state-information?)
      (enqueue-icon-editor-visual-event 
	icon-editor
	(icon-editor-visual-event 'inform-user)
	(copy-constant-wide-string #w"End drawing line.")
	nil))
    (drawing-lines
      (translator-end-drawing-lines
	icon-editor translator state-information?)
      (enqueue-icon-editor-visual-event 
	icon-editor
	(icon-editor-visual-event 'inform-user)
	(copy-constant-wide-string #w"End drawing lines.")
	nil))
    (drawing-arc
      (translator-end-drawing-arc icon-editor))

    (drawing-outlined-rectangle
      (translator-end-drawing-outlined-rectangle icon-editor))
    (drawing-outlined-polygon
      (translator-end-drawing-outlined-polygon
	icon-editor translator state-information? keep-current-state?))
    (drawing-outlined-circle
      (translator-end-drawing-outlined-circle icon-editor))

    (drawing-filled-rectangle
      (translator-end-drawing-filled-rectangle icon-editor))
    (drawing-filled-polygon
      (translator-end-drawing-filled-polygon
	icon-editor translator state-information? keep-current-state?))
    (drawing-filled-circle
      (translator-end-drawing-filled-circle icon-editor))

    (drawing-outlined-filled-rectangle
      (translator-end-drawing-outlined-filled-rectangle	icon-editor))
    (drawing-outlined-filled-polygon
      (translator-end-drawing-outlined-filled-polygon
	icon-editor translator state-information? keep-current-state?))
    (drawing-outlined-filled-circle
      (translator-end-drawing-outlined-filled-circle icon-editor))
    (moving-layer-in-xy-plane
      (translator-end-moving-layer-in-xy-plane
	icon-editor translator state-information?)))

  (unless keep-current-state?
    (setf (icon-editor-translator-state translator)
	  (icon-editor-state 'waiting)))

  (clear-icon-editor-translator-state-information translator))




;;; Cancellation of states

;; currently not needed (polygons should complete when cancelled) ...

(defun-substitution-macro translator-cancel-drawing-outlined-polygon
				    (icon-editor) 
  (enqueue-icon-editor-visual-event 
    icon-editor
    (icon-editor-visual-event 'inform-user)
    (copy-constant-wide-string #w"Cancel drawing outlined polygon.")
    nil))


(defun-substitution-macro translator-cancel-drawing-filled-polygon
				    (icon-editor)
  (enqueue-icon-editor-visual-event 
    icon-editor
    (icon-editor-visual-event 'inform-user)
    (copy-constant-wide-string #w"Cancel drawing filled polygon.")
    nil))


(defun-substitution-macro translator-cancel-drawing-outlined-filled-polygon
				    (icon-editor) 
  (enqueue-icon-editor-visual-event 
    icon-editor
    (icon-editor-visual-event 'inform-user)
    (copy-constant-wide-string #w"Cancel drawing outlined filled polygon.")
    nil))




;; ... "cancellation" differs from "ending" just for polygons.

(defun translator-cancel-current-state (icon-editor translator state
					state-information?)  

  ;; Clear-markers needs to be at the start of this function, since some of the
  ;;   states will send draw events to the engine.
  (enqueue-icon-editor-visual-event
    icon-editor (icon-editor-visual-event 'clear-markers-from-view-pad)
    nil nil)

  (icon-editor-state-case state
    (drawing-point
      (translator-end-drawing-point icon-editor)
      (enqueue-icon-editor-visual-event 
	icon-editor
	(icon-editor-visual-event 'inform-user)
	(copy-constant-wide-string #w"Cancel drawing points.")
	nil))
    (drawing-points
      (translator-end-drawing-points icon-editor translator state-information?)
      (enqueue-icon-editor-visual-event 
	icon-editor
	(icon-editor-visual-event 'inform-user)
	(copy-constant-wide-string #w"Cancel drawing points.")
	nil))
    (drawing-line
      (translator-end-drawing-line
	icon-editor translator state-information?)
      (enqueue-icon-editor-visual-event 
	icon-editor
	(icon-editor-visual-event 'inform-user)
	(copy-constant-wide-string #w"Cancel drawing line.")
	nil))
    (drawing-lines
      (when state-information?
	(reclaim-icon-editor-slot-value state-information?)
	(setf (icon-editor-translator-state-information translator) nil)
	(enqueue-icon-editor-visual-event 
	  icon-editor
	  (icon-editor-visual-event 'inform-user)
	  (copy-constant-wide-string #w"Cancel drawing lines.")
	  nil)))
    (drawing-arc
      (translator-end-drawing-arc icon-editor))

    (drawing-outlined-rectangle
      (translator-end-drawing-outlined-rectangle icon-editor))
    (drawing-outlined-polygon
      (translator-cancel-drawing-outlined-polygon icon-editor))
    (drawing-outlined-circle
      (translator-end-drawing-outlined-circle icon-editor))

    (drawing-filled-rectangle
      (translator-end-drawing-filled-rectangle icon-editor))
    (drawing-filled-polygon
      (translator-cancel-drawing-filled-polygon icon-editor))
    (drawing-filled-circle
      (translator-end-drawing-filled-circle icon-editor))

    (drawing-outlined-filled-rectangle
      (translator-end-drawing-outlined-filled-rectangle	icon-editor))
    (drawing-outlined-filled-polygon
      (translator-cancel-drawing-outlined-filled-polygon icon-editor))
    (drawing-outlined-filled-circle
      (translator-end-drawing-outlined-filled-circle icon-editor))
    (moving-layer-in-xy-plane
      (clear-icon-editor-translator-state-information translator)
      (translator-end-moving-layer-in-xy-plane
	icon-editor translator state-information?)
      (enqueue-icon-editor-visual-event
	icon-editor
	(icon-editor-visual-event 'inform-user)
	(icon-editor-state 'waiting)
	nil)))

  (setf (icon-editor-translator-state translator)
	(icon-editor-state 'waiting))
  (clear-icon-editor-translator-state-information translator))




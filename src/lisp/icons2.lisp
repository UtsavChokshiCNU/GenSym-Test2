 ;; -*- Mode:Common-Lisp; Package:AB; Base:10; Syntax:COMMON-LISP -*-
(in-package "AB")

;;;; Module ICONS2 -- The Icon Editor Display and Initialization Code

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Ong, Peng Tsin






;; To ICONS3

(declare-forward-reference enqueue-icon-editor-translator-event function)

;; To ICONS5

(declare-forward-reference current-image-plane? variable) ; part of icon editor context

;; To CHECKMEMORY

#+development
(declare-forward-reference check-memory function)







;; The def-slot-value-writer for icon-editor-table-info-frame-info is moved
;; to ICONS2 because of eval-when problems.  -pto 03oct89

(def-slot-value-writer icon-editor-table-info-frame-info (value)
  (cond ((icon-editor-state-p value)
	 (twrite-string
	   (icon-editor-state-case value		; use the enumerated case
	     (waiting "Icon editor ready.")
	     (undoing "Undo.")
	     (redoing "Redo.")
	     (drawing-point "Drawing point.")
	     (drawing-points "Drawing points.")
	     (drawing-line "Drawing line.")
	     (drawing-lines "Drawing lines.")
	     (drawing-arc "Drawing an arc.")
	     (drawing-outlined-rectangle 
	       "Drawing an outlined rectangle.")
	     (drawing-outlined-polygon
	       "Drawing an outlined polygon.")
	     (drawing-outlined-circle
	       "Drawing an outlined circle.")
	     (drawing-filled-rectangle
	       "Drawing a filled rectangle.")
	     (drawing-filled-polygon
	       "Drawing a filled polygon.")
	     (drawing-filled-circle
	       "Drawing a filled circle.")
	     (drawing-outlined-filled-rectangle
	       "Drawing a filled and outlined rectangle.")
	     (drawing-outlined-filled-polygon
	       "Drawing a filled and outlined polygon.")
	     (drawing-outlined-filled-circle
	       "Drawing a filled and outlined circle.")
	     (moving-layer-in-xy-plane		; will probably not be implemented yet.
	       "Drag the current layer to its new position.")
	     (in-layers-pad "Working with layers.")
;	(moving-layer-along-z-axis 
;	   "Shuffling layer up or down.")
	     )))
	((text-string-p value)				    ; Assumed to be a text-string.
	 ;; Leak here: we should free value?
	 (tformat "~a" value))
	((null value)
	 nil)
	((symbolp value)
	 (twrite-symbol (or value 'icon-editor-ready)))
	(t
	 (twrite value))))




;; NOTES:

;; The Visible Parts of the Icon Editor

;; The Control Pad

;; PARTS:
;; Information:
;;   x-position-readout
;;   y-position-readout
;;   width-readout
;;   height-readout
;;   information-readout
;; Drawing Controls:
;;   change-size-button
;;   shrink-wrap-button
;;   undo-button
;;   redo-button
;;   points-button
;;   lines-button
;;   arc-button
;;   circle-button
;;   outline-button
;;   filled-circle-button
;;   filled-polygon-button
;;   outlined-filled-circle-button
;;   outlined-filled-polygon-button
;;   done-with-current-drawing-element-button
;;   cancel-current-drawing-element-button
;;   new-layer
;; Current Layer Control:
;;   delete-current-layer-button
;;   choose-foreground-color-button
;;   choose-foreground-region-button
;;   choose-background-color-button
;;   choose-background-region-button
;;   group-with-layer-below-button
;;   ungroup-current-layer-button
;; General Controls:
;;   cancel-icon-edting-button
;;   end-icon-editing-button
;;   show-position-switch


;; The View Pad

;; The Layers Pad






;;;; The Icon Editor Display and Its Widget Set




;;; An `icon editor draw button' is one that is used for drawing.  In most, but not
;;; all of these, the interior of the rectangle surrounding the button contains
;;; graphics instead of a textual label.  An `icon editor text button' is one
;;; that is used for other kinds of actions.  These have mostly textual labels
;;; inside.

;;; Many icon editor buttons have a region named DETAILS.  This region is specially
;;; handled by the button highlighter in such a way that it reverses to background
;;; when the button is highlighted in the foreground color.  See highlight-or-
;;; unhighlight-button in CONTROLS for details on button highlighting.

(def-class (icon-editor-button generic-action-button))

(def-class (icon-editor-draw-button icon-editor-button))
 
(def-class (big-icon-editor-text-button icon-editor-draw-button))
;  (icon-description
;    (:funcall-at-load-time
;      create-action-button-description 90 30)))	; was 60 (MHD)


(def-class (small-icon-editor-text-button icon-editor-draw-button)
  (icon-description
    (:funcall-at-load-time
      create-action-button-description 60 30)))	; was 60 (MHD)




 
;; Points Button

(def-class (points-button icon-editor-draw-button)
  (icon-description
    (:funcall-at-load-time
      create-action-button-description 60 30
      ((details . foreground))
      (details
	(outline (29 14) (29 16) (31 16) (31 14) (30 14) (30 15))))))




 


;; Line Button

(def-class (line-button icon-editor-draw-button)
  (icon-description
    (:funcall-at-load-time
      create-action-button-description 60 30
      ((details . foreground))
      (details
	(lines (10 10) (50 20))))))

;; Lines Button

(def-class (lines-button icon-editor-draw-button)
  (icon-description
    (:funcall-at-load-time
      create-action-button-description 60 30
      ((details . foreground))
      (details
	(lines (10 10) (30 25) (25 12) (50 7))))))


;; Arc Button

(def-class (arc-button icon-editor-draw-button)
  (icon-description
    (:funcall-at-load-time
      create-action-button-description 60 30
      ((details . foreground))
      (details
	(lines (25 22) (arc (38 10)) (32 5))))))



;; Outlined-Rectangle Button

(def-class (outlined-rectangle-button icon-editor-draw-button)
  (icon-description
    (:funcall-at-load-time
      create-action-button-description 60 30
      ((details . foreground))
      (details
	(outline (15 5) (45 5) (45 25) (15 25))))))



;; Outlined-Polygon Button

(def-class (outlined-polygon-button icon-editor-draw-button)
  (icon-description
    (:funcall-at-load-time
      create-action-button-description 60 30
      ((details . foreground))
      (details
	(outline (10 15) (17 5) (41 5) (30 17) (50 17) (45 25) (20 25))
	))))



;; Outlined-Circle Button

(def-class (outlined-circle-button icon-editor-draw-button)
  (icon-description
    (:funcall-at-load-time
      create-action-button-description 60 30
      ((details . foreground))
      (details
	(circle (18 15) (30 3) (42 15))
	))))



;; Filled-Rectangle Button

(def-class (filled-rectangle-button icon-editor-draw-button)
  (icon-description
    (:funcall-at-load-time
      create-action-button-description 60 30
      ((details . foreground))
      (details
	(solid-rectangle (15 5) (45 25))
	))))



;; Filled-Circle Button

(def-class (filled-circle-button icon-editor-draw-button)
  (icon-description
    (:funcall-at-load-time
      create-action-button-description 60 30
      ((details . foreground))
      (details
	(filled-circle (18 15) (30 3) (42 15))
	))))



;; Filled-Polygon Button

(def-class (filled-polygon-button icon-editor-draw-button)
  (icon-description
    (:funcall-at-load-time
      create-action-button-description 60 30
      ((details . foreground))
      (details
	(filled-polygon ((10 15) (17 5) (40 5) (30 17) (50 17) (45 25) (20 25))
			((10 15) (17 5) (40 5))
			((30 17) (50 17) (45 25))
			((20 25) (40 5) (30 17))
			((30 17) (45 25) (20 25))
			((20 25) (10 15) (40 5)))	
	))))



;; Outlined-Filled-Rectangle Button

(def-class (outlined-filled-rectangle-button icon-editor-draw-button)
  (icon-description
    (:funcall-at-load-time
      create-action-button-description 60 30
      ((outline-details . foreground)
       (details . foreground))
      (outline-details
	(outline (15 5) (45 5) (45 25) (15 25))
	details
	(solid-rectangle (17 7) (43 23))
	))))



;; Outlined-Filled-Polygon Button

(def-class (outlined-filled-polygon-button icon-editor-draw-button)
  (icon-description
    (:funcall-at-load-time
      create-action-button-description 60 30
      ((outline-details . foreground)
       (details . foreground))
      (outline-details
	(outline (10 15) (17 5) (41 5) (30 17) (50 17) (45 25) (20 25))
	details
	(filled-polygon ((13 15) (19 7) (38 7) (26 19) (46 19) (43 23) (22 23))
			((13 15) (19 7) (38 7))
			((26 19) (46 19) (43 23))
			((43 23) (22 23) (13 15))
			((13 15) (38 7) (26 19))
			((26 19) (43 23) (13 15)))	
	))))



;; Outlined-Filled-Circle Button

(def-class (outlined-filled-circle-button icon-editor-draw-button)
  (icon-description
    (:funcall-at-load-time
      create-action-button-description 60 30
      ((outline-details . foreground)
       (details . foreground))
      (outline-details
	(circle (18 15) (30 3) (42 15))
	details
	(filled-circle (20 15) (30 5) (40 15))
	))))











;;; The constant `icon-editor-buttons-specification-list' ...
;;; The first of an element of the constant is an icon-editor-translator-event
;;; enumerated type symbol corresponding to the button, the second of an 
;;; element is a string if the button has text on it, or a symbol representing
;;; the class to which the button belongs.  The third of an element is the
;;; relative coordinate of the top left corner of the button with
;;; respect to the first button, which should be at (0,0).


(defparameter icon-editor-buttons-specification-list
  '#.(let* ((draw-pallet-x (- (x-in-workspace-of-view-pad) 65)) ; was 0 
		       (draw-pallet-y (- y-in-workspace-of-view-pad 110))  ; was 102 (pbk) 
		       (layer-pallet-x 0)
		       (layer-pallet-y (+ y-in-workspace-of-view-pad 25))) ; was -10 (pbk)
		  (create-icon-editor-buttons-specification-list
		    `((cancel-editing "Cancel" (0 160))	; top left button (was 0 0) (pbk)
		      (end-editing "End" (0 195)) ; was 0 35 (pbk)
		      (update-class-definition "Update" (0 230)) ; was 0 70 (pbk)
		      (redraw "Redraw" (0 265)) ; was 0 120 (pbk)
		      ;;(undo "Undo" (0 35))
		      ;;(redo "Redo" (0 70))
		      ;;(end-editing "End" (0 105))
		      
		      ;; New bitmap button: allows editing the bitmap name for this layer.
;;		      (edit-name-of-image
;;			"image"
;;			(,(+ draw-pallet-x 0) ,(+ draw-pallet-y 0)))

		      ;; DRAW PALLET
		      ;; 130, 0
		      (draw-arc
			arc-button
			(,(+ draw-pallet-x 65) ,(+ draw-pallet-y 0)))
		      (draw-points
			points-button
			(,(+ draw-pallet-x 130) ,(+ draw-pallet-y 0)))

		      (view-pad-scale-1-to-1
			"x1"
			(,(+ draw-pallet-x 195) ,(+ draw-pallet-y 0)))
		      (view-pad-scale-2-to-1
			"x2"
			(,(+ draw-pallet-x 260) ,(+ draw-pallet-y 0)))
		      (view-pad-scale-3-to-1
			"x3"
			(,(+ draw-pallet-x 325) ,(+ draw-pallet-y 0)))
		      ; 195

;		      (draw-arc
;			arc-button
;			(,(+ draw-pallet-x 0) ,(+ draw-pallet-y 35)))
		      (draw-lines
			lines-button
			(,(+ draw-pallet-x 65) ,(+ draw-pallet-y 35)))
		      (draw-outlined-rectangle
			outlined-rectangle-button 
			(,(+ draw-pallet-x 130) ,(+ draw-pallet-y 35)))
		      (draw-outlined-circle 
			outlined-circle-button
			(,(+ draw-pallet-x 195) ,(+ draw-pallet-y 35)))
		      (draw-outlined-polygon
			outlined-polygon-button 
			(,(+ draw-pallet-x 260) ,(+ draw-pallet-y 35)))
		      (delete-most-recent-drawing-element
			"Pop"
			(,(+ draw-pallet-x 325) ,(+ draw-pallet-y 35)))
;		      (move-layer-in-xy-plane
;			"Move"
;			(,(+ draw-pallet-x 325) ,(+ draw-pallet-y 35)))

;		      (draw-points
;			points-button
;			(,(+ draw-pallet-x 0) ,(+ draw-pallet-y 70)))
		      (draw-line
			line-button
			(,(+ draw-pallet-x 65) ,(+ draw-pallet-y 70)))
		      (draw-filled-rectangle
			filled-rectangle-button
			(,(+ draw-pallet-x 130) ,(+ draw-pallet-y 70)))
		      (draw-filled-circle 
			filled-circle-button
			(,(+ draw-pallet-x 195) ,(+ draw-pallet-y 70)))
		      (draw-filled-polygon
			filled-polygon-button
			(,(+ draw-pallet-x 260) ,(+ draw-pallet-y 70)))
		      (done-drawing-element
			"Done"
			(,(+ draw-pallet-x 325), (+ draw-pallet-y 70)))

;		   (draw-outlined-filled-rectangle
;		     outlined-filled-rectangle-button
;		     (,(+ draw-pallet-x 65) ,(+ draw-pallet-y 0)))
;		   (draw-outlined-filled-circle
;		     outlined-filled-circle-button
;		     (,(+ draw-pallet-x 130) ,(+ draw-pallet-y 0)))
;		   (draw-outlined-filled-polygon 
;		     outlined-filled-polygon-button
;		     (,(+ draw-pallet-x 195) ,(+ draw-pallet-y 0)))

		      ;;(change-icon-size "Size" (100 0))
		      ;;(shrink-wrap "Wrap" (100 35))
		      ;;(show-grid "Show Grid" (165 0))
		      ;;(hide-grid "Hide Grid" (165 35))
		      
		      ;;(choose-main-color "Main" (0 175))
		      ;;(choose-outline-color "Outline" (0 210))
		      
		      
		      ;; LAYER PALLET
		      (new-layer "New"
				 (,(+ layer-pallet-x 0) ,(+ layer-pallet-y 0)))
		      (delete-current-layer 
			"Delete" (,(+ layer-pallet-x 0) ,(+ layer-pallet-y 35)))
		      (group "Group"
			     (,(+ layer-pallet-x 0) ,(+ layer-pallet-y 70)))
		      (ungroup-current-layer
			"Ungroup" 
			(,(+ layer-pallet-x 0) ,(+ layer-pallet-y 105)))
		      (clone-current-layer
			"Clone"
			(,(+ layer-pallet-x 0) ,(+ layer-pallet-y 140)))

		      (fill-current-layer
			"Fill"
			(,(+ layer-pallet-x 0) ,(+ layer-pallet-y 175)))
		      (outline-current-layer
			"Outline"
			(,(+ layer-pallet-x 0) ,(+ layer-pallet-y 210)))

;		      (change-current-layer-to-layer-above
;			"Up"
;			(,(+ layer-pallet-x 0) ,(+ layer-pallet-y 140)))
;		      (change-current-layer-to-layer-below
;			"Down"
;			(,(+ layer-pallet-x 0) ,(+ layer-pallet-y 175)))

		      ; 210
		      (move-layer-in-xy-plane
			"Move"
			(,(+ layer-pallet-x 0) ,(+ layer-pallet-y 245)))

;		      (redraw
;			"Redraw"
;			(,(+ layer-pallet-x 0) ,(+ layer-pallet-y 245)))

		      ))))
	       

;;; The constant `icon-editor-tables-specification-list' is a list of
;;; descriptions for tables in the icon editor.  Each element is in the form:
;;; (<table-name> <list-of-table-slots> (<x> <y>) <use-small-font?>).

(defparameter icon-editor-tables-specification-list
  `((info-box (icon-editor-table-info-frame-info) (0 0) t)
    (size-table
      (icon-editor-table-info-frame-icon-width
	icon-editor-table-info-frame-icon-height
	icon-editor-table-info-frame-global-stipple)
      (0 #.(- y-in-workspace-of-layers-pad 100))
      t)
    (label-table
      (icon-editor-table-info-frame-main-region
	icon-editor-table-info-frame-main-color
	icon-editor-table-info-frame-main-image
	icon-editor-table-info-frame-text ; (add-text (pbk 2/6/96))
	icon-editor-table-info-frame-stipple)
      (320 0)
      t) 
    (x-y-position-box
      (icon-editor-table-info-frame-x-y-position)
      (200 #.(- y-in-workspace-of-layers-pad 100))
      t)))














;;;; Widget Creation, Placement, and Deletion Functions



;;; View Pad



;;; The four macros that follow are to correct the problem caused
;;; by the fact that an icon of width x requires a raster of size
;;; x+1 to hold.

(defmacro adjusted-delta-x-for-icon-delta-x (icon-width)
  `(+w ,icon-width 1))

(defmacro adjusted-delta-y-for-icon-delta-y (icon-height)
  `(+w ,icon-height 1))

(defmacro icon-delta-x-for-adjusted-delta-x (raster-width)
  `(-w ,raster-width 1))

(defmacro icon-delta-y-for-adjusted-delta-y (raster-height)
  `(-w ,raster-height 1))




;;; The substitution macro `point-in-view-pad-p' returns nil if the
;;; given point (in workspace coordinates) is not in the view pad.  Non-nil
;;; is returned otherwise.  Only entities that belong in the view pad 
;;; should be placed there.
;;;
;;; [As of the release pending, 1/28/00. (MHD 1/28/00)] A little leeway (10
;;; window units) is added beyond the right and bottom edges to improve
;;; usability, and to compensate somewhat for inaxact scaling; otherwise, users
;;; would find it frustrating to "miss" if they were just a few pixels away from
;;; the edge, or even, at certain scales (e.g., 4 X full scale), if they were
;;; right on the border.]

(defun point-in-view-pad-p 
    (x-in-workspace y-in-workspace view-pad)
  (let* ((leeway 10)
	 (leeway-x-in-workspace
	   (delta-x-in-workspace
	     leeway (image-x-scale current-image-plane?)))
	 (leeway-y-in-workspace
	   (delta-y-in-workspace
	     leeway (image-y-scale current-image-plane?))))
    (and (<=w (icon-editor-view-pad-x-in-workspace view-pad) x-in-workspace)
	 (<w x-in-workspace (+w (view-pad-right-edge view-pad) leeway-x-in-workspace))
	 (<=w (icon-editor-view-pad-y-in-workspace view-pad) y-in-workspace)
	 (<w y-in-workspace (+w (view-pad-bottom-edge view-pad) leeway-y-in-workspace)))))

;; It would probably be better to have this take x/y in window units, but it
;; seems a bit difficult and not worthwhile at this time to fix the callers.
;; (MHD 1/28/99)







;;; The view pad marker facility allows the placement of either a cross-hair
;;; mark or a line in the view pad.  These lines are maintained as a stack
;;; and the can only be taken off the view pad in a LIFO manner.

(def-substitution-macro push-marker-in-view-pad (marker view-pad)
  (setf (icon-editor-view-pad-marker-stack view-pad)
	(icon-editor-cons (icon-editor-cons marker (copy-frame-serial-number (current-frame-serial-number)))
			  (icon-editor-view-pad-marker-stack view-pad))))






(defun wrap-polychrome-declaration-around-slot-value-conses
       (color line-drawing-description)
  (if (eq color 'transparent) (setq color 'foreground))
  (slot-value-cons-macro
    (slot-value-list
      'polychrome (slot-value-cons-macro color color))
    (slot-value-cons-macro
      color line-drawing-description)))


      

;;; The function `put-cross-marker-in-view-pad' ...

(defmacro-for-constant view-pad-cross-marker-size 5)	; should be an odd integer

(defun-substitution-macro put-cross-marker-in-view-pad
				(x-in-view-pad y-in-view-pad view-pad
					       color put-point-marker-instead?)
  #+development
  (check-memory-for-development 'put-cross-marker-in-view-pad_0)
  (let* ((marker-extent (-w (view-pad-cross-marker-size) 1))
	 (marker-relative-center (ashw marker-extent -1))
	 (cross-marker
	   (make-entity-with-specific-icon-description
	     'iconic-entity
	     (wrap-polychrome-declaration-around-slot-value-conses
	       color
	       (if put-point-marker-instead?
		   (slot-value-cons
		     (slot-value-list
		       'point
		       (slot-value-list
			 marker-relative-center
			 marker-relative-center))
		     nil)
		   (slot-value-list
		     (slot-value-list
		       'lines
		       (slot-value-list 0 marker-relative-center)
		       (slot-value-list marker-extent marker-relative-center))
		     (slot-value-list
		       'lines
		       (slot-value-list marker-relative-center 0)
		       (slot-value-list marker-relative-center marker-extent)))))
	     ;; eg.  `((lines (0 2) (4 2)) (lines (2 0) (2 4)))
	     marker-extent marker-extent)))
    #+development
    (check-memory-for-development 'put-cross-marker-in-view-pad_10)
    (push-marker-in-view-pad cross-marker view-pad)
    #+development
    (check-memory-for-development 'put-cross-marker-in-view-pad_20)
    (add-to-workspace cross-marker (icon-editor-view-pad-workspace view-pad)
		      (-w (x-in-workspace-from-view-pad x-in-view-pad view-pad)
			  marker-relative-center)
		      (-w (y-in-workspace-from-view-pad y-in-view-pad view-pad)
			  marker-relative-center)
		      t))
  #+development
  (check-memory-for-development 'put-cross-marker-in-view-pad_99))



;;; The function `put-line-marker-in-view-pad' ...

(defun put-line-marker-in-view-pad 
       (x0-in-view-pad y0-in-view-pad x1-in-view-pad y1-in-view-pad
	view-pad color
	left-edge-to-clip-in-workspace top-edge-to-clip-in-workspace
	right-edge-to-clip-in-workspace bottom-edge-to-clip-in-workspace
	put-rectangle-marker-instead?)
  #+development
  (check-memory-for-development 'put-line-marker-in-view-pad_0)
  ;; the x and y icon values can not go below 0.
  (let* ((flip-ends-of-lines? (>w x0-in-view-pad x1-in-view-pad))
	 (desired-x0-in-icon
	   (delta-x-in-workspace-from-view-pad
	     (if flip-ends-of-lines? x1-in-view-pad x0-in-view-pad)
	     view-pad))
	 (desired-y-for-x0-in-icon
	   (delta-y-in-workspace-from-view-pad
	     (if flip-ends-of-lines? y1-in-view-pad y0-in-view-pad)
	     view-pad))
	 (x0-in-icon (maxw desired-x0-in-icon 0))
	 (y0-in-icon (maxw desired-y-for-x0-in-icon 0))
	 (desired-y-for-x1-in-icon
	   (delta-y-in-workspace-from-view-pad
	     (if flip-ends-of-lines? y0-in-view-pad y1-in-view-pad)
	     view-pad))
	 (x1-in-icon (delta-x-in-workspace-from-view-pad
		       (if flip-ends-of-lines? x0-in-view-pad x1-in-view-pad)
		       view-pad))
	 (y1-in-icon (maxw desired-y-for-x1-in-icon 0)))
    (let* ((right-end-of-line-higher? (>w y0-in-icon y1-in-icon))
	   ;; The larger the y value, the lower the point (+ve y goes down).

	   ;; Try and implement this correctly, and use it instead of 0's in the icon description
;	   (desired-y0-in-icon
;	     (if right-end-of-line-higher?
;		 desired-y-for-x1-in-icon
;		 desired-y-for-x0-in-icon))

	   (x0-in-workspace
	     (x-in-workspace-from-view-pad-workspace
	       x0-in-icon view-pad))
	   (y0-in-workspace
	     (y-in-workspace-from-view-pad-workspace
	       (if right-end-of-line-higher?
		   y1-in-icon
		   y0-in-icon)
	       view-pad))
	   (desired-icon-width (absw (-w x1-in-icon x0-in-icon)))
	   (desired-icon-height (absw (-w y1-in-icon y0-in-icon)))
	   (icon-width (minw (maxw 1 desired-icon-width)
			     (-w (+w right-edge-to-clip-in-workspace 1)
				 (maxr left-edge-to-clip-in-workspace
				       x0-in-workspace))))
	   (icon-height (minw (maxw 1 desired-icon-height)
			      (-w (+w bottom-edge-to-clip-in-workspace 1)
				  (maxr top-edge-to-clip-in-workspace
					y0-in-workspace))))
	   (line-marker
	     (make-entity-with-specific-icon-description
	       'iconic-entity
	       (wrap-polychrome-declaration-around-slot-value-conses
		 color
		 (if put-rectangle-marker-instead?
		     (slot-value-list
		       (slot-value-list
			 'outline
			 (slot-value-list 0 0)	; desired-y0-in-icon
			 (slot-value-list 0 desired-icon-height)
			 (slot-value-list desired-icon-width
					  desired-icon-height)
			 (slot-value-list desired-icon-width 0)))	; desired-y0-in-icon
		     (slot-value-list
		       (slot-value-list
			 'lines
			 (slot-value-list 0
					  (if right-end-of-line-higher? 
					      desired-icon-height
					      0))	; desired-y0-in-icon
			 (slot-value-list desired-icon-width
					  (if right-end-of-line-higher?
					      0	; desired-y0-in-icon
					      desired-icon-height))))))
	       ;; eg.  `((lines (0 2) (4 2)) (lines (2 0) (2 4)))
	       icon-width
	       icon-height)))
      ;;(format t "~&~a,~a; ~a,~a" x0-in-icon y0-in-icon icon-width icon-height)
      #+development
      (check-memory-for-development 'put-line-marker-in-view-pad_10)
      (push-marker-in-view-pad line-marker view-pad)
      #+development
      (check-memory-for-development 'put-line-marker-in-view-pad_20)
      (add-to-workspace line-marker (icon-editor-view-pad-workspace view-pad)
			x0-in-workspace y0-in-workspace t)))
  #+development
  (check-memory-for-development 'put-line-marker-in-view-pad_99))



;;; The function `put-circle-marker-in-view-pad' puts a circle on the view pad
;;; by creating a circle icon description and placing it on the workspace.  The
;;; circle is clipped using left-top edge-to-clip-in-workspace (workspace) argument and the
;;; lower-bottom view-pad point.

(defun-substitution-macro put-circle-marker-in-view-pad
				    (x0-in-view-pad
				      y0-in-view-pad
				      radius-in-view-pad
				      view-pad
				      color
				      left-edge-to-clip-in-workspace
				      top-edge-to-clip-in-workspace
				      right-edge-to-clip-in-workspace
				      bottom-edge-to-clip-in-workspace)
  (let* ((x-radius-in-icon (delta-x-in-workspace-from-view-pad
			     radius-in-view-pad view-pad))
	 (y-radius-in-icon (delta-y-in-workspace-from-view-pad
			     radius-in-view-pad view-pad))
	 (left-edge-in-view-pad (-w x0-in-view-pad radius-in-view-pad))
	 (top-edge-in-view-pad (-w y0-in-view-pad radius-in-view-pad))
	 (desired-min-x-in-workspace
	   (maxw (x-in-workspace-from-view-pad left-edge-in-view-pad view-pad)
		 left-edge-to-clip-in-workspace))
	 (desired-min-y-in-workspace
	   (maxw (y-in-workspace-from-view-pad top-edge-in-view-pad view-pad)
		 top-edge-to-clip-in-workspace))
	 (desired-max-x-in-workspace
	   (minw
	     (x-in-workspace-from-view-pad
	       (+w x0-in-view-pad radius-in-view-pad) view-pad)
	     right-edge-to-clip-in-workspace))
	 (desired-max-y-in-workspace
	   (minw
	     (y-in-workspace-from-view-pad
	       (+w y0-in-view-pad radius-in-view-pad) view-pad)
	     bottom-edge-to-clip-in-workspace))
	 (clipped-delta-x-in-workspace
	   (if (=w desired-min-x-in-workspace left-edge-to-clip-in-workspace)
	       (-w left-edge-to-clip-in-workspace
		   (x-in-workspace-from-view-pad
		     left-edge-in-view-pad view-pad))
	       0))
	 (clipped-delta-y-in-workspace
	   (if (=w desired-min-y-in-workspace top-edge-to-clip-in-workspace)
	       (-w top-edge-to-clip-in-workspace 
		   (y-in-workspace-from-view-pad
		     top-edge-in-view-pad view-pad))
	       0))
	 (desired-icon-width (-w desired-max-x-in-workspace
				 desired-min-x-in-workspace))
	 (desired-icon-height (-w desired-max-y-in-workspace
				  desired-min-y-in-workspace))

	 (icon-width (maxw 1 desired-icon-width))
	 (icon-height (maxw 1 desired-icon-height))

	 (x1 (-w clipped-delta-x-in-workspace))
	 (y1 (-w y-radius-in-icon clipped-delta-y-in-workspace))
	 (x2 (-w x-radius-in-icon clipped-delta-x-in-workspace))
	 (y2 (-w clipped-delta-y-in-workspace))
	 (x3 (-w (twicew x-radius-in-icon) clipped-delta-x-in-workspace))
	 (y3 y1)

	 (circle-marker
	   (make-entity-with-specific-icon-description
	     'iconic-entity
	     (wrap-polychrome-declaration-around-slot-value-conses
	       color
	       (slot-value-cons
		 (if (and (=f desired-icon-width 0)
			  (=f desired-icon-height 0))
						; adjust width, height, top
						; edge, and left edge for
						; point!!
		     (slot-value-list 'point (slot-value-list 0 0))
		     (slot-value-list
		       'circle
		       (slot-value-list x1 y1)
		       (slot-value-list x2 y2)
		       (slot-value-list x3 y3)
		       ))
		 nil))
	     ;; eg.  `((circle (0 2) (2 4) (4 2)))
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              	     icon-width
	     icon-height)))
    (push-marker-in-view-pad circle-marker view-pad)
    (add-to-workspace circle-marker (icon-editor-view-pad-workspace view-pad)
		      desired-min-x-in-workspace
		      desired-min-y-in-workspace
		      t)))




;;; The function `put-arc-marker-in-view-pad' ...


(defun-substitution-macro put-arc-marker-in-view-pad
			  (x0-in-view-pad
			    y0-in-view-pad
			    x1-in-view-pad
			    y1-in-view-pad
			    x2-in-view-pad
			    y2-in-view-pad
			    view-pad
			    color
			    left-edge-to-clip-in-workspace
			    top-edge-to-clip-in-workspace
			    right-edge-to-clip-in-workspace
			    bottom-edge-to-clip-in-workspace)
  
  (multiple-value-bind (min-x-in-view-pad? min-y-in-view-pad?
			max-x-in-view-pad? max-y-in-view-pad?)
      (compute-arc-bounding-box
	x0-in-view-pad y0-in-view-pad x1-in-view-pad y1-in-view-pad
	x2-in-view-pad y2-in-view-pad)
    
    (if min-x-in-view-pad?
	;; if min-x-in-view-pad? THEN
	(let* ((min-x-in-workspace
		 (maxw (x-in-workspace-from-view-pad min-x-in-view-pad? view-pad)
		       left-edge-to-clip-in-workspace))
	       (min-y-in-workspace
		 (maxw (y-in-workspace-from-view-pad min-y-in-view-pad? view-pad)
		       top-edge-to-clip-in-workspace))
	       ;; currently the maximum x and y of the icon is base on the arc and
	       ;;   not the workspace size (the workspace expands to fit the
	       ;;   arc)!!!  Review this.  4oct89, cpm
	       (max-x-in-workspace
		 (minw
		   (x-in-workspace-from-view-pad max-x-in-view-pad? view-pad)
		   (+w 
		     (delta-x-in-workspace-from-view-pad 
		       (icon-editor-view-pad-width view-pad)
		       view-pad)
		     (icon-editor-view-pad-x-origin-in-workspace view-pad))))
	       (max-y-in-workspace
		 (minw
		   (y-in-workspace-from-view-pad max-y-in-view-pad? view-pad)
		   (+w 
		     (delta-y-in-workspace-from-view-pad 
		       (icon-editor-view-pad-height view-pad)
		       view-pad)
		     (icon-editor-view-pad-y-origin-in-workspace view-pad))))
	       
	       (left-edge-in-workspace min-x-in-workspace)
	       (top-edge-in-workspace min-y-in-workspace)
	       
	       (x0-in-icon (-w (x-in-workspace-from-view-pad
				 x0-in-view-pad view-pad)
			       left-edge-in-workspace))
	       (y0-in-icon (-w (y-in-workspace-from-view-pad
				 y0-in-view-pad view-pad)
			       top-edge-in-workspace))
	       (x1-in-icon (-w (x-in-workspace-from-view-pad
				 x1-in-view-pad view-pad)
			       left-edge-in-workspace))
	       (y1-in-icon (-w (y-in-workspace-from-view-pad
				 y1-in-view-pad view-pad)
			       top-edge-in-workspace))
	       (x2-in-icon (-w (x-in-workspace-from-view-pad
				 x2-in-view-pad view-pad)
			       left-edge-in-workspace))
	       (y2-in-icon (-w (y-in-workspace-from-view-pad
				 y2-in-view-pad view-pad)
			       top-edge-in-workspace))
	       
	       (icon-width (-w max-x-in-workspace min-x-in-workspace))
	       (icon-height (-w max-y-in-workspace min-y-in-workspace))
	       
	       (arc-marker
		 (make-entity-with-specific-icon-description
		   'iconic-entity
		   (wrap-polychrome-declaration-around-slot-value-conses
		     color
		     (slot-value-list
		       (slot-value-list
			 'lines
			 (slot-value-list x0-in-icon y0-in-icon)
			 (slot-value-list 'arc
					  (slot-value-list
					    x1-in-icon y1-in-icon))
			 (slot-value-list x2-in-icon y2-in-icon))))
		   ;; eg.  `((lines (0 2) (arc (2 4)) (4 2)))
		   (minw icon-width
			 (-w right-edge-to-clip-in-workspace
			     left-edge-in-workspace))
		   (minw icon-height
			 (-w bottom-edge-to-clip-in-workspace
			     top-edge-in-workspace)))))
	  (push-marker-in-view-pad arc-marker view-pad)
	  (add-to-workspace arc-marker (icon-editor-view-pad-workspace view-pad)
			    left-edge-in-workspace top-edge-in-workspace t))
	;; ELSE if not min-x-in-view-pad?
	(if (=w x0-in-view-pad x1-in-view-pad x2-in-view-pad)
	    (put-line-marker-in-view-pad
	      x0-in-view-pad
	      (minf y0-in-view-pad y1-in-view-pad y2-in-view-pad)
	      X0-in-view-pad
	      (maxf y0-in-view-pad y1-in-view-pad y2-in-view-pad)
	      view-pad
	      color
	      left-edge-to-clip-in-workspace top-edge-to-clip-in-workspace
	      right-edge-to-clip-in-workspace bottom-edge-to-clip-in-workspace nil)
	    (let* ((x-in-view-pad-of-left-most-point
		     (minf x0-in-view-pad x1-in-view-pad x2-in-view-pad))
		   (x-in-view-pad-of-right-most-point
		     (maxf x0-in-view-pad x1-in-view-pad x2-in-view-pad))
		   (y-in-view-pad-of-left-most-point
		     (cond
		       ((=f x-in-view-pad-of-left-most-point x0-in-view-pad)
			y0-in-view-pad)
		       ((=f x-in-view-pad-of-left-most-point x1-in-view-pad)
			y1-in-view-pad)
		       (t y2-in-view-pad)))
		   (y-in-view-pad-of-right-most-point
		     (cond
		       ((=f x-in-view-pad-of-right-most-point x0-in-view-pad)
			y0-in-view-pad)
		       ((=f x-in-view-pad-of-right-most-point x1-in-view-pad)
			y1-in-view-pad)
		       (t y2-in-view-pad))))
	      (put-line-marker-in-view-pad
		x-in-view-pad-of-left-most-point
		y-in-view-pad-of-left-most-point
		x-in-view-pad-of-right-most-point
		y-in-view-pad-of-right-most-point 
		view-pad color
		left-edge-to-clip-in-workspace top-edge-to-clip-in-workspace
		right-edge-to-clip-in-workspace bottom-edge-to-clip-in-workspace nil))))))


;; NEW, but has bugs:
;(defun-substitution-macro put-arc-marker-in-view-pad
;				    (x0-in-view-pad
;				      y0-in-view-pad
;				      x1-in-view-pad
;				      y1-in-view-pad
;				      x2-in-view-pad
;				      y2-in-view-pad
;				      view-pad
;				      color
;				      left-edge-to-clip-in-workspace
;				      top-edge-to-clip-in-workspace
;				      right-edge-to-clip-in-workspace
;				      bottom-edge-to-clip-in-workspace)
 
;  (multiple-value-bind (min-x-in-view-pad? min-y-in-view-pad?
;			max-x-in-view-pad? max-y-in-view-pad?)
;      (compute-arc-bounding-box
;	x0-in-view-pad y0-in-view-pad x1-in-view-pad y1-in-view-pad
;	x2-in-view-pad y2-in-view-pad)

;  (if min-x-in-view-pad?
;      (let* ((min-x-in-workspace
;	       (maxw (x-in-workspace-from-view-pad min-x-in-view-pad? view-pad)
;		     left-edge-to-clip-in-workspace))
;	     (min-y-in-workspace
;	       (maxw (y-in-workspace-from-view-pad min-y-in-view-pad? view-pad)
;		     top-edge-to-clip-in-workspace))

;	     (max-x-in-workspace
;	       (minw
;		 (x-in-workspace-from-view-pad max-x-in-view-pad? view-pad)
;		 (-w (+w right-edge-to-clip-in-workspace 1) left-edge-to-clip-in-workspace)))
;	     (max-y-in-workspace
;	       (minw
;		 (y-in-workspace-from-view-pad max-y-in-view-pad? view-pad)
;		 (-w (+w bottom-edge-to-clip-in-workspace 1) top-edge-to-clip-in-workspace)))

;	     (left-edge-in-workspace min-x-in-workspace)
;	     (top-edge-in-workspace min-y-in-workspace)
	     
;	     (x0-in-icon (-w (x-in-workspace-from-view-pad
;			       x0-in-view-pad view-pad)
;			     left-edge-in-workspace))
;	     (y0-in-icon (-w (y-in-workspace-from-view-pad
;			       y0-in-view-pad view-pad)
;			     top-edge-in-workspace))
;	     (x1-in-icon (-w (x-in-workspace-from-view-pad
;			       x1-in-view-pad view-pad)
;			     left-edge-in-workspace))
;	     (y1-in-icon (-w (y-in-workspace-from-view-pad
;			       y1-in-view-pad view-pad)
;			     top-edge-in-workspace))
;	     (x2-in-icon (-w (x-in-workspace-from-view-pad
;			       x2-in-view-pad view-pad)
;			     left-edge-in-workspace))
;	     (y2-in-icon (-w (y-in-workspace-from-view-pad
;			       y2-in-view-pad view-pad)
;			     top-edge-in-workspace))
	     
;	     (icon-width (-w max-x-in-workspace min-x-in-workspace))
;	     (icon-height (-w max-y-in-workspace min-y-in-workspace))
	     
;	     (arc-marker
;	       (make-entity-with-specific-icon-description
;		 'iconic-entity
;		 (wrap-polychrome-declaration-around-slot-value-conses
;		   color
;		   (slot-value-list
;		     (slot-value-list
;		       'lines
;		       (slot-value-list x0-in-icon y0-in-icon)
;		       (slot-value-list 'arc
;					(slot-value-list
;					  x1-in-icon y1-in-icon))
;		       (slot-value-list x2-in-icon y2-in-icon))))
;		 ;; eg.  `((lines (0 2) (arc (2 4)) (4 2)))
;		 (minw icon-width 500)		; 500 is maximum size of raster we want to handle
;		 (minw icon-height 500))))
;	(push-marker-in-view-pad arc-marker view-pad)
;	(add-to-workspace arc-marker (icon-editor-view-pad-workspace view-pad)
;			  left-edge-in-workspace top-edge-in-workspace t))
;	(if (=w x0-in-view-pad x1-in-view-pad x2-in-view-pad)
;	    (put-line-marker-in-view-pad
;	      x0-in-view-pad
;	      (minf y0-in-view-pad y1-in-view-pad y2-in-view-pad)
;	      X0-in-view-pad
;	      (maxf y0-in-view-pad y1-in-view-pad y2-in-view-pad)
;	      view-pad
;	      color
;	      left-edge-to-clip-in-workspace top-edge-to-clip-in-workspace
;	      right-edge-to-clip-in-workspace bottom-edge-to-clip-in-workspace nil)
;	    (let* ((x-in-view-pad-of-left-most-point
;		     (minf x0-in-view-pad x1-in-view-pad x2-in-view-pad))
;		   (x-in-view-pad-of-right-most-point
;		     (maxf x0-in-view-pad x1-in-view-pad x2-in-view-pad))
;		   (y-in-view-pad-of-left-most-point
;		     (cond
;		       ((=f x-in-view-pad-of-left-most-point x0-in-view-pad)
;			y0-in-view-pad)
;		       ((=f x-in-view-pad-of-left-most-point x1-in-view-pad)
;			y1-in-view-pad)
;		       (t y2-in-view-pad)))
;		   (y-in-view-pad-of-right-most-point
;		     (cond
;		       ((=f x-in-view-pad-of-right-most-point x0-in-view-pad)
;			y0-in-view-pad)
;		       ((=f x-in-view-pad-of-right-most-point x1-in-view-pad)
;			y1-in-view-pad)
;		       (t y2-in-view-pad))))
;	      (put-line-marker-in-view-pad
;		x-in-view-pad-of-left-most-point
;		y-in-view-pad-of-left-most-point
;		x-in-view-pad-of-right-most-point
;		y-in-view-pad-of-right-most-point 
;		view-pad color
;		left-edge-to-clip-in-workspace top-edge-to-clip-in-workspace
;		right-edge-to-clip-in-workspace bottom-edge-to-clip-in-workspace nil))))))







;;; The function `pop-marker-from-view-pad' removes the last marker from
;;; the view pad.

(defun-substitution-macro pop-marker-from-view-pad (view-pad)
  (let* ((marker-stack?
	   (icon-editor-view-pad-marker-stack view-pad)))
    (when marker-stack?
      (let* ((frame-and-serial-number-pair (car marker-stack?))
	     (frame (car frame-and-serial-number-pair))
	     (serial-number (cdr frame-and-serial-number-pair)))
	(if (frame-has-not-been-reprocessed-p
	      frame serial-number)
	    (delete-frame frame))
	(reclaim-frame-serial-number serial-number)
	(reclaim-icon-editor-cons frame-and-serial-number-pair)
	(setf (icon-editor-view-pad-marker-stack view-pad)
	      (cdr marker-stack?))
	(reclaim-icon-editor-cons marker-stack?)))))








(defun-substitution-macro place-icon-editor-view-pad-on-workspace
				    (view-pad workspace)
  #+development (gensym-assert (and (icon-editor-view-pad-p view-pad)
				    (frame-of-class-p workspace
						      'icon-editor-workspace)))
  (let* ((bounding-box
	   (icon-editor-view-pad-bounding-box view-pad))
	 (bounding-box-border-width
	   (adjusted-bounding-box-border-width bounding-box))
	 (x-in-workspace
	   (icon-editor-view-pad-x-in-workspace view-pad))
	 (y-in-workspace
	   (icon-editor-view-pad-y-in-workspace view-pad))
	 (x-origin-in-workspace
	   (+w x-in-workspace bounding-box-border-width))
	 (y-origin-in-workspace
	   (+w y-in-workspace bounding-box-border-width)))

    ;; Put bounding box on workspace:
    (add-to-workspace bounding-box workspace
		      x-in-workspace y-in-workspace)

    ;; Put icon origin into memory:
    (setf (icon-editor-view-pad-x-origin-in-workspace view-pad)
	  x-origin-in-workspace)
    (setf (icon-editor-view-pad-y-origin-in-workspace view-pad)
	  y-origin-in-workspace)

    ;; Remember the workspace:
    (setf (icon-editor-view-pad-workspace view-pad) workspace)

    ;; Set width and height of view pad:
    ;; We assume that the view pad occupies all the workspace
    ;; to the right of and below x-in-workspace and y-in-workspace.
    (setf (icon-editor-view-pad-width view-pad)
	  (maxw
	    (width-of-block bounding-box)
	    (-w (width-of-block workspace)	;assume start at 0
		x-in-workspace)))
    (setf (icon-editor-view-pad-height view-pad)
	  (maxw
	    (height-of-block bounding-box)
	    (-w (height-of-block workspace)	;assume start at 0
		y-in-workspace)))

    ;; Size bounding box to contain the default icon width and height:
    ;; This should be done last so that view-pad has the required information
    ;; for the macro x-in-workspace-from-view-pad.
    (update-border-of-bounding-box
      bounding-box nil nil
      (x-in-workspace-from-view-pad-workspace
	(adjusted-delta-x-for-icon-delta-x
	  (delta-x-in-workspace-from-view-pad (default-width-of-icon) view-pad))
	view-pad)
      (y-in-workspace-from-view-pad-workspace
	(adjusted-delta-y-for-icon-delta-y
	  (delta-y-in-workspace-from-view-pad (default-height-of-icon) view-pad))
	view-pad))))











;;; The Layers Pad



;;; The substitution macro `point-in-layers-pad-p' returns nil if the
;;; given point (in workspace coordinates) is not in the layers pad.  Non-nil
;;; is returned otherwise.  Only entities that belong in the layers pad 
;;; should be placed there.

(defun-substitution-macro point-in-layers-pad-p 
				    (x-in-workspace y-in-workspace layers-pad)
  #+development (gensym-assert (icon-editor-layers-pad-p layers-pad))
  (let* ((bounding-box
	   (icon-editor-layers-pad-bounding-box layers-pad))
	 (inner-left-edge-in-workspace
	   (icon-editor-layers-pad-x-origin-in-workspace layers-pad))
	 (inner-top-edge-in-workspace
	   (icon-editor-layers-pad-y-origin-in-workspace layers-pad))
	 (adjusted-bounding-box-border-width
	   (adjusted-bounding-box-border-width bounding-box))
	 (inner-right-edge-in-workspace
	   (-w (right-edge-of-block bounding-box)
	       adjusted-bounding-box-border-width))
	 (inner-bottom-edge-in-workspace
	   (-w (bottom-edge-of-block bounding-box)
	       adjusted-bounding-box-border-width)))
;    (format t "~%~a,~a,~a : ~a,~a,~a"
;	    inner-left-edge-in-workspace x-in-workspace inner-right-edge-in-workspace
;	    inner-top-edge-in-workspace y-in-workspace inner-bottom-edge-in-workspace)
    (and (<=w inner-left-edge-in-workspace x-in-workspace)
	 (<w x-in-workspace inner-right-edge-in-workspace)
	 (<=w inner-top-edge-in-workspace y-in-workspace)
	 (<w y-in-workspace inner-bottom-edge-in-workspace))))








;;; The function `create-layer-box' ...

(defmacro-for-constant space-between-edges-in-layer-box 1)

(defun create-layer-box (icon-editor layer layer-index x-scale y-scale)
  (declare (type fixnum layer-index x-scale y-scale))
  (let* ((symbol-for-label (label-of-layer layer))
	 (engine (icon-editor-engine icon-editor))
	 (layers-pad (icon-editor-layers-pad icon-editor))
	 (icon-width (icon-editor-engine-icon-width engine))
	 (icon-height (icon-editor-engine-icon-height engine))
	 (alist (icon-editor-region-and-name-alist icon-editor))
	 (color (cdr (assq symbol-for-label alist)))
	 (border-width
	   (icon-editor-layers-pad-layer-box-border-width layers-pad))
	 (scaled-icon-width
	   (delta-x-in-workspace-from-target icon-width x-scale))
	 (scaled-icon-height
	   (delta-y-in-workspace-from-target icon-height y-scale))
	 (list-of-layers (icon-editor-cons layer nil))
	 (layer-box-x-offset-of-layer-icon-from-x0
	   (+w border-width (space-between-edges-in-layer-box)))
	 (layer-box-y-offset-of-layer-icon-from-y0
	   (+w border-width (space-between-edges-in-layer-box)))
	 (icon-outline-left-edge-in-border-icon
	   (-w layer-box-x-offset-of-layer-icon-from-x0 2))
	 (icon-outline-top-edge-in-border-icon
	   (-w layer-box-y-offset-of-layer-icon-from-y0 2))
	 (icon-outline-right-edge-in-border-icon
	   (+w scaled-icon-width
	       layer-box-x-offset-of-layer-icon-from-x0
	       2))
	 (icon-outline-bottom-edge-in-border-icon
	   (+w scaled-icon-height
	       layer-box-y-offset-of-layer-icon-from-y0
	       2)))
    (declare (type fixnum icon-width icon-height))
    (setf (label-of-layer layer) 'foreground)	; temporarily
    (let* ((variable-spec-list 
	     (icon-editor-variable-spec-list icon-editor))
	   (background-layer
	     (icon-editor-icon-background-image icon-editor))
	   (stipple-spec
	     (icon-editor-stipple-spec icon-editor))
	   (layer-icon
	     (make-entity-with-specific-icon-description
	       'iconic-entity
	       (convert-list-of-layers-to-line-drawing-description
		 list-of-layers alist variable-spec-list
		 background-layer
		 scaled-icon-width scaled-icon-height
		 x-scale y-scale t t stipple-spec)
	        scaled-icon-width scaled-icon-height)))
      (setf (label-of-layer layer) symbol-for-label)	; set it back
      (reclaim-icon-editor-cons list-of-layers)
      (let* ((text-for-label
	       (make-free-text-box
		 (twith-output-to-text-string
		   (tformat "~(~a~)" symbol-for-label))
		 'borderless-free-text nil
		 (-w (default-layers-pad-width) 22)
		 ellipsis-text-string))
	     (scaled-width-of-layer-box
	       (icon-editor-layers-pad-max-layer-box-width layers-pad))
	     (scaled-height-of-layer-box
	       (+w (twicew border-width)
		   (*w 4 (space-between-edges-in-layer-box))
		   scaled-icon-height
		   (height-of-block text-for-label)
		   -1))
	     (border-icon
	       (make-entity-with-specific-icon-description
		 'iconic-entity
		 (slot-value-list
		   (slot-value-list
		     'polychrome
		     (slot-value-cons 'border 'transparent)
		     (slot-value-cons 'transparent 'transparent) ;pbk
		     (slot-value-cons 'outline 'black))
		   'border
		   (slot-value-list
		     'solid-rectangle
		     (slot-value-list 0 0)
		     (slot-value-list scaled-width-of-layer-box scaled-height-of-layer-box))
		   'transparent
		   (slot-value-list
		     'solid-rectangle
		     (slot-value-list border-width border-width)
		     (slot-value-list (-w scaled-width-of-layer-box border-width)
				      (-w scaled-height-of-layer-box
					  border-width)))
		   'outline
		   (slot-value-list
		     'outline
		     (slot-value-list 0 0)
		     (slot-value-list 0 scaled-height-of-layer-box)
		     (slot-value-list scaled-width-of-layer-box
				      scaled-height-of-layer-box)
		     (slot-value-list scaled-width-of-layer-box 0))
		   		   (slot-value-list
		     'outline
		     (slot-value-list icon-outline-left-edge-in-border-icon
				      icon-outline-top-edge-in-border-icon)
		     (slot-value-list icon-outline-left-edge-in-border-icon
				      icon-outline-bottom-edge-in-border-icon)
		     (slot-value-list icon-outline-right-edge-in-border-icon
				      icon-outline-bottom-edge-in-border-icon)
		     (slot-value-list icon-outline-right-edge-in-border-icon
				      icon-outline-top-edge-in-border-icon)))
		 scaled-width-of-layer-box scaled-height-of-layer-box)))
	      
	
;    (format t "~%~a,~a,~a,~a"
;      scaled-icon-width scaled-icon-height scaled-height-of-layer-box x-scale)
	(let* ((layer-box
		 (make-layer-box border-icon text-for-label
				 layer-icon (copy-frame-serial-number (current-frame-serial-number)))))
	  (setf (layer-box-layer layer-box) layer)
	  (setf (layer-box-x-offset-of-layer-icon-from-x0 layer-box)
		layer-box-x-offset-of-layer-icon-from-x0)
	  (setf (layer-box-y-offset-of-layer-icon-from-y0 layer-box)
		layer-box-y-offset-of-layer-icon-from-y0)
	  (setf (layer-box-x-offset-of-border-icon-from-x0 layer-box) 0)
	  (setf (layer-box-y-offset-of-border-icon-from-y0 layer-box) 0)
	  (setf (layer-box-x-offset-of-text-from-x0 layer-box)
		(layer-box-x-offset-of-layer-icon-from-x0 layer-box))
	  (setf (layer-box-y-offset-of-text-from-y0 layer-box)
		(+w (layer-box-y-offset-of-layer-icon-from-y0 layer-box)
		    scaled-icon-height
		    (space-between-edges-in-layer-box)))
	  (setf (layer-box-color? layer-box) color)
	  (setf (layer-box-label layer-box) symbol-for-label)
	  (setf (layer-box-layer-index layer-box) layer-index)
	  layer-box)))))


;;; The function/macro `check-and-repair-layer-box-if-necessary' deletes
;;; the layer-box it is given and returns nil if any of its frames have been
;;; reprocessed.  If the layer-box is ok, the layer-box itself is returned.

(defun-substitution-macro check-and-repair-layer-box-if-necessary
				    (layer-box)
  (let* ((serial-number
	   (layer-box-reference-serial-number layer-box)))
    (if (or (frame-has-been-reprocessed-p
	      (layer-box-border-icon layer-box) serial-number)
	    (frame-has-been-reprocessed-p
	      (layer-box-text-for-label layer-box) serial-number)
	    (frame-has-been-reprocessed-p
	      (layer-box-layer-icon layer-box) serial-number))
	(progn
	  (delete-layer-box layer-box)
	  nil)
	layer-box)))


(defun get-or-create-layer-box (icon-editor layer layer-index)
  (declare (type fixnum layer-index))
  (let* ((layer-box? (layer-box?-of-layer layer)))
    (if layer-box?
	(setq layer-box?
	      (check-and-repair-layer-box-if-necessary layer-box?)))
    (if layer-box?
	(progn
	  (setf (layer-box-layer-index layer-box?) layer-index)	; in case it wasn't set.
	  layer-box?)
	(let* ((layers-pad (icon-editor-layers-pad icon-editor)))
	  (setq layer-box?
		(create-layer-box
		  icon-editor
		  layer
		  layer-index
		  (icon-editor-layers-pad-x-scale layers-pad)
		  (icon-editor-layers-pad-y-scale layers-pad)))
	  (setf (layer-box?-of-layer layer) layer-box?)
	  layer-box?))))




;;; The macros `update-layer-color-of-layer-box', `highlight-layer-box',
;;; and `unhighlight-layer-box' ...

(defun-substitution-macro update-layer-color-of-layer-box
				    (layer-box)
  (let* ((color? (layer-box-color? layer-box)))
    (if (drawing-elements-of-layer (layer-box-layer layer-box))
	(change-color-of-item
	  (layer-box-layer-icon layer-box)
	  nil 'icon-color
	  (if (or (null color?)
		  (eq color? 'transparent)
		  (eq color? 'white))
	      'foreground
	      color?)))))


(defun-substitution-macro highlight-layer-box (layer-box)
  (let* ((color (or (layer-box-color? layer-box) 'foreground)))
    (change-color-of-item
      (layer-box-border-icon layer-box)
      nil 'border
      (if (or (eq color 'white) (eq color 'transparent))
	  'foreground
	  color))))
		     

(defun-substitution-macro unhighlight-layer-box (layer-box)
  (change-color-of-item
   (layer-box-border-icon layer-box)
   nil 'border 'transparent))




;;; The function `place-layer-box-in-workspace' ...
;;; It assumes that the following slots in layer-box have already been
;;; set: layer-box-x0-in-layers-pad, layer-box-y0-in-layers-pad,
;;; layer-box-x-offset-of-layer-icon-from-x0,
;;; layer-box-y-offset-of-layer-icon-from-y0,
;;; layer-box-x-offset-of-border-icon-from-x0,
;;; layer-box-y-offset-of-border-icon-from-y0,
;;; layer-box-x-offset-of-text-from-x0,
;;; layer-box-y-offset-of-text-from-y0.

(defun reset-y-midpoint-of-layer-box (layer-box)
  (setf (layer-box-y-midpoint-in-workspace layer-box)
	(halfw (+w (layer-box-top-edge-in-workspace layer-box)
		   (layer-box-bottom-edge-in-workspace layer-box)))))



(defun place-layer-box-in-workspace (x0-in-workspace y0-in-workspace
				     layer-box layers-pad workspace)
  (setf (layer-box-x0-in-layers-pad layer-box)
	(-w x0-in-workspace
	    (icon-editor-layers-pad-x-origin-in-workspace layers-pad)))
  (setf (layer-box-y0-in-layers-pad layer-box)
	(-w y0-in-workspace
	    (icon-editor-layers-pad-y-origin-in-workspace layers-pad)))
  (add-to-workspace
    (layer-box-border-icon layer-box)
    workspace
    (+w x0-in-workspace
	(layer-box-x-offset-of-border-icon-from-x0 layer-box))
    (+w y0-in-workspace
	(layer-box-y-offset-of-border-icon-from-y0 layer-box))
    t)
  (add-to-workspace
    (layer-box-text-for-label layer-box)
    workspace
    (+w x0-in-workspace
	(layer-box-x-offset-of-text-from-x0 layer-box))
    (+w y0-in-workspace
	(layer-box-y-offset-of-text-from-y0 layer-box))
    t)
  (add-to-workspace
    (layer-box-layer-icon layer-box)
    workspace
    (+w x0-in-workspace
	(layer-box-x-offset-of-layer-icon-from-x0 layer-box))
    (+w y0-in-workspace
	(layer-box-y-offset-of-layer-icon-from-y0 layer-box))
    t)
  (update-layer-color-of-layer-box layer-box)
  (reset-y-midpoint-of-layer-box layer-box))



(defun place-layer-box-in-layers-pad (x0-in-layers-pad y0-in-layers-pad
				      layer-box layers-pad workspace)
  (let* ((x0-in-workspace
	   (+w (icon-editor-layers-pad-x-origin-in-workspace layers-pad)
	       x0-in-layers-pad))
	 (y0-in-workspace
	   (+w (icon-editor-layers-pad-y-origin-in-workspace layers-pad)
	       y0-in-layers-pad)))
    (place-layer-box-in-workspace
      x0-in-workspace y0-in-workspace layer-box layers-pad workspace)))
  




;;; The functions `move-layer-box-in-workspace'
;;; and `move-layer-box-in-layers-pad' ...

(defun move-layer-box-in-workspace (x-in-workspace y-in-workspace
				    layer-box layers-pad)
  (let* ((workspace
	   (icon-editor-layers-pad-workspace layers-pad))
	 (delta-x
	   (-w x-in-workspace
	       (layer-box-left-edge-in-workspace layer-box)))
	 (delta-y
	   (-w (layer-box-top-edge-in-workspace layer-box)
	       y-in-workspace))
	 (border-icon (layer-box-border-icon layer-box)))
  (cond
    ((eq (superblock? border-icon)
	 workspace)
     (move-item-by				; +ve y is up
       border-icon delta-x delta-y nil)
     (move-item-by
       (layer-box-text-for-label layer-box)
       delta-x delta-y nil)
     (move-item-by
       (layer-box-layer-icon layer-box)
       delta-x delta-y nil))
    (t
     (add-to-workspace
       border-icon workspace x-in-workspace y-in-workspace t)
     (add-to-workspace
       (layer-box-text-for-label layer-box)
       workspace x-in-workspace y-in-workspace t)
     (add-to-workspace
       (layer-box-layer-icon layer-box)
       workspace x-in-workspace y-in-workspace t)))
    (setf (layer-box-x0-in-layers-pad layer-box)
	  (-w x-in-workspace
	      (icon-editor-layers-pad-x-origin-in-workspace layers-pad)))
    (setf (layer-box-y0-in-layers-pad layer-box)
	  (-w y-in-workspace
	      (icon-editor-layers-pad-y-origin-in-workspace layers-pad)))
    (reset-y-midpoint-of-layer-box layer-box)))



(defun move-layer-box-in-layers-pad (x-in-layers-pad y-in-layers-pad
				     layer-box layers-pad)
  (move-layer-box-in-workspace
    (+w x-in-layers-pad
	(icon-editor-layers-pad-x-origin-in-workspace layers-pad))
    (+w y-in-layers-pad
	(icon-editor-layers-pad-y-origin-in-workspace layers-pad))
    layer-box
    layers-pad))



;;; The function `place-icon-editor-layers-pad-on-workspace' ...

(defun-substitution-macro place-icon-editor-layers-pad-on-workspace
				    (layers-pad workspace)
  #+development (gensym-assert (and (icon-editor-layers-pad-p layers-pad)
				    (frame-of-class-p workspace
						      'icon-editor-workspace)))
  (setf (icon-editor-layers-pad-workspace layers-pad) workspace)
  (add-to-workspace (icon-editor-layers-pad-bounding-box layers-pad)
		    workspace
		    (icon-editor-layers-pad-x-in-workspace layers-pad)
		    (icon-editor-layers-pad-y-in-workspace layers-pad)))






(defun heuristically-compute-maximum-height-of-layers-box (number-of-layers)
  (cond
    ((<=f number-of-layers 2)  (default-maximum-layer-box-height))
    ((<=f number-of-layers 3)  100)
    ((<=f number-of-layers 4)  75)
    ((<=f number-of-layers 5)  50)
    ((<=f number-of-layers 8) 25)
    ((<=f number-of-layers 10) 20)
    ((<=f number-of-layers 15) 20)
    (t 15)))



;;; The function `heuristically-compute-layers-pad-scale' ...

(defun heuristically-compute-layers-pad-scale (icon-width icon-height
					       maximum-icon-width
					       maximum-icon-height)
  (cond
    ((and (<=w icon-width maximum-icon-width)
	  (<=w icon-height maximum-icon-height))
     (icon-editor-normalized-scale-factor))
    (t
     (minw				; largest scale to fit icon in layer box
       (roundw (*f maximum-icon-height (icon-editor-normalized-scale-factor))
	       icon-height)
       (roundw (*f maximum-icon-width (icon-editor-normalized-scale-factor))
	       icon-width)))))




;;; The function `delete-all-layer-boxes' ...

(defun delete-all-layer-boxes (layers)
  (loop for layer in layers
	do
    (reclaim-icon-editor-slot-value (layer-box?-of-layer layer))
    (setf (layer-box?-of-layer layer) nil)))



;;; The function `recompute-scale-for-layers-pad' ...

(defun recompute-scale-for-layers-pad (icon-editor)
  (let* ((engine (icon-editor-engine icon-editor))
	 (layers-pad (icon-editor-layers-pad icon-editor))
	 (icon-width (icon-editor-engine-icon-width engine))
	 (icon-height (icon-editor-engine-icon-height engine))
	 (new-maximum-height
	   (heuristically-compute-maximum-height-of-layers-box
	     (icon-editor-engine-number-of-layers engine))))
    (when (/=w new-maximum-height
	       (icon-editor-layers-pad-max-layer-height layers-pad))
      (setf (icon-editor-layers-pad-max-layer-height layers-pad)
	    new-maximum-height)
      (delete-all-layer-boxes
	(icon-editor-engine-layers engine)))
    (let* ((scale
	     (heuristically-compute-layers-pad-scale 
	       icon-width icon-height
	       (icon-editor-layers-pad-max-layer-width layers-pad)
	       (icon-editor-layers-pad-max-layer-height layers-pad))))
      (setf (icon-editor-layers-pad-x-scale layers-pad) scale)
      (setf (icon-editor-layers-pad-y-scale layers-pad) scale))))




(defun move-or-place-layer-box-in-workspace (icon-editor layer layer-index
					     x-in-workspace y-in-workspace)
  (let* ((layer-box? (layer-box?-of-layer layer))
	 (layers-pad (icon-editor-layers-pad icon-editor))
	 (workspace (icon-editor-workspace icon-editor)))
    (cond
      (layer-box?
       (if (eq (superblock? (layer-box-border-icon layer-box?))
	       workspace)
	   (move-layer-box-in-workspace
	     x-in-workspace y-in-workspace layer-box? layers-pad)
	   (place-layer-box-in-workspace
	     x-in-workspace
	     y-in-workspace
	     layer-box? layers-pad workspace)))
      (t
       (setq layer-box?
	     (create-layer-box
	       icon-editor layer layer-index
	       (icon-editor-layers-pad-x-scale layers-pad)
	       (icon-editor-layers-pad-y-scale layers-pad)))
       (setf (layer-box?-of-layer layer)
	     layer-box?)
       (place-layer-box-in-workspace
	 x-in-workspace
	 y-in-workspace
	 layer-box? layers-pad workspace)))))


(defun move-or-place-layer-box-in-layers-pad (icon-editor layer layer-index
					      x-in-layers-pad y-in-layers-pad)
  (let* ((layers-pad (icon-editor-layers-pad icon-editor))
	 (x-in-workspace
	   (+w
	     (icon-editor-layers-pad-x-origin-in-workspace layers-pad)
	     x-in-layers-pad))
	 (y-in-workspace
	   (+w
	     (icon-editor-layers-pad-y-origin-in-workspace layers-pad)
	     y-in-layers-pad)))
    (move-or-place-layer-box-in-workspace
      icon-editor layer layer-index x-in-workspace y-in-workspace)))






;;; The function `delete-layer-box-label-if-necessary' returns t if
;;; it deletes the layer-box, nil otherwise.

(defun delete-layer-box-label-if-necessary (layer)
  (let* ((layer-box? (layer-box?-of-layer layer)))
    (when (and layer-box?
	       (neq (label-of-layer layer)
		    (layer-box-label layer-box?)))
      (reclaim-icon-editor-slot-value layer-box?)
      (setf (layer-box?-of-layer layer) nil)
      t)))






;;; The function `handle-redrawing-layers-in-layers-pad' ...


;; Change the args list to just icon-editor!!! -pto 05oct89

(defun handle-redrawing-layers-in-layers-pad (icon-editor)
  (let* ((layers-pad (icon-editor-layers-pad icon-editor))
	 (engine (icon-editor-engine icon-editor))
	 (layers (icon-editor-engine-layers engine))
	 (bounding-box (icon-editor-layers-pad-bounding-box layers-pad))
	 (current-layer (icon-editor-engine-current-layer engine)))
    #+development (gensym-assert (and (framep bounding-box)
				      (frame-of-class-p bounding-box
							'bounding-box)))
    (let* ((maximum-y-in-layers-pad 0))
      (loop with layer-box
	    with layer-index = 0
	    for layer in layers
	    do
	(setq layer-box
	      (get-or-create-layer-box icon-editor layer layer-index))
	(incfw maximum-y-in-layers-pad
	       (+w (layer-box-height layer-box)
		   (space-between-edges-in-layer-box)))
	(incff layer-index))
	
	(update-border-of-bounding-box		; this also expands the workspace if necessary
	  bounding-box nil nil nil
	  (+w (icon-editor-layers-pad-y-origin-in-workspace layers-pad)
	      (space-between-edges-in-layer-box)
	      maximum-y-in-layers-pad))
	
	(let* ((x-in-layers-pad 0)
	       (y-in-layers-pad 0)
	       (reversed-layers
		 (reverse-using-icon-editor-conses layers)))
	  (loop with layer-index = (icon-editor-engine-number-of-layers engine)
		with layer-box
		for layer in reversed-layers
		do
	    (decff layer-index)
	    (delete-layer-box-label-if-necessary layer)
	    (move-or-place-layer-box-in-layers-pad
	      icon-editor layer layer-index
	      x-in-layers-pad y-in-layers-pad)
	    (setq layer-box (layer-box?-of-layer layer))
	    (if (eq current-layer layer)
		(highlight-layer-box layer-box)
		(unhighlight-layer-box layer-box))
	    (setf (layer-box-color? layer-box)
		  (cdr (assq (label-of-layer layer)
			     (icon-editor-region-and-name-alist icon-editor))))
	    (update-layer-color-of-layer-box layer-box)

	    (setq y-in-layers-pad
		  (+w y-in-layers-pad
		      (layer-box-height layer-box)
		      (space-between-edges-in-layer-box))))
	  (reclaim-icon-editor-list reversed-layers)))))





(defun handle-moving-layer-box-in-layers-pad (icon-editor
					      x-in-layers-pad y-in-layers-pad)
  (let* ((engine (icon-editor-engine icon-editor))
	 (layers-pad (icon-editor-layers-pad icon-editor))
	 (layer-box?
	   (layer-box?-of-layer
	     (icon-editor-engine-current-layer engine))))
    (when layer-box?
      (move-layer-box-in-layers-pad
	x-in-layers-pad y-in-layers-pad layer-box? layers-pad)
      t)))



(defun handle-resizing-layer-boxes-if-necessary (icon-editor)
  (recompute-scale-for-layers-pad icon-editor)
  (handle-redrawing-layers-in-layers-pad icon-editor))



(defun-substitution-macro handle-deleting-layer-in-layers-pad
				    (icon-editor layer-index)
  #+development
  (declare (ignore layer-index))
  ;; Can optimize this
  (handle-resizing-layer-boxes-if-necessary icon-editor))


(defun-substitution-macro handle-adding-layer-in-layers-pad
				    (icon-editor arg-1? arg-2?)
  #+development
  (declare (ignore icon-editor arg-1? arg-2?)))



(defun-substitution-macro
  handle-changing-color-of-current-layer-in-layers-pad
  (icon-editor arg-1? arg-2?)
  #+development
  (declare (ignore icon-editor arg-1? arg-2?)))


(defun redraw-label-box (icon-editor layer layer-index)
  (let* ((engine (icon-editor-engine icon-editor))
	 (old-layer-box? (layer-box?-of-layer layer)))
    (setf (layer-box?-of-layer layer) nil)
    (let* ((layer-box
	     (get-or-create-layer-box icon-editor layer layer-index)))
      (if old-layer-box?
	  (let* ((x-in-workspace
		   (layer-box-left-edge-in-workspace old-layer-box?))
		 (y-in-workspace
		   (layer-box-top-edge-in-workspace old-layer-box?)))
	    (reclaim-icon-editor-slot-value old-layer-box?)
	    (place-layer-box-in-workspace
	      x-in-workspace y-in-workspace layer-box
	      (icon-editor-layers-pad icon-editor)
	      (icon-editor-workspace icon-editor))
	    (if (eq (icon-editor-engine-current-layer engine) layer)
		(highlight-layer-box layer-box)))
	  (handle-redrawing-layers-in-layers-pad icon-editor)))))



(defun handle-changing-label-of-layer-in-layers-pad
       (icon-editor layer-index label)
  (declare (ignore label))
  (let* ((engine (icon-editor-engine icon-editor))
	 (layer (nth layer-index
		     (icon-editor-engine-layers engine)))
	 (old-layer-box? (layer-box?-of-layer layer)))
    (setf (layer-box?-of-layer layer) nil)
    (reclaim-icon-editor-slot-value old-layer-box?)
    (redraw-label-box icon-editor layer layer-index)
    ))





(defun-substitution-macro handle-changing-color-of-region-in-layers-pad
				    (icon-editor label? color)
  (let* ((engine (icon-editor-engine icon-editor)))
    (cond
      (label?
       (loop with current-layer-index = (icon-editor-engine-current-layer-index
					  engine)
	     with layer-box
	     with layer-index = 0
	     for layer in (icon-editor-engine-layers engine)
	     do
	 (when (delete-layer-box-label-if-necessary layer)
	   (handle-redrawing-layers-in-layers-pad icon-editor)
	   (return))
	 (when (eq (label-of-layer layer) label?)
	   (setq layer-box (get-or-create-layer-box
			     icon-editor layer layer-index))
	   (setf (layer-box-color? layer-box) color)
	   (update-layer-color-of-layer-box layer-box)
	   (if (=f current-layer-index
		   (layer-box-layer-index layer-box))
	       (highlight-layer-box layer-box)))
	 (incff layer-index)))
      (t
       (let* ((current-layer (icon-editor-engine-current-layer engine))
	      (current-layer-index
		(icon-editor-engine-current-layer-index engine)))
	 (if (delete-layer-box-label-if-necessary current-layer)
	     (redraw-label-box
	       icon-editor current-layer current-layer-index)))))))




(defun-substitution-macro handle-changing-current-layer-in-layers-pad
				    (icon-editor old-layer-index new-layer-index)
  (let* ((engine (icon-editor-engine icon-editor))
	 (layers (icon-editor-engine-layers engine))
	 (old-layer (nth old-layer-index layers))
	 (new-layer (nth new-layer-index layers)))
    (highlight-layer-box 
      (get-or-create-layer-box icon-editor new-layer new-layer-index))
    (unhighlight-layer-box
      (get-or-create-layer-box icon-editor old-layer old-layer-index))))



(defun-substitution-macro handle-redrawing-current-layer-box
				    (icon-editor arg-1? arg-2?)
  #+development
  (declare (ignore arg-1? arg-2?))
  (let* ((engine (icon-editor-engine icon-editor))
	 (layer-index (icon-editor-engine-current-layer-index engine))
	 (layer (nth layer-index
		     (icon-editor-engine-layers engine))))
    (redraw-label-box icon-editor layer layer-index)))



(defun-substitution-macro handle-setting-color-of-layer 
				    (icon-editor layer-index new-color)
  (let* ((layer
	   (nth layer-index
		(icon-editor-engine-layers
		  (icon-editor-engine icon-editor))))
	 (layer-box
	   (get-or-create-layer-box icon-editor layer layer-index)))
    (setf (layer-box-color? layer-box) new-color)
    (update-layer-color-of-layer-box layer-box)))






(defun pick-layer-in-layers-pad (icon-editor x-in-workspace y-in-workspace)
  (let* ((engine (icon-editor-engine icon-editor))
	 (layers (icon-editor-engine-layers engine))
	 (reversed-layers (reverse-using-icon-editor-conses layers))
	 (layers-pad (icon-editor-layers-pad icon-editor))
	 (top-layer-index
	   (icon-editor-layers-pad-visible-top-layer-index layers-pad))
	 (number-of-layers
	   (icon-editor-engine-number-of-layers engine))
	 (layer-box-picked-p nil)
	 (old-layer-index
	   (icon-editor-engine-current-layer-index engine)))
    (loop with index = number-of-layers
	  with layer-box?
	  for layer in reversed-layers		; top down
	  do
      (decff index)
      (setq layer-box? (layer-box?-of-layer layer))
      (when (and layer-box? (<=f index top-layer-index))
	(when
	  (and (<=f (layer-box-left-edge-in-workspace layer-box?) x-in-workspace)
	       (<f x-in-workspace (layer-box-right-edge-in-workspace layer-box?))
	       (<=f (layer-box-top-edge-in-workspace layer-box?) y-in-workspace)
	       (<f y-in-workspace (layer-box-bottom-edge-in-workspace layer-box?)))
	  (if (/=f index old-layer-index)
	   
	      ;; Change icon editor current layer
	      (enqueue-icon-editor-translator-event
		icon-editor
		(icon-editor-translator-event 'change-current-layer)
		index nil))
	  (setq layer-box-picked-p t)
	  (return))))
    (reclaim-icon-editor-list reversed-layers)
   
    (if layer-box-picked-p
	(icon-editor-engine-current-layer engine)
	nil)))




(defun-substitution-macro handle-layers-pad-mouse-down
				    (icon-editor x-in-workspace y-in-workspace)
  (let* ((translator (icon-editor-translator icon-editor))
	 (layer?
	   (pick-layer-in-layers-pad icon-editor
				     x-in-workspace y-in-workspace)))
    (cond
      (layer?
       (setf (icon-editor-translator-state translator)
	     (icon-editor-state 'in-layers-pad))
       
       (let* ((layer-box? (layer-box?-of-layer layer?)))
	 (when layer-box?
	   (setf (layer-box-original-y-midpoint-in-workspace? layer-box?)
		 (layer-box-y-midpoint-in-workspace layer-box?))
	   (setf (layer-box-cursor-x-offset-in-workspace? layer-box?)
		 (-w x-in-workspace
		     (layer-box-left-edge-in-workspace layer-box?)))
	   (setf (layer-box-cursor-y-offset-in-workspace? layer-box?)
		 (-w y-in-workspace
		     (layer-box-top-edge-in-workspace layer-box?))))))
      (t
       (setf (icon-editor-translator-state translator)
	     (icon-editor-state 'waiting))))
    nil))



(defun handle-layers-pad-mouse-motion
       (icon-editor cursor-x-in-workspace cursor-y-in-workspace)
  (let* ((engine (icon-editor-engine icon-editor))
	 (layers-pad (icon-editor-layers-pad icon-editor))
	 (layer (icon-editor-engine-current-layer engine))
	 (layer-index (icon-editor-engine-current-layer-index engine))
	 (layer-box? (layer-box?-of-layer layer)))
    (when layer-box?
      (let* ((x-offset?
	       (layer-box-cursor-x-offset-in-workspace? layer-box?))
	     (y-offset?
	       (layer-box-cursor-y-offset-in-workspace? layer-box?)))
	(when (and x-offset? y-offset?)
	  (let* ((desired-new-left-edge-in-workspace
		   (-w cursor-x-in-workspace x-offset?))

		 ;; We can cache these max and min values:
		 (minimum-new-left-edge-in-workspace
		   (icon-editor-layers-pad-x-origin-in-workspace layers-pad))
		 (maximum-new-left-edge-in-workspace
		   (+w minimum-new-left-edge-in-workspace
		       (layers-pad-width-in-workspace layers-pad)))

		 (new-left-edge-in-workspace
		   (cond
		     ((>f desired-new-left-edge-in-workspace
			  maximum-new-left-edge-in-workspace)
		      maximum-new-left-edge-in-workspace)
		     ((<f desired-new-left-edge-in-workspace
			  minimum-new-left-edge-in-workspace)
		      minimum-new-left-edge-in-workspace)
		     (t desired-new-left-edge-in-workspace)))
		 (new-top-edge-in-workspace
		   (-w cursor-y-in-workspace y-offset?))
		 (new-bottom-edge-in-workspace
		   (+w new-top-edge-in-workspace (layer-box-height layer-box?)))
		 (layers-pad (icon-editor-layers-pad icon-editor))
		 (adjusted-bounding-box-border-width
		   0)				; go a bit over the limit,
						;   so as to be able to set the new
						;   position above the top or below
						;   the bottom.
		 ;(adjusted-bounding-box-border-width
		 ;  (icon-editor-layers-pad-bounding-box layers-pad))
		 (y-min-limit
		   (+w (layers-pad-top-edge-in-workspace layers-pad)
		       adjusted-bounding-box-border-width))
		 (y-max-limit
		   (-w (layers-pad-bottom-edge-in-workspace layers-pad)
		       adjusted-bounding-box-border-width)))
	    (cond
	      ((<w new-top-edge-in-workspace y-min-limit)
	       (setq new-top-edge-in-workspace y-min-limit))
	      ((>w new-bottom-edge-in-workspace y-max-limit)
	       (setq new-top-edge-in-workspace
		     (-w y-max-limit (layer-box-height layer-box?)))))
	    (move-or-place-layer-box-in-workspace
	      icon-editor layer layer-index
	      new-left-edge-in-workspace new-top-edge-in-workspace)))))
    nil))



(defun compute-new-layer-index-from-new-position (icon-editor layer-box-to-check)
  ;  (print (layer-box-layer-index layer-box-to-check))
  (let* ((engine (icon-editor-engine icon-editor))
	 (layers (icon-editor-engine-layers engine))
	 (layers-pad (icon-editor-layers-pad icon-editor))
	 (visible-top-layer-index
	   (icon-editor-layers-pad-visible-top-layer-index layers-pad))
	 (visible-bottom-layer-index
	   (icon-editor-layers-pad-visible-bottom-layer-index layers-pad))
	 (y-midpoint-in-workspace
	   (halfw (+w (layer-box-top-edge-in-workspace layer-box-to-check)
		      (layer-box-bottom-edge-in-workspace layer-box-to-check))))
	 (above-layer-box-to-check-p nil)	; to provide a hysterisis
	 (previous-layer-box? nil)
	 (last-matching-layer-box? nil))
    (declare (type fixnum visible-top-layer-index visible-bottom-layer-index
		   y-midpoint-in-workspace))
    (loop with layer-box?
	  with layer-index = 0
	  for layer in layers			; bottom up
	  do
      (when (<=f visible-bottom-layer-index layer-index visible-top-layer-index)
	(setq layer-box? (layer-box?-of-layer layer))
	(when layer-box? 
	  (when (>=w y-midpoint-in-workspace
		     (if (eq layer-box? layer-box-to-check)
			 (layer-box-original-y-midpoint-in-workspace? layer-box?)
			 (layer-box-y-midpoint-in-workspace layer-box?)))
	    (when above-layer-box-to-check-p	; hysterisis
	      (setq last-matching-layer-box? previous-layer-box?)
	      (return))
	    (setq last-matching-layer-box? layer-box?)
	    (when (not above-layer-box-to-check-p)
	      (return)))
	  (if (eq layer-box? layer-box-to-check)
	      (setq above-layer-box-to-check-p t))
	  (setq previous-layer-box? layer-box?)))
      (incff layer-index))
    (if last-matching-layer-box?
	(layer-box-layer-index last-matching-layer-box?)
	;; Else:  must be at the top
	(maxf (-f (icon-editor-engine-number-of-layers engine) 1) 0)
	)))




(defun terminate-moving-layer-box (icon-editor x-in-workspace? y-in-workspace?)
  (when (and x-in-workspace? y-in-workspace?)
    (handle-layers-pad-mouse-motion icon-editor x-in-workspace? y-in-workspace?))
  (let* ((engine (icon-editor-engine icon-editor))
	 (translator (icon-editor-translator icon-editor))
	 (layer (icon-editor-engine-current-layer engine))
	 (layer-box? (layer-box?-of-layer layer)))
    (when layer-box?
      (let* ((x-offset?
	       (layer-box-cursor-x-offset-in-workspace? layer-box?))
	     (y-offset?
	       (layer-box-cursor-y-offset-in-workspace? layer-box?)))
	(when (and x-offset? y-offset?)
	  (setf (layer-box-cursor-x-offset-in-workspace? layer-box?) nil)
	  (setf (layer-box-cursor-y-offset-in-workspace? layer-box?) nil)
	  (let* ((old-index
		   (layer-box-layer-index layer-box?))
		 (new-index
		   (compute-new-layer-index-from-new-position
		     icon-editor layer-box?)))
	    (setf (icon-editor-translator-state translator)
		  (icon-editor-state 'waiting))
	    (if (/=f old-index new-index)
		(enqueue-icon-editor-translator-event
		  icon-editor
		  (icon-editor-translator-event 'move-layer-along-z-axis)
		  old-index
		  new-index)
		(handle-redrawing-layers-in-layers-pad icon-editor)))))))
  nil)




(defun-substitution-macro handle-layers-pad-mouse-up
				    (icon-editor x-in-workspace y-in-workspace)
  (terminate-moving-layer-box icon-editor x-in-workspace y-in-workspace)
  nil)						; event handled


(defun-substitution-macro handle-layers-pad-irrelevant-event
				    (icon-editor translator-event arg-1? arg-2?)
  #+development
  (declare (ignore icon-editor translator-event arg-1? arg-2?))
  ;; (terminate-moving-layer-box icon-editor nil nil)
  t)



(defun-substitution-macro handle-redrawing-all-layer-boxes (icon-editor)
  (delete-all-layer-boxes
    (icon-editor-engine-layers (icon-editor-engine icon-editor)))
  (handle-resizing-layer-boxes-if-necessary icon-editor))






;;; The function `handle-layers-pad-visual-event' ...
;;; It returns nil if the icon editor state is still 'in-layers-pad
;;; and t otherwise.

(defun handle-layers-pad-visual-event
       (icon-editor visual-event arg-1? arg-2?)
  (let* ()
    (icon-editor-visual-event-case visual-event
      (redraw-layers-in-layers-pad
	(handle-redrawing-layers-in-layers-pad icon-editor))
      (move-layer-in-layers-pad			; args: delta-x-in-workspace, delta-y
	(handle-moving-layer-box-in-layers-pad
	  icon-editor arg-1? arg-2?))
      (delete-layer-in-layers-pad
	(handle-deleting-layer-in-layers-pad icon-editor arg-1?))
      (add-layer-in-layers-pad
	(handle-adding-layer-in-layers-pad
	  icon-editor arg-1? arg-2?))
      (change-color-of-region-in-layers-pad
	(handle-changing-color-of-region-in-layers-pad
	  icon-editor arg-1? arg-2?))
      (change-color-of-current-layer-in-layers-pad
	(handle-changing-color-of-current-layer-in-layers-pad
	  icon-editor arg-1? arg-2?))
      (change-label-of-layer-in-layers-pad
	(handle-changing-label-of-layer-in-layers-pad
	  icon-editor arg-1? arg-2?))
      (change-current-layer-in-layers-pad
	(handle-changing-current-layer-in-layers-pad
	  icon-editor arg-1? arg-2?))
      (redraw-current-layer-box
	(handle-redrawing-current-layer-box
	  icon-editor arg-1? arg-2?))
      (resize-layer-boxes-if-necessary
	(handle-resizing-layer-boxes-if-necessary icon-editor))
      (set-color-of-layer
	(handle-setting-color-of-layer icon-editor arg-1? arg-2?))
      (redraw-all-layer-boxes
	(handle-redrawing-all-layer-boxes icon-editor))
      #+development
      (t 
	(cerror "Continue."  "Shouldn't reach here.")))))




;;; The function `handle-layers-pad-translator-event' ...
;;; It returns nil if the icon editor state is still 'in-layers-pad
;;; and t otherwise.  This function should only be called when a mouse-down
;;; occurred in the layers pad.

(defun handle-layers-pad-translator-event
       (icon-editor translator-event arg-1? arg-2?)
  (let* ((translator (icon-editor-translator icon-editor)))
    (icon-editor-translator-event-case translator-event
      (mouse-motion
	(handle-layers-pad-mouse-motion icon-editor arg-1? arg-2?))
      (layers-pad-mouse-down
	(when (/=f (icon-editor-translator-state translator)
		   (icon-editor-state 'in-layers-pad))
	  (handle-layers-pad-mouse-down icon-editor arg-1? arg-2?)))
      ((non-view-pad-mouse-up view-pad-mouse-up)
       ;; End in-layers-pad state.
       (handle-layers-pad-mouse-up icon-editor arg-1? arg-2?))
      (t
	;; End in-layers-pad state.
	(handle-layers-pad-irrelevant-event 
	  icon-editor translator-event arg-1? arg-2?)))))











;;; Buttons

(defun-substitution-macro create-icon-editor-buttons ()
  (let* ((buttons nil))
    ;; WORK TO BE DONE HERE!
    (let* (translator-event
	   text-or-button-class
	   button-coordinate
	   button)
      (loop for element in icon-editor-buttons-specification-list
	    do
	(setq translator-event (first element))
	(setq text-or-button-class (second element))
	(setq button-coordinate (third element))
	(setq button
	      (create-icon-editor-button
		(first button-coordinate)
		(second button-coordinate)
		text-or-button-class))
	(setf (button-action-data? (icon-editor-button-frame button))
	      translator-event)
	(icon-editor-push button buttons)))
    buttons))

(defun-substitution-macro place-icon-editor-buttons-on-workspace
				    (buttons workspace)
  #+development (gensym-assert (and (listp buttons)
				    (frame-of-class-p workspace 
						      'icon-editor-workspace)))
  (loop for button in buttons
	do
    (add-to-workspace
      (icon-editor-button-frame button)
      workspace
      (icon-editor-button-x-in-workspace button)
      (icon-editor-button-y-in-workspace button))))




;;; Tables

(defun create-icon-editor-tables ()
  (let* ((tables nil)
	 (info-box? nil)
	 (size-table? nil)
	 (label-table? nil)
	 (x-y-position-box? nil)
	 (x-position-box? nil)
	 (y-position-box? nil))
    ;; WORK TO BE DONE HERE!
    (let* (name-of-table
	   names-of-slots
	   table-coordinate
	   use-small-fonts?
	   table)
      (loop for element in icon-editor-tables-specification-list
	    do
	(setq name-of-table (first element))
	(setq names-of-slots (second element))
	(setq table-coordinate (third element))
	(setq use-small-fonts? (fourth element))
	(setq table
	      (create-icon-editor-table
		(first table-coordinate) (second table-coordinate)
		(copy-list-using-icon-editor-conses names-of-slots) 
		use-small-fonts?))
	(case name-of-table
	  (info-box
	   (setq info-box? table))
	  (size-table
	   (setq size-table? table))
	  (label-table
	   (setq label-table? table))
	  (x-position-box
	   (setq x-position-box? table))
	  (y-position-box
	   (setq y-position-box? table))
	  (x-y-position-box
	   (setq x-y-position-box? table)))
	(icon-editor-push table tables)))
    (values tables info-box? size-table? label-table?
	    x-position-box? y-position-box? x-y-position-box?)))


(defun-substitution-macro place-icon-editor-tables-on-workspace
				    (tables workspace)
  #+development (gensym-assert (and (listp tables)
				    (frame-of-class-p workspace 
						      'icon-editor-workspace)))
  (loop for table in tables
	do
    (add-to-workspace
      (icon-editor-table-display-frame table)
      workspace
      (icon-editor-table-x-in-workspace table)
      (icon-editor-table-y-in-workspace table))))








;;; The function `create-icon-editor' should be used in place of
;;; make-icon-editor because it creates all appropriate frames and
;;; structures within the icon editor.

(defun create-icon-editor (class-definition)
  (let* ((workspace
	   (make-workspace 'icon-editor-workspace nil nil 10))
	 (icon-editor
	   (make-icon-editor
	     class-definition
	     workspace
	     (copy-frame-serial-number (current-frame-serial-number)))))

    (when new-g2-classic-ui-p
      (let ((caption-text
	      (make-caption-text-for-icon-editor-workspace class-definition)))
	(change-slot-value workspace 'title-bar-caption-text caption-text)))

    (with-localization-domain 'icon-editor
    
    ;start of SoftServe changes
    #|(setf (icon-editor-view-pad icon-editor)
	  (create-icon-editor-view-pad
	    (x-in-workspace-of-view-pad)
	    (y-in-workspace-of-view-pad)))|# 
    ;Changed by SoftServe to (exact values taken from icons1.lisp):
    ;this is temporary solution         
        (setf (icon-editor-view-pad icon-editor)
	  (create-icon-editor-view-pad
	    320 
	    275))  
     ;end of SoftServe changes                         
                                                       
    (place-icon-editor-view-pad-on-workspace (icon-editor-view-pad icon-editor)
					     workspace)
    
    (setf (icon-editor-layers-pad icon-editor)
	  (create-icon-editor-layers-pad
	    (x-in-workspace-of-layers-pad)
	    (y-in-workspace-of-layers-pad)))
    (place-icon-editor-layers-pad-on-workspace (icon-editor-layers-pad icon-editor)
					       workspace)
    
    (setf (icon-editor-buttons icon-editor) (create-icon-editor-buttons))
    (place-icon-editor-buttons-on-workspace (icon-editor-buttons icon-editor)
					    workspace)
    
    (multiple-value-bind (tables info-box size-table label-table
			  x-position-box y-position-box x-y-position-box)
	(create-icon-editor-tables)
      (setf (icon-editor-tables icon-editor) tables)
      (setf (icon-editor-info-box icon-editor) info-box)
      (setf (icon-editor-size-table icon-editor) size-table)
      (setf (icon-editor-label-table icon-editor) label-table)
      (setf (icon-editor-x-position-box icon-editor) x-position-box)
      (setf (icon-editor-y-position-box icon-editor) y-position-box)
      (setf (icon-editor-x-y-position-box icon-editor) x-y-position-box))
    (place-icon-editor-tables-on-workspace (icon-editor-tables icon-editor)
					   workspace)
    icon-editor)))


(defun make-caption-text-for-icon-editor-workspace (class-definition)
  (twith-output-to-text
    (tformat "Icon Editor for ~NF" class-definition)))








;;; `Cleanup-icon-editor' implements the before method of the
;;; clean-up-workstation-context on the icon-editor.

(defun cleanup-icon-editor (icon-editor)
  (let* ((reference-serial-number
	   (icon-editor-reference-serial-number icon-editor)))
    (reclaim-icon-editor-slot-value
      (icon-editor-region-and-name-alist icon-editor))
    (setf (icon-editor-region-and-name-alist icon-editor) nil)
    (reclaim-icon-editor-slot-value
      (icon-editor-variable-spec-list icon-editor))
    (setf (icon-editor-variable-spec-list icon-editor) nil)
    (delete-icon-editor-translator (icon-editor-translator icon-editor))

    ;; Note that this is not reclaiming all of the engine pieces including
    ;; the layers/layerboxes, the engine text, etc
    ;; I tried adding reclaimers to the def-structure for the
    ;; icon-editor-engine but the engine contains many aliases and this
    ;; would therefore be a complicated project.  For now I am reclaiming by hand,
    ;; only those conses that I have recently introduced when adding text to icons
    ;; (pbk 2/6/96)
    (delete-icon-editor-engine (icon-editor-engine icon-editor))
       ;; Delete workspace
    
    (if (frame-has-not-been-reprocessed-p
	  (icon-editor-workspace icon-editor) reference-serial-number)
	(delete-frame (icon-editor-workspace icon-editor)))
    (reclaim-frame-serial-number reference-serial-number)
    (setf (icon-editor-reference-serial-number icon-editor) nil)
    (reclaim-frame-serial-number (icon-editor-main-color-menu-serial-number icon-editor))
    (setf (icon-editor-main-color-menu-serial-number icon-editor) nil)
    (delete-icon-editor-view-pad (icon-editor-view-pad icon-editor))
    (delete-icon-editor-layers-pad (icon-editor-layers-pad icon-editor))

    ;; Delete buttons
    (let* ((buttons (icon-editor-buttons icon-editor)))
      (loop for button in buttons
	    do
	(delete-icon-editor-button button))
      (reclaim-icon-editor-list buttons))
    ;; Delete tables
    (let* ((tables (icon-editor-tables icon-editor)))
      (loop for table in tables
	    do
	(delete-icon-editor-table table))
      (reclaim-icon-editor-list tables))
    
    ;; icon-editor-info-box, icon-editor-size-table, icon-editor-label-table,
    ;; icon-editor-x-position-box, and icon-editor-y-position-box are all
    ;; accounted for in icon-editor-tables; hence they don't have to be
    ;; reclaimed.

    
    ;; Reclaiming the main text within the engine  (pbk 2/6/96).
    ;; This should be in the def-structure for icon-editor-engine
    ;; see note above and the one near icon-editor-engine def-structure
    (when (icon-editor-engine-text?  
	    (icon-editor-engine icon-editor))
      (reclaim-icon-editor-slot-value (icon-editor-engine-text?
					(icon-editor-engine icon-editor))))

    (when (icon-editor-engine-stipple?  
	    (icon-editor-engine icon-editor))
      (reclaim-icon-editor-slot-value (icon-editor-engine-stipple?
					(icon-editor-engine icon-editor))))

    ;; ??? we aren't reclaiming image slot specs  (pbk 2/6/96)

    ;; Reclaiming the text within the engine's layers (pbk 2/6/96).
    ;; This should be in the def-structure for icon-editor-engine
    ;; see note above and the one near icon-editor-engine def-structure
    (loop for layer in (icon-editor-engine-layers
			 (icon-editor-engine icon-editor))
	  as drawing-elements = (cddr layer)
	  do
      (loop for drawing-element-list in drawing-elements by 'cddr
	    ;; every element is listed twice for some reason
	    as drawing-element = (first drawing-element-list)
	    do
	(when (and drawing-element (text-drawing-element-p drawing-element))
	  (reclaim-icon-editor-slot-value drawing-element))))
    ;; Reclaim undo and redo histories here.

    (delete-icon-editor-main-color-menu icon-editor)))














;;;; Hooks For The Icon Editor Engine


;;; The View Controller

;; These functions should not eat their inputs:

;; new-icon-in-view-controller
;; delete-layer-in-view-controller
;; add-layer-in-view-controller
;; change-layer-in-view-controller
;; move-current-layer-in-view-controller (icon-ed layer-index ...)
;; set-current-layer-in-view-controller  ... do caching



(defun reset-current-layer (icon-editor-engine new-current-layer-index)
  (let* ((layers (icon-editor-engine-layers icon-editor-engine))
	 (number-of-layers
	   (icon-editor-engine-number-of-layers icon-editor-engine)))
    (cond
      ((=f number-of-layers 0)			; do nothing
       nil)
      ((<=f new-current-layer-index 0)
       (setf (icon-editor-engine-current-layer-index icon-editor-engine)
	     0)
       (setf (icon-editor-engine-current-layer icon-editor-engine)
	     (car layers)))
      ((>=f new-current-layer-index number-of-layers)
       (setf (icon-editor-engine-current-layer-index icon-editor-engine)
	     (-f number-of-layers 1))
       (setf (icon-editor-engine-current-layer icon-editor-engine)
	     (nth (icon-editor-engine-current-layer-index icon-editor-engine)
		  layers)))
      (t (setf (icon-editor-engine-current-layer-index icon-editor-engine)
	       new-current-layer-index)
	 (setf (icon-editor-engine-current-layer icon-editor-engine)
	       (nth new-current-layer-index layers))))))


(defun-substitution-macro put-layer-at-the-bottom (new-layer icon-editor-engine)
  (let* ((old-list-of-layers (icon-editor-engine-layers icon-editor-engine))
	 (new-list-of-layers (icon-editor-cons new-layer old-list-of-layers)))
    (setf (icon-editor-engine-layers icon-editor-engine) new-list-of-layers)
    (if (null old-list-of-layers)
	(setf (icon-editor-engine-layers-tail icon-editor-engine)
	      new-list-of-layers)))
  (incff (icon-editor-engine-number-of-layers icon-editor-engine)))


(defun-substitution-macro put-layer-on-top
				    (new-layer icon-editor-engine)
  (let* ((new-tail (icon-editor-cons new-layer nil))
	 (tail-of-old-list-of-layers?
	  (icon-editor-engine-layers-tail icon-editor-engine)))
    (if tail-of-old-list-of-layers?
	(setf (cdr tail-of-old-list-of-layers?) new-tail)
	(setf (icon-editor-engine-layers icon-editor-engine) new-tail))
    (setf (icon-editor-engine-layers-tail icon-editor-engine) new-tail))
  (incff (icon-editor-engine-number-of-layers icon-editor-engine)))



(defun put-layer-before-specific-layer
       (new-layer specific-layer-index icon-editor-engine)
    (cond
      ((<=f specific-layer-index 0)
       (put-layer-at-the-bottom new-layer icon-editor-engine))
      ((>=f specific-layer-index
	    (icon-editor-engine-number-of-layers icon-editor-engine))
       (put-layer-on-top new-layer icon-editor-engine))
      (t (let* ((old-list
		  (icon-editor-engine-layers icon-editor-engine))
		(splicing-point-in-old-layers
		  (nthcdr (-f specific-layer-index 1) old-list))
		(cons-to-splice-in
		  (icon-editor-cons new-layer
				    (cdr splicing-point-in-old-layers))))
	   (setf (cdr splicing-point-in-old-layers) cons-to-splice-in))
	 (incff (icon-editor-engine-number-of-layers icon-editor-engine))))
    (reset-current-layer icon-editor-engine
			 (icon-editor-engine-current-layer-index
			   icon-editor-engine)))






(defun-substitution-macro delete-layer-from-the-bottom (icon-editor-engine)
  (let* ((old-layers (icon-editor-engine-layers icon-editor-engine)))
    (prog1 (car old-layers)
	   (setf (icon-editor-engine-layers icon-editor-engine)
		 (cdr old-layers))
	   (when (null (cdr old-layers))
	     (setf (icon-editor-engine-layers-tail icon-editor-engine)
		   nil))
	   (reclaim-icon-editor-cons old-layers)
	   (decff (icon-editor-engine-number-of-layers icon-editor-engine)))))


;;; The function `delete-specific-layer' removes the specified layer
;;; form the icon editor engine (but does not reclaim it), reclaims the 
;;; icon-editor cons that holds the layer in the list, and decrements
;;; the count of layers.  The layer is then returned.

(defun delete-specific-layer (specific-layer-index icon-editor-engine)
  #+development
  "Returns a <layer> which must be reclaimed."
  #+development (gensym-assert (<=f 0
				    specific-layer-index
				    (-f (icon-editor-engine-number-of-layers
					  icon-editor-engine) 1)))
  (when (<=f 0
	     specific-layer-index
	     (-f (icon-editor-engine-number-of-layers icon-editor-engine) 1))
    (prog1
      (cond
	((<=f specific-layer-index 0)
	 (delete-layer-from-the-bottom icon-editor-engine))
	(t 
	 (let* ((old-layers (icon-editor-engine-layers icon-editor-engine))
		(cons-preceding-cons-to-splice-out
		  (nthcdr (-f specific-layer-index 1) old-layers))
		(cons-to-splice-out (cdr cons-preceding-cons-to-splice-out)))
	   (prog1 (car cons-to-splice-out)
		  (if (null (cdr cons-to-splice-out))	; if splicing out tail
		      (setf (icon-editor-engine-layers-tail icon-editor-engine)
			    cons-preceding-cons-to-splice-out))
		  (setf (cdr cons-preceding-cons-to-splice-out)
			(cdr cons-to-splice-out))
		  (reclaim-icon-editor-cons cons-to-splice-out)
		  (decff (icon-editor-engine-number-of-layers
			   icon-editor-engine))))))
      (reset-current-layer
	icon-editor-engine
	(icon-editor-engine-current-layer-index icon-editor-engine)))))





;;; The function `move-icon-layer' should handle the moving of a layer from
;;; one position to another.  This should include the graphics updates as
;;; well.

(defun move-icon-layer (get-from-this-layer-index
			put-before-this-layer-index
			icon-editor-engine)
  (declare (type fixnum get-from-this-layer-index
		 put-before-this-layer-index))
  (when (not (=f get-from-this-layer-index	; when no movement
		 (-f put-before-this-layer-index 1)))

    ;; Clear drawings on view pad

;    (notify-user "Pretend to move icon layer ~a to before ~a."
;		 get-from-this-layer-index
;		 put-before-this-layer-index)

    (let* ((layer-to-move
	     (delete-specific-layer get-from-this-layer-index
				    icon-editor-engine)))
      (put-layer-before-specific-layer
	layer-to-move (-f put-before-this-layer-index 1) icon-editor-engine)
      )

    ;; remember to redraw layers and view pad.

    ))




;;; The function `new-icon-layer' makes the new layer into the view and layers
;;; pad.  List-of-line-drawing-elements? has to be an icon-editor list, and
;;; is consumed by this function.

(defun new-icon-layer (color-label
		       list-of-line-drawing-elements?
		       put-before-this-layer-index
		       icon-editor-engine)
  #+development (gensym-assert (typep put-before-this-layer-index 'fixnum))
  (let* ((new-layer
	   (make-layer
	     color-label			; region, color, or metacolor
	     nil				; layer-box
	     list-of-line-drawing-elements?
	     (last list-of-line-drawing-elements?)	; tail
	     )))
    (put-layer-before-specific-layer
      new-layer
      put-before-this-layer-index
      icon-editor-engine)))




;;; The function `merge-icon-layers' takes two icon layers and merges them
;;; into one, with the color label of the first.

(defun-substitution-macro merge-icon-layers
				    (layer-index-1 layer-index-2 icon-editor)
  (let* ((icon-editor-engine (icon-editor-engine icon-editor))
	 (layers (icon-editor-engine-layers icon-editor-engine))
	 (layer-1 (if (=f layer-index-1
			  (icon-editor-engine-current-layer-index
			    icon-editor-engine))
		      (icon-editor-engine-current-layer icon-editor-engine)
		      (nth layer-index-1 layers)))
	 (drawing-elements-1 (drawing-elements-of-layer layer-1))
	 (layer-2 (delete-specific-layer layer-index-2 icon-editor-engine))
	 (label-2 (label-of-layer layer-2)))
    (loop for element in (drawing-elements-of-layer layer-2)
	  do
      (icon-editor-push element drawing-elements-1))
    (setf (drawing-elements-of-layer layer-1) drawing-elements-1)
    (setf (drawing-elements-tail-of-layer layer-1)
	  ;; Note: if drawing-elements-1 and drawing-elements-1-tail are both NIL before
	  ;; the PUSH in above LOOP, then the new tail must be re-calculated.
	  (last drawing-elements-1))
    (reclaim-icon-editor-slot-value (layer-box-of-layer layer-1))	;ensure redraw
    (setf (layer-box-of-layer layer-1) nil)
    (reclaim-icon-editor-slot-value (layer-box-of-layer layer-2))
    (reclaim-icon-editor-list layer-2)
    (reset-current-layer icon-editor-engine
			 (maxf (-f layer-index-1 1) 0))
    (set-color-of-region-in-icon-editor icon-editor label-2 nil)
    #+development
    layer-1))




;;; The function `explode-icon-layer' takes the specified layer, blows it
;;; up into layers, each of which holds one of the original layer's drawing
;;; elements.  The exception to this is when a layer contains points.  If the
;;; layer only contains points each point becomes a separate layer.  But (here
;;; is the exception), when the layer contains points and any other element(s) the
;;; points are grouped together in a new layer (without the other drawing
;;; elements).

(defun-substitution-macro explode-icon-layer (layer-index icon-editor)
  (let* ((engine (icon-editor-engine icon-editor))
	 (layer (delete-specific-layer layer-index engine))
	 (label (label-of-layer layer))
	 (elements (drawing-elements-of-layer layer))
	 (new-current-layer? nil)
	 (group-points-into-one-layer? nil))
    ;; group points when then are other drawing elements in the original layer,
    ;; otherwise each point has its own layer.
    (loop for element in elements
	  while (eq (first element) 'point)
	  finally
	    (unless (eq (first element) 'point)
	      (setq group-points-into-one-layer? t)))
	  
    (loop with new-list-of-elements
	  for element in elements
	  when (and (eq (first element) 'point)
		    group-points-into-one-layer?)
	    collect element into list-of-point-elements using icon-editor-cons
	  do
      (unless (and (eq (first element) 'point)
		   group-points-into-one-layer?)
	(setq new-list-of-elements (icon-editor-list element))
	(setq new-current-layer?
	      (make-layer label nil 
			  new-list-of-elements new-list-of-elements))
	
	(put-layer-before-specific-layer
	  new-current-layer? layer-index engine)
	(incff layer-index))
      finally
	(when list-of-point-elements
	    (setq new-current-layer?
		  (make-layer label nil 
			list-of-point-elements list-of-point-elements))
	    (put-layer-before-specific-layer
	      new-current-layer? layer-index engine)
	    (incff layer-index)))

    (reclaim-icon-editor-list elements)
    (setf (icon-editor-engine-current-layer engine)
	  new-current-layer?)

    ;; new current layer index
						       ; last of exploded layer.
						       ; ok?? cpm, 6oct89.   
    (setf (icon-editor-engine-current-layer-index engine)
	  (-f layer-index 1))			       ; ??

    (setf (drawing-elements-of-layer layer) nil)
    (setf (drawing-elements-tail-of-layer layer) nil)
    (reclaim-icon-editor-slot-value layer)
    #+development
    new-current-layer?))




;;; The function `handle-icon-editor-visual-event' is the hook into the visual
;;; outputing parts (view pad, control pad, and layers pad) of the icon editor.
;;; This function reclaims all reclaimable arguments passed to it.  This
;;; function should only be called by the function or macro which permits the
;;; handling of the updates of the events (in this case, it is
;;; enqueue-icon-editor-visual-event).

(defun handle-icon-editor-visual-event (icon-editor visual-event
						    arg-1? arg-2?)

  (declare (type fixnum visual-event))
  #+development
  (check-memory-for-development 'handle-icon-editor-visual-event_0)
  (cond ((icon-editor-killed-p icon-editor)
	 (reclaim-icon-editor-slot-value arg-1?)
	 (reclaim-icon-editor-slot-value  arg-2?)
	 ;; WORK TO BE DONE HERE!  - shouldn't use destroy-icon-editor
	 ;; should let the icon editor engine handle the exit
	 ;; by calling enqueue-icon-editor-engine-event.
	 ;; This is also a forward reference to a macro.
	 (cleanup-icon-editor icon-editor)
	 (reclaim-icon-editor icon-editor))
	(t
	 (icon-editor-visual-event-case visual-event
	   (change-x-y-position-box-values	; args: x-in-view-pad, nil
	     (let* ((x-y-position-box (icon-editor-x-y-position-box icon-editor)))
	       #+development (gensym-assert (icon-editor-table-p x-y-position-box))
	       (let* ((frame (icon-editor-table-info-frame x-y-position-box))
		      (old-x-value
			(icon-editor-table-info-frame-x-position frame))
		      (old-y-value
			(icon-editor-table-info-frame-y-position frame)))
		 #+development
		 (gensym-assert (and (framep frame)
				     (frame-of-class-p frame 'icon-editor-table-info-frame)))
		 (when (not (and (=f old-x-value arg-1?) (=f old-y-value arg-2?)))
		   (setf (icon-editor-table-info-frame-x-position frame) arg-1?)
		   (setf (icon-editor-table-info-frame-y-position frame) arg-2?)
		   (change-slot-value
		     frame
		     (car (icon-editor-table-display-slot-names x-y-position-box))
		     arg-1?)))))
	     
	   (put-point-marker-in-view-pad		; args: x-in-view-pad, y-in-view-pad
	     (put-cross-marker-in-view-pad
	       arg-1? arg-2? (icon-editor-view-pad icon-editor)
	       (icon-editor-engine-main-color (icon-editor-engine icon-editor))
	       t))
	   (put-cross-marker-in-view-pad		; args: x-in-view-pad, y-in-view-pad
	     (put-cross-marker-in-view-pad
	       arg-1? arg-2? (icon-editor-view-pad icon-editor)
	       (icon-editor-engine-main-color (icon-editor-engine icon-editor))
	       nil))
	   ((put-line-marker-in-view-pad		; args: (x0 . y0), (x1 . y1)
	      put-rectangle-marker-in-view-pad)
	    ;;#+development
	    ;;(check-memory-for-development 'handle-icon-editor-visual-event_20)
	    (let* ((view-pad (icon-editor-view-pad icon-editor))
		   (engine (icon-editor-engine icon-editor))
		   (x-origin-in-workspace
		     (icon-editor-view-pad-x-origin-in-workspace view-pad))
		   (y-origin-in-workspace
		     (icon-editor-view-pad-y-origin-in-workspace view-pad)))
	      (put-line-marker-in-view-pad
		(car arg-1?) (cdr arg-1?)
		(car arg-2?) (cdr arg-2?)
		view-pad
		(icon-editor-engine-main-color engine)
		x-origin-in-workspace
		y-origin-in-workspace
		(+w x-origin-in-workspace
		    (delta-x-in-workspace-from-view-pad 
		      (icon-editor-engine-icon-width engine) view-pad))
		(+w y-origin-in-workspace
		    (delta-y-in-workspace-from-view-pad 
		      (icon-editor-engine-icon-height engine) view-pad))
		(=f visual-event 
		    (icon-editor-visual-event
		      'put-rectangle-marker-in-view-pad)))
	      (reclaim-icon-editor-cons arg-1?)
	      (reclaim-icon-editor-cons arg-2?)))

	   (put-circle-marker-in-view-pad	; args: (x0 . y0), radius-in-view-pad
	      (let* ((view-pad (icon-editor-view-pad icon-editor))
		     (engine (icon-editor-engine icon-editor))
		     (x-origin-in-workspace
		       (icon-editor-view-pad-x-origin-in-workspace view-pad))
		     (y-origin-in-workspace
		       (icon-editor-view-pad-y-origin-in-workspace view-pad)))
		(put-circle-marker-in-view-pad
		  (car arg-1?) (cdr arg-1?) arg-2?
		  view-pad
		  (icon-editor-engine-main-color (icon-editor-engine icon-editor))
		  x-origin-in-workspace
		  y-origin-in-workspace
		  (+w x-origin-in-workspace
		      (delta-x-in-workspace-from-view-pad 
			(icon-editor-engine-icon-width engine) view-pad))
		  (+w y-origin-in-workspace
		      (delta-y-in-workspace-from-view-pad 
			(icon-editor-engine-icon-height engine) view-pad)))))
	    (put-arc-marker-in-view-pad	; args: ((x0 . y0) (x1 . y1)), (x2 . y2)
	      (let* ((view-pad (icon-editor-view-pad icon-editor))
		     (engine (icon-editor-engine icon-editor))
		     (x-origin-in-workspace
		       (icon-editor-view-pad-x-origin-in-workspace view-pad))
		     (y-origin-in-workspace
		       (icon-editor-view-pad-y-origin-in-workspace view-pad)))
		(put-arc-marker-in-view-pad
		  (car (first arg-1?)) (cdr (first arg-1?))
		  (car (second arg-1?)) (cdr (second arg-1?))
		  (car arg-2?) (cdr arg-2?)
		  view-pad
		  (icon-editor-engine-main-color (icon-editor-engine icon-editor))
		  x-origin-in-workspace
		  y-origin-in-workspace
		  (+w x-origin-in-workspace
		      (delta-x-in-workspace-from-view-pad 
			(icon-editor-engine-icon-width engine) view-pad))
		  (+w y-origin-in-workspace
		      (delta-y-in-workspace-from-view-pad 
			(icon-editor-engine-icon-height engine) view-pad)))))
	    (pop-marker-from-view-pad		; no arguments.
	      (pop-marker-from-view-pad (icon-editor-view-pad icon-editor)))
	    (clear-markers-from-view-pad
	      (let* ((view-pad (icon-editor-view-pad icon-editor)))
		(delete-view-pad-marker-stack
		  (icon-editor-view-pad-marker-stack view-pad))
		(setf (icon-editor-view-pad-marker-stack view-pad) nil)))

	    ;; WORK TO BE DONE HERE!
	   (show-grid
	     ;; WORK TO BE DONE HERE!
	     )
	   (inform-user
	     (let* ((info-box (icon-editor-info-box icon-editor)))
	       ;;(if (text-string-p arg-1?) (cerror "continue" ">>>>>>~a" arg-1?))
	       (change-slot-value
		 (icon-editor-table-info-frame info-box)
		 (car (icon-editor-table-display-slot-names info-box))
		 ;; assume only one list displayed.
		 arg-1?)))
	   ((change-width-in-table		; args: new-value, slot-name
	      change-height-in-table
	      change-global-stipple)
	    (let* ((slot-name
		     (icon-editor-visual-event-case visual-event
		       (change-width-in-table
			 'icon-editor-table-info-frame-icon-width)
		       (change-height-in-table
			 'icon-editor-table-info-frame-icon-height)
		       (change-global-stipple
			 'icon-editor-table-info-frame-global-stipple))))
	      (change-slot-value
		(icon-editor-table-info-frame
		  (icon-editor-size-table icon-editor))
		slot-name
		arg-1?)))
	    ((change-main-region
	       change-main-color
	       change-main-image
	       change-text
	       change-stipple)
	       
	     (let* ((slot-name
		      (icon-editor-visual-event-case visual-event
			(change-main-region
			  'icon-editor-table-info-frame-main-region)
			(change-main-color
			  'icon-editor-table-info-frame-main-color)
			(change-main-image
			  'icon-editor-table-info-frame-main-image)
			(change-text 
			  'icon-editor-table-info-frame-text)
			(change-stipple 
			  'icon-editor-table-info-frame-stipple)))
		    
		    ;; text-drawing-elements contain strings and need a copy function
		    ;; that will copy the strings. (pbk 2/6/96)
		    
		    (new-value (cond ((consp arg-1?)
				      (if (memq
					    slot-name
					    '(icon-editor-table-info-frame-text
					      icon-editor-table-info-frame-stipple))
					  (copy-drawing-element-with-slot-value-conses
					    arg-1? nil nil nil)
					  (copy-tree-using-slot-value-conses arg-1?)))
				     ((text-string-p arg-1?)	    ; Probably does not happen.
				      (copy-text-string arg-1?))
				     (t
				      arg-1?))))

	       (change-slot-value
		 (icon-editor-table-info-frame
		   (icon-editor-label-table icon-editor))
		 slot-name
		 new-value)))

	    (change-view-pad-bounding-box-width	; args: workspace-width, nil
	      (let* ((bounding-box
		       (icon-editor-view-pad-bounding-box
			 (icon-editor-view-pad icon-editor))))
		(update-border-of-bounding-box
		  bounding-box
		  nil nil
		  (+w (left-edge-of-block bounding-box)
		      (adjusted-bounding-box-border-width bounding-box)
		      (adjusted-delta-x-for-icon-delta-x
			arg-1?)
		      (amount-to-adjust-bounding-box-border-width))
		  nil)))
	    (change-view-pad-bounding-box-height	; args: workspace-height, nil
	      (let* ((bounding-box
		       (icon-editor-view-pad-bounding-box
			 (icon-editor-view-pad icon-editor))))
		(update-border-of-bounding-box
		  bounding-box
		  nil nil
		  nil
		  (+w (top-edge-of-block bounding-box)
		      (adjusted-bounding-box-border-width bounding-box)
		      (adjusted-delta-y-for-icon-delta-y
			arg-1?)
		      (amount-to-adjust-bounding-box-border-width)))))
	    (delete-icon-editor-workspace
	      (let* ((workspace (icon-editor-workspace icon-editor))
		     (reference-serial-number
		       (icon-editor-reference-serial-number icon-editor)))
		(if (frame-has-not-been-reprocessed-p 
		      workspace reference-serial-number)
		    (delete-frame workspace))))

	    ((redraw-layers-in-layers-pad
	       move-layer-in-layers-pad
	       delete-layer-in-layers-pad
	       add-layer-in-layers-pad
	       change-color-of-region-in-layers-pad
	       change-color-of-current-layer-in-layers-pad
	       change-label-of-layer-in-layers-pad
	       change-current-layer-in-layers-pad
	       redraw-current-layer-box
	       resize-layer-boxes-if-necessary
	       set-color-of-layer
	       redraw-all-layer-boxes)
	     (handle-layers-pad-visual-event
	       icon-editor visual-event arg-1? arg-2?))

	    (delete-layer-in-view-pad
	      )

	    ((redraw-view-pad-icon
	       rescale-view-pad-icon
	       move-layer-in-view-pad
	       add-layer-in-view-pad
	       change-color-of-region-in-view-pad)	; perhaps can 
	     (let* ((engine (icon-editor-engine icon-editor))
		    (view-pad (icon-editor-view-pad icon-editor))
		    (icon-width (icon-editor-engine-icon-width engine))
							    ;(icon-editor-engine-width-extent engine)
		    (icon-height (icon-editor-engine-icon-height engine))
							    ;(icon-editor-engine-height-extent engine)
		    (layers (icon-editor-engine-layers engine))
		    (alist (icon-editor-region-and-name-alist icon-editor))
		    (x-scale (icon-editor-view-pad-x-scale view-pad))
		    (y-scale (icon-editor-view-pad-y-scale view-pad))
		    (scaled-width
		      (delta-x-in-workspace-from-target icon-width x-scale))
		    (scaled-height
		      (delta-y-in-workspace-from-target icon-height y-scale))
		    (old-iconic-entity?
		      (icon-editor-view-pad-iconic-entity view-pad))
		    (old-iconic-entity-serial-number
		      (icon-editor-view-pad-iconic-entity-serial-number view-pad))
		    (variable-spec-list ; pbk
		      (icon-editor-variable-spec-list icon-editor))
		    (background-layer
		      (icon-editor-icon-background-image icon-editor))
		    (stipple-spec
		      (icon-editor-stipple-spec icon-editor)))
	       (setf (icon-editor-view-pad-iconic-entity view-pad)
		     (make-entity-with-specific-icon-description
		       'iconic-entity
		       (convert-list-of-layers-to-line-drawing-description
			 layers alist variable-spec-list
			 background-layer
			 scaled-width scaled-height
			 x-scale y-scale t t stipple-spec)
		       scaled-width scaled-height
		       nil
		       (if (consp background-layer)
			   (slot-value-list
			     (copy-for-slot-value background-layer)
			     (slot-value-list 'editor-scaling x-scale y-scale))
			  (copy-for-slot-value background-layer))) )
	       (frame-serial-number-setf (icon-editor-view-pad-iconic-entity-serial-number view-pad)
		     (current-frame-serial-number))
	       (add-to-workspace
		 (icon-editor-view-pad-iconic-entity view-pad)
		 (icon-editor-workspace icon-editor)
		 (icon-editor-view-pad-x-origin-in-workspace view-pad)
		 (icon-editor-view-pad-y-origin-in-workspace view-pad)
		 t)
	       (when (and (framep old-iconic-entity?)
			  (frame-has-not-been-reprocessed-p old-iconic-entity?
							    old-iconic-entity-serial-number))
		 (delete-frame old-iconic-entity?))))

	  #+development
	  (t
	    (cerror "Continue, ignoring error."
		    "Illegal visual event command in handle-icon-editor-visual-event")))))
  #+development
  (check-memory-for-development 'handle-icon-editor-visual-event_99))



;;; The macro `enqueue-icon-editor-visual-event' ...  At present it just calls
;;; handle-icon-editor-visual-event.  This abstraction could, in the future be
;;; for makine the icon editor continuable.

(defmacro enqueue-icon-editor-visual-event (icon-editor visual-event
					    arg-1? arg-2?)
  `(handle-icon-editor-visual-event ,icon-editor ,visual-event ,arg-1? ,arg-2?))




;; We are disabling inform-user-of-current-regions because it might overflow the
;; info box.  -pto 21feb90

(defun inform-user-of-current-regions (icon-editor)
  #-debugging
  (declare (ignore icon-editor))
  #+debugging
  (let* ((alist
	   (icon-editor-region-and-name-alist icon-editor))
	 (info-string
	   (if alist
	       (twith-output-to-text-string
		 (if (cdr alist)		; length > 1
		     (twrite-string "Labels:  ")
		     (twrite-string "Label:  "))
		 (tformat "~(~a~)" (car (first alist)))
		 (loop with index = 1		; one already printed
		       for region-and-color-pair in (cdr alist)
		       do
		   (tformat ", ~(~a~)" (car region-and-color-pair))
		   (incff index)
		   (when (>=f index 6)
		     (twrite-string " ...")
		     (return)))
		 (twrite-char #.%\.))
	       (copy-constant-wide-string #w"No active labels."))))
;    (print info-string)
;    (print (icon-editor-engine-current-layer (icon-editor-engine icon-editor)))
    (enqueue-icon-editor-visual-event
      icon-editor
      (icon-editor-visual-event 'inform-user)
      info-string nil))
  )


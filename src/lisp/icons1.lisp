;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module ICONS1 -- The Icon Editor: Introduction and Data Structures

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Ong, Peng Tsin 1989 - 1992
;;; Mark H. David 1989 - 2001
;;; Fred M. White 1994 - 1995
;;; Paul B. Konigsberg 1996 - 2000



;;;; Overview of the icon editor



;; Module ICONS1 -- Enumerated event types
;; Module ICONS2 -- The Icon Editor Display and Initialization Code
;; Module ICONS3 -- The Events Translator for the Icon Editor
;; Module ICONS4 -- The Icon Editor Engine
;; Module ICONS5 -- Icon Editor Initialization and Exit Code



;;;; Forward References

(declare-forward-references
  (cleanup-icon-editor function))


;;;; States



;;; The following mutually exclusively event states in the icon editor:
;;;
;;;   waiting
;;;   undoing
;;;   drawing-point
;;;   drawing-points
;;;   drawing-line
;;;   drawing-lines
;;;   drawing-arc
;;;   drawing-outlined-rectangle
;;;   drawing-outlined-polygon
;;;   drawing-outlined-circle
;;;   drawing-filled-rectangle
;;;   drawing-filled-polygon
;;;   drawing-filled-circle
;;;   drawing-outlined-filled-rectangle
;;;   drawing-outlined-filled-polygon
;;;   drawing-outlined-filled-circle
;;;   moving-layer-in-xy-plane
;;;   moving-layer-along-z-axis
;;;
;;; Mouse States:
;;;   dragging-in-view-pad
;;;   dragging-in-layers-pad





;;;; Layers


;;; A `layer' is defined to be an ordered list of line drawing descriptions
;;; with a common label.  For example:
;;;
;;;   wheel:
;;;     filled circle (10 10) (...) (...),
;;;     filled rectangle (....) (...);
;;;

;;; A `layer-index' is a number which represents the layer.  Layer index 0
;;; refers to the bottom-most layer (the one which appears at the top of an
;;; icon line drawing description).








;;;; Icon Editor Enumerated Event Types




;;; Visual Icon Editor Visual Events are events sent from the icon editor event
;;; translator or engine to the icon editor display.

;;; The Icon Editor State is an enumerated type which describes the state of the
;;; icon editor as maintained by the translator.

(def-enumerated-type icon-editor-state
  waiting
  undoing
  redoing
  drawing-point
  drawing-points
  drawing-line
  drawing-lines
  drawing-arc
  drawing-outlined-rectangle
  drawing-outlined-polygon
  drawing-outlined-circle
  drawing-filled-rectangle
  drawing-filled-polygon
  drawing-filled-circle
  drawing-outlined-filled-rectangle
  drawing-outlined-filled-polygon
  drawing-outlined-filled-circle
  moving-layer-in-xy-plane
  in-layers-pad					; moving-layer-along-z-axis
  )


;;; The macro `icon-editor-drawing-state-p' checks to see if the icon
;;; editor state it is given is a "drawing" state.  This macro assumes the
;;; ordering in the declaration of the enumerated type.

(defmacro icon-editor-drawing-state-p (icon-editor-state)
  `(<=f (icon-editor-state 'drawing-points)
	,icon-editor-state
	(icon-editor-state 'drawing-outlined-filled-circle)))





;;; The Icon Editor Visual Event is an enumerated type which represent
;;; the different types of 

(def-enumerated-type icon-editor-visual-event
  delete-icon-editor-workspace
  show-grid
  hide-grid
  inform-user
  change-width-in-table
  change-height-in-table
  change-main-region
  change-main-color
  change-x-position-box-value
  change-y-position-box-value
  change-x-y-position-box-values		; both x and y
  change-view-pad-bounding-box-width
  change-view-pad-bounding-box-height
  put-point-marker-in-view-pad
  put-cross-marker-in-view-pad
  put-line-marker-in-view-pad
  put-rectangle-marker-in-view-pad
  put-circle-marker-in-view-pad
  put-arc-marker-in-view-pad
  pop-marker-from-view-pad
  clear-markers-from-view-pad

  redraw-view-pad-icon
  rescale-view-pad-icon
  move-layer-in-view-pad
  delete-layer-in-view-pad
  add-layer-in-view-pad
  change-color-of-region-in-view-pad

  redraw-layers-in-layers-pad
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
  redraw-all-layer-boxes
  scroll-up-in-layers-pad
  scroll-down-in-layers-pad

  :skip
  :skip
  :skip
  :skip
  :skip
  :skip
  :skip
  :skip
  change-main-image
  change-text ; (pbk 2/6/96)
  change-stipple
  change-global-stipple
  )



;;; The Icon Editor Translator Events are events sent by the icon editor
;;; display (its widget set) to the icon editor event translator.

(def-enumerated-type icon-editor-translator-event
  mouse-motion
  view-pad-mouse-down
  view-pad-mouse-up
  layers-pad-mouse-down
  non-view-pad-mouse-up

  cancel-editing
  end-editing
  update-class-definition

  new-layer
  delete-current-layer
  group
  ungroup-current-layer

  change-current-layer-to-layer-above
  change-current-layer-to-layer-below
  change-current-layer

  scroll-up-in-layers-pad
  scroll-down-in-layers-pad

  set-main-region
  set-main-color
  redraw

  change-icon-size-from-engine
  change-icon-width-from-table
  change-icon-height-from-table
  change-icon-width-from-bounding-box
  change-icon-height-from-bounding-box
  end-changing-icon-size-from-bounding-box

  view-pad-scale-1-to-2
  view-pad-scale-1-to-1
  view-pad-scale-2-to-1
  view-pad-scale-3-to-1

  done-drawing-element
  delete-most-recent-drawing-element
  draw-point					;32
  draw-points
  draw-line
  draw-lines
  draw-arc
  draw-outlined-rectangle
  draw-outlined-polygon
  draw-outlined-circle
  draw-filled-rectangle
  draw-filled-polygon
  draw-filled-circle
  draw-outlined-filled-rectangle
  draw-outlined-filled-polygon
  draw-outlined-filled-circle

  outside-event

  shrink-wrap
  set-outline-region
  set-outline-color
  show-grid
  hide-grid
  undo
  redo
  select-current-layer
  move-layer-along-z-axis
  move-layer-in-xy-plane
  clone-current-layer
  fill-current-layer
  outline-current-layer
  :skip
  non-pad-mouse-down
  :skip
  :skip

  edit-name-of-image
  set-main-image
  set-text ; (pbk 2/6/96)
  set-stipple
  set-global-stipple
  )




;;; The Icon Editor Engine Events are enumerated types that are sent from
;;; the translator to the engine to describe changes to the icon description
;;; due to state changes within the translator.

(def-enumerated-type icon-editor-engine-event
  :skip
  :skip
  :skip
  :skip
  :skip

  cancel-editing
  end-editing
  update-class-definition

  new-layer
  delete-current-layer
  group
  ungroup-current-layer

  change-current-layer-to-layer-above
  change-current-layer-to-layer-below
  change-current-layer

  :skip
  :skip

  set-main-region
  set-main-color
  :skip

  change-icon-size
  update-main-label
  end-changing-icon-size
  change-icon-width
  change-icon-height

  change-view-pad-scale
  :skip
  :skip
  :skip

  :skip
  :skip
  delete-most-recent-drawing-element
  draw-point					;32
  draw-points
  draw-line
  draw-lines
  draw-arc
  draw-outlined-rectangle
  draw-outlined-polygon
  draw-outlined-circle
  draw-filled-rectangle
  draw-filled-polygon
  draw-filled-circle
  draw-outlined-filled-rectangle
  draw-outlined-filled-polygon
  draw-outlined-filled-circle


  set-outline-color
  set-outline-region
  show-grid
  hide-grid
  undo
  redo
  shrink-wrap

  :skip
  :skip
  move-layer-along-z-axis
  move-layer-in-xy-plane
  clone-current-layer
  fill-current-layer
  outline-current-layer
  :skip
  :skip
  :skip
  :skip

  set-main-image
  set-text ; (pbk 2/6/96)
  set-stipple
  set-global-stipple
  )


;;; The macro `draw-engine-event-p' takes an engine event and tests to see if
;;; it is a "draw" event.  This test works because of the ordering of the
;;; "draw" events in the def-enumerated-type of the icon editor engine event.

(defmacro draw-engine-event-p (engine-event)
  `(<=f (icon-editor-engine-event 'draw-point)
	,engine-event
	(icon-editor-engine-event 'draw-outlined-filled-circle)))


; (icon-editor-engine-event 'change-icon-size)
; (icon-editor-engine-event 'draw-points)









;;; Defconser for the icon editor (icon-editor)

(defconser icon-editor)


;;; `copy-tree-including-leaves-using-icon-editor-conses'  (pbk 2/6/96)
;;;  Used to copy text-drawing-elements which contain strings.

(def-copy-tree-including-leaves-using-x-conses icon-editor)


;;; The function `reverse-using-icon-editor-conses' returns a reversed list of
;;; the list is it given.  The new list has icon editor conses in its spine.

(defun reverse-using-icon-editor-conses (list)
  (when list
    (loop with reversed-list = (icon-editor-cons-macro (car list) nil)
	  for element in (cdr list)
	  do
      (setq reversed-list (icon-editor-cons-macro
			    element reversed-list))
	  finally
	    (return reversed-list))))







;;; Default Parameters for the Icon Editor

(eval-when (:compile-toplevel :load-toplevel :execute)

;;; The constants/macros `maximum-icon-width-in-icon-editor' and
;;; `maximum-icon-width-in-icon-editor' define the maximum icon width
;;; and height of icons which are produced in the icon editor.

(defmacro-for-constant maximum-icon-width-in-icon-editor 500)
(defmacro-for-constant maximum-icon-height-in-icon-editor 500)


;;; The constants/macros `icon-editor-default-color' and
;;; `icon-editor-default-region' define the default color and region
;;; of the icon being edited if there was no previous icon.

(defmacro-for-constant icon-editor-default-color 'foreground)
;(icon-editor-default-color)
(defmacro-for-constant icon-editor-default-region nil)
;(icon-editor-default-region)


;;; The constants/macros `default-width-of-icon' and `default-height-of-icon'
;;; define the default width and height of the icon being edited if there
;;; was no previous icon.

(defmacro-for-constant default-width-of-icon 100)
(defmacro-for-constant default-height-of-icon 100)
;(default-height-of-icon)


;;; The constants/macros `default-layers-pad-width',
;;; `default-layers-pad-height', `default-maximum-layers-pad-height',
;;; `default-maximum-layer-box-width', `default-maximum-layer-box-height',
;;; `default-layer-box-border-width',
;;; `initial-width-of-bounding-box-in-view-pad', and
;;; `initial-height-of-bounding-box-in-view-pad' are parameters for the view
;;; and layer pads.

(defmacro-for-constant default-layers-pad-width 160)
(defmacro-for-constant default-layers-pad-height 160)
(defmacro-for-constant default-maximum-layers-pad-height 300)

(defmacro-for-constant default-maximum-layer-box-width 148)
(defmacro-for-constant default-maximum-layer-box-height 148)
(defmacro-for-constant default-layer-box-border-width 5)


; the following values will be overwritten by default width and heights
; of icons:
(defmacro-for-constant initial-width-of-bounding-box-in-view-pad 110)
(defmacro-for-constant initial-height-of-bounding-box-in-view-pad 110)




;;; The constant and macro `icon-editor-normalized-scale-factor' is the denominator of
;;; the scaling multiple for the view pad.  For example, if the user wants to
;;; view the icon at half scale (1/2), and the icon-editor-normalized-scale-factor is 1000
;;; than the scale is specified in the icon editor as 500.  Using this
;;; technique of scaling, we can avoid having to deal with floats while scaling.

(defmacro-for-constant icon-editor-normalized-scale-factor
    (normalized-scale))

;; You're not allowed to change this.


;; View Pad

(defmacro-for-constant x-in-workspace-of-view-pad 320) ; was 280 (pbk 2/6/96)
(defmacro-for-constant y-in-workspace-of-view-pad 275) ; was 180  (pbk 2/6/96)


;; Layers Pad

(defmacro-for-constant x-in-workspace-of-layers-pad 100)
(defmacro-for-constant y-in-workspace-of-layers-pad 150)    ;  Was 110 (pbk 2/6/96)

)



;; Spacing macros

(eval-when (:compile-toplevel :load-toplevel :execute)

;;; The constant/macro `amount-to-adjust-bounding-box-border-width' governments
;;; the spacing between the inner edges of the bounding box of the view pad
;;; to the outer edges of the icon within the bounding box.

(defmacro-for-constant amount-to-adjust-bounding-box-border-width 1)

)


(defmacro-for-constant trying-to-reclaim-text-in-icons? nil)

;;; The macro `adjusted-bounding-box-border-width' returns the width of the
;;; border of the bounding box of the view pad, adjusted for the spacing
;;; specified in amount-to-adjust-bounding-box-border-width.

(defmacro adjusted-bounding-box-border-width (bounding-box)
  `(+w (bounding-box-border-width ,bounding-box)
       (amount-to-adjust-bounding-box-border-width)))












;;; The def-structure `layer-box' is for the layers pad.  Each layer in the
;;; icon has a corresponding layer box which is used to display the layer in
;;; the layer pad.

(def-structure (layer-box
		 (:constructor 
		   make-layer-box
		   (layer-box-border-icon
		     layer-box-text-for-label
		     layer-box-layer-icon
		     layer-box-reference-serial-number)))
  layer-box-border-icon			; width and height contained here
  layer-box-text-for-label
  layer-box-layer-icon
  (layer-box-reference-serial-number nil :reclaimer reclaim-frame-serial-number)
  (layer-box-x0-in-layers-pad 0)
  (layer-box-y0-in-layers-pad 0)
  layer-box-x-offset-of-layer-icon-from-x0
  layer-box-y-offset-of-layer-icon-from-y0
  layer-box-x-offset-of-border-icon-from-x0
  layer-box-y-offset-of-border-icon-from-y0
  layer-box-x-offset-of-text-from-x0
  layer-box-y-offset-of-text-from-y0
  layer-box-y-midpoint-in-workspace		; We can live without this.  Optimize later.
  layer-box-color?
  layer-box-label
  layer-box-layer-index
  layer-box-cursor-x-offset-in-workspace?
  layer-box-cursor-y-offset-in-workspace?
  layer-box-original-y-midpoint-in-workspace?	; We can live without this.
  layer-box-layer
  )

(defmacro layer-box-top-edge-in-workspace (layer-box)
  `(top-edge-of-block (layer-box-border-icon ,layer-box)))

(defmacro layer-box-left-edge-in-workspace (layer-box)
  `(left-edge-of-block (layer-box-border-icon ,layer-box)))

(defmacro layer-box-right-edge-in-workspace (layer-box)
  `(right-edge-of-block (layer-box-border-icon ,layer-box)))

(defmacro layer-box-bottom-edge-in-workspace (layer-box)
  `(bottom-edge-of-block (layer-box-border-icon ,layer-box)))

(defmacro layer-box-width (layer-box)
  `(width-of-block (layer-box-border-icon ,layer-box)))

(defmacro layer-box-height (layer-box)
  `(height-of-block (layer-box-border-icon ,layer-box)))





;;; The functions `create-layer-box' and `delete-layer-box' are the functions
;;; to be called for generation and reclaimation of layer boxes (respectively).
;;; Do not use make-layer-box and reclaim-layer-box as these macros/functions
;;; do not reclaim all the apropriate slot slot values.

;; The function/macro `create-layer-box' is defined in ICONS2 because of
;; forward references.

(defun delete-layer-box (layer-box)
  (let* ((serial-number
	   (layer-box-reference-serial-number layer-box))
	 icon)
    (setq icon (layer-box-layer-icon layer-box))
    (if (and (framep icon)
	     (frame-has-not-been-reprocessed-p icon serial-number))
	(delete-frame icon))
    (setq icon (layer-box-border-icon layer-box))
    (if (and (framep icon)
	     (frame-has-not-been-reprocessed-p icon serial-number))
	(delete-frame icon))
    (setq icon (layer-box-text-for-label layer-box))
    (if (and (framep icon)
	     (frame-has-not-been-reprocessed-p icon serial-number))
	(delete-frame icon)))
  (reclaim-layer-box layer-box))









;;; Def-structure Icon Editor Translator

(def-structure (icon-editor-translator
		 (:constructor 
		   make-icon-editor-translator
		   ()))
  (icon-editor-translator-state (icon-editor-state 'waiting))
  (icon-editor-translator-state-information nil)	; must initialize
  icon-editor-translator-last-marker-drawn?	; t, nil, or 'special
  )


(defun-substitution-macro create-icon-editor-translator ()
  (make-icon-editor-translator))

(defun-substitution-macro delete-icon-editor-translator (translator)
  (reclaim-icon-editor-slot-value
    (icon-editor-translator-state-information translator))
  (reclaim-icon-editor-translator translator))






;;; Def-structure Icon Editor Engine

(def-structure (icon-editor-engine
		 (:constructor
		   make-icon-editor-engine
		   ()))
  (icon-editor-engine-icon-width 0)
  (icon-editor-engine-icon-height 0)
  (icon-editor-engine-layers nil ); list of layers
  (icon-editor-engine-layers-tail nil)		; points to last cons cell in layers list
  (icon-editor-engine-number-of-layers 0)
  (icon-editor-engine-current-layer nil)
  (icon-editor-engine-current-layer-index 0)
  (icon-editor-engine-width-extent ;; icon width if no clipped drawing elements
    0)
  (icon-editor-engine-height-extent ;; icon height if no clipped drawing elements
    0)
  (icon-editor-engine-main-region? (icon-editor-default-region))

  (icon-editor-engine-main-color (icon-editor-default-color))
  (icon-editor-engine-outline-region? (icon-editor-default-region))
  (icon-editor-engine-outline-color (icon-editor-default-color))
  (icon-editor-engine-main-image? nil )
  (icon-editor-engine-text? nil )  ; (pbk 2/6/96)
  (icon-editor-engine-stipple? nil )
  (icon-editor-engine-global-stipple? nil ))  

;; Note:  The cleanup being done in cleanup-icon-editor should be done here instead
;; through the use of a :reclaimer specification in the def-structure for the
;; icon-editor-engine.  In cleanup-icon-editor I have only added reclaimation for text slot
;; specs and have not tried to reclaim the larger structures that are not being reclaimed by
;; reclaim-icon-editor-engine.  Be sure to delete that code when the reclaimer for the
;; icon-editor-engine is rewritten.  Beware, that this is a large project because the slots in
;; the engine contain many tricky aliases.  (pbk 2/6/96)
;; (Note: the major source of the leaks seems to be layer-boxes)


(defun-substitution-macro create-icon-editor-engine ()
  (make-icon-editor-engine))

(defun-substitution-macro delete-icon-editor-engine (engine)
  (reclaim-icon-editor-engine engine))


;;; The def-structure `icon-editor-view-pad' contains the information
;;; for managing drawing on the view pad.

(def-structure (icon-editor-view-pad
		 (:constructor
		   make-icon-editor-view-pad
		   (icon-editor-view-pad-x-in-workspace
		     icon-editor-view-pad-y-in-workspace
		     icon-editor-view-pad-bounding-box
		     icon-editor-view-pad-reference-serial-number
		     )))
  icon-editor-view-pad-x-in-workspace
  icon-editor-view-pad-y-in-workspace
  icon-editor-view-pad-bounding-box
  (icon-editor-view-pad-reference-serial-number nil :reclaimer reclaim-frame-serial-number)
  (icon-editor-view-pad-x-origin-in-workspace 0)	; Where x0 of icon is on workspace
  (icon-editor-view-pad-y-origin-in-workspace 0)
  icon-editor-view-pad-width
  icon-editor-view-pad-height
  icon-editor-view-pad-workspace
  (icon-editor-view-pad-x-scale (icon-editor-normalized-scale-factor))	; 1:1 scale
  (icon-editor-view-pad-y-scale (icon-editor-normalized-scale-factor))	; 1:1 scale
  icon-editor-view-pad-marker-stack		; stack of (frame . serial#)
  icon-editor-view-pad-iconic-entity
  (icon-editor-view-pad-iconic-entity-serial-number 0 :reclaimer reclaim-frame-serial-number)
  icon-editor-view-pad-xored-icon-for-current-layer?
  icon-editor-view-pad-icon-for-current-layer?
  (icon-editor-view-pad-serial-number-of-icon-for-current-layer nil :reclaimer reclaim-frame-serial-number)
  icon-editor-view-pad-left-bound-of-current-layer-in-workspace
  icon-editor-view-pad-top-bound-of-current-layer-in-workspace
  icon-editor-view-pad-right-bound-of-current-layer-in-workspace
  icon-editor-view-pad-bottom-bound-of-current-layer-in-workspace
  )


(defmacro view-pad-left-edge (view-pad)
  `(left-edge-of-block (icon-editor-view-pad-bounding-box ,view-pad)))

(defmacro view-pad-right-edge (view-pad)
  `(right-edge-of-block (icon-editor-view-pad-bounding-box ,view-pad)))


(defmacro view-pad-top-edge (view-pad)
  `(top-edge-of-block (icon-editor-view-pad-bounding-box ,view-pad)))

(defmacro view-pad-bottom-edge (view-pad)
  `(bottom-edge-of-block (icon-editor-view-pad-bounding-box ,view-pad)))


(defmacro view-pad-width (view-pad)
  `(width-of-block (icon-editor-view-pad-bounding-box ,view-pad)))

(defmacro view-pad-height (view-pad)
  `(height-of-block (icon-editor-view-pad-bounding-box ,view-pad)))









;;; The function `create-icon-editor-view-pad' should be used in place of
;;; make-icon-editor-view-pad.

(defun-substitution-macro create-icon-editor-view-pad
			  (x-in-workspace y-in-workspace)
  (declare (type fixnum x-in-workspace y-in-workspace))
  (let* ((bounding-box
	   (make-bounding-box
	     (initial-width-of-bounding-box-in-view-pad)
	     (initial-height-of-bounding-box-in-view-pad)))
	 (view-pad (make-icon-editor-view-pad
		     x-in-workspace y-in-workspace
		     bounding-box
		     (copy-frame-serial-number (current-frame-serial-number)))))
    (setf (icon-editor-view-pad-marker-stack view-pad) nil)	; stack of (frame . serial#)
    view-pad))

(defun delete-view-pad-marker-stack (marker-stack)
  (loop for frame-and-serial-number-pair in marker-stack
	do
    (if (frame-has-not-been-reprocessed-p (car frame-and-serial-number-pair)
					  (cdr frame-and-serial-number-pair))
	(delete-frame (car frame-and-serial-number-pair)))
    (reclaim-frame-serial-number (cdr frame-and-serial-number-pair))
    (reclaim-icon-editor-cons frame-and-serial-number-pair)
	finally
	  (reclaim-icon-editor-list marker-stack)))



;;; The function/macro `delete-icon-editor-view-pad-icon-entity' deletes
;;; the iconic entity in the view-pad if it has not already been deleted.

(defun-substitution-macro delete-icon-editor-view-pad-iconic-entity (view-pad)
  (let* ((iconic-entity? (icon-editor-view-pad-iconic-entity view-pad)))
    (when iconic-entity?
      (let* ((serial-number
	       (icon-editor-view-pad-iconic-entity-serial-number view-pad)))
	(when (frame-has-not-been-reprocessed-p iconic-entity? serial-number)
	  (delete-frame iconic-entity?)
	  (setf (icon-editor-view-pad-iconic-entity view-pad) nil))))))


;;; The function/macro `delete-icon-editor-view-pad-icon-for-current-layer'
;;; deletes the iconic entity for the current layer and the iconic entity used
;;; to xor the current layer (in the view-pad) if they have not already been
;;; deleted.

(defun delete-icon-editor-view-pad-icon-for-current-layer (view-pad)
  ;; defun because called several times
  (let* ((xored-iconic-entity?
	   (icon-editor-view-pad-xored-icon-for-current-layer? view-pad))
	 (iconic-entity? (icon-editor-view-pad-icon-for-current-layer? view-pad))
	 (serial-number
	   (icon-editor-view-pad-serial-number-of-icon-for-current-layer
	     view-pad)))
    (when xored-iconic-entity?
      (when (frame-has-not-been-reprocessed-p xored-iconic-entity? serial-number)
	(delete-frame xored-iconic-entity?)
	(setf (icon-editor-view-pad-xored-icon-for-current-layer? view-pad) nil)))
    (when iconic-entity?
      (when (frame-has-not-been-reprocessed-p iconic-entity? serial-number)
	(delete-frame iconic-entity?)
	(setf (icon-editor-view-pad-icon-for-current-layer? view-pad) nil)))))



;;; The function/macro `delete-icon-editor-view-pad' is to be used to reclaim
;;; the view-pad instead of reclaim-icon-editor-view-pad.  It performs the
;;; necessary reclaimation for the slots of the view pad.

(defun-substitution-macro delete-icon-editor-view-pad (view-pad)
  (let* ((bounding-box
	   (icon-editor-view-pad-bounding-box view-pad))
	 (reference-serial-number
	   (icon-editor-view-pad-reference-serial-number view-pad)))
    (if (frame-has-not-been-reprocessed-p bounding-box reference-serial-number)
	(delete-frame bounding-box))
    ;; Reclaim marker stack
    (delete-view-pad-marker-stack (icon-editor-view-pad-marker-stack view-pad))
    (delete-icon-editor-view-pad-iconic-entity view-pad)
    (delete-icon-editor-view-pad-icon-for-current-layer view-pad)
    (reclaim-icon-editor-view-pad view-pad)))















;;; The def-structure `icon-editor-layers-pad' hold information concerning
;;; the layers pad.

(def-structure (icon-editor-layers-pad
		 (:constructor
		   make-icon-editor-layers-pad
		   (icon-editor-layers-pad-x-in-workspace
		     icon-editor-layers-pad-y-in-workspace
		     icon-editor-layers-pad-bounding-box
		     icon-editor-layers-pad-bounding-box-serial-number
		     )))
  icon-editor-layers-pad-x-in-workspace
  icon-editor-layers-pad-y-in-workspace
  icon-editor-layers-pad-bounding-box
  (icon-editor-layers-pad-bounding-box-serial-number nil :reclaimer reclaim-frame-serial-number)
  icon-editor-layers-pad-x-origin-in-workspace
  icon-editor-layers-pad-y-origin-in-workspace
  icon-editor-layers-pad-workspace
  (icon-editor-layers-pad-x-scale (icon-editor-normalized-scale-factor))	; 1:1 scale
  (icon-editor-layers-pad-y-scale (icon-editor-normalized-scale-factor))	; 1:1 scale
  (icon-editor-layers-pad-max-layer-width 0)
  (icon-editor-layers-pad-max-layer-height 0)
  (icon-editor-layers-pad-layer-box-border-width (default-layer-box-border-width))
  (icon-editor-layers-pad-visible-top-layer-index 9999999)	; for scrolling
  (icon-editor-layers-pad-visible-bottom-layer-index 0)	; a large number
  (icon-editor-layers-pad-max-layer-box-width 0)
  (icon-editor-layers-pad-max-layer-box-height 0)
  )


(defmacro layers-pad-left-edge-in-workspace (layers-pad)
  `(left-edge-of-block (icon-editor-layers-pad-bounding-box ,layers-pad)))

(defmacro layers-pad-right-edge-in-workspace (layers-pad)
  `(right-edge-of-block (icon-editor-layers-pad-bounding-box ,layers-pad)))

(defmacro layers-pad-top-edge-in-workspace (layers-pad)
  `(top-edge-of-block (icon-editor-layers-pad-bounding-box ,layers-pad)))

(defmacro layers-pad-bottom-edge-in-workspace (layers-pad)
  `(bottom-edge-of-block (icon-editor-layers-pad-bounding-box ,layers-pad)))

(defmacro layers-pad-width-in-workspace (layers-pad)
  `(width-of-block (icon-editor-layers-pad-bounding-box ,layers-pad)))

(defmacro layers-pad-height-in-workspace (layers-pad)
  `(height-of-block (icon-editor-layers-pad-bounding-box ,layers-pad)))






;;; The function `create-icon-editor-layers-pad' should be used in place of
;;; make-icon-editor-layers-pad.

(defun-substitution-macro create-icon-editor-layers-pad
			  (x-in-workspace y-in-workspace)
  (let* ((bounding-box (make-bounding-box
			 (default-layers-pad-width)
			 (default-layers-pad-height)))
	 (border-width
	   (adjusted-bounding-box-border-width bounding-box))
	 (twice-border-width
	   (twicew border-width))
	 (layers-pad (make-icon-editor-layers-pad
		       x-in-workspace y-in-workspace
		       bounding-box (copy-frame-serial-number (current-frame-serial-number)))))
    (setf (icon-editor-layers-pad-x-origin-in-workspace layers-pad)
	  (+w x-in-workspace border-width))
    (setf (icon-editor-layers-pad-y-origin-in-workspace layers-pad)
	  (+w y-in-workspace border-width))
    (let* ((inner-width 	 
	     (-w (width-of-block bounding-box) twice-border-width 1))
	   (inner-height
	     (-w (height-of-block bounding-box) twice-border-width)))
      (setf (icon-editor-layers-pad-max-layer-box-width layers-pad) inner-width)
      (setf (icon-editor-layers-pad-max-layer-width layers-pad)
	    (-w inner-width (twicew (default-layer-box-border-width)) 2))
      (setf (icon-editor-layers-pad-max-layer-height layers-pad) inner-height)
      layers-pad)))


;;; The function/macro `delete-icon-editor-layers-pad' should be used in place
;;; of reclaim-icon-editor-layer-pad.

(defun-substitution-macro delete-icon-editor-layers-pad (layers-pad)
  (let* ((bounding-box (icon-editor-layers-pad-bounding-box layers-pad))
	 (serial-number
	   (icon-editor-layers-pad-bounding-box-serial-number layers-pad)))
    (if (frame-has-not-been-reprocessed-p bounding-box serial-number)
	(delete-frame bounding-box)))
  (reclaim-icon-editor-layers-pad layers-pad))








;;; The def-structure `icon-editor-button' is used to hold information about
;;; the various buttons used in the icon editor.

;; Consider merging these slots with the icon editor button class.
;; -pto 24oct89.

(def-structure (icon-editor-button
		 (:constructor
		   make-icon-editor-button
		   (icon-editor-button-x-in-workspace
		     icon-editor-button-y-in-workspace
		     icon-editor-button-width
		     icon-editor-button-height
		     icon-editor-button-frame
		     icon-editor-button-frame-serial-number)))
  icon-editor-button-x-in-workspace
  icon-editor-button-y-in-workspace
  icon-editor-button-width
  icon-editor-button-height
  icon-editor-button-frame
  (icon-editor-button-frame-serial-number nil :reclaimer reclaim-frame-serial-number)
  )


;;; The function `create-icon-editor-button' should be called in place
;;; of make-icon-editor-button.

(defun create-icon-editor-button (x-in-workspace y-in-workspace 
				  button-text-or-type)
  (declare (type fixnum x-in-workspace y-in-workspace))
  #+development (gensym-assert (and (or (text-string-p button-text-or-type)
					(symbolp button-text-or-type))
				    (typep x-in-workspace 'fixnum)
				    (typep y-in-workspace 'fixnum)))
  (let* ((button-frame
	   (if (text-string-p button-text-or-type)
	       (let* ((symbol-id-for-button
			(intern-text-string (string-upcasew button-text-or-type)))
		      (translated-button-text?
			(with-localization-purpose 'button-label
			  (translation-for-symbol? symbol-id-for-button))))
		 (make-button
		   (if (=w x-in-workspace 0) ;; for-use-by-system?
		       'big-icon-editor-text-button
		       'small-icon-editor-text-button)
		   (or (if translated-button-text?
			   (copy-text-string translated-button-text?))
		       (copy-text-string button-text-or-type))))
	       (make-button button-text-or-type))))
    (make-icon-editor-button
      x-in-workspace
      y-in-workspace
      (width-of-block button-frame)
      (height-of-block button-frame)
      button-frame
      (copy-frame-serial-number (current-frame-serial-number)))))
  





;;; The function `delete-icon-editor-button' should be used in place
;;; of reclaim-icon-editor-button.

(defun delete-icon-editor-button (icon-editor-button)
  #+development (gensym-assert (icon-editor-button-p icon-editor-button))
  (let* ((button-frame
	   (icon-editor-button-frame icon-editor-button)))
    (if (frame-has-not-been-reprocessed-p 
	  button-frame
	  (icon-editor-button-frame-serial-number icon-editor-button))
	(delete-frame button-frame)))
  (reclaim-icon-editor-button icon-editor-button))









;;; The Icon Editor Table Info Frame class is for i/o of parameters in
;;; the icon editor.

(def-class (icon-editor-table-info-frame entity)
  ;; For Icon Editor Tables in the Icon Editor Display:
  (icon-editor-table-info-frame-info
    nil system do-not-save vector-slot (type icon-editor-table-info-frame-info)
    do-not-identify-in-attribute-tables not-user-editable)
  (icon-editor-table-info-frame-main-region
    nil system do-not-save vector-slot (type region?))
  (icon-editor-table-info-frame-main-color
    foreground system do-not-save vector-slot (type color-or-metacolor))
  (icon-editor-table-info-frame-outline-region
    nil system do-not-save vector-slot (type region?))
  (icon-editor-table-info-frame-outline-color
    foreground system  do-not-save vector-slot (type color-or-metacolor))
  (icon-editor-table-info-frame-icon-width
    0 system do-not-save vector-slot (type positive-integer))
  (icon-editor-table-info-frame-icon-height
    0 system do-not-save vector-slot (type positive-integer))
  (icon-editor-table-info-frame-x-position
    0 system do-not-save vector-slot (type integer)
    ;;do-not-identify-in-attribute-tables
    not-user-editable)
  (icon-editor-table-info-frame-y-position
    0 system do-not-save vector-slot (type integer)
    ;;do-not-identify-in-attribute-tables
    not-user-editable)
  (icon-editor-table-info-frame-x-y-position
    0 system do-not-save vector-slot (type icon-editor-table-info-frame-x-y-position)
    do-not-identify-in-attribute-tables
    not-user-editable)
  (icon-editor-table-info-frame-global-stipple
    nil system do-not-save lookup-slot (type  global-stipple-specification?))

  (icon-editor-table-info-frame-stipple
    nil system do-not-save lookup-slot (type  stipple-specification?))
  
  ;; This is where one can type-in the name of an image and x,y offsets
  (icon-editor-table-info-frame-main-image
    nil system do-not-save lookup-slot (type image-specification?))
  
  ;; For typing in text in icons (pbk 2/6/96)
  (icon-editor-table-info-frame-text
    nil system do-not-save lookup-slot (type text-specification?))
  (icon-editor-table-info-frame-icon-editor
    nil system do-not-save lookup-slot))

(def-slot-value-reclaimer icon-editor-table-info-frame-icon-editor (frame icon-editor)
  frame icon-editor
  nil)
  
 



;;; Slot Aliases for Icon Editor Tables Frame:

(define-slot-alias region icon-editor-table-info-frame-main-region
  icon-editor-table-info-frame)
(define-slot-alias color icon-editor-table-info-frame-main-color
  icon-editor-table-info-frame)
(define-slot-alias outline-region icon-editor-table-info-frame-outline-region
  icon-editor-table-info-frame)
(define-slot-alias outline-color icon-editor-table-info-frame-outline-color
  icon-editor-table-info-frame)
(define-slot-alias width icon-editor-table-info-frame-icon-width
  icon-editor-table-info-frame)
(define-slot-alias height icon-editor-table-info-frame-icon-height
  icon-editor-table-info-frame)
(define-slot-alias stipple icon-editor-table-info-frame-global-stipple
  icon-editor-table-info-frame)
(define-slot-alias x icon-editor-table-info-frame-x-position
  icon-editor-table-info-frame)
(define-slot-alias y icon-editor-table-info-frame-y-position
  icon-editor-table-info-frame)
(define-slot-alias x-y icon-editor-table-info-frame-x-y-position
  icon-editor-table-info-frame)
(define-slot-alias stippled-area icon-editor-table-info-frame-stipple
  icon-editor-table-info-frame)
(define-slot-alias image icon-editor-table-info-frame-main-image
  icon-editor-table-info-frame)
(define-slot-alias text icon-editor-table-info-frame-text
  icon-editor-table-info-frame)





;;; Slot Value Writers for Icon Editor Tables

;; Consider adding slot value writers for both the x and y position
;; boxes, and make them write the coordinates in the form: (x,y).

(def-slot-value-writer region? (value)
  (twrite-symbol (cond ((and value (neq value :nil)) value)
		       (t 'none))))

(def-slot-value-writer color-or-metacolor (value)
  (twrite-color value))


;; The def-slot-value-writer for icon-editor-table-info-frame-info is moved
;; to ICONS2 because of eval-when problems.  -pto 03oct89


(def-slot-value-writer icon-editor-table-info-frame-x-y-position (value frame)
  (declare (ignore value))
  (tformat "(~a, ~a)"
	   (icon-editor-table-info-frame-x-position frame)
	   (icon-editor-table-info-frame-y-position frame)))





;;; Slot Value Reclaimers for Icon Editor Tables:

(def-slot-value-reclaimer icon-editor-table-info-frame-info (value)
  (reclaim-icon-editor-slot-value value))








;;; The def-structure `icon-editor-table' is used to hold information about
;;; the various tables used in the icon editor.

;; Consider merging these slots with the icon-editor-table-info-frame class.
;; -pto 24oct89.

(def-structure (icon-editor-table
		 (:constructor
		   make-icon-editor-table
		   (icon-editor-table-x-in-workspace
		     icon-editor-table-y-in-workspace
		     icon-editor-table-width
		     icon-editor-table-height
		     icon-editor-table-info-frame
		     icon-editor-table-display-frame
		     icon-editor-table-reference-serial-number
		     icon-editor-table-display-slot-names
		     )))
  icon-editor-table-x-in-workspace
  icon-editor-table-y-in-workspace
  icon-editor-table-width
  icon-editor-table-height
  icon-editor-table-info-frame
  icon-editor-table-display-frame
  (icon-editor-table-reference-serial-number nil :reclaimer reclaim-frame-serial-number)
  icon-editor-table-display-slot-names	; an icon-editor-list
  )




;;; The function `create-icon-editor-table' should be used in place of
;;; make-icon-editor-table.  The argument display-slot-name-or-names is
;;; either an icon-editor-list of slot name(s) or a slot name to display
;;; for i/o in a table.  The arugment is consumed by the creation
;;; function

(defun create-icon-editor-table (x-in-workspace y-in-workspace
				 display-slot-name-or-names
				 use-small-fonts?)
  (declare (type fixnum x-in-workspace y-in-workspace))
  #+development (gensym-assert (and (or (symbolp display-slot-name-or-names)
					(consp  display-slot-name-or-names))
				    (typep x-in-workspace 'fixnum)
				    (typep y-in-workspace 'fixnum)))
  (let* ((display-slot-names
	   (if (symbolp display-slot-name-or-names)
	       (icon-editor-cons display-slot-name-or-names nil)
	       display-slot-name-or-names))
	 (info-frame
	   (make-frame 'icon-editor-table-info-frame)))
    (setf (icon-editor-table-info-frame-info info-frame) (icon-editor-state 'waiting)
	  (icon-editor-table-info-frame-main-region info-frame) (icon-editor-default-region)
	  (icon-editor-table-info-frame-global-stipple info-frame) nil
	  (icon-editor-table-info-frame-stipple info-frame) nil
	  (icon-editor-table-info-frame-main-image info-frame) NIL
	  (icon-editor-table-info-frame-text info-frame) NIL   ; (pbk 2/6/96)
	  (icon-editor-table-info-frame-main-color info-frame) (icon-editor-default-color)
	  (icon-editor-table-info-frame-outline-color info-frame) (icon-editor-default-color)
	  (icon-editor-table-info-frame-outline-region info-frame) (icon-editor-default-region)
	  (icon-editor-table-info-frame-icon-width info-frame) (default-width-of-icon)
	  (icon-editor-table-info-frame-icon-height info-frame) (default-height-of-icon))

    (let* ((display-frame
	     (make-attributes-table
	       info-frame
	       nil
	       (if use-small-fonts?
		   'small-class-format)		; for small font
	       (if use-small-fonts?
		   'small-attribute-value-format)
	       (if use-small-fonts?
		   'small-attribute-description-format)
	       display-slot-names)))
      (make-icon-editor-table
	x-in-workspace
	y-in-workspace
	(width-of-block display-frame)
	(height-of-block display-frame)
	info-frame
	display-frame
	(copy-frame-serial-number (current-frame-serial-number))
	display-slot-names))))


;;; The function `delete-icon-editor-table' should be used in place of
;;; reclaim-icon-editor-table.

(defun delete-icon-editor-table (icon-editor-table)
  #+development (gensym-assert (icon-editor-table-p icon-editor-table))
  (let* ((info-frame
	   (icon-editor-table-info-frame icon-editor-table))
	 (display-frame
	   (icon-editor-table-display-frame icon-editor-table))
	 (reference-serial-number
	   (icon-editor-table-reference-serial-number icon-editor-table)))
    (if (frame-has-not-been-reprocessed-p
	  info-frame reference-serial-number)
	(delete-frame info-frame))
    (if (frame-has-not-been-reprocessed-p
	  display-frame reference-serial-number)
	(delete-frame info-frame)))
  (reclaim-icon-editor-list 
    (icon-editor-table-display-slot-names icon-editor-table))
  (reclaim-icon-editor-table icon-editor-table))






(define-workstation-context icon-editor ()
  :selection-style top-level-with-mouse-tracking-is-selection-style
  :structure-name icon-editor
  :keymaps (icon-editor-keymap)
  :constructor (make-icon-editor
		 (icon-editor-class-definition
		   icon-editor-workspace
		   icon-editor-reference-serial-number))
  :state-variables (icon-editor-class-definition
		     icon-editor-workspace
		     icon-editor-reference-serial-number
		     icon-editor-region-and-name-alist
		     icon-editor-variable-spec-list
		     icon-editor-icon-background-image
		     icon-editor-stipple-spec
		     (icon-editor-translator (create-icon-editor-translator))
		     (icon-editor-engine (create-icon-editor-engine))

		     ;; For the Icon Editor Display (these widgets need frames):
		     ;; The "create-" functions are defined in module ICONS2.
		     icon-editor-view-pad
		     icon-editor-layers-pad
		     icon-editor-buttons
		     icon-editor-tables
		     icon-editor-info-box		    ; an icon editor table listed in icon-editor-tables
		     icon-editor-size-table
		     icon-editor-label-table
		     icon-editor-x-position-box
		     icon-editor-y-position-box
		     icon-editor-x-y-position-box

		     (icon-editor-mouse-down-p nil) ; t or nil

		     ;; Histories for the Icon Editor:
		     icon-editor-history-for-undo
		     icon-editor-history-for-redo
		     (icon-editor-snapping-on? t)
		     (icon-editor-main-color-menu? nil)
		     icon-editor-main-color-menu-serial-number))


(def-structure-method clean-up-workstation-context (icon-editor)
  (cleanup-icon-editor icon-editor)
  (funcall-superior-method icon-editor))


;;; The macro `icon-editor-killed-p' returns non-nil if the icon editor
;;; workspace has been deleted.  We identify the icon editor with the
;;; icon editor workspace.

(def-substitution-macro icon-editor-killed-p (icon-editor)
  (frame-has-been-reprocessed-p
    (icon-editor-workspace icon-editor)
    (icon-editor-reference-serial-number icon-editor)))

;; one other frame to check! - how about the object definition?

(def-structure-method valid-workstation-context-p (icon-editor)
  (and (funcall-superior-method icon-editor)
       (not (icon-editor-killed-p icon-editor))
       (frame-has-not-been-reprocessed-p 
	 (icon-editor-class-definition icon-editor)
	 (icon-editor-reference-serial-number icon-editor))))


;;; The function `create-icon-editor' should be used in place of
;;; make-icon-editor because it creates all appropriate frames and
;;; structures within the icon editor.  This function is in ICONS2
;;; because of references to definition of widgets in that module.



;;; The function `delete-icon-editor-main-color-menu' is used to
;;; reclaim the frame in the icon-editor-main-color-menu slot of
;;; the icon editor.

(defun delete-icon-editor-main-color-menu (icon-editor)
  (when (icon-editor-main-color-menu? icon-editor)
    (when (frame-has-not-been-reprocessed-p
	    (icon-editor-main-color-menu? icon-editor)
	    (icon-editor-main-color-menu-serial-number icon-editor))
      (delete-frame (icon-editor-main-color-menu? icon-editor))
      (setf (icon-editor-main-color-menu? icon-editor) nil))))







;;; The class `icon-editor-workspace' is a child class of temporary-workspace
;;; and is only used by the icon-editor.

(def-class (icon-editor-workspace temporary-workspace)
  (workspace-margin 10))			; margin had been defaulted 





;;;; Useful Functions For The Icon Editor






;;; The function `reclaim-icon-editor-slot-value' is a generic reclaimer for
;;; slots in the icon editor.  It can reclaim trees of icon editor conses,
;;; strings, and layer boxes.  It does not reclaim any thing else; it does not
;;; delete frames.  If it is given a tree, it will treat the tree's branches as
;;; other icon editor slot values.  This function is based on the function
;;; `reclaim-slot-value'

(defun reclaim-icon-editor-slot-value (value-to-reclaim)
  (cond
    ((consp value-to-reclaim)
     (cond
       ((not (or (eq value-to-reclaim no-value)	; should not occur at top level
		 (default-slot-constant-p value-to-reclaim)))
	(loop with l = value-to-reclaim		; a bit slow for 1 or 2 conses
	      as x = (car l)
	      do (if (not (symbolp x))		; only for speed
		     (if (not (numberp x))	; only for speed
			 (reclaim-icon-editor-slot-value x)
			 ;; recycle x if heap-allocated!
			 ))
	      until (or (atom (setq l (cdr l))) (eq l no-value))
	      finally
		(cond
		  (l (reclaim-icon-editor-slot-value l)
		     (setf (cdr (last value-to-reclaim)) nil)))
		(reclaim-icon-editor-list value-to-reclaim)))))
    ((layer-box-p value-to-reclaim)
     (delete-layer-box value-to-reclaim))
    ((text-string-p value-to-reclaim)
     (reclaim-text-string value-to-reclaim))
    ((integerp value-to-reclaim) nil)
    ;; Else do nothing.
    ;; Don't delete frames.
    ))












;;; Scaling



;;; The macros `delta-x-in-target' and `delta-y-in-target' allow conversion
;;; from workspace coordinates to the target coordinate system, given the
;;; scaling factor.  The macros `delta-x-in-workspace-from-target' and 
;;; `delta-y-in-workspace-from-target' do the opposite.

(defmacro delta-x-in-target (delta-x-in-workspace x-scale-of-target)
  `(inverse-scalef ,x-scale-of-target ,delta-x-in-workspace))

(defmacro delta-y-in-target (delta-y-in-workspace y-scale-of-target)
  `(inverse-scalef ,y-scale-of-target ,delta-y-in-workspace))


(defmacro delta-x-in-workspace-from-target (delta-x-in-target x-scale-of-target)
  `(scalef ,x-scale-of-target ,delta-x-in-target))

(defmacro delta-y-in-workspace-from-target (delta-y-in-target y-scale-of-target)
  `(scalef ,y-scale-of-target ,delta-y-in-target))




;;; Scaling for the View Pad:


;;; The macros `icon-editor-x-scale' and `icon-editor-y-scale' just
;;; extracts the x and y scale of the view pad from the icon editor.

(defmacro icon-editor-x-scale (icon-editor)
  `(icon-editor-view-pad-x-scale (icon-editor-view-pad ,icon-editor)))

(defmacro icon-editor-y-scale (icon-editor)
  `(icon-editor-view-pad-y-scale (icon-editor-view-pad ,icon-editor)))





;;; The macros `delta-x-in-view-pad', `delta-y-in-view-pad',
;;; `delta-x-in-workspace-from-view-pad', `delta-y-in-workspace-from-view-pad',
;;; `x-in-view-pad-workspace-from-workspace',
;;; `y-in-view-pad-workspace-from-workspace',
;;; `x-in-workspace-from-view-pad-workspace', and
;;; `y-in-workspace-from-view-pad-workspace', `x-in-view-pad', `y-in-view-pad',
;;; `x-in-workspace-from-view-pad', and `y-in-workspace-from-view-pad' allow
;;; conversion between view pad and icon editor workspace coordinates.

(defmacro delta-x-in-view-pad (delta-x-in-workspace view-pad &optional x-scale)
  `(inverse-scalef ,(or x-scale `(icon-editor-view-pad-x-scale ,view-pad))
		   ,delta-x-in-workspace))


(defmacro delta-y-in-view-pad (delta-y-in-workspace view-pad &optional y-scale)
  `(inverse-scalef ,(or y-scale `(icon-editor-view-pad-y-scale ,view-pad))
		   ,delta-y-in-workspace))


(defmacro delta-x-in-workspace-from-view-pad (delta-x-in-view-pad view-pad
								  &optional x-scale)
  `(scalef ,(or x-scale `(icon-editor-view-pad-x-scale ,view-pad))
	   ,delta-x-in-view-pad))

(defmacro delta-y-in-workspace-from-view-pad (delta-y-in-view-pad view-pad
								  &optional y-scale)
  `(scalef ,(or y-scale `(icon-editor-view-pad-y-scale ,view-pad))
	   ,delta-y-in-view-pad))



(defmacro x-in-view-pad-workspace-from-workspace (x-in-workspace view-pad)
  `(-w ,x-in-workspace (icon-editor-view-pad-x-origin-in-workspace
			 ,view-pad)))

(defmacro y-in-view-pad-workspace-from-workspace (y-in-workspace view-pad)
  `(-w ,y-in-workspace (icon-editor-view-pad-y-origin-in-workspace
			 ,view-pad)))

(defmacro x-in-workspace-from-view-pad-workspace (x-in-view-pad-workspace view-pad)
  `(+w ,x-in-view-pad-workspace
       (icon-editor-view-pad-x-origin-in-workspace ,view-pad)))

(defmacro y-in-workspace-from-view-pad-workspace (y-in-view-pad-workspace view-pad)
  `(+w ,y-in-view-pad-workspace
       (icon-editor-view-pad-y-origin-in-workspace ,view-pad)))





(def-substitution-macro x-in-view-pad (x-in-workspace view-pad)
  (delta-x-in-view-pad
    (x-in-view-pad-workspace-from-workspace x-in-workspace view-pad)
    view-pad))

(def-substitution-macro y-in-view-pad (y-in-workspace view-pad)
  (delta-y-in-view-pad 
    (y-in-view-pad-workspace-from-workspace y-in-workspace view-pad)
    view-pad))


(def-substitution-macro x-in-workspace-from-view-pad (x-in-view-pad view-pad)
  (x-in-workspace-from-view-pad-workspace
    (delta-x-in-workspace-from-view-pad x-in-view-pad view-pad)
    view-pad))

(def-substitution-macro y-in-workspace-from-view-pad (y-in-view-pad view-pad)
  (y-in-workspace-from-view-pad-workspace
    (delta-y-in-workspace-from-view-pad y-in-view-pad view-pad)
    view-pad))








;;; Scaling for the Layers Pad


(defmacro delta-x-in-layers-pad (delta-x-in-workspace layers-pad &optional x-scale)
  `(inverse-scalef ,(or x-scale `(icon-editor-layers-pad-x-scale ,layers-pad))
		   ,delta-x-in-workspace))


(defmacro delta-y-in-layers-pad (delta-y-in-workspace layers-pad &optional y-scale)
  `(inverse-scalef ,(or y-scale `(icon-editor-layers-pad-y-scale ,layers-pad))
		   ,delta-y-in-workspace))


(defmacro delta-x-in-workspace-from-layers-pad (delta-x-in-layers-pad layers-pad
					      &optional x-scale)
  `(scalef ,(or x-scale `(icon-editor-layers-pad-x-scale ,layers-pad))
	   ,delta-x-in-layers-pad))

(defmacro delta-y-in-workspace-from-layers-pad (delta-y-in-layers-pad layers-pad
					      &optional y-scale)
  `(scalef ,(or y-scale `(icon-editor-layers-pad-y-scale ,layers-pad))
	   ,delta-y-in-layers-pad))







(defmacro x-in-layers-pad-workspace-from-workspace (x-in-workspace layers-pad)
  `(-w ,x-in-workspace (icon-editor-layers-pad-x-origin-in-workspace
			 ,layers-pad)))

(defmacro y-in-layers-pad-workspace-from-workspace (y-in-workspace layers-pad)
  `(-w ,y-in-workspace (icon-editor-layers-pad-y-origin-in-workspace
			 ,layers-pad)))

(defmacro x-in-workspace-from-layers-pad-workspace (x-in-layers-pad-workspace layers-pad)
  `(+w ,x-in-layers-pad-workspace
       (icon-editor-layers-pad-x-origin-in-workspace ,layers-pad)))

(defmacro y-in-workspace-from-layers-pad-workspace (y-in-layers-pad-workspace layers-pad)
  `(+w ,y-in-layers-pad-workspace
       (icon-editor-layers-pad-y-origin-in-workspace ,layers-pad)))





(def-substitution-macro x-in-layers-pad (x-in-workspace layers-pad)
  (delta-x-in-layers-pad
    (x-in-layers-pad-workspace-from-workspace x-in-workspace layers-pad)
    layers-pad))

(def-substitution-macro y-in-layers-pad (y-in-workspace layers-pad)
  (delta-y-in-layers-pad 
    (y-in-layers-pad-workspace-from-workspace y-in-workspace layers-pad)
    layers-pad))


(def-substitution-macro x-in-workspace-from-layers-pad (x-in-layers-pad layers-pad)
  (x-in-workspace-from-layers-pad-workspace
    (delta-x-in-workspace-from-layers-pad x-in-layers-pad layers-pad)
    layers-pad))

(def-substitution-macro y-in-workspace-from-layers-pad (y-in-layers-pad layers-pad)
  (y-in-workspace-from-layers-pad-workspace
    (delta-y-in-workspace-from-layers-pad y-in-layers-pad layers-pad)
    layers-pad))











;;; History Keeping Functions for Undoing in the Icon Editor


;; WORK TO BE DONE HERE!


;; The function `push-old-value-into-icon-editor-undo-history' ... This
;; function eats its arguments (which are assumed to be icon-editor-trees).

;; This is not implemented yet.  -pto 24oct89

;(defun push-old-value-into-icon-editor-undo-history (icon-editor
;						     old-value-descriptor)
;  (setf (icon-editor-history-for-undo icon-editor)
;	(icon-editor-cons old-value-descriptor 
;			  (icon-editor-history-for-undo icon-editor))))


;; This is not implemented yet.  -pto 24oct89

;(defun pop-old-value-from-icon-editor-undo-history (icon-editor)
;  (let* ((history (icon-editor-history-for-undo icon-editor)))
;    (setf (icon-editor-history-for-undo icon-editor)
;	  (cdr history))
;    (prog1
;      (car history)
;      (reclaim-icon-editor-cons history))))


;(defun push-old-value-into-icon-editor-redo-history (icon-editor
;						     old-value-descriptor)
;  (setf (icon-editor-history-for-redo icon-editor)
;	(icon-editor-cons old-value-descriptor 
;			  (icon-editor-history-for-redo icon-editor))))


;(defun pop-old-value-from-icon-editor-redo-history (icon-editor)
;  (let* ((history (icon-editor-history-for-redo icon-editor)))
;    (setf (icon-editor-history-for-redo icon-editor)
;	  (cdr history))
;    (prog1
;      (car history)
;      (reclaim-icon-editor-cons history))))



;; The function `clear-icon-editor-redo-history' should be called whenever
;; the user is in an undo mode and does something besides undo or redo.

;(defun clear-icon-editor-redo-history (icon-editor)
;  (reclaim-icon-editor-slot-value (icon-editor-history-for-redo icon-editor))
;  (setf (icon-editor-history-for-redo icon-editor) nil))












;;; The function `get-color-of-region-in-icon-editor' maps the region of
;;; an icon description to its color name.  The function
;;; `set-color-of-region-in-icon-editor' sets the region.

(defun get-color-of-region-in-icon-editor (icon-editor region)
  (let* ((region-and-name-alist
	   (icon-editor-region-and-name-alist icon-editor)))
    (let* ((label-and-name-pair?
	     (assq region region-and-name-alist)))
      (if label-and-name-pair?
	  (cdr label-and-name-pair?)
	  nil))))



;;; The function `set-color-of-region-in-icon-editor' sets the color of a
;;; region in the icon editor.  If color? is nil, the entry for region is taken
;;; out.

(defun set-color-of-region-in-icon-editor (icon-editor region color?)
  (let* ((region-and-name-alist
	   (icon-editor-region-and-name-alist icon-editor))
	 (label-and-name-pair?
	   (assq region region-and-name-alist)))
    (if color?
	;; Add/change entry
	(if label-and-name-pair?
	    (setf (cdr label-and-name-pair?) color?)
	    (setf (icon-editor-region-and-name-alist icon-editor)
		  (icon-editor-cons
		    (icon-editor-cons region color?)
		    region-and-name-alist)))
	;; Delete entry
	(when label-and-name-pair?
	  (when (not (assq region (icon-editor-engine-layers
				    (icon-editor-engine icon-editor))))
	    ;; When region is no longer in use.
	    (loop with region-and-name
		  with tail? = nil
		  for rest-of-alist on region-and-name-alist
		  do
		  (setq region-and-name (car rest-of-alist))
		  (when (eq (car region-and-name) region)
		    (if tail?
			(setf (cdr tail?) (cdr rest-of-alist))
			(setf (icon-editor-region-and-name-alist icon-editor)
			      (cdr rest-of-alist)))
		    (reclaim-icon-editor-cons region-and-name)
		    (reclaim-icon-editor-cons rest-of-alist)
		    (return))
		  (setq tail? rest-of-alist)))))
    #+development
    (icon-editor-region-and-name-alist icon-editor)))




;;; The function `get-or-create-color-of-region-in-icon-editor' will try to map
;;; the region of an icon description to its color name.  If it fails to
;;; find a mapping, it creates a new entry in the icon editor for the new color
;;; label.  In either case, the color name, associated to the region is
;;; returned.

(defun get-or-create-color-of-region-in-icon-editor
       (icon-editor region color-if-have-to-create?)
  (let* ((region-and-name-alist
	   (icon-editor-region-and-name-alist icon-editor))
	 (label-and-name-pair?
	   (assq region region-and-name-alist)))
    (if label-and-name-pair?
	(cdr label-and-name-pair?)
	(progn
	  #+development
	  (if (not color-if-have-to-create?)
	      (cerror
		"Continue, ignoring error."
		"Trying to create an illegal color name for region ~a ~
		   in get-or-create-color-of-region-in-icon-editor"
		region))
	  (setf (icon-editor-region-and-name-alist icon-editor)
		(icon-editor-cons
		  (icon-editor-cons region color-if-have-to-create?)
		  region-and-name-alist))
	  color-if-have-to-create?))))


















;;;; Functions for Handling Icon Descriptions


;;; Icon Editor Engine's Layers:
;;;
;;; <layers>::= () | (<layer> . <layers>)
;;; <label> ::= <region> | <color-or-metacolor>
;;; <layer> ::= (<label> <layer-box> <drawing-elements> <tail-of-drawing-elements>)
;;; <drawing-elements> ::= () | (<drawing-element> . <drawing-elements>)
;;; <drawing-element> ::=		[see GRAMMAR2]
;;;	(point <point>) |
;;;	<lines-element> |
;;;	<lines-arc-element> |
;;;	(outline <list-of-points>) |
;;;	(circle <point> <point> <point>) |
;;;	(solid-rectangle <point> <point>) |
;;;	(filled-circle <point> <point> <point>) |
;;;	(filled polygon <fill-line-list> . <list-of-triangles>) |
;;;     (image <name>)
;;;
;;; <list-of-points> ::= (<point>) | (<point> . <list-of-points>)
;;; <lines-element> ::= (lines <list-of-points>)
;;; <lines-arc-element> ::=  (lines <point> (arc <point>) <point>)
;;; <list-of-triangles> ::= (<triangle>) | (<triangle> . <list-of-triangles>)
;;; <triangle> ::= (<point> <point> <point>)
;;; <line-list> ::= (<point>) | (<point> . <line-list>) | (<arc> . <line-list>)

(defmacro make-layer (label layer-box? drawing-elements drawing-elements-tail)
  `(icon-editor-list ,label ,layer-box? ,drawing-elements ,drawing-elements-tail))

(defmacro label-of-layer (layer)
  `(first ,layer))

(defmacro layer-box-of-layer (layer)		; take this out later.  -pto 04oct89
  `(second ,layer))

(defmacro layer-box?-of-layer (layer)
  `(second ,layer))

(defmacro drawing-elements-of-layer (layer)
  #-SymScale
  `(third ,layer)
  #+SymScale
  `(car (cddr ,layer)))  ; THIRD is not supported by CAS

(defmacro drawing-elements-tail-of-layer (layer)
  #-SymScale
  `(fourth ,layer)
  #+SymScale
  `(car (cdddr ,layer))) ; FOURTH is not supported by CAS



;;; The function `image-of-layer?' pulls out the image spec drawing element, if
;;; any.

(defun image-of-layer? (layer)
  (loop for drawing-element in (drawing-elements-of-layer layer)
	when (image-drawing-element-p drawing-element)
	  return drawing-element))

;;; The function `text-of-layer?' pulls out the first drawing element of the
;;; given layer that is a text-drawing-element (ie the car is the symbol 'text)
;;; (pbk 2/6/96)

(defun text-of-layer? (layer)  
  (loop for drawing-element in (drawing-elements-of-layer layer)
	when (text-drawing-element-p drawing-element)
	  return drawing-element))

;;; The function `stipple-of-layer?' pulls out the first drawing element of the
;;; given layer that is a stipple-drawing-element (ie the car is the symbol
;;; 'stippled-area) 

(defun stipple-of-layer? (layer)  
  (loop for drawing-element in (drawing-elements-of-layer layer)
	when (stipple-drawing-element-p drawing-element)
	  return drawing-element))

(defmacro reclaim-layer (layer)
  `(progn
     (setf (drawing-elements-tail-of-layer ,layer) nil)
     (reclaim-icon-editor-slot-value ,layer)
     ;; make sure the reclaimed variable cannot be referenced.
     (setq ,layer nil)))

;;; The function `decompose-polygon-using-slot-value-conses' is the
;;; same as the decompose-polygon function, except that the decomposed
;;; polygon (a list of triangles) is made up of slot-value conses.

(defun decompose-polygon-using-slot-value-conses (polygon)
  (if (simple-polygon-p polygon)
      (with-phrase-conses
	(copy-tree-using-slot-value-conses
	  (decompose-polygon polygon)))))

(defun decompose-polygon-using-icon-editor-conses (polygon)
  (if (simple-polygon-p polygon)
      (with-phrase-conses
	(copy-tree-using-icon-editor-conses
	  (decompose-polygon polygon)))))



;;; The function `scaled-slot-value-point' returns a <point>, scaled
;;; according to the x and y scales.  The <point> is a slot-value list
;;; and has to be reclaimed.  The function `scaled-icon-editor-point' does
;;; the same, except, that it uses two icon-editor conses (instead of
;;; slot-value conses) and it scales to the target, instead of to the
;;; workspace

(defun scaled-slot-value-point (x-in-target y-in-target
					    x-scale-of-target y-scale-of-target)
  (slot-value-list
    (delta-x-in-workspace-from-target x-in-target x-scale-of-target)
    (delta-y-in-workspace-from-target y-in-target y-scale-of-target)))


(defun scaled-icon-editor-point (x-in-workspace y-in-workspace
				 x-scale-of-target y-scale-of-target)
  (icon-editor-list
    (delta-x-in-target x-in-workspace x-scale-of-target)
    (delta-y-in-target y-in-workspace y-scale-of-target)))




;;; The functions `copy-drawing-element-with-icon-editor-conses' and
;;; `copy-drawing-element-with-slot-value-conses' copy line drawing
;;; elements and scale the coordinates accordingly.
;;; If the drawing-element contains points containing variables (called power-points)
;;; and the caller wants to evaluate these points, then pass in t for eval-power-points-p.
;;; The caller must then wrap the call to copy-drawing-element with 
;;; evaluating-icon-points and the variable list containing the variables
;;; in question should be held in that context. If eval-power-points-p is
;;; nil then the point is copied using copy-tree.

(defmacro copy-drawing-element
    (cons-pool drawing-element x-scale-of-target y-scale-of-target eval-power-points-p)
  (let* ((conser (build-ab-symbol cons-pool 'cons))
	 (lister (build-ab-symbol cons-pool 'list))
	 (copy-tree (build-ab-symbol 'copy-tree-using cons-pool 'conses))
	 (copy-list (build-ab-symbol 'copy-list-using cons-pool 'conses))
	 (scaled-point (build-ab-symbol 'scaled cons-pool 'point)))
    `(if (atom ,drawing-element)
	 ,drawing-element

	 (case (car drawing-element)
	   (image					    ; (image <name> <origin> <scale>)
	    (let* ((name (second ,drawing-element))
		   (unevaled-origin (third ,drawing-element))
		   (origin (cond ((null unevaled-origin)
				  nil)
				 (,eval-power-points-p
				  (,lister 
				     (point-x unevaled-origin) (point-y unevaled-origin)))
				 (t (,copy-tree unevaled-origin)))))
	      (cond ((and (=f ,x-scale-of-target (normalized-scale))
			  (=f ,y-scale-of-target (normalized-scale)))
		     (if origin
			 (,lister 'image name origin) 
			 (,lister 'image name)))
		    (t
		     (,lister 'image
			      name
			      (if origin origin (,lister 0 0))
			      (,lister ,x-scale-of-target ,y-scale-of-target))))))
	   
	   (text     ; (this DOES copy the strings (pbk 2/6/96))
	    (let* ((the-whole-string
		     (cond (,eval-power-points-p
			    (let ((evaled-text-string (simple-eval-for-icon (second ,drawing-element))))
			      (cond ((symbolp evaled-text-string)
				     (stringw "undefined-string")) ;this should never happen
				    (t (copy-text-string evaled-text-string)))))
			   ((symbolp (second ,drawing-element))
			    (second ,drawing-element))
			   (t (copy-text-string (second ,drawing-element)))))
		   (unevaled-origin (third ,drawing-element))
		   (origin (cond (,eval-power-points-p
				  (,lister 
				     (point-x unevaled-origin) (point-y unevaled-origin)))
				 (t (,copy-tree unevaled-origin))))
		   (font
		     (cond (,eval-power-points-p
			    (simple-eval-for-icon (fourth ,drawing-element)))
			   (t
			    (fourth ,drawing-element)))))
	      (cond ((or (null ,x-scale-of-target)
			 (null ,y-scale-of-target)
			  (and (=f ,x-scale-of-target (normalized-scale))
			       (=f ,y-scale-of-target (normalized-scale))))
		     (,lister 'text the-whole-string origin 
			      (,copy-list font)))
		    (t
		     (,lister 'text
			      the-whole-string
			      origin
			      (,copy-list font) 
			      (,lister ,x-scale-of-target ,y-scale-of-target))))))

	   (stippled-area		; (stippled-area <stipple> [<point-1> <point-2>])
	    ;; ignoring x/y scale -- not sure how to handle! (MHD 3/13/01)
	    (cond
	      (,eval-power-points-p	    
	       (let* ((stipple (second ,drawing-element))
		      (point-1 (third ,drawing-element))
		      (point-2 (fourth ,drawing-element)))
		 (nconc
		   (,lister
		      'stippled-area
		      stipple)
		   (if point-1
		       (,lister
			  (,lister (point-x point-1) (point-y point-1))
			  (,lister (point-x point-2) (point-y point-2)))))))
	      (t (,copy-tree ,drawing-element))))		     

	   (filled-polygon			       ; (filled-polygon points points ...)
	    (cond (,eval-power-points-p
		   (,conser
		      (car ,drawing-element)
		      (loop for points in (cdr ,drawing-element)
			    collect (loop for point in points
					  collect (,scaled-point
						     (point-x point) (point-y point)
						     ,x-scale-of-target ,y-scale-of-target)
					    using ,conser)
			      using ,conser)))
		  (t
		   (,copy-tree ,drawing-element))))

	   (t
	    (loop for x in drawing-element
		  collect (cond
			    ((and (arc-point-p x) ,eval-power-points-p)
			     (,lister
				'arc
				(let ((x (cadr x)))
				  (,scaled-point
				     (point-x x) (point-y x)
				     ,x-scale-of-target ,y-scale-of-target))))
			    ((constant-point-p x) 
			     (,scaled-point
				(point-x x) (point-y x)
				,x-scale-of-target ,y-scale-of-target))
			    ((and (power-point-p x) ,eval-power-points-p) 
			     (,scaled-point
				(point-x x) (point-y x)
				,x-scale-of-target ,y-scale-of-target))
			    (t
			      (,copy-tree x)))
		    using ,conser))))))

;; Only had need for eval-power-points-p in the icon-editor in
;; 'convert-list-of-layers-to-line-drawing-description

    
(defun copy-drawing-element-with-icon-editor-conses
    (drawing-element x-scale-of-target y-scale-of-target)
  (copy-drawing-element
    icon-editor drawing-element x-scale-of-target y-scale-of-target
    nil ;eval-power-points-p
    ))

(defun copy-drawing-element-with-slot-value-conses
    (drawing-element x-scale-of-target y-scale-of-target eval-power-points-p)
  (copy-drawing-element
    slot-value drawing-element x-scale-of-target y-scale-of-target eval-power-points-p))



;;; The function `convert-line-drawing-description-to-list-of-layers' returns:
;;; (1) an icon-editor list of layers (which must be reclaimed),
;;; (2) color region-and-name-alist for the icon.
;;;
;;; The x and y scales specified are the unnormalized scale of the 
;;; list of layers.  The normalization factor is given by
;;; icon-editor-normalized-scale-factor.

(defun convert-line-drawing-description-to-list-of-layers 
       (line-drawing-description x-scale y-scale)
  (let* ((list-of-layers nil)
	 (tail-of-list-of-layers nil)
	 (region-and-name-alist nil)
	 (current-label (icon-editor-default-color))
	 (current-layer-elements nil)
	 (tail-of-current-layer-elements nil))
    (loop for drawing-element-or-label
	      in (if (typep (car line-drawing-description) 'fixnum)
		     (cddr line-drawing-description)
		     line-drawing-description)
	  do
      (if (symbolp drawing-element-or-label)
						; Then
	  (progn				; LABEL
	    (when current-layer-elements
		(enqueue-1
		  (make-layer
		    current-label
		    nil				; icon data of layer
		    current-layer-elements
		    tail-of-current-layer-elements)
		  list-of-layers tail-of-list-of-layers icon-editor-cons)
	      (setq current-layer-elements nil)
	      (setq tail-of-current-layer-elements nil))
	    (setq current-label drawing-element-or-label))
						; Else
	  (case (car drawing-element-or-label)	; DRAWING ELEMENT
	    (polychrome
	     (setq region-and-name-alist
		   (copy-tree-using-icon-editor-conses
		     (cdr drawing-element-or-label))))
	    ((point outline circle solid-rectangle lines
		    filled-circle filled-polygon image text ; added text (pbk 2/6/96)
		    stippled-area)
	     (enqueue-1 (copy-drawing-element-with-icon-editor-conses
                          drawing-element-or-label x-scale y-scale)
		      current-layer-elements
		      tail-of-current-layer-elements
		      icon-editor-cons))
	    (lines-old
	     ;; pbk why don't we handle this above (this is buggy)
	     ;; copy-drawing-element can handle lines better
	     (let* ((last-x-in-workspace 0)
		    (last-y-in-workspace 0)
		    (list-of-points-so-far nil)
		    (tail-of-list-of-points-so-far nil)
		    point-or-arc)
	       (declare (type fixnum last-x-in-workspace last-y-in-workspace))
	       (loop for rest-of-drawing-element on (cdr drawing-element-or-label)
		     do
		 ;; This loop breaks up a "lines" drawing element into
		 ;; <lines-arc-element> elements and <lines-element> elements.
		 (setq point-or-arc (car rest-of-drawing-element))
		 (if (eq (car point-or-arc) 'arc)
		     (progn			; ARC
		       (if (cdr list-of-points-so-far)	; if length > 1
			   (enqueue-1
			     (icon-editor-cons 'lines list-of-points-so-far)
			     current-layer-elements
			     tail-of-current-layer-elements
			     icon-editor-cons)
			   (reclaim-icon-editor-slot-value list-of-points-so-far))
		       (setq list-of-points-so-far nil)
		       (setq tail-of-list-of-points-so-far nil)
		       (let* ((point (second point-or-arc))
			      (point-for-arc
				(scaled-icon-editor-point
				  (car point) (second point) x-scale y-scale)))
			 (enqueue-1
			   (icon-editor-list
			     'lines
			     (icon-editor-list last-x-in-workspace last-y-in-workspace)
			     (icon-editor-list 'arc point-for-arc)
			     (let* ((next-point-or-arc
				      (second rest-of-drawing-element))
				    (next-x? (first next-point-or-arc))
				    (next-y? (second next-point-or-arc)))
			       (scaled-icon-editor-point
				 (if (typep next-x? 'fixnum) next-x? 0)
				 (if (typep next-y? 'fixnum) next-y? 0)
				 x-scale y-scale)))
			   current-layer-elements tail-of-current-layer-elements icon-editor-cons)
			 (setq last-x-in-workspace (first point-for-arc))
			 (setq last-y-in-workspace (second point-for-arc))))
		     (let* ((scaled-point	; POINT
			      (scaled-icon-editor-point
				(car point-or-arc) (second point-or-arc)
				x-scale y-scale)))
		       (setq last-x-in-workspace (first scaled-point))
		       (setq last-y-in-workspace (second scaled-point))
		       (enqueue-1
			 scaled-point list-of-points-so-far
			 tail-of-list-of-points-so-far icon-editor-cons)))
		     finally
		       (if (cdr list-of-points-so-far)	; if length > 1
			   (enqueue-1
			     (icon-editor-cons 'lines list-of-points-so-far)
			     current-layer-elements
			     tail-of-current-layer-elements
			     icon-editor-cons)
			   (reclaim-icon-editor-slot-value list-of-points-so-far)))))))
	  finally
	    (if current-layer-elements
		(enqueue-1
		  (make-layer
		    current-label
		    nil				; icon data of layer
		    current-layer-elements
		    tail-of-current-layer-elements)
		  list-of-layers tail-of-list-of-layers icon-editor-cons)))
    (values list-of-layers region-and-name-alist)))


;;; `add-variable-spec-list-to-line-drawing-description'
;;;  Needed to draw icons when using foo-coordinates
;;;  Modifies the given line-drawing-description, unless
;;;  the spec-list needed to be placed on the front of the list
;;;  in which case it returns nil.

(defun add-variable-spec-list-to-line-drawing-description
    (description-without-size-and-variables variable-spec-list)
  (loop initially
	  (when  (eq (car (car description-without-size-and-variables)) 'polychrome)
	    (slot-value-push
	      (copy-for-slot-value variable-spec-list)
	      (cdr description-without-size-and-variables))
	    (return t))
	for rest-line-drawing-description on description-without-size-and-variables
	as front-element = (car rest-line-drawing-description)
	thereis
	(when (and (consp front-element)(eq (car front-element) 'polychrome))
	  (slot-value-push
	    (copy-for-slot-value variable-spec-list)
	    (cdr rest-line-drawing-description))
	  (return t))
	finally
	  (return nil)))

(defun add-background-layer-to-line-drawing-description
    (description-without-size-and-variables background-layer-info)
  (loop initially
	  (when  (eq (car (car description-without-size-and-variables)) 'polychrome)
	    (slot-value-push
	      background-layer-info
	      (cdr description-without-size-and-variables))
	    (return t))
	for rest-line-drawing-description on description-without-size-and-variables
	as front-element = (car rest-line-drawing-description)
	thereis
	(when (and (consp front-element) (eq (car front-element) 'polychrome))
	  (slot-value-push
	    background-layer-info
	    (cdr rest-line-drawing-description))
	  (return t))
	finally
	  (return nil)))

  
;;; The function `convert-list-of-layers-to-line-drawing-description'
;;; returns a slot-value tree which corresponds to a line drawing
;;; description.  The x-scale and y-scale values are the scale of the
;;; target icon description with respect to the original icon description.
;;; Eval-power-points-p returns a line-drawing-description that has values
;;; in the places of any variables by looking the variable up in the
;;; variable-spec-list. Places a copy of variable-spec-list into the
;;; line-drawing-description it creates.

(defun convert-list-of-layers-to-line-drawing-description
    (list-of-layers region-and-name-alist variable-spec-list background-layer 
		    scaled-icon-width scaled-icon-height x-scale y-scale
		    omit-size-p eval-power-points-p stipple-spec)
  (declare (type fixnum x-scale y-scale))
  (let* ((line-drawing-description nil)
	 (tail-of-line-drawing-description nil)
	 (filtered-alist nil)
	 (tail-of-filtered-alist? nil)
	 background-layer-info
	 (icon-width (inverse-scalef x-scale scaled-icon-width))
	 (icon-height (inverse-scalef y-scale scaled-icon-height))
	 (stipple-header?
	   (if (stipple-p stipple-spec)
	       (slot-value-list 'stipple stipple-spec))))	       
    (loop with drawing-elements-of-layer
	  with current-label and color?
	  for current-layer in list-of-layers
	  do
      (setq current-label (label-of-layer current-layer))
      (setq color?
	    (if (eq current-label 'foreground)
		'foreground
		(cdr (assq current-label region-and-name-alist))))
      (setq drawing-elements-of-layer
	    (copy-list-using-gensym-conses
	      (drawing-elements-of-layer current-layer)))
      (when drawing-elements-of-layer					 

	;; Put the stippled-area element(s) first.  The element is not
	;; absolutely required up front, but it makes most sense, since it's
	;; almost a part of the layer region or color. By the way, only one such
	;; element per layer is supported, but additional elements are tolerated
	;; (but may not do what anyone expects).
	(setq drawing-elements-of-layer
	      (partially-sort-drawing-elements-stippled-areas-first
		drawing-elements-of-layer))
	
	(when (not (assq current-label filtered-alist))
	  ;; colors go in front, regions go behind
 	  (cond
	    ((color-or-metacolor-p current-label)
	     (slot-value-push
	       (slot-value-cons current-label
				(or color? current-label))
	       filtered-alist)
	     (if (null tail-of-filtered-alist?)
		 (setq tail-of-filtered-alist? filtered-alist)))
	    (t
	     (enqueue-1 (slot-value-cons current-label
				       (or color? current-label))
		      filtered-alist
		      tail-of-filtered-alist?
		      slot-value-cons))))
	(enqueue-1 (label-of-layer current-layer)
		 line-drawing-description
		 tail-of-line-drawing-description
		 slot-value-cons)
	(loop for drawing-element in drawing-elements-of-layer
	      do
	  (enqueue-1
	    (evaluating-icon-elements
		(icon-width
		 icon-height
		 (cdr variable-spec-list)
		 nil)
	      (copy-drawing-element-with-slot-value-conses
		drawing-element x-scale y-scale eval-power-points-p))
	    line-drawing-description
	    tail-of-line-drawing-description
	    slot-value-cons))
	(reclaim-gensym-list drawing-elements-of-layer)))
    (when stipple-header?
      (slot-value-push stipple-header? line-drawing-description))
    (let* ((description-without-size
	     (if (and (eq (car line-drawing-description) 'foreground)
		      (or (null region-and-name-alist)
			  (and (null (cdr filtered-alist))	;length = 1
			       (eq (car (car filtered-alist))
				   'foreground))))
		 (prog1
		     (cdr line-drawing-description)
		   (reclaim-slot-value-cons line-drawing-description)
		   (reclaim-slot-value-tree filtered-alist))
		 ;; See Note.
		 (slot-value-cons
		   (slot-value-cons 'polychrome filtered-alist)
		   line-drawing-description))))
      (setf background-layer-info
	(copy-for-slot-value background-layer))
      (setf background-layer-info
	(if background-layer-info
	    (slot-value-list 'background-layer
			     background-layer-info)
	    (slot-value-list 'background-layer)))
	  
       (or (add-background-layer-to-line-drawing-description
	    description-without-size
	    background-layer-info)
	   (slot-value-push
	     background-layer-info
	     description-without-size))
       (or
	(add-variable-spec-list-to-line-drawing-description
	  description-without-size
	  variable-spec-list)
	(slot-value-push (copy-for-slot-value variable-spec-list)
			 description-without-size))       
     
      (if omit-size-p
	  description-without-size
	  (slot-value-cons
	    scaled-icon-width
	    (slot-value-cons
	      scaled-icon-height
	      description-without-size))))))

;; Note: There may be a bug here: if filtered-alist is NIL, we create a polychrome
;; header which looks like just (POLYCHROME).  This note was in entities:
;;   If polychrome-header?  is non-nil, polychrome-header-rest?  should be
;;   non-nil as well.  This is currently not always the case due to a bug in the
;;   icon editor (see note to Peng).  - agh, 7/5/90.
;; -fmw, 2/17/95



;;; Partially-sort-drawing-elements-stippled-areas-first takes a list of drawing
;;; elements and moves conses around so that elements that are conses of the
;;; form
;;;
;;;    (STIPPLED-AREA ...)
;;;
;;; come first.  This mutates the list, but the result must be set into the
;;; variable holding the result, in case the result has a different first cons
;;; cell.
;;;
;;; This is intended only to be used as a subfunction of
;;; convert-list-of-layers-to-line-drawing-description.

(defun partially-sort-drawing-elements-stippled-areas-first (drawing-elements)  
  ;; Partially sort drawing elements so that stippled area(s) come first:
  (loop with removed = nil
	while (loop as prev-elts = nil then elts
		    for elts on drawing-elements
		    as element = (car elts)
		    when (and (consp element)
			      (eq (car element) 'stippled-area))
		      do (setq removed (nconc removed elts))
			 (if prev-elts
			     (setf (cdr prev-elts) (cdr elts))
			     (setf drawing-elements (cdr elts)))
			 (setf (cdr elts) nil)
			 (return t))
	finally
	  (return (nconc removed drawing-elements))))









;;; The function `convert-to-filled-drawing-elements' takes a list of
;;; drawing elements and returns a similar list of line drawing elements
;;; with all outlined drawing elements converted to filled drawing
;;; elements where possible.  The function
;;; `convert-to-outlined-drawing-elements' does the opposite.  The
;;; drawing elements given to these functions are not consumed, and
;;; the returned drawing elements are formed with icon-editor conses.
;;; If no convertion is required, nil is returned.

(defun-substitution-macro necessary-to-convert-to-filled-drawing-elements-p
			  (outlined-drawing-elements)
  (loop for drawing-element in outlined-drawing-elements
	thereis (memq (car drawing-element) '(outline circle))))

(defun-substitution-macro convert-to-filled-drawing-element
			  (outlined-drawing-element)
  (case (car outlined-drawing-element)
    ((point lines solid-rectangle filled-polygon filled-circle image)
     (copy-tree-using-icon-editor-conses outlined-drawing-element))
    (text       ; added text (pbk 2/6/96) should use copy-tree-including-leav..
     (copy-drawing-element-with-icon-editor-conses
       outlined-drawing-element nil nil))
    (stippled-area
     (copy-drawing-element-with-icon-editor-conses
       outlined-drawing-element nil nil))
    (texttured-area
     (copy-drawing-element-with-icon-editor-conses
       outlined-drawing-element nil nil))
    (outline
     ;;
     ;; We could also check for the outline of a rectangle
     ;; and use 'solid-rectangle when applicable.  -pto 17oct89
     ;;
     (let* ((list-of-points
	      (copy-tree-using-icon-editor-conses
		(cdr outlined-drawing-element)))
	    decomposed-polygon?)

       (unless (clockwise-polygon-p list-of-points)
	 (setq list-of-points (nreverse list-of-points)))

       (cond
	 ((and (cddr outlined-drawing-element)	; length > 2
	       (setq decomposed-polygon?
		     (decompose-polygon-using-icon-editor-conses
		       list-of-points)))
	  (icon-editor-cons
	    'filled-polygon
	    (icon-editor-cons list-of-points decomposed-polygon?)))
	 (t
	  (icon-editor-cons (car outlined-drawing-element) list-of-points)))))
    (circle
     (setf (car outlined-drawing-element) 'filled-circle)
     (prog1
       (copy-tree-using-icon-editor-conses outlined-drawing-element)
       (setf (car outlined-drawing-element) 'circle)))))

;; Note: consider eliminating the first (point, et al), second (text), and third
;; (stippled-area) case clauses above, and having them simply fall through to an
;; otherwise case that does a general tree and leaf copy (as done now only for
;; TEXT). There's no good reason to narrowly specify every type of drawing
;; element, and this will avoid having to visit this code and/or have bugs
;; likeHQ-4712531 "Filling an icon region with Stipple pattern aborts G2" next
;; time a new tyep of drawing element is added. Same with
;; convert-to-outlined-drawing-element!  Leaving as is for now to minimize
;; changes for the upcoming revision (8.0r1). (MHD 7/14/04)





;;; The function/macro `necessary-to-convert-to-outlined-drawing-elements-p'
;;; decides if there are any filled drawing elements in the list it is givened.

(defun-substitution-macro necessary-to-convert-to-outlined-drawing-elements-p
			  (filled-drawing-elements)
  (loop for drawing-element in filled-drawing-elements
	thereis (memq (car drawing-element)
		      '(solid-rectangle filled-polygon filled-circle))))

(defun-substitution-macro convert-to-outlined-drawing-element
			  (filled-drawing-element)
  (case (car filled-drawing-element)
    ((point lines outline circle image)
     (copy-tree-using-icon-editor-conses filled-drawing-element))
    (text   ; added text (pbk 2/6/96) should use copy-tree-including-leaves...
     (copy-drawing-element-with-icon-editor-conses
       filled-drawing-element nil nil))
    (stippled-area
     (copy-drawing-element-with-icon-editor-conses
       filled-drawing-element nil nil))
    (solid-rectangle
     (let* ((point-1 (second filled-drawing-element))
	    (point-2 (third filled-drawing-element))
	    (x0 (first point-1))
	    (y0 (second point-1))
	    (x1 (first point-2))
	    (y1 (second point-2)))
       (macrolet ((point-list (x y)
		    `(icon-editor-list
		       (copy-tree-using-icon-editor-conses ,x)
		       (copy-tree-using-icon-editor-conses ,y))))
	 (icon-editor-list
	   'outline
	   (point-list x0 y0) (point-list x0 y1)
	   (point-list x1 y1) (point-list x1 y0)))))
    (filled-polygon
     (icon-editor-cons
       'outline
       (copy-tree-using-icon-editor-conses
	 (second filled-drawing-element))))
    (filled-circle
     (setf (car filled-drawing-element) 'circle)
     (prog1
       (copy-tree-using-icon-editor-conses filled-drawing-element)
       (setf (car filled-drawing-element) 'filled-circle)))))


(defun convert-to-filled-drawing-elements (outlined-drawing-elements)
  (if (necessary-to-convert-to-filled-drawing-elements-p
	outlined-drawing-elements)
      (loop with filled-drawing-elements = nil
	    with tail-of-filled-drawing-elements = nil
	    for drawing-element in outlined-drawing-elements
	    do
	(enqueue-1
	  (convert-to-filled-drawing-element drawing-element)
	  filled-drawing-elements
	  tail-of-filled-drawing-elements
	  icon-editor-cons)
	    finally
	      (return filled-drawing-elements))))


(defun convert-to-outlined-drawing-elements (filled-drawing-elements)
  (if (necessary-to-convert-to-outlined-drawing-elements-p
	filled-drawing-elements)
      (loop with outlined-drawing-elements = nil
	    with tail-of-outlined-drawing-elements = nil
	    for drawing-element in filled-drawing-elements
	    do
	(enqueue-1
	  (convert-to-outlined-drawing-element drawing-element)
	  outlined-drawing-elements
	  tail-of-outlined-drawing-elements
	  icon-editor-cons)
	    finally
	      (return outlined-drawing-elements))))



;;; `convert-infix-to-prefix'
;;; TAKES FLAT LISTS ONLY
;;; Returns a NEW list. Does NOT destroy or reclaim the argument.

(defun convert-infix-to-prefix (infix-variables)
  (loop with initial-minus-p = nil
	with result = (cond ((null (second infix-variables))
			     (car infix-variables))
			    ((null (third infix-variables))
			     (copy-for-slot-value infix-variables))
			    ((eq (second infix-variables) '-)
			     (slot-value-list '+ (car infix-variables)
					      (slot-value-list
						'-
						(third infix-variables))))
			    ((and (eq (car infix-variables) '-)
				  (eq (third infix-variables) '+))
			      (setf initial-minus-p t)
			     (slot-value-list '+
					      (slot-value-list
						'-
						(second infix-variables))
					      (fourth infix-variables)))
			    ((eq (car infix-variables) '-)
			     (setf initial-minus-p t)
			     (slot-value-list '+
					      (slot-value-list
						'-
						(second infix-variables))
					      (slot-value-list
						'-
						(fourth infix-variables))))
			    (t
			     (slot-value-list (second infix-variables)
					      (car infix-variables)
					      (third infix-variables))))
	with rest-variables = (cond (initial-minus-p
				     (cddddr infix-variables))
				    (t (cdddr infix-variables)))
	for (operation variable) on rest-variables by 'cddr
	do
    (cond ((eq operation '+)
	   (setf result (slot-value-list '+ result variable)))
	  ((eq operation '-)
	   (setf result (slot-value-list '+ result (slot-value-list '- variable)))))
	finally
	  (return result)))
	
(defun simplify-point-expression (point-expression)
  (let* ((resolved-constants (resolve-constants point-expression))
	 (infix-variables (extract-constants point-expression))
	 (prefix-variables (convert-infix-to-prefix infix-variables)))
    (reclaim-slot-value infix-variables)
    (cond ((and prefix-variables (not (eq resolved-constants 0)))
	   (slot-value-list '+ prefix-variables resolved-constants))
	  (prefix-variables prefix-variables)
	  (t resolved-constants))))
	   
(defun incff-power-point (power-point x-offset y-offset)
  (let ((point-x (car power-point))
	(point-y (second power-point)))
    (cond ((or (symbolp point-x) (consp point-x))
	   (setf (first power-point)
		 (simplify-point-expression
		   (slot-value-list '+
				    point-x
				    x-offset)))
	   (reclaim-slot-value point-x))
	  (t (incff (car power-point) x-offset)))
    (cond ((or (symbolp point-y)
	       (consp point-y))
	   (setf (second power-point)
		 (simplify-point-expression
		   (slot-value-list '+
				    point-y
				    y-offset)))
	   (reclaim-slot-value point-y))
	  (t (incff (second power-point) y-offset)))))
  

;;; The function `shift-points-in-place' bumps the x,y coordinates for each
;;; point in the list.

(defun shift-points-in-place (list-of-points x-offset y-offset)
  (loop for point-or-arc in list-of-points
	do
    (cond
      ((arc-point-p point-or-arc)
       (shift-points-in-place (cdr point-or-arc) x-offset y-offset))
      ((power-point-p point-or-arc)
       (incff-power-point point-or-arc x-offset y-offset))
      ((constant-point-p point-or-arc)
       (setf (first point-or-arc) (+w (first point-or-arc) x-offset))
       (setf (second point-or-arc) (+w (second point-or-arc) y-offset)))))

  #+development
  list-of-points)


;;; The function `shift-drawing-elements-in-place' shifts all the drawing
;;; elements by the specified offsets, and it does this in place.  It's used at
;;; the end of move-layer-in-xy-plane handler.

(defun shift-drawing-elements-in-place (list-of-drawing-elements
					 x-offset y-offset)
  (loop for drawing-element in list-of-drawing-elements
	do
    (case (car drawing-element)
      ((point lines outline circle solid-rectangle filled-circle)
       (shift-points-in-place (cdr drawing-element) x-offset y-offset))

      (image						    ; (image name &optional (x y))
       (let ((point? (third drawing-element)))
	 (cond ((null point?)
		(setq drawing-element (nconc drawing-element
					     (icon-editor-list
					       (icon-editor-list x-offset y-offset)))))
	       ((power-point-p point?)
		(incff-power-point point? x-offset y-offset))
	       ((constant-point-p point?)
		(incff (first point?) x-offset)
		(incff (second point?) y-offset)))))
      (text       ; added-text (pbk 2/6/96)    ; (text <whole-string> <point> <font-spec>)
       (let ((point (third drawing-element)))
	 (cond ((power-point-p point)
		(incff-power-point point x-offset y-offset))
	       (t
		(incff (first point) x-offset)
		(incff (second point) y-offset)))))

      (filled-polygon
       (shift-points-in-place (second drawing-element) x-offset y-offset)
       (loop for triangle in (cddr drawing-element)
	     do
	 (shift-points-in-place triangle x-offset y-offset)))))

  #+development
  list-of-drawing-elements)





;;;; Operations on Current Layer



;; The functionality to create-new-current-layer and delete-current-layer
;; are provided by new-icon-layer and delete-specific-layer in ICONS2

;;; The function/macro `add-element-to-current-layer' adds a new element to the
;;; current layer (as specified by the engine).  The argument
;;; new-drawing-element should be an icon-editor tree, and is consumed by this
;;; function/macro.

(defun-substitution-macro add-element-to-current-layer
			  (icon-editor-engine new-drawing-element)
  (let* ((layer
	   (icon-editor-engine-current-layer icon-editor-engine))
	 (drawing-elements (drawing-elements-of-layer layer)))
    (reclaim-icon-editor-slot-value
      (layer-box-of-layer layer))
    (setf (layer-box-of-layer layer) nil)
    (enqueue-1
      new-drawing-element
      drawing-elements                       ; head
      (drawing-elements-tail-of-layer layer) ; tail
      icon-editor-cons)
    ;; update queue head after `enqueue'
    (setf (drawing-elements-of-layer layer) drawing-elements)
    layer))

;;; The function `delete-last-element-from-current-layer' and
;;; `delete-first-element-from-current-layer' operate on the current
;;; layer as specified by the icon editor engine they are handed.

(defun-substitution-macro delete-last-element-from-current-layer
			  (icon-editor-engine)
  (let* ((layer
	   (icon-editor-engine-current-layer icon-editor-engine))
	 (drawing-elements (drawing-elements-of-layer layer)))
    (if (null (cdr drawing-elements))		; if only one element exists
	(progn
	  (setf (drawing-elements-of-layer layer) nil)
	  (setf (drawing-elements-tail-of-layer layer) nil))
	(loop for rest-of-elements on drawing-elements
	      do
	  (if (null (cddr rest-of-elements))
	      (progn
		(reclaim-icon-editor-slot-value (cdr rest-of-elements))
		(setf (cdr rest-of-elements) nil)
		(setf (drawing-elements-tail-of-layer layer)
		      rest-of-elements)
		(return)))))))

(defun-substitution-macro delete-first-element-from-current-layer
			  (icon-editor-engine)
  (let* ((layer
	   (icon-editor-engine-current-layer icon-editor-engine))
	 (first-element
	   (dequeue (drawing-elements-of-layer layer)
		    (drawing-elements-tail-of-layer layer)
		    reclaim-icon-editor-cons)))
    (reclaim-icon-editor-slot-value first-element)))

;;; The function/macro `change-label-of-current-layer' is just a setf of the
;;; label of the current layer in the icon editor engine.

(defun-substitution-macro change-label-of-current-layer
			  (icon-editor-engine new-label)
  (setf (label-of-layer (icon-editor-engine-current-layer icon-editor-engine))
	new-label))




;;; The defun-substitution-macro `change-image-of-current-layer' sets the IMAGE
;;; clause for the current layer.  The image clause is deleted if the new image
;;; is nil, and one is created if the old image is nil.  Returns non-nil iff we
;;; changed something.

(defun-substitution-macro change-image-of-current-layer (icon-editor-engine new-image)
  (let* ((layer (icon-editor-engine-current-layer icon-editor-engine))
	 (old-image-place (loop for sublist on (drawing-elements-of-layer layer)
				when (image-drawing-element-p (car sublist))
				  return sublist))
	 (old-image (car old-image-place)))
    
    (cond ((equal old-image new-image)
	   nil)
	  ((null old-image)
	   (add-element-to-current-layer icon-editor-engine
					 (copy-tree-using-icon-editor-conses new-image))
	   t)
	  (new-image
	   (setf (car old-image-place) (copy-tree-using-icon-editor-conses new-image)))
	  (t
	   (setf (drawing-elements-of-layer layer)
		 (delete-icon-editor-element old-image (drawing-elements-of-layer layer)))
	   (setf (drawing-elements-tail-of-layer layer)
		 (last (drawing-elements-of-layer layer)))
	   t))))


;;; The defun-substitution-macro `change-text-of-current-layer' changes the first
;;; text-drawing-element within the current layer of the icon-editor-engine.
;;; The (icon-editor-engine-text? of the engine is NOT changed here, but rather
;;; in 'set-text-in-icon-editor, which is the caller of this function.
;;; The function first makes a copy of the new-text before setting it in place.
;;; This function reclaims the old-text. It does NOT reclaim the new-text argument
;;; It returns true if anything changed.  (pbk 2/6/96)

(defun-substitution-macro change-text-of-current-layer (icon-editor-engine new-text)
  (let* ((layer (icon-editor-engine-current-layer icon-editor-engine))
	 (old-text-place (loop for sublist on (drawing-elements-of-layer layer)
				when (text-drawing-element-p (car sublist))
				  return sublist))
	 (old-text (car old-text-place)))
    (cond ((equal old-text new-text)
	   nil)
	  ((null old-text)
	   (add-element-to-current-layer
	     icon-editor-engine
	     (copy-drawing-element-with-icon-editor-conses new-text nil nil))
	   t)
	  (new-text
	   (setf (car old-text-place)
		 (copy-drawing-element-with-icon-editor-conses new-text nil nil))
	   (reclaim-icon-editor-slot-value old-text)
	   t) 
	  (t
	   ;(format t "doing last change-text-of-current-layer case~%") ;pbk temp
	   (setf (drawing-elements-of-layer layer)
		 (delete-icon-editor-element old-text (drawing-elements-of-layer layer)))
	   (setf (drawing-elements-tail-of-layer layer)
		 (last (drawing-elements-of-layer layer)))
	   t))))


(defun change-stipple-of-current-layer (icon-editor-engine new-stipple)
  (let* ((layer (icon-editor-engine-current-layer icon-editor-engine))
	 (old-stipple-place (loop for sublist on (drawing-elements-of-layer layer)
				when (stipple-drawing-element-p (car sublist))
				  return sublist))
	 (old-stipple (car old-stipple-place)))
    (cond ((equal old-stipple new-stipple)
	   nil)
	  ((null old-stipple)
	   (add-element-to-current-layer
	     icon-editor-engine
	     (copy-drawing-element-with-icon-editor-conses new-stipple nil nil))
	   t)
	  (new-stipple
	   (setf (car old-stipple-place)
		 (copy-drawing-element-with-icon-editor-conses new-stipple nil nil))
	   (reclaim-icon-editor-slot-value old-stipple)
	   t) 
	  (t
	   (setf (drawing-elements-of-layer layer)
		 (delete-icon-editor-element old-stipple (drawing-elements-of-layer layer)))
	   (setf (drawing-elements-tail-of-layer layer)
		 (last (drawing-elements-of-layer layer)))
	   t))))


 

;;; The defun-for-macro `create-icon-editor-buttons-specification-list' is
;;; needed for defining the constant icon-editor-buttons-specification-list.

#-no-macros
(defun-for-macro create-icon-editor-buttons-specification-list
    (unprocessed-list)
  (let* ((new-list nil))
    (loop for element in unprocessed-list
	  do
      (when (stringp (second element))
	(register-symbol-corresponding-to-string-for-button-internationalization
	  (second element)))
      (push `(,(icon-editor-translator-event-function (first element))
	      ,(if (symbolp (second element)) (second element) (stringw (second element)))
	       ,@(cddr element))
	      new-list))
      (nreverse new-list)))

(defun register-symbol-corresponding-to-string-for-button-internationalization (string)
  (let ((symbol (intern (string-upcase string))))
    (register-button-label-for-internationalization symbol)))



;;;; Old enhancement notes



;; Notes:
;; Possible Future Additions:
;;
;;  1. Allow clipped line drawing elements - fix up icon drawing routines.
;;  2. Control over thickness of lines being drawn.
;;  3. Snap-to grid points and an on/off switch for it.
;;  4. Undo
;;  5. Redo
;;  6. Outlined and filled shapes
;;  7. Grids on/off switch, and on view pad
;;  8. Insert layer button
;;  9. Duplicate/clone layer and/or drawing element
;; 10. Fill/unfill all line drawing elements of layer
;; 11. Shrink wrap button
;; 12. View pad x2, x5, x10 buttons (or slider scaling)
;; 13. Display for scale of view pad and for scale of layers pad.
;; 14. Get rid of the y-midpoint; this is redundant info.  Use top-edge of
;;     block instead.
;; 15. Feature to move layer in x-y plane.
;; 16. Edit drawing element feature; perhaps using pick algorithm for elements.
;; 17. Reexamine ungroup policy for points and non-points drawing elements.
;; 18. Confirmation upon "cancel".
;; 19. Rotate and reflect.
;; 20. Constraint drawing.  (Eg. constrain line to a particular angle or length.)
;; 21. Double clicks - for example to end line drawing elements.
;; 22. Highlight button of drawing element when active.
;; 23. Readout to tell user which object definition is being edited.
;; 24. Reexamine consistency of font usage.
;; 25. Consider changing the way repositioning of layers are done
;; 26. Draw circles from bounding rectangles should be possible, as well as
;;     drawing from center to circumference.
;; 27. Consider drawing rectangles from centroid to one of its corners.
;; 28.xButtons should highlight when clicked.
;; 29.xButtons take effect whether the mouse-up occurs in or out of the button.
;;     Reconsider this.
;; 30. Consider changing all buttons to square buttons.
;; 31. Turn mouse tracking off while not in view pad; or have switch to
;;     turn it off; or track only in a draw mode.


;; Improvements to Icons
;;
;;  1. Text elements in icon description
;;  2. Stipple elements in icon description

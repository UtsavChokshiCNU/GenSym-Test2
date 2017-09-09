;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module ICONS5 -- Icon Editor Initialization and Exit Code

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Ong, Peng Tsin




#+development
(declare-forward-reference check-memory function checkmemory)

;;;; Initialization Code





;;; The function `get-inherited-drawing-description', when the object definition
;;; has a class inheritance path, returns a copy, using icon-editor-conses, of
;;; the tree that would appear as the icon-description-for-class? slot of the
;;; most-specific superior that defines an icon-description; otherwise it
;;; returns nil.

(defun get-inherited-drawing-description (class-definition)
  (let* ((class-inheritance-path?
	   (class-inheritance-path-of-definition class-definition))
	 (superior-icon-description?
	   (when class-inheritance-path?
	     (loop for superior in (cdr class-inheritance-path?)
		   for superior-class-description = (class-description superior)
		   when (class-overrides-slot-p ;class-has-override-on-slot-p
			  superior 'icon-description)
		     return (slot-init-form
			      (get-slot-description-of-class-description
				'icon-description superior-class-description))))))
    (when superior-icon-description?
      (icon-editor-cons
	(width-of-icon superior-icon-description?)
	(icon-editor-cons
	  (height-of-icon superior-icon-description?)
	  (copy-tree-including-leaves-using-icon-editor-conses ; pbk
	    (icon-line-drawing-description
	      superior-icon-description?))))))) 

(defun get-inherited-background-image (class-definition)
  (let* ((class-inheritance-path?
	   (class-inheritance-path-of-definition class-definition))
	 (superior-background-image?
	   (when class-inheritance-path?
	     (loop for superior in (cdr class-inheritance-path?)
		   when (and (user-defined-class-p superior)
			     (class-overrides-slot-p ;class-has-override-on-slot-p
			       superior 'icon-background-images))
		     return
		     (icon-background-images
		       (class-definition superior))))))
    (when superior-background-image?
      (copy-tree-including-leaves-using-icon-editor-conses ; pbk
	superior-background-image?))))




(defun-substitution-macro install-icon-editor (class-definition)
  #+development (gensym-assert
		  (class-definition-defines-user-editable-icon-class-p
		    class-definition))
  (let* ((icon-editor (create-icon-editor class-definition))
	 (drawing-description?
	   (icon-description-for-class? class-definition))
	 (inherited-drawing-description?
	   (if (null drawing-description?)
	       (get-inherited-drawing-description class-definition)))
	 (engine (icon-editor-engine icon-editor))
	 (view-pad (icon-editor-view-pad icon-editor)))
    (setf (icon-editor-table-info-frame-icon-editor
	    (icon-editor-table-info-frame
	      (icon-editor-label-table icon-editor)))
	  icon-editor)
    (when (null drawing-description?)
      (setq drawing-description? inherited-drawing-description?))
    (if drawing-description?
	(let* ((icon-width (first drawing-description?))
	       (icon-height (second drawing-description?))
	       (variable-spec-list
		 (or (get-variable-specification-if-any drawing-description?)
		     (icon-editor-list 'variables)))
	       (icon-background-layer?
		 (or (icon-background-images class-definition)
		     (get-inherited-background-image class-definition)))
	       (icon-stipple?
		 (get-icon-stipple-if-any drawing-description?)))
		 
	  (multiple-value-bind (layers alist)
	      (convert-line-drawing-description-to-list-of-layers
		drawing-description?
		(icon-editor-normalized-scale-factor)
		(icon-editor-normalized-scale-factor))
	    (setf (icon-editor-engine-layers engine)
		  layers)
	    (setf (icon-editor-region-and-name-alist icon-editor)
		  alist)
	    (setf (icon-editor-variable-spec-list icon-editor)
		  (copy-tree-including-leaves-using-icon-editor-conses variable-spec-list))
	    (setf (icon-editor-icon-background-image icon-editor)
		  (copy-tree-including-leaves-using-icon-editor-conses
		    icon-background-layer?))
	    (setf (icon-editor-engine-layers-tail engine)
		  (last layers))
	    (setf (icon-editor-engine-current-layer engine)
		  (car (icon-editor-engine-layers-tail engine)))
	    (setf (icon-editor-engine-current-layer-index engine)
		  (if layers (-f (length layers) 1) 0))
	    (setf (icon-editor-engine-number-of-layers engine)
		  (length layers))
	    (setf (icon-editor-engine-width-extent engine)
		  icon-width)
	    (setf (icon-editor-engine-height-extent engine)
		  icon-height)
	    (setf (icon-editor-engine-icon-width engine) icon-width)
	    (setf (icon-editor-engine-icon-height engine) icon-height)
	    (setf (icon-editor-engine-global-stipple? engine) icon-stipple?)
	    (setf (icon-editor-view-pad-iconic-entity view-pad) nil)
	    #+development (gensym-assert (>=f (icon-editor-engine-current-layer-index engine)
					      0))

	    (when (null layers)
	      (new-icon-layer (icon-editor-engine-main-color engine) nil 0 engine)
	      (setq layers (icon-editor-engine-layers engine))
	      (setq alist (icon-editor-region-and-name-alist icon-editor)))
	    ;; Draw icon for view pad here.  ABSTRACT!!
	    (enqueue-icon-editor-visual-event
	      icon-editor
	      (icon-editor-visual-event 'redraw-view-pad-icon)
	      nil nil)
	    (let* ((current-label (label-of-layer (icon-editor-engine-current-layer engine)))
		   (current-image (image-of-layer? (icon-editor-engine-current-layer engine)))
		   (current-text (text-of-layer? (icon-editor-engine-current-layer engine)))
		   (current-stipple (stipple-of-layer? (icon-editor-engine-current-layer engine))))
	      (enqueue-icon-editor-engine-event
		icon-editor
		(icon-editor-engine-event 'update-main-label)
		current-label 
		current-image
		current-text   ;pbk
		current-stipple))
	    (when alist
	      (inform-user-of-current-regions icon-editor))))

	;; ELSE:  No icon description specified.
	(progn
	  (setf (icon-editor-engine-width-extent engine)
		(default-width-of-icon))
	  (setf (icon-editor-engine-height-extent engine)
		(default-height-of-icon))
	  (setf (icon-editor-engine-icon-width engine) (default-width-of-icon))
	  (setf (icon-editor-engine-icon-height engine) (default-height-of-icon))
	  (setf (icon-editor-engine-global-stipple? engine) nil)
	  (setf (icon-editor-variable-spec-list icon-editor)
		(icon-editor-list 'variables))
	  (new-icon-layer (icon-editor-engine-main-color engine) nil 0 engine)))
    (when nil; inherited-drawing-description?
      (reclaim-icon-editor-slot-value inherited-drawing-description?))

    ;; set up global stipple:
    (enqueue-icon-editor-visual-event
      icon-editor
      (icon-editor-visual-event 'change-global-stipple)
      (icon-editor-engine-global-stipple? engine)
      nil)
    
    ;; Draw layers for layers pad.
    (recompute-scale-for-layers-pad icon-editor)
    (enqueue-icon-editor-visual-event
      icon-editor
      (icon-editor-visual-event 'redraw-layers-in-layers-pad)
      nil nil)
    (recompute-view-pad-size icon-editor)
    (enqueue-icon-editor-translator-event
      icon-editor
      (icon-editor-translator-event 'change-icon-size-from-engine)
      (icon-editor-engine-width-extent engine)
      (icon-editor-engine-height-extent engine))
    icon-editor))











;;;; Bounding Box Contexts  --  For the Icon Editor


;;; `Bounding-box state' is used in the icon editor to handle the
;;; resizing of the bounding box.

(define-workstation-context bounding-box (workstation-context-frame)
  :selection-style top-level-with-mouse-tracking-is-selection-style
  :keymap ((<mouse-motion> mouse-motion-in-bounding-box-state)
	   (<mouse-up> any-mouse-up-or-down-in-bounding-box-state)
	   (<mouse-down> any-mouse-up-or-down-in-bounding-box-state))
  :constructor (make-bounding-box-state
		 (bounding-box-state-bounding-box
		   bounding-box-state-image-plane
		   bounding-box-state-x-in-window
		   bounding-box-state-y-in-window
		   bounding-box-state-edge-or-corner?
		   bounding-box-state-x-offset-of-mouse-from-edge
		   bounding-box-state-y-offset-of-mouse-from-edge
		   bounding-box-state-update-function?
		   bounding-box-state-update-information?
		   bounding-box-state-update-information-reclaimer?
		   ))
  :state-variables (bounding-box-state-bounding-box
		     bounding-box-state-image-plane
		     bounding-box-state-x-in-window
		     bounding-box-state-y-in-window
		     bounding-box-state-edge-or-corner?
		     bounding-box-state-x-offset-of-mouse-from-edge
		     bounding-box-state-y-offset-of-mouse-from-edge
		     bounding-box-state-update-function?
		     bounding-box-state-update-information?
		     bounding-box-state-update-information-reclaimer?))

(def-structure-method valid-workstation-context-p (bounding-box-state)
  (and (funcall-superior-method bounding-box-state)
       (valid-block-in-workstation-context-p
	 (bounding-box-state-bounding-box bounding-box-state)
	 bounding-box-state)))

(def-structure-method clean-up-workstation-context (bounding-box-state)
  (when (bounding-box-state-update-information-reclaimer? bounding-box-state)
    (reclaim-slot-value-list
      (bounding-box-state-update-information? bounding-box-state)))
  (funcall-superior-method bounding-box-state))

(define-event-handler any-mouse-up-or-down-in-bounding-box-state (mouse-pointer)
  (mouse-motion-in-bounding-box-state mouse-pointer)
  (return-from-current-workstation-context 'bounding-box))

(define-event-handler mouse-motion-in-bounding-box-state
    (x-in-window
      y-in-window
      (bounding-box-state workstation-context-specifics))
  (let* ((bounding-box
	  (bounding-box-state-bounding-box bounding-box-state))
	 (bounding-box-border-width
	  (bounding-box-border-width bounding-box))
	 (twice-bounding-box-border-width
	  (twicew bounding-box-border-width))
	 (bounding-box-state-edge-or-corner?
	  (bounding-box-state-edge-or-corner? bounding-box-state))
	 (image-plane-of-bounding-box
	  (bounding-box-state-image-plane
	    bounding-box-state)))
    (with-image-plane-transform (image-plane-of-bounding-box)
      (let* ((x-in-workspace-of-bounding-box
	      (x-in-workspace x-in-window))
	     (y-in-workspace-of-bounding-box
	      (y-in-workspace y-in-window))
	     (offset-x-in-workspace
	      (-w x-in-workspace-of-bounding-box
		  (bounding-box-state-x-offset-of-mouse-from-edge
		    bounding-box-state)))
	     (offset-y-in-workspace
	      (-w y-in-workspace-of-bounding-box
		  (bounding-box-state-y-offset-of-mouse-from-edge
		    bounding-box-state)))
	     (old-right-edge
	      ;; later keep an offset based on the original offset when context
	      ;; entered -- fix all this later!
	      (-w (right-edge-of-block bounding-box)
		  bounding-box-border-width))
	     (new-right-edge?
	      (case bounding-box-state-edge-or-corner?
		((right bottom-right)
		 ;;   doesn't do optional movement keeping both sides
		 ;;   proportional for bottom-right yet!
		 (-w (maxw (+w (left-edge-of-block bounding-box)
			       twice-bounding-box-border-width)
			   offset-x-in-workspace)
		     bounding-box-border-width))
		(t nil)))
	     (old-bottom-edge
	      (-w (bottom-edge-of-block bounding-box)
		  bounding-box-border-width))
	     (new-bottom-edge?
	      (case bounding-box-state-edge-or-corner?
		((bottom bottom-right)
		 (-w (maxw (+w (top-edge-of-block bounding-box)
			       twice-bounding-box-border-width)
			   offset-y-in-workspace)
		     bounding-box-border-width))
		(t nil)))

	     ;; The following four are not needed if bottom-right-corner?
	     (old-left-edge
	      (+w (left-edge-of-block bounding-box)
		  bounding-box-border-width))
	     (new-left-edge?
	      (case bounding-box-state-edge-or-corner?
		((left left-right)
		 (+w (minw (-w (right-edge-of-block bounding-box)
			       twice-bounding-box-border-width)
			   offset-x-in-workspace)
		     bounding-box-border-width))
		(t nil)))
	     (old-top-edge
	      (+w (top-edge-of-block bounding-box)
		  bounding-box-border-width))
	     (new-top-edge?
	      (case bounding-box-state-edge-or-corner?
		((top top-right)
		 (+w (minw (-w (bottom-edge-of-block bounding-box)
			       twice-bounding-box-border-width)
			   offset-y-in-workspace)
		     bounding-box-border-width))
		(t nil))))
	(when (and new-left-edge? (=w new-left-edge? old-left-edge))
	  (setq new-left-edge? nil))
	(when (and new-top-edge? (=w new-top-edge? old-top-edge))
	  (setq new-top-edge? nil))
	(when (and new-right-edge? (=w new-right-edge? old-right-edge))
	  (setq new-right-edge? nil))
	(when (and new-bottom-edge? (=w new-bottom-edge? old-bottom-edge))
	  (setq new-bottom-edge? nil))
	(when (or new-left-edge?
		  new-top-edge?
		  new-right-edge?
		  new-bottom-edge?)
	  (update-border-of-bounding-box
	    bounding-box 
	    new-left-edge?
	    new-top-edge?
	    new-right-edge?
	    new-bottom-edge?)
	  (let* ((bounding-box-state-update-function?
		  (bounding-box-state-update-function?
		    bounding-box-state)))
	    (when bounding-box-state-update-function?
	      (funcall
		bounding-box-state-update-function?
		x-in-workspace-of-bounding-box
		y-in-workspace-of-bounding-box
		(bounding-box-state-update-information?
		  bounding-box-state)))))))))



;;;; Workstation Context Operation Handling for the Icon Editor



;;; The function `enter-icon-editor' create an icon-editor instance and sets up
;;; an icon editor workspace, with all the pads in place.  The following
;;; dynamic state is required: for-workstation, current-workstation-detail-pane.

(defun enter-icon-editor (class-definition)
  #+development (gensym-assert
		  (class-definition-defines-user-editable-icon-class-p
		    class-definition))
  (let* ((icon-editor (install-icon-editor class-definition))
	 (workspace (icon-editor-workspace icon-editor)))
    (when new-g2-classic-ui-p
      (change-slot-value
	workspace 'workspace-background-color?
	(get-ui-parameter 'system-workspace-background-color)))
    (put-workspace-on-pane
      workspace current-workstation-detail-pane 'left 'top nil)
    (enter-context-in-current-workstation
      'icon-editor icon-editor)))




;;; The macro `in-icon-editor-context' is a wrapper which binds the following
;;; special variables: current-icon-editor-event, current-icon-editor,
;;; current-icon-editor-workspace, current-image-plane?,
;;; current-workspace-on-image-plane?

(defvar current-icon-editor-event)
(defvar current-icon-editor)
(defvar current-icon-editor-workspace)
(defvar current-image-plane?)
(defvar current-workspace-on-image-plane?)

(defmacro in-icon-editor-context ((workstation-event) &body body)
  `(let* ((current-icon-editor-event ,workstation-event)
	  (current-icon-editor 
	    specific-structure-for-current-workstation-context)
	  (current-icon-editor-workspace
	    (icon-editor-workspace current-icon-editor))
	  (current-image-plane?
	    (image-plane-for-workstation-event?
	      current-icon-editor-event))
	  (current-workspace-on-image-plane?
	    (if current-image-plane?
		(workspace-on-image-plane?
		  current-image-plane?)
		nil)))
     ,@body))





;;; The function/substitution-macro `snap-to-inner-dimensions' returns the
;;; adjusted x and y values.

(defun-substitution-macro snap-to-inner-dimensions
    (x-in-workspace y-in-workspace
		    left-edge top-edge
		    right-edge bottom-edge
		    border-width)
  (let* ((adjusted-right-edge (-w right-edge 1))
	 (adjusted-bottom-edge (-w bottom-edge 1)))
    (values
      (cond
	((<=w left-edge x-in-workspace (+w left-edge border-width))
	 (+w left-edge border-width))
	((<=w (-w adjusted-right-edge border-width) x-in-workspace adjusted-right-edge)
	 (-w adjusted-right-edge border-width))
	(t x-in-workspace))
      (cond
	((<=w top-edge y-in-workspace (+w top-edge border-width))
	 (+w top-edge border-width))
	((<=w (-w adjusted-bottom-edge border-width) y-in-workspace adjusted-bottom-edge)
	 (-w adjusted-bottom-edge border-width))
	(t y-in-workspace)))))




;;; The function `execute-icon-editor-mouse-down-in-view-pad' handles
;;; any mouse down event that falls within the view pad.  The bounding box
;;; is picked when mouse down occurs in the right or bottom borders of 
;;; the bounding box.

(defun execute-icon-editor-mouse-down-in-view-pad
    (x-in-window
      y-in-window
      x-in-workspace
      y-in-workspace
      icon-editor image-plane block-near-cursor)
  (declare (ignore block-near-cursor)) ; not needed currently
  (let* ((bounding-box (icon-editor-view-pad-bounding-box
			 (icon-editor-view-pad icon-editor)))
	 (border-width (adjusted-bounding-box-border-width bounding-box))
	 (left-edge (left-edge-of-block bounding-box))
	 (top-edge (top-edge-of-block bounding-box))
	 (right-edge (right-edge-of-block bounding-box))
	 (bottom-edge (bottom-edge-of-block bounding-box)))
    (multiple-value-bind (edge-or-corner?
			   x-offset-of-mouse-from-edge
			   y-offset-of-mouse-from-edge)
      (select-edge-or-corner-of-bounding-box
	bounding-box x-in-window y-in-window image-plane
	;; have leeway only if waiting, i.e., not using tool:
	(not (eq (icon-editor-translator-state
		   (icon-editor-translator icon-editor))
		 (icon-editor-state 'waiting))))
      (cond
	((memq edge-or-corner?
	       '(bottom-right right bottom bottom-left top-right))
	 ;; Then -- bounding box bottom or right edge picked.
	 (enqueue-icon-editor-translator-event
	   icon-editor
	   (icon-editor-translator-event 'view-pad-mouse-down)
	   x-in-workspace
	   y-in-workspace)
	 (with-old-style-workstation-return-function
	     ('finish-moving-bounding-box-for-icon-editor
		(slot-value-list icon-editor bounding-box)
		'reclaim-icon-editor-slot-value)
	   (enter-context-in-current-workstation
	     'bounding-box 
	     (make-bounding-box-state
	       bounding-box
	       image-plane x-in-window y-in-window
	       (case edge-or-corner?
		 (bottom-left 'bottom)
		 (top-right 'right)
		 ((bottom bottom-right right) edge-or-corner?)
		 (t nil))
	       x-offset-of-mouse-from-edge
	       y-offset-of-mouse-from-edge
	       'update-moving-bounding-box-for-icon-editor
	       (icon-editor-list icon-editor bounding-box)
	       'reclaim-icon-editor-slot-value))))
	(t
	 ;; Else
	 ;; Can handle other mouse down events in view pad here,
	 ;; but for now, just tell the events translator that a mouse-down
	 ;; occurred in the view-pad
	 (cond
	   ((and (>=f x-in-workspace left-edge)
		 (>=f y-in-workspace top-edge))
	    (multiple-value-setq (x-in-workspace y-in-workspace)
	      (snap-to-inner-dimensions
		x-in-workspace y-in-workspace
		left-edge top-edge right-edge bottom-edge border-width))
	    (enqueue-icon-editor-translator-event
	      icon-editor
	      (icon-editor-translator-event 'view-pad-mouse-down)
	      x-in-workspace
	      y-in-workspace))
	   (t
	    (enqueue-icon-editor-translator-event
	      icon-editor (icon-editor-translator-event 'outside-event)
	      nil nil))))))))




(defun-substitution-macro execute-icon-editor-mouse-down-in-table
    (x-in-window y-in-window icon-editor image-plane block-near-cursor)
  (let (cell? table frame? slot-name? class-qualifier?)
    (cond
      ((and (multiple-value-setq
	      (cell? table)
	      (pick-cell-from-table
		block-near-cursor 
		image-plane x-in-window y-in-window))
	    (not (cell-is-block-p cell?))
	    ;; A text cell picked
	    (multiple-value-setq
	      (frame? slot-name? class-qualifier?)
	      (get-slot-represented-by-text-cell-if-any cell?))
	    (type-of-slot-if-editable
	      (class frame?) slot-name? nil class-qualifier?))       
       (cond
	 ;; later, check class-qualifier? along with slot-name?(!)
	 ((eq slot-name? 'icon-editor-table-info-frame-main-color)
	  (when (and (icon-editor-main-color-menu? icon-editor)
		     (frame-has-been-reprocessed-p
		       (icon-editor-main-color-menu? icon-editor)
		       (icon-editor-main-color-menu-serial-number icon-editor)))
	    (setf (icon-editor-main-color-menu? icon-editor) nil))

	  (post-full-color-menu
	    'layer-color
	    (mouse-pointer-of-last-down current-workstation) ; Bogus
	    (icon-editor-workspace icon-editor)
	    'handle-menu-choice-for-layer-color
	    (slot-value-cons icon-editor nil)))
	 ((eq slot-name? 'icon-editor-table-info-frame-text) ;pbk
	  (let* ((icon-editor-engine  (icon-editor-engine icon-editor))
		 (layer (icon-editor-engine-current-layer icon-editor-engine))
		 (old-text-place (loop for sublist on (drawing-elements-of-layer layer)
				       when (text-drawing-element-p (car sublist))
					 return sublist))
		 (old-text (copy-drawing-element-with-icon-editor-conses
			     (car old-text-place)  nil nil))
		 (initial-string
		   (slot-value-list
		     (twith-output-to-text-string
		       (write-text-specification old-text)))))
	    (when t ;trying-to-reclaim-text-in-icons?  ; pbk
	      (reclaim-icon-editor-slot-value old-text)) ; pbk
	    (edit-attribute-table-slot-in-place
	      table frame? slot-name? class-qualifier?
	      image-plane
	      'finish-doing-icon-editor-type-in
	      slot-name?			; return information
	      nil nil nil nil 
	      initial-string)))
	 ((eq slot-name? 'icon-editor-table-info-frame-stipple)
	  (let* ((icon-editor-engine  (icon-editor-engine icon-editor))
		 (layer (icon-editor-engine-current-layer icon-editor-engine))
		 (old-stipple-place (loop for sublist on (drawing-elements-of-layer layer)
				       when (stipple-drawing-element-p (car sublist))
					 return sublist))
		 (old-stipple (copy-drawing-element-with-icon-editor-conses
				(car old-stipple-place)  nil nil))
		 (initial-string
		   (slot-value-list
		     (twith-output-to-text-string
		       (write-stipple-specification old-stipple)))))
	    (when t
	      (reclaim-icon-editor-slot-value old-stipple))
	    (edit-attribute-table-slot-in-place
	      table frame? slot-name? class-qualifier?
	      image-plane
	      'finish-doing-icon-editor-type-in
	      slot-name?			; return information
	      nil nil nil nil 
	      initial-string)))
	   
	  
	 (t
	  (when (eq slot-name? 'icon-editor-table-info-frame-main-region)	 
	    (inform-user-of-current-regions icon-editor))
	  (edit-attribute-table-slot-in-place
	    table frame? slot-name? class-qualifier?
	    image-plane
	    'finish-doing-icon-editor-type-in
	    slot-name?			; return information
	    nil)))))))			; return information reclaimer, if any



(defun handle-menu-choice-for-layer-color (menu new-color menu-item icon-editor?)
  (declare (ignore menu-item))
  (when (and new-color					    ; Color menu may now return NIL.
	     (icon-editor-p icon-editor?)
	     (not (icon-editor-killed-p icon-editor?)))
    (when (neq menu (icon-editor-main-color-menu? icon-editor?))
      (delete-icon-editor-main-color-menu icon-editor?)
      (setf (icon-editor-main-color-menu? icon-editor?) menu)
      (frame-serial-number-setf (icon-editor-main-color-menu-serial-number icon-editor?)
				(current-frame-serial-number)))
    (enqueue-icon-editor-translator-event
      icon-editor? (icon-editor-translator-event 'set-main-color)
      new-color nil)))











;;; The function `execute-icon-editor-mouse-down-event' takes care of a mouse-
;;; down event occuring within the icon editor workspace.

(defun execute-icon-editor-mouse-down-event
    (icon-editor mouse-pointer image-plane)
  (with-mouse-pointer-bindings (mouse-pointer
				 x-in-window
				 y-in-window
				 x-in-workspace
				 y-in-workspace) mouse-pointer
  (let* ((block-near-cursor?			; block, no connections
	   (find-object-near-mouse
	     x-in-window y-in-window
	     image-plane nil '(name-box button-label))))
    (cond 
      ((point-in-view-pad-p x-in-workspace y-in-workspace
			    (icon-editor-view-pad icon-editor))
       (execute-icon-editor-mouse-down-in-view-pad
	 x-in-window y-in-window x-in-workspace y-in-workspace
	 icon-editor image-plane block-near-cursor?))
      ((point-in-layers-pad-p x-in-workspace y-in-workspace
			      (icon-editor-layers-pad icon-editor))
       (enqueue-icon-editor-translator-event
	 icon-editor
	 (icon-editor-translator-event 'layers-pad-mouse-down)
	 x-in-workspace
	 y-in-workspace))
      (t
       (cond
	 (block-near-cursor?
	  (frame-class-case block-near-cursor?
	    (button
	      ;; Consider not entering and ignoring input
	      ;;   if not in-block-p
	      (check-memory-for-development
		'execute-icon-editor-mouse-down-event_1)
	      (with-old-style-workstation-return-function
		  ('enqueue-icon-editor-translator-event-on-return
		     (icon-editor-list
		       (button-action-data? block-near-cursor?)	; translator event
		       image-plane)
		     'reclaim-icon-editor-slot-value)
		(enter-button-down-context block-near-cursor? image-plane))
	      (check-memory-for-development
		'execute-icon-editor-mouse-down-event_2))
;            not currently used -- needs work!
;            (subcommand-menu
;            (enter-subcommand-context block-near-cursor?
;            'do-icon-editor-subcommand image-plane x-in-window y-in-window))

	    (table
	      (execute-icon-editor-mouse-down-in-table
		x-in-window y-in-window icon-editor image-plane block-near-cursor?))
	    (t
	      ;; assume that if it's a mouse down outside buttons and tables,
	      ;; it'll be a view-pad mouse down event.
	      (enqueue-icon-editor-translator-event
		icon-editor
		(icon-editor-translator-event 'view-pad-mouse-down)
		x-in-workspace
		y-in-workspace))
	    ))					; no need to clean up on exit of context
	 (t
	  ;; assume that if it's a mouse down outside buttons and tables,
	  ;; it'll be a view-pad mouse down event.
	  (enqueue-icon-editor-translator-event
	    icon-editor
	    (icon-editor-translator-event 'view-pad-mouse-down)
	    x-in-workspace
	    y-in-workspace)
	  (enqueue-icon-editor-translator-event
	    icon-editor (icon-editor-translator-event 'outside-event)
	    nil nil)
	  (run-top-level-event-handler mouse-pointer)
;       (enter-dragging-context			;   some way if other action
;	 image-plane
;	 (-w x-in-window
;	     (left-edge-of-image-in-window image-plane))
;	 (-w y-in-window
;	     (top-edge-of-image-in-window image-plane))
;	 nil t)
	  )))))))





(defmacro with-bounding-box-paramenters ((current-icon-editor) &body body)
  `(let* ((current-bounding-box
	    (icon-editor-view-pad-bounding-box
	      (icon-editor-view-pad current-icon-editor)))
	  (current-left-edge
	    (left-edge-of-block current-bounding-box))
	  (current-top-edge
	    (top-edge-of-block current-bounding-box))
	  (current-right-edge
	    (right-edge-of-block current-bounding-box))
	  (current-bottom-edge
	    (bottom-edge-of-block current-bounding-box))
	  (current-border-width
	    (adjusted-bounding-box-border-width current-bounding-box)))
     ,@body))


(defun execute-icon-editor-workstation-event (workstation-event mouse-pointer)
  (in-icon-editor-context (workstation-event)
    #+development (gensym-assert (icon-editor-p current-icon-editor))
    (key-case (workstation-event-code current-icon-editor-event)
      (mouse-motion	; motion can be outside the workspace
	(when (eq current-workspace-on-image-plane?
		  current-icon-editor-workspace)
	  #+development (gensym-assert (and 'mouse-motion
					    (image-plane-p current-image-plane?)))
	  (let (x-in-workspace y-in-workspace)
	    (with-image-plane-transform (current-image-plane?)
	      (setf x-in-workspace (x-in-workspace
				     (workstation-event-cursor-x workstation-event)))
	      (setf y-in-workspace (y-in-workspace
				     (workstation-event-cursor-y workstation-event))))
	    (when (icon-editor-mouse-down-p current-icon-editor)
	      (with-bounding-box-paramenters (current-icon-editor)
		(multiple-value-setq (x-in-workspace y-in-workspace)
		  (snap-to-inner-dimensions
		    x-in-workspace y-in-workspace
		    current-left-edge
		    current-top-edge
		    current-right-edge
		    current-bottom-edge
		    current-border-width))))
	    (enqueue-icon-editor-translator-event
	      current-icon-editor
	      (icon-editor-translator-event 'mouse-motion)
	      x-in-workspace y-in-workspace))))
      (mouse-up
	(setf (icon-editor-mouse-down-p current-icon-editor) nil)
	(when (eq current-workspace-on-image-plane?
		  current-icon-editor-workspace)
	  #+development (gensym-assert
			  (and 'mouse-up (image-plane-p current-image-plane?)))
	  (let (x-in-workspace y-in-workspace)
	    (with-image-plane-transform (current-image-plane?)
	      (setf x-in-workspace (x-in-workspace
				     (workstation-event-cursor-x workstation-event)))
	      (setf y-in-workspace (y-in-workspace
				     (workstation-event-cursor-y workstation-event))))
	    (with-bounding-box-paramenters (current-icon-editor)
	      (multiple-value-setq (x-in-workspace y-in-workspace)
		(snap-to-inner-dimensions
		  x-in-workspace y-in-workspace
		  current-left-edge
		  current-top-edge
		  current-right-edge
		  current-bottom-edge
		  current-border-width)))
	    (enqueue-icon-editor-translator-event
	      current-icon-editor
	      (if (point-in-view-pad-p x-in-workspace y-in-workspace
				       (icon-editor-view-pad current-icon-editor))
		  (icon-editor-translator-event 'view-pad-mouse-up)
		  (icon-editor-translator-event 'non-view-pad-mouse-up))
	      x-in-workspace y-in-workspace))))
      (<mouse-down>
	(setf (icon-editor-mouse-down-p current-icon-editor) t)
	(if (eq current-workspace-on-image-plane?
		current-icon-editor-workspace)
	    (execute-icon-editor-mouse-down-event
	      current-icon-editor mouse-pointer current-image-plane?)
	    ;; Should it ever to the next form, should it?
	    (run-top-level-event-handler mouse-pointer)))
      (end
	(enqueue-icon-editor-translator-event
	  current-icon-editor
	  (icon-editor-translator-event 'end-editing)
	  nil nil))
      (undo
	(enqueue-icon-editor-translator-event
	  current-icon-editor
	  (icon-editor-translator-event 'undo)
	  nil nil))
      (<standard-abort-keys>
	;; the following violates some abstractions by not
	;;   going through enqueue-icon-editor-translator-
	;;   event!
	;; follow the enqueue-icon-editor-translator-event logic
	;;   to find the real comments and discussion on the issue
	;;   of aborting. (MHD/PTO 10/27/89)
	(abort-current-workstation-context 'icon-editor))
      (<standard-enter-keys>
	;; quit?? [I doubt it. -mhd] -- must be enabled.
	))))




;;; The keymap `icon-editor-keymap' decides if the workstation-event it is
;;; given is relevant to the current icon editor workstation context.  If the
;;; workstation event is not relevant, the icon editor events translator will
;;; be informed that there was an outside event.

(define-keymap icon-editor-keymap (:private t)
  (<mouse-select> run-top-level-event-handler)
  (<mouse-drag> run-top-level-event-handler)

  ((<mouse-gesture> image-plane-spot)
   mouse-gesture-on-image-plane-icon-editor)
  (<mouse-gesture> run-top-level-event-handler)

  (end some-event-in-icon-editor)
  (undo some-event-in-icon-editor)
  (<standard-abort-keys> some-event-in-icon-editor)
  (otherwise run-top-level-event-handler))

(define-event-handler mouse-gesture-on-image-plane-icon-editor
    ((mouse-pointer mouse-pointer)
     (icon-editor workstation-context-specifics)
     (workspace workspace))
  (if (eq workspace (icon-editor-workspace icon-editor))
      (some-event-in-icon-editor mouse-pointer)
      (run-top-level-event-handler mouse-pointer)))

(define-event-handler some-event-in-icon-editor (event mouse-pointer)
  (execute-icon-editor-workstation-event event mouse-pointer))
      








;;;; Icon Editor Subcommands


;; These are stubs -- eventually use this to replace some of the button
;; stuff above!  This facility is still evolving from its original use
;; for (text) editor subcommands.  (MHD 9/19/89)

;; Implement this after prototype is ready.  -pto 23sep89

;;; Make-icon-editor-tool-palette ... 

;(defun make-icon-editor-tool-palette ()
;  (make-or-reformat-table
;    (slot-value-list
;      (slot-value-list
;        (make-icon-cell
;          'outlined-filled-polygon-button 0 0 0 0)
;        (make-icon-cell
;          'outlined-filled-polygon-button 0 0 0 0)
;        (make-icon-cell
;          'outlined-filled-polygon-button 0 0 0 0))
;      (slot-value-list
;        (make-icon-cell
;          'outlined-filled-polygon-button 0 0 0 0)
;        (make-icon-cell
;          'outlined-filled-polygon-button 0 0 0 0)
;        (make-icon-cell
;          'outlined-filled-polygon-button 0 0 0 0))
;      (slot-value-list
;        (make-icon-cell
;          'outlined-filled-polygon-button 0 0 0 0)
;        (make-icon-cell
;          'outlined-filled-polygon-button 0 0 0 0)
;        (make-icon-cell
;          'outlined-filled-polygon-button 0 0 0 0)))
;    'subcommand-menu-table-format nil 'subcommand-menu t))



;;; `Do-icon-editor-subcommand' is currently never invoked.  It would
;;; be invoked by the subcommand-state when it has selected some item
;;; in the subcommand menu.  But there are no subcommand menus in the
;;; icon editor at present.

;(defun do-icon-editor-subcommand (subcommand-menu subcommand-menu-cell)
;  (declare (ignore subcommand-menu))
;  (frame-class-case subcommand-menu-cell
;    (outlined-filled-polygon-button
;            
;            ;; do something!
;            
;            ;; (enable-or-disable-subcommand ...) -- have highlighting
;            ;;   on while doing it, and turn it off when done!
;            )
;          ;; [ETC.!]
;    ))
    
  
;;; Finish-doing-icon-editor-type-in ...

(defun finish-doing-icon-editor-type-in (workstation-context)

  #+development (gensym-assert (workstation-context-p workstation-context))
  (let* ((slot-name
	   (workstation-context-return-information workstation-context))
	 (edit-state
	   specific-structure-for-current-workstation-context))
    #+development (gensym-assert (edit-state-p edit-state))
    edit-state
    ;; now in edit context -- can use the edit context now before exiting
    (exit-current-workstation-context-in-return-function 'editing) ; exit edit context
    (if (icon-editor-killed-p
	  specific-structure-for-current-workstation-context)	; icon editor
	(abort-current-workstation-context 'icon-editor)
	(let* ((icon-editor
		 specific-structure-for-current-workstation-context)
	       (table-info-frame
		 (icon-editor-table-info-frame
		   (case slot-name
		     ((icon-editor-table-info-frame-main-color
			icon-editor-table-info-frame-main-region
			icon-editor-table-info-frame-main-image
			icon-editor-table-info-frame-text ; pbk
			icon-editor-table-info-frame-stipple)
		      (icon-editor-label-table icon-editor))
		     ((icon-editor-table-info-frame-icon-width
			icon-editor-table-info-frame-icon-height
			icon-editor-table-info-frame-global-stipple)
		      (icon-editor-size-table icon-editor))))))
	  #+development (gensym-assert (and (icon-editor-p icon-editor)
					    (frame-of-class-p
					      table-info-frame
					      'icon-editor-table-info-frame)))
	  (case slot-name
	    (icon-editor-table-info-frame-main-region
	     (enqueue-icon-editor-translator-event
	       icon-editor (icon-editor-translator-event 'set-main-region)
	       (icon-editor-table-info-frame-main-region
		 table-info-frame)
	       nil))
	    (icon-editor-table-info-frame-main-color
	     (let* ((new-color
		      (icon-editor-table-info-frame-main-color table-info-frame)))
	       (if (color-or-metacolor-p new-color)
		   (enqueue-icon-editor-translator-event
		     icon-editor (icon-editor-translator-event 'set-main-color)
		     new-color nil)
		   (progn
		     (enqueue-icon-editor-visual-event
		       icon-editor (icon-editor-visual-event 'change-main-color)
		       (icon-editor-engine-main-color (icon-editor-engine icon-editor))
		       nil)
		     (enqueue-icon-editor-visual-event
		       icon-editor
		       (icon-editor-visual-event 'inform-user)
		       (twith-output-to-text-string 
			 (tformat "Illegal color ~a -- not accepted." new-color))
		       nil)))))

	    (icon-editor-table-info-frame-main-image
	     (enqueue-icon-editor-translator-event
	       icon-editor (icon-editor-translator-event 'set-main-image)
	       (icon-editor-table-info-frame-main-image table-info-frame)
	       nil))
	    (icon-editor-table-info-frame-text    ; pbk
	     (enqueue-icon-editor-translator-event
	       icon-editor (icon-editor-translator-event 'set-text)
	       (icon-editor-table-info-frame-text table-info-frame)
	       nil))
	    (icon-editor-table-info-frame-stipple
	     (enqueue-icon-editor-translator-event
	       icon-editor (icon-editor-translator-event 'set-stipple)
	       (icon-editor-table-info-frame-stipple table-info-frame)
	       nil))
	    (icon-editor-table-info-frame-global-stipple
	     (enqueue-icon-editor-translator-event
	       icon-editor (icon-editor-translator-event 'set-global-stipple)
	       (icon-editor-table-info-frame-global-stipple table-info-frame)
	       nil))
	    (icon-editor-table-info-frame-icon-width
	     (enqueue-icon-editor-translator-event
	       icon-editor 
	       (icon-editor-translator-event 'change-icon-width-from-table)
	       (icon-editor-table-info-frame-icon-width table-info-frame)
	       nil))
	    (icon-editor-table-info-frame-icon-height
	     (enqueue-icon-editor-translator-event
	       icon-editor 
	       (icon-editor-translator-event 'change-icon-height-from-table)
	       (icon-editor-table-info-frame-icon-height table-info-frame)
	       nil)))))))







;;; Enqueue-icon-editor-translator-event-on-return ... for handling button
;;; down context.

(defun enqueue-icon-editor-translator-event-on-return (workstation-context)
  (let* ((translator-event
	   (first
	     (workstation-context-return-information workstation-context)))
	 (image-plane
	   (second
	     (workstation-context-return-information workstation-context))))
    (exit-current-workstation-context-in-return-function 'button-down)
    (let ((icon-editor
	    specific-structure-for-current-workstation-context))
      (enqueue-icon-editor-translator-event
	icon-editor translator-event image-plane nil))))






;;; The function `update-moving-bounding-box-for-icon-editor' ...

(defun update-moving-bounding-box-with-expanded-arguments
       (x-in-workspace y-in-workspace icon-editor bounding-box)
  #+development (gensym-assert (and (icon-editor-p icon-editor)
				    (frame-of-class-p bounding-box 'bounding-box)))
  (let* ((twice-bounding-box-border-width
	   (twicew (adjusted-bounding-box-border-width bounding-box)))
	 (new-width (icon-delta-x-for-adjusted-delta-x
		      (-w (width-of-block bounding-box)
			  twice-bounding-box-border-width)))
	 (new-height (icon-delta-y-for-adjusted-delta-y
		       (-w (height-of-block bounding-box)
			   twice-bounding-box-border-width))))
    (enqueue-icon-editor-translator-event
      icon-editor
      (icon-editor-translator-event 'change-icon-width-from-bounding-box)
      new-width
      nil)
    (enqueue-icon-editor-translator-event
      icon-editor
      (icon-editor-translator-event 'change-icon-height-from-bounding-box)
      new-height
      nil))
  (enqueue-icon-editor-translator-event
    icon-editor
    (icon-editor-translator-event 'mouse-motion)
    x-in-workspace y-in-workspace))


(defun update-moving-bounding-box-for-icon-editor
       (x-in-workspace y-in-workspace icon-editor-and-bounding-box)
  (update-moving-bounding-box-with-expanded-arguments
    x-in-workspace y-in-workspace
    (car icon-editor-and-bounding-box)
    (second icon-editor-and-bounding-box)))



(defun finish-moving-bounding-box-for-icon-editor (bounding-context)
  (declare (ignore bounding-context))
  (exit-current-workstation-context-in-return-function 'bounding-box)
  (let ((icon-editor specific-structure-for-current-workstation-context))
    #+development (gensym-assert (icon-editor-p icon-editor))
    (enqueue-icon-editor-translator-event
      icon-editor
      (icon-editor-translator-event 'end-changing-icon-size-from-bounding-box)
      nil nil)))




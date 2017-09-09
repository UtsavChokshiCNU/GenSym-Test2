;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module ICONS4 -- The Icon Editor Engine

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Ong, Peng Tsin







;; The Icon Editor Engine

;; change-icon-size
;; set-main-color
;; set-main-region
;; set-outline-color
;; set-outline-region
;; new-layer
;; cancel-editing
;; end-editing
;; show-grid
;; hide-grid
;; group
;; ungroup-current-layer
;; delete-current-layer
;; draw events:
;;   draw-point
;;   draw-lines
;;   draw-arc
;;   draw-outlined-rectangle
;;   draw-outlined-polygon
;;   draw-outlined-circle
;;   draw-filled-rectangle
;;   draw-filled-polygon
;;   draw-filled-circle
;;   draw-outlined-filled-rectangle
;;   draw-outlined-filled-polygon
;;   draw-outlined-filled-circle





;;;; The Icon Editor Engine's Supporting Functions and Macros


;;; The function `recompute-view-pad-size' ...

(defun recompute-view-pad-size (icon-editor)
  (let* ((view-pad (icon-editor-view-pad icon-editor))
	 (workspace (icon-editor-workspace icon-editor)))
    (setf (icon-editor-view-pad-width view-pad)
	  (-w (width-of-block workspace)
	      (icon-editor-view-pad-x-origin-in-workspace view-pad)))
    (setf (icon-editor-view-pad-height view-pad)
	  (-w (height-of-block workspace)
	      (icon-editor-view-pad-y-origin-in-workspace view-pad)))))





;;; The function `change-size-of-icon-in-icon-editor' changes the size (i.e.
;;; the current width and height) of the icon being drawn in the icon editor
;;; instance and calls the relevant functions to update the visual
;;; representations on the icon editor workspace.

(defun change-size-of-icon-in-icon-editor (icon-editor width height)
  (let* ((engine (icon-editor-engine icon-editor)))
    (cond
      ((or (>w width (maximum-icon-width-in-icon-editor))
	   (>w height (maximum-icon-height-in-icon-editor)))
       (enqueue-icon-editor-visual-event
	 icon-editor
	 (icon-editor-visual-event 'inform-user)
	 (twith-output-to-text-string
	   (cond
	     ((>w width (maximum-icon-width-in-icon-editor))
	      (tformat "The maximum icon width in the icon editor is ~a."
		       (maximum-icon-width-in-icon-editor)))
	     (t
	      (tformat "The maximum icon height in the icon editor is ~a."
		       (maximum-icon-height-in-icon-editor)))))
	 nil)
       (let* ((new-width
		(if (>w width (maximum-icon-width-in-icon-editor))
		    (maximum-icon-width-in-icon-editor)
		    width))
	      (new-height
		(if (>w height (maximum-icon-height-in-icon-editor))
		    (maximum-icon-height-in-icon-editor)
		    height)))
	 (enqueue-icon-editor-translator-event
	   icon-editor
	   (icon-editor-translator-event 'change-icon-size-from-engine)
	   new-width new-height)
	 (setf (icon-editor-engine-icon-width engine) new-width)
	 (setf (icon-editor-engine-icon-height engine) new-height)))
      (t
       (setf (icon-editor-engine-icon-width engine) width)
       (setf (icon-editor-engine-icon-height engine) height)
       ;;
       ;; WORK TO BE DONE HERE!
       ;; Remember to keep history.
       ;; Call apropriate update functions.
       ))))


;;; The function `shrink-wrap-icon-in-icon-editor' shrink each dimension (i.e.
;;; width and height) of the icon to an appropriate size: if the width-extent
;;; of the icon is less than the current-width, then the current-width is set
;;; to the width-extent.  Otherwise, the current-width is not changed.  The
;;; situation is analogous for the height of the icon.

(defun-substitution-macro shrink-wrap-icon-in-icon-editor 
				    (icon-editor)
  (let* ((icon-editor-engine
	   (icon-editor-engine icon-editor))
	 (current-width
	   (icon-editor-engine-icon-width icon-editor-engine))
	 (current-height
	   (icon-editor-engine-icon-height icon-editor-engine))
	 (width-extent
	   (icon-editor-engine-width-extent icon-editor-engine))
	 (height-extent
	   (icon-editor-engine-height-extent icon-editor-engine)))
    (declare (type fixnum
		   current-width current-height width-extent height-extent))
    (change-size-of-icon-in-icon-editor
      icon-editor
      (if (>f current-width width-extent) width-extent current-width)
      (if (>f current-height height-extent) height-extent current-height))))




;;; The functions `set-main-color-in-icon-editor',
;;; `set-main-color-in-icon-editor', 
;;; `set-outline-color-in-icon-editor', and
;;; `set-outline-color-in-icon-editor' are for declaring the color labels 
;;; for the draw commands.

(defun set-main-color-in-icon-editor (icon-editor new-color)
  (let* ((engine (icon-editor-engine icon-editor))
	 (current-region?
	   (icon-editor-engine-main-region? engine)))
    ;;
    ;; WORK TO BE DONE HERE!
    ;; . If current layer has no region (i.e. has a color or metacolor),
    ;;   then have to change label of current layer.
    ;;
    ;; WORK TO BE DONE HERE!
    ;; . Call enqueue-icon-editor-visual-event to change color of region
    ;; . Remember to update the color of the outline color menu if the outline
    ;;   has the same region
    (if (not current-region?)
	;; change the label  -- Must have a current layer at this point!
	(change-label-of-current-layer engine new-color))
    ;; change the region globally
    (set-color-of-region-in-icon-editor
      icon-editor (icon-editor-engine-main-color engine) nil)
    (set-color-of-region-in-icon-editor
      icon-editor (or current-region? new-color) new-color)
    (when (drawing-elements-of-layer (icon-editor-engine-current-layer engine))
      (enqueue-icon-editor-visual-event
	icon-editor
	(icon-editor-visual-event 'change-color-of-region-in-view-pad)
	current-region? new-color))
    (enqueue-icon-editor-visual-event
      icon-editor
      (icon-editor-visual-event
	'change-color-of-region-in-layers-pad)
      (icon-editor-engine-main-region? engine)
      new-color)
    (enqueue-icon-editor-visual-event
      icon-editor
      (icon-editor-visual-event 'change-main-color)
      new-color nil)
    (setf (icon-editor-engine-main-color engine) new-color)))



(defun-substitution-macro set-main-region-in-icon-editor
				    (icon-editor new-main-region?)
  (cond
    ((illegal-region-name-p new-main-region?)
     (enqueue-icon-editor-visual-event
       icon-editor
       (icon-editor-visual-event 'inform-user)
       (copy-constant-wide-string #w"Illegal region name -- not accepted.")
       nil))
    (t
     (if (or (eq new-main-region? :nil)
	     (eq new-main-region? 'none)) (setq new-main-region? nil))
     (let* ((engine (icon-editor-engine icon-editor))
	    (old-main-region? (icon-editor-engine-main-region? engine)))
       (when (not (eq old-main-region? new-main-region?))
	 ;;
	 ;; WORK TO BE DONE HERE!
	 ;; . reset label of current layer here
	 (enqueue-icon-editor-visual-event
	   icon-editor
	   (icon-editor-visual-event
	     'change-label-of-layer-in-layers-pad)
	   (icon-editor-engine-current-layer-index engine)
	   (or (icon-editor-engine-main-region? engine)
	       (icon-editor-engine-main-color engine)))
	 (setf (icon-editor-engine-main-region? engine) new-main-region?)
	 (setf (label-of-layer (icon-editor-engine-current-layer
				 (icon-editor-engine icon-editor)))
	       new-main-region?)
	 (let* ((new-color? (get-color-of-region-in-icon-editor
			      icon-editor new-main-region?)))
	   (set-main-color-in-icon-editor
	     icon-editor
	     (if new-color?
		 new-color?
		 (icon-editor-engine-main-color engine)))
	   (set-color-of-region-in-icon-editor
	     icon-editor old-main-region? nil))
	 )))))


;;; The function `set-main-image-in-icon-editor' sets the image for this icon
;;; layer.  Inserts/edits the (image <name> <point>) clause.  Returns non-nil
;;; iff we changed something.

(defun set-main-image-in-icon-editor (icon-editor new-image)
  (let* ((engine (icon-editor-engine icon-editor))
	 (workspace (icon-editor-workspace icon-editor))
	 (changed? nil)
	 (new-image-name? (and new-image
			       (second new-image)))
	 (new-image-definition? (and new-image-name?
				     (find-image-named new-image-name?)))
	 (variables
	   (cdr (icon-editor-variable-spec-list icon-editor)))
	 fixed-variables fixed-element new-variables)
    (multiple-value-setf (fixed-element fixed-variables new-variables)
			 (fix-up-drawing-element-for-icon-editor new-image variables))
    (without-consistency-analysis (workspace)
      (cond ((and new-image-name? (null new-image-definition?))
	     (enqueue-icon-editor-visual-event 
	       icon-editor
	       (icon-editor-visual-event 'inform-user)
	       (twith-output-to-text-string
		 (tformat "Note that there is currently no image named ~a" new-image-name?))
	       nil))
	    ((and new-image-definition? (frame-incomplete-p new-image-definition?))
	     (enqueue-icon-editor-visual-event 
	       icon-editor
	       (icon-editor-visual-event 'inform-user)
	       (twith-output-to-text-string
		 (tformat "Note that the image ~a is currently incomplete" new-image-name?))
	       nil))
	    (t
	     ;; Remove the error message, if any.
	     (enqueue-icon-editor-visual-event 
	       icon-editor
	       (icon-editor-visual-event 'inform-user)
	       (icon-editor-translator-state (icon-editor-translator icon-editor))
	       nil)))
      (unless (eq fixed-variables 'error)
	(when new-variables
	  (setf (icon-editor-variable-spec-list icon-editor)
		(icon-editor-push 'variables fixed-variables))
	  (inform-user-of-new-variables-for-icon-editor
	    icon-editor new-variables)
	  (reclaim-gensym-tree new-variables)
	  (reclaim-gensym-tree variables))
	(setf changed? (change-image-of-current-layer engine new-image))
	(when nil ; leaving old-leak for now! why slot value?? (pbk 2/6/96)
	  (reclaim-icon-editor-slot-value (icon-editor-engine-main-image? engine))) 
	(setf (icon-editor-engine-main-image? engine)
	      (copy-tree-using-icon-editor-conses new-image)))
      
      changed?)))

(defun default-value-for-variable
    (variable-name drawing-element)
  (cond
    ((text-drawing-element-p drawing-element)
     (cond ((eq variable-name (cadr drawing-element))
	    (stringw "undefined-text"))
	   ((eq variable-name (fourth drawing-element))
	    'large)
	   (t 0)))
    ((image-drawing-element-p drawing-element)
     0)))
       
(defun fix-up-drawing-element-for-icon-editor
    (drawing-element variables)
  (loop with new-variables = nil
	with current-variables
	  = (copy-tree-including-leaves-using-gensym-conses
	      variables)
	as current-error
	   = (element-contains-bad-variable? drawing-element
					     current-variables)
	as bad-variable-name
	   = (second current-error)
	as bad-variable-reason?
	   = (car current-error)
	until (null current-error)
	do
    (cond ((and (string=w bad-variable-reason? #w"is undefined")
		(not (reserved-icon-variable-name-p bad-variable-name)))
	   (let ((default-value (default-value-for-variable
				    bad-variable-name
				    drawing-element)))
	     (gensym-push default-value current-variables)
	     (gensym-push bad-variable-name current-variables)
	     (gensym-push (copy-for-slot-value default-value) new-variables)
	     (gensym-push bad-variable-name new-variables)))
	  (t (return (values drawing-element 'error))))
	finally
	  (return
	    (values drawing-element current-variables new-variables))))
		       
	

(defun inform-user-of-new-variables-for-icon-editor
    (icon-editor new-variables)
  (enqueue-icon-editor-visual-event 
    icon-editor
    (icon-editor-visual-event 'inform-user)
    (twith-output-to-text-string
      (twrite-string"Inserting new variable")
      (twrite-string
	(cond ((>f (length new-variables) 2)
	       "s:  ")
	      (t ":  ")))
      (loop for (name value) on new-variables by 'cddr
	    do
	(write-variable-name-and-value
	  name value)
	(twrite-string "  ")))
    nil))



;;; `reject-bad-variables'
;;; This is used by the slot-value-compiler for text-specification?
;;; and image-specification? within the icon-editor.

(defun reject-bad-variables (parse-result table-info-frame)  
  (let* ((icon-editor
	   (icon-editor-table-info-frame-icon-editor table-info-frame))
	 (variables
	   (cdr (icon-editor-variable-spec-list icon-editor)))
	 (bad-variable
	   (element-contains-bad-variable?
	     parse-result variables))
	 (reason-for-rejection (first bad-variable))
	 (reject-undefined-variables nil))
    (cond ((and bad-variable reason-for-rejection
		(or reject-undefined-variables
		    (not (string=w reason-for-rejection #w"is undefined"))))
	   (let* ((variable-name (second bad-variable))
		  (variable-value?
		    (getfq variables variable-name)))
	     (bad-variable-in-element-message
	       parse-result variable-name variable-value? reason-for-rejection)))
	  ((reserved-icon-variable-name-p (second bad-variable))
	   (reserved-icon-variable-message (second bad-variable)))
	  (t  parse-result))))


;;; `check-icon-description-for-images-named'
;;; Finds the first, if any, image-drawing-element in which
;;; the image-name is a member of names.
;;; Does not reclaim names or icon-description
;;; This function is used by the icon-editor before
;;; adding new variables, to avoid invalidating already
;;; existing image-drawing-elements.

(defun check-icon-description-for-images-named (names icon-description)
  (loop with line-drawing-description
	  = (cddr icon-description)
	with polychrome-header?
	  = (get-polychrome-header-if-any line-drawing-description)
	with variable-header?
	  = (get-variable-specification-if-any line-drawing-description)
	with background-header?
	  = (get-icon-background-layer-if-any line-drawing-description)
	 with stipple?
	   = (get-icon-stipple-if-any line-drawing-description)
	with description-elements
	  = (get-element-list
	      line-drawing-description
	      polychrome-header?
	      variable-header?
	      background-header?
	      stipple?)
	for description-element in description-elements
	thereis
	(and (image-drawing-element-p description-element)
	     (memq (image-drawing-element-image-name description-element)
		   names)
	     description-element)))


;;; `point-expression-variables'
;;; Returns a list of all the variables within a given
;;; point-expression.
;;; The caller is responsible for reclaiming the returned
;;; gensym-list.
;;; Does not reclaim point-expression.

(defun point-expression-variables (point-expression)
  (cond ((integerp point-expression)
	 nil)
	((or (eq point-expression '+) (eq point-expression '-))
	 nil)
	((null point-expression)
	 nil)
	((symbolp point-expression)
	 (gensym-list point-expression))
	((consp point-expression)
	 (let ((point-list-1
		 (point-expression-variables (car point-expression)))
	       (point-list-2
		 (point-expression-variables (cdr point-expression))))
	   (cond ((null point-list-1)
		  point-list-2)
		 ((null point-list-2)
		  point-list-1)
		 (t
		  (nconc point-list-1 point-list-2)))))))



;;; `image-specification? and text-specification?' are only top level
;;; slots in the table-info-frame of the icon-editor

(def-slot-value-compiler image-specification? (parse-result table-info-frame)
  (block validate-image-drawing-elements
  (let* ((point (third parse-result))
	 (variable-names
	   (and point
		(nconc (point-expression-variables (car point))
		       (point-expression-variables (cadr point))))))
    (when variable-names
      (let* ((icon-editor
	       (icon-editor-table-info-frame-icon-editor table-info-frame))
	     (icon-description?
	       (extract-icon-description-from-icon-editor icon-editor))
	     (conflicting-image-drawing-element?
	       (and icon-description?
		    (check-icon-description-for-images-named
		      variable-names
		      icon-description?)))
	     (error-string?
	       (and conflicting-image-drawing-element?
		    (bad-variable-in-element-message-string
		      conflicting-image-drawing-element?
		      #w"would contain"
		      (image-drawing-element-image-name conflicting-image-drawing-element?)
		      0
		      #w"would no longer be a symbol naming an image-definition"))))
	(when icon-description?
	  (reclaim-slot-value icon-description?))
	(reclaim-gensym-list variable-names)
	(when error-string?
	  (return-from validate-image-drawing-elements
	    (values bad-phrase
		    error-string?))))))
  (reject-bad-variables parse-result table-info-frame)))


(def-slot-value-compiler text-specification? (parse-result table-info-frame)
  (block validate-image-drawing-elements
  (let* ((label (cadr parse-result))
	 (point (third parse-result))
	 (x (car point))
	 (y (cadr point))
	 (variable-names
	   (nconc (point-expression-variables x)
		  (point-expression-variables y))))
    (when (symbolp label)
      (gensym-push label variable-names))
    (when variable-names
      (let* ((icon-editor
	       (icon-editor-table-info-frame-icon-editor table-info-frame))
	     (icon-description?
	       (extract-icon-description-from-icon-editor icon-editor))
	     (conflicting-image-drawing-element?
	       (check-icon-description-for-images-named
		 variable-names
		 icon-description?))
	     (image-name?
	       (and conflicting-image-drawing-element?
		    (image-drawing-element-image-name
		      conflicting-image-drawing-element?)))
	     (new-variable-value?
	       (and conflicting-image-drawing-element?
		    (cond ((eq label image-name?)
			   #w"undefined-text")
			  (t
			   0))))
	     (error-string?
	       (and conflicting-image-drawing-element?
		    (bad-variable-in-element-message-string
		      conflicting-image-drawing-element?
		      #w"would contain"
		      image-name?
		      new-variable-value?
		      #w"would no longer be a symbol naming an image-definition"))))
	(when icon-description?
	  (reclaim-slot-value icon-description?))
	(reclaim-gensym-list variable-names)
	(when error-string?
	  (return-from validate-image-drawing-elements
	    (values bad-phrase
		    error-string?))))))
  (reject-bad-variables parse-result table-info-frame)))


;;; The function `set-text-in-icon-editor' sets the text for this icon
;;; layer, including the icon-editor-engine-text? of the icon-editor-engine
;;; Inserts/edits the (text <whole-string> <point> <font-spec>) clause.
;;; Returns non-nil iff we changed something. (pbk 2/6/96)

(defun set-text-in-icon-editor (icon-editor text)  
  (let* ((engine (icon-editor-engine icon-editor))
	 (workspace (icon-editor-workspace icon-editor))
	 (changed? nil)
	 (variables
	   (cdr (icon-editor-variable-spec-list icon-editor)))
	 fixed-variables fixed-element new-variables)
    (multiple-value-setf (fixed-element fixed-variables new-variables)
			 (fix-up-drawing-element-for-icon-editor text variables))
    (without-consistency-analysis (workspace)
      (cond (t
	     ;; Remove the error message, if any.
	     (enqueue-icon-editor-visual-event 
	       icon-editor
	       (icon-editor-visual-event 'inform-user)
	       (icon-editor-translator-state (icon-editor-translator icon-editor))
	       nil)))
      (unless (eq fixed-variables 'error)
	(when new-variables
	  (setf (icon-editor-variable-spec-list icon-editor)
		(icon-editor-push 'variables fixed-variables))
	  (inform-user-of-new-variables-for-icon-editor
	    icon-editor new-variables)
	  (reclaim-gensym-tree new-variables)
	  (reclaim-gensym-tree variables))
	(setf changed? (change-text-of-current-layer engine text))
	(when (icon-editor-engine-text? engine) 
	  (reclaim-icon-editor-slot-value (icon-editor-engine-text? engine)))
	(setf (icon-editor-engine-text? engine)
	      (copy-drawing-element-with-icon-editor-conses text nil nil)))
      changed?)))

;;; The function `set-stipple-in-icon-editor' sets the stipple for this icon
;;; layer, including the icon-editor-engine-stipple? of the icon-editor-engine
;;; Inserts/edits the (stipple <stipple> [<point> <point>]) clause.  Returns
;;; non-nil iff we changed something.

(defun set-stipple-in-icon-editor (icon-editor stipple-spec &optional global-p)
  (cond
    (global-p
     (if (or (eq stipple-spec 'nil)
	     (stipple-p stipple-spec))
	 (setf (icon-editor-engine-global-stipple?
		 (icon-editor-engine icon-editor))
	       stipple-spec))
     (setf (icon-editor-stipple-spec icon-editor) stipple-spec))
    (t
     (let* ((engine (icon-editor-engine icon-editor))
	    (workspace (icon-editor-workspace icon-editor))
	    (changed? nil)
	    (variables
	      (cdr (icon-editor-variable-spec-list icon-editor)))
	    fixed-variables fixed-element new-variables)
       (multiple-value-setf (fixed-element fixed-variables new-variables)
			    (fix-up-drawing-element-for-icon-editor
			      stipple-spec variables))
       (without-consistency-analysis (workspace)
	 (cond (t
		;; Remove the error message, if any.
		(enqueue-icon-editor-visual-event 
		  icon-editor
		  (icon-editor-visual-event 'inform-user)
		  (icon-editor-translator-state (icon-editor-translator icon-editor))
		  nil)))
	 (unless (eq fixed-variables 'error)
	   (when new-variables
	     (setf (icon-editor-variable-spec-list icon-editor)
		   (icon-editor-push 'variables fixed-variables))
	     (inform-user-of-new-variables-for-icon-editor
	       icon-editor new-variables)
	     (reclaim-gensym-tree new-variables)
	     (reclaim-gensym-tree variables))
	   (setf changed? (change-stipple-of-current-layer engine stipple-spec))
	   (when (icon-editor-engine-stipple? engine) 
	     (reclaim-icon-editor-slot-value (icon-editor-engine-stipple? engine)))
	   (setf (icon-editor-engine-stipple? engine)
		 (copy-drawing-element-with-icon-editor-conses stipple-spec nil nil)))
	 changed?)))))

(defun set-global-stipple-in-icon-editor (icon-editor stipple-spec)
  (set-stipple-in-icon-editor icon-editor stipple-spec t))

;;; The function `update-icon-editor-status' updates the icon editor
;;; status table concerning the image in the current layer.

(defun update-icon-editor-status (icon-editor)
  (let* ((engine (icon-editor-engine icon-editor))
	 (layer (icon-editor-engine-current-layer engine)))

    (loop for drawing-element in (drawing-elements-of-layer layer) doing
      (when (image-drawing-element-p drawing-element)
	(let* ((image-name? (image-drawing-element-image-name drawing-element))
	       (image-definition? (and image-name?
				       (find-image-named image-name?))))
	  (cond ((and image-name? (null image-definition?))
		 (enqueue-icon-editor-visual-event 
		   icon-editor
		   (icon-editor-visual-event 'inform-user)
		   (twith-output-to-text-string
		     (tformat "Note that there is currently no image named ~a" image-name?))
		   nil))
		((and image-definition? (frame-incomplete-p image-definition?))
		 (enqueue-icon-editor-visual-event 
		   icon-editor
		   (icon-editor-visual-event 'inform-user)
		   (twith-output-to-text-string
		     (tformat "Note that the image ~a is currently incomplete" image-name?))
		   nil))
		(t
		 ;; Remove the error message, if any.
		 (enqueue-icon-editor-visual-event 
		   icon-editor
		   (icon-editor-visual-event 'inform-user)
		   (icon-editor-translator-state (icon-editor-translator icon-editor))
		   nil))))))))



(defun-substitution-macro set-outline-color-in-icon-editor
				    (icon-editor new-color)
  (let* ((icon-editor-engine (icon-editor-engine icon-editor))
	 (current-region?
	   (icon-editor-engine-outline-region? icon-editor-engine))
	 (old-color?
	   (get-color-of-region-in-icon-editor icon-editor current-region?)))
    (if old-color?
	(set-color-of-region-in-icon-editor
	  icon-editor old-color? nil))
    (when (not (eq old-color? new-color))
      ;;
      ;; WORK TO BE DONE HERE!
      ;; . Call enqueue-icon-editor-visual-event to change color of region
      ;; . Remember to update the color of the main color menu if the outline
      ;;   has the same region
      
      (setf (icon-editor-engine-outline-color icon-editor-engine)
	    new-color))))



(defun-substitution-macro set-outline-region-in-icon-editor
				    (icon-editor color-region)
  (setf (icon-editor-engine-outline-region?
	  (icon-editor-engine icon-editor)) color-region))





(defun extract-icon-description-from-icon-editor (icon-editor)
  (let* ((class-definition (icon-editor-class-definition icon-editor))
	 (serial-number (icon-editor-reference-serial-number icon-editor)))
    (when (frame-has-not-been-reprocessed-p class-definition serial-number)
      (let* ((engine (icon-editor-engine icon-editor))
	     (drawing-elements-present?
	       (loop for layer in (icon-editor-engine-layers engine)
		     thereis (drawing-elements-of-layer layer)))
	     (stipple-spec
	       (icon-editor-stipple-spec icon-editor))
	     (icon-description?
	       (if drawing-elements-present?
		   (convert-list-of-layers-to-line-drawing-description
		     (icon-editor-engine-layers engine)
		     (icon-editor-region-and-name-alist icon-editor)
		     (icon-editor-variable-spec-list icon-editor) ; pbk
		     (icon-editor-icon-background-image icon-editor)
		     (icon-editor-engine-icon-width engine)
		     (icon-editor-engine-icon-height engine)
		     (icon-editor-normalized-scale-factor)
		     (icon-editor-normalized-scale-factor)
		     nil nil stipple-spec))))
	icon-description?))))
    
;;; The function `update-class-definition' parses the drawing
;;; description into the object definition.

(defun update-class-definition-for-icon-editor (icon-editor)
  (let ((class-definition (icon-editor-class-definition icon-editor)))
    ;; Make sure we still really have an icon to edit, since a class can be
    ;; edited to no longer inherit from an iconish class [like rule] while the
    ;; icon-editor is still open. -dkuznick, 10/26/98 
    (if (class-definition-defines-user-editable-icon-class-p class-definition)
	(progn
	  (change-slot-value class-definition
			     'icon-description-for-class?
			     (extract-icon-description-from-icon-editor
			      icon-editor))
	  ;; Record the icon modified by icon-editor in change-log. 
	  (update-change-log-attribute class-definition 
				       (get-slot-description-of-frame 'icon-description-for-class? class-definition nil)
				       nil))
	(notify-user "Error: Could not accept edit for ~NF. The value of the direct-superior-classes attribute on the ~
          class-definition does not indicate that the class has a changeable icon-description."
		     class-definition))))
  

;;; The function `end-editing-of-icon-editor' tries to parse the icon designed
;;; in the icon editor into the class definition.  It then destroys the icon
;;; editor instance and the clean up procedure will reclaim
;;; all data structures associated with the icon editor.

(defun-substitution-macro end-editing-of-icon-editor (icon-editor)
  (update-class-definition-for-icon-editor icon-editor)
  ;; We only need to delete the workspace.  After the workspace
  ;; has been deleted, the next event caught by the icon editor
  ;; context operation handler will cause an exit from the icon
  ;; editor context.
  (enqueue-icon-editor-visual-event
    icon-editor
    (icon-editor-visual-event 'delete-icon-editor-workspace)
    nil nil))






;;; The macro `convert-dotted-pair-to-list' ...

(defmacro convert-dotted-pair-to-list-1 (dotted-pair cons-function)
  (if (or (not (symbolp cons-function))
	  (not (search "-CONS" (symbol-name cons-function))))
      (error "The cons-function must be a symbol and contain `-CONS'."))
  (if (symbolp dotted-pair)
      `(progn
	 (setf (cdr ,dotted-pair) (,cons-function (cdr ,dotted-pair) nil))
	 ,dotted-pair)
      (error "dotted-pair should be a symbol.")))

(defmacro convert-dotted-pair-to-list (dotted-pair cons-function)
  ;; (convert-dotted-pair-to-list foo icon-editor-cons)
  (if (or (not (symbolp cons-function))
	  (not (search "-CONS" (symbol-name cons-function))))
      (error "The cons-function must be a symbol and contain `-CONS'."))
  (if (symbolp dotted-pair)
      `(convert-dotted-pair-to-list-1 ,dotted-pair ,cons-function)
      (let* ((dotted-pair-var (gensym)))
	`(let* ((,dotted-pair-var ,dotted-pair))
	   (convert-dotted-pair-to-list-1 ,dotted-pair-var ,cons-function)))))


(defun convert-list-of-dotted-pairs-to-list-of-lists (list-of-dotted-pairs)
  (loop for dotted-pair in list-of-dotted-pairs
	do (convert-dotted-pair-to-list dotted-pair icon-editor-cons))
  list-of-dotted-pairs)






;;; The function `handle-group-event-for-engine' returns t
;;; if the view-pad has to be redrawn, nil otherwise.

(defun-substitution-macro handle-group-event-for-engine (icon-editor)
  ;; Remember to keep history
  ;; WORK TO BE DONE HERE!
  (let* ((engine (icon-editor-engine icon-editor))
	 (current-layer-index
	   (icon-editor-engine-current-layer-index engine)))
    (cond
      ((<=f current-layer-index 0)
       (enqueue-icon-editor-visual-event
	 icon-editor
	 (icon-editor-visual-event 'inform-user)
	 (copy-text-string
	   "There is no layer below the current layer to group.")
	 nil)
       nil)
      (t
       (merge-icon-layers current-layer-index
			  (-f current-layer-index 1) icon-editor)
       (inform-user-of-current-regions icon-editor)
       (enqueue-icon-editor-visual-event
	 icon-editor
	 (icon-editor-visual-event 'resize-layer-boxes-if-necessary)
	 nil nil)
       t))))




(defun handle-new-layer-creation-in-engine (icon-editor new-layer-index
					    region? color
					    new-layer-drawing-elements?)
  (let* ((engine (icon-editor-engine icon-editor)))
    (set-color-of-region-in-icon-editor
      icon-editor (or region? color) color)
    (new-icon-layer
      (or region? color)
      new-layer-drawing-elements? new-layer-index engine)
    (reset-current-layer engine new-layer-index)
    (enqueue-icon-editor-engine-event
      icon-editor
      (icon-editor-engine-event 'update-main-label)
      (label-of-layer (icon-editor-engine-current-layer engine))
      (image-of-layer? (icon-editor-engine-current-layer engine))
      (text-of-layer? (icon-editor-engine-current-layer engine)) ; (pbk 2/6/96)
      (stipple-of-layer? (icon-editor-engine-current-layer engine)))
    (enqueue-icon-editor-visual-event
      icon-editor
      (icon-editor-visual-event 'resize-layer-boxes-if-necessary)
      nil nil)))



(defun-substitution-macro handle-new-empty-layer-creation-in-engine (icon-editor new-layer-index)
  (let* ((engine (icon-editor-engine icon-editor)))
    (handle-new-layer-creation-in-engine
      icon-editor new-layer-index nil
      (icon-editor-engine-main-color engine) nil)))





;;; The function `handle-delete-current-layer-event-for-engine' returns t
;;; if the view-pad has to be redrawn, nil otherwise.  If nil is returned,
;;; a message has also been sent to the user that the command was not
;;; carried out.

(defun handle-delete-current-layer-for-engine
    (icon-editor deleting-drawing-element-p?)
  ;; Remember to keep history
  ;; WORK TO BE DONE HERE!
  (let* ((engine (icon-editor-engine icon-editor))
	 (number-of-layers
	   (icon-editor-engine-number-of-layers engine)))
    (cond
      ((or (=f number-of-layers 0)
	   (and (=f number-of-layers 1)
		(null (drawing-elements-of-layer
			(icon-editor-engine-current-layer engine)))))
       (enqueue-icon-editor-visual-event
	 icon-editor
	 (icon-editor-visual-event 'inform-user)
	 (copy-text-string 
	   (if deleting-drawing-element-p?
	       "No more drawing elements to pop."
	       "No more layers to delete."))
	 nil)
       ;; Disable redraw
       nil)
      (t
       (let* ((old-label
		(label-of-layer
		  (icon-editor-engine-current-layer engine))))
	 (let* ((layer-index-to-delete
		  (icon-editor-engine-current-layer-index engine))
		(layer-to-delete
		  (delete-specific-layer layer-index-to-delete engine))
		(layer-to-delete-is-empty-p (null (drawing-elements-of-layer
						    layer-to-delete))))
	   (reclaim-layer layer-to-delete)
	   (when (>f (icon-editor-engine-current-layer-index engine) 0)
	     (decff (icon-editor-engine-current-layer-index engine))
	     (reset-current-layer
	       engine (maxf (-f layer-index-to-delete 1) 0)))
	   (enqueue-icon-editor-visual-event
	     icon-editor			; this will resize if necessary
	     (icon-editor-visual-event 'delete-layer-in-layers-pad)
	     layer-index-to-delete nil)

	   (cond ((=f (icon-editor-engine-number-of-layers engine) 0)	;must have at least one
		  (handle-new-empty-layer-creation-in-engine
		    icon-editor 0))
		 (t
		  (set-color-of-region-in-icon-editor icon-editor old-label nil)
		  (inform-user-of-current-regions icon-editor)
		  (enqueue-icon-editor-engine-event
		    icon-editor
		    (icon-editor-engine-event 'update-main-label)
		    (label-of-layer (icon-editor-engine-current-layer engine))
		    (image-of-layer? (icon-editor-engine-current-layer engine))
		    (text-of-layer? (icon-editor-engine-current-layer engine))
		    (stipple-of-layer? (icon-editor-engine-current-layer engine)))))
	   (when (not layer-to-delete-is-empty-p)
	     (enqueue-icon-editor-visual-event
	       icon-editor
	       (icon-editor-visual-event 'redraw-view-pad-icon)
	       nil nil))))
       t))))




(defun handle-changing-current-layer-in-engine (icon-editor new-layer-index)
  (let* ((engine (icon-editor-engine icon-editor))
	 (number-of-layers
	   (icon-editor-engine-number-of-layers engine)))
    (cond
      ((<f new-layer-index 0)
       (enqueue-icon-editor-visual-event
	 icon-editor
	 (icon-editor-visual-event 'inform-user)
	 (copy-constant-wide-string #w"No layer below the current layer.")
	 nil))
      ((>=f new-layer-index number-of-layers)
       (enqueue-icon-editor-visual-event
	 icon-editor
	 (icon-editor-visual-event 'inform-user)
	 (copy-constant-wide-string #w"No layer above the current layer.")
	 nil))
      (t
       (let* ((old-layer-index (icon-editor-engine-current-layer-index engine)))
	 (declare (type fixnum old-layer-index))
	 (setf (icon-editor-engine-current-layer-index engine)
	       new-layer-index)
	 (setf (icon-editor-engine-current-layer engine)
	       (nth new-layer-index
		    (icon-editor-engine-layers engine)))
	 (enqueue-icon-editor-visual-event
	   icon-editor
	   (icon-editor-visual-event
	     'change-current-layer-in-layers-pad)
	   old-layer-index new-layer-index)
	 (let* ((current-label (label-of-layer (icon-editor-engine-current-layer engine)))
		(current-image (image-of-layer? (icon-editor-engine-current-layer engine)))
		(current-text (text-of-layer? (icon-editor-engine-current-layer engine)))
		(current-stipple (stipple-of-layer? (icon-editor-engine-current-layer engine))))
	   (enqueue-icon-editor-engine-event
	     icon-editor
	     (icon-editor-engine-event 'update-main-label)
	     current-label
	     current-image
	     current-text   ; (pbk 2/6/96)
	     current-stipple)))))))





(defun-substitution-macro handle-fill-or-outline-current-layer
    (icon-editor engine fill? icon-width icon-height)
  (let* ((current-layer
	   (icon-editor-engine-current-layer engine))
	 (current-drawing-elements?
	   (drawing-elements-of-layer current-layer)))
    (cond
      (current-drawing-elements?
       (let* ((variable-spec-list
		(cdr (icon-editor-variable-spec-list icon-editor)))
	      (new-drawing-elements?
		(evaluating-icon-elements
		  (icon-width icon-height variable-spec-list nil)
		  (if fill?
		      (convert-to-filled-drawing-elements
			current-drawing-elements?)
		      (convert-to-outlined-drawing-elements
			current-drawing-elements?)))))
	 (cond
	   (new-drawing-elements?
	    ;(reclaim-icon-editor-slot-value ;temp leak/fix (pbk)
	    ;  current-drawing-elements?)
	    (setf (drawing-elements-tail-of-layer current-layer)
		  (last new-drawing-elements?))
	    (setf (drawing-elements-of-layer current-layer)
		  new-drawing-elements?)
	    (reclaim-icon-editor-slot-value
	      (layer-box?-of-layer current-layer))
	    (setf (layer-box?-of-layer current-layer) nil)
	    (enqueue-icon-editor-visual-event
	      icon-editor
	      (icon-editor-visual-event 'redraw-current-layer-box)
	      nil nil)
	    (enqueue-icon-editor-visual-event
	      icon-editor
	      (icon-editor-visual-event 'redraw-view-pad-icon)
	     nil nil))
	   (t
	    (enqueue-icon-editor-visual-event
	      icon-editor
	      (icon-editor-visual-event 'inform-user)
	      (copy-text-string
		(if fill?
		    "Nothing in the current layer needs to be filled."
		    "Nothing in the current layer needs to be outlined."))
	      nil)))))
      (t
       (enqueue-icon-editor-visual-event
	 icon-editor
	 (icon-editor-visual-event 'inform-user)
	 (copy-text-string
	   (if fill?
	       "Can't fill an empty layer."
	       "Can't outline an empty layer."))
	 nil)))))



(defun handle-move-layer-along-z-axis-in-engine
    (icon-editor old-layer-index new-layer-index)
  (let* ((index-after-new-layer-index (+f new-layer-index 1))
	 (engine (icon-editor-engine icon-editor)))
    (move-icon-layer old-layer-index index-after-new-layer-index engine)
    (reset-current-layer engine (maxf new-layer-index 0)))
  t)




(defun handle-move-layer-in-xy-plane-in-engine
    (icon-editor engine x-offset y-offset)
  (let* ((layer
	   (icon-editor-engine-current-layer engine))
	 (drawing-elements   (drawing-elements-of-layer layer)))
    
    (when drawing-elements
      (shift-drawing-elements-in-place
	drawing-elements  x-offset y-offset)
      (reclaim-icon-editor-slot-value (layer-box?-of-layer layer))

      ;; Need to update the image and/or text offsets in the table rep.
      (let ((image?
	      (loop for drawing-element in drawing-elements
		    when (eq (car drawing-element) 'image)
		      return drawing-element))
	    (text?  ; (pbk 2/6/96)
	      (loop for drawing-element in drawing-elements
		    when (eq (car drawing-element) 'text)
		      return drawing-element))
	    (stipple?
	      (loop for drawing-element in drawing-elements
		    when (eq (car drawing-element) 'stippled-area)
		      return drawing-element)))
	(when image?
	  (enqueue-icon-editor-visual-event
	    icon-editor
	    (icon-editor-visual-event 'change-main-image)
	    image?					    ; Copied by change-main-image
	    nil))
	(when text?  
	  (enqueue-icon-editor-visual-event
	    icon-editor
	    (icon-editor-visual-event 'change-text)
	    text?
	    nil))
	(when stipple?  
	  (enqueue-icon-editor-visual-event
	    icon-editor
	    (icon-editor-visual-event 'change-stipple)
	    stipple?
	    nil)))

      (setf (layer-box?-of-layer layer) nil)
      (enqueue-icon-editor-visual-event
	icon-editor
	(icon-editor-visual-event 'redraw-view-pad-icon)
	nil nil)
      (enqueue-icon-editor-visual-event
	icon-editor
	(icon-editor-visual-event 'redraw-current-layer-box)
	nil nil))))






;;; The function `enqueue-icon-editor-engine-event' is the entry point into
;;; the icon editor engine.  All events which involve the changing of the
;;; icon description at the line drawing element goes through this function.
;;; Only the events translator should call this function.

;;; Returns nil if the event could not be executed; non-nil otherwise.

(defun enqueue-icon-editor-engine-event (icon-editor engine-event
					 arg-1? arg-2? arg-3? arg-4?)
  #-development
  (declare (type fixnum engine-event))
  #+development (and (icon-editor-p icon-editor)
		     (icon-editor-engine-event-p engine-event))


  (let* ((current-layer-changed-p nil)
	 (redraw-view-pad-p nil)
	 (drawing-failed-p nil))
    (if (icon-editor-killed-p icon-editor)
	(progn
	  (reclaim-icon-editor-tree arg-1?)
	  (reclaim-icon-editor-tree arg-2?)
	  (reclaim-icon-editor-tree arg-3?)
	  (reclaim-icon-editor-tree arg-4?)
	  (abort-current-workstation-context 'icon-editor))
	(let* ((engine (icon-editor-engine icon-editor)))
	  ;; WORK TO BE DONE HERE!
	  (icon-editor-engine-event-case engine-event

	    (change-icon-size
	      (change-size-of-icon-in-icon-editor icon-editor arg-1? arg-2?))
	    (change-icon-width
	      (change-size-of-icon-in-icon-editor
		icon-editor arg-1? (icon-editor-engine-icon-height
				     (icon-editor-engine icon-editor))))
	    (change-icon-height
	      (change-size-of-icon-in-icon-editor
		icon-editor (icon-editor-engine-icon-width
			      (icon-editor-engine icon-editor)) arg-1?))

	    (end-changing-icon-size
	      (enqueue-icon-editor-visual-event
		icon-editor
		(icon-editor-visual-event 'change-view-pad-bounding-box-width)
		(delta-x-in-workspace-from-view-pad
		  (icon-editor-engine-icon-width engine)
		  (icon-editor-view-pad icon-editor))
		nil)
	      (enqueue-icon-editor-visual-event
		icon-editor
		(icon-editor-visual-event 'change-view-pad-bounding-box-height)
		(delta-y-in-workspace-from-view-pad
		  (icon-editor-engine-icon-height engine)
		  (icon-editor-view-pad icon-editor))
		nil)

	      ;; Added to update image clipping, etc, when user moves the
	      ;; bounding box.  A long-standing bug, as far as I know.
	      ;; -fmw, 4/19/94
	      (enqueue-icon-editor-visual-event
		icon-editor
		(icon-editor-visual-event 'redraw-view-pad-icon)
		nil nil)

	      (enqueue-icon-editor-visual-event
		icon-editor
		(icon-editor-visual-event 'redraw-all-layer-boxes)
		nil nil))

	    (shrink-wrap
	      (shrink-wrap-icon-in-icon-editor icon-editor))
	    
	    (set-main-color
	      (set-main-color-in-icon-editor icon-editor arg-1?))
	    (set-main-region
	      (set-main-region-in-icon-editor icon-editor arg-1?)
	      (inform-user-of-current-regions icon-editor))

	    (set-main-image
	      (setq current-layer-changed-p
		    (set-main-image-in-icon-editor icon-editor arg-1?)))
	    
	    (set-text           ; (pbk 2/6/96)
	      (setq current-layer-changed-p
		    (set-text-in-icon-editor icon-editor arg-1?)))
	    
	    (set-stipple
	      (setq current-layer-changed-p
		    (set-stipple-in-icon-editor icon-editor arg-1?)))
	    (set-global-stipple
	      (setq current-layer-changed-p
		    (set-global-stipple-in-icon-editor icon-editor arg-1?)))

	    ;; Future work:		-pto 07oct89
	    (set-outline-color
	      (set-outline-color-in-icon-editor icon-editor arg-1?))
	    (set-outline-region
	      (set-outline-region-in-icon-editor icon-editor arg-1?))
	    
	    (new-layer				; args: 
	      ;; WORK TO BE DONE HERE!
	      (handle-new-empty-layer-creation-in-engine
		icon-editor
		(+f (icon-editor-engine-current-layer-index engine) 1)))
	    
	    (cancel-editing
	      ;; Be nice about this.  Ask use if he/she really wants to quit
	      ;; and flush all the work put in so far.
	      
	      ;; We only need to delete the workspace.  After the workspace
	      ;; has been deleted, the next event caught by the icon editor
	      ;; context operation handler will cause an exit from the icon
	      ;; editor context.

	      ;; See notes by MHD in EDIT by
	      ;;   def-workstation-event-type abort-editing
	      ;; on this subject! (MHD 10/27/89)
	      ;;
	      ;; This is currently dead code -- see execute-icon-editor-
	      ;;   workstation-event. (MHD/PTO 10/27/89)
	      (enqueue-icon-editor-visual-event
		icon-editor
		(icon-editor-visual-event 'delete-icon-editor-workspace)
		nil  nil))
	    
	    (end-editing
	      (end-editing-of-icon-editor icon-editor))
	    
	    (group
	      (setq redraw-view-pad-p
		    (handle-group-event-for-engine icon-editor))
	      (let ((current-layer
			 (icon-editor-engine-current-layer engine)))
		(when current-layer
		  (enqueue-icon-editor-engine-event
		    icon-editor
		    (icon-editor-engine-event 'update-main-label)
		    (label-of-layer current-layer)
		    (image-of-layer? current-layer)
		    (text-of-layer? current-layer)
		    (stipple-of-layer? current-layer)))))
	    (ungroup-current-layer
	      (let* ((current-layer
		       (icon-editor-engine-current-layer engine))
		     (number-of-elements
		       (length (drawing-elements-of-layer current-layer))))
		(declare (type fixnum number-of-elements))
		(cond
		  ((<f number-of-elements 2)
		   (enqueue-icon-editor-visual-event
		     icon-editor
		     (icon-editor-visual-event 'inform-user)
		     (copy-constant-wide-string #w"Current layer is too small to ungroup.")
		     nil))
		  (t
		   (explode-icon-layer (icon-editor-engine-current-layer-index engine)
				       icon-editor)

		   (enqueue-icon-editor-visual-event
		     icon-editor
		     (icon-editor-visual-event
		       'resize-layer-boxes-if-necessary)
		     nil nil)
		   (setf current-layer
			 (icon-editor-engine-current-layer engine))
		   (when current-layer
		     (let ((current-label (label-of-layer current-layer))
			   (current-image (image-of-layer? current-layer))
			   (current-text (text-of-layer? current-layer))
			   (current-stipple (stipple-of-layer? current-layer)))
		       (enqueue-icon-editor-engine-event
			 icon-editor
			 (icon-editor-engine-event 'update-main-label)
			 current-label
			 current-image
			 current-text
			 current-stipple)))
		   (setq redraw-view-pad-p t)))))
	    (delete-current-layer
	      (handle-delete-current-layer-for-engine icon-editor nil))
	    (draw-point				; args: x,y, nil, nil
	      ;; Remember to keep history
	      ;; WORK TO BE DONE HERE!
	      (add-element-to-current-layer
		engine
		(icon-editor-list 'point (icon-editor-list arg-1? arg-2?)))
	      (setq current-layer-changed-p t))
	    (draw-points			; args: ((x . y) ...), nil, nil, nil
	      ;; Remember to keep history
	      ;; WORK TO BE DONE HERE!
	      (loop for (x-value . y-value) in arg-1?
		    do (add-element-to-current-layer
			 engine
			 (icon-editor-list 'point (icon-editor-list x-value y-value))))
	      (reclaim-icon-editor-tree arg-1?)
	      (setq current-layer-changed-p t))
	    (draw-line				; args: x0, y0, x1, y1
	      ;; Remember to keep history
	      ;; WORK TO BE DONE HERE!
	      #+development (gensym-assert (and (typep arg-1? 'fixnum)
						(typep arg-2? 'fixnum)
						(typep arg-3? 'fixnum)
						(typep arg-4? 'fixnum)))
	      (add-element-to-current-layer
		engine (icon-editor-list
			 'lines
			 (icon-editor-list arg-1? arg-2?)
			 (icon-editor-list arg-3? arg-4?)))
	      (setq current-layer-changed-p t))
	    (draw-lines				; args: ((x . y) ... ), nil, nil, nil
	      ;; Remember to keep history
	      ;; WORK TO BE DONE HERE!
	      (add-element-to-current-layer
		engine (icon-editor-cons
			 'lines
			 (convert-list-of-dotted-pairs-to-list-of-lists 
			   arg-1?)))
	      (setq current-layer-changed-p t))
	    (draw-arc				; args: (x0.y0), (x1.y1), (x2.y2), nil
	      ;; Remember to keep history
	      ;; WORK TO BE DONE HERE!
	      (add-element-to-current-layer
		engine
		(icon-editor-list
		  'lines
		  (convert-dotted-pair-to-list arg-1? icon-editor-cons)
		  (icon-editor-list 'arc (convert-dotted-pair-to-list
					   arg-2? icon-editor-cons))
		  (convert-dotted-pair-to-list arg-3? icon-editor-cons)))
	      (setq current-layer-changed-p t))
	    (draw-outlined-rectangle		; (37) args: x0, y0, x1, y1
	      ;; WORK TO BE DONE HERE!
	      (add-element-to-current-layer
		engine
		(icon-editor-list
		  'outline
		  (icon-editor-list arg-1? arg-2?)
		  (icon-editor-list arg-1? arg-4?)
		  (icon-editor-list arg-3? arg-4?)
		  (icon-editor-list arg-3? arg-2?)))
	      (setq current-layer-changed-p t))
	    (draw-outlined-polygon		; args: ((x . y) ... ), nil, nil, nil
	      ;; WORK TO BE DONE HERE!
	      (add-element-to-current-layer
		engine
		(icon-editor-cons
		  'outline
		  (convert-list-of-dotted-pairs-to-list-of-lists 
		    arg-1?)))
	      (setq current-layer-changed-p t))
	    (draw-outlined-circle		; args: x0, y0, radius, nil
	      ;; WORK TO BE DONE HERE!
	      (add-element-to-current-layer
		engine
		(icon-editor-list
		  'circle
		  (icon-editor-list (-w arg-1? arg-3?) arg-2?)
		  (icon-editor-list arg-1? (-w arg-2? arg-3?))
		  (icon-editor-list (+w arg-1? arg-3?) arg-2?)))
	      (setq current-layer-changed-p t))
	    (draw-filled-rectangle		; args: x0, y0, x1, y1
	      ;; WORK TO BE DONE HERE!
	      (add-element-to-current-layer
		engine
		(icon-editor-list
		  'solid-rectangle
		  (icon-editor-list arg-1? arg-2?)
		  (icon-editor-list arg-3? arg-4?)))
	      (setq current-layer-changed-p t))
	    (draw-filled-polygon		; args: ((x . y) ... ), nil, nil, nil
	      ;; WORK TO BE DONE HERE!
	      (convert-list-of-dotted-pairs-to-list-of-lists arg-1?)
	      ;; Filled polygons should be clockwise
	      (unless (clockwise-polygon-p arg-1?)
		(setq arg-1? (nreverse arg-1?)))

	      (let* ((decomposed-polygon?
		       (decompose-polygon-using-icon-editor-conses arg-1?)))
		(if decomposed-polygon?
		    (progn
		      (add-element-to-current-layer
			engine
			(icon-editor-cons
			  'filled-polygon
			  (icon-editor-cons
			    arg-1?
			    decomposed-polygon?)))
		      (setq current-layer-changed-p t))
		    (progn
		      (setf drawing-failed-p t)
		      (enqueue-icon-editor-visual-event
			icon-editor
			(icon-editor-visual-event 'inform-user)
			(copy-text-string 
			  "The polygon was rejected because it was not a simple polygon.")
			nil)))))
	    (draw-filled-circle			; args: x0, y0, radius, nil
	      ;; WORK TO BE DONE HERE!
	      (add-element-to-current-layer
		engine
		(icon-editor-list
		  'filled-circle
		  (icon-editor-list (-w arg-1? arg-3?) arg-2?)
		  (icon-editor-list arg-1? (-w arg-2? arg-3?))
		  (icon-editor-list (+w arg-1? arg-3?) arg-2?)))
	      (setq current-layer-changed-p t))
	    (draw-outlined-filled-rectangle	; args: x0, y0, x1, y1
	      ;; WORK TO BE DONE HERE!
	      )
	    (draw-outlined-filled-polygon	; args: ((x . y) ... ), nil, nil, nil
	      ;; WORK TO BE DONE HERE!
	      )
	    (draw-outlined-filled-circle	; args: x0, y0, radius, nil
	      ;; WORK TO BE DONE HERE!
	      )
	    (change-current-layer-to-layer-above
	      (handle-changing-current-layer-in-engine
		icon-editor (+f (icon-editor-engine-current-layer-index engine) 1)))
	    (change-current-layer-to-layer-below
	      (handle-changing-current-layer-in-engine
		icon-editor (-f (icon-editor-engine-current-layer-index engine) 1)))
	    (change-current-layer		; args: new-layer-index, nil, nil, nil
	      (handle-changing-current-layer-in-engine icon-editor arg-1?))

	    (update-main-label			; args: new-label, new-image, new-text, nil
	      ;; Added new-image, which is the list (image image-name [point]).
	      (let* ((new-color
		       (or (get-color-of-region-in-icon-editor icon-editor arg-1?)
			   arg-1?))
		     (new-region?		  
		       (if (illegal-region-name-p arg-1?) nil arg-1?))
		     (new-image? arg-2?)
		     (new-text? arg-3?)
		     (new-stipple? arg-4?))

		;; N.B.  engine is not a %^&*ing frame - must reclaim old values
		;;       by hand. Only reclaiming the text-drawing-elements for now
		;;       and not reclaiming image slot. ; (pbk 2/6/96)
		
		(when (icon-editor-engine-text? engine)  
		  (reclaim-icon-editor-slot-value (icon-editor-engine-text? engine)))
		
	       ;(when (icon-editor-engine-main-image? engine)
       	       ;  (reclaim-slot-value (icon-editor-engine-main-image? engine)))
		
		(setf (icon-editor-engine-main-region? engine) new-region?
		      (icon-editor-engine-main-color engine) new-color
		      (icon-editor-engine-main-image? engine)
		      (copy-tree-using-slot-value-conses new-image?) ;why slot value?? pbk
		      (icon-editor-engine-text? engine)    
		      (copy-drawing-element-with-icon-editor-conses new-text? nil nil)
		      (icon-editor-engine-stipple? engine)    
		      (copy-drawing-element-with-icon-editor-conses new-stipple? nil nil))
		(enqueue-icon-editor-visual-event
		  icon-editor
		  (icon-editor-visual-event 'change-main-region)
		  new-region? nil)
		(enqueue-icon-editor-visual-event
		  icon-editor
		  (icon-editor-visual-event 'change-main-color)
		  new-color nil)
		(enqueue-icon-editor-visual-event
		  icon-editor
		  (icon-editor-visual-event 'change-main-image)
		  new-image? nil)
		(enqueue-icon-editor-visual-event
		  icon-editor
		  (icon-editor-visual-event 'change-text)
		  new-text? nil)
		(enqueue-icon-editor-visual-event
		  icon-editor
		  (icon-editor-visual-event 'change-stipple)
		  new-stipple? nil)))

	    (delete-most-recent-drawing-element
	      (let* ((current-layer
		       (icon-editor-engine-current-layer engine))
		     (drawing-elements
		       (drawing-elements-of-layer current-layer))
		     (number-of-drawing-elements (length drawing-elements))
		     (clear-info-box-p nil))
		(cond
		  ((<=f number-of-drawing-elements 0)
		   (setq clear-info-box-p
			 (handle-delete-current-layer-for-engine icon-editor t)))
		  (t (delete-last-element-from-current-layer engine)
		     (setq current-layer-changed-p t)))
		(setf current-layer
		      (icon-editor-engine-current-layer engine))
		(when current-layer
		  (let ((current-label (label-of-layer current-layer))
			(current-image (image-of-layer? current-layer))
			(current-text (text-of-layer? current-layer))
			(current-stipple (stipple-of-layer? current-layer)))
		    (enqueue-icon-editor-engine-event
		      icon-editor
		      (icon-editor-engine-event 'update-main-label)
		      current-label
		      current-image
		      current-text
		      current-stipple)))
		(when clear-info-box-p
		  (enqueue-icon-editor-visual-event
		    icon-editor
		    (icon-editor-visual-event 'inform-user)
		    (icon-editor-state 'waiting)
		    nil))))
	    (update-class-definition
	      (update-class-definition-for-icon-editor icon-editor)
	      (enqueue-icon-editor-visual-event
			icon-editor
			(icon-editor-visual-event 'inform-user)
			(twith-output-to-text-string
			  (twrite-string "Icon description updated ")
			  (let* ((name-or-names
				   (name-or-names-for-frame
				     (icon-editor-class-definition icon-editor))))
			    (cond
			      ((null name-or-names)
			       (twrite-string "to the class definition."))
			      (t
			       (tformat "for ~a." 
			       (if (listp name-or-names)
				   (car name-or-names)
				   name-or-names))))))
			nil))
	    (move-layer-along-z-axis		; args: old-index, new-index, nil, nil
	      (handle-move-layer-along-z-axis-in-engine icon-editor arg-1? arg-2?)
	      (setq redraw-view-pad-p t)
	      (enqueue-icon-editor-visual-event
		icon-editor
		(icon-editor-visual-event 'redraw-layers-in-layers-pad)
		nil nil))

	    (move-layer-in-xy-plane		; args: x-offset-in-view-pad, y-offset-in-view-pad,
						;   nil, nil
	      ;; (format t "~&(~a,~a)~%" arg-1? arg-2?)
	      (handle-move-layer-in-xy-plane-in-engine
		icon-editor engine arg-1? arg-2?)
	      ;;
	      ;; MORE WORK HERE!
	      ;; Offset layer, update drawing elements of current layer,
	      ;; and refresh screens.
	      ;;
	      )
	    (clone-current-layer
	      (handle-new-layer-creation-in-engine
		icon-editor
		(icon-editor-engine-current-layer-index engine)
		nil
		(icon-editor-engine-main-color engine)
		(copy-tree-including-leaves-using-icon-editor-conses ; (pbk 2/6/96)
		  (drawing-elements-of-layer
		    (icon-editor-engine-current-layer engine)))))

	    ((fill-current-layer outline-current-layer)
	      (handle-fill-or-outline-current-layer
		icon-editor engine
		(=f engine-event
		    (icon-editor-engine-event 'fill-current-layer))
		(icon-editor-engine-icon-width
		  (icon-editor-engine icon-editor))
		(icon-editor-engine-icon-height
		  (icon-editor-engine icon-editor))))

	    #+development
	    (t
	      (format 
		t "~%Illegal engine event command ~a in handle-icon-editor-engine-event.~%"
		engine-event
		)))))
    (when current-layer-changed-p
      (enqueue-icon-editor-visual-event
	icon-editor
	(icon-editor-visual-event 'redraw-current-layer-box)
	nil nil))
    (when (or redraw-view-pad-p current-layer-changed-p)
      (enqueue-icon-editor-visual-event
	icon-editor
	(icon-editor-visual-event 'redraw-view-pad-icon)
	nil nil))
    drawing-failed-p))


;; Output from the engine:

;;; handle-icon-editor-visual-event:

;; move-icon-layer <source-layer-index> <before-or-after> <target-layer-index>
;; delete-icon-layer <layer-index>
;; new-icon-layer <list-of-line-drawing-elements>







;;;; Consistency analysis



;; Attempt to update the icon editor when an image it references changes.


(defun icon-editor-for-icon-editor-workspace (workspace)
  (let* ((image-plane? (first (image-planes-this-is-on workspace)))
	 (pane? (and image-plane? (pane-for-image-plane image-plane?)))
	 (window? (and pane? (gensym-window-for-pane pane?)))
	 (workstation? (and window? (workstation-this-is-on window?)))
	 (context-stack (and workstation? (workstation-context-stack workstation?))))
    (loop for context in context-stack
	  as icon-editor? = (and (eq (type-of-workstation-context context) 'icon-editor)
				 (specific-structure-for-workstation-context context))
	  when (and icon-editor?
		    (eq (icon-editor-workspace icon-editor?) workspace))
	    do (return icon-editor?))))

;; What a load of commie bull.

				      

(define-analyze-for-consistency icon-editor-workspace
  (when (ok-to-do-name-consistency-analysis?)
    (delete-all-consistency-analysis-frame-notes icon-editor-workspace)

    (let* ((icon-editor? (icon-editor-for-icon-editor-workspace icon-editor-workspace))
	   (engine? (and icon-editor? (icon-editor-engine icon-editor?)))
	   (layers (and engine? (icon-editor-engine-layers engine?))))

      (when layers
	(let ((compiled-item-being-analyzed icon-editor-workspace)
	      (any? nil))
	  (analyze-consistency-of-block icon-editor-workspace)
	  (loop for layer in layers doing
	    (loop for drawing-element in (drawing-elements-of-layer layer) doing
	      (when (image-drawing-element-p drawing-element)
		(let ((image-name? (image-drawing-element-image-name drawing-element)))
		  (when image-name?
		    (check-undefined-instances-of-class image-name? 'image-definition)
		    (setq any? t))))))

	  (when (and any? (checking-for-consistency-analysis-p))
	    (update-icon-editor-status icon-editor?)
	    (enqueue-icon-editor-visual-event
	      icon-editor?
	      (icon-editor-visual-event 'redraw-all-layer-boxes)
	      nil nil)
	    (enqueue-icon-editor-visual-event
	      icon-editor?
	      (icon-editor-visual-event 'redraw-view-pad-icon)
	      nil nil)))))))

;; What a load of commie bull.

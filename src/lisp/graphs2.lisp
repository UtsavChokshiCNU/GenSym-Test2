;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module GRAPHS2

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Andreas Hofmann





;;;; Updating and Formatting Graphs

;;; Updating a graph causes only the data to be redrawn unless the
;;; grid format changes, in which case, the grid is redrawn also.
;;; In most cases, data points are simply being added, so the old
;;; data doesn't have to be redrawn.

;; The graph is updated simply by calling make-or-reformat-graph-grid
;; which does all the work.  Since no plot arguments are specified in
;; this call, each plot in the graph will be refreshed.  However, since
;; plots can be passed as arguments, it is possible to eventually
;; selectively update individual plots.

;; See also the other display update definitions in DISPLAYS.

;; Creates a function called update-display-for-graph

(define-update-display-function graph
  (unless (block-is-currently-being-dragged-p graph)
    (let ((redraw-as-well-as-reformat-p t)
	  (graph-grid
	    (get-graph-grid-given-graph graph)))
      (make-or-reformat-graph-grid
	nil
	graph-grid
	(graph-format graph)
	update-even-if-not-showing? t))))

;; When a graph is transferred, it is not updated since it is
;; deactivated.  The check to see if graph is being dragged inhibits
;; updating while the graph is being dragged.


(define-clear-display-function graph
  (let ((redraw-as-well-as-reformat-p nil)
	(graph-grid
	  (get-graph-grid-given-graph graph)))
    ;; unnecessary to erase the opaque block before painting over it. (MHD 6/24/92)
    ; (update-images-of-graph-grid-and-data t graph-grid)
    (loop for plot in (list-of-plots graph-grid)
	  doing (clear-plot plot))
    (make-or-reformat-graph-grid 
      nil
      graph-grid
      (graph-format graph)
      t nil)
    (unless transfer-in-progress			    ; -fmw, 2/15/95
      (update-images-of-graph-grid-and-data nil graph-grid)))
  (setf (graph-reformatted-since-start? graph) nil))

(defvar painting-for-graph-activation-p nil) 

(define-activate-method-for-display graph
  (setf (graph-reformatted-since-start? graph) nil)
  (let ((graph-grid?
	  (get-graph-grid-given-graph graph)))
    (when graph-grid?
      (make-graph-not-up-to-date graph-grid?)
      (let ((redraw-as-well-as-reformat-p
	      (if transfer-in-progress nil t)) ; -fmw, 2/14/95
	    (painting-for-graph-activation-p t))
	(make-or-reformat-graph-grid 
	  nil graph-grid? (graph-format graph) t t)))))

;; Graph-reformatted-since-start? is cleared here so that the horizontal axis
;; will be updated to show the correct universal times whenever the graph is 
;; activated (upon start, for example).

(define-deactivate-method-for-display graph)



;; Clear plot clears the data-buffer-for-plot.  The history buffer is cleared
;; by a separate mechanism during reset (see reset method for variables in 
;; "variables").  

(defun clear-plot (plot)
  (let ((data-buffer-for-plot
	  (data-buffer-for-plot plot))
	(current-block-of-dependent-frame
	  'dependent-frame-has-no-owner))
    (store-managed-number-or-value
      (x-data-minimum plot) nil)
    (store-managed-number-or-value
      (x-data-maximum plot) nil)
    (store-managed-number-or-value
      (most-recent-y-extremum plot) nil)
    (store-managed-number-or-value
      (opposite-y-extremum-of-most-recent plot) nil)

    ;; clear data-buffer-for-plot
    (when data-buffer-for-plot
      (set-oldest-active-element-index
	data-buffer-for-plot
	0)
      (set-newest-active-element-index
	data-buffer-for-plot
	0)
      (set-ring-buffer-empty?
	data-buffer-for-plot
	t)
      (clear-plot-marker-data data-buffer-for-plot))))

;; Shouldn't need to bind current-block-of-dependent-frame since none of
;; these slots are saved!



(defun make-horizontal-axis-graph-heading-text (graph)
  (make-horizontal-axis-graph-heading-text-1 graph 'expressions-to-display nil))

(defun make-horizontal-axis-graph-heading-text-1 (graph slot-name class-qualifier?)
  (make-text-cell-for-slot
    graph slot-name class-qualifier?
    (get-type-of-slot-if-any graph slot-name)
    (get-or-make-format-frame 
      'graph-horizontal-axis-heading-text-cell-format)))




(defun make-graph (graph-type) 
  (let* ((new-graph
	  (make-frame graph-type))
	 (new-graph-format
	   (get-or-make-format-frame 'default-graph-format))
	 (redraw-as-well-as-reformat-p nil)
	 new-graph-grid)
    (setf (graph-format new-graph)
	  new-graph-format)
    (setq new-graph-grid
	  (make-or-reformat-graph-grid 
	    new-graph nil (graph-format new-graph) nil nil))
    (setf (superblock? new-graph-grid) new-graph)
    (add-subblock new-graph-grid new-graph)
    (setf (table-rows new-graph)
	  (slot-value-list
	    (slot-value-list
	      new-graph-grid)
	    (slot-value-list
	      (make-horizontal-axis-graph-heading-text
		new-graph))))
    (make-or-reformat-table new-graph
			    (get-or-make-format-frame 'table-format-for-graphs)
			    nil)
    (put-up-label-for-graph-horizontal-axis new-graph-grid new-graph-format)
    (add-frame-representation-if-necessary new-graph new-graph)
    new-graph))

;; Subclasses of graph could be initialized with formats other than
;; default-graph-format.  Also, think about whether to pass in a graph
;; format (second arg of make-or-reformat-graph) in some way.  This
;; probably isn't too important since the format can always be edited in
;; the graph once it has been made.



(defvar minimum-grid-width)
(defvar minimum-grid-height)
(defvar desired-low-value-for-horizontal-axis)
(defvar desired-high-value-for-horizontal-axis)
(defvar desired-low-value-for-vertical-axis)
(defvar desired-high-value-for-vertical-axis)
(defvar number-of-horizontal-grid-lines)
(defvar number-of-vertical-grid-lines)
(defvar horizontal-grid-line-spacing)
(defvar vertical-grid-line-spacing)
(defvar low-value-for-horizontal-grid-lines)
(defvar high-value-for-horizontal-grid-lines)
(defvar interval-between-horizontal-grid-lines)
(defvar low-value-for-vertical-grid-lines)
(defvar high-value-for-vertical-grid-lines)
(defvar interval-between-vertical-grid-lines)
(defvar label-scale-for-vertical-grid-lines)



(defvar problems-reformatting-graph?)
(defvar finished-storing-in-plot-data-1?)

(defvar changing-graph-margins? nil)	; bound by slot-putter's for desired-range-for-<foo>-axis

;;; `Make-or-reformat-graph-grid' is called to either make or reformat a
;;; graph-grid.  If new-graph? is non-nil, then it is being made,
;;; otherwise it is being reformatted.  New-graph? must be an argument since
;;; when the graph-grid is being made, it is not yet a subblock of the
;;; graph.  If the graph-grid is being made, the graph-grid? argument
;;; will be nil.

;;; The horizontal-axis-grid-format-not-changed-p arg to refresh-data-for-plots
;;; controls whether a complete refresh of the plot data buffers is done or
;;; whether only new data is added.  This can make a big difference in
;;; efficiency.  

;;; Unless desired low and high values are specified for the vertical axis, the
;;; formatting of the vertical axis is determined by the data.  Thus, it is
;;; necessary to refresh the plot data buffers before reformatting the vertical
;;; axis.  Because the vertical axis format determines how data points are
;;; converted to workspace units, the conversion must be done after formatting of
;;; the vertical axis.  Thus, in cases where the vertical axis must be formatted,
;;; the plot data buffers are refreshed to contain data point rather than
;;; workspace unit values.  The vertical axis is then formatted.  Finally, the
;;; points in the plot data buffer are converted to workspace units by
;;; scale-y-data-for-plots-if-necessary.

;;; An optimization is attempted if horizontal-axis-grid-format-not-changed-p
;;; is t.  In this case, only a few data points are added to the plot data
;;; buffers and these are scaled to workspace units immediately, the assumption
;;; being that no vertical axis reformat will be necessary.  If one is, the
;;; optimization is abandoned and the entire plot data buffer is refreshed.
;;; This optimization is significant assuming that horizontal and vertical
;;; axes don't change often.  This is generally true since graphs are
;;; usually scrolling and have desired low and high values for the vertical
;;; axis specified.  Even in cases where the low and high values are not
;;; specified, vertical axis reformats are needed only occasionally.

;; The fact that scaling to workspace units must sometimes be done separately
;; (after) refreshing the plot data buffer and reformatting the vertical axis is
;; the main justification for existence of the plot data buffer.

(defun make-or-reformat-graph-grid 
    (new-graph? graph-grid? graph-format enforce-reformatting?
		refresh-plot-data-buffers? 
		&optional delta-left-edge? delta-top-edge?
		delta-right-edge? delta-bottom-edge?)
  (let () ; (current-drawing-transfer-mode :xor))
    (let* ((graph-grid (if graph-grid?
			   graph-grid?
			   (make-frame 'graph-grid)))
	   (graph (or new-graph? (superblock? graph-grid))))
      (with-named-dynamic-extent working-on-lexical-computation-of-frame
	  ((*current-computation-frame* graph))
	(let* ((current-computation-instance graph)
	       minimum-grid-width minimum-grid-height
	       (horizontal-axis-grid-format-not-changed-p nil)
	       (vertical-axis-grid-format-not-changed-p nil)
	       (graph-grid-slots-not-cached?
		 (null (graph-left-margin-width graph-grid)))
	       ;; Since the graph-grid slots are not saved, it is necessary
	       ;; to set them if empty.  The graph-grid is essentially a
	       ;; cache for the draw functions.
	       
	       (problems-reformatting-graph? nil)
	       (without-horizontal-labels?
		 (nth-value 1 (remove-tickmark-label-annotation
				(desired-range-for-horizontal-axis? graph))))
	       (without-vertical-labels?
		 (nth-value 1 (remove-tickmark-label-annotation
				(desired-range-for-vertical-axis?   graph)))))

	  (when (or (bad-plot-range-specs? graph)
		    (bad-desired-range-too-small? graph)
		    (bad-horizontal-range-zero? graph))
	    (setq enforce-reformatting? t))

	  (delete-all-frame-notes-for-graph graph)

	  (when (or graph-grid-slots-not-cached? changing-graph-margins?)
	    ;; Set margins.
	    (let ((minimum-graph-left-and-right-margin-width
		    (minimum-graph-left-and-right-margin-width graph-format))
		  (minimum-graph-top-and-bottom-margin-width
		    (minimum-graph-top-and-bottom-margin-width graph-format)))
	      (setf (graph-left-margin-width graph-grid)
		    minimum-graph-left-and-right-margin-width
		    (graph-right-margin-width graph-grid)
		    (floor minimum-graph-left-and-right-margin-width 16)
		    (graph-top-margin-width graph-grid)
		    (floor minimum-graph-top-and-bottom-margin-width 4)
		    (graph-bottom-margin-width graph-grid)
		    minimum-graph-top-and-bottom-margin-width))

	    (when without-horizontal-labels?
	      (remove-axis-labels-from-graph-grid 'horizontal graph-grid)
	      (setf (graph-bottom-margin-width graph-grid) 2))
	    (when without-vertical-labels?
	      (remove-axis-labels-from-graph-grid 'vertical   graph-grid)
	      (setf (graph-left-margin-width graph-grid) 5))	  
	    ;; Behave like a resize in what follows so that the margin changes we just
	    ;; made get propagated correctly.
	    (unless delta-left-edge? 
	      (setq delta-left-edge? 0 delta-right-edge?  0
		    delta-top-edge?  0 delta-bottom-edge? 0)))

	  (when (or new-graph? delta-left-edge?)
	    ;; Set edges.
	    (cond
	      (new-graph?
	       (set-edges-of-block graph-grid
				   0
				   0
				   (minimum-graph-width graph-format)
				   (minimum-graph-height graph-format)))
	      (t					; if resizing-graph?
	       ;; Here we are resizing a graph (due to either a resize menu choice or
	       ;; add/remove tickmark labels).  It is necessary to decache in these cases
	       ;; to avoid a memory leak (see the comment below graph-grid's cleanup method).
	       (decache-and-remove-all-graph-renderings-from-graph-grid graph-grid)
	       (change-edges-of-block
		 graph-grid
		 (+w (left-edge-of-block graph-grid) delta-left-edge?)
		 (+w (top-edge-of-block graph-grid) delta-top-edge?)
		 (+w (right-edge-of-block graph-grid) delta-right-edge?)
		 (+w (bottom-edge-of-block graph-grid) delta-bottom-edge?)))))
	  
	  (when (or graph-grid-slots-not-cached? new-graph? delta-left-edge?)
	    ;; Set widths.
	    (let ((width-of-graph-grid-block (width-of-block graph-grid))
		  (height-of-graph-grid-block (height-of-block graph-grid)))
	      (setf (grid-width-for-graph graph-grid)
		    (-f width-of-graph-grid-block
			(+f (graph-left-margin-width graph-grid)
			    (graph-right-margin-width graph-grid)))
		    (grid-and-erase-zone-width graph-grid)
		    (with-temporary-gensym-float-creation compute-grid-and-erase-zone 
		      (+w (floore-first (*e (coerce-fixnum-to-gensym-float
					      (grid-width-for-graph graph-grid))
					    erase-zone-ratio))
			  (grid-width-for-graph graph-grid)))
		    (grid-height-for-graph graph-grid)
		    (-f height-of-graph-grid-block
			(+f (graph-top-margin-width graph-grid)
			    (graph-bottom-margin-width graph-grid))))))
	  
	  (setq minimum-grid-width
		(grid-width-for-graph graph-grid)
		minimum-grid-height
		(grid-height-for-graph graph-grid))
	  
	  ;; Check if grid has to change.
	  ;; Note if horizontal axis has to change, plot data buffers must be
	  ;; completely refreshed (see also documentation for refresh-plot-data-buffer).
	  
	  (cond
	    ((and graph-grid?			; if not making graph grid
		  (graph-reformatted-since-start? graph)
		  (display-up-to-date? graph)
		  (not enforce-reformatting?)
		  (reformat-grid-only-if-absolutely-necessary? graph-format)
		  (not (graph-must-be-refreshed-for-old-data? graph-grid)))
	     ;; Note that it is necessary to check whether graph-rendering
	     ;; exists before trying to scroll since the graph rendering may be 
	     ;; reclaimed at any time.
	     
	     (when
		 (not (and (need-to-reformat-horizontal-axis?
			     graph-grid graph-format refresh-plot-data-buffers?)
			   (compute-new-parameters-for-horizontal-axis-of-grid
			     graph-grid graph-format refresh-plot-data-buffers?
			     t (scroll-continuously? graph))))
	       (setq horizontal-axis-grid-format-not-changed-p t))
	     
	     (if refresh-plot-data-buffers?
		 (refresh-data-for-plots graph-grid graph-format
					 horizontal-axis-grid-format-not-changed-p))
	     ;; If horizontal-axis-grid-format-not-changed-p is t, then don't refresh
	     ;; data buffers completely;  just add new data and discard old data.
	     
	     (cond
	       ((need-to-reformat-vertical-axis?
		  graph-grid graph-format)
		(when horizontal-axis-grid-format-not-changed-p
		  (setq horizontal-axis-grid-format-not-changed-p nil)
		  (compute-new-parameters-for-horizontal-axis-of-grid
		    graph-grid graph-format refresh-plot-data-buffers?)
		  (if refresh-plot-data-buffers?
		      (refresh-data-for-plots 
			graph-grid graph-format
			horizontal-axis-grid-format-not-changed-p)))
		
		(compute-new-parameters-for-vertical-axis-of-grid
		  graph-grid graph-format)
		)
	       (t
		(setq vertical-axis-grid-format-not-changed-p t)))
	     )
	    
	    (t					; if definitely have to reformat
	     (compute-new-parameters-for-horizontal-axis-of-grid
	       graph-grid graph-format refresh-plot-data-buffers?)
	     
	     (if refresh-plot-data-buffers?
		 (refresh-data-for-plots graph-grid graph-format nil))
	     
							    ;(reformat-plots graph-grid graph-format)
	     ;; Plot specific formats are currently not used.
	     (compute-new-parameters-for-vertical-axis-of-grid
	       graph-grid graph-format)))
	  
	  (scale-y-data-for-plots-if-necessary graph-grid)
	  
	  ;; put up new labels for graph axis if necessary
	  (when (not without-horizontal-labels?)
	    (if (not horizontal-axis-grid-format-not-changed-p)
		(put-up-new-labels-for-horizontal-graph-axis 
		  graph-grid graph-format
		  (not (absolute-range-specified-p
			 (desired-range-for-horizontal-axis-without-tickmark-info? graph))))
		(when (not (=w (old-dateline graph-grid)
			       (dateline graph-grid)))	; if scrolling
		  (put-up-new-high-value-label-for-horizontal-axis graph-grid))))
	  (when (not without-vertical-labels?)
	    (if (not vertical-axis-grid-format-not-changed-p)
		(put-up-new-labels-for-vertical-graph-axis graph-grid graph-format)))

	  (setf (display-up-to-date? graph) t)
	  
	  (when redraw-as-well-as-reformat-p
	    (cond
	      ((and horizontal-axis-grid-format-not-changed-p
		    vertical-axis-grid-format-not-changed-p
		    (not enforce-reformatting?))
	       ;; redraw only data
	       (update-images-of-only-new-data-for-graph-grid nil graph-grid))
	      (t
	       ;; else, redraw fully
	       ;; unnecessary to erase the opaque block before painting over it. (MHD 6/24/92)    
							    ; (update-images-of-graph-grid-and-data t graph-grid)
	       (update-images-of-graph-grid-and-data nil graph-grid))))
	  
	  (setf (graph-reformatted-since-start? graph) t)
	  
	  (if (and redraw-as-well-as-reformat-p
		   problems-reformatting-graph?)
	      (post-reformat-warning-note-for-graph graph))	; new arg. (MHD 2/22/91)
	  graph-grid)))))

;; Note that minimum-grid-width (and grid-width, grid-width-for-graph slot)
;; do not equal (width-of-block graph-grid);  they do not include the
;; margin widths.  Likewise for minimum-grid-height etc.

;; Left-edge-of-block and top-edge-of-block default to 0 when the block is
;; made.  They may change as the block is moved but they shouldn't be set
;; by make-or-reformat.

;; Horizontal and vertical grid line spacing calculation has to be fixed to
;; be consistent with algorithm used in draw.  Actually, if it exists in 
;; draw, it shouldn't have to be done here except maybe for reformatting.
;; In any case, it should only be done in one place, probably here.

;; Should format-of-superblock argument be passed also?
;; (superblock is always a table)

;; display-up-to-date? is slated for obsolescence, because we want to be able to
;; do an update command when hidden, and when hidden things will get out of date.



(defparameter minimum-grid-width-for-resizing-graph 10)

(defparameter minimum-grid-height-for-resizing-graph 10)



(defun change-size-of-graph 
    (graph left-edge-of-bounding-box top-edge-of-bounding-box
	   right-edge-of-bounding-box bottom-edge-of-bounding-box)
  (let ((region-invalidation-is-preferred t))		    ; Required to handle XOR mode.
    ;; Here necessary to remove the image of the opaque block, since its
    ;; size is changing. (MHD 6/24/92)
    (update-images-of-block graph t nil)
    (let ((delta-left-edge
	    (-w left-edge-of-bounding-box (left-edge-of-block graph)))
	  (delta-top-edge
	    (-w top-edge-of-bounding-box (top-edge-of-block graph))))
      (change-edges-of-block graph
			     left-edge-of-bounding-box top-edge-of-bounding-box
			     nil nil)
      
      (with-temporary-gensym-float-creation change-size-of-graph
	(let ((redraw-as-well-as-reformat-p nil)
	      (graph-grid (get-graph-grid-given-graph graph)))
	  (make-or-reformat-graph-grid 
	    nil (get-graph-grid-given-graph graph) (graph-format graph)
	    t t delta-left-edge delta-top-edge
	    (-w right-edge-of-bounding-box (right-edge-of-block graph))
	    (-w bottom-edge-of-bounding-box (bottom-edge-of-block graph)))
	  (reformat-table-in-place graph)

	  ;; If the bounding box is dragged to make the graph very small, but
	  ;; if there is significant text in the expressions-to-display cell,
	  ;; reformat-table-in-place will adjust the edges of the graph so
	  ;; that the text in the expressions-to-display cell fits.  This
	  ;; causes the graph to become larger than the bounding box while
	  ;; the graph grid is left small.  Since this doesn't look good,
	  ;; make-or-reformat-graph-grid is called again to enlarge the
	  ;; graph grid.  Doing this necessitates calling 
	  ;; reformat-table-in-place once again since this must always be
	  ;; called last.  
	  ;; Consider changing this so that the graph grid conforms to the
	  ;; bounding box and the text is adjusted (or dropped)!
	  (when (not (and (=w left-edge-of-bounding-box 
			      (left-edge-of-block graph))
			  (=w top-edge-of-bounding-box 
			      (top-edge-of-block graph))
			  (=w right-edge-of-bounding-box 
			      (right-edge-of-block graph))
			  (=w bottom-edge-of-bounding-box 
			      (bottom-edge-of-block graph))))
	    ;; Can happen due to reformat-table-in-place.
	    (make-or-reformat-graph-grid 
	      nil
	      graph-grid
	      (graph-format graph)
	      t t
	      (-w (left-edge-of-block graph) left-edge-of-bounding-box)
	      (-w (top-edge-of-block graph) top-edge-of-bounding-box)
	      (-w (right-edge-of-block graph) right-edge-of-bounding-box)
	      (-w (bottom-edge-of-block graph) bottom-edge-of-bounding-box))
	    (reformat-table-in-place graph))

	  (let ((width-adjustment 0)
		(height-adjustment 0))
	    (when (<w (width-of-block graph-grid)
		      (+w (graph-left-margin-width graph-grid)
			  (graph-right-margin-width graph-grid)
			  minimum-grid-width-for-resizing-graph))
	      (setq width-adjustment
		    (-w (+w (graph-left-margin-width graph-grid)
			    (graph-right-margin-width graph-grid)
			    minimum-grid-height-for-resizing-graph)
			(width-of-block graph-grid))))
	    (when (<w (height-of-block graph-grid)
		      (+w (graph-top-margin-width graph-grid)
			  (graph-bottom-margin-width graph-grid)
			  minimum-grid-width-for-resizing-graph))
	      (setq height-adjustment
		    (-w (+w (graph-top-margin-width graph-grid)
			    (graph-bottom-margin-width graph-grid)
			    minimum-grid-height-for-resizing-graph)
			(height-of-block graph-grid))))
	    (when (or (/=w width-adjustment 0)
		      (/=w height-adjustment 0))
	      (make-or-reformat-graph-grid 
		nil
		graph-grid
		(graph-format graph)
		t t
		0 0 width-adjustment height-adjustment)
	      (reformat-table-in-place graph))))))
    
    (enlarge-workspace-for-block-rectangle-if-necessary graph nil)
    (update-images-of-graph nil graph)))

;; For release 2.0, the graph format frame is used to determine the size of
;; a graph only when it is created, not when it is loaded.  Graphs can be
;; resized and the new size will persist once the kb is saved.

;; When changing size, erase and draw must be done outside
;; make-or-reformat-graph-grid.  Therefore, redraw-as-well-as-reformat-p is bound
;; to nil.  Change-size-of-graph is called from handle-dialog-button which takes
;; care of erasing and drawing.


(defun restore-graph-to-normal-size (graph)
  ;; Here necessary to remove the image of the opaque block, since its
  ;; size is changing. (MHD 6/24/92)
;  (with-updating-that-requires-the-draw-function-be-used
      (update-images-of-block graph t nil)
;
  (let* ((graph-grid (get-graph-grid-given-graph graph))
	 (delta-right-edge
	   (-w (+w (left-edge-of-block graph-grid)
		   (minimum-graph-width (graph-format graph)))
	       (right-edge-of-block graph-grid)))
	 (delta-bottom-edge
	   (-w (+w (top-edge-of-block graph-grid)
		   (minimum-graph-height (graph-format graph)))
	       (bottom-edge-of-block graph-grid))))
    (with-temporary-gensym-float-creation change-size-of-graph
      (let ((redraw-as-well-as-reformat-p nil))
	(make-or-reformat-graph-grid 
	  nil graph-grid (graph-format graph)
	  t t 0 0 delta-right-edge delta-bottom-edge))
      (reformat-table-in-place graph)))
  (with-updating-that-requires-the-draw-function-be-used
      (update-images-of-block graph nil nil)))




(defun update-images-of-graph (erase? graph)
  (let ((graph-grid
	  (get-graph-grid-given-graph graph)))
    (make-graph-not-up-to-date graph-grid)

    (with-updating-that-requires-the-draw-function-be-used
	(update-images-of-block graph erase? t))
    ;; above is equivalent to and replaces the following old code:  (MHD 4/15/91)
;    (update-images
;      erase? graph
;      (left-edge-of-block graph) (top-edge-of-block graph)
;      (right-edge-of-block graph) (bottom-edge-of-block graph)
;      nil nil nil graph)
    
    ))


(defun update-images-of-graph-grid-and-data (erase? graph-grid)
  #+development
  (when joes-graph-hax-trace-p
    (format t "Update whole graph ~s~%" graph-grid))
  (update-images-of-graph erase? (superblock? graph-grid)))

;; Consider calling draw-graph-grid-and-data here, via update-images, rather than
;; calling the draw method for graphs via update-images-of-graph.  Calling the
;; general draw method is more convenient since it paints the entire background of
;; the opaque block.  Calling draw-graph-grid-and-data directly would require
;; adding another argument to draw-graph-grid-and-data to indicate whether or not
;; to draw axis labels.

(defun update-images-of-only-new-data-for-graph-grid (erase? graph-grid)
  #+development
  (when joes-graph-hax-trace-p
    (format t "Update new data of graph ~s~%" graph-grid))
  (let ((graph (superblock? graph-grid))
	(current-graph-grid-in-minimal-update
	 graph-grid)
	(current-minimal-grid-draw-has-seen-one-image-plane-p nil))
;    (make-graph-not-up-to-date graph-grid)
    (with-updating-that-requires-the-draw-function-be-used	
	(update-images
	  erase?
	  graph						    ; Note A
	  graph
	  (left-edge-of-block graph) (top-edge-of-block graph) ; Note B
	  (right-edge-of-block graph) (bottom-edge-of-block graph)
	  nil
	  'draw-only-new-data-for-graph-grid graph-grid))
    (setf (draw-graph-rendering-to-show-new-data? graph-grid) nil)))

;; Note A: In order to prevent the code which cleans up overlapping blocks from
;; redrawing the multitudinous subblocks of graphs themselves, update-images has
;; been told that graphs have no subblocks.  So we must tell update-images here
;; that the block we are updating is the graph itself, and not the graph-grid,
;; which, being a subblock of the graph, confuses drawing.
;; -fmw, 9/7/94

;; Note B: Note that this update area is a very generous upper bound.


(defun graph-must-be-refreshed-for-old-data? (graph-grid)
  (loop with display-evaluation-should-use-simulated-values?
	  = (display-evaluation-should-use-simulated-values? 
	      (superblock? graph-grid))
	for plot in (list-of-plots graph-grid)
	as display-expression-for-plot
	   = (display-expression-for-plot plot)
	as variable-or-parameter
	   = (get-variable-given-graph-expression
	       display-expression-for-plot
	       display-evaluation-should-use-simulated-values?)
	as simulation-subtable?
	   = (if (and variable-or-parameter
		      (variable-p variable-or-parameter))
		 (simulation-details variable-or-parameter))
	as history-buffer-of-stored-values
	   = (if variable-or-parameter
		 (if display-evaluation-should-use-simulated-values?
		     (if simulation-subtable?
			 (simulation-stored-histories?
			   simulation-subtable?))
		     (variable-or-parameter-stored-histories? 
		       variable-or-parameter)))
	do
    (when (and history-buffer-of-stored-values
	       (old-data-has-been-saved? history-buffer-of-stored-values))
      (setf (old-data-has-been-saved? history-buffer-of-stored-values) nil)
      (return t))))

;; Note that this assumes that display-expression-for-plot is a name of a variable.
;; This will get more complicated for general expressions.  It will have to entity
;; evaluate and make this test for each variable in the expression!  Note that 
;; this could be improved by saving the time of the oldest data point saved in the
;; old-data-has-been-saved? slot.  This would allow checking for the case where
;; the current upper horizontal boundary is less than the time of old data saved 
;; this way.  This is probably not worth the effort however since typically,
;; a graph shows the latest data.  Also one complete refresh takes care of all 
;; old data saved this way, even if many old data points were stored since the
;; last update of the graph.


;;; Need-to-reformat-horizontal-axis? returns non-nil if the horizontal
;;; axis parameters have to be computed.  There are three basic cases 
;;; here corresponding to the user specifications given in 
;;; desired-range-for-horizontal-axis? for graph:
;;; 1.  Low and high values specified
;;;     - axis not a function of data, no need to reformat
;;; 2.  Range specified (moving window)
;;;     - check if newest data point fits on horizontal axis
;;; 3.  No format specified
;;;     - check if newest data point fits on horizontal axis
;;; Note, the horizontal axis will not reformat
;;; due to data being discarded;  it will not "shrink" in response to
;;; old data being discarded.  Thus, there is no need to look at oldest
;;; data point. 

;;; Note that when the user edits format specifications for graphs or plots,
;;; make-or-reformat-graph-grid is always called with enforce-reformatting? bound to t.
;;; Thus, need-to-reformat-horizontal-axis? will never be called when the user edits
;;; specs.  Therefore, it need only consider if new data for the plots requires
;;; that the horizontal axis be reformatted;  it does not have to worry about
;;; format specifications having changed.  Of course, if the axis format is
;;; completely specified by the user (if low and high values are specified)
;;; there is never any need to reformat due to new data.

;;; If plot-data-buffers-to-be-refreshed? is nil, use old extrema in plot
;;; data buffer, else, compute new extrema.

(defun need-to-reformat-horizontal-axis?
       (graph-grid graph-format plot-data-buffers-to-be-refreshed?)
       ;; If plot-data-buffers-to-be-refreshed? is nil, use old extrema in plot
       ;; data buffer, else, compute new extrema.
  (with-temporary-gensym-float-creation reformat-horizontal?
    (let* ((graph (superblock? graph-grid))
	   (desired-absolute-or-relative-range?
	     (desired-range-for-horizontal-axis-without-tickmark-info? graph))
	   (high-and-low-values-specified?
	     (if desired-absolute-or-relative-range?
		 (multiple-value-bind
		   (desired-range-for-horizontal-axis?
		    desired-low-value-for-horizontal-axis?
		    desired-high-value-for-horizontal-axis?)
		     (parse-desired-absolute-or-relative-range
		       desired-absolute-or-relative-range?)
		   (declare (ignore 
			      desired-high-value-for-horizontal-axis?
			      desired-range-for-horizontal-axis?))
		   desired-low-value-for-horizontal-axis?))))
      (cond
	(high-and-low-values-specified? nil)
	(t					       ; either no spec or moving window
	 (if (use-one-set-of-axes? graph-format)
	     
	     ;; compute high value for horizontal axes
	     (let ((high-value-for-horizontal-axis
		     (compute-high-value-for-horizontal-axis 
		       graph-grid plot-data-buffers-to-be-refreshed?)))
	       (if high-value-for-horizontal-axis
		   (<= (high-value-for-horizontal-axis graph-grid)
		       high-value-for-horizontal-axis)))
	     
	     ;; If (use-one-set-of-axes? graph-format) is nil
	     ))))))

;; Note that "desired" low and high values for the horizontal and vertical
;; axes, specified in the graph, will prevail if they are specified.
;; Otherwise, the high value computed from the plots will be used.


;;; Need-to-reformat-vertical-axis? is different from need-to-reformat-horizontal-axis?
;;; in the way new data is checked to see if it fits in the old grid.  In the case of
;;; the horizontal axis, the moving window is always determined with respect to the
;;; maximum value for the horizontal axis.  In the case of the vertical axis, the
;;; moving window must be determined with respect to the more recent (more recent
;;; on the horizontal axis) extremum.  This extremum may be either a minimum or a 
;;; maximum.  Thus, instead of analyzing the newest data point, the most recent
;;; extremum is analyzed.

;;; When need-to-reformat-vertical-axis? is called, the plot data buffers 
;;; will always have been refreshed already so there is no need for a
;;; plot-data-buffers-to-be-refreshed? flag. 

(defun need-to-reformat-vertical-axis?
       (graph-grid graph-format)
  (with-temporary-gensym-float-creation reformat-vertical?
    (let* ((graph (superblock? graph-grid))
	   (desired-absolute-or-relative-range?
	     (desired-range-for-vertical-axis-without-tickmark-info? graph))
	   most-recent-y-extremum opposite-y-extremum-of-most-recent)
      (cond
	(desired-absolute-or-relative-range?
	 (multiple-value-bind
	   (desired-range-for-vertical-axis?
	    desired-low-value-for-vertical-axis?
	    desired-high-value-for-vertical-axis?)
	     (parse-desired-absolute-or-relative-range
	       desired-absolute-or-relative-range?)
	   (declare (ignore
		      desired-range-for-vertical-axis?
		      desired-high-value-for-vertical-axis?))
	   (cond 
	     (desired-low-value-for-vertical-axis? nil)	       ; if low and high values specified
	     (t					       ; if moving window specified
	      (if (use-one-set-of-axes? graph-format)
		  ;; compute extrema
		  (loop for plot in (list-of-plots graph-grid)
;			as plot-format = (plot-format plot)
;			as data-buffer-for-plot = (data-buffer-for-plot plot)
			do
		    (when (data-exists-for-plot-p plot)
		      (setq most-recent-y-extremum
			    (extract-number-or-value (most-recent-y-extremum plot))
			    opposite-y-extremum-of-most-recent
			    (extract-number-or-value
			      (opposite-y-extremum-of-most-recent plot))))
		    (when (and most-recent-y-extremum
			       (or (< (extract-number-or-value
					(high-value-for-vertical-axis graph-grid))
				      (max most-recent-y-extremum
					   opposite-y-extremum-of-most-recent))
				   (> (extract-number-or-value
					(low-value-for-vertical-axis graph-grid))
				      (min most-recent-y-extremum
					   opposite-y-extremum-of-most-recent))))
		      (return t)))
		  
		  ;; If (use-one-set-of-axes? graph-format) is nil
		  )))))

	(t
	 ;; if no format specified
	 (if (use-one-set-of-axes? graph-format)
	     ;; compute extrema
	     (loop with high-value-for-vertical-axis = nil
		   with low-value-for-vertical-axis = nil
		   for plot in (list-of-plots graph-grid)
;		   as plot-format = (plot-format plot)
;		   as data-buffer-for-plot = (data-buffer-for-plot plot)
		   as most-recent-y-extremum
		      = (if (data-exists-for-plot-p plot)
			    (extract-number-or-value
			      (most-recent-y-extremum plot)))
		   do
	       (when (data-exists-for-plot-p plot)
		 (setq most-recent-y-extremum
		       (extract-number-or-value (most-recent-y-extremum plot))
		       opposite-y-extremum-of-most-recent
		       (extract-number-or-value
			 (opposite-y-extremum-of-most-recent plot)))
		 (when most-recent-y-extremum
		   (let* ((max-y-value
			    (max most-recent-y-extremum
				 opposite-y-extremum-of-most-recent))
			  (min-y-value
			    (min most-recent-y-extremum
				 opposite-y-extremum-of-most-recent)))
		     (setq high-value-for-vertical-axis
			   (if high-value-for-vertical-axis
			       (max high-value-for-vertical-axis max-y-value)
			       max-y-value)
			   low-value-for-vertical-axis
			   (if low-value-for-vertical-axis
			       (min low-value-for-vertical-axis min-y-value)
			       min-y-value)))))
		   finally
		     (return
		       (when high-value-for-vertical-axis
			 (or
			   (if high-value-for-vertical-axis
			       (< (extract-number-or-value
				    (high-value-for-vertical-axis graph-grid))
				  high-value-for-vertical-axis))
			   (if low-value-for-vertical-axis
			       (> (extract-number-or-value
				    (low-value-for-vertical-axis graph-grid))
				  low-value-for-vertical-axis))))))
	     
	     ;; If (use-one-set-of-axes? graph-format) is nil
	     ))))))

;; In the moving window case, the moving window is determined by the first plot.


;;; Parse-desired-absolute-or-relative-range returns three values:
;;; desired-range, desired-low-value, and desired-high-value.
;;; If the first is not nil, the second two must be, and vice-versa.

(defun parse-desired-absolute-or-relative-range
       (desired-absolute-or-relative-range)
  (cond
    ((slot-value-number-p desired-absolute-or-relative-range)
     (values (slot-value-number-value desired-absolute-or-relative-range) nil nil))
    ((not (eq (car desired-absolute-or-relative-range) '\;))
     (values (slot-value-number-value
	       (car desired-absolute-or-relative-range)) nil nil))
    ((slot-value-number-p (second desired-absolute-or-relative-range))
     (values nil
	     (slot-value-number-value
	       (second desired-absolute-or-relative-range))
	     (slot-value-number-value
	       (third desired-absolute-or-relative-range))))
    (t
     (values nil
	     (slot-value-number-value
	       (car (second desired-absolute-or-relative-range)))
	     (slot-value-number-value
	       (car (third desired-absolute-or-relative-range)))))))

(defun absolute-range-specified-p (desired-absolute-or-relative-range)
  (eq (car desired-absolute-or-relative-range) '\;))


;;; Compute-next-maximum-x-value computes the new maximum before the plot
;;; data buffer is refreshed.  It is important to know this value since
;;; it determines whether and how the graph grid will be reformatted which,
;;; in turn, determines how the plot data buffer will be refreshed.

(defun compute-next-maximum-x-value (plot graph-grid)
  (compute-time-of-newest-data-point
    (display-expression-for-plot plot)
    (display-evaluation-should-use-simulated-values? 
      (superblock? graph-grid))))


(defun compute-next-minimum-x-value (plot graph-grid)
  (compute-time-of-oldest-data-point
    (display-expression-for-plot plot)
    (display-evaluation-should-use-simulated-values? 
      (superblock? graph-grid))))


;; The compute-time functions (see histories) are used (as in the above case)
;; to determine graph grid reformatting but also to refresh plot data buffers.
;; These functions use histories to determine times.
;; Since some of these histories may be maintained in another process,
;; these functions will have to go through data servers eventually.  If 
;; they can't
;; get data, then the reformat or refresh operation will have to be postponed.
;; This is acceptable;  if a display can't get data, it can't be updated.
;; The issue of when to retry is an open one.  May have to make updating of
;; graphs and displays a resumeable task.
;; Actually, this issue can and should be deferred for some time
;; (see design book notes for 12/29/87).



;;; Compute-new-parameters-for-horizontal-axis-of-grid will compute the graph
;;; grid based on user edited format specs and data.  User format specs will
;;; overide data.  If low and high values are specified, data will be ignored.
;;; If a moving window is specified, it will be computed with respect to
;;; the highest x value in the data.  If the user specifies no format, then the low
;;; and high x values of data will be used.  X values of data are computed
;;; from the plots.  The horizontal axis range will be exactly as specified by
;;; the user.  If the user specifies a high and low value, the range will be
;;; the difference.  If the user specifies a range, that range exactly will
;;; be used.

;;; Scrolling ...   see memo!

;;; If plot-data-buffers-to-be-refreshed? is nil, use old extrema in plot
;;; data buffer, else, compute new extrema.

;;; Compute-new-parameters-for-horizontal-axis-of-grid returns t if the grid
;;; ruling changes.

(defun compute-new-parameters-for-horizontal-axis-of-grid
       (graph-grid graph-format plot-data-buffers-to-be-refreshed?
	&optional try-scrolling? scroll-continuously?)
  (with-temporary-gensym-float-creation compute-horizontal
    (let* ((graph (superblock? graph-grid))
	   (new-low-value-for-horizontal-axis nil)
	   (new-high-value-for-horizontal-axis nil)
	   (horizontal-axis-range nil)
	   desired-low-value-for-horizontal-axis
	   desired-high-value-for-horizontal-axis
	   desired-low-value-for-horizontal-axis?
	   desired-high-value-for-horizontal-axis?
	   (desired-absolute-or-relative-horizontal-axis-range?
	     (if graph (desired-range-for-horizontal-axis-without-tickmark-info? graph)))
	   desired-range-for-horizontal-axis?
	   (determine-ruling? t)
	   (absolute-range-specified? nil)
	   (new-shift nil))
      
      (if desired-absolute-or-relative-horizontal-axis-range?
	  (multiple-value-setq
	    (desired-range-for-horizontal-axis?
	     desired-low-value-for-horizontal-axis?
	     desired-high-value-for-horizontal-axis?)
	    (parse-desired-absolute-or-relative-range
	      desired-absolute-or-relative-horizontal-axis-range?)))
      
      ;; Compute desired low and high values.
      (cond
	(desired-low-value-for-horizontal-axis?	       ; low and high values specified
	 (setq desired-high-value-for-horizontal-axis
	       desired-high-value-for-horizontal-axis?
	       desired-low-value-for-horizontal-axis
	       desired-low-value-for-horizontal-axis?
	       absolute-range-specified? t))
	
	((and     ; check whether to scroll
	   (cond					       
	     (desired-range-for-horizontal-axis?
	      (setq new-high-value-for-horizontal-axis
		    (compute-high-value-for-horizontal-axis 
		      graph-grid plot-data-buffers-to-be-refreshed?))
	      (cond
		(try-scrolling? 
		 (setq horizontal-axis-range
		       (extract-number-or-value
			 (horizontal-axis-range graph-grid)))
		 t)
		(t
		 (setq new-low-value-for-horizontal-axis
		       (compute-low-value-for-horizontal-axis 
			 graph-grid plot-data-buffers-to-be-refreshed?))
		 nil)))
	     (t
	      (setq new-high-value-for-horizontal-axis
		    (compute-high-value-for-horizontal-axis 
		      graph-grid plot-data-buffers-to-be-refreshed?)
		    new-low-value-for-horizontal-axis
		    (compute-low-value-for-horizontal-axis 
		      graph-grid plot-data-buffers-to-be-refreshed?))
	      (and try-scrolling?
		   (<= (- new-high-value-for-horizontal-axis
			  new-low-value-for-horizontal-axis)
		       (setq horizontal-axis-range
			     (extract-number-or-value
			       (horizontal-axis-range graph-grid)))))))
	   new-high-value-for-horizontal-axis
	   (let* ((current-shift? (shift-horizontal-axis? graph-grid)))
	     (setq new-shift
		   (compute-shift-for-scrolling
		     graph-grid graph scroll-continuously? 
		     horizontal-axis-range 
		     (high-value-for-horizontal-axis graph-grid)
		     new-high-value-for-horizontal-axis))
	     (< (if current-shift?
		    (- new-shift current-shift?)
		    new-shift)
		horizontal-axis-range)))

	 (setq determine-ruling? nil)
	 ;; If only need to scroll axis,
	 ;; number-of-vertical-grid-lines and interval-between-vertical-grid-lines
	 ;; stays the same so there is no need to call 
	 ;; determine-ruling-for-time-axis.  A much simpler calculation will 
	 ;; suffice.
	 
	 ;; Determine shift.
	 (setf (shift-horizontal-axis? graph-grid)
	       new-shift
	       (dateline graph-grid)
	       (mod new-shift 
		    (horizontal-axis-and-erase-zone-range graph-grid))
	       (low-value-for-horizontal-axis graph-grid)
	       (+ (low-value-for-horizontal-axis-before-shift graph-grid)
		  new-shift)
	       (high-value-for-horizontal-axis graph-grid)
	       (+ (low-value-for-horizontal-axis graph-grid)
		  horizontal-axis-range))
	 ;; The computations are done this way to avoid any possibility
	 ;; of a cumulative shift between low-value-for-horizontal-axis
	 ;; high-value-for-horizontal-axis, and dateline.
	 ;; Note also that since not determining new
	 ;; ruling, low-value-for-horizontal-axis-before-shift and
	 ;; horizontal-axis-range are not recomputed.
	 )
	
	(t					       ; if not trying scrolling
	 (cond
	   ((use-one-set-of-axes? graph-format)
	    ;; compute high and low values for horizontal axes

	    (if (not new-high-value-for-horizontal-axis)       ; if no data
		(setq new-low-value-for-horizontal-axis
		      (-f (*f default-interval-between-vertical-grid-lines
			      (floor (/ (coerce-to-gensym-float
					  default-number-of-vertical-grid-lines)
					2))))
		      new-high-value-for-horizontal-axis
		      (*f default-interval-between-vertical-grid-lines
			  (ceiling (/ (coerce-to-gensym-float
					default-number-of-vertical-grid-lines)
				      2)))))
;	    (format t "newhigh2=~s range=~s extra=~s~%"
;		    new-high-value-for-horizontal-axis
;		    desired-range-for-horizontal-axis?
;		    (slot-value-number-value
;				(extra-range-for-high-end-of-horizontal-axis
;				  graph-format)))
	    	    
	    (if desired-range-for-horizontal-axis?
		(setq desired-high-value-for-horizontal-axis
		      new-high-value-for-horizontal-axis
		      desired-low-value-for-horizontal-axis
		      (- desired-high-value-for-horizontal-axis
			 desired-range-for-horizontal-axis?))
		(setq desired-high-value-for-horizontal-axis
		      (+ new-high-value-for-horizontal-axis
			 (round 
			   (* (abs
				(max
				  (- new-high-value-for-horizontal-axis
				     new-low-value-for-horizontal-axis)
				  1))
			      (slot-value-number-value
				(extra-range-for-high-end-of-horizontal-axis
				  graph-format)))))
		      ;; If no axis specs, leave some extra space to
		      ;; avoid constant reformatting.
		      desired-low-value-for-horizontal-axis
		      (if (= new-high-value-for-horizontal-axis
			     new-low-value-for-horizontal-axis)
			  (- new-low-value-for-horizontal-axis
			     default-interval-between-vertical-grid-lines)
			  new-low-value-for-horizontal-axis))))
	   (t
	    ;; If (use-one-set-of-axes? graph-format) is nil
	    ))))
      
      (when determine-ruling?
	(multiple-value-bind
	  (low-value-for-vertical-grid-lines
	   high-value-for-vertical-grid-lines
	   number-of-vertical-grid-lines
	   interval-between-vertical-grid-lines
	   label-scale-for-vertical-grid-lines)
	    (determine-ruling-for-time-axis	       ; for now
	      desired-low-value-for-horizontal-axis
	      desired-high-value-for-horizontal-axis
	      (number-of-vertical-grid-lines graph-grid)
	      (minimum-number-of-vertical-grid-lines graph-format)
	      (coerce-to-gensym-float
		(slot-value-number-value
		  (minimum-interval-between-vertical-grid-lines graph-format))))
	  
	  (when (not absolute-range-specified?)
	    (setf high-value-for-vertical-grid-lines
		  desired-high-value-for-horizontal-axis))
	  ;; To align grid lines with right edge of grid.
	  
	  (setf (low-value-for-vertical-grid-lines graph-grid)
		low-value-for-vertical-grid-lines
		(high-value-for-vertical-grid-lines graph-grid)
		high-value-for-vertical-grid-lines
		(number-of-vertical-grid-lines graph-grid)
		number-of-vertical-grid-lines
		(label-scale-for-vertical-grid-lines graph-grid)
		label-scale-for-vertical-grid-lines)
	  (store-managed-number-or-value
	    (interval-between-vertical-grid-lines graph-grid)
	    interval-between-vertical-grid-lines)
	  (setq horizontal-axis-range
		(compute-horizontal-axis-range
		  desired-high-value-for-horizontal-axis
		  desired-low-value-for-horizontal-axis
		  graph))
	  (store-managed-number-or-value	     
	    (horizontal-axis-range graph-grid) horizontal-axis-range)
	  (setf (horizontal-axis-and-erase-zone-range graph-grid)
		(floor (/ (coerce-to-gensym-float
			    (* horizontal-axis-range
			       (grid-and-erase-zone-width graph-grid)))
			  (grid-width-for-graph graph-grid))))
	  (setf (interval-between-plot-markers graph-grid)
		(round (/ (coerce-to-gensym-float horizontal-axis-range)
			  default-number-of-markers)))
	  (store-managed-number-or-value
	    (vertical-grid-line-spacing graph-grid)
	    (/ (* (coerce-to-gensym-float minimum-grid-width)
		  interval-between-vertical-grid-lines)
	       horizontal-axis-range))
	  (store-managed-number-or-value
	    (spacing-between-right-edge-and-grid-line graph-grid)
	    (/ (* (coerce-to-gensym-float minimum-grid-width)
		  (- interval-between-vertical-grid-lines
		     (- high-value-for-vertical-grid-lines 
			desired-high-value-for-horizontal-axis)))
	       horizontal-axis-range))
	  ;; Vertical grid line spacing is not truncated so that remainder can be 
	  ;; accumulated so that first and last grid lines fall exactly on the 
	  ;; margins when drawing.  Gensym-floats are used because they are faster
	  ;; than ratios.
	  
	  (setf (low-value-for-horizontal-axis graph-grid)
		desired-low-value-for-horizontal-axis
		(low-value-for-horizontal-axis-before-shift graph-grid)
		desired-low-value-for-horizontal-axis
		(high-value-for-horizontal-axis graph-grid)
		desired-high-value-for-horizontal-axis
		(dateline graph-grid) 0
		(old-dateline graph-grid) 0
		(shift-horizontal-axis? graph-grid) nil)))
      
      determine-ruling?
      )))

;; Abstract the code for determining desired low and high values!

;; There should be no need to determine ruling each time if axes
;; are specified absolutely!

;; Low-value-for-horizontal-axis and high-value-for-horizontal-axis are always
;; fixnums (representing seconds) for now.

;; Note that there is some repetition of activity here of what may have been
;; done in the need-to-reformat? functions.

;; Note that if the scrolling shift > horizontal-axis-range, scrolling is not
;; attempted.  The complete recomputation is not much less efficient than
;; scrolling in this (relatively rare) case.  Consider, at some point, improving
;; scrolling to allow for shifts greater than horizontal-axis-range.
;; This would require, among other things, limiting number-of-new-grid-lines
;; in compute-shift-for-scrolling.



(defun compute-horizontal-axis-range (high-value low-value graph)
  (let ((range (-f high-value low-value)))
    (when (=f range 0)
      (setq range 1)
      (setq problems-reformatting-graph? t)
      (add-frame-note 'horizontal-range-zero graph nil t nil))
    range))



(defun compute-high-value-for-horizontal-axis 
       (graph-grid plot-data-buffers-to-be-refreshed?)
  (loop with high-value = nil
	for plot in (list-of-plots graph-grid)
;	as plot-format = (plot-format plot)
;	as data-buffer-for-plot = (data-buffer-for-plot plot)
	as x-data-maximum
	   = (if plot-data-buffers-to-be-refreshed?
		 (compute-next-maximum-x-value plot graph-grid)
		 (if (data-exists-for-plot-p plot)
		     (extract-number-or-value
		       (x-data-maximum plot))))
	do
    (when x-data-maximum
	(setq high-value
	      (if high-value
		  (max high-value x-data-maximum)
		  x-data-maximum)))
	finally (return high-value)))

(defun compute-low-value-for-horizontal-axis 
       (graph-grid plot-data-buffers-to-be-refreshed?)
  (loop with low-value = nil
	for plot in (list-of-plots graph-grid)
;	as plot-format = (plot-format plot)
;	as data-buffer-for-plot = (data-buffer-for-plot plot)
	as x-data-minimum
	   = (if plot-data-buffers-to-be-refreshed?
		 (compute-next-minimum-x-value plot graph-grid)
		 (if (data-exists-for-plot-p plot)
		     (extract-number-or-value
		       (x-data-minimum plot))))
	do
    (when x-data-minimum
      (setq low-value
	    (if low-value
		(min low-value x-data-minimum)
		x-data-minimum)))
	finally (return low-value)))




(defun compute-shift-for-scrolling
       (graph-grid graph scroll-continuously? horizontal-axis-range
	high-value-for-horizontal-axis new-high-value-for-horizontal-axis)

  (reclaim-graph-list (new-scrolled-vertical-grid-line-positions graph-grid))
  (setf (new-scrolled-vertical-grid-line-positions graph-grid) nil)

  (let* ((horizontal-axis-shift
	   (or (shift-horizontal-axis? graph-grid) 0))
	 (desired-shift
	   (+ (- new-high-value-for-horizontal-axis
		 high-value-for-horizontal-axis)
	      (maxf
		(round 
		  (* (/ (percentage-extra-space-to-leave graph)
			100.0)
		     horizontal-axis-range))
		1)))
	 (interval-between-grid-lines
	   (extract-number-or-value
	     (interval-between-vertical-grid-lines graph-grid)))
	 (interval-after-last-grid-line
	   (rem horizontal-axis-shift interval-between-grid-lines))
	 (interval-until-next-grid-line
	   (if (= interval-after-last-grid-line 0) 
	       0
	       (- interval-between-grid-lines
		  interval-after-last-grid-line)))
	 (desired-shift-beyond-next-grid-line
	   (- desired-shift interval-until-next-grid-line))
	 (number-of-new-grid-lines nil)
	 amount-to-shift)
    (cond
      (scroll-continuously?
       (setq amount-to-shift desired-shift)
       (when (>= desired-shift-beyond-next-grid-line 0)
	 (setq number-of-new-grid-lines
	       (+f (floor desired-shift-beyond-next-grid-line 
			  interval-between-grid-lines)
		   1))))
      (t
       (setq number-of-new-grid-lines
	     (ceiling desired-shift-beyond-next-grid-line interval-between-grid-lines)
	     amount-to-shift
	     (if (> interval-until-next-grid-line desired-shift)
		 interval-until-next-grid-line
		 (+ interval-until-next-grid-line
		    (* number-of-new-grid-lines interval-between-grid-lines))))))
    (when number-of-new-grid-lines
      (loop with position-of-next-grid-line
	      = (+ horizontal-axis-shift interval-until-next-grid-line)
	    for i from 1 to number-of-new-grid-lines
	    do
	(setf (new-scrolled-vertical-grid-line-positions graph-grid)
	      (graph-cons 
		(mod position-of-next-grid-line 
		     (horizontal-axis-and-erase-zone-range graph-grid))
		(new-scrolled-vertical-grid-line-positions graph-grid)))
	(setq position-of-next-grid-line
	      (+ position-of-next-grid-line interval-between-grid-lines))))
    (+ horizontal-axis-shift amount-to-shift)))

;; Note that when computing position-of-next-grid-line, it is not necessary to
;; add horizontal-axis-range due to the subsequent mod operation using 
;; horizontal-axis-range.

;; Note that desired-shift must be at least 1 more than the difference between the
;; new and old high values so that the dateline is shifted enough so there is room 
;; for the new data.  Otherwise, the dateline will fall on the high value for the
;; horizontal axis rather than the low value.  This would cause problems when
;; bitblting the ring raster since this involves swapping regions based on the
;; dateline.

;; Interval-until-next-grid-line must be computed because this may be the first 
;; time that scroll-continuously? is nil after it has been non-nil for a while.
;; Thus, interval-until-next-grid-line is used to realign the grid lines.  This is
;; based on the very valid assumption that when (shift-horizontal-axis? graph-grid)
;; is 0, which happens when there is a complete reformat, the grid lines are 
;; aligned.  By definition, a complete reformat results in aligned grid lines.

;; Note that currently, (shift-horizontal-axis? graph-grid) is always an integer
;; or nil.  Also, since the horizontal axis is currently automatically formatted,
;; it will always have "nice" intervals which are currently always integers.
;; This will have to be reviewed if these assumptions change!


(defvar range-too-small?)


(defun compute-new-parameters-for-vertical-axis-of-grid
       (graph-grid graph-format)
  (with-temporary-gensym-float-creation compute-vertical
    (let* ((graph (superblock? graph-grid))
	   desired-low-value-for-vertical-axis
	   desired-high-value-for-vertical-axis
	   desired-low-value-for-vertical-axis?
	   desired-high-value-for-vertical-axis?
	   (desired-absolute-or-relative-vertical-axis-range?
	     (if graph (desired-range-for-vertical-axis-without-tickmark-info? graph)))
	   desired-range-for-vertical-axis?
	   (range-too-small? nil))
      (if desired-absolute-or-relative-vertical-axis-range?
	  (multiple-value-setq
	    (desired-range-for-vertical-axis?
	     desired-low-value-for-vertical-axis?
	     desired-high-value-for-vertical-axis?)
	    (parse-desired-absolute-or-relative-range
	      desired-absolute-or-relative-vertical-axis-range?)))
      
      (cond
	(desired-low-value-for-vertical-axis?	       ; low and high values specified
	 (setq desired-high-value-for-vertical-axis
	       desired-high-value-for-vertical-axis?
	       desired-low-value-for-vertical-axis
	       desired-low-value-for-vertical-axis?))
	(t					       ; if moving window or no format specification
	 ;; check if data for graph exists
	 (if (loop with data-exists? = nil
		   for plot in (list-of-plots graph-grid)
		   do (if (data-exists-for-plot-p plot)
			  (setq data-exists? t))
		      (when (plot-min-and-max-given-plot plot)
			(setq problems-reformatting-graph? t)
			(add-frame-note
			  'plot-range-specs-without-vertical-axis-spec
			  graph nil t nil))
		   finally (return data-exists?))
	     (if (use-one-set-of-axes? graph-format)
		 (cond
		   (desired-range-for-vertical-axis?   ; moving window
		    ;; compute extrema
		    (loop for plot in (list-of-plots graph-grid)
;			  as plot-format = (plot-format plot)
;			  as data-buffer-for-plot = (data-buffer-for-plot plot)
;			  as most-recent-y-extremum
;			     = (if (data-exists-for-plot-p plot)
;				   (extract-number-or-value
;				     (most-recent-y-extremum plot)))
			  do
		      (if (data-exists-for-plot-p plot)
			  (let* ((most-recent-y-extremum
				   (extract-number-or-value
				     (most-recent-y-extremum plot)))
				 (opposite-y-extremum-of-most-recent
				   (extract-number-or-value
				     (opposite-y-extremum-of-most-recent plot)))
				 (most-recent-y-extremum-maximum-p
				   (> most-recent-y-extremum
				      opposite-y-extremum-of-most-recent)))
			    (if most-recent-y-extremum-maximum-p
				(setq desired-high-value-for-vertical-axis
				      (+ most-recent-y-extremum
					 (* desired-range-for-vertical-axis?
					    (coerce-to-gensym-float
					      (slot-value-number-value
						(extra-range-for-high-end-of-vertical-axis
						  graph-format)))))
				      desired-low-value-for-vertical-axis
				      (- desired-high-value-for-vertical-axis
					 desired-range-for-vertical-axis?))
				(setq desired-low-value-for-vertical-axis
				      (- most-recent-y-extremum
					 (* desired-range-for-vertical-axis?
					    (coerce-to-gensym-float
					      (slot-value-number-value
						(extra-range-for-low-end-of-vertical-axis
						  graph-format)))))
				      desired-high-value-for-vertical-axis
				      (+ desired-low-value-for-vertical-axis
					 desired-range-for-vertical-axis?)))
			    (return (values))))))
		   (t				       ; no format specification
		    ;; compute extrema
		    (loop with high-value-for-vertical-axis = nil
			  with low-value-for-vertical-axis = nil
			  for plot in (list-of-plots graph-grid)
;			  as plot-format = (plot-format plot)
;			  as data-buffer-for-plot = (data-buffer-for-plot plot)
;			  as most-recent-y-extremum
;			     = (if (data-exists-for-plot-p plot)
;				   (extract-number-or-value
;				     (most-recent-y-extremum plot)))
			  do
		      (if (data-exists-for-plot-p plot)
			  (let* ((most-recent-y-extremum
				   (extract-number-or-value
				     (most-recent-y-extremum plot)))
				 (opposite-y-extremum-of-most-recent
				   (extract-number-or-value
				     (opposite-y-extremum-of-most-recent plot)))
				 (most-recent-y-extremum-maximum-p
				   (> most-recent-y-extremum
				      opposite-y-extremum-of-most-recent)))
			    (if most-recent-y-extremum-maximum-p
				(setq high-value-for-vertical-axis
				      (if high-value-for-vertical-axis
					  (max high-value-for-vertical-axis
					       most-recent-y-extremum)
					  most-recent-y-extremum)
				      low-value-for-vertical-axis
				      (if low-value-for-vertical-axis
					  (min low-value-for-vertical-axis
					       opposite-y-extremum-of-most-recent)
					  opposite-y-extremum-of-most-recent))
				(setq low-value-for-vertical-axis
				      (if low-value-for-vertical-axis
					  (min low-value-for-vertical-axis
					       most-recent-y-extremum)
					  most-recent-y-extremum)
				      high-value-for-vertical-axis
				      (if high-value-for-vertical-axis
					  (max high-value-for-vertical-axis
					       opposite-y-extremum-of-most-recent)
					  opposite-y-extremum-of-most-recent)))))
			  finally
			    (let ((vertical-axis-data-range
				    (- high-value-for-vertical-axis
				       low-value-for-vertical-axis)))
			      (setq desired-high-value-for-vertical-axis
				    (+ high-value-for-vertical-axis
				       (* vertical-axis-data-range
					  (coerce-to-gensym-float
					    (slot-value-number-value
					      (extra-range-for-high-end-of-vertical-axis
						graph-format))))))
			      (setq desired-low-value-for-vertical-axis
				    (- low-value-for-vertical-axis
				       (* vertical-axis-data-range
					  (coerce-to-gensym-float
					    (slot-value-number-value
					      (extra-range-for-low-end-of-vertical-axis
						graph-format))))))))))
		 
		 ;; If (use-one-set-of-axes? graph-format) is nil
		 )
	     
	     ;; if no data for graph exists and low and high values not specified
	     ;; by user
	     (cond
	       (desired-range-for-vertical-axis?       ; moving window
		(setq desired-low-value-for-vertical-axis
		      (- (/ desired-range-for-vertical-axis? 2.0))
		      desired-high-value-for-vertical-axis
		      (/ desired-range-for-vertical-axis? 2.0)))
	       (t 
		(setq desired-low-value-for-vertical-axis
		      (- default-axis-half-range)
		      desired-high-value-for-vertical-axis
		      default-axis-half-range)	       ; determine-ruling-for-axis can handle this 
		)))))
      
      (multiple-value-bind
	(low-value-for-horizontal-grid-lines
	 high-value-for-horizontal-grid-lines
	 number-of-horizontal-grid-lines
	 interval-between-horizontal-grid-lines)
	  (determine-ruling-for-axis
	    desired-low-value-for-vertical-axis
	    desired-high-value-for-vertical-axis
	    nil
	    (when graph
	      (interval-between-horizontal-grid-lines? graph)))
	(setf (number-of-horizontal-grid-lines graph-grid)
	      number-of-horizontal-grid-lines)
	(store-managed-number-or-value
	  (low-value-for-horizontal-grid-lines graph-grid)
	  low-value-for-horizontal-grid-lines)
	(store-managed-number-or-value
	  (high-value-for-horizontal-grid-lines graph-grid)
	  high-value-for-horizontal-grid-lines)
	(store-managed-number-or-value
	  (interval-between-horizontal-grid-lines graph-grid)
	  interval-between-horizontal-grid-lines)
	
	(when (and range-too-small?
		   (or desired-low-value-for-vertical-axis?
		       desired-range-for-vertical-axis?))
	  (setq problems-reformatting-graph? t)
	  (add-frame-note 'desired-range-too-small graph nil t nil))
	
	(let ((low-value-for-vertical-axis
		low-value-for-horizontal-grid-lines)
	      (high-value-for-vertical-axis
		high-value-for-horizontal-grid-lines)
	      vertical-axis-range
	      (exact-specification?
		(and (not range-too-small?)
		     graph
		     (or
		       (slot-value-number-p desired-absolute-or-relative-vertical-axis-range?)
		       (and
			 (consp desired-absolute-or-relative-vertical-axis-range?)
			 (not
			   (or
			     (numberp 
			       (car desired-absolute-or-relative-vertical-axis-range?))
			     (managed-float-p (car desired-absolute-or-relative-vertical-axis-range?))))
			 (null 
			   (fourth 
			     desired-absolute-or-relative-vertical-axis-range?)))))))
	  (when exact-specification?
	    (setq low-value-for-vertical-axis
		  desired-low-value-for-vertical-axis
		  high-value-for-vertical-axis
		  desired-high-value-for-vertical-axis))
	  (setq vertical-axis-range 
		(- high-value-for-vertical-axis
		   low-value-for-vertical-axis))
	  (store-managed-number-or-value
	    (low-value-for-vertical-axis graph-grid) low-value-for-vertical-axis)
	  (store-managed-number-or-value
	    (high-value-for-vertical-axis graph-grid) high-value-for-vertical-axis)
	  (store-managed-number-or-value	     
	    (vertical-axis-range graph-grid) vertical-axis-range)
	  (store-managed-number-or-value
	    (horizontal-grid-line-spacing graph-grid)
	    (/ (* (coerce-to-gensym-float minimum-grid-height)
		  interval-between-horizontal-grid-lines)
	       vertical-axis-range))
	  (store-managed-number-or-value
	    (spacing-between-top-edge-and-grid-line graph-grid)
	    (/ (* (coerce-to-gensym-float minimum-grid-height)
		  (- interval-between-horizontal-grid-lines
		     (- high-value-for-horizontal-grid-lines 
			high-value-for-vertical-axis)))
	       vertical-axis-range))
	  ;; Horizontal grid line spacing is not truncated
	  ;; so that remainder can be accumulated
	  ;; so that first and last grid lines fall exactly on the margins when drawing.
	  ;; Gensym-floats are used because they are faster than ratios and do not cons.
	  ))
      )))

;; Note that if "exact" specifications are given, low and high value for vertical axis
;; are set to those specifications, even though they typically will not match low and
;; high values for horizontal grid lines.



;;; Put-up-new-labels-for-horizontal-graph-axis deletes any existing horizontal
;;; axis labels and puts up a complete new set.  If strip-chart?  is non-nil,
;;; strip-chart format, as opposed to universal time format, is used.  In
;;; strip-chart format, only the rightmost horizontal axis label (the label for
;;; the maximum value) shows universal time.  The other labels to the left of it
;;; show time intervals relative to the universal time.  This way, as the strip
;;; chart scrolls, only the rightmost label changes.  Strip-chart?  will be
;;; non-nil when an absolute range is not specified in the
;;; desired-range-for-horizontal-axis slot.  Thus, strip-chart format is used in
;;; cases where scrolling typically occurs while universal time format is used for
;;; "static", non-scrolling graphs.

(defun put-up-new-labels-for-horizontal-graph-axis
    (graph-grid graph-format strip-chart?)

  (with-temporary-gensym-float-creation
      put-up-new-labels-for-horizontal-graph-axis
    
    ;; remove horizontal axis labels
    (remove-axis-labels-from-graph-grid 'horizontal graph-grid)
    
    (setf (horizontal-axis-high-value-label graph-grid) nil)
    ;; make new horizontal axis labels and add them
    (let* ((digits-to-left-of-decimal-point nil)
	   (digits-to-right-of-decimal-point nil)
	   (horizontal-axis-is-time-axis? t)	       ; for now
	   (interval-between-grid-lines
	     (extract-number-or-value
	       (interval-between-vertical-grid-lines graph-grid))))
      (when (not horizontal-axis-is-time-axis?)
	(multiple-value-setq 
	    (digits-to-left-of-decimal-point digits-to-right-of-decimal-point)
	  (determine-format-for-non-time-axis-label
	    interval-between-grid-lines)))
      (loop with y-position-for-label
	      = (round
		  (+w (top-edge-of-block graph-grid) 
		      (grid-height-for-graph graph-grid)
		      (graph-top-margin-width graph-grid)
		      3				       ; fudge factor for spacing purposes
		      ))
	    with previous-x-position-for-label = nil
	    with x-position-for-last-label 
	      = (+w (left-edge-of-block graph-grid) 
		    (graph-left-margin-width graph-grid))
	    with number-of-vertical-grid-lines
	      = (number-of-vertical-grid-lines graph-grid)
	    with last-label
	      = (make-horizontal-axis-label
		  (-f number-of-vertical-grid-lines 1)
		  graph-grid strip-chart? t
		  horizontal-axis-is-time-axis? interval-between-grid-lines 
		  digits-to-left-of-decimal-point digits-to-right-of-decimal-point
		  (if (superblock? graph-grid)
		      (car (background-colors (superblock? graph-grid)))))
	    with width-of-last-label = (width-of-block last-label)
	    for label-number 
	    from -1 to (-f number-of-vertical-grid-lines 2)
	    as first-time? = t then nil
	    as last-time? 
	       = (=f label-number (-f number-of-vertical-grid-lines 2))
	    as new-horizontal-axis-label
	       = (if last-time?
		     last-label
		     (make-horizontal-axis-label
		       (+f label-number 1) graph-grid strip-chart? nil
		       horizontal-axis-is-time-axis? interval-between-grid-lines 
		       digits-to-left-of-decimal-point 
		       digits-to-right-of-decimal-point
		       (if (superblock? graph-grid)
			   (car (background-colors (superblock? graph-grid))))))
	    as width-of-label
	       = (width-of-block new-horizontal-axis-label)
	    as half-width-of-label
	       = (halfw width-of-label)
	    as x-position-for-label
	       = (cond
		   (first-time?
		    (-w (right-edge-of-block graph-grid) 
			(graph-right-margin-width graph-grid)
			width-of-label))
		   (last-time? x-position-for-last-label)
		   (t
		    (-w (right-edge-of-block graph-grid) 
			(graph-right-margin-width graph-grid)
			(round
			  (+ (extract-number-or-value
			       (spacing-between-right-edge-and-grid-line 
				 graph-grid))
			     (* label-number
				(+ (extract-number-or-value
				     (vertical-grid-line-spacing graph-grid))
				   (graph-vertical-grid-line-width graph-format)))))
			half-width-of-label)))
	    do
	(cond
	  ((and
	     (or first-time? last-time?
		 (and
		   (>w (-w previous-x-position-for-label x-position-for-label)
		       width-of-label)
		   (>w (-w x-position-for-label x-position-for-last-label)
		       width-of-last-label)))
	     (>w (grid-width-for-graph graph-grid)
		 width-of-label))
	   (setq previous-x-position-for-label
		 x-position-for-label)
	   (setf (horizontal-or-vertical-axis-label? new-horizontal-axis-label)
		 'horizontal)
	   (when first-time?
	     (setf (horizontal-axis-high-value-label graph-grid)
		   new-horizontal-axis-label))
	   (funcall-method 'shift new-horizontal-axis-label
			   x-position-for-label
			   y-position-for-label)
	   (add-subblock new-horizontal-axis-label graph-grid))
	  (t

	   (when first-time?
	     (setq previous-x-position-for-label x-position-for-label))
	   (delete-frame new-horizontal-axis-label)
	   ;; delete if not used
	   ;; Consider computing width of label without actually creating it.
	   ;; It would then be possible to reject it without having to reclaim!
	   ))))))

;; Note that subblocks (axis labels) are deleted not only if their  
;; horizontal-or-vertical-axis-label? slots eq 'horizontal but also if they
;; are nil.  This is necessary for old graphs which may have these labels 
;; saved. 

;; Note that because the first and last labels are always drawn, it is possible
;; for them to overlap if the graph becomes very small.  Consider having a 
;; minimum graph size to avoid this, or to not show the last label in this case.


(defun make-horizontal-axis-label 
       (label-number graph-grid strip-chart? low-value-label?
	horizontal-axis-is-time-axis? interval-between-grid-lines
	digits-to-left-of-decimal-point digits-to-right-of-decimal-point
	&optional background-color?)
  (if horizontal-axis-is-time-axis?
      (make-new-time-axis-label 
	label-number graph-grid strip-chart? low-value-label?
	background-color?)
      (make-new-variable-axis-label 
	(+ (extract-number-or-value
	     (low-value-for-horizontal-axis graph-grid))
	   (* label-number
	      interval-between-grid-lines))
	digits-to-left-of-decimal-point
	digits-to-right-of-decimal-point
	background-color?)))

;;; This third version of `put-up-new-high-value-label-for-horizontal-axis'
;;; attempts to update the current time display of a graph while remaining
;;; in synch with the "graphs have no subblocks" protocol established in
;;; the drawing harness in DRAW and PANES.  (jed 1/23/95)

(defun put-up-new-high-value-label-for-horizontal-axis (graph-grid)
  (let* ((new-label
	   (with-temporary-gensym-float-creation make-time-axis-label
	    (make-text-string-for-time-axis-label	; needs the float wrapper
	      0 graph-grid t nil)))
	 (graph (superblock? graph-grid))
	 (high-value-label
	   (horizontal-axis-high-value-label graph-grid))
	 (old-label-text-value
	   (box-translation-and-text high-value-label)))
    ;; erase it
    (update-images t graph graph
		   (left-edge-of-block high-value-label)
		   (top-edge-of-block high-value-label)
		   (right-edge-of-block high-value-label)
		   (bottom-edge-of-block high-value-label)
		   nil 'draw-graph-grid-current-time-display graph-grid)
    ;; clobber it
    (setf (box-translation-and-text high-value-label)
	  (slot-value-cons
	    no-value (convert-text-string-to-text new-label)))
    (reclaim-slot-value old-label-text-value)
    ;; draw it
    (update-images nil graph graph
		   (left-edge-of-block high-value-label)
		   (top-edge-of-block high-value-label)
		   (right-edge-of-block high-value-label)
		   (bottom-edge-of-block high-value-label)
		   nil 'draw-graph-grid-current-time-display graph-grid)))



(defun label-values-same-p (value-1 value-2 number-of-grid-lines)
  (let ((value-1-float (coerce-to-gensym-float value-1))
	(value-2-float (coerce-to-gensym-float value-2)))
    (declare (#.(gensym-float-type) value-1-float value-2-float))
    (<e (abs (-e value-1-float value-2-float))
	(/e minimum-range-to-maximum-value-ratio
	    (*e (coerce-to-gensym-float number-of-grid-lines) 10.0)))))

;; Label-values-same-p is necessary for comparing high-value-for-vertical-axis
;; and high-value-for-horizontal-grid-lines due to round-off error in computing
;; the latter.  The 10 is a fudge factor.


;;; Put-up-new-labels-for-vertical-graph-axis will not put up the first or last
;;; label if the top or bottom of the grid is not aligned with the grid lines,
;;; something that can happen if the "with all intervals the same" clause is not
;;; included in the desired range for vertical axis.  In other words, it only puts
;;; up labels along the grid lines.  The only disadvantage to this approach is
;;; that it can result in the minimum and maximum values of the graph not being
;;; clearly labelled.  However, this approach is more aesthetically pleasing and
;;; is a common practice in many graphs (see The Wall Street Journal for example).
;;; Furthermore, it allows for use of determine-format-for-non-time-axis-label
;;; which guarantees that labels contain no more than 4 digits.  This is not only
;;; aesthetic but also allows setting the left graph margin to a fixed width
;;; without having to worry about the largest possible label.

(defun put-up-new-labels-for-vertical-graph-axis
    (graph-grid graph-format)

  (with-temporary-gensym-float-creation
      put-up-new-labels-for-vertical-graph-axis
    
    ;; remove vertical axis labels
    (remove-axis-labels-from-graph-grid 'vertical graph-grid)
    
    ;; make new vertical axis labels and add them
    (let ((digits-to-left-of-decimal-point nil)
	  (digits-to-right-of-decimal-point nil)
	  (interval-between-grid-lines
	    (extract-number-or-value
	      (interval-between-horizontal-grid-lines graph-grid))))
      (multiple-value-setq 
	  (digits-to-left-of-decimal-point digits-to-right-of-decimal-point)
	(determine-format-for-non-time-axis-label
	  interval-between-grid-lines))
      (loop with previous-y-position-for-label = nil
	    with y-position-for-last-label
	      = (-w (bottom-edge-of-block graph-grid) 
		    (graph-bottom-margin-width graph-grid))
	    with number-of-horizontal-grid-lines
	      = (number-of-horizontal-grid-lines graph-grid)
	    with high-value-for-horizontal-grid-lines
	      = (extract-number-or-value
		  (high-value-for-horizontal-grid-lines graph-grid))
	    with low-label-value
	      = (extract-number-or-value
		  (low-value-for-vertical-axis graph-grid))
	    with skip-last-label?
	      = (not (label-values-same-p 
		       low-label-value
		       (extract-number-or-value
			 (low-value-for-horizontal-grid-lines graph-grid))
		       number-of-horizontal-grid-lines))
	    with new-vertical-axis-label and height-of-label and
	    x-position-for-label and y-position-for-label
	    for label-number 
	    from -1 to (-f number-of-horizontal-grid-lines 2)
;	    as second-time? = nil then first-time?
	    as first-time? = t then nil
	    as last-time? 
	       = (=f label-number 
		     (-f number-of-horizontal-grid-lines 2))
	    as label-value
	       = (cond 
		   (first-time?
		    (extract-number-or-value
		      (high-value-for-vertical-axis graph-grid)))
		   (last-time? low-label-value)
		   (t
		    (- high-value-for-horizontal-grid-lines
		       (* (+f label-number 1)
			  interval-between-grid-lines))))
	    as skip?
	       = (cond
		   (first-time?
		    (not (label-values-same-p
			   label-value high-value-for-horizontal-grid-lines
			   number-of-horizontal-grid-lines)))
		   (last-time? skip-last-label?))
	    when (not skip?)
	      do (setq new-vertical-axis-label
		       (make-new-variable-axis-label 
			 label-value digits-to-left-of-decimal-point 
			 digits-to-right-of-decimal-point
			 (if (superblock? graph-grid)
			     (car (background-colors (superblock? graph-grid)))))	; background color
		       height-of-label
		       (height-of-block new-vertical-axis-label)
		       x-position-for-label
		       (+w (left-edge-of-block graph-grid)
			   (graph-left-margin-width graph-grid)
			   (-w (width-of-block new-vertical-axis-label))
			   -3			       ; fudge factor for spacing purposes
			   )
		       y-position-for-label
		       (cond
			 (first-time?
			  (+w (top-edge-of-block graph-grid) 
			      (graph-top-margin-width graph-grid)
			      -3		       ; fudge factor
			      ))
			 (last-time?
			  (-w y-position-for-last-label
			      height-of-label
			      -3		       ; fudge factor
			      ))
			 (t
			  (+w (top-edge-of-block graph-grid) 
			      (graph-top-margin-width graph-grid)
			      (round
				(+ (extract-number-or-value
				     (spacing-between-top-edge-and-grid-line 
				       graph-grid))
				   (* label-number
				      (+ (extract-number-or-value
					   (horizontal-grid-line-spacing graph-grid))
					 (graph-horizontal-grid-line-width 
					   graph-format)))))
			      (-w (halfw height-of-label))))))
		 (cond
		   ((or (null previous-y-position-for-label)
			(and
			  (or last-time?
			      skip-last-label?
			      (>w (-w y-position-for-last-label 
				      y-position-for-label)
				  (*w height-of-label 2)))
			  (>w (-w y-position-for-label previous-y-position-for-label)
			      height-of-label)))
		    (setq previous-y-position-for-label
			  y-position-for-label)
		    (setf (horizontal-or-vertical-axis-label? new-vertical-axis-label)
			  'vertical)
		    (funcall-method 'shift new-vertical-axis-label
				    x-position-for-label
				    y-position-for-label)
		    (add-subblock new-vertical-axis-label graph-grid))
		   (t
		    (delete-frame new-vertical-axis-label)
		    ;; See note for put-up-new-labels-for-horizontal-graph-axis!
		    ))))))

;; Height-of-label should be the same for all labels.  If not, there is 
;; possible in certain cases for the last two labels to overlap 
;; somewhat.



;;; Remove-axis-labels-from-graph-grid takes an arg axis which can be 
;;; either 'horizontal or 'vertical.  It calls remove-as-subblock-if-necessary
;;; before delete-frame since otherwise, delete-frame will erase the label
;;; causing turds on the graph because it is an opaque block.

(defun remove-axis-labels-from-graph-grid (axis graph-grid)
  (loop for axis-label being each subblock of graph-grid
	do (when (and (not (label-permanent? axis-label))
		      (or (null (horizontal-or-vertical-axis-label? axis-label))
			  (eq (horizontal-or-vertical-axis-label? axis-label)
			      axis)))
	     (remove-as-subblock-if-necessary axis-label)
	     (delete-frame axis-label)
	     )))




(defun determine-format-for-non-time-axis-label
       (interval-between-grid-lines)
  (cond
    ((< interval-between-grid-lines 0.01)
     ;; range < 0.1
     ;; max < 10
     (values 1 3))
    ((< interval-between-grid-lines 0.1)
     ;; range < 1
     ;; max < 100
     (values 2 2))
    ((< interval-between-grid-lines 1)
     ;; range < 10
     ;; max < 1000
     (values 3 1))
    (t
     (values 4 0))))

;; Interval-between-grid-lines is 10^k * l
;; where k is an integer and l can be 1, 2, or 5 (see determine-ruling-for-axis).
;; since minimum-range-to-maximum-value-ratio is .01, the axis labels can always
;; be printed with 4 significant digits.  Thus, if interval < .01, then range
;; must be < .1 (since there can be at most 7 grid lines).  The maximum value of
;; the label must be < 10 (since minimum-range-to-maximum-value-ratio is .01 and
;; range < .1).  Therefore, only one digit is needed to the left of the decimal
;; point.  There will never be any need for more than 3 digits to the right of
;; the decimal point since minimum-range-to-maximum-value-ratio is also minimum
;; range.  This means that interval-between-grid-lines will never be less than
;; .001 (since there can be at most 7 grid lines).




(defun make-new-variable-axis-label 
       (label-value digits-to-left-of-decimal-point
	digits-to-right-of-decimal-point
	&optional background-color?)
  (make-graph-axis-label
    (twith-output-to-text-string
      (write-floating-point-number
	label-value digits-to-left-of-decimal-point
	digits-to-right-of-decimal-point 4))
    nil
    background-color?))


(defun make-new-time-axis-label 
       (label-number graph-grid strip-chart? low-value-label?
	&optional background-color?)
    (make-graph-axis-label
      (make-text-string-for-time-axis-label
	label-number graph-grid strip-chart? low-value-label?)
      nil
      background-color?))

(defun make-text-string-for-time-axis-label
       (label-number graph-grid strip-chart? low-value-label?)
  (let* ((label-interval
	   (cond 
	     (low-value-label?
	      (extract-number-or-value
		(horizontal-axis-range graph-grid)))
	     (t
	      (* label-number
		 (extract-number-or-value
		   (interval-between-vertical-grid-lines graph-grid))))))
	 (label-scale?
	   (label-scale-for-vertical-grid-lines graph-grid))
	 (print-time-relative-to-high-value?
	   (and strip-chart? (/=f label-number 0)))
	 second minute hour date month year day-of-week)
    
    (when (not print-time-relative-to-high-value?)
      (multiple-value-setq
	(second minute hour date month year day-of-week)
	(decode-gensym-time
	  (+f (round
		(cond				; label value
		  ((=f label-number 0)		; high value label
		   (extract-number-or-value
		     (high-value-for-horizontal-axis graph-grid)))
		  (low-value-label?
		   (extract-number-or-value
		     (low-value-for-horizontal-axis graph-grid)))
		  (t
		   (- (extract-number-or-value
			(high-value-for-vertical-grid-lines graph-grid))
		      label-interval))))
	      (clock-get gensym-time-at-start)))))
    
    ;; Label can be printed in one of the following formats:
    ;; <min.>:<sec.>
    ;; <hrs>:<min.>
    ;; <day-of-week>, <hr.>
    ;; <month>, <date>
    ;; <month>, <year>
    
    (twith-output-to-text-string
      (when print-time-relative-to-high-value?      
	(twrite-char #.%\-))
      (if label-scale?
	  (case label-scale?
	    ((60 3600)	   
	     (when print-time-relative-to-high-value?
	       (multiple-value-setq
		 (minute second)
		 (floorf label-interval 60)))
	     (print-minute-and-second minute second))
	    (86400	   
	     (cond
	       (print-time-relative-to-high-value?
		(multiple-value-bind
		  (hours minutes)
		    (floorf (roundf label-interval 60) 60)
		  (print-relative-hours-and-minutes hours minutes)))
	       (t (print-hour-and-minute hour minute))))
	    (259200	   
	     (cond
	       (print-time-relative-to-high-value?
;		(multiple-value-bind
;		  (days hours)
;		    (floorf (roundf label-interval 3600) 24)
;		  (print-relative-days-and-hours days hours)))
		;; Just printing hours is more concise.
		(print-relative-hours
		  (roundf label-interval 3600)))
	       (t
		(print-day-of-week-and-hour day-of-week hour))))
	    (2419200	   
	     (cond
	       (print-time-relative-to-high-value?
;		(multiple-value-bind
;		  (weeks days)
;		    (floorf (roundf label-interval 86400) 7)
;		  (print-relative-weeks-and-days weeks days))
		;; Just printing days is more concise.
		(print-relative-days
		  (roundf label-interval 86400)))
	       (t
		(print-month-and-date month date)))))	
	  (cond
	    (print-time-relative-to-high-value?
;	     (multiple-value-bind
;	       (years weeks)
;		 (floorf (roundf label-interval 604800) 52)
;	       (print-relative-years-and-weeks years weeks)))
	     ;; Just printing weeks is more concise.
	     (print-relative-weeks
	       (roundf label-interval 604800)))
	    (t
	     (print-month-and-year month year)))))))

;; I simplified the above function a bit -- more can be done.  Review subfunctions,
;; esp. use of abbreviations (e.g. "h." for "hour(s)", "d." for "day(s)".  The
;; superabbreviated abbreviations are needed to squeeze labels into a tight space.
;; 
;; (MHD 5/7/91)
;;
;;
;; Most subfunctions are only used by this function, but they should be maintained
;; in the section that deals with printing time.
;;
;; Therefore, Time subfunctions moved to FRAMES5, subsection "Times and Timestamps".
;; The commented-out subfunctions are also defined there, commented out.
;;
;; Maybe more of the whole above should go there, since other code might want to
;; employ the exact same fitting of time stamp or time interval text.
;; 
;; (MHD 5/15/91)

;; See also print-constant in GRAMMAR1








(defun put-up-label-for-graph-horizontal-axis (graph-grid graph-format)
  ;; make horizontal axis label and add it
;  (let* ((horizontal-axis-label
;	   (make-graph-axis-label
;	     (tformat-text-string "Time")  ; for now
;	     t))
;	 (x-position-for-label
;	   (+ (left-edge-of-block graph-grid)
;	      (halfw (grid-width-for-graph graph-grid))
;	      (minimum-graph-left-and-right-margin-width
;		graph-format)))
;	 (y-position-for-label
;	   (+ (top-edge-of-block graph-grid)
;	      (grid-height-for-graph graph-grid)
;	      (minimum-graph-top-and-bottom-margin-width
;		graph-format)
;	      (height-of-block horizontal-axis-label)
;	      (halfw (height-of-block horizontal-axis-label)))))
;    (funcall-method 'shift horizontal-axis-label
;		    x-position-for-label
;		    y-position-for-label)
;    (add-subblock horizontal-axis-label graph-grid))
  ;; For Now:
  graph-grid graph-format
  nil)


;;; Make-plot takes a display-expression as an argument and returns
;;; a plot for this display-expression.  The plot-format will be the
;;; default initial value when making a plot frame.  Thus, a plot
;;; can be assumed to always have a plot-format.  Note that when
;;; a frame is first made, it does not have any plots.  They can
;;; only be added by editing the expressions-to-display slot of
;;; the graph.  This means that make-or-reformat-graph-grid 
;;; never has to make plots;  it only has to reformat them.

(defun make-plot 
       (display-expression plot-color? plot-pattern? plot-min-and-max?
	graph-grid)
  (let* ((new-plot
	   (make-frame 'plot))
	 (plot-format
	   (get-or-make-format-frame 'default-plot-format))
	 (plot-color
	   (or plot-color?
	       (plot-line-color? plot-format)))
	 (current-block-of-dependent-frame
	   graph-grid))
    (setf (plot-format new-plot) plot-format
	  (display-expression-for-plot new-plot) display-expression
	  (plot-color new-plot)
	  (if (and (null plot-pattern?) (null plot-min-and-max?))
	      plot-color
	      (slot-value-cons
		plot-color
		(slot-value-cons 
		  plot-pattern?
		  (if plot-min-and-max?
		      (slot-value-cons plot-min-and-max? nil))))))
    new-plot))

;; Currently, plot-line-color? is 'black in the default plot format frame.
;; Thus, the plot-color slot will always have a non-nil value.  If formats are 
;; ever used where plot-line-color? is not specified, then the plot-color slot
;; should be set based on the graph line color in the graph format frame.




(defun refresh-data-for-plots
       (graph-grid graph-format horizontal-axis-grid-format-not-changed-p)
  (loop with width = (grid-width-for-graph graph-grid)
	for plot in (list-of-plots graph-grid)
	for plot-number from 1
	doing
    (cond
      ;; this check fixes BUG-004-5953
      ((> width 0)
       (refresh-plot-data-buffer
	 plot graph-grid graph-format
	 horizontal-axis-grid-format-not-changed-p
	 plot-number))
      (t
       (clear-plot plot)))))




(def-class-method compute-minimum-right-edge (graph-grid)
  (+w (left-edge-of-block graph-grid) (width-of-block graph-grid)))

(def-class-method compute-minimum-bottom-edge (graph-grid)
  (+w (top-edge-of-block graph-grid) (height-of-block graph-grid)))



(def-class-method resize (graph-grid right-edge-for-graph-grid bottom-edge-for-graph-grid
				other-data-for-resizing)
  graph-grid right-edge-for-graph-grid bottom-edge-for-graph-grid other-data-for-resizing)
;; talk to Lowell


;(def-class-method shift (graph-grid delta-x delta-y)
;  (cond
;    ((not (= delta-x 0))
;     (incf (left-edge-of-block graph-grid) delta-x)
;     (incf (right-edge-of-block graph-grid) delta-x)))
;  (cond
;    ((not (= delta-y 0))
;     (incf (top-edge-of-block graph-grid) delta-y)
;     (incf (bottom-edge-of-block graph-grid) delta-y)))
;  (loop for subblock being each subblock of graph-grid
;	doing (funcall-method 'shift subblock delta-x delta-y)))

;; Commented out since it is functionally identical to block's shift. - ben 10/22/91

;; May have to do something for labels which may be subblocks of graph.
;; Invoke 'shift method for them as well.
;; There are currently no labels which are subblocks of the graph rather
;; than the graph grid so there is no problem here. - agh, 2/11/88.


;;;; Automatic Formatting

;;; Ruling in automatic mode is determined by computing the range from the low
;;; and high values of data to be displayed, and then determining the 
;;; increment-per-ruling which will result in from 4 to 7 rulings over this
;;; range.  Four to seven rulings is a "good" number of rulings for a graph.
;;; Possible values for increment-per-ruling are given by
;;;
;;;                          k
;;; Increment-per-ruling = 10  * l
;;; where l = {1, 2, or 5}
;;; 

;;; A maximum and minimum number of rulings can be obtained by the following
;;; algorithm:
;;; Let
;;;   range = high-value - low-value
;;;   quotient = range / increment-per-ruling
;;;   truncated-quotient = (truncate quotient)
;;; if 
;;;   truncated-quotient <= l
;;; then
;;;   minimum-number-of-rulings = truncated-quotient + 1
;;;   maximum-number-of-rulings = truncated-quotient + 2
;;; else if
;;;   truncated-quotient > l
;;; then
;;;   minimum-number-of-rulings = truncated-quotient + 2
;;;   maximum-number-of-rulings = truncated-quotient + 3


;;; This is illustrated by the following examples.
;;; Suppose 
;;;   low-value = 213.5
;;;   high-value = 246.3.
;;; Therefore,
;;;   range = 32.8.
;;; 
;;; The next step is to divide the range by 10, 5, 2, and 1 successively until 
;;; a good number of rulings is reached.
;;; 
;;; First try
;;;   increment-per-rule = 10    (k = 1, l = 1)
;;;  
;;; Dividing range by 10 yields
;;;   quotient = 3.28 
;;; Therefore, by the above formula, there are 5 or 6 rulings which is in
;;; the acceptable range.  To find the actual number of rulings, find the 
;;; low rule first.
;;; Dividing the low value by the increment-per-rule yields
;;;   21.35.
;;; Truncating and multiplying by increment-per rule yields
;;;   low-rule = 210
;;; 
;;; Adding rules by increment-per-rule until the high-value is passed yields
;;;   rules = {210, 220, 230, 240, 250}
;;; 
;;; Suppose instead that
;;;   high-value = 346.3
;;; and
;;;   range = 132.8
;;; 
;;; Dividing by an increment-per-rule of 10 yields 13.28, which means 15 or
;;; 16 rulings which is too many.
;;; Next try k = 1 and l = 2, or increment-per-rule = 20.
;;; This yields a quotient of 6.64 which means 8 or 9 rulings, still too many.
;;; Therefore, try k = 1 and l = 5, or 
;;; increment-per-rule = 50.  This yields a quotient of 2.656.
;;; The low rule is 200 and
;;;   rules = {200, 250, 300, 350}
;;; which is in the acceptable range.


;;; Note on Number of Rulings

;;; Four to seven rulings is a good number of rulings for a graph.  Furthermore,
;;; it is always possible to find from four to seven rulings, regardless of the
;;; low and high values using the above formula for increment-per-ruling.
;;; The greatest change in increment-per-ruling is from 5m to 2m where m is 
;;; arbitrary.  Thus, a change from 5 to 2 represents the worst case.
;;; 
;;; Let
;;;   range = high-value - low-value
;;;   increment-per-rule = 5
;;;   quotient = range / 5
;;; 
;;; Suppose
;;;   2.0 < quotient <= 3.0
;;; 
;;; By the above constraints, this will always yield 4 or 5 rulings.
;;; For example, if 
;;;   low-value = 4.75
;;;   high-value = 15.25
;;;   range = 10.5
;;;   quotient = 2.1
;;; the rulings will be
;;;   rulings = {0, 5, 10, 15, 20}
;;; If 
;;;   low-value = 3.0
;;;   high-value = 13.5
;;;   range = 10.5
;;;   quotient = 2.1
;;; the rulings will be
;;;   rulings = {0, 5, 10, 15}
;;; 
;;; Suppose now that 
;;;   quotient = 2.0
;;; 
;;; It is now possible that the number of rules might only be 3.
;;; For example, if
;;;   low-value = 5
;;;   high-value = 15
;;; the rulings will be
;;;   rulings = {5, 10, 15}
;;; 
;;; In this case, try 
;;;   increment-per-rule = 2
;;;   quotient = 5
;;; By the above constraints, this will always yield 6 or 7 rulings.
;;; For example, if 
;;;   low-value = 5
;;;   high-value = 15
;;; the rulings will be
;;;   rulings = {4, 6, 8, 10, 12, 14, 16}




;;; Determine-ruling-for-axis takes a low-value and a high-value as
;;; arguments and returns low-ruling, high-ruling, number-of-rulings, and 
;;; increment-per-ruling.  The low and high values will be adjusted in 
;;; cases where the range divided by the (absolute) magnitude of the
;;; highest value is less than the parameter minimum-range-to-maximum-value-ratio.
;;; This occurs, for example, if the low value is 1,000,000,000, and the
;;; high value is 1,000,000,001.  In such cases, the values are spread 
;;; further apart to increase their range so that intervals between grid
;;; lines will be large enough so that ruling labels can be displayed
;;; with only 5 significant digits and no ruling labels will show the
;;; same value.  The only drawback to this approach is that in cases
;;; such as the above example, the vertical axis will have a range of
;;; 100,000 but the data will only vary by 1, resulting in the data
;;; being just a straight horizontal line on the graph.  The user can always
;;; get around this by offsetting the data himself.  In the above case,
;;; simply subtracting 1,000,000,000 from the display expression will work
;;; nicely.  Also, if the range itself is less than the parameter
;;; minimum-range-to-maximum-value-ratio, the range is adjusted so that
;;; it is greater, again for labelling reasons.

;; If desired-number-of-grid-lines is nil, a number will be calculated.
;; If it is a number, that number will be returned.  Actually, the 
;; desired-number-of-grid-lines capability is not implemented and is
;; not used at the moment.

(defun determine-ruling-for-axis
       (low-value high-value desired-number-of-grid-lines
	interval-between-rulings?)
  desired-number-of-grid-lines   ; not implemented yet!

  ;; Adjust low and high values if necessary.
  (let ((range (coerce-to-gensym-float (- high-value low-value)))
	(absolute-maximum (max (abs high-value) (abs low-value)))
	range-to-absolute-maximum-ratio
	ratio-offset range-offset)
    (cond
      ((= absolute-maximum 0)  ; range will also be 0 in this case
       (setq low-value
	     (- minimum-range-to-maximum-value-ratio)
	     high-value
	     minimum-range-to-maximum-value-ratio
	     range-too-small? t))
      (t
       (setq range-to-absolute-maximum-ratio  
	     (/ range absolute-maximum))
       ;; Range-to-absolute-maximum-ratio will never be greater than 2
       ;; and will typically be less.
       (setq ratio-offset
	     (*
	       (- minimum-range-to-maximum-value-ratio
		  range-to-absolute-maximum-ratio)
	       absolute-maximum))
       (when (> ratio-offset 0)
	 (setq low-value
	       (- low-value (/ ratio-offset 2))
	       high-value
	       (+ high-value (/ ratio-offset 2))
	       range-too-small? t))

       (when (< range minimum-range-to-maximum-value-ratio)
	 (setq range-offset
	       (- minimum-range-to-maximum-value-ratio
		  range)
	       low-value
	       (- low-value (/ range-offset 2))
	       high-value
	       (+ high-value (/ range-offset 2))
	       range-too-small? t)))))
  (cond
    (interval-between-rulings?
     (cond
       ((= (slot-value-number-value (car interval-between-rulings?)) 0)
	(setq problems-reformatting-graph?
	      'zero-interval-between-horizontal-grid-lines)
	(determine-rulings-automatically
	  low-value high-value))
       (t
	(determine-rulings-based-on-interval
	  low-value high-value interval-between-rulings?))))
    (t 
     (determine-rulings-automatically
       low-value high-value))))


(defun determine-rulings-based-on-interval
       (low-value high-value interval-between-rulings)
  (let* ((interval (slot-value-number-value (car interval-between-rulings)))
	 (base (rem (slot-value-number-value (cdr interval-between-rulings))
		    interval))
	 (low-ruling
	   (- (* (floor (/ (+ (coerce-to-gensym-float low-value) base) interval))
		 interval)
	      base))
	 (high-ruling
	   (+ (* (ceiling (/ (- (coerce-to-gensym-float high-value) base) interval))
		 interval)
	      base))
	 (number-of-rulings
	   (+f (round (/ (coerce-to-gensym-float (- high-ruling low-ruling))
			 interval))
	       1)))
    (cond
      ((>f number-of-rulings maximum-number-of-horizontal-grid-lines) ; jed 6/27/94
       (setq problems-reformatting-graph? t)
       (add-frame-note 'too-many-grid-lines *current-computation-frame* nil t nil)
       (determine-rulings-automatically low-value high-value))
      (t
       (values low-ruling high-ruling
	       number-of-rulings interval)))))


(defun determine-rulings-automatically (low-value high-value)
  (let ((range (coerce-to-gensym-float (- high-value low-value)))
	(l 1.0)
	(k 0.0)
	low-ruling
	high-ruling
	number-of-rulings
	quotient
	increment-per-ruling
	best-low-ruling
	best-high-ruling
	best-number-of-rulings
	best-increment-per-ruling
	(try-for-more-rulings? nil)
	)

    ;; find k such that 1 <= quotient <= 10
    (loop doing 
      (setq increment-per-ruling (expt 10.0 k))
      (setq quotient (/ range increment-per-ruling))
      (cond
	((> quotient 10.0)
	 (setq k (+ k 1.0)))
;	((< quotient 1.0)
;	 (setq k (- k 1.0)))
	((< quotient 0.1)
	 (setq k (- k 1.0)))
;; This comparison was changed because the original
;; was causing limit cycle looping in certain cases (due to roundoff
;; error).  Thus the check is less stringent.  It is actually not 
;; necessary since it is checked again in the following code.  A less
;; stringent check is left in due to (minor) efficiency considerations.
;; - agh, 2/23/88

	(t
	 (return
	   (loop doing
	     (setq low-ruling
		   (* (floor
			(/ (coerce-to-gensym-float low-value) increment-per-ruling))
		      increment-per-ruling))
	     (setq high-ruling
		   (* (ceiling
			(/ (coerce-to-gensym-float high-value) increment-per-ruling))
		      increment-per-ruling))
	     (setq number-of-rulings
		   (+f (round 
			 (/ (coerce-to-gensym-float (- high-ruling low-ruling))
			    increment-per-ruling))
		       1))
	     (cond 
	       ((< number-of-rulings 4)
		(setq k (- k 1.0)))
	       ((<= number-of-rulings   ; satisfactory
		    7)
		(setq best-low-ruling low-ruling
		      best-high-ruling high-ruling
		      best-number-of-rulings number-of-rulings
		      best-increment-per-ruling increment-per-ruling)
		(cond
		  ((=f number-of-rulings 7)
		   (return t))
		  (t
		   (setq try-for-more-rulings? t)
		   (cond
		     ((= l 1.0)
		      (setq k (- k 1.0)
			    l 5.0))
		     ((= l 2.0)
		      (setq l 1.0))
		     (t   ; (= l 5.0)
		      (setq l 2.0))))))
	       (t
		(cond 
		  (try-for-more-rulings? (return t))
		  ((= l 1.0)
		   (setq l 2.0))
		  ((= l 2.0)
		   (setq l 5.0))
		  (t
		   (error "Couldn't determine rulings~%")))))	;shouldn't happen
	     (setq increment-per-ruling
		   (* (expt 10.0 k) l)))))))

    (values best-low-ruling best-high-ruling
	    best-number-of-rulings best-increment-per-ruling)))

;; The mechanism to try for more rulings has been added (for 2.0) to improve the
;; appearance for graphs, especially when the top or bottom of graph is not
;; aligned with grid lines.



;;; Determine-ruling-for-time-axis is similar in function to 
;;; determine-ruling-for-axis but produces rulings more appropriate
;;; for time axes.

;;; The low ruling is offset so that it lines up on "nice" boundaries for 
;;; hours, minutes, and seconds.  If increment-per-ruling is one day or 
;;; greater, then low ruling will just be lined up with the beginning of
;;; the day.  If increment-per-ruling is four weeks or greater, then low
;;; ruling is lined up with the beginning of the month.  If ranges of 
;;; greater than one year are ever allowed, and if increment-per-ruling
;;; is one year or greater, then the low ruling should be lined up with
;;; the beginning of the year.  Note that if increment-per-ruling is
;;; 8 weeks, 16 weeks, etc. labels are printed in Month, Year format.
;;; Although the low ruling will be lined up with the beginning of the
;;; month (and will therefore correspond exactly to the label) subsequent
;;; rulings will be at constant 4 week (or whatever) intervals which means
;;; that the rulings will not exactly line up with the beginning of the
;;; month indicated by the label.  This is unavoidable since months
;;; do not all have the same number of days but the increment between
;;; rulings must be fixed.  This is a minor issue for such large
;;; time scales.  Consider making the time increments be multiples of 
;;; 30 days since this will result in less drift.

;;; User specified range is currently constrained (by the slot value compiler
;;; for horizontal-graph-ruling-parameter?) to be no more than 24 weeks.
;;; When no user range is specified, range is computed automatically based on
;;; history data.  Since history data range is constrained to 6 months,
;;; range will be constrained in this case also.

;;; Since range is constrained, low-ruling and high-ruling should always be
;;; fixnums, never bignums.  This is due to the current fixnum limit of
;;; 6 months for gensym time.

;; There is really no reason low-value and high-value shouldn't be integers
;; when they are passed to determine-ruling-for-time-axis.  Review this!!!

(defun determine-ruling-for-time-axis
       (low-value high-value desired-number-of-grid-lines
	minimum-number-of-grid-lines minimum-interval-between-grid-lines)

  ;; Low and high value are not necessarily integers at this point.
  ;; They must be converted.  Consider converting at some earlier point.

  (setq low-value (floor low-value)
	high-value (ceiling high-value))

  ;; Low and high value are now integers representing seconds.

  (let ((range (- high-value low-value))
	low-ruling
	high-ruling
	number-of-rulings
	increment-per-ruling
	label-scale
	)

    desired-number-of-grid-lines
    minimum-interval-between-grid-lines

    (cond
      ((<= range 5)
       (setq increment-per-ruling 1
	     label-scale 60))   ; label printed as minutes:seconds
      ((<= range 10)
       (setq increment-per-ruling 2
	     label-scale 60))
      ((<= range 20)
       (setq increment-per-ruling 5
	     label-scale 60))
      ((<= range 30)
       (setq increment-per-ruling 10
	     label-scale 60))
      ((<= range 60)  ; less than or equal to one minute
       (setq increment-per-ruling 15
	     label-scale 3600))  
      ((<= range 300)
       (setq increment-per-ruling 60
	     label-scale 3600)) 
      ((<= range 600)
       (setq increment-per-ruling 120
	     label-scale 3600))
      ((<= range 1800)
       (setq increment-per-ruling 600
	     label-scale 3600))
      ((<= range 3600)  ; less than or equal to one hour
       (setq increment-per-ruling 1200
	     label-scale 86400))  ; label printed as hours:minutes
      ((<= range 10800)
       (setq increment-per-ruling 3600  ; 1 hr.
	     label-scale 86400))
      ((<= range 21600)
       (setq increment-per-ruling 7200  ; 2 hrs.   
	     label-scale 86400))
      ((<= range 43200)
       (setq increment-per-ruling 10800  ; 3 hrs.
	     label-scale 86400))
      ((<= range 64800)
       (setq increment-per-ruling 43200  ; 12 hrs.
	     label-scale 259200))  ; label printed as day-of-week, hr.
;      ((< range 172800)  
;       (setq increment-per-ruling 86400   ; 1 day
;	     label-scale 259200))
;; Results in too many grid lines for this label format

      ((<= range 172800)     
       (setq increment-per-ruling 86400   ; 1 day
	     label-scale 2419200))  ; label printed as month, date
      ((<= range 518400) 
       (setq increment-per-ruling 172800
	     label-scale 2419200))
      ((<= range 864000)   ; less than or equal to 10 days
       (setq increment-per-ruling 259200
	     label-scale 2419200))	     
;      ((<= range 1209600)  ; less than or equal to two weeks
;       (setq increment-per-ruling 259200
;	     label-scale 2419200))
;; Results in too many grid lines for this label format

      ((<= range 1814400)  ; less than or equal to three weeks
       (setq increment-per-ruling 518400
	     label-scale 2419200))

;      ((<= range 2419200)  ; less than or equal to four weeks
;       (setq increment-per-ruling 518400
;	     label-scale 2419200))
;; Results in too many grid lines for this label format

      ((<= range 4233600)  ; less than or equal to seven weeks
       (setq increment-per-ruling 1209600
	     label-scale 2419200))
      ((<= range 4838400)  ; less than or equal to eight weeks
       (setq increment-per-ruling 1814400
	     label-scale 2419200))
      ((<= range 9676800)  ; less than or equal to sixteen weeks
       (setq increment-per-ruling 2419200))  ; label printed as month, year
      ((<= range 19353600)  ; less than or equal to 32 weeks
       (setq increment-per-ruling 4838400))
      (t 
       (setq range 19353600)   ; clamp range
       (setq increment-per-ruling 4838400)
       (setq low-value (- high-value range))  ; adjust low-value upwards
;       (setq high-value (+ low-value range))  ; adjust high-value down
       ))

    (with-temporary-bignum-creation
      (multiple-value-bind 
	(second minute hour date)
	  (decode-gensym-time
	    (+f low-value
		(clock-get gensym-time-at-start)))
	(let* ((seconds-since-beginning-of-day
		 (+f second (*f 60 minute) (*f 3600 hour)))
	       (days-since-beginning-of-month-in-seconds
		 (*f date 86400))
	       offset-for-low-ruling)
	  (cond
	    ((< increment-per-ruling 86400)  ; less than one day
	     (setq offset-for-low-ruling
		   (- seconds-since-beginning-of-day
		      (* (floor
			   (/ seconds-since-beginning-of-day
			      (coerce-to-gensym-float increment-per-ruling)))
			 increment-per-ruling))))
	    ((< increment-per-ruling 2419200)  ; less than four weeks
	     (setq offset-for-low-ruling seconds-since-beginning-of-day))
	    (t
	     ;; label printed as Month, Year
	     ;; Low ruling must be offset so that it begins at the
	     ;; beginning of the month
	     (setq offset-for-low-ruling
		   (+f seconds-since-beginning-of-day
		       days-since-beginning-of-month-in-seconds))))
	  (setq low-ruling
		(round
		  (- low-value offset-for-low-ruling))))))

    (setq number-of-rulings
	  (+f (ceiling 
		(/ (coerce-to-gensym-float (- high-value low-ruling))
		   increment-per-ruling))
	      1))
    (setq high-ruling
	  (+f low-ruling
	      (*f (-f number-of-rulings 1) increment-per-ruling)))

    (if (< number-of-rulings minimum-number-of-grid-lines)
	(progn
	  (setq high-ruling
		(+ high-ruling
		   (* increment-per-ruling
		      (- minimum-number-of-grid-lines
			 number-of-rulings))))
	  (setq number-of-rulings
		minimum-number-of-grid-lines)))

    ;; Low-ruling, high-ruling, increment-per-ruling have now been calculated
    ;; (in seconds).  Number-of-rulings has also been calculated.

    (values low-ruling high-ruling number-of-rulings increment-per-ruling
	    label-scale)))

;; Note that convert-gensym-time-to-decoded-universal-time is done in two places,
;; here and in make-new-time-axis-label.  It is necessary to do it here to 
;; line up the low ruling and it is necessary to do it when making the labels.

;; Use constants here instead of numbers to make clearer.



;;;; History Access Functions Used by Graphs

;; Moved here from HISTORIES - agh, 7/22/88


;(defun variable-plot-data-exists-p (variable-name-and-data-source)
;  (let* ((variable 
;	   (get-instance-with-name-if-any 'variable
;					  (car variable-name-and-data-source))))
;    (if variable
;	(let* ((data-source (cdr variable-name-and-data-source))
;	       (buffer-of-stored-values
;		 (cond
;		   ((eq data-source 'computed)
;		    (variable-or-parameter-stored-histories? variable))
;		   ((eq data-source 'simulated)
;		    (if (simulation-details variable)
;			(simulation-stored-histories?
;			  (simulation-details variable)))))))
;	  (and buffer-of-stored-values
;	       (not (ring-buffer-empty?
;		      buffer-of-stored-values)))))))

;; Consider sending some kind of error message, especially if 
;; history frames or simulation frames don't exist.


;(defun get-data-point-for-variable-plot
;       (data data-index)
;  (let* ((variable 
;	   (get-instance-with-name-if-any 'variable
;					  (car data)))
;	 (data-source (cdr data))
;	 (ring-buffer-of-stored-values
;	   (cond
;	     ((eq data-source 'computed)
;	      (variable-or-parameter-stored-histories? variable))
;	     ((eq data-source 'simulated)
;	      (if (simulation-details variable)
;		  (simulation-stored-histories?
;		    (simulation-details variable))))))
;	 (size-of-buffer
;	   (array-dimension (history-value-vector ring-buffer-of-stored-values) 0))
;	 (unwrapped-vector-index (+ (oldest-active-element-index
;				      ring-buffer-of-stored-values)
;				    data-index))
;	 (vector-index (mod unwrapped-vector-index
;			    size-of-buffer))
;	 (time-stamp (aref (history-time-vector ring-buffer-of-stored-values)
;			   vector-index))
;	 (stored-value (aref (history-time-vector ring-buffer-of-stored-values)
;			     vector-index))
;	 (last-value-p (= vector-index
;			  (newest-active-element-index
;			    ring-buffer-of-stored-values))))
;    (values time-stamp stored-value last-value-p)))

;; It is assumed here that the required history frames exist and
;; that the buffer is not empty.



(defun coerce-managed-float-or-fixnum-to-gensym-float (managed-float-or-fixnum)
  (if (managed-float-p managed-float-or-fixnum)
      (managed-float-value managed-float-or-fixnum)
      (coerce-fixnum-to-gensym-float managed-float-or-fixnum)))

(defmacro mutate-managed-float-value-given-number (location-to-mutate number)
  `(mutate-managed-float-value
     ,location-to-mutate (coerce-managed-float-or-fixnum-to-gensym-float ,number)))

(defun mutate-plot-min-given-plot-min-and-max (plot-min-and-max)
  (mutate-managed-float-value-given-number
    plot-min? (slot-value-number-value (car plot-min-and-max))))

(defun mutate-plot-max-given-plot-min-and-max (plot-min-and-max)
  (mutate-managed-float-value-given-number
      plot-max? (slot-value-number-value (cdr plot-min-and-max))))



(defmacro extend-plot-data-extrema-if-necessary
    (minimum-location maximum-location most-recent-extremum-maximum-p
     y-value first-time?)
  (avoiding-variable-capture
      (y-value first-time? &aux managed-float-value-y-value)
    `(let ((,managed-float-value-y-value (managed-float-value ,y-value)))
       (when (or ,first-time?
		 (<e ,managed-float-value-y-value
		     (managed-float-value ,minimum-location)))
	 (mutate-managed-float-value
	   ,minimum-location ,managed-float-value-y-value)
	 (setf ,most-recent-extremum-maximum-p ,first-time?))
       (when (or ,first-time?
		 (>e ,managed-float-value-y-value
		     (managed-float-value ,maximum-location)))
	 (mutate-managed-float-value
	   ,maximum-location ,managed-float-value-y-value)
	 (setf ,most-recent-extremum-maximum-p t)))))

;; This can evaluate minimum-location and maximum-location more than once,
;; which violates macro coding conventions! (MHD 9/23/93)



(defun store-min-and-max-plot-data-points
    (data-buffer-for-plot min-y max-y
     x-value-on-graph most-recent-extremum-maximum-for-pixel-p)
  (mutate-number-in-plot-data-ring-buffer
    data-buffer-for-plot
    'expand-plot-data-ring-buffer
    x-value-on-graph
    (if most-recent-extremum-maximum-for-pixel-p min-y max-y))
  (mutate-number-in-plot-data-ring-buffer
    data-buffer-for-plot
    'expand-plot-data-ring-buffer
    x-value-on-graph
    (if most-recent-extremum-maximum-for-pixel-p max-y min-y)))

(defmacro scale-and-extend-extrema-for-datapoints
	  (value-or-minimum-y-value-for-pixel
	   maximum-y-value-for-pixel
	   value-or-minimum-y-value-to-set
	   maximum-y-value-to-set
	   history-time)
  `(progn
     (when (not low-and-high-values-specified-for-vertical-axis?)
       (extend-plot-data-extrema-if-necessary
	 minimum-y-value maximum-y-value
	 most-recent-extremum-maximum-p
	 ,value-or-minimum-y-value-for-pixel 
	 (not minimum-and-maximum-y-value-set?))
       (extend-plot-data-extrema-if-necessary
	 minimum-y-value maximum-y-value
	 most-recent-extremum-maximum-p 
	 ,maximum-y-value-for-pixel 
	 (not minimum-and-maximum-y-value-set?))
       (setq minimum-and-maximum-y-value-set? t))
     ; Combine these two extends when both datapoints are passed.
	      
     (when scale-y-data-points?
       (when plot-min-and-max?
	 (compute-y-value-scaled-to-vertical-axis
	   ,value-or-minimum-y-value-for-pixel
	   ,value-or-minimum-y-value-for-pixel)
	 (compute-y-value-scaled-to-vertical-axis
	   ,maximum-y-value-for-pixel ,maximum-y-value-for-pixel)))
     
     (setq x-value-on-graph
	   (adjust-and-compute-x-value-on-graph
	     ,history-time erase-dateline current-graph-grid
	     (low-value-for-horizontal-axis current-graph-grid)))
	      
     (when scale-y-data-points?
       (setq ,value-or-minimum-y-value-to-set
	     (compute-y-value-on-graph-new-with-less-truncation
	       ,value-or-minimum-y-value-for-pixel)
	     ,maximum-y-value-to-set
	     (compute-y-value-on-graph-new-with-less-truncation
	       ,maximum-y-value-for-pixel)))

     (when (not x-data-min-set?)
       (setf (x-data-minimum current-plot) ,history-time)
       (setq x-data-min-set? t))))

(defmacro scale-and-extend-extrema-for-datapoints-simple
	  (value-or-minimum-y-value-for-pixel
	   value-or-minimum-y-value-to-set
	   history-time)
  `(progn
     (when (not low-and-high-values-specified-for-vertical-axis?)
       (extend-plot-data-extrema-if-necessary
	 minimum-y-value maximum-y-value
	 most-recent-extremum-maximum-p
	 ,value-or-minimum-y-value-for-pixel 
	 (not minimum-and-maximum-y-value-set?))
       (setq minimum-and-maximum-y-value-set? t))
     ; Combine these two extends when both datapoints are passed.
	      
     (when scale-y-data-points?
       (when plot-min-and-max?
	 (compute-y-value-scaled-to-vertical-axis
	   ,value-or-minimum-y-value-for-pixel
	   ,value-or-minimum-y-value-for-pixel)))
     
     (setq x-value-on-graph
	   (adjust-and-compute-x-value-on-graph
	     ,history-time
	     erase-dateline current-graph-grid
	     (low-value-for-horizontal-axis current-graph-grid)))
	      
     (when scale-y-data-points?
       (setq ,value-or-minimum-y-value-to-set
	     (compute-y-value-on-graph-new-with-less-truncation
	       ,value-or-minimum-y-value-for-pixel)))

     (when (not x-data-min-set?)
       (setf (x-data-minimum current-plot) ,history-time)
       (setq x-data-min-set? t))))

(defun store-new-element-in-plot-function	; unused (from unused macro above)
       (data-buffer-for-plot expansion-function plot-x-value plot-y-value)
  (store-new-element-in-plot-data-ring-buffer
    data-buffer-for-plot expansion-function
    plot-x-value plot-y-value))



(defun store-new-plot-data-1 (use-simulation-history?)
  (when (cond
	  (many-more-data-points-than-pixels?
	   (store-data-to-display-for-more-data-than-pixels-case
	     use-simulation-history?))
	  (t
	   (store-data-to-display-for-enough-pixels-case
	     use-simulation-history?)))
    (set-up-next-plot-marker-if-appropriate-for-new-plot-data)))



(defun set-up-next-plot-marker-if-appropriate-for-new-plot-data ()
  (when plot-marker?
    (let ((x-value-for-last-marker?
	    (x-value-for-last-marker? current-data-buffer-for-plot)))
      (when 
	  (if (null x-value-for-last-marker?)
	      (let (minimum-interval-for-first-marker)
		(mutate-managed-float-value
		  handy-float-1
		  (*e (coerce-fixnum-to-gensym-float
			interval-between-plot-markers)
		      offset-ratio-for-plot-markers
		      (coerce-fixnum-to-gensym-float
			current-plot-number)))
		(setq minimum-interval-for-first-marker
		      (round-for-graphs handy-float-1))
		(and
		  (>f (-f history-time-to-evaluate-display-expression-with
			  low-value-for-horizontal-axis)
		      minimum-interval-for-first-marker)
		  (>f history-time-to-evaluate-display-expression-with
		      minimum-interval-for-first-marker)))
	      (>f (-f history-time-to-evaluate-display-expression-with
		      x-value-for-last-marker?)
		  interval-between-plot-markers))
	(setf (x-value-for-last-marker? current-data-buffer-for-plot)
	      history-time-to-evaluate-display-expression-with
	      (plot-marker-indices current-data-buffer-for-plot)
	      (graph-cons
		(newest-active-element-index current-data-buffer-for-plot)
		(plot-marker-indices current-data-buffer-for-plot)))))))



;;; Set-up-time-and-data-at-current-index ... sets up the variables
;;; history-time-to-evaluate-display-expression-with, data-point-value,
;;; current-index, finished-storing-in-plot-data-1?, which are special
;;; variables.
;;;
;;; After setting up the time and data variables, it sets the variable
;;; finished-storing-in-plot-data-1? true iff index-for-stop-time =
;;; current-index.  If not, it advances current-index to the next active-element
;;; index.
;;;
;;; If a range problem is detected (overflowing the limits of gensym floats),
;;; the value becomes 0.0, and the flag problems-reformatting-graph? is set to
;;; DATA-POINT-NUMBER-UNDEFINED.

(defmacro get-history-fixnum-time (history index use-simulation-history?)
  `(floore-first (get-history-current-time ,history ,index ,use-simulation-history?)))

(defun set-up-time-and-data-at-current-index (use-simulation-history?)
  (setq history-time-to-evaluate-display-expression-with
	(get-history-fixnum-time
	  current-cascaded-ring-buffer current-index use-simulation-history?))
;	(get-history-time
;	  ring-buffer-for-history-time
;	  current-index))
  (mutate-managed-float-from-history-value
    data-point-value
    ring-buffer-for-history-time
    current-index)
  (let ((value (managed-float-value data-point-value)))
    (when (not (and (<=e value most-positive-gensym-float)
		    (>=e value most-negative-gensym-float)))
      (setq problems-reformatting-graph? 'data-point-number-undefined)
      (mutate-managed-float-value
	data-point-value 0.0d0)))
  (unless (setq finished-storing-in-plot-data-1?
		(=f current-index index-for-stop-time))
    (setq current-index
	  (increment-active-element-index
	    current-index
	    ring-buffer-for-history-time))))

;; The most-positive-gensym-float and most-negative-gensym-float checks are used
;; here to avoid the temporary gensym float consing that accompanies use of
;; exceptional-float-p.  When an exceptional-managed-float-p is written, it
;; should be used here instead!
;;
;; -- WHY INCLUSIVE CHECKING?!! (MHD 9/24/93)



(defun store-data-to-display-for-enough-pixels-case (use-simulation-history?)
  (set-up-time-and-data-at-current-index use-simulation-history?)  
  ;; Update extrema if necessary, and store value
  (cond
    (scale-y-data-points?
     (scale-and-extend-extrema-for-datapoints-simple
       data-point-value fixnum-minimum-y-value
       history-time-to-evaluate-display-expression-with)
     (mutate-number-in-plot-data-ring-buffer
       current-data-buffer-for-plot 'expand-plot-data-ring-buffer
       x-value-on-graph fixnum-minimum-y-value))
    (t
     (scale-and-extend-extrema-for-datapoints-simple
       data-point-value data-point-value
       history-time-to-evaluate-display-expression-with)
     (mutate-number-in-plot-data-ring-buffer
       current-data-buffer-for-plot 'expand-plot-data-ring-buffer
       x-value-on-graph data-point-value)))
  t)

(defun store-data-to-display-for-more-data-than-pixels-case
    (use-simulation-history?)
  ;; Loop over pixels until we actually see a pixel 
  ;; that contains data. (?) - ben 12/09/92
  (loop with extrema-set? = nil
	with rounded-history-time
	do (mutate-managed-float-value
	     last-history-time-for-data-point-on-pixel
	     (+e (managed-float-value history-time-per-pixel)
		 (managed-float-value
		   last-history-time-for-data-point-on-pixel)))
           (setq rounded-history-time
		 (round-for-graphs last-history-time-for-data-point-on-pixel))
    ;; Work on one pixel, looping on current-index until
    ;; either we exit the pixel, or we reach stop time. (?) - ben 12/09/92
	   (loop do (set-up-time-and-data-at-current-index
		      use-simulation-history?)
		    (when (progn
			    ;; yes, this is the slasher bug -- roundoff error!
			    ;; running with the #+slasher bug will give slashes
			    ;; across your graph under certain circumstances.
			    ;; (e.g., running /home/jed/graphbugs.kb)
			    ;; (MHD 9/24/93)
			    #-slasher
			    (>f history-time-to-evaluate-display-expression-with
				rounded-history-time)
			    #+slasher
			    (>e (coerce-fixnum-to-gensym-float
				  history-time-to-evaluate-display-expression-with)
				(managed-float-value
				  last-history-time-for-data-point-on-pixel)))
		      (return))
		    (extend-plot-data-extrema-if-necessary
		      minimum-y-value-for-pixel maximum-y-value-for-pixel
		      most-recent-extremum-maximum-for-pixel-p 
		      data-point-value
		      (not extrema-set?))
		    (setq extrema-set? t)
		 until finished-storing-in-plot-data-1?)
	   (when extrema-set?
	     ;; Update extrema if necessary, and store value
	     (cond
	       (scale-y-data-points?
		(scale-and-extend-extrema-for-datapoints
		  minimum-y-value-for-pixel maximum-y-value-for-pixel
		  fixnum-minimum-y-value fixnum-maximum-y-value
		  #+slasher		; another -- or more likely the REAL -- cause of
					;   the slasher bug!  (MHD 11/3/93)
		  rounded-history-time
		  #-slasher
		  history-time-to-evaluate-display-expression-with)
		(store-min-and-max-plot-data-points
		  current-data-buffer-for-plot
		  fixnum-minimum-y-value
		  fixnum-maximum-y-value
		  x-value-on-graph
		  most-recent-extremum-maximum-for-pixel-p))
	       (t
		(scale-and-extend-extrema-for-datapoints
		  minimum-y-value-for-pixel maximum-y-value-for-pixel
		  minimum-y-value-for-pixel maximum-y-value-for-pixel
		  history-time-to-evaluate-display-expression-with)
		(store-min-and-max-plot-data-points
		  current-data-buffer-for-plot
		  minimum-y-value-for-pixel
		  maximum-y-value-for-pixel
		  x-value-on-graph
		  #+slasher		; another -- or more likely the REAL -- cause of
					;   the slasher bug!  (MHD 11/3/93)
		  rounded-history-time
		  #-slasher
		  most-recent-extremum-maximum-for-pixel-p)))
	     (return t))))


(defun store-new-plot-data-3 ()
  (when (not low-and-high-values-specified-for-vertical-axis?)
    (cond
      (most-recent-extremum-maximum-p
       (store-managed-number-or-value 
	 (most-recent-y-extremum current-plot)
	 (extract-number-or-value maximum-y-value))
       (store-managed-number-or-value 
	 (opposite-y-extremum-of-most-recent current-plot)
	 (extract-number-or-value minimum-y-value)))
      (t
       (store-managed-number-or-value 
	 (most-recent-y-extremum current-plot)
	 (extract-number-or-value minimum-y-value))
       (store-managed-number-or-value 
	 (opposite-y-extremum-of-most-recent current-plot)
	 (extract-number-or-value maximum-y-value))))))



(defmacro store-new-plot-data
	  (plot data-buffer-for-plot display-expression
	   display-evaluation-should-use-simulated-values?
	   start-time stop-time
	   low-and-high-values-specified-for-vertical-axis?
	   graph-grid scale-y-data-points? 
	   plot-number low-value-for-horizontal-axis)
  (avoiding-variable-capture
      (plot low-and-high-values-specified-for-vertical-axis?
	    graph-grid data-buffer-for-plot)
    `(progn
       (when ,scale-y-data-points?
	 (mutate-managed-float-value-given-number
	   vertical-axis-range
	   (vertical-axis-range ,graph-grid))
	 (mutate-managed-float-value-given-number
	   low-value-for-vertical-axis
	   (low-value-for-vertical-axis ,graph-grid)))
       (with-temporary-gensym-float-creation store-plot-data-1
	 (store-new-plot-data-4
	   ,display-expression
	   ,graph-grid
	   ,start-time
	   ,plot
	   ,stop-time
	   ,display-evaluation-should-use-simulated-values?
	   ,low-and-high-values-specified-for-vertical-axis?
	   ,scale-y-data-points?
	   ,data-buffer-for-plot
	   ,plot-number
	   ,low-value-for-horizontal-axis)))))

;; Minimum-y-value and maximum-y-value contain floats whose values must be saved
;; outside the with-temporary-gensym-float-creation wrapper in which they are set.
;; Therefore, these must be stored as managed numbers.  Minimum-y-value-for-pixel,
;; maximum-y-value-for-pixel, and previous-data-point-value also must be accessed
;; outside the with-temporary-gensym-float-creation wrapper.  These values,
;; however, will only be floats if scale-y-data-points?  is nil.  Therefore, they
;; only have to be stored as managed numbers for this case.

;; Minimum-y-value-for-pixel, maximum-y-value-for-pixel, and
;; most-recent-extremum-maximum-for-pixel-p are used to implement a filtering
;; mechanism whereby a maximum of two y values are stored for a set of data points
;; that are all plotted on the same workspace x value on the graph.  This saves
;; drawing of lines and results in an appearance no different from one in which
;; all data points are stored in the plot data ring buffer (and all lines drawn).

;; The word "pixel" here currently means a workspace unit pixel.  This could
;; however be extended to mean a virtual pixel that is several workspace pixels
;; wide.  This simply results in a reduction in resolution of the graph and a
;; decrease in plot data buffer size and the number of lines that have to be
;; drawn.  Consider making this a parameter settable from the graph table.



(defun store-new-plot-data-with-scaling
       (plot data-buffer-for-plot display-expression
	display-evaluation-should-use-simulated-values?
	start-time newest-time
	minimum-time-interval-for-data-points
	low-and-high-values-specified-for-vertical-axis?-arg graph-grid
	plot-number low-value-for-horizontal-axis-arg)
  (declare (ignore minimum-time-interval-for-data-points))  ; not currently used
  (store-new-plot-data
    plot data-buffer-for-plot display-expression
    display-evaluation-should-use-simulated-values?
    start-time newest-time
    low-and-high-values-specified-for-vertical-axis?-arg graph-grid
    t plot-number low-value-for-horizontal-axis-arg))

(defun store-new-plot-data-without-scaling
       (plot data-buffer-for-plot display-expression
	display-evaluation-should-use-simulated-values?
	start-time newest-time
	minimum-time-interval-for-data-points
	low-and-high-values-specified-for-vertical-axis?-arg graph-grid
	plot-number low-value-for-horizontal-axis-arg)
  (declare (ignore minimum-time-interval-for-data-points))  ; not currently used
  (store-new-plot-data
    plot data-buffer-for-plot display-expression
    display-evaluation-should-use-simulated-values?
    start-time newest-time
    low-and-high-values-specified-for-vertical-axis?-arg graph-grid
    nil plot-number low-value-for-horizontal-axis-arg))



(defun scale-y-data-for-plots-if-necessary (graph-grid)
  (loop with grid-height = (grid-height-for-graph graph-grid)
	for plot in (list-of-plots graph-grid)
	do (when (need-to-scale-y-data? plot)
	     (scale-y-data-for-plot plot graph-grid))))

(defun scale-y-data-for-plot (plot graph-grid)
  (with-temporary-gensym-float-creation scale1
    (let ((data-buffer-for-plot 
	    (data-buffer-for-plot plot)))
      (when (not (ring-buffer-empty? data-buffer-for-plot))
	(let ((plot-min-and-max?
		(plot-min-and-max-given-plot plot)))
	  (mutate-managed-float-value-given-number
	    vertical-axis-range
	    (vertical-axis-range graph-grid))
	  (mutate-managed-float-value-given-number
	    low-value-for-vertical-axis
	    (low-value-for-vertical-axis graph-grid))
	  (when plot-min-and-max?
	    (mutate-plot-min-given-plot-min-and-max plot-min-and-max?)
	    (mutate-plot-max-given-plot-min-and-max plot-min-and-max?))
	  (loop as plot-index = (oldest-active-element-index 
				  data-buffer-for-plot)
			      then (increment-active-element-index
				     plot-index data-buffer-for-plot)
		do 
	    (if plot-min-and-max?
		;; data-point-value <- low + range * (arg1 - min)/(max - min)
		(compute-y-value-scaled-to-vertical-axis
		  (managed-svref (plot-y-value-vector data-buffer-for-plot) plot-index)
		  data-point-value)
		(mutate-managed-float-value-given-number
		  data-point-value
		  (managed-svref (plot-y-value-vector data-buffer-for-plot) plot-index)))
	    (with-temporary-gensym-float-creation scale2
	      (set-plot-y-value
		data-buffer-for-plot plot-index
		;; grid-height - round((grid-height * (value - low))/range)
		(compute-y-value-on-graph-new-with-less-truncation
		  data-point-value)))
		until (=f plot-index 
			  (newest-active-element-index 
			    data-buffer-for-plot))))))))



;;; Refresh-plot-data-buffer takes plot, graph-grid, graph-format, 
;;; and horizontal-axis-grid-format-not-changed-p as arguments.
;;; If horizontal-axis-grid-format-not-changed-p is nil, then the entire
;;; plot data buffer will be refreshed.  In this case, all data on the
;;; graph must be completely erased before the plot data buffer is
;;; refreshed (see make-or-reformat-graph-grid).  
;;; If horizontal-axis-grid-format-not-changed-p is t, new data will be added
;;; to the buffer and old data discarded.  The data is actually not discarded
;;; until it is erased;  it is the responsibility of the draw function
;;; to erase data that has to be erased and actually discard the old data.
;;; The data boundary indices indicate to the draw function what data
;;; to erase and discard, and also what new data to draw.

;;; Note that at this point, the special variables 
;;; low-value-for-vertical-grid-lines,
;;; high-value-for-vertical-grid-lines, and minimum-grid-width
;;; have had their new values computed by 
;;; compute-new-parameters-for-horizontal-axis-of-grid (in make-or-reformat-graph-grid).  
;;; Thus, the low and high values, as well as the length of the horizontal
;;; axis are known at this point.

;;; There are two basic schemes for refreshing the plot data buffer:

;;; 1.  Evaluate the display expression at regularly spaced history time intervals
;;; between low-value-for-vertical-grid-lines and 
;;; high-value-for-vertical-grid-lines, putting the results into the plot data 
;;; buffer.  The time interval is computed from low-value-for-vertical-grid-lines,
;;; high-value-for-vertical-grid-lines, and minimum-grid-width.
;;; Thus, the plot data buffer is filled with data points at regularly spaced 
;;; intervals and the number of these data points remains fixed regardless
;;; of the horizontal axis formatting.  Therefore, the time to refresh and
;;; draw will not be a function of the reformatting.
;;; 2.  Data driven - store every data point (between times
;;; low-value-for-vertical-grid-lines and high-value-for-vertical-grid-lines 
;;; from the history buffers.

;;; For both these approaches, the plot data buffer will never contain data that
;;; is outside of the new horizontal axis range.

;;; The data driven approach is more complicated (especially when the display expression
;;; is more than just a variable) but it gives a completely accurate picture of the
;;; history.  An important drawback to this approach (besides complexity), is that
;;; when a complete refresh has to be done, if the horizontal axis covers a wide
;;; time-span, it will take a long time to refresh the plot data buffer since
;;; every data point is stored.  The advantage of keeping all the data is that
;;; the buffer will not have to be completely refreshed
;;; when the time-span of the horizontal axis decreases.

;;; Currently, the first scheme is used.  Consider implementing a hybrid approach 
;;; where each data point is stored if its duration is greater than the time
;;; interval computed for regular spacing evaluation.



(defun refresh-plot-data-buffer
       (plot graph-grid graph-format
	horizontal-axis-grid-format-not-changed-p plot-number)
  (with-temporary-gensym-float-creation refresh-plot
    (let* ((current-block-of-dependent-frame graph-grid)
	   (data-buffer-for-plot
	     (if (null (data-buffer-for-plot plot))
		 (setf (data-buffer-for-plot plot)
		       (get-or-make-smallest-plot-data-ring-buffer))
		 (data-buffer-for-plot plot)))
	   (display-expression (display-expression-for-plot plot))
	   (graph (superblock? graph-grid))
	   (low-and-high-values-specified-for-vertical-axis?
	     ;; This is useful for deciding whether to maintain
	     ;; plot data extrema.
	     (low-and-high-values-specified-for-vertical-axis? graph))
	   (display-evaluation-should-use-simulated-values?
	     (display-evaluation-should-use-simulated-values? graph))
	   (minimum-width-of-data-point
	     (/ (minimum-distance-for-data-points graph-format)
		3.0)  				       ; for now anyway
	     )
	   ;; minimum-width-of-data-point determines the granularity of
	   ;; the plotted data
	   
	   (high-value-for-horizontal-axis
	     (high-value-for-horizontal-axis graph-grid))
	   (low-value-for-horizontal-axis
	     (low-value-for-horizontal-axis graph-grid))
	   (minimum-time-interval-for-data-points
	     (* (- high-value-for-horizontal-axis
		   low-value-for-horizontal-axis)
		(/ (coerce-to-gensym-float minimum-width-of-data-point)
		   minimum-grid-width)))
	   (time-of-oldest-data-point
	     (compute-time-of-oldest-data-point
	       display-expression 
	       display-evaluation-should-use-simulated-values?))
	   (time-of-newest-data-point
	     (compute-time-of-newest-data-point
	       display-expression 
	       display-evaluation-should-use-simulated-values?)))
      
      (setq minimum-time-interval-for-data-points
	    (max 1 (round minimum-time-interval-for-data-points)))
      
      (when time-of-oldest-data-point		       ; if data exists
	(cond
	  ((or (not horizontal-axis-grid-format-not-changed-p)
	       (ring-buffer-empty? data-buffer-for-plot))
	   ;; have to refresh entire buffer
	   ;; first clear buffer
	   (set-oldest-active-element-index data-buffer-for-plot 0)
	   (set-newest-active-element-index data-buffer-for-plot 0)
	   (set-ring-buffer-empty? data-buffer-for-plot t)
	   (clear-plot-marker-data data-buffer-for-plot)	   
	   (setf (old-data-boundary-index data-buffer-for-plot) nil
	         (new-data-boundary-index data-buffer-for-plot)
		 (newest-active-element-index data-buffer-for-plot)
		 (draw-new-first-data-point? data-buffer-for-plot) nil)
	   ;; This has to be done just before storing new values.
	   (let ((start-time		; no data beyond axis boundary
		   (max low-value-for-horizontal-axis time-of-oldest-data-point))
		 (stop-time		; no data beyond axis boundary
		   (min high-value-for-horizontal-axis time-of-newest-data-point)))
	     ;; Store new values
	     (when (not (>f start-time stop-time))
	       (store-new-plot-data-without-scaling
		 plot data-buffer-for-plot display-expression
		 display-evaluation-should-use-simulated-values?
		 start-time stop-time
		 minimum-time-interval-for-data-points
		 low-and-high-values-specified-for-vertical-axis? graph-grid
		 plot-number low-value-for-horizontal-axis)))
	   (when (not (ring-buffer-empty? data-buffer-for-plot))
	     (setf (draw-new-first-data-point? data-buffer-for-plot) t))
	   (setf (need-to-scale-y-data? plot) t))	  
	  (t					       ; if don't have to refresh entire buffer
	   (let* ((obsolete-data-boundary-time
		    (max time-of-oldest-data-point low-value-for-horizontal-axis))
		  (grid-width (grid-width-for-graph graph-grid))
		  (newest-time		; no data beyond axis boundary
		    (min high-value-for-horizontal-axis time-of-newest-data-point)))
	     ;; this setf is what breaks the camel's back - JED 7/19/94
	     (setf (oldest-active-element-index data-buffer-for-plot)
		   (newest-active-element-index data-buffer-for-plot)
		   (new-data-boundary-index data-buffer-for-plot)
		   (newest-active-element-index data-buffer-for-plot)
		   (draw-new-first-data-point? data-buffer-for-plot) nil)
	     (reclaim-plot-marker-indices (plot-marker-indices data-buffer-for-plot))
	     (setf (plot-marker-indices data-buffer-for-plot) nil)	     
	     ;; Store new values
	     (let* ((start-time		; no data beyond axis boundary
		      (max low-value-for-horizontal-axis
			   (if (ring-buffer-empty? data-buffer-for-plot)
			       time-of-oldest-data-point
			       (max time-of-oldest-data-point
				    (+ (extract-number-or-value
					 (x-data-maximum plot))
				       1))))))
	       (when (not (> start-time newest-time))
		 (store-new-plot-data-with-scaling
		   plot data-buffer-for-plot display-expression
		   display-evaluation-should-use-simulated-values?
		   start-time newest-time
		   minimum-time-interval-for-data-points
		   low-and-high-values-specified-for-vertical-axis? graph-grid
		   plot-number low-value-for-horizontal-axis)))
	     ;; (print-contents-of-plot-data-buffer data-buffer-for-plot) ; to debug
	     (setf (need-to-scale-y-data? plot) nil)
	     (store-managed-number-or-value 
	       (x-data-minimum plot) obsolete-data-boundary-time))))))))

;; Minimum-time-interval-for-data-points is no longer used to skip over data
;; points in the history buffer; every history point is considered (see
;; store-new-plot-data).  This ensures that none are missed when the horizontal
;; axis range is large.  The code that did this filtering has been commented out
;; but not deleted.  Consider putting it back in as an option controlled by a slot
;; in the graph table.

;; Plot data buffers contain only fixnums, no floats.

;; For now, the only kind of display expression allowed for graphs
;; is a designation which entity evaluates to a variable.

;; Review whether y-extrema could be maintained in workspace units 
;; rather than floats.

;; It will be somewhat easier to allow for general display expressions
;; for simulated values rather than inferred values (because simulated
;; values are always current and are updated synchronously).  As with
;; expressions using inferred values, it will be necessary to use the
;; function (yet to be implemented) which returns all the variables in
;; an expression.  The variables are then passed to a function which
;; computes the time of the next new value given some time.  Finally,
;; the expression if evaluated for that history time.

;; Actually, a simpler (although less accurate mechanism) would be to
;; implement an evaluator which evaluates any expression for some
;; historical time.  The expression could then be evaluated at regular
;; history intervals to get the plot data.




(defun low-and-high-values-specified-for-vertical-axis? (graph)
  (let ((desired-range? (desired-range-for-vertical-axis-without-tickmark-info? graph)))
    (and (not (slot-value-number-p desired-range?))
	 (consp desired-range?)
	 (eq (car desired-range?) '\;))))


(defmacro get-history-from-simulation-subtable?
	  (variable-or-parameter display-evaluation-should-use-simulated-values?)
  `(and ,display-evaluation-should-use-simulated-values?
	(not (parameter-p ,variable-or-parameter))))



;;; Get-variable-given-graph-expression entity evaluates graph-expression
;;; and returns the result if it is a variable.  Currently, graph-expressions
;;; are constant-designations and should always evaluate to variables.
;;; This will have to be extended when more general expressions are allowed.

(defun variable-has-subsecond-history-p (variable use-simulator-p)
  (let* ((history-spec?
	  (cond
	    ((and (get-history-from-simulation-subtable? variable use-simulator-p)
		  (simulation-details variable))
	     (simulation-stored-history-specification? (simulation-details variable)))
	    (t
	     (variable-or-parameter-history-specification? variable))))
	 (granularity?
	   (and history-spec? (cadddr history-spec?))))
    (and granularity?
	 (/=f granularity? 1000)))) ; granularity is stored as milleseconds in fixnum

(defun get-variable-given-graph-expression (graph-expression
					     display-evaluation-should-use-simulated-values?)
  (when (or system-is-running system-has-paused)
    (let* ((*variables-that-did-not-have-values* nil)
	   (current-computation-flags current-computation-flags)
	   (variable? nil))
      (setf (role-serve-inactive-objects?) t)
      (setq variable? (evaluate-designation graph-expression nil))
      (cond
	((and (framep variable?)
	      (frame-of-class-p variable? 'variable-or-parameter))
	 (cond
	   ((variable-has-subsecond-history-p variable?
					      display-evaluation-should-use-simulated-values?)
	    (when redraw-as-well-as-reformat-p	; if not already in on-window context
	      (warning-message* 
		  1
		  "The graph expression \"~ND\" evaluated to a variable or parameter with subsecond histories."
		graph-expression))
	    nil)
	   (t
	    variable?)))
	(t
	 (when (temporary-constant-p variable?)
	   (reclaim-temporary-constant variable?))
	 (when (and redraw-as-well-as-reformat-p  ; if not already in on-window context
		    (not painting-for-graph-activation-p))
	   (warning-message* 
	     1 "The graph expression \"~ND\" did not evaluate to a variable or parameter."
	     graph-expression))
	 nil)))))





;;; Compute-time-of-oldest-data-point takes as arguments
;;; display-expression and
;;; display-evaluation-should-use-simulated-values?  and returns the
;;; time of the oldest data point using history buffers.  The oldest
;;; value of the display expression can only be as old as the oldest
;;; value of any of the variables in the expression.
;;; Nil will be returned if there are no data points
;;; (if there is no history).

(defun compute-time-of-oldest-data-point
       (display-expression 
	display-evaluation-should-use-simulated-values?)
  (let ((variable? (get-variable-given-graph-expression
		     display-expression
		     display-evaluation-should-use-simulated-values?)))
    (when variable?
      (compute-time-of-oldest-data-point-given-variable
	variable?
	display-evaluation-should-use-simulated-values?))))

(defun compute-time-of-oldest-data-point-given-variable
       (variable-or-parameter display-evaluation-should-use-simulated-values?)
  (let* ((simulation-subtable?
	   (when (variable-p variable-or-parameter)
	     (simulation-details variable-or-parameter)))
	 (use-simulation-history?
	   (get-history-from-simulation-subtable?
	     variable-or-parameter
	     display-evaluation-should-use-simulated-values?))
	 (history-buffer-of-stored-values
	   (if use-simulation-history?
	       (if simulation-subtable?
		   (simulation-stored-histories?
		     simulation-subtable?))
	       (variable-or-parameter-stored-histories? variable-or-parameter)))
	 (history-ring-buffer-or-cascade
	   (when history-buffer-of-stored-values
	     (car (cascaded-ring-buffers history-buffer-of-stored-values)))))
    (if (and history-ring-buffer-or-cascade
	     (not (ring-buffer-or-cascade-empty? history-ring-buffer-or-cascade)))
	(get-history-fixnum-time
	  history-buffer-of-stored-values
	  (get-oldest-active-element-index-for-ring-buffer-or-cascade
	    history-ring-buffer-or-cascade)
	  use-simulation-history?))))
;	(get-history-time-for-ring-buffer-or-cascade
;	  history-ring-buffer-or-cascade
;	  (get-oldest-active-element-index-for-ring-buffer-or-cascade
;	    history-ring-buffer-or-cascade)))))

;; When cascaded ring buffer mechanism is hooked up,
;; history-ring-buffer-or-cascade should be set to history-buffer-of-stored-values
;; if there is more than one ring buffer in the cascaded-ring-buffers slot.



;;; Compute-time-of-newest-data-point is like compute-time-of-oldest-data-point.

(defun compute-time-of-newest-data-point
       (display-expression 
	display-evaluation-should-use-simulated-values?)
  (let ((variable? (get-variable-given-graph-expression
		     display-expression
		     display-evaluation-should-use-simulated-values?)))
    (when variable?
      (compute-time-of-newest-data-point-given-variable
	variable?
	display-evaluation-should-use-simulated-values?))))

(defun compute-time-of-newest-data-point-given-variable
       (variable-or-parameter display-evaluation-should-use-simulated-values?)
  (let* ((simulation-subtable?
	   (when (variable-p variable-or-parameter)
	     (simulation-details variable-or-parameter)))
	 (use-simulation-history?
	   (get-history-from-simulation-subtable?
	     variable-or-parameter
	     display-evaluation-should-use-simulated-values?))
	 (history-buffer-of-stored-values
	   (if use-simulation-history?
	       (if simulation-subtable?
		   (simulation-stored-histories?
		     simulation-subtable?))
	       (variable-or-parameter-stored-histories? variable-or-parameter)))
	 (history-ring-buffer-or-cascade
	   (when history-buffer-of-stored-values
	     (car (cascaded-ring-buffers history-buffer-of-stored-values)))))
    (if (and history-ring-buffer-or-cascade
	     (not (ring-buffer-or-cascade-empty? history-ring-buffer-or-cascade)))
	(get-history-fixnum-time
	  history-buffer-of-stored-values
	  (get-newest-active-element-index-for-ring-buffer-or-cascade
	    history-ring-buffer-or-cascade)
	  use-simulation-history?))))
;	(get-history-time-for-ring-buffer-or-cascade
;	  history-ring-buffer-or-cascade
;	  (get-newest-active-element-index-for-ring-buffer-or-cascade
;	    history-ring-buffer-or-cascade)))))

;; When cascaded ring buffer mechanism is hooked up,
;; history-ring-buffer-or-cascade should be set to history-buffer-of-stored-values
;; if there is more than one ring buffer in the cascaded-ring-buffers slot.



;;; Compute-time-for-next-value takes as arguments display-expression,
;;; history-time, and display-evaluation-should-use-simulated-values?
;;; and returns the time for the next new value of display-expression
;;; after history-time using history buffers.  If there are no more new
;;; values, then nil is returned.  Note that in order for a
;;; display-expression to have a value at some time, all variables in
;;; the expression must also have current values at that time.

;(defun compute-time-for-next-value
;       (display-expression history-time
;	display-evaluation-should-use-simulated-values?)
;  (compute-time-for-next-value-given-variable-name
;    display-expression history-time
;    display-evaluation-should-use-simulated-values?))
;
;
;(defun compute-time-for-next-value-given-variable-name
;       (variable-name history-time
;	display-evaluation-should-use-simulated-values?)
;  (let* ((variable
;	   (get-instance-with-name-if-any 'variable variable-name))
;	 (history-buffer-of-stored-values
;	   (if display-evaluation-should-use-simulated-values?
;	       (simulation-stored-histories?
;		 (simulation-details variable))
;	       (variable-or-parameter-stored-histories? variable)))
;	 (oldest-active-element-index
;	   (get-oldest-active-element-index-for-cascaded-ring-buffer
;	     history-buffer-of-stored-values))
;	 (newest-active-element-index
;	   (get-newest-active-element-index-for-cascaded-ring-buffer
;	     history-buffer-of-stored-values))
;	 (newest-active-element-index-1  ; needed because previous index is altered
;	   (get-newest-active-element-index-for-cascaded-ring-buffer
;	     history-buffer-of-stored-values)))
;
;    (prog1
;      (if (eq history-time 'long-time-ago)
;	  (get-history-time-for-cascaded-ring-buffer
;	    history-buffer-of-stored-values
;	    oldest-active-element-index)
;	  (loop as element-index
;		   = newest-active-element-index
;		   then (decrement-active-element-index-for-cascaded-ring-buffer
;			  element-index history-buffer-of-stored-values)
;		as next-history-time = (get-history-time-for-cascaded-ring-buffer
;					 history-buffer-of-stored-values
;					 element-index)
;		while (and (> next-history-time history-time)
;			   (not (cascaded-ring-buffer-indices-same-p
;				  element-index
;				  oldest-active-element-index)))
;		finally
;		  (return
;		    (cond
;		      ((and (cascaded-ring-buffer-indices-same-p
;			      element-index
;			      newest-active-element-index-1)
;			    (not (> next-history-time history-time)))
;		       nil)
;		      ((and (cascaded-ring-buffer-indices-same-p
;			      element-index
;			      oldest-active-element-index)
;			    (> next-history-time history-time))
;		       next-history-time)
;		      (t
;		       (get-history-time-for-cascaded-ring-buffer
;			 history-buffer-of-stored-values
;			 (increment-active-element-index-for-cascaded-ring-buffer
;			   element-index history-buffer-of-stored-values)))))))
;
;      (reclaim-element-index-for-cascaded-ring-buffer oldest-active-element-index)
;      (reclaim-element-index-for-cascaded-ring-buffer newest-active-element-index)
;      (reclaim-element-index-for-cascaded-ring-buffer newest-active-element-index-1)
;      )))
;; Should probably also return how long this value lasts.


;;; Get-value-at-history-time takes as arguments display-expression,
;;; history-time, and display-evaluation-should-use-simulated-values?
;;; the value of display-expression at history-time.  This should use
;;; the current inference engine and simulation evaluators (with
;;; appropriate special variables bound) to make the evaluation.

;; This is also the reason that the function compute-time-for-next-value
;; is separated.  Compute-time-for-next-value does not have to 
;; evaluate the display expression; it only needs the variables in
;; the expression.  It would thus be inefficient to perform the
;; function of compute-time-for-next-value using the evaluators.

;; Get-value-at-history-time is relatively easy to implement for the
;; simulator.  Currently, a special variable indicates to the simulation
;; evaluator to use the current value instead of trying to evaluate.
;; This test is made in sim-eval-get-value-of-variable.  A similar test
;; should be made (of appropriate special variables) to check if
;; get-value-at-history-time-given-variable should be called at this
;; point.

;; For now this function is called here directly.



(defun get-value-at-history-time
       (display-expression history-time
	display-evaluation-should-use-simulated-values?)
  (get-value-at-history-time-given-variable
    (get-instance-with-name-if-any 'variable-or-parameter display-expression)  ; for now
    history-time
    display-evaluation-should-use-simulated-values?))



;; Get-value-at-history-time-given-variable does similar things as some of the
;; other history functions (see above).  The code should be consolidated at some
;; point.

(defun get-value-at-history-time-given-variable
       (variable-or-parameter history-time
	display-evaluation-should-use-simulated-values?)
  (let* ((simulation-subtable?
	   (when (variable-p variable-or-parameter)
	     (simulation-details variable-or-parameter)))
	 (history-buffer-of-stored-values
	   (if (get-history-from-simulation-subtable?
		 variable-or-parameter
		 display-evaluation-should-use-simulated-values?)
	       (if simulation-subtable?
		   (simulation-stored-histories?
		     simulation-subtable?))
	       (variable-or-parameter-stored-histories? variable-or-parameter))))
;	 (ring-buffer-for-history-time
;	   (get-ring-buffer-in-cascade-for-history-time
;	     history-buffer-of-stored-values history-time)))
    (when history-buffer-of-stored-values
      (get-history-element-using-best-search
	history-buffer-of-stored-values
	;; ring-buffer-for-history-time
	history-time
	t))))



(defun get-ring-buffer-in-cascade-for-history-time
       (cascaded-ring-buffer history-time)
  (declare (ignore history-time))
  (car (cascaded-ring-buffers cascaded-ring-buffer)))





(defun store-new-plot-data-4
       (display-expression graph-grid start-time plot stop-time
	display-evaluation-should-use-simulated-values?
	low-and-high-values-specified-for-vertical-axis?-arg
	scale-y-data-points?-arg data-buffer-for-plot
	plot-number low-value-for-horizontal-axis-arg)
  (let* ((low-and-high-values-specified-for-vertical-axis?
	   low-and-high-values-specified-for-vertical-axis?-arg)
	 (scale-y-data-points? scale-y-data-points?-arg)
	 (low-value-for-horizontal-axis low-value-for-horizontal-axis-arg)
	 (current-plot plot)
	 (current-graph-grid graph-grid)
	 (current-data-buffer-for-plot data-buffer-for-plot)
	 (current-plot-number plot-number)
	 (minimum-and-maximum-y-value-set? nil)
	 (fixnum-minimum-y-value nil)
	 (fixnum-maximum-y-value nil)
	 (most-recent-extremum-maximum-p nil)
	 (variable (get-variable-given-graph-expression
		     display-expression
		     display-evaluation-should-use-simulated-values?))
	 (previous-cascaded-ring-buffer-accessed nil) ; special - see def in histories
	 (previous-index-for-ring-buffer nil) ; ditto
	 (grid-width (grid-width-for-graph graph-grid))
	 (grid-height (grid-height-for-graph graph-grid))
	 (plot-min-and-max? nil)
	 (history-time-to-evaluate-display-expression-with start-time)
	 (erase-dateline (compute-erase-dateline graph-grid))
	 (plot-marker? (plot-marker-given-plot plot))
	 (interval-between-plot-markers (interval-between-plot-markers graph-grid))
	 (x-value-on-graph nil)
	 (most-recent-extremum-maximum-for-pixel-p nil)
	 (simulation-subtable?
	   (when (variable-p variable)
	     (simulation-details variable)))
	 (use-simulation-history?
	   (get-history-from-simulation-subtable?
		 variable
		 display-evaluation-should-use-simulated-values?))
	 (history-buffer-of-stored-values
	   (if use-simulation-history?
	       (if simulation-subtable?
		   (simulation-stored-histories?
		     simulation-subtable?))
	       (variable-or-parameter-stored-histories? variable)))
	 (current-cascaded-ring-buffer history-buffer-of-stored-values) ; special see GRAPHS1
	 (ring-buffer-for-history-time
	   (get-ring-buffer-in-cascade-for-history-time
	     history-buffer-of-stored-values start-time))
	 (index-for-start-time
	   (get-history-index-by-binary-search
	      history-buffer-of-stored-values start-time t))
	 (index-for-stop-time 
	   (get-history-index-by-binary-search
	     history-buffer-of-stored-values stop-time t))
	 (start-index-time
	   (get-history-fixnum-time 
	     history-buffer-of-stored-values index-for-start-time
	     use-simulation-history?))
	 (stop-index-time
	   (get-history-fixnum-time 
	     history-buffer-of-stored-values index-for-stop-time
	     use-simulation-history?))
	 (current-index nil)
	 (number-of-datapoints 
	   (ring-buffer-index-difference 
	     ring-buffer-for-history-time
	     index-for-stop-time
	     index-for-start-time))
	 (number-of-pixels-in-time-range 
	   (with-temporary-gensym-float-creation store-new-plot-data-4
	     ;; The following product can generate a bignum if left as
	     ;; integers so we convert its arguments to gensym-floats
	     ;; instead. - jpg 6/15/00
	     (+f 1 (round (*e (coerce-to-gensym-float 
				(grid-and-erase-zone-width graph-grid))
			      (coerce-to-gensym-float 
				(-f stop-index-time start-index-time)))
			  (maxf (-f (high-value-for-horizontal-axis graph-grid)
				    (low-value-for-horizontal-axis graph-grid))
				1)))))
	 (many-more-data-points-than-pixels? 
	   (>f number-of-datapoints
	       (*f 2 number-of-pixels-in-time-range)))
	 (x-data-min-set? nil))
    (loop with finished-storing-in-plot-data-1? = nil
	  initially
	    (when (and (<f start-index-time start-time)
		       (/=f index-for-start-time
			    (newest-active-element-index ring-buffer-for-history-time))
		       (/=f index-for-stop-time index-for-start-time))
	      (setq index-for-start-time
		    (increment-active-element-index
		      index-for-start-time ring-buffer-for-history-time)))
	    (when (and (>f stop-index-time stop-time)
		       (/=f index-for-stop-time
			    (oldest-active-element-index ring-buffer-for-history-time))
		       (/=f index-for-stop-time index-for-start-time))
	      (setq index-for-stop-time
		    (decrement-active-element-index
		      index-for-stop-time ring-buffer-for-history-time)))
	    ;; These checks are necessary because binary search may go
	    ;; over boundary.
	    (setq current-index index-for-start-time)
	    
	    (mutate-managed-float-value
	      last-history-time-for-data-point-on-pixel
	      (coerce-fixnum-to-gensym-float start-time))
	    (when many-more-data-points-than-pixels?
	      (mutate-managed-float-value
		history-time-per-pixel
		(/e (coerce-fixnum-to-gensym-float 
		      (horizontal-axis-and-erase-zone-range graph-grid))
		    (coerce-fixnum-to-gensym-float
		      (grid-and-erase-zone-width graph-grid)))))
	    (when scale-y-data-points?
	      (setq plot-min-and-max?
		    (plot-min-and-max-given-plot plot))
	      (when plot-min-and-max?
		(mutate-plot-min-given-plot-min-and-max plot-min-and-max?)
		(mutate-plot-max-given-plot-min-and-max plot-min-and-max?)))
	  ;; end 'initially'

	    ;; It is the responsiblity of store-new-plot-data-1 to
	    ;; set finished-storing-in-plot-data-1? it is done sweeping
	    ;; current-index from index-for-start-time to index-for-stop-time.
	    ;; Remember that these index are into a ring buffer.
	    ;; Remember that in many-more-data-points-than-pixels? it is
	    ;; possible to consume multiple history data points each time
	    ;; thru the loop. Remember also that in many-more-data-points-than-pixels?
	    ;; mode last-history-time-for-data-point-on-pixel and history-time-per-pixel
	    ;; are loop variables too. - ben 12/09/92

	  do (store-new-plot-data-1 use-simulation-history?)
      	  until finished-storing-in-plot-data-1?

	  finally
	    (store-new-plot-data-3)
	    (store-managed-number-or-value 
	      (x-data-maximum plot) 
	      (floore-first (get-previous-history-time)))
	  )))


;; Many-more-data-points-than-pixels?  is non-nil if the number of
;; datapoints exceeds twice the number of horizontal pixels in the
;; time range.  The factor of two is arbitrarily chosen, just to make sure
;; that the many-more-data-points special case code only is used when it
;; is really needed.





;;;; Frame Notes for Graphs

(defparameter list-of-graph-frame-note-types
	      '(plot-range-specs-without-vertical-axis-spec
		desired-range-too-small
		too-many-grid-lines
		horizontal-range-zero))

;; Improve to automatically generate this list (as is done with
;; installation frame notes.



(defun delete-all-frame-notes-for-graph (graph)
  (loop for frame-note-type in list-of-graph-frame-note-types
	do
    (delete-frame-note-if-any frame-note-type graph)))



(defun post-reformat-warning-note-for-graph (graph)
  (case problems-reformatting-graph?
    (zero-interval-between-horizontal-grid-lines
     (notify-user
       "There were problems reformatting ~a;  the interval between horizontal grid lines is specified to be 0."
       (get-or-make-up-designation-for-block graph)))
    (data-point-number-undefined
     (notify-user
       "There were problems reformatting ~a;  some of the data points are infinity or are undefined numbers."
       (get-or-make-up-designation-for-block graph)))
    (t
     (notify-user 
       "There were problems reformatting ~a; see its notes for details."
       (get-or-make-up-designation-for-block graph)))))



(def-frame-note-writer plot-range-specs-without-vertical-axis-spec
		       (dummy-for-particulars)
  dummy-for-particulars
  (twrite-string
    "if range is specified for a plot, the desired range for vertical axis slot must contain a minimum and maximum value"))

(defun bad-plot-range-specs? (graph)
  (memq 'plot-range-specs-without-vertical-axis-spec
	(frame-status-and-notes graph)))

(def-frame-note-writer desired-range-too-small
		       (dummy-for-particulars)
  dummy-for-particulars
  (twrite-string
    "the range specified is too small so the smallest possible will be used"))

(defun bad-desired-range-too-small? (graph)
  (memq 'desired-range-too-small
	(frame-status-and-notes graph)))

(def-frame-note-writer too-many-grid-lines (dummy-for-particulars)
  dummy-for-particulars
  (twrite-string
    "the number of grid lines requested is too large, computing grid lines automatically"))
  
(def-frame-note-writer horizontal-range-zero
		       (dummy-for-particulars)
  dummy-for-particulars
  (twrite-string
    "the range specified for the horizontal axis is zero"))

(defun bad-horizontal-range-zero? (graph)
  (memq 'horizontal-range-zero
	(frame-status-and-notes graph)))





#+development
(defun print-contents-of-plot-data-buffer (plot-data-buffer)
  (when (not (ring-buffer-empty? plot-data-buffer))
    (loop as index = (oldest-active-element-index plot-data-buffer)
	     then (increment-active-element-index index plot-data-buffer)
	  do (multiple-value-bind (x y)
		 (get-plot-data-ring-buffer-element plot-data-buffer index)
	       (format t "~%for idx=~s: ~s, ~s" index x y))
	  until (=f index (newest-active-element-index plot-data-buffer)))))

;; Make this automatically defined by define-ring-buffer!!




;;;; NUPEC Graphs

;;; This section contains enhancements to graphs required by NUPEC as specified
;;; in the NUPEC contract.  This is custom code for NUPEC only and is not part
;;; of the general G2 product.


;;; To get the NUPEC code compiled, need to do 
;;;   (pushnew ':NUPEC *features*)

;;; We have now integrated NUPEC code into G2.  The NUPEC features are only
;;; available to NUPEC users after authorization.  The NUPEC code is part of
;;; regular G2 compilation.  Several things are added during NUPEC
;;; authorization, such as grammar rules.  cpm, 3/15/91




;#+NUPEC
;(add-grammar-rules
;  '((plot-marker-phrase ('using class 'NUPEC 'plot 'marker) (3 . 2))
;    ))


;;; The internal format for the NUPEC plot marker is 
;;;   ('NUPEC . class) 
;;; Plot-marker-given-plot will return this if the NUPEC plot marker option
;;; is used (it will still return a symbol such as 'triangle, 'square, etc.
;;; if an ordinary plot marker is specified).







;;; Paint-nupec-plot-marker is called by paint-plot-marker if plot-marker
;;; is not one of the standard ones (triangle, square, etc.)

(defun paint-nupec-plot-marker
       (plot-marker-class x y graph-line-color-value x-scale y-scale)
  (let ((icon-description?
	  (get-icon-description-given-class plot-marker-class)))
    (cond 
      (icon-description?
       (let* ((icon-rendering
		(let ((current-image-x-scale x-scale) ; implicit parameters
		      (current-image-y-scale y-scale))
		  (get-or-make-icon-rendering icon-description? nil)))
	      (line-drawing-description
		(line-drawing-description-for-rendering?
		  icon-rendering))
;	      (polychrome-header?
;		     (let ((first-element (car line-drawing-description)))
;		       (if (and (consp first-element)
;				(eq (car first-element) 'polychrome))
;			   first-element)))
	      ;; all icons are polychrome, so change test  -dkuznick, 6/30/98
	      (monochrome?
		(single-color-line-drawing-description-p
		  line-drawing-description)))
	 (cond
	   (;;(not polychrome-header?) -dkuznick, 6/30/98
	    monochrome?
	    (paint-marker-onto-graph-raster
	      icon-rendering 
	      (delta-x-in-window x x-scale)
	      (delta-y-in-window y y-scale)
	      graph-line-color-value))
	   (t
	    ;; post warning message - monochrome icons only
	    ;; THIS WOULD REENTER ON-WINDOW -- NOT ALLOWED!! (MHD 10/25/90)
;	    (warning-message 1
;	      "The ~a plot-marker can not be drawn because it is a polychrome ~
;               icon.  Only monochrome plot-markers can be drawn on graphs."
;	      plot-marker-class)
	    ))))
      (t
       ;; post warning message
       ;; THIS WOULD REENTER ON-WINDOW -- NOT ALLOWED!! (MHD 10/25/90)
;       (warning-message 1
;	 "The ~a plot-marker can not be drawn a graph because it is ~
;	  missing an icon-description." 
;	 plot-marker-class)
       ))
    ))

;; See also draw method for entity, draw-icon, and make-rendering-structure.

;; If there is no icon description for the class, a warning is posted.

;; If the icon is polychrome, a warning is posted.  It would be possible
;; to have polychrome icons as well although this will require some more
;; work.

;; Note that if a class with the same name as one of the standard plot 
;; markers (triangle, square, etc.) is defined and used as a NUPEC plot
;; marker, it will not currently be recognized as such.  Rather, the plot
;; will be drawn in the usual non-NUPEC way with the standard plot marker.
;; This could be changed by having the call to add-graph-marker in
;; draw-data-point pass the full plot marker cons rather than just the
;; class.



;;; See also the icp message function paint-marker-onto-graph-raster in windows3.





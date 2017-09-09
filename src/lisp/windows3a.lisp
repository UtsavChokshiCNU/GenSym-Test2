;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module WINDOWS3A -- Operations on the Gensym Window System

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Lowell B.  Hawkinson, Brian Matthews, Mark David, Andreas Hofmann,
;;; and Ong, Peng Tsin






;;;; Forward References in WINDOWS3




(declare-forward-references
  (remove-graph-rendering-from-graph-grid  function graphs1))






;;;; Graph Renderings



(defconser graph)



;;; A `graph-rendering' is a structure similar to an icon-rendering.  It is
;;; also an icp-object-type.  Thus, when using telewindows, corresponding
;;; graph renderings will be kept on the G2 and on the remote side.  On
;;; the remote side, the graph-rendering-structure? slot of the 
;;; graph-rendering will contain a ring-raster-for-graph structure.
;;; This structure has a slot ring-raster which contains a raster for
;;; the graph.  (See also documentation for icon renderings).

(def-structure (graph-rendering
		 (:constructor
		   make-graph-rendering-internal
		   (line-drawing-description-for-graph-rendering?
		     format-of-graph-rendering-structure
		     x-scale-of-graph-rendering y-scale-of-graph-rendering
		     grid-border-width
		     width-of-rendered-graph
		     height-of-rendered-graph
		     width-of-graph-rendering-structure
		     height-of-graph-rendering-structure
		     corresponding-graph-grid-or-chart?
		     window-for-graph-rendering
		     graph-rendering-parent?))
		 (:include lru-element))
  
  x-scale-of-graph-rendering
  y-scale-of-graph-rendering
  
  (corresponding-icp-object-map-for-graph-rendering nil)
  
  format-of-graph-rendering-structure		; monochrome-raster, polychrome-raster, etc.

  (graph-rendering-structure? nil)	       	; nil => none yet (if ever)

  line-drawing-description-for-graph-rendering?	; nil => corresponding object in ICP server

  (grid-background-color-value nil)
  (color-values-for-rasters?			; a list iff format-or-graph-rendering-
    nil :reclaimer reclaim-graph-list)		;   structure is MONOCHROME-RASTER-LIST;
							    ;   else nil
  
  grid-border-width

  width-of-graph-rendering-structure
  height-of-graph-rendering-structure

  width-of-rendered-graph			; prior to scaling
  height-of-rendered-graph
  
  corresponding-graph-grid-or-chart?		; always nil for Telewindows

  window-for-graph-rendering		; kept in TW; for allocating rasters per-window
  (image-plane-for-graph-rendering? nil) ; never nil on the G2 side; always nil for TW

  (paint-foreground-only-p nil)
  (graph-rendering-parent? nil))    ; always nil for Telewindows

;; Make-graph-rendering is defined by define-decacheable-structure for 
;; graph-rendering.






;;; A graph-rendering is a decacheable structure.

(define-decacheable-structure graph-rendering 
  (make-graph-rendering-internal
    line-drawing-description-for-graph-rendering?
    format-of-graph-rendering-structure
    x-scale-of-graph-rendering y-scale-of-graph-rendering
    grid-border-width
    width-of-rendered-graph
    height-of-rendered-graph
    width-of-graph-rendering-structure
    height-of-graph-rendering-structure
    corresponding-graph-grid-or-chart?
    window-for-graph-rendering
    frame-serial-number-of-parent?)
  compute-cost-of-decaching-graph-rendering
  #.list-of-regular-raster-sizes
  compute-size-of-graph-rendering
  nil
  window-for-graph-rendering
  (delete-graph-rendering-and-reclaim-icp-index graph-rendering)
  )

(defun compute-cost-of-decaching-graph-rendering (graph-rendering)
  (if (null (corresponding-graph-grid-or-chart? graph-rendering))
      0
      2000
      ))
                                                                                
;; A constant cost actually works well since graphs don't vary much in
;; complexity.  Actually, could base cost on some function of both
;; number of plots and number of colors.  Also, no need to base cost on
;; size since the graph-rendering pool is subdivided by size.

;; The corresponding-graph-grid-or-chart?  slot will be nil here if the graph has been
;; deleted (see clean-up method for graph-grid).  In this case, the cost of
;; decaching is 0.



(defun compute-size-of-graph-rendering (graph-rendering)
  (compute-size-of-graph-rendering-1
    (width-of-graph-rendering-structure graph-rendering)
    (height-of-graph-rendering-structure graph-rendering)))

(defun compute-size-of-graph-rendering-1 (width height)
  (maxr width height))

;; This is a very crude size function.  It should take into account the
;; number of colors (number of bit planes) in the graph rendering.




(defun-void reclaim-graph-rendering-and-raster-1 (graph-rendering)
  (reclaim-graph-rendering-and-raster graph-rendering))

(def-icp-object-type graph-rendering
		     (standard-icp-object-index-space
		      (corresponding-icp-object-map-for-graph-rendering
			graph-rendering)
		      reclaim-graph-rendering-and-raster-1)
  (send-icp-begin-making-graph-rendering
    corresponding-icp-object-index
    (format-of-graph-rendering-structure graph-rendering)
    (x-scale-of-graph-rendering graph-rendering)
    (y-scale-of-graph-rendering graph-rendering)
    (grid-border-width graph-rendering)
    (width-of-graph-rendering-structure graph-rendering)
    (height-of-graph-rendering-structure graph-rendering)
    (width-of-rendered-graph graph-rendering)
    (height-of-rendered-graph graph-rendering)))


(def-icp-message-type begin-making-graph-rendering
		      (corresponding-icp-object-index
		       (symbol format-of-graph-rendering-structure)
		       (unsigned-integer x-scale-of-graph-rendering)
		       (unsigned-integer y-scale-of-graph-rendering)
		       (unsigned-integer grid-border-width)
		       (integer width-of-graph-rendering-structure)
		       (integer height-of-graph-rendering-structure)
		       (integer width-of-rendered-graph)
		       (integer height-of-rendered-graph))
  (let ((graph-rendering
	  (store-corresponding-icp-object
	    corresponding-icp-object-index
	    (make-graph-rendering
	      nil format-of-graph-rendering-structure
	      x-scale-of-graph-rendering y-scale-of-graph-rendering
	      grid-border-width
	      width-of-rendered-graph height-of-rendered-graph
	      width-of-graph-rendering-structure
	      height-of-graph-rendering-structure
	      nil current-window nil))))
    (setf (graph-rendering-structure? graph-rendering)
	  (make-graph-rendering-structure
	    width-of-graph-rendering-structure))
    ))

;; Note that unlike the graph-rendering on the G2 side, the graph-rendering
;; on the telewindows side has nil as the value of its 
;; line-drawing-description-for-graph-rendering? slot.  Thus, it need not
;; be initialized here as it is in make-new-graph-rendering.

;; Note that (unlike the icons case) no rasters are allocated here.
;; This is taken care of as needed by the update functions
;; (see update-graph-rendering).




(defun delete-graph-rendering-and-reclaim-icp-index (graph-rendering)
  (reclaim-icp-object-map-for-graph-rendering graph-rendering)
  (reclaim-graph-rendering-and-raster graph-rendering))

;; See notes for delete-icon-rendering-and-reclaim-icp-index.





;;;; Graph Draw Functions for Telewindows Server



;; AGH's notes:  (VERY OLD!)
;; 
;; Initialize this based on the platform (use features reader macros)!
;; Actually, this should probably be user settable in some way, perhaps via
;; a format frame.  Polychrome rasters are definitely faster than monochrome
;; rasters but they are less memory efficient when there are fewer than 8
;; different colors.  Typically, the graph update will not be scheduled for
;; every second but rather every 5 seconds, or maybe even just once every 
;; minute.  Also, unless scrolling continuously and not leaving any extra
;; space, most of the bitblts will be only for a small section of the raster
;; rather than the entire raster.  Finally, a typical graph will only have
;; 1 to 3 plots.  Thus, in most cases, monochrome rasters would be a better
;; choice.


(def-substitution-macro graph-rendering-uses-polychrome-rasters? 
			(graph-rendering)
  (eq (format-of-graph-rendering-structure graph-rendering) 'polychrome-raster))


(def-substitution-macro graph-rendering-uses-monochrome-raster-lists?
			(graph-rendering)
  (eq (format-of-graph-rendering-structure graph-rendering) 'monochrome-raster-list))

;; See also call to make-decacheable-graph-rendering in make-new-graph-rendering.



;;; Ring-raster-for-graph contains one or more rasters which are painted and
;;; then bitblt to the screen to draw the graph.  The raster-dateline slot
;;; indicates the position of the "dateline" on the rasters so that they can 
;;; be used as "ring rasters".  The raster-or-rasters slot will contain
;;; different things depending on the value of use-polychrome-rasters-for-graphs?.
;;; If this variable is non-nil, it will contain a polychrome raster.  Otherwise,
;;; it will contain a list of monochrome rasters, one for each color to be used
;;; for the graph.  The rasters are ordered such that they correspond to the
;;; list of color-values in the color-values-for-rasters? slot of the
;;; graph-rendering, as well as to the value of color-values-for-raster-list
;;; iff this is for a monochrome-raster-list graph rendering.

(def-structure ring-raster-for-graph
  (raster-or-rasters nil :reclaimer reclaim-graph-tree)
  (raster-dateline nil)
  (erase-raster-dateline nil)
  (color-values-for-raster-list nil :reclaimer reclaim-graph-list))





(defun compute-true-size-of-graph-rendering (graph-rendering)
  (let* ((graph-rendering-structure?
	   (graph-rendering-structure? graph-rendering))
	 (raster-or-rasters?
	   (when graph-rendering-structure?
	     (raster-or-rasters graph-rendering-structure?)))
	 (size-of-one-raster
	   (compute-true-size-of-graph-rendering-1
	     (width-of-graph-rendering-structure graph-rendering)
	     (height-of-graph-rendering-structure graph-rendering)))
	 (raster-count
	   (cond
	     ((consp raster-or-rasters?)
	      (length raster-or-rasters?))
	     (raster-or-rasters? 1)
	     (t 0))))
    (*f raster-count size-of-one-raster)))

(defun compute-true-size-of-graph-rendering-1 (width height)
  (maxr 1 (roundr (*r width height) 32)))

;; Make these be compute-size-of-graph-rendering, compute-size-of-graph-rendering-1! 



(defmacro adjusted-allocation-width-of-graph-rendering-structure (graph-rendering)
  `(+r (width-of-graph-rendering-structure ,graph-rendering) 1))

(defmacro adjusted-allocation-height-of-graph-rendering-structure (graph-rendering)
  `(+r (height-of-graph-rendering-structure ,graph-rendering) 1))

;; The raster is made one pixel larger than necessary to avoid bombouts on 
;; some platforms (Symbolics) when a line is drawn to the edge.

;; Changed to macros from functions.  (MHD 2/17/93)


;; The raster is made one pixel larger than necessary to avoid bombouts on 
;; some platforms (Symbolics) when a line is drawn to the edge.




;;; `Reclaim-monochrome-raster-for-ring-raster' ... [... currently a noop.]

(defmacro reclaim-monochrome-raster-for-ring-raster (raster)
  raster)					; just evaluate argument (ignore)

;; Implement! (AGH)
;; -- What are the consequences of not doing this.  Not "terrible", apparently.
;; Notice the loop that executes this noop, below. (MHD 2/17/93)



;;; `Reclaim-graph-raster-list' ... reclaims the rasters and conses that make
;;; up graph-raster-list, assuming it is made up of monochrome rasters and
;;; graph conses, respectively.

(def-substitution-macro reclaim-graph-raster-list (graph-raster-list)
  ;; noop for now-- see above -- so skip looping -- implement later! (MHD 2/17/93)
; (loop for raster in (cdr graph-raster-list)
;  	do (reclaim-monochrome-raster-for-ring-raster raster))
  (reclaim-graph-list graph-raster-list))



(defun reclaim-graph-rendering-and-raster (graph-rendering)
  (let ((corresponding-graph-grid-or-chart?   ; will be nil for Telewindows process
	  (corresponding-graph-grid-or-chart? graph-rendering))
	(ring-raster?
	  (graph-rendering-structure? graph-rendering)))
    (when corresponding-graph-grid-or-chart?
      (remove-graph-rendering-from-graph-grid
	graph-rendering corresponding-graph-grid-or-chart?))
    (when ring-raster?
      ;; reclaim ring raster structure and rasters
      (let ((raster-or-rasters
	      (raster-or-rasters ring-raster?))
	    (window-for-graph-rendering 
	      (window-for-graph-rendering graph-rendering)))
	(when raster-or-rasters
	  (loop with minimum-depth
		  = (if (graph-rendering-uses-polychrome-rasters? graph-rendering)
			8			; min depth -- fix later! (MHD 2/17/93)
			1)
		with adjusted-allocation-width
		  = (adjusted-allocation-width-of-graph-rendering-structure
		      graph-rendering)
		with adjusted-allocation-height
		  = (adjusted-allocation-height-of-graph-rendering-structure
		      graph-rendering)
		for raster-in-list?
		    in (if (atom raster-or-rasters) '(nil) raster-or-rasters)
		as raster = (or raster-in-list? raster-or-rasters)
		do (reclaim-stored-raster
		     raster window-for-graph-rendering
		     adjusted-allocation-width adjusted-allocation-height
		     minimum-depth nil))
	  ;; Note that if the raster is polychrome, raster-or-rasters
	  ;; will not be a cons.  Thus, this information is somewhat
	  ;; redundant with a bits-per-pixel slot in the 
	  ;; graph-rendering-structure.  The slot is still needed
	  ;; however for number of bits per pixel. (AGH)
	  ))
      (reclaim-ring-raster-for-graph ring-raster?)))
  (reclaim-graph-rendering graph-rendering))




(defvar current-graph-rendering-structure)
(defvar current-graph-rendering)

;; Note that current-graph-rendering is defined here for use in the Telewindows
;; side of the wire, but then also used in GRAPHS1 with a really different binding
;; discipline.  Here it is in fact only used free in the case of the
;; paint-clipped-marker-onto-graph-raster function.  Things should probably
;; be rearranged so that graph-rendering is used locally in this module, and
;; current-graph-rendering is used and defined as a special variable only in
;; GRAPHS1!! (MHD 2/17/93)



(def-icp-message-type prepare-for-painting-graph (graph-rendering)
  (let* ((current-graph-rendering graph-rendering)	; see note above! (MHD 2/17/93)
	 (current-graph-rendering-structure
	   (graph-rendering-structure? graph-rendering))
	 (adjusted-allocation-width
	   (adjusted-allocation-width-of-graph-rendering-structure
	     graph-rendering))
	 (adjusted-allocation-height
	   (adjusted-allocation-height-of-graph-rendering-structure
	     graph-rendering))
	 (raster-or-rasters
	   (raster-or-rasters current-graph-rendering-structure)))
    (cond
      ((graph-rendering-uses-polychrome-rasters? graph-rendering)
       (on-scratchpad-raster-given-stored-raster
	 (current-window raster-or-rasters
			 adjusted-allocation-width adjusted-allocation-height
			 8)			; min depth -- fix later!! (MHD 2/3/93)
	 (handle-icp-messages t)))
      ((graph-rendering-uses-monochrome-raster-lists? graph-rendering)
       ;; new way added.  (MHD 1/28/93)
       (on-scratchpad-raster-list-given-stored-raster-list
	 (current-window raster-or-rasters
			 (color-values-for-raster-list current-graph-rendering-structure)
			 adjusted-allocation-width adjusted-allocation-height)
	 (handle-icp-messages t)))
      (t
       (loop for stored-raster in raster-or-rasters
	     do (on-scratchpad-raster-given-stored-raster
		  (current-window stored-raster
				  adjusted-allocation-width adjusted-allocation-height
				  1)		; 1 (monochrome) by definition
		  (handle-icp-messages t)))))))

;; This is similar to begin-making-icon-rendering in that it binds a
;; scratchpad raster and waits to receive icp messages for painting the
;; raster.  The difference is that begin-making-icon-rendering is called
;; only once for the icon rendering whereas this is called whenever the
;; graph is updated.




;;; Update-ring-raster-for-graph-given-color-values does different things
;;; depending on whether the graph rendering uses monochrome or polychrome
;;; rasters.  This is tested by the macro
;;; graph-rendering-uses-polychrome-rasters?.  If the value is nil, it allocates
;;; monochrome rasters as needed according to color-values.  If
;;; graph-rendering-uses-polychrome-rasters?  is non-nil, then a polychrome raster
;;; with depth specified by use-polychrome-rasters-for-graphs?  is allocated if
;;; none exists.  Thus, update-ring-raster-for-graph-given-color-values does
;;; nothing for the polychrome case once the raster is allocated.  Also, the
;;; color-values argument is not used for the polychrome case.

(def-icp-message-functions update-ring-raster-for-graph-given-color-values
			   (graph-rendering 
			    (unsigned-integer number-of-rasters-needed))
  (case type-of-current-window
    (t
     (let* ((ring-raster (graph-rendering-structure? graph-rendering))
	    (raster-or-rasters? (raster-or-rasters ring-raster)))
       (cond 
	 ((not (graph-rendering-uses-polychrome-rasters? graph-rendering))
	  ;; Since the rasters in raster-or-rasters? are not tied to any color and
	  ;; since they will all be completely repainted after the colors are
	  ;; updated, the update simply involves making sure that the number of
	  ;; colors and the number of rasters is the same.

	  (let* ((raster-surplus
		   (-f (length raster-or-rasters?) number-of-rasters-needed)))
	    (cond
	      ((<f raster-surplus 0)
	       (setf (raster-or-rasters ring-raster)
		     (nconc
		       raster-or-rasters?
		       (loop with width
			       = (adjusted-allocation-width-of-graph-rendering-structure
				   graph-rendering)
			     with height
			       = (adjusted-allocation-height-of-graph-rendering-structure
				   graph-rendering)
			     for x from -1 downto raster-surplus
			     collect
			       ;; Look into allocating tiled raster! (MHD 2/17/93)
			       (allocate-stored-raster-1 current-window width height 1 nil)
			      using graph-cons))))
	      ((>f raster-surplus 0)
	       (loop for x from 1 to number-of-rasters-needed
		     for rest-of-rasters on raster-or-rasters?	; skip end test?!
		     finally
		       (reclaim-graph-raster-list (cdr rest-of-rasters))
		       (setf (cdr rest-of-rasters) nil))))))
	 (t 
	  (when (null raster-or-rasters?)	; check if nil or a raster
	    (setf (raster-or-rasters ring-raster)
		  (allocate-stored-raster-1
		    current-window
		    (adjusted-allocation-width-of-graph-rendering-structure
		      graph-rendering)  
		    (adjusted-allocation-height-of-graph-rendering-structure
		      graph-rendering)
		    8				; min depth!  fix later!
		    nil)))))))))



;;; The ICP message `update-ring-raster-for-graph-given-color-values-2' is a new
;;; version of update-ring-raster-for-graph-given-color-values, but it is only
;;; available for the newer icp-window-protocol-supports-monochrome-raster-lists
;;; version of the Telewindows Protocol.  (Version 3.1 of G2).  The old version
;;; may continue to be called indefinitely into the future, but may only be used
;;; for graph renderings not of format monochrome-raster-list.  Since the old
;;; version does not require the transmission of a color list, it is a bit more
;;; efficient in terms of transmission time.

(def-icp-message-functions update-ring-raster-for-graph-given-color-values-2
			   (graph-rendering
			     (list-of-unsigned-integers color-values-for-rasters?))
  (case type-of-current-window				
    (t
     (update-ring-raster-for-graph-given-color-values
       graph-rendering (length color-values-for-rasters?))
     (when (eq (format-of-graph-rendering-structure graph-rendering)
	       'monochrome-raster-list)
       (let ((ring-raster-for-graph (graph-rendering-structure? graph-rendering)))
	 (reclaim-graph-list (color-values-for-raster-list ring-raster-for-graph))
	 (setf (color-values-for-raster-list ring-raster-for-graph)
	       (copy-list-using-graph-conses color-values-for-rasters?)))))))


(def-icp-message-functions set-graph-rendering-foreground-only-mode
			   (graph-rendering
			     (boolean foreground-only-mode))
  (case type-of-current-window				
    (t
     (setf (paint-foreground-only-p graph-rendering)
	   foreground-only-mode))))

;; Added today.  (MHD 2/16/93)

;; Consider specing that nil may be passed in the non-monochrome-raster-list
;; case.  (MHD 2/16/93)


#+development
(def-system-variable debug-mode-for-ring-raster? WINDOWS3 nil)
;; If debug-mode-for-ring-raster? is non-nil, swapping of the two raster regions
;; will not take place and the raster will simply be bitblted to the screen
;; without modification and without any clipping to limit bitblt to only new
;; data.  Also, the dateline will be shown by a single vertical line.  This mode
;; is useful for getting an unobscured view of the ring raster.

#+development
(def-system-variable debug-mode-for-clipping? WINDOWS3 nil)
;; If debug-mode-for-clipping? is non-nil, then the region bitblt to screen will
;; be bitblt as a solid rectangle.  This is useful for making sure that the
;; bitblting is working properly.

#+development
(def-system-variable debug-graph-line-draw? WINDOWS3 nil)
;; If debug-graph-line-draw? is non-nil, the raster coordinates for lines
;; will be displayed in the upper-left corner as they are painted into the
;; raster.  Clipping rectangle coordinates will be displayed as well.



;#+development
;(def-system-variable debug-mode-for-color-rasters? WINDOWS3 nil)
;; If debug-mode-for-color-rasters? should be nil or an integer.  If it is an
;; integer n, the nth raster will be bitblt to the screen.  This is useful for
;; checking the contents of different color rasters.


(def-system-variable clipping-rectangles-for-new-data? WINDOWS3 nil)



(def-substitution-macro set-graph-colors
			(color-value background-color-value alu-function)
  (progn
    background-color-value ;; (declare (ignore background-color-value))
    alu-function           ;; (declare (ignore alu-function))
    color-value))

;; This is derived from set-color-value-for-painting.



(def-substitution-macro add-from-graph-ring-raster-to-current-window-2
			(clipped-left-edge clipped-top-edge
			 clipped-right-edge clipped-bottom-edge
			 color-value background-color-value
			 stored-raster alu-function
			 left-edge-in-stored-raster top-edge-in-stored-raster)
  alu-function background-color-value  ; not always used
  (case type-of-current-window
    (x11-window
     (c-x11-copy-pixmap 
       stored-raster current-native-window?
       left-edge-in-stored-raster top-edge-in-stored-raster
       clipped-left-edge clipped-top-edge
       (-r clipped-right-edge clipped-left-edge)
       (-r clipped-bottom-edge clipped-top-edge)
       color-value
       background-color-value
       alu-function
       ))))

;; This is similar to add-from-stored-raster-to-current-window
;; except that the alu bitblt option is set (paint) rather than exclusive-or.
;; Finish for other architectures for 2.0!  Possibly consolidate with 
;; add-from-stored-raster-to-current-window (talk to Mark).


(def-substitution-macro add-from-polychrome-raster-to-current-window
			(clipped-left-edge clipped-top-edge
 		         clipped-right-edge clipped-bottom-edge
			 raster 
			 left-edge-in-stored-raster 
			 top-edge-in-stored-raster)
  (case type-of-current-window
    (x11-window
     (c-x11-copy-polychrome-pixmap 
       raster current-native-window?
       left-edge-in-stored-raster top-edge-in-stored-raster
       clipped-left-edge clipped-top-edge
       (-r clipped-right-edge clipped-left-edge)
       (-r clipped-bottom-edge clipped-top-edge)
       x11-copy))))

;; X11-copy-polychrome-pixmap uses XCopyArea rather than XCopyPlane.
;; Therefore, the raster must be of the same depth as the screen.
;; On-polychrome-scratchpad-raster always allocates a raster with
;; the same depth as the screen.


;;; If color-value? is nil, add-from-graph-ring-raster-to-current-window-1 will
;;; loop for all rasters and bitblt them all to the screen (by calling
;;; add-from-graph-ring-raster-to-current-window-2).  However, if color-value?
;;; is non-nil, it will only bitlt the raster for that color.

(def-substitution-macro add-from-graph-ring-raster-to-current-window-1
			(clipped-left-edge clipped-top-edge
			 clipped-right-edge clipped-bottom-edge
			 color-value grid-background-color-value first-raster?
			 graph-rendering raster
			 left-edge-in-stored-raster top-edge-in-stored-raster)
  (cond 
    ((not (graph-rendering-uses-polychrome-rasters? graph-rendering))
     (let* ((2nd-alu-function
	      (if (paint-foreground-only-p graph-rendering)
		  x11-stippled
		  x11-xor))
	    (alu-function
	      (if first-raster? 
		  x11-copy
		  2nd-alu-function
					; was (current-transfer-mode-for-x11-windows) 
		  )
	      ))
       (add-from-graph-ring-raster-to-current-window-2
	 clipped-left-edge clipped-top-edge
	 clipped-right-edge clipped-bottom-edge
	 color-value
	 (if first-raster?
	     grid-background-color-value 0)
	 raster alu-function
	 left-edge-in-stored-raster top-edge-in-stored-raster)))
    (t  ; polychrome case
     (add-from-polychrome-raster-to-current-window
       clipped-left-edge clipped-top-edge
       clipped-right-edge clipped-bottom-edge
       raster
       left-edge-in-stored-raster top-edge-in-stored-raster))))



;;; Add-from-graph-ring-raster-to-current-window takes care of mapping from the
;;; raster to the screen.  This usually involves separate bitblts, one for the
;;; region to the left of the dateline, and one for the region to the right.

(defun-void add-from-graph-ring-raster-to-current-window
    (clipped-left-edge clipped-top-edge
		       clipped-right-edge clipped-bottom-edge
		       color-value grid-background-color-value first-raster?
		       graph-rendering ring-raster raster
		       left-edge-in-stored-raster top-edge-in-stored-raster
		       left-edge-of-new-data-in-ring-raster 
		       top-edge-of-new-data-in-ring-raster 
		       right-edge-of-new-data-in-ring-raster 
		       bottom-edge-of-new-data-in-ring-raster)
  
;  (format t "left = ~a, top = ~a, right = ~a, bottom = ~a~%"
;	  left-edge-of-new-data-in-ring-raster 
;	  top-edge-of-new-data-in-ring-raster
;	  right-edge-of-new-data-in-ring-raster 
;	  bottom-edge-of-new-data-in-ring-raster)
  
  (let* ((border-width (grid-border-width graph-rendering)))
    (setq left-edge-in-stored-raster 
	  (+r left-edge-in-stored-raster border-width)
	  top-edge-in-stored-raster 
	  (+r top-edge-in-stored-raster border-width)))
  
  #+development
  (when debug-mode-for-ring-raster?
    (add-from-graph-ring-raster-to-current-window-1
      clipped-left-edge clipped-top-edge
      clipped-right-edge clipped-bottom-edge
      color-value grid-background-color-value first-raster?
      graph-rendering raster
      left-edge-in-stored-raster
      top-edge-in-stored-raster)
    (return-from add-from-graph-ring-raster-to-current-window))
  
  (let* (
;	 (raster-dateline                       ; unused
;	   (raster-dateline ring-raster))
	 (erase-raster-dateline
	   (erase-raster-dateline ring-raster))
	 (raster-width
	   (width-of-graph-rendering-structure graph-rendering))
;	 (raster-width-to-right-of-dateline     ; unused
;	   (-r raster-width raster-dateline))
	 (raster-width-to-right-of-erase-dateline
	   (-r raster-width erase-raster-dateline))
	 (clipped-region-width (-r clipped-right-edge clipped-left-edge))
	 (clipped-region-height (-r clipped-bottom-edge clipped-top-edge))
	 (right-edge-in-stored-raster 
	   (+r left-edge-in-stored-raster clipped-region-width))
	 (bottom-edge-in-stored-raster 
	   (+r top-edge-in-stored-raster clipped-region-height)))
    
    (when left-edge-of-new-data-in-ring-raster

;      #+development
;      (when debug-graph-line-draw?
;        (format t "~%data clipping rectangles:")
;        (format t "~%~d, ~d, ~d, ~d~%"
;                left-edge-of-new-data-in-ring-raster
;                top-edge-of-new-data-in-ring-raster
;                right-edge-of-new-data-in-ring-raster
;                bottom-edge-of-new-data-in-ring-raster)
;        (when (eq debug-graph-line-draw? 'pause)
;          (terminal-pause 100)))

      ;; Adjust clipping based on data.
      (setq left-edge-of-new-data-in-ring-raster
	    (if (<r left-edge-of-new-data-in-ring-raster erase-raster-dateline)
		(+r left-edge-of-new-data-in-ring-raster
		    raster-width-to-right-of-erase-dateline)
		(-r left-edge-of-new-data-in-ring-raster erase-raster-dateline))
	    right-edge-of-new-data-in-ring-raster
	    (if (<r right-edge-of-new-data-in-ring-raster erase-raster-dateline)
		(+r right-edge-of-new-data-in-ring-raster
		    raster-width-to-right-of-erase-dateline)
		(-r right-edge-of-new-data-in-ring-raster erase-raster-dateline)))
      (if (>r left-edge-of-new-data-in-ring-raster left-edge-in-stored-raster)
	  (setq clipped-left-edge 
		(+r clipped-left-edge
		    (-r left-edge-of-new-data-in-ring-raster 
			left-edge-in-stored-raster))
		left-edge-in-stored-raster left-edge-of-new-data-in-ring-raster))
      (if (>r top-edge-of-new-data-in-ring-raster top-edge-in-stored-raster)
	  (setq clipped-top-edge 
		(+r clipped-top-edge
		    (-r top-edge-of-new-data-in-ring-raster 
			top-edge-in-stored-raster))
		top-edge-in-stored-raster top-edge-of-new-data-in-ring-raster))
      (if (<r right-edge-of-new-data-in-ring-raster right-edge-in-stored-raster)
	  (setq clipped-right-edge 
		(-r clipped-right-edge
		    (-r right-edge-in-stored-raster 
			right-edge-of-new-data-in-ring-raster))))
      (if (<r bottom-edge-of-new-data-in-ring-raster bottom-edge-in-stored-raster)
	  (setq clipped-bottom-edge 
		(-r clipped-bottom-edge
		    (-r bottom-edge-in-stored-raster 
			bottom-edge-of-new-data-in-ring-raster))))
      (setq clipped-region-width (-r clipped-right-edge clipped-left-edge)))
    ;; A useful thing to do for testing purposes is to comment out this section
    ;; so that the entire raster is always bitblt to the screen.
    
;    (format t "left = ~a, top = ~a, right = ~a, bottom = ~a~%"
;	    clipped-left-edge clipped-top-edge
;	    clipped-right-edge clipped-bottom-edge)
    
    (when (and (<r clipped-left-edge clipped-right-edge)
	       (<r clipped-top-edge clipped-bottom-edge))
      (if (<r left-edge-in-stored-raster raster-width-to-right-of-erase-dateline)
	  (cond
	    ((<=r (+r left-edge-in-stored-raster clipped-region-width)
		  raster-width-to-right-of-erase-dateline)
	     ;; only bitblt region to right of dateline
	     (add-from-graph-ring-raster-to-current-window-1
	       clipped-left-edge clipped-top-edge
	       clipped-right-edge clipped-bottom-edge
	       color-value grid-background-color-value first-raster?
	       graph-rendering raster
	       (+r left-edge-in-stored-raster erase-raster-dateline)
	       top-edge-in-stored-raster))
	    (t  ;; bitblt both regions
	     (let* ((new-left-edge-in-stored-raster
		      (+r left-edge-in-stored-raster erase-raster-dateline))
		    (width-of-region-a 
		      (-r raster-width new-left-edge-in-stored-raster))
		    (clipped-edge-for-dateline
		      (+r clipped-left-edge width-of-region-a)))
	       ;; bitblt region to right of dateline
	       (add-from-graph-ring-raster-to-current-window-1
		 clipped-left-edge clipped-top-edge
		 clipped-edge-for-dateline clipped-bottom-edge
		 color-value grid-background-color-value first-raster?
		 graph-rendering raster
		 new-left-edge-in-stored-raster
		 top-edge-in-stored-raster)
	       
	       ;; bitblt region to left of dateline
	       (when (>r clipped-right-edge clipped-edge-for-dateline)
		 (add-from-graph-ring-raster-to-current-window-1
		   clipped-edge-for-dateline clipped-top-edge
		   clipped-right-edge clipped-bottom-edge
		   color-value grid-background-color-value first-raster?
		   graph-rendering raster
		   0 top-edge-in-stored-raster)))))
	  
	  ;; only bitblt region to left of dateline
	  (add-from-graph-ring-raster-to-current-window-1
	    clipped-left-edge clipped-top-edge
	    clipped-right-edge clipped-bottom-edge
	    color-value grid-background-color-value first-raster?
	    graph-rendering raster
	    (-r left-edge-in-stored-raster 
		raster-width-to-right-of-erase-dateline)
	    top-edge-in-stored-raster)))))

;; Consider making this a macro!




;;; `Add-from-graph-rendering-to-current-window' takes care of bitblting the raster
;;; or rasters in the ring-raster of the graph-rendering to the window.  It is
;;; thus similar to add-from-icon-rendering-to-current-window.  When a set of
;;; monochrome rasters is used for color graphs (see also
;;; paint-graph-rendering-raster), add-from-graph-rendering-to-current-window
;;; loops through these bitblting each to the screen.  The first raster is painted
;;; and subsequent ones are added using an x-or alu function.  It is necessary to
;;; paint the first one to achieve the scrolling effect.  Subsequent ones must be
;;; painted using x-or so that they don't wipe out earlier ones.  Because x-or is
;;; used for these, it is important (as with icons) to "burn" regions in all other
;;; rasters blotted out by regions in any of the rasters (see also
;;; paint-graph-rendering-raster).

;;; When clipping-rectangles-for-new-data?  is non-nil, only a small region is
;;; bitblted.  In this case, it is not necessary to perform the bitblt from every
;;; plane.  It is only necessary to do a paint bitblt from the first plane (to
;;; clear the region to the grid background color) and then to do an x-or bitblt
;;; from the plane with the appropriate color.

(def-icp-message-functions add-from-graph-rendering-to-current-window
    (subtract-instead?
      (coordinate clipped-left-edge) (coordinate clipped-top-edge)
      (coordinate clipped-right-edge) (coordinate clipped-bottom-edge)
      (color-value grid-background-color-value)
      graph-rendering
      (coordinate left-edge-in-graph-rendering)
      (coordinate top-edge-in-graph-rendering)
      color-value  ; if only one raster
      (list-of-unsigned-integers	; nil if only one raster
	color-values-for-rasters?))
  (case type-of-current-window
    (t
     (let* ((rendering-structure
	      (graph-rendering-structure? graph-rendering)))
       (loop with flipped-colors
	       = (if (paint-foreground-only-p graph-rendering)
		     (nreverse
		       (copy-list-using-gensym-conses
			 color-values-for-rasters?))
		     color-values-for-rasters?)
	     with remaining-color-values?	
	       = flipped-colors
	     with flipped-rasters
	       = (if (paint-foreground-only-p graph-rendering)
		     (nreverse
		       (copy-list-using-gensym-conses
			 (raster-or-rasters rendering-structure)))
		     (raster-or-rasters rendering-structure))
	     with raster-or-rasters? = flipped-rasters
	     with remaining-rasters?
		  = (if (consp raster-or-rasters?) raster-or-rasters?)
	     as first-time? = t then nil
	     as next-color-value
		= (if remaining-color-values?
		      (car remaining-color-values?)
		      color-value)
	     as color-value-or-difference
		= (if first-time? 
		      next-color-value
		      (if (paint-foreground-only-p graph-rendering)
			  next-color-value
			  (color-difference 
			    next-color-value grid-background-color-value)))
	     as raster
		= (if remaining-rasters? 
		      (car remaining-rasters?)
		      raster-or-rasters?)
	     do
	 (cond
	   (#+development
	    (and (not debug-mode-for-ring-raster?)
		 clipping-rectangles-for-new-data?)
	    #-development
	    clipping-rectangles-for-new-data?
	    (loop as rest-of-rectangles = clipping-rectangles-for-new-data?
					then (nthcdr 4 rest-of-rectangles)
		  while rest-of-rectangles
		  do
	      (add-from-graph-ring-raster-to-current-window
		clipped-left-edge clipped-top-edge 
		clipped-right-edge clipped-bottom-edge
		color-value-or-difference grid-background-color-value
		first-time?
		graph-rendering rendering-structure raster
		left-edge-in-graph-rendering top-edge-in-graph-rendering
		(first rest-of-rectangles) (second rest-of-rectangles)
		(third rest-of-rectangles) (fourth rest-of-rectangles))))
	   (t
	    (add-from-graph-ring-raster-to-current-window
	      clipped-left-edge clipped-top-edge 
	      clipped-right-edge clipped-bottom-edge
	      color-value-or-difference grid-background-color-value
	      first-time?
	      graph-rendering rendering-structure raster
	      left-edge-in-graph-rendering top-edge-in-graph-rendering
	      nil nil nil nil)
	    ))
	 (cond
	   ((or (null remaining-color-values?)
		(null (cdr remaining-color-values?)))
	    (return nil))
	   (t
	    (pop remaining-color-values?)
	    (pop remaining-rasters?)))
	     finally
	       (when (paint-foreground-only-p graph-rendering)
		 (reclaim-gensym-list flipped-colors)
		 (reclaim-gensym-list flipped-rasters))
	     )))))

;; An alternative to computing color differences here would be to compute them in
;; update-color-values-for-graph and store them is another slot of the
;; graph-rendering.  This would however require this second list to be passed to
;; this function (since both color values and color differences are needed here).
;; This would be less efficient in the Telewindows case.




(defun make-graph-rendering-structure (width-of-graph-rendering-structure)
  (let* ((ring-raster-for-graph (make-ring-raster-for-graph)))
    (setf (raster-dateline ring-raster-for-graph) 0)
    (setf (erase-raster-dateline ring-raster-for-graph)
	  width-of-graph-rendering-structure)
    ring-raster-for-graph))




(def-icp-message-functions update-graph-dateline
			   ((coordinate dateline) 
			    (coordinate erase-dateline) graph-rendering)
  (case type-of-current-window
    (t
     (setf (raster-dateline
	     (graph-rendering-structure? graph-rendering))
	   dateline
	   (erase-raster-dateline
	     (graph-rendering-structure? graph-rendering))
	   erase-dateline))))


(def-icp-message-functions update-graph-data-extrema
			   ((coordinate left-edge) (coordinate top-edge)
			    (coordinate right-edge) (coordinate bottom-edge))
  (case type-of-current-window
    (t
     (setq clipping-rectangles-for-new-data?
	   (nconc
	     (graph-list
	       left-edge top-edge right-edge bottom-edge)
	     clipping-rectangles-for-new-data?)))))


(def-icp-message-functions clear-data-clipping-rectangles ()
  (case type-of-current-window
    (t
     (reclaim-graph-list clipping-rectangles-for-new-data?)
     (setq clipping-rectangles-for-new-data? nil))))



;; Color value is needed when bitblting to screen.


;(def-icp-message-functions set-plot-pattern-to-use ((symbol plot-pattern))
;  (case type-of-current-window				
;    (x11-window
;     (cond
;       (x11-mode?
;	(c-x11-set-line-pattern
;	  current-scratchpad-raster
;	  (case plot-pattern
;	    (wide 0)
;	    (dashed 1)
;	    (wide-dashed 2)
;	    (t 3))))))))

;; Plot patterns not currently used (see Plot Marker section in GRAPHS1).





;;;; Pseudo Run Lights




;;; `Update-pseudo-run-lights' is called with a keyword, that should be
;;; enumerated in `run-state-color-mapping.'  It should only be called in
;;; development.  A marque around the G2 window is animated in the colors
;;; implied by that mapping.  Setting `pseudo-run-light-enabled-p' maybe used to
;;; toggle these on and off.

#+development
(defparameter pseudo-run-light-enabled-p #-SymScale t #+SymScale nil)

#+development
(defparameter run-state-color-mapping?
  '(;; Top level Scheduler
    :take-actions-at-start-of-clock-tick blue

    ;; no more idle-process or process-icp-socket: white and pink are available again.
    ;;   -ncc, 19 Aug 1996 

    :scheduler-event coral
    :display-event cyan
    :network-event magenta

    :icp-message-task orange

    ;; Priority Scheduler
    :execute-task red

    ;; User Interface
    :service-workstation green
;    :native-window-heartbeat green
;    :synthetic-mouse-motion magenta
;    :poll-workstation orange
    :pending-events white
    :continuing-refeshing yellow
    :work-on-drawing-window purple
    
    ))

#+development
(defparameter color-of-unknown-state? nil)

#+development
(defvar latest-run-line-x 1)
#+development
(defvar latest-run-line-y 1)
#+development
(defvar latest-run-line-heading :east)

#+development
(defvar tracing-predicate nil "A list of (name . function) or NIL.")

#+development
(defmacro watch-for (expression)
  "Enter the debugger when the expression evaluates to non-NIL.  Checked pretty often."
  (cond (expression
	 `(setq tracing-predicate (list ',expression #'(lambda () ,expression))))
	(t
	 `(setq tracing-predicate nil))))

#+development
(defparameter memory-of-pseudo-run-lights (make-list 5000))

#+development
(defvar pointer-of-memory-of-pseudo-run-lights memory-of-pseudo-run-lights)

#+development
(defun update-pseudo-run-lights (run-state)
  (let (value)
    (when (and tracing-predicate (setq value (funcall (second tracing-predicate))))
      (break "Your tracing predicate ~s returned ~s." (first tracing-predicate) value)))
  (when pseudo-run-light-enabled-p
    (let* ((color? (getf run-state-color-mapping?
			 run-state
			 color-of-unknown-state?))
	   (width-of-window-border
	     (get-gensym-window-parameter system-window 'width-of-window-border))
	   (light-height (min width-of-window-border 5))
	   (light-width 2)
	   (step-size (+f light-width 1)))
      (when color?
	(case latest-run-line-heading
	  (:east (incff latest-run-line-x step-size))
	  (:west (decff latest-run-line-x step-size))
	  (t     (setq latest-run-line-heading :east)))
	(let* ((left-edge-of-track (+f (left-edge-of-window system-window) 1))
	       (top-edge-of-track (-f (bottom-edge-of-window system-window)
				      light-height))
	       (right-edge-of-track (-f (right-edge-of-window system-window)
					2 light-width))
	       (bottom-edge-of-track (+f top-edge-of-track light-height))
	       (turning? nil))
	  (unless (point-inside-rectangle-p 
		    latest-run-line-x latest-run-line-y
		    left-edge-of-track top-edge-of-track
		    (1+ right-edge-of-track) (1+ bottom-edge-of-track))
	    (setf turning? t)
	    (loop for p on memory-of-pseudo-run-lights
		  doing (setf (car p) nil))
	    (setf pointer-of-memory-of-pseudo-run-lights memory-of-pseudo-run-lights)
	    (multiple-value-setq
		(latest-run-line-heading latest-run-line-x latest-run-line-y)
	      (case latest-run-line-heading
		(:east (values :west right-edge-of-track top-edge-of-track))
		(:west (values :east left-edge-of-track top-edge-of-track)))))

	  (let* ((light-right (+ latest-run-line-x light-width))
		 (light-bottom (+f latest-run-line-y light-height))
		 ;; Possible Rebound if turning.
		 (extent-left latest-run-line-x)
		 (extent-top latest-run-line-y)
		 (extent-right light-right)
		 (extent-bottom light-bottom))
	    (when turning?
	      (setq extent-left left-edge-of-track
		    extent-top top-edge-of-track
		    extent-right right-edge-of-track
		    extent-bottom bottom-edge-of-track))
	    (setf (car pointer-of-memory-of-pseudo-run-lights)
		  run-state)
	    (pop pointer-of-memory-of-pseudo-run-lights)
	    (update-window
	      system-window
	      left-edge-of-track
	      top-edge-of-track
	      right-edge-of-track
	      bottom-edge-of-track
	      'update-pseudo-run-lights-1
	      turning?
	      latest-run-line-x latest-run-line-y
	      light-right light-bottom
	      color?)))))))

#+development
(defun update-pseudo-run-lights-1 (turning?
				    latest-run-line-x latest-run-line-y
				    light-right light-bottom
				    color?)
    (when turning?
      (paint-solid-rectangle-in-current-window
	left-edge-of-draw-area
	top-edge-of-draw-area
	right-edge-of-draw-area
	bottom-edge-of-draw-area
	1))
    #+nil
    (print (list latest-run-line-x latest-run-line-y
		 light-right light-bottom))
    (paint-solid-rectangle-in-current-window
      latest-run-line-x latest-run-line-y
      light-right light-bottom
      (map-to-color-value color?)))

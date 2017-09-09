;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module WINDOWS2 -- Operations on Scratchpad Rasters and Tiling Patterns

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Lowell B.  Hawkinson, Brian Matthews, Mark David, Andreas Hofmann,
;;; and Ong, Peng Tsin




(declare-forward-references
  (telewindows-check-version-of-remote-g2  function) ; g2-patches or telewindows.
  (shredded-raster-to-background-tile function)	; in IMAGES
  (read-raster function)		; also in IMAGES
  (reclaim-shredded-raster function)
  (telewindows-mdi-frame-p function))	; WINDOWS4


;;;; Clipping






;;; The following are only needed for the #+tv-windows implementation, although
;;; they are general.  So they are only defined in #+(or development tv-windows)
;;; environments.


#+development
(progn


;;; The function `clip-coordinate-for-raster' takes a value, a maximum,
;;; and a minimum for that value, and returns the value if it is within the range,
;;; or either maximum or minimum as appropriate.

(def-substitution-macro clip-coordinate-for-raster (coordinate minimum maximum)
  (if (>=r coordinate maximum)
      (-r maximum 1)
      (if (<r coordinate minimum) minimum coordinate)))



;;; The function `clip-coordinates-for-painting-line' takes the
;;; two end-points of a line and the top-left and bottom-right corners of the
;;; clip rectangle and returns four values (x1, y1, x2, y2) which correspond to
;;; the two end-points of the line after clipping.  If the line is completely
;;; outside the raster, the specified no-plot value is returned as the first
;;; value, and the other three values are 0.
;;;
;;; Note the maximum value for x is the right edge of the clip rectangle minus
;;; 1 and the maximum value for y is the bottom edge of the clip rectangle
;;; minus 1.
;;;
;;; Also ensure that the values of x1, y1, x2, y2 are not needed again in the
;;; rest of the function which calls clip-coordinates-for-painting-line.  This
;;; is because for distribution compiles, clip-coordinates-for-painting-line
;;; changes the values of its arguments.  The usual practice is to
;;; multiple-value-setq of the arguments to the call to
;;; clip-coordinates-for-painting-line.

(defmacro multiply-by-slope-r (x unnormalized-slope normalization-factor)
  `(the fixnum					; only 1st value needed
	(values
	  (roundr (*r ,x ,unnormalized-slope) ,normalization-factor))))


(defmacro divide-by-slope-r (y unnormalized-slope normalization-factor)
  `(the fixnum					; only 1st value needed
	(values
	  (roundr (*r ,y ,normalization-factor) ,unnormalized-slope))))


;; (defun a (x1 y1 x2 y2) (clip-coordinates-for-painting-line x1 y1 x2 y2 0 0 10 10 'lousy))

(defun clip-coordinates-for-painting-line
       (x1 y1 x2 y2
	clip-rectangle-left clip-rectangle-top
	clip-rectangle-right clip-rectangle-bottom
	no-plot-value)
  (cond
    ((and (<=r clip-rectangle-left x1)
	  (<r x1 clip-rectangle-right)
	  (<=r clip-rectangle-top y1)
	  (<r y1 clip-rectangle-bottom)
	  (<=r clip-rectangle-left x2)
	  (<r x2 clip-rectangle-right)
	  (<=r clip-rectangle-top y2)
	  (<r y2 clip-rectangle-bottom))
     (values x1 y1 x2 y2))
    ((or (and (<r x1 clip-rectangle-left)	; line left of clip rectangle
	      (<r x2 clip-rectangle-left))
	 (and (>=r x1 clip-rectangle-right)	; line right of clip rectangle
	      (>=r x2 clip-rectangle-right))
	 (and (<r y1 clip-rectangle-top)	; line above clip rectangle
	      (<r y2 clip-rectangle-top))
	 (and (>=r y1 clip-rectangle-bottom)	; line below clip rectangle
	      (>=r y2 clip-rectangle-bottom)))
     (values no-plot-value 0 0 0))
    (t						; Need to clip at one or more points
     (cond
       ((=r x1 x2)				; Vertical line:
	(values x1
		(clip-coordinate-for-raster
		  y1 clip-rectangle-top clip-rectangle-bottom)
		x2
		(clip-coordinate-for-raster
		  y2 clip-rectangle-top clip-rectangle-bottom)))
       ((=r y1 y2)				; Horizontal line:
	(values (clip-coordinate-for-raster
		  x1 clip-rectangle-left clip-rectangle-right)
		y1
		(clip-coordinate-for-raster
		  x2 clip-rectangle-left clip-rectangle-right)
		y2))
       (t					; Diagonal line:
	(let* ((flip-p (>w x1 x2)))
	  (when flip-p				; Assure that point1 is left of point2
	    (psetq x1 x2 x2 x1)
	    (psetq y1 y2 y2 y1))
	  (let* ((normalization-factor (-r x2 x1))
		 (unnormalized-slope (-r y2 y1))
		 (y0				; = value of x when y = 0.
		   (-r y1 (multiply-by-slope-r
			    x1 unnormalized-slope normalization-factor))))
	    (declare (type fixnum normalization-factor unnormalized-slope y0))
	    (let* ((x-at-intersect-with-top-edge
		     (divide-by-slope-r (-r clip-rectangle-top y0)
					unnormalized-slope
					normalization-factor))
		   (y-at-intersect-with-left-edge
		     (+r (multiply-by-slope-r clip-rectangle-left
					      unnormalized-slope
					      normalization-factor)
			 y0))
		   (x-at-intersect-with-bottom-edge
		     (divide-by-slope-r (-r clip-rectangle-bottom 1 y0)
					unnormalized-slope
					normalization-factor))
		   (y-at-intersect-with-right-edge
		     (+r (multiply-by-slope-r (-r clip-rectangle-right 1)
					      unnormalized-slope
					      normalization-factor)
			 y0)))
	      (declare (type fixnum
			     y-at-intersect-with-left-edge
			     y-at-intersect-with-right-edge
			     x-at-intersect-with-top-edge
			     x-at-intersect-with-bottom-edge))
	      (if (or (and (<r x-at-intersect-with-top-edge clip-rectangle-left)
			   (<r x-at-intersect-with-bottom-edge clip-rectangle-left))
		      (and (>=r x-at-intersect-with-top-edge clip-rectangle-right)
			   (>=r x-at-intersect-with-bottom-edge clip-rectangle-right))
		      (and (<r y-at-intersect-with-left-edge clip-rectangle-top)
			   (<r y-at-intersect-with-right-edge clip-rectangle-top))
		      (and (>=r y-at-intersect-with-left-edge clip-rectangle-bottom)
			   (>=r y-at-intersect-with-right-edge clip-rectangle-bottom)))
		  ;; If line not in raster, THEN return "no plot"
		  (values no-plot-value 0 0 0)
		  ;; ELSE
		  (progn			;remember:  point1 is left of point2
		    ;; Point 1
		    (when (not (and (<=r clip-rectangle-left x1)
				    (<r x1 clip-rectangle-right)
				    (<=r clip-rectangle-top y1)
				    (<r y1 clip-rectangle-bottom)))
		      (setq x1
			    (cond
			      ((<r y-at-intersect-with-left-edge clip-rectangle-top)
			       (setq y1 clip-rectangle-top)
			       x-at-intersect-with-top-edge)
			      ((>=r y-at-intersect-with-left-edge clip-rectangle-bottom)
			       (setq y1 (-r clip-rectangle-bottom 1))
			       x-at-intersect-with-bottom-edge)
			      (t
			       (cond
				 ((<r x1 clip-rectangle-left)
				  (setq y1 y-at-intersect-with-left-edge)
				  clip-rectangle-left)
				 ((<r x1 clip-rectangle-right)
				  x1)
				 (t		       ; (>=r x1 clip-rectangle-right)
				  (setq y1 y-at-intersect-with-right-edge)
				  (-r clip-rectangle-right 1)))))))
		    ;; Point 2
		    (when (not (and (<=r clip-rectangle-left x2)
				    (<r x2 clip-rectangle-right)
				    (<=r clip-rectangle-top y2)
				    (<r y2 clip-rectangle-bottom)))
		      (setq x2
			    (cond
			      ((<r y-at-intersect-with-right-edge clip-rectangle-top)
			       (setq y2 clip-rectangle-top)
			       x-at-intersect-with-top-edge)
			      ((>=r y-at-intersect-with-right-edge clip-rectangle-bottom)
			       (setq y2 (-r clip-rectangle-bottom 1))
			       x-at-intersect-with-bottom-edge)
			      (t
			       (cond
				 ((>=r x2 clip-rectangle-right)
				  (setq y2 y-at-intersect-with-right-edge)
				  (-r clip-rectangle-right 1))
				 ((>=r x2 clip-rectangle-left)
				  x1)
				 (t		       ; (<r x2 clip-rectangle-left)
				  (setq y2 y-at-intersect-with-left-edge)
				  clip-rectangle-left))))))
		    (if flip-p
			(values x2 y2 x1 y1)
			(values x1 y1 x2 y2))))))))))))


)      ; end of progn





;;;; Operations on the Current Scratchpad Raster





;;; On-current-scratchpad-raster-tiles is to be used around a body that paints on
;;; the current scratchpad raster when current-scratchpad-raster-tiled-p is true.
;;; A few symbols are reserved for use as local variables by the macro's internal
;;; control structure within body, at present: I, J, TILE-SIZE, X-OFFSET, Y-OFFSET.
;;; In addition, several special variables, documented elsewhere, are internal
;;; to this macro, or macros it uses.

(defmacro on-current-scratchpad-raster-tiles
	  ((x-coordinates y-coordinates
			  left-edge-of-paint top-edge-of-paint
			  right-edge-of-paint bottom-edge-of-paint
			  tiled-raster)
	   &body body)
  `(with-coordinates-adjusted-for-region
     ,x-coordinates ,y-coordinates
     (iterate-over-tiles-to-be-painted
       (,left-edge-of-paint ,top-edge-of-paint
	,right-edge-of-paint ,bottom-edge-of-paint
	,tiled-raster)
       (with-coordinates-adjusted-for-tile
	 ,x-coordinates ,y-coordinates
	 i j tile-size
	 . ,body))))


;; I created this to thin out the repeated code above in about five places
;; below.  At least now they're smaller, and less repetitious.  NOTE: It's not
;; clean that this takes over the symbols I, J, TILE-SIZE, etc., during body.
;; THAT NEEDS CLEANUP!  (MHD 4/22/93)





;;;; Stipples



;;; A `stipple' is a symbol corresponding to a stipple pattern that can be set
;;; in rasters used for icons.
;;;
;;; The constant `all-stipples' holds a list of the currently supported
;;; stipples:
;;;
;;;   LIGHT-STIPPLE
;;;   MEDIUM-STIPPLE
;;;   DARK-STIPPLE
;;;
;;; The macro `stipple-p' is true if its argument is one of the elements of
;;; all-stipples, i.e., a supported stipple.
;;;
;;; Stipples are new for G2 and Telewindows in G2 6.0. ...

(def-concept stipple)
;SS_ERROR
(eval-when (:compile-toplevel :load-toplevel :execute)
(defparameter all-stipples
  '(light-stipple medium-stipple dark-stipple))
)

(defmacro stipple-p (thing)
  (avoiding-variable-capture (thing)
    `(or . ,(loop for stipple
		      in (append
			   all-stipples
			   ;; TEMPORARY! Remove in a few weeks. (MHD 3/16/01)
			   '(light-texture medium-texture dark-texture))
		  collect `(eq ,thing ',stipple)))))


(def-global-property-name map-to-stipple-value)

(setf (map-to-stipple-value 'light-stipple) 1)
(setf (map-to-stipple-value 'medium-stipple) 2)
(setf (map-to-stipple-value 'dark-stipple) 3)






;;;; Setting the Stipple





(defun-void stipple-rectangle-in-scratchpad-raster
    (scratchpad-raster scratchpad-raster-type 
		       left-edge-of-rectangle top-edge-of-rectangle
		       right-edge-of-rectangle bottom-edge-of-rectangle stipple)
  (cond
    (current-scratchpad-raster-tiled-p
     (on-current-scratchpad-raster-tiles
	 ((left-edge-of-rectangle right-edge-of-rectangle)
	  (top-edge-of-rectangle bottom-edge-of-rectangle)
	  left-edge-of-rectangle top-edge-of-rectangle
	  right-edge-of-rectangle bottom-edge-of-rectangle
	  scratchpad-raster)
       (stipple-rectangle-in-scratchpad-raster-1
	 tile-to-paint scratchpad-raster-type 
	 left-edge-of-rectangle top-edge-of-rectangle
	 right-edge-of-rectangle bottom-edge-of-rectangle 
	 stipple)))
    (t
     (stipple-rectangle-in-scratchpad-raster-1
       scratchpad-raster scratchpad-raster-type 
       left-edge-of-rectangle top-edge-of-rectangle
       right-edge-of-rectangle bottom-edge-of-rectangle
       stipple))))



;;; stipple-rectangle-in-scratchpad-raster-1 ... stipple? may be the special value
;;; nil, remove any stipple from the raster.  This is used when issuing recycled
;;; raster.

(defun-void stipple-rectangle-in-scratchpad-raster-1
    (scratchpad-raster scratchpad-raster-type 
		       left-edge-of-rectangle top-edge-of-rectangle
		       right-edge-of-rectangle bottom-edge-of-rectangle stipple?)
  (case scratchpad-raster-type
    (x11-pixmap
     (c-x11-stipple-rectangle
       scratchpad-raster
       (or (map-to-stipple-value stipple?)
	   no-stipple-value)
       left-edge-of-rectangle
       top-edge-of-rectangle
       (-r right-edge-of-rectangle left-edge-of-rectangle)
       (-r bottom-edge-of-rectangle top-edge-of-rectangle)))))


(def-icp-message-functions stipple-rectangle-in-current-scratchpad-raster
			   ((coordinate clipped-left-edge)
			    (coordinate clipped-top-edge)
			    (coordinate clipped-right-edge)
			    (coordinate clipped-bottom-edge)
			    color-value (symbol stipple))
  (case current-scratchpad-raster-type
    (t
     (iterate-over-monochrome-raster-list-if-appropriate (color-value)
       (stipple-rectangle-in-scratchpad-raster
	 current-scratchpad-raster
	 current-scratchpad-raster-type
	 clipped-left-edge clipped-top-edge
	 clipped-right-edge clipped-bottom-edge
	 stipple)))))





;;;; Solid Rectangle



;;; The ICP message function `paint-solid-rectangle-in-current-scratchpad-raster' paints
;;; an arbitrary rectangular area of the current scratchpad-raster, as specified by the
;;; edge arguments.  The color of the painted area will be color-value.

(defun-void fill-rectangle-on-scratchpad-raster
    (scratchpad-raster scratchpad-raster-type
		       left-edge-of-rectangle top-edge-of-rectangle
		       right-edge-of-rectangle bottom-edge-of-rectangle color-value)
  (cond
    (current-scratchpad-raster-tiled-p
     (on-current-scratchpad-raster-tiles
	 ((left-edge-of-rectangle right-edge-of-rectangle)
	  (top-edge-of-rectangle bottom-edge-of-rectangle)
	  left-edge-of-rectangle top-edge-of-rectangle
	  right-edge-of-rectangle bottom-edge-of-rectangle
	  scratchpad-raster)
       (fill-rectangle-on-scratchpad-raster-1
	 tile-to-paint scratchpad-raster-type
	 left-edge-of-rectangle top-edge-of-rectangle
	 right-edge-of-rectangle bottom-edge-of-rectangle color-value)))
    (t
     (fill-rectangle-on-scratchpad-raster-1
       scratchpad-raster scratchpad-raster-type
       left-edge-of-rectangle top-edge-of-rectangle
       right-edge-of-rectangle bottom-edge-of-rectangle color-value))))



(defun-void fill-rectangle-on-scratchpad-raster-1
    (scratchpad-raster scratchpad-raster-type
		       left-edge-of-rectangle top-edge-of-rectangle
		       right-edge-of-rectangle bottom-edge-of-rectangle color-value)
  (case scratchpad-raster-type
    (x11-pixmap
     (c-x11-pfill-rectangle
       scratchpad-raster
       left-edge-of-rectangle top-edge-of-rectangle
       (-r right-edge-of-rectangle left-edge-of-rectangle)
       (-r bottom-edge-of-rectangle top-edge-of-rectangle)
       color-value))))



(def-icp-message-functions paint-solid-rectangle-in-current-scratchpad-raster
			   ((coordinate clipped-left-edge)
			    (coordinate clipped-top-edge)
			    (coordinate clipped-right-edge)
			    (coordinate clipped-bottom-edge)
			    color-value)
  (case current-scratchpad-raster-type
    (t
     (iterate-over-monochrome-raster-list-if-appropriate (color-value)
       (fill-rectangle-on-scratchpad-raster
	 current-scratchpad-raster
	 current-scratchpad-raster-type
	 clipped-left-edge clipped-top-edge
	 clipped-right-edge clipped-bottom-edge color-value)))))

;; Consider distinguishing the single-pixel height and width cases, as is done
;; in add-solid-rectangle-to-current-window, if there is reason to think they
;; will arise with any frequency (as they might in the formation of characters
;; and icons).

(def-icp-message-functions paint-clearing-rectangle-in-current-scratchpad-raster
			   ((coordinate clipped-left-edge)
			    (coordinate clipped-top-edge)
			    (coordinate clipped-right-edge)
			    (coordinate clipped-bottom-edge)
			    color-value)
  (case current-scratchpad-raster-type
    (t
     (let ((paint-only-target-monochrome-raster-p nil))
       (iterate-over-monochrome-raster-list-if-appropriate (color-value)
	 (fill-rectangle-on-scratchpad-raster
	   current-scratchpad-raster
	   current-scratchpad-raster-type
	   clipped-left-edge clipped-top-edge
	   clipped-right-edge clipped-bottom-edge color-value))))))





;;;; Point




;;; Local-current-scratchpad-pixel is the accessor for the (x,y) pixel in a
;;; local current scratchpad raster.  The top left corner pixel is the (0,0)
;;; pixel.  (This should only be used to implement other primitives, and may
;;; not be required in some implementations.)

(def-substitution-macro local-current-scratchpad-pixel (x y)
  (case current-scratchpad-raster-type
    (t
     x y ;; (declare (ignore x y))
     (error "Unimplemented primitive: local-current-scratchpad-pixel!"))))

;; Only the setf method, not the above, is actually ever needed in practice
;; at this time, except for creating fonts on lisp machines; see module
;; FONTS.  (MHD 2/7/91, and 2/5/93)



(defsetf local-current-scratchpad-pixel (x y) (color-value)
  `(progn
     (case current-scratchpad-raster-type
       (x11-pixmap
	(c-x11-pdraw-point current-scratchpad-raster ,x ,y ,color-value)))
     ,color-value))			; return value, per convention

;; Consider defining local-binary-scratchpad-pixel, which could use sbit
;; instead of aref.





;;; The ICP message function `paint-point-in-current-scratchpad-raster' ...

(defun-substitution-macro paint-point-in-current-scratchpad-raster-2
			  (x y color-value)
  (setf (local-current-scratchpad-pixel x y) color-value))



(defun-substitution-macro paint-point-in-current-scratchpad-raster-1
			  (x y color-value)
  (cond
    (current-scratchpad-raster-tiled-p
     (on-current-scratchpad-raster-tiles
       ((x) (y)
	x y x y current-scratchpad-raster)
       (let ((current-scratchpad-raster tile-to-paint))
	 (paint-point-in-current-scratchpad-raster-2 x y color-value))))
    (t
     (paint-point-in-current-scratchpad-raster-2 x y color-value))))



(def-icp-message-functions paint-point-in-current-scratchpad-raster
			   ((coordinate x) (coordinate y) color-value)
  (case current-scratchpad-raster-type
    (t
     (iterate-over-monochrome-raster-list-if-appropriate (color-value)
       (paint-point-in-current-scratchpad-raster-1 x y color-value)))))





;;;; Filled Triangle



;;; The ICP message function `paint-filled-triangle-in-current-scratchpad-raster'
;;; ...

(defun-substitution-macro paint-filled-triangle-in-current-scratchpad-raster-2
			  (scratchpad-raster x1 y1 x2 y2 x3 y3 color-value)
  (case current-scratchpad-raster-type
    (x11-pixmap
     (c-x11-pfill-triangle
       scratchpad-raster x1 y1 x2 y2 x3 y3 color-value))))

(defun-substitution-macro paint-filled-triangle-in-current-scratchpad-raster-1
			  (x1 y1 x2 y2 x3 y3 color-value)
  (cond
    (current-scratchpad-raster-tiled-p
     (on-current-scratchpad-raster-tiles
       ((x1 x2 x3) (y1 y2 y3)
	(minr x1 x2 x3) (minr y1 y2 y3)
	(maxr x1 x2 x3) (maxr y1 y2 y3)
	current-scratchpad-raster)
       (paint-filled-triangle-in-current-scratchpad-raster-2
	 tile-to-paint x1 y1 x2 y2 x3 y3 color-value)))
    (t
     (paint-filled-triangle-in-current-scratchpad-raster-2
       current-scratchpad-raster x1 y1 x2 y2 x3 y3 color-value))))

(def-icp-message-functions paint-filled-triangle-in-current-scratchpad-raster
			   ((coordinate x1) (coordinate y1)
			    (coordinate x2) (coordinate y2)
			    (coordinate x3) (coordinate y3)
			    color-value)
  (case current-scratchpad-raster-type
    (t
     (iterate-over-monochrome-raster-list-if-appropriate (color-value)
       (paint-filled-triangle-in-current-scratchpad-raster-1
	 x1 y1 x2 y2 x3 y3 color-value)))))


;;; The system variable `the-polygon-data-buffer' holds a data-abstracted buffer
;;; of points, of length (2 X maximum-polygon-coordinates). This is implemented
;;; as a simple gensym string (i.e., a Lisp string).  The reason for this choice
;;; of implementation is that it allows the information to be passed to C
;;; without any copying. This is used to send the information to C via foreign
;;; function calls.  The data is setf'd into the buffer using the setf'able
;;; accessor `polygon-data-buffer-element', which takes an index and sets the
;;; byte value at that position.  The values are 16-bit integers stored as pairs
;;; of bytes in this order: least significant 8 bits, most significant 8 bits.

;;; The function `fill-polygon-data-buffer-from-unsigned-point-list' is used to
;;; fill this data buffer given a list of points.

(def-system-variable the-polygon-data-buffer WINDOWS2
  (:funcall obtain-simple-gensym-string #.(* 2 maximum-polygon-coordinates)))

(defmacro polygon-data-buffer-element (index)
  `(schar the-polygon-data-buffer ,index))

(defun fill-polygon-data-buffer-from-unsigned-point-list
    (unsigned-point-list)
  (loop for x fixnum in unsigned-point-list
	as i fixnum from 0 by 2
	do (setf (polygon-data-buffer-element i)
		 (code-char (logandf x 255)))
	   (setf (polygon-data-buffer-element (1+f i))
		 (code-char (logandf (ashf x -8) 255)))
	finally
	  (return the-polygon-data-buffer)))

(defun-substitution-macro paint-filled-polygon-in-current-scratchpad-raster-2
    (scratchpad-raster polygon-point-list left top right bottom color-value)
  (case current-scratchpad-raster-type
    (x11-pixmap
     (let ((point-data
	     (fill-polygon-data-buffer-from-unsigned-point-list
	       polygon-point-list))
	   (number-of-points (floorf (length polygon-point-list) 2)))
       (c-x11-pfill-clipped-polygon
	 scratchpad-raster point-data number-of-points
	 left top right bottom
	 color-value)))))

(defun separate-x-y-coordinates (points)
  (loop for (x y) on points by 'cddr
	collect x into x-coords using gensym-cons-macro
	collect y into y-coords using gensym-cons-macro
	finally (return (values x-coords y-coords))))

(defun combine-x-and-y-coordinates (x-coords y-coords)
  (loop for x in x-coords
	for y in y-coords
	collect x using gensym-cons-macro
	collect y using gensym-cons-macro))

(defun calculate-bounds-of-unsigned-point-list (point-list)
  (loop with left = (car point-list)
	with top =  (cadr point-list)
	with right = left
	with bottom = top
        for tail on (cddr point-list) by 'cddr
	as (x y . ignore) = tail
	do
          (setf left (minf left x))
	  (setf right (maxf right x))
	  (setf top (minf top y))
	  (setf bottom (maxf bottom y))
	finally
	  (return (values (maxf 0 (-f left 8192))
			  (maxf 0 (-f top 8192))
			  (-f right 8192)
			  (-f bottom 8192)))))

(defun-substitution-macro paint-filled-polygon-in-current-scratchpad-raster-1
    (unsigned-point-list color-value)
  (multiple-value-bind (left top right bottom)
      (calculate-bounds-of-unsigned-point-list unsigned-point-list)
    (cond
      (current-scratchpad-raster-tiled-p
       (multiple-value-bind (x-coords y-coords)
	   (separate-x-y-coordinates unsigned-point-list)
	 (on-current-scratchpad-raster-tiles
	     ((left right (:list x-coords)) (top bottom (:list y-coords))
	      left top right bottom
	      current-scratchpad-raster)
	   (let ((adjusted-unsigned-point-list
		   (combine-x-and-y-coordinates x-coords y-coords)))
	     (paint-filled-polygon-in-current-scratchpad-raster-2
	       tile-to-paint
	       adjusted-unsigned-point-list
	       left top right bottom
	       color-value)
	     (reclaim-gensym-tree adjusted-unsigned-point-list)))
	 (reclaim-gensym-list x-coords)
	 (reclaim-gensym-list y-coords)))
      (t
       (paint-filled-polygon-in-current-scratchpad-raster-2
	 current-scratchpad-raster
	 unsigned-point-list
	 left top right bottom
	 color-value)))))

(def-icp-message-functions paint-filled-polygon-in-current-scratchpad-raster
    ((list-of-unsigned-integers unsigned-polygon-point-list)
     color-value)
  (case current-scratchpad-raster-type
    (t
     (iterate-over-monochrome-raster-list-if-appropriate (color-value)
       (paint-filled-polygon-in-current-scratchpad-raster-1
	 unsigned-polygon-point-list color-value)))))






;;;; Line



;;; The ICP message function `paint-line-in-current-scratchpad-raster'
;;; paints a line from (x1,y1) to (x2,y2) in the current scratchpad raster.
;;; The color of the line will be color-value.

;;; The argument paint-last-point? is obsolete; the point (x2, y2) itself is
;;; always painted.  But the argument cannot be removed without dealing with
;;; Telewindows Protocol compatibility issues, so it will remain.

(defun-substitution-macro paint-line-in-current-scratchpad-raster-2
			  (scratchpad-raster x1 y1 x2 y2 color-value)
  (case current-scratchpad-raster-type
    (x11-pixmap
     (c-x11-pdraw-line scratchpad-raster x1 y1 x2 y2 color-value))))

(defun-substitution-macro paint-line-in-current-scratchpad-raster-1
			  (x1 y1 x2 y2 color-value)
  (cond
    (current-scratchpad-raster-tiled-p
     (on-current-scratchpad-raster-tiles
       ((x1 x2) (y1 y2)
	(minr x1 x2) (minr y1 y2)
	(maxr x1 x2) (maxr y1 y2)
	current-scratchpad-raster)
       (paint-line-in-current-scratchpad-raster-2
	 tile-to-paint x1 y1 x2 y2 color-value)))
    (t
     (paint-line-in-current-scratchpad-raster-2
       current-scratchpad-raster x1 y1 x2 y2 color-value))))


(def-icp-message-functions paint-line-in-current-scratchpad-raster
			   ((coordinate x1) (coordinate y1)
			    (coordinate x2) (coordinate y2)
			    color-value (boolean paint-last-point?))
  (case current-scratchpad-raster-type
    (t
     (iterate-over-monochrome-raster-list-if-appropriate (color-value)
       (paint-line-in-current-scratchpad-raster-1
	 x1 y1 x2 y2 color-value)))))

;; Paint-last-point? should not be supported.  It is only supported on Lisp
;; machines at the primitive level at present, and it is never used by higher
;; software.  The only way to implement it otherwise is to read the pixel value
;; of the last point then restore it after drawing the line.  This tends to be
;; very slow and/or complex to implement.  In any case, its major utility is not
;; here (where we are "painting") but in the case where we are adding (xor'ing),
;; lines, and we do not have an operation for that right now anyway. (MHD 2/8/89)
;; --- UPDATE:
;; Paint-last-point? is no longer used by the non-icp cases.  It just gets sent
;; gets evaluated in the ICP case, to be sent over ICP for compatibility with the
;; old (previous versions') arglist.  The current behavior is that the last point
;; is always painted, which was always the behavior in practice for this
;; operation.  Consider removing the argument in some cleanup eventually!  This
;; all applies the wide-line painting operation, q.v., below.
;; (MHD 3/8/93)





;;;; Wide Line



;;; The ICP message function `paint-wide-line-in-current-scratchpad-raster' ...

;;; The argument paint-last-point? is obsolete; the point (x2, y2) itself is
;;; always painted.  But the argument cannot be removed without dealing with
;;; Telewindows Protocol compatibility issues, so it will remain.

(def-substitution-macro paint-wide-line-in-current-scratchpad-raster-2
			(x1 y1 x2 y2 color-value line-width)
  (case current-scratchpad-raster-type
    (x11-pixmap
     (c-x11-pdraw-wide-line
       current-scratchpad-raster x1 y1 x2 y2 color-value line-width))))

(defun-void paint-wide-line-in-current-scratchpad-raster-1
	    (x1 y1 x2 y2 color-value line-width)
  (cond
    (current-scratchpad-raster-tiled-p
     (on-current-scratchpad-raster-tiles
       ((x1 x2) (y1 y2)
	(minr x1 x2) (minr y1 y2)
	(maxr x1 x2) (maxr y1 y2)
	current-scratchpad-raster)
       (let ((current-scratchpad-raster tile-to-paint)
	     (current-scratchpad-raster-tiled-p nil))
	 (paint-wide-line-in-current-scratchpad-raster-2
	   x1 y1 x2 y2 color-value line-width))))
    (t
     (paint-wide-line-in-current-scratchpad-raster-2
       x1 y1 x2 y2 color-value line-width))))

(def-icp-message-functions paint-wide-line-in-current-scratchpad-raster
			   ((coordinate x1)
			    (coordinate y1)
			    (coordinate x2)
			    (coordinate y2)
			    color-value
			    (boolean paint-last-point?)
			    (unsigned-integer line-width))
  (case current-scratchpad-raster-type
    (t
     (iterate-over-monochrome-raster-list-if-appropriate (color-value)
       (paint-wide-line-in-current-scratchpad-raster-1
	 x1 y1 x2 y2 color-value line-width)))))



#+unused
(defun paint-wide-line-using-thin-lines (x1 y1 x2 y2 color-value line-width)
  (loop for count from 1 to line-width
	as relative-y = (-r (halfr line-width)) then (+r relative-y 1)
	do (paint-line-in-current-scratchpad-raster-1
	     x1 (+r y1 relative-y)
	     x2 (+r y2 relative-y)
	     color-value)))

;; This is necessary because the lisp machine line draw primitives (unlike all
;; other line draw primitives) do not allow specifying line width.
;; Paint-wide-line-using-thin-lines is always called from
;; paint-wide-line-in-current-scratchpad-raster, an icp function.  Therefore, the
;; calls by paint-wide-line-using-thin-lines to
;; paint-line-in-current-scratchpad-raster will never be over ICP.
;; -- consider making this be defined for Lispm only. (MHD 2/23/93)

;; Note that the paint-last-point? argument is an artifact of the paint-line-
;; in-current-scratchpad-raster.  It is useless.  See discussion above.  (It
;; has been dropped as an argument to the paint-wide-line-using-thin-lines
;; subfunction for this reason. (MHD 2/22/93)





;;;; Arc or Circle



;;; The ICP message function `paint-arc-or-circle-in-current-scratchpad-raster'
;;; takes three coordinate points which determine a circle or arc.  The coordinates
;;; are in image units.  The coordinates are coerced into short floats and the
;;; center of the circle is computed using floating point arithmetic.  The points of
;;; the circle are then computed using Minsky's algorithm, also in floating point
;;; arithmetic.  The computed points are rounded to integers which give the
;;; raster coordinates for the pixel to paint.  If the x-scale and y-scale are
;;; not the same, the coordinates are "stretched" prior to computation of the
;;; circle points so that the x-scale and y-scale are the same.  The basic
;;; circle computation algorithm can then be used except that the computed
;;; points have to be "unstretched" before they are painted into the raster.
;;; The result is correct: an ellipse is painted rather than a circle when the
;;; x and y scales aren't the same.
;;;
;;; Circle and Arc Drawing Algorithm:
;;; The two-dimensional rotation transformation matrix for clockwise rotation
;;; in a right handed coordinate system is:
;;;
;;;    |cos(a)  sin(a)|
;;;    |-sin(a) cos(a)|
;;;
;;; AB uses a left handed coordinate system so the matrix is:
;;;
;;;    |cos(a) -sin(a)|
;;;    |sin(a)  cos(a)|
;;;
;;; For small angle a (a = k), the trigonometric functions can be approximated:
;;;
;;;    |1 -k|
;;;    |k  1|
;;;
;;; The equations are thus
;;;
;;;    x' = x - ky
;;;    y' = kx + y
;;;
;;; If these are evaluated serially rather than in parallel,
;;;
;;;    x' = x - ky
;;;    y' = kx' + y
;;;
;;; the computation is completely reversible and therefore stable.  Small
;;; errors due to serial evaluation, small angle approximation, and finite
;;; accuracy of floating point numbers will occur.  However, they will be
;;; recovered and the circle will not spiral to 0 or infinity.  This circle
;;; drawing algorithm is known as the Minsky algorithm after Marvin Minsky, who
;;; developed it at MIT in the 1960's.
;;;
;;; There are a number of criteria for choosing k.  K should be small enough so
;;; that small angle approximations are valid and errors due to serial
;;; evaluation are kept small.  K should also be small enough so that there are
;;; no discontinuities on the drawn path (all pixels touch).  On the other
;;; hand, k should be chosen as large as possible for efficiency reasons.
;;;
;;; The requirement that there be no discontinuities on the drawn path yields
;;; an initial formula for k.  Since k is in radians, the distance by the
;;; rotation is kr where r is the radius of the circle.  This distance should
;;; be less than or equal to one pixel unit (it is O.K.) to paint a pixel more
;;; than once.  Thus, k <= 1/r.
;;;
;;; K must be small enough so that the errors introduced are minimized enough
;;; that the maximum radius error is small (less than 0.5 pixels in the x or y
;;; direction).  This ensures that the "wrong" pixel won't be drawn; there
;;; won't be any discontinuities and circles and arcs will end exactly on the
;;; correct end-point.  Empirically, a good value for k is 1/2r.
;;;
;;; The number of iterations required to complete is simply 2 pi / k
;;;
;;; Arc drawing is a little more complicated than circle drawing because start
;;; and end points have to be chosen.  It is assumed that the points are in
;;; order.  Points 1 and 3 sub-divide the circle into two arcs and point 2 is
;;; used to choose the correct one.  The number of iterations required to
;;; complete is (a1 - a3) / k, where a1 and a3 are the arc-tangents of points 1
;;; and 3.  It should not however be necessary to compute the number of
;;; iterations because (assuming k is small enough so that things stay
;;; accurate) the endpoint should be encountered in the computation and this
;;; can be used as a test to stop.

;;; Recent Revisions to the algorithm:
;;;
;;; The new Paint-arc-or-circle-in-current-scratch-pad-raster takes its
;;; arguments in workspace units.  The circle is drawn in workspace units and
;;; the points are scaled just before they are painted in the raster.  This
;;; solves the previous scaling problem and also simplifies circle drawing.  It
;;; is no longer necessary to stretch and un-stretch.  A minor draw back is
;;; that all points of the workspace circle will always be painted, even for
;;; small scales.  At some future time, it may be desireable to cache this
;;; workspace unit circle somehow so that the points don't have to be
;;; recalculated every time for different scales.



(defmacro with-circle-chords-1 (x1 y1 x2 y2 x3 y3 &body body)
  `(let* ((a1 (-w ,x2 ,x1))
	  (b1 (-w ,y2 ,y1))
	  (c1
	    (/ (+ (* ,x2 ,x2) (* ,y2 ,y2)
		   (- (* ,x1 ,x1)) (- (* ,y1 ,y1)))
	       2.0))
	  (a2 (-w ,x3 ,x2))
	  (b2 (-w ,y3 ,y2))
	  (c2
	    (/ (+ (* ,x3 ,x3) (* ,y3 ,y3)
		   (- (* ,x2 ,x2)) (- (* ,y2 ,y2))) 2.0))
	  (determinant (- (* a1 b2) (* a2 b1))))
     (declare (type fixnum a1 b1 a2 b2))
     ,@body))

(defmacro with-circle-chords (x1 y1 x2 y2 x3 y3 &body body)
  `(with-temporary-gensym-float-creation circle-draw
     (with-circle-chords-1 ,x1 ,y1 ,x2 ,y2 ,x3 ,y3 ,@body)))


;;; With-circle-info-for-external-draw-primitives is used on X
;;; implementations to use native circle and arc draw routines (see
;;; paint-arc-or-circle-in-current-scratchpad-raster).

(defmacro with-circle-info-for-external-draw-primitives
	  (x1 y1 x2 y2 x3 y3 &body body)
  `(with-circle-chords
     ,x1 ,y1 ,x2 ,y2 ,x3 ,y3
     ;; Determinant is always an integer, but could possibly be a bignum.
     ;; Generic = matches usage in calculate-center-of-circle.
     (if (= determinant 0)			       ; this will rarely be true
	 ;; points are colinear
	 (paint-line-in-current-scratchpad-raster	; Fixed to scale pts. (BAH/MHD 4/20/90)
	   (delta-x-in-window x1 x-scale) (delta-y-in-window y1 y-scale)
	   (delta-x-in-window x3 x-scale) (delta-y-in-window y3 y-scale)
	   color-value t)			; changed to paint last pt. (MHD 5/2/90)
	 (let* ((x-center
		  (coerce-to-gensym-float
		    (/ (+ (* c1 b2) (* c2 (-r b1))) determinant)))
		(y-center
		  (coerce-to-gensym-float
		    (/ (+ (* c1 (-r a2)) (* c2 a1)) determinant)))
		(normalized-x-scale
		  (* x-scale #.(/ 1.0 (coerce-to-gensym-float
					(normalized-scale)))))
		(normalized-y-scale
		  (* y-scale #.(/ 1.0 (coerce-to-gensym-float
					(normalized-scale)))))
		(radius
		  (compute-float-circle-radius
		    x-center y-center x1 y1))
		(diameter (+ radius radius))
		(scaled-x-offset
		  (round (* (- x-center radius) normalized-x-scale)))
		(scaled-y-offset
		  (round (* (- y-center radius) normalized-y-scale)))
		(scaled-width
		  (round (* diameter normalized-x-scale)))
		(scaled-height
		  (round (* diameter normalized-y-scale))))
	   (declare (type fixnum
			  scaled-x-offset scaled-y-offset
			  scaled-width scaled-height))
	   ,@body))))



(defun-void paint-arc-or-circle-in-current-scratchpad-raster-1
    (x1 y1 x2 y2 x3 y3 x-scale y-scale color-value circle? filled?)
  (cond
    (current-scratchpad-raster-tiled-p
     (multiple-value-bind
       (min-x min-y max-x max-y)
	 (if circle?
	     (compute-circle-bounding-box x1 y1 x2 y2 x3 y3)
	     (compute-arc-bounding-box x1 y1 x2 y2 x3 y3))
       (setq min-x (delta-x-in-window min-x x-scale)
	     max-x (delta-x-in-window max-x x-scale)
	     min-y (delta-y-in-window min-y y-scale)
	     max-y (delta-y-in-window max-y y-scale))
       (when current-x-offset-for-stored-raster?
	 (setq min-x (-r min-x current-x-offset-for-stored-raster?)
	       max-x (-r max-x current-x-offset-for-stored-raster?)
	       min-y (-r min-y current-y-offset-for-stored-raster?)
	       max-y (-r max-y current-y-offset-for-stored-raster?)))
       (iterate-over-tiles-to-be-painted
	 (min-x min-y max-x max-y current-scratchpad-raster)
	 (with-offsets-for-region-and-tile
	   i j tile-size
	   (let ((current-scratchpad-raster tile-to-paint)
		 (current-scratchpad-raster-tiled-p nil))
	     (paint-arc-or-circle-in-current-scratchpad-raster-2
	       x1 y1 x2 y2 x3 y3 x-scale y-scale
	       color-value circle? filled?))))))
    (t
     (paint-arc-or-circle-in-current-scratchpad-raster-2
       x1 y1 x2 y2 x3 y3 x-scale y-scale
       color-value circle? filled?))))

(defun-void paint-arc-or-circle-in-current-scratchpad-raster-2
    (x1 y1 x2 y2 x3 y3 x-scale y-scale
	color-value circle? filled?)
  (case current-scratchpad-raster-type
    (x11-pixmap
     (with-circle-info-for-external-draw-primitives
       x1 y1 x2 y2 x3 y3
       (if circle?
	   (if filled?
	       (c-x11-pfill-arc
		 current-scratchpad-raster
		 (x-with-region-and-tile-offset scaled-x-offset)
		 (y-with-region-and-tile-offset scaled-y-offset)
		 scaled-width
		 scaled-height
		 0 #.(* 360 64) color-value)
	       (c-x11-pdraw-arc
		 current-scratchpad-raster
		 (x-with-region-and-tile-offset scaled-x-offset)
		 (y-with-region-and-tile-offset scaled-y-offset)
		 scaled-width
		 scaled-height
		 0 #.(* 360 64) color-value))
	   ;; Remember that +ve y goes "downwards" when computing
	   ;; angles.  Also, all angles are altered based on the x
	   ;; and y scales.
	   (let ((angle-1			       ;scaled by 64 per Xlib
		   (round
		     (* (atan
			  (* (- y-center y1) normalized-y-scale)
			  (* (- x1 x-center) normalized-x-scale))
			#.(* 64 (/ 360.0 (* 2 pi))))))
		 (angle-2			       ;scaled by 64 per Xlib
		   (round
		     (* (atan
			  (* (- y-center y2) normalized-y-scale)
			  (* (- x2 x-center) normalized-x-scale))
			#.(* 64 (/ 360.0 (* 2 pi))))))
		 (angle-3			       ;scaled by 64 per Xlib
		   (round
		     (* (atan
			  (* (- y-center y3) normalized-y-scale)
			  (* (- x3 x-center) normalized-x-scale))
			#.(* 64 (/ 360.0 (* 2 pi))))))
		 (start-angle 0)
		 (inc-angle 0))
	     (declare (type fixnum
			    angle-1 angle-2 angle-3 start-angle inc-angle))
	     ;; Ensure +ve angles.
	     (if (<f angle-1 0)
		 (setq angle-1 (+ #.(* 360 64) angle-1)))
	     (if (<f angle-2 0)
		 (setq angle-2 (+ #.(* 360 64) angle-2)))
	     (if (<f angle-3 0)
		 (setq angle-3 (+ #.(* 360 64) angle-3)))
	     ;; Six cases possible: a1<a2<a3(-clock),
	     ;; a1<a3<a2(+clock), a2<a1<a3(+clock),
	     ;; a2<a3<a1(-clock), a3<a1<a2(-clock), a3<a2<a1(+clock)
	     (if (>f angle-1 angle-2)
		 (if (>f angle-1 angle-3)
		     (if (>f angle-2 angle-3)
			 (progn			       ; a1>a2>a3 +
						       ; a3<a1 +clk
			   (setq start-angle angle-3)
			   (setq inc-angle (-f angle-1 angle-3))
			   )
			 (progn			       ; a1>a3>a2 -
						       ; a3<a1 -clk
			   (setq start-angle angle-3)
			   (setq inc-angle
				 (-f angle-1 angle-3 #.(* 360 64)))
			   ))
		     (progn			       ; a3>a1>a2 +
						       ; a1<a3 +clk
		       (setq start-angle angle-1)
		       (setq inc-angle
			     (-f angle-3 angle-1 #.(* 360 64)))
		       ))
		 (if (>f angle-1 angle-3)
		     (progn			       ; a2>a1>a3 -
						       ; a3<a1 -clk
		       (setq start-angle angle-3)
		       (setq inc-angle
			     (-f angle-1 angle-3 #.(* 360 64)))
		       )
		     (if (>f angle-2 angle-3)
			 (progn			       ; a2>a3>a1 +
						       ; a1<a3 +clk
			   (setq start-angle angle-1)
			   (setq inc-angle
				 (-f angle-3 angle-1 #.(* 360 64)))
			   )
			 (progn			       ; a3>a2>a1 -
						       ; a1<a3 -clk
			   (setq start-angle angle-1)
			   (setq inc-angle (-f angle-3 angle-1))
			   ))))
	     (c-x11-pdraw-arc
	       current-scratchpad-raster
	       (x-with-region-and-tile-offset scaled-x-offset)
	       (y-with-region-and-tile-offset scaled-y-offset)
	       scaled-width
	       scaled-height
	       start-angle
	       inc-angle
	       color-value)))))))



(def-icp-message-functions paint-arc-or-circle-in-current-scratchpad-raster
			   ((coordinate x1) (coordinate y1)
			    (coordinate x2) (coordinate y2)
			    (coordinate x3) (coordinate y3)
			    (unsigned-integer x-scale)
			    (unsigned-integer y-scale)
			    color-value
			    (boolean circle?)
			    (boolean filled?))
  (case current-scratchpad-raster-type
    (t
     (iterate-over-monochrome-raster-list-if-appropriate (color-value)
       (paint-arc-or-circle-in-current-scratchpad-raster-1
	 x1 y1 x2 y2 x3 y3 x-scale y-scale color-value circle? filled?)))))

;; Note that integer-x is compared to decimal-point-shift-factor rather than 0
;; so that no gaps are left at the end of the circle.

;; 6/21/88:
;;
;; This version is similar to the one in 1.0 but it uses single integers
;; instead of the double integer mechanism.  This greatly simplifies the code
;; and also improves speed.  In cases where the radius is very large (> 4000),
;; bignums can occur on some machines.  Although there will never be a circle
;; with so large a radius in an icon, it is possible to define arcs with very
;; large radii.  Consider limiting this in some reasonable way.  This would be
;; one way to solve the bignum problem.  For now, don't worry about the bignums
;; since they are so rare (do have to wrap with-temporary-bignum form).

;; This can potentially be made alot faster by using type declarations and
;; eliminating some unnecessary floating point operations and function calls.
;; Calculate-center-of- circle should also be fixed not to cons up a list!  Not
;; a priority till we get some large schematics or have to debug it for any
;; reason, however. - 3/24/87 mhd




(defun circle-convert-float-to-integer (float decimal-point-shift-factor)
  (round (*e float (coerce-to-gensym-float decimal-point-shift-factor))))

(defun quadrant-of-point (x y)
  (if (< x 0)
      (if (< y 0) 3 2)
      (if (< y 0) 4 1)))

(defun compute-float-circle-radius (x-center y-center x1 y1)
  (coerce-to-gensym-float
    (sqrt (+ (square (- x1 x-center))
	     (square (- y1 y-center))))))

;; Consider making these be macros.



;;; Clockwise-arc?, given three points, returns a poitive number if the three points
;;; are in clockwise order on the perimeter of a circle, a negative number if they are
;;; in counterclocwise order, and zero if they are colinear. If the arguments are
;;; integers, the value will be an integer. It does not divide, and so cannot encounter
;;; a division by zero.

;;; Note that the left/right convention here is opposite that given in math textbooks
;;; because out screen coordinates have increasing y in the down direction.

(defun clockwise-arc? (x1 y1 x2 y2 x3 y3)
  (- (* (- x2 x1) (- y3 y1))
     (* (- x3 x1) (- y2 y1))))

;; Verify that this can or cannot return a bignum given all integers and so
;; document, and add temporary bignum creation wrappers if needed!!




;;; Calculate-center-of-circle takes three pairs of coordinate points where the
;;; coordinates are floating point numbers.  It returns the x and y coordinates
;;; for the center as its first two values.  If the three points are colinear,
;;; nil is returned.

(defun calculate-center-of-circle (x1 y1 x2 y2 x3 y3)
  (declare (type fixnum x1 y1 x2 y2 x3 y3))
  (with-circle-chords-1
    x1 y1 x2 y2 x3 y3
    (if (= 0 determinant)
	nil
	(let* ((x-center
		 (/ (+ (* c1 b2) (* c2 (- b1)))
		    determinant))
	       (y-center
		 (/ (+ (* c1 (- a2)) (* c2 a1))
		    determinant)))
	  (values x-center y-center)))))




(defun calculate-center-and-radius-of-circle (x1 y1 x2 y2 x3 y3)
  (let* ((fixnum-x-center? nil)
	 (fixnum-y-center? nil)
	 (fixnum-radius? nil))
    (with-temporary-gensym-float-creation calculate-center-and-radius
      (multiple-value-bind (x-center? y-center?)
	  (calculate-center-of-circle x1 y1 x2 y2 x3 y3)
	(if (and x-center? y-center?)
	    (progn
	      (setq fixnum-x-center? (g2-round x-center?))
	      (setq fixnum-y-center? (g2-round y-center?))
	      (setq fixnum-radius? (fixnum-vector-distance
				     (- x1 fixnum-x-center?)
				     (- y1 fixnum-y-center?)))))))
    (values fixnum-x-center? fixnum-y-center? fixnum-radius?)))





;;; The function `compute-arc-bounding-box' takes as input 3 points that form an
;;; arc and returns the values x0, y0, x1, and y1, which are the
;;; upper-left and lower-right points, respectively, of the box that surrounds
;;; the arc.

;;; x1, x2, etc. are all assumed to be in workspace units.

(defun compute-arc-bounding-box (x1 y1 x2 y2 x3 y3)
  (declare (type fixnum x1 y1 x2 y2 x3 y3))
  (let ((min-x (minw x1 x2 x3))
	(max-x (maxw x1 x2 x3))
	(min-y (minw y1 y2 y3))
	(max-y (maxw y1 y2 y3)))
    (with-temporary-bignum-creation
      (let* ((arc-direction			; an integer, conceivably a bignum
	       (g2-round
		 (clockwise-arc? x1 y1 x2 y2 x3 y3))))
	;; If the points are given in counterclockwise order,
	;;   interchange the first and the last. After this,
	;;   assume that they are clockwise or co-linear:
	(unless (= arc-direction 0)		; points are colinear?
	  (when (< arc-direction 0)		; make clockwise
	    (psetq x1 x3 x3 x1)
	    (psetq y1 y3 y3 y1))
	  ;; points are now in clockwise order and not colinear
	  (with-temporary-gensym-float-creation bounding-arc
	    (multiple-value-bind (center-x center-y)
		(calculate-center-of-circle	; won't return nil here
		  x1 y1 x2 y2 x3 y3)
	      (let* ((radius
		       (compute-float-circle-radius
			 center-x center-y x1 y1))
		     (cardinal-point-clipping-margin 1))
		;; For each of the four cardinal points on the perimeter of the circle,
		;; if it is within the drawn arc, check for out of range.
		(when (> (clockwise-arc? x1 y1 center-x (- center-y radius) x3 y3) 0)
		  (setq min-y
			(round (- center-y radius cardinal-point-clipping-margin))))
		(when (> (clockwise-arc? x1 y1 (- center-x radius) center-y x3 y3) 0)
		  (setq min-x
			(round (- center-x radius cardinal-point-clipping-margin))))
		(when (> (clockwise-arc? x1 y1 (+ center-x radius) center-y x3 y3) 0)
		  (setq max-x
			(round (+ center-x radius cardinal-point-clipping-margin))))
		(when (> (clockwise-arc? x1 y1 center-x (+ center-y radius) x3 y3) 0)
		  (setq max-y
			(round (+ center-y radius cardinal-point-clipping-margin))))))))))
    (values min-x min-y max-x max-y)))

;; Consider passing in "points" instead of x's & y's to be consistent with
;; other things. -5oct89, cpm

;; Consider coercing everything to gensym float and using float arithmetic
;; operators.

;; ... based on code from check-if-arc-within-bounds.

;; Not sure about the following; a version of it used to be at top-level.
;; (MHD 4/20/90)
;;
;; ;;; The algorithim is
;; ;;;
;; ;;;   (1) If the arc is really a straight line, then trivially compute the
;; ;;;   bounding box and return that; otherwise go on.
;; ;;;
;; ;;;   (2) If the arc is given in counterclockwise order, interchange the first
;; ;;;   and third point.
;; ;;;
;; ;;;   (3) For each of the four cardinal points of the circle of the arc, if
;; ;;;   that point is on the arc, save that value.
;; ;;;
;; ;;;   (4) Of the original arc points and the cardinal points that are on the
;; ;;;   arc, find the minimum and maximum x and y values.







;;; The function `compute-circle-bounding-box' takes as input 3 points that form an
;;; circle and returns the values x0, y0, x1, and y1, which are the
;;; upper-left and lower-right points, respectively, of the box that surrounds
;;; the circle.

;;; x1, x2, etc. are all assumed to be in workspace units.

(defun compute-circle-bounding-box (x1 y1 x2 y2 x3 y3)
  (let (min-x min-y max-x max-y)
    (with-temporary-gensym-float-creation compute-circle-bounding-box
      (multiple-value-bind (x-center? y-center?)
	  (calculate-center-of-circle x1 y1 x2 y2 x3 y3)
	(cond
	  ((null x-center?)			; points are colinear
	   (setq min-x (minw x1 x2 x3))
	   (setq max-x (maxw x1 x2 x3))
	   (setq min-y (minw y1 y2 y3))
	   (setq max-y (maxw y1 y2 y3)))
	  (t
	   (let ((radius
		   (compute-float-circle-radius x-center? y-center? x1 y1))
		 (cardinal-point-clipping-margin 1))
	     (setq min-x (round (- x-center? radius cardinal-point-clipping-margin))
		   min-y (round (- y-center? radius cardinal-point-clipping-margin))
		   max-x (round (+ x-center? radius cardinal-point-clipping-margin))
		   max-y (round (+ y-center? radius cardinal-point-clipping-margin))))))))
    (values min-x min-y max-x max-y)))





;;;; Miscellaneous Raster Functions



;;; Paint-from-stored-raster-to-current-scratchpad-raster ...

(defun-substitution-macro paint-from-stored-raster-to-current-scratchpad-raster
  (left-edge-in-scratchpad-raster top-edge-in-scratchpad-raster
   right-edge-in-scratchpad-raster bottom-edge-in-scratchpad-raster
   stored-raster
   left-edge-in-stored-raster top-edge-in-stored-raster
   color-value)
  (case current-scratchpad-raster-type
    (x11-pixmap
     (c-x11-copy-bitmap-to-bitmap
       stored-raster current-scratchpad-raster
       left-edge-in-stored-raster top-edge-in-stored-raster
       left-edge-in-scratchpad-raster top-edge-in-scratchpad-raster
       (-r right-edge-in-scratchpad-raster left-edge-in-scratchpad-raster)
       (-r bottom-edge-in-scratchpad-raster top-edge-in-scratchpad-raster)
       color-value))))

;; This is experimental and limited in use -- later it will be fully documented
;; and detailed. (MHD 9/1/89)



;;; Transfer-region-to-smaller-raster is used in
;;; convert-current-scratchpad-raster-to-stored-raster for the optimization of
;;; using smaller rasters for bounded regions.

(defun-void transfer-region-to-smaller-raster
    (left-edge-in-scratchpad-raster
      top-edge-in-scratchpad-raster
      right-edge-in-scratchpad-raster bottom-edge-in-scratchpad-raster
      stored-raster
      left-edge-in-stored-raster top-edge-in-stored-raster
      color-value)
  (paint-from-stored-raster-to-current-scratchpad-raster
    left-edge-in-scratchpad-raster top-edge-in-scratchpad-raster
    right-edge-in-scratchpad-raster bottom-edge-in-scratchpad-raster
    stored-raster
    left-edge-in-stored-raster top-edge-in-stored-raster
    color-value))



;;; The function `clear-stored-raster' writes 0's on stored-raster within the
;;; specified width and height.  [New functionality in 6.0:] It also clears away
;;; the stipple associated with the raster, if any. It assumes it is being
;;; called within the context of on-scrachpad-raster (within the
;;; initialize-scratchpad-raster call).  This function returns stored-raster.

(defun clear-stored-raster (stored-raster raster-type width height)
  ;; There is no difference between scratchpad and stored rasters
  ;;   in any implementation at present.
  (fill-rectangle-on-scratchpad-raster-1
    stored-raster raster-type 0 0 width height 0)
  stored-raster)





;;;; Tiling Patterns


(defvar available-tiling-patterns '())

(defmacro def-tiling-pattern (symbol-for-command-line &body pattern)
  (avoiding-variable-capture (symbol-for-command-line)
    `(progn
       (push '(,symbol-for-command-line ,@pattern) available-tiling-patterns))))


(defun get-tiling-pattern (pattern-name)
   (cadr (assq pattern-name available-tiling-patterns)))



;;; The tiling-pattern `gensym' is the first two lines of
;;;  GENSYM GENSYM GENSYM GENSYM GENSYM GENSYM
;;;  YM GENSYM GENSYM GENSYM GENSYM GENSYM GEN
;;;  GENSYM GENSYM GENSYM GENSYM GENSYM GENSYM
;;;  YM GENSYM GENSYM GENSYM GENSYM GENSYM GEN
;;; It is 32x16 bits in size.

(def-tiling-pattern gensym
    ((0 1 1 1 0 1 1 1 0 1 0 0 1 0 1 1 1 0 1 0 0 1 0 1 0 0 0 1 0 0 0 0)
     (1 0 0 0 0 1 0 0 0 1 1 0 1 0 1 0 0 0 0 1 0 1 0 1 1 0 1 1 0 0 0 0)
     (1 0 1 1 0 1 1 1 0 1 0 1 1 0 0 1 0 0 0 0 1 0 0 1 0 1 0 1 0 0 0 0)
     (1 0 0 1 0 1 0 0 0 1 0 0 1 0 0 0 1 0 0 0 1 0 0 1 0 0 0 1 0 0 0 0)
     (0 1 1 0 0 1 1 1 0 1 0 0 1 0 1 1 1 0 1 1 0 0 0 1 0 0 0 1 0 0 0 0)
     (0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0)
     (0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0)
     (0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0)

     (1 0 1 0 0 1 0 1 0 0 0 1 0 0 0 0 0 1 1 1 0 1 1 1 0 1 0 0 1 0 1 1)
     (0 0 0 1 0 1 0 1 1 0 1 1 0 0 0 0 1 0 0 0 0 1 0 0 0 1 1 0 1 0 1 0)
     (0 0 0 0 1 0 0 1 0 1 0 1 0 0 0 0 1 0 1 1 0 1 1 1 0 1 0 1 1 0 0 1)
     (1 0 0 0 1 0 0 1 0 0 0 1 0 0 0 0 1 0 0 1 0 1 0 0 0 1 0 0 1 0 0 0)
     (1 0 1 1 0 0 0 1 0 0 0 1 0 0 0 0 0 1 1 0 0 1 1 1 0 1 0 0 1 0 1 1)
     (0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0)
     (0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0)
     (0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0)))



(defparameter tiling-pattern-foreground-color 'white)
(defparameter tiling-pattern-background-color 'gray)


(def-structure (tiling-pattern
		 (:constructor
		   make-tiling-pattern-structure
		   (gensym-window-for-tiling-pattern
		    tiling-pattern-width tiling-pattern-height
		    tiling-pattern-rows-with-color-values
		    tiling-pattern-stored-raster?)))

  tiling-pattern-width
  tiling-pattern-height

  (tiling-pattern-rows-with-color-values	; list of same-length lists of
    nil :reclaimer reclaim-graphics-tree)	;   graphics conses
  tiling-pattern-stored-raster?			; non-nil in all cases except
						;   in windows of type ICP
  gensym-window-for-tiling-pattern

  (corresponding-icp-object-map-for-tiling-pattern nil
   :reclaimer reclaim-gensym-list))



(def-icp-object-type tiling-pattern
		     (standard-icp-object-index-space
		       (corresponding-icp-object-map-for-tiling-pattern
			 tiling-pattern))
  (send-icp-make-tiling-pattern
    corresponding-icp-object-index
    (gensym-window-for-tiling-pattern tiling-pattern)
    (tiling-pattern-rows-with-color-values tiling-pattern)))


(def-icp-message-type make-tiling-pattern
		      (corresponding-icp-object-index gensym-window
		       tiling-pattern-rows-with-color-values)

  ;; Note A
  (telewindows-check-version-of-remote-g2 gensym-window)

  (store-corresponding-icp-object
    corresponding-icp-object-index
    (make-and-install-tiling-pattern
      gensym-window				; system-window till 3/6/89!
      tiling-pattern-rows-with-color-values))

  ;; Note that we assume that the gensym-window has been fully
  ;; initialized, i.e. that the color map has been installed.  -pto 27feb89

  (reclaim-graphics-tree tiling-pattern-rows-with-color-values))

;; Note A: This grotesque kludge is here because this is the earliest point in
;; the TW-G2 connection negotiations at which TW knows what version of G2 it
;; has the pleasure of conversing, namely, the icp-window-protocol-version slot
;; of the gensym-window is valid.  -fmw, 10/6/94

;; Tiling-pattern-rows-with-color-values is assumed to be a list of lists of
;; recyclable graphics conses.




(def-icp-value-reader tiling-pattern-rows-with-color-values
  (loop with width = (read-icp-unsigned-integer)
	with height = (read-icp-unsigned-integer)
	as j from 0 below height
	collect
	  (loop as i from 0 below width
		collect (read-icp-unsigned-integer) using graphics-cons)
	  using graphics-cons))

(def-icp-value-writer tiling-pattern-rows-with-color-values
  (write-icp-unsigned-integer
    (length (first tiling-pattern-rows-with-color-values)))
  (write-icp-unsigned-integer (length tiling-pattern-rows-with-color-values))
  (loop as tiling-pattern-row in tiling-pattern-rows-with-color-values
	do (loop as color-value in tiling-pattern-row
		 do (write-icp-unsigned-integer color-value))))

;; A make-tiling-pattern message could use current-window in lieu of its
;; gensym-window argument, if it were certain to occur only during window
;; updating.

;; Consider using recycled conses when creating a tiling pattern rows with
;; color values.






;;; The function `install-tiling-pattern' takes a gensym-window and a tiling
;;; pattern and calls the appropriate native functions to initialize the tiling
;;; pattern.  Here we dictate the foreground and background colors for every
;;; tiling pattern.

(defun-void install-tiling-pattern (gensym-window)
  (case (type-of-gensym-window gensym-window)
    (x11-window
     (let* ((tiling-pattern-or-color
	      (default-pane-background-color-or-tiling-pattern
		  gensym-window)))
       (when (tiling-pattern-p tiling-pattern-or-color)
	 (let* ((current-color-map
		  (color-map-for-window gensym-window))
		(foreground
		  (map-to-color-value tiling-pattern-foreground-color))
		(background
		  (map-to-color-value tiling-pattern-background-color)))

	   ;; Force the colors to be different
	   (when (=f background foreground)
	     (setq foreground (map-to-color-value 'black)
		   background (map-to-color-value 'white)))

	   (c-x11-initialize-tile
	     (native-window? gensym-window)
	     (tiling-pattern-stored-raster? tiling-pattern-or-color)
	     foreground background)))))))



;;; The funtion `make-and-install-tiling-pattern' calls make-tiling-pattern to
;;; make the tiling pattern and then install-tiling-pattern to install it.  It
;;; returns the tiling pattern.  This function should be called when gensym-window
;;; has already been initialized.  If gensym-window is in the process of being
;;; created, make-tiling-pattern should be called first, and then
;;; install-tiling-pattern should be called after

(defun make-and-install-tiling-pattern (gensym-window tiling-pattern-rows)
  (prog1 (make-tiling-pattern gensym-window tiling-pattern-rows)
	 (install-tiling-pattern gensym-window)))





;;; `Make-tiling-pattern' makes a `tiling pattern' suitable for gensym-window
;;; per tiling- pattern-rows.  Tiling-pattern-rows is a list of lists of
;;; bits.  The length of each tiling pattern row should be the same power of
;;; 2, but rows past the first that are not so will be truncated or
;;; cyclically used as necessary.  (None of the conses in tiling-pattern-rows
;;; is incorporated into the new tiling pattern.)  Tiling patterns are used
;;; primarily to fill the non-image portions of a pane, i.e.,
;;; the `pane background'.

(defun make-tiling-pattern (gensym-window tiling-pattern-rows)
  (let* ((tiling-pattern-width (length (first tiling-pattern-rows)))
	 (tiling-pattern-height (length tiling-pattern-rows))
	 (current-color-map (color-map-for-window gensym-window)) ; Special variable!
	 (tiling-pattern-rows-with-color-values
	   (loop as tiling-pattern-row in tiling-pattern-rows
		 collect
		 (loop with i = 0
		       nconc
		       (loop for color-or-color-value in tiling-pattern-row
			     collect (if (integerp color-or-color-value)
					 color-or-color-value
					 (map-to-color-value color-or-color-value))
			       using graphics-cons
			     do (incff i)
			     until (=f i tiling-pattern-width))
		       until (=f i tiling-pattern-width))
		   using graphics-cons))
	 (tiling-pattern-stored-raster?
	   (case (type-of-gensym-window gensym-window)
	     (icp nil)
	     (printer nil)
	     (t
	      (on-scratchpad-raster
		  (gensym-window tiling-pattern-width tiling-pattern-height t)
		(loop as tiling-pattern-row
			 in tiling-pattern-rows-with-color-values
		      as j from 0
		      do
		  (loop as i from 0
			as bit in tiling-pattern-row
			do
		    (if (=f bit 1)
			(setf (local-current-scratchpad-pixel i j) bit)))))))))
    (make-tiling-pattern-structure
      gensym-window tiling-pattern-width tiling-pattern-height
      tiling-pattern-rows-with-color-values
      tiling-pattern-stored-raster?)))

;; Consider using recycled conses when creating a tiling pattern rows with
;; color values.

;; The previous spec for tiling-pattern-rows:
;; Tiling-pattern-rows is a list of lists of colors or color values, each of
;; which describes one row of the pattern.




;;; `Reclaim-default-pane-background-color-or-tiling-pattern' is the slot
;;; reclaimer for the `default-pane-background-color-or-tiling-pattern' pattern
;;; slot in gensym-window structures.  Reclaim-tiling-pattern is called on
;;; color-or- tiling-pattern if it is a tiling-pattern structure.  Otherwise,
;;; value being a color, nothing is done.

(defun reclaim-default-pane-background-color-or-tiling-pattern
       (color-or-tiling-pattern)
  (when (tiling-pattern-p color-or-tiling-pattern)
    (reclaim-tiling-pattern color-or-tiling-pattern)))




;; New per-window solid background color (MHD 11/19/00) and pattern tiling feature -css

;;; The function `get-background-color-or-tiling-pattern-from-command-line'
;;; processes the "-background" command-line option for the local window.

;;; Description of the bucket-brigade used to draw the pane background in the
;;; non-MDI case:

;;; This runs on the client-side: TW reads the tile bitmap, if any, converts it
;;; into a nested list of 1's and 0's, and sends that to G2 via the
;;; `window-parameters-plist'. G2 uses that to creating a tiling-pattern
;;; structure, sends that structure back to TW as an ICP object, via
;;; `make-tiling-pattern', make-tiling-pattern creates a bitmap and draws to it
;;; pixel-by-pixel using the nested list of 1's and 0's, and records it as the
;;; single global tiling pattern via `c-x11-initialize-tile'. Then, whenever G2
;;; needs to draw the tiling pattern, it uses the special ICP message
;;; `copy-from-tiling-pattern-to-current-window', which although it takes a
;;; tiling-pattern argument, ignores it and always draws from the global
;;; pattern.

;;; In the MDI (aka multiwindow) case, TW refreshes the pane background locally,
;;; without involving G2 at all. The call to c-x11-set-mdi-client-background-color, run
;;; on TW, tells the MDI C code what background color to use, or if none, to use
;;; the cached tiling pattern.

(defun get-background-color-for-symbol (color-symbol)
  ;; Record the bg color in C, for the benefit of MDI mode.
  (multiple-value-bind (r? g? b?)
      (and color-symbol (rgb-from-color color-symbol))
    (c-x11-set-mdi-client-background-color (or r? -1) (or g? -1) (or b? -1)))
  color-symbol)

(defun get-background-color-or-tiling-pattern-from-command-line ()
  (let* ((path-or-symbol (getf command-line-arguments 'background))
	 (raster-or-error nil)
	 (tiling-pattern (get-tiling-pattern path-or-symbol)))
    (cond (tiling-pattern
	   (copy-tree-using-gensym-conses tiling-pattern))
	  ((symbolp path-or-symbol)
	   (get-background-color-for-symbol path-or-symbol))
	  ((or (not (stringpw path-or-symbol))
	       (not (gensym-probe-file-for-truth-value path-or-symbol)))
	   (notify-user-at-console "~s is not a color or background pattern file." path-or-symbol)
	   (c-x11-set-mdi-client-background-color -1 -1 -1)
	   nil)
	  ((text-string-p (setq raster-or-error (read-raster path-or-symbol)))
	   (notify-user-at-console "Problem reading background pattern ~s: ~a"
				   path-or-symbol raster-or-error)
	   (reclaim-text-string raster-or-error)
	   (c-x11-set-mdi-client-background-color -1 -1 -1)
	   nil)
	  (t
	   (prog1 (shredded-raster-to-background-tile raster-or-error)
	     (reclaim-shredded-raster raster-or-error))))))

;; TODO: Full color background tiling patterns.


(defun get-background-color-or-tiling-pattern ()
  (or
    ;; New per-window background color (MHD 11/19/00) and pattern tiling feature -css
    (get-background-color-or-tiling-pattern-from-command-line)
    (if (and (eq current-system-name 'telewindows) (telewindows-mdi-frame-p))
	'dark-gray)			; TODO: Ought to get COLOR_APPWORKSPACE
    'light-gray))


(def-gensym-c-function c-x11-set-mdi-client-background-color
    (:void "g2ext_set_mdi_client_background_color")
  ((:fixnum-int red)
   (:fixnum-int green)
   (:fixnum-int blue)))

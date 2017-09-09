;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module WINDOWS3 -- Operations on the Gensym Window System

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Lowell B.  Hawkinson, Brian Matthews, Mark David, Andreas Hofmann,
;;; and Ong, Peng Tsin








;;;; Forward References in WINDOWS3




(declare-forward-references
  (make-rendering-structure                function icons)
  (reclaim-icon-rendering-and-remove-from-icon-description-if-g2 function)) ; TELESTUBS



;;; This macro defines a function 'copy-tree-including-leaves-using-<root-name>-conses
;;; Use this function, instead of the copy tree function defined by defconser if you
;;; need to copy leaves within the tree, ie the tree includes strings and/or floats.

(defmacro def-copy-tree-including-leaves-using-x-conses (root-name)
  (let ((copy-tree-including-leaves-using-x-conses
	  (intern (format nil "COPY-TREE-INCLUDING-LEAVES-USING-~a-CONSES"
			  root-name)))
	(x-cons-function  (intern (format nil "~a-CONS" root-name)))) 
    `(defun-simple ,copy-tree-including-leaves-using-x-conses (tree?)
       (cond ((text-string-p tree?) (copy-text-string tree?))
	     ((managed-float-p tree?)
	      (copy-managed-float tree?))
	     ((not (consp tree?))  tree?)
	     (t
	      (loop with new-list
		      = (,x-cons-function
			   (,copy-tree-including-leaves-using-x-conses (car tree?))
			   (cdr tree?))
		    with last-new-cons = new-list
		    with current-copy-position = (cdr tree?)
		    until (atom current-copy-position)
		    do (setf (cdr last-new-cons)
			     (,x-cons-function
				(,copy-tree-including-leaves-using-x-conses
				   (car current-copy-position))
				(cdr current-copy-position)))
		       (setf last-new-cons (cdr last-new-cons))
		       (setf current-copy-position
			     (cdr current-copy-position))
		    finally (return new-list)))))))

(defmacro def-reclaim-tree-including-leaves-for-x-conses (root-name)
  (let ((reclaim-tree-including-leaves-for-x-conses
	  (intern (format nil "RECLAIM-TREE-INCLUDING-LEAVES-FOR-~a-CONSES"
			  root-name)))
	(x-reclaim-cons (intern (format nil "RECLAIM-~a-CONS" root-name))))
    `(defun-simple ,reclaim-tree-including-leaves-for-x-conses (tree?)
       (cond ((text-string-p tree?) (reclaim-text-string tree?))
	     ((managed-float-p tree?)
	      (reclaim-managed-float tree?))
	     ((not (consp tree?))  nil)
	     (t
	      (,reclaim-tree-including-leaves-for-x-conses (car tree?))
	      (,reclaim-tree-including-leaves-for-x-conses (cdr tree?))
	      (,x-reclaim-cons tree?))))))

(def-copy-tree-including-leaves-using-x-conses gensym)
(def-reclaim-tree-including-leaves-for-x-conses gensym)



;;;; Operations on Current Windows



;;; Operations on a window may only be done within the body of an `on-window',
;;; which establishes the `current window'.  These operations may be required,
;;; in an implementation, to work for several distinct types of window.

;;; Most of the operations on device memories are `graphic element primitives'
;;; that implement `graphic element operations'.  The graphic element
;;; operations are, at present: paint-solid-rectangle, add-solid-rectangle,
;;; add-icon-rendering, add-upward-sloping-line, add-downward-sloping-line,
;;; and add-line-of-text.  See module PANES for further details.



;; If, in an implementation, support is needed for identical windows on two or
;; more screens, that should be handled below by a "replicating" window.



	

;;; `Paint-solid-rectangle-in-current-window' paints an arbitrary rectangular
;;; area of current-window, as specified by the edge arguments.  The color of
;;; the painted area will be color-value.  The edges are assumed to be open
;;; on the right and bottom.  That is, the number of pixels painted is
;;; (right-left) * (bottom-top).

(def-icp-message-functions paint-solid-rectangle-in-current-window
    ((coordinate clipped-left-edge)
     (coordinate clipped-top-edge)
     (coordinate clipped-right-edge)
     (coordinate clipped-bottom-edge)
     color-value)
  (case type-of-current-window
    (x11-window
     (c-x11-draw-rectangle
       current-native-window? clipped-left-edge clipped-top-edge
       (-r clipped-right-edge clipped-left-edge)
       (-r clipped-bottom-edge clipped-top-edge)
       color-value x11-copy))))



;;; `Add-solid-rectangle-to-current-window' adds color-difference to an
;;; arbitrary rectangular area of current-window, as specified by the edge
;;; arguments. The edges are assumed to be open on the right and bottom.  That
;;; is, the number of pixels painted is (right-left) * (bottom-top).  The
;;; subtract-instead? argument is ignored.

(def-icp-message-functions add-solid-rectangle-to-current-window
    (subtract-instead?
      (coordinate clipped-left-edge)
      (coordinate clipped-top-edge)
      (coordinate clipped-right-edge)
      (coordinate clipped-bottom-edge)
      color-difference)
  (case type-of-current-window
    (x11-window
     (unless (color-difference-is-transparent-p color-difference) ; Used to be zerop.
       (c-x11-draw-rectangle
	 current-native-window?
	 clipped-left-edge clipped-top-edge
	 (-r clipped-right-edge clipped-left-edge)
	 (-r clipped-bottom-edge clipped-top-edge)
	 (infer-color-value-from-color-difference-and-transfer-mode color-difference)
	 (current-transfer-mode-for-x11-windows))))))

;; Decide whether distinguishing the single-pixel height and width cases
;; is a worthwhile optimization in each implementation on a case-by-case
;; basis.



#+development
(def-system-variable debugging-raster-tiling? windows3 nil)

(def-substitution-macro add-from-raster-tiles-to-current-window
    (subtract-instead?
      clipped-left-edge clipped-top-edge
      clipped-right-edge clipped-bottom-edge
      color-difference stored-raster
      left-edge-in-stored-raster-arg top-edge-in-stored-raster-arg)
  (if (tiled-raster-p stored-raster)
      (let* ((left-edge-in-stored-raster left-edge-in-stored-raster-arg)
	     (top-edge-in-stored-raster top-edge-in-stored-raster-arg)
	     (width-of-area (-r clipped-right-edge clipped-left-edge))
	     (height-of-area (-r clipped-bottom-edge clipped-top-edge))
	     (raster-x-origin (-r clipped-left-edge left-edge-in-stored-raster))
	     (raster-y-origin (-r clipped-top-edge top-edge-in-stored-raster)))
	(iterate-over-tiles-to-be-painted
	    (left-edge-in-stored-raster top-edge-in-stored-raster
					(+r left-edge-in-stored-raster width-of-area)  ; right edge in stored raster
					(+r top-edge-in-stored-raster height-of-area)  ; bottom edge in stored raster
					stored-raster)

	  (let ((tile-x-position (*r j tile-size))
		(tile-y-position (*r i tile-size)))
	    (add-from-stored-raster-to-current-window
	      subtract-instead?
	      (maxr clipped-left-edge
		    (+r raster-x-origin tile-x-position))
	      (maxr clipped-top-edge
		    (+r raster-y-origin tile-y-position))
	      (minr clipped-right-edge 
		    (+r raster-x-origin (+r tile-x-position tile-size)))
	      (minr clipped-bottom-edge
		    (+r raster-y-origin (+r tile-y-position tile-size)))
	      color-difference tile-to-paint
	      (maxr 0 (-r left-edge-in-stored-raster tile-x-position))
	      (maxr 0 (-r top-edge-in-stored-raster tile-y-position))))))
      (add-from-stored-raster-to-current-window
	subtract-instead?
	clipped-left-edge clipped-top-edge
	clipped-right-edge clipped-bottom-edge
	color-difference stored-raster
	left-edge-in-stored-raster-arg top-edge-in-stored-raster-arg)))

;; This is used only by add-from-region-bounds-and-raster.


;;; `Add-from-stored-raster-to-current-window' adds to the area of current-window
;;; bounded by clipped-left-edge, clipped-top-edge, clipped-right-edge, and
;;; clipped-bottom-edge, color differences based on color-difference? and the
;;; congruent (rectangular) area of stored-raster bounded by
;;; left-edge-in-stored-raster and top-edge-in-stored-raster, where the top
;;; left corner pixel of stored-raster is pixel (0,0).  Stored-raster must be
;;; a monochrome raster, wherein pixel value 1 indicates the pixels to which
;;; color-difference is to be added.  (Note that when subtract-instead? is non-
;;; nil, add-from-stored-raster-to-current-window subtracts instead of adds.)
;;;   Note that `current-background-color-value' must be correctly bound here,
;;; so that we can infer the paint-mode color value from the color difference.

(defun-substitution-macro add-from-stored-raster-to-current-window
    (subtract-instead?
      clipped-left-edge clipped-top-edge
      clipped-right-edge clipped-bottom-edge
      color-difference stored-raster
      left-edge-in-stored-raster top-edge-in-stored-raster)
  (pretend-to-use-value subtract-instead?)		    ; not used yet -- gag compiler!
  ;;(declare (ignore subtract-instead?)) ; can't use this if a macro (MHD)

  (unless (color-difference-is-transparent-p color-difference)
    (case type-of-current-window
      (x11-window
       (c-x11-copy-pixmap
	 stored-raster current-native-window?
	 left-edge-in-stored-raster top-edge-in-stored-raster
	 clipped-left-edge clipped-top-edge
	 (-r clipped-right-edge clipped-left-edge)
	 (-r clipped-bottom-edge clipped-top-edge)
	 (infer-color-value-from-color-difference-and-transfer-mode color-difference)
	 0
	 (current-transfer-mode-for-bitmaps-in-x11-windows))))))

;; Despite the name of this routine, it is used to paint as well as xor the raster.

;; Consider pulling overhead of the case statement to a higher level, since this
;; has to be done once per character in a string in the add-from-line-of-text-to-
;; current-window ICP message and once per "layer" in the add-from-stored-raster-
;; to-current-window ICP message!  Also see if overhead of foreign function calling
;; in X windows versions can be reduced!  (MHD 5/8/89)

;; Fix subtract-instead? to be subtract-instead, and the documentation, since
;; polychrome rasters will not be supported, at least in the way documented!
;; (MHD 5/8/89)

;; Changed back to a macro, but this time using defun-substitution-macro; it
;; had been changed to a defun-void in 3.0, but there is suspicion that this
;; caused a loss of performance.

;; Used only by add-from-raster-tiles-to-current-window and
;; add-from-line-of-text-to-current-window-1.





;;; The icp-message-functions `add-upward-sloping-line-to-current-window' 
;;; assumes that clipped-left-edge < clipped-right-edge and that
;;; clipped-top < clipped-right-edge.

(def-icp-message-functions add-upward-sloping-line-to-current-window
    (subtract-instead?
      (coordinate clipped-left-edge)
      (coordinate clipped-top-edge)
      (coordinate clipped-right-edge)
      (coordinate clipped-bottom-edge)
      color-difference
      (coordinate left-end-x) (coordinate right-end-y) ; [**] Notice changed arg order!!
      (coordinate right-end-x) (coordinate left-end-y))
  (case type-of-current-window
    (x11-window
     (unless (color-difference-is-transparent-p color-difference)
       (setq right-end-x (-r right-end-x 1) ; [*]
	     left-end-y (-r left-end-y 1))
       (when (and (<r clipped-left-edge clipped-right-edge)
		  (<r clipped-top-edge clipped-bottom-edge))
	 (c-x11-draw-line-with-clipping
	   current-native-window?
	   left-end-x left-end-y right-end-x right-end-y
	   clipped-left-edge clipped-top-edge
	   clipped-right-edge clipped-bottom-edge
	   (infer-color-value-from-color-difference-and-transfer-mode color-difference)
	   (current-transfer-mode-for-x11-windows)))))))

;; This is used only for drawing diagonal connections and connection
;; fins. Notice the completely bogus adjustment to the coordinates at [*].  We
;; can't change this routine, since old G2's will be expecting it to draw the
;; way it does, but we can add a new ICP message that simply draws a line, with
;; no funny business.  -fmw, 5/22/02


;;; The icp-message-functions `add-downward-sloping-line-to-current-window'
;;; assumes that clipped-left-edge < clipped-right-edge and that clipped-top <
;;; clipped-right-edge.

(def-icp-message-functions add-downward-sloping-line-to-current-window
    (subtract-instead?
      (coordinate clipped-left-edge)
      (coordinate clipped-top-edge)
      (coordinate clipped-right-edge)
      (coordinate clipped-bottom-edge)
      color-difference
      (coordinate left-end-x) (coordinate left-end-y)
      (coordinate right-end-x) (coordinate right-end-y))
  (case type-of-current-window
    (x11-window
     (unless (color-difference-is-transparent-p color-difference)
       (setq right-end-x (-r right-end-x 1)) ; [*]
       (setq right-end-y (-r right-end-y 1))
       (when (and (<r clipped-left-edge clipped-right-edge)
		  (<r clipped-top-edge clipped-bottom-edge))
	 (c-x11-draw-line-with-clipping
	   current-native-window?
	   left-end-x left-end-y right-end-x right-end-y
	   clipped-left-edge clipped-top-edge
	   clipped-right-edge clipped-bottom-edge
	   (infer-color-value-from-color-difference-and-transfer-mode color-difference)
	   (current-transfer-mode-for-x11-windows)))))))

;; Note that the right end coordinates are not those of the right end point.

;; Try to define these as hardcoded machine primitives.



;;;; Patterned Lines (G2 6.2)







;; Since Chestnut does not supply us with a :32-bit-unsigned-array type, (or
;; :32-bit-signed-array, for that matter, which is what we really want), we have
;; to pack vertices into an unsigned-16.  We assume little-endian, which is the
;; case on all of our Win32 platforms (w98, intelnt, and alphant).

;; The resulting array can be passed directly to Polyline, which is a big win,
;; worth the endianess hassle.

;; Since X only supports 16-bit coordinates, no special word order is needed,
;; but we do lose when the coordinates exceed 16 bits.  See HQ-4308342. -fmw,
;; 6/7/02

(defmacro with-point-vector ((point-vector npoints vertices) &body body)
  (avoiding-variable-capture (vertices &aux length win32 nshorts)
    `(let* ((,length (length ,vertices))
	    (,npoints (ash ,length -1))
	    (,win32 (windows-platform-p))
	    (,nshorts (if ,win32 (ash ,length 1) ,length))
	    (,point-vector (allocate-byte-vector-16 ,nshorts)))
       (cond (,win32
	      (loop with i fixnum = 0
		    for xy in ,vertices
		    doing
		(setf (byte-vector-16-aref point-vector i) (logandf 65535 xy))
		(incff i)
		(setf (byte-vector-16-aref point-vector i) (logandf 65535 (ash xy -16)))
		(incff i)))
	     (t
	      (loop with i fixnum = 0
		    for xy in ,vertices
		    doing
		(setf (byte-vector-16-aref point-vector i) (logandf 65535 xy))
		(incff i))))
       (progn ,@body)
       (reclaim-byte-vector-16 ,point-vector))))



;;; The function `encode-poly-line-style' converts a line style and pattern to
;;; the encoded value we send over the wire, and supply to the C drawing
;;; routines.

(defun encode-poly-line-style (line-style line-pattern)
  (logiorf (case line-style
	     (miter   (logiorf ps-endcap-flat ps-join-miter))
	     (rounded (logiorf ps-endcap-flat ps-join-round))
	     (t       (logiorf ps-endcap-round ps-join-round)))
	   (cond ((null line-pattern)
		  ps-solid)
		 ((consp line-pattern)
		  ps-userstyle)
		 ((not (symbolp line-pattern))
		  (dwarn "Unknown line pattern ~s" line-pattern)
		  ps-solid)
		 (t
		  (case line-pattern
		    (solid ps-solid)
		    (dash ps-dash)
		    (dot ps-dot)
		    (dash-dot ps-dashdot)
		    (dash-dot-dot ps-dashdotdot)
		    (t
		     (dwarn "Unknown line pattern ~s" line-pattern)
		     ps-solid))))))

;;; The function `line-dashes-for-pattern' ensure we pass NIL when line-pattern
;;; is one of the predefined pattern symbols

(defun encode-poly-line-pattern (line-pattern)
  (when (consp line-pattern)
    line-pattern))


;;; The icp-message-functions `add-wide-polyline-to-current-window' is used to
;;; draw wide diagonal and patterned connections.  Note that Win95/98/ME is
;;; limited to 1360 points per polyline, if width>1.

(def-icp-message-functions add-wide-polyline-to-current-window
    ((coordinate clipped-left-edge)	; Clipping rectangle.
     (coordinate clipped-top-edge)
     (coordinate clipped-right-edge)
     (coordinate clipped-bottom-edge)
     (unsigned-integer color-difference)
     (unsigned-integer width)
     (unsigned-integer style)		; PS-SOLID, maybe other style bits.
     (list-of-unsigned-integers dashes) ; dot/dash pattern.
     (list-of-integers vertices))	; Alternating x and y.
  (case type-of-current-window
    (x11-window
     ;; Shouldn't these tests be done on the G2 side?
     (unless (color-difference-is-transparent-p color-difference)
       (draw-wide-polyline-on-window
	 current-native-window?
	 clipped-left-edge clipped-top-edge clipped-right-edge clipped-bottom-edge
	 (infer-color-value-from-color-difference-and-transfer-mode color-difference)
	 (current-transfer-mode-for-x11-windows)
	 width style dashes vertices)))))

(defun draw-wide-polyline-on-window (native-window clipped-left-edge clipped-top-edge
						   clipped-right-edge clipped-bottom-edge
						   color transfer-mode
						   width style dashes vertices)
  (when (and (<r clipped-left-edge clipped-right-edge)
	     (<r clipped-top-edge clipped-bottom-edge))

    (let* ((ndashes (length dashes))
	   (dash-vector (allocate-byte-vector-16 ndashes)))
      (loop for dash in dashes
	    as index fixnum from 0
	    do (setf (byte-vector-16-aref dash-vector index) (logandf 65535 dash)))

      (with-point-vector (point-vector npoints vertices)
	(c-x11-draw-wide-polyline
	  native-window
	  point-vector npoints
	  clipped-left-edge clipped-top-edge
	  clipped-right-edge clipped-bottom-edge
	  color
	  width style
	  dash-vector ndashes
	  transfer-mode))
      (reclaim-byte-vector-16 dash-vector))))


;; The copy from list to array is annoying, especially since it is redone for
;; each subrectangle in do-projection-through-region.  Also, the entire list of
;; vertices is shipped over ICP for each subrectangle.  Maybe this is not
;; actually a performance issue, but ought to be looked into. -fmw, 2/6/02

;; Moreover, the C code for Win32 does another copy, to get the points into
;; 32-bit words.  So someday we should fill up a byte-vector-32 here, since
;; Win32 is our most important port.

;; Perhaps do-projection-through-region should happen on the far side: we send
;; over a list of only the clipping rectangles we touch.  That way, we will get
;; the advantage of clipping on the G2-side, but send the drawing operation over
;; only once.


;;; `Copy-from-tiling-pattern-to-current-window' fills, from tiling-pattern, the
;;; area of current-window bounded by left-edge, top-edge, right-edge, and
;;; bottom-edge.  Tiling- pattern is treated as a "repeat", that is, a pattern
;;; that is to be replicated in both dimensions.  The tiling pattern, when
;;; copied, is aligned so that it will be in phase with an instance of the
;;; pattern in the top-left corner of raster.

;;; This operation should not be implemented if it cannot be efficiently
;;; implemented, in which case tiling patterns cannot be used for pane
;;; backgrounds.

(def-icp-message-functions copy-from-tiling-pattern-to-current-window
			   ((coordinate left-edge) (coordinate top-edge)
			    (coordinate right-edge) (coordinate bottom-edge)
			    tiling-pattern)
  (case type-of-current-window
    (x11-window
     ;; Prior to 3.0, this just drew a gray rectangle in some cases here.
     ;; It is no longer practical to support that as a "feature", at least not
     ;; here; it was really intended as a bug fix.  (MHD 6/5/91)
     (c-x11-draw-tiling-pattern
       current-native-window? 
       ;; (tiling-pattern-stored-raster? tiling-pattern) stored globally in C.
       left-edge top-edge
       (-r right-edge left-edge) (-r bottom-edge top-edge)))))


;;;; New Drawing Primitives (8.1b0)


(defun get-color-value-1 (color-difference)
  (if (=f color-difference transparent-color-value)
      transparent-color-value
      (infer-color-value-from-color-difference-and-transfer-mode color-difference)))

(defun draw-polygon-on-current-window
    (clip-left clip-top clip-right clip-bottom 
	       line-color-difference line-width
	       fill-color-difference fill-pattern
	       vertices)
  (when (and (<r clip-left clip-right)	; Surely this is redundant.
	     (<r clip-top clip-bottom)
	     (or (not (color-difference-is-transparent-p line-color-difference))
		 (not (color-difference-is-transparent-p fill-color-difference))))
    (add-polygon-to-current-window	; ICP/printer dispatch
      clip-left clip-top clip-right clip-bottom 
      line-color-difference line-width
      fill-color-difference fill-pattern
      vertices)))

(def-icp-message-functions add-polygon-to-current-window
    ((coordinate clipped-left-edge)	; Clipping rectangle.
     (coordinate clipped-top-edge)
     (coordinate clipped-right-edge)
     (coordinate clipped-bottom-edge)
     (unsigned-integer line-color-difference)
     (unsigned-integer line-width)
     (unsigned-integer fill-color-difference)
     (unsigned-integer fill-pattern)
     (list-of-integers vertices))	; Alternating x and y.
  (case type-of-current-window
    (x11-window
     (with-point-vector (point-vector npoints vertices)
       (c-x11-draw-polygon
	 current-native-window?
	 clipped-left-edge clipped-top-edge clipped-right-edge clipped-bottom-edge
	 (get-color-value-1 line-color-difference)
	 line-width
	 (get-color-value-1 fill-color-difference)
	 fill-pattern
	 (current-transfer-mode-for-x11-windows)
	 point-vector npoints)))))


(defun draw-ellipse-on-current-window
    (clip-left clip-top clip-right clip-bottom 
	       line-color-difference line-width
	       fill-color-difference fill-pattern
	       x1 y1 x2 y2)
  (when (and (<r clip-left clip-right)	; Surely this is redundant.
	     (<r clip-top clip-bottom)
	     (or (not (color-difference-is-transparent-p line-color-difference))
		 (not (color-difference-is-transparent-p fill-color-difference))))
    (add-ellipse-to-current-window	; ICP/printer dispatch
      clip-left clip-top clip-right clip-bottom
      line-color-difference
      line-width
      fill-color-difference
      fill-pattern
      x1 y1 x2 y2)))

(def-icp-message-functions add-ellipse-to-current-window
    ((coordinate clipped-left-edge)	; Clipping rectangle.
     (coordinate clipped-top-edge)
     (coordinate clipped-right-edge)
     (coordinate clipped-bottom-edge)
     (unsigned-integer line-color-difference)
     (unsigned-integer line-width)
     (unsigned-integer fill-color-difference)
     (unsigned-integer fill-pattern)
     (coordinate x1) (coordinate y1)
     (coordinate x2) (coordinate y2))
  (case type-of-current-window
    (x11-window
     (c-x11-draw-ellipse
       current-native-window?
       clipped-left-edge clipped-top-edge clipped-right-edge clipped-bottom-edge
       (get-color-value-1 line-color-difference)
       line-width
       (get-color-value-1 fill-color-difference)
       fill-pattern
       (current-transfer-mode-for-x11-windows)
       x1 y1 x2 y2))))




;;;; Scrolling Portions of Window


;;; `Scroll-rectangle-in-current-window' is available when
;;; icp-window-protocol-supports-scrolling or better is in use.  It moves a
;;; rectangle from one portion of the current-window to another.  If portions of
;;; the source are obscured, say by other workstation windows and the
;;; corresponding portion of the destination is not obscured as a side effect
;;; this call will generate expose events for those portions of the destination.

;;; The portions of the source that don't overlap the destination should be
;;; queued for refresh by the caller.

;;; `Scroll-region-of-current-window' is the prefered interface to this operation.

(def-icp-message-functions scroll-rectangle-in-current-window
			   ((coordinate source-left) (coordinate source-top)
			    (unsigned-integer width) (unsigned-integer height)
			    (coordinate destination-left) (coordinate destination-top))
  (case type-of-current-window
    (x11-window
     ;; Prior to 3.0, this just drew a gray rectangle in some cases here.
     ;; It is no longer practical to support that as a "feature", at least not
     ;; here; it was really intended as a bug fix.  (MHD 6/5/91)
     (c-x11-scroll-rectangle
       current-native-window?
       source-left source-top
       width height
       destination-left destination-top))))











;;;; Region Bounds and Rasters for Icons



;;; A region-bounds-and-raster structure contains the raster for a region of an
;;; icon, and also information about the bounds of the region.  The
;;; rendering-structure?  slot of an icon-rendering contains a list of such
;;; structures.

(def-structure region-bounds-and-raster
  x-offset-for-stored-raster?
  y-offset-for-stored-raster?
  x-max-for-stored-raster?
  y-max-for-stored-raster?
  raster-for-region)


#+development
(def-development-printer print-region-bounds-and-raster
    (raster &optional (stream *standard-output*))
  (when (region-bounds-and-raster-p raster)
    (printing-random-object (raster stream)
      (let ((size (tile-size (raster-for-region raster))))
	(format stream "REGION-BOUNDS-AND-RASTER ~dx~d"
		size size)))
    raster))



;;; `Make-region-raster-for-icon' is used by make-rendering-structure, for the
;;; non-telewindows case, and by the handler for the icp message type
;;; begin-making-icon-rendering, for the telewindows case, to make
;;; region-bounds-and-raster structures for each region of an icon.  These are
;;; collected into a list and put into the rendering-structure?  slot of an
;;; icon-rendering.

(defmacro make-region-raster-for-icon
	  ((gensym-window-in-non-icp-case?
	    minimum-width-for-scratchpad-raster
	    minimum-height-for-scratchpad-raster
	    x-offset-for-stored-raster? y-offset-for-stored-raster?
	    x-max-for-stored-raster? y-max-for-stored-raster?)
	   &body raster-painting-body)
  (let ((value-of-gensym-window? (gensym))
	(value-of-x-offset-for-stored-raster? (gensym))
	(value-of-y-offset-for-stored-raster? (gensym))
	(value-of-x-max-for-stored-raster? (gensym))
	(value-of-y-max-for-stored-raster? (gensym)))
    `(let* ((,value-of-gensym-window? ,gensym-window-in-non-icp-case?)
	    (scratchpad-raster-type
	      (scratchpad-raster-type-for-window ,value-of-gensym-window?)))
       (case scratchpad-raster-type
	 (x11-pixmap
	  (let* ((,value-of-x-offset-for-stored-raster? ,x-offset-for-stored-raster?)
		 (,value-of-y-offset-for-stored-raster? ,y-offset-for-stored-raster?)
		 (,value-of-x-max-for-stored-raster? ,x-max-for-stored-raster?)
		 (,value-of-y-max-for-stored-raster? ,y-max-for-stored-raster?)
		 (new-region-bounds-and-raster (make-region-bounds-and-raster))
		 (new-stored-raster
		   (on-scratchpad-raster
		     (,gensym-window-in-non-icp-case?
		      ,minimum-width-for-scratchpad-raster
		      ,minimum-height-for-scratchpad-raster
		      nil
		      ,value-of-x-offset-for-stored-raster? 
		      ,value-of-y-offset-for-stored-raster?
		      ,value-of-x-max-for-stored-raster? 
		      ,value-of-y-max-for-stored-raster? t)
		     ,@raster-painting-body)))
	    (setf (x-offset-for-stored-raster? new-region-bounds-and-raster)
		  ,value-of-x-offset-for-stored-raster?
		  (y-offset-for-stored-raster? new-region-bounds-and-raster)
		  ,value-of-y-offset-for-stored-raster?
		  (x-max-for-stored-raster? new-region-bounds-and-raster)
		  ,value-of-x-max-for-stored-raster?
		  (y-max-for-stored-raster? new-region-bounds-and-raster)
		  ,value-of-y-max-for-stored-raster?
		  (raster-for-region new-region-bounds-and-raster)
		  new-stored-raster)
	    new-region-bounds-and-raster))
	 (t
	  (let ((new-region-bounds-and-raster (make-region-bounds-and-raster))
		(new-stored-raster
		  (on-scratchpad-raster
		    (,gensym-window-in-non-icp-case?
		     ,minimum-width-for-scratchpad-raster
		     ,minimum-height-for-scratchpad-raster
		     nil
		     nil nil nil nil)
		     ,@raster-painting-body)))
	    (setf (raster-for-region new-region-bounds-and-raster)
		  new-stored-raster)
	    new-region-bounds-and-raster))))))

;; The region raster optimization is not used if not using x-windows or tv-windows
;; due to current limitations in paint-from-stored-raster-to-current-scratchpad-raster
;; (see notes for this).  When these limitations are lifted, always do optimization.





;;;; Icon Renderings



;;; An `icon rendering' represents an icon drawn in a particular manner,
;;; specifically, at a particular x scale, y scale, reflection/rotation,
;;; and a particular computed-values-plist.


;;; A `rendering structure' is a list of n stored rasters, where n is given by the
;;; number-of-rendering-structure-elements slot and n > 0.  The slot
;;; rendering-structure?  starts out as nil and may be filled in with a rendering
;;; structure as needed.  The list is made up of gensym conses.

;;; In the case of TELEWINDOWS, there is a one to one relation between an icon
;;; rendering in a G2 process and corresponding icon renderings in the TELEWINDOWS
;;; process.  This is illustrated in the following diagram of windows and
;;; renderings.


;;;   G2                     TELEWINDOW 1             TELEWINDOW 2        ...

;;;   gensym-window-1        gensym-window-4          gensym-window-5
;;;   (native)               (native)                 (native)
 
;;;   gensym-window-2
;;;   (ICP for
;;;    TELEWINDOW 1)

;;;   gensym-window-3
;;;   (ICP for
;;;    TELEWINDOW 2)

;;;   icon-rendering-1                         
;;;   icon-rendering-2       icon-rendering-2-1
;;;   icon-rendering-3                                icon-rendering-3-1


;;; When any icon rendering is decached,
;;; delete-icon-rendering-and-reclaim-icp-index calls
;;; reclaim-icp-object-map-for-icon-rendering (defined by def-icp-object-type) to
;;; reclaim the corresponding icon rendering as well.  Note that decaching is
;;; handled completely in the G2 process.  No separate decaching is done in the
;;; TELEWINDOW processes.  Thus, any TELEWINDOW icon-rendering always has a
;;; corresponding icon rendering in the G2 process.

;;; Because of the one to one relation, the
;;; corresponding-icp-object-map-for-icon-rendering slots of icon renderings in
;;; the G2 process should never have more than one icp-port - index entry.

;;; As mentioned above, icon renderings are window specific.  The
;;; window-for-icon-rendering slot is used to ensure this.  This slot is also used
;;; for reclamation of rasters for icon renderings (since rasters are
;;; window-specific as well).  Since rasters are only allocated for native windows
;;; (never for ICP windows) the window-for-icon-rendering slot can always be used
;;; to reclaim the rasters.

;; Note that because icon renderings are window-specific and because decaching of 
;; icon renderings is window-specific as well (see get-structure-to-decache),
;; rasters will be decached only when necessary.  Consider making decaching
;; non-window-specific!  Would have to modify cost functions and also
;; reclaim-icp-object-map-for-icon-rendering since icp port for rendering being
;; decached may not be current-icp-port.

;; It would be possible (although very complicated) to have separate
;; decaching mechanisms for the G2 and TELEWINDOWS processes.  Currently,
;; there is absolutely no reason to do this however, 

;; See "Rendering Decaching Test Functions" in CONTROLS for a set of test
;; functions for checking decaching of icon (and graph) renderings.




(def-structure (icon-rendering
		 (:constructor
		   make-icon-rendering-internal
		   (line-drawing-description-for-rendering?
		     computed-values-plist
		     x-scale-of-rendering y-scale-of-rendering
		     reflection-and-rotation-of-rendering
		     width-of-rendered-icon
		     height-of-rendered-icon
		     width-of-rendering-structure
		     height-of-rendering-structure
		     number-of-rendering-structure-elements
		     corresponding-icon-description?
		     window-for-icon-rendering
		     region-extrema-for-rendering?
		     array-of-bitmaps-used
		     total-number-of-bitmaps
		     memory-used-by-bitmaps))
		 (:include lru-element)
		 #+development (:print-function print-icon-rendering))
  x-scale-of-rendering
  y-scale-of-rendering
  
  reflection-and-rotation-of-rendering		; nil => normal

  (corresponding-icp-object-map-for-icon-rendering nil)

  (rendering-structure? nil)			; nil => none yet (if ever)

  line-drawing-description-for-rendering?	; nil => corresponding 
						;   object in ICP server

  computed-values-plist                         ; for power icons
  
  width-of-rendering-structure			; one more than scaled width
						;   and height,
  height-of-rendering-structure			;   appropriately rotated
						;   and reflected

  number-of-rendering-structure-elements

  width-of-rendered-icon			; prior to scaling, rotation,
						;   and reflection
  height-of-rendered-icon

  ; (scaled-x-offset-for-fine-positioning-of-icon? nil)
  ; (scaled-y-offset-for-fine-positioning-of-icon? nil)

  corresponding-icon-description?		; always nil for Telewindows

  (number-of-times-used-in-cache? 0)

  window-for-icon-rendering

  region-extrema-for-rendering?

  array-of-bitmaps-used

  total-number-of-bitmaps

  memory-used-by-bitmaps
  )


#+development
(defun print-icon-rendering (rendering &optional (stream *standard-output*) depth)
  (declare (ignore depth))
  (printing-random-object (rendering stream)
    (let* ((x-scale (x-scale-of-rendering rendering))
	   (y-scale (y-scale-of-rendering rendering))
	   (rotation (reflection-and-rotation-of-rendering rendering))
	   (line-drawing (line-drawing-description-for-rendering? rendering))
	   (name? (and line-drawing
		       (consp (car line-drawing))
		       (memq (caar line-drawing) '(image))
		       (cadar line-drawing))))
      (cond ((and (numberp x-scale) (numberp y-scale))
	     (format stream "ICON-RENDERING ~@[~a ~]~a ~@[~a ~]~d"
		     name?
		     (if (equal x-scale y-scale)
			 (format nil "~d%" (round (* 100 x-scale) (normalized-scale)))
			 (format nil "~dx~d%"
				 (round (* 100 x-scale) (normalized-scale))
				 (round (* 100 y-scale) (normalized-scale))))
		     rotation
		     (number-of-times-used-in-cache? rendering)))
	    (t
	     (format stream "ICON-RENDERING ~@[~a ~] ~d"
		     name?
		     (number-of-times-used-in-cache? rendering))))))
  rendering)

;; Make-icon-rendering is defined by define-decacheable-structure for 
;; icon-rendering.

;; Note that the function reclaim-icon-rendering-and-raster, rather than
;; reclaim-icon-rendering, must be used to reclaim icon renderings if the
;; rendering structure is to be reclaimed as well.  It would be better
;; to have a slot value reclaimer for the rendering-structure? slot but 
;; this is not possible since in order to reclaim the rendering structure,
;; other slots in the icon rendering besides rendering-structure? must
;; be accessed (see also reclaim-icon-rendering-and-raster,
;; reclaim-rendering-structure).

;; Original documentation (prior to 2.0):
;; ;;; An `icon rendering' represents an icon drawn in a particular manner,
;; ;;; specifically, at a particular x scale, y scale, and reflection/rotation; in
;; ;;; a particular format; and (except for a monochrome raster) for a particular
;; ;;; foreground color difference and against a particular background color.
;; 
;; ;;; A `rendering structure' is typically a stored raster, but could also be a
;; ;;; display list structure of some sort.  An icon rendering is always for a
;; ;;; particular format of rendering structure, but the rendering structure need
;; ;;; not yet exist (or ever exist if the actual rendering is only done remotely
;; ;;; via ICP).  As of 11 April 89, a rendering structre is a list of stored
;; ;;; rasters or is an empty list (i.e. nil).  The list has to be made up of
;; ;;; gensym conses.



;; Reorder the slots, someday!




;;; An icon-rendering is a decacheable structure.

(define-decacheable-structure icon-rendering 
  (make-icon-rendering-internal
    line-drawing-description-for-rendering?
    computed-values-plist 
    x-scale-of-rendering y-scale-of-rendering
    reflection-and-rotation-of-rendering
    width-of-rendered-icon
    height-of-rendered-icon
    width-of-rendering-structure
    height-of-rendering-structure
    number-of-rendering-structure-elements
    corresponding-icon-description?
    window-for-icon-rendering
    region-extrema-for-rendering?
    array-of-bitmaps-used
    total-number-of-bitmaps
    memory-used-by-bitmaps)
  compute-cost-of-decaching-icon-rendering
  nil
  compute-size-of-icon-rendering
  t
  window-for-icon-rendering
  (delete-icon-rendering-and-reclaim-icp-index icon-rendering)
  )

;; A simple test for icon-rendering decaching is as follows.
;; 1.  Trace make-decacheable-icon-rendering and decache-icon-rendering.
;; 2.  On a new G2 process, make a workspace and put a quantitative variable
;;     on it.
;; 3.  Delete the quantitative variable.
;; 4.  Put up a quantitative parameter.  The icon rendering for the
;;     quantitative variable should be decached.



(defun compute-cost-of-decaching-icon-rendering (icon-rendering)
  icon-rendering
  100  ; see notes for compute-cost-of-decaching-graph-rendering
  )

(defun compute-size-of-icon-rendering (icon-rendering)
  (compute-size-of-icon-rendering-1
    (width-of-rendering-structure icon-rendering)
    (height-of-rendering-structure icon-rendering)))

(defun compute-size-of-icon-rendering-1 (width height)
  (maxf width height))



(defun compute-true-size-of-icon-rendering (icon-rendering)
  (loop for region-bounds-and-raster in (rendering-structure? icon-rendering)
	as x-offset-for-stored-raster?
	   = (x-offset-for-stored-raster? region-bounds-and-raster)
	sum
    (cond 
      ((null x-offset-for-stored-raster?)
       (return
	 (compute-true-size-of-icon-rendering-1
	   (width-of-rendering-structure icon-rendering)
	   (height-of-rendering-structure icon-rendering))))
      (t 
       (compute-true-size-of-icon-rendering-1
	 (-r (x-max-for-stored-raster? region-bounds-and-raster)
	     x-offset-for-stored-raster?)
	 (-r (y-max-for-stored-raster? region-bounds-and-raster)
	     (y-offset-for-stored-raster? region-bounds-and-raster)))))))

(defun compute-true-size-of-icon-rendering-1 (width height)
  (maxr 1 (roundr (*r width height) 32)))

;; Make these be compute-size-of-icon-rendering, compute-size-of-icon-rendering-1! 






;;; `Delete-icon-rendering-and-reclaim-icp-index' is called by
;;; decache-icon-rendering to do all reclamation and cleanup necessary to
;;; delete the icon rendering.  Note that decache-icon-rendering is only
;;; called from a G2 process, never a telewindows process.  This is due to the
;;; fact that decache-icon-rendering is called only from 
;;; make-decacheable-icon-rendering which is called in the G2 process by
;;; get-or-make-icon-rendering when an entity is drawn.
;;; Make-decacheable-icon-rendering is never called from a Telewindows
;;; process (begin-making-icon-rendering uses make-icon-rendering).

(defun delete-icon-rendering-and-reclaim-icp-index (icon-rendering)
  (reclaim-icp-object-map-for-icon-rendering icon-rendering)
  (reclaim-icon-rendering-and-remove-from-icon-description-if-g2 icon-rendering))

;; An icp object index is assigned in the G2 process when an icp object (such as
;; an icon-rendering) is made (see def-icp-object-type,
;; assign-corresponding-icp-object-index, assign-index-in-index-space).  In the
;; Telewindows process, the object is typically created and its index noted
;; using store-corresponding-icp-object (see begin-making-graph-rendering or
;; begin-making-icon-rendering for example).  Store-corresponding-icp-object
;; does not allocate any new memory, but rather, stores the object in the
;; appropriate vector in the index space according to the index (so that the
;; object can be retrieved from the index in the future).

;; The index is deassigned in the G2 process when the icon rendering is deleted
;; by deassign-index-in-index-space.  The index can now be used for other
;; objects.  Note that nothing has to be done for the Telewindows side; the
;; location in the index space corresponding to the index simply becomes
;; available and is reset with a new object when the index is reused.
;; The deassignment is done by reclaim-icp-object-map-for-icon-rendering
;; which is automatically defined by def-icp-object-type for icon-rendering.




;;; The function `reclaim-rendering-structure' reclaims a rendering structure
;;; (which is a list of stored rasters).  The conses are reclaimed as gensym
;;; conses, and the stored rasters are reclaimed using reclaim-stored-raster.

(defun reclaim-rendering-structure (icon-rendering)
  (let ((rendering-structure?
	  (rendering-structure? icon-rendering)))
    (when rendering-structure?
      (loop with gensym-window 
	      = (window-for-icon-rendering icon-rendering)
	    with minimum-width
	      = (width-of-rendering-structure icon-rendering)
	    with minimum-height
	      = (height-of-rendering-structure icon-rendering)
	    for region-bounds-and-raster in rendering-structure?
	    as x-max-for-stored-raster?
	       = (x-max-for-stored-raster? region-bounds-and-raster)
	    do
	(if x-max-for-stored-raster?
	    (reclaim-stored-raster 
	      (raster-for-region region-bounds-and-raster)
	      gensym-window
	      (-r x-max-for-stored-raster?
		  (x-offset-for-stored-raster? region-bounds-and-raster))
	      (-r (y-max-for-stored-raster? region-bounds-and-raster)
		  (y-offset-for-stored-raster? region-bounds-and-raster))
	      1 nil)
	    (reclaim-stored-raster 
	      (raster-for-region region-bounds-and-raster)
	      gensym-window
	      minimum-width minimum-height
	      1 nil))
	(reclaim-region-bounds-and-raster
	  region-bounds-and-raster))
      (reclaim-gensym-list rendering-structure?))))

;; The depth of stored rasters for icons is currently always 1.




;;; `reclaim-icon-bitmap-parameters' reclaims anything in
;;; the icon-rendering used for memory usage of bitmaps,
;;; and updates the global variables that keep track of the
;;; bitmap memory usage.

(defun reclaim-icon-bitmap-parameters (icon-rendering)
  (let ((number-of-bitmaps (total-number-of-bitmaps icon-rendering))
	(window-for-icon-rendering
	  (window-for-icon-rendering icon-rendering)))
    ;; if TW, these slots are nil
    (when number-of-bitmaps
      (decff (icon-bitmap-count-for-window window-for-icon-rendering)
	     number-of-bitmaps)
      (decff (icon-bitmap-memory-for-window window-for-icon-rendering)
	     (memory-used-by-bitmaps icon-rendering))
      (reclaim-managed-simple-vector (array-of-bitmaps-used icon-rendering)))))




;;; The ICP object type `icon-rendering' ...

(defun reclaim-icon-rendering-and-raster (icon-rendering)
  (reclaim-icon-bitmap-parameters icon-rendering)
  (reclaim-computed-values-plist icon-rendering)
  (reclaim-region-extrema-for-rendering? icon-rendering)
  (reclaim-rendering-structure icon-rendering)
  (reclaim-icon-rendering icon-rendering))

(defun reclaim-computed-values-plist (icon-rendering)
  (reclaim-tree-including-leaves-for-gensym-conses
    (computed-values-plist icon-rendering)))

(defun reclaim-icon-region-extrema? (icon-region-extrema?)
  (reclaim-gensym-tree icon-region-extrema?))

(defun reclaim-region-extrema-for-rendering? (icon-rendering)
  (reclaim-icon-region-extrema?
    (region-extrema-for-rendering? icon-rendering)))


;; Thanks to rh, messages to reclaim ICP objects are queued and processed later
;; in a scheduler task. Use this function to flush that queue.

(defun flush-queued-reclaim-index-space-messages (gensym-window)
  (let ((icp-socket? (icp-socket-for-gensym-window? gensym-window)))
    (when (and icp-socket?
	       (icp-socket-deregister-icp-objects-alist icp-socket?))
      (send-queued-reclaim-index-space-messages icp-socket?))))



(def-icp-object-type icon-rendering
		     (standard-icp-object-index-space
		      (corresponding-icp-object-map-for-icon-rendering
			icon-rendering)
		      reclaim-icon-rendering-and-raster)
  (current-system-case
    ((ab)
     (send-icp-begin-making-icon-rendering
       corresponding-icp-object-index
       (x-scale-of-rendering icon-rendering)
       (y-scale-of-rendering icon-rendering)
       (reflection-and-rotation-of-rendering icon-rendering)
       (width-of-rendering-structure icon-rendering)
       (height-of-rendering-structure icon-rendering)
       (width-of-rendered-icon icon-rendering)
       (height-of-rendered-icon icon-rendering)
       (number-of-rendering-structure-elements icon-rendering))
     (make-rendering-structure nil icon-rendering))
    (t
      (error "Can only send an icon-rendering from G2."))))

;; An alternative to sending icp messages to paint on the scratchpad raster in the
;; server is to have the line drawing description as an icp object argument to a
;; make-icon- rendering icp message.  This would make it ...



(declare-forward-reference remove-icon-rendering-from-icon-description function) ; ICONS

(defun reclaim-icon-rendering-and-remove-from-icon-description (icon-rendering)
  (current-system-case
    ((ab)
     (remove-icon-rendering-from-icon-description 
       icon-rendering 
       (corresponding-icon-description? icon-rendering))
     (reclaim-icon-rendering-and-raster icon-rendering))
    (t
      (error "Reclaim-icon-rendering-and-remove-from-icon-description called ~
              outside G2.  The argument was ~a"
	     icon-rendering))))





(def-icp-message-type begin-making-icon-rendering
    (corresponding-icp-object-index
      (unsigned-integer x-scale-of-rendering)
      (unsigned-integer y-scale-of-rendering)
      (symbol reflection-and-rotation-of-rendering)
      (unsigned-integer width-of-rendering-structure)
      (unsigned-integer height-of-rendering-structure)
      (unsigned-integer width-of-rendered-icon)
      (unsigned-integer height-of-rendered-icon)
      (unsigned-integer
	number-of-rendering-structure-elements))
  (let ((icon-rendering
	  (store-corresponding-icp-object
	    corresponding-icp-object-index
	    (make-icon-rendering
	      nil ;line-drawing-description
	      nil ;computed-values-plist
	      x-scale-of-rendering y-scale-of-rendering
	      reflection-and-rotation-of-rendering
	      width-of-rendered-icon height-of-rendered-icon
	      width-of-rendering-structure height-of-rendering-structure
	      number-of-rendering-structure-elements nil current-window nil
	      nil nil nil))))
    (setf (rendering-structure? icon-rendering)
	  (loop repeat number-of-rendering-structure-elements
		collect (make-region-raster-according-to-messages
			  icon-rendering)
		  using gensym-cons-macro))))


;; to look for and use an EXISTING icon rendering, the icon description would
;; have to exist as an ICP object and any existing rendering structure in that
;; icon rendering would have to be dealt with in some way.




;;; Make-region-raster-according-to-messages is called by the handler for the
;;; begin-making-icon-rendering message type to make the region rasters for an
;;; icon rendering for the Telewindows case.  As with the non-Telewindows case,
;;; make-region-raster-for-icon is called.  However, before this can be called,
;;; the region extrema must be received.  Therefore,
;;; make-region-raster-according-to-messages first calls handle-icp-messages in
;;; order to receive the region-extrema-for-stored-raster message.  The handler
;;; for this message type sets the special variables region-x-offset?,
;;; region-y-offset?, region-x-max?, and region-y-max?.  See also
;;; make-rendering-structure (this sends the messages).  Note that the
;;; region-extrema-for-rendering?  slot of the icon rendering is not set on the
;;; Telewindows side.

(defvar region-x-offset?)
(defvar region-y-offset?)
(defvar region-x-max?)
(defvar region-y-max?)

(defun make-region-raster-according-to-messages (icon-rendering)
  (let ((region-x-offset? nil)
	(region-y-offset? nil)
	(region-x-max? nil)

	(region-y-max? nil))
    (handle-icp-messages t)  ; to set region-x-offset?, etc.
    (make-region-raster-for-icon
      (current-window
	(width-of-rendering-structure icon-rendering)
	(height-of-rendering-structure icon-rendering)
	region-x-offset? region-y-offset? region-x-max? region-y-max?)
      (handle-icp-messages t))))


(def-icp-message-type region-extrema-for-stored-raster
    ((unsigned-integer x-offset)
     (unsigned-integer y-offset)
     (unsigned-integer x-max)
     (unsigned-integer y-max))
  (setq region-x-offset? x-offset
	region-y-offset? y-offset
	region-x-max? x-max
	region-y-max? y-max))




;;; The substitution-macro `add-from-region-bounds-and-raster' is
;;; a subfunction of add-from-icon-rendering-to-current-window.

(defun-substitution-macro add-from-region-bounds-and-raster
    (subtract-instead?
      clipped-left-edge clipped-top-edge
      clipped-right-edge clipped-bottom-edge
      color-difference-for-stored-raster
      region-bounds-and-raster
      left-edge-in-icon-rendering
      top-edge-in-icon-rendering)
  (let ((x-offset-for-stored-raster?
	  (x-offset-for-stored-raster? region-bounds-and-raster)))
    (if x-offset-for-stored-raster?
	(let* ((y-offset-for-stored-raster?
		 (y-offset-for-stored-raster? region-bounds-and-raster))
	       (left-edge-in-region 
		 (-r left-edge-in-icon-rendering x-offset-for-stored-raster?))
	       (top-edge-in-region
		 (-r top-edge-in-icon-rendering y-offset-for-stored-raster?))
	       (left-edge-in-stored-raster
		 (maxr 0 left-edge-in-region))
	       (top-edge-in-stored-raster
		 (maxr 0 top-edge-in-region))
	       (new-clipped-left-edge
		 (maxr clipped-left-edge
		       (-r clipped-left-edge left-edge-in-region)))
	       (new-clipped-top-edge
		 (maxr clipped-top-edge
		       (-r clipped-top-edge top-edge-in-region)))
	       (new-clipped-right-edge
		 (minr clipped-right-edge
		       (+r new-clipped-left-edge
			   (-r (-r (x-max-for-stored-raster?   ; region width
				     region-bounds-and-raster)
				   x-offset-for-stored-raster?)
			       (maxr left-edge-in-region 0)))))
	       (new-clipped-bottom-edge
		 (minr clipped-bottom-edge
		       (+r new-clipped-top-edge
			   (-r (-r (y-max-for-stored-raster?   ; region height
				     region-bounds-and-raster)
				   y-offset-for-stored-raster?)
			       (maxr top-edge-in-region 0))))))
	  (when (and (>r new-clipped-right-edge new-clipped-left-edge)
		     (>r new-clipped-bottom-edge new-clipped-top-edge))
	    (add-from-raster-tiles-to-current-window
	      subtract-instead?
	      new-clipped-left-edge new-clipped-top-edge
	      new-clipped-right-edge new-clipped-bottom-edge
	      color-difference-for-stored-raster
	      (raster-for-region region-bounds-and-raster)
	      left-edge-in-stored-raster
	      top-edge-in-stored-raster)))
	(add-from-raster-tiles-to-current-window
	  subtract-instead?
	  clipped-left-edge clipped-top-edge
	  clipped-right-edge clipped-bottom-edge
	  color-difference-for-stored-raster
	  (raster-for-region region-bounds-and-raster)
	  left-edge-in-icon-rendering
	  top-edge-in-icon-rendering))))

;; This is used only by add-from-icon-rendering-to-current-window, below.



;;; `Add-from-icon-rendering-to-current-window' adds to the area of
;;; current-window bounded by clipped-left-edge, clipped-top-edge,
;;; clipped-right-edge, and clipped-bottom-edge, color differences based on
;;; color-difference or list-of-color-differences and the corresponding
;;; (rectangular) area of icon-rendering bounded by left-edge-in-icon-rendering
;;; and top-edge-in-icon-rendering.  (Note that when subtract-instead? is
;;; non-nil, add-from-icon-rendering-to-current-window subtracts instead of
;;; adds.)

;;; The function `add-from-icon-rendering-to-current-window' will reclaim
;;; the list of color differences it is given as gensym conses.

(def-icp-message-functions add-from-icon-rendering-to-current-window
    (subtract-instead?
      (coordinate clipped-left-edge)
      (coordinate clipped-top-edge)
      (coordinate clipped-right-edge)
      (coordinate clipped-bottom-edge)
      color-difference					    ; Ignored for polychrome icon
      icon-rendering
      (coordinate left-edge-in-icon-rendering)
      (coordinate top-edge-in-icon-rendering)
      ;; nil for monochrome icon, for polychrome, 1:1 w/rendering structure
      ;; elements, nil for monochr.
      (list-of-unsigned-integers
	list-of-color-differences))
  (case type-of-current-window
    (t
     (let ((rendering-structure
	     (or (rendering-structure? icon-rendering)
		 (setf (rendering-structure? icon-rendering)
		       (current-system-case
			 ((ab)
			  (make-rendering-structure
			    current-window icon-rendering))
			 (t
			   (error
			     "Make-rendering-structure called outside G2.")))))))
       (loop for region-bounds-and-raster in rendering-structure
	     as remaining-color-differences
		= (or list-of-color-differences '(nil))
		then (cdr remaining-color-differences)
	     as color-difference-for-stored-raster
		= (or (car remaining-color-differences) color-difference)
	     doing
	 (unless (color-difference-is-transparent-p
		   color-difference-for-stored-raster)
	   (add-from-region-bounds-and-raster
	     subtract-instead?
	     clipped-left-edge clipped-top-edge
	     clipped-right-edge clipped-bottom-edge
	     color-difference-for-stored-raster
	     region-bounds-and-raster left-edge-in-icon-rendering
	     top-edge-in-icon-rendering)))))))

;; Expands into 2026 lines of C code!

    ;; In paint-mode, the meaning of color-difference is slightly changed: a 0
;; difference means to go ahead and draw, using the bg color.  The value
;; transparent-color-value, which is only passed in paint mode, is then used to
;; mean do not draw at all. This comment applies to other routines in this
;; file.  -fmw, 6/8/94



;;;; Double Buffering


(def-concept double-buffering)




;;; The function `allocate-offscreen-pixmap' tries to ensure a raster the size
;;; of our window, for buffering screen updates.  Runs on TW.

(defun ensure-offscreen-pixmap (gensym-window)
  (let ((window-width (-f (right-edge-of-window gensym-window)
			  (left-edge-of-window gensym-window)))
	(window-height (-f (bottom-edge-of-window gensym-window)
			   (top-edge-of-window gensym-window)))
	(window-depth (window-screen-depth gensym-window))
	(pixmap? (offscreen-pixmap? gensym-window)))
    (cond ((and pixmap?
		(>=f (pixmap-width pixmap?) window-width)
		(>=f (pixmap-height pixmap?) window-height)
		(=f (pixmap-depth pixmap?) window-depth))
	   pixmap?)
	  (t
	   (when pixmap?
	     (reclaim-pixmap pixmap?))
	   (setf (offscreen-pixmap? gensym-window)
		 (allocate-offscreen-pixmap
		   gensym-window window-width window-height window-depth))))))

;; TODO: Make it screen-sized if not too much bigger (handles 99% of window
;; resizes)


;;; The function `allocate-offscreen-pixmap' tries to allocate a pixmap of the
;;; given size.  Unlike create-stored-raster, on failure it gives up
;;; immediately, rather than reclaiming every other raster in existance and
;;; trying again.  Runs on TW.

(defun allocate-offscreen-pixmap (gensym-window width height depth)
  (unless (eq g2-machine-type 'windows95) ; True for any Win9x
    (let* ((do-not-error-in-x11-create-pixmap-on-failed-allocation t)
	   ;; Due to a conflict on Win32 with ImageClusters, make this always be
	   ;; an "irregular size" raster, which means it gets its own private
	   ;; bitmap handle on Windows. This doesn't impact GDI usage much since
	   ;; there are at most 3 pixmaps created this way: one for buffered
	   ;; drawing two for native icons. -fmw, 4/3/07
	   (raster (allocate-irregular-size-stored-raster
		     gensym-window width height depth)))
      (cond ((stored-raster-error-result-p raster)
	     ;; TODO: set flag which overrides system table on this window.
	     (notify-user-at-console
	       "Unable to allocate offscreen bitmap for buffered drawing.")
	     nil)
	    (t
	     (make-pixmap width height depth raster))))))



;;; The function `reclaim-offscreen-pixmap' reclaims the pixmap locally.  It is
;;; only called from the gensym-window reclaimer currently, since it is
;;; otherwise hard to determine a good time to reclaim it.

(defun reclaim-offscreen-pixmap (gensym-window)
  (when (offscreen-pixmap? gensym-window)
    (reclaim-pixmap (offscreen-pixmap? gensym-window))
    (setf (offscreen-pixmap? gensym-window) nil)))



;;; The function `bitblt-offscreen-bitmap' bitblts the offscreen bitmap for the
;;; current window to the given region of the current window.  Runs on the G2
;;; side.

(defun bitblt-offscreen-bitmap (region)
  (do-region-rectangles ((left top right bottom) region)
    (with-nested-draw-area? (left top right bottom)
      (draw-offscreen bitblt-offscreen-pixmap
		      left-edge-of-draw-area
		      top-edge-of-draw-area
		      right-edge-of-draw-area
		      bottom-edge-of-draw-area))))


;;; The ICP message `draw-offscreen' does all things related to offscreen
;;; drawing on the current window: enable, disable, bitblt, and reclaim.

(def-icp-message-functions draw-offscreen
    ((fixnum opcode)			; Operation
     (coordinate left)			; Source/dest rectangle for the bitblt
     (coordinate top)
     (coordinate right)
     (coordinate bottom))
  (case type-of-current-window
    (x11-window
     (case opcode
       (#.enable-offscreen-drawing
	(let ((pixmap? (ensure-offscreen-pixmap current-window)))
	  (when pixmap?
	    (c-x11-draw-offscreen current-native-window?
				  (pixmap-pointer pixmap?)
				  1))))
       (#.disable-offscreen-drawing
	(c-x11-draw-offscreen current-native-window? -1 0))
       (#.bitblt-offscreen-pixmap
	(let ((pixmap? (offscreen-pixmap? current-window)))
	  (when pixmap?
	    (c-x11-draw-pixmap (pixmap-pointer pixmap?)
			       current-native-window?
			       -1		; No mask
			       left top (-f right left) (-f bottom top) ; Source rectangle
			       left top	; Dest corner
			       1 0))))	; fg, bg colors don't matter
       (#.reclaim-offscreen-pixmap
	(reclaim-offscreen-pixmap current-window))
       (t
	(dwarn "Bogus opcode ~s in offscreen-drawing" opcode))))))

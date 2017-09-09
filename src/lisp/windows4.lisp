;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module WINDOWS4 -- Operations on the Gensym Window System

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Lowell B.  Hawkinson, Brian Matthews, Mark David, Andreas Hofmann,
;;; and Ong, Peng Tsin




;;;; Forward References in WINDOWS4




(declare-forward-reference refresh-window function)           ;; Panes
(declare-forward-reference refresh-rectangle-of-window function) ;; Panes
(declare-forward-reference lay-out-window function)           ;; Panes
(declare-forward-reference reshape-telewindow function)       ;; TeleWindows
(declare-forward-reference refresh-telewindow function)       ;; TeleWindows
(declare-forward-reference make-rendering-structure function) ;; Icons
(declare-forward-reference pending-drawing-for-workstation-p function)
(declare-forward-reference get-local-ui-toolkit-name function) ;; Native-TW

;; To CONTROLS or TW-PATCHES
(declare-forward-reference copy-gensym-window-attributes-into-g2-window function)

;; To TYPES or TW-PATCHES
(declare-forward-reference reclaim-if-evaluation-item-reference function)




;;;; Global Operations on Gensym Windows



;;; `Make-or-revise-window' makes or revises a gensym window, according to
;;; whether or not gensym-window-to-revise? is specified.
;;; Window-parameters-plist? must be a tree of unshared gensym conses and should
;;; always be specified for a new gensym window....

;;; Left-edge-in-window, top-edge-in-window, right-edge-in-window, and
;;; bottom-edge-in-window, specify the edges of the gensym window (in the
;;; window coordinate system).

;;; As of G2 7.1, when specified, for G2 or TW windows, the window parameters
;;; plist should contain two important new elements: window-x-in-parent and
;;; window-y-in-parent.  (For printing and old versions of TW, these are not
;;; needed.  They will default to (0, 0). This pair gives the position of the
;;; outside upper left corner of the window in the parent coordinate system.

;;; This is invoked by run-system-process via and in response to reshape events.

(defun make-or-revise-window
    (gensym-window-to-revise?
      left-edge-in-window top-edge-in-window
      right-edge-in-window bottom-edge-in-window
      native-window? raster-for-native-window?
      window-parameters-plist?)
  (let* ((gensym-window
	   (or gensym-window-to-revise?
	       (make-gensym-window native-window?)))
	 (original-window-parameters-plist
	   (window-parameters-plist gensym-window))
	 (window-parameters-plist
	   (or window-parameters-plist? original-window-parameters-plist)))
    (unless (eq window-parameters-plist original-window-parameters-plist)
      (reclaim-gensym-tree-with-text-strings original-window-parameters-plist))
    (setf (window-parameters-plist gensym-window) window-parameters-plist)

    (let* ((x (get-gensym-window-parameter gensym-window 'window-x-in-parent))
	   (y (get-gensym-window-parameter gensym-window 'window-y-in-parent)))
      (when (and x y)			; missing from pre-7.1 versions of TW
	(setf (window-x-in-parent gensym-window) x)
	(setf (window-y-in-parent gensym-window) y)))

    (setf (type-of-gensym-window gensym-window)
	  (get-gensym-window-parameter gensym-window 'type-of-gensym-window))
    (setf (scratchpad-raster-type-for-window gensym-window)
	  (get-gensym-window-parameter gensym-window 'scratchpad-raster-type-for-window))
    (setf (stored-raster-type-for-window gensym-window)
	  (get-gensym-window-parameter gensym-window 'stored-raster-type-for-window))

    (setf (window-screen-depth gensym-window)
	  ;; missing from pre-8.1 versions of TW.
	  (or (get-gensym-window-parameter gensym-window 'window-screen-depth)
	      (guess-screen-depth gensym-window)))

    ;; Note that although the 'bits-per-pixel value is bogus, and a vistigal
    ;; organ it must remain in the plist for connecting to old G2.
    (setf (minimum-line-height-of-text-to-draw gensym-window)
	  (get-gensym-window-parameter gensym-window
				       'minimum-line-height-of-text-to-draw))

    (reclaim-color-map-if-any			; New. (MHD 11/14/91)
      (color-map-for-window gensym-window))
    (setf (color-map-for-window gensym-window)
	  (make-color-map
	    (window-screen-depth gensym-window)
	    (or (get-gensym-window-parameter
		  gensym-window 'color-description-plist?)
		;; We only can get to the the next clause if we have an old
		;; (prior to 3.0) release of Telewindows, which was allowed to
		;; transmit nil for the color-description-plist? parameter.
		;; (MHD 11/2/90)
		(make-monochrome-color-description-plist 1 0))))

    ;; Create the tiling pattern, while reclaiming the old one.
    ;; Do we really have to do this if the window is merely being reshaped?
    ;; Nope. Create the tiling pattern only once. -fmw, 8/20/03
    (unless (default-pane-background-color-or-tiling-pattern gensym-window)
      (reclaim-default-pane-background-color-or-tiling-pattern
	(default-pane-background-color-or-tiling-pattern gensym-window))
      (setf (default-pane-background-color-or-tiling-pattern gensym-window)
	    (let ((color-or-pattern
		    (get-gensym-window-parameter
		      gensym-window
		      'default-pane-background-color-or-tiling-pattern-rows)))
	      (if (symbolp color-or-pattern)
		  color-or-pattern
		  (make-tiling-pattern gensym-window color-or-pattern))))
      (install-tiling-pattern gensym-window))		    ; Local window only?

    (setf (raster-for-native-window? gensym-window) raster-for-native-window?) ; Always NIL?
    (setf (left-edge-of-window gensym-window) left-edge-in-window)
    (setf (top-edge-of-window gensym-window) top-edge-in-window)
    (setf (right-edge-of-window gensym-window) right-edge-in-window)
    (setf (bottom-edge-of-window gensym-window) bottom-edge-in-window)
    gensym-window))

;; This looks like it leaks anything already in these slots, in particular the
;; color map, but since I don't fully understand the lifecycle of a color map
;; I leave it to MHD to decide what to do. - ben 11/07/91
;; It was leaking tiling-patterns, too. -fmw, 3/30/94

;; Consider having the minimum and maximum scale be x/y-specific.

;; Consider having pane-background-color-or-tiling-pattern, and perhaps some of
;; the scale parameters, be pane-specific.


;;; The function `guess-screen-depth' is used to try to guess the screen depth
;;; of a pre-8.1 telewindow, which doesn't send the depth over in the window
;;; parameters plist. We guess based on the pixel values in the color
;;; description plist, which is sent over.

(defun guess-screen-depth (gensym-window)
  (let ((maximum-pixel-value
	  (loop for (name (pixel)) on (get-gensym-window-parameter
					gensym-window 'color-description-plist?) by #'cddr
		maximize pixel)))
    (cond ((>=f maximum-pixel-value 65536)
	   24)
	  ((>=f maximum-pixel-value 256)
	   16)
	  ((>=f maximum-pixel-value 2)
	   8)
	  (t
	   1))))



;;; Clear-window paints gensym-window in color.  If left-edge-of-area?, et al,
;;; are specified, they specify the subset of the area to paint; otherwise,
;;; gensym-window is painted in its entirety.

(defun clear-window
       (gensym-window color
	&optional left-edge-of-area? top-edge-of-area?
	          right-edge-of-area? bottom-edge-of-area?)
  (let ((left-edge-of-area
	  (if left-edge-of-area?
	      (maxr left-edge-of-area? (left-edge-of-window gensym-window))
	      (left-edge-of-window gensym-window)))
	(top-edge-of-area
	  (if top-edge-of-area?
	      (maxr top-edge-of-area? (top-edge-of-window gensym-window))
	      (top-edge-of-window gensym-window)))
	(right-edge-of-area
	  (if right-edge-of-area?
	      (minr right-edge-of-area? (right-edge-of-window gensym-window))
	      (right-edge-of-window gensym-window)))
	(bottom-edge-of-area
	  (if bottom-edge-of-area?
	      (minr bottom-edge-of-area? (bottom-edge-of-window gensym-window))
	      (bottom-edge-of-window gensym-window))))
    (if (and (>r bottom-edge-of-area top-edge-of-area)
	     (>r right-edge-of-area left-edge-of-area))
	(update-window
	  gensym-window
	  left-edge-of-area top-edge-of-area
	  right-edge-of-area bottom-edge-of-area
	  'clear-window-1
	  left-edge-of-area top-edge-of-area
	  right-edge-of-area bottom-edge-of-area
	  color))))

(defun clear-window-1 (left-edge-of-area top-edge-of-area
		       right-edge-of-area bottom-edge-of-area color)
  (paint-solid-rectangle-in-current-window	; maybe do this more efficiently!?
    left-edge-of-area top-edge-of-area
    right-edge-of-area bottom-edge-of-area
    (map-to-color-value color))
  ;; Eliminate the annoying transparent window on startup?
  (sync-graphics-on-current-window))




;;; `Begin-window-update' invokes `handler-body-for-begin-window-update' and
;;; that establishes an a draw area and on-window-with-drawing context for the
;;; window and update area recieved.  It then recursively handles a message
;;; group inside that extent.  Most all messages in the icp window protocol
;;; expect to execute in this dynamic extent.

(defun-allowing-unwind handler-body-for-begin-window-update
    (gensym-window left-edge-of-update-area
		   top-edge-of-update-area
		   right-edge-of-update-area
		   bottom-edge-of-update-area)
  (with-draw-area (left-edge-of-update-area
		    top-edge-of-update-area
		    right-edge-of-update-area
		    bottom-edge-of-update-area
		    :who :telewindows
		    :why :telewindows)
    (on-window-without-drawing (gensym-window)
      (on-window-with-drawing (gensym-window)
	(handle-icp-messages t)))))


;;; `Begin-window-update' ... see handler-body-for-begin-window-update.

(def-icp-message-type begin-window-update
		      (gensym-window
		       (coordinate left-edge-of-update-area)
		       (coordinate top-edge-of-update-area)
		       (coordinate right-edge-of-update-area)
		       (coordinate bottom-edge-of-update-area))
  (handler-body-for-begin-window-update
    gensym-window
    left-edge-of-update-area
    top-edge-of-update-area
    right-edge-of-update-area
    bottom-edge-of-update-area))
  


;;; The defvar `trace-reshape-events' is set from trace-events in G2,
;;; and from some other function in telewindows.

(defvar trace-reshape-events nil)

(defun trace-reshape-event (gensym-window key-code left top right bottom &optional window-handle?)
  (with-permanent-allocation
    (format t "ReshapeEvent: ~a ~a  ~d,~d ~d,~d [~s]~%"
	    (if (fixnump key-code) (symbol-from-key-code key-code) key-code)
	    (type-of-gensym-window gensym-window)
	    left top right bottom
	    window-handle?)))



;;; The function `handle-reshape-event' eventually invalidates a region of the
;;; G2 window, which eventually causing drawing to happen.  It returns T iff we
;;; had to do a reshape.

(defun handle-reshape-event (gensym-window native-window)
  (let ((reshape-event?					    ; always there, but not assumed
	  (queue-pop (reshape-event-queue gensym-window)))
	(this-is-telewindows
	  (eq current-system-name 'telewindows)))
    ;; (icp-output-port-to-master-for-window? gensym-window)
    ;;  -- won't work if not connected yet!!
    (cond
      (reshape-event?
       (let* ((event-code (local-event-key-code reshape-event?))
	      (left-edge-of-update-area? (local-event-cursor-x reshape-event?))
	      (top-edge-of-update-area? (local-event-cursor-y reshape-event?))
	      (right-edge-of-update-area? (local-event-right reshape-event?))
	      (bottom-edge-of-update-area? (local-event-bottom reshape-event?)))
	 (when trace-reshape-events
	   (trace-reshape-event gensym-window event-code
				left-edge-of-update-area? top-edge-of-update-area?
				right-edge-of-update-area? bottom-edge-of-update-area?))
	 (reclaim-local-event reshape-event?)
	 (key-case event-code
	   (window-refresh
	     (if this-is-telewindows
		 (refresh-telewindow
		   gensym-window native-window
		   left-edge-of-update-area?
		   top-edge-of-update-area?
		   right-edge-of-update-area?
		   bottom-edge-of-update-area?)
		 (refresh-rectangle-of-window
		   gensym-window
		   left-edge-of-update-area? top-edge-of-update-area? 
		   right-edge-of-update-area? bottom-edge-of-update-area?)))
	   (window-reshape
	     (if this-is-telewindows
		 (reshape-telewindow gensym-window native-window)
		 (reshape-native-g2-window gensym-window native-window)))))
       T)					; T indicates we had to reshape
      (t nil))))				; NIL indicates we're in good shape

;; See also enqueue-window-reshape-event, in PRIMITIVES.

;; The "-or-data" case for the variable event-type-or-data is obsolete! Clean
;; this up! (MHD/AC 5/31/91)



;;; The icp-message `request-to-refresh-window' is sent from TW to G2. If
;;; edges-supplied? (a boolean arg) is nil, then left top right bottom, can be
;;; an arbitrary coordinates; they are ignored in that case.

(def-icp-message-type request-to-refresh-window
    (gensym-window
      (boolean refresh-graphic-element-memory-too?)
      (boolean edges-supplied?)	; unnecessary if coordinate?
      (coordinate		        ;   were a type!!
	left-edge-of-update-area-or-or-arbitrary-coordinate)
      (coordinate
	top-edge-of-update-area-or-or-arbitrary-coordinate)
      (coordinate
	right-edge-of-update-area-or-or-arbitrary-coordinate)
      (coordinate
	bottom-edge-of-update-area-or-or-arbitrary-coordinate))
  (request-to-refresh-window-1
    gensym-window
    refresh-graphic-element-memory-too?
    edges-supplied?
    left-edge-of-update-area-or-or-arbitrary-coordinate
    top-edge-of-update-area-or-or-arbitrary-coordinate
    right-edge-of-update-area-or-or-arbitrary-coordinate
    bottom-edge-of-update-area-or-or-arbitrary-coordinate))


(defun-void request-to-refresh-window-1
    (gensym-window
      refresh-graphic-element-memory-too?
      edges-supplied?
      left-edge-of-update-area-or-or-arbitrary-coordinate
      top-edge-of-update-area-or-or-arbitrary-coordinate
      right-edge-of-update-area-or-or-arbitrary-coordinate
      bottom-edge-of-update-area-or-or-arbitrary-coordinate)
  (declare (ignore refresh-graphic-element-memory-too?))

  (when trace-reshape-events
    (trace-reshape-event gensym-window 'refresh
			 left-edge-of-update-area-or-or-arbitrary-coordinate
			 top-edge-of-update-area-or-or-arbitrary-coordinate
			 right-edge-of-update-area-or-or-arbitrary-coordinate
			 bottom-edge-of-update-area-or-or-arbitrary-coordinate))

  (cond (edges-supplied?
	 (refresh-rectangle-of-window
	   gensym-window 
	   left-edge-of-update-area-or-or-arbitrary-coordinate
	   top-edge-of-update-area-or-or-arbitrary-coordinate
	   right-edge-of-update-area-or-or-arbitrary-coordinate
	   bottom-edge-of-update-area-or-or-arbitrary-coordinate))
	(t
	 (refresh-window gensym-window))))


(defun-allowing-unwind handler-body-for-request-to-reshape-window
    (gensym-window
      new-left-edge
      new-top-edge
      new-right-edge
      new-bottom-edge)
  (case (type-of-gensym-window gensym-window)
    (icp
     (when trace-reshape-events
       (trace-reshape-event gensym-window 'reshape
			    new-left-edge new-top-edge new-right-edge new-bottom-edge))
     (setf (left-edge-of-window gensym-window) new-left-edge)
     (setf (top-edge-of-window gensym-window) new-top-edge)
     (setf (right-edge-of-window gensym-window) new-right-edge)
     (setf (bottom-edge-of-window gensym-window) new-bottom-edge)
     (note-change-in-gensym-window gensym-window)

     (with-icp-window (gensym-window)
       (send-icp-request-to-reshape-native-window
	 gensym-window
	 new-left-edge new-top-edge
	 new-right-edge new-bottom-edge))

     (lay-out-window gensym-window)

     ;; This is what was causing the double refresh after resizing a
     ;; telewindow: the reshape event is followed immediately by all needed
     ;; refresh events (at least under X windows), so we don't need to refresh
     ;; here. -fmw, 10/12/94
     #+ignore
     (refresh-window gensym-window))))

(defun-allowing-unwind handler-body-for-request-to-move-window
    (gensym-window x y)
  (case (type-of-gensym-window gensym-window)
    (icp
     (setf (window-x-in-parent gensym-window) x)
     (setf (window-y-in-parent gensym-window) y)
     (note-change-in-gensym-window gensym-window)

     (with-icp-window (gensym-window)
       (send-icp-request-to-move-native-window gensym-window x y)))))

(def-icp-message-type request-to-reshape-window
		      (gensym-window
			(coordinate new-left-edge)
			(coordinate new-top-edge)
			(coordinate new-right-edge)
			(coordinate new-bottom-edge))
  (handler-body-for-request-to-reshape-window
    gensym-window
    new-left-edge
    new-top-edge
    new-right-edge
    new-bottom-edge))


;; This message is sent from TW 7.1 whenever the main window is moved or
;; resized.
(def-icp-message-type request-to-move-window
    (gensym-window (coordinate x) (coordinate y))
  (handler-body-for-request-to-move-window gensym-window x y))



(def-icp-message-type request-to-reshape-native-window
		      (gensym-window
			(coordinate new-left-edge)
			(coordinate new-top-edge)
			(coordinate new-right-edge)
			(coordinate new-bottom-edge))
  (make-or-revise-window
    gensym-window
    new-left-edge new-top-edge
    new-right-edge new-bottom-edge
    (native-window? gensym-window)
    (raster-for-native-window? gensym-window)
    (window-parameters-plist gensym-window)))


;; This is a G2->TW message, new in 7.1, telling TW to update it's local copy of
;; the gensym-window.
(def-icp-message-type request-to-move-native-window
    (gensym-window (coordinate x) (coordinate y))
  (setf (window-x-in-parent gensym-window) x)
  (setf (window-y-in-parent gensym-window) y))



;; Used in NUPEC.

(def-icp-message-functions paint-marker-onto-graph-raster 
			   (icon-rendering 
			     (coordinate x-in-graph-raster) 
			     (coordinate y-in-graph-raster)
			     color-value)
  (case type-of-current-window
    (t
     (let* ((rendering-structure
	      (or (rendering-structure? icon-rendering)
		  (or (rendering-structure? icon-rendering)
		      (setf (rendering-structure? icon-rendering)
			    (current-system-case
			      ((ab)
			       (make-rendering-structure
				 current-window icon-rendering))
			      (t
				(error
				  "Make-rendering-structure called outside G2."))))))))
       (iterate-over-monochrome-raster-list-if-appropriate (color-value)
	 (paint-clipped-marker-onto-graph-raster
	   (-r x-in-graph-raster 
	       (width-of-rendering-structure icon-rendering))
	   (-r y-in-graph-raster
	       (halfr (height-of-rendering-structure icon-rendering)) 1)
	   x-in-graph-raster
	   (+r y-in-graph-raster
	       (halfr (height-of-rendering-structure icon-rendering)))
	   (raster-for-region (car rendering-structure))
	   color-value))))))



;; Used in NUPEC.

(defun-void paint-clipped-marker-onto-graph-raster 
       (left-edge-in-graph-raster top-edge-in-graph-raster
	right-edge-in-graph-raster bottom-edge-in-graph-raster 
	stored-raster graph-line-color-value)
  (let* ((erase-raster-dateline
	   (erase-raster-dateline current-graph-rendering-structure))
	 (left-edge-in-icon-raster 0)
	 (top-edge-in-icon-raster 0))
    (when (>r 0 left-edge-in-graph-raster)
      (setq left-edge-in-icon-raster (-r left-edge-in-graph-raster)
	    left-edge-in-graph-raster 0))
    (when (and (>r right-edge-in-graph-raster erase-raster-dateline)
	       (>r erase-raster-dateline left-edge-in-graph-raster))
      (setq left-edge-in-icon-raster
	    (+r left-edge-in-icon-raster
		(-r erase-raster-dateline left-edge-in-graph-raster))
	    left-edge-in-graph-raster erase-raster-dateline))
    (when (>r 0 top-edge-in-graph-raster)
      (setq top-edge-in-icon-raster (-r top-edge-in-graph-raster)
	    top-edge-in-graph-raster 0))

    (if (tiled-raster-p stored-raster)
	(let ((width-of-area (-r right-edge-in-graph-raster left-edge-in-graph-raster))
	      (height-of-area (-r bottom-edge-in-graph-raster top-edge-in-graph-raster))
	      (raster-x-origin (-r left-edge-in-graph-raster left-edge-in-icon-raster))
	      (raster-y-origin (-r top-edge-in-graph-raster top-edge-in-icon-raster)))
	  (iterate-over-tiles-to-be-painted
	    (left-edge-in-icon-raster top-edge-in-icon-raster
					(+r left-edge-in-icon-raster width-of-area)	; right edge in stored raster
					(+r top-edge-in-icon-raster height-of-area)	; bottom edge in stored raster
					stored-raster)
	    
	    (let ((tile-x-position (*r j tile-size))
		  (tile-y-position (*r i tile-size)))
	      (paint-from-stored-raster-to-current-scratchpad-raster
		(maxr left-edge-in-graph-raster
		      (+r raster-x-origin tile-x-position))
		(maxr top-edge-in-graph-raster
		      (+r raster-y-origin tile-y-position))
		(minr right-edge-in-graph-raster
		      (width-of-graph-rendering-structure current-graph-rendering)
		      (+r raster-x-origin (+r tile-x-position tile-size)))
		(minr bottom-edge-in-graph-raster
		      (height-of-graph-rendering-structure current-graph-rendering)
		      (+r raster-y-origin (+r tile-y-position tile-size)))
		tile-to-paint
		(maxr 0 (-r left-edge-in-icon-raster tile-x-position))
		(maxr 0 (-r top-edge-in-icon-raster tile-y-position))
		graph-line-color-value))))

	(paint-from-stored-raster-to-current-scratchpad-raster
	  left-edge-in-graph-raster
	  top-edge-in-graph-raster
	  (minr right-edge-in-graph-raster 
		(width-of-graph-rendering-structure current-graph-rendering))
	  (minr bottom-edge-in-graph-raster 
		(height-of-graph-rendering-structure current-graph-rendering))
	  stored-raster left-edge-in-icon-raster top-edge-in-icon-raster
	  graph-line-color-value))))


;; Used in Trend Charts

(def-icp-message-functions paint-icon-onto-graph-raster 
    (icon-rendering
      (coordinate clip-left)
      (coordinate clip-top)
      (coordinate clip-right)
      (coordinate clip-bottom)
      (coordinate origin-left) 
      (coordinate origin-top)
      color-value)
  (case type-of-current-window
    (t
     (let* ((rendering-structure
	      (or (rendering-structure? icon-rendering)
		  (setf (rendering-structure? icon-rendering)
			(current-system-case
			  ((ab)
			   (make-rendering-structure
			     current-window icon-rendering))
			  (t
			    (error
			      "Make-rendering-structure called outside G2.")))))))
       (iterate-over-monochrome-raster-list-if-appropriate (color-value)
	 (paint-clipped-icon-onto-graph-raster
	      clip-left clip-top clip-right clip-bottom
	      (-r clip-left origin-left)
	      (-r clip-top origin-top)
	      (raster-for-region (car rendering-structure))
	      color-value))))))

(defun-void paint-clipped-icon-onto-graph-raster 
       (left-edge-in-graph-raster top-edge-in-graph-raster
	right-edge-in-graph-raster bottom-edge-in-graph-raster
	left-edge-in-icon-raster
	top-edge-in-icon-raster
	stored-raster graph-line-color-value)
;  (format t "TILING=~s~%" (tiled-raster-p stored-raster))
  (if (tiled-raster-p stored-raster)
      (let ((width-of-area (-r right-edge-in-graph-raster left-edge-in-graph-raster))
	    (height-of-area (-r bottom-edge-in-graph-raster top-edge-in-graph-raster))
	    (raster-x-origin (-r left-edge-in-graph-raster left-edge-in-icon-raster))
	    (raster-y-origin (-r top-edge-in-graph-raster top-edge-in-icon-raster)))
	  (iterate-over-tiles-to-be-painted
	    (left-edge-in-icon-raster
	     top-edge-in-icon-raster
	     (+r left-edge-in-icon-raster width-of-area)  ; right edge in stored raster
	     (+r top-edge-in-icon-raster height-of-area)  ; bottom edge in stored raster
	     stored-raster)

	    ;; tiled-raster
	    (let* ((tile-x-position (*r j tile-size))
		   (tile-y-position (*r i tile-size))
		   (destination-left-edge
		     (maxr left-edge-in-graph-raster
			   (+r raster-x-origin tile-x-position)))
		   (destination-top-edge
		     (maxr top-edge-in-graph-raster
			   (+r raster-y-origin tile-y-position))))
	;      (format t "graph-line-color-value=~s dest ~s to ~s source-left ~s~%"
	;             graph-line-color-value
	;	      left-edge-in-graph-raster right-edge-in-graph-raster
	;	      left-edge-in-icon-raster)
	;      (format t "tile-array-length ~s ~s ~%"
	;	      (managed-array-length tile-arrays)
	;	     (if (> (managed-array-length tile-arrays) 0)
	;		 (managed-array-length (managed-svref tile-arrays 0))
	;		  -1))
	;      (format t "numcol=~s numrow=~s tec=~s bec=~s lec=~s rec=~s~%"
	;	      number-of-columns-1 number-of-rows-1
	;	      top-edge-column bottom-edge-column
	;	      left-edge-column right-edge-column)
	;      (format t
	;	      "tile=~s tile-size=~s i=~s j=~s rxo=~s ryo=~s~%"
	;	      tile-to-paint tile-size i j raster-x-origin raster-y-origin)
	;      (format t "redge=~s width=~s foo=~s~%"
	;	      right-edge-in-graph-raster
	;	      (width-of-graph-rendering-structure current-graph-rendering)
	;	      (+r raster-x-origin (+r tile-x-position tile-size)))
	;      (format t "bedge=~s height =~s foo=~s~%~%"
	;	      bottom-edge-in-graph-raster
	;	      (height-of-graph-rendering-structure current-graph-rendering)
	;	      (+r raster-y-origin (+r tile-y-position tile-size)))
	;      (format t "FINAL DEST left=~s right= ~s source-left = ~s~%"
	;	      destination-left-edge
	;	      (minr right-edge-in-graph-raster
	;		    (width-of-graph-rendering-structure current-graph-rendering)
	;		    (+r destination-left-edge tile-size))
	;	      (if (=f i 0)
	;		  left-edge-in-icon-raster 0))
	      (paint-from-stored-raster-to-current-scratchpad-raster
		destination-left-edge
		destination-top-edge
		(minr right-edge-in-graph-raster
		      (width-of-graph-rendering-structure current-graph-rendering)
		      (+r destination-left-edge tile-size))
		(minr bottom-edge-in-graph-raster
		      (height-of-graph-rendering-structure current-graph-rendering)
		      (+r destination-top-edge tile-size))
		tile-to-paint
		(if (=f j 0)     ; bug fix 11/20/95 (jed,pbk) see NOTE A
		    left-edge-in-icon-raster 0)
		(if (=f i 0)     ; bug fix 11/20/95 (jed,pbk)
		   top-edge-in-icon-raster 0)
;		(maxr 0 (-r left-edge-in-icon-raster tile-x-position))
;		(maxr 0 (-r top-edge-in-icon-raster tile-y-position))
	       graph-line-color-value))))
      (paint-from-stored-raster-to-current-scratchpad-raster
	left-edge-in-graph-raster
	top-edge-in-graph-raster
	right-edge-in-graph-raster 
	bottom-edge-in-graph-raster 
	stored-raster
	left-edge-in-icon-raster top-edge-in-icon-raster
	graph-line-color-value)))

;; NOTE A: iterator  uses 'j for horizontal and 'i for vertical.  Left the iterator alone
;; and changed the uses of 'i and 'j . Should probably fix the iterator so that future bugs do
;; not crop up from this again.



;;; The function `note-change-in-gensym-window' is called from platforms after
;;; we create or revise a gensym-window, or from windows4 when a window changes
;;; size.  If this is Telewindows process, nothing is done.  

(defun note-change-in-gensym-window (gensym-window)
  (unless (memq current-system-name '(telewindows))
    ;; alt. test
    ;;   (icp-output-port-to-master-for-window? gensym-window)
    ;; won't work if not connected yet!!
    (copy-gensym-window-attributes-into-g2-window gensym-window)))



;;;; Enabling the New UI


;;; The predicates in this section determine which bits of the new UI (selection
;;; mode, native menus, etc), are enabled.  Each gensym-window can have its own
;;; UI.

;;; Currently, they are based on the values of two command line arguments, -ui
;;; and -windowhandle (and of course on the platform, etc).  Later, they may
;;; also depend on values in a system table.

;;; Normally the values for command line options are taken from the window's
;;; plist; however, during TW startup we need to know the value MDI before a
;;; gensym-window even exists. Hence the two different routines.  If a
;;; gensym-window is available, then you must use mdi-frame-p. Only during
;;; startup should one use telewindows-mdi-frame-p.



;;; The function `get-frame-window-type' returns a fixnum identifying the type
;;; of frame window to create for this process, if any. Note this is called from
;;; make-native-window, before command line arguments are parsed!

(defun get-frame-window-type (system)
  (let ((windowhandle? (get-command-line-keyword-argument #w"windowhandle"))
	(ui (parse-ui-style (get-command-line-keyword-argument #w"ui"))))
    (cond ((this-is-twng-p)
	   (if windowhandle?
	       frame-type-none		; TWAXL mode
	       frame-type-mdi))		; Otherwise, TWNG is always MDI.
	  ((neq system 'telewindows)
	   frame-type-classic)	   
	  (windowhandle?
	   frame-type-child)
	  ((eq ui 'classic)
	   frame-type-classic)
	  (t
	   frame-type-sdi))))

(defun this-is-twng-p ()
  (eq (get-local-ui-toolkit-name) 'xtp))

(defun twng-p (gensym-window?)
  (and gensym-window?
       (eq (get-gensym-window-parameter gensym-window? 'ui-toolkit) 'xtp)))

(defun embedded-window-p (gensym-window)
  (not (null (get-gensym-window-parameter gensym-window 'windowhandle))))

(defun multiwindow-option-p (gensym-window)
  (eq (get-gensym-window-parameter gensym-window 'ui) 'multiwindow))

(defparameter cached-gensym-window-for-gensym-window-ui nil)
(defparameter cached-found-ui-for-gensym-window-ui nil)

(defun gensym-window-ui (gensym-window?)
  (let ((found-ui))
    (cond
      ((null gensym-window?)
       nil)
      ((twng-p gensym-window?)
       'multiwindow)
      ((progn
	 (setq found-ui
	       (if (eq cached-gensym-window-for-gensym-window-ui gensym-window?)
		 cached-found-ui-for-gensym-window-ui
		 (progn
		   (setq cached-gensym-window-for-gensym-window-ui
			 gensym-window?)
		   (setq cached-found-ui-for-gensym-window-ui
			 (get-gensym-window-parameter gensym-window? 'ui))
		   cached-found-ui-for-gensym-window-ui)))
	 (member found-ui known-ui-styles))
       found-ui)
      ((current-window-supports-nms-menus gensym-window?) ; tw-70r0 or later
       (gensym-default-ui))
      (t
        'classic))))

(defun classic-ui-p (gensym-window)
  (eq (gensym-window-ui gensym-window) 'classic))

;; here we "know" that 'standard is (gensym-default-ui)
(defun standard-ui-p (gensym-window)
  (or (eq (gensym-window-ui gensym-window) 'standard)
      (not (member (gensym-window-ui gensym-window)
		   known-ui-styles))))

(defun multiwindow-ui-p (gensym-window)
  (twng-p gensym-window))

(defun win32-window-p (gensym-window)
  (eq (get-gensym-window-parameter gensym-window 'os-type) 'win32))

(defun telewindows-window-p (gensym-window)
  gensym-window
  (current-system-case
    (ab (icp-window-p gensym-window))
    (gsi nil)
    (t t)))
      
;; These versions are for use only by Telewindows, and only during startup
;; before the gensym-window exists.

(defun telewindows-embedded-p ()
  (getf command-line-arguments 'windowhandle))

(defun telewindows-multiwindow-ui-p ()
  (this-is-twng-p))

(defun telewindows-win32-window-p ()
  (windows-platform-p))  

(defun selection-ui-p (gensym-window)
  (and (not (classic-ui-p gensym-window))
       (current-window-supports-wide-polyline gensym-window)
       ;; A random condition to get tw7. Although TW 6.2 (and even earlier)
       ;; could run the selection UI, they have no command-line option turn
       ;; it off! (Actually, since TW simply sends all of its options to G2
       ;; uninterpreted, they do!!).
       (current-window-supports-nms-menus gensym-window)))

(defun native-pop-up-menus-p (gensym-window)
  (and (not (classic-ui-p gensym-window))
       (telewindows-window-p gensym-window)
       (win32-window-p gensym-window)
       (window-supports-native-widgets gensym-window)))

(defun mdi-frame-p (gensym-window)
  (and (multiwindow-ui-p gensym-window)
       (not (embedded-window-p gensym-window))
       (telewindows-window-p gensym-window)
       (win32-window-p gensym-window)
       (current-window-supports-mdi gensym-window)))

;; This can be true only for TW 7.0rx.
(defun old-style-mdi-frame-p (gensym-window)
  (and (multiwindow-ui-p gensym-window)
       (not (embedded-window-p gensym-window))
       (telewindows-window-p gensym-window)
       (win32-window-p gensym-window)
       (not (current-window-supports-mdi gensym-window))))
  
(defun telewindows-mdi-frame-p ()
  (and (telewindows-multiwindow-ui-p)
       (not (telewindows-embedded-p))
       (telewindows-win32-window-p)))

(defun telewindows-twaxl-mode-p ()
  (and (telewindows-embedded-p) 
       (telewindows-multiwindow-ui-p)))

(defun native-menu-bar-p (gensym-window)
  (and (native-pop-up-menus-p gensym-window)
       (current-window-supports-nms-menus gensym-window) ; tw7
       (not (embedded-window-p gensym-window))))

(defun native-icons-p (gensym-window)
  (and (not (classic-ui-p gensym-window))
       (not (printing-window-p gensym-window))
       (telewindows-window-p gensym-window) ; TODO: Could work in local G2 window.
       (win32-window-p gensym-window)
       (current-window-supports-native-icons gensym-window)))

(defun native-progress-bar-p (gensym-window)
  ;; We only really need the native progress bar in multiwindow mode, but
  ;; we might as well use it in standard mode, too.
  (and (native-menu-bar-p gensym-window)
       (current-window-supports-native-progress-bar gensym-window)))

#+unused
(defun native-scroll-bars-p (gensym-window)
  (native-pop-up-menus-p gensym-window)) ; Allow scroll bars in embedded TW.

(defun native-simple-dialogs-p (gensym-window)
  (and (native-pop-up-menus-p gensym-window)
       (current-window-supports-event-plists gensym-window))) ; False only in some alpha 7.0s?

(defun native-basic-dialogs-p (gensym-window)
  (and (native-simple-dialogs-p gensym-window)
       (current-window-supports-basic-dialogs gensym-window)))

(defun native-animation-control-p (gensym-window)
  (native-basic-dialogs-p gensym-window))

(defun native-file-dialog-without-custom-buttons-p (gensym-window)
  (and (native-pop-up-menus-p gensym-window)
       (current-window-supports-nms-menus gensym-window))) ; tw7

;; This is true if a native file dialog on gensym-window can browse the server's
;; file system.
(defun native-file-dialog-p (gensym-window)
  (and (native-pop-up-menus-p gensym-window)
       (current-window-supports-nms-menus gensym-window) ; tw7
       (or (current-window-supports-list-directory gensym-window)
	   (server-and-client-share-file-system-p gensym-window))))

(defun twaxl-window-p (gensym-window)
  (and (multiwindow-ui-p gensym-window)		     ; Embedded and multiwindow means TWAXL
       (embedded-window-p gensym-window)
       (telewindows-window-p gensym-window)
       (win32-window-p gensym-window)
       (current-window-supports-mdi gensym-window)))

(defun native-windows-p (gensym-window)
  (or (mdi-frame-p gensym-window)
      (twaxl-window-p gensym-window)))

(defun nms-controls-p (gensym-window)
  (and (native-pop-up-menus-p gensym-window)
       (current-window-supports-nms-controls gensym-window)
       (twng-p gensym-window)))

(defun nms-toolbars-p (gensym-window)
  (and (nms-controls-p gensym-window)
       (not (embedded-window-p gensym-window)))) ; TODO: Someday we may allow toolbars here.

(defun twng-window-p (gensym-window)
  (nms-controls-p gensym-window))

(defun native-custom-dialogs-p (gensym-window)
  (and (twng-window-p gensym-window)
       (current-window-supports-native-editor-ex gensym-window)))

(defun native-debugger-dialog-p (gensym-window)
  (and (not (classic-ui-p gensym-window))
       (not (printing-window-p gensym-window))
       (twng-window-p gensym-window)	; Only TWNG supports the native debugger now.
       (window-supports-debugger-dialog gensym-window)))

;;; The function `inhibit-restore-detail-pane-p' returns true only for a TWAXL
;;; window which is not in the special testing mode where windowhandle="0".
;;; Called from `restore-current-workstation-detail-pane'.

(defun inhibit-restore-detail-pane-p (gensym-window)
  (and (twaxl-window-p gensym-window)
       (not (equalw (get-gensym-window-parameter gensym-window 'windowhandle) #w"0"))))


;;; The function `server-and-client-share-file-system-p' is used to determine
;;; whether the client can see the same files as the server.  We restrict this
;;; to identical hosts for now.  Note that diskless hosts, for example, may have
;;; identical file systems while being distinct hosts.

(defun server-and-client-share-file-system-p (gensym-window)
  (server-and-client-are-same-host-p gensym-window))


;;; The function `server-and-client-are-same-host-p' is an approximation. It
;;; should work to call this function in either the server (G2) or the client
;;; (TW). In the G2 case, gensym-window is an ICP window and in the TW case
;;; gensym-window is an X11 window. However, in either case
;;; remote-icp-version-info contains the info for the peer.

;;; Note that the g2-operating-system and g2-machine-type properties were added
;;; to the version-info only in 7.0a2, so G2's and TW's earlier than this will
;;; never appear to be the same host. That's OK, since only 7.0 features use
;;; this predicate, and earlier 7.0 alpha's are no longer being run.

(defun server-and-client-are-same-host-p (gensym-window)
  (let* ((icp-port? (or (icp-output-port-for-window? gensym-window)
			(icp-output-port-to-master-for-window? gensym-window)))
	 (icp-socket? (and icp-port? (parent-icp-socket icp-port?)))
	 (info? (and icp-socket? (remote-icp-version-info icp-socket?))))
    (when info?
      (and
	(string-equalw local-host-name
		       (get-remote-icp-version-info-value icp-socket? 'local-host-name #w""))
	(eq g2-operating-system
	    (get-remote-icp-version-info-value icp-socket? 'g2-operating-system nil))
	(or (eq g2-machine-type
                (get-remote-icp-version-info-value icp-socket? 'g2-machine-type nil))
            ;; For compatibility with G2 2011 before June release
            (and (eq 'intelnt g2-machine-type)
                 (eq 'windows (get-remote-icp-version-info-value icp-socket? 'g2-machine-type nil))))))))

;; TODO: Use machine IDs or peer IP addresses.


;;;; 32-bit Integers


;;; A `32bit-integer' is represented as a fixnum or a gensym-cons of the high
;;; and low 16 bits. We could also use a double-float, string, structure,
;;; simple-array of (unsigned 32), etc.

;; Note: the name "int32" conflicts with C typedefs.

(defun make-32bit-integer (high-part low-part)
  (let ((h (logandf high-part #xFFFF))
	(l (logandf low-part  #xFFFF)))
    (if (=f h 0) l (gensym-cons h l))))

(defun 32bit-integer-p (thing)
  (or (fixnump thing)
      (and (consp thing)
 	   (fixnump (car thing))
 	   (fixnump (cdr thing)))))

(defun 32bit-integer-high-part (32bit-integer)
  (if (consp 32bit-integer)
      (car-of-cons 32bit-integer)
      0))

(defun 32bit-integer-low-part (32bit-integer)
  (if (consp 32bit-integer)
      (cdr-of-cons 32bit-integer)
      32bit-integer))

(defun copy-32bit-integer (32bit-integer)
  (make-32bit-integer (32bit-integer-high-part 32bit-integer)
		      (32bit-integer-low-part 32bit-integer)))
  
(defun reclaim-32bit-integer (32bit-integer)
  (if (consp 32bit-integer)
      (reclaim-gensym-cons 32bit-integer)))

(def-icp-value-writer 32bit-integer
  (write-icp-unsigned-integer
    (non-resumable-icp-form (32bit-integer-high-part 32bit-integer)))
  (write-icp-unsigned-integer
    (non-resumable-icp-form (32bit-integer-low-part 32bit-integer))))

(def-icp-value-reader 32bit-integer
  (non-resumable-icp-form
    (make-32bit-integer (read-icp-unsigned-integer) (read-icp-unsigned-integer))))


;;;; Lisp-C Glue

;;; The functions `fixnum-list-to-word-vector' and `word-vector-to-fixnum-list'
;;; have as their sole purpose getting a list of fixnums in and out of C. A
;;; "word-vector" here is a null-terminated wide-string, using two words per
;;; fixnum, low word first, 15 bits per word. The high bit of every word is 1,
;;; except for the terminating null.

;;; See `editor_set_breakpoints' and `editor_get_breakpoints' in ext/c/editor.c
;;; for corresponding C code.

(defun fixnum-list-to-word-vector (fixnum-list)
  (let ((array (allocate-byte-vector-16 (1+f (*f 2 (length fixnum-list))))))
    (loop with i = -1
	  for fixnum in fixnum-list
	  do (setf (byte-vector-16-aref array (incff i)) (logiorf #x8000 (logandf fixnum #x7FFF))
		   (byte-vector-16-aref array (incff i)) (logiorf #x8000 (logandf (ashf fixnum -15) #x7FFF)))
	  finally
	    (setf (byte-vector-16-aref array (incff i)) 0))
    array))

(defun word-vector-to-fixnum-list (array?)
  (when array?
    (loop for i from 0 by 2
	  until (=f (byte-vector-16-aref array? i) 0)
	  as low  = (logandf (byte-vector-16-aref array? i) #x7FFF)
	  as high = (logandf (byte-vector-16-aref array? (1+f i)) #x7FFF)
	  as value = (logiorf (ashf (logandf high #x3FFF) 15) low)
	  as fixnum = (cond ((=f (logandf high #x4000) 0) ; Sign bit
			     value)
			    ((and (=f high #x4000) (=f low 0))
			     most-negative-fixnum)
			    (t
			     (-f (1+f (logxorf value #x1FFFFFFF)))))
	  collect fixnum using gensym-cons)))

(defmacro setf-bits (place mask bool)
  `(setf ,place (if ,bool (logiorf ,place ,mask) (logandc2f ,place ,mask))))


;;;; Native Windows


;;; Low-level code for creating and managing native windows, independent of
;;; whether they are attached to image-planes or not. The code is here because
;;; it must be in both G2 and TW, and in G2 must precede panes.lisp.

;;; A `native-window' is a structure representing an HWND. When G2 tells TW to
;;; create a native-window, the structure is allocated on both sides, while the
;;; HWND lives only on TW.

(def-concept native-window)

;;; A `window-handle' is a non-negative fixnum (>= 0) assigned by G2 for each
;;; native-window created. Window-handles increase linearly from 1 and are never
;;; reused for a given TW connection. When we tell TW to create a native-window,
;;; we send the window-handle to assign to it, and TW sends the window-handle
;;; back to G2 in all events pertaining to that window.

;;; By convention, the handle 0 represents the main G2 window, which corresponds
;;; to the MDI client window on TW.

;;; This is essentially duplicating what ICP does with `index-spaces', but with
;;; the vital difference that we never reuse a handle on a given connection. We
;;; need that property in order to reliably detect stale handles (handles to
;;; windows which have already been deleted, but still have events in the
;;; queue).

(def-concept window-handle)

;;; A `window-index' is the non-negative integer (>=0) assigned in the C code
;;; via cache_cpointer, needed only because we can't return 32-bit HWND's from C
;;; to lisp directly. In contrast to window-handles, window-indexes are local to
;;; their process (TW or G2). It is meaningless to send them in an ICP message.

(def-concept window-index)

(defconstant-for-case nip-wintype-mdichild 1)    ; Keep in sync with NativeWindowType in msincls.h
(defconstant-for-case nip-wintype-embedded 2)
(defconstant-for-case nip-wintype-toplevel 3)
(defconstant-for-case nip-wintype-pane 4)

(defconstant default-top-level-window-style
  (logiorf ws-visible ws-overlapped ws-minimizebox ws-maximizebox ws-caption ws-sysmenu
 	   ws-clipsiblings ws-thickframe))

(defconstant default-mdi-child-style
  (logiorf ws-visible ws-child ws-minimizebox ws-maximizebox ws-caption ws-sysmenu 
 	   ws-clipsiblings ws-thickframe))

(defconstant default-pane-window-style
  (logiorf ws-visible ws-child ws-clipsiblings ws-thickframe))

;;; The function `allocate-native-window-handle' returns the next window handle
;;; on given window. Handles are never reused for a given window, and do not
;;; check for fixnum overflow.

(defun allocate-native-window-handle (gensym-window)
  (prog1 (next-native-window-handle gensym-window)
    (incff (next-native-window-handle gensym-window))))


;;; The `native-window' structure represents a native window on the given
;;; gensym-window. It is abstract, and is subclassed for the various window
;;; types we need: workspace windows, tree windows, etc.

;;; A KB-level G2 object may be attached, and will be kept in sync. It must be a
;;; subclass of g2-native-window.

(def-structure (native-window
		 (:constructor make-native-window-1)
		 (:reclaimer reclaim-native-window-1)
		 (:predicate nil)
		 #+development (:print-function print-native-window))
  (native-window-gensym-window nil)
  (native-window-handle -1)		; Assigned by G2. Unique positive integer or -1.
  (native-window-index? nil)		; As returned from C routines. NIL on G2 side if ICP window.
  (native-window-left 0)		; The client area position and size.
  (native-window-top 0)
  (native-window-width 0)
  (native-window-height 0)
  (native-window-state nil)		; minimized, maximized, normal, docked, floating, etc.
  (native-window-style 0)		; Win32 window style bits
  (native-window-exstyle 0)
  (native-window-x-scroll? nil)		; Scroll position (want to know scroll range, too?)
  (native-window-y-scroll? nil)
  (native-window-parent? nil)		; 32bit-integer HWND of parent or NIL.
  (native-window-class nil)		; g2-workspace-view, editor, etc.
  (native-window-item? nil)		; KB-level object, if any.
  (native-window-close-action 'destroy)
  (native-window-type nil)		; MDI-CHILD, PANE, EMBEDDED, TOP-LEVEL, or fixnum.
  (native-window-title? nil)		; Window title, even if not visible.
  (native-window-icon? nil)		; Icon-designation
  (native-window-dock nil)		; Dock position
  (native-window-neighbor? nil)		; Dock neighbor handle
  (native-window-closeable t)
  (native-window-floatable nil)		; Never T unless type is PANE
  (native-window-autohidable nil)
  (native-window-draggable t)
  (native-window-saved-geom nil))	; (left top width height state style exstyle)

#+development
(defun print-native-window (native-window stream depth)
  (declare (ignore depth))
  (printing-random-object (native-window stream)
    (format stream "~a [~d] ~dx~d"
	    (type-name-of native-window)
	    (native-window-handle native-window)
	    (native-window-width native-window)
	    (native-window-height native-window))))

#+development
(defvar trace-native-windows nil)

#+development
(defun trace-native-window (event native-window &rest args)
  (when trace-native-windows
    (format t "~@(~10a~) ~s~{ ~s~}~%" event native-window args)))

(defun native-window-p (thing)
  (and (allocated-named-gensym-structure-p thing)
       (structure-type-p thing 'native-window)))

(defun initialize-native-window (native-window gensym-window handle class)
  (setf (native-window-gensym-window native-window) gensym-window
	(native-window-handle native-window) handle
	(native-window-class native-window) class)
  (graphics-push native-window (native-windows-on-gensym-window gensym-window))
  #+development (trace-native-window 'created native-window)
  native-window)

;;; The function `initialize-native-window-type' sets the windows type
;;; (container) and updates some dependent slots.

(defun initialize-native-window-type (native-window container)
  (when (and (native-window-parent? native-window)
 	     (not (eql (native-window-parent? native-window) 0)))
    (setq container 'embedded))
  (setf (native-window-type native-window) container
 	(native-window-style native-window) (default-native-window-style container)
 	(native-window-autohidable native-window) (eq container 'pane)
 	(native-window-floatable native-window) (eq container 'pane))
  container)

(def-structure-method clean-up-structure (native-window)
  #+development (trace-native-window 'destroyed native-window)
  (let ((gensym-window (native-window-gensym-window native-window)))
    (current-system-case
      (ab (reclaim-if-evaluation-item-reference (native-window-icon? native-window))))
    (setf (native-window-icon? native-window) nil)
    (when (native-window-parent? native-window)
      (reclaim-32bit-integer (native-window-parent? native-window))
      (setf (native-window-parent? native-window) nil))
    (when (text-string-p (native-window-title? native-window))
      (reclaim-text-string (native-window-title? native-window))
      (setf (native-window-title? native-window) nil))
    (setf (native-windows-on-gensym-window gensym-window)
	  (delete-graphics-element native-window (native-windows-on-gensym-window gensym-window)))
    (setf (native-window-gensym-window native-window) nil
	  (native-window-handle native-window) -1)
    (reclaim-gensym-list (native-window-saved-geom native-window))
    (setf (native-window-saved-geom native-window) nil)
    native-window))

;; Used to make "stub" windows on TW, solely to map handle<->index.
(defun make-basic-native-window (gensym-window handle index? class container)
  (let ((native-window (make-native-window-1)))
    (initialize-native-window native-window gensym-window handle class)
    (setf (native-window-index? native-window) index?
	  (native-window-type native-window) container)
    native-window))

(defmacro do-native-windows ((var gensym-window) &body body)
  `(loop for ,var in (native-windows-on-gensym-window ,gensym-window)
	 do (progn ,@body)))


;; This may return NIL when an image-plane is deleted and there are queued ICP
;; events referring to it. We always know when a handle is stale because handles
;; are never reused within one invocation of G2.

(defun find-native-window-by-handle (gensym-window handle?)
  (when (and handle? (>f handle? 0))
    (do-native-windows (nw gensym-window)
      (when (eql (native-window-handle nw) handle?)
	(return-from find-native-window-by-handle nw)))))

(defun find-native-window-by-index (gensym-window index?)
  (when (and index? (>=f index? 0))
    (do-native-windows (nw gensym-window)
      (when (eql (native-window-index? nw) index?)
	(return-from find-native-window-by-index nw)))))

(defun reclaim-native-window (native-window?)
  (when native-window?
    (clean-up-structure native-window?)
    (reclaim-structure native-window?)))

(defun reclaim-native-windows (native-windows)
  (loop for native-window in native-windows
	do (reclaim-native-window native-window)))

(defun reclaim-native-window-by-handle (gensym-window handle)
  (let ((native-window? (find-native-window-by-handle gensym-window handle)))
    (when native-window?
      (reclaim-native-window native-window?))))

(defun set-native-window-x-scroll (native-window pos?)
  (setf-bits (native-window-style native-window) ws-hscroll pos?)
  (setf (native-window-x-scroll? native-window) pos?))

(defun set-native-window-y-scroll (native-window pos?)
  (setf-bits (native-window-style native-window) ws-vscroll pos?)
  (setf (native-window-y-scroll? native-window) pos?))

(defun mdi-child-p (thing)
  (and (native-window-p thing)
       (eq (native-window-type thing) 'mdi-child)))

(defun top-level-window-p (thing)
  (and (native-window-p thing)
       (eq (native-window-type thing) 'top-level)))
  
(defun native-pane-p (thing)
  (and (native-window-p thing)
       (eq (native-window-type thing) 'pane)))

(defun floating-pane-p (thing)
  (and (native-pane-p thing)
       (eq (native-window-state thing) 'floating)))

(defun native-window-embedded-p (native-window)
  (or (eq (native-window-type native-window) 'embedded)
      (fixnump (native-window-type native-window))))

(defun native-window-container-type (native-window)
  (cond ((native-pane-p native-window)
	 'pane)
	((mdi-child-p native-window)
	 'mdi-child)
	((top-level-window-p native-window)
	 'top-level)
	((native-window-embedded-p native-window)
	 'embedded)
	(t
	 (native-window-type native-window))))

(def-substitution-macro native-window-right (native-window)
  (+r (native-window-left native-window)
      (native-window-width native-window)))

(def-substitution-macro native-window-bottom (native-window)
  (+r (native-window-top native-window)
      (native-window-height native-window)))

(def-substitution-macro native-window-maximized-p (native-window)
  (eq (native-window-state native-window) 'maximized))

(def-substitution-macro native-window-minimized-p (native-window)
  (eq (native-window-state native-window) 'minimized))

(defun native-window-center (native-window)
  (values (+f (native-window-left native-window)
	      (ashf (native-window-width native-window) -1))
	  (+f (native-window-top native-window)
	      (ashf (native-window-height native-window) -1))))

(defun save-native-window-geometry (native-window)
  (reclaim-gensym-list (native-window-saved-geom native-window))
  (setf (native-window-saved-geom native-window)
	(gensym-list (native-window-left native-window)
		     (native-window-top native-window)
		     (native-window-right native-window)
		     (native-window-bottom native-window)
		     (native-window-state native-window)
		     (native-window-style native-window)
		     (native-window-exstyle native-window))))

(defun native-window-workstation (native-window)
  (workstation-this-is-on (native-window-gensym-window native-window)))

(defun native-window-has-style (native-window style-bits)
  (=f (logandf (native-window-style native-window) style-bits)
      style-bits))

(defun default-native-window-style (type)
  (case type
    (mdi-child default-mdi-child-style)
    (top-level default-top-level-window-style)
    (pane      default-pane-window-style)
    (t         (logiorf ws-visible ws-child ws-clipsiblings))))

;; Munge the style according to user-supplied init options.
(defun process-window-style-options (style options)
  (loop for (property value) on options by #'cddr doing
    (case property
      (state
       (case value
	 (minimized (setf-bits style ws-minimize t))
	 (maximized (setf-bits style ws-maximize t))
	 (hidden    (setf-bits style ws-visible nil))))
      (visible
       (setf-bits style ws-visible value))
      (visible-caption
       (setf-bits style ws-caption value))
      (minimizeable
       (setf-bits style ws-minimizebox value))
      (maximizeable
       (setf-bits style ws-maximizebox value))
      (resizeable
       (setf-bits style ws-thickframe value))))
  style)

;; Passed directly to Win32 DrawText(). TODO: A set of flags, not an enum.
(defun encode-text-alignment (alignment)
  (case alignment
    (left dt-left)
    (center dt-center)
    (right dt-right)))

;;;; Native View


(def-structure (native-view                ; An abstract class, at least for now.
                 (:include native-window)
                 (:reclaimer NIL)
                 (:predicate NIL)
                 #+development (:print-function print-native-window))
  (native-view-callback? nil)		; Symbol or NIL
  (native-view-dialog-component? nil))	; dialog-component or NIL

(defun native-view-p (thing)
  (and (allocated-named-gensym-structure-p thing)
       (structure-type-p thing 'native-view)))

(def-structure-method clean-up-structure (native-view)
  (setf (native-view-callback? native-view) nil)
  (funcall-superior-method native-view))


;;;; Workspace View


;;; The `workspace-view' structure is a subclass of native-window used
;;; only for displaying image-planes.

(def-structure (workspace-view
		 (:include native-view)
		 (:reclaimer reclaim-workspace-view-1)
		 (:constructor make-workspace-view-1 ())
		 #+development (:print-function print-native-window))
  (native-window-image-plane? nil))

(defun make-workspace-view-structure (gensym-window handle)
  (let ((wsv (make-workspace-view-1)))
    (initialize-native-window wsv gensym-window handle 'g2-workspace-view)
    (initialize-native-window-type wsv 'mdi-child)
    wsv))

(def-substitution-macro native-image-plane? (native-window?)
  (and (workspace-view-p native-window?)
       (native-window-image-plane? native-window?)))

(defun compute-workspace-view-region (workspace-view)
  (declare (ignore workspace-view))
  (make-unbounded-region)
  ;; TODO: This enables server-side clipping, which we want, but which currently
  ;; breaks rapid fire IP inflates.
  #+ignore
  (make-region-from-rectangle
    (native-window-left workspace-view)
    (native-window-top workspace-view)
    (native-window-right workspace-view)
    (native-window-bottom workspace-view)))

;;; The function `construct-local-event-plist' returns a new gensym plist of the
;;; attributes for the current local event, stored down in C. Forward referenced
;;; by get-all-x11-events, and runs in both G2 and TW.

(defun construct-local-event-plist (native-window)
  (let* ((window-handle? (native-window-handle-for-last-event? native-window))
	 (native-window? (find-native-window-by-handle current-workstation-window window-handle?))
	 (tack-on-window-geometry?
	   (and native-window? (or (native-window-embedded-p native-window?)
				   (twaxl-window-p current-workstation-window)))))
    (nconc 
      (if window-handle?
	  (gensym-list 'window window-handle?))
      ;; FIXME: We add on the current native-window position as a workaround to
      ;; the problem that in TWAXL mode, our native-windows do not receive
      ;; WM_MOVE events. Of course, G2 will still get out of sync if the window
      ;; moves and no input events are sent. These properties are used in
      ;; absorb-local-event-ab-side-1, and have to not collide with those used
      ;; by decode-native-control-event -fmw, 1/20/04.
      (if tack-on-window-geometry?
	  (gensym-list 'left (c-x11-last-window-x (native-window-index? native-window?))
		       'top  (c-x11-last-window-y (native-window-index? native-window?))
		       'width (c-x11-window-width (native-window-index? native-window?))
		       'height (c-x11-window-height (native-window-index? native-window?)))))))

(defun native-window-type-for-type-code (type-code)
 (case (logandf type-code nip-wintype-mask)
   (#.nip-wintype-mdichild 'mdi-child)
   (#.nip-wintype-embedded 'embedded)
   (#.nip-wintype-toplevel 'top-level)
   (#.nip-wintype-pane 'pane)))

;;; The function `create-native-window-1' creates a workspace-view instance,
;;; dispatching to a local call or an ICP message. It will be assigned the given
;;; handle. Runs on *both* sides of the wire.

(defun create-native-window-1 (gensym-window type-code parent handle title style exstyle
					     x y width height options)
  (let ((native-window (make-workspace-view-structure gensym-window handle)))
    (setf (native-window-left native-window) x
	  (native-window-top native-window) y
	  ;; We might not achieve this size, depending on Win32 constraints.
	  (native-window-width native-window) width
	  (native-window-height native-window) height
	  (native-window-title? native-window) (copy-if-text-string title)
	  (native-window-style native-window) style
	  (native-window-exstyle native-window) exstyle
	  (native-window-parent? native-window) (unless (eql parent 0)
						  (copy-32bit-integer parent))
	  (native-window-type native-window) (native-window-type-for-type-code type-code))

    ;; These slots must be non-NIL if we have scroll bars.
    (when (/=f (logandf style ws-hscroll) 0)
      (setf (native-window-x-scroll? native-window) 0))
    (when (/=f (logandf style ws-vscroll) 0)
      (setf (native-window-y-scroll? native-window) 0))
    
    (case (type-of-gensym-window gensym-window)
      (x11-window
       (setf (native-window-index? native-window)
	     (c-x11-create-window type-code
				  (32bit-integer-high-part parent)
				  (32bit-integer-low-part parent)
				  handle title style exstyle
				  x y width height)))
      (icp
       (with-icp-window (gensym-window)
	 (send-icp-create-window gensym-window
				 type-code parent handle title style exstyle
				 x y width height options))))

    native-window))

;;; The function `compute-native-window-style' computes the type, style, and
;;; extended style integers given a symbol naming a native-frame-style.

(defun compute-native-window-style (gensym-window native-frame-style parent &optional options)
  (let* ((type nip-wintype-classic)	; Reset below.
	 (noframe? (eq native-frame-style 'none))
	 (framing (if noframe? 0
		      (logiorf ws-minimizebox ws-maximizebox ws-sysmenu
			       ws-caption ws-thickframe)))
	 (style ws-clipchildren)
	 (exstyle 0))
    (cond ((and parent (not (eql parent 0))) ; (embedded-window-p gensym-window)
	   (setq type nip-wintype-embedded
		 style (logiorf style ws-child ws-clipsiblings)))
	  ((mdi-frame-p gensym-window)
	   (setq type nip-wintype-mdichild
		 style (logiorf style ws-child ws-clipsiblings framing)))
	  ((eql parent 0)
	   (setq type nip-wintype-toplevel
		 style (logiorf style (if noframe? ws-popup ws-overlapped)
				framing)))
	  (t
	   (dwarn "Cannot compute style for native windows on ~s parent ~s"
		  gensym-window parent)))

    (case native-frame-style
      (hscroll (setq style (logiorf style ws-hscroll)))
      (vscroll (setq style (logiorf style ws-vscroll)))
      (bscroll (setq style (logiorf style ws-hscroll ws-vscroll))))

    ;; Munge the style according to user-supplied init plist.
    (setq style (process-window-style-options style options))
    (values type style exstyle)))

;;; The function `limit-native-window-size' adjusts the proposed edges for a
;;; native window if it would otherwise exceed the maximum allowed size.  Edges
;;; are adjusted so that the user gets the illusion that the native window
;;; really is that large. The illusion fades as soon as the window is moved,
;;; however (to be fixed).

(defun limit-native-window-size (gensym-window left top right bottom)
  (let ((maximum-width (maximum-window-width gensym-window))
	(maximum-height (maximum-window-height gensym-window))
	new-left new-right new-top new-bottom)
    (multiple-value-setq (new-left new-right)
      (limit-native-window-size-1
	left right
	maximum-width
	(left-edge-of-window gensym-window)
	(right-edge-of-window gensym-window)))
    (multiple-value-setq (new-top new-bottom)
      (limit-native-window-size-1
	top bottom
	maximum-height
	(top-edge-of-window gensym-window)
	(bottom-edge-of-window gensym-window)))
    (values new-left new-top new-right new-bottom)))

;; Helper function for one dimension. Written in terms of x but works for y, too.
(defun limit-native-window-size-1 (left right max-width window-left window-right)
  (let* ((width (-f right left))
	 (dx (-f width max-width)))
    (cond ((<=f dx 0))			              ; Proposed edges are OK.
	  ((<=f window-left left (1-f window-right))  ; Left edge visible: leave alone.
	   (decff right dx))
	  ((<=f window-left right (1-f window-right)) ; Right edge visible: leave alone
	   (incff left dx))
	  (t					      ; Both edges invisible: preserve that.
	   (let* ((window-width (-f window-right window-left))
		  (dw (-f max-width window-width)))
	     (setq left (-f window-left (halff dw))
		   right (+f window-right (halff dw))))))
    (values left right)))

;;; The function `manage-native-window-1' consolidates various operations on a
;;; native window into one routine and one ICP message.

(defun manage-native-window-1 (native-window? opcode left top right bottom plist)
  (when native-window?
    (let ((gensym-window (native-window-gensym-window native-window?)))
      (case (type-of-gensym-window gensym-window)
        (x11-window
          (let
             ((result (c-x11-manage-window opcode 
                                           (native-window-index? native-window?)
                                           left top right bottom
                                           (or (getf plist 'title) #w""))))
           ;; Gensym-129 fix
          (when (= opcode nip-destroy-window)
            (reclaim-native-window native-window?))
          (return-from manage-native-window-1 result)))
        (icp
	 (with-icp-window-if-needed (gensym-window)
	   (send-icp-manage-window gensym-window (native-window-handle native-window?)
				   opcode left top right bottom plist)))))))

;; Assuming not a pane.
(defun manage-native-window-locally (native-window property value)
  (let ((window-index (native-window-index? native-window)))
    (case property
      (title
       (when (wide-string-p value)
	 (c-x11-manage-window nip-caption-window window-index 0 0 0 0 value)))
      (closeable
       (c-x11-manage-window nip-set-closeable window-index (if value 1 0) 0 0 0 #w""))
      (icon
       (when (fixnump value)
	 (c-x11-manage-window nip-set-icon window-index value 0 0 0 #w""))))))

;;; The function `redirect-window-1' causes all drawing on gensym-window to go
;;; to the given native window, offset by dx, dy, regardless of the window
;;; supplied to the C drawing routines. Supply NIL for the native-window to
;;; revert to normal. This one must be called in an `on-window' context.

(defun redirect-window-1 (gensym-window native-window? dx dy)
  (let ((handle (if native-window? (native-window-handle native-window?) -1))
	(index (if native-window? (native-window-index? native-window?) -1)))
    (case (type-of-gensym-window gensym-window)
      (x11-window
       (progn 
       (c-x11-redirect-window index dx dy) nil))
      (icp
       ;; Notice no `with-icp-window' here.
       (send-icp-redirect-window gensym-window handle dx dy)))))

;;; The function `stack-native-windows-1' ensures that the given native windows
;;; are stacked in the given order, top to bottom. Instead of passing an array
;;; to C, we pass the elements one at a time, in order.

(defun stack-native-windows-1 (gensym-window handles)
  (case (type-of-gensym-window gensym-window)
    (x11-window
     (c-x11-stack-windows 1 (length handles) 0)	; Begin
     (loop with prev-index = -1
	   for handle in handles
	   as native-window? = (find-native-window-by-handle gensym-window handle)
	   as index? = (and native-window? (native-window-index? native-window?))
	   when index?
	     do (c-x11-stack-windows 2 prev-index index?) ; Stack
		(setq prev-index index?))
     (c-x11-stack-windows 3 0 0))	; End
    (icp
     (with-icp-window (gensym-window)
       (send-icp-stack-windows gensym-window handles)))))

(defun scroll-native-window-1 (gensym-window native-window? dx dy)
  (when native-window?
    (case (type-of-gensym-window gensym-window)
      (x11-window
       (progn 
       (c-x11-scroll-window (native-window-index? native-window?) dx dy) nil))
      (icp
       (with-icp-window (gensym-window)
	 (send-icp-scroll-window gensym-window (native-window-handle native-window?) dx dy))))))

(defun manage-scrollbars-1 (gensym-window native-window? xmin xpos xmax ymin ypos ymax)
  (when native-window?
    (set-native-window-x-scroll native-window? (if (>f xmax xmin) xpos))
    (set-native-window-y-scroll native-window? (if (>f ymax ymin) ypos))
    (case (type-of-gensym-window gensym-window)
      (x11-window
       (c-x11-manage-scrollbars (native-window-index? native-window?)
				xmin xpos xmax ymin ypos ymax))
      (icp
       (unless (and (native-window-minimized-p native-window?)
		    (not (window-supports-scroll-while-minimized-fix gensym-window)))
	 (with-icp-window (gensym-window)
	   (send-icp-manage-scrollbars gensym-window (native-window-handle native-window?)
				       xmin xpos xmax ymin ypos ymax)))))))

(defun mega-refresh-1 (gensym-window)
  (case (type-of-gensym-window gensym-window)
    (x11-window
     (c-x11-mega-refresh))
    (icp
     (with-icp-window (gensym-window)
       (send-icp-mega-refresh gensym-window)))))


(def-icp-message-type create-window ((gensym-window gensym-window)
				     (fixnum type)
				     (32bit-integer parent) ; Ignored unless embedded
				     (fixnum handle)        ; Pre-assigned by G2 (yahm)
				     (wide-string title)
				     (fixnum style)
				     (fixnum exStyle)
				     (fixnum x)	            ; Geometry ignored if embedded
				     (fixnum y)
				     (fixnum width)
				     (fixnum height)
				     (icp-tree options))
  (create-native-window-1 gensym-window type parent handle
			  title style exStyle x y width height options)
  (reclaim-32bit-integer parent)
  (reclaim-icp-tree-with-text-strings options)
  (reclaim-wide-string title))

(def-icp-message-type manage-window ((gensym-window gensym-window)
				     (fixnum handle) ; NOT the window-index
				     (fixnum opcode)
				     (fixnum x)
				     (fixnum y)
				     (fixnum width)
				     (fixnum height)
				     (icp-tree options))
  (manage-native-window-1 (find-native-window-by-handle gensym-window handle)
			  opcode x y width height options)
  (reclaim-icp-tree-with-text-strings options))

(def-icp-message-type redirect-window ((gensym-window gensym-window)
				       (fixnum handle)
				       (fixnum dx)
				       (fixnum dy))
  (redirect-window-1 gensym-window (find-native-window-by-handle gensym-window handle) dx dy))

(def-icp-message-type stack-windows ((gensym-window gensym-window)
				     (list-of-unsigned-integers handles))
  (stack-native-windows-1 gensym-window handles))

(def-icp-message-type scroll-window
    ((gensym-window gensym-window) (fixnum handle)
     (fixnum dx) (fixnum dy))
  (scroll-native-window-1 gensym-window (find-native-window-by-handle gensym-window handle) dx dy))

(def-icp-message-type manage-scrollbars
    ((gensym-window gensym-window) (fixnum handle)
     (fixnum xmin) (fixnum xpos) (fixnum xmax)
     (fixnum ymin) (fixnum ypos) (fixnum ymax))
  (manage-scrollbars-1 gensym-window (find-native-window-by-handle gensym-window handle)
		     xmin xpos xmax ymin ypos ymax))

(def-icp-message-type mega-refresh ((gensym-window gensym-window))
  (mega-refresh-1 gensym-window))


(def-gensym-c-function c-x11-create-window
    (:pointer "g2ext_x11_create_window")
  ((:fixnum-int type)			; Some args are ignored, depending on type.
   (:fixnum-int parent-hi)		; High 16 bits of parent hwnd
   (:fixnum-int parent-low)		; Low 16 bits.
   (:fixnum-int handle)
   (:wide-string title)
   (:fixnum-int style)			; High 16 bits of Win32 style
   (:fixnum-int exStyle)		; Win32 extended style
   (:fixnum-int x)
   (:fixnum-int y)
   (:fixnum-int width)
   (:fixnum-int height)))

(def-gensym-c-function c-x11-manage-window
    (:pointer "g2ext_x11_manage_window")
  ((:fixnum-int opcode)
   (:fixnum-int window-index)
   (:fixnum-int x)
   (:fixnum-int y)
   (:fixnum-int width)
   (:fixnum-int height)
   (:wide-string string)))

(def-gensym-c-function c-x11-stack-windows
    (:pointer "g2ext_x11_stack_windows")
  ((:fixnum-int opcode)			; 1=begin, 2=stack, 3=done
   (:fixnum-int previous-window-index-or-count)
   (:fixnum-int window-index)))

(def-gensym-c-function c-x11-redirect-window
    (:void "g2ext_redirect_window")
  ((:fixnum-int window-index)
   (:fixnum-int dx)
   (:fixnum-int dy)))

(def-gensym-c-function c-x11-scroll-window
    (:void "g2ext_scroll_window")
  ((:fixnum-int window-index)
   (:fixnum-int dx)
   (:fixnum-int dy)))

(def-gensym-c-function c-x11-manage-scrollbars
    (:fixnum-int "g2ext_manage_scrollbars")
  ((:fixnum-int window-index)
   (:fixnum-int xmin)			; Positions in pixels.
   (:fixnum-int xpos)
   (:fixnum-int xmax)
   (:fixnum-int ymin)
   (:fixnum-int ypos)
   (:fixnum-int ymax)))

(def-gensym-c-function c-x11-mega-refresh
    (:fixnum-int "g2ext_mega_refresh")
  ())

(def-gensym-c-function c-x11-tell-control-our-session-id
    (:fixnum-int "g2ext_x11_tell_control_our_session_id")
  ((:fixnum-int session-id)))

(defconstant-for-case editor-set-breakpoints 23)

(defconstant-for-case editor-show-completions 57)

(defconstant editor-disabled-breakpoint-flag #.(ash 1 20)) ; Flag bit in line number

(defun manage-native-editor (native-window opcode &optional string? caret? arg?)
  (let ((gensym-window (native-window-gensym-window native-window)))
    (with-icp-window (gensym-window)
      (send-icp-manage-editor gensym-window opcode (native-window-handle native-window)
			      (or string? #w"") (or caret? 0) arg?))))

(defun editor-show-completions-1 (handle menus)
  (c-manage-editor editor-clear-output handle #w"" 0 0)
  (loop with any
	for menu in menus
	as style = editor-style-category then editor-style-completion
	doing
    (when any
      (c-manage-editor editor-append-output handle #w"\u2028" 0 0))
    (loop for string in menu
	  as first = t then nil
	  doing
      (unless first
	(c-manage-editor editor-append-output handle #w"   " 0 0))
      (c-manage-editor editor-append-output handle string style 0)
      (setq any t))))

(def-icp-message-type manage-editor
    ((gensym-window gensym-window)
     (fixnum opcode)
     (fixnum handle)
     (wide-string string)
     (fixnum number)
     (icp-tree arg))
  gensym-window
  (case opcode
    (#.editor-set-breakpoints
     (let ((bkpts (fixnum-list-to-word-vector arg)))
       (c-manage-editor opcode handle bkpts number 0)
       (reclaim-byte-vector-16 bkpts)))
    (#.editor-show-completions
     (when (listp arg)
       (editor-show-completions-1 handle arg)))
    (#.editor-cancel
     (c-manage-editor opcode handle string number arg))
    (#.editor-exit-new
     (c-manage-editor opcode handle string number arg))
    (t
     (c-manage-editor opcode handle string number (if (fixnump arg) arg 0))))
  (reclaim-wide-string string)
  (reclaim-icp-tree-with-text-strings arg))

(def-gensym-c-function c-manage-editor
    (:fixnum-int "g2ext_manage_editor")
  ((:fixnum-int opcode)
   (:fixnum-int handle)
   (:wide-string string)
   (:fixnum-int number)
   (:fixnum-int other-number)))

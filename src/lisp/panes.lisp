;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module PANES: A "Window Manager" and Related Facilities

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Lowell B. Hawkinson and Ben Hyde





(declare-forward-references
  (sketch-image-plane                            function draw)
  (refresh-title-bar                             function draw)
  (workspace-title                               function draw)

  (paint-background-of-image-plane               function draw)
  (paint-contents-of-image-plane                 function draw)
  (paint-region-of-image-plane-overlapping-block function draw)
  (make-region-from-block-edges                  function draw)

  (lookup-frame-description-reference-of-block?  function draw)
  (purpose-of-extreme-edges                      variable draw)
  (determine-extreme-edges-of-block              function draw)
  (create-frame-transforms-of-image-plane        function draw)
  (make-workspace-background-spot-function       function draw)
  (local-edges-of-block                          function draw)
  (new-g2-classic-ui-p                           variable draw)

  (draw-overlapping-blocks                       function connect3a)
  (draw-blocks-overlapping-connection            function connect3a)
  (draw-overlapping-xor-blocks                   function draw)

  (render-connection-in-xor-overlay-p-function   function connect1)
  (build-spacial-index                           function connect3a)
  (destroy-spacial-index                         function connect3a)
;  (invalidate-overlapping-cache-for-entire-workspace   function connect3a)
  (blocks-touching-region-of-image-plane         function connect3a)
  (add-thing-to-spacial-index                    function connect3a)
  (remove-thing-from-spacial-index               function connect3a)
  (recompute-layer-positions               function connect3a)
  (bounding-region-of-block-or-connection function connect3a)

  #+development (compute-changed-blocks-of-workspace   function connect3a)
  (local-edges-of-block-or-connection    function connect3a)
  
  (note-kb-state-change                      function kb-save2)

  (current-workstation-window                variable telestubs)
  (global-table-of-attributes-pane           variable commands1)
  (global-table-of-hidden-attributes-pane    variable commands1)

  (push-more-detailed-spot                   function workstation)
  (push-last-spot                            function workstation)
  (remove-image-plane-pointers-in-workstation-event-queue function workstation)
  (force-process-drawing                     function workstation)
  (force-workstation-drawing                 function workstation)

  (reclaim-image-plane-cursors               function moves)
  (add-cursors-to-current-window             function moves)
  (erase-and-reclaim-all-selection-highlights function moves)
  (trigger-user-icon-movement-rules-for-blocks function moves)

  (printing-p                                function printing)

  (drawing-for-eyes-of-player-p              function player)

  (event-update-status-of-cell-array-showing function cells)
  (the-only-dynamic-computation-style variable cells)
  (update-trend-chart-for-exposure           function graphs) 

  (draw-selected-regions-of-block      function entities)
  (adjust-icon-rendering-usage-counts function entities)

  (get-total-title-bar-text-width function) ; boxes


  (get-workspace-of-block-or-connection function)

  (workspace-showing-on-ui-client-p function view-g2)

  (maybe-schedule-task-to-run-propagate-all-workspace-changes-to-image-planes function workstation)

  (ensure-native-window-item function workstation)
  (synchronize-native-window-item function workstation)
  (delete-native-window-item function workstation)

  (note-workspace-hidden function)
  (%select-image-plane function)
  (selectable-image-plane-p function))	; COMMANDS0


;; Selection
(declare-forward-reference reclaim-selection function)
(declare-forward-reference remove-as-selected-image-plane function)
(declare-forward-reference selection-enabled-p function)
(declare-forward-reference select-topmost-workspace function)

(declare-forward-reference image-plane-selection-non-empty-p function)
(declare-forward-reference show-selection-handles-p function)
(declare-forward-reference selection-handle-radius variable)
(declare-forward-reference draw-selection-handles-for-current-image-plane function)
(declare-forward-reference image-plane-selected-p function)

;; Native frame styles
(declare-forward-reference workspace-title-bar-frame-style-small variable)
(declare-forward-reference workspace-title-bar-frame-style-large variable)

(declare-forward-reference warp-mouse-to-center-of-workstation-window function)

;; Native Editor
(declare-forward-reference prefer-native-editor-p function)     ; EDIT1
(declare-forward-reference set-up-native-editor function)	; COMMANDS2

;; Views API
(declare-forward-reference note-native-window-event function) ; COMMANDS2
(declare-forward-reference manage-pane-1 function)
(declare-forward-reference send-native-icon function)
(declare-forward-reference update-icon-views function)
(declare-forward-reference copy-icon-designation function)
(declare-forward-reference stored-callback-procedure function)

;;;; Debugging


(defvar trace-drawing-for-build nil)

(defmacro with-drawing-trace-for-build (() &body body)
  `(when trace-drawing-for-build
     ,@body))


;;; The defparameter `kinds-of-draw-tracing' is a list of (name doc
;;; {variable}).

#+development
(defparameter-for-macro kinds-of-draw-tracing
  '((t			"Trace everything")
    (task 		"Detailed drawing-task queueing")
    (add-task 		"Even more")
    (discard-task       "Full refresh optimization")
    (sked 		"Drawing schedule")
    (wks 		"Workstation")
    (block 		"?")
    (xor 		"XOR drawing")
    (service-workstation "Each call to service-workstation.")
    (time-slice 	"Time slice expiration")
    (bleeding 		"Use of bleeding hack.")
    (kb 		"Queueing of KB drawing tasks.")
    (pop 		"Dequeueing of drawing tasks")
    (show-regions 	"Outlines each inval region.")
    (cache 		"The overlap cache.")
    (graphic-element 	"All graphic elements")
    (queue 		"?")
    (single-step 	"Flush and pause lisp")
    (draw-block 	"Every draw-block")
    (connections 	"Parts of connection drawing")
    (index 		"Spacial index")
    (text 		"Parts of text boxes")
    (merge 		"Queue merges.")
    (events		"Workstation events" trace-workstation-events)
    (local-events       "Local events" trace-local-events)
    (sync 		"X Syncs" trace-xsync)
    (icp 		"ICP Messages" trace-icp-messages)
    (icp-bytes 		"Outstanding ICP bytes")
    (backtrace		"Include backtrace with each printout")
    (times              "Include timestamps with each printout")
    (player		"The Player")
    (run-event          "Run-event-handler generic command hacking")
    (menu               "Menu construction")
    (config             "Event lookup in item configuration")
    (config+            "Include non-matches in the config lookup")
    (spots              "Spot generation")
    (keymap             "Keymap searches")
    (project-frame      "Components of workspace frames")
    (event-q            "Enqueueing workstation events")
    (pick               "Picking rectangle for find-object-near-mouse"
     testing-mouse-track-distances-for-development?)
    (mouse-tracking     "Eg, finding the object under the mouse" trace-mouse-tracking-p)
    (icp-buffering      "Number of bytes in ICP buffers, and ICP bandwidth")
    (mouse-cache        "The cache for find-object-near-mouse")))

#+development
(defun-for-macro note-kind-of-drawing-trace (kind)
  (unless (member kind kinds-of-draw-tracing :key #'car)
    (push (list kind "??") kinds-of-draw-tracing)))

#+development
(defvar trace-drawing nil)

#+development
(defmacro trace-drawing (&rest kinds)
  `(trace-drawing-1 ',(mapcar #'unquote kinds) t))

#+development
(defmacro untrace-drawing (&rest kinds)
  `(trace-drawing-1 ',(mapcar #'unquote kinds) nil))

#+development
(defun trace-drawing-1 (kinds trace-p)
  (flet ((doc ()
	   (format t ";;; Kinds of drawing trace: ~{~<~%;;;~:; ~A~>~^,~}.~%"
		   (mapcar 'car kinds-of-draw-tracing))
	   (format t ";;; Do (trace-drawing :help) for more info.~%")
	   (values))
	 (help ()
	   (format t "~&(Do (untrace-drawing) to turn this off.)")
	   (loop for (name doc) in kinds-of-draw-tracing doing
	     (format t "~&~s~25t~a" name doc))
	   (values))
	 (cur ()
	   (format t ";;; Currently traced: ~{~<~%;;;~:; ~A~>~^,~}."
		   (cond ((null trace-drawing)
			  '("nothing"))
			 ((eq trace-drawing t)
			  '("everything"))
			 (t
			  trace-drawing)))
	   (values)))
    (cond ((equal kinds '(:help))
	   (HELP))
	  ((and (null kinds) trace-p)
	   (DOC) (CUR))
	  ((and (not (null kinds))
		(set-difference kinds (mapcar 'car kinds-of-draw-tracing)))
	   (format t "Unknown kind of draw tracing ~S~%"
		   (set-difference kinds (mapcar 'car kinds-of-draw-tracing)))
	   (DOC))
	  (t
	   (dolist (kind (or kinds '(t)))
	     (trace-kind-of-drawing kind trace-p))
	   trace-drawing))))


#+development
(defun trace-kind-of-drawing (kind trace-p)
  (cond ((eq kind 't)
	 (setq trace-drawing trace-p)
	 (loop for (name doc var?) in kinds-of-draw-tracing
	       when var?
		 do (set var? trace-p)))
	(t
	 (if trace-p
	     (pushnew kind trace-drawing)
	     (setq trace-drawing (remove kind trace-drawing)))

	 ;; Special cases controlled by other defvars.
	 (let ((var? (third (assoc kind kinds-of-draw-tracing))))
	   (when var?
	     (set var? trace-p))))))


#+development
(defvar interesting-block-for-drawing nil)


#+development
(defun trace-drawing-print (closure &optional kind interesting-block)
  (when (or (null interesting-block-for-drawing)
	    (null interesting-block)
	    (eq interesting-block-for-drawing interesting-block))
    (when (or (eq trace-drawing t) (memq 'backtrace trace-drawing))
      (format t "~s " (make-lisp-backtrace)))

    (when (or (eq trace-drawing t) (memq 'times trace-drawing))
      (format t "~6d ~4d " (get-fixnum-time t) (time-since-last-call)))

    ;; Indent by lcl:*trace-level* ?
    (format t "[~a] " kind)
    (funcall closure)
    (fresh-line)
    (force-output)))

;; All the draw tracing passes thru this function, so that we could save output
;; into a string, etc.



(defmacro trace-drawing-kind-active-p (kind)
  `(or (eq trace-drawing t)
       (memq ,kind trace-drawing)))


(defmacro with-drawing-trace ((kind &optional interesting-block) &body body)
  #-development (declare (ignore kind interesting-block body))
  #+development
  (progn
    (note-kind-of-drawing-trace kind)
    `(when (trace-drawing-kind-active-p ',kind)
       (trace-drawing-print #'(lambda () ,@body) ',kind ,interesting-block))))


#+development
(defun print-time-slice (&optional (label ""))
  (format t "~aTime slice: ~d/~dms,  expired-p = ~s~%"
	  label
	  (fixnum-time-difference (get-fixnum-time) time-slice-start-time)
	  maximum-time-slice-size
	  (time-slice-expired-p)))

#+development
(defun debug-map-color (color)
  (cond ((integerp color)
	 color)
	(t
	 (on-window-without-drawing ((window-for-workstation (first workstations-in-service)))
	   (map-to-color-value color)))))

#+development
(defun debug-map-drawing-mode (mode)
  (case mode
    (paint x11-copy)
    (xor x11-xor)
    (t (if (numberp mode) mode x11-copy))))


#+development
(defun draw-rectangle-1 (left top right bottom &key
			      (color 'black)
			      (mode 'paint)
			      filled
			      (window (native-window? system-window)))
  (let ((width (- right left))
	(height (- bottom top))
	(color (debug-map-color color))
	(mode (debug-map-drawing-mode mode)))

    (when (eql mode x11-xor)
      (setq color (color-difference color (if (boundp 'current-background-color-value)
					      current-background-color-value
					      (debug-map-color 'black)))))

    (cond (filled
	   (c-x11-draw-rectangle
	     window
	     left top width height
	     color mode))
	  (t
	   (c-x11-draw-rectangle
	     window
	     left top width 1
	     color mode)
	   (c-x11-draw-rectangle
	     window
	     left (-f bottom 1) width 1
	     color mode)

	   (c-x11-draw-rectangle
	     window
	     left top 1 height
	     color mode)
	   (c-x11-draw-rectangle
	     window
	     (-f right 1) top 1 height
	     color mode)))))


#+development
(defun outline-draw-area (&key (color 'green) (mode 'paint)
			      (window (native-window? system-window)))
  (draw-rectangle-1 left-edge-of-draw-area
		    top-edge-of-draw-area
		    right-edge-of-draw-area
		    bottom-edge-of-draw-area
		    :color color
		    :mode mode
		    :window window))
    
  
#+development
(defun outline-region-of-window (region &key (color 'green)
					relative (x0 10) (y0 10) (mode 'paint)
					(window (native-window? system-window)))
  ;; region is window coordinates
  (let ((color (debug-map-color color))
	(mode (debug-map-drawing-mode mode)))

    (multiple-value-bind (left-1 top-1)
	(region-bounding-rectangle region)
      (let ((dx (if relative (- x0 left-1) 0))
	    (dy (if relative (- y0 top-1) 0)))

	;; Don't draw interior edges.
	(do-region-rectangles ((left top right bottom) region)
	  (draw-rectangle-1 (+ left dx)
			    (+ top dy)
			    (+ right dx)
			    (+ bottom dy)
			    :window window
			    :color color
			    :mode mode))

	(flush-graphics-on-native-window window)
	nil))))




;;;; Drawing priority and queue draining





;;; The defvar `drawing-is-locked?' is bound to T to inhibit any
;;; draining of drawing queues while the KB may be in some
;;; unstable intermediate state.  For example, when the editor
;;; updates and dehighlights a slot.

(defvar drawing-is-locked? nil)

(def-substitution-macro work-on-drawing-for-workstation (workstation)
  (work-on-drawing-window (window-for-workstation current-workstation) nil))


;;; The function `drain-current-workstation-drawing-queue' flushes all the
;;; drawing queues for the current workstation.  It should not be called in an
;;; on-window context, but must be in a for-workstation context.

(defun drain-current-workstation-drawing-queue ()
  (with-unlimited-time-slice
    (work-on-drawing-window (window-for-workstation current-workstation)
			    nil)))


;;; The function `drain-current-window-drawing-queue' does the same thing, but
;;; within an on-window context.

(defun drain-current-window-drawing-queue ()
  ;; First pull down any pending workspace changes.
  (check-for-pending-drawing-on-window current-window)

  ;; Then drain all of the pane and image-plane queues.
  (with-raw-window-transform-and-draw-area (current-window)
    (with-transfer-mode-when-drawing ((drawing-transfer-mode-of-current-window))
      (with-unlimited-time-slice
	(work-on-drawing-current-window)))))

;; Draining must happen in the top-level window clipping environment, since we
;; may be called below update-window, which has narrowed the draw area.  -fmw,
;; 12/8/94

;; Draining must also happen in the top-level drawing mode.  We may be called
;; below update-window, which has narrowed the draw area, or below any random
;; function which has rebound the drawing mode.  Since we are already on-window
;; here, we have to use the "network-transparent" way of binding the drawing
;; mode, to wit, with-transfer-mode-when-drawing. -fmw, 2/7/95


;;; The function `force-current-window-drawing-if-appropriate' completely
;;; drains the drawing queues associated with the current window, and flushes
;;; all drawing to the screen, if drawing is immediate.  It must be called in
;;; an on-window context.

(defun force-current-window-drawing-if-appropriate ()
  (within-named-dynamic-extent on-window-with-drawing
    (when (draw-as-soon-as-possible?)
      (with-temporary-profiling-context redraw
	(drain-current-window-drawing-queue)
	;; Do an XSync, too.
	(sync-graphics-on-current-window)))))



;;; The function `force-window-drawing' forces drawing for the given window.
;;; It must be called outside of any on-window context.

(defun force-window-drawing (gensym-window)
  (update-window gensym-window
		 (left-edge-of-window gensym-window)
		 (top-edge-of-window gensym-window)
		 (right-edge-of-window gensym-window)
		 (bottom-edge-of-window gensym-window)
		 'drain-current-window-drawing-queue))


(defun work-on-current-image-plane-and-sync ()
  (work-on-drawing-schedule-of-current-image-plane)
  (unless (and (icp-window-p current-window)
	       (=f (icp-connection-state current-icp-socket) icp-connection-closed))
    (sync-graphics-on-current-window)))



;;; The function `force-some-workspace-drawing' works on drawing the given
;;; workspace until the current time slice expires.

(defun force-some-workspace-drawing (workspace sync-too?)
  (when (pending-drawing-for-workspace-p workspace)

    ;; Pull down workspace changes, if any.
    (check-for-pending-drawing-on-workspace workspace)

    (map-drawing-over-image-planes
      workspace
      workspace
      (left-edge-of-block workspace)
      (top-edge-of-block workspace)
      (right-edge-of-block workspace)
      (bottom-edge-of-block workspace)
      :no-bleeding

      (if sync-too?
	  'work-on-current-image-plane-and-sync
	  'work-on-drawing-schedule-of-current-image-plane))))



;;; The function `force-workspace-drawing' drains just the drawing queues
;;; associated with image-planes showing the workspace. It does not drain the
;;; pane drawing queue, so should only be used when it is known that only the
;;; workspace contents could have changed.  It does flush the graphics to the
;;; underlying window system.

(defun force-workspace-drawing (workspace)
  ;; Look ahead to see if we really have anything to do.
  (when (pending-drawing-for-workspace-p workspace)
    (with-unlimited-time-slice
      (force-some-workspace-drawing workspace t))))




(defun force-workspace-drawing-if-appropriate (workspace)
  (when (or (draw-as-soon-as-possible?)
	    flush-graphics-immediately?)
    (propagate-workspace-changes-to-image-planes workspace)
    (force-workspace-drawing workspace)))

;; flush-graphics-immediately? causes us to flush the X buffers, in addition to
;; flushing G2's buffers.




(defmacro with-drawing-options ((&key deferred inval-preferred)
				&body body)
  `(let ((current-drawing-priority
	   (if ,deferred ':draw-as-late-as-possible current-drawing-priority))
	 (region-invalidation-is-preferred
	   (if ,inval-preferred t region-invalidation-is-preferred)))
     ,@body))


;;; The macro `with-deferred-drawing' forces drawing to be scheduled within
;;; its body. (Unless overriden by XOR, etc.).  If a workspace is given,
;;; the drawing queue for 

(defmacro with-deferred-drawing (() &body body)
  `(let ((current-drawing-priority ':draw-as-late-as-possible))
     ,@body))



;;; The macro `with-locked-drawing' inhibits any forcing of the drawing queues.
;;; This prevents queue draining while the KB is in some inconsistent intermediate
;;; state.  For example, the editor uses this when updating and dehighlighting
;;; an attribute.  It is a no-op in XOR mode.

(defmacro with-locked-drawing (() &body body)
  `(let ((current-drawing-priority (if (paint-mode-p)
				       ':draw-as-late-as-possible
				       current-drawing-priority)) ; noop case
	 (drawing-is-locked? (if (paint-mode-p)
				 t
				 drawing-is-locked?)))
     (progn ,@body)
     (when (eq drawing-is-locked? 'force)		    ; Set by a nested FORCE-process-drawing
       (let ((drawing-is-locked? nil))
	 (force-process-drawing)))))




;;; `With-deferred-drawing-in-current-window' binds the current-drawing-priority
;;; to assure that drawing is deferred, and then upon exit will drain that
;;; drawing if the original binding requires this.  This is used to batch up a
;;; bit of drawing and hence reduce flicker.  This must be called within the
;;; on-window-with-drawing context.

(defmacro with-deferred-drawing-in-current-window (() &body body)
  `(progn
     (with-deferred-drawing ()
       ,@body)
     (force-current-window-drawing-if-appropriate)))



;;; `with-updating-that-requires-the-draw-function-be-used' this function creates
;;; a dynamic extent within which calls to update images must invoke the
;;; draw-function in spite of scheduling or transfer mode.  This is used
;;; for places where the client of update-images has not yet been
;;; reworked so that the update can be defered using an invalidate of the
;;; draw area's rectangle.

;;; For example graphs must update and blit their incremental updates to
;;; graph rasters immediately since otherwise the update to their raster
;;; is lost.

(defmacro with-updating-that-requires-the-draw-function-be-used (&body body)
  `(let ((changing-colors-of-graphic-elements? t))
     ,@body))

;; This is only useful if you go into XOR mode as well?
;; This must flush any pending drawing, at least of this image-plane.
;; Should this take an image-plane argument?







;;; `With-deferred-drawing-in-process' will suppress the drawing over it's
;;; dynamic extent for the entire process.  If on exit it returns to
;;; :draw-as-soon-as-possible mode it will drain the drawing Qs for in all
;;; windows.  This is slightly different from a N window version of
;;; with-deferred-drawing-in-current-window in that it will notice any pending
;;; reshape events as well.  This must be called outside of an
;;; on-window-without-drawing-context.

(defmacro with-deferred-drawing-in-process ((&key (force-drawing-at-end
						    '(eq current-drawing-priority :draw-as-soon-as-possible)))
					    &body body)
  `(progn
     (with-deferred-drawing ()
       ,@body)
     (when ,force-drawing-at-end
       (force-process-drawing))))


(def-substitution-macro time-slice-unlimited-p ()
  (=f maximum-time-slice-size most-positive-fixnum))


(defparameter drawing-max-outstanding-icp-bytes 20000)

;; A huge number for now, to mostly disable the feature.


;;; The system-variable `extra-time-for-drawing' is NIL or a fixnum time
;;; difference to add to drawing's time slice.

(def-system-variable extra-time-for-drawing panes nil)


;;; The substitution-macro `time-slice-for-drawing-expired-p' returns T if
;;; drawing's time slice has expired, including any extra time we've been
;;; allotted.

(defun-substitution-macro time-slice-for-drawing-expired-p ()
  (and (<f maximum-time-slice-size most-positive-fixnum)
       (let ((maximum-time-slice-size (+f maximum-time-slice-size
					  (or extra-time-for-drawing 0))))
	 (time-slice-expired-p))))


;;; The macro `drawing-time-slice-expired-p' is true when the current time
;;; slice allocated for drawing has expired, or, for ICP windows, when
;;; too many bytes of data are outstanding.

(defun-substitution-macro drawing-time-slice-expired-p ()
  (or (time-slice-for-drawing-expired-p)
      (and (not (time-slice-unlimited-p)) ; Means we are not allowed to return early.
	   (icp-window-p current-window)
	   (or (=f (icp-connection-state current-icp-socket) icp-connection-closed)
	       (let ((info (i-am-alive-info? current-icp-socket)))
		 (and info
		      (if (drawing-is-scheduled?)
			  (icp-port-blocked? (icp-output-port current-icp-socket))
			  (>=f (number-of-outstanding-icp-bytes info)
			       drawing-max-outstanding-icp-bytes))))))))

(defun-substitution-macro drawing-blocked-p ()
  (and (not (time-slice-unlimited-p)) ; Means we are not allowed to return early.
       (icp-window-p current-window)
       (let ((info (i-am-alive-info? current-icp-socket)))
	 (and info
	      (drawing-is-scheduled?)
	      (icp-port-blocked? (icp-output-port current-icp-socket))))))

(defun-simple gensym-window-drawing-blocked-p (gensym-window)
  (and (not (time-slice-unlimited-p)) ; Means we are not allowed to return early.
       (icp-window-p gensym-window)
       (let* ((icp-output-port? (icp-output-port-for-window? gensym-window))
	      (parent-socket?
		(and icp-output-port?
		     (parent-icp-socket icp-output-port?)))
	      (info (and parent-socket?
			 (i-am-alive-info? parent-socket?))))
	 (and info
	      (drawing-is-scheduled?)
	      (icp-port-blocked? icp-output-port?)))))



;;; The macro `with-zero-drawing-time' runs body and then increments
;;; extra-time-for-drawing by the amount of time taken to run body.  This
;;; effectively runs body without charging its time to the current time slice.
;;; extra-time-for-drawing must be initially let-bound to 0 at the beginning of
;;; the time slice for this macro to have any affect.

(defmacro with-zero-drawing-time (&body body)
  (avoiding-variable-capture (&aux start-time)
    `(let ((,start-time (get-fixnum-time)))
       (prog1
	   (progn ,@body)
	 (when extra-time-for-drawing
	   (incff extra-time-for-drawing
		  (fixnum-time-difference (get-fixnum-time) ,start-time)))))))



;;;; Gensym Window Geometry



;;; A gensym window is divided up into any number of non-overlapping,
;;; rectangular panes (see `pane-area-hack').  On each pane is a stack of one or
;;; more image planes.  An image plane may have on it a rectangular image of a
;;; workspace.  An image on an image plane occludes images on planes that are
;;; deeper down in its stack.  See below for further details.

;;; The term `area' is used to refer to an arbitrary rectangular window of a
;;; raster (or window, pane, image plane, image, etc.).  By convention, an area
;;; is represented by its left, top, right, and bottom `edges', in that order,
;;; where, for a non-zero-size area, left-edge < right-edge and top-edge <
;;; bottom-edge.  (When left-edge >= right-edge or top-edge >= bottom-edge, the
;;; area is of zero size.)  When the edges are viewed as raster subscripts, the
;;; upper left-hand corner pixel is at (left-edge, top-edge) and the lower
;;; right-hand pixel is at (right-edge - 1, top-edge - 1).  Thus, viewed as
;;; raster subscripts, the edges are asymmetric with respect to the raster area.
;;; The width of an area is given by (right-edge - left-edge) and the height by
;;; (bottom-edge - top-edge).

;;; Note that all raster graphics in an AB system should use rasters and raster-
;;; specific operations, as defined in module PRIMITIVES, especially for raster
;;; element access and raster arithmetic.

;;; A point, edge, or area is said to be `in' a pane if it is described in the
;;; coordinate system of the window and `within' a pane if it is both "in" the
;;; pane and located entirely within the pane rectangle.  Thus something "in" a
;;; pane is not necessarily "within" the pane.

(def-concept gensym-window-geometry)


;;;; Panes


;;; A `pane' is a rectangular region within a gensym window.  See
;;; `gensym-window-geometry' and `pane-area-hack' for further details.

;;; A pane has on it a `stack' of one or more `image planes': a `top plane' and
;;; any number of `buried planes'....

;;; Note that there is no guarantee that the stack of image planes will remain
;;; in any particular order, since planes may be shuffled arbitrarily during
;;; user interaction.  Furthermore, an image plane may be deleted during user
;;; interaction, and thus nothing should count on the continued existence or
;;; stack position of an image plane, except momentarily.

;;; A drawing schedule is stored in the pane to record drawing that has
;;; be deferred to allow the oportunity for other micro tasks to run.
;;; Drawing schedules are documented in the section "drawing schedules" below.

(def-structure (pane
		 (:constructor
		   make-pane
		   (pane-name gensym-window-for-pane
		    pane-background-color-or-tiling-pattern))
		 #+development
		 (:print-function print-pane-structure))

  ;; A denotation, used only internally.
  pane-name

  ;; Backpointer in window's display hierarchy.
  gensym-window-for-pane

  ;; Pane background rendering info.
  pane-background-color-or-tiling-pattern
  (pane-background-color-override? nil)	; nonnil => override background, color only

  ;; Pane interior rendering info, aka the Children in window display hierarchy.
  ;; These are ordered front to back, i.e. closest to user first.
  (stack-of-image-planes			; nil only transiently!
    nil :reclaimer reclaim-stack-of-image-planes)

  ;; Pane foreground rendering info.
  (pane-cursors
    nil :reclaimer reclaim-pane-cursors-if-any)

  ;; This is the pane border, and background which is showing past
  ;; any image-planes
  (visible-region-of-pane nil                             ; nil only transiently
		 :reclaimer reclaim-region)

  ;; Deferred drawing.
  (pane-drawing-schedule (make-queue)
			 :reclaimer reclaim-drawing-schedule-and-queue)

  ;; Vistigal organ, a heap of image-planes.
  #+unused
  (tail-of-stack-of-image-planes-that-are-not-mine nil)

  (recycled-image-planes-for-pane	; must all be "available" (see below)
    nil :reclaimer reclaim-recycled-image-planes-for-pane))

;; We should trust the structure heap to manage these.


#+development
(defun print-pane-structure (pane stream depth)
  (declare (ignore depth))
  (let* ((pane-name (pane-name pane))
	 (gensym-window-for-pane (gensym-window-for-pane pane))
	 (shown-in-window-p
	   (and gensym-window-for-pane	; nec.?
		(memq pane (panes-in-window gensym-window-for-pane)))))
    (printing-random-object (pane stream)
      (format stream "PANE ~(~a~) - ~a ~a"
	      pane-name
	      (if shown-in-window-p "shown in" "hidden in")
	      gensym-window-for-pane))))



;;; A long time ago somebody thought it would be good to cache the pane edges in
;;; the image-planes, and not to keep them in the pane data structure.  The
;;; principle consequence of that is that even an empty pane has to have one
;;; image-plane, and we need a scheme to detect an "empty" image-plane.
;;; This is usually written: (null (workspace-on-image-plane? image-plane)).

(def-concept pane-area-hack)

;; Boy was that a bad idea.




;;; Reclaim-panes-in-window reclaims panes-in-window, the value of the slot
;;; of the same name in a gensym window being reclaimed.

(defun reclaim-panes-in-window (panes-in-window)
  (loop for pane in panes-in-window
	do (reclaim-pane pane))
  (reclaim-graphics-list panes-in-window))


;;; `Get-pane-if-any' returns the pane named pane-name in gensym-window, if
;;; there is one, or else nil. NOTE: this can be removed if we require a full
;;; recompile.

(defun get-pane-if-any (pane-name gensym-window)
  (declare #-development (ignore pane-name))
  (assert-for-development (eq pane-name 'detail-pane))
  (detail-pane gensym-window))

;;; The function `detail-pane' returns the "detail-pane" in gensym-window.  It
;;; is never NIL.

(defun detail-pane (gensym-window)
  (car (panes-in-window gensym-window)))

(defun detail-pane-for-workstation (workstation)
  (detail-pane (window-for-workstation workstation)))


;;; `Override-pane-background' ... is for development use only.

#+development
(def-system-variable overriding-pane-background-color-or-tiling-pattern?
    panes nil)

#+development
(defun override-pane-background
    (pane-background-color-or-tiling-pattern-rows?
      &optional (gensym-window system-window))
  (setq overriding-pane-background-color-or-tiling-pattern?
	(when pane-background-color-or-tiling-pattern-rows?
	  (if (symbolp pane-background-color-or-tiling-pattern-rows?)
	      pane-background-color-or-tiling-pattern-rows?
	      (make-tiling-pattern
		gensym-window
		pane-background-color-or-tiling-pattern-rows?)))))



;;; `Gray-tiling-pattern-rows' is an alist mapping the names of gray tiling
;;; pattern row configurations (VERY-LIGHT, LIGHT, MEDIUM, or DARK), the cars,
;;; to each's respective list of tiling pattern rows, the cdrs.  For development
;;; use only.

#+development
(eval-when (:compile-toplevel :load-toplevel :execute)
(defconstant gray-tiling-pattern-rows
    '((very-light
	. ((1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0)
	   (0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0)
	   (0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0)
	   (0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0)))
      (light
	. ((1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0)
	   (0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0)
	   (0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0)
	   (0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1)))
      (medium
	. ((1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0)
	   (0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1)))
      (dark
	. ((0 1 1 1 0 1 1 1 0 1 1 1 0 1 1 1 0 1 1 1 0 1 1 1 0 1 1 1 0 1 1 1)
	   (1 1 0 1 1 1 0 1 1 1 0 1 1 1 0 1 1 1 0 1 1 1 0 1 1 1 0 1 1 1 0 1)
	   (1 0 1 1 1 0 1 1 1 0 1 1 1 0 1 1 1 0 1 1 1 0 1 1 1 0 1 1 1 0 1 1)
	   (1 1 1 0 1 1 1 0 1 1 1 0 1 1 1 0 1 1 1 0 1 1 1 0 1 1 1 0 1 1 1 0)))
      )))

;; Consider making this facility non-development, putting an interface on it,
;; and extending it further, perhaps giving users a pattern editor, with
;; functionality something like the one in the Mac's Control Panel. (MHD
;; 4/29/89)

#+development
(defun gray-background (&optional (shade 'light))
  (override-pane-background
    (cdr (assq shade gray-tiling-pattern-rows))))

#+development
(defun grey-background (&optional (shade 'light)) (gray-background shade))



;;; `Compute-pane-background-color-value-or-tiling-pattern' only to be called
;;; in an on-window-without-drawing context.

(defun compute-pane-background-color-value-or-tiling-pattern (pane)
  (let ((pane-background-color-or-tiling-pattern
	  (or #+development overriding-pane-background-color-or-tiling-pattern?
	      (pane-background-color-override? pane)
	      (pane-background-color-or-tiling-pattern pane))))
    (if (symbolp pane-background-color-or-tiling-pattern)
	(map-to-color-value pane-background-color-or-tiling-pattern)
	pane-background-color-or-tiling-pattern)))




;;; The substitution-macro `paint-background-of-current-pane' paints from the
;;; background specification, which is a color or tiling pattern.

(def-substitution-macro paint-background-of-current-pane
    (background left top right bottom)
  (cond ((fixnump background)
	 (paint-solid-rectangle-in-current-window
	   left top right bottom
	   background))
	(t
	 (copy-from-tiling-pattern-to-current-window
	   left top right bottom
	   background)))
  (paint-window-and-pane-borders-in-current-window
    left top right bottom))



;;;; Memory Management of Frame Descriptions

;;; Frame descriptions are instructions for how to wrap an item in a decorative
;;; and useful frame.  These frames contain scroll bars, and possible other
;;; controls.  Frames are described by frame descriptions, a list of
;;; instructions sort of like the body of a progn.  Frame descriptions are
;;; consed both at compile time, for the build in frame descriptions and at run
;;; time for the user's custome frame descriptions.  Frame descriptions are
;;; owned by global variables or by instances of the class
;;; frame-style-definition.

;;; Frame descriptions are named.  These names appear in object configurations
;;; to configure the frame placed around an object.  When an object actually is
;;; rendered the frame description is infered from the name, this is a little
;;; complex.  The first we look for a frame-style-description in the current kb,
;;; and then we look in at small build in set, finally we just use a default
;;; frame.  This technique allows users to override the build in frames even for
;;; objects that lack an ovious class upon which to modify the object
;;; configuartion, e.g. menus, dialogs, etc by defining a frame style
;;; description that is the same as the build in one.  Since this computation is
;;; a little complex we always cache the result of this look up in the
;;; items/image-planes being framed.

;;; This cached value is not invalidated when the frame-style-definitions are
;;; editted by the users.  That's sad.  To avoid reclaiming the frame
;;; description when such edits are done is managed by indirecting thru a small
;;; structure, the frame-style-reference, where in a reference count is used to
;;; manage the reclaiming.

;;; The lookup of a frame-style-reference given symbol naming a frame-style, aka
;;; a frame-style, is implemented by storing the frame style in the
;;; frame-style-description, and for built in frame-style-descriptions storing
;;; the frame-style-reference on a property of the frame-style.

;;; Frame descriptions are implemented in the module DRAW.  The
;;; frame-style-definitions are implement in the module FORMATS.  The
;;; frame-style-references are implemented in this module.

;;; In summary:
;;;    frame-style             -- a symbol in AB or KEYWORD
;;;    frame-description       -- a progn body like description of the frame
;;;    frame-style-definition  -- a class users use for customizing
;;;    frame-description-reference   -- a structure counting users of a
;;;                                     frame-style-description

;;; Frame-styles named by keywords are those that may not be overridden by the
;;; user.  Slots containing frame-style or frame-style-references may be nil,
;;; indicating that no frame is found on this object, this is the usual case for
;;; items.

;;; A `frame-style-reference' is holds a frame style description along with
;;; a reference count.  The place which defines a unique frame style maintains
;;; creates the reference.  A bit in the reference is set, a dirty bit, when
;;; that place notices that the description is changing.  Users of this frame
;;; description increment the reference when they start using it, and decrement
;;; it when done.  They may use the dirty bit to notice they should fetch a
;;; new, accurate frame reference from the place that defines thier frame.

;;; These are created via create-frame-description-reference in DRAW. 

(def-structure (frame-description-reference
		 (:constructor
		   make-frame-description-reference
		   (frame-description-of-frame-description-reference)))
  (reference-count-of-frame-description-reference 0)
  (frame-description-of-frame-description-reference nil
			    :reclaimer reclaim-graphics-tree)
  (dirty-frame-description-reference nil)
  left-frame-indent
  top-frame-indent
  right-frame-indent
  bottom-frame-indent)

(defmacro reference-frame-description-reference (frame-style-reference)
  (avoiding-variable-capture (frame-style-reference)
    `(progn
       (incff (reference-count-of-frame-description-reference
		,frame-style-reference))
       ,frame-style-reference)))

(defun-simple release-frame-description-reference-if-any
    (frame-description-reference?)
  (when frame-description-reference?
    (decff (reference-count-of-frame-description-reference
	     frame-description-reference?))
    (when (=f 0
	      (reference-count-of-frame-description-reference
		frame-description-reference?))
      (reclaim-frame-description-reference frame-description-reference?)))
  nil)



;;;; Image Planes



;;; An image plane is primarily used to show a workspace, or portion thereof,
;;; within a pane.  An image plane may or may not [at present] have a workspace
;;; on it, in which case it is said to have an `image' (of the workspace).

;;; The `workspace-on-image-plane?' links the image-plane to his workspace,
;;; the `images-this-is-upon' slot in the workspace point's back.

;;; The `pane-for-image-plane' slot is a back pointer to this image plane's
;;; pane, where he resides in the `stack-of-image-planes' slot.  Image-planes
;;; are part of the window display hierarchy, i.e. the tree of `gensym-window',
;;; `pane', and `image-plane'.

;;; The rectangle of an image-plane's enclosing pane is stored directly in
;;; the image-plane.  These values are in raster units.
;;;    `*-edge-of-pane-in-window'
;;; You would expect these to be stored in the pane, but they aren't.  The
;;; principle consequence of that is that even an empty pane has to have one
;;; image-plane, and we need a scheme to detect an "empty" image-plane.

;;; Image-planes have a decorative border drawn around them known as a `frame'.
;;; Inside of that frame we draw the workspace and it's margin.  The size of
;;; the frame is recorded in raster units in `*-frame-indent-of-image-plane.'
;;; The frame is not scaled image-plane is showing a scaled workspace.

;;; Two nested rectangles record the area the entire image takes and the
;;; workspace's rendering take.  These are all in raster units, and are not
;;; clipped to the pane boundries.
;;;     `*-edge-of-workspace-area-in-window'
;;;     `*-edge-of-image-in-window image-plane'
;;; The `workspace-area' is the portion of the image-plane which is displaying
;;; some portion of the workspace.  If you add the pixels for the `frame-indent'
;;; then you get the `edge-of-image.'  The edge-of-image is always larger
;;; than the `workspace-area'

;;; Those three rectangles, in raster units, are related to the workspace
;;; rectangles via scaling.
;;;    `{x,y}-origin-of-workspace-in-window'
;;;    `image-{x,y}-scale'
;;; This mapping is abstracted in the macros `{x,y}-in-window'.

;;; The displayed portion of the workspace is known as the content-area, this
;;; is recorded in:
;;;     `*-edge-of-content-area-of-image-plane'
;;; this rectangle maps directly into the *-edge-of-workspace-area.  Due to
;;; bleeding, icon overflow, and the rough nature of scaling the actual area
;;; rendered may include blocks that overlap this rectangle:
;;;   `loose-*-edge-of-visible-workspace-area'
;;; This is used for `quick clipping'.

;;; In summary:
;;;    - Workspace Units -                            - Raster Units -
;;;     content-area                  --transform->     workspace-area
;;;     loose-visible-workspace-area  <-transform--           "
;;;                                                plus  frame-indent
;;;                                                      image-area

;;; The `workspace-area' may not be entirely visible within the pane.  The
;;; `workspace-area-within-pane' is the `workspace-area' clipped by the pane
;;; `edge-of-pane'
;;;    *-edge-of-workspace-area-within-pane -- a macro

;;; Image planes maybe occluded by the pane boundries and other image-planes in
;;; the stack of image-planes.  The union of the unoccluded portions of the
;;; `image-in-window' are recorded in the slot `visible-region-of-image-plane.'
;;; Drawing an image-plane from scratch requires refreshing each one of
;;; rectangles that together make up this region.

;;; Each rectangle is drawn by:
;;;  1. Drawing the frame (including the background aka the paper).
;;;     guided by the slot `frame-style-reference-of-image-plane'.
;;;  2. Drawing the workspace 
;;;     guided by the `subblocks' of the our workspace.
;;;  3. Drawing any overlay'd image-plane cursors, and finally
;;;     guided by the slot `image-plane-cursors'
;;;  4. Drawing any overlay'd pane cursors.
;;;     guided by the slot `pane-cursors' in our pane.

;;; Since drawing an entire image-plane may take longer than a single micro
;;; task is allowed to take we can suspend drawing.  The record of pending
;;; drawing is maintained in the slot `image-plane-drawing-schedule'.  Drawing
;;; schedules are documented in the section "drawing schedules" below.

;;; An image-plane maybe "coupled" with another so that movements in one of
;;; them creates synchronized movements in the coupled image-plane.  Both the
;;; relative xy position and the relative layer position of image-planes so
;;; coupled are maintained.  See `fix-up-superplanes-and-subplanes.'  The
;;; relevant slots are `superplane?' and `superplane-coupling?'.
;; Currently used only by edit-in-plane.


;;; Some image-planes are pinned so that they show the entire workspace's
;;; extent.  This is indicated by the flag
;;;     `showing-entire-workspace-p'
;;; this flag effects the behavior of scrolling and scaling operations.

;;; `BEWARE:' You might think that you could define reclaimers for slot values
;;; on image-planes the same as any other structure. Well, you be wrong. Slot
;;; reclaimers on image-planes are never called because image-planes are never
;;; reclaimed, they're "disassociated". So you must add explicit calls to slot
;;; reclaimers in `disassociate-workspace-and-image-plane'.

(def-structure (image-plane
		 (:constructor make-image-plane (pane-for-image-plane))
		 #+development
		 (:print-function print-image-plane-structure))
  (serial-number-of-image-plane 0)

  ;; Backpointer in window display hierarchy.
  pane-for-image-plane

  ;; Sibling image-plane to which we are coupled, if any.
  (superplane? nil)			; NIL or image plane this is coupled to
  superplane-coupling?			; NIL, RIDING, or GLUED

  ;; Linkage over into the KB hierarchy.
  (workspace-on-image-plane? nil)

  ;; The clipping rectangle of the enclosing pane. (See intro!)
  left-edge-of-pane-in-window
  top-edge-of-pane-in-window
  right-edge-of-pane-in-window
  bottom-edge-of-pane-in-window

  ;; How to draw a pretty frame around the image, and how big it is.
  (frame-description-reference-of-image-plane nil
    :reclaimer release-frame-description-reference-if-any) ; never called!

  ;; Knowledge about how to map workspace units into image-plane.
  image-x-scale
  image-y-scale
  x-origin-of-workspace-in-window-of-image-plane
  y-origin-of-workspace-in-window-of-image-plane

  ;; The workspace's area mapped into window coordinates, plus frame, i.e. the
  ;; maximum extent.  NOT clipped inside of pane edges.
  (left-edge-of-image-in-window 0)
  (top-edge-of-image-in-window 0)
  (right-edge-of-image-in-window 0)
  (bottom-edge-of-image-in-window 0)

  ;; Workspace range mapped into window units.
  ;; Not clipped inside of pane edges, but a subset of image-in-window.
  left-edge-of-workspace-area-in-window
  top-edge-of-workspace-area-in-window
  right-edge-of-workspace-area-in-window
  bottom-edge-of-workspace-area-in-window

  ;; Inverse of workspace-area plus some slop
  loose-left-edge-of-visible-workspace-area
  loose-top-edge-of-visible-workspace-area
  loose-right-edge-of-visible-workspace-area
  loose-bottom-edge-of-visible-workspace-area

  ;; See MOVES
  (image-plane-cursors nil
		       :reclaimer reclaim-image-plane-cursors) ; never called!

  ;; The exposed region of the image-plane, see
  ;; recompute-visible-regions-for-pane.
  (visible-region-of-image-plane nil
				 :reclaimer reclaim-region) ; never called!

  ;; A list of drawing-tasks waiting to be executed.
  (image-plane-drawing-schedule (make-queue)
				:reclaimer reclaim-drawing-schedule-and-queue) ; never called!

  ;; A slot-value list of blocks OR connections awaiting drawing, in order from
  ;; back to front.  Sometimes this list includes connections and subsubblocks,
  ;; and sometimes it doesn't.
  remaining-subblocks-of-workspace-to-draw

  ;; Another agenda of activities to be drawn after all of the others.
  remaining-xor-drawing-activities

  ;; The workspace area inside of the frame.
  left-edge-of-content-area-of-image-plane
  top-edge-of-content-area-of-image-plane
  right-edge-of-content-area-of-image-plane
  bottom-edge-of-content-area-of-image-plane

  ;; The set of frame-transforms, used by items on this workspace
  ;; to transform into this workspace.  These are reclaimed when the
  ;; image-plane has the workspace removed.  The set is double linked
  ;; thru the structures.
  (frame-transforms-of-blocks-in-image-plane
    nil
    :reclaimer reclaim-frame-transforms-of-blocks-in-image-plane) ; never called!

  (image-plane-native-window? nil :reclaimer reclaim-native-window)
  (image-plane-native-frame-style-internal nil)

  (image-plane-close-box-situation 'normal) ; NORMAL, PENDING, or NA

  ;; The selected things on this image-plane.
  (image-plane-current-selection nil :reclaimer reclaim-selection) ; never called!
  (image-plane-view-preferences nil))	; A gensym plist

#+development
(defun print-image-plane-structure (image-plane stream depth)
  (declare (ignore depth))
  (let* ((index (position image-plane
			  (stack-of-image-planes (pane-for-image-plane image-plane))))
	 (workspace? (workspace-on-image-plane? image-plane))
	 (x-scale (image-x-scale image-plane))
	 (y-scale (image-y-scale image-plane))
	 (percent (and x-scale y-scale
		       (round (* 100 (minf x-scale y-scale)) (normalized-scale)))))
    (printing-random-object (image-plane stream)
      (format stream "IMAGE-PLANE ~d of ~a ~a%" index workspace? percent))))

(def-substitution-macro gensym-window-for-image-plane (image-plane)
  (gensym-window-for-pane
    (pane-for-image-plane
      image-plane)))

(def-substitution-macro workstation-of-image-plane (image-plane)
  (workstation-this-is-on
    (gensym-window-for-pane
      (pane-for-image-plane
	image-plane))))

;; cf the g2-window magic argument.
(defun g2-window-for-gensym-window? (gensym-window)
  (let ((workstation? (workstation-this-is-on gensym-window)))
    (when workstation?
      (g2-window-for-this-workstation? workstation?))))


(defun printing-image-plane-p (image-plane)
  (printing-window-p (gensym-window-for-image-plane image-plane)))

(defun minimized-image-plane-p (image-plane)
  (and (image-plane-native-window? image-plane)
       (native-window-minimized-p (image-plane-native-window? image-plane))))


(def-substitution-macro pending-kb-drawing-for-workspace-p (workspace)
  (or (changed-blocks-of-workspace workspace)
      (invalid-region-of-workspace? workspace)))


(defun-simple pending-drawing-for-workspace-p (workspace)
  (or (pending-kb-drawing-for-workspace-p workspace)
      (loop for image-plane in (image-planes-this-is-on workspace)
	    thereis (queue-non-empty-p-macro
		      (image-plane-drawing-schedule image-plane)))))

;;; The function `pending-drawing-for-process-p' is true if there is any
;;; pending drawing on any connected window.

(defun-simple pending-drawing-for-process-p ()
  (loop for workstation in workstations-in-service
	thereis (pending-drawing-for-workstation-p workstation)))

(defun-simple pending-drawing-for-workstation-p (workstation)
  (let ((window (window-for-workstation workstation)))
    (loop for pane in (panes-in-window window)
	  thereis (queue-non-empty-p-macro (pane-drawing-schedule pane))
	  thereis (loop for image-plane in (stack-of-image-planes pane)
			as workspace? = (workspace-on-image-plane? image-plane)
			thereis (and workspace?
				     (pending-kb-drawing-for-workspace-p workspace?))
			thereis (queue-non-empty-p-macro
				  (image-plane-drawing-schedule image-plane))))))

;; We're not using the cached counts here!


(defmacro discard-image-plane-drawing-queue-entry (image-plane)
  `(progn
     (reclaim-slot-value-list (remaining-subblocks-of-workspace-to-draw ,image-plane))
     (reclaim-remaining-xor-drawing-activities (remaining-xor-drawing-activities ,image-plane))
     (setf (remaining-subblocks-of-workspace-to-draw ,image-plane) nil
	   (remaining-xor-drawing-activities ,image-plane) nil)))

(defun-void reclaim-remaining-xor-drawing-activities (activities)
  (loop for activity in activities
	for (function block fsn . args) = activity
	do (reclaim-frame-serial-number fsn)
	   (reclaim-slot-value-list activity))
  (reclaim-slot-value-list activities))



;;; `Set-remaining-subblocks-of-workspace-to-draw' sets the agenda of blocks to
;;; be drawn for the image-plane.  The given list of blocks must be a
;;; slot-value list in the order from back to front.  The list is consumed by
;;; this function.

(defun set-remaining-subblocks-of-workspace-to-draw (image-plane blocks)
  (discard-image-plane-drawing-queue-entry image-plane)
  (setf (remaining-subblocks-of-workspace-to-draw image-plane) blocks))


(defun set-image-plane-view-preferences (image-plane plist?)
  (reclaim-gensym-list (image-plane-view-preferences image-plane))
  (setf (image-plane-view-preferences image-plane)
	(if plist? (copy-list-using-gensym-conses plist?))))


;;; The function `workspace-background-images' returns a list of lists of
;;; (image-name x-in-workspace y-in-workspace) for the given workspace.
;;; Each of the three elements is guarenteed to be non-NIL

(defun workspace-background-images (workspace)
  (background-images workspace))

(defun image-plane-background-images (image-plane)
  (let ((workspace? (workspace-on-image-plane? image-plane)))
    (when workspace?
      (background-images workspace?))))



;;; The macro `do-image-planes-in-group' runs body with group-member boud
;;; to each member of the superplane/subplane group of which the given
;;; image-plane is a member.  The first iteration is always on the
;;; given image-plane.

(defmacro do-image-planes-in-group ((group-member image-plane) &body body)
  (avoiding-variable-capture (image-plane)
    `(loop with up-p
	   for ,group-member = ,image-plane
			     then (cond (up-p
					 (superplane? ,group-member))
					(t
					 (or (subplane? ,group-member)
					     (prog1
						 (superplane? ,image-plane)
					       (setq up-p t)))))
	   while ,group-member
	   doing
       (progn ,@body))))




;;;; Image-plane Serial Nnumbers



;;; `Image-plane-serial-numbers' are used to detect that an image-plane has been
;;; recycled.  When a workspace is associated with an image-plane a fixnum is
;;; given to the image-plane, the fixnum is set to zero when the image-plane is
;;; disassociated.  By checking that the number of an image-plane has remained
;;; unchanged a data structure can guard a pointer to an image-plane against
;;; recycling the image-plane.

;;; These are like `frame-serial-numbers' except that we treat the fixnums as a
;;; ring, and just go around and around; skipping zero of course.  This has the
;;; advantage that we can not exaust the set of serial numbers, but the
;;; disadvanges is that two image-planes may have the same serial number, and
;;; you can not guard a set of image-planes by storing only a single number.

;;; The primary interface to this is `image-plane-has-not-been-reprocessed-p'
;;; and the slot `serial-number-of-image-plane' in the image-plane.  The
;;; principle customer of this facility is the `valid-workstation-context'
;;; facility.

(def-concept image-plane-serial-numbers)



(defvar last-image-plane-serial-number minimum-image-plane-serial-number)

(defun-substitution-macro set-image-plane-serial-number (image-plane)
  (setf (serial-number-of-image-plane image-plane)
	(setf last-image-plane-serial-number
	      (cond
		;; Skip over -1 and neighbors
		((=f -2 last-image-plane-serial-number) 2)
		;; Wrap around.
		((=f last-image-plane-serial-number
		     maximum-image-plane-serial-number)
		 minimum-image-plane-serial-number)
		;; Sequence
		(t (+f 1 last-image-plane-serial-number))))))

(defun-substitution-macro clear-image-plane-serial-number (image-plane)
  (setf (serial-number-of-image-plane image-plane) -1))


(defun-substitution-macro image-plane-has-not-been-reprocessed-p
    (image-plane reference-serial-number)
  (=f (serial-number-of-image-plane image-plane) reference-serial-number))

(defun-substitution-macro image-plane-has-been-reprocessed-p
    (image-plane reference-serial-number)
  (not
    (image-plane-has-not-been-reprocessed-p
      image-plane reference-serial-number)))

(defun-substitution-macro image-plane-unassociated-p (image-plane)
  (=f (serial-number-of-image-plane image-plane) -1))







;;;; Reclaimers for Pane and Image Plane Slots




;;; Reclaim-stack-of-image-planes reclaims stack-of-image-planes, the value
;;; of the slot of the same name in a pane now being reclaimed.

(defun reclaim-stack-of-image-planes (stack-of-image-planes)
  (loop for image-plane in stack-of-image-planes
	as workspace? = (workspace-on-image-plane? image-plane)
	when workspace?
	  do (disassociate-workspace-and-image-plane workspace? image-plane)
	     (when (and (temporary-workspace-p workspace?)
			(null (image-planes-this-is-on workspace?)))
	       (delete-frame workspace?))
	do (reclaim-image-plane image-plane))
  (reclaim-graphics-list stack-of-image-planes))



;;; `Reclaim-recycled-image-planes-for-pane' reclaims
;;; recycled-image-planes-for- pane, the value of the slot of the same name in
;;; a pane now being reclaimed.

(defun reclaim-recycled-image-planes-for-pane (recycled-image-planes-for-pane)
  (loop for image-plane in recycled-image-planes-for-pane
	do (reclaim-image-plane image-plane))
  (reclaim-graphics-list recycled-image-planes-for-pane))



;;; `Reclaim-pane-cursors-if-any' reclaims pane-cursors, the slot of the same name
;;; in a pane now being deleted.

(defun reclaim-pane-cursors-if-any (pane-cursors)
  (when pane-cursors				; optimization -- usually nil
    (reclaim-graphics-tree pane-cursors)))







;;;; Conversion Between Workspace and Window Coordinates



;;; `X-in-window' converts x-in-workspace from workspace to window coordinates
;;; for image-plane?, if that is supplied, or else the current image plane.
;;; `Y-in-window' is similar.

(defmacro x-in-window (x-in-workspace)
  `(+r current-x-origin-of-drawing
       (delta-x-in-window ,x-in-workspace current-image-x-scale)))

(defmacro y-in-window (y-in-workspace)
  `(+r current-y-origin-of-drawing
       (delta-y-in-window ,y-in-workspace current-image-y-scale)))

;; Remember block-specific scaling of text lines and icons!



(def-substitution-macro x-in-window-for-image-plane (x-in-workspace image-plane)
  (+r (x-origin-of-workspace-in-window-of-image-plane image-plane)
      (delta-x-in-window x-in-workspace
			 (image-x-scale image-plane))))

(def-substitution-macro y-in-window-for-image-plane (y-in-workspace image-plane)
  (+r (y-origin-of-workspace-in-window-of-image-plane image-plane)
      (delta-y-in-window y-in-workspace
			 (image-y-scale image-plane))))



;;; `Transform-x' and `transform-y' will compute the window
;;; coordinate of a block coordinate for the block given when
;;; displayed in the image-plane given.

(defmacro x-in-frame-transform (x-in-workspace within-block image-plane)
  (declare (ignore within-block))
  (avoiding-variable-capture (x-in-workspace image-plane)
    `(+r (x-origin-of-workspace-in-window-of-image-plane
	   ,image-plane)
	 (delta-x-in-window ,x-in-workspace
			    (image-x-scale ,image-plane)))))

(defmacro y-in-frame-transform (y-in-workspace within-block image-plane)
  (declare (ignore within-block))
  (avoiding-variable-capture (y-in-workspace image-plane)
    `(+r (y-origin-of-workspace-in-window-of-image-plane
	   ,image-plane)
	 (delta-y-in-window ,y-in-workspace
			    (image-y-scale ,image-plane)))))



;;; `X-in-workspace' converts x-in-window from window to workspace coordinates
;;; for image-plane?, if that is supplied, or else current image plane.
;;; `Y-in-workspace' is similar.  This is seldom used.

(defmacro x-in-workspace (x-in-window &optional image-plane?)
  (cond
    (image-plane?
     (avoiding-variable-capture (x-in-window image-plane?)
       `(delta-x-in-workspace
	  (-r ,x-in-window
	      (x-origin-of-workspace-in-window-of-image-plane ,image-plane?))
	  (image-x-scale ,image-plane?))))
    (t
     `(delta-x-in-workspace
	(-r ,x-in-window current-x-origin-of-drawing)
	current-image-x-scale))))


(defmacro y-in-workspace (y-in-window &optional image-plane?)
  (cond
    (image-plane?
     (avoiding-variable-capture (y-in-window image-plane?)
       `(delta-y-in-workspace
	  (-r ,y-in-window
	      (y-origin-of-workspace-in-window-of-image-plane ,image-plane?))
	  (image-y-scale ,image-plane?))))
    (t
     `(delta-y-in-workspace
	(-r ,y-in-window current-y-origin-of-drawing)
	current-image-y-scale))))


(defun x-within-workspace (x-in-window image-plane &optional (margin 0))
  (x-in-workspace
    (maxf (+f (left-edge-of-workspace-area-in-window image-plane) margin)
	  (minf (-f (right-edge-of-workspace-area-in-window image-plane) 1 margin)
		x-in-window))
    image-plane))

(defun y-within-workspace (y-in-window image-plane &optional (margin 0))
  (y-in-workspace
    (maxf (+f (top-edge-of-workspace-area-in-window image-plane) margin)
	  (minf (-f (bottom-edge-of-workspace-area-in-window image-plane) 1 margin)
		y-in-window))
    image-plane))


;;; `Get-default-image-x-scale' and `get-default-image-y-scale' return the
;;; default scale of the image plane, by getting it from the plist of the window
;;; of the pane of the image plane.
;;;
;;; The concept of `full scale' in the G2 language is interpreted to mean "at
;;; default x and y scale".  By extension, the rest of the scaling language
;;; should be interpreted as being with respect to full scale, thus defined.
;;;
;;; Note, however, that at present, and in versions of G2 through 3.0, users had
;;; no control over default x and y scale, and they in fact always defaulted to
;;; the value of (normalized-scale). (MHD 3/14/94)

(defun-simple get-default-image-x-scale (image-plane)
  (get-gensym-window-parameter
    (gensym-window-for-image-plane image-plane)
    'default-x-scale))

(defun-simple get-default-image-y-scale (image-plane)
  (get-gensym-window-parameter
    (gensym-window-for-image-plane image-plane)
    'default-y-scale))

;; Author: MHD

;; Move elsewhere?! (MHD 3/14/94)


(defun default-x-scale (gensym-window)
  (get-gensym-window-parameter gensym-window 'default-x-scale))

(defun default-y-scale (gensym-window)
  (get-gensym-window-parameter gensym-window 'default-y-scale))


(defun image-plane-x-scale-mf (image-plane)
  (with-temporary-gensym-float-creation image-plane-x-scale-mf
    (allocate-managed-float
      (/e (/e (*e (coerce-to-gensym-float (image-x-scale image-plane))
		  (coerce-to-gensym-float (normalized-scale)))
	      (coerce-to-gensym-float (get-default-image-x-scale image-plane)))
	  (coerce-to-gensym-float (normalized-scale))))))

(defun image-plane-y-scale-mf (image-plane)
  (with-temporary-gensym-float-creation image-plane-y-scale-mf
    (allocate-managed-float
      (/e (/e (*e (coerce-to-gensym-float (image-y-scale image-plane))
		  (coerce-to-gensym-float (normalized-scale)))
	      (coerce-to-gensym-float (get-default-image-y-scale image-plane)))
	  (coerce-to-gensym-float (normalized-scale))))))




;;;; Frame Transforms


;;; Frame Transforms are used to hold the transformation matrix and frame thru
;;; which a block is rendered, i.e. to do scrolling.

;;; A frame transform is a linkage between an block, an image-plane, and
;;; frame-description-reference.  They are one of the bridges between the window
;;; and KB hierarchy.  Each of these linkages has memory management issues.

;;; The frame-transform <-> image-plane is managed via an unordered double
;;; linked threaded list thru the frame-transforms which hangs from the
;;; frame-transforms-of-blocks-in-image-plane of the image-plane.

;;; The frame-transform -> frame-description-reference is managed as one
;;; reference counted pointer into the frame-description-reference.

;;; The frame-transform <-> block is managed via an alist in the block key'd by
;;; the image-plane, and a pointer in the frame-transform back to the block.

;;; These relationships are established by make-frame-transform, and undone by
;;; reclaim-frame-transform.  That is called by the reclaimers for: the slot in
;;; blocks, the slot in image-planes, as well as by the code that removes an
;;; workspace from an image-plane.

;; Currently these are not used for the workspace blocks, which is way sad.

;; They are KB specific, and not saved into the KB (a fact that needs work)!

(def-structure (frame-transform
		 (:constructor
		   make-frame-transform-1
		   (block-of-frame-transform
		     image-plane-of-frame-transform
		     next-frame-transform-of-this-image-plane?
		     frame-description-reference-of-frame-transform))
		 (:reclaimer reclaim-frame-transform-1))

  ;; Resides in the Window Hierarchy.
  image-plane-of-frame-transform
  next-frame-transform-of-this-image-plane?
  (previous-frame-transform-of-this-image-plane? nil)

  ;; Resides in the KB hierarchy
  ;; hanging off the alist in slot frame-transforms-of-block.
  block-of-frame-transform

  (frame-description-reference-of-frame-transform
    nil
    :reclaimer release-frame-description-reference-if-any)

  ;; This rectangle is ...
  (left-edge-of-source-of-frame-transform 0)
  (top-edge-of-source-of-frame-transform 0)
  (right-edge-of-source-of-frame-transform 0)
  (bottom-edge-of-source-of-frame-transform 0)

  ;; projected into this rectangle.
  (left-edge-of-destination-of-frame-transform 0)
  (top-edge-of-destination-of-frame-transform 0)
  (right-edge-of-destination-of-frame-transform 0)
  (bottom-edge-of-destination-of-frame-transform 0))



;;; `Make-frame-transform' does that, but there's more, it also entangles the
;;; resulting frame-transform into the block and image-plane given.

(defun make-frame-transform (block image-plane frame-description-reference)
  (let* ((next-frame-transform-of-image-plane?
	  (frame-transforms-of-blocks-in-image-plane
	    image-plane))
	 (frame-transform
	  (make-frame-transform-1 block
				  image-plane
				  next-frame-transform-of-image-plane?
				  frame-description-reference)))

    ;; Finish Installing into Window hierarchy.
    (when next-frame-transform-of-image-plane?
      (setf (previous-frame-transform-of-this-image-plane?
	      next-frame-transform-of-image-plane?)
	    frame-transform))
    (setf (frame-transforms-of-blocks-in-image-plane
	    image-plane)
	  frame-transform)

    ;; Finish Install into KB Hierarchy.
    (graphics-push (graphics-cons image-plane frame-transform)
		   (frame-transforms-of-block block))
    (unless (block-is-transformed-p block) ;; already marked.
      (unless (workspace-p block) ;; no such marking on workspaces.
	(set-and-propogate-block-is-transformed block)))

    ;; Now bind the transformation, presumbably as it was
    ;; last bound when shown.
    (bind-initial-transformation-of-frame-transform frame-transform)

    frame-transform))


;;; `Bind-initial-transformation-of-frame-transform' is called
;;; as the last step of giving a block a frame transformation.
;;; It will search for an old recorded binding for the blocks frame.
;;; first checking for a configuration previously used in this window,
;;; during this run of G2, and then checking for a configuration
;;; recorded when this block was lasts saved.  These are stored
;;; in the two slots `unsaved-but-remembered-block-transforms' and
;;; `remembered-block-transforms' as lists 8 fixnum, i.e. two rectangles.
;;; The unsaved ones are stored as a plist keyed by a gensym-window.

;;; This design assures that if you show/hide/show a block then the
;;; second show will take you back to the same view as when you last
;;; hide it.

;;; This design has the subplot that you must give a block an initial
;;; remembered-block-transforms prior to showing with a frame first time.

(defun-void bind-initial-transformation-of-frame-transform (frame-transform)
  (let* ((block (block-of-frame-transform frame-transform))
	 (mapping (if (workspace-p block) ;; Bummer.
		      '(0 0 0 0   0 0 0 0)
		      (or
			(getf (unsaved-but-remembered-block-transforms block)
			      (session-id-of-workstation
				(workstation-of-image-plane
				  (image-plane-of-frame-transform frame-transform))))
			(remembered-block-transform block)))))
    #+development
    (unless mapping
      (error
	"You must provide something in remembered-block-transform ~
         before giving a block a frame-transform."))
    (setf (left-edge-of-source-of-frame-transform frame-transform)
	  (pop mapping))
    (setf (top-edge-of-source-of-frame-transform frame-transform)
	  (pop mapping))
    (setf (right-edge-of-source-of-frame-transform frame-transform)
	  (pop mapping))
    (setf (bottom-edge-of-source-of-frame-transform frame-transform)
	  (pop mapping))

    (setf (left-edge-of-destination-of-frame-transform frame-transform)
	  (pop mapping))
    (setf (top-edge-of-destination-of-frame-transform frame-transform)
	  (pop mapping))
    (setf (right-edge-of-destination-of-frame-transform frame-transform)
	  (pop mapping))
    (setf (bottom-edge-of-destination-of-frame-transform frame-transform)
	  (pop mapping))))






;;; `Reclaim-frame-transform' does that, but there's more, it also reclaims the
;;; pointers that associate this with a block, an image-plane, and a
;;; frame-description-reference.  In doing so it side effects those objects.
;;; That's an important fact to the reclaimers that clean up those the slots in
;;; those objects maintain these relationships.

(defun reclaim-frame-transform (frame-transform)

  ;; Clean up the image-plane <-> frame-transform relationship.
  ;; I.e. splice this entry out of the threaded dbl. linked list.
  (let ((next? (next-frame-transform-of-this-image-plane?
		 frame-transform))
	(prev? (previous-frame-transform-of-this-image-plane?
		 frame-transform)))
    (if prev?
	(setf (next-frame-transform-of-this-image-plane? prev?)	  next?)
	(setf (frame-transforms-of-blocks-in-image-plane
		(image-plane-of-frame-transform frame-transform)) next?))
    (when next?
      (setf (previous-frame-transform-of-this-image-plane? next?)
	    prev?)))

  ;; Clean up the block <-> frame-stranform
  ;; I.e. recalim the approprate alist entry out of the alist
  (let ((block (block-of-frame-transform frame-transform)))
    (loop as previous-listed-alist-entry? = nil then listed-alist-entry
	  for listed-alist-entry on (frame-transforms-of-block block)
	  when (eql (cdr (car listed-alist-entry))
		    frame-transform)
	    do
	      (reclaim-graphics-cons (first listed-alist-entry))
	      (let ((tail (cdr listed-alist-entry)))
		(cond
		  (previous-listed-alist-entry?
		   (setf (cdr previous-listed-alist-entry?) tail))
		  (t
		   (setf (frame-transforms-of-block block) tail))))
	      (reclaim-graphics-cons listed-alist-entry)
	      (return nil))
    ;; If we removed the last one, clear the kb flag.
    (unless (frame-transforms-of-block block)
      (clear-and-propogate-block-is-transformed block)))

  ;; Discard it, and hence
  ;; cleanup the frame-transform -> frame-description-reference
  (reclaim-frame-transform-1 frame-transform))



;;; `Reclaimer for Frame-transforms-of-block' reclaims the frame-tranforms for
;;; the block until there are none.

(def-slot-value-reclaimer frame-transforms-of-block
    (frame-transforms-alist block)
  (declare (ignore frame-transforms-alist))
  (reclaim-frame-transforms-of-block block))

(defun reclaim-frame-transforms-of-block (block)
  (loop for alist? = (frame-transforms-of-block block)
	while alist?
	do (reclaim-frame-transform (cdr (car alist?)))))



;;; `Reclaim-frame-transforms-of-blocks-in-image-plane' is the reclaimer for the
;;; frame-transforms-of-blocks-in-image-plane slot in the image-plane.  It finds
;;; the image-plane, this is on, and then reclaims frame-transforms in there
;;; until there are none

(defun-void reclaim-frame-transforms-of-blocks-in-image-plane
    (first-frame-transform?)
  (when first-frame-transform?
    (loop with image-plane
	  = (image-plane-of-frame-transform first-frame-transform?)
	  for frame-transform?
	  = (frame-transforms-of-blocks-in-image-plane image-plane)
	  while frame-transform?
	  do (reclaim-frame-transform frame-transform?))))



;;; `Set-and-propogate-block-is-transformed' is called when a block get's it's
;;; first frame-transform while `clear-and-propogate-block-is-transformed'
;;; is called when we reclaims it's last one.

;;; Since this bit is not set on workspaces, care must be take to avoid calling
;;; this when placing a transform on a workspace.

(defun set-and-propogate-block-is-transformed (block)
  (set-block-is-transformed block)
  (loop for subblock being each subblock of block
	do (set-and-propogate-block-is-transformed subblock)))

(defun clear-and-propogate-block-is-transformed (block)
  (unless (frame-transforms-of-block block)
    (clear-block-is-transformed block)
    (loop for subblock being each subblock of block
	  do (clear-and-propogate-block-is-transformed subblock))))



;;; `update-block-is-transformed-if-necessary' is called when a block is
;;; is added into the subblock hierarchy.  It assures that the block's
;;; tranformed-state is in synch with it's parents.

(defun update-block-is-transformed-if-necessary (block superblock)
  (unless (eq (block-is-transformed-p block)
	      (block-is-transformed-p superblock))
    (if (block-is-transformed-p superblock)
	(set-and-propogate-block-is-transformed block)
	(clear-and-propogate-block-is-transformed block))))




;;; `Find-frame-transform-if-any' returns the frame-transform that maps the
;;; given block into the given image-plane.  It may return Nil, frames that lack
;;; a frame, or currently are not appearing in that window.

(defun-simple find-frame-transform-if-any (block image-plane)
  (loop for (cantidate-image-plane . frame-transform)
	    in (frame-transforms-of-block block)
	when (eq image-plane cantidate-image-plane)
	  do (return frame-transform)))

;;; `frame-description-reference-of-block?' will return the frame-description-reference
;;; if it currently as any.  If the block is framed, and showing on any image-plane
;;; it will.

(defun frame-description-reference-of-block? (block)
  (if (frame-transforms-of-block block)
      (frame-description-reference-of-frame-transform
	(cdr
	  (car
	    (frame-transforms-of-block block))))
      nil))



;;; `With-frame-transform' and `with-frame-transform-of-block-if-any' rebind the
;;; for-image-plane transform to that requested by the frame-transform.  They
;;; also bind current-frame-transform.  There are two schools of thought about
;;; how to manage the establishment of frame transforms.  Both macros always
;;; rebind the assorted variables, but they don't reset them unless necessary.
;;; It is necessary if a frame transform is given and if it is different from
;;; the one currently bound to current-frame-transform?

;;; In one school the draw block method never binds it, it is the responsiblity
;;; of the harness that invokes the drawing to do it.  This is the prefered
;;; design, but it is expensive since it requires looking up the frame
;;; transform in the harness a lot, when it is usually nil.

;;; In the second school the draw block method establishes the frame transform.
;;; Then only those blocks that currently can have frame transforms need to
;;; be modified.  This is easier to fold into the existing code and is what
;;; is implemented.

;;; The problem with the second school is that if block A establishes the
;;; transform and the renders its subblocks we run the risk of double
;;; tranforming.  To avoid this we maintain a "current-frame-transform" binding
;;; and establish only as necessary.  This actually allows us toward move some
;;; binding into the harness, and then removing the bind in the draw block
;;; methods when we think we have the harness doing all the work.



;;; `With-frame-transform' establishes a new contour of tranform
;;; bindings, and then established the frame transform given, if
;;; it is not already current.  See this name above for more info.

(defmacro with-frame-transform ((frame-transform) &body body)
  (avoiding-variable-capture (frame-transform)
    `(with-frame-transform-rebindings-1 ()
       (unless (eq current-frame-transform? ,frame-transform)
	 (set-frame-transform-bindings-1 ,frame-transform))
       ,@body)))



;;; `With-frame-transform-of-block-if-any' will establish the transform
;;; for the given block in the current image-plane, if the block has one.
;;; See this name above for more info.

(defmacro with-frame-transform-of-block-if-any ((block) &body body)
  (avoiding-variable-capture (block)
    `(with-draw-area-contour (,block :maybe-framed)
       (with-frame-transform-rebindings-1 ()
	 (when (block-is-transformed-p ,block)
	   (let* ((frame-transforms-of-enclosing-block
		    (loop for enclosing-block = ,block
					      then (superblock? enclosing-block)
			  as frame-transforms-of-block?
			     = (frame-transforms-of-block enclosing-block)
			  when frame-transforms-of-block?
			    do (return frame-transforms-of-block?)))
		  (frame-transform
		    (cdr (assq current-image-plane
			       frame-transforms-of-enclosing-block))))
	     (unless (eq current-frame-transform? frame-transform)
	       (nest-draw-area-for-frame-1 frame-transform)
	       (set-frame-transform-bindings-1 frame-transform))))
	 ,@body))))



;;; `With-frame-transform-rebindings-1' creates the contour so the
;;; transfomr can be rebound if necessary.  This is internal to the
;;; macros that actually establish the contours.

(defmacro with-frame-transform-rebindings-1 (() &body body)
  `(let ((current-frame-transform? current-frame-transform?)
	 (current-x-origin-of-drawing current-x-origin-of-drawing)
	 (current-y-origin-of-drawing current-y-origin-of-drawing))
     ,@body))



;;; `Set-frame-transform-bindings-1' is called to establish
;;; the actual transform bindings. It is internal to the macros that
;;; rebind the tranform.

(defmacro set-frame-transform-bindings-1 (frame-transform)
  (avoiding-variable-capture (frame-transform)
    `(progn 
       (setf current-frame-transform? ,frame-transform)
       (let ((x-offset
	       (+f (left-edge-of-destination-of-frame-transform ,frame-transform)
		   (delta-x-in-window
		     (left-edge-of-source-of-frame-transform ,frame-transform)
		     #.(normalized-scale))))) ;; if frames scaled this would be wrong.
	 (unless (=w 0 x-offset)
	   (incfr current-x-origin-of-drawing
		  (delta-x-in-window
		    x-offset
		    current-image-x-scale))))
       (let ((y-offset
	       (+f (top-edge-of-destination-of-frame-transform ,frame-transform)
		   (delta-y-in-window
		     (top-edge-of-source-of-frame-transform ,frame-transform)
		     #.(normalized-scale)))))
	 (unless (=w 0 y-offset)
	   (incfr current-y-origin-of-drawing
		  (delta-y-in-window y-offset current-image-y-scale)))))))


(defun nest-draw-area-for-frame-1 (frame-transform)
  (let ((block (block-of-frame-transform frame-transform)))
    (set-nested-draw-area
      (x-in-window (left-edge-of-block block))
      (y-in-window (top-edge-of-block block))
      (x-in-window (right-edge-of-block block))
      (y-in-window (bottom-edge-of-block block))
      frame-transform
      :content)))


;;; `With-image-plane-transform' establishes the tranform recorded in a given
;;; image-plane.

(defmacro with-image-plane-transform ((image-plane) &body body)
  (avoiding-variable-capture (image-plane)
    `(with-cached-transform (nil
			      (image-x-scale ,image-plane)
			      (image-y-scale ,image-plane)
			      (x-origin-of-workspace-in-window-of-image-plane
				,image-plane)
			      (y-origin-of-workspace-in-window-of-image-plane
				,image-plane))
       ,@body)))






;;;; Computing Edges Within the Pane


;; This was a local binding in compute-image-transformation-to-fit-in-pane

(defparameter minimum-margin-between-pane-and-image-plane 3)


;;; `Left-edge-within-pane' clips left-edge-in-window into the pane for
;;; image-plane.  `Top-edge-within-pane', `right-edge-within-pane', and
;;; `bottom-edge-within-pane' are similar.

(defun left-edge-within-pane (left-edge-in-window image-plane)
  (if (native-image-plane-p image-plane)
      left-edge-in-window
      (left-edge-within-area
	left-edge-in-window (left-edge-of-pane-in-window image-plane))))

(defun top-edge-within-pane (top-edge-in-window image-plane)
  (if (native-image-plane-p image-plane)
      top-edge-in-window
      (top-edge-within-area
	top-edge-in-window (top-edge-of-pane-in-window image-plane))))

(defun right-edge-within-pane (right-edge-in-window image-plane)
  (if (native-image-plane-p image-plane)
      right-edge-in-window
      (right-edge-within-area
	right-edge-in-window (right-edge-of-pane-in-window image-plane))))

(defun bottom-edge-within-pane (bottom-edge-in-window image-plane)
  (if (native-image-plane-p image-plane)
      bottom-edge-in-window
      (bottom-edge-within-area
	bottom-edge-in-window (bottom-edge-of-pane-in-window image-plane))))


;;; `Left-edge-of-image-within-pane' et al compute the edges of the workspace
;;; area of image-plane.

;;; When the workspace area is entirely outside the pane for image-plane, it may
;;; be the case that (left-edge-of-image-within-pane image-plane) >
;;; (right-edge-of-image-within-pane image-plane) and/or that
;;; (top-edge-of-image-within-pane image-plane) >
;;; (bottom-edge-of-image-within-pane image-plane).

(def-substitution-macro left-edge-of-image-within-pane (image-plane)
  (left-edge-within-pane
    (left-edge-of-image-in-window image-plane) image-plane))

(def-substitution-macro top-edge-of-image-within-pane (image-plane)
  (top-edge-within-pane
    (top-edge-of-image-in-window image-plane) image-plane))

(def-substitution-macro right-edge-of-image-within-pane (image-plane)
  (right-edge-within-pane
    (right-edge-of-image-in-window image-plane) image-plane))

(def-substitution-macro bottom-edge-of-image-within-pane (image-plane)
  (bottom-edge-within-pane
    (bottom-edge-of-image-in-window image-plane) image-plane))

;; Consider having these edges precomputed and stored, by set-up-edges-for-
;; image-plane et al, in image-plane slots.  This would gain a bit of speed.



;;; `Left-edge-of-workspace-area-within-pane' et al compute the edges of the
;;; workspace area of image-plane.  Image-plane must have a workspace on it.

;;; When the workspace area is entirely outside the pane for image-plane, it may
;;; be the case that (left-edge-of-workspace-area-within-pane image-plane) >
;;; (right-edge-of-workspace-area-within-pane image-plane) and/or that
;;; (top-edge-of-workspace-area-within-pane image-plane) >
;;; (bottom-edge-of-workspace-area-within-pane image-plane).

(def-substitution-macro left-edge-of-workspace-area-within-pane (image-plane)
  (left-edge-within-pane
    (left-edge-of-workspace-area-in-window image-plane) image-plane))

(def-substitution-macro top-edge-of-workspace-area-within-pane (image-plane)
  (top-edge-within-pane
    (top-edge-of-workspace-area-in-window image-plane) image-plane))

(def-substitution-macro right-edge-of-workspace-area-within-pane (image-plane)
  (right-edge-within-pane
    (right-edge-of-workspace-area-in-window image-plane) image-plane))

(def-substitution-macro bottom-edge-of-workspace-area-within-pane (image-plane)
  (bottom-edge-within-pane
    (bottom-edge-of-workspace-area-in-window image-plane) image-plane))

;; Consider having these edges precomputed and stored, by set-up-edges-for-
;; image-plane et al, in image-plane slots.  This would gain a bit of speed.



;;; `Left-edge-within-workspace-area' clips left-edge-in-window into the
;;; workspace area for image-plane.  `Top-edge-within-workspace-area',
;;; `right-edge-within-workspace-area', and `bottom-edge-within-workspace-area'
;;; are similar.

(defmacro left-edge-within-workspace-area (left-edge-in-window image-plane)
  `(left-edge-within-area
     ,left-edge-in-window (left-edge-of-workspace-area-in-window ,image-plane)))

(defmacro top-edge-within-workspace-area (top-edge-in-window image-plane)
  `(top-edge-within-area
     ,top-edge-in-window (top-edge-of-workspace-area-in-window ,image-plane)))

(defmacro right-edge-within-workspace-area (right-edge-in-window image-plane)
  `(right-edge-within-area
     ,right-edge-in-window
     (right-edge-of-workspace-area-in-window ,image-plane)))

(defmacro bottom-edge-within-workspace-area (bottom-edge-in-window image-plane)
  `(bottom-edge-within-area
     ,bottom-edge-in-window
     (bottom-edge-of-workspace-area-in-window ,image-plane)))

;; None of these are used.





;; A utility function

(def-substitution-macro region-possibly-overlaps-rectangle-p (region left top right bottom)
  (multiple-value-bind (region-left region-top region-right region-bottom)
      (region-bounding-rectangle region)
    (rectangles-overlap-p
      region-left region-top region-right region-bottom
      left top right bottom)))





;;;; Maintaining Visible Regions



;;; The principle algorithm of this section is a recursive walk down the stack
;;; of image-planes, adding or subtracting from the visible region of each
;;; image-plane encountered.  For simplicity we will only discuss the expose
;;; case.  The recursion takes a rectangle being exposed.  It searchs down
;;; until it finds an image-plane overlapping that rectangle.  Failing to find
;;; any such rectangle it adds the exposed rectangle to the pane's visible
;;; region.

;;; Finding an overlapping image-plane it adds the overlap to the visible region
;;; of the image-plane, and then takes the remaininder (up to four new
;;; rectangles, and recurse with them on the remaining stack.

;;; The external routines of this section are:
;;;   recompute-visible-regions-for-workstation
;;;   expose-rectangle-behind-image-plane
;;;   hide-rectangle-behind-image-plane

;;; `Expose-rectangle-over-some-image-planes' takes a newly exposed area and
;;; some tail of the current-pane's stack of image-planes.  It adds the
;;; rectangle to the image-planes and pane it overlaps.  This is called when
;;; any image-plane ocupies some screen real estate.

;;; This routine is internal to this section.  It assumes current-image-plane is
;;; bound.  It assumes this area is not obscured by of the pane's image-planes
;;; not in this list See section introduction for additional info.

;;; Called at present only from recompute-visible-regions-for-pane. That is, we
;;; always recompute the visible region from scratch. -fmw, 9/19/03

(defun-void expose-rectangle-over-some-image-planes (left-edge-of-area 
						      top-edge-of-area
						      right-edge-of-area
						      bottom-edge-of-area
						      stack-of-image-planes)
  (loop for (image-plane . remaining-stack-of-image-planes) 
	    = stack-of-image-planes
	  then remaining-stack-of-image-planes
	while image-plane
	as left-edge-of-image-within-area
	   = (maxr (left-edge-of-image-in-window image-plane)
		   left-edge-of-area)
	as top-edge-of-image-within-area
	   = (maxr (top-edge-of-image-in-window image-plane)
		   top-edge-of-area)
	as right-edge-of-image-within-area
	   = (minr (right-edge-of-image-in-window image-plane)
		   right-edge-of-area)
	as bottom-edge-of-image-within-area
	   = (minr (bottom-edge-of-image-in-window image-plane)
		   bottom-edge-of-area)
	when (rectangle-not-empty-p
	       left-edge-of-image-within-area top-edge-of-image-within-area
	       right-edge-of-image-within-area bottom-edge-of-image-within-area)
	  do
	    (setf (visible-region-of-image-plane image-plane)
		  (add-rectangle-to-region
		    left-edge-of-image-within-area
		    top-edge-of-image-within-area
		    right-edge-of-image-within-area
		    bottom-edge-of-image-within-area
		    (visible-region-of-image-plane image-plane)))
	    (macrolet ((recur (a1 a2 a3 a4) 
			      `(expose-rectangle-over-some-image-planes
				 ,a1 ,a2 ,a3 ,a4
				 remaining-stack-of-image-planes)))
	      (when (<r top-edge-of-area top-edge-of-image-within-area)
		(recur
		  left-edge-of-area top-edge-of-area
		  right-edge-of-area top-edge-of-image-within-area))
	      (when (<r left-edge-of-area left-edge-of-image-within-area)
		(recur
		  left-edge-of-area top-edge-of-image-within-area
		  left-edge-of-image-within-area
		  bottom-edge-of-image-within-area))
	      (when (>r right-edge-of-area right-edge-of-image-within-area)
		(recur
		  right-edge-of-image-within-area top-edge-of-image-within-area
		  right-edge-of-area bottom-edge-of-image-within-area))
	      (when (>r bottom-edge-of-area bottom-edge-of-image-within-area)
		(recur
		  left-edge-of-area bottom-edge-of-image-within-area
		  right-edge-of-area bottom-edge-of-area)))
	    (return nil)
	finally
	  (setf (visible-region-of-pane current-pane)
		(add-rectangle-to-region
		  left-edge-of-area
		  top-edge-of-area
		  right-edge-of-area 
		  bottom-edge-of-area
		  (visible-region-of-pane current-pane)))))



;;; `Hide-rectangle-over-some-image-planes' is the inverse of
;;; expose-rectangle-over-some-image-planes it removes the area given from
;;; the visible regions of the image-planes given.  This is called when
;;; an image-plane vacates some screen real estate.

;;; This routine is internal to this section.  See section introduction
;;; for additional info.

#+unused-and-buggy
(defun-void hide-rectangle-over-some-image-planes (left-edge-of-area 
						    top-edge-of-area
						    right-edge-of-area
						    bottom-edge-of-area
						    stack-of-image-planes)
  (loop for (image-plane . remaining-stack-of-image-planes) 
	    = stack-of-image-planes
	  then remaining-stack-of-image-planes
	while image-plane
	as left-edge-of-image-within-area
	   = (maxr (left-edge-of-image-in-window image-plane) left-edge-of-area)
	as top-edge-of-image-within-area
	   = (maxr (top-edge-of-image-in-window image-plane) top-edge-of-area)
	as right-edge-of-image-within-area
	   = (minr (right-edge-of-image-in-window image-plane)
		   right-edge-of-area)
	as bottom-edge-of-image-within-area
	   = (minr (bottom-edge-of-image-in-window image-plane)
		   bottom-edge-of-area)
	when (rectangle-not-empty-p
	       left-edge-of-image-within-area top-edge-of-image-within-area
	       right-edge-of-image-within-area bottom-edge-of-image-within-area)
	  do
	    (setf (visible-region-of-image-plane image-plane)
		  (remove-rectangle-from-region
		    left-edge-of-image-within-area
		    top-edge-of-image-within-area
		    right-edge-of-image-within-area
		    bottom-edge-of-image-within-area
		    (visible-region-of-image-plane image-plane)))
	    (macrolet ((recur (a1 a2 a3 a4) 
			      `(expose-rectangle-over-some-image-planes	; HIDE??
				 ,a1 ,a2 ,a3 ,a4
				 remaining-stack-of-image-planes)))
	      (when (<r top-edge-of-area top-edge-of-image-within-area)
		(recur
		  left-edge-of-area top-edge-of-area
		  right-edge-of-area top-edge-of-image-within-area))
	      (when (<r left-edge-of-area left-edge-of-image-within-area)
		(recur
		  left-edge-of-area top-edge-of-image-within-area
		  left-edge-of-image-within-area
		  bottom-edge-of-image-within-area))
	      (when (>r right-edge-of-area right-edge-of-image-within-area)
		(recur
		  right-edge-of-image-within-area top-edge-of-image-within-area
		  right-edge-of-area bottom-edge-of-image-within-area))
	      (when (>r bottom-edge-of-area bottom-edge-of-image-within-area)
		(recur
		  left-edge-of-area bottom-edge-of-image-within-area
		  right-edge-of-area bottom-edge-of-area)))
	    (return nil)
	finally
	  (setf (visible-region-of-pane current-pane)
		(remove-rectangle-from-region
		  left-edge-of-area
		  top-edge-of-area
		  right-edge-of-area 
		  bottom-edge-of-area
		  (visible-region-of-pane current-pane)))))




;;; `Recompute-visible-regions-for-workstation' walks the panes and image-planes
;;; of a workstation recomputing the visible-region of each pane and image-plane
;;; from scratch.

;;; These slots contain a datum of type region (see UTILITIES).

(defun-void recompute-visible-regions-for-workstation (gensym-window)
  (loop for pane in (panes-in-window gensym-window)
	do (recompute-visible-regions-for-pane pane)))


;;; `Recompute-visible-regions-for-pane' is used when the entire pane layout is
;;; recomputed, or initialized. In fact, we always use this function, and never
;;; do an incremental update.

(defun-void recompute-visible-regions-for-pane (pane)
  (if (native-windows-p (gensym-window-for-pane pane))
      (recompute-visible-regions-for-mdi-pane pane)
      (recompute-visible-regions-for-classic-pane pane)))

(defun-void recompute-visible-regions-for-classic-pane (current-pane)
  (let* ((stack-of-image-planes (stack-of-image-planes current-pane))
	 (first-image-plane (first stack-of-image-planes)))
    ;; Set the visible regions to empty, reclaiming the old ones.
    (reclaim-region
      (shiftf (visible-region-of-pane current-pane)
	      (make-empty-region)))
    (loop for image-plane in stack-of-image-planes
	  do (reclaim-region
	       (shiftf (visible-region-of-image-plane image-plane)
		       (make-empty-region))))
    ;; Now expose the entire pane.
    (expose-rectangle-over-some-image-planes
      (left-edge-of-pane-in-window   first-image-plane)
      (top-edge-of-pane-in-window    first-image-plane)
      (right-edge-of-pane-in-window  first-image-plane)
      (bottom-edge-of-pane-in-window first-image-plane)
      stack-of-image-planes)))

(defun-void recompute-visible-regions-for-mdi-pane (pane)
  (reclaim-region (shiftf (visible-region-of-pane pane) (make-unbounded-region))) ; Needed?
  (loop for image-plane in (stack-of-image-planes pane) doing
    (recompute-visible-region-of-native-image-plane image-plane)))


;;;; Native Image Planes


;;; A `native-image-plane', or NIP for short, is a standard G2 image-plane with
;;; an attached native-window. The presence of the native-window causes all
;;; drawing to that image-plane to be redirected to the native-window, disables
;;; G2-side clipping, etc. For a particular gensym-window, all the image-planes
;;; must be native or else all must be non-native.

(def-concept native-image-plane)
(def-concept nip)

;; How large to make a native-window before using scroll bars.
(defparameter usable-fraction-of-window (round (* 0.95 (normalized-scale))))

;; A plist, bound by some callers to influence the native-window created.
(defvar native-image-plane-options nil)

;; If true, defer creating KB items for native windows until referenced.
#+views-api
(defvar lazy-native-window-item-creation nil)

(def-system-variable current-native-image-plane PANES nil)
(def-system-variable outer-native-image-plane PANES nil)

(def-system-variable native-window-updated-by-client PANES nil)
(def-system-variable native-window-client-operation PANES nil)

(def-system-variable transform-image-operation-hint PANES nil)
(def-system-variable native-image-plane-updated-by-client PANES nil)
(def-system-variable desired-parent-of-native-window? PANES nil)

(defun %move-native-window (native-window left top)
  (setf (native-window-left native-window) left
	(native-window-top native-window) top)
  (synchronize-native-window-item native-window))

(defun %move-native-window-by (native-window dx dy)
  (incff (native-window-left native-window) dx)
  (incff (native-window-top native-window) dy)
  (synchronize-native-window-item native-window))

(defun %reshape-native-window (native-window left top right bottom)
  (setf (native-window-left native-window) left
	(native-window-top native-window) top
	(native-window-width native-window) (-f right left)
	(native-window-height native-window) (-f bottom top))
  (synchronize-native-window-item native-window))
  
(defun %set-native-window-size (native-window width height)
  (unless (and (eql width (native-window-width native-window))
 	       (eql height (native-window-height native-window)))
    #+development (trace-native-window 'sized native-window width height)
    (setf (native-window-width native-window) width
	  (native-window-height native-window) height)
    (synchronize-native-window-item native-window)))

(defun embedded-native-window-p (native-window)
  (embedded-window-p (native-window-gensym-window native-window)))

;; TODO: Yeech.
(defun valid-native-window-state-p (native-window state)
  (cond ((memq state '(normal hidden)))
	((native-pane-p native-window)
	 (memq state '(autoshown floating docked autohidden closed destroyed)))
	((embedded-native-window-p native-window)
	 nil)
	(t
	 (memq state '(minimized maximized)))))

;; TODO: This needs more work.
(defun %set-native-window-state (native-window state)
  (unless (eq state (native-window-state native-window))
    #+development (trace-native-window 'state native-window state)
    (when (memq state '(left top right bottom))
      (setf (native-window-dock native-window) state
	    state 'docked))
    (when (eq state 'collapsed)
      (setq state 'autohidden))
    (when (valid-native-window-state-p native-window state)
      (setf (native-window-state native-window) state)
      (note-native-window-event state native-window))	    ; Start KB-level callback, if any.
    (unless (eq native-window native-window-updated-by-client)
      (cond ((native-pane-p native-window)
	     (case state
	       ((normal autoshown)	                    ; What is normal?
		(manage-pane-1 native-window 'show nil))
	       (floating
		(manage-pane-1 native-window 'float nil))
	       (docked
		(manage-pane-1 native-window 'redock nil))
	       (autohidden
		(manage-pane-1 native-window 'hide nil))
	       (hidden			                    ; Completely hidden
		(manage-pane-1 native-window 'close nil))
	       ((closed destroyed)
		(manage-pane-1 native-window 'destroy nil))
	       (t
		(dwarn "Unknown pane state ~s" state))))
	    (t
	     (case state
	       (normal
		(%show-native-window native-window sw-restore))
	       (hidden
		(%show-native-window native-window sw-hide))
	       (minimized
		(unless (embedded-native-window-p native-window)
		  (%show-native-window native-window sw-minimize)))
	       (maximized
		(unless (embedded-native-window-p native-window)
		  (%show-native-window native-window sw-maximize)))
	       (t
		(dwarn "Unknown window state ~s" state))))))
    (synchronize-native-window-item native-window)
    state))

(defun %show-native-window (native-window &optional (cmd sw-showna))
  (manage-native-window-1 native-window nip-show-window cmd 0 0 0 nil))

(defun %set-native-window-title (native-window title)
  (unless (and (stringpw title)
	       (stringpw (native-window-title? native-window))
	       (string=w title (native-window-title? native-window)))
    (when (native-window-title? native-window)
      (reclaim-if-text-string (native-window-title? native-window)))
    (setf (native-window-title? native-window) (copy-if-text-string title))
    (case (native-window-type native-window)
      (pane
       (manage-pane-1 native-window 'set-title title))
      (t
       (let ((plist (icp-list 'title title)))
	 (manage-native-window-1 native-window nip-caption-window 0 0 0 0 plist)
	 (reclaim-icp-list plist))))
    title))

;; NB: It won't work to add/remove scroll bars this way.
(defun %set-native-window-style (native-window &optional style? exstyle?)
  (when style?
    (setf (native-window-style native-window) style?))
  (when exstyle?
    (setf (native-window-exstyle native-window) exstyle?))
  (manage-native-window-1 native-window nip-restyle-window
			  (native-window-style native-window)
			  (native-window-exstyle native-window)
			  0 0 nil))

(defun %set-native-window-icon (native-window icon)
  (unless (eq icon (native-window-icon? native-window))
    (let ((icon-handle?
	    (send-native-icon (native-window-gensym-window native-window) icon)))
      (when icon-handle?
	(setf (native-window-icon? native-window) (copy-icon-designation icon))
	(case (native-window-type native-window)
	  (pane
	   (manage-pane-1 native-window 'set-icon icon-handle?))
	  (t
	   (manage-native-window-1 native-window nip-set-icon icon-handle? 0 0 0 nil)))))))

(defun %set-native-window-closeable (native-window closeable-p)
  (unless (eq closeable-p (native-window-closeable native-window))
    (let ((bit (if closeable-p 1 0)))
      (setf (native-window-closeable native-window) closeable-p)
      (case (native-window-type native-window)
	(pane
	 (manage-pane-1 native-window 'set-closeable closeable-p))
	(t
	 (manage-native-window-1 native-window nip-set-closeable bit 0 0 0 nil))))))

(defun %set-native-window-floatable (native-window floatable-p)
  (unless (eq floatable-p (native-window-floatable native-window))
    (unless (floating-pane-p native-window)
      (setf (native-window-floatable native-window) floatable-p)
      (case (native-window-type native-window)
	(pane
	 (manage-pane-1 native-window 'set-floatable floatable-p)
	 native-window)))))

(defun %set-native-window-autohideable (native-window autohideable-p)
  (unless (eq autohideable-p (native-window-autohidable native-window))
    (setf (native-window-autohidable native-window) autohideable-p)
    (case (native-window-type native-window)
      (pane
       (manage-pane-1 native-window 'set-hideable autohideable-p)
       native-window))))

(defun %set-native-window-draggable (native-window draggable-p)
  (unless (eq draggable-p (native-window-draggable native-window))
    (unless (floating-pane-p native-window)
      (setf (native-window-draggable native-window) draggable-p)
      (case (native-window-type native-window)
	(pane
	 (manage-pane-1 native-window 'set-draggable draggable-p)
	 native-window)))))

(defun %set-native-window-close-action (native-window close-action)
  (unless (eq close-action (native-window-close-action native-window))
    (setf (native-window-close-action native-window) close-action)
    (case (native-window-type native-window)
      (pane
       (manage-pane-1 native-window 'set-close-action close-action)
       native-window))))

;; Only for workspace-views at the moment.
(defun %set-native-window-background-color (native-window color?)
  (when (window-supports-set-background-color
	  (native-window-gensym-window native-window))
    (manage-native-window-1 native-window nip-set-background-color
			    (if (null color?) -1 (rgb-value-of-gensym-color color?))
			    0 0 0 nil)))

(defun native-image-plane-p (thing)
  (and (image-plane-p thing)
       (not (null (image-plane-native-window? thing)))))

(defun embedded-image-plane-p (thing)
  (and (image-plane-p thing)
       (image-plane-native-window? thing)
       (native-window-embedded-p (image-plane-native-window? thing))))

(defun native-editor-image-plane-p (image-plane)
  (and (image-plane-native-window? image-plane)
       (eq (native-window-class (image-plane-native-window? image-plane))
	   'editor)))

(defun native-editor-workspace-p (edit-workspace)
  (loop for image-plane in (image-planes-this-is-on edit-workspace)
	thereis (and (image-plane-p image-plane)
		     (native-editor-image-plane-p image-plane))))

;; This is currently true only for a native editor.
(defun client-drawn-image-plane-p (thing)
  (and (image-plane-p thing)
       (native-editor-image-plane-p thing)))

;; True if the native window's shape is not tied to the image-plane's shape.
(defun shape-decoupled-image-plane-p (thing)
  (and (image-plane-p thing)
       (native-editor-image-plane-p thing)))

(defun view-designation-p (thing)
  (and thing (or (fixnump thing) (symbolp thing) (wide-string-p thing))))

;;; The function `find-native-window' returns the "first" native window
;;; designated by window-designation, which is either a handle (integer), a name
;;; (symbol), a class name (symbol), or a title (string), and optionally has the
;;; given class.

(defun find-native-window (gensym-window? window-designation? &optional class?)
  (macrolet ((match-class (nw class?)
	       `(or (null ,class?)
		    (eq (native-window-class ,nw) ,class?))))
    (cond ((null gensym-window?) nil)
	  ((null window-designation?) nil)
	  ((fixnump window-designation?)
	   (let ((nw? (find-native-window-by-handle gensym-window? window-designation?)))
	     (when (and nw? (match-class nw? class?))
	       nw?)))
	  ((symbolp window-designation?)
	   (block search
	     (do-native-windows (nw gensym-window?)
	       (when (and (eq (native-window-name nw) window-designation?)
			  (match-class nw class?))
		 (return-from search nw)))
	     (do-native-windows (nw gensym-window?)
	       (when (and (eq (native-window-class nw) window-designation?)
			  (match-class nw class?))
		 (return-from search nw)))))
	  ((wide-string-p window-designation?)
	   (block search
	     (do-native-windows (nw gensym-window?)
	       (when (and (native-window-title? nw)
			  (match-class nw class?)
			  (string-equalw (native-window-title? nw) window-designation?))
		 (return-from search nw))))))))

;;; The function `native-window-name' returns the NAME of a window, which is a
;;; symbol that can be used by the KB to restore the window (or pane or dialog).

(defun native-window-name (native-window)
  (cond ((workspace-view-p native-window)
	 (and (native-window-image-plane? native-window)
	      (workspace-on-image-plane? (native-window-image-plane? native-window))
	      (car-or-atom
		(name-or-names-for-frame
		  (workspace-on-image-plane? (native-window-image-plane? native-window))))))
	(t
	 nil)))

;;; The function `create-native-window' is the sole interface for creating a
;;; native-window for an image-plane, from the G2 side. This creates the
;;; structure as well as the real window (currently only on the TW side). TW
;;; uses create-native-window-1 since it's really creating only a stub.

(defun create-native-window (gensym-window class title
					   frame-style left top right bottom
					   parent options
                                           ;; Added by SoftServe
                                           &optional
                                           modal)
  (let ((handle (allocate-native-window-handle gensym-window)))
    (multiple-value-bind (type style exstyle)
	(compute-native-window-style gensym-window frame-style parent options)
      
      ;; Added by SoftServe
      (when modal
        (setq type nip-wintype-toplevel))
      ;; End of SoftServe changes

      ;; Encode class in the upper byte of the type.
      (case class
	(editor (setq type (logiorf type #x80)))) ; KLUDGE: magic bit
      
      (let ((native-window
	      (create-native-window-1 gensym-window type parent handle title style exstyle
				      left top (-f right left) (-f bottom top) options)))
	(setf (native-window-class native-window) class)

	;; Maybe create the KB-level object.
	#+views-api (unless lazy-native-window-item-creation
		      (ensure-native-window-item native-window)
		      (synchronize-native-window-item native-window))

	native-window))))

(defun show-native-window (native-window &optional (cmd sw-showna))
  (when (and (eql cmd sw-restore)
	     (or (native-window-minimized-p native-window)
		 (native-window-maximized-p native-window)))
    (%set-native-window-state native-window 'normal))
  (manage-native-window-1 native-window nip-show-window cmd 0 0 0 nil))

(defun move-native-window (native-window x y)
  (%move-native-window native-window x y)
  (unless (native-window-embedded-p native-window)
    (manage-native-window-1 native-window nip-move-window x y 0 0 nil)))

;; Added by SoftServe
(defun set-native-window-size (native-window width height)
  (%set-native-window-size native-window width height)
  (unless (native-window-embedded-p native-window)
    (manage-native-window-1 native-window nip-size-window 0 0 width height nil)))

(defun move-native-window-by (native-window dx dy)
  (move-native-window native-window
		      (+f dx (native-window-left native-window))
		      (+f dy (native-window-top native-window))))

(defun reshape-native-window (native-window left top right bottom &optional variation)
  (let* ((gensym-window
	   (native-window-gensym-window native-window))
	 (opcode
	   (case variation
	     (inflate nip-inflate-window)
	     (rescale
	      (if (window-supports-nip-rescale-window gensym-window)
		  nip-rescale-window
		  nip-reshape-window))
	     (t nip-reshape-window))))

    (%reshape-native-window native-window left top right bottom)
    (unless (native-window-embedded-p native-window)
      (manage-native-window-1 native-window opcode left top right bottom nil))))

(defun raise-native-window (native-window)
  (manage-native-window-1 native-window nip-raise-window 0 0 0 0 nil))

(defun lower-native-window (native-window)
  (manage-native-window-1 native-window nip-lower-window 0 0 0 0 nil))

(defun zorder-native-window (native-window after-window-handle)
  (manage-native-window-1 native-window nip-zorder-window
			  after-window-handle 0 0 0 nil))

(defun stack-native-windows (gensym-window native-windows-top-to-bottom)
  (let ((handles (loop for native-window in native-windows-top-to-bottom
		       collect (native-window-handle native-window) using gensym-cons)))
    (stack-native-windows-1 gensym-window handles)
    (reclaim-gensym-list handles)))

(defun destroy-native-window (native-window)
  (manage-native-window-1 native-window nip-destroy-window 0 0 0 0 nil))

(defun caption-native-window (native-window title)
  (%set-native-window-title native-window title))

(defun erase-complement (native-window left top right bottom)
  (manage-native-window-1 native-window
			  nip-cerase-window left top right bottom nil))

(defun set-maximum-tracking-size (native-window width height)
  (manage-native-window-1 native-window
			  nip-set-max-size 0 0 width height nil))

(defun restyle-native-window (native-window frame-style)
  (multiple-value-bind (type style exstyle)
      (compute-native-window-style (native-window-gensym-window native-window)
				   frame-style
				   (native-window-parent? native-window))
    (declare (ignore type))		; Type can't be changed.
    (%set-native-window-style native-window style exstyle)))


#+development
(defvar nip-nesting 0)

#+development
(defvar nip-trace-p nil)

#+development
(defun nip-trace (string &optional image-plane)
  (when nip-trace-p
    (format t "~&~v@T~a NIP~@[ ~a~]~%" nip-nesting string image-plane)))

;; aka with-coor-shift-if-native-image-plane
(defmacro with-native-image-plane ((image-plane) &body body)
  `(let ((outer-native-image-plane current-native-image-plane))
     #+development (nip-trace "Enter" ,image-plane)
     (let ((current-native-image-plane ,image-plane)
	   #+development (nip-nesting (1+ nip-nesting)))
       ;; FIXME: Get out of this context if image-plane is not native.
       (unless (eq outer-native-image-plane current-native-image-plane)
	 (nip-begin-drawing current-native-image-plane))
       ,@body				; FIXME: needs an unwind-protect
       (unless (eq outer-native-image-plane current-native-image-plane)
	 (nip-end-drawing current-native-image-plane)))
     #+development (nip-trace "Leave")
     ;; Restablish outer context, if necessary.
     (when current-native-image-plane
       (unless (eq ,image-plane current-native-image-plane)
	 (nip-begin-drawing current-native-image-plane)))))

;;; The macro `with-out-native-image-plane' restores drawing to the entire G2
;;; window if we were in a NIP context.

(defmacro with-out-native-image-plane (() &body body)
  `(let ((outer-native-image-plane current-native-image-plane))
     (when outer-native-image-plane
       (nip-end-drawing outer-native-image-plane))
     (let ((current-native-image-plane nil))
       ,@body)				; FIXME: unwind-protect
     (when outer-native-image-plane
       (nip-begin-drawing outer-native-image-plane))))

(defun nip-x-offset (native-image-plane)
  (native-window-left (image-plane-native-window? native-image-plane)))

(defun nip-y-offset (native-image-plane)
  (native-window-top (image-plane-native-window? native-image-plane)))

(defun nip-begin-drawing (image-plane)
  (when (image-plane-native-window? image-plane)
    (redirect-window-1 (gensym-window-for-image-plane image-plane)
		       (image-plane-native-window? image-plane)
		       (-f (nip-x-offset image-plane))
		       (-f (nip-y-offset image-plane)))))

(defun nip-end-drawing (image-plane)
  (when (image-plane-native-window? image-plane)
    (redirect-window-1 (gensym-window-for-image-plane image-plane) nil 0 0)))

(defun reclaim-native-window-for-image-plane (image-plane)
  (let ((native-window? (image-plane-native-window? image-plane)))
    (when native-window?
      (setf (image-plane-native-window? image-plane) nil ; Snap link.
	    (image-plane-native-frame-style-internal image-plane) nil)
      (unless (eq native-image-plane-updated-by-client image-plane)
	(destroy-native-window native-window?))
      (when (native-window-item? native-window?)
	(delete-native-window-item native-window?))
      (reclaim-native-window native-window?))))


(defun image-plane-native-frame-style (image-plane)
  (or (image-plane-native-frame-style-internal image-plane)
      (setf (image-plane-native-frame-style-internal image-plane)
	    (compute-native-frame-style image-plane))))

;;; The function `native-frame-p' is true if the image-plane is native and it is
;;; using native framing. Otherwise, the framing is drawn entirely by G2.

(defun native-frame-p (image-plane)
  (neq (image-plane-native-frame-style image-plane) 'none))

(defun scrollable-image-plane-p (image-plane)
  (native-frame-p image-plane))		; For now, anything with a title bar.

(defun image-plane-has-x-scrollbar-p (image-plane)
  (and (image-plane-native-window? image-plane)
       (not (null (native-window-x-scroll? (image-plane-native-window? image-plane))))))

(defun image-plane-has-y-scrollbar-p (image-plane)
  (and (image-plane-native-window? image-plane)
       (not (null (native-window-y-scroll? (image-plane-native-window? image-plane))))))


(defun recompute-visible-region-of-native-image-plane (image-plane)
  (reclaim-region (visible-region-of-image-plane image-plane))
  (setf (visible-region-of-image-plane image-plane)
	(if (image-plane-native-window? image-plane)
	    (compute-workspace-view-region (image-plane-native-window? image-plane))
	    (make-empty-region))))


;;; `image-plane-client-left' and -top return the G2 window coordinates of the
;;; upper-left corner of the client area of the corresponding native-window
;;; ((0,0) in the native-window's client coordinates), assuming no scrolling.
;;; If using native framing, we include just the workspace area; otherwise, the
;;; entire image-plane area (workspace + classic framing).

(defun image-plane-client-left (image-plane)
  (if (native-frame-p image-plane)
      (left-edge-of-workspace-area-in-window image-plane)
      (left-edge-of-image-in-window image-plane)))

(defun image-plane-client-top (image-plane)
  (if (native-frame-p image-plane)
      (top-edge-of-workspace-area-in-window image-plane)
      (top-edge-of-image-in-window image-plane)))

(defun image-plane-client-right (image-plane)
  (if (native-frame-p image-plane)
      (right-edge-of-workspace-area-in-window image-plane)
      (right-edge-of-image-in-window image-plane)))

(defun image-plane-client-bottom (image-plane)
  (if (native-frame-p image-plane)
      (bottom-edge-of-workspace-area-in-window image-plane)
      (bottom-edge-of-image-in-window image-plane)))

(defun total-image-width (image-plane)	; That is, including G2 framing.
  (-r (right-edge-of-image-in-window image-plane)
      (left-edge-of-image-in-window image-plane)))

(defun total-image-height (image-plane)
  (-r (bottom-edge-of-image-in-window image-plane)
      (top-edge-of-image-in-window image-plane)))

(defun workspace-image-width (image-plane)
  (-r (right-edge-of-workspace-area-in-window image-plane)
      (left-edge-of-workspace-area-in-window image-plane)))

(defun workspace-image-height (image-plane)
  (-r (bottom-edge-of-workspace-area-in-window image-plane)
      (top-edge-of-workspace-area-in-window image-plane)))

(defun window-width (image-plane)
  (-r (right-edge-of-pane-in-window image-plane)
      (left-edge-of-pane-in-window image-plane)))

(defun window-height (image-plane)
  (-r (bottom-edge-of-pane-in-window image-plane)
      (top-edge-of-pane-in-window image-plane)))

(defun usable-window-width (image-plane)
  (scalef (window-width image-plane) usable-fraction-of-window))

(defun usable-window-height (image-plane)
  (scalef (window-height image-plane) usable-fraction-of-window))

;;; The functions `*-edge-of-view-in-window' compute the edges of the "view" of
;;; the image-plane. The edges of the view are the edges of the image-plane,
;;; except possibly when a native-window is present, in which case it is the
;;; edges of the client area of the window. With scrolling, the native-window
;;; may be smaller than the image-plane. With minimum window sizes, the
;;; native-window may be larger.

(defun left-edge-of-view-in-window (image-plane)
  (if (native-image-plane-p image-plane)
      (native-window-left (image-plane-native-window? image-plane))
      (left-edge-of-image-in-window image-plane)))

(defun top-edge-of-view-in-window (image-plane)
  (if (native-image-plane-p image-plane)
      (native-window-top (image-plane-native-window? image-plane))
      (top-edge-of-image-in-window image-plane)))

(defun right-edge-of-view-in-window (image-plane)
  (if (native-image-plane-p image-plane)
      (native-window-right (image-plane-native-window? image-plane))
      (right-edge-of-image-in-window image-plane)))

(defun bottom-edge-of-view-in-window (image-plane)
  (if (native-image-plane-p image-plane)
      (native-window-bottom (image-plane-native-window? image-plane))
      (bottom-edge-of-image-in-window image-plane)))


;;; The function `native-window-right-without-scrollbars' is used to anticipate
;;; the size of the window if scroll bars were removed.

(defun native-window-right-without-scrollbars (gensym-window native-window)
  (+f (native-window-right native-window)
      (if (native-window-y-scroll? native-window)
	  (get-system-metric gensym-window sm-cxvscroll 16)
	  0)))

(defun native-window-bottom-without-scrollbars (gensym-window native-window)
  (+f (native-window-bottom native-window)
      (if (native-window-x-scroll? native-window)
	  (get-system-metric gensym-window sm-cyhscroll 16)
	  0)))


;;; The function `initial-shape-of-native-window' computes the desired shape of
;;; the client area of the native-window for image-plane. If the image-plane
;;; will not have scroll bars, then the client area of the native-window will be
;;; the same as the "client area" of the image-plane. Otherwise, we fit the
;;; entire native-window, including all framing, into the G2-window, and let
;;; scroll bars appear. Note that the image-plane is not moved, we just pull-in
;;; the native-window borders.

(defun initial-shape-of-native-window (image-plane)
  (let ((native-frame-style
	  (or (when native-image-plane-options
		(compute-native-frame-style-1
		  (getf native-image-plane-options 'x-scroll-position)
		  (getf native-image-plane-options 'y-scroll-position)))
	      (image-plane-native-frame-style image-plane))))	      
    (setf (image-plane-native-frame-style-internal image-plane) native-frame-style)
    (multiple-value-bind (left top right bottom)
	(compute-initial-shape-of-native-window image-plane native-frame-style)
      (let ((width (-f right left))
	    (height (-f bottom top)))
	(when native-image-plane-options
	  (setq left (or (getf native-image-plane-options 'left) left)
		top (or (getf native-image-plane-options 'top) top)
		width (or (getf native-image-plane-options 'width) width)
		height (or (getf native-image-plane-options 'height) height)))
	(values left top (+f left width) (+f top height))))))

(defun compute-initial-shape-of-native-window (image-plane native-frame-style)
  (let* ((gensym-window (gensym-window-for-image-plane image-plane))
	 (left (image-plane-client-left image-plane))
	 (top (image-plane-client-top image-plane))
	 (right (image-plane-client-right image-plane))
	 (bottom (image-plane-client-bottom image-plane))

	 (cxvscroll (get-system-metric gensym-window sm-cxvscroll 16))
	 (cyhscroll (get-system-metric gensym-window sm-cyhscroll 16))
	 (cycaption (get-system-metric gensym-window sm-cycaption 19))
	 (cxframe   (get-system-metric gensym-window sm-cxframe 2))

	 (vsb? (memq native-frame-style '(vscroll bscroll)))
	 (hsb? (memq native-frame-style '(hscroll bscroll)))
	 
	 (margin (+r cxframe minimum-margin-between-pane-and-image-plane))
	 (lm margin)
	 (tm (+r margin cycaption))
	 (rm (+r margin (if vsb? cxvscroll 0)))
	 (bm (+r margin (if hsb? cyhscroll 0))))
    ;; Don't shrink a dimension unless we already have a scroll bar along it.
    ;; We don't want to cause a scroll bar to appear.
    (when hsb?
      (setq left (maxr left lm)
	    right (minr right (-r (window-width  image-plane) rm))))
    (when vsb?
      (setq top (maxr top tm)
	    bottom (minr bottom (-r (window-height image-plane) bm))))
    (values left top right bottom)))


;;;; Some native editor support, which belongs elsewhere.


(defun native-editor-p (gensym-window)
  (and (window-supports-native-editor-ex gensym-window)	; Require 8.3 version
       (twng-window-p gensym-window)))

(defun use-native-editor-p (gensym-window workspace)
  (and (prefer-native-editor-p gensym-window)
       (native-editor-p gensym-window)
       (of-class-p workspace 'edit-workspace)
       (boundp 'current-edit-state)
       (frame-being-edited? current-edit-state)

       ;; Disable for the login dialog.
       (not (of-class-p-function (frame-being-edited? current-edit-state) 'g2-login))

       ;; Disable for edit-in-place: we need a different native editor
       ;; control for that. -fmw, 2/3/05
       (not (specific-image-plane-on-which-to-edit-in-place? current-edit-state))))


;;; The function `create-native-window-for-image-plane' creates a native-window
;;; to display the image-plane. The size and shape depends on the G2 frame style
;;; as well as whether scroll bars are required.

(defvar editor-window-handle nil) ;; Added by SoftServe

(defun create-native-window-for-image-plane (gensym-window workspace image-plane
                                                           ;; Added by SoftServe
                                                           &optional
                                                           modal size-x size-y pos-x pos-y)
  (let ((title? (workspace-title workspace))
	(parent (or desired-parent-of-native-window? 0))
	(class (cond ((use-native-editor-p gensym-window workspace)
		      'editor)
		     (t
		      'g2-workspace-view)))
	(topmost? (eq image-plane (top-image-plane? (pane-for-image-plane image-plane))))
	(options nil))			; TODO: From either view-preferences, or g2-ui-show-workspace

    (multiple-value-bind (left top right bottom)
	(initial-shape-of-native-window image-plane)

      ;; FIXME: hack. Limit size of native editor window.
      (when (eq class 'editor)
	(let ((width (minf (width-of-block (edit-box current-edit-state))
			   (-f (window-width image-plane) left 40)))
	      (height (minf (width-of-block (edit-box current-edit-state))
			    (-f (window-width image-plane) top 40))))
	  (setq right (+f left width)
		bottom (+f top height))))

      (let ((native-window
	      ;; TODO: Want to include the scroll bars in the create, if needed,
	      ;; rather than adding them later.
	      (create-native-window gensym-window
				    class
				    (or title? #w"")
				    (image-plane-native-frame-style image-plane)
				    left top right bottom
				    parent options
	                            ;; Added by SoftServe
	                            modal)))
	(setf (image-plane-native-window? image-plane) native-window
	      (native-window-image-plane? native-window) image-plane)

	(when (unused-area-color? workspace)
	  (%set-native-window-background-color native-window (unused-area-color workspace)))

	(recompute-visible-region-of-native-image-plane image-plane)
	(update-native-scroll-bars image-plane)
	#+notyet (update-tracking-size image-plane)

	(when topmost?
	  (raise-native-window native-window))

	;; This sets the text and the caret position, although the caret is
	;; unreliable at this point.
	(when (eq class 'editor)	; FIXME: hack
	  (set-up-native-editor gensym-window native-window current-edit-state 
	                        ;; Added by SoftServe
	                        modal))

	;; Save original geometry, before TW changes it in order to put the
	;; window into some tab group.
	(when (tabbed-mdi-p gensym-window)
	  (save-native-window-geometry native-window))
      
	(show-native-window native-window)
	
	;; Added by SoftServe
	(when (eq class 'editor)	; FIXME: hack
	  (when (and pos-x pos-y (>f pos-x 0) (>f pos-y 0))
	    (move-native-window native-window pos-x pos-y))
	  (when (and size-x size-y (>f size-x 0) (>f size-y 0))
	    (set-native-window-size native-window size-x size-y)))
	  
	(reclaim-if-text-string title?)
	(setf editor-window-handle native-window) ;; Added by SoftServe
	native-window))))

(defun menu-workspace-p (workspace?)
  (and workspace? (of-class-p workspace? 'menu-workspace)))

;;; The function `image-plane-will-have-native-framing-p' is true if given
;;; image-plane will be native with native framing.  This has to work early in
;;; image-plane creation, where only the frame-style and workspace are valid. We
;;; can't tell at this point whether the image-plane will have scroll bars.

(defun image-plane-will-have-native-framing-p (image-plane)
  (let* ((frame-description
	   (frame-description-of-frame-description-reference
	     (frame-description-reference-of-image-plane image-plane)))
	 (workspace? (workspace-on-image-plane? image-plane)))
    (cond ((not (native-windows-p (gensym-window-for-image-plane image-plane)))
	   ;; TODO: and not toplevel window? How?
	   nil)
	  ((menu-workspace-p workspace?)
	   nil)
	  ((not (or (equal frame-description workspace-title-bar-frame-style-small)
		    (equal frame-description workspace-title-bar-frame-style-large)))
	   nil)
	  (t t))))

(defun image-plane-will-be-scrollable-p (image-plane)
  (image-plane-will-have-native-framing-p image-plane))


;;; The function `compute-native-frame-style' computes the "native frame style"
;;; for an image-plane. It is later mapped to Win32 style and exStyle fixnums by
;;; `compute-native-window-style'. This can only be used once the image-plane is
;;; fully set up.

(defun compute-native-frame-style (image-plane)
  (cond ((image-plane-will-have-native-framing-p image-plane)
	 (let* ((hscrollp (>f (workspace-image-width image-plane)
			      (usable-window-width image-plane)))
		(vscrollp (>f (workspace-image-height image-plane)
			      (usable-window-height image-plane))))
	   (compute-native-frame-style-1 hscrollp vscrollp)))
	(t
	 'none)))

(defun compute-native-frame-style-1 (hscrollp vscrollp)
  (cond ((and hscrollp vscrollp) 'bscroll)
	(hscrollp 'hscroll)
	(vscrollp 'vscroll)
	(t 'mdi)))

;;; The function `update-native-image-plane-frame-style' updates the frame style
;;; of a native window to match that of the image-plane.

(defun update-native-image-plane-frame-style (image-plane)
  (restyle-native-window
    (image-plane-native-window? image-plane)
    (progn
      (setf (image-plane-native-frame-style-internal image-plane) nil) ; Decache
      (image-plane-native-frame-style image-plane))))


(defun find-native-image-plane (gensym-window window-handle?)
  (let ((native-window? (find-native-window gensym-window window-handle?)))
    (when native-window?
      (native-image-plane? native-window?))))

(defun find-native-image-plane-with-parent (gensym-window parent)
  (do-native-windows (nw gensym-window)
    (when (and (equal (native-window-parent? nw) parent)
	       (workspace-view-p nw))
      (return (native-window-image-plane? nw)))))


;;; The function `synchronize-native-window-with-image-plane' creates or
;;; modifies an existing native-window to match the shape of the given
;;; image-plane. Called only from transform-image.

(defun synchronize-native-window-with-image-plane (gensym-window workspace image-plane &optional variation
                                                                 ;; Added by SoftServe
                                                                 modal size-x size-y pos-x pos-y)
  (cond ((null (image-plane-native-window? image-plane))
	 (create-native-window-for-image-plane gensym-window workspace image-plane
	                                       ;; Added by SoftServe
                                               modal size-x size-y pos-x pos-y))
	(t
	 ;; TODO: synchronize layer position.
	 (synchronize-shape-of-native-image-plane image-plane variation)
	 (show-native-window (image-plane-native-window? image-plane)))))


(defun synchronize-zorder-of-native-image-plane (gensym-window image-plane stack-of-image-planes)
  (cond ((window-supports-zorder-native-window gensym-window)
	 (let ((previous-native-window?
		 (loop for (upper lower) on stack-of-image-planes
		       when (eq image-plane lower)
			 return (image-plane-native-window? upper))))
	   (zorder-native-window (image-plane-native-window? image-plane)
				 (if previous-native-window?
				     (native-window-handle previous-native-window?)
				     swp-hwnd-top))))
	(t
	 (synchronize-stacking-of-native-image-planes gensym-window stack-of-image-planes))))


;;; The function `refresh-native-image-plane' queues a refresh for a rectangle
;;; of the given native image-place. The rectangle is in the native window's
;;; client coordinates.

(defun refresh-native-image-plane (native-image-plane left top right bottom)
  (let ((dx (nip-x-offset native-image-plane))
	(dy (nip-y-offset native-image-plane))
	(current-draw-paper-p nil))	; FIXME
    (with-region-from-rectangle-void (region (+r left dx) (+r top dy)
					     (+r right dx) (+r bottom dy))
      (invalidate-region-of-image-plane native-image-plane region))))


;;; The function `paint-unused-area-of-native-image-plane', if the native-window
;;; is larger than its image-plane, erases the extra "gray" area.

(defun paint-unused-area-of-native-image-plane (native-image-plane)
  (let ((native-window (image-plane-native-window? native-image-plane)))
    (when (and (or (>f (native-window-width native-window)
		       (workspace-image-width native-image-plane))
		   (>f (native-window-height native-window)
		       (workspace-image-height native-image-plane))))
      (let ((dx (nip-x-offset native-image-plane))
	    (dy (nip-y-offset native-image-plane)))
	;; Hmm, this drawing bypasses the queues.
	(erase-complement native-window
			  (-r (image-plane-client-left native-image-plane) dx)
			  (-r (image-plane-client-top native-image-plane) dy)
			  (-r (image-plane-client-right native-image-plane) dx -1)
			  (-r (image-plane-client-bottom native-image-plane) dy -1))))))

;;; The function `reshape-native-window-and-update-scroll-bars' reshapes the
;;; native-window to the given rectangle, and removes scroll bars if possible.
;;; Variation is INFLATE, RESCALE, or RESHAPE (default)

(defun reshape-native-window-and-update-scroll-bars
    (native-window left top right bottom &optional variation)
  (cond ((not (native-image-plane? native-window))
	 (reshape-native-window native-window left top right bottom variation))
	((native-window-embedded-p native-window)
	 (update-native-scroll-bars (native-window-image-plane? native-window))
	 (canonicalize-scroll-position (native-window-image-plane? native-window)))
	(t
	 ;; TODO: Reshape and remove scroll bars in one step.
	 (reshape-native-window native-window left top right bottom variation)
	 (update-native-scroll-bars (native-window-image-plane? native-window))
	 (reshape-native-window native-window left top right bottom variation))))


(defun compute-delta-for-canonicalize-scroll-position
    (image-plane-left image-plane-right native-window-left native-window-right)
  (let ((dx (-f native-window-left image-plane-left)))
    (cond ((<f dx 0)			; Remove gray area on left
	   dx)
	  ((=f dx 0)			; Already minimal gray area on right
	   0)
	  (t				; Otherwise, reduce gray area on right, if any.
	   (maxr 0 (minr (-f native-window-right image-plane-right)
			 dx))))))

;;; The function `canonicalize-scroll-position' moves the image-plane relative
;;; to its native-window to ensure that there is no gray area in the window on
;;; the left or top, and that the gray area is minimized on the right and
;;; bottom.

(defun canonicalize-scroll-position (native-image-plane)
  (let* ((native-window (image-plane-native-window? native-image-plane))
	 (dx (compute-delta-for-canonicalize-scroll-position
	       (image-plane-client-left native-image-plane)
	       (image-plane-client-right native-image-plane)
	       (native-window-left native-window)
	       (native-window-right native-window)))
	 (dy (compute-delta-for-canonicalize-scroll-position
	       (image-plane-client-top native-image-plane)
	       (image-plane-client-bottom native-image-plane)
	       (native-window-top native-window)
	       (native-window-bottom native-window))))
    (unless (=r dx dy 0)
      ;; Adjust image-plane without affecting the native-window.
      (let ((native-image-plane-updated-by-client native-image-plane)
	    (native-window-client-operation 'scroll))
	(move-image-plane native-image-plane dx dy)))
    (update-native-scroll-bars native-image-plane)))

;; FIXME: A complete hack for the moment.
(defun inspect-workspace-p (workspace?)
  (and workspace?
       (non-kb-workspace-p workspace?)
       (name-or-names-for-frame workspace?)
       (symbolp (name-or-names-for-frame workspace?))
       (substring-equal #w"INSPECT" 0 7
			(symbol-namew (name-or-names-for-frame workspace?))
			0 (minf 7 (wide-string-length
				    (symbol-namew (name-or-names-for-frame workspace?)))))))


;;; The function `image-plane-fixed-size-native-window-p' returns true if G2
;;; should never resize the native-window for the image-plane. The user may
;;; still be able to resize it using window-system operations; however, scaling
;;; and shrink-wrapping the workspace, for example, will not.

(defun image-plane-fixed-size-native-window-p (image-plane)
  (and (scrollable-image-plane-p image-plane) ; FIXME: Not sure about this condition.
       (get-view-preference (image-plane-view-preferences image-plane) 'fixed-size)))

;;; The substitution-macro `unselectable-image-plane-p' returns true if the
;;; image-plane has been declared unselectable. You probably want to use
;;; `selectable-image-plane-p' instead of this function.

(def-substitution-macro unselectable-image-plane-p (image-plane)
  (get-view-preference (image-plane-view-preferences image-plane) 'unselectable))

(defun make-workspace-unselectable (workspace)
  (setf-view-preference (view-preferences workspace) 'unselectable t)
  workspace)


;;; The function `scale-to-fit-in-view-window-p' returns true if scale-to-fit
;;; operations on the given image-plane should fit into its view window, rather
;;; than the overall g2-window. This is true for embedded and "fixed size"
;;; views.

(defun scale-to-fit-in-view-window-p (image-plane)
  (or (embedded-image-plane-p image-plane)
      (image-plane-fixed-size-native-window-p image-plane)))


;;; The function `auto-scroll-bars-p' determines whether we should automatically
;;; add scroll bars to a native-window in order to keep it from growing larger
;;; than the g2-window.

(defun auto-scroll-bars-p (native-image-plane)
  (let ((workspace? (workspace-on-image-plane? native-image-plane)))
    (and workspace?
	 (or (>f (image-plane-client-bottom native-image-plane)
		 (usable-window-height native-image-plane))
	     (>f (image-plane-client-right native-image-plane)
		 (usable-window-width native-image-plane)))

	 ;; FIXME: Hack to the message board and inspect to scroll automatically.
	 (or (of-class-p-function workspace? 'message-board)
	     (inspect-workspace-p workspace?)))))

;;; The function `prefer-scroll-bars-p' determines whether we prefer to adjust
;;; scroll bars when an image-plane changes shape, rather than reshape the
;;; native-window. For now, this is only true when we've acquired scroll bars
;;; already through some other means.

(defun prefer-scroll-bars-p (native-image-plane)
  (let ((native-window (image-plane-native-window? native-image-plane)))
    (or (native-window-x-scroll? native-window)
	(native-window-y-scroll? native-window))))

(defun tabbed-mdi-p (gensym-window)
  (get-ui-property gensym-window 'tabbed-mdi))

(defun image-plane-maximized-p (image-plane)
  (and (native-image-plane-p image-plane)
       (native-window-maximized-p (image-plane-native-window? image-plane))))


;;; The function `image-plane-fixed-in-place-p' is true if the image-plane is
;;; constrained from moving (as opposed to scrolling) by the UI mode.

(defun image-plane-fixed-in-place-p (image-plane)
  (or (image-plane-maximized-p image-plane)
      (tabbed-mdi-p (gensym-window-for-image-plane image-plane))))

;;; Rectangles

(defun get-rectangle-center (left top right bottom)
  (values (halff (+f left right)) (halff (+f top bottom))))

(defun set-rectangle-center (center-x center-y left top right bottom)
  (multiple-value-bind (current-center-x current-center-y)
      (get-rectangle-center left top right bottom)
    (let ((x0 (-f center-x current-center-x))
	  (y0 (-f center-y current-center-y)))
      (values (+f left x0) (+f top y0) (+f right x0) (+f bottom y0)))))

(defun transpose-rectangles-centers (pinned-rectangle-left pinned-rectangle-top
				     pinned-rectangle-right pinned-rectangle-bottom
				     moved-rectangle-left moved-rectangle-top
				     moved-rectangle-right moved-rectangle-bottom)
  (multiple-value-bind (center-x center-y)
      (get-rectangle-center pinned-rectangle-left pinned-rectangle-top
			    pinned-rectangle-right pinned-rectangle-bottom)
    (set-rectangle-center center-x center-y
			  moved-rectangle-left moved-rectangle-top
			  moved-rectangle-right moved-rectangle-bottom)))

(defun get-rectangles-intersect
    (rectangle-1-left rectangle-1-top rectangle-1-right rectangle-1-bottom
     rectangle-2-left rectangle-2-top rectangle-2-right rectangle-2-bottom)
  (values (max rectangle-1-left rectangle-2-left)
	  (max rectangle-1-top rectangle-2-top)
	  (min rectangle-1-right rectangle-2-right)
	  (min rectangle-1-bottom rectangle-2-bottom)))

(defun get-transposed-rectangles-intersect
    (rectangle-1-left rectangle-1-top rectangle-1-right rectangle-1-bottom
     rectangle-2-left rectangle-2-top rectangle-2-right rectangle-2-bottom)
  (multiple-value-bind (left top right bottom)
      (transpose-rectangles-centers rectangle-1-left rectangle-1-top
				    rectangle-1-right rectangle-1-bottom
				    rectangle-2-left rectangle-2-top
				    rectangle-2-right rectangle-2-bottom)
    (get-rectangles-intersect rectangle-1-left rectangle-1-top
			      rectangle-1-right rectangle-1-bottom
			      left top right bottom)))

;;; The function `synchronize-shape-of-native-image-plane' is supposed to
;;; reshape a native-window to match its image-plane.

(defun synchronize-shape-of-native-image-plane (native-image-plane &optional variation)
  (let* ((native-window (image-plane-native-window? native-image-plane))
	 (gensym-window (native-window-gensym-window native-window))
	 (left (image-plane-client-left native-image-plane))
	 (top (image-plane-client-top native-image-plane))
	 (right (image-plane-client-right native-image-plane))
	 (bottom (image-plane-client-bottom native-image-plane)))

    ;; This has to be done before we change the position of a native-window,
    ;; since queued drawing for this image-plane assumes the previous
    ;; offset. TODO: only need to force drawing for the image-plane.
    #-SymScale
    (force-workstation-drawing (workstation-of-image-plane native-image-plane))
    #+SymScale
    (if (in-main-thread-p)
	(force-workstation-drawing (workstation-of-image-plane native-image-plane))
      (maybe-schedule-service-workstation
	(workstation-of-image-plane native-image-plane) t))

    (cond ((shape-decoupled-image-plane-p native-image-plane)) ; So far, just the native editor.

	  ((image-plane-fixed-size-native-window-p native-image-plane)
	   (canonicalize-scroll-position native-image-plane))
	   
	  ((not (scrollable-image-plane-p native-image-plane))
	   (reshape-native-window native-window left top right bottom variation))

	  ((or (native-window-maximized-p native-window)
	       (tabbed-mdi-p gensym-window)) ; Behave as if maximized.
	   (canonicalize-scroll-position native-image-plane))

	  ((eq transform-image-operation-hint 'scale-to-fit)
	   (reshape-native-window-and-update-scroll-bars
	     native-window left top right bottom variation))

	  ((auto-scroll-bars-p native-image-plane)
	   (setq right (minr right (usable-window-width native-image-plane))
		 bottom (minr bottom (usable-window-height native-image-plane)))
	   (reshape-native-window-and-update-scroll-bars
	     native-window left top right bottom variation))

	  ((prefer-scroll-bars-p native-image-plane)
	   ;; FIXME: These max/mins are just a heuristic for what parts of the
	   ;; IP to keep visible.
	   (setq left (maxr (native-window-left native-window) left)
		 top (maxr (native-window-top native-window) top)
		 right (minr (native-window-right native-window) right)
		 bottom (minr (native-window-bottom native-window) bottom))
	   (reshape-native-window-and-update-scroll-bars
	     native-window left top right bottom variation))

	  ((native-window-embedded-p native-window)
	   (canonicalize-scroll-position native-image-plane))

	  (t
	   (reshape-native-window native-window left top right bottom variation)))
    #+notyet (update-tracking-size native-image-plane)
    (recompute-visible-region-of-native-image-plane native-image-plane)))


;;; The function `synchronize-stacking-of-native-image-planes' reorders the
;;; native-windows on the client from scratch, to match the given order (which
;;; is top-to-bottom).

(defun synchronize-stacking-of-native-image-planes (gensym-window stack-of-image-planes)
  (let ((native-windows (loop for image-plane in stack-of-image-planes
			      as native-window? = (image-plane-native-window? image-plane)
			      when native-window? collect it using gensym-cons)))
    (when native-windows
      (stack-native-windows gensym-window native-windows)
      (reclaim-gensym-list native-windows))))

;; TODO: Maybe sync shapes, too, while we are at it (being careful to preserve
;; min/maximized state). Synchronize-everything -- something to do on full
;; refresh. The question is whether to take G2 as the master version or TW.


;;; The function `mega-refresh' forces a redraw of the entire MDI client frame,
;;; including the MDI background and the non-client areas of the native
;;; image-planes. Temporary workaround for refresh problems in 8.0 alpha.

(defun mega-refresh (gensym-window)
  (mega-refresh-1 gensym-window))

#+notyet
(defun update-tracking-size (image-plane)
  ;; This causes problems when inflating an image-plane. It also needs to "look
  ;; ahead" to see if removing scroll bars will make the image-plane fit.
  (when (scrollable-image-plane-p image-plane) ; TODO: Really has-resize-borders-p
    (set-maximum-tracking-size (image-plane-native-window? image-plane)
			       (workspace-image-width image-plane)
			       (workspace-image-height image-plane))))


;;; The function `move-native-image-plane-to' is the body of
;;; handle-window-moved, as well as the hack in absorb-local-event-ab-side-1 to
;;; update a native-window's position for each event.

;;; Its function is to update our local cache of the native-window's position,
;;; without changing the relative position of the image-plane within the
;;; native-window.

(defun move-native-image-plane-to (native-image-plane left top)
  (let* ((native-image-plane-updated-by-client native-image-plane)
	 (native-window-client-operation 'move)
	 (native-window (image-plane-native-window? native-image-plane))
	 (dx (-f left (native-window-left native-window)))
	 (dy (-f top  (native-window-top native-window))))
    (unless (=f dx dy 0)
      (move-image-plane native-image-plane dx dy)
      (let ((current-workstation (workstation-this-is-on (native-window-gensym-window native-window)))
	    (workspace (workspace-on-image-plane? native-image-plane)))
	  (when workspace
	    (trigger-user-icon-movement-rules-for-blocks workspace))))))

;;; The function `visible-region-of-native-window' returns the client region of
;;; the native-window, clipped to G2 window, but not to sibling windows.

(defun visible-region-of-native-window (gensym-window native-window)
  (let ((gensym-window-interior
	  (make-region-from-rectangle
	    (left-edge-of-window gensym-window)
	    (top-edge-of-window gensym-window)
	    (right-edge-of-window gensym-window)
	    (bottom-edge-of-window gensym-window)))
	(native-window-interior
	  (make-region-from-rectangle
	    (native-window-left native-window)
	    (native-window-top native-window)
	    (native-window-right  native-window)
	    (native-window-bottom native-window))))
    (prog1 (intersect-region gensym-window-interior native-window-interior)
      (reclaim-region gensym-window-interior)
      (reclaim-region native-window-interior))))


;;; The function `scroll-native-image-plane' bitblts the native image-plane by
;;; dx,dy and updates scroll bars.  Optionally returns the region which now
;;; needs refreshing.

(defun scroll-native-image-plane (native-image-plane dx dy &optional return-update-region?)
  (let ((gensym-window (gensym-window-for-image-plane native-image-plane))
	(native-window (image-plane-native-window? native-image-plane)))

    (scroll-native-window-1 gensym-window native-window dx dy)
    (update-native-scroll-bars native-image-plane)

    (when return-update-region?
      (let* ((src (visible-region-of-native-window gensym-window native-window))
	     (dst (shift-region (copy-region src) dx dy)))
	(prog1
	    (subtract-region src dst)
	  (reclaim-region src)
	  (reclaim-region dst))))))

(defun synchronize-unused-area-color (workspace)
  (let ((color (unused-area-color workspace)))
    (loop for image-plane in (image-planes-this-is-on workspace)
	  when (native-image-plane-p image-plane)
	    do (%set-native-window-background-color (image-plane-native-window? image-plane) color))))

(defun unused-area-color (workspace)
  (if (eq (unused-area-color? workspace) 'same-as-workspace)
      (workspace-background-color? workspace)
      (unused-area-color? workspace)))


;;;; Native Window/Image Plane Event Handlers


;;; The function `handle-native-window-event' processes some native-window
;;; events, returning T iff handled.

(defun handle-native-window-event (native-window key-code plist)
  (when (native-image-plane? native-window)
    (key-case key-code
      (window-refresh
	(handle-window-refresh-1 native-window plist)
	t)
      (window-moved
	(handle-window-moved-1 native-window plist)
	t)
      (window-sized
	(handle-window-sized-1 native-window plist)
	t)
      (window-closed
	(handle-window-closed-1 native-window plist)
	t))))

(defun handle-window-refresh-1 (native-window event-plist)
  ;; Only things refreshed by G2 need to be handled.
  (when (native-image-plane? native-window)
    (let* ((native-window-client-operation 'refresh)
	   (left (getf event-plist 'x))
	   (top (getf event-plist 'y))
	   (right (+f left (getf event-plist 'width)))
	   (bottom (+f top (getf event-plist 'height)))
	   (native-window-updated-by-client native-window)
	   (native-image-plane-updated-by-client (native-image-plane? native-window)))
      (refresh-native-image-plane (native-image-plane? native-window) left top right bottom))))

(defun handle-window-moved-1 (native-window event-plist)
  (let ((status (getf event-plist 'status))
	(x (getf event-plist 'x))
	(y (getf event-plist 'y))
	(native-window-updated-by-client native-window)
	(native-image-plane-updated-by-client (native-image-plane? native-window)))
    #+development (trace-native-window 'moved native-window x y status)
    (cond ((eql status #.size-minimized)
	   (%set-native-window-state native-window 'minimized))
	  ((null (native-image-plane? native-window))
	   (%move-native-window native-window x y)) ; FIXME: coor sys?
	  (t
	   (move-native-image-plane-to (native-image-plane? native-window) x y)))))

(defun window-state-name (status)
  (case status
    (#.size-restored 'restored)
    (#.size-minimized 'minimized)
    (#.size-maximized 'maximized)
    (#.size-maxshow   'maxshow)
    (#.size-maxhide   'maxhide)
    (#.status-floated 'floating)
    (#.status-docked 'docked)		; Old value, no indication of side.
    (#.status-autohidden 'autohidden)   ; This was called PINNED in 8.1 => behavioral change.
    (#.status-expanded 'autoshown)	; For symmetry with autohidden.
    (#.status-collapsed 'collapsed)	; No longer used
    (#.status-closed 'closed)		; Destroyed
    (#.status-attached 'attached)
    (#.status-docked-left 'left)
    (#.status-docked-top 'top)
    (#.status-docked-right 'right)
    (#.status-docked-bottom 'bottom)
    (#.status-hidden 'hidden)
    (t 'unknown)))

;; We handle resize by adjusting scroll bars (and noting min/maxed state).
;; TODO: If NW big enough to not have scroll bars, ensure positioned at UL.
;; TODO: Handle resize by scaling, limit max size to IP size, etc.

(defun handle-window-sized-1 (native-window event-plist)
  (let* ((native-window-client-operation 'resize)
	 (width (getf event-plist 'width))
	 (height (getf event-plist 'height))
	 (status (getf event-plist 'status))
	 (state (native-window-state native-window))
	 (new-state (window-state-name status))
	 (native-image-plane? (native-image-plane? native-window))
	 (native-window-updated-by-client native-window)
	 (native-image-plane-updated-by-client native-image-plane?))
    (unless (eq new-state 'minimized)        ; Windows sends 0,0 in this case.
      (%set-native-window-size native-window width height))
    (when native-image-plane?
      (recompute-visible-region-of-native-image-plane native-image-plane?))
    #+notyet (update-tracking-size native-image-plane?)
    (case new-state
      (restored
       (%set-native-window-state native-window 'normal)
       (when native-image-plane?
	 ;; We get a size-restored for most any reshape. It is a genuine
	 ;; restore-from-minimized only if we are currently minimized.
	 (cond ((eq state 'minimized)
		(unless (window-supports-scroll-while-minimized-fix
			  (gensym-window-for-image-plane native-image-plane?))
		  ;; If window didn't support updates while minimized, then
		  ;; update it at the moment it now.
		  (update-native-scroll-bars native-image-plane?)))
	       (t
		(canonicalize-scroll-position native-image-plane?)))))
      (minimized
       (%set-native-window-state native-window new-state))
      (maximized
       (%set-native-window-state native-window new-state)
       (when native-image-plane?
	 (canonicalize-scroll-position native-image-plane?)))

      ((floating docked autohidden autoshown collapsed attached left top right bottom hidden)
       (%set-native-window-state native-window new-state))

      (unknown)

      (t
       ;; SIZE_MAXSHOW and SIZE_MAXHIDE cases. Probably don't care.
       (when native-image-plane?
	 (update-native-scroll-bars native-image-plane?))))))

(defun handle-window-closed-1 (native-window event-plist)
  (declare (ignore event-plist))
;; Added by SoftServe for Gensym-381
  (when (eq (native-window-handle native-window) global-table-of-attributes-pane)
    (setf global-table-of-attributes-pane nil))
  (when (eq (native-window-handle native-window) global-table-of-hidden-attributes-pane)
    (setf global-table-of-hidden-attributes-pane nil))
;; End of SoftServ changes 
  (let* ((native-window-client-operation 'close)
	 (native-image-plane? (native-image-plane? native-window))
	 (native-window-updated-by-client native-window)
	 (native-image-plane-updated-by-client native-image-plane?))
    #+development (trace-native-window 'closed native-window)
    ;; Starts KB-level callbacks, if any.
    (note-native-window-event 'closed native-window)
    (cond (native-image-plane?
	   (delete-image-plane native-image-plane?))
	  (t
	   (when (native-window-item? native-window)
	     (delete-native-window-item native-window))
	   (reclaim-native-window native-window)))))


;;;; Scrolling Native Image Planes


(defparameter native-scrolling-line-height 10) ; Pixels to move on line-up/down

;; These can be negative, but aren't normally.
(defun image-plane-x-scroll-position (native-image-plane)
  (-r (native-window-left (image-plane-native-window? native-image-plane))
      ;; NOTE: Assuming never show workpace framing when we are scrolling.
      (left-edge-of-workspace-area-in-window native-image-plane)))

(defun image-plane-y-scroll-position (native-image-plane)
  (-r (native-window-top (image-plane-native-window? native-image-plane))
      (top-edge-of-workspace-area-in-window native-image-plane)))

;;; The function `update-native-scroll-bars' updates the thumb size and position
;;; of the horizontal and vertical scroll bars of image-plane (if any).

(defun update-native-scroll-bars (image-plane)
  (when (and (image-plane-native-window? image-plane)
	     (scrollable-image-plane-p image-plane)
	     ;; FIXME: hack
	     (not (native-editor-image-plane-p image-plane)))
    (let* ((gensym-window (gensym-window-for-image-plane image-plane))
	   (native-window (image-plane-native-window? image-plane))
	   (view-width (native-window-width native-window))
	   (view-height (native-window-height native-window))
	   (cxvscroll (get-system-metric gensym-window sm-cxvscroll 16))
	   (cyhscroll (get-system-metric gensym-window sm-cyhscroll 16))
	   (image-width  (workspace-image-width image-plane))
	   (image-height (workspace-image-height image-plane))
	   (xmin 0)
	   (xpos (maxr 0 (image-plane-x-scroll-position image-plane)))
	   (xmax (maxr 0 (-r image-width view-width)))
	   (ymin 0)
	   (ypos (maxr 0 (image-plane-y-scroll-position image-plane)))
	   (ymax (maxr 0 (-r image-height view-height)))
	   (old-hsb (not (null (native-window-x-scroll? native-window))))
	   (old-vsb (not (null (native-window-y-scroll? native-window))))
	   (new-hsb (>f xmax xmin))
	   (new-vsb (>f ymax ymin)))

      ;; If removing both scroll bars would open up enough space that we don't
      ;; need them, then do so.
      (when (and old-hsb old-vsb new-hsb new-vsb
		 (=f (image-plane-x-scroll-position image-plane) 0)
		 (=f (image-plane-y-scroll-position image-plane) 0)
		 (<=f xmax cxvscroll)
		 (<=f ymax cyhscroll))
	(setq new-hsb nil
	      new-vsb nil))
      
      ;; Recompute after accounting for space taken by scroll bars themselves.
      (when (neq old-hsb new-hsb)
	(if new-hsb
	    (decff view-height cyhscroll)
	    (incff view-height cyhscroll)))

      (when (neq old-vsb new-vsb)
	(if new-vsb
	    (decff view-width cxvscroll)
	    (incff view-width cxvscroll)))

      (setq xmax (maxr 0 (-r image-width view-width))
	    ymax (maxr 0 (-r image-height view-height))
	    new-hsb (>f xmax xmin)
	    new-vsb (>f ymax ymin))

      ;; Update our copy of local window with final decision.
      (when (neq old-hsb new-hsb)
	(if new-hsb
	    (decff (native-window-height native-window) cyhscroll)
	    (incff (native-window-height native-window) cyhscroll)))

      (when (neq old-vsb new-vsb)
	(if new-vsb
	    (decff (native-window-width native-window) cxvscroll)
	    (incff (native-window-width native-window) cxvscroll)))
      
      ;; The client computes the page size (length of proportional scroll bar).
      (manage-scrollbars-1 gensym-window native-window xmin xpos xmax ymin ypos ymax))))


;;; The function `invalidate-region-exposed-by-scrolling' invalidates the same
;;; region that windows does via ScrollWindow (except not accounting for
;;; overlying windows). We could simply wait for the refresh event to come back
;;; from the client, but we inval here to push it out sooner and reduce
;;; flashing. This does mean we get a double refresh for this region, and we
;;; still have to wait for the client to tell us about exposures out from under
;;; overlying windows.

(defun invalidate-region-exposed-by-scrolling (image-plane dx dy)
  (let* ((native-window (image-plane-native-window? image-plane))
	 (w (native-window-width native-window))
	 (h (native-window-height native-window)))
    (cond ((> dx 0)
	   (refresh-native-image-plane image-plane 0 0 dx h))
	  ((< dx 0)
	   (refresh-native-image-plane image-plane (+f w dx) 0 w h)))
    (cond ((> dy 0)
	   (refresh-native-image-plane image-plane 0 0 w dy))
	  ((< dy 0)
	   (refresh-native-image-plane image-plane 0 (+f h dy) w h)))))

;;; The function `scroll-image-plane-to' moves the image-plane to place the
;;; point (xpos,ypos) in the image-plane's "client coor" at (0,0) in the
;;; native-window's client coor. The native-window is not moved.

(defun scroll-image-plane-to (image-plane xpos ypos)
  (when (image-plane-native-window? image-plane)
    (let ((native-window (image-plane-native-window? image-plane)))
      (setq xpos (pin-in-range 0 xpos (-f (workspace-image-width image-plane)
					  (native-window-width native-window)))
	    ypos (pin-in-range 0 ypos (-f (workspace-image-height image-plane)
					  (native-window-height native-window))))
      (let ((dx (-f (image-plane-x-scroll-position image-plane) xpos))
	    (dy (-f (image-plane-y-scroll-position image-plane) ypos)))
	(unless (=f dx dy 0)
	  ;; (force-workstation-drawing (workstation-of-image-plane
	  ;; image-plane)) Here we want to move the image-plane *without*
	  ;; changing the native-window (the client-side instance or our local
	  ;; structure). Tell move-image-plane to do this by binding
	  ;; native-window-client-operation to SCROLL.
	  (let ((native-image-plane-updated-by-client image-plane)
		(native-window-client-operation 'scroll))
	    (move-image-plane image-plane dx dy))
	  ;; Push out a refresh, rather than waiting for the client to send
	  ;; expose events.
	  (invalidate-region-exposed-by-scrolling image-plane dx dy))))))

;;; The function `compute-scroll-position' returns the new scroll position given
;;; the symbolic operation and the old position, etc.

(defun compute-scroll-position (operation pos count thumb linesize pagesize)
  (case operation
    (thumbposition thumb)
    (thumbtrack    thumb)
    (home     0)
    (end      most-positive-fixnum)
    (rasterup (-r pos 1))
    (rasterdown (+r pos 1))
    (lineup   (-r pos (*f count linesize)))
    (linedown (+r pos (*f count linesize)))
    (pageup   (-r pos pagesize))
    (pagedown (+r pos pagesize))
    (t pos)))

(defun hscroll-image-plane (image-plane operation &optional (count 1) (thumb 0))
  (let* ((native-window (image-plane-native-window? image-plane))
	 (view-width (native-window-width native-window))
	 (pos (compute-scroll-position operation
				       (image-plane-x-scroll-position image-plane)
				       count thumb
				       native-scrolling-line-height
				       (maxr 1 (-r view-width native-scrolling-line-height)))))
    (scroll-image-plane-to image-plane pos (image-plane-y-scroll-position image-plane))))

(defun vscroll-image-plane (image-plane operation &optional (count 1) (thumb 0))
  (let* ((native-window (image-plane-native-window? image-plane))
	 (view-height (native-window-height native-window))
	 (pos (compute-scroll-position operation
				       (image-plane-y-scroll-position image-plane)
				       count thumb
				       native-scrolling-line-height
				       (maxr 1 (-r view-height native-scrolling-line-height)))))
    (scroll-image-plane-to image-plane
			   (image-plane-x-scroll-position image-plane)
			   pos)))

;;; The function `update-native-title-bar' updates the native title bar for
;;; image-plane, if any.

(defun update-native-title-bar (image-plane)
  (when (image-plane-native-window? image-plane)
    (let* ((workspace? (workspace-on-image-plane? image-plane))
	   (title? (workspace-title workspace?)))
      (when title?
	(when (image-plane-native-window? image-plane)
	  (caption-native-window (image-plane-native-window? image-plane) title?))
	(reclaim-text-string title?)))))


;;;; View Properties

;; TODO: def-view-property

(def-type-parameter view-properties-type ; These are just the settable properties.
    (structure
      ((title text)
       (visible-caption truth-value)
       (icon item-or-datum)		; Actually symbol-or-entity
       (state (member normal minimized maximized autohidden hidden docked floating closed))
       (dock (member left top right bottom float within none))
       (container (or (member pane mdi-child) ; Also: top-level, embedded
		      datum))		; A view designation
       (left integer)
       (top integer)
       (width integer)
       (height integer)
       (neighbor datum)			; A view-designation or a dialog control ID
       (floatable truth-value)
       (autohideable truth-value)
       (draggable truth-value)
       (closeable truth-value)
       (resizeable truth-value)
       (minimizeable truth-value)
       (maximizeable truth-value)
;       (x-scroll-bar (member always never automatic))
;       (y-scroll-bar (member always never automatic))
       (x-scroll-position integer)
       (y-scroll-position integer)
       (close-action (member destroy hide))
       (callback symbol)
       (min-width integer)
       (min-height integer))))

(defun container-name-p (thing)
  (and (symbolp thing)
       (or (null thing)
	   (memq thing '(pane mdi-child top-level embedded)))))

(defparameter readonly-view-properties '(handle class))
(defparameter all-view-properties (append readonly-view-properties
					  (mapcar 'car (cadr view-properties-type))
					  '(x-scale y-scale))) ; Workspace views only

(defun view-property-p (property)
  (memq property all-view-properties))

(defun readonly-view-property-p (property)
  (memq property readonly-view-properties))

(defun writeable-view-property-p (property)
  (and (view-property-p property)
       (not (readonly-view-property-p property))))

(defun copy-view-property (value)
  (get-reference-to-item-if-item
    (copy-if-text-string value)))

;;; The function `get-view-property' simply returns the value in the named slot,
;;; without any copying.  Must be called in temporary float context.

(defun get-view-property (native-window property)
  (assert-that-within-temporary-float-scope)
  (case property
    (handle (native-window-handle native-window))
    (container (native-window-type native-window))
    (name (native-window-name native-window))
    (callback (if (native-view-p native-window)
		  (native-view-callback? native-window))) ; A symbol
    (class (native-window-class native-window))
    (title (native-window-title? native-window))
    (visible-caption (native-window-has-style native-window ws-caption))
    (close-action (native-window-close-action native-window))
    (closeable (native-window-closeable native-window))
    (floatable (native-window-floatable native-window))
    (autohideable (native-window-autohidable native-window))
    (draggable (native-window-draggable native-window))
    (dock (native-window-dock native-window))
    (neighbor (native-window-neighbor? native-window))
    (minimizeable (native-window-has-style native-window ws-minimizebox))
    (maximizeable (native-window-has-style native-window ws-maximizebox))
    (resizeable (native-window-has-style native-window ws-thickframe))
    (icon (native-window-icon? native-window))
    (left (native-window-left native-window))
    (top (native-window-top native-window))
    (width (native-window-width native-window))
    (height (native-window-height native-window))
    (state (or (native-window-state native-window) 'normal))
    (x-scroll-position (native-window-x-scroll? native-window))
    (y-scroll-position (native-window-y-scroll? native-window))
    ((x-scale y-scale)			; Workspace views only
     (when (native-image-plane? native-window)
       (compute-user-image-plane-scale property (native-image-plane? native-window))))))

;;; The function `set-view-property' simply puts the value into the named slot,
;;; without any copying.

(defun set-view-property (native-window property value)
  (case property
    (handle (setf (native-window-handle native-window) value))
    (container (setf (native-window-type native-window) value))
    (callback (if (native-view-p native-window)
		  (setf (native-view-callback? native-window) (stored-callback-procedure value))))
;    (name (setf (native-window-name native-window) value))
    (class (setf (native-window-class native-window) value))
    (title (setf (native-window-title? native-window) value))
    (visible-caption (setf-bits (native-window-style native-window) ws-caption value))
    (close-action (setf (native-window-close-action native-window) value))
    (closeable (setf (native-window-closeable native-window) value))
    (floatable (setf (native-window-floatable native-window) value))
    (autohideable (setf (native-window-autohidable native-window) value))
    (draggable (setf (native-window-draggable native-window) value))
    (dock (setf (native-window-dock native-window) value))
    (neighbor (setf (native-window-neighbor? native-window) value))
    (minimizeable (setf-bits (native-window-style native-window) ws-minimizebox value))
    (maximizeable (setf-bits (native-window-style native-window) ws-maximizebox value))
    (resizeable (setf-bits (native-window-style native-window) ws-thickframe value))
    (icon (setf (native-window-icon? native-window) value))
    (left (setf (native-window-left native-window) value))
    (top (setf (native-window-top native-window) value))
    (width (setf (native-window-width native-window) value))
    (height (setf (native-window-height native-window) value))
    (state (setf (native-window-state native-window) value))
    (x-scroll-position (set-native-window-x-scroll native-window value))
    (y-scroll-position (set-native-window-y-scroll native-window value))))

(defun compute-user-image-plane-scale (x-or-y-scale image-plane)
  (assert-that-within-temporary-float-scope)
  (let ((gensym-window (gensym-window-for-image-plane image-plane)))
    (with-image-plane-transform (image-plane)
      current-frame-transform?
      (/e (/e (*e (coerce-to-gensym-float
		    (case x-or-y-scale
		      (x-scale current-image-x-scale)
		      (t current-image-y-scale)))
		  (coerce-to-gensym-float (normalized-scale)))
	      (coerce-to-gensym-float
		(get-gensym-window-parameter
		  gensym-window
		  (case x-or-y-scale
		    (x-scale 'default-x-scale)
		    (t 'default-y-scale)))))
	  (coerce-to-gensym-float (normalized-scale))))))

;;; The function `copy-view-options-into-structure' copies all known view
;;; options from the view's init-plist into the view's structure The actual
;;; implementation of the options (doing WM_SETICON, etc), happens on the TW
;;; side, in `process-view-init-plist'. Here we're just caching the values,
;;; mostly to make them easily readable by a KB.

(defun copy-view-options-into-structure (view plist)
  (loop for (property value) on plist by #'cddr
	when (writeable-view-property-p property)
	  do (set-view-property view property (copy-view-property value))))

(defun initialize-native-view (view gensym-window class container options &optional callback?)
  (initialize-native-window view gensym-window
			    (allocate-native-window-handle gensym-window) class)
  (initialize-native-window-type view container)
  (set-view-property view 'callback callback?)
  (copy-view-options-into-structure view options)
  view)


;;;; Image Plane Operations



;;; `do-projection-thru-region' is a macro for iterating over rectangles of a
;;; region.  It is used when you want to project a rectangle into N rectangles,
;;; one for each portion of the input rectangle that are overlaps part of the
;;; region.  This operation lies at the heart of clipping.

;;; For example in (do-projection-thru-regions ((a b c d) (w x y z) R) <body>)
;;; the body will be executed zero or more times with a..d bound to rectangles
;;; that are subsets of both the rectangle w..z and the region R.

;;; This guy is used only on the far side of the drawing queue (the dequeue end).

(defmacro do-projection-thru-region
    (((left-edge-of-task-segment top-edge-of-task-segment
				 right-edge-of-task-segment
				 bottom-edge-of-task-segment)
      (left-edge-of-entire-task top-edge-of-entire-task
				right-edge-of-entire-task
				bottom-edge-of-entire-task)
      region)
     &body body)
  (avoiding-variable-capture
      ( left-edge-of-entire-task
	 top-edge-of-entire-task
	 right-edge-of-entire-task bottom-edge-of-entire-task
	 region)
    `(do-region-rectangles
	 ((,left-edge-of-task-segment
	     ,top-edge-of-task-segment
	     ,right-edge-of-task-segment
	     ,bottom-edge-of-task-segment)
	  ,region
	  :clip-to
	  (,left-edge-of-entire-task
	     ,top-edge-of-entire-task
	     ,right-edge-of-entire-task
	     ,bottom-edge-of-entire-task))
       ,@body)))


(defun-void change-frame-description-reference-of-image-plane
    (image-plane frame-description-reference)
  (unless (eq frame-description-reference
	      (frame-description-reference-of-image-plane image-plane))
    (release-frame-description-reference-if-any
      (frame-description-reference-of-image-plane image-plane))
    (setf (frame-description-reference-of-image-plane image-plane)
	  (reference-frame-description-reference frame-description-reference))))




;;; `Get-available-image-plane' causes the top or bottom plane on pane to be
;;; available, according to whether on-the-bottom? is nil or non-nil,
;;; respectively.  (An image plane is `available' when it has no image.)  If
;;; there currently is an available image plane at the top of the stack, it is
;;; used (and is moved to the bottom if appropriate); otherwise, a new image
;;; plane is added to the stack.  The available plane is returned -- and should
;;; have an image put on it immediately.

;;; `Get-available-image-plane-on-top-of-another' is similar, but it causes the
;;; image plane directly on top of other-image-plane, which must be an existing
;;; image plane on pane, to be available.

;;; `Get-available-image-plane-below-another' is similar, but it causes the
;;; image plane directly below other-image-plane, which must be an existing
;;; image plane on pane, to be available.

(defun-simple get-available-image-plane
    (pane frame-description-reference on-the-bottom?)
  (new-get-available-image-plane
    pane
    frame-description-reference
    (if on-the-bottom? 'above 'below)
    nil))

;;; `new-get-available-image-plane' does what unifies various functions that
;;; got new image planes on top, bottom, or above and below other things
;;; in the stack.

(defun-simple new-get-available-image-plane
    (pane frame-description-reference above-or-below existing-image-plane?)
  (let ((gensym-window (gensym-window-for-pane pane))
	(image-plane (first (stack-of-image-planes pane))))
    (if (null (workspace-on-image-plane? image-plane))
	(initialize-image-plane-per-window-parameters
	  image-plane gensym-window)
	(setq image-plane
	      (let ((new-image-plane (get-new-image-plane pane)))
		(initialize-image-plane-per-window-parameters
		  new-image-plane gensym-window)
		(setf (left-edge-of-pane-in-window new-image-plane)
		      (left-edge-of-pane-in-window image-plane))
		(setf (top-edge-of-pane-in-window new-image-plane)
		      (top-edge-of-pane-in-window image-plane))
		(setf (right-edge-of-pane-in-window new-image-plane)
		      (right-edge-of-pane-in-window image-plane))
		(setf (bottom-edge-of-pane-in-window new-image-plane)
		      (bottom-edge-of-pane-in-window image-plane))
		(insert-image-plane-in-stack
		  pane new-image-plane above-or-below existing-image-plane?)
		new-image-plane)))

    #+development
    (when trace-image-planes-p
      (format t "new image-plane ~s~%" image-plane))
    (change-frame-description-reference-of-image-plane
      image-plane frame-description-reference)

    ;; Leftover drawing tasks! -fmw, 6/27/94
    (when (queue-non-empty-p
	    (image-plane-drawing-schedule image-plane))
      (reclaim-drawing-schedule (image-plane-drawing-schedule image-plane)))

    (recompute-visible-regions-for-pane pane)
    image-plane))

#+obsolete
(defun old-get-available-image-plane
    (pane frame-description-reference on-the-bottom?)
  (let ((gensym-window (gensym-window-for-pane pane))
	(image-plane (first (stack-of-image-planes pane))))
    (if (null (workspace-on-image-plane? image-plane))
	(initialize-image-plane-per-window-parameters
	  image-plane gensym-window)
	(setq image-plane
	      (let* ((listed-new-image-plane
		       (gensym-list (get-new-image-plane pane)))
		     (new-image-plane (car listed-new-image-plane)))
		(initialize-image-plane-per-window-parameters
		  new-image-plane gensym-window)
		(setf (left-edge-of-pane-in-window new-image-plane)
		      (left-edge-of-pane-in-window image-plane))
		(setf (top-edge-of-pane-in-window new-image-plane)
		      (top-edge-of-pane-in-window image-plane))
		(setf (right-edge-of-pane-in-window new-image-plane)
		      (right-edge-of-pane-in-window image-plane))
		(setf (bottom-edge-of-pane-in-window new-image-plane)
		      (bottom-edge-of-pane-in-window image-plane))     
		(setf (stack-of-image-planes pane)
		      (nconc listed-new-image-plane
			     (stack-of-image-planes pane)))
		new-image-plane)))
    (when on-the-bottom?
      (let* ((first-cons (stack-of-image-planes pane))
	     (second-cons? (cdr first-cons)))
	(setf (cdr first-cons) nil)
	(when second-cons?
	  (setf (stack-of-image-planes pane)
		(nconc second-cons? first-cons)))))
    (change-frame-description-reference-of-image-plane
      image-plane frame-description-reference)

    ;; Leftover drawing tasks! -fmw, 6/27/94
    (when (queue-non-empty-p
	    (image-plane-drawing-schedule image-plane))
      (reclaim-drawing-schedule (image-plane-drawing-schedule image-plane)))

    (recompute-visible-regions-for-pane pane)
    image-plane))

;;; `insert-image-plane-in-stack' returns the (eq) value of the stack
;;; after the modification.

(defun-simple insert-image-plane-in-stack
    (pane new-image-plane above-or-below existing-image-plane?)
  (cond
    ((null existing-image-plane?)
     (cond
       ((eq above-or-below 'below)
	(setf (stack-of-image-planes pane)
	      (graphics-cons-macro
		new-image-plane
		(stack-of-image-planes pane))))
       (t
	(setf (stack-of-image-planes pane)
	      (nconc (stack-of-image-planes pane)
		     (graphics-list new-image-plane))))))
    ((eq above-or-below 'above)
     (loop as prev-tail = nil then tail
	   for tail on (stack-of-image-planes pane)
	   as image-plane = (car tail)
	   when (eq image-plane existing-image-plane?)
	     do
	       (cond (prev-tail
		      (let ((new-cons
			      (graphics-cons new-image-plane tail)))
			(setf (cdr prev-tail) new-cons)))
		     (t
		      (graphics-push new-image-plane
				     (stack-of-image-planes pane))))
	       (return
		 (stack-of-image-planes pane))))
    (t
     #+development
     (unless (stack-of-image-planes pane)
       (error "bad assumption - tell JED"))
     (loop for tail on (stack-of-image-planes pane)
	   as image-plane = (car tail)
	   when (eq image-plane existing-image-plane?)
	     do
	       (let ((new-tail (graphics-cons new-image-plane (cdr tail))))
		 (setf (cdr tail) new-tail))
	       (return (stack-of-image-planes pane))))))

(defun-simple delete-image-plane-from-stack 
    (pane image-plane-to-delete)
  ;; it is probably superstitious to have this in a separate loop from
  ;; the next
  (loop for image-plane in (stack-of-image-planes pane)
	when (eq (superplane? image-plane) image-plane-to-delete)
	  do (setf (superplane? image-plane) nil)
	     (setf (superplane-coupling? image-plane) nil)
	     (return nil))
  (loop as l-trailer? = nil then l
	as l on (stack-of-image-planes pane)
	when (eq (car l) image-plane-to-delete)
	  do
	    (cond
	      (l-trailer?
	       (setf (cdr l-trailer?) (cdr l)))
	      (t
	       (setf (stack-of-image-planes pane) (cdr l))))
	    #+development
	    (unless (eq (pane-for-image-plane image-plane-to-delete) pane)
	      (error "deleting image-plane from wrong pane ~s"
		     image-plane-to-delete))
	    (setf (cdr l) (recycled-image-planes-for-pane pane))
	    (setf (recycled-image-planes-for-pane pane) l))
  (stack-of-image-planes pane))


#+obsolete
(defun get-available-image-plane-on-top-of-another
    (pane other-image-plane frame-description-reference)
  (let ((available-image-plane (get-available-image-plane
				 pane frame-description-reference nil)))
     (if (not (eq other-image-plane (car (cdr (stack-of-image-planes pane)))))
	 (loop with first-cons = (stack-of-image-planes pane)
	       with second-cons = (cdr first-cons)
	       for l-trailer = nil then l
	       as l = second-cons then (cdr l)
	       while l	; test unnec?
	       when (eq (car l) other-image-plane)
		 do (setf (cdr first-cons) l)
		    (setf (cdr l-trailer) first-cons)
		    (setf (stack-of-image-planes pane) second-cons)
		    (return nil)))
     (recompute-visible-regions-for-pane pane)
     available-image-plane))

#+obsolete
(defun get-available-image-plane-below-another (pane
						 other-image-plane
						 frame-description-reference)
  (let ((available-image-plane (get-available-image-plane
				 pane frame-description-reference nil)))
     (if (not (eq other-image-plane available-image-plane))  ; shouldn't happen
	 (loop with first-cons = (stack-of-image-planes pane)
	       for l on first-cons
	       when (eq (car l) other-image-plane)
		 do (setf (stack-of-image-planes pane)
			  (cdr first-cons))
		    (setf (cdr first-cons) (cdr l))
		    (setf (cdr l) first-cons)
		    (return nil)))
     (recompute-visible-regions-for-pane pane)
     available-image-plane))

;; Revise to always make a new image plane!  If the stack of image planes
;; consists of a single available image plane, delete that first!



(defun-simple get-new-image-plane (pane)
  (let ((recycled-image-planes-for-pane (recycled-image-planes-for-pane pane)))
    (cond
      (recycled-image-planes-for-pane
       (setf (recycled-image-planes-for-pane pane)
	     (cdr recycled-image-planes-for-pane))
       (setf (cdr recycled-image-planes-for-pane) nil)
       (let ((image-plane (car recycled-image-planes-for-pane)))
	 (reclaim-graphics-cons-macro recycled-image-planes-for-pane)
	 image-plane))
      (t
       (make-image-plane pane)))))


(defun make-top-plane (pane)
  (let* ((gensym-window (gensym-window-for-pane pane))
	 (stack-of-image-planes
	   (graphics-list (get-new-image-plane pane)))
	 (top-plane (first stack-of-image-planes)))
    (initialize-image-plane-per-window-parameters top-plane gensym-window)
    (setf (stack-of-image-planes pane) stack-of-image-planes)
   ;; (recompute-visible-regions-for-pane pane) -- done by caller
    top-plane))

;; This is used only in lay-out-area-of-window.  Consider incorporating it
;; there. Also, note that this one does not get its pane-area-hack slots set.

(defun-void make-pane-invisible (pane)
  (let* ((stack-of-image-planes (stack-of-image-planes pane)))
    (loop for image-plane in stack-of-image-planes
	  do (setf (right-edge-of-pane-in-window image-plane) ; zero area
		   (left-edge-of-pane-in-window image-plane))
	     (setf (bottom-edge-of-pane-in-window image-plane)
		   (top-edge-of-pane-in-window image-plane))
	     (when (workspace-on-image-plane? image-plane) ; fix workspace area
	       (set-up-loose-edges-for-workspace-area-within-pane image-plane)))
    (recompute-visible-regions-for-pane pane)))

(defun-void make-pane-visible (pane)
  (recompute-visible-regions-for-pane pane))



(def-substitution-macro image-plane-has-attached-planes-p (image-plane)
  (or (subplane? image-plane)
      (superplane? image-plane)))





;;; `Raise-image-plane-to-top' raises the image-plane, if necessary, so that it
;;; is the top top plane on its pane.  If do-not-refresh? is true, the pane
;;; will not be refreshed; this can be used by a caller that knows how to
;;; refresh more efficiently.

(defun raise-image-plane-to-top (image-plane &optional do-not-refresh?)
  (let* ((pane
	   (pane-for-image-plane image-plane))
	 (stack-of-image-planes
	   (stack-of-image-planes pane))
	 (top-image-plane
	   (first stack-of-image-planes)))

    #+development
    (when trace-image-planes-p
      (format t "raising ~s to top~%" image-plane))
    (unless (eq image-plane top-image-plane)

      (let ((old-visible-region
	      (copy-region
		(visible-region-of-image-plane image-plane))))

	(setf (stack-of-image-planes pane)
	      (graphics-cons image-plane
			     (delete-graphics-element image-plane stack-of-image-planes)))
	
	(recompute-visible-regions-for-pane pane)

	(let* ((new-visible-region
		 (visible-region-of-image-plane image-plane))
	       (exposed-region
		 (subtract-region
		   new-visible-region old-visible-region)))
	  
	  (unless do-not-refresh?
	    (invalidate-region-of-window (gensym-window-for-pane pane)
					 exposed-region))
	  
	  (reclaim-region old-visible-region)
	  (reclaim-region exposed-region))))

    ;; Raise the native window even if we think it doesn't need it, since the
    ;; windows on TW are not always in sync. -fmw, 2/23/06
    (when (image-plane-native-window? image-plane)
      (unless (eq native-image-plane-updated-by-client image-plane)
	(raise-native-window (image-plane-native-window? image-plane))))

    (unless (eq image-plane top-image-plane)
      ;; Only edit-in-place edit boxes have these, I think.
      (when (image-plane-has-attached-planes-p image-plane)
	(fix-up-superplanes-and-subplanes pane image-plane)))))



;;; The function `lower-image-plane-to-bottom' lowers the given image-plane to
;;; the bottom of the stacking order.

(defun lower-image-plane-to-bottom (image-plane)
  (let* ((pane
	   (pane-for-image-plane image-plane))
	 (stack-of-image-planes
	   (stack-of-image-planes pane))
	 (bottom-image-plane
	   (first (last stack-of-image-planes))))

    #+development
    (when trace-image-planes-p
      (format t "lowering ~s to bottom~%" image-plane))
    (unless (eq image-plane bottom-image-plane)
      (let ((old-visible-region
	      (copy-region
		(visible-region-of-image-plane image-plane))))

	(setf (stack-of-image-planes pane)
	      (nconc (delete-graphics-element image-plane stack-of-image-planes)
		     (graphics-list image-plane)))
	
	(recompute-visible-regions-for-pane pane)

	(let* ((new-visible-region
		 (visible-region-of-image-plane image-plane))
	       (exposed-region
		 (subtract-region
		   old-visible-region new-visible-region)))
	  
	  (invalidate-region-of-window (gensym-window-for-pane pane)
				       exposed-region)
	  (reclaim-region old-visible-region)
	  (reclaim-region exposed-region))))

    ;; Do in all cases. See above.
    (when (image-plane-native-window? image-plane)
      (unless (eq native-image-plane-updated-by-client image-plane)
	(lower-native-window (image-plane-native-window? image-plane))))

    (unless (eq image-plane bottom-image-plane)
      ;; Only edit-in-place edit boxes have these, I think.
      (when (image-plane-has-attached-planes-p image-plane)
	(fix-up-superplanes-and-subplanes pane image-plane)))))

;; Revise-pane has a bug where it refreshes more of the window than
;; necessary.  We work around that here by calling it only when
;; there are superplanes or subplanes to deal with. -fmw, 5/26/95



(defun bottom-image-plane? (pane)
  (let ((last-plane-with-image? nil))
    (loop with stack-of-image-planes = (stack-of-image-planes pane)
	  with top-plane = (car stack-of-image-planes)
	  for image-plane in stack-of-image-planes
	  when (and (not (eq image-plane top-plane))
		    (workspace-on-image-plane? image-plane))
	    do (setq last-plane-with-image? image-plane))
    last-plane-with-image?))
  

(defun top-image-plane? (pane)
  (loop for image-plane in (stack-of-image-planes pane)
	when (workspace-on-image-plane? image-plane)
	  return image-plane))




;;; The function `circulate-up' raises the bottom-most image-plane (with a
;;; workspace) to the top.

(defun circulate-up (pane)
  (let ((image-plane? (bottom-image-plane? pane)))
    (when image-plane?
      (raise-image-plane-to-top image-plane?))))



;;; The function `circulate-down' drops the top-most image-pane (with a
;;; workspace) to the bottom.

(defun circulate-down (pane)
  (let ((image-plane? (top-image-plane? pane)))
    (when image-plane?
      (lower-image-plane-to-bottom image-plane?))))



	  
;;; `Delete-image-planes-workspace-is-on' "deletes" (using delete-image-plane)
;;; all of the image planes, if any, workspace is on.

(defun delete-image-planes-workspace-is-on (workspace)
  (let ((image-planes (image-planes-this-is-on workspace)))
    (when image-planes
;      (when g2-has-v5-mode-windows-p
;	(send-representations-kb-workspace-remove workspace)) ;pbk 11/6/95 v5-tw-hook
      (setf (image-planes-this-is-on workspace) nil)
      (loop for image-plane in image-planes
	    when (workspace-on-image-plane? image-plane)
	      do (delete-image-plane image-plane))
      (reclaim-slot-value-list image-planes))))


;; This logic is very delicate, in its interaction with remove-image-if-any.



;;; `Delete-image-plane' deletes and recycles image-plane and returns true,
;;; provided there is at least one other image plane on the pane.  In any case,
;;; delete-image-plane removes the image, if any, from image-plane.  If an image
;;; of a temporary workspace is deleted), that temporary workspace is deleted,
;;; as is each of its subblocks to all levels.

;;; `Remove-image-if-any' removes the image on image-plane, if there is one.  If
;;; an image of a temporary workspace is removed, that temporary workspace is
;;; deleted, as is each of its subblocks to all levels.

(defun delete-image-plane (image-plane)
  (when (superplane? image-plane)
    (delete-image-plane (superplane? image-plane)))

  (with-drawing-trace (task)
    (when (queue-non-empty-p (image-plane-drawing-schedule image-plane))
      (format t "Drawing left on ~s: ~s~%"
	      image-plane (image-plane-drawing-schedule image-plane))))
  
  (let* ((current-pane (pane-for-image-plane image-plane))
	 (current-window (gensym-window-for-pane current-pane))
	 (workstation (workstation-this-is-on current-window))
	 (was-native? (native-image-plane-p image-plane)))

    ;; Note that the following can have side effects on the stack of image
    ;; planes.  For example, it may delete the workspace on the image plane
    ;; (i.e., if it is a temporary workspace), which may delete another
    ;; image plane, i.e., if there is a menu for that workspace up on an
    ;; image plane.  (This used to be a bug when we bound a lexical variable
    ;; up above to the accessor (stack-of-image-planes pane) and assumed
    ;; it could not become out of synch with the accessor across the
    ;; following change. Fixed today by getting rid of the variable and
    ;; simply using the accessor below.) (MHD/BAH 12/8/92)
    (remove-image-if-any image-plane)

    (when (not (null (cdr (stack-of-image-planes current-pane))))
      #+development
      (when trace-image-planes-p
	(format t "about to delete ~s~%" image-plane))
      (delete-image-plane-from-stack current-pane image-plane)
;      (setf (stack-of-image-planes current-pane)
;	    (reclaim-image-plane-in-list
;	      image-plane
;	      (stack-of-image-planes current-pane)))
      t)
    (remove-as-selected-image-plane workstation image-plane was-native?)
    (when (image-plane-native-window? image-plane)
      (reclaim-native-window-for-image-plane image-plane))))


(defun remove-image-if-any (image-plane)
  (let ((current-pane (pane-for-image-plane image-plane))
	(workspace? (workspace-on-image-plane? image-plane)))
    (when workspace?
      (let* ((left-edge-of-image-within-pane
	       (maxr (left-edge-of-image-in-window image-plane)
		     (left-edge-of-pane-in-window image-plane)))
	     (top-edge-of-image-within-pane
	       (maxr (top-edge-of-image-in-window image-plane)
		     (top-edge-of-pane-in-window image-plane)))
	     (right-edge-of-image-within-pane
	       (minr (right-edge-of-image-in-window image-plane)
		     (right-edge-of-pane-in-window image-plane)))
	     (bottom-edge-of-image-within-pane
	       (minr (bottom-edge-of-image-in-window image-plane)
		     (bottom-edge-of-pane-in-window image-plane)))
	     (gensym-window (gensym-window-for-pane current-pane)))
	(disassociate-workspace-and-image-plane workspace? image-plane)
	#+development
	(when trace-image-planes-p
	  (format t "about to take ~s off the window~%"
		  image-plane))
	(remove-image-plane-pointers-in-workstation-event-queue
	  (workstation-this-is-on gensym-window) image-plane)
	
	(setf (left-edge-of-image-in-window image-plane) 0)
	(setf (top-edge-of-image-in-window image-plane) 0)
	(setf (right-edge-of-image-in-window image-plane) 0)
	(setf (bottom-edge-of-image-in-window image-plane) 0)
	(setf (workspace-on-image-plane? image-plane) nil)

	(recompute-visible-regions-for-pane current-pane)

	(when (and (<r left-edge-of-image-within-pane
		       right-edge-of-image-within-pane)
		   (<r top-edge-of-image-within-pane
		       bottom-edge-of-image-within-pane))
	  (let ((current-window (gensym-window-for-pane current-pane)))
	    (unless (printing-window-p current-window)	    ; Don't invalidate printing windows

	      ;; This pushes a drawing task onto this image-plane!!

	      (invalidate-subsequence-of-image-planes-for-current-pane
		(memq image-plane (stack-of-image-planes current-pane))
		nil
		left-edge-of-image-within-pane
		top-edge-of-image-within-pane
		right-edge-of-image-within-pane
		bottom-edge-of-image-within-pane))))

	;; Discards the state, if any, associated with the drawing tasks.
	;; Have to do this here, since new drawing commands may have been
	;; enqueued by invalidate-subsequence-of-image-planes-for-current-pane!!
	;; -fmw, 6/28/94
	(discard-image-plane-drawing-queue-entry image-plane)
	(reclaim-drawing-schedule (image-plane-drawing-schedule image-plane))

	;; Guess what?  We don't invoke the reclaimers for image planes because
	;; we don't call reclaim-image-plane; instead we call a special-purpose
	;; reclaimer that puts the old image plane into a local pool.  Note also
	;; that the initialization of the slot (i.e., to nil) never happens due
	;; to the use of the special-purpose pool for "creation".
	;;
	;; That logic should be changed to be conventional, but that should be
	;; done later! In 4.0, we're adding it this way.  In 5.0, we're adding
	;; it this way until we can get a chance to revise as suggested above.
	;; Also, note that this means we don't have to do the fix that JED put
	;; in around show-workspace-1 -- that only fixed one instance of this
	;; bug, and wasn't a general solution.  (MHD 8/20/96)
	(reclaim-image-plane-cursors	; in place of reclaimer that's never called
	  (prog1 (image-plane-cursors image-plane)
	    (setf (image-plane-cursors image-plane) ; in place of initialization of the slot
		  nil)))

	(when (kb-workspace-p workspace?) ; Only care about these.
	  (let ((gensym-window (gensym-window-for-pane current-pane)))
	    (unless (printing-window-p gensym-window)
	      (note-workspace-hidden workspace? gensym-window))))

	(when (and (temporary-workspace-p workspace?)
		   (null (image-planes-this-is-on workspace?)))
	  (delete-frame workspace?))))

    workspace?))



;;; The function `reclaim-image-plane-in-list' removes the image-plane from the
;;; list and saves in onto the pane's list of available image planes

#+unused
(defun reclaim-image-plane-in-list (image-plane list-of-image-planes)
  (loop for some-image-plane in list-of-image-planes
	when (eq (superplane? some-image-plane) image-plane)
	  do (setf (superplane? some-image-plane) nil)
	     (setf (superplane-coupling? some-image-plane) nil)
	     ;; return now?!
	     )
  (loop as l-trailer? = nil then l
	as l on list-of-image-planes
	when (eq (car l) image-plane)
	  return				; return the revised list
	    (prog1
	      (cond
		(l-trailer?
		 (setf (cdr l-trailer?) (cdr l))
		 list-of-image-planes)
		(t (cdr l)))
	      (let ((current-pane (pane-for-image-plane image-plane)))
		(setf (cdr l) (recycled-image-planes-for-pane current-pane))
		(setf (recycled-image-planes-for-pane current-pane) l)))))


;;; `workspace-showing-p' is defined here because it is needed in the
;;; following function.  See the ";;;;" section on showing-p for
;;; documentation.

(def-substitution-macro workspace-showing-p (workspace classic-only-p)
  (or (image-planes-this-is-on workspace)
      (and (not classic-only-p)
	   (workspace-showing-on-ui-client-p workspace))))

(defun-simple workspace-showing-p-function (workspace classic-only-p)
  (workspace-showing-p workspace classic-only-p))

(defun-simple fixnum-from-normalized-value-or-managed-float (x)
  (if (fixnump x)
      x
      (rounde-first (*e (managed-float-value x)
			(coerce-to-gensym-float (normalized-scale))))))

(defun-simple unnormalized-managed-float-for-value (x)
  (allocate-managed-float
    (/e (coerce-to-gensym-float x) (coerce-to-gensym-float (normalized-scale)))))

(defun-void set-remembered-window-position-and-scale (workspace pane-name x y x-scale y-scale)
  (let* ((plist (plist-of-remembered-window-positions-and-scales workspace))
	 (remembered-window-position-and-scale
	   (or (getf plist pane-name)
	       (let ((value (slot-value-list 0 0 0 0)))
		 (setf (plist-of-remembered-window-positions-and-scales workspace)
		       (slot-value-cons pane-name (slot-value-cons value plist)))
		 value))))
    (setf (first remembered-window-position-and-scale)
	  (fixnum-from-normalized-value-or-managed-float x))
    (setf (second remembered-window-position-and-scale)
	  (fixnum-from-normalized-value-or-managed-float y))
    (setf (third remembered-window-position-and-scale)
	  (fixnum-from-normalized-value-or-managed-float x-scale))
    (setf (fourth remembered-window-position-and-scale)
	  (fixnum-from-normalized-value-or-managed-float y-scale))))


;; The function `discard-pending-workspace-drawing' discards pending KB drawing
;; associated with the workspace.  It MUST be called when a workspace becomes
;; completely hidden (ie, when (workspace-showing-p ws t) becomes nil), since at
;; that time the pending drawing of a workspace becomes inaccessable to
;; `propagate-all-workspace-changes-to-image-planes', and hence MUST be removed
;; from the cache count-of-pending-workspace-drawing.

;; This points out the extreme fragility of this cache (and all caches, for that
;; matter), and makes me want it to go away.

;; The pending drawing is not needed, of course, since the workspace will be
;; completely redrawn when it is first reexposed.  Note that this assumption
;; would fail if we ever cached the bits of hidden workspaces (unlikely).

;; Non-g2classic representations of the workspace do not count for visibility
;; since they are not considered by the drawing harness.  -fmw, 12/4/01

;; SymScale Notes: if the function is called by different worker threads on the
;; same workspace at the same time, the CAS-based fixes could make sure only one
;; worker can successfully do each of the work on CHANGED-BLOCKS-OF-WORKSPACE and
;; INVALID-REGION-OF-WORKSPACE? of the workspace. -- Chun Tian (binghe), 14/1/24

(defun discard-pending-workspace-drawing (workspace)
  (gensym-assert (not (workspace-showing-p workspace t)))
  (let ((blocks? (changed-blocks-of-workspace workspace))
	(region? (invalid-region-of-workspace? workspace)))
    (when (and blocks?
	       #+SymScale
	       (compare-and-swap (changed-blocks-of-workspace workspace) blocks? nil))
      ;; Maintain the invariant that changed-blocks-of-workspace is precisely the
      ;; list of subblocks of workspace with non-NIL block-changes.
      ;; remove-block-from-drawing-queues assumes this, for example.
      (loop for block in blocks? doing
	#+SymScale
	(let ((block-changes? (block-changes block)))
	  (if block-changes?
	      (let ((old? (block-changes block)))
		(when (and old? (compare-and-swap (block-changes block) old? nil))
		  (reclaim-block-change old?)))
	    (dwarn "Block ~s is in list for ~s but has no changes." block workspace)))
	#-SymScale
	(cond ((block-changes block)
	       (reclaim-block-change (block-changes block))
	       (setf (block-changes block) nil))
	      (t
	       (dwarn "Block ~s is in list for ~s but has no changes." block workspace))))
      (atomic-decff count-of-pending-workspace-drawing (length blocks?))
      (reclaim-slot-value-list blocks?)
      #-SymScale
      (setf (changed-blocks-of-workspace workspace) nil))
    (when (and region?
	       #+SymScale
	       (compare-and-swap (invalid-region-of-workspace? workspace) region? nil))
      (atomic-decff count-of-pending-workspace-drawing)
      (reclaim-workspace-region region?)
      #-SymScale
      (setf (invalid-region-of-workspace? workspace) nil))))

(defun disassociate-workspace-and-image-plane (workspace image-plane &optional keep-native-window)
  ;; Remember the layout for next time shown, except, do not remember the
  ;; layout from a printing window.
  (let* ((pane (pane-for-image-plane image-plane))
	 (pane-name (pane-name pane))
	 (gensym-window (gensym-window-for-pane pane))
	 (printing-window-p (printing-window-p gensym-window)))

    (unless printing-window-p
      (let ((default-x-scale (default-x-scale gensym-window))
	    (default-y-scale (default-y-scale gensym-window)))
	(set-remembered-window-position-and-scale
	  workspace pane-name
	  ;; Note A:
	  (delta-x-in-window
	    (x-origin-of-workspace-in-window-of-image-plane image-plane)
	    (scale-scale (normalized-scale) (normalized-scale) default-x-scale))
	  (delta-y-in-window
	    (y-origin-of-workspace-in-window-of-image-plane image-plane)
	    (scale-scale (normalized-scale) (normalized-scale) default-y-scale))
	  (scale-scale (image-x-scale image-plane) (normalized-scale) default-x-scale)
	  (scale-scale (image-y-scale image-plane) (normalized-scale) default-y-scale))))

    ;; Make this appear to have been recycled.
    (clear-image-plane-serial-number image-plane)

    ;; Discard the frame transforms...
    (reclaim-frame-transforms-of-blocks-in-image-plane
      (frame-transforms-of-blocks-in-image-plane image-plane))
    (setf (frame-transforms-of-blocks-in-image-plane image-plane) nil)

    ;; Discard the back pointer.
    (setf (image-planes-this-is-on workspace)
	  (delete-slot-value-element
	    image-plane (image-planes-this-is-on workspace)))

    ;; Discard pending drawing if this workspace is now entirely hidden in the
    ;; classic sense.
    (when (not (workspace-showing-p workspace t))
      (discard-pending-workspace-drawing workspace))

    ;; Reclaim the selection
    (when (image-plane-current-selection image-plane)
      (erase-and-reclaim-all-selection-highlights image-plane)
      (reclaim-selection (image-plane-current-selection image-plane))
      (setf (image-plane-current-selection image-plane) nil))

    ;; Reclaim the native-window
    (unless keep-native-window
      (when (image-plane-native-window? image-plane)
	(reclaim-native-window-for-image-plane image-plane)))

    ;; Reclaim the view preferences
    (set-image-plane-view-preferences image-plane nil)

    ;; Forward chain if this workspace is now entirely hidden.
    (unless (or (workspace-showing-p workspace nil)
		printing-window-p)
      (event-update-status-of-block-showing workspace image-plane nil))
    nil))

;; The logic of remembered-window-position-and-scale is adhoc.  The
;; If window A hides W, then window B hides W, window A show's W it
;; appears at window B's location.

;; Note A: the inverse of these scaling operations is performed in the code for
;; showing per the saved positions, i.e., in decode-evaluation-show-parameters,
;; where the numerator and denominator are reversed in the scale-scale calls.
;; This ends up giving resolution and platform-independent values.  (MHD
;; 2/17/95)



;;; `Associate-workspace-and-image-plane' is called to establish the
;;; relationship between a workspace and an image-plane.  If the
;;; image-plane is already bound to some other workspace that is
;;; backed out.  This should not be called to if the workspace is
;;; already on the image-plane.

(defun associate-workspace-and-image-plane (workspace image-plane)
  (when (workspace-on-image-plane? image-plane)
    (disassociate-workspace-and-image-plane
      (workspace-on-image-plane? image-plane)
      image-plane
      t))
  (set-image-plane-serial-number image-plane)
  (setf (workspace-on-image-plane? image-plane) workspace)
  (create-frame-transforms-of-image-plane workspace image-plane)
  (set-remaining-subblocks-of-workspace-to-draw image-plane nil)

  ;; Copy workspace's view preferences to the image-plane.
  (set-image-plane-view-preferences image-plane (view-preferences workspace))

  (slot-value-push image-plane (image-planes-this-is-on workspace)))

;; At present, this is called only by transform-image. -- ben 1/11/94



;;; `Valid-image-plane-p' is used in workstation contexts to check if
;;; image-planes are still ok, and also by UI commands.  Currently it just
;;; checks that the backpointers betwixt the workspace and the image-plane are
;;; correct.

(defun valid-image-plane-p (image-plane?)
  (when image-plane?
    (and
      (not (image-plane-unassociated-p image-plane?))
      (let ((workspace?
	      (workspace-on-image-plane? image-plane?)))
	(and workspace?
	     (memq image-plane? (image-planes-this-is-on workspace?)))))))

;; Used by tester-form-for-type.


;;; `Decode-window-position' returns either
;;;
;;;   (1) the pane containing this position
;;;   (2) the image-plane containing-this-position, if any; otherwise nil
;;;
;;; or
;;;
;;;   (1) nil

(defun decode-window-position (gensym-window x-in-window y-in-window)
  (loop for pane in (panes-in-window gensym-window)
	as stack-of-image-planes = (stack-of-image-planes pane)
	as top-plane = (first stack-of-image-planes)
	when (and (>=r x-in-window
		       (left-edge-of-pane-in-window top-plane))
		  (>=r y-in-window
		       (top-edge-of-pane-in-window top-plane))
		  (<r x-in-window
		      (right-edge-of-pane-in-window top-plane))
		  (<r y-in-window
		      (bottom-edge-of-pane-in-window top-plane)))
	  do (return
	       (values
		 pane
		 (loop for image-plane in stack-of-image-planes
		       when (and (not (minimized-image-plane-p image-plane))
				 (>=r x-in-window
				      (left-edge-of-view-in-window image-plane))
				 (>=r y-in-window
				      (top-edge-of-view-in-window image-plane))
				 (<r x-in-window
				     (right-edge-of-view-in-window
				       image-plane))
				 (<r y-in-window
				     (bottom-edge-of-view-in-window
				       image-plane)))
			 return image-plane)))))

;; by mhd, makes find-image-plane-for-window-position somewhat redundant!

;; Should return nearest image plane, within some limit?

;; Might tell you if the cursor is on a border between panes?



;;; `Find-image-plane-for-workspace-in-pane' returns either nil or the image
;;; plane showing workspace in pane.

(defun find-image-plane-for-workspace-in-pane (workspace pane)
  (loop for image-plane in (image-planes-this-is-on workspace)
	when (eq (pane-for-image-plane image-plane) pane)
	  return image-plane))






;;; `Remove-other-image-planes-in-pane' removes all image planes besides the
;;; supplied image-plane in the pane.

#+unused
(defun remove-image-plane-siblings (image-plane)
  ;; Remove other image planes:
  (loop for count from 1
	while (loop with pane = (pane-for-image-plane image-plane)
		    for ip in (stack-of-image-planes pane)
		    when (and (workspace-on-image-plane? ip)
			      (not (eq ip image-plane))
			      
			      ;; don't remove superplanes/subplanes: (check for
			      ;; possible additional levels of chain, too?!)
			      (not (eq (superplane? ip) image-plane))
			      (not (eq (superplane? image-plane) ip)))
		      do (delete-image-plane ip)
			 (return t))
	when (=f count 5000)		; sanity check!
	  do (notify-user-if-possible
	       "Removed ~d image planes, count too high, quitting!"
	       count)))





;;;; Showing-p




;;; `Showing-p' is the fundamental definition upon which update-only-when-
;;; shown is based.  This returns true if and only if the block in question has
;;; a superior which is a workspace, and that workspace is currently on any
;;; image-plane.  Showing is not the same as "a user can see it" for two
;;; reasons.  First issues of window boundries, obscuring, and scaling are all
;;; ignored.  Secondly embedded items, such as attributes are considered
;;; showing if thier containing item is visible.

;;; The routine `event-update-status-of-block-showing' provides event updates
;;; for some blocks in the system.

;; - ben 10/25/91

;;; Showing-p (and friends) is being extended to take into account
;;; new (Nevada) UI clients.  These predicates have a new argument to
;;; distinguish whether the caller only cares about "Classic" (i.e. LISP)
;;; Telewindows or not.

;; - jed 9/21/97


(defun-simple showing-p (block classic-only-p)
  (let ((workspace? (get-workspace-if-any-macro block)))
    (and workspace?
	 (workspace-showing-p workspace? classic-only-p)
	 t)))

;; This predicate should be available to end users, if only for documentation
;; reasons.

;; Note that if the workspace is being printed, then it has one image-plane
;; for that, and hence appears to be visible.

;; This is a performance hog, mostly due to the call in
;; fast-lookup-frame-description-reference-of-block?


  

;;; The system-variable `currently-exposed-workspaces' is maintained but
;;; never used.

(def-system-variable currently-exposed-workspaces panes nil)



;;; `Event-update-status-of-block-showing' is called when ever (showing-p
;;; <block>) changes for a block that are either workspaces or immediate
;;; subblocks of workspaces.  It wouldn't be difficult to traverse all blocks,
;;; but currently that isn't necessary.

;;; For all workspaces (kb, non-kb, whatever) it updates the 
;;; currently-exposed-workspace state within pending-kb-drawing.

;;; For workspaces it recurses on all the immediate subblocks, but not on the
;;; indirect subblocks.

;;; Some blocks (new-table, readout-table, variable, user-menu-choice, ...) are
;;; known to have cell arrays whose entries make use of the update-only-when-
;;; showing flag.  Event-update-status-of-cell-array-showing-p on those blocks.

;;; Other than recursive calls this routine is invoked from code in panes where
;;; workspaces are (de)associated with image-planes, and from code in
;;; transfer-item where blocks are tranfered from one workspace to another.  It
;;; is called only when the showing-p state is changing.  The block maybe active
;;; or inactive.

;; - ben 10/25/91, 2/12/93

(defun-void event-update-status-of-block-showing
    (block image-plane? now-showing?)
  (frame-class-case block
    (workspace
      (cond
	(now-showing?
	 ;; the pushnew below seems superfluous because one would
	 ;; assume that the currently-exposed-workspaces would always
	 ;; be in synch with the now-showing? arg of this function.
	 ;; (i.e. the  would not be in the list iff now-showing is T)
	 ;; For reasons beyond my comprehension this is not true, and
	 ;; multiple expose events are generated by calls to transform-image
	 ;; with arg workspace? = NIL.  (this occurs when the user presses
	 ;; cntrl-F repeatedly).  If some genius can prove that there
	 ;; is a rock-solid way of proving that a workspace is already
	 ;; showing (e.g. before cntrl-F/S/B is pressed), then the bug
	 ;; could be fixed in transform-image.
	 (graphics-pushnew block currently-exposed-workspaces))
	(t
	 (setf currently-exposed-workspaces
	       (delete-graphics-element block currently-exposed-workspaces))))

      (notice-workspace-exposure block now-showing?)

      (unless (non-kb-workspace-p block)
	(loop for subblock being each subblock of block do
	  (event-update-status-of-block-showing
	    subblock image-plane? now-showing?))))

    (trend-chart
      (update-trend-chart-for-exposure block now-showing?)
      (when (cell-array block)
	(event-update-status-of-cell-array-showing block now-showing?)))

    (t
      ;; Adjust the usage count for icon renderings. -fmw, 1/7/94
      (adjust-icon-rendering-usage-counts block image-plane? now-showing?)
      
      ;; Propagate this event to the cell arrays of any other kind of block.
      (when (cell-array block)
	(event-update-status-of-cell-array-showing block now-showing?)))))

;; This might have been implemented as a method, but it wasn't presumably for
;; reasons of efficency. - ben 2/12/92









;;;; Initializing Image Planes



;;; `Initialize-image-plane-per-window-parameters' initializes image-plane per
;;; the window parameters plist stored in gensym-window, and also performs
;;; reinitializations various other image-plane slots.

(defun-void initialize-image-plane-per-window-parameters (image-plane gensym-window)
  (setf (image-x-scale image-plane)
	(default-x-scale gensym-window))
  (setf (image-y-scale image-plane)
	(default-y-scale gensym-window))

  (setf (superplane? image-plane) nil)
  (setf (superplane-coupling? image-plane) nil)

  (setf (image-plane-close-box-situation image-plane) 'normal)
  nil)




;;; `Set-up-image-plane-for-top-bar' (1) sets up image-plane parameter slots
;;; that are required when there is a top bar, based upon gensym window
;;; parameters, (2) sets the image-plane-has-top-bar? slot to t, (3) sets up the
;;; image plane title slots, and (4) sets the top-edge-of-image-in-window slot
;;; appropriately.

;;(defun set-up-image-plane-for-top-bar (image-plane)
;;  (declare (ignore image-plane)))
;; This was based on the old scrolling stuff.


;;; `Update-titles-on-image-planes-workspace-is-on' ...

(defun-void update-titles-on-image-planes-workspace-is-on (workspace)
  (refresh-title-bar workspace))

;; Call this just after the primary name of the workspace changes!

;; Move this, or just put it in-line!








;;;; Revising Panes



;;; `Subplane?' is the inverse of superplane?  It is computed by searching
;;; the stack-of-image-planes.

(defun subplane? (image-plane)
  (loop for image-plane-1
	    in (stack-of-image-planes (pane-for-image-plane image-plane))
	when (eq (superplane? image-plane-1) image-plane)
	  return image-plane-1))


;;; `Revise-pane' revises the panes stack of image-planes by moving the
;;; image-plane the distance requested in the stack of image-planes.  Negative
;;; numbers move the image-plane up, i.e. closer to the user.  A fourth
;;; argument supresses the refreshing, this argument only makes sense if the
;;; delta is negative, i.e. the image is being raised.  The sub/super plane
;;; relationship is maintained.

(defun revise-pane (pane image-plane delta-position-index do-not-refresh?)
  (revise-pane-1 pane image-plane delta-position-index do-not-refresh?)
  ;; Hmm. This guy may do some refreshing.
  (fix-up-superplanes-and-subplanes pane image-plane))



;;; The function `fix-up-superplanes-and-subplanes' does something about
;;; subplanes and superplanes of the given image-plane.  At the moment, only
;;; floating edit-in-place edit boxes have them.

(defun fix-up-superplanes-and-subplanes (pane image-plane)
  (let ((current-pane pane)
	(did-something? nil))
    
    ;; Fix up subplanes, if any.
    (loop as superplane = image-plane
			then subplane?
	  for subplane? = (subplane? image-plane)
			then (subplane? subplane?)
	  while subplane?
	  do (let ((position-of-superplane
		     (position superplane (stack-of-image-planes pane)))
		   (position-of-subplane
		     (position subplane? (stack-of-image-planes pane))))
	       (setq did-something? t)
	       (revise-pane-1
		 pane subplane?
		 (-f position-of-superplane
		     (if (>f position-of-subplane position-of-superplane)
			 (-f position-of-subplane 1)
			 position-of-subplane))
		 nil)))

    ;; Fix up superplanes, if any.
    (loop for subplane = image-plane
		       then superplane?
	  as superplane? = (superplane? image-plane)
			 then (superplane? superplane?)
	  while superplane?
	  do (let ((position-of-subplane
		     (position subplane (stack-of-image-planes pane)))
		   (position-of-superplane
		     (position superplane? (stack-of-image-planes pane))))
	       (setq did-something? t)
	       (revise-pane-1
		 pane superplane?
		 (-f (if (<f position-of-superplane position-of-subplane)
			 (-f position-of-subplane 1)
			 position-of-subplane)
		     position-of-superplane)
		 nil)))
    (when did-something?
;      (when (native-windows-p (gensym-window-for-pane pane))
;	(synchronize-stacking-of-native-image-planes
;	  (gensym-window-for-pane pane) (stack-of-image-planes pane)))
      (recompute-visible-regions-for-pane pane))))


(defun revise-pane-1
    (pane image-plane delta-position-index do-not-refresh?)
  #+development
  (when trace-image-planes-p
    (format t "revising pane on ~s delta=~s refresh?=~s~%"
	    image-plane delta-position-index do-not-refresh?))
  (loop as old-position-index? = 0 then (+f old-position-index? 1) 
	as old-position-trailer? = nil then l
	as l = (stack-of-image-planes pane) then (cdr l)
	when (null l)
	  do (setq old-position-index? nil)
	     (loop-finish)
	when (eq (car l) image-plane)
	  do (if old-position-trailer?
		 (setf (cdr old-position-trailer?) (cdr l))
		 (setf (stack-of-image-planes pane) (cdr l)))
	     (reclaim-graphics-cons l)
	     (loop-finish)
	finally
	  (let* ((new-position-index
		   (if (<f delta-position-index 0)
		       (maxf (+f (or old-position-index? 0) delta-position-index)
			     0)
		       (minf (+f (or old-position-index? 0)
				 delta-position-index)
			     ;;   maximum index: (Notice that length of
			     ;;   stack has been already been shortened by
			     ;;   one and will be increased by one below.
			     ;;   This used to subtract one from the length,
			     ;;   which I fixed.  (MHD 1/29/90))
			     (length (stack-of-image-planes pane)))))
		 (moved-image-plane-listed
		   (let ((new-position-trailer?
			   (if (>f new-position-index 0)
			       (nthcdr (-f new-position-index 1)
				       (stack-of-image-planes pane)))))
		     (if new-position-trailer?
			 (setf (cdr new-position-trailer?)
			       (graphics-cons image-plane
					      (cdr new-position-trailer?)))
			 (setf (stack-of-image-planes pane)
			       (graphics-cons image-plane
					      (stack-of-image-planes pane)))))))
	    (recompute-visible-regions-for-pane pane)

	    ;; Synchronize entire native window stack.
	    (when (native-windows-p (gensym-window-for-pane pane))
	      (synchronize-zorder-of-native-image-plane
		(gensym-window-for-pane pane) image-plane (stack-of-image-planes pane))
	      ;; We will get refresh events.
	      (setq do-not-refresh? t))

	    ;; The following was from before to after the previous form; having
	    ;; it before caused extra refreshing to happen when there was a
	    ;; plane to raise. (MHD 2/3/90)
	    (unless do-not-refresh?
	      (let* ((left-edge-of-image-within-pane
		       (maxr (left-edge-of-image-in-window image-plane)
			     (left-edge-of-pane-in-window image-plane)))
		     (top-edge-of-image-within-pane
		       (maxr (top-edge-of-image-in-window image-plane)
			     (top-edge-of-pane-in-window image-plane)))
		     (right-edge-of-image-within-pane
		       (minr (right-edge-of-image-in-window image-plane)
			     (right-edge-of-pane-in-window image-plane)))
		     (bottom-edge-of-image-within-pane
		       (minr (bottom-edge-of-image-in-window image-plane)
			     (bottom-edge-of-pane-in-window image-plane))))
		(when (and (<r left-edge-of-image-within-pane
			       right-edge-of-image-within-pane)
			   (<r top-edge-of-image-within-pane
			       bottom-edge-of-image-within-pane))
		  (cond
		    ((or (null old-position-index?)
			 (<f new-position-index old-position-index?))
		     (invalidate-reordered-image-planes
		       (gensym-window-for-pane pane)
		       left-edge-of-image-within-pane
		       top-edge-of-image-within-pane
		       right-edge-of-image-within-pane
		       bottom-edge-of-image-within-pane
		       (stack-of-image-planes pane) image-plane
		       moved-image-plane-listed old-position-trailer? pane))
		    ((>f new-position-index old-position-index?)
		     (invalidate-reordered-image-planes
		       (gensym-window-for-pane pane)
		       left-edge-of-image-within-pane
		       top-edge-of-image-within-pane
		       right-edge-of-image-within-pane
		       bottom-edge-of-image-within-pane
		       (stack-of-image-planes pane) nil
		       old-position-trailer?
		       (nthcdr
			 (-f new-position-index 1)
			 (stack-of-image-planes pane))
		       pane)))))))))

;; The guard against image-plane not being in the stack is unnecessary. - ben 4/11/93

;; Revised to work and to support functionality needed in BOOKS (for lifting an
;; entire substack of logbook page image planes to the top) and in PANES (for
;; raise-image- plane-to-top and lower-image-plane-to-bottom).  (MHD 2/3/90)

;; Note that the do-not-refresh? arg was already defined
;; raise-image-plane-to-top?, and I added it to revise-pane (with identical
;; documentation) to support the former's use of the latter.  (MHD 2/3/90)

;; Consider testing, before projecting, that
;;    (and (<r left-edge-of-image-within-pane right-edge-of-image-within-pane)
;;	   (<r top-edge-of-image-within-pane bottom-edge-of-image-within-pane)).










;;;; Pane Cursors



;;; A `pane cursor' is a graphic that overlays the entire pane, it is used, for
;;; example, to animate the dragging of an image-plane.  It is represented as a
;;; list of the form (color {rectangle}).  The rectangles here are a
;;; list of the form:
;;;  (left-edge-in-window top-edge-in-window
;;;   right-edge-in-window bottom-edge-in-window).

;;; Each pane cursor reside as an element of the list in the pane-cursors slot
;;; of the pane. They are entirely constructed from graphic conses.

(def-concept pane-cursor)

;;; `Draw-or-erase-pane-cursor' is used to update the exposure of individual
;;; pane cursors.  No useful value is returned

(defun-void draw-or-erase-pane-cursor (erase? pane-cursor pane)
  (let* ((top-plane (first (stack-of-image-planes pane)))	; ugly
	 (left-edge-of-pane-in-window
	   (left-edge-of-pane-in-window top-plane))
	 (top-edge-of-pane-in-window
	   (top-edge-of-pane-in-window top-plane))
	 (right-edge-of-pane-in-window
	   (right-edge-of-pane-in-window top-plane))
	 (bottom-edge-of-pane-in-window
	   (bottom-edge-of-pane-in-window top-plane)))
    (update-window
      (gensym-window-for-pane pane)
      left-edge-of-pane-in-window top-edge-of-pane-in-window
      right-edge-of-pane-in-window bottom-edge-of-pane-in-window
      'add-from-pane-cursor-to-current-window
      erase? pane-cursor pane
      left-edge-of-pane-in-window top-edge-of-pane-in-window
      right-edge-of-pane-in-window bottom-edge-of-pane-in-window)))

;; This is one of the routines that presumes there is always something
;; in the image-plane stack. - ben 12/3/93



;;; `Add-pane-cursor,' is used to add individual pane cursors to a pane.  The
;;; added cursor is drawn and returned.

(defun-simple add-pane-cursor (pane-cursor pane)
  (graphics-push pane-cursor (pane-cursors pane))
  (draw-or-erase-pane-cursor nil pane-cursor pane)
  pane-cursor)



;;; `Delete-pane-cursor' is used to remove individual pane cursors from a pane.
;;; the pane cursor is erased, and reclaimed.  No useful value is returned.

(defun-void delete-pane-cursor (pane-cursor pane)
  (draw-or-erase-pane-cursor t pane-cursor pane)
  (setf (pane-cursors pane)
	(delete-graphics-element pane-cursor (pane-cursors pane)))
  (reclaim-graphics-tree pane-cursor))


;;; `Move-pane-cursor' offsets an individual pane cursor.  It is erased, each
;;; rectangle is offset, and then redrawn.  No useful value is returned.

(defun-void move-pane-cursor
       (pane-cursor pane delta-x-in-window delta-y-in-window)
  (draw-or-erase-pane-cursor t pane-cursor pane)
  (loop for rectangle in (cdr pane-cursor)
	do (incfr (first rectangle) delta-x-in-window)
	   (incfr (second rectangle) delta-y-in-window)
	   (incfr (third rectangle) delta-x-in-window)
	   (incfr (fourth rectangle) delta-y-in-window))
  (draw-or-erase-pane-cursor nil pane-cursor pane))

;; Later, handle moving individual edges of a image plane border, with
;; individual "delta edge in window" arguments, avoiding unnecessary erasing and
;; redrawing!



;;; `Add-from-pane-cursor-to-current-window' will add a single pane cursor to
;;; the current window.  This is called to draw/erase the set of all pane
;;; cursors and in modification of individual pane cursors.

(defun add-from-pane-cursor-to-current-window
    (subtract-instead?
      pane-cursor pane
      left-edge-of-area top-edge-of-area
      right-edge-of-area bottom-edge-of-area)
  (with-out-native-image-plane ()
    (with-transfer-mode-when-drawing (:xor)
      (loop with pane-background-color-or-tiling-pattern
	      = (or #+development overriding-pane-background-color-or-tiling-pattern?
		    (pane-background-color-override? pane)
		    (pane-background-color-or-tiling-pattern pane))
	    with pane-cursor-color-difference
	      = (color-difference
		  (map-to-color-value (car pane-cursor))
		  (map-to-color-value
		    (if (symbolp pane-background-color-or-tiling-pattern)
			pane-background-color-or-tiling-pattern
			tiling-pattern-background-color)))	    ; some color in the pattern?

	    as (left top right bottom) in (cdr pane-cursor)
	    as left-edge-of-rectangle-within-area	; use macros for some of this?
	       = (left-edge-within-area left left-edge-of-area)
	    as top-edge-of-rectangle-within-area
	       = (top-edge-within-area top top-edge-of-area)
	    as right-edge-of-rectangle-within-area
	       = (right-edge-within-area right right-edge-of-area)
	    as bottom-edge-of-rectangle-within-area
	       = (bottom-edge-within-area bottom bottom-edge-of-area)
	    when (and (<r left-edge-of-rectangle-within-area
			  right-edge-of-rectangle-within-area)
		      (<r top-edge-of-rectangle-within-area
			  bottom-edge-of-rectangle-within-area))
	      do (add-solid-rectangle-to-current-window
		   subtract-instead?
		   left-edge-of-rectangle-within-area
		   top-edge-of-rectangle-within-area
		   right-edge-of-rectangle-within-area
		   bottom-edge-of-rectangle-within-area
		 pane-cursor-color-difference)))))



;;; The substitution-macro `add-pane-cursors-to-current-window' will draw/erase
;;; the pane-cursors of a pane.  This routine must be called whenever a region
;;; of the screen is drawn from scratch, otherwise holes will appear in the
;;; pane cursors.  Avoiding this bug requires testing all code that erases with
;;; a pane cursor over the area when the erase occurs.

;;; The edges given must be clipped inside of the draw area.

(def-substitution-macro add-pane-cursors-to-current-window
    (pane left-edge-of-area top-edge-of-area
	  right-edge-of-area bottom-edge-of-area)
  (loop for pane-cursor in (pane-cursors pane) doing
    (add-from-pane-cursor-to-current-window
      nil pane-cursor pane left-edge-of-area top-edge-of-area
      right-edge-of-area bottom-edge-of-area)))



;;; The macro `with-open-cursors' runs its body with all cursor-like objects
;;; removed from the given region (in window coordinates), and then puts them
;;; back after the body finishes.  Cursors are any XOR objects living in the
;;; topmost drawing layer.  This includes pane cursors, image-plane cursors,
;;; and objects in the XOR overlay (eg, those being dragged).

(defmacro with-open-cursors ((left top right bottom &key
				   (condition t)
				   (pane-cursors t)	    ; Include pane cursors?
				   (image-plane-cursors t)  ; Include image-plane cursors?
				   (xor-overlay nil)	    ; Include XOR overlay?
				   (zero-time nil))
			     &body body)
  (avoiding-variable-capture (condition pane-cursors
					image-plane-cursors xor-overlay)
    (let ((draw-cursors `(add-cursors-to-current-window ,left ,top ,right ,bottom
							,pane-cursors
							,image-plane-cursors
							,xor-overlay)))
      (when (eq zero-time t)
	(setq draw-cursors `(with-zero-drawing-time ,draw-cursors)))
      (unless (eq condition t)
	(setq draw-cursors `(when ,condition ,draw-cursors)))
      `(unwind-protect-for-development with-open-cursors
	   (progn
	     ,draw-cursors
	     ,@body)
	 ,draw-cursors))))



;;; `Add-image-plane-border-as-pane-cursor' creates a pane cursor that is
;;; graphically the same as the border of basis-image-plane; adds it to the pane
;;; that contains basis- image-plane, offset by (x-offset, y-offset); and
;;; finally draws it.  The pane cursor is returned.

;;; The outside edges of the image plane border are normally derived from the
;;; image plane edges. But any of these edges may be overridden by supplying any
;;; or all of the optional left, top, right, or bottom edges of image in window
;;; arguments.  This feature is useful for implementing rubber-band style sizing
;;; and lassoing user interactions.

(defun add-image-plane-border-as-pane-cursor (basis-image-plane x-offset y-offset)
  (let* ((pane (pane-for-image-plane basis-image-plane))
	 (cursor-pen-width 2)
	 (left-edge-of-border
	   (+r (left-edge-of-view-in-window basis-image-plane)
	       x-offset))
	 (top-edge-of-border
	   (+r (top-edge-of-view-in-window basis-image-plane)
	       y-offset))
	 (right-edge-of-border
	   (+r (right-edge-of-view-in-window basis-image-plane)
	       x-offset))
	 (bottom-edge-of-border
	   (+r (bottom-edge-of-view-in-window basis-image-plane)
	       y-offset))
	 (left-edge-of-area-inside-borders		; only used once
	   (+r left-edge-of-border cursor-pen-width))
	 (top-edge-of-area-inside-borders
	   (+r top-edge-of-border cursor-pen-width))
	 (right-edge-of-area-inside-borders		; only used once
	   (-r right-edge-of-border cursor-pen-width))
	 (bottom-edge-of-area-inside-borders
	   (-r bottom-edge-of-border cursor-pen-width)))
    (add-pane-cursor
      (graphics-list
	(if (mdi-frame-p (gensym-window-for-pane pane)) 'light-gray 'black)
	(graphics-list
	  left-edge-of-border top-edge-of-border
	  right-edge-of-border top-edge-of-area-inside-borders)
	(graphics-list
	  left-edge-of-border top-edge-of-area-inside-borders
	  left-edge-of-area-inside-borders bottom-edge-of-area-inside-borders)
	(graphics-list
	  right-edge-of-area-inside-borders top-edge-of-area-inside-borders
	  right-edge-of-border bottom-edge-of-area-inside-borders)
	(graphics-list
	  left-edge-of-border bottom-edge-of-area-inside-borders
	  right-edge-of-border bottom-edge-of-border))
      pane)))

;; Consider having an optional color argument.



;;; `Add-plus-sign-as-pane-cursor' creates a pane cursor in the shape of a plus
;;; sign of the specified width, height, stroke-width, and color; adds it to
;;; pane at position (center-x, center-y); and finally draws it.  The pane
;;; cursor is returned.  Stroke- width is assumed to be less than both width and
;;; height.

(defun add-plus-sign-as-pane-cursor
       (pane center-x center-y width height stroke-width color)
  (let* ((left-edge-of-plus-sign
	   (-r center-x (halfr width)))
	 (top-edge-of-plus-sign
	   (-r center-y (halfr height)))
	 (left-edge-of-vertical-stroke
	   (-r center-x (halfr stroke-width)))
	 (top-edge-of-horizontal-stroke
	   (-r center-y (halfr stroke-width)))
	 (right-edge-of-vertical-stroke
	   (+r left-edge-of-vertical-stroke stroke-width))
	 (bottom-edge-of-horizontal-stroke
	   (+r top-edge-of-horizontal-stroke stroke-width)))
    (add-pane-cursor
      (graphics-list
	color
	(graphics-list
	  left-edge-of-vertical-stroke top-edge-of-plus-sign
	  right-edge-of-vertical-stroke top-edge-of-horizontal-stroke)
	(graphics-list
	  left-edge-of-plus-sign top-edge-of-horizontal-stroke
	  (+r left-edge-of-plus-sign width) bottom-edge-of-horizontal-stroke)
	(graphics-list
	  left-edge-of-vertical-stroke bottom-edge-of-horizontal-stroke
	  right-edge-of-vertical-stroke (+r top-edge-of-plus-sign height)))
      pane)))







;;;; Drawing On A Particular Image Plane

;; Fix documentation for changes and to include refreshing-from-image-plane and
;; for-image-plane!!!




;;; `Drawing' refers to the drawing or erasing of images of workspace elements
;;; on the current image plane, insofar as they fit within that portion of the
;;; workspace area of image-plane-with-image, if any, that is within the pane.

;;; This section introduces the name dynamic extents required to do drawing to a
;;; particular image-plane.  These all require that an on-window-with-drawing
;;; extent has been established.  On-window-with-drawing provides sufficent
;;; context for extremely simple drawing, for example the drawing the "paper"
;;; (i.e.  the pane and image-plane backgrounds and borders.

;;; `Simple-for-image-plane' provides sufficent context to enable refreshing
;;; from graphic element memory.  `For-image-plane' provides sufficent context
;;; for workspace drawing and is used for most drawing in G2.

;;; The act of establishing both an on-window-with-drawing context and then
;;; immediately a for-image-plane context is known as going "on image-plane" and
;;; the macro on-image-plane is provided for establishing both in one fell
;;; swoop.  The term "on-image-plane" is used in two slightly different ways.
;;; First to describe the execution time act of establishing the dynamic extent
;;; necessary to draw a something that resides in a workspace on one of the
;;; image-planes showing that workspace.

;;; Secondly it is used to describe the structural relationship between an
;;; image-plane and the workspace, i.e.  a workspace is said to be "on an
;;; image-plane." The image-plane has a workspace-on-image-plane slot and
;;; meanwhile the workspace has an image-planes-this-is-on slot.

;;; Recall that it is illegal to recursively enter on-window, since ICP message
;;; groups don't nest.

;;; Bear in mind that both on-window-with-drawing and on-image-plane are
;;; expensive both lexically and dynamicly.

(def-named-dynamic-extent simple-for-image-plane
  (module panes)
  (dynamic-superior on-window-without-drawing))

(def-named-dynamic-extent for-image-plane
  (module panes)
  (includes simple-for-image-plane)
  (dynamic-superior on-window-without-drawing))





;;; `Current-image-plane' is bound and never rebound within an
;;; simple-for-image-plane context.

(defvar-of-named-dynamic-extent current-image-plane simple-for-image-plane)


;;; Drawing style is dynamicly controled by rebinding these variables.
;;;   current-drawing-transfer-mode
;;;   current-{fore, back}ground-color-value
;;;   current-image-{x, y}-scale
;;;   {x, y}-origin-of-current-workspace
;;;   current-text-box-format
;;;   current-text-cell-plist
;;; Any color differences passed to drawing primitives should be identical
;;; to those implied by the fore and background color bindings.  Individual
;;; block draw methods will rebind these as approprate.

;;; Most of these are part of the for-image-plane context, but current-{fore,
;;; back}ground-color-value and current-drawing-transfer-mode are part of the
;;; on-window-without-drawing dynamic-extent.

;;; The `current-frame-transform?', if any, is the frame transform of that is
;;; enclosing the current rendering.  This binding allows draw-block methods to
;;; check if the frame transform they require has been established and if not to
;;; establish it.  That, in turn, enables them to be called recursively from a
;;; parent (that presumbably would establish the transform) and directly (when
;;; it wouldn't be established).
;;; You should also see the doc for block-is-currently-being-dragged-p
;;; since it usually that effects the behavior of the block draw methods.
;;; By convention most block draw methods establish a lexical binding for
;;; suppress-details?  so that the block is drawn differently at a small
;;; scale.

;; TBD: doc these more explicitly, especially transfer-mode

(defvar-of-named-dynamic-extent current-frame-transform? for-image-plane
  (global-binding nil))


(defvar-of-named-dynamic-extent current-text-box-format         for-image-plane
  (process-binding nil))

(defvar-of-named-dynamic-extent current-text-cell-plist         for-image-plane
  (process-binding nil))

;; If we had an extent for drawing a block independent of image-plane,
;; then current-text-box-format would be established there.  That would
;; encourage getting things bound right prior to the call to update-images
;; on the incremental update paths.



;;; The primary clipping rectangle is established in `left-edge-of-draw-area',
;;; `top-edge-of-draw-area', `right-edge-of-draw-area', and
;;; `bottom-edge-of-draw-area'.  These are known as the `draw-area'.
;;; These are part of the basic-on-window context.

;;; Draw areas nest.  The entire window is broken into panes.  The panes have
;;; image-planes.  The image-planes are parititoned into exposed rectangular
;;; regions.  Meanwhile the image-planes have frames, inside of band of the
;;; frame is a workspace area.  The workspace area has blocks and connections
;;; in it.  The blocks have extent (aka extreme-edges).  The blocks have
;;; edges.  The blocks have subblocks (that need not lie within their edges).
;;; The blocks have nested components (cells in tables for example).
;;; Incremental updates to blocks sometimes focus the draw area on components
;;; or even portions of the components (portions of the text for example).

;;; The exposed region of an image plane, which might not be a rectangle, is
;;; drawn one or more times until the union of these draw-areas covers the
;;; entire exposed area of the image-plane.  Of course these are in raster
;;; units, see the section on quick clipping for a similar but not identical set
;;; rectangle in workspace units.

;;; Individual draw methods may rebind these values to tighten the draw
;;; area, both to assure that drawing is limited to the bounds of the
;;; block, or to limit drawing just to the areas being changed.

;;; Two examples taken from text drawing.  In freeform tables this is
;;; used to clip the user's text to the bounds of the table cells.  In
;;; all (?) incremental text updating this is used to limit redrawing,
;;; for example if "Temp of tank 12: 32 degrees" becomes "Temp of tank
;;; 12: 33 degrees" we attempt to draw only the portion "33 degrees"

;;; The mapping from a workspace clipping rectangle into an
;;; image-plane clipping rectangle is very delicate.  First there is a
;;; flaw in the design of icons.  Second is a generic problem in
;;; scalling.

;;; A icon that is recorded as 20 pixels wide is actually 21 pixel's
;;; wide.  The routines that compute the 'extreme edges' of portions
;;; of the subblock connection hierarchy add in this additional
;;; padding.  It would be wrong to circumvent those routines.

;;; At small scales objects may `bleed' outside the right or bottom of the
;;; the draw area.  Part of the reason for this arises from the pen's
;;; behavor of hanging down and to the right.  The primary reason arises
;;; because if a graphic's width scales down to zero then the draw code
;;; may decide to increment the width back up to one to get ink on the
;;; page.  When the graphic is on the right or botttom edge then it
;;; will bleed outside clipping area implied by a simple mapping of the
;;; workspace clipping area into the image plane clipping area.

;;; This is sometimes called `bleeding at low scales', and it is handled
;;; by a `bleeding-hack' parameter to the routines that do this mapping.

;;; The work around is not pretty.  When mapping a workspace clipping
;;; rectangle into the image-plane clipping rectangle a one pixel hack
;;; is added on the right and left when rendering at less then full
;;; scale.  This is the default behavor.

;;; The work around can be adjusted in two ways.  The routines that
;;; do this work around take a flag to adjust it.  In some cases it
;;; is possible to skip it, this is done when rendering text, since
;;; those bitmaps are scalled so as not to bleed.  In some cases it
;;; is possible to bleed to the left or top, for example when enlarge
;;; the right edge of the text box.  In that case the clipping
;;; rectangle is bought right up against the inside edge of the border,
;;; after scaling the border maybe drawn one pixel to the left of that
;;; hence bleeding outside the clipping area.

;;; The flag controlling the `bleeding-hack' may have one of four possible values:
;;; `:no-bleeding'              -- no bleeding
;;; `nil'                       -- bleeding on the right and bottom
;;; `:bleeding-on-all-sides'.'  -- bleeding on left, top, right, and bottom.
;;       This one bleeds at large-scale, too. Used only by text-box borders.
;;; `:connection-bleeding'      -- bleeding on all sides by 2 pixels at reduced scales

;; The precise semantics of the bleeding-hack are defined by the macro
;; with-workspace-to-window-transform.

;;; The work around can cause flickering.  Text drawing, for example, never
;;; bleeds at low scales since the character rectangles don't ever scale down
;;; to zero width.  The routines that do the mapping from workspace clipping to
;;; image-plane clipping therefore all take a flag to supress this bleeding
;;; hack.

(def-concept bleeding)
(def-concept bleeding-hack)


(def-substitution-macro increase-bleeding-to-accomodate-selection-handles-p (image-plane)
  (and (show-selection-handles-p (gensym-window-for-image-plane image-plane))
       (image-plane-selection-non-empty-p image-plane)))


;;; The substitution-macro `bleeding-hack-maximum' returns the bloodiest of the
;;; two hacks.

(def-substitution-macro bleeding-hack-maximum (bleeding-hack-1 bleeding-hack-2)
  (cond ((or (eq bleeding-hack-1 :bleeding-on-all-sides)
	     (eq bleeding-hack-2 :bleeding-on-all-sides))
	 :bleeding-on-all-sides)
	((or (eq bleeding-hack-1 :connection-bleeding)
	     (eq bleeding-hack-2 :connection-bleeding))
	 :connection-bleeding)
	((or (eq bleeding-hack-1 nil)
	     (eq bleeding-hack-2 nil))
	 nil)
	(t
	 :no-bleeding)))

(defun left-or-top-extension-for-bleeding (bleeding-hack full-scale-p reduced-scale-p)
  ;; A brute force way to fixup selection handle drawing
  ;; FIXME: This is racey. We should be testing this at enqueue time, not here.
  (cond ((increase-bleeding-to-accomodate-selection-handles-p current-image-plane)
	 (1+f selection-handle-radius))
	(t
	 (case bleeding-hack
	   ((:no-bleeding) 0)
	   ((nil) 0)
	   ((:bleeding-on-all-sides) (if full-scale-p
					 0
					 (bleeding-overflow)))
	   ((:connection-bleeding) (if reduced-scale-p
				       2
				       0))
	   (t
	    #+development (cerror "Continue" "Invalid value for bleeding-hack was ~s" bleeding-hack)
	    0)))))

(defun right-or-bottom-extension-for-bleeding (bleeding-hack full-scale-p reduced-scale-p)
  ;; FIXME
  (cond ((increase-bleeding-to-accomodate-selection-handles-p current-image-plane)
	 (1+f selection-handle-radius))	; 1+ needed for text-boxes, apparently.
	(t
	 (case bleeding-hack
	   (:no-bleeding 0)
	   ((nil) (if reduced-scale-p
		      (bleeding-overflow)
		      0))
	   ((:bleeding-on-all-sides) (if full-scale-p
					 0
					 (bleeding-overflow)))
	   ((:connection-bleeding) (if reduced-scale-p
				       2
				       0))
	   (t
	    #+development (cerror "Continue" "Invalid value for bleeding-hack was ~s" bleeding-hack)
	    0)))))

;;; Loose-{left, top, right, bottom}-edge-of-visible-workspace-area is bound to
;;; the analagous slots of the image-plane.  This rectangle includes the
;;; bounding rectangle of the exposed region of the image-plane as a proper
;;; subset.  See the section `quick-clipping'.

(defvar-of-named-dynamic-extent loose-left-edge-of-visible-workspace-area
    for-image-plane)
(defvar-of-named-dynamic-extent loose-top-edge-of-visible-workspace-area
    for-image-plane)
(defvar-of-named-dynamic-extent loose-right-edge-of-visible-workspace-area
    for-image-plane)
(defvar-of-named-dynamic-extent loose-bottom-edge-of-visible-workspace-area
    for-image-plane)



;;; When elements are removed from the screen they are drawn with erase-instead?
;;; bound to T.  When revising the color of existing elements they are drawn
;;; with changing-colors-of-graphic-elements?  bound to T.  Of course these
;;; shouldn't both be T simultanously.

(defvar-of-named-dynamic-extent erase-instead? for-image-plane
  (process-binding nil)
  (global-binding nil))

(defvar-of-named-dynamic-extent changing-colors-of-graphic-elements?
    for-image-plane
  (process-binding nil))




;;; Opaque blocks and an XOR transfer mode interact to add some complexity.
;;; When blocks are rendered using an XOR transfer mode, a few blocks,
;;; known as opaque blocks, are drawn as if by painting them on the screen.
;;; Graphs and charts are the only two examples at this writing.  These
;;; opaque blocks are drawn on top of all other workspace subblocks, i.e.
;;; last.



(def-system-variable current-default-line-color panes 'black)

;; This is somewhat dated and obsolete, having been replaced by
;; foreground/background-color-value, and hard-wired uses of BLACK in
;; various places.  (MHD 11/2/90)

;; Or better yet by uses of FOREGROUND -- ben 4/08/93



;;; `With-clipping-to-draw-area?' takes an initial form consisting of two lists,
;;; along with a body.  The first list is four variables to bind around the
;;; body.  The second list is four forms that are evaluated to a rectangle.
;;; This rectangle is then clipped to the current draw area and bound to the
;;; variables.  If the area is non-empty the body is executed.  This must be
;;; executed with on-window-without-drawing.

(defmacro with-clipping-to-draw-area? (((clipped-left-edge-in-window
					  clipped-top
					  clipped-right
					  clipped-bottom)
					(left-edge-in-window top right bottom))
				       &body body)
  (unless (and (symbolp clipped-left-edge-in-window)
	       (symbolp clipped-top)
	       (symbolp clipped-right)
	       (symbolp clipped-bottom))
    (warn "With-clipping-to-draw-area? must take symbols."))
  `(let ((,clipped-left-edge-in-window
	    (left-edge-within-draw-area ,left-edge-in-window))
	 (,clipped-right
	    (right-edge-within-draw-area ,right)))
     (when (<r ,clipped-left-edge-in-window ,clipped-right)
       (let ((,clipped-top (top-edge-within-draw-area ,top))
	     (,clipped-bottom (bottom-edge-within-draw-area ,bottom)))
	 (when (<r ,clipped-top ,clipped-bottom)
	   ,@body)))))




;;; `On-image-plane' is shorthand for establishing three contours.  i.e.
;;; on-window-without-drawing, on-window-with-drawing, and for-image-plane.

;;; On-image-plane assumes that both the draw area and the drawing-transform
;;; have been established already.

;;; See drawing-transform, draw-area, on-window-without-drawing,
;;; on-window-with-drawing and for-image-plane for additional informations.

;;; In addition is sets up the variables around
;;; top-plane-if-draw-area-is-subject-to-occlusion? that enable projection to
;;; skip or quickly clip individual elements in some cases.

(defmacro on-image-plane ((image-plane) &body body)
  (avoiding-variable-capture (image-plane)
    `(on-window-without-drawing ((gensym-window-for-image-plane ,image-plane))
       (on-window-with-drawing (current-window)
	 (for-image-plane (,image-plane)
	   ,@body)))))



;;; `On-image-plane-without-drawing' creates a dynamic extent within which you
;;; can compute color values, scaling, and clipping etc.  but where it is not
;;; legal to actually engage in drawing.  This is useful for doing mouse
;;; tracking, but that's only one example of using a drawing routine in variant
;;; modes.  This macro is nothing more than a short hand way to establish first
;;; an `on-window-without-drawing' extent and then a
;;; `for-image-plane-without-drawing' extent for that.

(defmacro on-image-plane-without-drawing ((image-plane-with-image) &body body)
  (avoiding-variable-capture (image-plane-with-image)
    `(on-window-without-drawing
	 ((gensym-window-for-image-plane ,image-plane-with-image))
       (with-image-plane-transform (,image-plane-with-image)
	 (for-image-plane-without-drawing (,image-plane-with-image)
	   ,@body)))))

;; Shouldn't this be on-image-plane-contents-without-drawing


(def-substitution-macro compute-workspace-background-color-value (image-plane)
  (let ((color-or-metacolor
	  (or (if (workspace-on-image-plane? image-plane)	; necessary?
		  (workspace-background-color?
		    (workspace-on-image-plane? image-plane)))
	      'white)))
    (case color-or-metacolor
      ((transparent background)			; background is obsolete!
       (color-value-for-white))
      ((foreground workspace-foreground)	; pick one!!!
       (compute-workspace-foreground-color-value image-plane))
      (t
       (map-to-color-value-macro color-or-metacolor)))))


(def-substitution-macro compute-workspace-foreground-color (image-plane)
  (or (if (workspace-on-image-plane? image-plane)	; necessary?
	  (workspace-foreground-color?
	    (workspace-on-image-plane? image-plane)))
      'black))

(def-substitution-macro compute-workspace-foreground-color-value (image-plane)
  (let ((color-or-metacolor (compute-workspace-foreground-color image-plane)))
    (case color-or-metacolor
      ((transparent background)			; background is obsolete!
       (let ((background-color-or-metacolor
	       (or (if (workspace-on-image-plane? image-plane)	; necessary?
		       (workspace-background-color?
			 (workspace-on-image-plane? image-plane)))
		   'white)))
	 (case background-color-or-metacolor
	   ((foreground workspace-foreground)	; circular metacolor
	    (color-value-for-black))
	   ((transparent background)
	    (color-value-for-white))
	   (t
	    (map-to-color-value-macro background-color-or-metacolor)))))
      ((foreground workspace-foreground)
       (color-value-for-black))
      (t
       (map-to-color-value-macro color-or-metacolor)))))

;; These might have been put in the same section as
;; map-color-or-metacolor-to-color-value, but they reference slots in
;; image-plane, which comes later.

;; The metacolors workspace-foreground and background are obsolete!

;; The idea of the above two macros is that the metacolor buck stops with
;; the workspace foreground/background colors.  And if the background color is
;; defined in terms of the foreground color, the foreground color can't turn
;; around and be defined in terms of the background color.  So,
;;
;;  (1) If the foreground color is FOREGROUND, your foreground color is BLACK
;;
;;  (2) If the background color is TRANSPARENT, your background color is WHITE
;;
;;  (3) if the background color is FOREGROUND, and the foreground color is
;;      FOREGROUND, your background color is BLACK
;;
;;  (4) if the background color is FOREGROUND, and the foreground color is
;;      TRANSPARENT, your background color is WHITE (circular case)
;;
;;  (5) if the foreground color is TRANSPARENT, and the background color is
;;      transparent, your foreground color is WHITE
;;
;;  (6) if the foreground color is TRANSPARENT, and the background color is
;;      FOREGROUND, your foreground color is BLACK (circular case)
;;
;; (MHD 7/6/92)

;; Really, the original goal was to never allow metacolors in the workspace
;; color regions, but it's too late for that, since actions have been allowing
;; them for a while (although the menus don't put them in).  You could maybe go
;; back to that, but you'd have to check workspaces upon loading in, and
;; introduce new errors at runtime.  This probably shouldn't be documented for a
;; while.  (MHD 7/6/92)





;;; The macro `for-image-plane-internal' includes the code common
;;; to for-image-plane and for-image-plane-without-drawing, namely, everything
;;; but the background color value.

(defmacro for-image-plane-internal ((image-plane) &body body)
  (avoiding-variable-capture (image-plane)
    `(with-named-dynamic-extent for-image-plane
	 ((current-pane (pane-for-image-plane ,image-plane))
	  (current-image-plane ,image-plane)
	  (loose-left-edge-of-visible-workspace-area
	    (loose-left-edge-of-visible-workspace-area ,image-plane))
	  (loose-top-edge-of-visible-workspace-area
	    (loose-top-edge-of-visible-workspace-area	,image-plane))
	  (loose-right-edge-of-visible-workspace-area
	    (loose-right-edge-of-visible-workspace-area ,image-plane))
	  (loose-bottom-edge-of-visible-workspace-area
	    (loose-bottom-edge-of-visible-workspace-area ,image-plane))
	  (current-foreground-color-value				     
	    (compute-workspace-foreground-color-value ,image-plane)))
       ,@body)))



;;; The macro `for-image-plane-without-drawing' establishes a for-image-plane
;;; context, while binding but not synchronizing the background-color value.

(defmacro for-image-plane-without-drawing ((image-plane) &body body)
  (avoiding-variable-capture (image-plane)
    `(for-image-plane-internal (,image-plane)
       (let ((current-background-color-value
	       (compute-workspace-background-color-value ,image-plane)))
	 ,@body))))

;; with-background-color-value can do "drawing" in an attempt to
;; synchronize color values.  So we can't use that here.



;;; `For-image-plane' establishes the for-image-plane dynamic extent,
;;; allowing drawing.  The background color value is synchronized.

(defmacro for-image-plane ((image-plane) &body body)
  (avoiding-variable-capture (image-plane)
    `(for-image-plane-internal (,image-plane)
       (with-native-image-plane (,image-plane)
	 (with-background-color-value 
	     (compute-workspace-background-color-value ,image-plane)
	   ,@body)))))

;; As of now, for-image-plane is used only in on-image-plane and
;; invalidate-region-of-image-plane-when-on-window in module PANES.




(def-substitution-macro scale-too-small-for-details-p (x-scale y-scale)
  x-scale y-scale
  nil)

;; Code, and document above!

;; Right now, this is used for text boxes, tables, and graphs, but it should
;; also be used for other classes of blocks!





;;; `With-rectangle-scaling' takes two rectangles in workspace coordinates.
;;; I extablishs a dynamic extent for it's body where in coordinates in the
;;; first rectangle are mapped into the second rectangle.

(defmacro with-rectangle-scaling ((left-edge-in-workspace-of-source
				    top-edge-in-workspace-of-source
				    right-edge-in-workspace-of-source
				    bottom-edge-in-workspace-of-source

				    left-edge-in-workspace-of-destination
				    top-edge-in-workspace-of-destination
				    right-edge-in-workspace-of-destination
				    bottom-edge-in-workspace-of-destination)
				  &body body)
  (avoiding-variable-capture (left-edge-in-workspace-of-source
			       top-edge-in-workspace-of-source
			       right-edge-in-workspace-of-source
			       bottom-edge-in-workspace-of-source
			       
			       left-edge-in-workspace-of-destination
			       top-edge-in-workspace-of-destination
			       right-edge-in-workspace-of-destination
			       bottom-edge-in-workspace-of-destination)
    `(with-shifted-origin (,left-edge-in-workspace-of-source
			     ,top-edge-in-workspace-of-source
			     (x-in-window ,left-edge-in-workspace-of-destination)
			     (y-in-window ,top-edge-in-workspace-of-destination))
       (let* ((current-image-x-scale
		(let ((dx-source (minf (- ,right-edge-in-workspace-of-source ; Generic subtract!
					  ,left-edge-in-workspace-of-source)
				       most-positive-workspace-coordinate))
		      (dx-destination
			(minf (- ,right-edge-in-workspace-of-destination
				 ,left-edge-in-workspace-of-destination)
			      most-positive-workspace-coordinate)))
		  (magnify
		    current-image-x-scale
		    (roundw
		      (*w (convert-to-magnification-at-compile-time 1)
			  dx-destination)
		      dx-source))))
	      (current-image-y-scale
		(let ((dy-source (minf (- ,bottom-edge-in-workspace-of-source
					  ,top-edge-in-workspace-of-source)
				       most-positive-workspace-coordinate))
		      (dy-destination
			(minf (- ,bottom-edge-in-workspace-of-destination
				 ,top-edge-in-workspace-of-destination)
			      most-positive-workspace-coordinate)))
		  (magnify
		    current-image-y-scale
		    (roundw
		      (*w (convert-to-magnification-at-compile-time 1)
			  dy-destination)
		      dy-source)))))
	 ,@body))))




;;; The macro `with-workspace-to-window-transform' binds a local macro called
;;; "transform" which transforms a left,top,right and bottom from workspace to
;;; window coordinates, clipping the result to the visible inside portion of
;;; the current image-plane.  This routine is the only place where the
;;; semantics of `bleeding-hack' are defined. Requires current-image-plane.

(defmacro with-workspace-to-window-transform ((bleeding-hack) &body body)
  `(let* ((image-plane current-image-plane)
	  ;; No matter what, don't extend outside of the enclosing pane's
	  ;; extent, or the workspace extent.
	  (left-edge-of-workspace-area-within-pane
	    (left-edge-of-workspace-area-within-pane image-plane))
	  (top-edge-of-workspace-area-within-pane
	    (top-edge-of-workspace-area-within-pane image-plane))
	  (right-edge-of-workspace-area-within-pane
	    (right-edge-of-workspace-area-within-pane image-plane))
	  (bottom-edge-of-workspace-area-within-pane
	    (bottom-edge-of-workspace-area-within-pane image-plane))
	  
	  ;; Scale workspace clipping rectangle into image-plane/window clipping
	  ;; area.
	  (reduced-scale-p
	    (or (<f (image-x-scale image-plane) (normalized-scale))
		(<f (image-y-scale image-plane) (normalized-scale))))
	  (full-scale-p
	    (and (=f (image-x-scale image-plane) (normalized-scale))
		 (=f (image-y-scale image-plane) (normalized-scale))))
	  (left-or-top-extension-for-bleeding
	    (left-or-top-extension-for-bleeding bleeding-hack full-scale-p reduced-scale-p))
	  (right-or-bottom-extension-for-bleeding
	    (right-or-bottom-extension-for-bleeding bleeding-hack full-scale-p reduced-scale-p)))

     (with-drawing-trace (bleeding)
       (format t "Bleeding: ~s, left-top ~s right-bottom ~s~%"
	       ,bleeding-hack
	       left-or-top-extension-for-bleeding
	       right-or-bottom-extension-for-bleeding))

     ;; Note A.
     (macrolet ((transform (left top right bottom)
		  `(let ((left* (-r (x-in-window ,left)
				    left-or-top-extension-for-bleeding))
			 (top* (-r (y-in-window ,top)
				   left-or-top-extension-for-bleeding))
			 (width* (+r (delta-x-in-window (-r ,right ,left)
							(image-x-scale image-plane))
				     left-or-top-extension-for-bleeding
				     right-or-bottom-extension-for-bleeding))
			 (height* (+r (delta-y-in-window (-r ,bottom ,top)
							 (image-y-scale image-plane))
				      left-or-top-extension-for-bleeding
				      right-or-bottom-extension-for-bleeding)))

		     (values
		       (maxr left* left-edge-of-workspace-area-within-pane)

		       (maxr top* top-edge-of-workspace-area-within-pane)

		       (minr (maxr
			       (+r left* width*)
			       (+r (x-in-window ,right) right-or-bottom-extension-for-bleeding))
			     right-edge-of-workspace-area-within-pane)

		       (minr (maxr
			       (+r top* height*)
			       (+r (y-in-window ,bottom) right-or-bottom-extension-for-bleeding))
			     bottom-edge-of-workspace-area-within-pane)))))
       ,@body)))

;; Note A: One goal of the this transformation is to duplicate the computations
;; in create-icon-rendering: at small scales, the area covered by an icon is
;; computed from the position and the size, where the size is computed with
;; delta-x/y-in-window.  By using exactly the same transformation, we can be
;; sure the inval-region at the start of dragging, and the XOR drawing during
;; dragging, will match up.

;; Unfortunately, other routines in G2 may follow a different convention.



(defun current-workstation ()
  (cond ((boundp 'current-workstation) current-workstation)
	((boundp 'current-window) (workstation-this-is-on current-window))
	((boundp 'current-image-plane) (workstation-of-image-plane current-image-plane))
	(t nil)))


(defun current-window ()
  (cond ((boundp 'current-window) current-window)
	((boundp 'current-workstation-window) current-workstation-window)
	((boundp 'current-image-plane) (gensym-window-for-image-plane current-image-plane))
	(t nil)))
	 


;;;; A Spatial Index for Drawing

(defmacro geometry-elements-hash-macro (block)
  `(sxhash-symbol ,block))

(def-skip-list-or-binary-tree geometry-elements
  :constructor make-geometry-elements-tree
  :reclaimer reclaim-geometry-elements-tree
  :clearer clear-geometry-elements-tree
  :hash-function geometry-elements-hash-macro)

(def-structure (geometry
		 (:reclaimer reclaim-geometry-1)
		 (:constructor create-geometry-1))
  geometry-x-origin
  geometry-y-origin
  geometry-delta-x
  geometry-delta-y
  geometry-width					    ; In cells
  geometry-height
  geometry-grid)

(defun create-geometry (size left top right bottom)
  (let ((geometry (create-geometry-1))
	(ncells (*f size size)))
    (setf (geometry-x-origin geometry) left
	  (geometry-y-origin geometry) top
	  (geometry-width geometry) size
	  (geometry-height geometry) size
	  (geometry-delta-x geometry) (floorf-positive (-f right left) size)
	  (geometry-delta-y geometry) (floorf-positive (-f bottom top) size)
	  (geometry-grid geometry) (allocate-managed-array ncells))
    (loop for index from 0 below ncells do
      (setf (managed-svref (geometry-grid geometry) index)
	    (make-geometry-elements-tree)))
    geometry))

(def-substitution-macro geometry-x-to-cell-number (geometry x)
  (minf (1-f (geometry-width geometry))
	(floorf-positive
	  (maxf 0 (-f x (geometry-x-origin geometry)))
	  (geometry-delta-x geometry))))

(def-substitution-macro geometry-y-to-cell-number (geometry y)
  (minf (1-f (geometry-width geometry))
	(floorf-positive
	  (maxf 0 (-f y (geometry-y-origin geometry)))
	  (geometry-delta-y geometry))))



;;; The macro `do-geometry-cells' runs the body for each cell of the index
;;; which overlaps the given rectangle.  Within the body, the local macro
;;; (CELL) may be used to get the cell contents, or as a setf-able place to
;;; change the cell contents.  Finally, X and Y are bound to the row and column
;;; indices of the cell.

(defmacro do-geometry-cells ((geometry &key left top right bottom)
			     &body body)
  (avoiding-variable-capture (geometry &aux span grid yindex index x0 y0 x1 y1)
    `(loop with ,x0 = (if ,left
			 (geometry-x-to-cell-number ,geometry ,left)
			 0)
	   with ,y0 = (if ,top
			 (geometry-y-to-cell-number ,geometry ,top)
			 0)
	   with ,x1 = (if ,right
			 (geometry-x-to-cell-number ,geometry ,right)
			 (1-f (geometry-width ,geometry)))
	   with ,y1 = (if ,bottom
			 (geometry-y-to-cell-number ,geometry ,bottom)
			 (1-f (geometry-height ,geometry)))
	   with ,span = (geometry-width ,geometry)
	   with ,grid = (geometry-grid ,geometry)
	   for y from ,y0 to ,y1
	   for ,yindex from (*f ,y0 ,span) by ,span
	   doing
       (loop for x from ,x0 to ,x1
	     as ,index = (+f x ,yindex)
	     doing
	 (macrolet ((cell () `(managed-svref ,',grid ,',index)))
	   ,@body)))))

(defun reclaim-geometry (geometry)
  (do-geometry-cells (geometry)
    (clear-geometry-elements-tree (cell))
    (setf (cell) nil))
  (reclaim-managed-array (geometry-grid geometry))
  (reclaim-geometry-1 geometry))


;;; The function `picture-geometry' draws a little picture
;;; of the occupied cells.

#+development
(defun picture-geometry (geometry)
  (let ((empty-cells 0)
	(max-cell 0))
    (do-geometry-cells (geometry)
      (let ((n (length (cell))))
	(if (=f n 0)
	    (incff empty-cells))
	(setq max-cell (maxf n max-cell)))
      (when (=f x 0)
	(format t "~&~3d: " y))
      (princ (if (cell) "*" ".")))
    (format t "~&There are ~d empty cells, and the max cell size is ~d element~:p.~%"
	    empty-cells max-cell)
    geometry))


#+development
(defun check-geometry ()
  (loop for ws being each class-instance of 'kb-workspace
	as geometry? = (workspace-spacial-index? ws)
	doing
    (when geometry?
      (do-geometry-cells (geometry?)
	(loop for thing being each binary-tree-value of (cell) do
	  (cond ((deleted-frame-p thing)
		 (break "Garbage in the index for ~s: ~s" ws thing))
		((neq ws (get-workspace-of-block-or-connection thing))
		 (break "~s is in the wrong index ~s" thing geometry?))))))))



;;; The function `find-in-geometry' scans all the cells of the index for the
;;; given block, and returns T if it was found.

#+development
(defun find-in-geometry (block &optional geometry? verbose?)
  (let ((workspace? (get-workspace-of-block-or-connection block))
	(found? nil))
    (unless geometry?
      (setq geometry? (and workspace?
			   (workspace-spacial-index? workspace?))))
    (when (and geometry? (not (workspace-p block)))
      (do-geometry-cells (geometry?)
	(when (get-geometry-elements block (cell))
	  (setq found? t)
	  (when verbose?
	    (format t "~d ~d ~d/~d ~%" x y (position block (cell)) (length (cell)))))))
    found?))


#+development
(defun check-index-for-block (thing)
  (let* ((workspace? (get-workspace-of-block-or-connection thing))
	 (geometry? (and workspace?
			 (workspace-spacial-index? workspace?))))
    (when (and geometry? (not (workspace-p thing)))
      (multiple-value-bind (left top right bottom)
	  (local-edges-of-block-or-connection thing)
	(let ((x0 (geometry-x-to-cell-number geometry? left))
	      (y0 (geometry-y-to-cell-number geometry? top))
	      (x1 (geometry-x-to-cell-number geometry? right))
	      (y1 (geometry-y-to-cell-number geometry? bottom)))

	  (do-geometry-cells (geometry?)
	    (cond ((and (<= x0 x x1)
			(<= y0 y y1))
		   (unless (get-geometry-elements thing (cell))
		     (break "Missing ~s at ~d ~d from ~s" thing x y (cell))))
		  (t
		   (when (get-geometry-elements thing (cell))
		     (break "Extra ~s at ~d ~d from ~s" thing x y (cell)))))))))))


#+development
(defun geometry-cell-edges (geometry column row)
  (let* ((left (+ (geometry-x-origin geometry)
		  (* (geometry-delta-x geometry) column)))
	 (top (+ (geometry-y-origin geometry)
		 (* (geometry-delta-y geometry) row)))
	 (right (+ left (geometry-delta-x geometry)))
	 (bottom (+ top (geometry-delta-y geometry))))
    (values left top right bottom)))

;; Cells lying on the border actually extend to the workspace borders.




#+development
(defun find-bugs-in-geometry-delete (geometry object)
  (when (find-in-geometry object geometry)
    (cerror "Proceed" "Failed to delete ~s from ~s" object geometry)))


;;; The function `geometry-insert' inserts the given object into the index,
;;; such that any find operation which intersects the given rectangle is
;;; guarenteed include the object in its returned list.

(defun geometry-insert (geometry object left top right bottom)
  (do-geometry-cells (geometry :left left :top top :right right :bottom bottom)
    (setf (get-geometry-elements object (cell)) object))
  geometry)

;; Connections are indexed for each rectangle of their bounding regions, and so
;; are inserted multiple times.  Each insertion may touch some of the same
;; geometry cells, so we need the pushnew here.



;;; The function `geometry-delete' deletes the given object from the index.
;;; The supplied rectangle MUST be identical to the one supplied when the
;;; object was inserted.

(defun geometry-delete (geometry object left top right bottom)
  (let ((found-p nil))

    (do-geometry-cells (geometry :left left :top top :right right :bottom bottom)
      (when (get-geometry-elements object (cell))
	(delete-geometry-elements object (cell))
	(setq found-p t)))

    #+development (find-bugs-in-geometry-delete geometry object)

    found-p))



;;; The function `geometry-flush' deletes the given object from the index,
;;; without needing to know its old edges.  It runs in O(n) since it must
;;; scan all of the grid cells.

(defun geometry-flush (geometry object)
  (do-geometry-cells (geometry)
    (delete-geometry-elements object (cell)))
  geometry)



;;; The function `geometry-find' returns a newly consed slot-value-list of the
;;; objects in the index which potentially overlap the given rectangle.

(defun geometry-find (geometry left top right bottom)
  (let ((answer ())
	(ans-ht (make-geometry-elements-tree)))
    (do-geometry-cells (geometry :left left :top top :right right :bottom bottom)
      (loop for object being each binary-tree-value of (cell) do
	(unless (get-geometry-elements object ans-ht)
	  (setf (get-geometry-elements object ans-ht) t)
	  (slot-value-push object answer))))
    (reclaim-geometry-elements-tree ans-ht)
    answer))

;; It might be a good idea to protect the entire index against deletions by
;; storing a max frame serial number with each cell.
;; NOTE: above function is not used any more. --binghe, Aug2015


;;; The function `geometry-find-in-region' returns a newly consed slot-value
;;; list of the objects in the index which potentially touch the given region.
;;; This list does not contain duplicates.

(defun geometry-find-in-region (geometry region)
  (let ((answer ())
	(ans-ht (make-geometry-elements-tree)))
    (do-region-rectangles ((left top right bottom) region)
      (do-geometry-cells (geometry :left left :top top :right right :bottom bottom)
	(loop for object being each binary-tree-value of (cell) do
	  (unless (get-geometry-elements object ans-ht)
	    (setf (get-geometry-elements object ans-ht) object)
	    (slot-value-push object answer)))))
    (reclaim-geometry-elements-tree ans-ht)
    answer))


;;; The function `geometry-optimize' rebuilds the index with a grid which more
;;; uniformly covers all of the objects.

(defun geometry-optimize (geometry)
  geometry)



;;;; Maintaining the geometry index



;;; The defparameter `permit-spacial-index-p' determines whether spacial
;;; indices are created automatically for any workspace.

(def-system-variable permit-spacial-index-p panes t)


;;; The defparameter `default-size-of-spacial-index' is the default number of
;;; grid cells in each dimension.

(def-system-variable default-size-of-spacial-index panes 10)


;;; The defparameter `minimum-number-of-blocks-for-spacial-index' is the
;;; threshold in the number of blocks on the workspace at which point we
;;; build an index.

(def-system-variable minimum-number-of-blocks-for-spacial-index panes 50)

;; Tests on a sparc10 indicate that the index wins even for as few as 10
;; blocks.  But be conservative here.


;;; The defparameter `minimum-number-of-blocks-to-retain-spacial-index' is the
;;; threshold in the number of blocks below which we reclaim the index if there
;;; is one.

(def-system-variable minimum-number-of-blocks-to-retain-spacial-index panes 25)



(def-substitution-macro subblock-of-graph-p (block-or-connection)
  (and (framep block-or-connection)
       (memq-p-macro (class block-or-connection)
		     '(graph-grid graph-axis-label))))

(def-substitution-macro frame-is-graph-p (frame)
  (eq (class frame) 'graph))




;;; The function `test-spacial-index' is used for testing the index
;;; performance in the build.

(defun test-spacial-index (what)
  (case what
    (geometry-on
     (setq permit-spacial-index-p t
	   minimum-number-of-blocks-for-spacial-index 1
	   minimum-number-of-blocks-to-retain-spacial-index 1)

     (loop for workspace being each class-instance of 'kb-workspace
	   doing
       (when (null (workspace-spacial-index? workspace))
	 (build-spacial-index workspace))))
    
    (geometry-off
     (setq permit-spacial-index-p nil
	   minimum-number-of-blocks-for-spacial-index 100
	   minimum-number-of-blocks-to-retain-spacial-index 50)
     
     (loop for workspace being each class-instance of 'kb-workspace
	   doing
       (when (workspace-spacial-index? workspace)
	 (destroy-spacial-index workspace))))
    (t
     (setq permit-spacial-index-p t
	   minimum-number-of-blocks-for-spacial-index 50
	   minimum-number-of-blocks-to-retain-spacial-index 25)
     (loop for workspace being each class-instance of 'kb-workspace
	   doing
       (when (workspace-needs-spacial-index-p workspace)
	 (build-spacial-index workspace)))))

  (format t "Permit: ~s, min: ~s, retain: ~s~%"
	  permit-spacial-index-p
	  minimum-number-of-blocks-for-spacial-index
	  minimum-number-of-blocks-to-retain-spacial-index)

  (loop for workspace being each class-instance of 'kb-workspace
	as name = (or (name-or-names-for-frame workspace)
		      workspace)
	doing
    (when (workspace-spacial-index? workspace)
      (format t "Has index: ~s~%" name))))






;;; The slot-value-reclaimer `workspace-spacial-index?' is here to
;;; pick up the geometry macros.

(def-slot-value-reclaimer workspace-spacial-index? (geometry? workspace)
  (when geometry?
    (reclaim-geometry geometry?)
    (setf (workspace-spacial-index? workspace) nil)))



(defun invalidate-layer-positions (workspace)
  (setf (workspace-layer-positions-are-valid-p workspace) nil))

(defun validate-layer-positions (workspace)
  (setf (workspace-layer-positions-are-valid-p workspace) t))


(defun ensure-layer-positions (workspace)
  (or (workspace-layer-positions-are-valid-p workspace)
      (progn (recompute-layer-positions workspace)
	     (setf (workspace-layer-positions-are-valid-p workspace) t))))



;;; The function `region-covers-workspace?' returns T if the given region
;;; covers the entire workspace interior.

(defun region-covers-workspace? (workspace region)
  (multiple-value-bind (left top right bottom)
      (region-bounding-rectangle region)
    (and (exactly-one-rectangle-in-region-p region)
	 (rectangle-covers-entire-workspace? workspace left top right bottom))))



(defun rectangle-covers-entire-workspace? (workspace left top right bottom)
  (rectangle-inside-rectangle-p
    (left-edge-of-block workspace)
    (top-edge-of-block workspace)
    (right-edge-of-block workspace)
    (bottom-edge-of-block workspace)

    left top right bottom))


;;; The function `region-is-simple-and-covers-visible-portion-of-image-plane-p'
;;; returns true if the region, in window coordinates, consists of a single
;;; rectangle, and that rectangle completely covers the image-plane.

(defun region-is-simple-and-covers-visible-portion-of-image-plane-p (image-plane region)
  ;; I don't think the region can ever be NIL here, but I'm being paranoid for
  ;; 6.2, 24 minutes before the code freeze.
  (when (visible-region-of-image-plane image-plane)
    (multiple-value-bind (region-left region-top region-right region-bottom)
	(region-bounding-rectangle region)
      (multiple-value-bind (visible-left visible-top visible-right visible-bottom)
	  (region-bounding-rectangle (visible-region-of-image-plane image-plane))
	(and (exactly-one-rectangle-in-region-p region)
	     (rectangle-inside-rectangle-p
	       visible-left visible-top visible-right visible-bottom
	       region-left region-top region-right region-bottom))))))



;;; The function `workspace-needs-spacial-index-p' returns true if the given
;;; workspace does not have a spacial index but ought to have one.  Mostly, the
;;; workspace must be a KB workspace (to disallow editor workspaces with
;;; scrolling, which break the index), it must be showing, and it must have a
;;; bunch of blocks.

(defun workspace-needs-spacial-index-p (workspace)
  (and permit-spacial-index-p
       (null (workspace-spacial-index? workspace))
       (kb-workspace-p workspace)
       (workspace-showing-p workspace t)
       (>=f (number-of-blocks-on-workspace workspace)
	    minimum-number-of-blocks-for-spacial-index)))



;;; The function `workspace-needs-to-lose-spacial-index-p' returns true if the
;;; workspace has a spacial index but should no longer.

(defun workspace-needs-to-lose-spacial-index-p (workspace)
  (and (workspace-spacial-index? workspace)
       (or (not (kb-workspace-p workspace))
	   (not (workspace-showing-p workspace t))
	   (<f (number-of-blocks-on-workspace workspace)
	       minimum-number-of-blocks-to-retain-spacial-index))))





;;; The function `build-spacial-index-if-needed' builds an index for the
;;; workspace if one is deemed necessary.  The index, if any, if returned.

(defun build-spacial-index-if-needed (workspace)
  (when (workspace-needs-spacial-index-p workspace)
    (build-spacial-index workspace))
  (workspace-spacial-index? workspace))



;;; The function `update-spacial-index' adds or removes the block or connection
;;; THING from the index, creating or destroying the index as needed.

(defun update-spacial-index (workspace thing what)
  (let ((geometry? nil))
    (case what
      (add
       (when (setq geometry? (build-spacial-index-if-needed workspace))
	 (add-thing-to-spacial-index geometry? thing t)))

      (remove
       (cond ((workspace-needs-to-lose-spacial-index-p workspace)
	      (destroy-spacial-index workspace))
	     ((setq geometry? (workspace-spacial-index? workspace))
	      (remove-thing-from-spacial-index workspace geometry? thing)))))
    geometry?))




;;; The function `notice-workspace-exposure' is called whenever a workspace
;;; transitions between showing somewhere and not showing anywhere.  We
;;; unconditionally reclaim the index when the workspace is not showing, and
;;; rebuild it if needed when we are showing.

(defun notice-workspace-exposure (workspace showing?)
  (cond ((not showing?)
	 (destroy-spacial-index workspace))
	(showing?
	 (build-spacial-index-if-needed workspace))))
	   
;; Wait until we really need it?



;; There are more functions related to the index in CONNECT3A.




;;;; Drawing Schedules and drawing tasks



;;; A `drawing-schedule' is a queue of drawing tasks which need to be taken to
;;; get a pane or image-plane up-to-date.  These actions maybe deferred in G2
;;; to allow other micro tasks to run.

;;; Drawing schedules are stored in the {pane,image-plane}-drawing-schedule
;;; slots of panes and image-planes respectively.  The drawing schedule
;;; is a graphics list.  The individual drawing tasks are instances of
;;; the structure drawing-task.

;;; It is a small problem that drawing schedules appear on both
;;; image-planes and panes.  For example the dynamic extent required
;;; to draw in a pane is very different than that of an image-plane.
;;; That usually means that drawing tasks appropriate for an image-plane
;;; are not approprate for a pane.

;;; These are the currently implemented drawing tasks:
;;;  refresh-region-of-image-plane
;;;  refresh-region-of-block
;;;  refresh-color-of-block
;;;  refresh-region-of-pane

;;; All coordinates in drawing tasks are given in window coordinates.
;;; Transform-image-plane must fixup existing drawing tasks.  The drawing tasks
;;; often attempt to draw things that are entirely obscured in the current
;;; image-plane.  Individual drawing tasks must clip approprately.

;;; To enable an efficent implementation of the predicate: "Is there any drawing
;;; pending on this window?" we maintain a counter `count-of-enqueued-drawing'
;;; in every gensym-window.  This counter is incremented when new drawing tasks
;;; are consed and decremented when they are reclaimed.

(def-concept drawing-schedule)


;;; The variable `working-on-drawing-schedule' is bound to T during the dynamic
;;; extent of work-on-drawing-schedule. Certain mutations of the schedule are
;;; not allowed while we are working on it, namely, you are not allowed to
;;; delete the head of the queue.

(defvar working-on-drawing-schedule nil)


;;; The structure `drawing-task' is an entry in a drawing schedule.  It is
;;; allowed one state-variable, state, and one argument, arg, each of which may
;;; be any slot-value.  State is initially NIL, and is set back to NIL when the
;;; task is finished.

(def-structure (drawing-task
		 (:constructor make-drawing-task-1
			       (drawing-task-operation
				 drawing-task-state
				 drawing-task-region?
				 drawing-task-block?
				 drawing-task-arg))
		 (:reclaimer reclaim-drawing-task-1)
		 #+development
		 (:print-function print-drawing-task))
  drawing-task-operation
  drawing-task-state			; Task progress.  A slot-value.
  drawing-task-region?			; Optional region, in window coor.
  drawing-task-block?			; Optional block. (or connection?)
  drawing-task-arg			; Optional arg.  A slot-value.
  drawing-task-data			; Random data.  NOT reclaimed or managed.
  drawing-task-buffered?)		; T if being double-buffered.



;;; The macro `make-drawing-task' creates a drawing task with
;;; an initial state of NIL.

(defmacro make-drawing-task (operation region? &optional block? arg?)
  `(make-drawing-task-1 ,operation nil  ,region? ,block? ,arg?))

(defun reclaim-drawing-task (drawing-task)
  (let ((state? (drawing-task-state drawing-task))
	(region? (drawing-task-region? drawing-task))
	(arg? (drawing-task-arg drawing-task)))
    (when state?
      (reclaim-slot-value state?)
      (setf (drawing-task-state drawing-task) nil))
    (when region?
      (reclaim-region region?)
      (setf (drawing-task-region? drawing-task) nil))
    (when arg?
      (reclaim-slot-value arg?)
      (setf (drawing-task-arg drawing-task) nil))
      
    (reclaim-drawing-task-1 drawing-task)))

;; We assume that state is a slot-value, and arg is a slot-value-list.


;;; The substitution-macro `update-drawing-task-state' sets a new state for a
;;; drawing task.  If the new state is EQ to the old, then we do nothing.  This
;;; means that mutable states may be mutated at will and returned by the task.

(def-substitution-macro update-drawing-task-state (drawing-task new-state)
  (let ((old-state (drawing-task-state drawing-task)))
    (unless (eq old-state new-state)
      (when old-state
	(reclaim-slot-value old-state))
      (setf (drawing-task-state drawing-task) new-state))))


;;; The macro `drawing-task-in-progress?' returns T is thr drawing task has
;;; begun but is not finished.  Indicated by a non-NIL state.

(def-substitution-macro drawing-task-in-progress? (drawing-task)
  (not (null (drawing-task-state drawing-task))))


#+development
(defmacro name-of-drawing-task-p (name)
  `(get ,name 'drawing-task))



#+development
(defun find-bugs-in-drawing-schedule (schedule)
  (loop for drawing-task being each queue-element of schedule
	doing (assert (drawing-task-p drawing-task))))



;;; The macro `def-drawing-task' defines a potentialy resumable drawing task.
;;; The lambda-list must look like (task state thing . args), where task is the
;;; drawing-task structure, where thing is the structure on whose behalf we are
;;; running this task (an image-plane or a pane) and state is the state
;;; variable.  The state is initially NIL.  If the drawing task does not finish
;;; and wishes to be called again, then it should set the state to something
;;; non-NIL, and which is a valud slot-value.  The new value of state must be
;;; returned, which happens automatically if the body exits normally.

;;; The body can reference the local macros `allow-other-processing' and
;;; `exit-drawing-task'.  It should contain a block named "quantum".

;;; The task runs in the dynamic extent established by work-on-drawing-schedule.

(defmacro def-drawing-task (name (task state region &rest arguments) &body body)
  `(progn
     #+development (setf (name-of-drawing-task-p ',name) t)
     (defun-allowing-unwind ,name (,task ,state ,region ,@arguments)
       ,task
       (macrolet ((allow-other-processing (&optional force-p)
		    (if force-p
			`(return-from quantum)
			`(when (drawing-time-slice-expired-p)
			   (return-from quantum))))
		  (exit-drawing-task ()
		    `(progn (setq ,',state nil)
			    (return-from quantum))))
	 (let ((,state ,state))		; HQ-4315345
	   ,@body
	   ,state)))))

;; This macro is really just sugar for now -- all drawing tasks must
;; be explicitly threaded into: in the case form in
;; work-on-drawing-schedule, and reclaim-drawing-task.  A wrapper that
;; calls enqueue-drawing-task must also be implemented.




#+development
(defun print-drawing-task (drawing-task stream depth)
  (declare (ignore depth))
  (printing-random-object (drawing-task stream)
    (format stream "DRAWING-TASK ~a ~s "
	    (name-of-drawing-task drawing-task)
	    (drawing-task-state drawing-task))
    (when (drawing-task-region? drawing-task)
      (print-region-bounding-rectangle (drawing-task-region? drawing-task) stream))
    (when (drawing-task-block? drawing-task)
      (format stream " ~s" (drawing-task-block? drawing-task)))
    (when (drawing-task-arg drawing-task)
      (format stream " ~s" (drawing-task-arg drawing-task)))
    (when (drawing-task-data drawing-task)
      (format stream " ~s" (drawing-task-data drawing-task))))
  drawing-task)



#+development
(defun name-of-drawing-task (drawing-task)
  (case (drawing-task-operation drawing-task)
    (refresh-region-of-pane "P")
    (refresh-region-of-image-plane "I")
    (refresh-region-of-block "B")
    (refresh-color-of-block "C")
    (t (drawing-task-operation drawing-task))))


#+development
(defun print-drawing-schedule (schedule &key verbose)
  (format t "Sched (~a): " (case (type-of-gensym-window current-window)
			     (icp "ICP")
			     (t   "X11")))
  (cond (verbose
	 (loop for task being each queue-element of schedule
	       doing (format t "~s " task)))
	(t
	 (format t "(~d) ~{~a~}"
		 (queue-length schedule)
		 (loop for task being each queue-element of schedule
		       collect (name-of-drawing-task task)))))
  (terpri))


(defmacro enqueue-drawing-task-for-pane (pane operation region? &rest args)
  (avoiding-variable-capture (pane)
    `(add-task-to-drawing-schedule
       ,pane
       (pane-drawing-schedule ,pane)
       (make-drawing-task ,operation ,region? ,@args))))

(defmacro enqueue-drawing-task-for-image-plane (image-plane operation region?
							    &optional block? arg?)
  ;; TODO: record native-image-plane offsets in the task object.
  (avoiding-variable-capture (image-plane)
    `(unless (client-drawn-image-plane-p ,image-plane)
       (add-task-to-drawing-schedule
	 ,image-plane
	 (image-plane-drawing-schedule ,image-plane)
	 (make-drawing-task ,operation ,region? ,block? ,arg?)))))

;; Since the operation is nearly always a constant here, we could do some
;; optimizations, perhaps.




;;; The substitution-macro `empty-drawing-task?' returns T if the drawing-task
;;; covers no area on the screen.  For now, this is true if the task has a 
;;; region and the region is empty.

(def-substitution-macro empty-drawing-task? (drawing-task)
  (let ((region? (drawing-task-region? drawing-task)))
    (and region?
	 (empty-region-p region?))))



;;; The defparameter `maximum-region-complexity' is the maximum number of
;;; strips allowed in a region before we simplify the region to its bounding
;;; rectangle.

(def-kb-specific-variable maximum-region-complexity PANES 1000)

;;; The function `g2-set-maximum-region-complexity' can be used by KB developers
;;; to give G2 a hint about upcoming KB updates which cause drawing. If the
;;; drawing is "dense", meaning that the bounding rectangle of all the graphical
;;; changes on a workspace includes few or no Non-changing items, then the
;;; maximum-region-complexity can be set to a low value (as low as 1, but 10 is
;;; probably sufficient) without causing extraneous flicker. Supply 0 to restore
;;; the default value, which currently is 1000.

;; For HQ-5173059 "TW (multiwindow) and TWNG causing G2 procedure
;; timeouts". This has been patched into G2 8.0r1h. -fmw, 3/20/06

(defun-for-system-procedure g2-set-maximum-region-complexity (new-value)
  (prog1 maximum-region-complexity
    (setq maximum-region-complexity (if (or (not (fixnump new-value))
					    (<f new-value 1))
					1000
					(minf 1000 new-value)))))


(defun union-region-and-simplify (region-1 region-2)
  (let ((composite-region (union-region region-1 region-2)))

    ;; Limit the region complexity.
    (when (>=f (region-complexity composite-region)
	       maximum-region-complexity)
      (setq composite-region (simplify-region composite-region)))
    composite-region))

;; This has turned out to be a very bad idea -- simplifying a region to its
;; bounding rectangle can cause the region to enclose many more blocks on the
;; workspace than before, leading to some very suprising and annoying (to the
;; user) flickering effects.  A value of 50 for the max complexity may be
;; enough to reduce the flicker in mill.kb, but the whole idea should be
;; improved or thrown away. -fmw, 1/26/95

;; Increased to 1000 for HQ-2162459.  We may want to revisit this when we have
;; double buffering.  Then we could simplify the region without introducing
;; flicker.  -fmw, 5/18/02



;;; The substitution-macro `merge-drawing-task-if-possible' tries to merge the
;;; given drawing task into other-drawing-task, destructively.  If it succeeds,
;;; it returns the new, merged drawing task.  If merging is not possible, it
;;; returns NIL.  In either case, drawing-task is untouched; only
;;; other-drawing-task may be mutated.  This is where we limit the complexity
;;; of regions.

(defun merge-drawing-task-if-possible (drawing-task other-drawing-task)
  (let ((operation (drawing-task-operation drawing-task))
	(region? (drawing-task-region? drawing-task))
	(block?  (drawing-task-block? drawing-task))
	(other-operation (drawing-task-operation other-drawing-task))
	(other-region? (drawing-task-region? other-drawing-task))
	(other-block? (drawing-task-block? other-drawing-task)))

    ;; Two drawing operations of the same type and same mode, with regions, are
    ;; mergable by merging the regions.  All others we don't bother to merge.
    (when (and (eq operation other-operation)
	       (eq block? other-block?)
	       region?
	       other-region?)

      (let ((composite-region (union-region-and-simplify region? other-region?)))
	(reclaim-region other-region?)
	
	(setf (drawing-task-region? other-drawing-task) composite-region)
	other-drawing-task))))




;;; The function `add-task-to-drawing-schedule' adds a drawing task to the
;;; given drawing schedule, which must be associated with the current-window.
;;; The schedule is mutated in-plane.  The task object is owned by this
;;; routine, and may be reclaimed if necessary.  Note that
;;; current-drawing-priority may imply that the caller must work on schedule
;;; immediately.

;;; This is where we merge drawing tasks as follows:
;;;   A region refresh will enlarge the region of any existing refresh
;;; in the queue. However, we will not search past any "non-shift-invariant"
;;; operations, like change-color-of-block, and we will also not merge with
;;; a drawing-task which is in-progress (non-null state).

(defun add-task-to-drawing-schedule (pane-or-image-plane schedule drawing-task)
  (with-drawing-trace (add-task)
    (format t "....Before ~d ~d~%"
	    (count-of-enqueued-drawing current-window)
	    (queue-length schedule)))

  ;; Full refresh of image-plane?
  (when (and (not working-on-drawing-schedule)
	     (eq (drawing-task-operation drawing-task) 'refresh-region-of-image-plane)
	     (image-plane-p pane-or-image-plane)
	     (drawing-task-region? drawing-task)
	     (region-is-simple-and-covers-visible-portion-of-image-plane-p
	       pane-or-image-plane
	       (drawing-task-region? drawing-task)))
    (with-drawing-trace (discard-task)
      (format t "New task is full refresh of ~s. Discarding drawing schedule"
	      pane-or-image-plane))
    (discard-image-plane-drawing-schedule pane-or-image-plane))

  (cond
    ;; Empty task?
    ((empty-drawing-task? drawing-task)
     (with-drawing-trace (queue) (format t " Empty task ~s~%" drawing-task))
     (reclaim-drawing-task drawing-task))

    ;; Empty schedule?
    ((queue-empty-p schedule)
     (with-drawing-trace (queue) (format t " Enqueue: ~s~%" drawing-task))
     (loop
       (let* ((count (count-of-enqueued-drawing current-window))
	      (new-value (1+f count)))
	 (when (=f 0 count)
	   (maybe-schedule-service-workstation (workstation-this-is-on current-window) t))
	 (when (compare-and-swap (count-of-enqueued-drawing current-window) count new-value)
	   (return new-value))))
     (queue-insert schedule drawing-task))

    ;; Otherwise, attempt to merge with an existing task.
    (t
     (block merged
       ;; Maybe we don't want to search in this order (oldest to newest)?
       (loop for other-drawing-task being each queue-element of schedule
	     doing
	 (when (and (not (drawing-task-in-progress? other-drawing-task))
		    (merge-drawing-task-if-possible drawing-task other-drawing-task))
	   (with-drawing-trace (queue) (format t " Merge task into: ~s~%" other-drawing-task))
	   (reclaim-drawing-task drawing-task)
	   (return-from merged)))

       ;; If failed to merge with any of them, enqueue.
       (with-drawing-trace (queue) (format t " Enqueue: ~s~%" drawing-task))
       (loop
	 (let* ((count (count-of-enqueued-drawing current-window))
		(new-value (1+f count)))
	   (when (=f 0 count)
	     (maybe-schedule-service-workstation (workstation-this-is-on current-window) t))
	   (when (compare-and-swap (count-of-enqueued-drawing current-window) count new-value)
	     (return new-value))))
       (queue-insert schedule drawing-task))))

  (with-drawing-trace (add-task)
    (format t "....After ~d ~d~%"
	    (count-of-enqueued-drawing current-window)
	    (queue-length schedule)))

  #+development (find-bugs-in-drawing-schedule schedule)

  schedule)

;; Limit queue lengths here.


;;; The function `discard-image-plane-drawing-schedule' aborts all pending
;;; drawing tasks for the given image-plane.

(defun discard-image-plane-drawing-schedule (image-plane)
  (with-drawing-trace (queue)
    (format t " Discarding entire ~s for ~s~%"
	    (image-plane-drawing-schedule image-plane)
	    image-plane))
  (discard-image-plane-drawing-queue-entry image-plane)
  (reclaim-drawing-schedule (image-plane-drawing-schedule image-plane)))



;;;; Drawing Tasks


;;; The drawing task `refresh-region-of-pane' draws the GENSYM tiling
;;; pattern over the given portion of the pane, subject to occulusion
;;; by image planes.

(def-drawing-task refresh-region-of-pane (task state region pane)
  (let ((pane-background
	  (compute-pane-background-color-value-or-tiling-pattern pane))
	(visible-region (intersect-region region (visible-region-of-pane pane))))
    
    ;; Always runs to completion.
    (do-region-rectangles ((left top right bottom) visible-region)
      (paint-background-of-current-pane pane-background left top right bottom)
      (add-pane-cursors-to-current-window pane left top right bottom))

    (reclaim-region visible-region)))




;;; `set-flag-to-jump-out-of-drawing-image-plane' - see description of
;;; currently-jump-out-of-drawing-image-plane-when-empty-rectangle-p in
;;; WINDOWS1.  This system procedure allows us to restore the old behavior
;;; in distribution images.

(defun-for-system-procedure set-flag-to-jump-out-of-drawing-image-plane (flag)
  (setq currently-jump-out-of-drawing-image-plane-when-empty-rectangle-p
	(neq flag evaluation-false-value)))


(defun-substitution-macro begin-offscreen-drawing (task)
  (when (drawing-task-buffered? task)
    (draw-offscreen enable-offscreen-drawing 0 0 0 0)))

(defun-substitution-macro end-offscreen-drawing (task)
  (when (drawing-task-buffered? task)
    (draw-offscreen disable-offscreen-drawing 0 0 0 0)))

(defun-substitution-macro bitblt-offscreen-drawing (task image-plane region)
  (when (drawing-task-buffered? task)
    (let ((visible-region (intersect-region
			    (visible-region-of-image-plane image-plane)
			    region)))
      (bitblt-offscreen-bitmap visible-region)
      (reclaim-region visible-region))))


;;; The function `double-buffering-enabled-p' returns T if double buffering is
;;; enabled for the given image-plane.  Note we still won't get buffering if the
;;; platform is Win9x or if the bitmap cannot be allocated.  We can't test that
;;; here since the test can only be performed on the remote TW.

(defun double-buffering-enabled-p (image-plane)
  (and (not (printing-image-plane-p image-plane))
       (window-supports-offscreen-drawing current-window)
       (paint-mode-p)
       (workspace-on-image-plane? image-plane)
       (not (null (prefer-buffered-drawing (workspace-on-image-plane? image-plane))))))


(defun closed-icp-window-p ()
  (and (icp-window-p current-window)
       (=f (icp-connection-state current-icp-socket) icp-connection-closed)))


;;; The function `refresh-region-of-image-plane' is an instruction in
;;; the drawing queue which refreshes each of the rectangles comprising
;;; the region.

(def-drawing-task refresh-region-of-image-plane (task state region image-plane)
  (with-drawing-trace (time-slice)
    (print-time-slice))
  (with-drawing-trace (icp-buffering)
    (print-icp-buffer-sizes "RROP"))
  (with-drawing-trace (show-regions)
    (outline-region-of-window region))
  (within-named-dynamic-extent for-image-plane
    (with-open-cursors (left-edge-of-draw-area		    ; Note A.
			 top-edge-of-draw-area
			 right-edge-of-draw-area
			 bottom-edge-of-draw-area :zero-time t)
      (multiple-value-bind (left top right bottom)
	  (region-bounding-rectangle region)
	;; Clip to pane. Is this needed? Yes, until we prove that
	;; the Q is updated whenever the pane layout is.
	(with-nested-draw-area-for-image-plane?
	    ((left-edge-within-pane left image-plane)
	     (top-edge-within-pane top image-plane)
	     (right-edge-within-pane right image-plane)
	     (bottom-edge-within-pane bottom image-plane)
	     state
	     image-plane :exterior-in-pane)
	  (let ((workspace? (workspace-on-image-plane? image-plane)))
	    (unwind-protect
		 (block quantum
		   ;; Initialize the list of blocks to draw.  Note whether they came
		   ;; from the geometry index, which if so, implies that the list
		   ;; includes it own subblocks (kludge).  As a further performance
		   ;; bum, don't bother sorting the list into drawing order if we
		   ;; are in XOR mode.
		   (when (null state)
		     (multiple-value-bind (blocks using-geometry-p)
			 (if workspace?
			     (blocks-touching-region-of-image-plane workspace? region (paint-mode-p))
			     nil)
		       (set-remaining-subblocks-of-workspace-to-draw
			 image-plane blocks)
		       (setf (drawing-task-data task) using-geometry-p
			     (drawing-task-buffered? task) (double-buffering-enabled-p image-plane))
		       (setq state 'paper)))
		   ;; Draw paper and frame.
		   (when (or (eq state 'paper)
			     (numberp state))		    ; State of BG drawing.
		     (begin-offscreen-drawing task)
		     (setq state
			   (paint-background-of-image-plane region (if (eq state 'paper) nil state)))
		     (cond ((null state)
			    (setq state 'content))
			   (t
			    (allow-other-processing t))))
		   ;; Draw subblocks, both regular and XORed.
		   (when (eq state 'content)
		     (begin-offscreen-drawing task)
		     (paint-contents-of-image-plane region (drawing-task-data task))
		     (if (or (current-drawing-task-is-finished? image-plane)
			     (closed-icp-window-p))
			 (exit-drawing-task)  ;; Exit task.
			 (allow-other-processing))))
	      (end-offscreen-drawing task)
	      (when (and (drawing-task-buffered? task)
			 (null state)
			 (not (closed-icp-window-p)))
		(with-image-plane-draw-area? (image-plane)
		  (bitblt-offscreen-drawing task image-plane region))))))))))

;; Note A: This needs to be done before and after EACH entry into drawing.
;; since other microtasks assume that the pane cursors are always up-to-date on
;; the screen.  Note: the current draw area is set to the interior of the
;; image-plane at this point.  This is what we need for opening and closing the
;; cursors.



;;; The drawing-task `refresh-region-of-block' redraws the given region from
;;; scratch.  The region must be entirely contained in the current bounds of
;;; the given block, so that we can make use of the overlapping cache to find
;;; which blocks to draw.  Runs atomically, which could be a problem since
;;; filling the overlap cache can be slow.

(def-drawing-task refresh-region-of-block (task state region image-plane block)
  (with-drawing-trace (show-regions) (outline-region-of-window region))
  (within-named-dynamic-extent for-image-plane
    (let ((workspace? (workspace-on-image-plane? image-plane)))
      (when workspace?

	;; Task is valid only if region is still inside the block bounds, in
	;; particular, inside the same block bounds used to compute
	;; overlapping-siblings.
	(let* ((bleeding-hack :bleeding-on-all-sides)
	       (region-is-inside-block?
		(multiple-value-bind (region-left region-top region-right region-bottom)
		    (region-bounding-rectangle region)
		  (multiple-value-bind (block-left block-top block-right block-bottom)
		      (local-edges-of-block block)
		    (with-workspace-to-window-transform (bleeding-hack)
		      (multiple-value-bind (left-in-window top-in-window
							   right-in-window bottom-in-window)
			  (transform block-left block-top block-right block-bottom)
			(rectangle-inside-rectangle-p
			  region-left region-top region-right region-bottom
			  left-in-window top-in-window
			  right-in-window bottom-in-window)))))))

	  (cond ((and region-is-inside-block?
		      ;; This kludge is needed because we arbitrarily grew the
		      ;; bleeding hack to accomodate selection handles. The
		      ;; enlarged region may touch other blocks, even though the
		      ;; original region did not.  That unfortunately breaks the
		      ;; nice RROB optimization. -fmw, 3/19/07
		      (not (increase-bleeding-to-accomodate-selection-handles-p image-plane)))
		 (with-open-cursors (left-edge-of-draw-area
				      top-edge-of-draw-area
				      right-edge-of-draw-area
				      bottom-edge-of-draw-area)
		   ;; Guts are in DRAW only to pickup some macros.
		   (paint-region-of-image-plane-overlapping-block
		     workspace? image-plane block region)))
		(t
		 (with-drawing-trace (kb)
		   (format t " BLK: ~s becomes general inval of ~s~%" block region))

		 ;; Probably should maintain the queue ordering here.
		 (enqueue-drawing-task-for-image-plane
		   image-plane 'refresh-region-of-image-plane (copy-region region)))))))))




;;; The drawing-task `refresh-color-of-block' draws just the given icon regions
;;; of the block (which is always either an entity or a connection-frame).
;;; This lets users efficiently flash the little indicator light on their
;;; 500x500 tank icon.

(def-drawing-task refresh-color-of-block (task state image-plane block changed-regions)
  (within-named-dynamic-extent for-image-plane
    (let ((workspace? (workspace-on-image-plane? image-plane))
	  (bleeding-hack nil))

      (when workspace?

	;; Focus the draw area onto the block bounds.  Otherwise we'd need to
	;; draw the entire transitive closure of overlapping blocks.  As an
	;; optimization, we could avoid this when there are no overlapping
	;; blocks.
	
	(multiple-value-bind (left top right bottom)
	    (local-edges-of-block-or-connection block)

	  (with-workspace-to-window-transform (bleeding-hack)
	    (multiple-value-bind (left-in-window top-in-window
						 right-in-window bottom-in-window)
		(transform left top right bottom)
	      
	      (with-nested-draw-area? (left-in-window top-in-window
						      right-in-window bottom-in-window
						      block :block-bounds)
		(with-drawing-trace (show-regions)
		  (outline-draw-area :color 'yellow))
		
		;; Duplicates code from map-over-image-planes...
		(with-open-cursors (left-edge-of-draw-area
				     top-edge-of-draw-area
				     right-edge-of-draw-area
				     bottom-edge-of-draw-area
				     :xor-overlay t)		    ; Blocks being dragged
		  (draw-selected-regions-of-block block changed-regions)
		  (if (frame-of-class-p block 'connection) ;; need to check framep first?
		      (draw-blocks-overlapping-connection workspace? block)
		      (draw-overlapping-blocks workspace? block 'above nil))

		  (when (and (show-selection-handles-p current-window)
			     (image-plane-selected-p image-plane))
		    (draw-selection-handles-for-current-image-plane
		      left-edge-of-draw-area
		      top-edge-of-draw-area
		      right-edge-of-draw-area
		      bottom-edge-of-draw-area)))))))))))



;;; `Ping-image-plane-drawing' creates an identified drawing task and
;;; sends it's id, via ping-drawing, to the client's drawing server.
;;; That will reply with a ping-drawing-reply which will finish the
;;; activity, and fire the continuation pops activity out of the
;;; window.

(def-drawing-task ping-image-plane-drawing
    (task state image-plane id-of-identified-drawing-activity)
  (within-named-dynamic-extent for-image-plane
    (let ((workspace? (workspace-on-image-plane? image-plane)))
      (when workspace?
	(with-drawing-trace (pop)
	  (format t " Execute IP ping ~S~%" id-of-identified-drawing-activity))
	(cond
	  ((current-window-supports-this-icp-window-protocol-p
	     icp-window-protocol-supports-ping-drawing)
	   (ping-drawing id-of-identified-drawing-activity))
	  (t
	   (handle-ping-drawing-reply-1
	     current-window id-of-identified-drawing-activity)))))))





;;; The function `current-drawing-task-is-finished?' returns T if there is no
;;; remaining work to be done on the given image plane for the topmost element
;;; of the drawing queue for this image plane.

(defun current-drawing-task-is-finished? (image-plane)
  (and (null (remaining-subblocks-of-workspace-to-draw image-plane))
       (null (remaining-xor-drawing-activities image-plane))))



;;; The function `image-plane-drawing-is-completely-finished?' is true if the
;;; image-plane drawing queue is empty.  It does not check for additional tasks
;;; queued at the KB level.

(defun image-plane-drawing-is-completely-finished? (image-plane)
  (queue-empty-p (image-plane-drawing-schedule image-plane)))




  
;;; `Reclaim-drawing-schedule' is installed as the reclaimer for the drawing
;;; schedules in image-planes and panes.  Current-window must be established
;;; prior to reclaiming these, so that the count of enqueued drawing tasks can
;;; be decremented prior to reclaiming the graphic's tree that makes up the
;;; schedule.

;;; Image planes are kept in a special pool that hangs of the pane.  It is
;;; necessary to call reclaim-drawing-schedule when they are "deleted" and
;;; moved into that Q.  That is the primary source of calls to this, but
;;; it is also called in the recursive decent of pane's being deleted and
;;; entire window's being deleted.

(defun-simple reclaim-drawing-schedule (drawing-schedule)
  #-SymScale
  (decff (count-of-enqueued-drawing current-window)
	 (queue-length drawing-schedule))
  (loop for drawing-task being each queue-element of drawing-schedule
	doing
    (reclaim-drawing-task drawing-task)
    #+SymScale
    (atomic-decff (count-of-enqueued-drawing current-window)))
  (clear-queue drawing-schedule)
  drawing-schedule)

;; Does this need an else clause that forces the next Q on each channel?

(defun-simple reclaim-drawing-schedule-and-queue (drawing-schedule)
  (reclaim-drawing-schedule drawing-schedule)
  (reclaim-queue drawing-schedule))



;;;; Sketching to Forshadow Drawing



(defun sketch-region-of-image-plane (image-plane region-invalidated)
  (within-named-dynamic-extent on-window-with-drawing
    (let ((current-pane (pane-for-image-plane image-plane))
	  (current-image-plane image-plane))
      (with-nested-image-plane-draw-area? (image-plane)
	;; Is it necessary to open cursors? Does the sketch need to include them?
	(with-open-cursors (left-edge-of-draw-area
			     top-edge-of-draw-area
			     right-edge-of-draw-area
			     bottom-edge-of-draw-area)

	  (do-region-rectangles ((left top right bottom) region-invalidated)
	    (with-nested-draw-area? (left top right bottom
					  region-invalidated :region-rectangle)
	      (sketch-image-plane))))))))



;;; The function `paint-region-of-pane' draws the pane background tiling
;;; pattern and borders in the given region.  Must be called in an
;;; on-window context.

(defun paint-region-of-pane (pane region)
  (let ((current-pane pane))
    (with-open-cursors (left-edge-of-draw-area		    ; Region better be w/in the draw area.
			 top-edge-of-draw-area
			 right-edge-of-draw-area
			 bottom-edge-of-draw-area
			 :image-plane-cursors nil)	    ; Just pane cursors
      (do-region-rectangles ((left top right bottom) region)
	(paint-pane-background-and-borders pane left top right bottom)))))




;;;; Module Internal Invalidation Primitives



;;; The routine in this section invalidate regions when we are already drawing
;;; in a particular window.  The only reason they must be called when on window
;;; is to enable them to draw a sketch of the drawing they are enqueuing (a
;;; miminum to erase the old drawing).  These routines are use ONLY in the
;;; next section of PANES.

;;; All updates to the drawing Q pass thru two bottle necks:
;;;   invalidate-region-of-image-plane-when-on-window
;;;   invalidate-region-of-pane-when-on-window
;;; These routines place the region into the drawing Q and force a sketch of the
;;; drawing to be emited ASAP, to provide the user with some fore shadowing of
;;; what's to come.  These routines are only used in the following section of
;;; PANES.

;;; One routine is provided for invalidation regions of the window.
;;; invalidate-region-of-window-when-on-window.

;;; In addition a few routines are provide that are just sugar on
;;; the previous two.
;;;  invalidate-rectangle-of-image-plane-when-on-window


(defvar allow-invalidate-on-printing-window-p nil)



;;; The function `invalidate-region-of-image-plane-when-on-window' enqueues a
;;; refresh for the given region (in window coordinates), drawing only the given
;;; image plane.  The region argument is copied: the caller retains ownership.

(defun-void invalidate-region-of-image-plane-when-on-window (image-plane region)
  (within-named-dynamic-extent on-window-with-drawing
    #+development (find-bugs-in-paper)

    (unless (client-drawn-image-plane-p image-plane)

      ;; First, a quick test so that off-screen drawing is fast.
      (when (regions-intersect-p
	      region (visible-region-of-image-plane image-plane))

	(when (or allow-invalidate-on-printing-window-p
		  (not (printing-image-plane-p image-plane)))
	  
	  (with-drawing-trace (kb)
	    (format t "IVI: ~s ~s (paper/doc: ~s ~s)~%" image-plane region
		    current-draw-paper-p current-draw-document-p))

	  ;; Draw the paper ASAP (FIXME: unless we have native paper).
	  (when current-draw-paper-p
	    (for-image-plane (image-plane) ; Sometimes (always?) we are already on-image-plane.
	      (sketch-region-of-image-plane image-plane region)))

	  ;; Enqueue the rest.
	  ;; Need to intersect with the current draw area for enqueueing. -fmw, 12/8/94
	  (when (or current-draw-document-p
		    (and workspace-for-current-draw-document? ; KLudge -fmw, 8/20/04
			 (native-image-plane-p image-plane)
			 (neq workspace-for-current-draw-document?
			      (workspace-on-image-plane? image-plane))))
	    (with-draw-area-as-region (drawing-region)
	      (enqueue-drawing-task-for-image-plane
		image-plane 'refresh-region-of-image-plane (intersect-region region drawing-region))))
	  
	  ;; Drain the queue if drawing is immediate.
	  (force-current-window-drawing-if-appropriate))))))

;; Todo: Discard the drawing queue entirely if the inval covers the entire image-plane.
;;       Force drawing if queue is too long.
;;       Don't draw the paper if it is already invalidated?


#+development
(defun find-bugs-in-paper ()
  (unless (or current-draw-paper-p current-draw-document-p)
    (warn "Both current-draw-paper-p and current-draw-document-p are NIL. That no-ops this function.")))



;;; `Invalidate-rectangle-of-image-plane-when-on-window' is sugar
;;; on invalidate-region-of-image-plane-when-on-window.

(defun-void invalidate-rectangle-of-image-plane-when-on-window
    (image-plane left top right bottom)
  (with-region-from-rectangle-void (region left top right bottom)
    (invalidate-region-of-image-plane-when-on-window image-plane region)))




;;; The function `invalidate-region-of-pane-when-on-window' is identical to
;;; invalidate-region-of-image-plane except that it works on panes.  The region
;;; argument is copied.

(defun invalidate-region-of-pane-when-on-window (pane region)
  (within-named-dynamic-extent on-window-with-drawing
    #+development (find-bugs-in-paper)
    (with-drawing-trace (kb)
      (format t "IVP: ~s ~s~%" pane region))

    (unless (or (empty-region-p region)
		(native-windows-p current-window)) ; MDI TW draws pane bg itself.

      ;; Draw the paper asap.
      (when current-draw-paper-p
	(paint-region-of-pane pane region))

      ;; Enqueue the rest.
      ;; Need to intersect with the current draw area for enqueueing. -fmw, 12/8/94
      (when current-draw-document-p
	(with-draw-area-as-region (drawing-region)
	  (enqueue-drawing-task-for-pane
	    pane 'refresh-region-of-pane (intersect-region region drawing-region))))

      ;; Drain the queue if drawing is immediate.
      (force-current-window-drawing-if-appropriate))))




;;; `Invalidate-region-of-window-when-on-window' is internal to this section of
;;; It spreads the invalidation over the affected image-planes and panes.  This
;;; is used to trigger:

;;;  - full redraws
;;;  - process updates from the enclosing window system.
;;;  - as a fall back in some operations on image-planes.

;;; It presumes that we are on window.

(defun invalidate-region-of-window-when-on-window (region)
  (within-named-dynamic-extent on-window-with-drawing
    (with-deferred-drawing-in-current-window ()
      (loop for pane in (panes-in-window current-window)
	    as stack-of-image-planes = (stack-of-image-planes pane)
	    as first-image-plane = (first stack-of-image-planes)
	    doing
	(when (region-possibly-overlaps-rectangle-p
		region
		(left-edge-of-pane-in-window first-image-plane)
		(top-edge-of-pane-in-window first-image-plane)
		(right-edge-of-pane-in-window first-image-plane)
		(bottom-edge-of-pane-in-window first-image-plane))

	  (invalidate-region-of-pane-when-on-window pane region)

	  (loop for image-plane in stack-of-image-planes doing
	    (when (and (workspace-on-image-plane? image-plane)
		       (region-possibly-overlaps-rectangle-p
			 region
			 (left-edge-of-image-in-window image-plane)
			 (top-edge-of-image-in-window image-plane)
			 (right-edge-of-image-in-window image-plane)
			 (bottom-edge-of-image-in-window image-plane)))
	      (invalidate-region-of-image-plane-when-on-window
		image-plane region))))))))




;;;; External Invalidation Routines




;;; There are five operations provided for invalidating.  These all require
;;; NO dynamic extent, but presume you are not currently drawing to a window.

;;; Four are used to edit the configuraiton of image-planes e.g. raising,
;;; lowering, and moving.  These are:
;;;  Lowering: Invalidate-subsequence-of-image-planes
;;;  Raising:  Raise-image-plane
;;;  Moving:   Refresh-moved-image-plane
;;;  Misc:     invalidate-region-of-image-plane

;;; One routine is provided for invalidating a workspace, this will enqueue
;;; drawing for all the image-planes of that workspace, mapping the region
;;; given into the window.  This is:
;;;            Invalidate-region-of-workspace

;;; One routine is provide for invalidating portions of the entire window.
;;; This routine is:
;;;            Invalidate-region-of-window

;;; In addition to these five routines a number of short hands for common
;;; operations are provided.  These are entirely sugar.
;;;      invalidate-rectangle-of-workspace



;;; The system-variable `count-of-pending-workspace-drawing' is a cached count
;;; of the number of changed-blocks and invalid regions for all workspaces.
;;; It's used to speed the check in check-for-pending-drawing-on-window.

(def-system-variable count-of-pending-workspace-drawing PANES 0)

;; To be precise, it is a cache of the sum over all showing (in the G2classic
;; sense) workspaces WS

;;  (+ (length (changed-blocks-of-workspace WS))
;;     (if (invalid-region-of-workspace? WS) 1 0))

;; The scheduler originally checked this value on every clock tick, hence the
;; need for a cache.  Now, with the new scheduled tasks for service-workstation
;; & friends, it is not needed so much.  In fact, various places in the code
;; recompute the value rather than using this cache.  This ought to be cleaned
;; up someday.  -fmw, 12/2/01


;;; `Invalidate-region-of-image-plane' does just that. The region argument is
;;; copied.

(defun invalidate-region-of-image-plane (image-plane region)
  (update-window (gensym-window-for-pane (pane-for-image-plane image-plane))
		 (left-edge-of-region region)
		 (top-edge-of-region region)
		 (right-edge-of-region region)
		 (bottom-edge-of-region region)
		 'invalidate-region-of-image-plane-when-on-window
		 image-plane
		 region))



;;; `Invalidate-image-plane' is sugar on invalidate-region-of-image-plane.
;;; It used to force a full refresh of an image-plane. Two examples: 
;;; moving an image-plane and the substrate doesn't support scrolling, or
;;; during printing.

(defun invalidate-image-plane (image-plane)
  (let ((left (left-edge-of-image-in-window image-plane))
	(top (top-edge-of-image-in-window image-plane))
	(right (right-edge-of-image-in-window image-plane))
	(bottom(bottom-edge-of-image-in-window image-plane)))
    (with-region-from-rectangle-void (region left top right bottom)
      (invalidate-region-of-image-plane image-plane region))))




;;; The function `invalidate-region-of-workspace' invalidates the workspace
;;; rectangles comprising the given region.  This enqueues a full refresh of
;;; the region on all image planes currently showing the workspace.  The region
;;; must of course be in workspace coordinates.  The region is copied as
;;; needed.

(defun invalidate-region-of-workspace
    (workspace region &optional bleeding-hack frame-transform-block)
  (with-drawing-trace (kb)
    (format t "IVWS~a: ~s ~s~%"
	    (if (eq frame-transform-block workspace) " Fast" "")
	    workspace region))

  (setq frame-transform-block (or frame-transform-block workspace))
  
  (cond ((empty-region-p region))
	((not (workspace-showing-p workspace t))) ; As for merge-change-to-block -fmw, 12/5/01
	((eq frame-transform-block workspace)
	 (invalidate-region-of-workspace-fast workspace region bleeding-hack))
	(t
	 (invalidate-region-of-workspace-slow workspace region frame-transform-block bleeding-hack))))



;;; The function `invalidate-region-of-workspace-slow' must be used when the
;;; frame transform is unusual.

(defun-allowing-unwind invalidate-region-of-workspace-slow
    (workspace region frame-transform-block bleeding-hack)
  (loop with current-draw-paper-p = nil		    ; This suppresses ASAP bg clears.
	for current-image-plane in (image-planes-this-is-on workspace)
	doing
    (with-raw-window-transform-and-draw-area
	((gensym-window-for-image-plane current-image-plane))
      (with-nested-transform-and-draw-area-of-image-plane-contents?
	  (current-image-plane)
	(with-frame-transform-of-block-if-any (frame-transform-block)
	  (let ((region-of-image-plane
		  (transform-region-to-window-coordinates region bleeding-hack)))

	    (multiple-value-bind (left top right bottom)
		(region-bounding-rectangle region-of-image-plane)
	      (with-nested-draw-area? (left top right bottom
					    region-of-image-plane :region-bounding-box)
		;; It's too bad that this enters an
		;; on-image-plane-with-drawing context,
		;; since most the time we don't do any drawing.
		
		(on-image-plane (current-image-plane)
		  (invalidate-region-of-image-plane-when-on-window
		    current-image-plane region-of-image-plane))))
	    (reclaim-region region-of-image-plane)))))))

;; This little routine binds the draw area 5 times.  It expands into 1800 lines of
;; C code, and binding 89 special variables.



;;; The function `invalidate-region-of-workspace-fast' may be used when the
;;; frame-transform block is the workspace.

(defun-allowing-unwind invalidate-region-of-workspace-fast
    (workspace region bleeding-hack)
  ;; If the workspace is not showing, then we would be invalidating the
  ;; cache count-of-pending-workspace-drawing, which is really the
  ;; count-of-pending-SHOWING-workspace-drawing. -fmw, 12/4/01
  (gensym-assert (workspace-showing-p workspace t))
  (unless (empty-region-p region)
    (when (null (invalid-region-of-workspace? workspace))
      (loop for count = count-of-pending-workspace-drawing
	    for new-value = (1+f count)
	    doing
	(when (compare-and-swap count-of-pending-workspace-drawing count new-value)
	  (when (=f 0 count)
	    (maybe-schedule-task-to-run-propagate-all-workspace-changes-to-image-planes))
	  (return new-value))))

    (setf (invalid-region-of-workspace? workspace)
	  (add-to-workspace-region (invalid-region-of-workspace? workspace)
				   region bleeding-hack))

    (force-workspace-drawing-if-appropriate workspace)))

;; Interestingly, this path does not sketch the paper.



;;; The function `invalidate-rectangle-of-workspace' is sugar on
;;; invalidate-region-of-workspace.  

(defun-allowing-unwind invalidate-rectangle-of-workspace
    (workspace frame-transform-block left top right bottom bleeding-hack)
  (with-region-from-rectangle-void (region left top right bottom)
    (invalidate-region-of-workspace
      workspace region bleeding-hack frame-transform-block)))



;;; `Invalidate-workspace' is sugar on invalidate-region-of-workspace.

(defun invalidate-workspace (workspace)
  (loop for image-plane in (image-planes-this-is-on workspace)
	do (invalidate-image-plane image-plane)))

;; This really is sugar, but the sugar and bun fused together.



;;;; Workspace regions




;;; A `workspace-region' is a region, in workspace coordinates, together with a
;;; value for bleeding-hack, which is a hint for how to convert to window
;;; coordinates.  It's used to represent the invalid region of both entire
;;; workspaces and individual blocks.

(def-structure (workspace-region
		 (:reclaimer reclaim-workspace-region-1)
		 (:constructor make-workspace-region
			       (workspace-region-region workspace-region-bleeding-hack))
		 #+development
		 (:print-function print-workspace-region))

  workspace-region-region
  workspace-region-bleeding-hack)

(defun reclaim-workspace-region (workspace-region)
  (reclaim-region (workspace-region-region workspace-region))
  (reclaim-workspace-region-1 workspace-region))


#+development
(defun print-workspace-region (workspace-region stream depth)
  (declare (ignore depth))
  (printing-random-object (workspace-region stream)
    (format stream "WORKSPACE-REGION ")
    (when (workspace-region-region workspace-region)
      (print-region-bounding-rectangle (workspace-region-region workspace-region)
				       stream)))
  workspace-region)



;;; The function `add-to-workspace-region' adds the given region with
;;; bleeding-hack to the region already present in workspace-region?, if any.
;;; The region argument is copied.

(defun add-to-workspace-region (workspace-region? new-region new-bleeding)
  (cond ((null workspace-region?)
	 (make-workspace-region (copy-region new-region) new-bleeding))
	(t
	 (let* ((old-region (workspace-region-region workspace-region?))
		(old-bleeding (workspace-region-bleeding-hack workspace-region?)))

	   ;; Union the regions.
	   (setf (workspace-region-region workspace-region?)
		 (union-region-and-simplify old-region new-region))

	   ;; Maximize the bleeding-hack.
	   (setf (workspace-region-bleeding-hack workspace-region?)
		 (bleeding-hack-maximum old-bleeding new-bleeding))

	   (reclaim-region old-region)
	   workspace-region?))))



;;;; Block changes



;;; The function `invalidate-region-of-block' invalidates the given region of
;;; the block, in workspace coordinates.  By "region of the block", we mean
;;; that the region must be wholely contained inside of the block.  Normally, the
;;; region represents a text-cell of a table or the entire block itself. It's
;;; only called by `invalidate-rectangle-of-block'.

;;; The invalidation regions are kept on the block and the workspace, for
;;; more efficient merging.

;;; We can enqueue a much more efficient drawing task in this case, one which
;;; does not need to scan the entire workspace searching for overlapping
;;; blocks, but rather can use the overlapping cache of the given block.
;;; If we ever have an efficient spacial index, we might be able to do away
;;; with this routine.

(defun invalidate-region-of-block (workspace block region)
  (with-drawing-trace (kb)
    (format t "BLK: ~s ~s ~a~%" block region (if (block-changes block) "merged" "")))

  (when (workspace-showing-p workspace t)
    (merge-change-to-block workspace block 'region region))

  (force-workspace-drawing-if-appropriate workspace))

(defun invalidate-rectangle-of-block (workspace block left top right bottom)
  (with-region-from-rectangle-void (region left top right bottom)
    (invalidate-region-of-block workspace block region)))

;;; The substitution-macro `appropriate-to-invalidate-color-of-block?'
;;; determines whether clients ought to call invalidate-color-of-block.
;;; Ideally, it would not be part of the drawing API (duh).

(def-substitution-macro appropriate-to-invalidate-color-of-block?
    (block-or-connection becoming-transparent?)
  (and (paint-mode-p)
       (drawing-is-scheduled?)				    ; We could allow this even if ASAP.
       (not becoming-transparent?)
       (not (if (framep block-or-connection) 
		(render-frame-in-xor-overlay-p block-or-connection)
		(render-connection-in-xor-overlay-p-function block-or-connection)))))



;;; The function `invalidate-color-of-block' takes a list of the names of the
;;; changed regions, and marks as invalid each region of the block. The list of
;;; regions is copied as needed.

(defun invalidate-color-of-block (workspace block changed-regions)
  (with-drawing-trace (kb)
    (format t "IC: ~s ~s ~a~%" block changed-regions (if (block-changes block) "merged" "")))

  (when (workspace-showing-p workspace t)
    (merge-change-to-block workspace block 'color changed-regions))
  
  (force-workspace-drawing-if-appropriate workspace))



;;;; Managing the block-change slot


(def-structure (block-change
		 (:constructor make-block-change (block-change-type block-change-arg))
		 (:reclaimer reclaim-block-change-1))
  block-change-type					    ; REGION or COLOR
  block-change-arg)					    ; A region or a list of icon-region names.

(defun reclaim-block-change (block-change)
  (case (block-change-type block-change)
    (region
     (reclaim-region (block-change-arg block-change)))
    (color
     (reclaim-slot-value-list (block-change-arg block-change))))
  (reclaim-block-change-1 block-change))


;; The slot on block.

(def-slot-value-reclaimer block-changes (block-change?)
  (when block-change?
    (reclaim-block-change block-change?)))


(defmacro block-change-region? (block-change)
  `(block-change-arg ,block-change))

(defmacro block-change-icon-regions? (block-change)
  `(block-change-arg ,block-change))


(def-substitution-macro copy-icon-regions (icon-regions)
  (copy-list-using-slot-value-conses icon-regions))

(def-substitution-macro reclaim-icon-regions (icon-regions)
  (reclaim-slot-value-list icon-regions))

(defun merge-icon-regions (old-regions new-regions)
  (let ((result (copy-icon-regions new-regions)))
    (loop for region in old-regions
	  unless (memq-macro region result)
	    do (slot-value-push region result))
    result))


;;; The function `merge-change-to-block' is the single bottleneck through which
;;; all additions to the block-changes slot must pass.  As such, it has to
;;; handle all the various arglists of all possible changes, which is too bad.
;;; Type should be 'region or 'color.

(defun merge-change-to-block (workspace block new-type region-or-icon-regions)
  (gensym-assert (workspace-showing-p workspace t))

  ;; If this is the first change, push onto the workspace's list.
  (let* ((block-change (block-changes block))
	 (old-type (if block-change
		       (block-change-type block-change)
		       'none)))
    
    (when (null block-change)
      #-SymScale
      (slot-value-push block (changed-blocks-of-workspace workspace))
      #+SymScale
      (slot-value-push-atomic block
	(changed-blocks-of-workspace workspace))
      (loop for count = count-of-pending-workspace-drawing
	    for new-value = (1+f count)
	    doing
	(when (compare-and-swap count-of-pending-workspace-drawing count new-value)
	  (when (=f 0 count)
	    (maybe-schedule-task-to-run-propagate-all-workspace-changes-to-image-planes))
	  (return new-value))))

    (case new-type
      (region
       (case old-type
	 (none
	  ;; region + nil = region
	  (setf (block-changes block)
		(make-block-change new-type (copy-region region-or-icon-regions))))
	 (region
	  ;; region + region = union the regions.
	  (let ((old-region (block-change-region? block-change)))
	    (setf (block-change-region? block-change)
		  (union-region-and-simplify region-or-icon-regions old-region))

	    (reclaim-region old-region)))

	 (color
	  ;; region + color = complete draw-block.
	  (let ((old-icon-regions (block-change-icon-regions? block-change)))
	    (setf (block-change-type block-change) 'region
		  (block-change-region? block-change) (make-region-from-block-edges block))
	    (reclaim-icon-regions old-icon-regions)))))

      (color
       (case old-type
	 (none
	  ;; color + nil = color
	  (setf (block-changes block)
		(make-block-change new-type (copy-icon-regions region-or-icon-regions))))

	 (region
	  ;; color + region = complete draw-block.
	  ;; Have to union with the old region -- it might be larger than the block.
	  (let ((old-region (block-change-region? block-change))
		(block-region (make-region-from-block-edges block)))
	    (setf (block-change-region? block-change)
		  (union-region-and-simplify old-region block-region))
	    (reclaim-region old-region)
	    (reclaim-region block-region)))

	 (color
	  ;; color + color = merge the lists of regions..
	  (let* ((old-icon-regions (block-change-icon-regions? block-change))
		 (new-icon-regions (merge-icon-regions old-icon-regions
						       region-or-icon-regions)))
	    (setf (block-change-icon-regions? block-change) new-icon-regions)
	    (reclaim-icon-regions old-icon-regions)))))
      (t
       #+development (error "Not a known type of block-change: ~s" new-type)))

    (with-drawing-trace (merge)
      (when block-change
	(format t "Merged ~s and ~s into ~s for ~s~%"
		old-type new-type (block-change-type (block-changes block)) block)))))









;;; The function `check-for-pending-drawing-on-window' pulls down pending
;;; changes for all workspaces on this window, and propagates the changes to
;;; the image-plane drawing queues for ALL image planes on which the workspace
;;; is visible.

(defun check-for-pending-drawing-on-window (gensym-window)
  (loop for pane in (panes-in-window gensym-window) doing
    (loop for image-plane in (stack-of-image-planes pane) doing
      (let ((workspace? (workspace-on-image-plane? image-plane)))
	(when (and workspace?
		  (pending-kb-drawing-for-workspace-p workspace?))
	  (propagate-workspace-changes-to-image-planes workspace?))))))

;; This is called too often -- when all the queues are empty, on each clock tick.
;; Need to call this where ever we work on image-plane drawing.



;;; The function `check-for-pending-drawing-on-workspace' pulls down any
;;; pending changes for the given workspace.

(defun check-for-pending-drawing-on-workspace (workspace)
  (when (pending-kb-drawing-for-workspace-p workspace)
    (propagate-workspace-changes-to-image-planes workspace)))

;; Bad idea?  The goal is to keep stuff on the workspace change list as long as
;; possible, so that more merging can happen.  IF there is no work already
;; scheduled on at least one of the image-plane queues, OR is force-p is true.

;; The loop over all image-planes could be a performance killer in large
;; telewindows installations, like Intelsat.

  
  
;;; The function `propagate-workspace-changes-to-image-planes' copies down
;;; pending KB drawing for the workspace into ALL the image-plane queues for
;;; EVERY image-plane the workspace is on.

(defun propagate-workspace-changes-to-image-planes (workspace)
  (let ((image-planes
	  (image-planes-this-is-on workspace))
	(changed-blocks-in-order
	  ;; Now in order from earliest change to oldest change.
	  (setf (changed-blocks-of-workspace workspace)
		(nreverse (changed-blocks-of-workspace workspace))))
	(workspace-region?
	  (invalid-region-of-workspace? workspace)))

    ;; First the region, if any.  There's no particular reason why we queue this first.
    (when workspace-region?
      (loop for image-plane in image-planes doing
	(unless (printing-image-plane-p image-plane)	    ; Note A
	  (on-image-plane-without-drawing (image-plane)   ; Ugh.
	    (let ((new-region
		    (transform-region-to-window-coordinates
		      (workspace-region-region workspace-region?)
		      (workspace-region-bleeding-hack workspace-region?))))
	      (cond ((empty-region-p new-region)
		     (reclaim-region new-region))
		    (t
		     (enqueue-drawing-task-for-image-plane
		       image-plane 'refresh-region-of-image-plane new-region)))))))

      (atomic-decff count-of-pending-workspace-drawing)
      (reclaim-workspace-region workspace-region?)
      ;; Q: Does this call the slot-value-reclaimer?  If not, when *is* it called?
      ;; A: No need, just above two lines have done all the things. --binghe.
      (setf (invalid-region-of-workspace? workspace) nil))
    
    ;; Then the changed blocks.
    (loop for block in changed-blocks-in-order
	  with block-change?
	  when block ; SymScale added --binghe
	  doing
      (setq block-change? (block-changes block))
      (unless block-change?
	(dwarn "Block ~s should have changes, but doesn't" block))

      (when block-change?
	(loop for image-plane in image-planes doing
	  (unless (printing-image-plane-p image-plane)	    ; Note A
	    (on-image-plane-without-drawing (image-plane)   ; Ugh.

	      (case (block-change-type block-change?)
		(region
		 (let ((new-region (transform-region-to-window-coordinates
				     (block-change-region? block-change?)
				     :bleeding-on-all-sides
;				     nil
				     ))) ; Lost bleeding-hack!
		   (cond ((empty-region-p new-region)
			  (reclaim-region new-region))
			 (t
			  (enqueue-drawing-task-for-image-plane
			    image-plane 'refresh-region-of-block new-region block)))))

		(color
		 (enqueue-drawing-task-for-image-plane
		   image-plane 'refresh-color-of-block nil block
		   (copy-icon-regions			    ; drawing-task-arg
		     (block-change-icon-regions? block-change?))))
		(t
		 #+development
		 (cerror "Ignore" "Unknown type of block change ~s"
			 (block-change-type block-change?)))))))
	#+SymScale
	(when (compare-and-swap (block-changes block) block-change? nil)
	  (reclaim-block-change block-change?))
	#-SymScale
	(progn
	  (setf (block-changes block) nil)
	  (reclaim-block-change block-change?))))
    #+SymScale
    (when (compare-and-swap (changed-blocks-of-workspace workspace)
			    changed-blocks-in-order nil)
      (atomic-decff count-of-pending-workspace-drawing (length changed-blocks-in-order))
      (reclaim-slot-value-list changed-blocks-in-order))
    #-SymScale
    (progn
      (setf (changed-blocks-of-workspace workspace) nil)
      (atomic-decff count-of-pending-workspace-drawing (length changed-blocks-in-order))
      (reclaim-slot-value-list changed-blocks-in-order))))

;; Note A: I think this is right.  Only printing's initial invalidation needs
;; to go through, and for that it calls invalidate-image-plane directly.



;;;; Window invalidation



;;; `Invalidate-region-of-window' does just that.  It is used to implement some
;;; updates requests from the host window system, to force a full refresh, and
;;; occasionally to do an image-plane update when we are sloppy.

(defun invalidate-region-of-window (gensym-window region)
  (with-drawing-trace (show-regions) (outline-region-of-window region :color 'green))
  (when (or (not (eq (type-of-gensym-window gensym-window) 'printer))
	    (drawing-for-eyes-of-player-p)
	    (printing-p))
    (multiple-value-bind (left top right bottom)
	(region-bounding-rectangle region)
      (update-window gensym-window left top right bottom
		     'invalidate-region-of-window-when-on-window region))))



;;; `Invalidate-rectangle-of-window' is sugar on
;;; invalidate-region-of-current-window

(defun-void invalidate-rectangle-of-window (window left top right bottom)
  (with-region-from-rectangle-void (region left top right bottom)
    (invalidate-region-of-window window region)))



;;; `Invalidate-raised-portions-of-image-plane' called raising an image-plane in
;;; the stack.  The image-plane being raised maybe invalidated by each of the
;;; image-planes it passes by, as they no longer obscure portions of the image.
;;; This is goes on window, and then defers drawing while it accumulates the
;;; total area invalidated.

(defun invalidate-raised-portions-of-image-plane
    (image-plane 
      image-planes-now-behind
      image-planes-previously-behind)
  (update-window   
    (gensym-window-for-image-plane image-plane)
    (left-edge-of-image-in-window image-plane)
    (top-edge-of-image-in-window image-plane)
    (right-edge-of-image-in-window image-plane)
    (bottom-edge-of-image-in-window image-plane)
    'invalidate-raised-portions-of-image-plane-1
    image-plane 
    image-planes-now-behind
    image-planes-previously-behind))

(defun invalidate-raised-portions-of-image-plane-1
    (image-plane 
      image-planes-now-behind
      image-planes-previously-behind)
  (with-deferred-drawing-in-current-window ()
    (loop for image-plane-moving-behind in image-planes-now-behind
	  as remaining-image-planes on image-planes-now-behind
	  do (invalidate-rectangle-of-image-plane-when-on-window 
	       image-plane
	       (left-edge-of-image-in-window image-plane-moving-behind)
	       (top-edge-of-image-in-window image-plane-moving-behind)
	       (right-edge-of-image-in-window image-plane-moving-behind)
	       (bottom-edge-of-image-in-window image-plane-moving-behind))
	  until (eq remaining-image-planes image-planes-previously-behind))))




;;; `Invalidate-subsequence-of-image-planes-for-current-pane' is a workhorse
;;; used, for example, when an image-plane is dropped down in the stack.  as the
;;; image-plane falls it may expose portions of the image-planes it passes on
;;; the way down.

;;; In another example it is used when the image-plane is removed.  That's
;;; sort of like dropping it past the pane's background.

;;; It can also be used to shrink an image-plane.  Which is like removing
;;; a portion of the image-plane.

;;; This engenders a mess of calls on
;;; invalidate-rectangle-of-image-plane-when-on-window and possibly one on
;;; invalidate-rectangle-of-pane-when-on-window.

;;; First and second arguments delimit the subsequence.  The remaining four
;;; arguments specify the rectangle of the image-plane that is dropping out, or
;;; the area of the image-plane being shrinked from.

;;; The first argument, list-of-image-planes, should a list of image planes in
;;; current-pane, and may be an empty list.  The second argument,
;;; tail-to-stop-past?, is either NIL, indicating the entire
;;; list-of-image-planes, plus the pane background, should be invalidated, or a
;;; cons, which must be a sublist of list-of-image-planes, indicating that the
;;; subsequence should end at that cons inclusively.  The somewhat unusual
;;; inclusive design enables control over invalidating the pane's background.

;;; Note that when both the first and second arguments are nil, this will
;;; invalidate just the pane background.  For example, both args should be nil
;;; when the bottommost image plane (furthest back from the glass) is shrunk
;;; down.  In that case you can think of there being a zero-length list of image
;;; planes "behind" the one being shrunk down, so there are no image planes to
;;; invalidate, and just the pane background needs to be invalidated.

;;; This must be invoked in the dynamic extent on-window-without-drawing.

;;; To tighten up the flicker it creates a deferred-drawing extent around the
;;; invalidation.

(defun invalidate-subsequence-of-image-planes-for-current-pane 
       (list-of-image-planes tail-to-stop-past? left top right bottom)
  (update-window 
    (gensym-window-for-pane current-pane) 
    left top right bottom 
    'invalidate-subsequence-of-image-planes-for-current-pane-1
    list-of-image-planes tail-to-stop-past? left top right bottom))

(defun-void invalidate-subsequence-of-image-planes-for-current-pane-1
    (list-of-image-planes tail-to-stop-past? left top right bottom)
  (within-named-dynamic-extent on-window-without-drawing
    (with-deferred-drawing-in-current-window ()
      (with-region-from-rectangle-void (region left top right bottom)
	(loop for remaining-image-planes on list-of-image-planes
	      as image-plane = (car remaining-image-planes)
	      do (invalidate-region-of-image-plane-when-on-window
		   image-plane region)
	      until (eq remaining-image-planes tail-to-stop-past?))
	(unless tail-to-stop-past?
	  (invalidate-region-of-pane-when-on-window current-pane region))))))













;;;; Misc Invalidation Routines.



;;; `Invalidate-reordered-image-planes' is a switching yard that calls the
;;; appropriate invalidating routine when raising or lowering an image-plane.

(defun invalidate-reordered-image-planes
    (gensym-window
      left-edge-of-area top-edge-of-area
      right-edge-of-area bottom-edge-of-area
      stack-of-image-planes
      image-plane-to-be-raised?
      tail-of-stack-to-start-projection-past?
      tail-of-stack-to-stop-projection-past?
      pane)
  (declare (ignore pane))
  (let ((current-window gensym-window))
    (cond (image-plane-to-be-raised?
	   (invalidate-raised-portions-of-image-plane
	     image-plane-to-be-raised?
	     (or (cdr tail-of-stack-to-start-projection-past?)
		 (cdr (memq image-plane-to-be-raised? stack-of-image-planes)))
	     tail-of-stack-to-stop-projection-past?))
	  (t
	   (invalidate-subsequence-of-image-planes-for-current-pane
	     (if tail-of-stack-to-start-projection-past?
		 (cdr tail-of-stack-to-start-projection-past?)
		 stack-of-image-planes)
	     tail-of-stack-to-stop-projection-past?
	     left-edge-of-area
	     top-edge-of-area
	     right-edge-of-area
	     bottom-edge-of-area)))))

;; formally update-window-by-projecting-per-stack-of-image-planes









;;;; Working On Scheduled Drawing




;;; There are two entry points that cause the queue of drawing tasks
;;; to be drained off the panes and image-planes.  One is a call
;;; made out of service-workstations to work-on-drawing-workstation.
;;; The other is a call made to work-on-drawing-image-plane that is
;;; made when an explicit request is made to bring the image-plane
;;; upto date.  

;; This request should be made declaratively on a workspace?




;;; `Working-on-drawing' is a dynamic extent that encloses the processing of
;;; drawing tasks enqueued on panes and image-planes.  It is never directly
;;; established, instead working-on-drawing-image-plane and
;;; working-on-drawing-pane include it.


(def-named-dynamic-extent working-on-drawing
  (module panes))



;;; Working-on-drawing-image-plane is a dynamic extent that includes
;;; working-on-drawing, and which requires a dynamic superior of on-image-plane.

(def-named-dynamic-extent working-on-drawing-image-plane
  (module panes)
  (includes working-on-drawing)
  (dynamic-superior for-image-plane))



;;; Working-on-drawing-pane is a dynamic extent that includes
;;; working-on-drawing, and which requires a dynamic superior of on-window.

(def-named-dynamic-extent working-on-drawing-pane
  (module panes)
  (includes working-on-drawing)
  (dynamic-superior on-window-with-drawing))


(defvar-of-named-dynamic-extent currently-working-on-drawing-p
    working-on-drawing
  (process-binding nil))


#+development
(defun find-bugs-in-changed-blocks ()
  (loop for workspace being each class-instance of 'kb-workspace
	as cache = (changed-blocks-of-workspace workspace)
	as changed = (compute-changed-blocks-of-workspace workspace)
	unless (or (and cache changed)
		   (and (null cache) (null changed)))
	  do (cerror "Slam" "Cached list ~s differs from actual changed blocks ~s for ~s"
		     cache changed workspace)
	     (setf (changed-blocks-of-workspace workspace)
		   (copy-list-using-slot-value-conses changed))))

#+development
(defun pending-workspace-drawing-for-window-p (gensym-window)
  (loop for pane in (panes-in-window gensym-window)
	thereis
	(loop for image-plane in (stack-of-image-planes pane)
	      as workspace? = (workspace-on-image-plane? image-plane)
	      thereis (and workspace?
			   (pending-kb-drawing-for-workspace-p workspace?)))))

;;; ~=f is used to roughly compare two fixnum values in changing environments.
(defmacro ~=f (a b)
  #+SymScale
  `(<f (-f number-of-all-threads)
       (-f ,a ,b)
       number-of-all-threads)
  #-SymScale
  `(=f ,a ,b))

#+development
(defun find-bugs-in-count-of-enqueued-drawing (gensym-window)
  ;; Check the invariant for (count-of-enqueued-drawing gensym-window)
  (let ((computed-count
	  (loop for pane in (panes-in-window gensym-window)
		sum (+f (queue-length (pane-drawing-schedule pane))
			(loop for image-plane in (stack-of-image-planes pane)
			      sum (queue-length
				    (image-plane-drawing-schedule image-plane)))))))
    (unless (~=f (count-of-enqueued-drawing gensym-window) computed-count)
      (cerror "Slam it!" "Window's count-of-enqueued-drawing ~d is wrong, should be ~d."
	      (count-of-enqueued-drawing gensym-window)
	      computed-count)
      (setf (count-of-enqueued-drawing gensym-window) computed-count)))

  ;; Check the invariant for count-of-pending-workspace-drawing
  #-SymScale
  (let ((computed-count
	  (loop for ws being each class-instance of 'workspace
		as region? = (invalid-region-of-workspace? ws)
		as blocks? = (changed-blocks-of-workspace ws)
		if (workspace-showing-p ws t)
		  count region?
		  and sum (length blocks?))))
    (unless (~=f count-of-pending-workspace-drawing computed-count)
      (cerror "Slam it!" "Count of workspace drawing ~d is wrong, should be ~d."
	      count-of-pending-workspace-drawing
	      computed-count)
      (setf count-of-pending-workspace-drawing computed-count))))





;;; `Work-on-drawing-window' is invoked on a single gensym-window.  It works on
;;; drawing that window until it is done or time-slice-expired-p returns true.
;;; It does not require any unique dynamic extent.  Called from
;;; `service-workstation', it returns T iff some works was done.

;;; If blocking is allowed, and the gensym-window is blocked (ie, it is an ICP
;;; window and ICP is clogged), then we return without doing any drawing.

(defun work-on-drawing-window (gensym-window allow-blocking-p)
  (let ((work-was-done-p nil)
	(extra-time-for-drawing 0))	     ; Special variable
    
    #+development
    (find-bugs-in-count-of-enqueued-drawing gensym-window)
    
    ;; We should be lazier about calling this function.
    (when (>f count-of-pending-workspace-drawing 0)
      (check-for-pending-drawing-on-window gensym-window))

    (when (>f (count-of-enqueued-drawing gensym-window) 0)
      #+development (update-pseudo-run-lights :work-on-drawing-window)
      (with-temporary-profiling-context redraw
	(setq work-was-done-p
	      ;; (unless (and allow-blocking-p gensym-window-drawing-blocked-p) ...)
	      (and (or (not allow-blocking-p)
		       (not (gensym-window-drawing-blocked-p gensym-window)))
		   (update-window-macro
		     gensym-window
		     (left-edge-of-window gensym-window)
		     (top-edge-of-window gensym-window)
		     (right-edge-of-window gensym-window)
		     (bottom-edge-of-window gensym-window)
		     work-on-drawing-current-window)))))

    work-was-done-p))

;; Work-on-drawing-window is not inside on-window since that may flicker
;; the cursor, and because this should be called directly from the main
;; scheduler.  For now it is called from service workstation.


;;; The function `work-on-drawing-current-window' pops instructions
;;; from the drawing queues for the current window and executes
;;; them until the time slice expires.  It returns T iff some work
;;; was done (and presumably some is remaining?).

(defun-allowing-unwind work-on-drawing-current-window ()
  (let ((work-was-done? nil))
    (within-named-dynamic-extent on-window-with-drawing	
      (with-drawing-trace (time-slice)
	(format t "Time slice: ~d/~dms, ~s expired-p = ~s~%"
		(fixnum-time-difference (get-fixnum-time) time-slice-start-time)
		maximum-time-slice-size
		current-window
		(drawing-time-slice-expired-p)))

      (unless (drawing-blocked-p)
	;; First the pane, it's fast and looks better
	(loop with schedule
	      for current-pane in (panes-in-window current-window)
	      doing
	  (setq schedule (pane-drawing-schedule current-pane))
	  (unless (queue-empty-p schedule)
	    (setq work-was-done? t)
	    (work-on-drawing-schedule schedule)
	    (when (and (icp-window-p current-window)
		       (=f (icp-connection-state current-icp-socket) icp-connection-closed))
	      (return)))

	  ;; Then the image-planes front to back.  Check for time expiration at
	  ;; the end, so that we always do some work.
	  (loop for image-plane in (stack-of-image-planes current-pane)
	        doing
	    (setq schedule (image-plane-drawing-schedule image-plane))
	    (unless (queue-empty-p schedule)
	      (let ((work-was-really-done? nil))
		(with-nested-image-plane-draw-area? (image-plane)
		  (with-image-plane-transform (image-plane)
		    (for-image-plane (image-plane)
		      (setf work-was-really-done? t)
		      (work-on-drawing-schedule schedule)
		      (when (and (icp-window-p current-window)
				 (=f (icp-connection-state current-icp-socket) icp-connection-closed))
			(return)))))
		(unless work-was-really-done?
		  (reclaim-drawing-schedule
		    ;; Queue had work, but the image-plane
		    ;; wasn't exposed at all.
		    (image-plane-drawing-schedule image-plane)))
		(setf work-was-done? t)
		(when (drawing-time-slice-expired-p)
		  (return)))))

	      until (drawing-time-slice-expired-p))))

    work-was-done?))

;;; Sad, image-planes toward the back can starve.  It also makes it hard to
;;; implement a ping without the cost of a synch over all Q.  - ben May 8 1995.



;;; The function `work-on-drawing-schedule-of-current-image-plane' does some
;;; drawing for the current image plane.  Must be called in a for-image-plane
;;; context.

(defun-void work-on-drawing-schedule-of-current-image-plane ()
  (let ((schedule (image-plane-drawing-schedule current-image-plane)))
    (unless (queue-empty-p schedule)
      (work-on-drawing-schedule schedule))))




;;; `work-on-drawing-schedule' takes a Q of drawing tasks and works upon them
;;; until the current scheduling quantum is exhausted.  A for-image-plane must
;;; be established if the schedule is that of an image-plane.

;;; A drawing schedule is a queue drawing-tasks.  All coordinates given in
;;; these are window coordinates.  The drawing schedule must be non-nil.

(defun work-on-drawing-schedule (schedule)
  #+development (find-bugs-in-drawing-schedule schedule)
  (with-drawing-trace (sked)
    (print-drawing-schedule schedule :verbose t))
  
  (unless (drawing-blocked-p)
    ;; Note that drawing tasks are allowed to enqueue new tasks. In particular,
    ;; refresh-region-of-block sometimes enqueues a refresh-region-of-image-plane.
    ;; So the schedule queue might not decrease in length every time through this
    ;; loop but it is guarenteed to eventually become empty as all of the
    ;; refresh-region-of-block tasks are processed. -fmw, 10/21/02
    (loop with working-on-drawing-schedule = t
	  for drawing-task = (queue-peek schedule)
	  ;; NOTE: still possible to be NIL in SymScale.
	  while drawing-task
	  as operation = (drawing-task-operation drawing-task)
	  as state = (drawing-task-state drawing-task)
	  as region? = (drawing-task-region? drawing-task)
	  as block? = (drawing-task-block? drawing-task)
	  as arg? = (drawing-task-arg drawing-task)	    ; A list of icon-regions, if anything.
	  doing
      (case operation
	(refresh-region-of-image-plane
	 (setq state (refresh-region-of-image-plane drawing-task state region? current-image-plane)))

	(refresh-region-of-block
	 (setq state (refresh-region-of-block drawing-task state region? current-image-plane block?)))

	(refresh-color-of-block
	 (setq state (refresh-color-of-block drawing-task state current-image-plane block? arg?)))

	(refresh-region-of-pane
	 (setq state (refresh-region-of-pane drawing-task state region? current-pane)))

	(ping-image-plane-drawing
	 (setq state (ping-image-plane-drawing drawing-task state current-image-plane arg?)))

	(t
	 (dwarn "Unknown drawing task operation ~s." operation)))

      (cond (state					    ; Update state in-place. 
	     (with-drawing-trace (task)
	       (format t " Update: ~s ~s~%" drawing-task state))
	     ;; insert the dequeued task back for next rounds.
	     (update-drawing-task-state drawing-task state))
	    (t						    ; NIL means that task is done.
	     (with-drawing-trace (pop)
	       (format t " Finished: ~s~%" drawing-task))
	     (queue-pop schedule)
	     (atomic-decff (count-of-enqueued-drawing current-window))
	     (reclaim-drawing-task drawing-task)
	     (with-drawing-trace (queue)
	       (format t "  Queue count: ~d~%" (count-of-enqueued-drawing current-window)))))

      #+development
      (find-bugs-in-drawing-schedule schedule)

      #+(and lucid development)
      (with-drawing-trace (single-step)
	(sync-graphics-on-current-window)
	(lcl:prompt-and-read :string "Pause"))
      
      (when (or (queue-empty-p schedule)
		(drawing-time-slice-expired-p))
	(return)))))




;;;; Ping Workspace Drawing


;;; `Ping-workspace-drawing' broadcasts to the image-planes of this
;;; workspace the desire for a drawing-ping.  Children are created on
;;; given identified drawing activity that will block it's
;;; continuation until all N image-planes have replied.  These
;;; children are given a continuation which will remove them from the
;;; window.  Before enqueuing the children the workspace drawing
;;; queues are pulled down into the image-plane drawing queue.

(defun ping-workspace-drawing
    (workspace identified-drawing-activity-of-workspace)
  ;; Flush the workspace Queue into the image-plane Queues
  (propagate-workspace-changes-to-image-planes workspace)
  ;; Broadcast the ping into the image-plane queues
  (loop for image-plane in (image-planes-this-is-on workspace) doing
    (unless (printing-image-plane-p image-plane)
      (on-image-plane-without-drawing (image-plane)   ; Ugh.
	(let ((drawing-activity-for-image-plane
		(start-identified-drawing-activity
		  (gensym-window-for-image-plane image-plane)
		  identified-drawing-activity-of-workspace
		  #'remove-identified-drawing-activity)))
	  (enqueue-drawing-task-for-image-plane
	    image-plane
	    'ping-image-plane-drawing
	    nil
	    nil
	    (id-of-identified-drawing-activity
	      drawing-activity-for-image-plane)))))))








;;;; Putting Up and Changing Images



;;; `Put-workspace-on-pane' puts a new top plane on pane with an image of
;;; workspace.  The image plane will be on the left, on the right, or
;;; horizontally centered in the pane depending on whether left-or-right? is
;;; LEFT, RIGHT, or nil, respectively; it will be at the top, at the bottom, or
;;; vertically centered depending on whether top-or-bottom?  is TOP, BOTTOM, or
;;; nil, respectively.  If scale-or-t-to-choose-scale-to-fit-in-pane?  is nil,
;;; the image plane will have the default x and y scales for the window; if it
;;; is t, the image will be either at the maximum (default-proportioned) scale
;;; or at a (default-proportioned) scale such that the image fits with at least
;;; 2.5% margins on each side; otherwise,
;;; scale-or-t-to-choose-scale-to-fit-in-pane? should be the x and y scale to
;;; use.
;;;
;;; Frame-description-reference, a keyword argument, may be passed in to
;;; override that the default frame style for the workspace.  This is used by
;;; enter-dialog at present, for example, to pass in its nicer bordering.  In
;;; general, it would likely be a mistake to override a user-assigned frame
;;; style for a user-owned (KB) workspace.

;;; This function returns the new image plane it creates.

(defun-allowing-keywords put-workspace-on-pane
       (workspace
	 pane
	 horizontal-alignment?	       ; left, right, defaults to "center"
	 vertical-alignment?	       ; top, bottom, defaults to "center"
	 scale-or-t-to-choose-scale-to-fit-in-pane?
	 &key
	 (margin-in-pane 11)
	 at-the-bottom?
	 frame-description-reference
	 ;; added keywords in `put-workspace-on-pane-1'
	 modal size-x size-y pos-x pos-y)
  (let* ((image-plane
	  (get-available-image-plane
	    pane
	    (or frame-description-reference
		(lookup-frame-description-reference-of-block? workspace))
	    at-the-bottom?))
	 (x-in-window
	   (case horizontal-alignment?
	     (left (+r (left-edge-of-pane-in-window image-plane)
		       margin-in-pane))
	     (right (-r (right-edge-of-pane-in-window image-plane)
			margin-in-pane))
	     (t (halfr (+r (left-edge-of-pane-in-window image-plane)
			   (right-edge-of-pane-in-window image-plane))))))
	 (y-in-window
	   (case vertical-alignment?
	     (top (+r (top-edge-of-pane-in-window image-plane)
		      margin-in-pane
		      ;; The following allows callers that put up images
		      ;; relative to the top of the pane to continue to function
		      ;; as expected even when the images have addition junk at
		      ;; the top, e.g., title bars and thicker borders.  -- This
		      ;; is part the new-g2-classic-ui-p. (MHD 9/13/99)
		      (maxr 0
			    (-r (top-frame-indent
				  (frame-description-reference-of-image-plane image-plane))
				assumed-standard-image-plane-border-width))))
	     (bottom (-r (bottom-edge-of-pane-in-window image-plane)
			 margin-in-pane))
	     (t (halfr (+r (top-edge-of-pane-in-window image-plane)
			   (bottom-edge-of-pane-in-window image-plane))))))
	 (x-in-workspace
	   (case horizontal-alignment?
	     (left (left-edge-of-block workspace))
	     (right (right-edge-of-block workspace))
	     (t (halfw (+w (left-edge-of-block workspace)
			   (right-edge-of-block workspace))))))
	 (y-in-workspace
	   (case vertical-alignment?
	     (top (top-edge-of-block workspace))
	     (bottom (bottom-edge-of-block workspace))
	     (t (halfw (+w (top-edge-of-block workspace)
			   (bottom-edge-of-block workspace)))))))
    (put-image-on-image-plane
      image-plane workspace
      scale-or-t-to-choose-scale-to-fit-in-pane?	; x scale, or t
      scale-or-t-to-choose-scale-to-fit-in-pane?	; y scale, or t
      (if (eq scale-or-t-to-choose-scale-to-fit-in-pane? t)	; fraction-...
	  #.(convert-to-magnification-at-compile-time 1.025))
      nil					; block to position on
      x-in-workspace y-in-workspace x-in-window y-in-window
      ;; added passing arguments in `put-workspace-on-pane-1'
      modal size-x size-y pos-x pos-y)
    image-plane))

;;; `Restore-workspace-onto-pane' puts a new top plane on pane with an image of
;;; workspace.  Workspace-x-at-center-of-pane, workspace-y-at-center-of-pane,
;;; x-scale, and y-scale determine the position and scale of the new image
;;; plane.

;;; The new image plane is returned.

;;; See also post-workspace-in-pane and put-workspace-on-pane

#+unused
(defun restore-workspace-onto-pane
       (workspace pane
	workspace-x-at-center-of-pane workspace-y-at-center-of-pane
	x-scale y-scale)
  (let* ((image-plane
	  (get-available-image-plane
	    pane
	    (lookup-frame-description-reference-of-block? workspace)
	    nil)))
    (put-image-on-image-plane
      image-plane workspace x-scale y-scale nil nil
      workspace-x-at-center-of-pane workspace-y-at-center-of-pane nil nil)
    image-plane))

;; Consider specifying the position and scale as they are specified in a saved
;; kb.



;; GET RID OF THE FOLLOWING KLUDGES IN FAVOR OF THE ABOVE!!!

;; PROBLEM: Callers put-up-attributes-table (in TABLES) and put-up-table-of-
;; values (in FUNCTIONS) depend need the functionality of the x-in-window,
;; y-in-window, and always-fit-image-plane-in-window? args used in put-
;; workspace-on-top-plane-at-position-in-window.  (All other callers were
;; converted.  But nothing done yet with post-workspace-in-window.  See it
;; in MENUS.) (MHD 4/10/89)



;;; `Post-workspace-in-pane' ... If x-in-window-for-center-or-left-of-workspace?
;;; or y-in-window-for-top-of-workspace? are nil, this keeps the existing image
;;; plane (if any) at its same position and scale.  If there is no existing
;;; image plane, this puts up the new workspace with its origin at the center of
;;; pane.  This creates and returns the image plane the workspace is posted on.
;;; (see also post-workspace-on-pane).

;;; This function looks like it is the general way to post a workspace, but it's
;;; not.  It is used exclusively for posting tables (regular, virtual, menu, and
;;; table-of-values). Other workspaces are posted with `transform-image' (which
;;; in turn uses `compute-scale-to-fit', instead of `compute-image-transformation-to-fit-in-pane'
;;; used here). So, this function would better be called something like
;;; `post-table-workspace-with-special-alignment-options'.

(defun-allowing-keywords post-workspace-in-pane
    (workspace pane
	       x-in-window-for-center-of-workspace?
	       y-in-window-for-top-of-workspace?
	       &key
	       existing-image-plane?
	       default-x-scale?
	       default-y-scale?
	       x-for-left-adjusting?
	       x-for-right-adjusting?
	       direction-for-adjusting?)
  (let* ((frame-description-reference
	   (lookup-frame-description-reference-of-block? workspace))
	 (image-plane
	   (cond
	     (existing-image-plane?
	      (release-frame-description-reference-if-any
		(frame-description-reference-of-image-plane
		  existing-image-plane?))
	      (setf
		(frame-description-reference-of-image-plane
		  existing-image-plane?)
		(reference-frame-description-reference
		  frame-description-reference))
	      existing-image-plane?)
	     (t
	      (get-available-image-plane
		pane
		frame-description-reference
		nil))))
	 (adjustment-of-workspace nil))
    (cond
      ((and (or x-in-window-for-center-of-workspace?
		x-for-left-adjusting?
		x-for-right-adjusting?)
	    y-in-window-for-top-of-workspace?)
       (multiple-value-bind
	   (x-scale y-scale x-in-workspace y-in-workspace x-in-window y-in-window adjustment)
	   (compute-image-transformation-to-fit-in-pane
	     workspace image-plane
	     x-in-window-for-center-of-workspace?
	     y-in-window-for-top-of-workspace?
	     default-x-scale? default-y-scale?
	     x-for-left-adjusting? x-for-right-adjusting?
	     direction-for-adjusting?
	     frame-description-reference)
	 (setq adjustment-of-workspace adjustment)
	 (unless (and (or (eq direction-for-adjusting? 'left)
			  (eq direction-for-adjusting? 'right))
		      (not (eq adjustment direction-for-adjusting?)))
	   (transform-image
	     image-plane workspace
	     x-scale y-scale nil nil
	     x-in-workspace y-in-workspace
	     x-in-window y-in-window
	     nil nil nil nil
	     t))))
      (t
       (transform-image
	 image-plane workspace
	 nil nil nil nil
	 nil nil nil nil
	 nil nil nil nil
	 t)))

    ;; This "autoselection" code is completely bogus. It is only an
    ;; approximation of the behavior we want.
    (when (and (null existing-image-plane?)
	       (selection-enabled-p (gensym-window-for-pane pane)))
      (cond ((and (menu-workspace-p workspace)
		  (image-plane-native-window? image-plane))
	     (%select-image-plane image-plane)) ; FIXME: This is a hack for 8.0 alpha to get
					        ; the editor's cut/paste menu to show up on top.
	    ((selectable-image-plane-p image-plane)
	     (select-topmost-workspace (workstation-of-image-plane image-plane)))))

    (values image-plane adjustment-of-workspace)))

;; This used to put the menu to the side of the mouse when it had to be shifted
;; up to fit in the window; consider doing something similar again!




;;; `Compute-image-transformation-to-fit-in-pane' returns the following values,
;;; which may be supplied as the same-named args to tranform-image, in order to
;;; have workspace displayed on image-plane such that it fits into pane with a
;;; little margin, as close in position to that specified in the x/y-... args,
;;; and as close in scale to the x and y default scales, as can be allowed such
;;; that workspace is completely exposed within the pane.
;;;
;;;    (1) x-scale
;;;    (2) y-scale
;;;    (3) x-in-workspace
;;;    (4) y-in-workspace
;;;    (5) x-in-window
;;;    (6) y-in-window
;;;
;;; This tries and almost never fails to return values such that the resulting
;;; tranformation leaves the image entirely within the pane. However, a scale
;;; smaller than the minimum allowed by the system cannot be permitted, so
;;; theoretically, for a large enough menu, in a small enough pane, this could
;;; "lose" in that the minimum scale image would in fact go outside the pane,
;;; but that would be an extreme case.)
;;;
;;; X-in-window-for-center-or-left-of-workspace is normally taken to specify the
;;; center of the workspace unless left-adjusted-case? or right-adjusted-case?
;;; are specified true, in which case it's taken to taken to specify the left
;;; edge.  Note that left- and right-adjusted-case? are mutually exclusive: if
;;; both are specified true, one of the two cases will be randomly chosen.

;;; `WARNING:' The present function is used only when posting tables. There is
;;; another similar but different function, `compute-scale-to-fit', for the
;;; general case. It uses `fraction-of-image-width-or-height-to-have-within-rectangle',
;;; instead of `minimum-margin-between-pane-and-image-plane'.

;;; If x-for-left-adjusting? or x-for-right-adjusting? are supplied, then
;;; x-in-window-for-center-of-workspace is ignored.

(defun compute-image-transformation-to-fit-in-pane
    (workspace image-plane
	       x-in-window-for-center-of-workspace y-in-window-for-top-of-workspace
	       default-x-scale? default-y-scale?
	       x-for-left-adjusting? x-for-right-adjusting? direction-for-adjusting?
	       frame-description-reference)
  (let* ((usable-pane-width
	   (-r (right-edge-of-pane-in-window image-plane) 
	       (left-edge-of-pane-in-window image-plane)
	       (twicer minimum-margin-between-pane-and-image-plane)))
	 (usable-pane-height
	   (-r (bottom-edge-of-pane-in-window image-plane) 
	       (top-edge-of-pane-in-window image-plane)
	       (twicer minimum-margin-between-pane-and-image-plane)))
	 (workspace-width (+f (width-of-block workspace)
			      (left-frame-indent frame-description-reference)
			      (right-frame-indent frame-description-reference)))
	 (workspace-height (+f (height-of-block workspace)
			       (top-frame-indent frame-description-reference)
			       (bottom-frame-indent frame-description-reference)))
	 (default-x-scale
	     (or default-x-scale? (get-default-image-x-scale image-plane)))
	 (default-y-scale
	     (or default-y-scale? (get-default-image-y-scale image-plane)))
	 (x-scale
	   (if (image-plane-will-be-scrollable-p image-plane)
	       default-x-scale
	       ;; Scale so it will fit in the pane, with a small margin around it.
	       (with-temporary-gensym-float-creation
		   post-workspace-in-pane
		 (round 
		   (* default-x-scale
		      (min 1	      ;; changed to min of 2 args 
			   (min    ;;   for Chestnut/SGI bug (MHD 10/2/92)
			     (/ usable-pane-width
				(coerce-to-gensym-float
				  (delta-x-in-window
				    workspace-width
				    default-x-scale)))
			     (/ usable-pane-height
				(coerce-to-gensym-float
				  (delta-y-in-window
				    workspace-height
				    default-y-scale))))))))))
	 (y-scale
	   (scale-scale default-y-scale x-scale default-x-scale))
	 (half-width-of-workspace-in-window
	   (delta-x-in-window (halfw (width-of-block workspace)) x-scale))
	 (adjustment direction-for-adjusting?))
    (unless adjustment
      (setq adjustment
	    (cond (x-for-left-adjusting? 'left)
		  (x-for-right-adjusting? 'right))))
    (case adjustment
      (left
       (setq x-in-window-for-center-of-workspace
	     (+r x-for-left-adjusting? half-width-of-workspace-in-window))
       (when (and x-for-right-adjusting?
		  (>r x-in-window-for-center-of-workspace
		      (-r (right-edge-of-pane-in-window image-plane)
			  half-width-of-workspace-in-window
			  minimum-margin-between-pane-and-image-plane)))
	 (setq x-in-window-for-center-of-workspace
	       (-r x-for-right-adjusting? half-width-of-workspace-in-window))
	 (setq adjustment 'right)))
      (right
       (setq x-in-window-for-center-of-workspace
	     (-r x-for-right-adjusting? half-width-of-workspace-in-window))
       (when (and x-for-left-adjusting?
		  (<r x-in-window-for-center-of-workspace
		      (+r (left-edge-of-pane-in-window image-plane)
			  half-width-of-workspace-in-window
			  minimum-margin-between-pane-and-image-plane)))
	 (setq x-in-window-for-center-of-workspace
	       (+r x-for-left-adjusting? half-width-of-workspace-in-window))
	 (setq adjustment 'left))))
    (values
      x-scale y-scale
      (halfw (+w (left-edge-of-block workspace) (right-edge-of-block workspace)))
      (top-edge-of-block workspace)
      (maxr
	(+r (left-edge-of-pane-in-window image-plane)
	    half-width-of-workspace-in-window
	    minimum-margin-between-pane-and-image-plane)
	(minr (-r (right-edge-of-pane-in-window image-plane)
		  half-width-of-workspace-in-window
		  minimum-margin-between-pane-and-image-plane)
	      x-in-window-for-center-of-workspace))
      (maxr
	(+r (top-edge-of-pane-in-window image-plane)
	    minimum-margin-between-pane-and-image-plane
	    (top-frame-indent frame-description-reference))
	(minr (-r (bottom-edge-of-pane-in-window image-plane)
		  (delta-y-in-window
		    (height-of-block workspace)
		    y-scale)
		  minimum-margin-between-pane-and-image-plane)
	      y-in-window-for-top-of-workspace))
      adjustment)))

;;; `Put-image-on-image-plane' is an alias of transform-image, intended for the
;;; case where a workspace is being put on an image plane.

(defun put-image-on-image-plane
       (image-plane workspace
	new-image-x-scale? new-image-y-scale?
	fraction-of-image-width-or-height-to-have-within-pane?
	block-to-position-on? x-in-workspace? y-in-workspace?
	x-in-window? y-in-window?
        ;; Added by SoftServe
        &optional
        modal size-x size-y pos-x pos-y)
  ;; block-to-position-on? is always NIL in callers.
  (transform-image
    image-plane workspace
    new-image-x-scale? new-image-y-scale?
    fraction-of-image-width-or-height-to-have-within-pane?
    block-to-position-on? x-in-workspace? y-in-workspace?
    x-in-window? y-in-window?
    nil nil nil nil nil nil
    ;; Added by SoftServe
    modal size-x size-y pos-x pos-y)
  (when (selection-enabled-p (gensym-window-for-image-plane image-plane))
    (select-topmost-workspace (workstation-of-image-plane image-plane))))


;;; `Transform-image' transforms the image, if any, on image-plane or, when
;;; workspace? is specified, puts an image or new image there.  The scale and
;;; position of the resulting image, if any, are determined by the current state
;;; of image-plane, as well as by other arguments of transform-image.

;;; The x and y scales of the image plane remain unchanged unless
;;; new-image-x-scale?, new-image-y-scale?, and/or fraction-of-image-width-
;;; or-height-to-have-within-pane? are specified, or unless the old scales were
;;; out-of-limits (which ought never to occur), or unless left-edge-for-image?,
;;; top-edge-for-image?, right-edge-for-image?, and bottom-edge-for-image? are
;;; specified.

;;; When fraction-of-image-width-or-height-to-have-within-pane? is specified (as
;;; a magnification, or the opposite (negative) of one) and there is an image, a
;;; new scale for the image plane is computed such that (1) that exact fraction
;;; of either the width or height of the image would fit in the pane and (2) at
;;; least that large a fraction of the other dimension of the image would fit in
;;; the pane.  This then becomes the new scale for the image plane, subject to
;;; the constraints that the x and y scales must be in the same proportion as
;;; the default x and y scales are for the window and that neither the x nor y
;;; scale can be larger than the default scale, for a positive magnification,
;;; and the maximum scale, for a negative magnification, for the window.  When
;;; fraction-of-image-width-or-height-to-have-within-pane? is specified,
;;; new-image-x-scale? and new-image-y-scale? are ignored.

;;; Note: new-image-x-scale? and new-image-y-scale? are sometimes supplied as T
;;; in this case (when called from put-workspace-on-pane).

;;; When fraction-of-image-width-or-height-to-have-within-pane? is NIL, and
;;; left-edge-for-image? is optionally specified, the other three edges are
;;; assumed to be specified as well.  In this case, the new x and y scales for
;;; the image plane are computed so that the edges of the image plane including
;;; its border match those specified.

;;; Whether old or newly specified or computed, the x and y scales are tested
;;; against the minimum-scale and maximum-scale window-parameter limits.  If a
;;; limit is violated, the x and y scales are adjusted, without changing their
;;; ratio, to be just within the limit.  (It is assumed that the ratio of the x
;;; and y scales does not exceed the ratio of the limits.)  Note, for example,
;;; that when a new-image-x-scale? exceeding the maximum scale is specified and
;;; no new-image-y-scale? is specified, the result will be a reduction of the y
;;; scale.

;;; The position of the image can be affected only if there is one.  When there
;;; is an image, the position of the (0,0) origin of the workspace remains
;;; unchanged (or, if there was no prior image, is centered in the pane), unless
;;; block-to-position-on?, x-in-workspace?, and/or y-in-workspace? are
;;; specified.  When x-in-workspace? is not specified but block-to-position-on?
;;; is, x-in-workspace? is implicitly specified as the x center of
;;; block-to-position-on?; y-in-workspace? is similar.  When x-in-workspace? is
;;; specified, explicitly or implicitly, the image is so positioned that the
;;; x-in-workspace? coordinate of the workspace is approximately aligned with
;;; the x-in-window? of the pane (or with the center of the pane when
;;; x-in-window? is nil); y-in-workspace? and y-in-window? are similar.

;;; As an example, specifying #.(convert-to-magnification-at-compile-time 1.2)
;;; for fraction-of-image-width-or-height-to-have-within-pane?, the workspace
;;; for block-to-position-on?, and other arguments nil would cause the whole
;;; image of the workspace to fit in the pane, centered, with an extra 10% on
;;; one pair of opposite sides and at least an extra 10% on the other pair of
;;; opposite sides, unless the image is so large that 10% could not fit at
;;; minimum scale.

(defun transform-image
    (image-plane workspace?
		 new-image-x-scale? new-image-y-scale?
		 fraction-of-image-width-or-height-to-have-within-pane?
		 block-to-position-on? x-in-workspace? y-in-workspace?
		 x-in-window? y-in-window?
		 &optional
		 left-edge-for-image? top-edge-for-image?
		 right-edge-for-image? bottom-edge-for-image?
		 raise-image-plane-to-top?		    ; DOCUMENT!
		 tail-of-stack-to-start-projection-past?    ; BAD IDEA! REVISE THIS!
		 ;; Added by SoftServe
                 modal size-x size-y pos-x pos-y)
  (let* (;; Unpack pane knowledge.
	 (pane (pane-for-image-plane image-plane))
	 (left-edge-of-pane-in-window
	   (left-edge-of-pane-in-window image-plane))
	 (top-edge-of-pane-in-window
	   (top-edge-of-pane-in-window image-plane))
	 (right-edge-of-pane-in-window
	   (right-edge-of-pane-in-window image-plane))
	 (bottom-edge-of-pane-in-window
	   (bottom-edge-of-pane-in-window image-plane))

	 ;; Unpack window knowledge
	 (gensym-window (gensym-window-for-pane pane))
	 (minimum-scale
	   (get-gensym-window-parameter gensym-window 'minimum-scale))
	 (maximum-scale
	   (get-gensym-window-parameter gensym-window 'maximum-scale))

	 ;; Old layout knowledge
	 (old-workspace?
	   (workspace-on-image-plane? image-plane))
	 (old-left-edge-of-image-within-pane
	   (maxr (left-edge-of-image-in-window image-plane)
		 left-edge-of-pane-in-window))
	 (old-top-edge-of-image-within-pane
	   (maxr (top-edge-of-image-in-window image-plane)
		 top-edge-of-pane-in-window))
	 (old-right-edge-of-image-within-pane
	   (minr (right-edge-of-image-in-window image-plane)
		 right-edge-of-pane-in-window))
	 (old-bottom-edge-of-image-within-pane
	   (minr (bottom-edge-of-image-in-window image-plane)
		 bottom-edge-of-pane-in-window))

	 ;; Maybe we should trigger a block showing event.
	 (workspace?-was-initially-showing
	   (if workspace?
	       (and (workspace-showing-p workspace? nil)
		    t)
	       (and old-workspace?
		    ;; compute to see if old workspace? was showing,
		    ;; although my guess is that this is true iff
		    ;; (and (not workspace?) old-workspace?)
		    ;; but I'm not confident enough of this proof.
		    ;; Please see comment in the function,
		    ;; event-update-status-of-block-showing
		    nil)))

	 ;; Computed at great expense below
	 image-x-scale image-y-scale

	 ;; Maybe some of what is on screen can be reused.
	 (image-needs-refreshing?  ;; rebound
	   (or
	     (and workspace?
		  (not (eq workspace? (workspace-on-image-plane? image-plane))))
	     (eq image-plane
		 (image-plane-to-continue-refreshing? 
		   (workstation-this-is-on gensym-window))))))
    (cond
      ;; Changing workspace on this image-plane.
      ((and workspace?
	    (not (eq workspace? (workspace-on-image-plane? image-plane))))
       (associate-workspace-and-image-plane workspace? image-plane))
      ;; Make sure we have a workspace.
      ((null workspace?)
       (setq workspace? (workspace-on-image-plane? image-plane)))) ; changes arg

    ;; Bind the scales as implied by the arguments.
    (cond
      ;; fraction-of-image-width-or-height-to-have-within-pane? non-NIL means to
      ;; do a scale-to-fit operation. However, in the multiwindow UI, we prefer
      ;; to show a view at full scale with scroll bars, if possible, instead of
      ;; scaled-to-fit. We do that here, unless the user has *explicitly*
      ;; requested a scale-to-fit operation. NB: there is another pathway for
      ;; scale-to-fit operations, via compute-image-transformation-to-fit-in-pane.
      ;; -fmw, 6/17/04
      ((and (image-plane-will-be-scrollable-p image-plane)
	    (neq transform-image-operation-hint 'scale-to-fit)
	    fraction-of-image-width-or-height-to-have-within-pane?)
       (setq image-x-scale (default-x-scale gensym-window)
	     image-y-scale (default-y-scale gensym-window)))

      (fraction-of-image-width-or-height-to-have-within-pane?
       (let ((native-window? (image-plane-native-window? image-plane)))
	 (multiple-value-setq (image-x-scale image-y-scale)
	   (cond ((scale-to-fit-in-view-window-p image-plane)
		  (compute-scale-to-fit
		    workspace? image-plane gensym-window
		    (native-window-left native-window?)
		    (native-window-top native-window?)
		    (native-window-right-without-scrollbars gensym-window native-window?)
		    (native-window-bottom-without-scrollbars gensym-window native-window?)
		    (if (minusp fraction-of-image-width-or-height-to-have-within-pane?)
			#.(- (convert-to-magnification-at-compile-time 1.0))
			#.(convert-to-magnification-at-compile-time 1.0))
		    minimum-scale maximum-scale 0))
		 (t
		  (compute-scale-to-fit
		    workspace? image-plane gensym-window
		    left-edge-of-pane-in-window
		    top-edge-of-pane-in-window
		    right-edge-of-pane-in-window
		    bottom-edge-of-pane-in-window
		    fraction-of-image-width-or-height-to-have-within-pane?
		    minimum-scale maximum-scale))))))

      (left-edge-for-image?
       (with-temporary-gensym-float-creation transform-image
	 (setq image-x-scale
	   (round 
	     (max
	       minimum-scale
	       (* (normalized-scale)
		  (/ (-r right-edge-for-image? left-edge-for-image?)
		     (coerce-to-gensym-float (width-of-block workspace?)))))))
	 (setq image-y-scale
	   (round 
	     (max
	       minimum-scale
	       (* (normalized-scale)
		  (/ (-r bottom-edge-for-image? top-edge-for-image?)
		     (coerce-to-gensym-float (height-of-block workspace?)))))))))
      (t (setq image-x-scale
	       (or (if new-image-x-scale? (round new-image-x-scale?))
		   (image-x-scale image-plane)))
	 (setq image-y-scale
	       (or (if new-image-y-scale? (round new-image-y-scale?))
		   (image-y-scale image-plane)))))

    ;; Pin the scale in the range legal in this window.
    (multiple-value-setq (image-x-scale image-y-scale)
      (pin-image-scale-in-range image-x-scale image-y-scale minimum-scale maximum-scale))

    (multiple-value-setq (image-x-scale image-y-scale)
      (pin-image-plane-scale-to-avoid-overflow
	workspace? image-plane gensym-window
	minimum-scale maximum-scale
	image-x-scale image-y-scale))

    ;; Store the new scales, notice if we need to refresh.
    (unless (eql (image-x-scale image-plane)
		 (setf (image-x-scale image-plane) image-x-scale))
      (setq image-needs-refreshing? t))
    (unless (eql (image-y-scale image-plane)
		 (setf (image-y-scale image-plane) image-y-scale))
      (setq image-needs-refreshing? t))

    ;; Compute the X position of the image-plane
    (cond
      ((or x-in-workspace? block-to-position-on?)
       (unless (eq (x-origin-of-workspace-in-window-of-image-plane
		     image-plane)
		   (setf (x-origin-of-workspace-in-window-of-image-plane
			   image-plane)
			 (-r (or x-in-window?
				 (halfr (+r left-edge-of-pane-in-window
					    right-edge-of-pane-in-window)))
			     (delta-x-in-window
			       (or
				 x-in-workspace?
				 (halfw
				   (+w
				     (left-edge-of-block
				       block-to-position-on?)
				     (right-edge-of-block
				       block-to-position-on?))))
			       image-x-scale))))
	 (setq image-needs-refreshing? t)))
      ((null old-workspace?)
       (setf (x-origin-of-workspace-in-window-of-image-plane image-plane)
	     (halfr (+r left-edge-of-pane-in-window
			right-edge-of-pane-in-window)))))
    ;; Compute the Y position of the image-plane
    (cond
      ((or y-in-workspace? block-to-position-on?)
       (unless (eq (y-origin-of-workspace-in-window-of-image-plane
		     image-plane)
		   (setf (y-origin-of-workspace-in-window-of-image-plane
			   image-plane)
			 (-r (or y-in-window?
				 (halfr (+r top-edge-of-pane-in-window
					    bottom-edge-of-pane-in-window)))
			     (delta-y-in-window
			       (or y-in-workspace?
				   (halfw
				     (+w (top-edge-of-block
					   block-to-position-on?)
					 (bottom-edge-of-block
					   block-to-position-on?))))
			       image-y-scale))))
	 (setq image-needs-refreshing? t)))
      ((null old-workspace?)
       (setf (y-origin-of-workspace-in-window-of-image-plane image-plane)
	     (halfr (+r top-edge-of-pane-in-window
			bottom-edge-of-pane-in-window)))))

    (set-up-edges-for-image-plane image-plane)

    ;; Refresh the image-plane, oh and also move it's layer if desired.
    (cond ((native-windows-p gensym-window)
	   (unless (eq native-image-plane-updated-by-client image-plane)
	     ;; RESCALE here is one way of saying that G2 is doing a full
	     ;; refresh, so client-side refresh events are not needed.
	     (synchronize-native-window-with-image-plane
	       gensym-window workspace? image-plane (if image-needs-refreshing? 'rescale)
               ;; Added by SoftServe
               modal size-x size-y pos-x pos-y)
	     (when raise-image-plane-to-top?
	       (raise-image-plane-to-top image-plane t)
	       ;; Only when asked to raise to top, also restore if minimized.
	       ;; The logic here is that if the KB did not request a
	       ;; lift-to-top, for example, if it did a show preserving
	       ;; workspace layering, then it is not insisting that the
	       ;; workspace actually become visible, but rather just wants to
	       ;; change the current scaling, or whatever. If the user has
	       ;; chosen to bury or minimize the workspace, then G2 should leave
	       ;; that aspect alone. -fmw, 8/19/04
	       (when (minimized-image-plane-p image-plane)
		 (show-native-window (image-plane-native-window? image-plane)
				     sw-restore)
		 (unless (window-supports-scroll-while-minimized-fix gensym-window)
		   (update-native-scroll-bars image-plane))))
	     (when image-needs-refreshing?
	       (invalidate-image-plane image-plane))))
	  (t
	   (refresh-transformed-image-as-necessary
	     image-plane image-needs-refreshing?
	     raise-image-plane-to-top? tail-of-stack-to-start-projection-past?
	     old-left-edge-of-image-within-pane old-top-edge-of-image-within-pane
	     old-right-edge-of-image-within-pane old-bottom-edge-of-image-within-pane)))

    ;; Trigger a showing event if this is the first time it started showing.
    (when workspace?
      (unless (can-trigger-showing-p gensym-window)
	(let ((workspace?-is-now-showing
		(and (workspace-showing-p workspace? nil)
		     t)))
	  (unless (eq workspace?-is-now-showing
                          workspace?-was-initially-showing)
	    (event-update-status-of-block-showing
	      workspace? image-plane workspace?-is-now-showing))))))
  nil)

(defun-simple can-trigger-showing-p (gensym-window)
  (declare (ignore gensym-window))
  (printing-p))
  
;; Added event-update-status-of-block-showing logic. - ben 10/25/91

;; Changed spec for fraction-of-image-width-or-height-to-have-within-pane? so
;; that it doesn't make the scale larger than normalized scale.  It now reads
;; "... subject to the constraints that ... that neither the x nor y scale can
;; be larger than the NORMALIZED scale for the window.", where NORMALIZED used
;; to be MAXIMUM.  All callers that I have written, which is most of them,
;; depended on that being the behavior, which it always was in practice, since
;; normalized scale = maximum scale in all versions of products so far.
;; (MHD 8/7/90)
;;
;; --- Update -- obsolete comment.  (MHD 3/14/94)

;; Added new (optional) arguments left-edge-for-image?, top-edge-for-image?,
;; right-edge-for-image?, and bottom-edge-for-image?. (MHD 10/18/88)  The
;; computation should be done outside and passed in as new scale arguments!

;; Transform-image endeavors never to refresh the image if doesn't have to.
;; I.e.  the scale and window position do not change, refreshing need not be
;; done.

;; Consider having, optionally, the x and y normalizations of scale be computed
;; independently.

;; Note A: If we are creating a new native-window, then TW will send us the
;; needed refresh events, so we will get a double refresh. However, there are
;; times when we want to get the drawing out ASAP, before a refresh has a chance
;; to arrive (eg, the classic file progress display). So something more
;; sophisticated is needed here to prevent double refreshes.  -fmw, 11/26/03


;;; The function `pin-image-scale-in-range' adjusts the image scales to
;;; be in given ranges.  Does NOT handle overflow.

(defun pin-image-scale-in-range
    (image-x-scale image-y-scale minimum-scale maximum-scale)
  (cond ((<f image-x-scale minimum-scale)
	 (cond ((=f image-y-scale image-x-scale)
		;; This clause is especially needed when
		;; image-y-scale = image-x-scale = 0 to prevent a 0.0/0.0
		;; in scale-scale.  See e.g. Bug HQ-4459208 "Application
		;;  error in G2 showing hidden attributes for large array".
		;; - jpg 1/8/03
		(setq image-x-scale minimum-scale)
		(setq image-y-scale minimum-scale))
	       ((<f image-y-scale image-x-scale)
		(setq image-x-scale
		      (minf (scale-scale minimum-scale image-x-scale image-y-scale)
			    maximum-scale))
		(setq image-y-scale minimum-scale))
	       (t (setq image-y-scale
			(minf (scale-scale minimum-scale image-y-scale image-x-scale)
			      maximum-scale))
		  (setq image-x-scale minimum-scale))))
	((<f image-y-scale minimum-scale)
	 (setq image-x-scale
	       (minf (scale-scale minimum-scale image-x-scale image-y-scale)
		     maximum-scale))
	 (setq image-y-scale minimum-scale))

	((>f image-x-scale maximum-scale)
	 (cond ((>f image-y-scale image-x-scale)
		(setq image-x-scale
		      (maxf (scale-scale maximum-scale image-x-scale image-y-scale)
			    minimum-scale))
		(setq image-y-scale maximum-scale))
	       (t (setq image-y-scale
			(maxf (scale-scale maximum-scale image-y-scale image-x-scale)
			      minimum-scale))
		  (setq image-x-scale maximum-scale))))
	((>f image-y-scale maximum-scale)
	 (setq image-x-scale
	       (maxf (scale-scale maximum-scale image-x-scale image-y-scale)
		     minimum-scale))
	 (setq image-y-scale maximum-scale)))
  (values image-x-scale image-y-scale))





;;; `Move-image-plane' changes the XY position of an image-plane in the pane,
;;; without changing its layer position.

;;; This function does NOT enforce image-plane visibility.  Usually, the caller
;;; invokes require-that-image-plane-be-visible immediately after moving.

(defun move-image-plane (image-plane delta-x-in-window delta-y-in-window)
  (unless (=f 0 delta-x-in-window delta-y-in-window)
    (do-image-planes-in-group (ip image-plane)
      (move-image-plane-1 ip delta-x-in-window delta-y-in-window))))


;;; The function `move-image-plane-1' moves the given image-plane, ignoring any
;;; inter-plane couplings.

(defun-allowing-unwind move-image-plane-1
    (image-plane delta-x-in-window delta-y-in-window)
  (assert-that-not-within-named-dynamic-extent 'on-window)

  ;; For some reason the call to drain-current-window-drawing-queue [*] doesn't
  ;; work reliably when using this routine to scroll a native-image-plane. The
  ;; symptom is that an ICP drawing message is sent by G2 but never received by
  ;; TW! Some sort of ICP/drawing context problem I don't understand. In any
  ;; case, forcing window drawing here, outside the various on-window macro's,
  ;; does work. -fmw, 1/9/04
  (when (eq native-window-client-operation 'scroll) ; FIXME
    (force-window-drawing (gensym-window-for-image-plane image-plane)))

  ;; Must open cursors around the entire update.
  (with-raw-window-transform-and-draw-area
      ((gensym-window-for-image-plane image-plane))
    (with-nested-draw-area-of-pane? (image-plane)

      (on-window-without-drawing ((gensym-window-for-image-plane image-plane))
	(on-window-with-drawing (current-window)

	  ;; Must bring the screen up-to-date before we can scroll regions,
	  ;; and, before we start messing with image-plane edges.
	  (drain-current-window-drawing-queue)                   ; [*]

	  ;; Update the cached position of the native-window (if any) here,
	  ;; *after* draining the drawing queue and *before* we go
	  ;; on-image-plane.
	  (when (eq native-image-plane-updated-by-client image-plane)
	    (cond ((eq native-window-client-operation 'scroll))
		  (t
		   (%move-native-window-by (image-plane-native-window? image-plane)
					   delta-x-in-window
					   delta-y-in-window)
		   (recompute-visible-region-of-native-image-plane image-plane))))

	  (let ((dirty-region? nil))
	    ;; Open cursors before bitblting.
	    (for-image-plane (image-plane) ; FIXME: This goes on-native-window,
					   ; which causes unnecessary network
					   ; traffic if there are no image-plane
					   ; cursors.
	      (with-nested-image-plane-interior-draw-area (image-plane)
		(with-open-cursors (left-edge-of-draw-area
				     top-edge-of-draw-area
				     right-edge-of-draw-area
				     bottom-edge-of-draw-area
				     ;; Don't open image-plane cursors if native.
				     :image-plane-cursors (not current-native-image-plane))

		  (setq dirty-region?
			(move-image-plane-2 image-plane
					    delta-x-in-window
					    delta-y-in-window))

		  ;; Here we see reason #69 why dynamic contexts are evil: they
		  ;; cache.  The current draw area is supposed to be the
		  ;; interior of the image-plane, which unfortunately we've
		  ;; just moved.  So we have to explicitly remember to update
		  ;; the cache. -fmw, 7/26/95

		  ;; NOTE: We would also need to reset native-image-plane
		  ;; offsets here, if we actually did any drawing before leaving
		  ;; for-image-plane. -fmw, 12/29/03
		  (set-draw-area-from-image-plane-interior image-plane))))

	    (when dirty-region?
	      (invalidate-region-of-window-when-on-window dirty-region?)
	      (reclaim-region dirty-region?))))))))



;;; The function `move-image-plane-2' updates the image-plane edges and the
;;; screen bits as much as possible using scroll-window.  It returns the newly
;;; exposed region to refresh, so that the region can be invalidated outside of
;;; the for-image-plane context, above.

(defvar old-exposed-region)

(defun move-image-plane-2 (image-plane
			    delta-x-in-window
			    delta-y-in-window)
  (assert-that-within-named-dynamic-extent 'for-image-plane)
  (protected-let*-for-development
      ((old-exposed-region (copy-region
			     (visible-region-of-image-plane image-plane))
			   (reclaim-region old-exposed-region)))

    ;; Update image-plane edges.
    (incfr (x-origin-of-workspace-in-window-of-image-plane
	     image-plane) delta-x-in-window)
    (incfr (y-origin-of-workspace-in-window-of-image-plane
	     image-plane) delta-y-in-window)

    #+development
    (when trace-image-planes-p
      (format t "moving ~s at (~s ~s ~s ~s) by ~s ~s~%"
	      image-plane
	      (left-edge-of-image-in-window   image-plane)
	      (top-edge-of-image-in-window    image-plane)
	      (right-edge-of-image-in-window  image-plane)
	      (bottom-edge-of-image-in-window image-plane)
	      delta-x-in-window
	      delta-y-in-window))

    (incfr (left-edge-of-image-in-window    image-plane) delta-x-in-window)
    (incfr (top-edge-of-image-in-window     image-plane) delta-y-in-window)
    (incfr (right-edge-of-image-in-window   image-plane) delta-x-in-window)
    (incfr (bottom-edge-of-image-in-window  image-plane) delta-y-in-window)

    (incfr (left-edge-of-workspace-area-in-window   image-plane)
	   delta-x-in-window)
    (incfr (top-edge-of-workspace-area-in-window    image-plane)
	   delta-y-in-window)
    (incfr (right-edge-of-workspace-area-in-window  image-plane)
	   delta-x-in-window)
    (incfr (bottom-edge-of-workspace-area-in-window image-plane)
	   delta-y-in-window)

    ;; Update visible region.
    (recompute-visible-regions-for-pane (pane-for-image-plane image-plane))
    (set-up-loose-edges-for-workspace-area-within-pane image-plane)

    (cond ((eq native-window-client-operation 'scroll)
	   (scroll-native-image-plane image-plane delta-x-in-window delta-y-in-window t))
	  ((image-plane-native-window? image-plane)
	   (unless (eq native-image-plane-updated-by-client image-plane)
             (move-native-window-by
               (image-plane-native-window? image-plane)
               delta-x-in-window delta-y-in-window)
             (recompute-visible-region-of-native-image-plane image-plane))
	   nil)
	  ;; classic image planes
	  (t
	   (move-image-plane-3 image-plane delta-x-in-window delta-y-in-window)))))

;; `move-image-plane-3` was the last part of `move-image-plane-2' for scrolling of
;; classic image planes, now it's called by `move-image-plane-2' for several different
;; cases when scrolling a native image plane.

(defun move-image-plane-3 (image-plane delta-x-in-window delta-y-in-window)
  (protected-let*-for-development
      ((destination-region
	(visible-region-of-image-plane image-plane))
       (offset-destination-region
	(shift-region (copy-region destination-region)
		      (-r delta-x-in-window) (-r delta-y-in-window))
	(reclaim-region offset-destination-region))
       (useful-source-region
	(intersect-region old-exposed-region offset-destination-region)
	(reclaim-region useful-source-region)))

    ;; Update some screen bits
    (scroll-region-of-current-window
      useful-source-region
      delta-x-in-window delta-y-in-window)

    ;; Compute newly exposed region.
    (protected-let*-for-development
	((still-dirty-destination-region
	  (subtract-region destination-region
			   (shift-region useful-source-region
					 delta-x-in-window
					 delta-y-in-window))
	  (reclaim-region still-dirty-destination-region))
	 (now-dirty-source
	  (subtract-region old-exposed-region destination-region)
	  (reclaim-region now-dirty-source)))

      ;; Return the total dirty region.
      (union-region now-dirty-source still-dirty-destination-region))))


;;; `Scroll-region-of-current-window' will move the given region by the given
;;; offset in the current window.  If the scroll-rectangle operation is not
;;; supported in the current drawing footprint the destination region will be
;;; invalidated.  Note that in that scenario the drawing may happen in the
;;; recursive decent of this call (depending on the status of drawing priority)
;;; and so the image-planes must be configured as if the destination has
;;; already moved.

;;; In the usual scenario the caller must take care to fill those portions of
;;; the source that are vacated by this copy.  The copy may not be possible if
;;; the source is obscured in the host window system, in that case the expose
;;; events are generated by the drawing primtives.

;;; This routine, like all drawing primitives, must be called when
;;; on-window-with-drawing.

;; (ben 11/30/93)

;; Called by move-image-plane-2 and scroll-region-on-image-plane.

(defun-allowing-unwind scroll-region-of-current-window
    (region dx dy)
  (cond
    ((and (current-window-supports-this-icp-window-protocol-p
	    icp-window-protocol-supports-scrolling)
	  (not (native-windows-p current-window))) ; FIXME: Maybe this test belongs in caller.
     (do-region-rectangles ((left top right bottom) region
			    :reverse-horizontal-p (<f 0 dx)
			    :reverse-vertical-p (<f 0 dy))
       (scroll-rectangle-in-current-window
	 left top
	 (-f right left)
	 (-f bottom top)
	 (+f left dx)
	 (+f top dy))))
    (t
     (let ((destination-region (shift-region (copy-region region) dx dy)))
       (invalidate-region-of-window-when-on-window destination-region)
       (reclaim-region destination-region)))))



;;; `Scroll-content-area-of-image-plane' rebinds the portion of the workspace
;;; showing in the image-area.  It should not be used on an image-plane which is
;;; showing-entire-workspace-p.

;;; This sets:
;;;   *-edge-of-workspace-content-area-of-image-plane
;;; and it propogates the resulting change to
;;;    the loose-workspace-area
;;;    the origin of workspace in window (if necessary)
;;;    the image scale (if necessary)

;;; See the introduction to this section for details about invalidation
;;; and on-image-plane dynamic extent.

;;; This is used primarily to implement scrolling operations.

(defun scroll-content-area-of-image-plane
    (image-plane
     delta-x-of-content-area
     delta-y-of-content-area)
  (let ((delta-x-in-window
	 (delta-x-in-window delta-x-of-content-area
			    (image-y-scale image-plane)))
	(delta-y-in-window
	 (delta-y-in-window delta-y-of-content-area
			    (image-y-scale image-plane))))
    (unless (=f 0 delta-x-of-content-area)
      (incff (left-edge-of-content-area-of-image-plane image-plane)
	     delta-x-of-content-area)
      (incff (right-edge-of-content-area-of-image-plane image-plane)
	     delta-x-of-content-area)
      (incff (loose-left-edge-of-visible-workspace-area image-plane)
	     delta-x-of-content-area)
      (incff (loose-right-edge-of-visible-workspace-area image-plane)
	     delta-x-of-content-area)
      (incff (x-origin-of-workspace-in-window-of-image-plane image-plane)
	     delta-x-in-window))
    (unless (=f 0 delta-y-of-content-area)
      (incff (bottom-edge-of-content-area-of-image-plane image-plane)
	     delta-y-of-content-area)
      (incff (top-edge-of-content-area-of-image-plane image-plane)
	     delta-y-of-content-area)
      (incff (loose-top-edge-of-visible-workspace-area image-plane)
	     delta-y-of-content-area)
      (incff (loose-bottom-edge-of-visible-workspace-area image-plane)
	     delta-y-of-content-area)
      (incff (y-origin-of-workspace-in-window-of-image-plane image-plane)
	     delta-y-in-window))
    (invalidate-image-plane image-plane)))


;; scroll-region-of-current-window

;; Unused
(defun scroll-percentage-of-content-area-of-image-plane
    (image-plane x-percent y-percent)
  (scroll-content-area-of-image-plane
    image-plane
    (roundf
      (*f x-percent
	  (-w (right-edge-of-content-area-of-image-plane image-plane)
	      (left-edge-of-content-area-of-image-plane image-plane)))
      100)
    (roundf
      (*f y-percent
	  (-w (bottom-edge-of-content-area-of-image-plane image-plane)
		  (top-edge-of-content-area-of-image-plane image-plane)))
      100)))



;;; The function `refresh-transformed-image-as-necessary' is presently called
;;; only by transform-image.

(defun refresh-transformed-image-as-necessary
    (image-plane image-needs-refreshing? 
		 raise-image-plane-to-top? ; DOCUMENT!
		 tail-of-stack-to-start-projection-past? ; DOCUMENT!
		 old-left-edge-of-image-within-pane
		 old-top-edge-of-image-within-pane
		 old-right-edge-of-image-within-pane
		 old-bottom-edge-of-image-within-pane)
  ;; Rework the clipping region for this image-plane
  (recompute-visible-regions-for-pane (pane-for-image-plane image-plane))
  (let (;; Sometimes used to find the shortest tail of stack to
	;; start projection past if the image is being raised &
	;; needs refreshing (MHD 10/24/90)
	(original-position-of-image-plane? nil))

    ;; Percolate it to the top, if requested.
    (when raise-image-plane-to-top?
      (when image-needs-refreshing?
	(setq original-position-of-image-plane?
	      (loop for x in (stack-of-image-planes
			       (pane-for-image-plane image-plane))
		    until (eq x image-plane)
		    count t)))
      (raise-image-plane-to-top image-plane image-needs-refreshing?)
      (when (and image-needs-refreshing?
		 (not (=f original-position-of-image-plane? 0)))
	(loop for subplane?
		  = (subplane? image-plane)
		  then (subplane? subplane?)
	      while subplane?
	      do (setf old-left-edge-of-image-within-pane
		       (minr old-left-edge-of-image-within-pane
			     (left-edge-of-image-within-pane subplane?)))
		 (setf old-top-edge-of-image-within-pane
		       (minr old-top-edge-of-image-within-pane
			     (top-edge-of-image-within-pane subplane?)))
		 (setf old-right-edge-of-image-within-pane
		       (maxr old-right-edge-of-image-within-pane
			     (right-edge-of-image-within-pane subplane?))) 
		 (setf old-bottom-edge-of-image-within-pane
		       (maxr old-bottom-edge-of-image-within-pane
			     (bottom-edge-of-image-within-pane subplane?)))
		 (incff original-position-of-image-plane?))))

    ;; Rework the clipping region for this image-plane (again!)
    (recompute-visible-regions-for-pane (pane-for-image-plane image-plane))
    
    (when image-needs-refreshing?
      ;; This wrapper cures the double-refresh on ^S/^B -fmw, 1/28/95.
      (with-deferred-drawing-in-process ()
	(let* ((current-pane (pane-for-image-plane image-plane))
	       (stack-of-image-planes (stack-of-image-planes current-pane)))

	  ;; If the image-plane is brand-new, then this WHEN does not fire.
	  (when (rectangle-not-empty-p
		  old-left-edge-of-image-within-pane
		  old-top-edge-of-image-within-pane
		  old-right-edge-of-image-within-pane
		  old-bottom-edge-of-image-within-pane)
	    (invalidate-reordered-image-planes
	      (gensym-window-for-pane current-pane)
	      old-left-edge-of-image-within-pane
	      old-top-edge-of-image-within-pane
	      old-right-edge-of-image-within-pane
	      old-bottom-edge-of-image-within-pane
	      stack-of-image-planes nil
	      (or tail-of-stack-to-start-projection-past?
		  (if (and original-position-of-image-plane?
			   (null (subplane? image-plane))
			   (null (superplane? image-plane)))
		      (nthcdr
			original-position-of-image-plane?
			stack-of-image-planes)
		      (memq image-plane stack-of-image-planes)))
	      nil current-pane))

	  ;; Alternatively, do the refresh-image-plane ahead of the previous
	  ;; expression, which leaves an "after-image", but gets image-plane drawn
	  ;; first.

	  ;; If this is an alternative, then why was it being done in addition
	  ;; to the above?  Was causing double redraws upon shrinking or
	  ;; growing a workspace.  -fmw, 2/23/94
	  
	  (invalidate-image-plane image-plane))))))

;; If image-needs-refreshing? is false and raise-image-plane-to-top?,
;; raise-image- plane-to-top is used.  It only refreshes the previously
;; unexposed areas of the image and usually does so using graphic element
;; memory, which is faster to refresh than would be the case if
;; refresh-image-plane were used.  Refresh-image-plane, of course, does always
;; redraw the exposed areas of the entire image.  Note that some interfaces may
;; actually suffer from this feature.  For example, in an interface where the
;; user clicks a button to see a workspace pop up, if the workspace is already
;; where it should end up, then absolutely nothing will change on the screen,
;; leaving him with no indication that the button click has done anything.  For
;; one thing, some machines may be so fast that the refresh would not be noticed
;; anyway.  For another, having interfaces that depend unnecessary drawing is a
;; bad idea.  If that feature wanted to be supported, then there would want to
;; be a "refresh" action. (MHD 6/22/89)

;; MHD's NOTES (10/18/88)

;; Refreshing the image plane being transformed first, and then afterwards
;; "exposing" images and background underneath in some cases is most desirable
;; from the user standpoint. This will be the case when his attention is focused
;; on the image plane being transformed (e.g. when he moves it to bring it into
;; view). However, often he is interested in seeing what's underneath the image
;; plane first, (e.g. when he moves an image out of the way or shrinks it down
;; very small to expose what's underneath).  A good answer (for transform-image)
;; might be to offer both options, and let higher level software be responsible
;; for determining the best order.

;; If refreshing of the image plane being transformed is done first (it is not
;; at present), a secondary disadvantage is that if updates happen slowly
;; enough, you see transiently on the screen both the unoccluded parts of old
;; image and the new image at the same time.  This causes an "after-image" to be
;; visible to the user.

;; A hybrid approach (evidently employed by the Macintosh) is to first paint the
;; background of the screen and the borders and background of the images below,
;; then refresh the image plane being transformed, then to go back and finish
;; drawing the details of the images below.  This gives the user an instant
;; glimpse of the general layout of the background, without the need to sit
;; through the filling in of details, which, presumably, the user is happy to
;; see deferred until after the image being transformed is completely refreshed.
;; This approach suffers from an efficiency standpoint, in that it requires two
;; passes over the stack of image planes to compute the occlusion of each plane
;; to complete making the screen consistent.  It also suffers in terms of the
;; "flash principle", since it it may subject users to two (as opposed to one)
;; burst of graphics in the occluded areas exposed by the image transformation.

;; These issues and any proposed changes need further analysis and
;; experimentation.




;;; `Set-up-edges-for-image-plane' recalculates the values of the
;;; edge-of-image-in-window and edge-of-workspace-area-in-window slots of
;;; image-plane, based upon the values of other slots of image-plane.
;;;    block -copy-> content-area-of-image-plane
;;;    content-area-of-image-plane -scale-> workspace-area-in-window
;;;    loose-edges
;;;    workspace-area-in-window + frame --> edge-of-image-in-window

(defun set-up-edges-for-image-plane (image-plane)
  (let ((workspace (workspace-on-image-plane? image-plane)))
    (with-image-plane-transform (image-plane)

      ;; Content area = workspace area - workspace margins.
      (with-code-matching-pattern
	  ((<left> left top right bottom))
	(setf (<left>-edge-of-content-area-of-image-plane image-plane)
	      (<left>-edge-of-block workspace))
	-->
	(setf (left-edge-of-content-area-of-image-plane image-plane)
	      (left-edge-of-block workspace))
	(setf (top-edge-of-content-area-of-image-plane image-plane)
	      (top-edge-of-block workspace))
	(setf (right-edge-of-content-area-of-image-plane image-plane)
	      (right-edge-of-block workspace))
	(setf (bottom-edge-of-content-area-of-image-plane image-plane)
	      (bottom-edge-of-block workspace)))

      ;; Workspace area = image-plane minus the frame (borders, etc).
      (with-code-matching-pattern
	  ((<left> left top right bottom)
	   (<x> x y))
	(setf (<left>-edge-of-workspace-area-in-window image-plane)
	      (<x>-in-window
		(<left>-edge-of-content-area-of-image-plane image-plane)))
	-->
	(setf (left-edge-of-workspace-area-in-window image-plane)
	      (x-in-window
		(left-edge-of-content-area-of-image-plane image-plane)))
	(setf (top-edge-of-workspace-area-in-window image-plane)
	      (y-in-window
		(top-edge-of-content-area-of-image-plane image-plane)))
	(setf (right-edge-of-workspace-area-in-window image-plane)
	      (x-in-window
		(right-edge-of-content-area-of-image-plane image-plane)))
	(setf (bottom-edge-of-workspace-area-in-window image-plane)
	      (y-in-window
		(bottom-edge-of-content-area-of-image-plane image-plane))))

      (when new-g2-classic-ui-p
	;; expand the workspace area to the right, if necessary, to fit in the
	;; title bar, including its text and its widgets, e.g., the close box.
	;; Needs to have some hardcoding reworked.... Review! (MHD 9/23/99)
	(when (stretch-new-image-planes-for-caption-p workspace)
	  (let ((text? (title-bar-caption-text workspace)))
	    (when text?
	      (setf (right-edge-of-workspace-area-in-window image-plane)
		    (maxr (right-edge-of-workspace-area-in-window image-plane)
			  (+r (left-edge-of-workspace-area-in-window image-plane)
			      (get-total-title-bar-text-width text?)
			      4 7		; left/right padding
			      24)))))))	; room for close box

      ;; The loose-edges
      (set-up-loose-edges-for-workspace-area-within-pane image-plane)

      ;; The image-area, which is the outermost rectangle covered by
      ;; the image plane, in window coordinates.  It's the workspace area
      ;; outdented by the frame width on each side.  NOT clipped by the pane.
      (let ((frame-description-reference
	      (frame-description-reference-of-image-plane image-plane)))

	#+development
	(when trace-image-planes-p
	  (format t "resetting edges on ~s~%" image-plane))

	(with-code-matching-pattern ((<left> left top right bottom)
				     (<-r> -r -r +r +r))
	  (setf (<left>-edge-of-image-in-window image-plane)
		(<-r> (<left>-edge-of-workspace-area-in-window image-plane)
		      (<left>-frame-indent frame-description-reference)))
	  -->
	  (setf (left-edge-of-image-in-window image-plane)
		(-r (left-edge-of-workspace-area-in-window image-plane)
		    (left-frame-indent frame-description-reference)))
	  (setf (top-edge-of-image-in-window image-plane)
		(-r (top-edge-of-workspace-area-in-window image-plane)
		    (top-frame-indent frame-description-reference)))
	  (setf (right-edge-of-image-in-window image-plane)
		(+r (right-edge-of-workspace-area-in-window image-plane)
		    (right-frame-indent frame-description-reference)))
	  (setf (bottom-edge-of-image-in-window image-plane)
		(+r (bottom-edge-of-workspace-area-in-window image-plane)
		    (bottom-frame-indent frame-description-reference))))))))




;;; The function `compute-interior-region-of-image-plane' returns a region
;;; convering the interior of the image-plane, which is the total image-plane
;;; minus the frame.  In WORKSPACE coordinates. The region is NEWLY CONSED.

(defun compute-interior-region-of-image-plane (image-plane)
  (make-region-from-rectangle
    (left-edge-of-workspace-area-in-window image-plane)
    (top-edge-of-workspace-area-in-window image-plane)
    (right-edge-of-workspace-area-in-window image-plane)
    (bottom-edge-of-workspace-area-in-window image-plane)))








;;; `Pin-image-plane-scale-to-avoid-overflow' is called by transform-image after
;;; deciding a desired scale, and before putting up any image plane.  It pins
;;; the scale in order avoid overflow of the limits of the raster (window)
;;; coordinate system; the limits imposed on workspace coordinates should do
;;; this in most cases, but there's been some leakage (lack of imposition) and
;;; some grandfathering of violations that got in through laxer or non-existant
;;; limits.  In effect, can be scaled to have a size in window coordinates no
;;; larger than a workspace larger than the largest workspace at the maximum
;;; scale, reducing the scale to reduce its ultimate size.

(defun pin-image-plane-scale-to-avoid-overflow
    (workspace? image-plane gensym-window
		minimum-scale maximum-scale
		image-x-scale image-y-scale)
  (when (or
	  ;; t ; for testing
	  ;;
	  ;; note: this whole test is an optimization; it should work the same
	  ;; without it; test by uncommenting the above T clause.
	  (<w (left-edge-of-block workspace?) most-negative-workspace-coordinate)
	  (<w (top-edge-of-block workspace?) most-negative-workspace-coordinate)
	  (>w (right-edge-of-block workspace?) most-positive-workspace-coordinate)
	  (>w (bottom-edge-of-block workspace?) most-positive-workspace-coordinate))
    (multiple-value-bind (maximum-image-x-scale maximum-image-y-scale)
	(compute-scale-to-fit
	  workspace? image-plane gensym-window
	  ;; same as (delta-x/y-in-window coord. (normalized-scale)):
	  (delta-x-in-window most-negative-workspace-coordinate maximum-scale)
	  (delta-y-in-window most-negative-workspace-coordinate maximum-scale)
	  (delta-x-in-window most-positive-workspace-coordinate maximum-scale)
	  (delta-y-in-window most-positive-workspace-coordinate maximum-scale)
	  #.(convert-to-magnification-at-compile-time 1.0)
	  minimum-scale
	  (minw maximum-scale (maxw image-x-scale image-y-scale)))
      (when (or (<f maximum-image-x-scale image-x-scale)
		(<f maximum-image-y-scale image-y-scale))
	(setq image-x-scale maximum-image-x-scale)
	(setq image-y-scale maximum-image-y-scale))))
  (values image-x-scale image-y-scale))

;; (MHD 5/10/95)





;;; `Compute-scale-to-fit' returns two values, maximum-x-scale and
;;; maximum-y-scale, such that scale won't be greater than maximum-scale, or
;;; less than minimum-scale.  The four edge arguments specify a rectangle into
;;; which image plane must fit at the returned scale.
;;;
;;; If called with a desired scale as maximum-scale, then this limits the scale
;;; to that desired scale, and makes it smaller only if necessary to shrink.
;;; Thus, this can be used to restrict the scale so that the image plane won't
;;; exceed the specified rectangle.
;;;
;;; Limitation: unfortunately, this does not take independent minimum and maximum
;;; scales independent in x and y.  Therefore, the result has to be checked against
;;; a desired scale to see if it's different.  Otherwise, it would impose equal
;;; x/y scaling.

(defun compute-scale-to-fit
    (workspace image-plane gensym-window
	       left-edge top-edge
	       right-edge bottom-edge
	       fraction-of-image-width-or-height-to-have-within-rectangle
	       minimum-scale maximum-scale &optional margin?)
  (let ((frame-description-reference
	  (frame-description-reference-of-image-plane image-plane)))

    (compute-scale-to-fit-rectangle
      gensym-window
      (width-of-block workspace)
      (height-of-block workspace)
      (or margin? (+f (left-frame-indent frame-description-reference)
		      (right-frame-indent frame-description-reference)))
      (or margin? (+f (top-frame-indent frame-description-reference)
		      (bottom-frame-indent frame-description-reference)))
      left-edge top-edge
      right-edge bottom-edge
      fraction-of-image-width-or-height-to-have-within-rectangle
      minimum-scale maximum-scale)))



;;; The function `compute-scale-to-fit-rectangle' computes x and y scales so
;;; that a rectangle of the given image width and height, with the given
;;; margins in window coordinates, will fit in the other rectangle, with some
;;; fraction of slop.

(defun compute-scale-to-fit-rectangle
    (gensym-window
      image-width image-height image-x-margin image-y-margin
      left-edge top-edge
      right-edge bottom-edge
      fraction-of-image-width-or-height-to-have-within-rectangle
      minimum-scale maximum-scale)
  (with-temporary-gensym-float-creation compute-scale-to-fit
    (let* ((default-x-scale
	       (default-x-scale gensym-window))
	   (default-y-scale
	       (default-y-scale gensym-window))
	   (blow-up?
	     (if (minusp fraction-of-image-width-or-height-to-have-within-rectangle)
		 (with-temporary-gensym-float-creation transform-image
		   (setq fraction-of-image-width-or-height-to-have-within-rectangle
			 (- fraction-of-image-width-or-height-to-have-within-rectangle))
		   t)))
	   (unrounded-image-x-scale
	     (max
	       minimum-scale
	       ;; changed to min of 2 args for Chestnut/SGI bug 
	       ;; (MHD 10/2/92)
	       (min
		 (min
		   (* (normalized-scale)
		      (/
			(- (inverse-magnify
			     (-r right-edge
				 left-edge)
			     fraction-of-image-width-or-height-to-have-within-rectangle)
			   image-x-margin)
			(coerce-to-gensym-float
			  image-width)))
		   (/ (*
			default-x-scale
			(*
			  (normalized-scale)
			  (/
			    (-
			      (inverse-magnify
				(-r bottom-edge
				    top-edge)
				fraction-of-image-width-or-height-to-have-within-rectangle)
			      image-y-margin)
			    (coerce-to-gensym-float
			      image-height))))
		      default-y-scale))
		 (if blow-up?
		     maximum-scale
		     (maxf default-x-scale default-y-scale)
		     ;; (normalized-scale) ; Added. (MHD 8/7/90) ; removed (MHD
		     ;; 3/14/94)
		     )))))	; Added. (MHD 8/7/90)
      (values
	(round unrounded-image-x-scale)
	(round (/ (* default-y-scale unrounded-image-x-scale)
		  (coerce-to-gensym-float default-x-scale)))))))



;;;; Quick Clipping




;;; `Quick clipping' is used to see if any portion of an workspace element we
;;; are about to draw could possibly be visible in the image-plane we are
;;; drawing to.

;;; The quick-clipping rectangle is maintained in workspace coordinates
;;; an element that lies entirely outside of it is surely outside of any
;;; exposed region of that workspace.

;;; For assorted reasons this rectangle usually larger than necessary.
;;; Fundimentally this will always be true because of bleeding and scaling, but
;;; it is also true also because the macro with-nested-draw-area? refocuses in
;;; the draw area do not in these edges.

;;; Globals holding this rectangle are established when ever the on-image-plane
;;; dynamic extent is established, and these values are cached in the
;;; image-plane data structure.

;;; This can not be used to preempt KB updating since that must draw thru to
;;; all image-planes, and this information is good only for one image-plane.
;;; See showing-p for help with that.

(def-concept quick-clipping)



;;; `Set-up-loose-edges-for-workspace-area-within-pane' is called to recompute
;;; the rectangle used in quick clipping.

;;; This works by taking the edge-of-workspace-area-in-window rectangle in
;;; mapping it back into workspace coordinates, plus some slop to guard against
;;; scalling and bleeding problems.

;;; This is called when ever the transform between the workspace and the window
;;; is changed.  Even if the image-plane is just offset.

(defun set-up-loose-edges-for-workspace-area-within-pane (image-plane)
  (with-image-plane-transform (image-plane)
    (with-code-matching-pattern ((<left> left top right bottom)
				 (<x> x y)
				 (<-indentr> -r -r +r +r)
				 (<-indentw> -w -w +w +w))
      (setf (loose-<left>-edge-of-visible-workspace-area image-plane)
	    (<-indentw>
	      (<x>-in-workspace
		(<-indentr>
		  (<left>-edge-of-workspace-area-in-window image-plane)
		  5)) ;; but nobody knows why.
	      1))
      -->
      (setf (loose-left-edge-of-visible-workspace-area image-plane)
	    (-w (x-in-workspace
		  (-r (left-edge-of-workspace-area-in-window image-plane) 5))
		1))
      (setf (loose-top-edge-of-visible-workspace-area image-plane)
	    (-w (y-in-workspace
		  (-r (top-edge-of-workspace-area-in-window image-plane) 5))
		1))
      (setf (loose-right-edge-of-visible-workspace-area image-plane)
	    (+w (x-in-workspace
		  (+r (right-edge-of-workspace-area-in-window image-plane) 5))
		1))
      (setf (loose-bottom-edge-of-visible-workspace-area image-plane)
	    (+w (y-in-workspace
		  (+r (bottom-edge-of-workspace-area-in-window image-plane) 5))
		1)))))

;; Shouldn't the extra-pixels-for-quick-clipping have only enough to
;; manage the bleeding that happens at the current scale? - ben 12/7/93



;;; The macro `maybe-within-image-plane-p' provides a simple way to test a
;;; rectangle for possible exposure, and direct access to the on-image-plane
;;; varaibles (loose-left-edge-of-visible-workspace-area etc.) is also
;;; approprate.

;;; Note that this macro may not evaluate all of its arguments.

#+unused
(defmacro maybe-within-image-plane-p
	  (left-edge-in-workspace top-edge-in-workspace
	   right-edge-in-workspace bottom-edge-in-workspace)
  `(not
     (or
       (>w ,left-edge-in-workspace loose-right-edge-of-visible-workspace-area)
       (>w ,top-edge-in-workspace loose-bottom-edge-of-visible-workspace-area)
       (<w ,right-edge-in-workspace loose-left-edge-of-visible-workspace-area)
       (<w ,bottom-edge-in-workspace loose-top-edge-of-visible-workspace-area)
       )))







;;;; Updating All Images of a Workspace Element



;;; `Updating' is the process of revising the image of a block on one or all of
;;; the image-planes currently displaying that block.  This process may be
;;; scheduled.  Multiple requests to do similar updates may be merged into a
;;; single actual screen update.

;;; Each kind of updating is declared via the form `def-component-update'
;;; defined below.  This generates one routine to enqueue updates, and another
;;; to implement the update.  The first is invoked when ever an update is noted
;;; in the KB, and the second is then invoked zero or more of times to implement
;;; the update.  The first routine schedules an update, the second implements
;;; the update.

;;; The update routine maybe invoked many times.  Once for each image-plane that
;;; needs to be updated.  When we are using an XOR transfer mode then it will be
;;; invoked once to `subtract' the component, and once to add it back.  When we
;;; are using an XOR transfer mode, but only changing the color of a component
;;; the component-update routine can be called only once.

;; None of the above is implemented.



;;; `Rectangle-visible-p' is true if the rectangle for block is visible on any
;;; image plane anywhere.  This predicate is coded for speed, for the sake of
;;; display update tasks.

;;; If the rectangle for block is not visible and if the drawing of block is
;;; confined entirely to that rectangle, then images of block need not be
;;; "updated" when block is about to be or has just been changed.  (Note that
;;; the drawing of an icon is NOT usually confined to its rectangle.)

(defun rectangle-visible-p (block)
  (let* ((superblock?
	   (superblock? block))
	 (supreme-block
	   (cond
	     ((null superblock?) block)
	     ((null (superblock? superblock?)) superblock?)
	     (t (loop do (setq superblock? (superblock? superblock?))
		      until (null (superblock? superblock?))
		      finally
			(return superblock?))))))
    (and (workspace-p supreme-block)
	 (loop for image-plane in (image-planes-this-is-on supreme-block)
	       thereis
	       ;; adapted from maybe-within-pane-p
	       (not
		 (or
		   (>w (left-edge-of-block block)
		       (loose-right-edge-of-visible-workspace-area image-plane))
		   (>w (top-edge-of-block block)
		       (loose-bottom-edge-of-visible-workspace-area image-plane))
		   (<w (right-edge-of-block block)
		       (loose-left-edge-of-visible-workspace-area image-plane))
		   (<w (bottom-edge-of-block block)
		       (loose-top-edge-of-visible-workspace-area image-plane)))))
	 ;; and not completely obscured by another image plane (additional
	 ;; optimization)?  NO, because it still needs to be in graphic element
	 ;; memory in that case (LH) UNLESS it is a stack subblock!
	 )))

;; If this were not coded for speed, it could use get-workspace-if-any.



;;; The function `transform-region-to-window-coordinates' NON-destructively
;;; transforms the given region, from workspace coordinates to the window
;;; coordinates corresponding to the current image plane, as well as clipping
;;; the region to the visible region of the image-plane.  The current drawing
;;; transform must be set.

(defun transform-region-to-window-coordinates (region bleeding-hack)
  (with-workspace-to-window-transform (bleeding-hack)
    (transform-region-macro region transform)))

;; As a result of the clipping, the returned region could be empty, for
;; example.



;;; The function `transform-region-to-workspace-coordinates' transforms the
;;; given region from window coordinates, for the current window, to workspace
;;; coordinates, for the current image-plane.  The returned region is newly
;;; consed, sharing no structure with the argument.

(defun transform-region-to-workspace-coordinates (region)
  (macrolet ((transform (left top right bottom)
	       `(let ((left* (x-in-workspace ,left))
		      (top* (y-in-workspace ,top))
		      (right* (x-in-workspace ,right))
		      (bottom* (y-in-workspace ,bottom)))
		  ;; Ensure the result region is non-empty iff the source region is.
		  (when (and (>=f left* right*) (<f ,left ,right))
		    (setq right* (1+f left*)))
		  (when (and (>=f top* bottom*) (<f ,top ,bottom))
		    (setq bottom* (1+f top*)))
		  (values left* top* right* bottom*))))
    (transform-region-macro region transform)))




;;; `With-draw-area-from-kb-area?' encapsulates the curious semantics
;;; of establishing a draw area in given image-plane given a component
;;; of the KB.  It binds a draw area (see draw-area).  It assumes that
;;; we have already established the transform of the block in question,
;;; (see drawing-transform).  It takes four edges in the block relative
;;; coordinates, and a value for the bleeding hack (see bleeding-hack).

;;; The body is executed only if the draw area is non-empty, this
;;; presumes that current-image-plane is bound, and that the current
;;; transform has been established.

(defmacro with-draw-area-from-kb-area? ((bleeding-hack
					  left-edge-of-update-area
					  top-edge-of-update-area
					  right-edge-of-update-area
					  bottom-edge-of-update-area)
					&body body)
  (avoiding-variable-capture (bleeding-hack
			       left-edge-of-update-area
			       top-edge-of-update-area
			       right-edge-of-update-area
			       bottom-edge-of-update-area)
    `(with-workspace-to-window-transform (,bleeding-hack)
       ;; Now compute the actual draw area.
       (multiple-value-bind
	   (left-edge-of-update-area-within-pane
	     top-edge-of-update-area-within-pane
	     right-edge-of-update-area-within-pane
	     bottom-edge-of-update-area-within-pane)
	   (transform ,left-edge-of-update-area ,top-edge-of-update-area
		      ,right-edge-of-update-area ,bottom-edge-of-update-area)
	 (with-nested-draw-area? (left-edge-of-update-area-within-pane
				   top-edge-of-update-area-within-pane
				   right-edge-of-update-area-within-pane
				   bottom-edge-of-update-area-within-pane
				   :unknown :update-area)
	   ,@body)))))



;;; The substitution-macro `gensym-windows-showing-workspace' returns a
;;; a freshly consed gensym-list of the set of windows on which the
;;; the given workspace is showing.

(def-substitution-macro gensym-windows-showing-workspace (workspace)
  (loop with result = ()
	for image-plane in (image-planes-this-is-on workspace)
	as gensym-window = (gensym-window-for-image-plane image-plane)
	unless (memq gensym-window result)
	  do (gensym-push gensym-window result)
	finally (return result)))



;;; An `update-function' is a function updates the representation of something
;;; component of a workspace.  It is called when G2 notices a change that
;;; should be passed thru to the screen.  It in turn plans out a way to
;;; achieve that change, and then (usually) calls update-images with a
;;; draw-function, to map that change onto all the image-planes showing
;;; the block in question.  Update functions work outside of the for-image-plane
;;; context and in workspace coordinates.

;;; Update functions are very stylized.  First they compute a minimum amount
;;; they need to redraw.  They then erase that from the screen.  Then they
;;; commit the change being made to the KB data structures, finally they add
;;; that back onto the screen.  They must erase before the commit because
;;; the erase requires the old KB state to XOR out exactly.

;;; Much like update-functions are `change-color-functions'.  These combine the
;;; erase/draw or remove/add bracket with a single XOR to change the color.
;;; These pass thru update images via the macro do-color-revision-faster

;; Not implemented.

(def-concept update-function)
(def-concept change-color-function)




;;; A `Draw-function' is a symbol with a symbol-function.  This function is
;;; called to render onto image-planes.  It may assume that the for-image-plane
;;; context has been established.

;;; Components of the subblock hierarchy rendered by a draw function vary.  A
;;; draw function may render an entire block or connection, a portion of a block
;;; (say the edges of text block), or more than one block and connection (as
;;; occurs when dragging).  Each draw function can be said to render a
;;; particular selection of components.

;;; A draw-function may render the block, or change the color of it's selection
;;; of components.  Rendering the block when in the window is in XOR mode
;;; includes both adding and removing the selection of components.

;;; A draw-function is mapped over the image planes that are currently showing
;;; the selection of it's components, this is done by update-images.

;;; A draw-function may do nothing that might trigger drawing in other windows.
;;; For example it should not change slot values (since that can trigger updates
;;; to tables, or journalling and both of these can cause trigger drawing).  For
;;; example it should not post logbook messages.  Sadly there is one exception
;;; discussed below.

;;; A draw function must layer on top of draw primitives that run thru the
;;; project-graphic-element-to-current-window bottleneck.

;;; A draw function may modify one and only one block, i.e. the format frame
;;; named dynamic-text-cell-format.  This is often bound to
;;; current-text-box-format and used to provide state for the drawing engine in
;;; charts and new-tables.

;;; When the ICP connection is clogged then the draw function may not be called
;;; at all!!!  See on-window-with-drawing for details.

(def-concept draw-function)



;;; `Block-that-draw-function-may-modify-p' implements the exception
;;; to the rule that draw-functions must never ever set slots (see
;;; `draw-function').

(defun-substitution-macro block-that-draw-function-may-modify-p
    (block-or-connection)
  (or (and
	(eq block-or-connection current-text-box-format)
	(eq (name-or-names-for-frame block-or-connection)
	    'dynamic-text-cell-format))
      (eq block-or-connection the-only-dynamic-computation-style)))



;;; `Map-drawing-over-image-planes' calls a draw-function zero or more times on
;;; the image-planes that are showing the given workspace.  It binds the draw
;;; area by taking a rectangle of "update-area" in workspace coordinates and
;;; the bleeding hack flag.  It returns void.

(defun map-drawing-over-image-planes
    (workspace
      frame-transform-block				    ; Has the net frame transform.
      left-edge-of-update-area top-edge-of-update-area	    ; In workspace coordinates.
      right-edge-of-update-area bottom-edge-of-update-area
      bleeding-hack
      draw-function
      &optional
      (arg1 no-arg) (arg2 no-arg) (arg3 no-arg)
      (arg4 no-arg) (arg5 no-arg) (arg6 no-arg)
      (arg7 no-arg))
  (map-drawing-over-image-planes-1
    workspace
    frame-transform-block
    left-edge-of-update-area top-edge-of-update-area
    right-edge-of-update-area bottom-edge-of-update-area
    bleeding-hack
    nil							    ; No extra features.
    nil							    ; No overlapping cleanup.
    draw-function arg1 arg2 arg3 arg4 arg5 arg6 arg7))

;; Called only by force-some-workspace-drawing




;;; `Map-drawing-over-image-planes-1' is a backdoor to
;;; map-drawing-over-image-planes that avoids the optional argument binding.  A
;;; bunch of additional behavior is enabled by the kb-update? argument.  If
;;; that argument is non-NIL, then we first drain the drawing queues, and wrap
;;; a with-open-cursors around the draw function.
;;; Updatee? is as for update-images.

(defun-allowing-unwind map-drawing-over-image-planes-1
    (workspace
      frame-transform-block
      left-edge-of-update-area top-edge-of-update-area
      right-edge-of-update-area bottom-edge-of-update-area
      bleeding-hack
      kb-update?
      updatee?
      draw-function arg1 arg2 arg3 arg4 arg5 arg6 arg7)
  (loop for current-image-plane in (image-planes-this-is-on workspace)
	as gensym-window = (gensym-window-for-image-plane current-image-plane)
	doing
    ;; Printing requires its own special dynamic extent.
    (unless (or (printing-image-plane-p current-image-plane) ; Note D
		(client-drawn-image-plane-p current-image-plane))
      (with-raw-window-transform-and-draw-area
	  (gensym-window)
	(with-nested-transform-and-draw-area-of-image-plane-contents?
	    (current-image-plane)
	  (with-frame-transform-of-block-if-any (frame-transform-block)
	    ;; The following macro uses current-image-plane
	    (with-draw-area-from-kb-area? (bleeding-hack
					    left-edge-of-update-area
					    top-edge-of-update-area
					    right-edge-of-update-area
					    bottom-edge-of-update-area)

	      (on-window-without-drawing (gensym-window)
		(on-window-with-drawing (gensym-window)
		  ;; Call drain-current-window-drawing-queue inside of just the
		  ;; two on-window-xxx macros. This matches other
		  ;; usage. Otherwise, we get nested on-image-plane
		  ;; contexts. This did no harm in the past, but gets in the way
		  ;; of native-image-planes.
		  (when kb-update?
		    (drain-current-window-drawing-queue))

		  (let ((clear-off-top?			    ; Note C.
			  (and kb-update? (xor-mode-p)
			       (opaque-block-p frame-transform-block))))

		    (for-image-plane (current-image-plane)
		      ;; Note A.
		      (with-open-cursors (left-edge-of-draw-area
					   top-edge-of-draw-area
					   right-edge-of-draw-area
					   bottom-edge-of-draw-area
					   ;; Note B.
					   :condition
					   (and kb-update?
						(or (paint-mode-p)
						    (opaque-block-p frame-transform-block)))

					   :xor-overlay t)	    ; Blocks being dragged

			;; We're not properly maintaining the layering of the XOR blocks.
			;; In the presence of opaque blocks, their layer matters.

			(when clear-off-top?
			  (draw-overlapping-xor-blocks workspace frame-transform-block))

			(call-per-number-of-actual-args
			  funcall 1 draw-function
			  arg1 arg2 arg3 arg4 arg5 arg6 arg7)

			(when clear-off-top?
			  (draw-overlapping-xor-blocks workspace frame-transform-block))

			;; This must be done with cursors still open, but the XOR blocks back.
			(when updatee?
			  (draw-overlapping-blocks workspace updatee? 'above nil))))))))))))))

;; Note A: Moving a pane cursor (eg, the edge of a workspace you are moving around)
;; over a text-cell whose color is changing (or any other KB update which does
;; not turn into an invalidate-region), left turds.  Opening the cursors here
;; fixes that problem.

;; Moving an object around over the updating text-cell also turds, hence the
;; :xor-overlay flag is T here.  There is a somewhat delicate interaction
;; between this and start-rendering-dragging-state-for-move-or-transfer, which
;; puts things into the XOR overlay.  So be careful.

;; Note B: In general, if the block we are updating is being painted, then
;; we must open cursors around it.  That condition obtains either in paint-mode
;; or in XOR mode for opaque blocks.

;; Note C: We need even more than that: we need to "open" ANY blocks which are
;; drawn in XOR on top of us.  In XOR mode, that might be all of them!
;; However, since those XOR blocks are not in the XOR overlay, they might have
;; other opaque blocks on top of them.  This is why we must put them back
;; before cleaning up overlapping (opaque) blocks. We're being pretty sleezey
;; here: we can't actually clean off the XOR blocks when there are opaque blocks
;; above them since the region of overlap is trashed.  But the cleanup redraws
;; the opaque blocks on top of the trash, repairing the damage.

;; This solution does lead to some annoying screen dynamics.  The real solution
;; is probably to go back to the workspace - opaque blocks clipping region, as
;; used in 3.0.  Alternatively, if graphs told us the precise region of the
;; screen they are updating, we could clip to that. But graphs only know the
;; region deep inside the hoary recursive descent of their drawing.
;; We may want the clipping region anyways to fix the "flashing object underneath
;; trend-chart" bug from mhd.  It's a mess. -fmw, 9/9/94

;; Note D: Printing works by creating a window and doing output to it over
;; some period of time.  It is hopeless that callers to this routine would "update"
;; the already printed pages, so we preempt the attempt here.




;;; `Update-images' is used to inform the KB drawing queue that all images of
;;; some component of the KB should be refreshed.  It takes these arguments
;;;  erase?
;;;    A flag indicating that the component is being erased.  For window's using
;;;    an XOR drawing mode this means we will XOR off the object.  For window's
;;;    using a painting mode this means we will schedule the refresh of the
;;;    update area given.  If erase is T, then the caller GUARENTEES that it
;;;    will call update-images again with erase NIL, after making some KB change,
;;;    without any intermediate scheduling hit.  There may be other additional
;;;    calls to update-images, however.  If erase is DELETE, then the caller
;;;    makes no such guarentee, and normally will NOT call update-images again.
;; Please note that the erase? flag has been generalized. -fmw, 5/27/94
;;;  updatee
;;;    This is the block or connection which the draw function is drawing.  It
;;;    is used to find the blocks which overlap the draw area via the overlap
;;;    cache.
;;;  frame-transform-block
;;;    This argument anchors the scope within which the drawn requested
;;;    will take place.  It must not be nil.  It is used to infer the set
;;;    of image-planes, and the coordinate system established for the
;;;    drawing done by the function argument.  Drawing should definitely
;;;    not extend outside the extreme edges of this block.
;;;  {left,top,right,bottom}-edge-of-update-area?
;;;    These are in workspace coordinates, of course.  These default to the
;;;    bounds of the workspace containing the component.  To more tightly
;;;    constrain the updated area the caller may specify these, in workspace
;;;    coordinates.  These should be as tightly drawn in as possible to reduce
;;;    the redraw necessary for overlapping items.
;;;  bleeding-hack
;;;    This argument declares how "well behaved" the drawing function is when
;;;    it scales it's coordinates into the image-plane.  See the concept
;;;    bleeding.
;;;  draw-function  &optional arg[1-7]
;;;    The draw-function is a symbol whose symbol function is applied to as many
;;;    of arg1 thru arg7 as are provided.  The draw function is invoked zero or
;;;    more times.  Scheduling may combine updates.  The component may not be on
;;;    any workspace.  The component maybe displayed on one or more
;;;    image-planes.  See the concept draw-function.

;;; This routine requires a little dynamic extent.  It must not be invoked
;;; within an on-window-with-drawing extent.  All information about how to
;;; update the component must be encapsulated in these arguments since scheduled
;;; drawing may defer the actual update.  The special variables that currently
;;; affects this routine are:

;;;   `changing-colors-of-graphic-elements?'
;;;      This indicates that the drawing will change the color of something that
;;;      is already on the screen.


;;; The system-variable `region-invalidation-is-preferred' causes a workspace
;;; region invalidation instead of a direct draw if bound to T in XOR mode.
;;; It's currently bound only when starting to drag opaque blocks in XOR mode.
;;; We need the region invalidation in that case since that's the the only way
;;; to erase an opaque block.  It also bound for some obscure cases in
;;; operate-on-area, where the code is trying to erase a block and remove it as
;;; a subblock, but not delete it.

(def-system-variable region-invalidation-is-preferred panes nil)


;;; The system-variable `update-images-xor-overlay-p' assures update-images
;;; that all drawing is happening in the XOR overlay, hence there is no need to
;;; redraw overlapping blocks (an expensive operation).  This variable is
;;; overridden by region-invalidation-is-preferred.

(def-system-variable update-images-in-xor-overlay-p panes nil)




;; This protocol isn't right yet.  Current-drawing-transfer-mode shouldn't be
;; bound by the callers of this, but for now it must be to notify this protocol
;; that we want to write thru the scheduling.

;; Currently Suffering from the kitchen sink syndrome.


(defun update-images
    (erase? updatee
	    frame-transform-block
	    left-edge-of-update-area? top-edge-of-update-area?
	    right-edge-of-update-area? bottom-edge-of-update-area?
	    bleeding-hack
	    draw-function
	    &optional
	    (arg1 no-arg) (arg2 no-arg) (arg3 no-arg)
	    (arg4 no-arg) (arg5 no-arg) (arg6 no-arg) (arg7 no-arg))
  (let ((workspace (get-workspace-if-any-macro frame-transform-block)))
    (when (and workspace (workspace-showing-p workspace t))
      (let (left top right bottom)
	(cond ;; note C
	  ((and (xor-mode-p)
		(not region-invalidation-is-preferred))
	   (setf left most-negative-workspace-coordinate)
	   (setf top most-negative-workspace-coordinate)
	   (setf right most-positive-workspace-coordinate)
	   (setf bottom most-positive-workspace-coordinate))
	  (t
	   (setf left
		 (or left-edge-of-update-area? (left-edge-of-block workspace)))
	   (setf top
		 (or top-edge-of-update-area? (top-edge-of-block workspace)))
	   (setf right
		 (or right-edge-of-update-area? (right-edge-of-block workspace)))
	   (setf bottom
		 (or bottom-edge-of-update-area? (bottom-edge-of-block workspace)))))

	(cond
	  ;; Case 1: Old fashioned XOR drawing.
	  ((and (xor-mode-p)
		(not region-invalidation-is-preferred))

	   (with-drawing-trace (kb)
	     (format t "XOR: ~(~s ~s erase ~s ~s~)~%"
		     draw-function arg1 erase? current-drawing-priority))
	   
	   (let ((erase-instead? erase?))
	     (map-drawing-over-image-planes-1
	       workspace frame-transform-block
	       left top right bottom bleeding-hack
	       'kb-update
	       ;; We need to allow for overlapping blocks if (1) the block we are drawing is
	       ;; not in the XOR overlay and (2) the workspace has opaque blocks.
	       (if (and (not update-images-in-xor-overlay-p)
			(workspace-has-opaque-blocks-p workspace)
			(not (and (framep updatee) (render-frame-in-xor-overlay-p updatee))))
		   updatee)
	       draw-function arg1 arg2 arg3 arg4 arg5 arg6 arg7)))


	  ;; Case 2: Enqueue special tasks for change color cases.  This
	  ;; eventually cleans up overlapping blocks.
	  (changing-colors-of-graphic-elements?
	   (with-drawing-trace (kb)
	     (format t "CC: ~(~s ~s erase ~s~)~%" draw-function updatee erase?))

	   ;; Color changes assume the screen is currently correct. So drain now.
	   (let ((erase-instead? erase?))
	     (map-drawing-over-image-planes-1
	       workspace frame-transform-block
	       left top right bottom bleeding-hack
	       'kb-update
	       updatee					    ; Used to compute overlapping blocks..
	       draw-function arg1 arg2 arg3 arg4 arg5 arg6 arg7)))

	  
	  ;; Case 3: Invalidate a region inside a block.
	  ((and (or (eq frame-transform-block workspace)    ; Only workspace for WS transform.
		    (not (block-is-transformed-p frame-transform-block)))
		(neq erase? 'delete)
		(not region-invalidation-is-preferred)
		(framep updatee)
		(rectangle-inside-rectangle-p
		  left top right bottom
		  (left-edge-of-block updatee)
		  (top-edge-of-block updatee)
		  (right-edge-of-block updatee)
		  (bottom-edge-of-block updatee)))
	   ;; Lost bleeding-hack!
	   (let ((current-drawing-priority
		   (if erase? :draw-as-late-as-possible current-drawing-priority)))
	     (invalidate-rectangle-of-block workspace updatee left top right bottom)))

	  ;; Case 4: Enqueue an invalidated region. (Note A)
	  (t
	   ;; Defer the erase so that it may be merged with the following draw,
	   ;; if any.  (Note B).
	   (let ((current-drawing-priority
		   (if erase? :draw-as-late-as-possible current-drawing-priority)))
	     (with-drawing-trace (kb)
	       (format t "IV: ~(~s ~s erase ~s ~d ~d ~d ~d~)~%"
		       draw-function arg1 erase?
		       left top right bottom))
	     
	     (invalidate-rectangle-of-workspace
	       workspace
	       frame-transform-block
	       left top right bottom
	       bleeding-hack))))))))

;; Note A: Paint-mode draw-block, goes through here, for example, so we lose
;; the info about which block is changing, and have to scan them all for each
;; update.  This is one reason why we will have a spatial index

;; Note B: We MUST defer when erasing for this reason: callers typically erase
;; a block, then remove it from the workspace.  Thus, at the time the block is
;; erased, it is still on the workspace. Thus, drawing the invalidated region
;; now would bring it right back!

;; Note C: Computing the default update area is complex for blocks that are
;; subblocks of blocks with frames.  Just using the workspace bound's won't
;; work.  This happens currently only in XOR, so we can use this cheaper
;; test and open things up wide.   The mapping and invalidating will all
;; clip more tightly.  We could open things up wide, all the time, but
;; the invalidate-workspace doesn't clip to the workspace bounds, so I'm
;; concerned that if I do that ... trouble.  -- ben Apr 11 95




;;; `Update-images-of-block' updates (draws, or erases when erase-instead? is
;;; non-nil) all zero or more images of block.  If the block is not in a
;;; workspace, no updating is done.

;;; Update-images is used to invoke draw-block once for each image.

;;; The transfer mode may be rebound to XOR if the block is marked as being in
;;; XOR.

;;; The drawing is clipped in one of four ways:
;;;   (1) none,
;;;   (2) the extreme-edges,
;;;   (3) the block bounds, or
;;;   (4) the block bounds plus the icon-overflow.
;;; Three things control the clipping selected
;;;   (a) the third parameter confine-updating-to-block-rectangle?,
;;;           (b) the transfer mode,
;;;
;;;     (a)   (b)  
;;;     t      *     (3) - block bounds
;;;     nil   xor    (1) - none
;;;     nil  paint   (2) - extreme edges

;;; Updates to blocks may circumvent this routine when they want to avoid
;;; redrawing the entire block.

(defun-substitution-macro update-images-of-block-1
    (block erase-p left-extreme-edge? top-extreme-edge? right-extreme-edge? bottom-extreme-edge?)
  (let ((current-drawing-transfer-mode
	  (if (render-frame-in-xor-overlay-p block)
	      :xor
	      current-drawing-transfer-mode))
	(region-invalidation-is-preferred		    ; Note A.
	  (if (and (xor-mode-p)
		   (eq erase-p 'delete)
		   (opaque-block-p block))
	      t
	      region-invalidation-is-preferred)))

    (update-images
      erase-p block block
      left-extreme-edge? top-extreme-edge?
      right-extreme-edge? bottom-extreme-edge?
      nil						    ; Default bleeding for icons (bottom and right)
      'draw-block block)))

;; Note A: In XOR mode, opaque blocks can only be deleted by invalidating the
;; region. Graphs call this function also to just erase graphs, for example, when
;; resizing (erase-p is T).  That leaves a turd when reducing the size because
;; the erase does not really happen (since graphs requests that the draw function
;; be called). -fmw, 9/8/94



(defun update-images-of-block
    (block erase-p confine-updating-to-block-rectangle?)
  (when (showing-p block t)
    (let ((left-extreme-edge? nil)
	  (top-extreme-edge? nil)
	  (right-extreme-edge? nil)
	  (bottom-extreme-edge? nil)
	  (erasing-opaque-block-in-xor-mode?
	    (and (xor-mode-p)
		 (eq erase-p 'delete)
		 (opaque-block-p block))))

      ;; If we're forcing an inval, then also force a tight region.
      (when erasing-opaque-block-in-xor-mode?
	(setq confine-updating-to-block-rectangle? t))
      
      (cond
	(confine-updating-to-block-rectangle?
	 (multiple-value-setq (left-extreme-edge?
				top-extreme-edge?
				right-extreme-edge?
				bottom-extreme-edge?)
	   ;; This binding means we want just the edges of this block,
	   ;; excluding any subblocks.
	   (let ((purpose-of-extreme-edges 'block-and-frame-extent))
	     (determine-extreme-edges-of-block block))))

	;; As an optimization (yeck), if we're certain we won't need the edges,
	;; then don't compute them.
	((and (xor-mode-p)
	      (not region-invalidation-is-preferred)))

	(t
	 (multiple-value-setq (left-extreme-edge?
				top-extreme-edge?
				right-extreme-edge?
				bottom-extreme-edge?)
	   (determine-extreme-edges-of-block block))))
      
      (update-images-of-block-1
	block erase-p
	left-extreme-edge? top-extreme-edge?
	right-extreme-edge? bottom-extreme-edge?))))



;;; The function `update-images-of-rectangle-of-block' seems to be used in place
;;; of update-images-of-block when the edge are known, hence
;;; recomputation thereof can be avoided.

(defun update-images-of-rectangle-of-block 
    (entity erase?
	    left-edge top-edge
	    right-edge bottom-edge)
  (when (showing-p entity t)
    (update-images-of-block-1
      entity erase? left-edge top-edge right-edge bottom-edge)))

;; I think this guy can be removed.  It is called only from MOVE-ITEM-BY and
;; ROTATE-AND-REFLECT-ICON. -fmw, 12/29/94
;; Well, except that update-images-of-block-1 knows things the XOR bit
;; that update-images ought to know. - ben 1/10/95



;;; The macro `with-updates-to-transfer-representations' updates transfer
;;; representations of the given block-or-connection for a kb update.  We know
;;; that transfer reps are drawn in XOR, so we can erase them before the update
;;; and redraw them afterwards.  BODY presumably affects the state of
;;; block-or-connection.

(defmacro with-updates-to-transfer-representations ((block-or-connection) &body body)
  `(prog2
       (when (framep ,block-or-connection)
	 (redraw-transfer-representations-of-block ,block-or-connection t))
       (progn ,@body)
       (when (framep ,block-or-connection)     
	 (redraw-transfer-representations-of-block ,block-or-connection nil))))

;; This macro and the associated function were added to fix HQ-98137.  It
;; should still be wrapped around changes in icon descriptions (somehow), in
;; order to fix HQ-120259 "Changing icon during transfer".





;;; `Do-color-revision' is a macro that allows for smooth, incremental color
;;; revisions.  Function-that-adds-color-differences should be the name of a
;;; function that works by adding color differences to produce the appropriate
;;; colors according to its args.  Function-that-adds-color-differences is not
;;; evaluated.

;;; Body-that-revises-block-itself is run after the screen has been updated.  It
;;; should make the revisions permanent by changing whatever parts of block need
;;; to be changed so that drawing it from now on will display the new colors.
;;; Values that result from evaluating body are returned.

;;; Example (used to revise a text box's colors):
;;;
;;;      (do-color-revision (text-box)
;;;        (revise-text-box-color
;;;          text-box
;;;          new-text-color? new-border-color? new-background-color?)
;;;        (if note-as-kb-state-change?
;;;            (note-kb-state-change text-box 'icon-color))
;;;        (if new-text-color?
;;;            (change-text-box-property
;;;              text-box 'line-color new-text-color?))
;;;        (if new-border-color?
;;;            (change-text-box-property
;;;              text-box 'border-color new-border-color?))
;;;        (if new-background-color?
;;;            (change-text-box-property
;;;              text-box 'background-color new-background-color?)))


;;; The macro `do-color-revision' decides whether a color change can be done the
;;; fast way, by some incremental drawing, or whether it requires a full redraw
;;; of the affected region.  The full redraw is required by any change from an
;;; opaque to a transparent color.

(defmacro do-color-revision ((block-or-connection &optional becoming-transparent-p
						  frame-transform-block)
			     screen-update-form
			     &body kb-update-forms)
  (avoiding-variable-capture (block-or-connection frame-transform-block
						  &aux left top right bottom)
    (progn
      (unless frame-transform-block
	(setq frame-transform-block block-or-connection))
      `(cond ((and (paint-mode-p) ,becoming-transparent-p)
	      (prog1
		  (with-updates-to-transfer-representations (,block-or-connection)
		    ,@kb-update-forms)
		;; This invals just the local edges.
		(invalidate-region-for-block-or-connection ,block-or-connection)))

	     (t
	      (let ((edge-overflow-if-any
		      (if (and (framep ,block-or-connection)
			       (frame-of-class-p ,block-or-connection 'entity))
			  (icon-overflow)
			  0))
		    (changing-colors-of-graphic-elements? t)
		    (current-drawing-transfer-mode current-drawing-transfer-mode)
		    (workspace? (and (framep ,block-or-connection)
				     (get-workspace-if-any-macro ,block-or-connection))))

		(when (if (framep ,block-or-connection) 
			  (render-frame-in-xor-overlay-p ,block-or-connection)
			  (render-connection-in-xor-overlay-p-function ,block-or-connection))
		  (setf current-drawing-transfer-mode :xor))

		(multiple-value-bind (,left ,top ,right ,bottom)
		    (local-edges-of-block-or-connection ,block-or-connection)
		  (update-images
		    nil ,block-or-connection
		    ,frame-transform-block		    ; Uh oh. frame-transform-block must be a block.
		    ,left
		    ,top
		    (+w ,right edge-overflow-if-any)	    ; Why are we adding this by hand?
		    (+w ,bottom edge-overflow-if-any)
		    nil					    ; bleeding-hack
		    ',(first screen-update-form)
		    ,@(rest screen-update-form))
		  
		  (with-updates-to-transfer-representations (,block-or-connection)
		    ,@kb-update-forms))
		(when (and (not (paint-mode-p))
			   (framep ,block-or-connection)
			   (frame-of-class-p ,block-or-connection 'meter)
			   workspace?)  ; (see NOTE A)
		  (let ((region (bounding-region-of-block-or-connection
				  (get-ruling-for-meter ,block-or-connection))))
		    (invalidate-region-of-workspace workspace? region)
		    (reclaim-region region)))))))))


;; NOTE A: This is an inefficient hack to get meters to update correctly when in XOR mode after
;; the user changes the g2-icon-background region color of a meter (or after a reset that changes
;; the background color to the default of light-gray). (pbk 2/6/96)

	

;; Binding changing-colors-of-graphic-elements? causes update-images to call
;; the incremental update function, rather than simply invalidating the region.
;; It also bound by `project-new-table', to no effect, I think.



;;; The macro `updating-images-of-block' takes care of updating the display
;;; properly given a body which mutates the appearance of the given block.  If
;;; locally is true, then we do not redraw subblocks of the block.

(defmacro updating-images-of-block ((block &key locally (condition t))
				    &body kb-update-body)
  (avoiding-variable-capture (block locally condition)
    `(with-deferred-drawing ()
       (when ,condition
	 (erase-images-of-block ,block ,locally))
       (multiple-value-prog1
	   (progn ,@kb-update-body)
	 (when ,condition
	   (draw-images-of-block ,block ,locally))))))

;; This macro is still under construction. -fmw, 12/7/94



;;; The function `invalidate-region-for-block-or-connection' invalidates a
;;; workspace for just the (local) edges of the given block or connection.  It
;;; is used for cases of color changes, just as becoming transparent, which in
;;; fact require a complete redraw, but for which the thing is not changing in
;;; size.

(defun invalidate-region-for-block-or-connection (block-or-connection)
  (let ((workspace?
	  (get-workspace-of-block-or-connection block-or-connection)))
    (when workspace?
      (cond ((framep block-or-connection)
	     ;; Use the faster routine for blocks.
	     (multiple-value-bind (left top right bottom)
		 (local-edges-of-block block-or-connection)
	       (invalidate-rectangle-of-block workspace?
					      block-or-connection
					      left top right bottom)))
	    (t
	     ;; Use the better region for connections.
	     (let ((region (bounding-region-of-block-or-connection
			     block-or-connection)))
	       (invalidate-region-of-workspace workspace? region)
	       (reclaim-region region)))))))


;;; The macro `update-item-views' updates all native views of the given item, on
;;; all connected windows.  At present, the only possible native view of an item
;;; is a view of its icon, for which we've allocated a bit in frame flags to
;;; indicate whether it has any.

(defmacro update-item-views (item)
  (avoiding-variable-capture (item)
    `(when (item-has-icon-views-p ,item)
       (update-icon-views ,item))))



;;;; Changing Workspace Colors




;;; `Change-color-of-workspace' takes four parameters (workspace,
;;; note-as-kb-state-change?, new-{back,fore}ground-color?).  It is a little
;;; unusual in that the "NIL" value is actually :no-change.  It is clever
;;; enough to only drawing only if necessary.

(defun change-color-of-workspace
    (workspace note-as-kb-state-change?
	       new-background-color? new-foreground-color?)
  (let ((do-not-note-permanent-changes-p note-as-kb-state-change?))
    (when note-as-kb-state-change?
      (note-kb-state-change workspace 'workspace-color-pattern))
    (unless (eq new-background-color? :no-change)
      (unless (eq (workspace-background-color? workspace)
		  new-background-color?)
	(change-slot-value workspace 'workspace-background-color?
			   new-background-color?)))
    (unless (eq new-foreground-color? :no-change)
      (unless (eq (workspace-foreground-color? workspace)
		  new-foreground-color?)
	(change-slot-value workspace 'workspace-foreground-color?
			   new-foreground-color?)))))






;;;; Laying Out and Refreshing Windows



;;; A `pane layout' is of the form
;;;
;;;    (pane-name [minimum-width] [minimum-height]) or
;;;
;;;    ((side breadth . pane-layout-of-side-area) . pane-layout-of-remainder),
;;;
;;; where pane-name is a symbol, minimum-width and minimum-height are integer
;;; numbers of pixels, side is left, top, right, or bottom, and where breadth
;;; may be either an integer number of pixels or a floating-point fraction (in
;;; the range 0-1) of the remaining space.  A pane layout must always include a
;;; pane named detail-pane.

;;; An example of a pane layout is
;;;
;;;    ((bottom .35 overview-pane) (left .35 (top .15 title-pane) menu-pane)
;;;     detail-pane).

(def-concept pane-layout)




;;; `Subdivide-pane' subdivides the specified pane in pane-layout, if present,
;;; to have a new pane named new-pane-name on side side with breadth breadth.
;;; It returns a pane layout consisting of entirely new gensym conses.

#+obsolete
(defun subdivide-pane
       (name-of-pane-to-be-subdivided pane-layout new-pane-name side breadth)
  (cond
    ((eq (first pane-layout) name-of-pane-to-be-subdivided)
     (gensym-cons
       (gensym-list side breadth new-pane-name)
       (copy-tree-using-gensym-conses pane-layout)))
    ((atom (first pane-layout))
     (copy-list-using-gensym-conses pane-layout))
    (t (gensym-cons
	 (gensym-cons
	   (car (first pane-layout))
	   (gensym-cons
	     (cadr (first pane-layout))
	     (subdivide-pane
	       name-of-pane-to-be-subdivided
	       (cddr (first pane-layout)) new-pane-name side breadth)))
	 (subdivide-pane
	   name-of-pane-to-be-subdivided
	   (cdr pane-layout)
	   new-pane-name side breadth)))))



;;; `Delete-pane' deletes the specified pane from pane-layout, if present and
;;; not the only pane.  It returns a pane layout consisting of entirely new
;;; gensym conses.

#+obsolete
(defun delete-pane (name-of-pane-to-be-deleted pane-layout)
  (cond
    ((atom (first pane-layout))
     (copy-list-using-gensym-conses pane-layout))
    ((eq (first (cddr (first pane-layout))) name-of-pane-to-be-deleted)
     (copy-tree-using-gensym-conses (cdr pane-layout)))	; recur instead?
    ((eq (first (cdr pane-layout)) name-of-pane-to-be-deleted)
     (copy-tree-using-gensym-conses (cddr (first pane-layout)))); recur instead?
    (t (gensym-cons
	 (gensym-cons
	   (car (first pane-layout))
	   (gensym-cons
	     (cadr (first pane-layout))
	     (delete-pane
	       name-of-pane-to-be-deleted (cddr (first pane-layout)))))
	 (delete-pane name-of-pane-to-be-deleted (cdr pane-layout))))))

;; Consider appending "-in-pane-layout" to the names of the above two functions.




;;; `Lay-out-window' lays out, or revises the layout of, panes on gensym-window,
;;; per window parameters of gensym-window.  The key window parameter is
;;; pane-layout, as described above.

;;; A revised pane layout, as matters now stand, must include all the pane names
;;; of the previous layout.

(defun lay-out-window (gensym-window)
  (let ((width-of-window-border
	  (if (native-windows-p gensym-window)
	      0
	      (get-gensym-window-parameter gensym-window 'width-of-window-border))))
    (lay-out-area-of-window
      gensym-window
      (get-gensym-window-parameter gensym-window 'pane-layout)
      (+r (left-edge-of-window gensym-window) width-of-window-border)
      (+r (top-edge-of-window gensym-window) width-of-window-border)
      (-r (right-edge-of-window gensym-window) width-of-window-border)
      (-r (bottom-edge-of-window gensym-window) width-of-window-border))
    (recompute-visible-regions-for-workstation gensym-window)))

(defun lay-out-area-of-window
       (gensym-window pane-layout
	left-edge-in-window top-edge-in-window
	right-edge-in-window bottom-edge-in-window)
  (let* ((width-of-area
	   (enforce-minimum 0 (-r right-edge-in-window left-edge-in-window)))
	 (height-of-area
	   (enforce-minimum 0 (-r bottom-edge-in-window top-edge-in-window)))
	 (width-of-space-between-panes
	   (get-gensym-window-parameter
	     gensym-window 'width-of-space-between-panes)))
    (if (atom (first pane-layout))
	(loop with pane-name
		= (first pane-layout)
	      with minimum-width-for-pane
		= (or (second pane-layout)
		      (get-gensym-window-parameter gensym-window
			     'default-minimum-width-for-pane))
	      with minimum-height-for-pane
		= (or (third pane-layout)
		      (get-gensym-window-parameter
			gensym-window 'default-minimum-height-for-pane))
	      with pane
		= (or (loop for old-pane in (panes-in-window gensym-window)
			    when (eq (pane-name old-pane) pane-name)
			      return old-pane)
		      (let* (;; (pane-spec?
			     ;;  (pane-spec pane-name))
			     (new-pane
			       ;;  (if pane-spec?
			       ;; (funcall
			       ;;   (pane-spec-constructor pane-spec?)
			       ;;    gensym-window)
				   (make-pane
				     pane-name gensym-window
				     (default-pane-background-color-or-tiling-pattern
					 gensym-window)))); )
			(make-top-plane new-pane)
			(setf (panes-in-window gensym-window)
			      (nconc (panes-in-window gensym-window)
				     (graphics-list new-pane)))
			new-pane))
	      initially
		(if (or (<r width-of-area minimum-width-for-pane)
			(<r height-of-area minimum-height-for-pane))
		    ;; dwarn for now; previously a fatal error
		    (dwarn
		      "There is insufficient space for pane ~A" pane-name))
	      as image-plane in (stack-of-image-planes pane)
;	      as top? = t then nil
	      do (setf (left-edge-of-pane-in-window image-plane)
		       left-edge-in-window)
		 (setf (top-edge-of-pane-in-window image-plane)
		       top-edge-in-window)
		 (setf (right-edge-of-pane-in-window image-plane)
		       right-edge-in-window)
		 (setf (bottom-edge-of-pane-in-window image-plane)
		       bottom-edge-in-window)
		 (if (workspace-on-image-plane? image-plane)
		     ;; fix up workspace-related slots if nec:
		     (set-up-loose-edges-for-workspace-area-within-pane
		       image-plane)))
	(let* ((side (first (first pane-layout)))
	       (maximum-breadth-of-side-area
		 (case side
		   ((left right) width-of-area)
		   (t height-of-area)))
	       (breadth (second (first pane-layout)))
	       (breadth-of-side-area
		 (restrict-to-range
		   0 maximum-breadth-of-side-area
		   (if (integerp breadth)
		       breadth
		       (with-temporary-gensym-float-creation
			   lay-out-area-of-window
			 (round (* breadth maximum-breadth-of-side-area))))))
	       (pane-layout-of-side-area (cddr (first pane-layout)))
	       (pane-layout-of-remainder (cdr pane-layout)))
	  (case side
	    (left
	      (lay-out-area-of-window
		gensym-window pane-layout-of-side-area
		left-edge-in-window top-edge-in-window
		(+r left-edge-in-window breadth-of-side-area)
		bottom-edge-in-window)
	      (lay-out-area-of-window
		gensym-window pane-layout-of-remainder
		(+r left-edge-in-window breadth-of-side-area
		    width-of-space-between-panes)
		top-edge-in-window right-edge-in-window bottom-edge-in-window))
	    (top
	      (lay-out-area-of-window
		gensym-window pane-layout-of-side-area
		left-edge-in-window top-edge-in-window
		right-edge-in-window
		(+r top-edge-in-window breadth-of-side-area))
	      (lay-out-area-of-window
		gensym-window pane-layout-of-remainder
		left-edge-in-window
		(+r top-edge-in-window breadth-of-side-area
		    width-of-space-between-panes)
		right-edge-in-window bottom-edge-in-window))
	    (right
	      (lay-out-area-of-window
		gensym-window pane-layout-of-side-area
		(-r right-edge-in-window breadth-of-side-area)
		top-edge-in-window
		right-edge-in-window bottom-edge-in-window)
	      (lay-out-area-of-window
		gensym-window pane-layout-of-remainder
		left-edge-in-window top-edge-in-window
		(-r right-edge-in-window
		    breadth-of-side-area width-of-space-between-panes)
		bottom-edge-in-window))
	    (bottom
	      (lay-out-area-of-window
		gensym-window pane-layout-of-side-area
		left-edge-in-window
		(-r bottom-edge-in-window breadth-of-side-area)
		right-edge-in-window bottom-edge-in-window)
	      (lay-out-area-of-window
		gensym-window pane-layout-of-remainder
		left-edge-in-window top-edge-in-window right-edge-in-window
		(-r bottom-edge-in-window
		    breadth-of-side-area width-of-space-between-panes))))))))

;; Verify that the pane layout includes a pane named detail-pane.

;; Handle the case where the new pane layout does not include all the old pane
;; names!



;; Should this draw the pane cursors?
(defun paint-pane-background-and-borders (pane left top right bottom)
  (let ((pane-background-color-value-or-tiling-pattern
	  (compute-pane-background-color-value-or-tiling-pattern pane)))
    (do-projection-thru-region 
	((actual-left actual-top actual-right actual-bottom)
	 (left top right bottom)
	 (visible-region-of-pane pane))

      (paint-background-of-current-pane
	pane-background-color-value-or-tiling-pattern
	actual-left actual-top actual-right actual-bottom))))



;;; `Paint-window-and-pane-borders' paints the window and pane borders in gensym
;;; window in the color specified by the pane-borders-color window plist
;;; parameter.  Left-edge-of-area?, top-edge-of-area?, right-edge-of-area?,
;;; and bottom-edge-of-area? may be specified to restrict painting only to that
;;; area.

(defun paint-window-and-pane-borders
    (gensym-window
      &optional
      left-edge-of-area? top-edge-of-area?
      right-edge-of-area? bottom-edge-of-area?)
  (let* ((left-edge-of-window 
	   (left-edge-of-window gensym-window))
	 (top-edge-of-window 
	   (top-edge-of-window gensym-window))
	 (right-edge-of-window 
	   (right-edge-of-window gensym-window))
	 (bottom-edge-of-window 
	   (bottom-edge-of-window gensym-window))
	 (left-edge-of-area
	   (if left-edge-of-area?
	       (maxr left-edge-of-area? left-edge-of-window)
	       left-edge-of-window))
	 (top-edge-of-area
	   (if top-edge-of-area?
	       (maxr top-edge-of-area? top-edge-of-window)
	       top-edge-of-window))
	 (right-edge-of-area
	   (if right-edge-of-area?
	       (minr right-edge-of-area? right-edge-of-window)
	       right-edge-of-window))
	 (bottom-edge-of-area
	   (if bottom-edge-of-area?
	       (minr bottom-edge-of-area? bottom-edge-of-window)
	       bottom-edge-of-window)))
    (when (and (>r bottom-edge-of-area top-edge-of-area)
	       (>r right-edge-of-area left-edge-of-area))
      (update-window
	gensym-window 
	left-edge-of-area top-edge-of-area
	right-edge-of-area bottom-edge-of-area
	'paint-window-and-pane-borders-in-current-window 
	left-edge-of-area top-edge-of-area
	right-edge-of-area bottom-edge-of-area))))


(defun paint-window-and-pane-borders-in-current-window
    (left-edge-of-area top-edge-of-area
		       right-edge-of-area bottom-edge-of-area)
  (let* ((width-of-window-border
	   (get-gensym-window-parameter current-window 'width-of-window-border))
	 (left-edge-of-window 
	   (left-edge-of-window current-window))
	 (top-edge-of-window 
	   (top-edge-of-window current-window))
	 (right-edge-of-window 
	   (right-edge-of-window current-window))
	 (bottom-edge-of-window 
	   (bottom-edge-of-window current-window))
	 (left-edge-of-window-interior		; add "-within-area" ??
	   (maxr left-edge-of-area
		 (+r left-edge-of-window
		     width-of-window-border)))
	 (top-edge-of-window-interior
	   (maxr top-edge-of-area
		 (+r top-edge-of-window
		     width-of-window-border)))
	 (right-edge-of-window-interior
	   (minr right-edge-of-area
		 (-r right-edge-of-window
		     width-of-window-border)))
	 (bottom-edge-of-window-interior
	   (minr bottom-edge-of-area
		 (-r bottom-edge-of-window
		     width-of-window-border))))
    (let ((color-value
	    (map-to-color-value
	      (get-gensym-window-parameter current-window
					   'pane-borders-color))))
      (when (>r top-edge-of-window-interior top-edge-of-area)
	(paint-solid-rectangle-in-current-window
	  left-edge-of-area top-edge-of-area
	  right-edge-of-area top-edge-of-window-interior
	  color-value))
      (when (>r bottom-edge-of-area bottom-edge-of-window-interior)
	(paint-solid-rectangle-in-current-window
	  left-edge-of-area bottom-edge-of-window-interior
	  right-edge-of-area bottom-edge-of-area
	  color-value))
      (when (>r bottom-edge-of-window-interior
		top-edge-of-window-interior)
	(when (>r left-edge-of-window-interior left-edge-of-area)
	  (paint-solid-rectangle-in-current-window
	    left-edge-of-area top-edge-of-window-interior
	    left-edge-of-window-interior bottom-edge-of-window-interior
	    color-value))
	(when (>r right-edge-of-area right-edge-of-window-interior)
	  (paint-solid-rectangle-in-current-window
	    right-edge-of-window-interior top-edge-of-window-interior
	    right-edge-of-area bottom-edge-of-window-interior
	    color-value))
	(paint-pane-borders-per-pane-layout-in-current-window
	  (get-gensym-window-parameter current-window 'pane-layout)
	  (+r left-edge-of-window width-of-window-border)
	  (+r top-edge-of-window width-of-window-border)
	  (-r right-edge-of-window width-of-window-border)
	  (-r bottom-edge-of-window width-of-window-border)
	  color-value
	  left-edge-of-area top-edge-of-area
	  right-edge-of-area bottom-edge-of-area)))))



(defun paint-pane-borders-per-pane-layout-in-current-window
    (pane-layout	; subfunction of the above function
      left-edge-in-window top-edge-in-window
      right-edge-in-window bottom-edge-in-window
      color-value 
      left-edge-of-area top-edge-of-area
      right-edge-of-area bottom-edge-of-area)
  (unless (atom (first pane-layout))
    (let* ((width-of-area
	     (maxr 0 (-r right-edge-in-window left-edge-in-window)))
	   (height-of-area
	     (maxr 0 (-r bottom-edge-in-window top-edge-in-window)))
	   (width-of-space-between-panes
	     (get-gensym-window-parameter
	       current-window 'width-of-space-between-panes))
	   (side (first (first pane-layout)))
	   (maximum-breadth-of-side-area
	     (case side
	       ((left right) width-of-area)
	       (t height-of-area)))
	   (breadth (second (first pane-layout)))
	   (breadth-of-side-area
	     (maxr
	       0 
	       (minr maximum-breadth-of-side-area
		     (if (integerp breadth)
			 breadth
			 (with-temporary-gensym-float-creation
			     paint-pane-borders-per-pane-layout
			   (round
			     (* breadth maximum-breadth-of-side-area)))))))
	   (pane-layout-of-side-area (cddr (first pane-layout)))
	   (pane-layout-of-remainder (cdr pane-layout))

	   ;; these are defaulted and then overridden below:
	   (left-edge-of-side left-edge-in-window)
	   (top-edge-of-side top-edge-in-window)
	   (right-edge-of-side right-edge-in-window)
	   (bottom-edge-of-side bottom-edge-in-window)
	   (side-area-left-edge left-edge-in-window)
	   (side-area-top-edge top-edge-in-window)
	   (side-area-right-edge right-edge-in-window)
	   (side-area-bottom-edge bottom-edge-in-window)			
	   (remainder-area-left-edge left-edge-in-window)
	   (remainder-area-top-edge top-edge-in-window)
	   (remainder-area-right-edge right-edge-in-window)
	   (remainder-area-bottom-edge bottom-edge-in-window))
      (case side
	(left
	 (setq left-edge-of-side
	       (setq side-area-right-edge
		     (+r left-edge-in-window
			 breadth-of-side-area)))
	 (setq right-edge-of-side
	       (setq remainder-area-left-edge		      
		     (+r left-edge-of-side
			 width-of-space-between-panes))))
	(right
	 (setq left-edge-of-side
	       (setq remainder-area-right-edge	
		     (-r right-edge-in-window
			 breadth-of-side-area
			 width-of-space-between-panes)))
	 (setq right-edge-of-side
	       (setq side-area-left-edge
		     (+r left-edge-of-side
			 width-of-space-between-panes))))
	(top
	 (setq top-edge-of-side
	       (setq side-area-bottom-edge
		     (+r top-edge-in-window
			 breadth-of-side-area)))
	 (setq bottom-edge-of-side
	       (setq remainder-area-top-edge
		     (+r top-edge-of-side
			 width-of-space-between-panes))))
	(t
	 (setq top-edge-of-side
	       (setq remainder-area-bottom-edge
		     (-r bottom-edge-in-window
			 breadth-of-side-area
			 width-of-space-between-panes)))
	 (setq bottom-edge-of-side
	       (setq side-area-top-edge
		     (+r top-edge-of-side
			 width-of-space-between-panes)))))
      (let* ((left-edge-of-side-within-area
	       (maxr left-edge-of-side left-edge-of-area))
	     (top-edge-of-side-within-area
	       (maxr top-edge-of-side top-edge-of-area))
	     (right-edge-of-side-within-area
	       (minr right-edge-of-side right-edge-of-area))
	     (bottom-edge-of-side-within-area
	       (minr bottom-edge-of-side bottom-edge-of-area)))
	(when (and (>r right-edge-of-side-within-area
		       left-edge-of-side-within-area)
		   (>r bottom-edge-of-side-within-area
		       top-edge-of-side-within-area))
	  (paint-solid-rectangle-in-current-window
	    left-edge-of-side-within-area top-edge-of-side-within-area
	    right-edge-of-side-within-area bottom-edge-of-side-within-area
	    color-value)
	  (paint-pane-borders-per-pane-layout-in-current-window
	    pane-layout-of-side-area		
	    side-area-left-edge side-area-top-edge
	    side-area-right-edge side-area-bottom-edge
	    color-value
	    left-edge-of-area top-edge-of-area 
	    right-edge-of-area bottom-edge-of-area)
	  (paint-pane-borders-per-pane-layout-in-current-window
	    pane-layout-of-remainder				
	    remainder-area-left-edge remainder-area-top-edge
	    remainder-area-right-edge remainder-area-bottom-edge
	    color-value
	    left-edge-of-area top-edge-of-area 
	    right-edge-of-area bottom-edge-of-area))))))

;; Try to make this smaller.  Speed is not much of an issue!!





;;; The function `Refresh-window' enqueues a refresh for an entire gensym
;;; window.  This would more consistently be called `invalidate-window'.

(defun-void refresh-window (gensym-window)
  (unless (native-windows-p gensym-window)	; Background is drawn locally on client.
    (paint-window-and-pane-borders gensym-window))
  (with-region-from-rectangle-void (region (left-edge-of-window gensym-window)
				      (top-edge-of-window gensym-window)
				      (right-edge-of-window gensym-window)
				      (bottom-edge-of-window gensym-window))
    (invalidate-region-of-window gensym-window region)))

;; Paint-window-and-pane-borders looks very suspicious. - ben 2/23/93

;; There is a bug lurking here: if you kill your X window manager and start it
;; up again, G2 gets confused about its size and its decorations, and the
;; window borders are drawn wrongly. Fixed.  The problem was that the
;; underlying code in xwindows.c was returning refresh and resize events from
;; the title bar window as if they were events for the G2 window. Havoc.



;;; The function `refresh-rectangle-of-window' handle incoming expose
;;; events from the underlying window system.

(defun-void refresh-rectangle-of-window
    (gensym-window left? top? right? bottom?)
  (let ((left-edge-of-area (or left?
			       (left-edge-of-window gensym-window)))
	(top-edge-of-area (or top?
			      (top-edge-of-window gensym-window)))
	(right-edge-of-area (or right?
				(right-edge-of-window gensym-window)))
	(bottom-edge-of-area (or bottom?
				 (bottom-edge-of-window gensym-window))))

    (unless (native-windows-p gensym-window)	; Background is drawn locally on client.
      (paint-window-and-pane-borders gensym-window))

    (invalidate-rectangle-of-window
      gensym-window 
      left-edge-of-area top-edge-of-area
      right-edge-of-area bottom-edge-of-area)))

;; Notice how we punt and redraw the window borders in all cases!





;;;; Mouse Pointing to Spots on Image-Planes




;;; The first refinement of the mouse pointer is to determine what
;;; image-plane the user is pointing to, if any.  Three strucuture
;;; types enumerate the outcome of this.




;;; A `pane-spot' is generated when the mouse is found over one
;;; of the panes of a g2 window.  The enclosed spot is always
;;; an entire-g2-window-spot.

(def-spot pane-spot
    :slots (pane-of-spot)
    :include spot
    :enclosing-spot-type entire-window-spot
    :innermost-spot-p nil
    :abstract-type nil
    :type-of-frame-represented null)



;;; (New:) The "named pane spots" `detail-pane-spot', `overview-pane-spot',
;;; `menu-pane-spot', `status-pane-spot', and `workspace-dock-spot' are used if
;;; the pane spot is for a correspondingly named pane.

(def-spot detail-pane-spot
    :include pane-spot)
(def-spot overview-pane-spot
    :include pane-spot)
(def-spot menu-pane-spot
    :include pane-spot)
(def-spot status-pane-spot
    :include pane-spot)
(def-spot workspace-dock-spot
    :include pane-spot)


;;; An `outside-window-spot' is generated when the mouse is found to
;;; lie outside any particular pane.  The enclosed spot is always
;;; an entire-g2-window-spot.

(def-spot outside-window-spot
    :enclosing-spot-type entire-window-spot
    :innermost-spot-p nil
    :abstract-type nil
    :type-of-frame-represented null)


;;; `Pane-component-spot' is an abstract type that that is subtyped to create
;;; the pane-background and pane-border spot.

(def-spot pane-component-spot
    :innermost-spot-p t
    :abstract-type t
    :type-of-frame-represented null)


;;; A `pane-background-spot' is a refinement of pane-component-spot.
;;; It is generated for locations over the tiled pane background.

(def-spot pane-background-spot
    :enclosing-spot-type entire-window-spot
    :include pane-component-spot
    :abstract-type nil)


;;; A `pane-border-spot' is a refinement of a pane component spot
;;; and it is generated for locations over the black pane borders.
;;; There will not be an enclosing pane-spot.

(def-spot pane-border-spot
    :enclosing-spot-type pane-spot
    :include pane-component-spot
    :abstract-type nil)



;;; An `image-plane-spot' is generated when the mouse is found over an
;;; image-plane.  The item-represented?  is always bound, and is the associated
;;; workspace.  This is an abstract type, refined to indicate if we are over a
;;; temporary, or a permanent workspace.  The two subtypes
;;; `kb-workspace-image-plane-spot' and `non-kb-workspace-image-plane-spot' are
;;; actually instantiated.

;;; The pointer to the image-plane in question is found in the slot
;;; `image-plane-of-spot'.

(def-spot image-plane-spot
    :slots (image-plane-of-spot
	     reference-number-of-image-plane-of-spot
	     x-in-workspace-of-spot
	     y-in-workspace-of-spot)
    :enclosing-spot-type pane-spot
    :innermost-spot-p nil
    :abstract-type t
    :type-of-frame-represented workspace)

;; Note that the code in validate-mouse-pointers has hardwired
;; the set of subtypes of image-plane-spot.

(def-spot kb-workspace-image-plane-spot
    :include image-plane-spot
    :innermost-spot-p nil
    :abstract-type nil
    :type-of-frame-represented kb-workspace)

(def-spot non-kb-workspace-image-plane-spot
    :include image-plane-spot
    :innermost-spot-p nil
    :abstract-type nil
    :type-of-frame-represented non-kb-workspace)

;; It maybe necessary to refine temporary-workspace-image-plane-spot even more
;; to distinquish the various kinds of temporary workspaces.  Message boards,
;; logbook pages, describe output, inspect workspace, clipboard, attribute
;; tables, help workspace, catagory instance menu workspace, telewindows status,
;; network info, title block.


;;; `initialize-mouse-pointer-tracking-for-window' takes a mouse pointer whose spot
;;; is the entire-g2-window.  It installs information about what pane, and
;;; image-plane spots we are over, given a pane? and image-plane?

;;; Before calling this the mouse-pointer's spot is simple:
;;;    #<entire-g2-window-spot ...>
;;; After calling this it is one of these configurations:
;;;    #<kb-workspace-image-plane-spot ...>
;;;    #<pane-spot ...>
;;;    #<entire-g2-window-spot ...>
;;;  or
;;;    #<non-kb-workspace-image-plane-spot ...>
;;;    #<pane-spot ...>
;;;    #<entire-g2-window-spot ...>
;;; or
;;;    #<pane-background-spot ...>
;;;    #<pane-spot ...>
;;;    #<entire-g2-window-spot ...>
;;; or
;;;    #<outside-window-spot ...>
;;;    #<entire-g2-window-spot ...>
;;; or
;;;    #<pane-border-spot ...>
;;;    #<entire-g2-window-spot ...>

;;; This routine is called from service workstation with information bound
;;; into the event that triggered the building of this mouse pointer.

(defun-void initialize-mouse-pointer-tracking-for-window
    (workstation mouse-pointer pane? image-plane?)
  ;; Note A.
  (let ((entire-g2-window-spot (stack-of-spots mouse-pointer))
	(x-of-mouse-pointer (x-of-mouse-pointer mouse-pointer))
	(y-of-mouse-pointer (y-of-mouse-pointer mouse-pointer)))
    (setf (further-tracking-maybe-required? entire-g2-window-spot) nil)
    (cond
      ((not pane?)
       (cond
	 ((let ((gensym-window (window-for-workstation workstation)))
	    (point-inside-rectangle-p 
	      x-of-mouse-pointer
	      y-of-mouse-pointer
	      (left-edge-of-window gensym-window)
	      (top-edge-of-window gensym-window)
	      (right-edge-of-window gensym-window)
	      (bottom-edge-of-window gensym-window)))
	  (push-last-spot mouse-pointer (make-pane-border-spot) nil))
	 (t
	  (push-last-spot mouse-pointer (make-outside-window-spot) nil))))
      (t
       (let ((pane-spot (make-named-pane-spot pane?)))
	 (push-more-detailed-spot mouse-pointer pane-spot nil))
       (cond
	 ((or (null image-plane?)
	      (null (workspace-on-image-plane? image-plane?)))
	  (push-last-spot mouse-pointer (make-pane-background-spot) nil))

	 ((not (point-inside-rectangle-p 
		 x-of-mouse-pointer y-of-mouse-pointer
		 (left-edge-of-image-in-window image-plane?)
		 (top-edge-of-image-in-window image-plane?)
		 (right-edge-of-image-in-window image-plane?)
		 (bottom-edge-of-image-in-window image-plane?)))
	  ;; This is a click in the gray area of a native-image-plane.  TODO:
	  ;; Define a new spot type and add some behavior.
	  (push-last-spot mouse-pointer (make-invalid-spot) nil))

	 (t
	  (let* ((workspace (workspace-on-image-plane? image-plane?))
		 (spot (make-workspace-spot workspace image-plane?
					    x-of-mouse-pointer y-of-mouse-pointer)))
	    (push-more-detailed-spot mouse-pointer spot workspace)
	    ;; Now before returning check that what was true at
	    ;; the time when poll-workstation ran in G2 time is still
	    ;; true, if not then push a final safe workspace background spot.
	    (multiple-value-bind (latest-pane? latest-image-plane?)
		(decode-window-position current-workstation-window
					x-of-mouse-pointer y-of-mouse-pointer)
	      (unless (and (eq latest-pane? pane?)
			   (eq latest-image-plane? image-plane?))
		(push-last-spot
		  mouse-pointer (make-workspace-background-spot-function) nil))))))))))

;; Note A: do not depend on the key-code it isn't normalized yet.


(defun make-named-pane-spot (pane)
  (let ((pane-spot
	  (case (pane-name pane)	; used a named-pane spot if possible.
	    (detail-pane (make-detail-pane-spot))
	    (overview-pane (make-overview-pane-spot))
	    (menu-pane (make-menu-pane-spot))
	    (status-pane (make-status-pane-spot))
	    (workspace-dock-pane (make-workspace-dock-spot))
	    (t (make-pane-spot)))))
    (setf (pane-of-spot pane-spot) pane)
    pane-spot))

(defun make-workspace-spot (workspace image-plane x-in-window y-in-window)
  (let ((spot (frame-class-case (workspace-on-image-plane? image-plane)
		(non-kb-workspace 
		  (make-non-kb-workspace-image-plane-spot))
		(kb-workspace
		  (make-kb-workspace-image-plane-spot)))))
    (setf (image-plane-of-spot spot) image-plane)
    (setf (reference-number-of-image-plane-of-spot spot)
	  (serial-number-of-image-plane image-plane))
    (with-image-plane-transform (image-plane)
      (setf (x-in-workspace-of-spot spot) (x-in-workspace x-in-window))
      (setf (y-in-workspace-of-spot spot) (y-in-workspace y-in-window)))
    (setf (frame-represented? spot) workspace)
    spot))

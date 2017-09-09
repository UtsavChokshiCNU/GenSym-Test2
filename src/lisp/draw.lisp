;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module DRAW

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Lowell B. Hawkinson, Ben Hyde, Mark H. David







;;;; Forward References


(declare-forward-references
  ;; Connections
  (update-new-subblock-connections-activation-and-propagate function)
  (update-removed-subblock-connections-activation-and-propagate function)
  (workspace-of-connection-frame function)
  (draw-overlapping-blocks   function)
  (perform-any-deferred-icon-set-up function)


  #+development (collect-output-connections-for-block function)
  (output-connections-of-block function)
  (note-change-of-connection-for-drawing function)
  (update-extreme-edges-from-connections-of-block function)
  (update-extreme-edges-from-connection function)
  (handle-connection-post-addition-or-removal-as-subblock function)

  (note-change-to-workspace-geometry function)
  (draw-block-or-connection function)
  (draw-connections-for-block function)
  (lower-connection-frame-to-bottom function)

  (remove-block-as-cell-of-table function) ;; tables
  (write-class-instance-header-from-slot function) ; (def... class-instance-header ...)
  (temporary-workspace-is-for-virtual-attribute-table-p function)
  
  (note-kb-state-change function) ;; kb-save2
  
  (add-as-inferior-block function) ;; Traversals
  (remove-as-inferior-block function)

  (install-superblock-in-model-if-appropriate function)

  (force-process-drawing function) ;; Workstations
  (push-more-detailed-spot function)
  (push-last-spot function)

  (lookup-frame-description-reference-from-frame-style-definition? function) ;; formats
  (get-or-make-format-frame-function function)

  (draw-title-bar-text function) ;; boxes

  (draw-rubber-stamp-widget function) ;; entities
  (close-box-rubber-stamp-widget variable)
  (draw-icon-for-entity function)

  (has-background-images-p function) ;; definitions
  (draw-background-images function) ;; definitions
  (draw-background-image function) ;; definitions
  (region-containing-background-images function)
  (update-extreme-edges-from-background-images function)

  (draw-alignment-grid function)	; definitions
  (visible-grid-p function)

  (lower-match-rank-for-player-eyes-p variable) ; player

  (suppress-printing-border-p function)) ; printing


(declare-forward-reference send-ws-representations-item-insert-as-subblock function) ; VIEW-G2
(declare-forward-reference send-ws-representations-item-remove-as-subblock function) ; VIEW-G2
(declare-forward-reference send-ws-representations-item-layer-change function) ; VIEW-G2
(declare-forward-reference get-topmost-child-of-block function) ; VIEW-DEF
(declare-forward-reference ws-has-ws-representation-p function) ; VIEW-DEF
(declare-forward-reference update-subscriptions-for-remove-item-from-workspace
			   function) ; VIEW-DEF
(declare-forward-reference loose-end-p-function function) ; CONNECT1
(declare-forward-reference get-or-make-connection-frame-and-activate-if-appropriate function) ;CONNECT2
(declare-forward-reference note-permanent-change-to-slot-group-for-block function)
(declare-forward-reference loose-end-connection-p function) ; CONNECT3A
(declare-forward-reference remove-subblocks-and-connections-from-drawing-queues function) ; CONNECT3A
(declare-forward-reference write-name-or-names-from-slot
			   function)	; FRAMES2B (slot writer for name-or-names)
(declare-forward-reference known-gensym-acronyms variable)	; TABLES
(declare-forward-reference color-or-metacolor-p function)       ; GRAMMAR4

;; Selection UI

(declare-forward-reference selection-enabled-p function)
(declare-forward-reference workspace-selected-p function)
(declare-forward-reference selectable-image-plane-p function)
(declare-forward-reference image-plane-selected-p function)
(declare-forward-reference primary-selection-color function)
(declare-forward-reference recompute-selection-highlights function)
(declare-forward-reference note-remove-as-subblock-for-selection function)
(declare-forward-reference show-selection-handles-p function)
(declare-forward-reference draw-selection-handles-for-current-image-plane function)


;;;; Support for Drawing



;;; The macro `do-subblocks' runs body on block, all subblocks of blocks, and
;;; recursively upon them.

(defmacro subblocks-list (superblock)
  (let ((subblock (gensym)))
    `(loop for ,subblock being each subblock of ,superblock
	   collect ,subblock using tree-ordering-cons)))

(defmacro do-subblocks ((subblock superblock) &body body)
  #-subblocks-v2
  `(do-post-order (,subblock ,superblock subblocks)
     ,@body)
  #+subblocks-v2
  `(do-post-order (,subblock ,superblock subblocks-list :do-not-copy-list t)
     ,@body))





;;; `Outline-drawing' takes a block or connection structure, and displays an
;;; outline in the style of outline-tree-of-nodes.  This helps to clarify
;;; drawing order, layering, etc.  This doesn't do the right thing with respect
;;; to displaying the objects that are deferred into the XOR or opaque overlays.

#+development
(defun outline-drawing (block-or-connection
			    &key
			    ((:print-length *print-length*) 10)
			    ((:print-level *print-level*) 4)
			    (visible-p #'(lambda (node) (declare (ignore node)) t)))
  (outline-tree-of-nodes
   #'(lambda (block-or-connection)
       (cond
	 ((framep block-or-connection)
	  (nconc
	    (let ((subblocks
		   (loop for subblock being subblock of block-or-connection
			 collect subblock)))
	      (cond
		((frame-of-class-p block-or-connection 'workspace)
		 (reverse subblocks))  ;; Drawn in reverse order.
		(t
		 subblocks)))
	    (collect-output-connections-for-block block-or-connection)))
	 ((image-plane-p block-or-connection)
	  (list*
	   :empty-image-plane
	   (workspace-on-image-plane? block-or-connection)
	   :overlay-followed-by-image-plane-cursors
	   (copy-list (image-plane-cursors block-or-connection))))))
   block-or-connection
   0
   (cons nil nil)
   visible-p)
  block-or-connection)





;;;; Special-purpose Funcalls in Workstation Contexts



;;; The function `funcall-for-workstation-of-image-plane' establishes a
;;; for-workstation context for the workstation image-plane is on, and then
;;; applies function to up to three optional args, arg1 through arg3.
;;;
;;; Note that while the function is applied to the args in for-workstation
;;; context, the args are evaluated before the context is entered.  That follows
;;; naturally from the fact that this is a function.
;;;
;;; Note: at present the maximum number or arguments is three.  This slightly
;;; exceeds requirements of current callers.  It can be extended to a higher
;;; number readily if needed.

;;; This is generally equivalent the effect of explicit code to establish the
;;; context and call the function, but it may save a bit of code space due to
;;; the expansion of the macro, and may be more convenient in some cases.  Note

(defun funcall-for-workstation-of-image-plane
    (image-plane function &optional (arg1 no-arg) (arg2 no-arg) (arg3 no-arg))
  (for-workstation ((workstation-of-image-plane image-plane))
    (call-per-number-of-actual-args funcall 1 function arg1 arg2 arg3)))

;; This was chosen as the best place for this function because this uses macros
;; defined in PANES, the previous module, and the first and thus-far only users
;; are in this module, below. (MHD 10/28/02)





;;;; Determining the Extent (aka Extreme Edges) of Blocks



;;; The `extreme edges' of a block (or a set of blocks and
;;; connections) define a rectangle bounding the block, subblock tree
;;; and out going connections of the block.

;;; The extreme edges are useful for clipping, and workspace resizing.
;;; These are not very useful for hit testing.

;;; The set of things included within the extreme edges are the the
;;; things rendered when the block is drawn. (See the generic method
;;; draw below)

;;; Some additional routines used for hit testing are also found in this
;;; section.

;;; Actual drawing may extend one pixel beyond the right and bottom
;;; of the extreme edges.  See left-edge-of-draw-area for some
;;; discussion of this problem in G2.

;; - ben 4/06/92

;; Is this doing the right thing about stubs that are input
;; connections? - ben 10/1/93



;;; `Extreme-left-edge-so-far' and friends provide a dynamic extent for the
;;; recursive process of accumulating the extreme edges of some portion of the
;;; subblock hierarchy.  Routines who's names begin `determine-extreme-edges-'
;;; establish this extent, while routines who's names begin
;;; update-extreme-edges- assume this extent is current.  This dynamic extent is
;;; named as `with-extreme-edges'.

;;; The variable `purpose-of-extreme-edges' is used to modify the extent
;;; computed.  The default value `draw-extent' computes the bounding rectangle
;;; that tightly encloses the block being drawn.  This includes the blocks,
;;; subblocks, frames and outgoing connections, and those incomming connections
;;; which have `loose-ends' at their other ends.

;;; When the purpose-of-extreme-edges is bound to `block-and-frame-extent' then
;;; only the block is included and any frame.  The connections, and subblocks
;;; extents are not included.  This is useful when changing the color of icons,
;;; or updating the frame.

;;; Binding purpose-of-extreme-edges to `move-extent' computes the extent as per
;;; drawing, except connections that leave the set being dragged and connect to
;;; objects outside that set are ignored.  This is used to infer the size of an
;;; selection being dragged and to trigger resizing, scrolling, or pinning the
;;; dragging.  (Not Yet Implemented, hence a bug).

(def-named-dynamic-extent with-extreme-edges
  (module draw))
(defvar-of-named-dynamic-extent purpose-of-extreme-edges with-extreme-edges
    (global-binding 'draw-extent))
(defvar-of-named-dynamic-extent extreme-left-edge-so-far with-extreme-edges)
(defvar-of-named-dynamic-extent extreme-top-edge-so-far with-extreme-edges)
(defvar-of-named-dynamic-extent extreme-right-edge-so-far with-extreme-edges)
(defvar-of-named-dynamic-extent extreme-bottom-edge-so-far with-extreme-edges)



;;; `With-extreme-edges' is the only correct way to establishes the
;;; dynamic extent within which the accumulation of extreme edges
;;; takes place.  It corrects for the one pixel addition necessary on
;;; the right and bottom of entities.

(defmacro with-extreme-edges ((block) &body body)
  (avoiding-variable-capture (block)
    `(let* ((extreme-left-edge-so-far (left-edge-of-block ,block))
	    (extreme-top-edge-so-far (top-edge-of-block ,block))
	    (extreme-right-edge-so-far extreme-left-edge-so-far)
	    (extreme-bottom-edge-so-far extreme-top-edge-so-far))
       (update-extreme-edges-from-block-bounds ,block)
       ,@body)))



;;; The macro `with-extreme-edges-1' does not require a block with which to
;;; start the extrematization.

(defmacro with-extreme-edges-1 (() &body body)
  `(let* ((extreme-left-edge-so-far (minf))
	  (extreme-top-edge-so-far (minf))
	  (extreme-right-edge-so-far (maxf))
	  (extreme-bottom-edge-so-far (maxf)))
     ,@body))



;;; `With-extreme-edges-minimizing-workspace' is used when computing
;;; minimum size required to hold the subblocks in a workspace.  It
;;; does the slightly clever thing of swapping the current workspace
;;; edges and using those as the initial bindings for the extreme
;;; edges.

(defmacro with-extreme-edges-minimizing-workspace ((workspace) &body body)
  (avoiding-variable-capture (workspace)
    `(let ; with-named-dynamic-extent with-extreme-edges ;; Multiple Values
	 ((extreme-left-edge-so-far (right-edge-of-block ,workspace))
	   (extreme-top-edge-so-far (bottom-edge-of-block ,workspace))
	   (extreme-right-edge-so-far (left-edge-of-block ,workspace))
	   (extreme-bottom-edge-so-far (top-edge-of-block ,workspace)))
      ,@body)))





;;; `Update-{horizontal,vertical}-extreme-edges' and
;;; `update-extreme-edges-of-point' are three substituiton macros are used
;;; internally here and in analagous code in connections to update the extremes.

(defun-substitution-macro update-horizontal-extreme-edges (left right)
  (when (<w left extreme-left-edge-so-far)
    (setf extreme-left-edge-so-far left))
  (when (>w right extreme-right-edge-so-far)
    (setf extreme-right-edge-so-far right)))

(defun-substitution-macro update-vertical-extreme-edges (top bottom)
  (when (<w top extreme-top-edge-so-far)
    (setf extreme-top-edge-so-far top))
  (when (>w bottom extreme-bottom-edge-so-far)
    (setf extreme-bottom-edge-so-far bottom)))

(defun-substitution-macro update-extreme-edges-from-point (x y)
  (update-horizontal-extreme-edges x x)
  (update-vertical-extreme-edges y y))

(defun-substitution-macro update-extreme-edges-from-rectangle
    (left top right bottom)
  (update-horizontal-extreme-edges left right)
  (update-vertical-extreme-edges top bottom))



;;; The function `grow-extreme-edges' grows all of the current extreme edges
;;; outwards by dx and dy.  It's used to fudge regions.

(defun-substitution-macro grow-extreme-edges (dx dy)
  (decff extreme-left-edge-so-far dx)
  (decff extreme-top-edge-so-far dy)
  (incff extreme-right-edge-so-far dx)
  (incff extreme-bottom-edge-so-far dy))




;;; The macro `adjust-block-edges-for-icon-overflow' adjusts the given edges to
;;; account for bleeding when drawing the given block.  Each of the edges
;;; arguments must be a setf-able place.

(defmacro adjust-block-edges-for-icon-overflow (block left top right bottom)
  (declare (ignore left top))
  `(when (frame-of-class-p ,block 'entity)
     (incff ,right (icon-overflow))
     (incff ,bottom (icon-overflow))))


;;; The variable `do-not-update-selection-highlights' is bound to T by routines
;;; which do their own selection highlight updating. It prevents
;;; note-change-to-edges-of-block from doing the update.

(defvar do-not-update-selection-highlights nil)


;;; The function `note-change-to-edges-of-block' updates various geometry
;;; caches and indices when the edges of a block are changed.  The edges
;;; passed-in must be precicely the old and new values of the *-edge-of-block
;;; slots of the block.

(defun note-change-to-edges-of-block (block old-left old-top old-right old-bottom
					    new-left new-top new-right new-bottom)
  (let ((workspace? (get-workspace-if-any block)))
    (when workspace?

      ;; As far as drawing is concerned, graphs do not have subblocks.
      (unless (subblock-of-graph-p block)

	(note-permanent-change-to-slot-group-for-block block)

	;; Invalidate caches.
	(note-change-to-workspace-geometry workspace?)

	;; Update the index if there is one.
	(let ((geometry? (workspace-spacial-index? workspace?)))
	  (when (and geometry? (not (workspace-p block)))

	    ;; Blocks are entered into the spacial index WITH icon-overflow included.
	    ;; The basic assumption is that local-edges-of-block returns the same
	    ;; values as those passed in here.
	    (adjust-block-edges-for-icon-overflow
	      block old-left old-top old-right old-bottom)

	    (adjust-block-edges-for-icon-overflow
	      block new-left new-top new-right new-bottom)
	    

	    (geometry-delete geometry?
			     block
			     old-left old-top old-right old-bottom)
	    (geometry-insert geometry?
			     block
			     new-left new-top new-right new-bottom)

	    ;; A block's connections move when the block moves, even though the
	    ;; connections themselves have not changed (since connection positions
	    ;; are maintained as deltas).  So reindex all the connections here.
	    (let ((connections
		    (output-connections-of-block block)))

	      (loop for connection in connections doing
		(note-change-of-connection-for-drawing connection))

	      (when connections
		(reclaim-tree-ordering-list connections)))))

	;; Propagate change to selection highlights, unless requested not to.
	(unless do-not-update-selection-highlights
	  (recompute-selection-highlights block))))))



;;; `Update-extreme-edges-from-block-bounds' is the only correct way to add a
;;; block into the dynamic extent of extreme edges.  It corrects for the one
;;; pixel overflow found in the icon of entities.  It adds in the enclosing
;;; frame, if any.

(defun update-extreme-edges-from-block-bounds (block)
  (let ((left-edge   (left-edge-of-block block))
	(top-edge    (top-edge-of-block block))
	(right-edge  (right-edge-of-block block))
	(bottom-edge (bottom-edge-of-block block)))

    ;; Note the icon overflow.
    (adjust-block-edges-for-icon-overflow
      block left-edge top-edge right-edge bottom-edge)

    ;; Note any enclosing frame. ( I used to wrap the around, now I nest them
    ;; inside, so this is obsolete, unless I change my mind again.
    (let ((frame-description-reference?
	    (fast-lookup-frame-description-reference-of-block? block)))
      (when frame-description-reference?
	(decff left-edge (left-frame-indent frame-description-reference?))
	(decff top-edge (top-frame-indent frame-description-reference?))
	(incff right-edge (right-frame-indent frame-description-reference?))
	(incff bottom-edge (bottom-frame-indent frame-description-reference?))))

    ;; Fold into the dynamic extent.
    (update-horizontal-extreme-edges left-edge right-edge)
    (update-vertical-extreme-edges top-edge bottom-edge)))


;;; `Update-extreme-edges-from-elements' updates special variables
;;; extreme-left-edge-so-far et al. for all subblocks of block to all levels
;;; plus all connections on the block and those subblocks to all levels, but NOT
;;; for block itself.  Taking advantage of the rule that a block with a frame
;;; never renders outside that frame this is a no-op for these blocks.  Then it
;;; avoids that optimization if the block passed is a workspace.

(defun-void update-extreme-edges-from-elements-function (block do-only-loose-ends-p)
  (unless (block-is-transformed-p block)
    (loop for subblock being each subblock of block 
	  do (update-extreme-edges-from-block-bounds subblock)
	     (when (or (has-subblocks-p subblock) (connections subblock))
	       (update-extreme-edges-from-elements-function subblock do-only-loose-ends-p)))
    (update-extreme-edges-from-connections-of-block block do-only-loose-ends-p)))

(defmacro update-extreme-edges-from-elements (block)
  `(update-extreme-edges-from-elements-function ,block nil))

;;; `Determine-extreme-edges-of-block' returns four values for any block: the
;;; left, top, right, and bottom extreme edges of block.  These are the extreme
;;; edges of the block and any of its "elements" (subblocks to all levels plus
;;; all connections on the block and those subblocks).

(defun determine-extreme-edges-of-block (block)
  (with-extreme-edges (block)
    (when (and (not (eq purpose-of-extreme-edges 'block-and-frame-extent))
	       (or (has-subblocks-p block)
		   (connections block)))
      (update-extreme-edges-from-elements block))
    (values extreme-left-edge-so-far extreme-top-edge-so-far
	    extreme-right-edge-so-far extreme-bottom-edge-so-far)))



(defun local-edges-of-block (block)
  (with-extreme-edges (block)
    (values extreme-left-edge-so-far extreme-top-edge-so-far
	    extreme-right-edge-so-far extreme-bottom-edge-so-far)))



;;; The function `make-region-from-block-edges' returns a region which cover
;;; the given block, NOT including subblocks or connections.

(defun make-region-from-block-edges (block)
  (with-extreme-edges (block)
    (make-region-from-rectangle
      extreme-left-edge-so-far extreme-top-edge-so-far
      extreme-right-edge-so-far extreme-bottom-edge-so-far)))




;;; `Determine-extreme-edges-of-workspace-subblocks' returns the extreme edges
;;; of the subblocks of the workspace given.  It returns NIL if there are
;;; no subblocks.

(defun determine-extreme-edges-of-workspace-subblocks (workspace)
  (when (has-subblocks-p workspace)
    (with-extreme-edges ((first-subblock workspace))
      (update-extreme-edges-from-elements workspace)
      (values extreme-left-edge-so-far extreme-top-edge-so-far
	      extreme-right-edge-so-far extreme-bottom-edge-so-far))))



;;; `Determine-extent-of-blocks-and-connections' returns four values,
;;; i.e. the smallest bounding box that includes the blocks and
;;; connections passed as the two arguments.  At least one block is
;;; required.

(defun determine-extreme-edges-of-blocks-and-connections (blocks
							   connections
							   do-only-loose-ends-p)
  (with-extreme-edges ((first blocks))
    (loop for block in blocks doing
      (update-extreme-edges-from-block-bounds block)
      (update-extreme-edges-from-elements-function block do-only-loose-ends-p))
    (loop for connection in connections
	  do
      (unless (and do-only-loose-ends-p
		   (not (loose-end-connection-p connection)))
	(update-extreme-edges-from-connection connection)))
    (values extreme-left-edge-so-far
	    extreme-top-edge-so-far
	    extreme-right-edge-so-far			    ; This was often off by one.
	    extreme-bottom-edge-so-far)))


;;; Extent-of-block-within-draw-area takes a block and returns a
;;; rectangle in four values.

(defun extent-of-block-within-draw-area (block)
  (with-extreme-edges (block)
    (update-extreme-edges-from-block-bounds block)
    (update-extreme-edges-from-elements block)
    (let ((extreme-left-edge-in-window (x-in-window extreme-left-edge-so-far))
	  (extreme-top-edge-in-window (y-in-window extreme-top-edge-so-far))
	  (extreme-right-edge-in-window (x-in-window extreme-right-edge-so-far))
	  (extreme-bottom-edge-in-window
	   (y-in-window extreme-bottom-edge-so-far)))
      (if (rectangles-overlap-p
	    extreme-left-edge-in-window extreme-top-edge-in-window
	    extreme-right-edge-in-window extreme-bottom-edge-in-window
	    left-edge-of-draw-area top-edge-of-draw-area
	    right-edge-of-draw-area bottom-edge-of-draw-area)
	  (values (maxf extreme-left-edge-in-window left-edge-of-draw-area)
		  (maxf extreme-top-edge-in-window  top-edge-of-draw-area)
		  (minf extreme-right-edge-in-window right-edge-of-draw-area)
		  (minf extreme-bottom-edge-in-window bottom-edge-of-draw-area))
	  ;; An Empty Region.
	  (values left-edge-of-draw-area top-edge-of-draw-area
		  left-edge-of-draw-area top-edge-of-draw-area)))))


;;; `Block-overlaps-draw-area' takes a block and returns a boolean.

(defun-simple block-overlaps-draw-area (block)
  (with-extreme-edges (block)
    (update-extreme-edges-from-elements block)
    (rectangles-overlap-p
      (x-in-window extreme-left-edge-so-far) 
      (y-in-window extreme-top-edge-so-far)
      (x-in-window extreme-right-edge-so-far)
      (y-in-window extreme-bottom-edge-so-far)
      left-edge-of-draw-area top-edge-of-draw-area
      right-edge-of-draw-area bottom-edge-of-draw-area)))


;;; `In-block-p' tests is {x,y}-in-workspace is within any of the
;;; blocks found within the subblock hierarchy begining from block.

;;; Not this is not the same as testing if the point is within the
;;; block's extreme edges.

(defun in-block-p (block x-in-workspace y-in-workspace)
  (or (and (>=w x-in-workspace (left-edge-of-block block))
	   (<=w x-in-workspace (right-edge-of-block block))
	   (>=w y-in-workspace (top-edge-of-block block))
	   (<=w y-in-workspace (bottom-edge-of-block block)))
      (loop for subblock being each subblock of block
	    thereis (in-block-p subblock x-in-workspace y-in-workspace))))

;; Rename this "in-block-or-subblock-thereof-p"!



;;; `In-extreme-edges-of-block-p' returns true if 
;;; {x,y}-in-workspace y-is within the extreme edges of the block.

;;; This is used in some hit testing when the block is known to have no
;;; connections.

(defun in-extreme-edges-of-block-p (block x-in-workspace y-in-workspace)
  (multiple-value-bind
    (extreme-left-edge extreme-top-edge extreme-right-edge extreme-bottom-edge)
      (determine-extreme-edges-of-block block)
    (and (>=w x-in-workspace extreme-left-edge)
	 (<=w x-in-workspace extreme-right-edge)
	 (>=w y-in-workspace extreme-top-edge)
	 (<=w y-in-workspace extreme-bottom-edge))))

;; Rename this "in-rectangle-encompassing-block-and-its-subelements-p"!



;;; `Edges-of-block-content-plus-frame' returns the edges of the block content
;;; plus that of any frame.

(defun edges-of-block-content-plus-frame (block)
  (let ((frame-description-reference?
	  (fast-lookup-frame-description-reference-of-block? block))
	(left-edge (left-edge-of-block block))
	(top-edge (top-edge-of-block block))
	(right-edge (right-edge-of-block block))
	(bottom-edge (bottom-edge-of-block block)))
    (when frame-description-reference?
      (decff left-edge (left-frame-indent frame-description-reference?))
      (decff top-edge (top-frame-indent frame-description-reference?))
      (incff right-edge (right-frame-indent frame-description-reference?))
      (incff bottom-edge (bottom-frame-indent frame-description-reference?)))
    (values left-edge top-edge right-edge bottom-edge)))




;;; The substitution-macro `extreme-edges-of-block' returns the outermost edges
;;; of block and all of its subblocks and connections.

(def-substitution-macro extreme-edges-of-block (block)
  (let ((purpose-of-extreme-edges 'draw-extent))
    (determine-extreme-edges-of-block block)))



(def-substitution-macro extreme-edges-of-blocks (block)
  (let ((purpose-of-extreme-edges 'draw-extent))
    (determine-extreme-edges-of-block block)))




;;;; Adding and Removing Subblocks

(defun-simple find-next-non-loose-end (list)
  (loop for block in list
	do
    (cond ((loose-end-p-function block)
	   (let ((output-connections (output-connections-of-block block)))
	     (when output-connections
	       (return; loose-end CANNOT have more than one
		 (prog1 (get-or-make-connection-frame-and-activate-if-appropriate
			  (car output-connections))
		   (reclaim-tree-ordering-list output-connections))))))
	  (t (return (get-topmost-child-of-block block))))))

#+subblocks-v2
(defun-simple find-next-non-loose-end-in-queue (constant-queue cursor)
  (loop with head = (constant-queue-head constant-queue)
	for queue-element = (if cursor
				(constant-queue-next cursor constant-queue)
			      #-Lockfree-Deque head
			      #+Lockfree-Deque (constant-queue-next head constant-queue))
		       then (constant-queue-next queue-element constant-queue)
	until #-Lockfree-Deque (eq queue-element constant-queue)
	      #+Lockfree-Deque (null queue-element)
	for block = (queue-datum queue-element)
	do
    (cond ((loose-end-p-function block)
	   (let ((output-connections (output-connections-of-block block)))
	     (when output-connections
	       (return
		 (prog1 (get-or-make-connection-frame-and-activate-if-appropriate
			  (car output-connections))
		   (reclaim-tree-ordering-list output-connections))))))
	  (t (return (get-topmost-child-of-block block))))))

;; This is here because of its dependency on image planes.



;;; `Add-subblock' makes block a subblock of superblock and returns block.  The
;;; state that is maintained in synch with the subblock hierarchy includes: the
;;; state of simulation models, the stack of opaque subblocks, the activation
;;; state, and finally the transient/permanent status of the block.

;;; Block gets added at the beginning of the ordered sequence of subblocks of
;;; superblock.  If the opaque-block frame flag of block is set, it will be
;;; pushed onto the stack of subblocks.

;;; This updates the activation status of block as appropriate: If superblock is
;;; active, block will be activated (if it has an activation method); otherwise,
;;; it will be deactivated appropriately ....

;;; If block has connections, and block is not a loose end, and superblock is a
;;; workspace, this also updates the activation status for frames connected to
;;; block (by calling itself with those frames).

;;; `Install-superblock-in-model-if-appropriate' implements updating the
;;; simulation model.  `Add-as-inferior-block' implements updating the
;;; permanent/transient state.

;;; The block should be drawn after this call.

;;; Note that reading a saved kb does not make use of add-subblock.


(defun add-subblock (block superblock)
  (let ((workspace? (get-workspace-if-any superblock))
	next-item)

    (perform-any-deferred-icon-set-up superblock)
    (perform-any-deferred-icon-set-up block)
    
    ;; Maintain overlap-cache, geometry index and count of opaque blocks.
    (when workspace?
      (note-change-to-workspace-geometry workspace?)
      (incff (number-of-blocks-on-workspace workspace?))
      (update-spacial-index workspace? block 'add)
      (when (opaque-block-p block)
	(incff (number-of-opaque-blocks-on-workspace workspace?))))

    #+development
    (when (and (superblock? block)
	       (neq (superblock? block) superblock))
      ;; Graphs do this.
      (dwarn "Slamming the superblock of ~s from ~s to ~s"
	     block (superblock? block) superblock))

    ;; Wire into super/subblock hierarchy.
    ;; Keeping opaque blocks on top makes this messy.
    (set-superblock-and-faction block superblock)
    (cond
      ;; NOTE: if it's a opaque block, push to the front.
      ((or (opaque-block-p block)
	   (empty-subblocks-p superblock)
	   (not (opaque-block-p (first-subblock superblock))))
       (when (and g2-has-v5-mode-windows-p
		  workspace?
		  (frame-of-class-p workspace? 'kb-workspace))
	 (setf next-item
	       (if (eq workspace? superblock)
		   (get-topmost-child-of-block
		     (first-subblock superblock))
		   (get-topmost-child-of-block
		     superblock)))
	 (when (and next-item (loose-end-p-function next-item))
	   (setf next-item
		 #-subblocks-v2 (find-next-non-loose-end (subblocks superblock))
		 #+subblocks-v2 (find-next-non-loose-end-in-queue
				  (subblocks superblock) nil))))
       #-subblocks-v2
       (slot-value-push block (subblocks superblock))
       #+subblocks-v2
       (progn
	 (unless (subblocks superblock)
	   (setf (subblocks superblock) (make-empty-constant-queue)))
	 (constant-queue-filo-enqueue (subblocks superblock) block)) ; push-left

       (when (and g2-has-v5-mode-windows-p
		  workspace?
		  (frame-of-class-p workspace? 'kb-workspace))
	 (send-ws-representations-item-insert-as-subblock
	   block superblock
	   next-item))) ;  -pbk 10/19/95
      (t
       (note-change-to-block superblock 'subblocks) ; NOTE D
       ;; NOTE: otherwise append to the end of all opaque blocks.
       #-subblocks-v2
       (loop for remaining-subblocks on (subblocks superblock)
	     as listed-next-subblock? = (cdr remaining-subblocks)
	     unless listed-next-subblock?
	       do
		 (setf (cdr remaining-subblocks)
		       (slot-value-cons block nil))
		 (when (and g2-has-v5-mode-windows-p
			    workspace?
			    (frame-of-class-p workspace? 'kb-workspace))
		   (send-ws-representations-item-insert-as-subblock
		     block superblock
		     'bottom)) ; -pbk 10/10/95 
		 (return nil)
	     unless (opaque-block-p (car listed-next-subblock?))
	       do
		 (when (and g2-has-v5-mode-windows-p
			    workspace?
			    (frame-of-class-p workspace? 'kb-workspace))
		   (setf next-item
			 (if (eq workspace? superblock)
			     (get-topmost-child-of-block
			       (car listed-next-subblock?))
			     (get-topmost-child-of-block
			       superblock))))
		 (when (and next-item (loose-end-p-function next-item))
		   (setf next-item (find-next-non-loose-end remaining-subblocks)))
		 (setf (cdr remaining-subblocks)
		       (slot-value-cons block listed-next-subblock?))
		 (when (and g2-has-v5-mode-windows-p
			    workspace?
			    (frame-of-class-p workspace? 'kb-workspace))
		   (send-ws-representations-item-insert-as-subblock
		     block superblock
		     next-item))  ;  -pbk 10/10/95 
		 (return nil))
       #+subblocks-v2
       (loop with constant-queue = (subblocks superblock)
	     with head = (constant-queue-head constant-queue)
	     for queue-element = #-Lockfree-Deque head
				 #+Lockfree-Deque
				 (constant-queue-next head constant-queue)
			    then next-queue-element
	     until #-Lockfree-Deque (eq queue-element constant-queue)
		   #+Lockfree-Deque (null queue-element)
	     for next-queue-element = (constant-queue-next queue-element constant-queue)
	     for subblock = (when #-Lockfree-Deque (neq next-queue-element constant-queue)
				  #+Lockfree-Deque next-queue-element
			      (queue-datum next-queue-element))
	     when #-Lockfree-Deque (eq next-queue-element constant-queue)
		  #+Lockfree-Deque (null next-queue-element)
	       do
		 (constant-queue-insert-after constant-queue queue-element block)
		 (when (and g2-has-v5-mode-windows-p
			    workspace?
			    (frame-of-class-p workspace? 'kb-workspace))
		   (send-ws-representations-item-insert-as-subblock
		     block superblock
		     'bottom))
		 (return nil)
	     unless (opaque-block-p subblock) ; after all opaque blocks
	       do
		 (when (and g2-has-v5-mode-windows-p
			    workspace?
			    (frame-of-class-p workspace? 'kb-workspace))
		   (setf next-item
			 (if (eq workspace? superblock)
			     (get-topmost-child-of-block subblock)
			     (get-topmost-child-of-block superblock))))
		 (when (and next-item (loose-end-p-function next-item))
		   (setf next-item
			 (find-next-non-loose-end-in-queue constant-queue next-queue-element)))
		 (constant-queue-insert-after constant-queue queue-element block)
		 (when (and g2-has-v5-mode-windows-p
			    workspace?
			    (frame-of-class-p workspace? 'kb-workspace))
		   (send-ws-representations-item-insert-as-subblock
		     block superblock
		     next-item))
		 (return nil))))

    ;; Maintain layer position, optimizing the case of a simple block added to
    ;; the top layer.
    (when workspace?
      (let ((first-subblock? (first-subblock workspace?))
	    (second-subblock? (second-subblock workspace?)))
	(cond ((or (neq block first-subblock?)
		   (has-subblocks-p block)
		   (connections block))
	       (invalidate-layer-positions workspace?))
	      ((null second-subblock?)
	       (ensure-layer-positions workspace?)
	       (setf (layer-position-of-block block) 0))
	      (t
	       (ensure-layer-positions workspace?)
	       (setf (layer-position-of-block block)
		     (1+f (layer-position-of-block second-subblock?)))))))

    ;; Transformed state.
    (update-block-is-transformed-if-necessary block superblock)
    
    ;; Permanent-transient state.
    (add-as-inferior-block block superblock)

    ;; Activation state.
    (update-new-subblock-activation-and-propagate block superblock)
    (when (and (connections block)
	       (frame-of-class-p superblock 'kb-workspace)
	       (not (frame-of-class-p block 'loose-end)))
							    ; see note C
      (update-new-subblock-connections-activation-and-propagate block superblock))

    ;; Simulation State.
    (install-superblock-in-model-if-appropriate block superblock)

    ;; Connection Post Installation State.
    (handle-connection-post-addition-or-removal-as-subblock block nil)
  
  block))

;; Note A: Consider having a variant of this that adds block at the end of the
;; subblocks list (i.e. to the bottom).

;; NOTE C: The update-new-subblock-connections-activation-and-propagate call
;; fixed a bug, i.e.  it used not happen when doing a transfer action.  It did
;; happen when doing a manual transfer i.e.  "New ...", "Clone", "Create
;; Instance, "Transfer", etc.  from a menu.  It used to be called from
;; update-activate-status-of-connection-frames-being-placed instead of here.  It
;; used not to happen when doing a transfer action, which was a bug.  Analagous
;; code is in remove-as-subblock-if-necessary. (MHD 4/1/91)
     
;; NOTE D: The explicit call to note-change-to-block is now needed because the
;; (new for 4.0) list surgery bypasses the slot setf method, bypassing this call
;; there.  (MHD 1/19/93)




;;; The function `compute-workspace-caches-after-reading' is called after
;;; reading a workspace from a KB.  It's needed since KB reading does
;;; not call add-subblock.

(defun compute-workspace-caches-after-reading (workspace)
  (loop for block being each subblock of workspace
	count t into nblocks
	count (opaque-block-p block) into nopaque
	finally
	  (setf (number-of-blocks-on-workspace workspace) nblocks
		(number-of-opaque-blocks-on-workspace workspace) nopaque)))
	



;;; `Update-new-subblock-activation-and-propagate' ... to be called right after
;;; block has become a member of superblock's subblocks list.

(defun update-new-subblock-activation-and-propagate (block superblock)
  (cond ((active-p superblock)
	 (funcall-method-macro 'activate-if-possible-and-propagate block))
	((or (manually-disabled-p superblock)
	     (frame-status superblock) 	; changed back to macro (MHD 10/19/90)
	     (ancestor-not-activatable-p superblock))
	 (funcall-method 'deactivate-and-propagate block t))
	(t
	 (funcall-method-macro 'deactivate-and-propagate block nil))))






;;; `Remove-as-subblock-if-necessary' is the inverse of add-subblock, except it
;;; maybe called on blocks that aren't actually subblocks.  It returns the
;;; block.

;;; In addition to updating the simulator, activation, opaque block, and
;;; transient/permanent state.  It also removes the block from any pending
;;; drawing recorded in the remaining-subblocks-of-workspace-to-draw slot of
;;; associated image-planes.

;;; If this is the last block of a temporary workspace that workspace is
;;; deleted.

;;; Dont-remove-as-inferior?, a second, optional parameter, allows several of
;;; the changes that have to happen when a block changes position in the
;;; workspace hierarchy to be suppressed.  This includes allowing the
;;; deactivation step to be supressed.  This is used when transfering a block
;;; from one workspace to another.

;;; Note that the block should already have been erased.

;; - ben 3/24/93

;;; `Remove-as-subblock' is about the same, only slightly lower-level.  Block
;;; must be a subblock of superblock, which must be supplied as the second
;;; argument.  The final argument is the same as for
;;; remove-as-subblock-if-necessary, except it's required.  Otherwise, these two
;;; functions are identical.

;; (MHD 1/20/93)

(defun remove-as-subblock-if-necessary
    (block &optional dont-remove-as-inferior?)
  (let ((superblock? (superblock? block))
	(workspace? nil))

    (cond (superblock?
	   (remove-as-subblock block superblock? dont-remove-as-inferior?)
	   (when (and (framep  superblock?)
		      (frame-of-class-p superblock? 'table))
	     (remove-block-as-cell-of-table block superblock?)))

	  ((and (frame-of-class-p block 'connection)	    ; Note A
		(setq workspace? (workspace-of-connection-frame block)))
	   (maintain-workspace-caches-for-remove-block workspace? block))
	  
	  ;; This case is probably not needed.  Only connection-frame's can
	  ;; have a workspace and yet a null superblock.
	  ((setq workspace? (get-workspace-if-any block))
	   (maintain-workspace-caches-for-remove-block workspace? block)))
    block))

;; Note A: connection-frames always have null superblocks (and hence workspace),
;; even though they may appear in our change-blocks list on workspaces.  So,
;; we have to really get their workspace here and update the caches.  There is
;; a similar code change in delete-frame. -fmw, 12/29/94


(defun-simple remove-as-subblock
    (block superblock dont-remove-as-inferior?)
  (let* (#-subblocks-v2
	 (updated-subblocks-of-superblock nil)
	 (workspace?
	   (if (workspace-p superblock)
	       superblock
	       (get-workspace-if-any block)))
	 ;; Discard a temporary workspace if this is the last IMMEDIATE subblock
	 ;; of the workspace (see Note C, Note D)
	 (discard-superblock-at-end-p
	   (and workspace?
		(eq workspace? superblock)
		(and (temporary-workspace-p workspace?)
		     (or (has-only-one-subblock-p superblock)
			 (temporary-workspace-is-for-virtual-attribute-table-p
			   workspace?)))))) ; Note D

    ;; Connection Post Installation State.
    ;; Note that this must be called before the superblock? of block is
    ;; cleared (i.e., set to NIL).  - cpm, 4/5/94
    (handle-connection-post-addition-or-removal-as-subblock block t)
    
    (when workspace?
      (maintain-workspace-caches-for-remove-block workspace? block)
      (note-remove-as-subblock-for-selection block superblock))
    
    ;; KB Hierarchy and Module Hierarchy
    (unless dont-remove-as-inferior?
      (remove-as-inferior-block block superblock))      

    ;; Subblock Hierarchy.
    (setf (superblock? block) nil)
    (when (and workspace? g2-has-v5-mode-windows-p)
      (send-ws-representations-item-remove-as-subblock block workspace?)) ; -pbk, 10/19/95
    ;; so we don't get loose-ends etc.
    (when (and workspace? (frame-of-class-p block 'item))
      (update-subscriptions-for-remove-item-from-workspace workspace? block))

    #-subblocks-v2
    (setf (subblocks superblock)
	  (setq updated-subblocks-of-superblock
		(delete-slot-value-element block (subblocks superblock))))
    #+subblocks-v2
    (constant-queue-search-and-delete (subblocks superblock) block)

    #+mtg2
    (remove-as-faction-member block)     

    ;; Activation State
    (unless dont-remove-as-inferior?
      (funcall-method-if-any-macro 'deactivate-and-propagate block nil)
      (when (and (connections block)
		 (frame-of-class-p superblock 'kb-workspace)
		 (not (frame-of-class-p block 'loose-end)))
	;; Note B
	(update-removed-subblock-connections-activation-and-propagate block)))

    ;; Simulation State.
    (install-superblock-in-model-if-appropriate block superblock)

    (when discard-superblock-at-end-p
      (delete-frame superblock))

    block))


  ;; Note B: See note about
;; update-removed-subblock-connections-activation-and-propagate on add-block.
;; -- ben 3/24/93

;; Note C: In addition to this indirect way of deleting a temporary workspace
;; when its only subblock is deleted, the user interface should do it directly,
;; for speed.

;; Note D: Added the case of a pop-up virtual attribute table being deleted --
;; it currently appears on a temporary workspace with a couple of peripheral
;; blocks, but it should be handled the same as a classic attributes table, and
;; have its workspace deleted when it gets deleted.  This mostly comes up when
;; the item the table represents is deleted, which causes the table to be
;; deleted.  The code to explicitly delete the table handles this
;; explicitly.. (MHD 7/18/02)

;; changes made by pbk 11/3/95 to add in hooks for v5-telewindows







;;; Additional functions used to aid in the transformation to the new telewindows
;;; by pbk 11/3/95.  Trying to transform all layer changes, subblock additions,
;;; and subblock removals into primitive insertions and deletions. Have not as of
;;; yet transformed add-as-subblock into these terms but rather just placed signals
;;; to telewindows that the equivalence of such a command has been performed.
;;; `primitive-insert-as-subblock' and `primitive-remove-as-subblock' have only been
;;; used in the ui-commands raise-to-top and drop-to-bottom.

(defun insert-before-item (block1 block2 superblock)
  (declare (ignorable block1 block2 superblock))
  #-subblocks-v2
  (error "insert-before-item-to-be-defined-later~%")
  #+subblocks-v2
  (loop with constant-queue = (subblocks superblock)
	with head = (constant-queue-head constant-queue)
	for queue-element = #-Lockfree-Deque head
			    #+Lockfree-Deque (constant-queue-next head constant-queue)
		       then (constant-queue-next queue-element constant-queue)
	until #-Lockfree-Deque (eq queue-element constant-queue)
	      #+Lockfree-Deque (null queue-element)
	when (eq block2 (queue-datum queue-element))
	  do (constant-queue-insert-before constant-queue queue-element block1)
	     (loop-finish)))

(defun primitive-insert-as-subblock (block superblock position-or-next-item)
  (cond ((eq position-or-next-item 'top)
	 #-subblocks-v2
	 (setf (subblocks superblock)
	       (slot-value-cons
		 block (subblocks superblock)))
	 #+subblocks-v2
	 (unless (subblocks superblock)
	   (setf (subblocks superblock) (make-empty-constant-queue)))
	 #+subblocks-v2
	 (constant-queue-filo-enqueue (subblocks superblock) block))
	((eq position-or-next-item 'bottom)
	 #-subblocks-v2
	 (setf (subblocks superblock)
	       (nconc (subblocks superblock)
		      (slot-value-list block)))
	 #+subblocks-v2
	 (unless (subblocks superblock)
	   (setf (subblocks superblock) (make-empty-constant-queue)))
	 #+subblocks-v2
	 (constant-queue-enqueue (subblocks superblock) block))
	((frame-of-class-p position-or-next-item 'block)
	 (insert-before-item block position-or-next-item superblock))
	(t
	 (error "item could not be inserted~%"))))

;; case 3 not used as of yet 12/4/94

(defun primitive-remove-as-subblock (block superblock)
  #-subblocks-v2
  (setf (subblocks superblock)
	(delete-slot-value-element block (subblocks superblock)))
  #+subblocks-v2
  (constant-queue-search-and-delete (subblocks superblock) block))

;;; The function `maintain-workspace-caches-for-remove-block' is called
;;; whenever a block which has a workspace is removed from that workspace.

(defun maintain-workspace-caches-for-remove-block (workspace block)
  (note-change-to-workspace-geometry workspace)
  
  ;; Update, or completely remove the spatial index.
  (update-spacial-index workspace block 'remove)
  
  ;; Only top-level subblocks?
  (setf (number-of-blocks-on-workspace workspace)
	(maxf 0 (1-f (number-of-blocks-on-workspace workspace))))
  
  (when (opaque-block-p block)
    (setf (number-of-opaque-blocks-on-workspace workspace)
	  (maxf 0 (1-f (number-of-opaque-blocks-on-workspace workspace)))))

  ;; Remove from Drawing Queues.
  (remove-block-from-drawing-queues workspace block)

  ;; See note.
  (remove-subblocks-and-connections-from-drawing-queues workspace block))


;; Note: We must remove subblocks now since during the recursive descent of
;; delete-frame, by the time we reach the subblocks they have forgotten their
;; workspace.  Connections, however, do not have this problem since they DO
;; remember their workspace, which is why we can use do-subblocks rather than
;; do-subblocks-and-connections here, which would be a macro forward reference.
;; This was the fix for HQ-364604.  See also `remove-thing-from-spacial-index'.

;; This doesn't bother to recompute layer positions, since their relative
;; values are still valid after removing a block, and we only care about the
;; relative values.





;;; The function `remove-block-from-drawing-queues' removes the newly deleted
;;; block from all of the drawing queues which mention blocks, namely, the
;;; workspace's list of changed blocks and the `refresh-region/color-of-block'
;;; image-plane drawing tasks.

(defun remove-block-from-drawing-queues (workspace block)
  ;; Workspace queue.
  (when (block-changes block)
    (setf (changed-blocks-of-workspace workspace)
	  (delete-slot-value-element block (changed-blocks-of-workspace workspace)))
    (atomic-decff count-of-pending-workspace-drawing)
    #+SymScale
    (let ((old? (block-changes block)))
      (when (and old? (compare-and-swap (block-changes block) old? nil))
	(reclaim-block-change old?)))
    #-SymScale
    (progn
      (reclaim-block-change (block-changes block))
      (setf (block-changes block) nil)))

  ;; Image-plane queues
  (remove-thing-from-image-plane-drawing-queues workspace block))

;; There are some cases where we should not simply throw away the block
;; changes.  If the block is being removed as a subblock, but not deleted, then
;; the changes should probably be kept.




;;; The function `remove-thing-from-image-plane-drawing-queues' removes all
;;; image-plane drawing queue elements which reference the given block or
;;; connection.

(defun remove-thing-from-image-plane-drawing-queues (workspace block-or-connection)
  (macrolet ((discard-drawing-task (drawing-task)
	       `(progn (reclaim-drawing-task ,drawing-task)
		       (atomic-decff (count-of-enqueued-drawing window)))))

    (loop for image-plane in (image-planes-this-is-on workspace)
	  as schedule = (image-plane-drawing-schedule image-plane)
	  as window = (gensym-window-for-image-plane image-plane)
	  doing
      (queue-delete-macro schedule block-or-connection
			  :key drawing-task-block?
			  :reclaimer discard-drawing-task)
      (setf (remaining-subblocks-of-workspace-to-draw image-plane)
	    (delete-slot-value-element
	      block-or-connection
	      (remaining-subblocks-of-workspace-to-draw image-plane))))))




;;;; Drawing



;;; `Drawing' (as that term is used in AB), refers to the drawing of images of
;;; workspace elements on the current image plane, insofar as those images fit
;;; within the pane for the plane and are not too deep or too small.  If the
;;; current image plane is subject to occlusion, any changes made by drawing
;;; will be projected per the stack of image planes.

;;; Drawing is always done reversibly, by adding (or subtracting) color
;;; differences to (or from) existing color values.  In situations where drawn
;;; objects may overlap freely, this is essential for `animation' and other
;;; forms of incremental updating of images.

;;; Since drawing can only occur within the body of an on-image-plane, `draw
;;; functions' and macros may use the many special variables bound by
;;; on-image-plane.  When erase-instead? is true, every drawing function or
;;; macro should subtract color differences rather than add them, under the
;;; assumption that what it is trying to erase has earlier been drawn and not
;;; yet erased.

;;; Geometric arguments to draw functions and macros are always in the
;;; coordinate system of the window for the current image plane; on-image-plane
;;; guarantees that there will be "access" to this window.  Color arguments to
;;; draw functions and macros are always, as mentioned above, color differences.

;;; All of the operations below apply to the current image plane, i.e., are
;;; usable only within the body of an on-image-plane form, except that
;;; x-in-window, y-in- window, x-in-workspace, and y-in-workspace may be used
;;; outside of this context by supplying an image-plane? argument.  These
;;; operations are designed to be as fast as possible.



;;; `Draw' is a class method defined directly or indirectly on most
;;; subclasses of block.  It is not defined on block.  It takes a
;;; block as an argument and returns no useful values.

;;; The draw method is responsible for drawing the subblocks of the
;;; block, and any output connections on the block.  It is not
;;; responsible for drawing any overlapping blocks.  It should invoke
;;; draw-subblocks, or draw-subblocks-and-connections as the last
;;; thing it does.

;;; Blocks that want to be rendered in XOR, even when painting, may be required
;;; to utilize `with-deferred-xor-drawing', see that routine for additional
;;; information.

;;; The draw method is invoked in an on-image-plane dynamic extent.
;;; That extent controls issues of scalling, color, transfer mode,
;;; erase/draw.  They are a primary example of a `draw-function' and
;;; hence must obey those rules.

;;; The draw method may be called in one of two ways: KB updates or
;;; window updates.  KB updates are done via update-images and done to
;;; propogate a change to the block's state into the display(s).
;;; Window updates are done via work--drawing-workspace and are done
;;; to propogate a change to the window's layout.

;;; Draw methods never invoke their superior method.

;;; Bits on the object may control rendering details, for example
;;; `render-frame-in-xor-overlay', and `block-is-currently-being-dragged'.

(def-generic-method draw (block))



;;; The function `draw' simply invokes the draw method for the block.  It's
;;; handy place to insert tracing in development.

(defun-substitution-macro draw (block)
  (with-drawing-trace (draw-block)
    (format t "Draw ~s ~d ~d ~d ~d  ~s~%"
	    (if (xor-mode-p) 'xor 'pnt)
	    left-edge-of-draw-area
	    top-edge-of-draw-area
	    right-edge-of-draw-area
	    bottom-edge-of-draw-area
	    block))
  (funcall-method 'draw block))



;;; The draw method is responsible for the block's subblocks and connections.
;;; This is almost always done by invoking `draw-subblocks', or 
;;; `draw-subblocks-and-connections'.  This is done last so that the subblocks
;;; and connections lie over the block in the drawing.

#+unused
(defmacro draw-subblocks (block)
  (unless (symbolp block)
    (warn "draw-subblocks requires a symbol, not ~S" block))
  `(when (has-subblocks-p ,block)
     (loop for subblock being each subblock of ,block
	   do (draw subblock))))



;;;; Frame Descriptions and Projection

;;; Frame projection is used to draw a frame (ala picture frame) around an
;;; object.  The routine `project-frame' does just that as guided by a
;;; `frame-description' for example something along these lines:
;;;   (
;;;     (border (black 1))
;;;     (frame-section (top 16)
;;;        (title-bar))
;;;     (frame-section (bottom 16 nil 16)
;;;        (horizontal-scroll-bar)
;;;        (resize-box))
;;;     (frame-section (right 16)
;;;        (vertical-scroll-bar))
;;;     (border (transparent 3))

;;; Frame descriptions consist of little programs executed by an interpreter
;;; found here.  These descriptions construct the frame, from the exterior
;;; bounding box in.  Each component of the frame consumes some of the bounding
;;; box, leaving less and less for the framed object.  At each step in the
;;; interpretation the current bounding box is available in the
;;; `frame-projecting' dynamic extent in `{left,top,right,bottom}-edge-of-frame'

;;; The input to the frame drawing process is a rectangle, and its output is
;;; another rectangle set inside of the first. The amount of inset may be
;;; different for each edge (e.g., the left edge may inset only a few pixels for
;;; a border, while the right edge may inset a lot to draw both a border and
;;; along with a scroll bar), but it must be constant for a given frame
;;; description.

;;; In the example given above, there are five statements. Each consumes a chunk
;;; of the bounding rectangle, progressively reducing its size.  For example the
;;; second statement takes 16 window units off the top of the bounding rectangle
;;; and places a title-bar in that sections.

;;; Frames may be projected for any one of six purposes: drawing-paper,
;;; drawing-contents, drawing, compute-content-region, move-elevator, and
;;; mouse-tracking.  The variable `current-purpose-of-frame-projecting' is bound
;;; to one of these symbols.

;;; `Drawing-paper' is used only when drawing an empty image-plane as part of
;;; exposing, prior to scheduling the drawing of the rest of the image. It
;;; should implement a strict subset of the draw operation, and use only
;;; painting.  It is supposed to be a "quick sketch" of what the image plane is
;;; going to look like, giving the user some immediate feedback.  As such, it
;;; must execute quickly.  Currently, it draws the frame and the background,
;;; including images (probably should not include images).
;;; `Drawing-frame' draws the frame and background in full detail.
;;; `Drawing-contents' draws, at full resolution, everything but the frame and
;;; background. It is used by scheduled drawing to pick up where drawing-frame
;;; left off.  What the contents are is determined by the functional argument
;;; handed to project-frame.
;;; `Drawing' is equivalent to drawing-frame followed by drawing-contents, that is
;;; it draws the entire block at full resolution.
;;; `Compute-content-region' computes the bounding box of the content region, the
;;; part inside of the frame.  It does no drawing.
;;; `Mouse-tracking' computes the object under to a mouse position.  it also does
;;; no drawing.

;;; `Move-Elevator' is called to move the elevator position, updating slots in of the
;;; frame's block and updating images as necessary.  This does not update the
;;; frame's content; the caller is responsible for doing that.  In this mode
;;; we are not a draw-function.  This mode is invoked via the routine move-elevator.


;; Drawing-paper might be better named drawing-sketch

;;; When `drawing' or `drawing-paper' project-frame is a `draw-function.'

;;; When `drawing' `drawing-contents' or `drawing-paper' project-frame is a
;;; `draw-function.'

;;; `Orientation-of-frame' is bound within frame-projecting to one of three
;;; values SQUARE, HORIZONTAL, VERTICAL.  Some frame components are rendered
;;; differently by this.

(def-dynamic-extent (frame-projecting (module draw))
  (purpose-of-frame-projecting)
  (control-stack-of-frame-projecting)
  (orientation-of-frame)
  (current-slice-size?)
  (left-edge-of-frame)					    ; Outer edges of frame in parent's coordinates.
  (top-edge-of-frame)
  (right-edge-of-frame)
  (bottom-edge-of-frame)
  (remaining-space-for-variable-size-pieces-of-frame)
  (remaining-number-of-size-pieces-of-frame)
  (partition-details-of-current-branch-of-frame)
  (mouse-pointer-of-frame)
  (block-of-frame)
  (frame-transform-of-frame)
  (new-position-of-horizontal-elevator-of-frame)
  (new-position-of-vertical-elevator-of-frame))


;;; The macro `inhibit-drawing-subblocks-in-harness-p' returns T for blocks
;;; which maintain a "private" list of subblocks, hidden from the drawing
;;; harness.  This means that drawing treats them as a single block -- their
;;; subblocks are never returned as overlapping blocks to clean up, and the
;;; draw methods of their subblocks are never called (by the harness, that is).

(def-substitution-macro inhibit-drawing-subblocks-in-harness-p (block)
  ;; opaque-block-p would work here (since all other opaque-blocks do not
  ;; have subblocks), and is a faster test.
  (eq (class block) 'graph))

;; Might want this for all tables, too, so that the Gensym icon can
;; appear sooner in the copyright workspace.


(def-substitution-macro block-possibly-overlaps-workspace-rectangle?
    (block left top right bottom)
  (or (and (subblocks block)
	   (not (inhibit-drawing-subblocks-in-harness-p block)))
      (connections block)
      (rectangles-overlap-p left top right bottom 
			    (left-edge-of-block block)
			    (top-edge-of-block block)
			    (1+f (right-edge-of-block block)) ; Icon overflow
			    (1+f (bottom-edge-of-block block)))))



;;; The substitution-macro `block-possibly-overlaps-rectangle?' is true if the
;;; given block or its subblocks or connections could possibly overlap the
;;; given rectangle, in window coordinates.

(def-substitution-macro block-possibly-overlaps-rectangle? (block left top right bottom)
  (or (and (subblocks block)
	   (not (inhibit-drawing-subblocks-in-harness-p block)))
      (connections block)
      (rectangles-overlap-p left top right bottom 
			    (x-in-window (left-edge-of-block block))
			    (y-in-window (top-edge-of-block block))
			    (x-in-window (1+f (right-edge-of-block block)))
			    (y-in-window (1+f (bottom-edge-of-block block))))))



;;; The substitution-macro `block-possibly-overlaps-draw-area?' is a cheap test
;;; of whether any of the ink which is sprayed as the result of drawing this
;;; block, including its subblocks and connections, could possibly overlap the
;;; current drawing area.  Notice that we punt on blocks with connections or
;;; subblocks.

(def-substitution-macro block-possibly-overlaps-draw-area? (block)
  (block-possibly-overlaps-rectangle?
    block
    left-edge-of-draw-area
    top-edge-of-draw-area
    right-edge-of-draw-area
    bottom-edge-of-draw-area))



;;; The `workspace-background-spot' is used to describe the area of a workspace
;;; that includes the margins, and those pars of the interior that have
;;; no blocks sufficently close to the mouse.

(def-spot workspace-background-spot
    :include spot
    :enclosing-spot-type image-plane-spot
    :innermost-spot-p t
    :abstract-type nil
    :type-of-frame-represented workspace)


;;; `Make-workspace-background-spot-function' is needed to fufill a forward
;;; reference in panes that arises when the initialization of mouse tracking
;;; discovers that the initial bindings for an image-plane are inaccurate, i.e.
;;; that type ahead has been confused by rearranging of the image-planes.

(defun make-workspace-background-spot-function ()
  (make-workspace-background-spot))



;;; The `title-bar-spot' ...

(def-spot title-bar-spot
    :include spot
    :enclosing-spot-type image-plane-spot
    :innermost-spot-p t
    :abstract-type nil
    :type-of-frame-represented workspace)

(defun make-title-bar-spot-function ()
  (make-title-bar-spot))





;;;; Overlapping Cache



;; The overlapping cache routines, including cleanup-overlapping-blocks, are in
;; CONNECT3A, in order to pick up the flag bits on connections.


;;;; Drawing a Workspace




;;; This section implements the refresh drawing of a region of a workspace.

;;; Some things complicate drawing the workspace.  In the presence XOR'd
;;; drawing when we are using true color or opaque drawing when we are using
;;; false color we need to draw the an overlay of the unsual blocks.  During
;;; the drawing of a workspace we may exhaust our quantum.  In which case we
;;; must enqueue some continuation of the drawing to allow us to pick up the
;;; drawing later.  During the drawing of a workspace we may notice that user
;;; events have appeared in the input Q, most important among these are events
;;; that will entirely invalidate the drawing we have in progress. For example,
;;; a request to scale the workspace.

;;; Drawing on a workspace establishes a dynamic extent
;;; `working-on-drawing-workspace' that manages these problems.

;;; Drawing on a workspace is invoked with in an on-image-plane context.
;;; Usually in response to a drawing task being popped off the image-plane
;;; drawing schedule.

(def-named-dynamic-extent working-on-drawing-workspace
  (dynamic-superior for-image-plane)
  (module draw))


;;; The variable `currently-working-on-drawing-workspace' really means "inside
;;; of a deferrable XOR drawing context."

(defvar-of-named-dynamic-extent currently-working-on-drawing-workspace
    working-on-drawing-workspace
  (process-binding nil))



;;; `With-deferred-xor-drawing' is used to schedule deferred XOR drawing.

;;; Portions of the workspace that are highlighted using XOR, say to provide
;;; cursors or selection, must be drawn after all other drawing in the
;;; workspace to achieve the approprate effect.  When drawing a workspace we
;;; accumulate a set of such things in the `remaining-xor-drawing-activities'
;;; slot of the current image plane, in the form of a tree of slot-value cons.
;;; Each element in the list is of the form
;;;      (<compiled-function> <block-or-connection> <reference-serial-number> <arg> ...)
;;; These are all called and removed from the list whenever
;;; work-on-drawing-workspace exits.

;;; The tasks guard against unexpected reclaimation in spite of the fact their
;;; lifecycle is limited to within one micro task.  That's the reason for the
;;; two required arguments.  The Q manager does not check the reference-serial
;;; number for the task.

;;; The handler is invoked using funcall-simple-compiled-function.  The function
;;; is invoked with the current-drawing transfer mode bound to :XOR.

;;; The task is responsible for reestablishing any dynamic extent beyond that
;;; established for the entire workstation context.  I.e. scrolling or scaling
;;; in addition to that of the image-plane.


(defun-substitution-macro find-deferred-drawing-task (compiled-function block-or-connection)
  (loop for (fun blk) in (remaining-xor-drawing-activities current-image-plane)
	thereis (and (eq fun compiled-function)
		     (eq blk block-or-connection))))



;;; The macro `with-deferred-xor-drawing' evaluates the given form
;;; either immediately and in XOR mode, if we are not inside of 
;;; workspace drawing, or defered, if we are.  This is how XOR drawing
;;; gets lifted into the XOR overlay.

(defmacro with-deferred-xor-drawing
    ((function block-or-connection reference-serial-number &rest args)
     &optional undeferred-form)
  `(cond
     (currently-working-on-drawing-workspace
      (unless (find-deferred-drawing-task #',function ,block-or-connection)
	(slot-value-push
	  (slot-value-list #',function ,block-or-connection
			   (copy-frame-serial-number ,reference-serial-number)
			   ,@args)
	  (remaining-xor-drawing-activities current-image-plane))))

     (t
      (with-transfer-mode-when-drawing (:xor)
	,(or undeferred-form
	     `(,function ,block-or-connection ,reference-serial-number ,@args))))))

;; One problem with this macro is that sometimes we want to call a different
;; draw function depending on whether we were deferred or not.



;;; `maybe-defer-refreshing-image-plane' returns true if we can hold off
;;; refreshing this image-plane.  The prime example of this arises when a user
;;; types a series of N scaling commands.  This holds off drawing the workspace
;;; at each of the N scales.  If this predicate begins returning true then
;;; later service-workstation will end the hold and refresh the workspace.

;;; We peek into the input queue for events that will refresh this this
;;; workspace.  Actually the event's workstation-event-type of the event must be
;;; marked refreshes-image-plane-p.

;;; The peek is done as follows.  First to avoid calling poll-workstation we
;;; only check the presence of events in the workstation-event-queue.  User
;;; input generated "too late" will have no effect.  If there is input in the
;;; queue we interpret/handle the first of that input to discover the
;;; "workstation-event-type." Finally if the workstation-event-type type is
;;; marked a refreshes-image-plane-p we return true.

;;; If we find an event which is going to cause a full refreshing then we stow
;;; the image-plane into image-plane-to-continue-refreshing?  of this
;;; workstation.  That provides cached awnser for futher checks, but more
;;; importantly allows service workstation to force the refresh as soon as no
;;; more events that might refresh the window are found in the input queue.
;;; Service-workstation calls continue-refreshing-image-plane to clear
;;; image-plane-to-continue-refreshing?  and to finally do the deferred
;;; refreshing.

;;; The implementation of this facility found in PLATFORMS, PANES, DRAW, 
;;; and WORKSTATIONS.

;; - ben 2/23/93

(defvar-of-named-dynamic-extent workstation-with-image-plane-being-refreshed
				working-on-drawing-workspace)

#+development
(defun print-drawing-queues (&optional image-plane-or-workspace (max-length 5))
  (flet ((F (image-plane)
	   (let ((queue (image-plane-drawing-schedule image-plane))
		 (length (length (remaining-subblocks-of-workspace-to-draw image-plane))))
	     (when queue
	       (format t " Drawing queue for ~s has ~d element~:p (~d block~:p):~%"
		       image-plane
		       (queue-length queue)
		       length)
	       (loop for e being each queue-element of queue
		     for i below max-length
		     do (format t "  [~d] ~s~%" i e))))))

    (let ((*print-pretty* t)
	  (thing (or image-plane-or-workspace
		     (and (boundp 'current-image-plane) current-image-plane)
		     (and (boundp 'current-workstation) current-workstation)
		     (and (boundp 'current-window) current-workstation)
		     (first workstations-in-service))))
      
      (cond ((image-plane-p thing)
	     (F thing))
	    ((workstation-p thing)
	     (dolist (pane (panes-in-window (window-for-workstation thing)))
	       (dolist (image-plane (stack-of-image-planes pane))
		 (F image-plane))))
	    ((and (framep thing) (workspace-p thing))
	     (dolist (image-plane (image-planes-this-is-on thing))
	       (F image-plane))))
      thing)))




;;;; Drawing Blocks


;; NOTE: the function is not used anywhere. --binghe
(defun subblocks-for-drawing (block)
  (unless (inhibit-drawing-subblocks-in-harness-p block)
    (subblocks block)))



(def-substitution-macro draw-block-and-subblocks-macro
    (block recurse-to-subblocks?)
  (cond ((render-frame-in-xor-overlay-p block)
	 (with-deferred-xor-drawing
	   (deferred-draw-block block (frame-serial-number block))
	   (draw block)))
	(t
	 (draw block)))

  (when (and recurse-to-subblocks?
	     (not (inhibit-drawing-subblocks-in-harness-p block)))
    (when (has-subblocks-p block)
      (loop for subblock being each subblock of block
	    do (draw-block-and-subblocks subblock recurse-to-subblocks?)))

    (when (connections block)
      (draw-connections-for-block block))))



;;; The function `draw-block-and-subblocks' calls the block's draw method with
;;; the correct drawing transfer mode. Subblocks and connections are optionally
;;; drawn also.  The recurse-to-subblocks? is certainly ugly.

(defun draw-block-and-subblocks (block recurse-to-subblocks?)
  (draw-block-and-subblocks-macro block recurse-to-subblocks?))




(defun-simple deferred-draw-block
    (block reference-frame-serial-number)
  (when (frame-has-not-been-reprocessed-p block reference-frame-serial-number)
    ;; We only want the frame if we were truely deferred?
    (with-frame-transform-of-block-if-any (block)
      (draw block))))




;;; The substitution-macro `draw-block-macro' is a slightly bummed version of
;;; draw-block for use when refreshing regions.

(def-substitution-macro draw-block-macro (block)
  (cond ((null (block-is-transformed-p block))
	 (draw-block-and-subblocks-macro block t))
	(t
	 (draw-block-possibly-with-frame block t))))

;; Almost all blocks are not transformed.


  

;;; The function `draw-block-possibly-with-frame' draws the given block,
;;; possibly within a frame.  Optionally, it recursively draws subblocks and
;;; connections.

(defun draw-block-possibly-with-frame (block recurse-to-subblocks?)
  (let (frame-transforms-of-block)
    (cond
      ((null (block-is-transformed-p block))
       ;; No framing, so just draw it.
       (draw-block-and-subblocks block recurse-to-subblocks?))

      ((null (setq frame-transforms-of-block (frame-transforms-of-block block)))
       ;; Ancestor had a frame.
       (with-frame-transform-of-block-if-any (block)
	 (draw-block-and-subblocks block recurse-to-subblocks?)))

      (t
       (let* ((frame-transform-of-frame
		(cdr (assq current-image-plane frame-transforms-of-block)))
	      (block-of-frame block)
	      (frame-description-reference
		(frame-description-reference-of-frame-transform
		  frame-transform-of-frame))
	      (left-edge-of-frame
		(-w (left-edge-of-block block)
		    (left-frame-indent frame-description-reference)))
	      (top-edge-of-frame
		(-w (top-edge-of-block block)
		    (top-frame-indent frame-description-reference)))
	      (right-edge-of-frame
		(+w (right-edge-of-block block)
		    (right-frame-indent frame-description-reference)))
	      (bottom-edge-of-frame
		(+w (bottom-edge-of-block block)
		    (bottom-frame-indent frame-description-reference))))
	 (project-frame 'drawing
			(frame-description-of-frame-description-reference
			  frame-description-reference)
			left-edge-of-frame
			top-edge-of-frame
			right-edge-of-frame
			bottom-edge-of-frame
			(if recurse-to-subblocks?
			    #'draw-block-within-frame-1
			    #'draw-block-within-frame-2)))))))


;; This one draws subblocks.
(defun draw-block-within-frame-1 ()
  (with-nested-draw-area? ((x-in-window left-edge-of-frame)
			   (y-in-window top-edge-of-frame)
			   (x-in-window right-edge-of-frame)
			   (y-in-window bottom-edge-of-frame)
			   block-of-frame :frame-interior)
    (with-frame-transform (frame-transform-of-frame)
      (draw-block-and-subblocks block-of-frame t))))


;; This one does not.
(defun draw-block-within-frame-2 ()
  (with-nested-draw-area? ((x-in-window left-edge-of-frame)
			   (y-in-window top-edge-of-frame)
			   (x-in-window right-edge-of-frame)
			   (y-in-window bottom-edge-of-frame)
			   block-of-frame :frame-interior)
    (with-frame-transform (frame-transform-of-frame)
      (draw-block-and-subblocks block-of-frame nil))))





;;; The function `draw-block' draws the block and all of its subblocks,
;;; connections, and frame, and then if necessary repairs any damage done to
;;; overlapping blocks.  This function must be called within the extent of
;;; on-image-plane.  It is used via update-images to draw blocks on workspaces,
;;; and also used to draw blocks being moved (hence the check for XOR overlay).

(defun draw-block (block)
  (draw-block-macro block)
  ;; The above call draws the subblocks, too. So we must clean up
  ;; the extreme area.

  (unless (or (render-frame-in-xor-overlay-p block)
	      (workspace-p block)
	      ;; Not right but less awful, needs more work!! - ben 6/18/93
	      ;; Need to redraw overlappping blocks above us if either we are
	      ;; in paint mode, or, this block is an opaque block.
	      (and (xor-mode-p)
		   (not (opaque-block-p block))))
    (let ((workspace? (get-workspace-if-any-macro block) ))
      (when workspace?
	(draw-overlapping-blocks workspace? block 'above nil)))))

;; This is called by update-images-of-block, for erase and redraw.
;; Probably don't need to fixup overlapping blocks in both cases.
;; Besides, update-images is cleaning up, too.





;;;; Block Scrolling Protocol and Workspace Scrolling






;;; The interface from user commands (etc) to scrolling falls thru
;;; to a call on the `scroll-block' method.  This takes an image-plane,
;;; a step amount (either `page' or `line'), a direction to step, (either
;;; `up' `down' `left' or `right').

(def-generic-method scroll-block (block image-plane amount-of-step direction-of-step)
  )



;;; The `scroll-block method for a block' for block generates a warning in
;;; development, and does nothing in production code. Calling it implies somebody
;;; tried to scroll something that we didn't expect would be scrollable.

(def-class-method scroll-block (block image-plane amount-of-step direction-of-step)
  (declare (ignore #-development block image-plane amount-of-step direction-of-step))
  #+development
  (warn "Scrolling should never be attempted on ~S" block))



;;; The `scroll-block method on a workspace' scrolls 10 percent of the visible
;;; workspace area for `line' and 100% for page.

;; Unused, but hard to prove.
(def-class-method scroll-block (workspace image-plane amount-of-step direction-of-step)
  (declare (ignore workspace))
  (let* ((percent (if (eq 'line amount-of-step) 10 100))
	 (x-percent (case direction-of-step
		      ((up down) 0)
		      (left percent)
		      (t (- percent)))) ; right
	 (y-percent (case direction-of-step
		      ((left right) 0)
		      (up percent)
		      (t (- percent))))) ; down
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
	100))))



;;; `Scroll-frame-transform' erases the block, offsets it's the source rectangle
;;; of the frame transform as given by the argumenats in workspace units, and
;;; then restores it to the screen.

;; This should use screen to screen copybits, and only on the one image plane.

(defun scroll-frame-transform (frame-transform workspace-dx workspace-dy)
  (let ((block (block-of-frame-transform frame-transform)))
    (incff (left-edge-of-source-of-frame-transform frame-transform)
	   workspace-dx)
    (incff (top-edge-of-source-of-frame-transform frame-transform)
	   workspace-dy)
    (incff (right-edge-of-source-of-frame-transform frame-transform)
	   workspace-dx)
    (incff (bottom-edge-of-source-of-frame-transform frame-transform)
	   workspace-dy)
    (map-drawing-over-image-planes
      (get-workspace-if-any block)
      (get-workspace-if-any block)
      (left-edge-of-block block)
      (top-edge-of-block block)
      (right-edge-of-block block)
      (bottom-edge-of-block block)
      nil
      'scroll-entire-block-contents
      block
      workspace-dx workspace-dy)))

;; Mapping over all image-planes is very bogus, but it works since
;; we only have edit-boxes on one image-plane. - ben May 25 95




;;; `Scroll-entire-block-contents' is called on-window-with-drawing with the
;;; frame given by the frame enclosing the block being scrolled.

;;; It uses screen to screen copy to move what it can.  It presumes the block
;;; given will draw it's contents relative to the top left corner of the block's
;;; bounds.  It will scroll, in window offset, and amount that is exactly the
;;; result of how much that corner moved when the frame transform was updated.
;;; It presumes that it was called after the transform was updated.

;;; To compute an accurate delta in window cordinates requires computing the
;;; location of the corner before and after the change to the frame transform.
;;; That's a mess!

(defun scroll-entire-block-contents
    (block delta-x-in-workspace delta-y-in-workspace)
  (let* ((src-left (x-in-window (left-edge-of-block block)))
	 (src-top (y-in-window (top-edge-of-block block)))
	 (src-right (x-in-window (right-edge-of-block block)))
	 (src-bottom (y-in-window (bottom-edge-of-block block))))
    (protected-let*-for-development
	((src-region
	   (make-region-from-rectangle src-left src-top src-right src-bottom)
	   (reclaim-region src-region)))
      (let ((left-edge-of-block (left-edge-of-block block))
	    (top-edge-of-block (top-edge-of-block block))
	    old-x-in-window old-y-in-window
	    new-x-in-window new-y-in-window)
	;; Compute the upper left corner, prior to the change.
	(let ((frame-transform
		(cdr (assq current-image-plane
			   (frame-transforms-of-block block)))))
	  (decff (left-edge-of-source-of-frame-transform frame-transform)
		 delta-x-in-workspace)
	  (decff (top-edge-of-source-of-frame-transform frame-transform)
		 delta-y-in-workspace)
	  (decff (right-edge-of-source-of-frame-transform frame-transform)
		 delta-x-in-workspace)
	  (decff (bottom-edge-of-source-of-frame-transform frame-transform)
		 delta-y-in-workspace)
	  (with-frame-transform-of-block-if-any (block)
	    (setf old-x-in-window (x-in-window left-edge-of-block))
	    (setf old-y-in-window (y-in-window top-edge-of-block)))
	  (incff (left-edge-of-source-of-frame-transform frame-transform)
		 delta-x-in-workspace)
	  (incff (top-edge-of-source-of-frame-transform frame-transform)
		 delta-y-in-workspace)
	  (incff (right-edge-of-source-of-frame-transform frame-transform)
		 delta-x-in-workspace)
	  (incff (bottom-edge-of-source-of-frame-transform frame-transform)
		 delta-y-in-workspace))
	;; Compute the upper left corner now.
	(with-frame-transform-of-block-if-any (block)
	    (setf new-x-in-window (x-in-window left-edge-of-block))
	    (setf new-y-in-window (y-in-window top-edge-of-block)))
      (scroll-region-on-image-plane
	src-region
	src-region
	(-r new-x-in-window old-x-in-window)
	(-r new-y-in-window old-y-in-window))))))



;;; `Scroll-region-on-image-plane' will scroll the given region on the current
;;; image-plane.  A clipping region is also passed, this is presumed to limit
;;; the area the source and destination regions can occupy.

(defun scroll-region-on-image-plane (source-region
				      clip-region
				      delta-x-in-window delta-y-in-window)
  (protected-let*-for-development
      ((clip-visible-region
	 (intersect-region clip-region
			   (visible-region-of-image-plane current-image-plane))
	 (reclaim-region clip-visible-region))
       (destination-region
	 (shift-region (copy-region source-region)
		       delta-x-in-window delta-y-in-window)
	 (reclaim-region destination-region))
       (visible-destination-region
	 (intersect-region destination-region clip-visible-region)
	 (reclaim-region visible-destination-region))
       (offset-destination-region
	 (shift-region (copy-region visible-destination-region)
		       (-r delta-x-in-window) (-r delta-y-in-window))
	 (reclaim-region offset-destination-region))
       (useful-source-region
	 (intersect-region source-region offset-destination-region)
	 (reclaim-region useful-source-region))
       (visible-useful-source-region
	 (intersect-region useful-source-region clip-visible-region)
	 (reclaim-region visible-useful-source-region)))

    (scroll-region-of-current-window
      visible-useful-source-region
      delta-x-in-window delta-y-in-window)

    (protected-let*-for-development
	((visible-source-region
	   (intersect-region source-region clip-visible-region)
	   (reclaim-region visible-source-region))
	 (still-dirty-destination-region
	   (subtract-region visible-destination-region
			    (shift-region visible-useful-source-region
					  delta-x-in-window
					  delta-y-in-window))
	   (reclaim-region still-dirty-destination-region))
	 (now-dirty-source
	   (subtract-region visible-source-region visible-destination-region)
	   (reclaim-region now-dirty-source))
	 (total-dirty-region
	   (union-region now-dirty-source still-dirty-destination-region)
	   (reclaim-region total-dirty-region)))
      (invalidate-region-of-window-when-on-window total-dirty-region))))



#+obsolete
(defun reset-content-of-block (block)
  (erase-images-of-block block t)
  (setf (left-edge-of-content-of-block-1 block)
	(left-edge-of-block block))
  (setf (top-edge-of-content-of-block-1 block)
	(left-edge-of-block block))
  (setf (right-edge-of-content-of-block-1 block)
	(right-edge-of-block block))
  (setf (bottom-edge-of-content-of-block-1 block)
	(bottom-edge-of-block block))
  (draw-images-of-block block t))

#+obsolete
(defun change-size-of-content-of-block
    (block left-delta top-delta right-delta bottom-delta)
  (erase-images-of-block block t)
  (decfw (left-edge-of-content-of-block-1 block) left-delta)
  (decfw (top-edge-of-content-of-block-1 block) top-delta)
  (incfw (right-edge-of-content-of-block-1 block) right-delta)
  (incfw (bottom-edge-of-content-of-block-1 block) bottom-delta)
  (draw-images-of-block block t))









;;;; The Graphic Element




;;; First a historical note.  G2 in versions 1.11B thru 3.0 maintained a cache
;;; or backing store of the screen.  This data structure was known as
;;; graphic-element-memory.  The elements in that memory still exist to provide
;;; a dynamic extent in used when clipping drawing.

;;;  A `graphic element' is a structure that represents a solid rectangle, an
;;;  icon, a sloping line, a line of text, etc.  Only one instance is allocated
;;;  for each process (see graphic-element-projection below).  When we want to
;;;  draw a graphic onto the screen we must clip that graphic in a number of
;;;  ways.  The process of clipping it is known as `projection'.

;;; The clipping process takes place within the dyanmic extent known as 
;;; graphic-element-projection.  During that extent the particulars of the
;;; drawing taking place are recorded in that extent.



;;; A graphic element includes a `graphic element operation' and operation-specific
;;; argument, as follows:
;;;
;;;    paint-solid-rectangle         color-value
;;;
;;;    add-solid-rectangle           color-difference
;;;
;;;    add-icon-rendering            (color-difference-or-list-of-color-differences
;;;                                    . icon-rendering), a graphics cons
;;;
;;;    add-graph-rendering           (color-values-for-rasters
;;;                                    . graph-rendering), a graphics cons
;;;
;;;    add-upward-sloping-line       color-difference
;;;
;;;    add-downward-sloping-line     color-difference
;;;
;;;    add-line-of-text              description-of-line-of-text (see below)
;;;

;;; The list of color differences (for a polychrome icon) is a graphics list
;;; that IS (at least now) to be reclaimed.  Add-graph-rendering graphic
;;; elements occur only transiently, not within graphic element memories, and
;;; thus the allocation properties for their substructures need not be specified
;;; here.

;;; A graphic element also includes four slots that specific a rectangle in a
;;; gensym window (by its left edge, top edge, right edge, and bottom edge, in
;;; that order).  This rectangle need not be entirely within the window, but
;;; should intersect it (though it is not an error for it to be entirely
;;; outside).  For add-upward- sloping-line, the four edges may be interpreted
;;; as: left-end-x, right-end-y, right-end-x, left-end-y.  For
;;; add-downward-sloping-line, the four edges may be interpreted as: left-end-x,
;;; left-end-y, right-end-x, right-end-y.

;;; Finally, a graphic element includes a slot used to link graphic elements (in
;;; "buckets" and recycled element pools).



;;; ??? BEN  -- Think about this! ben 4/2/93
;;; `Reclaim-arbitrary-graphic-element' ... In the case of an add-icon-rendering
;;; graphic-element, this handles the decrementing of the usage count for the
;;; icon rendering.  (The incrementing is done (only) by draw-graphic-element,
;;; in DRAW.)



;;; `Graphic-element-projection' is the named dynamic extent within which 
;;; clipping is performed.  This extent is only used within this module.

(def-dynamic-extent (graphic-element-projection (module draw))
  (operation-of-graphic-element (process-binding nil))
  (left-edge-in-window-of-graphic-element (process-binding nil)) 
  (top-edge-in-window-of-graphic-element (process-binding nil))
  (right-edge-in-window-of-graphic-element (process-binding nil))
  (bottom-edge-in-window-of-graphic-element (process-binding nil))

  ;; Painted Solid Rectangles & Images 
  (foreground-color-value-of-graphic-element (process-binding nil))

  ;; add-solid-rectangle, upward-sloping-line, downward-sloping-line
  (foreground-color-difference-of-graphic-element (process-binding nil))

  ;; Text & Images
  (x-scale-of-graphic-element (process-binding nil))
  (y-scale-of-graphic-element (process-binding nil))

  ;; Images
  (image-data-of-graphic-element (process-binding nil))
  (x-in-window-of-graphic-element (process-binding nil))
  (y-in-window-of-graphic-element (process-binding nil))
  (rotation-of-graphic-element (process-binding nil))
  (quality-of-graphic-element (process-binding nil))
  (background-color-value-of-graphic-element (process-binding nil))

  ;; Graph or Icon Renderings
  (graph-or-icon-rendering-of-graphic-element (process-binding nil))
  (foreground-color-difference-or-differences-of-graphic-element (process-binding nil))
  (color-values-of-graph-rasters-of-graphic-element (process-binding nil))

  ;; Text
  (left-edge-of-line-of-text-in-window-of-graphic-element (process-binding nil))
  (baseline-in-window-for-line-of-text-of-graphic-element (process-binding nil))
  (text-line-for-line-of-text-of-graphic-element (process-binding nil))
  (word-spacing-for-line-of-text-of-graphic-element (process-binding nil))
  (font-map-for-line-of-text-of-graphic-element (process-binding nil))
  (color-difference-for-line-of-text-of-graphic-element (process-binding nil))
  (image-left-offset-in-ws (process-binding nil))
  (image-top-offset-in-ws (process-binding nil))
  (entity-width-in-ws (process-binding nil))
  (entity-height-in-ws (process-binding nil))

  ;; Polylines and Polygons
  (poly-vertices (process-binding nil))
  (poly-line-width (process-binding nil))
  (poly-line-pattern (process-binding nil))
  (poly-line-style (process-binding nil))

  ;; Polygons
  (polygon-fill-color-difference (process-binding nil)) ; fg color used for line-color
  (polygon-fill-pattern (process-binding nil)))

(defun-void fill-out-current-graphic-element
    (graphic-element-operation
      new-left-edge-of-graphic-element-in-window
      new-top-edge-of-graphic-element-in-window
      new-right-edge-of-graphic-element-in-window
      new-bottom-edge-of-graphic-element-in-window
      arg1 arg2 arg3 arg4 arg5 arg6 arg7 arg8)
  (setf operation-of-graphic-element graphic-element-operation)
  (setf left-edge-in-window-of-graphic-element new-left-edge-of-graphic-element-in-window)
  (setf top-edge-in-window-of-graphic-element new-top-edge-of-graphic-element-in-window)
  (setf right-edge-in-window-of-graphic-element new-right-edge-of-graphic-element-in-window)
  (setf bottom-edge-in-window-of-graphic-element new-bottom-edge-of-graphic-element-in-window)
  (case graphic-element-operation

    (add-line-of-text 
     (setf text-line-for-line-of-text-of-graphic-element arg1)
     (setf word-spacing-for-line-of-text-of-graphic-element arg2)
     (setf font-map-for-line-of-text-of-graphic-element arg3)
     (setf color-difference-for-line-of-text-of-graphic-element arg4)
     (setf x-scale-of-graphic-element arg5)
     (setf y-scale-of-graphic-element arg6)
     (setf left-edge-of-line-of-text-in-window-of-graphic-element arg7)
     (setf baseline-in-window-for-line-of-text-of-graphic-element arg8))
    
    (add-icon-rendering 
     (setf foreground-color-difference-or-differences-of-graphic-element arg1)
     (setf graph-or-icon-rendering-of-graphic-element arg2))
    
    (add-graph-rendering  
     (setf color-values-of-graph-rasters-of-graphic-element arg1)
     (setf graph-or-icon-rendering-of-graphic-element arg2)
     nil)
    
    (paint-solid-rectangle
     (setf foreground-color-value-of-graphic-element arg1))

    ((add-solid-rectangle
       add-upward-sloping-line
       add-downward-sloping-line)
     (setf foreground-color-difference-of-graphic-element arg1))
    
    (paint-image 
     (setf image-data-of-graphic-element arg1))

    (paint-icon-background-image
     (setf image-data-of-graphic-element arg1)
     (setf image-left-offset-in-ws arg2)
     (setf image-top-offset-in-ws arg3)     
     (setf entity-width-in-ws arg4)
     (setf entity-height-in-ws arg5))

    (add-wide-polyline
     (setq foreground-color-difference-of-graphic-element arg1
	   poly-line-width arg2
	   poly-line-pattern arg3
	   poly-line-style arg4
	   poly-vertices arg5))
    
    (add-polygon
     (setq foreground-color-difference-of-graphic-element arg1 ; Line color
	   poly-line-width arg2
	   polygon-fill-color-difference arg3
	   polygon-fill-pattern arg4
	   poly-vertices arg5))

    (add-ellipse
     (setq foreground-color-difference-of-graphic-element arg1 ; Line color
	   poly-line-width arg2
	   polygon-fill-color-difference arg3
	   polygon-fill-pattern arg4
	   x-in-window-of-graphic-element arg5
	   y-in-window-of-graphic-element  arg6
	   entity-width-in-ws arg7
	   entity-height-in-ws arg8))

    #+development
    (otherwise 
     (error "Unknown operation for graphic-element"))))



;;;; Project Graphic Element After All Clipping




(defun-void project-graphic-element-to-current-window
    (left-edge-of-area top-edge-of-area right-edge-of-area bottom-edge-of-area)
  (with-drawing-trace (graphic-element)
    (format t "Enter ~s on ~s~%" operation-of-graphic-element current-image-plane))

  (when (rectangles-overlap-p
	  left-edge-in-window-of-graphic-element top-edge-in-window-of-graphic-element
	  right-edge-in-window-of-graphic-element bottom-edge-in-window-of-graphic-element
	  left-edge-of-area top-edge-of-area
	  right-edge-of-area bottom-edge-of-area)
    (let ((top-edge-of-element-within-area
	    (maxr top-edge-in-window-of-graphic-element top-edge-of-area))
          (bottom-edge-of-element-within-area
	    (minr bottom-edge-in-window-of-graphic-element bottom-edge-of-area)))

      (when (<r top-edge-of-element-within-area bottom-edge-of-element-within-area)
        (let ((left-edge-of-element-within-area
		(maxr left-edge-in-window-of-graphic-element left-edge-of-area))
              (right-edge-of-element-within-area
		(minr right-edge-in-window-of-graphic-element right-edge-of-area)))

	  (with-drawing-trace (graphic-element)
	    (format t "..really draw ~s~%" operation-of-graphic-element))

          (case operation-of-graphic-element
            
            (add-solid-rectangle
             (add-solid-rectangle-to-current-window
	       erase-instead?
	       left-edge-of-element-within-area top-edge-of-element-within-area
	       right-edge-of-element-within-area bottom-edge-of-element-within-area
	       foreground-color-difference-of-graphic-element))
            
            (add-line-of-text
             (add-from-line-of-text-to-current-window
	       erase-instead?
	       left-edge-of-element-within-area top-edge-of-element-within-area
	       right-edge-of-element-within-area bottom-edge-of-element-within-area
	       text-line-for-line-of-text-of-graphic-element
	       word-spacing-for-line-of-text-of-graphic-element
	       font-map-for-line-of-text-of-graphic-element
	       color-difference-for-line-of-text-of-graphic-element
	       x-scale-of-graphic-element
	       y-scale-of-graphic-element
	       left-edge-of-line-of-text-in-window-of-graphic-element
	       baseline-in-window-for-line-of-text-of-graphic-element))
            
            (add-icon-rendering
             (if (consp foreground-color-difference-or-differences-of-graphic-element)
		 ;; Polychrome icon
		 (add-from-icon-rendering-to-current-window
		   erase-instead?
		   left-edge-of-element-within-area top-edge-of-element-within-area
		   right-edge-of-element-within-area bottom-edge-of-element-within-area
		   0
		   graph-or-icon-rendering-of-graphic-element
		   (-r left-edge-of-element-within-area left-edge-in-window-of-graphic-element)
		   (-r top-edge-of-element-within-area top-edge-in-window-of-graphic-element)
		   foreground-color-difference-or-differences-of-graphic-element)
		 ;; Monochrome Icon
		 (add-from-icon-rendering-to-current-window
		   erase-instead?
		   left-edge-of-element-within-area top-edge-of-element-within-area
		   right-edge-of-element-within-area bottom-edge-of-element-within-area
		   foreground-color-difference-or-differences-of-graphic-element
		   graph-or-icon-rendering-of-graphic-element
		   (-r left-edge-of-element-within-area left-edge-in-window-of-graphic-element)
		   (-r top-edge-of-element-within-area top-edge-in-window-of-graphic-element)
		   nil)))
            
            (paint-solid-rectangle
             (paint-solid-rectangle-in-current-window
	       left-edge-of-element-within-area top-edge-of-element-within-area
	       right-edge-of-element-within-area bottom-edge-of-element-within-area
	       foreground-color-value-of-graphic-element))
            
            (add-upward-sloping-line
             (add-upward-sloping-line-to-current-window
	       erase-instead?
	       left-edge-of-element-within-area top-edge-of-element-within-area
	       right-edge-of-element-within-area bottom-edge-of-element-within-area
	       foreground-color-difference-of-graphic-element
	       left-edge-in-window-of-graphic-element
	       top-edge-in-window-of-graphic-element
	       right-edge-in-window-of-graphic-element
	       bottom-edge-in-window-of-graphic-element))
            
            (add-downward-sloping-line
             (add-downward-sloping-line-to-current-window
	       erase-instead?
	       left-edge-of-element-within-area top-edge-of-element-within-area
	       right-edge-of-element-within-area bottom-edge-of-element-within-area
	       foreground-color-difference-of-graphic-element
	       left-edge-in-window-of-graphic-element
	       top-edge-in-window-of-graphic-element
	       right-edge-in-window-of-graphic-element
	       bottom-edge-in-window-of-graphic-element))
            
            (add-graph-rendering
             (let ((color-values-for-rasters?
		     color-values-of-graph-rasters-of-graphic-element)
                   (graph-rendering graph-or-icon-rendering-of-graphic-element))
               (if (cdr color-values-for-rasters?)
		   ;; Polychrome graph
		   (add-from-graph-rendering-to-current-window
		     erase-instead?
		     left-edge-of-element-within-area top-edge-of-element-within-area
		     right-edge-of-element-within-area bottom-edge-of-element-within-area
		     (grid-background-color-value graph-rendering)
		     graph-rendering
		     (-r left-edge-of-element-within-area left-edge-in-window-of-graphic-element)
		     (-r top-edge-of-element-within-area top-edge-in-window-of-graphic-element)
		     0 ;; 0 is a dummy color value.
		     color-values-for-rasters?)
		   ;; Monochrome Raster
		   (add-from-graph-rendering-to-current-window
		     erase-instead?
		     left-edge-of-element-within-area top-edge-of-element-within-area
		     right-edge-of-element-within-area bottom-edge-of-element-within-area
		     (grid-background-color-value graph-rendering)
		     graph-rendering
		     (-r left-edge-of-element-within-area left-edge-in-window-of-graphic-element)
		     (-r top-edge-of-element-within-area top-edge-in-window-of-graphic-element)
		     (if color-values-for-rasters? ;; Necessary?
			 (car color-values-for-rasters?)
			 0) ;; 0 is a dummy color value.
		     nil))))
            
	    ;; This is a lengthy operation -- it needs to be scheduled.
            (paint-image
             (paint-or-tile-image-in-current-window
	       image-data-of-graphic-element
	       x-in-window-of-graphic-element
	       y-in-window-of-graphic-element
	       left-edge-of-element-within-area top-edge-of-element-within-area
	       right-edge-of-element-within-area bottom-edge-of-element-within-area
	       x-scale-of-graphic-element y-scale-of-graphic-element
	       rotation-of-graphic-element quality-of-graphic-element
	       foreground-color-value-of-graphic-element
	       background-color-value-of-graphic-element))

	    (paint-icon-background-image
             (paint-icon-background-image-in-current-window
	       image-data-of-graphic-element
	       x-in-window-of-graphic-element
	       y-in-window-of-graphic-element
	       left-edge-of-element-within-area top-edge-of-element-within-area
	       right-edge-of-element-within-area bottom-edge-of-element-within-area
	       x-scale-of-graphic-element y-scale-of-graphic-element
	       rotation-of-graphic-element quality-of-graphic-element
	       foreground-color-value-of-graphic-element
	       background-color-value-of-graphic-element
	       image-left-offset-in-ws
	       image-top-offset-in-ws
	       entity-width-in-ws
	       entity-height-in-ws))

	    (add-wide-polyline
	     (add-wide-polyline-to-current-window
	       left-edge-of-element-within-area top-edge-of-element-within-area
	       right-edge-of-element-within-area bottom-edge-of-element-within-area
	       foreground-color-difference-of-graphic-element
	       poly-line-width
	       (encode-poly-line-style poly-line-style poly-line-pattern)
	       (encode-poly-line-pattern poly-line-pattern)
	       poly-vertices))

	    (add-polygon
	     (draw-polygon-on-current-window
	       left-edge-of-element-within-area top-edge-of-element-within-area
	       right-edge-of-element-within-area bottom-edge-of-element-within-area
	       foreground-color-difference-of-graphic-element ; line-color-difference
	       poly-line-width
	       polygon-fill-color-difference
	       polygon-fill-pattern
	       poly-vertices))

	    (add-ellipse
	     (draw-ellipse-on-current-window
	       left-edge-of-element-within-area top-edge-of-element-within-area
	       right-edge-of-element-within-area bottom-edge-of-element-within-area
	       foreground-color-difference-of-graphic-element ; line-color-difference
	       poly-line-width
	       polygon-fill-color-difference
	       polygon-fill-pattern
	       x-in-window-of-graphic-element
	       y-in-window-of-graphic-element
	       entity-width-in-ws
	       entity-height-in-ws))))))))



;;;; Projecting Graphic Elements to Windows With All Clipping.


(def-system-variable effectively-infinite-region DRAW nil)

;;; The substitution-macro `current-visible-region' was added to support drawing
;;; without a current-image-plane. We assume an essentially unbounded visible
;;; region if there is no image-plane.

(def-substitution-macro current-visible-region ()
  (if (boundp 'current-image-plane)
      (visible-region-of-image-plane current-image-plane)
      (or effectively-infinite-region
	  (setq effectively-infinite-region
		(make-region-from-rectangle -100000 -100000 100000 100000)))))


;;; `Project-graphic-element' is a draw function called only within
;;; graphic-element-projection. The specified area must be entirely within the
;;; pane, and of non-zero size.  It projects the current graphic element zero or
;;; more times via do-projection-thru-region.

(defun-void project-graphic-element (left-edge-of-area
				      top-edge-of-area
				      right-edge-of-area
				      bottom-edge-of-area)
  
  (do-projection-thru-region
      ((left-edge-of-portion
	 top-edge-of-portion
	 right-edge-of-portion
	 bottom-edge-of-portion)
       (left-edge-of-area top-edge-of-area right-edge-of-area bottom-edge-of-area)
       (current-visible-region))

    (project-graphic-element-to-current-window
      left-edge-of-portion
      top-edge-of-portion
      right-edge-of-portion
      bottom-edge-of-portion)))

;; This routine once had an optimization to avoid the image-plane
;; clipping when the image-plane was topmost.  That is unnecessary now
;; since do-projection-thru-region is so zippy. - ben 4/12/93

;; This is the only caller of project-graphic-element-to-current-window.





;;;; Drawing Graphic Elements



;;; `Draw-graphic-element' provides a bottleneck thru which all draw-functions
;;; inevitably pass their individual drawing actions.  This bottleneck is
;;; responsible for assuring that each drawing action is mapped over and clipped
;;; to the current visible region, as defined by the macro `current-visible-region'.

;;; Normally, this function is called in an on-image-plane context, in which
;;; case the visible region is that of the current-image-plane. Otherwise, the
;;; visible region is taken to be unbounded.

;;; Note that drawing tasks are clipped to the visible portion of the image
;;; plane when they are enqueued they may not be correctly clipped when they
;;; are dequeued.

;;; In earlier version of G2 this bottleneck was used to capture a "memory" of
;;; what was on the screen.  This was known as Graphic Element Memory, and the
;;; erase-instead? binding was used to add/subtract from this memory.

;;; This routine is the cornerstone of the "draw" layer in the drawing protocol
;;; stack.  It should be used only in this module, so that it's N callers become
;;; the draw layer foundation.

;;; Draw-graphic-element is void returning, and as such sets a standard that
;;; the rest of the draw functions tend to follow.

;; This is the only caller of project-graphic-element.

(defun draw-graphic-element
  (graphic-element-operation
   left-edge-of-graphic-element-in-window top-edge-of-graphic-element-in-window
   right-edge-of-graphic-element-in-window bottom-edge-of-graphic-element-in-window
   arg1 &optional arg2 arg3 arg4 arg5 arg6 arg7 arg8)	;  "operation-specific-"?
  
  (with-clipping-to-draw-area? 
      ((left-edge-within-draw-area
        top-edge-within-draw-area
        right-edge-within-draw-area
        bottom-edge-within-draw-area)
       (left-edge-of-graphic-element-in-window
        top-edge-of-graphic-element-in-window
        right-edge-of-graphic-element-in-window
        bottom-edge-of-graphic-element-in-window))
    (with-named-dynamic-extent graphic-element-projection
        #-(or mtg2 SymScale) ()
        #+(or mtg2 SymScale) ; this is all global variables touched in `fill-out-current-graphic-element'
        (operation-of-graphic-element
         baseline-in-window-for-line-of-text-of-graphic-element
         bottom-edge-in-window-of-graphic-element
         color-difference-for-line-of-text-of-graphic-element
         color-values-of-graph-rasters-of-graphic-element
         entity-height-in-ws
         entity-width-in-ws
         font-map-for-line-of-text-of-graphic-element
         graph-or-icon-rendering-of-graphic-element
         image-data-of-graphic-element
         image-left-offset-in-ws
         image-top-offset-in-ws
         left-edge-in-window-of-graphic-element
         left-edge-of-line-of-text-in-window-of-graphic-element
         poly-line-width
         poly-line-pattern
         poly-line-style
         poly-vertices
         polygon-fill-color-difference
         polygon-fill-pattern
         right-edge-in-window-of-graphic-element
         text-line-for-line-of-text-of-graphic-element
         top-edge-in-window-of-graphic-element
         word-spacing-for-line-of-text-of-graphic-element)
      (fill-out-current-graphic-element graphic-element-operation
                                        left-edge-of-graphic-element-in-window 
                                        top-edge-of-graphic-element-in-window
                                        right-edge-of-graphic-element-in-window
                                        bottom-edge-of-graphic-element-in-window
                                        arg1 arg2 arg3 arg4 arg5 arg6 arg7 arg8)
      (project-graphic-element
       left-edge-within-draw-area top-edge-within-draw-area
       right-edge-within-draw-area bottom-edge-within-draw-area)
      #+development (find-bugs-in-graphic-elements)
      nil)))


#+development
(defun find-bugs-in-graphic-elements ()
  (loop with bogus-value = #.#C(-123 345)
	for i in '(operation-of-graphic-element
		   left-edge-in-window-of-graphic-element
		   top-edge-in-window-of-graphic-element 
		   right-edge-in-window-of-graphic-element 
		   bottom-edge-in-window-of-graphic-element 
		   foreground-color-value-of-graphic-element
		   foreground-color-difference-of-graphic-element
		   x-scale-of-graphic-element 
		   y-scale-of-graphic-element 
		   image-data-of-graphic-element 
		   x-in-window-of-graphic-element
		   y-in-window-of-graphic-element
		   rotation-of-graphic-element
		   quality-of-graphic-element 
		   background-color-value-of-graphic-element 
		   graph-or-icon-rendering-of-graphic-element 
		   foreground-color-difference-or-differences-of-graphic-element
		   color-values-of-graph-rasters-of-graphic-element
		   left-edge-of-line-of-text-in-window-of-graphic-element
		   baseline-in-window-for-line-of-text-of-graphic-element
		   text-line-for-line-of-text-of-graphic-element 
		   word-spacing-for-line-of-text-of-graphic-element
		   font-map-for-line-of-text-of-graphic-element 
		   color-difference-for-line-of-text-of-graphic-element)
	do (setf (symbol-value i) bogus-value)))



;;; `Draw-line-of-text' is the draw-function that draws a line of text into
;;; the visible regions of the current image-plane.

;;; Text-line must remain unchanged while (any part of) the line of text is on a
;;; window.  Under no circumstances will draw-line-of-text recycle text-line.

(defmacro draw-line-of-text
	  (left-edge-in-window top-edge-in-window
	   right-edge-in-window bottom-edge-in-window
	   text-line word-spacing font-map color-difference x-scale y-scale
	   left-edge-of-line-of-text-in-window baseline-in-window)
  `(draw-graphic-element
     'add-line-of-text
     ,left-edge-in-window ,top-edge-in-window
     ,right-edge-in-window ,bottom-edge-in-window
     ,text-line ,word-spacing ,font-map ,color-difference ,x-scale ,y-scale
     ,left-edge-of-line-of-text-in-window ,baseline-in-window))


;;; `Draw-line-of-text-handling-tabs' quickly scans text-line for tabs,
;;; dispatching to draw-line-of-text if there are none, or to the slower
;;; `draw-line-of-text-with-tabs', which is the most general purpose, if there
;;; is at least one tab.

(defun-substitution-macro draw-line-of-text-handling-tabs
    (left-edge-in-window
      top-edge-in-window
      right-edge-in-window bottom-edge-in-window
      text-line word-spacing font-map color-difference x-scale y-scale
      left-edge-of-line-of-text-in-window baseline-in-window)
  (cond
    ((loop with length fixnum = (text-string-length text-line)
	   for i from 0 below length
	   when (char=w (charw text-line i) '#.%tab)
	     return t)
     ;; The above test should be maximally fast -- possibly coded in C.
     (draw-line-of-text-with-tabs
       left-edge-in-window top-edge-in-window
       right-edge-in-window bottom-edge-in-window
       text-line word-spacing font-map color-difference x-scale y-scale
       left-edge-of-line-of-text-in-window baseline-in-window))
    (t
     (draw-line-of-text
       left-edge-in-window top-edge-in-window
       right-edge-in-window bottom-edge-in-window
       text-line word-spacing font-map color-difference x-scale y-scale
       left-edge-of-line-of-text-in-window baseline-in-window))))



(defun-void draw-line-of-text-with-tabs
    (left-edge-in-window
      top-edge-in-window
      right-edge-in-window bottom-edge-in-window
      text-line word-spacing font-map color-difference x-scale y-scale
      left-edge-of-line-of-text-in-window baseline-in-window)
  (declare (type fixnum
	     left-edge-in-window
	     top-edge-in-window
	     right-edge-in-window bottom-edge-in-window
	     word-spacing color-difference x-scale y-scale
	     left-edge-of-line-of-text-in-window baseline-in-window))
  (loop with end fixnum = (text-string-length text-line)
	with text-string-substring = (make-wide-string end)
	for previous-start fixnum = 0 then start
	as start fixnum = 0 then (+f next-end 1)
	as left-edge-offset-text-width fixnum
	   = 0
	   then (+f left-edge-offset-text-width
		    (compute-width-of-text-line
		      text-line previous-start start
		      font-map word-spacing t))
	as left-edge fixnum
	   = (+r left-edge-of-line-of-text-in-window
		 (text-width-to-x
		   (delta-x-in-window
		     left-edge-offset-text-width
		     x-scale)))
	;; uses text widths to reduce roundoff error
	as next-end
	fixnum = (loop for i from start
		       when (=f i end)
			 return end
		       when (char=w (charw text-line i) '#.%tab)
			 return i)
	do (setf (wide-string-length text-string-substring)
		 (-f next-end start))
	   (copy-portion-of-wide-string-into-wide-string
	     text-line start next-end
	     text-string-substring 0)
	do (draw-line-of-text
	     left-edge-in-window top-edge-in-window
	     right-edge-in-window bottom-edge-in-window
	     text-string-substring
	     word-spacing font-map color-difference x-scale y-scale
	     left-edge baseline-in-window)
	until (=f next-end end)
	finally (reclaim-text-string text-string-substring)))

;; Historical note only: update-graphic-element-memory-in-spite-of-draw-area?



;;; `Draw-icon-rendering' is a draw function used to draw an icon rendering into
;;; the visible region of the current image plane.  The width and height of the
;;; added-in area are (right-edge- in-window - left-edge-in-window) and
;;; (bottom-edge-in-window - top-edge-in-window), respectively.

(defmacro draw-icon-rendering
	  (left-edge-in-window top-edge-in-window
	   right-edge-in-window bottom-edge-in-window
	   foreground-color-difference-or-differences
	   icon-rendering)
  `(draw-graphic-element
     'add-icon-rendering
     ,left-edge-in-window ,top-edge-in-window
     ,right-edge-in-window ,bottom-edge-in-window
     ,foreground-color-difference-or-differences
     ,icon-rendering))



;;; `Draw-solid-rectangle' is a draw-function that will draw a rectangle in the
;;; given color difference on the visible region of the current image-plane.
;;; The edges are closed on the left and top, and open on the right and bottom.
;;; This eventually calls `add-solid-rectangle-to-current-window' to do the
;;; drawing.

(defmacro draw-solid-rectangle
    (left-edge-in-window top-edge-in-window right-edge-in-window bottom-edge-in-window
			 color-difference)
  `(draw-graphic-element
     'add-solid-rectangle
     ,left-edge-in-window ,top-edge-in-window
     ,right-edge-in-window ,bottom-edge-in-window
     ,color-difference))



;;; `Draw-image' is the draw-function the will render an image onto the
;;; visible region of the current image-plane.

(defmacro draw-image (image-data x-in-window y-in-window
				 left top right bottom x-scale y-scale rotation quality
				 foreground-color-value background-color-value)
  (avoiding-variable-capture
      (image-data x-in-window y-in-window
		  left top right bottom x-scale y-scale rotation quality
		  foreground-color-value background-color-value)
    `(let ((x-scale-of-graphic-element ,x-scale)
	   (y-scale-of-graphic-element ,y-scale)
	   (rotation-of-graphic-element ,rotation)
	   (quality-of-graphic-element ,quality)
	   (foreground-color-value-of-graphic-element ,foreground-color-value)
	   (background-color-value-of-graphic-element ,background-color-value)
	   (x-in-window-of-graphic-element ,x-in-window)
	   (y-in-window-of-graphic-element ,y-in-window))
       (draw-graphic-element 'paint-image
			     ,left ,top ,right ,bottom
			     ,image-data))))

(defmacro draw-icon-background-image (image-data x-in-window y-in-window
						 image-left-offset-in-ws
						 image-top-offset-in-ws
						 entity-width-in-ws
						 entity-height-in-ws
				 left top right bottom x-scale y-scale rotation quality
				 foreground-color-value background-color-value)
  (avoiding-variable-capture
      (image-data x-in-window y-in-window
		  left top right bottom x-scale y-scale rotation quality
		  foreground-color-value background-color-value)
    `(let ((x-scale-of-graphic-element ,x-scale)
	   (y-scale-of-graphic-element ,y-scale)
	   (rotation-of-graphic-element ,rotation)
	   (quality-of-graphic-element ,quality)
	   (foreground-color-value-of-graphic-element ,foreground-color-value)
	   (background-color-value-of-graphic-element ,background-color-value)
	   (x-in-window-of-graphic-element ,x-in-window)
	   (y-in-window-of-graphic-element ,y-in-window))
       (draw-graphic-element 'paint-icon-background-image
			     ,left ,top ,right ,bottom
			     ,image-data
			     ,image-left-offset-in-ws
			     ,image-top-offset-in-ws
			     ,entity-width-in-ws
			     ,entity-height-in-ws))))



;;; `Draw-graph-rendering-inner' is a draw-function that renders a graph rendering
;;; into the visible region of the current-image-plane.

(defmacro draw-graph-rendering (left-edge-in-window
				 top-edge-in-window 
				 right-edge-in-window
				 bottom-edge-in-window
				 color-values-for-rasters
				 graph-rendering)
  `(draw-graphic-element
     'add-graph-rendering
     ,left-edge-in-window ,top-edge-in-window 
     ,right-edge-in-window ,bottom-edge-in-window
     ,color-values-for-rasters
     ,graph-rendering))







;;; `Draw-line' is the draw function that will draw a line in the given color
;;; difference.  It optimizes the horizontal and vertical cases.  When the line
;;; is horizontal or vertical, it is more efficient to use draw-solid-rectangle
;;; than draw-line.

(defun draw-line (x1-in-window y1-in-window x2-in-window y2-in-window color-difference)
  (cond
    ((=r y1-in-window y2-in-window)
     (if (<r x1-in-window x2-in-window)
	 (draw-solid-rectangle
	   x1-in-window y1-in-window (+r x2-in-window 1) (+r y2-in-window 1)
	   color-difference)
	 (draw-solid-rectangle
	   x2-in-window y2-in-window (+r x1-in-window 1) (+r y1-in-window 1)
	   color-difference)))
    ((=r x1-in-window x2-in-window)
     (if (<r y1-in-window y2-in-window)
	 (draw-solid-rectangle
	   x1-in-window y1-in-window (+r x2-in-window 1) (+r y2-in-window 1)
	   color-difference)
	 (draw-solid-rectangle
	   x2-in-window y2-in-window (+r x1-in-window 1) (+r y1-in-window 1)
	   color-difference)))
    ((<r x1-in-window x2-in-window)
     (if (<r y1-in-window y2-in-window)
	 (draw-downward-sloping-line-1
	   x1-in-window y1-in-window (+r x2-in-window 2) (+r y2-in-window 2)
	   color-difference)
	 (draw-upward-sloping-line-1
	   x1-in-window y2-in-window (+r x2-in-window 2) (+r y1-in-window 2)
	   color-difference)))
    (t (if (<r y1-in-window y2-in-window)
	   (draw-upward-sloping-line-1
	     x2-in-window y1-in-window (+r x1-in-window 2) (+r y2-in-window 2)
	     color-difference)
	   (draw-downward-sloping-line-1
	     x2-in-window y2-in-window (+r x1-in-window 2) (+r y1-in-window 2)
	     color-difference)))))



;;; The function `new-draw-line' simply draws a solid line of width 1, with no
;;; messing around with endpoints or converting to rectangles.  We use the bogus
;;; existing line drawing routines, but pre-fudge the coordinates so that in the
;;; end we get a call to XDrawLine with the original arguments supplied here.

(defun new-draw-line (x1-in-window y1-in-window x2-in-window y2-in-window color-difference)
  ;; The only reason we have to dispatch on upward or downward is to get past
  ;; the clipping in add-graphic-element.
  (cond ((<r x1-in-window x2-in-window)
	 (if (<r y1-in-window y2-in-window)
	     (draw-downward-sloping-line-1
	       x1-in-window y1-in-window (+r x2-in-window 1) (+r y2-in-window 1)
	       color-difference)
	     (draw-upward-sloping-line-1
	       x1-in-window y2-in-window (+r x2-in-window 1) (+r y1-in-window 1)
	       color-difference)))
	((<r y1-in-window y2-in-window)
	 (draw-upward-sloping-line-1
	   x2-in-window y1-in-window (+r x1-in-window 1) (+r y2-in-window 1)
	   color-difference))
	(t
	 (draw-downward-sloping-line-1
	   x2-in-window y2-in-window (+r x1-in-window 1) (+r y1-in-window 1)
	   color-difference))))


;;;  `Draw-upward-sloping-line' is a subfunction of draw-line.  The line is an
;;;  diagonal from the bottom-left to the top-right corner of the specified
;;;  area.

(defun draw-upward-sloping-line-1
       (left-edge-in-window top-edge-in-window right-edge-in-window bottom-edge-in-window
	color-difference)
  (draw-graphic-element
    'add-upward-sloping-line
    left-edge-in-window top-edge-in-window right-edge-in-window bottom-edge-in-window
    color-difference))



;;;  `Draw-downward-sloping-line' is a subfunction of draw-line.  The line is an
;;;  diagonal from the top-left to the bottom-right corner of the specified
;;;  area.

(defun draw-downward-sloping-line-1
       (left-edge-in-window top-edge-in-window right-edge-in-window bottom-edge-in-window
	color-difference)
  (draw-graphic-element
    'add-downward-sloping-line
    left-edge-in-window top-edge-in-window right-edge-in-window bottom-edge-in-window
    color-difference))



;;; `Paint-solid-rectangle' is a draw-function that paints a solid rectangle
;;; in the color value in the visible region of the current-image-plane.
;;; This is as opposed to draw-solid-rectangle, which may XOR one in.

(defun-void paint-solid-rectangle
    (left-edge-in-window top-edge-in-window right-edge-in-window bottom-edge-in-window
			 color-value)
  (with-clipping-to-draw-area? ((left-edge-in-draw-area
				  top-edge-in-draw-area
				  right-edge-in-draw-area
				  bottom-edge-in-draw-area)
				(left-edge-in-window
				  top-edge-in-window
				  right-edge-in-window
				  bottom-edge-in-window))
    (draw-graphic-element
      'paint-solid-rectangle
      left-edge-in-draw-area
      top-edge-in-draw-area
      right-edge-in-draw-area
      bottom-edge-in-draw-area
      color-value)))

;; Why is this clipping-to-draw-area? exceptional amongst the functions
;; in this section.


;;; The function `draw-wide-polyline' draws a wide, patterned line connecting
;;; the given points in sequence, with proper line joins between segments.
;;; Line-pattern here either a symbol for stock patterns or a slot-value list of
;;; fixnum dash lengths (in window units) for custom patterns. Line-style is
;;; either MITER, ROUNDED, or NIL.

(defun draw-wide-polyline (points color-difference line-width line-pattern line-style)
  (draw-graphic-element
    'add-wide-polyline
    left-edge-of-draw-area
    top-edge-of-draw-area
    right-edge-of-draw-area
    bottom-edge-of-draw-area
    color-difference line-width line-pattern line-style
    points))


;;; The function `draw-patterned-line' draws a wide, patterned line segment if
;;; it can; otherwise, for old TW's, a thin, solid line.

(defun draw-patterned-line (x0 y0 x1 y1 color-value line-width line-pattern)
  (let ((color-difference (color-difference color-value current-background-color-value)))
    (cond ((current-window-supports-wide-polyline current-window)
	   (let ((points (gensym-list x0 y0 x1 y1)))
	     (draw-wide-polyline points color-difference line-width line-pattern nil)
	     (reclaim-gensym-list points)))
	  (t
	   (draw-line x0 y0 x1 y1 color-difference)))))


;;; Convenience routines based on the two new drawing primitives for 8.1b0,
;;; `add-polygon-to-current-window' and `add-ellipse-to-current-window'.

(defun draw-polygon (points color-difference &optional (thick 1) filled?)
  (cond ((or (not (window-supports-polyarcs))
	     (not filled?))
	 ;; FIXME: punting filled on old windows.
	 (draw-wide-polyline points color-difference thick nil nil))
	(t
	 (draw-graphic-element
	   'add-polygon
	   left-edge-of-draw-area top-edge-of-draw-area
	   right-edge-of-draw-area bottom-edge-of-draw-area
	   color-difference thick
	   (if filled? color-difference transparent-color-value) 0
	   points)))
  points)

(defun draw-circle (dimensions color-difference &optional (thick 1) filled?)
  (gensym-dstruct-bind ((x y radius) dimensions)
    (let ((x1 (-f x radius))
	  (y1 (-f y radius))
	  (x2 (+f x radius))
	  (y2 (+f y radius)))
      (cond ((not (window-supports-polyarcs))
	     ;; FIXME: punting completely.
	     (draw-solid-rectangle x1 y1 x2 y2 color-difference))
	    (t
	     (draw-graphic-element
	       'add-ellipse
	       left-edge-of-draw-area top-edge-of-draw-area
	       right-edge-of-draw-area bottom-edge-of-draw-area
	       color-difference thick
	       (if filled? color-difference transparent-color-value) 0
	       x1 y1 x2 y2)))
    dimensions)))



;;;; Drawing image planes


;;; The defvar `drawing-state-for-project-paper' hold the resumption state
;;; needed for drawing background images.  It is bound around calls to
;;; project-frame.

(defvar drawing-state-for-project-paper nil)



;;; The function `sketch-image-plane' draws the "low resolution" background of
;;; the current image plane.  Designed to be give the user very quick feedback
;;; on what's coming next.  It must complete as quickly as possible.

(defun sketch-image-plane ()
  (within-named-dynamic-extent on-window-with-drawing
    (with-null-drawing-transform ;; Note A
      (with-background-color-value
	  (compute-workspace-background-color-value current-image-plane)
	;; TODO: Don't draw paper for native IP, download the bg color instead.
	(project-frame
	  'drawing-paper
	  (frame-description-of-frame-description-reference
	    (frame-description-reference-of-image-plane 
	      current-image-plane))
	  (left-edge-of-image-in-window current-image-plane)
	  (top-edge-of-image-in-window current-image-plane)
	  (right-edge-of-image-in-window current-image-plane)
	  (bottom-edge-of-image-in-window current-image-plane)
	  nil)))))

;; Note A: This is necessary since the caller maybe working on some part
;; of, just the content area.  But the frame is in the window coordinates.





;;; The macro `current-window-printer-p' is a fast, convenient macro to
;;; determine if the current window is being used for printing, i.e., is of type
;;; PRINTER.  It must be called in an environment with current-window bound,
;;; e.g., simple-for-image-plane or on-window-without-drawing.

(defmacro current-window-printer-p ()
  `(eq (type-of-gensym-window current-window) 'printer))





;;; The function `paint-background-of-image-plane' draws the "high resolution"
;;; background of the current-image-plane -- the frame, the background color
;;; and the background images.  Since this can be very slow if background
;;; images are present, this takes and returns a state-block with enough
;;; information to resume drawing where we stopped when our time slice expired.

(defun paint-background-of-image-plane (region state?)
  (unless (client-drawn-image-plane-p current-image-plane)
    (with-drawing-trace (wks)
      (format t "Paint-background: ~s ~s~%" current-image-plane region))
    (with-null-drawing-transform				    ; See Note A on sketch-image-plane

      ;; We must back out the draw area to exterior of the image plane, which is
      ;; where the paper is!  Some callers bind it to the interior.
      (with-image-plane-draw-area? (current-image-plane)

	(do-region-rectangles ((left top right bottom) region)
	  
	  (with-nested-draw-area? (left top right bottom
					:paint-background-of-image-plane :region-rectangle)
	    ;; Do we have to engage the frame interpreter?
	    (cond ((rectangle-inside-rectangle-p
		     left-edge-of-draw-area
		     top-edge-of-draw-area
		     right-edge-of-draw-area
		     bottom-edge-of-draw-area
		     (left-edge-of-workspace-area-in-window current-image-plane)
		     (top-edge-of-workspace-area-in-window current-image-plane)
		     (right-edge-of-workspace-area-in-window current-image-plane)
		     (bottom-edge-of-workspace-area-in-window current-image-plane))
		   ;; No.  Hooray!!
		   (setq state?
			 (draw-paper-for-current-image-plane
			   state?
			   left-edge-of-draw-area top-edge-of-draw-area
			   right-edge-of-draw-area bottom-edge-of-draw-area)))
		  (t
		   ;; DRAWING versus DRAWING-PAPER here includes the borders, scrollbars, etc.
		   (let ((drawing-state-for-project-paper state?))
		     (unless (and (current-window-printer-p)
				  (suppress-printing-border-p current-image-plane))
		       (project-frame
			 'drawing
			 (frame-description-of-frame-description-reference
			   (frame-description-reference-of-image-plane 
			     current-image-plane))
			 (left-edge-of-image-in-window current-image-plane)
			 (top-edge-of-image-in-window current-image-plane)
			 (right-edge-of-image-in-window current-image-plane)
			 (bottom-edge-of-image-in-window current-image-plane)
			 nil))
		     (setq state? drawing-state-for-project-paper))))))))
    state?))

;; This was a performance hog in paint-mode.  During KB updates, the region is
;; nearly always entirely inside of the frame, hence only the background paper
;; need be drawn.



(defun work-on-xor-drawing (region)
  (with-drawing-trace (xor)
    (format t "XOR activities ~s~%" (remaining-xor-drawing-activities
				      current-image-plane)))

  (with-transfer-mode-when-drawing (:xor)
    (loop while (remaining-xor-drawing-activities current-image-plane)
	  as activity = (slot-value-pop
			  (remaining-xor-drawing-activities
			    current-image-plane))

	  doing (do-region-rectangles ((left top right bottom) region)
		  (with-nested-draw-area? (left top right bottom
						region :region-segment)
		    (do-activity activity)))
		(reclaim-slot-value-list activity)

	  until (drawing-time-slice-expired-p))))





;;; The parameters `icp-window-max-buffered-drawing-in-bytes' and
;;; `icp-window-max-buffered-drawing-in-seconds' regulate the amount of drawing
;;; we are allowed to buffer for an ICP window before flushing and restarting
;;; the message group.

;;; GENSYMCID-1215: twng locking up (Part III)
;;;
;;; Try to increase ICP window drawing buffer to get around of NASA's very big
;;; workspace.  -- Chun Tian (binghe), Feb 2015.

(defparameter icp-window-max-buffered-drawing-in-bytes 10000) ; old: 5000
(defparameter icp-window-max-buffered-drawing-in-seconds   3) ; old: 2




;;; The function `paint-contents-of-image-plane' draws the contents of the
;;; current-image-plane overlapping region.  It draws only the blocks upon the
;;; workspace, and not the background or frame.  It is subject to the drawing
;;; time slice.

;;; The using-geometry-p argument describes what is in the list of remaining
;;; subblocks to draw.  If it is NIL, then that list contains only top-level
;;; subblocks and deeper subblocks should be drawn recursively.  If the flag is
;;; T, then the list of remaining subblocks explicitly includes subblocks,
;;; sub-subblocks, etc, which need to be drawn.  The list may also include
;;; connections in this case.

;;; It is effectively the draw method of workspaces.  It draws each of the
;;; subblocks in the order they are recorded as if in two passes: one pass for
;;; most blocks and one pass of the "XOR'd" blocks.

;;; The caller must provide an erased image-plane below the subblocks, and
;;; restore the pane cursors above.  The image-plane transform must be current.

;;; This establishes working-on-drawing-workspace, see above.

;;; Individual blocks are drawn via their draw method.  Blocks flaged as
;;; render-frame-in-xor-overlay-p are drawn in the XOR overlay.

;;; If the drawing time-slice expires, then we will return with some work
;;; remaining to be done.  Our state for resumption is stored in slots
;;; in the image plane.

(defun paint-contents-of-image-plane (region using-geometry-p)
  (with-drawing-trace (wks)
    (format t "Paint-contents:   ~s ~s ~d~%"
	    current-image-plane region
	    (length (remaining-subblocks-of-workspace-to-draw current-image-plane))))
  (with-drawing-trace (icp-bytes) (print-icp-buffer-sizes "ICP bytes "))
  (with-drawing-trace (show-regions) (outline-region-of-window region :color 'blue))

  (with-named-dynamic-extent working-on-drawing-workspace
      ((currently-working-on-drawing-workspace t)
       (workstation-with-image-plane-being-refreshed
	 (workstation-of-image-plane current-image-plane)))

    (multiple-value-bind (left top right bottom)
	(region-bounding-rectangle region)
      
      ;; Draw blocks which overlap the region.
      (loop while (remaining-subblocks-of-workspace-to-draw current-image-plane)
	    as block-or-connection = (slot-value-pop
				       (remaining-subblocks-of-workspace-to-draw
					 current-image-plane))

	    as connection-p = (not (framep block-or-connection))
	    doing
	(when (icp-window-p current-window)
	  (maybe-restart-icp-window-update
	    icp-window-max-buffered-drawing-in-seconds
	    icp-window-max-buffered-drawing-in-bytes)
	  (when (=f (icp-connection-state current-icp-socket) icp-connection-closed)
 	    (return nil)))

	(when (or connection-p using-geometry-p
		  (block-possibly-overlaps-rectangle? block-or-connection
						      left top right bottom))

	  (do-region-rectangles ((left top right bottom) region)
	    (with-nested-draw-area? (left top right bottom
					  :paint-contents-of-image-plane :region-rectangle)

	      ;; Note B
	      (cond ((or using-geometry-p connection-p)
		     (draw-block-or-connection block-or-connection))
		    (t
		     (when (block-possibly-overlaps-draw-area? block-or-connection)
		       (draw-block-macro block-or-connection)))))))

	    until (drawing-time-slice-expired-p))

      ;; Selection handles go above all blocks, but below XOR overlay.
      (when (and (null (remaining-subblocks-of-workspace-to-draw current-image-plane))
		 (show-selection-handles-p current-window)
		 (image-plane-selected-p current-image-plane))
	(draw-selection-handles-for-current-image-plane left top right bottom))))

  ;; XOR blocks which wanted it. (Note A).
  ;; MUST be outside the scope of working-on-drawing-workspace.
  (when (and (remaining-xor-drawing-activities current-image-plane)
	     (null (remaining-subblocks-of-workspace-to-draw current-image-plane)))
    (work-on-xor-drawing region)))


;; Note A: Eg, blocks being dragged or which have set their
;; render-frame-in-xor-overlay-p bit (pointer-for-dial, marker-for-meter, etc).
;; Or, blocks which draw themselves in XOR by using the
;; with-deferred-xor-drawing macro: the connection joining two blocks being
;; dragged, blinkers (eg, edit cursors) and text-highlight-bar

;; Note B: We're not taking advantage of the fact that region rectangles are sorted
;; from top to bottom and left to right.  Also, the test of whether a block
;; overlaps requires xforming the block edges to window coordinates.  We could
;; have done this test at KB-level, before we xformed the region (sometimes).



;;; The function `paint-region-of-image-plane-overlapping-block' is used by the
;;; refresh-region-of-block drawing task.  Runs atomically for now.  The region
;;; given MUST be entirely inside the bounding region of the block (else the list
;;; of overlapping blocks we compute may be too small).

(defun paint-region-of-image-plane-overlapping-block
    (workspace image-plane block region)
  (with-named-dynamic-extent working-on-drawing-workspace
      ((currently-working-on-drawing-workspace t)
       (workstation-with-image-plane-being-refreshed
	 (workstation-of-image-plane current-image-plane)))

    (let ((opaque? (opaque-block-p block)))
      ;; If the block is being dragged, then it isn't opaque after all.
      ;; But, opaque blocks never draw themselves via this pathway when
      ;; they are being dragged, so the additional test is not needed.
      ;; -fmw, 2/22/95

      (unless opaque?
	(with-unlimited-time-slice
	  (paint-background-of-image-plane region nil)))

      (do-region-rectangles ((left top right bottom) region)
	;; Clip to pane. Is this needed?
	(with-nested-draw-area?
	    ((left-edge-within-pane left image-plane)
	     (top-edge-within-pane top image-plane)
	     (right-edge-within-pane right image-plane)
	     (bottom-edge-within-pane bottom image-plane)
	     region :region-segment)
	  (draw-overlapping-blocks workspace block (if opaque? 'above-inclusive nil) t)))

      ;; Selection handles go above all blocks, but below XOR overlay.
      (when (and (show-selection-handles-p current-window)
		 (image-plane-selected-p current-image-plane))
	(multiple-value-bind (left top right bottom)
	    (region-bounding-rectangle region)
	  (draw-selection-handles-for-current-image-plane left top right bottom)))))

  ;; MUST be outside the scope of working-on-drawing-workspace.
  (when (remaining-xor-drawing-activities current-image-plane)
    (with-unlimited-time-slice
      (work-on-xor-drawing region))))


;;;; Utility Functions for Drawing Current Image-Plane



;;; These utility functions draw various standard shapes on a workspace, given
;;; arguments in a variety of convenient formats, and are intended to be called
;;; from within a drawing context, assuming bindings for current-image-plane,
;;; current-image-x-scale, current-background-color-value, etc.


;;; `Paint-background-for-opaque-block' paints the block rectangle (clipped to
;;; the draw area) in the current-background-color-value.

;;; This assumes that a block that has its opaque-block flag set and has a
;;; superblock is an opaque block.  Block can have the former without the latter
;;; when it is being dragged for transfer or just after it has been created.  If
;;; pane cursors are later used in these dragging cases, then the circumstance
;;; of block having the opaque-block flag but no superblock may never arise.

(defun-void paint-background-for-opaque-block (block)
  (when (and (opaque-block-p block) (superblock? block))
    (with-clipping-to-draw-area? ((left-edge-within-draw-area
				    top-edge-within-draw-area
				    right-edge-within-draw-area
				    bottom-edge-within-draw-area)
				  ((x-in-window (left-edge-of-block block))
				   (y-in-window (top-edge-of-block block))
				   (x-in-window (right-edge-of-block block))
				   (y-in-window (bottom-edge-of-block block))))
      (paint-solid-rectangle
	left-edge-within-draw-area top-edge-within-draw-area
	right-edge-within-draw-area bottom-edge-within-draw-area
	current-background-color-value))))

;; Abstract the code common to this and draw-block as a macro, and see if it also might
;; be used in some of the project functions!




;;; `Draw-block-outline-in-current-image-plane' ... color-or-metacolor?
;;; defaults to FOREGROUND.

(defun draw-block-outline-in-current-image-plane (block &optional color-or-metacolor?)
  (draw-rectangle-outline-in-current-image-plane
    (left-edge-of-block block) (top-edge-of-block block)
    (right-edge-of-block block) (bottom-edge-of-block block)
    color-or-metacolor?))



;;; `Draw-rectangle-outline-in-current-image-plane' draws an outline of a
;;; rectangle described by the four edge arguments in the color described by
;;; color-or-metacolor?, which defaults to the metacolor FOREGROUND.  It
;;; uses current background color bound in current-background-color-value
;;; as an implicit parameter to decide the ultimate color difference to draw
;;; in.
;;;
;;; The lines of the outline are line-width-in-workspace?, or 1, workspace
;;; units, which get scaled down per the current image plane x and y scale, but
;;; not further than "hairlines", meaning single-pixel-width lines.
;;;
;;; Line widths of 0 are given a special meaning: they are drawn as "hairlines"
;;; even when scaling up.  Thus, no matter how great the scale, they will never
;;; be larger than the size of a pixel.  Negative line widths are illegal.
;;;
;;; The size of the rectangle is scaled in the standard way per the current
;;; drawing environment.
;;;
;;; `Paint-rectangle-outline-in-current-image-plane' does the same thing, but
;;; uses the equivalent painting operations.  Accordingly, it ignores the
;;; current background color bound in the for-image-plane context.

(defun draw-rectangle-outline-in-current-image-plane
    (left-edge-in-workspace top-edge-in-workspace
     right-edge-in-workspace bottom-edge-in-workspace
     &optional color-or-metacolor? line-width-in-workspace?)
  (draw-rectangle-outline-in-current-image-plane-1
    left-edge-in-workspace top-edge-in-workspace
    right-edge-in-workspace bottom-edge-in-workspace
    (color-difference
      (map-color-or-metacolor-to-color-value (or color-or-metacolor? 'FOREGROUND))
      current-background-color-value)
    (or line-width-in-workspace? 1)))

(defun paint-rectangle-outline-in-current-image-plane
    (left-edge-in-workspace top-edge-in-workspace
     right-edge-in-workspace bottom-edge-in-workspace
     &optional color-or-metacolor? line-width-in-workspace?)
  (paint-rectangle-outline-in-current-image-plane-1
    left-edge-in-workspace top-edge-in-workspace
    right-edge-in-workspace bottom-edge-in-workspace
    (map-color-or-metacolor-to-color-value (or color-or-metacolor? 'FOREGROUND))
    (or line-width-in-workspace? 1)))


;;; `Draw-rectangle-outline-in-current-image-plane-1' does the final scaling
;;; from workspace to window coordinates.  It also has a fixed argument list,
;;; requiring color-difference line-width-in-workspace.  Otherwise, it's the
;;; same as draw-rectangle-outline-in-current-image-plane.
;;;
;;; This is a subfunction of draw-rectangle-outline-in-current-image-plane,
;;; at which definition the rest of its documentation is to be found.
;;;
;;;
;;; `Paint-rectangle-outline-in-current-image-plane-1' is the same thing but
;;; uses the equivalent paint operations, and accordingly takes color-value
;;; as an argument rather than a color-difference.

(defun-void draw-rectangle-outline-in-current-image-plane-1
    (left-edge-in-workspace top-edge-in-workspace
     right-edge-in-workspace bottom-edge-in-workspace
     color-difference line-width-in-workspace)
  (let* ((left-edge-in-window (x-in-window left-edge-in-workspace))
	 (top-edge-in-window (y-in-window top-edge-in-workspace))
	 (right-edge-in-window (x-in-window right-edge-in-workspace))
	 (bottom-edge-in-window (y-in-window bottom-edge-in-workspace))
	 (x-width-in-window
	  (if (=w line-width-in-workspace 0)
	      1
	      (maxr 1
		    (delta-x-in-window
		      line-width-in-workspace
		      current-image-x-scale))))
	 (y-width-in-window
	  (if (=w line-width-in-workspace 0)
	      1
	      (maxr 1
		    (delta-y-in-window
		      line-width-in-workspace
		      current-image-y-scale)))))
    (draw-rectangle-outline-in-window
      left-edge-in-window top-edge-in-window
      right-edge-in-window bottom-edge-in-window
      color-difference x-width-in-window y-width-in-window)))

(defun-void paint-rectangle-outline-in-current-image-plane-1
    (left-edge-in-workspace top-edge-in-workspace
     right-edge-in-workspace bottom-edge-in-workspace
     color-value line-width-in-workspace)
  (let* ((left-edge-in-window (x-in-window left-edge-in-workspace))
	 (top-edge-in-window (y-in-window top-edge-in-workspace))
	 (right-edge-in-window (x-in-window right-edge-in-workspace))
	 (bottom-edge-in-window (y-in-window bottom-edge-in-workspace))
	 (x-width-in-window
	  (if (=w line-width-in-workspace 0)
	      1
	      (maxr 1
		    (delta-x-in-window
		      line-width-in-workspace
		      current-image-x-scale))))
	 (y-width-in-window
	  (if (=w line-width-in-workspace 0)
	      1
	      (maxr 1
		    (delta-y-in-window
		      line-width-in-workspace
		      current-image-y-scale)))))
    (paint-rectangle-outline-in-window
      left-edge-in-window top-edge-in-window
      right-edge-in-window bottom-edge-in-window
      color-value x-width-in-window y-width-in-window)))



;;; `Draw-rectangle-outline-in-window' draws a rectangle in the current image
;;; plane, given window coordinates, color-difference, and line width, scaled in
;;; x and y.
;;; 
;;; `Paint-rectangle-outline-in-window' draws a rectangle in the current image
;;; plane, given window coordinates, color-value, and line width, scaled in
;;; x and y.

(defun-void draw-rectangle-outline-in-window
    (left-edge-in-window top-edge-in-window
     right-edge-in-window bottom-edge-in-window
     color-difference x-line-width-in-window y-line-width-in-window)
  (draw-solid-rectangle			; top
    left-edge-in-window
    top-edge-in-window
    right-edge-in-window
    (+r top-edge-in-window y-line-width-in-window)
    color-difference)
  (draw-solid-rectangle			; bottom
    left-edge-in-window
    (-r bottom-edge-in-window y-line-width-in-window)
    right-edge-in-window
    bottom-edge-in-window
    color-difference)
  (draw-solid-rectangle			; left
    left-edge-in-window
    (+r top-edge-in-window y-line-width-in-window)
    (+r left-edge-in-window x-line-width-in-window)
    (-r bottom-edge-in-window y-line-width-in-window)
    color-difference)
  (draw-solid-rectangle			; right
    (-r right-edge-in-window x-line-width-in-window)
    (+r top-edge-in-window y-line-width-in-window)
    right-edge-in-window
    (-r bottom-edge-in-window y-line-width-in-window)
    color-difference))

(defun-void paint-rectangle-outline-in-window
    (left-edge-in-window top-edge-in-window
     right-edge-in-window bottom-edge-in-window
     color-value x-line-width-in-window y-line-width-in-window)
  (paint-solid-rectangle			; top
    left-edge-in-window
    top-edge-in-window
    right-edge-in-window
    (+r top-edge-in-window y-line-width-in-window)
    color-value)
  (paint-solid-rectangle			; bottom
    left-edge-in-window
    (-r bottom-edge-in-window y-line-width-in-window)
    right-edge-in-window
    bottom-edge-in-window
    color-value)
  (paint-solid-rectangle			; left
    left-edge-in-window
    (+r top-edge-in-window y-line-width-in-window)
    (+r left-edge-in-window x-line-width-in-window)
    (-r bottom-edge-in-window y-line-width-in-window)
    color-value)
  (paint-solid-rectangle			; right
    (-r right-edge-in-window x-line-width-in-window)
    (+r top-edge-in-window y-line-width-in-window)
    right-edge-in-window
    (-r bottom-edge-in-window y-line-width-in-window)
    color-value))

;; Note that we don't have a general line drawing primitive that renders lines
;; with thickness.  Also, calling the draw-rectangle primitive is generally a
;; bit more efficient than calling the general line drawing primitive, even
;; for single-unit-thick lines.



;;; `Paint-rectangle-frame-in-current-image-plane' paints the frame described by
;;; the two rectangles specified by the arguments (the inside and outside
;;; rectangles).  The "frame" is painted in the current image plane in the
;;; designated color by painting four bars, like so
;;;
;;;                  -----       <- 1st
;;;                  |   |       <- 2nd & 3rd
;;;                  -----       <- 4th
;;;
;;; thus forming a frame around the inside rectangle.  

(defun-void paint-rectangle-frame-in-current-image-plane
    (outside-left-edge-in-workspace outside-top-edge-in-workspace
     outside-right-edge-in-workspace outside-bottom-edge-in-workspace
     
     inside-left-edge-in-workspace inside-top-edge-in-workspace
     inside-right-edge-in-workspace inside-bottom-edge-in-workspace
     
     color-or-metacolor)
  (let* ((color-value
	  (map-color-or-metacolor-to-color-value color-or-metacolor))
	 (outside-left-edge-in-window
	  (x-in-window outside-left-edge-in-workspace))
	 (outside-top-edge-in-window
	  (y-in-window outside-top-edge-in-workspace))
	 (outside-right-edge-in-window
	  (x-in-window outside-right-edge-in-workspace))
	 (outside-bottom-edge-in-window
	  (y-in-window outside-bottom-edge-in-workspace))
	 (inside-left-edge-in-window
	  (x-in-window inside-left-edge-in-workspace))
	 (inside-top-edge-in-window
	  (y-in-window inside-top-edge-in-workspace))
	 (inside-right-edge-in-window
	  (x-in-window inside-right-edge-in-workspace))
	 (inside-bottom-edge-in-window
	  (y-in-window inside-bottom-edge-in-workspace)))
    
    (when (and (<r outside-left-edge-in-window
		   outside-right-edge-in-window)
	       (<r outside-top-edge-in-window
		   outside-bottom-edge-in-window))
      
      (when (<r outside-top-edge-in-window
		inside-top-edge-in-window)
	(paint-solid-rectangle	; top bar
	  outside-left-edge-in-window outside-top-edge-in-window
	  outside-right-edge-in-window inside-top-edge-in-window
	  color-value))
      (when (<r inside-top-edge-in-window
		inside-bottom-edge-in-window)
	(when (<r outside-left-edge-in-window
		  inside-left-edge-in-window)
	  (paint-solid-rectangle      ; left bar
	    outside-left-edge-in-window inside-top-edge-in-window
	    inside-left-edge-in-window inside-bottom-edge-in-window
	    color-value))
	(when (<r inside-right-edge-in-window
		  outside-right-edge-in-window)
	  (paint-solid-rectangle      ; right bar
	    inside-right-edge-in-window inside-top-edge-in-window
	    outside-right-edge-in-window inside-bottom-edge-in-window
	    color-value)))
      (when (<r inside-bottom-edge-in-window
		outside-bottom-edge-in-window)
	(paint-solid-rectangle        ; bottom bar
	  outside-left-edge-in-window inside-bottom-edge-in-window
	  outside-right-edge-in-window outside-bottom-edge-in-window
	  color-value)))))




;;;; Frame Projection Primitives


;;; `Frame-interesting-p' is used internally in frame projection to test
;;; if the current frame should be projected or not.  For example when
;;; drawing it tests to assure that the frame overlaps the current draw area.

(defun frame-interesting-p ()
  (within-named-dynamic-extent frame-projecting 
   (case purpose-of-frame-projecting
      ((drawing drawing-paper drawing-contents drawing-close-box)
       (rectangles-overlap-p left-edge-of-draw-area
			     top-edge-of-draw-area
			     right-edge-of-draw-area
			     bottom-edge-of-draw-area

			     (x-in-window left-edge-of-frame)
			     (y-in-window top-edge-of-frame)
			     (x-in-window right-edge-of-frame)
			     (y-in-window bottom-edge-of-frame)))
      (mouse-tracking
       #+junk
       (print (list 
	 (x-of-mouse-pointer mouse-pointer-of-frame)
	 (y-of-mouse-pointer mouse-pointer-of-frame)
	 (x-in-window left-edge-of-frame)
	 (y-in-window top-edge-of-frame)	
	 (x-in-window right-edge-of-frame)
	 (y-in-window bottom-edge-of-frame)))
       (point-inside-rectangle-p 
	 (x-of-mouse-pointer mouse-pointer-of-frame)
	 (y-of-mouse-pointer mouse-pointer-of-frame)
	 (x-in-window left-edge-of-frame)
	 (y-in-window top-edge-of-frame)	
	 (x-in-window right-edge-of-frame)
	 (y-in-window bottom-edge-of-frame)))
      (compute-content-region
       (null (cdr control-stack-of-frame-projecting)))
      (move-elevator
       t)
      #+development
      (otherwise
       (error "Unknown purpose-of-frame-projecting")))))

;; Note that by returning Nil here when computing content region we focus
;; compute-content-region pass just right so that it visits only the outtermost
;; segments.








;;; `Indent-frame' indents the current frame inwards by INDENT units.

(defun indent-frame (indent)
  (incff left-edge-of-frame indent)
  (incff top-edge-of-frame indent)
  (decff right-edge-of-frame indent)
  (decff bottom-edge-of-frame indent))



;;; `Project-frame' takes a purpose, a frame description, a rectangle, and a
;;; simple-compiled-function of no arguments.  It executes the frame description
;;; according to the purpose, either drawing or just computing, working inwards
;;; from the given rectangle.  Once we compute the innermost boundary inside the
;;; frame, it calls the given function.

;;; The rectangle is in coordinates in which the frame-description's block
;;; lives.  For example, workspaces live in windows, so the rectangle should be
;;; in window coordinates.  The rectangle MUST be the outermost rectangle for the
;;; frame, which the frame description moves inwards.

;;; The purpose is one of these values.  `Draw' which indicates that the frame
;;; should be drawn into the current window.  `Track-mouse' which means that
;;; appropriate mouse spots should be generated in the current event (this
;;; is not implemented as yet).  `Compute-content-region' which indicates that
;;; the content region is being recomputed.

;;; The simple-compiled-function should project the drawing within the frame.
;;; It will be invoked within the `frame-projecting' dynamic extent.

;;; The frame description is in the form of a lisp program matching the
;;; following grammar.

;;;    <frame-description> := (<frame-component>*)

;;;    <frame-component> :=  <frame-section>
;;;    <frame-component> :=  <border-component>
;;;    <frame-component> :=  (title-bar <size>)
;;;    <frame-component> :=  (scroll-bar)
;;;    <frame-component> :=  (resize-box)
;;;    <frame-component> :=  (close-box <size>)
;;;    <size> := SMALL
;;;    <size> := LARGE

;; Consider <size> for other components, not currently used. (MHD 11/16/99)

;;;    <border-component> := (border <border-bit>*)
;;;    <border-bit>      := (<border-kind> <color> <width>)
;;;    <border-kind>     := frame
;;;    <border-kind>     := drop-shadow

;;;    <frame-section> := (frame-section <layout-spec> <frame-components>*)
;;;    <layout-spec>  := (top <size> <partition-detail>*)
;;;    <layout-spec>  := (bottom <size> <partition-detail>*)
;;;    <layout-spec>  := (left <size> <partition-detail>*)
;;;    <layout-spec>  := (right <size> <partition-detail>*)

;;;    <partition-detail> := (<minimum?> <maximum?>)  ;; TBD
;;;    <minimum?>     := <integer>
;;;    <minimum?>     := nil
;;;    <maximum?>     := <integer>
;;;    <maximum?>     := nil

(defun project-frame (purpose frame-description
			      left-edge-of-frame-in-workspace ; really, in parent coordinates.
			      top-edge-of-frame-in-workspace
			      right-edge-of-frame-in-workspace
			      bottom-edge-of-frame-in-workspace
			      interior-projection?)
  #+development
  (unless frame-description
    (cerror "Go On." "No frame-description?"))
  
  (with-named-dynamic-extent frame-projecting
      ((purpose-of-frame-projecting purpose)
       (orientation-of-frame 'square)
       (control-stack-of-frame-projecting (graphics-list frame-description))
       (left-edge-of-frame left-edge-of-frame-in-workspace)
       (top-edge-of-frame top-edge-of-frame-in-workspace)
       (right-edge-of-frame right-edge-of-frame-in-workspace)
       (bottom-edge-of-frame bottom-edge-of-frame-in-workspace))
    ;; The frame itself is now always drawn in paint-mode.  Note that we may
    ;; or may not be on-window here, but with-paint-mode handles that.  -fmw,
    ;; 6/21/95
    (with-paint-mode ()
      (project-frame-1 ()))

    (when interior-projection?
      (funcall interior-projection?))))


;;; `Project-frame-1' implements the recursive process of projecting a frame
;;; description.  It expects to find a list of <frame-component> on the
;;; control-stack-of-frame-projecting, it pops the first of these off and does
;;; what it suggests.

(defun project-frame-1 (partition-details-of-current-branch-of-frame)
  (within-named-dynamic-extent frame-projecting
    (let ((remaining-space-for-variable-size-pieces-of-frame
	    (if (eq orientation-of-frame 'vertical)
		(-r bottom-edge-of-frame top-edge-of-frame)
		(-r right-edge-of-frame left-edge-of-frame)))
	  (remaining-number-of-size-pieces-of-frame 0))

      ;; Adjust the layout budget given the partition-details.
      (loop for chunk-size? in partition-details-of-current-branch-of-frame
	    do
	(when (eq 'slice-size chunk-size?)
	  (setf chunk-size? current-slice-size?))
	(cond
	  (chunk-size?
	   (decfr remaining-space-for-variable-size-pieces-of-frame
		  chunk-size?))
	  (t (incff remaining-number-of-size-pieces-of-frame))))
      (loop doing
	(when (null (first control-stack-of-frame-projecting))
	  (graphics-pop control-stack-of-frame-projecting)
	  (return nil))

	;; Pack part using info from the partition-details and the budget
	;; we setup a moment ago.
	(when partition-details-of-current-branch-of-frame
	  (let* ((chunk-size-spec
		   (pop partition-details-of-current-branch-of-frame))
		 (chunk-size
		   (cond
		     ((eq 'slice-size chunk-size-spec)
		      current-slice-size?)
		     ((fixnump chunk-size-spec)
		      chunk-size-spec)
		     (t
		      #+development
		      (when chunk-size-spec (error "unknown chunksize spec."))
		      (let ((var-chunk-size
			      (truncatef
				remaining-space-for-variable-size-pieces-of-frame
				remaining-number-of-size-pieces-of-frame)))
			(decff remaining-number-of-size-pieces-of-frame)
			(decff remaining-space-for-variable-size-pieces-of-frame
			       var-chunk-size)
			var-chunk-size)))))
	    (case orientation-of-frame
	      (vertical
	       (setf bottom-edge-of-frame (+r top-edge-of-frame chunk-size)))
	      (horizontal
	       (setf right-edge-of-frame (+r left-edge-of-frame chunk-size))))))

	;; Emit this component.
	(let ((instruction
		(pop (first control-stack-of-frame-projecting))))

	  (with-drawing-trace (project-frame)
	    (format t "Frame component: ~s" instruction))

	  (when (or (eq (first instruction) 'frame-section)
		    (frame-interesting-p))
	    (case (first instruction)

	      ;; Frame components that mess with the layout.
	      (frame-section
	       (let* ((layout-specification (second instruction))
		      (partition-details (cddr layout-specification))
		      (current-slice-size? (let ((slice-size
						   (second
						     layout-specification)))
					     (if (eq slice-size 'slice-size)
						 current-slice-size?
						 slice-size)))
		      (branch-frame-description (cddr instruction)))
		 (macrolet ((do-branch ()
			      `(when (frame-interesting-p)
				 (graphics-push
				   branch-frame-description
				   control-stack-of-frame-projecting)
				 (project-frame-2 partition-details))))

		   (case (first layout-specification)
		     (top
		      (let ((bottom-edge-of-frame
			      (+f top-edge-of-frame current-slice-size?))
			    (orientation-of-frame 'horizontal))
			(do-branch)
			(setf top-edge-of-frame bottom-edge-of-frame)))
		     (bottom
		      (let ((top-edge-of-frame
			      (-f bottom-edge-of-frame current-slice-size?))
			    (orientation-of-frame 'horizontal))
			(do-branch)
			(setf bottom-edge-of-frame top-edge-of-frame)))
		     (right
		      (let ((left-edge-of-frame
			      (-f right-edge-of-frame current-slice-size?))
			    (orientation-of-frame 'vertical))
			(do-branch)
			(setf right-edge-of-frame left-edge-of-frame)))
		     (left
		      (let ((right-edge-of-frame
			      (+f left-edge-of-frame current-slice-size?))
			    (orientation-of-frame 'vertical))
			(do-branch)
			(setf left-edge-of-frame right-edge-of-frame)))))))
	      
	      ;; Frame components that both mess with layout, and emit ink.
	      (border           (project-border-for-frame (rest instruction)))
	      
	      ;; Frame Components that just emit ink.
	      (paper                 (project-paper-for-frame))
	      (scroll-bar            (project-scroll-bar-for-frame))
	      (title-bar             (project-title-bar-for-frame (second instruction)))
	      (resize-box            (project-resize-box-for-frame))
	      (close-box            (project-close-box-for-frame (second instruction)))
	      (elevator-shaft        (project-shaft-of-scroll-bar-for-frame))
	      (up-arrow        (project-arrow-of-scroll-bar-for-frame 'up))
	      (down-arrow      (project-arrow-of-scroll-bar-for-frame 'down))
	      (left-arrow      (project-arrow-of-scroll-bar-for-frame 'left))
	      (right-arrow     (project-arrow-of-scroll-bar-for-frame 'right))
	      #+development
	      (otherwise (error "Unknown frame-component.")))))

	;; Shift toward next part of partitioning
	(case orientation-of-frame
	  (vertical
	   (setf top-edge-of-frame bottom-edge-of-frame))
	    (horizontal
	     (setf left-edge-of-frame right-edge-of-frame)))))))


(defun project-frame-2 (partition-details)
  (let ((left-edge-of-frame left-edge-of-frame)
	(top-edge-of-frame top-edge-of-frame)
	(right-edge-of-frame right-edge-of-frame)
	(bottom-edge-of-frame bottom-edge-of-frame))
    (project-frame-1 partition-details)))






(defvar current-create-frame-description-reference-1)

;;; `Create-frame-description-reference' ...

(defun-simple create-frame-description-reference (frame-description)
  (let ((current-create-frame-description-reference-1
	  (make-frame-description-reference frame-description)))
      (project-frame
	'compute-content-region
	frame-description
	0 0 0 0
	#'create-frame-description-reference-1)
      current-create-frame-description-reference-1))

(defun-void create-frame-description-reference-1 ()
  (setf (left-frame-indent current-create-frame-description-reference-1)
	left-edge-of-frame)
  (setf (top-frame-indent current-create-frame-description-reference-1)
	top-edge-of-frame)
  (setf (right-frame-indent current-create-frame-description-reference-1)
	(-r right-edge-of-frame))
  (setf (bottom-frame-indent current-create-frame-description-reference-1)
	(-r bottom-edge-of-frame)))

#+unused
(defun-simple current-image-plane-edge-is-volatile (edge)
  (loop for component in (frame-description-of-image-plane current-image-plane)
	when (and (eq (car component) 'frame-section)
		  (eq (car (second component)) edge)
		  (memq 'nil (cddr (second component))))
	  do (return t)))


;;; `Move-Elevator' sets the position of the elevators of the block given
;;; as specified.  It updates the block's slots and moves the elevators
;;; displayed on any images of that block.  The block's displayed contents
;;; is not revised, that is the caller's responiblity.

;;; This is implemented by projecting the frame in move-elevator mode, and
;;; that in turn will wander down to the project-elevator routine which in
;;; due course will actually redraw the elevators and set the block.

(defun move-elevator (block
			 new-position-of-horizontal-elevator
		       new-position-of-vertical-elevator)
  (with-named-dynamic-extent frame-projecting
      ((block-of-frame block)
       (new-position-of-horizontal-elevator-of-frame
	 new-position-of-horizontal-elevator)
       (new-position-of-vertical-elevator-of-frame
	 new-position-of-vertical-elevator))
    (let ((frame-transforms-of-block?
	    (frame-transforms-of-block block)))
      (cond
	;; In the absence of any images, we can just update the KB state.
	((not frame-transforms-of-block?)
	 (update-elevator-positions-of-block-1 'vertical)
	 (update-elevator-positions-of-block-1 'horizontal))
	;;
	(t
	 (let* ((any-frame-transform-of-frame
		  (cdr (first frame-transforms-of-block?)))
		(frame-description-reference
		  (frame-description-reference-of-frame-transform
		    any-frame-transform-of-frame))
		(left-edge-of-frame
		  (-w (left-edge-of-block block)
		      (left-frame-indent frame-description-reference)))
		(top-edge-of-frame
		  (-w (top-edge-of-block block)
		      (top-frame-indent frame-description-reference)))
		(right-edge-of-frame
		  (+w (right-edge-of-block block)
		      (right-frame-indent frame-description-reference)))
		(bottom-edge-of-frame
		  (+w (bottom-edge-of-block block)
		      (bottom-frame-indent frame-description-reference))))
	   (project-frame
	     'move-elevator
	     (frame-description-of-frame-description-reference
	       frame-description-reference)
	     left-edge-of-frame
	     top-edge-of-frame
	     right-edge-of-frame
	     bottom-edge-of-frame
	     nil)))))))

;; (move-elevator (ci 'edit-box) (position-of-horizontal-elevator (ci 'edit-box)) (position-of-vertical-elevator (ci 'edit-box)))

(defun move-elevator-within-shaft
    (left-of-elevator top-of-elevator right-of-elevator bottom-of-elevator)
  ;; We are called out of projection with the frame bound to the elevator shaft.
  ;; The edges of the old elevator were computed in the projection
  ;; routine, we now compute the edges of the new elevator.
  (multiple-value-bind (left-edge-of-new-elevator
			 top-edge-of-new-elevator
			 right-edge-of-new-elevator
			 bottom-edge-of-new-elevator)
      (edges-of-elevator
	orientation-of-frame
	left-edge-of-frame
	top-edge-of-frame
	right-edge-of-frame
	bottom-edge-of-frame
	(if (eq orientation-of-frame 'vertical)
	    new-position-of-vertical-elevator-of-frame
	    new-position-of-horizontal-elevator-of-frame))
    (let ((region-invalidation-is-preferred t)
	  (workspace
	    ;; Move-elevator assured we were called only on things with images,
	    ;; hence things with workspaces.
	    (get-workspace-if-any block-of-frame)))
      (macrolet ((update-images-of-elevator-areas (erase?)
		   `(progn
		      ;; Update the area with the old elevator position
		      (update-images
			,erase? block-of-frame workspace
			left-of-elevator
			top-of-elevator
			(+f right-of-elevator 1)
			(+f bottom-of-elevator 1)
			nil ; :no-bleeding -- damn rubber stamps.
			'draw-block
			block-of-frame)
		      ;; Update the area with the new elevator position
		      (update-images
			,erase? block-of-frame workspace
			left-edge-of-new-elevator
			top-edge-of-new-elevator
			(+f right-edge-of-new-elevator 1)
			(+f bottom-edge-of-new-elevator 1)
			nil ; :no-bleeding  -- damn rubber stamps
			'draw-block
			block-of-frame)
		      )))
	(with-deferred-drawing-in-process ()
	  (update-images-of-elevator-areas t)
	  (update-elevator-positions-of-block-1 orientation-of-frame)
	  (update-images-of-elevator-areas nil))))))

(defun update-elevator-positions-of-block-1 (orientation)
  (when (eq orientation 'horizontal)
    (setf (position-of-horizontal-elevator block-of-frame)
	  new-position-of-horizontal-elevator-of-frame))
  (when (eq orientation 'vertical)
    (setf (position-of-vertical-elevator block-of-frame)
	  new-position-of-vertical-elevator-of-frame)))







;;;; Projecting Frame Components

;;; This section contains the routines that project individual
;;; components in the frame, resize boxes, paper, scroll bars, etc.

;;; Each routine is very stylized since these routines much dispatch
;;; on the purpose-of-frame-projecting.  These routines all execute
;;; within the dynamic extent of frame-projecting as established
;;; by project-frame.





;;; `Generate-workspace-background-spot' is called from those blocks
;;; that are actually transparent.  For example page-numbers in logbooks.

(defun-void generate-workspace-background-spot (mouse-pointer)
  (push-last-spot mouse-pointer
		  (make-workspace-background-spot)
		  (frame-represented? (stack-of-spots mouse-pointer))))


;;; `Track-mouse-over-frame' is called to generate spots in a mouse pointer
;;; which describe what portion of the frame the mouse lies over.  It is called
;;; with a mouse pointer that must lie within the frame, but not inside the
;;; frame provided.  Upon return the mouse pointer will have been fully
;;; tracked.  This is called with a rectangle in WINDOW coordinates of the
;;; outer edges of the workspace's frame, when block is a workspace.

(defun track-mouse-over-frame (mouse-pointer frame-description block
					     left top right bottom)
  (with-named-dynamic-extent frame-projecting
      ((block-of-frame block)
       (mouse-pointer-of-frame mouse-pointer))
    (let ((original-head-of-stack-of-spots (stack-of-spots mouse-pointer-of-frame)))
      (with-unlimited-time-slice	        ; Do it to completion! -fmw, 2/23/94
	(project-frame 'mouse-tracking
		       frame-description
		       left top right bottom
		       nil))

      (unless (eq original-head-of-stack-of-spots
		  (stack-of-spots mouse-pointer-of-frame))
	(setf (further-tracking-maybe-required?
		(stack-of-spots mouse-pointer-of-frame))
	      nil))))

  ;; The project-frame must have yielded at least one new spot as a result of
  ;; tracking the pointer.  If not, there was a "black hole".  The following
  ;; development checks for such black holes, which should never be.
  ;; (MHD/BHyde, 9/28/99)
  #+development
  (when (further-tracking-maybe-required? (stack-of-spots mouse-pointer))
    (cerror "Oh No!" "Tracking error.")
    (push-last-spot mouse-pointer
		    (make-workspace-background-spot)
		    block)))


;;; `Frame-rectangle-with-clipping' is a utility routine used in this
;;; section to paint a frame in a rectangle of a given thickness.  This is
;;; the routine which draws workspace borders, for example.

(defun frame-rectangle-with-clipping (pen-thickness)
  ;; Paint in reading order, top, left, right, bottom while avoiding overlap.
  (unless (=f 0 pen-thickness)
    (let ((scaled-left-edge-of-frame (x-in-window left-edge-of-frame))
	  (scaled-top-edge-of-frame (y-in-window top-edge-of-frame))
	  (scaled-right-edge-of-frame (x-in-window right-edge-of-frame))
	  (scaled-bottom-edge-of-frame (y-in-window bottom-edge-of-frame))
	  (scaled-x-pen-thickness
	    (delta-x-in-window pen-thickness current-image-x-scale))
	  (scaled-y-pen-thickness
	    (delta-y-in-window pen-thickness current-image-y-scale))
	  (scaled-left-inner-edge
	    (x-in-window (+r left-edge-of-frame pen-thickness)))
	  (scaled-top-inner-edge
	    (y-in-window (+r top-edge-of-frame pen-thickness)))
	  (scaled-right-inner-edge
	    (x-in-window (-r right-edge-of-frame pen-thickness)))
	  (scaled-bottom-inner-edge
	    (y-in-window (-r bottom-edge-of-frame pen-thickness)))
	  (color-difference
	    (color-difference current-foreground-color-value
			      current-background-color-value)))
      (macrolet ((my-draw-rectangle (left top right bottom)
		   `(with-clipping-to-draw-area? ((a b c d)
						  (,left ,top ,right ,bottom))
		      (draw-solid-rectangle a b c d color-difference))))
	(cond
	  ;; devolve into a vertical or horizontal line?
	  ((or (>=f scaled-left-edge-of-frame (-f scaled-right-edge-of-frame
						 scaled-x-pen-thickness
						 scaled-x-pen-thickness))
	       (>=f scaled-top-edge-of-frame (-f scaled-bottom-edge-of-frame
						scaled-x-pen-thickness
						scaled-y-pen-thickness)))
	   ;; Emit NOTHING if everything mapped into one point.
	   (unless (or (=f scaled-left-edge-of-frame
			   scaled-right-edge-of-frame)
		       (=f scaled-top-edge-of-frame
			   scaled-bottom-edge-of-frame))
	     (my-draw-rectangle scaled-left-edge-of-frame
				scaled-top-edge-of-frame
				scaled-right-edge-of-frame
				scaled-bottom-edge-of-frame)))

	  (t
	   (progn ;; Use a hairline if necessary
	     (when (=f scaled-left-edge-of-frame scaled-left-inner-edge)
	       (incff scaled-left-inner-edge))
	     (when (=f scaled-top-edge-of-frame scaled-top-inner-edge)
	       (incff scaled-top-inner-edge))
	     (when (=f scaled-right-edge-of-frame scaled-right-inner-edge)
	       (decff scaled-right-inner-edge))
	     (when (=f scaled-bottom-edge-of-frame scaled-bottom-inner-edge)
	       (decff scaled-bottom-inner-edge))	 )  
	   (my-draw-rectangle scaled-left-edge-of-frame scaled-top-edge-of-frame
			      scaled-right-edge-of-frame scaled-top-inner-edge)
	   (my-draw-rectangle scaled-left-edge-of-frame scaled-top-inner-edge
			      scaled-left-inner-edge scaled-bottom-inner-edge)
	   (my-draw-rectangle scaled-right-inner-edge scaled-top-inner-edge
			      scaled-right-edge-of-frame
			      scaled-bottom-inner-edge)
	   (my-draw-rectangle
	     scaled-left-edge-of-frame  scaled-bottom-inner-edge
	     scaled-right-edge-of-frame scaled-bottom-edge-of-frame)))))))

;; The hairline code doesn't bleed because the code that lets things
;; devolve into a line will trigger in the case where it would (or
;; at least that was my intent).



(defun paint-rectangle-with-clipping ()
  ;; Paint in reading order, top, left, right, bottom while avoiding overlap.
  (let ((scaled-left-edge-of-frame (x-in-window left-edge-of-frame))
	(scaled-top-edge-of-frame (y-in-window top-edge-of-frame))
	(scaled-right-edge-of-frame (x-in-window right-edge-of-frame))
	(scaled-bottom-edge-of-frame (y-in-window bottom-edge-of-frame))
	(color-difference
	  (color-difference current-foreground-color-value
			    current-background-color-value)))
    (with-clipping-to-draw-area? ((a b c d)
				  (scaled-left-edge-of-frame
				    scaled-top-edge-of-frame
				    scaled-right-edge-of-frame
				    scaled-bottom-edge-of-frame))
      (draw-solid-rectangle a b c d color-difference))))



;;; The function `image-plane-border-color' changes the outermost border color
;;; of selected image-planes. FIXME: only want to do this if the image-plane
;;; does not have a title bar!

(defun image-plane-border-color (image-plane color index)
  (cond ((or (>f index 0)
	     (not (selection-enabled-p (gensym-window-for-image-plane image-plane)))
	     (not (selectable-image-plane-p image-plane))
	     (image-plane-selected-p image-plane))
	 color)
	(t
	 'dim-gray)))


;;; `Project-border-for-frame' will render a nested series of
;;; bounding framed rectangles into current frame.  These are
;;; described by the argument, which is documented in the grammar
;;; shown above in project-frame.

(defun-void project-border-for-frame (border-description) ; eg, ((FRAME BLACK 3))
  (within-named-dynamic-extent frame-projecting
    (let ((symmetric-indent 0)
	  (drop-shadow-indent 0))

      ;; Make a first pass to get total indent
      (loop for (kind nil size) in border-description
	    do (case kind
		 (frame (incff symmetric-indent size))
		 (drop-shadow (incff drop-shadow-indent size))))

      ;; Now do the modal behavior
      (case purpose-of-frame-projecting
	((drawing drawing-paper)
	 (loop for (kind color size) in border-description
	       as index from 0
	       as current-foreground-color-value
		  = (map-color-or-metacolor-to-color-value
		      (image-plane-border-color current-image-plane color index))
	       doing
	   (case kind
	     (frame
	      (unless (eq 'transparent color)
		(frame-rectangle-with-clipping size))
	      (indent-frame size))
	     #+comment
	     (drop-shadow
	      ;; (frame-drop-shadow-with-clipping size)
	      (decff right-edge-of-frame size)
	      (decff bottom-edge-of-frame size))
	     #+development
	     (t
	      (error "Kind of border?")))))

	(drawing-contents ;; maintain the indent for clipping.
;         (indent-frame symmetric-indent)
;         (decff right-edge-of-frame drop-shadow-indent)
;         (decff bottom-edge-of-frame drop-shadow-indent)
	 )

	((compute-content-region move-elevator)
	 (indent-frame symmetric-indent)
	 (decff right-edge-of-frame drop-shadow-indent)
	 (decff bottom-edge-of-frame drop-shadow-indent))
	(mouse-tracking
	 (indent-frame symmetric-indent)
	 (decff right-edge-of-frame drop-shadow-indent)
	 (decff bottom-edge-of-frame drop-shadow-indent)
	 (unless (point-inside-rectangle-p
		   (x-of-mouse-pointer mouse-pointer-of-frame)
		   (y-of-mouse-pointer mouse-pointer-of-frame)
		   (x-in-window left-edge-of-frame)
		   (y-in-window top-edge-of-frame)
		   (x-in-window right-edge-of-frame)
		   (y-in-window bottom-edge-of-frame))
	   (push-last-spot mouse-pointer-of-frame
			   (make-workspace-background-spot)
			   block-of-frame)))))))




;;; `Project-paper-for-frame' is responsible for drawing the paper
;;; that the workspace is layed out upon.  This paper is a block of
;;; color as specified in the workspace on the image-plane, together
;;; with possible background images.

(defun-void project-paper-for-frame ()
  (within-named-dynamic-extent frame-projecting
    (case purpose-of-frame-projecting
      (drawing-paper
       (sketch-paper-for-current-image-plane
	 (x-in-window left-edge-of-frame)
	 (y-in-window top-edge-of-frame)
	 (x-in-window right-edge-of-frame)
	 (y-in-window bottom-edge-of-frame)))

      (drawing
       (setq drawing-state-for-project-paper
	     (draw-paper-for-current-image-plane
	       drawing-state-for-project-paper
	       (x-in-window left-edge-of-frame)
	       (y-in-window top-edge-of-frame)
	       (x-in-window right-edge-of-frame)
	       (y-in-window bottom-edge-of-frame))))

      (drawing-contents
       nil)
      
      (compute-content-region
       ;; Nothing to do.
       nil)
      (move-elevator
       nil)
      (mouse-tracking
       ;; An exceptional case, the paper has no behavior: the
       ;; document placed upon the paper must give it behavior.
       ;; If the spot generation had a conflict resolution mechinism
       ;; we could give paper a behavior.
       nil))))


(defun tiled-image-spec-for-image-plane (image-plane)
  (loop for image-spec in (image-plane-background-images image-plane)
	if (image-spec-tiled-p image-spec)
	  return image-spec))


;;; The function `sketch-paper-for-current-image-plane' draws the low
;;; resolution paper for an image-plane, in a project-frame context.
;;; Currently, that's just the workspace background color, without any
;;; background images.

(defun sketch-paper-for-current-image-plane (left top right bottom)
  (with-drawing-trace (pop)
    (format t " Sketch ~s" current-image-plane))
  (with-clipping-to-draw-area? ((left-edge-of-draw-area
				  top-edge-of-draw-area
				  right-edge-of-draw-area
				  bottom-edge-of-draw-area)
				(left top right bottom))

    ;; Undo the with-null-drawing-transform in paint-empty-image-plane
    (with-image-plane-transform (current-image-plane)

      (let* ((background-color-value
	       (compute-workspace-background-color-value
		 current-image-plane))
	     (tiled-image-spec? 
	       (tiled-image-spec-for-image-plane current-image-plane))
	     (tiled-image-data?
	       (and tiled-image-spec?
		    (find-image-data (image-spec-image-name tiled-image-spec?)))))
	
	;; Note: If we ever permit transparency in tiled images, we'd need to
	;; fill the background color in either case.
	(cond (tiled-image-data?
	       ;; Very old TW's sometimes lie about whether they can draw
	       ;; images.  For example, a TW-4.1 displaying on a 24-bit X server
	       ;; is unable to draw 8-bit images, and just ignores requests to
	       ;; do so (with a warning message).  As a result, if we didn't
	       ;; clear the background here, then nothing whatsoever would get
	       ;; drawn for the paper, resulting in horrible turds.  So, for
	       ;; such old TW's (approximated by supports-icon-image-painting),
	       ;; we clear the rectangle AND draw the tiled images, just in case
	       ;; the images are not drawn after all. -fmw, 7/10/02
	       (unless (window-supports-icon-image-painting current-window)
		 (paint-solid-rectangle
		   left-edge-of-draw-area top-edge-of-draw-area
		   right-edge-of-draw-area bottom-edge-of-draw-area
		   background-color-value))
	       (draw-background-image
		 current-image-plane
		 tiled-image-data?
		 (image-spec-user-x-position tiled-image-spec?)
		 (image-spec-user-y-position tiled-image-spec?)
		 (image-spec-tiled-p tiled-image-spec?)
		 left top right bottom
		 (compute-workspace-foreground-color-value current-image-plane)
		 background-color-value))
	      (t
	       (paint-solid-rectangle
		 left-edge-of-draw-area top-edge-of-draw-area
		 right-edge-of-draw-area bottom-edge-of-draw-area
		 background-color-value)))

	(when (visible-grid-p current-image-plane)
	  (draw-alignment-grid
	    left-edge-of-draw-area top-edge-of-draw-area
	    right-edge-of-draw-area bottom-edge-of-draw-area))

	;; This call ensures that any "gray area" we are vacating gets erased.
	(when (image-plane-native-window? current-image-plane)
	  (paint-unused-area-of-native-image-plane current-image-plane))))))

;; I suppose we could draw blocks of gray where the images go.  Anybody care?

;; IWBNI this did not clear underneath the workspace border.  They flash as it
;; is now.

;; I wish I could ask that all the images have been sent, and that their
;; renderings are cached.  But that info currently lives only in TW.  Makes one
;; think that paper drawing ought to be a TW function.




;;; The function `draw-paper-for-current-image-plane' paints the paper for
;;; an image-plane within the given rectangle in window coordinates, clipping
;;; to the current draw area.

(defun draw-paper-for-current-image-plane (state? left top right bottom)
  (with-clipping-to-draw-area? ((left-edge-of-draw-area
				  top-edge-of-draw-area
				  right-edge-of-draw-area
				  bottom-edge-of-draw-area)
				(left top right bottom))
    ;; Undo the with-null-drawing-transform in paint-background-of-image-plane
    (with-image-plane-transform (current-image-plane)

      (let ((background-color-value
	      (compute-workspace-background-color-value
		current-image-plane)))

	(cond ((null (image-plane-background-images current-image-plane))
	       (paint-solid-rectangle
		 left-edge-of-draw-area top-edge-of-draw-area
		 right-edge-of-draw-area bottom-edge-of-draw-area
		 background-color-value)
	       (setq state? nil))			    ; Done.
	      (t
	       ;; Clear the space around the images, but don't clear the frame.
	       ;; This is nice because it means that the workspace frame will
	       ;; be visible during the long interval while the image is being
	       ;; rendered (or transmitted to a TW).  The frame will be drawn
	       ;; again later, but since it is now always drawn in paint mode,
	       ;; it won't matter if it is drawn twice. -fmw, 6/21/95
	       (when (null state?)
		 (let* ((images-region
			  (region-containing-background-images
			    current-image-plane))
			(background-region
			  (make-region-from-rectangle
			    (left-edge-of-workspace-area-in-window current-image-plane)
			    (top-edge-of-workspace-area-in-window current-image-plane)
			    (right-edge-of-workspace-area-in-window current-image-plane)
			    (bottom-edge-of-workspace-area-in-window current-image-plane)))
			(net-region
			  (subtract-region
			    background-region images-region)))
		   
		   (fill-region-with-color net-region background-color-value)
		   (reclaim-region net-region)
		   (reclaim-region background-region)
		   (reclaim-region images-region)
		   (setq state? 'images)))

	       ;; Now draw the images.  State is either an atom or a list of info.
	       (when state?
		 (setq state?
		       (draw-background-images
			 current-image-plane
			 (if (eq state? 'images) nil state?)
			 left-edge-of-draw-area top-edge-of-draw-area
			 right-edge-of-draw-area bottom-edge-of-draw-area)))))

	(when (and (null state?)
		   (visible-grid-p current-image-plane))
	  (draw-alignment-grid
	    left-edge-of-draw-area top-edge-of-draw-area
	    right-edge-of-draw-area bottom-edge-of-draw-area)))))
  state?)

;; Note: Since we might have done this for any opaque blocks on the workspace
;; (and in paint mode, all blocks are opaque), our only justification for doing
;; this only for background images is the tacit assumption that images cover
;; most of the workspace, or that there are not many of them.  -fmw, 5/2/94




(defun fill-region-with-color (region color-value)
  (do-projection-thru-region
      ((left top right bottom)
       (left-edge-of-draw-area
	 top-edge-of-draw-area
	 right-edge-of-draw-area
	 bottom-edge-of-draw-area)
       region)
    (paint-solid-rectangle left top right bottom color-value)))




;;; `Draw-rubber-stamp-widget-in-frame' calls thru to draw-rubber-stamp-widget
;;; asking for it to render the stamp into the current frame bounds.

(defun-void draw-rubber-stamp-widget-in-frame (rubber-stamp-widget)
  (draw-rubber-stamp-widget rubber-stamp-widget
			    left-edge-of-frame top-edge-of-frame
			    right-edge-of-frame bottom-edge-of-frame))



;;; `Project-scroll-bar-for-frame' renders a scroll bar in the current
;;; this is oriented as per the `orientation-of-frame' which should
;;; be either 'horizontal or 'vertical.

(defun project-scroll-bar-for-frame ()
  (within-named-dynamic-extent frame-projecting
    (case purpose-of-frame-projecting
      (drawing-paper
       (frame-rectangle-with-clipping 1))
      ((drawing mouse-tracking move-elevator)
       (project-frame 
	 purpose-of-frame-projecting
	 (if (eql orientation-of-frame 'vertical)
	     `((frame-section (right slice-size slice-size nil slice-size)
			      (up-arrow)
			      (elevator-shaft)
			      (down-arrow)))
	     `((frame-section (bottom slice-size slice-size nil slice-size)
			      (left-arrow)
			      (elevator-shaft)
			      (right-arrow))))
	 left-edge-of-frame top-edge-of-frame
	 right-edge-of-frame bottom-edge-of-frame
	 nil))

      (drawing-contents
       nil)
      (compute-content-region
       nil))))


;;; `Frame-component-spot' is an abstract type included into each of
;;; the spots generated for the components of a frame.  It has slots that
;;; remember the edges of the frame.

(def-spot frame-component-spot
    :slots ((left-edge-of-scroll-bar-spot left-edge-of-frame)
	    (top-edge-of-scroll-bar-spot top-edge-of-frame)
	    (right-edge-of-scroll-bar-spot right-edge-of-frame)
	    (bottom-edge-of-scroll-bar-spot bottom-edge-of-frame))
    :include workspace-background-spot  ;; Not right but keeps things functional for now.
    :enclosing-spot-type image-plane-spot
    :type-of-frame-represented block
    :innermost-spot-p t
    :abstract-type t)

(def-spot elevator-shaft-spot
    :slots (orientation-of-shaft)
    :include frame-component-spot
    :innermost-spot-p nil)

(def-spot stepper-of-scroll-bar-spot
    :slots (direction-of-step ;; left, right, up, down
	     amount-of-step)  ;; page or line.
    :include frame-component-spot
    :abstract-type nil)

(defun make-stepper-of-scroll-bar-spot-plus (direction amount)
  (let ((spot (make-stepper-of-scroll-bar-spot)))
    (setf (direction-of-step spot) direction)
    (setf (amount-of-step spot) amount)
    spot))

(def-spot elevator-of-scroll-bar-spot
    :slots (orientation-of-elevator)  ;; Vertical or Horizontal
    :include frame-component-spot
    :abstract-type nil)

(defun make-elevator-of-scroll-bar-spot-plus (orientation)
  (let ((spot (make-elevator-of-scroll-bar-spot)))
    (setf (orientation-of-elevator spot)
	  orientation)
    spot))

(defun project-arrow-of-scroll-bar-for-frame (direction)
  (within-named-dynamic-extent frame-projecting
    (case purpose-of-frame-projecting
      (drawing-paper
       (frame-rectangle-with-clipping 1))
      (drawing
;       (frame-rectangle-with-clipping 1)
       (draw-rubber-stamp-widget-in-frame
	 (case direction
	   (left  'gensym-left-scroll-arrow-frame-component)
	   (right 'gensym-right-scroll-arrow-frame-component)
	   (up    'gensym-up-scroll-arrow-frame-component)
	   (down  'gensym-down-scroll-arrow-frame-component))))
      ((drawing-contents move-elevator)
       nil)
      (compute-content-region
       nil)
      (mouse-tracking
       (push-last-spot
	 mouse-pointer-of-frame
	 (let ((spot (make-stepper-of-scroll-bar-spot-plus direction 'line)))
	   spot)
	 block-of-frame)))))

(defun project-shaft-of-scroll-bar-for-frame ()
  (within-named-dynamic-extent frame-projecting
    (case purpose-of-frame-projecting
      (drawing-paper
       (frame-rectangle-with-clipping 1))
      (drawing
       (let ((light-grey-color-value (map-to-color-value 'light-grey)))
	 (let ((current-foreground-color-value light-grey-color-value))
	   (paint-rectangle-with-clipping))
	 (with-background-color-value light-grey-color-value
	   (frame-rectangle-with-clipping 1)
	   (project-elevator-of-scroll-bar-for-frame)))
       )
      (move-elevator
       (project-elevator-of-scroll-bar-for-frame))
      (drawing-contents
       nil)
      (compute-content-region
       nil)
      (mouse-tracking
       (let ((spot (make-elevator-shaft-spot)))
	 (setf (orientation-of-shaft spot) orientation-of-frame)
	 (push-more-detailed-spot mouse-pointer-of-frame spot block-of-frame))
       ;; Only the elevator knows how to find the subparts of the shaft
       (project-elevator-of-scroll-bar-for-frame)))))

(defun position-of-elevator-as-offset-given-scale
    (position-as-scale shaft-width shaft-height)
  (scalef position-as-scale (-f shaft-height shaft-width)))


(defun position-of-elevator-as-scale-given-offset
    (position-as-offset shaft-width shaft-height)
  (cond ((squareable-fixnum-p position-as-offset)
	 (values ;; One value only.
	   ;; Can't use inverse-scalef: it expects the scale to be positive.
	   (roundf (*f position-as-offset #.(normalized-scale))
		   (-f shaft-height shaft-width))))
	(t
	 (inverse-scalef-function (-f shaft-height shaft-width)
				  position-as-offset))))



;;; `Edges-of-elevator' is a extent independent routine that returns the edges
;;; of the elevator inside of the shaft given.  This is used both in the
;;; projection of the elevator and in the workstation context that drags the
;;; elevator.

(defun edges-of-elevator (orientation
			   left-edge-of-shaft
			   top-edge-of-shaft
			   right-edge-of-shaft
			   bottom-edge-of-shaft
			   position-of-elevator-as-scale
			   ;; (if vertical?
			   ;;   (position-of-vertical-elevator block)
	                   ;;   (position-of-horizontal-elevator block))
			   )
  (let* ((vertical? (eq orientation 'vertical))
	 (height (-f bottom-edge-of-shaft top-edge-of-shaft 2))
	 (width (-f right-edge-of-shaft left-edge-of-shaft 2))
	 (shaft-width (if vertical? width height))
	 (shaft-height (if vertical? height width))
	 (top-of-elevator (+f top-edge-of-shaft 1)) ;; 1st aprox.
	 (left-of-elevator (+f left-edge-of-shaft 1)) ;; 1st aprox.
	 (position-of-elevator-as-shaft-offset
	   (position-of-elevator-as-offset-given-scale
	     position-of-elevator-as-scale shaft-width shaft-height)))
    (if vertical?
	(incff top-of-elevator position-of-elevator-as-shaft-offset)
	(incff left-of-elevator position-of-elevator-as-shaft-offset))
    (values left-of-elevator top-of-elevator
	    (+f left-of-elevator shaft-width)
	    (+f top-of-elevator shaft-width))))

(defun project-elevator-of-scroll-bar-for-frame ()
  (within-named-dynamic-extent frame-projecting
    (let* ((vertical? (eq orientation-of-frame 'vertical)))
      (multiple-value-bind (left-of-elevator
			     top-of-elevator
			     right-of-elevator
			     bottom-of-elevator)
	  (edges-of-elevator orientation-of-frame
			     left-edge-of-frame
			     top-edge-of-frame
			     right-edge-of-frame
			     bottom-edge-of-frame
			     (if vertical?
				 (position-of-vertical-elevator block-of-frame)
				 (position-of-horizontal-elevator block-of-frame)))
	(case purpose-of-frame-projecting
	  (drawing-paper
	   ;; When drawing only the paper we don't show the elevator.
	   nil)
	  ((drawing drawing-contents)
	   ;; When drawing anything else we get the paper right.
	   (let ((left-edge-of-frame left-of-elevator)
		 (top-edge-of-frame top-of-elevator)
		 (right-edge-of-frame right-of-elevator)
		 (bottom-edge-of-frame bottom-of-elevator))
	     (draw-rubber-stamp-widget-in-frame
	       'gensym-scroll-bar-elevator-frame-component)))
	  (compute-content-region
	   nil)
	  (move-elevator
	   (move-elevator-within-shaft
	     left-of-elevator top-of-elevator right-of-elevator bottom-of-elevator))
	  (mouse-tracking
	   ;; Compute the last spot for all three portions of the shaft.
	   (let* ((x-in-window (x-of-mouse-pointer mouse-pointer-of-frame))
		  (y-in-window (y-of-mouse-pointer mouse-pointer-of-frame))
		  (left-edge-of-elevator-in-window
		    (x-in-window left-of-elevator))
		  (top-edge-of-elevator-in-window
		    (y-in-window top-of-elevator))
		  (right-edge-of-elevator-in-window
		    (x-in-window right-of-elevator))
		  (bottom-edge-of-elevator-in-window
		    (y-in-window bottom-of-elevator))
		  (spot 
		    (cond
		      (vertical?
		       (cond
			 ((<f y-in-window top-edge-of-elevator-in-window)
			  (make-stepper-of-scroll-bar-spot-plus 'up 'page))
			 ((<f y-in-window bottom-edge-of-elevator-in-window)
			  (make-elevator-of-scroll-bar-spot-plus 'vertical))
			 (t
			  (make-stepper-of-scroll-bar-spot-plus 'down 'page))))
		      (t  ;; Horizontal
		       (cond
			 ((<f x-in-window left-edge-of-elevator-in-window)
			  (make-stepper-of-scroll-bar-spot-plus 'left 'page))
			 ((<f x-in-window right-edge-of-elevator-in-window)
			  (make-elevator-of-scroll-bar-spot-plus 'horizontal))
			 (t
			  (make-stepper-of-scroll-bar-spot-plus
			    'right 'page)))))))
	     (when (elevator-of-scroll-bar-spot-p spot)
	       (setf (left-edge-of-scroll-bar-spot spot) left-of-elevator)
	       (setf (top-edge-of-scroll-bar-spot spot) top-of-elevator)
	       (setf (right-edge-of-scroll-bar-spot spot) right-of-elevator)
	       (setf (bottom-edge-of-scroll-bar-spot spot) bottom-of-elevator))
	     (push-last-spot mouse-pointer-of-frame spot block-of-frame))))))))




(defun image-plane-has-new-g2-classic-title-bar-p (image-plane)
  (let* ((frame-description-reference
	   (frame-description-reference-of-image-plane image-plane))
	 (frame-description
	   (frame-description-of-frame-description-reference
	     frame-description-reference))
	 (frame-section-3? (third frame-description)))
    (and frame-section-3?
	 (eq (first frame-section-3?) 'frame-section)
	 (eq (first (second frame-section-3?)) 'top)
	 (consp (third frame-section-3?))
	 (eq (first (third frame-section-3?)) 'title-bar))))



;;; The function `make-title-bar-text-for-workspace' returns a text data
;;; structure according to spec....

(defparameter default-workspace-title-bar-text-spec
  '(name class))

;; The Alpha and beta spec was implicitly (table-header), but that proved rather
;; unpopular.  Users did not want the ", a <class>" to come after the name if
;; the workspace had a name.

(defun make-title-bar-text-for-workspace (workspace spec)
  (twith-output-to-text
    (if spec				; else blank
	(if (atom spec)
	    (make-title-bar-text-per-directive-or-string workspace spec)	
	    (loop for element in spec
		  until (make-title-bar-text-per-directive-or-string workspace element))))))


(defun make-title-bar-text-per-directive-or-string (workspace directive-or-string)
  (case directive-or-string
    (name
     (let ((name? (get-primary-name-for-frame-if-any workspace)))
       (when name?
	 (write-name-for-frame name?)
	 t)))
    (names
     (let ((name-or-names? (name-or-names-for-frame workspace)))
       (when name-or-names?
	 (write-name-or-names-from-slot ; slot writer
	   name-or-names? workspace)
	 t)))
    (a-or-an+class	; as in a table header
     (write-symbol-with-a-or-an (class workspace))
     t)
    (class		; as in a workspace menu; see
     ;; refer to translated-string-for-symbol
     (twrite-symbol-name
       (class workspace)
       :first-of-each-word t nil  known-gensym-acronyms)
     t)
    (table-header
     (write-class-instance-header-from-slot ; slot writer
       (class workspace)
       workspace)
     t)
    (uuid
     (twrite-uuid-printed-representation-as-string
       (uuid workspace)))
    (t
     (if (text-string-p directive-or-string)
	 (twrite-string directive-or-string)
	 (dwarn "Unknown title-text option: ~s" directive-or-string)))))




;;; The function `workspace-title' returns a newly consed text string or NIL.

(defun workspace-title (workspace?)
  (cond ((null workspace?))
	((title-bar-caption-text workspace?)
	 (convert-text-to-text-string
	   (title-bar-caption-text workspace?)))
	(t
	 (let ((text (make-title-bar-text-for-workspace
		       workspace?
		       (or (title-bar-text workspace?)
			   default-workspace-title-bar-text-spec))))
	   (prog1 (convert-text-to-text-string text)
	     (reclaim-text text))))))


;;; The function `title-bar-background-color' returns the desired background
;;; color for the title bar of given image-plane, as a symbol. For historical
;;; reasons, menu workspaces always have a blue title bar, even though they are
;;; not selectable. Other unselectable workspaces do not get a blue title bar.

(defun title-bar-background-color (image-plane)
  (cond ((or (not (selection-enabled-p (gensym-window-for-image-plane image-plane)))
	     (menu-workspace-p (workspace-on-image-plane? image-plane))
	     (image-plane-selected-p image-plane))
	 'dark-slate-blue)
	(t
	 'dim-gray)))

(defun title-bar-foreground-color (image-plane)
  (cond ((or (not (selection-enabled-p (gensym-window-for-image-plane image-plane)))
	     (menu-workspace-p (workspace-on-image-plane? image-plane))
	     (image-plane-selected-p image-plane))
	 'white)
	(t
	 'gray)))


;;; `Project-title-bar-for-frame'


(defun project-title-bar-for-frame (font-size)
  (within-named-dynamic-extent frame-projecting
    (case purpose-of-frame-projecting
      ((drawing-paper drawing)
       (let* ((workspace? (workspace-on-image-plane? current-image-plane))
	      (reclaim-title-text-p nil)
 	      (title-text?
 		(if workspace?
 		    (or (title-bar-caption-text workspace?)
 			(progn
 			  (setq reclaim-title-text-p t)
 			  (make-title-bar-text-for-workspace
 			    workspace?
 			    (or (title-bar-text workspace?)
 				default-workspace-title-bar-text-spec))))))
	      (background-color (map-to-color-value
				  (title-bar-background-color current-image-plane)))
	      (foreground-color (map-to-color-value
				  (title-bar-foreground-color current-image-plane))))
	 (draw-solid-rectangle
	   left-edge-of-frame top-edge-of-frame
	   right-edge-of-frame bottom-edge-of-frame
	   (color-difference
	     background-color
	     current-background-color-value))
	 (when title-text?
	   (with-background-color-value
	       background-color
	     (let ((current-foreground-color-value foreground-color)
		   (lower-match-rank-for-player-eyes-p t)) ; just to keep qa-test from breaking, no joke! (MHD 4/1/02)
	       (draw-title-bar-text
		 title-text? font-size
		 left-edge-of-frame top-edge-of-frame
		 right-edge-of-frame bottom-edge-of-frame))))
	 (when reclaim-title-text-p
	   (reclaim-text title-text?))))
      ((drawing-contents compute-content-region move-elevator)
       nil)
      (mouse-tracking
       ;; We do not use push-last-spot here, since there may be further spots
       ;; for the close box, et al. (MHD 9/28/99)
       (push-more-detailed-spot
	 mouse-pointer-of-frame
	 (make-title-bar-spot)
	 block-of-frame)))))



;;; `Refresh-title-bar' refreshes the title bar of a workspace.  This is to be
;;; used whenever the text of the title bar may have been changed, e.g., when
;;; changing the name of an item represented in a "classic" attribute table.

(defun refresh-title-bar (workspace)
  (loop for image-plane in (image-planes-this-is-on workspace)
	do 
    (refresh-title-bar-of-image-plane image-plane)))



;;; The function `refresh-title-bar-of-image-plane' refreshes the workspace
;;; title bar only on given image-plane.

(defun refresh-title-bar-of-image-plane (image-plane)
  (let ((left (left-edge-of-image-in-window image-plane))
	(top (top-edge-of-image-in-window image-plane))
	(right (right-edge-of-image-in-window image-plane))
	(bottom (top-edge-of-workspace-area-in-window image-plane)))
    (with-region-from-rectangle-void (region left top right bottom)
      (invalidate-region-of-image-plane image-plane region))
    (update-native-title-bar image-plane)))


;;; The function `refresh-borders-of-image-plane' wants to refresh the borders
;;; but not the title bar.  Of course, since frame descriptions are so general,
;;; it is hopeless, so we just refresh the entire frame.

(defun refresh-borders-of-image-plane (image-plane)
  (with-region-from-rectangle-void (outer-region
				     (left-edge-of-image-in-window image-plane)
				     (top-edge-of-image-in-window image-plane)
				     (right-edge-of-image-in-window image-plane)
				     (bottom-edge-of-image-in-window image-plane))
    (with-region-from-rectangle-void (inner-region
				       (left-edge-of-workspace-area-in-window image-plane)
				       (top-edge-of-workspace-area-in-window image-plane)
				       (right-edge-of-workspace-area-in-window image-plane)
				       (bottom-edge-of-workspace-area-in-window image-plane))
      (let ((border-region (subtract-region outer-region inner-region)))
	(invalidate-region-of-image-plane image-plane border-region)
	(reclaim-region border-region)))))


;;; `Project-resize-box-for-frame' renders the resize box of an image-plane.



(def-spot resize-box-spot
    :slots (near-left-edge? near-right-edge? near-bottom-edge? near-top-edge?)
    :include workspace-background-spot  ;; Not right but keeps things functional for now.
    :enclosing-spot-type image-plane-spot
    :innermost-spot-p t
    :abstract-type nil
    :type-of-frame-represented block)

(defun project-resize-box-for-frame ()
  (within-named-dynamic-extent frame-projecting
    (case purpose-of-frame-projecting
      (drawing-paper
       (frame-rectangle-with-clipping 1))
      (drawing
       (draw-rubber-stamp-widget-in-frame 'gensym-resize-box-frame-component))
      (drawing-contents
       nil)
      (compute-content-region
       nil)
      (move-elevator
       nil)
      (mouse-tracking
       (let* ((spot (make-resize-box-spot))
;              (x-of-box (halfr (+r left-edge-of-frame right-edge-of-frame)))
;              (y-of-box (halfr (+r top-edge-of-frame bottom-edge-of-frame)))
;              (size-of-box (maxr (-r right-edge-of-frame left-edge-of-frame)
;                                 (-r bottom-edge-of-frame top-edge-of-frame)))
	      )
;         (macrolet ((f (near-left-edge? x-of-box x-in-window left-edge-of-block)
;                      `(let ((distance
;                             (absr
;                               (-r ,x-of-box
;                                   (,x-in-window
;                                     (,left-edge-of-block block-of-frame))))))
;                        (setf (,near-left-edge? spot)
;                              (<r distance size-of-box)))))
;           (f   near-left-edge? x-of-box x-in-window   left-edge-of-block)
;           (f    near-top-edge? y-of-box y-in-window    top-edge-of-block)
;           (f  near-right-edge? x-of-box x-in-window  right-edge-of-block)
;           (f near-bottom-edge? y-of-box y-in-window bottom-edge-of-block))
;         (d spot)
	 (push-last-spot mouse-pointer-of-frame spot block-of-frame))))))



;; the following cloned and specialized from "resize" box. (MHD 9/13/99)
(def-spot close-box-spot
    :include spot
    :enclosing-spot-type image-plane-spot
    :innermost-spot-p t
    :abstract-type nil
    :type-of-frame-represented workspace)

(defun project-close-box-for-frame (size)
  (within-named-dynamic-extent frame-projecting
    (case purpose-of-frame-projecting
      ((drawing drawing-paper drawing-close-box)
       ;; Notice that we assume here that a close box lives only on a title bar.
       (let ((background 
	       (title-bar-background-color current-image-plane)))
	 (when (eq purpose-of-frame-projecting 'drawing-close-box)
	   ;; For situation changes (e.g., changing to pending), we have to redraw
	   ;; this for now -- for some reason, our frame is shifted a pixel to the
	   ;; left for now, and this extra paint masks the turds that would
	   ;; otherwise result if we just repainted the icon. (!!) (MHD 9/29/99)
	   (draw-solid-rectangle
	     left-edge-of-frame top-edge-of-frame
	     right-edge-of-frame bottom-edge-of-frame
	     (color-difference
	       (map-to-color-value background)
	       current-background-color-value)))
	 (with-background-color-value (map-to-color-value background)
	   (let* ((current-foreground-color-value (map-to-color-value 'white))
		  (situation (image-plane-close-box-situation current-image-plane))
		  (widget-entity
		    (progn
		      #+development
		      (test-assertion (memq situation '(normal pending na)))
		      (getf close-box-rubber-stamp-widget situation))))
	     (with-shifted-origin ((left-edge-of-block widget-entity)
				   (top-edge-of-block widget-entity)
				   (+r left-edge-of-frame 4)
				   (+r top-edge-of-frame
				       (case size (small 4) (t 5))))
	       (draw-icon-for-entity widget-entity))))))
      (drawing-contents
       nil)
      (compute-content-region
       nil)
      (move-elevator
       nil)
      (mouse-tracking
       (let* ((spot (make-close-box-spot)))
	 (push-last-spot mouse-pointer-of-frame spot block-of-frame))))))



;;;; User Grammar for Frame Descriptions

;;; Let's start with an example.  This frame description:

;;;     ((border (frame black 2))
;;;      (paper)
;;;      (frame-section (bottom 16 nil 16)
;;;		     (scroll-bar)
;;;		     (resize-box))
;;;      (frame-section (right 16 nil)
;;;		     (scroll-bar)))

;;; Is specified by the user with this grammar.

;;;    border black 2;
;;;    place on bottom in a space 16 high: scroll-bar, resize-box;
;;;    place on right in a space 16 wide: scroll-bar;


;;; First we start with the writer.

(def-slot-value-writer frame-description (frame-description?)
  (if frame-description?
      (write-frame-description-1 frame-description?)
      (twrite-string "none")))

(define-category-evaluator-interface (frame-description :access read-write)
    (or (no-item)
	(sequence
	  (structure border-element
		     ((color symbol)
		      (width integer))
		     (and color width))
	  1))
  ((set-form (evaluation-value))
   (evaluation-etypecase evaluation-value
    ((no-item) nil)
    ((sequence)
     (block setter
       (phrase-list 
	 (phrase-cons
	   'border
	   (with-evaluation-sequence-to-phrase-list-mapping
	       (evaluation-value border-element)
	     (let ((color (evaluation-structure-slot border-element 'color)))
	       (unless (color-or-metacolor-p color)
		 (return-from setter
		   (values bad-phrase
			   (tformat-text-string "Invalid color: ~a" color))))
	       (phrase-list
		 'frame color (evaluation-structure-slot border-element 'width))))))))))
  ((get-form (slot-value))
   (and
     slot-value
     (loop with color-width-pairs = '()
	   for frame-component in slot-value
	   when (eq (car frame-component) 'border)
	     do (loop for (nil color width) in (cdr frame-component)
		      do
		  (gensym-push (gensym-cons color width) color-width-pairs))
	   finally
	     (setf color-width-pairs (nreverse color-width-pairs))
	     (let ((sequence
		     (with-list-to-evaluation-sequence-mapping
			 (color-width-pairs pair)
		       (allocate-evaluation-structure-inline
			 'color (car pair)
			 'width (cdr pair)))))
	       (reclaim-gensym-tree color-width-pairs)
	       (return sequence))))))
	     
		  

(defun write-frame-description-1 (frame-description)
  (loop
    with first? = t
    for (frame-component . remaining-components) on frame-description
    do
    (unless (eq 'paper (car frame-component))
      (unless first?
	(tformat ";~%"))
      (setf first? nil)
      (write-frame-component frame-component))))


(defun write-frame-component (frame-component)
  (case (car frame-component)
    (border
     (twrite-string "border")
     (loop for (kind color size) in (rest frame-component)
	   as first? = t then nil
	   do
       (unless first? (tformat ", "))
       (tformat " ~D ~(~A~)" size color)))
    ((resize-box close-box scroll-bar)
     (tformat "~(~A~)" (first frame-component)))
;    (paper
;     ;; These are slipped into by the slot value compiler,
;     ;; before the first non-border,
;     ;; they are invisible to the user.
;     )
    (frame-section
     (let* ((partition (second frame-component))
	    (components (cddr frame-component))
	    (where (first partition))
	    (partition-size (second partition))
	    (layouts (cddr partition)))
       (tformat "along the ~(~A~) using ~D workspace units place: "
		where
		partition-size)
       (loop for component in components
	     as layout in layouts
	     as first? = t then nil
	     do
	 (if first?
	     (tformat "~%    ")
	     (tformat ",~%    "))
	 (tformat "a ~(~A~)" (first component))
	 (cond
	   (layout
	    (tformat " of size ~D" layout))
	   (t
	    (tformat " of variable size"))))))
    #+development
    (T
     (error "unknown kind of frame-component"))))

;;; In the grammar rules that follow the comments show the internal
;;; Lisp form's syntax that the grammar reduce into.

;;;    <frame-description> := (<frame-component>*)

(def-grammar-category frame-description-1 ()
  (frame-component (1))
  (( frame-component '\; frame-description-1) (1 . 3)))

;;;    <frame-component> :=  <frame-section>
;;;    <frame-component> :=  <border-component>

(def-grammar-category frame-component ()
  ; (frame-section)
  (border-component))

;; Frame sections were disabled when workspace scrolling was disabled.
;; Note that they may still appear internally for blocks with borders
;; that the internals of G2 create. - ben 6/29/94

;;;    <border-component> := (border <border-bit>*)
;;;    <border-bit>      := (<border-kind> <color> <width>)
;;;    <border-kind>     := frame

(def-grammar-category border-component ()
  (('border border-bits) (1 . 2)))

(def-grammar-category border-bits ()
  (border-bit (1))
  ((border-bit '\, border-bits) (1 . 3)))

(def-grammar-category border-bit ()
  ((positive-integer color) (frame 2 1)))



;;;    <frame-section> := (frame-section <layout-spec> <frame-component-1>*)
;;;    <layout-spec>  := (top <size> <partition-detail>*)
;;;    <layout-spec>  := (bottom <size> <partition-detail>*)
;;;    <layout-spec>  := (left <size> <partition-detail>*)
;;;    <layout-spec>  := (right <size> <partition-detail>*)

#+tbd
(def-grammar-category frame-section ()
  (('along 'the frame-section-edge
	   'using positive-integer 'workspace 'units
	   'place '\: frame-components-with-layouts)
   (3 5 10) reduce-frame-section))

#+tbd
(def-grammar-category frame-section-edge ()
   ('left)
   ('top)
   ('right)
   ('bottom))

#+tbd
(def-grammar-category frame-components-with-layouts ()
  (frame-component-with-layout (1))
  ((frame-component-with-layout `\, frame-components-with-layouts) (1 . 3)))

#+tbd
(def-grammar-category frame-component-with-layout ()
     (('a frame-component-1 'of frame-component-layout) (2 . 4))
     (('variable 'size) t)
     (('size positive-integer) 2))

#+tbd
(def-grammar-category frame-component-1 ()
   ('scroll-bar (1))
   ('resize-box (1))
   ('close-box (1)))

#+tbd
(defun reduce-frame-section (parse)
  ;; (bottom 16 (((scroll-bar) . t) ((resize-box) . 16)))
  ;; --> (frame-section  (bottom 16 t 16) (scroll-bar) (resize-box))
  (let ((edge (first parse))
	(size (second parse))
	(frame-components-with-layouts (third parse)))
    (loop
      for (component . layout) in frame-components-with-layouts
      collect component into frame-components using phrase-cons
      collect (if (eq t layout) nil layout)
	into layouts using phrase-cons
      finally
	(return
	  (phrase-list*
	    'frame-section
	    (phrase-list* edge size layouts)
	    frame-components)))))

;;; The root is frame-description.

(def-grammar-category frame-description ()
  ('none nil)
  (frame-description-1))

(def-slot-value-compiler frame-description (parse-of-frame-description)
  (when parse-of-frame-description
    (loop named outer-loop 
	  for frame-component in parse-of-frame-description 
	  when (eq (car frame-component) 'border)
	    do (loop for (nil color width) in (cdr frame-component)
		     do
		 (when (<f width 0)
		   ;; Checks that all widths specified must be non-negative
		   ;; integers.  But no check has been added for e.g. an 
		   ;; incorrectly spelled color despite the precedent with
		   ;; e.g. connection stripes.  Instead, a black border is
		   ;; drawn in this case. - jpg 5/31/00
		   (return-from outer-loop 
		     (values
		       bad-phrase
		       (tformat-text-string 
			 "The frame description width ~a must be a non-negative integer."
			 width)))))
	  finally
	    ;; insert a paper instruction after before the first non-frame
	    (return-from outer-loop
	      (phrase-cons (phrase-list 'paper)
			   parse-of-frame-description)))
    ))




;;;; Standard Frame Descriptions



;;; There is a small set of built in frame descriptions used for
;;; workspaces.  These are enuemrated here for the benifit of Meta-dot.
;;; they are implemented in the routine
;;; `lookup-frame-description-reference-of-frame-style'

#+development
(defparameter dialog-workspace-frame-style nil)
#+development
(defparameter menu-workspace-frame-style nil)
#+development
(defparameter default-workspace-frame-style nil)
#+development
(defparameter credits-workspace-frame-style nil)
#+development
(defparameter thick-workspace-frame-style nil)  ;; Help Workspaces.
#+development
(defparameter extremely-thin-workspace-frame-style nil)  ;; Workspaces in workspace views.
#+development
(defparameter item-frame-used-when-frame-style-is-incomplete nil)
#+development
(defparameter edit-box-frame-style nil)
#+development
(defparameter edit-box-with-scroll-bar-frame-style nil)

(def-kb-specific-property-name frame-description-reference-of-built-in-frame-style
    release-frame-description-reference-if-any)

(defparameter workspace-title-bar-frame-style-small
  '((paper) (border (frame dark-slate-blue 1))
    (frame-section
     (top 24) (title-bar small)
     (frame-section
      (right 24) (close-box small)))))

(defparameter workspace-title-bar-frame-style-large
  '((paper) (border (frame dark-slate-blue 1))
    (frame-section
     (top 28) (title-bar large)
     (frame-section
      (right 24) (close-box large)))))


;;; `Lookup-frame-description-reference-of-frame-style' implements the look up
;;; of from a frame style to a frame-description-reference.  It searchs, and
;;; handles the undefined case.  It looks first for a user definition, i.e.  an
;;; OK instance of frame-style-definition, then it looks for a built in
;;; definition, and finally it gives up and uses the default-frame-style passed
;;; as an argument, this should be one of the built in frame styles.

(defun lookup-frame-description-reference-of-frame-style
    (frame-style default-frame-style)
  (or
    ;; First try any names the user had defined.
    (lookup-frame-description-reference-from-frame-style-definition?
      frame-style)
    
    ;; Do we have something built in and cons'd up in this KB?
    (frame-description-reference-of-built-in-frame-style
      frame-style)
    
    (progn
      ;; Do we know this name and can cons up something?
      (unless (memq frame-style
		    '(dialog-workspace-frame-style
		      #+development old-menu-workspace-frame-style
		      menu-workspace-frame-style
		      workspace-title-bar-frame-style-small
		      workspace-title-bar-frame-style-large
		      walking-menu-frame-style
		      :credits-workspace-frame-style
		      :new-credits-workspace-frame-style
		      :item-frame-used-when-frame-style-is-incomplete
		      :edit-box-frame-style
		      :edit-box-with-scroll-bar-frame-style
		      thick-workspace-frame-style
		      extremely-thin-workspace-frame-style
		      default-workspace-frame-style))
	;; Nope, fall back on the default-frame-style
	(setf frame-style default-frame-style))
      ;; Cons up and remember one of these.
      (or (frame-description-reference-of-built-in-frame-style
	    frame-style)
	  (setf (frame-description-reference-of-built-in-frame-style
		  frame-style)
		(reference-frame-description-reference
		  (create-frame-description-reference
		    (copy-tree-using-graphics-conses
		      (case frame-style
			(dialog-workspace-frame-style
			 `((paper)
			   (border (frame black 1) (frame white 2)
				   (frame black 2))))

 			#+development
 			(old-menu-workspace-frame-style
 			 `((paper)
 			   (border (frame black 1)
 				   (frame green 2))))

			(menu-workspace-frame-style
			 `((paper)
			   (border (frame black 1))))
			
			(workspace-title-bar-frame-style-small
			 workspace-title-bar-frame-style-small)
			
			(workspace-title-bar-frame-style-large
			 workspace-title-bar-frame-style-large)
			
			(walking-menu-frame-style
			 `((paper)
			   (border (frame black 1))))

			(:credits-workspace-frame-style
			 `((paper)
			   (border (frame dark-gray 3))))
 			(:new-credits-workspace-frame-style
			 `((paper)
			   (border (frame dim-gray 3))))

			(:item-frame-used-when-frame-style-is-incomplete
			 `((paper)
			   (border (frame black 1))))
			(:edit-box-with-scroll-bar-frame-style
			 '((paper)
			   (border (frame black 2))
			   (frame-section (right 21 nil) (scroll-bar))
			   (border (frame transparent 2))))
			(:edit-box-frame-style
			 '((paper)
			   (border (frame black 2))))
			(thick-workspace-frame-style
			 `((paper)
			   (border (frame black 5))))
			(extremely-thin-workspace-frame-style
			 `((paper)
			   (border (frame black 1))))
			(default-workspace-frame-style
			    `((paper)
			      (border (frame black 3)))))))))))))






;;; The function `image-plane-has-default-frame-p' is true if image-plane
;;; has a default workspace frame style. 

(defun image-plane-has-default-frame-p (image-plane)
  (let ((workspace (workspace-on-image-plane? image-plane)))
    (or (null workspace)  ; test probably unnec., for safety
	(null (frame-style workspace))
	(let ((frame-description-reference
		(frame-description-reference-of-image-plane image-plane)))
	  (eq frame-description-reference
	      (get-default-workspace-frame-description-reference))))))

(defun get-default-workspace-frame-description-reference ()
  (lookup-frame-description-reference-of-frame-style
    'default-workspace-frame-style
    'default-workspace-frame-style))







;;;; Subblock Frame Transforms and Image-planes


(defun block-is-allowed-to-have-frame-p (block)
  (frame-class-case block
    (workspace t)
;    (free-text t)  
;    (borderless-free-text t)
    (edit-box t)
    (block nil)))

(defun default-frame-style-of-block-when-user-request-is-bogus? (block)
  (frame-class-case block
    (workspace 'default-workspace-frame-style)
    (block :item-frame-used-when-frame-style-is-incomplete)))

(defun default-frame-style-of-block? (block)
  (frame-class-case block
    (menu-workspace
      (if new-g2-classic-ui-p
	  (cond
	    ((get-slot-value		; fwd. ref.
	       block 'menu-workspace-for-is-for-walking-submenu-p)
	     ;; If this is a submenu WALKING-MENU as its reason-to-..., then
	     ;; it's a walking menu, and should have a plain frame style.
	     'walking-menu-frame-style)
	    (t
	     (get-ui-parameter 'workspace-title-bar-frame-style)))
	  'menu-workspace-frame-style))
    ((logbook-page) 'default-workspace-frame-style) ; system-defined, old-UI oriented
    (workspace
      (if new-g2-classic-ui-p
	  (get-ui-parameter 'workspace-title-bar-frame-style)
	  'default-workspace-frame-style))
    (block
	nil)))



;;; The substitution-macro `frame-style-of-block' returns the frame-style
;;; of a block.  In 4.0, this is a workspace slot.  Later, it maybe
;;; taken from the object configuration.

(def-substitution-macro frame-style-of-block (block)
  (or
    (frame-class-case block
      (workspace
	(frame-style block))
      (edit-box
	(get-slot-value block 'frame-style-of-edit-box 'edit-box))
      (block
	  nil)
      #+development
      (root
	(error "OH NO")))
    (default-frame-style-of-block? block)))

;; This was:
;; (get-format-value-in-object-configuration block 'frame-style nil))

(defun set-frame-style-of-block (block frame-style)
  (frame-class-case block
    (workspace
      (setf (frame-style block) frame-style))
    (edit-box
      (set-slot-value block 'frame-style-of-edit-box frame-style 'edit-box))
    #+development
    (root
      (error "OH NO"))))

  
(defsetf frame-style-of-block set-frame-style-of-block)



;;; `Lookup-frame-description-reference-of-block?' will return nil or a
;;; frame-description-reference for the block by looking up the
;;; frame-style configuration of the object.  This is used when
;;; the frame might currently be displayed wrong.

(defun lookup-frame-description-reference-of-block? (block)
  (when (block-is-allowed-to-have-frame-p block)
    (let ((frame-style (frame-style-of-block block)))
      (if (null frame-style)
	  nil
	  (lookup-frame-description-reference-of-frame-style
	    frame-style
	    (default-frame-style-of-block-when-user-request-is-bogus? block))))))

; Deferred from 4.0
;(defun lookup-frame-description-reference-of-block? (block)
;  (when (block-is-allowed-to-have-frame-p block)
;    (let (frame-style)
;      (when (setf frame-style
;                  (or (get-format-value-in-object-configuration
;                        block 'frame-style nil)
;                      (default-frame-style-of-block? block)))
;        (lookup-frame-description-reference-of-frame-style
;          frame-style
;          (default-frame-style-of-block-when-user-request-is-bogus? block))))))



;;; `Create-frame-transforms-of-image-plane' spawn a frame transform for each
;;; subblock of the workspace that has a frame description and associate it with
;;; image-plane and the workspace.

(defun create-frame-transforms-of-image-plane (workspace image-plane)
  (let (frame-description-reference)
    (when (setf frame-description-reference
		(lookup-frame-description-reference-of-block? workspace))
      (make-frame-transform
	workspace image-plane
	(reference-frame-description-reference
	  frame-description-reference))))
  (loop with frame-description-reference
	for subblock being each subblock of workspace
	do
    (when (setf frame-description-reference
		(lookup-frame-description-reference-of-block? subblock))
      (make-frame-transform
	subblock image-plane
	(reference-frame-description-reference
	  frame-description-reference)))))



;;; `Fast-lookup-frame-description-reference-of-block?' is the same as
;;; lookup-frame-description-reference-of-block? but it trusts the current
;;; display and hence can optimize the case when the block is currently
;;; showing.

(defun fast-lookup-frame-description-reference-of-block? (block)
  (let (frame-transforms
	 frame-transform
	 frame-style)
    (cond
      ;; If this is showing, we can assume the current frame transforms are
      ;; uptodate and useful
      ((showing-p block t)
       (if (and (setf frame-transforms (frame-transforms-of-block block))
		(setf frame-transform (cdr (car frame-transforms))))
	   (frame-description-reference-of-frame-transform
	     frame-transform)))
      (T
       (if (setf frame-style (frame-style-of-block block))
	   (lookup-frame-description-reference-of-frame-style
	     frame-style
	     :item-frame-used-when-frame-style-is-incomplete))))))




;;; `Clean-frame-description-references' is the consequence of noticing that a
;;; the frame description defined at a given place has changed.  The place
;;; where the frame style is defined marks the frame-description-reference
;;; dirty, and then installs the new frame description-reference, if any, for
;;; that place.  He then calls this routine, which tours the window hierarchy
;;; from workstations-in-service down to the individual subblocks.
;;; Image-planes or subblocks with dirty frames have the class method
;;; `reconsider-formatting' invoked on them.

(defun-void clean-frame-description-references ()
  (loop
    for workstation in workstations-in-service
    as gensym-window = (window-for-workstation workstation)
    do
    (loop
      for pane in (panes-in-window gensym-window)
      do
      (when (workspace-on-image-plane? ;; See `pane-area-hack'
	      (first (stack-of-image-planes pane)))
	(loop
	  for image-plane in (stack-of-image-planes pane)
	  as frame-description-reference-of-image-plane
	     = (frame-description-reference-of-image-plane image-plane)

	  ;; Image-plane is Dirty?
	  when (dirty-frame-description-reference
		 frame-description-reference-of-image-plane)
	    do (funcall-method 'reconsider-formatting
			       (workspace-on-image-plane? image-plane)
			       'frame-description-reference)

	      ;; Subblocks in this image-plane are dirty?
	      ;; Quick check for dirty frames in here.
	  when (loop for frame-transform
			 = (frame-transforms-of-blocks-in-image-plane image-plane)
			 then (next-frame-transform-of-this-image-plane?
				frame-transform)
		     while frame-transform
		     thereis (dirty-frame-description-reference
			       (frame-description-reference-of-frame-transform
				 frame-transform)))
	    do
	      (loop for subblock
			being each subblock of (workspace-on-image-plane? image-plane)
		    as frame-transforms-of-block
		       = (frame-transforms-of-block subblock)
		    when (and frame-transforms-of-block
			      (dirty-frame-description-reference
				(frame-description-reference-of-frame-transform
				  (cdr (first frame-transforms-of-block)))))
		      do
			(funcall-method 'reconsider-formatting
					subblock
					'frame-description-reference)))))))


;;; `Reconsider-formatting' is a method on blocks, called when event may have
;;; triggered the need to reformat compute the format of a block.  A second
;;; argument, a symbol, denotes what aspect of the formatting may have changed.

;;; This routine should implement concequences as necessary.  For example it
;;; might check that the format has actually changed, it may refresh caches, it
;;; might update the screen.

;;; Refinements to this should be around methods.  See your ancestors to decern
;;; what has actually they do, for example the method on blocks, just below.

;;; It is intended that the set of all legal values for the second argument be
;;; arranged organized in a tree.  The leafs of this tree are the most primitive
;;; changes that can happen to the format, while the interior nodes larger
;;; changes.  Currently the only formating-dimension is
;;; 'dirty-frame-description-reference.

;;; `Dirty-frame-description-reference' denotes that a frame description has
;;; changed and it is necessary to reconsider this blocks frame description and
;;; redraw if necessary.

;;; `Formatting-configuration-changed' indicates that a frame who's object
;;; configuration is might be inherited by this frame has had it's formatting
;;; changed.

(def-generic-method reconsider-formatting (block formatting-dimension)
  )

;;; `Reconsider-formatting of block' will check the frame description of the
;;; block to see if it is dirty.

(def-class-method reconsider-formatting (block formatting-dimension)
  (case formatting-dimension
    (frame-description-reference
     (let (frame-transforms-of-block)
       (cond
	 ((workspace-p block)		; see Note! (MHD 10/25/02)
	  (loop for image-plane in (image-planes-this-is-on block)
		when (dirty-frame-description-reference
		       (frame-description-reference-of-image-plane image-plane))
		  return (rebind-frame-description-reference-of-workspace block)))
	 ((and (setf frame-transforms-of-block
		     (frame-transforms-of-block block))
	       (dirty-frame-description-reference
		 (frame-description-reference-of-frame-transform
		   (cdr (car frame-transforms-of-block)))))
	  (rebind-frame-description-references-of-block
	    block
	    frame-transforms-of-block
	    (lookup-frame-description-reference-of-block?
	      block))))))
    (formatting-configuration-changed     
     (cond
       ((workspace-p block)
	(loop for image-plane in (image-planes-this-is-on block)
	      unless (funcall-for-workstation-of-image-plane
		       image-plane #'image-plane-frame-lookup-eq
		       image-plane block)
		return (rebind-frame-description-reference-of-workspace block)))
       (t
	(let (new-frame-description-reference?
	       old-frame-description-reference?
	       frame-transforms-of-block)
	  ;; Only need to rebind this stuff if we are showing.
	  (when (showing-p block t)
	    ;; If we had a frame already, then get it here.
	    (when (setf frame-transforms-of-block
			(frame-transforms-of-block block))
	      (setf old-frame-description-reference?
		    (frame-description-reference-of-frame-transform
		      (cdr (first frame-transforms-of-block)))))
	    ;; See if the frame has changed.
	    (setq new-frame-description-reference?
		  (lookup-frame-description-reference-of-block? block))
	    (unless (eq old-frame-description-reference?
			(setf new-frame-description-reference?
			      (lookup-frame-description-reference-of-block?
				block)))
	      ;; Yes, rebind it.
	      (rebind-frame-description-references-of-block
		block
		frame-transforms-of-block
		new-frame-description-reference?)))))))
    #+development
    (t
     (error "Unknown formatting-dimension"))))

;; Ben's original comment: sadly workspaces are a special case! MHD: c.f. block
;; case. And note that it is now now required to wrap a for-workstation context
;; around the test for at least one image plane per window/workstation (we
;; currently do all) since the advent of per-window styles in G2 6.0. However,
;; it was only fixed today in 7.0 alpha.  It is not yet known if this will be
;; backpatched to the 6.x stream, which is now at 6.2r1. Refer to this bug:
;; HQ-4377052 "Overriding g2-5.x style windows doesn't work when
;; programmatically merging a KB". (MHD 10/25/02)

;; Note: it seems there should be separate methods for workspace vs. general
;; block case. Review later! (MHD 10/25/02)





;;; The function `image-plane-frame-lookup-eq' is called with an image plane and
;;; a workspace. It looks up the frame description for the workspace and sees if
;;; the image plane currently matches it.  Note that this may be sensitive to
;;; whether we are in a for-workstation context and, if so, the bindings of
;;; various elements of that context.  This is at present only used by the
;;; reconsider-formatting method implementation for block, in the workspace case
;;; only, to determine if a workspace needs to be update to reflect its true
;;; current frame style.

(defun image-plane-frame-lookup-eq (image-plane workspace)  
  (eq (lookup-frame-description-reference-of-block? workspace)
      (frame-description-reference-of-image-plane image-plane)))





(defun rebind-frame-description-references-of-block
    (block old-frame-transforms-of-block new-frame-description-reference?)
  (let (workspace?) 
    (macrolet ((with-redraw-of-images-of-block ((block) &body body)
		 `(updating-images-of-block (,block)
		    ,@body)))
      (with-redraw-of-images-of-block (block)
	(cond
	  ;; We had a frame previously.
	  (old-frame-transforms-of-block
	   (cond
	     ;; Old Frame -> New Frame
	     (new-frame-description-reference?
	      (loop for (nil . frame-transform) in old-frame-transforms-of-block
		    do
		(release-frame-description-reference-if-any
		  (frame-description-reference-of-frame-transform
		    frame-transform))
		(setf (frame-description-reference-of-frame-transform
			frame-transform)
		      (reference-frame-description-reference
			new-frame-description-reference?))))
	     ;; Old Frame -> No Frame
	     (T
	      (reclaim-frame-transforms-of-block block))))
	  (T
	   (cond
	     ;; No frame -> New Frame
	     (new-frame-description-reference?
	      (let (image-planes)
		(when (and (setf workspace? (get-workspace-if-any block))
			   (setf image-planes
				 (image-planes-this-is-on workspace?)))
		  (loop for image-plane in image-planes
			do
		    (make-frame-transform
		      block image-plane
		      (reference-frame-description-reference
			new-frame-description-reference?))))))
	     ;; No frame -> No Frame
	     (t
	      #+development
	      (warn "??? rebind-frame-description-references-of-block."))))))
      (unless (workspace-p block)
	(enlarge-workspace-for-block-rectangle-if-necessary
	  block workspace?)))))


(defun rebind-frame-description-reference-of-workspace (workspace)
  (loop for image-plane in (image-planes-this-is-on workspace)
	do (funcall-for-workstation-of-image-plane ; see note (MHD 10/25/02)
	     image-plane
	     #'rebind-frame-description-reference-image-plane
	     workspace image-plane)))

(defun rebind-frame-description-reference-image-plane (workspace image-plane)
  (let ((new-frame-description-reference
	  (lookup-frame-description-reference-of-block? workspace)))
    (unless (eq new-frame-description-reference
		(frame-description-reference-of-image-plane image-plane))
      (release-frame-description-reference-if-any
	(frame-description-reference-of-image-plane image-plane))
      (setf (frame-description-reference-of-image-plane image-plane)
	    (reference-frame-description-reference
	      new-frame-description-reference))
      (let ((old-left (left-edge-of-image-in-window image-plane))
	    (old-top (top-edge-of-image-in-window image-plane))
	    (old-right (right-edge-of-image-in-window image-plane))
	    (old-bottom (bottom-edge-of-image-in-window image-plane)))
	(set-up-edges-for-image-plane image-plane)
	(recompute-visible-regions-for-pane (pane-for-image-plane image-plane))

	;; Update window's native frame style and shape.
	(when (native-image-plane-p image-plane)
	  (update-native-image-plane-frame-style image-plane)
	  (synchronize-shape-of-native-image-plane image-plane))

	(invalidate-rectangle-of-window
	  (gensym-window-for-pane (pane-for-image-plane image-plane))
	  (minf old-left (left-edge-of-image-in-window image-plane))
	  (minf old-top (top-edge-of-image-in-window image-plane))
	  (maxf old-right (right-edge-of-image-in-window image-plane))
	  (maxf old-bottom (bottom-edge-of-image-in-window image-plane))))
      ;; Better... Intersecting the image-plane's before and after exposed
      ;; regions
      )))

;; Note: the lookup may be sensitive to the workstation context bindings, so we
;; must do it in a for-workstation context. Refer to this bug: HQ-4377052
;; "Overriding g2-5.x style windows doesn't work when programmatically merging a
;; KB". (MHD 10/25/02)




;;; `Propagate-formating-configuration-change' does a depth first tour
;;; of the blocks that would be effected by a change to the configuration
;;; of the block given.  The routine is self recursive with the help of
;;; funcall-function-to-inferior-blocks.  It invokes the reconsider-formatting
;;; method on each block with the formatting-dimension of
;;; formatting-configuration-changed.

#+deferred
(defun-simple propagate-formating-configuration-change (block junk-argument)
  (declare (ignore junk-argument))
  (funcall-function-to-inferior-blocks
		 block
		 #'propogate-formating-configuration-change)
  (funcall-method 'reconsider-formatting
		  block
		  'formatting-configuration-changed))

  
;;; The simple function `reconsider-formatting' reconsiders formatting for
;;; just the given block.  In 4.0, formatting attributes are not inherited.

(defun-simple reconsider-formatting (block)
  (funcall-method 'reconsider-formatting block
		  'formatting-configuration-changed))





;;;; More Image-Plane/Workspace/Pane Utilities



(defun-simple get-image-plane-if-any (workspace pane)
  (loop for image-plane in (stack-of-image-planes pane)
	when (eq (workspace-on-image-plane? image-plane) workspace)
	  return image-plane))

;; Used only by pane commands.
(defun-simple get-or-make-image-plane (workspace pane)
  (or (get-image-plane-if-any workspace pane)
      (get-available-image-plane
	pane
	(lookup-frame-description-reference-of-block? workspace)
	nil)))





;;;; Enlarging or Shrink Wrapping a Workspace






;;; `Block-is-enclosed-by-superior-p' tests if a block lies inside of a block
;;; that has a frame.  Since blocks with frames are assured of having clipping
;;; the rendering of their subblocks inside of the bounds of the block the
;;; extent computations can be subtle.

(defun block-is-enclosed-by-superior-p (block)
  (and (block-is-transformed-p block)
       (block-is-transformed-p (superblock? block))))



;;; `enlarge-workspace-for-block-rectangle-if-necessary' enlarges the workspace
;;; block is or will be upon.  If known-or-future-workspace?  is nil, the
;;; workspace that block is on, if any, is used.

(defun enlarge-workspace-for-block-rectangle-if-necessary
    (block known-or-future-workspace?)
  (let ((workspace?
	  (or known-or-future-workspace? (get-workspace-if-any block))))
    (when workspace?
      (unless (block-is-enclosed-by-superior-p block)
	(multiple-value-bind (left-edge top-edge right-edge bottom-edge)
	    (extreme-edges-of-block block)
	  (enlarge-workspace-if-necessary
	    workspace?
	    left-edge
	    top-edge
	    right-edge
	    bottom-edge))))))




(defun enlarge-workspace-for-block-and-subblocks-as-necessary (block workspace)
  (unless (block-is-enclosed-by-superior-p block)
    (enlarge-workspace-for-block-rectangle-if-necessary block workspace)
    (unless (block-is-transformed-p block)
      (loop for subblock being each subblock of block
	    do
	(enlarge-workspace-for-block-and-subblocks-as-necessary
	  subblock workspace)))))



(defun enlarge-workspace-if-necessary
    (workspace
      left-edge-of-new-element top-edge-of-new-element
      right-edge-of-new-element bottom-edge-of-new-element
      &optional (draw-document-p nil)) ;; Note A
  (let ((current-draw-document-p draw-document-p)
	(workspace-for-current-draw-document? workspace)
	(margin (workspace-margin workspace))
	(new-left? nil)
	(new-top? nil)
	(new-right? nil)
	(new-bottom? nil))
    (when (<w (-w left-edge-of-new-element margin)
	      (left-edge-of-block workspace))
      (setq new-left? (-w left-edge-of-new-element margin)))

    (when (<w (-w top-edge-of-new-element margin)
	      (top-edge-of-block workspace))
      (setq new-top? (-w top-edge-of-new-element margin)))

    (when (>w (+w right-edge-of-new-element margin)
	      (right-edge-of-block workspace))
      (setq new-right? (+w right-edge-of-new-element margin)))

    (when (>w (+w bottom-edge-of-new-element margin)
	      (bottom-edge-of-block workspace))
      (setq new-bottom? (+w bottom-edge-of-new-element margin)))

    (when (change-edges-of-block workspace new-left? new-top? new-right? new-bottom?)
      (move-image-plane-borders workspace))))

;; Note A: This routine should be called when the block being moved, added, or
;; what ever is ERASED.  If we drew the document we would draw the erased block
;; leading to turds in XOR.  I'm not able to prove all the callers obey this
;; rule, hence the optional arg.  So far I've fixed one caller that was calling
;; this with the block drawn.  - ben 5/23/95

;; IMPORTANT: This should check that the workspace has not become so large that
;; fixnum overflow could occur when converting from workspace to window
;; coordinates!  The inspect and describe facilities should independently do
;; such checking, so that no fault will be detected here!




;;; The defun-void `shrink-wrap-workspace' makes the workspace just large
;;; enough to enclose all of its subbblocks and its background image, if any.
;;; If the workspace has no subblocks and no image, then nothing is changed.

(defun-void shrink-wrap-workspace (workspace)
  (when (or (has-subblocks-p workspace)
	    (has-background-images-p workspace))
    (with-extreme-edges-minimizing-workspace (workspace)
      (when (has-subblocks-p workspace)
	(update-extreme-edges-from-elements workspace))
      (update-extreme-edges-from-background-images workspace)  ; Possible bg images.
      (change-workspace-edges-after-including-margin
	workspace
	extreme-left-edge-so-far extreme-top-edge-so-far
	extreme-right-edge-so-far extreme-bottom-edge-so-far))))




;;; `Shrink-wrap-workspace-around-maximum-rectangle' just ensures that the
;;; workspace is no larger than the hard limits imposed by the constant
;;; implementation parameters most-positive-workspace-coordinate and
;;; most-negative-workspace-coordinate, UNLESS it has to be because there are
;;; blocks or a background image there.
;;;
;;; Intuitively, this really hates to shrink-wrap, and will only do it to edges
;;; that jut out too far, and then only if there are no blocks or connections in
;;; the way.
;;;
;;; Since we try to avoid this from occurring while the system is being used
;;; interactively, this isn't much used.  It is used by a post-loading function
;;; to get rid of such cases that got in under older software.  And to fix
;;; "loopholes" in the current software.
;;;
;;; If this can't make a workspace small enough, transform-image has to, and
;;; can, still cope with it, scaling it down as necessary to have window
;;; coordinates as small as the largest "allowable" workspace.
;;;
;;; `Shrink-wrap-down-workspace-around-rectangle' is the more general of these
;;; functions, parameterizing the limit.  This lets you add a box (styrofoam?)
;;; around the goods you're shrinkwrapping.

(defun shrink-wrap-workspace-around-maximum-rectangle (workspace)
  (shrink-wrap-down-workspace-around-rectangle
    workspace
    most-negative-workspace-coordinate most-negative-workspace-coordinate
    most-positive-workspace-coordinate most-positive-workspace-coordinate))

(defun shrink-wrap-down-workspace-around-rectangle
    (workspace left-edge-limit top-edge-limit right-edge-limit bottom-edge-limit)
  (when (or (<w (left-edge-of-block workspace) left-edge-limit)
	    (<w (top-edge-of-block workspace) top-edge-limit)
	    (>w (right-edge-of-block workspace) right-edge-limit)
	    (>w (bottom-edge-of-block workspace) bottom-edge-limit))
    (with-extreme-edges-minimizing-workspace (workspace)
      (update-extreme-edges-from-elements workspace)
      (update-extreme-edges-from-background-images workspace)  ; Possible bg images.
      (change-workspace-edges-after-including-margin
	workspace
	(maxw (minw left-edge-limit extreme-left-edge-so-far)
	      (left-edge-of-block workspace))
	(maxw (minw top-edge-limit extreme-top-edge-so-far)
	      (top-edge-of-block workspace))
	(minw (maxw right-edge-limit extreme-right-edge-so-far)
	      (right-edge-of-block workspace))
	(minw (maxw bottom-edge-limit extreme-bottom-edge-so-far)
	      (bottom-edge-of-block workspace))))))
  






;;; `change-size-of-workspace-to-minimum' is used by the action:
;;;    change the size of <workspace> to minimum

(defun-void change-size-of-workspace-to-minimum (workspace)
  (let ((note-as-kb-state-change? t)
	(do-not-note-permanent-changes-p t))
    (note-kb-state-change workspace 'workspace-frame)
    (shrink-wrap-workspace workspace)))



;;; The function `change-workspace-edges-after-margin-change' updates workspace
;;; edges if necessary so that there is at least a margin size equal to
;;; (workspace-margin workspace) on all four sides.  Note that the workspace is
;;; never shrunk to make the margin smaller; it is only grown to make the
;;; margin big enough.

(defun-void change-workspace-edges-after-margin-change (workspace)
  (when (or (has-subblocks-p workspace)
	    (has-background-images-p workspace))
    (with-extreme-edges-minimizing-workspace (workspace)
      (update-extreme-edges-from-elements workspace)
      (update-extreme-edges-from-background-images workspace)
      (let ((margin (workspace-margin workspace)))
	(new-change-workspace-edges
	  workspace
	  (minr
	    (-r extreme-left-edge-so-far margin)
	    (left-edge-of-block workspace))
	  (minr
	    (-r extreme-top-edge-so-far margin)
	    (top-edge-of-block workspace))
	  (maxr
	    (+r extreme-right-edge-so-far margin)
	    (right-edge-of-block workspace))
	  (maxr
	    (+r extreme-bottom-edge-so-far margin)
	    (bottom-edge-of-block workspace)))))))



;;; `Change-workspace-edges-after-including-margin' calls
;;; new-change-workspace-edges after adding the margin to
;;; the bounds given.

(defun-void change-workspace-edges-after-including-margin
       (workspace
	left-edge-for-workspace top-edge-for-workspace
	right-edge-for-workspace bottom-edge-for-workspace)
  (let ((margin (workspace-margin workspace)))
    (new-change-workspace-edges
      workspace
      (-w left-edge-for-workspace margin)
      (-w top-edge-for-workspace margin)
      (+w right-edge-for-workspace margin)
      (+w bottom-edge-for-workspace margin))))


;;; `New-change-workspace-edges' rebinds the edges of the workspace
;;; block.  This may trigger assorted drawing via a call to
;;; move-image-plane-borders

(defun-void new-change-workspace-edges
    (workspace
      left-edge-for-workspace top-edge-for-workspace
      right-edge-for-workspace bottom-edge-for-workspace)

  (when (change-edges-of-block
	  workspace
	  left-edge-for-workspace top-edge-for-workspace
	  right-edge-for-workspace bottom-edge-for-workspace)

    (move-image-plane-borders workspace)))



;;; `Move-image-plane-borders' is invoked to update images of the borders and
;;; adjacent areas of workspace after one or more of its edges has been changed.

;;; After moving the image, it is forced to be visible by calling require-that-
;;; image-plane-be-visible.

(defun-allowing-unwind move-image-plane-borders (workspace)
  (loop for image-plane in (image-planes-this-is-on workspace) doing
    (reshape-image-plane-of-workspace image-plane)
    (require-that-image-plane-be-visible image-plane)))

;; Consider not doing the require-that-image-plane-be-visible here
;; unconditionally.  It may not be the right thing in all cases! (MHD 3/22/90)




;;; `reshape-image-plane-of-workspace' is used to rebind the edges of the
;;; image-plane when the transform mapping the workspace into that image-plane
;;; is NOT changing.  For example when shrink-wrapping or enlarging the view
;;; area.

;;; For each edge which has changed, we add the rectangle which encloses
;;; both the old and new edges, including the workspace frame.  Then finally
;;; we clip the resulting region to the union of the old and new visible
;;; regions of the image-plane.

;;; The invalidation is done with deferred drawing to enable a sharper refresh.

;;; It maybe desirable to invoke this with a deferred drawing if you
;;; are going to add workspace blocks into the newly exposed area
;;; in the near future.

(defun reshape-image-plane-of-workspace (image-plane)
  (let ((gensym-window (gensym-window-for-image-plane image-plane))
	(old-shape (copy-region (visible-region-of-image-plane image-plane)))
	
	;; Outer edges.
	(old-left (left-edge-of-image-in-window image-plane))
	(old-top (top-edge-of-image-in-window image-plane))
	(old-right (right-edge-of-image-in-window image-plane))
	(old-bottom (bottom-edge-of-image-in-window image-plane))

	;; Inner edges
	(old-left-1 (left-edge-of-workspace-area-in-window image-plane))
	(old-top-1 (top-edge-of-workspace-area-in-window image-plane))
	(old-right-1 (right-edge-of-workspace-area-in-window image-plane))
	(old-bottom-1 (bottom-edge-of-workspace-area-in-window image-plane)))

    ;; Recompute all of the image-plane slots, as well as its visible region.
    (set-up-edges-for-image-plane image-plane)
    (recompute-visible-regions-for-pane (pane-for-image-plane image-plane))

    (let ((region (make-empty-region))
	  (new-shape (visible-region-of-image-plane image-plane))

	  (new-left (left-edge-of-image-in-window image-plane))
	  (new-top (top-edge-of-image-in-window image-plane))
	  (new-right (right-edge-of-image-in-window image-plane))
	  (new-bottom (bottom-edge-of-image-in-window image-plane))

	  (new-left-1 (left-edge-of-workspace-area-in-window image-plane))
	  (new-top-1 (top-edge-of-workspace-area-in-window image-plane))
	  (new-right-1 (right-edge-of-workspace-area-in-window image-plane))
	  (new-bottom-1 (bottom-edge-of-workspace-area-in-window image-plane)))

      (when (/=f new-left old-left)
	(setq region
	      (add-rectangle-to-region
		(minr old-left new-left) (minr old-top new-top)
		(maxr old-left-1 new-left-1)  (maxr old-bottom new-bottom)
		region)))

      (when (or (/=f new-top old-top)
		;; See note about the following. (MHD 9/23/99)
		(and (image-plane-has-new-g2-classic-title-bar-p image-plane)
		     (or (/=f new-left old-left)
			 (/=f new-right old-right))))
	(setq region
	      (add-rectangle-to-region
		(minr old-left new-left) (minr old-top new-top)
		(maxr old-right new-right)  (maxr old-top-1 new-top-1)
		region)))
      
      (when (/=f new-right old-right)
	(setq region
	      (add-rectangle-to-region
		(minr old-right-1 new-right-1) (minr old-top new-top)
		(maxr old-right new-right)  (maxr old-bottom new-bottom)
		region)))
      
      (when (/=f new-bottom old-bottom)
	(setq region
	      (add-rectangle-to-region
		(minr old-left new-left) (minr old-bottom-1 new-bottom-1)
		(maxr old-right new-right)  (maxr old-bottom new-bottom)
		region)))

      (let* ((union (union-region old-shape new-shape))
	     (visible (intersect-region region union)))

	;; Sync-up native-image-plane with new size by inflating.  This has to
	;; come before the inval else native image-planes will get turds.
	(when (image-plane-native-window? image-plane)
	  (unless (eq native-image-plane-updated-by-client image-plane)
	    (synchronize-shape-of-native-image-plane image-plane 'inflate)))

	(unless (shape-decoupled-image-plane-p image-plane)
	  (with-deferred-drawing-in-process ()		    ; Makes any difference?
	    (invalidate-region-of-window gensym-window visible)))

	(reclaim-region visible)
	(reclaim-region union)
	(reclaim-region region)
	(reclaim-region old-shape)))))

;; Note: we've added a little hand-hard-coded exception to handle title bar
;; refreshing, as a placeholder for a more sophisticated resizing protocol.  We
;; know if there's a title bar the title bar may need to be redrawn after a
;; change in the right or left border.  This just handled our current
;; ideosyncratic case.  We could fix this problem in general, but with flicker,
;; by always refreshing all framing regions whenever any edge changes.  But I'm
;; hesitant to introduce that much flicker now.  (MHD 9/23/99)



;;; `Require-that-image-plane-be-visible' ... leaves at least a minimal area
;;; visible in the pane image-plane is on.  If maximally? is true, the minimal
;;; area is the lesser of the width of the pane and the width image-plane by the
;;; lesser of the height of the pane and the height of image-plane.  Otherwise,
;;; the minimal area is `default-required-visible-area-size-for-image-planes'
;;; window units in width and height.

(defparameter default-required-visible-area-size-for-image-planes 11)

;; should be a system parameter!

(defun require-that-image-plane-be-visible (image-plane &optional maximally?)
  (let* ((width-of-minimum-area
	   (if maximally?
	       (minr (-r (right-edge-of-pane-in-window image-plane)
			 (left-edge-of-pane-in-window image-plane))
		     (-r (right-edge-of-image-in-window image-plane)
			 (left-edge-of-image-in-window image-plane)))
	       default-required-visible-area-size-for-image-planes))
	 (height-of-minimum-area
	   (if maximally?
	       (minr (-r (bottom-edge-of-pane-in-window image-plane)
			 (top-edge-of-pane-in-window image-plane))
		     (-r (bottom-edge-of-image-in-window image-plane)
			 (top-edge-of-image-in-window image-plane)))
	       default-required-visible-area-size-for-image-planes))
	 (delta-x-to-pull-far-enough-into-pane
	   (minr (-r (-r (right-edge-of-pane-in-window image-plane)
			 width-of-minimum-area)
		     (left-edge-of-view-in-window image-plane))
		 (maxr (-r (+r (left-edge-of-pane-in-window image-plane)
			       width-of-minimum-area)
			   (right-edge-of-view-in-window image-plane))
		       0)))
	 (delta-y-to-pull-far-enough-into-pane
	   (minr (-r (-r (bottom-edge-of-pane-in-window image-plane)
			 height-of-minimum-area)
		     (top-edge-of-view-in-window image-plane))
		 (maxr (-r (+r (top-edge-of-pane-in-window image-plane)
			       height-of-minimum-area)
			   (bottom-edge-of-view-in-window image-plane))
		       0))))
    (when (or (/=r delta-x-to-pull-far-enough-into-pane 0)
	      (/=r delta-y-to-pull-far-enough-into-pane 0))
      (move-image-plane
	image-plane
	delta-x-to-pull-far-enough-into-pane
	delta-y-to-pull-far-enough-into-pane))))

;; At most of the call sites this is called right after image-plane was moved
;; to any old place and the screen was updated accordingly.  Thus, if this has
;; to move image-plane, extra screen updating would have been done.  Figure out
;; a nice way to be able to avoid that!  This is especially apparent when a
;; workspace is "pinned" against the pane boundary while the user is moving the
;; workspace with arrow keys in certain modes.  (But note that the current way
;; the system behaves when a workspace is "pinned", by "moving it there" then
;; "bouncing it back", may actually be appealing to users, since it somewhat
;; animates the action taken by the system; alternatives, e.g.  to beep or to
;; just not respond by not doing anything, may not be as good.  (MHD 3/28/90)

;; I think that when drawing is scheduled, at least, we should try to avoid
;; the double update.  Immediate drawing can replicate 3.0 behavior for nostalgic
;; users. Besides, there's a bug in this vicinity: see `refresh-moved-image-plane'
;; -fmw, 7/26/94



;;;; Adding to a Workspace



;;; The function `add-to-workspace' adds the given block to the workspace.  and
;;; enlarges the workspace for block and its subblocks as necessary.  If
;;; confine-updating-to-block-rectangle? is true, then the drawing region is
;;; clipped to the only the local edges of the block, NOT including any
;;; subblocks.  If NIL, then the clipping rectangle is the entire workspace
;;; (see update-images).  The block becomes the new topmost block, and is
;;; assigned a position of (0,0).

(defun add-to-workspace
       (block workspace left-edge-for-block top-edge-for-block
	&optional update-images? confine-updating-to-block-rectangle?)
  (add-to-block
    block workspace left-edge-for-block top-edge-for-block
    update-images? confine-updating-to-block-rectangle?
    workspace))



;;; The function `add-to-block' adds block as a subblocks of superblock.  The
;;; superblock must be a block which either is or is on a workspace.
;;; Add-to-block enlarges the workspace superblock is on for block and its
;;; subblocks as necessary.

(defun add-to-block
    (block superblock left-edge-for-block top-edge-for-block
	   &optional
	   update-images? confine-updating-to-block-rectangle?
	   workspace-if-known?)

  (perform-any-deferred-icon-set-up superblock)
  (perform-any-deferred-icon-set-up block)
    
  (shift-block
    block
    (-w left-edge-for-block (left-edge-of-block block))	; new blocks usually at (0,0)
    (-w top-edge-for-block (top-edge-of-block block)))

  (enlarge-workspace-for-block-and-subblocks-as-necessary
    block (or workspace-if-known? (get-workspace-if-any superblock)))

  ;; If there is pending drawing on the workspace in XOR mode, we have to drain
  ;; it before updating the KB (with add-subblock).  Normally, no drawing is
  ;; deferred in XOR mode, so this is not a problem.  However, drawing which
  ;; creates new image-planes is deferred, even in XOR mode, to get a smoother
  ;; update.  If that happened, then we'd get a turd here in XOR mode.
  ;; -fmw, 1/10/95
  
  (when (and (xor-mode-p) (workspace-p superblock))
    (force-workspace-drawing superblock))
  
  (add-subblock block superblock)

  (when update-images?
    (update-images-of-block block nil confine-updating-to-block-rectangle?)))






;;;; Tracking Spots via Blocks


;;; When mouse tracking is computing mouse-pointers and it has resolved
;;; the mouse pointer down into a single image-plane we continue the
;;; process by calling the mouse-tracking-into-point method of the
;;; image-plane spot.  This in turn finds the object closes to the mouse,
;;; and requests that object to compute a spot approprate for the object.

;;; If you think of the draw method on a block as generating the view,
;;; the generate-spot method generates the controler for the block.



;;; `Uninteresting-block-spot' is the default spot generated for a block
;;; it may never actually be generated in practice.  But it is the
;;; default as implemented by the generate-spot method on blocks.

(def-structure (uninteresting-block-spot (:include spot)))



;;; `Generate-spot' is a class method on blocks.  In addition to a block it
;;; takes a mouse-pointer, and into this mouse-pointer it should place a spot
;;; that indicates how this block should respond to input.  If the block is
;;; invisible to input it may choose to add nothing to the spot.  It may insert
;;; multiple spots, and it may leave the top most spot requiring additional
;;; tracking or not.

;;; Refinements to this method may decline to call the superior, or use the
;;; superior method to push some spot(s) and then push additional ones to
;;; indicate additional behavors.

;;; For example menu-workspace it leaves a single spot that needs further
;;; tracking that indicating menu, and with the menu frame as it's frame
;;; represented.

;;; For example a KB-workspace it leaves a workspace schematic that needs
;;; further tracking, and the workspace is the frame represented.  Tracking that
;;; spot will then find the what portion of the schematic we are over and place
;;; a spots to indicate that.

;;; For example an attribute display leaves a stack of spots indicating the
;;; portion of the attribute display the mouse points at.

;;; Generate spot methods are called by track-mouse-into-spot methods and
;;; by each other.  The dynamic extent established for track-mouse-into-spot
;;; is available to these.

(def-generic-method generate-spot (block mouse-pointer))



;;; The `generate-spot' method on a block pushes a uninteresting-block-spot.
;;; This is must be overridden to give the block some behavior.

(def-class-method generate-spot (block mouse-pointer)
  (let ((spot (make-uninteresting-block-spot)))
    (setf (further-tracking-maybe-required? spot) nil)
    (push-more-detailed-spot mouse-pointer spot block)))







;;; `Simple-item-spot' are generated for many items in G2.  Many entities, and
;;; some text-boxes for example.

(def-spot simple-item-spot
    :slots nil
    :include spot
    :enclosing-spot-type image-plane-spot
    :innermost-spot-p t
    :abstract-type nil
    :type-of-frame-represented entity)


;;; `Generate-simple-item-spot' is a short hand that pushs a last spot
;;; of simple-item-spot representing the frame given on the mouse-pointer given.

(defun-void generate-simple-item-spot (frame-represented mouse-pointer)
  (push-last-spot mouse-pointer (make-simple-item-spot) frame-represented))



;;; `Aggregates' are sets of blocks that form a portion of the subblock tree, and
;;; the top most block in that tree can appear as a direct subblock of the workspace.
;;; Dials, for example, have a subblock tree hanging form them that looks like this:
;;;  > #<dial @1019>
;;;   > #<ruling-for-dial @1014>
;;;    > #<dial-marking-label marking-label-format @1017>
;;;    > #<dial-marking-label marking-label-format @1011>
;;;    > #<dial-marking-label marking-label-format @1010>
;;;    > #<dial-marking-label marking-label-format @1012>
;;;    > #<dial-marking-label marking-label-format @1018>


;;; `Generate-spot-for-parent-of-part-in-aggregate' is used to implement the
;;; generate-spot method of the inferior subblocks of an aggregate, when those
;;; subblocks haven't any unique input behavior compaired to the superior of the
;;; block.

(defun generate-spot-for-aggregate (aggregate-subblock mouse-pointer)
  (loop for superior-block = (superblock? aggregate-subblock)
			   then super-super-block?
	as super-super-block? = (superblock? superior-block)
	until (or (null super-super-block?)
		  (workspace-p super-super-block?))
	finally
	  (if (workspace-p superior-block)
	      ;; This really ought not happen, but it does for button labels.
	      ;; I ought to fix that, but then this helps avoid an explosive
	      ;; recursion in the case of some corruption.
              (push-last-spot mouse-pointer
                              (make-workspace-background-spot)
                              superior-block)
	      (funcall-method 'generate-spot superior-block mouse-pointer))))


  



;;; The function `invalidate-region-of-workspace-for-block' invalidates the
;;; region of the workspace touched the given block or any of its subblocks or
;;; connections.

(defun invalidate-region-of-workspace-for-block (workspace block)
  (multiple-value-bind (left top right bottom)
      (extreme-edges-of-block block)
    (invalidate-rectangle-of-workspace workspace workspace left top right bottom
				       nil)))

;; Use regions here?  Should this go thru update-images?





;;;; Adjust layer position of workspace subblocks



;;; The `layer-position' of a block or connection is a fixnum indicating its
;;; position in the "Z axis" of drawing.  Internally, layer positions increase
;;; from bottom to top: the thing on the bottom most layer of a workspace has
;;; layer position 0.  The operation to use to get a block's internal layer
;;; position is `get-block-layer-position'.  For a connection, use
;;; `get-connection-layer-position'.  Given a block or connection not on a
;;; workspace, these simply return nil.
;;;
;;; Externally, the topmost thing is given layer position 0, as computed by
;;; g2-get-layer-position.  It's done this way internally so that adding a new
;;; block to the top layer of a workspace does not have to renumber all the
;;; blocks.  The external choice was arbitrary, but cannot be changed now.

(def-concept layer-position)


(defun get-block-layer-position (block)
  (let ((workspace? (get-workspace-if-any block)))
    (when workspace?
      (ensure-layer-positions workspace?)
      (layer-position-of-block block))))

;; Get-connection-layer-position is defined in a CONNECT2 to overcome
;; macro forward reference problems. (MHD 3/5/97)
  


;;; Changing these to NOT remove and insert, but to instead
;;; simply change layer position 

;; This will rearrange subblocks of anything, not just a workspace.
;; Do we want that?

(defun raise-block-to-top (block)
  (let ((superblock? (superblock? block))
	(workspace? (get-workspace-if-any block)))
    (when superblock?
      (cond ((eq block (first-subblock superblock?))
	     nil)
	    (t
	     (primitive-remove-as-subblock block superblock?)  ; pbk 10/25/95
	     (primitive-insert-as-subblock block superblock? 'top)
	     (send-ws-representations-item-layer-change
	       block superblock?
	       #-subblocks-v2
	       (find-next-non-loose-end (cdr (memq block (subblocks superblock?))))
	       #+subblocks-v2
	       (let ((cursor
		      (loop with constant-queue = (subblocks superblock?)
			    with head = (constant-queue-head constant-queue)
			    for queue-element = #-Lockfree-Deque head
						#+Lockfree-Deque
						(constant-queue-next head constant-queue)
					   then (constant-queue-next queue-element constant-queue)
			    until #-Lockfree-Deque (eq queue-element constant-queue)
				  #+Lockfree-Deque (null queue-element)
			    when (eq block (queue-datum queue-element))
			      do (return queue-element))))
		 (find-next-non-loose-end-in-queue (subblocks superblock?) cursor)))
	   ; (setf (subblocks superblock?)
	   ;     (slot-value-cons
           ;		     block
	   ;	     (delete-slot-value-element block (subblocks superblock?))))
	     (when workspace?
	       (note-change-to-workspace-geometry workspace?)
	       (invalidate-layer-positions workspace?)
	       (invalidate-region-of-workspace-for-block workspace? block)))))))

;; The subblock list is in order from topmost to bottommost.

;; changed the setting of the positions to calls to primitive remove and insert functions
;; pbk 11/6/95

(defun lower-block-to-bottom (block)
  (if (frame-of-class-p block 'connection)
      (lower-connection-frame-to-bottom block)
      (let ((superblock? (superblock? block))
	    (workspace? (get-workspace-if-any block)))
	(when superblock?
	  (cond ((eq block (last-subblock superblock?))
		 nil)
		(t
		 (primitive-remove-as-subblock block superblock?)   ; pbk 10/25/95
		 (primitive-insert-as-subblock block superblock? 'bottom)
		 (send-ws-representations-item-layer-change
		   block superblock? 'bottom)
		 (when (workspace-p superblock?)
		   (note-change-to-workspace-geometry workspace?)
		   (invalidate-layer-positions workspace?)
		   (invalidate-region-of-workspace-for-block superblock? block))))))))

;; changed the setting of the positions to calls to primitive remove and insert functions
;; pbk 11/6/95




;;; The function `order-blocks' forces block-1 to be in front or in back of
;;; block-2 in their common superblock's list of subblocks.  It returns T iff
;;; anything actually changed.

(defun order-blocks (block-1 block-2 in-back-p)
  (let ((superblock-1 (superblock? block-1))
	(superblock-2 (superblock? block-2)))
    (when (and superblock-1 superblock-2 (eq superblock-1 superblock-2))
      #-subblocks-v2
      (multiple-value-bind (new-list changed-something?)
	  (if in-back-p
	      (order-in-back block-1 block-2 (subblocks superblock-1))
	      (order-in-front block-1 block-2 (subblocks superblock-1)))

	(setf (subblocks superblock-1) new-list)
	(when (and changed-something?
		   (workspace-p superblock-1))
	  (when (ws-has-ws-representation-p superblock-1)
	    (if in-back-p
		(let* ((remaining-blocks (cdr (memq block-1 new-list)))
		       (item-below (find-next-non-loose-end
				      remaining-blocks))
		       (position-or-next-lower-item (or item-below
							'bottom)))
		  (send-ws-representations-item-layer-change
		    block-1 superblock-1 position-or-next-lower-item))
		(send-ws-representations-item-layer-change
		  block-1 superblock-1 (get-topmost-child-of-block block-2))))
	  (note-change-to-workspace-geometry superblock-1)
	  (invalidate-layer-positions superblock-1)
	  (invalidate-region-of-workspace-for-block superblock-1 block-1))
	changed-something?)
      #+subblocks-v2
      (let ((constant-queue (subblocks superblock-1))
	    (queue-element-1 nil)
	    (queue-element-2 nil)
	    (changed-something? nil))
	(loop with head = (constant-queue-head constant-queue)
	      for element = #-Lockfree-Deque head
			    #+Lockfree-Deque (constant-queue-next head constant-queue)
		       then (constant-queue-next element constant-queue)
	      until #-Lockfree-Deque (eq element constant-queue)
		    #+Lockfree-Deque (null element)
	      for block = (queue-datum element)
	      do
	  (cond ((eq block block-1)
		 (setq queue-element-1 element)
		 (when (and (null queue-element-2) in-back-p)
		   (setq changed-something? t)))
		((eq block block-2)
		 (setq queue-element-2 element)
		 (when (and (null queue-element-1) (not in-back-p))
		   (setq changed-something? t))))
	  ;; terminate the loop early if both blocks are found.
	  (when (and queue-element-1 queue-element-2)
	    (loop-finish)))
	(when changed-something?
	  (cond (in-back-p
		 (constant-queue-delete queue-element-2 constant-queue)
		 (constant-queue-insert-before constant-queue queue-element-1 block-2))
		(t ; in-front-p
		 (constant-queue-delete queue-element-1 constant-queue)
		 (constant-queue-insert-before constant-queue queue-element-2 block-1))))
	(when (and changed-something?
		   (workspace-p superblock-1))
	  (when (ws-has-ws-representation-p superblock-1)
	    (if in-back-p
		(let* ((item-below (find-next-non-loose-end-in-queue
				     constant-queue queue-element-1))
		       (position-or-next-lower-item (or item-below
							'bottom)))
		  (send-ws-representations-item-layer-change
		    block-1 superblock-1 position-or-next-lower-item))
		(send-ws-representations-item-layer-change
		  block-1 superblock-1 (get-topmost-child-of-block block-2))))
	  (note-change-to-workspace-geometry superblock-1)
	  (invalidate-layer-positions superblock-1)
	  (invalidate-region-of-workspace-for-block superblock-1 block-1))
	changed-something?))))

; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module MOVES

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.  

;;; Mark H. David and Lowell B. Hawkinson







;;;; Forward References




;; To RUN
(declare-forward-reference find-object-near-mouse function)
(declare-forward-reference constant-mouse-leeway variable)
(declare-forward-reference scalable-mouse-leeway variable)
(declare-forward-reference break-out-of-debug-messages function)


;; To EDIT
(declare-forward-reference launch-compile-to-bring-kb-up-to-date function)

;; To CHAINING
(declare-forward-reference invoke-rules-for-user-icon-movement-if-necessary function)
(declare-forward-reference invoke-rules-for-direct-connection-chaining function)
(declare-forward-reference invoke-rules-for-indirect-connection-chaining function)
(declare-forward-reference invoke-rules-for-resizement-chaining function)
(declare-forward-reference recursive-schedule-task-to-invoke-creation-rules
			   function)



;; To ACTIVATE
(declare-forward-reference ancestor-p function)

;; To FILTERS
(declare-forward-reference non-menu-choice-permitted-p function)
(declare-forward-reference note-dependent-or-stable-status-change function)
(declare-forward-reference no-manual-connections-p function)
(declare-forward-reference compute-snap-grid-for-block function)
(declare-forward-reference movement-limits-for-block function)

(declare-forward-reference ignore-snap-grid-in-transfer-operations-p function) ; GRAMMAR7

(declare-forward-reference note-kb-state-change function)	; KB-SAVE2
(declare-forward-reference enter-dialog function)       	; CONTROLS
(declare-forward-reference item-to-transfer-connected-stack-error function) ; STACK-ACTS
(declare-forward-reference install-item-in-model-if-models-used function)   ; SIMULATE5
(declare-forward-reference write-list-in-chicago-style function)   ; GRAMMAR6

(declare-forward-reference get-module-block-is-in function) ; MOVES
(declare-forward-reference remove-as-inferior-block function) ; MOVES
(declare-forward-reference block-of-edit-workspace-p function)

;; To EVENTS-G2
(declare-forward-reference send-ws-representations-connection-moved function)
(declare-forward-reference send-ws-representations-remove-connections-of-block function)
(declare-forward-reference send-ws-representations-item-insert-as-subblock function)

;; To VIEW-G2

(declare-forward-reference workspace-showing-on-ui-client-p function)

;; To COMMANDS0

(declare-forward-reference recompute-selection-highlights function)
(declare-forward-reference get-table-for-cell function)
(declare-forward-reference select-objects-after-transfer function)
(declare-forward-reference selection-enabled-p function)

;; To COMMANDS1
(declare-forward-reference update-table-of-attributes-pane function)

;;;; Dragging Globals

;;; `Current-dragging-states' is a KB specific variable used to manage
;;; the scenario which arises when multiple users are dragging the same
;;; object, in this situation the bits indicating that the object is
;;; being dragged must not be cleared until the last user finishs
;;; dragging.

;;; This list is also used when a block is deleted, in that situation
;;; it is popped out of the dragging states it is found in.

(def-kb-specific-variable current-dragging-states moves nil nil
			  reclaim-dragging-list-function)



;;;; Dragging Conses




;;; `Dragging conses' are used to make up all of the list structure present
;;; internal to dragging states.

(defconser dragging run)

;;; The functions reclaim-dragging-list-function, dragging-cons-function are
;;; needed in menus.

(defun reclaim-dragging-list-function (list)
  (reclaim-dragging-list-macro list))

(defun dragging-cons-function (car cdr)
  (dragging-cons-macro car cdr))

(defun reclaim-dragging-cons-function (a-cons)
  (reclaim-dragging-cons a-cons))

;;;; Dragging States




;;; A `dragging-state' implements the frame in the workstation context stack
;;; when ever the user is dragging.  There are three styles of dragging,
;;; move, transfer, and image-plane.  In all three cases a "outline" of the
;;; objects being dragged is recorded in the dragging-state, this outline
;;; is recorded in `objects-being-dragged' and `external-connections-to-drag'.

;;; In image-plane dragging the outline consists a set of rectangles for
;;; prefaced by the symbol IMAGE-PLANE.  This "display list" is then
;;; updated on the fly to record the position the user is currently
;;; dragging over.  The original image-plane is not moved until the user
;;; comits the drag.

;;; In move and transfer style dragging a list of objects being dragged is
;;; maintained in objects-being-dragged.  In move style dragging connections
;;; running from this set to other objects are enumerated in
;;; `external-connections-to-drag'.  Objects being dragged are marked with
;;; a bit and drawing of these objects is then done at a "lower" resolution.
;;; All windows reflect this `dragging style rendering'.

;;; Move style dragging has some unique behaviors.  The objects can not leave
;;; the workspace they originally started upon.  The bounds of the workspace may
;;; change if user restrictions allow it.  The objects are moved live, a primary
;;; application of this is that object nearest queries change as the object is
;;; moved the KB author may use this to do various forms of highlighting.  The
;;; position of the objects is not changed in the workspace subblocks list.  If
;;; the user aborts a move the objects are left where he last moved them too.

;;; In transfer style objects may move from one workspace to another.  The
;;; objects do not have `live updating during the dragging'.  Instead the
;;; objects remain on their original workspace and a `ghost' of them is dragged
;;; from image-plane to image-plane.  This ghost is represented internally by
;;; placing the dragging state into the `image-plane-cursors' of the image-plane
;;; in question, and it is rendered by creating a dynamic extent where in that
;;; image-plane's origin is shifted.  If a transfer is aborted the objects are
;;; left where they originally sat.

;; - ben 6/18/93

(define-workstation-context dragging ()
  :selection-style top-level-with-mouse-tracking-is-selection-style
  :keymaps (dragging screen-layout)
  :constructor
  (make-dragging-state
    (dragging-style
      objects-being-dragged
      window-for-objects-being-dragged
      image-plane-showing-objects-being-dragged?
      x-offset-of-objects-being-dragged
      y-offset-of-objects-being-dragged
      external-connections-to-drag
      workspace-for-objects-being-dragged?
      mouse-up-exits-this-context?
      original-workspace-of-objects-being-dragged?))
  :state-variables
  (
   (objects-being-dragged          ; a list of blocks or (rubber-band ...)
     nil :reclaimer reclaim-dragging-list)   ; or (IMAGE-PLANE
					;     image-plane-to-drag
					;   workspace-on-image-plane-to-drag
					; . image-planes-representing-sides)
					; can also be nil, transiently, usually
					; when a connection or loose end is
					; deleted
   
   window-for-objects-being-dragged

   ;; image-plane-showing-objects-being-dragged? is nil if not currently drawn
   ;; (never nil if external-connections-to-stretch)
   image-plane-showing-objects-being-dragged?

   external-connections-to-drag		; Only used in the move case.  These are
					; those connections that extend between
                                        ; blocks in the objects-being-dragged
                                        ; to blocks not being dragged.

   workspace-for-objects-being-dragged? ; nil or a workspace for blocks being
					; dragged to belong to when dragging ends

   x-offset-of-objects-being-dragged    ; offset of first block or image plane 
   y-offset-of-objects-being-dragged    ;   from mouse; in workspace units for
					;   block case; in window units for
					;   image-plane case.
   
   (previous-x-in-window-of-mouse? nil)
   (previous-y-in-window-of-mouse? nil)

   mouse-up-exits-this-context?

   ;; Constrain the objects being dragged to be inside this rectangle.
   (minimum-left-edge-for-dragging? nil)
   (minimum-top-edge-for-dragging? nil)
   (maximum-right-edge-for-dragging? nil)
   (maximum-bottom-edge-for-dragging? nil)
   
   (x-in-workspace-for-blocks-being-transferred nil); Only in transfer style.
   (y-in-workspace-for-blocks-being-transferred nil);
   ;; This second pair is redundant with  previous-x/y-in-window-of-mouse??!
   (x-in-window-for-blocks-being-transferred nil)
   (y-in-window-for-blocks-being-transferred nil)

   dragging-style                 ; {image-plane,move,transfer}-dragging-style
   (alignment-grid-x-step 1)
   (alignment-grid-y-step 1)


   (items-made-incomplete-were-recorded-during-transfer? nil)

   ;; Determines where the "hole" in transfer drawing is -- the position on
   ;; the screen where we don't draw, in order to not erase the originals.
   (original-workspace-of-objects-being-dragged? nil)

   (saved-copy-of-pane-cursors-for-image-plane-dragging?
     nil				; saved dragging list of pane cursors while suspended
     :reclaimer				;   if dragging an image plane; reclaimed only
     reclaim-dragging-list-of-pane-cursors))) ;  if aborted; set nil if put back into use


(defun reclaim-dragging-list-of-pane-cursors (l)
  (loop for x in l
	do (reclaim-graphics-tree x))
  (reclaim-dragging-list l))


;;; The keymap `dragging' particularly needs to handle ANY mouse-up in this
;;; context, else the user can depress the shift key, say, release the mouse,
;;; and remain in dragging context.

(define-keymap dragging (:private t)
  (<mouse-up> mouse-up-in-dragging-state)
  (<mouse-down> mouse-down-in-dragging-state)
  (<mouse-motion> mouse-motion-in-dragging-state)
  (<standard-abort-keys> abort-workstation-context))




(def-substitution-macro dragging-state-contains-block-p (dragging-state block)
  (memq block (objects-being-dragged dragging-state)))

(def-substitution-macro transfer-dragging-style-p (dragging-state)
  (eq (dragging-style dragging-state) 'transfer-dragging-style))

(def-substitution-macro move-dragging-style-p (dragging-state)
  (eq (dragging-style dragging-state) 'move-dragging-style))

(def-substitution-macro image-plane-dragging-style-p (dragging-state)
  (eq (dragging-style dragging-state) 'image-plane-dragging-style))



;;;; Draggers



;;; A `dragger' is a pair of G2 variables that provide the x and y window
;;; positions for dragging objects being dragged.  Typically a dragger reflects
;;; the current mouse cursor position....

;;; The macros dragger-x-in-window and dragger-y-in-window give the current
;;; dragger location in current-workstation.  These should only be used in a
;;; for-workstation context whose current workstation context is of type
;;; DRAGGING.

;;; The special variables explicit-dragger-x-in-window? and
;;; explicit-dragger-y-in- window? may be used to explicitly bind the dragger
;;; location, overriding the location looked up in the current workstation by
;;; macros dragger-x-in-window and dragger-y-in-window.  At top-level, these are
;;; bound to nil.  (The primary purpose for having these is be able to simulate
;;; the user's dragging objects without having the user there to move the
;;; mouse.)

(defvar explicit-dragger-x-in-window? nil)
(defvar explicit-dragger-y-in-window? nil)

(defmacro dragger-x-in-window ()
  '(or explicit-dragger-x-in-window?
      (x-in-window-of-mouse? current-workstation)))

(defmacro dragger-y-in-window ()
  '(or explicit-dragger-y-in-window?
      (y-in-window-of-mouse? current-workstation)))




;;;; Dragging restrictions



(def-substitution-macro restrict-movement-of-block-to-workspace-interior?
    (block)
  (null (non-menu-choice-permitted-p
	  'move-objects-beyond-workspace-margin block)))

(defun compute-movement-contraints (workspace blocks outline external-connections?)
  (let ((first-block (first blocks))
	x-step? y-step? left? top? right? bottom?)

    (multiple-value-setq (x-step? y-step?)
      (compute-snap-grid-for-block first-block))

    (multiple-value-bind (left-limit? top-limit? right-limit? bottom-limit?)
	(movement-limits-for-block first-block)
      ;; If first block has movement contraints, or if any block is
      ;; restricted to the workspace interior, then restrict them all.
      (when (or left-limit?
		(loop for block in outline
		      thereis (restrict-movement-of-block-to-workspace-interior?
				block)))
	(multiple-value-setq (left? top? right? bottom?)
	  (compute-movement-limits-for-blocks
	    workspace
	    blocks
	    external-connections?
	    left-limit? top-limit? right-limit? bottom-limit?))))

    (values x-step? y-step? left? top? right? bottom?)))


;;;; Dragging Contexts


;; Document numerous implicit cross-dependencies among the arguments!!!!!!!

;;; `Enter-dragging-context-1' is internal to this module, it establishes a
;;; workstation context stack entry capable of dragging something.

;;; Objects-to-drag should be either an image plane, a single block, or a
;;; dragging-list of blocks.  Passing a single block is equivalent to passing a
;;; list of consisting of a single block.

;;; The initial offset to start dragging are passed via
;;; {x,y}-offset-from-dragger.  These default to zero.  They are in workspace
;;; units, except when dragging an image plane when they are in window units.
;;; They are relative to the origin of the image-plane or the first block in the
;;; list of blocks being dragged.

;;; Specific-image-plane? should be provide when dragging blocks.  It should an
;;; image-plane currently showing the blocks.

;;; Mouse-up-exits-this-context?, which defaults to nil, does just as it says.

;;; Dragging can be done in one of three styles: image-plane dragging, transfer
;;; dragging, and move dragging.  For historical reasons this code defaults to
;;; the transfer case and then degenerates into the other two cases.  The
;;; optional argument assume-transfer-case? defaults to T, but can be used to
;;; immediately degenerate into the move case.  Of course, if objects-to-drag,
;;; is an image-plane then we immediately fall into the image-plane dragging
;;; case.

;;; Restrictions can affect where the blocks or image-plane maybe dragged.  For
;;; example move-workspaces-beyond-window-margin and
;;; move-objects-beyond-workspace-margin.

;;; The user may abort the dragging context.  The stuff being dragged maybe
;;; deleted, and then dragging context will be aborted.  A transfer by some
;;; other agent, of some of the stuff involed may abort the context.

;;; If the context returns normally one of five return values patterns
;;; will occur.
;;;   a. Image-plane Resizing: (values image-plane <resize-values>)
;;;      where <resize-values> is ({x,y}-center {x,y}-border-offset)
;;;   b. Image-plane Dragging: (values image-plane delta-x delta-y)
;;;   c. Connection (aka loose-end) dragging: (values)
;;;   d. Moving block(s): (values <list-of-objects-being-dragged>)
;;;   e. Transfering Block(s): (values <transfer-values>)
;;;      where <transfer-values> is a list of objects-being-dragged,
;;;       external-connections-to-drag, the original workspace, and
;;;       delta x and y.

;;; In case a, d, and e the tree is freshly consed and the continuation
;;; function must reclaim it back into the gensym cons pool.

;;; In case d and e, the blocks involved will be currently drawn using their
;;; dragging rendering.

;;; Case a. currently does not arise in the field.

;;; Enter-dragging-context-1 is called by various routines for each
;;; of the five cases above:
;;;   a. Image-plane Resizing: enter-image-plane-dragging-context
;;;   b. Image-plane Dragging: enter-image-plane-dragging-context
;;;   c. Connection Dragging:  enter-connection-dragging-context
;;;   d. Moving block(s):      enter-move-dragging-context
;;;   e. Transfering Block(s): enter-transfer-dragging-context
;;; Most of these establish a continuation to swallow the return values,
;;; and some of these create an additional workstation context.

;;; When the style is moving or transfering (c,d,e) the the blocks are
;;; marked as being in the XOR layer, and as block-is-currently-being-dragged
;;; changes how they are rendered and is unwound by the clean up method.

(defun enter-dragging-context-1
    (image-plane-block-or-blocks-to-drag
      x-offset-from-dragger
      y-offset-from-dragger
      specific-image-plane?
      &optional
      (mouse-up-exits-this-context? (mouse-down-p))
      (assume-transfer-case? t))
  (let* ((image-plane-case? (image-plane-p image-plane-block-or-blocks-to-drag))
	 (image-plane-to-drag?
	   (if image-plane-case? image-plane-block-or-blocks-to-drag))
	 (blocks-to-drag? (cond
			    (image-plane-case? 
			     nil)
			    ((consp image-plane-block-or-blocks-to-drag)
			     image-plane-block-or-blocks-to-drag)
			    (t
			     (dragging-list
			       image-plane-block-or-blocks-to-drag))))
	 (first-block? (first blocks-to-drag?)))

    (multiple-value-bind 
	(outline external-connections-to-drag? dragging-confined-p)
	(if image-plane-case?
	    (make-outline-for-image-plane-to-drag
	      image-plane-to-drag? 
	      x-offset-from-dragger y-offset-from-dragger)
	    (make-outline-for-blocks-to-drag
	      blocks-to-drag? assume-transfer-case?))

      (let* ((dragging-style
	       (cond
		 (image-plane-case?                'image-plane-dragging-style)
		 ((or dragging-confined-p
		      (not assume-transfer-case?)) 'move-dragging-style)
		 (t                                'transfer-dragging-style)))
	     (move-case-p (eq dragging-style 'move-dragging-style))
	     (window-for-objects-being-dragged
	       (window-for-workstation current-workstation))
	     (image-plane-showing-objects-being-dragged?
	       (and move-case-p specific-image-plane?))
	     (workspace-for-objects-being-dragged?
	       (and move-case-p
		    (workspace-on-image-plane? specific-image-plane?)))
	     (mouse-up-exits-this-context?
	       (and mouse-up-exits-this-context?
		    ;; override this request if illegal:
		    (not (loose-end-dragging-outline-p outline))))
	     (original-workspace-of-objects-being-dragged?
	       (and blocks-to-drag?
		    (get-workspace-if-any first-block?)))
	     (dragging-state
	       (make-dragging-state
		 dragging-style
		 outline
		 window-for-objects-being-dragged
		 image-plane-showing-objects-being-dragged?
		 x-offset-from-dragger
		 y-offset-from-dragger
		 external-connections-to-drag?
		 workspace-for-objects-being-dragged?
		 mouse-up-exits-this-context?
		 original-workspace-of-objects-being-dragged?)))

	(dragging-push dragging-state current-dragging-states)
	(enter-context-in-current-workstation 'dragging dragging-state)

	;; Redraw the blocks in the dragging style.
	(when blocks-to-drag?
	  (start-rendering-dragging-state-for-move-or-transfer dragging-state))
	
	;; Take note of restrictions.
	(cond
	  (image-plane-case?
	   (unless (non-menu-choice-permitted-p
		     'move-workspaces-beyond-window-margin
		     (workspace-on-image-plane? image-plane-to-drag?))
	     (let* ((image-plane image-plane-to-drag?)
		    (x-offset-of-image-plane-from-dragger x-offset-from-dragger)
		    (y-offset-of-image-plane-from-dragger y-offset-from-dragger)
		    (minimum-left-edge
		      (+r (minr (left-edge-of-pane-in-window image-plane)
				(-r (right-edge-of-pane-in-window image-plane)
				    (-r (right-edge-of-image-in-window
					  image-plane)
					(left-edge-of-image-in-window
					  image-plane))))
			  x-offset-of-image-plane-from-dragger))
		    (minimum-top-edge
		      (+r (minr (top-edge-of-pane-in-window image-plane)
				(-r (bottom-edge-of-pane-in-window image-plane)
				    (-r (bottom-edge-of-image-in-window image-plane)
					(top-edge-of-image-in-window image-plane))))
			  y-offset-of-image-plane-from-dragger))
		    (maximum-right-edge
		      (+r (maxr (-r (right-edge-of-pane-in-window image-plane)
				    (-r (right-edge-of-image-in-window image-plane)
					(left-edge-of-image-in-window image-plane)))
				(left-edge-of-pane-in-window image-plane))			     
			  x-offset-of-image-plane-from-dragger))
		    (maximum-bottom-edge
		      (+r (maxr (-r (bottom-edge-of-pane-in-window image-plane)
				    (-r (bottom-edge-of-image-in-window image-plane)
					(top-edge-of-image-in-window image-plane)))
				(top-edge-of-pane-in-window image-plane))
			  y-offset-of-image-plane-from-dragger)))
	       (setf (minimum-left-edge-for-dragging? dragging-state)
		     minimum-left-edge)
	       (setf (minimum-top-edge-for-dragging? dragging-state)
		     minimum-top-edge)
	       (setf (maximum-right-edge-for-dragging? dragging-state)
		     maximum-right-edge)
	       (setf (maximum-bottom-edge-for-dragging? dragging-state)
		     maximum-bottom-edge))))
	  
	  (move-case-p
	   (multiple-value-bind (x-step? y-step? left? top? right? bottom?)
	       (compute-movement-contraints
		 (workspace-on-image-plane? specific-image-plane?)
		 blocks-to-drag? outline external-connections-to-drag?)
	     (when (and x-step? y-step?)
	       (setf (alignment-grid-x-step dragging-state) x-step?)
	       (setf (alignment-grid-y-step dragging-state) y-step?))
	     (when left?
	       (setf (minimum-left-edge-for-dragging? dragging-state) left?
		     (minimum-top-edge-for-dragging? dragging-state) top?
		     (maximum-right-edge-for-dragging? dragging-state) right?
		     (maximum-bottom-edge-for-dragging? dragging-state) bottom?))))
	  
	  ;; transfer case
	  (t       
	   (compute-snap-grid-for-transfer dragging-state)

	   (setf (x-in-workspace-for-blocks-being-transferred dragging-state)
		 (+w (left-edge-of-block first-block?) x-offset-from-dragger))
	   (setf (y-in-workspace-for-blocks-being-transferred dragging-state)
		 (+w (top-edge-of-block first-block?) y-offset-from-dragger))
	   (when specific-image-plane?
	     (with-image-plane-transform (specific-image-plane?)
	       (setf (x-in-window-for-blocks-being-transferred dragging-state)
		     (x-in-window (left-edge-of-block first-block?)))
	       (setf (y-in-window-for-blocks-being-transferred dragging-state)
		     (y-in-window (top-edge-of-block first-block?)))))))))))


(defun compute-snap-grid-for-transfer (dragging-state &optional workspace?)
  (multiple-value-bind (x-step? y-step?)
      (unless (ignore-snap-grid-in-transfer-operations-p)
	(compute-snap-grid-for-block (first (objects-being-dragged dragging-state))
				     (or workspace?
					 (original-workspace-of-objects-being-dragged? dragging-state))))
    (setf (alignment-grid-x-step dragging-state) (or x-step? 1)
	  (alignment-grid-y-step dragging-state) (or y-step? 1))))



;;; The function `compute-movement-limits-for-blocks' returns four values, the
;;; left,top,right,bottom edges in which the movement of the given blocks and
;;; connections should be constrained, to keep them from moving beyond the
;;; interior of the workspace and with the optional user-specified limits given
;;; by left?, top?, right?, and bottom?.

;;; If the user-specified limits are too small to even contain the first block,
;;; much less move it about, we enlarge the region symmetrically just enough to
;;; contain the first block.  This is a convenience, so that users can specify
;;; left=right, and the constraint will be that the center of the first-block
;;; is aligned at x=left=right, rather than one side of the block.

(defun compute-movement-limits-for-blocks
    (workspace blocks connections left? top? right? bottom?)
  (let* ((first-block
	   (first blocks))
	 (block-width
	   (width-of-block first-block))
	 (block-height
	   (height-of-block first-block))
	 (workspace-margin
	   (workspace-margin workspace))
	 (left
	   (+w (left-edge-of-block workspace) workspace-margin))
	 (top
	   (+w (top-edge-of-block workspace) workspace-margin))
	 (right
	   (-w (right-edge-of-block workspace) workspace-margin))
	 (bottom
	   (-w (bottom-edge-of-block workspace) workspace-margin)))

    ;; Combine with the limits on first-block, if any.
    (when left?
      (setq left (maxf left left?)
	    top (maxf top top?)
	    right (minf right right?)
	    bottom (minf bottom bottom?))

      ;; If too small to even contain first-block, enlarge.
      (when (<f (-f right left) block-width)
	(let* ((left-width (halff block-width))
	       (right-width (-f block-width left-width))
	       (center (halff (+f left right))))
	  (setq left (-f center left-width)
		right (+f center right-width))))

      (when (<f (-f bottom top) block-height)
	(let* ((top-height (halff block-height))
	       (bottom-height (-f block-height top-height))
	       (center (halff (+f top bottom))))
	  (setq top (-f center top-height)
		bottom (+f center bottom-height)))))

    ;; Adjust to keep the entire collection with the limits.
    
    (multiple-value-bind (extreme-left-edge extreme-top-edge extreme-right-edge
					    extreme-bottom-edge)
	(determine-extreme-edges-of-blocks-and-connections
	  blocks connections t)
      
      (let ((minimum-left-edge
	      (+w left
		  (-w (left-edge-of-block first-block)
		      extreme-left-edge)))
	    (minimum-top-edge
	      (+w top
		  (-w (top-edge-of-block first-block)
		      extreme-top-edge)))
	    (maximum-right-edge
	      (-w right
		  (-w extreme-right-edge
		      (left-edge-of-block first-block))))
	    (maximum-bottom-edge
	      (-w bottom
		  (-w extreme-bottom-edge
		      (top-edge-of-block first-block)))))

	(values minimum-left-edge minimum-top-edge maximum-right-edge maximum-bottom-edge)))))



;;; `Frames-currently-being-dragged-have-been-deleted-p' returns non-nil if any of
;;; the frames in the current selection have been deleted.  When this is the case,
;;; the selection context should be aborted.

(defun frames-currently-being-dragged-have-been-deleted-p (dragging-state)
  (let ((objects-being-dragged (objects-being-dragged dragging-state)))
    (cond
      ;; All the blocks have been deleted and removed by delete frame.
      ((null objects-being-dragged)
       t)
      ;; We are in the image-plane case.
      ((eq (car objects-being-dragged) 'image-plane)
       (let ((workspace? (third objects-being-dragged)))
	 (or (null workspace?)
	     (or (not (valid-block-in-workstation-context-p workspace? dragging-state))
		 (not (eq workspace?
			  (workspace-on-image-plane?
			    (second objects-being-dragged))))))))
      ;; Check out da blocks.
      (t
       (loop for block in objects-being-dragged
	     thereis (not (valid-block-in-workstation-context-p
			    block dragging-state)))))))

;; Is the third clause necessary?
       
       
       

;;; The substitution-macro `restrict-coordinate-value' applies movement
;;; restrictions to a coordinate value.

(def-substitution-macro restrict-coordinate-value (u step? min? max?)
  (let ((ur u))
    (when step?
      (setq ur (*f step? (roundf u step?))))
    (when min?
      (setq ur (maxf ur min?)))
    (when max?
      (setq ur (minf ur max?)))
    ur))

;;; The substitution-macro `restrict-dragger-x-as-appropriate' contrains the
;;; given x to be within the bounds set by the dragging state, and to be
;;; on an even multiple of the grid size.

(def-substitution-macro restrict-dragger-x-as-appropriate (x dragging-state)
  (restrict-coordinate-value x
			     (alignment-grid-x-step dragging-state)
			     (minimum-left-edge-for-dragging? dragging-state)
			     (maximum-right-edge-for-dragging? dragging-state)))

(def-substitution-macro restrict-dragger-y-as-appropriate (y dragging-state)
  (restrict-coordinate-value y
			     (alignment-grid-y-step dragging-state)
			     (minimum-top-edge-for-dragging? dragging-state)
			     (maximum-bottom-edge-for-dragging? dragging-state)))



;;; `Do-not-invoke-rules-for-user-icon-movement?' is bound to nil a top-level.
;;; This should be bound non-nil to keep the dragging context from calling
;;; invoke-rules-for-user-icon-movement-if-necessary after moving objects.
;;; This is done, e.g., when the objects are being moved via dragging contexts
;;; by program rather than by user interaction.

(defvar do-not-invoke-rules-for-user-icon-movement? nil)


;;; `Trigger-user-icon-movement-rules-for-blocks' ...

(defun trigger-user-icon-movement-rules-for-blocks (block-or-blocks)
  ;; Trigger forward chaining
  (unless do-not-invoke-rules-for-user-icon-movement?
    (cond ((consp block-or-blocks)
	   (loop for block in block-or-blocks
		 do
	     (invoke-rules-for-user-icon-movement-if-necessary block)))
	  (block-or-blocks
	   (invoke-rules-for-user-icon-movement-if-necessary block-or-blocks)))))

(defun-simple gather-connections-for-block (block connection-list)
  #-connections-v2
  (loop for connection in (connections block)
	when (and (connection-p connection)
		  (not (memq connection connection-list)))
	  do
	    (gensym-push connection connection-list))
  #+connections-v2
  (loop for connection being each connection of block
	when (not (memq connection connection-list))
	do (gensym-push connection connection-list))
  connection-list)

;;; `connections-moved-for-blocks-moved' gathers a freshly gensym-consed
;;; list of connection (structures) for block or list of blocks that
;;; has been altered by a dragging state or by an inference engine
;;; action.

(defun-simple connections-moved-for-blocks-moved (block-or-blocks)
  (cond ((listp block-or-blocks)
	 (loop with connections = nil
	       for block in block-or-blocks
	       do
	   (setf connections
		 (gather-connections-for-block block connections))
	       finally
		 (return connections)))
	(t
	 (copy-list-using-gensym-conses (connections block-or-blocks)))))


(def-structure-method valid-workstation-context-p (dragging-state)
  (and (funcall-superior-method dragging-state)
       (if (move-dragging-style-p dragging-state)
	   (valid-image-plane-p
	     (image-plane-showing-objects-being-dragged? dragging-state))
	   t)
       (not
	 (frames-currently-being-dragged-have-been-deleted-p dragging-state))))


(define-event-handler mouse-motion-in-dragging-state
    ((dragging-state workstation-context-specifics)
     x-in-window y-in-window)
  ;; Establish an explicit-dragger context
  (let ((explicit-dragger-x-in-window? x-in-window)
	(explicit-dragger-y-in-window? y-in-window))
    (drag-outline-if-appropriate dragging-state nil)))

(define-event-handler mouse-down-in-dragging-state
    (mouse-pointer
      (dragging-state workstation-context-specifics)
      x-in-window y-in-window)
  (mouse-motion-in-dragging-state mouse-pointer)
  (let ((explicit-dragger-x-in-window? x-in-window)
	(explicit-dragger-y-in-window? y-in-window))
    (return-from-dragging-context dragging-state)))

(define-event-handler mouse-up-in-dragging-state
  (mouse-pointer
      (dragging-state workstation-context-specifics)
      x-in-window y-in-window)
  (mouse-motion-in-dragging-state mouse-pointer)
  (when (mouse-up-exits-this-context? dragging-state)
    (let ((explicit-dragger-x-in-window? x-in-window)
	  (explicit-dragger-y-in-window? y-in-window))
      (return-from-dragging-context dragging-state))))


(def-structure-method clean-up-workstation-context (dragging-state)
  (case (dragging-style dragging-state)
    (image-plane-dragging-style
     (erase-outline-of-image-plane-being-dragged dragging-state))
    (t
     (unless (frames-currently-being-dragged-have-been-deleted-p dragging-state)
       (stop-rendering-dragging-state-for-move-or-transfer dragging-state))
     (unless (workspace-for-objects-being-dragged? dragging-state)
       ;; We should get here iff transferring items that aren't on any
       ;; workspace, and this is an abort.  Otherwise, it is hoped/presumed that
       ;; the continuation function will handle any items in limbo.
       (let  ((objects-being-dragged (objects-being-dragged dragging-state)))
	 (setf (objects-being-dragged dragging-state) nil)
	 (delete-blocks-from-list-in-limbo
	   objects-being-dragged
	   (frame-reference-number-of-workstation-context dragging-state))
	 (reclaim-dragging-list objects-being-dragged)))
     (let ((image-plane?
	     (image-plane-showing-objects-being-dragged? dragging-state)))
       (when image-plane?
	 (remove-image-plane-cursor image-plane? dragging-state)))))
  (setf current-dragging-states
	(delete-dragging-element dragging-state current-dragging-states))
  (funcall-superior-method dragging-state))

;; Current Bugs (MHD 6/10/89)
;;
;; (1) When moving a group of blocks including text, turds are left when the
;;     image plane is refreshed.
;;
;; (2) When transfering a group of blocks, if one gets deleted the whole
;;     operation is aborted and the blocks are "orphaned" -- left without
;;     a superblock.
;;
;; (3) Dragging conses are lost when moving objects with external connections.



;;; `Delete-blocks-from-list-in-limbo' deletes every block in the list
;;; blocks that has not been reprocessed, and that has no superblock.

(defun delete-blocks-from-list-in-limbo (blocks reference-serial-number)
  (let ((fsn (copy-frame-serial-number reference-serial-number)))
    (loop for block in blocks
	  unless (or (frame-has-been-reprocessed-p block fsn)
		     (superblock? block))
	    do (delete-frame block))
    (reclaim-frame-serial-number fsn)))



;;; The capability `no-manual-connections' ...

;(def-capability no-manual-connections nil () ())




;;; `Return-from-dragging-context' is not a "return-function."  I.e. it does not
;;; straddle between two contexts.  It is the epilog of the dragging state.  It
;;; contains clean up necessary upon exiting dragging, and calls
;;; return-from-current-workstation-context.

(defun return-from-dragging-context (dragging-state)
  (case (dragging-style dragging-state)
    (image-plane-dragging-style
     (return-from-dragging-context-to-move-image-plane dragging-state))
    (t
     (cond
       ((and (objects-being-dragged dragging-state)
	     (image-plane-showing-objects-being-dragged? dragging-state)
	     (setf (workspace-for-objects-being-dragged? dragging-state)
		   (workspace-on-image-plane?
		     (image-plane-showing-objects-being-dragged?
		       dragging-state))))
	(cond
	  ((and (singleton? (objects-being-dragged dragging-state))
		(loose-end-p (first (objects-being-dragged dragging-state))))
	   ;; Connection dragging case (i.e., dragging loose end point)
	   (finish-connection-dragging dragging-state))
	  (t
	   (case (dragging-style dragging-state)
	     (move-dragging-style
	      (return-from-move-dragging-style dragging-state))
	     (transfer-dragging-style
	      (return-from-transfer-dragging-style dragging-state))))))
       (t
	(beep-at-user)
	(abort-current-workstation-context 'dragging))))))

;; In the image-plane case, be sure nothing bad can happen if the click is
;; outside of the window.  In particular, the code now assumes that there will
;; alway be pane found by mapping from the final-x/y-in-window.



;;; `Enter-image-plane-dragging-context' launches a dragging context to either
;;; move or resize image-plane, assuming all goes well and there are no aborts.

;;; If this is called with the mouse already down, then
;;; mouse-up-exits-this-context?  should be true, and the dragging context will
;;; await a mouse-up event to exit; otherwise, it awaits a mouse down.

(defun enter-image-plane-dragging-context
    (image-plane x-offset-from-dragger y-offset-from-dragger
		 &optional
		 (mouse-up-exits-this-context? (mouse-down-p)))
  (with-workstation-context-continuation
      (move-image-plane-upon-continuation-after-dragging)
    (enter-dragging-context-1
      image-plane x-offset-from-dragger y-offset-from-dragger
      nil mouse-up-exits-this-context? nil)))

;; Consider breaking sizing case down into its own function/facility.
     

;;; `Return-from-dragging-context-to-move-image-plane' returns (3) values from
;;; the dragging context:
;;;
;;;    (1) the image plane being dragged, or, if image-plane has a subplane,
;;;    that is returned instead;
;;;
;;;    (2) delta-x-in-window, the amount the image plane should be moved by,
;;;    restricted as per the restrictions in the dragging state (e.g., to the
;;;    window's size);
;;;
;;;    (3) delta-y-in-window, similarly
;;;
;;; `Move-image-plane-upon-continuation-after-dragging' is the continuation
;;; function, intended to be called after the dragging workstation context has
;;; been exited.  It moves the image plane returned by the specified delta-x/y-
;;; in-window amount.  In addition, it may move the image plane elsewhere if
;;; necessary to ensure that at least a tiny bit of the image is showing.  It
;;; does this by applying require-that-image-plane-be-visible to the image
;;; plane.  However, if this is an aborted context, it does nothing.

(defun return-from-dragging-context-to-move-image-plane (dragging-state)
  (let ((image-plane (second (objects-being-dragged dragging-state))))
    (return-from-current-workstation-context
      'dragging
      image-plane
      (-r (restrict-dragger-x-as-appropriate ; delta-x
	    (dragger-x-in-window)
	    dragging-state)
	  (+r (left-edge-of-image-in-window image-plane)
	      (x-offset-of-objects-being-dragged dragging-state)))
      (-r (restrict-dragger-y-as-appropriate ; delta-y
	    (dragger-y-in-window)
	    dragging-state)
	  (+r (top-edge-of-image-in-window image-plane)
	      (y-offset-of-objects-being-dragged dragging-state))))))

(defun move-image-plane-upon-continuation-after-dragging (workstation-context)
  (declare (ignore workstation-context))
  (with-workstation-context-return-values
      (image-plane delta-x-in-window delta-y-in-window)
    (unless (eq image-plane ':abort)			    ; abort flag checking - a bit ugly

      (move-image-plane image-plane
			delta-x-in-window delta-y-in-window)
      (let ((workspace (workspace-on-image-plane? image-plane)))
	(when workspace
	  (trigger-user-icon-movement-rules-for-blocks workspace)))
      (require-that-image-plane-be-visible image-plane))))


;;; `Finish-connection-dragging' is to be called when 
;;;
;;;    (dragging-style dragging-state)
;;;
;;; is either MOVE- or TRANSFER-DRAGGING-STYLE; and 
;;;
;;;    (objects-being-dragged dragging-state)
;;;
;;; contains a list of just one block.  That block must be a loose end.
;;; 
;;; 
;;;     (image-plane-showing-objects-being-dragged? dragging-state)
;;;
;;; must be an image plane showing a workspace that has just been clicked on at
;;; the designated final-x/y-in-window position.
;;;
;;; This works by first checking for the object near loose-end. If it's another
;;; loose-end, this joins the two connections.  If it's a block but not a
;;; loose-end, and it's allowed to have a connection added to it, this adds the
;;; connection to that block.  If it's a connection, this makes a T junction.
;;; If there is no object near the loose-end, this checks if the x/y location is
;;; close to the last bend, simulating detecting a "double click".  If so, it
;;; puts up an anchor point menu.  Otherwise, end-dragging-state, then add a
;;; bend (add a delta of 0 to delta-or-deltas, update loose-end side position),
;;; then begin-dragged-state for loose-end.

(defun finish-connection-dragging
    (dragging-state)
  (let* ((objects-being-dragged (objects-being-dragged dragging-state))
	 (final-image-plane
	   (image-plane-showing-objects-being-dragged? dragging-state))
	 (loose-end (first objects-being-dragged))
	 (connection-being-dragged (get-connection-for-loose-end loose-end))
	 #+ignore
	 (connection-frame?
	   (if (framep (connection-frame-or-class connection-being-dragged))
	       (connection-frame-or-class connection-being-dragged)))
	 (object-near-loose-end?
	   (find-object-near-loose-end-being-dragged
	     loose-end connection-being-dragged
	     final-image-plane))
	 end-dragging-p connection-type connection-was-not-made-p joined-connection)

      
    
    (when object-near-loose-end?
      (cond
	((not (connection-p object-near-loose-end?))	; use block-p or framep ??
	 (cond
	   ((loose-end-p object-near-loose-end?)
	    ;; join connections if possible
	    (setq connection-type 'joined-connections)
	    ;; HOOK FOR WS-REPRESENTATIONS IS IN join-two-connections
	    (multiple-value-setq (end-dragging-p joined-connection) 
	      (join-two-connections loose-end object-near-loose-end?)))
	   (t
	    ;; add connection to block if block if possible
	    (setq connection-type 'added-connection-to-block)
	    (multiple-value-setq (end-dragging-p connection-was-not-made-p)
	      (add-new-connection-to-block loose-end object-near-loose-end?))
	    (when (and g2-has-v5-mode-windows-p
		       (not connection-was-not-made-p))
	      ;;(format t "CONNECTING TO BLOCK::MOVING A CONNECTION~%")
	      (send-ws-representations-connection-moved
		connection-being-dragged)))))
	(t
	 ;; if it is the middle of another connection, make 
	 ;;   a T junction if possible
	 (setq connection-type 'made-junction)
	 (setq end-dragging-p
	       (make-junction object-near-loose-end? loose-end))

	 (when (and g2-has-v5-mode-windows-p)
	   ;;(format t "INSERT JUNCTION BLOCK::MOVE CONNECTIONS ~%")
	   (send-ws-representations-connection-moved
	     connection-being-dragged)
	   (send-ws-representations-connection-moved
	     object-near-loose-end?)))))
    (cond
      (end-dragging-p
       ;; Here is where we might make "whenever any connection is moved"
       ;; rules work. (another call below).
       #+ignore
       (trigger-user-icon-movement-rules-for-blocks connection-frame?)
       
       ;; The following is the interface (aka hack) to allow
       ;; GDA process connections as they are made by user edits
       (invoke-connection-handler-if-any
	 (if connection-was-not-made-p
	     object-near-loose-end?
	     connection-being-dragged)
	 (g2-window-for-this-workstation?
	   (workstation-this-is-on
	     (window-for-objects-being-dragged dragging-state)))
	 (if connection-was-not-made-p
	     'deleted-stub
	     connection-type)
	 (and (not connection-was-not-made-p)
	      (eq connection-type 'added-connection-to-block)
	      object-near-loose-end?))


       
       ;; Invoke connection event handlers.
       (if (not connection-was-not-made-p)
	   (case connection-type
	     (added-connection-to-block
	      (invoke-rules-for-direct-connection-chaining connection-being-dragged nil)
	      (invoke-rules-for-indirect-connection-chaining connection-being-dragged nil))
	     (joined-connections
	      (invoke-rules-for-direct-connection-chaining joined-connection nil)
	      (invoke-rules-for-indirect-connection-chaining joined-connection nil))
	     (made-junction
	      (invoke-rules-for-indirect-connection-chaining connection-being-dragged nil))))

       (return-from-current-workstation-context 'dragging))
      ((null object-near-loose-end?)
       (let ((exit-dragging-context? nil))
	 (multiple-value-bind (link-1-delta link-2-delta)
	     (compute-stretched-links-of-connection-being-dragged
	       connection-being-dragged loose-end)
	   (let* ((maximum-mouse-leeway
		    (+w constant-mouse-leeway
			(delta-x-in-workspace
			  scalable-mouse-leeway
			  (image-x-scale final-image-plane))))
		  (d1 (absw link-1-delta))
		  (d2 (absw link-2-delta)))
	     (cond
	       ((place-connection-if-orthogonal?
		  connection-being-dragged d1 d2 maximum-mouse-leeway)
		(update-connection-images
		  t (superblock? loose-end) connection-being-dragged)
		(delete-last-bend-from-connection
		  connection-being-dragged loose-end)
		(update-connection-images 
		  nil (superblock? loose-end) connection-being-dragged)
		(setq exit-dragging-context? t))
	       (t
		(update-images-of-blocks-and-connections-being-moved
		  t (superblock? loose-end)
		  objects-being-dragged
		  (external-connections-to-drag dragging-state))
		;; If no object near loose-end, then if the loose end is near
		;; to where it was last click, then place the connection.  
		;; Else, if the loose end is near the anchor point, delete the
		;; last bend.  Else, add a bend.
		(cond
		  ((loose-end-near-last-anchor-point? 
		     d1 d2 maximum-mouse-leeway)
		   (setq exit-dragging-context?
			 (handle-connection-click-near-last-anchor-point
			   connection-being-dragged loose-end)))
		  ((and (not (connection-diagonal-p connection-being-dragged))
			(<w d1 maximum-mouse-leeway))
		   ;; get rid of kink and add bend
		   (remove-kink-and-add-bend
		     connection-being-dragged loose-end link-1-delta))
		  (t
		   ;; if not near last bend, add a bend
		   (add-bend-to-connection
		     connection-being-dragged loose-end)))
		(update-images-of-blocks-and-connections-being-moved
		  nil (superblock? loose-end)
		  objects-being-dragged
		  (external-connections-to-drag dragging-state))))
	     (when (and connection-being-dragged g2-has-v5-mode-windows-p)
	       ;;(format t "DRAGGING LOOSE-END::MOVING A CONNECTION~%")
	       ;; WHAT ABOUT THE LOOSE-END???
	       (send-ws-representations-connection-moved connection-being-dragged)))
	   (when exit-dragging-context?
	     #+ignore (trigger-user-icon-movement-rules-for-blocks connection-frame?)
	     (return-from-current-workstation-context 'dragging))))))))


    

	    
;;; The variable `classes-that-do-not-normally-connect' contains a list
;;; of all of the built-in item classes that do not normally take manual
;;; connections.  This is used by find-object-near-loose-end-being-dragged
;;; at the end of dragging a loose end in order to determine which item
;;; a connection might be being dragged into.

(defparameter classes-that-do-not-normally-connect
  '(table text-box dial meter button
    definition chart freeform-table trend-chart))

;; note: definition added today.  If you connect an inferior class instance to a
;; superior definition, the KB will save out ok, but it will not be loadable!
;; Adding definition will keep most users from doing this; however, there is one
;; way they still can do this: if they have a stub on a definition created in an
;; older G2, they will still be able to do this!  This is not considered a high
;; enough risk to do anything about. (MHD/ML 7/25/90)
;;
;; --- UPDATE: You can connect to anything via the "create a connection" action,
;; released in 2.1!!  Problem!!  --- Possible solution: add the
;; no-manual-connection capability to the above classes!  (MHD 5/12/92)
;; 
;; note: dial, meter, button added 9/20/88 (this means that they might still
;; have connections put into 1.0, 1.0 Patch, or 1.1 Beta KBs.) (MHD 9/20/88)
;; others? compute in some other way??



;;; `Find-object-near-loose-end-being-dragged' finds the object nearest to
;;; loose-end, the loose end of the connection being dragged, that is eligible
;;; to receive this connection.
;;; 
;;; Note that loose-end and connection-being-dragged are not considered in
;;; search for objects near loose-end.
;;;
;;; Also not considered are instances of classes in the list that is the value
;;; of special variable classes-that-do-not-normally-connect.
;;;
;;; Also not considered are items for which no-manual-connections-p is true,
;;; i.e., items configured with the no-manual-connections property.

(defun find-object-near-loose-end-being-dragged
    (loose-end connection final-image-plane)
  (let ((objects-to-not-consider (dragging-list loose-end connection)))
    (prog1 (loop as object?
		 = (find-object-near-mouse
		     (dragger-x-in-window) (dragger-y-in-window)
		     final-image-plane
		     objects-to-not-consider
		     classes-that-do-not-normally-connect)
		 do (cond
		      ((and object?
			    (framep object?)
			    (no-manual-connections-p object?)
			    (not (loose-end-p object?)))
		       ;; Don't connect to objects with the
		       ;; "no-manual-connections" property (formerly
		       ;; capability).
		       (dragging-push object? objects-to-not-consider))
	       (t (return object?))))
      (reclaim-dragging-list objects-to-not-consider))))




;;; The `suspend-workstation-context method for dragging-state' and the
;;; `resume-workstation-context method for dragging-state' currently just
;;; arrange for rather awkward pane cursors used for image plane dragging,
;;; if any, to be hidden and restored, i.e., if a workstation context is
;;; pushed on top of dragging.  This happens frequently, for example, in
;;; Guide, which causes transfers and editing contexts to be pushed on
;;; top of workspace dragging.
;;;
;;; Note that nothing is currently done to remove graphics associated
;;; with dragging objects upon workspaces, nor objects being transferred
;;; between workspaces.
;;;
;;; This works by saving away the old pane cursors in a slot made to
;;; hold them, and then restoring them upon resumption.  
;;;
;;; Since the mouse will often be used in the course of the pushed-on context,
;;; this will the mouse-up-exits-this-context? flag in the dragging context upon
;;; resumption to the value of (mouse-down-p), thereby switching to a dragging
;;; context in which clicking ends the context if the user has resumed while the
;;; mouse is up.

(def-structure-method suspend-workstation-context (dragging-state)
  (funcall-superior-method dragging-state)
  (case (dragging-style dragging-state)
    (image-plane-dragging-style
     (setf (saved-copy-of-pane-cursors-for-image-plane-dragging?
	     dragging-state)
	   (erase-outline-of-image-plane-being-dragged
	     dragging-state t)))
    (t
     ;; maybe handle later?!
     )))

(def-structure-method resume-workstation-context (dragging-state)
  (funcall-superior-method dragging-state)
  (case (dragging-style dragging-state)
    (image-plane-dragging-style
     (setf (mouse-up-exits-this-context? dragging-state)
	   (mouse-down-p))
     (restore-outline-of-image-plane-being-dragged
       dragging-state
       (prog1
	   (saved-copy-of-pane-cursors-for-image-plane-dragging?
	     dragging-state)
	 (setf (saved-copy-of-pane-cursors-for-image-plane-dragging?
		 dragging-state)
	       nil)))
     (drag-outline-if-appropriate dragging-state nil))
    (t
     ;; maybe handle later?!
     )))





;;;; Connection Dragging Contexts


;;; `Enter-connection-dragging-context' passes right thru into
;;; enter-dragging-context.

#+unused
(defun enter-connection-dragging-context (loose-end image-plane)
  (enter-dragging-context-1 loose-end 0 0 image-plane))






;;;; Move Dragging Contexts



(define-workstation-context move-dragging ()
  :constructor (make-move-dragging-state ()))

(defun enter-move-dragging-context (block-or-blocks-to-drag
				    &optional 
				    (x-offset-from-dragger 0) 
				    (y-offset-from-dragger 0)
				    specific-image-plane
				    (mouse-up-exits-this-context? (mouse-down-p)))
  (enter-context-in-current-workstation
    'move-dragging (make-move-dragging-state) nil)
  (with-workstation-context-continuation (wrap-up-move-after-drag)
    (enter-dragging-context-1
      block-or-blocks-to-drag
      x-offset-from-dragger y-offset-from-dragger
      specific-image-plane
      mouse-up-exits-this-context?
      nil)))



(defun return-from-move-dragging-style (dragging-state)
  (return-from-current-workstation-context
    'dragging
    (copy-list-using-gensym-conses
      (objects-being-dragged dragging-state))))

(defun wrap-up-move-after-drag (workstation-context)
  (declare (ignore workstation-context))
  (with-workstation-context-return-values (blocks)
    (cond
      ((eq blocks ':abort)
       (abort-current-workstation-context 'move-dragging))
      (t
       (trigger-user-icon-movement-rules-for-blocks blocks)
       (reclaim-gensym-list blocks)
       (return-from-current-workstation-context 'move-dragging)))))





;;;; Transfer Dragging Contexts





(define-workstation-context transfer-dragging ()
  :constructor (make-transfer-dragging-state ())
  :state-variables
  ((transfer-return-information	; set after return from drag
     nil :reclaimer reclaim-gensym-list-function)
   (transfer-dragging-state-serial-number? nil)
   (select-transfered-objects-when-done nil)))


(def-structure-method clean-up-workstation-context (transfer-dragging-state)
  (gensym-dstruct-bind
      ((blocks external-connections)
       (transfer-return-information transfer-dragging-state))
    (when (transfer-dragging-state-serial-number? transfer-dragging-state)
      (delete-blocks-from-list-in-limbo
	blocks
	(transfer-dragging-state-serial-number? transfer-dragging-state))
      (reclaim-frame-serial-number (transfer-dragging-state-serial-number? transfer-dragging-state)))
    (reclaim-gensym-list external-connections)
    (reclaim-gensym-list blocks))
  (funcall-superior-method transfer-dragging-state))


(defun enter-transfer-dragging-context 
    (block-or-blocks-to-drag
      &optional 
      (x-offset-from-dragger 0) 
      (y-offset-from-dragger 0)
      specific-image-plane?
      (mouse-up-exits-this-context? (mouse-down-p))
      (select-transfered-objects-when-done t))
  (let ((state (make-transfer-dragging-state)))
    (setf (select-transfered-objects-when-done state) select-transfered-objects-when-done)
    (enter-context-in-current-workstation 'transfer-dragging state  nil))
  (cond
    ((if (atom block-or-blocks-to-drag)
	 (not (block-transferable-p block-or-blocks-to-drag))
	 (not (blocks-transferable-p block-or-blocks-to-drag)))
     (abort-current-workstation-context 'transfer-dragging))
    (t
     (with-workstation-context-continuation
	 (wrap-up-transfer-after-drag)
       (enter-dragging-context-1
	 block-or-blocks-to-drag
	 x-offset-from-dragger y-offset-from-dragger
	 specific-image-plane?
	 mouse-up-exits-this-context?
	 t)))))
    

;;; `Wrap-up-transfer-dragging-style' , which is called
;;; at the end of a dragging context for the transfer case.  It simply
;;; returns from the dragging workstation context a single value,
;;; transfer-return-information, which is the following list
;;;
;;;    (blocks external-connections workspace x-in-workspace y-in-workspace)
;;;
;;; The list is made up of fresh gensym conses which become the resposibility of
;;; the continuation function.  The blocks and external-connections elements are
;;; also fresh gensym lists owned by the continuation functions.  Note that the
;;; list blocks is guaranteed to be filtered of any deleted blocks; only new
;;; blocks will  be present.   However, it might be an empty list.

;;; `Wrap-up-transfer-after-drag' is called as the continuation function after
;;; in a transfer-dragging-state context, after having returned from a
;;; dragging-state context.  It expects the single return value,
;;; transfer-return-information, as described above.
;;;
;;; If there is a problem with the transfer, it notifies the user with a logbook
;;; message, and aborts the transfer-dragging workstation context.
;;;
;;; If there is no problem, it transfers the designated items.  It then invokes
;;; rules for user icon movement, if necessary.  Then, if there were items made
;;; incomplete by the transfer, it will launch a dialog to offer to recompile
;;; incomplete items.
;;;
;;; Eventually, it returns one of the following three possible values:
;;;
;;;    T, NO-RECOMPILE, or RECOMPILE
;;;
;;; If it does not need to launch the dialog, it returns immediately the single
;;; value T.  If it launches the dialog, it doesn't return immediately, but the
;;; dialog OK and CANCEL functions will return from this context.  In the case
;;; of the CANCEL function returning, it returns NO-RECOMPILE.  In the case of
;;; the OK function being called, it returns RECOMPILE.

(defun return-from-transfer-dragging-style (dragging-state)
  (return-from-current-workstation-context
    'dragging
    (with-image-plane-transform
	((image-plane-showing-objects-being-dragged? dragging-state))
      (let* ((x-in-window (dragger-x-in-window))
	     (y-in-window (dragger-y-in-window))
	     (block (first (objects-being-dragged dragging-state)))
	     (new-x-in-workspace
	       (-w (x-in-workspace x-in-window)
		   (x-offset-of-objects-being-dragged dragging-state)))
	     (new-y-in-workspace
	       (-w (y-in-workspace y-in-window)
		   (y-offset-of-objects-being-dragged dragging-state))))

	(unless (ignore-snap-grid-in-transfer-operations-p)
	  (setq new-x-in-workspace (restrict-dragger-x-as-appropriate new-x-in-workspace dragging-state)
		new-y-in-workspace (restrict-dragger-y-as-appropriate new-y-in-workspace dragging-state)))

	(gensym-list
	  ;; returns: (blocks external-connections workspace dx dy)
	  (copy-list-using-gensym-conses
	    (objects-being-dragged dragging-state))
	  (copy-list-using-gensym-conses
	    (external-connections-to-drag dragging-state))
	  (workspace-for-objects-being-dragged? dragging-state)
	  (-w new-x-in-workspace (left-edge-of-block block))
	  (-w new-y-in-workspace (top-edge-of-block block)))))))


(defun wrap-up-transfer-after-drag (workstation-context)
  (wrap-up-transfer-after-drag-1 workstation-context 'transfer-dragging))

(defun wrap-up-transfer-after-drag-1
    (workstation-context transfer-dragging-mode)
  (declare (ignore workstation-context))
  (with-workstation-context-return-values
      (transfer-return-information)
    (cond
      ((eq transfer-return-information ':abort)
       (abort-current-workstation-context transfer-dragging-mode))
      (t
       (gensym-dstruct-bind
	   ((blocks external-connections workspace delta-x-in-workspace delta-y-in-workspace)
	    transfer-return-information)
	 (let ((transfer-dragging-state
		 specific-structure-for-current-workstation-context))
	   (frame-serial-number-setf (transfer-dragging-state-serial-number? transfer-dragging-state)
				     (current-frame-serial-number))
	   (setf (transfer-return-information transfer-dragging-state)
		 ;; This copy is a leak in most cases. However, there is a case
		 ;; where it is not, and removing it causes an abort. See
		 ;; HQ-4704483 and HQ-4494688. -fmw, 2/10/04
		 (copy-tree-using-gensym-conses transfer-return-information))
	   (let ((string-explaining-problem?
		   (check-completion-of-transfer-after-drag blocks workspace)))
	     (cond
	       (string-explaining-problem?
		(beep-at-user)
		(notify-user "~a" string-explaining-problem?)
		(reclaim-text-string string-explaining-problem?)
		(abort-current-workstation-context transfer-dragging-mode))
	       (t
		(loop for block in blocks
		      do
		  (unless (or (transient-p block)
			      (permanent-block-p block)
			      (superblock? block))
		    (recursive-schedule-task-to-invoke-creation-rules
		      block)))
		(recording-items-made-incomplete
		    ('transfer)
		  (transfer-grouped-blocks-with-their-external-connections
		    blocks external-connections workspace
		    delta-x-in-workspace delta-y-in-workspace
		    nil)
		  (when (and (select-transfered-objects-when-done transfer-dragging-state)
			     (selection-enabled-p current-workstation-window))
		    (select-objects-after-transfer workspace blocks external-connections))
		  (trigger-user-icon-movement-rules-for-blocks blocks)
		  (cond
		    (items-made-incomplete-were-recorded?
		     (offer-to-recompile-after-transfer))
		    (t
		     (return-from-current-workstation-context
		       transfer-dragging-mode 't)))))))))))))


(defun offer-to-recompile-after-transfer ()
  (let ((inner-text-string (make-description-of-barrier-to-destabilization)))
    (enter-dialog
      (tformat-text-string "Recompile the KB?  (~A)" inner-text-string)
      nil nil
      'launch-compile-to-bring-kb-up-to-date-and-return-from-transfer-dragging
      (slot-value-list inner-text-string)
      'return-from-current-workstation-context ; if cancelled
      (slot-value-list 'transfer-dragging 'no-recompile))))


(defun launch-compile-to-bring-kb-up-to-date-and-return-from-transfer-dragging
    (additional-comment-string?)
  (launch-compile-to-bring-kb-up-to-date additional-comment-string?)
  (return-from-current-workstation-context 'transfer-dragging 'recompile))


(defun check-completion-of-transfer-after-drag (blocks workspace)
  (loop with uneditable-reason = nil
	with uneditable-item = nil
	for block in blocks
	for reason
	    = (cond
		((non-kb-workspace-p workspace)
		 "Cannot transfer items to non-KB workspaces!")
		((ancestor-p block workspace)
		 "Cannot place items on their subordinate workspace!")
		((and (proprietary-p workspace)
		      (not (eq (get-workspace-if-any block)
			       workspace)))
		 "Cannot transfer items to proprietary workspaces!")
		((and (transient-p workspace)
		      (permanent-block-p block))
		 "Cannot transfer permanent items to transient workspaces!")
		((setq uneditable-reason
		       (reason-permanent-items-module-is-not-editable block))
		 (setq uneditable-item block)
		 "Cannot transfer ~NF, because ~A")
		((setq uneditable-reason
		       (reason-permanent-items-module-is-not-editable workspace))
		 (setq uneditable-item workspace)
		 "Cannot transfer to ~NF, because ~A"))
	when reason return (tformat-text-string reason uneditable-item uneditable-reason)))
    





;;; Delete-blocks-being-dragged-for-user ... 

;(defun delete-blocks-being-dragged-for-user (blocks)
;  (loop with item-class
;	for block in blocks
;	collect block into blocks using dragging-cons
;	when (frame-of-class-p block 'item)
;	  do (setq item-class (class block))
;	  and count t into number-of-items	  
;	finally
;	  (enter-dialog
;	    (tformat-text-string
;	      "You are in the process of transferring ~a ~(~a~), but you did not click ~
;               on a valid KB workspace to place ~a.  You may continue the transfer or ~
;               delete the item~a?"
;	      (if (=f number-of-items 1)
;		  ;; sigh! (supply-a-or-an item-class) supplies an extra space!
;		  (if (begins-with-vowel? item-class) "an" "a")
;		  number-of-items)
;	      (if (=f number-of-items 1) item-class "items")
;	      (if (=f number-of-items 1) "it" "them")
;	      (if (=f number-of-items 1) "" "s"))
;	    (copy-constant-wide-string #w"Continue") (copy-constant-wide-string #w"Delete")
;	    #'(lambda ()) nil
;	    #'(lambda (blocks-to-delete reference-serial-number)
;		;; This can leave a turd -- the "ghost" image being
;		;; transferred is not properly erased! FIX!! (MHD 5/11/92)
;		(loop for block in blocks-to-delete
;		      do (delete-frame-after-checking-serial-number
;			   block reference-serial-number))
;		(reclaim-dragging-list-function blocks-to-delete))
;	    (slot-value-list blocks (current-frame-serial-number))
;	    (dragger-x-in-window) (dragger-y-in-window))))

;; No longer used.  It was thought to be overkill.  The introduction of the
;; return function return-from-dragging-context-for-newly-edited-text-box for
;; text boxes, which pops you back into the editor if you misplace a newly
;; edited text box, is thought to make the old behavior of beep & delete for
;; other cases seem fine.  (MHD 6/8/92)

;; This (and the clean-up code for the dragging context) should have the same
;; logic as the code for delete in handle-dialog-button for dealing with
;; junction blocks.  As things now stand, both might now create junction blocks
;; that will remain in limbo forever!



;;; Return-from-dragging-context-for-newly-edited-text-box is called to end the
;;; dragging context after an edit of a newly created and edited text box.  It
;;; has much special knowledge of the dragging context and therefore belongs in
;;; the MOVES module.  It also works closely with the specialized function
;;; hand-place-on-return, in FACILITIES.

;;; This expects to the workstation context return function only for a dragging
;;; context created by hand-place-on-return.  If this is a (non-deleted) text
;;; box being dragged but the destination workspace it is about to be placed on
;;; is not a KB workspace, this manages putting the text box back into the
;;; editor, with the same return function as it previously had, i.e.,
;;; hand-place-on-return.

;;; The return information that this expects (listed in workstation-context-
;;; return-information) is just the following
;;;
;;;     x-in-workspace
;;;     y-in-workspace
;;;
;;; These should just be propagated in via hand-place-on-return.  

;;; See also hand-place-on-return in the Class Choice Actions section of FACILITIES.

(defun reenter-editor-if-not-hand-placed (workstation-context)
  (declare (ignore workstation-context))
  ;; NEEDS WORK!  (For now, clicking astray won't reenter the editor, but
  ;; will delete the item just edited.  A regression!)
;  (let* ((dragging-state
;           (specific-structure-for-workstation-context workstation-context))
;         (workstation-context-return-information
;           (workstation-context-return-information workstation-context))
;         (x-in-window (first workstation-context-return-information))
;         (y-in-window (second workstation-context-return-information)))
;    (cond
;      ((and (or (null (workspace-for-objects-being-dragged? dragging-state))
;                (not (kb-workspace-p
;                       (workspace-for-objects-being-dragged? dragging-state))))
;            (car (objects-being-dragged dragging-state))
;            (not (frame-has-been-reprocessed-p
;                   (car (objects-being-dragged dragging-state))
;                   (frame-reference-serial-number-for-dragging-state dragging-state))))
;       (let ((text-box (car (objects-being-dragged dragging-state))))
;         (drag-outline-if-appropriate dragging-state t)  ; final erase
;         (clear-block-is-currently-being-dragged-if-appropriate text-box dragging-state)
;         (reclaim-dragging-list (objects-being-dragged dragging-state))
;         (setf (objects-being-dragged dragging-state) nil)
;         (exit-current-workstation-context-in-return-function 'dragging)))
;      (t
;       (exit-current-workstation-context-in-return-function 'dragging))))
  )

;; This function was introduced 6/8/92, for 3.0 Beta Rev.  8.  Replacing the
;; "rev.  2" behavior of having a dialog for any misplaced item.  That was
;; thought to be overkill.  I think this is getting pretty close to just
;; right.  (MHD 6/8/92)




;;; The defvar `drawing-on-behalf-on-dragging-state?' informs some drawing routines
;;; that the objects they are drawing are all in their dragging state, and hence
;;; consist of XOR-ed outlines.

; (defvar drawing-on-behalf-on-dragging-state? nil)



;;; `drag-outline-if-appropriate' updates the rendering for the dragging state
;;; if necessary.  It dispatchs between two cases i.e. the image plane style
;;; and move/transfer styles.

(defun drag-outline-if-appropriate
       (dragging-state just-erase-if-currently-drawn?)
  (let* ((current-x-in-window-of-mouse? (dragger-x-in-window))
	 (current-y-in-window-of-mouse? (dragger-y-in-window)))
    (case (car (objects-being-dragged dragging-state))
      (image-plane
       (cond
	 (just-erase-if-currently-drawn?
	  (erase-outline-of-image-plane-being-dragged dragging-state))
	 ((or (not (eql current-x-in-window-of-mouse?
			(previous-x-in-window-of-mouse? dragging-state)))
	      (not (eql current-y-in-window-of-mouse?
			(previous-y-in-window-of-mouse? dragging-state))))
	  (move-outline-of-image-plane-being-dragged
	    dragging-state
	    current-x-in-window-of-mouse?
	    current-y-in-window-of-mouse?))))
      (t
       (when (objects-being-dragged dragging-state)
	 (move-or-transfer-blocks-being-dragged-if-appropriate
	   dragging-state
	   current-x-in-window-of-mouse?
	   current-y-in-window-of-mouse?
	   just-erase-if-currently-drawn?))))))





;;; `Move-or-transfer-blocks-being-dragged-if-appropriate' cases on the
;;; drawing style and then does the appropriate erase and drawing for
;;; the objects-being-dragged.  The drawing is implemented by
;;; shift-blocks-with-their-external-connections for the
;;; move case and shift-and-draw-blocks-being-transferred in the
;;; transfer case.  In the transfer case two operations maybe required
;;; if the objects are moving from one image plane to another.  Care
;;; is taken to suppress the flicker if nothing is changing.

(defun move-or-transfer-blocks-being-dragged-if-appropriate
    (dragging-state dragger-x dragger-y just-erase-if-currently-drawn?)
  (let* ((objects-being-dragged (objects-being-dragged dragging-state))
	 (old-image-plane?
	   (let ((image-plane?
		   (image-plane-showing-objects-being-dragged? dragging-state)))
	     (if (and image-plane?	; minimal guarding against crash!!
					;   IMPROVE!! (MHD/BAH 5/2/90)
		      (workspace-on-image-plane? image-plane?))
		 image-plane?))))
    (cond
      ;; Transfer Dragging Style
      ((transfer-dragging-style-p dragging-state)
       (let* ((current-image-plane?
		(nth-value 1 (decode-window-position
			       (window-for-objects-being-dragged dragging-state)
			       dragger-x dragger-y)))
	      (new-image-plane?
		(if (not just-erase-if-currently-drawn?)
		    current-image-plane?))
	      (same-image-plane?
		(eq old-image-plane? new-image-plane?)))

	 ;; Does it need to be moved?
	 (when (or (not same-image-plane?)
		   (if new-image-plane?
		       (not (eql dragger-x
				 (previous-x-in-window-of-mouse? dragging-state))))
		   (if new-image-plane?
		       (not (eql dragger-y
				 (previous-y-in-window-of-mouse? dragging-state))))
		   (if just-erase-if-currently-drawn?
		       old-image-plane?))
	   (let ((dragger-x* dragger-x)
		 (dragger-y* dragger-y))

	     ;; Update snap grid if image-plane changed.
	     (unless same-image-plane?
	       (compute-snap-grid-for-transfer dragging-state
						(if current-image-plane?
						    (workspace-on-image-plane? current-image-plane?))))
	     ;; Maybe restrict dragger-x,y
	     (when current-image-plane?
	       (with-image-plane-transform (current-image-plane?)
		 (setq dragger-x* (x-in-window
				    (+f (restrict-dragger-x-as-appropriate
					  (-f (x-in-workspace dragger-x)
					      (x-offset-of-objects-being-dragged dragging-state))
					  dragging-state)
					(x-offset-of-objects-being-dragged dragging-state)))
		       dragger-y* (y-in-window
				    (+f (restrict-dragger-y-as-appropriate
					  (-f (y-in-workspace dragger-y)
					      (y-offset-of-objects-being-dragged dragging-state))
					  dragging-state)
					(y-offset-of-objects-being-dragged dragging-state))))))

	     ;; Yes, move it, and drawing twice if we changed image-planes.
	     (cond (just-erase-if-currently-drawn?
		    (when old-image-plane?
		      (shift-and-draw-blocks-being-transferred
			dragging-state old-image-plane? dragger-x* dragger-y* t nil)))
		   (same-image-plane?
		    (when old-image-plane?
		      (shift-and-draw-blocks-being-transferred
			dragging-state old-image-plane? dragger-x* dragger-y* t t)))
		   (t
		    (when old-image-plane?
		      (shift-and-draw-blocks-being-transferred
			dragging-state old-image-plane? dragger-x* dragger-y* t nil))
		    (when new-image-plane?
		      (shift-and-draw-blocks-being-transferred
			dragging-state new-image-plane? dragger-x* dragger-y* nil t))))

	     ;; Save away the new positions.
	     (setf (image-plane-showing-objects-being-dragged? dragging-state)
		   new-image-plane?)
	     (setf (previous-x-in-window-of-mouse? dragging-state)
		   dragger-x)
	     (setf (previous-y-in-window-of-mouse? dragging-state)
		   dragger-y)))))
      
      ;; Guard.
      ((null old-image-plane?)
       ;; Should never get here, because this case is checked for at the
       ;;   top of the handler... trouble
       nil)

      ;; Move Dragging Style      
      (t
       (when (or (not (eql dragger-x
			   (previous-x-in-window-of-mouse? dragging-state)))
		 (not (eql dragger-y
			   (previous-y-in-window-of-mouse? dragging-state)))
		 just-erase-if-currently-drawn?)
	 (let ((dragger-x-in-workspace nil)
	       (dragger-y-in-workspace nil)
	       (workspace (workspace-on-image-plane?
			    old-image-plane?))
	       (first-block (car objects-being-dragged)))
	   ;; Dragger-x,y is the proposed position for left,top of the first
	   ;; block.
	   (with-image-plane-transform (old-image-plane?)
	     (setf dragger-x-in-workspace (x-in-workspace dragger-x))
	     (setf dragger-y-in-workspace (y-in-workspace dragger-y)))
	   (let* ((delta-x-in-workspace
		    (-w (restrict-dragger-x-as-appropriate
			  (-w dragger-x-in-workspace
			      (x-offset-of-objects-being-dragged
				dragging-state))
			  dragging-state)
			(left-edge-of-block first-block)))
		  (delta-y-in-workspace
		    (-w (restrict-dragger-y-as-appropriate
			  (-w dragger-y-in-workspace
			      (y-offset-of-objects-being-dragged
				dragging-state))
			  dragging-state)
			(top-edge-of-block first-block))))
	     (shift-blocks-with-their-external-connections
	       objects-being-dragged (external-connections-to-drag dragging-state)
	       just-erase-if-currently-drawn? workspace
	       delta-x-in-workspace delta-y-in-workspace
	       nil nil t)))
	 (setf (previous-x-in-window-of-mouse? dragging-state)
	       dragger-x)
	 (setf (previous-y-in-window-of-mouse? dragging-state)
	       dragger-y))))))

;; Called only by drag-outline-if-appropriate



;;; `With-on-image-plane-for-moves' abstracts the environment used in this
;;; module when updating the image-plane cursors.

(defmacro with-on-image-plane-for-moves ((image-plane) &body body)
  (avoiding-variable-capture (image-plane)
    `(with-raw-window-transform-and-draw-area
	 ((gensym-window-for-image-plane ,image-plane))
       (with-nested-transform-and-draw-area-of-image-plane-contents? (,image-plane)
	 (on-image-plane (,image-plane)
	   ,@body)))))

;; Note: This code isn't using the standard interface to drawing.  Queues may
;; need draining, for example.  It duplicates some code in
;; shift-and-draw-blocks-being-transferred.



;;; `Shift-and-draw-blocks-being-transferred' shifts the outline being
;;; transfered to the new position on the given image-plane.  If the outline is
;;; moving from one image plane to another this routine must be called twice.
;;; The dragging-state is updated to reflect the new position, and the
;;; image-plane-cursor slot of the affected image-planes are kept in synch.

(defun-allowing-unwind shift-and-draw-blocks-being-transferred
    (dragging-state image-plane
		    new-x-in-window new-y-in-window
		    erase? draw?)
  (with-on-image-plane-for-moves (image-plane)
    (when erase?
      (let ((erase-instead? t))
	(draw-image-plane-cursor-1 dragging-state)
	(unless draw?
	  (remove-image-plane-cursor image-plane dragging-state))))
    (when draw?
      (setf (x-in-window-for-blocks-being-transferred dragging-state)
	    new-x-in-window)
      (setf (y-in-window-for-blocks-being-transferred dragging-state)
	    new-y-in-window)
      (draw-image-plane-cursor-1 dragging-state)
      (add-image-plane-cursor image-plane dragging-state))))






;;; `Update-images-of-blocks-and-connections-being-moved' is used in move style
;;; drawing to do all rendering of the objects-being-dragged.

(defun update-images-of-blocks-and-connections-being-moved
    (erase? workspace-enclosing-drawing blocks connections)
  (let* ((first-block
	   (first blocks))
	 (current-drawing-transfer-mode
	   (if (render-frame-in-xor-overlay-p first-block)
	       :xor
	       current-drawing-transfer-mode))
	 (update-images-in-xor-overlay-p t)
	 (bleeding-hack			    ; See update-connection-images-1
	   (if connections :connection-bleeding nil)))

    (multiple-value-bind (extreme-left-edge
			   extreme-top-edge
			   extreme-right-edge
			   extreme-bottom-edge) 
	(determine-extreme-edges-of-blocks-and-connections 
	  blocks connections nil)
      (update-images
	erase?
	first-block					    ; Note L
	workspace-enclosing-drawing
	extreme-left-edge
	extreme-top-edge
	extreme-right-edge
	extreme-bottom-edge
	bleeding-hack
	'draw-blocks-and-connections-being-moved
	blocks connections))))

;; Note L: We lie and tell update-images that only the first subblock is being
;; drawn.  But, it doesn't matter since we're drawing in the XOR overlay.

;; This used to have two identical calls to update-images. Don't know why.



;;; `Draw-blocks-and-connections-being-moved' a subfunction of
;;; update-images-of-blocks-and-connections invoked via update-images.  It is
;;; used only in move style dragging.

(defun draw-blocks-and-connections-being-moved
    (objects-being-dragged external-connections-to-drag)
  (with-transfer-mode-when-drawing
      ((if (and objects-being-dragged
		(render-frame-in-xor-overlay-p (first objects-being-dragged)))	
	   :xor
	   current-drawing-transfer-mode))

    ;; This used to use draw-block, which includes the cleanup of
    ;; overlapping blocks,  We don't need that here since it is taken care
    ;; of by update-images.
    (loop for block in objects-being-dragged
	  do (draw-block-possibly-with-frame block t))

    (loop for connection in external-connections-to-drag
	  when (memq (output-end-object connection) objects-being-dragged)
	    do (draw-connection connection nil))))



;;;; Image-plane Cursors



;;; The slot `image-plane-cursors' in an image plane contains a graphics-cons
;;; list of "image-plane cursors".

;;; An `image-plane cursor' is either:
;;;  (1) a dragging-state structure that represents one or more blocks being
;;;      transferred and across a particular image plane, or
;;;  (2) a graphics-list of (color x0 y0 x1 y1), which draws a dotted rectangle
;;;      used for the selection rubberband rectangle. x,y are in workspace coor.
;;;  (3) a graphics-list of (selectable color . points), which is the selection
;;;      highlight for the given selectable (we don't need fsn protection since
;;;      we actively remove the cursor when the selectable becomes invalid.
;;;  (4) a graphics-list of (managed-float managed-float color . points), which
;;;      is the dotted outline drawn when resizing a group of objects

;;; All stored x,y's are in workspace coor.

;;; The dragging-state object is owned by some workstation context.  However,
;;; the list in the second case is owned by the image-plane.  So it is reclaimed
;;; while the dragging-state is not in reclaim-image-plane-cursors.

;;; To maintain a pane cursor, it is necessary to "refresh" portions of it that get
;;; erased when areas of the image plane are repainted.  This is now done in two
;;; places in work-on-drawing-workspace.

;;; Adding and deleting of image-plane cursors from image planes is currently
;;; done in MOVES.

(def-concept image-plane-cursor)


;;; The function `add-image-plane-cursor' pushes the cursor onto the
;;; image-plane's list but does not do any drawing.

(defun add-image-plane-cursor (image-plane cursor)
  (unless (memq cursor (image-plane-cursors image-plane))
    (graphics-push cursor (image-plane-cursors image-plane))))

(defun remove-image-plane-cursor (image-plane cursor)
  (setf (image-plane-cursors image-plane)
	(delete-graphics-element
	  cursor (image-plane-cursors image-plane))))

(defun clean-up-image-plane-cursor (image-plane cursor image-plane-serial-number)
  (when (and (image-plane-has-not-been-reprocessed-p image-plane image-plane-serial-number)
	     (memq cursor (image-plane-cursors image-plane)))
    (draw-image-plane-cursor image-plane cursor) ; Erase
    (remove-image-plane-cursor image-plane cursor)
    (reclaim-image-plane-cursor cursor)))


;;; `add-image-plane-cursors-to-current-window' adds the image plane cursors of
;;; current-image-plane, if any, to the current window.  This expects to be
;;; called in an on-image-plane context.

(defun add-image-plane-cursors-to-current-window (&aux (c current-image-plane))
  (when (image-plane-cursors c)
    (within-named-dynamic-extent for-image-plane
      ;; These are ALWAYS drawn in the strict interior of the image-plane.
      (with-nested-transform-and-draw-area-of-image-plane-contents? (c)
	(loop for cursor in (image-plane-cursors c)
	      do (draw-image-plane-cursor-1 cursor))))))


;;; The function `draw-image-plane-cursor-1' always draws to the current image
;;; plane, irrespective of any image planes mentioned in the given dragging
;;; state.  It always draws in XOR, and so is used both to draw and erase the
;;; cursor.

(defun draw-image-plane-cursor-1 (cursor)
  (within-named-dynamic-extent for-image-plane
    (cond ((dragging-state-p cursor)
	   (draw-block-or-blocks-in-dragging-state cursor (objects-being-dragged cursor)))
	  ((resize-cursor-p cursor)	         ; (scale-mf ...)
	   (draw-resize-cursor cursor))
	  ((selection-rectangle-cursor-p cursor) ; (color x1 y1 x2 y2), like pane-cursors.
	   (draw-selection-rectangle-cursor cursor))
	  ((selection-highlight-cursor-p cursor) ; (selectable color . points)
	   (draw-selection-highlight cursor))
	  (t
	   (dwarn "Unknown image-plane cursor: ~s" cursor)))))

(defun draw-image-plane-cursor (image-plane cursor)
  (with-raw-window-transform-and-draw-area ((gensym-window-for-image-plane image-plane))
    (on-image-plane (image-plane)
      (with-nested-transform-and-draw-area-of-image-plane-contents? (image-plane)
	(with-transfer-mode-when-drawing (:xor)
	  (draw-image-plane-cursor-1 cursor))))))

(defun reclaim-image-plane-cursor (cursor)
  (cond ((dragging-state-p cursor)
	 (setf (image-plane-showing-objects-being-dragged? cursor) nil)) ; nec.?
	((resize-cursor-p cursor)
	 (reclaim-resize-cursor cursor))
	((selection-rectangle-cursor-p cursor)
	 (reclaim-graphics-list cursor))
	((selection-highlight-cursor-p cursor)
	 (reclaim-graphics-list cursor))
	(t
	 (dwarn "Unknown image-plane cursor: ~s" cursor))))

;;; `reclaim-image-plane-cursors' is called from the reclaimer for the
;;; image-plane-cursors slot of image planes.

(defun reclaim-image-plane-cursors (image-plane-cursors)
  (loop for cursor in image-plane-cursors doing
    (reclaim-image-plane-cursor cursor))
  (reclaim-graphics-list image-plane-cursors))



;;; The function `draw-block-or-blocks-in-dragging-state' draws some subset of
;;; the blocks in the dragging-state to the current image plane.

(defun draw-block-or-blocks-in-dragging-state (dragging-state block-or-blocks)
  (within-named-dynamic-extent for-image-plane
    (with-transfer-mode-when-drawing (:xor)
      (let ((first-block? (car-or-atom block-or-blocks)))
	(when first-block?
	  (let ((x-in-window (x-in-window-for-blocks-being-transferred dragging-state))
		(y-in-window (y-in-window-for-blocks-being-transferred dragging-state))
		(x-in-workspace (x-in-workspace-for-blocks-being-transferred dragging-state))
		(y-in-workspace (y-in-workspace-for-blocks-being-transferred dragging-state)))
	    
	    (unless (and (eq (workspace-on-image-plane? current-image-plane)
			     (original-workspace-of-objects-being-dragged? dragging-state)) ; Note A
			 (=r 0
			     (delta-x-in-window
			       (-w x-in-workspace (x-in-workspace x-in-window))
			       current-image-x-scale))
			 (=r 0
			     (delta-y-in-window 
			       (-w y-in-workspace (y-in-workspace y-in-window))
			       current-image-y-scale)))
	      (with-shifted-origin (x-in-workspace
				     y-in-workspace
				     x-in-window
				     y-in-window)
		(if (consp block-or-blocks)
		    (loop for block in block-or-blocks do
		      (draw-block block))
		    (draw-block block-or-blocks))))))))))

;; This is only used in the transfer case, where the objects being dragged
;; remain in their original workspace.  To avoid erasing the originals we
;; decline to draw when aligned with them.

;; Note A: This used to simply take the workspace of first-block.  But, that
;; block's workspace may be changing while the transfer is in progress, which
;; means that the appearance of this transfer representation could change while
;; the block is being transfered by another agent (eg, the evaluator).  By
;; sampling the block's workspace once at the start, we get the simpler
;; behavior that transfer reps do NOT depend on the current workspace of their
;; blocks.  (The old way left turds in cases where this dependence was not
;; noticed).  -fmw, 11/1/94

;; Require area args?



;;;; Selection Highlighting


;;; The concept `selection-highlighting' is specifically about old-style XOR
;;; mode selection highlighting, done with image-plane cursors. new style PAINT
;;; mode highlighting is in the `selection-handle' section.

(def-concept selection-highlighting)

;; Add to drawing-parameters? Also, line pattern.
(defparameter selection-highlight-line-width 3)

(defun selection-highlight-cursor-p (cursor)
  (and (consp cursor)
       (not (symbolp (car cursor)))
       (not (managed-float-p (car cursor)))))

(def-substitution-macro selection-highlight-thing (cursor)
  (first cursor))

(def-substitution-macro selection-highlight-color (cursor)
  (second cursor))

(def-substitution-macro selection-highlight-points (cursor)
  (cddr cursor))

(defun-substitution-macro create-selection-highlight-cursor (thing color points)
  (graphics-cons thing (graphics-cons color points)))

(defun draw-or-erase-all-selection-highlights (image-plane)
  (when (image-plane-cursors image-plane)
    (with-raw-window-transform-and-draw-area
	((gensym-window-for-image-plane image-plane))
      (on-image-plane (image-plane)
	(with-nested-transform-and-draw-area-of-image-plane-contents? (image-plane)
	  (with-transfer-mode-when-drawing (:xor)
	    (dolist (cursor (image-plane-cursors image-plane))
	      (when (selection-highlight-cursor-p cursor)
		(draw-selection-highlight cursor)))))))))

(defun erase-and-reclaim-all-selection-highlights (image-plane)
  (when (image-plane-cursors image-plane)
    (draw-or-erase-all-selection-highlights image-plane)
    (dolist-safely (cursor (image-plane-cursors image-plane))
      (when (selection-highlight-cursor-p cursor)
	(remove-image-plane-cursor image-plane cursor)
	(reclaim-image-plane-cursor cursor)))))


;;; The function `draw-selection-highlight' draws the highlight appropriate for
;;; the selectable, which is in the car of the cursor list.  The rest of the
;;; list are the color and x,y points in workspace coordinates.  An essential
;;; aspect of the cursor is that all of the information needed to draw one is in
;;; the cursor itself -- we don't need any coordinates from the selected object.
;;; This is so that we can undraw one even after the object has changed size or
;;; moved.

(defun draw-selection-highlight (cursor)
  (draw-selection-highlight-1
    cursor 
    (color-difference (map-color-or-metacolor-to-color-value
			(selection-highlight-color cursor))
		      current-background-color-value)))

(defun draw-selection-highlight-1 (cursor color-difference)
  ;; Selection highlights are drawn only for selected image planes.
  (when (image-plane-selected-p current-image-plane)
    (let ((points (selection-highlight-points cursor))
	  (thick selection-highlight-line-width))
      ;; selectable is either a block, a connection structure, or a text-cell.
      ;; Yes, but, it may be reclaimed here, so we can't dispatch on it for drawing.
      (with-transfer-mode-when-drawing (:xor)
	(cond ((null (nthcdr 4 points))   	; FIXME FIXME FIXME FIXME
	       (draw-rectangle-outline-in-window
		 (-f (x-in-window (first points)) thick)
		 (-f (y-in-window (second points)) thick)
		 (+f (x-in-window (third points)) thick 1)
		 (+f (y-in-window (fourth points)) thick 1)
		 color-difference thick thick))
	      (t
	       (let ((window-points
		       (loop for (x y) on points by 'cddr
			     collect (x-in-window x) using gensym-cons
			     collect (y-in-window y) using gensym-cons)))
		 (draw-wide-polyline window-points color-difference thick nil nil)
		 (reclaim-gensym-list window-points))))))))


;;; The function `move-all-selection-highlights' moves existing highlights for
;;; blocks, their subblocks, and internal connections, and recomputes highlights
;;; for external connections.

(defun move-all-selection-highlights (workspace blocks external-connections
						delta-x-in-workspace delta-y-in-workspace)
  (loop for block in blocks doing
    (move-selection-highlights block workspace delta-x-in-workspace delta-y-in-workspace)
    (loop for subblock being the subblocks of block doing
      (move-selection-highlights subblock workspace delta-x-in-workspace delta-y-in-workspace))
    (loop for connection being the output-connections of block doing
      (unless (memq connection external-connections)
	(move-selection-highlights
	  connection workspace delta-x-in-workspace delta-y-in-workspace))))
  (loop for connection in external-connections doing
    (recompute-selection-highlights connection)))


;;; The function `move-selection-highlights' moves the selection highlighting
;;; cursor on all image-planes showing given selectable.

(defun move-selection-highlights (selectable workspace dx dy)
  (loop for current-image-plane in (image-planes-this-is-on workspace) doing
    (unless (printing-image-plane-p current-image-plane)
      (let ((cursors (find-selection-highlights selectable current-image-plane)))
	(when cursors
	  (let ((gensym-window (gensym-window-for-image-plane current-image-plane)))
	    (with-raw-window-transform-and-draw-area (gensym-window)
	      (with-nested-transform-and-draw-area-of-image-plane-contents? (current-image-plane)
		(on-image-plane (current-image-plane)
		  (dolist (cursor cursors)
		    (move-selection-highlight cursor dx dy))))))
	  (reclaim-dragging-list cursors))))))

;;; The function `change-color-of-selection-highlight' sets the color of given
;;; cursor on image-plane.

(defun change-color-of-selection-highlight (image-plane cursor new-color)
  (let ((old-color (selection-highlight-color cursor)))
    (setf (selection-highlight-color cursor) new-color)
    (let ((current-image-plane image-plane)
	  (gensym-window (gensym-window-for-image-plane image-plane)))
      (with-raw-window-transform-and-draw-area (gensym-window)
	(with-nested-transform-and-draw-area-of-image-plane-contents? (current-image-plane)
	  (on-image-plane (current-image-plane)
	    (draw-selection-highlight-1
	      cursor
	      (color-difference (map-color-or-metacolor-to-color-value new-color)
				(map-color-or-metacolor-to-color-value old-color)))))))))


;;; The function `move-selection-highlight' moves given selection highlight
;;; image-plane-cursor by dx, dy.

(defun move-selection-highlight (cursor dx dy)
  (with-transfer-mode-when-drawing (:xor)
    (draw-selection-highlight cursor) ; erase
    (loop for sublist on (cddr cursor) by 'cddr doing ; selection-cursor-points
      (incff (car sublist) dx)
      (incff (cadr sublist) dy))
    (draw-selection-highlight cursor))) ; draw

(defun replace-selection-highlight (sublist new-cursor)
  (let ((old-cursor (car sublist)))
    (with-transfer-mode-when-drawing (:xor)
      (draw-selection-highlight old-cursor) ; erase
      (setf (car sublist) new-cursor)
      (reclaim-selection-highlight old-cursor)
      (draw-selection-highlight new-cursor)))) ; draw

(defun reclaim-selection-highlight (cursor)
  (reclaim-graphics-list cursor))


(defun find-selection-highlight (selectable? image-plane)
  (and selectable?
       ;; This could be ASSQ but for non-cons objects in the list.
       (loop for cursor in (image-plane-cursors image-plane) doing
	 (when (and (consp cursor)
		    (eq (car-of-cons cursor) selectable?))
	   (return cursor)))))


;;; The function `find-selection-highlights' returns all the highlights
;;; associated with thing. There can be at most one, except when thing is a
;;; table.  In that case, we include all of the table cell highlights, too.

(defun find-selection-highlights (thing image-plane)
  (loop for cursor in (image-plane-cursors image-plane)
	when (and (selection-highlight-cursor-p cursor)
		  (or (eq thing (selection-highlight-thing cursor))
		      (and (text-cell-p (selection-highlight-thing cursor))
			   (eq thing (get-table-for-cell (selection-highlight-thing cursor))))))
	  collect cursor using dragging-cons))


;; If speed is an issue here (probably not), we can change the list of
;; image-plane cursors into a hash table keyed on the selectable.

(defun find-selection-highlight-position (selectable image-plane)
  (loop for sublist on (image-plane-cursors image-plane)
	as cursor = (car sublist)
	when (and (consp cursor) (eq (car cursor) selectable))
	  return sublist))


;;;; Selection Rectangle

;;; This image-plane cursor simply draws a single dotted rectangle. Used for the
;;; selection rubber band.

(defun-substitution-macro create-selection-rectangle-cursor (color x-in-workspace y-in-workspace)
  (graphics-list color
		 x-in-workspace y-in-workspace
		 x-in-workspace y-in-workspace))

(defun selection-rectangle-cursor-p (cursor)
  (and (consp cursor) (symbolp (car cursor))))

(defun draw-selection-rectangle-cursor (cursor)
  (draw-dotted-rectangle (map-color-or-metacolor-to-color-value (first cursor))
			 (second cursor) (third cursor)
			 (fourth cursor) (fifth cursor)))

;;; The function `draw-dotted-rectangle' draws a dotted rectangle on the
;;; current image-plane. x0 y0 x1 y1 are in workspace coordinates.

(defun draw-dotted-rectangle (color-value x0 y0 x1 y1)
  (within-named-dynamic-extent for-image-plane
    (let ((points (gensym-list
		    ;; This point order makes the box appear little more animated.
		    (x-in-window x1) (y-in-window y0)
		    (x-in-window x0) (y-in-window y0)
		    (x-in-window x0) (y-in-window y1)
		    (x-in-window x1) (y-in-window y1)
		    (x-in-window x1) (y-in-window y0)))
	  (color-difference (color-difference color-value current-background-color-value))
	  (line-pattern 'dot))
      (with-transfer-mode-when-drawing (:xor)
	(draw-wide-polyline points color-difference 0 line-pattern nil)
	(reclaim-gensym-list points)))))



;;;; Dragging state vs. transfer and delete



;;; `Remove-object-from-dragging-context' removes the given object or
;;; connection from all current dragging states, without doing any drawing.  It
;;; is invoked by the cleanup method for loose-end and from delete-connection
;;; remove.  It removes the object from every dragging state, and clears the
;;; bit indicating it is being dragged.

;;; Note that remove-object-from-dragging-context can leave
;;; objects-being-dragged in the dragging state nil or even in an inconsistent
;;; state, and all dragging context operation handlers must therefore be able
;;; to deal with that situation appropriately.

(defun-void remove-object-from-dragging-context (object-or-connection)
  (loop with object-is-a-frame? = (framep object-or-connection)
	for dragging-state in current-dragging-states
	do (cond
	     (object-is-a-frame?
	      (setf (objects-being-dragged dragging-state)
		    (delete-dragging-element
		     object-or-connection
		     (objects-being-dragged dragging-state))))
	     ((memq			; a connection
	       object-or-connection
	       (external-connections-to-drag dragging-state))
	      (loop while
		    (memq
		     object-or-connection
		     (setf (external-connections-to-drag
				 dragging-state)
			   (delete-dragging-element
			    object-or-connection
			    (external-connections-to-drag
				  dragging-state)))))))
	finally 
	  (when object-is-a-frame?
	      (do-subblocks (sub object-or-connection)
		(clear-block-is-currently-being-dragged sub)))))



;;; The function `remove-as-block-being-dragged' removes the given block from
;;; ALL dragging states of which it is a part, both transfer and move, and
;;; re-renders it in its natural state (that is, outside of the XOR overlay).

(defun remove-as-block-being-dragged (block)
  (erase-transfer-representations-of-block block)
  (remove-object-from-dragging-context block)
  (remove-block-from-xor-overlay block))


;;; The function `remove-as-block-being-moved' removes the given block only
;;; from MOVE contexts.  Transfer contexts are untouched.

(defun remove-as-block-being-moved (block)
  (loop with still-being-transfered? = nil
	for dragging-state in current-dragging-states
	doing
    (when (dragging-state-contains-block-p dragging-state block)
      (cond ((move-dragging-style-p dragging-state)
	     (setf (objects-being-dragged dragging-state)
		   (delete-dragging-element
		     block (objects-being-dragged dragging-state))))
	    ((transfer-dragging-style-p dragging-state)
	     (setq still-being-transfered? t))))
	finally
	  (unless still-being-transfered?
	    (remove-block-from-xor-overlay block))))

;;; The function `remove-block-from-xor-overlay' re-renders the block outside
;;; of the XOR overlay, clearing the bits indicating that it is in overlay or
;;; is being dragged.

(defun remove-block-from-xor-overlay (block)
  ;; need to recurse into subblocks restoring flag
  (erase-images-of-block block nil)
  (do-subblocks (sub block)
    (clear-block-is-currently-being-dragged sub)
    (set-value-of-render-frame-in-xor-overlay sub (previous-render-state-was-xor-p sub)))
  (draw-images-of-block block nil))

;;; The function `recompute-external-connections-for-dragging-states'
;;; recomputes the external-connections for all dragging states which are
;;; dragging the given block.  This is called when a block being dragged
;;; acquires a new input connection.
;; -fmw, 10/19/94

(defun recompute-external-connections-for-dragging-states (block)
  (loop for dragging-state in current-dragging-states
	doing
    (when (and (move-dragging-style-p dragging-state)
	       (dragging-state-contains-block-p dragging-state block))
      (let ((objects-being-dragged
	      (copy-list-using-dragging-conses
		(objects-being-dragged dragging-state))))
	(reclaim-dragging-list (objects-being-dragged dragging-state))
	(reclaim-dragging-list (external-connections-to-drag dragging-state))

	(setf (objects-being-dragged dragging-state) nil ; Tidiness.
	      (external-connections-to-drag dragging-state) nil)
	
	(multiple-value-bind (new-objects new-external-connections)
	    (make-outline-for-blocks-to-drag objects-being-dragged t)

	  (setf (objects-being-dragged dragging-state) new-objects
		(external-connections-to-drag dragging-state) new-external-connections))))))




;;; The function `block-is-currently-being-moved-p' is true if the block is
;;; currently being MOVED, as opposed to TRANSFERRED.  In the transfer case,
;;; the block actually stays in its original position, usually with its
;;; original rendering, and a ghost (or "transfer representation") is moved
;;; about.  Thus, a block should switch to its ghost drawing mode only when
;;; being moved.

#+unused
(defun block-is-currently-being-moved-p (block)
  (when (block-is-currently-being-dragged-p block)
    (loop for dragging-state in current-dragging-states
	  thereis (and (move-dragging-style-p dragging-state)
		       (dragging-state-contains-block-p dragging-state block)))))


      
;;; The function `redraw-transfer-representations-of-block' draws or erases
;;; every "transfer representation" of the given block, meaning every place the
;;; block has been drawn due to its being transfered.

(defun redraw-transfer-representations-of-block (block erase-p)
  (when (block-is-currently-being-dragged-p block)
    (loop for dragging-state in current-dragging-states
	  doing
    (when (and (transfer-dragging-style-p dragging-state)
	       (dragging-state-contains-block-p dragging-state block))
	(let ((dragger-x (previous-x-in-window-of-mouse? dragging-state))
	      (dragger-y (previous-y-in-window-of-mouse? dragging-state))
	      (image-plane (image-plane-showing-objects-being-dragged? dragging-state)))

	  ;; Minimal guard, copied from
	  ;; move-or-transfer-blocks-being-dragged-if-appropriate
	  (when (and image-plane			    
		     (workspace-on-image-plane? image-plane))
	    
	    (for-workstation ((workstation-of-image-plane image-plane))
	      (shift-and-draw-blocks-being-transferred
		dragging-state image-plane dragger-x dragger-y erase-p (not erase-p)))))))))

;; This actually redraws all of the blocks being transfered, if their dragging
;; states contain this block, rather than just redrawing the given block.
;; Since this routine is called so rarely, we don't care much about
;; efficiency. -fmw, 10/19/94



;;; The function `erase-transfer-representations-of-block' is called when a
;;; block is deleted. Unlike the above routine, this erases JUST the given block.

(defun-allowing-unwind erase-transfer-representations-of-block (block)
  (loop for dragging-state in current-dragging-states
	doing
    (when (and (transfer-dragging-style-p dragging-state)
	       (dragging-state-contains-block-p dragging-state block))
      (let ((image-plane?
	      (image-plane-showing-objects-being-dragged? dragging-state)))
	(when image-plane?
	  (with-on-image-plane-for-moves (image-plane?)
	    (draw-block-or-blocks-in-dragging-state dragging-state block)))))))





;;;; Dragging Blocks and Connections




;;; `blocks-transferable-p' is true if blocks, a list of subblocks, may be
;;; transferred to another workspace.  To be transferable, the following must
;;; be true:
;;;
;;;  (1) all blocks must be subblocks of a workspace (presumably the same one);
;;;  (2) no blocks may be name boxes for a workspace; and
;;;  (3) no external connections may be present. (I.e. all connections, if
;;;      any, are between members of the list of blocks.)

(defun blocks-transferable-p (blocks)
  (loop for block in blocks
	always (block-transferable-p block blocks)))



;;; The substitution-macro `subblock-of-workspace-p' replaces what used
;;; to be simply (null (superblock? (superblock? block))).
;; -fmw, 11/24/93

(def-substitution-macro subblock-of-workspace-p (block)
  (let ((superblock? (superblock? block)))
    (and superblock?
	 (null (superblock? superblock?)))))



;;; `Block-transferable-p' ... Block must either not have a superblock, or must be
;;; the subblock of a workspace.  Other-blocks-to-be-transferred? is used to
;;; specify the entire group of blocks that are to be transferred.  Block can
;;; only be transferred if all of the blocks its is connected to are either in
;;; that group or are loose ends.  In addition,

(defun block-transferable-p (block &optional other-blocks-to-be-transferred?)
  (not
    (or (and (superblock? block)
	     (not (subblock-of-workspace-p block)))
	(frame-of-class-p block 'workspace)  ; Can't transfer workspaces. -fmw, 4/12/95
	(frame-of-class-p block 'workspace-name-box)
	(block-of-edit-workspace-p block)
	(loop for connection being each connection of block
	      thereis
	        (connection-external-to-blocks-p
		  block connection other-blocks-to-be-transferred?)))))






;;; `Make-outline-for-blocks-to-drag' ... modifies blocks, a dragging list of 
;;; blocks, to have in it loose ends connected to the group of blocks.  This
;;; determines if dragging is to be confined to the workspace the blocks are on
;;; depending on ... The values returned are:
;;; 
;;;    (1) blocks -- the argument, possibly altered, but always with
;;;          the same first element as originally given (it must be
;;;          reclaimed by the caller;
;;;          
;;;    (2) external-connections-to-drag -- a dragging list of
;;;          connections to drag, if any; and
;;;          
;;;    (3) dragging-confined-p -- true if blocks may not be transferred

(defun group-blocks-for-move-or-transfer (blocks)
  (loop for block in blocks
	;; Put appropriate stubs in the list.
	do (loop for connection being the connections of block
		 as input-end-object = (input-end-object connection)
		 as loose-end-maybe
		    = (if (eq input-end-object block)
			  (output-end-object connection)
			  input-end-object)
		 when (loose-end-p loose-end-maybe)	; See block-transferable-p.
		   do (unless (memq loose-end-maybe blocks)
			(setf (cdr blocks)	; Into cdr, so first block-
			      (dragging-cons	;   being-dragged stays the same
				loose-end-maybe (cdr blocks))))))
  (let* ((external-connections-to-drag
	   (list-external-connections-to-drag blocks))
	 (dragging-confined-p
	   (or external-connections-to-drag
	       (check-if-dragging-confined-due-to-superblock blocks))))
    (values blocks external-connections-to-drag dragging-confined-p)))

;; Added MEMQ test to avoid duplicating a loose end if it was previously present
;; in blocks.  This avoids the tedious and error-prone special case around
;; operate-on-area, which used to have to leave loose ends out of the list of
;; blocks to be dragged just so they would not be duplicated. (MHD 6/13/94)



;;; `Connection-external-to-blocks-p' is true if the connection from block does
;;; not lead to a block that is either one of the elements of blocks and is not
;;; a loose end.

(defun connection-external-to-blocks-p (block connection blocks)
  (let* ((output-end-object (output-end-object connection))
	 (other-block 
	   (if (eq output-end-object block)
	       (input-end-object connection)
	       output-end-object)))
    (and (not (memq other-block blocks))
	 (not (loose-end-p other-block)))))


(defun list-external-connections-to-drag (blocks)
  (loop for block in blocks
	nconc (loop for connection being each connection of block
		    when (connection-external-to-blocks-p block connection blocks)
		      collect connection using dragging-cons)))


(defun check-if-dragging-confined-due-to-superblock (blocks)
  (loop for block in blocks
	as previous-superblock = nil then superblock?
	as superblock? = (superblock? block)
	thereis
	(or
	  ;; Does this block have the same superblock as
	  ;;   all the others?
	  (if previous-superblock
	      (not (eq previous-superblock superblock?)))
	  
	  ;; Is this block the name box for a workspace?
	  (if superblock?
	      (if (workspace-p superblock?)
		  (or (superblock? superblock?)
		      (frame-of-class-p
			block 'workspace-name-box))
		  t)))))


;;; `Loose-end-dragging-outline-p' is true iff outline is a list of blocks to
;;; drag in the connection (loose-end) dragging case.

(defun loose-end-dragging-outline-p (outline)
  (and (null (cdr outline))
       (loose-end-p (first outline))))


;;; `make-outline-for-blocks-to-drag' ... Blocks must be top-level subblocks
;;; of a workspace.  Here, it is known to always be an actual list.

(defun make-outline-for-blocks-to-drag (blocks transfer-case?)
  (multiple-value-bind (blocks external-connections-to-drag confine?)
      (group-blocks-for-move-or-transfer blocks)


    ;; if a stub, change end side of loose-end
    (when (loose-end-dragging-outline-p blocks)
      #+development
      (assert (and
		(singleton? external-connections-to-drag)
		(singleton? blocks)))
      (let* ((loose-end (first blocks))
	     (connection (first external-connections-to-drag)))
	(when (connection-is-straight? connection)
	  (update-connection-images t (superblock? loose-end) connection)
	  (toggle-side-for-loose-end loose-end connection)
	  (update-connection-images nil (superblock? loose-end) connection))))
    
    ;; Straight external connections have to have kinks put in.    
    (when (or confine? (not transfer-case?))
      (loop for connection in external-connections-to-drag
	    do (put-kink-into-connection-if-straight connection blocks)))
    
    (values blocks external-connections-to-drag confine?)))

;;; `Start-rendering-dragging-state-for-move-or-transfer' will change the blocks
;;; and connections of the dragging state so they are rendered in XOR in
;;; dragging style.  It removes them from the screen, sets the appropriate bits,
;;; and then restores them to the screen.  In Painting mode it creates a defered
;;; drawing scope over these changes so the change happens in one redraw, and it
;;; does a force workspace drawing.  It also supresses the restore to the screen
;;; since this would happen in XOR and hence not be defered.

;;; `Stop-rendering-dragging-state-for-move-or-transfer' does the opposite.  It
;;; is called in the at the end of a dragging context, in the clean-up method.

(defun start-rendering-dragging-state-for-move-or-transfer (dragging-state)
  (let* ((blocks (objects-being-dragged dragging-state))
	 (external-connections-to-drag (external-connections-to-drag dragging-state))
	 (workspace? (get-workspace-if-any (first blocks))))
    (with-deferred-drawing ()
      (when workspace?
	(let ((region-invalidation-is-preferred t))
	  ;; erase blocks
	  (update-images-of-blocks-and-connections-being-moved t workspace? blocks external-connections-to-drag)))
      (loop for block in blocks do
	(unless (block-is-currently-being-dragged-p block)
	  ;; does block too...
	  (do-subblocks (sub block)
	    (set-block-is-currently-being-dragged sub)
	    (set-value-of-previous-render-state-was-xor sub (render-frame-in-xor-overlay-p sub))
	    (set-render-frame-in-xor-overlay sub))))
      (when workspace?
	(force-workspace-drawing workspace?)))))

;; Note 1: Have an option not to render in the XOR overlay.  The choice could
;; be a system parameter, and perhaps Shift-Drag should automatically do this.
;; (MHD 7/15/94)

;; Note 2: If the transfer mode is PAINT, then the first call to
;; update-images-of-blocks-and-connections-being-moved does the entire job: it
;; redraws the affected region of the workspace, while drawing the things being
;; dragged in XOR and dragging-style . Hence, the second call MUST be skipped.
;;    In XOR mode, the first call really just erases the objects and the
;; second call puts them back in dragging-style.
;;   Unfortunately, that does not work for opaque blocks.  Even in XOR mode, they
;; must be erased as if in paint mode.

;; Note 3: The solution is a pain: define the new special variable
;; region-invalidation-is-preferred, which is used by update-images to turn XOR
;; updates into invals.  Of course, that does not really erase anything -- the
;; block would get redrawn if the queue were drained.  So the second
;; update-images needs to draw only non-opaque blocks.

;; This still does not exactly replicate 3.0 behavior for the transfer of
;; opaque blocks in XOR mode:  we leave behind in the original position
;; the box enclosing a graph (its rendering in dragging-style).  In 3.0,
;; we left behind nothing.  However, note that the current behvior agrees
;; with that for text-boxes in 3.0 and 4.0.

;; Note 4: It would be nice to supress flicker if the rendering doesn't
;; change. (MHD 12/29/89)

(defun stop-rendering-dragging-state-for-move-or-transfer (dragging-state)
  (let* ((blocks (objects-being-dragged dragging-state))
	 (external-connections-to-drag (external-connections-to-drag dragging-state))
	 (workspace? (get-workspace-if-any (first blocks))))
    ;; erase xor image.
    (drag-outline-if-appropriate dragging-state t)
    (when (or (move-dragging-style-p     dragging-state)
	      (transfer-dragging-style-p dragging-state))
      (loop for block in blocks do
	(unless (loop for ds in current-dragging-states
		      unless (eq ds dragging-state)
			thereis (member block (objects-being-dragged ds)))
	  ;; we are the only one dragging this block.
	  (do-subblocks (sub block)
	    (clear-block-is-currently-being-dragged sub)
	    (set-value-of-render-frame-in-xor-overlay sub (previous-render-state-was-xor-p sub)))))
      (when workspace?
	(with-deferred-drawing ()
	  (let ((region-invalidation-is-preferred t))
	    (update-images-of-blocks-and-connections-being-moved nil workspace? blocks external-connections-to-drag)))))))

;;; `Shift-blocks-with-their-external-connections' is used too widely.  In it's
;;; simple case it erases the blocks, moves them, and then draws them.  The
;;; extreme edges of the workspace are updated.  The caller is responsible
;;; for assuring all the user contraints are obeyed.

;;; The draw can be supressed which is useful when deleting or starting a
;;; transfer.  The erase can be supressed which is useful when creating or
;;; finishing a transfer the blocks.

;;; It can also attempt to clear the bits indicating a block is being dragged
;;; which is useful when finishing a move.  The argument that triggers this,
;;; dragging-state-if-ending-hand-transfer?, may be NIL or T or a the dragging
;;; state being terminated.

;;; The argument final-update? forces the draw to be done via an invalidate.

;;; This will invalidate the area covered by the blocks unless the caller
;;; promises (via the optiaonl arg) that all the blocks are in the XOR layer.
;;; For the invalidate to work out this must be invoked with
;;; with-drawing-defered, otherwise it may attempt to put the blocks back on
;;; before they have been shifted.

(defun shift-blocks-with-their-external-connections
    (blocks external-connections
	    just-erase-if-currently-drawn?
	    workspace delta-x-in-workspace delta-y-in-workspace
	    &optional
	    just-draw?
					; dragging-state-if-ending-hand-transfer?
	    final-update?
	    all-blocks-are-in-xor?)

  (unless just-draw?
    ;; This call erases the transferred blocks from their original position.
    ;; Erasing requires a region inval if there are any opaque blocks, so we
    ;; bind region-invalidation-is-preferred to T.  Except if we are dragging,
    ;; then all blocks have an XORable representation.
    
    (let ((region-invalidation-is-preferred
	    (if all-blocks-are-in-xor? ; drawing-on-behalf-on-dragging-state?
		region-invalidation-is-preferred
		t)))
      (update-images-of-blocks-and-connections-being-moved
	'delete workspace blocks external-connections)))

  (unless just-erase-if-currently-drawn?
    (let ((do-not-update-selection-highlights t)) ; We do it later.
      (loop for block in blocks doing
	(shift-block block delta-x-in-workspace delta-y-in-workspace)
	;; change deltas on external connections!  don't do this if block is a
	;; loose-end
	(loop for connection in external-connections doing
	  (change-connection-deltas-for-object-being-dragged
	    connection block delta-x-in-workspace delta-y-in-workspace))))

    ;; Do this after all blocks shifted because it might follow
    ;; connections pointers between two or more elements of
    ;; blocks before all have been shifted. (MHD 5/21/91)
    (multiple-value-bind (extreme-left-edge
			   extreme-top-edge
			   extreme-right-edge
			   extreme-bottom-edge) 
	(determine-extreme-edges-of-blocks-and-connections 
	  blocks external-connections nil)
      (let ((current-draw-document-p nil))
	(enlarge-workspace-if-necessary ; optimize?
	  workspace
	  extreme-left-edge extreme-top-edge
	  extreme-right-edge extreme-bottom-edge)))

    ;; Move the selection highlights, if any.
    (unless (show-selection-handles-p)
      (move-all-selection-highlights workspace blocks external-connections
				     delta-x-in-workspace delta-y-in-workspace))
    
    ;; If this is the final update, then the objects are dropping down
    ;; out of the XOR overlay into their natural positions, besides
    ;; possibly changing their appearance from an outline to the real
    ;; thing.  This requires a region-inval to work, whether in XOR or
    ;; PAINT mode.  It is required in XOR mode because of the existance
    ;; of opaque blocks.
    (let ((region-invalidation-is-preferred
	    (if final-update? t region-invalidation-is-preferred)))
      (update-images-of-blocks-and-connections-being-moved
	nil workspace blocks external-connections))))

;; The function is responsible for way too many sorts of behavior.  It's used
;; for dragging moves and transfers.  It's also used to initially place a block
;; on a workspace.

;; It is a problem that the shift for a transfered block is done after the
;; add-subblock.  Factor out the shift so it can be done while the block
;; is not on any workspace?




;;; The function `add-xor-overlay-to-current-image-plane' draws all of the block
;;; being dragged on the current image plane.

(defun add-xor-overlay-to-current-image-plane ()
  (loop for dragging-state in current-dragging-states doing
    (when (and (move-dragging-style-p dragging-state)
	       (eq (image-plane-showing-objects-being-dragged? dragging-state)
		   current-image-plane))
      (draw-blocks-and-connections-being-moved
	(objects-being-dragged dragging-state)
	(external-connections-to-drag dragging-state)))))

;; Assuming clipping region set?  Should be the interior of the image-plane
;; (ie, not including the frame), at this point.





;;; The function `add-cursors-to-current-window' opens some number of XOR-ed
;;; cursor or cursor-like objects on the current window, in the given region.

(defun add-cursors-to-current-window (left top right bottom
					   pane-cursors-p
					   image-plane-cursors-p
					   xor-overlay-p)
  (when pane-cursors-p
    (add-pane-cursors-to-current-window current-pane left top right bottom))
  (when image-plane-cursors-p
    (add-image-plane-cursors-to-current-window))
  (when xor-overlay-p
    (add-xor-overlay-to-current-image-plane)))

;; Used in panes, this code is here to pick up dragging-state macros.




;;; The function `determine-extreme-edges-for-item-being-moved' returns the
;;; extreme edges of the item, except that connections are included only if
;;; they are connections to loose-ends.  In other words, this returns the
;;; extreme edges of the "rigid body" which is moved when the item is moved.

(defun determine-extreme-edges-for-item-being-moved (block)
  (with-extreme-edges (block)
    (update-extreme-edges-for-item-being-moved block)
    (values extreme-left-edge-so-far extreme-top-edge-so-far
	    extreme-right-edge-so-far extreme-bottom-edge-so-far)))

;; Used to determine the range of movement allowed for the item.
    


(defun update-extreme-edges-for-item-being-moved (block)
  (update-extreme-edges-from-block-bounds block)
  (loop for connection being the connections of block
	as other-end = (get-block-at-other-end-of-connection connection block)
	when (loose-end-p other-end)
	  do (update-extreme-edges-from-connection connection))

  ;; If the block is transformed, then
  ;;  (1) Its subblocks are guarenteed to be inside the block, hence do not
  ;;      contribute to the extreme edges.
  ;;  (2) Its subblocks' edges are in a different coordinate system, anyways.

  (unless (block-is-transformed-p block)
    (loop for subblock being each subblock of block 
	  do (update-extreme-edges-for-item-being-moved subblock))))




;;;; Dragging Image Planes





;;; Make-outline-for-image-plane-to-drag returns three values.
;;; The first is the outline used to render the image-plane 
;;; while dragging it.  It is of this form:
;;;  <image-plane-outline> : 
;;;    (image-plane <image-plane> <workspace> 
;;;          <image-plane-outline> <original-cross> <moving-cross>)
;;;  <image-plane-outline> : <outline-drawing>
;;;  <original-cross>  : <outline-drawing>
;;;  <moving-cross : <outline-drawing>
;;;  <outline-drawing> : <x-center/fixnum> <y-center/fixnum> ( <outline-drawing-1>* )
;;;  <outline-drawing-1> : ( <color> <left> <top> <right> <bottom> )
;;; These are constructed of drawing cons.

;;; The final two return values are nil.

(defun make-outline-for-image-plane-to-drag
       (image-plane x-offset-from-dragger y-offset-from-dragger)
  (values
    (nconc
      (dragging-list
	'image-plane image-plane
	(workspace-on-image-plane? image-plane))
      (let ((x-center
	      (+r (left-edge-of-image-in-window image-plane)
		  x-offset-from-dragger))
	    (y-center
	      (+r (top-edge-of-image-in-window image-plane)
		  y-offset-from-dragger)))
	(dragging-list
	  x-center y-center			; reference these as
						;   the original position
	  (add-image-plane-border-as-pane-cursor
	    image-plane 0 0)
	  x-center y-center
	  (add-plus-sign-as-pane-cursor
	    (pane-for-image-plane image-plane)
	    x-center y-center 16 16 4
	    'black)
	  x-center y-center
	  (add-plus-sign-as-pane-cursor
	    (pane-for-image-plane image-plane)
	    x-center y-center 16 16 4
	    'black)
	  nil nil)))
    nil ;; External Connections
    nil ;; Confined?
    ))



;;; Erase-outline-of-image-plane-being-dragged ...

(defun erase-outline-of-image-plane-being-dragged
    (dragging-state &optional return-copy-of-pane-cursors?)
  (prog1 (if return-copy-of-pane-cursors?
	     (copy-list-using-dragging-conses
	       (copy-tree-using-graphics-conses
		 (cddr (cdddr (objects-being-dragged dragging-state))))))
    (loop with objects-being-dragged
	    = (objects-being-dragged dragging-state)
	  with pane
	    = (pane-for-image-plane (cadr objects-being-dragged))
	  for pane-cursor
	      in (cddr (cdddr objects-being-dragged))
	      by #'cdddr
	  do (delete-pane-cursor pane-cursor pane)
	  finally
	    (reclaim-dragging-list (cddr (cdddr objects-being-dragged)))
	    (setf (cddr (cdddr objects-being-dragged)) nil))))

(defun restore-outline-of-image-plane-being-dragged
    (dragging-state saved-copy-of-pane-cursors)
  (setf (cddr (cdddr (objects-being-dragged dragging-state)))
	saved-copy-of-pane-cursors)
  (loop with objects-being-dragged
	    = (objects-being-dragged dragging-state)
	  with pane
	    = (pane-for-image-plane (cadr objects-being-dragged))
	for pane-cursor
	    in (cddr (cdddr objects-being-dragged))
	    by #'cdddr
	do (add-pane-cursor pane-cursor pane)))



;;; Move-outline-of-image-plane-being-dragged

(defun move-outline-of-image-plane-being-dragged
    (dragging-state dragger-x dragger-y)
  (loop with objects-being-dragged
	  = (objects-being-dragged dragging-state)
	with basis-image-plane = (cadr objects-being-dragged)
	with pane = (pane-for-image-plane basis-image-plane)
	for l on (cddr (cdddr objects-being-dragged)) by #'cdddr
	as (pane-cursor . positions-and-rest) = l
	as (x-position? y-position?) = positions-and-rest
	as first-time? = t then nil
	when x-position?
	  do
	    (let ((delta-x-in-window
		    (let ((position
			    (restrict-dragger-x-as-appropriate
			      dragger-x
			      dragging-state)))
		      (-r position
			  (prog1
			      x-position?
			    (setf (previous-x-in-window-of-mouse?
				    dragging-state)
				  dragger-x)
			    (setf (car positions-and-rest)
				  position)))))
		  (delta-y-in-window			 
		    (let ((position 
			    (restrict-dragger-y-as-appropriate
			      dragger-y
			      dragging-state)))
		      (-r position
			  (prog1
			      y-position?
			    (setf (previous-y-in-window-of-mouse?
				    dragging-state)
				  dragger-y)
			    (setf (cadr positions-and-rest)
				  position))))))
	      (unless (and (=r delta-x-in-window 0) (=r delta-y-in-window 0))
		(move-pane-cursor
		  pane-cursor pane delta-x-in-window delta-y-in-window)))))







;;; The function `move-blocks-with-their-external-connections' shifts the block
;;; or blocks by the given dx and dy, shifting their external (incoming)
;;; connections as well. Block-or-blocks can be a list of blocks made up of any
;;; kind of conses or just a block.  The list will not be recycled.

(defun move-blocks-with-their-external-connections
       (block-or-blocks workspace delta-x-in-workspace delta-y-in-workspace)
  (let ((blocks
	  (if (atom block-or-blocks)
	      (dragging-list block-or-blocks)
	      (copy-list-using-dragging-conses block-or-blocks))))
    (multiple-value-bind (list-of-blocks external-connections-to-drag confine?)
	(group-blocks-for-move-or-transfer blocks)
      (when confine?
	(loop for connection in external-connections-to-drag
	      do (put-kink-into-connection-if-straight connection list-of-blocks)))

      ;; Specifying final-update? as T was needed to get moves of objects with
      ;; connections in XOR mode to work.  The problem was that objects were
      ;; erased using an inval-region, but redrawn using XOR, down inside of
      ;; shift-blocks-with-their-external-connections. -fmw, 2/14/95
      (shift-blocks-with-their-external-connections
	list-of-blocks external-connections-to-drag
	nil workspace delta-x-in-workspace delta-y-in-workspace nil t)

      (reclaim-dragging-list list-of-blocks)
      (reclaim-dragging-list external-connections-to-drag))))





;;; `Transfer-blocks-with-their-external-connections' ... Blocks may be a
;;; dragging-cons list of blocks, or a single block.  Blocks must be workspace
;;; subblocks, i.e., not subblocks thereof.

(defun-simple transfer-blocks-with-their-external-connections
    (blocks workspace? new-x? new-y? note-as-kb-state-change?)
  (let ((blocks
	  (if (atom blocks)
	      (dragging-list blocks)
	      (copy-list-using-dragging-conses blocks))))
    (multiple-value-bind (list-of-blocks external-connections-to-drag confine?)
	(group-blocks-for-move-or-transfer blocks)
      (cond
	(confine?
	 (reclaim-dragging-list external-connections-to-drag)
	 (item-to-transfer-connected-stack-error blocks))
	(t
	 (transfer-grouped-blocks-with-their-external-connections
	   list-of-blocks external-connections-to-drag
	   workspace?
	   (if (null new-x?)
	       0
	       (-w new-x? (item-x-position (car list-of-blocks))))
	   (if (null new-y?)
	       0
	       (-w (-w new-y? (item-y-position (car list-of-blocks)))))
	   note-as-kb-state-change?)
	 (reclaim-dragging-list list-of-blocks)
	 (reclaim-dragging-list external-connections-to-drag)
	 nil)))))

;; This used to have a cousin, transfer-block-with-no-connections, that was a
;; optimized a bit for the case of no connections.  But things are too
;; complicated to support that right now.  Consider reviving it, at least
;; in spirit, as a later optimization.  (MHD 2/3/94)



;;; The defvar `transfer-in-progress' when bound to T prevents graphs from
;;; drawing themselves upon activation, which happens when they are newly added
;;; to a workspace.

(defvar transfer-in-progress nil)

;; We need this kludge variable cuz by the time a graph is activated due to
;; being dropped onto a workspace, its currently-being-dragged bit has already
;; been cleared. -fmw, 2/15/95




;;; `Transfer-grouped-blocks-with-their-external-connections' ... handles blocks
;;; "grouped" as by group-blocks-for-move-or-transfer, used by
;;; enter-dragging-context and transfer-blocks-with-their-external-connections.

;;; All elements of blocks must have the same superior, which must either be nil
;;; or a workspace, and must not be confined in any way, e.g., by connections to
;;; other blocks on in the argument.  External-connections must contain the
;;; connections between all elements of blocks, if any.  It is an error, to call
;;; this function with these constraints violated.

;;; Dragging-state-if-ending-hand-transfer? should be supplied only when
;;; finishing a transfer in a dragging context.  If supplied, it should be the
;;; dragging-state structure for the transfer in progress.  It will clear the
;;; bit indicating that each block in blocks is being dragged.  It does
;;; so at just the appropriate time in between erasing the old and drawing the
;;; new image, as needed.

(def-system-variable saved-position-or-next-lower-thing moves nil)

(defun-void transfer-grouped-blocks-with-their-external-connections
    (blocks external-connections workspace?
	    delta-x-in-workspace delta-y-in-workspace
	    note-as-kb-state-change?)
  (let ((original-workspace? (superblock? (car blocks))))
    (with-deferred-drawing ()
      (let ((region-invalidation-is-preferred t) ;; Note A
	    (saved-position-or-next-lower-thing nil))
	(unless (eq original-workspace? workspace?)
	  (note-modification-of-module-for-clear-text
	    workspace? original-workspace?))
	;; Erase from old workspace.
	(when (and original-workspace?
		   (neq original-workspace? workspace?))
	  ;; If another agent is dragging the block, then we must tear it away
	  ;; from that her since tranfering it would totally bewilder her.
	  ;; But we only do this if the transfer is from one workspace to another.
	  (loop for block in blocks doing
	    (when (block-is-currently-being-dragged-p block)
	      (remove-as-block-being-moved block)))
	  (shift-blocks-with-their-external-connections
	    blocks external-connections 'just-erase original-workspace?
	    0 0)) ; These args ignored, Note C.
	(when workspace?
	  (when note-as-kb-state-change? ; added. (MHD 9/27/91)
	    (note-kb-state-change workspace? 'workspace-frame)))
	;; Do the KB update.  Must not do any drawing, because the blocks
	;; have not yet been shifted to their final positions!!
	(let ((reversed-blocks
		;;  Reverse the list so that the stacking order is not reversed by
		;;  add-subblock. (MHD 4/21/92)
		;; See note by fmw and myself on 8/16/02 in
		;; g2-clone-list-contents, for a related explanation on why
		;; the reverse got moved up here so it can be used twice. -dkuznick, 8/20/02
		(reverse-list-using-gensym-conses blocks)))
	  (let ((do-not-note-permanent-changes-p note-as-kb-state-change?)
		(transfer-in-progress t))
	    (loop for block in reversed-blocks  ;; Note C
		  do (transfer-workspace-subblock block original-workspace? workspace?)))
	  ;; Draw on new workspace.
	  (when workspace?
	    (shift-blocks-with-their-external-connections blocks external-connections nil
							  workspace? delta-x-in-workspace delta-y-in-workspace
							  (neq workspace? original-workspace?)	    ; if true => just draws
							  t))					    ; Final update => inval
	  (loop for block in reversed-blocks ;changing this to reversed-blocks
					; from blocks is the key to rev. 1.57 to
					; fix bug HQ-4369427 -dkuznick, 8/20/02
		do
	    (when g2-has-v5-mode-windows-p
	      (send-ws-representations-item-insert-as-subblock
		block workspace? saved-position-or-next-lower-thing))
	    ;; For add-item-to-workspace event, we send it for each block and
	    ;; only for a new add, not for a transfer to the same ws
	    (when (and workspace?
		       (neq original-workspace? workspace?)
		       ;; so we don't get loose-ends
		       (frame-of-class-p block 'item))
	      (update-subscriptions-for-add-item-to-workspace
		workspace? block)))
	  (reclaim-gensym-list reversed-blocks))
	;; In any case, note that the blocks superiors have changed.
	(when (and original-workspace?
		   (neq original-workspace? workspace?))
	  (note-change-to-superior-of-block-or-blocks blocks))))
    ;; Outside the scope of the deferred drawing, do this.  The macro should do
    ;; this for us.
    (force-process-drawing-if-appropriate)))

;; Note A: The call on transfer-workspace-subblock can trigger activation,
;; and that can trigger drawing.  The block isn't in the right place yet.
;; Better to force us into a firmer defered drawing.  Meanwhile note that
;; the call that actually changed these blocks so they aren't drawn in their
;; dragging rendering did a with-defered-drawing, but didn't
;; call force-process-drawing-if-appropriate.

;; Note B: It is bogus that this routine is in the moves module.  It should
;; be part of the lower level substrate.  It be could if it it didn't do
;; all this junk with the dragging-flags, which I reasonably sure have
;; already been cleared in the clean-up method of the dragging-state.

;; Note C: Why can't we shift the blocks before we do the call on
;; transfer-workspace-subblock?





;;; The simple function `note-change-to-superior-of-block-or-blocks' should be
;;; called whenever the superior of a block changes.

(defun-simple note-change-to-superior-of-block-or-blocks (block-or-blocks)
  ;; A change in superior means our declarations may have changed.
  (defer-some-consistency-analysis
    (cond ((atom block-or-blocks)
	   (note-dependent-or-stable-status-change block-or-blocks))
	  (t
	   (loop for block in block-or-blocks doing
	     (note-dependent-or-stable-status-change block))))))




;;; `Transfer-workspace-subblock' transfers block from source-workspace?, if
;;; any, to destination-workspace? if any.  This assumes that block has been
;;; erased already, if need be.
;;;
;;; This does the following:
;;;
;;;    (1) if going off of a workspace, the module is changing, this calls
;;;    remove-as-subblock-if-necessary;
;;;
;;;    (2) if going from a workspace to either nowhere or to another workspace,
;;;    this calls remove-as-subblock;
;;;
;;;
;;;    (3) if going off of a workspace, call the
;;;    activate-if-possible-and-propagate method;
;;;
;;;    (4) if going to a workspace, call add-subblock;
;;;
;;;    (5) if not showing on the same image plane as before, call
;;;    event-update-status-of-block-showing

(defun-void transfer-workspace-subblock
    (block source-workspace? destination-workspace?)
  (let* ((source-module?
	   (if source-workspace? (get-module-block-is-in source-workspace?)))
	 (destination-module?
	   (if destination-workspace?
	       (get-module-block-is-in destination-workspace?))))
    
    (when (and source-workspace?
	       (null destination-workspace?)
	       (not (eq destination-module? source-module?)))
      ;; transfer off, write out subhierarchy before module change
      (remove-as-inferior-block block source-workspace?))
    
    (when (and source-workspace?
	       (not (eq source-workspace? destination-workspace?)))
      (let ((frame-serial-number (copy-frame-serial-number (frame-serial-number source-workspace?))))
	(remove-as-subblock block source-workspace? t)
	;; N.B. remove-as-subblock can delete workspaces !!
	(when (frame-has-been-reprocessed-p
		source-workspace? frame-serial-number)
	  (setf source-workspace? nil))
	(reclaim-frame-serial-number frame-serial-number)))
    
    (cond
      ((null destination-workspace?)
       ;; if "off", activate
       (funcall-method 'activate-if-possible-and-propagate block))
      (t
       (unless (eq destination-workspace? source-workspace?)
	 (add-subblock block destination-workspace?))))
    
    (unless (eq source-workspace? destination-workspace?)
      ;; Necessary?  C.f., 3.0.  Test for 4.0!!! (HOW?!) (MHD 1/20/94)
      (install-item-in-model-if-models-used block)
      (let ((now-showing?
	      (if (and destination-workspace?
		       (workspace-showing-p destination-workspace? nil))
		  t
		  nil)))
	(unless (eq (if (and source-workspace?
			     (workspace-showing-p source-workspace? nil))
			t
			nil)
		    now-showing?)
	  (event-update-status-of-block-showing block nil now-showing?))))))

;; In the only case where this is used, workspace is known already, so it may
;; as well be passed in.  This could recompute it or even check there even is
;; one, if that were needed.

;; Abstract further and better, esp. for transfer-item (below)!

;; Abstract the parts in MOVES better in light this new use!

;; This could be used for entities without connections, but the part
;; below was optimized, so I will leave it.

;; Note: shift-blocks-with-their-external-connections
;; has had a bug in it for some time (for dragging) that causes it
;; to fail to expand the workspace properly for objects with
;; stubs or connections with loose ends! FIX!

;; Note: MENUS has developed a bug that causes it to offer the
;; transfer option for objects with connections that are not stubs
;; but are have loose ends! FIX!

;; Note: put-kink-into-connection-if-straight is really
;; coded so that it erases then "kinks", then redraws
;; the connection as necessary; however, the code this
;; was derived from (in MOVES) erases it first; that
;; probably is a bug, and I even think some kludges
;; have been amassed on top of that to hide turding.
;; This needs investigation at some point. (MHD 8/28/89)


;;;; Selection Handles


;;; `Selection-handles' are paint-mode selection highlights, which also serve as
;;; affordances for resizing blocks, dragging connection vertices, etc.

(def-concept selection-handle)

(defparameter selection-handle-hit-distance 4)

(def-spot selection-handle-spot
    :slots (selection-handle-spot-type	; resize, rotate, vertex, etc.
	     selection-handle-spot-handle)
    :include simple-item-spot
    :enclosing-spot-type image-plane-spot
    :innermost-spot-p t
    :abstract-type nil
    :type-of-frame-represented item)

(defun push-selection-handle-spot (mouse-pointer block type handle x-in-workspace y-in-workspace)
  x-in-workspace y-in-workspace
  (let ((spot (make-selection-handle-spot)))
    (setf (selection-handle-spot-type spot) type
	  (selection-handle-spot-handle spot) handle)
    (push-last-spot mouse-pointer spot block)
    spot))

(defun selection-handle-mouse-cursor (selection-handle-spot)
  (case (selection-handle-spot-type selection-handle-spot)
    (vertex 'size-all)
    (resize (case (selection-handle-spot-handle selection-handle-spot)
	      ((top bottom) 'size-ns)
	      ((left right) 'size-we)
	      ((top-left bottom-right) 'size-nw-se)
	      ((top-right bottom-left) 'size-ne-sw)
	      (t 'default)))
    (t 'default)))

;;; The function `generate-spot-for-selection-handle' pushes a final
;;; selection-handle-spot if the mouse is close enough to a handle of
;;; block. Note that a different function takes care of computing this for
;;; connections.

(defun generate-spot-for-selection-handle (block mouse-pointer)
  (with-mouse-pointer-bindings (image-plane x-in-workspace y-in-workspace x-in-window y-in-window)
      mouse-pointer
    (on-image-plane-without-drawing (image-plane)
      ;; TODO: Quick check for point too far inside or outside block.
      (let* ((handle-positions (selection-handle-positions block))
	     (dist selection-handle-hit-distance) ; Minimum picking distance
	     handle? x0 y0)
	(loop for (name x y) on handle-positions by #'cdddr
	      as d = (vector-distance-in-workspace (absw (-f x-in-window (x-in-window x)))
						   (absw (-f y-in-window (y-in-window y))))
	      when (<f d dist)
		do (setq dist d
			 handle? name
			 x0 x
			 y0 y))
	(reclaim-graphics-list handle-positions)
	(when handle?
	  (push-selection-handle-spot mouse-pointer block 'resize handle? x0 y0))))))

;;; The function `selection-handle-positions' returns a new graphics list of the
;;; names and positions of all handles on given item. At least potential
;;; handles.

;; TODO: Include edges, only if room.
;; TODO: Spread them at small scales (implies we need to know the scale!)
(defun selection-handle-positions (block)
  (let ((left (left-edge-of-block block))
	(top (top-edge-of-block block))
	(right (right-edge-of-block block))
	(bottom (bottom-edge-of-block block)))
    (graphics-list 'top-left left top
		   'top-right right top
		   'bottom-right right bottom
		   'bottom-left left bottom)))

(defun adjust-rectangle-edges (edge-or-corner left top right bottom dx dy)
  (case edge-or-corner
    (top (incff top dy))
    (left (incff left left))
    (bottom (incff bottom dy))
    (right (incff right dy))
    (top-left (incff left dx) (incff top dy))
    (top-right (incff right dx) (incff top dy))
    (bottom-right (incff right dx) (incff bottom dy))
    (bottom-left (incff left dx) (incff bottom dy)))
  (values left top right bottom))


;;;; Selection Handle Drawing


(defparameter selection-handle-radius 3)

(def-kb-specific-variable selection-handle-icon moves ; This is the square version.
  (:funcall
    make-iconic-entity-with-specific-icon-description
    ((polychrome (fill . background) (line . foreground))
     fill (solid-rectangle (0 0) (6 6))
     line (outline (0 0) (0 6) (6 6) (6 0)))
    6 6 nil)
  nil
  reclaim-rubber-stamp-widgets)

(defun selection-handles-visible-p (thing image-plane)
  (and (show-selection-handles drawing-parameters)
       (image-plane-selected-p image-plane)
       (thing-selected-p thing image-plane)))

(defun draw-selection-handle (icon-description color x-in-window y-in-window)
  (let ((current-image-x-scale #.(normalized-scale))
	(current-image-y-scale #.(normalized-scale)))
    (with-shifted-origin (selection-handle-radius selection-handle-radius x-in-window y-in-window)
      (let ((icon-attributes-plist
	      (slot-value-list 'icon-color-pattern
			       (slot-value-list (slot-value-cons 'fill color)
						(slot-value-cons 'line 'foreground)))))
	(draw-icon-from-description
	  icon-description
	  icon-attributes-plist
	  0 0 (width-of-icon icon-description) (height-of-icon icon-description)
	  nil)
	(reclaim-slot-value-tree icon-attributes-plist)))))

(defun draw-selection-handles-for-block (block color)
  (let ((icon-description (icon-description (second selection-handle-icon)))
	(handles (selection-handle-positions block)))
    (loop for (name x-in-workspace y-in-workspace) on handles by #'cdddr doing
      (draw-selection-handle icon-description color (x-in-window x-in-workspace) (y-in-window y-in-workspace)))
    (reclaim-graphics-list handles)))

(defun draw-selection-handles-for-connection (connection color)
  (let ((vertices (compute-connection-vertices connection))
	(icon-description (icon-description (second selection-handle-icon))))
    (loop for (x-in-window y-in-window . rest) on vertices by #'cddr
	  as first = t then nil
	  as last = (null rest)
 	  as color* = (if (or (and first (not (loose-end-p (input-end-object connection))))
			      (and last (not (loose-end-p (output-end-object connection)))))
			  'red color)	; FIXME: configurable
	  do (draw-selection-handle icon-description color* x-in-window y-in-window))
    (reclaim-gensym-list vertices)))

;; The usual box, although now in paint mode.
(defun draw-selection-handles-for-text-cell (text-cell color)
  (let ((table? (get-table-for-cell text-cell)))
    #+development
    (unless table?
      (dwarn "Table-less text-cell in draw-selection-handles-for-text-cell: ~s" text-cell))
    (when table?
      (multiple-value-bind (left top right bottom)
	  (get-table-cell-edges table? text-cell)
	(let ((thick (-f selection-highlight-line-width 1))	; Random
	      (tweak (if (and (text-cell-format text-cell)
			      (<=f (text-cell-top-margin (text-cell-format text-cell)) 1))
			 1 0))
	      (color-value (map-color-or-metacolor-to-color-value color)))
	  (paint-rectangle-outline-in-window
	    (x-in-window left)
	    (y-in-window (-f top tweak))
	    (x-in-window right)
	    (y-in-window bottom)
	    color-value thick thick))))))

(defun invalidate-selection-handles (thing image-plane)
  (let ((d (+f selection-handle-radius 1))
	(region (make-empty-region)))
    (on-image-plane-without-drawing (image-plane)
      (cond ((connection-p thing)
	     (let ((vertices (compute-connection-vertices thing)))
	       (loop for (x-in-window y-in-window) on vertices by #'cddr doing
		 (setq region (add-rectangle-to-region (-f x-in-window d) (-f y-in-window d)
						       (+f x-in-window d) (+f y-in-window d)
						       region)))
	       (reclaim-gensym-list vertices)))
	    ((framep thing)
	     (let ((handles (selection-handle-positions thing)))
	       (loop for (name x y) on handles by #'cdddr
		     as x-in-window = (x-in-window x)
		     as y-in-window = (y-in-window y)
		     doing
		 (setq region (add-rectangle-to-region (-f x-in-window d) (-f y-in-window d)
						       (+f x-in-window d) (+f y-in-window d)
						       region)))
	       (reclaim-graphics-list handles)))
	    ((text-cell-p thing)
	     (let ((table? (get-table-for-cell thing)))	; Can be NIL during deletion.
	       (when table?
		 (multiple-value-bind (left top right bottom)
		     (get-table-cell-edges table? thing)
		   ;; FIXME: Inval just the edges, not the interior.
		   (let ((w selection-highlight-line-width))
		     (setq region (add-rectangle-to-region
				    (-f (x-in-window left) w) (-f (y-in-window top) w)
				    (+f (x-in-window right) w) (+f (y-in-window bottom) w)
				    region))))))))
      (let ((current-draw-paper-p nil))
	(invalidate-region-of-image-plane image-plane region))
      (reclaim-region region))))


;;;; Selection Handle Dragging

;; TODO: Abort context if handle becomes invalid. Eg, list of connection deltas changes.

(define-workstation-context drag-handle ()
  :selection-style top-level-with-mouse-tracking-is-selection-style
  :state-variables (target		  ; item-or-items
		     type		  ; Type of handle: connection-vertex, resize, etc.
		     handle		  ; Which "handle" on the item is being dragged
		     image-plane
		     image-plane-serial-number
		     cursor		  ; An image-plane cursor
		     x-in-workspace	  ; Last position
		     y-in-workspace)
  :conc-name t
  :define-enter-context-function t
  :keymap ((<mouse-motion> track-mouse-for-drag-handle)
	   (<mouse-down> finish-drag-handle)
	   (<mouse-up> finish-drag-handle)
	   (<standard-abort-keys> abort-workstation-context)
	   (escape abort-workstation-context)))

(def-structure-method valid-workstation-context-p (drag-handle-state)
  (and (funcall-superior-method drag-handle-state)
       (valid-block-in-workstation-context-p
	 (car-or-atom (drag-handle-state-target drag-handle-state))
	 drag-handle-state)))

(def-structure-method clean-up-workstation-context (drag-handle-state)
  (funcall-superior-method drag-handle-state)
  (clean-up-image-plane-cursor
    (drag-handle-state-image-plane drag-handle-state)
    (drag-handle-state-cursor drag-handle-state)
    (drag-handle-state-image-plane-serial-number drag-handle-state)))

(defun begin-dragging-selection-handle (image-plane mouse-pointer target handle-type handle
					       x-in-workspace y-in-workspace)
  (let* ((color (compute-workspace-foreground-color image-plane))
	 (cursor (case handle-type	; TODO: vertex
		   (resize (create-resize-cursor color handle target))))
	 (state-block
	   (enter-drag-handle-context
	     :target target
	     :handle handle
	     :type handle-type
	     :image-plane image-plane
	     :image-plane-serial-number (serial-number-of-image-plane image-plane)
	     :cursor cursor
	     :x-in-workspace x-in-workspace
	     :y-in-workspace y-in-workspace)))
    (when cursor
      (add-image-plane-cursor image-plane cursor)
      (draw-image-plane-cursor image-plane cursor))
    ;; This ensures we go away if item or image-plane does.
    (add-mouse-pointer-to-guardians-of-workstation-context mouse-pointer state-block)))

(define-event-handler track-mouse-for-drag-handle
    ((state workstation-context-specifics) x-in-window y-in-window)
  (let* ((item-or-items (drag-handle-state-target state))
	 (item (car-or-atom item-or-items))
	 (handle (drag-handle-state-handle state))
	 (handle-type (drag-handle-state-type state))
	 (cursor (drag-handle-state-cursor state))
	 (image-plane (drag-handle-state-image-plane state))
	 (x-in-workspace (x-within-workspace x-in-window image-plane))
	 (y-in-workspace (y-within-workspace y-in-window image-plane))
	 (dx (-f x-in-workspace (drag-handle-state-x-in-workspace state)))
	 (dy (-f y-in-workspace (drag-handle-state-y-in-workspace state))))
    (unless (=f dx dy 0)
      (case handle-type
	(vertex
	 (move-connection-vertex-by item handle dx dy)
	 (setf (drag-handle-state-x-in-workspace state) x-in-workspace
	       (drag-handle-state-y-in-workspace state) y-in-workspace))
	(resize
	 (move-resize-cursor cursor item handle image-plane dx dy))))))

(define-event-handler finish-drag-handle
    ((state workstation-context-specifics) mouse-pointer)
  (track-mouse-for-drag-handle mouse-pointer) ; Update with last point.
  (case (drag-handle-state-type state)
    (vertex)
    (resize
     (resize-items-per-resize-cursor (drag-handle-state-cursor state)
				     (drag-handle-state-handle state)
				     (drag-handle-state-target state)
				     (frame-reference-number-of-workstation-context state))))
  (return-from-current-workstation-context 'drag-handle))


;;;; Resize Cursor

;;; This is an image-plane cursor used when resizing multiple items at once. It
;;; consists of N dotted rectangles, which resize proportionally. Stored coordinates
;;; are in workspace units.

;;; TODO: Arbitrary polypolylines for each item, reflecting its internal structure.

(def-list-structure (resize-cursor (:consing-function graphics-cons)
				   (:optimize t))
    (resize-cursor-x-scale resize-cursor-y-scale resize-cursor-color . resize-cursor-rects))

(defun create-resize-cursor (color corner-being-moved blocks)
  (let ((rects (loop for block in blocks
		     as left = (left-edge-of-block block)
		     as top = (top-edge-of-block block)
		     as right = (right-edge-of-block block)
		     as bottom = (bottom-edge-of-block block)
		     as x = left
		     as y = top
		     as width = (width-of-block block)
		     as height = (height-of-block block)
		     doing
		 ;; Compute coor for fixed corner, given corner being moved. 
		 (case corner-being-moved
		   (top-left
		    (setq x right
			  y bottom
			  width (-f width)
			  height (-f height)))
		   (top-right
		    (setq y bottom
			  height (-f height)))
		   (bottom-left
		    (setq x right
			  width (-f width))))
		     collect (graphics-list x y width height) using graphics-cons)))
    ;; Or, initialize scale relative to unmagnified size?
;    (unmagnified-block-width
;      (or (getfq icon-attributes-plist 'width)
;	  (width-of-icon icon-description)))
;    (unmagnified-block-height
;      (or (getfq icon-attributes-plist 'height)
;	  (height-of-icon icon-description)))
    (make-resize-cursor (allocate-managed-float 1.0)
			(allocate-managed-float 1.0)
			color
			rects)))

(defun resize-cursor-p (cursor)
  (and (consp cursor)
       (managed-float-p (resize-cursor-x-scale cursor))
       (managed-float-p (resize-cursor-y-scale cursor))))

(defun reclaim-resize-cursor (cursor)
  (reclaim-managed-float (resize-cursor-x-scale cursor))
  (reclaim-managed-float (resize-cursor-y-scale cursor))
  (loop for rect in (resize-cursor-rects cursor) doing
    (reclaim-graphics-list rect))
  (reclaim-graphics-list cursor))

(defun draw-resize-cursor (cursor)
  (with-temporary-gensym-float-creation draw-resize-cursor
    (let ((x-scale (managed-float-value (resize-cursor-x-scale cursor)))
	  (y-scale (managed-float-value (resize-cursor-y-scale cursor)))
	  (color-value (map-color-or-metacolor-to-color-value (resize-cursor-color cursor))))
      (loop for (x0 y0 width height) in (resize-cursor-rects cursor)
	    as x1 = (+f x0 (rounde-first (*e x-scale (coerce-to-gensym-float width))))
	    as y1 = (+f y0 (rounde-first (*e y-scale (coerce-to-gensym-float height))))
	    doing
	(draw-dotted-rectangle color-value x0 y0 x1 y1)))))

(defun move-resize-cursor (cursor item handle image-plane dx dy)
  (let ((left (left-edge-of-block item))
	(top (top-edge-of-block item))
	(right (right-edge-of-block item))
	(bottom (bottom-edge-of-block item))
	(gensym-window (gensym-window-for-image-plane image-plane)))
    (multiple-value-setq (left top right bottom)
      (adjust-rectangle-edges handle left top right bottom dx dy))
    (with-temporary-gensym-float-creation track-mouse-for-drag-handle
      (let ((x-scale (maxe 0.0 (/e (coerce-to-gensym-float (-f right left))
				   (coerce-to-gensym-float (width-of-block item)))))
	    (y-scale (maxe 0.0 (/e (coerce-to-gensym-float (-f bottom top))
				   (coerce-to-gensym-float (height-of-block item))))))
	(with-raw-window-transform-and-draw-area (gensym-window)
	  (on-image-plane (image-plane)
	    (with-nested-transform-and-draw-area-of-image-plane-contents? (image-plane)
	      (with-transfer-mode-when-drawing (:xor)
		(draw-resize-cursor cursor)	    ; erase
		(mutate-managed-float-value (resize-cursor-x-scale cursor) x-scale)
		(mutate-managed-float-value (resize-cursor-y-scale cursor) y-scale)
		(draw-resize-cursor cursor))))))))) ; draw

(defun resize-items-per-resize-cursor (cursor corner-being-moved items frame-serial-number)
  (with-temporary-gensym-float-creation resize-items-per-resize-cursor
    (let ((x-scale (managed-float-value (resize-cursor-x-scale cursor)))
	  (y-scale (managed-float-value (resize-cursor-y-scale cursor))))
      (loop for item in items doing
	(when (frame-has-not-been-reprocessed-p item frame-serial-number)
	  (let ((left (left-edge-of-block item))
		(top (top-edge-of-block item))
		(right (right-edge-of-block item))
		(bottom (bottom-edge-of-block item))
		(new-width (rounde-first (*e x-scale (coerce-to-gensym-float (width-of-block item)))))
		(new-height (rounde-first (*e y-scale (coerce-to-gensym-float (height-of-block item))))))
	    (macrolet ((top () `(setq top (-f bottom new-height)))
		       (left () `(setq left (-f right new-width)))
		       (bottom () `(setq bottom (+f top new-height)))
		       (right () `(setq right (+f left new-width))))
	      (case corner-being-moved
		(top-left (top) (left))
		(top-right (top) (right))
		(bottom-left (bottom) (left))
		(bottom-right (bottom) (right))
		(top (top))
		(left (left))
		(bottom (bottom))
		(right (right))))
	    (change-size-per-bounding-rectangle item left top right bottom)
	    (invoke-rules-for-resizement-chaining item 'is-resized-by-the-user)))))))

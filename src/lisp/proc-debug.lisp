
;; -*- Mode: LISP; Syntax: Common-Lisp; Base: 10; Package: AB -*-
(in-package "AB")

;;;; Module PROC-DEBUG

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All rights reserved.

;;; Jim Allard




(declare-forward-reference make-description-box function)	; in QUERIES

(declare-forward-reference disassemble-item-if-appropriate	; in QUERIES
			   function)

(declare-forward-reference execute-computation-instance function) ;  STACK-UTILS
(declare-forward-reference write-byte-code-body function)	; in STACK-UTILS
(declare-forward-reference write-stack-instruction function)	; in STACK-UTILS

(declare-forward-reference get-and-clear-workspace-for-inspect-command function)


;; In G2-BPEL

(declare-forward-reference g2gl-call-invocation-p-function function)



;;;; Procedure Debugging Facilities




;;; Eventually, procedures will need a full debugging environment.  The needs
;;; within this environment include a disassembler; a stack examination
;;; environment with access to calling stack, environment, and disassembled code
;;; with visible program counter pointers; and a procedures stepping facility
;;; for stepping procedure executions.

;;; At first, I'm implementing the disassemblers and graphic stack display
;;; facilities.






;;;; Procedure Stack Trees



;;; The following facility implements a tree display for procedures.  It should
;;; be abstracted and made into a grapher for the whole system.






;;;; Graphical Tree Layout




;;; The graphical tree layout facility provides a tool for displaying directed
;;; graphs as a forest of trees on the G2 user interface.  The function
;;; `graph-frame-hierarchy' takes an item or symbol and functions for returning
;;; the sub-nodes and will graph the specified hierarchy.

;;; The graph-node-of-graphed-thing hash table is used by the tree grapher to
;;; determine if a frame or symbol has already been represented in the tree.

(defvar current-graph-layout-hashing-function nil)

(defmacro graph-layout-hash (graph-element)
  `(funcall-symbol
     (or current-graph-layout-hashing-function 'sxhashw) ; sxhashw safest -- handles wide strings
     ,graph-element))

(def-hash-table graph-node-of-graphed-thing
		:hash-function-or-macro graph-layout-hash)

(defconser graph-layout)




;;; The structure `graph-display' is used to store the node representations of a
;;; graph which is being generated.

(def-structure (graph-display
		 (:constructor make-graph-display
		  (graph-display-root-item
		    graph-display-orientation
		    graph-display-vertical-spacing
		    graph-display-horizontal-spacing
		    graph-display-children-function
		    graph-display-extra-argument
		    graph-display-short-rep-function
		    graph-display-hash-function)))
  graph-display-orientation			; vertical or horizontal
  graph-display-root-item
  (graph-display-root nil :reclaimer reclaim-graph-node-function)
  (graph-display-lookup-table
    (make-graph-node-of-graphed-thing)
    :reclaimer reclaim-graph-node-of-graphed-thing)
  graph-display-vertical-spacing
  graph-display-horizontal-spacing
  graph-display-children-function
  graph-display-extra-argument
  graph-display-short-rep-function
  graph-display-hash-function
  (graph-display-extra-non-sibling-spacing 10)
  (graph-display-left-most-edge 0)
  (graph-display-right-most-edge 0)
  (graph-display-top-edge 0)
  (graph-display-bottom-edge 0)
  (graph-display-depth 0)
  (graph-display-maximum-height-array nil :reclaimer reclaim-if-managed-array)
  (graph-display-update-root nil)
  (graph-display-update-lookup-table
    (make-graph-node-of-graphed-thing)
    :reclaimer reclaim-graph-node-of-graphed-thing)
  (graph-display-workspace nil))




;;; The `graph-node' structure is used to represent a node with a graph being
;;; generated.

(def-structure (graph-node
		 (:constructor make-graph-node
		  (graph-node-item
		    graph-node-superior graph-node-depth
		    graph-node-short-representation graph-node-graph)))
  graph-node-graph
  graph-node-item
  graph-node-short-representation
  graph-node-superior
  (graph-node-children nil :reclaimer reclaim-graph-node-list)
  (graph-node-maximum-child-depth 0)
  (node-to-left nil)
  (node-to-right nil)
  graph-node-depth
  (graph-node-surrogate? nil)
  (other-graph-nodes-for-item nil :reclaimer reclaim-graph-layout-list)
  (graph-node-x-position 0)
  (graph-node-y-position 0)
  (graph-node-subgraph-isomorphic-cached? nil)
  (graph-node-original-node-in-update nil))

(defun reclaim-graph-node-function (graph-node)
  (reclaim-graph-node graph-node))

(defun reclaim-graph-node-list (graph-nodes)
  (when graph-nodes
    (reclaim-graph-node (car graph-nodes))
    (loop for trailer-cons = graph-nodes then graph-node-cons
	  for graph-node-cons on (cdr graph-nodes)
	  do
      (reclaim-graph-node (car graph-node-cons))
	  finally
	    (reclaim-graph-layout-list-given-tail
	      graph-nodes trailer-cons))))




;;; The class `dynamic-temporary-workspace' is used to present displays which
;;; need some clean up when the workspace is deleted.  This class of temporary
;;; workspace has an extra slot called associated-dynamic-workspace-structure.
;;; This structure type must be a structure which includes the structure
;;; dynamic-workspace-associated-structure.  This will add the slot
;;; `reclaimer-for-dynamic-workspace-associated-structure'.  This slot should
;;; contain a symbol which names a function to be called to reclaim the given
;;; structure.  This definition is made so that arbitrary types of dynamic
;;; displays may be made using this workspace type.

(def-class (dynamic-temporary-workspace temporary-workspace)
  (associated-dynamic-structure nil (system) (vector-slot)))

(def-structure (dynamic-workspace-associated-structure)
  (reclaimer-for-dynamic-workspace-associated-structure nil))

(def-slot-value-reclaimer associated-dynamic-structure (value)
  (let ((structure-reclaimer?
	  (reclaimer-for-dynamic-workspace-associated-structure value)))
    (when structure-reclaimer?
      (funcall-symbol structure-reclaimer? value))))




;;; The macro `graph-node-siblings-p' takes two graph-nodes and returns whether
;;; or not they are children of the same parent.

(defmacro graph-node-siblings-p (graph-node-1 graph-node-2)
  `(eq (graph-node-superior ,graph-node-1)
       (graph-node-superior ,graph-node-2)))




;;; The function `represented-in-graph-display-p' takes a thing and a graph
;;; display.  This function will return whether or not the given thing is
;;; registered in the hash table of items currently shown for the given
;;; graph-display.

(defun represented-in-graph-display-p (thing graph-display)
  (let ((current-graph-layout-hashing-function
	  (graph-display-hash-function graph-display))
	(hash-table (graph-display-lookup-table graph-display)))
    (if (get-graph-node-of-graphed-thing thing hash-table)
	t
	nil)))




;;; The function `graph-item-hierarchy' takes an item, a function to call to
;;; retrieve a gensym cons list of children of the item, any extra argument to
;;; pass to that function, and a function to call on items to be graphed which
;;; returns the actual frame which will be presented on a temporary workspace.
;;; This function displays a temporary workspace on the screen and then returns
;;; an instance of the graph-display structure.  This structure can be
;;; immediately reclaimed without affecting the display, but must be retained
;;; and used again if mutations to the display will be requested via
;;; `mutate-item-graph' (yet to be developed).

(defmacro graph-frame-hierarchy
    (item children-function extra-argument? short-representation-function
	     &optional hash-function orientation vertical-spacing
	     horizontal-spacing pane-for-workspace-display? class-of-workspace
	     workspace? left-edge-for-graph? top-edge-for-graph?)
  `(graph-frame-hierarchy-function
     ,item ,children-function ,extra-argument? ,short-representation-function
     (or (identity ,hash-function) 'sxhashw) (or (identity ,orientation) 'vertical)
     (or (identity ,vertical-spacing) 50) (or (identity ,horizontal-spacing) 50)
     ,pane-for-workspace-display? (or (identity ,class-of-workspace) 'temporary-workspace)
     ,workspace? ,left-edge-for-graph? ,top-edge-for-graph?))

;; Identity used just to gag the ACL compiler, boasting about unreachable clause
;; at the end if a constant is passed in! -mhd, 6/15/00


(defun graph-frame-hierarchy-function
       (item children-function extra-argument? short-representation-function
	     hash-function orientation vertical-spacing
	     horizontal-spacing pane-for-workspace-display? class-of-workspace
	     workspace? left-edge-for-graph? top-edge-for-graph?)
  (let ((current-graph-layout-hashing-function hash-function)
	(graph (make-graph-display
		 item orientation vertical-spacing horizontal-spacing
		 children-function
		 extra-argument?
		 short-representation-function
		 hash-function))
	(workspace
	  (or workspace?
	      (make-workspace class-of-workspace nil nil nil nil nil))))
    (setf (graph-display-workspace graph) workspace)
    (represent-items-in-graph
      graph
      item children-function extra-argument?
      short-representation-function)
    (determine-node-positions
      graph left-edge-for-graph? top-edge-for-graph?)
    (display-graph-on-workspace graph)
    (when pane-for-workspace-display?
      (put-workspace-on-pane
	workspace
	pane-for-workspace-display?
	'left 'top t))
    graph))




;;; The function `represent-items-in-graph' takes a newly created graph object,
;;; a root to be graphed, and a children function, an extra-argument for the
;;; children function, and a function for producing a short representation frame
;;; of the items to be graphed.  This function will build a tree of graph-node
;;; structures, and store it into the graph object.  This function does not lay
;;; out node positions, it merely builds the tree structure.

(defparameter original-graph-depth 32)

(defun represent-items-in-graph
    (graph item children-function extra-argument? short-rep-function)
  (let ((node-table (graph-display-lookup-table graph))
	(row-array (allocate-managed-array original-graph-depth))
	root-node)
    (multiple-value-setq (root-node row-array)
      (make-node-for-item
	item children-function extra-argument? short-rep-function
	node-table row-array nil 0 graph))
    (setf (graph-display-root graph) root-node)
    (let ((maximum-height-array (allocate-managed-array (graph-display-depth graph))))
      (setf (graph-display-maximum-height-array graph) maximum-height-array)
      (initialize-graph-display-maximum-height-array
	maximum-height-array row-array (graph-display-orientation graph)))
    (reclaim-managed-array row-array)))




;;; The function `make-node-for-item' is used to make a new graph-node structure
;;; for an item to be represented in a graph.  This function recurses to produce
;;; graph-node structures for the children of the given item, but it always
;;; checks if this node is represented in the graph already before recursing so
;;; that it will not get stuck in loops within cyclic directed graphs given to
;;; this function.

(defun make-node-for-item
    (item children-function extra-argument? short-rep-function
	  node-table row-array superior depth graph)
  (let* ((old-length (managed-array-length row-array))
	 (new-node (make-graph-node
		     item superior depth
		     (funcall-symbol short-rep-function item)
		     graph))
	 (existing-node? (set-graph-node-of-graphed-thing-if-no-entry
			   item node-table new-node)))
    (declare (type fixnum old-length))
    (when (>=f depth old-length)
      (setq row-array (adjust-managed-array
			row-array
			(+f old-length original-graph-depth))))
    (let ((node-to-left? (managed-svref row-array depth)))
      ;; node-to-left? variable used to be bound before the adjust-managed-array, resulting in
      ;; array reference error when array must be grown. -pga, 2/14/96
      (when node-to-left?
	(setf (node-to-right node-to-left?) new-node)
	(setf (node-to-left new-node) node-to-left?))
      (when (>=f depth (graph-display-depth graph))
	(setf (graph-display-depth graph) (+f depth 1)))
      (setf (graph-node-depth new-node) depth)
      (setf (managed-svref row-array depth) new-node)
      (cond ((neq existing-node? new-node)
	     (setf (graph-node-surrogate? new-node) existing-node?)
	     (setf (other-graph-nodes-for-item existing-node?)
		   (graph-layout-cons
		     new-node
		     (other-graph-nodes-for-item existing-node?))))
	    (t
	     (loop with new-depth = (+f depth 1)
		   with children = (funcall-symbol
				     children-function
				     item extra-argument?)
		   with maximum-child-depth fixnum = 0
		   for child in children
		   with child-node
		   do
	       (multiple-value-setq (child-node row-array)
		 (make-node-for-item
		   child children-function extra-argument?
		   short-rep-function
		   node-table row-array
		   new-node new-depth graph))
		   collect child-node into child-nodes using graph-layout-cons
		   do
	       (setq maximum-child-depth
		     (maxf maximum-child-depth
			   (+f (graph-node-maximum-child-depth
				 child-node)
			       1)))
		   finally
		     (reclaim-gensym-list children)
		     (setf (graph-node-maximum-child-depth new-node)
			   maximum-child-depth)
		     (setf (graph-node-children new-node) child-nodes))))
      (values new-node row-array))))




;;; The special variable `graph-display-changed-during-update?' is used to
;;; record whether or not an actual graphic change occurred during the update.

(defvar graph-display-changed-during-update? nil)




;;; The function `update-graph-display' takes a previously made graph whose tree
;;; may have changed somewhat since it was graphed.  This function will traverse
;;; the new item hierarchy, creating a new node hierarchy.  For each new node,
;;; it will lookup any old node from the previous hierarchy.  Where it is found,
;;; this node will be stored on the new node.  If it is not found, then new
;;; short-representations and other data will be stored into the new node.  This
;;; functions returns T when the display actually changes during the update,
;;; else it returns NIL.

(defun update-graph-display (graph)
  (let ((current-graph-layout-hashing-function
	  (graph-display-hash-function graph))
	(graph-display-changed-during-update? nil))
    (update-graph-display-nodes graph)
    (determine-node-positions graph)
    (update-display-of-graph-on-workspace graph)
    ;; Clear or reclaim old lookup table and graph-nodes.
    (reclaim-graph-node (graph-display-update-root graph))
    (setf (graph-display-update-root graph) nil)
    (clear-graph-node-of-graphed-thing
      (graph-display-update-lookup-table graph))
;    (terminal-pause 100 "Update finished")
    graph-display-changed-during-update?))

(defun update-graph-display-nodes (graph)
  (let* ((node-table (graph-display-update-lookup-table graph))
	 (row-array (allocate-managed-array original-graph-depth))
	 (item (graph-display-root-item graph))
	 (children-function (graph-display-children-function graph))
	 (extra-argument? (graph-display-extra-argument graph))
	 (short-rep-function (graph-display-short-rep-function graph)))
    (setf (graph-display-update-lookup-table graph)
	  (graph-display-lookup-table graph))
    (setf (graph-display-lookup-table graph) node-table)
    (setf (graph-display-update-root graph) (graph-display-root graph))
    (setf (graph-display-root graph) nil)
;    (cerror "Continue" "Ready to make new graph-node hierarchy.")
    (setf (graph-display-root graph)
	  (make-or-update-node-for-item
	    item children-function extra-argument? short-rep-function
	    node-table row-array nil 0 graph))
    (let ((maximum-height-array (allocate-managed-array (graph-display-depth graph))))
      (setf (graph-display-maximum-height-array graph) maximum-height-array)
      (initialize-graph-display-maximum-height-array
	maximum-height-array row-array (graph-display-orientation graph)))
    (reclaim-managed-array row-array)))



;;; The function `previous-actual-graph-node' takes a new graph node and an old
;;; graph node for the same item from the previous version of the graph display.
;;; This function should return the one of the graph represntations of this item
;;; within in the old graph which has the same parent item, or else it should
;;; return NIL.  The given node is the representation of the item which has an
;;; expanded children tree.  The correct old node could be the given node, or
;;; else one of the other-graph-nodes-for-item of the given node.  (Note that
;;; the returned node really represents the link from its parent to this item,
;;; and the identity function should operate on this aspect of the
;;; representation.)

(defun previous-actual-graph-node (new-node previous-node-version)
  (let* ((superior-graph-node? (graph-node-superior new-node))
	 (superior-item?
	   (when superior-graph-node?
	     (graph-node-item superior-graph-node?)))
	 (previous-superior-graph-node?
	   (graph-node-superior previous-node-version))
	 (previous-superior-item?
	   (when previous-superior-graph-node?
	     (graph-node-item previous-superior-graph-node?))))
    (if (eq superior-item? previous-superior-item?)
	previous-node-version
	(loop for previous-node
		  in (other-graph-nodes-for-item previous-node-version)
		 do
	  (setq previous-superior-graph-node? (graph-node-superior previous-node))
	  (when (and previous-superior-graph-node?
		     (eq superior-item?
			 (graph-node-item previous-superior-graph-node?)))
	    (return previous-node))))))




;;; The function `make-or-update-node-for-item' is used to make a new graph-node
;;; structure for an item to be represented in a graph.  This function recurses
;;; to produce graph-node structures for the children of the given item, but it
;;; always checks if this node is represented in the graph already before
;;; recursing so that it will not get stuck in loops within cyclic directed
;;; graphs given to this function.

(defun make-or-update-node-for-item
       (item children-function extra-argument? short-rep-function
	node-table row-array superior depth graph)
  (let* ((old-length (managed-array-length row-array))
	 (new-node (make-graph-node item superior depth nil graph))
	 (existing-update-node?
	   (set-graph-node-of-graphed-thing-if-no-entry
	     item node-table new-node))
	 (previous-expanded-graph-node?
	   (get-graph-node-of-graphed-thing
	     item
	     (graph-display-update-lookup-table
	       graph)))
	 (previous-actual-graph-node?
	   (when previous-expanded-graph-node?
	     (previous-actual-graph-node
	       new-node previous-expanded-graph-node?)))
	 (node-to-left? (managed-svref row-array depth)))
    (when (>=f depth old-length)
      (setq row-array
	    (adjust-managed-array
	      row-array
	      (+f old-length original-graph-depth))))
    (if previous-actual-graph-node?
	(progn 
	  (setf (graph-node-original-node-in-update new-node)
		previous-actual-graph-node?)
	  (setf (graph-node-short-representation new-node)
		(graph-node-short-representation previous-actual-graph-node?))
	  (setf (graph-node-short-representation previous-actual-graph-node?)
		nil))
	(setf (graph-node-short-representation new-node)
	      (funcall-symbol short-rep-function item)))
    (when node-to-left?
      (setf (node-to-right node-to-left?) new-node)
      (setf (node-to-left new-node) node-to-left?))
    (when (>=f depth (graph-display-depth graph))
      (setf (graph-display-depth graph) (+f depth 1)))
    (setf (graph-node-depth new-node) depth)
    (setf (managed-svref row-array depth) new-node)
    (cond ((neq existing-update-node? new-node)
	   (setf (graph-node-surrogate? new-node) existing-update-node?)
	   (setf (other-graph-nodes-for-item existing-update-node?)
		 (graph-layout-cons
		   new-node
		   (other-graph-nodes-for-item existing-update-node?))))
	  (t
	   (loop with new-depth = (+f depth 1)
		 with children = (funcall-symbol
				   children-function
				   item extra-argument?)
		 with maximum-child-depth fixnum = 0
		 for child in children
		 for child-node
		     = (make-or-update-node-for-item
			 child children-function extra-argument?
			 short-rep-function
			 node-table row-array
			 new-node new-depth graph)
		 collect child-node into child-nodes using graph-layout-cons
		 do
	     (setq maximum-child-depth
		   (maxf maximum-child-depth
			 (+f (graph-node-maximum-child-depth
			       child-node)
			     1)))
		 finally
		   (reclaim-gensym-list children)
		   (setf (graph-node-maximum-child-depth new-node)
			 maximum-child-depth)
		   (setf (graph-node-children new-node) child-nodes))))
    new-node))




;;; The function `initialize-graph-display-maximum-height-array' is called to
;;; initialize the array used in laying out the depth of a graphed array.  Note
;;; that the maximum-height-array actually holds the maximum size in the
;;; direction of the depth of displayed tree, which will be either the height or
;;; the width depending on whether the graph is vertical or horizontal,
;;; respectively.

(defun initialize-graph-display-maximum-height-array
       (maximum-height-array row-array orientation)
  (loop for row-number from 0 below (managed-array-length maximum-height-array)
	do
    (loop with maximum-height fixnum = 0
	  for node = (managed-svref row-array row-number)
		   then (node-to-left node)
	  while node
	  for short-rep = (graph-node-short-representation node)
	  do
      (if (eq orientation 'vertical)
	  (setq maximum-height
		(maxf maximum-height (height-of-block short-rep)))
	  (setq maximum-height
		(maxf maximum-height (width-of-block short-rep))))
	  finally (setf (managed-svref maximum-height-array row-number)
			maximum-height))))

(declare-function-type maximum-graph-node-extent-to-right (t) (t))




;;; The function `determine-node-positions' is used to set the X and Y
;;; coordinates of the graph-node structures already created in a graph object
;;; by the function represent-items-in-graph.  This function does not display
;;; the graph or lay out connections between the nodes, it merely sets the slots
;;; of the graph-node structures to hold the correct X and Y coordinates.

(defun determine-node-positions
       (graph &optional left-edge-for-graph? top-edge-for-graph?)
  (let ((root (graph-display-root graph)))
    (setf (graph-display-left-most-edge graph) 0)
    (setf (graph-display-right-most-edge graph) 0)
    (setf (graph-display-top-edge graph) 0)
    (setf (graph-display-bottom-edge graph) 0)
    (cond ((eq (graph-display-orientation graph) 'vertical)
	   (position-node-vertically root)
	   (when (/=f (graph-node-x-position root) 0)
	     (shift-graph-node-and-children-to-right
	       root graph (-f (graph-node-x-position root))))
	   (setf (graph-display-left-most-edge graph)
		 (-f (maximum-graph-node-extent-to-left root) 1))
	   (setf (graph-display-right-most-edge graph)
		 (+f (maximum-graph-node-extent-to-right root) 1)))
	  (t
	   (position-node-horizontally root)
	   (when (/=f (graph-node-y-position root) 0)
	     (shift-graph-node-and-children-toward-bottom
	       root graph (-f (graph-node-y-position root))))
	   (setf (graph-display-top-edge graph)
		 (-f (maximum-graph-node-extent-to-top root) 1))
	   (setf (graph-display-bottom-edge graph)
		 (+f (maximum-graph-node-extent-to-bottom root) 1))))
    ;; New:   (MHD 6/20/90)
    (cond
      ((or left-edge-for-graph? top-edge-for-graph?)
       (if left-edge-for-graph?
	   (shift-graph-node-and-children-to-right
	     root graph
	     (-w left-edge-for-graph?
		 (graph-display-left-most-edge graph))))
       (if top-edge-for-graph?
	   (shift-graph-node-and-children-toward-bottom
	     root graph
	     (-w top-edge-for-graph?
		 (graph-display-top-edge graph))))
       (setf (graph-display-left-most-edge graph)
	     (-f (maximum-graph-node-extent-to-left root) 1))
       (setf (graph-display-right-most-edge graph)
	     (+f (maximum-graph-node-extent-to-right root) 1))
       (setf (graph-display-top-edge graph)
	     (-f (maximum-graph-node-extent-to-top root) 1))
       (setf (graph-display-bottom-edge graph)
	     (+f (maximum-graph-node-extent-to-bottom root) 1))))
    nil))




;;; The function `maximum-graph-node-extent-to-right' takes a graph-node, and
;;; returns the furthest to the right that it or any of its children extend.
;;; Note that we can't just check the last child, in that the subtree of another
;;; child may be very wide and go further to the right than the last child.

(defun maximum-graph-node-extent-to-right (graph-node)
  (let ((right-edge (+f (graph-node-x-position graph-node)
			(width-of-block
			  (graph-node-short-representation graph-node)))))
    (declare (type fixnum right-edge))
    (loop for kid in (graph-node-children graph-node) do
      (setq right-edge
	    (maxf right-edge (maximum-graph-node-extent-to-right kid))))
    right-edge))




;;; The function `maximum-graph-node-extent-to-left' takes a graph-node, and
;;; returns the furthest to the left that it or any of its children extend.

(defun maximum-graph-node-extent-to-left (graph-node)
  (let ((left-edge (graph-node-x-position graph-node)))
    (declare (type fixnum left-edge))
    (loop for kid in (graph-node-children graph-node)
	  for kid-left fixnum = (maximum-graph-node-extent-to-left kid) do
      (if (<f kid-left left-edge)
	  (setq left-edge kid-left)))
    left-edge))




;;; The function `maximum-graph-node-extent-to-bottom' takes a graph-node, and
;;; returns the furthest to the bottom that it or any of its children extend.
;;; Note that we can't just check the last child, in that the subtree of another
;;; child may be very wide and go further to the right than the last child.

(defun maximum-graph-node-extent-to-bottom (graph-node)
  (let ((bottom-edge (+f (graph-node-y-position graph-node)
			 (height-of-block
			   (graph-node-short-representation graph-node)))))
    (declare (type fixnum bottom-edge))
    (loop for kid in (graph-node-children graph-node) do
      (setq bottom-edge
	    (maxf bottom-edge (maximum-graph-node-extent-to-bottom kid))))
    bottom-edge))




;;; The function `maximum-graph-node-extent-to-top' takes a graph-node, and
;;; returns the furthest toward the top that it or any of its children extend.

(defun maximum-graph-node-extent-to-top (graph-node)
  (let ((top-edge (graph-node-y-position graph-node)))
    (declare (type fixnum top-edge))
    (loop for kid in (graph-node-children graph-node)
	  for kid-top fixnum = (maximum-graph-node-extent-to-top kid) do
      (if (<f kid-top top-edge)
	  (setq top-edge kid-top)))
    top-edge))




;;; The function `position-node-vertically' is called to determine the X and Y
;;; coordinates of a single graph-node structure within a graph-display.  

(defun position-node-vertically (graph-node)
  (let* ((graph (graph-node-graph graph-node))
	 (short-rep (graph-node-short-representation graph-node))
	 (depth (graph-node-depth graph-node))
	 (superior-node? (graph-node-superior graph-node))
	 (y-position
	   (if superior-node?
	       (+f (graph-node-y-position superior-node?)
		   (managed-svref
		     (graph-display-maximum-height-array graph)
		     (-f depth 1))
		   (graph-display-vertical-spacing graph))
	       (graph-display-top-edge graph)))
	 (kids (graph-node-children graph-node)))
    (setf (graph-node-y-position graph-node) y-position)
    (cond (kids
	   (loop with first-kid = (first kids)
		 for kid in kids
		 do
	     (position-node-vertically kid)
	     (unless (eq kid first-kid)
	       (pack-graph-node-to-left kid)))
	   (let* ((left-edge (graph-node-x-position (first kids)))
		  (last-kid (car (last kids)))
		  (right-edge (+f (graph-node-x-position last-kid)
				  (width-of-block
				    (graph-node-short-representation
				      last-kid)))))
	     (setf (graph-node-x-position graph-node)
		   (-f (+f left-edge (halff (-f right-edge left-edge)))
		       (halff (width-of-block short-rep))))
	     (when (<f (graph-node-x-position graph-node)
		       (graph-display-left-most-edge graph))
	       (setf (graph-display-left-most-edge graph)
		     (graph-node-x-position graph-node)))
	     (when (>f (+f (graph-node-x-position graph-node)
			   (width-of-block short-rep))
		       (graph-display-right-most-edge graph))
	       (setf (graph-display-right-most-edge graph)
		     (+f (graph-node-x-position graph-node)
			 (width-of-block short-rep))))))
	  (t
	   (let ((node-to-left? (node-to-left graph-node)))
	     (setf (graph-node-x-position graph-node)
 		   ;; If the graph is empty so far, place first node against
		   ;; left-most-edge.
		   (if (=f (graph-display-right-most-edge graph)
			   (graph-display-left-most-edge graph))
		       (graph-display-left-most-edge graph)
		       (+f (graph-display-right-most-edge graph)
			   (graph-display-horizontal-spacing graph)
			   (if (and node-to-left?
				    (not (graph-node-siblings-p
					   graph-node
					   node-to-left?)))
			       (graph-display-extra-non-sibling-spacing graph)
			       0)))))
	   (setf (graph-display-right-most-edge graph)
		 (+f (graph-node-x-position graph-node)
		     (width-of-block short-rep)))
	   (when (>f (+f y-position (height-of-block short-rep))
		     (graph-display-bottom-edge graph))
	     (setf (graph-display-bottom-edge graph)
		   (+f y-position (height-of-block short-rep))))))))

(defun shift-graph-node-and-children-to-right (graph-node graph shift-amount)
  (let ((new-x (incff (graph-node-x-position graph-node) shift-amount)))
    (loop for kid in (graph-node-children graph-node)
	  do
      (shift-graph-node-and-children-to-right kid graph shift-amount))
    (if (>f shift-amount 0)
	(let ((rightmost-extent
		(+f new-x (width-of-block (graph-node-short-representation
					    graph-node)))))
	  (when (>f rightmost-extent (graph-display-right-most-edge graph))
	    (setf (graph-display-right-most-edge graph) rightmost-extent)))
	(when (<f new-x (graph-display-left-most-edge graph))
	  (setf (graph-display-left-most-edge graph) new-x)))
    nil))

(defun shift-graph-node-and-children-toward-bottom (graph-node graph shift-amount)
  (let ((new-y (incff (graph-node-y-position graph-node) shift-amount)))
    (loop for kid in (graph-node-children graph-node)
	  do
      (shift-graph-node-and-children-toward-bottom kid graph shift-amount))
    (if (>f shift-amount 0)
	(let ((bottommost-extent
		(+f new-y (height-of-block
			    (graph-node-short-representation graph-node)))))
	  (when (>f bottommost-extent (graph-display-bottom-edge graph))
	    (setf (graph-display-bottom-edge graph) bottommost-extent)))
	(when (<f new-y (graph-display-top-edge graph))
	  (setf (graph-display-top-edge graph) new-y)))
    nil))

(defun pack-graph-node-to-left (graph-node)
  (let ((shift-amount? (graph-node-freedom-to-shift-left? graph-node 0)))
    (when shift-amount?
      (shift-graph-node-and-children-to-right
	graph-node (graph-node-graph graph-node) (-f shift-amount?)))))

(defun pack-graph-node-to-top (graph-node)
  (let ((shift-amount? (graph-node-freedom-to-shift-up? graph-node 0)))
    (when shift-amount?
      (shift-graph-node-and-children-toward-bottom
	graph-node (graph-node-graph graph-node) (-f shift-amount?)))))




;;; The function `graph-node-freedom-to-shift-left?' takes a graph-node and a
;;; number of levels to ignore, and returns two values.  The first value is
;;; either NIL, or the number of workstation units that this node and its
;;; children can move to the left, and the second value is the depth of the
;;; search used to find this value.  If there are no nodes to the left of this
;;; node, then the result for this node and all of its children will be NIL.  If
;;; there are nodes to the left, the freedom to left is the difference between
;;; the x-position of this node and the right edge of the node to left, minus
;;; the graph horizontal spacing.

(defun graph-node-freedom-to-shift-left? (graph-node levels-to-ignore)
  (declare (type fixnum levels-to-ignore))
  (let ((maximum-child-depth (graph-node-maximum-child-depth graph-node)))
    (declare (type fixnum maximum-child-depth))
    (cond ((>f levels-to-ignore maximum-child-depth)
	   (values nil (+f maximum-child-depth 1)))
	  ((>f levels-to-ignore 0)
	   (loop with freedom? = nil
		 with kid-levels-to-ignore fixnum = (-f levels-to-ignore 1)
		 with depth-seen fixnum = 0
		 with child-freedom? = nil
		 with child-depth fixnum = 0
		 for kid in (graph-node-children graph-node)
		 do
	     (multiple-value-setq (child-freedom? child-depth)
	       (graph-node-freedom-to-shift-left?
		 kid (maxf depth-seen kid-levels-to-ignore)))
	     (when (>f child-depth depth-seen)
	       (setq depth-seen child-depth))
	     (when (and child-freedom?
			(or (null freedom?)
			    (<f child-freedom? freedom?)))
	       (setq freedom? child-freedom?))
		 finally
		   (return (values freedom? (+f depth-seen 1)))))
	  (t
	   (let ((node-to-left? (node-to-left graph-node))
		 (graph-display (graph-node-graph graph-node)))
	     (if node-to-left?
		 (loop with short-representation-to-left =
			 (graph-node-short-representation node-to-left?)
		       with freedom fixnum =
			 (-f (graph-node-x-position graph-node)
			     (+f (graph-node-x-position node-to-left?)
				 (width-of-block short-representation-to-left))
			     (graph-display-horizontal-spacing
			       graph-display)
			     (if (graph-node-siblings-p
				   graph-node node-to-left?)
				 0
				 (graph-display-extra-non-sibling-spacing
				   graph-display)))
		       with depth-seen fixnum = 0
		       with child-freedom? = nil
		       with child-depth fixnum = 0
		       for kid in (graph-node-children graph-node)
		       do
		   (multiple-value-setq (child-freedom? child-depth)
		     (graph-node-freedom-to-shift-left? kid depth-seen))
		   (when (>f child-depth depth-seen)
		     (setq depth-seen child-depth))
		   (when (and child-freedom? (<f child-freedom? freedom))
		     (setq freedom child-freedom?))
		       finally
			 (return (values freedom (+f depth-seen 1))))
		 (values nil (+f maximum-child-depth 1))))))))




;;; The function `graph-node-freedom-to-shift-up?' takes a graph-node and a
;;; number of levels to ignore, and returns two values.  The first value is
;;; either NIL, or the number of workstation units that this node and its
;;; children can move to the up, and the second value is the depth of the search
;;; used to find this value.  If there are no nodes above this node, then the
;;; result for this node and all of its children will be NIL.  If there are
;;; nodes above, the freedom above is the difference between the y-position of
;;; this node and the bottom edge of the node above, minus the graph vertical
;;; spacing.

(defun graph-node-freedom-to-shift-up? (graph-node levels-to-ignore)
  (declare (type fixnum levels-to-ignore))
  (let ((maximum-child-depth (graph-node-maximum-child-depth graph-node)))
    (declare (type fixnum maximum-child-depth))
    (cond ((>f levels-to-ignore maximum-child-depth)
	   (values nil (+f maximum-child-depth 1)))
	  ((>f levels-to-ignore 0)
	   (loop with freedom? = nil
		 with kid-levels-to-ignore fixnum = (-f levels-to-ignore 1)
		 with depth-seen fixnum = 0
		 with child-freedom? = nil
		 with child-depth fixnum = 0
		 for kid in (graph-node-children graph-node)
		 do
	     (multiple-value-setq (child-freedom? child-depth)
	       (graph-node-freedom-to-shift-up?
		 kid (maxf depth-seen kid-levels-to-ignore)))
	     (when (>f child-depth depth-seen)
	       (setq depth-seen child-depth))
	     (when (and child-freedom?
			(or (null freedom?)
			    (<f child-freedom? freedom?)))
	       (setq freedom? child-freedom?))
		 finally
		   (return (values freedom? (+f depth-seen 1)))))
	  (t
	   ;; Note that node to left really means node above, since we are laying
	   ;; out the graph horizontally.
	   (let ((node-to-left? (node-to-left graph-node))
		 (graph-display (graph-node-graph graph-node)))
	     (if node-to-left?
		 (loop with short-representation-to-left =
			 (graph-node-short-representation node-to-left?)
		       with freedom fixnum =
			 (-f (graph-node-y-position graph-node)
			     (+f (graph-node-y-position node-to-left?)
				 (height-of-block short-representation-to-left))
			     (graph-display-vertical-spacing
			       (graph-node-graph graph-node))
			     (if (graph-node-siblings-p graph-node node-to-left?)
				 0
				 (graph-display-extra-non-sibling-spacing
				   graph-display)))
		       with depth-seen fixnum = 0
		       with child-freedom? = nil
		       with child-depth fixnum = 0
		       for kid in (graph-node-children graph-node)
		       do
		   (multiple-value-setq (child-freedom? child-depth)
		     (graph-node-freedom-to-shift-up? kid depth-seen))
		   (when (>f child-depth depth-seen)
		     (setq depth-seen child-depth))
		   (when (and child-freedom? (<f child-freedom? freedom))
		     (setq freedom child-freedom?))
		       finally
			 (return (values freedom (+f depth-seen 1))))
		 (values nil (+f (graph-node-maximum-child-depth graph-node) 1))))))))




;;; The function `position-node-horizontally' is called to determine the X and Y
;;; coordinates of a single graph-node structure within a graph-display, when
;;; the layout has the root on the left with children to the right, and children
;;; laid out with first at the top and last toward the bottom.

(defun position-node-horizontally (graph-node)
  (let* ((graph (graph-node-graph graph-node))
	 (short-rep (graph-node-short-representation graph-node))
	 (depth (graph-node-depth graph-node))
	 (superior-node? (graph-node-superior graph-node))
	 (x-position
	   (if superior-node?
	       (+f (graph-node-x-position superior-node?)
		   (managed-svref
		     (graph-display-maximum-height-array graph)
		     (-f depth 1))
		   (graph-display-horizontal-spacing graph))
	       (graph-display-left-most-edge graph)))
	 (kids (graph-node-children graph-node)))
    (setf (graph-node-x-position graph-node) x-position)
    (cond (kids
	   (loop with first-kid = (first kids)
		 for kid in kids
		 do
	     (position-node-horizontally kid)
	     (unless (eq kid first-kid)
	       (pack-graph-node-to-top kid)))
	   (let* ((top-edge (graph-node-y-position (first kids)))
		  (last-kid (car (last kids)))
		  (bottom-edge (+f (graph-node-y-position last-kid)
				   (height-of-block
				     (graph-node-short-representation
				       last-kid)))))
	     (setf (graph-node-y-position graph-node)
		   (-f (+f top-edge (halff (-f bottom-edge top-edge)))
		       (halff (height-of-block short-rep))))
	     (when (<f (graph-node-y-position graph-node)
		       (graph-display-top-edge graph))
	       (setf (graph-display-top-edge graph)
		     (graph-node-y-position graph-node)))
	     (when (>f (+f (graph-node-y-position graph-node)
			   (height-of-block short-rep))
		       (graph-display-bottom-edge graph))
	       (setf (graph-display-bottom-edge graph)
		     (+f (graph-node-y-position graph-node)
			 (height-of-block short-rep))))))
	  (t
	   ;; If the graph is empty so far, place first node against top edge.
	   (let ((node-to-left? (node-to-left graph-node)))
	     (setf (graph-node-y-position graph-node)
		   (if (=f (graph-display-top-edge graph)
			   (graph-display-bottom-edge graph))
		       (graph-display-top-edge graph)
		       (+f (graph-display-bottom-edge graph)
			   (graph-display-vertical-spacing graph)
			   (if (and node-to-left?
				    (not (graph-node-siblings-p graph-node node-to-left?)))
			       (graph-display-extra-non-sibling-spacing graph)
			       0)))))
	   (setf (graph-display-bottom-edge graph)
		 (+f (graph-node-y-position graph-node)
		     (height-of-block short-rep)))
	   (when (>f (+f x-position (width-of-block short-rep))
		     (graph-display-right-most-edge graph))
	     (setf (graph-display-right-most-edge graph)
		   (+f x-position (width-of-block short-rep))))))))

(defun display-graph-on-workspace (graph)
  (let ((workspace (graph-display-workspace graph)))
    (with-deferred-drawing-in-process ()		    ; Speeds up inspector display. -fmw, 6/28/94
      (enlarge-workspace-if-necessary
	workspace
	(graph-display-left-most-edge graph)
	(graph-display-top-edge graph)
	(graph-display-right-most-edge graph)
	(graph-display-bottom-edge graph))
      (display-graph-node (graph-display-root graph) workspace))))

(defun update-display-of-graph-on-workspace (graph)
  (let ((workspace (graph-display-workspace graph)))
    (enlarge-workspace-if-necessary
      workspace
      (graph-display-left-most-edge graph)
      (graph-display-top-edge graph)
      (graph-display-right-most-edge graph)
      (graph-display-bottom-edge graph))
    (update-display-of-graph-nodes graph)
    (change-workspace-edges-after-including-margin
      workspace
      (graph-display-left-most-edge graph)
      (graph-display-top-edge graph)
      (graph-display-right-most-edge graph)
      (graph-display-bottom-edge graph)) ))

(defun display-graph-node (graph-node workspace)
  (let* ((graph (graph-node-graph graph-node))
	 (short-rep (graph-node-short-representation graph-node))
	 (kids (graph-node-children graph-node)))
    (add-to-workspace
      short-rep workspace
      (graph-node-x-position graph-node)
      (graph-node-y-position graph-node)
      t)
    ;; The previous replaces the following three and adds the capability
    ;;   of drawing images of the new subblocks to be immediately.  (Note
    ;;   that connections had been drawn immediately in all cases before.) 
    ;;   (MHD 6/20/90)
;    (move-block-to-position
;      short-rep
;      (graph-node-x-position graph-node)
;      (graph-node-y-position graph-node))
;    (add-subblock short-rep workspace)
    (when kids
      (loop for kid in kids
	    do
	(display-graph-node kid workspace))
      (connect-superior-and-kid-graph-display-nodes
	graph graph-node (graph-display-orientation graph) kids))))




;;; The special variables `graphed-block-groups-to-move',
;;; 'graph-nodes-needing-children-connections', and
;;; `graph-nodes-to-add-as-subblocks' contain graph-layout lists of groups to
;;; move, graph-nodes whose children connections should be drawn, and graph
;;; nodes which need to be added to their workspaces as subblocks.  Each block
;;; group will look like (x-movement y-movement .  <list-of-blocks>).  The
;;; macros `graphed-block-group-x-movement', `graphed-block-group-y-movement',
;;; and `graphed-block-group-blocks' can be used to access and SETF elements of
;;; a block group.

(defvar graphed-block-groups-to-move nil)

(defvar graph-nodes-needing-children-connections nil)

(defvar graph-nodes-to-add-as-subblocks nil)

(defmacro graphed-block-group-x-movement (block-group)
  `(car ,block-group))

(defmacro graphed-block-group-y-movement (block-group)
  `(cadr ,block-group))

(defmacro graphed-block-group-blocks (block-group)
  `(cddr ,block-group))

(defun make-graphed-block-group (x-movement y-movement initial-block)
  (let ((new-group (graph-layout-list x-movement y-movement initial-block)))
    (setq graphed-block-groups-to-move
	  (graph-layout-cons new-group graphed-block-groups-to-move))
    new-group))

(defmacro reclaim-graphed-block-group (graphed-block-group)
  `(reclaim-graph-layout-list ,graphed-block-group))

(defun add-blocks-to-graphed-block-group (block-group graph-layout-block-list)
  (when graph-layout-block-list
    (setf (graphed-block-group-blocks block-group)
	  (nconc graph-layout-block-list
		 (graphed-block-group-blocks block-group))))
  nil)




;;; The function `update-display-of-graph-nodes' is the top level function for
;;; actually displaying changes from a graph.  It establishes two schedule
;;; queues in special variables and then calls the function
;;; schedule-or-reposition-graph-node on the root node of the graph.  This
;;; function will move blocks as well as schedules groups of blocks to be moved
;;; and scheduling graph nodes to have their children connections redrawn.  Each
;;; group of blocks will have no connections to any other blocks by the time
;;; this function returns.  After this function returns, the two schedules
;;; should be executed.  This first schedule is for the repositioning of groups
;;; of blocks.  The second schedule is for drawing the children connections
;;; graph-nodes.

(defun update-display-of-graph-nodes (graph)
  (let ((root-node (graph-display-root graph))
	(workspace (graph-display-workspace graph))
	(orientation (graph-display-orientation graph))
	(graphed-block-groups-to-move nil)
	(graph-nodes-needing-children-connections nil)
	(graph-nodes-to-add-as-subblocks nil))
    (schedule-or-reposition-graph-node
      root-node
      (make-graphed-block-group 0 0 (graph-node-short-representation root-node)))
;    (cerror "Continue." "Schedules made.")
    (delete-short-representation-frames-of-graph-node-tree
      (graph-display-update-root graph))
    (loop for block-group in graphed-block-groups-to-move
	  for x-shift = (graphed-block-group-x-movement block-group)
	  for y-shift = (graphed-block-group-y-movement block-group)
	  do
      (when (or (/=f x-shift 0)
		(/=f y-shift 0))
	(setq graph-display-changed-during-update? t)
	(move-blocks-with-their-external-connections
	  (graphed-block-group-blocks block-group)
	  workspace
	  x-shift
	  y-shift)
;	(terminal-pause 100 "Block group just moved")
	)
      (reclaim-graphed-block-group block-group))
    (reclaim-graph-layout-list graphed-block-groups-to-move)
    (loop for graph-node in graph-nodes-to-add-as-subblocks
	  for short-rep = (graph-node-short-representation graph-node)
	  do
      (setq graph-display-changed-during-update? t)
      (add-to-workspace
	short-rep workspace
	(graph-node-x-position graph-node)
	(graph-node-y-position graph-node)
	t)
      ;; the previous replaces the following three:   (MHD 6/20/90)
;      (move-block-to-position
;	short-rep
;	(graph-node-x-position graph-node)
;	(graph-node-y-position graph-node))
;      (add-subblock short-rep workspace)
;      (update-images-of-block short-rep nil t)

;      (terminal-pause 100 "New Block Added")
      )
    (reclaim-graph-layout-list graph-nodes-to-add-as-subblocks)
    (loop for graph-node in graph-nodes-needing-children-connections do
      (setq graph-display-changed-during-update? t)
      (connect-superior-and-kid-graph-display-nodes
	graph
	graph-node
	orientation
	(graph-node-children graph-node)))
    (reclaim-graph-layout-list graph-nodes-needing-children-connections)
    nil))




;;; The function `schedule-or-reposition-graph-node' takes a graph-node and a
;;; workspace and either positions or schedules for the positioning the block
;;; representing the node.  The second argument to this function reflects
;;; whether the parent has already scheduled this node to be repositioned.  If
;;; it has, then this node should only process its connections to children,
;;; possibly scheduling them to be moved within the given block group, if
;;; possible.

;;; Note that the root node will be included in a block group which has x and y
;;; movements of 0.

(defun schedule-or-reposition-graph-node
       (graph-node block-group-already-containing-this-node?)
  (let* ((short-rep (graph-node-short-representation graph-node))
	 (kids (graph-node-children graph-node))
	 (original-node? (graph-node-original-node-in-update graph-node)))
    (cond (original-node?
	   (when (null block-group-already-containing-this-node?)
	     (setq block-group-already-containing-this-node?
		   (make-graphed-block-group
		     (-f (graph-node-x-position graph-node)
			 (graph-node-x-position original-node?))
		     (-f (graph-node-y-position graph-node)
			 (graph-node-y-position original-node?))
		     short-rep)))
	   (if (graph-node-children-can-be-included-in-block-group-p
		 graph-node block-group-already-containing-this-node?)
	       (progn
		 ;; Add intermediate junctions to block group.
		 (add-blocks-to-graphed-block-group
		   block-group-already-containing-this-node?
		   (graph-layout-list-of-children-junctions short-rep))
		 ;; Add children to block group.
		 (add-blocks-to-graphed-block-group
		   block-group-already-containing-this-node?
		   (loop for kid in kids
			 collect (graph-node-short-representation kid)
				 using graph-layout-cons))
		 ;; Position the kids.
		 (loop for kid in kids do
		   (schedule-or-reposition-graph-node
		     kid
		     block-group-already-containing-this-node?)))
	       (progn
		 ;; Remove connections between short-rep and children.
		 (remove-connections-to-sub-nodes
		   (graph-node-short-representation graph-node))
		 ;; If there are children, schedule this node to draw thier
		 ;; connections and repostion them.
		 (when kids
		   (setq graph-nodes-needing-children-connections
			 (graph-layout-cons
			   graph-node
			   graph-nodes-needing-children-connections))
		   (loop for kid in kids do
		     (schedule-or-reposition-graph-node kid nil))))))
	  (t
	   (setq graph-nodes-to-add-as-subblocks
		 (graph-layout-cons
		   graph-node graph-nodes-to-add-as-subblocks))
	   (when kids
	     (setq graph-nodes-needing-children-connections
		   (graph-layout-cons
		     graph-node
		     graph-nodes-needing-children-connections))
	     (loop for kid in kids
		   do
	       (schedule-or-reposition-graph-node kid nil)))))))




;;; The function `graph-node-children-can-be-included-in-block-group-p' is used
;;; to determine whether the children of a graph-node can be included in the
;;; block group as the parent graph-node.  The children of a node can be
;;; included if the following criteria hold: the children of the given node all
;;; have original nodes, the list of original nodes of the children of the given
;;; graph node is equal to the list of children of the original node of the
;;; given node, and the amount to shift the short rep of the children is equal
;;; to the amounts to shift of the given block group.

(defun graph-node-children-can-be-included-in-block-group-p
       (graph-node block-group)
  (let ((original-node (graph-node-original-node-in-update graph-node))
	(kids (graph-node-children graph-node))
	(x-shift (graphed-block-group-x-movement block-group))
	(y-shift (graphed-block-group-y-movement block-group)))
    (declare (type fixnum x-shift y-shift))
    (if (and original-node kids)
	(loop for kid-cons = kids then (cdr kid-cons)
	      for old-kid-cons = (graph-node-children original-node)
			       then (cdr old-kid-cons)
	      while (and kid-cons old-kid-cons)
	      for kid = (car kid-cons)
	      for kid-original = (graph-node-original-node-in-update kid)
	      do
	  (when (or (neq kid-original (car old-kid-cons))
		    (/=f (-f (graph-node-x-position kid)
			     (graph-node-x-position kid-original))
			 x-shift)
		    (/=f (-f (graph-node-y-position kid)
			     (graph-node-y-position kid-original))
			 y-shift))
	    (return nil))
	      finally
		(return (and (null kid-cons) (null old-kid-cons))))
	nil)))




;;; The function `graph-layout-list-of-children-junctions' is given a block and
;;; should return a list of all junction instances between it and its children.

(defun graph-layout-list-of-children-junctions (block)
  (loop with junctions = nil
	with search-origins = (graph-layout-list block)
	while search-origins
	for new-junctions
	    = (loop for connection being each connection
			of (car search-origins) at-port 'sub-nodes
		    for other-end = (get-block-at-other-end-of-connection
				      connection (car search-origins))
		    when (frame-of-class-p other-end 'default-junction)
		      collect other-end using eval-cons)
	    then (loop for connection being each connection
		       of (car search-origins)
		       for other-end = (get-block-at-other-end-of-connection
					 connection (car search-origins))
		       when (frame-of-class-p other-end 'default-junction)
			 collect other-end using eval-cons)
	do
    (setq search-origins
	  (prog1 (cdr search-origins)
		 (reclaim-graph-layout-cons-macro search-origins)))
    (loop for junction in new-junctions do
      (when (not (memq junction junctions))
	(setq junctions (graph-layout-cons junction junctions))
	(setq search-origins (graph-layout-cons junction search-origins))))
    (reclaim-eval-list new-junctions)
	finally
	  (return junctions)))




;;; The function `graph-layout-list-of-connected-child-short-representations' is
;;; given a block which is a short representation, and returns those short
;;; representations which are connected to it and children of this object.  Note
;;; that since the graph display facility does not know the class of the short
;;; representation items, this facility must find all connected blocks and
;;; then filter out the junction blocks and connections.

(defun graph-layout-list-of-connected-child-short-representations (block)
  (let ((blocks (graph-layout-list block)))
    (loop with search-origins = (graph-layout-list block)
	  while search-origins
	  for new-blocks
	      = (eval-list-of-connected-blocks
		  (car search-origins)
		  'sub-nodes
		  nil)
	      then (eval-list-of-connected-blocks
		     (car search-origins)
		     'sub-nodes
		     nil)
	  do
      (setq search-origins
	    (prog1 (cdr search-origins)
		   (reclaim-graph-layout-cons search-origins)))
      (loop for new-block in new-blocks do
	(when (not (memq new-block blocks))
	  (setq blocks (graph-layout-cons new-block blocks))
	  (when (frame-of-class-p new-block 'default-junction)
	    (setq search-origins (graph-layout-cons new-block search-origins)))))
      (reclaim-eval-list new-blocks))
    (loop for candidate in blocks
	  unless (or (eq block candidate)
		     (frame-of-class-p candidate 'default-junction)
		     (frame-of-class-p candidate 'loose-end)
		     (frame-of-class-p candidate 'connection))
	    collect candidate into result-blocks using graph-layout-cons
	  finally
	    (reclaim-graph-layout-list blocks)
	    (return result-blocks))))




;;; The function `remove-connections-to-sub-nodes' takes a short representation
;;; of a graph node and should delete the connection tree from the short
;;; representation which goes to children nodes.  This is done by deleting all
;;; junction blocks inbetween this node and its children, and then calling the
;;; delete connection function for the superior node connections of all
;;; connected children and for the sub-nodes connection of this block.

(defun remove-connections-to-sub-nodes (short-rep)
  (let* ((junction-blocks
	   (graph-layout-list-of-children-junctions short-rep))
	 (connected-children
	   (graph-layout-list-of-connected-child-short-representations
	     short-rep))
	 (sub-nodes-connection nil))
    (loop for junction in junction-blocks
	  do
      (setq graph-display-changed-during-update? t)
      (delete-frame junction)
;      (terminal-pause 100 "Junction Deleted")
	  )
    (reclaim-graph-layout-list junction-blocks)
    (setq sub-nodes-connection (sub-nodes-connection short-rep))
    (when sub-nodes-connection
      (setq graph-display-changed-during-update? t)
      (delete-connection sub-nodes-connection)
;      (terminal-pause 100 "Sub-nodes connection Deleted")
      )
    (loop for child in connected-children
	  for connection = (superior-node-connection child)
	  do
      (when connection
	(setq graph-display-changed-during-update? t)
	(delete-connection connection)
;	(terminal-pause 100 "Superior node connection Deleted")
	))
;    (when (or junction-blocks connected-children sub-nodes-connection)
;      (terminal-pause 100 "Connections Removed")
;      (cerror "Continue" "Check for clean kids!")
;      )
    (reclaim-graph-layout-list connected-children)))




;;; The function `delete-short-representation-frames-of-graph-node-tree' takes a
;;; graph node and will traverse the sub-tree of this node, deleting any short
;;; representation frames found along the way.  This function is called at the
;;; end of an update to a graph.  The old graph-node tree has already been
;;; scavenged and those old short representations which could be reused have
;;; been moved to the new graph-node tree, and pointers to them removed from the
;;; old tree.

(defun delete-short-representation-frames-of-graph-node-tree (graph-node)
  (let ((short-rep? (graph-node-short-representation graph-node))
	(kids (graph-node-children graph-node)))
    (when short-rep?
;      (cerror "Continue" "About to delete short rep frame.")
      (remove-connections-to-sub-nodes short-rep?)
      (delete-frame short-rep?)
;      (terminal-pause 100 "Old Frame Deleted")
      )
    (loop for kid in kids do
      (delete-short-representation-frames-of-graph-node-tree kid))))




;;; The function `add-parent-stub-to-graph-display-block' is used to place a
;;; stub onto the given frame in preparation for connecting this frame to its
;;; children frames in a graph hierarchy.

(defun add-parent-stub-to-graph-display-block (block orientation workspace)
  (unless (sub-nodes-connection block)
    (let ((new-connection
	    (add-stub
	      block
	      (if (eq orientation 'inverted)
		  'inverted-sub-nodes
		  'sub-nodes)
	      'connection nil
	      (case orientation
		((vertical)
		 'bottom)
		((horizontal)
		 'right)
		((inverted)
		 'top)
		((backwards)
		 'left))
	      (halff
		(case orientation
		  ((vertical inverted)
		   (width-of-block block))
		  ((horizontal backwards)
		   (height-of-block block))
                  (t 0))))))
      (update-connection-images nil workspace new-connection)
      nil)))




;;; The function `add-superior-node-stub-to-graph-display-block is used to place
;;; a stub onto the given frame in preparation for connecting this frame to its
;;; superior object in a graphed hierarchy.

(defun add-superior-node-stub-to-graph-display-block
       (block orientation workspace)
  (unless (superior-node-connection block)
    (let ((new-connection
	    (add-stub
	      block
	      'superior-node 'connection nil
	      (case orientation
		((vertical)
		 'top)
		((horizontal)
		 'left)
		((inverted)
		 'bottom)
		((backwards)
		 'right))
	      (halff (case orientation
		       ((vertical inverted)
			(width-of-block block))
		       ((horizontal backwards)
			(height-of-block block))
                       (t 0))))))
      (update-connection-images nil workspace new-connection)
;      (terminal-pause 100 "Stub added to child")
      nil)))




;;; The function `connect-superior-and-kid-graph-display-nodes' is used to draw
;;; connections between a superior node's frame and the children frames in a
;;; graphed hierarchy display.

(defun connect-superior-and-kid-graph-display-nodes
       (graph graph-node orientation kids)
  (loop for kid in kids
	collect (graph-node-short-representation kid)
		into kid-frames using graph-layout-cons
	finally
	  (progn
	    (connect-superior-and-kid-frames
	      (graph-node-short-representation graph-node)
	      orientation
	      kid-frames
	      (graph-display-workspace graph)
	      (graph-display-horizontal-spacing graph)
	      (graph-display-vertical-spacing graph))
	    (reclaim-graph-layout-list kid-frames))))

(defun connect-superior-and-kid-frames
       (parent-frame orientation kid-frames
	workspace horizontal-spacing vertical-spacing)
  (let ((short-rep parent-frame))
    ;; Create stubs on the parent and kids.
    (add-parent-stub-to-graph-display-block short-rep orientation workspace)
    (loop for kid in kid-frames do
      (add-superior-node-stub-to-graph-display-block
	kid orientation workspace))
    (let* ((parent-connection
	     (sub-nodes-connection short-rep orientation))
	   (parent-loose-end (get-block-at-other-end-of-connection
			       parent-connection short-rep)))
      (if (null (cdr kid-frames))
	  (let* ((kid-short-rep (car kid-frames))
		 (kid-loose-end
		   (get-block-at-other-end-of-connection
		     (superior-node-connection kid-short-rep)
		     kid-short-rep)))
	    (join-two-connections parent-loose-end kid-loose-end))
	  (let* ((first-short-rep (car kid-frames))
		 (first-loose-end
		   (get-block-at-other-end-of-connection
		     (superior-node-connection first-short-rep)
		     first-short-rep))
		 (last-short-rep (car (last kid-frames)))
		 (last-connection (superior-node-connection last-short-rep))
		 (last-loose-end
		   (get-block-at-other-end-of-connection
		     last-connection last-short-rep))
		 (junction-x
		   (case orientation
		     ((vertical inverted)
		      (left-edge-of-block parent-loose-end))
		     ((horizontal)
		      (-f (left-edge-of-block first-short-rep)
			  (halff horizontal-spacing)))
		     ((backwards)
		      (+f (right-edge-of-block first-short-rep)
			  (halff horizontal-spacing)))))
		 (junction-y
		   (case orientation
		     ((vertical)
		      (-f (top-edge-of-block first-short-rep)
			  (halff vertical-spacing)))
		     ((horizontal backwards)
		      (top-edge-of-block parent-loose-end))
		     ((inverted)
		      (+f (bottom-edge-of-block first-short-rep)
			  (halff vertical-spacing)))))
		 junction)
	    
	    ;; Connect first kid, inserting bend.
	    (update-connection-images t workspace parent-connection)
	    (toggle-side-for-loose-end
	      parent-loose-end parent-connection)
	    (move-block-to-position
	      parent-loose-end
	      (case orientation
		((vertical inverted)
		 (left-edge-of-block first-loose-end))
		((horizontal backwards)
		 junction-x))
	      (case orientation
		((vertical inverted)
		 junction-y)
		((horizontal backwards)
		 (top-edge-of-block first-loose-end))))
	    (add-bend-to-connection parent-connection parent-loose-end)
	    (move-block-to-position
	      parent-loose-end
	      (left-edge-of-block first-loose-end)
	      (top-edge-of-block first-loose-end))
	    (update-connection-images nil workspace parent-connection)
	    (join-two-connections parent-loose-end first-loose-end)

;	    (terminal-pause 100 "First Kid Connected")

	    ;; Connect up last child, forming junction.
	    (update-connection-images
	      t workspace (get-connection-for-loose-end last-loose-end))
	    (toggle-side-for-loose-end
	      last-loose-end (get-connection-for-loose-end last-loose-end))
	    (move-block-to-position
	      last-loose-end junction-x junction-y)
	    (update-connection-images
	      nil workspace (get-connection-for-loose-end last-loose-end))
	    (make-junction parent-connection last-loose-end)
	    (setq parent-connection
		  (sub-nodes-connection short-rep orientation))
	    (setq junction (get-block-at-other-end-of-connection
			     parent-connection short-rep))

;	    (terminal-pause 100 "Last kid connected")
	    
	    ;; Connect up all the middle children.
	    (loop with first-connection-limit fixnum
		    = (case orientation
			((vertical inverted)
			 (-f (left-edge-of-block junction)
			     (width-of-block junction)))
			((horizontal backwards)
			 (-f (top-edge-of-block junction)
			     (height-of-block junction)))
                        (t 0))
		  with last-connection-limit fixnum
		    = (case orientation
			((vertical inverted)
			 (+f (right-edge-of-block junction)
			     (width-of-block junction)))
			((horizontal backwards)
			 (+f (bottom-edge-of-block junction)
			     (height-of-block junction)))
                        (t 0))
		  for kid-short-rep in (cdr kid-frames)
		  until (eq kid-short-rep last-short-rep)
		  for kid-loose-end
		      = (get-block-at-other-end-of-connection
			  (superior-node-connection kid-short-rep)
			  kid-short-rep)
		  for kid-x fixnum = (left-edge-of-block kid-loose-end)
		  for kid-y fixnum = (top-edge-of-block kid-loose-end)
		  do
	      (update-connection-images
		t workspace
		(superior-node-connection kid-short-rep))
	      (toggle-side-for-loose-end
		kid-loose-end
		(superior-node-connection kid-short-rep))
	      (cond ((and (<f kid-x first-connection-limit)
			  (or (eq orientation 'vertical)
			      (eq orientation 'inverted)))
		     (move-block-to-position
		       kid-loose-end kid-x junction-y)
		     (update-connection-images
		       nil workspace
		       (superior-node-connection kid-short-rep))
		     (make-junction (get-left-connection-of-junction
				      junction parent-connection)
				    kid-loose-end))
		    ((and (<f kid-y first-connection-limit)
			  (not (or (eq orientation 'vertical)
				   (eq orientation 'inverted))))
		     (move-block-to-position
		       kid-loose-end junction-x kid-y)
		     (update-connection-images
		       nil workspace
		       (superior-node-connection kid-short-rep))
		     (make-junction (get-top-connection-of-junction
				      junction parent-connection)
				    kid-loose-end))
		    ((and (or (eq orientation 'vertical)
			      (eq orientation 'inverted))
			  (>f kid-x last-connection-limit))
		     (move-block-to-position
		       kid-loose-end kid-x junction-y)
		     (update-connection-images
		       nil workspace
		       (superior-node-connection kid-short-rep))
		     (make-junction
		       (superior-node-connection last-short-rep)
		       kid-loose-end))
		    ((and (not (or (eq orientation 'vertical)
				   (eq orientation 'inverted)))
			  (>f kid-y last-connection-limit))
		     (move-block-to-position
		       kid-loose-end junction-x kid-y)
		     (update-connection-images
		       nil workspace
		       (superior-node-connection kid-short-rep))
		     (make-junction
		       (superior-node-connection last-short-rep)
		       kid-loose-end))
		    ((eq orientation 'vertical)
		     (cond ((<=f kid-x (left-edge-of-block junction))
			    (move-block-to-position
			      kid-loose-end
			      (+f kid-x 40)	       ; a little to the right
			      (+f (bottom-edge-of-block junction) 2))
			    (add-bend-to-connection
			      (superior-node-connection kid-short-rep)
			      kid-loose-end))
			   ((>=f kid-x (right-edge-of-block junction))
			    (move-block-to-position
			      kid-loose-end
			      (-f kid-x 40)	       ; a little to the left
			      (+f (bottom-edge-of-block junction) 2))
			    (add-bend-to-connection
			      (superior-node-connection kid-short-rep)
			      kid-loose-end)))
		     (move-block-to-position
		       kid-loose-end
		       (+f (left-edge-of-block junction)
			   (halff (width-of-block junction)))
		       (-f (bottom-edge-of-block junction) 2))
		     (update-connection-images
		       nil workspace
		       (superior-node-connection kid-short-rep))
		     (add-new-connection-to-block kid-loose-end junction t))
		    ((eq orientation 'inverted)
		     (cond ((<=f kid-x (left-edge-of-block junction))
			    (move-block-to-position
			      kid-loose-end
			      (+f kid-x 40)	       ; a little to the right
			      (-f (top-edge-of-block junction) 2))
			    (add-bend-to-connection
			      (superior-node-connection kid-short-rep)
			      kid-loose-end))
			   ((>=f kid-x (right-edge-of-block junction))
			    (move-block-to-position
			      kid-loose-end
			      (-f kid-x 40)	       ; a little to the left
			      (-f (top-edge-of-block junction) 2))
			    (add-bend-to-connection
			      (superior-node-connection kid-short-rep)
			      kid-loose-end)))
		     (move-block-to-position
		       kid-loose-end
		       (+f (left-edge-of-block junction)
			   (halff (width-of-block junction)))
		       (+f (top-edge-of-block junction) 2))
		     (update-connection-images
		       nil workspace
		       (superior-node-connection kid-short-rep))
		     (add-new-connection-to-block kid-loose-end junction t))
		    ((eq orientation 'horizontal)
		     (cond ((<=f kid-y (top-edge-of-block junction))
			    (move-block-to-position
			      kid-loose-end
			      (+f (right-edge-of-block junction) 2)
			      (+f kid-y 40))	       ; a little down
			    (add-bend-to-connection
			      (superior-node-connection kid-short-rep)
			      kid-loose-end))
			   ((>=f kid-y (bottom-edge-of-block junction))
			    (move-block-to-position
			      kid-loose-end
			      (+f (right-edge-of-block junction) 2)
			      (-f kid-y 40))	       ; a little up
			    (add-bend-to-connection
			      (superior-node-connection kid-short-rep)
			      kid-loose-end)))
		     (move-block-to-position
		       kid-loose-end
		       (-f (right-edge-of-block junction) 2)
		       (+f (top-edge-of-block junction)
			   (halff (height-of-block junction))))
		     (update-connection-images
		       nil workspace
		       (superior-node-connection kid-short-rep))
		     (add-new-connection-to-block kid-loose-end junction t))
		    ((eq orientation 'backwards)
		     (cond ((<=f kid-y (top-edge-of-block junction))
			    (move-block-to-position
			      kid-loose-end
			      (-f (left-edge-of-block junction) 2)
			      (+f kid-y 40))	       ; a little down
			    (add-bend-to-connection
			      (superior-node-connection kid-short-rep)
			      kid-loose-end))
			   ((>=f kid-y (bottom-edge-of-block junction))
			    (move-block-to-position
			      kid-loose-end
			      (-f (left-edge-of-block junction) 2)
			      (-f kid-y 40))	       ; a little up
			    (add-bend-to-connection
			      (superior-node-connection kid-short-rep)
			      kid-loose-end)))
		     (move-block-to-position
		       kid-loose-end
		       (+f (left-edge-of-block junction) 2)
		       (+f (top-edge-of-block junction)
			   (halff (height-of-block junction))))
		     (update-connection-images
		       nil workspace
		       (superior-node-connection kid-short-rep))
		     (add-new-connection-to-block kid-loose-end junction t)))
;	      (terminal-pause 100 "Middle kid connected")
	      ))))))

(defun move-block-to-position (block x-position y-position)
  (let ((old-x (left-edge-of-block block))
	(old-y (top-edge-of-block block)))
    (funcall-method
      'shift block (-f x-position old-x) (-f y-position old-y))))

(defun eval-list-of-connected-blocks (block port-name? class?)
  (let ((result nil))
    (if port-name?
	(loop for connection being each connection
		  of block at-port port-name?
	      for other-end = (get-block-at-other-end-of-connection
				connection block)
	      do
	  (when (or (null class?)
		    (frame-of-class-p other-end class?))
	    (setq result (eval-cons other-end result))))
	(loop for connection being each connection of block
	      for other-end = (get-block-at-other-end-of-connection
				connection block)
	      do
	  (when (or (null class?)
		    (frame-of-class-p other-end class?))
	    (setq result (eval-cons other-end result)))))
    result))

(defun superior-node-connection (display-node-entity)
  (loop for connection being each connection
	    of display-node-entity at-port 'superior-node
	do (return connection)))

(defun sub-nodes-connection
       (display-node-entity &optional (orientation nil))
  (loop for connection being each connection
	    of display-node-entity
	    at-port (if (eq orientation 'inverted)
			'inverted-sub-nodes
			'sub-nodes)
	do (return connection)))

(defun get-left-connection-of-junction (junction parent-connection)
  (loop for connection being each connection of junction
	do
    (when (and (neq connection parent-connection)
	       (<f (left-edge-of-block
		     (get-block-at-other-end-of-connection
		       connection junction))
		   (left-edge-of-block junction)))
      (return connection))))

(defun get-top-connection-of-junction (junction parent-connection)
  (loop for connection being each connection of junction
	do
    (when (and (neq connection parent-connection)
	       (<f (top-edge-of-block
		     (get-block-at-other-end-of-connection
		       connection junction))
		   (top-edge-of-block junction)))
      (return connection))))






;;;; Graphing Procedure Invocations




(defun graph-procedure-invocations (procedure-invocation)
  (graph-frame-hierarchy
    procedure-invocation
    'called-procedure-invocations-for-graph
    nil
    'make-short-representation
    'frame-hash-function ;hash-function
    'vertical)) ;orientation

(defun called-procedure-invocations-for-graph (procedure-invocation extra-arg)
  (declare (ignore extra-arg))
  (loop for invocation in (called-code-bodies procedure-invocation)
	nconc (called-procedure-invocations-for-graph-1 invocation)))

(defun called-procedure-invocations-for-graph-1 (invocation)
  (if (procedure-invocation-p invocation)
      (gensym-list invocation)
      (loop for invocation in (called-code-bodies invocation)
	    nconc (called-procedure-invocations-for-graph-1 invocation))))

(defvar focus-for-graph-detailed-procedures nil)

(defun get-workspace-for-graph-detailed-procedures ()
  (make-workspace 'temporary-workspace nil nil nil nil nil))

(defun-simple valid-computation-instance-p (invocation)
  (or (code-body-invocation-p invocation)
      (remote-procedure-call-p invocation)
      (rule-instance-p invocation)
      (formula-invocation-p invocation)))

(defun list-callers-of-computation-instance (computation-instance-at-breakpoint)
  (loop for invocation = computation-instance-at-breakpoint
		       then (code-body-caller invocation)
	while (valid-computation-instance-p invocation)
	collect invocation using gensym-cons))

(defun graph-detailed-procedures (&optional invocation inspect-command?
					    focus-for-graph-detailed-procedures)
  (let* ((workspace-with-inspect-command?
	   (if inspect-command?
	       (get-and-clear-workspace-for-inspect-command
		 inspect-command?)))
	 (workspace?
	   (or workspace-with-inspect-command?
	       (get-workspace-for-graph-detailed-procedures))))
    (reclaim-graph-display
      (graph-frame-hierarchy
	(if (valid-computation-instance-p invocation)
	    invocation
	    'top-level)
	'called-detailed-procedure-graph
	nil
	'detailed-procedure-graph-short-representation
	'hash-detailed-procedure-graph ;hash-function
	nil nil nil ;orientation, vertical-spacing, and horizontal-spacing
	(unless workspace-with-inspect-command? ;pane-for-workspace-display?
	  (or pane-for-debugger-pause ;so we display on right pane from TW -dkuznick, 3/8/99
	      (and (boundp 'current-workstation-detail-pane)
		   current-workstation-detail-pane)
	      (car (panes-in-window system-window))))
	nil ;class-of-workspace
	workspace? ; workspace?
	(when inspect-command? ;left-edge-for-graph?
	  (left-edge-of-block inspect-command?))
	(when inspect-command? ;top-edge-for-graph?
	  (+w 5 (bottom-edge-of-block inspect-command?)))))
    (when workspace-with-inspect-command?
      (shrink-wrap-workspace workspace-with-inspect-command?))))

(defvar non-procedure-root-invocations nil)

(defun root-invocation-of-invocation (instance)
  (when (valid-computation-instance-p instance)
    (loop for invocation = instance
			 then next
	  for next = (code-body-caller invocation)
	  while (valid-computation-instance-p next)
	  finally (return invocation))))

(defun maybe-collect-root-invocation-of-invocation (instance)
  (let ((invocation (root-invocation-of-invocation instance)))
    (unless (or (null invocation)
		(code-body-invocation-p invocation)
		(remote-procedure-call-p invocation)
		(memq invocation non-procedure-root-invocations))
      (gensym-push invocation non-procedure-root-invocations))))

(defun collect-non-procedure-root-invocations-in-queue (constant-queue)
  (loop with fn = (task-function-for-symbol execute-computation-instance)
	for schedule-task being each constant-queue-element of constant-queue
	when (eq (schedule-task-function schedule-task) fn)
	  do (maybe-collect-root-invocation-of-invocation
	       (schedule-task-arg-1 schedule-task))))

(defun collect-non-procedure-root-invocations ()
  (#+mtg2 tx:with-lock-held #+mtg2 (scheduler-lock) #-mtg2 progn
  (let ((non-procedure-root-invocations nil))
    ;; for immediate task queue
    #-SymScale
    (unless (constant-queue-empty-p immediate-task-queue)
      (collect-non-procedure-root-invocations-in-queue immediate-task-queue))
    #+SymScale
    (loop for i from 0 below number-of-all-threads
	  for queue = (svref immediate-task-queue-vector i)
	  doing
      (unless (constant-queue-empty-p queue)
	(collect-non-procedure-root-invocations-in-queue queue)))
    ;; for current task queue
    (loop for priority from highest-system-priority to lowest-system-priority
	  for constant-queue = (svref current-task-queue-vector priority)
	  do (collect-non-procedure-root-invocations-in-queue constant-queue))
    (maybe-collect-root-invocation-of-invocation computation-instance-at-breakpoint)
    non-procedure-root-invocations)))

(defun called-detailed-procedure-graph (top-level-or-invocation extra-arg)
  (declare (ignore extra-arg))
  (let* ((valid-invocation? nil)
	 (result
	   (cond ((eq top-level-or-invocation 'top-level)
		  (nconc
		    (#-SymScale progn
		     #+SymScale tx:with-lock-held #+SymScale (procedure-invocations-lock)
			(loop with top-array = top-level-procedure-invocations-array
			       for index from 0 below (managed-array-length top-array)
			       for invocation? = (managed-svref top-array index)
			       when (and (when invocation?
					   (setq valid-invocation?
						 (or (code-body-caller invocation?)
						     invocation?)))
					 ;; GENSYMCID-1188: G2-Abort - Inspect while G2GL calls a procedure
					 (not (g2gl-call-invocation-p-function valid-invocation?)))
				 collect valid-invocation?
				   using gensym-cons))
			 (collect-non-procedure-root-invocations)))
		 ((or (rule-instance-p top-level-or-invocation)
		      (formula-invocation-p top-level-or-invocation))
		  nil)
		 ((valid-computation-instance-p top-level-or-invocation)
		  (copy-list-using-gensym-conses
		    (called-code-bodies top-level-or-invocation)))
		 (t
		  #+development
		  (error "Unknown element ~a in detailed procedure graph."
			 top-level-or-invocation))))
	 (focus-element
	   (loop for x in focus-for-graph-detailed-procedures
		 when (memq x result)
		   return x)))
    (if focus-element
	(gensym-cons focus-element (delete-gensym-element focus-element result))
	result)))	

(defun twrite-detailed-short-representation-of-code-body-invocation (invocation)
  ;; should try to do more when disassemble-enabled? is false. see write-computation-context.
  (when disassemble-enabled?
    (write-stack-instruction
      (invocation-stack-program-counter invocation)
      (invocation-byte-code-body invocation)
      (invocation-constant-vector invocation))
    (tformat "~%"))
  (write-code-body-environment
    (environment-description (code-body-of-invocation invocation))
    (invocation-local-var-vector invocation)))

(defun detailed-procedure-graph-short-representation (symbol-or-invocation)
  (make-description-box
    (cond ((symbolp symbol-or-invocation)
	   (copy-text-string (symbol-name-text-string symbol-or-invocation)))
	  ((procedure-invocation-p symbol-or-invocation)
	   (twith-output-to-text-string
	     (write-procedure-invocation-instance-from-slot symbol-or-invocation nil)
	     (tformat "~%")
	     (twrite-detailed-short-representation-of-code-body-invocation symbol-or-invocation)))
	  ((remote-procedure-call-p symbol-or-invocation)
	   (twith-output-to-text-string
	     (tformat "RPC ~A"
		      (if (remote-procedure-identifier-of-call symbol-or-invocation)
			  "call" "start"))
	     (let ((socket? (remote-procedure-call-icp-socket
			      symbol-or-invocation)))
	       (cond ((called-code-bodies symbol-or-invocation)
		      (tformat " from ")
		      (if socket?
			  (twrite-icp-socket-connection-name socket?)
			  (tformat "closed connection"))
		      (let ((interface
			      (remote-procedure-call-icp-interface symbol-or-invocation)))
			(when interface
			  (tformat "~%server interface ~NF" interface))))
		     (t
		      ;; I'm not sure we can ever NOT have an outgoing socket,
		      ;; but this will prevent any aborts if so
		      (if socket?
			  (progn
			    (tformat " to ~NF across ~NF~%connecting to "
				     (remote-procedure-declaration-of-call
				       symbol-or-invocation)
				     (remote-procedure-call-icp-interface
				       symbol-or-invocation))
			    (twrite-icp-socket-connection-name
			      (remote-procedure-call-icp-socket
				symbol-or-invocation)))
			  (tformat " to closed connection")))))))
	  ((or (rule-instance-p symbol-or-invocation)
	       (formula-invocation-p symbol-or-invocation))
	   (twith-output-to-text-string
	     (tformat "~NF" (if (rule-instance-p symbol-or-invocation)
				(ri-rule symbol-or-invocation)
				(formula-invocation-variable symbol-or-invocation)))
	     (when disassemble-enabled?
	       (tformat "~%")
	       (write-stack-instruction
		 (invocation-stack-program-counter symbol-or-invocation)
		 (invocation-byte-code-body symbol-or-invocation)
		 (invocation-constant-vector symbol-or-invocation)))))
	  ((code-body-invocation-p symbol-or-invocation)
	   (twith-output-to-text-string
	     (twrite-detailed-short-representation-of-code-body-invocation symbol-or-invocation)))
	  (t
	   (tformat-text-string "Unknown thing ~a" symbol-or-invocation)))))

(defun hash-detailed-procedure-graph (symbol-or-invocation)
  (declare (ignore symbol-or-invocation))
  1)






;;;; Disassembling Code Bodies




;;; The function `print-code' pretty prints out the code for all of the raw
;;; instructions bodes of the given procedure.  This is a development only
;;; function.

#+development
(defun print-code (procedure)
  (disassemble-item procedure))

#+development
(defun disassemble-item (item &optional (output-stream *standard-output*))
  (let ((short-reps (nreverse (disassemble-item-if-appropriate item))))
    (loop for short-rep in short-reps
	  for text = (cdr (box-translation-and-text short-rep))
	  for text-string = (convert-text-to-text-string text)
	  do
      (pprint-wide-string-fully text-string output-stream)
      (reclaim-text-string text-string)
      (delete-frame short-rep))
    (reclaim-eval-list short-reps)
    item))

#+development
(defun disassemble-byte-code-body (byte-code-body
				    &optional (output-stream *standard-output*))
  
  (let* ((text-string
	   (twith-output-to-text-string
	     (write-byte-code-body
	       byte-code-body
	       (byte-code-body-constant-vector byte-code-body)))))
    (pprint-wide-string-fully text-string output-stream)
    (reclaim-text-string text-string)
    byte-code-body))

#+development
(defun disassemble-code-body (code-body
			       &optional (output-stream *standard-output*))
  (disassemble-byte-code-body (code-body-byte-code-body code-body)
			      output-stream)
  code-body)


#+development
(defun disassemble-code-body-invocation (code-body-invocation
					  &optional (output-stream *standard-output*))
  (disassemble-byte-code-body (invocation-byte-code-body code-body-invocation)
			      output-stream)
  code-body-invocation)

#+development
(defun disassemble-procedure-invocation (procedure-invocation
					  &optional (output-stream *standard-output*))
  (disassemble-item (procedure-of-invocation procedure-invocation)
		    output-stream)
  procedure-invocation)



;;; The function `disassemble-procedure-on-temporary-workspace takes a procedure
;;; instance as its argument and produces a temporary workspace which shows the
;;; disassembled code for that procedure.  The image of the workspace is put
;;; onto the detail pane for current workstation.

(def-slot-value-writer code-bodies (code-bodies)
  (write-disassembled-code-bodies code-bodies))

#+development
(defun disassemble-procedure-on-temporary-workspace (procedure)
  (put-workspace-on-pane
    (make-workspace
      'temporary-workspace nil
      (make-description-box
	(twith-output-to-text-string
	  (tformat
	    "Disassembly of ~NF~%~%"
	    procedure)
	  (write-disassembled-code-bodies (code-bodies procedure))))
      50 nil nil)
    current-workstation-detail-pane 'left 'top t))




(defun write-disassembled-code-bodies (code-bodies)
  (loop with default-constant-vector?
	  = (if (car code-bodies)
		(byte-code-body-constant-vector
		  (code-body-byte-code-body (car code-bodies)))
		nil)
	for code-body-number from 0
	for code-body-to-print in code-bodies
	for byte-code-body? =
	    (code-body-byte-code-body code-body-to-print)
	for first-time? = t then nil
	do
    (unless first-time?
      (tformat "~%~%"))
    (tformat "Code Body ~a~%" code-body-number)
    (cond (byte-code-body?
	   (write-byte-code-body
	     byte-code-body?
	     (or (byte-code-body-constant-vector byte-code-body?)
		 default-constant-vector?)))
	  (t
	   (twrite-string "No compiled code")))))

;;


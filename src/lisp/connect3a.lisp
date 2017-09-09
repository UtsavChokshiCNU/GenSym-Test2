;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module CONNECT3A

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Andreas Hofmann



(declare-forward-reference
  update-runtime-structures-according-to-edit function)	; in module INSTALL
(declare-forward-reference
  decache-roles-for-entities-related-to-this-connection function)  ; in module ROLES

(declare-forward-reference mouse-leeway-in-workspace function run)
(declare-forward-reference loading-kb-p variable)
(declare-forward-reference image-plane-of-workspace-on-window function workstation)
(declare-forward-reference send-ws-representations-item-insert-as-subblock function)

(declare-forward-reference send-ws-representations-connection-moved function)
(declare-forward-reference add-cursors-to-current-window function)

(declare-forward-reference note-deletion-of-connection-for-selection function) ; MOVES



;;; The module CONNECT3A contains what used to be in the tail of CONNECT3.  The
;;; file was split up to deal with limitations on the IBM RS/6000 C compiler.
;;; -jra 1/16/92

;;; Make-junction takes a connection and a loose-end as an argument.  It is
;;; assumed that the loose-end is close to some non-endpoint portion of the
;;; connection.  A junction is added, the connection is split into two, each end
;;; being connected to the junction, and the connection from the loose end is
;;; also connected to the junction, if there is no cross-section compatibility
;;; problem.  The function returns t if the connection was successful.  Some
;;; heuristics will eventually have to be added to get rid of small wrinkles in
;;; connections.  A junction can not be made by dragging a connection loose end
;;; to some previous point on the same connection.

(defun make-junction (junction-connection loose-end)
  (let* ((loose-end-connection (get-connection-for-loose-end loose-end))
	 (junction-connection-frame-or-class
	   (connection-frame-or-class junction-connection))
	 (loose-end-connection-frame-or-class
	   (connection-frame-or-class loose-end-connection))
	 (junction-block-class
	   (if (>w (compute-connection-width-given-connection-frame-or-class
		     loose-end-connection-frame-or-class)
		   (compute-connection-width-given-connection-frame-or-class
		     junction-connection-frame-or-class))
	       (get-junction-block-class-given-connection-frame-or-class
		 loose-end-connection-frame-or-class)
	       (get-junction-block-class-given-connection-frame-or-class
		 junction-connection-frame-or-class)))
	 (problem-format-string?
	   (cond
	     ;; cross section pattern problem?
	     ((and (not (connection-cross-section-patterns-compatible?
			  loose-end-connection junction-connection))
		   (not (of-class-p
			  (get-block-at-other-end-of-connection
			    loose-end-connection loose-end)
			  'sensor)))
	      "Cannot join connections with incompatible cross sections.")
	     ;; Diagonal (will be allowed eventually)
	     ((or (connection-diagonal-p loose-end-connection)
		  (connection-diagonal-p junction-connection))
	      "Cannot make junction for diagonal connections.")
	     ;; Class not specified?
	     ((null junction-block-class)
	      "Cannot join connections because there is no defined class for ~
               the junction.")
	     ;; Class undefined?
	     ((not (classp junction-block-class))	; note: requires 2 args
	      "Cannot join connections because the class for the junction, ~
               ~a, is not defined.")
	     ;; Not a junction class?
	     ((not (subclassp junction-block-class 'default-junction))
	      "Cannot join connections because the class for the junction, ~
               ~a, is not a subclass of ~a.")
	     ;; connecting connection to itself?
	     ((eq loose-end-connection junction-connection)
	      ;; It seems that this check is made at a higher level (in MOVES).
	      "Cannot join a connection to itself."))))
    (cond
      (problem-format-string?
       (notify-user    ; 2nd & 3rd arg only used for 1 case, which is ok.
	 problem-format-string? junction-block-class 'default-junction)
       nil)
      (t
       (let* ((workspace (superblock? loose-end))
	      (junction-block (make-entity junction-block-class)))
	 ;; erase the two connections and loose end
	 (update-images-of-block loose-end t nil)
	 (if (eq (output-end-object loose-end-connection) loose-end)
	     (update-connection-images 
	       t workspace loose-end-connection))
	 (update-connection-images 
	   t workspace junction-connection)	 
	 ;; [It used to rebind junction-block-class and loose-end-connection
	 ;; here, but for no apparent reason. -mhd]
	 (cond
	   ((determine-position-of-and-insert-junction-block
	      junction-block junction-connection loose-end)
	    ;; if insertion is successful
	    
	    ;; Redraw loose end connection, two new connections,
	    ;; and junction-block.
	    (update-images-of-block junction-block nil nil)
	    (update-connection-images nil workspace junction-connection)
	    (if (not (eq (input-end-object loose-end-connection)
			 junction-block))
		(update-connection-images nil workspace loose-end-connection))
	    ;; Remove loose end from workspace.
	    ;; Recycle eventually!
	    (when (connections loose-end)
	      (reclaim-connection-item-table (connections loose-end)))
	    (setf (connections loose-end) nil)
	    (delete-frame loose-end)
	    t)
	   (t 
	    ;; if insertion is not successful
	    (delete-frame junction-block)
	    ;; so that the junction-block is not left as a ghost
	    
	    (update-images-of-block loose-end nil nil)
	    (when (eq (output-end-object loose-end-connection) loose-end)
	      (update-connection-images nil workspace loose-end-connection))
	    (update-connection-images nil workspace junction-connection)
	    nil)))))))

;; Reorganized a bit by MHD: (1) added guard against instantiating classes
;; of junction that are not subclasses of default-junction, (2) cleaned up
;; the English a bit -- all in complete sentences of more similar form, (3)
;; factored out common parts of guard clauses to reduce amount of code, 
;; (4) removed redundant bindings of a few variables, (5) bound workspace,
;; (6) replaced calls to update-images with update-images-of-block
;; where appropriate, (7) made test for incompatible cross sections the first
;; test (seems to make more sense).  Size of disassembled code was reduced
;; by about 17% (on Explorer II+) even though functionality was added.

;; Review case of where insertion is not successful.




;;; Determine-position-of-and-insert-junction-block determines the "best" (most
;;; wrinkle-free) position for the junction block.  It also adjusts the
;;; loose-end and connection being dragged so that it meets the junction
;;; block.  There are various cases for which a junction is not inserted.
;;; If the junction is inserted, t will be returned, else nothing will be
;;; done and nil will be returned.

(defun determine-position-of-and-insert-junction-block
       (junction-block junction-connection loose-end)
  (add-missing-deltas-to-connection junction-connection)
  (multiple-value-bind
    (connection distance intercept-or-corner
     rest-of-deltas
     x-position-of-intercept-or-corner
     y-position-of-intercept-or-corner
     orientation-horizontal-p)
      (find-vector-length-from-point-to-connection-if-within-limit 
	junction-connection
	(left-edge-of-block loose-end)
	(top-edge-of-block loose-end)
	(mouse-leeway-in-workspace (normalized-scale)))
    distance
;    (break "distance, intercept-or-corner, and rest-of-deltas: ~S ~S ~S ~%"
;	   distance intercept-or-corner
;	   rest-of-deltas)
;    (break "x and y position of intercept-or-corner: ~S ~S~%"
;	   x-position-of-intercept-or-corner
;	   y-position-of-intercept-or-corner)

    (cond
      (connection  
       ;; If find-vector-length-from-point-to-connection-if-within-limit succeeds.
       (let* ((connection-being-dragged
		(get-connection-for-loose-end loose-end))
	      junction-block-input-end-side junction-block-output-end-side
	      junction-block-connection-being-dragged-end-side
	      (inhibit-insertion-p nil))
	 
	 (multiple-value-bind
	   (link-1-delta link-2-delta link-2-orientation-horizontal-p)
	     (compute-stretched-links-of-connection-being-dragged
	       connection-being-dragged loose-end)
	   (declare (ignore link-1-delta))

	   (setq junction-block-connection-being-dragged-end-side
		 (if link-2-orientation-horizontal-p
		     (if (>w link-2-delta 0)
			 'left
			 'right)
		     (if (>w link-2-delta 0)
			 'top
			 'bottom)))
	   
	   ;; check if too close to a corner of the connection
	   ;; Note have to check if this is the first begin-corner or last
	   ;; end-corner of a connection, in which case, the junction-block
	   ;; should not be inserted.
	   (cond
	     ((or
		(cond
		  ((cond
		     ((numberp intercept-or-corner)
		      (cond
			((<w (absw intercept-or-corner)
			     (width-of-block junction-block))
			 (if orientation-horizontal-p
			     (setq x-position-of-intercept-or-corner
				   (-w x-position-of-intercept-or-corner 
				       intercept-or-corner))
			     (setq y-position-of-intercept-or-corner
				   (-w y-position-of-intercept-or-corner 
				       intercept-or-corner)))
			 (setq intercept-or-corner 'begin-corner)
			 t)))
		     (t
		      (eq intercept-or-corner 'begin-corner)))
		   ;; if near begin corner
		   
		   (cond
		     ((not (eq rest-of-deltas
			       (delta-or-deltas junction-connection)))
		      ;; if not first begin corner
		      (loop for new-rest-of-deltas
				on (delta-or-deltas junction-connection)
			    until (eq (cdr new-rest-of-deltas)
				      rest-of-deltas)
			    finally (setq rest-of-deltas new-rest-of-deltas))
		      (setq junction-block-input-end-side
			    (if orientation-horizontal-p
				(if (>w (car rest-of-deltas) 0)
				    'top
				    'bottom)
				(if (>w (car rest-of-deltas) 0)
				    'left
				    'right))
			    junction-block-output-end-side
			    (if orientation-horizontal-p
				(if (>w (cadr rest-of-deltas) 0)
				    'right
				    'left)
				(if (>w (cadr rest-of-deltas) 0)
				    'bottom
				    'top))))
		     (t (setq inhibit-insertion-p t)))
		   t))
		(cond
		  ((cond
		     ((numberp intercept-or-corner)
		      (cond
			((<w (absw (-w (car rest-of-deltas)
				       intercept-or-corner))
			     (width-of-block junction-block))
			 (if orientation-horizontal-p
			     (setq x-position-of-intercept-or-corner
				   (+w x-position-of-intercept-or-corner 
				       (-w (car rest-of-deltas) intercept-or-corner)))
			     (setq y-position-of-intercept-or-corner
				   (+w y-position-of-intercept-or-corner 
				       (-w (car rest-of-deltas) intercept-or-corner))))
			 (setq intercept-or-corner 'end-corner)
			 t)))
		     (t
		      (eq intercept-or-corner 'end-corner)))
		   ;; if near end corner
		   
		   (cond 
		     ((not (null (cdr rest-of-deltas)))
		      ;; if not last end corner
		      (setq junction-block-input-end-side
			    (if orientation-horizontal-p
				(if (>w (car rest-of-deltas) 0)
				    'left
				    'right)
				(if (>w (car rest-of-deltas) 0)
				    'top
				    'bottom))
			    junction-block-output-end-side
			    (if orientation-horizontal-p
				(if (>w (cadr rest-of-deltas) 0)
				    'bottom
				    'top)
				(if (>w (cadr rest-of-deltas) 0)
				    'right
				    'left))))
		     (t
		      (setq inhibit-insertion-p t)))
		   
		   t)))
	      
	      (cond 
		((and (not inhibit-insertion-p)
		      (not (or (eq junction-block-connection-being-dragged-end-side
				   junction-block-input-end-side)
			       (eq junction-block-connection-being-dragged-end-side
				   junction-block-output-end-side))))
		 ;; if connection-being-dragged won't overlap other connection
		 ;; in corner

		 (insert-junction-block
		   junction-block junction-connection loose-end
		   connection-being-dragged
		   junction-block-input-end-side
		   junction-block-output-end-side
		   junction-block-connection-being-dragged-end-side
		   intercept-or-corner rest-of-deltas
		   x-position-of-intercept-or-corner y-position-of-intercept-or-corner)
		 t)
		(t
		 (remove-redundant-deltas-from-connection junction-connection)
		 nil))
	      )
	     (t					; if not on corner
	      (cond 
		((or (and orientation-horizontal-p
			  link-2-orientation-horizontal-p)
		     (and (not orientation-horizontal-p)
			  (not link-2-orientation-horizontal-p)))
		 ;; If last link of connection being dragged and 
		 ;; link it is to be connected to are parallel,
		 ;; then if last link of connection being dragged is small,
		 ;; delete last bend and try to connect again.
		 ;; Else, do nothing.
		 
		 (let ((try-to-insert-again?
			 (and (<w (abs link-2-delta)
				  (mouse-leeway-in-workspace (normalized-scale)))
			      (not (and (null (delta-or-deltas connection-being-dragged))
					(cond
					  ((or (and (>w link-2-delta 0)
						    (>w (car rest-of-deltas) 0))
					       (and (not (>w link-2-delta 0))
						    (not (>w (car rest-of-deltas) 0))))
					   ;; link-2-delta and (car rest-of-deltas) have same direction
					   (<w (absw (-w intercept-or-corner link-2-delta))
					       (width-of-block junction-block)))
					  (t
					   (<w (absw (-w (car rest-of-deltas)
							 intercept-or-corner
							 (-w link-2-delta)))
					       (width-of-block junction-block)))))))))
		   ;; Do not try to insert again if too close to corner.  See notes in
		   ;; design notebook for 3/17/88.
		   (remove-redundant-deltas-from-connection junction-connection)
		   (cond
		     (try-to-insert-again?
		      (delete-last-bend-from-connection
			connection-being-dragged loose-end)
		      (determine-position-of-and-insert-junction-block
			junction-block junction-connection loose-end))))
		 )
		(t
		 
		 
		 (setq junction-block-input-end-side
		       (if orientation-horizontal-p
			   (if (>w (car rest-of-deltas) 0)
			       'left
			       'right)
			   (if (>w (car rest-of-deltas) 0)
			       'top
			       'bottom))
		       junction-block-output-end-side
		       (case junction-block-input-end-side
			 (left 'right)
			 (right 'left)
			 (top 'bottom)
			 (t			; if bottom
			  'top)))
		 
		 (insert-junction-block
		   junction-block junction-connection loose-end
		   connection-being-dragged
		   junction-block-input-end-side
		   junction-block-output-end-side
		   junction-block-connection-being-dragged-end-side
		   intercept-or-corner rest-of-deltas
		   x-position-of-intercept-or-corner y-position-of-intercept-or-corner)
		 t)))))))
      (t
       (remove-redundant-deltas-from-connection junction-connection)
       nil))))



;;; Insert-junction-block is called during a dragging context to insert
;;; junction-block joining junction-connection, a preexisting connection, and
;;; connection-being-dragged, another preexisting connection that the user has
;;; dragged into junction-connection.  Loose-end, whose superblock must be a
;;; workspace, is the end of the connection being dragged.

;;; This function results in the shortening of junction-connection, and the
;;; creation of a second connection, making up the output end of junction-block.
;;; It also makes junction-block a subblock of the workspace of (the superblock
;;; of) loose-end.  And it arranges to activate the resulting connection frame
;;; (explicitly), if needed, as well as junction-block (by virtue of calling
;;; add-subblock to add it to the workspace).  It also arranges that
;;; connection-post pointers remain set up correctly, if applicable.

;;; Input-end-side, output-end-side, and connection-being-dragged-end-side refer
;;; to sides of junction-block, and may all have values of either LEFT, TOP,
;;; RIGHT, or BOTTOM.

;;; Intercept-or-corner may be either workspace coordinate (a fixnum), in which
;;; case it gives the position at which connection-being-dragged intercepts
;;; junction-connection, or one of the symbols END-CORNER or BEGIN-CORNER.

;;; Rest-of-deltas is the portion of the delta-or-deltas slot of
;;; junction-connection that is to go with the resulting output end connection.

;;; X-position-of-intercept-or-corner and y-position-of-intercept-or-corner ....

(defun insert-junction-block
    (junction-block junction-connection
		    loose-end connection-being-dragged
		    input-end-side output-end-side
		    connection-being-dragged-end-side
		    intercept-or-corner rest-of-deltas
		    x-position-of-intercept-or-corner y-position-of-intercept-or-corner)

  (let ((junction-block-half-width
	  (halfw (width-of-block junction-block))))    
    
    (shift-block
      junction-block
      (-w x-position-of-intercept-or-corner junction-block-half-width)
      (-w y-position-of-intercept-or-corner junction-block-half-width))
    
    (change-connection-deltas-for-object-being-dragged
      connection-being-dragged loose-end 
      (case connection-being-dragged-end-side
	(left	 
	 (-w (left-edge-of-block junction-block)
	     (left-edge-of-block loose-end)))
	(right	 
	 (-w (right-edge-of-block junction-block)
	     (right-edge-of-block loose-end)))
	(t
	 ;; (top bottom)
	 (-w x-position-of-intercept-or-corner
	     (left-edge-of-block loose-end))))
      (case connection-being-dragged-end-side
	(top	 
	 (-w (top-edge-of-block junction-block)
	     (top-edge-of-block loose-end)))
	(bottom	 
	 (-w (bottom-edge-of-block junction-block)
	     (bottom-edge-of-block loose-end)))
	(t
	 ;; (left right)
	 (-w y-position-of-intercept-or-corner
	     (top-edge-of-block loose-end)))))

    (note-change-to-connection junction-connection)
    (note-change-to-connection connection-being-dragged)

    ;; bug fix:  we allowed (and continue to allow -- but maybe
    ;; for not much longer) users to define stubs on (custom)
    ;; junction-block definitions (i.e., subclasses of default-
    ;; junction).  Now, we delete any connections on junction-block
    ;; before doing any more work, and before adding it to the
    ;; workspace.  (Note the connections slot is set to a
    ;; completely new value below in this function.)  Old KBs must
    ;; have been getting garbage connections in this obscure case.
    ;; An even more obscure case is when the user not only defines
    ;; stubs for a junction, but defines them with connection
    ;; classes that need to be instantiated when the connection
    ;; structure is instantiated.  That could result in connection
    ;; frames in limbo pointing to junction-block, but not pointed
    ;; back to by junction-block, and pointing to loose ends
    ;; not on any workspace.  This resulted in at least one
    ;; bug report, where a user iterated over all connection frames,
    ;; changing their stripe patters, and G2 bombed out when it
    ;; hit one of these orphan connections in limbo. (MHD 4/14/93)
    (loop for count from 0			; need a delete-connections fn?
	  when (>f count 10000)			; development only?
	    do (cerror "Continue" "Probable infinite loop while inserting junction")
	  while (connections junction-block)
	  do (loop for connection being the connections of junction-block
		   return (delete-connection connection)))
    
    (add-subblock junction-block (superblock? loose-end))
    
    (let* ((noting-changes-to-kb-p nil)
	   (junction-block-connection-1 junction-connection)
	   (connection-1-connection-frame-or-class
	     (connection-frame-or-class junction-block-connection-1))
	   (connection-1-transient-p
	     (transient-connection-p junction-block-connection-1))
	   (connection-1-connection-class
	     (get-connection-class-given-connection-frame-or-class
	       connection-1-connection-frame-or-class))
	   #+connections-v2
	   (connection-1-input-end-object
	     (input-end-object junction-block-connection-1))
	   (connection-1-output-end-object
	     (output-end-object junction-block-connection-1))
	   (junction-block-connection-2 (make-connection))
	   junction-block-connection-1-last-delta
	   junction-block-connection-2-first-delta
	   (junction-block-connection-2-connection-frame? nil)
	   (junction-on-corner-p nil))    
      
      (when (not connection-1-transient-p)
	(set-connection-permanently-changed junction-block-connection-2))
      
      ;; set up new connections
      (setf (frame-serial-number-for-connection junction-block-connection-2)
	    (copy-frame-serial-number (increment-current-frame-serial-number)))
      (decache-roles-for-entities-related-to-this-connection
	junction-block-connection-1)
      (decache-roles-for-entities-related-to-this-connection
	connection-being-dragged)

      #-connections-v2
      (setf (connections junction-block)
	    (slot-value-list
	      'junction-block-connection-1 junction-block-connection-1
	      'junction-block-connection-2 junction-block-connection-2
	      'junction-block-connection-3 connection-being-dragged))
      #+connections-v2
      (let ((connection-table (make-connection-item-table))
	    (connection-item-1 (make-connection-item junction-block-connection-1))
	    (connection-item-2 (make-connection-item junction-block-connection-2))
	    (connection-item-3 (make-connection-item connection-being-dragged)))
	(case (get-direction-of-connection junction-block-connection-1
					   connection-1-input-end-object)
	  (output
	   (setf (connection-item-input-names connection-item-1)
		 (slot-value-list 'junction-block-connection-1)))
	  (t
	   (setf (connection-item-output-names connection-item-1)
		 (slot-value-list 'junction-block-connection-1))))
	(case (get-direction-of-connection junction-block-connection-2
					   connection-1-output-end-object)
	  (output
	   (setf (connection-item-input-names connection-item-2)
		 (slot-value-list 'junction-block-connection-2)))
	  (t
	   (setf (connection-item-output-names connection-item-2)
		 (slot-value-list 'junction-block-connection-2))))
	(case (get-direction-of-connection connection-being-dragged loose-end)
	  (input
	   (setf (connection-item-input-names connection-item-3)
		 (slot-value-list 'junction-block-connection-3)))
	  (t
	   (setf (connection-item-output-names connection-item-3)
		 (slot-value-list 'junction-block-connection-3))))
	(setf (get-connection-item junction-block-connection-1 connection-table)
	      connection-item-1)
	(setf (get-connection-item junction-block-connection-2 connection-table)
	      connection-item-2)
	(setf (get-connection-item connection-being-dragged connection-table)
	      connection-item-3)
	(setf (connections junction-block) connection-table))

      (set-output-end-of-connection-1
	junction-block-connection-2 connection-1-output-end-object
	(output-end-position junction-block-connection-1))
      (set-input-end-of-connection-1
	junction-block-connection-2 junction-block
	(combine-side-and-position-on-side-for-end-position
	  output-end-side junction-block-half-width))
      (set-output-end-of-connection-1
	junction-block-connection-1 junction-block
	(combine-side-and-position-on-side-for-end-position
	  input-end-side junction-block-half-width))
      
      (when connection-1-transient-p
	(set-transient-connection junction-block-connection-2))
      
      (cond
	((or connection-1-transient-p
	     (always-instantiate-connection-frame-for-this-class?
	       connection-1-connection-class))
	 (setq junction-block-connection-2-connection-frame?
	       (make-new-connection-frame-for-connection
		 junction-block-connection-2 connection-1-connection-class))
	 (activate-connection-frame-if-appropriate
	   junction-block-connection-2-connection-frame? (superblock? loose-end)))
	(t
	 (setf (connection-frame-or-class junction-block-connection-2)
	       connection-1-connection-class)))
      
      (if (connection-not-directed? junction-block-connection-1)
	  (set-connection-not-directed junction-block-connection-2)
	  (set-connection-directed junction-block-connection-2))    
      
      (clone-connection-attributes-plist
	junction-block-connection-1 junction-block-connection-2)

      (replace-connection-in-block
	connection-1-output-end-object
	junction-block-connection-1
	junction-block-connection-2)
      (when (and g2-has-v5-mode-windows-p)
 	(send-ws-representations-item-insert-as-subblock
 	  junction-block-connection-2 junction-block nil))
      (cond ((eq (input-end-object connection-being-dragged) loose-end)
	     (set-input-end-of-connection-1
	       connection-being-dragged junction-block 
	       (combine-side-and-position-on-side-for-end-position
		 connection-being-dragged-end-side
		 junction-block-half-width))
	     (when (and g2-has-v5-mode-windows-p)
	       (send-ws-representations-item-layer-change
		 (get-or-make-connection-frame-and-activate-if-appropriate
		   connection-being-dragged)
		 (superblock? loose-end)
		 (get-or-make-connection-frame-and-activate-if-appropriate
		   junction-block-connection-2))))
	    (t (set-output-end-of-connection-1
		 connection-being-dragged junction-block
		 (combine-side-and-position-on-side-for-end-position
		   connection-being-dragged-end-side
		   junction-block-half-width))))

      (update-runtime-structures-according-to-edit junction-block-connection-1)
      (update-runtime-structures-according-to-edit connection-being-dragged)
      (when junction-block-connection-2-connection-frame?
	(update-runtime-structures-according-to-edit
	  junction-block-connection-2-connection-frame?))
      
      ;; Note that since junction-block and junction-block-connection-2
      ;; have just been created at this point (by make-junction and
      ;; make-connection respectively), there are no runtime structures
      ;; effected by it and so there is no need to call
      ;; update-runtime-structures-according-to-edit for it.  For this
      ;; reason also, it is not necessary to decache roles for
      ;; junction-block-connection-2.
      
      (cond
	((fixnump intercept-or-corner)
	 (let ((delta
		 (if (>w intercept-or-corner 0)
		     junction-block-half-width
		     (-w junction-block-half-width))))
	   (setq junction-block-connection-1-last-delta
		 (-w intercept-or-corner delta))
	   (setq junction-block-connection-2-first-delta
		 (-w (-w (car rest-of-deltas) intercept-or-corner) delta))))
	(t
	 ;; intercept-or-corner is END-CORNER or BEGIN-CORNER
	 (setq junction-block-connection-1-last-delta (car rest-of-deltas))
	 (setq junction-block-connection-2-first-delta (cadr rest-of-deltas))
	 (setq rest-of-deltas (cdr rest-of-deltas))
	 (setq junction-on-corner-p t)))
      
      ;; set up new deltas for two connections
      (cond
	((eq (delta-or-deltas junction-block-connection-1)
	     rest-of-deltas)
	 (setf (delta-or-deltas junction-block-connection-1)
	       junction-block-connection-1-last-delta)
	 (setf (car rest-of-deltas)
	       junction-block-connection-2-first-delta)
	 (setf (delta-or-deltas junction-block-connection-2)
	       rest-of-deltas))
	(t
	 (loop for rest-of-old-deltas 
	       on (delta-or-deltas junction-block-connection-1)
	       until (eq (cdr rest-of-old-deltas)
			 rest-of-deltas)
	       finally
		 (setf (car rest-of-deltas)
		       junction-block-connection-2-first-delta)
		 (setf (delta-or-deltas junction-block-connection-2)
		       rest-of-deltas)
		 (cond
		   (junction-on-corner-p
		    (setf (car rest-of-old-deltas)
			  junction-block-connection-1-last-delta)
		    (setf (cdr rest-of-old-deltas)
			  nil))
		   (t
		    (setf (cdr rest-of-old-deltas)
			  (slot-value-list
			    junction-block-connection-1-last-delta)))))))
      
      (remove-redundant-deltas-from-connection junction-block-connection-1)
      (remove-redundant-deltas-from-connection junction-block-connection-2)
      (send-ws-representations-connection-moved junction-block-connection-2))))

;; Note that the call to replace-connection-in-block ensures that subworkspace
;; connection post pointers are set up correctly (replace-connection-in-block
;; calls determine-subworkspace-connection-posts-for-object).




;;; `Distance-to-allow-if-connection-is-fat?' is a predicate that returns
;;; a useful value in the non-nil case. Its purpose is to correct a problem
;;; in mouse selection on 'fat' connections. These are connections where the
;;; apparent size of the connection (as determined by the size of its interior
;;; and exteriors) is larger than the leeway that's used when calculating
;;; where the mouse is (see discussion around find-object-near-mouse).
;;; In that situation we had a long standing bug, HQ-721907, where people
;;; could only select a connection when they clicked in its center.

(defun-substitution-macro distance-to-allow-if-connection-is-fat?
    (connection reference-distance)
  (let ((half-width-of-connection
	  (halfw (compute-connection-width-given-connection-frame-or-class
		   (connection-frame-or-class connection)))))
    (when (>w half-width-of-connection reference-distance)
      half-width-of-connection)))


;;; `Find-vector-length-from-point-to-block-connections-if-within-limit'
;;; will return a connection and a distance-from-point if the distance is
;;; not greater than standard-maximum-distance-to-allow or, in the case of
;;; fat connections, the connection's half-width. If it is, nil will be
;;; returned.

(defun find-vector-length-from-point-to-block-connections-if-within-limit
    (x-in-workspace y-in-workspace
     block
     standard-maximum-distance-to-allow
     objects-to-not-consider?)
  ;; objects-to-not-consider? is a special!
  (if (or (null objects-to-not-consider?)
	  (not (memq block objects-to-not-consider?)))
      (loop with nearest-connection? = nil
	    with nearest-distance? = nil
	    with maximum-distance-to-allow
	    for connection being the output-connections of block
	    doing
	(setq maximum-distance-to-allow
	      (or (distance-to-allow-if-connection-is-fat?
		    connection standard-maximum-distance-to-allow)
		  standard-maximum-distance-to-allow))
	(cond
	  ((or (null objects-to-not-consider?)
	       (not (memq connection objects-to-not-consider?)))

	   ;; We're just temporarily changing the connection deltas, so do not
	   ;; invalidate the indexing.
	   (let ((geometric-change-to-connection-is-temporary-p t))

	     (add-missing-deltas-to-connection connection)
	     (multiple-value-bind
		 (this-connection-nearest-connection?
		   this-connection-nearest-distance?)
		 (find-vector-length-from-point-to-connection-if-within-limit
		   connection
		   x-in-workspace y-in-workspace maximum-distance-to-allow)
	       (if this-connection-nearest-distance?
		   (if (or (null nearest-distance?)
			   (<w this-connection-nearest-distance?
			       nearest-distance?))
		       (setq nearest-distance?
			     this-connection-nearest-distance?
			     nearest-connection?
			     this-connection-nearest-connection?))))
	     (remove-redundant-deltas-from-connection connection))))
	    finally
	      (return (values nearest-connection? nearest-distance?)))))

;; If there is a tie for two connections, then the first one will be
;; returned.



;;; `Find-vector-length-from-point-to-connection-if-within-limit' takes as
;;; arguments connection, x-in-workspace and y-in-workspace of point, and
;;; maximum-distance-to-allow.  If the point is within
;;; maximum-distance-to-allow of the connection, then connection, distance,
;;; intercept-or-corner, rest-of-deltas, x-position-of-intercept-or-corner,
;;; y-position-of-intercept-or-corner, and orientation-horizontal-p will be
;;; returned, else nil will be returned.  Distance, intercept-or-corner,
;;; x-position-of-intercept-or-corner, and y-position-of-intercept-or-corner
;;; are values returned by find-vector-length-from-point-to-connection-link for
;;; the link closest to the point (see documentation for
;;; find-vector-length-from-point-to-connection-link).  Rest-of-deltas is the
;;; list of deltas for links starting from the link closest to the point.
;;; Orientation-horizontal-p pertains to this link.

(defun find-vector-length-from-point-to-connection-if-within-limit 
       (connection
	x-in-workspace y-in-workspace maximum-distance-to-allow)
  (let* ((nearest-connection? nil)
	 (nearest-distance? nil)
	 (nearest-intercept-or-corner? nil)
	 (nearest-rest-of-deltas? nil)
	 (nearest-x-position-of-intercept-or-corner? nil)
	 (nearest-y-position-of-intercept-or-corner? nil)
	 (nearest-orientation-horizontal-p nil)
	 (connection-frame-or-class ; not currently used
	   (connection-frame-or-class connection))
	 (intercept-or-corner? nil)
	 (x-position-of-intercept-or-corner? nil)
	 (y-position-of-intercept-or-corner? nil)
	 (distance-from-point? nil)
	 (input-end-object
	   (input-end-object connection))
	 (input-end-position
	   (input-end-position connection))
	 (input-end-side
	   (get-side-given-end-position
	     input-end-position))
	 (input-end-position-on-side
	   (get-position-on-side-given-end-position
	     input-end-position))
	 (input-end-x-position
	   (+w (left-edge-of-block input-end-object)
	       (case input-end-side
		 (left 0)
		 (right (+w (width-of-block input-end-object) 1))
		 (t  ; if top or bottom
		  input-end-position-on-side))))
	 (input-end-y-position
	   (+w (top-edge-of-block input-end-object)
	       (case input-end-side
		 (top 0)
		 (bottom (+w (height-of-block input-end-object) 1))
		 (t  ; if right or left
		  input-end-position-on-side))))
	 ;; The 1+ offset is used here so that the stubs won't xor
	 ;; with the edge of the rectangle.  This will not be necessary 
	 ;; when the capability to draw stubs into the rectangle until
	 ;; they meet a non-zero pixel is implemented.

	 (connection-diagonal-p
	   (connection-diagonal-p connection))

	 (initial-orientation-horizontal-p
	   (initial-orientation-horizontal-p input-end-side))

	 (delta-or-deltas
	   (delta-or-deltas
	     connection)))

    connection-frame-or-class
    
    (loop with rest-of-deltas = delta-or-deltas
	  with stable-axis-position
	    = (if initial-orientation-horizontal-p
		  input-end-y-position
		  input-end-x-position)
	  with variable-axis-begin-position
	    = (if initial-orientation-horizontal-p
		  input-end-x-position
		  input-end-y-position)
	  with vertex-x = input-end-x-position
	  with vertex-y = input-end-y-position

	  as current-delta
	     = (first rest-of-deltas)
	  as next-delta
	     = (second rest-of-deltas)
	  as orientation-horizontal-p
	     = initial-orientation-horizontal-p
	     then (not orientation-horizontal-p)
	  as variable-axis-end-position
	     = (+w variable-axis-begin-position
		   current-delta)
	  as variable-axis-point-position
	     = (if orientation-horizontal-p
		   x-in-workspace
		   y-in-workspace)
	  as stable-axis-point-position
	     = (if orientation-horizontal-p
		   y-in-workspace
		   x-in-workspace)
	  as next-x-and-y-vertex-available?
	     = t then (not next-x-and-y-vertex-available?)

	  until (not next-delta)
	  do

      (multiple-value-setq 
	(distance-from-point? intercept-or-corner?
	 x-position-of-intercept-or-corner? 
	 y-position-of-intercept-or-corner?
	 vertex-x vertex-y)
	(if connection-diagonal-p
	    (find-vector-length-from-point-to-diagonal-connection-link
	      x-in-workspace y-in-workspace
	      vertex-x vertex-y
	      maximum-distance-to-allow orientation-horizontal-p
	      current-delta next-delta next-x-and-y-vertex-available?)
	    (find-vector-length-from-point-to-connection-link
	      variable-axis-point-position stable-axis-point-position
	      variable-axis-begin-position variable-axis-end-position
	      stable-axis-position maximum-distance-to-allow
	      current-delta orientation-horizontal-p)))
      (if distance-from-point?
	  (if (or (null nearest-distance?)
		  (<w distance-from-point? nearest-distance?))
	      (setq nearest-distance? distance-from-point?
		    nearest-connection? connection
		    nearest-intercept-or-corner? intercept-or-corner?
		    nearest-rest-of-deltas? rest-of-deltas
		    nearest-x-position-of-intercept-or-corner? 
		    x-position-of-intercept-or-corner?
		    nearest-y-position-of-intercept-or-corner? 
		    y-position-of-intercept-or-corner?
		    nearest-orientation-horizontal-p orientation-horizontal-p)))

      (setq variable-axis-begin-position stable-axis-position
	    stable-axis-position variable-axis-end-position)
      (setq rest-of-deltas
	    (cdr rest-of-deltas))

	  finally
	    (progn
	      (multiple-value-setq 
		(distance-from-point? intercept-or-corner?
		 x-position-of-intercept-or-corner? 
		 y-position-of-intercept-or-corner?
		 vertex-x vertex-y)
		(if connection-diagonal-p
		    (find-vector-length-from-point-to-diagonal-connection-link
		      x-in-workspace y-in-workspace
		      vertex-x vertex-y
		      maximum-distance-to-allow orientation-horizontal-p
		      current-delta 0 next-x-and-y-vertex-available?)
		    (find-vector-length-from-point-to-connection-link
		      variable-axis-point-position stable-axis-point-position
		      variable-axis-begin-position variable-axis-end-position
		      stable-axis-position maximum-distance-to-allow
		      current-delta orientation-horizontal-p)))
	      (if distance-from-point?
		  (if (or (null nearest-distance?)
			  (<w distance-from-point? nearest-distance?))
		      (setq nearest-distance? distance-from-point?
			    nearest-connection? connection
			    nearest-intercept-or-corner? intercept-or-corner?
			    nearest-rest-of-deltas? rest-of-deltas
			    nearest-x-position-of-intercept-or-corner? 
			    x-position-of-intercept-or-corner?
			    nearest-y-position-of-intercept-or-corner? 
			    y-position-of-intercept-or-corner?
			    nearest-orientation-horizontal-p orientation-horizontal-p)))))

    (values nearest-connection? nearest-distance? nearest-intercept-or-corner?
	    nearest-rest-of-deltas? 
	    nearest-x-position-of-intercept-or-corner?
	    nearest-y-position-of-intercept-or-corner?
	    nearest-orientation-horizontal-p)))

;; Find-vector-length-from-point-to-connection-if-within-limit requires
;; that all deltas be present in (delta-or-deltas connection).  Thus,
;; the function that calls it must use add-missing-deltas-to-connection
;; and remove-redundant-deltas-from-connection to convert
;; (delta-or-deltas connection).



(defun find-vector-length-from-point-to-diagonal-connection-link
       (x-in-workspace y-in-workspace
	vertex-x vertex-y
	maximum-distance-to-allow orientation-horizontal-p
	current-delta next-delta next-x-and-y-vertex-available?)
  (if next-x-and-y-vertex-available?
      (multiple-value-bind 
	(new-vertex-x new-vertex-y)
	  (compute-new-vertex
	    vertex-x vertex-y orientation-horizontal-p 
	    current-delta next-delta nil)
	(find-vector-length-from-point-to-diagonal-connection-link-1
	  x-in-workspace y-in-workspace
	  vertex-x vertex-y new-vertex-x new-vertex-y
	  maximum-distance-to-allow))
      (values nil nil nil nil vertex-x vertex-y)))



(defun find-vector-length-from-point-to-diagonal-connection-link-1
       (x-in-workspace y-in-workspace
	vertex-x vertex-y new-vertex-x new-vertex-y
	maximum-distance-to-allow)
  (let* ((switch-point-order? (<w new-vertex-x vertex-x))
	 x1 y1 x2 y2 delta-x delta-y m1 m2 b1 b2 x3 y3
	 fx1 fy1 fx2
	 x-intercept y-intercept distance-from-point?
	 (intercept-or-corner? nil)
	 (x-position-of-intercept-or-corner? nil)
	 (y-position-of-intercept-or-corner? nil)
	 (try-for-corner? nil))
    (if switch-point-order?
	(setq x1 new-vertex-x
	      y1 new-vertex-y
	      x2 vertex-x
	      y2 vertex-y)
	(setq x1 vertex-x
	      y1 vertex-y
	      x2 new-vertex-x
	      y2 new-vertex-y))
    (setq delta-x (-w x2 x1) 
	  delta-y (-w y2 y1))
    (cond
      ((=w delta-x 0)
       (if (or (<=w vertex-y y-in-workspace new-vertex-y)
	       (<=w new-vertex-y y-in-workspace vertex-y))
	   (setq distance-from-point? (absw (-w x1 x-in-workspace))
		 intercept-or-corner? 0
		 x-position-of-intercept-or-corner? x1
		 y-position-of-intercept-or-corner? y-in-workspace)
	   (setq try-for-corner? t)))
      ((=w delta-y 0)
       (if (or (<=w vertex-x x-in-workspace new-vertex-x)
	       (<=w new-vertex-x x-in-workspace vertex-x))
	   (setq distance-from-point? (absw (-w y1 y-in-workspace))
		 intercept-or-corner? 0
		 x-position-of-intercept-or-corner? x-in-workspace
		 y-position-of-intercept-or-corner? y1)
	   (setq try-for-corner? t)))
      (t
       (with-temporary-gensym-float-creation 
	 find-vector-length-from-point-to-diagonal-link
	 
	 (setq fx1 (coerce-to-gensym-float x1)
	       fy1 (coerce-to-gensym-float y1)
	       fx2 (coerce-to-gensym-float x2)
	       delta-x (coerce-to-gensym-float delta-x)
	       delta-y (coerce-to-gensym-float delta-y)
	       x3 (coerce-to-gensym-float x-in-workspace)
	       y3 (coerce-to-gensym-float y-in-workspace))
	 (setq m1 (/e delta-y delta-x)		       ; slope of line
	       m2 (-e (/e delta-x delta-y))	       ; slope of intercept of line
	       b1 (-e fy1			       ; y intercept of line
		      (/e (*e delta-y fx1) delta-x))
	       b2 (+e y3			       ; y intercept of intercept of line
		      (/e (*e delta-x x3) delta-y)))
	 (setq x-intercept
	       (/e (-e b2 b1) (-e m1 m2))
	       y-intercept
	       (+e (*e m1 x-intercept) b1))
	 (if (<=e fx1 x-intercept fx2)
	     (setq distance-from-point?
		   (let ((delta-x (-e x3 x-intercept))
			 (delta-y (-e y3 y-intercept)))
		     (round (float-distance delta-x delta-y)))
		   intercept-or-corner? 0
		   x-position-of-intercept-or-corner? (round x-intercept)
		   y-position-of-intercept-or-corner? (round y-intercept))
	     (setq try-for-corner? t)))))
    (when try-for-corner?
      (setq distance-from-point?
	    (minw (vector-distance-in-workspace
		    (absw (-w x1 x-in-workspace))
		    (absw (-w y1 y-in-workspace)))
		  (vector-distance-in-workspace
		    (absw (-w x2 x-in-workspace))
		    (absw (-w y2 y-in-workspace))))))
    (if (and distance-from-point?
	     (<= distance-from-point?
		 maximum-distance-to-allow))
	(values distance-from-point? intercept-or-corner?
		x-position-of-intercept-or-corner? 
		y-position-of-intercept-or-corner?
		new-vertex-x new-vertex-y)
	(values nil nil nil nil
		new-vertex-x new-vertex-y))))



;;; Find-vector-length-from-point-to-connection-link takes as arguments
;;; variable-axis and stable-axis positions of the point,
;;; variable-axis-begin, variable-axis-end, and stable-axis positions
;;; of the link, maximum distance to allow, the delta for the link, and 
;;; orientation-horizontal-p for the link.  If the point is within the
;;; maximum distance to allow for the link, then distance-from-point,
;;; intercept-or-corner, x-position-of-intercept-or-corner, and
;;; y-position-of-intercept-or-corner will be returned as values, else
;;; nil will be returned.  If the point is not near the beginning or
;;; end of the link, intercept-or-corner will be an integer, otherwise
;;; it will be 'begin-corner or 'end-corner.  The last two values
;;; specify the x and y position of the intercept or corner.

(defun find-vector-length-from-point-to-connection-link
       (variable-axis-point-position stable-axis-point-position
	variable-axis-begin-position variable-axis-end-position
	stable-axis-position maximum-distance-to-allow
	current-delta orientation-horizontal-p)
  (let ((distance-from-point? nil)
	(intercept-or-corner? nil)
	(x-position-of-intercept-or-corner? nil)
	(y-position-of-intercept-or-corner? nil))
    (if (>w current-delta 0)
	(if (>=w variable-axis-end-position 
		 variable-axis-point-position
		 variable-axis-begin-position)
	    (setq distance-from-point?
		  (absw (-w stable-axis-point-position
			    stable-axis-position))
		  intercept-or-corner?
		  (-w variable-axis-point-position
		      variable-axis-begin-position)
		  x-position-of-intercept-or-corner?
		  (if orientation-horizontal-p
		      variable-axis-point-position
		      stable-axis-position)
		  y-position-of-intercept-or-corner?
		  (if orientation-horizontal-p
		      stable-axis-position
		      variable-axis-point-position))
	    (cond
	      ((and (<w (absw (-w stable-axis-point-position
				  stable-axis-position))
			maximum-distance-to-allow)
		    (<w
		      (if (>w variable-axis-point-position
			      variable-axis-end-position)
			  (absw (-w variable-axis-point-position
				    variable-axis-end-position))
			  (absw (-w variable-axis-begin-position
				    variable-axis-point-position)))
		      maximum-distance-to-allow))
	       (setq distance-from-point?
		     (vector-distance-in-workspace
		       (absw
			 (-w stable-axis-point-position
			     stable-axis-position))
		       (absw
			 (-w variable-axis-point-position
			     (if (>w variable-axis-point-position
				     variable-axis-end-position)
				 variable-axis-end-position
				 variable-axis-begin-position)))))
	       
	       (if (>w variable-axis-point-position
		       variable-axis-end-position)
		   (setq intercept-or-corner? 'end-corner
			 x-position-of-intercept-or-corner?
			 (if orientation-horizontal-p
			     variable-axis-end-position
			     stable-axis-position)
			 y-position-of-intercept-or-corner?
			 (if orientation-horizontal-p
			     stable-axis-position
			     variable-axis-end-position))
		   (setq intercept-or-corner? 'begin-corner
			 x-position-of-intercept-or-corner?
			 (if orientation-horizontal-p
			     variable-axis-begin-position
			     stable-axis-position)
			 y-position-of-intercept-or-corner?
			 (if orientation-horizontal-p
			     stable-axis-position
			     variable-axis-begin-position))))))
	(if (<=w variable-axis-end-position 
		 variable-axis-point-position
		 variable-axis-begin-position)
	    (setq distance-from-point?
		  (absw (-w stable-axis-point-position
			    stable-axis-position))
		  intercept-or-corner?
		  (-w variable-axis-point-position
		      variable-axis-begin-position)
		  x-position-of-intercept-or-corner?
		  (if orientation-horizontal-p
		      variable-axis-point-position
		      stable-axis-position)
		  y-position-of-intercept-or-corner?
		  (if orientation-horizontal-p
		      stable-axis-position
		      variable-axis-point-position))
	    (cond
	      ((and (<w (absw (-w stable-axis-point-position
				   stable-axis-position))
			 maximum-distance-to-allow)
		     (<w
		       (if (<w variable-axis-point-position
			       variable-axis-end-position)
			   (absw (-w variable-axis-point-position
				     variable-axis-end-position))
			   (absw (-w variable-axis-begin-position
				     variable-axis-point-position)))
		       maximum-distance-to-allow))
	       (setq distance-from-point?
		     (vector-distance-in-workspace
		       (absw
			 (-w stable-axis-point-position
			     stable-axis-position))
		       (absw
			 (-w variable-axis-point-position
			     (if (<w variable-axis-point-position
				     variable-axis-end-position)
				 variable-axis-end-position
				 variable-axis-begin-position)))))
	       (if (<w variable-axis-point-position
		       variable-axis-end-position)
		   (setq intercept-or-corner? 'end-corner
			 x-position-of-intercept-or-corner?
			 (if orientation-horizontal-p
			     variable-axis-end-position
			     stable-axis-position)
			 y-position-of-intercept-or-corner?
			 (if orientation-horizontal-p
			     stable-axis-position
			     variable-axis-end-position))
		   (setq intercept-or-corner? 'begin-corner
			 x-position-of-intercept-or-corner?
			 (if orientation-horizontal-p
			     variable-axis-begin-position
			     stable-axis-position)
			 y-position-of-intercept-or-corner?
			 (if orientation-horizontal-p
			     stable-axis-position
			     variable-axis-begin-position)))))))
    (if distance-from-point?
	(if (<=w distance-from-point?
		 maximum-distance-to-allow)
	    (values distance-from-point? intercept-or-corner?
		    x-position-of-intercept-or-corner? 
		    y-position-of-intercept-or-corner?)))))




;;; `Add-missing-deltas-to-connection' takes a connection as argument, computes
;;; the omitted deltas, and conses these onto the end of delta-or-deltas of the
;;; connection.  The full list is also returned.

(defun add-missing-deltas-to-connection (connection)
  (let ((noting-changes-to-kb-p nil))
    (with-connection
      connection nil t nil
      ((delta-or-deltas
	 (delta-or-deltas connection))
       missing-link-delta-1
       missing-link-delta-2)
      (multiple-value-bind
	(last-delta-anchor-x last-delta-anchor-y
	 last-delta-orientation-horizontal-p rest-of-deltas)
	  (compute-last-delta-anchor-point connection)
	(declare (ignore rest-of-deltas))
	(setf (delta-or-deltas connection)
	      (cond
		((null delta-or-deltas)
		 (if last-delta-orientation-horizontal-p
		     (setq missing-link-delta-1
			   (-w output-end-x-position
			       last-delta-anchor-x)
			   missing-link-delta-2
			   (-w output-end-y-position
			       last-delta-anchor-y))
		     (setq missing-link-delta-1
			   (-w output-end-y-position
			       last-delta-anchor-y)
			   missing-link-delta-2
			   (-w output-end-x-position
			       last-delta-anchor-x)))
		 (if (=w missing-link-delta-2 0)
		     (slot-value-list missing-link-delta-1)
		     (slot-value-list missing-link-delta-1 missing-link-delta-2)))
		((atom delta-or-deltas)
		 (if last-delta-orientation-horizontal-p
		     (setq missing-link-delta-1
			   (-w output-end-y-position
			       last-delta-anchor-y)
			   missing-link-delta-2
			   (-w output-end-x-position
			       last-delta-anchor-x))
		     (setq missing-link-delta-1
			   (-w output-end-x-position
			       last-delta-anchor-x)
			   missing-link-delta-2
			   (-w output-end-y-position
			       last-delta-anchor-y)))
		 (slot-value-cons 
		   delta-or-deltas
		   (slot-value-list missing-link-delta-1 missing-link-delta-2)))
		(t		 
		 (if last-delta-orientation-horizontal-p
		     (setq missing-link-delta-1
			   (-w output-end-y-position
			       last-delta-anchor-y)
			   missing-link-delta-2
			   (-w output-end-x-position
			       last-delta-anchor-x))
		     (setq missing-link-delta-1
			   (-w output-end-x-position
			       last-delta-anchor-x)
			   missing-link-delta-2
			   (-w output-end-y-position
			       last-delta-anchor-y)))
		 (nconc delta-or-deltas
			(slot-value-list missing-link-delta-1 missing-link-delta-2)
			))))))))




;;; `Remove-redundant-deltas-from-connection' takes a connection as argument,
;;; and undoes what add-missing-deltas-to-connection-does; it removes the last
;;; two deltas from delta-or-deltas of connection.

(defun remove-redundant-deltas-from-connection (connection)
  (let ((noting-changes-to-kb-p nil))
    (let ((delta-or-deltas
	    (delta-or-deltas connection)))
      (cond
	((or (atom delta-or-deltas)
	     (null (cdr delta-or-deltas))
	     (null (cddr delta-or-deltas)))
	 (if (consp delta-or-deltas)
	     (reclaim-slot-value-list delta-or-deltas))
	 (setf (delta-or-deltas connection) nil))
	((null (cdddr delta-or-deltas))
	 (setf (delta-or-deltas connection) 
	       (prog1 (car delta-or-deltas)
		 (reclaim-slot-value-list delta-or-deltas))))
	(t
	 (loop for rest-of-deltas
		   on delta-or-deltas
	       until (null (cdddr rest-of-deltas))
	       finally 
		 (reclaim-slot-value-list (cdr rest-of-deltas))
		 (setf (cdr rest-of-deltas) nil))
	 delta-or-deltas)))))

(defun remove-last-delta-from-connection (connection)
  (let ((noting-changes-to-kb-p nil))
    (let ((delta-or-deltas
	    (delta-or-deltas connection)))
      (cond
	((or (atom delta-or-deltas)
	     (null (cdr delta-or-deltas)))
	 (if (consp delta-or-deltas)
	     (reclaim-slot-value-list delta-or-deltas))
	 (setf (delta-or-deltas connection) nil))
	((null (cddr delta-or-deltas))
	 (setf (delta-or-deltas connection) 
	       (prog1 (car delta-or-deltas)
		 (reclaim-slot-value-list delta-or-deltas))))
	(t
	 (loop for rest-of-deltas
		   on delta-or-deltas
	       until (null (cddr rest-of-deltas))
	       finally 
		 (reclaim-slot-value-list (cdr rest-of-deltas))
		 (setf (cdr rest-of-deltas) nil))
	 delta-or-deltas)))))


;;; `thing-or-things-pop' exists for a purpose.  Suppose you want to
;;; iterate over the set of elements stored in the ridiculous, "it's
;;; a thing, or a list of things", format that is so common in parts
;;; of G2's implementation.  Well, then thing-or-things-pop is for you.
;;; Why this macro is so cool maybe I'll store all my lists this way
;;; in the future   NOT!


(defmacro thing-or-things-pop (x)
  (unless (symbolp x)
    (error "Don't call this on generalized variables.  It's just a hack"))
  `(if (consp ,x)
       (pop ,x)
       (shiftf ,x nil)))

;;; `connection-vertices-in-workspace' is a new function (3/97)
;;; that really just gets a list of (x . y) pairs describing the
;;; connection in ws coordinates.  The list is freshly consed.

(defun-simple connection-vertices-in-workspace (connection)
  (let* ((input (input-end-object connection))
	 (output (output-end-object connection))
	 (input-end-position (input-end-position connection))
	 (output-end-position (output-end-position connection))
	 (diagonal-p (connection-diagonal-p connection))
	 (input-end-horizontal-p (horizontal-end-position-p input-end-position))
	 (output-end-horizontal-p (horizontal-end-position-p output-end-position)))
    (multiple-value-bind (start-x start-y)
	(determine-connection-terminal-coordinate
	  input input-end-position)
      (multiple-value-bind (end-x end-y)
	  (determine-connection-terminal-coordinate
	    output output-end-position)
	(cond
	  ;; "no kinks" case
	  ((or (and (=f start-x end-x) (not input-end-horizontal-p) (not output-end-horizontal-p))
	       (and (=f start-y end-y) input-end-horizontal-p output-end-horizontal-p))
	   (gensym-list (gensym-cons start-x start-y)
			(gensym-cons end-x end-y)))
	  (t
	   (loop with res = '()
		 with x = start-x
		 with y = start-y
		 with deltas = (delta-or-deltas connection)
		 with horizontal-p
		   = (horizontal-end-position-p input-end-position)
		 do
	     (gensym-push (gensym-cons x y) res)
	     (when (null deltas)
	       (loop-finish))
	     (cond
	       (diagonal-p
		(if horizontal-p
		    (setf x (+w (thing-or-things-pop deltas) x))
		    (setf y (+w (thing-or-things-pop deltas) y)))
		(cond (deltas
		       (if horizontal-p			   
			   (setf y (+w (thing-or-things-pop deltas) y))
			   (setf x (+w (thing-or-things-pop deltas) x))))
		      (t
		       (if horizontal-p
			   (setf y end-y)
			   (setf x end-x)))))
	       (t
		(setf x (if horizontal-p (+w (thing-or-things-pop deltas) x) x))
		(setf y (if horizontal-p y (+w (thing-or-things-pop deltas) y)))))
	     (unless diagonal-p
	       (setf horizontal-p (not horizontal-p)))
		 finally
		   (unless diagonal-p
		     (if horizontal-p
			 (gensym-push (gensym-cons end-x y) res)
			 (gensym-push (gensym-cons x end-y) res)))
		   (gensym-push (gensym-cons end-x end-y) res)
		   (return (nreverse res)))))))))


(defun determine-connection-terminal-coordinate (item end-position)
  (let ((side (get-side-given-end-position end-position))
	(offset (get-position-on-side-given-end-position end-position))
	(block-left (left-edge-of-block item))
	(block-top (top-edge-of-block item))
	(block-right (right-edge-of-block item))
	(block-bottom (bottom-edge-of-block item)))
    (case side
      (left   (values block-left (+w block-top offset)))
      (top    (values (+w block-left offset) block-top))
      (right  (values block-right (+w block-top offset)))
      (bottom (values (+w block-left offset) (+w block-bottom 1))))))

	     


;;; `Compute-dragged-connection-anchor-point' takes a connection and a block as
;;; arguments and returns connection-anchor-point-x, and
;;; connection-anchor-point-y.  It handles all cases of delta-or-deltas of
;;; connections.  The block may be the input or the output end-object of the
;;; connection.

(defun compute-dragged-connection-anchor-point
       (connection block)
  (cond
    ((eq (output-end-object connection) block)
     (compute-last-delta-anchor-point connection))
    (t
     (with-connection
       connection t t t 
       ((delta-or-deltas
	  (delta-or-deltas connection)))
       (cond
	 ((null delta-or-deltas)
	  (values output-end-x-position
		  output-end-y-position))
	 ((atom delta-or-deltas)
	  (if initial-orientation-horizontal-p
	      (values
		(+w input-end-x-position
		    delta-or-deltas)
		output-end-y-position)
	      (values
		output-end-x-position
		(+w input-end-y-position
		    delta-or-deltas))))
	 (t					       ; if a cons with length of at least 2
	  (if initial-orientation-horizontal-p
	      (values
		(+w input-end-x-position
		    (car delta-or-deltas))
		(+w input-end-y-position
		    (cadr delta-or-deltas)))
	      (values
		(+w input-end-x-position
		    (cadr delta-or-deltas))
		(+w input-end-y-position
		    (car delta-or-deltas))))))))))



;;; `Compute-last-delta-anchor-point' returns last-delta-anchor-x,
;;; last-delta-anchor-y, last-delta-orientation-horizontal-p, and
;;; rest-of-deltas.  It handles all cases of delta-or-deltas of connections.
;;; It loops throught the deltas, from input-end to output end until the last
;;; delta is reached.  It is used by functions like add-bend-to-connection
;;; which may have to know the x and y coordinates of the point at the end of
;;; the last delta in (delta-or-deltas connection).
;;;
;;; By default, the connection's deltas come from the connection's
;;; delta-or-delta's slot.  But an override value can be supplied as the second
;;; argument and it will be used instead.

(defun compute-last-delta-anchor-point
       (connection &optional override-delta-or-deltas)
  (with-connection
    connection t nil t
    ((delta-or-deltas
       (or override-delta-or-deltas
	   (delta-or-deltas connection))))
    (cond
      ((null delta-or-deltas)
       (values input-end-x-position input-end-y-position
	       initial-orientation-horizontal-p delta-or-deltas))
      ((atom delta-or-deltas)
       (if initial-orientation-horizontal-p
	   (values (+w input-end-x-position delta-or-deltas)
		   input-end-y-position
		   initial-orientation-horizontal-p
		   delta-or-deltas)
	   (values input-end-x-position
		   (+w input-end-y-position delta-or-deltas)
		   initial-orientation-horizontal-p
		   delta-or-deltas)))
      (t   ; if cons with length of at least 2
       (loop with stable-axis-position
	       = (if initial-orientation-horizontal-p
		     input-end-y-position
		     input-end-x-position)
	     with variable-axis-begin-position
	       = (if initial-orientation-horizontal-p
		     input-end-x-position
		     input-end-y-position)
	     for rest-of-deltas on delta-or-deltas
	     as delta 
		= (car rest-of-deltas)
	     as orientation-horizontal-p
		= initial-orientation-horizontal-p
		then (not orientation-horizontal-p)
	     as variable-axis-end-position
		= (+w variable-axis-begin-position
		      delta)
	     until (null (cdr rest-of-deltas))
	     do (setq variable-axis-begin-position
		      stable-axis-position
		      stable-axis-position
		      variable-axis-end-position)
	     finally
	       (if orientation-horizontal-p
		   (return 
		     (values
		       variable-axis-end-position
		       stable-axis-position
		       orientation-horizontal-p
		       rest-of-deltas))
		   (return
		     (values
		       stable-axis-position
		       variable-axis-end-position
		       orientation-horizontal-p
		       rest-of-deltas))))))))







;;;; Updating Extreme Edges from Connections

(defun-simple loose-end-connection-p (connection)
  (let ((connection-input (input-end-object connection))
	(connection-output (output-end-object connection)))
     (if (loose-end-p connection-input)
	 (not (loose-end-p connection-output))
	 (loose-end-p connection-output))))

;;; `Update-extreme-edges-from-connections-from-block',
;;; `update-extreme-edges-from-block-loose-ends' and
;;; `update-extreme-edges-from-connection' are utilized by "Detemining Extreme
;;; Edges of Blocks", a section of DRAW.

(defun-void update-extreme-edges-from-connections-of-block (subblock do-only-loose-ends-p)
  (loop for connection being the output-connections of subblock
	do
    (unless (and do-only-loose-ends-p
		 (not (loose-end-connection-p connection)))
      (update-extreme-edges-from-connection connection))))



;;; The function `rectangle-for-connection-segment' attempts to return the
;;; bounding rectangle for a wide line from x1,y1 to x2,y2, with the given
;;; half-width.  If extend is true of an endpoint, then the line length at that
;;; end point is extended by one half-width.  The extension is an approximation
;;; which is strictly correct only for orthogonal segments.  Fortunately, only
;;; orthogonal segments require it.

;;; Initial points of orthogonal connections butt against the given x,y
;;; positions, hence call this function with extend = NIL.  Intermediate points
;;; of orthgonal connections call with extend = T.  Diagonal connections always
;;; specify extend = NIL.

(defun rectangle-for-connection-segment
    (x1 y1 extend1 x2 y2 extend2 half-width fudge)
  (macrolet ((extend (u1 u2 extend-p)
	       `(cond ((null ,extend-p)
		       0)
		      ((< ,u1 ,u2)
		       (-f half-width))
		      (t
		       half-width))))

    (multiple-value-bind (left top right bottom)
	(cond ((>=f (absf (-f x1 x2)) (absf (-f y1 y2)))	    ; Mostly horizontal
	       ;; Extend the line length if requested.
	       (incff x1 (extend x1 x2 extend1))
	       (incff x2 (extend x2 x1 extend2))
	       (values (minf x1 x2)
		       (-f (minf y1 y2) half-width)
		       (maxf x1 x2)
		       (+f (maxf y1 y2) half-width)))
	      (t						    ; Mostly vertical
	       (incff y1 (extend y1 y2 extend1))
	       (incff y2 (extend y2 y1 extend2))
	       (values (-f (minf x1 x2) half-width)
		       (minf y1 y2)
		       (+f (maxf x1 x2) half-width)
		       (maxf y1 y2))))

      ;; Apply fudge liberally on all sides.
      (values (-f (minf left right) fudge)
	      (-f (minf top bottom) fudge)
	      (+f (maxf left right) fudge)
	      (+f (maxf top bottom) fudge)))))

;; An internal function for the following.




;;; The function `map-over-connection-rectangles' applies the given function to
;;; the bounding rectangle of each segment of the connection.  It effectively
;;; runs
;;;      (setq argument (funcall function left top right bottom argument))
;;; for each bounding rectangle, and then returns the final value of the
;;; argument.  The function must be a simple compiled function.

;;; This function includes numerous fudge factors in an attempt to model the
;;; bizaare behvior of the code which actually draws connections.  The code has
;;; been delicately balanced in an attempt to satisfy two conflicting
;;; requirements:

;;;  (1) The rectangles must be big enough to cover the entire connection.
;;;  (2) The rectangle must be small enough to NOT cover the input and output blocks.

;;; Requirement 1 is needed to prevent turds when connections are moved.  I
;;; think that it is satisfied for all but the pathological cases of connection
;;; drawing (See the "pathologies" workspace in /home/fmw/kbs/connections/conn3.kb).

;;; Requirement 2 is needed to prevent connections from appearing to overlap
;;; their end blocks.  If they do appear to, then every update (change-color,
;;; etc) to an end block will cause the connection to be drawn.  Mill.kb, for
;;; example, even though it never changes any of its connections, was spending
;;; 30% of its CPU drawing them, before this function was modified to satisfy
;;; this property.

;;; In the end, this is a complete kludge.  It's hopeless to guarentee anything
;;; about these bounding rectangles while the connection drawing code remains
;;; so buggy, bizaare, and capricious.

;; -fmw, 2/2/95

(defun map-over-connection-rectangles (connection function argument)
  (cond ((new-connection-p connection)
	 (map-over-diagonal-connection-rectangles connection function argument))
	(t
	 (map-over-orthogonal-or-thin-diagonal-connection-rectangles
	   connection function argument))))

;; This is the old routine which assumes that diagonal connection have width 1.
(defun map-over-orthogonal-or-thin-diagonal-connection-rectangles
    (connection function argument)
  (with-connection
      connection t t t
      ((delta-or-deltas (delta-or-deltas connection))
       (current-x-position input-end-x-position)
       (current-y-position input-end-y-position)
       (horizontal-p initial-orientation-horizontal-p)
       (connection-half-width
	 (compute-connection-half-width-adjusted-for-fins
	   connection))
       (diagonal?
	 (connection-diagonal-p connection))
       (one-segment?
	 (and (or (null delta-or-deltas)
		  ;; There are connections with just one segment, yet a
		  ;; non-NULL delta.
		  (atom delta-or-deltas))
	      (if horizontal-p
		  (=f input-end-y-position output-end-y-position)
		  (=f input-end-x-position output-end-x-position))))
       (extend-final-endpoint?
	 ;; Note A.
	 (loose-end-p output-end-object))
       (answer
	 argument)
       (fudge
	 ;; Most Unfortunate.
	 (if diagonal? 3 0)))

    (macrolet
	((rect (x1 y1 extend1 x2 y2 extend2)
	   `(multiple-value-bind (left top right bottom)
		(rectangle-for-connection-segment
		  ,x1 ,y1 ,extend1
		  ,x2 ,y2 ,extend2
		  connection-half-width fudge)
	      (setq answer
		    (funcall-simple-compiled-function
		      function left top right bottom answer))))

	 (step-both (dx dy extend-1 extend-2)
	   ;; Step forwards in both dx and dy.
	   `(let ((last-x current-x-position)
		  (last-y current-y-position))
	      (incff current-x-position ,dx)
	      (incff current-y-position ,dy)
	      (rect last-x last-y ,extend-1
		    current-x-position current-y-position ,extend-2)
	      (setq horizontal-p (not horizontal-p))))

	 (step-forward (dx dy extend-1)
	   ;; Step forwards by dx or dy (only one used).
	   `(if horizontal-p
		(step-both ,dx 0 ,extend-1 t)
		(step-both 0 ,dy ,extend-1 t)))

	 (finish (extend-1)
	   ;; Step to the finish.
	   `(rect current-x-position current-y-position
		  ,extend-1
		  output-end-x-position output-end-y-position
		  extend-final-endpoint?))

	 (final-dx ()
	   `(-f output-end-x-position current-x-position))

	 (final-dy ()
	   `(-f output-end-y-position current-y-position))
	 
	 (zigzag (extend-1)
	   ;; Follow the last two (implied) deltas to the finish.
	   `(progn
	      (step-forward (final-dx) (final-dy) ,extend-1)
	      (finish t))))

      (cond (diagonal?
	     ;; Diagonal connections can actually have any number of deltas,
	     ;; although they ought to always have an even number.
	     (cond ((null delta-or-deltas)
		    ;; One diagonal segment.
		    (finish nil))
		   ((numberp delta-or-deltas)
		    ;; Two segments.
		    (if horizontal-p
			(step-both delta-or-deltas (final-dy) nil nil)
			(step-both (final-dx) delta-or-deltas nil nil))
		    (finish nil))
		   (t
		    ;; Arbitrary number of segments.
		    (loop for (delta-1 delta-2?) on delta-or-deltas by #'cddr
			  as last-x = current-x-position
			  as last-y = current-y-position
			  doing
		      (cond (horizontal-p
			     (if (null delta-2?)
				 (setq delta-2? (final-dy)))
			     (incff current-x-position delta-1)
			     (incff current-y-position delta-2?))
			    (t
			     (if (null delta-2?)
				 (setq delta-2? (final-dx)))
			     (incff current-x-position delta-2?)
			     (incff current-y-position delta-1)))

		      (rect last-x last-y nil
			    current-x-position current-y-position nil))
		    (finish nil))))
	    (t
	     (cond
	       (one-segment?
		;; One segment.
		(finish nil))

	       ((null delta-or-deltas)
		;; Two segments.
		(zigzag nil))

	       ((numberp delta-or-deltas)
		;; Three segments.
		(step-forward delta-or-deltas delta-or-deltas nil)
		(zigzag t))
	       
	       (t
		;; Arbitrary number of segments.
		(loop for delta in delta-or-deltas
		      as extend-1 = nil then t
		      doing
		  (step-forward delta delta extend-1))
		(zigzag t)))))

      answer)))

;; Note A: This is an attempt to compensate for adjust-next-to-last-delta.
;; That function adds one, in window coordinates, to the last delta,
;; unpredictably.  It seems to be a problem only for loose-ends at the
;; output-end of a connection.  Also, we are safe fudging the bounding
;; rectangle for a loose-end since there's no real object which we must butt up
;; against precisely.  Ideally we would fudge by just one pixel, but fudging by
;; the half-width works for now.  An abomination?  Yes. -fmw, 2/2/95



;;; The function `map-over-diagonal-connection-rectangles' uses the same vertex
;;; and mitering functions used by diagonal connection drawing, with a unit
;;; transform, to get workspace coordinates.  We need to do this to capture the
;;; mitered corners, etc.

(defun map-over-diagonal-connection-rectangles (connection function argument)
  (with-temporary-gensym-float-creation map-over-diagonal-connection-rectangles
    (let* ((stripes-width (compute-connection-width-given-connection-frame-or-class
			    (connection-frame-or-class connection)))
	   (fins-width (if (connection-has-arrows-p connection)
			   0 (connection-arrow-width connection)))
	   (fwidth2 (/e (coerce-to-gensym-float (+f stripes-width fins-width 2)) ; Fudge
			2.0))
	   (answer argument)
	   vertices upper-points lower-points)
      (with-null-drawing-transform
	(setq vertices (compute-connection-vertices connection)
	      upper-points (compute-miter-points fwidth2 vertices)
	      lower-points (compute-miter-points (-e fwidth2) vertices)))
      (loop for (x1 y1 x2 y2) on upper-points by 'cddr
	    for (x3 y3 x4 y4) on lower-points by 'cddr
	    while x2
	    as left = (minf x1 x2 x3 x4)
	    as top = (minf y1 y2 y3 y4)	          ; Workspace coor.
	    as right = (1+f (maxf x1 x2 x3 x4))	  ; Regions are open on right,bottom.
	    as bottom = (1+f (maxf y1 y2 y3 y4))
	    doing
	(setq answer
	      (funcall-simple-compiled-function
		function left top right bottom answer)))

      (when (connection-has-arrows-p connection)
	(setq answer
	      (map-over-connection-arrows connection vertices function answer)))

      (reclaim-gensym-list vertices)
      (reclaim-gensym-list upper-points)
      (reclaim-gensym-list lower-points)
      answer)))

#+development
(defun debug-draw-region (region)
  (when (boundp 'current-image-x-scale)
    (do-region-rectangles ((left top right bottom) region)
      (draw-rectangle-1 (x-in-window left) (y-in-window top)
			(x-in-window right) (y-in-window bottom)
			:color 'red))))

#+development
(defun debug-draw-connection-bounding-rectangles (connection-or-frame)
  (let* ((connection (if (framep connection-or-frame)
			 (connection-for-this-connection-frame connection-or-frame)
			 connection-or-frame))
	 (image-plane (car (image-planes-this-is-on (workspace-of-connection? connection)))))
    (with-raw-window-transform-and-draw-area ((gensym-window-for-image-plane image-plane))
      (with-nested-transform-and-draw-area-of-image-plane-contents? (image-plane)
	(on-image-plane (image-plane)
	  (map-over-connection-rectangles
	    connection
	    #'(lambda (left top right bottom arg)
		(draw-rectangle-1 (x-in-window left) (y-in-window top)
				  (x-in-window right) (y-in-window bottom)
				  :color 'blue)
		arg)
	    nil))))))

;;; The function `connection-bounding-region' returns the smallest workspace
;;; region we can find which bounds the given connection.

(defun connection-bounding-region (connection)
  (map-over-connection-rectangles
    connection
    #'add-rectangle-to-region
    (make-empty-region)))


;;; The function `update-extreme-edges-from-connection', when run in a
;;; computing extreme edges dynamic context, updates them by the bounding
;;; rectangle of the given connection.

(defun-void update-extreme-edges-from-connection (connection)
  (map-over-connection-rectangles
    connection
    #'update-extreme-edges-from-connection-1
    nil))

;; The extreme edges returned are not very accurate, since this code doesn't
;; use the exact same computations as draw-connection (eg, calling
;; serve-next-delta, etc.).  It can't easily, since draw-connection runs
;; entirely in window coordinates, not workspace coordinates!



;;; The simple function `update-extreme-edges-from-connection-1' is merely a
;;; helper function for the one above.

(defun-simple update-extreme-edges-from-connection-1 (left top right bottom arg)
  (declare (ignore arg))
  (update-extreme-edges-from-rectangle left top right bottom))




;;; The simple function `compute-connection-half-width-adjusted-for-fins'
;;; attempts to return the half-width of a connection, including the
;;; directional fins, if any.

(defun-simple compute-connection-half-width-adjusted-for-fins
    (connection)
  (let* ((basis-half-width
	   (if (connection-diagonal-p connection)
	       1
	       (halfw (compute-connection-width-given-connection-frame-or-class
			(connection-frame-or-class connection))))))
    
    (+w basis-half-width
	(if (connection-directed? connection)
	    (+f (connection-fin-length connection (*f basis-half-width 2)) 3) ; Fudge
	    1))))				      ; Fudge





;;;; "Invisible Entity" method of dragging connections


;;; Dragging Loose Ends of Connections

;;; Instead of erasing and redrawing an entire connection as it is being
;;; dragged, only the part of the connection that has to be redrawn, is
;;; redrawn.  This is done by splitting the connection into two
;;; connections, c1 and c2, while it is being dragged.  The two
;;; connections are connected by an "invisible entity", as shown below.
;;; As the mouse is dragged, the invisible entity is moved to an optimum
;;; point, and only the second (or loose) connection is erased and
;;; redrawn.  When dragging is finished, the two connections are
;;; recombined.


;;;         c1           c2
;;;   ------------ i.e. ----  <- anchor point
;;;                        |
;;;                        |
;;;                        |
;;;                        |
;;;                        -----------m  <- mouse cursor

;;; This optimal approach is important since connections may have
;;; complicated cross sections which take longer to draw, and because
;;; several connections may be dragged at once (when they are connected
;;; to an icon being dragged).  This implementation is also a very nice
;;; because it abstracts the dragging from the drawing of connections;
;;; by using the two connections, the basic draw functions for
;;; connections can be used to do most of the work.


;;; Things to be done when beginning to drag loose end:   Set up a
;;; transit state.  Calculate the anchor position, and the position  for
;;; the invisible entity.  Split the connection into two, connected  by
;;; the invisible entity.  At least one of  the connections, as well as
;;; perhaps some other information, are  cached in the transit state.
;;; The functions that perform  these operations will be invoked by
;;; handle-mouse-action (see "run").   Note that eventually, all
;;; connection structures  and invisible entities should be fully
;;; reclaimable.  
;; Some of this functionality is in "run".













;;; Things to be done while dragging loose end:
;;;   1.  Calculate new position for invisible entity and changes to 
;;; connection c2.  The position of the invisible entity is 
;;; a function of the anchor point, and the new and old mouse positions.
;;;   2.  Erase c2.
;;;   3.  Change c2.
;;;   4.  Draw c2.
;;; The function that performs these operations will be invoked by
;;; move-object-in-transit-if-appropriate (see "run").


;;; Compute-new-position-for-invisible-entity will return
;;; x-position-of-invisible-entity-in-workspace,
;;; y-position-of-invisible-entity-in-workspace,
;;; connection-2-initial-orientation-horizontal-p,
;;; new-delta-for-c2, and side-of-invisible-entity-for-connection.
;;; When this is called initially (for a
;;; new invisible-entity), the old cursor and new cursor arguments
;;; should be the same.

;(defun compute-new-position-for-invisible-entity
;       (x-position-of-anchor-point-in-workspace
;	y-position-of-anchor-point-in-workspace
;	old-cursor-x-in-workspace
;	old-cursor-y-in-workspace	
;	new-cursor-x-in-workspace
;	new-cursor-y-in-workspace
;	connection-half-width
;	link-0-orientation-horizontal-p
;	link-0-delta)
;  (let (x-position-of-invisible-entity-in-workspace
;	y-position-of-invisible-entity-in-workspace
;	connection-2-initial-orientation-horizontal-p
;	(new-delta-for-c2 nil)
;	side-of-invisible-entity-for-connection
;	(connection-epsilon 1)  ; should this be 0?
;	old-link-1-delta
;	old-link-2-delta
;	new-link-1-delta
;	new-link-2-delta)

;    (if link-0-orientation-horizontal-p
;	(setq old-link-1-delta
;	      (-w old-cursor-y-in-workspace
;		  y-position-of-anchor-point-in-workspace)
;	      old-link-2-delta
;	      (-w old-cursor-x-in-workspace
;		  x-position-of-anchor-point-in-workspace)
;	      new-link-1-delta
;	      (-w new-cursor-y-in-workspace
;		  y-position-of-anchor-point-in-workspace)
;	      new-link-2-delta
;	      (-w new-cursor-x-in-workspace
;		  x-position-of-anchor-point-in-workspace))
;	(setq old-link-1-delta
;	      (-w old-cursor-x-in-workspace
;		  x-position-of-anchor-point-in-workspace)
;	      old-link-2-delta
;	      (-w old-cursor-y-in-workspace
;		  y-position-of-anchor-point-in-workspace)
;	      new-link-1-delta
;	      (-w new-cursor-x-in-workspace
;		  x-position-of-anchor-point-in-workspace)
;	      new-link-2-delta
;	      (-w new-cursor-y-in-workspace
;		  y-position-of-anchor-point-in-workspace)))


;    (setq new-delta-for-c2
;	  (if (>w link-0-delta 0)
;	      (+w connection-half-width
;		  connection-epsilon)
;	      (-w (+w connection-half-width
;		      connection-epsilon)))
;	  connection-2-initial-orientation-horizontal-p
;	  link-0-orientation-horizontal-p)
;    (if link-0-orientation-horizontal-p
;	(setq y-position-of-invisible-entity-in-workspace
;	      y-position-of-anchor-point-in-workspace
;	      x-position-of-invisible-entity-in-workspace
;	      (-w x-position-of-anchor-point-in-workspace
;		  new-delta-for-c2)
;	      side-of-invisible-entity-for-connection
;	      (if (>w link-0-delta 0)
;		  'right
;		  'left))
;	(setq x-position-of-invisible-entity-in-workspace
;	      x-position-of-anchor-point-in-workspace
;	      y-position-of-invisible-entity-in-workspace
;	      (-w y-position-of-anchor-point-in-workspace
;		  new-delta-for-c2)
;	      side-of-invisible-entity-for-connection
;	      (if (>w link-0-delta 0)
;		  'bottom
;		  'top)))
;    ;; temporary test


;;    (cond
;;      ((or (=w old-link-1-delta 0)
;;	   (=w new-link-1-delta 0)
;;	   (/= (signum old-link-1-delta)
;;	       (signum new-link-1-delta)))
;;       (setq new-delta-for-c2
;;	     (if (>w link-0-delta 0)
;;		 (+ connection-half-width
;;		    connection-epsilon)
;;		 (- (+ connection-half-width
;;		       connection-epsilon)))
;;	     connection-2-initial-orientation-horizontal-p
;;	     link-0-orientation-horizontal-p)
;;
;;       (if link-0-orientation-horizontal-p
;;	   (setq y-position-of-invisible-entity-in-workspace
;;		 y-position-of-anchor-point-in-workspace
;;		 x-position-of-invisible-entity-in-workspace
;;		 (- x-position-of-anchor-point-in-workspace
;;		    new-delta-for-c2)
;;		 side-of-invisible-entity-for-connection
;;		 (if (>w link-0-delta 0)
;;		     'right
;;		     'left))
;;	   (setq x-position-of-invisible-entity-in-workspace
;;		 x-position-of-anchor-point-in-workspace
;;		 y-position-of-invisible-entity-in-workspace
;;		 (- y-position-of-anchor-point-in-workspace
;;		    new-delta-for-c2)
;;		 side-of-invisible-entity-for-connection
;;		 (if (>w link-0-delta 0)
;;		     'bottom
;;		     'top))))
;;
;;      ((=w old-link-1-delta new-link-1-delta)
;;       (if link-0-orientation-horizontal-p
;;	   (cond
;;	     ((and (>w old-link-2-delta 0)
;;		   (>w new-link-2-delta 0))
;;	      (setq y-position-of-invisible-entity-in-workspace
;;		    old-cursor-y-in-workspace
;;		    x-position-of-invisible-entity-in-workspace
;;		    (if (>= new-link-2-delta old-link-2-delta)
;;			(- old-cursor-x-in-workspace 
;;			   connection-epsilon)
;;			(- new-cursor-x-in-workspace 
;;			   connection-epsilon))
;;		    side-of-invisible-entity-for-connection
;;		    'right
;;		    connection-2-initial-orientation-horizontal-p
;;		    link-0-orientation-horizontal-p))
;;	     ((and (>w 0 old-link-2-delta)
;;		   (>w 0 new-link-2-delta))
;;	      (setq y-position-of-invisible-entity-in-workspace
;;		    old-cursor-y-in-workspace
;;		    x-position-of-invisible-entity-in-workspace
;;		    (if (<= new-link-2-delta old-link-2-delta)
;;			(+ old-cursor-x-in-workspace 
;;			   connection-epsilon)
;;			(+ new-cursor-x-in-workspace 
;;			   connection-epsilon))
;;		    side-of-invisible-entity-for-connection
;;		    'left
;;		    connection-2-initial-orientation-horizontal-p
;;		    link-0-orientation-horizontal-p))
;;	     (t
;;	      (setq x-position-of-invisible-entity-in-workspace
;;		    x-position-of-anchor-point-in-workspace
;;		    y-position-of-invisible-entity-in-workspace
;;		    (if (>w old-link-1-delta 0)
;;			(- old-cursor-y-in-workspace
;;			   connection-half-width
;;			   connection-epsilon)
;;			(+ old-cursor-y-in-workspace
;;			   connection-half-width
;;			   connection-epsilon))
;;		    side-of-invisible-entity-for-connection
;;		    (if (>w old-link-1-delta 0)
;;			'bottom
;;			'top)
;;		    connection-2-initial-orientation-horizontal-p
;;		    (not link-0-orientation-horizontal-p))))
;;	   (cond
;;	     ((and (>w old-link-2-delta 0)
;;		   (>w new-link-2-delta 0))
;;	      (setq x-position-of-invisible-entity-in-workspace
;;		    old-cursor-x-in-workspace
;;		    y-position-of-invisible-entity-in-workspace
;;		    (if (>= new-link-2-delta old-link-2-delta)
;;			(- old-cursor-y-in-workspace 
;;			   connection-epsilon)
;;			(- new-cursor-y-in-workspace 
;;			   connection-epsilon))
;;		    side-of-invisible-entity-for-connection
;;		    'bottom
;;		    connection-2-initial-orientation-horizontal-p
;;		    link-0-orientation-horizontal-p))
;;	     ((and (>w 0 old-link-2-delta)
;;		   (>w 0 new-link-2-delta))
;;	      (setq x-position-of-invisible-entity-in-workspace
;;		    old-cursor-x-in-workspace
;;		    y-position-of-invisible-entity-in-workspace
;;		    (if (<= new-link-2-delta old-link-2-delta)
;;			(+ old-cursor-y-in-workspace 
;;			   connection-epsilon)
;;			(+ new-cursor-y-in-workspace 
;;			   connection-epsilon))
;;		    side-of-invisible-entity-for-connection
;;		    'top
;;		    connection-2-initial-orientation-horizontal-p
;;		    link-0-orientation-horizontal-p))
;;	     (t  
;;	      ;; if old or new link-2-delta = 0
;;	      ;; or if they have different signs
;;	      (setq y-position-of-invisible-entity-in-workspace
;;		    y-position-of-anchor-point-in-workspace
;;		    x-position-of-invisible-entity-in-workspace
;;		    (if (>w old-link-1-delta 0)
;;			(- old-cursor-x-in-workspace
;;			   connection-half-width
;;			   connection-epsilon)
;;			(+ old-cursor-x-in-workspace
;;			   connection-half-width
;;			   connection-epsilon))
;;		    side-of-invisible-entity-for-connection
;;		    (if (>w old-link-1-delta 0)
;;			'right
;;			'left)
;;		    connection-2-initial-orientation-horizontal-p
;;		    (not link-0-orientation-horizontal-p))))))
;;
;;      (t
;;       (setq connection-2-initial-orientation-horizontal-p
;;	     (not link-0-orientation-horizontal-p))
;;       (if link-0-orientation-horizontal-p
;;	   (setq x-position-of-invisible-entity-in-workspace
;;		 x-position-of-anchor-point-in-workspace
;;		 y-position-of-invisible-entity-in-workspace
;;		 (cond
;;		   ((and (>w old-link-1-delta 0)
;;			 (>w new-link-1-delta 0))
;;		    (if (>= new-link-1-delta old-link-1-delta)
;;			(- old-cursor-y-in-workspace
;;			   connection-half-width
;;			   connection-epsilon)
;;			(- (+ y-position-of-anchor-point-in-workspace
;;			      new-link-1-delta)
;;			   connection-half-width
;;			   connection-epsilon)))
;;		   ((and (>w 0 old-link-1-delta)
;;			 (>w 0 new-link-1-delta))
;;		    (if (<= new-link-1-delta old-link-1-delta)
;;			(+ old-cursor-y-in-workspace
;;			   connection-half-width
;;			   connection-epsilon)
;;			(+ (+ y-position-of-anchor-point-in-workspace
;;			      new-link-1-delta)
;;			   connection-half-width
;;			   connection-epsilon))))
;;		 side-of-invisible-entity-for-connection
;;		 (if (>w old-link-1-delta 0)
;;		     'bottom
;;		     'top))
;;	   (setq y-position-of-invisible-entity-in-workspace
;;		 y-position-of-anchor-point-in-workspace
;;		 x-position-of-invisible-entity-in-workspace
;;		 (cond
;;		   ((and (>w old-link-1-delta 0)
;;			 (>w new-link-1-delta 0))
;;		    (if (>= new-link-1-delta old-link-1-delta)
;;			(- old-cursor-x-in-workspace
;;			   connection-half-width
;;			   connection-epsilon)
;;			(- (+ x-position-of-anchor-point-in-workspace
;;			      new-link-1-delta)
;;			   connection-half-width
;;			   connection-epsilon)))
;;		   ((and (>w 0 old-link-1-delta)
;;			 (>w 0 new-link-1-delta))
;;		    (if (<= new-link-1-delta old-link-1-delta)
;;			(+ old-cursor-x-in-workspace
;;			   connection-half-width
;;			   connection-epsilon)
;;			(+ (+ x-position-of-anchor-point-in-workspace
;;			      new-link-1-delta)
;;			   connection-half-width
;;			   connection-epsilon))))
;;		 side-of-invisible-entity-for-connection
;;		 (if (>w old-link-1-delta 0)
;;		     'right
;;		     'left)))))

;    (values x-position-of-invisible-entity-in-workspace
;	    y-position-of-invisible-entity-in-workspace
;	    connection-2-initial-orientation-horizontal-p
;	    new-delta-for-c2
;	    side-of-invisible-entity-for-connection)))

;; New-delta-for-c2 will be either nil or + or - (+
;; connection-half-width epsilon)

;; Note that while dragging, shouldn't have to fix c1 at all.  If fact,
;; if c1 is the original connection, it shouldn't have to be fixed at all.
;; when dragging is done, c1 becomes the connection once again.
;; Since the invisible entity is stored in the connection in transit,
;; there is no need to connect c1 to the invisible entity.



;;; Things to be done when finishing dragging of loose end:  Recombine
;;; c1 and c2 back into one connection.  Recycle extra connection.



;;;; Support for drawing


;;; Since connections aren't blocks, drawing functions which must deal with
;;; either blocks or connections are way over here in CONNECT3A, instead of in
;;; DRAW, where they belong.


;;; The function `output-connections-of-block' returns a freshly consed gensym
;;; list of the connections which "belong" to the block, namely the block's
;;; output connections.

(defun output-connections-of-block (block)
  (loop for connection being the output-connections of block
	collect connection using tree-ordering-cons))

(defmacro copy-subblocks-using-tree-ordering-conses (subblocks)
  #-subblocks-v2
  `(copy-list-using-tree-ordering-conses ,subblocks)
  #+subblocks-v2
  (let ((subblock (gensym)))
    (avoiding-variable-capture (subblocks)
      `(when ,subblocks
	 (loop for ,subblock being each constant-queue-element of ,subblocks
	       collect ,subblock using tree-ordering-cons)))))

;;; The function `subblocks-and-connections-top-to-bottom' returns the
;;; inferiors of a block, as needed for the tree-traversal macro below.
;;; They are in top-to-bottom order.

(defun-substitution-macro subblocks-and-connections-top-to-bottom (superblock)
  (cond ((connection-p superblock)
	 nil)
	((workspace-p superblock)			    ; Too bad this test is so big.
	 (copy-subblocks-using-tree-ordering-conses (subblocks superblock)))
	((inhibit-drawing-subblocks-in-harness-p superblock)
	 nil)
	(t
	 (nreverse
	   (nconc-macro
	     (copy-subblocks-using-tree-ordering-conses (subblocks superblock))
	     (output-connections-of-block superblock))))))


(defun-substitution-macro subblocks-and-connections-bottom-to-top (superblock)
  (cond ((connection-p superblock)
	 nil)
	((workspace-p superblock)
	 (nreverse
	   (copy-subblocks-using-tree-ordering-conses (subblocks superblock))))
	((inhibit-drawing-subblocks-in-harness-p superblock)
	 nil)
	(t
	 (nconc-macro
	   (copy-subblocks-using-tree-ordering-conses (subblocks superblock))
	   (output-connections-of-block superblock)))))




;;; The macro `do-subblocks-and-connections' runs body for each block or
;;; connection upon the workspace, or in any subblock of the workspace
;;; recursively, in reverse drawing order (top to bottom).

(defmacro do-subblocks-and-connections ((subblock-or-connection workspace) &body body)
  `(macrolet ((valid-node (node) `(not (symbolp ,node))))
     (do-post-order (,subblock-or-connection ,workspace
					     subblocks-and-connections-top-to-bottom
					     :filter valid-node
					     :do-not-copy-list t)
       (unless (eq ,subblock-or-connection ,workspace)
	 ,@body))))

					

(defmacro do-subblocks-and-connections-in-drawing-order
    ((subblock-or-connection workspace) &body body)
  `(macrolet ((valid-node (node) `(not (symbolp ,node))))
     (do-pre-order (,subblock-or-connection ,workspace
					    subblocks-and-connections-bottom-to-top
					    :filter valid-node
					    :do-not-copy-list t)
       (unless (eq ,subblock-or-connection ,workspace)
	 ,@body))))



;;; The function `descendents-of-block-or-connection' return a newly consed
;;; slot-value list of all the subblocks and connections of the given thing,
;;; recursively including their subblocks, in reverse drawing order (top to
;;; bottom).

(defun descendents-of-block-or-connection (block-or-connection)
  (let ((list ()))
    (do-subblocks-and-connections (sibling block-or-connection)
      (slot-value-push sibling list))
    list))



;;; The function `extreme-edges-of-block-or-connection' returns the extreme
;;; edges of all drawing which would be done for the given block or connection.

#+unused
(defun extreme-edges-of-block-or-connection (block-or-connection)
  (with-extreme-edges-1 ()
    (cond ((or (connection-p block-or-connection)
	       (frame-of-class-p block-or-connection 'connection))
	   (update-extreme-edges-from-connection
	     (if (connection-p block-or-connection)
		 block-or-connection
		 (connection-for-this-connection-frame block-or-connection))))
	  
	  (t
	   (update-extreme-edges-from-block-bounds block-or-connection)
	   (update-extreme-edges-from-elements block-or-connection)))

    (values extreme-left-edge-so-far
	    extreme-top-edge-so-far
	    extreme-right-edge-so-far
	    extreme-bottom-edge-so-far)))



;;; The function `extreme-edges-of-blocks-and-connections' returns the box
;;; enclosing all of the given blocks and connections.

#+unused
(defun extreme-edges-of-blocks-and-connections (blocks connections)
  (with-extreme-edges-1 ()
    (loop for block in blocks doing
      (update-extreme-edges-from-block-bounds block)
      (update-extreme-edges-from-elements block))
      
    (loop for connection in connections doing
      (update-extreme-edges-from-connection
	(if (connection-p connection)
	    connection
	    (connection-for-this-connection-frame connection))))

    (values extreme-left-edge-so-far
	    extreme-top-edge-so-far
	    extreme-right-edge-so-far
	    extreme-bottom-edge-so-far)))



;;; The function `local-edges-of-block-or-connection' returns the "local" edges
;;; of the given block or connection, WITHOUT recursing on subblocks.

(def-substitution-macro local-edges-of-block-or-connection-macro (block-or-connection)
  (with-extreme-edges-1 ()
    (cond ((connection-p block-or-connection)
	   (update-extreme-edges-from-connection block-or-connection))

	  ((frame-of-class-p block-or-connection 'connection)
	   (when (connection-for-this-connection-frame block-or-connection)
	     (update-extreme-edges-from-connection
	       (connection-for-this-connection-frame
		 block-or-connection))))

	  (t
	   (update-extreme-edges-from-block-bounds block-or-connection)))

    (values extreme-left-edge-so-far
	    extreme-top-edge-so-far
	    extreme-right-edge-so-far
	    extreme-bottom-edge-so-far)))


(defun local-edges-of-block-or-connection (block-or-connection)
  (local-edges-of-block-or-connection-macro block-or-connection))




;;; The substitution-macro `bounding-region-of-block-or-connection-macro'
;;; returns a tight bounding region for given block or connection.  This does
;;; NOT include any subblocks.

(def-substitution-macro bounding-region-of-block-or-connection-macro
    (block-or-connection)
  (cond ((connection-p block-or-connection)
	 (connection-bounding-region block-or-connection))
	(t
	 (multiple-value-bind (left top right bottom)
	     (local-edges-of-block-or-connection-macro block-or-connection)
	   (make-region-from-rectangle left top right bottom)))))


(defun bounding-region-of-block-or-connection (block-or-connection)
  (bounding-region-of-block-or-connection-macro block-or-connection))




;;; The function `get-workspace-of-block-or-connection' returns the workspace
;;; of a block-or-connection.

(defun get-workspace-of-block-or-connection (block-or-connection)
  (cond ((connection-p block-or-connection)
	 (workspace-of-connection? block-or-connection))
	(t
	 (get-workspace-if-any-macro block-or-connection))))



#+development
(defun compute-changed-blocks-of-workspace (workspace)
  (let ((list ()))
    (do-subblocks-and-connections (block-or-connection workspace)
      (let ((block? (cond ((framep block-or-connection)
			   block-or-connection)
			  ((framep (connection-frame-or-class block-or-connection))
			   (connection-frame-or-class block-or-connection)))))
	(when (and block? (block-changes block?))
	  (push block? list))))
    list))



;;;; Overlapping Cache



;;; The `overlapping-cache' is a mechanism for partially memoizing the function
;;; `overlapping-siblings'.  We say that it is partially memoized since we
;;; cache only one possible return value: we can determine quickly whether the
;;; list of overlapping blocks is NIL.  This is the most common case for
;;; typical knowledge bases (they say).  Two bits on blocks implement the
;;; cache: `block-overlap-cache' and `block-overlap-cache-valid'.

;;; Note these bits have a slightly different meaning for workspaces: the cache
;;; bit is unused, and the valid bit, if false, means that ALL of the blocks on
;;; the workspace (as well as their subblocks and connections) have an invalid
;;; cache bit.

;;; Of course, connections ain't blocks, so we must allocate another pair of
;;; bits in connection-flags.


(def-concept overlapping-cache)
    

;;; The valid bit.

(defun block-or-connection-overlap-cache-valid-p (block-or-connection)
  (cond ((connection-p block-or-connection)
	 (connection-overlap-cache-valid-p block-or-connection))
	(t
	 (block-overlap-cache-valid-p block-or-connection))))

(defun set-block-or-connection-overlap-cache-valid-p (block-or-connection valid-p)
  ;; When we transition to invalid, clear the cached list of blocks.
  (cond ((connection-p block-or-connection)
	 (setf (connection-overlap-cache-valid-p block-or-connection) valid-p)
	 (unless valid-p
	   (when (connection-overlapping-blocks-cache block-or-connection)
	     ;; This setf DOES reclaim the old value.
	     (setf (connection-overlapping-blocks-cache block-or-connection) nil))))

	(t
	 (setf (block-overlap-cache-valid-p block-or-connection) valid-p)
	 (unless valid-p
	   (when (overlapping-blocks-cache block-or-connection)
	     (reclaim-slot-value-list (overlapping-blocks-cache block-or-connection))
	     ;; This setf does NOT reclaim the old value.
	     (setf (overlapping-blocks-cache block-or-connection) nil))))))


(defsetf block-or-connection-overlap-cache-valid-p set-block-or-connection-overlap-cache-valid-p)



;;; The overlap bit.
;; Now this is the same as a non-NIL overlap-cache list, and could be removed.

(defun block-or-connection-overlap-cache-p (block-or-connection)
  (cond ((connection-p block-or-connection)
	 (connection-overlap-cache-p block-or-connection))
	(t
	 (block-overlap-cache-p block-or-connection))))

(defun set-block-or-connection-overlap-cache-p (block-or-connection new-value)
  (cond ((connection-p block-or-connection)
	 (setf (connection-overlap-cache-p block-or-connection) new-value))
	(t
	 (setf (block-overlap-cache-p block-or-connection) new-value))))

(defsetf block-or-connection-overlap-cache-p set-block-or-connection-overlap-cache-p)


;;; The cached list of blocks and connections.

(defun block-or-connection-overlap-cache (block-or-connection)
  (cond ((connection-p block-or-connection)
	 (connection-overlapping-blocks-cache block-or-connection))
	(t
	 (overlapping-blocks-cache block-or-connection))))

(defun set-block-or-connection-overlap-cache (block-or-connection new-value)
  (cond ((connection-p block-or-connection)
	 (setf (connection-overlapping-blocks-cache block-or-connection) new-value))
	(t
	 (setf (overlapping-blocks-cache block-or-connection) new-value))))

(defsetf block-or-connection-overlap-cache set-block-or-connection-overlap-cache)




  
;;; Might overlap if either the cache is invalid or the cache is valid and
;;; the bit is set.

(defun block-or-connection-might-overlap-p (block-or-connection)
  (or (not (block-or-connection-overlap-cache-valid-p block-or-connection))
      (block-or-connection-overlap-cache-p block-or-connection)))



;;; The defconstant `workspace-geometry-tick-mask' is used to limit the size of
;;; the workspace geometry tick.  Since that is incremented whenever a block
;;; moved, it could easily become a bignum otherwise.

(defconstant workspace-geometry-tick-mask (1-f (ashf 1 (1-f positive-bits-per-fixnum))))



;;; The function `note-change-to-workspace-geometry' is is called whenever a
;;; block is added, moved, resized, raised, or lowered.  This is where we
;;; invalidate the overlap cache for all blocks on a workspace.

(defun note-change-to-workspace-geometry (workspace?)
  (when workspace?

    ;; Increment the change tick.
    (setf (workspace-geometry-tick workspace?)
	  (logandf (1+f (workspace-geometry-tick workspace?))
		   workspace-geometry-tick-mask))
    
    ;; Invalidate the overlap cache.
    (when (block-overlap-cache-valid-p workspace?)

      (setf (block-overlap-cache-valid-p workspace?) nil)

      ;; Go ahead and clear all of the subblock caches now, for tidiness.
      (do-subblocks-and-connections (subblock-or-connection workspace?)
	(setf (block-or-connection-overlap-cache-valid-p subblock-or-connection)
	      nil)))))

;; We should be more clever about invalidating only the affected subset of
;; subblocks.



;; Called from maintain-workspace-caches-for-remove-block.

(defun remove-subblocks-and-connections-from-drawing-queues (workspace block)
  (do-subblocks-and-connections (subblock block)
    (unless (eq subblock block)				    ; A quirk of do-subblocks.
      (if (framep subblock)
	  (remove-block-from-drawing-queues workspace subblock)
	  (note-deletion-of-connection-for-drawing subblock)))))




;;; The function `validate-overlapping-cache-for-workspace' is the first step in
;;; validating the cache for a subblock of the workspace.  It is O(n).

(defun validate-overlapping-cache-for-workspace (workspace)
  (setf (block-overlap-cache-valid-p workspace) t))




;;; The function `draw-block-or-connection' draws the given block or connection, only.
;;; It does NOT recurse to subblocks.

(defun draw-block-or-connection (block-or-connection)
  (cond ((connection-p block-or-connection)
	 (draw-connection block-or-connection nil))
	(t
	 (draw-block-possibly-with-frame block-or-connection nil))))



;;; The substitution-macro `block-or-connection-is-transformed-p' returns T if
;;; the thing's edges are not in its workspace's coordinate system, and NIL
;;; otherwise. The result is strictly correct only if the thing is showing!

(def-substitution-macro block-or-connection-is-transformed-p (block-or-connection)
  (let ((block (if (connection-p block-or-connection)
		   (input-end-object block-or-connection)
		   block-or-connection)))
    (when (and (block-is-transformed-p block)
	       (null (frame-description-reference-of-block? block)))
      t)))


      
;;; The substitution-macro `block-or-connection-is-framed-p' returns T if the
;;; given thing has a frame (which also means that it defines a coordinate
;;; system).

(def-substitution-macro block-or-connection-is-framed-p (block-or-connection)
  (when (and (framep block-or-connection)
	     (frame-description-reference-of-block? block-or-connection))
    t))



;;; The substitution-macro `get-frame-transform-block' returns the block
;;; which defines the coordinate system in which the given block or
;;; connection lives.

(def-substitution-macro get-frame-transform-block (block-or-connection)
  (when (connection-p block-or-connection)
    (setq block-or-connection (input-end-object block-or-connection)))
  (loop for block? = (superblock? block-or-connection) then (superblock? block?)
	while block?
	until (frame-transforms-of-block block?)
	finally
	  (return block?)))

  

;;; The function `compute-overlapping-siblings-1' computes the overlapping
;;; blocks from scratch, returning a newly-consed slot-value list.  The list
;;; always includes the given block-or-connection (unfortunately).

(defun-substitution-macro compute-overlapping-siblings-1
    (workspace block-or-connection)
  (let* ((transformed?
	   (block-or-connection-is-transformed-p block-or-connection))
	 (this-region
	   (bounding-region-of-block-or-connection-macro block-or-connection))
	 (candidates
	   (blocks-potentially-touching-region workspace this-region))
	 (answer ()))
    
    (loop for sibling in candidates
	  doing
      ;; Don't bother unless they're in the same coordinate system.
      (when (eq transformed? (block-or-connection-is-transformed-p sibling))
	(let ((region
		(bounding-region-of-block-or-connection-macro sibling)))

	  (when (regions-intersect-p region this-region)
	    (slot-value-push sibling answer)

	    ;; If the sibling is framed, always include all its subblocks.
	    ;; Since the subblocks are in a different coordinate system, we
	    ;; know they will not be included twice.
	    (when (block-or-connection-is-framed-p sibling)
	      (setq answer (nconc (descendents-of-block-or-connection sibling)
				  answer))))
	  (reclaim-region region))))

    (reclaim-region this-region)
    (reclaim-slot-value-list candidates)
    
    (nreverse answer)))

;; This function tries to return a very accurate answer.  Since the result is
;; cached, we can afford some expensive computations.

;; Note that spacial indices don't work for transformed blocks.



;;; The function `compute-overlapping-siblings' returns a slot-value list of
;;; the blocks and connections which overlap, or might overlap, the given one,
;;; in drawing order (bottom to top).

(defun-substitution-macro compute-overlapping-siblings (workspace block-or-connection)
  (cond ((block-or-connection-is-transformed-p block-or-connection)
	 ;; If the thing is in an alternate coordinate system, then we really
	 ;; have no idea what it might overlap -- the alternate coordinate system
	 ;; only exists on a per-image-plane basis.  So, conclude that we
	 ;; overlap everything our frame-defining block does.
	 (let ((frame-transform-block?
		 (get-frame-transform-block block-or-connection)))
	   (cond (frame-transform-block?
		  (compute-overlapping-siblings-1 workspace frame-transform-block?))
		 (t
		  #+development (cerror "Return NIL" "~s claims to be transformed but isn't."
					block-or-connection)
		  nil))))
	(t
	 (compute-overlapping-siblings-1 workspace block-or-connection))))



  
;;; The function `overlapping-siblings-1' returns a list of all of the blocks or
;;; connections which overlap the given block-or-connection, INCLUDING itself,
;;; in order from bottom-most to top-most (drawing order), on their common
;;; workspace.  The returned list is owned by this function and should NOT be
;;; reclaimed.

(def-substitution-macro overlapping-siblings-1 (workspace block-or-connection)
  (unless (block-overlap-cache-valid-p workspace)
    (validate-overlapping-cache-for-workspace workspace))

  (cond ((block-or-connection-overlap-cache-valid-p block-or-connection)
	 (block-or-connection-overlap-cache block-or-connection))
	(t
	 (with-drawing-trace (cache)
	   (format t "Overlap cache miss on ~s~%" block-or-connection))
	 (let ((answer (compute-overlapping-siblings workspace block-or-connection)))
	   (setf (block-or-connection-overlap-cache-valid-p block-or-connection) t
		 (block-or-connection-overlap-cache-p block-or-connection) (not (null answer))
		 (block-or-connection-overlap-cache block-or-connection) answer)
	   answer))))

;; Too bad we include the block itself -- this means the cache is always non-NIL.




;;; The substitution-macro `canonical-block-or-connection' return the connection
;;; structure for connection frames.

(def-substitution-macro canonical-block-or-connection (block-or-connection)
  (cond ((and (framep block-or-connection)
	      (connection-frame-p block-or-connection))
	 (connection-for-this-connection-frame block-or-connection))
	(t
	 block-or-connection)))

;; The cached list of blocks stores connection's NOT connection-frames, so we
;; must be sure to use connections here for the memq below to work properly.



;;; The function `overlapping-siblings' returns a list of all blocks and
;;; connections which overlap the given block (aboveness = nil), or which are
;;; strictly above it (T), or inclusively above it (above-inclusive).

(defun overlapping-siblings (workspace block-or-connection aboveness)
  (let* ((thing
	   (canonical-block-or-connection block-or-connection))
	 (list
	   (overlapping-siblings-1 workspace thing)))
    (case aboveness
      ((above t)
       (cdr (memq-macro thing list)))
      ((above-inclusive)
       (memq-macro thing list))
      (t
       list))))



;;; The function `block-is-entirely-visible-p' returns T if the given block is
;;; completely unobscured.  That is, it is above any other items on its
;;; workspace, and its portion of its workspace is completely visible on the
;;; image-plane of the given window.  If the block is not visible anywhere,
;;; then we return NIL.  Subblocks are not included.

#+unused
(defun block-is-entirely-visible-p (gensym-window block)
  (let ((workspace? (get-workspace-if-any-macro block)))
    (when workspace?
      (let ((image-plane? (image-plane-of-workspace-on-window
			    gensym-window workspace?)))
	(when image-plane?
	  (cond ((workspace-p block)
		 (rectangle-in-region-p
		   (left-edge-of-image-in-window image-plane?)
		   (top-edge-of-image-in-window image-plane?)
		   (right-edge-of-image-in-window image-plane?)
		   (bottom-edge-of-image-in-window image-plane?)
		   (visible-region-of-image-plane image-plane?)))
		(t
		 (and (null (overlapping-siblings workspace? block t))

		      (multiple-value-bind (left top right bottom)
			  (local-edges-of-block block)
			(let ((left-in-window
				(x-in-window-for-image-plane left image-plane?))
			      (top-in-window
				(y-in-window-for-image-plane top image-plane?))
			      (right-in-window
				(x-in-window-for-image-plane right image-plane?))
			      (bottom-in-window
				(y-in-window-for-image-plane bottom image-plane?)))

			  ;; Bleed conservatively.
			  (decff left-in-window)
			  (decff top-in-window)
			  (incff right-in-window)
			  (incff bottom-in-window)
			  
			  (rectangle-in-region-p left-in-window top-in-window
						 right-in-window bottom-in-window
						 (visible-region-of-image-plane image-plane?))))))))))))

  

#+development
(defun print-overlap-cache (ws)
  (print-random-tree
    ws #'(lambda (x) (subblocks-and-connections-bottom-to-top x))
    :printer
    #'(lambda (node stream)
	(format stream "~s   ~s"
		node
		(if (block-or-connection-overlap-cache-valid-p node)
		    (block-or-connection-overlap-cache node)
		    "invalid")))))
		



;;;; Cleanup overlapping blocks



(def-substitution-macro fast-check-for-overlapping-blocks (workspace block-or-connection)
  (unless (block-overlap-cache-valid-p workspace)
    (validate-overlapping-cache-for-workspace workspace))
  (block-or-connection-might-overlap-p block-or-connection))



;;; `draw-overlapping-blocks' draws the non-XOR blocks and connections which
;;; overlap the local edges of the given block or connection.  If aboveness is
;;; T or ABOVE, then only things strictly above the given one in the layering
;;; order are drawn.  An aboveness of ABOVE-INCLUSIVE is the same, except that
;;; the given thing is included.  For any other value of aboveness, all blocks
;;; and connections overlapping the given one are drawn, including the given
;;; one itself.

;;; One client, refresh-region-of-block, tells this guy to include blocks in
;;; the XOR overlay.  Blocks in the XOR overlay must be drawn even if they are
;;; apparently below the given block (because the XOR overlay is an overlay).

;;; Called by update-images to repair color changes.  Note this
;;; should not be called on a workspace, or on blocks in the XOR overlay.

;; Note that as of 6/19/97, this function should not be called from refresh-
;; color-of-block if the block is a connection; draw-blocks-overlapping-
;; connection should be called instead.  Not sure if other callers might
;; still pass a connection as the block-or-connection argument.  -jv, 6/19/97

(defun-void draw-overlapping-blocks
    (workspace block-or-connection aboveness include-xor-overlay?)
  (when (fast-check-for-overlapping-blocks workspace block-or-connection)
    (let* ((this-thing
	     (canonical-block-or-connection block-or-connection))
	   (siblings
	     (copy-list-using-slot-value-conses		    ; Note D.
	       (overlapping-siblings workspace this-thing nil))))

      (when siblings
	(let ((subblock-of-a-graph?				    ; Note A.
		(subblock-of-graph-p block-or-connection))
	      (erase-instead?
		nil))

	  (loop with above? = nil
		for thing in siblings
		as connection? = (connection-p thing)
		as in-overlay? = (if connection?
				     (render-connection-in-xor-overlay-p thing)
				     (render-frame-in-xor-overlay-p thing))
		;; Whether aboveness criteria met, or XOR overlap.
		as condition-1 = (case aboveness
				   ((t above)
				    (if include-xor-overlay?
					(or above? in-overlay?)
					(and above? (not in-overlay?))))
				   (above-inclusive
				    (if include-xor-overlay?
					(or above?
					    (eq thing this-thing)
					    in-overlay?)
					(and (or above?
						 (eq thing this-thing))
					     (not in-overlay?))))
				   (t
				    t))

		;; Don't draw the graph superblock.
		as condition-2 = (and (not (and subblock-of-a-graph?
						(frame-is-graph-p thing)))
				      (or (paint-mode-p)
					  ;; This fixes the
					  ;; graph-over-updating-readout-table-in-xor bug.
					  (and (not connection?)
					       (opaque-block-p thing))))

		doing
	    (when (and condition-1 condition-2)
	      (draw-block-or-connection thing))

	    (when (eq thing this-thing)
	      (setq above? t)))

	  (reclaim-slot-value-list siblings))))))

;; Note A: For graphs, we used get all of the axis labels, etc, as overlapping
;; blocks.  That caused some problems, and was fixed in
;; subblocks-and-connections-top-to-bottom, which now does not consider graphs
;; to have any subblocks at all. -fmw, 9/6/94

;; Note B: It would be nice if we could clean up overlapping XORed objects
;; here, too, but the that to work the clipping region must be exactly correct.
;; For graphs in particular, it's too hard to figure out exactly which parts of
;; the screen were clobbered.  So instead, the XOR overlay is handled by
;; removing it around each update-images.  This happens in
;; map-drawing-over-image-planes-1 -fmw, 9/7/94

;; Note C: Draw overlying block or connections which are opaque. That is, which
;; are not in the XOR overlay, and which are either in paint-mode themselves,
;; or are opaque-block-p.  There's an additional test so that we don't consider
;; a graph to overlie its subblocks.

;; Note D: The draw method for graphs can sometimes invalidate the overlap
;; cache, which will reclaim this list.  The elements of the list never include
;; subblocks of a graph, so they remain valid.  For example, reformatting a
;; graph may add and remove axis-label subblocks, which invalidates the cache.
;; It would be better to fix graphs, but hopefully they will just fade away.  .
;; -fmw, 6/27/95


;;; `draw-current-connection-overlapping-things' - draws the list of 
;;; things-to-draw within the region given, in workspace coordinates,
;;; by left, right, top, and bottom.  Must return things-to-draw,
;;; because map-over-connection-rectangles passes the return value
;;; to the next call as the fifth argument.

(defun-simple draw-current-connection-overlapping-things
    (left top right bottom things-to-draw)
  (with-nested-draw-area?
      ((x-in-window left) (y-in-window top)
       (x-in-window right) (y-in-window bottom))
    (within-named-dynamic-extent for-image-plane
      (with-open-cursors (left-edge-of-draw-area
			   top-edge-of-draw-area
			   right-edge-of-draw-area
			   bottom-edge-of-draw-area
			   :xor-overlay t)
	(loop for thing in things-to-draw do
	  (draw-block-or-connection thing)))))
  things-to-draw)



;;; `draw-blocks-overlapping-connection' - a hacked-up version of
;;; draw-overlapping-blocks for when we know that the block being
;;; overlapped is a connection, the aboveness is 'above, and the
;;; the include-xor-overlay? is nil.  The main point of this function
;;; is to only redraw the portions of the overlapping blocks that
;;; should be invalidated by the redrawing (or color change) of the
;;; connection.

(defun-void draw-blocks-overlapping-connection (workspace connection)
  (within-named-dynamic-extent for-image-plane
    (when (and workspace
	       (fast-check-for-overlapping-blocks workspace connection))
      (let* ((this-thing
	       (connection-for-this-connection-frame connection))
	     (erase-instead? nil)
	     (siblings
	       (copy-list-using-slot-value-conses		    ; Note A.
		 (overlapping-siblings workspace this-thing nil)))
	     (siblings-to-draw '()))
	(when siblings
	  (setq siblings-to-draw
	    (loop as above-p = nil then (or above-p (eq thing this-thing))
		  for thing in siblings
		  as connection-p = (connection-p thing)
		  when (and above-p
			    (not (if connection-p
				     (render-connection-in-xor-overlay-p thing)
				     (render-frame-in-xor-overlay-p thing)))
			    (or (paint-mode-p)
				;; This fixes the
				;; graph-over-updating-readout-table-in-xor bug.
				(and (not connection-p)
				     (opaque-block-p thing))))
		    collect thing using gensym-cons))
	  (map-over-connection-rectangles
	    this-thing
	    #'draw-current-connection-overlapping-things
	    siblings-to-draw)
	  (reclaim-gensym-list siblings-to-draw))
	(reclaim-slot-value-list siblings)))))

;; Note A: The draw method for graphs can sometimes invalidate the overlap
;; cache, which will reclaim this list.  The elements of the list never include
;; subblocks of a graph, so they remain valid.  For example, reformatting a
;; graph may add and remove axis-label subblocks, which invalidates the cache.
;; It would be better to fix graphs, but hopefully they will just fade away.
;; -fmw, 6/27/95



;;; The function `draw-overlapping-xor-blocks' draws the overlying XOR-ed
;;; blocks, not including those in the XOR overlay.  It is used only in XOR
;;; mode to draw XOR blocks which are on top of an opaque block.

(defun-void draw-overlapping-xor-blocks (workspace block)
  (when (xor-mode-p)
    (let ((siblings-above
	    (overlapping-siblings workspace block 'above)))
      
      (when siblings-above
	(let ((erase-instead? nil))
	  (loop for thing in siblings-above doing
	    (unless (cond ((framep thing)
			   (or (opaque-block-p thing)
			       (render-frame-in-xor-overlay-p thing)))
			  (t
			   (render-connection-in-xor-overlay-p thing)))
	      (draw-block-or-connection thing))))))))



;;;; Geometric Index


;;; This section contains the portions of the spacial indexing code which
;;; references connection macros.


(def-substitution-macro set-layer-position-of-block-or-connection (block-or-connection value)
  (cond ((connection-p block-or-connection)
	 (setf (layer-position-of-connection block-or-connection) value)
	 ;; Keep the connection-frame in sync.
	 (when (connection-frame-of-connection? block-or-connection)
	   (setf (layer-position-of-block (connection-frame-of-connection? block-or-connection))
		 value))
	 value)
	(t
	 (setf (layer-position-of-block block-or-connection) value))))


(def-substitution-macro layer-position-of-block-or-connection (block-or-connection)
  (cond ((connection-p block-or-connection)
	 (layer-position-of-connection block-or-connection))
	(t
	 (layer-position-of-block block-or-connection))))

(defsetf layer-position-of-block-or-connection set-layer-position-of-block-or-connection)



;;; The simple function `block-or-connectio-less-p' returns T if thing-1 is
;;; below thing-2 in the layering for drawing.  Each thing may be a block or a
;;; connection.

(defun-simple block-or-connection-less-p (thing-1 thing-2)
  (<f (layer-position-of-block-or-connection thing-1)
      (layer-position-of-block-or-connection thing-2)))



(def-substitution-macro remove-connection-from-those-awaiting-indexing
    (workspace connection)
  (with-drawing-trace (index)
    (format t "Index: remove ~s from ~s~%" connection workspace))
  (setf (connection-needs-indexing-p connection) nil)
  (setf (workspace-connections-which-need-indexing workspace)
	(delete-slot-value-element
	  connection
	  (workspace-connections-which-need-indexing workspace))))


(def-substitution-macro add-connection-to-those-awaiting-indexing
    (workspace connection)
  (with-drawing-trace (index)
    (format t "Index: invalidate ~s on ~s~%" connection workspace))
  (setf (connection-needs-indexing-p connection) t)
  (slot-value-push connection
		   (workspace-connections-which-need-indexing
		     workspace)))




;;; The function `add-thing-to-spacial-index' adds a block or connection to the
;;; index, based upon the thing's local bounding box or region.  If recurse-p,
;;; then add all subblocks and connections, too.

(defun add-thing-to-spacial-index (geometry thing recurse-p)
  (cond ((connection-p thing)
	 (add-connection-to-spacial-index geometry thing))

	((connection-frame-p thing)
	 (when (connection-for-this-connection-frame thing)
	   (add-connection-to-spacial-index
	     geometry
	     (connection-for-this-connection-frame thing))))
	
	;; As far as drawing is concerned, graphs do not have subblocks.
	((subblock-of-graph-p thing)
	 nil)
	
	(t
	 (multiple-value-bind (left top right bottom)
	     (local-edges-of-block-or-connection thing)
	   (geometry-insert geometry thing left top right bottom))

	 (when recurse-p
	   (do-subblocks-and-connections (subthing thing)
	     (add-thing-to-spacial-index geometry subthing recurse-p))))))



;;; The function `remove-thing-from-spacial-index' removes the given block or
;;; connection, and all of its subblocks and connections, from the index, on
;;; behalf of the given workspace.

(defun remove-thing-from-spacial-index (workspace geometry thing)
  (cond ((connection-p thing)
	 (geometry-flush geometry thing)
	 (remove-connection-from-those-awaiting-indexing workspace thing))

	((connection-frame-p thing)
	 (geometry-flush geometry thing)
	 (when (connection-for-this-connection-frame thing)
	   (geometry-flush geometry (connection-for-this-connection-frame thing))
	   (remove-connection-from-those-awaiting-indexing
	     workspace 
	     (connection-for-this-connection-frame thing))))

	;; As far as drawing is concerned, graphs do not have subblocks.
	((subblock-of-graph-p thing)
	 nil)

	(t
	 (multiple-value-bind (left top right bottom)
	     (local-edges-of-block-or-connection thing)
	   (geometry-delete geometry thing left top right bottom))
	 ;; See note.
	 (do-subblocks-and-connections (subthing thing)
	   (remove-thing-from-spacial-index workspace geometry subthing)))))

;; We must remove subblocks now since during the recursive descent of
;; delete-frame, by the time we reach the subblocks they have forgotten their
;; workspace.  There is similar code in
;; `maintain-workspace-caches-for-remove-block', which calls us.
	


;;; The function `add-connection-to-spacial-index' indexes a connection
;;; based on its tight bounding region.

(defun add-connection-to-spacial-index (geometry connection)
  (let ((region (connection-bounding-region connection)))
    (do-region-rectangles ((left top right bottom) region)
      (geometry-insert geometry connection left top right bottom))
    (reclaim-region region)
    connection))




  
;;; The function `recompute-layer-positions' computes and caches the internal
;;; layer position of each block and connection on the given workspace.

(defun recompute-layer-positions (workspace)
  (let ((i 0))
    (do-subblocks-and-connections-in-drawing-order (thing workspace)
      (setf (layer-position-of-block-or-connection thing) i)
      (incff i))))

;; Maybe, do this only when we have an index.  Don't need the cached value
;; otherwise (set to 0 when not needed, to clear the lookup slot on blocks).




;;; The function `compute-user-visible-layer-position' returns the user-visible
;;; layer position of the given item (which may be a connection frame).  The
;;; user-visible layer position is, unfortunately, numbered backwards from the
;;; internally cached layer position.  It is 0 for the topmost item, and
;;; increases towards the bottom-most item.

(defun compute-user-visible-layer-position-of-item (item)
  (let ((workspace? (get-workspace-if-any item))
	(i 0))
    (cond
      ((null workspace?)
       0)
      (t
       (do-subblocks-and-connections (thing workspace?)
	 (let ((this-item? (if (connection-p thing)
			       (connection-frame-of-connection? thing)
			       thing)))
	   (when (eq item this-item?)
	     (return)) ; ugh, see note A 
	   (incff i)))
       i))))

;; Note A:  do-subblocks-and-connections is built on top
;;          do-post-order which demands that non-local exits be done with return
;;          and sets up the appropriate loop block.
;;          It's not the most lexically obvious thing on the planet.



;;; The function `build-spacial-index' rebuilds the index from scratch.  It
;;; also recomputes layer positions.

(defun build-spacial-index (workspace)
  (let ((geometry (create-geometry default-size-of-spacial-index
				   (left-edge-of-block workspace)
				   (top-edge-of-block workspace)
				   (right-edge-of-block workspace)
				   (bottom-edge-of-block workspace)))
	(i 0))
    
    ;; This loops from bottom to top. (See Note).
    (do-subblocks-and-connections-in-drawing-order (thing workspace)
      (add-thing-to-spacial-index geometry thing nil)
      (setf (layer-position-of-block-or-connection thing) i)
      (incff i))

    (with-drawing-trace (index)
      (format t "*** Create spacial index ~s for ~s~%" geometry workspace))

    (validate-layer-positions workspace)
    (setf (workspace-spacial-index? workspace) geometry)
    geometry))

;; Note: This does NOT put subblocks of graphs into the index; however, they
;; may get in there by other means, such as under shift-block.




;;; The function `destroy-spacial-index' reclaims the spacial index, if any.

(defun destroy-spacial-index (workspace)
  (when (workspace-spacial-index? workspace)
    (with-drawing-trace (index)
      (format t "*** Destroy spacial index for ~s~%" workspace))

    ;; Reclaim the list of connections awaiting indexing.
    (let ((connections (workspace-connections-which-need-indexing workspace)))
      (when connections
	(loop for connection in connections doing
	  (setf (connection-needs-indexing-p connection) nil))
	(setf (workspace-connections-which-need-indexing workspace) nil)
	(reclaim-slot-value-list connections)))
    
    ;; Reclaim the index itself
    (reclaim-geometry (workspace-spacial-index? workspace))
    (setf (workspace-spacial-index? workspace) nil)))

;; Also reset all cached layer positions to 0?




;;; The function `note-change-of-connection-for-drawing' is called whenever a
;;; connection's bounding region may have changed.  Since it is too hard to
;;; find precisely all of the places where this might occur, this function is
;;; called for ANY connection change, in note-change-to-connection.  We just
;;; inval the connection's indexing, so that it can be reindexed as-needed.

(defun note-change-of-connection-for-drawing (connection)
  (unless (or loading-kb-p
	      (connection-being-deleted-p connection))
    (unless (connection-needs-indexing-p connection)
      (let ((workspace?
	      (workspace-of-connection? connection)))
	(when workspace?
	  (note-change-to-workspace-geometry workspace?)
	  (when (workspace-spacial-index? workspace?)
	    (add-connection-to-those-awaiting-indexing workspace? connection)
	    connection))))))


;;; The function `note-deletion-of-connection-for-drawing' is called when a
;;; connection structure is about to be deleted.

(defun note-deletion-of-connection-for-drawing (connection)
  (let ((workspace?
	  (workspace-of-connection? connection)))
    (when workspace?
      (note-change-to-workspace-geometry workspace?)
      (update-spacial-index workspace? connection 'remove)
      (remove-thing-from-image-plane-drawing-queues workspace? connection)
      (note-deletion-of-connection-for-selection connection))))






;;; The function `ensure-spacial-index-is-up-to-date' handles the deferred
;;; update to the layer positions and connection indexing.

(defun ensure-spacial-index-is-up-to-date (workspace)
  (let ((geometry? (workspace-spacial-index? workspace))
	(connections (workspace-connections-which-need-indexing workspace)))
    (when geometry?
      (ensure-layer-positions workspace)

      (with-drawing-trace (index)
	(when connections
	  (format t "Index: updating connections on ~s: ~s~%" workspace connections)))
      
      ;; Index connections which were waiting, and clear the bit.
      (loop for connection in connections doing
	#+development (unless (eq workspace (get-workspace-of-block-or-connection connection))
			(warn "Pending connections on wrong workspace for ~s!" workspace))
	
	(geometry-flush geometry? connection)
	(add-connection-to-spacial-index geometry? connection)
	(setf (connection-needs-indexing-p connection) nil))
      
      (reclaim-slot-value-list connections)
      (setf (workspace-connections-which-need-indexing workspace) nil))))





;;; The function `blocks-potentially-touching-region' returns a newly consed
;;; slot-value list of blocks and connections which touch the given region in
;;; workspace coordinates.  The list is in drawing order, from bottom to top.
;;; Unlike the function below, this one ALWAYS includes subblocks and
;;; connections in the list.

(defun blocks-potentially-touching-region (workspace region)
  (let ((geometry? (workspace-spacial-index? workspace)))
    (cond ((null geometry?)
	   (let ((list ()))
	     (do-subblocks-and-connections (sibling workspace)
	       (slot-value-push sibling list))
	     list))
	  (t
	   ;; Bring index up-to-date before using it.
	   (ensure-spacial-index-is-up-to-date workspace)

	   (let ((list (geometry-find-in-region geometry? region)))

	     (with-drawing-trace (index)
	       (format t "INDEX: using index for ~s ~s (~d blocks)~%"
		       workspace region (length list)))
	     
	     (sort-list list #'block-or-connection-less-p nil))))))



;;; The function `blocks-touching-region-for-drawing' returns a list of blocks
;;; OR CONNECTIONS on the workspace which potentially touch the given region,
;;; in workspace coordinates.  The result is a freshly-consed slot-value list
;;; sorted into drawing order (bottom to top by layer position).

;;; The list may or may not include subblocks of the top-level blocks.  A
;;; second value of NIL indicates that subblocks are not included and T
;;; indicates that they are.  This is a temporary kludge to ensure that drawing
;;; without the spacial index is identical to the way drawing used to be.

(defun blocks-touching-region-for-drawing (workspace region sorted?)
  (let ((geometry? (workspace-spacial-index? workspace)))
    (cond ((or (null geometry?)
	       (region-covers-workspace? workspace region))

	   ;; For large regions, go ahead and return all subblocks, thereby
	   ;; avoiding the scan and the sort.

	   (with-drawing-trace (index)
	     (when geometry?
	       (format t "INDEX: skip index for ~s ~s~%" workspace region)))

	   (values
	     ;; reverse list using slot-value conses:
	     (loop with list = nil
		   for block being each subblock of workspace
		   do (slot-value-push block list)
		   finally (return list))
	     nil))
	  
	  (t
	   ;; Bring index up-to-date before using it.
	   (ensure-spacial-index-is-up-to-date workspace)

	   (let ((list (geometry-find-in-region geometry? region)))

	     (with-drawing-trace (index)
	       (format t "INDEX: using index for ~s ~s (~d blocks)~%"
		       workspace region (length list)))
	     
	     #+development
	     (setq list (find-bugs-in-spacial-index workspace geometry? list))
	     
	     (values (if sorted?
			 (sort-list list #'block-or-connection-less-p nil)
			 list)
		     t))))))


#+development
(defun find-bugs-in-spacial-index (workspace geometry list)
  (loop for thing in list doing
    (unless (or (connection-p thing) (framep thing))
      (cerror "Remove it" "Garbage in the spacial index ~s for ~s: ~s"
	      geometry workspace thing)
      (setq list (remove thing list))
      (geometry-flush geometry thing)))
  list)



;;; The function `blocks-touching-region-of-image-plane' returns a list of the
;;; blocks touching the given region, optionally sorted into drawing order.
;;; The returned list may or may not include subblocks. If the second returned
;;; value is T, then the list does include them.

(defun blocks-touching-region-of-image-plane (workspace region-of-window sorted?)
  (let ((region-of-workspace
	  (transform-region-to-workspace-coordinates region-of-window)))
    (multiple-value-bind (blocks flag)
	(blocks-touching-region-for-drawing workspace region-of-workspace sorted?)
      (reclaim-region region-of-workspace)
      (values blocks flag))))

;; It's most unfortunate that we have to transform back to workspace coor.

;; Ought to return a new data structrure, list-of-blocks, which knows whether
;; it is sorted, etc.





;;;; Checking If an Image-plane Has Any Drawing


;;; The function `image-plane-has-drawing-in-window-p' returns non-NIL if there
;;; is anything on image-plane that is visible in its window including the frame
;;; (border) and any background images.  Note that this is not very efficient.
;;; It is used by the printing facility to detect blank pages, for which it is
;;; fast enough.

(defun image-plane-has-drawing-in-window-p (image-plane)
  (let ((workspace? (workspace-on-image-plane? image-plane)))
    (when workspace?
      (with-image-plane-transform (image-plane)
	(let* ((draw-area-region
		 (make-region-from-rectangle
		   (left-edge-of-pane-in-window image-plane)
		   (top-edge-of-pane-in-window image-plane)
		   (right-edge-of-pane-in-window image-plane)
		   (bottom-edge-of-pane-in-window image-plane))))
	  (prog1
	      (or
		;; visible-blocks-or-connections-p
		(let ((candidate-blocks-and-connections
			(blocks-touching-region-of-image-plane workspace? draw-area-region nil)))
		  (prog1
		      (loop for block-or-connection in candidate-blocks-and-connections
			    thereis (block-or-connection-overlaps-window-rectangle-p
				      block-or-connection
				      (left-edge-of-pane-in-window image-plane)
				      (top-edge-of-pane-in-window image-plane)
				      (right-edge-of-pane-in-window image-plane)
				      (bottom-edge-of-pane-in-window image-plane)))
		    (reclaim-slot-value-list candidate-blocks-and-connections)))
		;; visible-background-images-p
		(when (image-plane-background-images image-plane)
		  (let* ((images-region
			   (region-containing-background-images image-plane))
			 (visible-images-region
			   (intersect-region images-region draw-area-region)))
		    (prog1 (not (empty-region-p visible-images-region))
		      (reclaim-region images-region)
		      (reclaim-region visible-images-region))))
		;; visible-border-p
		(and (or (not (printing-image-plane-p image-plane))
			 (not (suppress-printing-border-p image-plane)))
		     (let* ((outer-region
			      (make-region-from-rectangle
				(left-edge-of-image-in-window image-plane)
				(top-edge-of-image-in-window image-plane)
				(right-edge-of-image-in-window image-plane)
				(bottom-edge-of-image-in-window image-plane)))
			    (inner-region
			      (make-region-from-rectangle
				(left-edge-of-workspace-area-in-window image-plane)
				(top-edge-of-workspace-area-in-window image-plane)
				(right-edge-of-workspace-area-in-window image-plane)
				(bottom-edge-of-workspace-area-in-window image-plane)))
			    (border-region
			      (subtract-region outer-region inner-region))
			    (visible-border-region
			      (intersect-region border-region draw-area-region)))
		       (prog1 (not (empty-region-p visible-border-region))
			 (reclaim-region inner-region)
			 (reclaim-region outer-region)
			 (reclaim-region border-region)
			 (reclaim-region visible-border-region)))))
	    (reclaim-region draw-area-region)))))))


(defun connection-overlaps-window-rectangle-p-1 (left top right bottom value-so-far)
  (or value-so-far
      (rectangles-overlap-p
	left-edge-of-draw-area
	top-edge-of-draw-area
	right-edge-of-draw-area
	bottom-edge-of-draw-area
	(x-in-window left)
	(y-in-window top)
	(x-in-window (1+f right))
	(y-in-window (1+f bottom)))))

(defun connection-overlaps-window-rectangle-p (connection left top right bottom)
  (with-draw-area (left top right bottom)
    (map-over-connection-rectangles
      connection
      #'connection-overlaps-window-rectangle-p-1
      nil)))


;;; The function `block-or-connection-overlaps-window-rectangle-p' tries hard to
;;; return a precise answer, unlike block-possibly-overlaps-rectangle?, which
;;; errs on the side of true.

(defun block-or-connection-overlaps-window-rectangle-p (block-or-connection left top right bottom)
  (cond ((connection-p block-or-connection)
	 (connection-overlaps-window-rectangle-p block-or-connection left top right bottom))
	((framep block-or-connection)
	 (block-overlaps-window-rectangle-p block-or-connection left top right bottom))
	(t
	 (dwarn "Junk in block-or-connection-overlaps-window-rectangle-p: ~s" block-or-connection))))

(defun block-overlaps-window-rectangle-p (block left top right bottom)
  (or (rectangles-overlap-p left top right bottom 
			    (x-in-window (left-edge-of-block block))
			    (y-in-window (top-edge-of-block block))
			    (x-in-window (1+f (right-edge-of-block block)))
			    (y-in-window (1+f (bottom-edge-of-block block))))
      (loop for subblock being the subblocks of block
	    thereis (block-overlaps-window-rectangle-p subblock left top right bottom))
      (loop for connection being the connections of block
	    thereis (connection-overlaps-window-rectangle-p connection left top right bottom))))

;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module CONNECT3

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Andreas Hofmann


(declare-forward-reference
  update-runtime-structures-according-to-edit function)	; in module INSTALL
(declare-forward-reference flush-subworkspace-connection-posts function)
(declare-forward-reference compute-dragged-connection-anchor-point function)
(declare-forward-reference add-missing-deltas-to-connection function)
(declare-forward-reference remove-redundant-deltas-from-connection function)
(declare-forward-reference subworkspace-connection-posts-p function) ; FILTERS
(declare-forward-reference add-subworkspace-connection-post function) ; CONNECT4
(declare-forward-reference delete-subworkspace-connection-post-if-superfluous function)
(declare-forward-reference recompute-external-connections-for-dragging-states function)

(declare-forward-references
  (send-ws-representations-connection-moved function events-g2)
  (start-procedure-invocation-in-place  function proc-utils))

(declare-forward-reference remove-object-from-dragging-context function)	; in MOVES

(declare-forward-reference decache-roles-for-entities-related-to-this-connection function)


;;; CONNECT3 contains functions for editing connections. These functions are
;;; typically invoked by functions in RUN.


;; Note on memory management.  There is no floating point arithmetic in
;; any of the connections stuff so number consing should not be a
;; problem.  There is no generic consing; all consing is done using
;; connection conses.  These are all being reclaimed except for a minor
;; leak when deleting an entity (should be easy to fix).  Note that the
;; list (if any) in the connections slot of an entity is made up of
;; slot-value-conses, not connection conses.  These are also being
;; reclaimed except for a very minor leak in replace-connection-in-block
;; when both ends of the connection are on the same entity (should be
;; easy to fix).  Some connections may be getting lost in the slot value
;; reclaimer when make-stub fails to make a new connection.  This is
;; only the case when deleting knowledge bases where the connection
;; definition is deleted first.

;; Make-stub may lose a connection in certain cases (since a connection is made
;; but the connection class definition may have been deleted).  This happens
;; when deleting kbs.

;; To test memory management of connections, use show-memory-management and 
;; observe connection conses, slot-value conses, connection structures, and
;; connection-subrectangle structures.


;; To Do 

;; Currently, if connection is dragged into same block, the connection is deleted.
;; Consider deleting if only near stub position!  See add-new-connection-to-block.

;; Review compute-position-of-last-bend and its relation to other compute
;; functions.  If redundant, consolidate.  Else document better.

;; All calls to update-images with a connection should be abstracted to a macro
;; or function.  There are about 30 of these.

;; Connection draw function: improve, get rid of extra delta mechanism.  Make 
;; a delta server abstraction.  This could use a mechanism similar to role
;; servers.  The continuation would be the list of remaining deltas.  When 
;; there are no more deltas, the continuation could be special symbols for
;; the last two links.  This should substantially simplify the connection
;; draw routine.  Also, fix non-centering problem of connections (look at
;; any sensor).  Also, on TI, it is sometimes difficult to get rid of kinks,
;; even at full scale.  Investigate this.  

;; Allow joining of directed and non-directed connections.  The non-directed
;; connections should become directed.  Also, allow joining of connections
;; with different cross sections (use junction blocks).

;; Improve connection arrows.  Make shorter and fatter.  Also, improve 
;; spacing.

;; (low priority)
;; For put-kink-into-connection-if-straight, put kink near object being dragged
;; rather than near object at other end.  Currently, the kink is always put
;; near the input end object.

;; (low priority)
;; Make document sometime describing high level strategy of connections stuff;
;; rules for how links are stretched etc.  For example, when an object is moved,
;; the two links nearest to it are stretched.

;; (low priority)
;; Review connection editing stuff.  Maybe this shouldn't be spread over three
;; files (RUN, MOVES, and MENUS).  In handle-mouse-event, code for figuring out
;; side of loose-end for connection doesn't belong here.  This should be 
;; abstracted and moved to connections.  Similarly, code in 
;; mouse-down-in-dragging-context for adding bends to connections does not
;; belong here.

;; (low priority)
;; Find-nearest... functions.  Try to simplify.  Rather than returning
;; multiple values through several levels, use special variables.

;; (low priority)
;; Replace add/remove missing delta mechanism with a delta server.  Also,
;; try to simplify functions and remove repetitive code by using some 
;; primitives.  There are too many cases of long let forms that do the 
;; same thing.  Replace with a function that returns multiple values.

;; (low priority)
;; A name can be given to a connection frame but it isn't displayed anywhere.
;; Don't get rid of name slot since it may be used by inference engine or
;; simulator.

;; (low priority)
;; Consider not saving connection frames that haven't had any values of 
;; attributes changed.

;; (low priority)
;; Review connection role grammar.  It may be possible to flatten this
;; out further.  Also, bug in menu:  "at the" comes up when it is possible
;; to say "at an" as well as "at the".

;; (low priority)
;; When a connection class is defined, a junction for that class is automatically
;; defined.  The user can overide this by defining his own junction class and then
;; putting that class in the junction block slot for the connection class.  The
;; slot putter for this slot should check to make sure that the user defined junction
;; class actually is a sub-class of default-junction-class and put up a frame note
;; if it isn't.

;; Review connection drawing when dragging across the icon from which the
;; connection originates.

;; Review issues of rotating icons with connections.  If an icon connected to
;; another icon is rotated, it will often be the case that the output end
;; of the connection does not enter the icon at the output end perpendicularly.
;; The only way to fix this would be to add links to the connections which is
;; really too complicated.  If this is a problem, don't allow rotation of
;; connected icons at all.  Also, if a connection is connected to itself
;; and rotated, drawing across icon can result depending on what the deltas
;; are.

;; Review add-new-connection-to-block.  It may be possible to simplify this.

;; Consider implementing a with-end-information wrapper to consolidate
;; some of the repetitious code for getting end information of a connection.

;; Consider implementing a delta-server (same idea as a role server) which
;; serves all deltas of a connection (including the two omitted ones).
;; This way, don't always have to check if (delta-or-deltas connection) is
;; nil, a number, or a list.

;; Review insertion of junction blocks, especially at corners that are
;; small kinks.  In this case, the connection often seems to be being
;; inserted on a wrong side somehow.  In this case, consider putting
;; junction not on corner but rather on one of the longer links.  
;; This would look better.  This is a complicated issue and needs some
;; review.

;; Declare notify-user, begin-transit-state, and
;; external-connections-to-stretch to be forward references.

;; Need a capability to somehow put up a new, simple, short
;; connection with two loose ends.  This would allow for 
;; adding connections when there are no stubs around to do so.
;; (see note and drawing in (paper) file on connections).

;; Sometimes have trouble getting rid of kinks in control block
;; connections.  This problem only happens on the TI.

;; Also consider allowing connection of directed to non-directed
;; connections.

;; Still a problem with connection placement on sides
;; (probably a draw problem).  For example, a box icon with 
;; connections at same y location on the left and right sides is
;; not symmetric.

;; Probably should relax the restriction of connecting only pipes with
;; the same cross section.  See notes on type compatibility checking
;; in design book from 9/25/87.  These are the result of a design 
;; meeting with Mike and Jim.  Use the junction block from the pipe
;; with the bigger cross section.  Also, allow connection of directed
;; to non-directed connections.  Again, this is easily done using a
;; junction block.




;;;; Editing Connections



;;; `Change-deltas-for-input-end-object-being-dragged' is invoked when the
;;; object being dragged is the input-end-object of a connection.  Connection,
;;; block, delta-x-in-workspace, and delta-y-in-workspace are passed as
;;; arguments.  The first two deltas of (delta-or-deltas connection) are
;;; modified.  When the connection is placed, if the last delta is still 0, it
;;; should be removed.  If the block is a loose-end, its side may have to be
;;; changed.

(defun change-connection-deltas-for-input-end-object-being-dragged
    (connection block delta-x-in-workspace delta-y-in-workspace)
  (let* ((input-end-position
	   (input-end-position connection))
	 (input-end-side
	   (get-side-given-end-position
	     input-end-position))
	 (initial-orientation-horizontal-p
	   (initial-orientation-horizontal-p input-end-side))
	 (delta-or-deltas
	   (delta-or-deltas connection))
	 link-1-delta
	 link-2-delta)
    (cond
      ((null delta-or-deltas)
       (multiple-value-setq
	   (link-1-delta link-2-delta)
	 (compute-stretched-links-of-connection-being-dragged
	   connection block))
       (setq link-2-delta (-w link-2-delta)))
      ((atom delta-or-deltas)
       (setq link-2-delta
	     (if initial-orientation-horizontal-p
		 (-w delta-or-deltas
		     delta-x-in-workspace)
		 (-w delta-or-deltas
		     delta-y-in-workspace)))
       (setf (delta-or-deltas connection) link-2-delta))
      (t   ; if delta-or-deltas is a cons with length of at least 2
       (setq link-1-delta
	     (if initial-orientation-horizontal-p
		 (-w (cadr delta-or-deltas)
		     delta-y-in-workspace)
		 (-w (cadr delta-or-deltas)
		     delta-x-in-workspace))
	     link-2-delta
	     (if initial-orientation-horizontal-p
		 (-w (car delta-or-deltas)
		     delta-x-in-workspace)
		 (-w (car delta-or-deltas)
		     delta-y-in-workspace)))
       (setf (car (delta-or-deltas connection)) link-2-delta
	     (cadr (delta-or-deltas connection)) link-1-delta)))
    
    (when (loose-end-p block)
      (setf (input-end-position connection)
	    (combine-side-and-position-on-side-for-end-position
	      (if initial-orientation-horizontal-p
		  (if (>w 0 link-2-delta) 'left 'right)
		  (if (>w 0 link-2-delta) 'top 'bottom))
	      0)))))

;; Consider defining a more efficient loose-end-p.


;;; `Change-deltas-for-output-end-object-being-dragged' is invoked when the
;;; object being dragged is the output-end-object of a connection.  Connection,
;;; block, delta-x-in-workspace, and delta-y-in-workspace are passed as
;;; arguments.  The last two deltas of (delta-or-deltas connection) are
;;; modified.

(def-substitution-macro change-connection-deltas-for-output-end-object-being-dragged
    (connection block delta-x-in-workspace delta-y-in-workspace)
  connection block delta-x-in-workspace	delta-y-in-workspace
  ;; shouldn't have to do anything in this case since last two
  ;; deltas are omitted.
  ;; -- therefore made into a (substitution) macro. (MHD 5/13/90)
  )



;;; The function `change-connection-deltas-for-object-being-dragged' when the
;;; given block has been dragged by the given delta.  If that block was
;;; attached to the connection, we update the connections deltas as needed.

(defun change-connection-deltas-for-object-being-dragged
    (connection block delta-x-in-workspace delta-y-in-workspace)
  (cond ((eq (input-end-object connection) block)
	 (change-connection-deltas-for-input-end-object-being-dragged
	   connection block delta-x-in-workspace delta-y-in-workspace))
	((eq (output-end-object connection) block)
	 (change-connection-deltas-for-output-end-object-being-dragged
	   connection block delta-x-in-workspace delta-y-in-workspace))))



(defmacro side-horizontal-p (side)
  `(memq ,side '(top bottom)))

(defmacro side-vertical-p (side)
  `(memq ,side '(right left)))

(defun side-orientations-same-p (side1 side2)
  (or (and (side-horizontal-p side1)
	   (side-horizontal-p side2))
      (and (side-vertical-p side1)
	   (side-vertical-p side2))))


;;; `Connection-is-straight?' will return the length of the connection if it is
;;; straight, else nil.

(defun connection-is-straight? (connection)
  (with-connection
    connection t t nil
    nil
    (and (null (delta-or-deltas connection))
	 (side-orientations-same-p
	   input-end-side output-end-side)
	 (cond 
	   ((=w input-end-x-position
		output-end-x-position)
	    (-w output-end-y-position
		input-end-y-position))
	   ((=w input-end-y-position
		output-end-y-position)
	    (-w output-end-x-position
		input-end-x-position))))))

;; If no deltas and no bends, then connection is straight.
;; May also want to put a limit on length to check for stubs.



(defun put-kink-into-connection-if-straight (connection blocks)
  (unless (connection-diagonal-p connection)
    (let ((delta?
	    (connection-is-straight? connection)))
      (when (and delta?
	       (not (loose-end-p (car blocks))))       ; if not a loose end being dragged
	  (let ((workspace?			; maybe never nil?!
		  (superblock? (output-end-object connection))))
	    (update-connection-images t workspace? connection)
	    (put-kink-into-connection-if-straight-1 connection delta?)
	    (update-connection-images nil workspace? connection))))))


(defun put-kink-into-connection-if-straight-1 (connection delta)
  (let* ((connection-frame-or-class
	   (connection-frame-or-class connection))
	 (stub-length
	   (get-stub-length-given-connection-frame-or-class
	     connection-frame-or-class)))
    (setf (delta-or-deltas connection)
	  (if (>w delta 0)
	      (minw stub-length delta)
	      (-w (minw stub-length
			(-w delta)))))))


;;; `Compute-stretched-links-of-connection-being-dragged' takes as
;;; arguments a connection and a block and returns the deltas of the
;;; links being stretched and also link-2-orientation-horizontal-p.

(defun compute-stretched-links-of-connection-being-dragged
       (connection block)
  (let* (link-1-delta
	 link-2-delta
	 end-object
	 end-position)
    (if (eq (output-end-object connection) block)
	(setq end-object
	      (output-end-object connection)
	      end-position
	      (output-end-position connection))
	(setq end-object
	      (input-end-object connection)
	      end-position
	      (input-end-position connection)))
    (let* ((block-at-other-end
	     (get-block-at-other-end-of-connection connection block))
	   (other-end-position
	     (get-position-at-this-end-of-connection connection block-at-other-end))
	   (other-end-side
	     (get-side-given-end-position other-end-position))
	   (other-end-initial-orientation-horizontal-p
	     (memq other-end-side '(left right)))
	   (end-side
	     (get-side-given-end-position
	       end-position))
	   (end-position-on-side
	     (get-position-on-side-given-end-position
	       end-position))
	   (end-x-position
	     (+w (left-edge-of-block end-object)
		 (case end-side
		   (left 0)
		   (right (+w (width-of-block end-object) 1))
		   (t  ; if top or bottom
		    end-position-on-side))))
	   (end-y-position
	     (+w (top-edge-of-block end-object)
		 (case end-side
		   (top 0)
		   (bottom (+w (height-of-block end-object) 1))
		   (t  ; if right or left
		    end-position-on-side))))
	   (initial-orientation-horizontal-p
	     (initial-orientation-horizontal-p end-side)))

      (multiple-value-bind
	(connection-anchor-point-x connection-anchor-point-y)
	  (compute-dragged-connection-anchor-point
	    connection block)

      other-end-initial-orientation-horizontal-p

;	(cond
;	  ((and (null (delta-or-deltas connection))
;		(or (and initial-orientation-horizontal-p
;			 other-end-initial-orientation-horizontal-p)
;		    (and (not initial-orientation-horizontal-p)
;			 (not other-end-initial-orientation-horizontal-p))))
;	   ;; If special case of no deltas and output end and input end sides parallel.
;	   ;; This means that connection is straight and object sides are correct.
;	   ;; Note that this is different from connection-is-straight? which doesn't
;	   ;; require for object sides to be correct.  Abstract this into a function!
;	   ;; See also notes in design notebook for 3/17/88.

;	   (setq link-1-delta 

	(if initial-orientation-horizontal-p
	    (setq link-1-delta
		  (-w end-y-position
		      connection-anchor-point-y)
		  link-2-delta
		  (-w end-x-position
		      connection-anchor-point-x))
	    (setq link-1-delta
		  (-w end-x-position
		      connection-anchor-point-x)
		  link-2-delta
		  (-w end-y-position
		      connection-anchor-point-y))))
      (values link-1-delta link-2-delta initial-orientation-horizontal-p))))



;;; `Even-number-of-deltas-in-connection?'  is used by add-bend-to-connection
;;; and delete-bend-from-connection to adjust diagonal connections to have an
;;; even number of deltas if they do not (due to the fact that they have been
;;; converted to diagonal from an orthogonal connection which had an odd number
;;; of deltas).

(defun even-number-of-deltas-in-connection? (connection)
  (let ((delta-or-deltas? (delta-or-deltas connection)))
    (or (null delta-or-deltas?)
	(when (consp delta-or-deltas?)
	  (evenp (length delta-or-deltas?))))))

(defun add-bend-to-connection (connection loose-end)
  (cond
    ((and (connection-diagonal-p connection)
	  (even-number-of-deltas-in-connection? connection))
     (add-bend-to-connection-1 connection loose-end)
     (add-bend-to-connection-1 connection loose-end))
    (t
     (add-bend-to-connection-1 connection loose-end))))

(defun add-bend-to-connection-1
       (connection loose-end)
  (multiple-value-bind
    (link-1-delta link-2-delta)
      (compute-stretched-links-of-connection-being-dragged
	connection loose-end)
    link-2-delta
    (let ((delta-or-deltas
	    (delta-or-deltas connection)))
      (cond
	((eq (output-end-object connection) loose-end)
	 (cond
	   ((null delta-or-deltas)
	    (setf (delta-or-deltas connection) link-1-delta))
	   ((atom delta-or-deltas)
	    (setf (delta-or-deltas connection)
		  (slot-value-list delta-or-deltas link-1-delta)))
	   (t   ; if a cons with length of at least 2
	    (loop for rest-of-deltas
		      on delta-or-deltas
		  until (null (cdr rest-of-deltas))
		  finally
		    (setf (cdr rest-of-deltas)
			  (slot-value-list link-1-delta)))))
	 ;; change end position of connection on loose-end
	 (setf (output-end-position connection)
	       (combine-side-and-position-on-side-for-end-position
		 (case (get-side-given-end-position
			 (output-end-position connection))
		   ((left right) 'top)
		   (t  ; if top or bottom
		    'left))
		 0)))
	(t
	 (cond 
	   ((null delta-or-deltas)
	    (setf (delta-or-deltas connection) 0))
	   ((atom delta-or-deltas)
	    (setf (delta-or-deltas connection)
		  (slot-value-list 0 delta-or-deltas)))
	   (t					; if cons with length of at least 2
	    (setf (delta-or-deltas connection)
		  (slot-value-cons 0 (delta-or-deltas connection)))))
	 ;; change end position of connection on loose-end
	 (setf (input-end-position connection)
	       (combine-side-and-position-on-side-for-end-position
		 (case (get-side-given-end-position
			(input-end-position connection))
		   ((left right) 'top)
		   (t				; if top or bottom
		    'left))
		 0)))))))


(defun remove-kink-and-add-bend
       (connection loose-end link-1-delta)
  link-1-delta
  (let ((delta-or-deltas
	  (delta-or-deltas connection)))
    (cond
      ((null delta-or-deltas)
       (add-bend-to-connection connection loose-end))
      ((atom delta-or-deltas)
       (setf (delta-or-deltas connection) nil)
       (if (eq (output-end-object connection) loose-end)
	   (setf (output-end-position connection)
		 (combine-side-and-position-on-side-for-end-position
		   (case (get-side-given-end-position
			   (output-end-position connection))
		     ((left right) 'top)
		     (t  ; if top or bottom
		      'left))
		   0))
	   (setf (input-end-position connection)
		 (combine-side-and-position-on-side-for-end-position
		   (case (get-side-given-end-position
			   (input-end-position connection))
		     ((left right) 'top)
		     (t  ; if top or bottom
		      'left))
		   0))))
      (t
       (cond
	 ((eq (output-end-object connection) loose-end)
	  (cond 
	    ((null (cddr delta-or-deltas))	; if a list of length 2
	     (setf (delta-or-deltas connection) nil))
	    ((null (cdddr delta-or-deltas))	; if a list of length 3
	     (setf (delta-or-deltas connection)
		   (car (delta-or-deltas connection))))
	    (t					; if a list with length of at least 4
	     (loop for rest-of-deltas
		       on delta-or-deltas
		   until (null (cdddr rest-of-deltas))
		   finally
		     (setf (cdr rest-of-deltas) nil)))))
	 (t
	  (cond 
	    ((null (cddr delta-or-deltas))	; if a list of length 2
	     (setf (delta-or-deltas connection) nil))
	    ((null (cdddr delta-or-deltas))	; if a list of length 3
	     (setf (delta-or-deltas connection)
		   (caddr (delta-or-deltas connection))))
	    (t					; if a list with length of at least 4
	     (setf (delta-or-deltas connection)
		   (cddr (delta-or-deltas connection)))))))
       (add-bend-to-connection connection loose-end)))))



(defun delete-last-bend-from-connection (connection loose-end)
  (cond
    ((and (connection-diagonal-p connection)
	  (even-number-of-deltas-in-connection? connection))
     (delete-last-bend-from-connection-1 connection loose-end)
     (delete-last-bend-from-connection-1 connection loose-end))
    (t
     (delete-last-bend-from-connection-1 connection loose-end))))

(defun delete-last-bend-from-connection-1
       (connection loose-end)
  (let ((delta-or-deltas
	  (delta-or-deltas connection)))
    (cond
      ((eq (output-end-object connection) loose-end)
       (cond
	 ((null delta-or-deltas)
	  ;; shift loose-end so connection is straight
	  (multiple-value-bind
	    (link-1-delta link-2-delta link-2-orientation-horizontal-p)
	      (compute-stretched-links-of-connection-being-dragged
		connection loose-end)
	    link-1-delta
	    (if link-2-orientation-horizontal-p
		(funcall-method
		  'shift loose-end
		  (-w link-2-delta)
		  0)
		(funcall-method
		  'shift loose-end
		  0
		  (-w link-2-delta)))))
	 ((atom delta-or-deltas)
	  (setf (delta-or-deltas connection) nil))
	 ((null (cddr delta-or-deltas))
	  (setf (delta-or-deltas connection)
		(car delta-or-deltas))
	  (reclaim-slot-value-list delta-or-deltas))
	 (t   ; if cons with length of at least 3
	  (loop for rest-of-deltas
		    on (delta-or-deltas connection)
		until (null (cddr rest-of-deltas))
		finally (progn
			  (reclaim-slot-value-list (cdr rest-of-deltas))
			  (setf (cdr rest-of-deltas)
				nil)))))
       ;; change end position of connection on loose-end
       (setf (output-end-position connection)
	     (combine-side-and-position-on-side-for-end-position
	       (case (get-side-given-end-position
		       (output-end-position connection))
		 ((left right) 'top)
		 (t  ; if top or bottom
		  'left))
	       0)))
      (t
       (multiple-value-bind
	 (link-1-delta link-2-delta link-2-orientation-horizontal-p)
	   (compute-stretched-links-of-connection-being-dragged
	     connection loose-end)
	 (cond
	   ((null delta-or-deltas)
	    ;; shift loose-end so connection is straight
	    (if link-2-orientation-horizontal-p
		(funcall-method
		  'shift loose-end
		  (if (eq (get-side-given-end-position
			    (input-end-position connection))
			  'left)
		      (-w link-2-delta)
		      (+w (-w link-2-delta) 1))
		  0)
		(funcall-method
		  'shift loose-end
		  0
		  (if (eq (get-side-given-end-position
			    (input-end-position connection))
			  'top)
		      (-w link-2-delta)
		      (+w (-w link-2-delta) 1)))))
	   ((atom delta-or-deltas)
	    (setf (delta-or-deltas connection) nil))
	   ((null (cddr delta-or-deltas))
	    (setf (delta-or-deltas connection)
		  (cadr delta-or-deltas))
	    (reclaim-slot-value-list delta-or-deltas))
	   (t			; if cons with length of at least 3
	    (let ((old-delta-or-deltas
		    (delta-or-deltas connection)))
	      (setf (delta-or-deltas connection)
		    (cdr delta-or-deltas))
	      (reclaim-slot-value-cons old-delta-or-deltas))))
	 ;; change end position of connection on loose-end
	 (setf (input-end-position connection)
	       (combine-side-and-position-on-side-for-end-position
		 (case (get-side-given-end-position
			 (input-end-position connection))
		   ((left right)
		    (if (>w 0 link-1-delta) 'bottom 'top))
		   (t  ; if top or bottom
		    (if (>w 0 link-1-delta) 'right 'left)))
		 0)))))))



;;; Place-connection-if-orthogonal? returns non-nil if connection is orthogonal
;;; and loose end is near last bend.

(defun place-connection-if-orthogonal? 
       (connection-being-dragged d1 d2 maximum-mouse-leeway)
  (and (connection-orthogonal-p connection-being-dragged)
       (not (loose-end-near-last-anchor-point? 
	      d1 d2 maximum-mouse-leeway))
       (<w d2 (+w maximum-mouse-leeway 4))))

;; 4 gives a bit of extra leeway for pseudo double-click (MHD 8/29/88).

(defun loose-end-near-last-anchor-point? (d1 d2 maximum-mouse-leeway)
  (and (<=w d1 maximum-mouse-leeway)
       (<=w d2 maximum-mouse-leeway)
       (<=w (isqrt (+w (expt d1 2) (expt d2 2)))
	    maximum-mouse-leeway)))

;; Handle-connection-click-near-last-anchor-point returns non-nil if the
;; connection should be placed at this point (if connection is diagonal).

(defun handle-connection-click-near-last-anchor-point 
       (connection-being-dragged loose-end)
  ;; If near last anchor point, delete last bend.
  (when (delta-or-deltas connection-being-dragged)
    ;; Problems occur if connection is made straight
    ;; (as would be the case if delta-or-deltas is
    ;; nil) and dragging continues.
    (delete-last-bend-from-connection
      connection-being-dragged loose-end)
    (connection-diagonal-p connection-being-dragged)))



;;; Delete-connections-without-leaving-stubs?  is bound to t when the "removing
;;; connection stubs" option is specified in the delete action.  Note that this
;;; affects both connections and items with connections on them.  When an item
;;; with connections is deleted by the delete action, and "removing connection
;;; stubs" is specified, stubs are not generated for the items to which the
;;; connections were connected.

(defvar delete-connections-without-leaving-stubs? nil)



;;; Slot value reclaimer for connections.

;;; in the proceed cond, change from superblock check first, to loose end
;;; check first -rdf, 4/8/94

(defun reclaim-connections-value (block)
  (loop for connection-or-name being each connection of block
	do  (note-deletion-of-connection connection-or-name)
	    (let* ((connection-frame-or-class
		     (connection-frame-or-class connection-or-name))
		   (connection-class
		     (get-connection-class-given-connection-frame-or-class
		       connection-frame-or-class))
		   (block-at-other-end-of-connection
		     (get-block-at-other-end-of-connection
		       connection-or-name block))
		   (block-at-other-end-input-object-p
		     (eq (input-end-object connection-or-name)
			 block-at-other-end-of-connection))
		   position-of-block-at-other-end
		   side-of-block-at-other-end
		   position-on-side-of-block-at-other-end
		   new-connection-for-block-at-other-end
		   (proceed-with-delete?
		     (and block-at-other-end-of-connection
			  (framep block-at-other-end-of-connection)
			  (not (frame-being-deleted-p
				 block-at-other-end-of-connection))))
		   ;; Normally, shouldn't have to check for existence of 
		   ;; block-at-other-end-of-connection.  It should always be there.
		   ;; The only time there can be a connection with no input or output
		   ;; end objects is when a knowledge base is partially loaded and then
		   ;; can't finish loading for some reason.  In this case, the kb
		   ;; is deleted once again.  - agh 1/15/88
		   
		   (connection-transient-p 
		     (transient-connection-p connection-or-name))
		   (connection-style?
		     (getfq (connection-attributes-plist connection-or-name) 
			    'connection-style))
		   (line-pattern?
		     (copy-for-slot-value
		       (connection-line-pattern connection-or-name)))
		   (connection-arrows?
		     (copy-for-slot-value
		       (connection-arrows-of-connection connection-or-name)))
		   (direction?
		     (if (connection-not-directed? connection-or-name)
			 nil
			 (if block-at-other-end-input-object-p
			     'output
			     'input))))

	      (when (and proceed-with-delete?
			 (superblock? block-at-other-end-of-connection)
			 block-at-other-end-input-object-p)
		(update-connection-images
		  t (superblock? block-at-other-end-of-connection)
		  connection-or-name))
	      (note-change-to-connection connection-or-name)

	      (let ((fsn (when (framep connection-frame-or-class)
			   (copy-frame-serial-number
			     (frame-serial-number connection-frame-or-class))))
		    (connection-frame-not-deleted nil))
		(when (and fsn
			   (not (frame-being-deleted-p connection-frame-or-class)))
		  (delete-frame connection-frame-or-class))
		(setq connection-frame-not-deleted
		      (and fsn
			   (not (frame-has-been-reprocessed-p
				  connection-frame-or-class fsn))))
		(reclaim-frame-serial-number fsn)
		(setf (connection-frame-or-class connection-or-name)
		      connection-class)

		(when proceed-with-delete?
		  (cond
		    ((loose-end-p block-at-other-end-of-connection)
		     (delete-connection-in-block
		       block-at-other-end-of-connection connection-or-name nil)
		     (unless connection-frame-not-deleted
		       (reclaim-connection-and-delta-or-deltas
			 connection-or-name t)
		       (delete-frame block-at-other-end-of-connection)))

		    ((null (superblock? block-at-other-end-of-connection))
		     (delete-connection-in-block
		       block-at-other-end-of-connection connection-or-name nil)
		     (unless connection-frame-not-deleted
		       (reclaim-connection-and-delta-or-deltas
			 connection-or-name t)))
		    ;; May cause connection to be erased twice.
		    ((when		; `Beware!' This COND condition has side-effects!
			 (default-junction-p block-at-other-end-of-connection)
		       (delete-connection-in-block
			 block-at-other-end-of-connection connection-or-name nil)
		       (unless connection-frame-not-deleted
			 (reclaim-connection-and-delta-or-deltas
			   connection-or-name t))
		       (or (delete-junction-if-appropriate 
			     block-at-other-end-of-connection)
			   delete-connections-without-leaving-stubs?)))

		    (delete-connections-without-leaving-stubs?
		     (delete-connection-in-block
		       block-at-other-end-of-connection connection-or-name nil)
		     (unless connection-frame-not-deleted
		       (reclaim-connection-and-delta-or-deltas
			 connection-or-name t))
		     (when (connection-post-p block-at-other-end-of-connection)
		       (delete-subworkspace-connection-post-if-superfluous
			 block-at-other-end-of-connection)))

		    ((superblock? block-at-other-end-of-connection)
		     ;; Only make stub if block-at-other-end-of-connection
		     ;; still has a superblock.  This is an issue, for example, when
		     ;; workspaces are deleted.  The slot value reclaimer for 
		     ;; subblocks detaches all the subblocks before calling
		     ;; delete-frame with them.

		     (if block-at-other-end-input-object-p
			 (setq position-of-block-at-other-end
			       (input-end-position connection-or-name)
			       side-of-block-at-other-end
			       (get-side-given-end-position
				 position-of-block-at-other-end)
			       position-on-side-of-block-at-other-end
			       (get-position-on-side-given-end-position
				 position-of-block-at-other-end))
			 (setq position-of-block-at-other-end
			       (output-end-position connection-or-name)
			       side-of-block-at-other-end
			       (get-side-given-end-position
				 position-of-block-at-other-end)
			       position-on-side-of-block-at-other-end
			       (get-position-on-side-given-end-position
				 position-of-block-at-other-end)))
		     
		     (setq new-connection-for-block-at-other-end
			   (make-stub
			     block-at-other-end-of-connection
			     connection-class
			     direction?
			     side-of-block-at-other-end
			     position-on-side-of-block-at-other-end
			     connection-transient-p
			     connection-style?
			     line-pattern?
			     connection-arrows?))

		     (when new-connection-for-block-at-other-end
		       (if (connection-exist-p connection-or-name
					       (connections block-at-other-end-of-connection))
			   ;; May have been deleted if input-end-object is
			   ;; a junction block.
			   (progn
			     (replace-connection-in-block
			       block-at-other-end-of-connection
			       connection-or-name
			       new-connection-for-block-at-other-end)
			     (unless connection-frame-not-deleted
			       (reclaim-connection-and-delta-or-deltas
				 connection-or-name t)))
			   (add-connection-in-block
			     block-at-other-end-of-connection
			     new-connection-for-block-at-other-end))
		       (place-stub-loose-end-onto-workspace
			 block-at-other-end-of-connection
			 new-connection-for-block-at-other-end
			 (superblock? block-at-other-end-of-connection))	
		       (update-connection-images 
			 nil (superblock? block-at-other-end-of-connection)
			 new-connection-for-block-at-other-end))))))

	      (when line-pattern?
		(reclaim-slot-value line-pattern?))
	      (when connection-arrows?
		(reclaim-slot-value connection-arrows?))))

  (when (connections block)
    (reclaim-connection-item-table (connections block)))
  (setf (connections block) nil))

;; If not cyclical connection and not connected to a block now being deleted:
;; if connected to a junction or loose end, delete or fix accordingly, else
;; replace by a loose connection (maybe back to a stub).

;; For each connection, delete connection frame if one exists.  Then,
;; get object at other end.  If this object is not already being
;; deleted:  If this object is at input end, then erase connection.  For
;; this object, check whether it should be deleted or whether a stub
;; should replace the connection.  Remember that delete-frame erases the
;; block, and therefore, all output connections of the block.

;; If a stub replaces a connection, then the connection-frame-or-class
;; for the stub will be a class, even if the connection had a frame
;; as connection-frame-or-class.

;; Abstract out the portions of this common with delete-connection-to-stub!
;; Consider combining delete-connection, delete-connection-to-stub, and the
;; connections slot reclaimer into common code which checks
;; delete-connections-without-leaving-stubs?!

(def-class-method cleanup (loose-end)
  (funcall-superior-method loose-end)
  (remove-object-from-dragging-context loose-end))


;;; Delete-block-and-connections will delete the block and all its
;;; connections.  The connections will be deleted back to stubs on
;;; the objects at the other end of the connections, rather than 
;;; being completely deleted.

;(defun delete-block-and-connections (block)
;  (delete-connections-on-block-to-stub block)
;  (delete-connections-on-block block)    ; just stubs now
;  (remove-block-from-superblock
;    block (superblock? block)))
;
;(defun delete-connections-on-block-to-stub (block)
;  (loop for connection being the connections of block
;	do
;    (delete-connection-to-stub connection)))
;
;(defun delete-connections-on-block (block)
;  (loop for connection being the connections of block
;	do
;    (delete-connection connection)))
;; obsolete - taken care of by delete-frame and
;; slot value reclaimer


;;; Ok-to-delete-connection-p checks if either end of the connection
;;; is a junction block.  If so, and if all other connections of the
;;; junction block are directional and have the same direction,
;;; then nil will be returned.

(defun ok-to-delete-connection-p (connection)
  connection
;  (let ((input-end-object
;	  (input-end-object connection))
;	(output-end-object
;	  (output-end-object connection)))
;    (and
;      (if (of-class-p input-end-object 'default-junction)
;	  (loop for connection-of-junction being each connection of input-end-object
;		do (if (not (eq connection-of-junction connection))
;		       (if (or (connection-not-directed? connection-of-junction)
;			       (eq (input-end-object connection-of-junction)
;				   input-end-object))
;			   (return t))))
;	  t)
;      (if (of-class-p output-end-object 'default-junction)
;	  (loop for connection-of-junction being each connection of output-end-object
;		do (if (not (eq connection-of-junction connection))
;		       (if (or (connection-not-directed? connection-of-junction)
;			       (eq (output-end-object connection-of-junction)
;				   output-end-object))
;			   (return t))))
;	  t)))
  t
  )

;; This has changed.  If junction can't be deleted, a stub is left and
;; connection can still be deleted (see delete-junction-if-appropriate).

;; There will undoubtedly be other reasons not to delete a connection
;; which this will have to check for.


;;; `Delete-connection', unlike delete-connection-to-stub, deletes the
;;; connection entirely.  The loose-end, if any, is removed from the workspace
;;; and the connection is removed from the connections slots of the input and
;;; output end objects.

(defun delete-connection (connection
			   &optional (remove-subworkspace-connection-posts-if-appropriate? t)
			   #+connections-v2 (preserved-loose-end? nil))
  (note-deletion-of-connection connection)
  (let* ((input-end-object
	  (input-end-object connection))
	(output-end-object
	  (output-end-object connection))
	(connection-frame-or-class
	  (connection-frame-or-class connection))
	(connection-frame-not-deleted nil))

   (with-deferred-drawing ()			    ; Note A
      (update-connection-images 'delete (superblock? output-end-object) connection)
      (delete-connection-in-block
	output-end-object connection remove-subworkspace-connection-posts-if-appropriate?)
      (delete-connection-in-block
	input-end-object connection remove-subworkspace-connection-posts-if-appropriate?)
      (let ((fsn (if (framep connection-frame-or-class)
		     (copy-frame-serial-number (frame-serial-number connection-frame-or-class)))))
	(when fsn
	  (delete-frame connection-frame-or-class))
	(setq connection-frame-not-deleted
	      (and fsn
		   (not (frame-has-been-reprocessed-p
			  connection-frame-or-class fsn))))
	(reclaim-frame-serial-number fsn)
	;; NOTE: here, if the function is called from
	;; `make-cloned-connection-stub-be-copy-of-connection', in which cloned
	;; temporary connections were deleted, an extra 2rd optional argument is
	;; used to protect and preserve external loose-ends - they shouldn't be
	;; deleted in this case. This fixed gedpq-test.kb.  --binghe, Aug2015
	(unless connection-frame-not-deleted 
	  (cond
	    ((and (loose-end-p input-end-object)
		  #+connections-v2
		  (neq preserved-loose-end? input-end-object))
	     (delete-frame input-end-object))
	    ((and (loose-end-p output-end-object)
		  #+connections-v2
		  (neq preserved-loose-end? output-end-object))
	     (delete-frame output-end-object))))

	(when remove-subworkspace-connection-posts-if-appropriate?
	  (when (and (framep output-end-object)
		     (connection-post-p output-end-object)
		     #+connections-v2
		     (neq preserved-loose-end? output-end-object))
	    (delete-subworkspace-connection-post-if-superfluous output-end-object))
	  (when (and (framep input-end-object)
		     (connection-post-p input-end-object)
		     #+connections-v2
		     (neq preserved-loose-end? input-end-object))
	    (delete-subworkspace-connection-post-if-superfluous input-end-object)))

	(remove-object-from-dragging-context connection)

	(unless connection-frame-not-deleted
	  (reclaim-connection-and-delta-or-deltas connection t))))))

;; Note A: This binding, here and in delete-connection-to-stub, below, is
;; required in paint mode so that the drawing substrate does not try to drain
;; the queue before all data structures reflect the deletion.  This is because,
;; in paint mode, we can't actually erase anything, as we can in XOR mode: we
;; can only invalidate a region, update the KB, then redraw. -fmw, 10/17/94



;;; The function `delete-connection-to-stub' deletes the given connection,
;;; putting back stubs to replace it.

(defun delete-connection-to-stub (connection)
  (note-deletion-of-connection connection)
  (let* ((connection-frame-or-class
	   (connection-frame-or-class connection))
	 (connection-class
	   (get-connection-class-given-connection-frame-or-class
	     connection-frame-or-class))
	 (connection-transient-p
	   (transient-connection-p connection))
	 (connection-style?
	   (getfq (connection-attributes-plist connection)
		  'connection-style))
	 (line-pattern?
	   (copy-for-slot-value
	     (connection-line-pattern connection)))
	 (connection-arrows?
	   (copy-for-slot-value
	     (connection-arrows-of-connection connection)))
	 (input-end-object-to-delete nil)
	 (output-end-object-to-delete nil))

    (with-deferred-drawing ()
      (with-connection
	  connection t nil nil
	  (new-input-end-connection)
	(declare (ignore input-end-x-position input-end-y-position))
	(update-connection-images 'delete (superblock? input-end-object) connection)
	(cond
	  ((and (framep input-end-object)
		(loose-end-p input-end-object))
	   (delete-connection-in-block
	     input-end-object connection nil)
	   (setq input-end-object-to-delete
		 input-end-object))
	  ((when (and (framep input-end-object)
		      (default-junction-p input-end-object))
	     (delete-connection-in-block
	       input-end-object connection nil)
	     (if (not (eq input-end-object
			  (output-end-object connection)))
		 (delete-junction-if-appropriate input-end-object))))
	  (t
	   (setq new-input-end-connection
		 (make-stub
		   input-end-object
		   connection-class
		   (if (connection-not-directed? connection)
		       nil
		       'output)
		   input-end-side
		   input-end-position-on-side
		   connection-transient-p
		   connection-style?
		   line-pattern?
		   connection-arrows?))
	   (place-stub-loose-end-onto-workspace
	     input-end-object new-input-end-connection
	     (superblock? input-end-object))
	   (if (connection-exist-p connection
				   (connections input-end-object))
	       ;; May have been deleted if input-end-object is
	       ;; a junction block.
	       (replace-connection-in-block
		 input-end-object
		 connection
		 new-input-end-connection)
	       (add-connection-in-block
		 input-end-object
		 new-input-end-connection))
	   (update-connection-images 
	     nil (superblock? input-end-object) new-input-end-connection))))

      (with-connection
	  connection nil t nil
	  (new-output-end-connection)
	(declare (ignore output-end-x-position output-end-y-position))
	(cond
	  ((loose-end-p output-end-object)
	   (delete-connection-in-block
	     output-end-object connection nil)
	   (setq output-end-object-to-delete
		 output-end-object))

	  ((when (default-junction-p output-end-object)
	     (delete-connection-in-block
	       output-end-object connection nil)
	     (if (not (eq output-end-object
			  (input-end-object connection)))
		 (delete-junction-if-appropriate output-end-object))))
	  (t
	   (setq new-output-end-connection
		 (make-stub
		   output-end-object
		   connection-class
		   (if (connection-not-directed? connection)
		       nil
		       'input)
		   output-end-side
		   output-end-position-on-side
		   connection-transient-p
		   connection-style?
		   line-pattern?
		   connection-arrows?))
	   (place-stub-loose-end-onto-workspace
	     output-end-object new-output-end-connection
	     (superblock? output-end-object))
	   (if (connection-exist-p connection
				   (connections output-end-object))
	       ;; May have been deleted if output-end-object is
	       ;; a junction block.
	       (replace-connection-in-block
		 output-end-object
		 connection
		 new-output-end-connection)
	       (add-connection-in-block
		 output-end-object
		 new-output-end-connection))
	   (update-connection-images 
	     nil (superblock? output-end-object) new-output-end-connection))))

      ;; Delete the connection frame while the connection structure is
      ;; still valid.
      (let ((fsn (if (framep connection-frame-or-class)
		     (copy-frame-serial-number (frame-serial-number connection-frame-or-class)))))
	(when fsn
	  (delete-frame connection-frame-or-class))
	(unless (and fsn
		     (not (frame-has-been-reprocessed-p 
			    connection-frame-or-class fsn)))
	  (when input-end-object-to-delete
	     (delete-frame input-end-object-to-delete))
	  (when output-end-object-to-delete
	     (delete-frame output-end-object-to-delete))
	  (reclaim-connection-and-delta-or-deltas connection nil))
	(reclaim-frame-serial-number fsn)))

    (when line-pattern?
      (reclaim-slot-value line-pattern?))		
    (when connection-arrows?
      (reclaim-slot-value connection-arrows?))))



;;; `Delete-junction-if-appropriate' takes a junction as its argument.  If the
;;; junction has zero or one connections on it, then the junction is deleted
;;; and the connection, if any, is deleted back to a stub.  If the junction has
;;; two connections on it, and if they don't have opposing directionality, then
;;; the junction is deleted and the connections are joined into one if
;;; possible.  If the two connections do have opposing directionality, nothing
;;; is deleted.  Likewise, if there are more than two connections on the
;;; junction, then nothing is deleted.  Delete-junction-if-appropriate will
;;; return t if the junction is deleted.

;;; Delete-junction-if-appropriate expects to be called when junction is

(defvar junction-blocks-not-to-be-deleted nil)

(defun delete-junction-if-appropriate (junction-block)
  (when (not (memq junction-block junction-blocks-not-to-be-deleted))
    (let ((junction-connections
	    (loop for connection being the connections of junction-block
		  collect connection using gensym-cons))
	  (junction-block-half-width
	    (halfw (width-of-block junction-block))))
      (prog1
	  (cond ; level 1
	    ((or (null junction-connections)
		 (null (cdr junction-connections)))
	     (delete-frame junction-block)
	     t)
	    ((null (cddr junction-connections))
	     (let* ((junction-connection-1
		      (car junction-connections))
		    (junction-connection-2
		      (cadr junction-connections))
		    junction-connection-1-end-position-side
		    junction-connection-1-opposite-end-position-side	     
		    junction-connection-2-end-position-side
		    loose-end-1 loose-end-2
		    (block-at-other-end-of-connection-1
		      (get-block-at-other-end-of-connection
			junction-connection-1 junction-block))
		    (block-at-other-end-of-connection-2
		      (get-block-at-other-end-of-connection
			junction-connection-2 junction-block))
		    (workspace? (superblock? junction-block)))

	       ;; Delete junction and join connections into one if appropriate
	       ;; (if cross sections and directions are compatible, and if 
	       ;; a superblock for the junction exists).
	       ;; Otherwise, just delete junction.
	       (cond ; level 2
		 ((and workspace?
		       (not (and (loose-end-p block-at-other-end-of-connection-1)
				 (loose-end-p block-at-other-end-of-connection-2)))
		       (not (or (frame-being-deleted-p
				  block-at-other-end-of-connection-1)
				(frame-being-deleted-p
				  block-at-other-end-of-connection-2)))
		       (connection-cross-section-patterns-compatible?
			 junction-connection-1 junction-connection-2)
		       (if (connection-not-directed? junction-connection-1)
			   (connection-not-directed? junction-connection-2)
			   (and (connection-directed? junction-connection-2)
				(not
				  (or
				    (and (eq (input-end-object junction-connection-1)
					     junction-block)
					 (eq (input-end-object junction-connection-2)
					     junction-block))
				    (and (eq (output-end-object junction-connection-1)
					     junction-block)
					 (eq (output-end-object junction-connection-2)
					     junction-block)))))))
		
		  (update-connection-images t workspace? junction-connection-1)
		  (update-connection-images t workspace? junction-connection-2)

		  (setq loose-end-1
			(make-frame 'loose-end)
			loose-end-2
			(make-frame 'loose-end))
		  (add-subblock loose-end-1 workspace?)
		  (add-subblock loose-end-2 workspace?)

		  (delete-connection-in-block
		    junction-block junction-connection-1 nil)
		  (delete-connection-in-block
		    junction-block junction-connection-2 nil)

		  #-connections-v2
		  (setf (connections loose-end-1)
			(slot-value-list 'junction-connection-1 junction-connection-1)
			(connections loose-end-2)
			(slot-value-list 'junction-connection-2 junction-connection-2))
		  #+connections-v2
		  (let ((connection-table-1 (make-connection-item-table))
			(connection-table-2 (make-connection-item-table))
			(connection-item-1 (make-connection-item junction-connection-1))
			(connection-item-2 (make-connection-item junction-connection-2)))
		    (case (get-direction-of-connection junction-connection-1
						       block-at-other-end-of-connection-1)
		      (output
		       (setf (connection-item-input-names connection-item-1)
			     (slot-value-list 'junction-connection-1)))
		      (t ; input or undirected
		       (setf (connection-item-output-names connection-item-1)
			   (slot-value-list 'junction-connection-1))))
		    (case (get-direction-of-connection junction-connection-2
						       block-at-other-end-of-connection-2)
		      (output
		       (setf (connection-item-input-names connection-item-2)
			     (slot-value-list 'junction-connection-2)))
		      (t ; input or undirected
		       (setf (connection-item-output-names connection-item-2)
			     (slot-value-list 'junction-connection-2))))
		    (setf (get-connection-item junction-connection-1 connection-table-1)
			  connection-item-1)
		    (setf (get-connection-item junction-connection-2 connection-table-2)
			  connection-item-2)
		    (setf (connections loose-end-1) connection-table-1)
		    (setf (connections loose-end-2) connection-table-2))

		  (cond ; level 3
		    ((eq (input-end-object junction-connection-1) junction-block)
		     (setq junction-connection-1-end-position-side
			   (get-side-given-end-position
			     (input-end-position junction-connection-1))
			   junction-connection-1-opposite-end-position-side
			   (get-side-given-end-position
			     (output-end-position junction-connection-1)))

		     ;; add bend to junction-connection-1 if straight
		     ;; so that join-two-connections will work properly
		     ;; (junction-connection-1 has to look as if it is being dragged)
		     (if (null (delta-or-deltas junction-connection-1))
			 (case junction-connection-1-end-position-side
			   (left
			    (if (memq junction-connection-1-opposite-end-position-side '(left right))
				(setq junction-connection-1-end-position-side 'top)))
			   (right
			    (if (memq junction-connection-1-opposite-end-position-side '(left right))
				(setq junction-connection-1-end-position-side 'top)))
			   (top
			    (if (memq junction-connection-1-opposite-end-position-side '(top bottom))
				(setq junction-connection-1-end-position-side 'left)))
			   (t			; if bottom
			    (if (memq junction-connection-1-opposite-end-position-side '(top bottom))
				(setq junction-connection-1-end-position-side 'left)))))

		     (set-input-end-of-connection
		       junction-connection-1 loose-end-1
		       junction-connection-1-end-position-side 0)
		     (cond ; level 4
		       ((eq (input-end-object junction-connection-2) junction-block)
			(setq junction-connection-2-end-position-side
			      (get-side-given-end-position
			        (input-end-position junction-connection-2)))
			(set-input-end-of-connection
			  junction-connection-2 loose-end-2
			  junction-connection-2-end-position-side 0))
		       (t ; default of level 4
			(setq junction-connection-2-end-position-side
			      (get-side-given-end-position
			        (output-end-position junction-connection-2)))
			(set-output-end-of-connection
			  junction-connection-2 loose-end-2
			  junction-connection-2-end-position-side 0))))
		    (t ; default of level 3
		     (setq junction-connection-1-end-position-side
			   (get-side-given-end-position
			     (output-end-position junction-connection-1))
			   junction-connection-1-opposite-end-position-side
			   (get-side-given-end-position
			     (input-end-position junction-connection-1)))

		     ;; add bend to junction-connection-1 if straight
		     ;; so that join-two-connections will work properly
		     ;; (junction-connection-1 has to look as if it is being dragged)
		     (if (null (delta-or-deltas junction-connection-1))
			 (case junction-connection-1-end-position-side
			   (left
			    (if (memq junction-connection-1-opposite-end-position-side '(left right))
				(setq junction-connection-1-end-position-side 'top)))
			   (right
			    (if (memq junction-connection-1-opposite-end-position-side '(left right))
				(setq junction-connection-1-end-position-side 'top)))
			   (top
			    (if (memq junction-connection-1-opposite-end-position-side '(top bottom))
				(setq junction-connection-1-end-position-side 'left)))
			   (t			; bottom
			    (if (memq junction-connection-1-opposite-end-position-side '(top bottom))
				(setq junction-connection-1-end-position-side 'left)))))

		     (set-output-end-of-connection
		       junction-connection-1 loose-end-1
		       junction-connection-1-end-position-side 0)
		     (cond ; level 4
		       ((eq (input-end-object junction-connection-2) junction-block)
			(setq junction-connection-2-end-position-side
			      (get-side-given-end-position
			        (input-end-position junction-connection-2)))
			(set-input-end-of-connection
			  junction-connection-2 loose-end-2
			  junction-connection-2-end-position-side 0))
		       (t ; default of level 4
			(setq junction-connection-2-end-position-side
			      (get-side-given-end-position
			        (output-end-position junction-connection-2)))
			(set-output-end-of-connection
			  junction-connection-2 loose-end-2
			  junction-connection-2-end-position-side 0))))) ; end of level 3

		  ;; shift loose ends to end positions of junction block
		  (funcall-method
		    'shift loose-end-1
		    (-w (case junction-connection-1-end-position-side
			  (left
			   (left-edge-of-block junction-block))
			  (right
			   (right-edge-of-block junction-block))
			  (t
			   (+w (left-edge-of-block junction-block)
			       junction-block-half-width)))
			(left-edge-of-block loose-end-1))
		    (-w (case junction-connection-1-end-position-side
			  (top
			   (top-edge-of-block junction-block))
			  (bottom
			   (bottom-edge-of-block junction-block))
			  (t
			   (+w (top-edge-of-block junction-block)
			       junction-block-half-width)))
			(top-edge-of-block loose-end-1)))

		  (funcall-method
		    'shift loose-end-2
		    (-w (case junction-connection-2-end-position-side
			  (left
			   (left-edge-of-block junction-block))
			  (right
			   (right-edge-of-block junction-block))
			  (t
			   (+w (left-edge-of-block junction-block)
			       junction-block-half-width)))
			(left-edge-of-block loose-end-2))
		    (-w (case junction-connection-2-end-position-side
			  (top
			   (top-edge-of-block junction-block))
			  (bottom
			   (bottom-edge-of-block junction-block))
			  (t
			   (+w (top-edge-of-block junction-block)
			       junction-block-half-width)))
			(top-edge-of-block loose-end-2)))

		  ;; drag loose-end-2 with connection to center of junction-block
		  (change-connection-deltas-for-object-being-dragged
		    junction-connection-2 loose-end-2
		    (-w (+w (left-edge-of-block junction-block)
			    junction-block-half-width)
			(left-edge-of-block loose-end-2))
		    (-w (+w (top-edge-of-block junction-block)
			    junction-block-half-width)
			(top-edge-of-block loose-end-2)))

		  (update-images-of-block loose-end-1 nil nil)
		  (update-images-of-block loose-end-2 nil nil)
		  (if (eq (output-end-object junction-connection-1) loose-end-1)
		      (update-connection-images nil workspace? junction-connection-1))
		  (if (eq (output-end-object junction-connection-2) loose-end-2)
		      (update-connection-images nil workspace? junction-connection-2))

		  (join-two-connections loose-end-1 loose-end-2)
		  (delete-frame junction-block)
		  t)
		 ) ; end of level 2
	       ) ; let*
	     ) ; null
	    ) ; end of level 1
	(reclaim-gensym-list junction-connections)
	) ; prog1
      ) ; let
    ) ; when
  ) ; defun

;; Revised above as follows: (1) bind workspace? in the let, (2) use workspace?
;; instead of (superblock? ...) several times, (3) use update-image-of-block or
;; update-connection-images where necessary to avoid calling update-images
;; directly.  (MHD 4/12/91)


;; Consider sending some sort of error message if there are 
;; directionality conflicts.

;; recycle conses


;(defun junction-on-corner-p
;       (junction-connection-1-end-position-side
;	junction-connection-2-end-position-side)
;  (case junction-connection-1-end-position-side
;    (left
;      (not (eq junction-connection-2-end-position-side 'right)))
;    (right
;      (not (eq junction-connection-2-end-position-side 'left)))
;    (top
;      (not (eq junction-connection-2-end-position-side 'bottom)))
;    (bottom
;      (not (eq junction-connection-2-end-position-side 'top)))))

;; Not currently needed!




;; The following function has been moved here from the former CAPABILITY
;; module.  (ghw 2/8/94)

(defun add-subworkspace-connection-post-if-appropriate (connection object)
  (when (and (of-class-p object 'object)
	     (subworkspace-connection-posts-p object))
    (loop with port-name? = (get-port-name-given-block-and-connection
			      object connection)
	  for subworkspace in (subworkspaces object)
	  do
      (add-subworkspace-connection-post
	connection port-name? object subworkspace))))




;;; `Add-new-connection-to-block' takes loose-end-1 and a block as arguments.
;;; The connection being dragged is made a connection of the block.  The
;;; connection deltas are also modified appropriately.  This function returns
;;; two values.  The first indicates whether a connection was made or a
;;; connection was deleted, which implies that the dragging action that was
;;; invoking this function can return from its workstation context.  The second
;;; value is non-NIL when the first value is non-NIL and we are deleting a
;;; connection due to it being dragged back into the block from which it came.

(defun add-new-connection-to-block
       (loose-end block
	&optional (allow-multiple-connections-on-junction-side? nil))
  (let* ((connection
	   (get-connection-for-loose-end loose-end))
	 (connection-frame-or-class
	   (connection-frame-or-class connection))
	 (connection-overall-width
	   (compute-connection-width-given-connection-frame-or-class
	     connection-frame-or-class))
	 (connection-half-width
	   (halfw connection-overall-width))
	 (loose-end-delta-x-in-workspace 0)
	 (loose-end-delta-y-in-workspace 0)
	 side position-on-side make-connection?
	 desired-position-on-side?)

    (if (eq (get-block-at-other-end-of-connection 
	      connection loose-end)
	    block)
	(cond
	  ((loose-end-within-block-p block loose-end)
	   ;; if inside same block, delete connection
	   (delete-connection connection)
	   (values t t)))

	(multiple-value-bind 
	  (current-link-1-delta current-link-2-delta
	   loose-end-initial-orientation-horizontal-p)
	    (compute-stretched-links-of-connection-being-dragged
	      connection loose-end)
	  (cond ; level 1
	    ((default-junction-p block)
	     (when (loose-end-within-block-p block loose-end)
	       ;; if inside junction block
	       (setq desired-position-on-side? (halfw (width-of-block block)))
	       (update-connection-images t (superblock? loose-end) connection)
	       (multiple-value-setq
		 (side position-on-side
		  loose-end-delta-x-in-workspace 
		  loose-end-delta-y-in-workspace)
		 (compute-side-of-exit
		   block loose-end connection
		   current-link-1-delta 
		   current-link-2-delta 
		   loose-end-initial-orientation-horizontal-p 
		   desired-position-on-side?))
		
	       ;; check if side already has a connection
	       (cond ; level 2
		 ((and side
		       (or (not (side-of-junction-has-connection-p block side))
			   allow-multiple-connections-on-junction-side?))
		  (setq make-connection? t)
		  (let ((delta? (connection-is-straight? connection)))
		    (when delta?
		      (put-kink-into-connection-if-straight-1 
			connection delta?))))
		 (t
		  (update-connection-images 
		    nil (superblock? loose-end) connection)))))
	    (t
	     (cond ; level 2
	       ((loose-end-within-block-and-border-p
		  block loose-end connection-half-width)
		;; if inside block with enough room to spare
		
		(update-connection-images 
		  t (superblock? loose-end) connection)

		(multiple-value-setq
		  (side position-on-side
		   loose-end-delta-x-in-workspace 
		   loose-end-delta-y-in-workspace)
		  (compute-side-of-exit
		    block loose-end connection
		    current-link-1-delta 
		    current-link-2-delta 
		    loose-end-initial-orientation-horizontal-p nil))

		(cond ; level 3
		  (side (setq make-connection? t))
		  (t
		   (update-connection-images 
		     nil (superblock? loose-end) connection)))
		)))) ; end of level 1
	  
	  (cond ; level 1
	    ((and make-connection?
		  side position-on-side)
	     (funcall-method 'shift loose-end
	       loose-end-delta-x-in-workspace
	       loose-end-delta-y-in-workspace)
	     (cond ; level 2
	       ((eq (input-end-object connection) loose-end)
		(change-connection-deltas-for-input-end-object-being-dragged
		  connection loose-end 
		  loose-end-delta-x-in-workspace loose-end-delta-y-in-workspace)

		(when (connection-diagonal-p connection)
		  (let ((loose-end-side
			  (get-side-given-end-position
			    (input-end-position connection))))
		    (when (not (side-orientations-same-p loose-end-side side))
		      (add-missing-deltas-to-connection connection)
		      (let ((temp1 
			      (reverse-connection-delta-pairs
				(delta-or-deltas connection))))
			(reclaim-slot-value-list (delta-or-deltas connection))
			(setf (delta-or-deltas connection) temp1))
		      (remove-redundant-deltas-from-connection connection))))

		(setf (input-end-object connection) block
		      (input-end-position connection)
		      (combine-side-and-position-on-side-for-end-position
			side position-on-side)))
	       (t
		(change-connection-deltas-for-output-end-object-being-dragged
		  connection loose-end 
		  loose-end-delta-x-in-workspace loose-end-delta-y-in-workspace)
		(setf (output-end-object connection) block
		      (output-end-position connection)
		      (combine-side-and-position-on-side-for-end-position
			side position-on-side))))
	     (add-connection-in-block block connection)
	     (add-subworkspace-connection-post-if-appropriate
	       connection block)

	     (update-connection-images 
	       nil (superblock? loose-end) connection)
	     (when (and (eq block (input-end-object connection))
			(ws-has-ws-representation-p (superblock? block)))
	       (send-ws-representations-item-layer-change
		 (get-or-make-connection-frame-and-activate-if-appropriate connection)
		 (superblock? block)
		 (find-connection-or-block-below-this-connection
		   connection block)))

	     (setf (connections loose-end) nil)
	     (delete-frame loose-end)

	     t))))))

(defun-simple find-connection-or-block-below-this-connection (connection block)
  (or (loop with c1 = nil
	    for c2 being the output-connections of block
	    do
	(when (eq c2 connection)
	  (if (null c1)
	      (return block)
	      (return (get-or-make-connection-frame-and-activate-if-appropriate c1))))
	(setf c1 c2))
      block))

;; Review this function.  We are suspicious that the connections slot is not
;; being reclaimed!!  -cpm, mhd 6/3/93

;; Currently, if connection is dragged into same block, the connection is
;; deleted.  Consider deleting if only near stub position!



;;; Compute-side-of-exit-given-last-bend computes the side where the connection
;;; exits the block and also computes the x and y deltas between the position of
;;; the loose end and the position where the connection should be put on the side.
;;; Desired-position-on-side?  can be passed in as an argument.  This is used for
;;; junction blocks where the connection must be centered on the side.

(defun compute-side-of-exit 
       (block loose-end connection 
	current-link-1-delta current-link-2-delta 
	loose-end-initial-orientation-horizontal-p
	desired-position-on-side?)
  (let (side position-on-side
	loose-end-delta-x-in-workspace loose-end-delta-y-in-workspace
	x-position-of-last-bend y-position-of-last-bend
	x-position-of-next-to-last-bend y-position-of-next-to-last-bend)
    (cond
      ((connection-completely-inside-block-p connection loose-end block)
       (multiple-value-setq
	 (side position-on-side
	  loose-end-delta-x-in-workspace loose-end-delta-y-in-workspace)
	 (compute-info-for-connection-inside-block 
	   loose-end block current-link-2-delta 
	   loose-end-initial-orientation-horizontal-p)))
      (t
       ;; Iterate through previous links until at link which exits block.
       ;; Keep track of delta-x and delta-y which must change.
       
       (multiple-value-setq
	 (x-position-of-last-bend y-position-of-last-bend
	  x-position-of-next-to-last-bend y-position-of-next-to-last-bend)
	 (compute-positions-of-last-bends
	   loose-end current-link-1-delta current-link-2-delta 
	   loose-end-initial-orientation-horizontal-p))
       (loop with last-chance? = nil
	     doing
	 (multiple-value-setq
	   (side 
	    loose-end-delta-x-in-workspace
	    loose-end-delta-y-in-workspace
	    position-on-side)
	   (compute-side-of-exit-given-last-bend
	     block loose-end 
	     x-position-of-last-bend y-position-of-last-bend
	     x-position-of-next-to-last-bend y-position-of-next-to-last-bend
	     (connection-diagonal-p connection)
	     desired-position-on-side?))
	 (cond
	   (side (return (values)))
	   (last-chance? (return (values)))
	   (t			  ; if last bend is within block
	    (delete-last-bend-from-connection connection loose-end)
	    (multiple-value-bind 
	      (current-link-1-delta current-link-2-delta
	       loose-end-initial-orientation-horizontal-p)
		(compute-stretched-links-of-connection-being-dragged
		  connection loose-end)
	      current-link-1-delta
	      (multiple-value-setq
		(x-position-of-last-bend y-position-of-last-bend
		 x-position-of-next-to-last-bend y-position-of-next-to-last-bend)
		(compute-positions-of-last-bends
		  loose-end current-link-1-delta current-link-2-delta 
		  loose-end-initial-orientation-horizontal-p)))
	    (setq loose-end-delta-x-in-workspace 0
		  loose-end-delta-y-in-workspace 0)
	    (setq last-chance? t))))))
    (values side position-on-side
	    loose-end-delta-x-in-workspace loose-end-delta-y-in-workspace)))

;; The loop and delete-last-bend-from-connection is necessary for the case where
;; the first and possibly subsequent bends away from the loose end are within the
;; block.  This can easily happen when dragging a connection in and the first link
;; from the loose end is short.  A more obscure case is when a large block is
;; dragged over a portion of a connection with many bends, and then one end of the
;; connection is dragged into this block.



;;; Compute-position-of-last-bend returns x-position-of-last-bend and
;;; y-position-of-last-bend.

(defun compute-positions-of-last-bends
       (loose-end next-to-last-link-delta last-link-delta
	loose-end-initial-orientation-horizontal-p)
  (if loose-end-initial-orientation-horizontal-p
      (let ((x-position-of-last-bend
	      (-w (left-edge-of-block loose-end) last-link-delta))
	    (y-position-of-last-bend
	      (top-edge-of-block loose-end)))
	(values x-position-of-last-bend y-position-of-last-bend
		x-position-of-last-bend
		(-w y-position-of-last-bend next-to-last-link-delta)))
      (let ((x-position-of-last-bend
	      (left-edge-of-block loose-end))
	    (y-position-of-last-bend
	      (-w (top-edge-of-block loose-end) last-link-delta)))
	(values x-position-of-last-bend y-position-of-last-bend 
		(-w x-position-of-last-bend next-to-last-link-delta)
		y-position-of-last-bend))))



(defun loose-end-within-block-p (block loose-end)
  (loose-end-within-block-and-border-p block loose-end 0))

(defun loose-end-within-block-and-border-p (block loose-end border)
  (and (>w (top-edge-of-block loose-end)
	   (+w (top-edge-of-block block) border))
       (<w (bottom-edge-of-block loose-end)
	   (-w (bottom-edge-of-block block) border))
       (>w (left-edge-of-block loose-end)
	   (+w (left-edge-of-block block) border))
       (<w (right-edge-of-block loose-end)
	   (-w (right-edge-of-block block) border))))



;;; Compute-side-of-exit-given-last-bend checks if the bend is outside of the
;;; block.  If so, it computes the side where the connection exits the block and
;;; also computes the x and y deltas between the position of the loose end and the
;;; position where the connection should be put on the side.
;;; Desired-position-on-side?  can be passed in as an argument.  This is used for
;;; junction blocks where the connection must be centered on the side.  If the
;;; bend is outside the block, compute-side-of-exit-given-last-bend returns the
;;; side of exit, the x and y deltas, and the position on side.

(defun compute-side-of-exit-given-last-bend
       (block loose-end 
	 x-position-of-last-bend y-position-of-last-bend
	 x-position-of-next-to-last-bend y-position-of-next-to-last-bend
	 connection-diagonal-p
	 desired-position-on-side?)
  (if connection-diagonal-p
      (compute-side-of-exit-for-diagonal-connection
	block loose-end
	x-position-of-next-to-last-bend y-position-of-next-to-last-bend)
      (compute-side-of-exit-for-orthogonal-connection
	block loose-end
	x-position-of-last-bend y-position-of-last-bend
	desired-position-on-side?)))

(defun compute-side-of-exit-for-diagonal-connection
       (block loose-end
	 x-position-of-next-to-last-bend y-position-of-next-to-last-bend)
  (let ((intercept? nil))
    (cond
      ((and (>w x-position-of-next-to-last-bend (right-edge-of-block block))
	    (setq intercept?
		  (compute-intercept-with-vertical-side
		    (right-edge-of-block block)
		    block loose-end
		    x-position-of-next-to-last-bend y-position-of-next-to-last-bend)))
       (values 'right
	       (-w (right-edge-of-block block)
		   (left-edge-of-block loose-end))
	       (-w intercept? (top-edge-of-block loose-end))
 	       (-w intercept? (top-edge-of-block block))))
      ((and (<w x-position-of-next-to-last-bend (left-edge-of-block block))
	    (setq intercept?
		  (compute-intercept-with-vertical-side
		    (left-edge-of-block block)
		    block loose-end
		    x-position-of-next-to-last-bend y-position-of-next-to-last-bend)))
       (values 'left 
	       (-w (left-edge-of-block block)
		   (left-edge-of-block loose-end))
	       (-w intercept? (top-edge-of-block loose-end))
	       (-w intercept? (top-edge-of-block block))))
      ((and (>w y-position-of-next-to-last-bend (bottom-edge-of-block block))
	    (setq intercept?
		  (compute-intercept-with-horizontal-side
		    (bottom-edge-of-block block)
		    block loose-end
		    x-position-of-next-to-last-bend y-position-of-next-to-last-bend)))
       (values 'bottom 
	       (-w intercept? (left-edge-of-block loose-end))
	       (-w (bottom-edge-of-block block)
		   (top-edge-of-block loose-end))
	       (-w intercept? (left-edge-of-block block))))
      ((and (<w y-position-of-next-to-last-bend (top-edge-of-block block))
	    (setq intercept?
		  (compute-intercept-with-horizontal-side
		    (top-edge-of-block block)
		    block loose-end
		    x-position-of-next-to-last-bend y-position-of-next-to-last-bend)))
       (values 'top 
	       (-w intercept? (left-edge-of-block loose-end))
	       (-w (top-edge-of-block block)
		   (top-edge-of-block loose-end))
	       (-w intercept? (left-edge-of-block block)))))))

(defun compute-intercept-with-vertical-side
       (side-x block loose-end x1 y1)
  (with-temporary-gensym-float-creation compute-intercept-with-vertical-side
    (let* ((fx1 (coerce-to-gensym-float x1))
	   (fy1 (coerce-to-gensym-float y1))
	   (fx2 (coerce-to-gensym-float (left-edge-of-block loose-end)))
	   (fy2 (coerce-to-gensym-float (top-edge-of-block loose-end)))
	   (delta-x (-e fx2 fx1))
	   (delta-y (-e fy2 fy1))
	   (fside-x (coerce-to-gensym-float side-x))
	   (intercept? nil))
      (cond 
	((=e delta-x 0.0)
	 ;; shouldn't happen
	 )
	((=e delta-y 0.0)
	 (setq intercept? y1))
	(t
	 (setq intercept?
	       (round (+e (/e (*e fside-x delta-y) delta-x)
			  (-e (/e (*e fx1 delta-y) delta-x))
			  fy1)))))
      (when (and intercept?
		 (>w intercept? (top-edge-of-block block))
		 (<w intercept? (bottom-edge-of-block block)))
	intercept?))))

(defun compute-intercept-with-horizontal-side
       (side-y block loose-end x1 y1)
  (with-temporary-gensym-float-creation compute-intercept-with-horizontal-side
    (let* ((fx1 (coerce-to-gensym-float x1))
	   (fy1 (coerce-to-gensym-float y1))
	   (fx2 (coerce-to-gensym-float (left-edge-of-block loose-end)))
	   (fy2 (coerce-to-gensym-float (top-edge-of-block loose-end)))
	   (delta-x (-e fx2 fx1))
	   (delta-y (-e fy2 fy1))
	   (fside-y (coerce-to-gensym-float side-y))
	   (intercept? nil))
      (cond 
	((=e delta-x 0.0)
	 (setq intercept? x1))
	((=e delta-y 0.0)
	 ;; shouldn't happen
	 )
	(t
	 (setq intercept?
	       (round (+e (/e (*e fside-y delta-x) delta-y)
			  fx1
			  (-e (/e (*e fy1 delta-x) delta-y)))))))
      (when (and intercept?
		 (>w intercept? (left-edge-of-block block))
		 (<w intercept? (right-edge-of-block block)))
	intercept?))))

(defun compute-side-of-exit-for-orthogonal-connection
       (block loose-end
	 x-position-of-last-bend y-position-of-last-bend
	 desired-position-on-side?)
  (cond
    ((>w x-position-of-last-bend
	 (right-edge-of-block block))
     (if desired-position-on-side?
	 (values 'right
		 (-w (right-edge-of-block block)
		     (left-edge-of-block loose-end))
		 (-w (+w (top-edge-of-block block)
			 desired-position-on-side?)
		     (top-edge-of-block loose-end))
		 desired-position-on-side?)
	 (values 'right
		 (-w (right-edge-of-block block)
		     (left-edge-of-block loose-end))
		 0
		 (-w y-position-of-last-bend
		     (top-edge-of-block block)))))
    ((<w x-position-of-last-bend
	 (left-edge-of-block block))
     (if desired-position-on-side?
	 (values 'left
		 (-w (left-edge-of-block block)
		     (left-edge-of-block loose-end))
		 (-w (+w (top-edge-of-block block)
			 desired-position-on-side?)
		     (top-edge-of-block loose-end))
		 desired-position-on-side?)
	 (values 'left
		 (-w (left-edge-of-block block)
		     (left-edge-of-block loose-end))
		 0
		 (-w y-position-of-last-bend
		     (top-edge-of-block block)))))
    ((>w y-position-of-last-bend
	 (bottom-edge-of-block block))
     (if desired-position-on-side?
	 (values 'bottom
		 (-w (+w (left-edge-of-block block)
			 desired-position-on-side?)
		     (left-edge-of-block loose-end))
		 (-w (bottom-edge-of-block block)
		     (top-edge-of-block loose-end))
		 desired-position-on-side?)
	 (values 'bottom
		 0
		 (-w (bottom-edge-of-block block)
		     (top-edge-of-block loose-end))
		 (-w x-position-of-last-bend
		     (left-edge-of-block block)))))
    ((<w y-position-of-last-bend
	 (top-edge-of-block block))
     (if desired-position-on-side?
	 (values 'top
		 (-w (+w (left-edge-of-block block)
			 desired-position-on-side?)
		     (left-edge-of-block loose-end))
		 (-w (top-edge-of-block block)
		     (top-edge-of-block loose-end))
		 desired-position-on-side?)
	 (values 'top
		 0
		 (-w (top-edge-of-block block)
		     (top-edge-of-block loose-end))
		 (-w x-position-of-last-bend
		     (left-edge-of-block block)))))))


;;; Connection-completely-inside-block-p assumes that loose-end is completely
;;; inside the block.

(defun connection-completely-inside-block-p (connection loose-end block)
  (and (null (delta-or-deltas connection))
       (multiple-value-bind
	 (anchor-x anchor-y)
	   (compute-dragged-connection-anchor-point
	     connection loose-end)
	 (and
	   (>=w anchor-y (top-edge-of-block block))
	   (<=w anchor-y (bottom-edge-of-block block))
	   (>=w anchor-x (left-edge-of-block block))
	   (<=w anchor-x (right-edge-of-block block))))))

;; This can happen if block A is inside block B and a connection from block A
;; extends outside both blocks.  It is then possible to drag the connection
;; and try to connect it inside A without going outside either block.


(defun compute-info-for-connection-inside-block 
       (loose-end block current-link-2-delta 
	loose-end-initial-orientation-horizontal-p)
  (let ((closest-side 'left)
	(distance-to-closest-side 
	  (-w (left-edge-of-block loose-end) (left-edge-of-block block))))
    (loop for side-to-try in '(top right bottom)
	  as distance-to-side
	     = (case side-to-try
		 (top (-w (top-edge-of-block loose-end) (top-edge-of-block block)))
		 (right (-w (right-edge-of-block block) (right-edge-of-block loose-end)))
		 (bottom (-w (bottom-edge-of-block block) (bottom-edge-of-block loose-end))))
	  do (when (<w distance-to-side distance-to-closest-side)
	       (setq distance-to-closest-side distance-to-side
		     closest-side side-to-try)))
    (case closest-side
      (left
       (values 'left (-w (top-edge-of-block loose-end)
			 (if (not loose-end-initial-orientation-horizontal-p)
			     current-link-2-delta 0)
			 (top-edge-of-block block)) 0 0))
      (top
       (values 'top (-w (left-edge-of-block loose-end)
			(if loose-end-initial-orientation-horizontal-p
			    current-link-2-delta 0)
			(left-edge-of-block block)) 0 0))
      (right
       (values 'right (-w (top-edge-of-block loose-end)
			  (if (not loose-end-initial-orientation-horizontal-p)
			      current-link-2-delta 0)
			  (top-edge-of-block block)) 0 0))
      (bottom
       (values 'bottom (-w (left-edge-of-block loose-end)
			   (if loose-end-initial-orientation-horizontal-p
			       current-link-2-delta 0)
			   (left-edge-of-block block)) 0 0)))))


(defun side-of-junction-has-connection-p (junction side)
  (loop for connection being the connections of junction
	doing
    (if (eq (input-end-object connection) junction)
	(if (eq (get-side-given-end-position
		  (input-end-position connection))
		side)
	    (return t))
	(if (eq (get-side-given-end-position
		  (output-end-position connection))
		side)
	    (return t)))))




;;; `Join-two-connections' takes loose-end-1 and loose-end-2 as arguments.
;;; Loose-end-1 is the one being dragged and loose-end-2 is the one near
;;; loose-end-1.  The two connections are combined into one if there are no
;;; directionality or cross-section compatibility problems.  The function
;;; returns T if the connection was successful.  Some heuristics will
;;; eventually have to be added to get rid of small wrinkles in connections.

(defun join-two-connections
    (loose-end-1 loose-end-2)
  (let* ((connection-1 
	   (get-connection-for-loose-end loose-end-1))
	 (connection-1-fixed-end-block
	   (get-block-at-other-end-of-connection
	     connection-1 loose-end-1))
	 (connection-2
	   (get-connection-for-loose-end loose-end-2))
	 (connection-2-fixed-end-block
	   (get-block-at-other-end-of-connection
	     connection-2 loose-end-2))
	 (directionality-or-cross-section-problem-p
	   (or
	     (cond
	       ((not (connection-cross-section-patterns-compatible?
		       connection-1 connection-2))
		(notify-user
		  "Can't join connections with incompatible cross sections")
		t))
	     (cond 
	       ((and (connection-not-directed? connection-1)	; both non-directed
		     (connection-not-directed? connection-2))
		nil)
	       ((or (connection-not-directed? connection-1)	; one directed, one not
		    (connection-not-directed? connection-2))
		(notify-user
		  "Can't join directed and non-directed connections!")
		t)
	       ((or (and (eq connection-1-fixed-end-block	; both directed
			     (input-end-object connection-1))
			 (eq connection-2-fixed-end-block
			     (input-end-object connection-2)))
		    (and (eq connection-1-fixed-end-block
			     (output-end-object connection-1))
			 (eq connection-2-fixed-end-block
			     (output-end-object connection-2))))
		(notify-user
		  "Can't join directed connections with opposing directions!")
		t)))))

    (unless directionality-or-cross-section-problem-p
      (note-change-to-connection connection-1)
      (note-deletion-of-connection connection-2)
      
      ;; erase the two connections and loose ends
      (update-images-of-block loose-end-1 t nil)
      (update-images-of-block loose-end-2 t nil)
      (if (eq (output-end-object connection-1) loose-end-1)
	  (update-connection-images 
	    t (superblock? loose-end-1) connection-1))
      (if (eq (output-end-object connection-2) loose-end-2)
	  (update-connection-images 
	    t (superblock? loose-end-2) connection-2))

      (adjust-deltas-of-connections-to-be-joined
	connection-1 loose-end-1 connection-2 loose-end-2)
      (when g2-has-v5-mode-windows-p
	;;(format t "JOIN-TWO-CONNECTIONS::MOVING A CONNECTION~%")
	(send-ws-representations-connection-moved connection-1))
      (replace-connection-in-block
	connection-2-fixed-end-block
	connection-2
	connection-1)
      (when g2-has-v5-mode-windows-p
	(send-ws-representations-item-layer-change
	  (get-or-make-connection-frame-and-activate-if-appropriate connection-1)
	  (superblock? (input-end-object-internal connection-1))
	  (find-connection-or-block-below-this-connection
	    connection-1
	    (input-end-object-internal connection-1))))

      ;; Remove loose ends from workspace.

      ;; Added a fix to reclaim the connections slot.  - cpm, mhd, 6/3/93
      (when (connections loose-end-1)
	(reclaim-connection-item-table (connections loose-end-1))
	(setf (connections loose-end-1) nil))
      (when (connections loose-end-2)
	(reclaim-connection-item-table (connections loose-end-2))
	(setf (connections loose-end-2) nil))

      (let* ((connection-2-frame-or-class
	       (connection-frame-or-class connection-2))
	     (fsn (if (not (symbolp connection-2-frame-or-class))
		      (copy-frame-serial-number
		        (frame-serial-number connection-2-frame-or-class)))))
	(if fsn
	    (delete-frame connection-2-frame-or-class))

	;; If there is a connection frame and it has not been deleted
	;; then it will be deleted later by the g2-delete method.
	;; In that case the loose-ends and the connection-structure
	;; will still need to exist for the connection to be deleted.
	(unless (and fsn
		     (not
		       (frame-has-been-reprocessed-p
			 connection-2-frame-or-class fsn)))
	  (reclaim-connection-and-delta-or-deltas connection-2 nil)
	  (delete-frame loose-end-2))
	(reclaim-frame-serial-number fsn))

      (delete-frame loose-end-1)
      
      ;; If the input-end object is being dragged, then this connection must be
      ;; added to the dragging state, and rendered in XOR.  -fmw, 10/14/94
      (when (block-is-currently-being-dragged-p connection-2-fixed-end-block)
	(recompute-external-connections-for-dragging-states connection-2-fixed-end-block))

      ;; redraw connection-1
      (update-connection-images 
	nil (superblock? 
	      connection-1-fixed-end-block) connection-1))

    (values (not directionality-or-cross-section-problem-p) connection-1)))

(defun reclaim-connection-and-delta-or-deltas (connection delete-dangling-connection-posts?)
  (update-runtime-structures-according-to-edit connection)
  #+development
  (when debug-connections?
    (check-for-bad-connections connection))
  (let ((delta-or-deltas
	  (delta-or-deltas connection)))
    (when (consp delta-or-deltas)
      (reclaim-slot-value-list delta-or-deltas)
      (setf (delta-or-deltas connection) nil)))
  (flush-subworkspace-connection-posts connection nil delete-dangling-connection-posts?)
  (reclaim-slot-value (connection-attributes-plist connection))
  (frame-serial-number-setf (frame-serial-number-for-connection connection)
			    (frame-serial-number-recycled))
  (reclaim-connection connection))

;; Reclaim using slot reclaimers in the structure definition!

;; Shares some code with reclaim-bad-connections-of-blocks -fmw, 1/3/02.

(defun connection-cross-section-patterns-compatible?
       (connection-1 connection-2)
  (let* ((connection-1-connection-frame-or-class
	   (connection-frame-or-class connection-1))
	 (connection-1-cross-section-pattern
	   (get-cross-section-pattern-given-connection-frame-or-class
	     connection-1-connection-frame-or-class))
	 (connection-2-connection-frame-or-class
	   (connection-frame-or-class connection-2))
	 (connection-2-cross-section-pattern
	   (get-cross-section-pattern-given-connection-frame-or-class
	     connection-2-connection-frame-or-class)))
    (equal (get-cross-section-stripes connection-1-cross-section-pattern)
	   (get-cross-section-stripes connection-2-cross-section-pattern))))

(defun small-link-delta-p (delta)
  (if called-within-clear-text-loading
      (<=f -2 delta 2)
      (=f delta 0)))

(defun adjust-deltas-of-connections-to-be-joined
       (connection-1 loose-end-1 connection-2 loose-end-2)
  (let ((connection-1-delta-or-deltas
	  (delta-or-deltas connection-1))
	(connection-2-delta-or-deltas
	  (delta-or-deltas connection-2))
	(connection-2-fixed-end-block
	  (get-block-at-other-end-of-connection
	    connection-2 loose-end-2))
	(loose-end-orientations-same-p
	  (loose-end-orientations-same-p
	    connection-1 loose-end-1 connection-2 loose-end-2))
	(connection-being-dragged-diagonal-p
	  (connection-diagonal-p connection-1))
	(absorb-link-when-joining? nil)
	(reverse-connection-delta-pairs-for-output-connection? nil))
    
    (setq connection-2-delta-or-deltas
	  (add-missing-deltas-to-connection connection-2))

    (funcall-method
      'shift loose-end-1
      (-w (left-edge-of-block loose-end-2)
	  (left-edge-of-block loose-end-1))
      (-w (top-edge-of-block loose-end-2)
	  (top-edge-of-block loose-end-1)))
    
    (multiple-value-bind
      (link-1-delta link-2-delta)
	(compute-stretched-links-of-connection-being-dragged
	  connection-1 loose-end-1)
      (cond
	((eq (output-end-object connection-1) loose-end-1)
	 (let (new-last-deltas)
	   (cond
	     ((small-link-delta-p link-2-delta)
	      (setf (output-end-position connection-1)
		    (combine-side-and-position-on-side-for-end-position
		      (case (get-side-given-end-position
			      (output-end-position connection-1))
			((left right) 'top)
			(t  ; if top or bottom
			 'left))
		      0))
	      (setq loose-end-orientations-same-p
		    (loose-end-orientations-same-p
		      connection-1 loose-end-1 connection-2 loose-end-2))
	      (setq new-last-deltas
		    (slot-value-list link-1-delta)))
	     (t 
	      (setq new-last-deltas
		    (slot-value-list link-1-delta link-2-delta))))
	   (cond 
	     ((null connection-1-delta-or-deltas)
	      (setq connection-1-delta-or-deltas new-last-deltas))
	     ((atom connection-1-delta-or-deltas)
	      (setq connection-1-delta-or-deltas
		    (slot-value-cons connection-1-delta-or-deltas new-last-deltas)))
	     (t (setq connection-1-delta-or-deltas
		      (nconc connection-1-delta-or-deltas new-last-deltas))))

	   ;; Combine two connections into one.
	   ;; Connection-1 is the joining connection;
	   ;; connection-2 will be deleted.

	   (setq absorb-link-when-joining?
		 (absorb-link-when-joining?
		   loose-end-orientations-same-p
		   connection-being-dragged-diagonal-p
		   (oddp (length connection-1-delta-or-deltas))
		   (=f (length connection-2-delta-or-deltas) 1)))

	   (setq reverse-connection-delta-pairs-for-output-connection?
		 (reverse-connection-delta-pairs-for-output-connection?
		   connection-being-dragged-diagonal-p
		   loose-end-orientations-same-p absorb-link-when-joining?))	   

	   (loop for rest-of-connection-1-deltas
		     on connection-1-delta-or-deltas
		 until (null (cdr rest-of-connection-1-deltas))
		 finally
		   (let ((deltas-to-be-added-to-connection-1
			   (if (eq (input-end-object connection-2) loose-end-2)
			       (if reverse-connection-delta-pairs-for-output-connection?
				   (reverse-connection-delta-pairs
				     connection-2-delta-or-deltas)
				   (copy-list-using-slot-value-conses
				     connection-2-delta-or-deltas))
			       (invert-connection-deltas 
				 connection-2-delta-or-deltas 
				 reverse-connection-delta-pairs-for-output-connection?))))
		     (if absorb-link-when-joining?
			 (progn
			   (setf (car rest-of-connection-1-deltas)
				 (+w (car rest-of-connection-1-deltas)
				     (car deltas-to-be-added-to-connection-1))
				 (cdr rest-of-connection-1-deltas)
				 (cdr deltas-to-be-added-to-connection-1))
			   ;; Added a reclaimer for the first cons of this list.
			   ;;  - cpm, mhd, 6/3/93
			   (reclaim-slot-value-cons deltas-to-be-added-to-connection-1))
			 (setf (cdr rest-of-connection-1-deltas)
			       deltas-to-be-added-to-connection-1))))
	   (setf (delta-or-deltas connection-1)
		 connection-1-delta-or-deltas)
	   
	   ;; set up links between connection-1 and end object of 
	   ;; connection-2
	   (set-output-end-of-connection-1 
	     connection-1 connection-2-fixed-end-block
	     (get-position-at-this-end-of-connection
	       connection-2 connection-2-fixed-end-block))))
	(t
	 ;; adjust deltas of connection-1 (connection being dragged)
	 ;; so that it meets connection-2
	 ;; Replace first deltas
	 
	 (setq connection-1-delta-or-deltas
	       (add-missing-deltas-to-connection connection-1))
	 (setq link-1-delta (-w link-1-delta)
	       link-2-delta (-w link-2-delta))
	 (cond
	   ((small-link-delta-p link-2-delta)
	    (setf (input-end-position connection-1)
		  (combine-side-and-position-on-side-for-end-position
		    (case (get-side-given-end-position
			    (input-end-position connection-1))
		      ((left right) 'top)
		      (t  ; if top or bottom
		       'left))
		    0))
	    (setq loose-end-orientations-same-p
		  (loose-end-orientations-same-p
		    connection-1 loose-end-1 connection-2 loose-end-2))
	    (setq connection-1-delta-or-deltas
		  (slot-value-cons link-1-delta
			(if (cdr connection-1-delta-or-deltas)
			    (cddr connection-1-delta-or-deltas)))))
	   (t
	    (setq connection-1-delta-or-deltas
		  (slot-value-cons link-2-delta
			(slot-value-cons link-1-delta
			      (if (cdr connection-1-delta-or-deltas)
				  (cddr connection-1-delta-or-deltas)))))))
	 
	 ;; Combine two connections into one.
	 ;; Connection-1 is the joining connection;
	 ;; connection-2 will be deleted (and eventually recycled).

	 (setq absorb-link-when-joining?
	       (absorb-link-when-joining?
		 loose-end-orientations-same-p
		 connection-being-dragged-diagonal-p
		 (oddp (length connection-2-delta-or-deltas))
		 nil))  ; output connection is being dragged so it is not a stub

	 (when (reverse-connection-delta-pairs-for-output-connection?
		 connection-being-dragged-diagonal-p
		 loose-end-orientations-same-p absorb-link-when-joining?)
	   (let ((temp1 
		   (reverse-connection-delta-pairs
		     connection-1-delta-or-deltas)))
	     (reclaim-slot-value-list connection-1-delta-or-deltas)
	     (setq connection-1-delta-or-deltas temp1)))
	 
	 (let ((deltas-to-be-added-to-connection-1
		 (if (eq (input-end-object connection-2) loose-end-2)
		     (invert-connection-deltas 
		       connection-2-delta-or-deltas 
		       nil)
		     (copy-list-using-slot-value-conses
		       connection-2-delta-or-deltas))))

	   (loop for rest-of-deltas
		     on deltas-to-be-added-to-connection-1
		 until (null (cdr rest-of-deltas))
		 finally
		   (if absorb-link-when-joining?
		       (progn
			 (setf (car rest-of-deltas)
			       (+w (car rest-of-deltas)
				   (car connection-1-delta-or-deltas))
			       (cdr rest-of-deltas)
			       (cdr connection-1-delta-or-deltas))
			 ;; Added a reclaimer for the first cons of this list.
			 ;;  - cpm, mhd, 6/3/93
			 (reclaim-slot-value-cons connection-1-delta-or-deltas))
		       (setf (cdr rest-of-deltas)
			     connection-1-delta-or-deltas)))

	   (setf (delta-or-deltas connection-1)
		 deltas-to-be-added-to-connection-1))
	 
	 ;; set up links between connection-1 and end object of 
	 ;; connection-2

	 (set-input-end-of-connection-1 
	   connection-1 connection-2-fixed-end-block
	   (get-position-at-this-end-of-connection
	     connection-2 connection-2-fixed-end-block))))))

  (remove-redundant-deltas-from-connection connection-1))

;; Consider using change... functions (see above) to simplify
;; Actually, this wouldn't simplify things much since surgery of 
;; delta-or-deltas (to add deltas when orientations are the same)
;; has to be done anyway.

(defun loose-end-orientations-same-p
       (connection-1 loose-end-1 connection-2 loose-end-2)
  (let* ((loose-end-1-end-position
	   (get-position-at-this-end-of-connection
	     connection-1 loose-end-1))
	 (loose-end-1-end-side
	   (get-side-given-end-position
	     loose-end-1-end-position))
	 (loose-end-1-initial-orientation-horizontal-p
	   (memq loose-end-1-end-side '(left right)))
	 (loose-end-2-end-position
	   (get-position-at-this-end-of-connection
	     connection-2 loose-end-2))
	 (loose-end-2-end-side
	   (get-side-given-end-position
	     loose-end-2-end-position))
	 (loose-end-2-initial-orientation-horizontal-p
	   (memq loose-end-2-end-side '(left right))))
    (or (and loose-end-1-initial-orientation-horizontal-p
	     loose-end-2-initial-orientation-horizontal-p)
	(and (not loose-end-1-initial-orientation-horizontal-p)
	     (not loose-end-2-initial-orientation-horizontal-p)))))

(defun absorb-link-when-joining? 
       (loose-end-orientations-same-p connection-being-dragged-diagonal-p
	input-connection-has-odd-number-of-deltas-p
	output-connection-is-stub-p)
  (if connection-being-dragged-diagonal-p
      (or input-connection-has-odd-number-of-deltas-p
	  output-connection-is-stub-p)
      loose-end-orientations-same-p))

(defun reverse-connection-delta-pairs-for-output-connection?
       (connection-being-dragged-diagonal-p
	loose-end-orientations-same-p absorb-link-when-joining?)
  (when connection-being-dragged-diagonal-p
    (if absorb-link-when-joining?
	(not loose-end-orientations-same-p)
	loose-end-orientations-same-p)))

;;; `Invert-connection-deltas' returns a list of deltas which is the "inverse" of
;;; the argument in that it is the deltas which would result from traversing the
;;; connection in the opposite direction from the one for which the argument is
;;; valid.  This is useful for changing the direction of connections.

(defun invert-connection-deltas (deltas reverse-delta-pairs?)
  (cond
    (reverse-delta-pairs?
     (let* ((temp1 (reverse-connection-delta-pairs deltas))
	    (inverted-deltas
	      (invert-connection-deltas-1 temp1)))
       (reclaim-slot-value-list temp1)
       inverted-deltas))
    (t
     (invert-connection-deltas-1 deltas))))

(defun invert-connection-deltas-1 (deltas)
  (loop with processed-deltas = nil
	for delta in deltas
	do (setq processed-deltas		       ; reverse and take negative
		 (slot-value-cons (-w delta) processed-deltas))
	finally (return processed-deltas)))

(defun reverse-connection-delta-pairs (deltas)
  (loop with processed-deltas = nil
	with processed-deltas-tail = nil
	with list-to-add = nil
	with tail-of-list = nil
	as rest-of-deltas = deltas then (cddr rest-of-deltas)
	as first-delta = (first rest-of-deltas)
	as second-delta = (second rest-of-deltas)
	while rest-of-deltas
	do
    (if second-delta
	(setq list-to-add
	      (slot-value-list second-delta first-delta)
	      tail-of-list
	      (cdr list-to-add))
	(setq list-to-add
	      (slot-value-list first-delta)
	      tail-of-list
	      list-to-add))
    (if (not processed-deltas)
	(setq processed-deltas list-to-add)
	(setf (cdr processed-deltas-tail) list-to-add))
    (setq processed-deltas-tail tail-of-list)
	finally (return processed-deltas)))

;;;; System Procedures for Monitoring Connection Creation

;;; This facility is being introduced to support GDA having
;;; access to user connection editing without having to add
;;; a new "whenever" facility to G2 before the release of 4.0.
;;; This facility is upwardly compatible with the connection
;;; event updating that will be in G2v4.1.

(def-kb-specific-variable connection-handling-procedure?
    connect3 nil nil nil)
(def-kb-specific-variable connection-handling-procedure-fsn?
    connect3 nil nil reclaim-frame-serial-number)
(def-kb-specific-variable connection-handling-connection-queue
    connect3 nil nil reclaim-slot-value-list-function)

(defun reclaim-slot-value-fsn-queue (queue)
  (loop for fsn in queue do
    (reclaim-frame-serial-number fsn))
  (reclaim-slot-value-list queue))

(def-kb-specific-variable connection-handling-fsn-queue
    connect3 nil nil reclaim-slot-value-fsn-queue)
(def-kb-specific-variable connection-handling-window-queue
    connect3 nil nil reclaim-slot-value-list-function)
(def-kb-specific-variable connection-handling-connection-type-queue
    connect3 nil nil reclaim-slot-value-list-function)
(def-kb-specific-variable connection-handling-block-queue
    connect3 nil nil reclaim-slot-value-list-function)

;; kb-props for proc-frame & proc-fsn

(defun-for-system-procedure g2-register-connection-handling-procedure
    (procedure)
  (cond
    ((of-class-p procedure 'procedure)
     (setq connection-handling-procedure? procedure)
     (frame-serial-number-setf connection-handling-procedure-fsn?
			       (frame-serial-number procedure))
     (make-evaluation-truth-value-function truth))
    (t
     (setq connection-handling-procedure? nil)
     (make-evaluation-truth-value-function falsity))))

(defun-for-system-procedure g2-get-connection-to-handle ()
  (values (let ((frame (slot-value-pop connection-handling-connection-queue))
		(fsn (slot-value-pop connection-handling-fsn-queue)))
	    (if (and frame
		     (not (frame-has-been-reprocessed-p frame fsn))
		     (serve-item-p frame))
		(progn
		  (reclaim-frame-serial-number fsn)
		  frame)
		(progn
		  (reclaim-frame-serial-number fsn)
		  (make-evaluation-truth-value-function falsity))))
	  (slot-value-pop connection-handling-window-queue)
	  (slot-value-pop connection-handling-connection-type-queue)
	  (or (slot-value-pop connection-handling-block-queue)
	      (make-evaluation-truth-value-function falsity))))

(defun-for-system-procedure g2-more-connections-to-be-handled ()
  (if connection-handling-connection-queue
      (make-evaluation-truth-value-function truth)
      (make-evaluation-truth-value-function falsity)))

(defun invoke-connection-handler-if-any
    (connection-or-block? window connection-type
			  block-receiving-connection-if-any?)
  (when (and connection-handling-procedure?
	     (not (frame-has-been-reprocessed-p
		    connection-handling-procedure?
		    connection-handling-procedure-fsn?)))
    (let ((frame-to-queue?
	    (if connection-or-block?
		(if (connection-p connection-or-block?)
		    (get-or-make-connection-frame-and-activate-if-appropriate
		      connection-or-block?)
		    connection-or-block?))))
      (when frame-to-queue?
	(setq connection-handling-connection-queue
	      (nconc
		connection-handling-connection-queue
		(slot-value-list
		  frame-to-queue?)))
	(setq connection-handling-fsn-queue
	      (nconc
		connection-handling-fsn-queue
		(slot-value-list
		  (copy-frame-serial-number (frame-serial-number frame-to-queue?)))))
	(setq connection-handling-window-queue
	      (nconc
		connection-handling-window-queue
		(slot-value-list window)))
	(setq connection-handling-connection-type-queue
	      (nconc
		connection-handling-connection-type-queue
		(slot-value-list connection-type)))
	(setq connection-handling-block-queue
	      (nconc
		connection-handling-block-queue
		(slot-value-list block-receiving-connection-if-any?)))))
    (start-procedure-invocation-in-place
      connection-handling-procedure? nil nil
      nil 0 0
      nil nil nil nil nil)))

(defun-for-system-procedure g2-set-connection-port-name
    (block connection-frame name)
  #-connections-v2
  (loop with connection
	     = (connection-for-this-connection-frame
		 connection-frame)
	with tail = (connections block)
	with prev-cons = nil
	while tail do
    (cond
      ((if (symbolp (car tail))
	   (eq (cadr tail) connection)
	   (eq (car tail) connection))
       (note-change-to-block block 'connections)
       (decache-roles-for-entities-related-to-this-connection
	 connection)
       (cond
	 ((symbolp (car tail))
	  (setf (car tail) name))
	 (t
	  (slot-value-push name tail)))
       (cond (prev-cons
	      (setf (cdr prev-cons) tail))
	     (t
	      (setf (connections block) tail)))
       (update-runtime-structures-according-to-edit block)
       (update-runtime-structures-according-to-edit connection)
       (return))
      ((symbolp tail)
       (setq prev-cons (cdr tail))
       (setq tail (cddr tail)))
      (t
       (setq prev-cons tail)
       (setq tail (cdr tail)))))
  #+connections-v2
  (let* ((connection
	  (connection-for-this-connection-frame connection-frame))
	 (connections (connections block)))
    (when-let (connection-item (get-connection-item connection connections))
      (cond ((connection-item-input-names connection-item)
	     (reclaim-slot-value-list (connection-item-input-names connection-item))
	     (setf (connection-item-input-names connection-item)
		   (slot-value-list name)))
	    (t
	     (when (connection-item-output-names connection-item)
	       (reclaim-slot-value-list (connection-item-output-names connection-item)))
	     (setf (connection-item-output-names connection-item)
		   (slot-value-list name)))))))

(defun-for-system-procedure g2-get-connection-input-and-output
    (connection-frame)
  (let* ((connection
	   (connection-for-this-connection-frame
	    connection-frame))
	 (in (input-end-object connection))
	 (out (output-end-object connection)))
    (values
      (if (or (null in)
	      (loose-end-p in))
	  (make-evaluation-truth-value-function falsity)
	  in)
      (if (or (null out)
	      (loose-end-p out))
	  (make-evaluation-truth-value-function falsity)
	  out))))

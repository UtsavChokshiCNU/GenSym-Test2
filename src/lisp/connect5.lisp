;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module CONNECT5

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Andreas Hofmann



;;;; Overview

;;; This module contains code for diagonal connections and dynamic connection
;;; creation.

;;; Also, this module contains a system procedure to reference the items
;;; connected at a given port.

;;; Test kbs are - ma:>agh>diag1, 2, 3, 4, 5, ...
;;; Diag4.kb contains a fairly exhaustive list of tests on the
;;; basic-connection-creation-tests workspace.

;;; See also ma:>agh>build-plant.kb for an interesting example.



;; To Do

;; Since connection structures themselves now have frame flags, transient-p for
;; connections could use these flags, rather than the flags on the connection
;; frame.

;; Review clipping on Sun.  Looked tight last time for cases when line is vertical
;; or horizontal.

;; Odd number-of-zeros-swallowed case for compute-next-delta.



;; Make some test kbs that show usefulness of transient connections for building
;; assemblies according to specs.  Have a distillation column assembly spec and a
;; procedure build-distillation-column-assembly.  Have a similar procedure for
;; build plant.

;; Review with Mark call to find-object-near-mouse for connection dragging case.
;; Passing in several classes as classes-of-objects-to-not-consider?  This should
;; probably be restricted to objects only.  Currently, transient connections can
;; only be made to objects.

;; Consider putting commas between deltas in grammar for vertices.  

;; Make some flashy test kbs.  Maybe some map outlines.  Railroad layouts.
;; Use map of T.  Search tree for a maze?

;; Remove global-draw-diagonally?.

;; Clipping for non-X platforms (lisp machine, Sunviews).

;; Review
;; print-create-connection-statement
;; print-create-connection-instruction
;; Check if common code in procedure and inference engine versions of 
;; create-connection.  
;; Check where procedure-evaluate-connection-style-detail is called from.

;; Consider creating junctions automatically for diagonal connections.  Need to
;; fix make-connection in insert-junction-block in this case.  The new connection
;; must be given the correct style.  
;; Find-vector-length-from-point-to-diagonal-connection-link-1 must return
;; intercept correctly.

;; When making transient connections with vertices, don't draw until all vertices
;; have been added.

;; Give warnings in make-transient-connection functions.  Don't cause
;; procedure error though.

;; Make-transient-stub-to-replace-existing-one is not exactly correct since it
;; returns only the first connection that satisfies the constraints.

;; Test all error conditions.

;; See !

;; Review whether replace-connection-in-block could be accomplished just by
;; delete-connection-in-block and add-connection-in-block.

;; Change &optional args in make-stubs, make-entity, make-stub, add-stub...
;; to required.

;; set-or-clear-connection-transient-if-necessary (see note)

;; Brian suggests a role server which serves vertices of a connection.  This
;; would be useful for computing trajectories of objects as they move along
;; the connections.

;; Review create and delete actions with Jim.

;; Review add-connection-in-block case in slot reclaimer for connections.
;; This must be dead code.  Also in delete-connection-to-stub.

;; Check with Peng - what is clip-for-drawing in xwindows.c for?
;; It seems that he should clear the clip rectangles before leaving
;; the X window function. 

;; Find-vector-length-from-point-to-connection-if-within-limit
;; Use with-connection?
;; Use delta-server mechanism used in draw function.
;; Have find take into account connection width.
;; Review find-vector-length-from-point-to-connection-link.  Check if
;; can abstract some of this better.



;; Grammar to do

;; Consider taking 'end-specifier operator out and making a non-default
;; template.

;; Review compilation of this create action.  Consistency checkers definitely need
;; work.

;; Create action - process connection details specifiers.  Direction must be with 
;; respect to first end object (check).

;; Make sure that connection-class is in directory of names.



;; Testing

;; Testing of connection creation and deletion.  
;; Load "ma:>agh>diag4.kb".
;; 1.  start, make connections, reset  (all connections go away)
;; 2.  start, make connections, delete connections  (get stubs which go away on reset)
;; 3.  change delete connections to delete "removing connection stubs"
;;     repeat 2  (no more stubs)
;; 4.  start, make black hole, delete manually (get stub which goes away on reset)
;; 5.  start, make black hole, delete black hole 
;; 6.  repeat 5 using "removing connection stubs" phrase

;; Player files are
;; connections-player-1.lisp, connections-player-1.kb.

;; Developing player scripts is currently tedious, especially for schematic
;; editing.  Ben may implement something like a multiple-value-bind or a setq, as
;; well as arithmetic operators.  It would then be good to define primitives for
;; picking up and connecting connections.

;; Use Ben's player stuff to make test kb for diagonal connections.
;; (guardian-test).  Important to test drawing diagonal connections as straight
;; ones.  Also, test input connections, as well as output connections, and test
;; dragging objects connected to each other by diagonal connections.  Also, test
;; cases of orthogonal connection with odd number of deltas being converted to
;; diagonal, causing add and delete bend functions to initially add or delete one
;; delta rather than two.  Test connection finding for connections with very
;; steep or very non-steep angles.  Test changing scale.  Test for leaks in
;; transient connections, including number cons leaks.

;; In diag4.kb basic tests, make corresponding set of buttons for procedures case
;; as well as inference engine case.

;; Test with Dave's test kb.

;; Joining connections is a good thing to test.  Style becomes style of connection
;; being dragged.  Use Ben's player for this.  Cloning is also a good thing to test
;; this way.




;;;; Diagonal Connections

;;; Diagonal connections have a number of important differences from orthogonal
;;; ones in both representation and behavior.

;;; Diagonal and orthogonal connections both use the delta-or-deltas?  slot of a
;;; connection to determine the vertices.  However, unlike orthogonal connections,
;;; diagonal ones normally require two numbers (two links) per vertex.  Therefore,
;;; for diagonal connections, delta-or-deltas?  should always be even (or nil).
;;; Thus, add-bend-to-connection and delete-last-bend-from-connection actually add
;;; or delete two links for the diagonal case.

;;; Difficulties can occur when converting from orthogonal to diagonal.  The
;;; orthogonal connection may have an odd number of links.  When converted to a
;;; diagonal connection, the missing number is assumed to be 0.  In this case,
;;; add-bend-to-connection and delete-last-bend-from-connection will add or delete
;;; one link rather than two in order to give the diagonal connection an even
;;; number of deltas.  This approach is better than padding the diagonal
;;; connection with an extra link when it is converted from an orthogonal one
;;; since it allows changing the connection back to orthogonal without any change
;;; in the original appearance.

;;; The issue of reversibility is an important one.  It is desireable to allow
;;; switching the style of a connection between orthogonal and diagonal without
;;; any change of appearance (in the absence of other edits).  When a diagonal
;;; connection is entered with right angle bends, its delta-or-deltas?  slot can
;;; contain 0's.  If such a connection is then converted to orthogonal, it is
;;; tempting to eliminate the 0's.  Doing so, however, would make it impossible to
;;; switch the connection back to diagonal and have it maintain its original
;;; appearance.

;; Note that the presence of 0's, especially two in a row, can cause some odd
;; behavior when dragging.  Consider eliminating the 0's if the user adds or
;; deletes bends for the orthogonal connection.

;;; The clicking sequences for orthogonal and diagonal connections are slightly
;;; different.  As with orthogonal connections, diagonal connections are picked up
;;; by clicking near the loose end.  Only the previous link stretches (rather than
;;; the previous two for the case of orthogonal connections).  However, the link
;;; can rotate diagonally, as well as stretch, so that as with orthogonal
;;; connections, two deltas are actually changing.  As with orthogonal
;;; connections, a bend is added by clicking (not close to the previous bend).  As
;;; mentioned, adding a bend for diagonal connections adds two deltas.  As with
;;; orthogonal connections, a diagonal connection is placed by clicking near the
;;; previous bend.  Unlike orthogonal connections, bends can not be removed by
;;; clicking near the bend before the last.  However, bends can always be removed,
;;; one by one, by picking up the loose end, and then placing it by clicking near
;;; the previous bend.

;; The code which implements diagonal connections is distributed amongst 
;; connect1, 2, and 3, as well as other modules.



;;;; Dynamic Connection Creation



(declare-forward-reference get-connection-given-stub-designation function)

(declare-forward-reference decache-roles-for-entities-related-to-this-connection
			   function)

(declare-forward-reference shift-blocks-with-their-external-connections function)

(declare-forward-reference send-ws-representations-connection-moved function) ;events-g2

(declare-forward-reference permit-transfer-of-permanent-items-p variable)

(defvar transient-connection-error?)



;;; The function `make-transient-connection' creates a new, transient
;;; connection.  This is what the GPL "make a connection" statement ends up
;;; calling.  We have to be careful about making new connections into a block
;;; being dragged.

(defun make-transient-connection 
    (class 
      input-end-object? make-new-input-stub?
      input-end-side? input-end-position-on-side? input-end-portname?
      output-end-object? make-new-output-stub?
      output-end-side? output-end-position-on-side? output-end-portname?
      connection-directional? connection-style? connection-vertices?
      report-errors?)

  (when
      (cond
	((and input-end-object? output-end-object?)
	 (let ((input-workspace? (superblock? input-end-object?))
	       (output-workspace? (superblock? output-end-object?)))
	   (cond
	     ((and (of-class-p input-workspace? 'workspace)
		   (of-class-p output-workspace? 'workspace)
		   (eq input-workspace? output-workspace?))
	      t)
	     (t
	      (when report-errors?
		(setq transient-connection-error? 
		      (gensym-list 
			'not-same-workspace 
			input-end-object? output-end-object?)))
	      nil))))
	(input-end-object?
	 (cond
	   ((of-class-p (superblock? input-end-object?) 'workspace)
	    t)
	   (t
	    (when report-errors?
	      (setq transient-connection-error? 
		    (gensym-list 'not-on-workspace input-end-object?)))
	    nil)))
	
	(output-end-object?
	 (cond
	   ((of-class-p (superblock? output-end-object?) 'workspace)
	    t)
	   (t
	    (when report-errors?
	      (setq transient-connection-error? 
		    (gensym-list 'not-on-workspace output-end-object?)))
	    nil))))

    ;; Batch the multitude of update which happen in here.
    ;; Also, this works around bug HQ-352772 "dynamically drawn connections need ctrl-c".
    
    (with-drawing-options (:deferred t :inval-preferred t)

      (let* ((stub-length-to-use? 
	       (if connection-vertices? 0 nil))
	     (input-end-object-connection?
	       (when input-end-object?
		 (let ((replaced-stub?
			 (when (or (eq make-new-input-stub? 'nil)
				   (eq make-new-input-stub? 'if-does-not-exist))
			   (make-transient-stub-to-replace-existing-one
			     class input-end-object?
			     (when connection-directional? 'output)
			     input-end-portname? input-end-side? 
			     input-end-position-on-side?
			     connection-style?
			     (and report-errors?
				  (eq make-new-input-stub? 'nil))))))
		 (cond
		   (replaced-stub?
		    replaced-stub?)
		   (make-new-input-stub?
		    (make-new-transient-stub
		      class input-end-object?
		      (when connection-directional? 'output)
		      input-end-portname? input-end-side? 
		      input-end-position-on-side?
		      connection-style?))))))
	     (output-end-object-connection?
	       (when output-end-object?
		 (let ((replaced-stub?
			 (when (or (eq make-new-output-stub? 'nil)
				   (eq make-new-output-stub? 'if-does-not-exist))
			   (make-transient-stub-to-replace-existing-one
			     class output-end-object?
			     (when connection-directional? 'input)
			     output-end-portname? output-end-side? 
			     output-end-position-on-side?
			     connection-style?
			     (and report-errors?
				  (eq make-new-output-stub? 'nil))))))
		 (cond
		   (replaced-stub?
		    replaced-stub?)
		   (make-new-output-stub?
		    (make-new-transient-stub
		      class output-end-object?
		      (when connection-directional? 'input)
		      output-end-portname? output-end-side? 
		      output-end-position-on-side?
		      connection-style?))))))
	     (final-connection? nil))
	
	;; At this point, input-end-object-connection? and/or 
	;; output-end-object-connection? are stubs (straight).
	
	(cond 
	  ((and input-end-object? output-end-object?)
	   (when (and input-end-object-connection? output-end-object-connection?)
	     (let* ((input-end-loose-end
		      (get-block-at-other-end-of-connection 
			input-end-object-connection? input-end-object?))
		    (output-end-loose-end
		      (get-block-at-other-end-of-connection 
			output-end-object-connection? output-end-object?))
		    (workspace (superblock? input-end-loose-end)))
	       (when (and connection-vertices?
			  called-within-clear-text-loading
			  (or (of-class-p input-end-object? 'loose-end)
			      (of-class-p output-end-object? 'loose-end)))
		 (setq connection-vertices? (nreverse connection-vertices?))
		 (eval-pop connection-vertices?)
		 (setq connection-vertices? (nreverse connection-vertices?)))
	       (when connection-vertices?
		 (install-vertices-in-connection
		   input-end-object-connection? input-end-loose-end
		   connection-vertices? 
		   (get-side-given-end-position 
		     (input-end-position input-end-object-connection?))
		   workspace))
	       (when (connection-is-straight? input-end-object-connection?)
		 (update-connection-images t workspace input-end-object-connection?)
		 (toggle-side-for-loose-end
		   input-end-loose-end
		   input-end-object-connection?)
		 (update-connection-images nil workspace input-end-object-connection?))
	       
	       (when connection-vertices?
		 (update-connection-images t workspace input-end-object-connection?)
		 (add-bend-to-connection-1 
		   input-end-object-connection? input-end-loose-end)
		 (add-bend-to-connection-1 
		   input-end-object-connection? input-end-loose-end)
		 (update-connection-images nil workspace input-end-object-connection?))
	       
	       (join-two-connections
		 input-end-loose-end		       ; this connection will prevail
		 output-end-loose-end))

	     (setq final-connection? input-end-object-connection?)
	     
	     ;; At this point, final-connection? has either two or three links
	     ;; and is connected to the objects.
	     
	     ))

	  (input-end-object?
	   (when input-end-object-connection?
	     (setq final-connection? input-end-object-connection?)
	     
	     ;; At this point, final-connection? is a stub connected to 
	     ;; input-end-object?
	     
	     (when connection-vertices?
	       (let ((loose-end
		       (get-block-at-other-end-of-connection 
			 input-end-object-connection? input-end-object?)))
		 (install-vertices-in-connection
		   final-connection? loose-end
		   connection-vertices? 
		   (get-side-given-end-position 
		     (input-end-position input-end-object-connection?))
		   (superblock? loose-end))))))

	  (output-end-object?
	   (when output-end-object-connection?
	     (setq final-connection? output-end-object-connection?)
	     
	     ;; At this point, final-connection? is a stub connected to 
	     ;; output-end-object?
	     
	     (when connection-vertices?
	       (let* ((loose-end
			(get-block-at-other-end-of-connection 
			  output-end-object-connection? output-end-object?)))
		 (install-vertices-in-connection
		   final-connection? loose-end
		   connection-vertices? 
		   (get-side-given-end-position 
		     (output-end-position output-end-object-connection?))
		   (superblock? loose-end)))))))
	(when final-connection?
	  ;; If final-connection? is nil at this point, connection creation has
	  ;; failed for some reason.  added calls to
	  ;; add-subworkspace-connection-post-if-appropriate -rdf, 10/19/94
	  
	  ;; When final-connection? is nil the list of deltas
	  ;; is reclaimed by the caller,
	  ;; execute-create-connection-stack-instruction-internal.
	  ;; - jpg 1/21/02
	  (reclaim-eval-list connection-vertices?)
	  (when output-end-object?
	    (add-subworkspace-connection-post-if-appropriate
	      final-connection? output-end-object?))
	  (when input-end-object?
	    (add-subworkspace-connection-post-if-appropriate
	      final-connection? input-end-object?))
	  (connection-frame-or-class final-connection?))))))



;;; The function `install-vertices-in-connection' is used only by
;;; make-transient-connection.  Apparently, it tries to animate the changes by
;;; erasing and redrawing for each vertex added.

(defun install-vertices-in-connection 
    (connection loose-end connection-vertices starting-side
		workspace)
  (update-connection-images t workspace connection)
  (toggle-side-for-loose-end loose-end connection)
  (update-connection-images nil workspace connection)
  (loop with delta-x 
	with delta-y
	with objects-to-drag = (gensym-list loose-end)
	with connections-to-drag = (gensym-list connection)
	for delta in connection-vertices
	as orientation-horizontal-p 
	   = (memq starting-side '(left right))
	   then (not orientation-horizontal-p)
	as first-time? = t then nil
	do (if orientation-horizontal-p
	       (setq delta-x delta
		     delta-y 0)
	       (setq delta-x 0
		     delta-y (-w delta)))
	   (shift-blocks-with-their-external-connections
	     objects-to-drag connections-to-drag nil workspace
	     delta-x delta-y)
	   (when (not first-time?)
	     (update-connection-images t workspace connection)
	     (add-bend-to-connection-1 connection loose-end)
	     (update-connection-images nil workspace connection))
	finally
	  (update-connection-images t workspace connection)
	  (delete-last-bend-from-connection-1 connection loose-end)
	  (update-connection-images nil workspace connection)
	  (when g2-has-v5-mode-windows-p
	    (send-ws-representations-connection-moved connection))
	  (reclaim-gensym-list objects-to-drag)
	  (reclaim-gensym-list connections-to-drag))
  (delta-or-deltas connection))


;; TODO: Handle the line-pattern.  Requires support in the stack evaluator.
;; (eg, execute-create-connection-stack-instruction).

(defun make-new-transient-stub 
    (class end-object direction? end-portname? end-side end-position-on-side
	   connection-style?)
  (let ((new-connection
	  (add-stub
	    end-object end-portname?
	    class direction? end-side end-position-on-side t connection-style?)))
    (decache-roles-for-entities-related-to-this-connection
      new-connection)
    (update-connection-images 
      nil (superblock? end-object) new-connection)
    new-connection))

(defun make-transient-stub-to-replace-existing-one
    (class end-object direction? end-portname? end-side? end-position-on-side?
	   connection-style? report-errors?)
  (let ((designated-connection? nil)
	(portname-of-designated-connection? nil)
	position-of-designated-connection
	side-of-designated-connection
	position-on-side-of-designated-connection)
    (cond
      ((cond
	 (end-side?				       ; side and position specified
	  (let ((stub-designation (gensym-list end-side? end-position-on-side?)))
	    (setq designated-connection?
		  (get-connection-given-stub-designation end-object stub-designation))
	    (reclaim-gensym-list stub-designation))
	  (when designated-connection?
	    (cond 
	      ((and end-portname?
		    (not (eq end-portname? 
			     (get-port-name-given-block-and-connection
			       end-object designated-connection?))))
	       nil)
	      (t
	       (setq portname-of-designated-connection? 
		     end-portname?
		     side-of-designated-connection
		     end-side?
		     position-on-side-of-designated-connection
		     end-position-on-side?)
	       t))))
	 (t					       ; only end-portname? specified
	  (setq designated-connection?
		(get-connection-given-stub-designation end-object end-portname?))
	  (when designated-connection?
	    (setq portname-of-designated-connection? 
		  end-portname?
		  position-of-designated-connection
		  (get-position-at-this-end-of-connection
		    designated-connection? end-object)
		  side-of-designated-connection
		  (get-side-given-end-position position-of-designated-connection)
		  position-on-side-of-designated-connection
		  (get-position-on-side-given-end-position
		    position-of-designated-connection))
	    t)))
       ;; if designated-connection? is non-nil

       (cond
	 ((and (permanent-connection-p designated-connection?)
	       (not permit-transfer-of-permanent-items-p))
	  (when report-errors?
	    (setq transient-connection-error? 
		  (gensym-list 'not-transient end-object)))
	  nil)
	 (t
	  ;; NOTE: Ideally, these would be passed in from the stack-evaluator,
	  ;; but that would require a new create-connection stack instruction
	  ;; which takes more arguments. Instead, inherit the line-pattern and
	  ;; arrows from the stub we are replacing. For HQ-5458449. -fmw, 4/3/07
	  (let ((line-pattern?
		  (copy-for-slot-value (connection-line-pattern designated-connection?)))
		(connection-arrows?
		  (copy-for-slot-value (connection-arrows-of-connection designated-connection?))))

	    ;; delete connection and then make new one
	    (delete-connection designated-connection? nil)
	    
	    (let ((new-connection
		    (add-stub
		      end-object portname-of-designated-connection?
		      class direction? side-of-designated-connection
		      position-on-side-of-designated-connection t connection-style?
		      line-pattern? connection-arrows?)))
	      (decache-roles-for-entities-related-to-this-connection
		new-connection)
	      (update-connection-images 
		nil (superblock? end-object) new-connection)
	      (reclaim-slot-value line-pattern?)
	      (reclaim-slot-value connection-arrows?)
	      new-connection)))))
      (t
       (when report-errors?
	 (setq transient-connection-error? 
	       (gensym-list 'bad-designation end-object)))
       nil
       ))))



;;; `Delete-item' calls delete-frame on its arg unless the arg is a subclass of
;;; connection, in which case it calls delete-connection on the corresponding
;;; connection structure.

(defun delete-item (item)
  (if (frame-of-class-p item 'connection)
      (delete-connection-leaving-stubs-if-appropriate
	(connection-for-this-connection-frame item))
      (delete-frame item)))

(defun delete-connection-leaving-stubs-if-appropriate (connection)	
  (if delete-connections-without-leaving-stubs?
      (delete-connection connection)
      (delete-connection-to-stub connection)))


;;; The substitution-macro `bad-connection-p' returns T iff the connection is
;;; missing its class or its endpoint backpointers.  All the broken connections
;;; in KBs we've seen so far satisfy this test.  Note however that NIL's in the
;;; end-position slots of a connection could also cause crashes later on.

(defun-substitution-macro bad-connection-p (connection-structure)
  (or (null (connection-frame-or-class connection-structure))
      (null (output-end-object-internal connection-structure))
      (null (input-end-object-internal connection-structure))))

;;; The substitution-macro `block-has-bad-connection-p' attempts to be a quick
;;; test whether a block has any connections needing fixing.

(defun-substitution-macro block-has-bad-connection-p (block)
  (and (connections block)
       (loop for conn being the connections of block
	     thereis (bad-connection-p conn))))


;;; The function `reclaim-bad-connections-of-blocks' is a very special purpose
;;; function for use only by `g2-clear-floating-connection-structures' and
;;; `delete-bad-connection-structures' post-loading function.  It has odd
;;; constraints since it is called while the KB is in an inconsistent state.

;;; It takes a list of possibly recycled blocks, all of which contain some "bad"
;;; connections, and none of whose connections are reprocessed.  It also takes a
;;; reference frame serial number snarfed when all the blocks were valid.  It
;;; carefully reclaims the bad connections attached to each block, and then
;;; deletes the block if it was a LOOSE-END.  We assume that for each bad
;;; connection, both its input-end and output-end block are somewhere in the
;;; list of blocks.

;;; Returns the number of connection structures reclaimed.

(defun reclaim-bad-connections-of-blocks (blocks reference-fsn)
  (let ((count 0)
	(loose-ends ()))

    ;; During this loop over blocks we will normally encounter each bad
    ;; connection twice: once for its input-end block and once for its
    ;; output-end.  Since we reclaim the bad connection the first time we see
    ;; it, the next time we see it it will be an "available connection".  IT IS
    ;; EXTREMELY IMPORTANT THAT NO CONNECTION CAN BE RESUSCITATED DURING THIS
    ;; LOOP, THAT IS, THIS LOOP MUST NEVER CALL `MAKE-CONNECTION'.  Such a
    ;; resuscitated connection would hopelessly confuse the logic of this
    ;; routine.  Connections have their own pool, so they can only come back as
    ;; connections.
    
    ;; This is why we defer deleting loose-ends until we are outside the loop.
    ;; Although delete-frame probably never calls make-connection, one could
    ;; reasonably expect that it might someday.

    ;; -fmw, 1/3/02
    (loop for block in blocks doing
      (when (frame-has-not-been-reprocessed-p block reference-fsn)
	(let ((connections (loop for conn being each connection of block
				 collect conn using gensym-cons)))

	  (loop for conn in connections doing
	    ;; CONN here is a connection structure, possibly reclaimed.  If it
	    ;; is reclaimed, then we've seen it earlier in this loop.  If it is
	    ;; not reclaimed, then this is the first time we've seen it.
	    (when (or (connection-has-been-reprocessed-p conn reference-fsn)
		      (bad-connection-p conn))

	      ;; Remove it and its port names from block, whether reclaimed or not.
	      #-connections-v2
	      (reclaim-slot-value-list (excise-connection-sublist-from-block block conn))
	      #+connections-v2
	      (let ((connection-item
		     (get-connection-item conn (connections block))))
		(setf (get-connection-item conn (connections block)) nil)
		(delete-connection-item conn (connections block))
		(reclaim-connection-item connection-item))

	      ;; Reclaim it only if it is not already reclaimed.
	      ;; A subset of the code in `reclaim-connection-and-delta-or-deltas'
	      (when (connection-has-not-been-reprocessed-p conn reference-fsn)
		(when (consp (delta-or-deltas conn))
		  (reclaim-slot-value-list (delta-or-deltas conn)))
		(setf (delta-or-deltas conn) nil)
		(reclaim-slot-value (connection-attributes-plist conn))
		(frame-serial-number-setf (frame-serial-number-for-connection conn)
					  (frame-serial-number-recycled))
		(reclaim-connection conn) ; [Note]
		(incff count))))
	  (reclaim-gensym-list connections)
	  (if (and (null (connections block))
		   (loose-end-p block))
	      (gensym-push block loose-ends)))))

    ;; Now reclaim the loose-ends outside the critical loop.
    (loop for loose-end in loose-ends doing
      (when (frame-has-not-been-reprocessed-p loose-end reference-fsn)      
	(delete-frame loose-end)))
    (reclaim-gensym-list loose-ends)
    
    count))

;; Presumably, since the KB has not yet aborted, bad connections have not yet
;; made it into other data structures such as role caches or spatial indices.
;; So removing the connection from every connections list of which is a member
;; should suffice.  We also delete dangling loose-ends, something else that
;; delete-connection does, although we are more paranoid and check that they are
;; indeed connectionless first.  See HQ-4162779, HQ-3387902. -fmw, 12/21/01

;; [Note]: If a connection-frame exists, then we ought to remove ourselves from
;; that, too, and probably delete the frame.  However, that case does not occur
;; in any corrupted KBs seen so far, so we leave it at that.


;;; The system-procedure-function `g2-clear-floating-connection-structures'
;;; reclaims connection-structures that have null connection-frame-or-class
;;; components.  These connection-structures were discovered shortly before
;;; 5.0rev1 was released in several kbs.  In addition, these structures had
;;; null input-end-object and output-end-object components.  This code locates
;;; them, removes their references, and reclaims them.  It is to be used by
;;; customers who suspect that they have this problem.

(defun-for-system-procedure g2-clear-floating-connection-structures ()
  (declare (keeps-g2-local-variables-valid nil))
  (let* ((blocks (loop for block being each class-instance of 'block
		       when (block-has-bad-connection-p block)
			 collect block using gensym-cons))
	 (reference-fsn (copy-frame-serial-number (current-frame-serial-number)))
	 (count (reclaim-bad-connections-of-blocks blocks reference-fsn)))

    ;; Safe to cons logbook pages, etc, now.
    (notify-user-at-console-and-on-logbook
      "Cleared ~d unattached connection~a." count (if (=f count 1) "" "s"))

    (reclaim-gensym-list blocks)
    (reclaim-frame-serial-number reference-fsn)
    (copy-evaluation-truth-value
      (if (>f count 0) evaluation-true-value evaluation-false-value))))


#+development
(defun find-blocks-with-bad-connections ()
  (loop for block being each class-instance of 'block
	when (block-has-bad-connection-p block)
	  collect block))





;;;; Connection Hookup Utilities



;;; The function `connect-loose-end-to-block' connects origin-loose-end to
;;; destination-block at the specified side and position.  The connection used
;;; (that which priviously connected to loose-end) is returned.  Note that
;;; loose-end is deleted as part of this process.

;;; At least one bend is always created.  If a vertical side connects to a
;;; horizontal side, a single bend that looks like an ell (L) is created:
;;;
;;;               |
;;;               ----
;;;
;;; If a horizontal side (left or right) connects to another horizontal side, or
;;; a vertical side (top or bottom) connects to another vertical side, then two
;;; bends are created, so it looks like an ell with another line at the bottom
;;; right corner:
;;;
;;;               |
;;;                ----
;;;                   |
;;;
;;; The optional fifth argument bend-distance? specifies the distance from the
;;; origin block at which to create a bend (if necessary).  (The "origin block"
;;; is the block at which origin-loose-end is attached.) The distance defaults
;;; to the distance from the edge of the origin block on the side the loose end
;;; is on to the edge of the destination-block on the side we're connecting
;;; (given by the side argument) minus default-stub-length (by default: 20).
;;;
;;; The optional sixth argument where-to-bend? can be nil or one of the
;;; following symbols:
;;;
;;;    DESTINATION - same as the default (nil) - creates the bend the given
;;;    distance from the destination block
;;;
;;;    ORIGIN - creates the bend the given distance from the origin
;;;    block, not from the destination block
;;;
;;;    LOOSE-END - creates the bend at current location of the loose end
;;;
;;;    ABSOLUTE - creates the bend at the given distance from the beginning of
;;;    the connection, regardless of which block is at which end.

;;; This does not expect there to be a preexisting stub on destination block.
;;; This adds a stub to destination-block, but only transiently: it gets deleted
;;; by the time the final connection is made.  Note that position is relative to
;;; the (0, 0) top-left corner position of destination-block.

(defun connect-loose-end-to-block
    (origin-loose-end destination-block side position
		      &optional bend-distance? where-to-bend?)
  (let* ((connection
	   (loop for c being each connection of origin-loose-end return c))
	 (end-position
	   (combine-side-and-position-on-side-for-end-position
	     side position))
	 (loose-end-is-input-end
	   (eq origin-loose-end (input-end-object connection)))
	 (origin-block-end-position
	   (if loose-end-is-input-end
	       (output-end-position connection)
	       (input-end-position connection)))
	 (origin-side
	   (get-side-given-end-position origin-block-end-position))
	 (bend-distance
	   (or bend-distance? default-stub-length))
	 (bend-distance-from-input-end
	   (if (eq (if (memq origin-side '(bottom top)) t nil) ; have bend?
		   (if (memq side '(bottom top)) t nil))
	       (case where-to-bend?
		 (loose-end
		  (if loose-end-is-input-end
		      (absw (-w (edge-of-side-of-block side destination-block)
				(edge-of-side-of-block
				  origin-side origin-loose-end)))
		      bend-distance))
		 ((nil destination)
		  (if loose-end-is-input-end
		      bend-distance
		      (-w (absw (-w (edge-of-side-of-block side destination-block)
				    (edge-of-side-of-block
				      origin-side
				      (get-block-at-other-end-of-connection
					connection origin-loose-end))))
			  bend-distance)))
		 (origin 
		  (if loose-end-is-input-end
		      (-w (absw (-w (edge-of-side-of-block side destination-block)
				    (edge-of-side-of-block
				      origin-side
				      (get-block-at-other-end-of-connection
					connection origin-loose-end))))
			  bend-distance)
		      bend-distance))
		 (absolute
		  (assert-for-development (fixnump bend-distance))
		  bend-distance))))	; must be a fixnum
	 (output-side
	   (if loose-end-is-input-end origin-side side))
	 (delta-or-deltas
	   (if (memq output-side '(top left))
	       bend-distance-from-input-end
	       ;; The connection goes up or to the left, invert the sign.
	       (when bend-distance-from-input-end
		 (-w bend-distance-from-input-end)))))
    (setf (delta-or-deltas connection)
	  (prog1 delta-or-deltas
	    (reclaim-slot-value (delta-or-deltas connection))))
    (cond
      (loose-end-is-input-end
       (setf (input-end-object connection) destination-block)
       (setf (input-end-position connection) end-position))
      (t
       (setf (output-end-object connection) destination-block)
       (setf (output-end-position connection) end-position)))
    (setf (connections origin-loose-end)
	  (prog1 nil
	    (reclaim-connection-item-table (connections origin-loose-end))))
    (delete-frame origin-loose-end)
    #-connections-v2
    (slot-value-push connection (connections destination-block))
    #+connections-v2
    (let ((connection-item-table
	   (or (connections destination-block)
	       (setf (connections destination-block)
		     (make-connection-item-table))))
	  (connection-item (make-connection-item connection)))
      (setf (get-connection-item connection connection-item-table)
	    connection-item))
    connection))



;;; The development-only function test-connect-loose-end-to-block provides an
;;; easy way to try out connect-loose-end-to-block and see that it works and see
;;; how to call it.
;;;
;;; You give it the name of a block that has a connection, the side that
;;; connection is on, the name of a block to connect to, and optionally the side
;;; and position at which to connect, which default to the side opposite the
;;; origin block and the center of that side, respectively.  Also optionally you
;;; can specify the "bend distance". (See connect-loose-end-to-block.)
;;;
;;; The connection chosen will be the connection on the specified side, or the
;;; first of those if there are more than one.  If no connection is found on
;;; that side, this does nothing.  Similarly, if origin-block or
;;; destination-block have no names, this does nothing.  If more than one item
;;; has the name used, the results are not strictly defined, other than to say
;;; the first item with that name will be used (which could be a random choice,
;;; and is not guaranteed stable).
;;;
;;; The theory behind this approach is that it should be quite easy to name two
;;; items, see where they have connections, and then try out connecting them,
;;; without the need to do a lot of digging through connection substructures.

;;; It is important to note that this DOES NOT UPDATE GRAPHICS INCREMENTALLY.
;;; This is primarily intended to support offscreen layout of connected
;;; workspace diagrams.  It would be tricky to make use of this with a workspace
;;; potentially being displayed, other than by doing a full refresh after the
;;; changes, which be too "flashy" and therefore risks disappointing users.

#+development
(defun test-connect-loose-end-to-block
    (origin-name origin-side destination-name
     &optional destination-side? destination-position? bend-distance?)
  (let* (origin-block destination-block loose-end
		      destination-side destination-position)
    (cond
      ((null (setq origin-block
		   (get-instance-with-name-if-any nil origin-name)))
       (values nil 'no-origin-block-with-that-name))
      ((null (setq destination-block
		   (get-instance-with-name-if-any nil destination-name)))
       (values nil 'no-destination-block-with-that-name))
      ((null (setq loose-end
		   (loop for c being each connection of origin-block
			 as input-end-object = (input-end-object c)
			 as other-block
			    = (get-block-at-other-end-of-connection c origin-block)
			 as connection-side
			    = (get-side-given-end-position
				(if (eq input-end-object origin-block)
				    (input-end-position c)
				    (output-end-position c)))			 
			 when (and (loose-end-p other-block)
				   (eq origin-side connection-side))
			   return other-block)))
       (break)
       (values nil 'no-loose-end-on-specified-side))
      (t
       (setq destination-side
	     (or destination-side?
		 (case origin-side
		   (left 'right)
		   (top 'bottom)
		   (right 'left)
		   (bottom 'top))))
       (assert-for-development
	 (memq destination-side '(left top right bottom))
	 "destination-side is ~a, not a valid side (LEFT, TOP, RIGHT, or BOTTOM)"
	 destination-side)
       (setq destination-position
	     (or destination-position?
		 (case destination-side
		   ((left right)
		    (halfw (height-of-block destination-block)))
		   (t
		    (halfw (width-of-block destination-block))))))
       (connect-loose-end-to-block
	 loose-end destination-block destination-side destination-position
	 (if (fixnump bend-distance?) bend-distance? default-stub-length)
	 (if (fixnump bend-distance?) 'absolute bend-distance?))))))

;; Private test functions -- tests to go with my bpel.kb. -- (MHD 10/26/04)

#+development
(defun test-connect-loose-end-to-block-for-mhd ()
  (test-connect-loose-end-to-block 'while 'right 'pick-join nil nil 'origin)
  (test-connect-loose-end-to-block 'sequence 'top 'flow-split)
  (test-connect-loose-end-to-block 'link-signal 'bottom 'compensate 'right)
  (test-connect-loose-end-to-block 'link-sync 'left 'sequence 'right)
  (test-connect-loose-end-to-block 'sequence 'bottom 'compensate 'left)
  (test-connect-loose-end-to-block 'compensate 'top 'pick-join nil nil 100)
  (test-connect-loose-end-to-block 'switch-join 'top 'flow-sync 'left nil)
  (test-connect-loose-end-to-block 'switch-join 'bottom 'switch-fork 'left nil)
  (test-connect-loose-end-to-block 'switch-fork 'right 'flow-sync 'bottom 150)
  (test-connect-loose-end-to-block 'switch-fork 'top 'flow-sync 'bottom 25)
  (test-connect-loose-end-to-block 'flow-sync 'bottom 'switch-fork 'top 75))

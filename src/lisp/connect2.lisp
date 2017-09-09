;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module CONNECT2

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Andreas Hofmann






(declare-forward-references
  (send-ws-representations-connection-moved              function events-g2)
  (send-ws-representations-item-rotated                  function events-g2)
  (change-connection-deltas-for-object-being-dragged     function connect3)
  (put-kink-into-connection-if-straight-1                function connect3)
  (connection-is-straight?                               function connect3)
  (find-connection-or-block-below-this-connection        function connect3)
  (update-extreme-edges-from-connection                  function connect3a)
  (determine-subworkspace-connection-posts-for-object    function connect4)
  (flush-subworkspace-connection-posts-for-object        function connect4)
  (local-edges-of-block-or-connection                    function connect3a)

  (clone-frame                                           function kb-load1)
  (note-kb-state-change                                  function kb-save2)
  (releasing-kb?                                         variable kb-save2)
  (note-change-or-deletion                               function kb-save3)
  (update-runtime-structures-according-to-edit           function install)
  (decache-roles-for-entities-related-to-this-connection function roles)
  (break-out-of-debug-messages                           function run)
  (icon-description-for-instance                         function definitions)
  (set-transient-and-propagate                           function stack-acts)
  (set-permanent-and-propagate                           function stack-acts)
  (set-neither-permanent-nor-transient-and-propagate     function stack-acts)
  (add-as-inferior-block                                 function traversals)

  (redraw-transfer-representations-of-block              function moves))

(declare-forward-reference get-ruling-for-meter function)

(declare-forward-reference send-ws-representations-item-insert-as-subblock function)
(declare-forward-reference bounding-region-of-block-or-connection function)
(declare-forward-reference send-ws-representations-item-moved function)

(declare-forward-reference recompute-selection-highlights function) ; COMMANDS0








;;; CONNECT2 contains all code related to connections except for
;;; primitives and editing functions which are in CONNECT1 and CONNECT3,
;;; respectively. CONNECT2 thus contains functions for making stubs, draw
;;; functions, support functions for reflection, rotation, and magnification,
;;; and other support functions.  CONNECT3 contains the editing functions.

;; Note: the immediate motivation to go from 2 to 3 submodules for connections
;; was the TI 3.0 bug that made it impossible to have the loop path definition
;; in the same file as it is used, as was previously the case.  The solution was to
;; cut off the last half of connect1 (which used the path), shift it over to
;; connect2, and shift connect2 over to connect3. (MHD 8/5/87)


;; To Do

;; It is currently possible to change stub definitions in object definitions
;; when there are instances.  Review.

;; Draw problems occur at the point where a connection joins a block when the
;; workspace is scaled.  See design notebook notes for 3/16/88 for why this
;; happens.  This is also an issue when scaling connections with complicated
;; cross sections.  A decision about which color in the cross section ribbon
;; "wins out" in an x-or situation must be made.  Also, cross sections for
;; all connections of same type should be the same at any particular scale.
;; Again, this suggests doing more calculation using image coordinates rather
;; than workspace coordinates.

;; There are some notes on user interface issues for connections in
;; ma:>agh>connections-notes.text.  These may be useful (to Mark Allen)
;; for user documentation of the connections interface.

;; Bug in rotate-reflect for connections with more than one bend
;; (deltas get messed up).

;; Tap should be a separate icon.  Don't allow new connections to
;; be dragged into a tap (another special case for 
;; add-new-connection-to-block).

;; Review end positions.  It seems that they may be off by more than
;; one pixel.  Also, they should be adjusted in a "nicer" way when
;; a new connection is added to a block.  One heuristic for this 
;; might be if the new connection is the only one on a side, then center it.
;; Actually, this may have problems also.  Also take a close look at
;; junctions.  They don't seem to be centered properly.

;; Need a better scaling algorithm.

;; Arrows.  If cross-section is simple, fins are o.k.  Else use 
;; icons alongside, or perhaps inside the connection.

;; Add-new-connection-to-block can be condensed.

;; Move some of the notes at the end to a text file.

;; Think about issues of deltas less than connection-half-width.

;; May want to abstract function for drawing one connection component
;; (code that loops through subrectangles).

;; Review comments.  Some of them should probably be removed.

;; Add "?" to delta-or-deltas since this may be nil.

;; For invisible entities and loose ends, give a trivial icon-description.
;; Don't make it nil and take out check for nil in draw method for 
;; entity.

;; Consider changing draw-connection so that it doesn't always form
;; a list of deltas but rather takes care of the individual cases of
;; whether delta-or-deltas is a list, atom, or nil. 



;;; A `stub-spec' is of a form identical to that of the slot feature stubs.  An
;;; accessor is defined for each of the components, connection-name-or-names,
;;; connection-type, connection-direction?, connection-side, and
;;; connection-position.

(def-list-structure (stub-spec
		      (:constructor nil)
		      (:consing-function nil))
  (connection-name-or-names
    connection-type
    connection-direction?
    connection-side
    connection-position
    connection-style-in-stub-spec
    connection-line-pattern-in-stub-spec))

;; This list structure definition is nice, but unfortunately it's never used,
;; preferring loop destructuring.  So you can't change the arrangement of stub
;; specs by merely changing this definition.



;;;; Making Connections

;;; Slot initializations for the connections slot in an entity are specified
;;; by the "stubs" slot feature in the class definition of the entity.  This
;;; slot feature is used by make-entity which calls make-stubs with the
;;; appropriate specifications.  Stub-specs is a list of the form
;;;
;;;  (connection-name-or-names
;;;    connection-type
;;;    direction?
;;;    side
;;;    position
;;;    style?
;;;    pattern?)
;;;
;;; Connection-name-or-names can be a symbol, or a list of symbols.
;;; Connection-type is the class for the connection.  Note that the
;;; connection-frame is not actually instantiated until it is edited.
;;; Direction?  can be nil 'input, or 'output.  Side can be 'left, 'right, 'top,
;;; or 'bottom.  Position is an integer in workspace units which specifies the
;;; position on the side.  The top-most point of the left and right sides, and
;;; the left-most point of the top and bottom sides, are specified by 0.  Style?
;;; can be nil or a connection style symbol, i.e., DIAGONAL or ORTHOGONAL (same
;;; as nil).  Pattern? can be nil or a connection line pattern (with nil meaning
;;; "solid").

(defun make-stubs (block stub-specs &optional transient?)
  #-connections-v2
  (setf (connections block)
	(loop for (connection-name-or-names connection-type direction? 
					    side position style? pattern? connection-arrows?)
		  in stub-specs
	      nconcing 
		(nconc
		  (if connection-name-or-names
		      (if (consp connection-name-or-names)
			  ;; NOTE: this will cause the connections slot looks like
			  ;;   (name1 name2 connection .. name connection ...)
			  ;; other than:
			  ;;   ((name1 name2) connection .. name connection)
			  ;; but it's on purpose.
			  (copy-list-using-slot-value-conses connection-name-or-names)
			  (slot-value-list connection-name-or-names)))
		  (let ((new-stub?
			  (make-stub
			    block connection-type direction? 
			    side position transient? style? pattern? connection-arrows?)))
		    ;; NOTE: if new-stub? is NIL, that usually means something wrong, and having a NIL
		    ;; after connection-name-or-names won't cause any issue in the LOOP of connections,
		    ;; but it's not necessary. Better if connection-name-or-names is also ignored.
		    ;; -- Chun Tian (binghe), July 19, 2015.
		    (when new-stub? (slot-value-list new-stub?))))))
  #+connections-v2
  (let ((connection-item-table (make-connection-item-table)))
    (loop for (connection-name-or-names connection-type direction? 
	       side position style? pattern? connection-arrows?)
	      in stub-specs
	  for new-stub? = (make-stub
			    block connection-type direction? 
			    side position transient? style? pattern? connection-arrows?)
	  when new-stub? do
      (let ((connection-item (make-connection-item new-stub?))
	    (names (when connection-name-or-names
		     (if (consp connection-name-or-names)
			 (copy-list-using-slot-value-conses connection-name-or-names)
		       (slot-value-list connection-name-or-names)))))
	(case direction?
	  (input
	   (setf (connection-item-input-names connection-item) names))
	  (t ; output or nil
	   (setf (connection-item-output-names connection-item) names)))
      (setf (get-connection-item new-stub? connection-item-table)
	    connection-item)))
    (setf (connections block) connection-item-table)))


;;; The function `add-stub-given-spec' adds a permanent stub given a stub-info
;;; list.

(defun add-stub-given-spec (block stub-info)
  (gensym-dstruct-bind ((connection-name-or-names
			 connection-type direction? side position
			 connection-style? line-pattern?)
		       stub-info)
    (add-stub
      block connection-name-or-names 
      connection-type direction? side position nil connection-style? line-pattern?)))

;; Old comment:
;; Fix for HQ-2371466
;; This is a blatant hack to get a stub added whether it's called from the
;; change attribute code for stubs (length = 6 where the sixth element is the
;; connection-style? and there is no seventh element) or from the functions
;; make-new-transient-stub and make-transient-stub-to-replace- existing-one
;; (length = 7: where the sixth element is transient? and the seventh element is
;; connection-style?). (ghw 12/16/98)


;;; The function `add-stub' is useful in generating trees.  It takes a stub
;;; description, a la make-stubs, but just adds one new stub to the block
;;; instead of replacing the whole list.  It assumes that block is already
;;; on the workspace and calls place-stub-loose-end-onto-workspace.  Add-stub
;;; returns the new connection if make-stub was successful.

(defun add-stub
       (block connection-name-or-names connection-type direction? side position
	&optional transient? connection-style? line-pattern? connection-arrows?)
  (let ((new-stub?
	  (make-stub
	    block connection-type direction? side position transient?
	    connection-style? line-pattern? connection-arrows?)))
    (when new-stub?
      #-connections-v2
      (setf (connections block)
	    (nconc (connections block)
		   (if connection-name-or-names
		       (if (consp connection-name-or-names)
			   (copy-list-using-slot-value-conses 
			     connection-name-or-names)
			   (slot-value-list connection-name-or-names)))
		   (slot-value-list new-stub?)))
      #+connections-v2
      (progn
	(unless (connections block)
	  (setf (connections block) (make-connection-item-table)))
	(let ((connection-item (make-connection-item new-stub?))
	      (names
	       (when connection-name-or-names
		 (if (consp connection-name-or-names)
		     (copy-list-using-slot-value-conses connection-name-or-names)
		   (slot-value-list connection-name-or-names)))))
	  (case direction?
	    (input
	     (setf (connection-item-input-names connection-item) names))
	    (t ; output or nil
	     (setf (connection-item-output-names connection-item) names)))
	  (setf (get-connection-item new-stub? (connections block))
		connection-item)))
      (let ((workspace? (get-workspace-if-any-macro block)))
	(when workspace?
	  (place-stub-loose-end-onto-workspace block new-stub? (superblock? block))
	  (determine-subworkspace-connection-posts-for-object new-stub? block)
	  new-stub?)))))

(def-system-variable stub-length-to-use? connect2 nil)
(def-system-variable default-stub-length connect2 20)



;;;; Connection Frames

;;; All connections made by the user are made via make-stub except for
;;; the extra connection made when a junction is created.  This is 
;;; handled separately by insert-junction-block.

;;; The connection-frame-or-class slot of a connection can be a symbol
;;; (the class name) or a frame.  Whether a connection frame is actually
;;; instantiated or not is transparent to the user.  Thus, 
;;; connection frames are not initially instantiated for a connection
;;; but are instantiated as needed according to the following rules:
;;; 1.  When the user clicks on a connection and chooses the "table"
;;; or "disable" options, a connection frame will be instantiated if
;;; it doesn't already exist (see handle-choice-for-connection-menu).
;;; 2.  In the role service functions serve-first-instance-of-class
;;; and search-for-directly-connected-entities, if a connection is
;;; encountered that satisfies the pattern, a connection frame 
;;; will be instantiated if it doesn't exist and returned.
;;; 3.  When a frame is cloned, clone-frame calls clone-stub-for-connection
;;; which clones the connection frame if one exists in the original.
;;; 4.  In certain cases, such as when an attribute of a connection frame
;;; is specified (in the definition of the connection class) to contain
;;; a variable, a connection frame must always be instantiated for the
;;; connection.  This is so that, among other reasons, simulation can 
;;; take place if necessary.  Make-stub deals with this case and
;;; slot-init-form-needs-evaluation? is used
;;; to decide whether the connection frame must be instantiated (see also
;;; slot putter for "change" in DEFINITIONS).  If a connection frame does
;;; not have to be instantiated (the more common case) make-stub will just
;;; set the connection-frame-or-class slot of the connection to the class.

;;; When a connection is made by insert-junction-block, it may also be
;;; necessary to instantiate a connection frame according to the 
;;; conditions of case 4 above.  This is handled separately by 
;;; insert-junction-block.

;;; When a connection frame is instantiated, it may also be necessary to 
;;; activate it.  The function get-or-make-connection-frame-and-activate-
;;; if-appropriate instantiates a connection frame, if one doesn't exist, 
;;; for the argument connection and activates it if this is appropriate.  This
;;; function is used in all of the above cases except the case 4; make-stub
;;; never activates connection frames since the stub has not yet been 
;;; placed onto a workspace.  Activation in case 4 can be subdivided into
;;; 3 cases:
;;; 1.  An entity has just been made and is placed after being dragged.
;;; Make-stub is called to make the stubs (and connection frames
;;; if necessary).  Activation of the entity and its stubs is taken care
;;; of by exit-dragging-context.  
;;; 2.  A stub is made due to deletion (slot value reclaimer for connections
;;; or delete-connection-to-stub) or cloning (clone-stub-for-connection).
;;; Here also, make-stub is called to make the stubs and connection frames
;;; if necessary.  Activation is taken care of by place-stub-loose-end-onto-workspace.
;;; 3.  A connection is made by insert-junction-block.  Here, make-stub
;;; is not called.  Insert-junction-block makes the connection frame if 
;;; necessary and also takes care of activating it if necessary.


;;; Make-stub

;;; Make-stub takes as arguments block, connection-type, direction?,
;;; side, and position.  These come from stub-specs which are a 
;;; slot-feature of the slot connections (see make-entity and make-stubs).
;;; Block is the block to which the stub should be attached, 
;;; connection-type is the class name for frames to be instantiated
;;; for the connection; it goes in the connection-frame-or-class 
;;; slot of the connection structure.  Direction? can be 'input, 'output,
;;; or nil and specifies the directionality of the connection.
;;; Side and position (position-on-side) indicate where the stub is
;;; attached to the block.

;;; The arg connection-frame-or-class will always be a class except when
;;; make-stub is called by clone-stub-for-connection in which case it may be a
;;; connection frame (the connection frame cloned from the original connection
;;; frame.

;;; Make-stub and related functions deal with transient connections.  A
;;; transient connection always has a connection frame instantiated for it and
;;; that connection frame is marked as transient.  A transient connection always
;;; needs a connection frame so that it can be handled by a create action and
;;; put into a local variable.  Connection-style?  can be 'orthogonal or
;;; 'diagonal.  If connection-style?  is nil, style will be orthogonal.

(defun make-stub ; old
       (block connection-frame-or-class direction? side position 
	&optional transient? connection-style? line-pattern? connection-arrows?)
  (make-stub-new block connection-frame-or-class
		 (not (not direction?))			    ; t or nil
		 (if (eq direction? 'input) 'input 'output) ; 'output or 'input
		 side position
		 ;; optional arguments
		 transient? connection-style? line-pattern? connection-arrows?))

(defun make-stub-new
       (block connection-frame-or-class directed? direction side position 
	&optional transient? connection-style? line-pattern? connection-arrows?)
  (cond
    ((or (framep connection-frame-or-class)
	 (subclassp connection-frame-or-class 'connection))
     ;; Check to make sure that connection class exists.  Note that it is
     ;; assumed that if connection-frame-or-class is a frame, then the
     ;; connection is defined.  This is a valid assumption because if a
     ;; connection class is not defined, stubs of that class cannot
     ;; be made in the first place, and if a connection class becomes
     ;; undefined, all instances of connections for that class are 
     ;; deleted.

     (let ((connection (make-connection))
	   (make-transient? (or transient? (transient-p block)))
	   (noting-changes-to-kb-p nil))

       (when (not make-transient?)
	 (set-connection-permanently-changed connection))

       (setf (frame-serial-number-for-connection connection)
	     (copy-frame-serial-number (increment-current-frame-serial-number)))

       (change-connection-attribute 
	 connection 'connection-style connection-style?)
       (change-connection-attribute
	 connection 'connection-arrows (copy-for-slot-value connection-arrows?))
       (change-connection-attribute
	 connection 'line-pattern (copy-for-slot-value line-pattern?))

       (let* ((stub-length
		(or
		  stub-length-to-use?
		  (get-stub-length-given-connection-frame-or-class
		    connection-frame-or-class)
		  default-stub-length))
	      (stub-loose-end
		(make-frame 'loose-end))
	      (stub-x-position
		(case side
		  (right
		   (+w (right-edge-of-block block)
		       1
		       stub-length))
		  (left
		   (-w (left-edge-of-block block)
		       stub-length))
		  (t				       ; if (top bottom)
		   (+w (left-edge-of-block block)
		       position))))
	      (stub-y-position
		(case side
		  (top
		   (-w (top-edge-of-block block)
		       stub-length))
		  (bottom
		   (+w (bottom-edge-of-block block)
		       1
		       stub-length))
		  (t				       ; if (left right)
		   (+w (top-edge-of-block block)
		       position)))))

	 (when make-transient?
	   (set-transient stub-loose-end))
	 
	 (funcall-method 
	   'shift stub-loose-end
	   (+w (-w (left-edge-of-block stub-loose-end))
	       stub-x-position)
	   (+w (-w (top-edge-of-block stub-loose-end))
	       stub-y-position))
	 
;	 (setf (connection-not-directed? connection)
;	       (not direction?))

	 (if directed?
	     (set-connection-directed connection)
	     (set-connection-not-directed connection))

	 #-connections-v2
	 (setf (connections stub-loose-end)
	       (slot-value-list 'stub-connection connection))
	 #+connections-v2
	 (let ((connection-table (make-connection-item-table))
	       (connection-item (make-connection-item connection)))
	   (case direction
	     (input
	      (setf (connection-item-output-names connection-item)
		    (slot-value-list 'stub-connection)))
	     (t ; output or undirected
	      (setf (connection-item-input-names connection-item)
		    (slot-value-list 'stub-connection))))
	   (setf (get-connection-item connection connection-table)
		 connection-item)
	   (setf (connections stub-loose-end) connection-table))

	 (if (eq direction 'input)
	     (setf (output-end-object connection)
		   block
		   (output-end-position connection)
		   (combine-side-and-position-on-side-for-end-position
		     side 
		     (case side
		       ((left right)
			position)
		       (t			       ; top or bottom
			position)))
		   (input-end-object connection)
		   stub-loose-end
		   (input-end-position connection)
		   (combine-side-and-position-on-side-for-end-position
		     (case side
		       (left 'right)
		       (right 'left)
		       (top 'bottom)
		       (t			       ; bottom
			'top))
		     0))
	     (setf (input-end-object connection)
		   block
		   (input-end-position connection)
		   (combine-side-and-position-on-side-for-end-position
		     side 
		     (case side
		       ((left right)
			position)
		       (t			       ; top or bottom
			position)))
		   (output-end-object connection)
		   stub-loose-end
		   (output-end-position connection)
		   (combine-side-and-position-on-side-for-end-position
		     (case side
		       (left 'right)
		       (right 'left)
		       (top 'bottom)
		       (t			       ;bottom
			'top))
		     0)))

	 (when make-transient?
	   (set-transient-connection connection))

	 (cond
	   ((and (not (framep connection-frame-or-class))
		 (or make-transient?
		     (always-instantiate-connection-frame-for-this-class?
		       connection-frame-or-class)))
	    (setq connection-frame-or-class
		  (make-new-connection-frame-for-connection
		    connection connection-frame-or-class))
	    ;; Instantiate connection frame if necessary.
	    )
	   (t
	    (setf (connection-frame-or-class connection)
		  connection-frame-or-class)
	    (when (and (framep connection-frame-or-class) make-transient?)
	      (set-transient-and-propagate connection-frame-or-class nil))))
	 
	 (when (framep connection-frame-or-class)
	   (setf (connection-for-this-connection-frame connection-frame-or-class)
		 connection)
	   ;; This is necessary in cases of cloning where a connection frame is
	   ;; passed in to make-stub.  The cloned connection frame has to have this
	   ;; backpointer set.
	   (update-runtime-structures-according-to-edit connection-frame-or-class))

	 connection)))
    (t
     (write-warning-message* 1
       (tformat "Attempting to make a connection of class ~A. ~%"
		connection-frame-or-class)
       (tformat "This class is not defined as a connection class."))
     nil)))

(defun get-connection-for-loose-end (loose-end)
  ;; GENSYMCID-1706: G2 Abort - Pulling stubs into object
  ;;
  ;; The old version "(second (connections loose-end))" is wrong because the loose-end
  ;; may become both input name and output name in certain cases, and in this case the
  ;; connection becomes the 3rd element in its connections slot. -- Fei Liu, May 2016.
  #-connections-v2
  (loop for connection-or-symbol in (cdr (connections loose-end))
	do (unless (symbolp connection-or-symbol)
	     (return connection-or-symbol)))
  #+connections-v2
  (loop for connection being each connection of loose-end
	do (return connection)))

(defun always-instantiate-connection-frame-for-this-class?	
       (connection-class)
  (when (not releasing-kb?)
    ;; Releasing-kb? is checked to prevent warning messages
    ;; when a new kb is loaded for the case where the connection frame
    ;; contains frames in its attributes which are no longer defined.
    (or (loop for slot-description 
	      in (slot-descriptions (class-description connection-class))
	  as slot-init-form = (slot-init-form slot-description)
	  thereis (slot-init-form-needs-evaluation? slot-init-form)))))


;;; Place-stub-loose-end-onto-workspace is called by the slot value reclaimer 
;;; for connections, and delete-connection-to-stub.
;;; If stub-connection has a connection frame, then it was instantiated just
;;; prior to the call to this function.  It may be necessary to activate it.

;;; added workspace existence check to obviate crashing -rdf, 1/4/95
(defun-void place-stub-loose-end-onto-workspace
    (block stub-connection workspace)
  (when workspace
    (let ((loose-end
	    (get-block-at-other-end-of-connection 
	      stub-connection block))
	  (connection-frame-or-class
	    (connection-frame-or-class stub-connection)))
      (when (framep connection-frame-or-class)
	(activate-connection-frame-if-appropriate
	  connection-frame-or-class workspace))
      (add-subblock loose-end workspace)))

  (when g2-has-v5-mode-windows-p
    ;;(format t "placing stub::insert-move-connection~%")
    (send-ws-representations-item-insert-as-subblock
      stub-connection
      block
      (find-connection-or-block-below-this-connection
	stub-connection (input-end-object-internal stub-connection)))
    (send-ws-representations-connection-moved
      stub-connection)))

(defun get-or-make-connection-frame-and-activate-if-appropriate (connection)
  (let ((connection-frame-for-connection
	  (let ((connection-frame-or-class
		  (connection-frame-or-class connection)))
	    (if (framep connection-frame-or-class)
		connection-frame-or-class
		;; Make frame if none present
		(make-and-install-new-connection-frame
		  connection connection-frame-or-class))))
	(superblock?
	  (get-superblock-of-connection connection)))
    (activate-connection-frame-if-appropriate
      connection-frame-for-connection superblock?)
    connection-frame-for-connection))

;; No check is made for whether a connection definition exists since it should
;; always exist at this point.


(defun activate-connection-frame-if-appropriate
    (connection-frame superblock?)
  (if (and (not (active-p connection-frame))
	   superblock?
	   (active-p superblock?))
      (funcall-method 'activate-if-possible-and-propagate 
		      connection-frame)))


;;; Update-activate-status-of-connection-frames-being-placed is called
;;; by exit-dragging-context to update the activation status of 
;;; connection frames in connections of the block being dragged.
;;; The update of activation status is handled exactly the same way as
;;; in add-subblock.

;(defun update-activate-status-of-connection-frames-being-placed
;       (block-being-dragged workspace?)
;  (when workspace?
;    (loop for dragged-connection 
;	      being each connection of block-being-dragged
;	  as connection-frame-or-class
;	     = (connection-frame-or-class dragged-connection)
;	  do
;      (if (framep connection-frame-or-class)
;	  (cond ((active-p workspace?)
;		 (funcall-method 
;		   'activate-if-possible-and-propagate
;		   connection-frame-or-class))
;		((or (manually-disabled-p workspace?)
;		     (frame-status-function workspace?)
;		     (ancestor-not-activatable-p workspace?))
;		 (funcall-method 'deactivate-and-propagate connection-frame-or-class t))
;		(t (funcall-method 'deactivate-and-propagate connection-frame-or-class nil)))))))

;; Not used anymore because add-subblock now does this. (MHD 4/1/91)



;;; Update-new-subblock-connections-activation-and-propagate ...

;;; Update-removed-subblock-connections-activation-and-propagate ...

;;; ... only to be called from add-subblock.  (There is a forward reference to
;;; the connections iteration path.)

(defun update-new-subblock-connections-activation-and-propagate (block superblock)
  (loop for connection being the connections of block
	when (framep (connection-frame-or-class connection))
	  do (update-new-subblock-activation-and-propagate
	      (connection-frame-or-class connection)
	       superblock)))


(defun update-removed-subblock-connections-activation-and-propagate (block)  
  (loop for connection being the connections of block
	when (framep (connection-frame-or-class connection))
	  do (funcall-method-if-any
	       'deactivate-and-propagate
	       (connection-frame-or-class connection)
	       nil)))






;;; Deactivate-connection-frames-being-picked-up is called by enter-dragging-context
;;; to deactivate connection frames in connections of the block being picked up.
;;; The deactivation is handled exactly the same way as in remove-as-subblock-if-necessary.

;(defun deactivate-connection-frames-being-picked-up (block)
;  (loop for dragged-connection 
;	    being each connection of block
;	as connection-frame-or-class
;	   = (connection-frame-or-class dragged-connection)
;	do
;    (if (and (framep connection-frame-or-class)
;	     (active-p connection-frame-or-class))
;	(funcall-method-if-any
;	  'deactivate-and-propagate
;	  BLOCK					; <--- this never did anything
;	  nil))))				;   because it said BLOCK here
						;   instead of CONNECTION-FRAME-OR-CLASS.
						;   Now it is obsolete anyway. (MHD 4/1/91)

;; Not used anymore because remove-as-subblock-if-necessary now does this. (MHD 4/1/91)



(defun get-superblock-of-connection-frame (connection-frame)
  (get-superblock-of-connection 
    (connection-for-this-connection-frame connection-frame)))

(defun get-superblock-of-connection (connection)
  (superblock? (input-end-object connection)))

(defun make-and-install-new-connection-frame 
       (connection connection-class)
  (let ((new-connection-frame
	  (make-new-connection-frame-for-connection
	    connection connection-class)))
    (update-runtime-structures-according-to-edit connection-class)
    new-connection-frame))




(defun make-new-connection-frame-for-connection
    (connection connection-class)
  (let ((new-connection-frame
	  (make-entity connection-class)))
    (note-change-to-connection connection)
    (setf (connection-for-this-connection-frame new-connection-frame)
	  connection
	  (connection-frame-or-class connection)
	  new-connection-frame)
    (when (transient-connection-p connection)
      (set-transient-and-propagate new-connection-frame nil))
    (add-as-inferior-block new-connection-frame
			   (output-end-object connection))

    ;; Copy over important slots from the connection.

    ;; This called the slot putter, causing the connection to be redrawn!
;    (update-style-in-connection-frame connection new-connection-frame)

    (setf (connection-style new-connection-frame)
	  (connection-style-of-connection connection))

    (setf (connection-arrows new-connection-frame)
	  (copy-for-slot-value (connection-arrows-of-connection connection)))

    (setf (line-pattern new-connection-frame)
	  (copy-for-slot-value (connection-line-pattern connection)))

    (setf (layer-position-of-block new-connection-frame)
	  (layer-position-of-connection connection))

    new-connection-frame))

;; make-new-connection-frame-for-connection requires that the end objects of
;; the connection be filled in before it is called.

(def-class-method cleanup (connection)
  (funcall-superior-method connection)
  (let ((connection-structure?
	  (connection-for-this-connection-frame connection)))
    ;; It is a violation to have a connection frame that does not have an
    ;; associated connection structure; however, there are kbs that do have that
    ;; problem.  A post-loading function now deletes them.  See the post-loading
    ;; function, delete-connection-frames-without-connection-structures, in
    ;; KB-LOAD2.  (ghw 9/16/95)
    #+development
    (unless connection-structure?
      (cerror  "connect2" "connection-frame-without-structure"))
    (when connection-structure?
      (setf (connection-frame-or-class connection-structure?)
	    (class connection)))))


;;; The function `copy-unsaved-slots-from-connection-to-connection-frame' is
;;; called during KB-load to copy slots in the connection structure up to the
;;; corresponding slots in the connection frame (if any), since by convention
;;; those slots in the connection frame are not saved.

(defun copy-unsaved-slots-from-connection-to-connection-frame (connection connection-frame)
  (change-slot-value
    connection-frame 'connection-style
    (connection-style-of-connection connection))
  (change-slot-value
    connection-frame 'connection-arrows
    (copy-for-slot-value (connection-arrows-of-connection connection)))
  (change-slot-value
    connection-frame 'line-pattern
    (copy-for-slot-value (connection-line-pattern connection))))

;; Also see make-new-connection-frame-for-connection



;; Clone-stub-for-connection is used by clone-frame.  It calls make-stub
;; to make the new stub which is returned.

(defun clone-stub-for-connection 
       (previous-connection? connection-being-cloned 
	frame-being-cloned new-frame)
  (let* ((old-connection-frame-or-class
	   (connection-frame-or-class connection-being-cloned))
	 (new-connection-frame-or-class
	   (if (framep old-connection-frame-or-class)
	       (clone-frame old-connection-frame-or-class)
	       old-connection-frame-or-class))
	 (output?
	   ;; Note: if connection-being-cloned equals to the previous connection,
	   ;; then it must be a input connection, because in #-connections-v2,
	   ;; if the same connection appears twice in the connection list, the 1st
	   ;; one is output connection, 2nd one is input connection.
	   (and (neq connection-being-cloned previous-connection?)
		(eq (input-end-object connection-being-cloned) frame-being-cloned)))
	 (new-end-position
	   (if output?
	       (input-end-position connection-being-cloned)
	       (output-end-position connection-being-cloned)))
	 (new-end-side
	   (get-side-given-end-position
	     new-end-position))
	 (new-end-position-on-side
	   (get-position-on-side-given-end-position
	     new-end-position))
	 (new-stub
	   (make-stub-new
	     new-frame
	     new-connection-frame-or-class
	     (connection-directed? connection-being-cloned) ; directed?
	     (if output? 'output 'input) ; direction
	     new-end-side
	     new-end-position-on-side)))

    (clone-connection-attributes-plist connection-being-cloned new-stub)

;    (place-stub-loose-end-onto-workspace
;      new-frame new-stub
;      (superblock? frame-being-cloned))
    ;; It is wrong to place the stub here since new-frame has not
    ;; yet been placed.  Exit dragging context takes care of putting
    ;; new-frame and its connections onto the workspace.

    new-stub))

(defun clone-connection-attributes-plist (old-connection new-connection)
  (change-connection-attribute
    new-connection 'connection-style
    (getfq (connection-attributes-plist old-connection)
	   'connection-style))
  (change-connection-attribute
    new-connection 'connection-arrows
    (copy-for-slot-value (connection-arrows-of-connection old-connection)))
  (change-connection-attribute
    new-connection 'line-pattern
    (copy-for-slot-value (connection-line-pattern old-connection))))
  
;; Note that only the connection-style, line-pattern, and connection-arrows
;; attributes are currently cloned.

(defun set-connections-of-transient-block-transient (block)
  (loop for connection being each connection of block 
	as connection-frame-or-class 
	   = (connection-frame-or-class connection)
	as loose-end-maybe 
	   = (get-block-at-other-end-of-connection 
	       connection block)
	do
    (make-connection-transient connection)
    (when (frame-of-class-p loose-end-maybe 'loose-end)
      (set-transient loose-end-maybe)
      (clear-permanent-block loose-end-maybe))
    (when (framep connection-frame-or-class)
      (set-transient-and-propagate connection-frame-or-class nil))))

(defun set-connections-of-permanent-block-permanent (block)
  (loop for connection being each connection of block 
	as connection-frame-or-class 
	   = (connection-frame-or-class connection)
	as block-at-other-end
	   = (get-block-at-other-end-of-connection 
	       connection block)
	do
    (cond
      ((frame-of-class-p block-at-other-end 'loose-end)
       (set-permanent-block block-at-other-end)
       (clear-transient block-at-other-end)
       (make-connection-permanent connection)
       (when (framep connection-frame-or-class)
	 (set-permanent-and-propagate connection-frame-or-class nil)))
      ((permanent-block-p block-at-other-end)
       ;; Don't propagate unless both blocks are permanent.
       (make-connection-permanent connection)
       (when (framep connection-frame-or-class)
	 (set-permanent-and-propagate connection-frame-or-class nil))))))

(defun set-connections-of-neither-permanent-nor-transient-block-neither-permanent-nor-transient
       (block)
  (loop for connection being each connection of block 
	as connection-frame-or-class 
	   = (connection-frame-or-class connection)
	as loose-end-maybe 
	   = (get-block-at-other-end-of-connection 
	       connection block)
	do
    (make-connection-neither-permanent-nor-transient connection)
    (when (frame-of-class-p loose-end-maybe 'loose-end)
      (clear-transient loose-end-maybe)
      (clear-permanent-block loose-end-maybe))
    (when (framep connection-frame-or-class)
      (set-neither-permanent-nor-transient-and-propagate connection-frame-or-class nil))))

(defun make-connection-transient (connection)
  (note-change-or-deletion connection t)
  (set-transient-connection connection)
  (let ((connection-frame (connection-frame-or-class connection))
	(output-end-object (output-end-object connection))
	(input-end-object (input-end-object connection)))
    (when (framep connection-frame)
      (set-transient connection-frame)
      (clear-permanent-block connection-frame))
    (when (frame-of-class-p output-end-object 'loose-end)
      (set-transient output-end-object)
      (clear-permanent-block output-end-object))
    (when (frame-of-class-p input-end-object 'loose-end)
      (set-transient input-end-object)
      (clear-permanent-block input-end-object))))

(defun make-connection-permanent (connection)
  (note-change-or-deletion connection t)
  (clear-transient-connection connection)
  (let ((connection-frame (connection-frame-or-class connection))
	(output-end-object (output-end-object connection))
	(input-end-object (input-end-object connection)))
    (when (framep connection-frame)
      (clear-transient connection-frame)
      (set-permanent-block connection-frame))
    (when (frame-of-class-p output-end-object 'loose-end)
      (clear-transient output-end-object)
      (set-permanent-block output-end-object))
    (when (frame-of-class-p input-end-object 'loose-end)
      (clear-transient input-end-object)
      (set-permanent-block input-end-object))))

(defun make-connection-neither-permanent-nor-transient (connection)
  (note-change-or-deletion connection t)
  (clear-transient-connection connection)
  (let ((connection-frame (connection-frame-or-class connection)))
    (when (framep connection-frame)
      (clear-transient connection-frame)
      (clear-permanent-block connection-frame))))



;;;; Support for adding and deleting connections from blocks

;;; Replace-connection-in-block takes a block, a connection to be
;;; replaced and a new connection as arguments.  The connection to be
;;; replaced must be in the connections slot of the entity or nothing
;;; will happen.  Note that the connection names are not changed.  In
;;; general, the list structure in the connections slot is not altered.
;;; The only exception to this is in the case where the new connection
;;; is already in the connections slot.  This happens, for example, when
;;; both ends of a connection are joined to the same entity.  In this
;;; case, the list structure in the connections slot may have to be
;;; modified so that the connection appears twice, in the following format:
;;; ( output-name-or-names connection input-name-or-names connection ...)

;;; A related special case is when the above format already exists for
;;; some connection and it is the connection to be replaced.  This 
;;; happens, for example, when a connection is broken for some reason
;;; such as deletion back to stubs or insertion of a junction.
;;; The problem is to decide whether to put the new connection after
;;; the output name or after the input name.  If the input-end-object
;;; of the new connection is the block, then it is put after the
;;; output name, else, after the input name.  In order to accomplish
;;; this test, it is assumed that the end information for the
;;; connection-to-be-replaced and for the new-connections
;;; is valid when this function is called.

;; May eventually have to do some end position check rather than
;; end object check.

(defun replace-connection-in-block
       (block
	connection-to-be-replaced
	new-connection)
  (note-change-to-block block 'connections)
  (decache-roles-for-entities-related-to-this-connection
    connection-to-be-replaced)
  (decache-roles-for-entities-related-to-this-connection
    new-connection)

  (let* ((connection-to-be-replaced-duplicated?
	  #-connections-v2
	  (memq connection-to-be-replaced
		(cdr (memq connection-to-be-replaced
			   (connections block))))
	  #+connections-v2 ; now it's simply stored inside a structure
	  (connection-item-duplicated?
	    (get-connection-item connection-to-be-replaced (connections block))))
	 (side nil)
	 (position nil)
	 (position-on-side nil)
	 (raw-stub-specs?
	  (get-class-feature-in-class-description-if-any
	    (class-description-slot block) 'stubs))
	 (connection-replaced-via-stub-spec? nil)
	 (stub-specs?
	  (when (and raw-stub-specs?
		     (eq (car raw-stub-specs?) 'stubs)
		     (not (eq (cdr raw-stub-specs?) 'none)))
	    (cdr raw-stub-specs?))))

    (when (and stub-specs?
	       connection-to-be-replaced-duplicated?)
      (cond ((eq block (input-end-object new-connection))
	     (setq position (input-end-position new-connection)))
	    (t
	     (setq position (output-end-position new-connection))))
      (setq side (get-side-given-end-position position))
      (setq position-on-side (get-position-on-side-given-end-position position))
      ;; NOTE: in this case, only ONE of both connections is to be replaced. -binghe
      #-connections-v2
      (loop with connection-list-to-search = (connections block)
	    with test-spec? = nil
	    with connection-position = 0
	    while connection-list-to-search
	    for search-head = (car connection-list-to-search)
	    until connection-replaced-via-stub-spec?
	    do
	(cond ((and (symbolp search-head)
		    (eq (cadr connection-list-to-search) connection-to-be-replaced))
	       (loop for spec in stub-specs?
		     with name = search-head
		     with spec-found? = nil
		     until spec-found?
		     until connection-replaced-via-stub-spec?
		     do
		 (when (eq (car spec) name)
		   (setq spec-found? t)
		   (when (and (eq side (connection-side spec))
			      (=f position-on-side (connection-position spec)))
		     (setf (cadr connection-list-to-search)
			   new-connection)
		     (setq connection-replaced-via-stub-spec? t)))))
	      ((connection-p search-head)
	       (setq test-spec? (nth connection-position stub-specs?))
	       (when (and test-spec?
			  (eq side (connection-side test-spec?))
			  (=f position (connection-position test-spec?)))
		 (setf (car connection-list-to-search)
		       new-connection)
		 (setq connection-replaced-via-stub-spec? t))
	       (incff connection-position)))
	(setq connection-list-to-search (cdr connection-list-to-search)))
      ;; NOTE: in this version, the idea is to use stub spec to find out the correct position
      ;; (input/output) to be replaced, and then copy the old names.
      #+connections-v2
      (let* ((connection-item-table (connections block))
	     (connection-item
	      (get-connection-item connection-to-be-replaced connection-item-table))
	     ;; possible names to be replaced
	     (input-names (connection-item-input-names connection-item))
	     (output-names (connection-item-output-names connection-item))
	     ;;
	     (new-connection-item (make-connection-item new-connection))) ; name is still unknown
	(setf (connection-item-duplicated? connection-item) nil)
	(when (or input-names output-names) ; if either names are non-NIL
	  (loop for spec in stub-specs?
		with spec-found? = nil
		until spec-found?
		do
	    (cond ((memq (car spec) input-names)
		   (setq spec-found? t)
		   (when (and (eq side (connection-side spec))
			      (=f position-on-side (connection-position spec)))
		     (setf (connection-item-input-names new-connection-item)
			   (copy-list-using-slot-value-conses input-names))))
		  ((memq (car spec) output-names)
		   (setq spec-found? t)
		   (when (and (eq side (connection-side spec))
			      (=f position-on-side (connection-position spec)))
		     (setf (connection-item-input-names new-connection-item)
			   (copy-list-using-slot-value-conses output-names)))))))
	#+development
	(when (connection-exist-p new-connection (connections block))
	  (error "impossible: new-connection is already in block"))
	(setf (get-connection-item new-connection connection-item-table)
	      new-connection-item)))

    (cond
      (connection-replaced-via-stub-spec? nil)
      ((connection-exist-p new-connection (connections block))
       ;; special case of both ends of connection being attached to same block
       #-connections-v2
       (let* ((output-port-connection
		(if (eq (input-end-object connection-to-be-replaced) block)
		    connection-to-be-replaced
		    new-connection))
	      (input-port-connection
		(if (eq output-port-connection connection-to-be-replaced)
		    new-connection
		    connection-to-be-replaced))
	      (output-port-sublist
		(get-connections-sublist-for-connection
		  block output-port-connection))
	      (output-port-sublist-last-connection-sublist
		(get-last-connection-sublist output-port-sublist))
	      (input-port-sublist
		(get-connections-sublist-for-connection
		  block input-port-connection))
	      (input-port-sublist-last-connection-sublist
		(get-last-connection-sublist input-port-sublist)))
	 (if (eq output-port-sublist
		 (connections block))
	     (setf (connections block)
		   (cdr output-port-sublist-last-connection-sublist))
	     (loop for rest-of-connection-or-name
		   on (connections block)
		   do
	       (if (eq (cdr rest-of-connection-or-name)
		       output-port-sublist)
		   (setf (cdr rest-of-connection-or-name)
			 (cdr output-port-sublist-last-connection-sublist)))))
	 (if (eq input-port-sublist
		 (connections block))
	     (setf (connections block)
		   output-port-sublist
		   (cdr output-port-sublist-last-connection-sublist)
		   input-port-sublist)
	     (loop for rest-of-connection-or-name
		   on (connections block)
		   do
	       (if (eq (cdr rest-of-connection-or-name)
		       input-port-sublist)
		   (setf (cdr rest-of-connection-or-name)
			 output-port-sublist
			 (cdr output-port-sublist-last-connection-sublist)
			 input-port-sublist))))
	 (setf (car output-port-sublist-last-connection-sublist)
	       new-connection
	       (car input-port-sublist-last-connection-sublist)
	       new-connection))
       ;; special case of both ends of connection being attached to same block
       ;; remove `connection-to-be-replaced', duplicate `new-connection'.
       #+connections-v2
       (let* ((output-port-connection
	        (if (eq (input-end-object connection-to-be-replaced) block)
		    connection-to-be-replaced
		    new-connection))
	      (input-port-connection
	        (if (eq output-port-connection connection-to-be-replaced)
		    new-connection
		    connection-to-be-replaced)))
	 (let* ((connection-item (get-connection-item connection-to-be-replaced
						      (connections block)))
		(old-single-item (get-connection-item new-connection (connections block))))
	   #+development
	   (when (connection-item-duplicated? old-single-item)
	     (error "impossible: the new connection is already duplicated?!"))
	   (setf (connection-item-duplicated? old-single-item) t)

	   #+development
	   (when (or (and (eq input-port-connection new-connection)
			  (connection-item-output-names old-single-item))
		     (and (eq output-port-connection new-connection)
			  (connection-item-input-names old-single-item)))
	     (error "impossible: the target names is not empty"))
	   ;; move port names to new-connection
	   (if (eq input-port-connection new-connection)
	       (setf (connection-item-output-names old-single-item)
		     (connection-item-output-names connection-item))
	       (setf (connection-item-input-names old-single-item)
		     (connection-item-input-names connection-item)))

	   #+development
	   (when connection-to-be-replaced-duplicated?
	     (error "impossible: connection to be replaces is duplicated?1"))
	   (setf (get-connection-item connection-to-be-replaced (connections block)) nil)
	   (delete-connection-item connection-to-be-replaced (connections block))
	   (reclaim-connection-item connection-item))))

      #-connections-v2
      (connection-to-be-replaced-duplicated? ; if entry exists twice, both get replaced
       (let* ((output-port-connection-sublist
		(memq connection-to-be-replaced (connections block)))
	      (input-port-connection-sublist
		(memq connection-to-be-replaced 
		      (cdr output-port-connection-sublist))))
	 (loop for rest-of-connection-or-name
	       on (connections block)
	       do
	   (if (eq (input-end-object new-connection) block)
	       (if (eq rest-of-connection-or-name output-port-connection-sublist)
		   (setf (car rest-of-connection-or-name)
			 new-connection))
	       (if (eq rest-of-connection-or-name input-port-connection-sublist)
		   (setf (car rest-of-connection-or-name)
			 new-connection))))))
      (t
       #-connections-v2
       (loop for rest-of-connection-or-name
	     on (connections block)
	     as connection-or-name
	     = (car rest-of-connection-or-name)
	     doing (if (and (connection-p connection-or-name)
			    (eq connection-or-name
				connection-to-be-replaced))
		       (setf (car rest-of-connection-or-name)
			     new-connection)))
       #+connections-v2
       (let* ((connection-item-table (connections block))
	      (connection-item
	       (get-connection-item connection-to-be-replaced connection-item-table)))
	 ;; remove old connection item
	 (setf (get-connection-item connection-to-be-replaced connection-item-table) nil)
	 (delete-connection-item connection-to-be-replaced connection-item-table)
	 ;; re-use exist connection item structure
	 (setf (connection-item-connection connection-item) new-connection)
	 ;; add new connection item
	 (setf (get-connection-item new-connection connection-item-table)
	       connection-item)))))

  (update-runtime-structures-according-to-edit block)
  (update-runtime-structures-according-to-edit connection-to-be-replaced)
  (update-runtime-structures-according-to-edit new-connection)
  (flush-subworkspace-connection-posts-for-object 
    connection-to-be-replaced block nil)
  (determine-subworkspace-connection-posts-for-object
    new-connection block))

;; Note that decache-roles-for-entities-related-to-this-connection must
;; be called before the change since it decaches based on the old
;; connectivity.  Update-runtime-structures-according-to-edit and
;; determine-subworkspace-connection-posts-for-object must be called
;; after the change since they may do installation which should be based
;; on the new connectivity.



;;; Get-connections-sublist-for-connections takes as arguments a block
;;; and a connection and returns the sublist of (connections block)
;;; beginning with the first name for the connections.

#-connections-v2 ; disable all list-based helpers
(defun get-connections-sublist-for-connection (block connection)
  (get-connections-sublist-for-connection-1 (connections block) connection))

#-connections-v2 ; disable all list-based helpers
(defun get-connections-sublist-for-connection-1 (connections-list connection)
  (loop named search-for-connection-sublist
	with sublist-being-considered
	  = connections-list
	while sublist-being-considered
	do
    (loop for rest-of-names
	      on sublist-being-considered
	  as connection?
	     = (car rest-of-names)
	  until (connection-p connection?)
	  finally
	    (if (eq connection? connection)
		(return-from search-for-connection-sublist
		  sublist-being-considered)
		(setq sublist-being-considered
		      (cdr rest-of-names))))))

#-connections-v2 ; disable all list-based helpers
(defun get-last-connection-sublist (sublist)
  (loop for rest-of-names
	    on sublist
	do 
    (if (connection-p (car rest-of-names))
	(return rest-of-names))))

;;; NOTE: in this function, a null optional `input-or-output' doesn't indicate
;;; "output or undirected connections", instead it indicate either input or output
;;; connections! -- Chun Tian (binghe), Aug 2015.

(defun get-port-name-given-block-and-connection
       (block connection &optional input-or-output)
  #+development
  (unless (connection-connected-to-block-p connection block)
    (error "impossible: block is not connected yet?!"))
  #-connections-v2
  (let ((portname-or-connection
	  (case input-or-output
	    (input
	     (car (get-connections-sublist-for-input-connection
		    block connection)))
	    (t					       ; output or nil
	     (car (get-connections-sublist-for-output-connection
		    block connection))))))
    (when (symbolp portname-or-connection) portname-or-connection))
  #+connections-v2
  (let* ((connection-item
	  (get-connection-item connection (connections block)))
	 (names
	  (case input-or-output
	    (input
	     (connection-item-input-names connection-item))
	    (output
	     (connection-item-output-names connection-item))
	    (t
	     (or (connection-item-output-names connection-item)
		 (connection-item-input-names connection-item))))))
    (first names)))

#-connections-v2 ; disable all list-based helpers
(defun get-connections-sublist-for-output-connection (block connection)
  (get-connections-sublist-for-connection block connection))

#-connections-v2 ; disable all list-based helpers
(defun get-connections-sublist-for-input-connection (block connection)
  (let* ((connections-sublist
	   (get-connections-sublist-for-connection block connection))
	 (next-sublist
	   (loop for rest-of-list on connections-sublist
		 do (when (eq (car rest-of-list) connection)
		      (return (cdr rest-of-list))))))
    (or (get-connections-sublist-for-connection-1 next-sublist connection)
	connections-sublist)))

;;; `Add-connection-in-block' takes a block and a connection to be added as
;;; arguments.  If the connection already exists in the connections slot of the
;;; block, then it is put in the appropriate format as described above.  In
;;; order for this to work correctly, it is necessary that the new end
;;; information not yet be on the connection (so that the block is not yet at
;;; both ends).  There is currently no way of supplying a port name for the
;;; connection to be added.

(defun add-connection-in-block
       (block connection-to-be-added)
  (note-change-to-block block 'connections)
  (decache-roles-for-entities-related-to-this-connection
    connection-to-be-added)
  (cond 
    ((connection-exist-p connection-to-be-added (connections block))
     ;; special case of both ends of connection being
     ;; attached to same block
     #-connections-v2
     (let* ((port-sublist
	      (get-connections-sublist-for-connection
		block connection-to-be-added))
	    (port-sublist-last-connection-sublist
	      (get-last-connection-sublist port-sublist)))
       (cond
	 ((eq (input-end-object connection-to-be-added) block)
	  ;; if connection already in slot corresponds to output port,
	  ;; put connection-to-be-added after this, else before.
	  (setf (cdr port-sublist-last-connection-sublist)
		(slot-value-cons connection-to-be-added
				 (cdr port-sublist-last-connection-sublist))))
	 (t
	  (if (eq port-sublist (connections block))
	      (setf (connections block)
		    (slot-value-cons connection-to-be-added
				     (connections block)))
	      (loop for rest-of-connection-or-name
			on (connections block)
		    do
		(if (eq (cdr rest-of-connection-or-name)
			port-sublist)
		    (setf (cdr rest-of-connection-or-name)
			  (slot-value-cons connection-to-be-added
				(cdr rest-of-connection-or-name)))))))))
     #+connections-v2
     (let ((connection-item
	    (get-connection-item connection-to-be-added (connections block))))
       #+development
       (when (connection-item-duplicated? connection-item)
	 (error "impossible: connection-to-be-added is already duplicated?!"))
       (setf (connection-item-duplicated? connection-item) t)))

    (t
     #-connections-v2
     (setf (connections block)
	   (slot-value-cons connection-to-be-added (connections block)))
     #+connections-v2
     (if (connections block)
	 (setf (get-connection-item connection-to-be-added (connections block))
	       (make-connection-item connection-to-be-added))
       (setf (connections block)
	     (let ((connection-table (make-connection-item-table))
		   (connection-item (make-connection-item connection-to-be-added)))
	       (setf (get-connection-item connection-to-be-added connection-table)
		     connection-item)
	       connection-table)))))

  ;; Maintain cached layer positions.
  (let ((workspace? (get-workspace-if-any block)))
    (when workspace?
      (invalidate-layer-positions workspace?)))
  (update-runtime-structures-according-to-edit block)
  (update-runtime-structures-according-to-edit connection-to-be-added)
  (determine-subworkspace-connection-posts-for-object
    connection-to-be-added block))



;;; `Delete-connection-in-block' takes a block and a connection to be deleted.
;;; The connection to be deleted must be in the connections slot of the entity
;;; or nothing will happen.  If the connection has a name or names in the
;;; connections slot, the names will be deleted as well.

(defun delete-connection-in-block
    (block connection-to-be-deleted remove-subworkspace-connection-posts-if-appropriate?)
  (note-change-to-block block 'connections)
  (decache-roles-for-entities-related-to-this-connection
    connection-to-be-deleted)

  ;; The let* form below can be replaced by this call, I believe. -fmw, 12/26/01
  ;; (reclaim-slot-value-list
  ;;   (excise-connection-sublist-from-connections block connection-to-be-deleted))
  #-connections-v2
  (let* ((replacement-sublist? nil)
	 (sublist-to-be-replaced?
	   (loop named search
		 with sublist-being-considered = (connections block)
		 while sublist-being-considered
		 do
	     (loop for rest-of-names
		   on sublist-being-considered
		   as connection?
		      = (car rest-of-names)
		   until (connection-p connection?)
		   finally
		     (cond
		       ((eq connection? connection-to-be-deleted)
			(setq replacement-sublist?
			      (cdr rest-of-names))
			(return-from search sublist-being-considered))
		       (t 
			(setq sublist-being-considered
			      (cdr rest-of-names))))))))

    (when sublist-to-be-replaced?
      (if (eq sublist-to-be-replaced?
	      (connections block))
	  (setf (connections block)
		replacement-sublist?)
	  (loop for sublist-being-considered
		on (connections block)
		doing
	    (if (eq (cdr sublist-being-considered)
		    sublist-to-be-replaced?)
		(setf (cdr sublist-being-considered)
		      replacement-sublist?))))
      (loop for sublist-not-to-delete?
	    on sublist-to-be-replaced?
	    do (if (eq (cdr sublist-not-to-delete?)
		       replacement-sublist?)
		   (setf (cdr sublist-not-to-delete?) nil)))
      (reclaim-slot-value-list sublist-to-be-replaced?)))
  #+connections-v2
  (when-let* ((connection-item-table (connections block))
	      (connection-item
	       (get-connection-item connection-to-be-deleted connection-item-table)))
    (setf (get-connection-item connection-to-be-deleted connection-item-table) nil)
    (delete-connection-item connection-to-be-deleted connection-item-table)
    (reclaim-connection-item connection-item))

  (update-runtime-structures-according-to-edit block)
  (update-runtime-structures-according-to-edit connection-to-be-deleted)
  (flush-subworkspace-connection-posts-for-object
    connection-to-be-deleted
    block
    remove-subworkspace-connection-posts-if-appropriate?))


;; Note that the connection itself is not reclaimed here.
;; This is done elsewhere.


;;; The function `excise-connection-sublist-from-block' excises and returns the
;;; sublist ({name1}... {nameN} connection) from the connections list for block,
;;; if present.

;;; In support of reclaim-bad-connections-of-block, we allow for the possibility
;;; that the connection is actually in a reclaimed state, and does not satisfy
;;; connection-p.  So to be precise, this function excises the first longest
;;; sublist L where (EQ connection (car (last L))) and (every #'symbolp (butlast
;;; L)) is true.

#-connections-v2
(defun excise-connection-sublist-from-block (block connection)
  (loop for cons-before-sublist = nil
				then sublist-last-cons
	for sublist-cons = (connections block)
			 then (cdr sublist-last-cons)
	while sublist-cons
	for sublist-last-cons = (loop for cons on sublist-cons
				      until (not (symbolp (car cons)))
				      finally (return cons))
	while sublist-last-cons
	;; At this point, sublist-cons and sublist-last-cons delimit a connection
	;; and its port-names (if any) in the list.
	when (eq connection (car sublist-last-cons))
	  do (if cons-before-sublist
		 (setf (cdr cons-before-sublist) (cdr sublist-last-cons))
		 (setf (connections block) (cdr sublist-last-cons)))
	     (setf (cdr sublist-last-cons) nil)
	     (return sublist-cons)))

;; Note does not reclaim anything.

;;; The function `lower-connection-frame-to-bottom' moves given connection-frame
;;; to the end of the list of connections on its input-end object.

;;; For connections-v2, there's no connection orders any more, so it's disabled.
;;; NOTE: it's only called by `lower-block-to-bottom' in DRAW. --binghe

(defun lower-connection-frame-to-bottom (connection-frame)
  #+connections-v2
  (declare (ignore connection-frame))
  #-connections-v2
  (let ((connection? (connection-for-this-connection-frame connection-frame)))
    (when connection?
      (let* ((input-end-block (input-end-object connection?))
	     (output-sublist-for-block
	       (excise-connection-sublist-from-block input-end-block connection?))
	     (input-sublist-for-block
	       (excise-connection-sublist-from-block input-end-block connection?)))
	(setf (connections input-end-block)
	      (nconc (connections input-end-block)
		     output-sublist-for-block
		     input-sublist-for-block))
	(let ((superblock? (superblock? input-end-block)))
	  (when (workspace-p superblock?)
	    (update-connection-images-1 nil superblock? connection?)
	    (when (ws-has-ws-representation-p superblock?)
	      (send-ws-representations-item-layer-change
		connection-frame
		superblock?
		(find-connection-or-block-below-this-connection
		  connection? input-end-block)))
	    (note-change-to-workspace-geometry superblock?)
	    (invalidate-layer-positions superblock?)))))))

;;; `Get-block-at-other-end-of-connection' takes a connection and a block
;;; and returns the block at the other end.

(defun get-block-at-other-end-of-connection (connection block)
  (if (eq (input-end-object connection) block)
      (output-end-object connection)
      (input-end-object connection)))

(defun connection-connected-to-block-p (connection block)
  (or (eq block (input-end-object connection))
      (eq block (output-end-object connection))))

;; This could also be implemented to check if the connection is in the connections
;; slot of the block but this is faster.

(defun get-direction-of-connection 
       (connection block &optional even-if-not-directed?)
  (if (or (connection-directed? connection)
	  even-if-not-directed?)
      (if (eq (input-end-object connection) block)
	  'output
	  'input)
      nil))

(defun get-style-of-connection (connection)
  (if (connection-diagonal-p connection)
      'diagonal
      'orthogonal))

(defun get-position-at-this-end-of-connection (connection block)
  (if (eq (output-end-object connection) block)
      (output-end-position connection)
      (input-end-position connection)))

;; Consider implementing a function get-information-for-other-end-of-connection
;; which takes connection and block and returns the block and position at the
;; other end.


#+unused
(defun set-position-at-this-end-of-connection 
       (connection block side position-on-side)
  (if (eq (output-end-object connection) block)
      (set-output-end-of-connection connection block side position-on-side)
      (set-input-end-of-connection connection block side position-on-side)))

(defun set-input-end-of-connection (connection block side position-on-side)
  (set-input-end-of-connection-1 
    connection block
    (combine-side-and-position-on-side-for-end-position
      side position-on-side)))

(defun set-input-end-of-connection-1 (connection block end-position)
  ;pbk possible hook needed here
  (setf (input-end-object connection) block
	(input-end-position connection) end-position)
  (set-or-clear-connection-transient-if-necessary
    connection block (output-end-object connection)))

(defun set-output-end-of-connection (connection block side position-on-side)
  (set-output-end-of-connection-1
    connection block 
    (combine-side-and-position-on-side-for-end-position
      side position-on-side)))

(defun set-output-end-of-connection-1 (connection block end-position)
  (setf (output-end-object connection) block
	(output-end-position connection) end-position)
  (set-or-clear-connection-transient-if-necessary
    connection block (input-end-object connection)))

(defun set-or-clear-connection-transient-if-necessary
       (connection block1 block2)
  (when (and (framep block1) (framep block2))
    (set-or-clear-connection-transient-if-necessary-1 block1 block2)
    (set-or-clear-connection-transient-if-necessary-1 block2 block1))
  connection)  ; mark this transient as well for 2.1!

(defun set-or-clear-connection-transient-if-necessary-1
       (block-to-check block-at-other-end)
  (when (loose-end-p block-at-other-end)
    (cond
      ((transient-p block-to-check)
       (set-transient block-at-other-end))
      (t (clear-transient block-at-other-end)))))

;; Loose ends never have inferior blocks.





;;;; Changing Connection Colors


;;; There are two major modalities to color changing connections, one for solid
;;; connections, and one for striped connections.  The code for these two case
;;; is extremely similar.  They both check to assure that a change is actually
;;; necessary, normalize their color change, and use `do-color-revision'
;;; to invoke revise-connection-stripe-if-possible, which in turn will fall
;;; thru to draw-connection.



;;; `Change-color-pattern-of-connection' changes the color of a striped
;;; connection as specified by connection-color-change-pattern.  The recording
;;; of KB state changes is controlled by the second argument.  The target color
;;; pattern is specified by a list of conses each consisting of a region and
;;; color or meta-color, e.g.  (fluid . blue).  This is known as a
;;; `connection-color-change-pattern'.

(defun change-color-pattern-of-connection
    (connection-frame note-as-kb-state-change? connection-color-change-pattern)
  (loop with old-color-pattern
	  = (get-cross-section-regions
	      (cross-section-pattern connection-frame))
	with new-color-pattern
	  = (copy-tree-using-slot-value-conses
	      old-color-pattern)
	with cross-section-stripes
	  = (copy-tree-using-slot-value-conses
	      (get-cross-section-stripes
		(cross-section-pattern connection-frame)))
	with any-changes-noticed? = nil
	as (region . color-or-listed-color)		    ; after 2.0: => (region . color)!
	   in connection-color-change-pattern
	as color					    ; eliminate after 2.0!
	   = (if (atom color-or-listed-color)
		 color-or-listed-color
		 (car color-or-listed-color))
	as new-region-and-color?
	   = (assq region new-color-pattern)
	do (cond
	     ((null new-region-and-color?)
	      (warn-of-missing-color-region connection-frame region))
	     ((eq (car new-region-and-color?)		    ; (color . color), i.e. unlabeled
		  (cdr new-region-and-color?))
	      (warn-of-unnamed-color-region connection-frame region))
	     (t
	      (if (neq color (cdr new-region-and-color?))
		  (setq any-changes-noticed? t))	    ; optimization
	      (setf (cdr new-region-and-color?) color)))

	finally
	  (let* ((connection 
		   (connection-for-this-connection-frame connection-frame))
		 (workspace?
		   (superblock? (output-end-object connection)))
		 (becoming-transparent?
		   (transparent-color-pattern-p new-color-pattern))
		 (do-not-note-permanent-changes-p note-as-kb-state-change?))

	    (macrolet ((kb-update ()
			 `(progn
			    (when note-as-kb-state-change?
			      (note-kb-state-change connection-frame
						    'connection-color-pattern))
			    ;; This absorbs the two lists.
			    (change-slot-value
			      connection-frame 'cross-section-pattern
			      (make-cross-section-pattern
				new-color-pattern
				cross-section-stripes)))))
	      (cond
		((null any-changes-noticed?)
		 (reclaim-slot-value-tree new-color-pattern)
		 (reclaim-slot-value-tree cross-section-stripes))

		((appropriate-to-invalidate-color-of-block?
		   connection becoming-transparent?)
		 (kb-update)
		 ;; Note that connection-color-change-pattern still holds just
		 ;; the changed regions and colors, while new-color-pattern
		 ;; held the exhaustive list of all new colors.
		 (when workspace?
		   (let ((changed-regions
			   (loop for (region . color) in connection-color-change-pattern
				 collect region using gensym-cons)))
		     (invalidate-color-of-block workspace? connection-frame changed-regions)
		     (reclaim-gensym-list changed-regions))))

		(t
		 ;; This guy allows both frames and connection structures, but
		 ;; the connection-frame has the wrong edges.
		 (do-color-revision (connection becoming-transparent?
						(output-end-object connection))

		     (draw-connection connection new-color-pattern)
		   (kb-update))))))))



;;; `Change-color-of-connection' changes the color of the solid or striped
;;; connection whose frame is the first argument to the color or meta color
;;; given in the third argument.  The KB state change recording is controlled
;;; by the second argument.

(defun change-color-of-connection
    (connection-frame note-as-kb-state-change? new-color)
  (let ((new-cross-section-regions
	  (copy-tree-using-slot-value-conses
	    (get-cross-section-regions
	      (cross-section-pattern connection-frame))))
	(new-cross-section-stripes
	  (copy-tree-using-slot-value-conses
	    (get-cross-section-stripes
	      (cross-section-pattern connection-frame))))
	(any-changes-noticed? nil))

    ;; Stuff the new-color into ALL regions.
    (loop for region-color-pair in new-cross-section-regions
	  as color = (cdr region-color-pair)
	  do (when (not (eq color new-color))
	       (setf any-changes-noticed? t
		     (cdr region-color-pair) new-color)))
    
    ;; Stuff the new-color into unnamed stripes (those which have explicit
    ;; colors).
    (loop for region-width-pair in new-cross-section-stripes
	  as region-or-color = (car region-width-pair)
	  do (when (and (not (assq region-or-color new-cross-section-regions))  ; not a region
			(not (eq region-or-color new-color)))
	       (setf any-changes-noticed? t
		     (car region-width-pair) new-color)))

    (let* ((connection 
	     (connection-for-this-connection-frame connection-frame))
	   (workspace?
	     (superblock? (output-end-object connection)))
	   (becoming-transparent?
	     (transparent-color-p new-color))
	   (do-not-note-permanent-changes-p note-as-kb-state-change?))

      (macrolet ((kb-update ()
		   `(progn
		      (when note-as-kb-state-change?
			(note-kb-state-change connection-frame 'stripe-color))
		      (change-slot-value 
			connection-frame 'cross-section-pattern
			(make-cross-section-pattern new-cross-section-regions new-cross-section-stripes)))))
	(cond
	  ((null any-changes-noticed?)
	   (reclaim-slot-value-tree new-cross-section-regions)
	   (reclaim-slot-value-tree new-cross-section-stripes))
	  
	  ((appropriate-to-invalidate-color-of-block? connection becoming-transparent?)
	   (kb-update)
	   (when workspace?
	     (let ((changed-regions (gensym-list 'stripe-color)))
	       (invalidate-color-of-block workspace? connection-frame changed-regions)
	       (reclaim-gensym-list changed-regions))))

	  (t
	   (do-color-revision (connection becoming-transparent?
					  (output-end-object connection))
	       (draw-connection connection new-color)
	     (kb-update))))))))






;;;; Connection and Workspace Drawing Layers



;;; `Get-connection-layer-position' returns the layer position of connection, a
;;; connection structure, if any.  If connection is not on any workspace, it
;;; returns nil.  See the concept layer-position for additional information.

(defun get-connection-layer-position (connection)
  (let ((block-for-connection?
	  (input-end-object connection)))
    (when block-for-connection?
      (let ((workspace? (get-workspace-if-any block-for-connection?)))
	(when workspace?
	  (ensure-layer-positions workspace?)
	  (layer-position-of-connection connection))))))





;;;; Drawing Connections


;;; Computations for drawing connections are, in general, done in image units 
;;; rather than workspace units, in order to avoid scaling problems.


;;; `Draw-connections-for-block' is called from draw methods for blocks.  All
;;; output connections of the block will be drawn.  Thus, when a schematic on a
;;; workspace is being drawn, each connection for each block will be drawn
;;; exactly once.  Since this draw method is invoked via update-images, there
;;; is no need to use update-images here.  If the block is in XOR, then
;;; the connections inherit that attribute, and their drawing is deferred.

(defun draw-connections-for-block (block)
  (loop for connection being the output-connections of block
	do (draw-connection connection nil)))

;;; `Collect-output-connections-for-block' is used, in development, to
;;; collect the connections drawn below a given block.

#+development
(defun collect-output-connections-for-block (block)
  (loop for connection being the output-connections of block
	collect connection))


#+unused
(defun output-connection-of-block-p (the-connection block)
  (loop for connection being the output-connections of block
	thereis (eq the-connection connection)))



(defun update-connection-images (erase? workspace? connection)
  (when workspace?
    (update-connection-images-1 erase? workspace? connection))
  (unless erase?
    (recompute-selection-highlights connection)))


;; Changed local variable name above from erase-instead? to erase? to prevent
;; special variable binding.  (MHD 4/12/91)

(defun update-connection-images-1 (erase? workspace connection)
  (when (image-planes-this-is-on workspace)	; Optimization: NIL during KB-load.
    (with-extreme-edges-minimizing-workspace (workspace) 
      (update-extreme-edges-from-connection connection)
      (let ((bleeding-hack :connection-bleeding))
	(update-images
	  erase? connection workspace
	  extreme-left-edge-so-far
	  extreme-top-edge-so-far
	  extreme-right-edge-so-far
	  extreme-bottom-edge-so-far
	  bleeding-hack
	  'draw-connection connection nil)))))

;; The unspecified workspace clipping can't stand for long. -- ben 6/23/93

;; The bleeding hack can not be supressed since connections can easily bleed
;; at small scales.   -- ben 6/23/93

;; Note A: In fact, diagonal connection sometimes bleed by more than 1 pixel,
;; hence the binding of size-of-bleeding-overflow. Also conditionally bound in
;; update-images-of-blocks-and-connections-being-moved -fmw, 9/15/94




;;; `Connection-subrectangle-structures' are allocated in each KB for the
;;; individual strips found in various connection classes.  They reside within
;;; the `connection-subrectangle-structures-for-drawing' property of the class.
;;; Effectively, these are the tiny little paint brushes used to render each
;;; strip.  When used to in a given drawing operation they are scaled, offset
;;; and colored correctly for that rendering of the connection on the given
;;; image-plane.  They could be dynamically allocated within each drawing
;;; operation, and they are reinitialized by in the setup of draw-connection
;;; (see `initialize-connection-subrectangle-structures').

;;; For each strip in the connection they record the actual and scaled widths.
;;; Recall that the scaled X and Y maybe different.  The background color value,
;;; and foreground color difference are computed for each draw operation.
;;; Something I don't comprehend involving the axis position is also recorded,
;;; maybe this is the offset of the strip from the center line of the
;;; connection.

;; -- ben 6/30/93

(def-structure (connection-subrectangle-structure
		 (:constructor
		   make-connection-subrectangle-structure 
		   (subrectangle-width)))
  (subrectangle-color-difference nil)
  (subrectangle-background-color-value nil)
  (subrectangle-width nil)
  (subrectangle-scaled-x-width nil)
  (subrectangle-scaled-y-width nil)
  (variable-axis-begin-position nil)
  (variable-axis-end-position nil)
  (stable-axis-position nil))


(def-system-variable minimum-distance-between-fins connect2 50)

(def-system-variable desired-distance-between-fins connect2 100)

(def-system-variable desired-distance-between-fins-on-link connect2 300)

;; Note that desired-distance-between-fins-on-link is much larger than
;; desired-distance-between-fins.  Thus, while fins will in general
;; be spaced at a distance of 100, they will be no closer than 300 if
;; they are on the same link.  This improves appearance substantially.


(def-substitution-macro new-connection-p (connection)
  (or (connection-diagonal-p connection)
      (connection-line-pattern connection)
      (connection-has-arrows-p connection)))

;;; The substitution-macro `new-draw-connection-p' determines when we use the
;;; "new" connection drawing routine.

(def-substitution-macro new-draw-connection-p (gensym-window connection)
  (and (current-window-supports-wide-polyline gensym-window)
       (new-connection-p connection)
       (not (buggy-polyline-p))))


(def-system-variable default-fin-length connect2 10)
;; Actually, (* fin-length (/ (sqrt 2) 2)))

;;; The function `connection-fin-length' returns the desired length (actually
;;; the length of the projection onto the line segment) of fins and arrows, in
;;; workspace units. Arrows scale a bit with the connection's width, which looks
;;; better.

(defun connection-fin-length (connection &optional total-width?)
  (cond ((connection-has-arrows-p connection)
	 (let* ((total-width (or total-width?
				 (compute-connection-width-given-connection-frame-or-class
				   (connection-frame-or-class connection))))
		(fin-length (*f 3 total-width)))
	   (maxf fin-length default-fin-length)))
	(t
	 default-fin-length)))


(defun connection-total-width (connection)
  (let ((cross-section-stripes
	  (get-cross-section-stripes
	    (get-cross-section-pattern-given-connection-frame-or-class
	      (connection-frame-or-class connection)))))
    (loop for (color . width) in cross-section-stripes
	  summing width using +f)))


;;; `Orientation-horizontal-p' and `current-delta' define an environment for
;;; mapping from "handed" operations to workspace operations.  Note that
;;; stable-axis-position, variable-axis-begin-position, etc.  are also
;;; workspace coordinates.  The mapping is done on the operations, not on the
;;; positions.

(defvar orientation-horizontal-p)

(defvar init-orientation-horizontal-p)

(defvar current-delta)



;;; The cumulative scaled widths are computed by
;;; initialize-cumulative-scaled-widths.

(defvar cumulative-x-scaled-connection-stripe-width)
(defvar cumulative-y-scaled-connection-stripe-width)
(defvar cumulative-x-scaled-connection-stripe-half-width)
(defvar cumulative-y-scaled-connection-stripe-half-width)

(defun initialize-cumulative-scaled-widths (cross-section-stripes)
  (loop for (nil . width) in cross-section-stripes
	summing (maxr 1 (delta-x-in-window width current-image-x-scale))
	  into cumulative-x
	summing (maxr 1 (delta-y-in-window width current-image-y-scale))
	  into cumulative-y
	finally
	  (setq cumulative-x-scaled-connection-stripe-width cumulative-x
		cumulative-y-scaled-connection-stripe-width cumulative-y))
  (setq cumulative-x-scaled-connection-stripe-half-width
	(halfr cumulative-x-scaled-connection-stripe-width)
	cumulative-y-scaled-connection-stripe-half-width
	(halfr cumulative-y-scaled-connection-stripe-width)))

(def-substitution-macro scaled-subrectangle-width-given-orientation
			(subrectangle-structure)
  (if orientation-horizontal-p
      (subrectangle-scaled-y-width subrectangle-structure)
      (subrectangle-scaled-x-width subrectangle-structure)))

(def-substitution-macro delta-in-window-given-orientation
			(delta-in-workspace orientation-horizontal-p)
  (if orientation-horizontal-p
      (delta-y-in-window delta-in-workspace current-image-y-scale)
      (delta-x-in-window delta-in-workspace current-image-x-scale)))

(defmacro cumulative-scaled-width-given-orientation (orientation-horizontal-p)
  `(if ,orientation-horizontal-p
       cumulative-y-scaled-connection-stripe-width
       cumulative-x-scaled-connection-stripe-width))

(defmacro cumulative-scaled-half-width-given-orientation 
	  (orientation-horizontal-p)
  `(if ,orientation-horizontal-p
       cumulative-y-scaled-connection-stripe-half-width
       cumulative-x-scaled-connection-stripe-half-width))


;;; The following macros utilize the special variables orientation-horizontal-p
;;; and current delta to provide a layer of abstraction that hides the
;;; notion of an x and y coordinate system.  Calculations are accomplished
;;; based on whether the next turn is left or right.

(def-substitution-macro sub-rectangle-end-extended-by-width
			(subrectangle-variable-axis-end-position 
			 scaled-subrectangle-width)
  (if (>w 0 current-delta)
      (+r subrectangle-variable-axis-end-position
	  scaled-subrectangle-width)
      (-r subrectangle-variable-axis-end-position
	  scaled-subrectangle-width)))

(def-substitution-macro calculate-subrectangle-stable-axis-position-for-next-link
			(right-turn? subrectangle-variable-axis-end-position
			 scaled-subrectangle-width)
  (if right-turn?
      subrectangle-variable-axis-end-position
      (sub-rectangle-end-extended-by-width
	subrectangle-variable-axis-end-position 
	scaled-subrectangle-width)))

(def-substitution-macro calculate-next-subrectangle-variable-axis-end-position
			(subrectangle-variable-axis-end-position
			 scaled-subrectangle-width)
  (sub-rectangle-end-extended-by-width
    subrectangle-variable-axis-end-position scaled-subrectangle-width))

(def-substitution-macro delta-direction-negative? ()
  (if (>w 0 current-delta)
      orientation-horizontal-p
      (not orientation-horizontal-p)))

(def-substitution-macro subrectangle-stable-extended-by-width
			(subrectangle-stable-axis-position
			 scaled-subrectangle-width)
  (+r subrectangle-stable-axis-position
      (if (delta-direction-negative?)	  
	  (-r scaled-subrectangle-width)
	  scaled-subrectangle-width)))

(def-substitution-macro calculate-next-initial-subrectangle-stable-axis-position
			(subrectangle-stable-axis-position
			 scaled-subrectangle-width)
  (subrectangle-stable-extended-by-width 
    subrectangle-stable-axis-position scaled-subrectangle-width))

(def-substitution-macro calculate-subrectangle-variable-axis-begin-position-for-next-link
			(right-turn? subrectangle-stable-axis-position
			 scaled-subrectangle-width)
  (if (not right-turn?)
      subrectangle-stable-axis-position
      (subrectangle-stable-extended-by-width 
	subrectangle-stable-axis-position scaled-subrectangle-width)))

(def-substitution-macro right-turn-p (next-delta)
  (if (delta-direction-negative?)
      (>w 0 next-delta)
      (not (>w 0 next-delta))))


;;; `Connection-subrectangle-structures-for-drawing' is set by the slot putter for
;;; cross-section-pattern-for-connection.  It is used by draw-connection.

(def-kb-specific-property-name connection-subrectangle-structures-for-drawing
			       reclaim-connection-subrectangle-structures)

;; Consider keeping this information in the class-definition for the class 
;; rather than on a property of the class.




;;; `Generate-connection-subrectangle-structures' sets the value found on the
;;; connection-subrectangle-structures-for-drawing property.  It returns a cons
;;; of the form (forward-list . reverse-list) where forward-list is the list of
;;; subrectangle structures corresponding to the cross-section-pattern and
;;; reverse-list is its reverse.  Both are needed by draw-connection.

(defun generate-connection-subrectangle-structures (cross-section-pattern)
  (let* ((forward-list
	   (loop for (nil . width) 
		     in (get-cross-section-stripes cross-section-pattern)
		 collect (make-connection-subrectangle-structure width)
		   using connection-cons))
	 (reverse-list
	   (loop with reversed-list = nil 
		 for subrectangle-structure in forward-list
		 do (setq reversed-list
			  (connection-cons 
			    subrectangle-structure reversed-list))
		 finally (return reversed-list))))
    (connection-cons forward-list reverse-list)))

(defun reclaim-connection-subrectangle-structures 
       (connection-subrectangle-structures)
  (when connection-subrectangle-structures
    (let ((forward-list (car connection-subrectangle-structures)))
      (loop for connection-subrectangle-structure in forward-list
	    do (reclaim-connection-subrectangle-structure
		 connection-subrectangle-structure))
      (reclaim-connection-list forward-list)
      (reclaim-connection-list (cdr connection-subrectangle-structures))
      (reclaim-connection-cons connection-subrectangle-structures))))


;;; `Initialize-connection-subrectangle-structures' is called by
;;; draw-connection as it is setting up to draw the connection.
;;; It computes approprate color values, scaled widths, and axis
;;; position information for this one connection drawing.

;; - ben 6/26/92

(defun initialize-connection-subrectangle-structures
    (cross-section-regions cross-section-stripes
			   connection-subrectangle-structures
			   input-end-x-position input-end-y-position input-end-side
			   initial-delta
			   change-to-this-color-or-color-pattern?)
  (loop with input-end-x-position-in-window = (x-in-window input-end-x-position)      
	with input-end-y-position-in-window = (y-in-window input-end-y-position)
	with subrectangle-stable-axis-position
	  = (case input-end-side
	      (right 
	       (if (>r initial-delta 0)
		   (-r input-end-y-position-in-window
		       cumulative-y-scaled-connection-stripe-half-width)
		   (if (oddp cumulative-y-scaled-connection-stripe-width)
		       (+r input-end-y-position-in-window
			   cumulative-y-scaled-connection-stripe-half-width 1)
		       (+r input-end-y-position-in-window
			   cumulative-y-scaled-connection-stripe-half-width))))
	      (left 
	       (if (<r initial-delta 0)
		   (if (oddp cumulative-y-scaled-connection-stripe-width)
		       (+r input-end-y-position-in-window
			   cumulative-y-scaled-connection-stripe-half-width 1)
		       (+r input-end-y-position-in-window
			   cumulative-y-scaled-connection-stripe-half-width))
		   (-r input-end-y-position-in-window
		       cumulative-y-scaled-connection-stripe-half-width)))
	      (top 
	       (if (<r initial-delta 0)
		   (-r input-end-x-position-in-window
		       cumulative-x-scaled-connection-stripe-half-width)
		   (if (oddp cumulative-y-scaled-connection-stripe-width)
		       (+r input-end-x-position-in-window
			   cumulative-x-scaled-connection-stripe-half-width 1)
		       (+r input-end-x-position-in-window
			   cumulative-x-scaled-connection-stripe-half-width))))
	      (t				; if bottom
	       (if (>r initial-delta 0)
		   (if (oddp cumulative-x-scaled-connection-stripe-width)
		       (+r input-end-x-position-in-window
			   cumulative-x-scaled-connection-stripe-half-width 1)
		       (+r input-end-x-position-in-window
			   cumulative-x-scaled-connection-stripe-half-width))
		   (-r input-end-x-position-in-window
		       cumulative-x-scaled-connection-stripe-half-width))))
	with subrectangle-variable-axis-begin-position
	  = (case input-end-side
	      ((right left) input-end-x-position-in-window)
	      (t input-end-y-position-in-window))
	for connection-subrectangle-structure in connection-subrectangle-structures
	for (region-or-color . nil) in cross-section-stripes
	as width = (subrectangle-width connection-subrectangle-structure)

	as recorded-color = (if change-to-this-color-or-color-pattern?
				(compute-connection-stripe-color
				  region-or-color cross-section-regions)
				'background)
	as desired-color
	   = (cond
	       ((null change-to-this-color-or-color-pattern?)
		(compute-connection-stripe-color
		  region-or-color cross-section-regions))
	       ((symbolp change-to-this-color-or-color-pattern?)
		change-to-this-color-or-color-pattern?)
	       (t
		(compute-connection-stripe-color
		  region-or-color change-to-this-color-or-color-pattern?)))
	as color-difference
	   = (metacolor-difference desired-color recorded-color)
	do

    (setf (subrectangle-color-difference connection-subrectangle-structure)
	  color-difference)
    (setf (subrectangle-background-color-value connection-subrectangle-structure)
	  (map-color-or-metacolor-to-color-value recorded-color))

    (setf (stable-axis-position connection-subrectangle-structure)
	  subrectangle-stable-axis-position)
    (setf (variable-axis-begin-position connection-subrectangle-structure)
	  subrectangle-variable-axis-begin-position)
    (setf (subrectangle-scaled-x-width connection-subrectangle-structure)
	  (maxr 1 (delta-x-in-window width current-image-x-scale)))
    (setf (subrectangle-scaled-y-width connection-subrectangle-structure)
	  (maxr 1 (delta-y-in-window width current-image-y-scale)))
    (setq subrectangle-stable-axis-position
	  (calculate-next-initial-subrectangle-stable-axis-position
	    subrectangle-stable-axis-position 
	    (scaled-subrectangle-width-given-orientation 
		connection-subrectangle-structure)))))



;;; The function `adjust-next-to-last-delta' appears to be a misguided attempt
;;; to get connection ends to butt precisely with their objects.  Not only does
;;; it fail in many cases, particularly for diagonal connections, it also makes
;;; the connection bounding rectangle unpredictable in workspace coordinates,
;;; depending as it does on the parity of the scaled width (eg, (oddp
;;; cumulative-scaled-width)).

(defun-substitution-macro adjust-next-to-last-delta
    (delta last-delta orientation-horizontal-p 
	   initial-orientation-horizontal-p)
  (let ((cumulative-scaled-width 
	  (if orientation-horizontal-p
	      cumulative-x-scaled-connection-stripe-width
	      cumulative-y-scaled-connection-stripe-width)))

    (if (or (and initial-orientation-horizontal-p orientation-horizontal-p)
	    (and (not initial-orientation-horizontal-p) (not orientation-horizontal-p)))
	(if (oddp cumulative-scaled-width)
	    (if (>r delta 0)
		(+r delta 1)
		delta)
	    (if orientation-horizontal-p
		(if (<r last-delta 0)
		    (if (>r delta 0)
			delta
			(-r delta 1))
		    (if (>r delta 0)
			(+r delta 1)
			delta))
		(if (>r last-delta 0)
		    (if (>r delta 0)
			delta
			(-r delta 1))
		    (if (>r delta 0)
			(+r delta 1)
			delta))))
	delta)))

;; What problem is this trying to solve?  It introduces at least one new
;; problem: diagonal connections to the bottom of a block, coming from above,
;; hang in space by 3 pixels or so.

;; I bet that it is also responsible for the way connections jiggle back and
;; forth by one pixel while being moved.



;;; `Serve-first-connection-delta' and `serve-next-connection-delta' constitute
;;; a server mechanism similar to role servers.  It is a useful abstraction for
;;; drawing connections and a variety of other operations where sequential
;;; access to the deltas is needed.

;;; Serve-first-connection-delta returns the first delta, the second delta (or
;;; nil if there is none), stable-axis-position, variable-axis-begin-position,
;;; variable-axis-end-position, orientation-horizontal-p, and a delta 
;;; continuation to be used with serve-next-connection-delta.

(defun serve-first-connection-delta 
       (connection input-end-x input-end-y 
	output-end-x output-end-y
	initial-orientation-horizontal-p)
  (let ((delta-or-deltas?
	  (delta-or-deltas connection))
	current-delta next-delta delta-continuation
	stable-axis-position variable-axis-begin-position 
	variable-axis-end-position
	(output-end-x-in-window (x-in-window output-end-x))
	(input-end-x-in-window (x-in-window input-end-x))
	(output-end-y-in-window (y-in-window output-end-y))
	(input-end-y-in-window (y-in-window input-end-y)))
    (if initial-orientation-horizontal-p
	(setq stable-axis-position input-end-y-in-window
	      variable-axis-begin-position input-end-x-in-window)
	(setq stable-axis-position input-end-x-in-window
	      variable-axis-begin-position input-end-y-in-window))
    (cond 
      ((null delta-or-deltas?)
       (if initial-orientation-horizontal-p
	   (setq next-delta
		 (-r output-end-y-in-window
		     input-end-y-in-window)
		 current-delta
		 (adjust-next-to-last-delta
		   (-r output-end-x-in-window input-end-x-in-window)
		   next-delta
		   initial-orientation-horizontal-p
		   initial-orientation-horizontal-p))
	   (setq next-delta
		 (-r output-end-x-in-window
		     input-end-x-in-window)
		 current-delta
		 (adjust-next-to-last-delta		    ; ***
		   (-r output-end-y-in-window input-end-y-in-window)
		   next-delta
		   initial-orientation-horizontal-p
		   initial-orientation-horizontal-p)))
       (when (=r next-delta 0) (setq next-delta nil))
       (setq delta-continuation 'link-2-delta
	     variable-axis-end-position
	     (+r variable-axis-begin-position current-delta)))
      (t   ; if delta-or-deltas? is an atom or a cons with at least two elements
       (multiple-value-setq
	 (current-delta delta-continuation)
	 (compute-next-delta
	   connection
	   delta-or-deltas? (not initial-orientation-horizontal-p)
	   variable-axis-begin-position
	   0
	   stable-axis-position
	   output-end-x-in-window output-end-y-in-window))
       ;; Note here that since this is computing a delta for the first
       ;; link, it uses axis position arguments for an imaginary
       ;; link before the first one;  hence the switch in the
       ;; axis position arguments.

       (when (null current-delta) (setq current-delta 0))
       (setq variable-axis-end-position
	     (+r variable-axis-begin-position current-delta))

       (multiple-value-setq 
	 (next-delta delta-continuation)
	 (compute-next-delta 
	   connection
	   delta-continuation initial-orientation-horizontal-p 
	   stable-axis-position
	   variable-axis-begin-position
	   variable-axis-end-position
	   output-end-x-in-window output-end-y-in-window))

       ))

    (values current-delta next-delta stable-axis-position
	    variable-axis-begin-position variable-axis-end-position
	    delta-continuation)))

;; There will always be at least one delta if the connection is straight 
;; and at least two if the connection has a bend.

(defun serve-next-connection-delta 
       (connection output-end-x output-end-y 
	stable-axis-position variable-axis-end-position
	delta-continuation old-next-delta)

  #+development
  (when (null delta-continuation)
    (cerror "" "serve-next-connection-delta must always receive a non-nil value
for its delta-continuation argument"))

  (let* ((current-delta old-next-delta)
	 next-delta next-delta-continuation
	 (next-stable-axis-position variable-axis-end-position) 
	 (next-variable-axis-begin-position stable-axis-position)
	 (next-variable-axis-end-position
	   (+r next-variable-axis-begin-position current-delta))
	 (output-end-x-in-window (x-in-window output-end-x))
	 (output-end-y-in-window (y-in-window output-end-y)))
    (multiple-value-setq 
      (next-delta next-delta-continuation)
      (compute-next-delta 
	connection
	delta-continuation orientation-horizontal-p next-stable-axis-position
	next-variable-axis-begin-position next-variable-axis-end-position
	output-end-x-in-window output-end-y-in-window))
    (values current-delta next-delta next-stable-axis-position
	    next-variable-axis-begin-position next-variable-axis-end-position
	    next-delta-continuation)))

;; Orientation-horizontal-p is with regard to the current-delta link.

;; Consider updating orientation-horizontal-p within the delta server
;; mechanism.

(defun compute-next-delta
       (connection
	delta-continuation orientation-horizontal-p-arg
	next-stable-axis-position
	next-variable-axis-begin-position next-variable-axis-end-position
	output-end-x-in-window output-end-y-in-window)
  (multiple-value-bind
    (next-delta next-delta-continuation)
      (compute-next-delta-1 
	delta-continuation orientation-horizontal-p-arg next-stable-axis-position
	next-variable-axis-end-position output-end-x-in-window output-end-y-in-window)
    (when (and (connection-orthogonal-p connection)
	       next-delta-continuation)
      (multiple-value-bind
	(possible-next-delta 
	 possible-next-delta-continuation number-of-zeros-swallowed)
	  (compute-next-delta-swallowing-zeros
	    delta-continuation 
	    orientation-horizontal-p-arg
	    next-stable-axis-position
	    next-variable-axis-begin-position next-variable-axis-end-position
	    output-end-x-in-window output-end-y-in-window)
	(when (/=f number-of-zeros-swallowed 0)
	  (cond 
	    ((evenp number-of-zeros-swallowed)
	     (setq next-delta possible-next-delta
		   next-delta-continuation
		   possible-next-delta-continuation))))))
    (values next-delta next-delta-continuation)))

(defun compute-next-delta-1 
       (delta-continuation orientation-horizontal-p-arg next-stable-axis-position
	next-variable-axis-end-position output-end-x-in-window output-end-y-in-window)
  (let (next-delta next-delta-continuation)
    (cond 
      ((eq delta-continuation 'link-2-delta)	       ; last link
       (setq next-delta nil
	     next-delta-continuation nil))
      ((eq delta-continuation 'link-1-delta)	       ; next to last link
       (setq next-delta
	     (compute-delta-from-end-position
	       orientation-horizontal-p-arg next-stable-axis-position
	       output-end-x-in-window output-end-y-in-window))
       (when (=r next-delta 0) (setq next-delta nil))
       (setq next-delta-continuation 'link-2-delta))
      ((eq delta-continuation 'link-0-delta)	       ; next to next to last link
       (setq next-delta
	     (compute-delta-from-end-position-link-1
	       orientation-horizontal-p-arg next-stable-axis-position
	       next-variable-axis-end-position 
	       output-end-x-in-window output-end-y-in-window))
       (setq next-delta-continuation 'link-1-delta))
      ((atom delta-continuation)  ; number (case of only one delta)
       (setq next-delta 
	     (delta-in-window-given-orientation
	       delta-continuation orientation-horizontal-p-arg)
	     next-delta-continuation 'link-0-delta))
      (t					       ; delta-continuation is a cons
       (setq next-delta 
	     (delta-in-window-given-orientation
	       (car delta-continuation) orientation-horizontal-p-arg))
       (setq next-delta-continuation 
	     (or (cdr delta-continuation)
		 'link-0-delta))))
    (values next-delta next-delta-continuation)))

(defun compute-next-delta-swallowing-zeros 
       (next-delta-continuation orientation-horizontal-p-arg next-stable-axis-position
	next-variable-axis-begin-position next-variable-axis-end-position
	output-end-x-in-window output-end-y-in-window)
  (loop with zeros-to-swallow? = t
	with next-delta
	for number-of-zeros-swallowed from 0
	do
    (multiple-value-setq
      (next-delta next-delta-continuation)
      (compute-next-delta-1 
	next-delta-continuation orientation-horizontal-p-arg next-stable-axis-position
	next-variable-axis-end-position output-end-x-in-window output-end-y-in-window))
    (when (not (and next-delta
		    (=r next-delta 0)))
      (setq zeros-to-swallow? nil))

	while (and next-delta-continuation zeros-to-swallow?)
	do
	(psetq next-stable-axis-position next-variable-axis-end-position
	       next-variable-axis-begin-position next-stable-axis-position)
	(setq next-variable-axis-end-position next-variable-axis-begin-position
	      orientation-horizontal-p-arg (not orientation-horizontal-p-arg))
	finally
	  (return (values next-delta next-delta-continuation number-of-zeros-swallowed))))

(defun compute-delta-from-end-position
       (orientation-horizontal-p-arg next-stable-axis-position
	output-end-x-in-window output-end-y-in-window)
  (if orientation-horizontal-p-arg
      (-r output-end-y-in-window next-stable-axis-position)
      (-r output-end-x-in-window next-stable-axis-position)))

(defun compute-delta-from-end-position-link-1
       (orientation-horizontal-p-arg next-stable-axis-position
	next-variable-axis-end-position output-end-x-in-window output-end-y-in-window)
  (let (delta next-delta)
    (if orientation-horizontal-p-arg
	(setq delta (-r output-end-y-in-window next-stable-axis-position)
	      next-delta (-r output-end-x-in-window next-variable-axis-end-position))
	(setq delta (-r output-end-x-in-window next-stable-axis-position)
	      next-delta (-r output-end-y-in-window next-variable-axis-end-position)))
    (adjust-next-to-last-delta
      delta next-delta
      (not orientation-horizontal-p-arg) init-orientation-horizontal-p)))


;;;; Connection Drawing



;;; `Draw-connection' takes a connection as an argument.  It assumes that
;;; the connection always has an output-end-object and an input-end-object.
;;; Drawing is done from the output-end-object to the input-end-object using
;;; the delta-or-deltas of the connection.  It is  assumed that the last
;;; two deltas are omitted, they are calculated using the input-end-object.

;;; A second argument may be provided to trigger a change in the color of a
;;; connection already drawn.  This argument may be NIL, to indicate no change
;;; and that the connection is to be drawn from scratch.  It may be a color when
;;; the connection is not striped, the connection will be changed to have that
;;; color.  It maybe a list of cons each consisting of a strip name and a color
;;; (i.e. (<strip> . <color>).

;; - ben 6/26/93

(def-system-variable global-draw-diagonally? CONNECT3 nil) ; Obsolete? -fmw, 1/10/02

(defun draw-connection (connection change-to-this-color-or-color-pattern?)
  (let ((connection-frame-or-class
	  (connection-frame-or-class connection)))
    (when (or (framep connection-frame-or-class)
	      (class-description connection-frame-or-class))
      (cond
	((render-connection-in-xor-overlay-p connection)
	 ;; Can't move framep test inside due to the nature of
	 ;; with-deferred-xor-drawing.
	 (if (framep connection)
	     (with-deferred-xor-drawing
	       (draw-connection-frame-in-xor
		 connection
		 (frame-serial-number connection)
		 change-to-this-color-or-color-pattern?))
	     (with-deferred-xor-drawing
	       (draw-connection-structure-in-xor
		 connection
		 (frame-serial-number-for-connection connection)
		 change-to-this-color-or-color-pattern?))))
	(t
	 (draw-connection-1 connection change-to-this-color-or-color-pattern?)))))
  connection)

;; Why must we consider connection frames separately?  Is it ever possible that
;; the connection-frame is recycled, but the connection structure is not?


(defun-simple draw-connection-structure-in-xor (connection
						 reference-frame-serial-number
						 change-to-this-color-or-color-pattern?)
  (when (connection-has-not-been-reprocessed-p connection reference-frame-serial-number)
    (draw-connection-1 connection change-to-this-color-or-color-pattern?)))

(defun-simple draw-connection-frame-in-xor (connection
					     reference-frame-serial-number
					     change-to-this-color-or-color-pattern?)
  (when (frame-has-not-been-reprocessed-p connection reference-frame-serial-number)
    (draw-connection-1 connection change-to-this-color-or-color-pattern?)))



;;; The function `buggy-polyline-p' avoids all calls to wide-polyline if true.
;;; This forces the old way of drawing thin diagonal connections.  It's mostly
;;; paranoia for 6.2, since there is otherwise no way to revert to the old
;;; drawing code in this case.  Some PC graphics cards, for example the Nvidia
;;; Riva TNT 64 in the PC on my desk, have problems drawing polylines in XOR.
;;; Rather than forcing users to turn off hardware acceleration, I added this
;;; bogus environment variable. -fmw, 6/8/02

(defvar buggy-polyline-p 'pending)

(defun buggy-polyline-p ()
  (when (eq buggy-polyline-p 'pending)
    (setq buggy-polyline-p
	  (get-gensym-environment-variable #w"G2_BUGGY_POLYLINE")))
  buggy-polyline-p)


;;; The function `draw-connection-1' dispatches to the old drawing code for
;;; unpatterned orthogonal connections, or for old telewindows.

;changed in Gensym-320: added call to the new-draw-connection-wrapper
(defun draw-connection-1 (connection change-to-this-color-or-color-pattern?)
  (cond ((new-draw-connection-p current-window connection)
	 (new-draw-connection-wrapper connection change-to-this-color-or-color-pattern?))
	(t
	 (old-draw-connection connection change-to-this-color-or-color-pattern?))))
;end of changes

;;; The function `old-draw-connection' is the old function for drawing
;;; connections. It is highly efficient and accurate for orthogonal connections,
;;; but basically punts on diagonal connections (it ignores their cross section
;;; pattern).  It also ignores the line pattern.

(defun old-draw-connection (connection change-to-this-color-or-color-pattern?)
  (with-connection 
      connection t t t
      ((connection-frame-or-class
	 (connection-frame-or-class connection))
       (cross-section-pattern
	 (get-cross-section-pattern-given-connection-frame-or-class
	   connection-frame-or-class))
       (cross-section-regions
	 (get-cross-section-regions cross-section-pattern))
       (cross-section-stripes
	 (get-cross-section-stripes cross-section-pattern))
       (draw-diagonally?
	 (or global-draw-diagonally?
	     (connection-diagonal-p connection)))
       (fin-length
	 (connection-fin-length connection))
       cumulative-x-scaled-connection-stripe-width
       cumulative-y-scaled-connection-stripe-width
       cumulative-x-scaled-connection-stripe-half-width
       cumulative-y-scaled-connection-stripe-half-width)

    (loop with init-orientation-horizontal-p = initial-orientation-horizontal-p
	  with stable-axis-position
	  and variable-axis-begin-position
	  and variable-axis-end-position
	  and delta-continuation
	  and current-delta and next-delta and right-turn?
	  and orientation-horizontal-p
	  with previous-turn? = nil
	  with distance-from-last-fin = 0
	  with any-fins-drawn? = nil
	  with forward-and-reverse-subrectangle-structures
	    = (let ((connection-class
		      (get-connection-class-given-connection-frame-or-class
			connection-frame-or-class)))
		(or (connection-subrectangle-structures-for-drawing
		      connection-class)
		    (setf (connection-subrectangle-structures-for-drawing
			    connection-class)
			  (generate-connection-subrectangle-structures
			    cross-section-pattern))))
	  with connection-subrectangle-structures
	    = (car forward-and-reverse-subrectangle-structures)
	  with reverse-connection-subrectangle-structures
	    = (cdr forward-and-reverse-subrectangle-structures)
	  with left-most-subrectangle-structure
	    = (car connection-subrectangle-structures)
	  with draw-fins?
	    = (connection-has-classic-fins-p connection)
	  with vertex-x and vertex-y	; only used if drawing diagonally
	  initially
	    (initialize-cumulative-scaled-widths cross-section-stripes)
	    (multiple-value-setq
		(current-delta next-delta 
			       stable-axis-position
			       variable-axis-begin-position
			       variable-axis-end-position
			       delta-continuation)
	      (serve-first-connection-delta
		connection input-end-x-position input-end-y-position
		output-end-x-position output-end-y-position
		initial-orientation-horizontal-p))
	    (setq orientation-horizontal-p ; if nil, then vertical
		  initial-orientation-horizontal-p)
	    (initialize-connection-subrectangle-structures
	      cross-section-regions cross-section-stripes
	      connection-subrectangle-structures
	      input-end-x-position input-end-y-position input-end-side
	      current-delta
	      change-to-this-color-or-color-pattern?)
	    (when draw-diagonally?
	      (setq vertex-x (x-in-window input-end-x-position)
		    vertex-y (y-in-window input-end-y-position)))
	  as initial-delta-p 
	     = t
	     then nil
	  as next-x-and-y-vertex-available?
	     = t then (not next-x-and-y-vertex-available?)

	  until (null next-delta)

	  do 
      (setq right-turn? (right-turn-p next-delta))
      
      (setq distance-from-last-fin
	    (+r distance-from-last-fin (absr current-delta)))

      (cond
	(draw-diagonally?
	 (when next-x-and-y-vertex-available?
	   (multiple-value-setq 
	       (vertex-x vertex-y)
	     (compute-new-vertex-and-draw-diagonal-link 
	       vertex-x vertex-y orientation-horizontal-p 
	       current-delta next-delta connection-subrectangle-structures
	       draw-fins? fin-length))))
	(t
	 (if (not (=r current-delta 0))
	     (progn
	       (if draw-fins?
		   (if (>r distance-from-last-fin
			   (delta-in-window-given-orientation
			     desired-distance-between-fins
			     orientation-horizontal-p))
		       (setq distance-from-last-fin
			     (draw-fins-for-connection-component
			       current-delta orientation-horizontal-p
			       left-most-subrectangle-structure
			       variable-axis-begin-position
			       (cumulative-scaled-width-given-orientation 
				 orientation-horizontal-p)
			       fin-length)
			     any-fins-drawn? t)))
	       (draw-connection-subrectangles
		 (if right-turn?
		     connection-subrectangle-structures
		     reverse-connection-subrectangle-structures)
		 right-turn? previous-turn? nil
		 next-delta initial-delta-p variable-axis-end-position))
	     
	     (if initial-delta-p	; if initial delta is 0
		 (loop with subrectangle-stable-axis-position
			 = (let* ((cumulative-scaled-half-width
				    (cumulative-scaled-half-width-given-orientation
				      initial-orientation-horizontal-p))
				  (stable-axis-position-offset
				    (if (oddp (cumulative-scaled-width-given-orientation
						initial-orientation-horizontal-p))
					cumulative-scaled-half-width
					(-w cumulative-scaled-half-width 1)))
				  (orientation-horizontal-p
				    initial-orientation-horizontal-p))
			     (+r variable-axis-begin-position
				 (if initial-orientation-horizontal-p
				     (if (>r next-delta 1)
					 stable-axis-position-offset
					 (-r stable-axis-position-offset))
				     (if (>r next-delta 1)
					 (-r stable-axis-position-offset)
					 stable-axis-position-offset))))
		       for connection-subrectangle-structure
			   in connection-subrectangle-structures
		       as next-stable-axis-position
			  = (if initial-orientation-horizontal-p
				(if (>r next-delta 1)
				    (-r subrectangle-stable-axis-position
					(scaled-subrectangle-width-given-orientation
					  connection-subrectangle-structure))
				    (+r subrectangle-stable-axis-position
					(scaled-subrectangle-width-given-orientation
					  connection-subrectangle-structure)))
				(if (>r next-delta 1)
				    (+r subrectangle-stable-axis-position
					(scaled-subrectangle-width-given-orientation
					  connection-subrectangle-structure))
				    (-r subrectangle-stable-axis-position
					(scaled-subrectangle-width-given-orientation
					  connection-subrectangle-structure))))
		       do
		   (psetf (stable-axis-position
			    connection-subrectangle-structure)
			  subrectangle-stable-axis-position
			  (variable-axis-begin-position
			    connection-subrectangle-structure)
			  stable-axis-position)
		   (setq subrectangle-stable-axis-position
			 next-stable-axis-position))))))
      
      (setq previous-turn?
	    (if (=r current-delta 0)
		nil
		(if right-turn? 'right 'left))
	    orientation-horizontal-p (not orientation-horizontal-p))

      (multiple-value-setq
	  (current-delta next-delta 
			 stable-axis-position
			 variable-axis-begin-position
			 variable-axis-end-position
			 delta-continuation)
	(serve-next-connection-delta
	  connection output-end-x-position output-end-y-position
	  stable-axis-position
	  variable-axis-end-position
	  delta-continuation next-delta))
      
	  finally
	    ;; draw last component

	    (cond
	      (draw-diagonally?
	       (when next-x-and-y-vertex-available?
		 (compute-new-vertex-and-draw-diagonal-link 
		   vertex-x vertex-y orientation-horizontal-p 
		   current-delta 0 connection-subrectangle-structures
		   draw-fins? fin-length)))
	      (t
	       (if (not (=r current-delta 0))
		   (draw-connection-subrectangles
		     connection-subrectangle-structures
		     right-turn? previous-turn? t
		     next-delta initial-delta-p variable-axis-end-position))
	       (setq distance-from-last-fin
		     (+r distance-from-last-fin (absr current-delta)))
	       (if draw-fins?
		   (if (or (and (null any-fins-drawn?)
				(>r distance-from-last-fin
				    (delta-in-window-given-orientation
				      minimum-distance-between-fins
				      orientation-horizontal-p)))
			   ;; If no fins have been drawn, draw one for
			   ;; final link.
			   (>r distance-from-last-fin
			       (delta-in-window-given-orientation
				 desired-distance-between-fins
				 orientation-horizontal-p)))
		       (setq distance-from-last-fin
			     (draw-fins-for-connection-component
			       current-delta orientation-horizontal-p
			       left-most-subrectangle-structure
			       variable-axis-begin-position
			       (cumulative-scaled-width-given-orientation 
				 orientation-horizontal-p)
			       fin-length)))))))
    ))

;; Bind input and output end x and y in window!

;; Consider notifying user if can't draw because there is no 
;; class-description for the connection-class.  Actually, this
;; should be a frame note on the object definition for the icon
;; which has the connection.

;; Assuming left-handedness and end object is output-end-object.
;; Elaborate on this in up front documentation!

#+development
(defparameter draw-connection-corners-p nil)

#+development
(defparameter show-u-vector nil)

#+development
(defun show-u-vector (x y dx dy &optional (scale 30.0))
  (when (boundp 'left-edge-of-draw-area)
    (unless (=e scale 0.0)
      (debug-draw-arrow x y (+f x (round (*e scale dx))) (+f y (round (*e scale dy)))))))

#+development
(defun debug-draw-connection-points (i points)
  (when draw-connection-corners-p
    (debug-draw-vertices points (case i (0 'red) (1 'yellow) (2 'blue) (t 'red)))
    ;; Draw highlights when segment is 45-degrees
    (when (and (eq current-drawing-transfer-mode :xor)
	       (loop for (x1 y1 x2 y2) on points by 'cddr
		     thereis (and x2 y2 (=f (absf (-f x2 x1)) (absf (-f y2 y1))))))
      (debug-draw-vertices points 'red 3))))

#+development
(defun debug-draw-arrow (x0 y0 x1 y1 &key (color 'black))
  (let* ((arrow-length 6.0)
	 (arrow-width 6.0)
	 (dx (coerce-fixnum-to-gensym-float (-f x1 x0)))
	 (dy (coerce-fixnum-to-gensym-float (-f y1 y0)))
	 (L (float-length dx dy))
	 (La (-e L arrow-length 1.0))
	 (c (/e dx L))
	 (s (/e dy L))
	 (xp (+e (coerce-fixnum-to-gensym-float x0) (*e La c)))
	 (yp (+e (coerce-fixnum-to-gensym-float y0) (*e La s)))
	 (x2 (round (-e xp (*e arrow-width 0.5 s))))
	 (y2 (round (+e yp (*e arrow-width 0.5 c))))
	 (x3 (round (+e xp (*e arrow-width 0.5 s))))
	 (y3 (round (-e yp (*e arrow-width 0.5 c))))
	 (xpr (round xp))
	 (ypr (round yp))
	 (color (metacolor-difference color 'background))
	 (points (gensym-list x0 y0 xpr ypr x2 y2 x1 y1 x3 y3 xpr ypr)))
    (draw-wide-polyline points color 0 nil nil)
    (reclaim-gensym-list points)))

#+development
(defun debug-draw-point (x y &key (color 'red) (size 0))
  (draw-solid-rectangle (-f x size) (-f y size)
			(+f x 1 size) (+f y 1 size)
			(metacolor-difference color 'background)))

#+development
(defun debug-draw-vertices (vertices &optional (color 'orange) (size 0))
  (loop for (x y) on vertices by 'cddr
	doing
    (draw-solid-rectangle (-f x size) (-f y size)
			  (+f x 1 size) (+f y 1 size)
			  (metacolor-difference color 'background))))


(defun connection-has-classic-fins-p (connection)
  (and (connection-directed? connection)
       ;; TODO: maybe other cases with classic fins.
       (null (connection-arrows-of-connection connection))))

(defun connection-has-arrows-p (connection)
  (let ((arrows (connection-arrows-of-connection connection)))
    (and ; (connection-directed? connection)
	 (not (null arrows))
	 (neq arrows 'none))))


;changed in Gensym-320: added wrapper on top of the new-draw-connection 
;to optimize connection drawing when possible	 
	 
(defun new-draw-connection-wrapper (connection change-to-this-color-or-color-pattern?)
  
  (when (not (and (=f
              (left-edge-of-block (input-end-object-internal connection))
              (left-edge-of-block (output-end-object-internal connection)))
			  (=f
              (top-edge-of-block (input-end-object-internal connection))
              (top-edge-of-block (output-end-object-internal connection)))			  
			 )) 
        
      (new-draw-connection connection change-to-this-color-or-color-pattern?)
)) 	 
;end of changes	 
	 
;;; The function `new-draw-connection' is the new connection drawing function,
;;; which can draw both orthogonal and diagonal connections with cross section
;;; patterns.

(defun new-draw-connection (connection change-to-this-color-or-color-pattern?)
  (with-temporary-gensym-float-creation new-draw-connection
    (let* ((connection-frame-or-class (connection-frame-or-class connection))
	   (cross-section-pattern
	     (get-cross-section-pattern-given-connection-frame-or-class
	       connection-frame-or-class))
	   (cross-section-regions
	     (get-cross-section-regions cross-section-pattern))
	   (cross-section-stripes
	     (get-cross-section-stripes cross-section-pattern))
	   (vertices (compute-connection-vertices connection))
	   (total-width (connection-total-width connection))
	   (scale (minf current-image-x-scale current-image-y-scale)) ; Arbitrary choice.
	   (line-pattern (connection-line-pattern connection))
	   (stripes (sort-stripes
		      (compute-stripes cross-section-regions
				       cross-section-stripes
				       change-to-this-color-or-color-pattern?
				       scale
				       (and (paint-mode-p) (null line-pattern)))))
	   (nstripes (length stripes))
	   (scaled-line-pattern (compute-scaled-line-pattern line-pattern scale total-width))
	   (connection-has-fins-p (connection-has-classic-fins-p connection))
	   (connection-has-arrows-p (connection-has-arrows-p connection))

	   (fin-length (connection-fin-length connection total-width)) ; Workspace units
	   (fin-color-difference
	     (loop for (index color-difference) in stripes
		   when (=f index 0)	                   ; Historical choice.
		     return color-difference))

	   (arrows (connection-arrows-of-connection connection))
	   (arrow-size (scalef fin-length scale))
	   (arrow-line-thickness (scalef total-width scale))

	   (line-style
	     (cond ((and (connection-diagonal-p connection) (=f nstripes 1))
		    'rounded)
		   (t
		    'miter))))
      ;; TODO: If nstripes>1 and patterned, draw each segment separately, in
      ;; order to keep the line patterns in sync for each stripe.
      (loop for (index color-difference stripe-width-in-window fdist) in stripes
	    as points = (compute-miter-points fdist vertices)
	    doing
	(when connection-has-arrows-p
	  (adjust-points-for-connection-arrows connection arrows points
					       arrow-size arrow-line-thickness))
	(draw-wide-polyline points color-difference stripe-width-in-window
			    scaled-line-pattern line-style)
	#+development
	(debug-draw-connection-points (cond ((=e fdist 0.0) 0) ((>e fdist 0.0) 1) (t 2)) points)
	(reclaim-gensym-list points))

      (when connection-has-fins-p
	(draw-connection-fins vertices total-width fin-length fin-color-difference))

      (when connection-has-arrows-p
	(draw-connection-arrows connection arrows vertices
				arrow-size arrow-line-thickness fin-color-difference))

      (when (consp scaled-line-pattern)
	(reclaim-gensym-list scaled-line-pattern))
      (reclaim-gensym-tree stripes)
      (reclaim-gensym-list vertices))))



;;; The function `compute-stripes' computes a list of
;;;   (index color-difference width-in-window signed-dist-from-centerline).
;;; Fudge increases the width of inner stripes in an attempt to close up missing
;;; pixels.

(defun compute-stripes (cross-section-regions cross-section-stripes color? scale fudge)
  (loop with total-width = (loop for (color . width) in cross-section-stripes
				 summing width using +f)
	with fwidth2 = (/e (float-delta-x-in-window total-width scale) 2.0)
	with nstripes = (length cross-section-stripes)
	for (region-or-color . stripe-width) in cross-section-stripes
	as sum-width = 0.0 then (+e sum-width fw)
	as fw = (float-delta-x-in-window stripe-width scale)
	as fw2 = (/e fw 2.0)
	as fdist = (-e fwidth2 sum-width fw2)
	as index from 0
	as stripe-width-in-window = (delta-x-in-window stripe-width scale)
	as fudged-width-in-window = (if (or (not fudge) (=f index 0) (=f index (-f nstripes 1)))
					stripe-width-in-window
					(+f stripe-width-in-window 2)) ; Hack
	as stripe-color = (compute-connection-stripe-color region-or-color cross-section-regions)
	as recorded-color = (if color? stripe-color 'background)
	as desired-color = (cond ((null color?)
				  stripe-color)
				 ((symbolp color?)
				  color?)
				 (t
				  (compute-connection-stripe-color region-or-color color?)))
	as color-difference = (metacolor-difference desired-color recorded-color)
	collect (gensym-list index color-difference fudged-width-in-window fdist)
	  using gensym-cons))

;; FIXME: The fudge needs to be per-segment, not for the entire connection.
;; No fudge needed for orthogonal segments.


;;; The function `sort-stripes' attempts to improve rendering by moving the
;;; outer stripes to the end of the list, thus drawing them last.

(defun sort-stripes (stripes)
  (cond ((or (<=f (length stripes) 2) (xor-mode-p)) ; Doesn't help in XOR mode.
	 stripes)
	(t
	 ;; (1 2 3 4) -> (2 3 1 4)
	 (let ((next (cdr stripes))
	       (last-two (lastn stripes 2)))
	   (setf (cdr stripes) (last stripes)
		 (cdr last-two) stripes)
	   next))))


;;; The function `lastn' returns the sublist containing the last n elements of
;;; list, or the entire list if it has fewer than n elements.

(defun lastn (list n)
  (loop for result on list
	as marker on (nthcdr n list)
	while marker
	finally (return result)))


;;; The function `compute-miter-points' returns newly consed gensym-list of
;;; integer points perpendicularly offset from the given integer vertices by
;;; fdist, a signed float, and with mitered joins at the corners.  Both vertices
;;; and points are alternating lists like (x1 y1 x2 y2 ...).  Assumes a window
;;; coordinate system (+y is downwards).

(defun compute-miter-points (fdist vertices)
  (if (=e fdist 0.0)			     ; An optimization
      (copy-list-using-gensym-conses vertices)
      (macrolet ((point (x0 y0 scale fdx fdy)
		   `(let* ((x (+f ,x0 (ceilinge-first (*e ,scale ,fdx)))) ; [*]
			   (y (+f ,y0 (ceilinge-first (*e ,scale ,fdy)))))
		      #+development (when show-u-vector (show-u-vector ,x0 ,y0 ,fdx ,fdy))
		      (setq points (gensym-cons y (gensym-cons x points))))))
	(with-temporary-gensym-float-creation compute-miter-points
	  (loop with points = ()
		with pdx = 0.0		; Previous dx,dy.
		with pdy = 0.0
		with pdxn = 0.0		; Previous dxn,dyn.
		with pdyn = 0.0
		for (x1 y1 x2 y2 . rest?) on vertices by 'cddr
		while x2
		as first = t then nil
		as dx = (coerce-fixnum-to-gensym-float (-f x2 x1))
		as dy = (coerce-fixnum-to-gensym-float (-f y2 y1))
		as dn = (float-length dx dy)
		as dxn = (/e dx dn)
		as dyn = (/e dy dn)
		as perpx = dyn
		as perpy = (-e dxn)
		doing
	    (cond (first		     ; First point
		   (point x1 y1 fdist perpx perpy))
		  (t			     ; Middle point
		   (let* ((ux (-e dxn pdxn)) ; b-a
			  (uy (-e dyn pdyn))
			  (cross (float-cross pdxn pdyn dxn dyn))  ; a*b
			  (signum (if (>e cross 0.0) -1.0 +1.0))
			  (un (float-length ux uy))
			  (uxn (if (=e un 0.0) perpx (*e signum (/e ux un))))
			  (uyn (if (=e un 0.0) perpy (*e signum (/e uy un))))
			  (sinth2 (float-cross uxn uyn pdxn pdyn))
			  (length (/e fdist (maxe sinth2 0.1)))) ; FIXME [**]
		     (point x1 y1 length uxn uyn))))
	    (when (null rest?)		     ; Last point
	      (point x2 y2 fdist perpx perpy))
	    (setq pdx dx pdy dy pdxn dxn pdyn dyn)
		finally (return (nreverse points)))))))

;; [*] We use ceiling because X (and Win32) fills towards the smaller coordinate
;; when given an even-width line.

;; [**] Slamming the scale to 0.1 here is bogus. We really want to create a
;; beveled corner. However, we can get away with this for now since it only
;; affects highly acute angles (the connection has to almost turn back on
;; itself).

#+development
(defun debug-connection-vertices (connection &optional ip)
  (let* ((ip (or ip (car (image-planes-this-is-on (workspace-of-connection? connection)))))
	 (gensym-window (gensym-window-for-pane (pane-for-image-plane ip))))
    (on-window-without-drawing (gensym-window)
      (with-raw-window-transform-and-draw-area (gensym-window)
	(with-image-plane-transform (ip)
	  (compute-connection-vertices connection))))))


;;; The function `connection-vertices' returns a newly consed gensym-list of the
;;; vertices of the given connection in window coordinates.  The list is
;;; alternating x and y starting from the input-end.

;;; Contrast with g2-get-connection-vertices, which actually returns deltas, not
;;; vertices, and with connection-vertices-in-workspace, which returns points in
;;; workspace coordinates, each a cons of x and y.

(defun compute-connection-vertices (connection)
  (if (connection-diagonal-p connection)
      (compute-diagonal-connection-vertices connection)
      (compute-orthogonal-connection-vertices connection)))

(defun compute-orthogonal-connection-vertices (connection)
  (with-connection connection t t t
      ((delta-or-deltas? (delta-or-deltas connection))
       (horizontal initial-orientation-horizontal-p)
       (x nil)
       (y nil)
       (xw 0)
       (yw 0)
       (result ()))
    (macrolet ((point (x y)
		 `(progn
		    (setq x ,x y ,y
			  xw (x-in-window x) yw (y-in-window y))
		    (unless (and result (=f yw (car result)) (=f xw (cadr result)))
		      (gensym-push xw result)
		      (gensym-push yw result)))))
      (point input-end-x-position input-end-y-position)
      (do-atom-or-list-of-atoms (delta delta-or-deltas?)
	(if horizontal
	    (point (+r x delta) y)
	    (point x (+r y delta)))
	(setq horizontal (not horizontal)))
      (if horizontal
	  (point output-end-x-position y)
	  (point x output-end-y-position))
      (point output-end-x-position output-end-y-position)
      (nreverse result))))

;; Possible optimization: remove middle point if three consecutive points are colinear.

(defun compute-diagonal-connection-vertices (connection)
  (with-connection connection t t t
      ((delta-or-deltas? (delta-or-deltas connection))
       (horizontal initial-orientation-horizontal-p)
       (x nil)
       (y nil)
       (xw 0)
       (yw 0)
       (ready nil)
       (result ()))
    (macrolet ((point (x y &optional (push-p t))
		 `(progn
		    (setq x ,x y ,y
			  xw (x-in-window x) yw (y-in-window y))
		    (when ,push-p
		      (unless (and result (=f yw (car result)) (=f xw (cadr result)))
			(gensym-push xw result)
			(gensym-push yw result))))))
      (point input-end-x-position input-end-y-position)
      (do-atom-or-list-of-atoms (delta delta-or-deltas?)
	(if horizontal
	    (point (+r x delta) y ready)
	    (point x (+r y delta) ready))
	(setq horizontal (not horizontal)
	      ready (not ready)))
      (when ready
	(if horizontal
	    (point output-end-x-position y)
	    (point x output-end-y-position)))
      (point output-end-x-position output-end-y-position)
      (nreverse result))))


;;; `Draw-fins-for-connection-component' decides how many fins to draw and
;;; computes placement for them so that they are symmetric with respect to the
;;; middle of the link.  It returns the distance from the last fin to the end
;;; of the link.

(defun draw-fins-for-connection-component
    (current-delta orientation-horizontal-p
		   subrectangle-structure
		   connection-component-variable-axis-begin-position
		   connection-overall-width fin-length)
  (let* ((subrectangle-stable-axis-position
	   (stable-axis-position subrectangle-structure))
	 (number-of-fins
	   (maxr 1 (floor (absr current-delta)		    ; slow floor()
			  (delta-in-window-given-orientation
			    desired-distance-between-fins-on-link
			    orientation-horizontal-p))))
	 (spacing-between-fins-on-link
	   (round					    ; slow round()
	     current-delta
	     (+r number-of-fins 1)))
	 (fin-color-difference
	   (subrectangle-color-difference subrectangle-structure))
	 (x-scaled-fin-length
	   (delta-x-in-window fin-length current-image-x-scale))
	 (y-scaled-fin-length
	   (delta-y-in-window fin-length current-image-y-scale)))
    (with-background-color-value
	(subrectangle-background-color-value subrectangle-structure)
      (loop with left-fin-inner-point-x
	    with left-fin-inner-point-y
	    with left-fin-outer-point-x
	    with left-fin-outer-point-y
	    with right-fin-inner-point-x
	    with right-fin-inner-point-y
	    with right-fin-outer-point-x
	    with right-fin-outer-point-y
	    for fin-number from 1 to number-of-fins
	    as position-along-link = (* fin-number
					spacing-between-fins-on-link)
	    do
	(cond
	  (orientation-horizontal-p
	   (setq left-fin-inner-point-x
		 (+r connection-component-variable-axis-begin-position
		     position-along-link)
		 right-fin-inner-point-x
		 left-fin-inner-point-x)
	   (if (>r current-delta 1)
	       (setq left-fin-inner-point-y
		     (-r subrectangle-stable-axis-position 2)
		     left-fin-outer-point-x
		     (-r left-fin-inner-point-x
			 x-scaled-fin-length)
		     left-fin-outer-point-y
		     (-r left-fin-inner-point-y
			 y-scaled-fin-length)
		     right-fin-inner-point-y
		     (+r subrectangle-stable-axis-position
			 connection-overall-width)
		     right-fin-outer-point-y
		     (+r right-fin-inner-point-y
			 y-scaled-fin-length))
	       (setq left-fin-inner-point-y
		     (+r subrectangle-stable-axis-position)
		     left-fin-outer-point-x
		     (+r left-fin-inner-point-x
			 x-scaled-fin-length)
		     left-fin-outer-point-y
		     (+r left-fin-inner-point-y
			 y-scaled-fin-length)
		     right-fin-inner-point-y
		     (-r subrectangle-stable-axis-position
			 connection-overall-width 2)
		     right-fin-outer-point-y
		     (-r right-fin-inner-point-y
			 y-scaled-fin-length)))
	   (setq right-fin-outer-point-x
		 left-fin-outer-point-x))
	  (t
	   (setq left-fin-inner-point-y
		 (+r connection-component-variable-axis-begin-position
		     position-along-link)
		 right-fin-inner-point-y
		 left-fin-inner-point-y)
	   (if (>r current-delta 1)
	       (setq left-fin-inner-point-x
		     (+r subrectangle-stable-axis-position)
		     left-fin-outer-point-x
		     (+r left-fin-inner-point-x
			 x-scaled-fin-length)
		     left-fin-outer-point-y
		     (-r left-fin-inner-point-y
			 y-scaled-fin-length)
		     right-fin-inner-point-x
		     (-r subrectangle-stable-axis-position
			 connection-overall-width
			 2)
		     right-fin-outer-point-x
		     (-r right-fin-inner-point-x
			 x-scaled-fin-length))
	       (setq left-fin-inner-point-x
		     (-r subrectangle-stable-axis-position 2)
		     left-fin-outer-point-x
		     (-r left-fin-inner-point-x
			 x-scaled-fin-length)
		     left-fin-outer-point-y
		     (+r left-fin-inner-point-y
			 y-scaled-fin-length)
		     right-fin-inner-point-x
		     (+r subrectangle-stable-axis-position
			 connection-overall-width)
		     right-fin-outer-point-x
		     (+r right-fin-inner-point-x
			 x-scaled-fin-length)))
	   (setq right-fin-outer-point-y
		 left-fin-outer-point-y)))
	(draw-line left-fin-inner-point-x left-fin-inner-point-y
		   left-fin-outer-point-x left-fin-outer-point-y
		   fin-color-difference)
	(draw-line right-fin-inner-point-x right-fin-inner-point-y
		   right-fin-outer-point-x right-fin-outer-point-y
		   fin-color-difference))
      (absr spacing-between-fins-on-link))))

;; For orthogonal connections only.



(defun-simple float-square (x)
  (*e x x))

(defun-simple float-dot (x1 y1 x2 y2)
  (+e (*e x1 x2) (*e y1 y2)))

(defun-simple float-cross (x1 y1 x2 y2)
  (-e (*e x1 y2) (*e x2 y1)))

(defun-simple float-length (delta-x delta-y)
  (sqrte (+e (*e delta-x delta-x)
	     (*e delta-y delta-y))))

(defun-simple float-distance (delta-x delta-y)
  (sqrte (+e (*e delta-x delta-x)
	     (*e delta-y delta-y))))


;;;; Connection Arrowheads


;;; The parameter `basic-arrow-shapes' defines the grammar symbols for arrow
;;; shapes.

(defparameter basic-arrow-shapes '(arrow triangle diamond circle))
;; TODO: swept-back triangle


;;; The function `draw-connection-arrows' draws one or more arrows on the
;;; connection given the value from the connection-arrows attribute.

(defun draw-connection-arrows (connection arrows vertices size line-width color-difference)
  (if (atom arrows)
      (draw-connection-arrow-1 connection arrows vertices size line-width color-difference)
      (loop for spec in arrows doing
	(draw-connection-arrow-1 connection spec vertices size line-width color-difference))))

(defun draw-connection-arrow-1 (connection spec vertices size line-width color-difference)
  (multiple-value-bind (shape end thickness width height filled?)
      (decode-arrow-spec connection spec size line-width)
    (gensym-dstruct-bind ((xp yp xn yn) (lastn vertices 4))
      (gensym-dstruct-bind ((x0 y0 x1 y1) vertices)
	(when (and yn (or (eq end 'output) (eq end 'both)))
	  (draw-connection-arrow shape xp yp xn yn width height thickness color-difference filled?))
	(when (and y1 (or (eq end 'input) (eq end 'both)))
	  (draw-connection-arrow shape x1 y1 x0 y0 width height thickness color-difference filled?))
	#+tbd
	(when (eq end 'along)
	  (dwarn "draw-connection-arrow-1: fmw should implement ALONG"))))))


;;; The function `draw-connection-arrow' draws a single arrow of given shape on
;;; the x1,y1, end of the given vector. All values are in window coordinates.
;;; Must be called in a temporary-gensym-float context.

(defun draw-connection-arrow (shape x0 y0 x1 y1 width height thickness color-difference filled?)
  (let ((points (compute-arrow-points shape x0 y0 x1 y1 width height thickness)))
    (case shape
      (circle
       (draw-circle points color-difference thickness filled?))
      (t
       (draw-polygon points color-difference thickness filled?)))
    (reclaim-gensym-list points)))


;; Crude sideways drawing of where each point is (0,1,2,3,b,t,c):
;;     |----height---|       
;;     .             .        
;;     .    x1,y1 - -.- - - - -
;;     .      |      .        | thickness/2
;;     .      t - - -.- - - - -
;;     .     /|\     .    |   
;;     .    / | \    .    |  
;;     .   /  |  \   .  width
;;     .  /   c   \  .    |  
;;     . /    |    \ .    |  
;;     ./     |     \.    |  
;;     2------b------3- - -  
;;            |           
;;            |           ^   
;;            |           x
;;          x0,y0    <--y-+

(defun compute-arrow-points (shape x0 y0 x1 y1 width height thickness)
  (assert-that-within-temporary-float-scope)
  (unless (and (=f x0 x1) (=f y0 y1))
    (let* ((W (coerce-fixnum-to-gensym-float width))
	   (H (coerce-fixnum-to-gensym-float height))
	   (dx (coerce-fixnum-to-gensym-float (-f x1 x0)))
	   (dy (coerce-fixnum-to-gensym-float (-f y1 y0)))
	   (L (float-length dx dy))
	   (c (/e dx L))
	   (s (/e dy L))
	   (x1f (coerce-fixnum-to-gensym-float x1))
	   (y1f (coerce-fixnum-to-gensym-float y1))
	   (t2 (if (=f thickness 1) 0.0 (/e (coerce-fixnum-to-gensym-float thickness) 2.0)))
	   (xb (-e x1f (*e (+e t2 W) c)))	      ; Base (float)
	   (yb (-e y1f (*e (+e t2 W) s)))
	   (xt (round (-e x1f (*e t2 c))))	      ; Tip
	   (yt (round (-e y1f (*e t2 s))))
	   (x2 (round (-e xb (*e H 0.5 s))))          ; Endpoint (2)
	   (y2 (round (+e yb (*e H 0.5 c))))
	   (x3 (round (+e xb (*e H 0.5 s))))          ; Endpoint (3)
	   (y3 (round (-e yb (*e H 0.5 c))))
	   (x4 (round (-e xb (*e W c))))	      ; Mirror of t around b.
	   (y4 (round (-e yb (*e W s)))))
      (case shape
	((arrow simple-arrow)			 ; simple-arrow is old name.
	 (gensym-list x2 y2 xt yt x3 y3))
	(triangle
	 (gensym-list x2 y2 xt yt x3 y3 x2 y2))
	(diamond
	 (gensym-list x2 y2 xt yt x3 y3 x4 y4 x2 y2))
	(circle
	 (let* ((d (+e t2 (/e W 2.0)))
		(xc (round (-e x1f (*e d c))))
		(yc (round (-e y1f (*e d s))))
		(radius (halff width)))		 ; width=height here.
	   (gensym-list xc yc radius)))))))


;;;; Map Over Connection Arrows

(defun map-over-connection-arrows (connection vertices function answer)
  (when (connection-has-arrows-p connection)
    (let* ((arrows (connection-arrows-of-connection connection))
	   (thickness (connection-total-width connection))
	   (size (connection-fin-length connection thickness)))
      (cond ((atom arrows)
	     (setq answer
		   (map-over-connection-arrows-1
		     function answer connection arrows vertices size thickness)))
	    (t
	     (loop for spec in arrows doing
	       (setq answer (map-over-connection-arrows-1
			      function answer connection spec vertices size thickness)))))))
    answer)

(defun map-over-connection-arrows-1 (function answer connection spec vertices size line-width)
  (multiple-value-bind (shape end thickness width height)
      (decode-arrow-spec connection spec size line-width)
    (gensym-dstruct-bind ((xp yp xn yn) (lastn vertices 4))
      (gensym-dstruct-bind ((x0 y0 x1 y1) vertices)
	(when (and yn (or (eq end 'output) (eq end 'both)))
	  (setq answer
		(map-over-connection-arrows-2
		  function answer shape xp yp xn yn width height thickness)))
	(when (and y1 (or (eq end 'input) (eq end 'both)))
	  (setq answer
		(map-over-connection-arrows-2
		  function answer shape x1 y1 x0 y0 width height thickness))))))
  answer)

(defun map-over-connection-arrows-2 (function answer shape x0 y0 x1 y1 width height thickness)
  (let ((points (compute-arrow-points shape x0 y0 x1 y1 width height thickness))
	(t2 (1+f (truncatef thickness 2))))
    (case shape
      (circle
       (gensym-dstruct-bind ((xc yc radius) points)
	 (let ((left (-f xc radius t2))
	       (top (-f yc radius t2))
	       (right (+f xc radius t2))
	       (bottom (+f yc radius t2)))
	   (setq answer
		 (funcall-simple-compiled-function
		   function left top right bottom answer)))))
      (t
       (loop for (x y) on points by #'cddr
	     while y
	     minimize (-f x t2) into left
	     minimize (-f y t2) into top
	     maximize (+f x t2) into right
	     maximize (+f y t2) into bottom
	     finally
	       (setq answer
		     (funcall-simple-compiled-function
		       function left top right bottom answer)))))
    (reclaim-gensym-list points))
  answer)


;;;; Connection Arrow Utilties


;;; The function `decode-arrow-spec' gives meaning to the various adjectives in
;;; a connection arrow specification.

(defun decode-arrow-spec (connection spec size line)
  (multiple-value-bind (shape placement thick width height filled)
      (decode-arrow-spec-1 spec)
    (values shape
	    (default-placement-of-connection-arrow connection placement)
	    (ashf line thick)
	    (ashf size width)
	    (ashf size height)
	    filled)))

;; NOTE: This could be done at compile-time. 
(defun decode-arrow-spec-1 (spec)
  (let ((filled 0)
	(thick 0)
	(width 0)
	(height 0)
	(delta 1))
    (when (consp spec)
      (loop for adjective in (cddr spec)
	    doing (case adjective
		    (filled
		     (incff filled delta))
		    (open
		     (decff filled delta))
		    (large
		     (incff width delta)
		     (incff height delta))
		    (small
		     (decff width delta)
		     (decff height delta))
		    (wide
		     (incff height delta)) ; NOTE: What we call height, is width to the user.
		    (narrow
		     (decff height delta))
		    (thick
		     (incff thick delta))
		    (thin
		     (decff thick delta)))
		  (if (eq adjective 'very)
		      (setq delta 2)
		      (setq delta 1))))
    (values (if (atom spec) spec (cadr spec))      ; shape
	    (if (atom spec) 'default (car spec))   ; placement
	    thick width height (> filled 0))))

;;; The function `connection-arrow-height-1' returns the "height" of the arrow,
;;; which is defined to be the perpendicular distance on both sides of the
;;; centerline (see figure above). It duplicates some of the computations in
;;; `decode-arrow-spec' and `decode-arrow-spec-1'.

(defun connection-arrow-height-1 (arrow size)
  (let ((height 0)
	(delta 1))
    (when (consp arrow)
      (loop for adjective in (cddr arrow) doing
	(case adjective
	  ((wide large)   (incff height delta))
	  ((narrow small) (decff height delta)))
	(if (eq adjective 'very)
	    (setq delta 2)
	    (setq delta 1))))
    (ashf size height)))

;;; The function `default-placement-of-connection-arrow' puts the arrow at the
;;; output end for directed connections and both ends for undirected
;;; connections, by default.

(defun default-placement-of-connection-arrow (connection placement)
  (case placement
    (default (if (connection-directed? connection) 'output 'both))
    (t placement)))

;;; The function `connection-arrow-width' returns an upper bound on the twice
;;; the maximum perpendicular distance of any of connection's pixels from the
;;; centerline of any connection segment. Note that classic fins extend from the
;;; border of the segment, while the new arrows extend from the centerline.

(defun connection-arrow-width (connection)
  (let* ((width (compute-connection-width-given-connection-frame-or-class
		  (connection-frame-or-class connection)))
	 (size (connection-fin-length connection width)) ; Workspace units, w/o modifiers.
	 (arrows (connection-arrows-of-connection connection)))
    (maxf width
	  (cond ((eq arrows 'none)
		 width)
		((and (null arrows)
		      (connection-directed? connection))
		 (+f width (*f size 2)))	; Total distance on both sides.
		((atom arrows)
		 size)
		(t
		 (loop for arrow in arrows
		       maximize (connection-arrow-height-1 arrow size)))))))


;;; The function `length-of-arrow-shape' determines how far to "pull back" a
;;; connection line to make room for an arrow of given shape, size, and line
;;; thickness.

(defun length-of-arrow-shape (shape size thickness)
  (case shape
    ((arrow simple-arrow) thickness)	; simple-arrow is in some 8.1a/b KBs
    (triangle size)
    (diamond  (*f 2 size))
    (circle   size)
    (t size)))

;;; The function `adjust-points-for-connection-arrows', given arrow specs and
;;; size, and the set of points for the connection, pull back the input and/or
;;; output end vertices of points to make room for the arrow(s) to be drawn
;;; there.

(defun adjust-points-for-connection-arrows (connection arrows points size line)
  (if (atom arrows)
      ;; Yuck
      (multiple-value-bind (shape ends thickness width)
	  (decode-arrow-spec connection arrows size line)
	(let ((length (length-of-arrow-shape shape width thickness)))
	  (case ends
	    (input
	     (pull-in-endpoint points length nil))
	    (output
	     (pull-in-endpoint points length t))
	    (both
	     (pull-in-endpoint points length nil)
	     (pull-in-endpoint points length t)))))
      
      (loop for arrow in arrows
	    as len-1 = 0
	    as len-2 = 0
	    do (multiple-value-bind (shape ends thickness width)
		   (decode-arrow-spec connection arrow size line)
		 (let ((length (length-of-arrow-shape shape width thickness)))
		   (case ends
		     (input
		      (setq len-1 length))
		     (output
		      (setq len-2 length))
		     (both
		      (setq len-1 length
			    len-2 length))
		     #+tbd (along))))	         ; Neither end.
	    maximize len-1 into length-at-input-end
	    maximize len-2 into length-at-output-end
	    finally
	      (when (>f length-at-input-end 0)
		(pull-in-endpoint points length-at-input-end nil))
	      (when (>f length-at-output-end 0)
		(pull-in-endpoint points length-at-output-end t)))))


;;; The function `pull-in-endpoint' adjusts either the head or tail segment of
;;; the given points list, pulling it inwards along the line segment by
;;; distance.

(defun pull-in-endpoint (points distance tail-p)
  (let ((vector (if tail-p (lastn points 4) points)))
    (gensym-dstruct-bind ((x0 y0 x1 y1) vector)
      (when (and y1 (or (/=f x0 x1) (/=f y0 y1)))
	(let* ((dx (coerce-fixnum-to-gensym-float (-f x1 x0)))
	       (dy (coerce-fixnum-to-gensym-float (-f y1 y0)))
	       (L (float-length dx dy))
	       (c (/e dx L))
	       (s (/e dy L))
	       (x0f (coerce-fixnum-to-gensym-float x0))
	       (y0f (coerce-fixnum-to-gensym-float y0))
	       (x1f (coerce-fixnum-to-gensym-float x1))
	       (y1f (coerce-fixnum-to-gensym-float y1))
	       (dist (coerce-fixnum-to-gensym-float distance)))
	  (cond (tail-p
		 (setf (third vector)  (round (-e x1f (*e dist c)))
		       (fourth vector) (round (-e y1f (*e dist s)))))
		(t
		 (setf (first vector)  (round (+e x0f (*e dist c)))
		       (second vector) (round (+e y0f (*e dist s)))))))))))


;;; The function `draw-connection-fins' draws all of the fins for the diagonal
;;; connection of given thickness (in workspace units) with given vertices
;;; (in window coordinates).

(defun draw-connection-fins (vertices thickness fin-length color-difference)
  (loop for (x1 y1 x2 y2) on vertices by 'cddr doing
    (when x2
      (draw-fins-for-diagonal-connection-component
	x1 y1 x2 y2 thickness fin-length color-difference))))


;;; The function `draw-fins-for-diagonal-connection-component' draws the
;;; fins for the given connection segment.

(defun draw-fins-for-diagonal-connection-component
    (x1 y1 x2 y2 connection-width fin-length color-difference)
  (draw-fins-for-diagonal-connection-component-1
    x1 y1 x2 y2 connection-width fin-length color-difference t))


;;; The function `bounding-region-of-fins-for-diagonal-connection-component'
;;; returns the region bounding the fins for the given connection component.

(defun bounding-region-of-fins-for-diagonal-connection-component
    (x1 y1 x2 y2 connection-width fin-length)
  (draw-fins-for-diagonal-connection-component-1
    x1 y1 x2 y2 connection-width fin-length 0 nil))


;;; The function `draw-fins-for-diagonal-connection-component-1' is used
;;; either to draw the fins for the given connection segment, or to simply
;;; return the bounding region for all of them.  connection-width is the total
;;; connection width in workspace units.

(defun draw-fins-for-diagonal-connection-component-1
    (x1 y1 x2 y2 connection-width fin-length color-difference draw?)
  (with-temporary-gensym-float-creation draw-fins-for-diagonal-connection-component-1
    (loop with region = (unless draw? (make-empty-region))
	  with fx1 = (coerce-to-gensym-float x1)
	  with fy1 = (coerce-to-gensym-float y1)
	  with fx2 = (coerce-to-gensym-float x2)
	  with fy2 = (coerce-to-gensym-float y2)
	  with scale = (minf current-image-x-scale current-image-y-scale)
	  with fw2 = (/e (float-delta-x-in-window connection-width scale) 2.0)
	  with delta-x = (-e fx2 fx1)
	  with delta-y = (-e fy2 fy1)
	  with link-length = (float-distance delta-x delta-y)
	  with number-of-fins 
	    = (max 1 (floor link-length
			    desired-distance-between-fins-on-link))
	  with spacing-between-fins-on-link
	    = (round 
		link-length
		(+ number-of-fins 1))
	  ;; Rather than not scaling fin-length at all, at least scale it correctly
	  ;; for unstretched workspaces. -fmw, 12/30/94
	  with scaled-fin-length = (delta-x-in-window fin-length scale)
	  with float-fin-length = (coerce-to-gensym-float scaled-fin-length)
	  with base-length = (-e float-fin-length)
	  with fin-1-inner-point-x
	  with fin-1-inner-point-y
	  with fin-2-inner-point-x
	  with fin-2-inner-point-y
	  with fin-1-base-point-x
	  with fin-1-base-point-y
	  with fin-2-base-point-x
	  with fin-2-base-point-y
	  with fin-1-outer-point-x
	  with fin-1-outer-point-y
	  with fin-2-outer-point-x
	  with fin-2-outer-point-y
	  for fin-number from 1 to number-of-fins
	  as position-along-link 
	     = (coerce-to-gensym-float 
		 (* fin-number
		    spacing-between-fins-on-link))
	  do
      (cond
        ((= delta-x 0)
	 (setq fin-1-inner-point-x (+e fx1 fw2)
	       fin-2-inner-point-x (-e fx1 fw2)
	       fin-1-inner-point-y (if (>e delta-y 0.0) 
				       (+e fy1 position-along-link)
				       (-e fy1 position-along-link))
	       fin-2-inner-point-y fin-1-inner-point-y
	       fin-1-base-point-y  (if (>e delta-y 0.0) 
				       (+e fin-1-inner-point-y base-length)
				       (-e fin-1-inner-point-y base-length))
	       fin-1-outer-point-x (+e fin-1-inner-point-x float-fin-length)
	       fin-1-outer-point-y fin-1-base-point-y
	       fin-2-outer-point-x (-e fin-2-inner-point-x float-fin-length)
	       fin-2-outer-point-y fin-1-base-point-y))
	((= delta-y 0)
	 (setq fin-1-inner-point-x (if (>e delta-x 0.0) 
				       (+e fx1 position-along-link)
				       (-e fx1 position-along-link))
	       fin-2-inner-point-x fin-1-inner-point-x
	       fin-1-inner-point-y (+e fy1 fw2)
	       fin-2-inner-point-y (-e fy1 fw2)
	       fin-1-base-point-x  (if (>e delta-x 0.0) 
				       (+e fin-1-inner-point-x base-length)
				       (-e fin-1-inner-point-x base-length))
	       fin-1-outer-point-x fin-1-base-point-x
	       fin-1-outer-point-y (+e fin-1-inner-point-y float-fin-length)
	       fin-2-outer-point-x fin-1-base-point-x
	       fin-2-outer-point-y (-e fin-2-inner-point-y float-fin-length)))
	(t
	 (let* ((ux (/e delta-x link-length))
		(uy (/e delta-y link-length))
		(perpx uy)
		(perpy (-e ux))
		(dx (*e fw2 perpx))
		(dy (*e fw2 perpy)))
	   (setq fin-1-inner-point-x (+e fx1 (*e position-along-link ux) dx)
		 fin-2-inner-point-x (+e fx1 (*e position-along-link ux) (-e dx))
		 fin-1-inner-point-y (+e fy1 (*e position-along-link uy) dy)
		 fin-2-inner-point-y (+e fy1 (*e position-along-link uy) (-e dy))
		 fin-1-base-point-x  (+e fin-1-inner-point-x
					 (/e (*e delta-x base-length) link-length))
		 fin-1-base-point-y  (+e fin-1-inner-point-y
					 (/e (*e delta-y base-length) link-length))
		 fin-2-base-point-x  (+e fin-2-inner-point-x
					 (/e (*e delta-x base-length) link-length))
		 fin-2-base-point-y  (+e fin-2-inner-point-y
					 (/e (*e delta-y base-length) link-length))
		 fin-1-outer-point-x (+e fin-1-base-point-x
					 (/e (*e delta-y float-fin-length) link-length))
		 fin-1-outer-point-y (+e fin-1-base-point-y
					 (/e (*e (-e delta-x) float-fin-length) link-length))
		 fin-2-outer-point-x (+e fin-2-base-point-x
					 (/e (*e (-e delta-y) float-fin-length) link-length))
		 fin-2-outer-point-y (+e fin-2-base-point-y
					 (/e (*e delta-x float-fin-length) link-length))))))
      (when fin-1-inner-point-x
	(setq fin-1-inner-point-x (round fin-1-inner-point-x)
	      fin-1-inner-point-y (round fin-1-inner-point-y)
	      fin-2-inner-point-x (round fin-2-inner-point-x)
	      fin-2-inner-point-y (round fin-2-inner-point-y)
	      fin-1-outer-point-x (round fin-1-outer-point-x)
	      fin-1-outer-point-y (round fin-1-outer-point-y)
	      fin-2-outer-point-x (round fin-2-outer-point-x)
	      fin-2-outer-point-y (round fin-2-outer-point-y))
	(cond (draw?
	       (new-draw-line fin-1-inner-point-x fin-1-inner-point-y
			      fin-1-outer-point-x fin-1-outer-point-y
			      color-difference)
	       (new-draw-line fin-2-inner-point-x fin-2-inner-point-y
			      fin-2-outer-point-x fin-2-outer-point-y
			      color-difference))
	      (t
	       (setq region
		     (add-rectangle-to-region
		       (minf fin-1-inner-point-x fin-2-inner-point-x
			     fin-1-outer-point-x fin-2-outer-point-x)
		       (minf fin-1-inner-point-y fin-2-inner-point-y
			     fin-1-outer-point-y fin-2-outer-point-y)
		       (1+f (maxf fin-1-inner-point-x fin-2-inner-point-x
				  fin-1-outer-point-x fin-2-outer-point-x))
		       (1+f (maxf fin-1-inner-point-y fin-2-inner-point-y
				  fin-1-outer-point-y fin-2-outer-point-y))
		       region)))))
	  finally
	    (return (if draw? spacing-between-fins-on-link region)))))


(def-substitution-macro compute-outer-link-end-position 
    (variable-axis-end-position 
			 first-subrectangle-structure subrectangle-scaled-width
			 next-delta initial-delta-p previous-turn? right-turn?
			 cumulative-scaled-width cumulative-scaled-half-width)
  (if (=r next-delta 0)
      variable-axis-end-position
      (if (or initial-delta-p
	      (null previous-turn?))
	  (if (>r current-delta 1)
	      (if (or (oddp cumulative-scaled-width)
		      (not right-turn?))
		  (+r variable-axis-end-position
		      cumulative-scaled-half-width)
		  (+r variable-axis-end-position
		      cumulative-scaled-half-width
		      (-r 1)))
	      (if (or (oddp cumulative-scaled-width)
		      (not right-turn?))
		  (-r variable-axis-end-position
		      cumulative-scaled-half-width)
		  (-r variable-axis-end-position
		      cumulative-scaled-half-width
		      (-r 1))))
	  (if
	    (if right-turn?
		(not (eq previous-turn? 'right))
		(not (eq previous-turn? 'left)))
	    (+r (variable-axis-begin-position
		  first-subrectangle-structure)
		current-delta)
	    (if (or (oddp cumulative-scaled-width)
		    (not right-turn?))
		(+r (variable-axis-begin-position
		      first-subrectangle-structure)
		    current-delta
		    (if (>r current-delta 1)
			(+r 
			  cumulative-scaled-width
			  (-r subrectangle-scaled-width))
			(-r
			  (+r 
			    cumulative-scaled-width
			    (-r subrectangle-scaled-width)))))
		(+r (variable-axis-begin-position
		      first-subrectangle-structure)
		    current-delta
		    (if (>r current-delta 1)
			(+r 
			  cumulative-scaled-width
			  (-r subrectangle-scaled-width)
;					    (-r 1))
			  )
			(-r
			  (+r
			    cumulative-scaled-width
			    (-r subrectangle-scaled-width)
;					      (-r 1)
			    )))))))))




(defun draw-connection-subrectangles 
       (connection-subrectangle-structures-to-use 
	right-turn? previous-turn? last-link?
	next-delta initial-delta-p variable-axis-end-position)
  (if last-link?
      ;; Last link is special cased here since it requires far
      ;; fewer calculations.
      (loop for connection-subrectangle-structure
		in connection-subrectangle-structures-to-use
	    as subrectangle-width
	       = (scaled-subrectangle-width-given-orientation
		   connection-subrectangle-structure)
	    do 
	(setf (variable-axis-end-position
		connection-subrectangle-structure)
	      variable-axis-end-position)
	(draw-subrectangle-for-connection 
	  connection-subrectangle-structure subrectangle-width))

      ;; if not last-link?
      (loop with first-subrectangle-structure
	      = (car connection-subrectangle-structures-to-use)
	    with subrectangle-variable-axis-end-position
	      = (if orientation-horizontal-p
		    (compute-outer-link-end-position 
		      variable-axis-end-position first-subrectangle-structure
		      (subrectangle-scaled-y-width first-subrectangle-structure)
		      next-delta initial-delta-p previous-turn? right-turn?
		      cumulative-y-scaled-connection-stripe-width
		      cumulative-y-scaled-connection-stripe-half-width)
		    (compute-outer-link-end-position 
		      variable-axis-end-position first-subrectangle-structure
		      (subrectangle-scaled-x-width first-subrectangle-structure)
		      next-delta initial-delta-p previous-turn? right-turn?
		      cumulative-x-scaled-connection-stripe-width
		      cumulative-x-scaled-connection-stripe-half-width))

	    for connection-subrectangle-structure
		in connection-subrectangle-structures-to-use
	    
	    as subrectangle-width
	       = (scaled-subrectangle-width-given-orientation
		   connection-subrectangle-structure)
	    as subrectangle-stable-axis-position
	       = (stable-axis-position
		   connection-subrectangle-structure)
	    as next-subrectangle-stable-axis-position
	       = (if (=r next-delta 0)
		     subrectangle-stable-axis-position
		     (calculate-subrectangle-stable-axis-position-for-next-link
		       right-turn? subrectangle-variable-axis-end-position
		       subrectangle-width))
	    as next-subrectangle-variable-axis-begin-position
	       = (if (=r next-delta 0)
		     subrectangle-variable-axis-end-position
		     (calculate-subrectangle-variable-axis-begin-position-for-next-link
		       right-turn? subrectangle-stable-axis-position
		       subrectangle-width))
	    
	    do
	
;	    (break "srsap, srvabp, srvaep: ~S ~S ~S~%"
;		   subrectangle-stable-axis-position
;		   (variable-axis-begin-position
;		     connection-subrectangle-structure)
;		   subrectangle-variable-axis-end-position)
	
	(setf (variable-axis-end-position connection-subrectangle-structure)
	      subrectangle-variable-axis-end-position)
	(draw-subrectangle-for-connection 
	  connection-subrectangle-structure subrectangle-width)
	(setq subrectangle-variable-axis-end-position
	      (if (=r next-delta 0)
		  subrectangle-variable-axis-end-position
		  (calculate-next-subrectangle-variable-axis-end-position
		    subrectangle-variable-axis-end-position
		    subrectangle-width)))	       ; turn always started on outside corner
	(setf (variable-axis-begin-position
		connection-subrectangle-structure)
	      next-subrectangle-variable-axis-begin-position
	      (stable-axis-position
		connection-subrectangle-structure)
	      next-subrectangle-stable-axis-position))))




#+development
(defvar debug-connections? t) ; old: nil

(defun draw-subrectangle-for-connection 
    (connection-subrectangle-structure subrectangle-width)
  (with-background-color-value (subrectangle-background-color-value
				 connection-subrectangle-structure)
    (let ((subrectangle-color-difference
	    (subrectangle-color-difference
	      connection-subrectangle-structure))
	  (subrectangle-variable-axis-begin-position
	    (variable-axis-begin-position
	      connection-subrectangle-structure))
	  (subrectangle-variable-axis-end-position
	    (variable-axis-end-position
	      connection-subrectangle-structure))
	  (subrectangle-stable-axis-position
	    (stable-axis-position
	      connection-subrectangle-structure))
	  top-edge-of-subrectangle-in-window
	  left-edge-of-subrectangle-in-window
	  bottom-edge-of-subrectangle-in-window
	  right-edge-of-subrectangle-in-window)

      ;#+development
      ;(when debug-connections?
	;(format t "Subrectangle positions: ~S ~%"
		;(x-in-window subrectangle-stable-axis-position)))

      (unless (color-difference-is-transparent-p subrectangle-color-difference)
	(if orientation-horizontal-p
	    (if (>r 0 current-delta)
		(setq top-edge-of-subrectangle-in-window
		      (-r subrectangle-stable-axis-position
			  subrectangle-width)
		      left-edge-of-subrectangle-in-window
		      subrectangle-variable-axis-end-position
		      bottom-edge-of-subrectangle-in-window
		      subrectangle-stable-axis-position
		      right-edge-of-subrectangle-in-window
		      subrectangle-variable-axis-begin-position)
		(setq top-edge-of-subrectangle-in-window
		      subrectangle-stable-axis-position
		      left-edge-of-subrectangle-in-window
		      subrectangle-variable-axis-begin-position
		      bottom-edge-of-subrectangle-in-window
		      (+r subrectangle-stable-axis-position
			  subrectangle-width)
		      right-edge-of-subrectangle-in-window
		      subrectangle-variable-axis-end-position))

	    ;; if orientation is vertical
	    (if (>r 0 current-delta)
		(setq top-edge-of-subrectangle-in-window
		      subrectangle-variable-axis-end-position
		      left-edge-of-subrectangle-in-window
		      subrectangle-stable-axis-position
		      bottom-edge-of-subrectangle-in-window
		      subrectangle-variable-axis-begin-position
		      right-edge-of-subrectangle-in-window
		      (+r subrectangle-stable-axis-position
			  subrectangle-width))
		(setq top-edge-of-subrectangle-in-window
		      subrectangle-variable-axis-begin-position
		      left-edge-of-subrectangle-in-window
		      (-r subrectangle-stable-axis-position
			  subrectangle-width)
		      bottom-edge-of-subrectangle-in-window
		      subrectangle-variable-axis-end-position
		      right-edge-of-subrectangle-in-window
		      subrectangle-stable-axis-position)))
	
	(with-drawing-trace (connections)
	  (format t "Connection subrectangle ~d ~d ~d ~d  color-diff ~d~%"
		  left-edge-of-subrectangle-in-window
		  top-edge-of-subrectangle-in-window
		  right-edge-of-subrectangle-in-window
		  bottom-edge-of-subrectangle-in-window
		  subrectangle-color-difference))
	(draw-solid-rectangle
	  left-edge-of-subrectangle-in-window
	  top-edge-of-subrectangle-in-window
	  right-edge-of-subrectangle-in-window
	  bottom-edge-of-subrectangle-in-window
	  subrectangle-color-difference)))))

;; This doesn't work right when color difference is 0!

;; I changed the test for 0 color-difference to
;; color-difference-is-transparent-p. -fmw, 6/10/94


(defun compute-new-vertex-and-draw-diagonal-link
       (vertex-x vertex-y orientation-horizontal-p 
	current-delta next-delta connection-subrectangle-structures
	draw-fins? fin-length)
  (multiple-value-bind 
    (new-vertex-x new-vertex-y)
      (compute-new-vertex
	vertex-x vertex-y orientation-horizontal-p 
	current-delta next-delta t)
    (draw-diagonal-link 
      connection-subrectangle-structures
      vertex-x vertex-y new-vertex-x new-vertex-y)
    (when draw-fins?
      (draw-fins-for-diagonal-connection-component
	vertex-x vertex-y new-vertex-x new-vertex-y 1
	fin-length
	(subrectangle-color-difference
	  (car connection-subrectangle-structures)))) ; Arbitrary choice.
    (values new-vertex-x new-vertex-y)))

(defun compute-new-vertex
       (vertex-x vertex-y orientation-horizontal-p 
	current-delta next-delta compute-in-image-units?)
  (let (delta-x delta-y new-vertex-x new-vertex-y)
    (if orientation-horizontal-p
	(setq delta-x current-delta
	      delta-y next-delta)
	(setq delta-y current-delta
	      delta-x next-delta))
    (if compute-in-image-units?				    ; Hah!
	(setq new-vertex-x (+r vertex-x delta-x)
	      new-vertex-y (+r vertex-y delta-y))
	(setq new-vertex-x (+w vertex-x delta-x)
	      new-vertex-y (+w vertex-y delta-y)))
    (values new-vertex-x new-vertex-y)))

(defun draw-diagonal-link 
       (connection-subrectangle-structures-to-use
	old-vertex-x old-vertex-y vertex-x vertex-y)
  (let ((color-difference
	  (subrectangle-color-difference
	    ;; Here we arbitrarily choose the color of the first stripe in the
	    ;; list.  Might make more sense to choose the "center" stripe, if
	    ;; any.  Too late now. -fmw, 1/11/02
	    (car connection-subrectangle-structures-to-use))))
    (draw-line old-vertex-x old-vertex-y vertex-x vertex-y
	       color-difference)))



;;;; Support for "Loose-ends"


(defun add-loose-ends-as-subblocks-and-shift (block superblock delta-x delta-y)
  (loop for connection being the connections of block
	as loose-end
	   = (if (eq (input-end-object connection) block)
		 (output-end-object connection)
		 (input-end-object connection))
	do (funcall-method
	     'shift loose-end delta-x delta-y)
	   (add-subblock loose-end superblock)))


;;;; Support for Changing Size in Object Definition


;;; Adjust-connections-according-to-new-edge is used by
;;; adjust-edges-of-instances to adjust connections when an object definition's
;;; icon height or width are changed and there are
;;; instances of the object in the schematic.

(defun adjust-connections-according-to-new-edge 
       (block straight-connections side-to-shift delta-width delta-height)
  (loop for connection being each connection of block
	do
    (adjust-connection-according-to-new-edge
      connection block straight-connections
      side-to-shift delta-width delta-height 
      (eq (input-end-object connection) block))))


(def-substitution-macro left-or-right-side? (side)
  (memq side '(left right)))

(def-substitution-macro top-or-bottom-side? (side)
  (memq side '(top bottom)))

(defun adjust-connection-according-to-new-edge
       (connection block straight-connections side-to-shift 
	delta-width delta-height output-connection?)
  (let ((side
	  (if output-connection? 
	      (get-side-given-end-position (input-end-position connection))
	      (get-side-given-end-position (output-end-position connection)))))
    (when (eq side side-to-shift)
      (shift-connection
	connection block straight-connections
	output-connection? 
	(if (left-or-right-side? side) delta-width 0)
	(if (top-or-bottom-side? side) delta-height 0)))
    (cond
      ((top-or-bottom-side? side)
       (case side-to-shift
	 (left
	  (shift-end-position-of-connection
	    block connection straight-connections
	    output-connection? side (-w delta-width)))
	 (right
	  (shift-end-position-of-connection
	    block connection straight-connections
	    output-connection? side 0))))
      ((left-or-right-side? side)
       (case side-to-shift
	 (top
	  (shift-end-position-of-connection
	    block connection straight-connections
	    output-connection? side (-w delta-height)))
	 (bottom
	  (shift-end-position-of-connection
	    block connection straight-connections
	    output-connection? side 0)))))))


;;; `Shift-end-position-of-connection' makes sure to check that the end
;;; position will not be beyond the limits of the edges of the block.  If it
;;; is, it clips it and returns a shift difference.

(defun shift-end-position-of-connection
       (block connection straight-connections
	output-connection? side shift)
  (let* ((end-position
	   (if output-connection?
	       (input-end-position connection) 
	       (output-end-position connection)))
	 (desired-position
	   (+w (get-position-on-side-given-end-position end-position)
	       shift))
	 (left-or-right-side? (left-or-right-side? side))
	 (maximum-position
	   (-w (if left-or-right-side?
		   (height-of-block block) (width-of-block block)) 1))
	 actual-position 
	 (shift-difference? nil)
	 new-end-position)
    (cond
      ((<w desired-position 0)
       (setq actual-position 0
	     shift-difference? (-w actual-position desired-position)))
      ((>w desired-position maximum-position)
       (setq actual-position maximum-position
	     shift-difference? (-w actual-position desired-position)))
      (t (setq actual-position desired-position)))
    (setq new-end-position
	  (combine-side-and-position-on-side-for-end-position
	    side actual-position))

    (when shift-difference?
      (if left-or-right-side?
	  (shift-connection connection block straight-connections
			    output-connection? 0 shift-difference?)
	  (shift-connection connection block straight-connections
			    output-connection? shift-difference? 0)))

    (if output-connection?
	(setf (input-end-position connection) new-end-position)
	(setf (output-end-position connection) new-end-position))))


(defun shift-connection
       (connection block straight-connections
	output-connection? delta-x delta-y)
  (let ((delta-for-straight-connection?
	  (cdr (assq connection straight-connections)))
	(object-at-other-end 
	  (if output-connection?
	      (output-end-object connection) 
	      (input-end-object connection))))
    (if delta-for-straight-connection?
	(cond
	  ((loose-end-p object-at-other-end)
	   (funcall-method
	     'shift object-at-other-end
	     delta-x delta-y))
	  (t (put-kink-into-connection-if-straight-1 
	       connection delta-for-straight-connection?)
	     (if output-connection?
		 (change-connection-deltas-for-object-being-dragged
		   connection block delta-x delta-y))))
	(if output-connection?
	    (change-connection-deltas-for-object-being-dragged
	      connection block delta-x delta-y)))))

;; The loose end is shifted to keep the connection straight.  A "safer"
;; way to do this would be to base the shift not on the delta but on
;; the end position of the connection.



;;; Updating images on an entity redraws all output connections.  Input connections
;;; have to be drawn separately (by calling draw-input-connections-of-block).

(defun update-input-connections-of-entity 
       (entity erase? &optional icon-description-for-inhibiting?)
  (loop with workspace? = (get-workspace-if-any entity)
	for connection being each input-connection of entity
	do
    (when (and (not (eq (input-end-object connection) entity))
	       (or (null icon-description-for-inhibiting?)
		   (not (eq (icon-description-for-instance
			      (input-end-object connection))
			    icon-description-for-inhibiting?))))
      (update-connection-images erase? workspace? connection))))

#+unused
(defun update-output-connections-of-entity (entity erase?)
  (loop with workspace? = (get-workspace-if-any entity)
	for connection being each output-connection of entity
	do
    (when (not (eq (output-end-object connection) entity))
      (update-connection-images erase? workspace? connection))))

;; This is currently used only in adjust-and-draw-images.  Normally,
;; output connections are drawn by draw-connections-for-block as
;; part of the draw method of a block.




;;;; Connection Magnification, Reflection and Rotation Support


;;; Magnify-icon changes the size of an icon according to the arguments
;;; x-magnification? and y-magnification?.  These arguments are absolute
;;; and can also be nil, in which case, normal magnification is used for
;;; the axis.  Thus, an icon can be easily restored to its original size
;;; by passing nil for these arguments.

;;; Entity must have a non-nil icon-description slot.

;;; Note that it is assumed that the magnification arguments passed in are
;;; for the current rotation.  Thus, they are converted to magnifications
;;; for the non-rotated icon (depending on whether rotated-by-90) before 
;;; being put into the icon attributes plist.  See also documentation for
;;; draw method for entity.  Note also that since both the draw method
;;; for entity and magnify-icon use magnify which does integer multiplication,
;;; there is never any loss of accuracy and the icon rendering should stay
;;; consistent with the edges of the block.

;;; If new-left-edge? is non-nil, the new-left-edge? and new-top-edge specify
;;; the location the entity should be shifted to before redrawing with the new
;;; magnification.

;; Note that this "absolute" behavior is in contrast to rotate-and-reflect-icon
;; which takes as its argument an incremental rotation rather than an absolute
;; one.

;; Note-as-kb-state-change? is not currently used.  This would be useful if 
;; icons could be magnified due to actions of rules.

(defun magnify-icon (entity 
		      x-magnification-for-current-rotation? 
		      y-magnification-for-current-rotation?
		      new-left-edge? new-top-edge? note-as-kb-state-change?)
  ;; Note as kb state change?
  note-as-kb-state-change?

  (let* ((workspace? (get-workspace-if-any entity))
	 (icon-attributes-plist (icon-attributes-plist entity))
	 (icon-description (icon-description entity))
	 (x-magnification-for-current-rotation
	   (or x-magnification-for-current-rotation?
	       (icon-x-magnification? icon-description)
	       (convert-to-magnification 1)))
	 (y-magnification-for-current-rotation
	   (or y-magnification-for-current-rotation?
	       (icon-y-magnification? icon-description)
	       (convert-to-magnification 1)))
	 (old-x-magnification-with-no-rotation?
	   (or (getf icon-attributes-plist 'x-magnification)
	       (icon-x-magnification? icon-description)))
	 (old-y-magnification-with-no-rotation?
	   (or (getf icon-attributes-plist 'y-magnification)
	       (icon-y-magnification? icon-description)))
	 (delta-left-edge
	   (if new-left-edge?
	       (-w new-left-edge? (left-edge-of-block entity))
	       0))
	 (delta-top-edge
	   (if new-top-edge?
	       (-w new-top-edge? (top-edge-of-block entity))
	       0))
	 (x-magnification-with-no-rotation? x-magnification-for-current-rotation?) 
	 (y-magnification-with-no-rotation? y-magnification-for-current-rotation?)
	 (old-x-magnification-for-current-rotation?
	   old-x-magnification-with-no-rotation?)
	 (old-y-magnification-for-current-rotation?
	   old-y-magnification-with-no-rotation?)
	 (unmagnified-block-width
	   (or (getfq icon-attributes-plist 'width)
	       (width-of-icon icon-description)))
	 (unmagnified-block-height
	   (or (getfq icon-attributes-plist 'height)
	       (height-of-icon icon-description)))
	 (reflection-and-rotation?
	   (getfq (icon-attributes-plist entity) 'reflection-and-rotation))
	 delta-right-edge delta-bottom-edge)

    (when (rotated-by-90-p reflection-and-rotation?)
      (psetq unmagnified-block-height unmagnified-block-width
	     unmagnified-block-width unmagnified-block-height
	     x-magnification-with-no-rotation? y-magnification-with-no-rotation?
	     y-magnification-with-no-rotation? x-magnification-with-no-rotation?
	     old-x-magnification-for-current-rotation?
	     old-y-magnification-for-current-rotation?
	     old-y-magnification-for-current-rotation?
	     old-x-magnification-for-current-rotation?))
    (setq delta-right-edge
	  (-w (+w (left-edge-of-block entity)
		  (magnify unmagnified-block-width 
			   x-magnification-for-current-rotation))
	      (right-edge-of-block entity))
	  delta-bottom-edge
	  (-w (+w (top-edge-of-block entity)
		  (magnify unmagnified-block-height 
			   y-magnification-for-current-rotation))
	      (bottom-edge-of-block entity)))
    (when workspace?
      (update-images-of-block entity t nil)
      (update-input-connections-of-entity entity t)
      (magnify-connections-on-block-in-workspace
	entity 
	x-magnification-for-current-rotation y-magnification-for-current-rotation
	old-x-magnification-for-current-rotation? 
	old-y-magnification-for-current-rotation?
	delta-left-edge delta-top-edge
	delta-right-edge delta-bottom-edge)

      (change-icon-attribute
	entity 'x-magnification x-magnification-with-no-rotation?)
      (change-icon-attribute
	entity 'y-magnification y-magnification-with-no-rotation?)

      (change-edges-of-block entity nil nil
			     (+w (right-edge-of-block entity) delta-right-edge)
			     (+w (bottom-edge-of-block entity) delta-bottom-edge))
      
      (when new-left-edge?
	(funcall-method 'shift entity delta-left-edge delta-top-edge)
	(when (and g2-has-v5-mode-windows-p
		   (not ws-protocol-handle-moves-from-edge-change-p))
	  (send-ws-representations-item-moved
	    entity delta-left-edge delta-top-edge)))

      (enlarge-workspace-for-block-and-subblocks-as-necessary entity nil)

      (update-images-of-block entity nil nil)
      (update-input-connections-of-entity entity nil))))

;; NOTE: It is certainly wrong for it to not do anything when workspace? is nil,
;; but changing it might be a bit of a tarpit -- e.g., does code the code that
;; gets called expect an item on a workspace?  Also, are some "advanced" users
;; taking advantage of this feature for advanced "memory management"?  Finally,
;; worry about Jim's optimizations for keeping block/connection info off of
;; transient items not on workspaces.  A small project.  (MHD 3/13/95)


;;; Magnify-connections-on-block-in-workspace adjusts the connections of a block
;;; that is being magnified.  If the connection is not straight, the two links
;;; nearest the block are stretched as needed.  If the connection is straight
;;; and the block at the other end of the connection from the block being
;;; magnified is a loose end, then the connection remains straight and the loose
;;; end is shifted as necessary.  If the connection is straight and the block at
;;; the other end is not a loose end, then a kink is put into the connection
;;; (resulting in the connection now having three links rather than one) and the
;;; two links nearest the block being magnified are stretched as needed.
;;; This is in general consistent with the way that connections are processed
;;; when an icon is moved.  This is appropriate, especially considering that 
;;; the icon can actually be moved as part of the change size option (by clicking
;;; inside the bounding box).

(defun magnify-connections-on-block-in-workspace
       (block x-magnification y-magnification
	old-x-magnification? old-y-magnification?
	delta-left-edge delta-top-edge
	delta-right-edge delta-bottom-edge)
  (loop for connection being each connection of block
	as input-end-object = (input-end-object connection)
	as output-end-object = (output-end-object connection)
	as connection-is-straight? = (connection-is-straight? connection)
	as object-at-other-end-is-loose-end? = nil
	do 
    (cond
      ((eq input-end-object block)
       (setq object-at-other-end-is-loose-end? (loose-end-p output-end-object))
       (when (and connection-is-straight?
		  (not object-at-other-end-is-loose-end?))
	 (put-kink-into-connection-if-straight-1 
	   connection connection-is-straight?))
       (multiple-value-bind
	 (new-end-position delta-x delta-y)
	   (magnify-end-position
	     (input-end-position connection)
	     x-magnification y-magnification block
	     old-x-magnification? old-y-magnification?
	     delta-left-edge delta-top-edge
	     delta-right-edge delta-bottom-edge)
	 (setf (input-end-position connection)
	       new-end-position)
	 (cond
	   ((and connection-is-straight? 
		 object-at-other-end-is-loose-end?)
	    (funcall-method
	      'shift output-end-object
	      delta-x delta-y))
	   (t					; if connection is not straight 
	    (change-connection-deltas-for-object-being-dragged
	      connection block delta-x delta-y)))))
      (t       	; (eq output-end-object block)
       (setq object-at-other-end-is-loose-end? (loose-end-p input-end-object))
       (when (and connection-is-straight?
		  (not object-at-other-end-is-loose-end?))
	 (put-kink-into-connection-if-straight-1 
	   connection connection-is-straight?))
       (multiple-value-bind
	 (new-end-position delta-x delta-y)
	   (magnify-end-position
	     (output-end-position connection)
	     x-magnification y-magnification block
	     old-x-magnification? old-y-magnification?
	     delta-left-edge delta-top-edge
	     delta-right-edge delta-bottom-edge)
	 (setf (output-end-position connection)
	       new-end-position)
	 (cond
	   ((and connection-is-straight?
		 object-at-other-end-is-loose-end?)
	    (funcall-method
	      'shift input-end-object
	      delta-x delta-y))))))))

;; Change-connection-deltas-for-object-being-dragged is used when the connection
;; is not straight and the block is the input end object.  This way, the two
;; links of the connection nearest to the block being magnified rather than the
;; two links furthest from the block being magnified are adjusted.  The name of
;; the function is misleading in this case because the block is being magnified
;; rather than dragged, but it works.  Note that when the block is the output
;; end object, nothing like this has to be done since the last two deltas (for
;; the links nearest the block) are omitted.  See also
;; change-connection-deltas-for-object-being-dragged.


(defun magnify-end-position
       (end-position x-magnification y-magnification block
	old-x-magnification? old-y-magnification?
	delta-left-edge delta-top-edge
	delta-right-edge delta-bottom-edge)
  block
  (let* ((side (get-side-given-end-position end-position))
	 (position-on-side
	   (get-position-on-side-given-end-position end-position))
	 (shift-in-y-direction?
	   (memq side '(left right)))
	 (new-position-on-side
	   (if shift-in-y-direction?
	       (if old-y-magnification?
		   (magnify
		     (inverse-magnify position-on-side old-y-magnification?)
		     y-magnification)
		   (magnify position-on-side y-magnification))
	       (if old-x-magnification?
		   (magnify
		     (inverse-magnify position-on-side old-x-magnification?)
		     x-magnification)
		   (magnify position-on-side x-magnification))))
	 (delta (-w new-position-on-side position-on-side))
	 delta-x delta-y)
    (case side
      (left
       (setq delta-x delta-left-edge
	     delta-y (+w delta delta-top-edge)))
      (top
       (setq delta-x (+w delta delta-left-edge)
	     delta-y delta-top-edge))
      (right
       (setq delta-x (+w delta-left-edge delta-right-edge)
	     delta-y (+w delta delta-top-edge)))
      (bottom
       (setq delta-x (+w delta delta-left-edge)
	     delta-y (+w delta-top-edge delta-bottom-edge))))
    (values
      (combine-side-and-position-on-side-for-end-position
	side new-position-on-side)
      delta-x delta-y)))

;; Inverse-magnify is used here to take into account the old magnification
;; if any.  Thus, the end position if there were no magnification is found
;; using inverse-magnify and the new end position is then found using magnify.
;; Since magnify and inverse-magnify are not perfectly reversible (there is
;; some round-off error) it is possible for pixel errors in the end position
;; of a connection to accumulate if an icon is scaled many times.  However,
;; since an icon is unlikely to be scaled many times, and since even if it is,
;; such pixel errors are very unlikely to be noticed, this is not a serious
;; problem.  The only way I can see to fix this is to somehow save the
;; original end positions along with the magnified ones.  This way, errors
;; wouldn't accumulate.  This is not, however, an elegant solution, especially
;; considering the emphasis on memory efficiency for connections.



;;; `Rotate-and-reflect-icon' ...  If x-center-of-rotation/reflection? and/or
;;; y-center-of-rotation? are nil, center-line values are chosen, with rounding
;;; done in such a way that the lines are always the same relative to the icon
;;; regardless of its orientation, so that repeated operations will not result in
;;; the entity "drifting".

;;; Note that x-center-of-rotation/reflection? and y-center-of-rotation? are in
;;; the user, not the internal, workspace coordinate (sign of y needs is flipped
;;; from the internal perspective).

;;; If note-as-kb-state-change? is true, the original rotation and reflection of
;;; entity is noted before doing anything to it, for purposes of later restoring
;;; it.  Also when note-as-kb-state-change? is true, this will refuse to rotate
;;; or reflect entity if such a change would have to result in the workspace
;;; being enlarged; otherwise, this enlarges the workspace if necessary so that
;;; entity does not extend beyond the margin of the workspace.

(defun rotate-and-reflect-icon
    (entity clockwise-angle-of-rotation-in-degrees reflect-about-x-center?
	    x-center-of-rotation/reflection? y-center-of-rotation?
	    note-as-kb-state-change?)
  ;; change arg (to be 0, 90,180, or 270)
  (setf clockwise-angle-of-rotation-in-degrees	
	(* 90 (mod (round clockwise-angle-of-rotation-in-degrees 90) 4)))
  (let ((delta-rotation-and-reflection		; gets multiplied w/current r&r
	  (case clockwise-angle-of-rotation-in-degrees
	    (0 (if reflect-about-x-center? 'reflected 'normal))
	    (90 (if reflect-about-x-center?
		    'reflected-clockwise-90 'clockwise-90))
	    (180 (if reflect-about-x-center?
		     'reflected-clockwise-180 'clockwise-180))
	    (270 (if reflect-about-x-center?
		     'reflected-clockwise-270 'clockwise-270)))))
    (rotate-and-reflect-icon-symbolically
      entity delta-rotation-and-reflection
      x-center-of-rotation/reflection? y-center-of-rotation?
      note-as-kb-state-change?)
    (when g2-has-v5-mode-windows-p
      (send-ws-representations-item-rotated
	entity
	(getfq (icon-attributes-plist entity) 'reflection-and-rotation)))))



;;; `Rotate-and-reflect-icon-symbolically' rotates entity just as would
;;; rotate-and-reflect-icon, but takes a symbol, delta-rotation-and-reflection,
;;; rather than a the analog arguments of rotate-and-reflect-icon.
;;;
;;; Note that x-center-of-rotation/reflection? and y-center-of-rotation? are in
;;; the user, not the internal, workspace coordinate (sign of y needs is flipped
;;; from the internal perspective).

(defun rotate-and-reflect-icon-symbolically
    (entity delta-rotation-and-reflection
	    x-center-of-rotation/reflection? y-center-of-rotation?
	    note-as-kb-state-change?)
  (let ((do-not-note-permanent-changes-p note-as-kb-state-change?))
    (when note-as-kb-state-change?
      (note-kb-state-change entity 'icon-position)    ; both must be here in this order
      (note-kb-state-change entity 'icon-orientation))
    (when (null x-center-of-rotation/reflection?)
      (setq x-center-of-rotation/reflection?	; changes arg
	    (item-x-position entity)))
    (when (null y-center-of-rotation?)
      (setq y-center-of-rotation?		; changes arg
	    (-w				; flip from user to workspace coordinate system
	      (item-y-position entity))))
    (let ((workspace? (get-workspace-if-any entity)))
      (when (and workspace?
		 (neq delta-rotation-and-reflection 'normal))	    ; identity operation
	(with-updates-to-transfer-representations (entity)
	  (multiple-value-bind
	      (extreme-left-edge extreme-top-edge extreme-right-edge extreme-bottom-edge)
	      (determine-extreme-edges-of-block entity)
	    (update-images-of-rectangle-of-block
	      entity t
	      extreme-left-edge extreme-top-edge
	      extreme-right-edge extreme-bottom-edge)
	    (loop for connection being each connection of entity
		  as input-end-object = (input-end-object connection)
		  as loose-end-maybe
		     = (if (eq input-end-object entity)
			   (output-end-object connection)
			   input-end-object)
		  do
	      (cond
		((loose-end-p loose-end-maybe)
		 (erase-images-of-block loose-end-maybe nil)
		 (reflect-and-rotate-block-in-workspace
		   loose-end-maybe delta-rotation-and-reflection
		   x-center-of-rotation/reflection? y-center-of-rotation?))
		((not (eq input-end-object entity))
		 ;; If input connection, then must erase connection since
		 ;; updating images on entity redraws only output connections.
		 (update-connection-images t workspace? connection))))
	    
	    (reflect-and-rotate-block-in-workspace
	      entity delta-rotation-and-reflection
	      x-center-of-rotation/reflection? y-center-of-rotation?)

	    (multiple-value-setq
		(extreme-left-edge extreme-top-edge extreme-right-edge extreme-bottom-edge)
	      (determine-extreme-edges-of-block entity))
	    (unless note-as-kb-state-change? ;; Note A
	      (enlarge-workspace-if-necessary
		workspace? 
		extreme-left-edge extreme-top-edge
		extreme-right-edge extreme-bottom-edge))
	    ;; Connections have to be redrawn after the entity is rotated
	    ;; because rotating the entity rotates the sides.
	    (update-images-of-rectangle-of-block
	      entity nil
	      extreme-left-edge extreme-top-edge
	      extreme-right-edge extreme-bottom-edge)
	    (update-input-connections-of-entity entity nil)

	    (when (or (<w extreme-left-edge
			  (+w (left-edge-of-block workspace?)
			      (workspace-margin workspace?)))
		      (<w extreme-top-edge
			  (+w (top-edge-of-block workspace?)
			      (workspace-margin workspace?)))
		      (>w extreme-right-edge
			  (-w (right-edge-of-block workspace?)
			      (workspace-margin workspace?)))
		      (>w extreme-bottom-edge
			  (-w (bottom-edge-of-block workspace?)
			      (workspace-margin workspace?))))
	      (when note-as-kb-state-change? ;; But? this is illegal, undo, Note A
		(rotate-and-reflect-icon-symbolically
		  entity
		  (invert-reflection-and-rotation delta-rotation-and-reflection)
		  x-center-of-rotation/reflection? y-center-of-rotation?
		nil)))))
	(update-item-views entity)))))

;; Note A -- If we are noting KB changes then it is illegal for the rotate to
;; expand the workspace size.  We flicker, attempting the rotate, and then
;; undoing it by inverting the rotate.  Meanwhile the expand call must happen
;; when everything is erased.  One weird little detail, the invert call attempts
;; to expand the workspace, but that should be a noop.


;; Other notes:

;; I optimized this by computing extreme edges of entity and supplying them
;; to update-images and by using erase/draw-images-of-block on loose ends,
;; making the assumptions that drawing may be restricted to their block
;; rectangles.
;;
;; An alternative we could consider would be to wrap a dedicated on-image-
;; plane around the whole thing.  This could now enter and leave that macro
;; as many as six times.
;; 
;; This could be optimized further if it could avoid erasing and drawing
;; subblocks of entity, typically name boxes, when just rotating entity.
;; 
;; Note, however, that that could not (necessarily) be done if the whole
;; block would have to shift to keep from enlarging the workspace, which
;; I plan to fix it to do soon.
;;
;; (MHD 10/25/90)

;; I fixed this not to enlarge if note-as-kb-state-change?  is true -- in not the
;; most beautiful way: by undoing it if it turns out to exceed the edges.  AGH and
;; I will hopefully get back to this to fix it so it does not have to draw
;; anything if is going to refuse to change it!!  (MHD 11/12/90)

;; This really ought to be fixed!! - AGH 10/22/91
;; Also, it was wrong to use erase/draw-images-of-block restricting drawing to the
;; loose end.  This caused connections not to be drawn resulting in turding.  -
;; AGH (to MHD), 10/22/91.

;; This must follow the definition of the connection iteration path.

(defun reflect-and-rotate-loose-ends-of-block-in-workspace
       (block reflection-and-rotation?
	 x-center-of-block y-center-of-block)
  (loop for connection being each connection of block
	as loose-end-maybe
	   = (if (eq (input-end-object connection) block)
		 (output-end-object connection)
		 (input-end-object connection))
	when (loose-end-p loose-end-maybe)
	  do 
	    (reflect-and-rotate-block-in-workspace
	      loose-end-maybe reflection-and-rotation?
	      x-center-of-block y-center-of-block)))


(defun reflect-and-rotate-connections-on-block-in-workspace 
       (block reflection-and-rotation)
  (loop with rotated-initial-orientation-horizontal-p
	for connection being each connection of block
	as delta-or-deltas? = (delta-or-deltas connection)
	do 
    (with-connection
      connection t t nil nil
      input-end-x-position input-end-y-position
      output-end-x-position output-end-y-position
      (when (eq input-end-object block)
	(setf (input-end-position connection)
	      (reflect-and-rotate-end-position
		input-end-position reflection-and-rotation block)))
      (when (eq output-end-object block)
	(setf (output-end-position connection)
	      (reflect-and-rotate-end-position
		output-end-position reflection-and-rotation block)))
      (when (and delta-or-deltas?
		 (not (loose-end-p block))
		 (loose-end-p
		   (get-block-at-other-end-of-connection
		     connection block)))
	;; Only adjust connection deltas according to rotation
	;; for connections connected to real blocks (not to 
	;; loose ends.
	(multiple-value-bind
	  (delta-x-multiplier delta-y-multiplier)
	    (reflect-and-rotate-point-in-workspace
	      1 1 reflection-and-rotation 0 0)
	  (setq rotated-initial-orientation-horizontal-p
		(initial-orientation-horizontal-p
		  (get-side-given-end-position
		    (input-end-position connection))))
	  (cond
	    ((numberp delta-or-deltas?)
	     (setf (delta-or-deltas connection)
		   (adjust-delta-according-to-new-orientation
		     delta-or-deltas?
		     rotated-initial-orientation-horizontal-p
		     delta-x-multiplier
		     delta-y-multiplier)))
	    (t
	     (loop for delta in delta-or-deltas?
		   as orientation-horizontal-p 
		      = rotated-initial-orientation-horizontal-p
		      then (not orientation-horizontal-p)
		   collect 
		     (adjust-delta-according-to-new-orientation
		       delta orientation-horizontal-p
		       delta-x-multiplier
		       delta-y-multiplier)
		     into new-deltas using slot-value-cons
		   finally
		     (reclaim-slot-value-list delta-or-deltas?)
		     (setf (delta-or-deltas connection) new-deltas))))))
      )))

(defun adjust-delta-according-to-new-orientation 
       (delta orientation-horizontal-p x-multiplier y-multiplier)
  (*w delta
      (if orientation-horizontal-p x-multiplier y-multiplier)))

(defun reflect-and-rotate-end-position
       (end-position reflection-and-rotation block)
  (let* ((block-width (width-of-block block))
	 (block-height (height-of-block block))
	 (side (get-side-given-end-position end-position))
	 (new-side
	   (reflect-and-rotate-side
	     side reflection-and-rotation))
	 (position-on-side
	   (get-position-on-side-given-end-position end-position)))
    (multiple-value-bind (x y)
	(rotate-point-in-line-drawing-description
	  reflection-and-rotation block-width block-height
	  (case side
	    (left 0)
	    (right block-width)
	    (t position-on-side))
	  (case side
	    (top 0)
	    (bottom block-height)
	    (t position-on-side)))
      (combine-side-and-position-on-side-for-end-position
	new-side
	(if (memq new-side '(left right)) y x)))))

(defun reflect-and-rotate-side
       (side reflection-and-rotation)
  (if (eq reflection-and-rotation 'normal)
      side
      (case side
	(left
	 (case reflection-and-rotation
	   ((clockwise-90 reflected-clockwise-270) 'top)
	   ((clockwise-180 reflected) 'right)
	   ((clockwise-270 reflected-clockwise-90) 'bottom)
	   (reflected-clockwise-180 'left)))
	(right
	 (case reflection-and-rotation
	   ((clockwise-90 reflected-clockwise-270) 'bottom)
	   ((clockwise-180 reflected) 'left)
	   ((clockwise-270 reflected-clockwise-90) 'top)
	   (reflected-clockwise-180 'right)))
	(top
	 (case reflection-and-rotation
	   ((clockwise-90 reflected-clockwise-90) 'right)
	   (reflected 'top)
	   ((clockwise-270 reflected-clockwise-270) 'left)
	   ((clockwise-180 reflected-clockwise-180) 'bottom)))
	(t  ; if bottom
	 (case reflection-and-rotation
	   ((clockwise-90 reflected-clockwise-90) 'left)
	   (reflected 'bottom)
	   ((clockwise-270 reflected-clockwise-270) 'right)
	   ((clockwise-180 reflected-clockwise-180) 'top))))))

;; The purely arithmetic method for calculating the new side doesn't
;; work in cases where the position on side or the block height or width is
;; 0 (as is the case with some loose-ends.  Therefore,
;; reflect-and-rotate-side, which uses a tabular method, has been
;; implemented.


(defun toggle-side-for-loose-end (loose-end connection)
  (let* ((output-end-object (output-end-object connection))
	 (end-position
	   (combine-side-and-position-on-side-for-end-position
	     (case (get-side-given-end-position
		     (if (eq output-end-object loose-end)
			 (output-end-position connection)
			 (input-end-position connection)))
	       ((left right) 'top)
	       (t 'left))
	     0)))
    (if (eq output-end-object loose-end)
	(setf (output-end-position connection) end-position)
	(setf (input-end-position connection) end-position))))


;;;; Notes

;; 6.  User Interface Capabilities
;; Write a spec on this.
;; a. last two segments stretch
;; b. click near loose end to close connection
;; c. click back along path to erase
;; d. click near connection of same type to automatically create
;;    a "T" or "cross" junction.
;; e. pull connection into an icon to add a connection
;; f. double-click to leave as loose end
;; g. click near port to delete connection
;; h. should be able to move a stub location
;; i. Should be two options for dragging an icon: 
;;    1) connections disappear
;;    2) connections stretch as icon moves
;; j. It should be possible to move a set of icons together.
;; 
;; 7. Animation in connections
;; Change interior color.  Color map changes to show flow.  
;; "Real" animation, maybe with bubbles, moving proportionally with rate
;; of flow.
;; 
;; 8. Forget subblocks for now, at least as abstractions of ports.
;; 
;; 9. Workspaces can have connections inside (to correspond to entity 
;; "black box" view).
;; 
;; 11. Ends of connections are drawn into the icon rectangle up to non-zero
;; pixels.  Lowell has to do some work here.  It may be possible to do this
;; based on line drawing descriptions rather than pixels.
;; 
;; 13. When connection is being edited, will probably need a more complicated
;; "object in transit".  This object only exists temporarily, while the
;; connection is being edited; it does not affect kb saving or loading.
;;
;; 14. Need arrows on connections indicating direction if any.  For connections
;; with narrow cross-sections, it is probably o.k. to use wing type arrows.
;; For fatter connections, the arrow, perhaps an icon, should go separately
;; along side, or perhaps inside, the connection.

;; Talked to Mike about attributes and ports.  Ports will go away; all
;; connections will be in connections slot of icon.  We considered
;; putting all attributes into one slot as well since they are all
;; look-up slots anyway.  We probably shouldn't do this because we would
;; then lose some basic slot capabilities provided for frames (such as
;; slot types, checkers, putters, writers, etc.)


;;;; Inference Engine Requirements for Ports and Connectors

;; These are old notes from Mike.

;;; (1) For any entity or box possibly having ports, to be able to find
;;; out if it has a port of a given name, to find out if it has ports
;;; and how many, and to be able to find the names of the ports and the
;;; connectors in the ports if any by an efficient iteration path.

;;; (2) Given an entity or box, and a port name, to be find the
;;; connector if any in the port.

;;; (3) Given a connector, to find the entity on the other end if any,
;;; and the name of the port it is attached to. Also to know whether the
;;; connector is directional, if so which end one has entered.

;;; (4) Given a connector, to find out its type and whether it has an
;;; entity identified with it.


;;; (loop for (name direction connector) being port-values of
;;; <entity-or-table> ...)  provides three iteration variables for the
;;; name of the port, its directionality (see below), and its connector
;;; if any. A connector is not neccessarily a frame. It might be a list
;;; for example.

;;; (get-port-values <entity-or-box> <port-name>) Values are (1) input,
;;; output or bi-directional; and (2) the connector if any otherwise
;;; nil.

;;; (get-connector-values <connector>) Values are (1) frame at one end
;;; if any, (2) frame at other end if any, (3) type of connector, (4)
;;; entity associated with connector if any. If the port is directional,
;;; then the first value is its inlet and its second is its outlet.
;;; Since you presumably have one of these, the other is what is at the
;;; other end.

;;; I assume that junctions are entities and that algorithms that see
;;; through junctions are built at a higher level.


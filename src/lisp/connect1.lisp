;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module CONNECT1

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Andreas Hofmann




;;;; Introduction

;;; CONNECT1 contains the primitive data structure, memory management, and
;;; loop path definitions for the connections facility.  The core code related
;;; to connections is in CONNECT2.  Editing functions are in CONNECT3.







;;;; Forward References

(declare-forward-references
  (basis-kb-frame-serial-number              variable kb-load2)
  (push-last-spot                            function workstation)
  (note-change-of-connection-for-drawing     function connect3a)
  (note-deletion-of-connection-for-drawing   function connect3a)
  (note-change-to-connection-2               function kb-save1)
  (note-deletion-of-connection-2             function kb-save1)
  (invoke-rules-for-direct-connection-chaining function chaining)
  (invoke-rules-for-indirect-connection-chaining function chaining)
  (in-suspend-resume-p variable activate)
  (send-ws-representations-item-remove-as-subblock function events-g2))

(declare-forward-references
  (compute-connection-vertices function connect2)
  (update-connection-images function connect2)
  #+development
  (connection-connected-to-block-p function connect2)
  (get-direction-of-connection function connect2)
  (selection-handles-visible-p function moves)
  (push-selection-handle-spot function moves)
  (connection-line-pattern-dashes function grammar6a)
  (connection-line-pattern-absolute-p function grammar6a)
  (lookup-stock-line-pattern-element function grammar6a)
  (connection-line-pattern-explicit-p function grammar6a)
  (put-attribute-value function install))





;;;; Cons Storage Allocation

(defconser connection)




;;;; Connection Definitions

;;; A connection will always have an input-end-object and an output-end-object.
;;; The input and output end positions are specified in terms of side
;;; and position on side of the end object.  The side and position on side
;;; are combined into one value (see above accessor macros).
;;; The lengths of the connection links are specified by delta-or-deltas.
;;; The ordering of the deltas is from input-end-object to output-end-object.
;;; The last two deltas are omitted since they are redundant because all
;;; connections have an output-end-object.



(def-structure (connection
		 (:constructor make-connection))
  (connection-frame-or-class nil)	; a frame or class
  (output-end-object-internal nil)	; an entity or nil
  (input-end-object-internal nil)	; an entity or nil
  (output-end-position-internal nil)	; Packed integer of pos and 2 bits for side, or nil
  (input-end-position-internal nil)	; ditto
  (delta-or-deltas-internal nil)	; an integer, list of integers, or nil
  (connection-flags 0)			; See def-connection-flag, below.
  (runtime-structures-affected-by-this-connection nil)
  (connection-attributes-plist nil)
  (frame-serial-number-for-connection nil)
  (layer-position-of-connection 0))     ; New. -fmw, 1/16/95


(defun connection-p-function (thing)
  (connection-p thing))

;; Referenced in FRAMES5

(defun frame-serial-number-for-connection-function (connection)
  (frame-serial-number-for-connection connection))


;;;; Connection Flags


(defparameter savable-connection-flags 1)


;;; Summary of connection flags
;;; 0 connection-not-directed?
;;; 1 connection-permanently-changed
;;; 2 connection-has-been-written
;;; 3 connection-existed-at-start-of-save
;;; 4 connection-overlap-cache
;;; 5 connection-overlap-cache-valid
;;; 6 transient-connection
;;; 7 connection-needs-indexing
;;; 8 connection-being-deleted
;;; 9 connection-found-in-search

(defmacro def-connection-flag (flag-name bit-index
					 &key test-name set-name
					 clear-name savable?)
  (let ((flag-mask (ash 1 bit-index)))
    `(progn
       (define-flag-bit ,flag-name (connection-flags connection) ,bit-index
			:set ,set-name
			:clear ,clear-name
			:test ,test-name
			:for-connection t)
       ,@(when savable?
	   `((setq savable-connection-flags
		   (logiorf savable-connection-flags ,flag-mask))))
       ',flag-name)))



(def-connection-flag connection-not-directed-internal 0)

(def-connection-flag connection-permanently-changed 1)

(def-connection-flag connection-has-been-written 2)

(def-connection-flag connection-existed-at-start-of-save 3)



;;; The connection-flag `connection-overlap-cache' is the same as
;;; the frame flag `block-overlap-cache,' except it's for connections.
;;; It is not saveable.
;; -fmw, 8/9/94

(def-connection-flag connection-overlap-cache 4)
(def-connection-flag connection-overlap-cache-valid 5)

(def-connection-flag transient-connection 6 :savable? t)


;;; The connection-flag `connection-needs-indexing' is set when
;;; the connection's region has changed and it is on the workspace's
;;; list of connections awaiting reindexing (for the spacial index).
;; -fmw, 1/22/95

(def-connection-flag connection-needs-indexing 7)


(def-connection-flag connection-being-deleted 8)



;;; The connection flag `connection-found-in-search' is simply the connection
;;; analog of the non-savable frame flag block-found-in-search.  The function
;;; `clear-connections-found-in-search' clears the flag in each element of its
;;; argument list of connections.

(def-connection-flag connection-found-in-search 9)

(defun-simple clear-connections-found-in-search (connections)
  (loop for connection in connections
	do (clear-connection-found-in-search connection)))



;;; The variable `geometric-change-to-connection-is-temporary-p', normally NIL,
;;; is bound to T when making some temporary change to a connection's geometry.
;;; This inhibits the invalidation of connection indexing.

(defvar geometric-change-to-connection-is-temporary-p nil)



;;;; Connection accessors



;;; The macro `note-change-to-connection' notes changes to most connection
;;; slots as a KB change, or as something which invalidates the connection's
;;; region for drawing.  Slots watched include input-end, output-end, deltas,
;;; directedness, input-position, output-position, or style.

(defmacro note-change-to-connection (connection-structure)
  (avoiding-variable-capture (connection-structure)
    `(when (or noting-changes-to-kb-p
	       (and (null (connection-needs-indexing-p ,connection-structure))
		    (not geometric-change-to-connection-is-temporary-p)))
       (note-change-to-connection-1 ,connection-structure))))


(defun-void note-change-to-connection-1 (connection-structure)
  (unless (or (connection-being-deleted-p connection-structure)
	      (connection-needs-indexing-p connection-structure))
    (note-change-of-connection-for-drawing connection-structure))

  (when noting-changes-to-kb-p
    (note-change-to-connection-2 connection-structure)))

;; Called for change to (almost) any slot of connection.		


;;; The function `note-deletion-of-connection' is called just before
;;; a connection is deleted for any reason.  Note that this should always be
;;; called before any code that deletes the connection frame since the call
;;; here to invoke-rules-for-direct-connection-chaining can cause a connection
;;; frame to be created for the connection.

(defun note-deletion-of-connection (connection-structure)
  (when g2-has-v5-mode-windows-p
    ;;(format t "DELETING A CONNECTION~%")
    (send-ws-representations-item-remove-as-subblock connection-structure nil))
  (unless (connection-being-deleted-p connection-structure)
    (setf (connection-being-deleted-p connection-structure) t)
    (note-deletion-of-connection-for-drawing
      connection-structure)
    (when noting-changes-to-kb-p
      (note-deletion-of-connection-2 connection-structure))
    (invoke-rules-for-direct-connection-chaining connection-structure t)
    (invoke-rules-for-indirect-connection-chaining connection-structure t)))



;;; The following accessors are defined to abstract noting kb changes.


(defmacro output-end-object (connection)
  `(output-end-object-internal ,connection))

(defmacro set-output-end-object (connection value)
  (avoiding-variable-capture (connection)
    `(progn
       (note-change-to-connection ,connection)
       (setf (output-end-object-internal ,connection) ,value))))

(defsetf output-end-object set-output-end-object)



(defmacro input-end-object (connection)
  `(input-end-object-internal ,connection))

(defmacro set-input-end-object (connection value)
  (avoiding-variable-capture (connection)
    `(progn
       (note-change-to-connection ,connection)
       (setf (input-end-object-internal ,connection) ,value))))

(defsetf input-end-object set-input-end-object)

	   
(defmacro output-end-position (connection)
  `(output-end-position-internal ,connection))

(defmacro set-output-end-position (connection value)
  (avoiding-variable-capture (connection)
    `(progn
       (note-change-to-connection ,connection)
       (setf (output-end-position-internal ,connection) ,value))))

(defsetf output-end-position set-output-end-position)


(defmacro input-end-position (connection)
  `(input-end-position-internal ,connection))

(defmacro set-input-end-position (connection value)
  (avoiding-variable-capture (connection)
    `(progn
       (note-change-to-connection ,connection)
       (setf (input-end-position-internal ,connection) ,value))))

(defsetf input-end-position set-input-end-position)

(defmacro delta-or-deltas (connection)
  `(delta-or-deltas-internal ,connection))

(defmacro set-delta-or-deltas (connection value)
  (avoiding-variable-capture (connection)
    `(progn
       (note-change-to-connection ,connection)
       (setf (delta-or-deltas-internal ,connection) ,value))))

(defsetf delta-or-deltas set-delta-or-deltas)



;;;; Connection Flag Accessors



;;; Alternate names ending in ? rather than -p because of existing usage.

(def-substitution-macro connection-not-directed? (connection)
  (connection-not-directed-internal-p connection))

(def-substitution-macro connection-directed? (connection)
  (not (connection-not-directed-internal-p connection)))



(defmacro set-connection-not-directed (connection)
  (avoiding-variable-capture (connection)
    `(progn
       (note-change-to-connection ,connection)
       (set-connection-not-directed-internal ,connection))))

(defmacro set-connection-directed (connection)
  (avoiding-variable-capture (connection)
    `(progn
       (note-change-to-connection ,connection)
       (clear-connection-not-directed-internal ,connection))))



(defmacro permanent-connection-p (connection)
  `(not (transient-connection-p ,connection)))


(defmacro connection-has-been-reprocessed-p (connection reference-serial-number)
  (let ((frame-serial-number (gensym)))
    `(let ((,frame-serial-number (frame-serial-number-for-connection ,connection)))
       (or (frame-serial-number-equal ,frame-serial-number (frame-serial-number-recycled))
	   (frame-serial-number-> ,frame-serial-number ,reference-serial-number)))))

(defmacro connection-has-not-been-reprocessed-p (connection reference-serial-number)
  `(not (connection-has-been-reprocessed-p ,connection ,reference-serial-number)))



;;; The function `connection-frame-of-connection?' returns the connection frame
;;; which is associated with the connection structure, if one has been created.

(defun connection-frame-of-connection? (connection-structure)
  (let ((frame-or-class (connection-frame-or-class connection-structure)))
    (when (framep frame-or-class)
      frame-or-class)))

;; This should use the cheaper symbolp test, as below! However, first make sure
;; callers aren't now depending on the additional functionality of framep, i.e.,
;; a semi-reliable deleted-frame test. (MHD 10/25/04)



;;; The function `connection-class-of-connection' returns the connection class
;;; assocated with the connection structure.

(defun connection-class-of-connection (connection-structure)
  (let ((frame-or-class (connection-frame-or-class connection-structure)))
    (if (symbolp frame-or-class)
	frame-or-class
	(class frame-or-class))))

(defmacro connection-in-use-p (connection)
  `(not (frame-serial-number-equal
	  (frame-serial-number-for-connection ,connection)
	  (frame-serial-number-recycled))))


;; Runtime-structures-affected-by-this-connection is used to 
;; uncache runtime structures when the connection is edited
;; (see INSTALL, SIMULATE).  This slot is not saved.  Note that slots
;; that are not saved can simply be added to this structure;  the load and
;; save functions in FILES, which handle connections as a special case,
;; will simply ignore them.

;; Save-kb assumes that a connection is a simple named vector.

;; Consider saving the connection-not-directed? slot by grabbing a bit from
;; output-end-position, which is hacked up anyway.



(defun workspace-of-connection? (connection-structure)
  ;; return immediately on NIL
  (unless connection-structure
    (return-from workspace-of-connection?))
  (let ((input-end? (input-end-object connection-structure))
	(output-end? (output-end-object connection-structure)))
    (or
      (and input-end? (framep input-end?)
	   (get-workspace-if-any input-end?))

      (and output-end? (framep output-end?)
	   (get-workspace-if-any output-end?)))))

;; During the deletion of the output-end of a connection (which is the owner),
;; the connection is deleted in the recursive descent of delete-frame, via
;; reclaim-connections-value.  At this point, the input-end of the connection
;; has already had its superblock set to NIL.  the output-end of the connection
;; is OK though, so we get the workspace from there, too. -fmw, 1/24/95

(defun-simple get-module-connection-is-in (connection-structure)
  (get-module-block-is-in (input-end-object connection-structure)))

(defun-simple connection-within-module-p (connection-structure module)
  (eq (get-module-block-is-in (input-end-object connection-structure)) module))




;;;; Invisible-Entity and Loose-End



(def-class (invisible-entity entity define-predicate)
  (icon-description nil))

(def-class (loose-end entity define-predicate)
  (icon-description nil))

(defun-simple loose-end-p-function (frame)
  (loose-end-p frame))

(def-spot loose-end-spot
    :slots nil
    :include spot
    :enclosing-spot-type image-plane-spot
    :innermost-spot-p t
    :abstract-type nil
    :type-of-frame-represented object)

(def-class-method generate-spot (loose-end mouse-pointer)
  (push-last-spot mouse-pointer (make-loose-end-spot) loose-end))




;;;; Connection Primitives



;;; `Combine-side-and-position-for-end-position' takes a side 
;;; (left, right, top, or bottom), and a position (an integer),
;;; and combines them into the end-position format for connections.

(defmacro combine-side-and-position-on-side-for-end-position (side position)
  `(+f (case ,side (top 0) (left 1) (bottom 2) (t 3))
       (ashf ,position 2)))

;; Note that it is an error for the integer length of position to exceed
;; 
;;   (- (integer-length most-positive-gensym-fixnum) 2)
;;
;; Put checks in at a higher level!!  The constant most-positive-gensym-fixnum
;; is (or should be) the least positive value for most-positive-fixnum on any
;; platform supporting Gensym software. (MHD)



;;; `Get-side-from-end-position' retrieves the side (left, right, top, or
;;; bottom) from an end-position.

(defmacro get-side-given-end-position (end-position)
  `(svref '#(top left bottom right) (logandf ,end-position #2r11)))

(defmacro horizontal-end-position-p (end-position)
  `(=f 1 (logandf ,end-position 1)))


;;; `Get-position-from-end-position' retrieves the position (an integer) from
;;; an end-position.

(defmacro get-position-on-side-given-end-position (end-position)
  `(ashf ,end-position -2))



(def-substitution-macro output-connection-p (block connection)
  (eq (input-end-object connection) block))

(def-substitution-macro input-connection-p (block connection)
  (eq (output-end-object connection) block))

(defun output-connection-p-function (block connection)
  (output-connection-p block connection))


(def-substitution-macro render-connection-in-xor-overlay-p
    (connection)
  (or (render-frame-in-xor-overlay-p (input-end-object connection))
      (render-frame-in-xor-overlay-p (output-end-object connection))))

(defun render-connection-in-xor-overlay-p-function (connection)
  (render-connection-in-xor-overlay-p connection))

;; Forward referenced, e.g., from ENTITIES, via do-color-revision. (MHD 6/3/02)






;;; The macro `edge-of-side-of-block' takes a side (LEFT, TOP, RIGHT, or BOTTOM)
;;; and returns the edge of corresponding side of block.

(def-substitution-macro edge-of-side-of-block (side block)
  (case side
    (left (left-edge-of-block block))
    (top (top-edge-of-block block))
    (right (right-edge-of-block block))
    (t (bottom-edge-of-block block))))


;;;; Connection Frame Definitions


;;; These frames specify format and other information.

(def-substitute-for-old-class default-connection-class connection)

;; Default-connection-class has been replaced by connection in connection
;; definitions.  Default-connection-class was originally used so that there
;; wouldn't be any confusion with connection, the structure.  Connection-p is
;; now used so there isn't any problem here anymore.  Default-connection class
;; remains for old knowledge bases.



;;; `Connection' is the root class from which all connections inherit.

(def-class (connection (item entity) (foundation-class connection))
  (cross-section-pattern
    ((foreground . 1)) vector-slot user-overridable system save
    (attribute-export-comment
      "Export: ( [color: color-symbol, width: integer] *), writable: true,"))
  (cross-section-pattern-for-class
    nil lookup-slot system class-slot do-not-save (type cross-section-pattern)
    not-user-editable no-accessor do-not-put-in-attribute-tables user-overridable
        (attribute-export-comment
      "Export: ( [color: color-symbol, width: integer] *), writable: true,"))
  (stub-length
    20 system user-overridable
    (attribute-export-comment "Export: integer-or-none, writable: true,"))
  (stub-length-for-class
    nil lookup-slot system class-slot do-not-save (type stub-length) 
    not-user-editable no-accessor do-not-put-in-attribute-tables user-overridable
    (attribute-export-comment "Export: integer-or-none, writable: true,"))
  (junction-block-class
    default-junction system user-overridable
    (attribute-export-comment "Export: class-name, writable = true"))
  (junction-block-class-for-class
    nil lookup-slot system class-slot do-not-save (type junction-class)
    not-user-editable no-accessor do-not-put-in-attribute-tables user-overridable
    (attribute-export-comment "Export: class-name, writable = true"))
  (connection-for-this-connection-frame	; made a vector slot -- overdue!
    nil vector-slot system		;   (MHD 10/8/93)
    (attribute-export-comment
      "Export as alias: connection-part or connection, ~
	type struct, writable = true"))
  (connection-style
    orthogonal (type connection-instance-style) system do-not-save
    (attribute-export-comment
      "Exported: Type is (member seq(diagonal orthogonal)), writable = ~
	true"))

  (connection-arrows
    nil (type connection-arrows) system do-not-save
    (attribute-export-comment "Exported: Type is TBD, writable = true"))

  (line-pattern				; NIL means solid
    nil (type connection-line-pattern) system do-not-save
    (attribute-export-comment
      "Exported: Type is (or solid (member seq (dash dot))), writable = true")))

;; Connection-style is a slot in connections to allow users to edit the style of
;; individual connections.  It is always consistent with the connection attributes
;; plist style.  It is not saved since the information is in the connection
;; attributes plist.

;; The same goes for line-pattern, added for 6.2 -fmw, 5/21/02

(defmacro connection-frame-p (frame)
  `(frame-of-class-p ,frame 'connection))

(defun workspace-of-connection-frame (connection-frame)
  (let ((connection?
	  (connection-for-this-connection-frame
	    connection-frame)))
    (workspace-of-connection? connection?)))

(declare-forward-reference decache-roles-for-entities-related-to-this-connection function)
(declare-forward-reference decache-roles-for-connection-post-and-namesakes function) ; in ROLES

(def-class-method deactivate (connection)
  (unless in-suspend-resume-p
    (when (active-p connection)
      (let ((current-computation-flags current-computation-flags))
	(setf (role-serve-inactive-objects?) t)
	(decache-roles-for-entities-related-to-this-connection
	  (connection-for-this-connection-frame connection)))))
  (funcall-superior-method connection)
  nil)

(def-class-method activate (connection)
  (unless in-suspend-resume-p
    (unless (active-p connection)
      (let ((current-computation-flags current-computation-flags))
	(setf (role-serve-inactive-objects?) t)
	(decache-roles-for-entities-related-to-this-connection
	  (connection-for-this-connection-frame connection)))))
  (funcall-superior-method connection)
  nil)

;;; The `cross-section-pattern' slot is either of the form (regions .  stripes)
;;; or just stripes.  Regions is a list of (region .  color) pairs and stripes
;;; is a list of (color-or-region .  width) pairs.  The stripes form completely
;;; specifies the order and width of the connection stripes.  The optional
;;; regions form allows identification of stripes by region name so that these
;;; can be changed individually by rule action or edit.

;;; Note that only the stripes form is needed by
;;; generate-connection-subrectangle-structures.  Thus, one set of subrectangle
;;; structures can be used for drawing all connections of a particular class,
;;; even if they have different colors.  See also DEFINITIONS, GRAMMAR2, and
;;; CONNECT2.

(def-concept cross-section-pattern)

(def-substitution-macro make-cross-section-pattern (regions stripes)
  (if regions
      (slot-value-cons regions stripes)
      stripes))

(def-substitution-macro cross-section-regions-specified?
    (cross-section-pattern)
  (consp (caar cross-section-pattern)))


(def-substitution-macro get-cross-section-regions (cross-section-pattern)
  (when (cross-section-regions-specified? cross-section-pattern)
    (car cross-section-pattern)))

(defun get-cross-section-regions-function (cross-section-pattern)
  (get-cross-section-regions cross-section-pattern))

(def-substitution-macro get-cross-section-stripes (cross-section-pattern)
  (if (cross-section-regions-specified? cross-section-pattern)
      (cdr cross-section-pattern)
      cross-section-pattern))




(def-class (object (item entity) (foundation-class object) not-user-instantiable
		   do-not-put-in-menus))

(def-class (default-junction object (foundation-class default-junction)
	     define-predicate not-user-instantiable
	     do-not-put-in-menus)
  (icon-description
    (:funcall-at-load-time
      create-icon-description
      8 8 ((outline (0 0) (8 0) (8 8) (0 8))))))

;;; Instances of this class' subclasses can be shared across factions.
#+mtg2
(def-class (shareable-object object (foundation-class shareable-object)
			     not-user-instantiable do-not-put-in-menus)
    (shared #.falsity vector-slot system user-overridable save
						    (type truth-value)))


;;; A connection post is a subclass of entity.  It is not an item, and subclasses
;;; cannot be defined by the user.  It has only one attribute that is user 
;;; editable:  name-or-names-for-frame.  A connection post can be instantiated
;;; via the "new object" menu selection, or by cloning.  It can be placed 
;;; anywhere on a workspace, just like any object.

; Not sure why the above comment says that `connection-post' can't be subclassed

(def-class (connection-post object
			    (foundation-class connection-post) define-predicate)
  (icon-description
    (:funcall-at-load-time
      create-icon-description
      20 20 ((outline (0 0) (0 20) (20 20) (20 0))
	     (circle (1 10) (10 1) (19 10))
	     (lines (4 4) (16 16))
	     (lines (4 16) (16 4))
	     )))
  (superior-connection
    nil (type stub-designation-or-none) lookup-slot system)
  (superior-connection-cache nil lookup-slot system do-not-clone))

(defun-simple connection-post-equal (connection-post-1 connection-post-2)
  (or (eq connection-post-1 connection-post-2)
      (let ((name-or-names-1 (name-or-names-for-frame connection-post-1))
	    (name-or-names-2 (name-or-names-for-frame connection-post-2)))
	(name-or-names-like-p name-or-names-1 name-or-names-2))))

(declare-forward-reference remove-subworkspace-connection-post-from-connection
			   function)

(def-class-method cleanup (connection-post)
  (funcall-superior-method connection-post)
  (let ((superior-connection-cache
	  (superior-connection-cache connection-post)))
    (when superior-connection-cache
      (remove-subworkspace-connection-post-from-connection
	(cdr superior-connection-cache)
	connection-post
	(eq (car superior-connection-cache) 'input)
	t))))




;;; The `note-name-change connection-post' method, in addition to invoking the
;;; usual method of its superior, invalidates connection-post role caches for
;;; both the old and new set of names.

(def-class-method note-name-change (connection-post old-names initializing-p)
  (unless initializing-p		; see Note below
    (decache-roles-for-connection-post-and-namesakes connection-post old-names))
  (funcall-superior-method connection-post old-names initializing-p)
  (unless initializing-p
    (decache-roles-for-connection-post-and-namesakes
      connection-post (name-or-names-for-frame connection-post))))

;; Note: this role decaching for connection posts is needed before and after the
;; name of the frame is modified.  (See above.)  - rdf, cpm, 10/6/95
;;
;; --- UPDATE: it's now been modified slightly: if the names do not change, do
;; not do any decaching (by virtue of the guarantee provided by the slot putter
;; that this method will not be invoked in such a case). Note also that in the
;; initializing case, nothing is done.  If it wanted to be done, it would not be
;; appropriate here because not enough can be assumed about other slots.  In
;; practice, names are never preserved on clone and never are given as an
;; initialization.  Therefore there are no bugs in practice. If names
;; initialization could be non-nil, or names could be cloned, the way could be
;; handled would be to use the initialize method for the creation case, and have
;; special code in clone-frame for the cloning case.  There is a post-loading
;; method, install-connection-posts-after-loading, to handle the recreation
;; (KB-loading) case.  Further cleanup is conceivable!  (MHD 5/30/02)



(def-substitute-for-old-class terminal-post connection-post)




;;;; Connection Attributes Plist

;;; The `connection attributes plist' may have the following properties

;;;        connection-style 
;;;        input-end-subworkspace-connection-posts  
;;;        output-end-subworkspace-connection-posts  
;;;        overlapping-blocks

;;; Connection-style is nil if orthogonal.  It can also be 'diagonal, and perhaps
;;; 'spline eventually.  Note that the connection-style slot in a connection frame
;;; will contain 'orthogonal (rather than nil) if the connection is orthogonal.

;;; Input-end-subworkspace-connection-posts and
;;; output-end-subworkspace-connection-posts are connection posts on subworkspaces
;;; to be role served by the connection role servers (see CONNECT4).

;;; The connection attributes plist should only be changed using
;;; change-connection-attribute, defined below.  All strings and conses (to all
;;; levels) contained in a connection attributes plist must be unshared.  They are
;;; reclaimed upon deletion or upon a change via change-connection-attribute.



;;; `Change-connection-attribute' makes the connection attributes plist of
;;; connection have the property specified by indicator and value?  or, if value?
;;; is nil, not have a property under indicator.  Strings and conses making up the
;;; structure are recycled as necessary.  Slot value consing is done as necessary.
;;; Value? is returned after being stored. Note that value? is not copied.

(defun change-connection-attribute (connection indicator value?)
  (note-change-to-connection connection)
  (change-connection-attribute-1 connection indicator value?))

(defun change-connection-attribute-1 (connection indicator value?)
  (loop as l-trailer? = nil then (cdr l)
	as l = (connection-attributes-plist connection)
	     then (cdr l-trailer?)
	while l
	when (eq (car l) indicator)
	  do (cond
	       (value?
		(reclaim-slot-value (cadr l))		    ; Old value must be a slot-value.
		(setf (cadr l) value?))
	       (t (if l-trailer?
		      (setf (cdr l-trailer?) (cddr l))
		      (setf (connection-attributes-plist connection) (cddr l)))
		  (setf (cddr l) nil)
		  (reclaim-slot-value l)))
	     (return value?)
	finally
	  (if value?
	      (setf (connection-attributes-plist connection)
		    (slot-value-cons
		      indicator
		      (slot-value-cons
			value?
			(connection-attributes-plist connection)))))
	  (return value?)))

;; Consider abstracting this and similar code in change-icon-attribute and in
;; change-text-box-property!  Consider using get-gensym-plist-element (see INT3).



(defmacro connection-diagonal-p (connection)
  `(let ((plist (connection-attributes-plist ,connection)))
     (and plist
	  (eq (getfq plist 'connection-style)
	      'diagonal))))

(defmacro connection-orthogonal-p (connection)
  (let ((connection-style-name (gensym)))
    `(let ((,connection-style-name
	      (getfq (connection-attributes-plist ,connection) 
		'connection-style)))
       (or (null ,connection-style-name)
	   (eq ,connection-style-name 'orthogonal)))))


;;; The macro `connection-style-of-connection' returns NIL or ORTHGONAL.

(defmacro connection-style-of-connection (connection)
  `(or (getfq (connection-attributes-plist ,connection) 
	      'connection-style)
       'orthogonal))

(defun connection-arrows-of-connection (connection)
  (let ((plist (connection-attributes-plist connection)))
     (and plist (getfq plist 'connection-arrows))))


;;; The macro `connection-overlapping-blocks-cache' is a setf-able
;;; place.  It actually contains a slot-value-list of overlapping
;;; blocks or connections.

(defmacro connection-overlapping-blocks-cache (connection)
  `(getfq (connection-attributes-plist ,connection)
	  'overlapping-blocks))
  
(defmacro set-connection-overlapping-blocks-cache (connection new-value)
  `(change-connection-attribute-1 ,connection 'overlapping-blocks ,new-value))

(defsetf connection-overlapping-blocks-cache set-connection-overlapping-blocks-cache)


(defun connection-line-pattern (connection)
  (let ((plist (connection-attributes-plist connection)))
     (and plist (getfq plist 'line-pattern))))



;;; The function `compute-scaled-line-pattern' returns a new gensym-list of the
;;; dash lengths (as fixnums in window coordinates) for the given line-pattern.
;;; This is where we lookup the built-in patterns, and scale by the line width
;;; (or not).  Note that the built-in Win32 line patterns (PS_DOT, etc), which
;;; we are no longer using, scale by line width automatically.

(defun compute-scaled-line-pattern (line-pattern scale total-width)
  (macrolet ((scale (length)
	       `(progn
		  (if absolutep
		      (scalef scale ,length)
		      (scalef scale (*f ,length total-width))))))
    (when line-pattern			; Minor optimization.
      (let ((dashes (connection-line-pattern-dashes line-pattern))
	    (absolutep (connection-line-pattern-absolute-p line-pattern))
	    (result nil))
	(loop for dash in dashes doing
	  (cond ((symbolp dash)
		 (loop for length in (lookup-stock-line-pattern-element dash) doing
		   (gensym-push (scale length) result)))
		((fixnump dash)
		 (gensym-push (scale dash) result))
		(t
		 (dwarn "Junk in line-pattern: ~s" dash))))
	(setq result (nreverse result))
	(cond ((loop for length in result	   ; Scaled down to all zeroes, revert to solid.
		     always (=f length 0))
	       nil)
	      ((connection-line-pattern-explicit-p line-pattern)
	       result)
	      (t
	       ;; And now a little heuristic which improves the appearance:
	       ;; equalize space lengths to the min (or max, or mean...).  Don't
	       ;; apply the heuristic if user gave us an explicit list of lengths,
	       ;; though.
	       (let ((minoff (loop for (on off) on result by 'cddr
				   minimize off)))
		 (loop for offcons on (cdr result) by 'cddr doing
		   (setf (car offcons) minoff))
		 result)))))))



;;; A hash table for connections-v2:
;;;
;;;   key: connection (structure)
;;; value: #S(connection output-names input-names duplicated?)

#+connections-v2
(eval-when (:compile-toplevel :load-toplevel :execute)

(def-structure (connection-item
		 (:type vector)
		 (:creations-at-a-time 100)
		 (:constructor
		   make-connection-item
		   (connection-item-connection))
		 (:reclaimer reclaim-connection-item))
  connection-item-connection
  (connection-item-output-names nil)
  (connection-item-input-names nil)
  (connection-item-duplicated? nil)
  ;; The following two slots are used in `clone-connections-for-block'.
  (connection-item-output-marked? nil)
  (connection-item-input-marked? nil))

(def-skip-list-or-binary-tree connection-item-table
  :constructor make-connection-item-table
  :accessor get-connection-item
  :key-deleter delete-connection-item
  :reclaimer reclaim-connection-item-table
  :hash-function sxhash-lisp-object
  :max-level 7)

(defun-simple connection-item-name-or-names (connection-item)
  (nconc (copy-list-using-scope-conses (connection-item-output-names connection-item))
	 (copy-list-using-scope-conses (connection-item-input-names connection-item))))

) ; eval-when

#-connections-v2
(defmacro reclaim-connection-item-table (connections)
  `(reclaim-slot-value-list ,connections))

;;; NOTE: when upgrading connections, it's very hard to match the input and output names
;;; correctly. The function `get-direction-of-connection' may not be used here, because the related
;;; blocks may not be connected yet (we're at KB loading time). The only thing we know is: if the
;;; same connection object appears TWICE in the list, then the first one is output connection, the
;;; second one is input connection.

#+connections-v2 ; stage 1, used in kb reading stage
(defun-simple upgrade-connections (connections)
  (loop with connection-item-table = (make-connection-item-table)
	with current-connection-names = nil
	for connection-or-name in connections do
    (cond ((symbolp connection-or-name)
	   (slot-value-push connection-or-name current-connection-names))
	  ((connection-p connection-or-name)
	   (let* ((old-connection-item?
		   (get-connection-item connection-or-name connection-item-table))
		  (new-connection-item
		   (unless old-connection-item?
		     (make-connection-item connection-or-name))))
	     (cond (old-connection-item?
		    (setf (connection-item-input-names old-connection-item?)
			  (nreverse current-connection-names))
		    #+development
		    (when (connection-item-duplicated? old-connection-item?)
		      (error "impossible: connection item is already duplicated."))
		    (setf (connection-item-duplicated? old-connection-item?) t)
		    (setq current-connection-names nil))
		   (t
		    ;; NOTE: this is a temporary place, need to be fixed later in post loading functions.
		    (setf (connection-item-output-names new-connection-item)
			  (nreverse current-connection-names))
		    (setq current-connection-names nil)
		    (setf (get-connection-item connection-or-name connection-item-table)
			  new-connection-item)))))
	  (t
	   #+development
	   (error "impossible: neither connection nor name?!")))
	finally
	  (reclaim-slot-value-list connections)
	  (return connection-item-table)))

#+connections-v2 ; stage 2, used in post loading stage
(defun-void upgrade-block-connections (block)
  (loop for (connection . connection-item) being each binary-tree-entry-cons
					   of (connections block)
	for duplicated? = (connection-item-duplicated? connection-item)
	do
    #+development
    (unless (connection-connected-to-block-p connection block)
      (error "impossible: block is not connected yet?!"))
    #+development
    (unless (eq connection (connection-item-connection connection-item))
      (error "impossible: connection-item doesn't match the connection"))
    (when (and (not duplicated?)
	       (eq 'input (get-direction-of-connection connection block)))
      ;; move output names to input names
      (shiftf (connection-item-input-names connection-item)
	      (connection-item-output-names connection-item)
	      nil))))

;;;; Iteration Path Definitions for Connections

;;; The following paths should be used to access and filter 
;;; connections of an entity.
;;; Simple example:
;;; (loop for x being the connections of entity-1 ...

;;; More complicated paths are currently being implemented which
;;; access and filter connections according to various criteria.
;;; Ex.
;;; (loop for x being each {connection, input-connection, etc}
;;; 	  of y {such-that ___, of-type ___, 
;;;             connected-to-a-block-of-type ---, etc.} ...

;;; These paths are used in (among other things) the various role
;;; servers for connections (see "roles").  The role servers, and
;;; therefore these paths, are used by both the inference engine and
;;; simulator to allow for generic application of statements to the
;;; schematic.

;;; The connections slot value is of the form
;;; ( { {connection-name}* connection}* ) for #-connections-v2
;;;      connection-item (structure)      for #+connections-v2

;;; There can be any number of connections.  The connection name is
;;; optional and there can be more than one.  In general, a connection
;;; will not appear more than once in the connections slot (although it
;;; can have more than one name).  The only exception to this is in the
;;; case of a connection connected on both ends to the same entity [1]. The
;;; convention here is to have the output name or names (name or names
;;; associated with input-end-position of the connection), followed by
;;; the connection be immediately followed by the input name or names
;;; and connection.  The format is thus:
;;; ( output-name-or-names connection input-name-or-names connection )

;;; *1, in this case, the connection-item-duplicated? is T (connections-v2)

;;; Thus, when a connection is joined to the same entity, the list in
;;; the connections slot may have to be modified to follow this format.
;;; The connection may be split again for a variety of reasons; it could
;;; be deleted back to stubs, a block, such as a junction, may be
;;; inserted, or it may be split at the middle and one end dragged.
;;; When the connection is split, the new connection for the output name
;;; gets the input-end information of the old connection, and the new
;;; connection for the input name gets the output-end information of the
;;; old connection.  It is important to do this since the inference
;;; engine and simulator may use the port names.  If the input name or
;;; names are omitted, then while the connection is joined, it is
;;; sufficient to have the output name or names followed by the
;;; connection.  However, when the connection is split into two, it is
;;; important that the one associated with the output name or names get
;;; the input end information of the old connection.  The case is
;;; similar if the output name or names are omitted.  If both names are
;;; omitted, then there is no problem.

(eval-when (:compile-toplevel :load-toplevel :execute)

(define-loop-path (connection connections
			      output-connection output-connections
			      input-connection input-connections)
    connections-path 
  (of of-type at-port connected-to-a-block-of-type on-side-or-sides))

#-connections-v2
(defun-for-macro connections-path
    (path-name variable data-type prepositional-phrases
	       inclusive? allowed-prepositions data)
  (declare (ignorable data allowed-prepositions inclusive? data-type path-name))
  (let ((bindings nil)
	(prologue nil)
	(entity-var (gensym))
	(rest-of-connections-list (gensym))
	(class-for-connected-blocks (gensym))
	(class-for-connection-frame (gensym))
	(port-name (gensym))
	(side-or-sides (gensym))
	(previous-connection-found (gensym))
	(class-for-connected-blocks?
	  (cadr (assq 'connected-to-a-block-of-type
		      prepositional-phrases)))
	(class-for-connection-frame?
	  (cadr (assq 'of-type
		      prepositional-phrases)))
	(port-name?
	  (cadr (assq 'at-port
		      prepositional-phrases)))
	(side-or-sides?
	  (cadr (assq 'on-side-or-sides
		      prepositional-phrases))))
    (setq bindings
	  `((,variable nil)
	    (,entity-var ,(cadar prepositional-phrases)) ; (assq 'of ...)
	    ,@(if class-for-connected-blocks?
		  `((,class-for-connected-blocks
		      ,class-for-connected-blocks?)))
	    ,@(if class-for-connection-frame?
		  `((,class-for-connection-frame
		      ,class-for-connection-frame?)))
	    ,@(if port-name?
		  `((,port-name ,port-name?)))
	    ,@(if side-or-sides?
		  `((,side-or-sides ,side-or-sides?)))
	    (,rest-of-connections-list nil)
	    (,previous-connection-found nil)))
    ;; bindings are bound in parallel !
    (setq prologue
	  (list `(setq ,rest-of-connections-list
		       (connections ,entity-var))))
    (list bindings ; Part 1: init-bindings
	  prologue ; Part 2: prologue-forms

	  ;; Part 3: pre-step-endtest, specs for all but the first iteration
	  `(null (cdr ,rest-of-connections-list))

	  ;; Part 4: steppings
	  (list rest-of-connections-list
		`(loop for new-rest-of-connections-list
			   on (cdr ,rest-of-connections-list)
		       as connection?
			  = (car new-rest-of-connections-list)
		       doing
		   (if (and (not (symbolp connection?))  ; if it is a connection
			    ,@(case path-name
				((connection connections) nil)
				((output-connection output-connections)
				 `((eq (input-end-object connection?) ,entity-var)))
				(t		; if input-connection
				 `((eq (output-end-object connection?) ,entity-var))))
			    ,@(if class-for-connected-blocks?
				  `((of-class-p
				      (get-block-at-other-end-of-connection
					connection? ,entity-var)
				      ,class-for-connected-blocks)))
			    ,@(if class-for-connection-frame?
				  `((let ((connection-frame-or-class
					    (connection-frame-or-class connection?)))
				      (if (symbolp connection-frame-or-class)
					  (subclassp connection-frame-or-class
						     ,class-for-connection-frame)
					  (of-class-p connection-frame-or-class
						      ,class-for-connection-frame)))))
			    ;; port-name is the only loop path that requires an inner LOOP.
			    ,@(if port-name?
				  `((loop for rest-of-connections-cons on
					  ,rest-of-connections-list
					  for connection-or-name = 
					  (car rest-of-connections-cons)
					  for next-connection-or-name? =
					  (if (cdr rest-of-connections-cons)
					      (cadr rest-of-connections-cons)
					      nil)
					  do (if (and (eq connection-or-name
							  ,port-name)
						      next-connection-or-name?
						      (eq next-connection-or-name?
							  connection?))
						 (return t))
					  until (eq connection-or-name connection?))))
			    ,@(if side-or-sides?
				  `((let ((side
					    (get-side-given-end-position
					      (get-position-at-this-end-of-connection
						connection? ,entity-var))))
				      (if (atom ,side-or-sides)
					  (eq side ,side-or-sides)
					  (memq side ,side-or-sides)))))
			    (not (eq connection?
				     ,previous-connection-found)))
		       (return new-rest-of-connections-list))))

	  ;; Part 5: post-step-endtest
	  `(null ,rest-of-connections-list)

	  ;; Part 6: post-step-settings
	  (list variable
		`(car ,rest-of-connections-list)
		previous-connection-found
		variable)

	  ;; Part 7: pre-loop-pre-step-tests?, initial iteration specifications
	  `(null ,rest-of-connections-list) ; (cdr ,rest-of-connections-list) in Part 3

	  ;; Part 8: pre-loop-steps? 
	  (list rest-of-connections-list
		`(loop for new-rest-of-connections-list
			   on ,rest-of-connections-list ; (cdr ,rest-of-connections-list) in Part 4
		       as connection?
			  = (car new-rest-of-connections-list)
		       doing 
		   (if (and (not (symbolp connection?))  ; if it is a connection
			    ,@(case path-name
				((connection connections) nil)
				((output-connection output-connections)
				 `((eq (input-end-object connection?) ,entity-var)))
				(t		; if input-connection
				 `((eq (output-end-object connection?) ,entity-var))))
			    ,@(if class-for-connected-blocks?
				  `((of-class-p 
				      (get-block-at-other-end-of-connection
					connection? ,entity-var)
				      ,class-for-connected-blocks)))
			    ,@(if class-for-connection-frame?
				  `((let ((connection-frame-or-class
					    (connection-frame-or-class connection?)))
				      (if (symbolp connection-frame-or-class)
					  (subclassp connection-frame-or-class 
						     ,class-for-connection-frame)
					  (of-class-p connection-frame-or-class
						      ,class-for-connection-frame)))))
			    ;; port-name is the only loop path that requires an inner LOOP.
			    ,@(if port-name?
				  `((loop for rest-of-connections-cons on
					  ,rest-of-connections-list
					  for connection-or-name = 
					  (car rest-of-connections-cons)
					  for next-connection-or-name? =
					  (if (cdr rest-of-connections-cons)
					      (cadr rest-of-connections-cons)
					      nil)
					  do (if (and (eq connection-or-name
							  ,port-name)
						      next-connection-or-name?
						      (eq next-connection-or-name?
							  connection?))
						 (return t))
					  until (eq connection-or-name connection?))))
			    ,@(if side-or-sides?
				  `((let ((side
					    (get-side-given-end-position
					      (get-position-at-this-end-of-connection
						connection? ,entity-var))))
				      (if (atom ,side-or-sides)
					  (eq side ,side-or-sides)
					  (memq side ,side-or-sides)))))
			    )
		       (return new-rest-of-connections-list))))

	  ;; Part 9: pre-loop-post-step-tests?
	  `(null ,rest-of-connections-list)

	  ;; Part 10: pre-loop-pseudo-steps?
	  (list variable
		`(car ,rest-of-connections-list)
		previous-connection-found
		variable))))

#+connections-v2 ; based on expand-skip-list-or-binary-tree-entry-cons-loop-iterator
(defun-for-macro connections-path
    (path-name iter-var iter-var-data-type prep-phrases inclusive?
		 allowed-preps method-specific-data)
  (declare (ignorable path-name allowed-preps iter-var-data-type method-specific-data))
  (when inclusive?
    (error "The connections-path iteration path does not support ~
inclusive iterations."))
  (let* ((block-form-entry (assq 'of prep-phrases))
	 (block-form (second block-form-entry))
	 (skip-list-form (loop-gentemp 'skip-list-form-))
	 (skip-list-p (loop-gentemp 'skip-list-p-))
	 (node-stack (loop-gentemp 'node-stack-))
	 (current-node (loop-gentemp 'current-node-))
	 (next-node? (loop-gentemp 'next-node-))
	 (tail-node (loop-gentemp 'tail-node-))
	 (current-alist (loop-gentemp 'current-alist-))
	 (entry-cons (loop-gentemp 'entry-cons-))
	 (connection (loop-gentemp 'connection-))
	 (connection-item (loop-gentemp 'connection-item-))
	 (less-than-branch? (loop-gentemp 'less-than-branch?-))
	 ;; extra phrases
	 (class-for-connected-blocks (loop-gentemp 'class-for-connected-blocks-))
	 (class-for-connection-frame (loop-gentemp 'class-for-connection-frame-))
	 (port-name (loop-gentemp 'port-name-))
	 (side-or-sides (loop-gentemp 'side-or-sides-))
	 (class-for-connected-blocks?
	  (second (assq 'connected-to-a-block-of-type prep-phrases)))
	 (class-for-connection-frame?
	  (second (assq 'of-type prep-phrases)))
	 (port-name?
	  (second (assq 'at-port prep-phrases)))
	 (side-or-sides?
	  (second (assq 'on-side-or-sides prep-phrases)))
	 ;; return variables
	 init-bindings
	 prologue-forms
	 (pre-step-tests nil)
	 (steppings nil)
	 post-step-tests
	 post-step-settings)

    (when (null block-form-entry)
      (error "The connection-path iteration path requires an \"OF block-form\"."))

    (setq init-bindings
	  `((scope-conses scope-conses) ; requires a modification in loop-make-variable
	    (,node-stack nil)
	    (,current-node nil)
	    (,skip-list-form (connections ,block-form))
	    (,skip-list-p nil)
	    (,next-node? nil)
	    (,tail-node nil) 
	    (,current-alist nil)
	    (,entry-cons nil)
	    (,connection nil)
	    (,connection-item nil)
	    (,iter-var)
	    ,@(if class-for-connected-blocks?
		  `((,class-for-connected-blocks
		      ,class-for-connected-blocks?)))
	    ,@(if class-for-connection-frame?
		  `((,class-for-connection-frame
		      ,class-for-connection-frame?)))
	    ,@(if port-name?
		  `((,port-name ,port-name?)))
	    ,@(if side-or-sides?
		  `((,side-or-sides ,side-or-sides?)))))

    (setq prologue-forms
	  `((cond ((setq ,skip-list-p (skip-list-p ,skip-list-form))
		   (setq ,next-node?
			 (skip-list-element-next-0 (skip-list-head ,skip-list-form))
			 ,tail-node
			 (skip-list-tail ,skip-list-form))
		   (when (eq ,next-node? ,tail-node)
		     (setq ,next-node? nil)))
		  (t ; binary-tree
		   (setq ,next-node? (cdr ,skip-list-form))))))

    (setq post-step-tests
	  `(progn
	     (loop
	       (cond
	         (,current-alist
		  (setq ,entry-cons (car-of-cons ,current-alist))
		  (setq ,connection (car-of-cons ,entry-cons))
		  (setq ,connection-item (cdr-of-cons ,entry-cons))
		  (setq ,current-alist (cdr-of-cons ,current-alist)))
		 (,skip-list-p
		  (cond (,next-node?
			 (setq ,current-node ,next-node?)
			 (setq ,next-node? (skip-list-element-next-0 ,current-node))
			 (when (eq ,next-node? ,tail-node)
			   (setq ,next-node? nil))
			 (setq ,connection (skip-list-element-key ,current-node))
			 (setq ,connection-item (skip-list-element-entry ,current-node)))
			(t
			 (setq ,current-node nil))))
		 (t
		  (cond
		    (,next-node?
		     (setq ,current-node ,next-node?)
		     (loop for ,less-than-branch? = (less-than-branch
						      ,current-node)
			   while ,less-than-branch?
			   do
		       (setq ,node-stack (scope-cons ,current-node ,node-stack))
		       (setq ,current-node ,less-than-branch?)))
		    (,node-stack
		     (setq ,next-node? ,node-stack)
		     (setq ,current-node (car-of-cons ,node-stack))
		     (setq ,node-stack (cdr-of-cons ,node-stack)))
		    (t
		     (setq ,current-node nil)))
		  (when ,current-node
		    (setq ,next-node? (greater-than-branch ,current-node))
		    (setq ,current-alist (binary-element-alist ,current-node))
		    (setq ,entry-cons (car-of-cons ,current-alist))
		    (setq ,connection (car-of-cons ,entry-cons))
		    (setq ,connection-item (cdr-of-cons ,entry-cons))
		    (setq ,current-alist (cdr-of-cons ,current-alist)))))

	       (when (or (null ,current-node)
			 (and ,current-node
			      ,connection
			  ,@(case path-name
			      ((connection connections) nil)
			      ((output-connection output-connections)
			       `((eq (input-end-object ,connection) ,block-form)))
			      (t ; if input-connection
			       `((eq (output-end-object ,connection) ,block-form))))
			  ,@(when class-for-connected-blocks?
			      `((of-class-p
				 (get-block-at-other-end-of-connection
				   ,connection ,block-form)
				 ,class-for-connected-blocks)))
			  ,@(when class-for-connection-frame?
			      `((let ((connection-frame-or-class
				       (connection-frame-or-class ,connection)))
				  (if (symbolp connection-frame-or-class)
				      (subclassp connection-frame-or-class
						 ,class-for-connection-frame)
				    (of-class-p connection-frame-or-class
						,class-for-connection-frame)))))
			  ,@(when port-name?
			      `((memq ,port-name
				      ;; both input and output names here
				      (connection-item-name-or-names ,connection-item))))
			  ,@(when side-or-sides?
			      `((let ((side
				       (get-side-given-end-position
					 (get-position-at-this-end-of-connection
					   ,connection ,block-form))))
				  (if (atom ,side-or-sides)
				      (eq side ,side-or-sides)
				    (memq side ,side-or-sides)))))))
		 (return))) ; exit inner loop

	     (null ,current-node)))

    (setq post-step-settings
	  `(,iter-var ,connection))

    ;; Return a list of the six path elements.
    `(,init-bindings
      ,prologue-forms
      ,pre-step-tests
      ,steppings
      ,post-step-tests
      ,post-step-settings)))

) ; eval-when

;; Remember that the value of the connections slot of an entity is of the form:
;; ( {connection-name-or-names} connection ...)

;; iteration specs have four parts: pre-step-endtest, steps,
;; post-step-endtest, and pseudo-steps.

;; maybe do some error checking (see ex. of pg. 230)

(def-substitution-macro connection-exist-p (connection connections) ; new API
  ;; NOTE: some elements in the list is the connection name, but they just waste some extra time.
  #-connections-v2
  (memq connection connections)
  #+connections-v2
  (when connections
    (get-connection-item connection connections)))

;; User must use reclaim-slot-value-list to reclaim the return value at the end.
#+connections-v2
(defun-simple downgrade-connections (connections)
  (when connections
    (loop for (connection . connection-item)
	  being each binary-tree-entry-cons of connections
	  nconc
      (cond ((connection-item-duplicated? connection-item)
	     ;; (output-names connection input-names connection)
	     (nconc (copy-list-using-slot-value-conses
		      (connection-item-output-names connection-item))
		    (slot-value-list (connection-item-connection connection-item))
		    (copy-list-using-slot-value-conses
		      (connection-item-input-names connection-item))
		    (slot-value-list (connection-item-connection connection-item))))
	    (t
	     (let ((names ; only one of input/output names are non-NIL here:
		    (nconc (copy-list-using-slot-value-conses
			     (connection-item-output-names connection-item))
			   (copy-list-using-slot-value-conses
			     (connection-item-input-names connection-item)))))
	       (nconc names
		      (slot-value-list (connection-item-connection connection-item)))))))))

#-connections-v2
(defmacro downgrade-connections (connections)
  connections)

;; NOTE: moved from VIEW-DEF, similar with `gather-connections-for-block'
(defun connection-structures (item)
  (loop with result = nil
	for elt being each connection of item
	do
    (gensym-push elt result)
	finally
	  (return (nreverse result))))

#+development
(defun print-connection-locations (block)
  (cond ((and (framep block)
	      (block-p block))
	 #-connections-v2
	 (format t "~% ~a Connections" (length (connections block)))
	 (loop for connection being each connection of block
	       with output-position and input-position
	       with last-printed-object-was-a-name? = nil
	       do
	   (cond ((connection-p connection)
		  (setq output-position (output-end-position connection))
		  (setq input-position (input-end-position connection))
		  (cond (last-printed-object-was-a-name?
			 (format t ": "))
			(t
			 (format t "~%")))
		  (format t "~a Input ~a at ~a, ~a; Output ~a at ~a, ~a"
		   connection
		   (input-end-object connection)
		   (get-side-given-end-position input-position)
		   (get-position-on-side-given-end-position input-position)
		   (output-end-object connection)
		   (get-side-given-end-position output-position)
		   (get-position-on-side-given-end-position output-position))
		  (setq last-printed-object-was-a-name? nil))
		 (t
		  (format t "~% ~a" connection)
		  (setq last-printed-object-was-a-name? t)))))
	(t
	 (format t "~% ~a is not a block" block))))

(def-substitute-for-old-class flow-pipe-junction junction-block-for-flow-pipe)
(def-substitute-for-old-class
  instrument-signal-junction junction-block-for-instrument-signal)

(def-substitute-for-old-class standard-flow-pipe-junction junction-block-for-flow-pipe)
(def-substitute-for-old-class standard-flow-pipe flow-pipe)


(def-substitute-for-old-class standard-flow-pipe-connection-class flow-pipe)
(def-substitute-for-old-class standard-flow-pipe-junction
			       junction-block-for-flow-pipe)
(def-substitute-for-old-class instrument-signal-connection-class instrument-signal)

(def-absent-slot-putter control-block-input (control-block slot-value)
  (put-attribute-value control-block 'input-1 slot-value t))

(def-absent-slot-putter control-block-input-1 (control-block slot-value)
  (put-attribute-value control-block 'input-1 slot-value t))

(def-absent-slot-putter control-block-input-2 (control-block slot-value)
  (put-attribute-value control-block 'input-2 slot-value t))

(def-absent-slot-putter control-block-output (control-block slot-value)
  (put-attribute-value control-block 'output-1 slot-value t))

(declare-forward-reference put-attribute-value function)



;;;; Connection Information Wrapper and Other Primitives


;;; The macro `with-connection' binds a set of variables so that they provide
;;; information needed for drawing the connection and for other purposes.  The
;;; arguments control which groups of variables are bound since they are not
;;; all needed in all cases.  This wrapper is used mainly in CONNECT2 and
;;; CONNECT3.

(def-system-variable dont-include-offset-for-end-position? CONNECT1 nil)

(defmacro with-connection 
	  (connection input-info? output-info? initial-orientation? 
	   other-binding-forms? &body body)
  (let ((value-of-connection (gensym)))
    `(let* ((,value-of-connection ,connection)
	    ,@ (when input-info?
		 `((input-end-object
		     (input-end-object ,value-of-connection))
		   (input-end-position
		     (input-end-position ,value-of-connection))
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
			   (right (+w (width-of-block input-end-object)
				      (if dont-include-offset-for-end-position? 0 1)))
			   (t			       ; if top or bottom
			    input-end-position-on-side))))
		   (input-end-y-position
		     (+w (top-edge-of-block input-end-object)
			 (case input-end-side
			   (top 0)
			   (bottom (+w (height-of-block input-end-object)
				       (if dont-include-offset-for-end-position? 0 1)))
			   (t			       ; if right or left
			    input-end-position-on-side))))

		   ,@(when initial-orientation?
		       `((initial-orientation-horizontal-p
			   (initial-orientation-horizontal-p input-end-side))))))
	    ,@ (when output-info?
		 `((output-end-object
		     (output-end-object ,value-of-connection))
		   (output-end-position
		     (output-end-position ,value-of-connection))
		   (output-end-side
		     (get-side-given-end-position
		       output-end-position))
		   (output-end-position-on-side
		     (get-position-on-side-given-end-position
		       output-end-position))
		   (output-end-x-position
		     (+w (left-edge-of-block output-end-object)
			 (case output-end-side
			   (left 0)
			   (right (+w (width-of-block output-end-object) 
				      (if dont-include-offset-for-end-position? 0 1)))
			   (t			       ; if top or bottom
			    output-end-position-on-side))))
		   (output-end-y-position
		     (+w (top-edge-of-block output-end-object)
			 (case output-end-side
			   (top 0)
			   (bottom (+w (height-of-block output-end-object) 
				       (if dont-include-offset-for-end-position? 0 1)))
			   (t			       ; if right or left
			    output-end-position-on-side))))))

	    ,@ other-binding-forms?)
       ,@body)))

;; If dont-include-offset-for-end-position?  is nil, the 1+ offset is used so that
;; the stubs won't xor with the edge of the rectangle.  This is consistent with
;; what is done in ENTITIES.  In certain cases (such as when computing distances
;; to be returned to the user) the offset is undesireable.  In these cases,
;; dont-include-offset-for-end-position?  is bound to t and the offset is omitted.



(def-substitution-macro initial-orientation-horizontal-p (side)
  (or (eq side 'left)
      (eq side 'right)))




(def-substitution-macro get-connection-class-given-connection (connection)
  (get-connection-class-given-connection-frame-or-class
    (connection-frame-or-class connection)))

(def-substitution-macro get-connection-class-given-connection-frame-or-class
			(connection-frame-or-class)
  (if (symbolp connection-frame-or-class)
      connection-frame-or-class
      (class connection-frame-or-class)))

(defun-substitution-macro slot-description-for-connection-class (connection-class slot-name)
  (cond ((class-description connection-class)
	 (slot-description-from-class connection-class slot-name))
	(t
	 (dwarn "Connection class ~s is undefined." connection-class)
	 (slot-description-from-class 'connection slot-name))))

(def-substitution-macro get-cross-section-pattern-given-connection-frame-or-class
			(connection-frame-or-class)
  (if (framep connection-frame-or-class)
      (cross-section-pattern connection-frame-or-class)	        ; if a frame
      ;; else, if a class (symbol)
      (slot-init-form
	(slot-description-for-connection-class
	  connection-frame-or-class 'cross-section-pattern))))

(def-substitution-macro get-stub-length-given-connection-frame-or-class
       (connection-frame-or-class)
  (if (framep connection-frame-or-class)
      (stub-length connection-frame-or-class)	       ; if a frame
      ;; else, if a class (symbol)
      (slot-init-form
	(slot-description-for-connection-class
	  connection-frame-or-class 'stub-length))))

(def-substitution-macro get-junction-block-class-given-connection-frame-or-class
       (connection-frame-or-class)
  (if (framep connection-frame-or-class)
      (junction-block-class 
	connection-frame-or-class)	       ; if a frame
      ;; else, if a class (symbol)
      (slot-init-form
	(slot-description-for-connection-class
	  connection-frame-or-class 'junction-block-class))))


(def-substitution-macro compute-connection-width-given-stripe
			(cross-section-stripe)
  (loop for (nil . width) in cross-section-stripe
	summing width using +f))


(def-substitution-macro compute-connection-width-given-connection-frame-or-class
    (connection-frame-or-class)
  (compute-connection-width-given-stripe
    (get-cross-section-stripes
      (get-cross-section-pattern-given-connection-frame-or-class
	connection-frame-or-class))))

;; I think that is incorrect to ever compute the connection width from the
;; cross-section-pattern cache in the connection frame.  That cache is used
;; only for connection stripe colors.  The stripe widths are up-to-date only in
;; the connection definition. -fmw, 1/19/95


;;; The function `connection-striped-p' is true for connections which are truely
;;; "striped", that is, they have more than one element in their cross section
;;; pattern.  If a connection is not striped, then it is much easier to draw.

(defun connection-striped-p (connection)
  (let ((cross-section-stripes
	  (get-cross-section-stripes
	    (get-cross-section-pattern-given-connection-frame-or-class
	      (connection-frame-or-class connection)))))
    (not (null (cdr cross-section-stripes)))))

;; It is tempting to consider connections all of whose stripes are of the same
;; color to have just one stripe.  The problem is that this breaks the
;; color-change operations: now merely changing the color of a stripe changes
;; the way a connection is drawn.  Color-change assumes that exactly the same
;; pixels are drawn for any color, so that it can just draw the changed stripe.



(def-substitution-macro compute-connection-stripe-color
			(region-or-color cross-section-regions)
  (or (cdr (assq region-or-color cross-section-regions))
      region-or-color))



;;; `Get-connection-color' is a subfunction of item-color, used for computing
;;; user expressions for the colors of items.  If region is STRIPE-COLOR, then
;;; if connection has no regions and only one stripe, that stripe's color is
;;; returned.  Otherwise, if connection has the given named region, its color
;;; is returned.  Note that for defaulted colors (with nil values) the value of
;;; current-default-line-color is returned.  However, nil can be returned, e.g.
;;; when the region specification is wrong.

(defun get-connection-color (connection-frame region)
  (let ((cross-section-pattern?
	  (get-cross-section-pattern-given-connection-frame-or-class
	    connection-frame)))
    (when cross-section-pattern?
      (case region
	(stripe-color
	 (if (and (null (cross-section-regions-specified?
			  cross-section-pattern?))
		  (null (cdr cross-section-pattern?)))
	     ;; allow STRIPE-COLOR to access "monochrome" connection
	     ;;   color only
	     (or (car (car cross-section-pattern?))
		 current-default-line-color)))
	(t
	 (let ((cross-section-regions?
		 (get-cross-section-regions cross-section-pattern?)))
	   (if cross-section-regions?
	       (let ((entry?
		       (assq region cross-section-regions?)))
		 (if entry?
		     (or (cdr entry?)
			 current-default-line-color))))))))))

; Used to allow a null region, meaning stripe-color.



;;;; Connected Predicates

;;; These are predicates which indicate whether items are connected.



(defun generic-directly-connected-p (connection-frame block)
  (when (frame-of-class-p connection-frame 'connection)
    (let ((connection
	    (connection-for-this-connection-frame 
	      connection-frame)))
      (or
	(input-connection-p block connection)
	(output-connection-p block connection)))))
;; Expose this in G2 system procedure.



;;;; Connection Spots


(defparameter connection-vertex-hit-distance 5)

(def-spot connection-spot
    :slots nil
    :include spot
    :enclosing-spot-type image-plane-spot
    :innermost-spot-p t
    :abstract-type nil
    :type-of-frame-represented connection)

(def-class-method generate-spot (connection mouse-pointer)
  (or (push-connection-vertex-spot-if-close connection mouse-pointer)
      (push-last-spot mouse-pointer (make-connection-spot) connection)))

(defun push-connection-vertex-spot-if-close (connection-frame mouse-pointer)
  (let ((spot (stack-of-spots mouse-pointer))
	(connection (connection-for-this-connection-frame connection-frame)))
    (when (structure-type-p spot 'image-plane-spot)
      (let ((image-plane (image-plane-of-spot spot)))
	(when (selection-handles-visible-p connection image-plane)
	  (multiple-value-bind (vertex? distance? x? y?)
	      (find-closest-connection-vertex connection image-plane
					      (x-of-mouse-pointer mouse-pointer)
					      (y-of-mouse-pointer mouse-pointer))
	    (when (and distance? (<=f distance? connection-vertex-hit-distance))
	      (push-selection-handle-spot mouse-pointer connection-frame 'vertex vertex? x? y?)
	      t)))))))

(defun find-closest-connection-vertex (connection image-plane x0 y0)
  (with-image-plane-transform (image-plane)
    (let* ((vertices (compute-connection-vertices connection))
	   (vertex? nil)
	   (distance? nil)
	   (vertex-x? nil)
	   (vertex-y? nil))
      (loop for (x y) on vertices by #'cddr
	    as vertex from 0
	    as distance = (vector-distance-in-workspace (absw (-f x x0)) (absw (-f y y0)))
	    doing
	(when (or (null distance?) (<f distance distance?))
	  (setq vertex? vertex
		distance? distance
		vertex-x? (x-in-workspace x)
		vertex-y? (y-in-workspace y))))
      (reclaim-gensym-list vertices)
      (values vertex? distance? vertex-x? vertex-y?))))

(defmacro with-changes-to-connection ((workspace? connection) &body body)
  `(progn
     (when workspace?
       (update-connection-images t ,workspace? ,connection))
     (note-change-to-connection ,connection)
     (progn ,@body)
     (when workspace?
       (enlarge-workspace-for-connection ,workspace? ,connection)
       (update-connection-images nil ,workspace? ,connection))))

(defun move-connection-vertex-by (connection-or-connection-frame vertex dx dy)
  (let ((connection (if (framep connection-or-connection-frame)
			(connection-for-this-connection-frame connection-or-connection-frame)
			connection-or-connection-frame)))
    (cond ((connection-diagonal-p connection)
	   (move-diagonal-connection-vertex-by connection vertex dx dy))
	  (t
	   (move-orthogonal-connection-vertex-by connection vertex dx dy)))))

(defun move-if-loose-end (block dx dy)
  (when (loose-end-p-function block)
    (unless (=f dx dy 0)
      (move-item-by block dx (-f dy)))))

(defun move-diagonal-connection-vertex-by (connection vertex dx dy)
  (let* ((delta-or-deltas (delta-or-deltas connection))
	 (workspace? (workspace-of-connection? connection))
	 (initial-orientation-horizontal-p
	   (initial-orientation-horizontal-p
	     (get-side-given-end-position
	       (input-end-position connection))))
	 (input-end (input-end-object connection))
	 (output-end (output-end-object connection)))

    (cond ((null delta-or-deltas))
	  ((atom delta-or-deltas)
	   (let ((adjacent-end (if (=f vertex 1) input-end output-end)))
	     (with-changes-to-connection (workspace? connection)
	       (incff (delta-or-deltas connection) (if initial-orientation-horizontal-p dx dy)))
	     (if initial-orientation-horizontal-p
		 (move-if-loose-end adjacent-end 0 dy)
		 (move-if-loose-end adjacent-end dx 0))))
	  (t
	   (let* ((sublist (unless (atom delta-or-deltas)
			     (unless (<f vertex 1)
			       (nthcdr (*f (-f vertex 1) 2) delta-or-deltas))))
		  (rest (cddr sublist)))
	     ;; FIXME: Tighter clipping rect
	     (with-changes-to-connection (workspace? connection)
	       (when sublist
		 (incff (car sublist) (if initial-orientation-horizontal-p dx dy))
		 (when (cadr sublist)	; HQ-5534778
		   (incff (cadr sublist) (if initial-orientation-horizontal-p dy dx))))
	       (when rest
		 (decff (car rest) (if initial-orientation-horizontal-p dx dy))
		 (when (cadr rest)	; HQ-5534778
		   (decff (cadr rest) (if initial-orientation-horizontal-p dy dx))))))))))

;;; The function `move-orthogonal-connection-vertex-by' assumes that it's not
;;; allowed to move an endpoint object unless it is a loose-end. As a result, a
;;; vertex near a fixed endpoint can only move in one dimension. Maybe something
;;; better could be done here.

(defun move-orthogonal-connection-vertex-by (connection vertex dx dy)
  (let ((delta-or-deltas (delta-or-deltas connection))
	(workspace? (workspace-of-connection? connection))
	(initial-orientation-horizontal-p
	  (initial-orientation-horizontal-p
	    (get-side-given-end-position
	      (input-end-position connection))))
	(input-end (input-end-object connection))
	(output-end (output-end-object connection)))

    (cond ((null delta-or-deltas)
	   (cond (initial-orientation-horizontal-p
		  (move-if-loose-end input-end 0 dy)
		  (move-if-loose-end output-end dx 0))
		 (t
		  (move-if-loose-end input-end dx 0)
		  (move-if-loose-end output-end 0 dy))))

	  ((atom delta-or-deltas)
	   (let ((adjacent-end (if (=f vertex 1) input-end output-end)))
	     (with-changes-to-connection (workspace? connection)
	       (incff (delta-or-deltas connection) (if initial-orientation-horizontal-p dx dy)))
	     (if initial-orientation-horizontal-p
		 (move-if-loose-end adjacent-end 0 dy)
		 (move-if-loose-end adjacent-end dx 0))))

	  (t
	   (let* ((sublist (if (>=f vertex 1)	; Should always be true.
			       (nthcdr (-f vertex 1) delta-or-deltas)))
		  (prevlist (if (>=f vertex 2)
				(nthcdr (-f vertex 2) delta-or-deltas)))
		  (horizontal-p (neq initial-orientation-horizontal-p	; For delta in (car sublist)
				     (=f (modf vertex 2) 0))))
	     (with-changes-to-connection (workspace? connection)
	       (when prevlist
		 (incff (car prevlist) (if horizontal-p dy dx)))
	       (when (cddr prevlist)
		 (decff (caddr prevlist) (if horizontal-p dy dx)))

	       (when sublist
		 (incff (car sublist) (if horizontal-p dx dy)))
	       (when (cddr sublist)
		 (decff (caddr sublist) (if horizontal-p dx dy))))

	     (when (=f vertex 1)
	       (if initial-orientation-horizontal-p
		   (move-if-loose-end input-end 0 dy)
		   (move-if-loose-end input-end dx 0)))
	     
	     (when (>f vertex (length delta-or-deltas))
	       (if (neq initial-orientation-horizontal-p (=f (modf (length delta-or-deltas) 2) 0))
		   (move-if-loose-end output-end 0 dy)
		   (move-if-loose-end output-end dx 0))))))))

(defun enlarge-workspace-for-connection (workspace connection)
  (with-extreme-edges-1 ()
    (update-extreme-edges-from-connection connection)
    (let ((current-draw-document-p nil))
      (enlarge-workspace-if-necessary workspace
				      extreme-left-edge-so-far extreme-top-edge-so-far
				      extreme-right-edge-so-far extreme-bottom-edge-so-far))))


;;;; Random Stuff


#+development
(defun check-for-bad-connections (&optional reclaimed-connection)
  (loop for frame being each class-instance of 'connection
	for connection = (connection-for-this-connection-frame frame)
	do
    (unless (and connection
		 (eq (connection-frame-or-class connection) frame)
		 (not (and reclaimed-connection
			   (eq connection reclaimed-connection))))
      (error "bad connection frame"))))


;;; `subclasses'
;;; Returns a gensym-list of ALL the children of a class,
;;; which must be reclaimed by the caller.

(defun subclasses (class-name)
  (loop for subclass being each subclass of class-name
	collect subclass
	  using gensym-cons))

(defun instantiated-connection-class-p (connection-class)
  (let* ((subclasses (subclasses connection-class))
	 (instantiated? 
	   (loop for block being each class-instance of 'block
		 thereis
		 (loop for connection being each output-connection of block
		       as class-name = (class-of-thing connection)
		       thereis (memberp class-name subclasses)))))
    (reclaim-gensym-list subclasses)
    instantiated?))


(defmacro instantiated-class-or-connection-class-p (name-of-class)
  `(let* ((class-name ,name-of-class)
	  (class-definition (class-definition class-name))
	  (inheritance-path (class-inheritance-path-of-definition class-definition)))
     (cond ((memq 'connection inheritance-path)
	    (instantiated-connection-class-p class-name))
	   (t 
	    (instantiated-class-p class-name)))))



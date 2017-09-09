;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module TABLES

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Lowell B. Hawkinson, Mark H. David, and Joseph E. Devlin




(declare-forward-references-to-module workstation
  push-last-spot
  push-more-detailed-spot
  (current-workstation-detail-pane variable)
  idle-time-when-polling)

(declare-forward-references-to-module edit1
  enter-editing-context
  (editor-parameters variable))

(declare-forward-references-to-module edit2
 (parse-text-for-slot function))

(declare-forward-references  
  (procedure? function proc-utils)
  (image-plane-of-mouse-pointer function new-menus)
  (pick-cell-from-table function menus)
  (loading-kb-p variable kb-load2)
  (reading-kb-p variable kb-load2)
  (kb-file-progress variable kb-load1)
  (clone-frame function kb-load1)
  (note-kb-state-change function kb-save2)
  (saving-kb-p variable)
  (current-saving-context? variable)

  (include-slot-in-attribute-table-p function filters)
;  (attribute-operation-is-allowed-p function filters)
  (edit-attribute-allowed-p function filters)

  (write-procedure-invocation-instance-from-slot function proc-utils)
  (*current-computation-frame* variable comp-utils)
  (background-color-of-generic-action-button function controls)
  (twrite-number-per-format function controls)
  (show-or-hide-1 function)		; CONTROLS
  (show-or-hide function)		; CONTROLS
  (redraw-transfer-representations-of-block function moves)
  (allow-only-one-table-display-for-item?-from-system-table function grammar7)
  (representation-address-valid-p function view-g2)
  (send-ws-representations-item-virtual-attribute-change function events-g2)
  (doing-password-change-p variable run)
  (applicable-and-not-deprecated-virtual-attribute-p function attr-export))

(declare-forward-reference get-ruling-for-meter function)

(declare-forward-reference color-or-metacolor-p function)
(declare-forward-reference all-virtual-attributes-for-class function)
(declare-forward-reference all-non-local-virtual-attributes-for-class function)
(declare-forward-reference twrite-frame-edit-timestamp function)
(declare-forward-reference get-current-frame-edit-timestamp function)
(declare-forward-reference make-button-to-update-virtual-attributes-table function)
(declare-forward-reference make-description-box-with-text function)
(declare-forward-reference permit-view-slot-in-exported-format-p function)
(declare-forward-reference make-running-head function) ; in BOOKS

(declare-forward-reference update-selection-highlights-for-table function) ; MOVES
(declare-forward-reference note-deletion-of-text-cell-for-selection function) ; COMMANDS0
(declare-forward-reference thing-selected-p function) ; COMMANDS0
(declare-forward-reference note-deletion-of-all-text-cells-for-selection function)
(declare-forward-reference update-property-grid-all function) ; COMMANDS1

;;;; Tables



;;; A `table' is a two-dimensional graphic array of one or more `cells', where each
;;; cell exactly occupies the non-border, non-boundary area of one or more adjacent
;;; `columns' in a single `row' of the table.  Rows may be of different heights, and
;;; columns may be of different widths.  A cell may be specified by a `row index' and
;;; `column index' pair, where both are zero-based and where the column index is
;;; the rightmost column occupied by the cell.

;;; A table is kept formatted in accordance with its table format (see below).

;;; A `table row' is of the form ( { text-cell | block | nil } ), where nil indicates
;;; that the next text cell or block occupies this and one or more following columns.
;;; A text cell is a list structure that is fully described below; the use of a block
;;; as a table cell is discussed below.  A row cannot be nil nor end with a nil.
;;; Unfilled columns at the end of a row (a row that is shorter than the longest row
;;; in the table) are, at present, fully transparent when drawn, that is, they are not
;;; even colored in with the table background color, if any.

;;; Blocks used as table cells must be subblocks of the table, and must not be referred
;;; to in any other frame.  Tables may also have text regions as subblocks.  [Some
;;; new stuff:  (MHD 6/7/91)]  Some tables, e.g., readout tables, may also have
;;; display tables (mini attribute tables) as subblocks.  Note that display tables
;;; are frame representations of their superblock.

;;; When a block used as a table cell is deleted, it gets removed from the table
;;; rows such that only legal table rows remain.  The operation that does this
;;; is remove-block-as-cell-of-table, which is called by delete-frame via
;;; remove-as-subblock-if-necessary.
;;;
;;; Note that this could result in the table rows for a table being nil.  (This
;;; is a new requirement; some of the code may operate under the assumption that
;;; table-rows of a table can never be nil; needs investigation! (MHD/JED
;;; 5/17/95)]

;;; Blocks used as table cells must have methods for the following operations: draw,
;;; shift, compute-minimum-right-edge, compute-minimum-bottom-edge, compute-data-for-
;;; resize (not yet used), and resize (not yet used).  The compute-data-for-resize
;;; method takes a new right edge (or nil for no change) and the minimum bottom edge,
;;; and it returns six values: the leftmost point that could be changed by resize if
;;; given these same arguments, the topmost point that could be changed, the rightmost
;;; point that could be changed, the bottommost point that could be changed, the
;;; bottom edge for the resized block, and other data for the resizing.  The resize
;;; method takes the right edge, the bottom edge for the resized block, and other
;;; data for the resizing; the last two arguments are as computed by compute-data-for-
;;; resize.  The resize method must change the block according to its arguments,
;;; assuming that they are consistent with the values that would be returned by the
;;; compute-minimum-right-edge, compute-minimum-bottom-edge, and compute-data-for-
;;; resize methods.

;;; A block used as a table cell should be drawn without top and bottom borders when
;;; its superblock has row boundaries and without left and right borders when its
;;; superblock has column boundaries.  (Thus, for example, subtables of a table that
;;; has borders but no boundaries will be drawn with borders, even when such subtables
;;; are on the edge of the supertable.)  All tables (including graphs), all labeled
;;; and centered alarm lights, and all push buttons should be usable as table cells.

;;; Table borders, if any, fit just within the table rectangle.  A cell does not
;;; include its borders or boundaries, if any.  The left edge of a column boundary
;;; coincides with the `column edge', and the top edge of a row boundary coincides
;;; with the `row edge'.

;;; Row and column edges are always as high up and as far left as is consistent with
;;; the satisfaction of all formatting constraints.  Right and bottom edges of the
;;; table itself are also always as far left and high up as possible, unless the
;;; table is a subtable, in which case these edges can be arbitrarily far to the
;;; right and down.

;;; When a column edge is the same as the preceding column edge (or, for the first
;;; column edge, is zero), that indicates that no cell has yet been encountered that
;;; ends in that column.  If and when such a cell is encountered (during formatting),
;;; the column edge may be adjusted rightwards without necessarily moving other column
;;; edges to the right of it by the same amount, as long as all column edges are kept
;;; well-ordered and columns to the right retain their widths.

;;; Note that graphs in G2 are represented as tables. To align the vector slot
;;; accessors in class `graph' with `meter' and `dial', the number of vector slots
;;; of class `table' should be the same with class `entity' (defined in entities.lisp)
;;; -- Chun Tian (binghe), Apr 2, 2015.

(def-class (table block define-predicate)

  (table-format nil vector-slot save system)

  (row-edges nil vector-slot save system do-not-clone)
  (column-edges nil vector-slot save system do-not-clone)

  (table-rows nil vector-slot save system do-not-clone))


(def-class (table-item (exported-system-item table)
		       define-predicate not-user-instantiable))

(def-system-variable allow-activation-of-table-items-p tables nil) 

(def-class-method activate-if-possible-and-propagate (table-item)
  (when allow-activation-of-table-items-p
    (funcall-superior-method table-item)))


;;; `Pseudo-class-slot-description' is part of an experiment in frame slimming.
;;; Some vector slots defined at the block level have been converted to lookup
;;; slots, and the class slot has been eliminated altogether at root.  This
;;; pseudo slot-description for the former class slot is to get the table
;;; code working as quickly as possible.  It is a disgraceful hack.

(defvar pseudo-class-slot-description nil)

(defun set-pseudo-class-slot-description ()
  (setq pseudo-class-slot-description
	(make-slot-description
	  'class 'root nil nil nil nil nil
	  '((vector-slot) (system) (type class-instance-header) (do-not-save)
	    (do-not-identify-in-attribute-tables) (not-user-editable)))))

(set-pseudo-class-slot-description)





;;; Subtablep is true if table is a subblock of a table.

(defmacro subtablep (table)
  `(let ((superblock? (superblock? ,table)))
     (if superblock? (table-p superblock?))))



;;; `Cell-is-block-p' is true if table-cell is a block, that is, is not a text cell.

(defmacro cell-is-block-p (table-cell)
  `(atom ,table-cell))

      
(defun remove-block-as-cell-of-table (block table)
  (loop with prev-row-tail? = nil
	for row-tail on (table-rows table)
	as row = (car row-tail)
	do
    (loop with prev-cell-tail? = nil
	  with non-nil-row-p = nil
	  for cell-tail on row
	  as cell = (car cell-tail)
	  do
      (when (eq cell block)
	(cond (prev-cell-tail?
	       (cond ((or non-nil-row-p (cdr cell-tail))
		      (setf (cdr prev-cell-tail?) (cdr cell-tail))
		      (reclaim-slot-value-cons cell-tail))
		     (t
		      (reclaim-slot-value-list row)
		      (cond (prev-row-tail?
			     (setf (cdr prev-row-tail?) (cdr row-tail))
			     (reclaim-slot-value-cons row-tail))
			    (t
			     (setf (table-rows table) nil))))))
	      (prev-row-tail?
	       (reclaim-slot-value-cons row)
	       (setf (cdr prev-row-tail?) (cdr row-tail))
	       (reclaim-slot-value-cons row-tail))
	      (t
	       (reclaim-slot-value-cons row)
	       (setf (table-rows table) nil)))
	(return-from remove-block-as-cell-of-table nil))
      (when cell
	(setq non-nil-row-p t))
      (setf prev-cell-tail? cell-tail))
    (setf prev-row-tail? row-tail)))




;;; `cell-is-text-cell-p' is true if the table cell is a text cell.

(defmacro cell-is-text-cell-p (table-cell?)
  `(consp ,table-cell?))


;;; `resize' `compute-minimum-right-edge' and `compute-minimum-bottom-edge' are
;;; class methods on blocks that may appear as cells in tables.  They are
;;; discussed above.

(def-generic-method resize (block available-width available-height other-data)
  )

(def-generic-method compute-minimum-right-edge (block)
  )

(def-generic-method compute-minimum-bottom-edge (block)
  )





;;;; Table Formats



;;; A `table format' ...  If the row boundary width is non-zero, the top and bottom
;;; border widths must also be non-zero.  Similarly, if the column boundary width is
;;; non-zero, the left and right border widths must be non-zero.  When the row and
;;; column boundary colors differ, the row boundary color will prevail at the
;;; intersections.

(def-format-class (table-format format-frame)	; could be used as a table type

  (table-line-color?				; defaults to supertable line color,
    nil (type color) vector-slot system)	;   or else to current-default-line-color
						;   -- was black (MHD 8/3/89)
  (table-background-color?			; defaults to supertable background
    nil (type color) vector-slot system)	;   color, or else to transparent

  (table-left-border-width			; 0 for none; in workspace units
    2 (type width) vector-slot system)
  (table-top-border-width			; 0 for none; in workspace units
    2 (type width) vector-slot system)
  (table-right-border-width			; 0 for none; in workspace units
    2 (type width) vector-slot system)
  (table-bottom-border-width			; 0 for none; in workspace units
    2 (type width) vector-slot system)
  (table-border-color?				; defaults to current-default-line-color
    nil (type color) vector-slot system)	;   -- was black (MHD 8/3/89)

  (table-row-boundary-width			; 0 for none; in workspace units
    2 (type width) vector-slot system)
  (table-row-boundary-color?			; defaults to current-default-line-color
    nil (type color) vector-slot system)	;   -- was black (MHD 8/3/89)

  (table-column-boundary-width			; 0 for none; in workspace units
    2 (type width) vector-slot system)
  (table-column-boundary-color?			; defaults to current-default-line-color
    nil (type color) vector-slot system))	;   -- was black (MHD 8/3/89)

;; Define types color and width!





;;; The macro `lookup-table-format-property' abstracts the knowledge about
;;; the inheritance of table format properties.  It lookups the value
;;; of property-name, a function on table-formats, for table, and returns
;;; the default if no property was found. -fmw, 6/10/94

(defmacro lookup-table-format-property (table property-name default)
  (let ((tab (make-symbol "TAB")))
    `(or
       (loop for ,tab = ,table
		      then (superblock? ,tab)
	     thereis (,property-name (table-format ,tab))
	     while (subtablep ,tab))
       ,default)))

#+unused
(defun table-line-color-function (table)
  (lookup-table-format-property table table-line-color? 'foreground))


(defun table-background-color (table)
  (lookup-table-format-property table table-background-color? 'transparent))

;; Notice that tables default to a transparent background color.


#+unused
(defun table-border-color-function (table)
  (or (table-border-color? (table-format table))
      (table-line-color-function table)))

;; Notice how this one is not inherited -- a bug?





;;;; Text Cells



;;; A `text cell' is a table cell that contains formatted text.  A text cell
;;; has these four components.  In tables these are represented using a list
;;; of slot value conses, while in text-boxes they are found in slots of the
;;; block.
;;;
;;;     text-cell-format
;;;     text-cell-plist
;;;
;;;     minimum-right-edge-for-cell ; also used temporarily, during formatting,
;;;				    ;   to store the minimum width for the cell
;;;     text?                       ; a text (no longer allowed to be nil)

;;; In addition a text of a text cell is rendered in a rectangular region
;;; of the workspace.  Variables such as left-edge-of-text-cell manifest
;;; this, and are generated procedurally.  Clipping may further constrain
;;; what of the actually text appears, i.e. the text cell may be larger than
;;; the enclosing block, or table cell.

;;; Except transiently just after it has been made, text? is to be kept
;;; formatted in accordance with its text cell format (see below), i.e., a text
;;; cell is always "WYSIWYG" (what you see is what you get).  However, see
;;; update-text-cell, below, for an exeption.

;;; The plist is used to annotate the cell.  The things that may appear in this
;;; are documented in boxes. (see the concept text-cell-plist).

;;; When changes are made to these values all non-sharable components (i.e. text
;;; strings and conses) are reclaimed on a change.

(def-concept text-cell)

(defmacro text-cell-format (text-cell) `(car ,text-cell))

(defmacro text-cell-plist (text-cell) `(cadr ,text-cell))

(defmacro minimum-right-edge-for-cell (text-cell) `(caddr ,text-cell))

(defmacro text? (text-cell) `(cdddr ,text-cell))

;; This could have been defined as follows:
;; (def-list-structure text-cell
;;    (text-cell-format text-cell-plist minimum-right-edge-for-cell . text?))

(defun text-cell-p (thing)
  (and (consp thing)
       (framep (text-cell-format thing))
       (frame-of-class-p (text-cell-format thing) 'text-box-format)
       (listp (text-cell-plist thing))
       (fixnump (minimum-right-edge-for-cell thing))))

       
#+development
(def-development-printer print-text-cell (text-cell &optional (stream *standard-output*))
  (when (text-cell-p text-cell)
    (let ((text-string?
	    (loop for element in (text? text-cell)
		  when (text-line-p element)
		    return element)))
      (when (and (text-string-p text-string?)
		 (>f (text-string-length text-string?) 20))
	(setq text-string?
	      (tformat-text-string
		  "~a..."
		(text-string-substring text-string? 0 20))))
      (printing-random-object (text-cell stream)
	(format stream "TEXT-CELL~@[ ~s~]" text-string?)))
    text-cell))

#+development
(def-development-describer describe-text-cell (text-cell)
  (when (text-cell-p text-cell)
    (format t "~s is a ~s, represented by a ~s.~%"
	    text-cell 'text-cell (type-of text-cell))
    (let ((i 0))
      (macrolet ((S (slot) `(describe-slot-in-frame-or-structure
			      (incf i) nil ',slot (,slot text-cell))))
	(s text-cell-format)
	(s text-cell-plist)
	(s minimum-right-edge-for-cell)
	(s text?)
	text-cell))))



;;; `Make-text-cell' makes a text cell that holds text.  The format of the new
;;; text cell is specified by text-box-format-or-format-name.  The new text
;;; cell is made of slot value conses.

(defun make-text-cell
    (text text-box-format-or-format-name &optional text-cell-plist?)
  (slot-value-cons
    (if (symbolp text-box-format-or-format-name)
	(get-or-make-format-frame text-box-format-or-format-name)
	text-box-format-or-format-name)
    (slot-value-cons
      text-cell-plist?
      (slot-value-cons nil text))))

;; Added optional arg text-cell-plist?.  (MHD 1/11/90)


;;; `Make-text-cell-representing-slot' is like make-text-cell, but it makes up
;;; the appropriate plist giving the backpointer to the designated slot, or
;;; component thereof.

(defun make-text-cell-representing-slot
    (text text-box-format-or-format-name
	  frame slot-name
	  &optional defining-class?
	  slot-component-name? slot-component-indicator
	  virtual-attribute?)
  (let ((text-cell (make-text-cell text text-box-format-or-format-name)))
    (cond (slot-component-name?
	   (note-slot-component-represented-by-text-cell
	     text-cell frame slot-name
	     defining-class?
	     slot-component-name? slot-component-indicator))
	  ((not virtual-attribute?)
	   (note-slot-represented-by-text-cell
	     text-cell frame slot-name defining-class?))
	  (t
	   (note-virtual-attribute-represented-by-text-cell
	     text-cell frame slot-name)))
    text-cell))
  
	  



;;; `Change-text-cell-property' makes the text cell plist of text-cell have the
;;; property specified by indicator and value? or, if value? is nil, not have a
;;; property under indicator.
;;;
;;; Slot value consing or recycling is done as necessary.  Note that all
;;; non-sharable components (i.e., text strings, conses, and slot value floats)
;;; are reclaimed by this function where they exist within the changed section
;;; of the plist.
;;;
;;; Value? is always returned by this function.

(defun-simple change-text-cell-property (text-cell indicator value?)
  (loop as l-trailer? = nil then (cdr-of-cons l)
	as l = (text-cell-plist text-cell)
	     then (cdr-of-cons l-trailer?)
	while l
	when (eq (car-of-cons l) indicator)
	  do (cond
	       (value?
		;; Doesn't reclaim the old value!
		(setf (cadr l) value?))
	       (t (if l-trailer?
		      (setf (cdr l-trailer?) (cddr l))
		      (setf (text-cell-plist text-cell) (cddr l)))
		  (setf (cddr l) nil)
		  (reclaim-slot-value l)))
	     (return value?)
	finally
	  (if value?
	      (setf (text-cell-plist text-cell)
		    (slot-value-cons
		      indicator
		      (slot-value-cons
			value?
			(text-cell-plist text-cell)))))
	  (return value?)))



;;; Note-slot-represented-by-text-cell notes in text-cell that text-cell
;;; represents the slot-name slot of frame, qualified by defining-class?, if
;;; necessary.
;;;
;;; If this is used by the tabular function facility, things are quite
;;; different: then, slot-name is actually an index (a fixnum), and
;;; defining-class? is always nil.  This is an obscure exception that
;;; most of the software may ignore. Thankfully!

(defun-simple note-slot-represented-by-text-cell
    (text-cell frame slot-name defining-class?)
  ;; usually not necessary: (should be optimized!)  -- plan to exploit
  ;; defining-class coming first as a way to optimize plist searches;
  ;; see get-slot-represented-by-text-cell-if-any. (MHD)
  (change-text-cell-property text-cell 'defining-class defining-class?)
  (change-text-cell-property text-cell frame slot-name)
  ;; usually not necessary:  (should be optimized!) 
  (change-text-cell-property text-cell 'slot-component-name nil)
  (change-text-cell-property text-cell 'slot-component-indicator nil))


(defun-simple note-slot-component-represented-by-text-cell
    (text-cell frame slot-name defining-class?
	       slot-component-name slot-component-indicator?)
  (change-text-cell-property text-cell 'defining-class defining-class?)
  (change-text-cell-property text-cell frame slot-name)
  (change-text-cell-property
    text-cell 'slot-component-name slot-component-name)
  (change-text-cell-property
    text-cell 'slot-component-indicator slot-component-indicator?))


(defun-simple note-virtual-attribute-represented-by-text-cell
    (text-cell frame slot-name)
  (change-text-cell-property text-cell frame slot-name)
  (change-text-cell-property text-cell 'virtual-attribute t))



;;; Get-slot-represented-by-text-cell-if-any will, if text-cell represents some
;;; value in a frame, return nine values:
;;;
;;;   (1) the frame;
;;;   (2) either a slot name, the position index of a table-of-values
;;;       arg, or one less than the negative of the position index of a
;;;       table-of-values value;
;;;   (3) either nil or a defining class (if needed to uniquely
;;;       identify the slot);
;;;   (4) either nil or a slot-component name (if applicable);
;;;   (5) either nil or a slot-component indicator (if applicable);
;;;   (6) whether or not the slot represents a virtual attribute (t or nil); and
;;;   (7) either nil or t to indicate that the exported-format feature is enabled
;;;   (8) either nil or t to indicate the text-summarized feature is enabled
;;;   (9) either nil or a display format (e.g., INTERVAL, DEFAULT, TIME-STAMP, etc.)

;;;
;;; When no frame is represented, it returns nil.

;;; Note that [as of 4/16/92 -- 3.0 Beta Rev. 3] this may return a deleted
;;; frame, but only in the degenerate case of a text cell that pointed to a
;;; frame that did not point back to its table.  Only internal functions (in
;;; TABLES) should have to deal with this case.  [Previously, it always could
;;; return a recycled frame, just not a frame that's been deleted but is not
;;; currently recycled. -- MHD, 4/16/92]

;;; Note that this may return a slot name that is not a real slot name, i.e.,
;;; an element of the slot descriptions of the class description in two cases:
;;;
;;; (1) the slot is not any longer part of the class (e.g., it's being removed)
;;;
;;; or
;;;
;;; (2) this is a virtual attribute, in which case the 6th value is t.

(defun get-slot-represented-by-text-cell-if-any (text-cell)
  (loop with frame? = nil
	with slot-name? = nil
	with defining-class? = nil
	with slot-component-name? = nil
	with slot-component-indicator? = nil
	with virtual-attribute? = nil
	with exported-format? = nil
	with text-summarized? = nil
	with display-format? = nil
	for l on (text-cell-plist text-cell) by #'cddr-of-cons
	as indicator = (car-of-cons l)
	as value = (cadr-of-cons l)
	do (cond
	     ((symbolp indicator)
	      (case indicator
		((defining-class class-qualifier) ; class-qualifier is obsolete!
		 (setq defining-class? value))
		(slot-component-name
		 (setq slot-component-name? value))
		(slot-component-indicator
		 (setq slot-component-indicator? value))
		(virtual-attribute
		 (setq virtual-attribute? value))
		(exported-format
		 (setq exported-format? value))
		(text-summarized?
		 (setq text-summarized? value))
		(display-format
		 (setq display-format? value))))
	     (t
	      (setq frame? indicator)
	      (setq slot-name? value)))
	finally
	  (return
	    (values
	      frame? slot-name? defining-class?
	      slot-component-name? slot-component-indicator?
	      virtual-attribute? exported-format? text-summarized?
	      display-format?))))

;; Added display-format. (MHD 1/10/02)

;; Inserted a new third value, defining-class?, pushing the others to further
;; back.  All callers should be fixed.  (MHD 2/15/94)

;; When framep was replaced with frame-or-deleted-frame-p, the only callers that
;; needed to take advantage of the distinction were remove-deleted-frames-in-
;; multiframe-table-rows (TABLES) and clean-up-orphan-frame-representations
;; (KB-LOAD2), a post-loading function.  (MHD 4/16/92)  -- Obsolete comment --
;; now "symbolp" anyway.

;; In 6.0a3 and 6.0b0 releases the above returned nil if slot-name was not (any
;; longer) a valid slot (unless it was a virtual attribute or CLASS).  That
;; caused regressions in code that had to clean up tables with cells for such
;; slots!  It also did not correspond to the documentation, or any known entry
;; in the commit corresponding to this change.  I would like to know why that
;; was done, but my investigation has thus far turned up empty. Today I have
;; undone that change (for 6.0b1) to fix what we know was broken by the
;; change. (MHD 3/8/01)



;;; Get-text-cell-representing-slot-if-any searches table and returns the first
;;; text cell it finds, if any, that represents the following 6-tuple specified
;;; by the arguments:
;;;
;;;   <frame, slot-name, defining-class?,
;;;    slot-component-name, slot-component-indicator?, virtual-attribute?>
;;;    
;;; Normally the search starts from the beginning, i.e., from the first cell in
;;; the first row.  But if remaining-rows-index? is specified, the search begins
;;; there starting with the element indexed by remaining-cells-index?, which
;;; must also be specified in this case.  These args are should normally just be
;;; the second and third values returned from a previous call to this function.
;;;
;;; This second and third values returned are the remaining cells and remaining
;;; rows, respectively, if any.  These may be supplied on subsequent calls to
;;; specify where the search begins.
;;;
;;; When this returns nil as a first value, it means the search failed to find
;;; even one matching cell, and no further search is necessary.  When this
;;; returns nil as a second value, with the first value non-nil, it means that
;;; a cell has been found, but no further search is necessary.

(defun get-text-cell-representing-slot-if-any
    (table frame slot-name defining-class?
     &optional
     slot-component-name? slot-component-indicator?
     remaining-rows-index? remaining-cells-index?
     virtual-attribute-p)
  (loop with cell?
	for row-index from (or remaining-rows-index? 0)
	for rows on (nthcdr row-index (table-rows table))
	as column-index = (or remaining-cells-index? 0) then 0
	as row = (car rows)
	when
	  (multiple-value-setq (cell? column-index)
	    (search-row-for-text-cell-representing-slot
	      row column-index
	      frame slot-name defining-class?
	      slot-component-name? slot-component-indicator?
	      virtual-attribute-p))
	  do (return
	       (values
		 cell?
		 (if (cdr row) row-index (+f row-index 1))
		 (if (cdr row) column-index 0)))))



;;; `Search-row-for-text-cell-representing-slot' searches row for a text cell
;;; representing the designated slot or (slot component), starting at either the
;;; column indicated by starting-column-index?, if any, or else at column 0.
;;;
;;; If a matching text cell is found, it returns the text cell as its first value,
;;; and returns the index the cell as its second value.  If no match is found, it
;;; returns nil.

(defun search-row-for-text-cell-representing-slot
    (row starting-column-index?
	 frame slot-name defining-class?
	 &optional slot-component-name? slot-component-indicator? virtual-attribute?)
  (loop with cell? = nil
	with column-index = (or starting-column-index? 0)
	with remaining-row = (nthcdr column-index row)
	while remaining-row
	do (setq cell? (pop remaining-row))
	   (incff column-index)
	when (and cell?
		  (not (cell-is-block-p cell?))
		  (multiple-value-bind
		      (f sn dc scn sci va) ; Note: some or all can be nil
		      (get-slot-represented-by-text-cell-if-any cell?)
		    (and (eq frame f)
			 (eq slot-name sn)
			 (or slot-component-indicator?
			     slot-component-name?
			     (eq defining-class? dc)) ;; HACK talk to MHD
			 (eq va virtual-attribute?)
			 (cond
			   ((and (null scn) (null sci)) ; master slot
			    t)
			   (t
			    (and (eq slot-component-name? scn)
				 (or
				   (and
				     (eq slot-component-indicator?
					 'default)
				     ;; values eq
				     (multiple-value-bind (value defaulted-p)
					 (get-slot-component-value
					   frame slot-name defining-class?
					   scn sci)
				       (declare (ignore value))
				       defaulted-p))
				   (eq slot-component-indicator? sci))))))))
	  return (values cell? column-index)))





;;; These call the common function used by text-boxes and text-cells.

(def-substitution-macro text-cell-background-color (table text-cell)
  (compute-text-cell-background-color (text-cell-plist text-cell)
				      (text-cell-format text-cell)
				      table
				      nil))

(def-substitution-macro text-cell-background-color-ignoring-highlighting
    (table text-cell)
  (compute-text-cell-background-color (text-cell-plist text-cell)
				      (text-cell-format text-cell)
				      table
				      t))

(def-substitution-macro text-cell-line-color (table text-cell)
  (compute-text-cell-line-color (text-cell-plist text-cell)
				(text-cell-format text-cell)
				table))


(def-substitution-macro text-cell-border-color (table text-cell)
  (compute-text-cell-border-color (text-cell-plist text-cell)
				  (text-cell-format text-cell)
				  table))




;;;; Copying Tables



;;; Copy-table ...  Text cells that represent frame instances always continue to
;;; represent the same frame instances with two exceptions: when the frame
;;; represented is itself or when the frame represented is the superblock of the
;;; table (superior-frame-being-cloned?), text cells then represent the newly
;;; cloned frame, rather than the original.  For example, the expression-to-display
;;; slot is represented by a text cell in the graph itself (graphs are tables), and
;;; thus when cloning a graph, the cloned text cell will represent the cloned graph,
;;; rather than the original graph.  Another example is when you clone an item with
;;; an attribute display as one of its subblocks: in this case superior-frame-being-
;;; cloned? will be the item and the cloned attribute display subblock will represent
;;; the clone of the item, rather than the item.
;;;
;;; Added with-backtrace-for-internal-error. ajs (4/30/96)

(defun copy-table (table new-table &optional superior-frame-being-cloned?)
  (with-backtrace-for-internal-error 'copy-table
    (setf (table-format new-table) (table-format table))
    (setf (row-edges new-table)
	  (copy-tree-using-slot-value-conses (row-edges table)))
    (setf (column-edges new-table)
	  (copy-tree-using-slot-value-conses (column-edges table)))
    (setf (table-rows new-table)	  
	  (loop for table-row in (table-rows table)
		collect
		(loop for cell? in table-row
		      collect (if cell?
				  (if (cell-is-block-p cell?)
				      (let ((new-block (clone-frame cell?)))
					(funcall-method
					  'shift new-block
					  (-w (left-edge-of-block cell?)
					      (left-edge-of-block new-block))
					  (-w (top-edge-of-block cell?)
					      (top-edge-of-block new-block)))
					(add-subblock new-block new-table)
					new-block)
				      (let ((new-text-cell
					      (make-text-cell
						(if (text? cell?)
						    (copy-text (text? cell?)))
						(text-cell-format cell?))))
					(setf (minimum-right-edge-for-cell new-text-cell)
					      (minimum-right-edge-for-cell cell?))
					(incfw (minimum-right-edge-for-cell new-text-cell)
					       (-w (left-edge-of-block table)))
					(setf (text-cell-plist new-text-cell)
					      (copy-for-slot-value
						(text-cell-plist cell?)))
					(loop for l on (text-cell-plist new-text-cell)
						    by #'cddr
					      as (indicator) = l
					      when (framep indicator)
						do (add-frame-representation-if-necessary
						     new-table
						     (cond
						       ((and superior-frame-being-cloned?
							     (eq indicator (superblock? table)))
							;; represents superblock
							(setf (car l) superior-frame-being-cloned?))
						       ((eq indicator table)
							;; represents self
							(setf (car l) new-table))
						       (t
							;; represents some other guy
							indicator))))
					new-text-cell)))
			using slot-value-cons)
		  using slot-value-cons))	    
    new-table))

;; Maybe rename "clone-table" -- document this as a subfunction of clone-frame,
;; which is what it is! (MHD 7/5/94)

;; Fix to handle non-cell table subblocks (?)

;; Redo -- and finish!








;;;; Formatting Tables



;;; Reformat-table-in-place ... also [as of 6/6/91 -mhd] enlarges the workspace table
;;; is on, if any, if necessary.  Leave-text-cells-as-single-lines? is as documented
;;; for make-or-reformat-table.

(defun reformat-table-in-place
    (table &optional leave-text-cells-as-single-lines? minimum-cell-width?)
  (let* ((table-left-edge (left-edge-of-block table))
	 (table-top-edge (top-edge-of-block table)))
    (make-or-reformat-table
      table (table-format table) nil
      nil leave-text-cells-as-single-lines?
      minimum-cell-width?)
    (funcall-method
      'shift table
      (+w (-w (left-edge-of-block table))
	  table-left-edge)
      (+w (-w (top-edge-of-block table))
	  table-top-edge))
    (enlarge-workspace-for-block-rectangle-if-necessary table nil)
    (update-selection-highlights-for-table table)))

;; Consider adding an optional arg to specify what "in-place" means.



;;; `Make-or-reformat-table' ...  Text cells in table-rows need not yet be formatted.
;;; After formatting, the top left corner of the table will be at (0,0).  When the
;;; table-rows-or-table argument is a table, the value of that table's table-format slot
;;; will be entirely ignored and will be replaced by the format specified by the
;;; table-format-or-format-name argument.
;;;
;;; This does nothing to alter the first (rows) or second (cells) level of list
;;; structure in the table rows.  (Neither the argument table rows, if a list, nor
;;; the value of the table-rows slot, if a table.)
;;; 
;;; A table is always left WYSIWYG by this function; therefore, this sets the
;;; frame flag table-may-not-be-wysiwyg of the table to nil.

;;; When leave-text-cells-as-single-lines? is non-nil, all text cells are assumed to
;;; have exactly one line.

;;; Something being formatted (or reformatted) must not be drawn on any image plane at
;;; the time of the (re)formatting.  This certainly includes tables and blocks that are
;;; table cells.

;;; Text regions are deleted from a table that is to be reformatted, because it would be
;;; unduly difficult to update them correctly.

(defmacro exported-table-format-p (table-format-or-format-name)
  `(let ((format-name (cond ((symbolp ,table-format-or-format-name)
			     ,table-format-or-format-name)
			    (t
			     (name-or-names-for-frame
			       ,table-format-or-format-name)))))
     (not (null (memq format-name '(attributes-table-format

				    ;; for New G2 Classic UI:   (MHD 10/4/99)
				    new-attributes-table-format

				    short-representation-table-format
				    attribute-display-table-format
				    ;readout-table-format
				    ;table-format-for-graphs
				    ))))))
	
(defun make-or-reformat-table
    (table-rows-or-table table-format-or-format-name format-of-superblock-if-a-table?
			 &optional (table-class? nil) (leave-text-cells-as-single-lines? nil)
			 (minimum-cell-width? nil))
  (let* ((table-rows
	   (if (atom table-rows-or-table)	; table case
	       (table-rows table-rows-or-table)
	       table-rows-or-table))
	 (foundation-class-for-format
	   (cond ((exported-table-format-p table-format-or-format-name)
		  'table-item)
		 (t
		  'table)))
	 (table-class
	   (progn
	     #+development
	     (when (and table-class?
			(not (subclassp table-class? foundation-class-for-format)))
	       (cerror "go on" "Incompatible table classes - see PBK"))
	     (or table-class?
		 foundation-class-for-format)))
	 (table
	   (if (atom table-rows-or-table)	; table case
	       table-rows-or-table
	       (make-frame table-class)))
	 (table-format
	   (if (symbolp table-format-or-format-name)
	       (get-or-make-format-frame table-format-or-format-name)
	       table-format-or-format-name))
	 (left-border-width
	   (if (and format-of-superblock-if-a-table?
		    (>w (table-column-boundary-width format-of-superblock-if-a-table?)
			0))
	       0
	       (table-left-border-width table-format)))
	 (top-border-width
	   (if (and format-of-superblock-if-a-table?
		    (>w (table-row-boundary-width format-of-superblock-if-a-table?)
			0))
	       0
	       (table-top-border-width table-format)))
	 (right-border-width			; only used once
	   (if (and format-of-superblock-if-a-table?
		    (>w (table-column-boundary-width format-of-superblock-if-a-table?)
			0))
	       0
	       (table-right-border-width table-format)))
	 (bottom-border-width			; only used once
	   (if (and format-of-superblock-if-a-table?
		    (>w (table-row-boundary-width format-of-superblock-if-a-table?)
			0))
	       0
	       (table-bottom-border-width table-format)))
	 (row-edges (row-edges table))
	 (column-edges (column-edges table))
	 (some-cells-are-blocks? nil)
	 (right-edge-of-rightmost-cell 0)
	 bottom-edge-of-bottom-row)
    (when (and (eq table-rows-or-table table) 
	       (has-subblocks-p table))
      (delete-any-text-regions table))
    (loop for l on column-edges
	  do (setf (car l) 0))
    (loop for row in table-rows
	  do (loop with left-edge-of-cell = left-border-width
		   with remainder-of-row = row
		   as right-edge-of-preceding-column
		      = 0
		      then (car remaining-column-edges)
		   as remaining-column-edges
		      = (or column-edges
			    (if (cdr remainder-of-row)
				(setq column-edges
				      (slot-value-list right-edge-of-rightmost-cell))))
		      then (or (cdr remaining-column-edges)
			       (if (cdr remainder-of-row)
				   (cdr (nconc remaining-column-edges
					       (slot-value-list
						 right-edge-of-rightmost-cell)))))
		   as cell? = (car remainder-of-row)
		   when cell?
		     do (let ((right-edge-of-cell
				(+w
				  left-edge-of-cell
				  (if (cell-is-block-p cell?)
				      (progn
					(setq some-cells-are-blocks? t)
					(-w (funcall-method
					      'compute-minimum-right-edge cell?)
					    (left-edge-of-block cell?)))
				      (setf (minimum-right-edge-for-cell cell?)
					    (maxw
					      (format-text-cell
						cell?
						(-w (or (car remaining-column-edges)
							right-edge-of-rightmost-cell)
						    left-edge-of-cell)
						(or leave-text-cells-as-single-lines?
						    (getfq (text-cell-plist cell?)
							   'leave-as-single-line?))
						nil
						(get-text-cell-line-justification
						  (text-cell-format cell?)
						  (text-cell-plist cell?))
						nil)
					      (or minimum-cell-width? 0)))))))
			  (cond
			    (remaining-column-edges
			     (if (>w right-edge-of-cell (car remaining-column-edges))
				 (loop for m on remaining-column-edges
				       do (cond
					    ((=w (car m) right-edge-of-preceding-column)
					     (setf (car m) right-edge-of-cell))
					    (t (let ((excess
						       (-w right-edge-of-cell (car m))))
						 (cond
						   ((>w excess 0)
						    (loop for l on m	; incfws!
							  do (incfw (car l) excess))
						    (incfw right-edge-of-rightmost-cell
							   excess))))
					       (loop-finish)))
				       finally
					 (setq right-edge-of-rightmost-cell
					       (maxw right-edge-of-rightmost-cell
						     right-edge-of-cell))))
			     (setq left-edge-of-cell
				   (+w (car remaining-column-edges)
				       (table-column-boundary-width table-format))))
			    (t (setq right-edge-of-rightmost-cell
				     (maxw right-edge-of-rightmost-cell
					   right-edge-of-cell)))))
		   while (setq remainder-of-row (cdr remainder-of-row))
		   finally
		     (if (null cell?)		; should NEVER happen, but ...
			 (error "NIL as or at end of table row"))))
    (loop for remaining-rows on table-rows
	  as top-edge-of-cell
	     = top-border-width
	     then (+w bottom-edge-of-cell
		      (table-row-boundary-width table-format))
	  as bottom-edge-of-cell
	     = (+w top-edge-of-cell
		   (loop with left-edge-of-next-cell = left-border-width
			 as remaining-column-edges
			    = column-edges
			    then (cdr remaining-column-edges)
			 as cell? in (car remaining-rows)
			 when cell?
			   maximize
			   (if (cell-is-block-p cell?)
			       (-w (funcall-method 'compute-minimum-bottom-edge cell?)
				   (top-edge-of-block cell?))
			       (let ((minimum-width-for-cell
				       (minimum-right-edge-for-cell cell?))
				     (width-for-cell
				       (-w (or (car remaining-column-edges)
					       right-edge-of-rightmost-cell)
					   left-edge-of-next-cell))
				     (text-cell-line-justification?
				       (get-text-cell-line-justification
					 (text-cell-format cell?)
					 (text-cell-plist cell?))))
				 (if (>w width-for-cell minimum-width-for-cell)
				     (let ((single-line?
					     (or leave-text-cells-as-single-lines?
						 (loop with line-in-text-already? = nil
						       as text-element in (text? cell?)
						       when (text-line-p text-element)
							 do (if line-in-text-already?
								(return nil))
							    (setq line-in-text-already? t)
						       finally (return t)))))
				       (if (or (not single-line?)
					       text-cell-line-justification?)
					   (format-text-cell
					     cell? width-for-cell
					     single-line? t nil
					     text-cell-line-justification?))))
				 (setf (minimum-right-edge-for-cell cell?)
				       (+w left-edge-of-next-cell
					   minimum-width-for-cell))
				 (if remaining-column-edges
				     (setq left-edge-of-next-cell
					   (+w (car remaining-column-edges)
					       (table-column-boundary-width
						 table-format))))
				 (compute-height-for-text-cell cell?)))
			     using maxf))
	  as remaining-row-edges
	     = (or row-edges
		   (if (cdr remaining-rows)
		       (setq row-edges (slot-value-list nil))))
	     then (or (cdr remaining-row-edges)
		      (if (cdr remaining-rows)
			  (cdr (nconc remaining-row-edges (slot-value-list nil)))))
	  when remaining-row-edges
	    do (setf (car remaining-row-edges) bottom-edge-of-cell)
	  finally
	    (setq bottom-edge-of-bottom-row bottom-edge-of-cell))
    (when some-cells-are-blocks?
      (loop for row in table-rows
	    as top-edge-of-cells-in-row
	       = top-border-width
	       then (+w (car remaining-row-edges)
			(table-row-boundary-width table-format))
	    as remaining-row-edges
	       = row-edges
	       then (cdr remaining-row-edges)
	    do (loop with left-edge-of-next-cell = left-border-width
		     as remaining-column-edges
			= column-edges
			then (cdr remaining-column-edges)
		     as cell? in row
		     when cell?
		       do (cond
			    ((cell-is-block-p cell?)
			     (let ((width-for-block
				     (-w (or (car remaining-column-edges)
					     right-edge-of-rightmost-cell)
					 left-edge-of-next-cell))
				   (height-for-block
				     (-w (or (car remaining-row-edges)
					     bottom-edge-of-bottom-row)
					 top-edge-of-cells-in-row)))
			       (if (or (not (=w (width-of-block cell?)
						width-for-block))
				       (not (=w (height-of-block cell?)
						height-for-block)))
				   (funcall-method
				     'resize cell?
				     width-for-block height-for-block nil)))
			     (funcall-method
			       'shift cell?
			       (-w left-edge-of-next-cell
				   (left-edge-of-block cell?))
			       (-w top-edge-of-cells-in-row
				   (top-edge-of-block cell?)))
			     (if (not (eq table-rows-or-table
					  table))	; if not reformatting
				 (add-subblock cell? table))))
			  (if remaining-column-edges
			      (setq left-edge-of-next-cell
				    (+w (car remaining-column-edges)
					(table-column-boundary-width
					  table-format)))))))
    (setf (table-format table) table-format)
    (setf (row-edges table) row-edges)
    (setf (column-edges table) column-edges)
    (setf (table-rows table) table-rows)

    (change-edges-of-block table 0 0
			   (+w right-edge-of-rightmost-cell right-border-width)
			   (+w bottom-edge-of-bottom-row bottom-border-width))

    (clear-table-may-not-be-wysiwyg table)	; (MHD 6/29/92)
    
    table))

;; Make the optional args non-optional!

;; Consider assuming, optionally, that text cell plists are null.

;; Consider having a function to remove nils from the end of table rows.



;;; Compute-height-for-text-cell ... includes the top and bottom margins in its result.
;;; It returns the sum of the top and bottom margins if the text cell has no text.

(defun compute-height-for-text-cell (text-cell)
  (compute-height-for-text
    (text? text-cell) (text-cell-format text-cell) (text-cell-plist text-cell)))



(def-class-method compute-minimum-right-edge (table)
  (+w (loop with rightmost-column-index	; keep as slot of table?
	      = (loop for row in (table-rows table)
		      maximize (length row) using maxf)
	    as row in (table-rows table)
	    as cell? = (nth rightmost-column-index row)
	    when cell?
	      maximize (if (cell-is-block-p cell?)
			   (funcall-method 'compute-minimum-right-edge cell?)
			   (minimum-right-edge-for-cell cell?))
		using maxf)
      (if (and (subtablep table)		; unlikely ever to be false in practice
	       (>w (table-column-boundary-width (table-format (superblock? table))) 0))
	  0
	  (table-right-border-width (table-format table)))))



(def-class-method compute-minimum-bottom-edge (table)
  (+w (loop as cell? in (car (last (table-rows table)))
	    when cell?
	      maximize (if (cell-is-block-p cell?)
			   (funcall-method 'compute-minimum-bottom-edge cell?)
			   (compute-height-for-text-cell cell?))
		using maxf)
      (if (and (subtablep table)			; unlikely ever to be false in practice
	       (>w (table-row-boundary-width (table-format (superblock? table))) 0))
	  0
	  (table-bottom-border-width (table-format table)))))



;(def-class-method compute-data-for-resize
;       (table new-right-edge-for-table? new-bottom-edge-for-table?)
;  table
;  (values new-right-edge-for-table?
;	  new-bottom-edge-for-table?
;	  new-right-edge-for-table?
;	  new-bottom-edge-for-table?
;	  new-bottom-edge-for-table?
;	  nil))

;; Code this!



;(def-class-method resize (table right-edge-for-table bottom-edge-for-table
;				other-data-for-resizing)
;  table right-edge-for-table bottom-edge-for-table other-data-for-resizing)

;; Code this!



;(defun compute-data-for-text-cell-reformatting
;       (text-cell new-right-edge-for-cell minimum-bottom-edge-for-cell
;	old-top-edge-of-cell old-bottom-edge-of-cell)
;  text-cell old-top-edge-of-cell old-bottom-edge-of-cell
;  (values new-right-edge-for-cell
;	  minimum-bottom-edge-for-cell
;	  new-right-edge-for-cell
;	  minimum-bottom-edge-for-cell
;	  minimum-bottom-edge-for-cell
;	  nil))

;; Move this farther down!

;; This probably needs more args and should probably return the reformatted text.









;;;; Highlighting Cells



;;; `Highlight-or-unhighlight-cell' highlights or unhighlights cell in table, per
;;; unhighlight-case?, if cell is a text cell.  (Someday it might highlight cell in
;;; some way if it is not a text cell.)

;;; If highlight-color? is nil, the color or metacolor used is the the line-color
;;; property of the text cell plist for cell, if that is non-nil, or else the
;;; value of the text-cell-line-color? slot of the text cell format of cell, if
;;; that is non-nil, or else FOREGROUND.  Highlight-color? is ignored in the
;;; unhighlight case.

;;; If text-region-class? is specified, highlighting means highlighting the entire
;;; text as a text region of this class; otherwise, highlighting means highlighting
;;; the text cell by changing its highlight color (in a way that makes the text come
;;; out in a false color, with FOREGROUND causing foreground/background color
;;; reversal).

;;; This returns nil only in three cases: (1) when cell is not a text cell,
;;; (2) in the highlight case when cell is already highlighted as specified, and
;;; (3) in the unhighlight case when cell is not highlighted (which could occur,
;;; for example, when a new name box is created within the editor).

(defun highlight-or-unhighlight-cell
    (cell table highlight-color? unhighlight-case?
	  &optional text-region-class?)
  (unless (cell-is-block-p cell)
    (let ((highlight-color
	    (or highlight-color?
		(text-cell-line-color table cell))))
      (cond (text-region-class?
	     (loop for subblock being each subblock of table
		   when (and (frame-of-class-p subblock text-region-class?)
			     (multiple-value-bind
				 (row-index column-index)
				 (get-table-cell-indices table cell)
			       (and (=f (get-slot-value	; forward reference
					  subblock 'row-index-for-text-region-cell?)
					row-index)
				    (=f (get-slot-value	; forward reference
					  subblock 'column-index-for-text-region-cell?)
					column-index))))
		     do (cond
			  (unhighlight-case?
			   (delete-frame subblock)
			   (return t))
			  ((eq (get-slot-value	; forward reference
				 subblock 'text-highlight-bar-color)
			       highlight-color)
			   (return nil))
			  (t
			   (delete-frame subblock)
			   (loop-finish)))
		   finally
		     (when (not unhighlight-case?)
		       (return (make-text-region
				 table cell 1 0 'end nil nil text-region-class?)))))
	    (t
	     (let ((old-highlight-color?
		     (getf (text-cell-plist cell) 'highlight-color)))
	       (when (if unhighlight-case?
			 old-highlight-color?
			 (not (eq old-highlight-color? highlight-color)))
		 (change-color-of-text-cell
		   table cell nil 
		   (if (not unhighlight-case?) highlight-color)
		   :no-change :no-change
		   'highlight))))))))

;; This is a bit slower than before.

;; This might need work in the nested highlight case.

;; To highlight or unhighlight without changing the color of the text, it would be
;; necessary to erase, then change the highlight color property, and then redraw.  This
;; would be less efficient than what is now done.

;; Consider having this keep a stack of old highlight colors on the text cell plist.



;;; `Change-color-of-text-cell' ... When new-text-color? is nil, the original
;;; text color (as specified in the text box format) is implied.  When new-
;;; text-color? is :no-change, no change is done at all.  The analagous
;;; convention holds for new-border-color? and new-background-color?.

;;; Whenever color-change-case? is HIGHLIGHT, note-as-kb-state-change? should
;;; always be nil, and new-background-color? should never be :no-change.

(defun change-color-of-text-cell
    (table text-cell note-as-kb-state-change?
	   new-background-color? new-border-color? new-text-color? 
	   &optional (color-change-case? t))
  (let* ((do-not-note-permanent-changes-p note-as-kb-state-change?)
	 (old-background-color
	   (text-cell-background-color table text-cell))
	 (new-background-color
	   (cond ((eq color-change-case? 'highlight)
		  new-background-color?)
		 ((eq new-background-color? :no-change)
		  nil)
		 (t
		  (or new-background-color?
		      old-background-color))))
	 (new-background-color-really
	   ;; This is the truely non-NIL new background color.  We need to know
	   ;; what it is in order to see whether it is transparent.
	   (or new-background-color
	       (cond ((eq color-change-case? 'highlight)
		      (text-cell-background-color-ignoring-highlighting table text-cell))
		     ((eq new-background-color? :no-change)
		      old-background-color))))

	 (old-border-color
	   (text-cell-border-color table text-cell))
	 (new-border-color
	   (if (neq new-border-color? :no-change)
	       (or new-border-color?
		   old-border-color)))

	 (old-text-color
	   (text-cell-line-color table text-cell))
	 (new-text-color
	   (if (neq new-text-color? :no-change)
	       (or new-text-color?
		   old-text-color)))

	 (becoming-transparent?
	   (or (and (neq new-background-color? :no-change)
		    (neq new-background-color old-background-color)
		    (or (eq new-background-color-really 'background) ; Note A.
			(transparent-color-p new-background-color-really)))
	       (and (neq new-border-color? :no-change)
		    (neq new-border-color old-border-color)
		    (transparent-color-p new-border-color))
	       (and (neq new-text-color? :no-change)
		    (neq new-text-color old-text-color)
		    (transparent-color-p new-text-color)))))

    (macrolet ((kb-update ()
		 `(cond
		    ((eq color-change-case? 'highlight)
		     (change-text-cell-property
		       text-cell
		       'highlight-color new-background-color?))
		    (t
		     (when note-as-kb-state-change?		; IMPLEMENT THIS!
		       (note-kb-state-change text-cell 'text-cell-color-pattern))
		     (when new-background-color
		       (change-text-cell-property
			 text-cell 'background-color new-background-color?))
		     (when new-border-color
		       (change-text-cell-property
			 text-cell 'border-color new-border-color?))
		     (when new-text-color
		       (change-text-cell-property
			 text-cell 'line-color new-text-color?))))))

      (cond ((and (paint-mode-p)
		  (or (appropriate-to-invalidate-color-of-block?
			table becoming-transparent?)
		      becoming-transparent?)		    ; Note B
		  (or scheduled-text-highlighting
		      (neq color-change-case? 'highlight)))

	     (kb-update)
	     (invalidate-text-cell-of-table table text-cell))

	    (t
	     ;; The clipping region, which is the entire table since that's the only
	     ;; block we have lying around, is way too big here.
	     (do-color-revision (table becoming-transparent?)
		 (draw-or-change-color-in-table
		   table text-cell nil
		   color-change-case? new-background-color new-text-color new-border-color)
	       (kb-update)))))))

;; See the parallel function change-color-of-text-box in module BOXES.

;; Note A: For text-cells, a background-color of BACKGROUND behaves the same as
;; transparent in 3.0.  In order to get an opaque color the same as the WS
;; background, one must explicitly copy the color in.

;; Note B: Since we are invalidating the entire text-cell, rather than just colors
;; of the text-cell, the transparent case can fall through here. We get a better
;; clipping rectangle that way, due to misfeatures of do-color-revision.
;; -fmw, 12/28/94

;; Extensively revised for new color functionality.  LH should go over.
;; (MHD 7/21/89)

;; Have "new-background-color?" be "new-background-color-or-no-change?" and have
;; "new-background-color" be "new-background-color?", etc!

;; Consider setting the relevant property to nil in the case where both
;;   (a) it would be given the same value as in the text box format; and
;;   (b) note-as-kb-state-change? is nil. (MHD)

;; Consider having a new border color apply also to row and column boundaries.

;; Note that the interpretation given to :no-change and nil in this function
;; is unique.  Consider having the same interpretation in draw-or-change-
;; color-of-table.  Then the logic above could be simpler, and one wouldn't
;; need to encode the defaulting hierarchy separately here; also, that may
;; even need to be done as part of unkludging WHITE and BLACK above! (MHD)





;;; The function `invalidate-text-cell-of-table' invalidates the region
;;; of the table which encompasses the given text-cell.

(defun invalidate-text-cell-of-table (table text-cell)
  (let ((workspace? (get-workspace-if-any table)))
    (when workspace?
      (multiple-value-bind (left top right bottom)
	  (compute-edges-of-text-cell table text-cell)
	#+development
	(when (null left)
	  (cerror "Crash" "Text cell ~s is not in table ~s" text-cell table))
	(invalidate-rectangle-of-block workspace? table left top right bottom)))))





;;;; Drawing Tables



;;; The `draw-for-table' method draws borders, cell boundaries, cell
;;; backgrounds, text lines, text regions, and (in old kbs only) name boxes.
;;; Cells that are blocks are subblocks of the table, and hence are drawn by
;;; the harness.

(def-class-method draw (table)
;  (unless (maybe-defer-refreshing-image-plane current-image-plane))  ; Hmm.
  (draw-or-change-color-in-table table nil nil nil nil nil nil))




;;; The function `draw-or-change-color-in-table' is responsable for all table
;;; drawing, both complete redraws and incremental updates.

;;; When text-cell-to-draw-or-change? is specified, only that cell is drawn or
;;; changed.  When unmagnified-width-of-text-to-draw-beyond? is specified
;;; (together with text-cell-to-draw-or-change?), that amount of the text in the
;;; text cell (just to the right of the left margin) will not be drawn, and the
;;; text cell background will not be drawn at all.

;;; Color-change-case? must be one of the following:
;;;   HIGHLIGHT     -- temporary (undoable) highlight 
;;;   T             -- permanent color change
;;;   NIL           -- not a color change, ie, a full redraw.
;;;   BOUNDING-BOX  -- compute text-cell bounding box, drawing nothing.

;;; In the highlight case, new-background-color? is the new highlight color or
;;; nil for unhighlighting.  When color-change-case? is HIGHLIGHT or T and
;;; text-cell-to-draw-or-change?  is nil, the same color change is applied to
;;; all cells in table.  New-text-color? and new-border-color? are only
;;; relevant when color-change-case? is non-nil.  New-border-color? may only be
;;; specified when text-cell-to-draw-or-change? is not specified.

;;; When the scale is too small for details or the text is too small to draw or
;;; table is being dragged, no text is drawn.

;;; When computing the bounding box, this function is called WITHOUT being
;;; on-window.

(defun draw-or-change-color-in-table
    (table text-cell-to-draw-or-change?
	   unmagnified-width-of-text-to-draw-beyond?
	   color-change-case?
	   highlight-or-new-background-color?
	   new-text-color? new-border-color?)
  (let ((multi-cell-drawing?
	  (and (null text-cell-to-draw-or-change?)
	       (null color-change-case?)))
	(just-bounding-box-please
	  (eq color-change-case? 'bounding-box)))

    (loop with table-format = (table-format table)
	  ;; These are set explicitly during the scan.
	  with current-text-box-format = current-text-box-format ; This is binding probably not needed.
	  with current-text-cell-plist = nil ; Prob. not needed, but must be bound per text cell
	  with current-image-x-scale = current-image-x-scale
	  with current-image-y-scale = current-image-y-scale
	  with image-x-scale-of-table = current-image-x-scale
	  with image-y-scale-of-table = current-image-y-scale
	  with format-of-superblock-if-a-table?
	    = (if (subtablep table)
		  (table-format (superblock? table)))
	  with left-border-width
	    = (if (and format-of-superblock-if-a-table?
		       (>w (table-column-boundary-width
			     format-of-superblock-if-a-table?)
			   0))
		  0
		  (table-left-border-width table-format))
	  with top-border-width
	    = (if (and format-of-superblock-if-a-table?
		       (>w (table-row-boundary-width
			     format-of-superblock-if-a-table?)
			   0))
		  0
		  (table-top-border-width table-format))
	  with right-border-width
	    = (if (and format-of-superblock-if-a-table?
		       (>w (table-column-boundary-width
			     format-of-superblock-if-a-table?)
			   0))
		  0
		  (table-right-border-width table-format))
	  with bottom-border-width
	    = (if (and format-of-superblock-if-a-table?
		       (>w (table-row-boundary-width
			     format-of-superblock-if-a-table?)
			   0))
		  0
		  (table-bottom-border-width table-format))
	  with suppress-details?
	    = (or (scale-too-small-for-details-p
		    current-image-x-scale current-image-y-scale)
		  (block-is-currently-being-dragged-p table)
		  ;; Same code occurs in draw-or-change-color-of-text-box;
		  ;; the following was added here to support attribute
		  ;; displays. (MHD 6/6/91)
		  (loop for superblock? = (superblock? table)
					then (superblock? superblock?)
			while superblock?
			thereis (block-is-currently-being-dragged-p superblock?)))
	  with force-hairline-border?
	    = (if suppress-details?
		  (and (=w left-border-width 0)
		       (=w top-border-width 0)
		       (=w right-border-width 0)
		       (=w bottom-border-width 0)
		       ;; other conditions? C.f. draw method of text-box.
		       ))
	  with table-line-color-value
	    = (let ((table-line-color?
		      (or (table-line-color? table-format)
			  (if format-of-superblock-if-a-table?
			      (or (table-line-color? format-of-superblock-if-a-table?)
				  (loop as supertable
					   = (superblock? table)
					   then (superblock? supertable)
					thereis
					(table-line-color? (table-format supertable))
					while (subtablep supertable)))))))
		(if table-line-color?
		    (map-color-or-metacolor-to-color-value table-line-color?)
		    current-foreground-color-value))

	  with left-edge-of-table-in-window
	    = (x-in-window (left-edge-of-block table))
	  with left-edge-of-table-interior-in-window
	    = (+r left-edge-of-table-in-window
		  (cond
		    ((>w left-border-width 0)
		     (maxr (delta-x-in-window left-border-width current-image-x-scale)
			   1))
		    (force-hairline-border? 1)
		    (t 0)))
	  with top-edge-of-table-in-window
	    = (y-in-window (top-edge-of-block table))
	  with top-edge-of-table-interior-in-window
	    = (+r top-edge-of-table-in-window
		  (cond
		    ((>w top-border-width 0)
		     (maxr (delta-y-in-window top-border-width current-image-y-scale)
			   1))
		    (force-hairline-border? 1)
		    (t 0)))
	  with right-edge-of-table-in-window
	    = (x-in-window (right-edge-of-block table))
	  with right-edge-of-table-interior-in-window
	    = (-r right-edge-of-table-in-window
		  (cond
		    ((>w right-border-width 0)
		     (maxr (delta-x-in-window right-border-width current-image-x-scale)
			   1))
		    (force-hairline-border? 1)
		    (t 0)))
	  with bottom-edge-of-table-in-window
	    = (y-in-window (bottom-edge-of-block table))
	  with bottom-edge-of-table-interior-in-window
	    = (-r bottom-edge-of-table-in-window
		  (cond
		    ((>w bottom-border-width 0)
		     (maxr (delta-y-in-window bottom-border-width current-image-y-scale)
			   1))
		    (force-hairline-border? 1)
		    (t 0)))
	  with row-boundary-width-in-window
	    = (let ((row-boundary-width
		      (table-row-boundary-width table-format)))
		(if (=w row-boundary-width 0)
		    0
		    (maxr				; minimum 1
		      1 (delta-y-in-window row-boundary-width current-image-y-scale))))
	  with row-boundary-color-difference?
	    = (if multi-cell-drawing?
		  (let ((row-boundary-color? (table-row-boundary-color? table-format)))
		    (color-difference
		      (if row-boundary-color?
			  (map-color-or-metacolor-to-color-value row-boundary-color?)
			  table-line-color-value)
		      current-background-color-value)))
	  with column-boundary-width-in-window
	    = (let ((column-boundary-width
		      (table-column-boundary-width table-format)))
		(if (=w column-boundary-width 0)
		    0
		    (maxr				; minimum 1
		      1 (delta-x-in-window column-boundary-width current-image-x-scale))))
	  with column-boundary-color-difference?
	    = (if multi-cell-drawing?
		  (let ((column-boundary-color? (table-column-boundary-color? table-format)))
		    (color-difference
		      (if column-boundary-color?
			  (map-color-or-metacolor-to-color-value column-boundary-color?)
			  table-line-color-value)
		      current-background-color-value)))
	  with remaining-row-edges = (row-edges table)
	  initially
	    (when (and (or multi-cell-drawing? new-border-color?)
		       (not just-bounding-box-please))
	      (let ((border-color-difference
		      (if (and color-change-case? (null new-border-color?))
			  (color-meaning-no-change)
			  (let* ((border-color?
				   (table-border-color? table-format))
				 (border-color-value
				   (if border-color?
				       (map-color-or-metacolor-to-color-value
					 border-color?)
				       table-line-color-value)))
			    (if color-change-case?
				(color-difference
				  (map-color-or-metacolor-to-color-value
				    new-border-color?)
				  border-color-value)
				(color-difference
				  border-color-value
				  current-background-color-value))))))
		;; See similar code in draw-or-change-color-of-text-box.
		(draw-solid-rectangle		; top border, if any
		  left-edge-of-table-in-window top-edge-of-table-in-window
		  right-edge-of-table-in-window top-edge-of-table-interior-in-window
		  border-color-difference)
		(draw-solid-rectangle		; bottom border, if any
		  left-edge-of-table-in-window bottom-edge-of-table-interior-in-window
		  right-edge-of-table-in-window bottom-edge-of-table-in-window
		  border-color-difference)
		(draw-solid-rectangle		; left border, if any
		  left-edge-of-table-in-window top-edge-of-table-interior-in-window
		  left-edge-of-table-interior-in-window
		  bottom-edge-of-table-interior-in-window
		  border-color-difference)
		(draw-solid-rectangle		; right border, if any
		  right-edge-of-table-interior-in-window
		  top-edge-of-table-interior-in-window
		  right-edge-of-table-in-window bottom-edge-of-table-interior-in-window
		  border-color-difference)))
	  ;; Return early here if suppressing details and/or dragging? (MHD)
	  as row in (table-rows table)
	  as top-edge-of-cell-in-window
	     = top-edge-of-table-interior-in-window
	     then top-edge-of-next-cell-in-window
	  as bottom-edge-of-previous-cell-in-window
	     = top-edge-of-table-in-window	; cute (must be < bottom-edge-of-cell-in-window)
	     then bottom-edge-of-cell-in-window
	  as bottom-edge-of-cell-in-window
	     = (if remaining-row-edges
		   (y-in-window (pop remaining-row-edges))
		   bottom-edge-of-table-interior-in-window)
	  as top-edge-of-next-cell-in-window	; "loose" for last row
	     = (+r bottom-edge-of-cell-in-window row-boundary-width-in-window)
	  until (>=r top-edge-of-cell-in-window bottom-edge-of-draw-area)
	  doing
      (when (and (>r top-edge-of-next-cell-in-window top-edge-of-draw-area)
		 (or (null text-cell-to-draw-or-change?)
		     (memq text-cell-to-draw-or-change? row)))	; do in-line?
	(multiple-value-bind (cell-left cell-right)
	    (loop with remaining-column-edges = (column-edges table)
		  with remainder-of-row = row
		  while remainder-of-row	; end test in unusual position
		  as left-edge-of-cell-in-window
		     = left-edge-of-table-interior-in-window
		     then left-edge-of-next-cell-in-window
		  as cell = (loop thereis (pop remainder-of-row)	; loses if only nils left
				  do (pop remaining-column-edges))
		  as right-edge-of-cell-in-window
		     = (if remaining-column-edges
			   (x-in-window (pop remaining-column-edges)) 
			   right-edge-of-table-interior-in-window)
		  as left-edge-of-next-cell-in-window	; "loose" for last column
		     = (+r right-edge-of-cell-in-window
			   column-boundary-width-in-window)
		  until (>=r left-edge-of-cell-in-window right-edge-of-draw-area)
		  when (and (>r left-edge-of-next-cell-in-window left-edge-of-draw-area)
			    (or (null text-cell-to-draw-or-change?)
				(eq cell text-cell-to-draw-or-change?)))

		    ;; No longer supposed to draw our subblocks. But for now leave it in.
		    do (cond (just-bounding-box-please
			      nil)
			     ((cell-is-block-p cell)
			      ;; See note A.
			      (draw cell))
			     (t
			      (draw-or-change-color-in-text-cell-for-block
				table
				image-x-scale-of-table
				image-y-scale-of-table
				
				color-change-case?
				new-text-color?
				suppress-details?
				highlight-or-new-background-color?
				unmagnified-width-of-text-to-draw-beyond?
				
				(text? cell)
				(text-cell-format cell)
				(text-cell-plist cell)
				
				left-edge-of-cell-in-window
				top-edge-of-cell-in-window
				right-edge-of-cell-in-window
				bottom-edge-of-cell-in-window)))

		      ;; For the bounding-box case, return the cell edges
		       (when text-cell-to-draw-or-change?
			 (return (values left-edge-of-cell-in-window
					 right-edge-of-cell-in-window)))

		       (when (and multi-cell-drawing?
				  (not (=r right-edge-of-cell-in-window
					   right-edge-of-table-interior-in-window))
				  (>r column-boundary-width-in-window 0))	; optimization only
			 (draw-solid-rectangle	; column boundary, if any
			   right-edge-of-cell-in-window top-edge-of-cell-in-window
			   left-edge-of-next-cell-in-window
			   bottom-edge-of-cell-in-window
			   column-boundary-color-difference?)))

	  (when text-cell-to-draw-or-change?
	    (return (values cell-left top-edge-of-cell-in-window
			    cell-right bottom-edge-of-cell-in-window)))

	  (when (and multi-cell-drawing?
		     (not just-bounding-box-please)
		     (not (=r bottom-edge-of-cell-in-window
			      bottom-edge-of-table-interior-in-window))
		     (>r row-boundary-width-in-window 0)	; optimization only
		     ;; The following prevents two adjacent boundary lines from 
		     ;; xoring eachother; put in for the sake of spacers; see
		     ;; MENUS.  (MHD/BAH 6/6/91)
		     (not (=r bottom-edge-of-cell-in-window
			      bottom-edge-of-previous-cell-in-window)))
	    (draw-solid-rectangle		; row boundary, if any
	      left-edge-of-table-interior-in-window
	      bottom-edge-of-cell-in-window
	      right-edge-of-table-interior-in-window
	      top-edge-of-next-cell-in-window
	      row-boundary-color-difference?)))))))

;; Note A: This call to DRAW should not be here: the drawing harness is
;; supposed to take case of drawing all subblocks.  At the moment, the only
;; classes of table subblocks are ICON-CELL, whose draw method is a no-op, and
;; GRAPH-GRID and GRAPH-AXIS-LABEL.  So, only graph subblocks are really drawn
;; here.



;;; The function `compute-edges-of-text-cell' returns the edges of the
;;; given text-cell in its table, in workspace units.  It's implmentation
;;; resorts to some trickery to convince the text-cell drawing function
;;; above to return a workspace-units bounding rectangle instead of
;;; drawing.

(defun compute-edges-of-text-cell (table text-cell)
  (let ((window (window-for-workstation
		  (or (if servicing-workstation?
			  current-workstation)
		      (car (last workstations-in-service))))))
    (on-window-without-drawing (window)
      (let ((current-image-x-scale (normalized-scale))	
	    (current-image-y-scale (normalized-scale))
	    (current-x-origin-of-drawing 0)
	    (current-y-origin-of-drawing 0)
	    (left-edge-of-draw-area (left-edge-of-block table))
	    (top-edge-of-draw-area (top-edge-of-block table))
	    (right-edge-of-draw-area (right-edge-of-block table))
	    (bottom-edge-of-draw-area (bottom-edge-of-block table)))

	;; The above creates a dynamic extent which simulates that of drawing on a
	;; unit-scale image plane. Which window doesn't matter.
	(draw-or-change-color-in-table table text-cell nil 'bounding-box nil nil nil)))))





;;; The function `compute-background-color-value-for-block' attempts to compute
;;; the color-value of the background against which the given block is drawn.
;;; It was implemented to handle button-labels on action-buttons, and so
;;; handles only that case.  But it might someday be a general facility to make
;;; XOR drawing easier. -fmw

(defun compute-background-color-value-for-block (block)
  (let ((superblock? (superblock? block)))
    (cond ((and (frame-of-class-p block 'button-label)
		superblock?
		(frame-of-class-p superblock? 'generic-action-button))
	   (let ((color?
		   (background-color-of-generic-action-button
		     superblock?)))
	     (if color?
		 (map-color-or-metacolor-to-color-value color?)
		 current-background-color-value)))
	  (t
	   current-background-color-value))))



;;; `Draw-or-change-color-in-text-cell-for-block' contains the knowledge of how to
;;; render a text cell onto the screen.  A text cell consists of some text over
;;; a colored background.  It works for either XOR or PAINT drawing.  It handles
;;; the details of getting the colors right.

;;; It can draw from scratch managing the stored text-box-format,
;;; text-cell-plist, highlighting, and scalling.

;;; It can do a number of incremental changes to the text:
;;;  (1) turn highlighting on.
;;;  (2) turn highlighting off.
;;;  (3) changing the background color
;;;  (4) changing the text color

;;; If the caller knows that only the end of the text has changed (for
;;; example "temp of tank 14 is 12" -> "temp of tank 14 is 13") he
;;; may pass unmagnified-width-of-text-to-draw-beyond? to clip the 
;;; drawing to just that portion.

;;; It will suppress the drawing of the text entirely in a number of situations.
;;;   1. the parameter suppress-details? is true
;;;   2. scale-too-small-for-details-p is true
;;;   3. text-too-small-to-draw-p is true
;;;   4. parent object is being dragged.

(defun-void draw-or-change-color-in-text-cell-for-block
    (block
	image-x-scale-of-table
      image-y-scale-of-table
      
      color-change-case?
      new-text-color?
      suppress-details?
      highlight-or-new-background-color?
      unmagnified-width-of-text-to-draw-beyond?
      
      text
      text-box-format
      text-cell-plist
      
      left-edge-of-cell-in-window
      top-edge-of-cell-in-window
      right-edge-of-cell-in-window
      bottom-edge-of-cell-in-window)
  
  ;; This kind of code puts hair on your chest.

  ;; We want to bind four variables:
  ;;  {existing,final}-{text,background}-color-values
  ;; and then we will draw the background, followed by
  ;; the text if the existing value differs from the
  ;; final value.

  ;; The color difference we want to lay down is, of course, the
  ;; difference between the existing and the background.  To assure that
  ;; both XOR and Painting work, we must be sure to get
  ;; current-background-color-value bound correctly when we do the
  ;; drawing.

  ;; The first layer of complexity is provided by the way
  ;; that the color is inherited in text cells.  
  ;; Current-{foreground,background}-color-value may be
  ;; refined twice, first by text-cell-format, and 
  ;; second by text-cell-plist.

  ;; The second layer of complexity comes from highlighting.  A
  ;; highlighted text cell has its foreground and background colors
  ;; swapped.

  ;; A third layer of complexity comes from the color change cases.
  ;; There are two dimensions to this.  First, in the color change cases
  ;; the existing colors are the old colors, not the erased colors.
  ;; Second, in the color change cases the new color(s) are specified by
  ;; the args to this function, but the existing colors are still stored
  ;; in the text cell.

  ;; The unmagnified-width-of-text-to-draw-beyond? to draw beyond is analagous
  ;; to a color change case in that the background is already on screen in this
  ;; case.

  ;; A fourth layer of complexity comes from the entanglements around the text
  ;; drawing. First we have to set up the context appropriate to call
  ;; new-draw-text.  That includes setting the scaling,
  ;; current-text-box-format, and the current foreground/background
  ;; color values.  Secondly the text drawing may be supressed entirely
  ;; if the the text is either too small, or ????.

  ;; A final bit of complexity comes from supressing the
  ;; drawing if the existing and final color values are identical, i.e.,
  ;; the color difference is 0.

  ;; The routine proceeds in stages:
  ;;  1. Bind the color values we need.
  ;;  2. Do the drawing.
  ;; In the first stage we have these steps.
  ;;  1a. Compute the text cell's inherited colors, i.e.,
  ;;      cell-{background,text}-color-value
  ;;  1b. Compute the existing colors.
  ;;  1c. Pick apart the color change parameters into the
  ;;     flags and values we need.
  ;;  1d. Compute the final colors.

  image-x-scale-of-table
  image-y-scale-of-table
  (macrolet ((swap (a b) `(let ((temp ,a)) (setf ,a ,b) (setf ,b temp))))
    (with-background-color-value (compute-background-color-value-for-block block)

      (let* ((current-foreground-color-value
	       current-foreground-color-value)
	     
	     (table?
	       (if (table-p block) block))
	     
	     ;; Start 1a: Compute current colors of text-cell due to inheritance.
	     (cell-background-color
	       (compute-text-cell-background-color
		 text-cell-plist text-box-format table? t))

	     (cell-text-color
	       (compute-text-cell-line-color
		 text-cell-plist text-box-format table?))
	     ;; End 1a

	     (ordinary-color-change?
	       (memq-p-macro color-change-case? '(t highlight)))
	     
	     ;; Start 1b: Compute the existing colors
	     (existing-background-color
	       (if ordinary-color-change?
		   cell-background-color
		   'background))
	     
	     (existing-text-color			    ; Rebound below, if background is drawn.
	       (if ordinary-color-change?
		   cell-text-color
		   'background))
	     
	     (highlighted-before
	       (getfq text-cell-plist 'highlight-color)))
	

	(when (and highlighted-before ordinary-color-change?)
	  (swap existing-background-color existing-text-color))
	;; End 1b, but note we rebind existing-text-color if any background is drawn.

	(let* (;; Start 1c: Pick apart the color change parameters into the
	       ;;           flags and values we need.
	       
	       ;; Highlight cases
	       (highlighted-after (if (eq color-change-case? 'highlight)
				      (if highlight-or-new-background-color?
					  t                 ;; Turning it on.
					  nil)              ;; Turning it off.
				      highlighted-before))  ;; Already on.
	       
	       ;; New colors for parts of the text, these too must be swapped
	       ;; if we are changing color of some part.
	       (new-background-color? (and (eq color-change-case? t)
					   highlight-or-new-background-color?))
	       (real-new-text-color? (and (eq color-change-case? t)
					  new-text-color?))
	       ;; End 1c.
	       
	       ;; Start 1d: Compute the final colors.
	       (final-background-color (or new-background-color?
					   cell-background-color))

	       (final-text-color (or real-new-text-color?
				     cell-text-color)))
	  
	  (when highlighted-after
	    (swap final-background-color final-text-color))
	  ;; End 1d.

	  (let ((existing-text-color-value
		  (map-color-or-metacolor-to-color-value existing-text-color))
		(final-text-color-value
		  (map-color-or-metacolor-to-color-value
		    final-text-color))
		(final-background-color-value
		  (map-color-or-metacolor-to-color-value final-background-color))
		(drawing-against-cell-background?	    ; T if XOR drawing is wrt cell bg color.
		  nil))

	    ;; 2. Draw
	    ;; Draw the background.
	    (cond (unmagnified-width-of-text-to-draw-beyond?
		   (setq existing-text-color final-background-color
			 existing-text-color-value final-background-color-value)
		   (set-current-background-color-value 
		     final-background-color-value)
		   (setq drawing-against-cell-background? t))
		  
		  ((and ; (not (color-eq existing-background-color final-background-color)) ; Note D.
		     (not (and (eq color-change-case? 'selective-redraw)
			       (null highlight-or-new-background-color?))))
		   (let ((background-color-difference
			   (metacolor-difference final-background-color
						 existing-background-color)))

		     (set-current-background-color-value
		       (map-color-or-metacolor-to-color-value existing-background-color))

		     (with-drawing-trace (text #+fmw block)
		       (format t "Drawing background for ~s ~s in ~s~%"
			       block (abbrev-text text) final-background-color))

		     ;; Ensure that the background is always opaque in paint mode,
		     ;; even though the color-difference may be 0, except when
		     ;; the background-color is literally TRANSPARENT.
		     (cond ((and (paint-mode-p)
				 (not (transparent-color-p final-background-color)))
			    (paint-solid-rectangle
			      left-edge-of-cell-in-window
			      top-edge-of-cell-in-window
			      right-edge-of-cell-in-window
			      bottom-edge-of-cell-in-window
			      final-background-color-value))
			   (t
			    (draw-solid-rectangle
			      left-edge-of-cell-in-window
			      top-edge-of-cell-in-window
			      right-edge-of-cell-in-window
			      bottom-edge-of-cell-in-window
			      background-color-difference)))

		     (setq drawing-against-cell-background? t)
		     (set-current-background-color-value final-background-color-value)
		     (setq existing-text-color final-background-color
			   existing-text-color-value
			   (if (xor-mode-p)		    ; In XOR, the old text is still there, inverted.
			       (color-difference existing-text-color-value 
						 background-color-difference)
			       final-background-color-value)))))
	    
	    ;; Draw the text.
	    (unless (or suppress-details?
			(scale-too-small-for-details-p
			  current-image-x-scale current-image-y-scale)

			(text-too-small-to-draw-p
			  text-box-format text-cell-plist
			  current-image-x-scale current-image-y-scale)

			(and (block-is-currently-being-dragged-p block)
			     (not (frame-of-class-p block 'name-box)))

			(and (transparent-color-p final-text-color)
			     (transparent-color-p final-background-color)
			     (paint-mode-p))		    ; Note C

			(if (eq color-change-case? 'selective-redraw)
			    (null new-text-color?)
			    (and (color-eq existing-text-color final-text-color) ; Note A.
				 (not drawing-against-cell-background?)))) ; Note B.

	      (with-nested-draw-area?
		  ((if unmagnified-width-of-text-to-draw-beyond?
		       (maxr
			 (+r left-edge-of-cell-in-window
			     (delta-x-in-window
			       (text-cell-left-margin text-box-format)
			       current-image-x-scale)
			     (delta-x-in-window	; FIX MAGNIFIC. & INDENT!
			       unmagnified-width-of-text-to-draw-beyond?
			       current-image-x-scale))
			 left-edge-of-draw-area)
		       left-edge-of-draw-area)
		   top-edge-of-draw-area
		   right-edge-of-draw-area
		   bottom-edge-of-draw-area
		   block :text-tail)
		
		(setf current-foreground-color-value final-text-color-value)
		(set-current-background-color-value existing-text-color-value)
		
		(with-drawing-trace (text #+fmw block)
		  (format t "Drawing text for ~s ~s in ~s~%"
			  block (abbrev-text text) final-text-color))

		;; The following was being set, rather than bound, previous to
		;; 7/18/94.  This was corrupting the dynamic extent of callers
		;; in some cases.  (e.g. the dynamic-text-cell-format used in
		;; charts and new-tables).  JED
		(let* ((current-text-box-format text-box-format)
		       (current-text-cell-plist text-cell-plist))
		  (draw-text-with-decorations
		    text
		    left-edge-of-cell-in-window  top-edge-of-cell-in-window
		    right-edge-of-cell-in-window bottom-edge-of-cell-in-window))))))))))

;; Note A: We do not allow for underlying blocks which show through transparent
;; text characters over an opaque background color.  Transparent text is
;; treated the same as it was in 3.0, as text in the workspace background
;; color, with one exception: if the text is transparent and the background is
;; transparent, then we don't draw anything.

;; Note B: A bug had been introduced where the text of a button was not drawn
;; when the text-color was not changing.  However, if the background of a
;; text-cell was drawn, then the text must be redrawn whether or not its color
;; has changed, since it was just obliterated by the background.  This bug did
;; not show up in paint mode because do-color-revision saw a change to
;; transparent, and so invalidated a region instead of calling
;; draw-or-changes-color.  -fmw, 9/6/94

;; Note C: This fixes the bug where changing the background-color to transparent,
;; in XOR mode, when the text was transparent already, left us with the text
;; still visible.  When changing the background color in XOR mode, the text
;; has to (always) be redrawn since drawing the rectangle of the new background
;; color just flipped the text color, and it must be restored. -fmw, 11/14/94

;; Note D: This is working in the non-color-change case (where we're supposed
;; to draw everything) only because EXISTING-BACKGROUND-COLOR = BACKGROUND and
;; FINAL-BACKGROUND-COLOR = some real color, like BLACK.



(defun draw-text-with-decorations (text
				    left-edge-of-cell-in-window
				    top-edge-of-cell-in-window
				    right-edge-of-cell-in-window
				    bottom-edge-of-cell-in-window)
  (new-draw-text text
		 left-edge-of-cell-in-window  top-edge-of-cell-in-window
		 right-edge-of-cell-in-window bottom-edge-of-cell-in-window)
  (let ((text-box-post-draw-method? (text-box-post-draw-method current-text-box-format)))
    (when text-box-post-draw-method?
      (funcall-simple-compiled-function  ;; TBD: Change signature for these methods!
	text-box-post-draw-method?
	nil ; text-box?
	nil ; color-change-case?
	nil ; highlight-or-new-background-color?
	nil ; new-text-color?
	current-text-box-format		; text-box-format
	nil ; text-cell-plist
	nil ; unhighlighted-background-color-value
	nil ; cell-background-color-difference
	left-edge-of-cell-in-window 
	top-edge-of-cell-in-window
	right-edge-of-cell-in-window
	bottom-edge-of-cell-in-window))))

;; Consider supporting color changes for the whole table.  For this, color-change-case?
;; might be TABLE and text-cell-to-draw-or-change? would be nil.  This would also
;; require a table-specific-border-color slot in tables, a new-border-color? argument,
;; and substantial revisions to this function.

;; Consider having tables behave more like text boxes in the suppression of text regions
;; and name box subblocks and in the drawing of hairline borders.  (LH) --- I added
;; logic to force a hairline border if there are no non-zero borders, which logic
;; is just like that of the text box draw method.  (MHD 8/8/90)

;; Consider having row and column boundaries be "details", in that they would not be drawn
;; if scale-too-small-for-details-p were true.

;; Consider having a new border color apply also to row and column boundaries.

;; A "bevel join" (mitred corner) should be used where two adjacent segments of width
;; one meet a wider segment, to provide a 3-dimensional effect for the border!

;; Erasing elements of tables ought to happen in the reverse order of drawing them.

;; Consider improving the clipping efficiency for border and boundary drawing, to gain
;; a bit more speed.

;; One would need to bind various special variables if implementing MHD's contrasting
;; proposal for black and white.










;;;; Mouse pointers for Tables


;;; When the mouse is tracking into a table the generate-spot method for the
;;; table is invoked.  This in turn calls a function depending on the table's
;;; format.  These functions are defined via `def-table-format-generate-spot'
;;; these functions happen to be stored on the `table-format-spot-generator'
;;; property of the table format name.

;;; All table formats must have a spot generator defined.

;;; It is a tragic feature that the code that recompiles formats does, or
;;; did, have a the feature of going and setting all the table formats to
;;; having nil for their name.  Such KB's were saved.  For such tables
;;; there isn't much we can do.  Except, we can detect graphs and attempt
;;; to use the format-change? slot.

(def-global-property-name table-format-spot-generator)

(def-class-method generate-spot (table mouse-pointer)
  (let* ((table-format (table-format table))
	 (table-format-name?
	   (name-or-names-for-frame table-format)))
    (unless table-format-name?
      (let ((old-name-or-other-junk? (format-change? table-format)))
	(when (and old-name-or-other-junk?
		   (symbolp old-name-or-other-junk?) ;; Can be an integer.
		   (table-format-spot-generator old-name-or-other-junk?))
	  (dwarn "Mouse tracking forced to use info in format-change? of ~S." table)
	  (setf table-format-name? old-name-or-other-junk?))))
    (with-drawing-trace (spots)
      (format t "Spot for ~s calling ~s"
	      table
	      (if table-format-name?
		  (table-format-spot-generator table-format-name?)
		  (table-format-spot-generator 'table-format-for-graphs))))
    (cond (table-format-name?
	   (funcall (table-format-spot-generator table-format-name?)
		    table mouse-pointer))
	  ((eq (class table) 'graph)    ; Forgive graphs their multitude of sins.
	   (funcall (table-format-spot-generator 'table-format-for-graphs)
		    table mouse-pointer))
	  (t
	   (dwarn "Table format for ~s has a null name." table)
	   (push-last-spot mouse-pointer
			   (make-workspace-background-spot)
			   (get-workspace-if-any table))))))

;; Notice that format-change? has a bizzare protocol



(defmacro def-table-format-spot-generator (table-format-name (table mouse-pointer) &body body)
  (let ((spot-generator (build-ab-symbol "SPOT-GENERATOR-FOR" table-format-name)))
    `(progn
       (setf (table-format-spot-generator ',table-format-name) ',spot-generator)
       (defun-void ,spot-generator (,table ,mouse-pointer)
	 ,@body))))








;;; Table-spot is defined in boxes.lisp

;;; `Fill-out-table-spot' gives the table spot information
;;; about the row/column, cell, and edges of the cell nearest
;;; the mouse.  The cell maybe any flavor, i.e. text or a block.
;;; The tracking ignores cell edges, so even if your on and edge
;;; this will pick one cell or another.

;;; Oviously, we should have some way to denote your on a cell edge.

(defun fill-out-table-spot (table-spot table mouse-pointer)
  (multiple-value-bind (table-cell?  ;; Can be nil??
			 text-box-or-table
			 row-index-of-nearest-cell
			 column-row-index-of-nearest-cell
			 left-edge-of-area top-edge-of-area
			 right-edge-of-area bottom-edge-of-area)
      (pick-cell-from-table
	table
	(image-plane-of-mouse-pointer mouse-pointer)
	(x-of-mouse-pointer mouse-pointer)
	(y-of-mouse-pointer mouse-pointer)
	nil ;; only-if-in-text
	t ;; find-nearest-cell
	)
    (declare (ignore text-box-or-table))
    (setf (row-index-of-spot table-spot) row-index-of-nearest-cell)
    (setf (column-index-of-spot table-spot) column-row-index-of-nearest-cell)
    (setf (table-cell-of-spot? table-spot) table-cell?) ;; ever NIL?
    (setf (left-edge-of-cell-of-table-spot table-spot) left-edge-of-area)
    (setf (top-edge-of-cell-of-table-spot table-spot) top-edge-of-area)
    (setf (right-edge-of-cell-of-table-spot table-spot) right-edge-of-area)
    (setf (bottom-edge-of-cell-of-table-spot table-spot) bottom-edge-of-area)
    (when (cell-is-text-cell-p table-cell?)
      (fill-out-text-spot table-spot table mouse-pointer
			  (text? table-cell?)
			  (text-cell-format table-cell?)
			  (text-cell-plist table-cell?)
			  ))))




;;; An `output-only-table-spot' is a refinement of a table-spot.  The menu choices
;;; hide-table, and transfer-table are the only operations found on this spot. This
;;; is a top level spot, and it is always inclosed by a image-plane-spot.  It's
;;; represented-frame? is the table.

(def-spot output-only-table-spot
  :include table-spot
  :innermost-spot-p t)

(def-spot credits-table-spot
    :include output-only-table-spot)

(defun generate-output-only-table-spot (table mouse-pointer output-only-table-spot)
  (fill-out-table-spot output-only-table-spot table mouse-pointer)
  (push-last-spot mouse-pointer output-only-table-spot table))
  





;;; An `input-table-spot' is a refinement of a table-spot.  It is an abstract
;;; type. It is used for those tables that allow input.  The
;;; {row,cell}-{index,}-of-spot are stored in instances of this cell.  The
;;; frame-represented? is the table frame.  It is neither the frame being
;;; represented, nor is it the frame embedded in the attribute being
;;; represented.

;;; This spot is found only on the interior of the spot stack.

(def-spot input-table-spot
    :slots ()
    :include table-spot
    :innermost-spot-p nil
    :abstract-type nil)

;;; Input table spots are refined to for each of the differing
;;; behaviors found in input tables.  These are all enumerated here
;;; and include:
;;;   attributes-table-format-spot
;;;   short-representation-table-format-spot
;;;   readout-table-format-spot
;;;   attribute-display-table-format-spot
;;;   multiframe-table-format-spot
;;;   graph-table-spot

(def-spot attribute-table-spot
    :include input-table-spot :innermost-spot-p t :abstract-type nil)
(def-spot search-state-table-spot
    :include input-table-spot :innermost-spot-p t :abstract-type nil)
(def-spot short-representation-table-spot
    :include input-table-spot :innermost-spot-p t :abstract-type nil)
(def-spot attribute-display-spot
    :include input-table-spot :innermost-spot-p t :abstract-type nil)
(def-spot readout-table-spot
    :include input-table-spot :innermost-spot-p t :abstract-type nil)
(def-spot multiframe-table-spot
    :include input-table-spot :innermost-spot-p t :abstract-type nil)
(def-spot graph-table-spot
    :include input-table-spot :innermost-spot-p t :abstract-type nil)


;;; `Table-header-spot' are found at the top of the spot stack, with an
;;; input-table-spot enclosing them.  They are generated when the mouse
;;; appears over a table header.

(def-spot table-header-spot
    :enclosing-spot-type input-table-spot
    :innermost-spot-p t
    :abstract-type nil
    :type-of-frame-represented null)

(def-spot table-background-spot
    :enclosing-spot-type input-table-spot
    :innermost-spot-p t
    :abstract-type nil
    :type-of-frame-represented null)


;;; A `item-represented-by-table-spot' is generated when the mouse points
;;; to a entry in a table that represents some attribute of an item.  It is
;;; that item that is bound into the frame-represented? slot of the spot.
;;; The enclosing spot will be a table-header-spot.  This does not appear
;;; at the top of the stack, but is always immediately refined to indicate
;;; what portion of the item is being represented.

(def-spot item-represented-by-table-spot
    :enclosing-spot-type input-table-spot
    :innermost-spot-p nil
    :abstract-type nil
    :type-of-frame-represented item)

;;; The type `attribute-represented-by-table-spot' is generated when as the last
;;; entry on the spot stack when the mouse is over the representation of some
;;; attribute of an item.  The name of that attribute is stored in the
;;; `attribute-represented' slot of this spot.

;;; The frame-represented? slot is nil.

(def-spot attribute-represented-by-table-spot
    :slots
       (slot-name-of-spot
	 defining-class-of-spot
	 slot-component-name-of-spot?
	 slot-component-indicator-of-spot?
	 virtual-attribute-of-spot?)
    :enclosing-spot-type item-represented-by-table-spot
    :innermost-spot-p nil
    :abstract-type t
    :type-of-frame-represented null)

(def-spot attribute-value-represented-by-table-spot
    :include attribute-represented-by-table-spot
    :enclosing-spot-type spot
    :innermost-spot-p t
    :abstract-type nil)

(def-spot attribute-name-represented-by-table-spot
    :include attribute-represented-by-table-spot
    :enclosing-spot-type spot
    :innermost-spot-p t
    :abstract-type nil)



;;; `Generate-spot-for-input-table' will push from 3 to 5 of spots into the
;;; mouse-pointer's spot stack to indicate what the mouse is pointing.

;;; First we always push at these two spots on
;;;    input-table-spot -- to indicate we are over an input table.
;;;    item-represented-by-table-spot  -- to indicate what this represents.

;;; We then generate one of these patterns.
;;;    table-header-spot
;;;    non-item-attribute-represented-by-table-spot attribute-name-spot
;;;    non-item-attribute-represented-by-table-spot attribute-value-spot
;;;    item-attribute-represented-by-table-spot attribute-name-spot
;;;    item-attribute-represented-by-table-spot attribute-value-spot

;;; It is possible that further tracking maybe required if the mouse, in one
;;; case only.  If the mouse is point at an attribute-value-spot, and that
;;; attribute is editable, we may need to track to discover where in the text
;;; the mouse is pointing.

;;; This is called for those tables who's format indicates they are input
;;; tables.  At that point the a workspace-spot is the enclosing spot.

(defun generate-spot-for-input-table (table mouse-pointer input-table-spot)
  ;; Do the pure table info.
  (generate-spot-for-pure-input-table table mouse-pointer input-table-spot)

  ;; Now borrow into the table generating spots for the cell et. al.
  (let ((table-cell? (table-cell-of-spot? input-table-spot))
	(row-index-of-nearest-cell (row-index-of-spot input-table-spot)))
    ;; Track into the components of the table

    (cond
      ;; A block cell
      ((cell-is-block-p table-cell?)
       ;; All of the blocks found in tables the same input behavior, except
       ;; graphs.  So for the general case we don't have to bother to record
       ;; actual block and we just generate a table background.  For graphs
       ;; we want a different spot because graphs are much more like a display
       ;; than a table.
       (cond ((frame-of-class-p table 'graph)
	      (push-last-spot mouse-pointer (make-graph-table-spot) nil));; Note A
	     (t
	      (push-last-spot mouse-pointer (make-table-background-spot) nil))))
      ;; A text cell.
      (t
       (let* ((text-cell? table-cell?)
	      (attribute-table-like-p (attribute-table-like-p table))
	      ;; (text-cell-format (text-cell-format text-cell?))
	      spot-is-on-value-cell?
	      frame? slot-name-or-index? defining-class?
	      slot-component-name? slot-component-indicator? virtual-attribute?)

	 ;; Cleverly hidden in the (value) text cell is
	 ;; a "backpointer" to the frame and slot (or
	 ;; component thereof, or position index, in
	 ;; case of a tabular function) represented,
	 ;; i.e., "the attribute".
	 (multiple-value-setq
	     (frame? slot-name-or-index? defining-class?
		     slot-component-name? slot-component-indicator? virtual-attribute?)
	   (if text-cell?		 
	       (get-slot-represented-by-text-cell-if-any text-cell?)))
	 (setq spot-is-on-value-cell? frame?)
	 (unless frame?
	   (let ((real-attribute-value-cell?
		   (if attribute-table-like-p;; See attribute-table-like-p
		       (second (assq text-cell? (table-rows table))))))
	     (when real-attribute-value-cell?
	       (multiple-value-setq
		   (frame? slot-name-or-index? defining-class?
			   slot-component-name? slot-component-indicator? virtual-attribute?)
		 (get-slot-represented-by-text-cell-if-any
		   real-attribute-value-cell?)))))
	 
	 (when frame?
	   (push-more-detailed-spot
	     mouse-pointer (make-item-represented-by-table-spot) frame?))

	 ;; What kind of attribute display is this?
	 ;; attribute-table-like-p includes both short representations,
	 ;; and attribute display tables.  But, neither of these have table
	 ;; headers.  Therefore, the condition on generating a table header
	 ;; is that we are really in row 0 of an attribute-table.

	 (cond ((and (=f 0 row-index-of-nearest-cell) ; Clicked on first row.
		     (attribute-table-with-header-p table))
		;; This used to supply NIL for the spot's table.  I'm not sure
		;; what the intended logic is, but it seems reasonable that a
		;; table-header-spot will contain a pointer to the table of
		;; which it is the header.  In any case, this makes
		;; pop-down-attribute-table work again for any type of table,
		;; after I changed the attribute-table magic argument to also
		;; search table-header spots.  Some rethought ought to happen
		;; here. -fmw, 2/15/94
		(push-last-spot mouse-pointer (make-table-header-spot) table))

	       ;; We are looking at background
	       ((or (null frame?)
		    (fixnump slot-name-or-index?)) ; tabular-function values table
		(push-last-spot mouse-pointer (make-table-background-spot) nil))

	       ;; We are looking at some an attribute of some frame
	       ;; An attribute ... name or value?
	       (t
		(let ((spot
			(if spot-is-on-value-cell?
			    (make-attribute-value-represented-by-table-spot)
			    (make-attribute-name-represented-by-table-spot)))
		      (slot-description?
			(unless virtual-attribute?
			  (get-slot-description-of-frame ; NIL for a deleted slot!
			    slot-name-or-index? frame?))))
		  (setf (slot-name-of-spot spot) slot-name-or-index?)
		  (setf (defining-class-of-spot spot)
			(or defining-class?
			    (and slot-description?
				 (defining-class slot-description?))))
		  (setf (slot-component-name-of-spot? spot)
			slot-component-name?)
		  (setf (slot-component-indicator-of-spot? spot)
			slot-component-indicator?)
		  (setf (virtual-attribute-of-spot? spot)
			virtual-attribute?)
		  (push-last-spot mouse-pointer spot nil)))))))))

;; Note A: This seems wrong.  This spot is actually for block, and isn't a
;; table anymore, is it?  Meanwhile this isn't the only call on
;; make-graph-table-spot -- ben 3/7/95

;; I don't think graphs use this function any longer. -fmw, 3/17/95



(defun generate-spot-for-pure-input-table (table mouse-pointer input-table-spot)
  (fill-out-table-spot input-table-spot table mouse-pointer)
  (push-more-detailed-spot mouse-pointer input-table-spot table))







;;; The `default-table-format' is automatically generated when the table format
;;; class was defined.  It is apparently only used to format the network status
;;; table, but since it appears in the UI it must have a spot generator.  The
;;; `spot-generator for default-table-format' creates a output-only-table-spot.

(def-table-format-spot-generator default-table-format (table mouse-pointer)
  (multiple-value-bind (table-cell?  ;; Can be nil??
			 text-box-or-table
			 row-index-of-nearest-cell
			 column-row-index-of-nearest-cell
			 left-edge-of-area top-edge-of-area
			 right-edge-of-area bottom-edge-of-area)
      (pick-cell-from-table
	table
	(image-plane-of-mouse-pointer mouse-pointer)
	(x-of-mouse-pointer mouse-pointer)
	(y-of-mouse-pointer mouse-pointer)
	nil ;; only-if-in-text
	t ;; find-nearest-cell
	)
    (declare (ignore text-box-or-table table-cell? column-row-index-of-nearest-cell
		     left-edge-of-area top-edge-of-area
		     right-edge-of-area bottom-edge-of-area))
    ;; Is this test correct?  See title-bar-of-attribute-table-p.
    (cond ((and (=f 0 row-index-of-nearest-cell)
		(=f 1 (loop for element in (first (table-rows table)) ; First row has only a single cell.
			    count element)))
	   (push-last-spot mouse-pointer (make-table-header-spot) table))
	  (t
	   (generate-output-only-table-spot
	     table
	     mouse-pointer
	     (make-output-only-table-spot))))))

;; Shouldn't the header have a table above it? - ben 3/7/95






;;;; Timing Parameters



;;; ;;; The def-system-frame for timing-parameters has been moved here from cycles
;;; ;;; to provide accessors used in service-workstations below.  -jra 2/18/88
;;; -- UPDATE: moved here from WORKSTATIONS to provide accessors used in
;;; table-update-interval? below. (MHD 2/3/00)


(def-system-frame timing-parameters tables
  (scheduler-mode real-time (vector-slot) (system) (save)
		  (type timing-scheduler-mode))
  (minimum-scheduling-interval
    1000 (lookup-slot) (system) (save) (type minimum-scheduling-interval?))
  (milliseconds-to-sleep-when-idle nil (vector-slot) (system) (save)
				   (type millisecond-sleep-interval))
  (meter-lag-time 10 (vector-slot) (system) (save)
		  (type interval))
  (interface-mode time-slice-dependant
		  (vector-slot) (system) (save) (type interface-mode))
  (clock-adjustment-in-minutes 0 (vector-slot) (system) (save)
			      (type integer))

  ;; This slot is misnamed, and is part of the kb products authorizing system.
  ;; See ML if there are questions.
  (clock-fraction-adjustment nil system (vector-slot))

  ;; jh, 6/11/91.  Added these two slots for foreign function server.  See
  ;; FOREIGN.
  ;; jh, 2/21/95.  Removed foreign-function-wait-strategy.
  (foreign-function-timeout-interval 30 
    (vector-slot) (system) (save)
    (type default-foreign-function-timeout-interval))

  ;; jh, 9/6/91.  Added this slot, per the release notes, and made the
  ;; corresponding changes in FOREIGN.
  (reconnect-to-foreign-image-after-timeout? 
    nil vector-slot system (type yes-or-no))

  ;; cpm, 11/6/91.  Changed from a non-saved, lookup-slot to the following.
  (default-uninterrupted-procedure-execution-limit?
    30 (vector-slot) (system) (save) (type execution-interval?))

  (attribute-display-update-interval	; nil ("continuous") or an 
    nil (vector-slot) (system) (save)	;   interval (managed float)
    (type attribute-refresh-positive-quantity-interval)))

(add-grammar-rules
 '((attribute-refresh-positive-quantity-interval (float 'seconds) 1)
   (attribute-refresh-positive-quantity-interval 'continuous)))

(def-slot-value-writer attribute-refresh-positive-quantity-interval (value)
  (with-temporary-gensym-float-creation
   arpqi
   (cond
    ((managed-float-p value)
     (tformat "~f seconds" (managed-float-value value)))
    ((gensym-float-p value)
     (tformat "~f seconds" value))
    ((fixnump value)
     (tformat "~f seconds" (coerce-to-gensym-float value)))
    ((null value)
     (tformat "continuous"))
    #+development ; unknown thing if this happens!
    (t (tformat "??? ~s ???" value)))))

(define-category-evaluator-interface (attribute-refresh-positive-quantity-interval
				       :access read-write)
    (or (member continuous) float)
  ((set-form (evaluation-value))
   (case evaluation-value
     (continuous evaluation-value)
     (t       
      (evaluation-quantity-to-phrase-quantity evaluation-value))))
  ((get-form (slot-value))
   (case slot-value
     ((nil) 'continuous)
     (t (if (gensym-float-p slot-value)
	    (make-evaluation-float slot-value)
	    (copy-managed-float-into-evaluation-float slot-value))))))

(def-slot-value-compiler attribute-refresh-positive-quantity-interval (parse-result)
  (cond
   ((eq parse-result 'continuous)
    nil)
   ((with-temporary-gensym-float-creation
     arpqi
     (not (<=e 0.0 (phrase-float-value parse-result) .5)))
    (values
     bad-phrase
     (copy-text-string "The interval must be between 0.0 and 0.5 seconds")))
   (t parse-result)))


(def-absent-slot-putter foreign-function-wait-strategy
    (timing-parameters new-wait-strategy)
  (declare (ignore new-wait-strategy))
  nil)

;; copied from the putter for clock-adjustment-in-minutes. -ncc, 8 Jan 1997 

(def-slot-putter milliseconds-to-sleep-when-idle (timing-parameters-frame new-value)
  (setf (milliseconds-to-sleep-when-idle timing-parameters-frame) new-value)
  new-value)


;;;  The following function versions of timing-parameters slot accessors are
;;;  needed in SCHEDULE and CLOCKS.

(defun-simple scheduler-mode-function (timing-parameters-local)
  (scheduler-mode timing-parameters-local))

(defun-simple minimum-scheduling-interval-function (timing-parameters-local)
  (minimum-scheduling-interval timing-parameters-local))

(define-slot-alias uninterrupted-procedure-execution-limit
    default-uninterrupted-procedure-execution-limit?
  timing-parameters)




;;; The float-meter-lag-time-in-fixnum-time-units? slot of timing-parameters
;;; system table frames has been removed.  It was inappropriately propagating
;;; fixnum-time-units-per-second values through knowledge bases.  Its
;;; functionality has since been replaced.  These slot values will be present in
;;; 1.1 Beta and earlier knowledge bases, though not in the 1.1 official release
;;; KBs.  -jra 9/13/88


(def-absent-slot-putter float-meter-lag-time-in-fixnum-time-units?
			(timing-parameters value)
  (declare (ignore value))
  timing-parameters				; special (so don't ignore)
  nil)




;;; The slot putter for clock-adjustment-in-minutes needs to put its value into
;;; global-daylight-saving-time-adjustment if the given instance of
;;; timing-parameters is the currently installed system table.

(def-slot-putter clock-adjustment-in-minutes (timing-parameters-frame new-value)
  (setf (clock-adjustment-in-minutes timing-parameters-frame) new-value)
  (when (eq timing-parameters timing-parameters-frame)
    (setq global-daylight-saving-time-adjustment
	  new-value)
    (update-g2-time-to-tick-after-scheduling-change))
  new-value)




;;; The slot putter for `minimum-scheduling-interval' puts the value into the
;;; frame and then clears the cache that determines how long until the next
;;; clock tick.

(def-slot-putter minimum-scheduling-interval (timing-parameters-frame new-value)
  (setf (minimum-scheduling-interval timing-parameters-frame) new-value)
  (update-g2-time-to-tick-to-asap (get-fixnum-time))
  new-value)






;;;; Scheduled Table Representation Updates 1



;;; This section is new in in 5.1r5 and 6.0.  In these versions we introduced
;;; the concept of `scheduled attribute display updates'.  The user view of this
;;; is through the timing-parameters system table.  It now contains the
;;; attribute `attribute-display-update-interval', which can be, internally, nil
;;; or a float (gensym or managed) between 0.0 and .5, externally the symbol
;;; CONTINUOUS or an expression of the form <float> second(s), where <float> is
;;; between 0.0 and 0.5.
;;;
;;; Apart from various exceptional cases, when this attribute is non-nil in the
;;; installed system table, the system defers updates to cells in tables that
;;; represent slots in frames (blocks) until the specified interval of time has
;;; elapsed.  In addition, when called back to do the updates, this facility
;;; only does as many as fit into its time slice; if work remains, it is again
;;; deferred for the specified interval of time.  When the table is finally
;;; updated, it is always updated using the slot's value.  Since this may have
;;; changed a great many times in the interval between the first change that
;;; resulted in the scheduling and when the table actually gets its update,
;;; significant work may have been avoided.  This greatly lowers the overhead of
;;; changing a slot that is represented in one or more table cells, especially
;;; where this is done at a fast rate.
;;;
;;; The exceptional cases in which scheduled updates do not occur include:
;;;
;;;   (1) the expression-to-display slot in readout tables  (scheduling of
;;;         updates are already under user control)
;;;   (2) clearing a KB;
;;;   (3) loading a KB;
;;;   (4) saving a KB;
;;;   (5) when G2 is being reset;
;;;   (6) whenever there is no "current KB";
;;;   (7) when there is no installed timing-parameters

;;; Note: part 1 of this facility is here, and part 2 is further below, in order
;;; to overcome some macro ordering problems.

;;; G2 has one main bottleneck through which most slot value changes go:
;;; update-all-representations-of-slot.  This has been changed to possibly
;;; schedule updates to table cells representing slot values.


;;; The variable `safe-to-access-attribute-display-update-interval-p' is bound
;;; to nil globally and to T inside of a normal G2 KB where, unless
;;; in-clear-kb-p is true, it is safe to access the
;;; attribute-display-update-interval slot of timing-parameters (which is known
;;; to be bound to an installed, valid instance of timing parameters).

;;; The macro `suppressing-table-refresh-interval' may be used around code that
;;; may directly or indirectly update text cells for slots in tables to ensure
;;; that such updates are reflected immediately regardless of any update
;;; scheduling in effect.

(progn
(def-kb-specific-variable safe-to-access-attribute-display-update-interval-p
    tables t)
(setq safe-to-access-attribute-display-update-interval-p nil) ; set to nil globally
)



;;; The macro `can-use-table-refresh-interval-p' is used to tell whether the
;;; macro `table-update-interval?', a macro that returns either nil or a gensym
;;; float representing the update interval, can be used and whether it has a
;;; non-nil value.

(defmacro can-use-table-refresh-interval-p ()
  `(and safe-to-access-attribute-display-update-interval-p
	(not in-clear-kb-p)
	(and (not reading-kb-p)
	     (not saving-kb-p) (not current-saving-context?) ; why both?!
	     timing-parameters		; known bound, but potentially nil
	     (attribute-display-update-interval timing-parameters))))

(defun-substitution-macro table-update-interval? ()
  (let ((v (attribute-display-update-interval timing-parameters)))
    (if (and v (managed-float-p v))
	(managed-float-value v)
	v)))

(defmacro suppressing-table-refresh-interval (&body body)
  `(let ((safe-to-access-attribute-display-update-interval-p nil))
     . ,body))





;;;; Shifting, Reclaiming, and Updating Tables



(def-class-method shift (table delta-x delta-y)
  (unless (=w delta-x 0)
     (loop for l on (column-edges table)
	   do (incfw (car l) delta-x))
     (loop for row in (table-rows table)
	   do (loop for cell? in row
		    when (and cell? (not (cell-is-block-p cell?)))
		      do (incfw (minimum-right-edge-for-cell cell?) delta-x))))
  (unless (=w delta-y 0)
     (loop for l on (row-edges table)
	   do (incfw (car l) delta-y)))
  (funcall-superior-method table delta-x delta-y))




;(defun shift-table-beyond-nth-column (table column-index delta-x)
;  (incfw (right-edge-of-block table) delta-x)
;  (loop for l on (nthcdr column-index (column-edges table))
;	do (incfw (car l) delta-x))
;  (loop for row in (table-rows table)
;	do (loop for cell? in (nthcdr (+f column-index 1) row)
;		 when (and cell? (not (cell-is-block-p cell?)))
;		      do (incfw (minimum-right-edge-for-cell cell?) delta-x)))
;  (loop with dividing-line
;	  = (if (=f column-index 0)
;		(left-edge-of-block table)
;		(nth (-f column-index 1) (column-edges table)))
;	as subblock being each subblock of table
;	when (>=w (left-edge-of-block subblock) dividing-line)
;	  do (funcall-method 'shift subblock delta-x 0)))

;; This is used only in the incomplete function modify-cell-in-table, and needs testing.



(def-slot-value-reclaimer table-rows (table-rows table)
  (loop for row in (table-rows table)
	do (loop for cell? in row
		 when (and cell? (not (cell-is-block-p cell?)))
		   do (let ((frame?
			      (get-slot-represented-by-text-cell-if-any cell?)))
			(if frame?
			    (remove-from-frame-representations-if-present
			      table frame?)))))
  (reclaim-slot-value table-rows))

;; Note that remove-from-frame-representations-if-present is invoked once for each text
;; cell that represents a slot of a frame.  Many such invocations may be redundant.



;;; `Remove-representations-of-slot-component-group' deletes all tables
;;; representing the designated slot component group.  If the slot in frame
;;; designated by slot-name and defining-class? is a multiple compound slot,
;;; slot-component-indicator? must be specified.  In either case it removes all
;;; tables representing the slot component group, even if the table represents
;;; other slots or slot components from this or other frames.

(defun remove-representations-of-slot-component-group
    (frame slot-name defining-class? slot-component-indicator?)
  (loop while
	(loop for representation in (frame-representations frame)
	      thereis
	      (and
		(frame-of-class-p representation 'table)
		(loop with table = representation
		      for row in (table-rows table)
		      when (loop for cell? in row
				 thereis
				 (and cell?
				      (not (cell-is-block-p cell?))
				      (multiple-value-bind
					  (f sn dc scn sci)
					  (get-slot-represented-by-text-cell-if-any
					    cell?)
					(and scn ; it must be a sub table - not master slot
					     (eq frame f)
					     (eq slot-name sn)
					     (eq defining-class? dc)
					     (eq slot-component-indicator? sci)))))
			do (setf (frame-representations frame)
				 (delete-slot-value-element
				   table (frame-representations frame)))
			   (delete-frame table)
			   (return t))))))



;;; `Detach-table-from-frames-it-represents' ...

(defun detach-table-from-frames-it-represents (table)
  (loop for row in (table-rows table)
	do (loop for cell? in row
		 as frame?
		    = (if (and cell? (not (cell-is-block-p cell?)))
			  (get-slot-represented-by-text-cell-if-any cell?))
		 when frame?
		   do (remove-from-frame-representations-if-present table frame?)
		      (change-text-cell-property cell? frame? nil))))

;; Note that remove-from-frame-representations-if-present is invoked once for each text
;; cell that represents a slot of a frame.  Many such invocations may be redundant.







;;; `Update-representations-in-tables' updates all representations in tables
;;; (except for explanation tables) of the slot designated by slot-name and
;;; defining-class? in frame.
;;;
;;; It does the update via `update-representations-in-table', which updates all
;;; of the representations of the slot (or slot component) value in a single
;;; table representing frame.
;;;
;;; This is to be used only by change-slot-value.  See also change-slot-value
;;; and update-text-cell.

;;; When the special variable `suppress-updating-of-self-representations?' is
;;; true, update-representations-in-tables does not update a table that is EQ to
;;; frame.  This feature is used by the text stripping facility when it has to
;;; strip expression or label text from the tables of graphs and readouts but
;;; does not want to do so to the graphs and readout tables themselves.

(defvar suppress-updating-of-self-representations? nil)	; added. (MHD 8/24/90)




;;; `Write-compound-slots-parseably?' controls the writing of value of compound
;;; slots.  If true, they should be written so that they could be parsed back
;;; in.  Since they are usually overly verbose, they are typically written in an
;;; abbreviated form.

(defvar write-compound-slots-parseably? t)



(def-substitution-macro table-representation-should-be-updated? (frame table)
  (not
   (or (and suppress-updating-of-self-representations?
	    (eq table frame))
       ;; T => table is presumably a graph or readout
       ;;   table being text-stripped
       (frame-of-class-p table 'explanation-table))))

(def-substitution-macro representation-should-be-updated? (frame representation)
  (cond
    ((frame-of-class-p representation 'table)
     (table-representation-should-be-updated? frame representation))
    (t t)))

(defmacro fast-frame-representations (block)
  (if (vector-slot-index?
	(get-slot-description
	  'frame-representations
	  (slot-descriptions (class-description 'block))))
      `(frame-representations ,block)
      `(look-up-slot-value-else-compute-default ,block 'frame-representations nil)))

;; This need not know whether frame-representations is a vector slot or a lookup
;; slot, just that it's a system-defined slot on block. (MHD 1/10/01)


(defun-simple update-all-representations-of-slot
    (frame slot-description slot-component-name? slot-component-indicator?)
  (when (block-p frame)
    (update-property-grid-all frame)
    (let* ((representations (fast-frame-representations frame)))
      (when representations
	(update-all-representations-of-slot-1
	 frame representations
	 slot-description
	 slot-component-name? slot-component-indicator?)))
    ;; GENSYMCID-1406: Item deleted event
    ;; ignore to fire callbacks for attributes subscription while frame is being deleted
    (when (not (frame-being-deleted-p frame))
      (update-subscriptions-from-slot-change-with-description frame slot-description))))

;; I'd ultimately like the above function to be macro that's called in
;; change-slot-description-value inline, so it can avoid any function calling
;; overhead in the common case of a frame with no representations. However, such
;; a change requires moving this to FRAMES5, which comes earlier.  (MHD 5/5/00)
    


;;; `Update-representations-in-table-with-slot-description' ... called to update
;;; a table showing a slot only, not a virtual attribute (c.f.,
;;; update-representations-in-table).  In addition to updating the cell for the
;;; the slot, it updates the workspace title bar, if appropriate, if the table
;;; is shown on a workspace with a title bar showing what appears to be the
;;; "table header".

(defun-substitution-macro update-representations-in-table-with-slot-description
    (table frame slot-description
	   slot-component-name? slot-component-indicator?)
  (when (slot-description-for-namelike-slot-p slot-description)
    (let ((workspace-of-classic-attribute-table?
	    (if (classic-attribute-table-p table)
		(get-workspace-if-any table))))
      (when workspace-of-classic-attribute-table?
	(setf (title-bar-caption-text workspace-of-classic-attribute-table?)
	      (prog1 
		  (convert-text-string-to-text (make-class-header-string frame))
		(reclaim-slot-value
		  (title-bar-caption-text workspace-of-classic-attribute-table?))))
	(refresh-title-bar workspace-of-classic-attribute-table?))))
  (let ((slot-name (pretty-slot-name slot-description)))
    (update-representations-in-table
      table frame
      slot-name 
      (if (not (eq slot-name 'class))
	  (class-qualifier-of-slot-description frame slot-description))
      slot-component-name? slot-component-indicator?)))


(def-system-variable expressions-to-display-slot-description tables
  (:initialize get-slot-description-from-class readout-table expressions-to-display))

(defun-simple update-all-representations-of-slot-1
    (frame representations slot-description
	   slot-component-name? slot-component-indicator?)
    (loop with scheduled-for-refresh-p = nil
	  with can-use-table-refresh-interval-p
	    = (and (can-use-table-refresh-interval-p)
		   ;; readout table displays should not be delayed
		   (not (eq slot-description
			    expressions-to-display-slot-description)))
	  for representation in representations
	  do (frame-class-case representation
	       (table
		 (cond
		   ((not (table-representation-should-be-updated? frame representation)))	      
		   (scheduled-for-refresh-p)		       
		   (can-use-table-refresh-interval-p
		    (setq scheduled-for-refresh-p t)
		    (add-to-schedule-of-table-updates
		      frame slot-description
		      slot-component-name? slot-component-indicator?))
		   (t
		    (update-representations-in-table-with-slot-description
		      representation frame slot-description
		      slot-component-name? slot-component-indicator?)
		   )
)))))

(defmacro exported-cell-text (cell)
  `(when (cell-is-text-cell-p ,cell)
     (convert-text-to-text-string (text? ,cell))))

(defun update-representations-in-table
    (table frame slot-name defining-class?
	   slot-component-name? slot-component-indicator?
	   &optional virtual-attribute?)  
  (loop with text-cell? = nil
	with remaining-rows-index? = nil
	with remaining-cells-index? = nil
	do
    (when (multiple-value-setq
	      (text-cell? remaining-rows-index? remaining-cells-index?)
	    (get-text-cell-representing-slot-if-any
	      table frame slot-name defining-class?
	      slot-component-name? slot-component-indicator?
	      remaining-rows-index? remaining-cells-index?
	      virtual-attribute?))
      (update-text-cell-for-slot-in-table table text-cell?)
      (when (and g2-has-v5-mode-windows-p
		 (frame-of-class-p table 'item))
	(send-ws-representations-item-change-macro
	  table
	  (allocate-evaluation-structure-inline
	    'attribute-name 'table-rows ;'table-cells for ff-tables
	    'row-index remaining-rows-index?
	    'column-index (-f remaining-cells-index? 1)
	    'cell-attribute-name
	    'cell-display-text
	    'new-value (exported-cell-text text-cell?)))))
	while remaining-rows-index?))

;see update-representations and do-frames-this-represents
(defun update-all-representations-in-table (table frame)
  (loop for row in (table-rows table) do
    (loop for cell? in row
	  when (and cell?
		    (not (cell-is-block-p cell?)))
	    do (multiple-value-bind (f sn dc scn sci va) ; Note: some or all can be nil
		   (get-slot-represented-by-text-cell-if-any cell?)
		 (when (and (eq frame f) sn)
		   (update-representations-in-table
		     table frame sn dc scn sci va)))
	       (when (getf (text-cell-plist cell?) 'virtual-attribute-table-header)
		 (let ((new-text (get-text-for-virtual-attribute-table-header frame)))
		   (update-text-cell table cell? new-text nil nil))))))

;; This no longer automatically updates the CLASS slot whenever slot-name is
;; NAME-OR-NAMES-FOR-FRAME.  It was both a kludge of marginal benefit.  (MHD
;; 1/28/94)

;; Optimized ... [part of comment obsolete (MHD 1/28/94)] ... setq'ing
;; leave-text-representation-as-a-single-line?  before use, instead of binding
;; around use.  (The setq'ing had been suggested in an adjacent comment
;; previously.) (MHD 6/1/92)

;; Note that graphs and readouts are tables that point back to themselves through
;; their frame-representation slot, and that these are currently the only such
;; items in the user's model of G2.  (MHD 8/24/90)

;; New logic added for explanation-table case.  Review later.  Also see and review
;; explanation tables in TABLES. (MHD 1/24/90)





;;; `Update-text-cell-for-slot-in-table' rewrites the text of text cell based on
;;; the value of the slot, or slot component, it represents.  If it does not
;;; represent any slot, it does nothing.
;;;
;;; Use-stack-of-slot-value-changes? is passed through to update-text-cell,
;;; where it is documented.

;;; This function initially sets leave-text-representation-as-a-single-line? to
;;; nil.  Then it calls make-text-representation-for-slot-value-itself with
;;; the value for the slot, or a component thereof, and during this call, it
;;; might be set back to true.  Finally, the value of that variable influences
;;; the formatting of the cell in the obvious way.

;;; This now [1/10/02] handles cell-specific format overrides, using the
;;; display-format text cell plist indicator . The values it can handle are:
;;; FREE-TEXT, INTERVAL, TIME-STAMP, and DEFAULT.  Note that DD.DDD type formats
;;; (for floats) not yet handled. DEFAULT or any other format, or inapplicable
;;; cases, falls through and gets handled as before/default.

(defun update-text-cell-for-slot-in-table
    (table text-cell &optional use-stack-of-slot-value-changes?)
  (setq leave-text-representation-as-a-single-line? nil)
  (multiple-value-bind
      (frame? slot-name defining-class?
	      slot-component-name? slot-component-indicator?
	      virtual-attribute? exported-format?)
      (get-slot-represented-by-text-cell-if-any text-cell)
    (when frame?
      (let ((unformatted-new-text
	      (let* ((slot-description
		       (when (and (null slot-component-name?)
				  (not virtual-attribute?))
			 (if (eq slot-name 'class)				    
			     pseudo-class-slot-description
			     (get-slot-description-of-frame
			       slot-name frame? defining-class?))))
		     (virtual-attribute
		       (when virtual-attribute?
			 (virtual-attribute slot-name)))
		     (features
		       (if (null slot-component-name?)
			   (if slot-description
			       (slot-features slot-description))
			   (get-slot-component-features
			     slot-name defining-class?
			     slot-component-name?)))
		     (type-feature
		       (feature-assq 'type features))
		     (text-summarized?
		       (getfq (text-cell-plist text-cell)
			      'text-summarized?))
		     (display-format?
		       (getfq (text-cell-plist text-cell) 'display-format))
		     (current-ddd.dddd-format? ; special var.
		      (if (and display-format?
			       (consp display-format?))
			  display-format?
			  (let ((format-override?
				 (feature-assq 'format-override features)))
			    (if (and format-override?
				     (eq (second format-override?) 'ddd.dddd-format))
				(third format-override?)))))
		     (value
		       (if (null slot-component-name?)
			   (if (eq slot-name 'class)
			       (class frame?)
			       (if slot-description
				   (if exported-format?
				       (get-attribute-description-evaluation-value
					 frame? slot-description)
				       (get-slot-description-value
					 frame? slot-description))
				   (get-virtual-attribute
				     frame?
				     virtual-attribute)))
			   (get-slot-component-value
			     frame? slot-name defining-class?
			     slot-component-name?
			     slot-component-indicator?))))
		(declare		; nec. due to module ordering issue
		  (special current-ddd.dddd-format?))
		(cond
		  ((or virtual-attribute exported-format?)
		   (if text-summarized?
		       (let ((write-compound-slots-parseably? nil))
			 (text-for-item-or-value value)) ; reclaims value
		       (text-for-item-or-value value))) ; reclaims value
		  (text-summarized?
		   (let ((write-compound-slots-parseably? nil)
			 ;; controls other/all slots here some day
			 )
		     (make-text-representation-for-slot-value-itself
		       frame? value type-feature)))
		  ;; cell-specific format overrides: handle or fall through:
		  (display-format?
		   (make-text-representation-for-slot-value-per-display-format
		     frame? value type-feature display-format?))
		  (t
		   (make-text-representation-for-slot-value-itself
		     frame? value type-feature))))))
	(update-text-cell
	  table text-cell
	  unformatted-new-text
	  
	  ;; may be setq'd within make-text-representation-for-slot-value-itself:
	  leave-text-representation-as-a-single-line?
	  
	  use-stack-of-slot-value-changes?)))))


;;; Make-text-representation-for-slot-value-per-display-format ...
;;; Make-text-representation-for-slot-value-per-display-format ...

(defun make-text-representation-for-slot-value-per-display-format
    (frame value type-feature display-format)
  (convert-text-string-to-text
    (make-text-string-representation-for-slot-value-per-display-format
      frame value type-feature display-format)))


(defun make-text-string-representation-for-slot-value-per-display-format
    (frame value type-feature display-format)
  (let ((value-after-constant-conversion
	  (if (slot-constantp value)
	      (get-slot-value-number-or-string-from-slot-constant value)
	      value)))
    (cond
      ((and (eq display-format 'free-text)
	    (text-string-p value-after-constant-conversion))
       (copy-wide-string value-after-constant-conversion))
      ((and (or (eq display-format 'interval)
		(eq display-format 'time-stamp))
	    (slot-value-number-p value-after-constant-conversion))
       (with-temporary-gensym-float-creation
	   update-text-cell-for-slot-in-table
	 (twith-output-to-text-string
	   (twrite-number-per-format
	     (slot-value-number-value value-after-constant-conversion)
	     (if (eq display-format 'interval)
		 ;; translation necessary:
		 ;;   interval => seconds
		 'seconds
		 display-format)))))
      (t 
       (make-text-string-representation-for-slot-value-itself
	 frame value type-feature)))))





;;; `Update-cell-in-table' ... Plist-changes?, if specified, should be a slot
;;; value list of alternating text-cell-plist indicators and values, the conses
;;; of which, to all levels, will be recycled or incorporated.  Note that it
;;; should only be specified if cell is a text cell.  At present, changes to
;;; the text cell plist that would result in a different graphic appearance
;;; (i.e. color changes) will not be automatically reflected by this function
;;; and therefore should not be included in plist-changes? if table is currently
;;; drawn.

#+development
(defun update-cell-in-table
       (table row-index column-index unformatted-new-text leave-as-a-single-line?
	&optional plist-changes?)
  (let ((cell (get-table-cell table row-index column-index)))
    (update-text-cell
      table cell
      unformatted-new-text leave-as-a-single-line? nil)
    (if plist-changes?
	(loop for (indicator value) on plist-changes? by #'cddr
	      do (change-text-cell-property
		   cell indicator value)
	      finally (reclaim-slot-value-tree plist-changes?)))))

;; Later, change update-text-cell to take plist-changes? and to handle color
;; changes appropriately!

;; Later, incorporate the conses of plist-changes? directly into the text cell
;; plist where possible rather than just recycling them at the end!

;; Optional arg plist-changes? added 1/12/90.  Consider making it non-optional.
;; (MHD 1/12/90)




;;; The function `perform-minimal-text-cell-update' uses the new
;;; invalidate-region-of-block function for faster text-cell updates in
;;; paint-mode.

(defun perform-minimal-text-cell-update
    (table text-cell formatted-new-text
	   left-edge-of-cell top-edge-of-cell
	   right-edge-of-cell bottom-edge-of-cell
	   unmagnified-width-of-text-to-draw-beyond?)
  (let* ((workspace? (get-workspace-if-any-macro table))
	 (paint-mode-style?
	   (and (paint-mode-p)
		(not (render-frame-in-xor-overlay-p table)))))

    ;; If XOR, erase the old text.
    (when (and workspace?
 	       (not paint-mode-style?))
      (update-images-of-text-cell
	t table text-cell
	unmagnified-width-of-text-to-draw-beyond?
	left-edge-of-cell top-edge-of-cell
	right-edge-of-cell bottom-edge-of-cell))

    ;; Perform the KB update.
    (reclaim-text (text? text-cell))
    (setf (text? text-cell) formatted-new-text)

    ;; Invalidate a region, or if XOR, draw the new text.
    (when workspace?
      (cond
	(paint-mode-style?
	 ;; See the similar computation (except in window coordinates)
	 ;; in `draw-or-change-color-in-text-cell-for-block'
	 (when unmagnified-width-of-text-to-draw-beyond?
	   (incff left-edge-of-cell
		  (+f (text-cell-left-margin (text-cell-format text-cell))
		      unmagnified-width-of-text-to-draw-beyond?)))

	 (invalidate-rectangle-of-block
	   workspace? table
	   left-edge-of-cell top-edge-of-cell
	   right-edge-of-cell bottom-edge-of-cell))
	(t
	 (update-images-of-text-cell
	   nil table text-cell
	   unmagnified-width-of-text-to-draw-beyond?
	   left-edge-of-cell top-edge-of-cell
	   right-edge-of-cell bottom-edge-of-cell))))))




;;; `Update-text-cell' ... ...  If the new text no longer fits into the space
;;; occupied by the old text, the whole table is erased and either redrawn or,
;;; if use-stack-of-slot-value-changes? is non-nil, scheduled for complete
;;; reformatting by change-slot-value (q.v.).  Use-stack-of-slot-value-changes?
;;; should only be supplied true when the change is initiated from within a
;;; with-updates-to-representations, which is notably true, generally, of calls
;;; stemming from change-slot-value, and friends.

;; MHD: change the protocol to be: Use-stack-of-slot-value-changes? is special
;; and is bound by with-updates-to-representations.  OK?  (MHD)

;;; Any text regions in text-cell are deleted, because it would be unduly difficult to
;;; update them correctly.
;;;
;;; For any table that is the only subblock of a temporary workspace (notably, a
;;; classic attribute table), the workpspace is shrink-wrapped after
;;; reformatting.

;;; Exception to WYSIWYG: update-text-cell is allowed to introduce a certain
;;; laxness in the WYSIWYG rule: when a cell in a table (other than column 0 of
;;; a readout-table instance, or any graph, or any table other than the file
;;; progress display while reading a KB) is updated, if the line is not
;;; growing beyond the size of the cell to the right or left, then this does not
;;; reformat the entire table (or do the equivalent) in order to ensure that all
;;; cells are formatted in accordance with their, and the table's, formats.  In
;;; practice, this means that cells can grow and never shrink.  Readout tables
;;; always get reformatted when a change happens in column 0, i.e., an edit to
;;; the expression to display.  To mitigate the inconvenience of this somewhat,
;;; there is an initialize-after-reading method for the class table that reformats
;;; tables (other than graphs) as they are read in from a KB to reestablish the
;;; WYSIWYGness of the table.

;;; Whenever this exception to WYSIWYG is introduced, the frame-flag (on tables)
;;; table-may-not-be-wysiwyg is set true.  The function
;;; make-or-reformat-table, which is called by reformat-table-in-place, always
;;; sets this flag to false (nil).

;;; The variable `suppress-use-stack-of-slot-value-changes-p' is internal to
;;; update-text-cell.  It is by default bound to nil, and only bound true by
;;; finish-update-to-representations-in-table.  When true, it has the same
;;; effect as passing in nil as this function's use-stack-of-slot-value-changes?
;;; argument.  It is used to suppress use of stack-of-slot-value-changes in a
;;; phase of use where it would lead to corruption or infinite recursion.  In
;;; particular, it is used to prevent the rare, but possible, reentry (using
;;; stack-of-slot-value-changes) via a call to update the file progress display,
;;; caused by saving out a table changed via update-text-cell in a
;;; KB-save-while-running.

(defvar suppress-use-of-stack-of-slot-value-changes-p nil) ; See Note C

(defun update-text-cell
    (table text-cell unformatted-new-text leave-as-a-single-line?
	   use-stack-of-slot-value-changes?)
  (multiple-value-bind
      (left-edge-of-cell top-edge-of-cell right-edge-of-cell bottom-edge-of-cell
			 row-index column-index)
      (get-table-cell-edges table text-cell)	; a bit slow
    (declare (ignore row-index))
    (when (has-subblocks-p table)			; optimization
      (delete-any-text-regions
	table
	left-edge-of-cell top-edge-of-cell
	right-edge-of-cell bottom-edge-of-cell))
    (let* ((text-box-format
	     (text-cell-format text-cell))
	   (width-of-cell
	     (-w right-edge-of-cell left-edge-of-cell)))
      (if (and leave-as-a-single-line?
	       (not (getfq (text-cell-plist text-cell)
			   'leave-as-single-line?)))
	  (setf (text-cell-plist text-cell)
		(slot-value-cons
		  'leave-as-single-line?
		  (slot-value-cons t (text-cell-plist text-cell)))))
      (cond
	((and use-stack-of-slot-value-changes?
	      (not suppress-use-of-stack-of-slot-value-changes-p)
	      (memq table stack-of-slot-value-changes))
	 (reclaim-text (text? text-cell))
	 (setf (text? text-cell) unformatted-new-text))
	(t (multiple-value-bind
	       (formatted-new-text width-of-longest-line)
	       ;; handle leave-text-representation-as-a-single-line?
	       ;;   case here for speed?
	       (format-text
		 unformatted-new-text text-box-format
		 (text-cell-plist text-cell)
		 width-of-cell
		 leave-as-a-single-line?
		 t nil nil)
	     (cond
	       ((and ;; Removed -- see note B!
;		     (or (not reading-kb-p)
; 			 (not (eq kb-file-progress table)))
		     
		     (<=w (+w (text-cell-left-margin
				text-box-format)
			      width-of-longest-line
			      (text-cell-right-margin
				text-box-format))
			  width-of-cell)
		     (<=w (compute-height-for-text
			    formatted-new-text text-box-format
			    (text-cell-plist text-cell))
			  (-w bottom-edge-of-cell
			      top-edge-of-cell))
		     (or (not (=f column-index 0))	; reformat on change to 1st column
			 (not (frame-of-class-p	        ;   of readout table
				table 'readout-table)))
		     (not (frame-of-class-p table 'graph))
		     ;; This check is necessary because a graph is an opaque
		     ;; block.  Consider making check for opaque block in general!
		     )

		;; This entire section is trying to determine whether we can do
		;; a minimal update.  We can do so if the old and new text are
		;; a single line with the same indentation, and if some leading
		;; characters agree.  First pop crud off the head of each text
		;; (fixnum indentation, or lost-spaces) to see if we are left
		;; with exactly one line.
		(let* ((old-text (text? text-cell))
		       (old-indentation?
			 (if (fixnump (first old-text))
			     (first old-text)))
		       (old-text-tail
			 (if (or old-indentation? (zero-lost-spaces-p (car old-text)))
			     (cdr old-text)
			     old-text))
		       (new-indentation?
			 (if (fixnump (first formatted-new-text))
			     (first formatted-new-text)))
		       (new-text-tail
			 (if (or new-indentation? (zero-lost-spaces-p (car formatted-new-text)))
			     (cdr formatted-new-text)
			     formatted-new-text))
		       (character-index-of-update-area?
			 ;; Each a single line with same indentation?
			 (if (and (null (cdr old-text-tail))
				  (null (cdr new-text-tail))
				  (=w (or old-indentation? 0)
				      (or new-indentation? 0)))
			     ;; Yes, find the first mismatched char.
			     (find-first-mismatch-in-text-lines
			       (first old-text-tail) (first new-text-tail))))
		       (unmagnified-width-of-text-to-draw-beyond?
			 (if character-index-of-update-area?
			     (+w (or old-indentation? 0)
				 (compute-minimum-left-edge-of-character-in-line-of-text
				   (first old-text-tail) character-index-of-update-area?
				   (text-cell-font-map text-box-format)
				   (default-word-spacing text-box-format))))))
		  (cond
		    ((or (null character-index-of-update-area?)
			 (<f character-index-of-update-area?
			     (text-string-length (first old-text-tail)))
			 (<f character-index-of-update-area?
			     (text-string-length (first new-text-tail)))) ; minimal update case

		     (perform-minimal-text-cell-update
		       table text-cell formatted-new-text
		       left-edge-of-cell top-edge-of-cell
		       right-edge-of-cell bottom-edge-of-cell
		       unmagnified-width-of-text-to-draw-beyond?))

		    (t
		     (reclaim-text formatted-new-text))))
		(set-table-may-not-be-wysiwyg table)) ; do only in the minimal update case?!

	       (t (update-images-of-block table t t)	    ; Note A
		  (reclaim-text (text? text-cell))
		  (setf (text? text-cell) formatted-new-text)
		  (cond
		    ((and use-stack-of-slot-value-changes?
			  (not suppress-use-of-stack-of-slot-value-changes-p))
		     (nconc stack-of-slot-value-changes
			    (stack-change-list table)))
		    (t
		     (finish-update-to-representation-in-table table)))))))))))

;; Fixnump test above used to be integerp.  I changed it here and throughout
;; this module upon learning that fixnum is inlined, while integerp is a
;; function call (in Chestnut).  This is ok, although ideally, both would be
;; inlined, I think. (MHD 6/4/92)

;; Maybe this should only just update a text cell when that is consistent with what would
;; happen if the table were completely reformatted.  In particular, if the table would
;; shrink in size when reformatted, it should be reformatted!

;; Note A: bug: In paint mode, this update-images-of-block doesn't actually
;; erase the block (it can't), but rather enqueues an inval region.  If anybody
;; forces drawing before the matching update-images-of-block is called (in
;; do-deferred-updates-to-representations-in-tables-if-appropriate), then the
;; table will be redrawn in its old format.  If the newly formatted table is
;; smaller than before, we'll be left with a big fat turd. -fmw, 12/7/94
;;
;; -- UPDATE: yeah, now we see this during saving especially, since every update
;; to the "file-progress" display forces an update; to fix this, I've suppress
;; the forcing in update-file-progress-display-status, which I believe handles
;; the only known case of this bug manifesting itself.  I could have added
;; with-locked-drawing to with-updates-to-representations, q.v., but it would
;; have been a lot of overhead for such an extremely obscure case.  (MHD 7/9/99)

;; Note B: the test for table being the value of kb-file-progress is useless,
;; since that variable is never bound to a table.  Perhaps it was intended to
;; fix a different bug, such as the bug discussed below (note C) regarding KB
;; saving, although it couldn't have done any good for that either. (MHD 7/9/99)

;; Note C: KB saving, while running, presents a special little problem: we might
;; be in the middle of handling updates using stack-of-slot-value-changes and in
;; finish-update-to-representations-in-table, and thereby trigger the saving of
;; the table in a KB (by setf'ing a slot in a savable table), and thereby
;; trigger a reentry of finish-update-to-representations-in-table, e.g., from
;; the openning of a new KB (module) for saving.  This bug was encountered that
;; we know of only by one customer, usually after running for several weeks
;; doing frequent saves while running. The bug manifested itself as an infinite
;; recursion. (MHD 7/9/99)



;;; `Find-first-mismatch-in-text-lines' finds the index of the first character
;;; in either text line that is different.

(defun find-first-mismatch-in-text-lines (text-line-1 text-line-2)
  (loop with length fixnum
		    = (minf (text-string-length text-line-2)
			    (text-string-length text-line-1))
	with previous-j fixnum = 0
	with j fixnum = 0
	for i fixnum from 0
	when (=f j i)
	  do (setq previous-j j)
	     (if (<f j length)
		 (incff j))
	while (and (<f i length)
		   (char=w (charw text-line-2 i) (charw text-line-1 i)))
	finally
	  (return previous-j)))


;;; `Do-deferred-updates-to-representations-in-tables', called by
;;; do-deferred-updates-to-representations-in-tables-if-appropriate when the
;;; value of stack-of-slot-value-changes is a list of tables, reformats the
;;; tables in the list, and reclaims the list.
;;;
;;; For any table that is the only subblock of a temporary workspace (notably, a
;;; classic attribute table), the workpspace is shrink-wrapped after
;;; reformatting.

(defun-void do-deferred-updates-to-representations-in-tables ()
  #+development
  (test-assertion
    (and (atom (car stack-of-slot-value-changes))
	 (table-p (car stack-of-slot-value-changes))))
  (loop with suppress-use-of-stack-of-slot-value-changes-p = t
	for previous-cons = nil then table-cons	; ends up with tail pointer, needed
						;   for optimized reclamation
	for table-cons on stack-of-slot-value-changes
	for table = (car-of-cons table-cons)
	do (finish-update-to-representation-in-table table)
	finally
	  (reclaim-slot-value-list-given-tail ; optimized reclamation
	    stack-of-slot-value-changes previous-cons)
	  (setq stack-of-slot-value-changes nil))) ; setting nil not required


;;; `Finish-update-to-representation-in-table' is a subfunction both of
;;; do-deferred-updates-to-representations-in-tables and update-text-cell that
;;; handles one of the the final stages of updating the representation of
;;; of some frame in a table.
;;;
;;; This is called when the table is known to have been erased, and presumably
;;; had changes made to the texts of its cells.
;;;
;;; This function does just these things:
;;;
;;;    (1) reformats the table;
;;;    (2) draws the table; and
;;;    (3) shrinkwraps the workspace the table is on iff
;;;      this is the only block on a temporary workspace
;;;
;;; It returns no useful values.


(defun-void finish-update-to-representation-in-table (table)  
  (reformat-table-in-place table)
  (update-images-of-block table nil t)
  (let ((superblock? (superblock? table)))
    (when (and superblock?		; classic-attribute-table-p test!
	       (alternative-classic-attribute-table-p table))
      (shrink-wrap-workspace superblock?))))





(defun update-images-of-text-cell
    (erase? table text-cell unmagnified-width-of-text-to-draw-beyond?
	    left-edge-of-cell top-edge-of-cell right-edge-of-cell bottom-edge-of-cell)
  (update-images
    erase? table table
    left-edge-of-cell top-edge-of-cell
    right-edge-of-cell bottom-edge-of-cell
    :no-bleeding
    'draw-or-change-color-in-table
    table text-cell unmagnified-width-of-text-to-draw-beyond? nil nil nil nil))

;; This is the primary customer of the flag which suppresses the bleeding hack.
;; Text cells are carefully engineered to never bleed, and if the bleeding hack
;; is used the borders flicker during text cell updating.  - ben 6/23/93

;; Note that unmagnified-width-of-text-to-draw-beyond?, passed in to the draw
;; function above, is what causes the clipping rectangle to be narrowed further
;; than what is specified by the four edges; the four edges really are just the
;; the proper four cell edges.  (MHD 7/6/90)

;; The result of the preceding comment is that when update-images decides to
;; enqueue an inval region, the region is larger than it should be.  -fmw,
;; 12/6/94






;;;; Scheduled Table Representation Updates 2



;;; The variable `table-representation-update-schedule' holds a queue of table
;;; representation updates.  A `table representation update' is a gensym cons of
;;; the form
;;;
;;;    (frame . unique-copy-of-frame's-serial-number)
;;;
;;; For any frame entered in the queue, frame will have had added one or more
;;; entries to its changed-slots-to-represent slot, a slot-value list, each
;;; entry of which is either a slot-value list of the form
;;;
;;;    (unique-slot-name slot-component-name slot-component-indicator)
;;;
;;; i.e., in the case of a slot component change, or merely a symbol:
;;;
;;;    unique-slot-name
;;;
;;; in the case of a normal slot change.  An entry for a given slot or slot
;;; component should not be added more than once to the list.  Entries are added
;;; by add-to-schedule-of-table-updates and removed by
;;; work-on-schedule-of-table-updates-loop, both of which are defined below.

(def-system-variable table-representation-update-schedule tables
  (:funcall make-empty-constant-queue))

(def-system-variable current-table-updates-task? tables nil)


(defparameter table-updates-task-priority 2)

(defun-substitution-macro schedule-table-updates-if-necessary ()
  (when (null current-table-updates-task?)
    (schedule-table-updates)))

(defun-void schedule-table-updates ()
  (schedule-table-updates-continuation))

;; This turned out to be a loser, especially on Windows NT, when we tried it
;; with E-SCOR.  Need to understand this better!
;;
;;   (with-immediate-scheduling
;;       (current-table-updates-task?)
;;     (work-on-schedule-of-table-updates-a-little))
;;
;; See this bug: HQ-1903609 "G2 is not getting scheduled by NT".  (MHD 2/7/99)

(defun-void schedule-table-updates-continuation ()
  (with-temporary-gensym-float-creation
      schedule-table-updates-continuation
    (with-future-scheduling
	(current-table-updates-task?
	  table-updates-task-priority
	  (subsecond-future-interval (table-update-interval?))
	  nil nil t)
      (work-on-schedule-of-table-updates-a-little))))


(defun-void add-to-schedule-of-table-updates
    (frame slot-description slot-component-name? slot-component-indicator?)
  (let* ((changed-slots (changed-slots-to-represent frame))
	 (unique-slot-name (unique-slot-name slot-description)))
    (when (null changed-slots)
      (constant-queue-enqueue table-representation-update-schedule
	(gensym-cons
	  frame
	  (copy-frame-serial-number (frame-serial-number frame)))))
    (cond
     ((or slot-component-name? slot-component-indicator?)
      (when (or (null changed-slots)
		(loop for a-changed-slot in changed-slots
		      never (and (consp a-changed-slot)
				 (eq (first a-changed-slot) unique-slot-name)
				 (eq (second a-changed-slot)
				     slot-component-name?)
				 (eq (third a-changed-slot)
				     slot-component-indicator?))))
	(#+SymScale slot-value-push-atomic
	 #-SymScale slot-value-push
	 (slot-value-list unique-slot-name
			  slot-component-name?
			  slot-component-indicator?)
	 (changed-slots-to-represent frame))))
     (t
      (when (or (null changed-slots)
		(loop for a-changed-slot in changed-slots
		      never (eq unique-slot-name a-changed-slot)))
	(#-SymScale slot-value-push
	 #+SymScale slot-value-push-atomic
	  unique-slot-name
	  (changed-slots-to-represent frame))))))
  (schedule-table-updates-if-necessary))

(defmacro work-on-schedule-of-table-updates-loop (use-scheduler-p)
  `(loop ,@(if use-scheduler-p ;; could change between invocations
	       '(with can-use-table-refresh-interval-p
		      = (can-use-table-refresh-interval-p)))
	 while (constant-queue-non-empty-p table-representation-update-schedule)
	 do (let* ((entry (constant-queue-dequeue table-representation-update-schedule))
		   (frame (car entry))
		   (frame-serial-number (cdr entry)))
	      (unless (frame-has-been-reprocessed-p frame frame-serial-number)
		(loop with changed-slots
			= #-SymScale
			  (prog1 (changed-slots-to-represent frame)
			    (setf (changed-slots-to-represent frame) nil))
			  #+SymScale
			  (atomic-exchange (changed-slots-to-represent frame) nil)
		      for slot-info in changed-slots
		      as unique-slot-name
			 = (if (atom slot-info)
			       slot-info
			       (first slot-info))
		      as slot-description?
			 = (get-slot-description-of-frame unique-slot-name frame)
		      as (slot-component-name? slot-component-indicator?)
			 = (if (atom slot-info) nil (cdr slot-info))
		      when slot-description?
			;; Nil indicates a lookup failure, which is rare, but
			;; can happen, e.g., if class changes are made after an
			;; update is scheduled, before it is run. (MHD 11/10/03)
			do (update-representation-tables-for-slot-change
			     frame slot-description?
			     slot-component-name? slot-component-indicator?)
		      finally (reclaim-slot-value-tree changed-slots)))
	      (reclaim-frame-serial-number frame-serial-number)
	      (reclaim-gensym-cons entry))
	,@(if use-scheduler-p
	      '(until (and can-use-table-refresh-interval-p
			   (time-slice-expired-p))))
	finally
	(when current-table-updates-task?
	  (cancel-task current-table-updates-task?)
	  (setq current-table-updates-task? nil))
	,@(if use-scheduler-p
	      '((when (constant-queue-non-empty-p
			table-representation-update-schedule)
		  (schedule-table-updates-continuation))))))

(defun-void work-on-schedule-of-table-updates-a-little ()
  (work-on-schedule-of-table-updates-loop t))  

;;; The function `finish-all-table-updates' completes and/or flushes all pending
;;; update tasks associated with scheduled table updates. This is the function
;;; to call from anywhere to ensure that all slot changes are fully reflected in
;;; their table representations.
;;;
;;; This is safe and efficient to call at practically any point, since all it
;;; does is work that would have been started, if not completed, on the next
;;; scheduler cycle.
;;;
;;; Note that it is not strictly necessary to call this if class changes would
;;; delete or mutate slot descriptions for slots scheduled to be updated. That
;;; is because we handle the case of slots changing or going away completely.
;;; (We only store the slot's unique-slot-name symbol, and not the actual slot
;;; description data structure, and the slot description is only looked up just
;;; prior to its use.  If it is absent, the update for changes to that slot is
;;; simply skipped.)  As for removing (or adding) cells corresponding to slots
;;; that have disappeared: that's handled separately (or should be) from this
;;; facility; this facility only deals with updating values of cells that
;;; already exist after their update has been scheduled.

(defun-void finish-all-table-updates ()
  (work-on-schedule-of-table-updates-loop nil))


;;; `Update-representation-tables-for-slot-change' ... Note that this can
;;; tolerate a slot-name, etc., not being valid.

(defun update-representation-tables-for-slot-change
    (frame slot-description
	   slot-component-name? slot-component-indicator?)
  ;; reference: code for with-updates-to-representations
  (let* ((stack-of-slot-value-changes
	   (stack-change-cons-macro
	     (if slot-component-name?
		 (nconc
		   (stack-change-list frame slot-description)
		   (stack-change-cons slot-component-name? slot-component-indicator?))
		 (stack-change-cons-macro frame slot-description))
	     stack-of-slot-value-changes)))
    (loop for representation in (frame-representations frame)
	  do (frame-class-case representation
	       (table
		 (when (table-representation-should-be-updated? frame representation)
		   (update-representations-in-table-with-slot-description
		     representation frame slot-description
		     slot-component-name? slot-component-indicator?)))))
    (reclaim-stack-change-tree
      (stack-change-pop stack-of-slot-value-changes))
    (do-deferred-updates-to-representations-in-tables-if-appropriate)))





;;;; Getting Text Cells and their Edges

;; Use these where appropriate!  Search for "table-rows" to find where!



;;; `Get-table-cell' returns the cell in table specified by row-index and column-index.
;;; It is assumed that there is such a cell.

(defun get-table-cell (table row-index column-index)
  (nth column-index (nth row-index (table-rows table))))

;; Consider replacing the calls to nth by in-line loops, to gain a bit of speed.



;;; `Get-table-cell-edges' returns, as six values, the four edges and the row and
;;; column index of cell, where cell is a cell in table.

(defun get-table-cell-edges (table cell)
  (loop with table-format = (table-format table)
	with format-of-superblock-if-a-table?
	  = (if (subtablep table)
		(table-format (superblock? table)))
	with left-border-width
	  = (if (and format-of-superblock-if-a-table?
		     (>w (table-column-boundary-width format-of-superblock-if-a-table?)
			 0))
		0
		(table-left-border-width table-format))
	with top-border-width
	  = (if (and format-of-superblock-if-a-table?
		     (>w (table-row-boundary-width format-of-superblock-if-a-table?)
			 0))
		0
		(table-top-border-width table-format))
	with right-border-width
	  = (if (and format-of-superblock-if-a-table?
		     (>w (table-column-boundary-width format-of-superblock-if-a-table?)
			 0))
		0
		(table-right-border-width table-format))
	with bottom-border-width		; only used nearby
	  = (if (and format-of-superblock-if-a-table?
		     (>w (table-row-boundary-width format-of-superblock-if-a-table?)
			 0))
		0
		(table-bottom-border-width table-format))
	with row-boundary-width = (table-row-boundary-width table-format)
	with column-boundary-width = (table-column-boundary-width table-format)
	with left-edge-of-cell
	with right-edge-of-cell
	with column-index = 0
	as remaining-row-edges
	   = (row-edges table)
	   then (cdr remaining-row-edges)
	as top-edge-of-cell
	   = (+w (top-edge-of-block table) top-border-width)
	   then (+w bottom-edge-of-cell row-boundary-width)
	as bottom-edge-of-cell
	   = (or (car remaining-row-edges)
		 (-w (bottom-edge-of-block table) bottom-border-width))
	as row-index from 0
	as row in (table-rows table)
	when (memq-macro cell row)
	  do (setq left-edge-of-cell
		   (+w (left-edge-of-block table) left-border-width))
	     (loop as remaining-column-edges
		      = (column-edges table)
		      then (cdr remaining-column-edges)
		   as cell? in row
		   do (setq right-edge-of-cell
			    (or (car remaining-column-edges)
				(-w (right-edge-of-block table) right-border-width)))
		   until (eq cell? cell)
		   do (incff column-index)
		   when cell?
		     do (setq left-edge-of-cell
			      (+w right-edge-of-cell column-boundary-width)))
	     (return
	       (values			
		 left-edge-of-cell top-edge-of-cell
		 right-edge-of-cell bottom-edge-of-cell
		 row-index column-index))))



;;; `Get-table-cell-indices' returns, as two values, the row and column index of
;;; cell, where cell is a cell in table.

(defun get-table-cell-indices (table cell)
  (loop with column-index = 0
	as row-index from 0
	as row in (table-rows table)
	when (memq-macro cell row)
	  do (loop as cell? in row
		   until (eq cell? cell)
		   do (incff column-index))
	     (return (values row-index column-index))))









;;;; Copying Text



;;; Copy-text returns a copy of text made up of new (or recycled) slot value conses
;;; and simple text strings.

(defun copy-text (text)
  (loop with car
	for text-element in text
	collect
	  (cond
	    ((atom text-element)
	     (if (or (fixnump text-element)
		     (symbolp text-element))
		 text-element		; else, assume string or wide string
		 (copy-text-line text-element)))
	    (t
	     (slot-value-cons-macro
	       (setq car (car text-element))
	       (case car
		 (lost-spaces
		  (if (fixnump (cdr text-element))
		      (cdr text-element)
		      (copy-text-line (cdr text-element))))
		 (context-carryover
		  (loop for symbol in (cdr text-element)
			collect symbol using slot-value-cons))
		 (t (cdr text-element))))))
	using slot-value-cons))

;; This could be speeded up a bit if that were necessary.









;;;; Text Cell Formatting



;;; Format-text-cell formats text-cell and returns the minimum width for it as formatted,
;;; which will not be less than the minimum-width-for-text-cell specified in the text
;;; cell format.  Width-for-cell? is the minimum width that the cell is already
;;; constrained to be; if it is nil or less than minimum-format-width-for-text-cell
;;; (and it can be negative), minimum-format-width-for-text-cell will be used as the
;;; format width.  When minimum-format-width-for-text-cell is used as the format width,
;;; the returned value will be the minimum possible width for text cell with its present
;;; text and format.

;;; When leave-as-a-single-line? is non-nil, text cell must have exactly one line.

;;; There should be no currently displayed images of a text cell being reformatted, at
;;; least of those parts that might change.

;; This is called only in module TABLES.

(defun format-text-cell
       (text-cell width-for-cell? leave-as-a-single-line? reformatting-with-same-format?
	include-indentations-and-widths? known-to-have-indentations-and-widths?)
  (let ((text-box-format (text-cell-format text-cell)))
    (multiple-value-bind (text width-of-longest-line)
	(format-text
	  (text? text-cell) text-box-format (text-cell-plist text-cell) width-for-cell?
	  leave-as-a-single-line? reformatting-with-same-format?
	  include-indentations-and-widths? known-to-have-indentations-and-widths?)
      (setf (text? text-cell) text)
      (maxw (+w (text-cell-left-margin text-box-format)
		width-of-longest-line
		(text-cell-right-margin text-box-format))
	    0 ; (minimum-width-for-text-cell text-box-format)    ; FIX THIS!!!
	    ))))

;; Consider implementing this as a macro.

;; When compute-width-for-text is implemented, revise make-text-cell-for-slot!
;; (There might already be another text cell using the same format that has the width.)





;;;; Attribute Tables, Compound Slots, and Slot Components



;; [Note: this may be redundant with definitions Joe is providing elsewhere; if
;; so, merge this with his stuff.]

;;; A `slot component' is a `component' of a "compound slot".  A `compound slot'
;;; is a kind of slot of a frame.  A `compound slot' may be either a `singular'
;;; or a `multiple' compound.  A `singular compound' has one `slot component
;;; group', a set of slot components, each of which is identified by its `slot
;;; component name' (along with the name of the slot of which it is a component,
;;; and the frame, as needed).  A `multiple compound' consists of a set of slot
;;; component groups, each element of which has an associated `slot component
;;; indicator', a fixnum integer or symbol that keys the access to a given slot
;;; component group.
;;;
;;; A `type of slot component' or `slot component type' is a like a slot type,
;;; or "type of slot" for a slot component.  A `slot component value' is the value
;;; of a slot component.
;;;
;;; Since slot components make up slots, their values are still slot values,
;;; i.e., slot value numbers, list structure consisting of slot value conses,
;;; recyclable text strings, etc.
;;;
;;; Slot component names and slot names exist within a single namespace.  It is
;;; an error to set up a class in which any two names (either slot component
;;; names or slot names) are the same.  For example, you cannot set up a slot
;;; component with the name line-width if you have set up a slot with the name
;;; line-width.  (Note that this error may not be detected by the frame system.)
;;;
;;; Slot component indicators must be unique within a multiple compound.  They
;;; may be the same as any slot name or component name; in fact they can be any
;;; symbol or fixnum, but there may be one found within the set of slot
;;; component groups within a given multiple compound slot.  It is an error to
;;; have more than one indicator with the same name within a multiple compound
;;; slot, but note that this error may go undetected, and the results are
;;; undefined.





;;;; Attributes, Attribute Tables, and Slots and Slot Components



;;; Traditionally, in G2 attribute tables have been used as a way to present
;;; slots (i.e., of frames) to users.  The typical attribute table shows a
;;; "class header" along the top strip (with white text on a black background
;;; strip).  This class actually represents the CLASS slot of a frame.  Then,
;;; below this attribute, come a series of rows showing the "attribute name" in
;;; the left column, i.e., a slot name or alias thereof, and the "attribute
;;; value" in the right column, i.e., the value of the slot, as written by that
;;; slot's "writer".
;;;
;;; A few slots never explicitly show the attribute name: e.g., the "text" slot
;;; of a procedure or a text box (a rule, statement, free text, message, etc.);
;;; or the class slot.
;;;
;;; Within the traditionaly framework, attribute table text cells represented at
;;; most one, and only one, entire slot, and a slot, in turn, could be
;;; represented by only one kind of text cell.  With the advent of slot
;;; components, we allow one attribute table cell represent a slot component,
;;; that is, a part a part of a cell, and in turn, a slot value may be
;;; represented by a number of different kinds of text cells.
;;;
;;; In the traditional case, a frame pointed to its "frame representations",
;;; i.e., (attribute) tables containing representations of one or more of its
;;; slots.  These representations have been in the form of "text cells"
;;; representing slot values and containing backpointers to the slot via
;;; the pair
;;;
;;;   <frame, slot-name>
;;;
;;;
;;; The introduction of multiple inheritance has necessitated a change of the
;;; backpointer to a slot from the above pair to the following triple:
;;;
;;;   <frame, slot-name, defining-class?>
;;;
;;; defining-class? may be omitted (or nil), and this gives the triple the exact
;;; same meaning as if it were the class of the frame.
;;;
;;; The name "slot name" here means the same as "pretty slot name" in the "new"
;;; terminology introduced in February, 1994.  For purposes of the documentation
;;; and code in this module, there is no distinction to be made, and simple the
;;; term "slot name" is used.
;;;
;;; In 4.0, as of February, 1994, a class and slot name no longer uniquely
;;; designate a slot; now, the triple is necessary.
;;; 
;;;
;;; The situation changes only slightly with the advent of slot components:
;;; frames continue to point to their representation tables, which continue to
;;; contain text cells with backpointers to their slot in the form of a <frame,
;;; slot-name, defining-class> triple.  Now, in addition, some text cells
;;; represent slot component values (instead of mere slot values) and these have
;;; backpointers in the form of a 7-tuple
;;;
;;;    <frame, slot-name, defining-class?,
;;;     slot-component-name, slot-component-indicator?,
;;;     virtual-attribute?, exported-format?>
;;;
;;; 
;;; How is this implemented?  
;;;
;;; For a text cell representing a slot, the triple <frame, slot-name,
;;; defining-class?> is stored in the "text cell plist" of a text cell as one
;;; or two entries: first, the frame and slot name are stored as a
;;; "non-standard" plist entry
;;;
;;;    <frame> <slot-name>
;;;
;;; (It is non-standard in that the the frame is the indicator, and the slot name
;;; is the value, wherease plist indicators are normally symbols or integers.)
;;;
;;; Second, defining-class? is stored, if necessary, i.e., if non-nil, on
;;; the entry
;;;
;;;   DEFINING-CLASS <defining-class/symbol/class-name>
;;;
;;; Third, exported-format? is stored, if non-nil, on the entry
;;;
;;;   EXPORTED-FORMAT t
;;;
;;; 
;;;
;;; For a text cell representing a slot component, the frame, slot-name, and
;;; defining-class? fields of the 7-tuple are represented in the same way.  The
;;; slot-component name field is represented by a new entry in the plist
;;;
;;;    SLOT-COMPONENT-NAME <slot-component-name/symbol>
;;;
;;; And, for a multiple-compound slot, the slot-component indicator? field is
;;; represented by the new entry in the plist
;;; 
;;;    SLOT-COMPONENT-INDICATOR <slot-component-indiator/fixnum-or-symbol>
;;;
;;; For a single-compound slot, the slot-component-indicator? field is nil.
;;;
;;; 
;;; Note that it is a constraint of the tables/text-cell interface that the
;;; backpointers are always valid, other than very transiently while changes
;;; like deletion, changes in the class hierarchy, and the like, are taking
;;; place.
;;;
;;;
;;; For a text cell representing a virtual attribute, the frame, slot-name, and
;;; defining-class? fields are represented the same way (defining-class? is always nil).
;;;
;;; And, in addition, the virtual-attribute? field is
;;; represented by
;;;
;;;    VIRTUAL-ATTRIBUTE t
;;;
;;;
;;; How does this appear to the user?
;;;
;;; The term `attribute' has always had a not-quite-straightforward mapping to
;;; to our world of frames and slots.  Here it gets less straightforward: it can
;;; now be used to refer to either a slot of a frame (an "item" in the user
;;; module) or a slot component of a ... [part?!] of a frame.
;;;
;;; Note that it may be convenient to refer to both "slots" and "slot
;;; components", collectively, as "attributes", in both documentation and code.





;;;; Compound Slots and Restrictions


;;; Since compound slots are to appear in the user interface as "attributes",
;;; and naturally thus to be restricted in the same way as attributes are.  Note
;;; that the set of compound-slot names and the set of slot names (or aliases
;;; thereof) are disjoint for a particular class.  This means that we can restrict
;;; both kinds of attributes with respect to the class.
;;;
;;; For example, if we have a class GRAPH, with a compound slot aliased as
;;; PLOTS, which has a slot component EXPRESSION, then the user restriction
;;; on
;;;
;;;   the EXPRESSION of any GRAPH
;;;
;;; restricts the expression slot component for all plots in the graph (there
;;; can be any number).
;;; 
;;; There is no way currently provided to restrict an attribute just on one
;;; instance.  Nor can you restrict just one slot component group.





;;;; Advanced Topics Related to Compound Slots



;;; COMPOUND SLOTS AND "INHERITANCE"
;;;
;;; Like the traditional frame/slot system, and tables therefor, there is no
;;; sophisticated means to clue the user into whether a value is gotten via
;;; "inheritance", whether one means by this a default value inherited from some
;;; higher class's "default slot value", or one means "the value of some slot
;;; higher up structurally" which fills in when I don't.
;;;
;;; [I understand that this is an important capability that is lacking from
;;; traditional frame/slot tables, as well as frame/slot-component tables.  It
;;; is a feature of parts.]
;;;
;;; COMPOUND SLOTS VS THE PARTS FACILITY
;;;
;;; This facility covers to some extent some of the same ground covered by the
;;; "parts" facility elsewhere in G2.  Why was this developed in parallel to
;;; parts?  What are the advantages of this over parts?  Is this compatible with
;;; parts?  Should this be merged with the parts facility?  Should this be
;;; replaced by the parts facility.  Should both exist side by side?
;;;
;;; The parts facility is to date incomplete and not ready for general use,
;;; according to its author, Ben Hyde.  It is, however, used and supported for
;;; its two main user-visible customers, charts and freeform tables.
;;;
;;;
;;; COMPOUND SLOTS VS. INFERIOR FRAMES (FIRST-CLASS SUBOBJECT)
;;;
;;; Parts are not the only alternative to compound slots.  Another alternative,
;;; and a far more promising and enticing one in our view, in many respects, is
;;; the use of frames, and their slots, or lists thereof, to hold the
;;; "subcomponents".  That is, use real first-class objects.
;;;
;;; Why was this not the way chosen?
;;;
;;; There is currently a sense that there's a "freeze" on first-class objects
;;; inherent in the architecture of G2.  In other words, that first-class
;;; objects (as subobjects) are somehow "banned" from the product.
;;;
;;; Why is this so?  What are the exceptions to this that already exist in the
;;; product, with or without it being visible to the user?  How are we to view
;;; them, as exceptions that there might be more of some day, or as historical
;;; anomalies grandfathered in? ...
;;;
;;; What are the objections to them?  They include use of space.  What have we
;;; done to optimize space consumed by frames (initial-value hacks, lookup slot
;;; hacks), and what more can be done?  What are possible answers to the
;;; objections?
;;;
;;; When are first-class objects being used in the product now?
;;;
;;;   (1) Users can create objects under attributes to their heart's content;
;;;   (2) "Simulation subtables" are supported (with a UI similar to the
;;;   compound-slot UI, and the user-attribute-subobject UI)
;;;
;;;
;;; COMPOUND SLOTS VS. SUBWORKSPACES HOLDING COMPONENTS
;;;
;;; This is an extension of first-class subobjects.  If an object could have
;;; subcomponents upon subworkspaces, users would have a very natural way to
;;; access, view, and edit them.  This is sort of a cadillac version of the
;;; above.  It incurs even more space costs.  It's quite promising in many ways.
;;;
;;; 
;;; COMPOUND SLOTS VS. VARIOUS ONE-OFF SCHEMES
;;;
;;; Connection structures hold a connection frame or class.  The class is
;;; instantiated automatically by code wishing to see it as a frame.
;;;
;;; Rules are kept inside of action buttons and user menu choices.  This is not
;;; supposed to be visible to users, but it leaks out to them in various ways by
;;; mistake.
;;;
;;; Tabular functions ....
;;;
;;; Slider needles on sliders, indicators on meters ..., ...
;;;
;;; Cells in a readout table (the two of them) ...
;;;
;;;
;;; COMPOUND SLOTS VS THE PARTS FACILITY
;;;
;;; This facility covers to some extent some of the same ground covered by the
;;; "parts" facility elsewhere in G2.  Why was this developed in parallel to
;;; parts?  What are the advantages of this over parts?  Is this compatible with
;;; parts?  Should this be merged with the parts facility?  Should this be
;;; replaced by the parts facility.  Should both exist side by side?
;;;
;;; According to its author, Ben Hyde, the parts facility is to date incomplete
;;; and not ready for general use.
;;;
;;;
;;; COMPOUND SLOTS VS. REALLY-COMPLICATED SLOTS
;;;
;;; This alternative is just saying, you don't have to have subcomponents, but
;;; just have complicated "atoms".  We actually have a lot of this all over the
;;; place.  They are almost always associated with complicated grammars.
;;;
;;; But they are fine to have in many cases and have their place.  The NAMES
;;; attribute (block::name-or-names-for-frame slot), for example, is a list of
;;; 0, 1, or more than one name.  This shouldn't change.  Still, there should be
;;; access to each or the components of this list from the G2 language.
;;;
;;; I think the component-parts-references work in the language will have to
;;; cover this.
;;;
;;; The descriptions of attributes in class definitions are a grey area.  It's
;;; nice to view them in long lists, but they really have structure and
;;; subattributes that it would be nice to focus in on, and for users to have
;;; access to in a structured way.






;;;; Compound Slots



;;; The global property `compound-type-descriptor' of a slot type's grammar
;;; category symbol holds the `compound-type-descriptor' structure.  Such a
;;; property exists if and only if a slot that uses such a slot type is a
;;; compound slot.
;;;
;;; Note that this is a property on on the "grammar category symbol" of the
;;; "slot type" of a given compound slot, not its "slot name".
;;;
;;; Note that a slot type's grammar category symbol also gives a slot its
;;; grammar, writer, and compiler, and that there can be many slots that have
;;; the same slot type.  Since the values of the components of a compound slot
;;; are not usually entered directly via the editor, the grammar for a compound
;;; slot need not be defined, as long any slot using it is declared
;;; NOT-USER-EDITABLE.
;;;
;;; For example, a slot can have the "slot type"
;;;
;;;    (TYPE 2D-VALUE-AXIS)
;;;
;;; in which 2D-VALUE-AXIS is the type's grammar category symbol.  So, in this
;;; example (compound-type-descriptor '2d-value-axis) yields the
;;; compound-type-descriptor structure for the slot.
;;;
;;; A `compound type descriptor' contains a list of descriptions of the
;;; components of a compound slot via the list in its
;;; `slot-component-descriptors' slot.
;;;
;;; A compound type descriptor also says whether instances of this compound type
;;; are named (via `compount-type-instances-are-named-p').
;;;
;;; It also knows the compound slot type is for (via `compound-type-name').
;;; 
;;; Notice that for any symbol C, a slot type's grammar category symbol,
;;;
;;;   (eq C (compound-type-name (compound-type-descriptor C)))
;;;
;;; is true.  And for any slot name S for a compound slot, that slot's
;;; compound type descriptor is given by
;;;
;;;   (compound-type-descriptor
;;;      (category-symbol-given-slot-type
;;;         (get-type-of-slot-if-any S)))
;;;
;;; Note that there is no way to to get to a slot name from a compound type
;;; descriptor, since there is not necessarily just one slot that uses it.

;; Clean this up to handle defining-class? wherever slot-name is handled,
;; and/or document the constraint or limitation that justifies not doing so!
;; (MHD 2/15/94)

(def-global-property-name compound-type-descriptor)

(def-structure (compound-type-descriptor
		 (:constructor
		   make-compound-type-descriptor-1
		   (compound-type-name
		     compound-type-instances-are-named-p
		     slot-component-descriptors
		     slot-component-name-for-names))
		 (:predicate compound-type-descriptor-p))
  compound-type-name
  compound-type-instances-are-named-p
  slot-component-descriptors
  slot-component-name-for-names)

(defun make-compound-type-descriptor (name instances-are-named-p slot-descriptors
					   slot-component-name-for-names)
  (make-compound-type-descriptor-1
    name instances-are-named-p slot-descriptors
    slot-component-name-for-names))


;; I may want to do something fancier in the maker forms later, for this
;; structure and the next two. -- JED If not, switch to defining the maker
;; directly via the :constructor. -- MHD



(def-structure (slot-component-descriptor
		 (:constructor
		   make-slot-component-descriptor-1
		   (slot-component-name
		     slot-component-initform
		     slot-component-features))
		 #+development
		 (:print-function print-slot-component-descriptor))
  slot-component-name
  slot-component-initform
  slot-component-features)

#+development
(defun print-slot-component-descriptor (slot-component-descriptor stream depth)
  (declare (ignore depth))
  (printing-random-object (slot-component-descriptor stream)
    (format stream "SLOT-COMPONENT-DESCRIPTOR ~A"
	    (slot-component-name slot-component-descriptor))))

(defun make-slot-component-descriptor (name initform features)
  (make-slot-component-descriptor-1 name initform features))

; feature-assq

(defparameter all-compound-type-subtypes
  '(type reference internal definition component-type not-user-editable
    do-not-put-in-attribute-table))

;    (ecase (car subtype)
 ;;     (type subtype)
 ;     (reference (caddr subtype))
 ;     (definition '(type local-name))
 ;     (internal nil))))


  
;;; A `compound-slot-descriptor' property is placed on a symbol that names a
;;; compound slot.  The value of this property is a `compound-slot-descriptor'
;;; structure.  A slot name that a compound-slot-descriptor property may also
;;; have a an associated slot putter.
;;;
;;; NOTE: THE ABOVE IS CHANGING -- WE PLAN TO PUT THIS ON THE TYPE CATEGORY
;;; SYMBOL.

(def-global-property-name compound-slot-descriptor)

(def-structure (compound-slot-descriptor
		 (:constructor
		   make-compound-slot-descriptor-1
		   (compound-slot-name
		     compound-slot-compound-type
		     compound-slot-parent-class
		     compound-slot-multiple-p
		     compound-slot-has-at-least-one-instance-p)))
  compound-slot-name
  compound-slot-compound-type		; the name, not the structure
  compound-slot-parent-class
  compound-slot-multiple-p
  compound-slot-has-at-least-one-instance-p)

(defun make-compound-slot-descriptor
    (name compound-type parent-class multiple-p
	  has-at-least-one-instance-p)
  (make-compound-slot-descriptor-1
    name compound-type parent-class multiple-p
    has-at-least-one-instance-p))


;;; Storage Format of Compound Slot Values & Compound Type Instances
;;;
;;; Compound-Slot-Value ::=
;;;   if (compound-slot-multiple-p compound-slot-descriptor)
;;;     (counter . <compound-type-instance>*)
;;;
;;; Compound-Type-Instance ::=
;;;   (name/fixnum . <compound-type-instance-slot-plist>)
;;;
;;; Compound-Type-Instance-Slot-Plist ::=
;;;   ( {slot-component-name  slot-component-value }* ) 
;;;
;;; only (make/copy/reclaim)-compound-type-instance should know the storage internals,
;;; regardless of the storage characteristics of multiple-instances and
;;; compound-type-instance-slot-values.  However, note that these are stored in KBs.

;; the following macros are equivalent and are the exported and internal
;; interfaces for the component group indicator.  Some day there will be
;; only one of these two.

(defmacro slot-component-group-indicator (slot-component-group)
  `(car ,slot-component-group))
(defmacro compound-type-instance-indicator? (x) `(car ,x))

(defmacro compound-type-instance-plist (x) `(cddr ,x))
(defmacro compound-type-instance-master-slot? (x) `(cadr ,x))
(defmacro slot-component-group-master-slot-name (x) `(cadadr ,x))

(defmacro component-groups-for-compound-slot-value (x) `(cdr ,x))
(defmacro multiple-compound-slot-value-instances (x) `(cdr ,x))
(defmacro multiple-compound-slot-value-real-instances (x) `(cddr ,x))
(defmacro multiple-compound-slot-value-counter (x) `(car ,x))

(defparameter compound-type-slot-not-present (list 'not-present))

(defmacro default-slot-component-group-p (slot-component-group)
  `(eq (slot-component-group-indicator ,slot-component-group)
       'default))

(defmacro component-group-slot (cti slot-component-name &optional default)
  (avoiding-variable-capture (cti slot-component-name)
    `(getf (compound-type-instance-plist ,cti) ,slot-component-name ,default)))

(defmacro set-component-group-slot (cti slot-component-name new-value)
  (avoiding-variable-capture (cti slot-component-name new-value)
    `(or (loop for tail on (compound-type-instance-plist ,cti) by 'cddr
	       when (eq (car tail) ,slot-component-name)
		 do
		    (setf (cadr tail) ,new-value)
		    (return t))
	 (progn
	   (setf (compound-type-instance-plist ,cti)
		 (slot-value-cons
		   ,slot-component-name
		   (slot-value-cons
		     ,new-value
		     (compound-type-instance-plist ,cti))))
	   ,new-value))))

(defsetf component-group-slot set-component-group-slot)

(defun remove-component-group-slot (compound-type-instance slot-component-name)
  (loop as previous-tail = nil then tail
        for tail on (compound-type-instance-plist compound-type-instance)
	         by 'cddr
	when (eq (car tail) slot-component-name)
	  do
	    (cond (previous-tail
		   (setf (cddr previous-tail) (cddr tail)))
		  (t
		   (setf (compound-type-instance-plist compound-type-instance)
			 (cddr tail))))
	    (reclaim-slot-value-cons (cdr tail))
	    (reclaim-slot-value-cons tail)
	    (return nil)))

(defmacro compound-type-instance-indicator-p (x)
  (avoiding-variable-capture (x)
    `(or (symbolp ,x)
	 (fixnump ,x))))

(defmacro compound-type-instance-component-value (cti slot-name)
  (avoiding-variable-capture (cti slot-name)
    `(let ((value-in-instance
	     (getfq (compound-type-instance-plist ,cti)
		    ,slot-name
		    compound-type-slot-not-present)))
       (cond ((eq value-in-instance compound-type-slot-not-present)
	      (get-default-slot-component-value-from-master-slot
		,cti ,slot-name))
	     (t
	      value-in-instance)))))


(defun get-default-slot-component-value-from-master-slot
    (compound-type-instance
      slot-component-name)
  (let* ((master-slot-reference?
	   (compound-type-instance-master-slot? compound-type-instance))
	 (compound-slot-descriptor?
	   (and master-slot-reference?
		(compound-slot-descriptor (cadr master-slot-reference?))))
	 (value-in-master-slot? compound-type-slot-not-present))
    (when (and compound-slot-descriptor?
	       (compound-slot-multiple-p
		 compound-slot-descriptor?))
      (loop for instance in
	    (multiple-compound-slot-value-instances
	      (get-slot-value (car master-slot-reference?)
			      (cadr master-slot-reference?)
			      nil))
	    when (eq (compound-type-instance-indicator? instance)
		     'default)
	      do (setf value-in-master-slot?
		       (getfq (compound-type-instance-plist
				instance)
			      slot-component-name
			      compound-type-slot-not-present))))
    (cond
      ((eq value-in-master-slot? compound-type-slot-not-present)
       (values (get-default-slot-component-value-from-type
		 compound-type-instance slot-component-name)
	       'shared-through-initform))
      (t
       (values value-in-master-slot? 'shared-through-master-slot)))))

(defun get-default-slot-component-value-from-type (slot-component-group
						    slot-component-name)
  (loop with compound-type-descriptor
	     = (compound-type-descriptor
		 (component-group-slot slot-component-group
				       'component-type))
	for slot-component-descriptor
	    in (slot-component-descriptors compound-type-descriptor)
	when (eq (slot-component-name slot-component-descriptor)
		 slot-component-name)
	  do
	    (let ((initform (slot-component-initform
			      slot-component-descriptor)))
	      (return
		(cond ((and (consp initform)
			    (eq (car initform) :funcall))
		       nil)
		      (t
		       initform))))))

(def-global-property-name slot-component-alias)
(def-global-property-name slot-component-pretty-name)

;;; `def-slot-component-alias' ...

(defmacro def-slot-component-alias (pretty-slot-name alias class compound-type)
  (declare (ignore class))
  `(progn
     (eval-when (:compile-toplevel :load-toplevel :execute)
       (setf (slot-component-alias ',pretty-slot-name)
	     ',alias)
       (setf (getf (slot-component-pretty-name ',alias)
		   ',compound-type)
	     ',pretty-slot-name))))
;      (def-slot-alias ,pretty-slot-name ,alias ,class)))


;;; The category `component-reference' is used by slot components that
;;; refer to the names of others slot components.

(add-grammar-rules
  '(;; (component-name unreserved-symbol)
    (component-reference integer)
    (component-reference unreserved-symbol)))

(def-slot-value-compiler component-reference (parse-result)
  parse-result)

(def-slot-value-writer component-reference (slot-value)
  (twrite slot-value))

(define-category-evaluator-interface (component-reference :access read-write)
    (or symbol integer)
  ((set-form (evaluation-value))
   (let ((value (evaluation-value-value evaluation-value)))
     (cond ((symbolp value)
	    (cond ((reserved-word-p value)
		   (values bad-phrase
			    (tformat-text-string
			      "~a is a reserved symbol" value)))
		  (t
		   value)))
	   (t
	    value))))
  ((get-form (slot-value))
   (cond ((symbolp slot-value)
	  (make-evaluation-symbol slot-value))
	 (t
	  (make-evaluation-integer slot-value)))))

(defmacro component-type (slot-component-group)
  `(compound-type-instance-component-value
     ,slot-component-group 'component-type))

;;; The property `compound-slot-value-writer-info' is used
;;; by grammar generation and writing for compound slot values.
;;; Note that calls to define-compound-slot-value-writer
;;; should be BEFORE the def-class the uses them.

(def-global-property-name compound-slot-value-writer-info)

;;; The macro `define-compound-slot-value-writer' ...

(defmacro define-compound-slot-value-writer
    (slot-type slot-name &optional alias? alias-for-plural?)
  `(eval-when (:compile-toplevel :load-toplevel :execute)
     (setf (compound-slot-value-writer-info
	     ',slot-type)
	   (list ',slot-name ',alias? ',alias-for-plural?))))

;; the structure of an entry in the table
;; table-of-component-type-grammar-info is:
;; (compound-type-name . (component-type-name category)*)

(defvar-for-macro table-of-component-type-grammar-info ())

(defun-for-macro set-component-type-grammar-info
    (component-type-name name-category-pairs)
  (let ((grammar-templates-for-type?
	 (assq component-type-name
	       table-of-component-type-grammar-info)))
    (cond
      (grammar-templates-for-type?
       (setf (cdr grammar-templates-for-type?) name-category-pairs))
      (t
       (push (cons component-type-name name-category-pairs)
	     table-of-component-type-grammar-info)))))

(defun self-evaluating-category? (category)
  (memq
    category
    '(integer interval number display-interval)))

(defun-for-macro store-grammar-info-for-slot-component
    (slot-component-name category)
  (list slot-component-name category))
;  (let ((assignment-op
;	 (if (self-evaluating-category? category)
;	     '= 'is)))
;    `(('the ',slot-component-name 'of :component-ref
;           ',assignment-op ,category)
;      (,slot-component-name 6 4))))

(defun-for-macro store-grammar-info-for-compound-type
    (component-type-name slot-specs slot-component-name-for-names)
  (loop with pairs = '()
	for slot-spec in slot-specs
	 as subtype-spec = (caddr slot-spec)
	do
          (case (car subtype-spec)
	    (type 
	     (push (store-grammar-info-for-slot-component
		     (car slot-spec) (cadr subtype-spec))
		   pairs))
	    (reference
	     (push (store-grammar-info-for-slot-component
		     (car slot-spec) (caddr subtype-spec))
		   pairs)))
	finally
	  (push (store-grammar-info-for-slot-component
		  slot-component-name-for-names 'name-or-names)
		pairs)
	  (set-component-type-grammar-info
	    component-type-name pairs)))


;;; A `compound-slots-for-class' property is placed on a symbol that names a
;;; class defined by def-class-using-compound-types.  This property is a list of
;;; the names of compound slots defined for that class.

(def-global-property-name compound-slots-for-class)


(defun-for-macro make-slot-component-descriptor-for-name-slot
    (compound-type-name slot-component-name-for-names)
  `(make-slot-component-descriptor
     (optimize-constant
       ',slot-component-name-for-names)
     nil
     (optimize-constant 
       '((subtype definition ,compound-type-name)
	 (type name-or-names)
	 (not-editable-in-default t)))))

(defun-for-macro make-slot-component-descriptors-from-slot-specs (slot-specs)
  (loop for slot-spec in slot-specs
	collect
	(cond
	  ((and (>= (length slot-spec) 3) ; may have options as cdddr someday
		(symbolp (car slot-spec))
		(consp (caddr slot-spec))
		(memq (caaddr slot-spec)
		      all-compound-type-subtypes))
	   (let* ((desired-features (cdddr slot-spec))
		  (subtype (caaddr slot-spec))
		  (subtype-spec (caddr slot-spec))
		  (features nil)) ; (list (list 'subtype subtype))))
	     (when (memq 'not-editable-in-default
			 desired-features)
	       (push `(not-editable-in-default t) features))
	     (case subtype
	      (type (push subtype-spec features)
		    (push `(subtype type) features))
	      (reference (push `(type ,(caddr subtype-spec)) features)
			 (push `(subtype reference ,(cadr subtype-spec))
			       features))
	      (internal (push `(not-user-editable t) features)
			(push `(subtype internal) features))
	      )
	     `(make-slot-component-descriptor
		',(car slot-spec)
		,(let ((initform (cadr slot-spec)))
		   (cond
		     ((and (consp initform)
			   (eq (car initform) :funcall-at-load-time))
		      `(,(cadr initform)
			 ,@(mapcar #'(lambda (x) `(quote ,x)) (cddr initform))))
		     (t
		      `',initform)))
		',features)))
	  (t
	   (error "Malformed compound type slot descriptor ~s" slot-spec)))))

(defun-for-macro make-slot-component-descriptor-for-slot-component-type
    (compound-type-name)
  `(make-slot-component-descriptor
     'component-type nil '((subtype component-type)
			   (component-type  ,compound-type-name)
			   (type component-group-header) ; JED 1/30/94
			   (do-not-identify-in-attribute-tables t)
			   (not-user-editable t))))

(defun-for-macro make-accessor-macros-for-compound-type-slots (slot-specs)
  (loop for slot-spec in slot-specs
	 as slot-component-name = (car slot-spec)
	;; hack: should allow inclusions in compound-slot-types.
	;; This is needed to avoid multiple redefinitions of the
	;; same macro
	when (not (eq slot-component-name 'chart-element-uid))
	collect
	`(defmacro ,slot-component-name (slot-component-group)
	   `(compound-type-instance-component-value
	      ,slot-component-group ',',slot-component-name))
;	   `(getf (compound-type-instance-plist ,slot-component-group)
;		   ',',slot-component-name))
	when (not (eq slot-component-name 'chart-element-uid))
	collect
	`(defsetf ,slot-component-name (slot-component-group) (new-value)
	   `(setf (component-group-slot ,slot-component-group
					',',slot-component-name)
		  ,new-value))
	))

(defmacro def-compound-type (name-and-options &body slots) ; EXPORTED
  (destructuring-lambda-list (compound-type-name
			       &key named
			       slot-value-writer-function
			       slot-value-compiler-function)
      (if (atom name-and-options) (list name-and-options) name-and-options)
    (declare (ignore slot-value-writer-function slot-value-compiler-function))
    (let ((slot-component-name-for-names (format-symbol "~a-NAMES" compound-type-name)))
      (store-grammar-info-for-compound-type
	compound-type-name slots slot-component-name-for-names)
      `(progn
	 (setf (compound-type-descriptor ',compound-type-name)
	       (make-compound-type-descriptor
		 ',compound-type-name
		 ,named
		 (list
		   ,(make-slot-component-descriptor-for-slot-component-type
		      compound-type-name)
		   ,@(and named
			  (list (make-slot-component-descriptor-for-name-slot
				  compound-type-name slot-component-name-for-names)))
		   ,@(make-slot-component-descriptors-from-slot-specs
		       slots))
		 ',slot-component-name-for-names))
	 ,@(make-accessor-macros-for-compound-type-slots
	     (if named
		 (cons (list slot-component-name-for-names) slots)
		 slots))))))

(defun-for-macro get-compound-slot-category-name (compound-slot-name)
  (build-ab-symbol compound-slot-name 'grammar 'spec))

(defun-for-macro generate-grammar-rules-compound-slot
    (class-name compound-slot-name
		compound-type-name multiple-p)
  (loop with grammar-rules = '()
	with name-for-whole-slot-grammar
	     = (get-compound-slot-category-name compound-slot-name)
	with name-for-annotations
	     = ;  (if multiple-p
		   (build-ab-symbol compound-slot-name 'annotations)
		;    name-for-whole-slot-grammar)
	with name-for-annotation
	     = (build-ab-symbol compound-slot-name 'annotation)
	with category-for-component-group? = nil
        for (slot-component-name category)
	    in (cdr (assq compound-type-name
			  table-of-component-type-grammar-info))
	initially
	 (cond
	   (multiple-p
	    ;; generate header rules
	    (let ((name-for-compound-slot-header
		   (build-ab-symbol compound-slot-name 'header))
		  (name-for-naming-spec
		   (build-ab-symbol compound-slot-name 'naming 'spec))
		  (singular-or-plural-compound-type-name
		   (build-ab-symbol compound-slot-name 'type 'name))
		  (writer-info? (compound-slot-value-writer-info
				  compound-type-name))
		  (name-for-naming-spec-element
		   (build-ab-symbol compound-slot-name 'naming 'spec 'element)))
	      (push `(,name-for-whole-slot-grammar
			,name-for-compound-slot-header
			(1 nil))
		    grammar-rules)
	      (push `(,name-for-whole-slot-grammar
			(,name-for-compound-slot-header '\;
			 ,name-for-annotations)
			(1 3))
		    grammar-rules)
	      (push `(,name-for-compound-slot-header
			(integer ,singular-or-plural-compound-type-name)
			(1 nil))
		    grammar-rules)
	      (push `(,name-for-compound-slot-header
			(integer ,singular-or-plural-compound-type-name
			 '\: ,name-for-naming-spec)
			(1 4))
		    grammar-rules)
	      (push `(,singular-or-plural-compound-type-name
			',(if writer-info?
			      (cadr writer-info?)
			      compound-type-name))
		    grammar-rules)
	      (push `(,singular-or-plural-compound-type-name
			',(if writer-info?
			      (caddr writer-info?)
			      (intern (format nil "~as"
					      compound-type-name)
				      (find-package "AB"))))
		    grammar-rules)
	      (push `(,name-for-naming-spec ,name-for-naming-spec-element)
		    grammar-rules)
	      (push `(,name-for-naming-spec
			(,name-for-naming-spec-element '\,
			 ,name-for-naming-spec)
			(2 1 3) simplify-associative-operation)
		    grammar-rules)
	      (push `(,name-for-naming-spec-element
			(',compound-type-name integer
			 'named unreserved-symbol)
			(2 4))
		    grammar-rules)
	      ))
	   (t
	    (push `(,name-for-whole-slot-grammar
		      ('a ',compound-type-name)
		      (nil nil))
		  grammar-rules)
	    (push `(,name-for-whole-slot-grammar
		      ('a ',compound-type-name '\; ,name-for-annotations)
		      (nil 4))
		  grammar-rules)))
	  ;; generate them list rules 
	  (push `(,name-for-annotations
		    ,name-for-annotation)
		grammar-rules)
	  (push `(,name-for-annotations
		    (,name-for-annotation
		       '\; ,name-for-annotations)
		    (2 1 3) simplify-associative-operation)
		grammar-rules)
	  (when multiple-p
	    ;; generate component-access grammar
	    (setf category-for-component-group?
		  (build-ab-symbol compound-slot-name 'component 'access))
	    ;; "the plot named foo"
	    (push `(,category-for-component-group?
		      ('the ',compound-type-name 'named unreserved-symbol)
		      (named 4))
		  grammar-rules)
	    ;; "plot 1"
	    (push `(,category-for-component-group?
		      (',compound-type-name integer)
		      (numbered 2))
		  grammar-rules)
	    ;; any plot
	    (push `(,category-for-component-group?
		      ('any ',compound-type-name)
		      (any))
		  grammar-rules))
	do
    (multiple-value-bind (phrases transform)
	(generate-phrases-for-slot-component
	  slot-component-name category category-for-component-group? class-name)
      (loop for phrase in phrases
	    do
	(push
	  `(,name-for-annotation ,phrase ,transform)
	  grammar-rules)))
	finally
	  (return (nreverse grammar-rules))))

(defun-for-macro generate-phrases-for-slot-component
    (slot-component-name category category-for-component-group? class-name)
  (let* ((names (get-names-for-slot-component
		  slot-component-name class-name))
	 (assignment-op
	  (if (self-evaluating-category? category)
	      '= 'is)))
    (cond
      (category-for-component-group?
       (values (loop for name in names
		     collecting
		     `('the ',name 'of ,category-for-component-group?
			    ',assignment-op ,category))
	       `(,slot-component-name 6 4)))
      (t
       (values (loop for name in names
		     collecting
		     `('the ',name ',assignment-op ,category))
	       `(,slot-component-name 4 (single)))))))

(defun get-names-for-slot-component (slot-component-name class-name)
  (declare (ignore class-name))
  (let ((alias?
	  (slot-component-alias slot-component-name)))
    (if alias?
	(list alias? slot-component-name)
	(list slot-component-name))))

(defun get-best-name-for-slot-component (slot-component-name class-name)
  (declare (ignore class-name))
  (or (slot-component-alias slot-component-name)
      slot-component-name))
  
(defun get-slot-component-name-for-alias-if-any (alias class-name compound-type)
  (declare (ignore class-name))
  (getf (slot-component-pretty-name alias) compound-type))

(defun-for-macro find-compound-type-spec (slot-spec)
  (loop for elt in slot-spec
	do (when (and (consp elt)
		      (eq (car elt) 'compound-type))
	     (return elt))
	finally
	  (return nil)))


(defun-for-macro compound-type-option-specified-p (compound-type-options option)
  (if (memq option compound-type-options)
      t nil))

(defun-for-macro expand-compound-slot-spec (parent-class slot-spec compound-type-spec)
  (let* ((compound-type-name (cadr compound-type-spec))
	 (compound-type-options (cddr compound-type-spec))
	 (multiple-p (compound-type-option-specified-p compound-type-options
					      'multiple))
	 (grammar-rules
	  (generate-grammar-rules-compound-slot
	    parent-class (car slot-spec) compound-type-name multiple-p))
	 (category-for-slot (caar grammar-rules)))
    ;; what about initforms? make 'em nil for now
    (values
      `(,(car slot-spec) nil (type ,category-for-slot) ; ,(cadr compound-type-spec))
	 ,@(copy-seq (cdr (member compound-type-spec slot-spec))))
      `(setf
	 (compound-slot-descriptor ',(car slot-spec))
	 (make-compound-slot-descriptor
	   ',(car slot-spec)
	   ',compound-type-name
	   ',parent-class
	   ',multiple-p
	   ',(compound-type-option-specified-p compound-type-options
					       'at-least-one-element)))
      `(add-grammar-rules
	 ',grammar-rules)
      `(def-slot-value-compiler ,category-for-slot (parse-result frame slot-name)
	 (compile-compound-slot-value parse-result frame slot-name
				      ',compound-type-name ',multiple-p))
      `(def-slot-value-writer ,category-for-slot (slot-value frame)
	 (if write-compound-slots-parseably?
	     ,(if multiple-p
		  `(write-multiple-compound-slot-value
		    frame slot-value ',compound-type-name)
		  `(write-single-compound-slot-value
		     frame slot-value ',compound-type-name))
	     (write-component-group-count 
	       slot-value ',compound-type-name)))
      `(def-slot-putter ,(car slot-spec) (frame new-value)
	 (cond
	   ;; the editing case - should be unique marker 
	   ((memq (car new-value) '(multiple single))
	    (put-compound-slot-value
	      frame ',(car slot-spec) new-value))
	   (t
	    (values (without-consistency-analysis (frame)
		      (setf (,(car slot-spec) frame) new-value))
		    t)))))))


(defun-for-macro parse-slot-specs-for-compound-types (parent-class slot-specs)
  (loop with all-slot-specs = '()
	with compound-slot-descriptor-forms = '()
	with compound-slots-for-class = '()
	with grammar-creating-forms = '()
	with compilers = '()
	with writers = '()
	with putters = '()
	for slot-spec in slot-specs
	 as compound-type-spec? = (find-compound-type-spec slot-spec)
	do
          (cond
	    (compound-type-spec?
	     (multiple-value-bind
		 (real-slot-spec compound-slot-descriptor-form grammar-creating-form
				 compiler writer putter)
		 (expand-compound-slot-spec
		   parent-class slot-spec compound-type-spec?)
	       (push real-slot-spec all-slot-specs)
	       (push (car slot-spec) compound-slots-for-class)
	       (push grammar-creating-form grammar-creating-forms)
	       (push compound-slot-descriptor-form
		     compound-slot-descriptor-forms)
	       (push compiler compilers)
	       (push writer writers)
	       (push putter putters)))
	    (t
	     (push slot-spec all-slot-specs)))
	finally
	  (return (values (reverse all-slot-specs)
			  (reverse compound-slot-descriptor-forms)
			  (reverse compound-slots-for-class)
			  (reverse grammar-creating-forms)
			  (reverse compilers)
			  (reverse writers)
			  (reverse putters)
			  ))))


;;; `def-class-using-compound-types' is like def-class with the following exceptions:
;;;
;;; Instead of a (type ...) spec slots may have a (compound-type ...) spec.  Such
;;; slots are called compound slots.  The name of a compound-slot should not
;;; be used by some other normal slot in some other def-class.
;;;
;;; Compound slots are not accessed directly by the G2 implementor or
;;; application developer.  The slot components of the compound-type-instance(s)
;;; in a compound-slot are, instead.  There are operations for initializing
;;; compound-slots, as well as adding and deleting individual members.  This
;;; implies for the lisp developer that the putter and reclaimer for
;;; compound-slots are "owned" by the internals of this module, and any attempt
;;; to define a custom putter or reclaimer will result in the end of the
;;; universe as we know it.
;;;
;;; Compound-slots have one or more compound-type-instances as their values.  A
;;; compound-type-instance is like a lightweight frame, whose representation is
;;; not important to discuss here.  Compound-type-instances have, instead of
;;; "slots", "slot components", which can g2-types or references to other
;;; compound-type-instances contained the same block or item.
;;;
;;; The values in the slots of compound-types can be of any storage type,
;;; although standard slot values (things that can be reclaimed by
;;; reclaim-slot-value) are preferred.  If the value cannot be represented by
;;; slot values a special reclaimer can be defined through
;;; def-slot-component-reclaimer.  There is no parallel slot-component-compiler
;;; maintained by this module.  The one defined for the G2 type in question (if
;;; any) will be used.

(defmacro def-class-using-compound-types (name-and-options &body slots) ; EXPORTED
  (let ((parent-class (if (atom name-and-options)
			  name-and-options
			  (car name-and-options))))
    (multiple-value-bind
	(all-slot-specs compound-slot-descriptor-forms compound-slots-for-class
			grammar-creating-forms compilers writers putters)
	(parse-slot-specs-for-compound-types parent-class slots)
      `(progn
	 (def-class ,name-and-options
	   ,@all-slot-specs)
	 ,@compound-slot-descriptor-forms
	 (setf (compound-slots-for-class ',parent-class)
	       ',compound-slots-for-class)
	 ,@grammar-creating-forms
	 ,@compilers
	 ,@writers
	 ,@putters
	 ))))

(defun is-slot-multiple-compound-slot? (slot-name defining-class?)
  (declare (ignore defining-class?))
  (let ((descriptor? (compound-slot-descriptor slot-name)))
    (and descriptor?
	 (compound-slot-multiple-p descriptor?))))

;;; the function `if-slot-is-compound-is-it-editable?' is used in
;;; editing predicates to see if it is an editable compound slot
;;; or else returns t implying that this function is "and"ed with
;;; other restrictions.

(defun if-slot-is-compound-is-it-editable? (slot-name defining-class?
						      slot-component-name?)
  (declare (ignore defining-class?))
  (let ((compound-slot-descriptor?
	 (compound-slot-descriptor slot-name)))
    (cond
      ((and compound-slot-descriptor? (not slot-component-name?))
       write-compound-slots-parseably?)
      (t
       t))))


;;; `Get-slot-component-features' ...

(defun get-slot-component-features
    (slot-name defining-class? slot-component-name?)
  (declare (ignore defining-class?))	; for now -- this will later
					;   be on the type, kept on the
					;   slot description! (MHD 2/14/94)
  (loop with compound-slot-descriptor = (compound-slot-descriptor slot-name)
	with compound-type-descriptor
	   = (compound-type-descriptor
	       (compound-slot-compound-type compound-slot-descriptor))
	for slot-component-descriptor
	    in (slot-component-descriptors compound-type-descriptor)
	when (eq slot-component-name?
		 (slot-component-name slot-component-descriptor))
	  return (slot-component-features slot-component-descriptor)))

;; Consider arranging things so this doesn't need to loop, i.e., putting the
;; descriptor right on the slot-component-name?'s plist. (MHD)


(defun slot-component-group-name-or-names (slot-component-group
					    component-type-name)
  (let ((component-type-descriptor (compound-type-descriptor
				    component-type-name)))
    (compound-type-instance-component-value
      slot-component-group
      (slot-component-name-for-names
	component-type-descriptor))))

;;; `set-slot-component-group-name-or-names' is a low-level function
;;; that should only be called on freshly created slot-component-groups.

(defun set-slot-component-group-name-or-names (slot-component-group
					    component-type-name
					    name-for-component)
  (let ((component-type-descriptor (compound-type-descriptor
				    component-type-name)))
    (setf (component-group-slot
	    slot-component-group
	    (slot-component-name-for-names
	      component-type-descriptor))
	  name-for-component)))

(defun slot-component-group-count (frame slot-name defining-class?)
  (length (multiple-compound-slot-value-real-instances
	    (get-slot-value frame slot-name defining-class?))))

(defun slot-component-group-nth-indicator? (frame slot-name defining-class? index)
  (let ((instances (multiple-compound-slot-value-real-instances
		     (get-slot-value frame slot-name defining-class?))))
    (and (<f index (length instances))
	 (slot-component-group-indicator (nth index instances)))))

(defun-for-macro slot-component-groups-path
		 (path-name variable data-type prep-phrases
			    inclusive? allowed-prepositions data)
  (declare (ignore data-type data allowed-prepositions))
  (when (null prep-phrases)
    (error "OF is missing in ~S iteration path of ~S" path-name variable))
  (when inclusive?
    (error "Inclusive stepping is not supported in ~S path of ~S (prep-prase = ~:S)"
	   path-name variable prep-phrases))
  (let* ((iteration-domain (cadar prep-phrases))
	 (remaining-component-groups-var (loop-gentemp))
	 (generator-bindings `((,remaining-component-groups-var
				  (multiple-compound-slot-value-real-instances
				    ,iteration-domain))
			       (,variable nil)))
	 (generator-initialize nil)
	 (generator-eof-p `(null ,remaining-component-groups-var))
	 (generator-advance
	   `(,variable
	     (car-of-cons ,remaining-component-groups-var)
	     ,remaining-component-groups-var
	     (cdr-of-cons ,remaining-component-groups-var))))
    `(,generator-bindings
      ,generator-initialize
      ,generator-eof-p
      nil
      nil
      ,generator-advance)))

(define-loop-path (slot-component-groups slot-component-group)
    slot-component-groups-path (of))

(defun get-referred-slot-name (slot-name referring-slot-component-name)
  (let* ((compound-slot-descriptor (compound-slot-descriptor slot-name))
	 (compound-type-descriptor
	   (compound-type-descriptor
	     (compound-slot-compound-type compound-slot-descriptor)))
	 (slot-component-features
	   (loop for slot-component-descriptor
		     in (slot-component-descriptors compound-type-descriptor)
		 when (eq referring-slot-component-name
			  (slot-component-name slot-component-descriptor))
		   return (slot-component-features slot-component-descriptor)))
	 (subtype (feature-assq 'subtype slot-component-features))
	 (referred-slot-name (caddr subtype)))
    referred-slot-name))

(defun get-slot-component-indicator-for-name-if-any?
    (frame slot-name component-group-name)
  (let* ((compound-slot-descriptor?
	   (compound-slot-descriptor slot-name))
	 (compound-type-descriptor?
	   (and compound-slot-descriptor?
		(compound-type-descriptor
		  (compound-slot-compound-type
		    compound-slot-descriptor?)))))
    (and
      compound-type-descriptor?
      (compound-slot-multiple-p compound-slot-descriptor?)
      (if
	(memq component-group-name '(default any))
	'default
	(loop with slot-name-for-names-of-instances
	      = (slot-component-name-for-names
		  compound-type-descriptor?)
	      with instance-list = (multiple-compound-slot-value-real-instances
				     (get-slot-value frame slot-name))
	      for instance in instance-list
	      as name-or-names-for-instance
	      = (compound-type-instance-component-value
		  instance slot-name-for-names-of-instances)
	      when (if (atom name-or-names-for-instance)
		       (eq component-group-name name-or-names-for-instance)
		       (memq component-group-name
			     name-or-names-for-instance))
		do
		  (return (slot-component-group-indicator instance)))))))


(defun get-slot-component-group-by-reference (frame slot-component-group
					       referring-slot-component-name)
  
  (let* ((compound-type-descriptor (compound-type-descriptor
				     (component-type slot-component-group)))
	 (slot-component-features
	   (loop for slot-component-descriptor
		     in (slot-component-descriptors compound-type-descriptor)
		 when (eq referring-slot-component-name
			  (slot-component-name slot-component-descriptor))
		   return (slot-component-features slot-component-descriptor)))
	 (subtype (feature-assq 'subtype slot-component-features))
	 (referred-slot-name (caddr subtype))
	 (compound-slot-descriptor-for-referred
	   (compound-slot-descriptor referred-slot-name))
	 (compound-type-descriptor-for-referred
	   (compound-type-descriptor
	     (compound-slot-compound-type
	       compound-slot-descriptor-for-referred))))
    (loop with name-for-reference
	    = (compound-type-instance-component-value
		slot-component-group referring-slot-component-name)
	  with slot-name-for-names-of-instances
	       = (slot-component-name-for-names
		   compound-type-descriptor-for-referred)
          with instance-list = (multiple-compound-slot-value-real-instances
				 (get-slot-value frame referred-slot-name))
	  for instance in instance-list
	   as name-or-names-for-instance
	      = (compound-type-instance-component-value
		  instance slot-name-for-names-of-instances)
	   as count from 1 by 1
	  when 	(if (symbolp name-for-reference)
		    (or (eq name-for-reference name-or-names-for-instance)
			(and (consp name-or-names-for-instance)
			     (memq name-for-reference name-or-names-for-instance)))
		    (=f count name-for-reference))
	    return instance
	  finally
;	    (format t "Looking for name = ~s in:~%"
;		    name-for-reference)
;	    (pprint-compound-slot frame referred-slot-name)
	    (return
	      (cond ((or (compound-slot-has-at-least-one-instance-p
			   compound-slot-descriptor-for-referred)
			 instance-list)
		     (car instance-list))
		    (t
		     nil))))))

(def-slot-value-writer component-group-header (component-type frame)
  (declare (ignore frame))
  (write-symbol-with-a-or-an component-type))


#+development
(defun pprint-compound-slot (frame slot-name &optional defining-class?)
  (let ((compound-slot-descriptor?
	  (compound-slot-descriptor slot-name))) ; use defining-class? (?!)
    (when compound-slot-descriptor?
      (cond
	((compound-slot-multiple-p compound-slot-descriptor?)
	 (let* ((slot-value
		  (get-slot-value frame slot-name defining-class?))
		(counter (multiple-compound-slot-value-counter slot-value))
		(instances (multiple-compound-slot-value-instances slot-value)))
	   (declare (ignore counter))	; ok? (MHD 2/2/94)
	   (loop for instance in instances
		 do (pprint-component-group instance))))
	(t
	 (pprint-component-group
	   (get-slot-value frame slot-name defining-class?)))))))

#+development
(defun pprint-component-group (component-group)
  (format t "_________________________________~%")
  (format t "ID=~s for:~%" (slot-component-group-indicator component-group))
  (loop for (key value) on (compound-type-instance-plist component-group) by 'cddr
	do
    (format t "~a -> ~s~%"
	    key
	    (if (managed-float-p value)
		(managed-float-value value)
		value))))
			 
(defun compound-type-has-slot-p (compound-type-descriptor slot-name)
  (loop for slot-component-descriptor in (slot-component-descriptors
					       compound-type-descriptor)
	thereis (eq slot-name
		    (slot-component-name slot-component-descriptor))))


(defun compound-type-slot-if-any (compound-type-descriptor slot-name)
  (loop for slot-component-descriptor in (slot-component-descriptors
					       compound-type-descriptor)
	when (eq slot-name
		 (slot-component-name slot-component-descriptor))
	  return slot-component-descriptor))

(defvar initializing-compound-slot? nil)

(defun initialize-compound-slot-value (frame slot-name)
  (let ((compound-slot-descriptor? (compound-slot-descriptor slot-name))
	(initializing-compound-slot? t))
    (when compound-slot-descriptor?
      (cond
	((compound-slot-multiple-p compound-slot-descriptor?)
	 (change-slot-value
	   frame slot-name (slot-value-list 0)
	   nil)				; defining-class? (!)
	 (when (compound-slot-multiple-p compound-slot-descriptor?)
	   (add-instance-to-multiple-compound-slot-value
	     frame slot-name nil 'default))
	 (when (compound-slot-has-at-least-one-instance-p
		 compound-slot-descriptor?)
	   (add-instance-to-multiple-compound-slot-value
	     frame slot-name nil nil)))
	(t
	 (change-slot-value
	   frame slot-name
	   (make-compound-type-instance
	     (compound-slot-compound-type compound-slot-descriptor?)
	     'only)
	   nil))))))			; defining-class? (!)
	   
(defun clone-compound-slot-value (compound-slot-value new-frame slot-name)
  (let ((new-slot-value (copy-for-slot-value compound-slot-value))
	(compound-slot-descriptor (compound-slot-descriptor slot-name)))
    (when (compound-slot-multiple-p compound-slot-descriptor)
      (loop for instance in (multiple-compound-slot-value-instances
			      new-slot-value)
	    do
	(setf (car (compound-type-instance-master-slot? instance))
	      new-frame)))
    new-slot-value))

(defmacro compound-slot-value-error (control-string &body args)
  ;; error should be less severe!
  `(error ,control-string ,@args))

(defun get-compound-slot-compound-type (slot-name)
  (let ((compound-slot-descriptor? (compound-slot-descriptor slot-name)))
    (and compound-slot-descriptor?
	 (compound-slot-compound-type compound-slot-descriptor?))))

(defun get-type-of-slot-component-if-any
    (frame slot-name defining-class? slot-component-name? component-indicator?)
  (declare (ignore frame component-indicator?))
  (feature-assq
    'type
    (get-slot-component-features
      slot-name defining-class? slot-component-name?)))


(defun get-slot-component-feature-if-any
    (class slot-name defining-class?
	   slot-component-name slot-component-indicator? feature)
  (declare (ignore class slot-component-indicator?))
  (feature-assq
    feature
    (get-slot-component-features
      slot-name defining-class? slot-component-name)))
	   


;;; `Get-slot-component-value' is the main functional accessor
;;; for slot component-values.  This is only meant to be called
;;; from functions that have validated their arguments.

(defun get-slot-component-value
    (frame slot-name defining-class?
	   slot-component-name? slot-component-indicator?)
  (multiple-value-bind
      (error-status? compound-type-descriptor compound-type-instance slot-of-instance)
      (access-compound-slot-value
	frame slot-name defining-class?
	slot-component-indicator? slot-component-name?)
    (declare (ignore compound-type-descriptor))
    (cond
      ((and (null slot-component-name?)
	    slot-component-indicator?)
       (if error-status?
	   nil
	   compound-type-instance))
      (error-status?
       (handle-compound-slot-value-errors
	 error-status? frame slot-name
	 slot-component-indicator?))
      (t
       (compound-type-instance-component-value
	 compound-type-instance slot-of-instance)))))


;;; `Get-slot-component-value-if-any' is a safer, slower
;;; access for slot component-values than get-slot-component-value
;;; that does not signal errors on bad args. It is meant
;;; to be called from functions such that are basing their
;;; arguments upon user input.

(defun get-slot-component-value-if-any
    (frame slot-name defining-class?
	   slot-component-name slot-component-indicator?)
  (multiple-value-bind		; has-slot-component-p!
      (error-status? compound-type-descriptor
		     compound-type-instance slot-of-instance)
      (access-compound-slot-value
	frame slot-name defining-class?
	slot-component-indicator? slot-component-name)
    (declare (ignore compound-type-descriptor))
    (cond ((and (null slot-component-name)
		slot-component-indicator?)
	   (if error-status? 
	       nil
	       compound-type-instance))
	  (error-status?
	   nil)
	  (t
	   (values
	     (compound-type-instance-component-value
	       compound-type-instance slot-of-instance)
	     t)))))
  
  
  
  
(defun get-compound-slot-value
    (frame slot-name defining-class?
	   slot-component-name slot-component-indicator?)
  (multiple-value-bind
      (error-status? compound-type-descriptor compound-type-instance slot-of-instance)
      (access-compound-slot-value
	frame slot-name defining-class?
	slot-component-indicator? slot-component-name)
    (declare (ignore compound-type-descriptor))
    (cond
      ((and (null slot-component-name)
	    slot-component-indicator?)
       (if error-status?
	   nil
	   compound-type-instance))
      (error-status?
       (handle-compound-slot-value-errors
	 error-status? frame slot-name
	 slot-component-indicator?))
      (t
       (compound-type-instance-component-value
	 compound-type-instance slot-of-instance))))) ; ***

(defun get-current-place-of-component-group (frame slot-name slot-component-indicator?)
  (let ((compound-slot-descriptor (compound-slot-descriptor slot-name))
	(compound-slot-value
	  (get-slot-value frame slot-name nil))) ; defining-class? (!)
    (cond ((compound-slot-multiple-p compound-slot-descriptor)
	   (loop for instance in (multiple-compound-slot-value-real-instances
				   compound-slot-value)
		 as place from 1 by 1
		 when (eql slot-component-indicator?
			   (slot-component-group-indicator instance))
		   return place))
	  (t
	   1))))

;;; `get-slot-component-group' is the exported accessor for individual component groups
;;; of compound slot values.

(defun get-slot-component-group (frame slot-name &optional slot-component-indicator?)
  (let ((compound-slot-descriptor (compound-slot-descriptor slot-name))
	(compound-slot-value
	  (get-slot-value frame slot-name nil))) ; defining-class? (!)
    (cond ((compound-slot-multiple-p compound-slot-descriptor)
	   (loop for instance in (multiple-compound-slot-value-instances
				   compound-slot-value)
		 when (eql slot-component-indicator?
			   (slot-component-group-indicator instance))
		   return instance))
	  (t
	   compound-slot-value))))

(defun denote-slot-component-group (frame slot-name defining-class?
					  slot-component-indicator?)
  (let* ((compound-type (get-compound-slot-compound-type slot-name))
	 (multiplep
	   (is-slot-multiple-compound-slot? slot-name defining-class?))
	 (slot-component-group?
	   (get-slot-component-group
	     frame slot-name slot-component-indicator?))
	 (name-or-names
	   (and slot-component-group?
		(slot-component-group-name-or-names
		  slot-component-group?
		  (component-type slot-component-group?))))
	 (name? (cond ((consp name-or-names)
		       (car name-or-names))
		      (t
		       name-or-names)))
	 (number
	   (loop for component-group being each slot-component-group of
		 (get-slot-value frame slot-name nil)
		 as i from 1 by 1
		 when (eq component-group slot-component-group?)
		   do (return i))))
    (cond
      ((or (null slot-component-group?) 
	   ;; the above can happen at ill-defined in-between states
	   ;; while compiling and putting compound slot values.
	   (null slot-component-indicator?))
       (if multiplep
	   (write-symbol-with-a-or-an compound-type)
	   (tformat "the ~(~a~)" compound-type)))
      (name?
       (tformat "the ~(~a named ~a~)"
		(component-type slot-component-group?) name?))
      (t
       (tformat "~(~a~) #~d"
		(component-type slot-component-group?) number)))))
	   


(def-global-property-name slot-component-putter)
(def-global-property-name slot-component-acknowledger)


(defun get-slot-component-putter-if-any
    (frame slot-name defining-class?
	   slot-component-name? slot-component-indicator?)
  (declare (ignore frame slot-name defining-class? slot-component-indicator?))
  (when slot-component-name?
    (let ((function-place?
	   (slot-component-putter slot-component-name?)))
      (and function-place?
	   (compiled-function-in-place function-place?)))))
	
					; fix to work for ambiguous cases!


(defmacro def-slot-component-putter
	  (slot-component-name (frame-var
				slot-name-var slot-component-indicator-var
				new-value-var
				&optional initialization-case-var?)
	   &body body)
  (let ((putter-name
	  (intern (format nil "PUT-SLOT-COMPOUND-FOR-~A"
			  slot-component-name)))
	(initialization-case-var (or initialization-case-var?
				     (gensym)))
	(defining-class-var (gensym)))
    `(progn
       (declare-function-type ,putter-name (t t t t t t) (t t))
       (defun-into-place (,putter-name
			    (slot-component-putter
			      ',slot-component-name))
	                 (,frame-var
			      ,slot-name-var
			      ,defining-class-var
			      ,slot-component-indicator-var
			      ,new-value-var
			      ,initialization-case-var)
	 (declare (ignore ,defining-class-var
			  ,@(if (null initialization-case-var?)
				`(,initialization-case-var))))
	 ,@body)
;       (setf (slot-component-putter ',slot-component-name) #',putter-name)
       ',putter-name)))

(defmacro def-acknowledge-slot-component-group
	  (slot-name (frame-var slot-component-group-var
				&optional initialization-case-var?)
	   &body body)
  (let ((acknowledger-name
	  (intern (format nil "ACKNOWLEDGE-SLOT-COMPONENT-GROUP-FOR-~A"
			  slot-name)))
	(initialization-case-var (or initialization-case-var?
				     (gensym))))
    `(progn
       (declare-function-type ,acknowledger-name (t t t) (t))
       (defun ,acknowledger-name (,frame-var
				  ,slot-component-group-var
				  ,initialization-case-var)
	 ,@(if (null initialization-case-var?)
	       `((declare (ignore ,initialization-case-var))))
	 ,@body)
       (setf (slot-component-acknowledger ',slot-name)
	     #',acknowledger-name)
       ',acknowledger-name)))

(def-global-property-name cleanup-slot-component-group)

(defmacro def-cleanup-slot-component-group
    (compound-type-name (frame-var slot-name-var slot-component-var)
			&body body)
  (let ((name-for-cleanup-function (build-ab-symbol 'cleanup
						    compound-type-name)))
    `(progn
       (defun ,name-for-cleanup-function
	   (,frame-var ,slot-name-var ,slot-component-var)
	 ,@body)
       (setf (cleanup-slot-component-group ',compound-type-name)
	     #',name-for-cleanup-function))))

(defun set-slot-component-value
    (frame slot-name defining-class?	; EXPORT
	   slot-component-name slot-component-indicator?
	   new-value)
  (default-set-compound-slot-value
      frame slot-name defining-class?
    slot-component-name slot-component-indicator?
    new-value))

(defvar revert-marker (list 'revert))

(defun revert-slot-component-value 
    (frame slot-name defining-class? 
	   slot-component-name slot-component-indicator?)
  (change-slot-value
      frame slot-name revert-marker
      defining-class? slot-component-name slot-component-indicator?))

(defun default-set-compound-slot-value
    (frame slot-name defining-class?
	   slot-component-name slot-component-indicator?
	   new-value)
  (multiple-value-bind
      (error-status? compound-type-descriptor compound-type-instance slot-of-instance)
      (access-compound-slot-value
	frame slot-name defining-class?
	slot-component-indicator? slot-component-name)
    (cond
      ;; New - add a component group case
      ((and slot-component-indicator?
	    (not slot-component-name))
       (let ((master-slot-value
	      (get-slot-value frame slot-name defining-class?))
	     (slot-description (get-slot-description-of-frame
				 slot-name frame)))
	 (when compound-type-instance
	   (set-slot-description-value
	     frame slot-description
	     (delete-slot-value-element
	       compound-type-instance
	       master-slot-value)))
	 (when (and compound-type-instance
		    (not (eq compound-type-instance new-value)))
	   (let ((cleanup-function?
		  (cleanup-slot-component-group
		    (compound-type-name
		      compound-type-descriptor))))
	     (when cleanup-function?
	       (funcall cleanup-function?
			frame slot-name compound-type-instance))))
	 (when new-value
	   (set-slot-description-value
	     frame slot-description
	     (nconc master-slot-value
		    (slot-value-list new-value)))
	   (let ((acknowledger?
		  (slot-component-acknowledger slot-name)))
	     (when acknowledger?
	       (funcall acknowledger? frame new-value nil)))
	   )))
      (error-status?
       (handle-compound-slot-value-errors
	 error-status? frame slot-name
	 slot-component-indicator?))
      (t
;       (let ((compound-slot-descriptor
;	       (compound-slot-descriptor slot-name))
;	     (slot-component-name-for-names compound-type-descriptor))
	 ;; the following conditional blocks changes to
	 ;; the names of objects which are reference defaults
;	 (unless (and (eq slot-component-name slot-component-name-for-names)
;		      (eq 'default
;			  (compound-type-instance-indicator?
;			    compound-type-instance))
;		      (compound-slot-has-reference-default-p
;		        compound-slot-descriptor))
       (cond
	 ((eq new-value revert-marker)
	  (remove-component-group-slot compound-type-instance slot-of-instance))
	 (t
	  (setf (component-group-slot
		  compound-type-instance slot-of-instance)
		new-value)))))))



;;; `Do-slot-components' ... Slot component names are filtered in just the same
;;; way as slot names in terms of user restrictions. They share the same
;;; namespace, in fact.  Just as a restriction on a given slot name, [as of
;;; 2/15/94] applies to all slots with that name, a restriction on a given slot
;;; component name applies to all slot components with that name.

(defmacro do-slot-components ((frame
				slot-name
				defining-class?
				slot-component-indicator?
				&optional 
				  slot-components-to-include?
				  slot-components-to-exclude?
				  exclude-non-editable-slot-components?
				  exclude-restricted-slot-components?)
			      (slot-component-name-var
				&optional alias?-var?
				slot-component-features-var?
				type-of-slot-component-var?
				slot-component-value-var?) ; review order!!
			      &body body)
  (let ((slot-component-features
	  (or slot-component-features-var? '#:slot-features))
	(type-of-slot-component
	  (or type-of-slot-component-var? '#:type-of-slot))
	(alias? (or alias?-var? '#:alias))
	(slot-component-value
	  (or slot-component-value-var? '#:slot-component-value)))
    (avoiding-variable-capture
	(frame slot-name defining-class? slot-component-indicator?
	       slot-components-to-include?
	       slot-components-to-exclude?
	       exclude-non-editable-slot-components?
	       exclude-restricted-slot-components?
	       &aux
	       compound-slot-descriptor compound-type-descriptor
	       compound-slot-value compound-type-instance?
	       slot-component-descriptor)
      `(loop with ,compound-slot-descriptor
	       = (compound-slot-descriptor ,slot-name) ; defining-class? (!)
	     with ,compound-type-descriptor
	        = (compound-type-descriptor
		    (compound-slot-compound-type ,compound-slot-descriptor))
	     with ,compound-slot-value
	       = (get-slot-value ,frame ,slot-name ,defining-class?)
	     with ,compound-type-instance?
  	      = (cond ((null ,compound-slot-descriptor) nil) ; maybe error ??
		      ((compound-slot-multiple-p ,compound-slot-descriptor)
		       (loop for compound-type-instance
				 in (multiple-compound-slot-value-instances
				      ,compound-slot-value)
			     when (eql ,slot-component-indicator?
				       (compound-type-instance-indicator?
					 compound-type-instance))
			       return compound-type-instance))
		      (t
		       ,compound-slot-value))
	     for ,slot-component-descriptor
		in (and ,compound-type-instance?
			(slot-component-descriptors ,compound-type-descriptor))
	      as ,slot-component-name-var
	         = (slot-component-name ,slot-component-descriptor)
	      as ,slot-component-value
	         = (compound-type-instance-component-value
		     ,compound-type-instance? ,slot-component-name-var)
;	     for (,slot-component-name-var ,slot-component-value)
;	        on (and ,compound-type-instance?
;			(compound-type-instance-plist ,compound-type-instance?))
;		 by 'cddr
	     as ,alias?
	         = (get-best-name-for-slot-component
		     ,slot-component-name-var (class ,frame))
;	     as ,slot-component-descriptor
;		in  (slot-component-descriptors ,compound-type-descriptor)
	     as ,slot-component-features
	        = (slot-component-features ,slot-component-descriptor)
	     as ,type-of-slot-component
	        = (feature-assq 'type ,slot-component-features)
	     when (and ,type-of-slot-component
		       (or (not (feature-assq
				  'do-not-put-in-attribute-tables-if-null
				  ,slot-component-features))
			   ,slot-component-value)
		       (category-symbol-given-slot-type
			 ,type-of-slot-component) ; see NOTE 1
		       (or (not (feature-assq
				  'not-editable-in-default
				  ,slot-component-features))
			   (not (feature-assq
				  'do-not-put-in-attribute-tables
				  ,slot-component-features))
			   (not (eq ,slot-component-indicator?
				    'default)))
		       )
	       do (when (and
			  (or (null ,slot-components-to-include?)
			      (memq ,slot-component-name-var
				    ,slot-components-to-include?)
			      (if ,alias?
				  (memq ,alias?
					,slot-components-to-include?)))
			  (or (not ,exclude-restricted-slot-components?)
			      (include-slot-in-attribute-table-p
				,frame (or ,alias? ,slot-component-name-var)
				nil))			    ; Here I assume that all slots with components
							    ; have unique names, hence do not need to be
							    ; qualified with their defining class.
							    ; -fmw, 3/18/94
			  (or (null ,slot-components-to-exclude?)
			      (not
				(or (memq ,slot-component-name-var
					  ,slot-components-to-exclude?)
				    (if ,alias?
					(memq ,alias?
					      ,slot-components-to-exclude?)))))
			  (or (not ,exclude-non-editable-slot-components?)
			      (type-slot-feature-assq-if-editable
				,slot-component-features)))
		    . ,body)))))


(defun add-instance-to-multiple-compound-slot-value
    (frame slot-name defining-class? instance-name-or-instance? &optional name-to-copy?)
  ;; if instance just check that name is good
  ;;    assign number if not
  ;; if name use name-to-copy or defaults
  ;; if nil assign a number and make-defaults
  ;; Q: if name is specified and exists, should this clobber or error?
  ;; A: error for now
  (let* ((desired-name? (if (compound-type-instance-indicator-p instance-name-or-instance?)
			    instance-name-or-instance?
			    (compound-type-instance-indicator? instance-name-or-instance?)))
	 (instance? (if (compound-type-instance-indicator-p instance-name-or-instance?)
			nil
			instance-name-or-instance?))
	 (compound-slot-descriptor? (compound-slot-descriptor slot-name)))
    (unless compound-slot-descriptor?
      (handle-compound-slot-value-errors
	'not-a-compound-slot frame slot-name nil))
    (unless (compound-slot-multiple-p compound-slot-descriptor?)
      (handle-compound-slot-value-errors
	'not-a-multiple-compound-slot frame slot-name nil))
    
    ;; if desired-name is in use, generate an error
    (let* ((compound-slot-value (get-slot-value frame slot-name))
	   (compound-type-instances (multiple-compound-slot-value-instances
				      compound-slot-value))
	   (previously-existing-instance?
	     (and desired-name?
		  (loop for compound-type-instance in compound-type-instances
			do (when (eql desired-name?
				      (compound-type-instance-indicator?
					compound-type-instance))
			     (return compound-type-instance))))))
      (when previously-existing-instance?
	(handle-compound-slot-value-errors
	  'cannot-overwrite-compound-type-instances frame slot-name desired-name?))

      ;; if desired-name is nil, find a new one
      (unless desired-name?
	(setf desired-name? (incff (multiple-compound-slot-value-counter
				    compound-slot-value))))
      
      ;; at this point desired-name? is non-nil and good
      ;; if instance? is nil flesh it out
      ;; if name-to-copy? is non-nil find it and copy it
      ;; if instance for name-to-copy cannot be found, error
      (unless instance?
	(let ((instance-for-name-to-copy?
		(and name-to-copy?
		     (loop for compound-type-instance in compound-type-instances
			   do (when (eql name-to-copy?
					 (compound-type-instance-indicator?
					   compound-type-instance))
				(return compound-type-instance)))))
	      (compound-type-descriptor (compound-type-descriptor
					  (compound-slot-compound-type
					    compound-slot-descriptor?))))
	  (setf instance?
		(if instance-for-name-to-copy?
		    (copy-compound-type-instance
		      compound-type-descriptor
		      instance-for-name-to-copy?)
		    (make-compound-type-instance compound-type-descriptor)))))
      
    ;; put name in instance  & put the instance at the end 
    (setf (compound-type-instance-indicator? instance?) desired-name?)
    (setf (compound-type-instance-master-slot? instance?)
	  (slot-value-list frame slot-name))
    (setf (component-group-slot
	    instance?
	    (slot-component-name-for-names
	      (compound-type-descriptor
		(compound-slot-compound-type
		  compound-slot-descriptor?))))
	  (if (eq desired-name? 'default)
	      'default
	      nil))
;    (setf (multiple-compound-slot-value-instances compound-slot-value)
;	  (nconc
;	    (multiple-compound-slot-value-instances compound-slot-value)
;	    (slot-value-list instance?)))
    ;; to update the world
;    (change-slot-value frame slot-name compound-slot-value)
    (change-slot-value
      frame slot-name instance?
      (or defining-class? (class frame)) ; HACK !
      nil desired-name?)
    instance?)))


(defun make-transient-compound-type-instance (frame slot-name name-or-descriptor)
  (let ((compound-type-instance
	 (make-compound-type-instance name-or-descriptor)))
    (setf (compound-type-instance-master-slot?
	    compound-type-instance)
	  (slot-value-list frame slot-name))
    compound-type-instance))

(defun make-compound-type-instance (name-or-descriptor &optional name-for-instance?)
  (loop with compound-type-descriptor =
	(if (symbolp name-or-descriptor)
	    (compound-type-descriptor name-or-descriptor)
	    name-or-descriptor)
	with compound-type-instance = '()
	for slot-component-descriptor
	    in (slot-component-descriptors compound-type-descriptor)
	 as slot-component-name = (slot-component-name
					slot-component-descriptor)
	 as slot-component-initform = (slot-component-initform
					    slot-component-descriptor)
	 as slot-component-subtype = (cadr (feature-assq
						  'subtype
						  (slot-component-features
						    slot-component-descriptor)))
	do
          (case slot-component-subtype
	    (component-type		; "class/class-header"-like
	     (slot-value-push slot-component-name compound-type-instance)
	     (slot-value-push
	       (compound-type-name compound-type-descriptor)
	       compound-type-instance))
	    (otherwise
	     (when (or (eq slot-component-subtype 'internal)
		       (and (consp slot-component-initform)
			    (eq (car slot-component-initform) :funcall)))
	       (slot-value-push slot-component-name compound-type-instance)
	       (slot-value-push
		 (eval-slot-init-form slot-component-initform)
		 compound-type-instance))))
	finally
	  (return
	    ;; add the name/number of instance to head
	    (slot-value-cons
	      (if (compound-type-instances-are-named-p compound-type-descriptor)
		  name-for-instance?
		  nil)
	      (slot-value-cons
		nil
		(nreverse compound-type-instance))))))

(defun copy-compound-type-instance (compound-type-descriptor compound-type-instance)
  ;; we ignore this now because the represention of compound-type instances
  ;; is just (name . a-list)
  (declare (ignore compound-type-descriptor))
  (loop with copy = (car compound-type-instance)
	for (key value . tail) on (compound-type-instance-plist
				   compound-type-instance) by 'cddr 
	do
          (slot-value-push key copy)
	  (slot-value-push nil copy)
	  (slot-value-push (cond ((compound-slot-descriptor-p value) ; only shared slot
				  value)                             ; is descriptor
				 (t
				  (copy-for-slot-value value)))
			   copy)
	finally
	  (return (nreverse copy))))
			
;; used in COMMANDS2:

(defun remove-instance-from-multiple-compound-slot-value
    (frame slot-name defining-class? slot-component-group-or-indicator)
  ;; if fixnum or symbol, the last arg is an instance name
  (let ((compound-slot-descriptor? (compound-slot-descriptor slot-name))
        (compound-slot-value (get-slot-value frame slot-name defining-class?))
        (current-block-of-dependent-frame frame))
    (cond
      ((and compound-slot-descriptor?
	    (compound-slot-multiple-p
	      compound-slot-descriptor?)
	    (let ((indicator
		    (if (compound-type-instance-indicator-p
			  slot-component-group-or-indicator)
			slot-component-group-or-indicator
			(compound-type-instance-indicator?
			  slot-component-group-or-indicator))))
	      (or (eq indicator 'default)
		  (and
		    (compound-slot-has-at-least-one-instance-p
		      compound-slot-descriptor?)
		    (=f (length (multiple-compound-slot-value-instances
				  compound-slot-value))
			2)))))
       nil) ; default is not deletable in this case
      (compound-slot-descriptor?
       (loop with slot-component-indicator
             =  (if (compound-type-instance-indicator-p
                      slot-component-group-or-indicator)
                    slot-component-group-or-indicator
                    (compound-type-instance-indicator?
                      slot-component-group-or-indicator))
             for instance in (multiple-compound-slot-value-instances
                               compound-slot-value)
	     when (eql slot-component-indicator
		       (compound-type-instance-indicator? instance))
               do
		 (remove-representations-of-slot-component-group
		   frame slot-name defining-class? slot-component-indicator)
		 (change-slot-value
		   frame slot-name
		   nil
		   defining-class?
		   nil
		   slot-component-indicator)
		 ;; GENSYMCID-1066: Trend-chart get unexpected notes after delete plot.
		 (check-consistency-analysis frame)
		 (return)))
      (t
       (handle-compound-slot-value-errors
         'not-a-compound-slot frame slot-name nil)))))

(def-global-property-name slot-component-reclaimer)

;; def-slot-value-reclaimer
(defmacro def-slot-component-value-reclaimer
	  (slot-component-name (slot-value-var . listed-frame-var) &body body)
  (let ((name (intern (format nil "RECLAIM-~A-COMPOUND-SLOT-VALUE"
			      slot-component-name)))
	(frame-var (if listed-frame-var (car listed-frame-var) (gensym))))
    `(progn
       (defun ,name (,slot-value-var ,frame-var)
	 ,@(if (null listed-frame-var) `((declare (ignore ,frame-var))))
	 . ,body)
       (setf (slot-component-reclaimer ',slot-component-name) #',name)
       ',name)))

#+unused
(defun reclaim-compound-type-instance-slot (frame
					     compound-type-descriptor
					     compound-type-instance
					     slot-name-of-instance)
  (declare (ignore compound-type-descriptor))
  (unless (eq slot-name-of-instance 'component-type)
    (let ((special-reclaimer? (slot-component-reclaimer slot-name-of-instance))
	  (value
	    (component-group-slot
	      compound-type-instance slot-name-of-instance)))
      (if special-reclaimer?
	  (funcall special-reclaimer? value frame)
	  (reclaim-slot-value value)))))

(defun reclaim-compound-type-instance (frame
					compound-type-descriptor
					compound-type-instance)
  (declare (ignore compound-type-descriptor))
  ;; loop like the above function on all slots
  ;; then remove the spine
  (loop for (slot-name value . nil)
	on (compound-type-instance-plist compound-type-instance)
	    by 'cddr
	do
          (let ((special-reclaimer?
		  (slot-component-reclaimer slot-name)))
	    (if special-reclaimer?
		(funcall special-reclaimer? value frame)
		(reclaim-slot-value value)))
	finally
	  (reclaim-slot-value-list
	    (compound-type-instance-master-slot? compound-type-instance))
	  (reclaim-slot-value-list compound-type-instance)))


(defun handle-compound-slot-value-errors (error-status frame slot-name info)
  (ecase error-status
    (not-a-compound-slot
     (compound-slot-value-error
       "Attribute ~s of ~s does not have a compound value"
       slot-name frame))
    (not-a-multiple-compound-slot
     (compound-slot-value-error
       "Attribte ~s of ~s does not have a multiple compound value"
       slot-name frame))
    (bad-path
     (compound-slot-value-error
       "Bad Indicator ~s while retrieving value from attribute ~s of ~s"
       info slot-name frame))
    (no-compound-type-instance-for-name
     (compound-slot-value-error
       "Could not find compound value for name ~s in attribute ~s of ~s"
       info slot-name frame))
    (cannot-overwrite-compound-type-instances
     (compound-slot-value-error
       "Cannot overwrite existing instance for name ~a in attribute ~s of ~s"
       info slot-name frame))))


;;; `access-compound-slot-value' is the primitive from which the get- and
;;; changes functions are built.  It returns four values:
;;;
;;; error-status? -- one-of (bad-path, not-a-compound-slot,
;;;                          no-compound-type-instance-for-name, or nil)
;;; compound-type-descriptor -- verified to be good if error-status? is nil 
;;; compound-type-instance --   ditto
;;; slot-component-name --  same here

(defun access-compound-slot-value
    (frame slot-name defining-class? name-of-instance? slot-of-instance?)
  (declare (ignore defining-class?))	; will be used later, when slot descriptor is
					;   on the type feature of the slot! (MHD)
  (let ((compound-slot-descriptor? (compound-slot-descriptor slot-name))
	(compound-slot-value (get-slot-value frame slot-name)))
    (cond
      (compound-slot-descriptor?
       (let* ((path-is-good-p t)
	      (compound-type-descriptor (compound-type-descriptor
					  (compound-slot-compound-type
					    compound-slot-descriptor?)))
	      (compound-type-instance? 
		(cond
		  ((compound-slot-multiple-p compound-slot-descriptor?)
		   (cond
		     ((and name-of-instance?
			   (compound-type-instance-indicator-p name-of-instance?))
		      (loop for cti
				in (multiple-compound-slot-value-instances
				     compound-slot-value)
			    as name-of-cti = (compound-type-instance-indicator? cti)
			    do (when (eql name-of-cti name-of-instance?)
				 (return cti))))
		     (t
		      (setf path-is-good-p nil))))
		  (t
		   compound-slot-value)))
	      (slot-of-instance
		(cond ((and slot-of-instance?
			    (symbolp slot-of-instance?)
			    (compound-type-has-slot-p compound-type-descriptor
						      slot-of-instance?))
		       slot-of-instance?)
		      ((null slot-of-instance?)
		       nil)
		      (t
		       (setf path-is-good-p nil)))))
	 (cond ((not path-is-good-p)
		(values 'bad-path nil nil nil))
	       ((not compound-type-instance?)
		(values 'no-compound-type-instance-for-name nil nil nil))
	       (t
		(values nil compound-type-descriptor
			compound-type-instance? slot-of-instance)))))
      (t
       (values 'not-a-compound-slot nil nil nil)))))

      

;; We don't need the following functions if good initforms can be generated
;; for the compound-slots of the classes that use 'em.

(defun make-frame-using-compound-types (class-name) ; EXPORTED
  (let ((frame (make-frame class-name)))
    ;; loop over slots with compound types
    ;; make-default-instances where necessary

    ;; I changed "class-name" to "'trend-chart" to get the compound-slots-
    ;; for class because only a def-class form for a system-defined class
    ;; bestows them.  (ghw 1/9/96)
    (loop for compound-slot-name in (compound-slots-for-class 'trend-chart)
	  do
      (initialize-compound-slot-value frame compound-slot-name))
    frame))


;; wednesday
;; - slot-value writers and control variable
;;    remember the default (i.e. big and hairy) writer
;; - circularity in slot-putter (initialize)
;; - testing
;; - add "no-any-defaulting" feature for things like expression of plot
;;   or to plot object itself

;; Compiler:
;; 1 normalize list of triples (slot-component-name value component-group-ref)
;; 2 sort transforms by component-group-ref (nb:  foo named 'default = any foo)
;;   aborting with bad-phrase on multiple specification
;;   put default/only first
;; 3 wrap up result as (multiple/single (name . transform*)*)
;;   with name being `any or nil components


(defvar current-component-type-for-sorting nil)

(defun compile-compound-slot-value (parse-result frame slot-name
						 component-type-name multiple-p)
  (let (annotations sorted-transforms component-group-count
		    number-name-pairs)
    (cond
      (multiple-p
       (let* ((header (car parse-result))
	      (names-spec (cadr header)))
	 (setf annotations (cadr parse-result))
	 (setf number-name-pairs
	       (cond
		 ((and (consp names-spec)
		       (eq (car names-spec) '\,))
		  (cdr names-spec))
		 ((null names-spec)
		  nil)
		 (t
		  (phrase-list names-spec))))
	 (setf component-group-count (car header))
	 (loop with compound-type-descriptor =
	       (compound-type-descriptor component-type-name)
	       for i from 1 to component-group-count
	       as name? =  (cadr (assoc-eql i number-name-pairs))
	       do
	   (cond
	     (name?
	      (phrase-push
		(phrase-list i name?
			     (phrase-list
			       (slot-component-name-for-names
				 compound-type-descriptor)
			       name?))
		sorted-transforms))
	     (t
	      (phrase-push (phrase-list i nil) sorted-transforms)))
	       finally
		 (setq sorted-transforms
		       (phrase-cons (phrase-list 0 'default)
				    (nreverse sorted-transforms))))))
      (t
       (setf annotations (cadr parse-result))
       (setf sorted-transforms (phrase-list (phrase-list 0 'only)))))
    (loop for (number name) in number-name-pairs
	  unless (<=f 1 number component-group-count)
	    do
	      (return-from
		compile-compound-slot-value
		(values bad-phrase
			(tformat-text-string "The ~(~a~) number ~d is out of range"
					     component-type-name number))))
    (loop with annotation-list
	  = (cond ((and (consp annotations)
		     (eq (car annotations) '\;))
		   (cdr annotations))
		  (annotations
		   (phrase-list annotations))
		  (t
		   nil))
	  for annotation
	      in annotation-list
	  as (slot-component-name value (reference-type reference-index))
	     = annotation
	  as indicator = 
	     (case reference-type
	       (single
		0)
	       (any
		0)
	       (numbered
		(when (<=f 1 reference-index component-group-count)
		  reference-index))
	       (named
		(loop for (number name) in number-name-pairs
		      when (progn
;			     (format t "Name=~s number=~s ref-idx=~s~%"
;				     name number reference-index)
			     (eq name reference-index))
			do (return number))))
	  as annotations-for-group? = (and indicator
					  (assoc-eql indicator sorted-transforms))
	  do
            (cond
	      ((null indicator)
	       (return
		 (values bad-phrase
			 (twith-output-to-text-string
			   (tformat "The ~(~a~) number ~d is out of range"
				    component-type-name reference-index)))))
	      ((and annotations-for-group?
		    (assq slot-component-name (cddr annotations-for-group?)))
	       (return
		 (values bad-phrase
			 (twith-output-to-text-string
			   (tformat "Multiple specification given for ~(~a~)"
				    slot-component-name)))))
	      (annotations-for-group?
	       (phrase-push annotation (cddr annotations-for-group?)))
;	       (multiple-value-bind (success-p compiled-annotation-or-complaint)
;		   (compile-compound-slot-annotation
;		     annotation frame slot-name component-type-name)
;		 (cond (success-p
;			(phrase-push compiled-annotation-or-complaint
;				     (cddr annotations-for-group?)))
;		       (t
;			(values bad-phrase compiled-annotation-or-complaint)))))
	      (t
	       (error "Obsolete case")
	       (phrase-push (phrase-cons indicator annotation)
			    sorted-transforms)))
	  finally
	    (loop for uncompiled-group in sorted-transforms
		  as (indicator name . annotations-for-group)
		  = uncompiled-group
		  do
	      (let ((current-component-type-for-sorting
		     component-type-name))
		(setf (cddr uncompiled-group)
		      (sort-list annotations-for-group 'slot-component-name<
				 'car))))
	    (multiple-value-bind (compiled-annotations-or-bad-phrase
				  complaint?)
		(compile-sorted-annotations
		  sorted-transforms frame slot-name component-type-name)
	      (return
		(if (eq compiled-annotations-or-bad-phrase bad-phrase)
		    (values bad-phrase complaint?)
		    (phrase-cons
		      (if multiple-p 'multiple 'single)
		      compiled-annotations-or-bad-phrase)))))))

;; note that for multiple compound slot values the
;; transform groups (0 default . annotation*) is guaranteed to be first

(defun slot-component-name< (slot-component-name-1 slot-component-name-2)
  (let* ((compound-type-name current-component-type-for-sorting))
    (loop for slot-component-descriptor
	      in (slot-component-descriptors
		   (compound-type-descriptor compound-type-name))
	  as slot-component-name =
	     (slot-component-name slot-component-descriptor)
	  do
      (cond
	((eq slot-component-name slot-component-name-1)
	 (return t))
	((eq slot-component-name slot-component-name-2)
	 (return nil)))
	  finally
	    (return nil))))

(defun compile-sorted-annotations (sorted-annotations
				   frame slot-name component-type-name)
  (loop with default-component-group? = nil
        for (indicator name . annotations-for-group)
	    in sorted-annotations
	collect
	(loop with temporary-component-group =
	      (make-transient-compound-type-instance
		frame slot-name component-type-name)
	      with compiled-annotations-for-group = '()
	      for annotation in annotations-for-group
	      do
	  (when default-component-group?
	    ;; set up defaults if not present in current group
	    (add-defaults-to-component-group
	      temporary-component-group
	      default-component-group?)
	    )
	  (multiple-value-bind (success-p compiled-annotation-or-complaint)
	      (compile-compound-slot-annotation
		annotation frame slot-name component-type-name
		temporary-component-group)
	    (cond (success-p
		   ;; GENSYMCID-1166: G2 2011 October 2013 g2-set-text-of-trend-chart-component crash
		   (reclaim-slot-value
			 (component-group-slot
			   temporary-component-group (car annotation)))
		   (setf (component-group-slot
			   temporary-component-group (car annotation))
			 (copy-for-slot-value
			   (cadr compiled-annotation-or-complaint)))
		   (phrase-push compiled-annotation-or-complaint
				compiled-annotations-for-group))
		  (t
		   (reclaim-slot-value temporary-component-group)
		   (reclaim-slot-value default-component-group?)
		   (return-from compile-sorted-annotations
		     (values bad-phrase compiled-annotation-or-complaint)))))
	      finally
		(cond ((eq name 'default)
		       (setf default-component-group? temporary-component-group))
		      (t
		       (reclaim-slot-value temporary-component-group)))
	        (return (phrase-cons
			  indicator
			  (phrase-cons name compiled-annotations-for-group))))
	using phrase-cons
	finally
	  (reclaim-slot-value default-component-group?)))

(defun add-defaults-to-component-group
    (real-component-group default-component-group)
  (loop for tail on (compound-type-instance-plist default-component-group)
		 by 'cddr
	as (slot-component-name value . nil) = tail
	do
    (when (eq compound-type-slot-not-present
	      (component-group-slot
		real-component-group
		slot-component-name
		compound-type-slot-not-present))
      (setf (component-group-slot
	      real-component-group slot-component-name)
	    (copy-for-slot-value value)))))
	      
(defvar leak-list nil)

(defun compile-compound-slot-annotation (annotation frame slot-name compound-type-name
						    temporary-component-group)
  (let* ((slot-component-name (car annotation))
	 (slot-component-descriptor
	  (loop for slot-component-descriptor
		    in (slot-component-descriptors
			 (compound-type-descriptor compound-type-name))
		when (eq (slot-component-name slot-component-descriptor)
			 slot-component-name)
		  do (return slot-component-descriptor)))
	 (slot-component-features
	  (slot-component-features slot-component-descriptor))
	 (type-spec?
	  (feature-assq 'type slot-component-features))
	 (text-slot-type-p
	   (and type-spec? (text-slot-type-p type-spec?)))
	 (category?
	  (category-symbol-given-slot-type type-spec?))
	 (uncompiled-value
	   (if nil ; text-slot-type-p -- someday, when the world is kind, gentle and orthogonal
	       (caadr annotation)
	       (cadr annotation)))
	 (slot-value-compiler?
	  (and category? (not (eq category? 'free))
	       (slot-value-compiler category?))))
;    (loop for i from 0 to 100 do (slot-value-push (car type-spec?) leak-list))
    (multiple-value-bind (compiled-value-or-bad-phrase complaint)
	(if (or (null slot-value-compiler?)
		(eq bad-phrase uncompiled-value))
	    uncompiled-value
	    (funcall-compiled-function
	      slot-value-compiler? uncompiled-value frame slot-name
	      nil slot-component-name temporary-component-group))
      (cond ((eq compiled-value-or-bad-phrase bad-phrase)
	     (values nil complaint))
	    (text-slot-type-p
	     (values
	       t
	       (phrase-list
		 slot-component-name
		 (phrase-cons 
		   (if (eq category? 'free)
		       no-value
		       compiled-value-or-bad-phrase)
		   (let ((text-string
			   (twith-output-to-text-string
			     (if (eq category? 'free)
				 (tformat "Free Text Not Supported Yet")
				 (if (eq slot-component-name 'plot-expression)
				     ;; What we don't want to happen:
				     ;; A symbol such as x@(y@) in the plot
				     ;; expression of a trend chart would
				     ;; otherwise get converted upon recompilation,
				     ;; first into x(y), then into call-function(x,y),
				     ;; causing G2 to signal an error. - JPG 12/04/00
				     (let ((write-symbols-parsably? t))
				       (tformat "~NE" uncompiled-value))
				     (tformat "~NE" uncompiled-value))))))
		     (prog1
			 (phrase-list
			   (make-lost-spaces-phrase-text-element 0)
			   (copy-for-phrase text-string))
		       (reclaim-text-string text-string)))))))
	    (t
	     (values t (phrase-list
			 slot-component-name
			 compiled-value-or-bad-phrase)))))))

;; what about consing and noting changes (ask MHD) !!

;; Putter:
;; 1 clear the old-value
;;   by using initialize 
;; 2 add un-specialized instances
;;   by using add-instance
;; 3 put "any" specializations in
;;   csv for components
;; 4 put "instance" specializations in
;;   csv for components

(defun put-compound-slot-value (frame slot-name value &optional class-if-specific?)
  (let* (;(slot-description (get-slot-description-of-frame
					;		    slot-name frame))
					;(value-type (car value))
	 (compound-slot-descriptor
	   (compound-slot-descriptor slot-name))
	 (compound-type-name
	   (compound-slot-compound-type compound-slot-descriptor))
	 (cleanup-function?
	   (cleanup-slot-component-group compound-type-name))
	 (compound-type-descriptor
	   (compound-type-descriptor compound-type-name))
	 (value-specs-for-groups (cdr value))
	 (slot-value (get-slot-value frame slot-name class-if-specific?)))
    (reclaim-slot-value-cons value)
    
    ;; get rid of representations and call cleanup "methods" on components
    ;; and delete the components themselves.  The slot-value that points
    ;; at all this deleted stuff is cleaned up next.
    (cond
      ((compound-slot-multiple-p compound-slot-descriptor)
       (loop with component-groups
	       = (nreverse ; delete defaults last
		   (copy-list-using-gensym-conses
		     (multiple-compound-slot-value-instances slot-value)))
	     for component-group in component-groups
	     do
	 (remove-representations-of-slot-component-group
	   frame slot-name class-if-specific?
	   (slot-component-group-indicator component-group))
	 (when cleanup-function?
	   (funcall cleanup-function?
		    frame slot-name component-group))
	 (reclaim-compound-type-instance
	   frame compound-type-descriptor component-group)
	 ;; cut pointers to deleted components one by one
	 (setf (multiple-compound-slot-value-instances slot-value)
	       (delete-slot-value-element
		 component-group 
		 (multiple-compound-slot-value-instances slot-value)))
	 (decff (multiple-compound-slot-value-counter slot-value))
	     finally
	       (reclaim-gensym-list component-groups)
	       (reclaim-slot-value-list slot-value)))
      (t
       (remove-representations-of-slot-component-group
	 frame slot-name class-if-specific?
	 (slot-component-group-indicator slot-value))
       (when cleanup-function?
	 (funcall cleanup-function?
		  frame slot-name slot-value))
       (reclaim-compound-type-instance frame compound-type-descriptor slot-value)
       ))

    ;; initializing really get rid of slot-value 
    (set-slot-value frame slot-name nil nil)
    
    (initialize-compound-slot-value
      frame slot-name)
    ;; the following loop ensures that all new component
    ;; groups created here have some chance of being acknowledged
    ;; by the owning frame
    (let ((acknowledger?
	    (slot-component-acknowledger slot-name)))
      (when acknowledger?
	(cond
	  ((compound-slot-multiple-p compound-slot-descriptor)
	   (loop for component-group
		     in
		 (multiple-compound-slot-value-real-instances
		   (get-slot-value frame slot-name class-if-specific?))
		 do
	     (funcall acknowledger? frame component-group nil)))
	  (t
	   (funcall acknowledger?
		    frame
		    (get-slot-value frame slot-name class-if-specific?)
		    nil)))))

    (loop for value-specs-for-group
	      in value-specs-for-groups
	   as (number name . transforms)
	      = value-specs-for-group
	   as indicator
	      = (cond ((or (eq name 'default)
			   (eq name 'only))
		       name)
		      ((and (compound-slot-has-at-least-one-instance-p
			      compound-slot-descriptor)
			    (=f number 1))
		       (slot-component-group-indicator
			 (car (multiple-compound-slot-value-real-instances
				(get-slot-value frame slot-name)))))
		      (t
		       (slot-component-group-indicator
			 (add-instance-to-multiple-compound-slot-value
			   frame slot-name nil nil))))
	  do
	    (loop for transform in transforms
		   as (slot-component-name new-value)
		      = transform
		  do
	      (change-slot-value
		frame slot-name new-value
		class-if-specific?
		slot-component-name indicator)
	      (reclaim-slot-value-list transform))
	    (reclaim-slot-value-list value-specs-for-group)
	  finally
	    (reclaim-slot-value-list value-specs-for-groups)))
  (values nil t))


(defun write-multiple-compound-slot-value (frame slot-value compound-type-name)
  (write-multiple-compound-slot-value-header slot-value compound-type-name)
  (let ((component-groups
	 (component-groups-for-compound-slot-value slot-value))
	(compound-type-descriptor (compound-type-descriptor
				    compound-type-name))
	(first-component-group-p nil))
    (loop for component-group in component-groups
	  when (eq (slot-component-group-indicator component-group)
		   'default)
	    do
	      (write-component-group
		frame component-group compound-type-descriptor 'any
		first-component-group-p)
	      (setf first-component-group-p nil)
	      (return))
    (loop with count = 0
          for component-group in component-groups
	   as indicator? = (slot-component-group-indicator component-group)
	   as name?
	      = (let ((names? (slot-component-group-name-or-names
				component-group compound-type-name)))
		  (if (consp names?) (car names?) names?))
	  unless (eq indicator? 'default)
	    do
	      (incff count)
	      (write-component-group
		frame
		component-group
		compound-type-descriptor
		(or name? count)
		first-component-group-p)
	      (setf first-component-group-p nil))))

(defun write-multiple-compound-slot-value-header (slot-value compound-type-name)
  (let ((component-groups
	 (component-groups-for-compound-slot-value slot-value)))
    (write-component-group-count slot-value compound-type-name)
    (loop with first-p = t
	  with count = 0
          for component-group in component-groups
	  as name?
	     = (let ((names? (slot-component-group-name-or-names
			       component-group compound-type-name)))
		 (if (consp names?) (car names?) names?))
	  when (and name?
		    (not (eq (slot-component-group-indicator
			       component-group)
			     'default)))
            do
	      (cond
		(first-p
		 (setq first-p nil)
		 (tformat ":  "))
		(t
		 (tformat ", ")))
	      (incf count)
	      (tformat "~(~a~) ~d named ~(~a~)"
		       compound-type-name count name?))))

(defun write-single-compound-slot-value (frame slot-value compound-type-name)
  (tformat "a ~(~s~)" compound-type-name)
  (write-component-group
    frame
    slot-value
    (compound-type-descriptor compound-type-name)
    nil nil))

(defun write-component-group (frame component-group
				    compound-type-descriptor name-or-number?
				    first-component-group-p)
  (loop with compound-type-name
	     = (compound-type-name compound-type-descriptor)
	with first-p = t
	with slot-component-name-for-names
	     = (slot-component-name-for-names compound-type-descriptor)
        for slot-component-descriptor
	    in (slot-component-descriptors compound-type-descriptor)
	 as slot-component-name = (slot-component-name slot-component-descriptor)
	 as best-slot-component-name
	    = (get-best-name-for-slot-component
		slot-component-name (class frame))
	 as slot-component-features = (slot-component-features
					slot-component-descriptor)
	 as type-spec? = (feature-assq 'type slot-component-features)
	 as category? = (and type-spec? (cadr type-spec?))
	 as subtype = (cadr (feature-assq 'subtype slot-component-features))
	 as slot-component-value?
	    = (component-group-slot component-group slot-component-name
				    compound-type-slot-not-present)
	when (and (not (eq slot-component-value? compound-type-slot-not-present))
		  (not (eq slot-component-name-for-names
			   slot-component-name))
		  (memq subtype '(definition type reference)))
	  do
	    ;; write lhs
	    (cond
	      (first-p
	       (unless first-component-group-p
		 (tformat ";~%"))
	       (setf first-p nil))
	      (t
	       (tformat ";~%")))
	    (cond
	      ((eq name-or-number? 'any)
	       (tformat
		 "the ~(~a~) of any ~(~a~)"
		 best-slot-component-name
		 compound-type-name))
	      ((and name-or-number? (symbolp name-or-number?))
	       (tformat
		 "the ~(~a~) of the ~(~a~) named ~a"
		 best-slot-component-name
		 compound-type-name
		 name-or-number?))
	      (name-or-number?
	       (tformat
		 "the ~(~a~) of ~(~a~) ~d"
		 best-slot-component-name
		 compound-type-name
		 name-or-number?))
	      (t
	       (tformat "the ~(~a~)"
			best-slot-component-name)))
	    ;; write equating symbol based on category
	    (if (self-evaluating-category? category?)
		(tformat " = ")
		(tformat " is "))
	    ;; write component-value using the category's method
	    (cond ((eq (caddr type-spec?) 'text)
		   (cond
		     (slot-component-value?
		      (let ((temp-string
			     (convert-text-to-text-string
			       (cdr slot-component-value?))))
			(tformat "~a" temp-string)
			(reclaim-text-string temp-string)))
		     (t
		      (tformat "[No Printable Value]"))))
		  (t
		   (write-slot-value
		     category? slot-component-value? frame)))))
;	    (make-text-representation-for-slot-value-itself
;		   frame slot-component-value? type-spec?)))



;;; The property `denotation-for-compound' for compound-type exists so
;;; so that eventually menu choices and the default-slot-value-writer-
;;; for-compound-types can do there jobs better, with more specific names
;;; for the components in question.
  
(def-global-property-name denotation-for-compound-type)

(defun write-component-group-count (slot-value compound-type-name)
  (let ((writer-info? (compound-slot-value-writer-info
			compound-type-name)))
    (cond
      (writer-info?
       (let* ((components (multiple-compound-slot-value-real-instances slot-value))
	      (number (length components))
	      (slot-name (car writer-info?))
	      (name (or (cadr writer-info?) compound-type-name))
	      (plural-name? (caddr writer-info?)))
	 (if (compound-slot-multiple-p
	       (compound-slot-descriptor slot-name)) ; see note
	     (tformat
	       "~(~d ~a~a~)"
	       number
	       (or (if (=f number 1) name)
		   plural-name?
		   name)
	       (if (or (=f number 1) plural-name?)
		   ""
		   "s"))
	     (tformat
	       "~(~a~a~)"
	       (supply-a-or-an name)
	       name))))
      (t
       (tformat "must define writer for compound type ~a"
		compound-type-name)))))

;; Note: the value of this may not be known until load time, although it never
;; changes at runtime.  Testing a runtime is therefore more convenient for us at
;; the expense, negligable, of a bit of extra code space, and an extra runtime
;; test.
;; 

;; needed functionality:

;; run-time data-structure decisions (incl slot-value-cons vs. phrase-cons)
;; menus for classes-using-ct's
;; ui-command for making the attribute-table in question
;; ui-command for delete
;; menus for attrs-of-classes using ct's
;; how do we do value defaults (if at all)
;;  (default instances are relatively easy)
;; leave room for specialized slot value reclaimers
;; default-compound-slot-value-compiler
;; default-compound-slot-value-writer
;; analyze-for-consistency compatibility
;; name slots and standard integrity checker/frame note generator for
;;  all slot putters





;; Compound Slots - Miscellany 


;; NOTE: MISCELLANEOUS CHANGES for this facility: edit interface, tables
;; interface, menus interface, kb-state-changes interface (to note the changes
;; text for restoral upon reset), user-restrictions interface.  And
;; change-slot-value.
;;
;; tbd: fix note-kb-state-change-to-slot-by-saving-text and
;; note-change-of-text-slot and undo-kb-state-changes-for-frame!!!  They must
;; handle saving text keyed by slot-component name and indicator in addition to
;; slot name. This is needed only once you can do runtime changes to slot
;; components via "change the text of".  (MHD 1/21/94)
;;
;; tbd: implement get-slot-component-feature-if-any!! (JED)
;;
;; 
;; Compilers are not being changed not to take the component name and indicator.
;; That's not needed now -- could be done later, but would require fixing the
;; arglist generated for the compilers by def-slot-value-compiler, which wouldn't
;; be very hard. (MHD 1/27/94)
;; 
;; -- UPDATE: The extra defining-class? arg has been threaded through the
;; def-slot-value-compiler mechanism; it should now be threaded through
;; this facility.  One year later ... (MHD 1/13/95)
;; 
;;
;; tbd: implement get-slot-component-putter-if-any for real if needed!
;;
;; tbd: update-representations!! (MHD)
;;
;; JED: - Fixed up the makers a bit -- use constructors, but leave in the functional
;; interface in case you want to change it later.
;; 
;; - documented structures defined
;; 
;; - systematically changed compound-type-slot-descriptor to slot-component-descriptor
;;
;; - systematically change compound-type-slot to slot-component
;;
;; (10/31/94)
;; - systematically change component-slot-name to slot-component-name
;;
;; 
;; 
;; - changed "sub-" to "sub", i.e., sub-type -> subtype.  Note that this is the
;; convention we follow (subclass, subblock, etc.) generally.
  





;;;; Gross Grammar Access to Compound Slots



;;; A compound slot can be viewed as a regular slot, i.e., have its own grammar,
;;; writer, compiler, etc., and have a change-text-of/get-text-of interface.
;;; This grammar is referred to as its `gross grammar'.
;;;
;;; An additional goal of the gross grammar is to be compatible with
;;; annotations, the UI to the parts facility, used in G2 charts and
;;; freeform tables.
;;;
;;; The initial discussion below focuses on examples, and deals primarily with
;;; issues around making the gross grammar compatible with the annotations
;;; grammar.  Following this section is a formal description of the gross
;;; grammar.
;;; 
;;;
;;; Compound-slot writers and grammars are automatically generated from the
;;; compound-slot description.  Examples of the kind of language accepted
;;; by these automatically generated grammars:
;;;
;;; For the plots slot of a trend-chart:
;;;
;;; NEW EXAMPLES:  (for unification with annotations)
;;;
;;; This would be a PLOTS compound slot:
;;;
;;;   the use-variable-history of the
;;;     plot named temperature
;;;     is yes;
;;;
;;; Note the use of the keyword NAMED.  This is intended to be useable
;;; ultimately for parts.  Viewed in this way, they are compatible with
;;; parts.
;;;
;;; Note that the word "yes" follows is.  For analagous slots, charts use
;;; "true".  This superficial difference is only due to the fact that trend
;;; charts use the grammar category yes-or-no, whereas charts use the grammar
;;; category boolean.  This should be fixed, if at all, not at this level, but
;;; by changing the grammar catogory.  One or the other could use one or the
;;; others' grammar.  Or, one or both of the could both accept either grammar.
;;; Various other grammars are different between users of annotations (charts)
;;; and users of compound slots (trend charts).  For example, the plot marker
;;; grammar for trend charts vs. the indicator grammar for charts.  But that's
;;; not being considered here because it's not relevant to the unification of
;;; parts and compound slots.  (It is relevant to the unification of charts
;;; and trend charts.)
;;;
;;; While we're on the topic, another thing that is different between charts and
;;; trend charts, but not owing to one using annotations where the other uses
;;; compound slots, is the names of parts vs. the names of slot components and
;;; slot component groups.  For example, a chart has a part called "axis".  A
;;; trend chart has no slot component groups called "axis", but it does have
;;; slot component groups called "time axis" and "value axis".  Again, that's
;;; not relevant to this discussion, but might be relevant to the set of issues
;;; around unifying those two particular customers of these facilities.  (I.e.,
;;; these same differences could have been brought about with both using parts
;;; or both using compound slots.)
;;;
;;; Note that the word IS appears between the name of the left side of the
;;; equation (the use-variable-history of the plat named temperature) and the
;;; right side (yes).  For all subgrammars that are not among a select list of
;;; "self-evaluating" types (numbers or strings), IS is used.  For the self-
;;; evaluating subgrammars, = is used.  This is roughly compatible with
;;; annotations/charts.  It's not clear whether charts' use of is/= is
;;; compatible with use of is/= in the general G2 language, i.e., the conclude
;;; action.  There, IS is used to "quote" (inhibit evaluation of0 the right-hand
;;; side, and = is used to call for the evaluation of the right hand side.
;;; The reason it's ambiguous is that in charts, none of the right-hand sides
;;; of annotations are ever really evaluated, but, if they could be, then the
;;; ones that follow an = sign would evaluate to themselves anyway.
;;;
;;;   the expression of plot 1 is sin (the current time / 50) * 20
;;;
;;; This is completely compatible with parts.  (We would like to denigrate the
;;; use of such references in most cases as leading to a bad programming style
;;; (on the part of users), that is, numerical vs. named referencing, but we can
;;; support it all the same.  Annotations only have the numerical referencing,
;;; which is better than nothing, but will also want to be supplemented by the
;;; named referencing in the compound slots facility.)
;;;
;;;
;;; This would be in a time-axis compound slot:
;;;
;;;   the data-window-time-span = 5 minutes
;;;
;;; Note that the use of "the" at the beginning of this, which lacks an embedded
;;; prepositional phrase, doesn't make sense to me designing it from scratch.
;;; Presumably, it was done for the sake of users who don't see "the" as
;;; anything other than sugar for the grammar, not as an element of English
;;; grammar that has a precise function.  Such users would presumably be
;;; confused as to why it is sometimes missing, just as many who learn English
;;; late in life often have trouble knowing when or when not to stick "the" in
;;; to their sentences.  OK.  In any case, we're ignoring these qualms, and will
;;; do the same as annotations for compatibility's sake.
;;;
;;;    the color-for-value-axis-labels of any value-axis is blue
;;;
;;; This is not yet supported for compound slots, but it is a planned extension
;;; that has been mostly designed, and will not be hard to add.  This kind of
;;; expression is supported in annotations, and gives them considerable added
;;; power.  We should consider supporting it sooner rather than later.
;;;
;;; When we do this, a kind of visual indicator will be added to tables showing
;;; compound slots to indicate that their value comes from an "any" statement.
;;; Perhaps an asterik, or perhaps something better.  We have not thought of a
;;; place to put such an any statement in the "table ui"; it so far only has a
;;; place in the gross grammar.  It would be the only such thing in this
;;; category, i.e., not visible in the subtables, if we supported it right now.
;;; 
;;;
;;; Consider
;;;
;;;   the color-for-value-axis-labels of the value-axis named V1 is black
;;;
;;; Also consider that the default for the color-for-value-axis-labels slot
;;; component group happens to be black.  If a user enters something like this
;;; as an annotation, however, it means that the slot has to be black, and
;;; it must remain black even if the default changes to something else.  The
;;; fact that it corresponds to the default does not leave us free to throw
;;; it away.
;;;
;;; We plan to handle this by tagging all of our initial values so that we
;;; for any slot component, we know whether its value comes from the default
;;; or from a user specification.
;;;
;;; Given that users of annotations can set things away from the default (by
;;; adding an annotation) and to the default (by removing an annotation), how do
;;; users of tables get the same power?  Well, they can already change something
;;; away from the default, by simply editing it.  This leaves reverting to the
;;; default.  We plan to handle this by adding a menu choice, or editing option,
;;; that lets them do this in the UI.  In the ultimate G2 language, there should
;;; also be high-level support for this (for both annotations and compound
;;; slots).  Since this is kind of a hair-splitting issue for most people, we will
;;; defer adding this feature until some later date.
;;;   
;;;
;;;   the use-variable-history
;;;       of the plot named temperature is yes;  { don't keep local history }
;;;   the expression of the plot named temperature
;;;       is the temperature
;;;          of tank-1;
;;;
;;;   the the use-simulator of the plot named pressure is yes;
;;;   the expression of the plot named pressure is the pressure of tank-1;
;;;   the update-interval of the plot named pressure 1 second;
;;;
;;;   the expression of plot 3 is sin (the current time / 50) * 20
;;;
;;; When printed back, this would appear as
;;;   
;;;
;;;   the use-variable-history of the plot named temperature is yes;
;;;   the expression of the plot named temperature is the temperature of tank-1;
;;;
;;;   the the use-simulator of the plot named pressure is yes;
;;;   the expression of the plot named pressure is the pressure of tank-1;
;;;   the update-interval of the plot named pressure 1 second;
;;;
;;;   the expression of plot 3 is sin (the current time / 50) * 20
;;;
;;; Notice that (1) the comments have been stripped; (2) the user's exact
;;; formatting has been lost; (3) the order of entries has been changed so that
;;; it's in the order shown in the table; (4) for the third plot, the 3 was
;;; allowed to be omitted on input, but it was printed on output.
;;; 
;;; The formal spec for the gross grammar is given below.
;;;   
;;;
;;; The special variable `write-compound-slots-parseably?' controls whether
;;; a compound slot's writer just prints out a brief description of the
;;; contents of the slot or a verbose, parseable description.  This variable
;;; is bound to nil, by default, at top level.  When it is bound to true,
;;; the parseable description is written.
;;;
;;;
;;; (NOTE: in the following, brackets (<,>,[,]), elipses (...), and bar (|) are
;;; all metasymbols; equal sign (=), colon (:), and semicolon (;) are all
;;; literals.)
;;; 
;;; A `parseable compound-slot description' is a series of equations of the form
;;;
;;;       the <slot component name> [of <component group reference>]
;;;          is <quoted parseable slot component value>
;;;       the <slot component name> [of <component group reference>]
;;;          = <quoted parseable slot component value>
;;;
;;; each of which is separated by a semicolon (;).
;;;
;;; A `component group reference' is permitted in one of the above equations
;;; only for so-called multiple compound slots.  These can have, in general, 0,
;;; 1, or more "compound slot groups".  The grammar for this is
;;;
;;;       the <compound slot type> named <symbol/name>
;;;       <integer/index> <compound slot type>
;;;
;;; [A future grammar is:
;;; 
;;;       any <compound slot type>
;;;
;;; This is not yet supported.]
;;;
;;; Items that are omitted on input have their default value.  Items that have
;;; their default value are not mentioned in the output.
;;;
;;; On output, the items appear in the same top-to-bottom order that they
;;; display in their tables.  On input, the items may appear in any order, and
;;; may also appear any number of times.  Slots are changed by parsing their
;;; text, in the same left-to-right order specified in the input. For slots
;;; without side effects, there's no good theory as to why they should appear
;;; more than once.  It is permitted, but will presumably only serve to slow
;;; things down.  For slots with side effects, the above specification may give
;;; it some meaning.  (Note that general guidelines advise against having slots
;;; with side effects.)
;;;
;;; When <symbol/name> is specified on input, it is always merged with the
;;; value, if any, for the <slot-type>-names slot, if specified, so that it
;;; becomes the first value.  Thus, for example, you can specify
;;;
;;;    the plot-names of the plot named FOO is BAR, FOO, NELLIE; ...
;;;
;;; but the plot-names entry will end up looking like
;;;
;;;    plot-names = FOO, BAR, NELLIE
;;;
;;; and the output for the overall slot will become
;;;
;;;    the plot-names of the plot named FOO is FOO, BAR, NELLIE; ...
;;;
;;;
;;; There may be certain modes in which tables appear to be written parseably.
;;; For example, the G2 action "change-the-text-of" will see the slot this way,
;;; and the expression "the text of" will see the slot this way.
;;;
;;; It may be desirable to view these slots this way in other contexts: regular
;;; attribute tables (as an option), inspect tables, inspect written output,
;;; attribute displays, etc.





;;;; Attributes


(defvar permanent-mutable-list
  (with-permanent-allocation (list nil)))

;; Should be a def-system-variable! (MHD 5/30/00)



;;; `Get-attribute-features' ...

(defun get-attribute-features
    (class slot-name defining-class? slot-component-name?)  
  (cond (slot-component-name?
	 (get-slot-component-features
	   slot-name defining-class? slot-component-name?))
	((eq slot-name 'class)
	 (slot-features pseudo-class-slot-description))
	(t (let ((slot-description? (slot-description-from-class class slot-name defining-class?)))
	     (when slot-description?
	       (slot-features slot-description?))))))



;;;`Get-attribute-value' ...

(defun get-attribute-value
    (frame slot-name defining-class?
	   slot-component-name? slot-component-indicator?)
  (if slot-component-name?
      (get-slot-component-value
	frame slot-name defining-class?
	slot-component-name? slot-component-indicator?)
      (get-slot-value frame slot-name defining-class?)))


;;; `Get-attribute-value-if-any' ...

(defun get-attribute-value-if-any
    (frame slot-name defining-class?
	   slot-component-name? slot-component-indicator?)
  (if slot-component-name?
      (get-slot-component-value-if-any
	frame slot-name defining-class?
	slot-component-name? slot-component-indicator?)
      (get-slot-value-if-any frame slot-name defining-class?)))


;;; `Set-attribute-value' ...

#+unused
(defun set-attribute-value 
    (frame slot-name defining-class?
	   slot-component-name? slot-component-indicator?
	   value)
  (cond
    (slot-component-name?
     (set-slot-component-value
       frame slot-name defining-class?
       slot-component-name? slot-component-indicator?
       value))
    (t
     (set-slot-value frame slot-name value defining-class?))))


;;; `Change-attribute-value' ...

(defun change-attribute-value
    (frame slot-name defining-class?
	   slot-component-name? slot-component-indicator? value)
  (change-slot-value
    frame slot-name value
    defining-class? slot-component-name? slot-component-indicator?))



;;; `Do-attributes' ...

(defmacro do-attributes
    ((frame compound-slot-name? slot-component-indicator?
	    &optional
	    attributes-to-include? attributes-to-exclude?
	    exclude-non-editable-attributes? exclude-restricted-attributes?)
     (slot-or-slot-component-name-var defining-class?-var
				      &optional alias?-var? slot-features-var?
				      type-of-slot-var?
				      value-var? slot-description?-var?) ; review order!
     &body body)
  (avoiding-variable-capture
      (frame compound-slot-name? slot-component-indicator?
	     attributes-to-include? attributes-to-exclude?
	     exclude-non-editable-attributes? exclude-restricted-attributes?)
    `(if (null ,compound-slot-name?)
	 (do-attribute-table-slots
	     (,frame 
		,attributes-to-include? ,attributes-to-exclude?
		,exclude-non-editable-attributes?
		,exclude-restricted-attributes?)
	     (,slot-or-slot-component-name-var
		,defining-class?-var
		,alias?-var? ,slot-features-var?
		,type-of-slot-var? ,value-var? ,slot-description?-var?)
	   . ,body)
	 (progn
	   (setf (car permanent-mutable-list) ,compound-slot-name?)
	   (do-attribute-table-slots
	       (,frame 
		  ,attributes-to-include? ,attributes-to-exclude?
		  ;; other args?!
		  )
	       (,slot-or-slot-component-name-var
		  ,defining-class?-var
		  ,alias?-var? ,slot-features-var? ,type-of-slot-var?
		  ,value-var? ,slot-description?-var?)
	     ;; just do header
	     (when (eq ,slot-or-slot-component-name-var
		       ',compound-slot-name?)
	       . ,body)
	     (return))
	   (let ((,defining-class?-var nil))
	     (do-slot-components
		 (,frame ,compound-slot-name?
			 ,defining-class?-var
			 ,slot-component-indicator?
			 ,attributes-to-include?
			 ,attributes-to-exclude?
			 ,exclude-non-editable-attributes?
			 ,exclude-restricted-attributes?)
	       (,slot-or-slot-component-name-var
		  ,alias?-var? ,slot-features-var? ,type-of-slot-var?
		  ,value-var?)
	       (let (,@(if slot-description?-var?
			   `((,slot-description?-var? nil))))
		 . ,body)))))))

;; Consider binding values for slots -- this service is already provided for
;; slot components.


;;; `Do-virtual-attributes' executes body in a tagbody named
;;; DO-VIRTUAL-ATTRIBUTES with the symbols given by name-var to the name of each
;;; virtual attribute for class.
;;;
;;; Deprecated virtual attributes are not included in the iteration.
;;;
;;; Note that (virtual-attribute name) returns the virtual-attribute structure
;;; corresponding to name.
;;;

(defmacro do-virtual-attributes ((frame) (name-var) &body body)
  (avoiding-variable-capture
      (frame &aux class-description list)
    `(let* ((,class-description (class-description-slot ,frame))
	    (,list (nconc (all-virtual-attributes-for-class ,class-description)
			  (all-non-local-virtual-attributes-for-class ,class-description))))
       (unwind-protect
	    (loop for ,name-var in ,list do (progn . ,body))
	 (reclaim-eval-list ,list)))))



     
       



;;;; Attribute Tables



;;; `Do-attribute-table-slots' ... Frame is evaluated and must evaluate to a
;;; frame.  Slot-name-var, defining-class?-var, alias?-var?, slot-features-var,
;;; and type-of-slot?-var are symbols to be bound appropriately while body is
;;; executed for each slot that would appear in an attribute table for frame
;;; (not counting "user restrictions" that would cause some of these not to
;;; appear in certain "G2 user modes".)
;;;
;;; Slots-to-include and slots-to-exclude must each be a `name denotations
;;; list', that is, a list of "name denotations" for slots.  (These are either
;;; slot names, or class qualified slot names.  See their definition in
;;; FRAMES4.)


(defvar mutable-slot-description-list-head
  (with-permanent-allocation (list 'hahaha)))


(defmacro do-attribute-table-slots
    ((frame
       &optional
       slots-to-include? slots-to-exclude?
       exclude-non-editable-slots? exclude-restricted-slots?)
     (slot-name-var defining-class-var?
		    &optional alias?-var? slot-features-var? type-of-slot-var?
		    slot-value-var? slot-description-var?)	    ; review order!!
     &body body)
  (let ((slot-features (or slot-features-var? '#:slot-features))
	(type-of-slot (or type-of-slot-var? '#:type-of-slot))
	(alias? (or alias?-var? '#:alias))
	(slot-description (or slot-description-var? '#:slot-description)))
    (avoiding-variable-capture
	(slots-to-include? slots-to-exclude? exclude-non-editable-slots?
			   exclude-restricted-slots?
			   &aux class-description class)
      `(let ((,class (class ,frame))
	     (,class-description (class-description-slot ,frame)))
	 (setf (car mutable-slot-description-list-head) pseudo-class-slot-description)
	 (setf (cdr mutable-slot-description-list-head)
	       (slot-descriptions ,class-description))
	 (loop as ,slot-description in mutable-slot-description-list-head
	       as ,slot-name-var = (pretty-slot-name ,slot-description)
	       as ,defining-class-var? ; get this faster?!
		  = (unless (and (eq ,slot-name-var 'class)
				 (eq 'root (defining-class ,slot-description)))
		      (when (slot-name-needs-qualification-p
			      ,slot-description ,class-description)
			(defining-class ,slot-description)))
	       as ,slot-features = (slot-features ,slot-description)
	       as ,type-of-slot = (feature-assq 'type ,slot-features)
	       when (and ,type-of-slot
			 (not (do-not-put-slot-in-attribute-tables-p
				  ,slot-description nil ,frame))
			 (or (not (feature-assq
				    'do-not-put-in-attribute-tables-if-null
				    ,slot-features))
			     (get-slot-description-value ,frame ,slot-description))
			 (category-symbol-given-slot-type
			   ,type-of-slot) ; see NOTE 1
			 )
		 do (let* ((,alias?
			      (get-alias-for-slot-name-if-any
				,slot-name-var ,class))
			   ,@(if slot-value-var?
				 `((,slot-value-var?
				      (if (and (eq ,slot-name-var 'class)
					       (eq 'root (defining-class ,slot-description)))
					  (class ,frame)
					  (get-slot-description-value-macro
					    ,frame ,slot-description))))))
		      (when (and
			      (or (null ,slots-to-include?)
				  (slot-denotation-member
				    ,slot-name-var ,defining-class-var?
				    ,slots-to-include?)
				  (if ,alias? ; hmmmm! (MHD 3/25/94)
				      (slot-denotation-member
					,alias? ,defining-class-var?
					,slots-to-include?)))
			      (or (not ,exclude-restricted-slots?)
				  (include-slot-in-attribute-table-p
				    ,frame (or ,alias? ,slot-name-var)
				    ,defining-class-var?)    ; Added.

				  (frame-of-class-p ; see NOTE 2
				    ,frame 'file-progress)
				  (and (eq ,slot-name-var 'class) ; see NOTE 3
				       (eq 'root (defining-class ,slot-description)))
				  )
			      (or (null ,slots-to-exclude?)
				  (not
				    (or (slot-denotation-member
					  ,slot-name-var ,defining-class-var?
					  ,slots-to-exclude?)
					(if ,alias? ; hmmmm! (MHD 3/25/94)
					    (slot-denotation-member
					      ,alias? ,defining-class-var?
					      ,slots-to-exclude?)))))
			      (or (not ,exclude-non-editable-slots?)
				  (type-slot-feature-assq-if-editable
				    ,slot-features)))
			. ,body)))))))

;; Consider looping over the restricted list rather than over the class description
;; if a restricted list is provided, for efficiency! (MHD 1/27/94)

;; NOTE 1: Maybe this won't always be necessary!

;; NOTE 2: This kludges around problems with putting up the file progress
;; display.  See FILES. Formally and fully work this out! (MHD 10/31/88)

;; NOTE 3: The class header is not to be suppressed through user restrictions
;; -- what about do-not-describe-in-attribute-tables slots! (MHD 10/31/88)

;; Note that the slot feature do-not-describe-in-attributes-table has been
;; changed to do-not-identify-in-attribute-tables.  (ghw 10/25/95)

;; Further parts moved here from tables today.  (MHD 11/15/93)

;; Moved here from TABLES today. (MHD 11/5/91)


;; Consider doing this as a loop iteration path.  That's harder to do, but may
;; be more convenient to use, especially when doing list collection, which it's
;; usually very convenient to do in loop.

;; Used in TABLES (by make-attributes-table) and in FILTERS (for describing
;; restrictions).

;; Added. (MHD 10/27/88)

;; Example:
;;(defun test (frame)  
;;  (do-attribute-table-slots
;;    (frame) (slot-name defining-class? alias? slot-features type-of-slot)
;;    (print (list slot-name defining-class? alias?))))





;;; `Do-frames-this-represents' binds represented-frame (at least once) to each
;;; frame represented by frame-representation.  The same represented frame may
;;; be bound more than once.

;;; To use this effectively, you must either set up a named block and return
;;; from it (using return-from) and/or simply use it for side effects.  Using
;;; return inside of it will generally not have the desired effect.

(defmacro do-frames-this-represents
	  ((represented-frame frame-representation) &body body)
  (let ((frame-representation-var (gensym))
	(last-represented-frame? (gensym))
	(row (gensym))
	(cell? (gensym)))
    `(let ((,frame-representation-var ,frame-representation))
       (frame-class-case ,frame-representation-var
	 (table
	   (loop with ,last-represented-frame? = nil
		 for ,row in (table-rows ,frame-representation-var)
		 do (loop for ,cell? in ,row
			  when (and ,cell?
				    (not (cell-is-block-p ,cell?)))
			    do (let ((,represented-frame
				      (get-slot-represented-by-text-cell-if-any ,cell?)))
				 (when (and ,represented-frame
					    (not (eq ,last-represented-frame?
						     ,represented-frame)))
				   (setq ,last-represented-frame? ,represented-frame)
				   (let ()	; needed to allow declarations (an idea)
				     . ,body))))))
	 ;; other cases some day?
	 ))))
			   
			   






;;; Attribute-table-p ... 

(defun-simple attribute-table-p (table)
  (and (eq (class table) 'table-item)
       (memq (name-or-names-for-frame (table-format table))
	     '(attributes-table-format new-attributes-table-format))))

;; The above test is sensitive to current realities: attribute tables are 
;; always strictly of class TABLE and have the table format attributes-table-
;; format.  Note that tabular-function-of-1-arg and tabular-function tables
;; have the same format but their classes are strict subclasses of TABLE.
;; (MHD 1/29/92)




;;; The simple function `attribute-table-with-header-p' returns T for tables
;;; which have headers (titles in a black border), which should behave like
;;; headers are wont to do, namely dismiss the table when clicked upon.

(defun-simple attribute-table-with-header-p (table)
  (and (memq (class table) '(table-item table-of-values))
       (eq (name-or-names-for-frame (table-format table))
	   'attributes-table-format)

       ;; First row has only a single (non-NIL) cell.
       (=f 1 (loop for element in (first (table-rows table))
		   count element))))

;; This differs from attribute-table-p by including the class table-of-values.





;;; `Valid-attribute-table-slot-p' is true if its args refer to a slot that
;;; exists and is legal to display in an attribute table.
;;;
;;; `Valid-attribute-table-text-cell-p' is similar but works with a text cell
;;; by calling valid-attribute-table-slot-p on the elements of its backpointer,
;;; if any.  If there's no backpointer, it's always true.

(defun valid-attribute-table-slot-p
    (frame slot-name
	   &optional defining-class?
	   slot-component-name? slot-component-indicator?
	   virtual-attribute?
	   exclude-restricted-attributes-p)
  (if virtual-attribute?
      (applicable-and-not-deprecated-virtual-attribute-p
	(class-description-slot frame)
	(virtual-attribute slot-name)
	nil)	
      (block :out
	(do-attributes
	    (frame
	      (if slot-component-name? slot-name)
	      slot-component-indicator?
	      nil nil nil exclude-restricted-attributes-p)
	  (a-slot-or-slot-component-name a-defining-class?)
	  (when (and (eq (or slot-component-name? slot-name)
			 a-slot-or-slot-component-name)
		     (or slot-component-name?
			 (eq defining-class? a-defining-class?)))
	    (return-from :out t)))
	(return-from :out nil))))

(defun valid-attribute-table-text-cell-p (text-cell
					  exclude-restricted-attributes-p)
  (multiple-value-bind
      (represented-frame?
       slot-name defining-class?
       slot-component-name? slot-component-indicator?
       virtual-attribute?)
      (get-slot-represented-by-text-cell-if-any text-cell)
    (or (null represented-frame?)
	(valid-attribute-table-slot-p
	 represented-frame?
	 slot-name defining-class?
	 slot-component-name? slot-component-indicator?
	 virtual-attribute?
	 exclude-restricted-attributes-p))))





;;; `Classic-attribute-table-p' is true if table is
;;;
;;;    (a) an attribute table;
;;;    (b) represents just one frame;
;;;    (b) on a temporary workspace; and
;;;    (c) the workspace is in view on one and only one workstation
;;;
;;;    
;;; When true, this returns three values:
;;;
;;;    (1) the (single) frame this table represents;
;;;    (2) the workstation the table is on; and
;;;    (3) the workspace the table is on
;;;
;;; Note that the workspace is also guaranteed to be (superblock? table).

;;; The function `alternative-classic-attribute-table-p' is similar, but in
;;; addition to detecting an attribute table, also detects a virtual attribute
;;; table.  It only returns true or false (nil), and does not return the
;;; additional information.  This probably makes it slightly more efficient.

(defun classic-attribute-table-p (table)
  (let ((frame? nil))    
    (if (and (attribute-table-p table)
	     (block visit-frames
		(do-frames-this-represents (f table)
		  (setq frame? f)
		  (when (and frame? (not (eq f frame?)))
		    ;; => represents at least 2 frames
		    (return-from visit-frames nil)))
		frame?))		; if non-nil, there's one
	(let ((workspace? (superblock? table)))
	  (if (and workspace?
		   (frame-of-class-p workspace? 'temporary-workspace))
	      (loop with workstation? = nil
		    for image-plane in (image-planes-this-is-on workspace?)
		    as pane = (pane-for-image-plane image-plane)
		    as gensym-window = (gensym-window-for-pane pane)
		    as next-workstation
		    = (workstation-this-is-on gensym-window)
		    do (when (and workstation?
				  (not (eq workstation? next-workstation)))
			 (return nil))
		       (setq workstation? next-workstation)
		    finally
		      (when (and workspace? workstation?)
			(return (values frame? workstation? workspace?)))))))))



(defun alternative-classic-attribute-table-p (table)
  (classic-attribute-or-virtual-attribute-table-p table))

;; Called by finish-update-to-representation-in-table and the event-handler
;; pop-down-attribute-table.  Consider whether these can be combined into one --
;; why have two functions with semioverlapping functionality?! (MHD 7/21/02)






;;; The function `put-up-attributes-table' creates a "classic" attribute table.
;;;
;;; In order to make the attribute tables presented to users of "classic attributes"
;;; more usable, it is desirable to not show the full text of compound slots, since
;;; it largely destroys the usability of the table.
;;; 
;;; The text of compound slots is written as `summary text', rather than in its
;;; complete form.  Text cells of applicable compound slots then have their
;;; TEXT-SUMMARIZED? property set to true.  When this is true, the EDIT menu
;;; choice is suppressed, and the SHOW-TEXT menu choice appears.  The SHOW-TEXT
;;; menu choice, when chosen, causes the full text to be displayed on the table,
;;; gets rid of the TEXT-SUMMARIZED? property.  In the resulting state, the EDIT
;;; menu choice is presented, as well as an additional choice,
;;; SHOW-SUMMARY-OF-TEXT.

(defun put-up-attributes-table
    (frame x-in-window y-in-window
	   &optional slots-to-include?
	   compound-slot-name? slot-component-indicator?
	   slots-to-highlight?)
  (when (allow-only-one-table-display-for-item?-from-system-table)
    (let ((table (loop for frame-representation in (frame-representations frame)
		       thereis (and (attribute-table-p frame-representation)
				    (not (virtual-attribute-table-p frame-representation))
				    frame-representation))))
      (when table
	;; set go-to-block? to t to move the table to center?
	(show-or-hide table t nil nil nil)
	(return-from put-up-attributes-table table))))

  (let ((table
	 (let ((write-compound-slots-parseably? nil)) ; to show summary of text
	   (make-attributes-table
	     frame nil
	     (if new-g2-classic-ui-p
		 'new-class-format	; note: normally not applicable here
		 (choose-font-format-per-fonts-table
		   'class-format 'font-for-attribute-tables))
	     (if new-g2-classic-ui-p
		 'new-attribute-value-format
		 (choose-font-format-per-fonts-table
		   'attribute-value-format 'font-for-attribute-tables))
	     (if new-g2-classic-ui-p
		 'new-attribute-description-format
		 (choose-font-format-per-fonts-table
		   'attribute-description-format 'font-for-attribute-tables))
	     slots-to-include?
	     nil
	     nil
	     (if new-g2-classic-ui-p '(class component-type) nil)
	     nil nil
	     compound-slot-name? slot-component-indicator?
	     slots-to-highlight?))))
    (put-table-on-workspace-in-pane table x-in-window y-in-window frame)
    table))

;; Consider making more of the arguments optional.

(defun put-table-on-workspace-in-pane 
    (table x-in-window y-in-window &optional represented-frame?)
  (let ((workspace
	  (make-workspace
	    'temporary-workspace nil table
	    (if new-g2-classic-ui-p 0 2))))
    (when new-g2-classic-ui-p
      (when represented-frame?
	(refresh-table-caption represented-frame? table workspace))
      (change-slot-value
	workspace 'workspace-background-color? ; see note
	(get-ui-parameter 'system-workspace-background-color)))
    (post-workspace-in-pane
      workspace
      current-workstation-detail-pane
      (if new-g2-classic-ui-p
	  nil
	  x-in-window)
      (if new-g2-classic-ui-p
	  (+r y-in-window (get-ui-parameter 'close-box-y-offset))
	  y-in-window)
      ;; For new UI, as w/ new menus, right-adjusted looks nicer. (MHD 10/6/99)
      :x-for-right-adjusting?
      (when new-g2-classic-ui-p
	(+r x-in-window (get-ui-parameter 'close-box-x-offset))))))


(defun refresh-table-caption (represented-frame table workspace)
  (change-slot-value
    workspace 'title-bar-caption-text
    (convert-text-string-to-text
      (multiple-value-bind (frame? slot-name defining-class?
				   slot-componenent-name slot-component-indicator?)
	  (get-first-slot-component-backpointer-if-any table)
	(declare (ignore slot-componenent-name))
	(if frame?
	    (make-component-type-header-string
	      frame? slot-name defining-class? slot-component-indicator?)
	    (make-class-header-string represented-frame))))))

(defun put-up-virtual-attributes-table (frame x-in-window y-in-window)
  (when (allow-only-one-table-display-for-item?-from-system-table)
    (let ((table (loop for frame-representation in (frame-representations frame)
		       thereis (and (virtual-attribute-table-p frame-representation)
				    frame-representation))))
      (when table
	;; set go-to-block? to t to move the table to center?
	(show-or-hide table t nil nil nil)
	(return-from put-up-virtual-attributes-table (values nil nil)))))

  (let* ((table (make-table-of-virtual-attributes frame))
	 (timestamp
	   ;; Use a running head because this is in the header/footer category,
	   ;; and especially so that it won't get pop-up menus when clicked.
	   (make-running-head
	     (twith-output-to-text-string
	       (tformat "Last update: ")
	       (twrite-frame-edit-timestamp
		 (get-current-frame-edit-timestamp)))))
	 (button (make-button-to-update-virtual-attributes-table table frame timestamp))
	 (workspace
	   (make-workspace 'temporary-workspace nil table
			   (if new-g2-classic-ui-p 0 2))))
    (when new-g2-classic-ui-p
      (change-slot-value
	workspace 'title-bar-caption-text
	(convert-text-string-to-text (make-virtual-attribute-class-header-string frame)))
      (change-slot-value
	workspace 'workspace-background-color? ; see note
	(get-ui-parameter 'system-workspace-background-color)))
    (add-to-workspace button workspace
		      (left-edge-of-block table)
		      (+f (bottom-edge-of-block table) 10))
    (add-to-workspace timestamp workspace
		      (+f (right-edge-of-block button) 10)
		      (+f (bottom-edge-of-block table) 10))
    (post-workspace-in-pane
      workspace
      current-workstation-detail-pane
      (if new-g2-classic-ui-p
	  nil
	  x-in-window)
      (if new-g2-classic-ui-p
	  (+r y-in-window (get-ui-parameter 'close-box-y-offset))
	  y-in-window)
      ;; For new UI, as w/ new menus, right-adjusted looks nicer. (MHD 10/6/99)
      :x-for-right-adjusting?
      (when new-g2-classic-ui-p
	(+r x-in-window (get-ui-parameter 'close-box-x-offset))))))

(defun update-virtual-attributes-table (table table-fsn+frame+frame-fsn+timestamp+button)
  (gensym-dstruct-bind ((table-fsn frame frame-fsn timestamp button)
		       table-fsn+frame+frame-fsn+timestamp+button)
    (unless (or (frame-has-been-reprocessed-p table table-fsn)
		(frame-has-been-reprocessed-p frame frame-fsn))
      (update-all-representations-in-table table frame)
      (replace-text-with-text-string-in-text-box
	(twith-output-to-text-string
	  (tformat "Last update: ")
	  (twrite-frame-edit-timestamp
	    (get-current-frame-edit-timestamp)))
	timestamp)      
      (let* ((workspace (superblock? button))
	     (button-change-to-left-edge
	       (-f (left-edge-of-block table)
		   (left-edge-of-block button)))
	     (button-change-to-top-edge
	       (-f (+f (bottom-edge-of-block table) 10)
		   (top-edge-of-block button)))
	     (timestamp-change-to-left-edge
	       (-f (+f (right-edge-of-block button) 10)
		   (left-edge-of-block timestamp)))
	     (timestamp-change-to-top-edge
	       (-f (+f (bottom-edge-of-block table) 10)
		   (top-edge-of-block timestamp))))
	(unless (and (=f 0 button-change-to-left-edge)
		     (=f 0 button-change-to-top-edge)
		     (=f 0 timestamp-change-to-left-edge)
		     (=f 0 timestamp-change-to-top-edge))
	  (update-images-of-block button t nil)
	  (update-images-of-block timestamp t nil)
	  (shift-block button button-change-to-left-edge button-change-to-top-edge)
	  (shift-block timestamp timestamp-change-to-left-edge timestamp-change-to-top-edge)
	  (enlarge-workspace-for-block-and-subblocks-as-necessary button workspace)
	  (enlarge-workspace-for-block-and-subblocks-as-necessary timestamp workspace)
	  (update-images-of-block button nil nil)
	  (update-images-of-block timestamp nil nil))))))


;; Note: why not do the background color in the table format for
;; "new-attributes-table-format"?  It is not too unmodular this way, and a
;; little arbitrary, but mainly I chose this approach because it eliminates the
;; flashing of the background color when putting up or refreshing the workspace
;; with the table.  One side effect, which is not bad, maybe good, is that the
;; table, if transferred, would appear to have a "transparent" backround, rather
;; than a solid extra-light-gray background.  That's also as it was before the
;; new UI.  (MHD 10/5/99)


	


;;; ... This assumes that the set of slot names that have aliases is totally
;;; disjoint from the set of slot names that have pretty names that aren't the
;;; same as (EQ) to themselves.  If that constraint is violated, the results are
;;; undefined.
;;;
;;; When the attribute name needs qualification, it is written with a
;;; defining class prefix, a double colon (::), and the pretty name of
;;; the slot without hyphens stripped.  As follows
;;;
;;;    <class>::<pretty slot name>
;;;
;;; In this case, as well, do-not-downcase-first-character? and
;;; character-to-add-at-end? are ignored, as they are intended for
;;; system (internal) slot names. [?? check!!]
;;;
;;; Otherwise, the pretty name or alias of the slot is printed with hyphens
;;; stripped, obeying all of the arguments, and without the colons or defining
;;; class.

(defvar known-gensym-acronyms
  (loop for string in '("KB" "DDE" "GSI" "ICP" "GFI" "OLE" "G2" "UI" "UUID" "G2GL")
	collect (copy-as-wide-string string)))

(defun-simple make-string-that-identifies-attribute
    (frame slot-or-slot-component-name defining-class?
	   do-not-downcase-first-character? character-to-add-at-end?
	   slot-component-case-p)
  (twith-output-to-text-string
    (twrite-string-that-identifies-attribute
      frame slot-or-slot-component-name defining-class?
      do-not-downcase-first-character? character-to-add-at-end?
      slot-component-case-p)))



(defun-void twrite-string-that-identifies-attribute
    (frame slot-or-slot-component-name defining-class?
	   do-not-downcase-first-character? character-to-add-at-end?
	   slot-component-case-p)
  (let* ((slot-description?
	   (get-slot-description-of-frame
	     slot-or-slot-component-name frame defining-class?))
	 (pretty-slot-name?
	   (if slot-description? (pretty-slot-name slot-description?)))
	 (name-to-display
	   (or (if slot-component-case-p
		   (get-best-name-for-slot-component
		     slot-or-slot-component-name (class frame))
		   (if (aliases-for-slot-name ; optimization only
			 slot-or-slot-component-name)
		       (get-alias-for-slot-name-if-any
			 slot-or-slot-component-name frame)))
	       pretty-slot-name?
	       slot-or-slot-component-name)))
    (when (and slot-description?
	       (slot-name-needs-qualification-p
		 slot-description?
		 (class-description-slot frame)))
      (twrite-symbol-name
	(defining-class slot-description?)
	:all nil nil known-gensym-acronyms)
      (twrite-string "::"))

    (with-localization-domain 'table
      (with-localization-purpose 'attribute
	(let ((localized-string? (translation-for-symbol? name-to-display)))
	  (twrite-string-as-attribute-name
	    (or localized-string? (symbol-namew name-to-display))
	    (if do-not-downcase-first-character? :first nil)
	    t
	    character-to-add-at-end?
	    known-gensym-acronyms))))))


;; notes on the printing conventions:
;;
;; unqualified case:
;; traditional format: (with do-not-downcase-first-character?, which
;; is always true in practice)
;;   Slot name
;; maybe could be different, but it's a big deal, since it's saved in
;; many kbs.  I'd rather entertain changes to it when/if we give users
;; control over it, so they can do it.
;; class-qualified name case:
;;   CLASS::Slot name
;; alt: just print it plainly:
;;   class::slot-name


;; Other issues -- review the class header, which also prints the attribute name
;; without hyphens.  This breaks down as a "nicety" frequently!  (MHD 2/20/94)

;; Consider having a tformat directive for this kind of printing. (MHD 2/13/94)

;; Make this more efficient -- see note above! (MHD 2/3/94)

;; This is fast enough that there is little reason to do caching.

;; This is used only in the following two functions.

;; It can now be simplified since it is never going to get a value for
;; character-for-end? given that make-text-for-cell-identifying-attribute-in-table
;; has been modified. ddm 12/18/96






;;; `Make-text-for-cell-identifying-attribute-in-table' returns an unformatted
;;; text for a table cell that would identify the attribute of frame that is
;;; represented by the the slot named slot-or-slot-component-name.  The basis
;;; for the name is either the alias for the slot, if any, or else the
;;; slot-or-slot-component-name itself.  The name is written in lower case,
;;; except for the initial character, which is usually an upper-case letter.
;;; Hyphens in the name are written as spaces.  If slot-type (the type of the
;;; slot) is yes-or-no?, a "?" is appended to the name.


(defun make-text-for-cell-identifying-attribute-in-table
    (frame slot-or-slot-component-name defining-class?  ;; slot-type
	   slot-component-case-p)
;  (let ((character-for-end?
;	  (if (memq (category-symbol-given-slot-type slot-type)
;		    grammar-categories-getting-?-in-attribute-table)
;	      #.%\?)))
  ;; See note A.
    (convert-text-string-to-text
      (make-string-that-identifies-attribute
	frame slot-or-slot-component-name defining-class?
	t
      	nil ;;character-for-end?
	slot-component-case-p)))

;; This is fast enough that there is little reason to do caching.

;;; Note A.  This function used to provide the service of adding question marks
;;; to the end of the names of any slot that had one of specified set of categories
;;; as its type. We (ddm, mhd) removed that ability because the inconsistency between
;;; what the user saw in the table and what they would get when they entered
;;; the attribute into their code by clicking on the table cell.  ddm 12/20/96 
;;;    Only two categories were ever on the list: yes-or-no? and relation-yes-or-no?.
;;; Since the first of those was identical semantically to yes-or-no and only
;;; used in 8 places, we replaced it. Here is the original code/documentation:
;;  ;;; `grammar-categories-getting-?-in-attribute-table' is a list of grammar
;;  ;;; categories whose display in the left column of an attribute table gets
;;  ;;; a question mark added to the deconcatenated slot name.
;;  ;;; Defvar is in file RELATIONS.
;;
;;  (pushnew 'yes-or-no? grammar-categories-getting-?-in-attribute-table)



;;; `Write-attribute-name' writes, in lower case with hyphens changed to spaces,
;;; the name for the attribute of frame that is represented by the slot or slot
;;; component named slot-or-slot-component-name.  The basis for the name is
;;; either the alias for the slot, if any, or else the
;;; slot-or-slot-component-name itself.

(defun-void write-attribute-name
    (frame slot-or-slot-component-name defining-class?)
  (twrite-string-that-identifies-attribute
    frame slot-or-slot-component-name
    defining-class?
    nil nil nil))




;;; `Make-attributes-table' creates any number rows that represent slots in frame
;;; as appropriate given the state of the class system, the restrictions system,
;;; and the given arguments.  If one or more rows that represent frame are
;;; created, this adds table to (frame-representations frame), i.e., as a
;;; representation of frame.

;;; In the unusual event that there are no attributes to show, a table will be
;;; created that does not point back to frame and to which frame does not point.
;;; The table will have only row, and that row will have only one column
;;; consisting of a text cell that reads "NO ATTRIBUTES TO DISPLAY".

;;; Attributes-to-include? is a list of names of slots (or slot components) to
;;; include in the table insofar as they are present and satisfy other
;;; restrictions.  If non-nil, all slots that satisfy these other restrictions
;;; are included.  Attributes-to-exclude? is a list of names of slot (or slot
;;; components) to exclude.

;;; [New behavior as of the 6.0 release pending 1/10/99: (MHD)] If frame is
;;; transient, table is explicitly set transient.  Otherwise, it is left neither
;;; permanent nor transient.

(defun make-attributes-table
       (frame &optional table-format? class-format? attribute-value-format?
	                attribute-description-format?
			attributes-to-include?
			put-box-translation-and-text-up-front?
			attributes-not-to-name?
			attributes-to-exclude?
			exclude-non-editable-attributes?
			include-restricted-attributes?
			compound-slot-name? slot-componenent-indicator?
			attributes-to-highlight?)

  (with-localization-domain
      ;; The special check is part of a kludge thrown together in short order to
      ;; get around a substantial design flaw in the treatment of password
      ;; changing that was uncovered when we went to internationalize it. The
      ;; plan is to clean it up after 5.0r3 ships and sources can be committed
      ;; again.
      (if (frame-of-class-p frame 'g2-login)
	  (if doing-password-change-p
	      'password-change
	      ;; see one-of-the-localization-domains-subsumes-domain-p to
	      ;; understand why a symbol will work as well as a frame here.
	      frame)
	  frame)
    
  (let* ((attribute-description-format
	   (or attribute-description-format?
	       (if new-g2-classic-ui-p
		   'new-attribute-description-format
		   'attribute-description-format)))
	 (attribute-value-format
	   (or attribute-value-format?
	       (if new-g2-classic-ui-p
		   'new-attribute-value-format
		   'attribute-value-format)))
	 (attributes-table-format
	   (or table-format?
	       (if new-g2-classic-ui-p
		   'new-attributes-table-format
		   'attributes-table-format)))
	 (class-format
	   (or class-format? 'class-format))
	 (table-rows
	   (if (eq attributes-to-include? 'none) ; hack JED 9/194
	       nil
	       (make-attribute-table-rows
		 frame class-format attribute-value-format
		 attribute-description-format
		 attributes-to-include? put-box-translation-and-text-up-front?
		 attributes-not-to-name? attributes-to-exclude?
		 exclude-non-editable-attributes?
		 include-restricted-attributes?
		 compound-slot-name? slot-componenent-indicator?
		 attributes-to-highlight?)))
	 (table
	   (make-or-reformat-table
	     (or table-rows
		 (make-empty-attributes-table-rows attribute-value-format))
	     attributes-table-format
	     nil)))
    (when table-rows
      (add-frame-representation-if-necessary table frame))
    ;; For 6.0 anomaly HQ-2611709. (MHD 1/10/99)
    ;; But while a permanent table of a transient frame is bad,
    ;; a neither-permanent-nor-transient table of a transient frame
    ;; (for example, the one on an inspect workspace) is OK, so only
    ;; do this when the table would otherwise be permanent. This fixes
    ;; HQ-4955374 "Snapshot fails when transient items are visible on
    ;; an Inspect workspace" -alatto, 2/15/05
    (when (and
	    (transient-p frame)
	    (permanent-block-p table))
      (set-transient-and-propagate table nil))
    (when (not (or
		 (transient-p frame)
		 (permanent-block-p frame)))
      (set-neither-permanent-nor-transient-and-propagate table nil))
    table)))

;; NOTE 1: "... TO SHOW" until now. (MHD 1/30/92)

;; Internationalize this!  -- Done 4/11/97 ddm

;; Consider always putting the box-translation-and-text slot up front, eliminating the
;; put-box-translation-and-text-up-front? argument.  Alternatively, consider having it be
;; true by default.

;; Consider having an optional attributes-table-description? argument, to be cannibalized
;; for text-representation-for-slot-value? and text-that-identifies-attribute? components
;; that are set to nil when cannibalized.  This would be useful for make-short-
;; representation-as-appropriate.

;; Consider leaving hyphens in attribute names and aliases.
  

  



;;; `Make-attribute-table-rows' returns a slot-value list of table rows.  This is
;;; a subfunction of make-attributes-table, and the args are basically described
;;; there.
;;;
;;; The lists attributes-to-include?, attributes-to-exclude?, and
;;; attributes-not-to-name?  are all lists of slot name denotations, not simply
;;; lists of slot names (or aliases thereof).

(defun make-attribute-table-rows
    (frame class-format attribute-value-format attribute-description-format
      &optional attributes-to-include? put-box-translation-and-text-up-front?
      attributes-not-to-name? attributes-to-exclude?
      exclude-non-editable-attributes?
      include-restricted-attributes?      
      compound-slot-name? slot-component-indicator?
      attributes-to-highlight?)
  (let ((table-rows nil) tail table-row)	 
    (do-attributes
	(frame compound-slot-name? slot-component-indicator?
	       attributes-to-include? attributes-to-exclude?
	       exclude-non-editable-attributes?
	       (not include-restricted-attributes?))
      (slot-or-slot-component-name defining-class?
	alias? slot-features nil value)
      (setq table-row
	    (make-attribute-table-row
	      frame
	      (or compound-slot-name? slot-or-slot-component-name)
	      ;; Due to the removal of the class slot, unless nil is
	      ;; explicitly used for the "class slot", the class-instance-
	      ;; header will not update.  (ghw 3/22/96)
	      (unless (eq 'class (or compound-slot-name? slot-or-slot-component-name))
		defining-class?)
	      (if compound-slot-name? slot-or-slot-component-name)
	      (if compound-slot-name? slot-component-indicator?)
	      slot-features
	      value	      
	      (slot-denotation-member
		slot-or-slot-component-name defining-class?
		attributes-not-to-name?)
	      t
	      class-format  attribute-value-format
	      attribute-description-format
	      (or (not (listp attributes-to-highlight?))
		  (slot-denotation-member
		    slot-or-slot-component-name defining-class?
		    attributes-to-highlight?))))
      ;; collect table rows in order:
      (cond
	(table-rows
	 (cond
	   ((and (eq slot-or-slot-component-name 'box-translation-and-text)
		 put-box-translation-and-text-up-front?)
	    (if (null (first (first table-rows)))	; if first row has no description
		(setf (cdr table-rows)	        ;   put this second
		      (slot-value-cons table-row (cdr table-rows)))
		(setq table-rows (slot-value-cons table-row table-rows))))
	   (t
	    (setf (cdr tail) (slot-value-list table-row))
	    (pop tail))))
	(t
	 (setq table-rows (slot-value-list table-row))
	 (setq tail table-rows))))
    table-rows))




;;; `Make-attribute-table-row' ... if always-in-two-columns? is true, this will
;;; always return a (slot-value) list of length 2, filling the first column with
;;; nil if there's nothing else to go there.  If it's false, then the length of
;;; the result is 1 if the name gets excluded, and 2 otherwise.

(defun-simple make-attribute-table-row
    (frame slot-name defining-class?
	   slot-component-name? slot-component-indicator?
	   slot-features value
	   always-exclude-name? always-in-two-columns?
	   class-format attribute-value-format attribute-description-format
	   highlightp)
  (let* ((type-of-slot (feature-assq 'type slot-features))
	 (format-override? (feature-assq 'format-override slot-features))
	 (current-ddd.dddd-format? ; special var.
	   (if (and format-override?
		    (eq (second format-override?) 'ddd.dddd-format))
	       (third format-override?))))
    (declare (special current-ddd.dddd-format?)) ; nec. due module ordering issues!
    (nconc
      (if (and (not always-exclude-name?)
	       (not (feature-assq
		      'do-not-identify-in-attribute-tables
		      slot-features)))	  
	  (slot-value-list
	    (make-text-cell
	      (make-text-for-cell-identifying-attribute-in-table
		frame
		(or slot-component-name? slot-name)
		defining-class? ;; type-of-slot -- args changed 12/20/95
		slot-component-name?)
	      attribute-description-format))
	  (if always-in-two-columns?
	      (slot-value-list nil)))
      (slot-value-list
	(let ((value-cell
		(make-text-cell-for-slot-value-itself
		  frame value
		  type-of-slot	
		  (if (or (eq slot-name 'class)	; useful distinction
			  (eq slot-component-name? 'component-type))
		      class-format
		      attribute-value-format)
		  slot-name defining-class?
		  slot-component-name? slot-component-indicator?)))
	  (when highlightp
	    (change-text-cell-property value-cell 'highlight-color
				       (text-cell-line-color nil value-cell)))
	  value-cell)))))



;;; The functions `attribute-table-row-name-cell' and
;;; `attribute-table-row-value-cell' get the name and value cells of a row of an
;;; attribute table.

(defun-simple attribute-table-row-name-cell (row)
  (when (cdr row) (car row)))

(defun-simple attribute-table-row-value-cell (row)
  (if (cdr row) (cadr row) (car row)))


;;; The function `attribute-table-cell-is-class-p' determines whether a cell of
;;; an attribute table represents a class attribute.

(defun-simple attribute-table-cell-is-class-p (cell)
  (and (cell-is-text-cell-p cell)
       (loop for (frame slot-name) on (text-cell-plist cell) by 'cddr
	     when (eq slot-name 'class)
	       return t)))
       




(def-slot-value-writer free (attribute)
  (let ((value
	  (if (slot-constantp attribute)
	      (get-slot-value-number-or-string-from-slot-constant attribute)
	      attribute)))
    (when value				; if null, write nothing
      (if (text-string-p value)
	  (let ((write-strings-parsably? nil))
	    (twrite-string value))
	  (if (slot-constantp attribute) 
	      (print-constant
		value
		(get-unit-from-slot-constant attribute))
	      (twrite value))))))




;;; Make-empty-attributes-table-rows returns a list of one table row with one
;;; text cell that contains the just text
;;;
;;;    NO ATTRIBUTES TO DISPLAY
;;;

(defun make-empty-attributes-table-rows (text-cell-format)
  (slot-value-list
    (slot-value-list
      (make-text-cell
	(copy-text '("NO ATTRIBUTES TO DISPLAY")) ; See NOTE 1
	text-cell-format))))

;; Needs internationalization!



;;; Make-attributes-table-description returns a slot value list of the form
;;;
;;;  ({(slot-name defining-class?
;;;               text-representation-for-slot-value?
;;;               text-that-identifies-attribute?)}).

;;; slots-to-include? is a list of names or aliases thereof of slots to describe
;;; insofar as they are present and satisfy other restrictions.
;;; Slots-to-exclude? might, for instance, be used to eliminate the class slot.

(defun make-attributes-table-description
    (frame
      &optional omit-text-representations-for-text-slot-values?
      slots-to-include? slots-to-exclude?
      include-non-editable-slots? include-text-that-identifies-attributes?
      include-restricted-slots?)
  (let ((result nil))
    (do-attribute-table-slots
	(frame
	  slots-to-include? slots-to-exclude?
	  (not include-non-editable-slots?)
	  (not include-restricted-slots?))
	(slot-name defining-class? alias?
	 slot-features type-of-slot slot-value)
      (slot-value-push
	(slot-value-list
	  slot-name
	  defining-class?
	  (if (not (and omit-text-representations-for-text-slot-values?
			(text-slot-type-p type-of-slot)))
	      (make-text-representation-for-slot-value-itself
		frame slot-value type-of-slot))
	  (if (and include-text-that-identifies-attributes?
		   (not (feature-assq
			  'do-not-identify-in-attribute-tables
			  slot-features)))
	      (make-text-for-cell-identifying-attribute-in-table
		frame slot-name defining-class?
		;; type-of-slot  -- args changed 12/20/95
		nil)))
	result))
    (nreverse result)))

;; The unlikely case where an alias conflicts with a slot name for a
;; given frame is not handled here, nor is it generally handled in G2.
;; That is why I think it was ok to extend this to match aliases as well
;; as slot names here, even though it doesn't know whether uniasing has
;; already been done.  Note: this has not been done yet for
;; make-attributes table!  Confusing -- FIX!!  (MHD 8/8/90) -- NOTE: We
;; found at least one important conflict: CLASS is the alias for
;; name-of-defined-class, as slot of definitions.  This conflicts with
;; the slot name CLASS, a slot that every frame has.  Don't know what to
;; do about this.  This is a problem for the user in practice if he
;; tries to show the class slot in a table of every definition -- here
;; he gets two columns, one for the class, e.g.  object-definition, and
;; one for the name of the defined class, e.g.  pump.  Consider
;; realiasing this as "name of defined class", "defined class", or
;; "class name".  Note that the alias CLASS was never CLASS-NAME,
;; although uses of CLASS-NAME were eliminated in a few user-visible
;; places (documented in DEFINITIONS) to make them consistent with other
;; places where "-NAME" was left out, e.g.  class, superior-class.  Note
;; that such changes occurred after 2.1, I believe, so users have not
;; seen them yet at this point in time.  (MHD 3/25/91)

;; Fixed to use type-of-slot-if-editable to determine if a slot can be edited.
;; (MHD 4/3/90)

;; This must parallel make-attributes-table above.



(defun make-text-cell-for-slot
       (frame slot-name defining-class?
	      type-of-slot text-box-format-or-format-name
	&optional slot-component-name? slot-component-indicator?)
  (cond
    ;; this special case hack is here so that some callers of this
    ;; in tables and/or inspect do not have to wise up about the
    ;; fact that class is no longer a real slot.  JED 2/23/96
    ((and (eq slot-name 'class)
	  (null defining-class?))
     (make-text-cell-for-slot-value-itself
       frame
       (class frame)
       '(type class-instance-header)
       text-box-format-or-format-name
       slot-name defining-class?
       slot-component-name? slot-component-indicator?))
    (t
     (make-text-cell-for-slot-value-itself
       frame
       (get-slot-value frame slot-name defining-class?)
       type-of-slot text-box-format-or-format-name
       slot-name defining-class?
       slot-component-name? slot-component-indicator?))))


(defun make-text-cell-for-slot-value-itself
       (frame slot-value type-of-slot text-box-format-or-format-name
	      slot-name defining-class?
	      slot-component-name? slot-component-indicator?)
  (setq leave-text-representation-as-a-single-line? nil)
  (let* ((text-cell
	   (make-text-cell
	     (make-text-representation-for-slot-value-itself
	       frame slot-value type-of-slot)
	     text-box-format-or-format-name)))

    ;; Leave-text-representation-as-a-single-line?  may get its value setq'd by
    ;; subfunctions of make-text-representation-for-slot-value; its value is
    ;; relevant only in the following form:
    
    (when leave-text-representation-as-a-single-line?
      (change-text-cell-property text-cell 'leave-as-single-line? t))

    ;; When write-compound-slots-parseably? is false, and when writing
    ;; a compound slot, leave a property behind, 'text-summarized?, that
    ;; says so, for subsequent changes.
    (when (and (compound-slot-descriptor slot-name)
	       (null slot-component-name?)
	       (not write-compound-slots-parseably?)) ; usu. bound to T
      (change-text-cell-property text-cell 'text-summarized? t))

    (if slot-component-name? ; (compound-slot-descriptor slot-name)  ; slot-component-name?
	(note-slot-component-represented-by-text-cell
	  text-cell
	  frame slot-name defining-class?
	  slot-component-name? slot-component-indicator?)
	(note-slot-represented-by-text-cell
	  text-cell frame slot-name defining-class?))
    
    text-cell))

;; Revised the above to setq the global leave-text-representation-as-a-single-line?
;; before its use instead of binding it, as had been suggested by a comment
;; previously.  (MHD 6/1/92)

;; If a text slot, handle text in a special way!!!


#+unused
(defun make-text-representation-for-slot-component-value
    (frame slot-name defining-class?
	   &optional
	   slot-component-name? slot-component-indicator?
	   type-of-slot?)
  (make-text-representation-for-slot-value-itself
    frame
    (if slot-component-name?
	(get-slot-component-value
	  frame slot-name defining-class?
	  slot-component-name? slot-component-indicator?)
	(get-slot-value frame slot-name defining-class?))
    (or type-of-slot?
	(if slot-component-name?
	    (get-type-of-slot-component-if-any ; JOE TO DEFINE! (MHD 1/26/94)
	      frame slot-name defining-class?
	      slot-component-name? slot-component-indicator?)
	    (get-type-of-slot-if-any frame slot-name defining-class?)))))



(def-table-format attributes-table-format
  table-background-color? nil			; maybe "light-gray" when color mapping
						;   works for B&W systems
						; -- was white (MHD 8/3/89)
;  table-border-color? red
;  table-row-boundary-color? red
;  table-column-boundary-color? red
  table-row-boundary-width 1
  table-column-boundary-width 1)

(def-table-format new-attributes-table-format
  table-background-color? nil	; shows through the extra-light-gray background
  table-border-color? dark-gray
  table-row-boundary-color? dark-gray
  table-column-boundary-color? dark-gray
  table-row-boundary-width 1
  table-column-boundary-width 1)

(def-table-format-spot-generator attributes-table-format
    (attribute-table mouse-pointer)
  (generate-spot-for-input-table
    attribute-table
    mouse-pointer
    (make-attribute-table-spot)))

;; A verbatim copy of the above but for New G2 Classic UI:  (MHD 10/4/99)
(def-table-format-spot-generator new-attributes-table-format
    (attribute-table mouse-pointer)
  (generate-spot-for-input-table
    attribute-table
    mouse-pointer
    (make-attribute-table-spot)))


(def-table-format search-state-table-format
  table-background-color? nil
  table-row-boundary-width 1
  table-column-boundary-width 1)

(def-table-format-spot-generator search-state-table-format
    (attribute-table mouse-pointer)
  (generate-spot-for-input-table
    attribute-table
    mouse-pointer
    (make-search-state-table-spot)))

(defun search-results-table-p (table)
  (and (of-class-p table 'table)
       (eq (name-or-names-for-frame (table-format table))
	   'search-state-table-format)))




;;; Large (default) attributes table text cell formats:

(def-text-cell-format attribute-description-format
  text-cell-lines-justified? nil
  text-cell-line-quadding? right
  text-cell-left-margin 10
  text-cell-top-margin 10
  text-cell-right-margin 10
  text-cell-bottom-margin 10
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 10
  text-cell-font-map (hm18)			;was recently swiss20
  text-cell-line-height 20
  text-cell-baseline-position 16
  text-cell-line-spacing 3
  default-word-spacing #.(convert-to-text-width 4) ; was 6 (MHD 2/20/94)
  minimum-format-width-for-text-cell 350)	;was 225 (5/6/87)

;; Changed the word spacing here, and below, for 4.0.  I and GHW felt the
;; spacing was too wide for comfortable reading.  GHW felt 3 would not even be
;; going too far.  (MHD 2/20/94)

(def-text-cell-format new-attribute-description-format
  text-cell-lines-justified? nil
  text-cell-line-quadding? right
  text-cell-left-margin 5
  text-cell-top-margin 5
  text-cell-right-margin 5
  text-cell-bottom-margin 5
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 5
  text-cell-font-map (hm14)
  text-cell-line-height 15
  text-cell-baseline-position 12
  text-cell-line-spacing 2
  default-word-spacing #.(convert-to-text-width 3)
  minimum-format-width-for-text-cell 300)


(def-text-cell-format attribute-value-format
  text-cell-lines-justified? nil
  text-cell-left-margin 10
  text-cell-top-margin 10
  text-cell-right-margin 10
  text-cell-bottom-margin 10
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 20
  text-cell-font-map (hm18)			;was recently swiss20
  text-cell-line-height 20
  text-cell-baseline-position 16
  text-cell-line-spacing 3
  default-word-spacing #.(convert-to-text-width 4) ; was 6 (MHD 2/20/94)
  minimum-format-width-for-text-cell 350)


(def-text-cell-format new-attribute-value-format
  text-cell-lines-justified? nil
  text-cell-left-margin 5
  text-cell-top-margin 5
  text-cell-right-margin 5
  text-cell-bottom-margin 5
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 5
  text-cell-font-map (hm14)
  text-cell-line-height 15
  text-cell-baseline-position 12
  text-cell-line-spacing 2
  default-word-spacing #.(convert-to-text-width 3)
  minimum-format-width-for-text-cell 300)

(def-text-cell-format class-format
  text-cell-background-color? black
  text-cell-line-color? white
  text-cell-line-quadding? center
  text-cell-lines-justified? nil
  text-cell-left-margin 10
  text-cell-top-margin 10
  text-cell-right-margin 10
  text-cell-bottom-margin 10
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 20
  text-cell-font-map (hm18)			;was recently swiss20
  text-cell-line-height 20
  text-cell-baseline-position 16
  text-cell-line-spacing 3
  default-word-spacing #.(convert-to-text-width 4) ; was 6 (MHD 2/20/94)
  minimum-format-width-for-text-cell 350)




;;; The text-cell format `new-class-format', like class-format, it to be used to
;;; display the table-header text, which is the class slot and a little bit of
;;; other information about the frame.  This format is not normally displayed in
;;; classic attribute tables, since the table header text is normally put in the
;;; title block, for but it may be used for tables that will be put right onto
;;; workspaces, e.g., the virtual attribute table now shown in via the describe
;;; command.

(def-text-cell-format new-class-format
  text-cell-background-color? dark-slate-blue ; note: same as title-bar bg color
  text-cell-line-color? white
  text-cell-lines-justified? nil
  text-cell-line-quadding? center
  text-cell-left-margin 5
  text-cell-top-margin 5
  text-cell-right-margin 5
  text-cell-bottom-margin 5
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 10
  text-cell-font-map (hm14)
  text-cell-line-height 15
  text-cell-baseline-position 12
  text-cell-line-spacing 2
  default-word-spacing #.(convert-to-text-width 3)
  minimum-format-width-for-text-cell 300)




;;; Small attributes table text cell formats:

(def-text-cell-format small-attribute-description-format
  text-cell-lines-justified? nil
  text-cell-line-quadding? right
  text-cell-left-margin 8
  text-cell-top-margin 4
  text-cell-right-margin 8
  text-cell-bottom-margin 4
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 8
  text-cell-font-map (hm14)
  text-cell-line-height 18
  text-cell-baseline-position 14
  text-cell-line-spacing 3
  default-word-spacing #.(convert-to-text-width 4)
  minimum-format-width-for-text-cell 300)

(setf (corresponding-small-font-format-name 'attribute-description-format)
      'small-attribute-description-format)


(def-text-cell-format small-attribute-value-format
  text-cell-lines-justified? nil
  text-cell-left-margin 8
  text-cell-top-margin 4
  text-cell-right-margin 8
  text-cell-bottom-margin 4
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 8
  text-cell-font-map (hm14)
  text-cell-line-height 18
  text-cell-baseline-position 14
  text-cell-line-spacing 3
  default-word-spacing #.(convert-to-text-width 4)
  minimum-format-width-for-text-cell 300)

(setf (corresponding-small-font-format-name 'attribute-value-format)
      'small-attribute-value-format)


(def-text-cell-format small-class-format
  text-cell-background-color? black
  text-cell-line-color? white
  text-cell-line-quadding? center
  text-cell-lines-justified? nil
  text-cell-left-margin 8
  text-cell-top-margin 4
  text-cell-right-margin 8
  text-cell-bottom-margin 4
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 8
  text-cell-font-map (hm14)
  text-cell-line-height 18
  text-cell-baseline-position 14
  text-cell-line-spacing 3
  default-word-spacing #.(convert-to-text-width 4)
  minimum-format-width-for-text-cell 300)

(setf (corresponding-small-font-format-name 'class-format)
      'small-class-format)


			     
(def-text-cell-format extra-large-attribute-description-format
  text-cell-lines-justified? nil
  text-cell-line-quadding? right
  text-cell-left-margin 15
  text-cell-top-margin 10
  text-cell-right-margin 15
  text-cell-bottom-margin 8
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 14
  text-cell-font-map (hm24)
  text-cell-line-height 26
  text-cell-baseline-position 21
  text-cell-line-spacing 3
  default-word-spacing #.(convert-any-number-to-text-width-at-compile-time 8.75) ; 5/8 en
  minimum-word-spacing #.(convert-to-text-width 7)	          ; 1/2 en
  maximum-word-spacing #.(convert-to-text-width 21)	          ; 3/2 en
  minimum-format-width-for-text-cell 400)

(setf (corresponding-extra-large-font-format-name
	'attribute-description-format)
      'extra-large-attribute-description-format)


(def-text-cell-format extra-large-attribute-value-format
  text-cell-lines-justified? nil
  text-cell-left-margin 15
  text-cell-top-margin 10
  text-cell-right-margin 15
  text-cell-bottom-margin 8
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 14
  text-cell-font-map (hm24)
  text-cell-line-height 26
  text-cell-baseline-position 21
  text-cell-line-spacing 3
  default-word-spacing #.(convert-any-number-to-text-width-at-compile-time 8.75) ; 5/8 en
  minimum-word-spacing #.(convert-to-text-width 7)	          ; 1/2 en
  maximum-word-spacing #.(convert-to-text-width 21)	          ; 3/2 en
  minimum-format-width-for-text-cell 400)

(setf (corresponding-extra-large-font-format-name
	'attribute-value-format)
      'extra-large-attribute-value-format)


(def-text-cell-format extra-large-class-format
  text-cell-background-color? black
  text-cell-line-color? white
  text-cell-line-quadding? center
  text-cell-lines-justified? nil
  text-cell-left-margin 15
  text-cell-top-margin 10
  text-cell-right-margin 15
  text-cell-bottom-margin 8
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 14
  text-cell-font-map (hm24)
  text-cell-line-height 26
  text-cell-baseline-position 21
  text-cell-line-spacing 3
  default-word-spacing #.(convert-any-number-to-text-width-at-compile-time 8.75) ; 5/8 en
  minimum-word-spacing #.(convert-to-text-width 7)	          ; 1/2 en
  maximum-word-spacing #.(convert-to-text-width 21)	          ; 3/2 en
  minimum-format-width-for-text-cell 400)

(setf (corresponding-extra-large-font-format-name
	'class-format)
      'extra-large-class-format)

;; In module MENUS, class formats are explicitly tested for.




;;; Edit-attribute-table-slot-in-place ... Table must be a frame representation
;;; of frame which has one slot representing the slot named slot-name in frame.
;;; Image-plane is the specific image plane on which to edit and must have on it
;;; the image of a workspace containing table.

;;; Workstation-context-return-function?, workstation-context-return-information?,
;;; workstation-context-return-information-reclaimer? are defined as for enter-
;;; workstation-context.

;;; Edit-box-format?, if specified, is passed on the enter-edit-context to
;;; control the text box format of the edit box.

(defun edit-attribute-table-slot-in-place
    (table frame slot-name defining-class?
	   image-plane
	   &optional
	   workstation-context-return-function?
	   workstation-context-return-information?
	   workstation-context-return-information-reclaimer?
	   edit-box-format?		; revise arglist someday!
	   slot-component-name? slot-component-indicator?
	   (initial-string? nil))  ; added extra argument (pbk 2/1/96)
  (multiple-value-bind
      (left-edge-of-cell
	top-edge-of-cell
	right-edge-of-cell bottom-edge-of-cell)
      (let ((text-cell?
	      (get-text-cell-representing-slot-if-any
		table frame slot-name defining-class?
		slot-component-name? slot-component-indicator?
		nil nil)))
	(when text-cell?
	  (get-table-cell-edges table text-cell?)))
    (with-old-style-workstation-return-function
	( workstation-context-return-function?
	  workstation-context-return-information?
	  workstation-context-return-information-reclaimer?)
      (enter-editing-context
	frame
	(make-slot-name-denotation slot-name defining-class?)
 	initial-string?	 ;  was nil (pbk)
	nil
	edit-box-format?
	nil
	nil nil
	image-plane table
	left-edge-of-cell top-edge-of-cell
	right-edge-of-cell bottom-edge-of-cell
	nil nil nil
	nil ; dont show buttons-p 
	))))

;; This is used, at present, only by the icon editor, although it is expected to
;; to come into much wider use eventually by other facilities.





;;; The function `get-attribute-value-text-cell' returns the corresponding
;;; attribute-value text cell given the text-cell-or-row-index, which may be
;;; either a row index (0-based) or a text cell that is in the desired row,
;;; either the value or name side.
;;;
;;; The function `get-attribute-description-text-cell' returns the corresponding
;;; attribute-description text cell given a similar arg.
;;;
;;; Both functions assume that table is "attribute-table-like"; see
;;; attribute-table-like-p.

(defun get-attribute-value-text-cell (table text-cell-or-row-index)
  (let ((row
	  (if (fixnump text-cell-or-row-index)
	      (nth text-cell-or-row-index (table-rows table))
	      (loop for row in (table-rows table)
		    when (memq text-cell-or-row-index row)
		      return row))))
    (if (cdr row)
	(second row)	  ; a table with two columns has value cells in 2nd
	(first row))))	  ; a table with one column (must be an attribute display)
			  ;   has only value cells



(defun get-attribute-description-text-cell (table text-cell-or-row-index)
  (let ((row
	  (if (fixnump text-cell-or-row-index)
	      (nth text-cell-or-row-index (table-rows table))
	      (loop for row in (table-rows table)
		    when (memq text-cell-or-row-index row)
		      return row))))
    (if (cdr row)      ; a table with two columns has nil or a
		       ;   description cell in first of each row
	(first row))))
                       ; a table with one column has no description cells (must
		       ;   be an attribute display)

  





;;; `Get-attribute-table-row-alias-string' returns a new text string
;;; representing the attribute name for the designated row.
;;; Text-cell-or-row-index is described get-attribute-value-text-cell, q.v.

(defun get-attribute-table-row-alias-string
    (attribute-table text-cell-or-row-index)
  (let ((value-text-cell?
	  (get-attribute-value-text-cell
	    attribute-table
	    text-cell-or-row-index)))
    (when value-text-cell?
      (multiple-value-bind
	  (frame? slot-name? defining-class? slot-component-name? virtual-attribute?)
	  (get-slot-represented-by-text-cell-if-any value-text-cell?)
	(when (and frame? (not virtual-attribute?))
	  (if defining-class?
	      (tformat-text-string
		"~NQ"
		(alias-slot-name-if-necessary
		  (or slot-component-name? slot-name?)
		  frame?)
		defining-class?)
	      (copy-symbol-name-parsably
		(alias-slot-name-if-necessary
		  (or slot-component-name?
		      slot-name?)
		  frame?)
		nil)))))))








;;; Get-type-of-slot-feature-if-boolean returns the type feature from
;;; slot-features if it contains a "boolean" type.

(defun get-type-feature-if-boolean (slot-features)
  (let ((type-of-slot? (feature-assq 'type slot-features)))
    (when (and type-of-slot?
	       (memq (category-symbol-given-slot-type type-of-slot?)
		     grammar-categories-getting-yes-no-feature))
      type-of-slot?)))



;;; `Text-cell-represents-boolean-attribute-p' is true if text-cell represents a
;;; boolean-valued slot or slot component.  When this returns true as the first
;;; value, it also returns as its second value of the slot or slot component.

(defun text-cell-represents-boolean-attribute-p (text-cell)
  (multiple-value-bind
      (frame? slot-name-or-index? defining-class?
	      slot-component-name? slot-component-indicator? virtual-attribute?)
      (get-slot-represented-by-text-cell-if-any text-cell)
    (when (and frame?
	       slot-name-or-index?
	       (symbolp slot-name-or-index?)		    ; A test probably needed in many places.
	       (not virtual-attribute?)
	       (get-type-feature-if-boolean
		 (if slot-component-name?
		     (get-slot-component-features
		       slot-name-or-index? defining-class? slot-component-name?)
		     (slot-features
		       (if (eq slot-name-or-index? 'class)
			   pseudo-class-slot-description
			   (slot-description-from-class
			     (class frame?)
			     slot-name-or-index?
			     defining-class?))))))
      (values
	t
	(if (eq slot-name-or-index? 'class)
	    (class frame?)
	    (get-attribute-value
	      frame? slot-name-or-index? defining-class?
	      slot-component-name? slot-component-indicator?))))))





;;; `Change-value-of-attribute-in-text-cell' changes the value of the
;;; "attribute" represented by text-cell, if any.  If text-cell represents a
;;; frame, this changes the value of the slot or slot component it represents to
;;; value.

#+unused
(defun change-value-of-attribute-in-text-cell (text-cell value)
  (multiple-value-bind
      (frame? slot-name? defining-class?
	      slot-component-name? slot-component-indicator? virtual-attribute?)
      (get-slot-represented-by-text-cell-if-any text-cell)
    (when (and slot-name? (not virtual-attribute?))
      (change-attribute-value
	frame? slot-name? defining-class?
	slot-component-name? slot-component-indicator?
	value))))


;;; `Get-value-of-attribute-in-text-cell' gets the value of the attribute
;;; represented by text-cell, if any.  (Note that there is no way to distinguish
;;; the value nil from the case where the text cell doesn't represent any
;;; attribute at all.)

#+unused
(defun get-value-of-attribute-in-text-cell (text-cell)
  (multiple-value-bind
      (frame? slot-name? defining-class?
	      slot-component-name? slot-component-indicator? virtual-attribute?)
      (get-slot-represented-by-text-cell-if-any text-cell)
    (when (and slot-name? (not virtual-attribute?))
      (get-attribute-value
	frame? slot-name? defining-class?
	slot-component-name? slot-component-indicator?))))


;;; `Get-type-of-attribute-in-text-cell' ... returns the type feature for the
;;; attribute represented by text-cell, if any.

#+unused
(defun get-type-of-attribute-in-text-cell (text-cell)
  (multiple-value-bind
      (frame? slot-name? defining-class?
	      slot-component-name? slot-component-indicator? virtual-attribute?)
      (get-slot-represented-by-text-cell-if-any text-cell)
    (declare (ignore slot-component-indicator?))
    (when (and slot-name? (not virtual-attribute?))
      (feature-assq
	'type
	(get-attribute-features
	  (class frame?) slot-name? defining-class?
	  slot-component-name?)))))
  

;;; The function `change-value-of-attribute-in-text-cell-via-parser' changes the
;;; value of the attribute represented by text-cell by parsing the given symbol
;;; as text. This enables recording of author, etc.

(defun change-value-of-attribute-in-text-cell-via-parser (text-cell new-value-as-symbol)
  (multiple-value-bind (frame? slot-name?
			       defining-class?
			       slot-component-name?
			       slot-component-indicator?)
      (get-slot-represented-by-text-cell-if-any text-cell)
    ;; The following test seems to be needed for the times the user clicks on
    ;; the attribute name instead of the value.  The test for frame? is
    ;; probably unecessary, but it can't hurt and we'll abide by the
    ;; convention for "?" suffixed variables.  . -dkuznick, 11/26/07
    (when (and slot-name? frame?)
      (parse-text-for-slot (convert-text-string-to-text
			     (copy-wide-string
			       (symbol-namew new-value-as-symbol)))
			   frame?
			   (get-slot-description-of-frame slot-name? frame? defining-class?)
			   nil		; runtime-change? 
			   nil		; type-of-slot?
			   slot-component-name?
			   slot-component-indicator?))))

  




;;;; Highlighting Attributes



;;; The function `highlight-or-unhighlight-attribute' finds text cells
;;; representing the attribute designated by the 5-tuple
;;;
;;;   <frame, slot-name, defining-class?,
;;;    slot-component-name?, slot-component-indicator?>
;;;
;;; and either highlights or unhighlights them, depending on unhighlight-case?.
;;;
;;; When text-region-class? is true, it should be a subclass of text-region.
;;; It then is used to highlight by putting the text region of the entire text
;;; of the text cells found.
;;;
;;; This is called by the editor on entrance and exit, and is part of the
;;; highlight-or-unhighlight-for-slot facility, in EDIT.
;;;
;;; This interacts in a subtle way with change slot value: this tests whether
;;; table is in the midst of having a slot value changed, and is therefore
;;; erased, and an element of stack-of-slot-value-changes.  If so, we must not
;;; draw the highlight, but instead must only put the highlight property into
;;; the text cell plist so that the drawing will reflect it when drawing
;;; happens.  If the special suppress-updating-of-slot-value-representations? is
;;; true, we also don't want to do any drawing, and also don't want to look at
;;; the aforementioned stack-of-slot-value-changes.

(defun highlight-or-unhighlight-attribute
    (frame slot-name defining-class?
	   slot-component-name? slot-component-indicator?
	   highlight-color? unhighlight-case? text-region-class?)
  (loop for representation in (frame-representations frame)
         do
    (frame-class-case representation
      (table
	(unless (frame-of-class-p representation 'explanation-table)  ; review!
	  (let* ((table representation)
		 (cell?
		   (get-text-cell-representing-slot-if-any
		     table frame slot-name defining-class?
		     slot-component-name? slot-component-indicator?)))
	    (if (or suppress-updating-of-slot-value-representations?
		    (memq table (cdr stack-of-slot-value-changes)))
		(change-text-cell-property
		  cell? 'highlight-color highlight-color?)
		(highlight-or-unhighlight-cell
		  cell? table highlight-color?
		  unhighlight-case? text-region-class?)))))
      (t
	;; eventually do something clever to the views
	nil))))




;;;; Operations on Representations in Support of Save KB



;;; The services in this section are provided to FILES to help it achive
;;; two of its goals.  A simplified model of saving is that is walks a spanning
;;; tree over the entire KB walking depth-first over those attributes that
;;; are marked as savable.  Things that might be visited in the recursive
;;; descent of saving a structure S are said to be `reachable' from S.
;;;
;;; These functions may also be useful elsewhere in this or other modules.

;;; One goal that save-kb must achieve is that it never discover a frame
;;; in the midst of saving that shouldn't be saved.  For example, a transient
;;; should not be saved except if it appears in a position where it can be
;;; clipped out of the KB data structures.

;;; The second goal that save-kb must achieve is that it must never save
;;; a definition as a side effect of saving the things reachable from 
;;; another definition.  Why that would be bad is, presumably, documented
;;; in save-kb.

;; do-frames-this-represents moved upwards for the benefit of several functions
;; that need it.  This section is now really just documentary.




;;;; Updating Representations




;;; Update-representations updates any table or name box representations of frame.

;see update-all-representations-in-table
(defun update-representations (frame)
  (if (frame-representations frame)
      (do-attribute-table-slots (frame) (slot-name defining-class?)
	(update-representations-of-slot-value
	  frame slot-name defining-class?))))

;; New.  At present, this is only used by clone-frame.  This can use
;; optimization. (MHD 11/5/91)



;;; Update-frame-name-references is to be called from change-slot-value after
;;; the name-or-names-for-frame slot of any frame (i.e., any block) has been
;;; changed.  It does not update the direct frame representations of frame,
;;; but handles the indirect ones, as follows:
;;;
;;;    (1) calls update-name-box, if appropriate, on frame;
;;;    
;;;    (2) updates titles on image planes "title bars" showing
;;;        frame, if frame is a workspace; and
;;;        
;;;    (3) updates table-header slots of items below frame in
;;;        the KB hierarchy that may be showing frame (see the
;;;        printer for class-header).

;;; `Suppress-updates-to-name-boxes' provides an evil hack to avoid
;;; creating nameboxes on procedures and methods when their name is not
;;; changing.  This behavior is anomalous compared with all other name
;;; changes in G2.  Why you ask?  Well when we recompile the entire
;;; KB it would create name boxes on all the methods and procedures
;;; for which users had carefully "hidden" them.  This created litter
;;; in user and Gensym KBs that was unacceptable.  Hence this hack.

;;; We were tempted to suppress the call on the slot putter if we
;;; were not actually changing the name, but that would suppress
;;; the consistency analysis of frames that refer to this name.

;; - ben & ghw Jun 11, 97

(defvar suppress-updates-to-name-boxes nil)

(defun-void update-frame-name-references (frame)
  (update-indirect-class-header-name-references frame)
  (when (workspace-p frame)
    (update-titles-on-image-planes-workspace-is-on frame))
  (frame-class-case frame
    ;; GENSYMCID-983: action-button name box - The name-box of action buttons is not auto-updated after modification
    ;; NOTE: here a symbol `button' was removed. -- Jingtao Xu, Mar 2013
    ((text-box table trend-chart chart freeform-table user-menu-choice)
     nil)
    (t
      (unless suppress-updates-to-name-boxes
	(update-name-box frame)))))

(defun update-indirect-class-header-name-references (frame)
  (update-representations-of-slot-value frame 'class)
  (let ((subworkspace?
	  (if (frame-of-class-p frame 'entity) ; has subworkspaces slot
	      (car (subworkspaces frame)))))
    (when subworkspace?
      (update-representations-of-slot-value subworkspace? 'class)))
  (do-attribute-table-slots (frame)
      (slot-name defining-class? nil nil nil slot-value)
    (cond
      ((framep slot-value)
       (update-indirect-class-header-name-references slot-value))
;      ((compound-slot-p slot-name (class frame))
;       (let ((compound-slot-value slot-value))
;        (update-compound-slot-value-for-name-references
;          frame slot-name compound-slot-value)))
      )))


;;; `Update-compound-slot-value-for-name-references' does the following
;;;
;;;    (1) updates the representations of the "component type slot" of
;;;        all the slot component groups in compound-slot-value;
;;;    (2) for every slot component C in each of the groups, if C
;;;        is a slot component group (future capability maybe), it
;;;        recurs; otherwise, if C is a frame, it calls
;;;        back to update-indirect-class-header-name-references.
;;;
;;; 

#+unused
(defun update-compound-slot-value-for-name-references
    (frame slot-name compound-slot-value)
  (declare (ignore frame slot-name compound-slot-value))
  ;; JED TO WRITE!
  )



;;; The function `update-attribute-tables-for-instances' does a batch fixup of
;;; tables for instances denoted by class-or-list-of-instances, which is either
;;; a list of instances or a class.  If a class, then if
;;; strict-class-instances-p is true, only strict instances are dealt with;
;;; otherwise, all instances.  The args update-denotations-p and
;;; exclude-restricted-attributes-p are handled as per
;;; update-table-representation.

;;; This makes transient use of the table-specific non-savable KB flag
;;; table-collected-p.  It assumes all tables have it off (unset) by default,
;;; and leaves the flag off (unset) by the time this function returns.

(defun update-attribute-tables-for-instances
    (class-or-list-of-instances strict-class-instances-p
				&optional update-denotations-p
				exclude-restricted-attributes-p)
  (let ((all-tables-so-far '()))
    (macrolet ((per-instance-pushnew ()
		 `(loop for r in (frame-representations instance)
			when (and (table-p r) (not (table-collected-p r)))
			  do (setf (table-collected-p r) t)
			     (gensym-push r all-tables-so-far))))
      (cond
	((listp class-or-list-of-instances)
	 (loop for instance in class-or-list-of-instances
	       do (per-instance-pushnew)))
	(strict-class-instances-p
	 (loop for instance being each strict-class-instance
	       of class-or-list-of-instances
	       do (per-instance-pushnew)))
	(t
	 (loop for instance being each class-instance
	       of class-or-list-of-instances
	       do (per-instance-pushnew))))
      (loop with frame-reference
	      = (copy-frame-serial-number (current-frame-serial-number))
	    for table in all-tables-so-far
	    unless (frame-has-been-reprocessed-p table frame-reference)
	      do (setf (table-collected-p table) nil)
		 (update-table-representation
		   table t update-denotations-p
		   exclude-restricted-attributes-p
		   reading-kb-p)
	    finally
	      (reclaim-frame-serial-number frame-reference))
      (reclaim-gensym-list all-tables-so-far))))



;;; The function `update-attribute-tables' brings all tables representing frame
;;; up-to-date at least in so far as obsolete rows are removed.  In addition,
;;; "classic" attribute tables may also have rows added to them as necessary.
;;;
;;; Usually, any tables that would end up empty (no attributes to display) are
;;; deleted as a result of this call; however, this must take care particularly
;;; when deleting tables that represent them selves, e.g., digital clocks or
;;; readout tables or graphs, since that would result in its representations
;;; being deleted in the middle of its iteration over the list of
;;; representations.  Therefore, a table that represents itself will not be
;;; subject to any updating by this function.  However, its pure representations
;;; apart from itself (e.g., classic attribute tables) will be updated.
;;;
;;; By default, this now [as of 5.0, 4/28/97] refreshes the text of cells
;;; representing slots of frames in most cases.  However, if reading-kb-p is
;;; true, this does no such update in the case of "non-classic" attribute
;;; tables.  This is intended to address the issue of calling this function from
;;; the initialize-after-reading method of block, in which case frame is not
;;; necessarily fully set up when this is called, so we cannot risk invoking
;;; writers on its slots; we do know, however, what the slots are, so it is
;;; valid to remove obsolete rows.

(defun update-attribute-tables (frame &optional update-denotations-p
				      exclude-restricted-attributes-p)
  (loop with copy = (copy-list-using-gensym-conses (frame-representations frame))
	with reference-frame-serial-number = (copy-frame-serial-number (current-frame-serial-number))
	for representation in copy
	do (frame-class-case representation
	     (table
	       (let ((table representation))
		 (unless (or (frame-has-been-reprocessed-p
			       table reference-frame-serial-number)
			     ;; don't handle self-representing tables here:
			     (memq frame copy))
		   (update-table-representation
		     table t update-denotations-p
		     exclude-restricted-attributes-p
		     nil ; reading-kb-p ; SEE UPDATE 2!
		     ))))
	     (t
	       ;; eventually do something clever for other representations
	       nil))
	finally
	  (reclaim-gensym-list copy)
	  (reclaim-frame-serial-number reference-frame-serial-number)))

;; Note: the case that inspired the reading-kb-p guard was for the class
;; parameter, for the slot initial-value, which has type feature supplied-value.
;; When reading in a parameter from a KB, its initial-value slot has a value
;; (nil) that is unwritable by its writer at the beginning of
;; initialize-after-reading, and when this is invoked, but then get a valid
;; value by the end of initialize-after-reading. We could have fixed it to
;; handle the value in the writer, but we were afraid this problem might crop up
;; again unless we included this logic.  (MHD 4/29/97)
;;
;; -- UPDATE: I've changed that writer to handle the
;; transient-nil-while-initializing case, but I feel it's too risky to change
;; this still, now.  So note for now that there is special code for all the
;; slots that might have a different value upon recreation from a saved KB than
;; they did when they were saved, which code must update the table
;; representations.  There is the appropriate call, for example, in the
;; initialize-after-reading method for variable-or-parameter, which calls
;; update-representations-of-variable-or-parameter-value to ensure that the
;; current-value attribute in attribute displays is right after loading a KB.
;; I've just fixed another case: G2-window instances need to have their many
;; non-KB-saved slots updated after reading (See bug HQ-1479297). It just
;; calls this update-table-representation to update all tables, including
;; attribute displays ("non-classic"). (MHD 6/8/99)
;;
;; -- UPDATE 2: we are now enabling the refresh again. There should be no
;; writers at this point than cannot handle their slot's initial values.  This
;; change will fix the bug that tables representing do-not-save slots were
;; showing the wrong text, since they were showing the text as at the time of
;; the save. When recreated from a KB, they get their initial value, so that's
;; what they should show. (MHD 3/29/03)




;;; `Update-table-representation' at a minimum removes rows that are no longer
;;; valid for table.  In addition, if table is a "classic" attribute table, it
;;; applies refresh-classic-attribute-table, q.v., which also adds rows as
;;; necessary.
;;;
;;; Delete-if-empty? is documented at update-attribute-table-rows, q.v.
;;;
;;; If dont-refresh-existing-cells-in-non-classic-table-p is true, and table is
;;; not a "classic" atribute table, this does not refresh the text of cells
;;; representing slots in frames.  This should be specified false if the slot
;;; has an invalid value, e.g., if its in a transient state, such as when
;;; reading in a KB.  [But, ironically, that's been the only case we've
;;; specified TRUE for this var, at least since '97! (MHD 6/8/99)] For a classic
;;; attribute table, this argument is irrelevant.

(defun update-table-representation
    (table &optional delete-if-empty? update-denotations-p
	   exclude-restricted-attributes-p
	   dont-refresh-existing-cells-in-non-classic-table-p)
  (multiple-value-bind (frame? workstation workspace)
      (classic-attribute-table-p table)
    (cond
      (frame?
       (refresh-classic-attribute-table
	 table frame? workstation workspace delete-if-empty?))
      (t
       (refresh-attribute-table
	 table delete-if-empty? update-denotations-p
	 exclude-restricted-attributes-p
	 dont-refresh-existing-cells-in-non-classic-table-p)))))





;;; `Refresh-classic-attribute-table' is to be called on the `classic' attribute
;;; tables, i.e., those that are put up by put-up-attributes-table whenever some
;;; number of changes in the state of the system call into question table's
;;; appearance. In general, this make a table end up looking just as it would if
;;; it were made from scratch.
;;;
;;; Delete-if-empty? is documented at update-attribute-table-rows, q.v.
;;;
;;; The test for whether this function may be called on table is
;;; classic-attribute-table-p, q.v., which returns the arguments beyond table
;;; that refresh-classic-attribute-table needs.
;;;
;;; This creates a new set of table rows in the workstation context of
;;; workstation, the workstation the table is showing on.  This ensures that
;;; restrictions are obeyed.
;;;
;;; This shrink-wraps workspace upon completion.

(defun refresh-classic-attribute-table
    (table frame workstation workspace &optional delete-if-empty?)
  (for-workstation (workstation)
    (update-attribute-table-rows table frame delete-if-empty?))

  (when new-g2-classic-ui-p
    (refresh-table-caption frame table workspace)
    (refresh-title-bar workspace))
  
  (shrink-wrap-workspace workspace))

;; Note that this does not currently avoid refreshing if the table is all
;; up-to-date already. It could certainly be enhanced to do so, and that
;; would be desirable if we called it more often.
;;
;; Note that it might be a nice enhancement to call this on classic attribute
;; tables as needed when mode changes happened in a workstation.  Doing so would
;; be somewhat significant change.  It might be done, as well, at the same time
;; as we decide to refresh menus that are up whenever a mode changes.  
;;
;; Note that the fact that user modes may be played with to get the rows you
;; want and then set back, it is unclear whether a table that is permanently on
;; a workspace wants to be showing all and everything it can, or just the subset
;; that it could when it was created.  "Classic" tables don't have this problem,
;; at least not as much, since they're on temporary workspaces, can't be saved
;; in KBs, etc.  At least it's more reasonable to take liberties with their
;; contents, on feels....  (MHD 2/17/95)





;;; `Refresh-attribute-table' really only removes rows of table that have become
;;; obsolete.  Note, however, that at present, if there are no attributes left
;;; to display, the table will be left with a single row expressing that fact in
;;; English.  This behavior may not be appropriate and may want to be revised in
;;; the future.  We don't exactly know yet how.

;;; Unless dont-refresh-existing-cells-p, this regenerates the text of each cell
;;; in the table representing a slot of a frame.  This should be specified true
;;; if the slot has an invalid value, e.g., if its in a transient state, such as
;;; when reading in a KB. 

(defun refresh-attribute-table (table &optional delete-if-empty?
				      update-denotations-p
				      exclude-restricted-attributes-p
				      dont-refresh-existing-cells-p)
  (when update-denotations-p
    (when (update-text-cell-denotations-for-slot-name-change
	    table exclude-restricted-attributes-p)
      (update-images-of-block table t t)
      (reformat-table-in-place table)
      (update-images-of-block table nil t)))
  (let* ((frame-serial-number (copy-frame-serial-number (frame-serial-number table)))
	 (rows-to-delete-in-table?
	  (find-obsolete-rows-in-table
	    table exclude-restricted-attributes-p)))
    (when rows-to-delete-in-table?
      (update-attribute-table-rows
	table rows-to-delete-in-table? delete-if-empty?)
      (reclaim-gensym-list rows-to-delete-in-table?))
    ;; Now refresh the text of every remaining row, unless table's gone:
    (unless (or dont-refresh-existing-cells-p
		(frame-has-been-reprocessed-p table frame-serial-number))
      (update-text-cell-representations-of-slot-values table))
    (reclaim-frame-serial-number frame-serial-number)))

;; The update at the end was added especially to handle slots that become
;; qualified, and thereby start representing different slots, which may not have
;; the same value.  The backpointer then looks (and is) valid, but points to a
;; different slot.  We could either take the position that the display should
;; continue to represent the unqualified attribute, or that it should continue
;; to represent the slot defined by the same class as it used to.  The second of
;; these choices is much more complicated to implement, and is not clearly the
;; only right choice.  Therefore, we chose the first approach: we will have it
;; display the value of the slot its backpointer really resolves to, thus having
;; it display the value it really represents.  Note, too, that if the slot goes
;; away completely,the attribute tables gets deleted completely (assuming
;; delete-if-empty? is true).  This resolves bug HQ-1230529, "Attribute displays
;; not updated if class-specific-attributes are edited". (MHD 4/28/97)



;;; `Update-text-cell-representations-of-slot-values' calls
;;; update-representation-of-slot-value for each slot value or virtual-attribute
;;; value represented by a text cell in table.  In addition, for slot-value
;;; cases, but not, at present, for virtual-attribute cases, subscribed T2
;;; tables are updated via Javalink.

(defun update-text-cell-representations-of-slot-values (table)
  (loop for row in (table-rows table)
	as row-index from 0
	do (loop for cell? in row
		 as column-index from 0
		 when (and cell? (not (cell-is-block-p cell?)))
		   do (multiple-value-bind
			  (f sn dc scn sci va) ; Note: some or all can be nil
			  (get-slot-represented-by-text-cell-if-any cell?)
			(declare (ignore dc scn sci))
			(when (and f
				   (symbolp sn)
				   ;; In virtual-attribute case, check for a
				   ;; backpointer to the slot.
				   (or (null va)
				       (memq table (frame-representations f))))
			  (update-text-cell-for-slot-in-table table cell?)
			  (when (null va) ; VA's not yet implemented in T2!
			    (when (and g2-has-v5-mode-windows-p
				       (frame-of-class-p table 'item))
			      (send-ws-representations-item-change-macro
				table
				(allocate-evaluation-structure-inline
				  'attribute-name 'table-rows ;'table-cells for ff-tables
				  'row-index row-index
				  'column-index column-index
				  'cell-attribute-name
				  'cell-display-text
				  'new-value (exported-cell-text cell?))))))))))








;;; `Find-obsolete-rows-in-table' returns a gensym list of any rows in table
;;; that shouldn't be there because they would not currently be included in an
;;; attribute table, usually for reasons such as that their cells represent
;;; slots in frames that don't (or, more likely, no longer) exist.  Note that
;;; the elements are the actual list structure of the rows; only the backbone
;;; result list is new conses that are owned by the caller.
;;;
;;; Where a backpointer to a frame exists, it is assumed that the frame is
;;; always still a valid frame, but that the slots and possible slot component
;;; name and indicator may not be valid.
;;;
;;; This is for use with tables where rows represent a single frame, i.e.,
;;; attribute tables, or attribute-table-like tables.

(defun find-obsolete-rows-in-table (table exclude-restricted-attributes-p)
  (loop for row in (table-rows table)
	when
	  (loop for cell? in row
 		thereis
 		(and cell?
 		     (not (cell-is-block-p cell?))
 		     (not (valid-attribute-table-text-cell-p
			    cell? exclude-restricted-attributes-p))))
	  collect row using gensym-cons))

(defparameter table-denotation-change-list
  '((attribute-descriptions-for-class . class-specific-attributes)
    (superior-of-defined-class . direct-superiors-of-defined-class)
    (default-overrides-of-system-slots . default-overrides)
    (user-restrictions . object-configuration)
    ))

(defun update-text-cell-denotations-for-slot-name-change
    (table exclude-restricted-attributes-p)
  (loop with need-to-reformat-p = nil
        for row in (table-rows table)
	do
    (loop for cell? in row
	  do
      (when (and cell?
		 (not (cell-is-block-p cell?))
		 (not (valid-attribute-table-text-cell-p
			cell? exclude-restricted-attributes-p)))
	(multiple-value-bind (frame? slot-name?
				     defining-class)
	    (get-slot-represented-by-text-cell-if-any cell?)
	  (when frame?
	    (let ((tail (memq frame? (text-cell-plist cell?)))
		  (replacement-name?
		    (cdr (assoc slot-name? table-denotation-change-list))))
	      (when replacement-name?
		(setf (cadr tail) replacement-name?)
		;; assuming table is attribute-table-like-p
		(let* ((potential-name-cell?
			 (if (and (car row)
				  (not (eq (car row) cell?)))
			     (car row)
			     nil))
		       (name-cell? (if (and potential-name-cell?
					    (not (cell-is-block-p
						   potential-name-cell?)))
				       potential-name-cell?
				       nil))
;		       (type (and name-cell?   -- no longer needed for call below
;				  (get-slot-feature-if-any
;				    (class frame?) slot-name?
;				    'type defining-class)))
		       (old-text? (and name-cell?
				       (text? name-cell?))))
		  (when old-text?
		    (setq need-to-reformat-p t)
		    (setf (text? name-cell?)
			  (make-text-for-cell-identifying-attribute-in-table
			    frame? replacement-name? defining-class
			    ;; type  -- args changed 12/20/95
			    nil))
		    (reclaim-slot-value old-text?)))))))))
	finally
	  (return need-to-reformat-p)))





;;; `Update-attribute-table-rows' is called to change table rows.  The 2nd and
;;; third argus
;;;
;;; When frame-or-rows-to-delete? is a frame, this ensures that table shows all,
;;; and only, the rows that it would show if it were generated from scratch from
;;; table.  (This should be called whenever an attribute is added to frame's
;;; class definition, and it is "safe" to add the attribute to table, as
;;; determined by the predicate safe-to-add-attribute. [No one really calls
;;; that predicate -- review! -mhd])
;;; 
;;; When rows-to-delete is non-nil, this has different behavior: it simply
;;; deletes rows in table that are present in (eq) to rows in rows to delete.
;;;
;;; When delete-if-empty? is true, if table would end up empty, it is generally
;;; deleted, except in the case where it represents itself (e.g., a readout
;;; table, digital clock, or graph), in which case it simply removes itself from
;;; its own representations.  In case delete-if-empty? is nil, the table is left
;;; with one row, the "empty attributes table" row, which says that there are
;;; "NO ATTRIBUTES TO DISPLAY".
;;;
;;; Note that deleting the table can have subtle side effects:
;;;
;;; Deleting table removes the cons pointing to table from the
;;; frame-representations list of the frames it represents.
;;;
;;; Also, when a table is deleted that is currently in the list
;;; stack-of-slot-value-changes, it is removed from this list.  This protocol is
;;; documented in FRAMES5 near the documentation for
;;; stack-of-slot-value-changes.
;;;
;;; Also, callers must be written more carefully, i.e., in order to deal with
;;; the possibility that table can become a deleted, or possibly even a
;;; recycled, frame within their dynamic scope.

(defun update-attribute-table-rows
    (table frame-or-rows-to-delete? &optional delete-if-empty?)
  (unless (listp frame-or-rows-to-delete?)
    (when (virtual-attribute-table-p table)
      (return-from update-attribute-table-rows nil)))
  (let* ((old-frames-this-represents nil)
	 (classic-attribute-table-p (classic-attribute-table-p table))
	 (new-table-rows
	   (or
	    (if (listp frame-or-rows-to-delete?)
		(loop for row in (table-rows table)
		      unless (memq row frame-or-rows-to-delete?)
			collect (copy-for-slot-value row)
			  using slot-value-cons)
		(let ((font-size
			(or (get-apparent-size-of-attribute-table table)
			    (font-for-attribute-tables fonts))))
		  (make-attribute-table-rows
		    frame-or-rows-to-delete?
		    (choose-font-format-per-font-size
		      'class-format font-size)
		    (if (and new-g2-classic-ui-p classic-attribute-table-p)
			'new-attribute-value-format
			(choose-font-format-per-font-size
			  'attribute-value-format font-size))
		    (if (and new-g2-classic-ui-p classic-attribute-table-p)
			'new-attribute-description-format
			(choose-font-format-per-font-size
			  'attribute-description-format font-size))
		    nil nil nil
		    (if (and new-g2-classic-ui-p classic-attribute-table-p)
			'(class component-type)
			nil))))
	    ;; If this ends up with no rows, make it have one empty "no
	    ;; attributes" row.  Unless delete-if-empty? is true.  When it is,
	    ;; we'll delete table at the end.
	    (if delete-if-empty?
		nil
		(make-empty-attributes-table-rows 
		  (choose-font-format-per-fonts-table
		    'attribute-value-format 'font-for-attribute-tables))))))
    (cond
      ((null new-table-rows)
       ;; if new-table-rows is nil, delete-if-empty? must be true, and we're
       ;; just deleting the table
       (cond
	 ((memq table (frame-representations table))
	  (setf (frame-representations table)
		(delete-slot-value-element table (frame-representations table))))
	 (t
	  (delete-frame table)))
       ;; if it's an element at the end of stack-of-slot-value-changes, q.v.,
       ;; it has to be deleted.
       (when (and stack-of-slot-value-changes
		  (memq table (cdr stack-of-slot-value-changes)))
	 (delete-stack-change-element table stack-of-slot-value-changes)))
      (t
       (when (has-subblocks-p table)
	 (delete-any-text-regions table))
       (note-deletion-of-all-text-cells-for-selection table)
       (update-images-of-block table t t)
       ;; record all frames represented by table....
       (do-frames-this-represents (f table)
	 (gensym-push f old-frames-this-represents))
       ;; ... set table rows, and reclaim old
       (setf (table-rows table)
	     (prog1 new-table-rows
	       (reclaim-slot-value (table-rows table))))
       ;; ... pull out ones still represented by table ...
       (do-frames-this-represents (f table)
	 (when (memq f old-frames-this-represents)
	   (setq old-frames-this-represents
		 (delete-gensym-element f old-frames-this-represents))))
       ;; ... for remainder, remove table from frame-representations ...
       (loop for frame in old-frames-this-represents
	     do (remove-from-frame-representations-if-present table frame))
       ;; ... reclaim remainder list
       (reclaim-gensym-list old-frames-this-represents)
       (reformat-table-in-place table)
       (update-images-of-block table nil t)))))

;; What to do about digial clock readout tables that can have a bogus
;; EXPRESSIONS-TO-DISPLAY cell -- these are not currently valid cells, but they
;; appear in the same row next to the valid cell for
;; readout-table-display-value.  For now, both here and in the ultimate caller,
;; update-attribute-tables, they won't be handled the same way.  (In fact,
;; update-attribute-tables will for now not call this for self-representing
;; tables at all.) Note that it's maybe a bug that the class digital-clock
;; allows you to edit the label-to-display attribute, and then creates a cell
;; for that attribute with its text.  That cell in turn looks invalid.  That
;; should be fixed, but note that instances exist.  Note that removing invalid
;; cells only could also be used, though it may not be necessarily the total
;; solution for the problem just mentioned.  (MHD 4/4/95)

;; It would be better if this determined the size used when the table was
;; originally generated, rather than using the current size in FONTS.  There's
;; logic for this for attribute displays (see below), and that could be adapted
;; for attribute displays, easily. -- UPDATE: Done. (MHD 4/1/94)





;;;; Additional Operations on Attribute Tables



;;; A table that is `attribute-table-like-p' has two columns with attribute
;;; names in the first column, and attribute values in the second.  When this is
;;; true then it is safe to assume, that a cell that doesn't represent a block,
;;; is an attribute name, and that cell appears as the car of some row, the
;;; second element of which is representing the attribute it names.

(defun attribute-table-like-p (table)
  (or (attribute-table-p table)
      (attribute-display-p table)
      (short-representation-p table)))

;; What about explanation tables?! (MHD 2/7/94)
;; Beats me.  They only exist in NUPEC?



;;; `Kind-of-attribute-table-if-any' returns the kind of attribute table that
;;; table is, if it is attribute-table-like-p.  If not, it returns nil.
;;;
;;; The value returned, kind, would be one of ATTRIBUTE-DISPLAY,
;;; ATTRIBUTE-TABLE, or SHORT-REPRESENTATION.

(defun kind-of-attribute-table-if-any (table)
  (cond
    ((attribute-display-p table) 'attribute-display)
    ((attribute-table-p table) 'attribute-table)
    ((short-representation-p table) 'short-representation)))
  



;;; `Get-attribute-table-large-class-format-name' returns the large size format
;;; name for the class value cell (aka, table-header) for any kind of
;;; attribute-table-like table.  Kind should be one of ATTRIBUTE-DISPLAY,
;;; ATTRIBUTE-TABLE, or SHORT-REPRESENTATION.  (See
;;; kind-of-attribute-table-if-any.)
;;;
;;; `Get-attribute-table-large-value-format-name' does the same for the
;;; non-class value cells (typically, the cells along the right-hand column) of
;;; any attribute-table-like table.
;;;
;;; `Get-attribute-table-large-description-format-name' does the same for the
;;; description cells (typically, the cells along the left-hand column) of any
;;; attribute-table-like table.

(defun get-attribute-table-large-class-format-name (kind)
  (case kind
    (attribute-display 'large-attribute-display-class-format)
    (attribute-table 'class-format)
    (short-representation 'short-representation-class-format)))


(defun get-attribute-table-large-value-format-name (kind)
  (case kind
    (attribute-display 'large-attribute-display-value-format)
    (attribute-table 'attribute-value-format)
    (short-representation 'attribute-value-format)))

(defun get-attribute-table-large-description-format-name (kind)
  (case kind
    (attribute-display 'large-attribute-display-description-format)
    (attribute-table 'attribute-description-format)
    (short-representation 'attribute-description-format)))





;;; `Get-apparent-size-of-attribute-table' returns the apparent size (SMALL,
;;; LARGE, or EXTRA-LARGE) for any attribute-table-like table based on the
;;; formats already present in the existing (value) cells of the table.

(defun get-apparent-size-of-attribute-table (table)
  (loop with kind = (kind-of-attribute-table-if-any table)
	for row in (table-rows table)
	as value-cell? = (car (last row)) ; maybe never nil
	as slot-name?
	  = (if (and value-cell?
		     (not (cell-is-block-p value-cell?))) ; maybe never true
		(multiple-value-bind (frame slot-name)
		    (get-slot-represented-by-text-cell-if-any value-cell?)
		  (declare (ignore frame))
		  slot-name))
	as text-cell-format-name?
	  = (if value-cell?
		(name-or-names-for-frame
		  (text-cell-format value-cell?)))
	as large-font-format-name?	; find an abstraction!
	  = (case slot-name?
	      (class (get-attribute-table-large-class-format-name kind))
	      (t (get-attribute-table-large-value-format-name kind)))
	thereis
	  (and large-font-format-name?
	       (cond
		 ((eq text-cell-format-name? large-font-format-name?)
		  'large)
		 ((eq text-cell-format-name?
		      (corresponding-small-font-format-name
			large-font-format-name?))
		  'small)
		 ((eq text-cell-format-name?
		      (corresponding-extra-large-font-format-name
			large-font-format-name?))
		  'extra-large)))))






;;; `Make-and-insert-attribute-table-row-for-slot' inserts a row in an attribute
;;; table in "normal order", i.e., as it would appear in a classic attribute
;;; table.  We assume the rows are sorted according to this order prior to our
;;; being here (i.e., at all times).  But all that would happen if that were not
;;; true is that the insertion might not happen at the right spot.
;;;
;;; If always-exclude-name? is true, this doesn't create the column for the name
;;; (the "description") of the attribute, even it's "normally" supposed to be
;;; there.  This is intended to be used (supplying true) by the command to add
;;; to an attribute display, which just wants to add a row containing the value
;;; cell.
;;;
;;; If the designated slot doesn't belong in the table (e.g., due to user
;;; restrictions), it won't be added, and nil will be returned.  When a row
;;; is added, which normally should be the case, this return value is true.
;;;
;;; This does not check for duplication.  If a slot is already present, this
;;; will be happy to add it again.  It would appear adjacent to its duplicate.
;;;
;;; This should only be called when table is not drawn on any workspaces (i.e.,
;;; after it has been erased, if necessary).  After it is called, the table
;;; needs to be reformatted (i.e., using reformat-table-in-place) before it is
;;; redrawn.
;;;
;;; [If users (or the system) reorder their slots, should we visit every
;;; attribute table and normalize their order?!  That's what it would take to
;;; ensure that this never inserts in the wrong order.  That or a more
;;; complicated implmementation here .  Currently, that's not done. (MHD
;;; 5/2/94)]

(defun make-and-insert-attribute-table-row-for-slot
    (table frame slot-description always-exclude-name?)
  (let* ((slot-name (pretty-slot-name slot-description))
	 (defining-class?
	     (unless (eq slot-name 'class)
	       (when (slot-name-needs-qualification-p
		       slot-description
		       (class-description-slot frame))
		 (defining-class slot-description))))
	 (remaining-table-rows-trailer? nil)
	 (remaining-table-rows (table-rows table))
	 (first-of-remaining-rows (car remaining-table-rows)))
    (do-attribute-table-slots
	(frame nil nil nil t)	; exclude restricted slots
	(slot-name-in-table defining-class-in-table?)
      
      ;; When we're at the slot we want to insert, insert it at
      ;; the front of remaining-rows, and return:
      (when (and (eq slot-name-in-table slot-name)
		 (eq defining-class-in-table? defining-class?))
	(let* ((new-remaining-table-rows
		 (slot-value-cons
		   (make-additional-attribute-table-row
		     table frame slot-description always-exclude-name?)
		  remaining-table-rows)))
	  (if remaining-table-rows-trailer?
	      (setf (cdr remaining-table-rows-trailer?)
		    new-remaining-table-rows)
	      (setf (table-rows table)
		    new-remaining-table-rows)))
	(return t))

      ;; When we're at the slot for the first row in remaining-rows,
      ;; advance remaining-rows:
      (when (search-row-for-text-cell-representing-slot
	      first-of-remaining-rows nil
	      frame slot-name-in-table defining-class-in-table?)
	(setq remaining-table-rows-trailer? remaining-table-rows)
	(setq remaining-table-rows (cdr remaining-table-rows))
	(setq first-of-remaining-rows (car remaining-table-rows))))))




;;; `Make-additional-attribute-table-row' makes an additional row for table,
;;; which should be an attribute table, containing a text cell representing the
;;; value of the designated slot in frame.
;;;
;;; The name (description) of the slot is also included if it is appropriate to
;;; do so.  If always-exclude-name? is true, it never includes the name.
;;;
;;; It is determined that the resulting row should always be 2-long if the first
;;; of the existing rows in table is 2-long.  Otherwise, it's 2-long only if the
;;; name is included.

(defun make-additional-attribute-table-row
    (table frame slot-description always-exclude-name?)
  (let* ((slot-name (pretty-slot-name slot-description))
	 (defining-class?
	     (unless (eq slot-name 'class)
	       (when (slot-name-needs-qualification-p
		       slot-description (class-description-slot frame))
		 (defining-class slot-description))))
	 (kind (kind-of-attribute-table-if-any table))
	 (size (get-apparent-size-of-attribute-table table)))
    (make-attribute-table-row
      frame slot-name defining-class? nil nil
      (slot-features slot-description)
      (if (eq slot-name 'class)
	  (class frame)
	  (get-slot-description-value frame slot-description))
      always-exclude-name?
      (cdr (car (table-rows table)))	; in two columns?
      (choose-font-format-per-font-size
	(get-attribute-table-large-class-format-name kind)
	size)
      (choose-font-format-per-font-size
	(get-attribute-table-large-value-format-name kind)
	size)
      (choose-font-format-per-font-size
	(get-attribute-table-large-description-format-name kind)
	size)
      nil)))



;;; `Table-represents-some-frames-p' returns true if table represents at least
;;; one frame.  If it represents none, this returns nil.
;;;
;;; Note that this can be used to tell if a table returned as an attribute table
;;; could not display any slots, i.e., in the case where it just displays "NO
;;; ATTRIBUTES TO DISPLAY".

(defun table-represents-some-frames-p (table)
  (do-frames-this-represents (frame table)
    (return-from table-represents-some-frames-p t))
  nil)





;;;; Short Representations



;;; A `short representation' is, structurally, a table of which the
;;; predicate short-representation-p is true.  Conceptually, it is a
;;; representation for objects in which, in the case of entities, simply
;;; one or more designations of the entity, and, in the case of
;;; statements, just the text of the statement, are shown.  When a short
;;; representation is selected, the menu posted has the choices "hide
;;; short representation" (instead of "hide table") and "table", which
;;; would pop up a normal attributes table.  Also, the "go away" feature
;;; is suppressed when clicking on the designations (in the entities
;;; case).

;;; Short-representation-p is true if table is a short representation.
;;; At present, this is indicated by having a table format whose single
;;; name is the symbol short-representation-table-format.

(defun-simple short-representation-p (table)
  (eq (name-or-names-for-frame (table-format table))
      'short-representation-table-format))

;; Changed to a simple function from a macro -- not used in speed-critical
;; functions, and the function wanted to be forward-referenced from earlier in
;; this module (from attribute-table-like-p, where the other predicates are also
;; functions, by the way).  (MHD 2/7/94)



;;; Make-short-representation makes a short representation for frame.
;;; It adds the new short representation table to the frame (or its
;;; parent, in the case of embedded rules) as a frame representation.
;;; It returns the new short representation table, which presumably is
;;; then added to a workspace and displayed.

;;; When make-short-representation is called with an embedded rule, the
;;; text is shown (from the box-translation-and-text-of-embedded-rule
;;; slot of the parent) and the parent frame is represented.  In general
;;; and in this case in particular,
;;;
;;;   (memq   ; may return non-nil!
;;;     (make-short-representation frame)
;;;     (frame-representations frame))
;;;
;;; may return nil.  (In this case, (frame-representations <parent
;;; frame>) would have contained the short representation.

;;; Unless it is nil, table-class? specifies the class for the resulting
;;; representation table.

;;; [New behavior as of the 6.0 release pending 1/10/99: (MHD)] If frame is
;;; transient, table is explicitly set transient.  Otherwise, it is left neither
;;; permanent nor transient.

(defun make-short-representation
    (frame &optional table-class? font-size? background-color?)
  (let* (name-of-slot-to-represent defining-class-for-slot-to-represent?
	 (text-box-format-name			; this binding usually correct, but
	   (choose-font-format-per-font-size	;   gets overridden below for boxes
	     'short-representation-class-format	; assumed "large"!
	     font-size?))
	 table)
    ;; This is extremely unmodular code. The special case for
    ;; procedure-invocation below is wrong, and was not changed when
    ;; procedure-invocations were redesigned. Perhaps name-of-slot-to-represent
    ;; should be a property, so that it could be maintained in the appropriate
    ;; module. ML, 11/14/91 
    (cond
      ((frame-of-class-p frame 'text-box)
       (multiple-value-bind
	   (parent-of-embedded-rule? slot-name defining-class?)
	   (if (frame-of-class-p frame 'rule)
	       (get-kb-parent-information frame))
	 (cond
	   (parent-of-embedded-rule?			; special hack for actions buttons
	    (setq frame parent-of-embedded-rule?)	;   with their embedded rules!!
	    (setq name-of-slot-to-represent slot-name)	;   (MHD 9/1/88)
	    (setq defining-class-for-slot-to-represent?
		  defining-class?))
	   (t
	    (setq name-of-slot-to-represent 'box-translation-and-text)
	    (setq defining-class-for-slot-to-represent? nil)
	    (setq text-box-format-name
		  (choose-font-format-per-font-size
		    (default-text-box-format-name frame)	; assumed "large"!
		    font-size?))))))
;      ((frame-of-class-p frame 'procedure-invocation)
;       (setq name-of-slot-to-represent 'procedure-invocation-argument-list))
      (t
       (setq name-of-slot-to-represent 'class)))
    (setq table
	  (make-or-reformat-table
	    (slot-value-list
	      (slot-value-list
		(make-text-cell-for-slot
		  frame
		  name-of-slot-to-represent
		  defining-class-for-slot-to-represent?
		  (get-type-of-slot-if-any
		    frame name-of-slot-to-represent
		    defining-class-for-slot-to-represent?)
		  text-box-format-name)))
	    'short-representation-table-format nil table-class?))
    (add-frame-representation-if-necessary table frame)

    ;; For now, we implement the background color option by just looping through
    ;; each cell and setting its background color; later, we may choose to
    ;; implement this by using a different table format.
    (when background-color?
      (change-background-color-of-short-representation-table
	table background-color?))
    (when (transient-p frame)		; For 6.0 anomaly HQ-2611709. (MHD 1/10/99)
      (set-transient-and-propagate table nil))    
    table))

(def-table-format short-representation-table-format
  table-background-color? nil			; maybe "light-gray" when color mapping
						;   works for B&W systems
						; -- was white (MHD 8/3/89)
  table-row-boundary-width 1
  table-column-boundary-width 1)

(def-table-format-spot-generator short-representation-table-format (short-representation-table mouse-pointer)
  (generate-spot-for-input-table
    short-representation-table
    mouse-pointer
    (make-short-representation-table-spot)))


(def-text-cell-format short-representation-class-format	; like class-format without
  text-cell-line-quadding? center			;   white-on-black
  text-cell-lines-justified? nil
  text-cell-left-margin 10
  text-cell-top-margin 10
  text-cell-right-margin 10
  text-cell-bottom-margin 10
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 20
  text-cell-font-map (hm18)			;was recently swiss20
  text-cell-line-height 20
  text-cell-baseline-position 16
  text-cell-line-spacing 3
  default-word-spacing #.(convert-to-text-width 6)
  minimum-format-width-for-text-cell 350)


(def-text-cell-format small-short-representation-class-format	; like class-format without
  text-cell-line-quadding? center
  text-cell-lines-justified? nil
  text-cell-left-margin 8
  text-cell-top-margin 4
  text-cell-right-margin 8
  text-cell-bottom-margin 4
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 8
  text-cell-font-map (hm14)
  text-cell-line-height 18
  text-cell-baseline-position 14
  text-cell-line-spacing 3
  default-word-spacing #.(convert-to-text-width 4)
  minimum-format-width-for-text-cell 300)

(setf (corresponding-small-font-format-name 'short-representation-class-format)
      'small-short-representation-class-format)


(def-text-cell-format extra-large-short-representation-class-format	; like class-format without
  text-cell-line-quadding? center
  text-cell-lines-justified? nil
  text-cell-left-margin 15
  text-cell-top-margin 10
  text-cell-right-margin 15
  text-cell-bottom-margin 8
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 14
  text-cell-font-map (hm24)
  text-cell-line-height 26
  text-cell-baseline-position 21
  text-cell-line-spacing 3
  default-word-spacing #.(convert-any-number-to-text-width-at-compile-time 8.75) ; 5/8 en
  minimum-word-spacing #.(convert-to-text-width 7)	          ; 1/2 en
  maximum-word-spacing #.(convert-to-text-width 21)	          ; 3/2 en
  minimum-format-width-for-text-cell 400)

(setf (corresponding-extra-large-font-format-name 'short-representation-class-format)
      'extra-large-short-representation-class-format)







;;; `Make-short-representation-for-queries', if string-to-look-for? is not specified,
;;; returns a short representation table representing only the box-translation-and-text
;;; or class slot of frame, according to whether frame is a text box or not.  If
;;; string-to-look-for? is specified, a short representation table is returned only if
;;; the representation of some editable slot of frame contains string-to-look-for? or,
;;; where specified, second-string-to-look-for?.  In this second case, the table will
;;; contain representations for the box-translation-and-text or class slot plus editable
;;; slots in which one or both strings occur, and a second value will be returned to
;;; indicate if the representation of the box-translation-and-text or class slot contains
;;; either of the strings or not, where nil indicates that it does and the slot name
;;; indicates that it does NOT.  If only-find-string-to-look-for?-if-editable? is true,
;;; string-to-look-for? will not be matched in slots that are not editable because
;;; they either are not of an editable type or, unless frame is a message, because
;;; they have been stripped.

;;; When candidate-denotations-of-slots-to-describe-or-search? is specified, it
;;; should be a list of the slot denotations, or aliases thereof, of slots to
;;; always include in a resulting table and to limit the search to.  This list
;;; is not recycled by this function.

(defun make-short-representation-for-queries
    (frame
      string-to-look-for?
      observe-word-boundaries?
      only-find-string-to-look-for?-if-editable?
      candidate-denotations-of-slots-to-describe-or-search?
      just-find-key-slot-name-p)
  (let* ((attributes-table-description? nil)
	 (slot-denotations-for-occurrences
	   (if string-to-look-for?
	       (loop as (slot-name defining-class? text-representation-for-slot-value?)
			in (setq attributes-table-description?
				 (make-attributes-table-description
				   frame t
				   candidate-denotations-of-slots-to-describe-or-search?))
		     as text? = (or text-representation-for-slot-value?
				    (cdr (get-slot-value frame slot-name defining-class?)))
		     when (and text?
			       (or (not only-find-string-to-look-for?-if-editable?)
				   (and (type-of-slot-if-editable
					  (class frame) slot-name nil defining-class?)
					(or (transient-p frame)
					    (permanent-block-p frame))
					;; if a text slot, not stripped:
					(or text-representation-for-slot-value?
					    (not (stripped-text-p text?))
					    (frame-of-class-p frame 'message))
					(edit-attribute-allowed-p
					  frame slot-name
					  defining-class?)))
			       (find-string-in-text-for-inspect
				 string-to-look-for? text? observe-word-boundaries?))
		       collect (make-slot-name-denotation slot-name defining-class?)
			 using slot-value-cons)))
	 (key-slot-name-if-no-occurrence? nil)
	 (slot-denotations-for-table
	   (if candidate-denotations-of-slots-to-describe-or-search?
	       (if (or (null string-to-look-for?)
		       slot-denotations-for-occurrences)
		   (let ((attributes-table-description
			   (make-attributes-table-description
			     frame t
			     candidate-denotations-of-slots-to-describe-or-search?
			     nil t)))
		     (prog1
			 (nconc
			   (loop for (slot-name defining-class?)
				     in attributes-table-description
				 unless (slot-denotation-member
					  slot-name defining-class?
					  slot-denotations-for-occurrences)
				   collect (make-slot-name-denotation slot-name defining-class?)
				     using slot-value-cons)
			   slot-denotations-for-occurrences)
		       (reclaim-slot-value attributes-table-description))))
	       (if (or (null string-to-look-for?)
		       slot-denotations-for-occurrences)
		   (let ((key-slot-name
			   (if (text-box-p frame)
			       'box-translation-and-text
			       'class)))
		     (if (and string-to-look-for?
			      (slot-denotation-member
				key-slot-name
				nil ; system slots never qualified now.
				slot-denotations-for-occurrences))
			 slot-denotations-for-occurrences
			 (slot-value-cons
			   (setq key-slot-name-if-no-occurrence? key-slot-name)
			   slot-denotations-for-occurrences))))))
	 (attribute-table?
	   (and slot-denotations-for-table
		(not just-find-key-slot-name-p)
		(make-attributes-table
		  frame
		  'short-representation-table-format 'short-representation-class-format
		  nil nil slot-denotations-for-table t))))
    (when attributes-table-description?
      (reclaim-slot-value attributes-table-description?))
    (cond
      (slot-denotations-for-table
       (reclaim-slot-value-tree slot-denotations-for-table)
       (values t attribute-table? key-slot-name-if-no-occurrence?))
      (t
       (values just-find-key-slot-name-p nil key-slot-name-if-no-occurrence?)))))

;; I added the candidate-denotations-of-slots-to-describe-or-search? arg.

;; Include all appropriate features of make-short-representation herein, so that
;; this may be used for Inspect generally.

;; Consider having this include, where string-to-look-for? is specified, representations
;; of NON-EDITABLE slots in which one or both strings occur, since replace-editable-
;; occurrences-of-string-in-table will ignore them anyway.



(defun change-background-color-of-short-representation-table
    (table background-color)
  (loop for row in (table-rows table)
	do (loop for cell? in row
		 when (and cell?
			   (not (cell-is-block-p cell?)))
		   do (change-color-of-text-cell
			table cell? nil
			background-color nil nil))))





;;;; Attribute Displays



;;; An `attribute display' ...  is like a miniature attribute table.  They can
;;; have one or two columns per row.  If there are two, then rows having a
;;; single text cell have nils in the first column so that the value spans the
;;; row.  Attribute names may not be displayed unless they could otherwise be
;;; displayed in an attribute table; i.e., the attribute name for the
;;; table-header (class) or text (box-translation- and-text,
;;; procedure-definition) slots may not be displayed.
  
;;; Constraints
;;;
;;; Attributes (rows) are always kept in "normal order", i.e. the order in which
;;; they would appear in an attribute table.  The only time this constraint can
;;; get violated is when the class definition changes through user edits or
;;; merging such that the "normal order" for attribute tables would change.
;;; When the constraint is violated, the worst thing that happens is the
;;; attributes may not be able to be kept in correct order from then on.
;;;
;;; There is always at least one table row.  I.e., (table-rows table) is never
;;; nil.  (This is an internal representation detail.  Is this true of tables,
;;; in general?)
;;; 
;;; If any attribute is showing its name, then all rows have either a text cell
;;; with an attribute name or nil.  When there are no rows showing the name,
;;; then no nils appear in any rows. (This is an internal representation
;;; detail.)
;;;
;;; The attribute name cannot appear in an attribute display if it could not
;;; appear in an attribute table; i.e., you cannot see the name of the text or
;;; table-header attributes of items.
;;;
;;; In user interaction situation, addition or deletion of attributes is
;;; protected by attribute visibility user restrictions.  And menus that result
;;; from clicking on attribute displays strictly obey the same user restrictions
;;; as for attribute tables, i.e., table menu choices.



;;; `Attribute-display-p' is true of a table that is an attribute display.
;;; Attribute displays are considered "attribute-table-like", so this is a
;;; component of the attribute-table-like-p predicate.  See
;;; attribute-table-like-p, defined above.

(defun-simple attribute-display-p (table)
  (eq (name-or-names-for-frame (table-format table))
      'attribute-display-table-format))



;;; `Attributes-can-be-added-to-attribute-display-p' is true of an attribute
;;; display, table, representing frame if there are still attributes that can be
;;; shown.
;;;
;;; Note that this excludes slots restricted (via user restrictions), those for
;;; the current workstation if called from the user interface, i.e., when
;;; servicing-workstation? is true.

(defun attributes-can-be-added-to-attribute-display-p (table frame)
  (do-attribute-table-slots
      (frame nil nil nil t)		; exclude restricted slots
      (slot-name defining-class? alias? slot-features type-of-slot)
    (if (null (get-text-cell-representing-slot-if-any
		table frame slot-name defining-class?))
	(unless (eq (or alias? slot-name) 'class)	; ??
	  (return t)))))

;; Note that this could just as well be used for regular attribute tables, I
;; think without modification.  (But if it needed to be, it should be abstracted
;; first.)



;;; `make-menu-choice-list-for-missing-attribute-display-attributes' returns a
;;; list of menu items, to be displayed in the submenu whose title is
;;; add-another-attribute for an attribute display, table, representing frame.
;;;
;;; The result is a slot value that is suitable as a "menu item"; see the
;;; definition of the concept menu-item, elsewhere.

(defun make-menu-choice-list-for-missing-attribute-display-attributes
    (table frame for-new-style-menu?)
  (let ((result nil))
    (do-attribute-table-slots (frame nil nil nil t) ; exclude restricted slots
	(slot-name defining-class? alias? slot-features type-of-slot)
      (if (null (get-text-cell-representing-slot-if-any
		  table frame slot-name defining-class?))
	  (unless (eq (or alias? slot-name) 'class)	; ??
	    (let* ((string
		     (tformat-text-string "~NQ" (or alias? slot-name) defining-class?))
		   (value
		     (make-slot-name-denotation slot-name defining-class?))
		   (menu-item
		     (if for-new-style-menu?
			 (slot-value-list 'choice string value)	; format for new-style menu choice
			 (slot-value-list string value))))
	      (slot-value-push menu-item result)))))
    (nreverse-canonically result)))


;;; Get-or-make-font-format-per-existing-attribute-display determines the font
;;; size of attribute-display based on the existing format(s) in its cell(s),
;;; and returns the appropriate format frame based on that information.

;;; If it is unable to determine the size for any reason, the size is just the
;;; large size (the default); that should happen only rarely, however, if at
;;; all.  One way it might happen is if formats are changed (by developers) and
;;; not brought up-to-date (by users), but even that problem might be made not
;;; to happen (i.e., get fixed by us developers) some day.

(defun get-or-make-font-format-per-existing-attribute-display
       (attribute-display large-font-format-name)
  (get-or-make-format-frame
    (choose-font-format-per-font-size
      large-font-format-name
      (get-apparent-size-of-attribute-table attribute-display))))



(defun add-another-attribute-to-attribute-display
    (table frame slot-name class-qualifier?)
  (let* ((slot-description
	   (if (eq slot-name 'class)
	       pseudo-class-slot-description
	       (get-slot-description-of-frame slot-name frame class-qualifier?)))
	 (class-description
	   (class-description-slot frame))
	 (defining-class?
	     (unless (eq slot-name 'class)
	       (when (slot-name-needs-qualification-p
		       slot-description class-description)
		 (defining-class slot-description)))))
    (unless (get-text-cell-representing-slot-if-any ; make assumption? skip check?
	      table frame slot-name defining-class?)
      (update-images-of-block table t t)
      (make-and-insert-attribute-table-row-for-slot
	table frame slot-description t)
      (when (and g2-has-v5-mode-windows-p
		 (frame-of-class-p table 'item)
		 (table-rows table))
	(send-ws-representations-item-virtual-attribute-change
	  table (virtual-attribute 'table-rows) nil))
      (reformat-table-in-place table)
      (update-images-of-block table nil t))))



(defun attributes-can-be-deleted-from-attribute-display-p (table frame)
  (declare (ignore frame))
  (cdr (table-rows table)))			; if more than one attribute shown


;;; Delete-attribute-from-attribute-display ...  this will get rid of table if
;;; this ends up deleting its last row.  Note, however, that the menu interface
;;; doesn't call this for that purpose in practice; if there is only one row
;;; left, the delete-attribute choice is not offered, and only the
;;; hide-attribute-display is offered for the purpose of deleting the table.

(defun delete-attribute-from-attribute-display
    (table frame slot-name defining-class? text-cell)
  (declare (ignore slot-name defining-class?))
  (loop for remaining-rows on (table-rows table)
	when (memq text-cell (car remaining-rows))
	  do (loop for cell? in (car remaining-rows) ; Deleting entire row.
		   when cell?
		     do (note-deletion-of-text-cell-for-selection cell?))
	     (update-images-of-block table t t)
	     (setf (table-rows table)
		   (delq (car remaining-rows) (table-rows table)))
	     (setf (cdr remaining-rows) nil)
	     (reclaim-slot-value remaining-rows)
	     (reformat-table-in-place table)
	     (update-images-of-block table nil t)
	     (when (and g2-has-v5-mode-windows-p
			(frame-of-class-p table 'item)
			(table-rows table))
	       (send-ws-representations-item-virtual-attribute-change
		 table (virtual-attribute 'table-rows) nil))
	     (loop-finish)
	finally
	  (when (null (table-rows table))
	    (remove-from-frame-representations-if-present table frame)
	    (delete-frame table)
	    )))

;; The above is partially based on the def-slot-value-reclaimer for table-rows.
;; (MHD 6/5/91)


;;; Add-attribute-name-to-attribute-display ...

(defun add-attribute-name-to-attribute-display (table text-cell)
  ;; fix callers to pass in defining-class?, and reorder arglist!
  ;; (MHD 2/16/94)
  (update-images-of-block table t t)
  (loop with name-cell = nil
	with row-index = -1
	for rows on (table-rows table)
	do (incff row-index)
	when (null (cdr (car rows)))
	  do (setf (car rows)		; fill first column if missing second
		   (slot-value-cons nil (car rows)))
	when (eq (second (car rows)) text-cell)
	  do (multiple-value-bind (f sn dc scn sci) ; some/all can be nil
		 (get-slot-represented-by-text-cell-if-any text-cell)
	       (declare (ignore scn sci)) ; use?! (MHD 2/17/94)
	       (unless (or (first (car rows)) ; usu. unnec.
			   (null f)	; usu. unnec.
			   (get-slot-feature-if-any ; assume?
			     (class f)
			     sn
			     'do-not-identify-in-attribute-tables
			     dc))
		 (setq name-cell
		       (make-text-cell
			 (make-text-for-cell-identifying-attribute-in-table
			   f sn dc
			   ;; (get-slot-feature-if-any (class f) sn 'type dc)  Arg removed.  -jra 12/21/96
			   nil)
			 (get-or-make-font-format-per-existing-attribute-display
			   table 'large-attribute-display-description-format)))
		 (setf (first (car rows)) name-cell)))
	     (when (and g2-has-v5-mode-windows-p
			(frame-of-class-p table 'item))
	       (send-ws-representations-item-change-macro
		 table
		 (allocate-evaluation-structure-inline
		   'attribute-name 'table-rows 
		   'row-index row-index
		   'column-index 0
		   'cell-attribute-name
		   'cell-display-text
		   'new-value (exported-cell-text name-cell)))))
  (reformat-table-in-place table)
  (update-images-of-block table nil t))



;;; `Delete-attribute-name-from-attribute-display' ... text-cell can be either
;;; the cell showing the name of the attribute or the text cell showing its
;;; value.

(defun delete-attribute-name-from-attribute-display (table text-cell)
  (update-images-of-block table t t)
  (let ((row-index -1))
    (loop for row in (table-rows table)
	  as first-cell? = (car row)
	  do (incff row-index)
	  when (memq text-cell row)
	    return				; no meaningful value
	    (unless (null first-cell?)
	      ;; Name cells are not generally selected, but just in case.
	      (note-deletion-of-text-cell-for-selection first-cell?)
	      (setf (car row) nil)
	      (reclaim-slot-value first-cell?)))
    ;; collapse back to a single column table if appropriate:
    (if (loop for row in (table-rows table)
	      always (null (first row)))
	(loop for table-rows on (table-rows table)
	      as head-row-cons = (car table-rows)
	      do (setf (car table-rows)
		       (cdr head-row-cons))
		 (setf (cdr head-row-cons) nil)
		 (reclaim-slot-value-cons head-row-cons)))
    (when (and g2-has-v5-mode-windows-p
	       (frame-of-class-p table 'item))
      (send-ws-representations-item-change-macro
	table
	(allocate-evaluation-structure-inline
	  'attribute-name 'table-rows 
	  'row-index row-index
	  'column-index 0
	  'cell-attribute-name
	  'cell-display-text))))
  (reformat-table-in-place table)
  (update-images-of-block table nil t))




;;; `Attribute-name-shown-in-attribute-display-p' returns true if text-cell, a
;;; text cell in an attribute display, is not in a row showing an attribute's
;;; "description" (i.e., its attribute name).

(defun attribute-name-shown-in-attribute-display-p (table text-cell)
  (get-attribute-description-text-cell table text-cell))



;;; `Attribute-name-can-be-added-to-attribute-display-p' returns true if
;;; text-cell, a text cell in an attribute display, is not in a row showing an
;;; attribute's "description" (i.e., its attribute name), and may do so.

(defun attribute-name-can-be-added-to-attribute-display-p (table text-cell)
  (and (null (get-attribute-description-text-cell
	       table text-cell))
       (let  ((value-text-cell (get-attribute-value-text-cell table text-cell)))
	 (multiple-value-bind
	     (frame? slot-name? defining-class? slot-component-name?)
	     (get-slot-represented-by-text-cell-if-any value-text-cell)
	   (when frame?
	     (let ((features
		     (get-attribute-features
		       (class frame?)
		       slot-name? defining-class?
		       slot-component-name?)))
	       (not (feature-assq
		      'do-not-identify-in-attribute-tables
		      features))))))))



(declare-system-procedure-function g2-add-attribute-display t)

(defun-funcallable g2-add-attribute-display (item slot-name class-qualifier?)
  (unless (symbolp class-qualifier?)
    (setq class-qualifier? nil))
  (add-slot-representation-as-attribute-display item slot-name class-qualifier?))

(declare-system-procedure-function g2-delete-attribute-display t)

(defun-funcallable g2-delete-attribute-display
    (item slot-name class-qualifier?)
  (unless (symbolp class-qualifier?)
    (setq class-qualifier? nil))
  (loop for subblock being each subblock of item
	with cell?
	do
    (when (and (table-p subblock)
	       (attribute-display-p subblock))
      (setq cell?
	    (get-text-cell-representing-slot-if-any
	      subblock item slot-name class-qualifier?))
      (when cell?
	;; more than one
	(cond ((attributes-can-be-deleted-from-attribute-display-p subblock item)
	       (delete-attribute-from-attribute-display
		 subblock item slot-name class-qualifier? cell?))
	      (t
	       (delete-frame subblock)))))))

(declare-system-procedure-function g2-add-name-of-attribute-to-attribute-display t)

(defun-funcallable g2-add-name-of-attribute-to-attribute-display
    (item slot-name class-qualifier?)
  (unless (symbolp class-qualifier?)
    (setq class-qualifier? nil))
  (loop for subblock being each subblock of item
	with cell?
	do
    (when (and (table-p subblock)
	       (attribute-display-p subblock))
      (setq cell?
	    (get-text-cell-representing-slot-if-any
	      subblock item slot-name class-qualifier?))
      (when (and cell?
		 (attribute-name-can-be-added-to-attribute-display-p subblock cell?))
	(add-attribute-name-to-attribute-display subblock cell?)))))

(declare-system-procedure-function g2-hide-name-of-attribute-from-attribute-display t)

(defun-funcallable g2-hide-name-of-attribute-from-attribute-display
    (item slot-name class-qualifier?)
  (unless (symbolp class-qualifier?)
    (setq class-qualifier? nil))
  (loop for subblock being each subblock of item
	with cell?
	do
    (when (and (table-p subblock)
	       (attribute-display-p subblock))
      (setq cell?
	    (get-text-cell-representing-slot-if-any
	      subblock item slot-name class-qualifier?))
      (when cell?
	(when (attribute-name-shown-in-attribute-display-p subblock cell?)
	  (delete-attribute-name-from-attribute-display subblock cell?))))))

;;; Add-slot-representation-as-attribute-display ... all of the optional
;;; arguments (user-x-offset?, et al) are as described for
;;; add-attribute-display-as-subblock, to which they are all passed.

(defun add-slot-representation-as-attribute-display
    (block slot-name class-qualifier?
	   &optional 
	   user-x-offset? user-y-offset?
	   x-offset? y-offset?
	   advanced-spec?)
  (let* ((denotations-of-candidate-slots-to-describe
	   (slot-value-list
	     (denote-slot-using-slot-value-conses
	       (get-slot-description-of-frame
		 slot-name block class-qualifier?)
	       (class-description-slot block))))
	 (denotations-of-candidate-slots-for-which-to-suppress-name
	   (copy-for-slot-value
	     denotations-of-candidate-slots-to-describe))
	 (attribute-display
	   (make-attributes-display-table
	     block
	     denotations-of-candidate-slots-to-describe
	     denotations-of-candidate-slots-for-which-to-suppress-name)))
    (add-attribute-display-as-subblock
      attribute-display block
      user-x-offset? user-y-offset?
      x-offset? y-offset?
      advanced-spec?)
    (reclaim-slot-value denotations-of-candidate-slots-to-describe)
    (reclaim-slot-value denotations-of-candidate-slots-for-which-to-suppress-name)))




;;; Make-attributes-display-table ... 

(defun make-attributes-display-table
       (block denotations-of-candidate-slots-to-describe
	 denotations-of-slots-for-which-to-suppress-name)
  (make-attributes-table
    block
    'attribute-display-table-format
    (choose-font-format-per-fonts-table
      'large-attribute-display-class-format 'font-for-attribute-displays)
    (choose-font-format-per-fonts-table
      'large-attribute-display-value-format 'font-for-attribute-displays)
    (choose-font-format-per-fonts-table
      'large-attribute-display-description-format 'font-for-attribute-displays)
    (or denotations-of-candidate-slots-to-describe 'none) ; hack JED 9/1/94
    nil denotations-of-slots-for-which-to-suppress-name))



;;; Make-attribute-displays-per-specs ... Normally, for each spec in
;;; attribute-display-specs, this creates a table, and then adds that table as a
;;; subblock of entity.  However, in the case where there are no attributes to
;;; display, this either deletes the table or never creates it, and doesn't add
;;; the table as a subblock, and returns nil.

(defun make-attribute-displays-per-specs
    (entity attribute-display-specs)
  (loop for spec in attribute-display-specs
	do (make-attribute-display-per-one-spec entity spec)))

(defun make-attribute-display-per-one-spec (entity spec)
  (loop with attribute-part = (first spec)
	with offset-part = (second spec)
	for x in attribute-part
	as show-name? = (not (name-denotation-p x)) ; if name is consed
	as slot-name-denotation
	   = (if (name-denotation-p x)
		 x		; either x is a name denotation, or it
		 (car x))	;   should be a cons whose car is one
	as attribute-name = (unqualified-name slot-name-denotation)
	as slot-name		; only used for system slots, which
				;   are, in turn, never qualified
	   = (unalias-slot-name-if-necessary attribute-name entity)
	as class-qualifier? = (class-qualifier slot-name-denotation)
	as trusted-denotation?
	   = (if (eq attribute-name 'table-header)
		 (make-slot-name-denotation 'table-header nil)
		 (let ((slot-description?
			 (get-slot-description-of-frame
			   slot-name entity class-qualifier?)))
		   (when slot-description?
		     (denote-slot-using-slot-value-conses
		       slot-description? (class-description-slot entity)))))
	when trusted-denotation?
	  collect trusted-denotation?
	    into denotations-of-candidate-slots-to-describe
	    using slot-value-cons
	  and when (not show-name?)
		collect (copy-for-slot-value trusted-denotation?)
		  into denotations-of-slots-for-which-to-suppress-name
		  using slot-value-cons
	finally
	  (let ((table
		  (make-attributes-display-table
		    entity denotations-of-candidate-slots-to-describe
		    denotations-of-slots-for-which-to-suppress-name)))
	    (cond
	      ((table-represents-some-frames-p table)
	       (add-attribute-display-as-subblock
		 table entity
		 (if (memq offset-part '(at-standard-position to-left to-right))
		     nil
		     (first offset-part))
		 (if (memq offset-part '(at-standard-position to-left to-right))
		     nil
		     (second offset-part))
		 nil nil
		 (if (memq offset-part '(at-standard-position to-left to-right))
		     offset-part))
	       (reclaim-slot-value
		 denotations-of-slots-for-which-to-suppress-name)
	       (reclaim-slot-value
		 denotations-of-candidate-slots-to-describe)
	       (return table))
	      (t
	       (delete-frame table)
	       (return nil))))))

;; Note that this used to be able to put out no-attributes-to-display tables, so
;; they might be still be out in KBs.  The new policy began today. (MHD 12/2/94)

;; Notice that the references (to slots) cannot be trusted.  Also, there aren't
;; currently frame notes for bad references in the definition, which is a bit
;; sloppy, I must admit.  (MHD 4/2/94)



;;; Delete-all-attribute-displays ...

(defun delete-all-attribute-displays (entity)
  (loop while
	(loop for subblock being each subblock of entity
	      when (and (table-p subblock)
			(attribute-display-p subblock))
		do (delete-frame subblock)
		   (return t))))

;;; Add-attribute-display-as-subblock ... User-x-offset? and user-y-offset?
;;; must be either both nil or both user workspace coordinate system deltas.
;;; X-offset? and y-offset? must be either both nil or both workspace coordinate
;;; system deltas.  If user-x-offset? is non-nil, x-offset? should be nil,
;;; and vice versa.  If both are nil, then attribute-display is positioned
;;; in the "standard" position.  (This is what always happens when an attribute
;;; is displayed by the user from a menu.)  Otherwise, the attribute table
;;; is positioned with its top-left corner offset from the center of block
;;; according to one of the pair of offset arguments.

;;; When both pairs of user-x/y-offset? and x/y-offset? are nil, Advanced-spec?
;;; may be supplied either nil or non-nil with the following meanings. (Note: in
;;; the following descriptions "a small distance" means
;;; standard-attribute-display-spacing; see below.)
;;;
;;;   NIL, AT-STANDARD-POSITION, TOP-RIGHT: first attribute display has its left
;;;   edge a small distance away from the right edge of block, and its top edge
;;;   aligned with the top edge of block; subsequent attribute displays are
;;;   placed a small distance below the bottommost attribute display found, with
;;;   their left edges aligned with the bottommost attribute display's left
;;;   edge;
;;;
;;;   TO-LEFT: first attribute has its left edge a small distance away from the
;;;   right edge of block, and is centered vertically with respect to block;
;;;   subsequent displays are placed a small distance below the bottommost
;;;   attribute display found, with their left edges aligned with the bottommost
;;;   attribute display's left edge;
;;;
;;;   TO-RIGHT: first attribute has its right edge a small distance away from
;;;   the left edge of block, and is centered vertically with respect to block;
;;;   subsequent displays are placed a small distance below the bottommost
;;;   attribute display found, with their right edge aligned with the bottommost
;;;   attribute display's right edge
;;;

;;; The parameter `standard-attribute-display-spacing' is standard distance an
;;; attribute display's edge is placed from its superior item's edge.  It's also
;;; used as the vertical distance between attribute displays when there are
;;; multiple ones being stacked.

(defparameter standard-attribute-display-spacing 4)

(defun add-attribute-display-as-subblock
       (attribute-display block
	&optional
	user-x-offset? user-y-offset?		; pair
	x-offset? y-offset?			; pair (mutually exclusive w/above)
	advanced-spec?)
  (cond
    (user-x-offset?
     (add-to-block
       attribute-display block
       (+w (vertical-midline-of-block block) user-x-offset?)
       (+w (horizontal-midline-of-block block) (-w user-y-offset?))
       t))
    (x-offset?
     (add-to-block
       attribute-display block
       (+w (vertical-midline-of-block block) x-offset?)
       (+w (horizontal-midline-of-block block) y-offset?)
       t))
    (t
     (loop with bottom-edge? = nil
	   with left-edge? = nil
	   with right-edge? = nil
	   for subblock being each subblock of block
	   when (and (table-p subblock)
		     (attribute-display-p subblock))
	     do (case advanced-spec?
		  ((nil at-standard-position top-right to-right)
		   (when (or (null bottom-edge?)
			     (>w (bottom-edge-of-block subblock)
				 bottom-edge?))
		     (setq left-edge? (left-edge-of-block subblock))
		     (setq bottom-edge? (bottom-edge-of-block subblock))))
		  (t			; to-left
		   (when (or (null bottom-edge?)
			     (>w (bottom-edge-of-block subblock)
				 bottom-edge?))
		     (setq right-edge? (right-edge-of-block subblock))
		     (setq bottom-edge? (bottom-edge-of-block subblock)))))
	   finally
	     (cond
	       (bottom-edge?
		(add-to-block
		  attribute-display block
		  (or left-edge?
		      ;; else right-edge? non-nil
		      (-w right-edge?
			  (width-of-block attribute-display)))
		  (+w bottom-edge? standard-attribute-display-spacing)
		  t))
	       (t
		(add-to-block
		  attribute-display block
		  (case advanced-spec?
		    ((nil at-standard-position top-right to-right)
		     (+w (right-edge-of-block block)
			 standard-attribute-display-spacing))
		    (t			; to-left
		     (-w (-w (left-edge-of-block block)
			     standard-attribute-display-spacing)
			 (width-of-block attribute-display))))
		  (case advanced-spec?
		    ((nil at-standard-position top-right) (top-edge-of-block block))
		    (t			; (to-right to-left)
		     (halfw (-w (+w (top-edge-of-block block)
				    (bottom-edge-of-block block))
				(height-of-block attribute-display)))))
		  t)))))))






;;;; Component Access to Attribute Tables


      	
(def-virtual-attribute current-attribute-displays
    ((or (class entity)
	 (class free-text)
	 (class borderless-free-text)
	 (class statement)
	 (class message)
	 (class scrap))
     (or
       (no-item)
       (sequence
	 (structure 
	   ((attribute-list
	      (sequence (structure
			  ((attribute symbol)
			   (qualified-class symbol)
			   (display-with-name truth-value)
			   (display-format ; new. (MHD 1/10/02)
			     (member interval default time-stamp free-text))
			   (attribute-is-hidden truth-value)
			   (attribute-is-in-value-format truth-value)
			   (attribute-is-in-summary-format truth-value))
			  (and attribute display-with-name))
			1))

	    (text-color
 	      ;;should use (named color-or-metacolor) when
 	      ;;virtual attributes can use "named" construct.
 	      (member foreground background transparent
 		      . #.(mapcar #'car standard-gensym-color-alist)))
	    (position (or (member at-standard-position)
			  (structure
			    ((x-offset integer)
			     (y-offset integer))
			    (and x-offset y-offset)))))
	   (and attribute-list position))
	 1))
     ()   ;; "slot features" - are any necessary for this attribute?
     )
  :event-updates nil
  :initial ((class-name)
	    (let ((class-description (class-description class-name)))
	      (if (and (not (system-defined-class-p class-name))
		       (class-description-of-class-p class-description 'object))
		  (let ((slot-description
			  (get-slot-description-of-class-description
			    'attribute-displays-for-class class-description)))
		    ;; This should probably get-slot-evaluation-value from
		    ;; a definition object but we are not so sure as to how
		    ;; to access class-definitions and object-definitions in
		    ;; a consistent manner.
		    (call-category-getter
		      'attribute-displays-spec?
		      (slot-init-form slot-description)
		      nil
		      slot-description))
		  nil)))
  :getter ((entity)
	   (make-sequence-of-attribute-display-specs entity))   
  :setter ((entity evaluation-value)
	   (or (and evaluation-value
		    (attribute-displays-specification-error?
		      entity evaluation-value))
	       (progn
		 (delete-all-attribute-displays entity)
		 (when evaluation-value
		   (let ((servicing-workstation? nil)) ; see include-slot-in-attribute-table-p
		     (make-attribute-displays-from-specification
		       entity evaluation-value)))))))


(defun make-sequence-of-attribute-display-specs (entity)
  (loop for subblock being each subblock of entity
	when (and (table-p subblock)
		  (attribute-display-p subblock))
	  collect (make-structure-describing-attribute-display
		    entity subblock)
	    into attribute-display-structures
	    using eval-cons
	finally
	  (return
	    (and attribute-display-structures
		 (allocate-evaluation-sequence attribute-display-structures)))))

(defun make-structure-describing-attribute-display
    (entity attribute-display-table)
  (allocate-evaluation-structure-inline
    'attribute-list
    (export-table-layout attribute-display-table)
    'text-color
    (text-cell-line-color attribute-display-table
			  (get-a-text-cell attribute-display-table))
    'position
    (allocate-evaluation-structure-inline
      'x-offset (-w (left-edge-of-block attribute-display-table)
		    (vertical-midline-of-block entity))
      'y-offset (-w (horizontal-midline-of-block entity)
		    (top-edge-of-block attribute-display-table)))))

;;; `get-a-text-cell' could be better named, in my opinion.  Also, it used
;;; to just be a cadar.  Maybe it could be again if we change delete-
;;; attribute-name-from-attribute-display to not "collapse" the rows,
;;; and verify that nowhere ever changes the format like that.  - jv 9/2/98
;;; Do not ever use this function. - pbk 9/2/98

(defun get-a-text-cell (table-item)
  (let ((rows (table-rows table-item)))
    (if (cdar rows)
	(cadar rows)
	(caar rows))))

(defun export-table-layout (table-item)
  (loop for row in (table-rows table-item)
	as name-cell? = (and (cdr row) (car row))
	as value-cell = (if (cdr row) (cadr row) (car row))
	collect
	(multiple-value-bind
	    (frame slot-name defining-class?
		   slot-component-name? slot-component-indicator?
		   virtual-attribute? exported-format? text-summarized?
		   display-format?)
	    (get-slot-represented-by-text-cell-if-any value-cell)
	  (declare (ignore slot-component-name? slot-component-indicator?)) ; bug
	  (let* ((structure-values
		  (nconc
		   (eval-list
		    'attribute
		    (or (get-alias-for-slot-name-if-any slot-name frame)
			slot-name)
		    'display-with-name
		    (make-evaluation-boolean-value name-cell?))
		   (when defining-class?
		     (eval-list
		      'qualified-class
		      (make-evaluation-symbol defining-class?)))
		   (when virtual-attribute?
		     (eval-list
		      'attribute-is-hidden
		      (make-evaluation-boolean-value t)))
		   (when exported-format?
		     (eval-list
		      'attribute-is-in-value-format
		      (make-evaluation-boolean-value t)))
		   (when text-summarized?
		     (eval-list
		      'attribute-is-in-summary-format
		      (make-evaluation-boolean-value t)))
		   (when (memq display-format?
			       '(interval default time-stamp free-text))
		     (eval-list
		      'display-format
		      (make-evaluation-symbol display-format?))))))
	    (allocate-evaluation-structure structure-values)))
	  into attribute-structures
	  using eval-cons
	finally
	  (return
	    (allocate-evaluation-sequence attribute-structures))))

(defun attribute-displays-specification-error? (entity sequence)
  (loop for structure being each evaluation-sequence-element of sequence
	as attribute-list = (evaluation-structure-slot structure
						       'attribute-list)
	as text-color? = (evaluation-structure-slot structure 'text-color)
	as position = (evaluation-structure-slot structure 'position)
	do
    (when (and text-color?
	       (not (color-or-metacolor-p text-color?)))
      (return (tformat-text-string "unknown color ~a" text-color?)))
    (loop for attribute-spec
	      being each evaluation-sequence-element of attribute-list
	  do
      (with-evaluation-structure-slots
	  (attribute-spec
	    (attribute qualified-class))
	(let ((unaliased-slot-name (get-slot-name-for-alias-if-any attribute entity)))
	  (unless (or (eq unaliased-slot-name 'class) ; table-header
		      (get-slot-description-of-frame
			(or unaliased-slot-name attribute)
			entity qualified-class))
	    (return-from attribute-displays-specification-error?
	      (tformat-text-string
		"Unknown attribute, ~NQ, to display for ~NF"
		attribute qualified-class entity))))))))

(defun-simple evaluation-structure-slot-boolean-is-true-p (struct slot)
  (let ((value (evaluation-structure-slot struct slot)))
    (and (evaluation-boolean-p value)
	 (evaluation-boolean-is-true-p value))))

(defun make-attribute-display-table-from-specification (entity attribute-list)
  (loop with table = (make-attribute-display-table-from-specification-1 entity attribute-list)
	for attribute-spec
	    being each evaluation-sequence-element of attribute-list
	as slot-name = (evaluation-structure-slot attribute-spec 'attribute)
	as unaliased-slot-name = (get-slot-name-for-alias-if-any slot-name entity)
	as unaliased-slot-name-1 = (if (eq unaliased-slot-name 'class)
				       'table-header
				       unaliased-slot-name)
	as defining-class? = (evaluation-structure-slot attribute-spec 'qualified-class)
	as slot-component-name? = nil
	as slot-component-indicator? = nil
	as attribute-is-hidden-p
	  = (evaluation-structure-slot-boolean-is-true-p attribute-spec 'attribute-is-hidden)
	as attribute-is-in-value-format-p
	  = (evaluation-structure-slot-boolean-is-true-p attribute-spec 'attribute-is-in-value-format)
	as attribute-is-in-summary-format-p
	  = (evaluation-structure-slot-boolean-is-true-p attribute-spec 'attribute-is-in-summary-format)
	as display-format?
	   = (evaluation-structure-slot attribute-spec 'display-format)
	as value-text-cell?
	   = (get-text-cell-representing-slot-if-any
	      table entity unaliased-slot-name-1 defining-class?
	      slot-component-name? slot-component-indicator?
	      nil nil ; remaining-rows-index? remaining-cells-index?
	      nil) ;virtual-attribute-p
	do (when (and value-text-cell?
		      (or attribute-is-in-summary-format-p attribute-is-in-value-format-p attribute-is-hidden-p
			  display-format?))
	     (cond (attribute-is-in-summary-format-p
		    (when (or slot-component-name? slot-component-indicator?)
		      (change-text-cell-property value-text-cell? 'text-summarized? t)))
		   (attribute-is-in-value-format-p
		    (when (permit-view-slot-in-exported-format-p value-text-cell?)
		      (change-text-cell-property value-text-cell? 'exported-format t)))
		   (attribute-is-hidden-p
		    (when (virtual-attribute unaliased-slot-name-1)
		      (change-text-cell-property value-text-cell? 'virtual-attribute t))))
	     (when display-format?
	       (change-text-cell-property value-text-cell? 'display-format display-format?))
	     (update-text-cell-for-slot-in-table table value-text-cell?))
	finally (return table)))

(defun make-attribute-display-table-from-specification-1 (entity attribute-list)
  (loop with denotations-with-name = '()
	with denotations-without-name = '()
	for attribute-spec
	    being each evaluation-sequence-element of attribute-list
	do
    (with-evaluation-structure-slots
	(attribute-spec
	  (attribute qualified-class display-with-name attribute-is-hidden
		     attribute-is-in-value-format))
      (let ((slot-denotation?
	      (if (eq attribute 'table-header)
		  (make-slot-name-denotation 'table-header nil)
		  (let ((slot-description?
			  (get-slot-description-of-frame
			    (or (get-slot-name-for-alias-if-any attribute entity)
				attribute)
			    entity qualified-class)))
		    (when slot-description?
		      (denote-slot-using-slot-value-conses
			slot-description? (class-description-slot entity)))))))
	(when slot-denotation?
	  (slot-value-push slot-denotation? denotations-with-name)
	  (unless (evaluation-truth-value-is-true-p display-with-name)
	    (slot-value-push (copy-for-slot-value slot-denotation?)
			     denotations-without-name)))))
	finally
	  (when (or denotations-with-name denotations-without-name)
	    (setq denotations-with-name (nreverse denotations-with-name))
	    (setq denotations-without-name (nreverse denotations-without-name))
	    (return (prog1 (make-attributes-display-table
			     entity denotations-with-name denotations-without-name)
		      (reclaim-slot-value denotations-with-name)
		      (reclaim-slot-value denotations-without-name))))))

(defun make-attribute-displays-from-specification-1 (entity sequence)
  (loop for structure being each evaluation-sequence-element of sequence
	for attribute-display-table?
	    = (make-attribute-display-table-from-specification
		entity
		(evaluation-structure-slot structure 'attribute-list))
	when attribute-display-table?
	  collect (let ((text-color? (evaluation-structure-slot structure 'text-color))
			(position (evaluation-structure-slot structure 'position)))
		    (when (and text-color?
			       (neq text-color? 'foreground))
		      (loop for row in (table-rows attribute-display-table?)
			    do (loop for cell? in row
				     when (and cell?
					       (not (cell-is-block-p cell?)))
				       do (change-color-of-text-cell
					    attribute-display-table? cell? nil
					    :no-change :no-change text-color?))))
		    (cond
		      ((symbolp position) ;; in "standard-position"
		       (eval-list attribute-display-table?))
		      (t ; it's a struct
		       (with-evaluation-structure-slots
			   (position (x-offset y-offset))
			 (eval-list attribute-display-table? x-offset y-offset)))))
	  using eval-cons))

(defun make-attribute-displays-from-specification (entity sequence)
  (loop with list = (nreverse (make-attribute-displays-from-specification-1 entity sequence))
	for subblock-info in list
	for (attribute-display-table? x-offset y-offset) = subblock-info
	do (add-attribute-display-as-subblock attribute-display-table? entity x-offset y-offset)
	   (reclaim-eval-list subblock-info)
	finally (reclaim-eval-list list)))



;;;; Attribute Display Text Box/Cell Formats




(def-text-cell-format attribute-display-description-format
  text-cell-lines-justified? nil
  text-cell-line-quadding? right
  text-cell-left-margin 2
  text-cell-top-margin 1
  text-cell-right-margin 5
  text-cell-bottom-margin 1
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 8
  text-cell-font-map (hm14)
  text-cell-line-height 15
  text-cell-baseline-position 11
  text-cell-line-spacing 0
  default-word-spacing #.(convert-to-text-width 4)
  minimum-format-width-for-text-cell 300)

(def-text-cell-format large-attribute-display-description-format
  text-cell-lines-justified? nil
  text-cell-line-quadding? right
  text-cell-left-margin 2
  text-cell-top-margin 1
  text-cell-right-margin 5
  text-cell-bottom-margin 1
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 10
  text-cell-font-map (hm18)
  text-cell-line-height 18
  text-cell-baseline-position 13
  text-cell-line-spacing 0
  default-word-spacing #.(convert-to-text-width 5)
  minimum-format-width-for-text-cell 350)

(def-text-cell-format extra-large-attribute-display-description-format
  text-cell-lines-justified? nil
  text-cell-line-quadding? right
  text-cell-left-margin 2
  text-cell-top-margin 1
  text-cell-right-margin 5
  text-cell-bottom-margin 1
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 12
  text-cell-font-map (hm24)
  text-cell-line-height 25
  text-cell-baseline-position 20
  text-cell-line-spacing 0
  default-word-spacing #.(convert-to-text-width 5)
  minimum-format-width-for-text-cell 380)



;;; The "standard" format for attribute displays, i.e., with no size prefix, is the
;;; small format.  The others have prefix "large-" and "extra-large-".  But the
;;; mapping facility expects to get the large format name to map from.  This makes
;;; things look slightly wierd.  (We didn't originally anticipate putting keying the
;;; format selection off of the FONTS system table, and we originally just had the
;;; small format.

(setf (corresponding-extra-large-font-format-name
	'large-attribute-display-description-format)
      'extra-large-attribute-display-description-format)

(setf (corresponding-small-font-format-name
	'large-attribute-display-description-format)
      'attribute-display-description-format)



(def-text-cell-format attribute-display-value-format
  text-cell-lines-justified? nil
  text-cell-left-margin 5
  text-cell-top-margin 1
  text-cell-right-margin 2
  text-cell-bottom-margin 1
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 8
  text-cell-font-map (hm14)
  text-cell-line-height 15
  text-cell-baseline-position 11
  text-cell-line-spacing 0
  default-word-spacing #.(convert-to-text-width 4)
  minimum-format-width-for-text-cell 300)

(def-text-cell-format large-attribute-display-value-format
  text-cell-lines-justified? nil
  text-cell-left-margin 5
  text-cell-top-margin 1
  text-cell-right-margin 2
  text-cell-bottom-margin 1
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 10
  text-cell-font-map (hm18)
  text-cell-line-height 18
  text-cell-baseline-position 14
  text-cell-line-spacing 0
  default-word-spacing #.(convert-to-text-width 5)
  minimum-format-width-for-text-cell 350)

(def-text-cell-format extra-large-attribute-display-value-format
  text-cell-lines-justified? nil
  text-cell-left-margin 5
  text-cell-top-margin 1
  text-cell-right-margin 2
  text-cell-bottom-margin 1
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 12
  text-cell-font-map (hm24)
  text-cell-line-height 25
  text-cell-baseline-position 20
  text-cell-line-spacing 0
  default-word-spacing #.(convert-to-text-width 5)
  minimum-format-width-for-text-cell 380)

(setf (corresponding-extra-large-font-format-name
	'large-attribute-display-value-format)
      'extra-large-attribute-display-value-format)

(setf (corresponding-small-font-format-name
	'large-attribute-display-value-format)
      'attribute-display-value-format)



(def-text-cell-format attribute-display-class-format
  text-cell-background-color? nil
  text-cell-line-color? nil
  text-cell-line-quadding? center
  text-cell-lines-justified? nil
  text-cell-left-margin 2
  text-cell-top-margin 1
  text-cell-right-margin 2
  text-cell-bottom-margin 1
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 8
  text-cell-font-map (hm14)
  text-cell-line-height 15
  text-cell-baseline-position 11
  text-cell-line-spacing 0
  default-word-spacing #.(convert-to-text-width 4)
  minimum-format-width-for-text-cell 300)

(def-text-cell-format large-attribute-display-class-format
  text-cell-background-color? nil
  text-cell-line-color? nil
  text-cell-line-quadding? center
  text-cell-lines-justified? nil
  text-cell-left-margin 2
  text-cell-top-margin 1
  text-cell-right-margin 2
  text-cell-bottom-margin 1
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 10
  text-cell-font-map (hm18)
  text-cell-line-height 18
  text-cell-baseline-position 14
  text-cell-line-spacing 0
  default-word-spacing #.(convert-to-text-width 5)
  minimum-format-width-for-text-cell 350)

(def-text-cell-format extra-large-attribute-display-class-format
  text-cell-background-color? nil
  text-cell-line-color? nil
  text-cell-line-quadding? center
  text-cell-lines-justified? nil
  text-cell-left-margin 2
  text-cell-top-margin 1
  text-cell-right-margin 2
  text-cell-bottom-margin 1
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 12
  text-cell-font-map (hm24)
  text-cell-line-height 25
  text-cell-baseline-position 20
  text-cell-line-spacing 0
  default-word-spacing #.(convert-to-text-width 5)
  minimum-format-width-for-text-cell 380)

(setf (corresponding-extra-large-font-format-name
	'large-attribute-display-class-format)
      'extra-large-attribute-display-class-format)

(setf (corresponding-small-font-format-name
	'large-attribute-display-class-format)
      'attribute-display-class-format)


(def-table-format attribute-display-table-format

  ;; New -- to be more like readout tables:
  table-left-border-width 0
  table-top-border-width 0
  table-right-border-width 0
  table-bottom-border-width 0
  
  table-background-color? nil			; maybe "light-gray" when color mapping
						;   works for B&W systems
						; -- was white (MHD 8/3/89)
  table-row-boundary-width 0
  table-column-boundary-width 0)

(def-table-format-spot-generator attribute-display-table-format
    (attribute-display mouse-pointer)
  (generate-spot-for-input-table
    attribute-display
    mouse-pointer
    (make-attribute-display-spot)))





;;;; Virtual-Attribute Tables



;;; A `virtual attribute table' is the internal name for what is known to users
;;; as a `table of hidden attributes' or `hidden attribute table'. The idea is
;;; to give an interface similar to that of an attribute table.  However, it is
;;; different in an important respect: the value cells of a virtual attribute
;;; table are not dynamically updated based on the state of the represented
;;; frame; they must be refreshed explicitly, e.g., through a refresh button
;;; that is typically along with the table.  Virtual attributes are known to
;;; users generally as "hidden attributes".

(def-concept virtual-attribute-table)
(def-concept hidden-attribute-table)
(def-concept table-of-hidden-attributes)





;;; The function `make-table-of-virtual-attributes' returns an attribute-table
;;; style display of the virtual attributes of block, including inherited
;;; attributes but excluding deprecated attributes.  The style of the table
;;; display is generally similar to what would be shown for a classic attribute
;;; table (i.e., subject to various UI parameters).

(defun make-table-of-virtual-attributes (block)
  (let* ((value-format
	   (if new-g2-classic-ui-p
	       'new-attribute-value-format
	       (choose-font-format-per-fonts-table
		 'attribute-value-format 'font-for-attribute-tables)))
	 (description-format
	   (if new-g2-classic-ui-p
	       'new-attribute-description-format
	       (choose-font-format-per-fonts-table
		 'attribute-description-format 'font-for-attribute-tables)))
	 (table-format
	   (if new-g2-classic-ui-p
	       'new-attributes-table-format
	       'attributes-table-format))
	 (class-format
	   (if new-g2-classic-ui-p
	       'new-class-format
	       (choose-font-format-per-fonts-table
		 'class-format 'font-for-attribute-tables)))
	 (table
	   (make-or-reformat-table
	     (or 
	       (make-virtual-attribute-table-rows
		 block class-format value-format description-format)
	       (make-empty-attributes-table-rows value-format))
	     table-format
	    nil)))
    (add-frame-representation-if-necessary table block)
    table))



;;; The function `virtual-attribute-table-p' is true if table is a virtual
;;; attribute table.

(defun virtual-attribute-table-p (table)
  (let ((frame? (classic-attribute-table-p table)))
    (and frame?
	 (get-text-cell-representing-slot-if-any
	   table frame? 'table-header nil nil nil nil nil t))))



;;; Typically a virtual attribute table viewed by using the
;;; table-of-hidden-attributes command from a workspace or or item menu.  The
;;; resulting popup workspace wants to be recognized as being dedicated for that
;;; purpose. In particular, it wants to be disposed of as a unit whenever the
;;; table is deleted, e.g., as a result of deleting the frame it represents.

;;; Currently the workspace consists of three subblocks:
;;;
;;;       (1) a virtual attributes table -- the table showing the attributes;
;;;
;;;       (2) an update button -- a button of class generic-action-button
;;;           saying "update this table" that updates the values shown; and
;;;
;;;       (3) a timestamp -- a text box of class running-head showing
;;;           the time of the last update of the values shown


;;; The predicates `workspace-is-for-virtual-attribute-table-p', called with any
;;; workspace, and `temporary-workspace-is-for-virtual-attribute-table-p',
;;; called with a known temporary workspace, are used to determine if a
;;; workspace is such a popup virtual attributes table workspace.

;;; It is slightly heuristic in determining its result.  It uses the following
;;; rules. (1) The workspace must be temporary; (2) it must have no more than n
;;; subblocks, where n is given by the constant
;;; `max-subblock-count-with-pop-up-virtual-attributes-table', which is
;;; currently set to 3); and (3) there must be one and only one subblock that is
;;; a virtual attribute table (as decided using virtual-attribute-table-p), one
;;; and only one action button (the update button), and one and only one text
;;; box (the timestamp).

;;; These functions are called by the functions delete-block-for-user and
;;; remove-as-subblock, respectively, to enable them to handle deleting pop-up
;;; workspace as a whole whenever its virtual attribute table is deleted.

;;; The function `classic-attribute-or-virtual-attribute-table-p' is true iff
;;; table is either a classic attribute table or virtual attribute table.

(defun workspace-is-for-virtual-attribute-table-p (workspace)
  (and (temporary-workspace-p workspace)
       (has-subblocks-like-virtual-attribute-table-p workspace nil)))

(defun temporary-workspace-is-for-virtual-attribute-table-p (temporary-workspace)
  (has-subblocks-like-virtual-attribute-table-p temporary-workspace nil))


(defun classic-attribute-or-virtual-attribute-table-p (table)
  (let ((superblock? (superblock? table)))
    (if (and superblock? (temporary-workspace-p superblock?))
	(cond
	  ((virtual-attribute-table-p table)
	   (has-subblocks-like-virtual-attribute-table-p superblock? table))
	  ((attribute-table-p table)
	   (has-only-one-subblock-p superblock?))))))


(eval-when (:compile-toplevel :load-toplevel :execute)

(defconstant expected-button-class-for-pop-up-virtual-attributes-table 'generic-action-button)
(defconstant expected-timestamp-class-for-pop-up-virtual-attributes-table 'running-head)
(defconstant expected-table-class-for-pop-up-virtual-attributes-table 'table)
)

(defun has-subblocks-like-virtual-attribute-table-p (workspace table-if-known?)
  (loop with seen-button-p = nil
	with seen-timestamp-p = nil
	with seen-table-p = nil
	with count-so-far = 0
	with max-count
	  = max-subblock-count-with-pop-up-virtual-attributes-table
	for subblock being subblock of workspace
	do (incff count-so-far)
	when (>f count-so-far max-count)
	  return (values nil 'too-many-subblocks)
	do  (frame-class-case subblock
	      (#.expected-button-class-for-pop-up-virtual-attributes-table
		(if seen-button-p
		    (return (values nil 'too-many-action-buttons))
		    (setq seen-button-p t)))
	      (#.expected-timestamp-class-for-pop-up-virtual-attributes-table
		(if seen-timestamp-p
		    (return (values nil 'too-many-timestamps))
		    (setq seen-timestamp-p t)))
	      (#.expected-table-class-for-pop-up-virtual-attributes-table
		(cond
		  (seen-table-p
		   (return (values nil 'too-many-tables)))
		  (table-if-known?
		   (if (eq subblock table-if-known?)
		       (setq seen-table-p t)
		       (return (values nil 'too-many-tables))))
		  ((virtual-attribute-table-p subblock)
		   (setq seen-table-p t))
		  (t 
		   (return (values nil 'too-many-tables)))))
	      (t
		(return (values nil 'unrecognized-class-instance subblock))))
	finally
	  (let ((seen-them-all-p
		  (and seen-button-p seen-timestamp-p seen-table-p)))
	    (return
	      (values seen-them-all-p
		      (if (not seen-them-all-p)
			  'not-all-class-instances-seen))))))

;; New for G2 7.0. Note: the second value is handy for debugging, but is not
;; really needed, so I've left it undocumented for now.  Note: this could all be
;; made much simpler by simply using a specialized subclass of temporary
;; workspace dedicated to this purpose. Consider making that change at some
;; future point! (MHD 7/21/02)





;;; The function `make-virtual-attribute-table-rows' returns a table row for
;;; inclusion in an attribute-table style display of virtual attributes.  This
;;; is a subfunction of make-table-of-virtual-attributes.

(defun-allowing-unwind make-virtual-attribute-table-rows
    (block header-format value-format description-format)
  (let ((table-rows
	  (unless new-g2-classic-ui-p
	    (slot-value-list
	      (make-virtual-attribute-table-header-rows block header-format)))))
    (do-virtual-attributes
	(block) (name)
	(setq table-rows
	      (nconc table-rows
		     (slot-value-list
		       (slot-value-list
			 (make-text-cell
			   (make-text-for-cell-identifying-virtual-attribute-in-table name)
			   description-format)    
			 (make-text-cell-representing-slot
			   (text-for-item-or-value  ; reclaims the value
			     (get-virtual-attribute
			       block
			       (virtual-attribute name)))
			   value-format
			   block
			   name
			   nil nil nil t))))))
    table-rows))

(defun text-for-item-or-value (item-or-value)
  (twith-output-to-text
    (let ((in-text-for-item-or-value-p t))
      (cond ((framep item-or-value)
	     (tformat "~NF" item-or-value))
	    ((null item-or-value)
	     (tformat "none" item-or-value))
	    ((symbolp item-or-value)
	     (tformat "the symbol ~(~NV~)" item-or-value))
	    (t
	     (prog1 (tformat "~(~NV~)" item-or-value)
	       (reclaim-evaluation-value item-or-value)))))))

;; Added by SoftServe for Gensym-381
(defun text-string-for-item-or-value (item-or-value)
  (cond ((framep item-or-value)
	     (tformat-text-string "~NF" item-or-value))
	    ((null item-or-value)
	     (tformat-text-string "none" item-or-value))
	    ((symbolp item-or-value)
	     (tformat-text-string "the symbol ~(~NV~)" item-or-value))
	    (t
	     (tformat-text-string "~(~NV~)" item-or-value))))
;; End of SoftServe changes
    
(defun twrite-designation-for-item (item)
  (let ((name nil))
    (cond ((not (frame-in-use-p item))
	   (tformat "an item which has been deleted"))
	  ((not (of-class-p item 'system-item))
	   (twrite item))
	  ((and (of-class-p item 'block)
		(setq name (get-unique-name-for-frame-if-any item)))
	   (twrite name))
	  (t
	   (multiple-value-bind (parent-frame? slot-name? defining-class?)
	       (get-kb-parent-information item)
	     (cond (slot-name?
		    (twrite-string "the ")
		    (write-attribute-name parent-frame? slot-name? defining-class?)
		    (twrite-string " of ")
		    (twrite-designation-for-item parent-frame?))
		   (t
		    (twrite-string "the ")
		    (twrite (class item))
		    (twrite-string " having uuid ")
		    (twrite-uuid-printed-representation-as-string
		      (uuid item)))))))))

(defun twrite-denotation-for-item (denotation)
  (cond ((symbolp denotation)
	 (twrite denotation))
	((text-string-p denotation)
	 (tformat "the item having uuid ~S" denotation))
	((and (consp denotation)
	      (eq (car-of-cons denotation) 'the)
	      (symbolp (second denotation)))
	 (tformat "the ~A of " (second denotation))
	 (twrite-denotation-for-item (third denotation)))
	((and (consp denotation)
	      (eq (car-of-cons denotation) 'the-item-having-uuid)
	      (text-string-p (third denotation)))
	 (tformat "the ~A having uuid ~S" (second denotation) (third denotation)))))


;;; The function `make-virtual-attribute-table-header-row' returns a row that is
;;; to appear at the top of an attribute-table style display of virtual
;;; attributes.  This is a subfunction of make-virtual-attribute-table-rows.

(defun make-virtual-attribute-table-header-rows (block header-format)
  (slot-value-list
    nil
    (make-text-cell
      (get-text-for-virtual-attribute-table-header block)
      header-format
      (slot-value-list 'virtual-attribute-table-header t))))


(defun get-text-for-virtual-attribute-table-header (block)
  (twith-output-to-text
    (twrite-string "Hidden attributes for ")
    (write-class-instance-header-from-slot (class block) block)))



;;; The function `make-text-for-cell-identifying-virtual-attribute-in-table'
;;; returns a text identifying name, which should be a virtual attribute name,
;;; usable for inclusion in the "description" column of an attribute-table style
;;; display of virtual attributes.  This is a subfunction of
;;; make-virtual-attribute-table-rows.

(defun make-text-for-cell-identifying-virtual-attribute-in-table (name)
  (twith-output-to-text
    (twrite-string-as-attribute-name
      (symbol-namew name)
      nil t nil known-gensym-acronyms)))





;;;; Explanation Tables



;;; An `explanation table' is used for explanations of reasoning in G2.  It
;;; cannot "represent" a frame, but it can `originate' from a frame.  When the
;;; frame it originates from (called the `origination frame' is deleted, unlike a
;;; "frame representation", it is not deleted; all that happens is that it
;;; forgets about that frame.  When a slot value in the origination frame
;;; changes, that is not reflected in the explanation table.

;;; An explanation table is something of a cross between an inform message and
;;; a short representation table.  Like a message, it may have an `origin', and
;;; thus can support a menu choice like "go to origin of explanation".  It may
;;; originate from at most one frame.  And it also may have any number of extra
;;; cells with arbitrary texts at the end of the table.

; (def-class (explanation-table table))  ; -dkuznick, 6/15/98
;; Don't want users to instantiate these, as they can't exist nicely on their
;; own.  They need a frame to go woth them. -dkuznick, 8/7/98
(def-class (explanation-table table-item not-user-instantiable))

;; To implement explanation tables as described above, I had to make changes
;; in 4 areas in addition to adding this section, as follows.
;;
;;  (1) Update-representations-in-tables (in TABLES) does not update
;;       frame representations that are explanation tables;
;;       
;;  (2) Reclaim-frame-representations-value (i.e. the frame-
;;       representations slot reclaimer) (in FRAMES4) does not
;;       delete frame representations that are explanation tables;
;;
;;  (3) Highlight-or-unhighlight-for-slot (in EDIT) does not highlight
;;       frame representations that are explanation tables;
;;
;;  (4) Compute-table-choices (i.e. the function generated by the def-
;;       menu for table) (in FACILITIES) will not allow a cell in an
;;       explanation table to be edited; and 
;;
;;  (5) Make-short-representation takes an extra optional argument,
;;       table-class?

;; Some day it will be possible to save these in KBs.  When that is done, some
;; fix will have to be done in FILES to the code which fixes up KBs that were
;; saved with embedded rules (in action buttons) that had illegal pointers in
;; their frame-representations slot; see code there for further info.
;; (MHD 1/24/90)



;; This seemed like the easiest approach.  An alternative I considered was to
;; add slots or new text cell plist properties for keeping the origination frame
;; and its serial number.  I worried about (1) extending that for many-to-many
;; relations between origination frames and explanation tables and (2) dealing
;; with saving explanation tables in KBs.  (That IS the approach used for inform
;; messages to support the go-to-message-origin operation, but I am not that
;; satisfied with it.

;; Is it necessary to have explanation tables be creatable not for any frame?







;;; Make-explanation-table ...

;;; Frame?, if non-nil, will be represented in the topmost cell(s) of the resulting
;;; explanation table.  Additional rows specified by spec-for-rows are always
;;; located beneath the cell or cells associated with frame?.

;;; Spec-for-rows is a slot value list of specs for cells.  Each spec for a cell
;;; is either a text string, which is to occupy both the first and second
;;; column, or a slot value list of two text strings, the first of which to occupy
;;; the first column and second of which is to occupy the second column.  All conses
;;; and strings in spec-for-additional-rows are either incorporated into the resulting
;;; table or recycled.

;;; It is an error for both frame? and spec-for-additional-rows to be nil.

;;; Font-size? should be a standard font size (e.g. SMALL, LARGE).  It defaults to
;;; SMALL.
  
(defun make-explanation-table
    (frame? &optional spec-for-additional-rows font-size?)
  (let ((additional-table-rows
	  (loop for spec-for-row in spec-for-additional-rows
		nconc
		(slot-value-list
		  (slot-value-list
		    (if (atom spec-for-row)
			nil
			(make-text-cell
			  (convert-text-string-to-text (first spec-for-row))
			  (case font-size?
			    ((nil small)
			     'small-attribute-description-format)
			    (t
			     'attribute-description-format))))
		    (make-text-cell
		      (convert-text-string-to-text
			(if (atom spec-for-row)
			    spec-for-row
			    (second spec-for-row)))
		      (case font-size?
			((small nil)
			 'small-attribute-value-format)
			(t
			 'attribute-value-format))))))))
    (reclaim-slot-value-tree		; reclaim conses in spec-for-
      spec-for-additional-rows)		;   additional-rows now
    (cond
      (frame?
       (let ((table-representing-frame
	       (make-short-representation
		 frame? 'explanation-table
		 (or font-size? 'small))))
	 (loop for rows on (table-rows table-representing-frame)
	       when (null (cdr (car rows))) ; must span 2 columns
	       do (setf (car rows) (slot-value-cons nil (car rows))))
	 (setf (table-rows table-representing-frame)
	       (nconc (table-rows table-representing-frame)
		      additional-table-rows))
	 (reformat-table-in-place table-representing-frame)
	 table-representing-frame))
      (t
       (make-or-reformat-table
	 additional-table-rows
	 'short-representation-table-format
	 nil 'explanation-table)))))

;; Note that only SMALL and (not SMALL) are the only two cases handled for font-size?
;; at present!!

;; Integrate this with make-short-representation-as-necessary.  (For now it
;; was a little easier to make use of make-short-representation instead.)
;; (MHD 1/24/90)



;;; The function `get-explanation-table-original' returns the `explanation-table
;;; original' for explanation-table, if there is one.  This is the frame for which
;;; the explanation table was based, and which the "go to original" ui command
;;; should go to.

(defun get-explanation-table-original (explanation-table) 
  (do-frames-this-represents (frame explanation-table)
    ;; docs for do-frames-this-represents say return by itself won't do what's
    ;; expected, so let's try a return-from instead -dkuznick, 6/15/98
    (return-from get-explanation-table-original frame)))	; 







;;;; Multiframe Tables

;; Being prototyped. (MHD/BAH 7/31/90)

;; NEEDS TO BE FIXED FOR CLASS QUALIFIERS!  (MHD 2/15/94)


(define-slot-alias text box-translation-and-text text-box)

;; MOVE!! Review!! And do for all "unique, editable, undescribed" slots!



;;; A `multiframe table' ...

;; BAH's design notes have also referred to this kind of table as a "query
;; table".  (MHD 8/16/90)



;;; Multiframe-table-p is true if table is a short representation.  At present, this
;;; is indicated by having a table format whose single name is the symbol short-
;;; representation-table-format.  (This is out of date.)

(defun multiframe-table-p (table)
  (eq (name-or-names-for-frame (table-format table))
      'multiframe-table-format))



;;; Make-not-available-text ... used for the intersection of a slot name and a frame
;;; for which the slot name does not apply.

(defmacro make-not-available-text ()
  ;; Alternate:
  ;;   '(convert-text-string-to-text (copy-text-string "N/A"))
  '(make-empty-text))


;;; Merge-frame-into-multiframe-table-rows .... Returns nil if there are
;;; no applicable slots in frame and existing-table-rows is null.

;;; slots-to-include? is a list of names or aliases thereof
;;; of slots ....
;;;
;;; Attribute-value-format-name? is the name for text cell format for value
;;; slots.  It defaults to SMALL-ATTRIBUTE-VALUE-FORMAT.

(defun merge-frame-into-multiframe-table-rows
    (frame &optional slots-to-include?
	   existing-table-rows denotations-of-existing-slots
	   attribute-value-format-name?)
  (loop with text-cell-format
	  = (get-or-make-format-frame
	      (or attribute-value-format-name?
		  'small-attribute-value-format))
	with value-cells-spine
	  = (copy-list-using-slot-value-conses denotations-of-existing-slots)
	with some-slots-were-contributed? = nil
	with attributes-table-description = (make-attributes-table-description
					      frame nil slots-to-include? nil t t)
	for description-list in attributes-table-description
	for (slot-name
	      defining-class?
	      text-representation-for-slot-value?
	      text-that-identifies-attribute?)
	    = description-list
	as value-representation-cell
	   = (make-text-cell-representing-slot
	       (or text-representation-for-slot-value?
		   (make-not-available-text))
	       text-cell-format
	       frame slot-name defining-class?)
	as tail-for-slot-in-value-cells-spine?
	   = (slot-denotation-member
	       slot-name defining-class?
	       value-cells-spine)
	if (null tail-for-slot-in-value-cells-spine?)
	  collect (make-slot-name-denotation slot-name defining-class?)
	    into additional-slot-denotations-so-far using slot-value-cons
	  and collect 
	  (make-text-cell
	    (or text-that-identifies-attribute?
		;; Not very often needed:  (But consider, alternatively,
		;; adding an arg to make-attributes-table-description to
		;; require always returning this text instead of doing
		;; the work again here!  (MHD 6/20/91))
		(make-text-for-cell-identifying-attribute-in-table
		  frame slot-name
		  defining-class?
		  ;(get-type-of-slot-if-any  -- args changed 12/20/95
		  ;  frame slot-name
		  ;  defining-class?)
		  nil))
	    text-cell-format)
		into additional-description-cells-so-far using slot-value-cons
	  and do (setq value-cells-spine
		       (nconc
			 value-cells-spine
			 (slot-value-list value-representation-cell)))
	else do (setf (car tail-for-slot-in-value-cells-spine?)
		      value-representation-cell)
	    ;; patch a leak -rdf, 5/12/95
		(reclaim-slot-value text-that-identifies-attribute?)
	do (setq some-slots-were-contributed? t)
	   (when (consp description-list)
	     ;; patch a leak -rdf, 5/12/95
	     (reclaim-slot-value-list description-list))
	finally
	  (progn
	    (when (consp attributes-table-description)
	      ;; patch a leak -rdf, 5/12/95
	      (reclaim-slot-value-list
		attributes-table-description))
	    (when value-cells-spine
	      
	      (when some-slots-were-contributed?
		(cond
		  (existing-table-rows
		   (when additional-slot-denotations-so-far
		     (nconc
		       (first existing-table-rows)
		       additional-description-cells-so-far)
		     (loop with number-of-additional-cells
			     = (length additional-description-cells-so-far)
			   for row in (cdr existing-table-rows)
			   do (nconc
				row
				(loop repeat number-of-additional-cells				    
				      collect
				      (make-text-cell
					(make-not-available-text)
					text-cell-format)
					using slot-value-cons)))))
		  (additional-description-cells-so-far
		   (setq existing-table-rows
			 (slot-value-list
			   additional-description-cells-so-far))))
		(loop for l on value-cells-spine
		      when (name-denotation-p (car l)) ; Recognize unavailable class 
					; qualified slot names, as well as the case
					; where a simple slot-name is used. -pga, 1/3/96
			do (setf (car l)
				 (make-text-cell
				   (make-not-available-text)
				   text-cell-format)))
		(nconc existing-table-rows
		       (slot-value-list value-cells-spine)))
	      (return
		(values
		  existing-table-rows
		  (nconc
		    denotations-of-existing-slots
		    additional-slot-denotations-so-far)))))))




(def-table-format multiframe-table-format
  table-row-boundary-width 1
  table-column-boundary-width 1
  table-left-border-width 1
  table-top-border-width 1
  table-right-border-width 1
  table-bottom-border-width 1)

(def-table-format-spot-generator multiframe-table-format (multiframe-table mouse-pointer)
  (generate-spot-for-input-table
    multiframe-table
    mouse-pointer
    (make-multiframe-table-spot)))



;;; Finish-making-multiframe-table ... it is assumed that table-rows is non-nil
;;; and that all cells are non-nil and are text cells.  When
;;; put-attributes-along-stub? is true, table-rows is changed so that slot names
;;; are displayed in each row and instances displayed in each column of the
;;; table.  The other ranking is assumed of table-rows on input.  It is also
;;; assumed that cells have frame-representation backpointers to frames that
;;; must have yet to get frame-representation pointers to this table; this
;;; function fixes that.

(defun finish-making-multiframe-table
       (table-rows &optional put-attributes-along-stub?)
  (when put-attributes-along-stub?
    (setq table-rows
	  (exchange-stub-and-header-axes-of-multiframe-table-rows
	    table-rows)))
  (let ((table
	  (make-or-reformat-table
	    table-rows 'multiframe-table-format nil nil)))
    ;; put in frame->representation-frame backpointers
    (loop with frame
	  for row in table-rows
	  do (loop for text-cell in row
		   do (when (setq frame
				  (get-slot-represented-by-text-cell-if-any text-cell))
			(add-frame-representation-if-necessary
			  table frame)
			(unless put-attributes-along-stub?
			  (return))))
	     (when put-attributes-along-stub?
	       (return)))
    table))

;; On an Explorer II+, the above call to exchange-stub-and-header-axes-of-
;; multiframe-table-rows, when needed because put-attributes-along-stub? is
;; true, adds about an extra 3% of overhead to this function.  (MHD 9/4/90)



;;; Exchange-stub-and-header-axes-of-multiframe-table-rows ... It is assumed that
;;; table-rows is non-nil and that all cells are non-nil and are text cells.

(defun exchange-stub-and-header-axes-of-multiframe-table-rows (table-rows)
  (loop with new-number-of-rows = (length (car table-rows))
	with new-table-rows
	  = (make-slot-value-list new-number-of-rows)
	for row-index from 0 below new-number-of-rows
	do (loop with column-tail? = nil
		 for remaining-rows on table-rows
		 as row = (car remaining-rows)
		 do (if column-tail?
			(setf (cdr column-tail?) row)
			(setf (nth row-index new-table-rows) row))
		    (setq column-tail? row)
		    (pop (car remaining-rows))
		    (setf (cdr column-tail?) nil))
	finally
	  (reclaim-slot-value-list table-rows)	; table-rows is now a list of nils
	  (return new-table-rows)))



;;; Remove-deleted-frames-in-multiframe-table-rows ...  It is assumed that
;;; table-rows is non-nil and that all cells are non-nil and are text cells.
;;; Also, it is assumed that a row may contains text cells that represent at
;;; most one frame; i.e., this must be called BEFORE the stub and header axes
;;; have been exchanged.  Frame-serial-number is used for checking for deleted
;;; or recycled frames.  When a row is to be removed, it and the cons pointing
;;; to it are reclaimed using reclaim-slot-value.

;;; This returns two values: (1) table-rows containing no rows with text cells
;;; representing deleted or recycled frames and (2) the number of rows that
;;; contain text cells pointing to non-deleted/non-recycled frames.

(defun remove-deleted-frames-in-multiframe-table-rows
       (table-rows frame-serial-number)
  ;; the following loop will setq the arg-variable table so that it ends
  ;; up not containing any rows for deleted frames.
  (loop with number-of-good-frames-found = 0
	with previous-remaining-rows = nil
	with remaining-rows = table-rows
	while remaining-rows
	for row = (car remaining-rows)
	as frame?				; could be a nil or deleted 
	   = (loop for text-cell in row		;   or recycled frame
		   thereis
		     (get-slot-represented-by-text-cell-if-any text-cell))
	do (cond
	     ((and frame?
		   (frame-has-been-reprocessed-p frame? frame-serial-number))
	      (cond
		(previous-remaining-rows
		 (setf (cdr previous-remaining-rows) (cdr remaining-rows))
		 (setf (cdr remaining-rows) nil)
		 (reclaim-slot-value remaining-rows)
		 (setq remaining-rows (cdr previous-remaining-rows)))
		(t
		 (setq table-rows (cdr remaining-rows))
		 (setf (cdr remaining-rows) nil)
		 (reclaim-slot-value remaining-rows)
		 (setq remaining-rows table-rows))))
	     (t
	      (if frame? (incff number-of-good-frames-found))
	      (setq previous-remaining-rows remaining-rows)
	      (setq remaining-rows (cdr remaining-rows))))
	finally
	  (return (values table-rows number-of-good-frames-found))))





;;;; Designations for Frames



;;; `Table-header' is the alias for the CLASS slot of frames.  It is always
;;; printed using the writer for class-instance-header. ...

(define-slot-alias table-header class)

;; Alias added 6/17/91 for 3.0.  In 2.1 & earlier, this was not aliased.
;; In earlier versions of 3.0 (in development), this was aliased as
;; CLASS in a bunch of places, some of which still need cleanup!  (MHD
;; 6/17/91)


;; The class slot was removed from frames, making it no longer possible
;; for kb developers to access "the text of the table-head of <frame>".
;; The following three forms are a somewhat kludgy way of getting that
;; facility using a virtual-attribute.

(defvar class-instance-header-type-of-slot '(type class-instance-header))

(defun make-class-header-string (frame)
  (make-text-string-representation-for-slot-value-itself
    frame (class frame) class-instance-header-type-of-slot))

(defvar virtual-attribute-class-instance-header-type-of-slot '(type virtual-attribute-class-instance-header))

(defun make-virtual-attribute-class-header-string (frame)
  (make-text-string-representation-for-slot-value-itself
    frame (class frame) virtual-attribute-class-instance-header-type-of-slot))


;;; `Make-component-type-header-string' ...

(defun make-component-type-header-string (frame slot-name defining-class? slot-componenent-indicator?)
  (do-slot-components
      (frame slot-name defining-class? slot-componenent-indicator? '(component-type))
      (name nil nil type value)
    name ; not used
    (return-from make-component-type-header-string
      (make-text-string-representation-for-slot-value-itself frame value type))))


;;; `Get-first-slot-component-backpointer-if-any' returns as values the frame,
;;; slot-name, defining class if any, slot-component name, and slot-component
;;; indicator if any for the first cell in table that represents a slot
;;; componenent of a frame.  If there is no such cell, this returns nil.

(defun get-first-slot-component-backpointer-if-any (table)
  (loop named rows
	for row in (table-rows table)
	do (loop for cell? in row
		 when (and cell?
			   (not (cell-is-block-p cell?)))
		   do (multiple-value-bind
			  (f sn dc scn sci) ; Note: some or all can be nil
			  (get-slot-represented-by-text-cell-if-any cell?)
			(when scn
			  (return-from rows (values f sn dc scn sci)))))))


(def-virtual-attribute table-header
    ((class item) text ())
  :event-updates nil
  :initial ((class) (declare (ignore class)) nil)
  :getter ((item)
	   (make-class-header-string item)))






;;; The class-instance-header slot value writer is the slot value writer for
;;; the class slot of frame.  But what it really writes is one or more
;;; designations of frame, including:
;;;
;;;    a primary name, if frame is a named block (that is not a subworkspace with the
;;;       same name as its parent;
;;;
;;;    the class of frame, preceded by "a" or "an";
;;;
;;;    a designation of frame as an attribute of its parent or as a subworkspace,
;;;       if applicable.
;;;
;;; Symbols are not written parsably, since the designations will never be parsed and
;;; since the designations are often used as a table header, which should be as
;;; tidy as possible.

(def-slot-value-writer class-instance-header (class frame)
  (setq write-symbols-parsably? nil)		; bind this instead?
  (cond
    ((frame-of-class-p frame 'simulation-subtable)
     (twrite-string "simulation subtable for ")
     (write-description-of-parent
       (get-slot-value frame 'parent-variable)))	; forward reference
    (t (let* ((entity-case? (frame-of-class-p frame 'entity))
	      (system-frame-case?
		(if entity-case? (frame-of-class-p frame 'system-frame)))
	      (primary-name?
		(if (or entity-case? (frame-of-class-p frame 'block))
		    (get-primary-name-for-frame-if-any frame)))
	      (procedure-invocation-name?
		(if (and (null primary-name?)
			 (frame-of-class-p frame 'procedure-invocation))
		    (get-or-make-up-designation-for-block frame)
		    nil))
	      (parent-of-subworkspace?
		(if (frame-of-class-p frame 'workspace)
		    (parent-of-subworkspace? frame)))
	      (book-logbook-page-is-part-of?
		(if (frame-of-class-p frame 'logbook-page)
		    (get-slot-value frame 'book-this-is-part-of))))
	 (if (and parent-of-subworkspace?
		  (eq primary-name?
		      (get-primary-name-for-frame-if-any parent-of-subworkspace?)))
	     (setq primary-name? nil))
	 (cond (primary-name?
		(write-name-for-frame primary-name?))
	       (procedure-invocation-name?
		(twrite-string procedure-invocation-name?)))
	 (cond
	   (system-frame-case?
	    (let ((non-top-level-module-this-is-for?
		    (if (not (system-table-installed-p frame))
			(loop for entry
				  in modules-and-system-tables-a-list
			      when (memq frame entry)
				return
				(or (get-slot-value	; fwd. ref.!
				      (car entry) 'top-level-kb-module?)
				    'unspecified)))))
	      (when non-top-level-module-this-is-for?
		(twrite-string " for module ")
		(twrite-symbol non-top-level-module-this-is-for?))))
	   (t
	    (when (or primary-name? procedure-invocation-name?)
	      (twrite-string ", "))
	    (write-symbol-with-a-or-an class)
	    (cond
	      (entity-case?
	       (multiple-value-bind
		   (parent-frame? slot-name? defining-class?)
		   (get-kb-parent-information frame)
		 (cond
		   (slot-name?
		    (twrite-string ", the ")
		    (write-attribute-name
		      parent-frame? slot-name? defining-class?)
		    (twrite-string " of ")
		    (write-description-of-parent parent-frame?)))))
	      (parent-of-subworkspace?
	       (twrite-string " subworkspace of ")	; just " for "?
	       (write-description-of-parent parent-of-subworkspace?))
	      (book-logbook-page-is-part-of?
	       (tformat ", page ~d" (get-slot-value frame 'page-number))
	       ;; Later, add " of XXX" or " of logbook XXX" where
	       ;;   XXX is the name of the particular logbook!
	       ;; Also may have to add the window this is part of
		 ))))))))

(def-slot-value-writer virtual-attribute-class-instance-header (class frame)
  (twrite-string "Hidden attributes for ")
  (funcall (slot-value-writer 'class-instance-header) class frame))

;; CLASS-INSTANCE-HEADER used to be CLASS, here and in FRAMES1.  It was changed when a
;; conflict developed by changing CLASS-NAME to CLASS.  (MHD 6/19/90)

;; I added the book-logbook-page-is-part-of? logic today (to print page numbers
;; of logbook pages in the class header of tables). (MHD 11/10/89)

;; Consider having the type of slot class be called designations, so that this slot
;; value writer can be more accurately named.  Similarly, class-format should really
;; be called "designations-format".

;; Ideally, this description should be updated if the parentage and/or name is changed!

;; It would have been more economical to have a simulation frame be an entity with
;; parent information instead of parent-variable, probably.



;;; The function `get-or-make-up-designation-for-block' is used to generate a
;;; designation for the given block which will be shown to the user, typically
;;; by printing with the ~A option to tformat.  This function returns a symbol
;;; or a text string containing the designation.  Note that the string should
;;; not be reclaimed by the caller of this function, and that subsequent calls
;;; to this function for the same frame may reclaim the previously returned
;;; string.

;;; The designation will be one of the following: the first name for
;;; the block if it has one, a string of the form "the <attribute> of <parent>",
;;; a string which looks like the procedure call if the block is a procedure
;;; invocation, or if the block has no names, no parent, and is not a
;;; procedure-invocation, then a string containing a name of the form
;;; "<class>-XXX-<number>".  This name can be used in inspect to refer to the
;;; block.

;;; This routine owns and manages the slot `name-for-debugging' in blocks along
;;; with get-or-make-up-name-for-block.

;;; The name-for-debugging slot contains, nil, a string, or a cons who's car is
;;; a string.  Nil implies that it has not name for debugging.  A string implies
;;; that the contents of that string maybe used as a name for debugging.  It
;;; is allocated once and then persists until the frame is deleted.  A cons implies
;;; that a designation for this block relative to some other block was created
;;; relative to some other block.  These names are usually regenerated when ever
;;; the debugging name is needed.

;;; When the name-for-debugging is a string it is known as a simple debugging name.
;;; All frames with simple debugging names are collected into a kb specific global
;;; to they maybe easily scanned by inspect.  The slot value reclaimer for the
;;; name-for-debugging removes them from this list.

(defun get-or-make-up-designation-for-block (block)
  (if (frame-in-use-p block)
      (or (get-unique-name-for-frame-if-any block)
	  (let ((name-for-debugging? (name-for-debugging block)))
	    (multiple-value-bind (parent-frame? slot-name? defining-class?)
		(get-kb-parent-information block)
	      (when (consp name-for-debugging?)
		(reclaim-text-string (car-of-cons name-for-debugging?))
		(reclaim-slot-value-cons name-for-debugging?)
		(setf (name-for-debugging block) nil)
		(setq name-for-debugging? nil))
	      (cond
		(name-for-debugging?
		 name-for-debugging?)
		((and slot-name? (block-p parent-frame?))
		 (setq name-for-debugging?
		       (slot-value-list
			 (twith-output-to-text-string
			   (twrite-string "the ")
			   (write-attribute-name
			     parent-frame? slot-name? defining-class?)
			   (twrite-string " of ")
			   (twrite (get-or-make-up-designation-for-block
				     parent-frame?)))))
		 (setf (name-for-debugging block) name-for-debugging?)
		 (car-of-cons name-for-debugging?))
		((frame-of-class-p block 'procedure-invocation)
		 (setf name-for-debugging?
		       (slot-value-list
			 (twith-output-to-text-string
			   (write-procedure-invocation-instance-from-slot
			     block nil))))
		 (setf (name-for-debugging block) name-for-debugging?)
		 (car-of-cons name-for-debugging?))
		(t
		 (get-or-make-up-name-for-block block))))))
	  #w"an item which has been deleted"))

;; HORRIBLE KLUDGE!! (which kludge is this refering to? - ben 9/10/91)



;;; Get-or-make-up-name-for-block returns as its value the name (or first name)
;;; of a block if there is one.  Otherwise it creates a name for the block and
;;; returns that name as value.

;;; NOTE!  You should use get-or-make-up-designation-for-block to get user
;;; friendly denotations for frames!

;;; The created name for a block has the form "class-XXX-n" where class
;;; is the immediate class of the block, and n is the smallest possitive
;;; integer such that no other block has the resultant name.
;;; Alternately the created name has the form "class-XXX-name-n" when
;;; there are multiple blocks with the same name.  This function can
;;; return either a symbol (if the block already has a name) or a text
;;; string (if it has to create one).  Do not reclaim the string.

(def-system-variable debugging-name-index tables 1)


;;; `All-frames-with-simple-debugging-names' provides a fast way to 
;;; scan the items that have debugging names.  This enables access to
;;; them without a scan over the set of all items.

(def-kb-specific-variable all-frames-with-simple-debugging-names tables nil
  nil ; do not bind globally.
  reclaim-slot-value)



(def-slot-value-reclaimer name-for-debugging (debugging-name block)
  (when debugging-name
    (when (text-string-p debugging-name)
      (loop as prior-p = nil then p
	    for p on all-frames-with-simple-debugging-names
	    when (eq (car p) block)
	      do
		(if prior-p
		    (setf (cdr prior-p) (cdr p))
		    (setf all-frames-with-simple-debugging-names (cdr p)))
		(reclaim-slot-value-cons p)
		(return nil)))
    (reclaim-slot-value debugging-name)))



(defun get-or-make-up-name-for-block (block)
  (if (frame-in-use-p block)
      (or (get-unique-name-for-frame-if-any block)
	  (get-or-make-up-debugging-name-for-block block))
      #w"an item which has been deleted"))




;;; The function `get-or-make-up-debugging-name-for-block' is like the function
;;; get-or-make-up-name-for-block, but is guaranteed to always return a
;;; debugging name.  Since this will create a debugging name on an block
;;; embedded as the attribute of another block you probably would prefer
;;; to use get-or-make-up-designation-for-block.

(defun get-or-make-up-debugging-name-for-block (block)
  (if (frame-in-use-p block)
      (or (let ((name-for-debugging? (name-for-debugging block)))
	    (when (consp name-for-debugging?)
	      (reclaim-text-string (car name-for-debugging?))
	      (reclaim-slot-value-cons name-for-debugging?)
	      (setf (name-for-debugging block) nil)
	      (setq name-for-debugging? nil))
	    name-for-debugging?)
	  (prog1
	    (setf (name-for-debugging block)
		  (let ((primary-name? 
			  (get-primary-name-for-frame-if-any block)))
		    (if primary-name?
			(tformat-text-string
			  "~A-XXX-~A-~D"
			  (class block) primary-name? debugging-name-index)
			(tformat-text-string
			  "~A-XXX-~D" (class block) debugging-name-index))))
	    (slot-value-push block all-frames-with-simple-debugging-names)
	    (incf debugging-name-index)))
      #w"an item which has been deleted"))




;;; The macro `debugging-name-for-block-p' takes a block and a string, and
;;; returns T if the name given string matches the debugging name for this
;;; frame, else it returns NIL.

(defmacro debugging-name-for-block-p (block string)
  (let ((name-for-debugging? (gensym)))
    `(let ((,name-for-debugging? (name-for-debugging ,block)))
       (and (text-string-p ,name-for-debugging?)
	    (string=w ,name-for-debugging? ,string)))))




;;; The function `get-cached-debugging-name' takes a block and returns the
;;; string which is the cached debugging name for the frame.  If none exists for
;;; the given frame, then this function will return NIL.  Note that the given
;;; need not be reclaimed by the caller of this function, and that the string
;;; may be reclaimed by subsequent calls to get-or-make-up-designation-for-
;;; block.

(defun get-cached-debugging-name (block)
  (let ((name-for-debugging? (name-for-debugging block)))
    (if (consp name-for-debugging?)
	(car name-for-debugging?)
	name-for-debugging?)))

(defun write-description-of-parent (parent)
  (loop as ancestor = parent then parent?
	as primary-name? = (get-primary-name-for-frame-if-any ancestor)
	with parent?
	with slot-name?
	with defining-class?
	do (cond
	     (primary-name?
	      (write-name-for-frame primary-name?)
	      (loop-finish)))
	   (multiple-value-setq (parent? slot-name? defining-class?)
	     (get-kb-parent-information ancestor))
	   (cond
	     ((null slot-name?)
	      (tformat "some ~(~A~)" (class ancestor))	; "of a particular"?
	      (loop-finish)))
	   (twrite-string "the ")
	   (write-attribute-name parent? slot-name? defining-class?)
	   (twrite-string " of ")))






;;;; Ascii Output of Attribute Tables



(def-table-format attributes-table-print-format
  table-line-color? nil
  table-background-color? nil

  table-left-border-width 0
  table-top-border-width 0
  table-right-border-width 0
  table-bottom-border-width 0
  table-border-color? nil

  table-row-boundary-width 2			; relevant?
  table-row-boundary-color? nil

  table-column-boundary-width 16		; a multiple of (character width) 8
  table-column-boundary-color? nil
  )

#+development
(def-table-format-spot-generator attributes-table-print-format (table mouse-pointer)
  (declare (ignore table mouse-pointer))
  (error "An attributes-table-print-format should never appear under the mouse!"))


(def-text-cell-format attributes-table-text-cell-print-format
  text-cell-font-map (Fixed14)			; characters all have width 8

  text-cell-line-color? nil
  text-cell-background-color? nil

  text-cell-x-magnification? nil
  text-cell-y-magnification? nil

  text-cell-left-margin 0
  text-cell-top-margin 0
  text-cell-right-margin 0
  text-cell-bottom-margin 0

  text-cell-line-height 15
  text-cell-baseline-position 12
  text-cell-line-spacing 5
  default-word-spacing #.(convert-to-text-width 8)
  maximum-word-spacing #.(convert-to-text-width 8)

  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 24

  text-cell-line-quadding? nil
  text-cell-lines-justified? nil

  minimum-width-for-text-cell 0
  minimum-format-width-for-text-cell 400
  maximum-format-width-for-text-cell 800

  text-cell-selection-actions nil)

;; Inheritance would be helpful.  The following differs from the previous only
;; in being centered instead of left-justified and having zero turnover line
;; indentation



(def-text-cell-format attributes-table-text-cell-class-print-format
  text-cell-font-map (Fixed14)			; characters all have width 8

  text-cell-line-color? nil
  text-cell-background-color? nil

  text-cell-x-magnification? nil
  text-cell-y-magnification? nil

  text-cell-left-margin 0
  text-cell-top-margin 0
  text-cell-right-margin 0
  text-cell-bottom-margin 0

  text-cell-line-height 15
  text-cell-baseline-position 12
  text-cell-line-spacing 5
  default-word-spacing #.(convert-to-text-width 8)
  minimum-word-spacing #.(convert-to-text-width 8)
  maximum-word-spacing #.(convert-to-text-width 8)

  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 0

  text-cell-line-quadding? center
  text-cell-lines-justified? nil

  minimum-width-for-text-cell 0
  minimum-format-width-for-text-cell 400
  maximum-format-width-for-text-cell 800

  text-cell-selection-actions nil)




;;; Print-frame ... returns frame.  slots-to-include?, if non-nil, further
;;; restricts the slots which will be printed.  (See also the description of
;;; this variable under make-attributes-table.)

;;; When destination-g2-stream? is nil this writes its output to as if via tformat.

(defmacro print-frame-newline-idiom ()
  `(if destination-g2-stream?
       (export-and-emit-text-line
	 #w""
	 transcode-text-conversion-style-if-stream
	 destination-g2-stream?)
       (twrite-char #\newline)))

(defmacro print-frame-space-idiom ()
  `(if destination-g2-stream?
       (export-and-emit-character
	 #\space
	 transcode-text-conversion-style-if-stream
	 destination-g2-stream?)
       (twrite-char #\space)))

(defmacro print-frame-line-idiom (line)
  `(if destination-g2-stream?
       (export-and-emit-text-line
	 ,line
	 transcode-text-conversion-style-if-stream
	 destination-g2-stream?)
       (twrite-string ,line)))

(defmacro print-frame-string-idiom (string)
  `(if destination-g2-stream?
       (export-and-emit-text-string
	 ,string
	 transcode-text-conversion-style-if-stream
	 destination-g2-stream?)
       (twrite-string ,string)))

(defun print-frame (frame &optional slots-to-include? destination-g2-stream?
			  transcode-text-conversion-style-if-stream)
  (unless (ab-font 'fixed14)
    (create-fixed14-font))
  (print-frame-newline-idiom)
  (let ((table
	  (make-attributes-table    ; unnecessarily adds a frame representation to frame
	    frame 'attributes-table-print-format
	    'attributes-table-text-cell-class-print-format
	    'attributes-table-text-cell-print-format
	    'attributes-table-text-cell-print-format
	    slots-to-include?)))
    (loop with table-format = (table-format table)
	  with column-boundary-width = (table-column-boundary-width table-format)
	  as row in (table-rows table)
	  do (let* ((remainder-of-row row)
		    (remaining-column-edges (column-edges table))
		    (cell-1
		      (or (pop remainder-of-row)
			  (progn
			    (pop remaining-column-edges)
			    (pop remainder-of-row))))
		    (pixels-per-character
		      (text-width-to-x
			(default-word-spacing (text-cell-format cell-1))))
		    (text-1 (text? cell-1))
		    (cell-2?
		      (if remainder-of-row (pop remainder-of-row)))
		    (left-edge-of-cell-2?
		      (if cell-2?
			  (+w (pop remaining-column-edges) column-boundary-width)))
		    (left-edge-of-cell-2-in-character-widths?
		      (if cell-2?
			  (round left-edge-of-cell-2? pixels-per-character)))
		    (text-2 (if cell-2? (text? cell-2?))))
	       (loop with indentation-in-character-widths-for-text-1 = 0
		     with indentation-in-character-widths-for-text-2 = 0
		     with text-line
		     with skip-first-formatting-char?
		     with explicit-indentation?
		     while (or text-1 text-2)
		     do (cond
			  ((and text-1
				(multiple-value-setq-some	; other values too?
				    (text-line nil nil text-1 explicit-indentation?)
				    (get-next-text-line text-1)))
			   ;; PUNT HERE!  To do: settle on a scheme whereby
			   ;; unicode is translated to whatever desired
			   ;; character set/encoding to whatever extend possible
			   ;; on the output side, and what callers must do to
			   ;; worry about this; also, should fix twrite-string
			   ;; to have start/end args, and lose the substring
			   ;; complexity.  Also, spend some a little more time
			   ;; to make this and the text-2 common code be a
			   ;; subroutine! For now: just make wide strings be
			   ;; text strings and handle as before, here and just
			   ;; below.  (MHD 12/18/95)
			   (setq skip-first-formatting-char?
				 (and (>=f (text-string-length text-line) 1)
				      (newline-p (charw text-line 0))))
			   (if explicit-indentation?
			       (setq indentation-in-character-widths-for-text-1
				     (round explicit-indentation? pixels-per-character)))
			   (loop repeat indentation-in-character-widths-for-text-1
				 do (print-frame-space-idiom))
			   (if skip-first-formatting-char?
			       (let ((temporary-substring
				       (text-string-substring text-line 1 nil)))
				 (print-frame-string-idiom temporary-substring)
				 (reclaim-text-string temporary-substring))
			       (print-frame-string-idiom text-line))
			   (if text-2
			       (loop repeat (-f left-edge-of-cell-2-in-character-widths?
						(+f (text-string-length text-line)
						    (if skip-first-formatting-char? -1 0)
						    indentation-in-character-widths-for-text-1))
				     do (print-frame-space-idiom))))
			  (text-2
			   (loop repeat left-edge-of-cell-2-in-character-widths?
				 do (print-frame-space-idiom))))
			(cond
			  ((and text-2
				(multiple-value-setq-some
				    (text-line nil nil text-2 explicit-indentation?)
				    (get-next-text-line text-2)))
			   (setq skip-first-formatting-char?
				 (and (>=f (text-string-length text-line) 1)
				      (newline-p (charw text-line 0))))
			   (if explicit-indentation?
			       (setq indentation-in-character-widths-for-text-2
				     (round explicit-indentation? pixels-per-character)))
			   (loop repeat indentation-in-character-widths-for-text-2
				 do (print-frame-space-idiom))
			   (if skip-first-formatting-char?
			       (let ((temporary-substring
				       (text-string-substring text-line 1 nil)))
				 (print-frame-string-idiom temporary-substring)
				 (reclaim-text-string temporary-substring))
			       (print-frame-string-idiom text-line))))
			(print-frame-newline-idiom))))
    (delete-frame table))
  frame)

;; Added destination-g2-stream? to support output to G2 streams for 3.0 Inspect
;; today.  Consider doing something to make the code smaller. (MHD 6/17/91)








;;;; Text Regions

;;  This used to be in module EDIT.  Fix forward references accordingly!



;;; A `text region' is a block that specifies a single arbitrary subsequence of
;;; the sequence of gensym characters in a text, where the text is the contents
;;; of a text box or a table cell.

;;; A text region is typically defined interactively (`marked') by a user first
;;; mousing down on one end and then up on the other.  The mouse-down end is
;;; called the `fixed end', because it remains fixed as the `free end' tracks
;;; the mouse until the mouse button is released.  The free end may be either
;;; before or after the fixed end (and may cross over the fixed end as the mouse
;;; is moved).

;;; A text region must be a subblock of either a text box or a table, and may be
;;; deleted by means of delete-frame.  The edges of a text region are the edges
;;; of the text cell (the area inside the borders of the text box or table
;;; cell).

;;; A `text highlight bar' is a rectangle that highlights part of all of a text
;;; line in a text region.  A text region has one text highlight bar subblock
;;; for each text line in the region; these subblocks must be in
;;; free-end-to-fixed-end order.  There must be at least one text highlight bar,
;;; even if it is empty.


;; Consider redoing text regions so that text highlight bar structures are not
;; needed.  Instead, the draw method for text regions would draw highlight bars
;; directly, and updating would be done by a series of (up to 3)
;; update-images-of-block calls, with appropriate update edges when drawing or
;; erasing part of a bar, where the end positions have been set up appropriately
;; before each call.  This revision might entail some kb fixup code in FILES.



(def-class (text-region block define-predicate)

  (line-index-for-fixed-end-of-text-region 1 vector-slot system save)
  (character-index-for-fixed-end-of-text-region 0 vector-slot system save)

  (line-index-for-free-end-of-text-region 1 vector-slot system save)
  (character-index-for-free-end-of-text-region 0 vector-slot system save)

  (row-index-for-text-region-cell? nil vector-slot system save)	    ; 0-based; nil for the
  (column-index-for-text-region-cell? nil vector-slot system save)  ;   text box case

  (text-highlight-bar-color foreground vector-slot system save))

;; Note that make-text-region depends on FOREGROUND being the default for
;; the text-highlight-bar-color slot.  (MHD 2/21/90)

(def-class-method initialize (text-region)
  (funcall-superior-method text-region)
  (set-render-frame-in-xor-overlay text-region))

(def-class-method generate-spot (text-region mouse-pointer)
  (generate-spot-for-aggregate text-region mouse-pointer))





(def-class (text-highlight-bar block define-predicate))

(def-class-method initialize (text-highlight-bar)
  (funcall-superior-method text-highlight-bar)
  (set-render-frame-in-xor-overlay text-highlight-bar))

(def-class-method draw (text-region)
  (declare (ignore text-region))
  ;; Nothing but subblocks (i.e. text-highlight-bar)
  )

(def-class-method generate-spot (text-highlight-bar mouse-pointer)
  (generate-spot-for-aggregate
    text-highlight-bar mouse-pointer))



;;; The `draw method for text-highlight-bar' uses with-defered-xor-drawing to
;;; schedule draw-text-highlight-bar-in-xor to do the actual drawing.  

(def-class-method draw (text-highlight-bar)
  (with-deferred-xor-drawing
    (draw-text-highlight-bar-in-xor
      text-highlight-bar
      (frame-serial-number text-highlight-bar))))

;; Previously (G2 1.0 through 5.0 Rev. 2), nothing was drawn if the highlight
;; bar is empty.  Now this draws a vertical hairline whenever there's nothing to
;; draw.  This appears as a kind of "sans-serif I-beam cursor", which is called
;; for in G2 because of the recent innovation of pending delete and the ability
;; to have selected regions separate from the cursor.  It also has the nice
;; benefit that on blank lines of text that have a text region, at least a
;; hairline is drawn, whereas previously there was no indication that a region
;; existed on those lines.  Somewhat for free came the slight improvement that
;; it now draws a vertical hairline in the highly unusual situation of non-empty
;; regions drawn on a workspace scaled down so far in X that it previously would
;; not have had any width at all.  Other changes here to consider: (a) draw the
;; fixed and free ends slightly differently to give the user feedback on which
;; direction things are headed; (b) draw a proper I-beam in the empty region
;; case.  (MHD 3/21/98)


(defun-void draw-text-highlight-bar-in-xor
    (text-highlight-bar reference-frame-serial-number)
  (when (frame-has-not-been-reprocessed-p
	  text-highlight-bar reference-frame-serial-number)
    (with-frame-transform-of-block-if-any (text-highlight-bar)
      (let ((left-edge-in-window
	      (x-in-window (left-edge-of-block text-highlight-bar)))
	    (right-edge-in-window
	      (x-in-window (right-edge-of-block text-highlight-bar)))
	    ;; not nec. for empty bar
	    (text-region
	      (superblock? text-highlight-bar)))
	;; This color lookup surely exists as a function somewhere?
	(let* ((text-box-or-table
		 (superblock? text-region))
	       (text-cell?
		 (if (row-index-for-text-region-cell? text-region)
		     (get-table-cell	; use macro version, for speed?
		       text-box-or-table
		       (row-index-for-text-region-cell? text-region)
		       (column-index-for-text-region-cell? text-region))))
  	       (text-box-format
 		 (if text-cell?
 		     (text-cell-format text-cell?)
 		     (text-box-format text-box-or-table)))
 	       (text-cell-plist
 		 (if text-cell?
 		     (text-cell-plist text-cell?)
 		     (text-cell-plist-for-text-box text-box-or-table)))
	       (background-color?
		 (or (if text-cell-plist
			 (getfq text-cell-plist 'background-color))
		     (text-cell-background-color? text-box-format)
		     (if text-cell?
			 (loop as supertable
				  = text-box-or-table
				  then (superblock? supertable)
			       thereis
			       (table-background-color?
				 (table-format supertable))
			       while (subtablep supertable)))))
	       (bar-background
		 (if background-color?
		     (map-color-or-metacolor-to-color-value background-color?)
		     current-background-color-value))
	       (bar-foreground
		 (map-color-or-metacolor-to-color-value
		   (text-highlight-bar-color text-region))))
	  (draw-solid-rectangle
	    left-edge-in-window
	    (y-in-window (top-edge-of-block text-highlight-bar))
	    
	    ;; This gets you either a hairline and/or an "I-Beam cursor"
	    ;; depending on how you look at it.
	    (if (>f right-edge-in-window left-edge-in-window)
		right-edge-in-window
		(+r left-edge-in-window 1))
	    
	    (y-in-window (bottom-edge-of-block text-highlight-bar))
	    (color-difference bar-foreground bar-background)))))))

;; The background color is assumed not to change while a text highlight bar is
;; drawn.  If it does, there could be turding.  Fix this, somehow, some day!



;;; `Make-text-region' makes a new text region as a subblock of
;;; text-box-or-table.  If text-cell? is specified, text-box-or-table must be
;;; the table that contains text-cell?; otherwise, text-box-or-table must be a
;;; text box.

;;; The fixed end of the new text region is specified by
;;; line-index-for-fixed-end and character-index-for-fixed-end.

;;; The initial position for the free end may be specified explicitly by
;;; end-or-line-index-for-free-end? and character-index-for-free-end?.  If
;;; end-or-line-index-for-free-end? is END, the free end will be at the end of
;;; the text.  If end-or-line-index-for-free-end? i nil, the new text region
;;; will be empty initially.

;;; If text-highlight-bar-color? is not specified, the foreground color of the
;;; text box or text cell (as best as can be determined) will be used.  If
;;; text-region- class? is not specified, TEXT-REGION will be used.

;;; Delete-frame may be used to delete a text region.  Note that text regions
;;; may be "automatically" deleted; see delete-any-text-regions.

(defun make-text-region
    (text-box-or-table text-cell?
		       line-index-for-fixed-end character-index-for-fixed-end
		       &optional end-or-line-index-for-free-end? character-index-for-free-end?
		       text-highlight-bar-color? text-region-class?)
  (let ((text-region (make-frame (or text-region-class? 'text-region))))
    (if text-cell?
	(multiple-value-bind
	    (left-edge-of-cell top-edge-of-cell right-edge-of-cell bottom-edge-of-cell
			       row-index column-index)
	    (get-table-cell-edges text-box-or-table text-cell?)

	  (set-edges-of-block text-region left-edge-of-cell top-edge-of-cell
			      right-edge-of-cell bottom-edge-of-cell)

	  (setf (row-index-for-text-region-cell? text-region) row-index)
	  (setf (column-index-for-text-region-cell? text-region) column-index)
	  (if (null text-highlight-bar-color?)	; may change arg
	      (setq text-highlight-bar-color?	; result can be nil
		    (or (getf (text-cell-plist text-cell?) 'line-color)
			(text-cell-line-color? (text-cell-format text-cell?))))))
	;; Otherwise a text-box
	(let ((text-box-format (text-box-format text-box-or-table))
	      #+old
	      (frame-description-reference?
		(fast-lookup-frame-description-reference-of-block? text-box-or-table)))
	  (set-edges-of-block text-region
			      (+w (left-edge-of-block text-box-or-table)
				  (text-box-left-border-width text-box-format))
			      (+w (top-edge-of-block text-box-or-table)
				  (text-box-top-border-width text-box-format))
			      (-w (right-edge-of-block text-box-or-table)
				  (text-box-right-border-width text-box-format))
			      (-w (bottom-edge-of-block text-box-or-table)
				  (text-box-bottom-border-width text-box-format)))
	  (unless text-highlight-bar-color?	; may change arg
	    (setq text-highlight-bar-color?	; result can be nil
		  (or (getf (text-cell-plist-for-text-box text-box-or-table)
			    'line-color)
		      (text-cell-line-color? text-box-format))))))
    
    (setf (line-index-for-free-end-of-text-region text-region)
	  (setf (line-index-for-fixed-end-of-text-region text-region)
		line-index-for-fixed-end))
    (setf (character-index-for-free-end-of-text-region text-region)
	  (setf (character-index-for-fixed-end-of-text-region text-region)
		character-index-for-fixed-end))
    (when text-highlight-bar-color?		; nil => default => FOREGROUND
      (setf (text-highlight-bar-color text-region) text-highlight-bar-color?))
    (add-subblock text-region text-box-or-table)
    (add-or-update-text-highlight-bar
      text-region text-cell? nil line-index-for-fixed-end
      character-index-for-fixed-end character-index-for-fixed-end)
    (when end-or-line-index-for-free-end?
      (case end-or-line-index-for-free-end?
	(end
	 (multiple-value-setq
	     (end-or-line-index-for-free-end? character-index-for-free-end?)
	   (find-end-of-text
	     (if text-cell?
		 (text? text-cell?)
		 (cdr (box-translation-and-text text-box-or-table)))
	     1))))
      (update-text-region
	text-region end-or-line-index-for-free-end?
	character-index-for-free-end?))
    text-region))



;;; `Update-text-region' updates text-region to have its free end (or its fixed
;;; end, if move-fixed-end? is specified) at the position given by
;;; line-index-for-new-end and character-index-for-new-end.  The new end
;;; position may be before or after the its old position and before or after the
;;; other end position.  Furthermore, the update may cause one end to "cross
;;; over" the other end.  The text region is assumed to be currently drawn.

(defun update-text-region
    (text-region line-index-for-new-end character-index-for-new-end
		 &optional move-fixed-end?)
  (when move-fixed-end? (reverse-text-region text-region))
  (let* ((text-cell?		; not nec. if free end doesn't move
	   (if (row-index-for-text-region-cell? text-region)
	       (get-table-cell
		 (superblock? text-region)
		 (row-index-for-text-region-cell? text-region)
		 (column-index-for-text-region-cell? text-region))))
	 (line-index-for-fixed-end
	   (line-index-for-fixed-end-of-text-region text-region))
	 (character-index-for-fixed-end
	   (character-index-for-fixed-end-of-text-region text-region))
	 (line-index-for-old-free-end
	   (line-index-for-free-end-of-text-region text-region))
	 (character-index-for-old-free-end
	   (character-index-for-free-end-of-text-region text-region))
	 (new-free-end-after-old-free-end?
	   (or (>f line-index-for-new-end line-index-for-old-free-end)
	       (and (=f line-index-for-new-end line-index-for-old-free-end)
		    (>f character-index-for-new-end
			character-index-for-old-free-end)))))

    (unless (and (=f line-index-for-new-end line-index-for-old-free-end)
		 (=f character-index-for-new-end
		     character-index-for-old-free-end))
      (if (or (>f line-index-for-old-free-end line-index-for-fixed-end)
	      (and (=f line-index-for-old-free-end line-index-for-fixed-end)
		   (or (>f character-index-for-old-free-end
			   character-index-for-fixed-end)
		       (and (=f character-index-for-old-free-end
				character-index-for-fixed-end)
			    new-free-end-after-old-free-end?))))
	  (cond   ; free end after fixed end OR empty bar stretching forward
	    (new-free-end-after-old-free-end?
	     (loop for line-index		; stretch
		   from line-index-for-old-free-end
		       to line-index-for-new-end
		   do (add-or-update-text-highlight-bar
			text-region text-cell?
			(if (=f line-index line-index-for-old-free-end) 'right)
			line-index 0
			(if (=f line-index line-index-for-new-end)
			    character-index-for-new-end))))
	    ((or (>f line-index-for-new-end line-index-for-fixed-end)
		 (and (=f line-index-for-new-end line-index-for-fixed-end)
		      (>=f character-index-for-new-end
			   character-index-for-fixed-end)))
	     (loop until (=f line-index-for-old-free-end  ; shrink
			     line-index-for-new-end)
		   do (when (has-subblocks-p text-region) ; just to be safe
			(delete-frame (first-subblock text-region)))
		      (decff line-index-for-old-free-end))
	     (add-or-update-text-highlight-bar
	       text-region text-cell? 'right
	       line-index-for-new-end 0 character-index-for-new-end))
	    (t (update-text-region		; cross over
		 text-region
		 line-index-for-fixed-end character-index-for-fixed-end)
	       (update-text-region
		 text-region
		 line-index-for-new-end character-index-for-new-end)))
	  (cond	   ; free end before fixed end OR empty bar stretching backward
	    ((not new-free-end-after-old-free-end?)
	     (loop for line-index		; stretch
		   from line-index-for-old-free-end
		   downto line-index-for-new-end
		   do (add-or-update-text-highlight-bar
			text-region text-cell?
			(if (=f line-index line-index-for-old-free-end) 'left)
			line-index
			(if (=f line-index line-index-for-new-end)
			    character-index-for-new-end
			    0)
			nil)))
	    ((or (<f line-index-for-new-end line-index-for-fixed-end)
		 (and (=f line-index-for-new-end line-index-for-fixed-end)
		      (<=f character-index-for-new-end
			   character-index-for-fixed-end)))
	     (loop until (=f line-index-for-old-free-end	; shrink
			     line-index-for-new-end)
		   do (when (has-subblocks-p text-region)	; just to be safe
			(delete-frame (first-subblock text-region)))
		      (incff line-index-for-old-free-end))
	     (add-or-update-text-highlight-bar
	       text-region text-cell? 'left
	       line-index-for-new-end character-index-for-new-end nil))
	    (t (update-text-region		; cross over
		 text-region
		 line-index-for-fixed-end character-index-for-fixed-end)
	       (update-text-region
		 text-region
		 line-index-for-new-end character-index-for-new-end))))
      (setf (line-index-for-free-end-of-text-region text-region)
	    line-index-for-new-end)
      (setf (character-index-for-free-end-of-text-region text-region)
	    character-index-for-new-end)))
  (when move-fixed-end? (reverse-text-region text-region)))

;; Consider simplifying this by combining the code for the various cases.  In
;; particular, consider defining and using, here and elsewhere, text-position-<
;; et al.




(defun Change-color-of-text-region (text-region new-color)
  (unless (eq (text-highlight-bar-color text-region) new-color)
    (erase-images-of-block text-region t)
    (setf (text-highlight-bar-color text-region) new-color)
    (draw-images-of-block text-region t)))

;; Consider redoing this to use the do-color-revision macro or to work
;; at a lower level if that would be more efficient.






;;; `Reverse-text-region' exchanges the fixed and free ends of text-region.

(defun reverse-text-region (text-region)
  (let ((line-index-for-fixed-end-of-text-region
	  (line-index-for-fixed-end-of-text-region text-region))
	(character-index-for-fixed-end-of-text-region
	  (character-index-for-fixed-end-of-text-region text-region)))
    (setf (line-index-for-fixed-end-of-text-region text-region)
	  (line-index-for-free-end-of-text-region text-region))
    (setf (character-index-for-fixed-end-of-text-region text-region)
	  (character-index-for-free-end-of-text-region text-region))
    (setf (line-index-for-free-end-of-text-region text-region)
	  line-index-for-fixed-end-of-text-region)
    (setf (character-index-for-free-end-of-text-region text-region)
	  character-index-for-fixed-end-of-text-region)
    (setf (subblocks text-region)
	  #-subblocks-v2
	  (nreverse (subblocks text-region))
	  #+subblocks-v2
	  (constant-queue-nreverse (subblocks text-region)))))

(defun-simple text-region-oriented-forward-p (text-region)
  (or (>f (line-index-for-free-end-of-text-region text-region)
	  (line-index-for-fixed-end-of-text-region text-region))
      (and (=f (line-index-for-free-end-of-text-region text-region)
	       (line-index-for-fixed-end-of-text-region text-region))
	   (>=f (character-index-for-free-end-of-text-region text-region)
		(character-index-for-fixed-end-of-text-region text-region)))))

(defun-simple text-region-oriented-backward-p (text-region)
  (not (text-region-oriented-forward-p text-region)))

;; Use names forward/backward to be BIDI friendly.  (These deal with logical
;; character indices, which are the reverse of the visual direction.)

;; What's the orientation of the null region?  (= empty-text-region-p)
;; ANS: forward



;;; The macros `backward-line-index-of-text-region',
;;; `backward-character-index-of-text-region', `forward-line-index-of-text-region', and
;;; `forward-character-index-of-text-region' give the start and end positions for
;;; the earlier and later ends, respectively, of a text region.

(def-substitution-macro backward-line-index-of-text-region (text-region)
  (minf (line-index-for-fixed-end-of-text-region text-region)
	(line-index-for-free-end-of-text-region text-region)))

(def-substitution-macro backward-character-index-of-text-region (text-region)
  (if (text-region-oriented-forward-p text-region)
      (character-index-for-fixed-end-of-text-region text-region)
      (character-index-for-free-end-of-text-region text-region)))

(def-substitution-macro forward-line-index-of-text-region (text-region)
  (maxf (line-index-for-fixed-end-of-text-region text-region)
	(line-index-for-free-end-of-text-region text-region)))

(def-substitution-macro forward-character-index-of-text-region (text-region)
  (if (text-region-oriented-forward-p text-region)
      (character-index-for-free-end-of-text-region text-region)
      (character-index-for-fixed-end-of-text-region text-region)))



;;; `Has-text-regions-p' is true if text-box-or-table has any text regions
;;; (other than exception-text-region?, if that is specified).

(defun has-text-regions-p (text-box-or-table &optional exception-text-region?)
  (loop for subblock being each subblock of text-box-or-table
	unless (eq subblock exception-text-region?)
	  thereis (frame-of-class-p subblock 'text-region)))

(defun empty-text-region-p (text-region)
  (and (=f (character-index-for-fixed-end-of-text-region
	     text-region)
	   (character-index-for-free-end-of-text-region
	     text-region))
       (=f (line-index-for-fixed-end-of-text-region
	     text-region)
	   (line-index-for-free-end-of-text-region
	     text-region))))



;;; `Within-text-region-p' is true if the position (line-index, character-index)
;;; is outside of the text region, or if text-region is empty.

(defun within-text-region-p (text-region line-index character-index)
  (let ((l-fixed (line-index-for-fixed-end-of-text-region text-region))
	(l-free (line-index-for-free-end-of-text-region text-region))
	(c-fixed (character-index-for-fixed-end-of-text-region text-region))
	(c-free (character-index-for-free-end-of-text-region text-region)))
    (cond
      ((=f l-fixed l-free)
       (and (not (=f c-fixed c-free))	; empty region => no (don't allow them)
	    (or (not (=f line-index l-fixed))
		(<f character-index (minf c-fixed c-free))
		(>f character-index (maxf c-fixed c-free)))))
      ((<f l-fixed l-free)
       (or (<f line-index l-fixed)
	   (and (=f line-index l-fixed)
		(<f character-index c-fixed))
	   (>f line-index l-free)
	   (and (=f line-index l-free)
		(>f character-index c-free))))
      ((>f l-fixed l-free)
       (or (>f line-index l-fixed)
	   (and (=f line-index l-fixed)
		(>f character-index c-fixed))
	   (<f line-index l-free)
	   (and (=f line-index l-free)
		(<f character-index c-free)))))))
       
       
	   



;;; `Delete-any-text-regions' deletes any text regions of text-box-or-table,
;;; except that (1) exception-text-region? is not deleted and (2) only text
;;; regions in the specified area are deleted when one or more area edges are
;;; specified.

(defun delete-any-text-regions
    (text-box-or-table
      &optional
      left-edge-of-area? top-edge-of-area?
      right-edge-of-area? bottom-edge-of-area?
      exception-text-region?)
  (loop
    while
    (loop
      for subblock being each subblock of text-box-or-table
      when (and
	     (frame-of-class-p subblock 'text-region)
	     (or (null exception-text-region?)
		 (not (eq subblock exception-text-region?)))
	     (or (null left-edge-of-area?)
		 (>=w (left-edge-of-block subblock) left-edge-of-area?))
	     (or (null top-edge-of-area?)
		 (>=w (top-edge-of-block subblock) top-edge-of-area?))
	     (or (null right-edge-of-area?)
		 (<=w (right-edge-of-block subblock) right-edge-of-area?))
	     (or (null bottom-edge-of-area?)
		 (<=w (bottom-edge-of-block subblock) bottom-edge-of-area?)))
	do (delete-frame subblock)
	   (return t))))

;; Fix calls to take advantage of optional arguments!

;; Later, when a text region is deleted in this way, the user on the workstation
;; associated with the text region should be notified.

;; This is used by reformat-text-box-in-place, make-or-reformat-table, update-
;; representations-in-tables, and change-edit-box.  Consider, at least in some
;; of these functions, trying to update text regions appropriately.



;;; `Get-text-region-position' returns six values relating to text-region, but
;;; with line-index-for-free-end? and character-index-for-free-end? overriding
;;; the actual position of the free end when they are specified:

;;;    (1) the text tail for its beginning;
;;;    (2) the line index of its beginning;
;;;    (3) the character index of its beginning; 
;;;    (4) the line index of its end;
;;;    (5) the character index of its end; and
;;;    (6) the text cell it is within, if it is a subblock of a table.
;;;    (7) the entire text it is within

(defun get-text-region-position
       (text-region &optional line-index-for-free-end? character-index-for-free-end?)
  (let* ((text-box-or-table (superblock? text-region))
	 (text-cell?
	   (if (row-index-for-text-region-cell? text-region)
	       (get-table-cell
		 text-box-or-table
		 (row-index-for-text-region-cell? text-region)
		 (column-index-for-text-region-cell? text-region))))
	 (text
	   (if text-cell?
	       (text? text-cell?)
	       (cdr (box-translation-and-text text-box-or-table))))
	 (line-index-for-fixed-end
	   (line-index-for-fixed-end-of-text-region text-region))
	 (character-index-for-fixed-end
	   (character-index-for-fixed-end-of-text-region text-region))
	 (line-index-for-free-end
	   (or line-index-for-free-end?
	       (line-index-for-free-end-of-text-region text-region)))
	 (character-index-for-free-end
	   (or character-index-for-free-end?
	       (character-index-for-free-end-of-text-region text-region))))
    (if (or (>f line-index-for-free-end line-index-for-fixed-end)
	    (and (=f line-index-for-free-end line-index-for-fixed-end)
		 (>f character-index-for-free-end character-index-for-fixed-end)))
	(values
	  (find-text-tail-for-line text line-index-for-fixed-end)	; fix later!
	  line-index-for-fixed-end
	  character-index-for-fixed-end
	  line-index-for-free-end
	  character-index-for-free-end
	  text-cell?
	  text)
	(values
	  (find-text-tail-for-line text line-index-for-free-end)	; fix later!
	  line-index-for-free-end
	  character-index-for-free-end
	  line-index-for-fixed-end
	  character-index-for-fixed-end
	  text-cell?
	  text))))



(defun length-of-text-in-region (text-region)
  (let (start-line-index start-character-index
	end-line-index end-character-index)
    (cond
      ((or (<f (line-index-for-free-end-of-text-region text-region)
	       (line-index-for-fixed-end-of-text-region text-region))
	   (and (=f (line-index-for-free-end-of-text-region text-region)
		    (line-index-for-fixed-end-of-text-region text-region))
		(<f (character-index-for-free-end-of-text-region text-region)
		    (character-index-for-fixed-end-of-text-region text-region))))
       (setq start-line-index
	     (line-index-for-free-end-of-text-region text-region))
       (setq start-character-index
	     (character-index-for-free-end-of-text-region text-region))
       (setq end-line-index
	     (line-index-for-fixed-end-of-text-region text-region))
       (setq end-character-index
	     (character-index-for-fixed-end-of-text-region text-region)))
      (t
       (setq start-line-index
	     (line-index-for-fixed-end-of-text-region text-region))
       (setq start-character-index
	     (character-index-for-fixed-end-of-text-region text-region))
       (setq end-line-index
	     (line-index-for-free-end-of-text-region text-region))
       (setq end-character-index
	     (character-index-for-free-end-of-text-region text-region))))
    (loop with text-box = (superblock? text-region)
	  with text = (cdr (box-translation-and-text text-box))
	  for character being each text-character of text
	  line start-line-index
	  character start-character-index
	  end-line end-line-index
	  end-character end-character-index
	  ;; note that character is not really used
	  count t into count
	  do (progn
	       #+development
	       (when (=f count 64001)
		 (cerror "Continue looping indefinitely"
			 "MHD: More that 64000 characters in text counted; probable infinite loop!")))
	  finally (return count))))



;;; `Convert-text-region-to-text-string' returns a new text string, the content of which
;;; is that of text-region, but with line-index-for-free-end? and character-index-for-
;;; free-end? overriding the actual position of the free end when they are specified.

(defun convert-text-region-to-text-string
       (text-region &optional line-index-for-free-end? character-index-for-free-end?)
  (multiple-value-bind (text-tail
			beginning-line-index beginning-character-index
			end-line-index end-character-index)
      (get-text-region-position
	text-region line-index-for-free-end? character-index-for-free-end?)
    (convert-text-to-text-string
      nil text-tail
      beginning-line-index beginning-character-index
      end-line-index end-character-index)))



;;; Convert-text-region-to-text ... 

;(defun convert-text-region-to-text (text-region)
;  (multiple-value-bind (text-tail
;			 beginning-line-index beginning-character-index
;			 end-line-index end-character-index)
;      (get-text-region-position
;	text-region)
;    (loop with line-index = (-f beginning-line-index 1)
;	  with lost-spaces = 1
;	  with hyphen-added? = nil
;	  with context-carryover? = nil
;	  with lost-spaces-value?
;	  as text-element in text-tail		; null test unnecessary
;	  do (cond
;	       ((setq lost-spaces-value? (lost-spaces-value-if-any text-element))
;		(setq lost-spaces 0))
;	       ((consp text-element)
;		(case (first text-element)
;		  (hyphen-added
;		   (setq hyphen-added? text-element))
;		  (context-carryover
;		   (setq context-carryover? text-element)))))
;	  when (text-line-p text-element)
;	    nconc
;	    (prog1
;		(let* ((line-length (length text-element))
;		       (start
;			 (if (=f (incff line-index)	; ugly incff
;				 beginning-line-index)
;			     beginning-character-index
;			     0))		; nil?
;		       (end
;			 (if (=f line-index end-line-index)
;			     end-character-index
;			     (+f line-length
;				 (if (fixnump lost-spaces)
;				     lost-spaces
;				     (text-string-length lost-spaces)))))
;		       (lost-spaces-start
;			 (maxf (-f start line-length) 0))
;		       (lost-spaces-end
;			 (maxf (-f end line-length) 0))
;		       (lost-spaces-length
;			 (-f lost-spaces-end lost-spaces-start)))
;		  (nconc
;		    (cond
;		      ((and (text-string-p lost-spaces)
;			    (not (=f lost-spaces-length 0)))
;		       (slot-value-list
;			 (make-lost-spaces-text-element 
;			   (text-string-substring
;			     lost-spaces
;			     lost-spaces-start lost-spaces-end))))
;		      ((not (=f lost-spaces-length 1))
;		       (slot-value-list
;			 (make-lost-spaces-text-element lost-spaces-length))))
;		    (if (and hyphen-added?
;			     (not (=f line-index end-line-index)))
;			(slot-value-list
;			  (copy-list-using-slot-value-conses
;			    hyphen-added?)))
;		    (if (and context-carryover?
;			     (not (=f line-index beginning-line-index)))
;			(slot-value-list
;			  (copy-list-using-slot-value-conses
;			    context-carryover?)))
;		    (slot-value-list
;		      (text-string-substring	; later, fix for context!!
;			text-element
;			(minf start line-length)
;			(minf end line-length)))))
;	      (setq lost-spaces 1))
;	  until (=f line-index end-line-index))))	; ugly termination

;; This used to be used in scrap-text-region, but is no longer used anywhere.  However,
;; it has been kept, commented out, because, unlike convert-text-region-to-text-string,
;; it does preserve the line breaks of the text region, and therefore might someday be
;; useful.



;;; `Add-or-update-text-highlight-bar' is used by make-text-region and
;;; update-text-region to add or update a text highlight bar.  When update-end?
;;; is specified (as LEFT or RIGHT), the first subblock of text-region is
;;; revised accordingly.  When update-end?  is LEFT, end? is irrelevant; when
;;; update-end? is RIGHT, start is irrelevant.

;;; At present, text highlight bars should never be saved in KBs, so when a new
;;; text highlight bar frame is created, it has its do-not-save-in-kb frame flag
;;; set.  Note, however, that this was not done prior to 4/9/91 (3.0), so it is
;;; conceivable that there could be some instances present in old KBs (2.1 or
;;; earlier).

(defun add-or-update-text-highlight-bar
    (text-region text-cell? update-end? line-index start end?)
  (let* ((text-highlight-bar
	   (if update-end?
	       (first-subblock text-region)
	       (let ((text-highlight-bar
		       (make-frame 'text-highlight-bar)))
		 (set-do-not-save-in-kb text-highlight-bar)
		 text-highlight-bar)))
	 (text-box-or-table (superblock? text-region))
	 (text-box-format
	   (if text-cell?
	       (text-cell-format text-cell?)
	       (text-box-format text-box-or-table)))
	 (text-cell-plist
	   (if text-cell?
	       (text-cell-plist text-cell?)
	       (text-cell-plist-for-text-box text-box-or-table)))
	 (line-height (text-cell-line-height text-box-format))	 ; not nec. for update case
	 (line-spacing (text-cell-line-spacing text-box-format)) ; not nec. for update case
	 (font-map (text-cell-font-map text-box-format))
	 (default-word-spacing (default-word-spacing text-box-format))
	 (unmagnified-distance-from-top-so-far 0)	; not nec. for update case
	 (indentation 0)
	 (word-spacing default-word-spacing)
	 (lost-spaces 1)
	 (left-edge-of-text
	   (+w (left-edge-of-block text-region)
	       (text-cell-left-margin text-box-format)))
	 (top-edge-of-text
	   (+w (top-edge-of-block text-region)
	       (text-cell-top-margin text-box-format)))
	 (text-line
	   (loop with lost-spaces-value?
		 for text-element
		     in (if text-cell?
			    (text? text-cell?)
			    (cdr (box-translation-and-text text-box-or-table)))
		 with preceding-line-index = 0
		 do (cond
		      ((text-line-p text-element)
		       (if (=f (incff preceding-line-index) line-index)
			   (return text-element))
		       (setq unmagnified-distance-from-top-so-far  ; not nec. for update case
			     (+w unmagnified-distance-from-top-so-far
				 line-height line-spacing))
		       (setq word-spacing default-word-spacing)
		       (setq lost-spaces 1))
		      ((fixnump text-element)
		       (setq indentation text-element))
		      ((setq lost-spaces-value? (lost-spaces-value-if-any text-element))
		       (setq lost-spaces lost-spaces-value?))
		      ((eq (car text-element) 'leading)	; not nec. for update case
		       (setq unmagnified-distance-from-top-so-far
			     (+w unmagnified-distance-from-top-so-far
				 (cdr text-element))))
		      ((eq (car text-element) 'word-spacing)
		       (setq word-spacing (cdr text-element))))))
	 (x-magnification
	   (or (getfq text-cell-plist 'x-magnification)
	       (text-cell-x-magnification? text-box-format)
	       #.(convert-to-magnification-at-compile-time 1)))
	 (unmagnified-distance-of-left-edge-of-bar-from-left?
	   (case update-end?
	     (right nil)
	     (t (+w indentation
		    (compute-width-of-text-line	; computes to origin, not necessarily the
						; the left extent, of the start character
		      text-line 0 start font-map word-spacing nil lost-spaces)))))
	 (left-edge-for-bar
	   (if unmagnified-distance-of-left-edge-of-bar-from-left?
	       (minw (+w left-edge-of-text
			 (magnify
			   unmagnified-distance-of-left-edge-of-bar-from-left?
			   x-magnification))
		     (if (block-is-transformed-p text-region) ;; Note A.
			  most-positive-workspace-coordinate
			  (right-edge-of-block text-region)))
	       (left-edge-of-block text-highlight-bar)))
	 (right-edge-for-bar
	   (case update-end?
	     (left
	      (right-edge-of-block text-highlight-bar))
	     (t (minw (+w left-edge-of-text
			  (magnify
			    (+w (or unmagnified-distance-of-left-edge-of-bar-from-left?
				    indentation)
				(compute-width-of-text-line
				  text-line
				  (if unmagnified-distance-of-left-edge-of-bar-from-left?
				      start
				      0)
				  end? font-map word-spacing nil lost-spaces))
			    x-magnification))
		      (if (block-is-transformed-p text-region) ;; Note A.
			  most-positive-workspace-coordinate
			  (right-edge-of-block text-region))))))
	 (left-edge-of-update-area     ; in update case, include extra to ensure
	   (case update-end?	       ;   proper updating of graphic element memory!?
	     (left (minw (left-edge-of-block text-highlight-bar) left-edge-for-bar))
	     (right (minw (right-edge-of-block text-highlight-bar) right-edge-for-bar))
	     (t left-edge-for-bar)))
	 (right-edge-of-update-area
	   (case update-end?
	     (right (maxw (right-edge-of-block text-highlight-bar) right-edge-for-bar))
	     (left (maxw (left-edge-of-block text-highlight-bar) left-edge-for-bar))
	     (t right-edge-for-bar)))
	 (new-top? nil)
	 (new-bottom? nil))
    
    (cond (update-end?
	       (update-images-of-rectangle-of-block
		 text-highlight-bar nil
		 left-edge-of-update-area
		 (top-edge-of-block text-highlight-bar)
		 right-edge-of-update-area
		 (bottom-edge-of-block text-highlight-bar))
	       #+old ;; Doesn't do approprate XOR handling!
	       (update-images
		 t text-highlight-bar text-region
		 left-edge-of-update-area
		 (top-edge-of-block text-highlight-bar)
		 right-edge-of-update-area
		 (bottom-edge-of-block text-highlight-bar)
		 nil 'draw-block text-highlight-bar))
	  (t
	   (let* ((y-magnification
		    (or (getfq text-cell-plist 'y-magnification)
			(text-cell-y-magnification? text-box-format)
			#.(convert-to-magnification-at-compile-time 1)))
		  (extra-height-for-bar-above-and-below
		    (maxw 0 (-w (halfw line-spacing) 1))))	; parameterize? change formula?
	     (setf new-top?
		   (+w top-edge-of-text
		       (magnify
			 (-w unmagnified-distance-from-top-so-far
			     extra-height-for-bar-above-and-below)
			 y-magnification)))
	     (setf new-bottom?
		   (+w top-edge-of-text
		       (magnify
			 (+w unmagnified-distance-from-top-so-far
			     line-height
			     extra-height-for-bar-above-and-below)
			 y-magnification))))))

    (change-edges-of-block text-highlight-bar
			   left-edge-for-bar new-top?
			   right-edge-for-bar new-bottom?)
    (when (<w (right-edge-of-block text-region) right-edge-for-bar)
      (setf (right-edge-of-block text-region) right-edge-for-bar))

    (unless update-end?
      (add-subblock text-highlight-bar text-region))
    ;; Now, with scrolling, the text and hence the text region can
    ;; extend beyond the right and bottom edges of the enclosing block
    ;; which happens to be the initial binding for this.
    (loop for subblock being each subblock of text-region
	  as new-bottom = (bottom-edge-of-block subblock)
	  when (<w (bottom-edge-of-block text-region) new-bottom)
	    do (setf (bottom-edge-of-block text-region) new-bottom)
	  when (<w (right-edge-of-block text-region) right-edge-for-bar)
	    do (setf (right-edge-of-block text-region) right-edge-for-bar))
    (update-images-of-rectangle-of-block
      text-highlight-bar nil
      left-edge-of-update-area (top-edge-of-block text-highlight-bar)
      right-edge-of-update-area (bottom-edge-of-block text-highlight-bar))
    #+old
    (update-images
      nil text-highlight-bar text-region
      left-edge-of-update-area (top-edge-of-block text-highlight-bar)
      right-edge-of-update-area (bottom-edge-of-block text-highlight-bar)
      nil 'draw-block text-highlight-bar)))

;; Note A: See Note A on update-text-in-edit-box.

;; Revise the handling of y magnification in draw-text-segment to be compatible
;; with its use here!

;; Consider avoiding computing unmagnified-distance-from-top-so-far,
;; indentation, word- spacing, and text-line by having them as arguments.  In
;; any case, abstract the computation into
;; compute-distance-of-text-line-from-top, defined above!  See also
;; compute-height-for-text in module BOXES.






;;; Mark-occurrences-of-string-in-text ... returns the number of times the
;;; text occurred and was marked.  This does not add a new mark if one exists
;;; already, so this can be called any number of times without worry about
;;; xor problems or adding large numbers of blocks.  

(defun mark-occurrences-of-string-in-text
       (text-box-or-table text-cell?
	string-to-look-for observe-word-boundaries?)  
  (loop with end-line-index? = 1
	with end-character-index? = 0
	with beginning-line-index?
	with beginning-character-index?
	with row-index-for-text-region-cell? = nil
	with column-index-for-text-region-cell? = nil
	with default-highlight-bar-color
	  = (get-slot-init-form 'text-region 'text-highlight-bar-color)
	with text
	  = (if text-cell?
		(text? text-cell?)
		(cdr (box-translation-and-text text-box-or-table)))
	initially
	  (when text-cell?
	    (multiple-value-setq
		(row-index-for-text-region-cell?
		  column-index-for-text-region-cell?)
	      (get-table-cell-indices text-box-or-table text-cell?)))
	while
	  (multiple-value-setq
	    (beginning-line-index? beginning-character-index?
	     end-line-index? end-character-index?)
	    (find-string-in-text-for-inspect
	      string-to-look-for text observe-word-boundaries?
	      end-line-index? end-character-index?))
	count
	  (progn
	    (unless
	      (loop for subblock being each subblock of text-box-or-table
		    thereis
		      (and (frame-of-class-p subblock 'text-region)
			   (=f beginning-line-index?
			       (line-index-for-fixed-end-of-text-region
				 subblock))
			   (=f beginning-character-index?
			       (character-index-for-fixed-end-of-text-region
				 subblock))
			   (=f end-line-index?
			       (line-index-for-free-end-of-text-region
				 subblock))
			   (=f end-character-index?
			       (character-index-for-free-end-of-text-region
				 subblock))
			   (eql column-index-for-text-region-cell?
				(column-index-for-text-region-cell? subblock))
			   (eql row-index-for-text-region-cell?
				(row-index-for-text-region-cell? subblock))
			   (eq default-highlight-bar-color
			       (text-highlight-bar-color subblock))))
	      (make-text-region
		text-box-or-table text-cell?
		beginning-line-index? beginning-character-index?
		end-line-index? end-character-index?))
	    t)))

;; The was moved here from the section Text Searching in BOXES because there
;; were many macro forward references.  (MHD 5/2/91)





;;;; Table Visiblity



;;; The function `table-visible-p', patterned to some extent after
;;; text-box-visible-p. It returns either nil or t.  It works somewhat
;;; heuristically, and cannot absolutely guarantee that its result will jibe
;;; with actual visibility.  Unlike text-box-visible-p, this does not look at
;;; the text, or any other aspect, of the individual cells of a table.  It only
;;; looks at graphical features of the table itself, including borders,
;;; background color, row boundaries, and column boundaries.

(defun table-visible-p (table)
  (let* ((table-format (table-format table))
	 (background-color? (table-background-color? table-format)))
    (or
      ;; background color visible?
      (and background-color?
	   (not (eq background-color? 'transparent)))
      ;; outer border(s) visible?
      (or (>w (table-left-border-width table-format) 0)
	  (>w (table-top-border-width table-format) 0)
	  (>w (table-right-border-width table-format) 0)
	  (>w (table-bottom-border-width table-format) 0))
      ;; row or cell boundaries visible?
      (or
	(and (table-column-boundary-color? (table-format table))
	     (>w (table-column-boundary-width table-format) 0)
	     ;; a row with more than one cell? (column)
	     (loop for row in (table-rows table)
		   thereis (loop for (cell? . more?) on row
				 when cell? return more?)))
	(and (table-row-boundary-color? (table-format table))
	     (>w (table-row-boundary-width table-format) 0)
	     ;; more than one row?
	     (cdr (table-rows table)))))))

;; As with text-box-visible-p, this is somewhat heuristic.  It considers having
;; any border be non-zero-width to indicate visibility; thus, it would not
;; consider invisible a border that's non-zero-width but is in the transparent
;; metacolor or is in the same color as whatever's behind the table.

;; Consider returning true if table is opaque-block-p.  In practice this just
;; applies only to graphs, which appear visible in all cases due to always
;; having a cell that's a block.



;;; The function `text-cell-visible-in-image-plane-p' returns true or false
;;; (nil) if it determines that text-cell is invisible in image-plane.

;;; The function `text-cell-visible-without-text-in-image-plane-p' is true if
;;; text-cell is (or seems to be) visible in image-plane based only its
;;; coloring, not its text, e.g., having a background color, having a highlight
;;; color, or being selected, implying a visible highlight rectangle.  Note,
;;; however, that this does not take into account text-cell boundaries' or
;;; borders' widths or colors.

;;; The function `text-cell-text-visible-in-image-plane-p' is true if
;;; text-cell's text is visible in image-plane.

(defun text-cell-visible-without-text-in-image-plane-p (text-cell image-plane)
  (or
    ;; selected?
    (thing-selected-p text-cell image-plane)
    (let* ((format (text-cell-format text-cell))
	   (plist (text-cell-plist text-cell))
	   (background-color?
	     (or (text-cell-background-color? format)
		 (getf plist 'background-color))))
      (or
	;; background color visible?
	(and background-color?
	     (not (eq background-color? 'transparent)))
	;; highlighted?
	(getf plist 'highlight-color)))))



(defun text-cell-text-visible-in-image-plane-p (text-cell image-plane)
  (with-image-plane-transform (image-plane)
    (text-visible-p
      (text-cell-format text-cell) (text-cell-plist text-cell)
      current-image-x-scale current-image-y-scale)))



(defun text-cell-visible-in-image-plane-p (text-cell table image-plane)
  (declare (ignore table))		; not currently needed
  (let* ((text-visible?
	   (text-cell-text-visible-in-image-plane-p text-cell image-plane)))
    (if (text-cell-visible-without-text-in-image-plane-p text-cell image-plane)
	(if text-visible? t :without-text)
	(if text-visible? :just-text))))

;; Consider cacheing the cell visibility determinations instead of recomputing
;; each time for efficiency.  The visibility of text could be cached in a bit in
;; the table, and cache could be invalidated whenever the table is reformatted,
;; which generally happens only rarely. (MHD 9/5/03)



;;; The function `table-visible-in-image-plane-p' returns true or false (nil) if
;;; it determines that table is visible in image-plane. This uses various
;;; heuristics. Either:
;;;
;;;   (1) table is table-visible-p (q.v., for details);
;;;   (2) table is selected in image-plane; or
;;;   (3) cell? is non-nil and is either
;;;       (a) a block; or
;;;       (b) a text cell that is selected in image-plane
;;;
;;; This is primarily called from fill-out-text-spot in the table case.

(defun table-visible-in-image-plane-p (table cell? image-plane)
  (or (table-visible-p table)
      ;; selected, i.e., showing a selection border?
      (thing-selected-p table image-plane)
      (and cell?
	   (or (cell-is-block-p cell?)
	       (thing-selected-p cell? image-plane)))))


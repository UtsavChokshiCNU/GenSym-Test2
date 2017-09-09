;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module Icons (formerly part of entities)

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Mark H. David, Ong, Peng Tsin,
;;; Stephen R. DeVoy, Andreas Hofmann, and Lowell B. Hawkinson


;; To FRAMES2
(declare-forward-reference get-slot-value-function function)

;; To FRAMES4
(declare-forward-reference reclaim-slot-value function)

;; To PRINTING

(declare-forward-reference printing-icon-current-region-index? variable)
(declare-forward-reference native-printing-p function)

;; To BOXES

(declare-forward-reference orient-and-scale-and-paint-text function)

;; To DEFINITIONS

(declare-forward-reference find-image-data function)
(declare-forward-reference icon-decaching-parameters function)

#+development
(declare-forward-reference construct-image-info-from-image-data function)

;; To ENTITIES

(declare-forward-reference override-icon-description-for-system-defined-class-ab function)

;; To G2-BPEL

(declare-forward-reference revert-if-g2gl-object-icon-substitution function)

;;;; First, first Common facilities to all aspects of Drawing

;;;; Slot Value Conses


(defconser slot-value icons)

(defun reclaim-slot-value-list-function (slot-value-list)
  (reclaim-slot-value-list slot-value-list))


;; To FORMATS

(declare-forward-reference get-or-make-format-frame-function function)

;;;; Mapping Colors or Metacolors


;; To BOXES

(declare-forward-references
  (reclaim-text function)
  (convert-text-string-to-text function)
  (format-text function) 
  (text-line-p-function function))

;; To CONTROLS

(declare-forward-references
  (extrema-for-line-drawing-element function)
  (compute-extrema-for-text-drawing-element function))


(defun-substitution-macro map-color-or-metacolor-to-color-value
    (color-or-metacolor)
  (case color-or-metacolor
    (background
     current-background-color-value)
    ((foreground workspace-foreground)			    ; pick one!!!
     current-foreground-color-value)
    (transparent					    ; This is a convenient lie.
     current-background-color-value)
    (t
     (map-to-color-value color-or-metacolor))))


(def-substitution-macro transparent-color-p (color)
  (eq color 'transparent))

(def-substitution-macro becoming-transparent-p (old-color new-color)
  (and (not (transparent-color-p old-color))
       (transparent-color-p new-color)))


(defun-substitution-macro transparent-color-pattern-p (color-or-color-pattern)
  (cond ((atom color-or-color-pattern)
	 (transparent-color-p color-or-color-pattern))
	(t
	 (loop for element in color-or-color-pattern
	       as color = (if (atom element) element (cdr element))
	       thereis (transparent-color-p color)))))

;; A color-pattern is an alist of (region . color).


(defmacro color-meaning-no-change ()
  `(if (paint-mode-p) transparent-color-value 0))


;;; The function `metacolor-difference' returns the "color difference" required
;;; to draw the new color on top of the old color.  If the old and new are the same,
;;; or new is transparent, then we should not draw at all.  This is indicated by
;;; returning the value of (color-meaning-no-change).

(defun-substitution-macro metacolor-difference
    (new-metacolor old-metacolor)
  (cond ((not (paint-mode-p))
	 (color-difference (map-color-or-metacolor-to-color-value new-metacolor)
			   (map-color-or-metacolor-to-color-value old-metacolor)))
	((eq new-metacolor old-metacolor)
	 (color-meaning-no-change))
	((transparent-color-p new-metacolor)
	 (color-meaning-no-change))
	((transparent-color-p old-metacolor)
	 (color-difference (map-color-or-metacolor-to-color-value new-metacolor)
			   current-background-color-value))
	(t
	 (color-difference (map-color-or-metacolor-to-color-value new-metacolor)
			   (map-color-or-metacolor-to-color-value old-metacolor)))))






;;;; Entity Conses



;;; `Entity conses' are used to make up all of the list structure present as
;;; the entity of a frame.  The standard suite of consing related symbols
;;; are implemented with the stem "ENTITY"; see defconser for their specific
;;; names.

(defconser entity entities)





;;;; Icon Descriptions and Attributes



;;; An `icon description' is either part of the base software or is generated
;;; when a class-definition frame is put into use.  Therefore, icon descriptions
;;; need not be saved in kbs, per se.  Because icon descriptions may be global,
;;; the only slot of an icon description that may be changed after they have
;;; been created and filled in is the icon-renderings slot, and that slot must
;;; be changed with suitable locking.
;;;
;;; An `icon rendering' is derived from for an icon description by the
;;; substitution macro `get-or-make-icon-rendering', which is to be called with
;;; an icon-description structure and an icon attributes plist, in a drawing
;;; context, or at least with the two variables current-image-x/y-scale
;;; appropriately bound.  This macro manages the cache of icon renderings
;;; contained in the icon-renderings slot of an icon description.
;;; 
;;;
;;; The width (height) of the rendering for an icon is determined as follows:
;;;
;;;    We're given an icon-description structure, an icon attributes plist, and
;;;    special variables bound in a drawing context.
;;;
;;;    The basic width (basic height) is given by the width (height) indicator
;;;    in the icon attributes plist, if present; if not present, they are
;;;    given by the width-of-icon (height-of-icon) slot of the icon description.
;;;
;;;    The magnified width (height) is derived from this basic width (basic
;;;    height) by magnifying the basic width by a factor given by the
;;;    x-magnification (y-magnification) indicator in an icon attributes plist,
;;;    if present; if not present, the factor is given by the
;;;    icon-x-magnification?, if present; if not present, the factor is 1 (i.e.,
;;;    irrelevant).
;;;
;;;    The rotation of the icon is given by the reflection-and-rotation
;;;    indicator in the icon attributes plist, if present; if not present, the
;;;    rotation is considered normal; if the rotation is one that rotates the
;;;    icon by 90 degrees, then revise the above to magnify the width (heigh) by
;;;    the y-magnification (x-magnification), if present.
;;;
;;;    Finally, the rendering width (height) is derived from this magnified
;;;    width (height) by scaling it by current-image-x-scale
;;;    (current-image-x-scale), variables bound in the drawing context.
;;;
;;; Note: the official reclaimer of an icon-description structure is
;;; reclaim-icon-description.  The low-level structure reclaimer
;;; reclaim-icon-description-internal should not be used by any outside callers:
;;; it is only to be used by reclaim-icon-description internally.

(def-structure (icon-description
		 #+development
		 (:print-function print-icon-description)
		 (:reclaimer
		   reclaim-icon-description-internal)
		 (:constructor
		   make-icon-description
		   (width-of-icon
		     height-of-icon
		     x-offset-for-fine-positioning-of-icon?
		     y-offset-for-fine-positioning-of-icon?
		     icon-line-color?
		     icon-x-magnification?
		     icon-y-magnification?
		     icon-line-drawing-description
		     icon-color-pattern?
		     icon-region-extrema?)))

  width-of-icon					; these determine enclosing block's initial
  height-of-icon				;   width/height; thereafter, width, height,
						;   x-magnification, y-magnifcation, and
						;   rotation-and-reflection
						;   icon-attributes-plist elements may
						;   also determine the block's
						;   width/height

  x-offset-for-fine-positioning-of-icon?	; for reducing misalignments with
  y-offset-for-fine-positioning-of-icon?	;   connections due to scaling roundoff

  icon-line-color?				; see below for color determination
						;   priority
  icon-x-magnification?				; magnification of current-image-x-scale
  icon-y-magnification?				;   and current-image-y-scale
						; icon-attribute-plist can override these!

  (icon-line-drawing-description		; if the icon description is entity-specific,
    nil :reclaimer reclaim-line-drawing-description)   ;   this is a (like a) slot value
						; if the icon description is user-defined:
						;   this is taken, uncopied, from the icon-
						;   description-for-class? slot of the
						;   corresponding object definition
						; otherwise, this is a global constant

  ; (similar-icon-descriptions nil)		; for review when icon is changed!?

  (icon-renderings				; an entity list of icon renderings
    nil :reclaimer reclaim-icon-renderings)     ; this is in principle global across processes;
					        ;   in practice, we have only one process; if we
					        ;   had more, it would be ok except that
					        ;   entity conses would be shared between
					        ;   processes.

  icon-color-pattern?				; the cdr of the polychrome header, if any,
						;   in the icon-line-drawing-description slot
						
  (icon-region-extrema?			        ; a gensym alist with elements (region . extrema)
    nil 
    :reclaimer reclaim-icon-region-extrema?)	; (see valid-line-drawing-description-p)

  (icon-owner-class nil)                        ; The value will be a nil or a user-defined class
                                                ; set after calling create-icon-description-if
                                                ; valid.

  #+unused
  (serial-number-for-icon-description nil)      ; Needed to validate some queued drawing tasks.
  (icon-description-background-image nil :reclaimer reclaim-slot-value))






;;; The variable `g2gl-object-icon-substitutions-may-be-in-use-p' referred to
;;; whenever an icon description is deleted (by reclaim-icon-description) or
;;; updated (by update-icon-description) due to user edits to a user-defined
;;; class, particularly edits to an icon definition in a user defined class.
;;; When true, all g2gl-object classes are reviewed, and updates are made as
;;; needed.  When false (nil), these updates can be skipped (i.e., as an
;;; optimization).  See module G2-BPEL, particularly the subsection
;;; "G2GL-Object Icon Substitutions", for additional details.

(def-system-variable g2gl-object-icon-substitutions-may-be-in-use-p icons
  t)

;; For now, have this always be true -- it's probably OK to leave as is
;; until/unless icon substitution is generalized, or class g2gl-activity is
;; unsealed (as it could result in an explosion of subclasses). But it wouldn't
;; be very hard to maintain this. Review after 8.2a0. (MHD 9/8/05)




;;; The function `reclaim-icon-description' ...

(defun reclaim-icon-description (icon-description)
  (when g2gl-object-icon-substitutions-may-be-in-use-p
    (revert-if-g2gl-object-icon-substitution icon-description))
  (reclaim-icon-description-internal icon-description))
    

;; If the reclaimer defined for this structure were to be used to reclaim the default
;; value of the icon-description slot in a class description, it would have to
;; not reclaim the icon-line-drawing-description slot, because that value is shared
;; with the object definition to the icon description.  Fix this!

;; Consider copying the icon line drawing description, to simplify reclamation.


(defun reclaim-line-drawing-description (slot-value)
  (cond
    ((or (symbolp slot-value)		; handles NIL, too.
	 (fixnump slot-value))
     nil)
    ((managed-float-p slot-value)
     (reclaim-managed-float slot-value))
    ((consp slot-value)
     (reclaim-line-drawing-description (car-of-cons slot-value))
     (reclaim-line-drawing-description (cdr-of-cons slot-value))
     (reclaim-slot-value-cons-macro slot-value))
    ((text-string-p slot-value)
     (reclaim-text-string slot-value))
    ((gensym-string-p slot-value)
     ;; strings are now only used as constants, ala -- should not come up here
     ;; for reclamation!  (pbk 10/10/96)
     #+development
     (error "reclaim line drawing description recieved gensym string ~s"
	    slot-value))
    
    (t
     (error "reclaim line drawing description unexpected value ~s"
	    slot-value))))

#+development
(defun print-icon-description (icon-description stream depth)
  (declare (ignore depth))
  (printing-random-object (icon-description stream)
    (format stream "ICON-DESCRIPTION ~a"
	    (icon-owner-class icon-description))))




(defun icon-owner-class-function (icon-description)
  (icon-owner-class icon-description))

(defun set-icon-owner-class (class-name icon-description)
  (setf (icon-owner-class icon-description) class-name))

(defvar icon-renderings-being-bulk-decached nil)

(defun remove-icon-rendering-from-icon-description 
       (icon-rendering icon-description)
  (cond
    (icon-renderings-being-bulk-decached
     #+development
     (unless (memq icon-rendering icon-renderings-being-bulk-decached)
       (cerror "Ignore this" "icon-rendering being reclaimed twice")))
    (t
     (loop as icon-renderings-tail = nil then rest-of-icon-renderings
	   for rest-of-icon-renderings 
	   on (icon-renderings icon-description)
	   do
       (when (eq (car rest-of-icon-renderings) icon-rendering)
	 (as-atomic-operation
	   (if icon-renderings-tail
	       (setf (cdr icon-renderings-tail)
		     (cdr rest-of-icon-renderings))
	       (setf (icon-renderings icon-description)
		     (cdr rest-of-icon-renderings)))
	   (reclaim-entity-cons rest-of-icon-renderings))
	 (return (values)))
	   finally
	     #+development
	     (cerror "Ignore this" "icon-rendering being reclaimed twice")))))


(defun reclaim-icon-renderings (icon-renderings)
  (loop for icon-rendering in icon-renderings
	do
    (reclaim-icon-rendering-and-raster icon-rendering))
  (reclaim-entity-list icon-renderings))


#+unused
(defmacro icon-description-has-been-reprocessed-p
    (icon-description reference-serial-number)
  (let ((serial-number (gensym)))
    `(let ((,serial-number (serial-number-for-icon-description ,icon-description)))
       (or (minuspf ,serial-number)
	   (>f ,serial-number ,reference-serial-number)))))


#+unused
(defun icon-description-has-been-reprocessed-p-function (icon-description reference-serial-number)
  (icon-description-has-been-reprocessed-p icon-description reference-serial-number))

;; The following two functions are defined to allow forward referencing to the macros
;; defined by the icon-description def-structure.

(defun reclaim-icon-description-of-slot-description (icon-description)
  (reclaim-icon-description icon-description))

(defun icon-description-slot-init-form-p (slot-init-form)
  (icon-description-p slot-init-form))





;;;; Line Drawing Descriptions




;;; A `line drawing description' is a list which describes how an icon is to be drawn.
;;; Line drawing descriptions are lists of line drawing elements. Each line drawing
;;; element describes a set of contiguous points. These sets of points can be a
;;; single point, a line, a polyline, an enclosed figure, an arc, or a circle.

;;; A line drawing description takes the following general form
;;; 
;;;     ( [ <polychrome-header> ]
;;;       [ <variable header> ]
;;;       [ <background header> ]
;;;       [ <stipple header> ]
;;;       { <line-drawing-element> | <color-or-region> } )
;;;
;;; A `polychrome header' is
;;;
;;;     (POLYCHROME . icon-color-pattern)

;;; A `variable header' is of the form ....

;;; A `background header' is of the form ....

;;; A `stipple header' is of the form
;;;
;;;     (STIPPLE stipple)
;;;
;;; where stipple is a symbol that is one of the defined stipple symbols; see
;;; all-stipples in WINDOWS2.

;;; An `icon color pattern' is an alist of the form
;;;
;;;     ( { (color . color) | (region . color) } )

;;; An `icon color change pattern' is an alist of the form
;;;
;;;     ( { (region . color) } )
;;;
;;; An icon color change pattern is used to specify changes to named regions of a
;;; polychrome icon in actions.  See the action grammar (in GRAMMAR2) for more
;;; details.

;;; A `polychrome line drawing description' is a line drawing description with a
;;; polychrome header.  The predicate `polychrome-icon-p' of an entity is true if
;;; that entity has a polychrome line drawing description in its icon description.

;;; A `color' is a symbol naming a color, e.g. BLUE, GREEN, BLACK, etc., all of
;;; which are legal arguments to map-to-color-value.  In a line drawing
;;; description, a color can also be one of the symbols FOREGROUND or TRANSPARENT,
;;; which are not really colors and cannot be mapped to a color value.  A `region'
;;; (or `color region') is a symbol in a line drawing description for a polychrome
;;; icon naming one or more layers drawn in a particular color.

;;; If there is no polychrome header, the colors interspersed among the
;;; line drawing elements are FOREGROUND and TRANSPARENT only. Foreground is
;;; implied as the initial default.

;;; If there is a polychrome header, the only color or regions interspersed among
;;; the line drawing elements are TRANSPARENT, and the symbols which are the cars of
;;; each dotted pair in the polychrome header.

;;; A `line drawing element' generally has the form
;;; 
;;;     ( line-drawing-directive { point } )
;;;
;;; An exception is filled-polygon, which stores a decomposition into triangles
;;; so that this does not need to be recomputed each time a raster is generated.
;;; Its form is
;;;
;;;     (FILLED-POLYGON ( point point { point } ) { triangle } )
;;;     
;;; where triangle is
;;;
;;;     ( point point point )
;;;
;;; Developers creating icon descriptions by hand may use the function
;;; create-filled-polygon-icon-description-element at read time in order
;;; to create a filled polygon description, e.g.,
;;;
;;;     #.(create-filled-polygon-icon-description-element
;;;	   '((0 6) (5 0) (10 6) (8 6) (5 2) (2 6)))
;;;
;;; which ends up as
;;;
;;;     (FILLED-POLYGON ((0 6) (5 0) (10 6) (8 6) (5 2) (2 6))
;;;                     ((5 0) (10 6) (8 6))
;;;                     ((5 2) (0 6) (5 0))
;;;                     ((5 0) (8 6) (5 2))
;;;                     ((5 2) (2 6) (0 6)))

;;; A `point' (in an icon description) is
;;;
;;;     ( x y )
;;; 
;;; where x and y are "icon coordinates" (a kind of fixnum integers) or forms
;;; that evaluate using simple-eval-for-icon to icon coordinates.  If x and y
;;; are both icon coordinates, then point is a `constant point'.  If point needs
;;; evaluation (again, via simple-eval-for-icon), then it is called an `computed point'.
;;;
;;; During the evaluation of a point, there are several variables that may
;;; be referred to, having to do with the geometry of the icon:
;;;
;;;     width
;;;     height
;;;     any variable in variable-spec-list
;;;
;;; All of the above variables are in the "icon coordinate system".  These are
;;; bound in a dynamic extent created in the macro evaluating-icon-points, q.v.
;;;
;;; If an icon description contains computed points, then the caching mechanism
;;; _may_ become more complex.  Other than that, you don't need to be
;;; particularly concerned about using them.

;;; An `icon coordinate system' has its (0, 0) origin at the top, left corner of the
;;; icon.  Therefore, legal coordinates are always positive at present.  Note however
;;; it is planned to have as a future capability to allow drawing to be partially
;;; outside the bounding box of the icon, which would means that negative numbers
;;; could then be legal coordinates.  An `icon coordinate' is a special case of a
;;; workspace coordinate, which is a fixnum less than or equal to the integer square
;;; root of the most positive gensym fixnum and greater than the opposite of that
;;; number; i.e. between -(2^24 - 1) and 2^24 - 1.

;;; Arithmetic on icon coordinates is done with workspace coordinate arirthmetic
;;; (e.g. +w, -w, etc.; see PRIMITIVES).  See also `user workspace coordinate',
;;; below.



;;; The predicate `point-p' is true of any Lisp object which is a point.  
;;; The predicate `arc-point-p' is true of any Lisp object which is a point.
;;; These predicates exaustively test their argument and thus may be
;;; unnecessarily inefficient to use when working with an icon description
;;; which is known to be valid; in fact, they are only used by the code below
;;; which tests for validity of icon descriptions.

;;; For convenience, the accessor `point-x' of a point gives the x icon
;;; coordinate of a point, and the accessor `point-y' of a point gives the y
;;; icon coordinate of a point.   Note that point-x and point-y are defined in
;;; order to allow clarity in accessing points, not to totally abstract away
;;; the data representation of a point; if that were done, it would make it
;;; inconvenient, for example, to iterate over points using loop-desctructuring
;;; as in
;;;
;;;     (loop for ((x1 y1) (x2 y2) (x3 y3)) in triangles ...)

;;; A `line drawing directive' is one of several symbols, as described in the
;;; following table.

;; Consider using dotted pairs for points! But note that these lists already
;; exist in kbs. ML, 3.23.89.


;;;    
;;;    Line Drawing Directive  Peculiarities                    Function
;;;    ----------------------  -------------                    --------
;;;    point                   Takes one and only one point.    Plots single point.
;;;
;;;    
;;;    lines                   Takes any number of points       Draws polyline from the
;;;                            greater than two.                first point, through the
;;;                                                             second point and so on
;;;                                                             to the Nth point.
;;;                                                             (Lines described are not
;;;                                                             limited to staight lines.
;;;                                                             Arcs can be specified by
;;;                                                             utilizing arc points
;;;                                                             (see below)).
;;;    
;;;    outline                 Takes three or more points.      Like lines
;;;                                                             except that it draws a line
;;;                                                             from the last to the first
;;;                                                             point.
;;;    
;;;    solid-rectangle         Takes two points.                A filled region specified by
;;;                                                             diagonally opposite corners.
;;;                                                             Note that the user's grammar now
;;;                                                             calls this "filled rectangle."
;;;
;;;    rounded-rectangle,
;;;      filled-rounded-rectangle
;;;		                Takes two points.               A single unit width rectangle
;;;		                                                with rounded corners drawn with
;;;		                                                arcs of radius 13 (and
;;;		                                                filled in the filled-rounded-
;;;		                                                rectangle case) specified by
;;;		                                                diagonally opposite corners.
;;;		                                                
;;;                                                             Note that there is no user's
;;;                                                             grammar for these at this
;;;                                                             time.
;;;                                                           
;;;                            Note that in Version 2.0, the
;;;                            user's language is now "filled
;;;                            rectangle".
;;;    
;;;    circle                  Takes three points.              Any three points define
;;;                                                             exactly one circle. The
;;;                                                             circle directive draws that
;;;                                                             circle.
;;;


;;; The following were first made available in version 2.0 of G2.

;;;    filled-circle           Takes three points.              Any three points define
;;;                                                             exactly one circle. The
;;;                                                             circle directive draws and
;;;                                                             fills that circle.
;;;                                                             
;;;    filled-polygon	       Takes n (>= 3) points.		The polygon must have all its
;;;                                                             points distinct, and must be simple.
;;;                                                             (Its perimeter does not intersect
;;;                                                             itself.) Its representation includes
;;;                                                             a decomposition into triangles, which
;;;                                                             can be automated. (See above.)
;;;    

;;; Some Examples of Line Drawing Descriptions

;;; ...

;; Provide some examples!



;;; `Get-polychrome-header-if-any' returns the polychrome header, if any, of a
;;; line drawing description.
;;;
;;; `get-polychrome-header-from-icon-description-if-any' does the same except
;;; that it applies to the icon description containing the line drawing
;;; description.
;;;
;;; `Get-polychrome-header-from-entity-if-any' does the same except that it
;;; applies to the entity containing the icon description containing the line
;;; drawing description.

(def-substitution-macro get-polychrome-header-if-any (line-drawing-description)
  (let ((first-element (car line-drawing-description)))
    (if (and (consp first-element) (eq (car first-element) 'polychrome))
	first-element)))

(defun get-polychrome-header-from-icon-description-if-any (icon-description)
  (get-polychrome-header-if-any
    (icon-line-drawing-description icon-description)))
  
;;; `Single-color-line-drawing-description-p' is is true if
;;; line-drawing-description is either formally monochrome, which is obsolete in
;;; G2 4.0, or only trivially polychrome in that it only contains one color
;;; (apart from its implicit background color).
;;; 
;;; `Single-color-icon-description-p' does the same for an icon description.
;;; 
;;; `Single-color-entity-p' does the same for an entity.

(defun single-color-line-drawing-description-p (line-drawing-description)
  (null (cdr (cdr (get-polychrome-header-if-any line-drawing-description)))))

(defun single-color-icon-description-p (icon-description)
  (null (cdr (cdr (get-polychrome-header-from-icon-description-if-any
		    icon-description)))))  




;;;; Icon Evaluation



(defvar current-icon-untransformed-width)
(defvar current-icon-untransformed-height)
(defvar current-icon-variables-plist)
(defvar current-icon-variables-override-plist)

(defmacro evaluating-icon-elements
    ((untransformed-width
       untransformed-height
       variables-plist
       variables-override-plist)
     &body body)
  `(let* ((current-icon-untransformed-width ,untransformed-width)
	  (current-icon-untransformed-height ,untransformed-height)
	  (current-icon-variables-plist ,variables-plist)
	  (current-icon-variables-override-plist ,variables-override-plist))
     . ,body))

;; formerly evaluating-icon-points

(defun lookup-symbol-as-icon-variable (symbol-to-find)
  (or (getfq current-icon-variables-override-plist symbol-to-find)
      (getfq current-icon-variables-plist symbol-to-find)))
      
;; We can not return a hard error here because image names can be symbols
;; representing global image definitions. Maybe this function should take
;; a behavior controlling arg that dictates what will happen if the symbol
;; is not found.


(defun simple-eval-for-icon (form)
  (typecase form
    (symbol
     (or (lookup-symbol-as-icon-variable form)
	 (case form
	   (width current-icon-untransformed-width)
	   (height current-icon-untransformed-height))
	 form))
    (atom form)
    (list (simple-apply-for-icon (first form) (rest form)))))

(defun simple-apply-for-icon (function args)
  (case function
    ((+ - * /)
     (let* ((arg-1 (simple-eval-for-icon (first args))))
       (if (null (cdr args))
	   (case function
	     (+ (+f arg-1))
	     (- (-f arg-1)))			; unary plus and minus
	   (let ((arg-2 (simple-eval-for-icon (second args))))
	     (case function
	       (+ (+f arg-1 arg-2))	; These computations can overflow fixnums.
	       (- (-f arg-1 arg-2))
	       (* (*f arg-1 arg-2))
	       (/ (if (=f arg-2 0)
		      ;; illegal to divide by 0
		      0				; return garbage
		      (roundf arg-1 arg-2))))))))))

;; General Principles:
;;
;; Extremely simple (i.e., nonexistant) error handling: Garbage in => Garbage out
;;
;; Only datatype is fixnum.  Only functions supported: + , *, /, and - of two
;; args; - of one arg.  Dividing by 0 officially has undefined results, but
;; unofficially results in 0.  / is implemented as "round" (i.e., froundf).
;; Calling any other function is an error, and the results are undefined.
;;
;; Only two variables that may be evaluated at present: WIDTH and HEIGHT.




(def-substitution-macro point-p (thing)
  (and (consp thing)
       (consp (cdr thing))
       (null (cddr thing))))

(def-substitution-macro constant-point-p (thing)
  (and (consp thing)
       (consp (cdr-of-cons thing))
       (null (cddr-of-cons thing))
       (typep (car-of-cons thing) 'fixnum)
       (typep (cadr-of-cons thing) 'fixnum)))


(def-substitution-macro power-point-p (thing)
  (let (cdr-thing car-thing cadr-thing)
    (and (consp thing)
	 (setq cdr-thing (cdr-of-cons thing))
	 (consp cdr-thing)
	 (null (cdr-of-cons cdr-thing))
	 (setq car-thing (car-of-cons thing))
	 (setq cadr-thing (car-of-cons cdr-thing))
	 (or (not (typep car-thing 'fixnum))
	     (not (typep cadr-thing 'fixnum)))
	 (or (and (consp car-thing) (eq (car-of-cons car-thing) '+))
	     (and (consp cadr-thing) (eq (car-of-cons cadr-thing) '+))
	     (symbolp car-thing)
	     (symbolp cadr-thing)))))

(def-substitution-macro button-point-p (thing)
  (let (cdr-thing car-thing cadr-thing)
    (and (consp thing)
	 (setq cdr-thing (cdr-of-cons thing))
	 (consp cdr-thing)
	 (null (cdr-of-cons cdr-thing))
	 (setq car-thing (car-of-cons thing))
	 (setq cadr-thing (car-of-cons cdr-thing))
	 (or (not (typep car-thing 'fixnum))
	     (not (typep cadr-thing 'fixnum)))
	 (or (and (consp car-thing) (eq (car-of-cons car-thing) '+))
	     (and (consp cadr-thing) (eq (car-of-cons cadr-thing) '+))
	     (and (consp car-thing) (eq (car-of-cons car-thing) '-))
	     (and (consp cadr-thing) (eq (car-of-cons cadr-thing) '-))
	     (symbolp car-thing)
	     (symbolp cadr-thing)))))


(def-substitution-macro computed-point-p (thing)
  (and (consp thing)
       (consp (cdr thing))
       (null (cddr thing))
       (or (not (typep (car thing) 'fixnum))
	   (not (typep (cadr thing) 'fixnum)))))

;; Do more exhaustive checking if checking validity!  (e.g., for
;; legal things to evaluate for a computed point).

;; Check if less than "most positive coordinate" -- (2^24 - 1) !!


(def-substitution-macro arc-point-p (thing)
  (and (consp thing)
       (eq (car-of-cons thing) 'arc)
       (consp (cdr-of-cons thing))
       (null (cdr-of-cons (cdr-of-cons thing)))
       (point-p (second-of-cons thing))))


(def-substitution-macro point-x (point)
  (if (typep (first point) 'fixnum)
      (first point)
      (simple-eval-for-icon (first point))))

(def-substitution-macro point-y (point)
  (if (typep  (second point) 'fixnum)
      (second point)
      (simple-eval-for-icon (second point))))

(def-substitution-macro point-within-range-p (point width height)
  (and (<=w 0 (point-x point) width)
       (<=w 0 (point-y point) height)))




(defun-substitution-macro image-drawing-element-p (drawing-element)
  (and (consp drawing-element)
       (eq (first drawing-element) 'image)))


(defun-substitution-macro text-drawing-element-p (drawing-element)
  (and (consp drawing-element)
       (eq (first drawing-element) 'text)))

(defun-substitution-macro stipple-drawing-element-p (drawing-element)
  (and (consp drawing-element)
       (eq (first drawing-element) 'stippled-area)))

(defun-substitution-macro image-drawing-element-image-name (image-drawing-element)
  (second image-drawing-element))




;;; Get functions for line-drawing-descriptions and plists: (PBK)

;;; `get-variable-specification-if-any'
;;; Returns the variable specification list from the line-drawing-description,
;;; if one exists else nil
;;; Does NOT return a copy nor does it reclaim its argument.
;;;
;;; `Get-icon-background-layer-if-any' is similar but gets the background layer
;;; header element.
;;;
;;; These search the icon description list by cdr'ing down the list, and
;;; stopping after the first atom, indicating a color region, marking the end of
;;; header elements and the start of a drawing elements.

;; pbk ... also used in grammar6

(defun-simple get-variable-specification-if-any (remaining-parse-result)
  (loop	for spec-list in remaining-parse-result
	do (cond
	     ((consp spec-list)
	      (if (eq (car-of-cons spec-list) 'variables)
		  (return spec-list)))
	     ((symbolp spec-list)	       
	      (return nil)))))		; stop at first symbol, a color region

(defun-simple get-icon-background-layer-if-any (remaining-parse-result)
  (loop	for spec-list in remaining-parse-result
	do (cond
	     ((consp spec-list)
	      (if (eq (car-of-cons spec-list) 'background-layer)
		  (return spec-list)))
	     ((symbolp spec-list)
	      (return nil)))))		; stop at first symbol, a color region


;;; `Get-icon-stipple-if-any' returns the stipple for the entire icon, if any,
;;; i.e., either a non-nil stipple symbol, e.g., LIGHT-STIPPLE, or nil.  This
;;; stipple header element may appear among the other header elements. This
;;; searches the icon description list by cdr'ing down the list, and stopping
;;; after the first symbol, indicating a color region, marking the end of header
;;; elements and the start of a drawing elements.

(defun-simple get-icon-stipple-if-any (remaining-parse-result)
  (loop	for x in remaining-parse-result
	do (cond
	     ((consp x)
	      (if (eq (car x) 'stipple)
		  (return (second x))))
	     ((symbolp x)
	      (return nil)))))		; stop at first symbol, a color region

;; Defined for new stipple feature.  Also, made the above two have the
;; optimizations of being defun-simple's, and of returning early after the first
;; atom is encountered. (MHD 3/13/01)



;;; `get-element-list'
;;; Returns the line-drawing-elements part of a line-drawing-description
;;; Does NOT return a copy, nor does it reclaim its arguments

(defun-substitution-macro get-element-list
    (remaining-parse-result regions-p variables-p background-p stipple-p)
  (let ((header-count 0))
    (when regions-p (incff header-count))
    (when variables-p (incff header-count))
    (when background-p (incff header-count))
    (when stipple-p (incff header-count))
    (nthcdr header-count remaining-parse-result)))


;; `get-computed-values-plist'
;; Return the computed-variables-plist that is stored with the
;; icon-attributes-plist of some class instance.
;; Does NOT return a copy, nor does it reclaim its argument.

(defun-simple get-computed-values-plist (icon-attributes-plist)
  (and icon-attributes-plist  
       (getfq icon-attributes-plist 'variables)))




;;; Substitution functions for Power Icons: (PBK)

(declare-forward-reference copy-for-slot-value function) ; FRAMES4


(defvar current-icon-substitution-list nil)

(defun help-substitute-values-for-variables (x)
  (cond
    ((atom x)
     (cond ((symbolp x)
	    (let ((subst? (assq x current-icon-substitution-list)))
	      (if subst? (cadr subst?) x)))
	   ((stringp x)  ; need to copy strings
	    (copy-text-string x))
			;	   ((managed-floats ???
	   (t
	    x)))
    (t
     (slot-value-cons
       (help-substitute-values-for-variables (car x))
       (help-substitute-values-for-variables (cdr x))))))


;; `substitute-values-for-variables-in-line-drawing-description'
;; Returns a NEW line-drawing-description that needs to be reclaimed.

(defun substitute-values-for-variables-in-line-drawing-description
    (line-drawing-description substitution-list)
  (let ((current-icon-substitution-list substitution-list))
    (help-substitute-values-for-variables
      line-drawing-description)))



;;; `variable-spec-eq'
;;; Returns t if the variable specs are the same variable name
;;; but not necessarily the same value

(defun variable-spec-eq (spec-1 spec-2)
   (eq (car spec-1) (car spec-2)))



;;; `variable-spec-equal'
;;; Returns t if the variable specs have both the same variable
;;; name AND the same value for that variable

(defun-substitution-macro variable-spec-equal (spec-1 spec-2)
  (when (and (consp spec-1) (consp spec-2))
    (let ((name-1 (car-of-cons spec-1))
	  (name-2 (car-of-cons spec-2))
	  (value-1 (car-of-cons (cdr-of-cons spec-1)))
	  (value-2 (car-of-cons (cdr-of-cons spec-2))))
      (and (eq name-1 name-2)
	   (if (and (text-string-p-macro value-1)
		    (text-string-p-macro value-2))
	       (string=w value-1 value-2)
	       (eq value-1 value-2))))))
  

;;; `substitute-sorted-computed-values-in-variable-spec-list'
;;; Returns a NEW sorted variable-spec-list with preference given to
;;; computed-values over those in the default variable-spec-list
;;; Return value needs to be reclaimed by the caller caller of this function.
;;; Does NOT reclaim or destroy its arguments.

(defun substitute-sorted-computed-values-in-variable-spec-list
    (sorted-values default-sorted-values)
  
  (loop with match-p = nil
	with result = nil
	as remaining-default-sorted-values = default-sorted-values then
	(cdr remaining-default-sorted-values)
	as remaining-sorted-values = sorted-values then
	(if match-p (cdr remaining-sorted-values)
	    remaining-sorted-values)
	do
    (cond
      ((null remaining-sorted-values)
       (return
	 (loop for default-value in remaining-default-sorted-values
	       do
	   (slot-value-push (copy-for-slot-value default-value) result)
	       finally
		 (return (setf result (nreverse result))))))
      ((null remaining-default-sorted-values)
        (error "default-values-plist was incomplete for the given computed values!
         Missing variable for ~s~%"
	    (car remaining-sorted-values)))
      ((variable-spec-eq (car remaining-sorted-values)
			 (car remaining-default-sorted-values))
       (slot-value-push (copy-for-slot-value (car remaining-sorted-values))
			result)
       (setf match-p t))
      (t (slot-value-push (copy-for-slot-value (car remaining-default-sorted-values))
			  result)
	 (setf match-p nil)))))




;;; `sorted-plist-match-p' is used to compare two plists of variable-specs where
;;;  a variable-spec is a list of a variable-name and a corresponding value.
;;;  This is used to compare a class instance's current computed-values-plist
;;;  with an icon-rendering's computed-values-plist. A class instances
;;;  computed-values-plist is stored within the icon-attributes-plist of that
;;;  instance using the key 'variables. 

#+old
(defun-simple sorted-plist-match-p (plist-1 plist-2)
  (loop for variable-spec-1-tail on plist-1
	for variable-spec-2-tail on plist-2
	as variable-spec-1 = (car-of-cons variable-spec-1-tail)
	as variable-spec-2 = (car-of-cons variable-spec-2-tail)
	when (not (variable-spec-equal variable-spec-1 variable-spec-2))
	  return nil
	finally
	  (setf variable-spec-2-tail (cdr variable-spec-2-tail))
	  (return (not (or variable-spec-1-tail
			   variable-spec-2-tail)))))

(defun-substitution-macro variable-value-equal (value-1 value-2)
  (if (and (text-string-p-macro value-1)
	   (text-string-p-macro value-2))
      (string=w value-1 value-2)
      (eq value-1 value-2)))

(defun-simple sorted-plist-match-p (plist-1 plist-2)
  (loop for variable-spec-1-tail on plist-1
	for variable-spec-2-tail on plist-2
	as variable-spec-1 = (car-of-cons variable-spec-1-tail)
	as variable-spec-2 = (car-of-cons variable-spec-2-tail)
	when (not (variable-value-equal variable-spec-1 variable-spec-2))
	  return nil
	finally
	  (setf variable-spec-2-tail (cdr variable-spec-2-tail))
	  (return (not (or variable-spec-1-tail
			   variable-spec-2-tail)))))
  

;;; `with-multiple-properties'
;;; A version of getfq-macro for multiple properties.
;;; Use where speed is essential

(defmacro with-multiple-properties (keys plist &body body)
  (loop with cond-statement = nil
	with variables = nil
	for key in keys
	as variable = (build-ab-symbol key 'property)
	as conder =  `((eq key ',key)
		       (setf ,variable value))
	do
    (push conder cond-statement)
    (push variable variables)
	finally
	  (push 'cond cond-statement)
	  (return
	    `(let ,variables
	       (loop with icon-attributes-plist-tail = ,plist
		     while icon-attributes-plist-tail
		     as key = (car-of-cons icon-attributes-plist-tail)
		     as tail = (cdr-of-cons icon-attributes-plist-tail)
		     as value = (car-of-cons tail)
		     do
		 ,cond-statement
		     (setf icon-attributes-plist-tail (cdr-of-cons tail)))
	       . ,body))))



;;;; Icon Drawing




;;; ` bitmap-size-parameters-for-icon-rendering ' mirrors
;;; the computation done on TW of how large the icon
;;; bitmaps will be and how many of them will be
;;; created. An icon-rendering can have several regions of
;;; different sizes (and colors). Each region can be made
;;; up of many tiled bitmaps.
;;;
;;; Returns a nested list (must be reclaimed by the
;;; caller): Each element of the list is a list:
;;; (tile-edge-size-in-pixels rows columns).
;;; tile-edge-size-in-pixels is the number of pixels on one
;;; side (note that tiles are square).  Rows * columns
;;; gives the number of bitmaps created of this tile size.
;;; This function returns these raw data values so they can
;;; be compared with the structures TW creates, for
;;; debugging.
;;;
;;; The length of the list (the number of icon-regions) is
;;; (number-of-rendering-structure-elements icon-rendering)

;; Sadly, this also duplicates the computation in G2 in
;; make-rendering-structure because values are computed on
;; the fly, send to TW, and then discarded.  Note: need to
;; get rid of this duplicate code, probably by storing the
;; result of get-x-y-max-and-offset in the rendering and
;; iterating over that in make-rendering-structure

(defun bitmap-size-parameters-for-icon-rendering
    (x-scale y-scale
     width height
     reflection-and-rotation
     region-extrema
     line-drawing-description)
  (let* ((polychrome-header?
	   (get-polychrome-header-if-any line-drawing-description))
	 (polychrome-header-rest? (cdr polychrome-header?))
	 (color-region-and-symbol-pairs
	   (or polychrome-header-rest?
	       '((foreground . foreground)))))
    (loop for (color-region) in color-region-and-symbol-pairs
	  as region-extrema-entry? = (car region-extrema)
	  collect
	  (multiple-value-bind
	      (x-offset-for-stored-raster? y-offset-for-stored-raster?
	       x-max-for-stored-raster? y-max-for-stored-raster?)
	      (get-x-y-max-and-offset region-extrema-entry?
		x-scale y-scale
		width height reflection-and-rotation)
	    (multiple-value-bind
		(actual-width actual-height)
		(raster-dimensions-given-max-and-offset
		  width height
		  x-max-for-stored-raster? x-offset-for-stored-raster?
		  y-max-for-stored-raster? y-offset-for-stored-raster?)
	      (let ((tile-edge-size-in-pixels ; note tiles are square
		      (compute-tile-size-given-required-area actual-width actual-height)))
		(multiple-value-bind (rows columns)
		    (compute-rows-columns-given-tile-size
		      tile-edge-size-in-pixels actual-width actual-height)
		  (entity-list tile-edge-size-in-pixels rows columns)))))
	  into bitmap-sizes using entity-cons
	  do (setq region-extrema (cdr region-extrema))
	  finally (return bitmap-sizes)))) ;; See note 2

;; Note 2: If returned value (bitmap-sizes) is nil, nothing
;; was done.

;; Don't really need to cons up a list of bitmap sizes, but doing so for debugging.




;;; `count-bitmaps-needed-for-this-icon-rendering' creates
;;; a vector with the number of bitmaps of each size that
;;; will be created for this icon-rendering. To index into
;;; this vector with a regular raster size, index with
;;; (position raster-size list-of-regular-raster-sizes). To
;;; use actual memory usage as an index, do: (position
;;; raster-memory-usage
;;; list-of-regular-raster-memory-usage).

(defun count-bitmaps-needed-for-this-icon-rendering
    (x-scale y-scale
     width-of-icon height-of-icon
     reflection-and-rotation
     icon-region-extrema
     line-drawing-description)
  (let ((vector-of-bitmaps (allocate-managed-simple-vector #.number-of-regular-raster-sizes))
	(bitmap-size-parameters (bitmap-size-parameters-for-icon-rendering
				  x-scale
				  y-scale
				  width-of-icon height-of-icon
				  reflection-and-rotation
				  icon-region-extrema
				  line-drawing-description)))

    (fill-managed-simple-vector vector-of-bitmaps 0 0 #.number-of-regular-raster-sizes)

    (loop for (tile-edge-size-in-pixels rows columns) in bitmap-size-parameters
	  as count fixnum upfrom 0

	  as index fixnum
		   = (loop for x fixnum in '#.list-of-regular-raster-sizes
			   as i from 0
			   when (=f tile-edge-size-in-pixels x)
			     return i
			   finally (return 0)) ; make SBCL compiler happy

	  as old-value fixnum = (svref vector-of-bitmaps index)
	  do (setf (svref vector-of-bitmaps index)
		   (+f old-value (*f rows columns))))
    (loop for elem in bitmap-size-parameters
	  do (reclaim-entity-list elem))
    (reclaim-entity-list bitmap-size-parameters)
    vector-of-bitmaps))




(defun bitmap-memory-usage-for-icon-rendering (array-of-bitmap-counts)
  (loop for index upfrom #.minimum-index-for-icons
	upto #.largest-regular-raster-size-index
	with memory-used = 0
	with total-bitmaps = 0
	as bitmaps-of-this-size = (svref array-of-bitmap-counts index)
	when (<f 0 bitmaps-of-this-size)
	  do
	    (incff total-bitmaps bitmaps-of-this-size)
	    (incff memory-used
		   (*f bitmaps-of-this-size
		       (nth index '#.list-of-regular-raster-memory-usage)))
	finally
	  (return (values total-bitmaps memory-used)))
  )




;;; `decache-this-icon-rendering-p' compares two arrays of
;;; bitmaps by size. If the candidate array has even one
;;; bitmap of a desired size, its a match. Updates the
;;; desired-sizes-array as it goes (on the assumption this
;;; rendering will be decached). We don't need to decache
;;; any more if the desired-sizes-array is now zero (so we
;;; can see if further to go). Nil returned means don't
;;; decache this but keep on trying. Array returned means
;;; decache this rendering. If array all zero, done.
;;;
;;; Return values:
;;; nil		don't decache			(no matches)
;;; t		decache: this is last one	matches: all zero
;;; array	decache: need to do more	matches: more left to do

(defun decache-this-icon-rendering-p (desired-sizes-array candidate-array)
  (loop for index upfrom #.minimum-index-for-icons
	upto #.largest-regular-raster-size-index
	as desired-number fixnum = (svref desired-sizes-array index)
	as actual-number fixnum = (svref candidate-array index)
	with match = nil
	with all-done = t
	do
    (when (<f 0 desired-number)
      (when (<f actual-number desired-number)
	(setq all-done nil))
      (when (<f 0 actual-number)
	(setq match t)
	(setf (svref desired-sizes-array index)
	      (if (<f actual-number desired-number)
		  (-f desired-number actual-number)
		  0))))
	finally (return (when match
			  (if all-done
			      t
			      desired-sizes-array)))))




;;; `decache-exact-size-icon-bitmaps' decaches the least
;;; recently used icon renderings that have at least one
;;; bitmap in the desired sizes. Returns non-nil if enough
;;; have been decached.

(defun decache-exact-size-icon-bitmaps
    (window-for-icon-rendering array-of-bitmap-counts)
  (let ((decached-all-desired-sizes-p nil)
	(desired-bitmap-sizes
	  (allocate-managed-simple-vector #.number-of-regular-raster-sizes)))
    ;; make a copy because we are going to decrement as we go
    (copy-simple-vector-portion
      array-of-bitmap-counts 0 #.number-of-regular-raster-sizes
      desired-bitmap-sizes 0)
    
    (block decache-exact-size
      (do-lru-queue (icon-rendering icon-rendering-lru-queue)
	(let* ((candidate-bitmap-sizes (array-of-bitmaps-used icon-rendering))
	       (candidate-window (window-for-icon-rendering icon-rendering))
	       (decache? (and (eq window-for-icon-rendering	
				  candidate-window)
			      (decache-this-icon-rendering-p
				desired-bitmap-sizes candidate-bitmap-sizes))))
	  (when decache?
	    (decache-icon-rendering icon-rendering)
	    (when (setq decached-all-desired-sizes-p (eq t decache?)) ; See note 3
	      (return-from decache-exact-size))))))
    (reclaim-managed-simple-vector desired-bitmap-sizes)
    decached-all-desired-sizes-p))


;; note 3: decache-this-icon-rendering-p can return t, nil,
;; or an array if there is more to do.


(defun update-bitmap-count-and-decache-if-appropriate
    (window-for-icon-rendering
      array-of-bitmap-counts
      number-of-bitmaps-for-rendering
      bitmap-memory-used-for-rendering)

  ;; Compute new totals
  (incff (icon-bitmap-count-for-window window-for-icon-rendering)
	 number-of-bitmaps-for-rendering)
  (incff (icon-bitmap-memory-for-window window-for-icon-rendering)
	 bitmap-memory-used-for-rendering)

  (when (time-to-decache-p window-for-icon-rendering)
    (unless (decache-exact-size-icon-bitmaps
	      window-for-icon-rendering
	      array-of-bitmap-counts)
      ;; We decached all there were of the exact sizes
      ;; but that might not be enough!
      (when (time-to-decache-p window-for-icon-rendering)
	(block decache-until-under-limit
	  (do-lru-queue (icon-rendering icon-rendering-lru-queue)
	    (when (eq window-for-icon-rendering
		      (window-for-icon-rendering icon-rendering))
	      (decache-icon-rendering icon-rendering)
	      (unless (time-to-decache-p window-for-icon-rendering))
	      (return-from decache-until-under-limit))))))))


;; It would be nice if we knew what was in the bitmap pool
;; on TW, because there may be plenty of bitmaps in the
;; pool, but on the G2 side, we do not know what is in the
;; pool, so we have to go by what is in use (in
;; icon-rendering-lru-queue).


;;; `Get-or-make-icon-rendering' ... assumes values for these variables in the
;;; for-image-plane dynamic extent:
;;; 
;;;   current-image-x-scale
;;;   current-image-y-scale
;;;
;;; These must be bound around the call as appropriate if this not being called
;;; while making an icon rendering for the current image plane in such a dynamic
;;; extent.
    
(defun-simple get-or-make-icon-rendering (icon-description
					   icon-attributes-plist)
  ;; Obtain, by lookup or generation, an icon rendering.
  (with-multiple-properties (variables
			      width
			      height
			      x-magnification
			      y-magnification
			      reflection-and-rotation)
    icon-attributes-plist
    (let* ((computed-values-plist
	     variables-property)
	   (width-of-icon
	     (or width-property
		 (width-of-icon icon-description)))
	   (height-of-icon
	     (or height-property
		 (height-of-icon icon-description)))
	   (x-magnification?
	     (or x-magnification-property
		 (icon-x-magnification? icon-description)))
	   (y-magnification?
	     (or y-magnification-property
		 (icon-y-magnification? icon-description)))
	   (reflection-and-rotation reflection-and-rotation-property)
	   (rotation-by-90?
	     (and reflection-and-rotation
		  (rotated-by-90-p-macro reflection-and-rotation)))
	   (rotated-x-magnification?
	     (if rotation-by-90? y-magnification? x-magnification?))
	   (rotated-y-magnification?
	     (if rotation-by-90? x-magnification? y-magnification?))
	   (x-scale 
	     (if rotated-x-magnification?
		 (magnify current-image-x-scale rotated-x-magnification?)
		 current-image-x-scale))
	   (y-scale 
	     (if rotated-y-magnification?
		 (magnify current-image-y-scale rotated-y-magnification?)
		 current-image-y-scale))
	   (window-for-icon-rendering current-window))
      (declare (type fixnum width-of-icon height-of-icon x-scale y-scale))
      (or
	(multiple-value-bind (maximum-renderings-for-class
			       number-of-renderings-to-delete)
	    (icon-decaching-parameters (icon-owner-class icon-description))
	  
	  ;; Given an icon description, an x and y scale, a reflection and rotation,
	  ;; a computed-values-plist and a width and height, return the icon
	  ;; rendering from the icon-renderings slot of the icon description if
	  ;; there is one; otherwise, fall through the next OR clause below.
	  (loop with deletable-tail? = nil	 
		for ll = nil then l
		as count from 0 by 1
		as l on (icon-renderings icon-description)
		as icon-rendering = (car l)
		do
	    (when (and (=f x-scale (x-scale-of-rendering icon-rendering))
		       (=f y-scale (y-scale-of-rendering icon-rendering))
		       (eq reflection-and-rotation
			   (reflection-and-rotation-of-rendering icon-rendering))
		       (eq (window-for-icon-rendering icon-rendering)
			   window-for-icon-rendering)
		       
		       ;; x, y-offset-for-fine-positioning-of-icon? not
		       ;;   tested now because they are never used
		       
		       (=f width-of-icon
			   (width-of-rendered-icon icon-rendering))
		       (=f height-of-icon
			   (height-of-rendered-icon icon-rendering))
		       (sorted-plist-match-p
			 computed-values-plist 
			 (computed-values-plist icon-rendering)))
	      ;; Icon renderings move to the beginning of the cache list when
	      ;; they are used, and older ones move towards the end, in order
	      ;; to make accessing the more recently used ones faster.  The
	      ;; as-atomic-operation is needed because the cache is global,
	      ;; not process-specific.
	      (when ll
		(as-atomic-operation
		  (setf (cdr ll) (cdr l))
		  (setf (cdr l) (icon-renderings icon-description))
		  (setf (icon-renderings icon-description) l)))
	      (return icon-rendering))
	    (when (>=f count number-of-renderings-to-delete)
	      (cond (deletable-tail?
		     (setf deletable-tail? (cdr-of-cons deletable-tail?)))
		    (t
		     (setf deletable-tail?
			   (icon-renderings icon-description)))))
		finally
		  (when (>=f count maximum-renderings-for-class)
		    (let ((icon-renderings-being-bulk-decached
			    (cdr deletable-tail?)))
		      #+pbk-development
		      (format t "actually deleting icon-renderings ~S~%"
			      icon-renderings-being-bulk-decached)
		      (setf (cdr deletable-tail?) nil)
		      (loop for rendering in icon-renderings-being-bulk-decached
			    do
			(decache-icon-rendering rendering))
		      (reclaim-entity-list icon-renderings-being-bulk-decached)))))
      ;; No icon rendering was present: should we decache?
      (let ((array-of-bitmap-counts
	      (count-bitmaps-needed-for-this-icon-rendering
		x-scale
		y-scale
		width-of-icon height-of-icon
		reflection-and-rotation
		(icon-region-extrema? icon-description)
		(icon-line-drawing-description icon-description))))
	(multiple-value-bind
	    (number-of-bitmaps-for-rendering bitmap-memory-used-for-rendering)
	    (bitmap-memory-usage-for-icon-rendering array-of-bitmap-counts)
	  (update-bitmap-count-and-decache-if-appropriate
	    window-for-icon-rendering
	    array-of-bitmap-counts
	    number-of-bitmaps-for-rendering
	    bitmap-memory-used-for-rendering)

	  #+development 
	  (when (or (<f number-of-bitmaps-for-rendering 1)
		    (<f bitmap-memory-used-for-rendering 1))
	    (cerror "Continue"
		    "Unable to count bitmaps for this rendering"))
	  ;; Create an icon rendering and store it at the front
	  ;; of the list of icon renderings (in the icon-renderings slot) of the
	  ;; icon description.
	  (let ((icon-rendering
		  (create-icon-rendering
		    icon-description
		    (copy-tree-including-leaves-using-gensym-conses computed-values-plist)
		    ;; need to pass the computed-values-plist along so ;pbk
		    ;; that make-rendering-structure can obtain the plist
		    ;; from the icon-rendering
		  
		    window-for-icon-rendering x-scale y-scale
		    width-of-icon height-of-icon
		    reflection-and-rotation rotation-by-90?
		    array-of-bitmap-counts
		    number-of-bitmaps-for-rendering
		    bitmap-memory-used-for-rendering
		    )))
	    (as-atomic-operation
	      (setf (icon-renderings icon-description)
		    (entity-cons
		      icon-rendering
		      (icon-renderings icon-description))))
	    icon-rendering)))))))

;; Used only in draw-icon below this module.  Consider incorporating this code
;; directly.  Also consider making parts or all of it a function (-- DONE).

;; Note that because icon renderings are window specific, they are, in effect,
;; process specific as well.


(defun-simple create-icon-rendering
    (icon-description
      computed-values-plist 
      window-for-icon-rendering x-scale y-scale
      width-of-icon height-of-icon
      reflection-and-rotation rotation-by-90?
      array-of-bitmap-counts
      number-of-bitmaps
      memory-used-by-bitmaps)
  (let* ((overflow-units
	   (maxr (icon-overflow) (bleeding-overflow)))
	 (width-of-rendering-structure
	   (+r (delta-x-in-window
		 (if rotation-by-90? height-of-icon width-of-icon)
		 x-scale)
	       overflow-units))
	 (height-of-rendering-structure
	   (+r (delta-y-in-window
		 (if rotation-by-90? width-of-icon height-of-icon)
		 y-scale)
	       overflow-units))
	 (line-drawing-description
	   (icon-line-drawing-description icon-description)))
	 
    (multiple-value-bind (ok? information-if-not-ok-or-extrema-if-ok?)
	(valid-line-drawing-description-p 
	  width-of-icon height-of-icon
	  line-drawing-description computed-values-plist)
      
      (cond (ok?
	     (make-decacheable-icon-rendering
	       line-drawing-description
	       computed-values-plist 
	       x-scale y-scale
	       reflection-and-rotation width-of-icon height-of-icon
	       width-of-rendering-structure height-of-rendering-structure
	       (maxf
		 1
		 (length (cdr (get-polychrome-header-if-any line-drawing-description))))
	       icon-description window-for-icon-rendering
	       information-if-not-ok-or-extrema-if-ok? ; was (icon-region-extrema? icon-description)
	       array-of-bitmap-counts
	       number-of-bitmaps
	       memory-used-by-bitmaps
	       (maxr  ;; same as calling compute-size-of-icon-rendering-1
		 width-of-rendering-structure height-of-rendering-structure)
	       t ;; all icon decaching is handled in get-or-make-icon-rendering
	       ))
	    (t
	     #+development
	     (cerror
	       "Continue"
	       "~s is not valid with ~s~%"
	       computed-values-plist
	       line-drawing-description))))))


;;; The function `make-rendering-structure' ... Gensym-window-in-non-icp-case?
;;; should be the appropriate gensym window if it is not the icp case; otherwise,
;;; it should be nil.  In the non-icp case, this returns list made up of gensym
;;; conses of `rendering structure elements' (stored rasters); in the ICP case,
;;; this transmits ICP messaages, and nothing meaningful is returned.

#+development
(defvar line-drawing-description)		; useful for debugging

(defun make-rendering-structure (gensym-window-in-non-icp-case? icon-rendering)
  (let* ((line-drawing-description		; can't be nil here
	   (line-drawing-description-for-rendering?
	     icon-rendering))
	 (sorted-computed-variables
	   (computed-values-plist icon-rendering))
	 (polychrome-header?
	   (get-polychrome-header-if-any line-drawing-description))
	 (polychrome-header-rest? (cdr polychrome-header?))
	 (line-drawing-description-following-header
	   (if polychrome-header?
	       (cdr line-drawing-description)
	       line-drawing-description))
	 (color-region-and-symbol-pairs
	   (or polychrome-header-rest?
	       '((foreground . foreground))))
	 (width
	   (width-of-rendered-icon icon-rendering))
	 (height
	   (height-of-rendered-icon icon-rendering))
	 (x-scale
	   (x-scale-of-rendering icon-rendering))
	 (y-scale
	   (y-scale-of-rendering icon-rendering))
	 (reflection-and-rotation
	   (reflection-and-rotation-of-rendering icon-rendering))
	 (icon-stipple?
	   (get-icon-stipple-if-any line-drawing-description))
	 (minimum-width-for-scratchpad-raster ; width of raster
	   (width-of-rendering-structure icon-rendering))
	 (minimum-height-for-scratchpad-raster ; height of raster
	   (height-of-rendering-structure icon-rendering)))
    (if gensym-window-in-non-icp-case?
	(loop with rest-of-region-extrema
		= (region-extrema-for-rendering? icon-rendering)
	      for (color-region) in color-region-and-symbol-pairs
	      as region-extrema-entry? = (car rest-of-region-extrema)
	      collect
		(multiple-value-bind
		  (x-offset-for-stored-raster? y-offset-for-stored-raster?
		   x-max-for-stored-raster? y-max-for-stored-raster?)
		    (get-x-y-max-and-offset region-extrema-entry?
		      x-scale y-scale
		      width height reflection-and-rotation)
		  (make-region-raster-for-icon
		    (gensym-window-in-non-icp-case?
		      minimum-width-for-scratchpad-raster
		      minimum-height-for-scratchpad-raster
		      x-offset-for-stored-raster? y-offset-for-stored-raster?
		      x-max-for-stored-raster? y-max-for-stored-raster?)
		    (paint-one-bitmap-for-icon-on-scratchpad-raster
		      color-region line-drawing-description-following-header
		      width height x-scale y-scale
		      1 reflection-and-rotation
		      sorted-computed-variables
		      minimum-width-for-scratchpad-raster
		      minimum-height-for-scratchpad-raster
		      icon-stipple?)))
	      using gensym-cons
	      do (setq rest-of-region-extrema (cdr rest-of-region-extrema)))
	(loop with current-scratchpad-raster-type = 'icp
	      with rest-of-region-extrema
		= (region-extrema-for-rendering? icon-rendering)
	      for (color-region) in color-region-and-symbol-pairs
	      as region-extrema-entry? = (car rest-of-region-extrema)
	      do 
	  (multiple-value-bind
	    (x-offset-for-stored-raster? y-offset-for-stored-raster?
	     x-max-for-stored-raster? y-max-for-stored-raster?)
	      (get-x-y-max-and-offset region-extrema-entry?
		x-scale y-scale
		width height reflection-and-rotation)
	    (if x-offset-for-stored-raster?
		(send-icp-region-extrema-for-stored-raster
		  (maxf 0 x-offset-for-stored-raster?)
		  (maxf 0 y-offset-for-stored-raster?)
		  x-max-for-stored-raster? y-max-for-stored-raster?))
	    (send-icp-end-message-block)
	    (paint-one-bitmap-for-icon-on-scratchpad-raster
	      color-region line-drawing-description-following-header
	      width height x-scale  y-scale
	      1 reflection-and-rotation
	      sorted-computed-variables
	      minimum-width-for-scratchpad-raster
	      minimum-height-for-scratchpad-raster
	      icon-stipple?)
	    (send-icp-end-message-block)
	    (setq rest-of-region-extrema (cdr rest-of-region-extrema)))))))

;; Consider just having two separate functions -- one for the ICP case and one for
;; the non-ICP case.

;; Note ICON-EDITOR-POLYCHROME-HEADER-BUG: If polychrome-header?  is non-nil,
;; polychrome-header-rest?  should be non-nil as well.  This is currently not
;; always the case due to a bug in the icon editor (see note to Peng).  - agh,
;; 7/5/90.

;; In fact, valid-line-drawing-description-p was crashing in this case! -fmw,
;; 2/17/95




;;; `Paint-one-bitmap-for-icon-on-scratchpad-raster' is the only routine
;;; responsible for rendering an icon onto the screen (with the possible
;;; exception of the Icon editor).  It sweeps over its principle argument,
;;; line-drawing-description-following-header, drawing each element in that
;;; description with the given scale, reflection-and-rotation, into an area
;;; with the given width and height.  The origin of the line drawing
;;; description coordinate system is at the top left corner of the icon
;;; rectangle.

;;; If we ignore the transformation and clipping issues, the complexity
;;; of this routine arises from the color handling it does.
;;; Color-region-to-paint and foreground-icon-line-color-value
;;; parameterize this.  There are two modalities.  

;;; When color-region-to-paint-or-the-icon-color-pattern is a cons then each
;;; layer is painted using color values computed via the current color map.
;;; This mode is used when printing, or when the icon rendering bit maps are
;;; implemented using a single N-bit deep bit map.

;;; Otherwise, color-region-to-paint-or-the-icon-color-pattern must be a symbol
;;; naming a layer or color which appears in the icon.  Layers in that color
;;; will then be painted in the color value given by
;;; foreground-icon-line-color-value layers above the first in that color will
;;; be drawn in the color value zero.  This modality is used the icon rendering
;;; is implemented as a set of bit maps, one for each color, with each bit map
;;; only 1 bit deep.

;;; This is a draw function, i.e., it can only be used within an on-image-plane body.
;;; It does not check line-drawing-description for syntax or clipping problems.

;;; To support printing there is code here to set `printing-icon-current-region-index?',
;;; a variable documented in the module printing.

;;; When global-icon-stipple? is non-nil, then the stipple is applied to the
;;; entire area given by width-for-icon and height-for-icon for the bitmap
;;; regardless of the color value (e.g., even if "burning" 0).  Meanwhile, the
;;; line drawing description itself may contain stippled areas (stippled-area
;;; elements), which may be for either the whole area or for an area given by
;;; the element.  In this case, the stipple is only applied when not burning
;;; (icon-line-color-value is determined to not be 0). In a case where
;;; global-icon-stipple? is non-nil, any stippled-area element is redundant, and
;;; is therefore ignored.

(defun-void paint-one-bitmap-for-icon-on-scratchpad-raster
    (color-region-to-paint-or-the-icon-color-pattern
      ;; This argument controls what colors to print, it has three cases
      ;; 1. 'foreground, for monochrome icons.
      ;; 2. <color-or-metacolor>, to print only layers of that color.
      ;; 3. <cons>, to print all colors, an alist of (region-name . color-name).
      line-drawing-description-following-header
      width height				; before scaling, rotation/reflection
      x-scale y-scale
      foreground-icon-line-color-value
      reflection-and-rotation
      sorted-computed-variables
      width-for-icon height-for-icon
      global-icon-stipple?)
  (declare (special printing-icon-current-region-index?))
  (loop with default-variables
	  = (cdr (get-variable-specification-if-any
		   line-drawing-description-following-header))
	with started-painting-p =
	(if (consp color-region-to-paint-or-the-icon-color-pattern)
	    t
	    nil)
	with icon-line-color-value
	     = (if (or (consp color-region-to-paint-or-the-icon-color-pattern)
		       (eq color-region-to-paint-or-the-icon-color-pattern 'foreground))
		   foreground-icon-line-color-value
		   0)
	;; If the color region is not 'foreground, then it depends on
	;; the first description element (which will have to be a color
	;; region) whether we "paint" (paint a 1) or "burn" (paint a 0).
	with points
	with line-drawing-directive
	with icon-stipple? = global-icon-stipple?
	with stipple-area-left-edge fixnum = 0
	with stipple-area-top-edge fixnum = 0
	with stipple-area-right-edge fixnum = width-for-icon
	with stipple-area-bottom-edge fixnum = height-for-icon
	for description-element 
	    in line-drawing-description-following-header
	do (cond
	     ((atom description-element)	; a color or region name?
	      (unless global-icon-stipple?
		(when icon-stipple?
		  (when (window-supports-raster-stipples current-window)
		    ;; new for G2 6.0 (MHD 3/6/01))
		    (stipple-rectangle-in-current-scratchpad-raster
		      stipple-area-left-edge stipple-area-top-edge
		      stipple-area-right-edge stipple-area-bottom-edge
		      foreground-icon-line-color-value icon-stipple?))
		  (setq icon-stipple? nil)))
	      (setq icon-line-color-value
		    (cond
		      ((consp color-region-to-paint-or-the-icon-color-pattern)
		       (cond
			 ;; This code made the icon appear not-polychrome is all
			 ;; of its layers were named by colors. -fmw, 1/21/94
;			 ((or (memq description-element all-colors)
;			      (memq description-element all-metacolors))
;			  (setf printing-icon-current-region-index? nil)
;			  (map-color-or-metacolor-to-color-value description-element))
			 (T
			  (or				    ; Paranoia: 0 if region not found.
			    (loop for region-info in color-region-to-paint-or-the-icon-color-pattern
				  as region-index from 0
				  when (eql description-element (car region-info))
				    do
				      (setf printing-icon-current-region-index? region-index)
				      (return
					(map-color-or-metacolor-to-color-value
					  (cdr region-info))))
			    0))))
		      ((eq description-element
			   color-region-to-paint-or-the-icon-color-pattern)
		       ;; pbk fix
		       ;; dont  we need to start-painting since we hit the
		       ;; beginning of the elements for that layer?
		       ;;(setf started-painting-p t) 
		       foreground-icon-line-color-value)
		      ;;((eq color-region-to-paint-or-the-icon-color-pattern
		      ;;   'foreground)
		      ;; pbk fix
		      ;;if the caller wants a monochrome raster then
		      ;; shouldn't we just use the foreground-color
		      ;; for the entire layer? 
		      ;; (setf started-painting-p t)
		      ;; foreground-icon-line-color-value) 
		      (T
		       0))))
	     ((or started-painting-p
		  (/=f icon-line-color-value 0))
	      (setq started-painting-p t)
	      (setq points (cdr description-element)) ; for standard-form directives
	      (setq line-drawing-directive (first description-element))
 	      (evaluating-icon-elements (width height default-variables sorted-computed-variables)
		(case line-drawing-directive
		  ((lines outline)
		   (orient-and-scale-and-paint-polyline
		     points (eq line-drawing-directive 'outline)			
		     x-scale y-scale width height
		     reflection-and-rotation icon-line-color-value))
		  (solid-rectangle
		   (orient-and-scale-and-paint-solid-rectangle
		     (point-x (first points)) (point-y (first points))
		     (point-x (second points)) (point-y (second points))
		     x-scale y-scale
		     width height
		     reflection-and-rotation
		     icon-line-color-value))		
		  ((circle filled-circle)
		   ;; Previously filled-circle was solid-circle.
		   (let* ((first-point (first points))	; could use pop
			  (second-point (second points))     
			  (third-point (third points)))
		     (orient-and-scale-and-paint-arc-or-circle
		       (point-x first-point) (point-y first-point)
		       (point-x second-point) (point-y second-point)
		       (point-x third-point) (point-y third-point)
		       x-scale y-scale
		       width height
		       reflection-and-rotation
		       icon-line-color-value
		       t
		       (eq line-drawing-directive 'filled-circle))))
		  ((rounded-rectangle filled-rounded-rectangle)
		   (orient-and-scale-and-paint-rounded-rectangle
		     (point-x (first points)) (point-y (first points))
		     (point-x (second points)) (point-y (second points))
		     x-scale y-scale
		     width height
		     reflection-and-rotation
		     icon-line-color-value
		     (eq line-drawing-directive 'filled-rounded-rectangle)))
		  (point
		   (orient-and-scale-and-paint-point
		     (point-x (first points)) (point-y (first points))
		     x-scale y-scale width height reflection-and-rotation
		     icon-line-color-value))

		  ;; The next three directives are not in standard form.  Points
		  ;; is not really a list of points in these cases, and so is
		  ;; not used.
		  (stippled-area
		   (unless global-icon-stipple?	; irrelevant/ignore if non-nil
		     (when (/=f icon-line-color-value 0) ; no burning other layers
		       (setq icon-stipple? (second description-element)) ; changes arg!
		       (when (cddr description-element)
			 (let* ((x1 (point-x (third description-element)))
				(y1 (point-y (third description-element)))
				(x2 (point-x (fourth description-element)))
				(y2 (point-y (fourth description-element))))
			   (orient-points-for-icon
			       reflection-and-rotation width height x1 y1 x2 y2)
			   (setq stipple-area-left-edge
				 (delta-x-in-window
				   (maxw 0 (minw x1 x2))
				   x-scale))
			   (setq stipple-area-top-edge
				 (delta-y-in-window
				   (maxw 0 (minw y1 y2))
				   y-scale))
			   (setq stipple-area-right-edge
				 (delta-x-in-window
				   (minw (maxw x1 x2) width-for-icon)
				   x-scale))
			   (setq stipple-area-bottom-edge
				 (delta-y-in-window
				   (minw (maxw y1 y2) height-for-icon)
				   y-scale)))))))
		  (filled-polygon
		   (orient-and-scale-and-paint-filled-polygon
		     description-element
		     x-scale y-scale
		     width height
		     reflection-and-rotation
		     icon-line-color-value))
		  (image
		   ;; (image <name>)
		   ;; (image <name> (x y))
		   ;; (image <name> (x y) (x-scale y-scale))
		   ;;
		   ;; -- If the scales are present, then width and height are
		   ;; scaled by them.  This feature is used by the icon editor.
		   ;; See COPY-DRAWING-ELEMENT-WITH-SLOT-VALUE-CONSES -fmw,
		   ;; 12/20/93
		   (let* ((image-name (simple-eval-for-icon (second description-element)))
			  (point? (third description-element))
			  (scale? (fourth description-element))
			  (x (if point? (point-x point?) 0))
			  (y (if point? (point-y point?) 0))
			  (new-x-scale (if scale?
					   (scalef x-scale (first scale?))
					   x-scale))
			  (new-y-scale (if scale?
					   (scalef y-scale (second scale?))
					   y-scale)))

		     (paint-icon-image-if-any
		       image-name
		       x y
		       new-x-scale new-y-scale
		       width height reflection-and-rotation
		       icon-line-color-value)))
		  (text
		   (let* ((text-reflection-and-rotation
			       #+text-element-reflection-rotation
			       (when (symbolp (fifth description-element))
				 (fifth description-element))
			       #-text-element-reflection-rotation
			       nil)
			  (scale? (if text-reflection-and-rotation
				      (sixth description-element)
				      (fifth description-element)))
			  (new-x-scale (if scale?
					   (scalef x-scale (first scale?))
					   x-scale))
			  (new-y-scale (if scale?
					   (scalef y-scale (second scale?))
					   y-scale)))
		     (orient-and-scale-and-paint-text
		       description-element
		       new-x-scale new-y-scale
		       width height
		       reflection-and-rotation
		       icon-line-color-value)))))))
	finally
	  (when icon-stipple?
	    (when (window-supports-raster-stipples current-window)
	      ;; new for G2 6.0 (MHD 3/6/01))
	      (stipple-rectangle-in-current-scratchpad-raster
		stipple-area-left-edge stipple-area-top-edge
		stipple-area-right-edge stipple-area-bottom-edge
		foreground-icon-line-color-value icon-stipple?)))))


;; This is called only by make-rendering-structure-element.

;; For now, only the default color is used to paint. If color-map is nil,
;; color-value will be 1. It will be necessary to do some error checking here
;; to make sure that the default color is in the color map.  This has to be done
;; here rather than in valid-line-drawing-description-p where most other error
;; checking is done.

;;; The function `paint-icon-image-if-any' copys the data from an image-data
;;; structure into the current scratchpad raster at x,y.  The "1" bits in the
;;; bitmap draw with the given color-value and the "0" bits are transparent.
;;; It is used only by icon drawing.

(defun paint-icon-image-if-any (image-name x-in-icon y-in-icon x-scale y-scale
					   icon-width icon-height reflection-and-rotation
					   icon-line-color-value)
  (let ((image-data?
	  (find-image-data image-name)))
    (when image-data?
      ;; Render small images the slow way: gives better renderings at small scales.
      (let ((slow-is-better-p
	      (or (native-printing-p)
		  (and (or (<f x-scale (normalized-scale))
			   (<f y-scale (normalized-scale)))
		       (<=f (image-data-width image-data?) 64)
		       (<=f (image-data-height image-data?) 64)))))
	
	;; For icons, disable the scheduled image-data transfer.
	(let ((send-image-data-immediately? t))

	  (cond ((and (window-supports-painting-this-image-data current-window image-data?)
		      (not slow-is-better-p))
		 (paint-image-in-current-scratchpad-raster
		   image-data? x-in-icon y-in-icon x-scale y-scale
		   icon-width icon-height reflection-and-rotation
		   nil					    ; Ignored quality.
		   icon-line-color-value))
		(t
		 ;; May want to skip this for large icons, or based on a user option.
		 (slowly-draw-image-data-on-current-scratchpad
		   image-data? x-in-icon y-in-icon x-scale y-scale
		   icon-width icon-height reflection-and-rotation
		   icon-line-color-value))))))))


;;; The orient-and-scale-and-paint functions take coordinates and the width and height for
;;; the icon at normalized scale.  These coordinates are first reflected and/or rotated,
;;; if appropriate, and then scaled to raster coordinates.  The resultant raster
;;; coordinates are then passed to the paint primitives.

;; Consider having those of these functions that are used only once be in-line.

;; Consider renaming these "paint-point-for-icon", etc.

;; Consider reordering the arguments to these functions.



;; Text-in-icons code moved from here to BOXES. (MHD 6/9/99)


;;; The function `orient-points-for-icon' has been moved to IMAGES so that
;;; it is available in Telewindows. -fmw, 1/12/94





(defun orient-and-scale-and-paint-polyline
    (points outline-case?			
	    x-scale y-scale
	    width-at-normalized-scale height-at-normalized-scale
	    reflection-and-rotation? color-value)
  (loop with x1 with y1 with x2 with y2 with x3 with y3
	with remaining-points = points
	while remaining-points
	do (cond
	     ((and (cdr remaining-points)
		   (eq (first (second remaining-points))
		       'arc))
	      ;; prefixed by arc -- draw arc
	      (setq x1 (point-x (first remaining-points)))
	      (setq y1 (point-y (first remaining-points)))
	      (setq x2 (point-x (second (second remaining-points))))
	      (setq y2 (point-y (second (second remaining-points))))
	      (setq x3 (point-x 
			 (if (cddr remaining-points)
			     (third remaining-points)
			     (car points))))
	      (setq y3 (point-y 
			 (if (cddr remaining-points)
			     (third remaining-points)
			     (car points))))
	      (orient-points-for-icon
		  reflection-and-rotation?
		  width-at-normalized-scale height-at-normalized-scale
		x1 y1 x2 y2 x3 y3)
	      (paint-arc-or-circle-in-current-scratchpad-raster
		x1 y1 x2 y2 x3 y3
		x-scale y-scale color-value nil nil)					   
	      (setq remaining-points (cddr remaining-points)))
	     ((or (cdr remaining-points) outline-case?)
	      ;; prefixed by line -- draw line
	      (setq x1 (point-x (first remaining-points)))
	      (setq y1 (point-y (first remaining-points)))
	      (setq x2 (point-x 					       
			 (if (cdr remaining-points)
			     (second remaining-points)
			     (car points))))
	      (setq y2 (point-y 					       
			 (if (cdr remaining-points)
			     (second remaining-points)
			     (car points))))
	      (orient-points-for-icon
		  reflection-and-rotation?
		  width-at-normalized-scale height-at-normalized-scale
		x1 y1 x2 y2)

	      (paint-line-in-current-scratchpad-raster
		(delta-x-in-window x1 x-scale) (delta-y-in-window y1 y-scale)
		(delta-x-in-window x2 x-scale) (delta-y-in-window y2 y-scale)
		color-value t)

;	      (paint-line-in-current-scratchpad-raster-with-clipping
;		(delta-x-in-window x1 x-scale) (delta-y-in-window y1 y-scale)
;		(delta-x-in-window x2 x-scale) (delta-y-in-window y2 y-scale)
;		color-value t
;		width-at-normalized-scale height-at-normalized-scale)
	      ;; Need to figure out if width and height need to be switched 
	      ;; and scaled before calling clipping.


	      (setq remaining-points (cdr remaining-points)))
	     (t
	      ;; If all that remains is the endpoint of the
	      ;;   last object specified, then remove it
	      ;;   -- we're done.
	      (setq remaining-points (cdr remaining-points))))))

;; This makes orient-and-scale-and-paint-line obsolete and makes the
;; arc case of orient-and-scale-and-paint-arc-or-circle obsolete.





(defun orient-and-scale-and-paint-point
       (x y x-scale y-scale width-at-normalized-scale height-at-normalized-scale
	reflection-and-rotation? color-value)
  (orient-points-for-icon
    reflection-and-rotation?
    width-at-normalized-scale height-at-normalized-scale
    x y)					; changes arg
  (paint-point-in-current-scratchpad-raster
    (delta-x-in-window x x-scale)
    (delta-y-in-window y y-scale)
    color-value))




;;; `get-x-y-max-and-offset' returns 4 values:
;;; x-offset-for-stored-raster? y-offset-for-stored-raster?  
;;; x-max-for-stored-raster?    y-max-for-stored-raster?

(defun get-x-y-max-and-offset
    (region-extrema-entry?
      x-scale y-scale
      width height reflection-and-rotation)
  (if (and region-extrema-entry?
	   (second region-extrema-entry?))
      (orient-and-scale-region-extrema
	(second region-extrema-entry?)
	(third region-extrema-entry?)
	(fourth region-extrema-entry?)
	(fifth region-extrema-entry?)
	x-scale y-scale
	width height reflection-and-rotation)
      (values nil nil nil nil)))




;;; `Orient-and-scale-region-extrema' is used by make-rendering-structure to
;;; compute region-extrema for a raster for a region.

(defun orient-and-scale-region-extrema
       (x-offset-for-stored-raster y-offset-for-stored-raster
	x-max-for-stored-raster y-max-for-stored-raster
	x-scale y-scale
	width-at-normalized-scale height-at-normalized-scale
	reflection-and-rotation?)
  (orient-points-for-icon
    reflection-and-rotation?
    width-at-normalized-scale height-at-normalized-scale
    x-offset-for-stored-raster y-offset-for-stored-raster
    x-max-for-stored-raster y-max-for-stored-raster)
  (if (>r x-offset-for-stored-raster x-max-for-stored-raster)
      (psetf x-offset-for-stored-raster x-max-for-stored-raster
	     x-max-for-stored-raster x-offset-for-stored-raster))
  (if (>r y-offset-for-stored-raster y-max-for-stored-raster)
      (psetf y-offset-for-stored-raster y-max-for-stored-raster
	     y-max-for-stored-raster y-offset-for-stored-raster))
  (values (delta-x-in-window x-offset-for-stored-raster x-scale)
	  (delta-y-in-window y-offset-for-stored-raster y-scale)
	  (+r (delta-y-in-window x-max-for-stored-raster x-scale) 1)
	  (+r (delta-y-in-window y-max-for-stored-raster y-scale) 1)))

;; Note that orientation may cause x-offset-for-stored-raster to become greater
;; than x-max-for-stored-raster and y-offset-for-stored-raster to become greater
;; than y-max-for-stored-raster.  The simple comparison checks are sufficient to
;; fix this.  A slightly more complicated approach would be to expand all the
;; rotations (as in orient-points-for-icon) and swap appropriately for each case.




(defun orient-and-scale-and-paint-line
       (x1 y1 x2 y2
	x-scale y-scale
	width-at-normalized-scale height-at-normalized-scale
	reflection-and-rotation? color-value)
  (orient-points-for-icon
    reflection-and-rotation?
    width-at-normalized-scale height-at-normalized-scale
    x1 y1 x2 y2)				; changes args
  (paint-line-in-current-scratchpad-raster
    (delta-x-in-window x1 x-scale) (delta-y-in-window y1 y-scale)
    (delta-x-in-window x2 x-scale) (delta-y-in-window y2 y-scale)
    color-value t)
;  (paint-line-in-current-scratchpad-raster-with-clipping
;    (delta-x-in-window x1 x-scale) (delta-y-in-window y1 y-scale)
;    (delta-x-in-window x2 x-scale) (delta-y-in-window y2 y-scale)
;    color-value t width-at-normalized-scale height-at-normalized-scale)
;; Need to figure out if width and height need to be switched 
;; and scaled before calling clipping.
  )





;;; `orient-and-scale-polgon'
;;; Returns a new list of points that must be reclaimed
;;; by the caller.  Must be wrapped with an evaluating-icon-elements
;;; context.

(defun-substitution-macro orient-and-scale-polygon
    (points reflection-and-rotation?
	    x-scale y-scale
	    width-at-normalized-scale
	    height-at-normalized-scale)
  (loop with result = nil
	for point in points
	as point-x = (point-x point)
	as point-y = (point-y point)
	do
    (orient-points-for-icon ;; pbk notes inefficiency
	reflection-and-rotation?
	width-at-normalized-scale height-at-normalized-scale
        point-x point-y)
    (gensym-push
      (gensym-list
	(delta-x-in-window point-x x-scale)
	(delta-y-in-window point-y y-scale))
      result)
	finally
	  (return (nreverse result))))


;;; `point-list-to-unsigned-point-list' creates a new, flattenned
;;; list of points that have been shifted in the positive direction
;;; by 8192. This is used to ship the points through icp and to
;;; the C code.  Should be wrapped with evaluating-icon-elements.
;;; Return value must be reclaimed by the caller.

(defun point-list-to-unsigned-point-list (point-list)
  #+development
  (when (>f (length point-list) maximum-polygon-points)
    (cerror "go on" "polygon point-list too big"))
  
  (loop with result = nil
	with count = 0
	for p in point-list
	as x = (point-x p) 
	as y = (point-y p)
	while (<f count maximum-polygon-points)
	do
    (incff count)
    (gensym-push (+r x 8192) result)
    (gensym-push (+r y 8192) result)
	finally
	  (return (nreverse result))))



;;; The function `orient-and-scale-and-paint-filled-polygon' ...
;;; Description-element is a line drawing element for a filled polygon.
;;; (See the subsection on Line Drawing Descriptions above for details.)


(defun orient-and-scale-and-paint-filled-polygon
       (description-element
	x-scale y-scale
	width-at-normalized-scale height-at-normalized-scale
	reflection-and-rotation? color-value)
  (cond ((and (not (printing-window-p current-window))
	      (or (not (icp-window-p current-window))
		  (window-supports-un-decomposed-polygons-in-scratchpad-rasters current-window)))
	 
	 (let* ((polygon-points
		  (orient-and-scale-polygon (cadr description-element)
					    reflection-and-rotation?
					    x-scale y-scale
					    width-at-normalized-scale
					    height-at-normalized-scale))
		(unsigned-polygon-points
		  (point-list-to-unsigned-point-list polygon-points)))
	   (paint-filled-polygon-in-current-scratchpad-raster
	     unsigned-polygon-points color-value)
	   (reclaim-gensym-tree polygon-points)
	   (reclaim-gensym-list unsigned-polygon-points)))
	(t  ; otherwise, use decompose into triangles
	 (loop for (point-1 point-2 point-3)	; a list of "triangles"
		   in (cddr description-element)
	       as x1 = (point-x point-1)
	       as y1 = (point-y point-1)
	       as x2 = (point-x point-2)
	       as y2 = (point-y point-2)
	       as x3 = (point-x point-3)
	       as y3 = (point-y point-3) 
	       do (orient-points-for-icon
		      reflection-and-rotation?
		      width-at-normalized-scale height-at-normalized-scale
		    x1 y1 x2 y2 x3 y3)
		  (paint-filled-triangle-in-current-scratchpad-raster
		    (delta-x-in-window x1 x-scale)
		    (delta-y-in-window y1 y-scale)
		    (delta-x-in-window x2 x-scale)
		    (delta-y-in-window y2 y-scale)
		     (delta-x-in-window x3 x-scale)
		     (delta-y-in-window y3 y-scale)
		     color-value)))))




(defun orient-and-scale-and-paint-solid-rectangle
    (x1 y1 x2 y2
	x-scale y-scale
	width-at-normalized-scale height-at-normalized-scale
	reflection-and-rotation? color-value)
  (orient-points-for-icon
      reflection-and-rotation?
      width-at-normalized-scale height-at-normalized-scale
    x1 y1 x2 y2)				; changes args
  ;; G2 wants to add one pixel to the width and height here.  native-printing is
  ;; special because at this point the coordinates are not in pixels -- they are
  ;; scaled again before going to the printer. So adding one would get as a
  ;; whole additional logical unit, which would be much wider than a pixel.
  (let ((delta (if (native-printing-p) 0 1)))
    (paint-solid-rectangle-in-current-scratchpad-raster 
      (delta-x-in-window (minw x1 x2) x-scale)
      (delta-y-in-window (minw y1 y2) y-scale)
      (+r (delta-x-in-window (maxw x1 x2) x-scale) delta)
      (+r (delta-y-in-window (maxw y1 y2) y-scale) delta)
      color-value)))




(defun orient-and-scale-and-paint-rounded-rectangle
       (x1 y1 x2 y2
	x-scale y-scale
	width-at-normalized-scale height-at-normalized-scale
	reflection-and-rotation? color-value filled?)
  (let* ((radius
	   ;; make the radius whichever is less: 13, 1/3 of the width, 1/3 of
	   ;; the height:
	   (minw 13
		 (with-temporary-gensym-float-creation
		     orient-and-scale-and-paint-rounded-rectangle
		   (round
		     (/ 
		       (minw
			 (absw (-w x2 x1))
			 (absw (-w y2 y1)))
		       3.0)))))
	 (d (round (* .2929 radius)))
	 (inner-x1 (+w x1 radius))
	 (inner-y1 (+w y1 radius))
	 (arc-x1 (+w x1 d))
	 (arc-y1 (+w y1 d))
	 (inner-x2 (-w x2 radius))
	 (inner-y2 (-w y2 radius))
	 (arc-x2 (-w x2 d))
	 (arc-y2 (-w y2 d)))
    (orient-points-for-icon
      reflection-and-rotation?
      width-at-normalized-scale height-at-normalized-scale
      x1 y1 x2 y2				; changes args
      inner-x1 inner-y1 inner-x2 inner-y2
      arc-x1 arc-y2 arc-x2 arc-y2)
    (cond
      ((>w x1 x2)
       (psetq x1 x2 x2 x1)
       (psetq inner-x1 inner-x2 inner-x2 inner-x1)
       (psetq arc-x1 arc-x2 arc-x2 arc-x1)))
    (cond
      ((>w y1 y2)
       (psetq y1 y2 y2 y1)
       (psetq inner-y1 inner-y2 inner-y2 inner-y1)
       (psetq arc-y1 arc-y2 arc-y2 arc-y1)))
    (let* ((x1-in-window
	     (delta-x-in-window x1 x-scale))
	   (y1-in-window
	     (delta-y-in-window y1 y-scale))
	   (x2-in-window
	     (delta-x-in-window x2 x-scale))
	   (y2-in-window
	     (delta-y-in-window y2 y-scale))
	   (inner-x1-in-window
	     (delta-x-in-window inner-x1 x-scale))
	   (inner-y1-in-window
	     (delta-y-in-window inner-y1 y-scale))
	   (inner-x2-in-window
	     (delta-x-in-window inner-x2 x-scale))
	   (inner-y2-in-window
	     (delta-y-in-window inner-y2 y-scale)))
      (paint-arc-or-circle-in-current-scratchpad-raster
	x1 inner-y1
	arc-x1 arc-y1
	(+r inner-x1 1) y1			; doesn't close without 1 extra
	x-scale y-scale color-value		;   (here and in next 3 below)!!
	filled?					; say it's a circle, because
	filled?)				;   we don't have "wedges"
      (paint-arc-or-circle-in-current-scratchpad-raster
	x2 inner-y1
	arc-x2 arc-y1
	(-r inner-x2 1) y1
	x-scale y-scale color-value filled? filled?)
      (paint-arc-or-circle-in-current-scratchpad-raster
	x1 inner-y2
	arc-x1 arc-y2
	(+r inner-x1 1) y2
	x-scale y-scale color-value filled? filled?)
      (paint-arc-or-circle-in-current-scratchpad-raster
	x2 inner-y2
	arc-x2 arc-y2
	(-r inner-x2 1) y2
	
	x-scale y-scale color-value filled? filled?)
      (cond
	(filled?    
	 (paint-solid-rectangle-in-current-scratchpad-raster	; top bar
	   inner-x1-in-window y1-in-window
	   inner-x2-in-window inner-y1-in-window
	   color-value)
	 (paint-solid-rectangle-in-current-scratchpad-raster	; middle bar
	   x1-in-window inner-y1-in-window
	   x2-in-window inner-y2-in-window
	   color-value)
	 (paint-solid-rectangle-in-current-scratchpad-raster	; bottom bar
	   inner-x1-in-window inner-y2-in-window
	   inner-x2-in-window y2-in-window
	   color-value))
	(t
	 (paint-line-in-current-scratchpad-raster	; top line
	   inner-x1-in-window y1-in-window
	   inner-x2-in-window y1-in-window
	   color-value t)
	 (paint-line-in-current-scratchpad-raster	; bottom line
	   inner-x1-in-window y2-in-window
	   inner-x2-in-window y2-in-window
	   color-value t)
	 (paint-line-in-current-scratchpad-raster	; left line
	   x1-in-window inner-y1-in-window
	   x1-in-window inner-y2-in-window
	   color-value t)
	 (paint-line-in-current-scratchpad-raster	; right line
	   x2-in-window inner-y1-in-window
	   x2-in-window inner-y2-in-window
	   color-value t))))))

;; Needs work! The idea is to have a standard diameter for the arcs and
;; to not magnify them!  The only absolutely necessary application for this
;; now is action buttons.  The problem is that magnification has already been
;; combined with scaling by the time we are at this level, so a lot of
;; rearranging would be needed to accommodate this change.

;; Even if action buttons were the only application, since there are so many
;; of them, it would still save considerably in terms of efficiency
;; of drawing and also of transmission (esp. in Telewindows) over doing
;; this as a line drawing description.  

;; Another good way out for action buttons would be to just draw them directly
;; on the window.  There is no facility for drawing circles on windows, but
;; you could just unroll the logic into rectangle and line drawing, since the
;; radius is constant.  Alternatively, you could draw circles by making special
;; purpose use of rasters.

;; Note that this is not available for users at present, but is used for
;; action buttons, which users cannot define subclasses of.  This means that
;; there can be no use of the directives rounded-rectangle or filled-rounded-
;; rectangle saved in KBs at this time. (MHD 8/17/89)

;; Consider combining this with orient-and-scale-and-paint-solid-rectangle.

;; See if this can be simplified.

;; (MHD 8/17/89)






;;; `Orient-and-scale-and-paint-arc-or-circle,' given three points and other
;;; parameters, draws the specified arc or circle onto the current scratchpad
;;; raster.

(defun orient-and-scale-and-paint-arc-or-circle
       (x1 y1 x2 y2 x3 y3
	x-scale y-scale
	width-at-normalized-scale height-at-normalized-scale
	reflection-and-rotation? color-value circle? filled?)
  (orient-points-for-icon
    reflection-and-rotation?
    width-at-normalized-scale height-at-normalized-scale
    x1 y1 x2 y2 x3 y3)				; changes args
  (paint-arc-or-circle-in-current-scratchpad-raster
    x1 y1 x2 y2 x3 y3
    x-scale y-scale color-value circle? filled?))

;; Orient-and-scale-and-paint-arc-or-circle reflects and/or rotates the three points but
;; leaves it to paint-arc-or-circle-in-current-scratchpad-raster to scale them.  (See
;; paint-arc-or-circle-in-current-scratchpad-raster in module WINDOWS).




;; `rotated-by-90-p' has been moved to IMAGES. -fmw, 1/12/94

;;; `Rotate-point-in-line-drawing-description' reflects and rotates a point, 
;;; where the arguments are for the icon at normalized scale.

(defun rotate-point-in-line-drawing-description
       (reflection-and-rotation block-width block-height x y)
  (orient-points-for-icon
    reflection-and-rotation
    block-width block-height x y)		; changes arg
  (values x y))


(eval-when (:compile-toplevel :load-toplevel :execute)
(def-global-property-name reflection-and-rotation-multiplication-table)	; a plist


  ;; identity case:
  (setf (reflection-and-rotation-multiplication-table 'normal)
	(setf (reflection-and-rotation-multiplication-table 'nil)
	      '(nil normal
		normal normal
		clockwise-90 clockwise-90
		clockwise-180 clockwise-180
		clockwise-270 clockwise-270
		reflected reflected 
		reflected-clockwise-90 reflected-clockwise-90
		reflected-clockwise-180 reflected-clockwise-180
		reflected-clockwise-270 reflected-clockwise-270)))

  
  (setf (reflection-and-rotation-multiplication-table 'clockwise-90)
	'(nil clockwise-90 normal clockwise-90 clockwise-90 clockwise-180
	  clockwise-180 clockwise-270 clockwise-270 normal
	  reflected reflected-clockwise-270 
	  reflected-clockwise-90 reflected
	  reflected-clockwise-180 reflected-clockwise-90
	  reflected-clockwise-270 reflected-clockwise-180))
  (setf (reflection-and-rotation-multiplication-table 'clockwise-180)
	'(nil clockwise-180 normal clockwise-180 clockwise-90 clockwise-270
	  clockwise-180 normal clockwise-270 clockwise-90
	  reflected reflected-clockwise-180
	  reflected-clockwise-90 reflected-clockwise-270
	  reflected-clockwise-180 reflected
	  reflected-clockwise-270 reflected-clockwise-90))
  (setf (reflection-and-rotation-multiplication-table 'clockwise-270)
	'(nil clockwise-270 normal clockwise-270 clockwise-90 normal
	  clockwise-180 clockwise-90 clockwise-270 clockwise-180
	  reflected reflected-clockwise-90
	  reflected-clockwise-90 reflected-clockwise-180
	  reflected-clockwise-180 reflected-clockwise-270
	  reflected-clockwise-270 reflected))
  (setf (reflection-and-rotation-multiplication-table 'reflected)
	'(nil reflected normal reflected clockwise-90 reflected-clockwise-90
	  clockwise-180 reflected-clockwise-180 
	  clockwise-270 reflected-clockwise-270
	  reflected normal reflected-clockwise-90 clockwise-90
	  reflected-clockwise-180 clockwise-180 reflected-clockwise-270
	  clockwise-270))
  (setf (reflection-and-rotation-multiplication-table 'reflected-clockwise-90)
	'(nil reflected-clockwise-90 normal reflected-clockwise-90
	  clockwise-90 reflected-clockwise-180
	  clockwise-180 reflected-clockwise-270 clockwise-270 reflected
	  reflected clockwise-270 reflected-clockwise-90 normal
	  reflected-clockwise-180 clockwise-90 reflected-clockwise-270 clockwise-180))
  (setf (reflection-and-rotation-multiplication-table 'reflected-clockwise-180)
	'(nil reflected-clockwise-180 normal reflected-clockwise-180
	  clockwise-90 reflected-clockwise-270
	  clockwise-180 reflected clockwise-270 reflected-clockwise-90
	  reflected clockwise-180 reflected-clockwise-90 clockwise-270
	  reflected-clockwise-180 normal reflected-clockwise-270 clockwise-90))
  (setf (reflection-and-rotation-multiplication-table 'reflected-clockwise-270)
	'(nil reflected-clockwise-270 normal reflected-clockwise-270
	  clockwise-90 reflected
	  clockwise-180 reflected-clockwise-90 clockwise-270 reflected-clockwise-180
	  reflected clockwise-90 reflected-clockwise-90 clockwise-180
	  reflected-clockwise-180 clockwise-270 reflected-clockwise-270 normal))
  )						; eval-when

;; This could be more efficient if it had to be.



;;; Multiply-reflection-and-rotation multiplies reflection-and-rotation-1
;;; by reflection-and-rotation-2, using the above tables.

(defun multiply-reflection-and-rotation
       (reflection-and-rotation-1 reflection-and-rotation-2)
  (if (or (null reflection-and-rotation-1)
	  (eq reflection-and-rotation-1 'normal))
      reflection-and-rotation-2
      (getfq (reflection-and-rotation-multiplication-table
	       reflection-and-rotation-1)
	     reflection-and-rotation-2)))



;;; Invert-reflection-and-rotation computes the inverse of reflection-and-
;;; rotation, using the above tables.

(defun invert-reflection-and-rotation (reflection-and-rotation)
  (if (or (null reflection-and-rotation)
	  (eq reflection-and-rotation 'normal))
      'normal
      (loop for (multiplier product)
	    on (reflection-and-rotation-multiplication-table
		 reflection-and-rotation)
		by #'cddr
	    when (eq product 'normal)
	      return multiplier)))



;;; The function `legal-reflection-and-rotation-p' returns true if candidate is
;;; a valid reflection-and-rotation symbol.  Candidate-symbol must be a symbol.

(defun legal-reflection-and-rotation-symbol-p (candidate-symbol)
  (not (null (reflection-and-rotation-multiplication-table candidate-symbol))))






;;;; Creating Icon Descriptions



;;; The function `create-icon-description' must be usable immediately after
;;; module ENTITIES is loaded, even at compile time.

;;; This does not check for invalid icon descriptions.  That is done explicitly
;;; by create-icon-description-if-valid for user-defined icon descriptions, and
;;; developers may use valid-line-drawing-description-p to check theirs when
;;; written, and that should suffice.

;;; As of G2 4.0, this only creates polychrome icons (and monochrome icons
;;; should really not be created ever).  If necessary, this adds a polychrome
;;; header as needed based on icon-line-color? and
;;; icon-line-drawing-description.

;;; The optional arg region-extrema?  can be used for polychrome icons to limit
;;; the sizes of rasters to the boundaries of their corresponding regions.  This
;;; should be used only for polychrome icons and is entirely optional.  It should
;;; be used, however, since it can yield significant improvements in memory
;;; efficiency and speed.  A good example of this is the case of a large icon
;;; which has a small indicator light as a separate region.  If the
;;; region-extrema?  option is not used, then a raster the size of the entire icon
;;; will be allocated for the indicator light region.  Besides being wasteful of
;;; memory, this is slow because the entire raster is bitblted.

;;; Region-extrema is an alist with elements of the form
;;;   (region . extrema).
;;; Extrema is a quadruple of minimum-x, minimum-y, maximum-x, and maximum-y where
;;; the origin is the top left corner of the icon.  This format is not the same as
;;; the x-offset, y-offset, width, height format used for bounding boxes for
;;; characters (see character descriptions section of FONTS).  The reason that
;;; this can't be used is that the above width and height are computed by
;;; subtracting the maxima from the minima.  Since this is done before scaling,
;;; round-off errors can result when scaling is done.  Thus, to ensure proper
;;; scaling, the extrema must be the exact same workspace coordinates as the
;;; extreme values of the line elements from which they are derived.

;;; Region extrema are computed by valid-line-drawing-description-p which is
;;; called by create-icon-description-if-valid (used for user defined icons).
;;; Create-icon-description-if-valid calls create-icon-description with the
;;; region-extrema?  arg if there is more than one region.  Thus, all user defined
;;; icons have this optimization.

;;; The region extrema are maintained in the icon-region-extrema?  slot of an
;;; icon-description and in the region-extrema-for-rendering?  slot of an
;;; icon-rendering.  The icon-region-extrema?  slot is set in
;;; create-icon-description (when making the icon description) to the
;;; region-extrema?  arg.  The region-extrema-for-rendering?  slot is set in
;;; get-or-make-icon-rendering to the value of the icon-region-extrema?  slot.
;;; The icon-region-extrema?  slot has a reclaimer but the
;;; region-extrema-for-rendering?  slot does not.  Thus, the slots
;;; icon-region-extrema?  and region-extrema-for-rendering?  are analogous to
;;; the slots icon-line-drawing-description and
;;; line-drawing-description-for-rendering?  They point to the same list, and
;;; the reclamation is done when the icon description is reclaimed.
  
#+unused
(def-system-variable current-icon-description-serial-number icons 0)

#+unused
(setq current-icon-description-serial-number 0)

#+unused
(defmacro increment-current-icon-description-serial-number ()
  `(incff current-icon-description-serial-number))

(defun create-icon-description
    (width-of-icon height-of-icon icon-line-drawing-description
		   &optional
		   icon-line-color? icon-x-magnification? icon-y-magnification?
		   x-offset-for-fine-positioning-of-icon?
		   y-offset-for-fine-positioning-of-icon?
		   region-extrema?)
  
  ;; There will be an icon-line-color? for system-defined classes only.
  (when (null (get-polychrome-header-if-any icon-line-drawing-description))
    ;; Do some fixup if necessary:
    (let ((polychrome-header (slot-value-list 'polychrome)))
      (slot-value-push polychrome-header icon-line-drawing-description)
      (when icon-line-color?
	(slot-value-push
	  (slot-value-cons 'icon-color icon-line-color?)
	  (cdr polychrome-header))
	(slot-value-push
	  'icon-color
	  (cdr icon-line-drawing-description)))
      (when (memq 'foreground (cdr icon-line-drawing-description))
	(slot-value-push
	  (slot-value-cons 'foreground 'foreground)
	  (cdr polychrome-header)))))
  
  (let ((icon-description
	  (make-icon-description
	    width-of-icon height-of-icon
	    x-offset-for-fine-positioning-of-icon?
	    y-offset-for-fine-positioning-of-icon?
	    icon-line-color?
	    icon-x-magnification? icon-y-magnification?
	    icon-line-drawing-description
	    (cdr (get-polychrome-header-if-any icon-line-drawing-description))
	    region-extrema?)))

    #+unused
    (setf (serial-number-for-icon-description icon-description)
	  (increment-current-icon-description-serial-number))
    icon-description))



(defmacro with-rle-string ((length value rle-bcb) &body body)
  `(loop with rle-bcb-len = (length ,rle-bcb)
	 with length-low
	 with ,length
	 with ,value
	 with valuep = t
	 for i from 0 below rle-bcb-len
	 for code = (char-code (schar ,rle-bcb i))
	 do (cond ((not valuep)
		   (setq ,length (+f (ash (-f code 48) 3) length-low))
		   (setq valuep t))
		  ((< code 40)
		   (setq ,value (-f code 32))
		   (setq ,length 1))
		  ((< code 48)
		   (setq ,value (-f code 40))
		   (setq ,length 2))
		  (t
		   (setq ,value (logandf (-f code 48) 7))
		   (setq length-low (ashf (-f code 48) -3))
		   (setq valuep nil)))
	 do (when valuep
	      ,@body)))

(defun get-savable-image-info-for-image-name (image-name)
  (slot-value-cons
   'image-info
   #-rh-gensym-logo
   (progn image-name nil) ; ??
   #+rh-gensym-logo
   (loop with image-info
	   = (get-gensym-logo-image-definition-info image-name)
	 for (p v) on image-info by 'cddr
	 collect p
	   using slot-value-cons
	 collect (case p
		   (pathname (copy-text-string v))
		   (color-map
		    (loop with len = (length v)
			  with ma = (allocate-managed-array len)
			  for i from 0 below len
			  for e in v
			  do (setf (managed-svref ma i) e)
			  finally (return ma)))
		   (byte-code-bodies
		    (loop for rle-bcb in v
			  for total-length
			      = (let ((total-length 0))
				  (with-rle-string (length value rle-bcb)
				    (incff total-length length))
				  total-length)
			  for buffer = (allocate-byte-vector total-length)
			  for index = 0
			  do (with-rle-string (length value rle-bcb)
			       (loop for count from 0 below length
				     do (setf (byte-vector-aref buffer index) value)
					(incff index)))
			  collect (make-byte-code-body total-length buffer nil nil nil)
			    using slot-value-cons))
		   (t v))
	 using slot-value-cons
	 finally (reclaim-slot-value-tree image-info))))

;; Not sure how this works completely, but it's called from code in DEFINITIONS,
;; but it's only used when #+rh-gensym-logo is enabled. (MHD 1/12/01)




;;; The variable `list-of-built-in-image-definitions' is used by
;;; find-image-named....

#+rh-gensym-logo
(defvar list-of-built-in-image-definitions nil)

;; There was no documentation on this, but you can see its use in the code below
;; and in DEFINITIONS, find-image-named. (MHD 1/12/01)





;;;; RH Gensym Logo



#+rh-gensym-logo
(progn


#+development
(defun make-list-image-info-from-image (image-name)
  (let ((image-data?
	 (find-image-data image-name)))
    (loop with data = (cdr (construct-image-info-from-image-data image-data?))
	  for (name value) on data by 'cddr
	  collect name
	  collect (case name
		    (pathname #w"")
		    (color-map
		     (loop for i from 0 below (managed-array-length value)
			   collect (managed-svref value i)))
		    (byte-code-bodies
		     (loop for bcb in value
			   for len = (byte-code-body-length bcb)
			   for data = (byte-code-body-byte-vector bcb)
			   collect (twith-output-to-gensym-string
				    (loop for pos = 0 then next-pos
					  while (<f pos len)
					  for v = (byte-vector-aref data pos)
					  for next-pos
					      = (or (loop for p from (1+f pos) below len
							  unless (=f v (byte-vector-aref data p))
							    return p)
						    len)
					  for n = (-f next-pos pos)
					  do (cond ((=f 1 n)
						    (twrite-char (code-char (+f 32 v))))
						   ((=f 2 n)
						    (twrite-char (code-char (+f 40 v))))
						   (t
						    (twrite-char (code-char (+f 48 v (ashf (logandf n #x7) 3))))
						    (twrite-char (code-char (+f 48 (ashf n -3))))))))))
		    (t value)))))

#+development
(defun make-image-definition-constructors ()
  ;; Load /home/rh/gensym-logo/gensym-logo.kb
  (let ((names '(gensym-logo-32 gensym-logo-48 gensym-logo-64 gensym-logo-96 gensym-logo-128 gensym-logo-160
		 gensym-logo-192 gensym-logo-224 gensym-logo-256 gensym-logo-320 gensym-logo-384 gensym-logo-448
		 gensym-logo-512
		 gensym-logo-256-t)))
    (format t "~%~%(defvar list-of-built-in-image-definitions~%  '(")
    (loop for first = t then nil
	  for name in names
	  do (unless first (format t "~%    "))
	     (format t "#:~(~A~)" name))
    (format t "))~%")
    (loop for name in names
	  for i from 0
	  do (format t "~%(defvar built-in-~(~a~) (nth ~d list-of-built-in-image-definitions))" name i))
    (format t "~%")
    (format t "~%(defun get-gensym-logo-image-definition (name)")
    (format t "~%   (cond")
    (loop with *print-level* = nil
	  with *print-length* = nil
	  for name in names
	  for name-in-kb = (if (eq name 'gensym-logo-256-t)
			       'gensym-logo-256-tag-2
			       name)
	  for plist = (make-list-image-info-from-image name-in-kb)
	  for width = (getf plist 'width)
	  for height = (getf plist 'height)
	  for data = (getf plist 'byte-code-bodies)
	  do (format t "~%     ((eq name built-in-~(~a~))" name)
	     (format t "~%      '#(~d ~d" width height)
	     (loop for string in data
		   do (format t "~%        ~S" string))
	     (format t "))"))
    (format t "))~%~%")))

(defun lookup-name-for-gensym-logo-image-definition (desired-width &optional with-tagline-p)
  (declare (special list-of-built-in-image-definitions built-in-gensym-logo-256-t))
  (loop for last-name = nil then name
	for name in list-of-built-in-image-definitions
	for data = (get-gensym-logo-image-definition name)
	for width = (svref data 0)
	for has-tagline-p = (eq name built-in-gensym-logo-256-t)
	for tagline-matches-p = (if with-tagline-p
				    has-tagline-p
				    (not has-tagline-p))
	when (and (=f width desired-width)
		  tagline-matches-p)
	  return name
	when (and (>f width desired-width)
		  tagline-matches-p)
	  return last-name
	finally (return last-name)))

(defun get-gensym-logo-image-definition-info (name &optional with-tagline-p)
  (when (fixnump name)
    (setq name (lookup-name-for-gensym-logo-image-definition name with-tagline-p)))
  (let ((data (get-gensym-logo-image-definition name)))
    (slot-value-list 'pathname ""
		     'number-of-colors 8
		     'color-map (copy-list-using-slot-value-conses
				 (if with-tagline-p
				     '(12067379 12416401 13608123 14929627 ; gensym-logo-2.act
				       16117491 5964630 8996998 16777215)
				     '(12522271 13784156 15719906 13340577 ; gensym-logo.act
				       14662085 4522576 8343431 16777215)))
		     'format 'gif
		     'width (svref data 0)
		     'height (svref data 1)
		     'depth 8
		     'transparent-color-index 7 ; or -1
		     'byte-code-bodies
		     (loop for i from 2 below (length data)
			   collect (svref data i)
			     using slot-value-cons))))

;bar-width 6 is desired-width 128
;bar-width 1 is desired-width 32
(defun create-new-gensym-logo-description (desired-width &optional with-tagline-p)
  (let* ((name (lookup-name-for-gensym-logo-image-definition desired-width with-tagline-p))
	 (data (get-gensym-logo-image-definition name))
	 (width (svref data 0))
	 (height (svref data 1))
	 (icon-description
	  (create-icon-description
	   width height
	   `((polychrome (transparent . transparent))
	     (variables)
	     (background-layer (image ,name (0 0)))
	     transparent (point (0 0))))))
    (setf (icon-description-background-image icon-description)
	  `(image ,name (0 0)))
    icon-description))

(loop for x in
  '(#:gensym-logo-32
    #:gensym-logo-48
    #:gensym-logo-64
    #:gensym-logo-96
    #:gensym-logo-128
    #:gensym-logo-160
    #:gensym-logo-192
    #:gensym-logo-224
    #:gensym-logo-256
    #:gensym-logo-320
    #:gensym-logo-384
    #:gensym-logo-448
    #:gensym-logo-512
    #:gensym-logo-256-t)
      do (pushnew x  list-of-built-in-image-definitions))

;; Previously list-of-built-in-image-definitions was defvar'd, but it was pulled
;; out of the #+rh-gensy-logo section today. (MHD 1/12/01)

(defvar built-in-gensym-logo-32 (nth 0 list-of-built-in-image-definitions))
(defvar built-in-gensym-logo-48 (nth 1 list-of-built-in-image-definitions))
(defvar built-in-gensym-logo-64 (nth 2 list-of-built-in-image-definitions))
(defvar built-in-gensym-logo-96 (nth 3 list-of-built-in-image-definitions))
(defvar built-in-gensym-logo-128 (nth 4 list-of-built-in-image-definitions))
(defvar built-in-gensym-logo-160 (nth 5 list-of-built-in-image-definitions))
(defvar built-in-gensym-logo-192 (nth 6 list-of-built-in-image-definitions))
(defvar built-in-gensym-logo-224 (nth 7 list-of-built-in-image-definitions))
(defvar built-in-gensym-logo-256 (nth 8 list-of-built-in-image-definitions))
(defvar built-in-gensym-logo-320 (nth 9 list-of-built-in-image-definitions))
(defvar built-in-gensym-logo-384 (nth 10 list-of-built-in-image-definitions))
(defvar built-in-gensym-logo-448 (nth 11 list-of-built-in-image-definitions))
(defvar built-in-gensym-logo-512 (nth 12 list-of-built-in-image-definitions))
(defvar built-in-gensym-logo-256-t (nth 13 list-of-built-in-image-definitions))

;  Copy /home/rh/gensym-logo/images/gensym-logo.bmp
;    (or "logo with tag.gif")
;    to a PC that has Adobe Photoshop.
;  Possibly also copy /home/rh/gensym-logo/images/gensym-logo.act to that PC.
;    (use gensym-logo-2.act for "logo with tag.gif")
;  Load the logo into Photoshop.
;  Add 100 pixels of extra width and height to the canvas,
;    to make sure there is sufficient whitespace that the anti aliasing
;    will be done properly. (Image, Canvas Size)
;  Convert to RGB color (Image, Mode, RGB Color)
;    (This step is needed if the original image came from ".gif",
;     and is not necessary if it came from ".bmp" format)
;  Save the logo in psd format, since it loads much faster than the bmp format

;  --- Calculate the color table, using a "typical" image (a 256 pixel width logo)
;  ---  (This step can be skipped, because /home/rh/gensym-logo/images/gensym-logo.act 
;  ---   is the resulting color table. gensym-logo-2.act is for "logo with tag.gif")
;  Reduce the size to 256 pixels wide.  (afterwards, do View Actual Pixels)
;  Convert to indexed.  
;     Image, Mode, Indexed Color
;       Pallette: Adaptive; Color Depth: Other; Colors: 8; Dither: None; Color Matching: Best
;     Image, Mode, Color Table
;       Save the color table to gensym-logo.act

;  --- Compute a gif file for each size.
;  Load the logo in psd format.
;  Reduce to desired width in pixels.
;  Convert to indexed, using the saved color table.  
;     Image, Mode, Indexed Color
;       Pallette: Custom; Load gensym-logo.act (or gensym-logo-2.act)
;       Dither: None; Color matching: best
;  Save in compuserve gif format, with a name indicating the width.

;Here is how to put the logo into G2
;  --- Write a kb that uses each image.
;  --- Load the kb into a development G2
;  Run this form:
;     (make-image-definition-constructors)
;  Copy the results into lisp/icons.lisp
;  Put the color map into get-gensym-logo-image-definition-info.
(defun get-gensym-logo-image-definition (name)
  (cond
    ((eq name built-in-gensym-logo-256-t)
     '#(256 132
        "7P"
        "7P"
        "7P"
        "7P"
        "7P"
        "7P"
        "7P"
        "7P"
        "7P"
        "7P"
        "7P"
        "7P"
        "7P"
        "7P"
        "7P"
        "7P"
        "7P"
        "7P"
        "7P"
        "?=\",*GB"
        "_<\"T0\"_B"
        "G<\"#!#$?C"
        "g;$#!+$\"OC"
        "G;\"$#I0$oC"
        "7;$!(#\"GD"
        "W:\"#!(#$_D"
        "?:\"$!(!#\"oD"
        "o9$!H0!\"GE"
        "W9$!H0!$\"WE"
        "?9\"#!H0!$oE"
        "o8$!P0!\"?F"
        "W8\"#!P0#\"OF"
        "_5,\"G2\"#X0!\"_F"
        "O5$U0#o1\"!X0!\"oF"
        "74$[0$\"/\"e0$W1\"!P0!$\"O0\"$S0$\"_1J0W0\"$S0$\"G2\"$S0$\"W5*W0\"$S0$\"W1$S0,O5"
        "_3$#=1&$&e0#G1\"#P0!$/\"#i0H0!#\"/\"^0U0&'$#&51&#\"W1\"#&51&#\"/#V1$g0$>1#^0U0&'\"#&51&#\"_0\"$&=1&$\"o4"
        "O3\"&U2#?1#P0!\"/#H0!\"_0\"!P0#'$E1&e1&G1$e1$'&U1#g0#U2&e1&O0#m1$g4"
        "G3$e2$o0#!P0$'\"!H0#\"'\"#N0#\"'!P0#'#=3&\"o0#52$&U1#g0#=1&E3&#&=2&_4"
        "?3$m0&K0&m0N0$g0\"!P0!\"'$H0!$'\"&M0.%&*X0$'&]1N0E1\"_0#e0.K0&]0&$&E1&\"o0&m0&\"$&]1N0=2N0=1#W4"
        "73\"m0$_0\"m0\"o0#X0#/!H0!/#-&$W0*'!P0!/#E1#\"W0$51#W0\"e0$_0$e0\"'&51\"G1$]0#W0$E1#\"W0$U1&$W0\"&51\"O4"
        "73&e0$o0$e0&_0$!X0#'$!H0!'\"&%&\"?1#P0!/$51#71\"51W0&]0&g0$e0\"/&m0O1\"U0#_0\"51&\"o0\"&51&$71#m0#O4"
        "o2\"m0?1&e0$O0#`0$'$P0!*&%#O1#P0!/$m0#G1$m0$/\"e0#o0&U0&O0#m0$G1#U0\"_0\"m0&G1#51\"G1m0&O4"
        "o2#e0#?1&e0&/!`0$'$X0\"'-$W1!P0!/$m0\"O1m0#/\"e0#o0\"&-#W0\"m0&G1&M0&g0\"m0\"G1\"m0&O1&m0O4"
        "o2&e0$?1$e0&\"!`0#'#X0$'&%\"W1\"X0#'\"$m0\"O1&e0&/$e0&?1\"o0#m0\"71#U0$g0\"m0\"O1&e0&O1#m0\"G4"
        "o2&e0\"?1\"m0\"`0#'$X0#'&%\"_1#X0J0$m0\"O1&e0&/$m0&\"o1$m0#71&M0&o0\"m0\"O1&e0&O1$m0\"G4"
        "o2&e0G1\"m0\"!X0*`0'$%$_1\"!P0#'&\"$m0\"O1&e0&/\"=1#$g1m0&o0\"U0#o0\"m0\"O1&e0&O1$m0\"G4"
        "o2&e0G1\"m0\"!P0$'!X0#'%#g1!X0*%'$m0\"O1&e0&O0&M1#\"O1#m0$g0#U0\"o0\"m0\"O1&e0&O1$m0$G4"
        "o2&e0\"?1$m0\"P0!'#X0!'#&g1#X0$'&#'$m0\"O1&e0&O0$]1.\"71\"m0&_0\"U0#71\"m0\"O1&e0&O1$m0$G4"
        "o2&e0$?1#e0&\"P0$'`0$'&$_1#X0#'#%/$m0\"O1&e0&W0&m1#\"o0&e0&_0$U0$71\"m0\"O1&e0&O1$m0$G4"
        "o2#e0&?1&e0&#H0!'#`0\"$&W1\"!X0\"'#%#/$m0\"O1&e0&_0&52\"g0#m0$W0&M0&?1\"m0\"O1&e0&O1$m0$G4"
        "o2\"m0\"71&e0#!H0$'`0!'&$G1$!X0#/&%#O0$m0\"O1&e0&_0\"#52\"_0\"m0&O0$U0$?1\"m0\"O1&e0&O1$m0$G4"
        "73&e0#o0#e0&$P0'$`0\"'#71\"$!P0!#\"'$&%&W0$m0\"O1&e0&o0$&e1&g0#m0\"/&M0&G1\"m0\"O1&e0&O1$m0$G4"
        "?3&e0#_0$m0\"!H0!'#X0!o0\"$#!X0!\"/\"&-#_0$m0\"O1&e0&?1\"&]1$_0$m0$/&M0&G1\"m0\"O1&e0&O1$m0$G4"
        "?3$m0^0m0$#P0$'01Q0X0)#$\"/\"#&-&\"g0$m0\"O1&e0&O1\"$&E1&g0m0&'$U0$G1\"m0\"O1&e0&O1$m0$G4"
        "G3$=2#$X0*`0!#!S0,\"W0\"$#&M0&$71$m0\"O1&e0&g1\"&51&g0#m0\"&M0&O1\"m0\"O1&e0&O1$m0$G4"
        "G3\"m1&\"#`0'#`0$o0\",#&]0&#O1$m0\"O1&e0&72\"&e0&g0\"m0&U0$O1\"m0\"O1&e0&O1$m0$G4"
        "G3#U1&K0!`0!'#`0'$M1.#$\"_1$m0\"O1&e0&O0$.#G1$e0&o0&M1\"O1\"m0\"O1&e0&O1$m0$G4"
        "?3$U0&'\"c0$#81!'#X0!'n0+,\"G2$m0\"O1&e0&/#U0&G1e0&o0#E1#W1\"m0\"O1&e0&O1$m0$G4"
        "?3&U0$K0N0K0,)`0!'!X0!'$_3$m0\"O1&e0&'$e0#?1e0#o0\"E1\"W1\"m0\"O1&e0&O1$m0$G4"
        "73#52N0#!P0!'#X0!'\"_3$m0\"O1&e0&'&e0#71#]0&?1#51&_1\"m0\"O1&e0&O1$m0$G4"
        "o2\"U2&+H0!'#X0!o3$m0$O1&e0&'#e0$o0\"e0#?1$51#_1$m0$O1m0&O1$m0$G4"
        "o2&e2&$H0'$X0!g3$&m0&G1#51,e0#g0#e0&G1\"m0&_1\"&m0&\"?1#51#?1\"&m0&\"?4"
        "g2#53&$($'`0\"O3\"&E1&\"o0&E1.m0V0m0&\"O1#e0#W1&M1$g0\"&M1$g0#M1&74"
        "g2&=3#! #'!X0#O3$U1#g0$U1.52&\"W1\"e0\"O1\"U1&g0$U1&g0&U1$o0J0_2"
        "g2&E3#('$X0!O3$U1&g0#U1&'#]1&$o1&U0&W1$U1&g0$U1&g0&U1#_0\"$#\"g2"
        "g2\".+,R0O0\"$M1$! $'!X0#G3\"S1$g0\"S1$/\"$.e0&#$?2#U0\"W1\"S1$g0\"S1$g0$S1\"O0#!#$73"
        "g4#E1+ !'\"`0\"?2$!\"_5\"L0\"_2#M0&O8$#)$G3"
        "73#&#O1\"- m0+(!'#`0\"g1\"! $79&M0#78\"!(!\"W3"
        "g2$U0&\"G1#=1+H0#'$`0#O1$! !\"'#&_8$U0\"_7$)(#\"g3"
        "g2&]0#O1&51$!P0$'$!X0!#$Z0$#!(#/&%&\"W8&M0#G7\"$#H0!#\"74"
        "_2\"e0&O1\"&m0$`0#/$h1$/$-&o7*W0\"U0$o6\"#!P0!$O4"
        "_2\"e0#W1&e0&#h0!$/$#!`0)#\"/$&-$g7$&-&\"/#M0&W6$#)P0!#\"_4"
        "g2e0#G1\"&m0$!81!$\"O0R0W0\"#&-&\"g7\"]0&'\"&M0$o5\",#!`0!#75"
        "g2&e0#o0\"#51#!X1!#,J0$#!U0&\"78$e0$&M0&_5\"#!01!#O5"
        "g2\"&m0f0=1#&%83!$G8#M1#75$#)81!#\"_5"
        "o2\"&M2&$\"&-@3!#$\"g7$E1&O4*$#!H1!#$76"
        "?3#=2#W0#M0P3!#\"W7&51&74\"#)X1&#\"O6"
        "O3$#&=1&#$o0\"#M0X3I0#\"77#]0&$G3\"$#I0`1&#$\"g6"
        "o3\",#,\"_1\"&M004)#,\"O6\"$+$W2*,+!@2.$G7"
        "g6#U0P4)#$\"o7\"$+)`2%&$g7"
        "77$#U0h4Y0+,*_4*,K0Y083%&#,?8"
        "G7\"#&M086Q0C1d0C1Y0H4.#\"_8"
        "g7$&U0P=M0&#$G9"
        "78\"$#&]08<M0.#$*_9"
        "W8\"$N0U00;-V0$\"O:"
        "?9\"$.e0@9]0.#\"G;"
        "_9*$+.51`6m0N0+,\"o;"
        "W:\"$+V0E18451f0#,\"o<"
        "g;*$K0N4K0$*O>"
        "7P"
        "7P"
        "7P"
        "7P"
        "7P"
        "7P"
        "7P"
        "7P"
        "7P"
        "W2*_0$\"71*_0\"o3T0\"72*74\"G1$#\"o7*O0*W0$W1\"o2"
        "W2(\"O0\" !71)W0$!g3$X0#o1+o3\" $71# !\"?2$#O2\"#o2)O0! \"/# W1!$g2"
        "W2(#O0$ !71)_0\"g3$ \"/# \"g1*o3\" $71)O2#!O2$ o2#!/\"(#/#!W1!$g2"
        "O2\"I0O0#)/\")#/)/#*$'L0!#O0\"#!\"$g0$!#\"g0$ \"O0 $'#O0$\"'\"#!$/,'$\"#!$O0\")\"O0#!#\"/$)\"_0\" $'#\"#!$'$)#\",!\"'#)\"/\"#!$/! #\"$\"!,\"/,/$!#\"'# #\"$\"/$\"'$\"!$'$!#\"_0\" /$I0/!$'\"#!$/\",!\"!$'$#O2"
        "O2\" $!\"'\"!#!'$ + !')')'$ '# !#)'\" !#! _0#!+!$_0$ \"/#!/ \"/!$\"!+ #')'! !# #'# +!$'#!#! \"$ + $W0\" \"' !+ $\"),(!$)#)\"'!+ #'! #\"(!#!#/)'# #! \"# #\"!$/!#'! !+!+!$_0!$'K0!'\" '\")#)'\" )$!$\" #O2"
        "O2\" \"!#'#!#!'+/#!')#!\"'$!'# \"'$ '#!/# W0\" $/)_0$X0#'\" \"/!, \"'$#'+')/)'!#/#!'!#'\"!\"#!/#$W0\" \"' #/)')'$ $'\"!\"/!,!/+'#!/ #/!#/)'!#/!$\"!/!$/!#')'\" $/)_0+'!$\" '#!')/$ * #/!#!#W2"
        "O2\" \")'!#$!O0\"#)'!($/$!'#!/\" \"!#O0!\"O0$ K0)\"L0'$ L0! \"' \"/!$\"(#\"/+'!#/#!' K0! '# !$/$ !#g0\" \"' $/)')'$!W0\"$# $'(#\"/#!/ \"/!#/#!' \"W0$!/!$/!#'!$'$ K0)_0#!\"!/!$#!')O0 $\" \"/!(\"W2"
        "O2\" \"$!\"!\"#!'$)#)'! )/$!'#!/\" \"!#O0!\"O0$ S0,! !\"$ \"O0)' \"/!$'\"#! #'+'!#/#!' [0/$! !\"'$!($W0\" \"' $/)')'$!/\"I0# #'\"#(#'#!/ \"/!#/#!' \"W0$!/!$/!#'!$'$ S0$_0$!#!/#)#'!#O0!#\" \"/I0#W2"
        "O2\" \"'!#!'#!' #/#!')' #'$!'#!/\" \")/\" \"O0$ \"/*_0$ \"O0)' \"/ $'$/# '+'!#/#!' $/*'$/\" #*/)W0\" \"' $/)')'$!/$ \"/!#*/# '#!/ \"/!#/)' $/L0!/!$/!#'!$'$ \"/*_0\" )/$)$')/\" $\" \"/!, \"O2"
        "O2\" \"'# #'#!' #'\")')'# '$!'#!/\" \"$ $\"! _0 !/ !_0$ $*# \"'!#'$ , \"'$ '+'!#/)')/)'!#'\" $#!/!#W0\" $' $/)')'$!/# \"'# #$ \"'#!'# / \"/)'\" !')'\" $\" \"')'$ #'!$/ !/ !g0! $/\" !/# \"'# * \"/!$')O2"
        "W2!\"'$ \"'#!'$I0#!')/!#$!'#!/\" \"'#)# _0\") !\"_0$P0!$/$ I0$'#I0$'+'!#/#!'\") !\"'\"I0#'\"Q0\"W0\" \"' $/)')'$!/\"! !#!#'# )$'\")\"!O0\"! I0'\") #/! *()#'!$/\") !\"g0# \"O0 #O0# )$'\" \"/!$'$ $G2"
        "o3\"$?1\"G1*/\"!o0*?1J0_0*_0\"$o1*_0$\"W0$\"G3*_0\"$W0\"$o0$\"_0$\"W0$O0$G1*W2\"$74"
        "_6# \"'!#_H"
        "_6\"Q0\"_H"
        "7P"
        "7P"
        "7P"
        "7P"
        "7P"
        "7P"
        "7P"
        "7P"
        "7P"
        "7P"
        "7P"
        "7P"
        "7P"
        "7P"
        "7P"
        "7P"
        "7P"
        "7P"
	"7P"
	"7P"))
    ((eq name built-in-gensym-logo-32)
     '#(32 12
	"74"
	"?1T0O2"
	"o0$\"#$_2"
	"'$*!$\" )\"!*$J0!#$*!J0!#O0"
	"'!*&! !$!.$&!&\"#&\"#\")$&+&O0"
	"'!*&(\"Q0'!*&*&\"'!\"'&,&O0"
	"'\".! !*$\"&'!&+&$&\"')'&+&O0"
	"'\"!&% !',\"!'\"!*#'!#'*$!+!#$'"
	"'!#\"&()#71*W0,*#$/"
	"'$*#!P0!*[0!J0I0\"#$W0"
	"g0$#\")`0Q0\"#$71"
	"W1\\0o1"))
    ((eq name built-in-gensym-logo-48)
     '#(48 18
	"76"
	"O2$W3"
	"g1$K0$_3"
	"W1#*#$o3"
	"W0$'#$/#)\"$O0,W0$71$/,/,g0"
	"/#&!.#$!(&! !.!.,)&\".#'&)&!.).!_0"
	"/&!'\"&\"H0!$' !.,%)&'\"#!%$'&#\"%\"'\"%\"'\"%#W0"
	"'$%\"'#%!(!/\" !&!/&!\"%&#'#%#$!'\"%$'#%#'#%#W0"
	"/.$!&H0*! &#&!/&!'\"-!'&!*'\"%#'#%#'#%#W0"
	"/#&!&!H0I0\"$'&!/&!#$'!&'\"%&$'\"%$'#%#'#%#W0"
	"'$&%N0! !_0$%&'$%.!#&!'$%!/!%#'\"%\"'\"%\"W0"
	"'$J0-&($/K0*'$*#\"!\"O0&#/*#'#\"#'#*#$/"
	"'#&/\"%&H0)&#W1+!G1#*#$O0"
	"'$I0&)X0\"#$O1.#W0$#\"I0\"#$_0"
	"O0$#$'$\"&`0)*k0R0I0(!\"#$71"
	"G1#\"!&82)\"#$W1"
	"g1$+:1+,G2"
	"76"))
    ((eq name built-in-gensym-logo-64)
     '#(64 24
	"78"
	"78"
	"o2L0g4"
	"O2$S0$o4"
	"?2#*#$G5"
	"o1#!\"#_5"
	"W0$*$)O0#! !*#$+$#\"#W0$*,#$#/L0+,*$/#\"#71"
	"O0\"%)-\"'#!H0N0 !&%N0%&#'\"%!&%\"-&/\"%)-N0%!N0%&$g0"
	"/$%&/!%$\"P0!#, !\"%!/#%&$%!'$&#\"%\"/#&,-$/&%\"/\"%!g0"
	"/\"%\"/\"%!P0!$/\" !\"%\"/$%&$%&#O0$%&/)'$%&O0!%#/#%&g0"
	"/#%\"/\"%!H0&$/\"(*%\"/$%&'!-&\"/&%#$&$'$%&O0&%#/#%&g0"
	"O0.#$.!H0!#\"!(!$\"%\"/$%&/\"&-!'\"%!\"&/$%&O0&%#/#%&g0"
	"O0#%N0!P0V0!\"/\"%\"/$%&'$/#%&'$%.#/$%&O0&%#/#%&g0"
	"O0.!&)H0!+,W0\"%\"/$%&\"%#/%!/!%&O0$%&O0&%#/#%&g0"
	"/\"e0!(!o0#&%&/\"-!.!.$/#%\"O0!-#'#-&$'!-#'$O0"
	"/+,#-&!(\"O0#\",K0/K0,*#W0$&$O0K0$'$K0/+*+O0"
	"/!&O0!%&P0I0 &#72$'\"&g1$J0#$W0"
	"/\"%\"#\"&%!h0!$72$%.#G1$\"I0\"#o0"
	"O0\"!.!$#&h0!\"#$g1\"&\"_0$#\")()#G1"
	"O1\"!@1I0J031*Q0X0!\"#_1"
	"_1$\"!&83&!\"#$?2"
	"?2$#*I0>1Q0*#,g2"
	"78"
	"78"))
    ((eq name built-in-gensym-logo-96)
     '#(96 36
	"7<"
	"7<"
	"7<"
	"W4T077"
	"?4$K0$G7"
	"g3#J0#$W7"
	"O3$\"!\"#$o7"
	"?3\")\"$G8"
	"g2$\" !\"_8"
	"?1$/#&#_0$!(!S0W2$g5"
	"g0\"V0!-&O0$!(Q0&(!#!.!#.%&!#W0#V0!$\"&)&\"/$&!&\"!N0#!&%.#'$!&%.\"O1"
	"_0&%&*&-\"#/\"(!(V0!H0\"U0&)&-\"/\"-*&%&#U0#/$&-*U0&)&-&-)&-!G1"
	"W0\"-$/$&%!'$!(!(.\"$'$!($!-\"O0$&-/&%\"/#%&'#-!W0$%\"/!-!W0&-&$O0&-#?1"
	"W0&%&W0!-#H0!(.$W0!(\"!-_0!-,-\"O0#$/&-$O0!%$/!-#W0\"-#W0\"-\"?1"
	"W0&%!W0\"-!(!H0&$W0#H0\"!-$W0!-#$M0\"$_0!-\"O0%!O0!-#W0\"-\"W0\"-\"?1"
	"W0&%!W0!-!X0&\"W0#H0&#!-$W0!-#'!U0&\"O0#-&/\"%#O0!-#W0\"-\"W0\"-\"?1"
	"W0!%&W0&%&! !H0!O0#!H0&!'&-$W0!-#'$!]0&$/&-$'.W0!-#W0\"-\"W0\"-\"?1"
	"W0$&%!,\"-\"(!H0Q0(N0\"/&-$W0!-#O0#!&M0\"/\"-\"$%\"W0!-#W0\"-\"W0\"-\"?1"
	"_0#]0&\"!81V0!#O0&-$W0!-#g0\"-&/$-&!%$W0!-#W0\"-\"W0\"-\"?1"
	"_0.#R0H0!H0Y0\"#g0!-$W0!-+&\"W0&%!O0&M0!_0!-#W0\"-\"W0\"-\"?1"
	"W0\"%f0) !H0#W1&-_0!-$!%&O0$&%#O0\"M0#_0!-#W0\"-#W0#-\"?1"
	"O0$=1&!P0#O1\"M0!O0#M0&\"-\"#\"&%!_0&%&_0\"M0&$/#&-&#/$&-&#71"
	"O0#.)\"!U0I0(\"o0,/^0$/\"V0+&M0&\"g0!%\"_0!V0#/\"V0\"/#V0\"'$+W0"
	"W0$_0&M0&!P0#_0\"!\"G2L071!%G3$#*#_0"
	"O0#%&$O0#&-&! !H0!*) ._3&!o2$\")\"#o0"
	"O0\"-_0!-\"P0)P0N0$?3\"!'#%#O2$#\"! !\"$?1"
	"O0$&%!+\"!-)@1&\"G3$-&%&72$#\"!H0!#W1"
	"W0$!]0&#'!%H1!\"#$o2!-&$G1$#*!P0&\"#o1"
	"o0$#,W0#!&X1)\"#,G2,W0,+\"I0`0!\"#G2"
	"?2$\"&@2I0j1Q0H1!\"#$_2"
	"W2$\"!&85&)\"$G3"
	"o2$#\")&`3&)\"#,g3"
	"_3$+*Q0F1Y0*+,_4"
	"7<"
	"7<"
	"7<"))
    ((eq name built-in-gensym-logo-128)
     '#(128 48
	"7@"
	"7@"
	"7@"
	"7@"
	"G6T0G9"
	"g5,K0$W9"
	"O5$#J0,g9"
	"75$\")\"$G:"
	"_4$\")\"#_:"
	"G4$\"! !\"7;"
	"74$!(!#G;"
	"g3#!(!$W;"
	"72$*$71#!(!$',O;"
	"?1#\")\"#$&-!g0\"!(Y0H0!\"'$+*#'#\")*$71#\")\"#/k0W0$S0$K0*$'#\")\"#$W0#\")\"#72"
	"o0#&e0&M0!W0#!()H0V0H0*U0.m0\"_0#&e0&$&e0$O0\"U0)U0!&e0&\"$\"&e0&\"g1"
	"g0#M0\",\"M0\"#O0$!H0!H0!-N0!H0*]0&J0&M0!O0#-&#,!-\"#&U0\"W0$!-&#$!]0&J0&M0&-&J0&M0\"_1"
	"g0&-!W0\"-&$/#H0)H0&%!$O0#H0!'&M0\"_0&M0#/&-#O0#-!'$M0&g0$-$O0U0\"W0$&M0&#W0$M0&_1"
	"_0#M0$_0&-!'!H0)H0.#_0$H0!$&-&g0#M0\"'$M0_0\"!$/&M0$_0!%\"O0$M0!g0\"M0\"g0!M0#W1"
	"_0\"-&g0&-&\"H0)H0!&#g0\"H0!$&-&g0$M0!'#M0\"?1\"M0\"_0&%$O0$M0!g0#M0\"g0\"M0#W1"
	"_0!-&g0!-&\"H0!H0!&#g0$P0!$&-&g0$M0!'$U0!#o0$&-&W0#%&W0$M0!g0#M0\"g0\"M0#W1"
	"_0!-&g0&-&\"(!P0&!g0$!H0&!'&-&g0$M0!/!]0&!#_0!M0#O0&%#W0$M0!g0#M0\"g0\"M0#W1"
	"_0\"M0$_0&-)(!H0!&$_0#P0!&#'&-&g0$M0!/$&m0!$O0#M0!/$%&_0$M0!g0#M0\"g0\"M0#W1"
	"_0$&-\"W0#M0\"(!P0!\"O0$\"!H0!&%\"/&-&g0$M0!W0\"m0&W0&-&/\"%\"_0$M0!g0#M0\"g0\"M0#W1"
	"g0#M0\"$'#&-*(!P0Q0P0)&%&#O0&-&g0$M0!_0$\"!]0\"O0\"M0#'&%$_0$M0!g0#M0\"g0\"M0#W1"
	"o0\"51*H0!P0!(f0%&\"_0&-&g0$M0!71$!M0!O0$M0!#%&g0$M0!g0#M0\"g0\"M0#W1"
	"o0!%&!N0!\"!P0!H0!]0N0\"#o0&-&g0$M0!/+g0&-!W0&-.%#g0$M0!g0#M0\"g0\"M0#W1"
	"g0#%&,K0\"!X0!H0!\"K0,O1&-&g0$M0!'!-#_0!-\"W0\"U0&o0$M0!g0#M0\"g0\"M0#W1"
	"_0$&51&*H0!H0!?2&-&g0$M0!'&-\"W0$&-$W0$U0\"71M0!g0#M0\"g0\"M0#W1"
	"_0\"M1&\"! !H0!o1$\"U0#_0!M0&#!-!L0\"&-#g0!M0$g0$!M0&#W0$&M0&#W0$&M0&#O1"
	"W0$e1\" !H0!o1\"e0$O0\"e0#!m0&#o0#-!o0&]0&W0!e0$O0&]0&W0,_0"
	"_0*+T0!]0)X0#?1#\"O0#b0W0#b0$'#\"N0!#G1&%#o0#Z0#W0#b0$O0#Z0#'$#\"#$_0"
	"_1#% M0&! !P0#g0$\" !$g4$%&W4#)#$o0"
	"W0$&%&g0!U0)(!P0!S0!(!&\"g4\"%\"74$#! !#G1"
	"W0#M0$g0&M0\"!H0)01!&%!$G4#$/&%$_3#\"!(!#W1"
	"W0#-&g0$&-&\"`0i0&%&\"O4!%&'#%!?3$#\"!H0!\"$g1"
	"_0!-&\"+\"!M0&\"`1%!W4$M0&-$_2$#\"!P0&\"$?2"
	"g0\"&m0&\"'#&%`1)\"$?4!U0\"72$#*)X0!\"#W2"
	"71#*!*#_0\"&%02)\"#$_3\"!\"$O1$+\")01!\"#o2"
	"_2$\"&-H2)*#,G3,+*I0H1)#$G3"
	"73#!&%83Y0Z1a082)\"$g3"
	"O3#\"&-87&!\"#$G4"
	"g3$#\"!&-X5.!*#$o4"
	"O4$#\"!N0-h3.)\"+$_5"
	"?5,+J0I0.i1J0+,_6"
	"7@"
	"7@"
	"7@"
	"7@"))
    ((eq name built-in-gensym-logo-160)
     '#(160 60
	"7D"
	"7D"
	"7D"
	"7D"
	"7D"
	"78L0_;"
	"W7$S0$g;"
	"?7#J0#$?<"
	"_6$#\"!\"#$W<"
	"G6$\"I0\"$o<"
	"o5$\"! !\"$G="
	"W5$#!(!#_="
	"G5#!(!\"$o="
	"o4$\"!(!#G>"
	"_4$\"H0!#W>"
	"_2#\"#O1$!H0!#g>"
	"_1$+,/\"M0\"71$!H0!\"#\") I0#_1$+,_1$+,O4,+$?1$+,_2"
	"G1#!&]0&\"U0&g0$!H0I0H0I0P0!+f0$#!&]0&\"71$!&]0&\"/!n0\"_0!^0*^0!$\"&]0&!#O0#!&]0&\"O2"
	"?1\"U0.]0.%#_0\"P0)H0)&-&!P0\"e0&E1&$_0#U0N0M0!'&m0!_0&]0\"!]0.E1\"$!E1&#?2"
	"71\"M0&#/$!M0&'$W0#!H0)H0)-&)&)H0!$!e0&\"+\"!U0&$O0$M0&#O0!M0#$&]0\"$_0$!M0!$'#&e0!\"+\"&m0&\"K0!]0$72"
	"o0#U0$_0!M0\"W0\"P0)H0!&%&#W0$!H0!'$]0\"g0\"U0\"O0!M0$W0\"M0\"'$&M0&71$-!W0!U0&#_0$&]0\"g0\"U0!72"
	"o0&M0!g0#U0$'$!P0!P0!&%\"o0!P0#$U0\"71&M0&/$M0&_0$&%&$/!U0#o0\"-$W0!U0$o0\"U0!71&M0&72"
	"g0$U0#o0&M0\"#X0!P0!&%#71!H0!\"$U0\"71&M0&/#M0&o0$W0#U0!o0&%!_0!M0&71$U0\"71!U0$o1"
	"g0#U0$o0&M0!\"P0)P0!%#71#P0!\"'U0\"71!M0&/#U0\"W1&M0&g0#-#_0!M0&71$U0\"71\"U0$o1"
	"g0#U0$o0&M0!\"H0)P0!%\"71$!P0&\"'U0\"71!M0&/$]0&\"#?1\"U0#_0&%&g0!M0&71$U0\"71\"U0$o1"
	"g0#U0$o0&M0!\"H0!P0!.?1!P0!&,U0\"71!M0&O0!m0&\"$g0$U0!W0$-\"g0!M0&71$U0\"71\"U0$o1"
	"g0$U0#o0&M0\"!()P0!&$o0$!P0!%!'$U0\"71!M0&O0$&=1!$_0!U0$O0\"-$g0!M0&71$U0\"71\"U0$o1"
	"o0&M0!g0#U0#H0!X0&!g0$!X0!%&$'$U0\"71!M0&W0$&=1&#W0#U0\"O0&%!o0!M0&71$U0\"71\"U0$o1"
	"o0#U0$_0&M0*()P0)$/$#\"!X0!&%&$/$U0\"71!M0&g0#&51&_0&M0&/#-#o0!M0&71$U0\"71\"U0$o1"
	"71\"M0&#/$!M0&$H0!`0I0h0)&-!$O0$U0\"71!M0&71$\"&e0#W0!U0$'!%&71!M0&71$U0\"71\"U0$o1"
	"?1\"U0.U0!$!H0!81a0&M0!#_0$U0\"71!M0&O1#&U0\"W0#U0\"'-\"71!M0&71$U0\"71\"U0$o1"
	"?1\"-&]0&\"#X0!X0!V0e0&\"$o0$U0\"71!M0&W1$&M0!_0&M0&\"%&?1!M0&71$U0\"71\"U0$o1"
	"71#-!'$K0*!`0!P0!^0)*$O1$U0\"71!M0&/#.#o0!M0\"_0\"U0&%!?1!M0&71$U0\"71\"U0$o1"
	"71&%&+j0!X0!P0!\"W2$U0\"71!M0&/&M0$g0!M0#_0$e0#?1!M0&71$U0\"71\"U0$o1"
	"o0\"M1&!#\"H0!P0!#W2$U0\"71!M0&'$M0&g0$M0&o0&U0&G1!M0&71$U0\"71\"U0$o1"
	"g0#m1\"#(!P0!$O2$!U0&$g0#&U0\"$&-&#O0$#&-&$o0\"U0\"?1#&U0\"o0\"U0&#g0$&U0!$g1"
	"g0&52!\" !X0$G2#m0&$W0#m0&#&M0N0U0&$71$M0&$71\"m0\"_0!m0\"W0$51#_0,g0"
	"g0&%.I0J0&m0#(!P0\"G2#61$W0\"61,!&e0&\"O1!-!?1!n0!_0!n0!W0#61#O0#\"#$g0"
	"o0$71$m0\"! !X0$O1#!#g3#J0#$_1\"-$g5$\"!\"#71"
	"o0,71!% U0!\"(!X0#71#!(\"?6!%&_5#I0#G1"
	"g0\"-!o0$&]0!\"()X0!#L0#\"!(!&%#o5$-#?5$\"!(!$W1"
	"_0$U0$o0#]0\"!P0)H1)&%!$o5\"%&o4#\"!(!\"$g1"
	"_0$U0?1&M0&#`0I0h0)&%&\"O5#.#/&%\"O4$\"!P0!#?2"
	"g0&-&$g0$!U0#!01i0.-!$W5&-&'\"-$o3$\")P0!\"$O2"
	"g0#U0!\"+\"!&U0\"!@2&#_5$U0&-!O3$#\"!`0&\"#g2"
	"o0#&M1!$'!-@2!\"#$G5&]0&o2$#\")h0&!#?3"
	"?1#\"!^0!\"$W0#&-P2!\"#$g4$!N0\"G2$#\")@1!\"#W3"
	"G3#&-`2)*#,g5,+*)P1&!\"$o3"
	"W3$\"&-@3I0*+L0?3,K0*I082&!\"$O4"
	"o3#!&-@4a283&!\"$o4"
	"G4#\"&M009&!\"#$O5"
	"_4$\"!&U0X7.!\"#$76"
	"?5$#\"!.U0h5%N0!\"#,_6"
	"o5$#*!N0e083U0N0)*#,W7"
	"g6,+J0a2J0+L0_8"
	"7D"
	"7D"
	"7D"
	"7D"
	"7D"))
    ((eq name built-in-gensym-logo-192)
     '#(192 71
	"7H"
	"7H"
	"7H"
	"7H"
	"7H"
	"7H"
	"g9L0o="
	"?9,S0$7>"
	"g8$#*#,O>"
	"G8$#\")\"$o>"
	"o7$\"I0#$G?"
	"W7#\"! !\"$_?"
	"?7$\"(!\"$7@"
	"g6$\"H0!#O@"
	"O6$\"!H0\"$_@"
	"?6#!H0!#7A"
	"o5\"!H0!#GA"
	"W5$\"P0!#WA"
	"?3#)#_1$!P0!#gA"
	"72T0W0#U0#G1#!P0!+\"i0\"$72T0G2T0W5T0_1L0O3"
	"_1#!&U0.\"$&U0!71$!P0!\"!P1!$'\"I0N0!'$\".U0&!\"O1$\".U0&!#/$\"11\"$_0$\"a0+I0V0$'#!&U0.\"$_0$\".M0.!#o2"
	"O1#&52\"g0$\"P0I0H0I0N0)P0!$&e0&\"M1&\"71\"&E1!,E1$_0#m0)m0\"&M1!$'#&M1&#_2"
	"G1#]0!+\"&U0&#!\"g0#X0\"!P0)e0&!P0!#&E1V0e0!g0\"U0&\"+\"U0!'!51!o0&]0&#$&E1V0e0&!]0N0m0#W2"
	"?1#U0&$_0!U0\"g0$!P0)P0!\"&-!S0)X0#'\"m0\"$W0#&]0\"W0#U0\"_0!M0&/\"e0#?1#M0!W0#m0!#W0$!51&#$O0$\"]0&$O2"
	"?1&U0#o0&U0$W0\"X0)P0)-\"$g0#X0\"'#]0&$o0$&U0&W0&M0&g0!M0&O0!]0$?1#-&_0$e0#71!e0\"71\"]0\"O2"
	"71#U0&71\"U0!/$!X0)P0)%&#71$X0!'#]0#?1\"]0$/$U0!g0$&%&#O0$]0\"?1!-\"_0$]0\"?1$]0&G1&U0!O2"
	"71\"U0\"71#]0$#`0)X0!%&$?1\"X0!$#]0$?1#]0#/#U0!71$g0&U0&71$&%&$_0$]0\"G1&U0!G1&U0&O2"
	"71&U0#71$]0#!X0)X0\"%&$G1!P0)$#]0$?1#]0#/#U0&$g1\"]0#o0\"-!g0$]0\"G1&U0!G1!U0&O2"
	"71&U0#?1&U0#!X0\"X0!&%$G1#X0!&'#]0$?1$]0#/$]0&\"$W1$]0!o0&-#g0$]0\"G1&U0!G1!U0&O2"
	"71&U0#?1&U0#!P0\"`0!%#G1$X0)&'#]0$?1$]0\"O0&m0&#$G1!U0&g0#-&o0$]0\"G1&U0!G1!U0&O2"
	"71&U0\"71$]0#!H0)X0!.G1$!X0!%\"'#]0$?1$]0\"O0\"E1!#71#]0#_0!-\"o0$]0\"G1&U0!G1!U0&O2"
	"71\"U0\"71#]0$P0\"`0!%$?1\"`0\"%&/#]0$?1$]0\"W0!M1&#o0&U0!W0$-&71$]0\"G1&U0!G1!U0&O2"
	"71#U0&71\"U0&#H0)X0!&\"71#!X0)-#/#]0$?1$]0\"_0\"U1\"g0!]0$O0\"-\"71$]0\"G1&U0!G1!U0&O2"
	"?1&U0#g0$&U0#!H0!`0\"&$_0#\"!X0!\"&-#O0#]0$?1$]0\"g0$!M1\"_0#]0\"O0&-#71$]0\"G1&U0!G1!U0&O2"
	"?1#U0&#_0!U0\"$P0!`0)J0)h0I0-&#W0#]0$?1$]0\"71$\"&51&g0&U0&/#-&?1$]0\"G1&U0!G1!U0&O2"
	"G1#]0!\"#\"&U0!'!H0)02Q0&M0\"g0#]0$?1$]0\"O1$\"&e0#_0\"]0$'!-#?1$]0\"G1&U0!G1!U0&O2"
	"O1\"M1&#$!P0!`091N0U0&\"$o0#]0$?1$]0\"g1!]0\"_0$]0\"'-&G1$]0\"G1&U0!G1!U0&O2"
	"O1&-.]0&\"$\"`0!`0!M1&!\"$G1#]0$?1$]0\"o1&U0\"g0&U0&\"-\"G1$]0\"G1&U0!G1!U0&O2"
	"G1\"-&/$K0*!01!`0!V0I0*#$g1#]0$?1$]0\"/\".!$71\"U0#g0\"]0&-$G1$]0\"G1&U0!G1!U0&O2"
	"?1$M0,31\"!`0!`0!#73#]0$?1$]0\"'$U0!71\"U0$g0$&e0!O1$]0\"G1&U0!G1!U0&O2"
	"?1&M0&51&!\"#\"P0!`0\"$73\"]0$?1#]0\"'\"U0!71&M0!71!e0#O1$]0\"G1&U0!G1!U0&O2"
	"71\"52&\"$H0!`0#$73\"]0#?1#]0\"'#U0\"o0!M0&$71#]0&W1#]0\"?1$]0&G1&]0$G2"
	"o0$&E2!#()X0\"o2$!e0&#o0\"m0!$!M0&\"#,#\"&U0#G1&U0\"O1\"m0\"o0#&e0&#g0$!e0&\"?2"
	"o0\"U2\"#(!X0!o2&=1$_0$=1&'!U1&$O1\"U0$G1!=1#g0&=1#_0!=1\"o0,o0"
	"o0\"-.!j0=1$(!`0$g2!>1$_0#F1/#&51!#_1$M0!O1\">1#g0F1#_0!>1\"W0$*$71"
	"71,G1&% e0\"! )X0!g1$!\"W4$#R0#$72&-#?7#)#G1"
	"W2#%(]0*()X0!O1$\"(!O7$-&o6#I0#W1"
	"71\"&!#?1!% ]0*H0\"`0!#o0#\"H0!&!G7\"-\"O6$#!(!#g1"
	"o0!M0&$71$&e0\"!P0\"!`0)J0!P0!\"&%&G7&%&?6$\"!H0\"$72"
	"o0&U0$?1#e0$!X0I0P1I0-!_6$W0#-!_5$#\"!H0!\"O2"
	"o0&M0&O1&U0\"#01!\")`0I0&-&#W6#&%&$/!-#?5$#\"!X0\"$_2"
	"o0\"M0&$71#&U0&$!@111.-&\"g6&M0!'#-&g4$#\"!`0!#73"
	"71&U0!\"#,#\"&]0&$&`2\"o6$]0!M0#G4#\")h0!\"$G3"
	"71$!m1\"'#-`2!\"#$W6&m0\"_3$#*!81!\"$_3"
	"G1#!&=1&\"$O0$!-03!\"#?6$&U0&#?3$#\")H1!\"$74"
	"_1#b0#$71#&-@3!*#$_5\")\"$G2,#*)X1&!#$O4"
	"74$!M0P3)*#$g6,+\"I002&!\"$o4"
	"G4$\"&M004I0*K0,o3L0+J0Q0P2&!\"#O5"
	"_4#\"&M085i0R111`3&!\"#o5"
	"75#\"&U00;%&!\"#$O6"
	"O5$#!&U0`9-&!\"#$77"
	"o5$#\"!&]008M0.!*#$_7"
	"W6$#\"!.e086U0N0!\"#,O8"
	"G7$+*!N0M1H2=1V0)*+$O9"
	"O8,+J0I061Q0f0Q0J0K0,_:"
	"7H"
	"7H"
	"7H"
	"7H"
	"7H"
	"7H"))
    ((eq name built-in-gensym-logo-224)
     '#(224 83
	"7L"
	"7L"
	"7L"
	"7L"
	"7L"
	"7L"
	"7L"
	"W;,G@"
	"o:,K0$O@"
	"W:$J0#,_@"
	"7:$R0#$?A"
	"_9#\"I0#_A"
	"?9$\"! !\"#7B"
	"g8#\"!(!#OB"
	"O8$\"!(!#gB"
	"78$\"!H0\"$7C"
	"g7\"!H0!#OC"
	"O7#!P0\"$_C"
	"77$\"!P0\"$oC"
	"g6$!P0!#GD"
	"W6#!P0!\"WD"
	"g3J0$72#!X0\"gD"
	"W3$&M0&$_1\"`0\"/#\"Y0\"#$WC"
	"72$#)N0!\"#/!]0\"O1\"!X0J0!H1!$O0L0K0*$O0#\").)\"$o1$#).)\"$_0L1?141/L0K0*$O0#\").)\"$?1$\"!N0!\"#$W3"
	"g1#!E1&!e0\"?1#!P0!*!P0a0`0\"'\"51\"'\"&E1&#O1$!&=1&\"/#M1!o0!51*51\"'\"&E1&#W0$\"&E1&#G3"
	"_1\"52&-&$o0$!X0*X0!\"!&M0&\"`0*51.e1!$71\"e1!'#M1!o0!51*51.e1!$'\"m1!$73"
	"W1!]0!#L0\"e0#$\"$g0$!X0!\"!P0!\"&51\"`0+&M1&!*!m0&$g0\"]0!#L0#&U0\"'\"=1&$o0$!e0!$'\"&M1&!*!m0.]0&!*!m0&$o2"
	"O1\"]0\"g0$&U0&71\"`0\"!X0)M0&\"#,#!\"!X0!/!m0&\"$_0$!e0!_0$]0#g0&U0!/#&e0#O1#U0#_0!m0&\"$_0$!=1&\"$_0$!e0!o2"
	"G1#]0!71#]0\"_0$!`0\"!X0\"!-&$71!X0!/\"e0&$?1!e0$W0!U0!o0!U0!O0\"e0#O1#M0\"g0!e0&$?1!m0&$?1!e0$g2"
	"G1!]0$?1&]0$O0#h0\"`0\"&-#G1!X0!#'\"e0$G1$e0#W0&U0#o0$&-&$O0$&]0!O1!-&o0!]0&$G1$e0&$G1#e0\"g2"
	"?1$]0&G1\"]0\"/\"h0\"`0)%&#O1!X0!\"'\"]0&W1&]0\"O0#]0#71$*$_0!e0$?1$&-!o0!]0&W1&]0&W1&]0\"g2"
	"?1#]0!G1#]0&'!h0\"!X0!\"%&$O1$`0)'\"]0&W1!]0!O0#]0\"?2#e0\"?1\"M0#o0!]0&W1&]0&W1&]0!g2"
	"?1\"]0!G1$]0&$!`0\"!`0\"-$W1\"`0)'\"]0&W1!]0!O0#e0#?2&]0&?1&-&71!]0&W1!]0&W1&]0!g2"
	"?1\"]0\"G1$e0$!X0)`0!&%#W1$`0!&\"'\"]0&W1!]0!O0$m0!#o1\"e0$o0#M0#71!]0&W1&]0&W1&]0&g2"
	"?1\"]0\"G1$e0$!X0\"`0!\"%\"W1$!`0\"%#'\"]0&W1!]0!W0&51&\"#W1#e0\"o0!-&?1!]0&W1&]0&W1&]0&g2"
	"?1\"]0!G1#]0&$!P0\"h0\"%&W1$!`0\"%&/\"]0&W1!]0!W0\"M1&\"$G1&]0&g0$&-\"?1!]0&W1&]0&W1&]0&g2"
	"?1#]0!G1\"]0&'P0)`0)%#O1#h0\"&%\"/\"]0&W1!]0!_0!]1&#71\"e0#_0\"M0$?1!]0&W1&]0&W1&]0&g2"
	"G1&U0&G1!]0\"#P0\"h0\".G1$\"h0\"&%&O0\"]0&W1!]0!g0!e1\"o0$e0\"_0&-!G1!]0&W1&]0&W1&]0&g2"
	"G1!]0#?1&]0$!P0\"h0!%#71#\"h0!\"&%&$O0\"]0&W1!]0!o0\"&]1!o0!]0&W0#M0#G1!]0&W1&]0&W1&]0&g2"
	"G1$&U0&71\"]0\"$P0)`0I0_0$#\"!h0!\"!-&$W0\"]0&W1!]0!?1\"&U1\"g0#e0#O0!-&O1!]0&W1&]0&W1&]0&g2"
	"O1#]0&g0\"]0&'!P0\"h0i081!*&M0!g0\"]0&W1!]0!O1#\"&=1&o0&]0!/$M0\"O1!]0&W1&]0&W1&]0&g2"
	"W1\"]0&*#\"&]0&$\"X0\"@2a0&M0&#o0\"]0&W1!]0!g1#!51$g0\"]0&$'\"M0$O1!]0&W1&]0&W1&]0&g2"
	"_1#e1!'#X0)h091*!.]0!#?1\"]0&W1!]0!72$&e0#g0$e0\"'&-!W1!]0&W1&]0&W1&]0&g2"
	"_1!U1!$'!`0)`0)f051&!#$O1\"]0&W1!]0!?2$&]0#o0&]0&$M0#W1!]0&W1&]0&W1&]0&g2"
	"W1\"M0\"$\"Q0*+!01)`0!=1.!*#o1\"]0&W1!]0!O0$J0$G1\"]0#o0\"e0&-&_1!]0&W1&]0&W1&]0&g2"
	"O1$&-!o0#\"!@1)`0!&[0,g2\"]0&W1!]0!O0&M0&G1#]0$o0$=1#_1!]0&W1&]0&W1&]0&g2"
	"O1!M0+21#,\"!`0)`0!\"_3\"]0&W1!]0!/\"]0#?1\"U0!?1!m0&$_1!]0&W1&]0&W1&]0&g2"
	"G1#52&\",!P0)`0!#_3!]0&W1!]0!/\"]0#?1&U0#?1#m0!g1!]0&W1&]0&W1&]0&g2"
	"?1$&M2!$\"H0)`0!#_3&]0&W1&]0&/\"]0$o0$!U0!O1&e0$g1&]0&W1&]0&W1&]0&g2"
	"?1\"]2&$\"H0!`0!$O3$!m0!$71$!m0&#$&U0!#W0$\"&U0&W1\"]0&_1#!m0!$71$!m0!#71$!m0!#W2"
	"71$m2&$!(\"h0O3#E1&71&E1\"$&]0V0e0!_1$]0\"W1#E1&71&E1\"o0&E1\"?1,71"
	"71\"m0n0E1!$(\"!`0#G3\"M1$g0$M1&'$!U1&#o1&M0&_1\"M1$g0$M1&g0#M1&o0K0$71"
	"71$!&!\"#,o0!E1$!(\"`0!G2$#g0#J1$o0R1O0$\".U0.!#?2\"M0\"_1#J1o0$J1#g0$J1#W0$\"!\"$G1"
	"o2#- m0#\"(\"!`0\"72#(#W5T0_2#M0$G8#)\"$W1"
	"73&%(e0*H0\"h0\"_1$!H0#_8!-&78#!(\"$g1"
	"?1#!&!$G1#- e0*H0!\"h0!#?1#!H0!\"&#O8$&-#W7$#!(!\"$72"
	"71#U0&O1\"51#\"P0!\"01!\"S0\"!X0\"!-\"O8\"-&G7$\"!H0!#O2"
	"71!]0#O1!m0$!`0\"!82*&-\"W8&-\"o6#)P0\"$_2"
	"71&]0$O1$&]0!$01!\")H1I0&-&#_7#!\"$O0#-&$G6$#\"!X0!\"$o2"
	"71!U0&W1\"e0$!@1!*11*!&M0\"g7\"M0&$/!-!76#\"!h0!$G3"
	"71#]0#?1$!e0+h1i0]0!$o7&U0\"'#M0#O5$#\"!01!\"_3"
	"?1\"]0&\"+,#\"&m0+%83!$78$e0&M0!75$\")81!\"$o3"
	"G1#&=2!$'!-@3!\"$g7&51&$G4$#*!H1!\"$G4"
	"O1$\"&U1&!#W0\"&-H3)#$G7#&e0&$g3$#\")X1!\"$_4"
	"g1$\")^0!\"#?1\"&-`3!\"#$g6$\"N0!#G3$#\")h1&!#$75"
	"W4$\"&M0h3)*#$79,#*I082&!\"#W5"
	"o4#&M0H4)*+$77,+*I0`2&!#76"
	"?5$\"&M005Q0*+L0o3L0+J0Q0@3%.\"#$O6"
	"W5#!&M0@6I3P4%.\"#$o6"
	"g5$#!&U0h<-.!\"#$O7"
	"G6$\".U0`;-.!\"#?8"
	"g6$\"!&e00:]0&!\"#$g8"
	"G7$#\"!.e0H8U0N0!\"+$O9"
	"78$#\"!.5106m0N0)\"#$O:"
	"g8,+*!N0E5V0!J0+,G;"
	"7:,K0R0i2Z0K0L0_<"
	"7L"
	"7L"
	"7L"
	"7L"
	"7L"
	"7L"
	"7L"))
    ((eq name built-in-gensym-logo-256)
     '#(256 95
	"7P"
	"7P"
	"7P"
	"7P"
	"7P"
	"7P"
	"7P"
	"7P"
	"?=L0WB"
	"_<,K0$_B"
	"?<$+*#,oB"
	"g;#\")\"#$OC"
	"G;$\"I0\"#oC"
	"g:$#\"I0\"#GD"
	"O:$\"!(!\"$_D"
	"7:$\"!H0\"$7E"
	"_9$\"!H0\"#OE"
	"G9$\"!H0!#gE"
	"o8$\"!P0\"$7F"
	"_8#!P0!#OF"
	"G8$\"!P0!#_F"
	"78#!X0!#oF"
	"_7$\"!X0\"$?G"
	"O7$\"`0!$OG"
	"G4$*#O2#!`0!$_G"
	"?4\"U0\"72#!`0!$/$+J0+$WF"
	"_2$[0$W0#e0#_1$!`0!\"$\"!@1!\"$W2$[0$g2$[0$G7$[0$g1,S0,G4"
	"?2$\".m0.\"$&e0\"O1$!`0!\")`0)01!$'$!>1$'$\".m0.\"$o1#!&m0.\"$O0#&Q1$71A1+61%!/#!.m0.\"$o0#!&51&!#o3"
	"72\"e2#?1$\"`0!#!`0R0!*!h0,E1$\"m1!$O1#&e1\"/\"]1$71&=1#\"=1&$!e1&\"W0#&e1&#_3"
	"g1#&e0V051.-!?1\"`0!\"!X0!*&e0*`0!$&=1&=2&#?1#m0V0e0\"'\"]1$71&=1+U3&,!E2\"W3"
	"_1$e0&#W0$!e0!',71#!`0*`0*&]0.-)`0\"'#&U1!\"+*&51#o0\"]0&\"_0$&]0$'\"&=1&#?1$!e0&\"/$\"&M1&!\"+\"!m1&*+\"&51!O3"
	"_1&]0&$o0\"e0#?1\"h0#!`0\"!M0&\"#$/$\"&\"h0O0&=1\"$o0\"m0&g0$]0&$o0&]0#/$&m0\"_1#U0!g0#=1&#o0$!M1&#o0#&m0#G3"
	"W1!e0#?1&]0&o0#!`0!\"!`0\"&-&\"71$#h0$/&m0&$G1\"m0\"_0\"]0\"71&]0#O0#m0\"_1#M0&$g0$51!$G1!=1\"G1#m0&G3"
	"O1$e0!G1#e0\"_0\"h0!\"h0#&-\"O1$h0#/&e0&_1&e0!_0&]0$71\"U0&_0&e0&_1!M0\"o0$m0\"W1$51#W1\"m0$?3"
	"O1\"e0#O1&e0$/$!h0!\"h0#&-\"W1#h0!#'&e0\"_1\"e0&W0$e0$?1\".!$_0\"m0#O1$&M0$o0$m0$_1&e0&_1$m0#?3"
	"O1!]0&W1!e0#'\"01!\"h0\"&%&#_1\"`0)#'&e0\"_1#m0$O0#e0$O2$m0!O1\"M0!71$m0$_1!e0&g1&e0\"?3"
	"O1&]0&W1\"e0\"'01!\"h0!\"-#g1!`0!&#'&e0\"_1#m0$O0#e0\"W2&e0&O1!M0#71$m0$_1!e0&g1&e0\"?3"
	"G1$e0!W1#e0!'01#01\"-#g1#h0\"&$'&e0\"_1#m0$O0#m0\"O2\"m0#?1$M0&?1$m0$_1!e0&g1&e0\"?3"
	"G1$e0!W1#e0&'!`0\"!h0\"&%\"o1!`0)&/&e0\"_1#m0$O0$51&\"$?2&e0!?1!M0\"?1$m0$_1!e0&g1&e0\"?3"
	"G1$e0!W1#e0&'!X0!\"h0)%&o1!h0#%!/&e0\"_1#m0$W0&E1!#o1!e0&?1&M0$?1$m0$_1!e0&g1&e0\"?3"
	"G1$&]0&W1\"e0!'`0\"01\"-$g1!h0\"&%#/&e0\"_1#m0$W0\"U1&!#$O1#m0#o0\"M0!G1$m0$_1!e0&g1&e0\"?3"
	"O1&]0&W1\"e0\"'X0\"!h0)%\"_1$!h0*%&O0&e0\"_1#m0$_0!m1!$G1&e0!o0&M0#G1$m0$_1!e0&g1&e0\"?3"
	"O1!e0$O1!e0+X0\"01\"%&_1#01*-#O0&e0\"_1#m0$g0&52\"?1\"m0$_0#M0&O1$m0$_1!e0&g1&e0\"?3"
	"O1#e0\"G1$&]0&'!P0)h0!\"%#O1#!h0!\"&-\"W0&e0\"_1#m0$o0\"52&71$m0\"_0\"M0#O1$m0$_1!e0&g1&e0\"?3"
	"W1&]0&G1\"e0\"$X0\"01\".?1$\"!01*&-!_0&e0\"_1#m0$71#&m1!71&e0&_0&-&W1$m0$_1!e0&g1&e0\"?3"
	"W1#e0\"71$&]0&'\"X0!01#&\"W0,#\"!81!\"&M0!g0&e0\"_1#m0$G1#!e1#o0\"m0$O0#M0!W1$m0$_1!e0&g1&e0\"?3"
	"_1\"e0\"g0$&e0,X0)01a0H1)\"!&M0&#o0&e0\"_1#m0$W1$#!&E1&71&e0\"O0&M0#W1$m0$_1!e0&g1&e0\"?3"
	"g1!e0&\"+\"!m0#'!X0\"!X2)J0&]0\"$71&e0\"_1#m0$72\"&=1$o0!e0&/#M0&_1$m0$_1!e0&g1&e0\"?3"
	"o1\"52&$'!`0\"81A1J0)&]0&\"$G1&e0\"_1#m0$G2\"51$o0#m0$'!M0#_1$m0$_1!e0&g1&e0\"?3"
	"o1!e1&#'#01\"01\"Y0V0=1&!#_1&e0\"_1#m0$O2#m0#71&e0\"'&-&g1$m0$_1!e0&g1&e0\"?3"
	"g1#U0\"!&U0.!#'$!81\"h0!\"e1&!\"$72&e0\"_1#m0$W2\"e0$71\"e0&#M0\"g1$m0$_1!e0&g1&e0\"?3"
	"g1&M0\"O0T0K0\"!@1!\"h0)%n0)*#$W2&e0\"_1#m0$O0#N0!$O1#e0$71#m0&M0$g1$m0$_1!e0&g1&e0\"?3"
	"_1\"M0!71$+\")81!\"h0!&#?4&e0\"_1#m0$/#]0!O1#]0&G1&=1!o1$m0$_1!e0&g1&e0\"?3"
	"W1#U0*!n0!*$'$\"!`0!\"h0)$?4&e0\"_1#m0$/&]0&O1\"]0\"G1\"=1#o1$m0$_1!e0&g1&e0\"?3"
	"W1&E2.\"'#!P0!\"h0!\"$?4&e0\"_1#m0$/&]0&G1$&U0&W1&m0&72$m0$_1!e0&g1&e0\"?3"
	"O1\"e2&#'!P0\"h0!#$?4&e0!_1\"m0#/!]0\"G1&]0#W1!m0\"72#m0#_1&e0&$_1&e0!?3"
	"G1$&53\"'!H0\"01#74#!51\"O1#&m0&#'#]0&#g0$\"&]0\"_1#e0&$o1#&m0&#O1\"51!#G1$!51\"$o2"
	"G1!E3\"'!(\"!h0#o3!M1!?1\"M1&$\"e0.I0&m0\"o1&]0!g1$&M1\"?1&M1&71$&M1\"g2"
	"?1$U3+()h0!g3$]1$71&U1\"'\"52&#72\"]0#g1\"U1&71#]1#o0\"U1&?1$+$?1"
	"?1$&M0N0I0b0&M1!'H0\"01$_3$&M1&$71&U1\"/$!&M1&\"G2#U0&o1\"U1&71#]1#o0\"U1&o0#*#O1"
	"G1$+$W1$- =1$!(\"!h0!W2$!$o0\\1?1\\1g0#\").)\"#$_2&M0\"72T1G1\\1?1\\1W0$\")#_1"
	"O3&%(51#\"H0#01\"G2\"(!7:&-&$O9#! !#o1"
	"O3#-(m0+H0!\"01\"o1\"!H0\"$g9#M0\"79$\"!(!#?2"
	"O1\".\"_1!- m0+P0!\"01!$G1$\"!P0\"&!g9!M0$_8$\"!H0!$O2"
	"G1&U0!W1$E1#\"X0*81!#$O0,\"!X0!\"&-#_9&-!O8$\"!P0\"$_2"
	"?1\"e0$W1#51&'!`0!\"!P2!\"&M0\"_9#M0#o7$#)P0!\"$o2"
	"?1!e0#_1#m0!'81*!02!*M0&#o8$g0&-&$W7$\"!`0!#G3"
	"?1\"]0&g1$m0$#@1!*)@1)\"!&M0!$_8$!-&#O0#M0!?7$\")`0!\"$W3"
	"?1#]0&_1#&e0\"'`1!J1.U0!$o8!U0&O0&M0$_6#\"!01&\"$o3"
	"G1!]0!O1\"m0!'!P2)H0]0!#79$e0#'\"M0!G6#\"!@1!#G4"
	"G1$&]0&!\"[0\"!51!'!%P3&\"G9$e0.M0&$W5$+\"!H1!\"$W4"
	"O1$!U2&#'$&-`3!#$o8&E1#?5#\")X1!\"$o4"
	"_1#&52&\"W0$!M0h3!\"#$O8#=1\"W4$#\")h1!\"$G5"
	"o1$\"!.e0.!\"#71#!M084)\"#78#!U0&!$o3$#\")82&!#$_5"
	"W2,+,o1#&M0P4!\"#$_7$+$O3$#*)P2&\"#?6"
	"O5#!U0`4)\"+$W9,+*)h2&!\"$W6"
	"_5$\"&U0@5I0\"+,?7,+*I0H3%&!#$77"
	"76#!U086I0J0K0L0_3T0K0J0Q004-&!\"$W7"
	"G6$\".U0H7A3H5%.!\"$78"
	"g6#!&]0`>M0&!\"#_8"
	"?7#\"&e0P=U0&!\"#$?9"
	"W7$#\"!&e00<]0&!*#$g9"
	"?8$#!.e0P:e0.!\"#$W:"
	"g8$*!&51X8m0.!*#$G;"
	"O9$+*!.M1X5E1N0!J0#,?<"
	"O:,#*)N0]5V0!J0#,O="
	"_;L0+R0A3R0K0L0g>"
	"7P"
	"7P"
	"7P"
	"7P"
	"7P"
	"7P"
	"7P"
	"7P"))
    ((eq name built-in-gensym-logo-320)
     '#(320 119
	"7X"
	"7X"
	"7X"
	"7X"
	"7X"
	"7X"
	"7X"
	"7X"
	"7X"
	"7X"
	"7X"
	"?@$+L0?G"
	"_?$#J0#$WG"
	"??$#*!\",oG"
	"_>$#\"I0#$OH"
	"G>#\"! )#oH"
	"g=$#!()#GI"
	"O=$\"!H0!$_I"
	"7=#!H0!\"$7J"
	"_<#!P0\"#OJ"
	"?<$\"!P0!#gJ"
	"o;#!P0!\"$7K"
	"W;#!X0!#OK"
	"?;#!X0!\"$_K"
	"g:$\"!X0!#7L"
	"W:#!`0!$GL"
	"?:$\"h0\"$WL"
	"o9#!h0\"$gL"
	"W9$\"!h0\"?M"
	"G9$\"01\"OM"
	"W5,G3$!01\"_M"
	"G5\"&-&\"g2#!01\"$gM"
	"?5\"e0!O2$!01!$/$\"Y0 Q0\"#7L"
	"?3$#\"Y0\"#$W0#51$72$!01!#$\"!02!#_1T0o0$#\"Q0*#$?3$#\"Q0*#$O7T0o0$#\"Y0\"#$72$#\"Q0*#$G5"
	"g2#!&M1&!$'&51#g1$!01\"#\"!X2!$/#61U0#O0\".M1&\"$O2$\"&M1&!#_0\"n1!$G1\"N1!$#>1M0\"O0#!&M1&!#G1$\"&M1&!#o4"
	"W2#&=2&=1#W1$\"01\"#\"h0!21!81#'\"U1#'\"&=2!#o1$!=2!$O0&52$G1!U1$#U1\"'\"&=2&#g0\"&=2&\"_4"
	"O2!U3!W1\"01\"#!h0!\"#!&]0&\"#81$\"U1!&]2!_1#&U2#/&52$G1!U1$#U1.]2!$/#&]2&$O4"
	"?2$&51!\"K0!&=1+.\"O1#!h0!#\"01\"#&E1!#01!'!&U2.U1&O1#51&\"S0!&e0&$'\"m1!O1#M1!/\"&U2.U1&#!E1.U1&#G4"
	"?2&m0&$o0\"51\"_1$!01\"#!h0!#!e0^0-\"!01#/#&e1!\"$O0$#!E1!?1$&e0&$o0$m0\"/#&M1&#_1$\"&e0&\"_0#&e1&\",/$#!&=2&\"#$/$#\"&=1&$?4"
	"72!m0&G1#51$O1#81#\"01\"#]0&\"$_0$!&\"01!O0#U1\"$?1$&=1#71&e0&?1$m0!W0!=1!?2$]0&$o0#U1!$?1$&e1!$G1!=1!?4"
	"o1#m0&$O1\"m0&?1$!81#!01*U0&#G1+01!O0#E1&$W1$&51&o0#m0$?1$m0!_0&51!?2$U0&$71$E1&#_1&M1&#_1!=1$74"
	"o1&m0\"_1&m0#o0#81!#!01*M0&#_1$01!O0$=1&o1#=1$g0&e0&O1!e0#_0\"51&?2\"U0\"?1$=1&$g1#E1&$g1$&51\"74"
	"g1#51$_1\"m0&_0$!81!#81#\"M0!o1$01!#$'$51&$72&51\"_0$m0\"O1$&U0!g0$=1\"72&U0$?1$=1$72&=1#72!51!74"
	"g1!m0!g1$51#O0#@1!#81*M0\"72#01!\"#'$51&?2!51!_0#m0\"W1$\")#71!51&o1#U0!G1$51&?2\"=1$72#51&74"
	"g1&m0\"o1&m0!/\"@1!#81!#M0\"?2\"01\"&\"'$51&?2\"51!_0\"m0!?3#=1$g1!U0#G1$51&?2#51&?2$51&74"
	"_1#51#o1&m0&'#H1#!81#M0\"G2!01#&#'$51&?2#51&_0\"m0&G3&51\"_1$U0&O1$51&?2$51&?2$&51$o3"
	"_1#51#o1!51,@1#!81#&-\"G2#01!\"%$'$51&?2#51&_0\"51!?3\"51&_1\"U0\"O1$51&?2$51&G2&51$o3"
	"_1\"51$o1!51#'81*81!\"-!O2!01\"!%$'$51&?2#51&_0#=1&#o2#=1#W1&U0$O1$51&?2$51&G2&51$o3"
	"_1\"51$o1!51#'01!#@1#-&O2\"81\"%&/$51&?2#51&_0$M1&\"$_2&51!O1#U0!W1$51&?2$51&G2&51$o3"
	"_1\"51$o1!51#'01#@1\"!%&$G2\"81\"!%!/$51&?2#51&g0&]1!\"$G2\"51&O1!U0#W1$51&?2$51&G2&51$o3"
	"_1\"51#o1!51,h0*81!#-\"G2#81!#-#/$51&?2#51&g0#52!#$o1$=1#?1$U0&_1$51&?2$51&G2&51$o3"
	"_1#51#o1&m0&'#h0#@1\"!%&G2\"@1#&%&O0$51&?2#51&o0!E2!#g1&51!?1\"U0\"_1$51&?2$51&G2&51$o3"
	"_1$51\"o1&m0&'\"`0\"!@1#-#?2\"@1#&-#O0$51&?2#51&71&M2&#W1\"51&$71&U0$_1$51&?2$51&G2&51$o3"
	"g1&m0!g1$51\"'!`0#@1\"!%!72#!81!#&-!W0$51&?2#51&71$&U2!W1&51\"o0#U0!g1$51&?2$51&G2&51$o3"
	"g1\"51$_1\"51$'`0*@1#-$g1#!@1\"#&-&$W0$51&?2#51&?1$!U2&$G1!51&o0!U0#g1$51&?2$51&G2&51$o3"
	"o1&m0\"_1&m0!'\"`0#@1!\"%!W1$\"!@1!#!M0&$_0$51&?2#51&O1#&M2&$?1#=1$_0$&M0&o1$51&?2$51&G2&51$o3"
	"o1\"m0&$O1\"51$'!X0!\"@1#&%#?1$\"!H1!#\"&M0&$g0$51&?2#51&_1#&E2!G1&51\"_0\"U0\"o1$51&?2$51&G2&51$o3"
	"72!m0!G1$51\"'\"`0\"!@1$+'L0+\")X1\"#\"&U0!$o0$51&?2#51&o1#\"&52$?1\"51&_0&M0&72$51&?2$51&G2&51$o3"
	"72$&m0!71#&m0&'$h0#84!+!&]0\"?1$51&?2#51&G2#\"&]1\"?1$=1$O0#U0!72$51&?2$51&G2&51$o3"
	"?2$&m0&!\"K0\"&51!/!h0#P3!R0!&e0!$G1$51&?2#51&_2#!M1&G1&51\"O0!U0$72$51&?2$51&G2&51$o3"
	"O2!]2\"/!h0!\"H2Q0J0+\"!&m0&\"$W1$51&?2#51&o2$&=1&G1#51&/$U0&?2$51&?2$51&G2&51$o3"
	"O2\"M2&#'$!01!\"@1;1R0!.E1&\"o1$51&?2#51&?3!=1$G1&51#'\"U0#?2$51&?2$51&G2&51$o3"
	"G2$E2&#/\"@1\"!81!\"]2&!\"$?2$51&?2#51&G3&51$G1!51\"'&M0&G2$51&?2$51&G2&51$o3"
	"G2!U0!$\"!.-N0!#/$\"!H1\"!81\"!52.!\"$_2$51&?2#51&o0L072#m0&O1#51&#U0\"G2$51&?2$51&G2&51$o3"
	"?2#U0&$_0,/K0\"!`1\"@1\"&%>1)*#$G3$51&?2#51&_0#&-&\"o1$m0&W1&51&U0$G2$51&?2$51&G2&51$o3"
	"72$&U0#G1#*)`1#@1\"%\"?5$51&?2#51&W0\"e0!g1$m0\"W1\"U1!O2$51&?2$51&G2&51$o3"
	"72!U0\"',#j0+W0$\"!@1#@1\"&$?5$51&?2#51&W0&e0&g1$m0#W1#U1#O2$51&?2$51&G2&51$o3"
	"o1#]0.]1.!#/$\"01\"@1\"&G5$51&?2#51&O0#51$_1\"e0&g1&E1&W2$51&?2$51&G2&51$o3"
	"g1$&=3!#'$!`0\"!81\"!G5#51&?2\"51&O0#m0&_1$&e0#g1\"E1\"W2$51&?2$51&$?2&51$o3"
	"g1\"U3&$'\"X0\"!81*G5\"51&?2\"51&$/$m0!W1$&e0!o1$E1$W2\"=1$72#=1$72$=1#o3"
	"_1#m3#'\"P0!\"81!#?5#&=1\"o1$&=1!O0!e0&$G1#&e0&$72!51!W2$&=1!72&=1&$o1!=1&$g3"
	"_1&54\"'\"H0!#81!75#&U1&#W1\"&M1&!,&m0!\"#L0+\"&m0&$?2#51#G2#!U1&#W1\"&M1&!#O1\"&U1&#W3"
	"W1\"E4#'!H0#@1$g4#m1&O1\"m1&'$&e2!W2&e0&G2$52$G1#52$?1#52#_1,W1"
	"W1!E4&'#H0\"!81\"g4\"52$G1!52#'$!M2&\"_2\"e0\"G2\"52#G1\"52#?1\"52\"O1$#\"$W1"
	"W1\"e0N0)b0#*&e1\"'!(!#@1$_4\"52$G1!52$O0#&m1&\"o2$]0&$G2#52#G1\"52#?1\"52\"?1#\"!#g1"
	"_1\")\"#$g1!e1&'!H0\"!81\"G3#\"?1$32O1$32g0$\"!.]0.!\"$G3&U0!O2$32$G1$32$?1$32$g0$\")#72"
	"?4$-(M1'#H0!#@1#73\"(#78\\0o3\"U0#o;$#! !#G2"
	"G4!-(E1,P0*@1#_2#!H0!W<&M0!g;\"!(!#W2"
	"G4#M0(=1#'X0#!@1#G2$!P0!#$G<#U0#G;$\"!H0!#g2"
	"_1$\"N0#72!-(=1#'`0#!@1!$g1#!X0!#.G<!M0&7;$\"!P0!$73"
	"W1$&]0#72&- =1,h0#!H1!#?1#)`0#\"M0\"7<$U0\"_:$\"!X0\"$G3"
	"W1!e0&$o1#M1&'\"h0!#!X1i001!#!U0#7<\"U0$G:#\"!X0!\"$W3"
	"O1$&m0#72\"E1!'!81\"#!03!#\"U0&$?<&M0&o9$\"!h0!#o3"
	"O1$51$?2\"=1#'H1!#\"!P2!*&U0\"7;$+$g0#U0#O9$#)h0!\"$?4"
	"O1$m0&G2\"51!'\"X1!+\"!X1)\"#\"&U0&#7;\"&M0\"_0&M0&79$#\"!81!#W4"
	"W1&e0\"?2#51&$'82\"+*i0*+\"&]0&\"?;#e0#O0#U0\"W8$#\"!@1!\"$g4"
	"W1\"e0&$o1\"=1#'!P2)j0!&m0&!$G;&e0!O0&U0$78$#\"!H1&!#?5"
	"_1&e0&\"$G1$\"&=1\"'\"@4M0&\"W;$51#$!U0!_7#*!X1!#W5"
	"_1$&51&!*K0*&M1#'\"-H4!#_;$e1&?7$#\"!h1!\"$g5"
	"g1$!E3!$'$&M0X4!\"#G;!U1&#W6$\")02&!#$?6"
	"72#&e2!#W0$\"U0h4!\"$g:#M1&#76#\")@2&!#$W6"
	"G2#!&52&\"$71$!U005)\"$O:#&51!$O5$#\")H2%&!#$o6"
	"_2#*!61!\"#$_1#&U0H5!\"#$o9$\".-&!#o4$*)`2%&\"#O7"
	"W6#&U0X5)\"#$g9,O4$#\"I003%&!\"$g7"
	"g6#!]006)\"#$_<$#*I0H3-&\"#$?8"
	"77#\"&U0P6I0*#,?:,+*Q0h3%.!\"$_8"
	"O7#&]0@7)J0+,O7,K0J0I0X4M0&!#$?9"
	"_7$\"&]088Q0Z0[0l0g1l0[0Z0Y0X5-.!#$_9"
	"78$!&e0h:Q0H8M0.\"#G:"
	"O8$\"&e0`BU0&!\"$g:"
	"g8$\"!&e0PA]0&!\"#O;"
	"G9$\"!&m08@]0&!\"+$o;"
	"g9$#\"&51X>e0.!\"#$_<"
	"G:$#\"!&=1h<51.*#$O="
	"o:$#*!&E10;=1.!\"+$?>"
	"_;$#*!.]1H8U1.!*+$7?"
	"W<$+*!.M2`4=2.)*+,7@"
	"W=,+J0)^0U5f0)J0K0,GA"
	"G?T0K0b3K0T0GC"
	"7X"
	"7X"
	"7X"
	"7X"
	"7X"
	"7X"
	"7X"
	"7X"
	"7X"
	"7X"))
    ((eq name built-in-gensym-logo-384)
     '#(384 143
	"7`"
	"7`"
	"7`"
	"7`"
	"7`"
	"7`"
	"7`"
	"7`"
	"7`"
	"7`"
	"7`"
	"7`"
	"7`"
	"_C$K0$gK"
	"?C$#*+$7L"
	"_B$#\"!*$WL"
	"?B$#\"I0#$oL"
	"_A$\"Q0\"#OM"
	"?A$#!H0!#$gM"
	"g@$\"!H0!#GN"
	"O@#\"!H0!#_N"
	"o?#\"!P0!#7O"
	"W?#!X0\"#OO"
	"??#!X0!#gO"
	"g>#\"X0!\"$7P"
	"G>$#!`0!#OP"
	"7>#!`0!#gP"
	"_=#!h0\"$7Q"
	"G=$\"!`0!\"OQ"
	"7=#!h0!#_Q"
	"_<#)h0\"$oQ"
	"O<\"!h0!\"GR"
	"7<$\"01!\"WR"
	"g;#!01!\"gR"
	"O;$\"!01!\"7S"
	"?;$\"81!#GS"
	"o:$!@1#WS"
	"O6#V0\"W3$!@1\"$_S"
	"G6!e0!$73#!@1\"$W0$K0Z0+,gQ"
	"?6!51!g2#!@1!$'$#\"!`1!\"$OQ"
	"_3$#\"!n0!*$W0#E1$O2#!@1\"#$\"!X2!#O1T0S0\"$o0#\")f0)\"$_3$#\"!n0!\"#$G8T0K0*o0$#\"!n0!\"#$G2$\")f0)\"#G6"
	"G3$\"&m1&\"$'&E1$?2$!@1\"$#!@3!$O0\"^0=1\"W0#!&e1&!#73#!m1&\"g0$V2$W1#n1,f0=1$O0$\"&m1&\"$W1$\"&e1&!#o5"
	"?3\"&M2&!M1$72\"@1\"$\"!81!\"+,+\"P1$/!e1!/\"&U2&#W2#&M2&#W0$U2$W1\"m1$#m1$'$!]2!$71#&U2&\"_5"
	"o2\"&=4!g1$\"@1\"#!81!\"#\"!.-.!+H1#'!e1!\"&53&#72$!m2&$/$U2$W1\"m1,m1\"!53&\"_0\"&53&\"O5"
	"g2!M1.!.]1\"&M0!g1#@1!$\"81!+!M1!$H1$#M5\"g1#&E1.!N0=1&/$&E2&$W1$e1&/&E5&$'#&U3\"G5"
	"_2!=1&\"$_0#!E1&/#\"#_1$!@1+!81\"$!e1!#@1\"'#!&]2.).e1#W1$&51&\"$g0#&51#/#&52&#g1\"&M1&#O0\"&]2.I0.]1&!M1.I0&e1\"?5"
	"W2\"=1!$?1#&=1$72\"@1!$\"@1+51&)\"!&M0#!@1$O0\"=2!#$g0$\"&U1#O1&51\"G1#51!W0\"]1&\"$?2\"&m0&\"o0#&52&\"#o0#!]2!#$g0$\"&U1#75"
	"O2#=1&W1$&51&g1#!@1\"$!81!$\"]0&!\"$g0$\"&*@1\"W0&]1&!$W1\"M1&G1\"51\"O1#51&_0\"M1&_2$e0&$?1#e1&#W1#&52&!$W1\"M1&$o4"
	"G2$=1&g1#=1\"O1$!H1+@1\"$&U0&\"$W1+@1!W0!U1!$o1#M1\"71$51&W1#51&g0\"E1&_2$e0$O1]1\"72&e1!$o1#M1\"o4"
	"G2!=1#o1!=1#?1#P1#\"@1\"$]0!$o1$@1!W0!M1!G2&E1&71\"51\"W1$51!o0&E1#W2\"]0!O1$&E1&#?2$]1!G2!E1&o4"
	"?2$=1&72#=1&71\"P1$\"@1!$&M0&#?2$@1!#O0!E1&O2#E1&71&51$_1\"m0#o0!E1!W2&]0#O1$M1#O2\"M1&O2$M1$g4"
	"?2!=1\"?2&=1#_0$!H1!$\"@1!$&M0&$G2#@1*$/!E1#W2&E1#g0$=1o1\"&M0&\"71#M1$G2#]0&W1$E1!W2$M1#W2&E1#g4"
	"?2&=1$?2\"=1&W0\"P1!'!@1!$&M0\"W2\"@1\"&#/!E1$W2!E1\"g0#=1$72#\"#O1&E1\"G2!]0#W1$E1\"_2&E1#W2\"E1\"g4"
	"72$=1&G2#E1$/\"X1$!H1$&M0\"_2!@1#&#/!E1$W2\"E1\"g0\"=1$g3!E1&G2&U0&_1$E1!_2&E1$W2#E1\"g4"
	"72#=1!G2$E1#'\"X1#\"H1#\"M0!_2$H1$&#/!E1$W2#E1!g0\"=1\"g3#M1$72#]0\"_1$E1!_2&E1$W2#E1\"g4"
	"72\"=1!O2&=1\"'\"P1\"#H1!$M0!g2\"@1!#%#/!E1$W2#E1!g0\"=1&o3&E1\"72!]0$_1$E1!_2&E1$W2$E1!g4"
	"72\"=1\"O2&=1\"'#H1\"#H1!$&-!o2!@1#!%$/!E1$W2#E1!g0\"E1&#_3\"E1&o1#]0&g1$E1!_2&E1$W2$E1!g4"
	"72!=1\"O2&=1!'#@1!$P1$!-&o2\"@1!$%&O0!E1$W2#E1!g0$U1&#O3$M1$g1!]0\"g1$E1!_2&E1$W2$E1!g4"
	"72!=1\"O2&=1!'#@1#!H1!#M0$g2$H1#\"%!O0!E1$W2#E1!o0&]1&\"$?3!E1\"g1&U0&o1$E1!_2&E1$W2$E1!g4"
	"72!=1\"O2&=1!'#81!#P1$&-\"g2$!@1!$-\"O0!E1$W2#E1!o0!m1&!#o2#E1&_1\"]0\"o1$E1!_2&E1$W2$E1!g4"
	"72\"=1\"O2&=1\"'#81$!H1!\"-&g2$!H1$&-#O0!E1$W2#E1!o0$E2&!\"$W2&E1#W1&]0$o1$E1!_2&E1$W2$E1!g4"
	"72\"=1!G2$E1\"'\"01#\"P1#&-#_2$P1#!-&W0!E1$W2#E1!71!]2&\"G2\"E1!O1#]0!72$E1!_2&E1$W2$E1!g4"
	"72#=1&G2$E1#'!h0!$P1!\"-\"_2#P1+M0#W0!E1$W2#E1!71$&e2&\"$o1$E1&O1!]0#72$E1!_2&E1$W2$E1!g4"
	"?2=1&G2#E1$'!h0#\"P1$&%&$W2\"P1+M0!_0!E1$W2#E1!?1#53&\"o1&E1#?1$]0&?2$E1!_2&E1$W2$E1!g4"
	"?2&=1#?2!=1&'$h0!$P1!#-\"O2#!H1!#\"M0&$_0!E1$W2#E1!G1#&53&#_1\"E1!?1\"]0\"?2$E1!_2&E1$W2$E1!g4"
	"?2\"=1!?2&=1\"'\"h0#\"P1#&%&G2#!P1!$!M0&$g0!E1$W2#E1!W1!=3#W1$M1$71&U0&G2$E1!_2&E1$W2$E1!g4"
	"?2$=1&72#=1&/!h0$P1!$-#o1$\"!P1!+&U0#o0!E1$W2#E1!_1\"&m2&$W1&E1\"o0$]0\"G2$E1!_2&E1$W2$E1!g4"
	"G2\"=1\"o1&=1\"'#h0!#P1*%&_1$#!`1\"$\"]0\"71!E1$W2#E1!g1$\"&e2&W1\"E1&o0\"]0#G2$E1!_2&E1$W2$E1!g4"
	"O2&=1$_1\"=1&/!h0\"!P1'\"&\"?1$#\"!h1\"$\"&]0\"?1!E1$W2#E1!72$\"&]2#W1&E1$g0&U0&O2$E1!_2&E1$W2$E1!g4"
	"O2$&51&#O1#=1&$'#01#X1!j0Q002!\"+!&]0!$G1!E1$W2#E1!O2$\"!E2&W1\"E1\"_0\"]0\"O2$E1!_2&E1$W2$E1!g4"
	"W2#=1&#71$\"E1$'$01!#`4!\"#$\"&m0\"W1!E1$W2#E1!g2$\"&52#O1$E1&_0&U0&W2$E1!_2&E1$W2$E1!g4"
	"_2#E1&\"#L0#!&E1#/!01!\"@4!\"#$#\"&51!$_1!E1$W2#E1!?3#!e1\"W1&E1$O0#]0!W2$E1!_2&E1$W2$E1!g4"
	"g2#E3&#/!81*P3)\"+$#\"!&=1!#o1!E1$W2#E1!O3$!U1!W1\"E1\"O0!]0$W2$E1!_2&E1$W2$E1!g4"
	"o2#53!$'$!@1#!P1a0b0S0J0!&M1&!#?2!E1$W2#E1!_3#M1&W1$&=1&/$]0&_2$E1!_2&E1$W2$E1!g4"
	"o2&e2!$/#!H1$P1!#i0V0=2&\"$W2!E1$W2#E1!g3#E1&_1!E1#'\"]0#_2$E1!_2&E1$W2$E1!g4"
	"g2\"e0&]1&\"$/$!X1$P1*53&!\"$o2!E1$W2#E1!o3\"=1&_1#E1!'!U0&g2$E1!_2&E1$W2$E1!g4"
	"_2$e0#'#\"!n0*$O0$!`1!#P1#&M2.\"#$O3!E1$W2#E1!71L0W2$=1!_1$E1&$]0\"g2$E1!_2&E1$W2$E1!g4"
	"_2!]0!W1+*)02!#P1$&%N1I0*#$74!E1$W2#E1!g0\"&M0&\"O2&51\"g1!E1&]0$g2$E1!_2&E1$W2$E1!g4"
	"W2\"]0&W1$\"I0@2!#P1$%\"G6!E1$W2#E1!_0!m0!G2&51#g1#m1!o2$E1!_2&E1$W2$E1!g4"
	"O2$e0$71$?1$#\"!X1!#H1!#%$G6!E1$W2#E1!W0#=1$?2&m0&72&e1#o2$E1!_2&E1$W2$E1!g4"
	"O2!]0!#*!^0%f0!\"#$O0$\"H1!#H1!#&O6!E1$W2#E1!W0!=1#72$51!72\"]1&73$E1!_2&E1$W2$E1!g4"
	"G2#M3&\"#O0\"81!#H1!#&O6!E1$W2#E1!W0!=1#72\"51$72$]1\"73$E1\"_2&E1$W2$E1!g4"
	"?2$m3&!#'$\"01$P1#!O6&E1$W2\"E1!W0!51&72#51\"G2!U1$73$E1!_2&E1#W2#E1!g4"
	"?2!E4!/#h0$P1#\"O6&E1#W2\"E1&W0\"51!o1#51&O2#M1!?3\"E1&_2&E1\"W2#E1&g4"
	"72#U4&#'#`0#!H1+G6\"M1&O2$&M1#O0$51&$_1#&51#W2&E1#73$&M1#O2#M1&$O2&M1\"_4"
	"72&e4#'#X0*H1\"?6#&]1&$72#&]1!#/\"51&\"$71$\"&=1\"_2!=1&73\"e1\"?2\"]1&\"$o1#&]1&\"O4"
	"o1#55#'\"P0!#H1!o5$&=2\"g1\"=2&$'!E1!b0!&=1&\"g2#=1#g2\"&52&#_1#&=2\"_1\"=2&#?4"
	"o1&55&$'!P0#P1#g5\"M2$W1#M2!/\"E3!$73&m0&g2$M2!_1&M2#O1$M2&72$+g1"
	"g1#E5\"'#P0\"!H1\"g5!M2$W1\"M2&O0\"&e2&\"G3!m0!g2#M2&_1&M2\"O1#M2&g1$*#o1"
	"g1$&51N0)B1!E2$'!H0!\"P1g5!M2$W1\"M2&W0$\"&E2&\"$O3#m0#g2#M2&_1&M2\"O1#M2&W1#)#?2"
	"o1#!.!*#$72&=2\"'!P0$!H1\"74#$O1#J2$W1$J2#o0#!.E1.!#o3&]0&o2$J2#_1R2$O1$R2?1#\")\"O2"
	"75\"M0 ]1&'\"P0\"#P1#g3\" !W9$K0\"K0,O4\"]0\"W>$!(!#_2"
	"75$M0(U1&'#X0$!P1$O3#!H0\"7?!U0&G>$\"!(!#o2"
	"?5!M0(U1'$X0!$P1!$?3\"X0!7?&U0\"o=$#!H0!#?3"
	"?5$M0(U1/`0\"$P1!$_2$\"`0!,g>\"]0$_=#!P0!#O3"
	"72$!N0!$O2\"M0(M1/h0\"#X1\"$?2#!h0#\"%&g>&U0!G=#\"!X0\"$_3"
	"o1#&]0&$O2&M0 E1&'$01+`1!$W1$\"!h0!$\"M0!W>#]0#o<#\"!X0!\"$o3"
	"g1$&m0&O2#e1&'#81+h1!*#L0+\")81#$&U0&W>\"U0&_<#\"!`0!\"G4"
	"g1\"=1#O2\"]1\"'\"@1\"$!04!$\"]0!_>&U0\"?<$#!01!#W4"
	"g1&=1#W2\"U1#'!H1!#\"!P3!+&]0\"_>#]0#_;$#\"!81!#g4"
	"g1&=1$_2\"E1!/`1!+!h2!\"$\"&]0&$G=$+$71&U0&O;#\"!@1!#?5"
	"g1&51&g2\"E1#'\"02!+\"!@2\"#$\"&e0\"G=$!U0!g0#]0#o:$\"!H1&\"$O5"
	"g1!51\"_2\"E1!/H2!\"$#*)01!*#$\"&m0&#G=$&e0\"_0!U0&W:$#)P1!#g5"
	"g1#51!O2$\"E1&$'!`2!*K1\"!&51&\"W=!m0&$O0#]0\"o9$#*!X1!\"#76"
	"o1\"51!$72#&E1&$'\"h4m0!#g=&51\"/$]0&W9$#\"!h1&\"$O6"
	"72&51&\"#O1$\"&M1&$'\"@5-&\"$o=$=1&*&]0\"79$\")02&!#g6"
	"72$&E1.!b0!&]1!$'#M0@5!\"#7>&52!W8$#\"!@2&!\"$77"
	"?2$&54\"O0&U0P5!\"#_=&m1&$o7$#\")P2&\"$O7"
	"O2#&M3&\"$W0$\"&U0`5)#$7=#e1&#G7$#\"I0P2%&!#$g7"
	"_2#!m2&\"?1$!]006!\"#$_<#U1!$g6$#\")h2%&\"#G8"
	"o2$\"!&m1&!\"$_1#&]0@6!\"#$G<#&51&#G6$#*!83-&!#_8"
	"O3$#*)N0)*#$O2\"&]0P6!\"#$7<#!V0!#g5$#*)H3-&\"$79"
	"o7\"&]0h6!*#,g@,+*)h3%&!\"$O9"
	"?8#!e0@7)\"+$??$+\"I0@4-&!#$o9"
	"O8$\"e0`7)*#,?=,+*)`4M0&\"#O:"
	"_8$\"&e0@8I0*#,o:,+*I0H5M0&!#$g:"
	"79#!&e009I0R0S0L0o6T0S0R0Q006M0.!\"$G;"
	"O9#\"&m0H:i0b0C1d0K1b0i0P7U0&!\"$o;"
	"g9#!&m0PG]0&!\"$O<"
	"?:#!&m0XFU0.\"#$o<"
	"W:#\"&51HEe0&!\"#W="
	"o:$#\"!&51hCe0.!\"+$7>"
	"W;#\".=1PBm0.!\"#$g>"
	"o;$#\"!&E18A51&!\"#$W?"
	"W<$#\".M1H?=1.!\"#,?@"
	"?=$#\"!.M1X==1N0)\"#$7A"
	"o=,#\"!.m1h:U1.)\"+$7B"
	"g>$#*!.M2h752N0)\"+$7C"
	"_?,#*)N0m382]3V0)*#,?D"
	"g@L0+*I061E561I0J0+L0OE"
	"oBL5gG"
	"7`"
	"7`"
	"7`"
	"7`"
	"7`"
	"7`"
	"7`"
	"7`"
	"7`"
	"7`"
	"7`"
	"7`"))
    ((eq name built-in-gensym-logo-448)
     '#(448 167
	"7h"
	"7h"
	"7h"
	"7h"
	"7h"
	"7h"
	"7h"
	"7h"
	"7h"
	"7h"
	"7h"
	"7h"
	"7h"
	"7h"
	"7h"
	"?G,+OP"
	"_F$[0$WP"
	"7F$#R0#,oP"
	"_E#\")\"#$WQ"
	"7E$#\"Q0\"$oQ"
	"_D#\"!(!\"#OR"
	"?D$#!H0!\"$gR"
	"_C$#\"!H0!#$?S"
	"GC$\"!P0!#_S"
	"oB#\"!P0!\"$oS"
	"OB$\"!X0!#$GT"
	"7B$\"!X0!#gT"
	"_A#\"!X0!\"$7U"
	"GA#)X0!\"$OU"
	"o@$\"!`0!#gU"
	"W@#\"!`0!\"$7V"
	"?@$\"01!#OV"
	"g?$\"!01\"$_V"
	"W?#!01!#7W"
	"??$\"81!$GW"
	"g>$\"!81\"$WW"
	"W>#!81!#oW"
	"G>#!81!#?X"
	"o=#!@1!#OX"
	"_=#!@1!$_X"
	"G=$#!@1!#oX"
	"7=$\"H1!#?Y"
	"g<$\"P1#OY"
	"W7#\"I0#G4#!H1!#_Y"
	"G7$!e0&#g3#!H1!#O1T07X"
	"G7&51&$O3#!P1!_0$#*I0X0)*#$GW"
	"o441G1!E1\"?3#!P1!$'$#\"!H2!\"#o4l0W5l0G=41g3l0o7"
	"G4$\"N0m0N0!#_0#M1&o2#!P1\"$'\"!@3!#_1L0K0*)\"71#\"N0m0N0\"$G4$\"N0m0.!\"$_9T0+*)\"71$\"N0m0N0!#_2$\"N0m0.!\"$G7"
	"o3#\"&=2&!#/&M1&_2$\"H1!\"$#!h3!$W0!f0E1&_0#!&=2&!#W3$\"&=2&\"$o0#n2$g1$>2!/!f0E1!_0#!&=2&!#o1#\"&=2&!#o6"
	"_3#&m2&!U1&O2$!H1!#$\"!H1!\"#\\0#\"!X1#O0&52&/$\"&m2&\"$o2#!m2!$_0\"m2$g1$=2&/=2&/$\"&m2&\"$?1$\"&m2&!$W6"
	"W3!m4!G2\"P1#'#P1\",#\"!N0!\"#'\"X1#/&52&'#&M3&#_2\"E3&#W0\"m2$g1$=2&/&52&'#&M3&#o0#&M3&#O6"
	"G3#&=4&]0&$72#!H1\"$\"H1!#$\"&E1&#$!P1$'&=2&m3!$?2$!]3\"O0\"m2$g1$=2&/&52.m3!$O0#&m3!$?6"
	"?3\"U1&*K0\"!&]1\"$\"N0\"$o1#!H1!$#!H1#$\"m1!$!H1!'#&=6&$o1$&M1&*S0\"!&E1#/$&]2!72\"52\"/#&=6&,&E4&$76"
	"73\"M1&#?1\"&M1\"_2\"P1\"'\"H1!$#E2\"$P1#/$!m2.!\"K0\"!&m1&o1&E1!$?1$&=1!O0$&M2!G2\"&U1&#_0$!m2.!\"K0\"!&m1.M1.!\"K0\"!&m1&$o5"
	"o2\"M1!W1$!E1&$G2#!H1!+P1#$!51&!*+*!&%&'!H1!W0$!E2&\"#G1$\"e1!_1\"=1&#W1#E1#W0#&e1&\"$_2#&51&\"?1$!E2&\"#G1$\"m2&\"#G1$!e1&o5"
	"g2$M1\"o1&E1!?2!P1!'\"H1!$#m0&\"$G1\"%*P1$W0$=2\"o1$&]1\"O1#E1$_1#E1\"_0$&]1$?3m0&$O1$52&#o1$&M2&\"o1$&]1#g5"
	"g2!E1&72$&E1\"g1#!P1\"$!H1!$\"e0&\"$_1#\"#P1#_0&e1&#?2$&U1&O1&=1\"g1#E1\"g0#]1#73$m0#W1$m1&$?2$&=2!$?2$&U1!g5"
	"_2#M1$?2#M1$O1$!X1#$!H1!$!]0&\"G2$P1\"_0&]1\"W2$]1$?1#=1&o1$E1$o0!U1!73\"e0!_1$&]1\"W2#52\"W2$]1$_5"
	"_2&E1&O2&E1\"G1#`1#$P1!'\"]0!W2$P1\"$W0&U1!g2!U1\"?1!=1&72&51!71#U1&73!e0$_1$]1\"g2\"e1\"g2!U1\"_5"
	"W2\"M1#O2\"M1$71\"`1$#P1!$!]0\"_2#P1*$O0&M1&o2$U1!?1&=1!72#&e0&$?1&U1#g2$e0&g1$U1&o2$]1&o2#U1&_5"
	"W2&E1&W2#M1!g0$!`1$#X1$\"U0&$g2#P1#!#O0&M1\"73&M1&71$E1\"?2$!U0!$G1\"U1!g2\"e0#g1$U1!73&U1\"73&M1&_5"
	"W2&E1!_2&M1$W0#h1+X1$#U0&$o2\"P1#&#O0&M1\"73!M1&71#E1\"O2#*#W1#U1&g2&e0$g1$U1\"73!U1\"73!U1$W5"
	"O2#M1\"_2&M1\"/$!h1+X1+U0!?3!P1$%#O0&M1\"73\"M1&$o0\"E1!W4&U1#W2\"e0!o1$U1\"73\"U1\"73\"U1$W5"
	"O2\"M1#_2!M1!/!h1+X1!$U0!G3P1\"#%#O0&M1\"73#U1$o0\"E1&W4\"U1!W2&e0#o1$U1\"73\"U1\"73\"U1#W5"
	"O2!M1$_2\"M1&/!`1\"$X1!'!M0&$?3#P1#\"%#O0&M1\"73#U1$o0\"M1\"W4&U1#G2$e0!72$U1\"73#U1\"73\"U1#W5"
	"O2&M1$_2#M1&/!X1!'!X1$\"M0&G3$X1'&%$O0&M1\"73#U1#o0\"U1\"O4!U1\"G2\"e0#72$U1\"73#U1\"73\"U1#W5"
	"O2&E1&g2$U1$'\"X1'\"X1!$U0$G3\"P1!$-W0&M1\"73#U1#o0#]1!$?4#U1&G2&]0&?2$U1\"73\"U1\"73\"U1\"W5"
	"O2&E1&g2$U1$'\"P1#\"`1$&M0\"G3$X1#!%&W0&M1\"73#U1\"o0$e1&!#74&U1#72#e0\"?2$U1\"73\"U1\"73\"U1\"W5"
	"O2&E1&g2$U1$'\"H1!$`1+M0\"O3!P1!$-!W0&M1\"73#U1\"71&52&\"g3!U1\"72&e0$?2$U1\"73\"U1\"73\"U1\"W5"
	"O2&E1&g2$U1$'\"H1'!X1!'&-&O3!X1$!-\"W0&M1\"73#U1\"71!E2&!#$G3#U1&o1$e0&G2$U1\"73\"U1\"73\"U1\"W5"
	"O2&E1&g2#M1&/\"@1+`1#!M0#G3\"X1+M0$W0&M1\"73#U1\"71#]2.\"$73&U1$g1\"e0#G2$U1\"73\"U1\"73\"U1\"W5"
	"O2!M1$_2\"M1&/!81!$`1!$M0\"G3!X1\"$M0!_0&M1\"73#U1\"?1!53&\"g2#U1\"g1&]0&O2$U1\"73\"U1\"73\"U1\"W5"
	"O2\"M1$_2!M1!/!81#\"`1#\"-&?3$!X1!'&M0#_0&M1\"73#U1\"?1$&=3&!$O2$&M1&$W1#e0\"O2$U1\"73\"U1\"73\"U1\"W5"
	"O2#M1#_2&M1\"/81!$`1!$M0#73#!X1!'!M0\"g0&M1\"73#U1\"G1$U3&#G2!U1\"W1!e0$O2$U1\"73\"U1\"73\"U1\"W5"
	"O2$M1\"_2&M1#'$81$\"`1#\"-&73\"`1!'\"M0&o0&M1\"73#U1\"O1\"]3\"?2#U1!O1#e0!W2$U1\"73\"U1\"73\"U1\"W5"
	"W2&E1&W2$M1&/\"01!'`1!'&-#g2#!`1\"$&U0#o0&M1\"73#U1\"W1#&U3&#72&U1$G1!e0#W2$U1\"73\"U1\"73\"U1\"W5"
	"W2\"M1$O2\"M1!/!01#\"`1\"#-!_2#!h1,&U0\"71&M1\"73#U1\"_1$&]3#o1!U1\"G1&]0&_2$U1\"73\"U1\"73\"U1\"W5"
	"W2$M1\"O2&M1$'#81$!`1$&-$O2#!h1\"$\"]0!?1&M1\"73#U1\"g1$\"]3#g1$U1!?1#e0\"_2$U1\"73\"U1\"73\"U1\"W5"
	"_2\"M1$?2#M1\"/!01!#`1!#-!72$#!02!$#&]0!G1&M1\"73#U1\"72$!&M3$g1!U1$71!]0&g2$U1\"73\"U1\"73\"U1\"W5"
	"g2&E1!?2&E1&$'$81$\"`1#\"-#_1$\"!82!,&e0!O1&M1\"73#U1\"O2\"&=3!g1\"U1\"o0$e0\"g2$U1\"73\"U1\"73\"U1\"W5"
	"g2#M1#o1\"M1\"/\"01!'!`1'K0o0,#*)@2\",!m0\"W1&M1\"73#U1\"_2#!&m2#_1$U1&o0\"e0#g2$U1\"73\"U1\"73\"U1\"W5"
	"o2\"M1\"_1\"M1\"/#81!$h1A1`2!\",\"&m0&#_1&M1\"73#U1\"73#!&U2&g1!U1#_0$&]0&o2$U1\"73\"U1\"73\"U1\"W5"
	"73!M1\"$?1$!M1!/$!81+P5)$'$\"=1!o1&M1\"73#U1\"O3#&M2$_1\"U1\"_0#e0\"o2$U1\"73\"U1\"73\"U1\"W5"
	"?3!M1&!\"#L0#\"!U1&$/!@1$!05!\"#$#\"!&=1!#72&M1\"73#U1\"_3$\"&52#_1$U1&_0&]0&$o2$U1\"73\"U1\"73\"U1\"W5"
	"G3\"m3\"O0\"H1$H4!\"+$'$\"!&M1!#G2&M1\"73#U1\"74#m1\"g1!U1#O0$e0\"73$U1\"73\"U1\"73\"U1\"W5"
	"O3\"]3\"O0\"H1!#X2i0J0K0,#*.U1&!#W2&M1\"73#U1\"?4$!]1\"g1#U1\"O0\"e0$73$U1\"73\"U1\"73\"U1\"W5"
	"O3\"M3\"$/$!P1!#`1!$C1R0).52&!#o2&M1\"73#U1\"O4\"U1\"o1&U1$/&]0!?3$U1\"73\"U1\"73\"U1\"W5"
	"G3#E3!#O0#`1*`1#\"m3.\"G3&M1\"73#U1\"W4&M1\"o1\"U1\"'#e0\"?3$U1\"73\"U1\"73\"U1\"W5"
	"?3$&e0)&]1&!\"$O0#!h1*`1#&M3&!\"#$W3&M1\"73#U1\"W4#M1\"o1$U1&'&]0&$?3$U1\"73\"U1\"73\"U1\"W5"
	"?3!e0&O0$#\"I0&I0\"#$W0#\"!82#!X1!$]2.!*#$?4&M1\"73#U1\"?1#*#$o2&E1\"72&U1#e0\"G3$U1\"73\"U1\"73\"U1\"W5"
	"73$m0$g1,#*!P2#!X1!$M1^0)\"#$75&M1\"73#U1\"o0#&U0&#g2!E1#72\"U1&]0&O3$U1\"73\"U1\"73\"U1\"W5"
	"o2$&e0\"g1#&)h2#!X1\"#%&D1?6&M1\"73#U1\"g0!51!_2\"E1$72$&=2!O3$U1\"73\"U1\"73\"U1\"W5"
	"o2!e0&W2$#*@2#!X1#\"%#O7&M1\"73#U1\"_0#E1#W2!=1&G2\"=2#O3$U1\"73\"U1\"73\"U1\"W5"
	"g2$e0&$/,+B1+$g0#\"!`1#!X1#\"%W7&M1\"73#U1\"_0!E1\"W2!=1\"G2#52&W3$U1\"73\"U1\"73\"U1\"W5"
	"g2&e0&!.=2.!\"#W0#!P1#!X1#\"&W7&M1\"73#U1\"_0&E1\"O2$=1&W2&m1\"W3$U1\"73\"U1\"73\"U1\"W5"
	"_2#=4&\"#O0$!@1#!X1*!O7$U1#73#U1\"_0&E1\"O2!=1\"W2\"m1$W3$U1\"73\"U1\"73\"U1\"W5"
	"W2$&U4&\"$/\"81*X1\"#!O7$U1\"73\"U1\"_0&E1$G2#=1&$W2$e1&_3$U1\"73\"U1\"73\"U1\"W5"
	"W2&m4&\"/$!h0*X1!#\"O7#U1!73\"U1!_0!=1&G2#E1#g2&]1#_3\"U1&73!U1!73!U1!W5"
	"O2#E5&$/!`0!#`1$\"G7$&]1$o2&]1$W0\"E1$72\"E1\"o2\"U1&g3&]1$o2&U1&$o2&U1&$O5"
	"O2&M5&#'$!X0!$`1+?7\"&e1&#W2#&e1&\"$O0&=1&\"$O1$#&E1!?3&M1\"W3\"&e1&#W2#&e1&\"$O2#&e1&\"$?5"
	"G2!e5#'$`0$!X1\"77\"M2&$72$!M2!/#M1&!#$_0$\"!&M1!G3\"M1O3\"&E2&G2!M2!$72!M2!$o4"
	"?2$m5&$'\"X0#\"X1!o6\"]2!72!]2&$'#e1^0e1\"O3#E1!G3\"]2!72!]2&$g1!]2&$g4"
	"?2\"56!/!P0!$`1$g6&e2$g1$m2\"/#&]3&#_3&=1#G3&e2$g1$m2#_1#m2#G2$\"#$72"
	"?2&=6$'#X0'!X1\"g6&e2$g1$m2\"W0!M3\"o3!51&O3&e2$g1$m2\"_1#m2\"72#\"!#G2"
	"?2\"E1N0I0R1&U2&/!P0*X1!g6&e2$g1$m2\"_0#!e2&\"$74#51#O3m2$g1$m2\"_1#m2\"_1$\")\"W2"
	"G2\"V0!\"#,G2$]2$'\"X0$`1\"g4#g1j2$o1j2#o0$\"!&e1&!\"#W4&e0&W3j2o1$j2$_1$j2$G1$\"! !#g2"
	"o5&M0 52\"'#X0#\"`1$W4\" \"o:$#)f0)\"$75\"e0\"?A$\"H0#73"
	"o5\"M0(m1!'$X0!'!X1!G4#!H0#WA#e0$g@$\"!(!#G3"
	"o5$U0(e1!/!X0\"$`1!74!X0!WA&]0&W@$\"!H0!#W3"
	"76\"M0H0]1&/!`0#\"`1!_3#!`0\"OA$e0\"?@$#!P0!#g3"
	"?6&M0(]1&/!h0$\"`1!$?3\"!h0K0GA\"]0&$g?$\"!X0!$74"
	"W2\"!.\"#o2\"U0(U1&/!h0!'!h1\"g2#!h0!$#%&GA&]0\"W?$#!`0!$G4"
	"G2#&e0!o2&M0(U1!/!01!$!h1!\"$72#!81\"$!M0!7A#e0$??#\"!h0\"$W4"
	"?2#=1!g2$&M0 U1!/@1!'\"82!\"$?1$\"!@1!,&]0#o@!]0!o>#!01!\"o4"
	"?2&E1$g2#52\"'$H1!'\"H211X1\"$\"e0\"7A&]0\"O>$#)01!\"?5"
	"72$M1#o2\"m1$'\"X1#$!P4\"$\"&]0&#7A\"]0&7>$#\"!@1\"$O5"
	"72#M1#73!]1&/!`1!$#84\"'$&e0&$?A&]0\"_=$\"!H1!#g5"
	"72\"M1$?3!U1#'$82#$#!H3!\"$#!m0\"_?#\"#$?1#]0&$?=$#\"!P1!#76"
	"72#E1&G3&M1!/!H2\",\"!X2!\",\"&m0&#W?\"&U0!$o0!]0!g<$#\"!X1!\"$G6"
	"72$E1\"?3!U1#'$`2!#/\")X1)\"/#!=1\"_?\"m0!g0$e0#O<#\"!h1!#_6"
	"?2&=1\"73!U1\"/!83!\"#L0S0*S0$+\".=1!$_?#=1#_0!]0&o;$#\"!02!\"$o6"
	"?2#E1$_2$&U1&/#h3Y0\"Y0 U1!$o?!=1&W0\"e0\"W;#)82&\"$G7"
	"G2&=1&\"G2$\"]1&$'#h5e0&!$?@&E1#/#e0&$o:$#\"!@2&!#_7"
	"G2$&E1&!\",?1$#\"&e1!/#&@6%!#O@$&E1&!&m0#O:$*!P2&!#$o7"
	"W2&]1V0Q0.=2#/#U0@6!\"$G@&M2!7:#\"!X2-!#O8"
	"W2$!]4&#O0!]0P6!\"#o?\"E2&$G9$#\")h2&!\"$_8"
	"g2#&=4&#g0\"&]0X6)\"$O?$&52&$g8#*)03%&!#$79"
	"73\"&]3&\"?1$!e0h6!\"#??\"m1&O8$#\"!H3%.#W9"
	"G3#!&m2&\"#_1#&e087!\"#$_>\"&M1&\"_7$+\")P3-&\"#o9"
	"_3$#\"&e1&!\"#$G2#&e0P7!\"$G>$\"51&\"$?7$#I0`3M0&\"$G:"
	"?4$+21+$73$\"&e0X7)\"#$o=$#\")*#_6$#*)84-.\"#_:"
	"G9\"&e088)\"#,_C$+*)P4-.\"#?;"
	"W9#!m0P8)\"#$?B$#\"I005M0&\"#_;"
	"g9#!m0h8I0\"+$7@,+*I0H5M0.\"#7<"
	"7:$\"&m0P9I0*+,W=,+*Q006M0&!\"#W<"
	"O:#&51@:)*+L07;L0+J0)h6U0&\"#7="
	"_:$\"&518;Q0R0K0T0g6T0S0R0Y0X7U0&!\"#$O="
	"7;$\"&=1`<91\"!R0K2R0!\"A1H9]0&!#$7>"
	"O;#\"&51XK]0&!\"#W>"
	"g;$\"!&51HJ]0.!\"#$7?"
	"G<\".=1@Ie0.!#$_?"
	"_<#\".=10Hm0&!\"#$G@"
	"?=#\"!&E1PF51&!*#$o@"
	"_=$\".M1@E51.!#$_A"
	"?>$*.U1PC=1.!*#$GB"
	"g>$#\"!&e1PAU1&!*#$?C"
	"G?$#*!&m1h?U1.)\"#$oC"
	"7@,#\"!N052H=e1N0!*#,gD"
	"7A$\"!N0M20;=2N0!\"#$oE"
	"gA$+*!N0=307e2V0)*+,gF"
	"oB,+J0)V0U9^0)J0+L0?H"
	"WD,#*I0f0m5f0I0*+,7J"
	"GFl5oK"
	"7h"
	"7h"
	"7h"
	"7h"
	"7h"
	"7h"
	"7h"
	"7h"
	"7h"
	"7h"
	"7h"
	"7h"
	"7h"
	"7h"))
    ((eq name built-in-gensym-logo-512)
     '#(512 191
	"7p"
	"7p"
	"7p"
	"7p"
	"7p"
	"7p"
	"7p"
	"7p"
	"7p"
	"7p"
	"7p"
	"7p"
	"7p"
	"7p"
	"7p"
	"7p"
	"7p"
	"WJT07U"
	"7J$[0$?U"
	"WI$#R0#$WU"
	"7I$#*)\"$7V"
	"WH$#) !\"#$OV"
	"?H#)(!\"$oV"
	"WG$#\"!()#$GW"
	"?G#\"!H0!\"$gW"
	"_F$#\"P0!\"$?X"
	"GF#\"!P0!\"$WX"
	"gE$\"!X0!#$oX"
	"OE$\"!X0!\"$GY"
	"oD$\")X0!\"$_Y"
	"WD$\"!`0!\"?Z"
	"?D$\"!h0!$OZ"
	"gC$\"!h0!\"gZ"
	"OC$)h0!#$7["
	"7C$\"!01\"#O["
	"_B#\"!01!\"$_["
	"GB$\"!81\"$7\\"
	"7B#!81!\"O\\"
	"_A$\"!81!#_\\"
	"GA$\"!@1\"$o\\"
	"7A#!@1!\"G]"
	"_@#\"!@1!#W]"
	"O@#!H1!$g]"
	"7@$\"!H1!$7^"
	"g?$\"P1!$G^"
	"W?#!P1\"$W^"
	"G?\"!P1\"$g^"
	"o>$\"!P1!$7_"
	"_>$!X1!$G_"
	"_8$#J0$75#!X1!#W_"
	"W8\"&]0!$W4#!`1#g_"
	"G8$&=1#?4#!`1#?1$+R0!*#,G]"
	"G8&E1&$g3#!`1\"$W0$\"I0`1)\"#g\\"
	"G5$K0Z0K0$G1!U1\"W3#!`1!$'$#\"!83!#G5$+b0+,_5$+b0+$_>$K0b0+$o3$+Z0K0$g8"
	"g4$#\"&]1&!\"#_0#]1!G3#!X1!\"/#!h3!#?1T0S0j0I071$#\"!&]1&\"#$_4$*&U1&!\"#$?:T0S0j0I0#71#\"!&]1&!\"#o2#\"!&U1&!\"#$?8"
	"W4#!]2&\"$/&]1&73$!X1!#'$\"P4!$W0$.E2$_0#!&]2!\"$74\"!]2!#?1N3#?2\"%>2%\"/!&E2\"_0#\"&]2&\"#?2#\"&]2!#o7"
	"G4\"&E3*e1!g2$\"X1!#'#!`1!\"+$'$#\"!02#O0#U2$/$\"&E3&\"$W3\"&=3&#o0&E3#?2!M2!/&M2\"O0#!M3!#_1#!E3&\"$W7"
	"74\"&U5\"_2\"X1!#'\"`1\"$'$#\"!.)#/#h1#/#U2$'\"&m3\"?3#&]3&$_0&E3#?2!M2!/&M2\"'#&m3&$?1\"&m3\"O7"
	"g3$!]5&$O2#!X1#'#!P1!#'$\"&=1&!,!`1#'$U2\"&E4&#g2\"54&$W0&E3#?2!M2!/&M2!\"M4\"g0\"&E4&#?7"
	"_3#&e1N0!N0=2!\"&U0&#G2#!X1\"'#!P1!#'\"&m1\"'!`1$'&=7\"O2$!e1N0!V0U1&$O0!=3&$?2\"M2\"/\"=7!$/#&]4&\"77"
	"W3#e1!#o0#!m1O0\")\"G2$\"X1!$'!X1\"'#&E2\"'`1\"/\"&m3^0U2!G2&U1&\"$71#&M1!O0$&53#O2!=2!W0#.m3V0U2&#\"52^0U2\"o6"
	"O3#]1&$O1$&]1#o2#!X1!'#X1!,!]2+`1$O0$!=3&!#$_0$#!&=2\"72!M1&#_1&E1&_0\"&M2&!$_2#&]1&#71\"&53.\",W0,\"&m3&!#$_0$#!&=2#g6"
	"G3$&U1\"o1!U1&_2$!`1#'\"X1!'#&=1&!\"#T0\"!&-&'!X1\"_0#]2&!#_1#&52$g1\"M1&$g1\"M1#_0$!=2\"G3$&E1\"W1!]2&\"_1$!E3&\"$_1\"&m1&$_6"
	"G3&U1\"?2\"U1\"O2\"`1!,!X1#'!51&\"$O1#!%$\"X1!g0!M2\"$?2\"m1&_1$M1&72!M1!o0\"m1!_351&#_1$M2!$?2#&e2&#G2!m1!_6"
	"?3\"U1!O2&U1#72$!`1!'#`1$'&m0!#72*#`1$_0\"=2!$W2\"m1#W1!M1#72!M1!71&e1!W3$51#g1$=2&#W2$&U2\"$W2!m1$W6"
	"73$U1&$O2$U1&o1\"h1\"'\"`1$#&e0!#O2,`1$_0\"52\"o2!e1!O1$&E1!?2\"M1\"71#e1&W3#m0!o1$52&$g2#E2&#o2&e1\"W6"
	"73!U1#_2\"U1\"W1$!h1#'!X1!$#e0&#g2$`1#$W0\"m1#73$&e1$G1\"M1#?2$E1&G1&e1#O3!m0#o1$m1!?3!52&#73$e1&W6"
	"o2$]1$_2$U1&$G1#02#'!`1$#e0!73$`1#\"W0\"e1\"G3\"e1#G1&M1$G2\"=1\"G1\"e1!G3$m0&72$e1&G3$52#G3!e1$O6"
	"o2\"U1&o2&U1\"?1!02\"$!`1#$e0\"?3#`1$!$O0\"e1$G3#e1\"G1M1&W2!m0!W1e1&G3\"m0#72$e1\"O3&e1&O3#e1#O6"
	"o2&U1\"o2!U1&$g0#82#'h1#$e0#G3#`1$&#O0\"]1&W3&]1!?1#M1&_2#!M0&#_1!e1#?3&e0&?2$e1$O3\"e1\"O3$e1\"O6"
	"g2$]1$o2#]1\"_0\"82#'!`1\"'&U0&#O3\"X1!$%\"O0\"]1&W3\"]1!?1\"M1&o2L0o1\"e1\"73#m0!?2$e1$O3#e1\"W3&]1!O6"
	"g2\"U1&73$]1!O0$!82\"'!`1!'!U0&$W3!X1\"#%\"O0\"]1&W3\"]1&?1!U1$75$e1&$o2!m0#?2$e1$O3#e1\"W3&]1!O6"
	"g2!U1&?3&U1&/$!82\"'!h1'\"U0&_3#`1#\"%\"O0\"]1&W3#e1$71!U1\"?5!e1#o2&e0&G2$e1$O3$e1\"W3!]1&O6"
	"g2&U1!?3&]1/$82!'!h1#$U0&$_3\"`1$!%\"O0\"]1&W3#e1$71!U1&$75#e1!g2\"m0#G2$e1$O3$e1\"W3!]1&O6"
	"g2&U1\"?3!]1$/82'\"h1\"'&U0#_3$`1!'&%#O0\"]1&W3#e1$71!]1!?5&e1$_2&e0&O2$e1$O3$e1\"W3!]1&O6"
	"_2$]1\"?3!]1\"/!h1$#h1!'!U0#g3\"`1+-$O0\"]1&W3#e1$71!e1&$o4\"e1\"W2#m0\"O2$e1$O3$e1\"W3!]1&O6"
	"_2$]1#?3!]1\"/!`1\"'02+U0\"g3$h1'!%&W0\"]1&W3#e1#71\"m1&\"g4$e1&W2&m0#O2$e1$O3$e1\"W3!]1&O6"
	"_2$]1#?3!]1!/!X1!'!h1!'&M0!o3!`1\"$-&W0\"]1&W3#e1#71$=2&\"#W4&e1$G2$m0&W2$e1$O3$e1\"W3!]1&O6"
	"_2$]1#?3!]1!/!X1$\"02'\"M0&o3\"h1'&-\"W0\"]1&W3#e1#?1&M2&\"$?4\"e1\"G2#m0#W2$e1$O3$e1\"W3!]1&O6"
	"_2$]1#?3!]1\"/!P1\"$02\"$U0#g3#h1#$M0$W0\"]1&W3#e1#?1\"e2!#$o3e1&G2&e0&_2$e1$O3$e1\"W3!]1&O6"
	"_2$]1\"?3!]1\"/!H1!'!02$!M0!g3#h1!'&-&_0\"]1&W3#e1#?1$53&!#$W3&e1$72#m0\"_2$e1$O3$e1\"W3!]1&O6"
	"g2&U1\"?3!]1$/!H1$#02\"#M0&$_3#02$\"M0\"_0\"]1&W3#e1#G1\"M3&\"G3#e1!72!m0$_2$e1$O3$e1\"W3!]1&O6"
	"g2&U1!?3&]1O0H1\"'!02'!M0#_3#02$#U0$_0\"]1&W3#e1#G1$&U3&!#73&]1&o1$m0&g2$e1$O3$e1\"W3!]1&O6"
	"g2!U1&?3&U1&/$H1$\"02\"$M0!_3\"02#$&M0!g0\"]1&W3#e1#O1#m3&\"$_2\"e1#g1\"m0#g2$e1$O3$e1\"W3!]1&O6"
	"g2\"U1&73$]1!/#@1!'82'!M0$O3$!02,&M0&$g0\"]1&W3#e1#W1#54&\"_2e1&g1&e0&o2$e1$O3$e1\"W3!]1&O6"
	"g2$]1$o2#]1\"/\"@1$\"02\"$M0!O3\"82$#&U0#o0\"]1&W3#e1#_1\"=4&$O2&e1$W1#m0\"o2$e1$O3$e1\"W3!]1&O6"
	"o2&U1\"o2!]1#/!81!'82$\"M0$?3#!02!'#]0&71\"]1&W3#e1#g1\"=4&#G2\"e1#W1!m0$o2$e1$O3$e1\"W3!]1&O6"
	"o2\"U1&o2&U1!/#@1+02!'&-\"73#!82\"'\"]0&$71\"]1&W3#e1#o1#&=4\"?2$e1!W1&e0!73$e1$O3$e1\"W3!]1&O6"
	"o2$]1$_2#]1#/\"81!'!02#\"-&o2#!82!$'!]0&$?1\"]1&W3#e1#72$\"=4\"?2!e1$G1\"m0$73$e1$O3$e1\"W3!]1&O6"
	"73!U1\"_2!U1&/$@1\"$82'&-!O2$#\"!82!#'\"&]0&#G1\"]1&W3#e1#G2#!54#72#e1\"G1&e0&?3$e1$O3$e1\"W3!]1&O6"
	"73$&U1$O2#]1#/\"@1#\"02\"$M0#72$#\"H2!#'#&e0&$O1\"]1&W3#e1#W2$!&]3&$72&]1&?1#m0\"?3$e1$O3$e1\"W3!]1&O6"
	"?3#U1!G2$&U1!/$H1$!02$#.\"_1$#\"!P2!#'#&m0&$W1\"]1&W3#e1#g2$\"&U3!72\"e1#71!m0$?3$e1$O3$e1\"W3!]1&O6"
	"G3&U1!?2!U1&$/\"@1\"$82L0/l0+*!h2!#'#!51!g1\"]1&W3#e1#?3#!&=3&$o1#e1\"o0$&e0!G3$e1$O3$e1\"W3!]1&O6"
	"G3$&U1!o1!]1$/$H1#\"`6\"#'$!&51&#o1\"]1&W3#e1#W3#\"&m2#72&]1&o0#m0#G3$e1$O3$e1\"W3!]1&O6"
	"O3$&U1&#O1#&]1\"O0!H1$!@6!\"#/\"&E1!$72\"]1&W3#e1#o3#!]2\"72\"e1$g0&e0&O3$e1$O3$e1\"W3!]1&O6"
	"W3#&]1&\"+L0+\"&e1\"O0!H1!'!X5)\"#,#\"&M1!#G2\"]1&W3#e1#?4$\"&E2&72$e1!_0#m0#O3$e1$O3$e1\"W3!]1&O6"
	"_3$&M4&#O0\"P1\"'05I0\"$/$#\"!]1&#W2\"]1&W3#e1#W4#&=2$72&]1&_0!e0&W3$e1$O3$e1\"W3!]1&O6"
	"o3!=4&$O0\"X1+h3Q0*#$/,#*&m1!#g2\"]1&W3#e1#g4\"52#72#e1#O0$m0!W3$e1$O3$e1\"W3!]1&O6"
	"o3#m3&#W0!`1$\"02!D1O0$'L0#\").E2!\"$73\"]1&W3#e1#o4#&e1#?2&]1&O0\"m0$W3$e1$O3$e1\"W3!]1&O6"
	"g3$&e3\"$O0#!h1$!02+11f053&\"$O3\"]1&W3#e1#75$e1#?2!e1O0&e0&_3$e1$O3$e1\"W3!]1&O6"
	"g3!U3&\"$W0\"82'!02'&M4!\"$g3\"]1&W3#e1#?5\"]1#?2#e1#'$m0#_3$e1$O3$e1\"W3!]1&O6"
	"_3\"51#\"!&]1&!\"#W0$\"!82!'!h1!'&]3.!\"#$?4\"]1&W3#e1#G5&U1#G2&]1!'\"e0&g3$e1$O3$e1\"W3!]1&O6"
	"W3$51#W0$#\").I0\"#g0$#!P2!'02\"$53.)\"$o4\"]1&W3#e1#G1#J0#O3&U1$G2\"e1$&e0\"g3$e1$O3$e1\"W3!]1&O6"
	"W3!m0&?2,+\"!h2\"'02+]1^0)*,_5\"]1&W3#e1#71\"&]0&#?3!M1&O2$e1&e0&o3$e1$O3$e1\"W3!]1&O6"
	"O3#m0&$72.P3\"'02$!%&L177\"]1&W3#e1#o0!=1\"73\"M1!W2!U2!o3$e1$O3$e1\"W3!]1&O6"
	"O3&m0#?2T0+*!X2\"'02$!%\"O8\"]1&W3#e1#g0\"M1$o2\"M1\"W2#U2#o3$e1$O3$e1\"W3!]1&O6"
	"G3!m0!W1,_1$#\"!82\"'02$&%$O8\"]1&W3#e1#_0$U1!o2!M1$W2$&E2&74$e1$O3$e1\"W3!]1&O6"
	"?3#m0&+*)n0%n0)*#$_0#\"!`1\"'02$.W8\"]1&W3#e1#_0#U1&o2&E1&g2\"E2\"74$e1$O3$e1\"W3!]1&O6"
	"?3&m0&M3&\"#_0\"X1\"'02$.W8\"]1&W3#e1#_0\"U1&g2$M1\"g2#E2$74$e1$O3$e1\"W3!]1&O6"
	"73\"m4&\"#W0\"H1!'02$)W8\"]1&W3#e1#_0\"U1\"g2!E1&73&52!?4$e1$O3$e1\"W3!]1&O6"
	"o2#M5&\"O0$!81!'!h1#\"!W8!]1&W3\"e1#_0\"U1$_2\"M1#73\"52#?4$e1$O3#e1\"W3!]1&O6"
	"o2&]5&#O0!81'!h1+\"W8&e1$O3\"e1\"_0#M1&_2\"M1\"?3$m1&G4#e1\"O3#e1!W3&e1$G6"
	"g2#56!O0\"01$!h1\"$\"O8#m1#O3&e1&g0&E1&$O2\"M1&O3&e1\"G4&e1&O3!m1#G3$m1!G6"
	"_2$&=6&$/\"h0+h1!'#G8\"52&#73$&52&#W0#M1&#72#&M1&#O3\"]1&$74#&52!$73\"52&\"73#&52!#76"
	"_2!M6&$/\"`0\"'02,o7$\"&M2!$_2\"U2&#O0!U1!#$G1#\"&U1&$_3&U1!o3#&M2&#_2#&M2&\"$O2$!U2!#g5"
	"W2#]6&O0`0!'!h1#o7#&e2&#O2&m2&$/&e1!j0!&e1&$g3!U1$g3!m2!O2\"53#?2$&m2!_5"
	"W2&e6!/#`0$\"h1!o7&53&G2!=3&/$&U4!$o3#M1&g3\"=3\"?2#E3#72&=3!o2$#$G2"
	"O2$57\"/!X0\"#02$_7#E3#?2&=3&W0!=4&#?4$&E1\"g3&=3!?2\"E3\"72E3&_2$*$O2"
	"O2#57&/#X0!'02\"_7#E3#?2&=3&_0#&e3\"$O4\"E1$g3&=3!?2\"E3\"o1$E3&O2#)#_2"
	"O2$&M1V0)b1!&m2\"/!X0#\"h1!_7#E3#?2&E3g0$\"&=3&\"$_4#=1!o3&=3!?2\"E3\"o1$E3&72#\")\"o2"
	"W2#&U0.!\"#$_2\"m2&/\"X0!'02\"W7$!63!$?2\">3!?1$!&M2&!#?5&51#o3\">3\"?2#F3#72!>3!_1$\"!(#?3"
	"g2K0$O3#U0 M2$'#`0$\"02$G5\"!O<$\"!N0m0N0!#$W5\"m0&gC#\"H0\"O3"
	"g6&M0H0=2#'$`0!'02!75#!(!7=l0G6$m0#OC#!H0!#_3"
	"g6#U0H052\"/!`0+02\"g4\"X0\"7D#e0&?C$\"!H0!#o3"
	"g6$U0H052\"/!`0!'!02\"O4#!h07D!e0\"oB\"!P0!#?4"
	"o6\"U0H0m1\"/\"h0\"'!02\"74#!h0!#oC#m0$OB#\"!X0!#O4"
	"77&U0(m1\"/\"01#'82!$W3#!01!'+gC\"e0&?B$\"!`0!$_4"
	"g2$\"!.!\"$G3#U0H0e1\"/\"81$#@2#?3#!81\"'\"%&$WC$m0#gA$\"!h0!$o4"
	"_2\"51\"G3!U0(e1\"/!@1#$@2!#W2$!@1!$'&M0&WC\"e0&WA#)01\"$?5"
	"W2\"E1#?3$&U0 e1\"/!H1,P2!$g1#\"!H1\"'#&]0\"OC&e0\"?A#!81!\"$O5"
	"O2$M1&G3#M2#'$X1#$!P2I0\"[0*)X1!#'\"e0&#GC$e0&$g@#!@1!#g5"
	"O2\"U1#G3\"E2$'#`1\"'\"H5!\"$\"&e0&$OC!e0!G@$#\"!@1&!#76"
	"O2&U1#O3!52&/\"h1!,!05\"'$&m0!_C&e0#o?$#!P1&\"O6"
	"G2$]1#W3&m1\"/!82#'#!P4\"'$!51\"_C\"e0&W?$#\"!X1!#_6"
	"G2$]1$_3&]1&/$H2!#'#!h3!#'#&51&$gA$\"!\"#O1&e0\"??#\"!`1&\"$o6"
	"O2&M1&_3$&]1#/!X2!#'$\"!83!\"$'#&=1\"gA$&]0&$71$m0$_>$\"!02!#G7"
	"O2!M1!_3&]1&/$03!\"$'$#\"!82!\"#$'$!&=1&#gA#&m0&$o0\"e0!G>$#)02&\"#W7"
	"O2\"M1\"O3$&]1&$/!H3!\"#L0+J0Y0J0+,#\"!&E1&\"oA$&=1!g0$&e0#g=#\")82&!#o7"
	"O2$M1&G3#&e1#/#84!*+l0+*&]1&\"?B\"M1$_0!e0&O=#\"!H2.\"G8"
	"W2!M1\"$o2\"m1\"/$H6M1&\"OB&M1!W0\"m0\"g<$#\"!X2&\"$W8"
	"_2&M1&\"$G2$!&m1\"/$07U0&\"#_B&U1$'$!m0&O<$\")X2%&\"$o8"
	"_2$&U1.\",O1#!&=2\"/$&%@7\"7C&]1.51#o;#\"!h2%&\"#G9"
	"g2$&m1V0Y0N0E2&#/$&U087!\"$_B&e2\"O;$\")03-!#$W9"
	"o2$!M5!$O0\"e0H7)#$?B\"]2!g:$#\")@3%&!\"$o9"
	"?3#&m4!$g0\"&e0X7!\"#gA$U2&$?:$#*!P3%&!#O:"
	"O3\"&M4&#?1$!m0h7\"#$OA\"E2&_9,#*!`3%&!#g:"
	"_3#!e3&\"$_1$!m008)\"$7A\"52\"?9$#\")h3M0&\"#?;"
	"o3$\"!&e2&!\"$G2#&m0H8!\"$_@#&U1!$W8,\")@4M0&\"#W;"
	"O4+\"!.E1.!*#73\"&m0X8!\"#$G@\"!m0&\"#78,\"I0P4M0!\"$o;"
	"?5,c0,o3$\"&m0h8)*#$g?$+\"+$O7$+*I0`4-.\"#$G<"
	"_:\"&m0H9!*#$WF,#*)@5M0.\"$g<"
	"o:\"&51X9)\"+$gD,+*)`5M0&!#G="
	"?;#!=18:I0\",oB,#\"Q086U0&\"#$_="
	"O;$\"&51X:Q0\"#$o@,#\"Q0`6U0&!\"$?>"
	"g;#&=1@;Q0\"#,W>,#*Q0H7]0!\"#_>"
	"7<#\"&=10<Q0R0K0,g:,S0R0Y008]0&!\"#$7?"
	"O<#!&=1H=I0Z0S0T0G6T0[0Z0Q0P9]0&!\"$_?"
	"g<#.=1@?a0B4a0H;e0&!\"$?@"
	"7=$#\"&E18Om0&!\"#$_@"
	"W=#\"&M10N51&\"#$GA"
	"o=#\"&M10M51&!\"#$gA"
	"G>$\"!&M1hKm0.!\"#$OB"
	"g>$\"!&U1PJ51.!\"$?C"
	"G?$\"!&U1@I=1.!#$gC"
	"g?$#\"!&e1HGM1&!\"#,OD"
	"O@#*&m1hEU1&!*#$?E"
	"o@$#\"!&528De1&!*#$oE"
	"WA$#*!.52@B]1N0!*+$_F"
	"OB$#!N0E20@52N0!\"#$gG"
	"?C$#\"!N0U2X=E2N0!*,_H"
	"oC,+*!.U3H9E3.!J0+,_I"
	"7E$+J0!.=5X355&)J0+,oJ"
	"?F,+J0).e:.)R0K0,?L"
	"WG,S0R0Y0n6Q0b0K0L0gM"
	"7p"
	"7p"
	"7p"
	"7p"
	"7p"
	"7p"
	"7p"
	"7p"
	"7p"
	"7p"
	"7p"
	"7p"
	"7p"
	"7p"
	"7p"
	"7p"
	"7p"))))

)



;; Converting system icons to polygons/solid-rectangles.
;; JED 8/11/93

(defun create-gensym-logo-description (bar-width)
  (let* ((logo-height (-w (*w 19 bar-width) 1))
	 (half (round logo-height 2))
	 (diamonds-offset (round (*w 5 bar-width)))
	 (half-diamonds-offset (round diamonds-offset 2))
	 (logo-width (+w logo-height diamonds-offset))
	 (bar-center (+w diamonds-offset (round logo-height 2))))
    (create-icon-description
     logo-width logo-height
     (loop for x from 0 to 9
	   as  i = (if (<w x 5) x (-w 9 x))
	   as top = 0 then (+w top (twicew bar-width))
	   as bottom = (+w bar-width top)
	   as left = (-w bar-center (*w 2 i bar-width))
	   as right = (+w bar-center (*w 2 i bar-width))

	   if (=w x 0)                                  ; top triangle
	     collect
	     (create-filled-polygon-icon-description-element
	      `((,bar-center 0)
		(,(-w bar-center bar-width) ,bar-width)
		(,(+w bar-center bar-width) ,bar-width)))
	   else if (<w x 5)                           ; top trapezoids
		  collect
		  (create-filled-polygon-icon-description-element
		   `( (,(-w bar-center top) ,top) (,(+w bar-center top) ,top)
		      (,(+w bar-center bottom) ,bottom)
		      (,(-w bar-center bottom) ,bottom)))
	     else if (<w x 9)                           ; bottom trapezoids
		    collect
		    (create-filled-polygon-icon-description-element
		     `( (,(-w left bar-width) ,top) (,(+w right bar-width) ,top)
			(,right ,bottom) (,left ,bottom)))
	       else                                       ; bottom triangle
		 collect
		 (create-filled-polygon-icon-description-element
		  `( (,(-w bar-center bar-width) ,top)
		     (,(+w bar-center bar-width) ,top)
		     (,bar-center ,logo-height)))
		 and                                      ; solid region
		 collect
		 (create-filled-polygon-icon-description-element
		  `( (,half 0) (0 ,half) (,half ,logo-height)
		     (,(+w half half-diamonds-offset)
		       ,(-w logo-height half-diamonds-offset))
		     (,diamonds-offset ,half)
		     (,(+w half half-diamonds-offset)
		       ,half-diamonds-offset))))
     'aquamarine)))




#| (defun create-rounded-rectangle-description (width height)
(create-icon-description
 width height
 (let ((r 13) (d (round (* .2929 13))) )
   `((lines (,r 0) (,(- width r) 0) (arc (,(- width d) ,d)) (,width ,r)
	    (,width ,(- height r)) (arc (,(- width d) ,(- height d))) 
	    (,(- width r) ,height) (,r ,height) (arc (,d ,(- height d))) 
	    (0 ,(- height r)) (0 ,r) (arc (,d ,d)) (,r 0))))))
|#




#| (defun create-action-button-description
(width height
       &optional extra-color-pattern-elements extra-line-drawing-elements)
(create-icon-description
 width height
 `((polychrome
    (pending-indicator . transparent)
    (foreground . foreground)
    . ,extra-color-pattern-elements)
   
   pending-indicator				; filled interior
   (filled-rounded-rectangle
    ;; (0 0) (,width ,height)
    (0 0)
    (width height))
   
   foreground				; border
   (rounded-rectangle
    ;; (0 0) (,width ,height)
    (0 0)
    (width height))

   . ,extra-line-drawing-elements)))
|#

;; Review the need for either of this or the previous after 2.0 Alpha!
;; (MHD 8/14/89)

;pbk
(defun create-action-button-description
    (width height
	   &optional
	   extra-color-pattern-elements
	   extra-line-drawing-elements
	   pending-indicator-override-color? ; the main/center color
	   light-shading-override-color?
	   dark-shading-override-color?)
 (create-icon-description
    width height
    `((polychrome
       (pending-indicator
	 . ,(or pending-indicator-override-color? 'light-gray))
       (g2-icon-light-shading
	 . ,(or light-shading-override-color? 'extra-light-gray))
       (g2-icon-dark-shading
	 . ,(or dark-shading-override-color? 'dark-gray))
       . ,extra-color-pattern-elements)
      pending-indicator
      (solid-rectangle (2 2) ((- width 2) (- height 2)))
      g2-icon-light-shading
      (filled-polygon
       ((0 0) (width 0) ((- width 3) 3) (3 3) (3 (- height 3)) (0 height))
       ((0 0) (width 0) ((- width 3) 3))
       ((3 3) (3 (- height 3)) (0 height))
       ((0 0) ((- width 3) 3) (3 3))
       ((3 3) (0 height) (0 0)))
      g2-icon-dark-shading
      ;; "mystery polygon:"  not sure what this is -- my guess is its an
      ;; artifact! Talk to Dave! (MHD)
;      (filled-polygon
;       ((100 0) (100 40) (97 40) (97 3))
;       ((100 0) (100 40) (97 40))
;       ((97 40) (97 3) (100 0)))
      (filled-polygon
       ((3 (- height 3)) ((- width 3) (- height 3)) ((- width 3) 3) (width 0) (width height) (0 height))
       (((- width 3) (- height 3)) ((- width 3) 3) (width 0))
       ((width height) (3 (- height 3)) ((- width 3) (- height 3)))
       (((- width 3) (- height 3)) (width 0) (width height))
       ((width height) (0 height) (3 (- height 3))))
      .  ,extra-line-drawing-elements)
    'nil
    nil nil nil nil
    nil))


(defun create-arrow-description (direction arrow-width)
  (create-icon-description
    arrow-width arrow-width
    `((polychrome
	(pending-indicator . transparent) (foreground . foreground))
      pending-indicator
      foreground
      (filled-polygon
	. ,(let ((triangle
		   (case direction
		     (left
		      `((,arrow-width ,arrow-width)
			(0 ,(halfw arrow-width))
			(,arrow-width 0)))
		     (up
		      (list (list 0 arrow-width)	    ; See note.
			    (list (halfw arrow-width) 0)
			    (list arrow-width arrow-width)))
;		      `((0 ,arrow-width)
;			(,(halfw arrow-width) 0)
;			(,arrow-width ,arrow-width))
		     (right
		      `((0 0)
			(,arrow-width ,(halfw arrow-width))
			(0 ,arrow-width)))
		     (down
		      `((0 0)
			(,(halfw arrow-width) ,arrow-width)
			(,arrow-width 0))))))
	     `(,triangle ,triangle))))))

;; Right now this is only used by buttons.  The regions are so specified because
;; they are needed that way for button highlighting.  At present, these arrows
;; do not change at all to show that their action is pending. (MHD 8/15/89)

;; Note: This code has been rearranged to step around a bug in the HP 9000/300
;; optimizer. -fmw, 8/22/95





;;;; Checking Validity of Line Drawing Descriptions





;;; `Valid-line-drawing-description-p' takes as arguments width, height, 
;;; and line-drawing-description.

;;; It checks the syntax of line-drawing-description and whether all
;;; points are within bounds.  Note that this is independent of scale
;;; and need only be done once when the icon is installed.  

;;; Valid-line-drawing-description-p returns either t, to indicate that
;;; everything is alright, or nil and, if possible, the first line drawing
;;; element encountered that was not alright.

;;; If the line drawing description is valid, and the icon is polychrome,
;;; valid-line-drawing-description-p also returns region-extrema which is an alist
;;; with elements of the form
;;;   (region . extrema).
;;; Extrema is a quadruple of minimum-x, minimum-y, maximum-x, and maximum-y where
;;; the origin is the top left corner of the icon.  This format is not the same as
;;; the x-offset, y-offset, width, height format used for bounding boxes for
;;; characters (see character descriptions section of FONTS).  The reason that
;;; this can't be used is that the above width and height are computed by
;;; subtracting the maxima from the minima.  Since this is done before scaling,
;;; round-off errors can result when scaling is done.  Thus, to ensure proper
;;; scaling, the extrema must be the exact same workspace coordinates as the
;;; extreme values of the line elements from which they are derived.

;;; The entries on the alist appear in the same order as the regions in the line
;;; drawing description.  This eliminates the need to search to match up these
;;; entries with regions when painting.

;;; The extrema information is useful for deciding the size of the raster needed
;;; for the region.

;; Called in file definitions by create-icon-description-if-valid. ML.



(defvar current-region-minimum-x)
(defvar current-region-minimum-y)
(defvar current-region-maximum-x)
(defvar current-region-maximum-y)



(defun valid-line-drawing-description-p
       (width height line-drawing-description computed-values-plist)
  (let* ((current-region-minimum-x nil)
	 (current-region-minimum-y nil)
	 (current-region-maximum-x nil)		
	 (current-region-maximum-y nil)
	 (polychrome-header?
	   (get-polychrome-header-if-any line-drawing-description))
	 (variable-header?
	   (get-variable-specification-if-any line-drawing-description))
	 (background-header?
	   (get-icon-background-layer-if-any line-drawing-description))
	 (region-extrema (initialize-region-extrema polychrome-header?))
	 (current-region? 'foreground)
	 (stipple-header? (get-icon-stipple-if-any line-drawing-description))
	 (description-elements
	   (get-element-list
	     line-drawing-description
	     polychrome-header?
	     variable-header?
	     background-header?
	     stipple-header?)))
    
  (evaluating-icon-elements (width height (cdr variable-header?) computed-values-plist)
    (loop for description-element in description-elements
	  unless
	    (cond
	      ((atom description-element)	       ; a color or region
	       (when
		 (or (eq description-element 'background)      ; Take out after 2.0!
		     (eq description-element 'transparent)
		     (eq description-element 'foreground)
		     (and polychrome-header?
			  (assq description-element (cdr polychrome-header?))))
		 (when current-region-minimum-x
		   (add-extrema-to-current-region
		     region-extrema current-region? width height
		     current-region-minimum-x current-region-minimum-y
		     current-region-maximum-x current-region-maximum-y))
		 (setq current-region-minimum-x nil
		       current-region-minimum-y nil
		       current-region-maximum-x nil
		       current-region-maximum-y nil)
		 (setq current-region? description-element)
		 t))
	      ((let ((points (cdr description-element)))
		 (evaluating-icon-elements (width height (cdr variable-header?) computed-values-plist)
		  (case (car description-element)
		   (point
		    (when
		      (and (point-p (car points))
			   (null (cdr points)))
		      (update-extrema-for-current-region
			(point-x (car points)) (point-y (car points)))
		      t))
		   ((lines outline)
		    (and (point-p (car points))
			 (cond
			   ((null (cdr points))
			    (update-extrema-for-current-region			
			      (point-x (car points)) (point-y (car points)))
			    t)
			   ((loop with outline-case?
				    = (eq (first description-element) 'outline)
				  with remaining-points = points
				  while remaining-points
				  always
				    (cond
				      ((and (point-p (car remaining-points))
					    (cdr remaining-points)
					    (arc-point-p (car (cdr remaining-points)))
					    (if (cddr remaining-points)
						(point-p (car (cddr remaining-points)))
						outline-case?))
				       ;; prefixed by arc
				       (let ((p1 (first remaining-points))
					     (p2 (second (second remaining-points)))
					     (p3 (if (cddr remaining-points)
						     (third remaining-points)
						     (car points))))
					 (cond
					   ((arc-point-p p3)
					    nil)
					   (t
					    (multiple-value-bind
						(min-x min-y max-x max-y)
						(compute-arc-bounding-box
						  (point-x p1) (point-y p1)
						  (point-x p2) (point-y p2)
						  (point-x p3) (point-y p3))
					      (update-extrema-for-current-region
						min-x min-y)
					      (update-extrema-for-current-region
						max-x max-y))
					    (setq remaining-points (cddr remaining-points))
					    t))))
				      ((and (point-p (car remaining-points))
					    (if (cdr remaining-points)
						(point-p (car (cdr remaining-points)))
						outline-case?))
				       ;; prefixed by line
				       (let ((p1 (car remaining-points))
					     (p2 (if outline-case?
						     (car points)
						     (car (cdr remaining-points)))))
					 (update-extrema-for-current-region
					   (point-x p1) (point-y p1))
					 (update-extrema-for-current-region
					   (point-x p2) (point-y p2)))
				       (setq remaining-points
					     (if outline-case?
						 (cdr remaining-points)	       ; MHD: right????!
						 (cdr remaining-points)))
				       t)
				      ((point-p (car remaining-points))
				       ;; If all that remains is the endpoint of the
				       ;;   last object specified, then remove it -- we're
				       ;;   done.
				       
				       (let ((p1 (car remaining-points)))
					 (update-extrema-for-current-region
					   (point-x p1) (point-y p1)))
				       (setq remaining-points (cdr remaining-points))
				       t)
				      (t nil)))))))
		   ((circle filled-circle)
		    (let ((p1 (first points))
			  (p2 (second points))
			  (p3 (third points)))
		      (when
			(and (=f (length points) 3)
			     (point-p p1) (point-p p2) (point-p p3))
			(multiple-value-bind
			  (min-x min-y max-x max-y)
			    (compute-circle-bounding-box
			      (point-x p1) (point-y p1)
			      (point-x p2) (point-y p2)
			      (point-x p3) (point-y p3))
			  (update-extrema-for-current-region
			    min-x min-y)
			  (update-extrema-for-current-region
			    max-x max-y))
			t)))
		   ((rounded-rectangle		       ; rounded-rectangle, filled-rounded-
		      filled-rounded-rectangle	       ;   rectangle are not for users yet,
		      solid-rectangle)		       ;   but are for action buttons (MHD 8/17/89)
		    (let ((p1 (first points))
			  (p2 (second points)))
		      (when
			  (and (point-p p1)	       ; Added test for solid
			       (point-p p2))	       ;   rectangle. (MHD 8/17/89)
			(update-extrema-for-current-region
			  (point-x p1) (point-y p1))
			(update-extrema-for-current-region
			  (point-x p2) (point-y p2))
			t)))
		   ;; points are not points (and are not used) in next three cases:
		   ((stippled-area)
		    ;; This should not extend the extrema, since no ink is
		    ;; contributed by to its area, only texturing of existing
		    ;; ink in the area.  So just check validity of the element.
		    (let ((stipple (second description-element))
			  (point-1-or-nil (third description-element))
			  (point-2-or-nil (fourth description-element)))
		      (and (stipple-p stipple)
			   (or (null (cddr description-element))
			       (and
				 (point-p point-1-or-nil)
				 (point-p point-2-or-nil))))))
		   ((filled-polygon)
		    (loop for point in (second description-element)
			  do (if (point-p point)
				 (update-extrema-for-current-region
				   (point-x point) (point-y point))
				 (return nil))
			  finally (return t)))

		   ;; Add in image width/height here, if the image exists. -fmw, 12/17/93
		   ;; *** Images are not smart enough to handle region extrema, so, if there is an
		   ;; image in this layer, force this layer to be the size of the whole icon.
		   (image
		    (let* ((extrema-for-image-drawing-element
			     (extrema-for-line-drawing-element
			       description-element
			       (slot-value-list nil nil nil nil)))
			   (scale?  (fourth description-element))
			   (scale-x? (car scale?))
			   (scale-y? (second scale?))
			   (min-x ; (maxf 0
			     (car extrema-for-image-drawing-element))
			   (min-y ;(maxf 0
			     (second extrema-for-image-drawing-element))
			   (max-x ;(minf width
			     (third extrema-for-image-drawing-element))
			   (max-y ;(minf height
			     (fourth extrema-for-image-drawing-element)))
		      (when scale?
			(setf min-x (scalef min-x scale-x?)
			      min-y (scalef min-y scale-y?)
			      max-x (scalef max-x scale-x?)
			      max-y (scalef max-y scale-y?)))
		      
		      (reclaim-slot-value extrema-for-image-drawing-element)
		      (update-extrema-for-current-region min-x min-y)
		      (update-extrema-for-current-region max-x max-y)
		      ;(update-extrema-for-current-region 0 0)
		      ;(update-extrema-for-current-region width height)
		      t))
		   (text
		    (let* ((extrema-for-text-drawing-element
			     (compute-extrema-for-text-drawing-element
			       description-element
			       (slot-value-list nil nil nil nil)))
			   (scale?  (fifth description-element))
			   (scale-x? (car scale?))
			   (scale-y? (second scale?))
			   (min-x ;(maxf 0
			     (car extrema-for-text-drawing-element))
			   (min-y ;(maxf 0
			     (second extrema-for-text-drawing-element))
			   (max-x ;(minf width
			     (third extrema-for-text-drawing-element))
			   (max-y ; (minf height
			     (fourth extrema-for-text-drawing-element)))
		       (when scale?
			(setf min-x (scalef min-x scale-x?)
			      min-y (scalef min-y scale-y?)
			      max-x (scalef max-x scale-x?)
			      max-y (scalef max-y scale-y?)))
		      (reclaim-slot-value extrema-for-text-drawing-element)
		      (update-extrema-for-current-region min-x min-y)
		      (update-extrema-for-current-region max-x max-y)
		      ;(update-extrema-for-current-region 0 0)
		      ;(update-extrema-for-current-region width height)
		      t))

		   (t nil))))))
	    do				
	      #+development
	      (cerror "Return NIL"
		      "Bad Icon Description Element: ~a"
		      description-element)
	      (return (values nil description-element))
	      
	  finally 
	    (when current-region-minimum-x
	      (add-extrema-to-current-region
		region-extrema current-region? width height
		current-region-minimum-x current-region-minimum-y
		current-region-maximum-x current-region-maximum-y))
	    ;; convert to x-offset, y-offset, width, height form
;	    (loop for entry in region-extrema
;		  do
;	      (setf (fourth entry)
;		    (-w (fourth entry) (second entry))
;		    (fifth entry)
;		    (-w (fifth entry) (third  entry))))
;; Not done due to scaling problems.  See above documentation.
	    (return (values t region-extrema))))))

;; Increase use of fixnum arithmetic througout wherever possible!

;; MHD: Consider fixing up maintenence of maximum-x & maximum-y and returning them as
;; additional values.  Alternatively, just flush them.  ML plans to write hard parts
;; (i.e. arcs, polygons, etc.) some time after 2.0 Alpha.



(defun initialize-region-extrema (polychrome-header?)
  (cond ((null polychrome-header?)
	 (gensym-list (gensym-list 'foreground nil nil nil nil)))	 

	((null (cdr polychrome-header?))
	 ;; This case can happen due to a bug in the icon editor. See the note
	 ;; ICON-EDITOR-POLYCHROME-HEADER-BUG, above.  This patch prevents the
	 ;; valid-line-drawing-description-p from crashing, and ends up
	 ;; declaring the line-drawing-description valid.  -fmw, 2/17/95
	 (gensym-list (gensym-list 'foreground nil nil nil nil)))

	(t
	 (loop for region-pair in (cdr polychrome-header?)
	       collect (gensym-list (car region-pair) nil nil nil nil)
		 using gensym-cons))))




(defun add-extrema-to-current-region
    (region-extrema current-region width height
		    minimum-x minimum-y maximum-x maximum-y)
  ;; first clip extrema by bounds of icon
  (setq minimum-x (maxw minimum-x 0)
	minimum-y (maxw minimum-y 0)
	maximum-x (minw maximum-x width)
	maximum-y (minw maximum-y height))
  (let ((entry (assq current-region region-extrema)))
    (cond ((null entry)
	   #+development
	   (cond
	     ((eq current-region 'transparent)
	      ;; always ignore transparent -- we're not sure
	      ;; if this is the right thing, but they seem
	      ;; to be out there in this condition; it would
	      ;; be work to investigate/correct, which is being
	      ;; deferred.  For now this seems not too harmful.
	      ;; (MHD/PBK 4/23/96)
	      )
	     (t
	      ;; This case is probably more serious:
	      (cerror "Ignore it" "The region ~s was not found in ~s"
		      current-region region-extrema))))
	  ((null (second entry))
	   (setf (second entry) minimum-x
		 (third entry)  minimum-y
		 (fourth entry) maximum-x
		 (fifth entry)  maximum-y))
	  (t
	   (setf (second entry) (minw minimum-x (second entry))
		 (third entry) (minw minimum-y (third entry))
		 (fourth entry) (maxw maximum-x (fourth entry))
		 (fifth entry) (maxw maximum-y (fifth entry)))))))





(defun update-extrema-for-current-region (x y)
 (let ((x (or x current-region-minimum-x))   ;pbk (changed in case it is nil)
       (y (or y current-region-minimum-y)))
  (if (null current-region-minimum-x)
      (setq current-region-minimum-x x
	    current-region-minimum-y y
	    current-region-maximum-x x
	    current-region-maximum-y y)
      (setq current-region-minimum-x (minw current-region-minimum-x x)
	    current-region-minimum-y (minw current-region-minimum-y y)
	    current-region-maximum-x (maxw current-region-maximum-x x)
	    current-region-maximum-y (maxw current-region-maximum-y y)))))







;;;; Filled Polygons


;;; A `polygon' is a set of line segments called edges such that:
;;; (1) For some n >= 3, there are points (called verticies) in the XY
;;; plane v1, v2,... vn. (2) There are exactly n edges, and their end points 
;;; are each pair (vi vi+1) as well as the pair (vn v1). The data 
;;; structure which represents a polygon is the list of vertices, and each 
;;; vertex is represented by a list of 2 fixnums which are its coordinates.
;;; We make the further requirement that each edge is of positive
;;; length, which implies that no adjacent pair of points may be
;;; identical, and the first and last points may not be identical.

;;; A polygon is simple if its perimeter does not intersect itself.

;;; Given a simple polygon, an interior point is a point of the plane
;;; which is not on the perimieter, and may not be connected to a remote
;;; point of the plane by any path that does not cross the perimeter.
;;; A filled simple polygon is the polygon union its interior.  We shall
;;; exclude from further consideration non-simple polygons, and simply say
;;; `filled polygon'.

;;; Two aspects of the icon drawing software are dealt with here. (1)
;;; rejecting polygons that are not simple, and (2) representing a
;;; (simple) polygon as a union of triangles that overlap only on their
;;; edges.

;;; A set in Euclidean n space is convex iff every line segment
;;; connecting two points of the set lies entirely within the set.
;;; In the case of the set being a filled polygon in the XY plane,
;;; it is convex iff no interior angle exceeds 180 degrees. All convex
;;; polygons are simple, but not visa-versa. A vertex whose interior
;;; angle exceeds 180 degrees is called a concave vertex.

;;; To determine if a polygon is simple, first check to see
;;; if it is convex, which is a cheaper test. If not, the polygon
;;; is still simple if no pair of non-adjacent edges intersect.

;;; document how decomposition is done!!!



;;; The function `create-filled-polygon-icon-description-element' returns a
;;; FILLED-POLYGON icon description element, i.e., by decomposing 

;;; This may be used at read time in order to construct polygons in
;;; system-defined icon descriptions.
;;;
;;; For example, icon-description slot of edit-cursor is defined as
;;;
;;;
;;;  (icon-description
;;;    (:funcall-at-load-time
;;;      create-icon-description
;;;      12 8
;;;      (#.(create-filled-polygon-icon-description-element
;;;	      '((0 6) (5 0) (10 6) (8 6) (5 2) (2 6))))))

(defun create-filled-polygon-icon-description-element (simple-polygon)
  `(filled-polygon
    ,simple-polygon
    . ,(decompose-polygon simple-polygon 'cons)))




;;; Sense-of-vector-angle takes two vectors as arguments, the
;;; first being from the origin to x1,y1, and the second from
;;; the origin to x2,y2. The value is 0 if the vectors are aligned
;;; or are in oposition. The value is positive if the smaller arc
;;; from the first vector to the second is in the clockwise direction,
;;; and negative if this arc is in the counterclockwise direction.
;;; The arguments and the value are fixnums. 

;;; Method: This computes the cross-product of two vector.

;;; Note that to assure that the product of fixnums is a fixnum on all
;;; platforms, the size should not exceed 12 bits!!

;Added by SoftServe for this case only
;Another ways to fix the macros behaviour failed
(defvar global_temp_1 nil)
(defvar global_temp_2 nil)
(defvar global_temp_3 nil)

(defun sense-of-vector-angle (x1 y1 x2 y2)
  (setq global_temp_1 (* x1 y2))
  (setq global_temp_2 (* x2 y1))
  (setq global_temp_3 (- global_temp_1 global_temp_2))
    (progn
      (cond ((= global_temp_3 0) 0)
	    ((< global_temp_3 0) -1)
	    (t +1))));)

;end of SoftServe changes

;; This is only called when compiling a new icon description, so speed is
;; probably not an issue.



;;; Lines-intersect-p is true  (non-nil) if the line segment from
;;; x1,y1 to x2,y2 intersects the line segment from x3,y3 to x4,y4.
;;; It is assumed that both line segments are of positive length.

;;; Method: If either the x or y extents do not overlap, then the line
;;; segments cannot intersect. If both extents overlap, we test each
;;; line segment to see if it intersects the extension of the other
;;; line in either direction. (How to do this described below.) The line
;;; segments in fact intersect if and only if each intersects the extension
;;; of the other. Proof by cases: (i) The line segments lie on parallel
;;; but different lines: They do not intersect, and neither intersects the
;;; extension of the other. (2) The segments lie on the same parallel
;;; line: They will always intersect each others extension. But they will
;;; intersect iff their extents overlap which we have already established.
;;; (3) The segments lie on intersecting lines: They intersect iff each
;;;  intersects the extension of the other.

;;; To determine if the (infinite) line determined by points p,q 
;;; intersects the line segment r,s; find the sense of the angles
;;; qp-qr and qp-qs. There is an intersection if either sense is 0,
;;; or one is positive and the other negative.

(defun lines-intersect-p (x1 y1 x2 y2 x3 y3 x4 y4)
  (and
    ;; They do not have separate extents.    
    (if (<=f x1 x3)
	(>=f (maxf x1 x2) (minf x3 x4))
	(>=f (maxf x3 x4) (minf x1 x2)))
    
    (if (<=f y1 y3)
	(>=f (maxf y1 y2) (minf y3 y4))
	(>=f (maxf y3 y4) (minf y1 y2)))   
    
    ;; Each intersects the path of the other
    (let ((s1 (sense-of-vector-angle
		(-f x2 x1) (-f y2 y1) (-f x3 x1) (-f y3 y1)))
	  (s2 (sense-of-vector-angle
		(-f x2 x1) (-f y2 y1) (-f x4 x1) (-f y4 y1))))
      
      (and (or (and (>=f s1 0) (<=f s2 0))
	       (and (<=f s1 0) (>=f s2 0)))

	   ;; Postpone this computation until needed.
	   (let ((s3 (sense-of-vector-angle
		       (-f x4 x3) (-f y4 y3) (-f x1 x3) (-f y1 y3)))
		 (s4 (sense-of-vector-angle
		       (-f x4 x3) (-f y4 y3) (-f x2 x3) (-f y2 y3))))
	     
	     (or (and (>=f s3 0) (<=f s4 0))
		 (and (<=f s3 0) (>=f s4 0))))))))





;; convex-polygon-p is true if its argument is convex, else it is
;; nil. The argument must be a polygon with at least 3 sides, and
;; no side may be of length 0.

;; Method: Iterate over all angles, classifying them as right
;; bending, left bending or straight. If there are both left and right
;; angles, it is not convex. Note that to iterate over angles, p1,p2
;; and p3 are initially, the first 3 points of the list, and finally
;; the last, first and second.

;; Does not work. See comment before simple-polygon-p.

;(defun convex-polygon-p (polygon)
;  (loop with left = 0
;	with right = 0
;	;; Iterate over triples of a list, wrapping around 
;	for tail on polygon
;	for p1 = (first tail)
;	for p2 = (if (null (cdr tail))
;		     (first polygon) (second tail))
;	for p3 = (cond ((null (cdr tail)) (second polygon))
;		       ((null (cddr tail)) (first polygon))
;		       (t (third tail)))
;	for x1 = (first p1)
;	for y1 = (second p1)
;	for x2 = (first p2)
;	for y2 = (second p2)
;	for x3 = (first p3)
;	for y3 = (second p3)
;	for sense = 
;	    (sense-of-vector-angle
;	      (-f x2 x1) (-f y2 y1) (-f x3 x2) (-f y3 y2)) doing
;    (cond
;      ((>f sense 0) (incff right))
;      ((<f sense 0) (incff left)))
;	finally
;	  (return (or (=f 0 left) (=f 0 right)))))



;;; Simple-polygon-p is true if the polygon consists of edges of
;;; positive length, and if the perimeter does not intersect itself.

;;; Method: After first testing for all sides of finite length, 
;;; iterate over each side, testing to see that the side
;;; does not intersect any non-adjacent side.

;; Originally, this tested to see if it was convex, and if so, concluded
;; that the polygon was simple. This was for reason of efficiency.
;; But convex-polygon-p has a bug in that a polygon that only makes
;; turns to the right when traversed in a certain direction might
;; make two or more intersecting loops before meeting its starting point.
;; Such a polygon is neither simple nor convex. If convex-polygon-p
;; is to work, it must detect this either by testing for intersecting
;; lines, or by summing the angles of all the turns. 



;;; Simple-polygon-p does not cons.

(defun simple-polygon-p (polygon)

  (and
    ;; All sides of positive length.
    (loop for tail on polygon
	  for p1 = (first tail)
	  for p2 = (if (cdr tail) (second tail) (first polygon))
	  never
	  (and (=f (point-x p1) (point-x p2)) (=f (point-y p1) (point-y p2))))
    
;      (convex-polygon-p polygon)

    ;; If not convex, length >= 4. No need to test that.
    (loop with length = (length polygon)
	  for i from 1 to (-f length 2)
	  for tail-1 on polygon
	  for p1 = (first tail-1)
	  for p2 = (second tail-1)
	  for x1 = (point-x p1)
	  for y1 = (point-y p1)
	  for x2 = (point-x p2)
	  for y2 = (point-y p2)
	  always
	  
	  (loop for j from (+f i 2) to
		  ;; The exception is not to test the first and
		  ;; last lines because they are adjacent by wraparound.
		      (if (=f i 1) (-f length 1) length) 
		  for tail-2 on (cddr tail-1)
		  for p3 = (first tail-2)
		  for p4 = (if (cdr tail-2)
			       ;; Wraparound if necessary
			       (second tail-2) (first polygon))
		  for x3 = (point-x p3)
		  for y3 = (point-y p3)
		  for x4 = (point-x p4)
		  for y4 = (point-y p4) 
		  never (lines-intersect-p x1 y1 x2 y2 x3 y3 x4 y4)))))



;;; Clockwise-polygon-p is true if its argument (a simple
;;; polygon) has its vertices ordered clockwise. Note that
;;; reversing the argument complements the value of this function.

;;; Method: Let Vi be the first vertex with the least x, and
;;; the one of these with the least y. The angle Vi-1, Vi, Vi+1
;;; cannot be straight, and bends left iff the polygon is clockwise.

(defun clockwise-polygon-p (polygon)
  (loop with node-num = 1
	with min-x-value = most-positive-fixnum
	with min-y-value = min-x-value
	with p1
	with p2
	with p3
	with x1
	with y1
	with x2
	with y2
	with x3
	with y3
	for vertex in polygon
	for x-value = (point-x vertex)
	for y-value = (point-y vertex)
	for n from 1 doing
    (when (or (<f x-value min-x-value)
	      (and (=f x-value min-x-value)
		   (<=f y-value min-y-value)))
      (setq node-num n)
      (setq min-x-value x-value) 
      (setq min-y-value y-value))
    finally
      (setq p1 (if (=f node-num 1)
		    (first (last polygon))
		    (nth (-f node-num 2) polygon)))
      (setq p2 (nth (-f node-num 1) polygon))
      (setq p3 (if (=f node-num n)
		    (first polygon)
		    (nth node-num  polygon)))
      (setq x1 (point-x p1))
      (setq y1 (point-y p1))
      (setq x2 (point-x p2))
      (setq y2 (point-y p2))
      (setq x3 (point-x p3))
      (setq y3 (point-y p3))

      (return
	(>=f (sense-of-vector-angle
	       (-f x2 x1) (-f y2 y1) (-f x3 x2) (-f y3 y2))
	     0))))







;;; Decompose-polygon, given a simple polygon, decomposes it into a list of
;;; triangles. The given polygon is not modified, nor will the value reference
;;; any conses in the polygon.

;;; If cons-function? is provided, it should be an equivalent of CONS,
;;; phrase-cons, etc.  If it is nil, phrase-cons is used.

(defun decompose-polygon (polygon &optional cons-function?)
  (decompose-polygon-1
    (if (not (clockwise-polygon-p polygon))
	(loop with result = nil		; reverses polygon
	      for element in polygon
	      do (setq result
		       (funcall
			 (or cons-function? 'phrase-cons)
			 element result))
	      finally
		(return result))
	polygon)
    (or cons-function? 'phrase-cons)))

(defun decompose-polygon-1 (clockwise-polygon cons-function)
  (if (=f (length clockwise-polygon) 3)
      (funcall cons-function clockwise-polygon nil)
      (multiple-value-bind (poly-1 poly-2)
	  (divide-polygon clockwise-polygon cons-function)
	(nconc
	  (decompose-polygon-1 poly-1 cons-function)
	  (decompose-polygon-1 poly-2 cons-function)))))



;;; Divide-polygon, given a simple polygon of four or more sides
;;; returns as values two polygons obtained by drawing a line
;;; between some non-adjacent pair of vertices such that the line
;;; is interior to the original polygon. The argument must be traversed
;;; clockwise, and both values will be also.

;;; Method: Iterate over pairs of non-adjacent vertices vi, vj. Test the chord
;;; drawn between them, and discard if it intersects any edge not drawn to
;;; or from vi or vj. If this test is met, form the two polygons (vi ... vj), and
;;; (vj ... vn, v1 ... vi). Unless both of these are traversed clockwise,
;;; the chord is exterior, and this pair of vertices should be discarded. When one
;;; meets the test, return the polygons as values.

;;; Cons-function should be a symbol, either CONS or its equivalent.

(defun divide-polygon (polygon cons-function)
  ;; Iterate over the indices of pairs of non-adjacent vertices.
  (loop named sue with length = (length polygon)
	for i from 1 to (-f length 2)
	for tail-1 on polygon
	for v1 = (car tail-1)
    	for x1 = (point-x v1)
	for y1 = (point-y v1) doing
    
    (loop with poly-1 and poly-2
	  for j from (+f i 2) to length
	  for tail-2 on (cddr tail-1)
	  for v2 = (car tail-2)
	  for x2 = (point-x v2) 
	  for y2 = (point-y v2) do

      (when
	(and
	  ;; The first and last are adjacent by wraparound. Filter them out.
	  (or (/=f i 1) (/=f j length))
	  
	  ;; Test for the chord not intersecting any other edge.
	  ;; Iterate over all edges of polygon.
	  (loop for tail-3 on polygon
		for k from 1
		for v3 = (first tail-3)
		for v4 = (if (cdr tail-3) (second tail-3) (first polygon))
		never		    
		  (and
		    ;; Filter out edges touching p1 or p2.
		    (if (=f i 1) (/=f k length) (/=f k (-f i 1)))
		    (/=f k i)
		    (/=f k (-f j 1))
		    (/=f k j)
		    (lines-intersect-p
		      x1 y1 x2 y2
		      (point-x v3) (point-y v3) (point-x v4) (point-y v4)))))
	
	;; Form two polygons
	(setq poly-1
	      (loop for r from (-f i 1) to (-f j 1)
		    nconcing (funcall cons-function (nth r polygon) nil)
		    ;; was: collecting (nth r polygon) using phrase-cons  ; (MHD 7/21/93)
		    ))
	(setq poly-2
	      (loop for r from (-f j 1) to (+f (-f i 1) length)
		    nconcing (funcall cons-function (nth (mod r length) polygon) nil)
		    ;; was: collecting (nth (mod r length) polygon) using phrase-cons  ; (MHD 7/21/93)
		    ))
	(if (and (clockwise-polygon-p poly-1)
		 (clockwise-polygon-p poly-2))

	    (return-from sue (values poly-1 poly-2)))))))



;;; `override-icon-description-for-system-defined-class'
;;; This function should ONLY be called at load time.

(defun override-icon-description-for-system-defined-class
    (system-defined-class icon-description &optional stub-feature?)
  (current-system-case
    (ab
      (funcall 'override-icon-description-for-system-defined-class-ab
	       system-defined-class icon-description stub-feature?))
    (t
      (case current-system-being-loaded
	(ab
	 (funcall 'override-icon-description-for-system-defined-class-ab
		  system-defined-class icon-description stub-feature?))
	(t
	 (error "Can only override-icon-descriptions in ab"))))))


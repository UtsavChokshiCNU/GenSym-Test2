;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module DISPLAYS

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Andreas Hofmann and Jim Allard



(declare-forward-reference send-ws-representations-item-virtual-attribute-change
			   function);; EVENTS-G2



;; Notes

;; Currently, the names slot is not shown in the attribute table of displays.
;; Thus, displays can't be given names.  Consider allowing this in the 
;; future.  Actually, the best name to give is the expression to display.
;; Jim has suggested allowing the user to specify a shortened version of
;; this so that readouts don't get too big.

;; Display-evaluation-should-not-trigger-variable-evaluation? was a proposed
;; slot for displays (currently not used).  The same effect is achieved by
;; using "the current value of" expression so this slot will probably never
;; be needed.

;; Graphs and digital clocks don't currently call get-new-value-for-display
;; and therefore don't use wake up stuff at all, even though they have the
;; slots.  Note also that for these kinds of displays, tracing and breakpoint
;; capability is not used for the same reason.

;; Originally, readouts were implemented as text boxes.  This was changed
;; before release 1.0 to the current readout table implementation.  The
;; def-substitute-for-old-class that converts readouts to readout-tables
;; was removed 8/8/89 because a change was made about nine months prior
;; to this that caused it not to be called, and because it is highly
;; unlikely that any readouts exist in any kbs.



;; To do

;; Rewrite drawing utilities to use type declared arithmetic; much of it uses
;; untyped arithmetic now.

;; Consider updating displays by put-current-value and scheduling clearing
;; based on expiration time.  This would be an alternative style to the update
;; interval mechanism.  Would be more opportunistic and would always show the
;; current value.

;; Get rid of show-expressions-displayed? slot or do something with it.

;; Consider implementing special function for updating readouts (rather than
;; using change-slot-value), at least if the subtable is not being displayed.
;; Do some tests to see if this would improve performance substantially.
;; Also, Jim had a suggestions about displays of variables in attribute slots
;; of objects.  Currently, when a subtable of an object is put up, a 
;; snapshot of values of any variables in attribute slots is taken and
;; the values are shown.  It would be better to update these values as they
;; change, rather than taking a snapshot.

;; If a special function for updating readouts is implemented, could probably
;; get away with not putting type into slot.  Also, rather than allocating
;; and reclaiming cons, consider keeping it and setf'ing cars and cdrs.
;; alternatively, could have two slots in class.

;; Since there is no slot value reclaimer and no cleanup method for readouts,
;; (slot putter does reclamation) do conses for values get lost if deleted while
;; running?  Consider writing a memo on slot value compilers, slot putters,
;; reclaimers, and installation.  When to use what.

;; (low priority)
;; Consider displaying numerical type (such as units) in display along with number
;; (see design book notes for 8/12/88).

;; (low priority)
;; Do benchmark on readout overhead some time.  Use agh>sim-bench-2 and percentage
;; time spent in simulator.  Try with 100 readouts.  Do this with graphs also.

;; (low priority)
;; Convert look-up slots to vector slots.

;; In get-new-value-for-display, if using simulated values, the type may not
;; be numeric if formulas are used.  Check type.  This is a general issue 
;; with the simulator.

;; (low priority)
;; The slot display-evaluation-should-use-simulated-values is omitted for 
;; digital clocks.  Consider putting it in, aliasing it to 
;; "show simulated time?", and letting it control whether simulation-time
;; or gensym-time is displayed.

;; (low priority)
;; When a digital clock is not active, it just displays "time".
;; Consider showing the time even when the digital clock is not active.
;; The problem with this is that the time will not increment while not active
;; and merely reflects the time the digital clock was put up or the time
;; that the system was last reset.

;; (high priority)
;; Improve dials by making needle with more and smaller points.
;; Put in some solid areas by drawing solid rectangles.

;; Consider using leave-text-representation-as-a-single-line? mechanism for 
;; label boxes of meters and dials
;; (see also slot value writer for value-for-readout-table).

;; Concerning rectangle-visible-p and other mechanisms for deciding whether to
;; update the display:
;; 1.  Currently, it seems that rectangle-visible-p returns nil even if the
;; display is only partly off the screen.  
;; 2.  Rectangle-visible-p should return nil if rectangle is completely under
;; another window.
;; 3.  Something should prevent update if display is too small.

;; Consider implementing a define-display macro which defines the various
;; activate and other macros for displays.

;; Should be able to edit expression from readout table itself.

;; Consider displaying units on readout tables.  Mike says print-constant
;; (used extensively in GRAMMAR2) takes care of this.

;; Readout tables have replaced readouts on menus.  Conversion of readouts to readout
;; tables is handled below in this file.

;; Consider providing capability where the expression on the left hand side of the
;; readout table is just a label for a longer designation.  This is desireable since 
;; readout tables want to be squeezed into a compact area.

;; Some of the format information in meters and dials (such as pointer-arrowhead-size)
;; should probably go into format frames as is the case with graphs.  It depends on
;; what extent we allow these to be user editable.

;; Make expression grammar for displays like that for simulator
;; (using unique designations).

;; Nice formatting of labels with scale and offset, a la graphs.

;; Remove with-painless-errors wrapper if update for readouts when TI bug is fixed.

;; During installation, need to set up better link between variables and
;; their displays since put-current-value for a variable might want to
;; invoke update of displays for that variable.  Change display-frame?
;; slot in variable to displays-for-this-variable?

;; Consider abstracting activation method definitions for displays by
;; making a def-activation-method-for-display form.

;; Consider abstracting the common portions of the update functions
;; for the various displays.

;; Decide to what extent rulings for dials and meters are specifiable by
;; editing parameter slots of dials and meters.  Implement the
;; appropriate installation functions.

;; Put this into the ab system.

;; Work on color, pointer shape, and ruling formats
;; function to determine standard ruling
;; labels for dials


;;; DISPLAYS contains dials, meters, readouts, and other animated displays.

;; Graphs are still in their own separate file.

;; Dials have many similarities to "graphs" although they are much simpler.

;; The reason for making dial-rulings and dial-pointers be subblocks of
;; dials is so that they can easily be updated independently of
;; redrawing the whole entity.  A way to do this if they weren't
;; subblocks would be to write special functions for dials analogous to
;; draw-only-data... in "graphs".  Think about maybe making plots
;; subblocks of graphs.

;; For now, drop format frames for dials, at least until a need for them
;; is established.  Dials are simple enough that they don't need format
;; frames.  The user should be able to enter what format information is
;; needed into the frame itself.  A hierarchy of dial classes is also
;; possible.



;;;; Display of Simulated and Inferred Values

;;; Readout-tables can display values of the following type: number, symbol,
;;; truth-value, and text.  These types are the types checked by the
;;; inference engine (value, expiration, and type are the three values
;;; returned by datum-evaluate).  Meters, dials, and graphs only display
;;; numeric values.  Runtime messages are posted if there is an attempt
;;; to display some other kind of value.

;;; 1.  It is possible to display both simulated and inferred values
;;; at user specified intervals and in a variety of formats.
;;; Update intervals are specified in the various display frames.

;;; 2.  Display update is scheduled as a task, divorced from the simulator
;;; and the inference engine.  However, it is also be possible for 
;;; put-current-value to invoke display updates.  This would 
;;; cause the display to be updated when the new value arrives instead of 
;;; only when the scheduled task executes.  This capability could be used
;;; simultaneously with the scheduled task.  Consider providing the same
;;; capability for the simulator, so that it can update some variables 
;;; directly instead of only waiting for the scheduled task.

;;; 3.  For simulated values, values are always current and thus can always be
;;; displayed.

;;; 4.  For inferred values, the display should reflect what the
;;; inference engine knows.  Actually, displays will evaluate their
;;; display expressions and can cause chaining to get values.
;;; This can be prevented by using "the current value of".


;; The format of the display is a separate, knowledge base issue.
;; The user should be able to define various table formats for display of variables,
;; get instances of these tables, and place them anywhere on the schematic.
;; This information would all be saved in the knowledge base.
;; The variable-display-frame for the variable contains a list of the cells
;; and blocks to be updated.  This list has to be set up as part of installation.
;; These issues are deferred for now and belong in another file.  "Variables"
;; contains only the actual display functions and assumes that the required 
;; format information and tables somehow exist in the knowledge base and that
;; the installation methods have correctly installed the variable-display-frame
;; if one exists.

;; Display format should be very flexible and user defineable.
;; One scheme would be to let the user say something like:
;; 
;; "Give me a {n X m} table,
;; 1st row has cells for variable1, variable2 ...
;; 2nd row ...
;; Use simulated value for variable 1 and update display
;; every k seconds..."
;; 
;; The user could then place this table using the mouse.



(def-absent-slot-putter parent-meter-for-marker
			(marker-for-meter slot-value)
  marker-for-meter slot-value)
(def-absent-slot-putter parent-meter-for-ruling
			(ruling-for-meter slot-value)
  ruling-for-meter slot-value)
(def-absent-slot-putter parent-dial-for-pointer
			(pointer-for-dial slot-value)
  pointer-for-dial slot-value)
(def-absent-slot-putter parent-dial-for-ruling
			(ruling-for-dial slot-value)
  ruling-for-dial slot-value)






;;;; Activation of Displays




;;; It is assumed here that all display classes have update functions and
;;; clear functions.  These are defined using define-update-display-function
;;; and define-clear-display-function.

;;; The assumption above is being changed.  Some displays are being moved over
;;; to use the cells facility as their interface to the stack evaluation
;;; environment.  They are dials, meters, and readout-tables (and maybe
;;; digital-clocks).  These will not have update-display or clear-display
;;; methods, and instead will receive their updates through the cell which is
;;; managing the value to show.  Graphs (and maybe digital clocks) will retain
;;; these methods.  -jra 8/14/91

;; Consider abstracting the post-menu method definitions, since they are
;; somewhat similar, by defining define-display-post-menu-method.  Consider
;; abstracting all this further by implementing a define-display which
;; completely defines a kind of display.

(defmacro define-activate-method-for-entity-display
	  (display-class &body body)
  `(def-class-method activate-subclass-of-entity (,display-class)
     ,@body
     (let ((cell-array? (cell-array ,display-class)))
       (when cell-array?
	 (activate-g2-cell-array cell-array?)))))

(defmacro define-activate-method-for-cell-based-display
	  (display-class &body body)
  `(def-class-method activate (,display-class)
     ,@body
     (let ((cell-array? (cell-array ,display-class)))
       (when cell-array?
	 (activate-g2-cell-array cell-array?)))
     (funcall-superior-method ,display-class )))

(defmacro define-activate-method-for-display
    (display-class &body body)
  `(def-class-method activate (,display-class)
     (with-temporary-creation
	 activate
       (with-future-scheduling
	   ((display-update-task? ,display-class)
	    (display-update-priority ,display-class)

	    (+e (managed-float-value (clock-get current-g2-time))
		(if (fixnump (display-wait-interval ,display-class))
		    (coerce-fixnum-to-gensym-float
		      (display-wait-interval ,display-class))
		    (managed-float-value
		      (display-wait-interval ,display-class))))
	    (cond ((fixnump (display-update-interval ,display-class))
		   (coerce-fixnum-to-gensym-float
		     (display-update-interval ,display-class)))
		  ((managed-float-p (display-update-interval ,display-class))
		   (managed-float-value
		     (display-update-interval ,display-class)))
		  (t -1.0)))
	 (,(function-name-for-method display-class 'update-display)
	   ,display-class nil nil nil)))
     (funcall-superior-method ,display-class)
     ,@body))



;; Should be modified to allow displays to have capabilities, perhaps.
;; Check with current definition of activate-for-entity, to note changes!!!
;; Plese discuss with me. ML, 4 December 87

;; Note that this doesn't define an update function.  It does, however,
;; assume that one exists.

;; Modified by ML on 5 July 87 to set the two flags as appropriate, and test for frame status.

(defmacro define-deactivate-method-for-entity-display
	  (display-class &body body)
  `(def-class-method deactivate-subclass-of-entity (,display-class)
     ,@body
     (let ((cell-array? (cell-array ,display-class)))
       (when cell-array?
	 (deactivate-g2-cell-array cell-array?)))))


(defmacro define-deactivate-method-for-cell-based-display
	  (display-class &body body)
  `(def-class-method deactivate (,display-class)
     ,@body
     (let ((cell-array? (cell-array ,display-class)))
       (when cell-array?
	 (deactivate-g2-cell-array cell-array?)))
     (funcall-superior-method ,display-class)))


(defmacro define-deactivate-method-for-display
	  (display-class &body body)
  `(def-class-method deactivate (,display-class)
     (cancel-task (display-update-task? ,display-class))
     (cancel-task (task-for-display-continuation? ,display-class))
     (funcall-method 'clear-display ,display-class)
     (setf (display-up-to-date? ,display-class) nil)
     (loop for variable in (things-this-display-is-interested-in ,display-class)
	   do
       (remove-request-for-variable-value variable ,display-class))
     (reclaim-eval-list-macro (things-this-display-is-interested-in ,display-class))
     (setf (things-this-display-is-interested-in ,display-class) nil)
     ,@body
     (funcall-superior-method ,display-class)))

;; Note that this doesn't define a "clear" function.  It does, however,
;; assume that one exists.

;; May need a reset method at some point.



;;; `update-cell-based-display' and `update-display' are methods defined on
;;; displays, They are actually defined indirectly using
;;; define-update-display-function, or define-cell-based-update-display-function
;;; discussed-below. Update-display has an additional arg,
;;; update-even-if-not-showing?, which, if true, forces an update even if the
;;; display is not showing, as determined by rectangle-visible-p.

(def-generic-method update-display (display-class update-even-if-value-unchanged? wake-up?
						  update-even-if-not-showing?)
  )

(def-generic-method update-cell-based-display (display-class
						old-cache?
						new-cache?
						update-even-if-value-unchanged?)
  )





;;; `define-update-display-function' creates the methods
;;; update-display-for-graph and update-display-for-digital-clock.
;;; Displays of this type are updated if they are
;;; (showing or update-even-if-not-showing) AND
;;; (active or runs-while-inactive).

;;; `define-cell-based-update-display-function' creates methods for cell-based
;;; displays, which include readout-tables, meters and dials.

;;; The display-up-to-date? slot was used to indicate to the draw method (when
;;; the display is eventually drawn), that it is not up to date so that it will
;;; be drawn in such a way as to indicate this clearly.  Update even if value
;;; unchanged? is useful when the format of the display is changed in some way.

;; display-up-to-date? is slated for obselecence, because we want to be able to
;; do an update command when hidden, and when hidden things will get out of date.
;; lgibson 4/29/97

;;; Note that graphs and digital-clocks use the update-display function, and
;;; that all remaining displays (dials, meters, and readout-tables) are based on
;;; cells and so use its update mechanism, which is based on receiving calls to
;;; the expression-cell-updated method on any event which requires drawing.
;;; -jra 8/14/91, updated lgibson 4/29/97



(defmacro define-update-display-function
    (display-class &body body)
  `(def-class-method update-display 
       (,display-class update-even-if-value-unchanged? wake-up?
		       update-even-if-not-showing?)
     update-even-if-value-unchanged?   ; May not be used by all update methods
     wake-up?
     (when (and (or (active-p ,display-class)
		    (runs-while-inactive-p ,display-class))
		(or update-even-if-not-showing?
		    (rectangle-visible-p ,display-class)))
       (with-temporary-gensym-float-creation ,display-class ,@body))))


(defmacro define-cell-based-update-display-function
	  (display-class &body body)
  `(progn
     (def-class-method expression-cell-updated
		       (,display-class g2-cell-array index old-cache?
			new-cache?)
       (declare (ignore g2-cell-array index))
       (,(function-name-for-method display-class 'update-cell-based-display)
	,display-class
	old-cache? new-cache?
	nil))    
     (def-class-method update-display
		       (,display-class update-even-if-value-unchanged? wake-up?
				       update-even-if-not-showing?)
       (declare (ignore wake-up?))
       update-even-if-not-showing? ; maybe someday could use this
       (let ((cached-value?
	       (get-cached-value-for-cell-based-display ,display-class)))
	 (,(function-name-for-method display-class 'update-cell-based-display)
	  ,display-class cached-value? cached-value?
	  update-even-if-value-unchanged?)))

     ;; This creates the methods update-cell-based-display-for-readout-table,
     ;; update-cell-based-display-for-meter, update-cell-based-display-for-dial.

     (def-class-method update-cell-based-display
		       (,display-class old-cache? new-cache?
			update-even-if-value-unchanged?)
       update-even-if-value-unchanged?		; Not always used.
       (with-temporary-gensym-float-creation ,display-class ,@body))
     (def-class-method initialize (,display-class)
       (funcall-superior-method ,display-class))
     ))






;;; The function `get-cached-value-for-cell-based-display' takes a display
;;; frame and returns the currently cached display value (if any) for that
;;; display.  It does this by finding the cell for the display and fetching its
;;; cached value.

(defun get-cached-value-for-cell-based-display (display-frame)
  (let ((cell-array? (cell-array display-frame)))
    (when cell-array?
      (get-expression-cell-cache cell-array? 0))))




;;; 'Clear-display' is a method defined for all displays.

(def-generic-method clear-display (clear-display)
  )



;;; `define-clear-display-function' is used to define the clear-display method of
;;; a display

(defmacro define-clear-display-function
	  (display-class &body body)
  `(def-class-method clear-display (,display-class)
     ,@body))



;;; All display frames have a standard set of slots...

(define-slot-alias show-simulated-values display-evaluation-should-use-simulated-values?
  readout-table)
(define-slot-alias show-simulated-values display-evaluation-should-use-simulated-values?
  dial)
(define-slot-alias show-simulated-values display-evaluation-should-use-simulated-values?
  meter)
(define-slot-alias show-simulated-values display-evaluation-should-use-simulated-values?
  graph)




;;;; Reclamation of managed number slots.


(defmacro define-reclaimer-for-managed-number-slot (slot-name)
  `(def-slot-value-reclaimer ,slot-name (value frame)
     (declare (ignore value))
     (reclaim-managed-number-or-value (,slot-name frame))))

;; Reclaim-managed-number-or-value puts nil into its place argument.


(defmacro define-reclaimers-for-managed-number-slots
	  (&rest slot-names-with-managed-numbers)
  `(progn ,@(loop for slot-name in slot-names-with-managed-numbers
		  collecting `(define-reclaimer-for-managed-number-slot
				,slot-name))))



;;;; Overview of Dials




;;; A dial is an entity.  It has its own class definition.  It can be used to
;;; display a data value such as the current value of a variable.  Unlike
;;; graphs, rulings for dials are not calculated automatically; they are
;;; completely user specified.  Also, the rulings are fixed; they are not
;;; recalculated depending on the data.  There are a wide variety of format
;;; options for dials including: ruling, size, display drawing, number of
;;; pointers, colors, labels, whether pointers should wrap around, etc.  The
;;; pointers are analogous to the plots in graphs.

;;; Unlike a graph, a dial is an entity.  It has an iconic description but not
;;; necessarily a name.  Rulings and pointers are subblocks of the dial.  Ask
;;; Lowell if these should maybe be put in slots of a dial other than the
;;; subblocks slot and handled directly.

(def-class (dial (item entity) (foundation-class dial) define-predicate
		 (class-export-comment "Shares some slot names w/Meter"))

  (icon-description
    (:funcall-at-load-time
      create-icon-description
      120 120
      (
       ;; Converting system icons to polygons/solid-rectangles JED 8/11/93
;       (outline (0 0) (120 0) (120 120) (0 120))
;       (outline (1 1) (119 1) (119 119) (1 119))
       (solid-rectangle (0 0) (120 1))
       (solid-rectangle (0 1) (1 119))
       (solid-rectangle (119 1) (120 119))
       (solid-rectangle (0 119) (120 120))
       (circle (5 60) (60 5) (115 60))
       (circle (6 60) (60 6) (114 60)))))

  (display-update-task? nil vector-slot system do-not-save)
  (task-for-display-continuation? nil vector-slot system do-not-save)

  ;; should the icon description be specified somehow in the format frame?
  ;; Or should the user simply make more specific classes of dials with
  ;; different icon descriptions.  Go with the latter for now.

  (data-exists-for-dial-p nil vector-slot system)	; nil ok? (LH)

  ;; need slots for color, format for marker, etc.

  (ruling-low-value-angle
    180 vector-slot system)
  (ruling-high-value-angle
    0 vector-slot system)
  (number-of-marks-for-dial
    5 vector-slot system)
  (dial-radius
    60 vector-slot system)
  (dial-x-center
    60 vector-slot system)
  (dial-y-center
    60 vector-slot system)
  (length-of-dial-pointer
    40 vector-slot system)
  (length-of-ruling-markers 
    10 vector-slot system)

  (low-value-for-dial-ruling
    0.0 (type dial-ruling-parameter) vector-slot system user-overridable)
  (high-value-for-dial-ruling
    nil   ; (type number?)  temporarily disabled
    vector-slot system)
  (increment-per-dial-ruling
    0.25 (type dial-ruling-parameter) vector-slot system user-overridable)

  (desired-low-value-for-dial-ruling
    0.0
    ; (type number)   temporarily disabled
    vector-slot system)
  (desired-high-value-for-dial-ruling
    1.0
    ; (type number)   temporarily disabled
    vector-slot system)
  (function-to-determine-standard-dial-ruling
    determine-standard-dial-ruling vector-slot system)

  (pointer-arrowhead-size
    5 vector-slot system)  ; if nil, no arrowhead
  (distance-from-mark-to-label-center
    12 vector-slot system)

  ;; The following slots are the same as the ones for readouts.
  ;; If these become vector slots at some point, give them
  ;; unique names.

  (expressions-to-display
;    nil (type list-of-display-expressions text) lookup-slot system)
    nil (type display-expression text) lookup-slot system select-changes)
  ;; Allow list-of-display-expressions when dial can display more than one
  ;; expression (using more than one pointer).

  (variables-for-expressions-to-display		; only if requested (see below)
    nil lookup-slot save system)
  (display-up-to-date? nil lookup-slot system)

  (display-update-interval
    5 (type display-interval) lookup-slot system user-overridable)
  (display-wait-interval
    2 (type display-interval) lookup-slot system user-overridable)
  (display-update-priority
    2 (type priority) lookup-slot system user-overridable)

  (display-evaluation-should-use-simulated-values?
    nil (type yes-or-no) lookup-slot system user-overridable)  ;; see note with alias
;  (display-evaluation-should-not-trigger-variable-evaluation?
;    nil (type boolean) lookup-slot system)
;  (display-evaluation-should-interpolate?
;    nil (type boolean) lookup-slot system)
;  (expressions-to-display-should-be-kept-as-variables?
;    nil (type boolean) lookup-slot system)

  (variables-that-can-wake-up-this-display nil lookup-slot system)
  (things-this-display-is-interested-in nil lookup-slot system)
;  (time-that-wake-up-was-set-for-display nil lookup-slot system)
  (tracing-and-breakpoints nil system user-overridable lookup-slot
			   save (type tracing-and-breakpoints)))

;; Dial x and y center should not be user editable.  They should either be
;; constant for the dial type or automatically computed from the width of the
;; dial icon.  Go with the former method for now since dial icons can be made to
;; have "wierd" shapes.

;; Some of the other parameters such as length-of-dial-pointer shouldn't be user
;; editable either.  This makes it more bullet-proof (but less flexible).  To
;; get different values for length-of-dial-pointer and other such parameters, it
;; will be necessary to define other kinds of dials.  I think that this is the
;; best trade-off between ease of use and flexibility.

;; For now, assume there is only one pointer per dial. 

;; May want to have format frames at some point for dial rulings and dial
;; pointers.




(define-slot-alias expression-to-display expressions-to-display dial)

;; Allow expressions-to-display when dial can display more than one
;; expression (using more than one pointer).


;; Post-menu method for dials moved to menus. (MHD 7/4/87)


;(def-class-method cleanup (dial)
;  (retract-consistency-analysis dial))

(define-reclaimers-for-managed-number-slots 
  low-value-for-dial-ruling high-value-for-dial-ruling
  increment-per-dial-ruling desired-low-value-for-dial-ruling
  desired-high-value-for-dial-ruling)

;; When slot value floats get reclaimed automatically, these can go away.  But
;; they won't hurt anything in any case before or after the switch.  (MHD 3/1/91)


(def-class (ruling-for-dial block define-predicate)
  (ruling-low-value-angle-in-radians
    nil vector-slot system)
  (ruling-high-value-angle-in-radians
    nil vector-slot system)
  (angle-between-markings-in-radians
    nil vector-slot system))

(def-class (pointer-for-dial block define-predicate)
  (pointer-position-in-radians? nil vector-slot system))


(def-class-method initialize (pointer-for-dial)
  (funcall-superior-method pointer-for-dial)
  (set-render-frame-in-xor-overlay pointer-for-dial))

(def-class-method initialize-after-reading (dial)
  (funcall-superior-method dial)
  (make-or-reformat-ruling-for-dial (get-ruling-for-dial dial) dial)
  (eliminate-extra-rulings-for-dial dial))


(def-class-method initialize-after-reading (pointer-for-dial)
  (funcall-superior-method pointer-for-dial)
  (set-render-frame-in-xor-overlay pointer-for-dial))

(define-reclaimers-for-managed-number-slots 
  ruling-low-value-angle-in-radians ruling-high-value-angle-in-radians
  angle-between-markings-in-radians ; data-value-for-pointer 
  pointer-position-in-radians?)


(defun make-dial (dial-type)   
  (let ((new-dial (make-entity dial-type)))
    (make-or-reformat-ruling-for-dial nil new-dial)
    new-dial))

(def-class-method generate-spot (dial mouse-pointer)
  (push-last-spot mouse-pointer (make-dial-spot) dial))

(def-class-method generate-spot (pointer-for-dial mouse-pointer)
  (generate-spot-for-aggregate pointer-for-dial mouse-pointer))

(def-class-method generate-spot (ruling-for-dial mouse-pointer)
  (generate-spot-for-aggregate ruling-for-dial mouse-pointer))






;;; Make-marking-label ...

(def-class (dial-marking-label text-box))


;;; The `draw method for dial-marking-label' draws marking labels, which occur
;;; in the transitive closure of the subblocks of both meters and dials.
;;;
;;; In the case of dials, these are drawn on a background that is simply the
;;; workspace background.
;;;
;;; In the case of meters, these are the subblocks of the ruling-for-meter
;;; subblock of the meter, and are positioned and drawn within the meter's
;;; bounding rectangle, which is assumed to have an icon description giving it
;;; an icon color that serves as a solid background color.  Therefore, this
;;; binds current-background-color to the icon color of the superblock (i.e.,
;;; the meter).  (All of the subblocks of a meter must do this.)  This somewhat
;;; nongeneral scheme is needed only in order to get drawing to be correct when
;;; drawing in the XOR case.

(def-class-method draw (dial-marking-label)
  (unless (block-is-currently-being-dragged-p dial-marking-label)
    (if (frame-of-class-p (superblock? dial-marking-label) 'ruling-for-meter)
	(with-background-color-value
	    (map-color-or-metacolor-to-color-value
	      (item-color (superblock? (superblock? dial-marking-label))
			  'g2-icon-background))
	  (funcall-superior-method dial-marking-label))
	(funcall-superior-method dial-marking-label))))

;; Changed background-color-value from 'icon-color region
;; to 'g2-icon-background region for all meter subblocks (pbk 2/6/96)


      

(defun make-marking-label (number left-field-size right-field-size)
  (make-free-text-box
    (twith-output-to-text-string
      (write-floating-point-number
	number left-field-size right-field-size 6 t))
    'dial-marking-label 'marking-label-format))

;; This should really create text boxes of type free-text, not of type text-box!

;; This could be made more flexible by passing in a format-name
;; argument.  This would allow for different formats of labels
;; (for dials, meters, graphs, etc.)

;; jh, 1/22/92.  Added an extra argument to the call to
;; write-floating-point-number in make-marking-label.  This argument,
;; drop-trailing-digits-of-whole-number-p, will result in smaller marking labels
;; in the case where the markings are whole numbers (i.e., fixnums or floats
;; without a fractional part).

(def-class-method generate-spot (dial-marking-label mouse-pointer)
  (generate-spot-for-aggregate
    dial-marking-label mouse-pointer))



;;; Make-or-reformat-ruling-for-dial makes the dial ruling according
;;; to the specification parameters in dial.  The dial ruling is
;;; added as a subblock to the dial.

;;; If low-value-for-dial-ruling and increment-per-dial-ruling or
;;; low-value-for-dial-ruling and high-value-for-dial-ruling are
;;; specified for the meter, then desired-low-value-for-dial-ruling,
;;; desired-high-value-for-dial-ruling, and
;;; function-to-determine-standard-dial-ruling do not have to be
;;; specified.  In all cases, number of markings for meter must be
;;; specified.

(defun make-or-reformat-ruling-for-dial
    (ruling-for-dial? dial)
  (with-temporary-gensym-float-creation make-or-reformat-ruling-for-dial
    (let* ((ruling-for-dial
	     (or ruling-for-dial?
		 (make-frame 'ruling-for-dial)))
	   (short-pi (coerce-to-gensym-float pi))
	   (ruling-low-value-angle-in-radians
	     (* (ruling-low-value-angle
		  dial)
		(/ short-pi 180)))
	   (ruling-high-value-angle-in-radians
	     (* (ruling-high-value-angle
		  dial)
		(/ short-pi 180)))
	   (low-value-for-dial-ruling
	     (extract-number-or-value
	       (low-value-for-dial-ruling dial)))
	   (high-value-for-dial-ruling
	     (extract-number-or-value
	       (high-value-for-dial-ruling dial)))
	   (increment-per-dial-ruling
	     (extract-number-or-value
	       (increment-per-dial-ruling dial)))
	   (number-of-marks-for-dial
	     (number-of-marks-for-dial dial))
	   (distance-from-mark-to-label-center
	     (distance-from-mark-to-label-center dial))
	   (dial-radius 
	     (dial-radius dial))
	   (length-of-ruling-markers
	     (length-of-ruling-markers dial))
	   (x-center-of-dial
	     (+ (left-edge-of-block ruling-for-dial)
		(dial-x-center dial)))
	   (y-center-of-dial
	     (+ (top-edge-of-block ruling-for-dial)
		(dial-y-center dial))))
      
      (unless ruling-for-dial?		; if new
	(set-edges-of-block ruling-for-dial
			    (left-edge-of-block dial)
			    (top-edge-of-block dial)
			    (right-edge-of-block dial)
			    (bottom-edge-of-block dial))
	(add-subblock ruling-for-dial dial))
      
      (store-managed-number-or-value
	(ruling-low-value-angle-in-radians
	  ruling-for-dial)
	ruling-low-value-angle-in-radians)
      (store-managed-number-or-value
	(ruling-high-value-angle-in-radians
	  ruling-for-dial)
	ruling-high-value-angle-in-radians)
      (store-managed-number-or-value
	(angle-between-markings-in-radians
	  ruling-for-dial)
	(/ (- ruling-low-value-angle-in-radians
	      ruling-high-value-angle-in-radians)
	   (1- (number-of-marks-for-dial
		 dial))))
      
      (cond 
	((and low-value-for-dial-ruling
	      increment-per-dial-ruling)
	 (store-managed-number-or-value
	   (high-value-for-dial-ruling dial)
	   (+ low-value-for-dial-ruling
	      (* increment-per-dial-ruling
		 (1- number-of-marks-for-dial)))))
	((and low-value-for-dial-ruling
	      high-value-for-dial-ruling)
	 (store-managed-number-or-value
	   (increment-per-dial-ruling dial)
	   (/ (- high-value-for-dial-ruling
		 low-value-for-dial-ruling)
	      (1- number-of-marks-for-dial))))
	(t
	 ;; if this is the case, desired-low-value-for-dial-ruling,
	 ;; desired-high-value-for-dial-ruling, and 
	 ;; function-to-determine-standard-dial-ruling must not be nil.
	 ;; The user interface and installation mechanism must ensure this.
	 
	 (multiple-value-bind
	     (low high increment)
	     (funcall-symbol
	       (function-to-determine-standard-dial-ruling dial)
	       (extract-number-or-value
		 (desired-low-value-for-dial-ruling dial))
	       (extract-number-or-value
		 (desired-high-value-for-dial-ruling dial))
	       number-of-marks-for-dial)
	   (store-managed-number-or-value
	     (low-value-for-dial-ruling dial) low)
	   (store-managed-number-or-value
	     (high-value-for-dial-ruling dial) high)
	   (store-managed-number-or-value
	     (increment-per-dial-ruling dial) increment))))
      
      ;; remove dial marking labels
      (loop for dial-marking-label being each subblock of ruling-for-dial
	    doing (remove-as-subblock-if-necessary dial-marking-label)
		  (delete-frame dial-marking-label))
      
      ;; put up new labels for dial
      (loop for mark-number 
	    from 0 to (1- number-of-marks-for-dial) ; will get more complicated
	    as mark-angle
	       = (- ruling-low-value-angle-in-radians
		    (* mark-number
		       (extract-number-or-value
			 (angle-between-markings-in-radians
			   ruling-for-dial))))
	    as label-x-center 
	       = (round (+
			  (* (- dial-radius
				length-of-ruling-markers
				distance-from-mark-to-label-center)
			     (cos mark-angle))
			  x-center-of-dial))
	    as label-y-center
	       = (round (-
			  y-center-of-dial
			  (* (- dial-radius
				length-of-ruling-markers
				distance-from-mark-to-label-center)
			     (sin mark-angle))))
	    as label-value
	       = (+ low-value-for-dial-ruling
		    (* mark-number
		       increment-per-dial-ruling))
	    as new-dial-marking-label
	       = (make-marking-label label-value 3 2)
	    doing
	(funcall-method 'shift new-dial-marking-label
			(+w (-w label-x-center
				(left-edge-of-block new-dial-marking-label))
			    (round
			      (- (/ (width-of-block new-dial-marking-label)
				    2.0))))
			(+w (-w label-y-center
				(top-edge-of-block new-dial-marking-label))
			    (round
			      (- (/ (height-of-block new-dial-marking-label)
				    2.0)))))
	(add-subblock new-dial-marking-label ruling-for-dial))
      
      ruling-for-dial)))

;; Make-or-reformat-ruling-for-dial is called by slot value compilers for the
;; ruling parameter slots in dial.  Note that make-or-reformat-ruling-for-dial
;; is strictly an installation issue and has nothing to do with runtime updating
;; of the pointer(s) on the dial.  Note also that since make-dial (and therefore
;; make-or-reformat-ruling-for-dial) is called when a dial display is selected
;; (courtesy of def-class-choice-action for dial, in MENUS), there should be no
;; need for any slot putters to call make-or-reformat-ruling-for-dial.
;; Make-dial and the slot value compilers take care of things when a dial is
;; made or edited.  Since the dial ruling is saved as a subblock, nothing has to
;; be done when the dial is loaded as part of a knowledge base.

;; The slot value compilers for the ruling parameters will usually have to erase
;; and redraw the dial ruling so that the new one is shown.  These slot value
;; compilers should all be very similar; they erase the ruling, call
;; make-or-reformat-ruling-for-dial, and then draw the new ruling.  Many of the
;; ruling parameters could probably have the same type.  This would reduce the
;; number of similar slot value compilers.  Also, as mentioned above, some of
;; the ruling parameters should probably become non-editable.

;; The ruling for dial argument is currently used here only to indicate whether
;; a ruling exists or not.  Note that if a ruling exists, it is re-used so there
;; is no recycling issue here.


(def-text-box-format marking-label-format
  text-cell-x-magnification? #.(convert-to-magnification-at-compile-time .75)
  text-cell-y-magnification? #.(convert-to-magnification-at-compile-time .75)
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 24
  text-cell-left-margin 8
  text-cell-top-margin 6
  text-cell-right-margin 8
  text-cell-bottom-margin 5
  text-box-left-border-width 0
  text-box-top-border-width 0
  text-box-right-border-width 0
  text-box-bottom-border-width 0)



(defun determine-standard-dial-ruling
       (desired-low-value desired-high-value number-of-markings)
  (let ((desired-increment-per-ruling
	  (/ (coerce-to-gensym-float (- desired-high-value desired-low-value))
	     number-of-markings)))
    desired-increment-per-ruling))

;; finish, see "graphs"
;; Increment or decrement k and l until best fit (easy).


(defun get-pointer-for-dial-if-any (dial)
  (loop for subblock being each subblock of dial do
    (when (frame-of-class-p subblock 'pointer-for-dial)
      (return subblock))))


(defun get-ruling-for-dial (dial)
  (loop for subblock being each subblock of dial do
    (when (frame-of-class-p subblock 'ruling-for-dial)
      (return subblock))))


(def-system-variable do-not-update-simulated-value? displays nil)






;;;; Dial Pointer Update




;;; Updating a dial actually causes only the dial pointer to be moved; there is
;;; no reason to erase and redraw the entire dial and rulings.  If there is no
;;; value the meter will be cleared using clear meter.  If the value hasn't
;;; changed, nothing will be done.

(define-cell-based-update-display-function dial
  (let* ((dial-pointer? (get-pointer-for-dial-if-any dial))
	 (new-display-value?
	   (if (evaluation-obsolete-datum-p new-cache?)
	       (evaluation-obsolete-datum-value new-cache?)
	       new-cache?))
	 (old-display-value?
	   (if (evaluation-obsolete-datum-p old-cache?)
	       (evaluation-obsolete-datum-value old-cache?)
	       old-cache?)))
    (cond (new-display-value?
	   (unless (and (not update-even-if-value-unchanged?)
			dial-pointer? old-display-value?
			(evaluation-value-eql
			  new-display-value? old-display-value?))
	     (when dial-pointer?
	       (erase-images-of-block dial-pointer? t))
	     (make-or-reformat-pointer-for-dial
	       dial-pointer? dial
	       (evaluation-value-value new-display-value?))
	     (let ((new-dial-pointer? (or dial-pointer?
					  (get-pointer-for-dial-if-any dial))))
	       (when new-dial-pointer?
		 (draw-images-of-block new-dial-pointer? t)))
	     ;; should check if against min and max to see if it
	     ;; really changed
	     (send-ws-representations-item-virtual-attribute-change
	       dial (virtual-attribute 'value-to-display) nil)))
	  (t
	   (funcall-method 'clear-display dial)
	   (send-ws-representations-item-virtual-attribute-change
	     dial (virtual-attribute 'value-to-display) nil)))))


;;; `eliminate-extra-rulings-for-dial'

(defun-void eliminate-extra-rulings-for-dial (dial)
  #-subblocks-v2
  (loop with ruling-seen-p = nil
	with prev-tail = nil
	with tail = (subblocks dial)
	while tail
	as subblock = (car tail)
	as next-tail = (cdr tail)
	do
    (when (ruling-for-dial-p subblock)
      (cond
	(ruling-seen-p
	 (setf (cdr prev-tail) (cdr tail))
	 (delete-frame subblock))
	(t
	 (setf ruling-seen-p t))))
    (setf tail next-tail)
    (setf prev-tail tail))
  #+subblocks-v2
  (loop with ruling-seen-p = nil
	with constant-queue = (subblocks dial)
	with head = (constant-queue-head constant-queue)
	for queue-element = #-Lockfree-Deque head
			    #+Lockfree-Deque (constant-queue-next head constant-queue)
		       then next-queue-element
	until #-Lockfree-Deque (eq queue-element constant-queue)
	      #+Lockfree-Deque (null queue-element)
	for next-queue-element = (constant-queue-next queue-element constant-queue)
	do
    (let ((subblock (queue-datum queue-element)))
      (when (ruling-for-dial-p subblock)
	(cond (ruling-seen-p
	       (constant-queue-delete queue-element constant-queue)
	       (delete-frame subblock))
	      (t
	       (setq ruling-seen-p t)))))))

;;; `make-or-reformat-pointer-for-dial'

(defun make-or-reformat-pointer-for-dial
    (pointer-for-dial? dial new-data-value-for-pointer)
  (cond
    ((or (null new-data-value-for-pointer)
	 (fixnump new-data-value-for-pointer)
	 (gensym-float-p new-data-value-for-pointer))
     (let* ((high-value-for-dial-ruling
	      (extract-number-or-value
		(high-value-for-dial-ruling dial)))
	    (ruling-for-dial
	      (let ((ruling-for-dial? (get-ruling-for-dial dial)))
		(cond
		  ((null ruling-for-dial?)
		   (make-or-reformat-ruling-for-dial nil dial))
		  ((null high-value-for-dial-ruling)
		   (let ((the-ruling-for-dial
			   (make-or-reformat-ruling-for-dial
			     ruling-for-dial? dial)))
		     (setq high-value-for-dial-ruling
			   (extract-number-or-value
			     (high-value-for-dial-ruling dial)))
		     the-ruling-for-dial))
		  (t
		   ruling-for-dial?))))
	    (pointer-for-dial
	      (or pointer-for-dial?
		  (make-frame 'pointer-for-dial)))
	    (low-value-for-dial-ruling
	      (extract-number-or-value
		(low-value-for-dial-ruling dial)))
	    
	    ;; consider having slots in dial that are direct pointers
	    ;; to ruling-for-dial and pointer-for-dial
	    (ruling-low-value-angle-in-radians
	      (extract-number-or-value
		(ruling-low-value-angle-in-radians ruling-for-dial)))
	    (ruling-high-value-angle-in-radians
	      (extract-number-or-value
		(ruling-high-value-angle-in-radians ruling-for-dial))))
       
       (unless pointer-for-dial?		; if new
	 (set-edges-of-block pointer-for-dial
			     (left-edge-of-block dial)
			     (top-edge-of-block dial)
			     (right-edge-of-block dial)
			     (bottom-edge-of-block dial))
	 (add-subblock pointer-for-dial dial))

       (cond
	 ((not new-data-value-for-pointer)
	  (store-managed-number-or-value
	    (pointer-position-in-radians?
	      pointer-for-dial)
	    nil))
	 ((<= new-data-value-for-pointer
	      low-value-for-dial-ruling)
	  (store-managed-number-or-value
	    (pointer-position-in-radians?
	      pointer-for-dial)
	    ruling-low-value-angle-in-radians))
	 ((>= new-data-value-for-pointer
	      high-value-for-dial-ruling)
	  (store-managed-number-or-value
	    (pointer-position-in-radians?
	      pointer-for-dial)
	    ruling-high-value-angle-in-radians))
	 (t
	  (store-managed-number-or-value
	    (pointer-position-in-radians?
	      pointer-for-dial)
	    (+ ruling-low-value-angle-in-radians
	       (* (/ (- (coerce-to-gensym-float
			  new-data-value-for-pointer)
			low-value-for-dial-ruling)
		     (- high-value-for-dial-ruling
			low-value-for-dial-ruling))
		  (- ruling-high-value-angle-in-radians
		     ruling-low-value-angle-in-radians))))))
       
;    (format t "~%~%high-value-for-dial-ruling = ~S~%"
;	    high-value-for-dial-ruling)
;    (format t "low-value-for-dial-ruling = ~S~%"
;	    low-value-for-dial-ruling)
;    (format t "new-data-value-for-pointer = ~S~%"
;	    new-data-value-for-pointer)
;    (format t "pointer-position-in-radians? = ~S~%"
;	    (pointer-position-in-radians? pointer-for-dial))
       
       pointer-for-dial))
    (t  ; If value is not a number, complain.
     (warning-message* 1 "Attempting to display non-numeric values on a dial."))))






;;;; Draw Methods for Ruling and Pointer for Dial




;;; `Draw method for ruling-for-dial' ...

(def-class-method draw (ruling-for-dial)
  (unless (block-is-currently-being-dragged-p ruling-for-dial)
    (let ((parent-dial-for-ruling (superblock? ruling-for-dial)))
      (with-temporary-gensym-float-creation draw-ruling-for-dial
	(if (not (extract-number-or-value
		   (ruling-low-value-angle-in-radians
		     ruling-for-dial)))
	    (make-or-reformat-ruling-for-dial
	      ruling-for-dial parent-dial-for-ruling))
	(let* ((x-center-of-dial
		 (+ (left-edge-of-block ruling-for-dial)
		    (dial-x-center parent-dial-for-ruling)))
	       (y-center-of-dial
		 (+ (top-edge-of-block ruling-for-dial)
		    (dial-y-center parent-dial-for-ruling)))
	       (dial-radius
		 (dial-radius parent-dial-for-ruling))
	       (ruling-low-value-angle-in-radians
		 (extract-number-or-value
		   (ruling-low-value-angle-in-radians
		     ruling-for-dial)))
	       (ruling-high-value-angle-in-radians
		 (extract-number-or-value
		   (ruling-high-value-angle-in-radians
		     ruling-for-dial)))
	       (angle-between-markings-in-radians
		 (extract-number-or-value
		   (angle-between-markings-in-radians
		     ruling-for-dial)))
	       (ruling-marker-color-difference
		 (color-difference
		   current-foreground-color-value
		   current-background-color-value))
	       (length-of-ruling-markers
		 (length-of-ruling-markers parent-dial-for-ruling)))
	  
	  ruling-high-value-angle-in-radians
	  
	  (loop for mark-number 
		from 0 to (1- (number-of-marks-for-dial
				parent-dial-for-ruling))
		as mark-angle
		   = (- ruling-low-value-angle-in-radians
			(* mark-number
			   angle-between-markings-in-radians))
		as mark-x-position-in-window
		   = (x-in-window
		       (round (+
				(* (- dial-radius
				      length-of-ruling-markers)
				   (cos mark-angle))
				x-center-of-dial)))
		as mark-y-position-in-window
		   = (y-in-window
		       (round (- y-center-of-dial
				 (* (- dial-radius
				       length-of-ruling-markers)
				    (sin mark-angle)))))
		do
	    (draw-solid-rectangle	
	      mark-x-position-in-window
	      mark-y-position-in-window
	      (+ mark-x-position-in-window
		 (delta-x-in-window 3 current-image-x-scale))	; for now
	      (+ mark-y-position-in-window
		 (delta-y-in-window 3 current-image-y-scale))	; for now
	      ruling-marker-color-difference)))
	
;	(draw-subblocks ruling-for-dial)
	))))

;; It may eventually be necessary to define methods for pointer-for-dial
;; to compute-minimum-right-edge, compute-minimum-bottom-edge, resize,
;; and shift.  For now, the inherited methods for blocks are used.



;;; The `draw method for pointer-for-dial' ...

;;; Checks if the display is up to date.  If it isn't, the dial pointer is not
;;; drawn.

(def-class-method draw (pointer-for-dial)
  (let ((pointer-position-in-radians?
	  (pointer-position-in-radians? pointer-for-dial))
	(parent-dial (superblock? pointer-for-dial)))
    (when (and pointer-position-in-radians?
	       (not (block-is-currently-being-dragged-p parent-dial)))
      (with-temporary-gensym-float-creation draw-pointer-for-dial
	(let* ((parent-dial-for-pointer
		 (superblock? pointer-for-dial))
	       (x-center-of-dial
		 (+ (left-edge-of-block pointer-for-dial)
		    (dial-x-center parent-dial-for-pointer)))
	       (y-center-of-dial
		 (+ (top-edge-of-block pointer-for-dial)
		    (dial-y-center parent-dial-for-pointer)))
	       (length-of-dial-pointer
		 (length-of-dial-pointer parent-dial-for-pointer))
	       (pointer-position-in-radians
		 (coerce-to-gensym-float
		   (extract-number-or-value pointer-position-in-radians?)))
	       (number-of-points-for-pointer 20)
	       (list-of-points-for-pointer
		 (loop for point-number from 1 to number-of-points-for-pointer
		       collect
		       (eval-cons
			 (x-in-window
			   (round
			     (+ x-center-of-dial
				(* (* length-of-dial-pointer
				      (/ point-number 
					 (coerce-to-gensym-float
					   number-of-points-for-pointer)))
				   (cos pointer-position-in-radians)))))
			 (y-in-window
			   (round
			     (- y-center-of-dial
				(* (* length-of-dial-pointer
				      (/ point-number
					 (coerce-to-gensym-float
					   number-of-points-for-pointer)))
				   (sin pointer-position-in-radians))))))
			 using eval-cons))
	       (x-center-of-dial-in-window
		 (x-in-window x-center-of-dial))
	       (y-center-of-dial-in-window
		 (y-in-window y-center-of-dial))
	       (point-size 2)
	       (point-width-in-window
		 (delta-x-in-window point-size current-image-x-scale))
	       (point-height-in-window
		 (delta-y-in-window point-size current-image-y-scale))
	       (point-color-difference
		 (color-difference	; See note below (MHD 7/27/00)
		   current-foreground-color-value
		   (if (printing-window-p current-window)
		       current-background-color-value
		       (map-to-color-value 'white))))
	       (pointer-arrowhead-size
		 (pointer-arrowhead-size parent-dial-for-pointer)))
	  
	  (draw-solid-rectangle	
	    x-center-of-dial-in-window
	    y-center-of-dial-in-window
	    (+ x-center-of-dial-in-window point-width-in-window)
	    (+ y-center-of-dial-in-window point-height-in-window)
	    point-color-difference)
	  
	  (loop for point in list-of-points-for-pointer
		do
	    (draw-solid-rectangle	
	      (car point)
	      (cdr point)
	      (+ (car point) point-width-in-window)
	      (+ (cdr point) point-height-in-window)
	      point-color-difference))
	  
	  (if pointer-arrowhead-size
	      (let* ((arrowhead-base-x
		       (+ x-center-of-dial
			  (* (- length-of-dial-pointer pointer-arrowhead-size)
			     (cos pointer-position-in-radians))))
		     (arrowhead-base-y
		       (- y-center-of-dial
			  (* (- length-of-dial-pointer pointer-arrowhead-size)
			     (sin pointer-position-in-radians))))
		     (arrowhead-right-x-in-window
		       (x-in-window
			 (round
			   (+ arrowhead-base-x
			      (* pointer-arrowhead-size
				 (sin pointer-position-in-radians))))))
		     (arrowhead-left-x-in-window
		       (x-in-window
			 (round
			   (- arrowhead-base-x
			      (* pointer-arrowhead-size
				 (sin pointer-position-in-radians))))))
		     (arrowhead-right-y-in-window
		       (y-in-window
			 (round
			   (+ arrowhead-base-y
			      (* pointer-arrowhead-size
				 (cos pointer-position-in-radians))))))
		     (arrowhead-left-y-in-window
		       (y-in-window
			 (round
			   (- arrowhead-base-y
			      (* pointer-arrowhead-size
				 (cos pointer-position-in-radians))))))
		     (arrowhead-base-x-in-window
		       (x-in-window
			 (round arrowhead-base-x)))
		     (arrowhead-base-y-in-window
		       (y-in-window
			 (round arrowhead-base-y))))
		
		(draw-solid-rectangle	
		  arrowhead-base-x-in-window		
		  arrowhead-base-y-in-window
		  (+ arrowhead-base-x-in-window
		     (delta-x-in-window 3 current-image-x-scale))	; for now
		  (+ arrowhead-base-y-in-window
		     (delta-y-in-window 3 current-image-y-scale))	; for now
		  point-color-difference)
		
		(draw-solid-rectangle	
		  arrowhead-right-x-in-window		
		  arrowhead-right-y-in-window
		  (+ arrowhead-right-x-in-window
		     (delta-x-in-window 3 current-image-x-scale))	; for now
		  (+ arrowhead-right-y-in-window
		     (delta-y-in-window 3 current-image-y-scale))	; for now
		  point-color-difference)
		
		(draw-solid-rectangle	
		  arrowhead-left-x-in-window		
		  arrowhead-left-y-in-window
		  (+ arrowhead-left-x-in-window
		     (delta-x-in-window 3 current-image-x-scale))	; for now
		  (+ arrowhead-left-y-in-window
		     (delta-y-in-window 3 current-image-y-scale))	; for now
		  point-color-difference)
		
		))
	  (reclaim-eval-tree list-of-points-for-pointer))))))


;; Note: for the pointer, the background color is the color of the "face", which
;; we "know" is white (by looking at it and/or looking at SYSICONS). However, it
;; is too hard for the printing system to handle a color differerence on top top
;; of an icon -- it only wants to do painting of true colors at this level.  So,
;; we cheat by giving it a true color to paint in this funny way, which seems to
;; work out.  (MHD 7/2700)



(define-clear-display-function dial
  (let ((dial-pointer? (get-pointer-for-dial-if-any dial)))
    (when dial-pointer?
      (erase-images-of-block dial-pointer? t)
      (remove-as-subblock-if-necessary dial-pointer?)
      (delete-frame dial-pointer?))))


;;; `Activation Methods for Dials'

(define-activate-method-for-entity-display dial)

(define-deactivate-method-for-entity-display dial)







;;;; Meters

;;; Meters are similar to dials.

(def-class (meter (item entity) (foundation-class meter) define-predicate
		  (class-export-comment "Shares some slot names w/Dial"))

  (icon-description
    (:funcall-at-load-time
      create-icon-description
      80 300
       ;; Converting system icons to polygons/solid-rectangles JED 8/11/93
;      ((outline (0 0) (80 0) (80 300) (0 300))
;       (outline (1 1) (79 1) (79 299) (1 299)))))
       ((solid-rectangle (0 0) (80 1))
	(solid-rectangle (0 1) (1 299))
	(solid-rectangle (79 1) (80 299))
	(solid-rectangle (0 299) (80 300)))))

  (display-update-task? nil no-accessor vector-slot system do-not-save)
  (task-for-display-continuation? nil no-accessor vector-slot system do-not-save)

  ;; need slots for color, format for marker, etc.
  (ruling-low-value-position
    25 vector-slot system)
  (ruling-high-value-position
    275 vector-slot system)

  (number-of-marks-for-meter
    5 vector-slot system)
  (length-of-ruling-markers-for-meter 
    15 vector-slot system)
  (width-of-ruling-markers-for-meter 
    3 vector-slot system)
  (space-for-ruling-labels-for-meter
    30 vector-slot system)
  (meter-marker-sliding-axis-position
    45 vector-slot system)

  (low-value-for-meter-ruling
    0.0
    (type meter-ruling-parameter) vector-slot system user-overridable)
  (high-value-for-meter-ruling
    nil  ; (type number?)   temporarily disabled
    vector-slot system)
  (increment-per-meter-ruling
    0.25
    (type meter-ruling-parameter) vector-slot system user-overridable)

  (desired-low-value-for-meter-ruling
    0.0
    ; (type number)  temporarily disabled
    vector-slot system)
  (desired-high-value-for-meter-ruling
    1.0
    ; (type number)  temporarily disabled
    vector-slot system)
  (function-to-determine-standard-meter-ruling
    determine-standard-meter-ruling vector-slot system)

  (distance-from-mark-to-label-center-for-meter
    20 vector-slot system)

  ;; The following slots are the same as the ones for readouts.
  ;; If these become vector slots at some point, give them
  ;; unique names.

  (expressions-to-display
    nil (type display-expression text) no-accessor lookup-slot system select-changes)
  (variables-for-expressions-to-display		; only if requested (see below)
    nil no-accessor lookup-slot system)
  (display-up-to-date? nil no-accessor lookup-slot system)

  (display-update-interval
    5 (type display-interval) no-accessor lookup-slot system user-overridable)
  (display-wait-interval
    2 (type display-interval) no-accessor lookup-slot system user-overridable)
  (display-update-priority
    2 (type priority) no-accessor lookup-slot system user-overridable)

  (display-evaluation-should-use-simulated-values?
    nil (type yes-or-no) no-accessor lookup-slot system user-overridable) ; see note with Alias
;  (display-evaluation-should-not-trigger-variable-evaluation?
;    nil (type boolean) no-accessor lookup-slot)
;  (display-evaluation-should-interpolate?
;    nil (type boolean) no-accessor lookup-slot)
;  (expressions-to-display-should-be-kept-as-variables?
;    nil (type boolean) no-accessor lookup-slot)

  (variables-that-can-wake-up-this-display nil no-accessor lookup-slot system)
  (things-this-display-is-interested-in nil no-accessor lookup-slot system)
;  (time-that-wake-up-was-set-for-display nil no-accessor lookup-slot system)
  (tracing-and-breakpoints nil system user-overridable lookup-slot save
			   (type tracing-and-breakpoints)))

(define-slot-alias expression-to-display expressions-to-display meter)

;; The post-menu method for meters was moved from here to menus. (MHD 7/3/87)


;(def-class-method cleanup (meter)	
;  (retract-consistency-analysis meter))


(define-reclaimers-for-managed-number-slots 
  low-value-for-meter-ruling high-value-for-meter-ruling
  increment-per-meter-ruling desired-low-value-for-meter-ruling
  desired-high-value-for-meter-ruling)


(def-class (ruling-for-meter block define-predicate)
  (distance-between-markings-for-meter
    nil vector-slot system))


(def-class (marker-for-meter entity define-predicate)
  (icon-description
    (:funcall-at-load-time
      create-icon-description
      20 40
      (
       ;; Converting system icons to polygons/solid-rectangles JED 8/11/93
;       (outline (0 20) (10 10) (10 0) (20 0)
;		(20 40) (10 40) (10 30))
;       (outline (1 20) (9 11) (9 29))
;       (outline (2 20) (8 12) (8 28))
;       (outline (3 20) (7 13) (7 27))
;       (outline (4 20) (6 14) (6 26))
;       (lines (5 15) (5 25))
       #.(create-filled-polygon-icon-description-element
	   '((0 20) (10 10) (10 30)))
       (solid-rectangle (10 0) (20 40)))))
  (marker-position nil vector-slot system))

(def-class-method initialize (marker-for-meter)
  (funcall-superior-method marker-for-meter)
  (set-render-frame-in-xor-overlay marker-for-meter))

(def-class-method initialize-after-reading (marker-for-meter)
  (funcall-superior-method marker-for-meter)
  (set-render-frame-in-xor-overlay marker-for-meter))



(define-reclaimers-for-managed-number-slots
  distance-between-markings-for-meter)

(def-class-method generate-spot (meter mouse-pointer)
  (push-last-spot mouse-pointer (make-meter-spot) meter))

(def-class-method generate-spot (ruling-for-meter mouse-pointer)
  (generate-spot-for-aggregate ruling-for-meter mouse-pointer))

(def-class-method generate-spot (marker-for-meter mouse-pointer)
  (generate-spot-for-aggregate marker-for-meter mouse-pointer))


(defun make-meter (meter-type)   
  (let ((new-meter (make-entity meter-type)))
    (make-or-reformat-ruling-for-meter nil new-meter)
    new-meter))

;;; Added `initialize-after-reading-for-meter' to ensure that
;;; make-or-reformat-ruling-for-meter is called before the
;;; the meter is ever updated.  This was done to fix an abort
;;; wherein some meters were updated before
;;; make-or-reformat-ruling-for-meter was ever called.
;;; See Bug: HQ-1309801 
;;; -ajs 5/1/97

(def-class-method initialize-after-reading (meter)
  (funcall-superior-method meter)
  (make-or-reformat-ruling-for-meter nil meter))



;;; Make-or-reformat-ruling-for-meter makes the meter ruling according
;;; to the specification parameters in meter.  The meter ruling is
;;; added as a subblock to the meter.

;;; If low-value-for-meter-ruling and increment-per-meter-ruling or
;;; low-value-for-meter-ruling and high-value-for-meter-ruling are
;;; specified for the meter, then desired-low-value-for-meter-ruling,
;;; desired-high-value-for-meter-ruling, and
;;; function-to-determine-standard-meter-ruling do not have to be
;;; specified.  In all cases, number of markings for meter must be
;;; specified.

(defun make-or-reformat-ruling-for-meter
    (ruling-for-meter? meter)
  (with-temporary-gensym-float-creation make-or-reformat-ruling-for-meter
    (let* ((ruling-for-meter
	     (or ruling-for-meter?
		 (make-frame 'ruling-for-meter)))
	   (ruling-low-value-position
	     (ruling-low-value-position meter))
	   (ruling-high-value-position
	     (ruling-high-value-position meter))
	   (low-value-for-meter-ruling
	     (extract-number-or-value
	       (low-value-for-meter-ruling meter)))
	   (high-value-for-meter-ruling
	     (extract-number-or-value
	       (high-value-for-meter-ruling meter)))
	   (increment-per-meter-ruling
	     (extract-number-or-value
	       (increment-per-meter-ruling meter)))
	   (number-of-marks-for-meter
	     (number-of-marks-for-meter meter)))
      
      (unless ruling-for-meter?		       ; if new
	(set-edges-of-block ruling-for-meter
			    (left-edge-of-block meter)
			    (top-edge-of-block meter)
			    (right-edge-of-block meter)
			    (bottom-edge-of-block meter))
	(add-subblock ruling-for-meter meter))
      
      (store-managed-number-or-value
	(distance-between-markings-for-meter
	  ruling-for-meter)
	(/ (coerce-to-gensym-float
	     (- ruling-high-value-position
		ruling-low-value-position))
	   (1- (number-of-marks-for-meter
		 meter))))
      
      (cond 
	((and low-value-for-meter-ruling
	      increment-per-meter-ruling)
	 (store-managed-number-or-value
	   (high-value-for-meter-ruling meter)
	   (+ low-value-for-meter-ruling
	      (* increment-per-meter-ruling
		 (1- number-of-marks-for-meter)))))
	((and low-value-for-meter-ruling
	      high-value-for-meter-ruling)
	 (store-managed-number-or-value
	   (increment-per-meter-ruling meter)
	   (/ (- high-value-for-meter-ruling
		 low-value-for-meter-ruling)
	      (1- number-of-marks-for-meter))))
	(t
	 ;; if this is the case, desired-low-value-for-meter-ruling,
	 ;; desired-high-value-for-meter-ruling, and 
	 ;; function-to-determine-standard-meter-ruling must not be nil.
	 ;; The user interface and installation mechanism must ensure this.
	 
	 (multiple-value-bind
	     (low high increment)
	     (funcall-symbol
	       (function-to-determine-standard-meter-ruling meter)
	       (extract-number-or-value
		 (desired-low-value-for-meter-ruling meter))
	       (extract-number-or-value
		 (desired-high-value-for-meter-ruling meter))
	       number-of-marks-for-meter)
	   (store-managed-number-or-value
	     (low-value-for-meter-ruling meter) low)
	   (store-managed-number-or-value
	     (high-value-for-meter-ruling meter) high)
	   (store-managed-number-or-value
	     (increment-per-meter-ruling meter) increment))))
      
      
      ;; remove meter marking labels
      (loop for meter-marking-label being each subblock of ruling-for-meter
	    doing (remove-as-subblock-if-necessary meter-marking-label)
		  (delete-frame meter-marking-label))
      
      ;; put up new labels for meter
      (loop for mark-number 
	    from 0 to (1- number-of-marks-for-meter)       ; will get more complicated
	    as mark-position-in-meter
	       = (+ ruling-low-value-position
		    (round			       ; added by LH
		      (* mark-number
			 (extract-number-or-value
			   (distance-between-markings-for-meter
			     ruling-for-meter)))))
	    as label-left-edge
	       = (left-edge-of-block meter)
	    as label-bottom-edge
	       = (+w (top-edge-of-block meter)
		     (-w (height-of-block meter)
			 mark-position-in-meter))
	    as label-value
	       = (+ low-value-for-meter-ruling
		    (* mark-number
		       increment-per-meter-ruling))
	    as new-meter-marking-label
	       = (make-marking-label label-value 4 3)
	    doing
	(funcall-method 'shift new-meter-marking-label
			(-w label-left-edge
			    (left-edge-of-block new-meter-marking-label))
			(-w label-bottom-edge
			    (bottom-edge-of-block new-meter-marking-label)))
	(add-subblock new-meter-marking-label ruling-for-meter))
      
      ruling-for-meter)))


(defun determine-standard-meter-ruling
       (desired-low-value desired-high-value number-of-markings)
  (let ((desired-increment-per-ruling
	  (/ (coerce-to-gensym-float (- desired-high-value desired-low-value))
	     number-of-markings)))
    desired-increment-per-ruling))

;; finish, see "graphs"
;; Increment or decrement k and l until best fit (easy).


(define-clear-display-function meter
  (let ((meter-marker? (get-marker-for-meter-if-any meter)))
    (when meter-marker?
      (erase-images-of-block meter-marker? t)
      (remove-as-subblock-if-necessary meter-marker?)
      (delete-frame meter-marker?))))






;;;; Meter Marker Update


(defun get-marker-for-meter-if-any (meter)
  (loop for subblock being each subblock of meter do
    (when (frame-of-class-p subblock 'marker-for-meter)
      (return subblock))))

(defun get-ruling-for-meter (meter)
  (loop for subblock being each subblock of meter do
    (when (frame-of-class-p subblock 'ruling-for-meter)
      (return subblock))))




;;; Updating a meter actually causes only the meter marker to be moved; there is
;;; no reason to erase and redraw the entire meter and rulings.  If there is no
;;; value the meter will be cleared using clear meter.  If the value hasn't
;;; changed, nothing will be done.

(define-cell-based-update-display-function meter
  (let* ((meter-marker? (get-marker-for-meter-if-any meter))
	 (new-display-value?
	   (if (evaluation-obsolete-datum-p new-cache?)
	       (evaluation-obsolete-datum-value new-cache?)
	       new-cache?))
	 (old-display-value?
	   (if (evaluation-obsolete-datum-p old-cache?)
	       (evaluation-obsolete-datum-value old-cache?)
	       old-cache?)))
    (cond (new-display-value?
	   (unless (and (not update-even-if-value-unchanged?)
			meter-marker?
			old-display-value?
			(evaluation-value-eql
			  new-display-value? old-display-value?))
	     (when meter-marker?
	       (erase-images-of-block meter-marker? t))
	     (make-or-reformat-marker-for-meter
	       meter-marker? meter (evaluation-value-value new-display-value?))
	     (let ((new-meter-marker?
		     (or meter-marker?
			 (get-marker-for-meter-if-any meter))))
	       (when new-meter-marker?
		 (draw-images-of-block new-meter-marker? t)))
	     ;; should check if against min and max to see if it
	     ;; really changed
	     (send-ws-representations-item-virtual-attribute-change
	       meter (virtual-attribute 'value-to-display) nil)))
	  (t					; if no value, clear meter
	   (funcall-method 'clear-display meter)
	   (send-ws-representations-item-virtual-attribute-change
	       meter (virtual-attribute 'value-to-display) nil)))))
	   

(defun make-or-reformat-marker-for-meter
       (marker-for-meter? meter new-data-value-for-marker)
  (cond
    ((or (null new-data-value-for-marker)
	 (fixnump new-data-value-for-marker)
	 (gensym-float-p new-data-value-for-marker))
     (let* ((marker-for-meter
	      (or marker-for-meter?
		  (make-entity 'marker-for-meter)))
	    (low-value-for-meter-ruling
	      (extract-number-or-value
		(low-value-for-meter-ruling meter)))
	    (high-value-for-meter-ruling
	      (extract-number-or-value
		(high-value-for-meter-ruling meter)))
	    
	    ;; consider having slots in meter that are direct markers
	    ;; to ruling-for-meter and marker-for-meter
	    
	    (ruling-low-value-position
	      (ruling-low-value-position meter))
	    (ruling-high-value-position
	      (ruling-high-value-position meter))
	    (marker-position-for-shift nil))
       
     
       (if (not marker-for-meter?)		; if new
	   (progn
	     (add-subblock marker-for-meter meter)))
       
       (unless (or (block-is-currently-being-dragged-p meter)  ;(pbk)fix: marker-noshow-bug
		   (render-frame-in-xor-overlay-p meter))      ; initialize sets xor-mode flag
	 (clear-render-frame-in-xor-overlay marker-for-meter))

       
       (cond
	 ((null new-data-value-for-marker)
	  (setf (marker-position marker-for-meter) nil)
	  (setq marker-position-for-shift low-value-for-meter-ruling))
	 ((<= new-data-value-for-marker
	      low-value-for-meter-ruling)
	  (setq marker-position-for-shift ruling-low-value-position)
	  (setf (marker-position marker-for-meter)
		marker-position-for-shift))
	 ((>= new-data-value-for-marker
	      high-value-for-meter-ruling)
	  (setq marker-position-for-shift ruling-high-value-position)
	  (setf (marker-position marker-for-meter)
		marker-position-for-shift))
	 (t
	  (setq marker-position-for-shift
		(round
		  (+ ruling-low-value-position
		     (* (/ (- (coerce-to-gensym-float
				new-data-value-for-marker)
			      low-value-for-meter-ruling)
			   (- high-value-for-meter-ruling
			      low-value-for-meter-ruling))
			(- ruling-high-value-position
			   ruling-low-value-position)))))
	  (setf (marker-position marker-for-meter)
		marker-position-for-shift)))
       
;       (format t "~%~%high-value-for-meter-ruling = ~S~%"
;	       high-value-for-meter-ruling)
;       (format t "low-value-for-meter-ruling = ~S~%"
;	       low-value-for-meter-ruling)
;       (format t "new-data-value-for-marker = ~S~%"
;	       new-data-value-for-marker)
;       (format t "marker-position-in-radians = ~S~%"
;	       (marker-position marker-for-meter))
       
       (funcall-method 'shift marker-for-meter
		       (-w (+w (left-edge-of-block meter)
			       (meter-marker-sliding-axis-position meter))
			   (left-edge-of-block marker-for-meter))
		       (-w (+w (top-edge-of-block meter)
			       (-w (height-of-block meter)
				   marker-position-for-shift))
			   (+w (top-edge-of-block marker-for-meter)
			       (round 
				 (/ (height-of-block marker-for-meter) 2.0)))))
       marker-for-meter))
    (t						; If value is not a number, complain.
     (warning-message* 
       1 "Attempting to display non-numeric values on a meter."))))



;;; Activation Methods for Meters

(define-activate-method-for-entity-display meter)

(define-deactivate-method-for-entity-display meter)






;;;; Draw Methods for Ruling and Marker for Meter

;;; The `draw method for ruling-for-meter' draws a ruling icon on top of the
;;; meter, which is assumed to have an icon description giving it an icon color
;;; that serves as a solid background color.  Therefore, this binds
;;; current-background-color to the icon color of the superblock (i.e., the
;;; meter).  (All of the subblocks of a meter must do this.)  This somewhat
;;; nongeneral scheme is needed only in order to get drawing to be correct when
;;; drawing in the XOR case.

(def-class-method draw (ruling-for-meter)
  (with-background-color-value
      (map-color-or-metacolor-to-color-value
	(item-color (superblock? ruling-for-meter) 'g2-icon-background)) ;pbk
    (with-temporary-gensym-float-creation draw-ruling-for-meter
      (let ((parent-meter-for-ruling (superblock? ruling-for-meter)))
	(if (not (extract-number-or-value
		   (distance-between-markings-for-meter
		     ruling-for-meter)))
	    (make-or-reformat-ruling-for-meter
	      ruling-for-meter parent-meter-for-ruling))
	(let* ((ruling-low-value-position
		 (ruling-low-value-position
		   parent-meter-for-ruling))
	     (ruling-high-value-position
	       (ruling-high-value-position
		 parent-meter-for-ruling))
	     (distance-between-markings-for-meter
	       (extract-number-or-value
		 (distance-between-markings-for-meter
		   ruling-for-meter)))
	     (ruling-marker-color-difference
	       (color-difference
		 current-foreground-color-value
		 current-background-color-value))
	     (length-of-ruling-markers-for-meter
	       (length-of-ruling-markers-for-meter parent-meter-for-ruling))
	     (width-of-ruling-markers-for-meter
	       (width-of-ruling-markers-for-meter parent-meter-for-ruling))
	     (space-for-ruling-labels-for-meter
	       (space-for-ruling-labels-for-meter parent-meter-for-ruling)))
	
	ruling-high-value-position
	
	(loop for mark-number 
		  from 0 to (1- (number-of-marks-for-meter
				  parent-meter-for-ruling))
	      as mark-position-in-meter
		 = (+ ruling-low-value-position
		      (round			       ; added by LH
			(* mark-number
			   distance-between-markings-for-meter)))
	      as mark-position
		 = (+w (top-edge-of-block parent-meter-for-ruling)
		       (-w (height-of-block parent-meter-for-ruling)
			   mark-position-in-meter))
	      as mark-x-position-in-window
		 = (x-in-window
		     (+w (left-edge-of-block parent-meter-for-ruling)
			 space-for-ruling-labels-for-meter))
	      as mark-y-position-in-window
		 = (y-in-window
		     mark-position)
	      do
	  (draw-solid-rectangle	
	    mark-x-position-in-window
	    mark-y-position-in-window
	    (+ mark-x-position-in-window
	       (delta-x-in-window length-of-ruling-markers-for-meter
				  current-image-x-scale))
	    (+ mark-y-position-in-window
	       (delta-y-in-window width-of-ruling-markers-for-meter
				  current-image-y-scale))
	    ruling-marker-color-difference))))

;    (draw-subblocks ruling-for-meter)
    )))

;; Changed background-color-value from 'icon-color region
;; to 'g2-icon-background region for all meter subblocks (pbk 2/6/96)



;;; The `draw method for marker-for-meter' draws a marker icon on top of the
;;; meter, which is assumed to have an icon description giving it an icon color
;;; that serves as a solid background color.  Therefore, this binds
;;; current-background-color to the icon color of the superblock (i.e., the
;;; meter).  (All of the subblocks of a meter must do this.)  This somewhat
;;; nongeneral scheme is needed only in order to get drawing to be correct when
;;; drawing in the XOR case.

(def-class-method draw (marker-for-meter)
  (let ((meter (superblock? marker-for-meter)))
    (when (and (not (block-is-currently-being-dragged-p meter))
	       (marker-position marker-for-meter))      
      (with-background-color-value
       (map-color-or-metacolor-to-color-value
	(item-color meter 'g2-icon-background)) ;pbk
       (draw-icon-for-entity marker-for-meter)))))

;; Changed background-color-value from 'icon-color region
;; to 'g2-icon-background region for all meter subblocks (pbk 12/27/95)








;;;; Readout Tables




;;; A `readout-table' is a table used to display a recent value of a variable.
;;; The table contains a left and a right cell.  The left cell is normally a 
;;; representation of the expressions-to-display slot.  The right cell is always 
;;; a representation of the readout-table-display-value slot.  The 
;;; label-to-display slot is normally blank.  If, however, it is edited so that 
;;; it has a non-blank text, the left cell of the readout table becomes a 
;;; representation of this slot rather than the expressions-to-display slot.  If 
;;; the label-to-display slot is cleared, then the left cell will revert to 
;;; being a representation of the expressions-to-display slot.  This mechanism 
;;; is provided so that users can replace long expressions with short labels and 
;;; thus keep readouts small.  There is some potential for confusion in that 
;;; some users might edit the left cell while it is a representation for the 
;;; label-to-display slot but think it is a representation for the 
;;; expressions-to-display slot.

(def-class (readout-table (item table)
			  (foundation-class readout-table) define-predicate)

  (display-update-task? nil no-accessor vector-slot system do-not-save)
  (task-for-display-continuation? nil no-accessor vector-slot system do-not-save)

  (expressions-to-display
    nil (type display-expression text)
    no-accessor lookup-slot system select-changes
    (attribute-export-comment "Export numerical-expression-parse?"))

  (label-to-display
    nil (type free text) lookup-slot system
    (attribute-export-comment "Export: string."))
  (format-for-readout-table
    nil system user-overridable lookup-slot (type format?)
    (attribute-export-comment "Export text-format-name"))
  (variables-for-expressions-to-display		; only if requested (see below)
    nil no-accessor lookup-slot save system)
  (display-up-to-date? nil no-accessor lookup-slot system)

  (display-update-interval
    5 (type display-interval) no-accessor lookup-slot system user-overridable
    (attribute-export-comment "export time interval part"))
  (display-wait-interval
    2 (type display-interval) no-accessor lookup-slot system user-overridable
        (attribute-export-comment "export time interval part"))
  (display-update-priority
    2 (type priority) no-accessor lookup-slot system user-overridable)

  (display-evaluation-should-use-simulated-values?	
    nil (type yes-or-no) no-accessor lookup-slot system user-overridable ;; see note with alias
    (attribute-export-comment "Export and alias to show-simulated-values? ?"))
;  (display-evaluation-should-not-trigger-variable-evaluation?
;    nil (type boolean) lookup-slot system)
;  (display-evaluation-should-interpolate?
;    nil (type boolean) lookup-slot system)
;  (expressions-to-display-should-be-kept-as-variables?
;    nil (type boolean) lookup-slot system)

  (show-expressions-displayed?
    t (type nil) no-accessor lookup-slot system)
    ;; (type yes-or-no?) when implemented!  ;; This old comment is obsolete now (12/18/96)
    ;;   and do alias without the "?"       ;; since that category has been expunged
                                            ;; largely to obviate the alias hack
;  (alternative-display-format-name?
;    nil (type text-box-format-name?) lookup-slot system)

  (variables-that-can-wake-up-this-display nil no-accessor lookup-slot system)
  (things-this-display-is-interested-in
    nil no-accessor lookup-slot system
    (attribute-export-comment "Associated with callback and registration? ~
 This and several other slots are repeated in related classes. Should be in
 a multiple-inheritance mixin."))
;  (time-that-wake-up-was-set-for-display nil no-accessor lookup-slot system)

  (default-readout-table-format-name readout-table-format)

  (readout-table-display-value 
    nil not-user-editable do-not-save (type value-for-readout-table) lookup-slot system
    (attribute-export-comment
      "Export: currently in attribute tables. Not showing up in doc?"))
  (tracing-and-breakpoints nil system user-overridable lookup-slot save
			   (type tracing-and-breakpoints)))

;; Readout-table-display-value, if not nil, is of the form (value type).

;; Use default-table-format for now.  Eventually may want to def-format-class
;; a readout-table-format.


(define-slot-alias expression-to-display expressions-to-display readout-table)

(define-slot-alias display-format format-for-readout-table readout-table)


(def-table-format readout-table-format
  table-left-border-width 1
  table-top-border-width 1
  table-right-border-width 1
  table-bottom-border-width 1
  table-row-boundary-width 1
  table-column-boundary-width 1)

(def-table-format-spot-generator readout-table-format (readout-table mouse-pointer)
  (generate-spot-for-input-table readout-table mouse-pointer
				 (make-readout-table-spot)))



(def-text-cell-format readout-table-text-cell-format
		      text-cell-paragraph-indentation 0
		      text-cell-turnover-line-indentation 18
		      minimum-format-width-for-text-cell 300
		      text-cell-left-margin 6
		      text-cell-top-margin 4
		      text-cell-right-margin 6
		      text-cell-bottom-margin 4)

;; Andy -- fill in all your format definitions, so they won't be affected by
;; changes to defaults!



;;; Make-readout-table ...

(defun make-readout-table (readout-table-class)
  (let* ((readout-table
	   (make-frame readout-table-class))
	 (readout-table-format
	   (get-or-make-format-frame
	     (slot-init-form
	       (get-slot-description-of-class-description 
		 'default-readout-table-format-name 
		 (class-description readout-table-class))))))
    (cond
      ((subclassp readout-table-class 'digital-clock)
       (setf (table-rows readout-table)
	     (slot-value-list
	       (slot-value-list
		 nil				; so it will update efficiently
		 (make-initial-readout-table-value-text readout-table))))
       ;; Digital clocks don't have expression text cells.
       )
      (t
       (setf (table-rows readout-table)
	     (slot-value-list
	       (slot-value-list
		 (make-initial-readout-table-expression-text readout-table)
		 (make-initial-readout-table-value-text readout-table))))))
    (make-or-reformat-table readout-table readout-table-format nil)
    (add-frame-representation-if-necessary readout-table readout-table)
    readout-table))

;; Note, can't just make the readout-table using make-or-reformat-table
;; because the readout-table itself is needed to initialize the slots.
;; This is the same dilemna that occurs when making a graph.


(defun make-initial-readout-table-expression-text (readout-table)
  (make-readout-table-expression-text
    readout-table 'expressions-to-display nil))

(defun make-readout-table-expression-text (readout-table slot-name class-qualifier?)
  (make-text-cell-for-slot
    readout-table
    slot-name class-qualifier? 
    (get-type-of-slot-if-any readout-table slot-name class-qualifier?)
    (get-or-make-format-frame 'readout-table-text-cell-format)))

;; Slot-to-represent can be 'expressions-to-display or 'label-to-display.


(defun make-initial-readout-table-value-text (readout-table)
  (make-text-cell-for-slot
    readout-table
    'readout-table-display-value nil
    (get-type-of-slot-if-any readout-table 'readout-table-display-value nil)
    (get-or-make-format-frame
      'readout-table-text-cell-format)))





;;; Updating a readout table invokes change-slot-value for the readout table
;;; display value of the readout-table if the value has changed.  Note that the
;;; actual value to be displayed is left cached in the expression cell, and the
;;; writer for this slot actually fetches the value from that location.  The
;;; logic for showing the value is all contained in the writer for this slot, in
;;; the file GRAMMAR7.

(define-cell-based-update-display-function readout-table
  (when (or update-even-if-value-unchanged?
	    (and new-cache? (null old-cache?))
	    (and old-cache? (null new-cache?))
	    (and new-cache? old-cache?
		 (not (evaluation-value-eql new-cache? old-cache?))))
    (change-slot-value readout-table 'readout-table-display-value nil)))
 


#+development
(defun print-outstanding-memory (memory-symbol)
  (format t "~s~%"
	  (pool-entry-outstanding-object-count
	    (assq memory-symbol
		  object-pool-meters))))
;; This is useful for checking if consing occurs, for example while 
;; updating a readout-table.


(define-clear-display-function readout-table
  (change-slot-value readout-table 'readout-table-display-value nil))


(define-activate-method-for-cell-based-display readout-table)

(define-deactivate-method-for-cell-based-display readout-table)



(def-class-method initialize-after-reading (readout-table)
  (funcall-superior-method readout-table)
  (update-representations-of-slot-value
    readout-table 'readout-table-display-value))






;;;; Digital Clocks

(def-class (digital-clock readout-table
			  (foundation-class digital-clock) define-predicate)
  (expressions-to-display
    nil ; (type display-expression text)
    do-not-put-in-attribute-tables
    lookup-slot system)
  (format-for-readout-table 
    (3 . 4) do-not-put-in-attribute-tables system lookup-slot user-overridable
    ; (type format?)
    )
  (display-evaluation-should-use-simulated-values?	
    nil  ;(type yes-or-no?) ;; 12/18/95 this category has been expunged. See Tables
    do-not-put-in-attribute-tables
    no-accessor lookup-slot system user-overridable)
  (readout-table-display-value 
    nil not-user-editable do-not-save 
    (type value-for-digital-clock) lookup-slot system)
  (tracing-and-breakpoints nil system lookup-slot user-overridable
			   do-not-put-in-attribute-tables))


;;; Updating a digital clock invokes change-slot-value for the 
;;; readout-table-display-value of the digital clock if the value has changed.
;;; There should always be a value for gensym time.

;; display-up-to-date? is slated for obselecence, because we want to be able to
;; do an update command when hidden, and when hidden, things will get out of date.

(define-update-display-function digital-clock
  (unless (block-is-currently-being-dragged-p digital-clock)
    ;; do this in define-update-display-function?
    (let ((old-display-value
	    (readout-table-display-value digital-clock))
	  (new-display-value (-f (clock-get gensym-time) (clock-get gensym-time-at-start))))
      (when (or (null old-display-value)
		(/=f old-display-value new-display-value))
	(change-slot-value 
	  digital-clock 'readout-table-display-value
	  new-display-value)
	(setf (display-up-to-date? digital-clock) t)))))

(define-activate-method-for-display digital-clock)

(define-deactivate-method-for-display digital-clock)

(define-clear-display-function digital-clock
  (change-slot-value digital-clock 'readout-table-display-value nil))




(def-class-method denote-cell-array-element
		  (dial component-particulars include-block-denotation?)
  (declare (ignore dial component-particulars include-block-denotation?))
  (twrite-string "the expression-to-display")
  (denote-component-of-block-1 '*current-computation-frame* " of "))

(def-class-method denote-cell-array-element
		  (meter component-particulars include-block-denotation?)
  (declare (ignore meter component-particulars include-block-denotation?))
  (twrite-string "the expression-to-display")
  (denote-component-of-block-1 '*current-computation-frame* " of "))

(def-class-method denote-cell-array-element
		  (readout-table component-particulars
				 include-block-denotation?)
  (declare (ignore readout-table component-particulars
		   include-block-denotation?))
  (twrite-string "the expression-to-display")
  (denote-component-of-block-1 '*current-computation-frame* " of "))




(defun update-computation-style-with-display-settings
       (computation-style display-frame)
  (reclaim-slot-value (computation-style-scan-interval computation-style))
  (setf (computation-style-scan-interval computation-style)
	(copy-for-slot-value 
	  (display-update-interval display-frame)))
  (reclaim-slot-value
    (computation-style-initial-scan-wait-interval computation-style))
  (setf (computation-style-initial-scan-wait-interval computation-style)
	(copy-for-slot-value
	  (display-wait-interval display-frame)))
  (setf (computation-style-priority computation-style)
	(display-update-priority display-frame))
  (setf (computation-style-value-domain computation-style)
	(if (display-evaluation-should-use-simulated-values?
	      display-frame)
	    'simulator
	    'inference-engine))
  (setf (computation-style-tracing-and-breakpoints computation-style)
	(tracing-and-breakpoints display-frame)))

(declare-forward-references (update-computation-style-for-trend-chart function graphs))

(defun update-cell-based-display-computation-style (display-frame &optional (cell-index 0))
  (let ((cell-array? (cell-array display-frame)))
    (when cell-array?
      (without-consistency-analysis (display-frame)
	(let ((*current-computation-frame* display-frame)
	      (current-computation-component-particulars nil)
	      (current-computation-style
		the-only-dynamic-computation-style)
	      (current-block-of-dependent-frame display-frame))
	  (with-phrase-conses
	    (with-part-description ((get-default-computation-style-of-class))
	      ;; Next update the computation style with the values in the
	      ;; display which affect scheduling and execution of the
	      ;; expression.
	      ;; The following line will go when the transition from
	      ;; from pre-4.0 graphs to 4.0 graphs is complete - JED 1/12/94
	      (cond ((frame-of-class-p display-frame 'trend-chart)
		     (update-computation-style-for-trend-chart
		       current-computation-style
		       current-computation-slot-component-group))
		    (t
		     (update-computation-style-with-display-settings
		       current-computation-style display-frame)))
	      (register-expression-cell-during-compilation
		cell-array? cell-index t)))))
      (register-expression-cell-during-slot-putter cell-array? cell-index t))))


(defun-simple update-display-if-not-reprocessed 
    (reference-serial-number display)
  (unless (frame-has-been-reprocessed-p display reference-serial-number)
    (funcall-method 'update-display display nil t nil)))



;;; This code was moved here from rules to pick up the accessors for the display
;;; wake-up slots.  -jra 7/19/88


;;;; Wake-up



(defun kind-of-display-p (frame)
  (or (dial-p frame)
      (meter-p frame)
      (readout-table-p frame)
      (digital-clock-p frame)
      (frame-of-class-p frame 'graph)
      (frame-of-class-p frame 'trend-chart)))

(defun kind-of-cell-based-display-p (frame)
  (or (dial-p frame)
      (meter-p frame)
      (and (readout-table-p frame)
	   (not (digital-clock-p frame)))
      (frame-of-class-p frame 'trend-chart)
      ;; More to come
      ))




;;; The function `variable-has-received-a-value' is called by variables in
;;; put-current-value when they have received a new value, with a first argument
;;; of some thing which was waiting for the new value, and a second argument of
;;; the variable which received the value.  The thing remove the variable from
;;; its list of things it is interested in, and schedule itself to execute, if
;;; it has not already done so.  It should not clear the list of the other
;;; things it is interested in, since this might lead them to believe there is
;;; no reason for them to run anymore.  This list will be cleared when they run
;;; again.

(defun variable-has-received-a-value (thing variable)
  (cond
    ((rule-instance-p thing)
     (setf (ri-things-this-rule-instance-is-interested-in thing)
	   (delete-eval-element
	     variable
	     (ri-things-this-rule-instance-is-interested-in thing)))
     (schedule-computation-instance-execution
       thing (ri-priority thing) (ri-rule thing))
     ;; (when (nupec-authorized-p)
     (update-backward-chaining-displays thing))
    ((code-body-invocation-p thing)
     (setf (things-this-code-body-invocation-is-interested-in thing)
	   (delete-eval-element
	     variable
	     (things-this-code-body-invocation-is-interested-in thing)))
     (wake-up-code-body-invocation thing))
    ((inference-background-collection-p thing)
     (setf (things-this-inference-background-collection-is-interested-in
	     thing)
	   (delete-eval-element
	     variable
	     (things-this-inference-background-collection-is-interested-in
	       thing)))
     (wake-up-inference-background-collection thing))
    ((framep thing)
     (cond
       ((variable-p thing)
	(setf (things-this-variable-is-interested-in thing)
	      (delete-eval-element
		variable
		(things-this-variable-is-interested-in thing)))
	(wake-up-variable thing)
	;; (when (nupec-authorized-p)
	(update-backward-chaining-displays thing))
       ((g2-expression-cell-p thing)
	(schedule-expression-cell-execution-given-cell
	  thing
	  (g2-cell-array-parent-frame (g2-expression-cell-g2-cell-array thing))
	  nil))
       ;; The kind of display-p thing below should instead be split into the following
       ;; categories of frames and handled seperately.
       ;; (or (dial-p frame)
       ;; (meter-p frame)
       ;; (readout-table-p frame)
       ;; (digital-clock-p frame)
       ;; (graph-p frame))
       ((kind-of-display-p thing)
	(setf (things-this-display-is-interested-in thing)
	      (delete-eval-element
		variable
		(things-this-display-is-interested-in thing)))
	(when (not (schedule-task-in-place-p
		     (task-for-display-continuation? thing)))
	  (with-current-scheduling ((task-for-display-continuation? thing)
				    (display-update-priority thing)
				    nil nil nil
				    ('reclaim-frame-serial-number))
	    (update-display-if-not-reprocessed
	      (copy-frame-serial-number (frame-serial-number thing)) thing))))))
    (t
     (warning-message 1
		      "G2 INTERNAL BUG, a wake up sent to ~a from ~NF.  Please inform ~
          Gensym Software Support of this G2 wake up bug!"
       thing variable))))




;;; When a variable is deactivated, it will notify those things which are
;;; interested in it that it is no longer available through this function,
;;; `variable-is-no-longer-available'.

(defun-simple variable-is-no-longer-available (thing variable)
  (cond
    ((rule-instance-p thing)
     (setf (ri-things-this-rule-instance-is-interested-in thing)
	   (delete-eval-element
	     variable
	     (ri-things-this-rule-instance-is-interested-in thing)))
     ;; (when (nupec-authorized-p)
     (update-backward-chaining-displays thing))
    ((code-body-invocation-p thing)
     (setf (things-this-code-body-invocation-is-interested-in thing)
	   (delete-eval-element
	     variable
	     (things-this-code-body-invocation-is-interested-in thing))))
    ((inference-background-collection-p thing)
     (setf (things-this-inference-background-collection-is-interested-in
	     thing)
	   (delete-eval-element
	     variable
	     (things-this-inference-background-collection-is-interested-in
	       thing)))
     nil)
    ((framep thing)
     (cond
       ((variable-p thing)
	(setf (things-this-variable-is-interested-in thing)
	      (delete-eval-element
		variable
		(things-this-variable-is-interested-in thing)))
	;; (when (nupec-authorized-p)
	(update-backward-chaining-displays thing))
       ;; The kind of display-p thing below should instead be split into the
       ;; following categories of frames and handled seperately.
       ;;
       ;; (or (dial-p frame)
       ;;     (meter-p frame)
       ;;     (readout-table-p frame)
       ;;     (digital-clock-p frame)
       ;;     (graph-p frame))
       
       ((kind-of-display-p thing)
	(setf (things-this-display-is-interested-in thing)
	      (delete-eval-element
		variable
		(things-this-display-is-interested-in thing))))
       ((g2-expression-cell-p thing)
	(let ((current-block-of-dependent-frame 
		(g2-cell-array-parent-frame
		  (g2-expression-cell-g2-cell-array thing))))
	  (setf (things-this-g2-expression-cell-is-interested-in thing)
		(delete-eval-element
		  variable
		  (things-this-g2-expression-cell-is-interested-in thing)))))))))






;;;; Event Detector Utility Functions




;;; The following functions implement facilities for event detectors.  They are
;;; included here so as to have access to the macro slot accessors of any
;;; currently conceivable consumer of event detections.

;;; The function `install-event-detector' takes a block, an event type, an event
;;; consumer, and an extra info argument.  It creates an event detector and
;;; installs it on the given frame.

(defun-simple install-event-detector (block event-type event-consumer extra-info)
  (let ((new-event-detector
	  (make-event-detector event-type block event-consumer extra-info)))
    #+SymScale
    (progn
      (eval-push-atomic new-event-detector
	(registered-event-detectors block))
      (eval-push-atomic new-event-detector
	(code-body-invocation-event-detectors event-consumer)))
    #-SymScale
    (eval-push new-event-detector
	       (registered-event-detectors block))
    #-SymScale
    (eval-push new-event-detector
	       (code-body-invocation-event-detectors event-consumer))
    nil))




;;; The function `clear-event-detectors' takes a consumer of events and clears
;;; all events registered in it from its list and from the block which was being
;;; monitored.

(defun-simple clear-event-detectors (event-consumer)
  (loop with event-list = #-SymScale (code-body-invocation-event-detectors event-consumer)
			  #+SymScale
			  (loop for old = (code-body-invocation-event-detectors event-consumer)
				do
			    (when (compare-and-swap
				    (code-body-invocation-event-detectors event-consumer) old nil)
			      (return old)))
	for event in event-list
	for block = (event-detector-monitored-block event)
	do
    ;; NOT thread-safe, use skip list?
    (setf (registered-event-detectors block)
	  (delete-eval-element event (registered-event-detectors block)))
    (reclaim-event-detector event)
	finally
	  (reclaim-eval-list event-list))
  #-SymScale
  (setf (code-body-invocation-event-detectors event-consumer) nil)
  nil)



;;; The function `trigger-event-detector' is called by code which executes when
;;; an event occurs and has found a registered event detector looking for the
;;; appropriate event.  This function should take the action called for by the
;;; consumer of the event, remove the event detector from both the consumer
;;; and the monitored block, and reclaim the event detector.

(defun-simple trigger-event-detector (event-detector)
  (let ((consumer (event-detector-consumer event-detector))
	(monitored-block (event-detector-monitored-block event-detector)))
    (setf (code-body-invocation-event-detectors consumer)
	  (delete-eval-element
	    event-detector
	    (code-body-invocation-event-detectors consumer)))
    (setf (registered-event-detectors monitored-block)
	  (delete-eval-element
	    event-detector
	    (registered-event-detectors monitored-block)))
    (reclaim-event-detector-macro event-detector)
    (wake-up-code-body-invocation consumer)
    nil))




;;; The function `trigger-and-clear-event-detectors' is called from delete-frame
;;; when a block which contains event detectors is being deactivated.

(defun-simple trigger-and-clear-event-detectors (monitored-block)
  (loop for event-detectors = (registered-event-detectors monitored-block)
	while event-detectors
	do
    (trigger-event-detector (car-of-cons event-detectors))))

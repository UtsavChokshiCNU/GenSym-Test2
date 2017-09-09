;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module GRAPHS1

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Andreas Hofmann







;; Notes

;; Time Axis

;; Universal time, rather than time since start, is now displayed on the 
;; time axis of a graph.  Full universal time is not printed in each 
;; label as this would take up too much space.  An appropriate format,
;; depending on the total time range, is used (min:sec, hrs:min, etc.).
;; The user should be able to tell from the context (by looking at
;; the desired range for horizontal axis slot of the graph, and also
;; by looking at a digital clock) what time units the labels show
;; and what the time is for the data being displayed.

;; The absolute format for specifying the horizontal range is now of the
;; form: "<interval> to <interval> after start".  An alternative would be
;; "<universal-time> to <universal-time>" but this may actually be less 
;; clear and less useful, especially since it would constantly have to 
;; be manually changed when the system is started.  Consider also allowing
;; "from <interval> ago to <interval> ago".  Note that this is a moving
;; window rather than absolute specification.  Note that slot compilers
;; prevent specifying a negative number in <interval> (see grammar).

;; It is easy to test time axis formatting.  Just put up a graph and edit 
;; the desired range for horizontal axis slot.  Don't need data and system
;; doesn't even have to be running.  The same is true for vertical axis.

;; I had considered scaling the horizontal axis labels, and perhaps the 
;; vertical axis ones as well in order to save space and allow for more
;; grid lines.  I decided against it since labels don't look good if they
;; are magnified by less than .9, and a magnification factor of .9 doesn't
;; save much space.  Also, since the magnification factor is kept in a 
;; format frame, it couldn't be changed for old kbs.  Eventually, a 
;; mechanism will be needed to allow for not putting up label for every
;; single grid line, especially on the horizontal axis.  This mechanism
;; would put up labels on the first and last grid lines and every nth
;; grid line in between.  It should be able to compute n based on the
;; number of grid lines and the graph size.  Also, consider moving the
;; first and last horizontal axis labels out further by a percentage
;; of their width.

;; Note that when the horizontal axis range is large, it takes longer
;; for data to be put on the graph (simple common sense).

;; The convention of having history times start at 0 at start is a good one.
;; This provides consistency for maintaining histories and graphs.

;; Incrementally Erasing Old Data Points

;; In draw-only-new-data-for-graph-grid, mechanism for incrementally erasing
;; obsolete data points has been disabled.  It was a neat hack but really
;; unnecessary given that there is nothing wrong with displaying extra 
;; history on a graph, even if that history is no longer actually in the
;; history buffers.  This allows for great simplification and efficiency
;; improvement of refresh-plot-data-buffer as well as the draw mechanism.
;; It will also prevent headaches later on when we do
;; data filtering.  It would be very difficult to "filter" the plot data
;; as well as the history data.  

;; Graph Formats

;; The format frame for graphs is pretty much "frozen" since it is saved with
;; old kbs.  Thus, it is difficult to add or delete slots (without having 
;; code check for their existence) and it is also difficult to change slot 
;; values and have the code depend on the new values.  The basic rule is
;; that the code must be able to deal with all old format frames as well
;; as new ones.  It does seem that we should have primitives to check for
;; existence of format slots to allow for distinguishing old format frames
;; from new ones.  If all else fails, bailout options include defining a new
;; class, or not using certain format frame slots at all but rather system 
;; variables and parameters.

;; Currently, there is one slot for specifying left and right margin widths.
;; It is desireable now to make the left margin wider than the right;
;; the left margin must be wide enough to hold axis labels, the right margin
;; can be much narrower (to save space).  However, due to the limitations,
;; rather than adding separate slots for left and right margin width to 
;; replace the single slot, it is better that the code use the existing 
;; slot and somehow compute the smaller right margin (to be perhaps 1/4 the
;; width of the left margin).

;; Due to changes in the minimum-graph-width slot of the default graph format
;; frame, it is necessary for the code to check if the graph-grid block fits within
;; the graph table superblock and if it doesn't, to make it fit.

;; 9/15/88 
;; Modified make-or-reformat-graph-grid so that left and right margins and top
;; and bottom margins are no longer symmetric.  Left margin is 80, right margin
;; is 5, top margin is 5, and bottom margin is 20.  The left margin is big
;; enough to accomodate vertical axis labels.  The bottom margin is big enough
;; to hold graph expressions.  Note that no changes were made to the format
;; frame.  Thus, the overall size of the graph is unchanged.  The grid has
;; become slightly bigger.  This is good because a bit more data can be
;; displayed, complete reformats happen a bit less frequently, and there is a
;; little more space between horizontal axis labels.  Can always change format
;; frame to make overall size smaller.  A change in the format frame would only
;; take effect for new graphs, not
;; existing graphs in old kbs (format frames are saved with kbs).

;; Scaling Issues

;; Note also that display coordinates kept in slots of the graph must be kept
;; in workspace units, since the graph may be drawn on more than one workspace
;; at different scales.  This is also the reason that image unit coordinates
;; can't be cached for data points in the plot data buffers.  If it can be
;; guaranteed that the graph will be displayed at only one scale at a time,
;; then this restriction could be lifted.

;; At small scales, it is possible for data points to x-or with each other
;; (see notes in design notebook for 3/16/88).  This is a very low priority
;; issue.




;;;; To Do for 2.0

;; (low priority)
;; Review use of default-graph-line-color-value with respect to plot color.
;; Currently, it isn't used at all.

;; Create_pixmap (in XWINDOWS.C) currently creates a new graphics context 
;; for each new pixmap.  There is no reason to do this.  Just use one
;; global one.

;; (low priority)
;; Do more speed tests including ones using 
;; co:/usr/gms/bench-graph.kb (Greg's benchmark kb).  See also notes at 
;; bottom of this file.

;; Add features in LOAD for whether to use color and whether to use polychrome
;; rasters (if such features don't already exist).  Make use of them.

;; (low priority for now)
;; Currently, some slots in graph-grid associated with the horizontal axis
;; (such as shift-horizontal-axis?, low-value-for-horizontal-axis-before-shift, 
;; and dateline) are assumed to be integers.  Review and change if necessary.

;; (low priority for now)
;; Probably not necessary to have the two sets of special variables: grid-width
;; and grid-height.  Review and consolidate.

;; (low priority)
;; Give capability to adjust default horizontal axis so that it doesn't reformat
;; so often at start?

;; Need to develop organized, official test for all the new formatting
;; options.  Make a table indicating all the possibilities and count up
;; all the possible formats.  Document at end of GRAPHS2.  Need to also
;; list all the new features.

;; There is currently a problem with editing the display expressions cell
;; for graphs when the cell is empty.  It is not sensitized to the edit
;; option in this case because there is no text on which to click.  This
;; is not a problem when there is text in the cell.  Bug or feature?

;; (low priority)
;; Consider doing bar charts, spider graphs, and real readout tables soon.

;; Consider modifying grammar of horizontal-graph-ruling-parameter? (and 
;; vertical also) to be 'compute 'automatically instead of 'none.

;; (low priority)
;; Review special variables.  Make graph-renderings a special var?
;; Low, high value for horizontal and vertical grid lines should no
;; longer have to be special.

;; (low priority)
;; The functions make-graph-rendering and make-graph-rendering-structure
;; are completely different.  Rename them.

;; Test with graph showing 500 data points.  Jim thinks binary search stuff
;; may be slowing things down.  It should be easy to improve this for 
;; strip chart mode.  Also, the graph should check if there is no new data
;; to be plotted and do nothing in this case.

;; Allow plotting of time before time of start.  This is necessary since
;; GFI can load data from before the time of start.

;; Declare forward references to add-from-graph-rendering-to-current-window
;; in PANES and DRAW.

;; Review erase.  Not needed to clear screen or graphic element memory.
;; Only needed for labels.

;; (low priority)
;; Review graph-grid slots.  Check if some of these can be removed.
;; Desired high and low value slots are good candidates.  If not needed for
;; drawing, then probably not needed since graph-grid is essentially a 
;; cache for drawing.

;; (low priority)
;; Currently calling compute-next-maximum-x-value twice, once in 
;; need-to-reformat-horizontal-axis?, and once in 
;; compute-new-parameters-for-horizontal-axis-of-grid.  Don't do this and
;; make sure that it isn't done for y axis either.

;; Review graph slots and whether bignums could occur for horizontal axis.
;; Currently, there are limits on the minimum and maximum values for the
;; horizontal axis to eliminate the possibility of bignums.  This also 
;; means that the shift-horizontal-axis? slot will never contain a bignum.


;; More to do

;; General expressions.  Don't worry about issue of determining time scales in
;; this mode.  Consider not allowing completely free format expression if no
;; horizontal axis specification is given.  Either flag as error or use some
;; default such as from time of start to current time.  Will have to modify the
;; current display evaluation done in compute-time-of-oldest-data-point,
;; compute-time-of-newest-data-point, and store-new-plot-data.  Note that
;; *current-computation-frame* is bound in make-or-reformat-graph-grid.  More such
;; special variables will have to be bound when general expressions are allowed.
;; A mechanism like get-new-value-for-display should probably be set up for this
;; purpose.  Note that it is probably worth making a special case for
;; expressions that designate just a variable (for efficiency reasons).  I think
;; that 95% of all graph expressions will just be designations anyway.  This is
;; certainly the case with other display expressions.  Note also that graph
;; expressions (unlike display expressions) are not compiled since they
;; currently are simply designations for variables.  This will also have to change
;; in order to allow for general expressions.

;; Spending a lot of time recomputing horizontal axis.  The time is not
;; being spent on refreshing the plot data buffer;  recomputing the vertical
;; axis is much faster and involves refreshing the plot data buffer as well.

;; (low priority)
;; Consider reducing use of format frames in graphs (see notes at top of file).

;; (low priority)
;; Review compute-minimum-right-edge and compute-minimum-bottom-edge.
;; Loading bringing formats up to date works but these methods should be
;; reviewed.

;; (low priority)
;; Review using data driven approach for updating plot data buffers more
;; quickly.  Should be able to maintain indices for various histories.
;; In some cases, however, this may not be as efficient as the current
;; evaluation using interval sub-division.

;; (low priority)
;; Get rid of special variables that don't have to be special.

;; (low priority)
;; Review keep-interval slots in graph-format.  These aren't currently
;; used.

;; (high priority)
;; Time axis labels aren't offset properly in the following case:
;; - 1 minute for horizontal axis format
;; - no vertical axis format
;; - showing simulated values of variable that has "the current time"
;; as its simulation formula.
;; Happens only when only reformatting vertical axis.  Works fine
;; when reformatting horizontal axis.

;; (low priority)
;; Consider getting rid of grid line spacing options in graph format.
;; They are not currently used and probably never will be.

;; (low priority)
;; Consider moving the print functions for make-new-time-axis-label to
;; FRAMES3 where the basic time printing functions currently reside.  Talk
;; to Mark.

;; (low priority)
;; Consider scaling labels by 3/4, at least along the x axis.

;; (low priority)
;; Review horizontal axis formatting.

;; (low priority)
;; On vertical axis, consider not writing floating point number if it isn't.
;; Also, consider abstracting label making more for vertical axis.  
;; Parameterize formats for writing floating point numbers for these labels.

;; (low priority)
;; Consider using leave-text-representation-as-a-single-line? mechanism for 
;; label boxes of graphs 
;; (see also slot value writer for value-for-readout-table).

;; (low priority)
;; In draw-graph-grid, use +f etc. for image coordinates.

;; (high priority)
;; Test "the current time" on a graph with no formats specified.
;; At times, it seems that it isn't displaying all the data.

;; (low priority)
;; Put up error message if graph is attempting to display symbolic values.
;; Doesn't bomb out currently but doesn't put up message either.

;; (resolved but document better)
;; In make-or-reformat-graph-grid, when (right-edge-of-block graph-grid)
;; is being set, minimum-graph-width rather than minimum-grid-width is
;; used.  Review this.
;; The reason for this is that minimum-grid-width is the width of the 
;; grid pattern in the graph-grid (without the margins) but is not the
;; width of the graph-grid block.  The graph-grid block has the same
;; width (and same left and right edges) as the graph.
;; - agh 2/21/88

;; (low priority)
;; Handle case where (use-one-set-of-axes? graph-format) is nil
;; (see compute-new-parameters-for-vertical-axis-of-grid) etc.

;; (high priority)
;; If no history is being kept, the graph should put up some kind
;; of notify user message rather than just not doing anything.

;; (low priority)
;; Reformat so that plot begins at left edge when starting?

;; Should time-graph be a sub-class of graph?

;; (low priority)
;; For graph draw functions, consider making a "with" wrapper to bind
;; local and special variables (similar to on-image-plane).

;; (low priority)
;; When everything settles, check if there is unnecessary duplication
;; in graph and plot frames of slots in graph-format and plot-format frames.
;; function-to-access-data-point and perhaps function-to-check-if-data-exists
;; can go away.

;; If horizontal axis is time axis, don't need to use managed numbers for
;; most of its parameters since they are integers.  Consider special casing
;; this.


;;;; Overview

;;; A graph is a table with a number of cells.  These include sub-tables
;;; for headings and numeric labels, and a graph-grid block.  Both graph
;;; and graph-grid have their own class definitions.  A graph is based
;;; on history values collected, either simulated or monitored, for some
;;; variable.  The horizontal axis is therefore always for time and the
;;; vertical axis is for the value.  Only linear rulings are used for
;;; both axes; no logarithmic or otherwise warped rulings are provided
;;; even though histories for very old values are averaged and kept less
;;; frequently.
;;; 
;;; There are two basic modes for determining ruling: automatic, and user
;;; specified.  In automatic mode, ruling is determined by the system.  In
;;; user specified mode, the user determines the ruling.
;;; 
;;; The capability to update graphs in real time as new data arrives is 
;;; provided.  This is an animation-like capability and involves refreshing the	
;;; display or scheduling a task to refresh the display.
;;;
;;; The capability to display more than one value on the same graph is also
;;; provided.  In this case, the lowest and highest values for purposes of
;;; ruling determination are the minimum and maximum respectively of the
;;; lowest and highest values for each variable.
;;;

;; See note on using blocks rather than
;; text-cells as cells of tables (in "tables").

;;;; Forward References to Support New Graphs

;;; These functions will be referenced during the transition period in which pre-4.0
;;; and 4.0 graphs coexist.  Both GRAPHS1 and GRAPHS2 will be deleted after this transition
;;; is complete. - JED 1/12/94

(declare-forward-references
  (inner-full-paint-2d-grid function graphs)
  (inner-partial-paint-2d-grid function graphs)
  (remove-graph-rendering-from-trend-chart function graphs))

(declare-forward-reference paint-graph-to-native-printer function)
(declare-forward-reference remove-graph-rendering-from-chart function)


(defvar current-plot)
(defvar low-and-high-values-specified-for-vertical-axis?)
(defvar scale-y-data-points?)
(defvar current-graph-grid)
(defvar current-data-buffer-for-plot)
(defvar current-plot-number)
(defvar low-value-for-horizontal-axis)
(defvar many-more-data-points-than-pixels?)
(defvar history-time-to-evaluate-display-expression-with)
(defvar ring-buffer-for-history-time)
(defvar current-cascaded-ring-buffer)
(defvar current-index)
(defvar most-recent-extremum-maximum-for-pixel-p)
(defvar index-for-stop-time)
(defvar most-recent-extremum-maximum-p)
(defvar x-data-min-set?)
(defvar x-value-on-graph)
(defvar interval-between-plot-markers)
(defvar plot-marker?)
(defvar erase-dateline)
(defvar minimum-and-maximum-y-value-set?)
(defvar fixnum-minimum-y-value)
(defvar fixnum-maximum-y-value)
(defvar plot-min-and-max?)

(def-system-variable history-time-per-pixel GRAPHS2
  (:funcall initialize-to-managed-float-box))

(def-system-variable last-history-time-for-data-point-on-pixel GRAPHS2
  (:funcall initialize-to-managed-float-box))

(def-system-variable data-point-value GRAPHS2
  (:funcall initialize-to-managed-float-box))

(def-system-variable minimum-y-value-for-pixel GRAPHS2
  (:funcall initialize-to-managed-float-box))

(def-system-variable maximum-y-value-for-pixel GRAPHS2
  (:funcall initialize-to-managed-float-box))

(def-system-variable minimum-y-value GRAPHS2
  (:funcall initialize-to-managed-float-box))

(def-system-variable maximum-y-value GRAPHS2
  (:funcall initialize-to-managed-float-box))

(def-system-variable plot-min? GRAPHS2
  (:funcall initialize-to-managed-float-box))

(def-system-variable plot-max? GRAPHS2
  (:funcall initialize-to-managed-float-box))

(def-system-variable vertical-axis-range GRAPHS2
  (:funcall initialize-to-managed-float-box))

(def-system-variable low-value-for-vertical-axis GRAPHS2
  (:funcall initialize-to-managed-float-box))

(def-system-variable handy-float-1 GRAPHS2
  (:funcall initialize-to-managed-float-box))

(defun initialize-to-managed-float-box ()
  (allocate-managed-float-box))





(def-system-variable default-duration-for-data-point graphs1 0.5)


;;; Default-graph-left-margin-width and default-graph-right-margin-width
;;; are used by make-or-reformat-graph-grid if the graph-grid is 
;;; bigger than the graph (see note at bottom of make-or-reformat-graph-grid).

(defparameter default-graph-left-margin-width 60)

(defparameter default-graph-right-margin-width 0)


(defparameter default-data-point-y-size 4)


(defparameter erase-zone-ratio 0.1)




;;; Minimum-range-to-maximum-value-ratio is used by determine-ruling-for-axis.
;;; See documentation of this function for details.

(defparameter minimum-range-to-maximum-value-ratio 0.01)


;;; Default-axis-half-range is used by compute-new-parameters-for-vertical-axis-of-grid
;;; if there is no data and no vertical axis range is specified by the user.

(defparameter default-axis-half-range 1)


;;; Default-interval-between-vertical-grid-lines,
;;; default-number-of-vertical-grid-lines are used in 
;;; compute-new-parameters-for-horizontal-axis-of-grid if there is no data 
;;; and no absolute range is specified.

(defparameter default-interval-between-vertical-grid-lines 1)

(defparameter default-number-of-vertical-grid-lines 5)

(defparameter maximum-number-of-horizontal-grid-lines 500)

(defparameter default-number-of-markers 6)

;; Consider making this a user parameter.



;;; Redraw-as-well-as-reformat-p must be bound when make-or-reformat-graph-grid 
;;; is called.  If t, the graph will be redrawn as well as reformatted.

(defvar redraw-as-well-as-reformat-p)




;;;; Graph Formats


;; Ruling and Other Format Calculations

;; minimum and maximum values for horizontal and vertical axes
;;      |
;;      |
;; ranges for axes  <-- can also be user specified
;;      |
;;      |
;; intervals between grid lines
;; number of grid lines   <-- can also be user specified
;; low value and high value for grid lines
;;      |
;;      |
;; Given size of graph, number of grid lines
;; Calculate grid line spacing for graph  <-- can also be user specified


;; Note that intervals between grid lines, and low value and high value for
;; grid lines are never user specified.  This ensures that these have "normal"
;; values.  The user always has the option to specify (somehow) ranges for the 
;; axes.  Additionally, the user has the option to specify the number 
;; of grid lines and/or the grid line spacing.  Grid line spacing is calculated
;; by
;; grid line spacing = size of graph / number of grid lines
;; 
;; Thus, if number of grid lines is specified, size of graph will remain the
;; same and grid line spacing will be calculated by the above formula.
;; Similarly, if grid line spacing is specified, number of grid lines can
;; be calculated.
;; If both number of grid lines and grid line spacing are specified, then
;; size of graph has to change.  It should actually only get larger.


;; The mechanism for these specifications should be the format frames.
;; Hold off for now on passing extra arguments to make-or-reformat-graph.

;; The important slots for formatting are
;; 
;; minimum-graph-left-and-right-margin-width
;; minimum-graph-top-and-bottom-margin-width
;; minimum-graph-width
;; minimum-graph-height
;; number-of-horizontal-grid-lines?
;; number-of-vertical-grid-lines?
;; horizontal-grid-line-spacing?
;; vertical-grid-line-spacing?

;; Corresponding slots exist in graph (with different names of course,
;; typically without the "?")


;; Consider different formatting for initial graph and resize.
;; For initial graph, may want everything automatic but thereafter,
;; keep some things constant.  For example, may want to keep the grid line
;; spacing and the intervals between grid lines the same.  The intervals
;; between grid lines are then used to determine the number of grid lines 
;; needed to display the required range.  The number of grid lines and
;; the grid line spacing are then used to compute the size of graph.
;; In this way, the graph will grow as data comes in.
;; This can be accomplished by the following slots in the format
;; frame:

;; keep-interval-between-horizontal-grid-lines-same?
;; keep-interval-between-vertical-grid-lines-same?
;; keep-horizontal-grid-line-spacing-same?
;; keep-vertical-grid-line-spacing-same?

;; These slots should be checked only when reformatting, not when 
;; making the graph initially.




(def-table-format table-format-for-graphs	; call this "default-..."?

  table-left-border-width 1
  table-top-border-width 1
  table-right-border-width 1
  table-bottom-border-width 1

  table-row-boundary-width 0)


;;; The table-format-spot-generator `table-format-for-graphs' pushes just a
;;; graph-table-spot, unless the click was in the text of the graph label.

(def-table-format-spot-generator table-format-for-graphs (table-for-graph mouse-pointer)
  (let ((input-table-spot (make-graph-table-spot)))
    (fill-out-table-spot input-table-spot table-for-graph mouse-pointer)

    (let ((table-cell? (table-cell-of-spot? input-table-spot))
	  (tightness (tightness-of-text-spot input-table-spot)))

      (cond ((and (not (cell-is-block-p table-cell?))
		  (<f tightness 100))				    ; In the graph label
	     (generate-spot-for-input-table table-for-graph mouse-pointer
					    input-table-spot))
	    (t
	     (push-last-spot mouse-pointer input-table-spot table-for-graph))))))





;;; A `graph format' ...  When the horizontal and vertical grid line colors differ, the
;;; horizontal color will prevail at the intersections.

(def-format-class (graph-format format-frame)	; used as a graph type

  (graph-line-color? black vector-slot system	        ; defaults to supertable line color,
		     save)                              ;   or else to current-default-line-color
  (graph-background-color? nil vector-slot system	; defaults to supertable background
			   save)                        ;   color, or else to transparent

  (minimum-graph-left-and-right-margin-width		; 0 for none; in workspace units
    80 vector-slot system save)
  (minimum-graph-top-and-bottom-margin-width		; 0 for none; in workspace units
    20 vector-slot system save)
  (graph-margin-color? nil vector-slot system save)    	; defaults to graph background color

  (graph-horizontal-grid-line-width		; 0 for none; in workspace units
    1 vector-slot system save)
  (graph-horizontal-grid-line-color?		; defaults to current-default-line-color
    black vector-slot system save)

  (graph-vertical-grid-line-width		; 0 for none; in workspace units
    1 vector-slot system save)
  (graph-vertical-grid-line-color?		; defaults to current-default-line-color
    black vector-slot system save)

  (minimum-graph-width				; before 2.0: 500
    300 vector-slot system save)
  (minimum-graph-height				; before 2.0: 300
    200 vector-slot system save)

  (number-of-horizontal-grid-lines?   ; 6 for test purposes
    nil vector-slot system save)
  (number-of-vertical-grid-lines?     ; 6 for test purposes
    nil vector-slot system save)
  (horizontal-grid-line-spacing?
    nil vector-slot system save)
  (vertical-grid-line-spacing?
    nil vector-slot system save)

  (minimum-interval-between-horizontal-grid-lines
    0.1
    vector-slot system save)
  (minimum-number-of-horizontal-grid-lines
    4 vector-slot system save)
  (minimum-interval-between-vertical-grid-lines
    0.001
    vector-slot system save)
  (minimum-number-of-vertical-grid-lines
    3 vector-slot system save)

  (data-point-size
    10 vector-slot system save)
  (minimum-distance-for-data-points
    10 vector-slot system save)

  (use-one-set-of-axes?
    t vector-slot system save)

  (keep-interval-between-horizontal-grid-lines-same?
    nil vector-slot system save)
  (keep-interval-between-vertical-grid-lines-same?
    nil vector-slot system save)
  (keep-horizontal-grid-line-spacing-same?
    nil vector-slot system save)
  (keep-vertical-grid-line-spacing-same?
    nil vector-slot system save)
  (extra-range-for-low-end-of-horizontal-axis
    0 vector-slot system save)
  (extra-range-for-high-end-of-horizontal-axis
    0.4
    vector-slot system save)
  (extra-range-for-low-end-of-vertical-axis
    0.4
    vector-slot system save)
  (extra-range-for-high-end-of-vertical-axis
    0.4 
    vector-slot system save)
  (reformat-grid-only-if-absolutely-necessary?
    t vector-slot system save)
  )

;; The "extra-range" parameters are specified in terms of the fraction
;; of the range of the actual data to leave at an end of an axis.  They
;; are used when a new grid has to be computed and allow for leaving
;; extra space when this happens.  The extra space may then allow for
;; the same grid to be used for several updates, even as new data is
;; added.  This is one way of avoiding constant automatic reformatting.

;; The "extra-range" parameters are no longer used for the horizontal
;; axis.  They are no longer needed due to all the capabilities of the
;; scrolling mechanism.  - agh 7/1/89

;; Use-one-set-of-axes? indicates whether the same set (of axes labellings)
;; should be used for all plots.  This defaults to t.  If this is nil,
;; then the axes rulings computed for each individual plot will be used
;; and the graph will have multiple labellings for the axes.

;; x and y magnifications?

;; graph-selection-actions?




;;; Graph-format-for-books is the default graph format for graphs to be put
;;; into books (see also "books").

(def-graph-format graph-format-for-books)


;(def-absent-slot-putter desired-low-value-for-horizontal-axis?
;			(default-graph-format slot-value))
;(def-absent-slot-putter desired-high-value-for-horizontal-axis?
;			(default-graph-format slot-value))
;(def-absent-slot-putter desired-low-value-for-vertical-axis?
;			(default-graph-format slot-value))
;(def-absent-slot-putter desired-high-value-for-vertical-axis?
;			(default-graph-format slot-value))
;; No kbs should have these slots


(def-format-class (plot-format format-frame)

  (plot-line-color? black vector-slot system)		; defaults to graph-line-color, 
						; supertable color
						;   or else to current-default-line-color

  (plot-pattern? nil vector-slot system)			; not yet implemented

  (use-this-grid-for-all-plots?
    nil vector-slot system)
  )


;;;; Class Definitions for Graphs and Plots

;;; A graph is a table.

(def-class (graph (item table) define-predicate
		  (class-export-comment "Possible exported attributes ~
 and attribute-mimics:<br> ~
 <ul><LI>desired-range-for-horizontal-axis: (or none [start-value: integer, ~
 start-units: time-unit-symbol, end-value: integer, end-units: ~
 time-unit-symbol, include-tickmark-labels: boolean]),
 <LI>desired-range-for-vertical-axis: (or none [start-value: integer, ~
 start-units: time-unit-symbol, end-value: integer, end-units: ~
 time-unit-symbol, include-tickmark-labels: boolean]), 
 <LI>scroll-continuously?: boolean, 
 <LI>percentage-extra-space-to-leave: integer, 
 <LI>show-grid-lines?: boolean,
 <LI>interval-between-horizontal-grid-lines?: (or 'compute-automatically ~
 [interval: integer, start-value: integer])
 <LI>extra-grid-lines?: (or 'none ((or none [position: integer, color: ~
 color-symbol]) *)),
 <LI>background-colors: (color-symbol *), [graph-background: color-symbol, ~
 grid-background: color-symbol],
 <LI>expressions-to-display: (numerical-expression-parse *),
 <LI>label-to-display: string, 
 <LI>display-update-interval: time-interval-part,
 <LI>display-wait-interval: time-interval-part,
 <LI>display-update-priority: integer,
 <LI>show-simulated-values: boolean,</ul>"))

  (frame-flags #.opaque-block-flag)

;  (name-or-names-for-frame
;    nil 
;    do-not-put-in-attribute-tables)            ; commented out -- allow user 
						;  access.  (MHD 7/3/91)
;OBS:  ;; Displays don't currently have names.

  ;; The following vector slots have the same SVREF index with those slots for
  ;; defined in display.lisp under the same names. -- Chun Tian (binghe), 2015/4/2
  (display-update-task? nil no-accessor vector-slot system do-not-save)
  (task-for-display-continuation? nil no-accessor vector-slot system do-not-save)

  (graph-format nil vector-slot system save)

  (desired-range-for-horizontal-axis?
    nil
    (type horizontal-graph-ruling-parameter?) vector-slot system
    user-overridable)
  (desired-range-for-vertical-axis?
    nil (type vertical-graph-ruling-parameter?) vector-slot system
    user-overridable)
  (scroll-continuously? nil (type yes-or-no) vector-slot system
			user-overridable)

  (percentage-extra-space-to-leave 0 (type integer) vector-slot system
				   user-overridable)
  ;; Percentage extra space to leave is applicable whether scrolling
  ;; continuously or not.  Therefore, a separate slot is used rather than
  ;; combining this with the scroll-continuously? slot.

  (show-grid-lines? t (type yes-or-no) vector-slot system user-overridable)
  ;; This will become more complicated!  Allow specifications for both 
  ;; vertical and horizontal grid lines, for color, pattern, and width.
  ;; Also, this needs a slot putter so that when it is edited, the graph
  ;; is redrawn.

  (interval-between-horizontal-grid-lines?
    nil (type horizontal-gridline-interval?) vector-slot system
    user-overridable)

  (extra-grid-lines?
    nil (type extra-grid-line-specs) vector-slot system
    user-overridable)

  (background-colors
    (white . white) (type graph-background-colors) lookup-slot system
    user-overridable)

  ;; The following slots are the same as the ones for readouts.
  ;; If these become vector slots at some point, give them
  ;; unique names.

  (expressions-to-display
    nil (type list-of-graph-expressions text) no-accessor lookup-slot system select-changes)
  (label-to-display
    nil (type free text) no-accessor lookup-slot system)
  (variables-for-expressions-to-display		; only if requested (see below)
    nil no-accessor lookup-slot save system)
  (display-up-to-date? nil no-accessor lookup-slot system)

  (display-update-interval
    5 (type display-interval) no-accessor lookup-slot system user-overridable)
  (display-wait-interval
    2 (type display-interval) no-accessor lookup-slot system user-overridable)
  (display-update-priority
    2 (type priority) no-accessor lookup-slot system user-overridable)

  (display-evaluation-should-use-simulated-values?
    nil (type yes-or-no) no-accessor lookup-slot system user-overridable)
    ;; This used to be type yes-or-no? See Tables

;  (display-evaluation-should-not-trigger-variable-evaluation?
;    nil (type boolean) no-accessor lookup-slot system)
;  (display-evaluation-should-interpolate?
;    nil (type boolean) no-accessor lookup-slot system)
;  (expressions-to-display-should-be-kept-as-variables?
;    nil (type boolean) no-accessor lookup-slot system)

  (variables-that-can-wake-up-this-display nil no-accessor lookup-slot system)
;  (time-that-wake-up-was-set-for-display nil no-accessor lookup-slot system)
  (things-this-display-is-interested-in nil no-accessor lookup-slot system)

  (graph-reformatted-since-start? nil lookup-slot system))

;; For desired horizontal and vertical high and low values, both the
;; high and low value must be specified.  Need a slot putter which puts
;; up a frame note, and possibly posts a user note to check this.

;; Note that the "desired-..." slots specify desired values.
;; The actual axis values are computed automatically and are subject
;; to other considerations, such as number of grid lines, as well.


(define-slot-alias desired-range-for-horizontal-axis desired-range-for-horizontal-axis?)

(define-slot-alias desired-range-for-vertical-axis desired-range-for-vertical-axis?)




;; Changed to not have the "?" because not of type yes-or-no. (MHD 11/7/88)


;;; The 'without-tickmark-labels' attribute for an axis is represented as a wrapper around
;;; the parse of desired-range-for-<foo>-axis. It is true if the car of the parse is
;;; 'without-tickmark-labels' and false otherwise. This was implemented as an extension
;;; to the original slot parse.

(defmacro remove-tickmark-label-annotation (parse)
  (let ((parse-var '#:parse-var))
    `(let ((,parse-var ,parse))
       (if (and (consp ,parse-var) (eq (car ,parse-var) 'without-tickmark-labels))
	   (values (cdr ,parse-var) t)
	   (values ,parse-var nil)))))

(defmacro desired-range-for-horizontal-axis-without-tickmark-info? (graph)
  `(remove-tickmark-label-annotation (desired-range-for-horizontal-axis? ,graph)))

(defmacro desired-range-for-vertical-axis-without-tickmark-info? (graph)
  `(remove-tickmark-label-annotation (desired-range-for-vertical-axis?   ,graph)))


;;; A graph-grid is a block.  None of its slots are saved.  It is used
;;; to cache values computed during formatting for use when drawing.

(def-class (graph-grid block define-predicate)

  (desired-low-value-for-horizontal-axis nil vector-slot system)
  (desired-high-value-for-horizontal-axis nil vector-slot system)
  (desired-low-value-for-vertical-axis nil vector-slot system)
  (desired-high-value-for-vertical-axis nil vector-slot system)

  (interval-between-horizontal-grid-lines nil vector-slot system)
  (low-value-for-horizontal-grid-lines nil vector-slot system)
  (high-value-for-horizontal-grid-lines nil vector-slot system)
  (number-of-horizontal-grid-lines nil vector-slot system)
  (horizontal-grid-line-spacing nil vector-slot system)
  (spacing-between-top-edge-and-grid-line nil vector-slot system)

  (interval-between-vertical-grid-lines nil vector-slot system)
  (low-value-for-vertical-grid-lines nil vector-slot system)
  (high-value-for-vertical-grid-lines nil vector-slot system)
  (number-of-vertical-grid-lines nil vector-slot system)
  (vertical-grid-line-spacing nil vector-slot system) 
  (spacing-between-right-edge-and-grid-line nil vector-slot system)
  (label-scale-for-vertical-grid-lines nil vector-slot system)

  (list-of-plots
    nil vector-slot system save)

  (grid-width-for-graph nil vector-slot system)
  (grid-height-for-graph nil vector-slot system)
  (horizontal-axis-range nil vector-slot system)
  (vertical-axis-range nil vector-slot system)

  (graph-left-margin-width nil vector-slot system)
  (graph-right-margin-width nil vector-slot system)
  (graph-top-margin-width nil vector-slot system)
  (graph-bottom-margin-width nil vector-slot system)

  (graph-renderings nil vector-slot system)
  (shift-horizontal-axis? nil vector-slot system)
  (low-value-for-horizontal-axis nil vector-slot system)
  (low-value-for-horizontal-axis-before-shift nil vector-slot system)
  (high-value-for-horizontal-axis nil vector-slot system)
  (low-value-for-vertical-axis nil vector-slot system)
  (high-value-for-vertical-axis nil vector-slot system)
  (dateline 0 vector-slot system)
  (old-dateline 0 vector-slot system)
  (new-scrolled-vertical-grid-line-positions nil vector-slot system)

  (graph-description-up-to-date? nil vector-slot system)
  (currently-up-to-date-image-planes nil vector-slot system)

  (interval-between-plot-markers nil vector-slot system)

  (horizontal-axis-high-value-label nil vector-slot system)

  (line-drawing-description-for-graph-grid? nil vector-slot system)
  (tail-pointer-for-line-drawing-description nil vector-slot system)
  (tail-pointer-for-line-segments nil vector-slot system)

  (grid-and-erase-zone-width nil vector-slot system)
  (horizontal-axis-and-erase-zone-range nil vector-slot system)

  (draw-graph-rendering-to-show-new-data? nil vector-slot system)
  (old-dateline-in-workspace-units 0 vector-slot system)
  )

;; The spacing slots contain floats used when drawing the graph grid.  The floats
;; are rounded to produce workspace coordinates.

;; Although the graph-grid class could conceivably be replaced with a structure,
;; this would require eliminating the draw method for graph-grid and making
;; one for graph instead.



;;; Make-graph-not-up-to-date clears the graph-description-up-to-date? and
;;; currently-up-to-date-image-planes slots of graph-grid.  This ensures 
;;; that if a graph becomes not up to date, all graph renderings will be
;;; repainted the next time they are drawn.

(defun make-graph-not-up-to-date (graph-grid)
  (reclaim-graph-list (currently-up-to-date-image-planes graph-grid))
  (setf (graph-description-up-to-date? graph-grid) nil
	(currently-up-to-date-image-planes graph-grid) nil))



(defun remove-graph-rendering-from-graph-grid
       (graph-rendering graph-grid-or-chart)
  ;; The following protection is only needed for the relatively rare case that
  ;; charts (and maybe tc's and graphs) are deleted while printing (or PLAYER-ing)
  ;; Ugh.
  (when (get-item-if-item-reference (graph-rendering-parent? graph-rendering))
    (frame-class-case graph-grid-or-chart
      (graph-grid
	(delete-from-set (graph-renderings graph-grid-or-chart) graph-rendering)
	;; This guard is necessary to prevent printing from clobbering graphs
	;; in non-printer windows. Note that current-window need not be bound
	;; in non-printing contexts (in particular, when we are called from
	;; decache-graph-rendering from the cleanup method of graph-grid).
	(unless (and (printing-p)
		     (printing-window-p current-window))
	  (make-graph-not-up-to-date graph-grid-or-chart)
	  (let ((graph (superblock? graph-grid-or-chart)))
	    (when graph				; may be nil if deleting
	      (setf (graph-reformatted-since-start? graph) nil)))))
      (chart
	(remove-graph-rendering-from-chart	; in CHARTS
	  graph-rendering graph-grid-or-chart))
      (trend-chart
	(remove-graph-rendering-from-trend-chart
	  graph-rendering graph-grid-or-chart)))))



(defun decache-and-remove-all-graph-renderings-from-graph-grid (graph-grid)
  ;; We are called only from make-or-reformat-graph-grid when resizing a graph
  ;; (due to either a resize menu choice or add/remove tickmark labels).
  ;; It is necessary to decache in these cases to avoid a memory leak (see the
  ;; comment below graph-grid's cleanup method).
  (decache-all-graph-renderings-of-graph-grid graph-grid)
  (reclaim-eval-list (graph-renderings graph-grid))
  (setf (graph-renderings graph-grid) nil)
  (make-graph-not-up-to-date graph-grid)
  (let ((graph (superblock? graph-grid)))
    (when graph					       ; may be nil if deleting
      (setf (graph-reformatted-since-start? graph) nil))))

(defun decache-all-graph-renderings-of-graph-grid (graph-grid)
  (loop for graph-rendering in (graph-renderings graph-grid)
	do (decache-graph-rendering graph-rendering)))


(defmacro get-graph-grid-given-graph (graph)
  `(first (first (table-rows ,graph))))



(def-class-method cleanup (graph)
  (funcall-superior-method graph)
  (change-slot-value graph 'expressions-to-display nil)
  ;; This reclaims slot value conses automatically.
  )


(def-class-method cleanup (graph-grid)
  (funcall-superior-method graph-grid)
  (decache-all-graph-renderings-of-graph-grid graph-grid))

;; Despite the comment immediately below, it is necessary to decache graph
;; renderings when a graph is deleted.  Otherwise, such decaching gets tallied
;; into the thrashing counts and this can cause the memory allocated for graphs
;; to keep increasing without bound.  To see this, repeatedly clone a graph and
;; delete the clone.  To monitor the graph pools and caching state, see the KB
;; /home/agh/agh-on-ma/graph-decaching-test.kb.

;; [This note is no longer valid, see the comment immediately above]
;; Note that there is no need to explicitly reclaim graph renderings here.  The
;; graph renderings will eventually either be decached during normal operation of
;; the decaching mechanism, or they will be reclaimed when the window is deleted.
;; The corresponding-graph-grid-or-chart?  slot of each graph rendering is set to nil so
;; that compute-cost-of-decaching-graph-rendering will return 0 for the cost of
;; decaching (since the graph is deleted).

;; Note that a slot reclaimer for list-of-plots is no longer necessary since plots
;; are now dependent frames and reclaim-slot-value takes care of dependent frames
;; automatically.



(def-slot-value-reclaimer line-drawing-description-for-graph-grid?
			  (line-drawing-description-for-graph-grid? graph-grid)
  (reclaim-graph-tree line-drawing-description-for-graph-grid?)
  (setf (line-drawing-description-for-graph-grid? graph-grid) nil))


(def-slot-value-reclaimer tail-pointer-for-line-drawing-description
			  (tail-pointer-for-line-drawing-description graph-grid)
  (declare (ignore tail-pointer-for-line-drawing-description))
  (setf (tail-pointer-for-line-drawing-description graph-grid) nil))


(def-slot-value-reclaimer tail-pointer-for-line-segments
			  (tail-pointer-for-line-segments graph-grid)
  (declare (ignore tail-pointer-for-line-segments))
  (setf (tail-pointer-for-line-segments graph-grid) nil))



(define-reclaimers-for-managed-number-slots 
  desired-low-value-for-horizontal-axis
  desired-high-value-for-horizontal-axis
  desired-low-value-for-vertical-axis
  desired-high-value-for-vertical-axis
  interval-between-horizontal-grid-lines
  low-value-for-horizontal-grid-lines
  high-value-for-horizontal-grid-lines
  horizontal-grid-line-spacing
  interval-between-vertical-grid-lines
  low-value-for-vertical-grid-lines
  high-value-for-vertical-grid-lines
  vertical-grid-line-spacing
  low-value-for-horizontal-axis
  high-value-for-horizontal-axis
  low-value-for-vertical-axis
  high-value-for-vertical-axis
  horizontal-axis-range
  vertical-axis-range)




(def-class (plot dependent-frame define-predicate)
  (plot-format nil vector-slot system save)
  (display-expression-for-plot nil vector-slot system save)
  (plot-color nil vector-slot system save)  ; and possibly other info
  (data-buffer-for-plot nil vector-slot system)
  (x-data-minimum nil vector-slot system)
  (x-data-maximum nil vector-slot system)
  (most-recent-y-extremum nil vector-slot system)
  (opposite-y-extremum-of-most-recent nil vector-slot system)
  (need-to-scale-y-data? nil vector-slot system))

;; X-data-minimum and x-data-maximum currently contain times.  These are used
;; by refresh-plot-data-buffer.  When x-y plots are introduced, they will
;; contain values other than times (typically floats).


(def-absent-slot-putter plot-pattern (plot old-value)
  (when old-value
    (let ((current-block-of-dependent-frame
	    'dependent-frame-has-no-owner))
      (change-slot-value 
	plot 'plot-color
	(slot-value-list (plot-color plot) old-value)))))


(defun plot-color-given-plot (plot)
  (let ((plot-color-and-info (plot-color plot)))
    (if (consp plot-color-and-info)
	(car plot-color-and-info)
	plot-color-and-info)))

(defun plot-marker-and-or-line-width (plot)
  (let ((plot-color-and-info (plot-color plot)))
    (if (consp plot-color-and-info)
	(second plot-color-and-info))))

(defun plot-marker-or-shading-key-given-plot (plot)
  (let ((plot-marker-and-or-line-width
	  (plot-marker-and-or-line-width plot)))
    (cond
      ((symbolp plot-marker-and-or-line-width)
       plot-marker-and-or-line-width)
      ((consp plot-marker-and-or-line-width)
       (if (eq (car plot-marker-and-or-line-width) 'nupec)
	   plot-marker-and-or-line-width
	   (car plot-marker-and-or-line-width))))))

(defun plot-line-width-given-plot (plot)
  (let ((plot-marker-and-or-line-width
	  (plot-marker-and-or-line-width plot)))
    (cond
      ((numberp plot-marker-and-or-line-width)
       plot-marker-and-or-line-width)
      ((consp plot-marker-and-or-line-width)
       (when (not (eq (car plot-marker-and-or-line-width) 'nupec))
	 (cdr plot-marker-and-or-line-width))))))

(defun plot-marker-given-plot (plot)
  (let ((plot-marker-or-shading-key
	  (plot-marker-or-shading-key-given-plot plot)))
    (when (not (eq plot-marker-or-shading-key 'shading))
      plot-marker-or-shading-key)))

(defun plot-shading-given-plot (plot)
  (let ((plot-marker-or-shading-key
	  (plot-marker-or-shading-key-given-plot plot)))
    (eq plot-marker-or-shading-key 'shading)))

(defun plot-min-and-max-given-plot (plot)
  (let ((plot-color-and-info (plot-color plot)))
    (if (consp plot-color-and-info)
	(third plot-color-and-info))))

(defun plot-min-given-plot-min-and-max (plot-min-and-max)
  (coerce-to-gensym-float (slot-value-number-value (car plot-min-and-max))))

(defun plot-max-given-plot-min-and-max (plot-min-and-max)
  (coerce-to-gensym-float (slot-value-number-value (cdr plot-min-and-max))))



(def-class (graph-axis-label text-box)
  (default-text-box-format-name graph-axis-label-format)
  (label-permanent? nil lookup-slot system)
  (horizontal-or-vertical-axis-label? nil lookup-slot system))

;; All graph-axis-labels are subblocks of the graph-grid.  This simplifies
;; draw and shift methods.  However, it is necessary to distinguish between
;; horizontal and vertical axis labels.  The slot 
;; horizontal-or-vertical-axis-label? is used by the functions
;; put-up-new-labels-for-vertical-graph-axis and
;; put-up-new-labels-for-horizontal-graph-axis for this purpose.
;; These functions also set the slot appropriately.
;; The value can be 'horizontal, 'vertical, or nil.

(def-class-method generate-spot (graph-axis-label mouse-pointer)
  (generate-spot-for-aggregate graph-axis-label mouse-pointer))


;;;; Plot Markers

;;; Plot markers are used to distinguish plots, especially on a monochrome
;;; platform.  They are specified in the graph expression by entering, 
;;; for example "x1 using square plot marker" (see GRAMMAR2).  Typically,
;;; only a small number of plot markers are needed along the length of a
;;; plot to distinguish it;  four should be sufficient for most graphs.
;;; Plot markers are definitely not needed for every single data point.



;; The grammar for plot patterns has been disabled (see GRAMMAR2).  Plot
;; patterns, in contrast to plot markers, are patterns for the plot lines
;; themselves (wide, dashed, etc.).  Plot patterns have been disabled 
;; because plot markers are easier to implement and are actually better.
;; Plot patterns could be reintroduced at some time in the future.
;; Like plot patterns, information about plot markers is stored in the
;; plot-pattern slot of a plot.

;; The various plot markers are currently painted onto the graph ring
;; raster using line drawing primitives (see paint-graph-on-scratchpad-raster).
;; Although this is certainly satisfactory for now, it may be desireable
;; in the future to predefine icons for the markers and use these.
;; Such icons would not be associated with any entities and would be
;; painted onto the graph ring raster by a new primitive
;; paint-icon-onto-current-scratchpad-raster (similar to 
;; paint-solid-rectangle-in-current-scratchpad-raster).  Font rasters could
;; also be utilized if the primitive paint-icon-onto-current-scratchpad-raster
;; existed.  These primitives would also be useful for other things
;; (talk to Mark, Lowell).



;;;; Plot Data Buffers


;;; A plot data ring buffer contains vectors for x and y values in workspace
;;; units.  Plot marker indices are also maintained (the indices point to
;;; plot data ring buffer elements).

(define-ring-buffer plot-data 
  (plot-x-value plot-y-value)
  (new-data-boundary-index 0)
  (old-data-boundary-index nil)
  (x-value-for-last-marker? nil)
  (plot-marker-indices nil :reclaimer reclaim-plot-marker-indices)
  (draw-new-first-data-point? nil))

;; New-data-boundary-index is used to optimize drawing.  It is the
;; responsibility of refresh-plot-data-buffer to update these slots.
;; Draw-only-new-data-for-graph-grid draws only data after
;; new-data-boundary-index.  Old-data-boundary-index is no
;; longer used (see note for refresh-plot-data-buffer).



(defun reclaim-plot-marker-indices (indices)
  (reclaim-graph-list indices))


(defun clear-plot-marker-data (plot-data-ring-buffer)
  (reclaim-plot-marker-indices 
    (plot-marker-indices plot-data-ring-buffer))
  (setf (x-value-for-last-marker? plot-data-ring-buffer) nil
	(plot-marker-indices plot-data-ring-buffer) nil))



(def-slot-value-reclaimer data-buffer-for-plot
			  (data-buffer-for-plot plot)
  plot
  (reclaim-plot-data-ring-buffer data-buffer-for-plot))


(defun data-exists-for-plot-p (plot)
  (let ((data-buffer-for-plot (data-buffer-for-plot plot)))
    (and data-buffer-for-plot
	 (not (ring-buffer-empty? data-buffer-for-plot)))))



;;; Expand-plot-data-ring-buffer is like expand-history-ring-buffer
;;; except that it also updates the old-data-boundary-index and
;;; new-data-boundary-index pointers.  It does nothing if the
;;; plot data buffer size is already at the limit largest-ring-buffer-vector-size.
 
(defun expand-plot-data-ring-buffer
       (data-buffer-for-plot)
  (let ((current-size
	  (ring-buffer-size data-buffer-for-plot)))
    (when (<f current-size largest-ring-buffer-vector-size)
      (let* ((length-up-to-new-data-boundary-index
	       (ring-buffer-length-up-to-index 
		 data-buffer-for-plot 
		 (new-data-boundary-index data-buffer-for-plot)))
	     (old-data-boundary-index
	       (old-data-boundary-index data-buffer-for-plot))
	     (length-up-to-old-data-boundary-index
	       (when old-data-boundary-index
		 (ring-buffer-length-up-to-index 
		   data-buffer-for-plot 
		   old-data-boundary-index))))
	(enlarge-plot-data-ring-buffer
	  data-buffer-for-plot current-size)
	(setf (new-data-boundary-index data-buffer-for-plot)
	      (-f length-up-to-new-data-boundary-index 1))
	(when old-data-boundary-index
	  (setf (old-data-boundary-index data-buffer-for-plot)
		(-f length-up-to-old-data-boundary-index 1)))))))




;;;; Draw Functions

;;; The draw functions for graphs are called via the draw method for graphs or by
;;; update-images-of-only-new-data-for-graph-grid or
;;; update-images-of-graph-grid-and-data.  These two functions are called from
;;; make-or-reformat-graph-grid which is called when updating a graph during its
;;; scheduled update, or in certain cases when the user edits the graph
;;; specifications.  When these two functions are called, the graph grid has
;;; changed in some way and the graph raster must be repainted.  The draw method
;;; for graphs, however, does not typically require the graph to be repainted.
;;; Since the draw method and update-images-of-graph-grid-and-data both call
;;; draw-graph-grid-and-data, the argument repaint-graph-grid-raster?  is needed.
;;; No argument is needed with update-images-of-only-new-data-for-graph-grid which
;;; calls draw-only-new-data-for-graph-grid which always repaints the raster.

;;; In the 2.0 version of graphs, the general approach for drawing has changed.
;;; Instead of calling draw-solid-rectangle to draw data points and grid lines,
;;; descriptions of the points and grid lines are put into the
;;; line-drawing-description-for-graph-grid?  slot of the graph-grid using the
;;; add-graph...  functions.  Then draw-graph-rendering is called to send the line
;;; drawing descriptions to the various windows, both native and ICP, that have
;;; image-planes containing the graph.  The individual description elements for
;;; lines and rectangles do not contain any color information.  Rather, separate
;;; description elements are used to change the "current" color.  This is more
;;; efficient since it reduces what has to be sent over ICP.  This approach works
;;; for both monochrome and polychrome rasters.

;;; Unlike icons, the rasters for graphs are painted to the screen using "copy" or
;;; "or" alu functions, rather than being added to the screen using x-or.  Thus,
;;; color differences are not used for graphs; only color values are needed.

;;; Update-images loops through each image-plane containing a graph and calls the
;;; draw method or specified draw function, wrapped by on-window and
;;; on-image-plane, for each one.  Graph renderings are window specific and are
;;; kept in the graph-renderings slot of a graph grid (see also documentation for
;;; icon renderings in WINDOWS3).  The graph renderings do however share the line
;;; drawing description maintained in the graph grid (see also documentation for
;;; draw-graph-grid-and-data for more details).  Thus, the incremental cost of
;;; drawing one more image is low compared with the cost of drawing the first
;;; image.  Note however that while graph renderings share colors in the line
;;; drawing description, they do not share color values since these are window
;;; specific (each window may have a different color map).
;;; Update-color-values-for-graph updates the colors for each graph rendering.

;;; A typical example of multiple images of a graph is in a Telewindows case where
;;; there is an image on the G2 side and one on the Telewindows side.  The
;;; Telewindows side graph-rendering itself does not have a line drawing
;;; description.  Rather, the line drawing description in the graph-rendering on
;;; the G2 side is used to send ICP messages to paint the raster on the
;;; Telewindows side.  A graph rendering structure (containing a raster) exists on
;;; both sides.  It is actually not needed on the G2 side if the graph is not
;;; shown there.


(defvar minimum-distance-for-data-points)
(defvar graph-background-color-value)
(defvar horizontal-grid-line-width)
(defvar vertical-grid-line-width)
(defvar vertical-grid-line-color?) 
(defvar horizontal-grid-line-color?)
(defvar graph-grid-for-data)
(defvar grid-width)
(defvar grid-height)
(defvar default-graph-line-color-value)



(declare-forward-reference make-or-reformat-graph-grid function)       ; see GRAPHS2
#+development
(declare-forward-reference print-contents-of-plot-data-buffer function); see GRAPHS2

(declare-forward-reference project-chart-call-back function)           ; see CHARTS1

(declare-forward-reference remove-graph-rendering-from-chart function) ; see CHARTS1


; (def-system-variable plot-pattern-may-have-changed? graphs1 nil)

;;; The following three variables are the control variables of a mechanism
;;; to get graphs to be less sensitive about when their draw method might
;;; be called , to forge some sort of detente with the new scheduled draw
;;; paint.  When I am more confident that these fixes are really the
;;; "right thing", they switch joes-graph-hax{-trace}-p will be removed
;;; and a better explanation of what I am doing will be provided.
;;; JED 9/11/94
;;;
;;; My hax sux.  I think I found a better reason for graph drawing
;;; problems and I am giving that a try.  If it QA's at all I will
;;; remove joes-graph-hax-p and friends real soon.
;;; JED 12/5/94

(defvar joes-graph-hax-p nil)
(defvar joes-graph-hax-trace-p nil)
(defvar current-graph-grid-in-minimal-update nil)


(def-class-method draw (graph)
  #+development
  (when joes-graph-hax-trace-p
    (let ((bt (backtrace)))
      (format t "Draw Graph win=~s from ~s~%"
	      current-window
	      bt)))
  (cond
    ((block-is-currently-being-dragged-p graph)
     ;; Note that drawing an opaque block will LOSE if attempted
     ;; when the block is being transferred, since the block
     ;; will not be in the subblock stack (for opaque blocks).
     (draw-block-outline-in-current-image-plane graph 'foreground)) ; was black (MHD 11/11/93)
    (t
     (let ((graph-background-color (car (background-colors graph))))
       (with-background-color-value
	   (map-color-or-metacolor-to-color-value graph-background-color)
	 (paint-background-for-opaque-block graph)
	 (draw-for-table graph))))))



(defun graph-rendering-has-wrong-scale?
    (graph-rendering)
  (not (and (=f current-image-x-scale
		(x-scale-of-graph-rendering graph-rendering))
	    (=f current-image-y-scale
		(y-scale-of-graph-rendering graph-rendering)))))


(defun graph-needs-formatting? 
			(graph graph-grid graph-rendering-has-wrong-scale?)
  (or (null (horizontal-grid-line-spacing graph-grid))
      (null (graph-left-margin-width graph-grid))
      ;; Since axis format data is no longer saved, it must be derived 
      ;; if it doesn't exist. - agh, 12/28/87
      
      graph-rendering-has-wrong-scale?
      
      (and (or (active-p graph) (runs-while-inactive-p graph))
	   (not (display-up-to-date? graph)))
      ;; if active graph that has been hidden is brought up
      ))



;;; Graph renderings are window specific.  Get-graph-rendering-for-current-window
;;; returns the graph rendering for current-window, if any.

(defun get-graph-rendering-for-current-window (graph-grid)
  (loop for graph-rendering in (graph-renderings graph-grid)
	do (when (eq current-window
		     (window-for-graph-rendering graph-rendering))
	     (return graph-rendering))))


(def-class-method draw (graph-grid)
  #+development
  (when joes-graph-hax-trace-p
    (let ((bt (backtrace))
	  (currs
	    (loop for ip in (currently-up-to-date-image-planes graph-grid)
		  collect
		  (gensym-window-for-pane (pane-for-image-plane ip))
		  using gensym-cons)))
      (format t "Draw Graph Grid ~%  currs=~s~%  win=~s ~%  from ~s~%"
	      currs current-window
	      (subseq bt 1 8))
      (reclaim-gensym-list currs)))
  (let ((graph (superblock? graph-grid))
	(current-graph-rendering? 
	  (get-graph-rendering-for-current-window graph-grid))
	graph-rendering-has-wrong-scale?)

    (when (and current-graph-rendering?
	       (setq graph-rendering-has-wrong-scale?
		     (graph-rendering-has-wrong-scale? 
		       current-graph-rendering?)))
      (decache-graph-rendering current-graph-rendering?))

    (cond
      ((printing-p))
      ((graph-needs-formatting? 
	 graph graph-grid graph-rendering-has-wrong-scale?)
       #+development
       (when (and joes-graph-hax-p
		  (eq current-graph-grid-in-minimal-update
		      graph-grid))
	 (cerror "go on - but with grave caution"
		 "reformatting graph in minimal update"))
       (let ((redraw-as-well-as-reformat-p nil))
	 (make-or-reformat-graph-grid 
	   nil graph-grid (graph-format graph) t t))
       (when joes-graph-hax-p
	 (setq current-graph-grid-in-minimal-update nil))
       (make-graph-not-up-to-date graph-grid))
      ((and (eq (graph-description-up-to-date? graph-grid) 'scrolling)
	    (not (memq current-image-plane
		       (currently-up-to-date-image-planes graph-grid))))
       #+development
       (when (and joes-graph-hax-p
		  (eq current-graph-grid-in-minimal-update
		      graph-grid))
	 ;; new tw connections would find themselves here
	 ;; (format t "possible new TW connections~%")
	 ;;(cerror "go on - but with grave caution"
	 ;;	 "updating data buffers in minimal update")
	 )
       (reclaim-graph-list (currently-up-to-date-image-planes graph-grid))
       (setf (currently-up-to-date-image-planes graph-grid) nil)
       (let ((redraw-as-well-as-reformat-p nil))
	 (make-or-reformat-graph-grid 
	   nil graph-grid (graph-format graph) t t))
       (when joes-graph-hax-p
	 (format t "__+__+__+__Clobbering~%")
	 (setq current-graph-grid-in-minimal-update nil))
       (make-graph-not-up-to-date graph-grid)
       (setf (graph-reformatted-since-start? graph) nil)
       ;; Graph-reformatted-since-start? is set to nil to ensure that the
       ;; next time make-or-reformat-graph-grid is called, a scrolling
       ;; reformat won't be attempted.  An alternative to this would be
       ;; to set some flag that would cause 
       ;; make-or-reformat-graph-grid to call update-images before 
       ;; reformatting.
       ))
    (draw-graph-grid-and-data 
      graph-grid
      (if (and (printing-p) (eql printing-pass-number 2))
	  nil
	  (not (memq current-image-plane
		     (currently-up-to-date-image-planes graph-grid)))))
    (when (or (not joes-graph-hax-p)
	      (not (eq current-graph-grid-in-minimal-update
		       graph-grid))
	      (not current-graph-grid-in-minimal-update))
      (add-to-set (currently-up-to-date-image-planes graph-grid)
		  current-image-plane
		  graph))
    ))



;;; `Bogus-preflight-from-printing-to-graphs' implements a hack to supress the
;;; damage done to graph state when new image of a graph is created.  Graphs
;;; have a bogus feature that allows them to reformat when drawing one of their
;;; N images.  The other N images are then out of synch with the internal
;;; formating of the graph.  A request to partially refresh one of them will
;;; expose this by leaving the refreshed area in the new format while the
;;; remainder is shown in the old format.  If you could recursively enter
;;; on-window you could refresh the other N images.  This sad state will persist
;;; until the the graph is updated.

;;; To preempt reformating while drawing, we force an reformat prior to
;;; printing.  This leaves everything in a state sufficent to avoid the reformat
;;; in the midst of printing.

;;; This causes lots of extra drawing, and doesn't fix the analagous bug
;;; with freshly connecting TW's image.  

(declare-forward-reference reformat-graph-based-on-edit-if-necessary function)       ;; see install

(defvar bogus-preflight-from-printing-to-graphs nil)

(defun bogus-preflight-from-printing-to-graphs (workspace)
  (let ((bogus-preflight-from-printing-to-graphs t))
    (loop for subblock being each subblock of workspace
	  when (graph-p subblock)
	    do (reformat-graph-based-on-edit-if-necessary subblock nil))))


	


(defun draw-current-graph-rendering
    (left-edge-in-window top-edge-in-window right-edge-in-window bottom-edge-in-window)
  (record-lru-element-usage current-graph-rendering graph-rendering-lru-queue)
  ;; Doing this here (as opposed to within 
  ;; add-from-graph-rendering-to-current-window) means that it will
  ;; not be done for Telewindows processes, only for the G2 process.
  ;; This is consistent with the fact that no independent decaching
  ;; is done in the Telewindows processes (see documentation for
  ;; delete-graph-rendering-and-reclaim-icp-index).
  (draw-graph-rendering
    left-edge-in-window top-edge-in-window 
    right-edge-in-window bottom-edge-in-window
    (color-values-for-rasters? current-graph-rendering)
    current-graph-rendering))

;; Similar to draw-icon-rendering.




(defun compute-erase-dateline-1 (graph-grid dateline)
  (let ((total-range (horizontal-axis-and-erase-zone-range graph-grid)))
    (mod (+ dateline 
	    (- total-range
	       (extract-number-or-value (horizontal-axis-range graph-grid))))
	 total-range)))

(defun compute-erase-dateline (graph-grid)
  (compute-erase-dateline-1 graph-grid (dateline graph-grid)))



(defun round-for-graphs (x)
  (if (>e (managed-float-value x) 0.0d0)
      (if (<e (-e (managed-float-value x)
		  (ffloore-first (managed-float-value x)))
	      0.5d0)
	  (floore-first (managed-float-value x))
	  (ceilinge-first (managed-float-value x)))
      (if (>e (-e (managed-float-value x)
		  (coerce-fixnum-to-gensym-float
		    (ceilinge-first (managed-float-value x))))
	      -0.5d0)
	  (ceilinge-first (managed-float-value x))
	  (floore-first (managed-float-value x)))))


(defun compute-x-value-on-graph
			(x-value-on-offset-horizontal-axis graph-grid)
  (mutate-managed-float-value
    handy-float-1
    (mine (/e (*e (coerce-fixnum-to-gensym-float 
		    (grid-and-erase-zone-width graph-grid))
		  (coerce-fixnum-to-gensym-float
		    x-value-on-offset-horizontal-axis))
	      (coerce-fixnum-to-gensym-float 
		(horizontal-axis-and-erase-zone-range graph-grid)))
	  (coerce-fixnum-to-gensym-float
	    (+w 1 (grid-and-erase-zone-width graph-grid)))))
  (round-for-graphs handy-float-1))

;; The maxe is necessary for cases where the result of the divide is 
;; so large that rounding it would result in a bignum, rather than a fixnum.
;; See also compute-y-value-on-graph.

                                                                                                                                                              
;;; Draw-graph-grid-and-data is the main draw function for drawing a graph grid
;;; completely.  

;;; As mentioned in the documentation for the draw method for graph, graph
;;; renderings share the line drawing description maintained in the graph grid.
;;; Thus, the line drawing description need be updated only once.  However,
;;; all graph renderings must be repainted when the line drawing description
;;; is updated.  See also documentation for make-graph-not-up-to-date.

;;; The graph-grid slot graph-description-up-to-date?  and the argument
;;; repaint-raster?  are useful for avoiding unnecessary work.  There are three
;;; cases of possible values for these variables.  If
;;; graph-description-up-to-date?  is not t, then repaint-raster?  should be t,
;;; and the line drawing description in the graph rendering will be updated and
;;; the raster refreshed.  If graph-description-up-to-date?  is t and
;;; repaint-raster?  is nil, the line drawing description is cleared resulting in
;;; the raster not being repainted.  Finally, if graph-description-up-to-date?  is
;;; t and repaint-raster?  is t then the line drawing description is not cleared
;;; and the raster will be painted according to the existing description.  If no
;;; description exists, it must be generated.  See also make-graph-not-up-to-date.

;;; Graph-description-up-to-date?  should never be t and repaint-raster?  should
;;; always be t if the contents of the graph grid has actually changed in any way;
;;; if there is new data, or if the format specifications have been edited (see
;;; make-or-reformat-graph-grid, and slot putters).  Thus, the
;;; graph-description-up-to-date?  slot is always set to nil by the functions
;;; update-images-of-graph, update-images-of-only-new-data-for-graph-grid, and
;;; update-images-of-graph-grid-and-data.  The slot is always set to t at the end
;;; of draw-graph-grid-and-data.  Thus, the graph description is updated only
;;; once, even if there are several images of the graph (as when Telewindows is
;;; used).  It is still necessary to repaint all the rasters (recall that
;;; update-images loops through each image plane and calls the draw method,
;;; wrapped by on-window and on-image-plane, for each one).  The slot is always
;;; set to 'scrolling at the end of draw-only-new-data-for-graph-grid.  This way,
;;; the graph description is updated only once for all images when scrolling.  If
;;; draw-graph-grid-and-data is called while scrolling (due to an image plane
;;; being exposed for example) it will know to update fully since the slot is not
;;; t.

;;; If the contents of the graph grid have not changed, it is still necessary to
;;; repaint the raster if a portion of it is exposed that has changed since the
;;; last time it was exposed, or if the scale changes.

;;; If none of these cases hold, then the graph can be drawn without updating
;;; the description or repainting the raster.

;;; The special variable repaint-graph-raster-when-drawing? can be used to control
;;; raster painting when the draw method for the graph is invoked (see above).

;;; For draw-only-new-data-for-graph-grid, the raster is always repainted.  However,
;;; as with draw-graph-grid-and-data, when there are multiple images, the
;;; graph description need be updated only once.  Thus, update-graph-description?
;;; is set to nil at the end of draw-only-new-data-for-graph-grid as well. 


(defun draw-graph-grid-and-data (graph-grid repaint-raster?)
  #+development
  (when joes-graph-hax-trace-p
    (let ((bt (backtrace)))
      (format t "draw graph grid and data win=~s utd=~s from ~s~%"
	      current-window
	      (graph-description-up-to-date? graph-grid)
	      (subseq bt 1 8))))
  (let* ((graph (superblock? graph-grid))
	 (graph-format (graph-format graph))
	 (default-graph-line-color-value
	   (compute-graph-line-color-value graph-grid graph-format))
	 (graph-background-color-value
;	   (let ((graph-background-color?
;		   (or (graph-background-color? graph-format)
;		       (table-background-color? format-of-superblock)
;		       (loop as supertable
;				= (superblock? graph-grid)
;				then (superblock? supertable)
;			     thereis
;			       (table-background-color?
;				 (table-format supertable))
;			     while (and (superblock? supertable)
;					(table-p (superblock? supertable)))))))
;	     (if graph-background-color?
;		 (map-color-or-metacolor-to-color-value graph-background-color?)
;		 current-background-color-value))
	   (map-color-or-metacolor-to-color-value (car (background-colors graph))))
	 (grid-background-color-value
	   (map-color-or-metacolor-to-color-value (cdr (background-colors graph))))
	 (line-to-background-color-difference
	   (color-difference 
	     default-graph-line-color-value graph-background-color-value))
	 (horizontal-grid-line-width
	   (graph-horizontal-grid-line-width graph-format))
	 (vertical-grid-line-width
	   (graph-vertical-grid-line-width graph-format))
	 (left-edge-of-grid
	   (+w (left-edge-of-block graph-grid)
	       (graph-left-margin-width graph-grid)))
	 (top-edge-of-grid
	   (+w (top-edge-of-block graph-grid)
	       (graph-top-margin-width graph-grid)))
	 (right-edge-of-grid
	   (-w (right-edge-of-block graph-grid)
	       (graph-right-margin-width graph-grid)))
	 (bottom-edge-of-grid
	   (-w (bottom-edge-of-block graph-grid)
	       (graph-bottom-margin-width graph-grid))))

    (let* ((graph-grid-for-data graph-grid)
	   (graph-margin-color-value
	     (let ((graph-margin-color? (graph-margin-color? graph-format)))
	       (if graph-margin-color?
		   (map-color-or-metacolor-to-color-value graph-margin-color?)
		   graph-background-color-value)))
	   (horizontal-grid-line-color? 
	     (graph-horizontal-grid-line-color? graph-format))
	   (vertical-grid-line-color? 
	     (graph-vertical-grid-line-color? graph-format))
	   (grid-width 
	     (grid-width-for-graph graph-grid))
	   (grid-height
	     (grid-height-for-graph graph-grid))
	   (current-graph-rendering nil)
	   (graph-rendering-is-new? nil)
;	      (plot-pattern-may-have-changed? t)
	   (update-graph-description?
	     (and (not (graph-description-up-to-date? graph-grid))
		  )))

      (when joes-graph-hax-trace-p
	(format t "grid and data ugd?=~s cggimu=~s~%"
		update-graph-description?
		current-graph-grid-in-minimal-update))
		  
      graph-margin-color-value
      
      (multiple-value-setq
	(current-graph-rendering graph-rendering-is-new?)
	(get-or-make-graph-rendering graph-grid))
      (if graph-rendering-is-new?
	  (setq repaint-raster? t
		update-graph-description? t))

      (when repaint-raster?
	(update-color-values-for-graph 
	  graph-grid graph current-graph-rendering grid-background-color-value))
      
      (when (and update-graph-description?
		 (if joes-graph-hax-p
		     (not (eq current-graph-grid-in-minimal-update
			      graph-grid))
		     t))
	#+development
	(when joes-graph-hax-trace-p
	  (format t "UPdating graph in grid rend-new=~s cggimu=~s~%"
		  graph-rendering-is-new?
		  current-graph-grid-in-minimal-update))

	(reclaim-graph-tree 
	  (line-drawing-description-for-graph-grid? graph-grid))
	(setf (line-drawing-description-for-graph-grid? graph-grid)
	      (graph-list (graph-list 'graph))
	      (tail-pointer-for-line-drawing-description graph-grid)
	      (line-drawing-description-for-graph-grid? graph-grid)
	      (tail-pointer-for-line-segments graph-grid) nil)
	(setf (dateline graph-grid) 0
	      (old-dateline graph-grid) 0
	      (old-dateline-in-workspace-units graph-grid) 0)
	(with-temporary-gensym-float-creation draw-graph-grid-and-data
	  (add-graph-new-dateline
	    0
	    (compute-x-value-on-graph
	      (compute-erase-dateline graph-grid) graph-grid)))
	(add-graph-clear)
	(if (show-grid-lines? graph)
	    (draw-graph-grid graph-grid graph)
	    (let ((extra-grid-lines? (extra-grid-lines? graph)))
	      (when extra-grid-lines?
		(draw-extra-grid-lines 
		  graph-grid extra-grid-lines?
		  0 (grid-and-erase-zone-width graph-grid)))))
	(draw-data-for-graph-grid graph-grid graph-format))
      (let ((grid-border-width (grid-border-width current-graph-rendering))
	    (left-edge-of-grid-in-window (x-in-window left-edge-of-grid))
	    (top-edge-of-grid-in-window (y-in-window top-edge-of-grid))
	    (right-edge-of-grid-in-window (x-in-window right-edge-of-grid))
	    (bottom-edge-of-grid-in-window (y-in-window bottom-edge-of-grid)))
	(draw-rectangle-outline-in-window
	  left-edge-of-grid-in-window top-edge-of-grid-in-window
	  right-edge-of-grid-in-window bottom-edge-of-grid-in-window
	  line-to-background-color-difference
	  grid-border-width grid-border-width) ; why were these never scaled?! (MHD 11/11/93)
	(clear-data-clipping-rectangles)
	(cond
	  ((and repaint-raster?
		(if joes-graph-hax-p
		    (not (eq current-graph-grid-in-minimal-update
			     graph-grid))
		    t))
	   (update-graph-rendering))
	  (repaint-raster?
	   (update-colors-of-current-graph-rendering)
	   #+development
	   (when joes-graph-hax-trace-p
	     (format t "Averted Disaster!!!!!!!!!!!!!!!~%"))))

	(draw-current-graph-rendering
	  (+r left-edge-of-grid-in-window grid-border-width)
	  (+r top-edge-of-grid-in-window grid-border-width)
	  (-r right-edge-of-grid-in-window grid-border-width)
	  (-r bottom-edge-of-grid-in-window grid-border-width)))
      (unless (and joes-graph-hax-p
		   (eq current-graph-grid-in-minimal-update
		       graph-grid))
	(setf (graph-description-up-to-date? graph-grid) t))
      )

    (loop for subblock being each subblock of graph-grid
	  do
      (draw-graph-axis-label graph-grid subblock))))
    ;; (draw-subblocks graph-grid)))			    ; Hmm.

;; If update-graph-description? is t, draw-data-for-graph-grid will update
;; the graph description according to the contents of the plot data buffer.
;; It is therefore necessary that the plot data buffer be correct (that
;; make-or-reformat-graph-grid have been called with the enforce-reformatting?
;; and refresh-plot-data-buffers? args t).

;; The test for update-graph-description?  could possibly be moved to avoid
;; binding some of the special variables when not updating!

;; Description is considered empty if
;; line-drawing-description-for-graph-grid?  slot is '(graph).




(defun draw-graph-grid-current-time-display (graph-grid)
  (let ((time-display-text-box?
	  (horizontal-axis-high-value-label graph-grid)))
    (when time-display-text-box?
      (draw-graph-axis-label graph-grid time-display-text-box?))))

(defun draw-graph-axis-label (graph-grid axis-label-text-box)
  #+development
  (unless (frame-of-class-p axis-label-text-box 'graph-axis-label)
    (error "Need to rethink what can be a subblock of a graph-grid"))
  (let* ((text
	   (cdr (box-translation-and-text axis-label-text-box)))
	 (current-text-box-format
	   (text-box-format axis-label-text-box))
	 (current-text-cell-plist
	   (text-cell-plist-for-text-box axis-label-text-box))
	 (graph (superblock? graph-grid))
	 (background-color-value
	   (map-color-or-metacolor-to-color-value (car (background-colors graph)))))
    (with-background-color-value background-color-value
      (paint-background-for-opaque-block axis-label-text-box)
      (new-draw-text
	text
	(x-in-window (left-edge-of-block axis-label-text-box))
	(y-in-window (top-edge-of-block axis-label-text-box))
	(x-in-window (right-edge-of-block axis-label-text-box))
	(y-in-window (bottom-edge-of-block axis-label-text-box))))))

(defun compute-graph-line-color-value (graph-grid graph-format)
  (let ((graph-line-color?
	  (or (graph-line-color? graph-format)
	      (table-line-color? (table-format (superblock? graph-grid)))
	      (loop as supertable
		       = (superblock?  graph-grid)
		       then (superblock? supertable)
		    thereis
		      (table-line-color? 
			(table-format supertable))
		    while (and (superblock? supertable)
			       (table-p 
				 (superblock? supertable)))))))
    (if graph-line-color?
	(map-color-or-metacolor-to-color-value graph-line-color?)
	current-foreground-color-value)))


;;; Get-or-make-graph-rendering makes a new graph rendering if none exists or if
;;; the existing one does not have the right scale.  When changing the scale of
;;; a workspace containing a graph, the draw method for graphs is called which
;;; in turn calls draw-graph-grid-and-data.  This must be able to handle the
;;; scale change.  It is safe to assume, however, that when
;;; draw-only-new-data-for-graph-grid is called, the scale hasn't changed.
;;; Thus, get-or-make-graph-rendering is called from draw-graph-grid-and-data
;;; but not from draw-only-new-data-for-graph-grid.  A change in graph size is
;;; handled in make-or-reformat-new-graph-grid which simply clears the
;;; graph-rendering slot and then calls draw-graph-grid-and-data which in turn
;;; calls get-or-make-graph-rendering.

;;; Get-or-make-graph-rendering is similar in purpose to
;;; get-or-make-icon-rendering.  There is no caching of renderings for graphs,
;;; however.

(defun get-or-make-graph-rendering (graph-grid)
  (let ((current-graph-rendering? 
	  (get-graph-rendering-for-current-window graph-grid)))
    (cond
      ((or (null current-graph-rendering?)
	   (graph-rendering-has-wrong-scale? current-graph-rendering?))
       (when current-graph-rendering?
	 ;; Reclaim old graph rendering
	 (decache-graph-rendering current-graph-rendering?))
       (let ((new-graph-rendering 
	       (make-new-graph-rendering 
		 graph-grid
		 current-image-x-scale current-image-y-scale)))
	 (add-to-set (graph-renderings graph-grid) new-graph-rendering)
	 (values new-graph-rendering t)))
      (t
       (values current-graph-rendering? nil)))))




;;; Choose-format-for-graph-rendering encodes the decision for choosing
;;; the format, either POLYCHROME-RASTER, MONOCHROME-RASTER-LIST, or
;;; MONOCHROME-RASTER.  It reasons as follows:
;;;
;;;   If printing, use POLYCHROME-RASTER; 
;;;     otherwise if the Telewindows protocol version in use supports it,
;;;        use MONOCHROME-RASTER-LIST;
;;;     otherwise, use monochrome-raster
;;;
;;; Note that monochrome-raster will not be used unless talking to OLD
;;; (i.e. pre-4.0) Telewindows.
;;; 
;;; This is used for graph rendering used in either charts or graphs.
;;;
;;; This is to be called in an on-window context.

(defun choose-format-for-graph-rendering (number-of-colors)
  (declare (ignore number-of-colors))
  (if (polychrome-rasters-for-graphs-p current-window) ; Note A
      'polychrome-raster
      (if (current-window-supports-this-icp-window-protocol-p
	    icp-window-protocol-supports-monochrome-raster-lists)
	  'monochrome-raster-list
	  'monochrome-raster)))

;; New -- common code abstracted from uses CHARTS1 and GRAPHS1. (MHD 6/9/93)

;; Note -- things are a little different in the case of charts: tests
;; for printing-p[-macro] used just trail along with the test format
;; = polychrome-raster.  Now, instead, polychrome-raster just _is_ the
;; format when printing.  That's simpler I think.
;;
;; Note that printing doesn't currently handle the new ICP protocol for
;; monochrome raster lists, but it says it does.  Since polychrome
;; rasters are used instead of monochrome raster lists now, this is OK
;; for now.  Basically, printing is missing the
;; update-ring-raster-for-graph-given-color-values-2 ICP message.
;;
;; One other change: this no longer uses the global variable defined in
;; WINDOWS3: use-polychrome-rasters-for-graphs?.  That's obsolete.
;; If/when other customers besides printing come along, other tests
;; will be added, but the variable facility was incomplete anyway,
;; as no one responsibly bound it, e.g., based on the capability of
;; the Telewindows clint to handle it, or based on whether it's
;; the most efficient representation given the number of colors and
;; the type of device, etc.
;;
;; (MHD 6/9/93)


;; Note A: Make the polychrome raster only for printing-windows.  We may
;; sometimes call this function in the dynamic extent of printing, but not for
;; a printing window.  For example, when printing posts a message and forces
;; all of the drawing queues.  The right thing to do here is to check for a
;; printing-window (printing-window-p), and not for the printing dynamic extent
;; (printing-p).  Fixes HQ-76261 "Crash when printing once".  -fmw, 1/17/95

;; Addendum: Printing to a bitmap does *not* support polychrome rasters.
;; -fmw, 5/12/04


;;; Make-new-graph-rendering ...

(defun make-new-graph-rendering (graph-grid x-scale y-scale)
  (let* ((total-width (grid-and-erase-zone-width graph-grid))
	 (width-of-graph-rendering-structure
	   (delta-x-in-window total-width x-scale))
	 (height-of-graph-rendering-structure
	   (delta-y-in-window grid-height y-scale))
	 (size
	   (compute-size-of-graph-rendering-1
	     width-of-graph-rendering-structure
	     height-of-graph-rendering-structure))
	 (number-of-colors
	   ;; This unfortunately is coded in parallel with the
	   ;; function update-color-values-for-graph.  It may not
	   ;; be perfect; if so, the worst that happens currently
	   ;; is that a monochrome-raster-list format would
	   ;; be used as the format of graph rendering.  Ultimately,
	   ;; parallel code should be abstracted/merged.
	   ;; (MHD 2/16/93)
	   (loop with plot-color-specs-so-far = nil
		 with grid-background-color
		   = (cdr (background-colors
			    (superblock? graph-grid)))	; graph
		 for plot in (list-of-plots graph-grid)
		 as plot-color? = (plot-color-given-plot plot)
		 when (or (null plot-color-specs-so-far)
			  (and (not (eq plot-color? grid-background-color))
			       (not (memberp plot-color? plot-color-specs-so-far))))
		   do (setq plot-color-specs-so-far
			    (gensym-cons plot-color? plot-color-specs-so-far))
		   and count t into number-of-foreground-colors-so-far
		 finally
		   (reclaim-gensym-list plot-color-specs-so-far)
		   (return (+f number-of-foreground-colors-so-far
			       1)))))		; 1 for background color

    (increase-allocation-limit-for-graphs-if-necessary
      graph-grid x-scale y-scale size)
    ;; This is a feedforward mechanism used to eliminate unnecessary
    ;; graph decaching.  It is used because graph decaching can be so
    ;; costly, it should be avoided, even if it would only happen a few
    ;; times at start before the decaching feedback mechanism allocates
    ;; enough memory.  This sort of capability should be added to
    ;; the general decacheable structure mechanism in the form of
    ;; an additional arg "function-to-call-before-decaching"!

    (let ((graph-rendering
	    (make-decacheable-graph-rendering
	      nil
	      (choose-format-for-graph-rendering number-of-colors)
	      x-scale y-scale
	      horizontal-grid-line-width
	      total-width grid-height
	      width-of-graph-rendering-structure
	      height-of-graph-rendering-structure
	      graph-grid 
	      current-window
	      (get-reference-to-item-if-item graph-grid)
	      size)))
      (if (eq (format-of-graph-rendering-structure graph-rendering)
	      'monochrome-raster-list)
	  (update-color-values-for-graph	; sets up the color-values-for-rasters?
	    graph-grid (superblock? graph-grid)	;   slot in the structure  (MHD 2/4/93)
	    graph-rendering 
	    (map-color-or-metacolor-to-color-value
	      (cdr (background-colors (superblock? graph-grid))))))
      graph-rendering)))

;; Note that for graphs, 1 is not added to the height and width of the
;; rendering structure as it is for icons.



(defun increase-allocation-limit-for-graphs-if-necessary 
       (graph-grid x-scale y-scale size)
  (let ((limit-info?
	  (get-memory-limit-info-given-size 
	    graph-rendering-memory-limit-info size))
	(required-size?					    ; Could be NIL.
	  (compute-size-for-graphs-of-size-upon-workspace
	    graph-grid x-scale y-scale size)))
    (when limit-info?
      (setf (allocation-limit limit-info?)
	    (maxf (allocation-limit limit-info?)
		  (or required-size? 0))))))

(defun compute-size-for-graphs-of-size-upon-workspace 
       (graph-grid x-scale y-scale size)
  (let* ((graph (superblock? graph-grid))
	 (workspace?
	   (when graph				; this check shouldn't be needed
	     (superblock? graph))))
    (when workspace?
      (loop with total-size = 0
	    with size-1
	    for subblock being each subblock of workspace? 
	    as graph-grid-1 = (get-graph-grid-given-graph graph)
	    do
	(when (frame-of-class-p subblock 'graph)
	  (setq size-1 (compute-size-of-graph-rendering-1
			 (delta-x-in-window
			   (grid-and-erase-zone-width graph-grid-1) x-scale)
			 (delta-y-in-window
			   (grid-height-for-graph graph-grid) y-scale)))
	  (when (=f size-1 size)
	    (setq total-size
		  (+f total-size size-1))))
	    finally
	      (return total-size)))))





;;; Update-colors-for-graph loops through all the plots collecting all the
;;; colors used for the graph.  It then causes the raster(s) for the graph
;;; to be updated so that these colors can be drawn.  Update-colors-for-graph
;;; is called by draw-graph-grid-and-data which is called from 
;;; make-or-reformat-graph-grid when doing a full reformat.  Thus, editing
;;; the expressions-to-display slot of the graph (to change a plot color for
;;; example) causes update-colors-for-graph to be called.


(defun color-value-given-color-or-default (color?)
  (map-color-or-metacolor-to-color-value (or color? current-default-line-color)))


(defun update-color-values-for-graph 
       (graph-grid graph graph-rendering grid-background-color-value)
  (when (not (graph-rendering-uses-polychrome-rasters? graph-rendering))
    (reclaim-graph-list (color-values-for-rasters? graph-rendering))
    (setf (color-values-for-rasters? graph-rendering) nil)
    (loop for plot in (list-of-plots graph-grid)
	  as plot-color? = (plot-color-given-plot plot)
	  do (add-to-set (color-values-for-rasters? graph-rendering)
			 (if plot-color?
			     (map-color-or-metacolor-to-color-value plot-color?)
			     default-graph-line-color-value)
			 graph))
    (add-to-set (color-values-for-rasters? graph-rendering)
		(color-value-given-color-or-default horizontal-grid-line-color?)
		graph)
    (add-to-set (color-values-for-rasters? graph-rendering)
		(color-value-given-color-or-default vertical-grid-line-color?)
		graph)
    (let ((extra-grid-lines? (extra-grid-lines? graph)))
      (if (and (consp extra-grid-lines?)
	       (not (managed-float-p extra-grid-lines?))
	       (eq (car extra-grid-lines?) '\,))
	  (loop for grid-line-spec in (cdr extra-grid-lines?)
		do (add-to-set (color-values-for-rasters? graph-rendering)
			       (color-value-given-color-or-default 
				 (if (and (consp grid-line-spec)
					  (not (managed-float-p grid-line-spec)))
				     (cdr grid-line-spec)
				     horizontal-grid-line-color?))
			       graph))
	  (add-to-set (color-values-for-rasters? graph-rendering)
		      (color-value-given-color-or-default
			(if (and (consp extra-grid-lines?)
				 (not (managed-float-p extra-grid-lines?)))
			    (cdr extra-grid-lines?)
			    horizontal-grid-line-color?))
		      graph))))
  (setf (grid-background-color-value graph-rendering)
	grid-background-color-value))

;; For polychrome rasters the color-values-for-rasters? slot will always
;; be nil.

;; Note that map-color-or-metacolor-to-color-value will return 0 or 1
;; for the color value if there is no color map.  Thus, on monochrome
;; displays, only one color value will be used and only one raster plane
;; will be allocated.




(defun compute-y-value-on-graph
			(y-value-on-vertical-axis
			 vertical-axis-range low-value-for-vertical-axis)
  (-w grid-height
      (round (mine
	       (/e (*e (coerce-to-gensym-float grid-height)
		       (coerce-to-gensym-float (- y-value-on-vertical-axis
						  low-value-for-vertical-axis)))
		   (coerce-to-gensym-float vertical-axis-range))
	       (coerce-to-gensym-float (+w grid-height 1))))))

(defun compute-y-value-on-graph-new
			(y-value-on-vertical-axis)
  (mutate-managed-float-value
    handy-float-1
    ;; max(0,min(grid-height + 1, (grid-height * (y - low))/range))
    (maxe
      (mine
	(/e (*e (coerce-fixnum-to-gensym-float grid-height)
		(-e (managed-float-value y-value-on-vertical-axis)
		    (managed-float-value low-value-for-vertical-axis)))
	    (managed-float-value vertical-axis-range))
	(coerce-fixnum-to-gensym-float (+w grid-height 1)))
      0.0d0))
  (-w grid-height (round-for-graphs handy-float-1)))

;; The mine is necessary for cases where the result of the divide is 
;; so large that rounding it would result in a bignum, rather than a fixnum.
;; See also compute-x-value-on-graph.


(defun compute-y-value-on-graph-new-with-less-truncation
			(y-value-on-vertical-axis)
  ;; max(-limit,min(limit, (grid-height * (y - low))/range))
  ;; where limit is 20*(grid-height+1)
  (let ((limit 1000000))
    (mutate-managed-float-value
      handy-float-1
      (/e (*e (coerce-fixnum-to-gensym-float grid-height)
	      (-e (managed-float-value y-value-on-vertical-axis)
		  (managed-float-value low-value-for-vertical-axis)))
	  (managed-float-value vertical-axis-range)))
    ;; Clip inside some large values so the round will not
    ;; create a fixnum.
    (cond
      ((<e (coerce-fixnum-to-gensym-float limit)
	   (managed-float-value handy-float-1))
       (mutate-managed-float-value
	 handy-float-1
	 (coerce-fixnum-to-gensym-float limit)))
      ((>e (coerce-fixnum-to-gensym-float (-w limit)) 
	   (managed-float-value handy-float-1))
       (mutate-managed-float-value
	 handy-float-1
	 (coerce-fixnum-to-gensym-float (-w limit)))))
    (-w grid-height (round-for-graphs handy-float-1))))



(defun adjust-x-value-according-to-dateline
    (value-on-horizontal-axis dateline graph-grid
			      low-value-for-horizontal-axis-arg)
  (mod (+f (-f value-on-horizontal-axis low-value-for-horizontal-axis-arg)
	   dateline)
       (horizontal-axis-and-erase-zone-range graph-grid)))



(defmacro compute-y-value-scaled-to-vertical-axis
	   (y-value location-to-mutate)
  `(mutate-managed-float-value
     ,location-to-mutate
     (+e (managed-float-value low-value-for-vertical-axis)
	 (*e (managed-float-value vertical-axis-range)
	     (/e (-e (managed-float-value ,y-value) 
		     (managed-float-value plot-min?))
		 (-e (managed-float-value plot-max?)
		     (managed-float-value plot-min?)))))))



(defun adjust-and-compute-x-value-on-graph 
    (value-on-horizontal-axis dateline graph-grid
			      low-value-for-horizontal-axis-arg)
  (compute-x-value-on-graph
    (adjust-x-value-according-to-dateline
      value-on-horizontal-axis dateline graph-grid
      low-value-for-horizontal-axis-arg)
    graph-grid))



(defun draw-graph-grid (graph-grid graph)
  (when (not (scale-too-small-for-details-p	; finer test for grid lines!
	       current-image-x-scale current-image-y-scale))
    (draw-horizontal-grid-lines graph-grid graph nil nil)
    (draw-vertical-grid-lines graph-grid)))

;; Note that drawing grid lines is simpler in the 1.2 approach.  Since they are 
;; painted onto a raster, there is no need to worry about x-oring and no need
;; to nest the loop for drawing vertical grid lines inside the one for drawing
;; horizontal grid lines.

;; Get rid of horizontal and vertical grid line position slots in graph-grid.
;; They are obsolete!


(defun draw-horizontal-grid-lines 
       (graph-grid graph clipped-left-edge? clipped-right-edge?)
  (with-temporary-gensym-float-creation draw-horizontal-grid-lines
    (add-graph-color-to-use horizontal-grid-line-color?)
    (let ((left-edge (or clipped-left-edge? 0))
	  (right-edge (or clipped-right-edge? 
			  (grid-and-erase-zone-width graph-grid)))
	  (extra-grid-lines? (extra-grid-lines? graph)))
      (loop with horizontal-grid-line-spacing
	      = (extract-number-or-value
		  (horizontal-grid-line-spacing graph-grid))
	    as top-edge-of-horizontal-grid-line-float
	       first (extract-number-or-value
		       (spacing-between-top-edge-and-grid-line graph-grid))
	       then (+ top-edge-of-horizontal-grid-line-float
		       horizontal-grid-line-spacing)
	    ;; have to use generic +
	    as top-edge-of-horizontal-grid-line-in-workspace
	       = (round top-edge-of-horizontal-grid-line-float)
	    as bottom-edge-of-horizontal-grid-line-in-workspace
	       = (+w top-edge-of-horizontal-grid-line-in-workspace
		     horizontal-grid-line-width)
	    as number-of-horizontal-grid-lines-drawn 
	       = 1 then (+f number-of-horizontal-grid-lines-drawn 1)
	    do
	(when (<=w bottom-edge-of-horizontal-grid-line-in-workspace
		   grid-height)
	  (add-graph-rectangle
	    left-edge
	    top-edge-of-horizontal-grid-line-in-workspace
	    right-edge
	    bottom-edge-of-horizontal-grid-line-in-workspace))
	    until (>=f number-of-horizontal-grid-lines-drawn
		       (-f (number-of-horizontal-grid-lines graph-grid) 2)))
      (when extra-grid-lines?
	(draw-extra-grid-lines graph-grid extra-grid-lines? left-edge right-edge)))))



(defun draw-extra-grid-lines (graph-grid extra-grid-lines? left-edge right-edge)
  (with-temporary-gensym-float-creation draw-extra-grid-lines
    (let ((vertical-axis-range
	    (extract-number-or-value (vertical-axis-range graph-grid)))
	  (low-value-for-vertical-axis
	    (extract-number-or-value
	      (low-value-for-vertical-axis graph-grid))))
      (if (and (and (consp extra-grid-lines?)
		    (not (managed-float-p extra-grid-lines?)))
	       (eq (car extra-grid-lines?) '\,))
	  (loop for grid-line-spec in (cdr extra-grid-lines?)
		do (draw-extra-horizontal-grid-line
		     grid-line-spec vertical-axis-range 
		     low-value-for-vertical-axis left-edge right-edge))
	  (draw-extra-horizontal-grid-line
	    extra-grid-lines? vertical-axis-range 
	    low-value-for-vertical-axis left-edge right-edge)))))

(defun draw-extra-horizontal-grid-line 
       (grid-line-spec 
	vertical-axis-range low-value-for-vertical-axis left-edge right-edge)
  (let (y-on-vertical-axis
	(color horizontal-grid-line-color?)
	top-edge-of-horizontal-grid-line-in-workspace
	bottom-edge-of-horizontal-grid-line-in-workspace)
    (if (and (consp grid-line-spec)
	     (not (managed-float-p grid-line-spec)))
	(setq y-on-vertical-axis (slot-value-number-value (car grid-line-spec))
	      color (cdr grid-line-spec))
	(setq y-on-vertical-axis (slot-value-number-value grid-line-spec)))
    (add-graph-color-to-use color)
    (setq top-edge-of-horizontal-grid-line-in-workspace
	  (compute-y-value-on-graph 
	    y-on-vertical-axis vertical-axis-range low-value-for-vertical-axis)
	  bottom-edge-of-horizontal-grid-line-in-workspace
	  (+w top-edge-of-horizontal-grid-line-in-workspace
	      horizontal-grid-line-width))
    (when (and (>=w top-edge-of-horizontal-grid-line-in-workspace 0)
	       (<=w bottom-edge-of-horizontal-grid-line-in-workspace
		    grid-height))
      (add-graph-rectangle
	left-edge
	top-edge-of-horizontal-grid-line-in-workspace
	right-edge
	bottom-edge-of-horizontal-grid-line-in-workspace))))



(defun draw-vertical-grid-lines (graph-grid)
  (with-temporary-gensym-float-creation draw-vertical-grid-lines
    (add-graph-color-to-use vertical-grid-line-color?)
    (loop	with vertical-grid-line-spacing
		  = (extract-number-or-value
		      (vertical-grid-line-spacing graph-grid))
		as right-edge-of-vertical-grid-line-float
		   first (- (grid-and-erase-zone-width graph-grid)
			    (extract-number-or-value
			      (spacing-between-right-edge-and-grid-line graph-grid)))
		   then (- right-edge-of-vertical-grid-line-float
			   vertical-grid-line-spacing)
		;; have to use generic -
		as right-edge-of-vertical-grid-line-in-workspace
		   = (round right-edge-of-vertical-grid-line-float)
		as left-edge-of-vertical-grid-line-in-workspace
		   = (-w right-edge-of-vertical-grid-line-in-workspace
			 vertical-grid-line-width)
		as number-of-vertical-grid-lines-drawn 
		   = 1 then (+f number-of-vertical-grid-lines-drawn 1)
		do 
      (when (>=w left-edge-of-vertical-grid-line-in-workspace
		 (compute-x-value-on-graph
		   (compute-erase-dateline graph-grid) graph-grid))
	;; Need to check to make sure grid line isn't to left of
	;; erase dateline.  If it were, 
	;; the grid line would not be erased when the graph
	;; scrolls causing an extra one to appear.
	(add-graph-rectangle
	  left-edge-of-vertical-grid-line-in-workspace
	  0
	  right-edge-of-vertical-grid-line-in-workspace
	  grid-height))
		until (>=f number-of-vertical-grid-lines-drawn
			   (-f (number-of-vertical-grid-lines graph-grid) 2)))))

(defun draw-new-scrolled-vertical-grid-lines (graph-grid)
  (with-temporary-gensym-float-creation draw-new-scrolled-vertical-grid-lines
    (add-graph-color-to-use vertical-grid-line-color?)
    (loop for vertical-grid-line-position
	      in (new-scrolled-vertical-grid-line-positions graph-grid)
	  as left-edge-of-vertical-grid-line-in-workspace
	     = (compute-x-value-on-graph
		 vertical-grid-line-position graph-grid)
	  do
      (add-graph-rectangle
	left-edge-of-vertical-grid-line-in-workspace
	0
	(+w left-edge-of-vertical-grid-line-in-workspace
	    vertical-grid-line-width)
	grid-height))))

;; Using generic arithmetic operators for computing 
;; top-edge-of-next-horizontal-grid-line-float and
;; left-edge-of-next-vertical-grid-line-float since the computation involves 
;; fixnums and floats.  In any case, these arithmetic operations are at a high
;; level in the graph draw and improving them will not have a significant
;; effect on speed.


;; The data draw functions are simplified in 2.0 since erase does nothing except
;; clear the graphic element from graphic element memory.  Also, draw-data-point
;; is greatly simplified since there is no xor problem.




(defun draw-data-for-graph-grid (graph-grid graph-format)
  (if (and (not (scale-too-small-for-details-p
		  current-image-x-scale current-image-y-scale))
	   (not (block-is-currently-being-dragged-p (superblock? graph-grid))))

      ;; Draw data; no optimization is done here.
      ;; All data is drawn.
      ;; The function draw-only-new-data-for-graph-grid draws in a more
      ;; optimal way and is used if the grid format doesn't change.
      
      (loop with data-point-size = (data-point-size graph-format)
	    with minimum-distance-for-data-points
	      = (minimum-distance-for-data-points graph-format)
	    for plot in (list-of-plots graph-grid)
	    as plot-number = 1 then (+f plot-number 1)
	    as data-buffer-for-plot
	       = (data-buffer-for-plot plot)
	    
	    if (and data-buffer-for-plot
		    (not (ring-buffer-empty?
			   data-buffer-for-plot)))
	      do

;		(if (not (use-one-set-of-axes? graph-format))
;		    ;; Not yet implemented.
;		    )
		
		(draw-data-for-plot
		  data-buffer-for-plot
		  (oldest-active-element-index
		    data-buffer-for-plot)
		  (newest-active-element-index
		    data-buffer-for-plot)
		  data-point-size
		  (plot-color-given-plot plot)
		  (plot-marker-given-plot plot)
		  (plot-shading-given-plot plot)
		  (plot-line-width-given-plot plot)))))






;;; Draw-only-new-data-for-graph-grid, unlike draw-data-for-graph-grid, draws
;;; only new data.  If erasing, it draws (erases) only old data.
;;; Thus, if the graph-grid is not being reformatted, the more efficient
;;; draw-only-new-data-for-graph-grid can be used.

(def-system-variable minimum-x-value-for-new-data GRAPHS1 nil)
(def-system-variable minimum-y-value-for-new-data GRAPHS1 nil)
(def-system-variable maximum-x-value-for-new-data GRAPHS1 nil)
(def-system-variable maximum-y-value-for-new-data GRAPHS1 nil)
(def-system-variable new-dateline? GRAPHS1 nil)

(defun store-new-data-extrema (x y)
  (setq minimum-x-value-for-new-data x)
  (setq minimum-y-value-for-new-data y)
  (setq maximum-x-value-for-new-data x)
  (setq maximum-y-value-for-new-data y))

(defun extend-minimum-x-value-if-necessary (x)
  (setq minimum-x-value-for-new-data
	(minw minimum-x-value-for-new-data x)))

(defun extend-minimum-y-value-if-necessary (y)
  (setq minimum-y-value-for-new-data
	(minw minimum-y-value-for-new-data y)))

(defun extend-maximum-x-value-if-necessary (x)
  (setq maximum-x-value-for-new-data
	(maxw maximum-x-value-for-new-data x)))

(defun extend-maximum-y-value-if-necessary (y)
  (setq maximum-y-value-for-new-data
	(maxw maximum-y-value-for-new-data y)))

(defun extend-extrema-if-necessary (x y)
  (extend-minimum-x-value-if-necessary x)
  (extend-minimum-y-value-if-necessary y)
  (extend-maximum-x-value-if-necessary x)
  (extend-maximum-y-value-if-necessary y))




(defun get-erase-dateline-on-graph (graph-grid)
  (with-temporary-gensym-float-creation get-erase-dateline-on-graph
    (compute-x-value-on-graph
      (compute-erase-dateline graph-grid)
      graph-grid)))

(defvar current-minimal-grid-draw-has-seen-one-image-plane-p nil)

(defun draw-only-new-data-for-graph-grid (graph-grid)
  (unless current-minimal-grid-draw-has-seen-one-image-plane-p
    ; (make-graph-not-up-to-date graph-grid)
    (setf (graph-description-up-to-date? graph-grid) nil)
    (setq current-minimal-grid-draw-has-seen-one-image-plane-p t))
  #+development
  (when joes-graph-hax-trace-p
    (let ((bt (backtrace)))
      (format t "Draw New Data win=~s from ~s~%"
	      current-window
	      (subseq bt 1 8))))
  (let ((current-graph-rendering
	  (get-graph-rendering-for-current-window graph-grid))
	(graph (superblock? graph-grid)))
    (cond 
      (current-graph-rendering
       (let* ((graph-grid-for-data graph-grid)
	      (graph-format (graph-format graph))
	      (default-graph-line-color-value
		(compute-graph-line-color-value graph-grid graph-format))
	      (left-edge-of-grid
		(+f (left-edge-of-block graph-grid)
		    (graph-left-margin-width graph-grid)))
	      (right-edge-of-grid
		(-f (right-edge-of-block graph-grid)
		    (graph-right-margin-width graph-grid)))
	      (bottom-edge-of-grid
		(-f (bottom-edge-of-block graph-grid)
		    (graph-bottom-margin-width graph-grid)))
	      (top-edge-of-grid
		(+f (top-edge-of-block graph-grid)
		    (graph-top-margin-width graph-grid)))
	      (horizontal-grid-line-width
		(graph-horizontal-grid-line-width graph-format))
	      (vertical-grid-line-width
		(graph-horizontal-grid-line-width graph-format))
	      (horizontal-grid-line-color? 
		(graph-horizontal-grid-line-color? graph-format))
	      (vertical-grid-line-color? 
		(graph-vertical-grid-line-color? graph-format))
	      (minimum-x-value-for-new-data nil)
	      (minimum-y-value-for-new-data nil)
	      (maximum-x-value-for-new-data nil)
	      (maximum-y-value-for-new-data nil)
	      (new-dateline? nil)
	      (data-point-size (data-point-size graph-format))
	      (minimum-distance-for-data-points
		(minimum-distance-for-data-points graph-format))
;	 (horizontal-axis-range    ; unused
;	   (extract-number-or-value
;	     (horizontal-axis-range graph-grid)))
	      (grid-width 
		(grid-width-for-graph graph-grid))
	      (grid-height
		(grid-height-for-graph graph-grid))
	      (grid-border-width
		(grid-border-width current-graph-rendering))
	      (update-graph-description?
		(not (graph-description-up-to-date? graph-grid)))
	      (draw-data?
		(and update-graph-description?
		     (not erase-instead?)
		     (not (scale-too-small-for-details-p
			    current-image-x-scale current-image-y-scale))))
	      (new-data? nil)
	      (new-dateline-in-workspace-units-p nil))
	 
	 (when update-graph-description?
	   (reclaim-graph-tree 
	     (line-drawing-description-for-graph-grid? graph-grid))
	   (setf (line-drawing-description-for-graph-grid? graph-grid)
		 (graph-list (graph-list 'graph))
		 (tail-pointer-for-line-drawing-description graph-grid)
		 (line-drawing-description-for-graph-grid? graph-grid)
		 (tail-pointer-for-line-segments graph-grid) nil))
	 
	 (clear-data-clipping-rectangles)
	 
	 (when draw-data?
	   ;; Draw data.
	   ;; First, adjust dateline if necessary.
	   (when (not (=f (old-dateline graph-grid)
			  (dateline graph-grid)))
	     (setq new-dateline? t)
	     (with-temporary-gensym-float-creation
	       draw-only-new-data-for-graph-grid
	       (let ((left-edge-of-rectangle-in-raster
		       (compute-x-value-on-graph
			 (old-dateline graph-grid) graph-grid))
		     (right-edge-of-rectangle-in-raster
		       (compute-x-value-on-graph
			 (dateline graph-grid) graph-grid))
		     (left-edge-of-erase-rectangle
		       (compute-x-value-on-graph
			 (compute-erase-dateline-1 
			   graph-grid (old-dateline graph-grid))
			 graph-grid))
		     (right-edge-of-erase-rectangle
		       (compute-x-value-on-graph
			 (compute-erase-dateline graph-grid)
			 graph-grid))
		     (show-grid-lines? (show-grid-lines? graph))
		     (extra-grid-lines? (extra-grid-lines? graph)))
		 (setq new-dateline-in-workspace-units-p
		       (not (=w (old-dateline-in-workspace-units graph-grid)
				right-edge-of-rectangle-in-raster)))
		 (setf (old-dateline graph-grid) (dateline graph-grid)
		       (old-dateline-in-workspace-units graph-grid)
		       right-edge-of-rectangle-in-raster)
		 (when new-dateline-in-workspace-units-p
		   (add-graph-new-dateline 
		     right-edge-of-rectangle-in-raster right-edge-of-erase-rectangle))
		 (cond
		   ((>f left-edge-of-erase-rectangle
			right-edge-of-erase-rectangle)
		    (add-graph-clear-rectangle
		      left-edge-of-erase-rectangle 0
		      (grid-and-erase-zone-width graph-grid)
		      grid-height)
		    (add-graph-clear-rectangle
		      0 0
		      right-edge-of-erase-rectangle grid-height))
		   (t
		    (add-graph-clear-rectangle
		      left-edge-of-erase-rectangle 0
		      right-edge-of-erase-rectangle grid-height)))
		 (cond
		   ((>f left-edge-of-rectangle-in-raster
			right-edge-of-rectangle-in-raster)
		    (cond
		      (show-grid-lines?
		       (draw-horizontal-grid-lines
			 graph-grid graph left-edge-of-rectangle-in-raster 
			 (grid-and-erase-zone-width graph-grid))
		       (draw-horizontal-grid-lines
			 graph-grid graph 0 right-edge-of-rectangle-in-raster)
		       (draw-new-scrolled-vertical-grid-lines graph-grid))
		      (extra-grid-lines?
		       (draw-extra-grid-lines
			 graph-grid extra-grid-lines? left-edge-of-rectangle-in-raster
			 (grid-and-erase-zone-width graph-grid))
		       (draw-extra-grid-lines
			 graph-grid extra-grid-lines? 0
			 right-edge-of-rectangle-in-raster))))
		   (t
		    (cond
		      (show-grid-lines?
		       (draw-horizontal-grid-lines
			 graph-grid graph
			 left-edge-of-rectangle-in-raster 
			 right-edge-of-rectangle-in-raster)
		       (draw-new-scrolled-vertical-grid-lines graph-grid))
		      (extra-grid-lines?
		       (draw-extra-grid-lines
			 graph-grid extra-grid-lines?
			 left-edge-of-rectangle-in-raster 
			 right-edge-of-rectangle-in-raster))))))))

	   (loop with extrema-rectangles? = nil
		 with compute-extrema? = t
		 for plot in (list-of-plots graph-grid)
		 as plot-number = 1 then (+f plot-number 1)
		 as data-buffer-for-plot
		    = (data-buffer-for-plot plot)
		 
		 if (and data-buffer-for-plot
			 (not (ring-buffer-empty?
				data-buffer-for-plot)))
		   do
;		(if (not (use-one-set-of-axes? graph-format))
;		    ;; Not yet implemented.
;		    )
		     
	     ;; optimized data point drawing and erasing
		     
		     (when (not erase-instead?)
		       ;; draw new data points
		       (if (or (not (=f (new-data-boundary-index
					  data-buffer-for-plot)
					(newest-active-element-index
					  data-buffer-for-plot)))
			       (draw-new-first-data-point? data-buffer-for-plot))
			   (progn
			     (draw-data-for-plot
			       data-buffer-for-plot
			       (new-data-boundary-index
				 data-buffer-for-plot)
			       (newest-active-element-index
				 data-buffer-for-plot)
			       data-point-size
			       (plot-color-given-plot plot)
			       (plot-marker-given-plot plot)
			       (plot-shading-given-plot plot)
			       (plot-line-width-given-plot plot))
			     (setq new-data? t)
			     (setf (new-data-boundary-index
				     data-buffer-for-plot)
				   (newest-active-element-index
				     data-buffer-for-plot)))))
		     
		     (when (and (not new-dateline?)
				compute-extrema?
				minimum-x-value-for-new-data)
		       (cond
			 ((not (<w minimum-x-value-for-new-data
				   (get-erase-dateline-on-graph graph-grid)
				   maximum-x-value-for-new-data))
			  ;; If left and right edges straddle erase-raster-dateline,
			  ;; don't do data clipping.

			  (setq extrema-rectangles?
				(combine-new-extrema-with-existing-ones
				  extrema-rectangles?
				  minimum-x-value-for-new-data 
				  minimum-y-value-for-new-data
				  maximum-x-value-for-new-data
				  maximum-y-value-for-new-data))
			  (store-new-data-extrema nil nil))
			 (t
			  (setq compute-extrema? nil
				extrema-rectangles? nil))))
		 finally
		   (when extrema-rectangles?
		     (add-graph-data-extrema extrema-rectangles?))))
	 
	 (when (or new-data? new-dateline-in-workspace-units-p)
	   (setf (draw-graph-rendering-to-show-new-data? graph-grid) t))
	 
	 (when (draw-graph-rendering-to-show-new-data? graph-grid)
	   (update-graph-rendering)
	   (draw-current-graph-rendering
	     (+r (x-in-window left-edge-of-grid) grid-border-width)
	     (+r (y-in-window top-edge-of-grid) grid-border-width)
	     (-r (x-in-window right-edge-of-grid) grid-border-width)
	     (-r (y-in-window bottom-edge-of-grid) grid-border-width)))
	 
	 (setf (graph-description-up-to-date? graph-grid) 'scrolling)
	 (add-to-set (currently-up-to-date-image-planes graph-grid)
		     current-image-plane
		     graph)
	 ))
      (t

       ;; Graph rendering has been decached.  Do complete reformat
       ;; in manner similar to that for draw method.  
       ;; This is actually the best way to handle this since it
       ;; does not do a complete reformat until it is definitely needed.

       (let ((redraw-as-well-as-reformat-p nil))
	 (make-or-reformat-graph-grid 
	   nil graph-grid (graph-format graph) t t))
       (make-graph-not-up-to-date graph-grid)
       (setf (graph-reformatted-since-start? graph) nil)
       ;; Graph-reformatted-since-start? is set to nil to ensure that the
       ;; next time make-or-reformat-graph-grid is called, a scrolling
       ;; reformat won't be attempted.  An alternative to this would be
       ;; to set some flag that would cause 
       ;; make-or-reformat-graph-grid to call update-images before 
       ;; reformatting.
       (draw-graph-grid-and-data 
	 graph-grid
	 (not (memq current-image-plane
		    (currently-up-to-date-image-planes graph-grid))))
       (add-to-set (currently-up-to-date-image-planes graph-grid)
		   current-image-plane
		   graph)
       ))))

;; The flag draw-graph-rendering-to-show-new-data?  is necessary because
;; draw-only-new-data-for-graph-grid?  is optimized to call draw-graph-rendering
;; only when there is new data or the graph is being scrolled.  If this isn't the
;; case, draw-graph-rendering is not called.  It is necessary to note whether
;; draw-graph-rendering should be called in the
;; draw-graph-rendering-to-show-new-data?  slot because new-data?  and
;; new-dateline-in-workspace-units-p are only computed for the first image plane;
;; after the first image plane, draw-only-new-data-for-graph-grid?  will bypass
;; most of its computation because the graph-description-up-to-date?  slot is
;; non-nil.  If the draw-graph-rendering-to-show-new-data?  slot were not used,
;; draw-only-new-data-for-graph-grid?, when it is called for an image plane other
;; than the first, would not know that it has to call draw-graph-rendering.  Note
;; that this is not an issue with draw-graph-grid-and-data since there,
;; draw-graph-rendering is always called.  The
;; draw-graph-rendering-to-show-new-data?  slot is reset in
;; update-images-of-only-new-data-for-graph-grid, which is the only function that
;; calls draw-only-new-data-for-graph-grid?.

;; New-dateline-in-workspace-units-p is used as an optimization over new-dateline?
;; because the dateline in workspace units will sometimes not change even if the
;; dateline does change.  This is typical when the horizontal axis range is large.
;; Use of new-dateline-in-workspace-units-p thus prevents unnecessary updates
;; (updates where the graph does not change at all).

;; Note that nothing should ever be drawn to the right of, or on the new dateline
;; since this represents the low end or oldest part of the graph.  It will be 
;; erased by the next scroll.  

;; See if code in draw-only-new-data-for-graph-grid and
;; draw-data-for-graph-grid can be combined.

;; One good way to check clipping is to change draw-data-point to a function,
;; trace it, and trace add-graph-data-extrema.  Another good way is to
;; set debug-mode-for-clipping?.




(defun combine-new-extrema-with-existing-ones 
       (extrema-rectangles? min-x min-y max-x max-y)
  (loop with rectangles-to-combine = nil
	with combined-min-x = min-x
	with combined-min-y = min-y
	with combined-max-x = max-x
	with combined-max-y = max-y
	as previous-rest-of-rectangles = nil then rest-of-rectangles
	as rest-of-rectangles = extrema-rectangles?
			      then (nthcdr 4 rest-of-rectangles)
	while rest-of-rectangles
	as rectangle-left-edge = (first rest-of-rectangles)
	as rectangle-top-edge = (second rest-of-rectangles)
	as rectangle-right-edge = (third rest-of-rectangles)
	as rectangle-bottom-edge = (fourth rest-of-rectangles)
	do
    (when (rectangles-overlap-p
	    min-x min-y max-x max-y
	    rectangle-left-edge rectangle-top-edge
	    rectangle-right-edge rectangle-bottom-edge)
      (setq combined-min-x (minw combined-min-x rectangle-left-edge)
	    combined-min-y (minw combined-min-y rectangle-top-edge)
	    combined-max-x (maxw combined-max-x rectangle-right-edge)
	    combined-max-y (maxw combined-max-y rectangle-bottom-edge)
	    rectangles-to-combine 
	    (graph-cons previous-rest-of-rectangles rectangles-to-combine)))
	finally
	  (return
	    (cond
	      (rectangles-to-combine
	       (loop for rectangle-pointer in rectangles-to-combine
		     as rectangle-to-reclaim-head = (nthcdr 4 rectangle-pointer)
		     do
		 (cond 
		   (rectangle-pointer
		    (setf (cddddr rectangle-pointer) (nthcdr 8 rectangle-pointer)
			  (cddddr rectangle-to-reclaim-head) nil)
		    (reclaim-graph-list rectangle-to-reclaim-head))
		   (t
		    (let ((extrema-rectangles-head extrema-rectangles?))
		      (setf extrema-rectangles? (nthcdr 4 extrema-rectangles?)
			    (cddddr extrema-rectangles-head) nil)
		      (reclaim-graph-list extrema-rectangles-head)))))
	       (reclaim-graph-list rectangles-to-combine)
	       (graph-cons 
		 combined-min-x
		 (graph-cons
		   combined-min-y
		   (graph-cons combined-max-x
			       (graph-cons combined-max-y extrema-rectangles?)))))
	      (t
	       (graph-cons 
		 min-x
		 (graph-cons
		   min-y
		   (graph-cons max-x
			       (graph-cons max-y extrema-rectangles?)))))))))




;;; Draw-data-point takes the coordinates and color of the data point as
;;; args and draws it on the graph ...

;; The argument plot-marker? is used in NUPEC.
;; -- UPDATE: Removed additional test for nupec-authorized-p.  This type of
;; change is needed to allow non-NUPEC Telewindows to work with NUPEC G2.  cpm,
;; 8/21/91

(defun draw-data-point
    (x-on-graph y-on-graph previous-x-on-graph previous-y-on-graph
     first-time-p data-point-y-size plot-marker?)
  (declare (ignore data-point-y-size))
  (cond
    ((consp plot-marker?)
     (let* ((plot-marker-class (cdr plot-marker?))
	    (icon-description?
	      (get-icon-description-given-class plot-marker-class)))
       (cond 
	 (icon-description?
	  (draw-plot-marker
	    plot-marker-class x-on-graph y-on-graph
	    (width-of-icon icon-description?)
	    (halfw (height-of-icon icon-description?))
	    (get-erase-dateline-on-graph graph-grid-for-data)))
	 (t
	  ;; This class doesn't have an icon description -- there should be a
	  ;; frame note in the graph in this case, not a runtime warning! (MHD)
	  ))))
    ;; draw graph line
    ((<=w previous-x-on-graph x-on-graph)
     (add-graph-line
       first-time-p
       previous-x-on-graph previous-y-on-graph
       x-on-graph y-on-graph))
    (t
     ;; Interpolate and draw two lines.
     (with-temporary-gensym-float-creation draw-data-point
       (let* ((grid-and-erase-zone-width
		(grid-and-erase-zone-width graph-grid-for-data))
	      (dx1 (-w grid-and-erase-zone-width previous-x-on-graph))
	      (dx (+w x-on-graph dx1 1))
	      (dy (-w y-on-graph previous-y-on-graph))
	      (ratio
		(/ (coerce-to-gensym-float dy) (coerce-to-gensym-float dx)))
	      (dy1 (round (* ratio dx1)))
;	      (dy2 (round (* ratio x-on-graph))) ; only needed for y2, see below
	      (y1 (+w previous-y-on-graph dy1))
;	      (y2 (-w y-on-graph dy2))  ; removed because y2 should be the same as y1,
					; except for roundoff error
	      )
	 (add-graph-line
	   first-time-p
	   previous-x-on-graph previous-y-on-graph
	   grid-and-erase-zone-width y1)
	 (add-graph-line
	   t 0 y1 x-on-graph y-on-graph)
	 (when minimum-x-value-for-new-data	       ; if doing data clipping
	   (extend-extrema-if-necessary grid-and-erase-zone-width y1)
	   (extend-extrema-if-necessary 0 y-on-graph)))))))



(defparameter offset-ratio-for-plot-markers 0.3)

(defparameter default-marker-size 10)
(defparameter default-marker-half-size 5)
(defparameter plus-sign-marker-size 14)
(defparameter plus-sign-marker-half-size 7)

;; Consider making this a function of graph size and letting user
;; specify some sort of percentage of graph size.



(defun draw-plot-marker 
       (plot-marker? marker-x marker-y marker-size marker-half-size
	erase-dateline-on-graph)
  (let ((marker-left-edge (-w marker-x marker-size)))
    (add-graph-marker 
      plot-marker? marker-x marker-y)
    (cond 
      ((not (<w marker-left-edge 0))
       ;; Extend extrema so that entire marker will be put up.
       (when (not new-dateline?)
	 (extend-minimum-x-value-if-necessary
	   marker-left-edge)
	 (extend-minimum-y-value-if-necessary
	   (-w marker-y marker-half-size))
	 (extend-maximum-y-value-if-necessary
	   (+w marker-y marker-half-size))))
      (t  ; plot marker is at edge of raster and must be drawn twice.
       (let ((grid-and-erase-zone-width
	       (grid-and-erase-zone-width graph-grid-for-data)))
	 (when (<w marker-x erase-dateline-on-graph)
	   ;; Don't wrap around if marker-x is to the right of erase dateline.
	   (add-graph-marker
	     plot-marker? 
	     (+w marker-x (grid-and-erase-zone-width graph-grid-for-data))
	     marker-y))
	 (when (not new-dateline?)
	   (extend-minimum-x-value-if-necessary 0)
	   (extend-minimum-x-value-if-necessary grid-and-erase-zone-width)
	   (extend-minimum-y-value-if-necessary
	     (-w marker-y marker-half-size))
	   (extend-maximum-y-value-if-necessary
	     (+w marker-y marker-half-size))))))))

;; Need to improve clipping for triangle plot marker.  It sometimes doesn't
;; look good for the wrap-around case!




(defun draw-data-for-plot
       (data-buffer-for-plot
	plot-data-point-begin-index
	plot-data-point-end-index
	data-point-y-size
	plot-color? plot-marker? plot-shading? plot-line-width?)
  ;; Consider making some of these arguments special variables
  ;; instead!

  (add-graph-color-to-use plot-color?)
  (add-graph-shading plot-shading?)
  (add-graph-line-width-to-use plot-line-width?)
  ;; Consider calling these only if plot info has changed from previous plot!
  
  (setq data-point-y-size default-data-point-y-size)
  ;; Use global parameter for now rather than format frame value.
  
  (loop with previous-y-on-graph = nil
	with previous-x-on-graph = nil
	with plot-data-point-index 
	  = plot-data-point-begin-index
	with first-time-data-point-drawn-p = t
	with number-of-data-points-to-plot
	  = (ring-buffer-index-difference
	      data-buffer-for-plot 
	      plot-data-point-end-index plot-data-point-begin-index)
	for count from 1 to number-of-data-points-to-plot
	as first-time-p = t then nil
	do
    (multiple-value-bind
      (x-begin-value y-value)
	(get-plot-data-ring-buffer-element
	  data-buffer-for-plot
	  plot-data-point-index)
      (when (null previous-x-on-graph)
	(setq previous-x-on-graph x-begin-value
	      previous-y-on-graph y-value))

      (when (not new-dateline?)
	(cond
	  (minimum-x-value-for-new-data
	   (if (not plot-line-width?)
	       (extend-extrema-if-necessary x-begin-value y-value)
	       (let ((extra-room (ceilingw plot-line-width? 2)))
		 (extend-extrema-if-necessary 
		   x-begin-value (+w y-value extra-room))
		 (extend-extrema-if-necessary 
		   x-begin-value (-w y-value extra-room)))))
	  (t
	   (cond 
	     (plot-shading?
	      (store-new-data-extrema x-begin-value y-value)
	      (extend-extrema-if-necessary x-begin-value grid-height))
	     (t
	      (if (not plot-line-width?)
	       (store-new-data-extrema x-begin-value y-value)
	       (let ((extra-room (ceilingw plot-line-width? 2)))
		 (store-new-data-extrema
		   x-begin-value (+w y-value extra-room))
		 (store-new-data-extrema
		   x-begin-value (-w y-value extra-room)))))))))

      (setq plot-data-point-index
	    (increment-active-element-index
	      plot-data-point-index
	      data-buffer-for-plot))
      (when (or (draw-new-first-data-point? data-buffer-for-plot)
		(not first-time-p))
	#+development			; used to detect the "slasher bug", now
					;   thought to be fixed!  (MHD 9/23/93)
	(when (=f x-begin-value		; should probably NEVER happen legitimately
		  (-f previous-x-on-graph 1))
	  (format t "~%Slasher bug detected!")
	  (print-contents-of-plot-data-buffer data-buffer-for-plot)
	  (print (list previous-x-on-graph x-begin-value)))
	(draw-data-point
	    x-begin-value
	    y-value
	    previous-x-on-graph
	    previous-y-on-graph
	    first-time-data-point-drawn-p
	    data-point-y-size
	    plot-marker?)
	(setq first-time-data-point-drawn-p nil))
      (setq previous-x-on-graph x-begin-value)
      (setq previous-y-on-graph y-value)))

  ;; Draw plot markers if any.
  (when (and plot-marker?
	     (symbolp plot-marker?))
    (loop with erase-dateline-on-graph
	    = (get-erase-dateline-on-graph graph-grid-for-data)
	  for index in (plot-marker-indices data-buffer-for-plot)
	  do
      ;; Draw marker.
      (multiple-value-bind
	(marker-x marker-y)
	  (get-plot-data-ring-buffer-element
	    data-buffer-for-plot index)
	(draw-plot-marker 
	  plot-marker? marker-x marker-y 
	  plus-sign-marker-size plus-sign-marker-half-size
	  erase-dateline-on-graph))
; Note C
;	  finally
;	    (reclaim-plot-marker-indices 
;	      (plot-marker-indices data-buffer-for-plot))
;	    (setf (plot-marker-indices data-buffer-for-plot) nil)
	    )))

;; Note that it is necessary to compute number-of-data-points-to-plot due to
;; wrap-around of ring buffer; it is not satisfactory to test for end of the loop
;; by simply doing
;; (>=f plot-data-point-index plot-data-point-end-index).

;; Review arguments to this and other draw functions.  Check if some args should
;; be removed since so much information is available from special variables!
;; Note that special variables are widely used in all draw and window operations.

;; Note C: This function moves plot-data -to-> drawing-description.  Presumably
;; we could discard the plot data after doing this if we reuse the 
;; drawing-description for each image.  But apparently we don't do that
;; by commenting out this code keep the plot-markers around for use when
;; we draw the next image.



;;;; Functions for adding to graph line drawing description

(defun add-graph-rectangle
       (left-edge-of-rectangle-in-raster top-edge-of-rectangle-in-raster
	right-edge-of-rectangle-in-raster bottom-edge-of-rectangle-in-raster)
  (add-form-to-graph-line-drawing-description
    (graph-list 'solid-rectangle
		(graph-list left-edge-of-rectangle-in-raster 
			    top-edge-of-rectangle-in-raster)
		(graph-list right-edge-of-rectangle-in-raster 
			    bottom-edge-of-rectangle-in-raster))))

(defun add-graph-clear-rectangle
       (left-edge-of-rectangle-in-raster top-edge-of-rectangle-in-raster
	right-edge-of-rectangle-in-raster bottom-edge-of-rectangle-in-raster)
  (add-form-to-graph-line-drawing-description
    (graph-list 'clear-solid-rectangle
		(graph-list left-edge-of-rectangle-in-raster 
			    top-edge-of-rectangle-in-raster)
		(graph-list right-edge-of-rectangle-in-raster 
			    bottom-edge-of-rectangle-in-raster))))

(defun add-graph-new-dateline (dateline-in-raster erase-dateline-in-raster)
  (add-form-to-graph-line-drawing-description
    (graph-list 'graph-dateline 
		(graph-list dateline-in-raster erase-dateline-in-raster))))

(defun add-graph-data-extrema (extrema-rectangles)
  (add-form-to-graph-line-drawing-description
    (graph-list 'data-extrema extrema-rectangles)))

(defun add-graph-line
       (start-new-line?	x1 y1 x2 y2)
  (if (null (tail-pointer-for-line-segments graph-grid-for-data))
      (setf (tail-pointer-for-line-segments graph-grid-for-data)
	    (line-drawing-description-for-graph-grid? graph-grid-for-data)))
  (if (not start-new-line?)
      (setf (cdr (tail-pointer-for-line-segments graph-grid-for-data))
	    (graph-list (graph-list x2 y2))
	    (tail-pointer-for-line-segments graph-grid-for-data)
	    (cdr (tail-pointer-for-line-segments graph-grid-for-data)))
      (setf (cdr (tail-pointer-for-line-drawing-description graph-grid-for-data))
	    (graph-list
	      (graph-list 'lines
			  (graph-list x1 y1)
			  (graph-list x2 y2)))
	    (tail-pointer-for-line-drawing-description graph-grid-for-data)
	    (cdr (tail-pointer-for-line-drawing-description graph-grid-for-data))
	    (tail-pointer-for-line-segments graph-grid-for-data)
	    (cddar (tail-pointer-for-line-drawing-description graph-grid-for-data)))))

(defun add-graph-clear ()
  (add-form-to-graph-line-drawing-description 
    (graph-list 'clear-graph)))

(defun add-graph-color-to-use (color)
  (add-form-to-graph-line-drawing-description
    (graph-list 'graph-color-to-use color)))

(defun add-graph-shading (shading?)
  (add-form-to-graph-line-drawing-description
    (graph-list 'graph-shading? shading?)))

(defun add-graph-line-width-to-use (line-width?)
  (add-form-to-graph-line-drawing-description
    (graph-list 'graph-line-width-to-use line-width?)))

(defun add-graph-marker (plot-marker x-position y-position)
  (add-form-to-graph-line-drawing-description
    (graph-list 'graph-marker plot-marker x-position y-position)))


(defun add-form-to-graph-line-drawing-description (form)
  (setf (cdr (tail-pointer-for-line-drawing-description graph-grid-for-data))
	(graph-list form)
	(tail-pointer-for-line-drawing-description graph-grid-for-data)
	(cdr (tail-pointer-for-line-drawing-description graph-grid-for-data))))




;;;; Painting Graph Renderings


;;; Paint-graph-rendering-raster loads the raster or rasters used for the graph
;;; into the current scratchpad raster and paints it appropriately.  When done,
;;; the scratchpad raster is converted back to a stored raster.
;;; Paint-graph-rendering-raster is similar to make-rendering-structure which is
;;; used for icons.  However, because icons are not changed after they are
;;; painted, make-rendering-structure does not have to worry about loading stored
;;; rasters into the current scratchpad raster.

;;; Note that this graph renderings facility is also used, with some variations,
;;; by the CHARTS module.

;;; For color graphs, three possibilities exist in xwindow platforms for
;;; rasters; using a set of monochrome rasters as is done with icons, doing the
;;; same but allowing the new operations that work on a set of monochrome
;;; rasters known as a monochrome-raster-list, or using a true polychrome
;;; raster.  Which approach to use is determined by the
;;; format-of-graph-rendering-structure slot of the graph-rendering (see
;;; graph-rendering-uses-polychrome-rasters?  and
;;; graph-rendering-uses-monochrome-raster-lists?).

;;; As with icons, when a set of monochrome rasters is used, it is necessary not
;;; only to paint the appropriate lines, rectangles, etc.  into the plane of the
;;; appropriate color, but also to "burn" the lines and rectangles in all the
;;; other planes so that these regions are cleared.  This way, when the planes
;;; are bitblted on top of each other on the window, there won't be any x-or
;;; problems between painted regions of the different planes (see
;;; add-from-graph-rendering-to-current-window).  This involves entering an
;;; on-scratchpad-raster context for each raster.

;;; The monochrome-raster-list approach works the same way but only enters a single
;;; scratchpad-raster context, in this case the macro
;;; 
;;;   on-scratchpad-raster-list-given-stored-raster-list
;;; 
;;; is used.  The raster painting operations on the other side of ICP then paint
;;; appropriately in all rasters, 1s in the raster corresponding to color-value,
;;; and 0s in all others.

(defmacro transfer-info-from-graph-grid-to-graph-rendering ()
  `(setf (line-drawing-description-for-graph-rendering? 
	   current-graph-rendering)
	 (line-drawing-description-for-graph-grid? 
	   graph-grid-for-data)))

;; ;; Review whether this is necessary!  Rather than setting these slots,
;; ;; the information could be accessed directly from the graph grid.
;; -- comment obsolete if we're going to have charts without graph-grid
;; subframes. (MHD/BAH 8/28/90)


(defun update-graph-rendering ()
  (when (cdr (line-drawing-description-for-graph-grid? graph-grid-for-data))
    (transfer-info-from-graph-grid-to-graph-rendering)
    (paint-graph-rendering-raster)))


(defun paint-graph-from-graph-rendering 
			(graph-rendering foreground-color-value? first-time?)
  (paint-graph-on-scratchpad-raster
    first-time? foreground-color-value? 
    (line-drawing-description-for-graph-rendering? graph-rendering)
    (width-of-rendered-graph graph-rendering)
    (height-of-rendered-graph graph-rendering)
    (x-scale-of-graph-rendering graph-rendering)	
    (y-scale-of-graph-rendering graph-rendering)))

(defun update-colors-of-current-graph-rendering ()
  (if (graph-rendering-uses-monochrome-raster-lists?
	current-graph-rendering)
      ;; Between Telewindows Protocol versions, a new message
      ;; was created whose second arg was changed from a number
      ;; to a list of color values. (MHD 2/16/93)
      (update-ring-raster-for-graph-given-color-values-2
	current-graph-rendering
	(color-values-for-rasters? current-graph-rendering))
      (update-ring-raster-for-graph-given-color-values
	current-graph-rendering
	(length (color-values-for-rasters? current-graph-rendering)))))

(defun paint-graph-rendering-raster ()
  (cond ((and (native-printing-p)
	      (not bogus-preflight-from-printing-to-graphs))
	 (paint-graph-to-native-printer current-graph-rendering))
	(t
	 (paint-graph-rendering-raster-1))))

(defun paint-graph-rendering-raster-1 ()
  ; now done in update-graph-rendering (MHD 8/28/90)
  ; (transfer-info-from-graph-grid-to-graph-rendering)
  (case type-of-current-window
    (icp
     (let ((current-scratchpad-raster-type 'icp))
       (if (graph-rendering-uses-monochrome-raster-lists? current-graph-rendering)
	   ;; Between Telewindows Protocol versions, a new message
	   ;; was created whose second arg was changed from a number
	   ;; to a list of color values. (MHD 2/16/93)
	   (update-ring-raster-for-graph-given-color-values-2
	     current-graph-rendering
	     (color-values-for-rasters? current-graph-rendering))
	   (update-ring-raster-for-graph-given-color-values
	     current-graph-rendering
	     (length (color-values-for-rasters? current-graph-rendering))))
       (send-icp-prepare-for-painting-graph current-graph-rendering)
       (cond
	 ((or (graph-rendering-uses-polychrome-rasters? current-graph-rendering)
	      (graph-rendering-uses-monochrome-raster-lists? current-graph-rendering))
	  (paint-graph-from-graph-rendering current-graph-rendering nil t)
	  (send-icp-end-message-block))
	 (t
	  (loop for foreground-color-value-for-current-raster
		    in (color-values-for-rasters? current-graph-rendering)
		as first-time? = t then nil
		do (paint-graph-from-graph-rendering 
		     current-graph-rendering 
		     foreground-color-value-for-current-raster first-time?)
		   (send-icp-end-message-block))))))
    (t
     (make-graph-rendering-structure-if-necessary current-graph-rendering)     
     (let* ((current-graph-rendering-structure
	      (graph-rendering-structure? current-graph-rendering)))
       (if (graph-rendering-uses-monochrome-raster-lists? current-graph-rendering)
	   ;; Between Telewindows Protocol versions, a new message
	   ;; was created whose second arg was changed from a number
	   ;; to a list of color values. (MHD 2/16/93)
	   (update-ring-raster-for-graph-given-color-values-2
	     current-graph-rendering
	     (color-values-for-rasters? current-graph-rendering))
	   (update-ring-raster-for-graph-given-color-values
	     current-graph-rendering
	     (length (color-values-for-rasters? current-graph-rendering))))
       (let ((paint-only-target-monochrome-raster-p
	       (paint-foreground-only-p current-graph-rendering)))
	 (if (graph-rendering-uses-polychrome-rasters? current-graph-rendering)
	     (on-scratchpad-raster-given-stored-raster
		 (current-window 
		   (raster-or-rasters current-graph-rendering-structure)
		   (adjusted-allocation-width-of-graph-rendering-structure
		     current-graph-rendering)
		   (adjusted-allocation-height-of-graph-rendering-structure
		     current-graph-rendering)
		   8)				; fix later!! (MHD 2/2/93)	       
	       (paint-graph-from-graph-rendering current-graph-rendering nil t))
	     (if (graph-rendering-uses-monochrome-raster-lists? current-graph-rendering)
		 (on-scratchpad-raster-list-given-stored-raster-list
		     (current-window
		       (raster-or-rasters current-graph-rendering-structure)
		       (color-values-for-raster-list current-graph-rendering-structure)
		       (adjusted-allocation-width-of-graph-rendering-structure
			 current-graph-rendering)
		       (adjusted-allocation-height-of-graph-rendering-structure
			 current-graph-rendering))
		   (paint-graph-from-graph-rendering current-graph-rendering nil t))
		 (loop for stored-raster
			   in (raster-or-rasters current-graph-rendering-structure)
		       for foreground-color-value-for-current-raster
			   in (color-values-for-rasters? current-graph-rendering)
		       as first-time? = t then nil
		       do (on-scratchpad-raster-given-stored-raster
			      (current-window 
				stored-raster
				(adjusted-allocation-width-of-graph-rendering-structure
				  current-graph-rendering)
				(adjusted-allocation-height-of-graph-rendering-structure
				  current-graph-rendering)
				1)
			    (paint-graph-from-graph-rendering 
			      current-graph-rendering 
			      foreground-color-value-for-current-raster first-time?))))))))))

;; Optimize to not call update-ring-raster-for-graph-given-color-values
;; if colors haven't changed!

;; For the telewindows case, the rendering structure is made by
;; begin-making-graph-rendering which is called automatically because
;; graph-rendering is an icp object type.  Thus,
;; make-graph-rendering-structure-if-necessary is only used for the
;; non-telewindows case.

;; Consider renaming the "paint" functions since they may do more than just
;; paint rasters;  they can cause rasters to be allocated as well.

;; Note that there is no need to keep color values in remote graph renderings
;; in Telewindows processes.  All color computations are done on the G2
;; side.



(defun make-graph-rendering-structure-if-necessary (graph-rendering)
  (when (not (graph-rendering-structure? graph-rendering))
    (setf (graph-rendering-structure? graph-rendering)
	  (make-graph-rendering-structure
	    (width-of-graph-rendering-structure graph-rendering)))))



(defun paint-graph-line-in-current-scratchpad-raster
			(x1 y1 x2 y2 graph-line-color-value shading? line-width?)
  
  (if shading?
      (paint-shaded-line-in-current-scratchpad-raster
	x1 y1 x2 y2 graph-line-color-value)
      (if line-width?
	  (paint-wide-line-in-current-scratchpad-raster
	    x1 y1 x2 y2 graph-line-color-value t line-width?)
	  (paint-line-in-current-scratchpad-raster
	    x1 y1 x2 y2 graph-line-color-value t))))



(defun paint-graph-on-scratchpad-raster
       (first-time? foreground-color-value?
	line-drawing-description
	width height				; before scaling
	x-scale y-scale)

  (loop	with graph-rendering-uses-polychrome-rasters?
	  = (graph-rendering-uses-polychrome-rasters?
	      current-graph-rendering)
	with graph-rendering-uses-monochrome-raster-lists?
	  = (graph-rendering-uses-monochrome-raster-lists?
	      current-graph-rendering)
	with graph-fill-color-value 
	  = (or (if (or graph-rendering-uses-polychrome-rasters?
			graph-rendering-uses-monochrome-raster-lists?)
		    (grid-background-color-value current-graph-rendering))
		0)
	with graph-line-color-value = 1
	with burning? = nil
	with shading? = nil
	with scaled-line-width? = nil
	for description-element			; first description-element is just '(graph)
	    in (cdr line-drawing-description)
	as description-command
	   = (first description-element)
	as points
	   = (unless (or (eq description-command 'graph-color-to-use)
			 (eq description-command 'graph-marker)
			 (eq description-command 'graph-shading?)
			 (eq description-command 'graph-line-width-to-use))
	       (cdr description-element))
	do (case description-command
	     (clear-graph
	      (paint-solid-rectangle-in-current-scratchpad-raster
		(delta-x-in-window 0 x-scale)
		(delta-y-in-window 0 y-scale)
		(delta-x-in-window width x-scale)
		(delta-y-in-window height y-scale)
		graph-fill-color-value))
	     (lines
	      ;; the following loop straightens multilines
	      ;; into single lines; it also never draws zero-length lines; this
	      ;; does not help that much except when refreshing an entire graph,
	      ;; since the incremental updates only involve one pair of points;
	      ;; however, for a complete refresh this might save a lot of excess
	      ;; draw messages.  (MHD 2/3/93)
	      ;; --- NOTE: there is apparently a bug that the first pair of
	      ;; points are always equal.  That should be fixed at a layer
	      ;; of the graphs software higher up!! (MHD 2/8/93)
	      (loop for remaining-points = points then (cdr remaining-points)
		    as ((x1 y1) (x2 y2)) = remaining-points
		    as x1-scaled first (delta-x-in-window x1 x-scale)
				 then x2-scaled
		    as y1-scaled first (delta-y-in-window y1 y-scale)
				 then y2-scaled
		    as x2-scaled first (delta-x-in-window x2 x-scale)
				 then x3-scaled?
		    as y2-scaled first (delta-y-in-window y2 y-scale)
				 then y3-scaled?
		    as x3-scaled? = (if (cddr remaining-points)
					(delta-x-in-window
					  (first (first (cddr remaining-points)))
					  x-scale))
		    as y3-scaled? = (if (cddr remaining-points)
					(delta-y-in-window
					  (second (first (cddr remaining-points)))
					  y-scale))
		    count
		      (cond
			((and (=f x1-scaled x2-scaled)
			      (=f y1-scaled y2-scaled))
			 ;; zero-length line -- noop
			 nil)
			((and y3-scaled?
			      (=r y1-scaled y2-scaled)
			      (=r y3-scaled? y2-scaled))
			 ;; straight horizontal line
			 (setq x2-scaled x1-scaled)
			 nil)
			((and x3-scaled?
			      (=r x1-scaled x2-scaled)
			      (=r x3-scaled? x2-scaled))
			 ;; straight vertical line (less common)
			 (setq y2-scaled y1-scaled)
			 nil)
			
			((and x3-scaled? y3-scaled?
			      (or
				;; Consider 3 points crammed into 3 columns
				;; or rows to be on a line.
				;; -- Questionable: Consider the
				;; series (1,1), (2,1), (100, 2).  On the
				;; other hand, it will look the same 90% of
				;; time.  Still questionable.  
;				(or (if (=r (-r x1-scaled x2-scaled) 1)
;					(>=r 0 (-r x2-scaled x3-scaled?) 1)
;					(if (=r (-r x1-scaled x2-scaled) -1)
;					    (<=r 0 (-r x2-scaled x3-scaled?) -1)))
;				    (if (=r (-r y1-scaled y2-scaled) 1)
;					(>=r 0 (-r y2-scaled y3-scaled?) 1)
;					(if (=r (-r y1-scaled y2-scaled) -1)
;					    (<=r 0 (-r y2-scaled y3-scaled?) -1))))
				;; NOTE: the following has a chance of
				;; filling slightly different pixels due to
				;; rasterization, but it should never be off by
				;; more than one pixel, and should always draw
				;; the right shape.  (MHD 2/8/93)
				;; Check if the second point lies along a line
				;; from the first to the third:
				;;   slope1 = slope2
				;;   <=> (x1-x2)    (x1-x3)
				;;       -------  = -------
				;;       (y1-y2)    (y1-y3)
				;;   <=> (y1-y3)(x1-x2) = (x1-x3)(y1-y2)
				(=r (*r (-r y1-scaled y3-scaled?)
					(-r x1-scaled x2-scaled))
				    (*r (-r x1-scaled x3-scaled?)
					(-r y1-scaled y2-scaled)))))
			 ;; straight oblique lines
			 (setq x2-scaled x1-scaled)
			 (setq y2-scaled y1-scaled)
			 nil)
			(t
			 (paint-graph-line-in-current-scratchpad-raster
			   x1-scaled y1-scaled x2-scaled y2-scaled
			   graph-line-color-value shading?
			   scaled-line-width?)
			 t))
		      into number-of-actual-paints	; counting for development; see below
		    while (cddr remaining-points)
		    finally
;		      #+development		; uncomment to see if (how much) this helps
;		      (if (<f number-of-actual-paints (-f (length points) 1))
;			  (format t "~%~d/~d points drawn (~4f%)"
;				  number-of-actual-paints
;				  (-f (length points) 1)
;				  (if (=f number-of-actual-paints 0)
;				      0
;				      (* 100
;					 (/ (float number-of-actual-paints)
;					    (-f (length points) 1))))))
		      ))
	     ((solid-rectangle clear-solid-rectangle)
	      (let* ((left-edge-in-window 
		       (delta-x-in-window (first (first points)) x-scale))
		     (top-edge-in-window 
		       (delta-y-in-window (second (first points)) y-scale))
		     (right-edge-in-window 
		       (delta-x-in-window (first (second points)) x-scale))
		     (bottom-edge-in-window 
		       (delta-y-in-window (second (second points)) y-scale)))
		(paint-solid-rectangle-in-current-scratchpad-raster
		  left-edge-in-window top-edge-in-window
		  (if (eq description-command 'solid-rectangle)
		      (maxr right-edge-in-window (+r left-edge-in-window 1))
		      right-edge-in-window)
		  (if (eq description-command 'solid-rectangle)
		      (maxr bottom-edge-in-window (+r top-edge-in-window 1))
		      bottom-edge-in-window)
		  (if (eq description-command 'solid-rectangle)
		      graph-line-color-value
		      graph-fill-color-value))))
	     (graph-marker
	      (paint-plot-marker
		(cdr description-element)
		graph-line-color-value x-scale y-scale))
	     (graph-dateline
	      (when first-time?
		;; dateline is not raster specific
		(update-graph-dateline
		  (delta-x-in-window (first (first points)) x-scale)
		  (delta-x-in-window (second (first points)) x-scale)
		  current-graph-rendering))	      
	      #+development			; I'd like to flush this mode to
						;   make this code simpler! (MHD 2/3/93)
	      (when debug-mode-for-ring-raster?
		(paint-solid-rectangle-in-current-scratchpad-raster
		  (delta-x-in-window
		    (erase-raster-dateline 
		      (graph-rendering-structure? current-graph-rendering)) x-scale)
		  (delta-y-in-window 0 y-scale)
		  (delta-x-in-window
		    (+w (erase-raster-dateline 
			  (graph-rendering-structure? current-graph-rendering)) 1)
		    x-scale)
		  (delta-y-in-window height y-scale)
		  graph-line-color-value)
		;; Note that this will not work for telewindows case.
		))
	     (data-extrema
	      (when (or (not burning?)		; do only once
			graph-rendering-uses-monochrome-raster-lists?
			)			; why not for monochrome?! (MHD 2/5/93)
		(loop as rest-of-rectangles = (first points)
					    then (nthcdr 4 rest-of-rectangles)
		      while rest-of-rectangles
		      do (update-graph-data-extrema
			   (delta-x-in-window (first rest-of-rectangles) x-scale)
			   (delta-y-in-window (second rest-of-rectangles) y-scale)
			   (+r (delta-x-in-window (third rest-of-rectangles) x-scale) 1)
			   (+r (delta-y-in-window (fourth rest-of-rectangles) y-scale) 1)))))
	     (graph-color-to-use
	      (cond
		((or graph-rendering-uses-polychrome-rasters?
		     graph-rendering-uses-monochrome-raster-lists?)
		 (setq graph-line-color-value 
		       (color-value-given-color-or-default
			 (second description-element))))
		(t
		 (if (not (eql (color-value-given-color-or-default
				 (second description-element))
			       foreground-color-value?))
		     (setq graph-line-color-value 0
			   burning? t)
		     (setq graph-line-color-value 1
			   burning? nil)))))
	     (graph-shading? (setq shading? (second description-element)))
	     (graph-line-width-to-use 
	      (setq scaled-line-width?
		    (if (second description-element)
			(delta-x-in-window
			  (second description-element)
			  x-scale))))		; what about y scale?
						; -- questionable! (MHD 2/3/93)
	     (chart-call-back
	      (project-chart-call-back current-graph-rendering foreground-color-value?))
	     (2d-call-back-full
	      (inner-full-paint-2d-grid foreground-color-value?))
	     (2d-call-back-partial
	      (inner-partial-paint-2d-grid foreground-color-value?))
	     )))




(defun get-marker-dimensions 
			(x y marker-size marker-half-size)
  (values (-w y marker-half-size) (+w y marker-half-size)
	  (-w x marker-size) (-w x marker-half-size)))

(defun paint-clipped-rectangle-in-current-scratchpad-raster
			(left-edge-in-window top-edge-in-window
			 right-edge-in-window bottom-edge-in-window color-value)
  (paint-solid-rectangle-in-current-scratchpad-raster
    (maxr left-edge-in-window 0) (maxr top-edge-in-window 0)
    (minr right-edge-in-window 
	  (width-of-graph-rendering-structure current-graph-rendering))
    (minr bottom-edge-in-window 
	  (height-of-graph-rendering-structure current-graph-rendering))
    color-value))

(defun paint-clipped-triangle-in-current-scratchpad-raster
       (x1 y1 x2 y2 x3 y3 color-value)
  (let ((clipped-bottom-edge
	  (minr y1 (height-of-graph-rendering-structure
		     current-graph-rendering))))
    y3						; gag compiler (MHD 10/29/89)
    (paint-filled-triangle-in-current-scratchpad-raster  
      (maxr x1 0) clipped-bottom-edge
      (maxr x2 0) (maxr y2 0)
      x3 clipped-bottom-edge
      color-value)))



(defun paint-shaded-line-in-current-scratchpad-raster
       (x1 y1 x2 y2 graph-line-color-value)
  (cond
    ((>r y1 y2)
     (paint-clipped-triangle-in-current-scratchpad-raster
       x1 y1 x2 y2 x2 y1 graph-line-color-value)
     (paint-clipped-rectangle-in-current-scratchpad-raster
       x1 y1 x2 (height-of-graph-rendering-structure current-graph-rendering)
       graph-line-color-value))
    (t
     (paint-clipped-triangle-in-current-scratchpad-raster
       x1 y2 x1 y1 x2 y2 graph-line-color-value)
     (paint-clipped-rectangle-in-current-scratchpad-raster
       x1 y2 x2 (height-of-graph-rendering-structure current-graph-rendering)
       graph-line-color-value))))



(defun point-not-on-graph? (y)
  (if (<r y 0) 
      0
      (let ((height
	      (height-of-graph-rendering-structure current-graph-rendering)))
	(if (>=r y height) height))))

;; Note that it is only necessary to check the y value since the x value will
;; always be on the graph.


(declare-forward-reference paint-nupec-plot-marker function)   ; graphs2



;;; Paint-plot-marker paints the marker centered on the y coordinate
;;; but completely to the left of the datapoint so that it will be
;;; completely drawn, even when scrolling.

(defun paint-plot-marker 
       (plot-marker-info graph-line-color-value	x-scale y-scale)
  (let* ((plot-marker (first plot-marker-info))
	 (x (second plot-marker-info))
	 (y (third plot-marker-info))
	 top bottom left middle-x)
    (when (not (point-not-on-graph? (delta-y-in-window y y-scale)))
      (case plot-marker
	(square
	 (multiple-value-setq
	   (top bottom left middle-x)
	   (get-marker-dimensions 
	     x y default-marker-size default-marker-half-size))
	 (paint-clipped-rectangle-in-current-scratchpad-raster
	   (delta-x-in-window left x-scale)
	   (delta-y-in-window top y-scale)
	   (delta-x-in-window x x-scale)
	   (delta-y-in-window bottom y-scale)
	   graph-line-color-value))
	((plus-sign star)
	 (multiple-value-setq
	   (top bottom left middle-x)
	   (get-marker-dimensions 
	     x y plus-sign-marker-size plus-sign-marker-half-size))
	 (paint-clipped-rectangle-in-current-scratchpad-raster
	   (delta-x-in-window (-w middle-x 2) x-scale)
	   (delta-y-in-window top y-scale)
	   (maxr (delta-x-in-window (+w middle-x 2) x-scale) 0)
	   (delta-y-in-window bottom y-scale)
	   graph-line-color-value)
	 (paint-clipped-rectangle-in-current-scratchpad-raster
	   (delta-x-in-window left x-scale)
	   (delta-y-in-window (-w y 2) y-scale)
	   (delta-x-in-window x x-scale)
	   (delta-y-in-window (+w y 2) y-scale)
	   graph-line-color-value))
	(triangle
	 (multiple-value-setq
	   (top bottom left middle-x)
	   (get-marker-dimensions 
	     x y default-marker-size default-marker-half-size))
	 (paint-clipped-triangle-in-current-scratchpad-raster
	   (delta-x-in-window left x-scale)
	   (delta-y-in-window bottom y-scale)
	   (delta-x-in-window middle-x x-scale)
	   (delta-y-in-window top y-scale)
	   (delta-x-in-window x x-scale)
	   (delta-y-in-window bottom y-scale)
	   graph-line-color-value))
	(t
	 ;; Removed test for nupec-authorized-p.  This type of change is needed
	 ;; to have non-NUPEC Telewindows work with NUPEC G2.  cpm, 8/21/91

	 ;; NUPEC plot marker
	 (paint-nupec-plot-marker 
	   plot-marker x y graph-line-color-value x-scale y-scale))
	))))




;;;; Headings and Labeling for Axis

(def-text-cell-format graph-heading-text-cell-format
		      text-cell-paragraph-indentation 0
		      minimum-format-width-for-text-cell 300)

(def-text-cell-format graph-horizontal-axis-heading-text-cell-format
		      text-cell-paragraph-indentation 0
		      text-cell-line-quadding? center
		      text-cell-top-margin 2
		      text-cell-bottom-margin 2
		      minimum-format-width-for-text-cell 300)

(def-text-cell-format graph-vertical-axis-heading-text-cell-format
		      text-cell-paragraph-indentation 0
		      minimum-format-width-for-text-cell 100)

(def-text-cell-format corner-empty-text-cell-format
		      text-cell-paragraph-indentation 0
		      minimum-format-width-for-text-cell 100)


(def-text-box-format graph-axis-label-format
  text-box-left-border-width 0
  text-box-top-border-width 0
  text-box-right-border-width 0
  text-box-bottom-border-width 0
  text-cell-left-margin 0
  text-cell-top-margin 0
  text-cell-right-margin 0
  text-cell-bottom-margin 0

  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 0
  text-cell-lines-justified? nil

  minimum-format-width-for-text-cell 440
  maximum-format-width-for-text-cell 440)



(defun make-graph-axis-label (text-line label-permanent? &optional background-color?)
  (let ((graph-axis-label
	  (make-free-text-box
	    text-line 'graph-axis-label)))
    (setf (label-permanent? graph-axis-label) label-permanent?)

    ;; Change of 9/22/92: We now put in the background color explicitly
    ;; into each label.  This eliminates the need to have a special
    ;; call to update images that binds the background color of the
    ;; graph; see put-up-new-high-value-label-for-horizontal-axis.
    ;; (MHD 9/22/92)
    (if background-color?
	(change-text-box-property
	  graph-axis-label 'background-color background-color?))
    graph-axis-label))

;; This should really create text boxes of type free-text, not of type text-box!
;; (MHD 7/25/88)



(defun make-graphs-opaque-1 ()
  (loop for graph being each class-instance of 'graph
	do (set-opaque-block graph)))

;; Called from post-loading function.  This is necessary because the
;; opaque-block flag is saved.




(def-class-method reformat-as-appropriate (graph superblock-will-do-reformatting?)
  (let ((graph-format-to-reformat-by?
	  (format-frame-to-reformat-by-if-any graph (graph-format graph))))
    (when graph-format-to-reformat-by?
      (let* ((graph-grid (get-graph-grid-given-graph graph))
	     (grid-width-delta
	       (-w (minimum-graph-width graph-format-to-reformat-by?)
		   (width-of-block graph-grid)))
	     (grid-height-delta
	       (-w (minimum-graph-height graph-format-to-reformat-by?)
		   (height-of-block graph-grid))))
	(with-temporary-gensym-float-creation reformat-graph
	  (let ((redraw-as-well-as-reformat-p nil))
	    (make-or-reformat-graph-grid 
	      nil graph-grid graph-format-to-reformat-by?
	      t t 0 0 grid-width-delta grid-height-delta)))
	(reformat-table-in-place graph))))
  (reformat-as-appropriate-for-table graph superblock-will-do-reformatting?))




;;;; Notes for 2.0

;; Ma:>agh>solid-block.kb has some large icons that are useful for testing
;; how a large bitblt looks on various machines.

;; Got rid of most of the special vars.  These were only used because of the
;; erase mechanism.  If there is ever a need for this again, do the erase from
;; a more low level structure rather than doing complete redraw.

;; Got rid of most of the axis specification slots in the class plot and in
;; the plot format frame.  These may be replaced at some point by axis
;; specification frames for separate axes.  One slot in the plot can then 
;; point to the appropriate axis specification.  This is a much better 
;; approach since it eliminates duplication of all this info for slots
;; on the same axes.

;; It seems that painting grid lines is about as fast as drawing them.  Good.

;; Graphic element memory is used to redraw things when something is exposed.

;; Strip charts are just another formatting option for graphs.  Bar charts are
;; something completely different.

;; Special workspaces that are painted could probably be used for a lot of 
;; other things besides graphs - maps, animation (hinge robot), scrolling
;; text.  Note that users will want to put things onto maps.  Thus, if 
;; something is dragged across a map, that section of the raster has to be
;; re-bitblt'ed.


;;; A note on scrolling -
;;; The scrolling mechanism in 2.0 greatly increases speed of scrolling (compared
;;; with 1.0, 1.11).  There is, however, some decrease in speed of putting up new
;;; data only, especially on machines with very slow bitblts (like the VAXes).
;;; The tradeoff is well worth it however since scrolling happens often if the
;;; graph is being updated frequently (and it is desireable to keep data along
;;; most or all of the horizontal axis).  If the graph is not being updated
;;; frequently, then speed is not so much of an issue in any case.




;;;; Speed Test Results


;; The following tests were performed on a TI Explorer I and were repeated at 
;; least twice to ensure consistency.


;; Old Graphs
;; Tested using "ma:>agh>old-graph-test.kb".


;;  scheduler    horizontal    number of   real time
;;  mode         axis format   graphs
;;  ----------   -----------   ---------   ---------
;;  as fast as   1 minute       1           15 sec. 
;;  possible
;;                             ---------   ---------
;;                              2           20 sec. 


;; The real time column indicates the amount of real time required for 100
;; seconds of gensym time.  For the 1 minute horizontal axis range format,
;; 3 complete reformats were done in the 100 second interval.


;; New Graphs
;; Tested using "ma:>agh>new-graph-test.kb".


;;  scheduler    horizontal    number of   real time
;;  mode         axis format   graphs
;;  ----------   -----------   ---------   ---------
;;  as fast as   1 minute       1           17 sec. 
;;  possible     strip chart
;;                             ---------   ---------
;;                              2           25 sec. 
;;
;;               scrolling     ---------   ---------
;;               extra 30%      1           11 sec.


;; Microsecond Performance Metering

;; A clearer picture of the above tests is obtained by metering using the
;; meter-microsecond-performance wrapper.  This was accomplished by 
;; merging "ma:>agh>new-graph-test.kb" with "ma:>agh>readout-benchmark.kb"
;; and deleting the readouts.

;; With one graph in strip chart mode with no extra scrolling (the first
;; test in the previous table) the following percentages result:

;; update-display-for-graph - 40%
;; make-or-reformat-graph-grid - 39%
;; cond form in make-or-reformat-graph-grid
;; that computes new format - 4.5%
;; erase before reformat - 8%
;; draw after reformat - 25%
;; draw-only-new-data-for-graph-grid - 23%
;; draw-data-for-plot - 1%
;; draw-graph-rendering - 20%
;; add-from-graph-rendering-to-current-window - 20%
;; add-from-graph-ring-raster-to-current-window - 18%
;; add-from-graph-ring-raster-to-current-window-1 - 17%

;; It is clear that draw and erase are taking much more time than computing
;; the new format and refreshing the plot data buffer.  Furthermore, within
;; the draw, it is clear most of the time is being spent in the bitblt.
;; Thus, a big improvement can be achieved by scrolling the axis by some
;; extra amount when it is scrolled.  This leaves some space so that the
;; next several updates will not require scrolling.  This means that for
;; these updates, much smaller bitblts can be used (since only a few datapoints
;; are being added and the raster is not being scrolled).  Test results 
;; for one graph in strip chart mode with various amounts of scrolling are 
;; as follows:

;;  extra scrolling space       percent time spent
;;  (as percentage of graph     doing bitblt
;;  width)
;;  -----------------------     ------------------
;;   0%                          17%
;;   3%                          7%
;;   5%                          4%
;;   10%                         2.5%
;;   30%                         1%

;; Thus, with 10% extra scrolling, for example, it is possible to all but 
;; eliminate the overhead from bitblt and still have the basic appearance
;; of a strip chart.  This almost doubles the speed of graph update.  In
;; the previous table showing speed results for new graphs, time went from
;; 17 seconds to just 11 seconds when scrolling 30%.  This is a significant
;; improvement considering that only 40% of the time is being spent updating
;; graphs.

;; Note that it is also possible to use the function histogram capability
;; on TI version 3.2 (currently on OK or TX).  To use this, just do 
;; System-P and click on function histograms.  This is like the 
;; microsecond metering facility.  Read up on this some more.


;; The small bitblt and improved erase results in significant performance
;; improvement.  Three graphs with 30% scrolling get to 100 seconds in
;; gensym time in only 16 seconds of real time.  Note that this is faster
;; than old graphs as well.  Microsecond metering results are now as 
;; follows: 

;; make-or-reformat-graph-grid - 39%
;; cond form in make-or-reformat-graph-grid
;; that computes new format - 11%
;; erase before reformat - 5%
;; draw after reformat - 19%
;; draw-only-new-data-for-graph-grid - 15%
;; draw-data-for-plot - 3%
;; draw-graph-rendering - 8%
;; add-from-graph-rendering-to-current-window - 6%

;; The next things to work on are draw-only-new-data-for-graph-grid, erase
;; and reformatting code.  It may be possible to squeeze these for some
;; extra performance!  


;; Tested three graphs with 30% scrolling, each graph showing three plots.
;; It only took 27 seconds of real time to get to 100 seconds in 
;; gensym time.  Thus, it seems it will be very easy to show many plots
;; on many graphs, especially if the update intervals are less than one 
;; second.  The same test using old graphs required 44 seconds of real
;; time to get to 100 seconds of gensym time.  Taking into account the
;; fact that only about 40% of the time is spent drawing graphs (as 
;; indicated from microsecond metering tests) indicates that the new graphs
;; are at least twice as fast, if not three times as fast, as old graphs.

;; Of course, the difference in speed between
;; old and new graphs is much less if the update intervals are longer since
;; in this case, only a very small percentage of time is spent updating
;; graphs.

;; Further tests to perform include:
;;   - test in real and simulated time modes
;;   - test with smaller graphs (new graphs only)
;;   - test with overlapping graphs 
;;   - test on other machines
;;   - Greg's benchmarks

;; One fun thing to do is to put the attribute table for the graph to the
;; side of the graph and change the scrolling percentage while the graph
;; is running.  Neat demo.

;; As each bottleneck is eliminated, the remaining ones will be
;; highlighted.  Speed improvement is thus a process of whittling
;; down each bottleneck as much as possible until no more improvements
;; are possible.


;; Comments 
;; There are a few important points to remember about the above tests.
;; The new graphs were tested in strip chart mode and the old graphs were not.
;; Attempting a strip chart mode with old graphs would be impossibly slow.  In
;; any case, the perception of speed is much better with new graphs since
;; everything comes up pretty much at once.  Also, the new graphs look better.


;; Ultimate Goal
;; Given that graphs (and displays in general) do not have to be updated more
;; than once a second or so (due to human response time), and due to the fact
;; that only a limited number of graphs can be displayed on a screen at once
;; (due to limited screen size), it should be possible to define some percentage
;; P of overall processing time which will not be exceeded no matter what the
;; user does.  In other words, no matter how many graphs the user puts up, they
;; will never take more than P percentage of the processing time.  This goal is
;; complicated by the fact that graphs can be scaled and overlapped.



;; Notes on Icons and TELEWINDOWS

;; G2 side                                           Telewindows side
;; -------                                           ----------------

;; draw-icon-rendering
;;  draw-graphic-element
;;   project-graphic-element
;;    project-graphic-element
;;           -without-image-plane-occlusion
;;     project-graphic-element-to-current-window
;;      add-from-icon-rendering-to-current-window
;;       send-icp-begin-making-icon-rendering ---->  handle-icp-begin-making-icon-rendering
;;       make-rendering-structure
;;        paint-one-color-of-icon
;;                 -on-scratchpad-raster
;;         (calls icp functions for lines,    ---->    handle-icp-messages
;;          arcs, etc.)                                  (actually draws on scratchpad raster)
;;
;;       send icp args for
;;       add-from-icon-rendering-to-...       ---->  handle-icp-add-from-icon-rendering...
;;                                                     (rendering-structure? slot is already
;;                                                      set at this point (it has been set
;;                                                      by the above code))
;;                                                     add-from-stored-raster-to-current-window

;; Send-icp-begin-making-icon-rendering is called due to the fact that 
;; icon-rendering is an icp object type and is being passed as an
;; argument to add-from-icon-rendering-to-current-window.  As can be
;; seen from the def-icp-object-type for icon-rendering, 
;; send-icp-begin-making-icon-rendering is called first to make the 
;; icon-rendering on the telewindows side, after which, 
;; make-rendering-structure is called to cause the scratchpad raster
;; to be painted.  See also def-icp-message-type for 
;; begin-making-icon-rendering.

;; Note that it is the call to make-rendering-structure on the G2 side
;; that causes the line drawing description to be sent to the 
;; Telewindows side.  Note also that this is called only once,
;; when add-from-icon-rendering-to-current-window is called for the
;; first time for the icon rendering.  After that, the raster doesn't
;; change.  This is different from graphs where it is necessary to
;; repaint the raster in some way for each update.



;;;; Useful Tests

;;; In directory "ma:>agh>":
;;; graph-decaching-test.kb, flow.kb
;;; tw-test, tw-test2, tw-test3

;;; Graph sine and make sure that not jagged.  Make sure that simulation time
;;; increment is not < 1 second as this can cause history values to be re-written
;;; causing the graph to look jagged.

;;; To test that not missing any data points,
;;; - use graph on flowsheet1 in tw-test3.kb
;;; - graph sine
;;; - make horizontal range
;;;     1 minute (make sure sine is not jagged)
;;;     10 minutes  (make sure that no peaks are missed)
;;;     1 hour
;;; - also vary update interval




;;;; Memory Test Functions

#+development
(defun check-graph-conses ()
  (loop with valid-graph-conses = 0
	with number-of-graphs-without-graph-renderings = 0
	with number-of-plots-without-data = 0
	for graph being each class-instance of 'graph
	as graph-grid = (first-subblock graph)
	do
    (setq valid-graph-conses
	  (+f valid-graph-conses
	      (count-cons (line-drawing-description-for-graph-grid? graph-grid))
	      (length (new-scrolled-vertical-grid-line-positions graph-grid))
	      (length (currently-up-to-date-image-planes graph-grid))))
    (if (graph-renderings graph-grid)
	(setq valid-graph-conses
	      (+f valid-graph-conses
		  (length (color-values-for-rasters?
			    (car (graph-renderings graph-grid))))))
	(setq number-of-graphs-without-graph-renderings
	      (+f number-of-graphs-without-graph-renderings 1)))
    (loop for plot in (list-of-plots graph-grid)
	  as data-buffer = (data-buffer-for-plot plot)
	  do
      (if data-buffer
	  (setq valid-graph-conses
		(+f valid-graph-conses
		    (length (plot-marker-indices data-buffer))))
	  (setq number-of-plots-without-data 
		(+f number-of-plots-without-data 1))))
	finally
	  (let ((pool-outstanding-graph-conses 
		  (pool-entry-outstanding-object-count
		    (assq 'graph-conses object-pool-meters))))
	    (return (values valid-graph-conses
			    (-f pool-outstanding-graph-conses
				valid-graph-conses)
			    number-of-graphs-without-graph-renderings
			    number-of-plots-without-data)))))



#+development
(defun count-cons (tree)
  (loop with cons-count = 0
	for element in tree do
    (if (consp element)
	(setq cons-count
	      (+ cons-count (count-cons element))))
    (setq cons-count 
	  (+ cons-count 1))
	finally
	  (return cons-count)))



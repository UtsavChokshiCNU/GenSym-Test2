;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module CHARTS1

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.
;;; Author: Ben Hyde






;;;; Forward References


(declare-forward-reference parse-text-string function)
(declare-forward-reference send-ws-representations-item-moved function)
(declare-forward-reference in-suspend-resume-p variable)
#+development
(declare-forward-reference check-memory function)





;;;; Chart Drawing Bottleneck



;;; All drawing in the module is currently done via the routines given here.
;;; Together they allow us to change our minds about how to render these
;;; charts.

;;; All coordinates given to these routines are in device coordinates.
;;; All scalling is the responsibility of the callers.  Since charts are very
;;; sophisticated about transformation, the workspace scale transformations
;;; are folded in to the transforms done to support mapping the user's data.

;;; A mess of global state parameterizes the individual drawing actions.
;;; For example chart-pen-x and chart-pen-y are the current default
;;; location from which any line segment is added.  As chart rendering
;;; proceeds the part description is interpreted to set the state in
;;; the of a formatted part.  Only the line color is then moved over into
;;; the chart drawing state.

;;; One source of confusion here is that historically the slot text-cell-line-color?
;;; has been used to specify the text color rather than the line color.  That
;;; is true here and the global formatted-part-true-line-color is used
;;; to hold the color the user requests as via line-color.

;;; Charts are actually drawing into the current scratch pad raster.  This
;;; raster comes in one of two flavors: monochrome and polychrome.

;;; Monochrome rasters are constructed of N bit maps, one
;;; for each color.  These are all one bit deep, zero implies
;;; transparent.  To draw in a particular color we have to draw in the
;;; raster appropriate for that color.  We also have to burn a hole thru
;;; the rasters above that raster so the color will show thru.

;;; That is, of course, amazingly inefficent.

;;; Polychrome rasters are constructed of one bit map, with sufficent bits
;;; to represent the colors needed in the chart and to assure they can
;;; be BLITed to the screen efficently.  At this time (5/9/92) the only
;;; use of polychrome rasters is during printing.

;;; The routine project-chart-call-back far below is called once for each layer.  It
;;; binds the desired color into `current-chart-raster-color-value' and then these
;;; drawing operations decide to erase or paint by consulting its value.

;;; The complexity of supporting two flavors of rasters is encapsulated in
;;; these variables of the dynamic state.
;;; We bind on entry to the dynamic extent `chart-current-raster-is-polychrome-p'
;;; so we know which mode we are drawing in.  Then when ever `chart-pen-color' is
;;; set we derive a `current-chart-raster-color-value.'  If we are drawing a
;;; polychrome raster then we will draw in the color value implied by `color-value'
;;; i.e. the `chart-pen-color-value.'   If we are drawing one layer of the monochrome
;;; bitmap then we will derive a zero/erase or one/draw value by considering
;;; `chart-color-value-for-this-raster.'


(def-named-dynamic-extent chart-drawing
  (module charts))

(defvar-of-named-dynamic-extent chart-pen-x 			 chart-drawing)
(defvar-of-named-dynamic-extent chart-pen-y 			 chart-drawing)
(defvar-of-named-dynamic-extent chart-pen-color 		 chart-drawing)
(defvar-of-named-dynamic-extent chart-pen-color-value 		 chart-drawing)
(defvar-of-named-dynamic-extent chart-really-drawing 		 chart-drawing)
(defvar-of-named-dynamic-extent current-chart-raster-color-value chart-drawing)
(defvar-of-named-dynamic-extent chart-current-raster-is-polychrome-p chart-drawing)
(defvar-of-named-dynamic-extent chart-current-raster-is-monochrome-raster-list-p
				chart-drawing)	; (MHD 2/5/93)
(defvar-of-named-dynamic-extent chart-color-value-for-this-raster chart-drawing)

(defmacro synchronize-color-value-for-this-raster ()
  `(setf chart-color-value-for-this-raster
	(cond
	  ((or chart-current-raster-is-monochrome-raster-list-p	; (MHD 2/5/93)
	       chart-current-raster-is-polychrome-p)
	   chart-pen-color-value)
	  ((=f current-chart-raster-color-value chart-pen-color-value) 
	   1)
	  (t
	   0))))


(defmacro with-chart-drawing (&body body)
  `(with-named-dynamic-extent* chart-drawing
			       ((chart-really-drawing T)
				(chart-current-raster-is-polychrome-p 
				  (graph-rendering-uses-polychrome-rasters?
				    current-graph-rendering))
				(chart-current-raster-is-monochrome-raster-list-p 
				  (graph-rendering-uses-monochrome-raster-lists?
				    current-graph-rendering))	; (MHD 2/5/93)
				(chart-pen-x 0)
				(chart-pen-y 0)
				; (color 'black)
				(chart-pen-color 'black)
				(chart-pen-color-value (if chart-really-drawing 
							   (map-to-color-value 'black)
							   0)))
     (synchronize-color-value-for-this-raster)
     (progn ,@body)))

(defmacro with-simulated-chart-drawing (&body body)
  `(with-named-dynamic-extent* chart-drawing
			       ((chart-really-drawing nil)
				(chart-pen-x 0)
				(chart-pen-y 0)
				; (color 'black)
				(chart-pen-color 'black)
				(chart-pen-color-value (if chart-really-drawing 
							   (map-to-color-value 'black)
							   0)))
     (progn
       ,@body)))

(defun chart-pen-color (color)
  (unless (eql chart-pen-color color)
    (setf chart-pen-color color)
    (cond
      (chart-really-drawing
       (setf 
	 chart-pen-color-value 
	 (map-color-or-metacolor-to-color-value color))
       (synchronize-color-value-for-this-raster))
      (t
       (setf chart-pen-color-value 0)))))

(defmacro with-chart-pen-color (color &body body)
  (let ((old-color '#:old-color))
    `(let ((,old-color chart-pen-color))
       (chart-pen-color (or ,color ,old-color))
       ,@body
       (chart-pen-color ,old-color))))

(defun chart-move-to (x y)
  (setf chart-pen-x x)
  (setf chart-pen-y y))

(defun chart-line-to (x y)
  (macrolet ((pin (x) `(pin-in-rangef -65534 ,x 65534)))
    (paint-line-in-current-scratchpad-raster
      (pin chart-pen-x)
      (pin chart-pen-y)
      (pin x)
      (pin y)
      chart-color-value-for-this-raster
      T)
    (setf chart-pen-x x)
    (setf chart-pen-y y)))

(defun chart-move (dx dy)
  (chart-move-to 
    (+f chart-pen-x dx)
    (+f chart-pen-y dy)))

(defun chart-line (dx dy)
  (chart-line-to 
    (+f chart-pen-x dx)
    (+f chart-pen-y dy)))

(defmacro without-updating-chart-point (&body body)
  (let ((pen-x '#:pen-x)
	(pen-y '#:pen-y))
    `(let ((,pen-x chart-pen-x)
	   (,pen-y chart-pen-y))
       ,@body
       (setq chart-pen-x ,pen-x
	     chart-pen-y ,pen-y))))

(defun chart-fill-rectangle (left top right bottom)
  (macrolet ((pin (x) `(pin-in-rangef -65534 ,x 65534)))
    (when (=r top bottom)
      (setf bottom (+f 1 top)))
    (when (=r left right)
      (setf right (+f 1 left)))
    (paint-solid-rectangle-in-current-scratchpad-raster
      (pin left) (pin top)
      (pin right) (pin bottom)
      chart-color-value-for-this-raster)))

(defun chart-frame-rectangle (left top right bottom)
  (decfr right)
  (decfr bottom)
  (when (=r top bottom)
    (setf bottom (+f 1 top)))
  (when (=r left right)
    (setf right (+f 1 left)))
  (chart-move-to left top)
  (chart-line-to right top)
  (chart-line-to right bottom)
  (chart-line-to left bottom)
  (chart-line-to left top))



;;; The pixel width of this text string in the this current
;;; window.  This works only on hm14, with word spacing 10.

(defun chart-text-width (text-string)
  (let ((font-map (text-cell-font-map current-text-box-format))
	(word-spacing (default-word-spacing current-text-box-format)))
    (delta-x-in-window
      (compute-width-of-text-line text-string nil nil font-map word-spacing)
      current-image-x-scale)))


;;; Computes a bounding rectangle that will enclose a piece of 
;;; text. Returns the rectangle as (values left top right bottom).
;;; The text should start drawing at 0 0 in this rectangle.

(defun compute-bounding-rectangle-of-text (text)
  (let ((text-cell-line-height 
	  (text-cell-line-height current-text-box-format))
	(text-cell-baseline-position
	  (text-cell-baseline-position current-text-box-format)))
    (values 
      0
      (delta-y-in-window
	(-f text-cell-line-height)
	current-image-y-scale)
      (chart-text-width text)
      (delta-y-in-window 
	(-f text-cell-line-height text-cell-baseline-position)
	current-image-y-scale))))

;; MHD's notes:
;;
;;   * TEXT should be TEXT-LINE, or at least TEXT-STRING.
;;   * -f should be -w
;;   * This expects to be called in a for-image-plane context
;;     just so current-image-y-scale are bound so that it can
;;     return its values in window coordinates (with origin
;;     in upper, left corner)
;;   * This also expects to be called in whatever context binds
;;     current-text-box-format, just so it can dig up the parameters
;;     in there needed for figuring out facts about the font
;;   * Its subfunction, chart-text-width, does the the call to
;;     compute-width-of-text-box, which works in terms of workspace
;;     coordinates, and then transforms the answer into window
;;     coordinates
;;   * This and the subfunction should take start and end index
;;     args, at least, in order to support computing width of partial
;;     text lines
;;   * They should also ultimately take search arguments for efficiency's
;;     sake, in order to allow combining search with accumulation of
;;     width, but that goes beyond compute-width-of-text-line's capability
;;     at the moment
;;   * Perhaps they should just take a font, rather than a format; note
;;     that the formats have relatively unreliable information about font
;;     bounding boxes; I'm not sure the fonts themselves have completely
;;     correct information in that regard either
;;   * for sure, the code that implements compute-width-of-text-line
;;     could be easily modified to accumulate the vertical upper and
;;     lower bounds (i.e., the height) of at least the characters present
;;     then a function that computes the exact bounds (in workspace
;;     coordinates) could be made from that
;;     
;;
;; (MHD 2/20/92)


;;; Draw text, starting from current pen location.

(defun chart-draw-text (text-string)
  (let ((text-cell-font-map (text-cell-font-map current-text-box-format))
	(word-spacing (default-word-spacing current-text-box-format))
	chart-pen-color
	chart-pen-color-value
	chart-color-value-for-this-raster)
    (chart-pen-color (text-cell-line-color? current-text-box-format))
    (multiple-value-bind (left top right bottom)
	(compute-bounding-rectangle-of-text text-string)
      ;; Offset that rectangle to the pen position.
      (incff  left  chart-pen-x)
      (incff  top   chart-pen-y)
      (incff right  chart-pen-x)
      (incff bottom chart-pen-y)
      ;; Now paint it.
      (paint-from-line-of-text-to-current-scratchpad-raster
	left top right bottom 
	text-string word-spacing text-cell-font-map
	chart-color-value-for-this-raster
	current-image-x-scale current-image-y-scale
	chart-pen-x chart-pen-y))))

;; Apparently we don't have the actual raster's dimensions available in
;; the dynamic state at this point, so I had to reach up into the dynamic 
;; state of the chart.  This will be real bad if and when I have another
;; user of this code.





;;;; Without-frame-notes-asserted, A Wrapper.




;;; An abstraction for establishing a dynamic extent during which there are
;;; no frame notes for a block.

;;; `Retract-frame-notes' and `assert-frame-notes' are responsible for
;;; to just that. They should call their superior methods.  The ones
;;; on block do nothing.  These methods should not assert and retract
;;; the consistency analysis.

(def-class-method retract-frame-notes (block)
  (declare (ignore block)))

(def-class-method assert-frame-notes (block)
  (declare (ignore block)))



;;; `Without-frame-notes-asserted' returns only one value. During the body
;;; the frame notes of the block are removed, and then they are recomputed.
;;; The two methods retract-frame-notes and assert-frame-notes are used
;;; to do that.

(defmacro without-frame-notes-asserted ((block) &body body)
  (avoiding-variable-capture (block)
    `(progn
       (funcall-method 'retract-frame-notes ,block)
       (prog1
	 (progn 
	   ,@body)
	 (funcall-method 'assert-frame-notes ,block)))))






;;;; Generator operations for spinning out the elements of a managed-float-array



(def-list-structure (managed-float-array-generator 
		      (:consing-function slot-value-cons-function))
		    (managed-float-array-generator-array . managed-float-array-generator-next-element-index))

(defun managed-float-array-generator-open (managed-float-array) ; -> generator
  (make-managed-float-array-generator managed-float-array 0))

(defun managed-float-array-generator-next-element (generator)
  (let ((index (managed-float-array-generator-next-element-index generator)))
    (setf 
      (managed-float-array-generator-next-element-index generator) 
      (+f index 1))
    (managed-float-aref 
      (managed-float-array-generator-array generator)
      index)))

(defun managed-float-array-generator-eof (generator)
  (<=f (managed-float-array-length 
	 (managed-float-array-generator-array
	   generator))
       (managed-float-array-generator-next-element-index generator)))

(defun managed-float-array-generator-close (generator)
  (reclaim-slot-value-cons generator))







;;;; Transformation matrix mechinisms.



;;; Transformations are stored in a manner identical to that
;;; used in Postscript.  The transform is a matrix:
;;;   | a  b  0.0 |
;;;   | c  d  0.0 |
;;;   | tx ty 1.0 |
;;; an that matrix is stored in a simple vector as so:
;;;   #(a b c d tx ty)
;;; This encoding of the matrix is actually private, only
;;; the following few routines actually know about it.  So we don't
;;; provide a mess of accessors for this encoding, since we
;;; don't want other people accessing them directly.

;;; All operations on the transform manipulate the current
;;; transform, which is kept in `the-transform'.

;;; This doesn't need to be process specific since it is only used
;;; in the dynamic scope of the nonresumable function project-chart.

(def-system-variable the-transform CHARTS1 (:funcall initialize-the-transform)) ; element type is managed-value

(defun initialize-the-transform ()
  (let ((result 
	  (with-permanent-array-creation
	    (make-array 6))))
    (with-temporary-gensym-float-creation initialize-the-transform
      (setf the-transform result)
      (indentity-transform-matrix))
    result))

(defmacro the-transform-a  () `(svref the-transform 0))
(defmacro the-transform-b  () `(svref the-transform 1))
(defmacro the-transform-c  () `(svref the-transform 2))
(defmacro the-transform-d  () `(svref the-transform 3))
(defmacro the-transform-tx () `(svref the-transform 4))
(defmacro the-transform-ty () `(svref the-transform 5))


#+development
(defun check-the-transform ()
  (unless (and (managed-float-p (the-transform-a))
	       (managed-float-p (the-transform-b))
	       (managed-float-p (the-transform-c))
	       (managed-float-p (the-transform-d))
	       (managed-float-p (the-transform-tx))
	       (managed-float-p (the-transform-ty)))
    (error "The-transform is malformed.")))

#+development ; see also `show-transform'
(defun describe-the-transform ()
  (format t "~%[ X ]   [ ~8E  ~8E ] [ x ]   [~8E]~
	     ~%|   | = |                    | |   | + |        |~
	     ~%[ Y ]   [ ~8E  ~8E ] [ y ]   [~8E]"
	  (extract-cached-number (the-transform-a))
	  (extract-cached-number (the-transform-c))
	  (extract-cached-number (the-transform-tx))
	  (extract-cached-number (the-transform-b))
	  (extract-cached-number (the-transform-d))
	  (extract-cached-number (the-transform-ty))))

;;; `Set-after-translation-via-transform-matrix' is a macro.  It deposits 
;;; into the places destination-x and destination-y, the result of translating
;;; source-x and source-y according to the transform matrix.  It is
;;; the equivalent of the postscript operation TRANSLATE.

;;; Must be called within a with-temporary-gensym-float-creation.

(defmacro set-after-translation-via-transform-matrix (destination-x destination-y source-x source-y
						      &optional round-p)
  (let ((new-x '(+e (*e a t1) (*e c t2) tx))
	(new-y '(+e (*e b t1) (*e d t2) ty)))

    (when round-p
      (setq new-x `(floore-first ,new-x)
	    new-y `(floore-first ,new-y)))

    `(let ((a  (extract-cached-number (the-transform-a)))
	   (b  (extract-cached-number (the-transform-b)))
	   (c  (extract-cached-number (the-transform-c)))
	   (d  (extract-cached-number (the-transform-d)))
	   (tx (extract-cached-number (the-transform-tx)))
	   (ty (extract-cached-number (the-transform-ty)))
	   (t1 ,source-x)
	   (t2 ,source-y))
       #+development
       (assert (and (floatp a)
		    (floatp b)
		    (floatp c)
		    (floatp d)
		    (floatp tx)
		    (floatp ty)
		    (floatp t1)
		    (floatp t1)))
       (assert-that-within-temporary-float-scope)
       (setf ,destination-x ,new-x)
       (setf ,destination-y ,new-y))))



;;; `Indentity-transform-matrix' sets the transform to the
;;; indentity matrix.

  
(defun indentity-transform-matrix ()
  (assert-that-within-temporary-float-scope)
  ;; Note that `store-managed-number' will mutate managed floats
  (store-managed-number (the-transform-a)  1.0)
  (store-managed-number (the-transform-b)  0.0)
  (store-managed-number (the-transform-c)  0.0)
  (store-managed-number (the-transform-d)  1.0)
  (store-managed-number (the-transform-tx) 0.0)
  (store-managed-number (the-transform-ty) 0.0))



;;; `Scale-transform-matrix' scales the current transform matrix.
;;; The equivalent of the postscript operator SCALE.

(defun scale-transform-matrix (x-scale y-scale)
  (assert-that-within-temporary-float-scope)
  (let ((a (extract-cached-number (the-transform-a)))
	(b (extract-cached-number (the-transform-b)))
	(c (extract-cached-number (the-transform-c)))
	(d (extract-cached-number (the-transform-d))))
    ;; Note that `store-managed-number' will mutate managed floats
    (store-managed-number (the-transform-a) (*e x-scale a))
    (store-managed-number (the-transform-b) (*e x-scale b))
    (store-managed-number (the-transform-c) (*e y-scale c))
    (store-managed-number (the-transform-d) (*e y-scale d))))

;;; `Offset-transform-matrix' offsets the transform matrix, it is the
;;; equivalent of the postscript operator TRANSFORM.

(defun offset-transform-matrix (x-offset y-offset)
  (assert-that-within-temporary-float-scope)
  (let ((a  (extract-cached-number (the-transform-a)))
	(b  (extract-cached-number (the-transform-b)))
	(c  (extract-cached-number (the-transform-c)))
	(d  (extract-cached-number (the-transform-d)))
	(tx (extract-cached-number (the-transform-tx)))
	(ty (extract-cached-number (the-transform-ty))))
    ;; Note that `store-managed-number' will mutate managed floats
    (store-managed-number
      (the-transform-tx)
      (+e (*e a x-offset)
	  (*e c y-offset)
	  tx))
    (store-managed-number
      (the-transform-ty)
      (+e (*e b x-offset)
	  (*e d y-offset)
	  ty))))







;;;; Defining the set of chart styles.



;;; `Chart-part-description-for-chart-style' is a global property name used
;;; to assocate the user's name for a chart style with the part description
;;; that provides the default behavor required for that chart style.



(def-global-property-name chart-part-description-for-chart-style)

(defmacro define-chart-style (name description)
  (unless (search "CHART-STYLE" (symbol-name name))
    (warn "~S: chart styles should include the phrase \"chart-style\" in their name" name))
  `(progn
     (setf (chart-part-description-for-chart-style ',name)
	   ,description)))







;;;; The Class Chart


;;; A `chart' is a kind of block used to draw a wide range of 
;;; x-y plots.

(def-class (chart (item block) (foundation-class chart))
  
  ;; Revisions to default behavor of the slots of the ancestors.
  (frame-flags #.opaque-block-flag)
  
  ;; Internal state of the chart, see notes below.
  (graph-renderings-for-chart nil system vector-slot)
  (line-drawing-description-for-chart 
    ((graph) (chart-call-back))
    system 
    vector-slot
    do-not-save)
  (chart-initial-update-task? nil system vector-slot do-not-save)
  (computed-annotations nil do-not-save system)
  
  ;; The user visible slots of the chart.
  (chart-style nil (type chart-style) vector-slot system user-overridable); a symbol
  (data-series nil (type data-series-descriptions) vector-slot system
	       user-overridable)	; slot-vlaue cons pool.
  (annotations nil (type chart-annotations) vector-slot system
	       user-overridable)	; Slot-value cons pool.
  
  )

;;; The `graph-renderings-for-chart' is managed entirely by routines
;;; provided by the graphs.

;;; The `line-drawing-description-for-chart' is given an initial value.
;;; It is never changed!  So it is never reclaimed, which is good since
;;; that is a constant list and it would go back into the slot-value
;;; cons pool.  The do-not-save slot-feature is redundant since it would
;;; never get saved, being EQ to the default value.

;;; `Chart-initial-update-task?' is used to hold any update task associated
;;; with this chart.  Currently the only such task is the one spawned when
;;; the chart is activated.

;;; The `computed-annotations' slot of a chart is built from slot-value conses.
;;; it is used to cache data about the chart.  For example it is used to cache
;;; a full description of each chart axis.

;;; The `chart-style' slot is a symbol whose value contains a chart part description
;;; for the chart in this style containing the default layout information.  This
;;; is initially nil until patched by the class initialization method.  That provides
;;; a way to tell if the frame was cloned, or is actually really fresh.

;;; The `data-series' slot is a list of data-series part descriptions.  This slot may
;;; contain the names of other frames.

;;; The `annotations' slot is a chart part description giving changes requested by the user
;;; to the defaults provided by the chart-style.

;;; The parameters `default-chart-width' and `default-chart-height' give the
;;; default width and height, respectively, for a new chart.

(defparameter default-chart-height 200)
(defparameter default-chart-width  300)

;;; `Initialize, a method upon a chart', initializes the chart's
;;; frame notes, and name registrations.

(def-class-method initialize (chart)
  (funcall-superior-method chart)
  ;; Chart-style is now a user-overridable system slot, so we now must be sure
  ;; to set the edges when we initialize even though there is a chart-style.
  ;; (ghw 1/9/96)
  (unless (chart-style chart) 
    (setf (chart-style chart) 'line-chart-style))
  (when (=f (right-edge-of-block chart) 0)
    (set-edges-of-block chart 0 0 default-chart-width default-chart-height))
  (funcall-method-if-any 'assert-frame-notes chart))


;;; This exists in order to bring up to date any charts which still use the old
;;; naming scheme for text-sizes.

(def-class-method initialize-after-reading (chart)
  (funcall-superior-method chart)		; needed by convention
  (unless (standardized-part-text-sizes-p)
    (map-over-part-description 'standardize-text-size-feature-in-part-description
			       (annotations chart))
    (map-over-part-description 'standardize-text-size-feature-in-part-description
			       (computed-annotations chart))))


(def-spot chart-spot
    :slots nil ;; someday...
    :include spot
    :enclosing-spot-type image-plane-spot
    :innermost-spot-p t
    :abstract-type nil
    :type-of-frame-represented chart)

(def-class-method generate-spot (chart mouse-pointer)
  (push-last-spot mouse-pointer (make-chart-spot) chart))

;;; `Assure-all-charts-are-modern-1' is called by a post loading function
;;; since there was a time when the default for a chart's style was different.
;;; It also slams all instances of color into line-color 
;;; in the part descriptions.

(defun assure-all-charts-are-modern-1 ()
  (loop for chart being class-instances of 'chart
	do
    (unless (chart-part-description-for-chart-style (chart-style chart))
      (setf (chart-style chart) 'line-chart-style))
    (map-over-part-description 'fix-up-color-feature-in-chart-part-description (annotations chart))
    (map-over-part-description 'fix-up-color-feature-in-chart-part-description (computed-annotations chart))))

(defun fix-up-color-feature-in-chart-part-description (part-description)
  (loop for p on (rest part-description) by #'cddr
	do
    (when (eq 'color (car p))
      (setf (car p) 'line-color))))


;;; `Cleanup, a method on a chart', clears those slots that contain names
;;; in the chart, that triggers the reclaimation of their associated names.

(def-class-method cleanup (chart)
  (funcall-superior-method chart)
  (change-slot-value chart 'data-series nil))



;;; `Line-drawing-description-for-chart, the slot reclaimer,' does nothing.
;;; This slot is always EQ to the default, except in the very unusual case
;;; that the class definition has been recompiled.  In that case reclaiming
;;; the slot would attempt to reclaim read only data structures.  To avoid
;;; that sad event we define this do nothing slot reclaimer.

(def-slot-value-reclaimer line-drawing-description-for-chart (old-slot-value)
  (declare (ignore old-slot-value))
  nil)

;; If default size changed you should update code near change-size-of-chart
;; also.  -- UPDATE: no longer necessary, since these use the parameters
;; default-chart-width/height now, as does the change-size method in FACILITIES.
;; (MHD 5/12/95)


(def-named-dynamic-extent working-on-chart
  (module charts))

(defvar-of-named-dynamic-extent current-chart-frame working-on-chart)







;;;; Utilities to Manage the Graph Renderings of a Chart




;;; Remove-graph-rendering-from-chart simply removes graph-rendering as an
;;; element of the graph-renderings-for-chart slot of chart.  This is just
;;; called by remove-graph-rendering-from-graph-grid (GRAPHS1).

(defun remove-graph-rendering-from-chart (graph-rendering chart)
  (setf (graph-renderings-for-chart chart)
	(delete-eval-element
	  graph-rendering (graph-renderings-for-chart chart))))



;;; 'Get-or-make-graph-rendering-for-chart' ...


(defun get-or-make-graph-rendering-for-chart (chart)
  (loop with current-chart-frame = chart
	for graph-rendering in (graph-renderings-for-chart chart)
	when (and (=f current-image-x-scale
		      (x-scale-of-graph-rendering graph-rendering))
		  (=f current-image-y-scale
		      (y-scale-of-graph-rendering graph-rendering))
		  (eq current-window
		      (window-for-graph-rendering graph-rendering)))
	  return
	    graph-rendering 		; decaching not done here
	finally
	  (return
	    (let* ((width-of-block  (width-of-block  chart))
		   (height-of-block (height-of-block chart))
		   (width-of-block-in-window
		     (delta-x-in-window
		       width-of-block current-image-x-scale))
		   (height-of-block-in-window
		     (delta-y-in-window
		       height-of-block current-image-y-scale))
		   (chart-colors (chart-colors))
		   (format-of-graph-rendering-structure
		    (choose-format-for-graph-rendering (length chart-colors)))
		   (graph-rendering
		     (make-decacheable-graph-rendering
		       (line-drawing-description-for-chart chart)
		       format-of-graph-rendering-structure
		       current-image-x-scale current-image-y-scale
		       0			; grid-border-width
		       width-of-block height-of-block
		       width-of-block-in-window height-of-block-in-window
		       chart current-window
		       (get-reference-to-item chart)
		       (maxr
			 width-of-block-in-window height-of-block-in-window))))
	      ;; initialize a few more required slots
	      (setf (color-values-for-rasters? graph-rendering)
		    chart-colors)
	      (setf (grid-background-color-value graph-rendering)
		    (map-color-or-metacolor-to-color-value 'white))
	      ;; paint into graph rendering
	      (let ((current-graph-rendering graph-rendering))
		(paint-graph-rendering-raster))
	      ;; store graph rendering
	      (setf (graph-renderings-for-chart chart)
		    (eval-cons
		      graph-rendering (graph-renderings-for-chart chart)))
  	      graph-rendering))))




;;;; The Grid Mixin




(def-part-type grid)

(def-part-feature (grid grid-color)
  (type color-or-metacolor)
  (user-visible t))

(def-part-feature (grid grid-visible)
  (type boolean)
  (user-visible t))

;;;; The Charting State Vector




;;; The chart is drawn into a rectangular area, 
;;; these are in workspace coordinates.

(def-part-type chart
  (includes formatted-part grid)
  (children-part-types axis data-series)
  (other-descendant-part-types chart-data-point)
  (hidden-features text-alignment height width))

(defvar data-series-subparts) ;; !!

(def-part-feature (chart chart-left)
  (type fixnum)
  (user-visible nil))
(def-part-feature (chart chart-top)
  (type fixnum)
  (user-visible nil))
(def-part-feature (chart chart-right)
  (type fixnum)
  (user-visible nil))
(def-part-feature (chart chart-bottom)
  (type fixnum)
  (user-visible nil))

(def-part-feature (chart chart-right-margin)
  (type fixnum)
  (user-visible nil))
(def-part-feature (chart chart-top-margin)
  (type fixnum)
  (user-visible nil))
(def-part-feature (chart chart-left-margin)
  (type fixnum)
  (user-visible nil))
(def-part-feature (chart chart-bottom-margin)
  (type fixnum)
  (user-visible nil))


;;; For the chart at large we compute some information about
;;; the range taken on by the data points.  These statistics
;;; are then used to guide computing automatic axis ranges.

(def-part-feature (chart chart-tuple-1-minimum)
  (type temporary-constant)
  (user-visible nil))

(def-part-feature (chart chart-tuple-1-maximum)
  (type temporary-constant)
  (user-visible nil))

(def-part-feature (chart chart-tuple-2-minimum)
  (type temporary-constant)
  (user-visible nil))

(def-part-feature (chart chart-tuple-2-maximum)
  (type temporary-constant)
  (user-visible nil))

;;; When we draw the axis we set these variables
;;; so that we will will know where the axis
;;; lines are.  These are used when drawing bar,
;;; column, or area charts.

(def-part-feature (chart chart-origin-x)
  (type fixnum)
  (user-visible nil))

(def-part-feature (chart chart-origin-y)
  (type fixnum)
  (user-visible nil))






;;;; State for Drawing the Data Series




;;; We scan over the data series that are in our chart.
;;; For the current data series we are scanning we keep
;;; a handfull of state that supports that scan.

(def-part-type data-series
  (includes formatted-part)
  (children-part-types axis chart-data-point)
  (hidden-features text-size
		   height
		   width
		   text-alignment
		   text-color
		   border-color
		   background-color))


(def-part-feature (data-series data-series-index)
  (type fixnum)
  (user-visible nil))


;;; The data-series-transform-index indentifies which transform
;;; matrix should be used to map this data onto into device
;;; coordinates.  This is necessary if you allow multiple
;;; charts with more than two axis.

;(def-part-feature (data-series data-series-transform-index)
;  (type fixnum))


;;; Data-series-info-{1,2} provided parameters the
;;; the data series generators.  The data-series-source-kind
;;; is used to record what kind of data series generator will
;;; process this information to create the stream of data points.
;;; Coming out of the parse a unique designation is usually found
;;; in these features.  This is then compiled, and if that fails
;;; a nil will be found in the feature.


;;; `Data-series-source-kind' records how to obtain the values of the
;;; data series.  For those data series residing in the data-series slot
;;; of a chart the values are specified in the RHSs of the grammar rules
;;; that parse that slot.  For the computed-annotation slot the legal
;;; values are each defined by a def-data-series-source-kind form.

(def-part-feature (data-series data-series-source-kind)
  (type symbol)  ;; (or ;; Something like this is closer.
                 ;;   ;; What the parser makes
                 ;;   (member one-g2-quantity-list pair-of-g2-quantity-lists)
                 ;;   ;; What the computed kinds are.
                 ;;   (member axis-data-series malformed-data-series float-and-float-from-data-caches))
  (user-visible nil))

(def-part-feature (data-series data-series-info-1)
  (user-visible nil))

(def-part-feature (data-series data-series-info-2)
  (user-visible nil))

;;; Data-series-failed-to-compile is T when compile-expression either
;;; returned NIL or returned a LET form indicating that local names were
;;; used in the expression.  When it is T then the data-series-info
;;; variables will contain a unique-designation parse, not a compiled
;;; expression.  In either case the contents of data-series-info is
;;; appropriate input to print-designation. 

(def-part-feature (data-series data-series-failed-to-compile)
  (user-visible nil)
  (type boolean))

(defun-simple managed-float-array?-p (x)
  (or (null x)
      (managed-float-array-p x)))

(deftype-simple managed-float-array? ()
  '(satisfies managed-float-array?-p))

(def-part-feature (data-series data-series-data-cache-1?)
  (user-visible nil)
  (type managed-float-array?))

(def-part-feature (data-series data-series-data-cache-2?)
  (user-visible nil)
  (type managed-float-array?))



;;; Data-series-illustration-kind contains a symbol that
;;; tells what class of illustration to use for the data
;;; series.

(def-part-feature (data-series data-series-illustration-kind)
  (type symbol)
  (user-visible nil))

;;; Data-series-generator-info-{1,2} are used to store temporaries
;;; needed by the generator as it scans over the elements of the
;;; data series.

(def-part-feature (data-series data-series-generator-info-1)
  (type T)
  (user-visible nil))

(def-part-feature (data-series data-series-generator-info-2)
  (type T)
  (user-visible nil))

(def-part-feature (data-series data-series-connect-first-and-last-point)
  (type boolean)
  user-visible
  (user-spelling line-from-last-to-first-point-visible))







;;;; State for Drawing the Data Points




;;; We scan over the points in the data series.  For
;;; Each point we visit in the chart we keep a handfull
;;; of state about that point.  Each point consists of
;;; a tuple, for example X value and a Y value.  In complex
;;; cases this tuple can be quite complex, for example a
;;; Gant chart with labels can have a slew of elements in
;;; each tuple.

(def-part-type chart-data-point
  (user-spelling data-point)
  (includes formatted-part)
  (allow-individual-exceptions-in-parents nil)
  (hidden-features border-color
		   background-color
		   border-thickness 
		   text-alginment
		   text-color
		   text-size))

(def-part-feature (chart-data-point data-point-index)
  (type fixnum)
  (user-visible nil))

;;; The tuple that describes a data point is kept in a
;;; set of temporary constants.  These reside in
;;; data-point-tuple-1, data-point-tuple-2, etc.
;;; Currently we know that these will be of type number,
;;; i.e. they might be gensym-float, or fixnum.

(def-part-feature (chart-data-point data-point-tuple-valid?)
  (type boolean)
  (user-visible nil))
		  
(def-part-feature (chart-data-point data-point-tuple-1)
  (type t)
  (user-visible nil))

(def-part-feature (chart-data-point data-point-tuple-2)
  (type t)
  (user-visible nil))

;;; As we scan each point we first bind that tuple.
;;; We then transform the tuple into device coordinates.
;;; The result of that is placed into data-point-x, and 
;;; data-point-y.

(def-part-feature (chart-data-point data-point-x)
  (user-visible nil))

(def-part-feature (chart-data-point data-point-y)
  (user-visible nil))

(def-part-feature (chart-data-point data-point-first-x)
  (user-visible nil))

(def-part-feature (chart-data-point data-point-first-y)
  (user-visible nil))

(def-part-feature (chart-data-point data-point-last-x)
  (user-visible nil))

(def-part-feature (chart-data-point data-point-last-y)
  (user-visible nil))

;;; Each data point is illustrated in the chart by an
;;; indicator.  `Data-point-indicator' is bound to a function
;;; name that is called to actually draw the indicator.
;;; This is generally bound on a per series basis but
;;; it can be overridden by a data point annotation.

(deftype-simple data-point-indicator ()
  '(member square rectangle triangle cross x column bar solid-column solid-bar))

;;; Data-point-indicator is specified by the user.  When ever it
;;; changes handlers are called to maintain data-point-indicator-projection-function
;;; in synch with it.

(defun-simple enter-data-point-indicator (new-value)
  (enter-data-point-indicator-1 new-value)
  nil)

(defun-simple exit-data-point-indicator ()
  (exit-data-point-indicator-1)
  nil)

(defvar data-point-indicator 'symbol-standing-in-for-unbound)

(def-part-feature (chart-data-point data-point-indicator)
  (type data-point-indicator)
  (user-visible t)	   
  (means-of-scanning call-handlers #'enter-data-point-indicator #'exit-data-point-indicator)
  (user-spelling indicator))

(def-part-feature (chart-data-point data-point-indicator-projection-function)
  (user-visible nil))

(def-part-feature (chart-data-point data-point-show-indicator)
  (type boolean)
  user-visible
  (user-spelling indicator-visible))


(def-part-feature (chart-data-point data-point-show-connecting-line)
  (type boolean)
  user-visible
  (user-spelling connection-line-visible))



;;;; Axis State



;;; When scanning over the axis, we maintain a bundle
;;; of state that controls the drawing of that axis.
;;; Axis have data points as children, aka tick marks.

(def-part-type axis
  (children-part-types axis chart-data-point)
  (includes data-series grid)
  (hidden-features height
		   width
		   text-alignment
		   border-color
		   background-color)
  (allow-defaulting-in-parents nil))

;;; The axis-heading is currently either EAST or NORTH.
(def-part-feature (axis axis-heading)
  (type symbol)
  (user-visible nil))

(def-part-feature (axis axis-index)
  (type fixnum)
  (user-visible nil))

(deftype-simple simple-number ()
  '(satisfies simple-number-p))

(defun simple-number-p (x)
  (or (slot-value-number-p x)
      (phrase-float-p x)
      (phrase-long-p x)))

(deftype-writer simple-number (x)
  ;; called only when we know that this is a slot-value-number
  (cond ((slot-value-long-p x)
	 (tformat "~DL" (slot-value-long-value x)))
	(t
	 (tformat "~D" (slot-value-number-value x)))))

(deftype-simple simple-nonnegative-number ()
  '(satisfies simple-nonnegative-number-p))

(defun simple-nonnegative-number-p (x)
  (and (simple-number-p x)
       (with-temporary-gensym-float-creation simple-nonnegative-number-p
	 (<=e 0.0
	      (coerce-to-gensym-float
		(if (slot-value-number-p x)
		    (slot-value-number-value x)
		    (phrase-float-value x)))))))

(deftype-writer simple-nonnegative-number (x)
  ;; called only when we know that this is a slot-value-number
  (tformat "~D" (slot-value-number-value x)))

(deftype-error-printer simple-nonnegative-number () "not a nonnegative number")

(def-part-feature (axis axis-minimum)
  (type simple-number)
  user-visible)

(def-part-feature (axis axis-crossover)
  (type simple-number)
  user-visible)

(def-part-feature (axis axis-maximum)
  (type simple-number)
  user-visible)


;;; The users of the axis-tickmark-count must
;;; convert it to an integer before using it.

(def-part-feature (axis axis-tickmark-count)
  (type simple-nonnegative-number)
  user-visible
  (user-spelling number-of-tickmarks))

(def-part-feature (axis axis-tickmark-step)
  (type simple-number)
  user-visible
  (user-spelling tickmark-interval))

(def-part-feature (axis axis-automatic)
   (type boolean)
   (user-visible nil))

(def-part-feature (axis axis-tickmark-count-as-fixnum)
  (type fixnum)
  (user-visible nil))

(def-part-feature (axis axis-tickmark-label-frequency)
  (type fixnum)
  (user-visible nil))

;;; The following three axis part features are used to hold horizontal alignment information for
;;; tickmark labels.  They are used, for example, to line up the decimal points and exponent markers
;;; of labels along a vertical axis.

(def-part-feature (axis axis-tickmark-label-max-digits-before-point)
  (type fixnum)
  (user-visible nil))

(def-part-feature (axis axis-tickmark-label-max-digits-after-point)
  (type fixnum)
  (user-visible nil))

(def-part-feature (axis axis-tickmark-label-max-digits-in-exponent)
  (type fixnum)
  (user-visible nil))

(deftype-simple simple-number-for-significant-digits ()
  '(satisfies simple-number-for-significant-digits-p))

(deftype-error-printer simple-number-for-significant-digits () "not an integer equal to -1, or in the range 2 to 15")

(defun-simple simple-number-for-significant-digits-p (x)
  (and (fixnump x)
       (cond ((=f x -1) t)
	     ((>f x 15) nil)
	     ((<f x 2) nil)
	     (t t))))

(def-part-feature (axis number-of-significant-digits)
  (type simple-number-for-significant-digits)
  user-visible)

;;; This ends the discussion of the chart part type along with
;;; its component subparts.







;;;; Method Tables for Generating Data Series, and Rendering Them



;;; The points in a data series may be generated in more than one way.
;;; For each way that a data series may be generated we provide a set
;;; of functions that together provide a stream like abstraction around
;;; the generation of values.  There are three such functions, an
;;; open, close, and next-tuple method.  We don't have the usual
;;; EOF method---EOF is indicated by setting a flag, i.e. the flag
;;; data-point-tuple-valid?.
;;; See the macro DO-DATA-POINTS for a sample use of these macros.

;;; These methods are invoked within of a temporary float scope.

(defmacro data-series-generator-open-method  (data-series-source-kind) 
  `(get ,data-series-source-kind 'data-series-generator-open-method))

(defmacro data-series-generator-next-tuple-method (data-series-source-kind)
  `(get ,data-series-source-kind 'data-series-generator-next-tuple-method))

(defmacro data-series-generator-close-method (data-series-source-kind)
  `(get ,data-series-source-kind 'data-series-generator-close-method))

(defmacro def-data-series-source-kind (data-series-source-kind open-method tuple-generator close-method)
  (assert (and (symbolp data-series-source-kind)
	       (loop for function-arg 
			 in (list open-method tuple-generator close-method)
			 always
			   (and (consp function-arg)
				(eq 'function (car function-arg))
				(symbolp (second function-arg))))))	;
  `(progn
     #+development
     (loop for method-implementation-function-name
	       in ',(list (second open-method) (second tuple-generator) (second close-method))
	   as method-name in '(open tuple-generator close)
	   as function-type-declaration
	      = (get method-implementation-function-name 'function-type-declaration)
	   unless (equal function-type-declaration '(nil (t)))
	     do (warn "the ~S method of ~S is not declared to be a function of approprate type."
		      method-name ',data-series-source-kind))
     (setf (data-series-generator-open-method       ',data-series-source-kind) ,open-method)
     (setf (data-series-generator-next-tuple-method ',data-series-source-kind) ,tuple-generator)
     (setf (data-series-generator-close-method      ',data-series-source-kind) ,close-method)))




;;; Data series are drawn onto the chart in various ways.  The
;;; data-series-illustration-kind slot in a data series contains
;;; a symbol that dispatchs how the actual series is drawn onto
;;; the chart.  Each way of illustrating a data series on a chart
;;; is declared using 'def-data-series-illustration-kind.'  Along
;;; with that declaration a routine that will render that series
;;; is declared.

(defmacro data-series-projection-method (data-series-illustration-kind)
  `(get ,data-series-illustration-kind 'data-series-projection-method))

(defmacro def-data-series-illustration-method (data-series-illustration-method projection-method)
  (assert (symbolp data-series-illustration-method))
  (assert (symbolp projection-method))
  `(progn
     (setf (data-series-projection-method ',data-series-illustration-method) ',projection-method)))

;;; `With-chart' encapsulates the dynamic context of a chart.

(defmacro with-chart (&body body)
  `(with-part-type-scanning
     (let ((chart-top  0)
	   (chart-left 0)
	   (chart-right   (-f (right-edge-of-block current-chart-frame)
			      ( left-edge-of-block current-chart-frame)))
	   (chart-bottom (-f (bottom-edge-of-block current-chart-frame) 
			     (   top-edge-of-block current-chart-frame)))
	   (current-text-box-format 
	     (get-or-make-format-frame 'dynamic-text-cell-format)))
       (with-part-description ((chart-part-description-for-chart-style (chart-style current-chart-frame)))
	 (with-part-description ((or (annotations current-chart-frame)
				     '(chart)))
	   (with-part-description ((or (computed-annotations current-chart-frame)
				       '(chart)))
	     ,@body))))))

;; The three with-part-descriptions create identical code in their epilogs.
;; That code space could be reclaimed.



;;; `Do-data-series' is an iteration macro.  It sweeps over
;;;  the set of chart series binding the global state for
;;;  the current data series.

(defmacro do-data-series (&body body)
  `(loop
     for current-data-series in data-series-subparts
     as current-computed-data-series
	 in (get-subpart-collection
	      (computed-annotations current-chart-frame)
	      'subparts
	      'data-series)
     as data-series-index from 1
     do (with-part-description (current-data-series)
	  (with-part-exceptions ('data-series data-series-index)
	    (with-part-description (current-computed-data-series)
	      ,@body)))))



;;; `Do-data-points' sweeps over the tuples of a given
;;; data series.

(defmacro do-data-points (&body body)
  `(with-temporary-gensym-float-creation do-data-points
     (when (funcall-simple-compiled-function (data-series-generator-open-method data-series-source-kind))
       (let ((data-series-generator-next-tuple-method
	       (data-series-generator-next-tuple-method data-series-source-kind))
	     data-point-index)	 
	 (loop initially (setf data-point-index 1)
	       do
	   (with-temporary-gensym-float-creation do-one-data-point
	     (funcall-simple-compiled-function data-series-generator-next-tuple-method)
	     (unless data-point-tuple-valid?
	       (return nil))
	     ,@body)
	   (incff data-point-index))
	 (funcall-simple-compiled-function (data-series-generator-close-method data-series-source-kind))))))

;;; `axis-is-discrete-p' is bound true inside an axis context if the values of the
;;; data along the axis are integer quantities.  Currently this happens only if the
;;; axis is the horizontal axis and all data series consist of plots against integers.

(defvar axis-is-discrete-p) 

(defmacro do-axis (&body body)
  (let ((axis-subparts '(get-subpart-collection
			 (computed-annotations current-chart-frame)
			 'subparts
			 'axis)))
    `(with-part-description (default-axis-data-series-instance)
       (loop for current-axis in ,axis-subparts
	     as axis-index from 1
	     do (with-part-description (current-axis)
		  (let ((axis-is-discrete-p
			  (if (eq axis-heading 'east)
			      (plot-east-axis-label-tickmarks-as-integers-p
				current-chart-frame)
			      (plot-north-axis-label-tickmarks-as-integers-p
				current-chart-frame))))

		    ;; (and (eq axis-heading 'east) (all-data-series-are-one-
		    ;; quantity-lists-p))))    - the original code, Jwang 3/25/97
		    
		    ;; The original code only works for x-axis, in another words,
		    ;; no matter what type of the data-series-sources for y-axis
		    ;; is, the labels for the y-axis will always be float number.
		    ;; So if the user uses 'Plot data-series-1 versus data-series-2',
		    ;; the labels for both x-axis and y-axis will be float number.
		    ;; The code has been changed to first determine the type of
		    ;; the data-series-sources for both axes, if the type of
		    ;; the data series for one axis is integer the label for that
		    ;; axis will be an integer, otherwise a float.      Jwang, 3/24/97
		    ,@body))))))




;;;; Binding the Particulars for an Axis.



;;; These routines create a computed axis description given a partial axis description
;;; provided by the user.  They will bind all particulars of the axis, i.e. axis-minimum, 
;;; axis-maximum, crossover, axis-tickmark-step, etc. etc.   For input they take:
;;;  1. some information about the range of the data being displayed along this axis,
;;;  2. a first draft of the resulting axis description which is modified to create the result,
;;;  3. an axis description containing any particulars of the axis the user has requested.

;;; These routines should be called inside of a temporary float creation scope.  Any
;;; numbers placed into the computed axis description will be permanent.



;;; `Safe-chart-log' computes the log, base 10, of the magnitude of the number given.
;;; The most negative value it can return is -7.0.

(defun safe-chart-log (x)
  (assert-that-within-temporary-float-scope)
  (let ((x1 (abse x)))
    (if (<e x 1d-7)	; bug: does this want to be (<e x1 1e-7) ?
	-7.0
	(loge x1 10d0))))

;; Why limit the smallest value returned?
;; Todo:bug: limiting the most negative valued returned by `safe-chart-log' to -7
;; means that users cannot usefully chart data consisting of very small data points.
;; This limit should be removed but only after carefully ensuring that such removal
;; does not introduce exceptions (underflow, Nan, etc). -wgd 04/03/92

;;; `Estimated-axis-granularity' returns, given a range, a good number for rounding
;;; the boundaries of the axis to.  It returns the largest number (smaller than X) of
;;; the form A*10^N where A is one of 1, 2, or 5.

(defun estimated-axis-granularity (x)
  (assert-that-within-temporary-float-scope)
  (if (=e x 0d0)
      1d0
      (let* ((x1 (abse x))
             (d1 (expte 10d0 (ftruncatee (safe-chart-log x1))))
             (d2 (+e d1 d1))
             (d5 (*e 5d0 d1)))
        (cond
          ((<=e d5 x1) d5)
          ((<=e d2 x1) d2)
          ((<=e d1 x1) d1)
          (T (/e d1 2d0))))))

(defun estimated-axis-boundaries (data-minimum data-maximum)
  (assert-that-within-temporary-float-scope)
  (let ((grain (/e (estimated-axis-granularity 
		     (-e data-minimum data-maximum)) 
		   10d0)))
    (let ((low  (*e grain (if (or (<e data-minimum 0d0)
				  (>e data-minimum 0d0))
			      (ffloore   data-minimum grain) 0d0)))
          (high (*e grain (fceilinge data-maximum grain))))
      ;; The condition statement here is to avoid the following situation :
      ;; If data-minimum equal 0, this function will return a result '-0.0'. If
      ;; the result of this function is the label of a chart, the label on the
      ;; chart will be '-0.0' instead of '0.0'.   - Jwang  3/25/97
      (values low high grain))))



;;; `Compute-axis-bounds-1' does the meat of computing axis boundaries.  It first
;;; uses estimated-axis-boundaries to get a first guess at reasonable upper and lower
;;; limits on the axis.  It then applies some rules to these results.  
;;;   	 1. Assure that the axis boundaries aren't (fuzzily) identical.
;;;      2. Include zero in the axis range if it doesn't create too much
;;;         empty whitespace.
;;;      3. Make sure that some range appears on the chart when the user specified one
;;;         axis boundary, even if that range doesn't overlap the data.
;;; Finally it leaves its results in axis-minimum and axis-maximum.  These results
;;; contain allocated space, so the caller must manage that space.

(defun compute-axis-bounds-1 (axis-description data-minimum data-maximum)
  (assert-that-within-temporary-float-scope)
  (let ((requested-axis-minimum? (get-simple-part-feature axis-description 'axis-minimum))
	(requested-axis-maximum? (get-simple-part-feature axis-description 'axis-maximum)))
    (when requested-axis-minimum?
      (setf requested-axis-minimum? (slot-value-number-value-as-float requested-axis-minimum?)))
    (when requested-axis-maximum?
      (setf requested-axis-maximum? (slot-value-number-value-as-float requested-axis-maximum?)))
    (cond
      ;; Preserve the user's requested axis minimum and maximum (unless they are equal, in which
      ;; case we bump the maximum up by 1). Note that this allows max < min.
      ((and requested-axis-minimum? requested-axis-maximum?)
       (setf axis-minimum (make-slot-value-float requested-axis-minimum?))
       (setf axis-maximum
	     (make-slot-value-float
	       ;; Note that it is OK for max < min (the axis is essentially flipped in this case)
	       (if (=e requested-axis-minimum? requested-axis-maximum?)
		   (+e requested-axis-minimum? 1.0)
		   requested-axis-maximum?))))
      (T
       (multiple-value-bind (computed-axis-minimum computed-axis-maximum)
	   (estimated-axis-boundaries data-minimum data-maximum)
	 
	 ;; 1. Assure that the axis boundaries aren't (fuzzily) identical.
	 (let* ((min computed-axis-minimum)
		(max computed-axis-maximum)
		(log (ftruncatee (safe-chart-log (abse computed-axis-minimum))))
		(tiny (expte 10d0 (-e log 5d0)))
		(bump 1d0))
	   (unless (<=e min max)
	     (rotatef min max)
	     (setf bump -1.0))
	   (when (<=e (-e min tiny) min max (+e min tiny))
	     (setf computed-axis-minimum
		   (-e computed-axis-minimum bump))
	     (setf computed-axis-maximum
		   (+e computed-axis-maximum bump))))
	 
	 ;; 2. Include zero in the axis if it doesn't double the axis's range.
	 ;; GENSYMCID-1147: Chart_minimum_axis_2
	 ;;   minimum axis or maximum axis will be wrongly set to 0 in some situation.
	 ;;   e.g. when min is 9 and max is 21, in next piece of code, it will first
	 ;;   satisfy (21-9)*2 > 21, then min value will be set to 0. This is not correct.
	 ;;   If customer really need include 0 in axis, "the axis-minimum of axis X = V"
	 ;;   can be used in Annotations. -- Fei Liu, Nov 2013
#|
	 (unless (or (<=e computed-axis-minimum 0d0 computed-axis-maximum)
		     (>=e computed-axis-minimum 0d0 computed-axis-maximum))
	   (let ((current-axis-range 
		   (abse (-e computed-axis-minimum computed-axis-maximum)))
		 (bigger-axis-range
		   (maxe (abse computed-axis-minimum)
			 (abse computed-axis-maximum))))
	     (unless (<e (*e 2d0 current-axis-range) bigger-axis-range)
	       (if (<e 0d0 computed-axis-maximum)
		   (setf computed-axis-minimum 0d0)
		   (setf computed-axis-maximum 0d0)))))
|#
	 
	 ;; 3. If either of the axis bounds was given then we must make sure we put some range
	 ;; on the chart, even if none of the data. (also covers case of computed bound being
	 ;; identical to requested bound).
	 (let ((bump (expte 10d0 (ftruncatee (safe-chart-log (abse (-e data-minimum data-maximum)))))))
	   (when (and requested-axis-minimum?
		      (<=e computed-axis-maximum requested-axis-minimum?))
	     (setf computed-axis-maximum 
		   (+e requested-axis-minimum? bump)))
	   (when (and requested-axis-maximum?
		      (>=e computed-axis-minimum requested-axis-maximum?))
	     (setf computed-axis-minimum 
		   (-e requested-axis-maximum? bump))))
	 
	 ;; Ensure that max != min and enclose as slot-values
	 (setq axis-minimum (or requested-axis-minimum? computed-axis-minimum))
	 (setq axis-maximum (or requested-axis-maximum? computed-axis-maximum))
	 (when (=e axis-minimum axis-maximum)
	   (setq axis-maximum (+e axis-minimum 1.0)))
	 (setf axis-minimum (make-slot-value-float axis-minimum))
	 (setf axis-maximum (make-slot-value-float axis-maximum))))))
  (values axis-minimum axis-maximum))  ; return the result to ease debugging.





;;; `Compute-axis-bounds' holds the whole computation of the axis together.  It first computes
;;; the bounds, and someday it will get the tick marks computed up right.

(defun compute-axis-bounds (computed-axis-description requested-axis-description data-minimum data-maximum)
;  (with-part-description (requested-axis-description) ; this would be better!
  (let ((crossover (get-simple-part-feature requested-axis-description 'axis-crossover)))
    (when crossover
      (set-simple-part-feature 
	computed-axis-description
	'axis-crossover 
	(copy-for-slot-value crossover))))
  (let ((axis-minimum nil)
	(axis-maximum nil))
    (compute-axis-bounds-1
      requested-axis-description
      data-minimum
      data-maximum)
    (set-simple-part-features computed-axis-description 
      'axis-minimum axis-minimum
      'axis-maximum axis-maximum)))



;;; 'Pin-crossover-as-necessary' computes for a chart axis the appropriate place to do
;;; the axis cross over.  It will move the cross over so that axis appears on the 
;;; chart.  This is where symbolic requests for axis cross over should be handled.

(defun pin-crossover-as-necessary (axis-with-crossover axis)
  (assert-that-within-temporary-float-scope)
  (let ((min 	   (get-simple-part-feature-as-float axis 'axis-minimum))
	(max 	   (get-simple-part-feature-as-float axis 'axis-maximum))
	(crossover (get-simple-part-feature-as-float axis-with-crossover 'axis-crossover)))
    (unless (<=e min max)
      (rotatef min max))
    (unless (<=e min crossover max)
      (set-simple-part-feature 
	axis-with-crossover
	'axis-crossover	    
	(make-slot-value-float
	  (if (<e crossover min) 
	      min
	      max))))))

;;; `all-data-series-are-one-quantity-lists-p' returns true iff all data series of the current chart
;;; are `one quantity lists' (a list of values to be plotted against the natural integers 1,2,3...).
;;; This is used to determine whether or not tickmark labels should be printed as integers.

(defun-simple plot-north-axis-label-tickmarks-as-integers-p (chart-frame)
  (with-named-dynamic-extent working-on-lexical-computation-of-frame
      ((*current-computation-frame* chart-frame))
    (and (data-series chart-frame)
	 (loop for data-series in (data-series chart-frame)
	       as data-series-source-temp1 =
	       (evaluate-designation
		 (get-simple-part-feature data-series 'data-series-info-1)
		 nil)
	       as data-series-source-temp2 =
	       (let ((info-2
		       (get-simple-part-feature data-series 'data-series-info-2)))
		 (when info-2
		   (evaluate-designation info-2 nil)))
	       always
	       (cond
		 ((and
		    (null (get-simple-part-feature data-series 'data-series-info-2))
		    (framep data-series-source-temp1))
		  (or
		    (frame-of-class-p
		      data-series-source-temp1
		      'integer-array)
		    (frame-of-class-p
		      data-series-source-temp1
		      'integer-list)))
		 ((and
		    (framep data-series-source-temp2)
		    (framep data-series-source-temp1))
		  (or
		    (frame-of-class-p
		      data-series-source-temp2
		      'integer-array)
		    (frame-of-class-p
		      data-series-source-temp2
		      'integer-list)))
		 (t
		  (reclaim-if-temporary-constant data-series-source-temp1)
		  (reclaim-if-temporary-constant data-series-source-temp2)
		nil))))))
	       

;;;       (eq 'one-g2-quantity-list
;;;         (get-simple-part-feature data-series
;;;        'data-series-source-kind))))) ;;; - Original code, Jwang 3/25/97

;;; The code has been changed to only determine the type of data-series-sources
;;; for y-axis. If the data-series-sources is of 'integer', the 'axis-is-
;;; discrete-p' will be set to 't', otherwise 'nil'.   Jwang 3/25/97



;;; This function is to determine the type of the data-series-sources for
;;; x-axis. If the data-series-sources is of 'integer', the 'axis-is-discrete-p'
;;; will be set to 't', otherwise 'nil'.  Jwang 3/25/97


(defun-simple plot-east-axis-label-tickmarks-as-integers-p (chart-frame)
  (with-named-dynamic-extent working-on-lexical-computation-of-frame
      ((*current-computation-frame* chart-frame))
    (and (data-series chart-frame)
       (loop for data-series in (data-series chart-frame)
	     as data-series-source-temp =
	     (evaluate-designation
	       (get-simple-part-feature data-series 'data-series-info-1)
	       nil)
	     always
	     (cond ((eq 'one-g2-quantity-list
			(get-simple-part-feature data-series 'data-series-source-kind))
		    t)
		   ((and
		      (eq 'pair-of-g2-quantity-lists
			  (get-simple-part-feature data-series 'data-series-source-kind))
		      (neq data-series-source-temp nil))
		    (and (framep data-series-source-temp)
			 (or
			   (frame-of-class-p data-series-source-temp  'integer-array)
			   (frame-of-class-p data-series-source-temp  'integer-list))))
		   (t nil))))))    






;;; `tickmark-label-min-height' is the minimum height allowed to be used for a tickmark label along
;;; a vertical axis.  This is used to determine the maximum number of labels that will fit along
;;; a vertical axis.  This parameter should be computed based on the font height of a char.
;;; The current fixed value is for the current fixed tickmark label font (HM14)

(defvar tickmark-label-min-height 12.0)

;;; `tickmark-label-char-width' is the maximum width of a character allowed to appear in a tickmark label.
;;; Currently this is the width of a digit in the fixed char label font HM14.  The code for aligning
;;; tickmark labels depends on all digits having the same width (MHD says that this assumption is
;;; currently valid for all our fonts). However, in the current font used for tickmark labels,
;;; `-' is thinner than a digit and this messes up alignment when exponents are negative.  It would
;;; be nice to have a `-' as wide as a digit.

(defvar tickmark-label-char-width 8.0)

;;; `tickmark-label-min-width' is the minimum width allowed to be used for a tickmark label along a
;;; horizontal axis.  This is used to determine the maximum number of labels that will fit along a
;;; horizontal axis.  This parameter should be computed based on the font width of a char.  The
;;; current fixed value is for the current fixed tickmark label font (HM14) and is defined to be the
;;; maximal width of 6 chars (the general minimal horizontal tickmark allowed is `x.ye-z', except if
;;; either all labels can be displayed in the format `x.y' or else the labels are integers from
;;; one-g2-quantity-list's in which case single char labels are allowed).

(defvar tickmark-label-min-width (*e 6.0 tickmark-label-char-width))

;; Jim assures me this is acceptable, even without the with-temporary-gensym-float-creation!
;;  - ben, Aug 25, 93

;;; `Compute-axis-tickmarks-and-style' computes plausible tick marks for this axis.
;;; Note that the tickmark count is stored in the part description as a 
;;; gensym float.  Before being used in any computations it is truncated
;;; to leave only its integer part.

;;; This also copies over any formatting attributes.

(defmacro chart-horizontal-device-range ()
  '(-f chart-right chart-left chart-left-margin chart-right-margin))

(defmacro chart-vertical-device-range ()
  '(-f chart-bottom chart-top chart-top-margin chart-bottom-margin))

;;; `Compute-tickmark-count-from-tickmark-step' computes the tickmark-count 
;;; as a floated integer.

;;; Anything "close" to an integer should be truncated to that integer.
;;; E.g. (/e 0.7 0.1) gives 6.999...9 but 7.0 should be returned by
;;; the truncation.  Hence, 0.001 is added before truncating.

;;; Finally, calling 1+e is an attempt at having the outermost tickmarks
;;; subsume the entire range while obeying the tickmark step.

;;; - jpg 7/25/05

(defun-substitution-macro compute-tickmark-count-from-tickmark-step (range tickmark-step)
  (1+e (abse (ftruncatee (+e (/e range tickmark-step) 0.001)))))

(defun compute-axis-tickmarks-and-style
       (requested-axis-description computed-axis-description
	&optional (tickmark-min-width tickmark-label-min-width))
  (assert-that-within-temporary-float-scope)
  (let* ((min (get-simple-part-feature-as-float computed-axis-description 'axis-minimum))
	 (max (get-simple-part-feature-as-float computed-axis-description 'axis-maximum))
	 (range (-e max min))
	 (heading (get-simple-part-feature computed-axis-description 'axis-heading))
	 (requested-tickmark-count?
	   (get-simple-part-feature requested-axis-description 'axis-tickmark-count))
	 (requested-tickmark-step?
	   (get-simple-part-feature requested-axis-description 'axis-tickmark-step))
	 (actual-tickmark-count			; actual count and step may be adjusted below
	   (if requested-tickmark-count?
	       (maxe (abse (ftruncatee (slot-value-number-value-as-float
					 requested-tickmark-count?)))
		     0.0)			; todo: this allows 0 or 1 tickmark(s), should it?
	       2.0))
	 (axis-tickmark-label-frequency 1)
	 (discrete-p (and (eq heading 'east)
			  (plot-east-axis-label-tickmarks-as-integers-p
			    current-chart-frame)))
	 actual-tickmark-step device-range label-min-size label-room)

    (when requested-tickmark-step?
      (setq requested-tickmark-step?
	    (slot-value-number-value-as-float requested-tickmark-step?)))
    (setq actual-tickmark-step
	  (if (and requested-tickmark-step? 
		   (if (<=e min max)
		       (<e 0.0 requested-tickmark-step?)
		       (<e requested-tickmark-step? 0.0)))
	      requested-tickmark-step?
	      (/e range (maxe (1-e actual-tickmark-count) 1.0))))	; max avoids div by 0

    (when requested-tickmark-step?
      (setf actual-tickmark-count
	    (compute-tickmark-count-from-tickmark-step range actual-tickmark-step)))
    
    (case heading
      (east  (setq device-range (coerce-to-gensym-float (chart-horizontal-device-range)))
	     (setq label-min-size tickmark-min-width)) 
      (north (setq device-range (coerce-to-gensym-float (chart-vertical-device-range)))
	     (setq label-min-size tickmark-label-min-height)))
    
    ;; Adjust step and count based on the maximum number of labels we can fit along the axis using the label font.
    ;; In addition, for the horizontal axis, if all data-series are discrete (i.e. of type one-g2-quantity-list)
    ;; then force the axis tickmark labels to be integers by rounding the tickmark-step up to the next integer.
    
    (macrolet ((maybe-make-axis-tickmark-labels-integers ()
		 '(when discrete-p
		    ;; ftruncatee-UP (i.e. round away from 0) since step is negative if max < min
		    ;; We scale down by .9999 to avoid pushing up step by 1 when roundoff gives us a
		    ;; fuzzy increment of the desired step. If we didn't do this then the last
		    ;; tickmark might end up incorrectly clipped.
		    (setq actual-tickmark-step  (ftruncatee-up (*e .9999 actual-tickmark-step)))
		    (setq actual-tickmark-count
		          (compute-tickmark-count-from-tickmark-step range actual-tickmark-step)))))

      (maybe-make-axis-tickmark-labels-integers)

      (when (and (not (=e 0.0 actual-tickmark-count))
		 (>e label-min-size (setq label-room (/e device-range actual-tickmark-count))))
	(setq axis-tickmark-label-frequency (ceilinge-first label-min-size label-room))

	;; We no longer automatically compute a new step and count when there is not enough room
	;; for count labels. Instead we preserve the requested count or step and stagger the labels.
	;(setf actual-tickmark-count (ftruncatee (/e device-range label-min-size)))
	;(setf actual-tickmark-step  (/e range (maxe 1.0 actual-tickmark-count)))	; max avoids div by 0
	;(setf actual-tickmark-count (1+e actual-tickmark-count))

	(when (>=e actual-tickmark-count 2.0)
	  (maybe-make-axis-tickmark-labels-integers))))

    (set-simple-part-features computed-axis-description
      'axis-tickmark-step  (make-slot-value-float actual-tickmark-step)
      'axis-tickmark-count (make-slot-value-float actual-tickmark-count)
      'axis-tickmark-count-as-fixnum (truncate actual-tickmark-count)
      'axis-tickmark-label-frequency axis-tickmark-label-frequency)
        
    ;; Copy over any formatting attributes
    
    (loop for (feature value) on (cdr requested-axis-description) by #'cddr
	  when (memq feature '(text-color line-color grid-visible grid-color border-color
			       text-size number-of-significant-digits))
	    do
	      (set-simple-part-feature
		computed-axis-description
		feature
		value))))

;; Needs to be more sophisticated about selecting a default tickmark count and step.

;; ???? Negative values for tickmark count







;;;; Axis Series Generator

(defun-simple axis-series-open-generator ()
  (setf data-point-tuple-1 
	(make-temporary-constant-no-expiration
	  (slot-value-number-value-as-float axis-minimum) 'number))
  (setf data-point-tuple-2
	(make-temporary-constant-no-expiration
	  (slot-value-number-value-as-float axis-crossover) 'number))
  (when (eq axis-heading 'north)
    (rotatef data-point-tuple-1 data-point-tuple-2))
  ;; Map the first point into device space and this axis contribution to the
  ;; axis cross over origin.
  (transform-data-tuple-to-device-coordinates)
  (case axis-heading
    (north
     (setq chart-origin-x data-point-x))
    (east
     (setq chart-origin-y data-point-y)))
  t)

(defun-simple axis-series-close-generator ()
  (reclaim-temporary-constant data-point-tuple-1)
  (reclaim-temporary-constant data-point-tuple-2))

(defun-simple axis-series-next-tuple ()
  (assert-that-within-temporary-float-scope)
  (setf data-point-tuple-valid? T)

  (when (eq axis-heading 'north)
    (rotatef data-point-tuple-1 data-point-tuple-2))	; Undone below
  
  (let ((tick-mark-index data-point-index))
    (cond ; about tick-mark-index
      ((=f 1 tick-mark-index))       ; nothing to do since data-point-tuple was init'ed by open-method

      ;; Don't plot the maximum since it will usually be within epsilon of last point plotted and this
      ;; confuses our greedy precision heuristic for vertical axes (and may also cause overlapping
      ;; tickmark labels). 
      ;;
      ;; ((=f axis-tickmark-count-as-fixnum tick-mark-index)
      ;;  (store-constant-value data-point-tuple-1 (slot-value-number-value-as-float axis-maximum)))

      ((<f axis-tickmark-count-as-fixnum tick-mark-index)
       (setf data-point-tuple-valid? nil))
      (T
       (store-constant-value data-point-tuple-1
			     (+e (cached-constant-value data-point-tuple-1)
				 (slot-value-number-value-as-float axis-tickmark-step))))))
  
  (when (eq axis-heading 'north)
    (rotatef data-point-tuple-1 data-point-tuple-2)))

(def-data-series-source-kind axis-data-series
  #'axis-series-open-generator
  #'axis-series-next-tuple
  #'axis-series-close-generator)



(defvar default-axis-data-series-instance)

(setf default-axis-data-series-instance
      '(data-series
	 data-series-index -1
	 data-series-source-kind axis-data-series
	 data-series-illustration-kind simple-scatter-plot
	 ;; This used to be T so that the axis would be drawn implicitly as the connection line between
	 ;; between the first and last point (= tickmark). However this loses if there are no tickmarks,
	 ;; so that we now draw the axis explicitly in axis-tick-mark's chart-data-point-indicator method.
	 data-series-connect-first-and-last-point nil
	 ; color black
	 subpart-defaults (chart-data-point ((chart-data-point
					       data-point-show-connecting-line nil
					       data-point-show-indicator t
					       ;; axis-tick-mark is defined via define-chart-data-point-indicator
					       data-point-indicator axis-tick-mark)))))

; (validate-part-instance 'data-series default-axis-data-series-instance)







;;;; Data Series Generator for Malformed Input Data




;;; The data series source kind `malformed-data-series' is placed
;;; in the computed annotations when evaluation of the plot specification
;;; is unable to create useful data caches, usually because of an
;;; error during evaluation.  When a data-series has this as it's source
;;; kind the scans are prempted and no data points are generated.

(defun-simple malformed-data-series-return-nil ()
  nil)

(def-data-series-source-kind malformed-data-series
  #'malformed-data-series-return-nil
  #'malformed-data-series-return-nil
  #'malformed-data-series-return-nil)







;;;; Data Series Generator For Float Pairs From The Data Caches




;;; The data series source kind `float-and-float-from-data-caches'
;;; generates pairs of temporary constants in the data-point-tuples.
;;; The integers, starting from one, are generated in the first value.
;;; The values found in the managed float array of data-series-data-cache-1?
;;; are used to fill out the second value.  Both values are gensym floats. 

;; Inputs:
;;  data-series-data-cache-1?    -- a managed array of X values.
;;  data-series-data-cache-2?    -- a managed array of Y values.
;; Outputs:
;;  data-point-tuple-1 -- temporary constant, the "X" value, we own it.
;;  data-point-tuple-2 -- temporary-constant, the "Y" value, we own it.
;;  data-point-tuple-valid? -- boolean,
;; State:
;;  data-series-generator-info-1 -- the index of previous value in the managed array
;;  data-series-generator-info-2 -- the length of the managed array

(defun-simple float-and-float-from-data-caches-open-generator ()
  (assert-that-within-temporary-float-scope)
  (setf data-point-tuple-1 (make-temporary-constant-no-expiration 0.0 'number))
  (setf data-point-tuple-2 (make-temporary-constant-no-expiration 0.0 'number))
  (setf data-series-generator-info-1 -1)
  (setf data-series-generator-info-2 (minf (managed-float-array-length data-series-data-cache-1?)
					   (managed-float-array-length data-series-data-cache-2?)))
  t)

(defun-simple float-and-float-from-data-caches-next-tuple ()
  (assert-that-within-temporary-float-scope)
  (incff data-series-generator-info-1)
  (setf data-point-tuple-valid?
	(cond
	  ((>=f data-series-generator-info-1 data-series-generator-info-2)
	   nil)
	  (t
	   (store-constant-value data-point-tuple-1
				 (managed-float-aref data-series-data-cache-1? data-series-generator-info-1))
	   (store-constant-value data-point-tuple-2
				 (managed-float-aref data-series-data-cache-2? data-series-generator-info-1))
	   t))))

(defun-simple float-and-float-from-data-caches-close-generator ()
  (reclaim-temporary-constant data-point-tuple-1)
  (reclaim-temporary-constant data-point-tuple-2)
  nil)

(def-data-series-source-kind float-and-float-from-data-caches
  #'float-and-float-from-data-caches-open-generator
  #'float-and-float-from-data-caches-next-tuple
  #'float-and-float-from-data-caches-close-generator)





;;;; The Different Kinds of Data Series Illustration Techniques



;;; Simple-scatter-plot is the only data series illustration method
;;; currently available.

(def-data-series-illustration-method simple-scatter-plot
  simple-scatter-plot-data-series-projection-method)

(defun simple-scatter-plot-data-series-projection-method ()
  (setf data-point-last-x  nil)
  (setf data-point-last-y  nil)
  (setf data-point-first-x nil)
  (setf data-point-first-x nil)
	  
  (do-data-points
    (transform-data-tuple-to-device-coordinates)
    (unless data-point-first-x
      (setf data-point-first-x data-point-x)
      (setf data-point-first-y data-point-y))
    (when data-point-show-indicator
      (funcall-simple-compiled-function data-point-indicator-projection-function))
    (when data-point-show-connecting-line
      (project-connecting-line))
    (setf data-point-last-x data-point-x)
    (setf data-point-last-y data-point-y))
  
  (when (and data-series-connect-first-and-last-point
	     data-point-last-x)
    (let ((data-point-x data-point-last-x)
	  (data-point-y data-point-last-y)
	  (data-point-last-x data-point-first-x)
	  (data-point-last-y data-point-first-y))
      (project-connecting-line))))







;;;; The various kinds of data point indicators


(defun project-connecting-line ()
  (when data-point-last-x
    (chart-move-to data-point-last-x data-point-last-y)
    (chart-line-to data-point-x data-point-y)))




;;; Each kind of indicator that may appear for a data point is given a
;;; routine that will draw that indicator.  The name the user specifies
;;; for the indicator is then assocated with that routine's name via the
;;; global property chart-data-point-indicator.

;;; The macro define-chart-data-point-indicator is used to define each
;;; kind of indicator.  if you add another indicator you must augment
;;; the dictionary set-up routine to assure that the user name is added
;;; to the dictionary.

;;; Any addition to this set must also be added to the grammar for
;;; indicator-kind and to simple-type data-point-indicator.

(def-global-property-name chart-data-point-indicator)

(defmacro define-chart-data-point-indicator (user-name empty-argument-list &body body)
  (when empty-argument-list 
    (warn "Define-chart-data-point-indicator for ~S had arguments." user-name))
  (let ((function-name (intern (format nil "PROJECT-~S-CHART-INDICATOR" user-name))))
    `(progn
       (defun-simple ,function-name () ,@body nil)
       (setf (chart-data-point-indicator ',user-name)
	     #',function-name))))


;;; `With-indicator-bindings' establishs lexical bindings useful
;;; when rendering a a data-point indicator.  This is used only
;;; in the bodies of define-chart-data-point-indicator.  It takes
;;; a list of variables to bind, along with a body and creates
;;; bindings for those ala let*.  These variables provide access
;;; to the width and height as specified for the data-point part.
;;; They are in units of device raster units (i.e. the scalling
;;; has been done). w, w1, and w2 access the width, and h, h1, and
;;; h2 access the height.  w1+w2=w and h1+h2=h.
	 
(defmacro with-indicator-bindings (desired-bindings &body body)
  (let ((binding-table
	  '((width ()
	     (floor-slot-value-number-to-fixnum
	      current-width-of-formatted-part))
	    (height ()
	     (floor-slot-value-number-to-fixnum
	      current-height-of-formatted-part))
	    (w (width)
	     (delta-x-in-window width current-image-x-scale))
	    (w1 (width)
	     (delta-x-in-window
	      (truncatef width 2) current-image-x-scale))
	    (w2 (width)
	     (delta-x-in-window
	      (- width (truncatef width 2)) current-image-x-scale))
	    (h (height)
	     (delta-y-in-window height current-image-y-scale))
	    (h1 (height)
	     (delta-y-in-window
	      (truncatef height 2) current-image-y-scale))
	    (h2 (height)
	     (delta-y-in-window
	      (- height (truncatef height 2)) current-image-y-scale)))))
    `(let* (,@(loop with what-to-bind
		    ;; add in the required stuff
		      = (loop for var in desired-bindings
			      as needs-these-vars
				 = (second (assq var binding-table))
			      nconc (list var)
			      nconc (copy-list needs-these-vars))
		    for (bind nil form) in binding-table
		    when (memq bind what-to-bind)
		      collect (list bind form)))
       ,@body)))


;;; `floor-slot-value-number-to-fixnum' does just that, curiously
;;; I didn't notice another function to do this.

(defun floor-slot-value-number-to-fixnum (slot-value-number)
  (cond
    ((fixnump slot-value-number)
      slot-value-number)
    ((slot-value-float-p slot-value-number)
     (with-temporary-gensym-float-creation truncate-slot-value-number-1
	 (floore-first (slot-value-float-value slot-value-number))))
    #+development
    ((not (gensym-float-p slot-value-number))
     (cerror "Go" "Unexpected form of slot-value-number! ~S" slot-value-number)
     1)
    (t
     (with-temporary-gensym-float-creation truncate-slot-value-number-1
       (floore-first slot-value-number)))))

(define-chart-data-point-indicator rectangle ()
  (with-indicator-bindings (w1 h1 w2 h2)
    (chart-frame-rectangle
      (-f data-point-x w1)
      (-f data-point-y h1)
      (+f data-point-x w2)
      (+f data-point-y h2))))

(define-chart-data-point-indicator triangle ()
  (with-indicator-bindings (w1 h1 w2 h2)
    (chart-move-to data-point-x (-f data-point-y h1))
    (chart-line              w1 (+f h1 h2))
    (chart-line (-f (+f w1 w2)) 0)
    (chart-line              w2 (-f (+f h1 h2)))
    (chart-move-to data-point-x data-point-y)))

(define-chart-data-point-indicator square ()
  (with-indicator-bindings (w1 h1 w2 h2)
    (chart-fill-rectangle
      (-f data-point-x w1)
      (-f data-point-y h1)
      (+f data-point-x w2)
      (+f data-point-y h2))))

(define-chart-data-point-indicator cross ()
  (with-indicator-bindings (w h w1 h1)
    (chart-move-to (-f data-point-x w1) data-point-y)
    (chart-line w 0)
    (chart-move-to data-point-x (-f data-point-y h1))
    (chart-line 0 h)))

(define-chart-data-point-indicator x ()
  (with-indicator-bindings (w1 h1 w2 h2)
    (chart-move-to (-f data-point-x w1) (-f data-point-y h1))
    (chart-line    (+f w1 w2)   (+f h1 h2))
    (chart-move-to (+f data-point-x w2) (-f data-point-y h1))
    (chart-line    (-f 0 w1 w2) (+f h1 h2))
    (chart-move-to data-point-x data-point-y)))

(define-chart-data-point-indicator column ()
  (with-indicator-bindings (w1 w2)
    (chart-frame-rectangle
      (-f data-point-x w1)
      data-point-y
      (+f data-point-x w2)
      (1+f chart-origin-y))))

(define-chart-data-point-indicator bar ()
  (with-indicator-bindings (h1 h2)
    (chart-frame-rectangle
      chart-origin-x
      (-f data-point-y h1)
      data-point-x
      (+f data-point-y h2))))

(define-chart-data-point-indicator solid-column ()
  (with-indicator-bindings (w1 w2)
    (let* ((bottom chart-origin-y)
	   (top data-point-y))
      (when (<f bottom top)
	(rotatef top bottom))
      (chart-fill-rectangle
	(-f data-point-x w1)
	top
	(+f data-point-x w2)
	(1+f bottom)))))

(define-chart-data-point-indicator solid-bar ()
  (with-indicator-bindings (h1 h2)
    (let* ((left chart-origin-x)
	   (right data-point-x))
      (when (<f right left)
	(rotatef left right))
      (chart-fill-rectangle
	left
	(-f data-point-y h1)
	right
	(+f data-point-y h2)))))


;;; Tick mark indicator.

(defun chart-full-line-east ()
  (chart-line (1-f (delta-x-in-window (chart-horizontal-device-range)
				      current-image-x-scale))
	      0))

(defun chart-full-line-north ()
  ;; Theoretically the `progn' below should be a `1-f' but this causes pixel roundoff errors which
  ;; cause the grids not to line up correctly.
  (chart-line 0 (-f (progn (delta-y-in-window (chart-vertical-device-range)
					      current-image-y-scale)))))

;;; `tick-mark-part-to-draw' tells the axis-tick-mark data-point-indicator which combination
;;; of grids and tickmarks to draw. If NIL both are drawn. If 'grid only grids are drawn.
;;; If 'tick-mark only the tickmarks are drawn. This exists so that we can draw the grids
;;; before the tickmarks so that the grids don't overwrite the tickmarks and their labels.

(defvar tick-mark-part-to-draw nil)

(define-chart-data-point-indicator axis-tick-mark ()
  (let ((draw-grid-p (or (null tick-mark-part-to-draw) (eq tick-mark-part-to-draw 'grid)))
	(draw-tick-p (and
		       (or (null tick-mark-part-to-draw) (eq tick-mark-part-to-draw 'tick-mark))
		       (not (=f axis-tickmark-label-frequency 0)))))	
    (cond ((=f axis-tickmark-count-as-fixnum 0)
	   (when draw-tick-p
	     ;; Ensure that the axis is drawn even if no tickmarks are requested
	     (chart-move-to data-point-x data-point-y)					      
	     (case axis-heading
	       (east  (chart-full-line-east))
	       (north (chart-full-line-north)))))
	  ((<=f data-point-index axis-tickmark-count-as-fixnum)	; is this still needed???
	   (let* ((tick-amount (constant-value
				 (if (eq axis-heading 'east)
				     data-point-tuple-1
				     data-point-tuple-2)))
		  label left top right bottom
		  (tick-mark-length 4)	; todo: compute as half char-width
		  (long-tick-p nil)
		  (label-offset     4)	; todo: ditto (orthogonal offset (whitespace) between tickmark label and axis)
		  (origin-correction 0)
		  (first-tick? (null data-point-last-x))
		  (whole-size    axis-tickmark-label-max-digits-before-point)
		  (fraction-size axis-tickmark-label-max-digits-after-point)
		  (expt-size     axis-tickmark-label-max-digits-in-exponent)
		  fixed-field-width?)
	     
	     (when (and draw-tick-p
			(or (=f data-point-index 1)
			    (and (=f 0 (modf-positive (1-f data-point-index) axis-tickmark-label-frequency))
				 (not (<f (-f axis-tickmark-count-as-fixnum data-point-index) axis-tickmark-label-frequency)))
			    (and (=f data-point-index axis-tickmark-count-as-fixnum)
				 (not (<f data-point-index axis-tickmark-label-frequency)))))
	       (setq long-tick-p t)
	       (setq fixed-field-width?
		     (+f whole-size fraction-size expt-size
			 (if (>f fraction-size 0) 1 0)	; decimal-point = `.' 
			 (if (>f expt-size     0) 1 0)))	; exponent-marker = `e'
               (if (and
		     (= tick-amount 0.0)
		     (>= fixed-field-width? 3)
		     (= expt-size 0)
		     axis-is-discrete-p)
		   (setf fixed-field-width? 2))
	       (setq label (twith-output-to-text-string
			     (write-floating-point-number
			       tick-amount
			       whole-size
			       fraction-size
			       nil		; precision (ignored in new writer)
			       nil		; suppress-trailing-zeros-p
			       ;; force-any-number-into-exponential-p iff we desire scientific notation
			       (>f expt-size 0)
			       ;; The following should be NIL.  See Bug HQ-5059601 which has SD:
			       ;; "Numerically small axis tickmark labels generated by roundoff
			       ;; error sometimes display as ##### or as small non-zero floats
			       ;; instead of as 0.0 .".  The NIL setting fixes this. - jpg 7/26/05
			       nil		; force-small-number-into-exponential-p
			       ;; fixed-exponent-subfield-width?
			       (and fixed-field-width?
				    (-f fixed-field-width? whole-size
					(if (>f fraction-size 0) (1+f fraction-size) 0)	; - 1 for decimal point `-'
					(if (>f     expt-size 0) 1 0)))	; - 1 for exponent marker `e'
			       ;; fixed-field-width? (i.e. maximum number of char's we desire in printed representation)
			       fixed-field-width?
			       #.%\#)))		; over-or-underflow-char
	       
	       (multiple-value-setq (left top right bottom)
		 (compute-bounding-rectangle-of-text label)))
	     
	     (chart-move-to data-point-x data-point-y)
	     
	     ;; Note that we explicitly draw the axis below instead of the previous approach which depending upon
	     ;; it being drawn via data-series-connect-first-and-last-point = t for default-axis-data-series-instance
	     ;; because the latter approach does not extend the axis to the full device drawing range
	     ;; if there is not a tickmark at the end of the axis.
	     
	     (case axis-heading
	       (north
		;; Draw the axis if this is the first tickmark (cf. comment above `case')
		(when (and first-tick? draw-tick-p)
		  (without-updating-chart-point
		    (with-chart-pen-color formatted-part-true-line-color
		      (chart-full-line-north))))
		;; Draw the tickmark or grid line
		(without-updating-chart-point
		  (cond (grid-visible
			 (when draw-grid-p
			   (chart-move-to (delta-x-in-window chart-left-margin current-image-x-scale)
					  chart-pen-y)
			   (with-chart-pen-color grid-color
			     (chart-full-line-east))))
			(t (when draw-tick-p
			     (setf tick-mark-length (delta-x-in-window tick-mark-length current-image-x-scale))
			     (when long-tick-p (incff tick-mark-length 1))
			     (chart-line tick-mark-length 0)))))
		;; Draw any tickmark label
		(when (and label draw-tick-p)
		  (setf label-offset (delta-x-in-window label-offset current-image-x-scale))
		  (chart-move (-f 0 label-offset right)
			      ;; Don't move this up a pixel since then any minus sign might blend in with the grid
			      (-f (truncatef (+f top bottom) 2)))
		  (chart-draw-text label)))
	       (east
		;; For a discrete vertical axis (one whose labels are integers 0,1,2,...) shift
		;; the first tickmark label (= 0) on the horizontal axis right by half a char so
		;; that it doesn't overwrite the vertical axis. That this usually is prettier
		;; depends upon the fact that we usually have enough empty space between labels
		;; to rightshift such a label of length 1 char. In general tickmark labels are
		;; longer and doing this shift would overlap the next label.
		;; todo: this correction should also only happen if the north axis extends below,
		;; i.e. if east axis axis-crossover != north axis-minimum but this is not a cheap
		;; predicate because we don't have a pointer to the north axis at this point.
		(when (and first-tick? axis-is-discrete-p)
		  (setf origin-correction (1+f (delta-x-in-window (truncate tickmark-label-char-width)
								  current-image-x-scale))))
		;; The rest is precisely analogous to the vertical axis case above.
		;; Draw the axis if this is the first tickmark (cf. comment above `case')
		(when (and first-tick? draw-tick-p)
		  (without-updating-chart-point
		    (with-chart-pen-color formatted-part-true-line-color
		      (chart-full-line-east))))
		;; Draw the tickmark or grid line
		(without-updating-chart-point
		  (cond (grid-visible
			 (when draw-grid-p
			   (chart-move-to chart-pen-x
					  (delta-y-in-window (-f chart-bottom chart-bottom-margin) current-image-y-scale))
			   (with-chart-pen-color grid-color
			     (chart-full-line-north))))
			(t (when draw-tick-p
			     (setf tick-mark-length (delta-y-in-window tick-mark-length current-image-y-scale))
			     (when long-tick-p (incff tick-mark-length 1))
			     (chart-line 0 (-f tick-mark-length))))))
		;; Draw any tickmark label
		(when (and label draw-tick-p)
		  (setf label-offset (delta-y-in-window label-offset current-image-y-scale))
		  (chart-move (+f (-f (truncatef (+f left right) 2)) origin-correction)
			      (+f label-offset (-f top)))
		  (chart-draw-text label)))
	       #+development
	       (otherwise
		(error "Invalid axis-heading ~A" axis-heading)))
	     
	     (when label (reclaim-text-string label)))))))


;;; `truncate-tickmark-label' truncates `label', a text string, to fit in a
;;; field of width `axis-tickmark-label-max- digits-before-point'.  This is
;;; called to truncate horizontal axis tickmark labels in which case the
;;; truncation width `width' is the max tickmark label width allowed along the
;;; horizontal axis (cf. `update-the-computed-annotations').  If integer? is
;;; true then the tickmark label has an integral value and we print only the
;;; digits before the decimal point.  Note that this does NOT attempt to do any
;;; rounding.  That is the job of the floating point writer.

(defun truncate-tickmark-label (label width integer?)

  (twith-output-to-text-string

    (loop for i from 0 to (1-f (minf (text-string-length label) width))
	  as char = (charw label i)
	  until (and integer? (char=w char #.%\.))
	  do (twrite-char char))))


;;; `align-tickmark-label' adjusts `label' with appropriate padding so that its decimal point
;;; and exponential marker are aligned relative to the max field widths (for the digits before
;;; and after the decimal point and the exponent) computed by `update-the-computed-annotations'.

(defun align-tickmark-label (label)

  ;; Get the `whole, fraction, expt' sizes (no. of digits) of the floating-point string `label'
  
  (multiple-value-bind (whole fraction expt) (float-string-field-widths label)

    (twith-output-to-text-string

      ;; Get the maximum precomputed widths allowed for the whole,fraction,expt fields of tickmark labels
      ;; along the current axis.  These were computed previously by `update-the-computed-annotations'.

      (let ((max-before axis-tickmark-label-max-digits-before-point)
	    (max-after  axis-tickmark-label-max-digits-after-point)
	    (max-expt   axis-tickmark-label-max-digits-in-exponent))

	;; Write the digits before the decimal point in a field of width `whole' 

	(loop with pad = (-f max-before whole)
	      repeat (if (>=f pad 0)
			 pad
			 ;; If pad < 0 then max-before < whole which means that our heuristic (see the
			 ;; end of the function update-the-computed-annotations) for bounding the size
			 ;; of the axis tickmark label digits before the decimal point is incorrect.
			 (progn 
			   #+ignore (cerror "Ignore this error (this is always safe)"
					    "Inconsistency detected while aligning a tickmark label")
			   0))
	   do (twrite-char #.%space)
	   finally
	     ;; note that the max/min below will truncate the leftmost digits in label if it doesn't fit
	     (loop for i upfrom (maxf 0 (-f pad))
		   repeat (minf max-before whole)
		do (twrite-char (charw label i))))

	;; Write the decimal point and following fractional digits in a field of width `fraction'
	
	(when (>f max-after 0)
	  (twrite-char #.%\.)
	  (loop for i upfrom (1+f whole)	; + 1 is for decimal point `.'
		repeat (minf max-after fraction)
	     do (twrite-char (charw label i)))
	  (loop repeat (maxf 0 (-f max-after fraction))	; right-pad the fractional part with zeros
	     do (twrite-char #.%\0)))

	;; Finally, write the exponent field, including the exponent marker `e', in a field of width `max-expt'
	
	(when (>f max-expt 0)

	  ;; Note that by allowing the following code to execute when expt = 0 we implicitly
	  ;; handle the rare case when some tickmark labels are in scientific notation
	  ;; and this label is not (i.e. the labels span the range where twrite-float switches
	  ;; to scientific notation). For now we just convert this label to scientific notation by
	  ;; padding with an exponent `e00..'  A better way to do this would be to figure out
	  ;; how to force twrite-float to always obey our field widths (and perhaps force
	  ;; uniformity of notation (scientific vs. nonscientific) along any axis). Note that we
	  ;; now use the new float writer and ask it to force scientific notation so mixed notations
	  ;; should not occur anymore.
	  
	  (twrite-char #.%\e)			; perhaps we should get this from `label' in case if is `d' or `f' or ...
	  (loop repeat (-f max-expt expt)	; left-pad the exponent with zeros
	     do (twrite-char #.%\0))
	  (loop for i upfrom (+f whole 1 (if (>f fraction 0) (1+f fraction) 0)) ; + 1 is for exponent marker `e'
		repeat (minf max-expt expt)
	     do (twrite-char (charw label i))))))))


;;; The when the indicator data-point-indicator is encountered during scanning
;;; `enter-data-point-indicator' and `exit-data-point-indicator' are called to
;;; keep `data-point-indicator-projection-function' in sync.

(defun-simple enter-data-point-indicator-1 (new-value)
  (part-stack-push data-point-indicator part-feature-recall-stack)
  (setf data-point-indicator new-value)
  (setf data-point-indicator-projection-function 
	(or (chart-data-point-indicator new-value)
	    (chart-data-point-indicator 'triangle)))
  nil)

(defun-simple exit-data-point-indicator-1 ()
  (let ((new-value (part-stack-pop part-feature-recall-stack)))
    (setf data-point-indicator new-value)
    (setf data-point-indicator-projection-function 
	  (or (chart-data-point-indicator new-value)
	      (chart-data-point-indicator 'triangle))))
  nil)




;;;; Gallery of Chart Types






(define-chart-style line-chart-style
		    '(chart
		       subparts
		       (axis ((axis axis-heading east )
			      (axis axis-heading north)))
		       
		       subpart-defaults
		       (data-series
			 ((data-series
			    data-series-connect-first-and-last-point nil
			    data-series-illustration-kind simple-scatter-plot
						; color black
			    ))
			 chart-data-point
			 ((chart-data-point 
			    width  5 ; this is odd so that it will be centered around a connecting line
			    height 5 ; ditto
			    data-point-indicator square
			    data-point-show-indicator nil
			    data-point-show-connecting-line t)))
		       ;; These are set to get the axis labels enough space assuming they are in the default font.
		       ;; These values are later recomputed by `compute-axis-tickmark-label-field-widths' appropriately
		       chart-left-margin 50
		       chart-top-margin 10
		       chart-right-margin 25
		       chart-bottom-margin 23
		       line-color black
		       background-color white
		       text-color black
		       text-size small
		       ))



(define-chart-style scatter-chart-style
      '(chart
	 subparts
	 (axis ((axis axis-heading east )
		(axis axis-heading north)))
	 
	 subpart-defaults
	 (data-series
	   ((data-series
	      data-series-connect-first-and-last-point nil
	      data-series-illustration-kind simple-scatter-plot
	      ; color black
	      ))
	   chart-data-point
	   ((chart-data-point
	      width  5 ; this is odd so that it will be centered around a connecting line
	      height 5 ; ditto
	      data-point-indicator square
	      data-point-show-indicator t
	      data-point-show-connecting-line nil)))
	 ;; These are set to get the axis labels enough space assuming they are in the default font.
	 ;; These values are later recomputed by `compute-axis-tickmark-label-field-widths' appropriately
	 chart-left-margin 50
	 chart-top-margin 10
	 chart-right-margin 25
	 chart-bottom-margin 23
	 line-color black
	 background-color white
	 text-color black
	 text-size small
	 ))

; (validate-part-instance 'chart simple-scatter-chart)



;(define-chart-style simple-chart-style
;      '(chart
;	 subparts
;	 (axis ((axis axis-heading east )
;		(axis axis-heading north)))
	 
;	 subpart-defaults
;	 (data-series
;	   ((data-series
;	      data-series-connect-first-and-last-point nil
;	      data-series-illustration-kind simple-scatter-plot
;	      ; color black
;	      ))
;	   chart-data-point
;	   ((chart-data-point 
;	      width  5 ; this is odd so that it will be centered around a connecting line
;	      height 5 ; ditto
;	      data-point-indicator bar
;	      data-point-show-indicator t
;	      data-point-show-connecting-line nil)))
;	 chart-left-margin 50			; These are set to get the axis labels enough space. ??
;	 chart-top-margin 10
;	 chart-right-margin 25
;	 chart-bottom-margin 23
;	 line-color black
;	 background-color white
;	 text-color black
;	 ))

; (validate-part-instance 'chart simple-bar-chart)


(define-chart-style column-chart-style
      '(chart
	 subparts
	 (axis ((axis axis-heading east )
		(axis axis-heading north)))
	 
	 subpart-defaults
	 (data-series
	   ((data-series
	      data-series-connect-first-and-last-point nil
	      data-series-illustration-kind simple-scatter-plot
	      ; color black
	      ))
	   chart-data-point
	   ((chart-data-point 
	      width  7
	      height 4 ; ignored
	      data-point-indicator column
	      data-point-show-indicator t
	      data-point-show-connecting-line nil)))
	 ;; These are set to get the axis labels enough space assuming they are in the default font.
	 ;; These values are later recomputed by `compute-axis-tickmark-label-field-widths' appropriately
	 chart-left-margin 50			
	 chart-top-margin 10
	 chart-right-margin 25
	 chart-bottom-margin 23
	 line-color black
	 background-color white
	 text-color black
	 text-size small
	 ))

; (validate-part-instance 'chart simple-column-chart)






;;;; Routines that are in immedate support of project-chart.



;;; Compute-chart-statistics scans the data points of the
;;; chart and computes some statistical information that
;;; is then used to guide some of the layout.  For example
;;; if the axis are automatic then the range of data values
;;; is used to guide the selection of ranges.

(defun compute-chart-statistics ()
  ;; Compute the range spanned by the data values
  (with-temporary-gensym-float-creation compute-chart-statistics-1
    (let ((first-data-point-flag t))
      (with-chart
	(do-data-series 
	  (do-data-points
	    (let ((t1 (constant-value data-point-tuple-1))
		  (t2 (constant-value data-point-tuple-2)))
	      (cond
		(first-data-point-flag
		 (setf first-data-point-flag nil)
		 (store-constant-value chart-tuple-1-minimum t1)
		 (store-constant-value chart-tuple-1-maximum t1)
		 (store-constant-value chart-tuple-2-minimum t2)
		 (store-constant-value chart-tuple-2-maximum t2))
		(T
		 (store-constant-value
		   chart-tuple-1-minimum
		   (mine (constant-value chart-tuple-1-minimum) t1))
		 (store-constant-value
		   chart-tuple-1-maximum
		   (maxe (constant-value chart-tuple-1-maximum) t1))
		 (store-constant-value 
		   chart-tuple-2-minimum
		   (mine (constant-value chart-tuple-2-minimum) t2))
		 (store-constant-value 
		   chart-tuple-2-maximum 
		   (maxe (constant-value chart-tuple-2-maximum) t2)))))))))))


;;; `Assure-chart-transform-is-uptodate' computes the transform function from
;;; data tuples to device coordinates, if necessary.  This routine will
;;; need to be a lot more sophisticated.   For now it presumes a simple
;;; X-Y plot with one horizontal and one vertical axis.  No transposition
;;; of the data tuples.  The ranges of the axis is given, and not automaticly
;;; bound.

;;; `Transform-data-tuple-to-device-coordinates' does:
;;;   data-point-{x,y}
;;;       <- transform * data-point-tuple-{1,2}

(defun transform-data-tuple-to-device-coordinates ()
  (with-temporary-gensym-float-creation transform-data-tuple-to-device-coordinates 
    (set-after-translation-via-transform-matrix
      data-point-x                 	      data-point-y
      (constant-value data-point-tuple-1)   (constant-value data-point-tuple-2)
      ;; this last arg of `t' means round results to fixnums
      t)))


(defun assure-chart-transform-is-uptodate ()
  (let (horizontal-axis-minimum horizontal-axis-maximum
	vertical-axis-minimum   vertical-axis-maximum)
    (with-temporary-gensym-float-creation  assure-chart-transform-is-uptodate
      (with-chart
	(do-axis
	  (case axis-heading
	    (north
	     (setf vertical-axis-maximum   (slot-value-number-value-as-float axis-maximum))
	     (setf vertical-axis-minimum   (slot-value-number-value-as-float axis-minimum)))
	    (east
	     (setf horizontal-axis-maximum (slot-value-number-value-as-float axis-maximum))
	     (setf horizontal-axis-minimum (slot-value-number-value-as-float axis-minimum))))))
      (let ((chart-horizontal-device-range (chart-horizontal-device-range))
	    (chart-vertical-device-range   (chart-vertical-device-range))
	    (chart-horizontal-axis-range 
	      (-e horizontal-axis-maximum horizontal-axis-minimum))
	    (chart-vertical-axis-range
	      (-e vertical-axis-maximum vertical-axis-minimum)))
	(indentity-transform-matrix)
	(scale-transform-matrix
	  (/e (coerce-to-gensym-float current-image-x-scale) 
	      (coerce-to-gensym-float (normalized-scale)))
	  (/e (coerce-to-gensym-float current-image-y-scale)
	      (coerce-to-gensym-float (normalized-scale))))
	(offset-transform-matrix 
	  (coerce-to-gensym-float chart-left-margin)
	  (coerce-to-gensym-float (+f chart-vertical-device-range chart-top-margin)))
	(scale-transform-matrix 1.0 -1.0)
	(scale-transform-matrix
	  (/e (coerce-to-gensym-float chart-horizontal-device-range)
	      chart-horizontal-axis-range)
	  (/e (coerce-to-gensym-float chart-vertical-device-range)
	      chart-vertical-axis-range))
	(offset-transform-matrix (-e horizontal-axis-minimum) (-e vertical-axis-minimum))))))



#+development ; see also `describe-the-transform'
(defun show-transform (x)
  (with-temporary-gensym-float-creation show-transform
    (block nil
      (format t x)
      (format t "~20T")
      (dotimes (i 6)
	(format t " ~7,3F" (extract-cached-number (aref the-transform i))))
      
      (let (x y)
	(set-after-translation-via-transform-matrix x y 0.0 0.0)
	(format t " 0,0->~7,3F,~7,3F" x y))
      (let (x y)
	(set-after-translation-via-transform-matrix x y 1.0 1.0)
	(format t " 1,1->~7,3F,~7,3F" x y)))))


;;;; Draw chart


(defun project-chart ()
  (with-chart-drawing
    ;; Set background color of the already erased graph rendering
    (setf (grid-background-color-value current-graph-rendering)
	  (map-color-or-metacolor-to-color-value
	    (or (get-simple-part-feature (annotations current-chart-frame) 'background-color)
		'white)))
    ;; Note: the `delta-<>-in-window's have been distributed into the `-f's below because this better
    ;; matches the arithmetic that is used in drawing the background--thus avoiding roundoff error
    ;; during scaling. If you distribute them outward then roundoff errors will cause the chart border
    ;; to occasionally mismatch the edge of the background by a pixel--which looks ugly. A similar
    ;; scaling rounding problem still remains in the dragging code: if you drag a chart to a new location
    ;; it may have analogous border/background edge mismatches. However, the problem goes away once the
    ;; chart is updated (so that this problem is probably local to the dragging code).
    
    (let ((width  (-f (delta-x-in-window (right-edge-of-block  current-chart-frame) current-image-x-scale)
		      (delta-x-in-window (left-edge-of-block   current-chart-frame) current-image-x-scale)))
	  (height (-f (delta-y-in-window (bottom-edge-of-block current-chart-frame) current-image-y-scale)
		      (delta-y-in-window (top-edge-of-block    current-chart-frame) current-image-y-scale))))
      (cond
	((or (not (runnable-p current-chart-frame))
	     (not (computed-annotations current-chart-frame)))
	 (let* ((w1 (round width  12))
		(h1 (round height 12))
		(w2 (*f 10 w1))
		(h2 (*f 10 h1)))
	   (chart-frame-rectangle 0 0 width height)
	   (chart-move-to (+f w1 w1) h1)
	   (chart-line 0 h2)
	   (chart-move  (-f w1) (-f h1))
	   (chart-line w2 0)))
	(T
	 (with-chart

	   ;; Draw the background, if necessary.
	   (when chart-current-raster-is-polychrome-p
	     (chart-pen-color (text-cell-background-color? current-text-box-format))
	     (chart-fill-rectangle 0 0 width height))

	   ;; Draw the char border
	   (chart-pen-color (or (text-box-border-color? current-text-box-format) 'black))
	   (chart-frame-rectangle 0 0 width height)
	   
	   (let ((data-series-subparts (data-series current-chart-frame))
		 chart-origin-x  ;; set by side effect during axis draw.
		 chart-origin-y  ;; Ditto.
		 (grids-visible nil))
	     
	     (chart-pen-color formatted-part-true-line-color)
	     
	     ;; Set up transforms.
	     (assure-chart-transform-is-uptodate)

	     ;; Note if any grid is visible (this uses an inlined DO-AXIS for efficiency)
	     (setq grids-visible
		   (or grid-visible
		       (loop for axis in (get-subpart-collection (computed-annotations current-chart-frame) 'subparts 'axis)
			     thereis (get-simple-part-feature axis 'grid-visible))))
	     
	     ;; Draw the Axes, Tickmarks and Grids.  If there are grids visible, draw the grids before drawing the
	     ;; tickmarks so that the tickmarks and their labels are not overwritten by the grids.
	     (if grids-visible
		 (let ((tick-mark-part-to-draw 'grid))
		   (chart-pen-color formatted-part-true-line-color)
		   (do-axis
		     (funcall (data-series-projection-method data-series-illustration-kind)))
		   ;; Draw the data series (under the tick marks)
		   (do-data-series
		     (chart-pen-color formatted-part-true-line-color)
		     (funcall (data-series-projection-method data-series-illustration-kind)))
		   (setq tick-mark-part-to-draw 'tick-mark)
		   (do-axis
		     (funcall (data-series-projection-method data-series-illustration-kind))))	     
		 (progn
		   (do-axis
		     (chart-pen-color formatted-part-true-line-color)
		     (funcall (data-series-projection-method data-series-illustration-kind)))
		   ;; Draw the data series (under the tick marks)
		   (do-data-series
		     (chart-pen-color formatted-part-true-line-color)
		     (funcall (data-series-projection-method data-series-illustration-kind)))
		   
		   (let ((tick-mark-part-to-draw 'tick-mark))
		     (do-axis
		       (funcall (data-series-projection-method data-series-illustration-kind)))))))
	   ))))))

;; Background color is set here, rather than in graph-rendering allocation, since
;; that is that natural thing to do when we switch over to polychrome rasters.


;;; Chart-colors returns a graph list of the color values that are needed to
;;; draw this chart.  The caller should reclaim that list when done with it.

(defun chart-colors ()
  (let ((result (graph-list)))
    (setf result (chart-colors-1 result (annotations current-chart-frame)))
    (setf result (chart-colors-1 result default-axis-data-series-instance))
    (setf result (chart-colors-1 result 
				 (chart-part-description-for-chart-style
				   (chart-style current-chart-frame))))
    result))

(defun chart-colors-1 (colors-so-far part-description)
  (loop
    for (feature-name feature-value)
	on (rest part-description)
	by #'cddr
    do
    (case feature-name
      ((subparts subpart-defaults subpart-exceptions)
       (loop for (nil subpart-collection)
	     on feature-value
		 by #'cddr
	     do
	 (loop for subpart in subpart-collection
	       do (setf colors-so-far (chart-colors-1 colors-so-far subpart)))))
      (otherwise
       (when (memq feature-name '(color text-color line-color grid-color border-color))
	 (graph-pushnew (map-color-or-metacolor-to-color-value feature-value) colors-so-far)))))
  colors-so-far)

;;; `Project-chart-call-back' is called by the interpreter of a
;;; graph's line drawing description, upon encountering the
;;; opcode chart-call-back.

(defun project-chart-call-back (graph-rendering current-chart-raster-color-value) ; maybe "value?" ???
  (with-named-dynamic-extent working-on-chart ((current-chart-frame
						 (corresponding-graph-grid-or-chart? graph-rendering)))
    (with-named-dynamic-extent working-on-lexical-computation-of-frame
        ((*current-computation-frame* current-chart-frame))
      (project-chart))))







;;;; Grammar, Slot Writer, and Slot Compilers for the Chart Class


;;;; Grammar, Slot Writer, and Slot Compiler for the chart-style


;;; Chart style is one of an enumerated list of chart styles,
;;; analogous to a gallery selection in Excel.  The dictionary
;;; of these is filled out set-up-chart-dictionaries-if-necessary.

(add-grammar-rules
  '((chart-style unreserved-symbol)))

(def-slot-value-writer chart-style (chart-style)
  (twrite-symbol chart-style))

(def-slot-value-compiler chart-style (parse-result)
  (cond
    ((not (in-directory-of-names-p parse-result 'chart-style))
     (values bad-phrase (tformat-text-string "~S is not a known style for a chart" parse-result)))
    (T
     parse-result)))


(define-category-evaluator-interface (chart-style
				       :access read-write)
    (member line-chart-style column-chart-style scatter-chart-style)
  ((set-form (evaluation-value))
   evaluation-value)
  ((get-form (slot-value))
   slot-value))


;;; The data-series slot is a list of data-series part descriptions.
;;; Only the data-series-source-kind, data-series-info-1, and
;;; data-series-info2 currenly appear in these descriptions.

(add-grammar-rules-for-list
  'data-series-descriptions 'data-series-description
  '\; nil 'none)

(add-grammar-rules
  '((data-series-description g2-list-pair-series)

    ;; example: "Plot L1 versus L2"
    (g2-list-pair-series
      ('plot unique-designation 'versus unique-designation)	; other lists??
      (data-series 
	data-series-source-kind pair-of-g2-quantity-lists
        data-series-info-1 4
	data-series-info-2 2))
    
    ;; example: "Plot L1"
    (data-series-description data-series-of-one-g2-quantity-list)
    (data-series-of-one-g2-quantity-list
      ('plot unique-designation)
      (data-series
	data-series-source-kind one-g2-quantity-list
        data-series-info-1 2))))

;;; The slot value writer for `data-series-descriptions' uses print-designation
;;; on the embedded data series.  It is notable that these can be the output
;;; of compile-expression or the parse tree.  The second case happens only if
;;; the user attempted to use local names in the designation.

(def-slot-value-writer data-series-descriptions (data-series-descriptions)
  (cond
    ((null data-series-descriptions)
     (twrite-symbol 'none))
    (T
     (loop for (data-series . remainder?) on data-series-descriptions
	   as kind   = (get-simple-part-feature data-series 'data-series-source-kind)
	   as info-1 = (get-simple-part-feature data-series 'data-series-info-1)
	   as info-2 = (get-simple-part-feature data-series 'data-series-info-2)
	   do
       (tformat "plot ")
       (case kind
	 (pair-of-g2-quantity-lists
	  (print-designation info-2)
	  (tformat " versus ")
	  (print-designation info-1))
	 (one-g2-quantity-list
	  (print-designation info-1)))
       (when remainder? (tformat ";~%"))))))


;;; Plot-designation-may-not-contain-local-names notifies the user if the
;;; designation he provided for a data series contained local names.  This
;;; is noticed by applying compile expression to the parse, and then noticing
;;; that the compilation result was wrapped in a LET form.

(def-frame-note-writer plot-designation-may-not-contain-local-names (particulars)
  (declare (ignore particulars))
  (tformat "local names are not supported in data series."))



;;; Data-series-descriptions applies compile-expression to the embedded
;;; designations of data series found in each plot.  This may create frame
;;; notes so we setup component particulars.  This routine is directly responsible
;;; for the frame note plot-designation-may-not-contain-local-names.

;;; It is notable that after this the data-series-info features may contain
;;; either a compiled expression or a unique designation parse.  The
;;; data-series-failed-to-compile indicates which.

(def-slot-value-compiler data-series-descriptions (parse-result chart)
  (declare (use-for-default-overrides))
  (let (compilation-result bad-phrase?)
    (cond
      ((eq 'none parse-result)
       (setf compilation-result nil))
      (t
       (with-named-dynamic-extent working-on-annotated-frame
				  ((current-annotated-frame chart))
	 (with-updates-to-representations-supressed (chart 'frame-status-and-notes)
	   ;; Remove all frame notes that this routine can put in the frame
	   ;; from any component-particulars that reference the data series.
	   (loop with *current-computation-frame* = chart
		 with component-particulars-with-frame-notes = (component-particulars-with-frame-notes)
		 finally (reclaim-slot-value-list component-particulars-with-frame-notes)
		 for current-computation-component-particulars-1 in component-particulars-with-frame-notes
		 for current-computation-component-particulars =  
		     (copy-for-slot-value current-computation-component-particulars-1)
		 when (and (consp current-computation-component-particulars)
			   (eql 'data-series (car current-computation-component-particulars)))
		   do
		     (delete-frame-note-if-any
		       'plot-designation-may-not-contain-local-names
		       chart)
		     (delete-all-frame-notes-for-rule-or-expression nil)
		 do (reclaim-slot-value current-computation-component-particulars))
	   ;; Compile each of the designations in the plots, marking them as
	   ;; failing if compile-expression fails, or if it makes the designation into
	   ;; an expression.
	   (loop 
              with *current-computation-frame* = chart
	     with current-computation-component-particulars = (slot-value-list 'data-series 0)
	     finally (reclaim-slot-value-list current-computation-component-particulars)
	     for data-series in (rest parse-result)
	     as data-series-index from 1
	     do (setf (second current-computation-component-particulars) data-series-index)
	     as designation-1 = (copy-for-phrase (get-simple-part-feature data-series 'data-series-info-1))
	     as designation-2? = (copy-for-phrase (get-simple-part-feature data-series 'data-series-info-2))
	     as compilation-1? = (compile-expression designation-1 nil nil)
	     as compilation-2? = (when designation-2?
				   (compile-expression designation-2? nil nil))
	     do
	     (macrolet ((designation-compiled-into-an-expression-p 
			  (compiled-expression)
			  `(and 
			     (consp ,compiled-expression)
			     (eql 'let (car-of-cons ,compiled-expression)))))
	       (when (or (and compilation-1?
			      (designation-compiled-into-an-expression-p compilation-1?))
			 (and designation-2?
			      compilation-2?
			      (designation-compiled-into-an-expression-p compilation-2?)))
		 (setf compilation-1? nil)
		 (setf compilation-2? nil)
		 (add-frame-note 'plot-designation-may-not-contain-local-names chart))) 
	     (when (or (null compilation-1?)
		       (and designation-2? 
			    (null compilation-2?)))
	       (set-simple-part-feature
		 data-series 'data-series-failed-to-compile
		 t))
	     (if compilation-1?
		 (set-simple-part-feature-without-reclaiming
		   data-series 'data-series-info-1
		   compilation-1?))
	     (when compilation-2?
	       (set-simple-part-feature-without-reclaiming 
		 data-series 'data-series-info-2
		 compilation-2?))))
	 (setf compilation-result (rest parse-result)))))
  (values compilation-result bad-phrase?)))

(define-textof-category-evaluator-interface data-series-descriptions)

;;;; Grammer, Compiler, and Writer for Parsing Chart-Annotations

;;; `Set-up-chart-dictionaries-if-necessary' sets up
;;; `part-feature' and `part-type'. 
;;; These are directories of names used in the grammar that follows.  

(defun set-up-part-dictionaries (part-type)
  ;; Empty the directories, to get a clean slate.
  (reclaim-grammar-tree-function (directory-of-names 'part-type))
  (setf (directory-of-names 'part-type) nil)
  (reclaim-grammar-tree-function (directory-of-names 'part-feature))
  (setf (directory-of-names 'part-feature) nil) 
  (reclaim-grammar-tree-function (directory-of-names 'chart-style))
  (setf (directory-of-names 'chart-style) nil)
  
  ;; Fill in the enumeration of built in chart layouts.
  (add-to-directory-of-names 'line-chart-style    'chart-style)
  (add-to-directory-of-names 'scatter-chart-style 'chart-style)
  (add-to-directory-of-names 'column-chart-style  'chart-style)
  
  ;; Add those features that appear directly on this part-type
  (loop for (nil part-feature-description)
	    on (part-type-features (part-type-description part-type))
	    by #'cddr
	when (part-feature-user-visible? part-feature-description)
	  do
	    (add-to-directory-of-names 
	      (part-feature-user-spelling part-feature-description)
	      'part-feature))
  
  ;; Will all user visible part-type names, and all user-visible attribute names
  (loop for included-part-type in (part-type-descendant-part-types part-type)
	do
    (add-to-directory-of-names 
      (part-type-user-spelling (part-type-description included-part-type))
      'part-type)
    (loop for (nil part-feature-description)
	      on (part-type-features (part-type-description included-part-type))
	      by #'cddr
	  do
      (when (part-feature-user-visible? part-feature-description)
	(add-to-directory-of-names 
	  (part-feature-user-spelling part-feature-description)
	  'part-feature)))))

;; Always sets up the dictionaries at this point.
;; This code is charting specific still.




(add-grammar-rules-for-list
  'chart-annotations 'chart-annotation
  '\; nil 'none)


(add-grammar-rules
  '((chart-annotation formatted-chart-part-annotation)
    (chart-annotation real-chart-annotation)))

(defun reduce-annotation-1 (parse)
  (rotatef (first parse) (second parse))
  (reduce-annotation parse))

(add-grammar-rules
  '(
    
    ;; LINE-COLOR 
    (formatted-chart-part-annotation 
      ('the 'line-color colored-chart-part)
      (2 . 3)
      reduce-annotation-1)
    ;; TEXT-COLOR 
    (formatted-chart-part-annotation 
      ('the 'text-color colored-chart-part)
      (2 . 3)
      reduce-annotation-1)
    ;; BACKGROUND-COLOR 
    (formatted-chart-part-annotation 
      ('the 'background-color colored-chart-part)
      (2 . 3)
      reduce-annotation-1)
    ;; BORDER-COLOR 
    (formatted-chart-part-annotation 
      ('the 'border-color colored-chart-part)
      (2 . 3)
      reduce-annotation-1)
    ;; GRID-COLOR ; todo: do this via tickmark-style
    (formatted-chart-part-annotation 
      ('the 'grid-color colored-chart-part)
      (2 . 3)
      reduce-annotation-1)

    (formatted-chart-part-annotation 
      ('the 'grid-visible 'is boolean)
      (current-part-description 2 4) 
      reduce-annotation)
    
    ;; stuff in common to colored parts.
    (colored-chart-part
      ('is color-or-metacolor) 
      (current-part-description 2))
    (colored-chart-part
      ('of chart-part-pattern 'is color-or-metacolor)
      (2 4))
    
    ;; TEXT-SIZE
    (formatted-chart-part-annotation
      ('the 'text-size 'is text-size-kind)
      (current-part-description 2 4) 
      reduce-annotation)
    (formatted-chart-part-annotation
      ('the 'text-size 'of chart-part-pattern 'is text-size-kind)
      (4 2 6)
      reduce-annotation)
    
    ;; TEXT-ALIGNMENT
    (formatted-chart-part-annotation
      ('the 'text-alignment 'is text-alignment-kind)
      (current-part-description 2 4) 
      reduce-annotation)
    (formatted-chart-part-annotation
      ('the 'text-alignment 'of chart-part-pattern 'is text-alignment-kind)
      (4 2 6)
      reduce-annotation)
    
    ;; HEIGHT
    (formatted-chart-part-annotation 
      ('the 'height dimensioned-chart-part)
      (2 . 3)
      reduce-annotation-1)
    (formatted-chart-part-annotation 
      ('the 'width dimensioned-chart-part)
      (2 . 3)
      reduce-annotation-1)
    ;; WIDTH 
    (dimensioned-chart-part
      ('= number) 
      (current-part-description 2))
    (dimensioned-chart-part
      ('of chart-part-pattern '= number)
      (2 4))))

(add-grammar-rules
  '(

    ;; INDICATOR
    (real-chart-annotation
      ('the 'indicator 'of chart-part-pattern 'is indicator-kind)
      (4 2 6)
      reduce-annotation)
    (indicator-kind 'rectangle)
    (indicator-kind 'triangle)
    (indicator-kind 'square)
    (indicator-kind 'cross)
    (indicator-kind 'x)
    (indicator-kind 'column)
    (indicator-kind 'bar)
    (indicator-kind 'solid-column)
    (indicator-kind 'solid-bar)

    
    ;; INDICATOR-VISIBLE
    (real-chart-annotation
      ('the 'indicator-visible boolean-chart-subpart-feature)
      (2 . 3)
      reduce-annotation-1)

    ;; CONNECTION-LINE-VISIBLE
    (real-chart-annotation
      ('the 'connection-line-visible boolean-chart-subpart-feature)
      (2 . 3)
      reduce-annotation-1)

    ;; LINE-FROM-LAST-TO-FIRST-POINT-VISIBLE
    (real-chart-annotation
      ('the 'line-from-last-to-first-point-visible boolean-chart-subpart-feature)
      (2 . 3)
      reduce-annotation-1)

    ;; Boolean chart subpart feature
    (boolean-chart-subpart-feature
      ('of chart-part-pattern 'is boolean)
      (2 4))

    ;; AXIS-MINIMUM
    (real-chart-annotation
      ('the 'axis-minimum numeric-chart-subpart-feature)
      (2 . 3)
      reduce-annotation-1)

    (real-chart-annotation
      ('the 'number-of-significant-digits numeric-chart-subpart-feature)
      (2 . 3)
      reduce-annotation-1)

    ;; AXIS-CROSSOVER
    (real-chart-annotation
      ('the 'axis-crossover numeric-chart-subpart-feature)
      (2 . 3)
      reduce-annotation-1)

    ;; AXIS-MAXIMUM
    (real-chart-annotation
      ('the 'axis-maximum numeric-chart-subpart-feature)
      (2 . 3)
      reduce-annotation-1)

    ;; NUMBER-OF-TICKMARKS
    (real-chart-annotation
      ('the 'number-of-tickmarks numeric-chart-subpart-feature)
      (2 . 3)
      reduce-annotation-1)

    ;; TICKMARK-INTERVAL
    (real-chart-annotation
      ('the 'tickmark-interval numeric-chart-subpart-feature)
      (2 . 3)
      reduce-annotation-1)

    ;; numeric chart subpart feature
    (numeric-chart-subpart-feature
      ('of chart-part-pattern '= number)
      (2 4))

    ;; GRID-VISIBLE
    (real-chart-annotation
      ('the 'grid-visible boolean-chart-subpart-feature)
      (2 . 3)
      reduce-annotation-1)

    ))

;(add-grammar-rules
;  '(
;    ;; Annotations on direct features of the chart.
;    ;; "the background-color is blue"
;    (chart-annotation ('the part-feature 'is annotation-symbol)
;		      (current-part-description 2 4) reduce-annotation)
;    ;; "the margin-width = 10"
;    (chart-annotation ('the part-feature '= number)
;		      (current-part-description 2 4) reduce-annotation)
    
;    ;; Annotations on component parts of a chart.
;    ;; the color of data-series 2 is red
;    (chart-annotation ('the part-feature 'of chart-part-pattern 'is annotation-symbol)
;		      (4 2 6) reduce-annotation)
;    ;; the axis-minimum of any axis = 0.0
;    (chart-annotation ('the part-feature 'of chart-part-pattern '= number)
;		      (4 2 6) reduce-annotation)

;    (annotation-symbol symbol)
;    (part-feature      unreserved-symbol)
    
;    ))

(add-grammar-rules
  '(
    ;; parts of parts.
    ;; "any point of data-series 1"
    (chart-part-pattern ('any part-type 'of chart-part-pattern)
			(lookup-subpart-of-collection 
			  4
			  'subpart-defaults
			  '(get-internal-spelling 2 part-type)
			  nil)
			fix-up-parse-upon-reduction)
    ;; "point 3 of data-series 2"
    (chart-part-pattern (part-type number 'of chart-part-pattern)
			(lookup-subpart-of-collection 
			  4
			  'subpart-exceptions
			  '(get-internal-spelling 1 part-type)
			  2)
			fix-up-parse-upon-reduction)

    ;; Denoting a part or set of parts.
    ;;  "any data-series"
    (chart-part-pattern ('any part-type)
			(lookup-subpart-of-collection 
			  current-part-description
			  'subpart-defaults
			  '(get-internal-spelling 2 part-type)
			  nil)
			fix-up-parse-upon-reduction)
    ;; "point 3"
    (chart-part-pattern (part-type integer)
			(lookup-subpart-of-collection 
			  current-part-description
			  'subpart-exceptions
			  '(get-internal-spelling 1 part-type)
			  2)
			fix-up-parse-upon-reduction)

    (part-type         unreserved-symbol)

    ))





(def-slot-value-compiler chart-annotations (parse-result chart)
  (declare (use-for-default-overrides))
  (let (result error-message?)
    (with-named-dynamic-extent working-on-annotated-frame
			       ((current-annotated-frame chart))
      (multiple-value-setq (result error-message?)
	(compile-part-description parse-result 'chart)))
    (values result error-message?)))


;;; The writer for the compiled form of a chart-annotation must handle
;;; the case of a nil in the slot.  In addition it scans to chart
;;; part template and calls write-annotation-part-pattern on each of
;;; the collections of part templates that set up the inherited settings.

(def-slot-value-writer chart-annotations (annotations-slot-value)
  (write-part-description annotations-slot-value))







;;;; Chart Annotations Attribute Export/Import







(defun-simple make-evaluation-value-based-on-type-and-slot-presence (plist slot-name)
  (let ((member-result (memq slot-name plist)))
    (if member-result
	(make-evaluation-value-based-on-type (second member-result))
	nil)))

;;; `set-attributes-if-necessary'
;;; Takes a list of external attribute names.
(defmacro set-attributes-if-necessary (attribute-list attribute-plist)
  (flet ((remove-% (symbol)
	   (let ((name (symbol-name symbol)))
	     (if (char= (char name 0) #\%) ; see `with-evaluation-structure-slots'
		 (intern (subseq name 1))
	       symbol))))
    `(progn
       ,@(loop for attribute-name in attribute-list
	       collect
	       `(setf-non-nil ,attribute-name
			      (make-evaluation-value-based-on-type-and-slot-presence
				,attribute-plist
				(get-internal-spelling ',(remove-% attribute-name) 'part-feature)))))))

(define-category-evaluator-interface (chart-features
				       :access read-write)
    (structure chart-features-spec
	       ((line-color (named color-or-metacolor))
		(text-color (named color-or-metacolor))
		(background-color (named color-or-metacolor))
		(border-color (named color-or-metacolor))
		(grid-color (named color-or-metacolor))
		(grid-visible truth-value)
		(text-alignment symbol)
		(text-size symbol)
		(width number)
		(height number)
		(indicator symbol)
		(indicator-visible truth-value)
		(connection-line-visible truth-value)
		(line-from-last-to-first-point-visible truth-value)
		(axis-minimum number)
		(axis-maximum number)
		(axis-crossover number)
		(number-of-tickmarks number)
		(tickmark-interval number)
		(number-of-significant-digits number))
	       (or line-color text-color background-color
		   border-color grid-color grid-visible
		   text-alignment text-size
		   width height
		   indicator indicator-visible
		   connection-line-visible
		   line-from-last-to-first-point-visible
		   axis-minimum axis-maximum axis-crossover
		   number-of-tickmarks tickmark-interval number-of-significant-digits))
  ((set-form (chart-features))
   (loop with list-of-features = nil
	 for (feature-name . feature-value)
	     being each evaluation-structure-pair of chart-features
	 do
     (setf list-of-features
	   (phrase-cons
	     (phrase-list
	       (phrase-list 'QUOTE (get-internal-spelling feature-name 'part-feature))
	       (phrase-list 'COPY-FOR-SLOT-VALUE
			    (phrase-list 'QUOTE
					 (cond
					   ((evaluation-truth-value-p feature-value)
					    (evaluation-truth-value-is-true-p feature-value))
					   (t
					    (copy-if-evaluation-value feature-value))))))
	     list-of-features))
	 finally
	   (return list-of-features)))
  ((get-form (slot-value))
   ;; NOTE: for the %-prefix, please see `with-evaluation-structure-slots'
   (with-new-structure (chart-features-spec)
     (set-attributes-if-necessary
       (line-color
	 text-color background-color
	 border-color %grid-color %grid-visible
	 text-alignment text-size
	 width height
	 indicator indicator-visible
	 connection-line-visible
	 line-from-last-to-first-point-visible
	 %axis-minimum %axis-maximum %axis-crossover
	 number-of-tickmarks tickmark-interval %number-of-significant-digits)
       slot-value))))
		

(define-category-evaluator-interface (feature-path
				       :access read-write)
    (sequence (structure path-part
			 ((part-name (or (member chart-data-point data-series axis)
					 symbol))
			  (part-index number))
			 (and part-name))
	      1)
  
  ((set-form (feature-path))
   (loop with internal-path = 'CURRENT-PART-DESCRIPTION
	 for path-element
	     being each evaluation-sequence-element of feature-path
	 do
     (with-structure (path-element path-part)
       (setq internal-path
	     (phrase-list
	       'LOOKUP-SUBPART-OF-COLLECTION
	       internal-path
	       ;; NOTE: for the %-prefix, please see `with-evaluation-structure-slots'
	       (phrase-list 'QUOTE (if %part-index
				       'SUBPART-EXCEPTIONS
				       'SUBPART-DEFAULTS))
	       (phrase-list 'QUOTE part-name)
	       (copy-if-evaluation-value %part-index))))
;     (break)
	 finally
	;   (break)
	   (return internal-path)))
  ((get-form ())))


(define-category-evaluator-interface (chart-annotation
				       :access read-write)
    (structure annotation-spec
	       ((attributes (named chart-features))
		(path (named feature-path)))
	       (and attributes))
  
  ((set-form (evaluation-value))
   (with-safe-category-setter-calling
       (with-structure (evaluation-value annotation-spec)
	 (import-attributes attributes path))))
  ((get-form ())))

;;; `import-attributes'
;;; attributes is a structure with type-def given by 'chart-features.
;;; path is a sequence with type-def given by 'feature-path, or nil.
;;; Returns a list of annotaions.
;;; Does not consume attributes or path.

(defun import-attributes (attributes &optional path)
  (with-safe-category-setter-calling
      (loop with list-of-features
	      = (call-category-setter-safely 'chart-features attributes)
	    with internal-path
	      = (if path
		    (call-category-setter-safely 'feature-path path)
		    'CURRENT-PART-DESCRIPTION)
	    for (prev-feature . cdr) on list-of-features
	    while cdr
	    do
	(setf (car cdr)
	      (phrase-cons
		'SET-SIMPLE-PART-FEATURE
		(phrase-cons
		  (copy-tree-using-phrase-conses internal-path)
		  (car cdr))))
	    finally
	      (setf (car list-of-features)
		    (phrase-cons
		      'SET-SIMPLE-PART-FEATURE
		      (phrase-cons
			(copy-tree-using-phrase-conses internal-path)
			(car list-of-features))))
	      (return list-of-features))))


(define-category-evaluator-interface (chart-annotations-sequence
				       :access read-write)
    (sequence (named chart-annotation)
	      1)
  
  ((set-form (annotations))
   (with-safe-category-setter-calling
       (loop with list-of-annotations = nil
	     for chart-annotation
		 being each evaluation-sequence-element of annotations
	     as new-annotations
		= (call-category-setter-safely 'chart-annotation chart-annotation)
	     do
	 (setf list-of-annotations
	       (nconc new-annotations list-of-annotations))
	     finally
	       (return list-of-annotations))))
  ((get-form (slot-value))
   (allocate-evaluation-sequence
     (subpart-features slot-value nil))))



;;; `attributes-defined-p'
;;; Returns true iff chart-attributes are defined
;;; at the top level of the subpart-list.

(defmacro attributes-defined-p (subpart-list)
  `(let ((exceptions?
	   (getfq ,subpart-list 'subpart-exceptions))
	 (defaults?
	     (getfq ,subpart-list 'subpart-defaults))
	 (part-index?
	   (getfq ,subpart-list 'part-index)))
     (or (and (null exceptions?) (null defaults?))
	 (and exceptions? defaults?
	      (>f (length ,subpart-list)
		  (if part-index? 6 4)))
	 (and (or (null exceptions?) (null defaults?))
	      (>f (length ,subpart-list)
		  (if part-index? 4 2))))))
	 

;;; `subpart-features'
;;; Recurses throught the subpart hierarchy and
;;; exports an EVAL LIST of annotation structures,
;;; from which the user can allocate a sequence.
;;; (see type-def for chart-annotation)

;;; Does not consume subpart-list.
;;; Consumes path.

(defun subpart-features (subpart-list path)
  (let ((subpart-defaults
	  (getfq subpart-list 'subpart-defaults))
	(subpart-exceptions
	  (getfq subpart-list 'subpart-exceptions))
	(attributes
	  (when (attributes-defined-p subpart-list)
	    (call-category-getter 'chart-features
				  subpart-list nil nil)))
	(result nil))
    (when subpart-defaults
      (loop for (part values) on subpart-defaults by 'cddr
	    do
	(loop for value in values
	      do
	  (setf result
		(nconc (subpart-features
			 (cdr value)
			 (eval-cons
			   (allocate-evaluation-structure-inline
			     'part-name part)
			   (copy-list-using-eval-conses path)))
		       result)))))
    (when subpart-exceptions
      ;(break)
      (loop for (part values) on subpart-exceptions by 'cddr
	    do
	;(break "here1")
	(loop for value in values
	      do
	  ;(break "here2")
	  (setf result
		(nconc (subpart-features
			 (cdr value)
			 (eval-cons
			   (allocate-evaluation-structure-inline
			     'part-name part
			     'part-index (copy-if-evaluation-value
					   (getfq (cdr value) 'part-index)))
			   (copy-list-using-eval-conses path)))
		       result)))))
    (cond (attributes
	   (eval-push
	     (if path
		 (allocate-evaluation-structure-inline
		   'attributes attributes
		   'path
		   (allocate-evaluation-sequence (nreverse path)))
		 (allocate-evaluation-structure-inline
		   'attributes attributes))
	     result))
	  (t
	   (reclaim-eval-list path)))
    result))

(defun set-chart-annotation-root-denotation (feature subpart-type &optional index?)
  (cond ((eq (cadr feature) 'CURRENT-PART-DESCRIPTION)
	 (setf (cadr feature)
	       (phrase-list 'LOOKUP-SUBPART-OF-COLLECTION
			    'CURRENT-PART-DESCRIPTION
			    (phrase-list 'QUOTE
					 (if index?
					     'SUBPART-EXCEPTIONS
					     'SUBPART-DEFAULTS))
			    (phrase-list 'QUOTE subpart-type)
			    index?)))
	((consp (cadr feature))
	 (set-chart-annotation-root-denotation (cadr feature) subpart-type index?))
	(t
	 nil)))

(define-category-evaluator-interface (chart-data-point-features
				       :access read-write)
    (structure chart-data-point-features-spec
	       ((annotations (named chart-annotations-sequence)))
	       (and annotations))
  
  ((set-form (evaluation-value))
   (with-safe-category-setter-calling
       (with-structure (evaluation-value chart-data-point-features-spec)
	 (loop with internal-annotations
		 = (call-category-setter-safely 'chart-annotations-sequence annotations)
	       for annotation in internal-annotations
	       do
	   (set-chart-annotation-root-denotation annotation 'chart-data-point)
	       finally
		 (return internal-annotations)))))
  ((get-form (slot-value))
   (with-new-structure (chart-data-point-features-spec)
     (setf annotations (call-category-getter 'chart-annotations-sequence
					  (cdr slot-value) nil nil)))))

(define-category-evaluator-interface (chart-data-series-features
				       :access read-write)
    (structure chart-data-series-features-spec
	       ((index integer)
		(annotations (named chart-annotations-sequence)))
	       (and annotations))
  
  ((set-form (evaluation-value))
   (with-safe-category-setter-calling
       (with-structure (evaluation-value chart-data-series-features-spec)
	 (loop with internal-annotations
		 = (call-category-setter-safely 'chart-annotations-sequence annotations)
	       for annotation in internal-annotations
	       do
	   (set-chart-annotation-root-denotation annotation 'data-series index)
	       finally
		 (return internal-annotations)))))
  ((get-form (slot-value))
   (with-new-structure (chart-data-series-features-spec)
     (setf-non-nil index
		   (copy-if-evaluation-value (getfq (cdr slot-value) 'part-index)))
     (setf annotations (call-category-getter 'chart-annotations-sequence
					  (cdr slot-value) nil nil)))))

(define-category-evaluator-interface (chart-axis-features
				       :access read-write)
    (structure chart-axis-features-spec
	       ((index integer)
		(annotations (named chart-annotations-sequence)))
	       (and annotations))
  
  ((set-form (evaluation-value))
   (with-safe-category-setter-calling
       (with-structure (evaluation-value chart-axis-features-spec)
	 (loop with internal-annotations
		 = (call-category-setter-safely 'chart-annotations-sequence annotations)
	       for annotation in internal-annotations
	       do
	   (set-chart-annotation-root-denotation annotation 'axis index)
	       finally
		 (return internal-annotations)))))
  ((get-form (slot-value))
   (with-new-structure (chart-axis-features-spec)
     (setf-non-nil index
		   (copy-if-evaluation-value (getfq (cdr slot-value) 'part-index)))
     (setf annotations (call-category-getter 'chart-annotations-sequence
					     (cdr slot-value) nil nil)))))

(define-category-evaluator-interface (chart-data-point-features-sequence
				       :access read-write)
    (sequence (named chart-data-point-features)
	      1)
  
  ((set-form (features-sequence))
   (with-safe-category-setter-calling
       (loop with list-of-features = nil
	     for features-element
		 being each evaluation-sequence-element of features-sequence
	     do
	 (setf list-of-features
	       (nconc
		 (call-category-setter-safely 'chart-data-point-features
					      features-element)
		 list-of-features))
	 finally
	       (return list-of-features))))
  ((get-form (slot-value))
   (when slot-value
     (with-list-to-evaluation-sequence-mapping (slot-value element)
       (call-category-getter 'chart-data-point-features element nil nil)))))

(define-category-evaluator-interface (chart-data-series-features-sequence

				       :access read-write)
    (sequence (named chart-data-series-features)
	      1)
  
  ((set-form (features-sequence))
   (with-safe-category-setter-calling
       (loop with list-of-features = nil
	     for features-element
		 being each evaluation-sequence-element of features-sequence
	     do
	 (setf list-of-features
	       (nconc
		 (call-category-setter-safely 'chart-data-series-features
					      features-element)
		 list-of-features))
	 finally
	       (return list-of-features))))
  ((get-form (slot-value))
   (when slot-value
     (with-list-to-evaluation-sequence-mapping (slot-value element)
       (call-category-getter 'chart-data-series-features element nil nil)))))

(define-category-evaluator-interface (chart-axis-features-sequence
				       :access read-write)
    (sequence (named chart-axis-features)
	      1)
  
  ((set-form (features-sequence))
   (with-safe-category-setter-calling
       (loop with list-of-features = nil
	     for features-element
		 being each evaluation-sequence-element of features-sequence
	     do
	 (setf list-of-features
	       (nconc
		 (call-category-setter-safely 'chart-axis-features
					      features-element)
		 list-of-features))
	 finally
	       (return list-of-features))))
  ((get-form (slot-value))
   (when slot-value
     (with-list-to-evaluation-sequence-mapping (slot-value element)
       (call-category-getter 'chart-axis-features element nil nil)))))





(defun combine-lists-into-one-eval-list (l1 l2)
  (loop with l3 = (nreverse (copy-list-using-eval-conses l1))
	for elt in l2
	do
    (eval-push elt l3)
	finally
	  (return (nreverse l3))))

(defmacro subpart-defaults (chart-annotations)
  `(getfq (cdr ,chart-annotations) 'subpart-defaults))

(defmacro subpart-exceptions (chart-annotations)
  `(getfq (cdr ,chart-annotations) 'subpart-exceptions))

(define-category-evaluator-interface (chart-annotations
				       :access read-write)
    (or (no-item)
	(structure chart-annotations-spec
		   ((default-features (named chart-features))
		    (data-point-features (named chart-data-point-features-sequence))
		    (data-series-features (named chart-data-series-features-sequence))
		    (axis-features (named chart-axis-features-sequence)))
		   (or default-features 
		       data-point-features
		       data-series-features
		       axis-features)))
  
  ((set-form (evaluation-value))
   (with-safe-category-setter-calling
     (evaluation-etypecase
	 evaluation-value
	 ((no-item) nil)
	 ((structure)
	  (with-structure (evaluation-value chart-annotations-spec)
	    (let ((chart-default-features
		    (and default-features
			 (import-attributes default-features)))
		  (chart-data-point-features
		    (and data-point-features
			 (call-category-setter-safely 'chart-data-point-features-sequence
						      data-point-features)))
		  (chart-data-series-features
		    (and data-series-features
			 (call-category-setter-safely 'chart-data-series-features-sequence
						      data-series-features)))
		  (chart-axis-features
		    (and axis-features
			 (call-category-setter-safely 'chart-axis-features-sequence
						      axis-features))))
	      (phrase-cons
		'\;
		(nconc
		  chart-default-features
		  (nconc chart-data-point-features
			 (nconc chart-data-series-features
				chart-axis-features))))))))))
  ((get-form (slot-value))
   (when slot-value
     (let* ((subpart-defaults (subpart-defaults slot-value))
	    (subpart-exceptions (subpart-exceptions slot-value))
	    (default-features-internal
		(when (or (and (null subpart-defaults) (null subpart-exceptions)
			       (>f (length slot-value) 2))
			  (and (or (null subpart-defaults) (null subpart-exceptions))
			       (>f (length slot-value) 4))
			  (and subpart-defaults subpart-exceptions
			       (>f (length slot-value) 5)))
		  (cdr slot-value)))
	    (chart-data-point-defaults (getfq subpart-defaults 'chart-data-point))
	    (axis-defaults (getfq subpart-defaults 'axis))
	    (data-series-defaults (getfq subpart-defaults 'data-series))
	    (axis-exceptions (getfq subpart-exceptions 'axis))
	    (data-series-exceptions (getfq subpart-exceptions 'data-series))
	    (chart-data-point-features-internal chart-data-point-defaults)
	    (chart-axis-features-internal
	      (combine-lists-into-one-eval-list axis-defaults axis-exceptions))
	    (chart-data-series-features-internal
	      (combine-lists-into-one-eval-list data-series-defaults data-series-exceptions)))
       (when (or default-features-internal chart-data-point-features-internal
		 chart-data-series-features-internal chart-axis-features-internal)
	 (with-new-structure (chart-annotations-spec)
	   (setf-non-nil default-features
			 (when default-features-internal
			   (call-category-getter 'chart-features
						 default-features-internal nil nil)))
	   (setf-non-nil data-point-features
			 (call-category-getter 'chart-data-point-features-sequence
					       chart-data-point-features-internal nil nil))
	   (setf-non-nil data-series-features
			 (call-category-getter 'chart-data-series-features-sequence
					       chart-data-series-features-internal nil nil))
	   (setf-non-nil axis-features
			 (call-category-getter 'chart-axis-features-sequence
					       chart-axis-features-internal nil nil))
	   (reclaim-eval-list chart-axis-features-internal)
	   (reclaim-eval-list chart-data-series-features-internal)))))))

;;;; Virtual attribute for getting the "real" bounds of an axis

(def-virtual-attribute chart-axis-computed-details
    ((class chart)
     (or (no-item)
	 (structure
	   ((axis-1
	      (structure
		((axis-is-discrete truth-value)
		 (max-digits-in-exponent integer)
		 (max-digits-before-point integer)
		 (max-digits-after-point integer)
		 (axis-heading symbol)
		 (axis-crossover float)
		 (minimum float)
		 (maximum float))
		(and minimum maximum)))
	    (axis-2
	      (structure
		((axis-is-discrete truth-value)
		 (max-digits-in-exponent integer)
		 (max-digits-before-point integer)
		 (max-digits-after-point integer)
		 (axis-heading symbol)
		 (axis-crossover float)
		 (minimum float)
		 (maximum float))
		(and minimum maximum))))
	   (and axis-1 axis-2)))
     ())
  :event-updates nil
  :initial
  ((class) (declare (ignore class)) nil)
  :getter
  ((chart)
   (let ((computed-annotations? (computed-annotations chart)))
     (if computed-annotations?
	 (allocate-evaluation-structure-inline
	   'axis-1 (build-axis-bounds-structure chart computed-annotations? 0)
	   'axis-2 (build-axis-bounds-structure chart computed-annotations? 1))
	 nil))))

(defun-simple build-axis-bounds-structure (chart computed-annotations axis-number)
  (let ((requested-axis (get-subpart-of-collection
			  computed-annotations
			  'subparts
			  'axis
			  axis-number)))
    (with-named-dynamic-extent working-on-chart
	((current-chart-frame chart))
      (with-named-dynamic-extent working-on-lexical-computation-of-frame
	  ((*current-computation-frame* chart))
	(with-temporary-gensym-float-creation whatever
	  (let* ((axis-crossover
		   (get-simple-part-feature-as-float requested-axis 'axis-crossover))
		 (axis-minimum
		   (get-simple-part-feature-as-float requested-axis 'axis-minimum))
		 (axis-maximum
		   (get-simple-part-feature-as-float requested-axis 'axis-maximum))
		 (axis-is-discrete
		   (fixnum-case axis-number
		     (0 (plot-east-axis-label-tickmarks-as-integers-p current-chart-frame))
		     (1 (plot-north-axis-label-tickmarks-as-integers-p current-chart-frame))
		     (t #+development
			(cerror "Continue" "unknown axis number ~S" axis-number)
			nil)))
		 (max-digits-in-exponent
		   (get-simple-part-feature
		     requested-axis 'axis-tickmark-label-max-digits-in-exponent))
		 (max-digits-before-point
		   (get-simple-part-feature
		     requested-axis 'axis-tickmark-label-max-digits-before-point))
		 (max-digits-after-point
		   (get-simple-part-feature
		     requested-axis 'axis-tickmark-label-max-digits-after-point))
		 (structure
		   (allocate-evaluation-structure-inline
		     'axis-is-discrete (make-evaluation-boolean-value axis-is-discrete)
		     'axis-heading (get-simple-part-feature requested-axis 'axis-heading)
		     'axis-crossover (make-evaluation-float axis-crossover)
		     'axis-minimum (make-evaluation-float axis-minimum)
		     'axis-maximum (make-evaluation-float axis-maximum))))
	    ;; the following are given null checks, since the chart code that initially
	    ;; build the requested-axis does not include these initially, but adds
	    ;; them later.
	    (when max-digits-in-exponent
	      (setf (evaluation-structure-slot structure 'max-digits-in-exponent)
		    (make-evaluation-integer max-digits-in-exponent)))
	    (when max-digits-before-point
	      (setf (evaluation-structure-slot structure 'max-digits-before-point)
		    (make-evaluation-integer max-digits-before-point)))
	    (when max-digits-after-point
	      (setf (evaluation-structure-slot structure 'max-digits-after-point)
		    (make-evaluation-integer max-digits-after-point)))
	    structure))))))

;;;; Virtual attribute for getting data to plot

(def-virtual-attribute chart-data-series
    ((class chart)
     (or (no-item)
	 (sequence
	   (structure
	     ((data-series-cache-1
		(sequence float 0))
	      (data-series-cache-2
		(sequence float 0))
	      (data-series-source-kind (member axis-data-series malformed-data-series
					       float-and-float-from-data-caches)))
	     (and data-series-cache-1 data-series-cache-2 data-series-source-kind))
	   0))
     ())
  ;; actually only kind of within putter: there should be another
  ;; key one could use here
  :event-updates :within-putter
  :initial
  ((class) (declare (ignore class)) nil)
  :getter
  ((chart)
   (let ((data-series (get-subpart-collection (computed-annotations chart) 'subparts 'data-series)))
     (if data-series
	 (loop for data-series-element in data-series
	       collect (build-data-series-structure data-series-element)
		 into series-list
		 using eval-cons
	       finally
		 (return
		   (allocate-evaluation-sequence series-list)))))))

(defun-simple build-data-series-structure (data-series-element)
  (allocate-evaluation-structure-inline
    'data-series-cache-1
    (make-evaluation-sequence-from-managed-float-array
      (get-simple-part-feature data-series-element 'data-series-data-cache-1?))
    'data-series-cache-2
    (make-evaluation-sequence-from-managed-float-array
      (get-simple-part-feature data-series-element 'data-series-data-cache-2?))
    'data-series-source-kind
    (get-simple-part-feature data-series-element 'data-series-source-kind)))

(defun-simple make-evaluation-sequence-from-managed-float-array (managed-float-array)
  (if managed-float-array
    (allocate-evaluation-sequence
      (loop for index from 0 below (managed-float-array-length managed-float-array)
	    collect (make-evaluation-float (managed-float-aref managed-float-array index))
	      using eval-cons))))



;;;; The Draw Method for Charts



;;; `Draw for chart' ...

(def-class-method draw (chart)
  (cond
    ((block-is-currently-being-dragged-p chart)
     ;; Note that drawing an opaque block will LOSE if attempted
     ;; when the block is being transferred, since the block
     ;; will not be in the subblock stack (for opaque blocks).
     (draw-block-outline-in-current-image-plane chart 'foreground)) ; was black (MHD 11/11/93)
    (t
     (let ((current-graph-rendering (get-or-make-graph-rendering-for-chart chart)))
       (when (or (icp-window-p current-window)
                 (and current-graph-rendering
                      (graph-rendering-structure? current-graph-rendering)
                      (raster-or-rasters (graph-rendering-structure? current-graph-rendering))))
         (with-background-color-value
             (grid-background-color-value current-graph-rendering)
           (clear-data-clipping-rectangles)
           (draw-current-graph-rendering
             (x-in-window (left-edge-of-block   chart))
             (y-in-window (top-edge-of-block    chart))
             (x-in-window (right-edge-of-block  chart))
             (y-in-window (bottom-edge-of-block chart))))))))
; The drawing harness now does this.
;  (draw-subblocks chart)
  )

;; The call to clear-data-clipping-rectangles is part of a the protocol
;; for using graph renderings.  I'll admit I don't fully understand that
;; protocol, since I'd assume that since I never set these I'd never 
;; need to clear them, but apparently graphs maintain them in using
;; a if you care set 'em explicitly style rather than in a if you change
;; 'em change 'em back style. - ben 2/11/92







;;;; Slot Putters that Cause Updating



;;; `Update-chart' ...

;;; `Update-chart' is called when ever you want to recompute a chart from
;;; scratch.  It is the substanative part of the update action, and procedure
;;; statement.  Update chart proceeds by discarding the
;;; information stored about the chart, i.e. the rasters and the computed
;;; annotations.  It then updates the computed annotations.  Finally it
;;; asks to have the chart's images drawn, and that will recreate the
;;; currently needed rasters.  The chart may, or may not, be active.

(defun-simple update-chart (chart)
  (with-named-dynamic-extent working-on-annotated-frame
			     ((current-annotated-frame chart))
    ;; Update the KB state.
    (update-the-computed-annotations chart)
    ;; Flush the renderings no matter what, but
    ;; don't erase the screen.
    (erase-chart chart nil)
    ;; Draw a refreshed version
    (unless (block-is-currently-being-dragged-p chart)
      (draw-images-of-block chart t))))

(defun refresh-images-of-chart (chart)
  (update-chart chart))
;; ?? Kludge


;;; `Erase-chart' decaches all cached renderings of chart, and, if
;;; erase-renderings? is true, erases all images of chart.  Except
;;; in the case of renderings on printer windows.  These renderings
;;; cannot be modified in the middle of printing.  They will be
;;; cleaned up (deleted) when the printer-window is deleted.

(defun erase-chart (chart erase-renderings?)
  (when erase-renderings?
    (erase-images-of-block chart T))	; Assumes it doesn't depend on old value.
  (loop with copy-of-renderings =
	  (copy-list-using-eval-conses
	    (graph-renderings-for-chart chart))
	for rendering in copy-of-renderings
	unless (printing-window-p
		 (window-for-graph-rendering rendering))
	  do
	    (decache-graph-rendering rendering)
	finally
	  (reclaim-eval-list copy-of-renderings)))


;;; `Recompute-and-draw-chart' will draw a chart from scratch.  Starting first
;;; with recomputing the chart's layout (margins, axis, etc), and then drawing
;;; the chart onto the screen.  This is rarely called directly, usually 
;;; update-chart is called to do this.

(defun recompute-and-draw-chart (chart)
  (update-the-computed-annotations chart)
  (draw-images-of-block chart t))

(defun update-the-computed-annotations (chart)
  (check-memory-for-development
    'update-the-computed-annotations-a)
  (with-named-dynamic-extent working-on-chart
      ((current-chart-frame chart))
    ;; Discard the old value.
    (change-slot-value chart 'computed-annotations nil)
    (when (runnable-p chart)
      (with-simulated-chart-drawing 
	(let*
	    ;; This is a template for our result
	    ((chart-annotations (annotations chart))
	     (requested-horizontal-axis
	      (get-subpart-of-collection chart-annotations 'subpart-exceptions 'axis 1))
	     (requested-vertical-axis
	      (get-subpart-of-collection chart-annotations 'subpart-exceptions 'axis 2))
	     (computed-horizontal-axis 
	      (slot-value-list
		'axis 'axis-heading 'east
		'axis-minimum   (make-slot-value-float-macro 0d0)
		'axis-maximum   (make-slot-value-float-macro 10d0)
		'axis-crossover (make-slot-value-float-macro 0d0)
		'number-of-significant-digits -1))
	     (computed-vertical-axis 
	      (slot-value-list
		'axis 'axis-heading 'north
		'axis-minimum   (make-slot-value-float-macro 0d0)
		'axis-maximum   (make-slot-value-float-macro 10d0)
		'axis-crossover (make-slot-value-float-macro 0d0)
		'number-of-significant-digits -1))
	     (all-computed-data-series
	      (loop with result = ()
		    repeat (length (data-series chart))
		    do (slot-value-push 
			 (slot-value-list 'data-series)
			 result)
		    finally
		      (return result)))
	     (new-computed-annotations 
	      (slot-value-list
		'chart
		'subparts
		(slot-value-list
		  'axis  
		  (slot-value-list		; for fully bound axis
		    computed-horizontal-axis
		    computed-vertical-axis)
		  'data-series			; for data cache
		  all-computed-data-series)
		'subpart-defaults
		(slot-value-list
		  'axis
		  (slot-value-list
		    (slot-value-list
		      'axis
		      'axis-minimum   (make-slot-value-float-macro -1d0)
		      'axis-crossover (make-slot-value-float-macro  0d0)
		      'axis-maximum   (make-slot-value-float-macro 10d0)
		      )))
		'grid-visible (get-simple-part-feature chart-annotations 'grid-visible)
		'grid-color (or (get-simple-part-feature chart-annotations 'grid-color) 'black)
		)))
	  (with-some-temporary-constants-of-type-number 
	      (chart-tuple-1-minimum chart-tuple-1-maximum
				     chart-tuple-2-minimum chart-tuple-2-maximum)
	    (with-named-dynamic-extent working-on-lexical-computation-of-frame
		((*current-computation-frame* current-chart-frame))
	      (let* ((data-series-subparts (data-series current-chart-frame)))
		(with-chart
		  ;; 0. Setup data caches, and make install the computed annotations.
		  (check-memory-for-development
		    'update-the-computed-annotations-0-pre)
		  (setup-chart-data-caches all-computed-data-series)
		  (change-slot-value 
		    chart
		    'computed-annotations 
		    new-computed-annotations)
		  (update-subscriptions-from-virtual-attribute-change
		    chart (virtual-attribute 'chart-data-series) nil)
 
		  ;; Compute up the axis.		  
		  ;; 1. Get some idea of the data's range.
		  (check-memory-for-development
		    'update-the-computed-annotations-1-pre)
		  (compute-chart-statistics)

		  
		  ;; 2. Compute min, and max for the horizontal and vertical axis.
		  (check-memory-for-development
		    'update-the-computed-annotations-2-pre)
		  (with-temporary-gensym-float-creation update-chart-axis-1
		    (compute-axis-bounds
		      computed-horizontal-axis
		      (if requested-horizontal-axis 
			  requested-horizontal-axis
			  '(axis))
		      (constant-value chart-tuple-1-minimum)
		      (constant-value chart-tuple-1-maximum))
		    (compute-axis-bounds 
		      computed-vertical-axis
		      (if requested-vertical-axis
			  requested-vertical-axis
			  '(axis))
		      (constant-value chart-tuple-2-minimum)
		      (constant-value chart-tuple-2-maximum))

    		    ;; Now see if the cross over points still make sense.
		    (pin-crossover-as-necessary computed-horizontal-axis computed-vertical-axis)
		    (pin-crossover-as-necessary computed-vertical-axis   computed-horizontal-axis))

		  (with-temporary-gensym-float-creation update-chart-axis-2
		    (let* ((font-structure (ab-font (or (first (text-cell-font-map current-text-box-format))
							'hm14)))

			   (tickmark-label-char-width
			     ;; original:  (MHD 10/25/93)
			     ;; We use `2' below cuz it's the only digit in hb72 (which we use for testing)
			     ;;(coerce-fixnum-to-gensym-float
			     ;;  (text-width-to-x 
			     ;;     (get-set-width-for-character #.%\2 font-structure)))
			     ;; -- corrected here not to lose fractional part of width
			     ;; -- corrected to have less specific knowledge of fonts
			     (text-width-to-float
			       (font-digit-text-width font-structure)))
			   
			   ;; `ab-font-baseline' is the offset from the top of the bounding box to the baseline.
			   ;; Note that this is guaranteed to be bigger than the height of any char in a tickmark
			   ;; label (i.e. any digit, `e' or `.').
			   ;; The 1.3 multiplier is used to give us spacing between lines.

			   (tickmark-label-min-height
			    (*e 1d3 (coerce-fixnum-to-gensym-float (ab-font-baseline font-structure))))

			   (tickmark-label-min-width
			    (*e 6d0 tickmark-label-char-width)))	; 6 chars needed in general in `-x.yez'
		      
		      ;; 3. Compute some tickmarks for this axis, and copy over formatting attributes.
		      ;; These will be recomputed by `compute-axis-tickmark-label-field-widths' below
		      ;; after the correct margins have been computed. todo: eliminate this redundancy
		      (check-memory-for-development
			'update-the-computed-annotations-3-pre)
		      (compute-axis-tickmarks-and-style requested-horizontal-axis computed-horizontal-axis)
		      (compute-axis-tickmarks-and-style requested-vertical-axis   computed-vertical-axis)
		       
		      ;; 4. Compute tickmark label minimal sizes based on range of axis and adjust (if
		      ;; needed) number of tickmarks based on how many labels will fit.
		      (check-memory-for-development
			'update-the-computed-annotations-4-pre)
		      (compute-axis-tickmark-label-field-widths
			chart requested-vertical-axis   computed-vertical-axis
			requested-horizontal-axis computed-horizontal-axis)
		      (update-subscriptions-from-virtual-attribute-change
			chart (virtual-attribute 'chart-axis-computed-details) nil)))))))))))
  (check-memory-for-development
    'update-the-computed-annotations-z))


;;; The following form defines the part text size `huge' as hb72 (the font used
;;; to display the G2 logo). This is used in development for testing that the 
;;; tickmark layout code scales appropriately for large fonts. Note that the
;;; parameters below were cloned from `program-title-format' in run.lisp.
;;; Maybe there should be a `define-part-text-size' that does roughly this?

#+debugging
(progn
  
  (push '(huge
	   (hb72)				; text-cell-font-map
	   100 ;80				; text-cell-line-height
	    72 ;54				; text-cell-baseline-position
	     0 ; 8				; text-cell-line-spacing
	   #.(convert-to-text-width 10) ;30	; default-word-spacing 
	   #.(convert-to-text-width  8) ;24	; minimum-word-spacing 
	   #.(convert-to-text-width 14) ;52	; maximum-word-spacing
	   )
	part-text-size-parameters)

  (setf (simple-type-specification 'text-size)
	`(OR ,(simple-type-specification 'text-size)
	     (member huge)))
  
  (add-grammar-rules
    '((text-size-kind 'huge)))
  )


;;; `compute-axis-tickmark-label-field-widths' computes the field widths of the tickmark labels 
;;; for each axis and installs these widths into the chart. These widths are then used to compute
;;; the chart margins, which are installed into the chart. Finally, the number of tickmarks for
;;; the horizontal axis is recomputed in case the right or left margin changed and shrunk the
;;; drawing area.

(defun compute-axis-tickmark-label-field-widths
    (chart requested-vertical-axis computed-vertical-axis requested-horizontal-axis computed-horizontal-axis)

  (with-temporary-gensym-float-creation compute-tickmark-max-sizes

    (let* (whole fraction expt
		 unaligned-size label-size size-in-chars
		 (left-margin 0) right-margin top-margin (bottom-margin 0)
		 axis other-axis device-range char-width/2 char-width
		 left-margin-from-north-axis font-structure
		 east-char-width east-tickmark-label-char-width north-tickmark-label-min-height)

      ;; For each axis, compute the field widths of its tickmark labels and install these into
      ;; the appropriate axis part features. Also, if the tickmark label extends into the margin
      ;; then increase the size of the margin. todo: margins can be made smaller if there are no
      ;; labels along north axis; also bottom margin can be smaller if no labels on east axis.

      (do-axis
	(setq font-structure (ab-font (or (first (text-cell-font-map current-text-box-format))
					  'hm14)))
	(setq tickmark-label-char-width
	      ;; original:  (MHD 10/25/93)
	      ;; We use the char `2' below cuz it's the only digit in hb72 (which we use for testing)
	      ;;(coerce-fixnum-to-gensym-float
	      ;;  (text-width-to-x (get-set-width-for-character #.%\2 font-structure)))
	      ;; -- corrected here not to lose fractional part of width
	      ;; -- corrected to have less specific knowledge of fonts
	      (text-width-to-float (font-digit-text-width font-structure)))

	;; `ab-font-baseline' is the offset from the top of the bounding box to the baseline.
	;; Note that this is guaranteed to be bigger than the height of any char in a tickmark
	;; label (i.e. any digit, `e' or `.').
	;; The 1.3 multiplier is used to give us spacing between lines.
	(setq tickmark-label-min-height
	      (*e 1.3 (coerce-fixnum-to-gensym-float (ab-font-baseline font-structure))))

	(setq char-width (ceiling tickmark-label-char-width)
	      char-width/2 (halff char-width))

	(let ((label-significant-digits
                (if (eq axis-heading 'east)
		      (get-simple-part-feature computed-horizontal-axis
					       'number-of-significant-digits)
		      (get-simple-part-feature computed-vertical-axis
					       'number-of-significant-digits))))
	  (multiple-value-setq (size-in-chars whole fraction expt)
	    (if (=f label-significant-digits -1)
		(compute-current-axis-tickmark-label-field-widths nil)
		(compute-current-axis-tickmark-label-field-widths
		  label-significant-digits))))

	(case axis-heading
	  (north (setq axis computed-vertical-axis other-axis computed-horizontal-axis
		       device-range (chart-horizontal-device-range))
		 (setq label-size (+f (*f char-width (1+f size-in-chars))	; 1+ to give 1/2 char pad at left and right
				      char-width/2))
		 (when (or (<e (slot-value-number-value-as-float axis-minimum) 0.0)
			   (<e (slot-value-number-value-as-float axis-maximum) 0.0))
		   (decff label-size char-width/2))		; minus sign is narrower than a digit
		 (when (>f fraction 0)
		   (decff label-size char-width/2))		; decimal point is narrower than a digit
		 (setq bottom-margin (maxf bottom-margin (ceiling tickmark-label-min-height)))
		 (setq north-tickmark-label-min-height tickmark-label-min-height)
		 (setq left-margin-from-north-axis char-width))
	  (east  (setq axis computed-horizontal-axis other-axis computed-vertical-axis
		       device-range (chart-vertical-device-range))
		 ;; This should really be computed from digit-height and em-square height but there is 
		 ;; currently no protocol for obtaining these font parameters.
		 (setq label-size (+f 6 (truncatef (*f 3 (ceiling tickmark-label-min-height))
						   2)))
		 (setq unaligned-size size-in-chars)
		 (setq tickmark-label-min-width
		       (*e 6.0 tickmark-label-char-width))	; 6 chars needed in general in `-x.yez'
		 (setq east-char-width char-width
		       east-tickmark-label-char-width tickmark-label-char-width)))

	(set-simple-part-features axis
				  'axis-tickmark-label-max-digits-before-point whole
				  'axis-tickmark-label-max-digits-after-point  fraction
				  'axis-tickmark-label-max-digits-in-exponent  expt)

	(let* ((crossover (get-simple-part-feature-as-float       axis 'axis-crossover))
	       (min	  (get-simple-part-feature-as-float other-axis 'axis-minimum))
	       (max	  (get-simple-part-feature-as-float other-axis 'axis-maximum))
	       (delta (-f label-size (truncate (abse (*e (/e (-e crossover min) (-e max min))
							 (coerce-to-gensym-float device-range)))))))
	  (when (>f delta 0)
	    (case axis-heading
	      (east  (setq bottom-margin (maxf bottom-margin delta)))
	      (north (setq left-margin   (maxf left-margin   delta))
		     (setq left-margin-from-north-axis left-margin))))))
      
      ;; Ensure that the left and right margins are large enough to hold half a horizontal axis
      ;; tickmark label (the first and last tickmark labels are centered below the first and last
      ;; tickmarks hence extend halfway into the left and right margins). If these final computed
      ;; values for the margins leave no space in between for the chart then truncate the margins
      ;; (and hence the tickmark labels; todo: this heuristic should be more sophisticated).
      ;; Finally install these margin values into the chart and recompute the number of tickmarks
      ;; for the horizontal axis (since growing the left and right margins may have shrunk
      ;; the chart drawing area and hence decreased the number of labels we can fit).

      (let* ((half-label-width (*f east-char-width (1+f (halff unaligned-size))))	; +1 char for left margin
	     (label-count (get-simple-part-feature computed-horizontal-axis 'axis-tickmark-count-as-fixnum)))

	(setq right-margin half-label-width)

	;; If there are no horizontal labels then we don't need to allow for a half-label in the left-margin
	
	(setq left-margin (if (>f label-count 0)
			      (maxf left-margin half-label-width)
			      left-margin-from-north-axis))

	;; If there's < 1 horizontal label then we don't need the half-label right margin

	(when (and (<=f label-count 1) (>f right-margin east-char-width))
	  (setq right-margin east-char-width))

	;; If the sum of the left and right margins exceeds the chart width then first try a layout
	;; with drawing-area = right-margin / 2 and right-margin = char-width (right-margin / 2 is
	;; the minimal width drawing area needed to fit the right half of the origin label).
	;; If this still doesn't fit set the drawing-area to char-width and divide up any remaining
	;; space between the left and right margins.

	(when (>=f (+f left-margin right-margin) (-f chart-right chart-left))
	  (if (>f (setq left-margin (-f chart-right chart-left (halff right-margin) east-char-width))
		  char-width)
	      (setq right-margin east-char-width)
	      (progn
		(setq left-margin (maxf 0 (-f chart-right chart-left east-char-width)))
		(setq left-margin (halff left-margin)
		      right-margin left-margin))))
	
	(setq tickmark-label-min-height north-tickmark-label-min-height)
	(setq tickmark-label-char-width east-tickmark-label-char-width)
	(setq top-margin (ceiling tickmark-label-min-height))

     	(set-simple-part-features (computed-annotations chart)
				  'chart-left-margin   left-margin
				  'chart-right-margin  right-margin
				  'chart-top-margin    top-margin
				  'chart-bottom-margin bottom-margin)
	
      	;; Now we must recompute the number of tickmarks that will fit on each axis based on
	;; these new values for the bounding margins.

	(let ((chart-left-margin   left-margin)		; these margin parameters are used by
	      (chart-right-margin  right-margin)	;  chart-vertical-device-range and
	      (chart-top-margin    top-margin)		;  chart-horizontal-device-range in
	      (chart-bottom-margin bottom-margin))	; compute-axis-tickmarks-and-style

	  (with-temporary-gensym-float-creation re-update-chart-axis-2
	    (compute-axis-tickmarks-and-style requested-horizontal-axis computed-horizontal-axis
					      (*e east-tickmark-label-char-width
						  (coerce-fixnum-to-gensym-float (1+f unaligned-size))))
	    (compute-axis-tickmarks-and-style requested-vertical-axis computed-vertical-axis)))))))


;;; `compute-current-axis-tickmark-label-field-widths' estimates the maximum field widths over all the
;;; tickmark labels of the current axis. This is done for both scientific and non-scientific float
;;; representation and the representation which gives the smallest maximal total width is chosen. 
;;; Four width values are returned (all widths are in units `number of characters'):
;;; value 1: the total width of the largest tickmark label
;;; value 2: the width of the largest    `whole'   part (i.e. the part before the decimal point)
;;; value 3: the width of the largest `fractional' part (i.e. the part after the decimal point, before expt marker)
;;; value 4: the width of the largest    `expt'    part (i.e. the part after the expt marker)


;;; This function has been changed to give accurate value of the fraction part
;;; of a tickmark label.     Jwang   3/25/97.

(defun compute-current-axis-tickmark-label-field-widths (significant-digits?)

  ;; The suffix `+e' vs. `-e' distinguishes those variables that hold field widths for the
  ;; printed representation of floats with vs. without expts (i.e. scientific vs.
  ;; non-scientific notation, e.g. 1.234e2 vs. 123.4 with whole,fraction,expt widths 1,3,1 vs. 3,1).
  
  (let (whole+e            fraction+e       expt+e	; max field widths when printed with expt
			   whole-e            fraction-e			; max field widths when printed without expt 
			   this-whole+e  this-fraction+e  this-expt+e	; field widths of this-tick-value with expt
			   this-whole-e  this-fraction-e			; field widths of this-tick-value without expt
			   last-whole-e  last-fraction-e			; field widths of last-tick-value with expt
			   aligned-size+e  				; max aligned-size with expt encountered so far 
			   aligned-size-e  unaligned-size-e		; max (un)aligned-size without expt encountered so far 
			   this-expt-value last-expt-value 		; fixnum value of expt of this/last-tick-value
			   last-tick-value
			   (discrete? axis-is-discrete-p))

    (macrolet ((inc-if-pluspf (x)
		 `(if (<=f ,x 0) ,x (1+f ,x))))
      
      (setq whole+e 1 fraction+e 0  expt+e 1	; min label with expt is e.g. `1e5'
	    whole-e 0 fraction-e 0		; whole or fraction (not both) width can be 0 without expt
	    unaligned-size-e 1 last-tick-value nil)
      
      ;; Estimate the tickmark labels (un)aligned field widths based on the widths of the axis maximum
      ;; and minimum.

      (loop repeat 2
	    for this-tick-value = axis-minimum then axis-maximum
	    do 
	(setq this-tick-value (slot-value-number-value-as-float this-tick-value))
	(multiple-value-setq (this-expt-value this-expt+e) (float-expt-and-size this-tick-value))
	(setq expt+e (maxf expt+e this-expt+e))
	(setq this-whole+e 1)			; we require at least 1 digit before point in scientific notation
	(when (<e this-tick-value 0.0)
	  (incff this-whole+e)			; tick < 0 so inc the number of chars before the point for minus sign
	  (setq whole+e (maxf whole+e this-whole+e)))
	(setq this-fraction+e 0)
	(if (null last-tick-value)
	    (progn (multiple-value-setq (whole-e fraction-e)
		     (float-string-field-widths-without-expt 0 this-expt-value))
		   (when (<e this-tick-value 0.0) (incff whole-e))	; account for minus sign `-'
		   (setq unaligned-size-e
			 (+f whole-e (inc-if-pluspf fraction-e))))
	    (progn
	      (setq this-fraction+e (float-discrimination-precision this-tick-value last-tick-value
								    ;; extra precision needed due to many tickmark labels between min and max
								    (floor (safe-chart-log
									     (coerce-fixnum-to-gensym-float
									       (twicef axis-tickmark-count-as-fixnum))))))
	      (setq fraction+e (maxf fraction+e this-fraction+e))
	      (multiple-value-setq (this-whole-e this-fraction-e)
		(float-string-field-widths-without-expt fraction+e this-expt-value))
	      (multiple-value-setq (last-whole-e last-fraction-e)
		(float-string-field-widths-without-expt fraction+e last-expt-value))
	      (when (<e this-tick-value 0.0) (incff this-whole-e))	; account for minus sign `-'
	      (when (<e last-tick-value 0.0) (incff last-whole-e))	; account for minus sign `-'

	      (setq whole-e (maxf whole-e this-whole-e last-whole-e))
	      (cond
		(discrete?
		 ;; The data-series-sources is of typ 'integer', the size of the fraction part of
		 ;; labels should be set to zero, unless using scientific denotation. 
		 (setq this-fraction-e 0 last-fraction-e 0 fraction-e 0))
		(t
		 (setq fraction-e (maxf fraction-e this-fraction-e last-fraction-e))))

	      (if (eq axis-heading 'east)
		  (setq unaligned-size-e
			(maxf unaligned-size-e
			      (+f this-whole-e (inc-if-pluspf this-fraction-e))
			      (+f last-whole-e (inc-if-pluspf last-fraction-e)))))))
	(setq last-tick-value this-tick-value last-expt-value this-expt-value))

      ;; inc's below are for size of decimal point `.' and size of expt marker `e'
      (setq aligned-size+e (+f whole+e (inc-if-pluspf fraction+e) (inc-if-pluspf expt+e)))
      
      ;; Finally, choose between scientific versus non-scientific representation by simply choosing
      ;; the representation which provides the smallest maximum tickmark label width. Note that we
      ;; cannot use non-scientific notation if the number of significant digits exceeds that provided
      ;; in our gensym floats (thus the checks against `maximum-significant-decimal-digits-in-gensym-float').

      (let* ((no-fraction-p (=f fraction-e 0))
	     (whole-width-adjustment?
	       (and significant-digits?
		    (if no-fraction-p
			(if (adjust-for-the-sign-p axis-minimum axis-maximum) 2 0)
			(+f (-f significant-digits? whole-e fraction-e)
			    (if (adjust-for-the-sign-p axis-minimum axis-maximum) 2 0)))))
	     (fraction-width-adjustment?
	       (and significant-digits?
		    (if no-fraction-p
			0
			(if (adjust-for-the-sign-p axis-minimum axis-maximum)
			    (-f significant-digits? whole-e fraction-e -1)
			    (-f significant-digits? whole-e fraction-e)))))
	     (adjusted-fraction+e?
	       (and significant-digits?
		    (cond ((=f fraction+e 0) 0)
			  ((<e (slot-value-number-value-as-float axis-minimum) 0.0)
			   (-f significant-digits? 1))
			  ( t (-f significant-digits? 1))))))
	(case axis-heading
	  (north
	   (setq aligned-size-e (+f whole-e (inc-if-pluspf fraction-e)))	; +1 for size of decimal point `.'
	   (cond (significant-digits?
		  (if (>=f significant-digits? (+f whole-e fraction-e))
		      (setq aligned-size+e (+f aligned-size-e whole-width-adjustment?)
			    whole+e whole-e
			    fraction+e (+f fraction-e fraction-width-adjustment?)
			    expt+e 0)
		      (setq aligned-size+e (+f aligned-size+e (-f adjusted-fraction+e? fraction+e))
			    fraction+e adjusted-fraction+e?)))
		 ((and discrete?
		       (<= (+f whole-e fraction-e) 7))
		  (setq aligned-size+e aligned-size-e
			whole+e whole-e fraction+e fraction-e expt+e 0))
		 ((<=f aligned-size-e aligned-size+e)
		  (setq aligned-size+e aligned-size-e
			whole+e whole-e fraction+e fraction-e expt+e 0))))
	  (east
	   (cond (significant-digits?
		  (if (>=f significant-digits? (+f whole-e fraction-e))
		      (setq aligned-size+e (+f unaligned-size-e whole-width-adjustment?)
			    whole+e whole-e
			    fraction+e (+f fraction-e fraction-width-adjustment?)
			    expt+e 0)
		      (setq aligned-size+e (+f aligned-size+e (-f adjusted-fraction+e? fraction+e))
			    fraction+e adjusted-fraction+e?)))
		 ((and discrete?
		       (<f (+f whole-e fraction-e) 7))
		  (setq aligned-size+e unaligned-size-e
			whole+e whole-e fraction+e fraction-e expt+e 0))
		 ((<=f unaligned-size-e aligned-size+e)
		  (setq aligned-size+e unaligned-size-e
			whole+e whole-e fraction+e fraction-e expt+e 0))))))
      (values aligned-size+e whole+e fraction+e expt+e))))


(defun-simple adjust-for-the-sign-p (axis-min axis-max)
  (let ((min (slot-value-number-value-as-float axis-min))
	(max (slot-value-number-value-as-float axis-max)))
    (cond
      ((>=e min 0d0) nil)
      ((<=e max 0d0) t)
      ((>=e (ffloore (loge (-e min) 10d0)) ;min-width
	    (ffloore (loge max 10d0))) ;max-width
       t)
      (t nil))))

;;; `write-floating-point-tickmark' returns the printed string representation of the float `number'
;;; obtained by using the new floating point writer with options specified by the self-explanatory
;;; remaining arguments.
;;; No longer needed.
;(defun write-floating-point-tickmark (number whole-size fraction-size
;				      &optional (suppress-trailing-zeros-p t) fixed-field-width?
;				      		(force-any-number-into-exponential-p t))
;  (let ()
;   (twith-output-to-text-string
;    (write-floating-point-number number whole-size fraction-size
;       nil ; precision (ignored in new writer)
;       suppress-trailing-zeros-p
;       force-any-number-into-exponential-p
;       t ; force-small-number-into-exponential-p
;       ;; fixed-exponent-subfield-width?
;       (and fixed-field-width?
;	    (-f fixed-field-width? whole-size (if (>f fraction-size 0) (1+f fraction-size) 0) 1))
;       fixed-field-width?
;       #.%\#)))) ; over-or-underflow-char

;;; `float-string-field-widths' returns the whole,fraction,expt widths of
;;; `float-string', a text string.

(defun float-string-field-widths (float-string)
  (loop with size = (text-string-length float-string)
	and dot-index and e-index and non-float? = nil
	for i from 0 below size
	as char = (charw float-string i)
     do (wide-character-case char
	  (#.%\. (setq dot-index i))
	  (#.%\e (setq e-index i)
	       (loop-finish))
	  ((#.%\+ #.%\-))
	  (t (unless (digit-char-pw char)
	       ;; here string could be +-`Inf', `Nan', or `###' etc. (see new twrite-float)
	       (setq non-float? t)
	       (loop-finish))))
     finally
       (return ;;	   whole width	  fraction width	   expt width
	 (cond ((or non-float? (and (null dot-index) (null e-index)))
		(values      size 		 0 		        0))
	       ((null e-index)
		(values    dot-index (-f  size   dot-index 1) 	        0))
	       ((null dot-index)
		(values      e-index 		 0 	      (-f size e-index 1)))
	       (t (values  dot-index (-f e-index dot-index 1) (-f size e-index 1)))))))

;;; Compute the whole and fraction sizes of the string needed to represent a float in non-scientific
;;; notation given that in scientific notation we require `precision' digits after the decimal point
;;; and an exponent of `expt' (assuming, of course, one digit before the decimal point).

(defun float-string-field-widths-without-expt (precision expt)
  (if (>=f expt 0)
      ;; need to rightshift decimal point `expt' places: add `expt' before point and subtract it after point
      (values (1+f expt) (maxf (-f precision expt) 1))
      ;; need to leftshift decimal point -`expt' places: add -`expt' after point
      (values     1	 (-f precision expt))))

;;; `float-string-signed-p' returns true if the first char of `string', a text
;;; string, is the char #.%\+ or #.%\-.

(defun float-string-signed-p (string)
  (and (>f (text-string-length string) 0)
       (wide-character-member (charw string 0) '(#.%\- #.%\+))
       t)) ; to muzzle fascist Chestnut translator

;;; `float-expt-and-size' returns the base 10 expt of `float' and the printed size of the expt (in chars).
;;; This is not always precise, e.g. on Explorers it returns an expt of 98 for 1d99 and 100 for 9.99999999999999d99
;;; but precise preserving of read-write consistency here would negatively impact performance.

(defun float-expt-and-size (float)
  (if (=e float 0d0)
      (values 0 1)
      (let* ((expt (floor (loge (abse float) 10d0)))
	     (size (if (=f expt 0)
		       1
		       (1+f (floor (log (absf expt) 10))))))
	(if (and (> expt 0)
		 (<=e (expt 10d0 (1+f expt))
		      (abse float)))
	    (setf expt (+ expt 1)))
	; added to detect the inaccuracy of the 'loge' operation and fix it if it is the
	; case. This function is called 4 times when a chart is drawn and it is only
	; called from the chart drawing code, so it should not impact the performance
	; too much. 
	(values expt (if (<f expt 0)
			 (1+f size)	; + 1 for size of minus sign `-'
			 size)))))

;;; `float-string-expt' reads the exponent following the exponent marker `e' from `string',
;;; a printed representation of a floating point number in scientific notation.

; no longer needed
;(defun float-string-expt (string)
;  (loop with length = (text-string-length string)
;	for i from 0 below length
;	finally (return 0)	; no exponent marker encountered, default to 0 (shouldn't happen)
;     do (when (char=w #.%\e (charw string i))
;	  ;; Ensure that a valid expt follows #.%\e before we invoke the reader
;	  (when (loop for j from (1+f i) below length and first = t then nil
;		      always (or (digit-char-pw (charw string j))
;				 (and first (wide-character-member (charw string j) '(#.%\- #.%\+)))))
;	    (multiple-value-bind (expt length) (read-fixnum-from-string string (1+f i) length)
;	      (return (values expt (-f length (1+f i)))))))))	; expt-value and expt-string-length


;;; `float-discrimination-precision' approximates the minimum precision needed to discriminate the
;;; floats x and y when printed in scientific notation.  Conceptually, this is a string mismatch
;;; when the floats are printed with the same expt (modulo carries, e.g.  2.0000 "matches" 1.9991
;;; upto 4 digits). `extra-precision' is any extra precision to be added due to there also being
;;; floats between x and y that will need to be discriminated.

(defun float-discrimination-precision (x y extra-precision)
  (let ((x-y (-e x y))
	min max)
    (if (<e (abse y) (abse x))
	(setq min y max x)
	(setq min x max y))
    (maxf 1	; always need at least 1 digit preceding the expt
	  (minf maximum-significant-decimal-digits-in-gensym-float
		(if (=e x-y 0d0)
		    maximum-significant-decimal-digits-in-gensym-float
		    (if (=e min 0d0)
			1
			(+f (-f (truncate (ffloore (loge (abse (/e x-y min)) 10d0))))
			extra-precision)))))))


(defun setup-chart-data-caches (all-computed-data-series)
  (loop
     ;; We can't just to a do-data-series here,
     ;; because that would make current the computed data series.
     with current-computation-component-particulars = (slot-value-list 'data-series 0)
     finally (reclaim-slot-value-list current-computation-component-particulars)
     for current-data-series in data-series-subparts
     as computed-data-series in all-computed-data-series
     as data-series-index from 1
     do (with-part-description (current-data-series)
	  (setf (second current-computation-component-particulars)
		data-series-index)
	  (let* (computed-data-series-data-cache-1?
		 computed-data-series-data-cache-2?
		 (computed-data-series-source-kind
		   (cond
		     ((eq t data-series-failed-to-compile)
		      'malformed-data-series)
		     (t
		      (case data-series-source-kind
			(one-g2-quantity-list
			 (setf computed-data-series-data-cache-2?
			       (make-float-data-cache-from-designation? data-series-info-1))
			 (when computed-data-series-data-cache-2?
			   (setf computed-data-series-data-cache-1?
				 (make-float-data-cache-for-index
				   (managed-float-array-length computed-data-series-data-cache-2? ))))
			 (if (and computed-data-series-data-cache-1?
				  computed-data-series-data-cache-2?)
			     'float-and-float-from-data-caches
			     'malformed-data-series))
			(pair-of-g2-quantity-lists
			 (setf computed-data-series-data-cache-1?
			       (make-float-data-cache-from-designation? data-series-info-1))
			 (setf computed-data-series-data-cache-2?
			       (make-float-data-cache-from-designation? data-series-info-2))
			 (if (and computed-data-series-data-cache-1?
				  computed-data-series-data-cache-2?)
			     'float-and-float-from-data-caches
			     'malformed-data-series))
			(t
			 #+development
			 (cerror "Go" "Unknown data series source kind ~S" data-series-source-kind)
			 'malformed-data-series))))))
	    (set-simple-part-features computed-data-series
	      'data-series-data-cache-1? computed-data-series-data-cache-1?
	      'data-series-data-cache-2? computed-data-series-data-cache-2?
	      'data-series-source-kind   computed-data-series-source-kind)
	    ))))

(defun make-float-data-cache-from-designation? (designation?)
  (assert-that-within-named-dynamic-extent 'working-on-lexical-computation-of-frame)
  (assert-that-not-within-named-dynamic-extent
    'on-window-with-drawing
    "Never be ~S when computing is in progress.")
  (cond
    ((null designation?)
     nil)
    (t
     (with-temporary-gensym-float-creation make-float-data-cache-from-designation?
       (let ((data-source
	       (evaluate-designation designation? nil)))
	 (cond
	   ((not data-source)
	    (write-warning-message* 1
	      (tformat "the designation, i.e. \"~ND\", did not denote anything." designation?))
	    nil)
	   ((temporary-constant-p data-source)
	    (write-warning-message* 1
	      (tformat
		"the designation, i.e. \"~ND\", denoted the ~(~a~) ~NV.  A quantity-list or quantity-array was needed."
		designation?  
		(constant-type data-source)
		(constant-value data-source)))
	    nil)
	   ((let ((class (class data-source)))
	      (not 
		(or (subclassp class 'quantity-list)
		    (subclassp class 'quantity-array))))
	    (write-warning-message* 1
	      (tformat
		"the designation, i.e. \"~ND\", denoted the ~(~a~) ~NF.  A quantity-list or quantity-array was needed."
		designation?  (class data-source) data-source))
	    nil)
	   (t
	    (loop with data-values = (serve-eval-list-of-role-values
				       '(element-iterator number)
				       data-source)
		  with length = (length data-values)
		  with data-cache = (allocate-managed-float-array length)
		   and nan-count = 0
		  for data-value in data-values
		  as i from 0
		  as value = (coerce-to-gensym-float (constant-value data-value))
		  do
	      (if (exceptional-float-p value)
		  (incff nan-count)
		  (setf (managed-float-aref data-cache i) value))
	      (reclaim-temporary-constant data-value)
		  finally
		    (when (>f nan-count 0)
		      (let ((plural-string (if (=f nan-count 1) "" "s")))
			(write-warning-message* 1
			  (tformat
			    "the designation, i.e. \"~ND\", denoted a data-series containing ~A NaN~A ~
			     (IEEE floating-point Not a Number value~A)"
			    designation?
			    (if (=f nan-count 1) "a" nan-count)
			    plural-string
			    plural-string)))
		      (return nil))
		    (reclaim-eval-list data-values)
		    (return data-cache)))))))))

(defun make-float-data-cache-for-index (length)
  (with-temporary-gensym-float-creation make-float-data-cache-for-index
    (loop with data-cache = (allocate-managed-float-array length)
	  for data-value from 1 to length
	  as i from 0
	  do 
      (setf (managed-float-aref data-cache i)
	    (coerce-to-gensym-float data-value))
      finally (return data-cache))))


;;; The `slot-putter for chart-style on a chart' just stores the
;;; value, and updates the frame notes and status.

(def-slot-putter chart-style (chart new-chart-style initializing?)
  (without-frame-notes-asserted (chart)
    (setf (chart-style chart) new-chart-style))
  (unless initializing?
    (update-chart chart))
  new-chart-style)



;;; The slot-putter for data-series removes any registrations from
;;; analyze-for-consistency, updates the slot value, and then reconsiders
;;; the frame notes.

(def-slot-putter data-series (chart new-data-series initializing?)
  (without-consistency-analysis (chart)
    (without-frame-notes-asserted (chart)
      (setf (data-series chart) new-data-series)))
  (unless initializing?
    (update-chart chart))
  new-data-series)



;;; The `slot-putter for annotations on a chart' just stores the
;;; value, and updates the frame notes and status.

(def-slot-putter annotations (chart new-annotations initializing?)
  (without-frame-notes-asserted (chart)
    (setf (annotations chart) new-annotations))
  (unless initializing?
    (update-chart chart))
  new-annotations)






;;;; Activate and Deactivate Methods for the chart.

(def-class-method activate (chart)
  (let* ((*current-computation-frame* chart)
	   (computation-style-description (get-default-computation-style-of-class))
	   (priority (get-simple-part-feature computation-style-description 'priority))
	   (initial-scan-wait-interval (get-simple-part-feature computation-style-description 'priority)))
  (unless in-suspend-resume-p
    (with-future-scheduling ((chart-initial-update-task? chart)
			     priority
			     (g2-future-interval initial-scan-wait-interval))
      (update-chart chart)))
  (funcall-superior-method chart)))

(def-class-method deactivate (chart)
  (unless in-suspend-resume-p
    (cancel-task (chart-initial-update-task? chart))
    (set-inactive chart))
  (funcall-superior-method chart)
  (unless in-suspend-resume-p
    (update-chart chart)
    (set-active chart)))



;;;; Change Size



(defun change-size-of-chart
    (chart
      left-edge-of-bounding-box  top-edge-of-bounding-box
      right-edge-of-bounding-box bottom-edge-of-bounding-box)
  (with-named-dynamic-extent working-on-annotated-frame
      ((current-annotated-frame chart))
    (let ((region-invalidation-is-preferred t)		    ; Required to handle XOR mode.
	  (delta-left-edge (-f left-edge-of-bounding-box (left-edge-of-block chart)))
	  (delta-top-edge  (-f top-edge-of-bounding-box (top-edge-of-block chart))))
      (erase-chart chart t)
      (change-edges-of-block chart
			     left-edge-of-bounding-box
			     top-edge-of-bounding-box
			     right-edge-of-bounding-box
			     bottom-edge-of-bounding-box)
      (when (and g2-has-v5-mode-windows-p
		 (not ws-protocol-handle-moves-from-edge-change-p)
		 (or (/=f delta-left-edge 0)
		     (/=f delta-top-edge 0)))
	(send-ws-representations-item-moved
	  chart delta-left-edge delta-top-edge))
      (enlarge-workspace-for-block-rectangle-if-necessary chart nil)
      (recompute-and-draw-chart chart))))

(defun restore-chart-to-normal-size (chart)
  (let* ((left   (left-edge-of-block chart))
	 (top    (top-edge-of-block  chart))
	 (right  (+f left default-chart-width))
	 (bottom (+f top  default-chart-height)))
    (change-size-of-chart chart left top right bottom)))
			  


;;;; Frame Notes and Their Maintanance

;;; The frame notes types in Charts are:
;;;   patch-instance-chart-note -- warn that the chart may not survive to new versions. (obsolete)
;;;   no-data-series-chart-note -- note that, having no data series, the chart is going to be boring.

(def-frame-note-writer patch-instance-chart-note (particulars)
  (declare (ignore particulars))
  ;; Obsolete
  ;;(tformat "this chart was made possible via a patch to G2, all charts ~
  ;;          instances may have to be discarded prior to using a new version of G2 (or the charting patch)")
  (tformat "")  ;; Read an old KB and displayed prior to recomputing the frame notes.
  )

(def-frame-note-writer no-data-series-chart-note (particulars)
  (declare (ignore particulars))
  (tformat "the chart will appear empty until some data series are specified"))



;;; `Update-frame-status-and-notes' is called by the slot putters for user editable
;;; slots.  It will reconsider the notes status of the frame, from scratch, and then
;;; if the resulting notes differ from the existing notes, then it replaces the slot
;;; value.  The analyze-for-consistency method for charts is called from here, amoung
;;; other places.  It is defined in INSTALL.

;(def-class-method update-frame-status-and-notes (chart do-analyze-for-consistency?)
;  (delete-frame-note-if-any 'patch-instance-chart-note chart)
;  (delete-frame-note-if-any 'no-data-series-chart-note chart)
;  (let ((suppress-updating-of-slot-value-representations? t))
;    ;; Obsolete: warning that they are running a patch.
;    ;; (add-frame-note 'patch-instance-chart-note chart nil t t)
;    ;; warn if no data series is provided.
;    (unless (data-series chart)
;      (add-frame-note 'no-data-series-chart-note chart nil t t))
;    ;; Check the usage of names in this this things slots.
;    (when do-analyze-for-consistency?
;       (funcall-method-if-any 'analyze-for-consistency chart t nil)))
;  (update-representations-of-slot-value chart 'frame-status-and-notes))

(def-class-method retract-frame-notes (chart)
  (delete-frame-note-if-any 'patch-instance-chart-note chart)
  (delete-frame-note-if-any 'no-data-series-chart-note chart)
  (funcall-superior-method chart))

(def-class-method assert-frame-notes (chart)
  (funcall-superior-method chart)
  (unless (data-series chart)
    (add-frame-note 'no-data-series-chart-note chart nil t nil)))


;;;; Native Printing Support


(defun decache-all-graph-renderings-on-window (gensym-window)
  (loop for graph being each class-instance of 'graph doing
;    (make-graph-not-up-to-date graph-grid)
    (dolist-safely (graph-rendering (graph-renderings (get-graph-grid-given-graph graph)))
      (when (eq (window-for-graph-rendering graph-rendering) gensym-window)
	(decache-graph-rendering graph-rendering))))

  (loop for chart being each class-instance of 'chart doing
    (dolist-safely (graph-rendering (graph-renderings-for-chart chart))
      (when (eq (window-for-graph-rendering graph-rendering) gensym-window)
	(decache-graph-rendering graph-rendering))))

  ;; cf decache-all-renderings-of-trend-chart
  (loop for trend-chart being each class-instance of 'trend-chart
	doing
    (dolist-safely (state (2d-image-plane-states trend-chart))
      (when (eq (window-for-graph-rendering (2d-state-rendering state)) gensym-window)
	(decache-graph-rendering (2d-state-rendering state))
	(setf (2d-state-rendering state) nil)))))



;;;; To do List

;; = Ordered list:

;; - Bugs
;;   - connecting lines between data points should be clipped to lie within the
;;     actual chart drawing area (i.e. they should not be allowed to extend into
;;     the chart margins). Similarly, columns should be clipped when needed.
;;   - any axis, doesn't work.
;;   - why did the chart I just looked at have a lot of schedule blocks on 
;;     the chart-initial-update-task?
;;   - there may be problems when an axis has max < min (which is allowed)
;;     (min is actually the leftmost/lowest value displayed on a horizontal/vertical
;;      axis and it is allowed that min > max, so the axis is flipped from the
;;      usual orientation)
;;   - there is currently no distinction between Workspace vs. Raster coordinates 
;;     in this file and the two are often incorrectly intermingled. The correct
;;     arithmetic primitives should be used appropriately (i.e. the arithmetic
;;     primitives with a `W'/`R' suffix for Workspace/Raster arithmetic, resp.)
;;   - If the the range (i.e. abs(max-min) ) is of too small magnitude compared to
;;     max and min (i.e. range/min or range/max has exponent greater than the number
;;     of digits of precision in a gensym-float (usually 15)) then the the chart
;;     will be drawn incorrectly due to rounding errors in the transformation to
;;     device coordinates. This is probably related to the division by 0 problems 
;;     that occur when using plain old `log' instead of `safe-chart-log'.
;; - Source control issues
;;   - Telewindows Rev is necessary if they want to use it over TW.
;; - Data series issues.
;;   - Open data point generators needs a better way to assure that
;;     they are called with their preconditions met.
;; - Update 
;;   - compute and store transform
;;   - The automatic update after activation is questionable?
;;   - General control over updating. (including no updates on edit, or deactivate).
;;   - Consider having the update put something up while it is recomputing.
;; - Part Descriptions.
;;   - subparts stacking in with-part-description is a mess!
;;   - More efficent exception list processing.
;; - Performance 
;;   - analysis.
;;   - Telewindows message stream density issues.
;; - Misc.
;;   - when things seem more stable, stop calling set-up-part-dictionaries 
;;     with the T flag.
;;   - what features in graphs, i.e. extra grid lines, that we are
;;     missing here so far.  Graphs have a frame.
;; - House keeping.
;;   - Fold in MHD mark ups.
;;   - with-chart generates more code than it should.
;; - Smart ideas.
;;   - get some tick marks & grid lines. Grid lines were implemented by WGD 2/92.
;;     They were under #+development because we hadn't yet made a final decision
;;     as to what is the correct model of the grid. Is the grid like the background
;;     on a sheet of graph paper or an extension of the axis tickmarks? In the former
;;     model the grid does not necessarily have any relationship to the the axes or 
;;     user specified points such as axis max,min so that the axes need not be grid
;;     aligned. In the latter model, the grid lines essentially show level lines orthogonal
;;     to the axes (e.g. the grid lines orthogonal to the x-axis shows lines where x
;;     has constant values; in a polar coordinate system the grid lines would be the
;;     level curves consisting of circles and rays). Also, conceptually, the grid should
;;     be implement as a separate part so that one can set its color via the `line-color'
;;     attribute instead of having to use a new color attribute `grid-color' as currently done.
;;   - computed-annotations should be a vector rather than a plist slot since it
;;     occurs in every chart. Note that this is a compatible change since this slot
;;     is not saved (it has the `do-not-save' attribute in the def-class for chart).
;;   - Create a gallery of chart styles shown be example.
;;   - Data point indicators are not scaled (e.g. type C-S a few times and note that
;;     they remain the same size)
;;   - icons as indicators, maybe with changable scaling.
;;   - gant charts
;;   - Chart Noise
;;     - chart title
;;     - chart legend
;;   - logical plot values, and axis.
;;   - Symbolic plot values, and axis.
;;   - horz., vert., and multiple axis naming issues.
;;   - Consider a syntax like: "plot pairs from my-list"
;;   - Consider: "the connecting-line of data-series 2 is stepwise"
;;     v.s. piecewise, and none.
;;   - multiple axis
;;   - log axis

;;; -*- Mode: Lisp; Package: TCLOSI; Syntax: Common-Lisp -*-
;;;
;;; Computing slot indexes.
;;; Copyright (C) 1991 Chestnut Software, Inc.  All Rights Reserved.
;;;

(in-package "TCLOSI")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/slot-layout.lisp,v $"
 "$Revision: 1.3 $"
 "$Date: 2007/11/16 15:39:43 $")

;;; Based on the paper "Two-directional record layout for multiple
;;; inheritance", William Pugh and Grant Weddel, Proceedings ACM SIGPLAN '90.

;;; Input to the algorithm is a list of all the records (classes).  Each record
;;; contains an unordered list of the fields (names of the instance slots) for
;;; the record. 
;;;
;;; Definitions (from the paper):
;;;
;;; appears(x)
;;;  A function which returns a count of the number of records in which the
;;;  field x appears.
;;;
;;; appearsWith(x,y)
;;;  A function which returns a count of the number of records in which both of
;;;  the fields x and y appear.  This relationship is symmetric (ie.
;;;  appearsWith(x,y) =  appearsWith(y,x)).
;;;
;;; coexist(x,y)
;;;  A predicate which returns true iff appearsWith(x,y) > 0.
;;;
;;; implies(x,y)
;;;  If whenever x appears in a record, y appears in the record, then x is said
;;;  to imply y.  This is true iff appears(x) = appearsWith(x,y).  In order to
;;;  make this relation transitive and acyclic, an additional lexicographic
;;;  ordering constraint is imposed.  The actual definition of this predicate
;;;  is appears(x) = appearsWith(x,y) && (string_gt(x,y) || appearsWith(x,y) <
;;;  appears(y)).
;;;
;;; conflict(x,y)
;;;  Predicate which is true iff coexist(x,y) && !(implies(x,y) ||
;;;  implies(y,x)).
;;;
;;; A conflict graph G = (V,E) for a set of records has a vertex for each field
;;;  in the set of records and an edge between two vertices if those two
;;;  respective fields conflict.
;;;
;;; A position is available to x if no fields that coexist with x have already
;;;  been assigned to that position.  The first available position is the one
;;;  with lowest absolute offset.
;;;
;;; Algorithm B
;;;
;;; Loop invariants:
;;;  ImpliesCount(x) = the number of unplaced fields implied by x.
;;;  impatient = the set of unplaced fields that imply zero unplaced fields.
;;; loop body: (terminate when impatient = {})
;;;  desperate = { x in impatient st x conflicts with some placed field }
;;;  frustrated = { x in desperate st x conflicts with fields placed at both
;;;  		      positive and negative offsets }
;;;  if desperate - frustrated /= {} then
;;;    find x in desperate - frustrated st for all y in desperate - frustrated,
;;;	 appears(x) >= appears(y).
;;;  else if desperate /= {} then
;;;    /* Note: desperate == frustrated. */
;;;    find x in desperate st for all y in desperate, appears(x) >= appears(y).
;;;  else
;;;    find x in impatient st for all y in impatient, appears(x) >= appears(y).
;;;  remove x from impatient.
;;;  for all y st implies(y,x)
;;;    decrement ImpliesCount(y).
;;;    if ImpliesCount(y) = 0, add y to impatient.
;;;  place x in the first available position on a side that does not cause
;;;    conflicts with previously placed fields.  If placement on both sides
;;;    creates conflicts, choose the side that produces the fewest conflicts
;;;    (this happens only when no perfect layout is found).
;;;  if placing x at an offset already occupied by a field y then
;;;    merge x with y:
;;;      for all unplaced fields z,
;;;	   appearsWith(y,z) = appearsWith(y,z) + appearsWith(x,z).
;;;
;;; Some comments regarding the actual implementation.
;;;
;;; 1. The definition of `frustrated' is a little vague.  This implementation
;;; assumes that it means: the set of all fields x in desperate, such that
;;; there exists a field yp placed at a positive offset for which
;;; conflict(x,yp) is true, and there exists a field yn placed at a negative
;;; offset for which conflict(x,yn) is true.
;;;
;;; An alternative way of interpreting the description from the paper is: the
;;; set of all fields x in desperate, such that there exists an index i for
;;; which there exists a field yp placed at offset i and conflict(x,yp) is
;;; true, and there exists a field yn placed at offset -i and conflict(x,yn) is
;;; true.
;;;
;;; 2. The description of how to determine where to place a field is a bit
;;; vague.  Surprisingly, this vagueness seems to be important.  See the
;;; comment within the function PLACE-FIELD.

(defstruct (field-layout
	     (:constructor %make-field-layout ())
	     (:predicate nil)
	     (:copier nil))
  field-index
  field-count
  index-field
  appears
  appears-with-index
  appears-with
  implies-count
  unplaced
  offset
  positive-placements
  negative-placements
  )

(defun make-field-layout (records)
  (let ((layout (%make-field-layout)))
    (initialize-field-index records layout)
    (initialize-index-field records layout)
    (initialize-appears records layout)
    (initialize-appears-with-index records layout)
    (initialize-appears-with records layout)
    (initialize-implies-count records layout)
    (initialize-unplaced records layout)
    (initialize-offset records layout)
    (initialize-placement records layout)
    layout))

(defun make-count-vector (size)
  (make-array size
	      :element-type '(unsigned-byte 16)
	      :initial-element 0))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Mapping between field names and indices
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;; The general idea is to compute a mapping from a field name to an index into
;;; the various tables used here, and then manipulate fields via the index
;;; rather than the field name.  This permits the access of information about a
;;; field to be done by an array access rather than requiring a lookup based on
;;; the name.
;;;
;;; The assignment of indices to field names is done in decreasing order of
;;; appearance, with ties broken lexicographically.  This permits the ordering
;;; test in the implies relation to be implemented using a numerical ordering
;;; predicate on the associated indices.  Note that any assignment ordering
;;; (including a random ordering) would provide this capability.  The authors
;;; of the paper just used lexicographic order.  The ordering used here was
;;; chosen to facilitate the representation of the impatient and frustrated
;;; sets as bit-vectors (see update-sets).
;;;
;;; FIELD-INDEX name layout					[Function]
;;;   Returns the index associated with a field name.  This function may be
;;;   used as a place for SETF.
;;;
;;; ORDERED-FIELDS-P x y layout					[Function]
;;;   Returns true if x precedes y according to the rule used for breaking
;;;   cycles in the implies relation.
;;;
;;; FIELD-COUNT	layout						[Function]
;;;   Returns the number of fields being processed.
;;;
;;; INITIALIZE-FIELD-INDEX records layout			[Function]
;;;   Initialize the field-index information in the layout from the records.
;;;
;;; DO-FIELDS (name &optional index) layout &body body		[Macro]
;;;   This macro provides a means of iterating over the field names.  On each
;;;   iteration, name is bound to a field name and index (if supplied) is bound
;;;   to the associated index.

(defun field-index (name layout)
  (values (gethash name (field-layout-field-index layout))))

(defun set-field-index (name layout index)
  (setf (gethash name (field-layout-field-index layout)) index))

(defsetf field-index set-field-index)

(defun field-count (layout)
  (field-layout-field-count layout))

(defun ordered-fields-p (x y layout)
  (declare (ignore layout))
  (< x y))

(defun initialize-field-index (records layout)
  (let ((table (make-hash-table :test 'equal))
	(fields ()))
    (setf (field-layout-field-index layout) table)
    (dolist (record records)
      (dolist (field record)
	(multiple-value-bind (count therep)
	    (gethash field table)
	  (if therep
	      (setf (gethash field table) (1+ count))
	      (progn
		(setf (gethash field table) 1)
		(push field fields))))))
    ;; Order the fields by decreasing appearance counts, with ties broken
    ;; lexicographically.
    (setf fields (sort fields #'string<))
    (setf fields (stable-sort fields #'>
			      :key #'(lambda (field) (gethash field table))))
    (do ((index 0 (1+ index))
	 (fields fields (cdr fields)))
	((endp fields) (setf (field-layout-field-count layout) index))
      (setf (gethash (car fields) table) index))))

(defmacro do-fields ((field &optional index) layout &body body)
  (let* ((ivar (or index (gensym)))
	 (decls (when (null index) `((declare (ignore ,ivar))))))
    `(maphash #'(lambda (,field ,ivar) ,@decls ,@body)
	      (field-layout-field-index ,layout))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Mapping from indices to field names
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;; Provide a mapping from indices to field names.
;;;
;;; INDEX-FIELD index layout					[Function]
;;;   Return the field name associated with index.  This function may be used
;;;   as a place for SETF.
;;;
;;; INITIALIZE-INDEX-FIELD records layout	    		[Function]
;;;   Initialize the index-field information in the layout from the records.

(defun index-field (index layout)
  (svref (field-layout-index-field layout) index))

(defun set-index-field (index layout name)
  (setf (svref (field-layout-index-field layout) index) name))

(defsetf index-field set-index-field)

(defun initialize-index-field (records layout)
  (declare (ignore records))
  (let ((map (make-array (field-count layout) :element-type t :initial-element nil)))
    (setf (field-layout-index-field layout) map)
    (do-fields (field index) layout
      (setf (svref map index) field))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Layout computation database
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;; APPEARS x layout

(defun appears (x layout)
  (aref (field-layout-appears layout) x))

(defun set-appears (x layout value)
  (setf (aref (field-layout-appears layout) x) value))

(defsetf appears set-appears)

(defun initialize-appears (records layout)
  (let ((table (make-count-vector (field-count layout))))
    (setf (field-layout-appears layout) table)
    (dolist (record records)
      (dolist (field record)
	(incf (aref table (field-index field layout)))))))

;;; APPEARS-WITH x y layout
;;;
;;; The implementation of appearsWith uses an array to record the information,
;;; with the access and update functions being performed via access and update
;;; of the array.
;;;
;;; The obvious way to do this is to use a 2d array and simply use x and y as
;;; the indices in a call to AREF.  To make this work, the update function must
;;; modify both the (x,y) and the (y,x) location.
;;;
;;; The obvious method wastes a lot of space when the number of fields is
;;; large (n^2, where n is the number of fields).  The amount of space needed
;;; can be reduced by a factor of two by only recording those entries above (or
;;; below) the x = y diagonal.  The cost is that the index computation is more
;;; complex.  It turns out that this overhead has little effect on the total
;;; running time of the algorithm.
;;;
;;; The appearsWith information is recorded in a vector.  If f is the number of
;;; fields, then the length of the vector and the index that corresponds to a
;;; given pair of fields are determined as follows:
;;;
;;;   length     := f(f-1)/2
;;;   index(x,y) := x + fy - (y+1)(y+2)/2	if x >= y
;;;		    index(y,x)			if x < y
;;;
;;; The subexpression (fy - (y+1)(y+2)/2) is precomputed for all values of y in
;;; [0,f), with the results stored in a table.  This is how the overhead for
;;; the more complicated mechanism for computing the index is kept down to
;;; something comparable to the 2d array implementation.  This uses up some of
;;; the space saved by only recording one triangle of the array, but seems to
;;; be worth it.  (For example, using Lucid 4.0, computing this subexpression
;;; on the fly for each access degraded the running time by a factor of more
;;; than 3.  Heavy use of fixnum declarations along with optimization for speed
;;; without error checking (safety = 0, speed = 3) with the production compiler
;;; got this down to a factor of 1.5 performance degradation.)

(defun compute-appears-with-index-size (field-count)
  field-count)

(defun compute-appears-with-size (field-count)
  (/ (* field-count (1- field-count)) 2))

(defun initialize-appears-with-index (records layout)
  (declare (ignore records))
  (let* ((field-count (field-count layout))
	 (indices (make-array (compute-appears-with-index-size field-count)
			      ;; used to be fixnum, but must be t so
			      ;; we can svref it in index-field
			      :element-type t)))
    (setf (field-layout-appears-with-index layout) indices)
    (dotimes (i field-count)
      (setf (aref indices i)
	    (- (* field-count i) (/ (* (+ i 1) (+ i 2)) 2))))))

(defun appears-with-index (x y layout)
  (+ x (svref (field-layout-appears-with-index layout) y)))

(defun appears-with (x y layout)
  (cond ((> x y)
	 (aref (field-layout-appears-with layout)
	       (appears-with-index x y layout)))
	((< x y)
	 (aref (field-layout-appears-with layout)
	       (appears-with-index y x layout)))
	(t
	 (error "appearsWith called for self."))))

(defun set-appears-with (x y layout value)
  (cond ((> x y)
	 (setf (aref (field-layout-appears-with layout)
		     (appears-with-index x y layout))
	       value))
	((< x y)
	 (setf (aref (field-layout-appears-with layout)
		     (appears-with-index y x layout))
	       value))
	(t
	 (error "Setting appearsWith for self."))))

(defsetf appears-with set-appears-with)

(defun initialize-appears-with (records layout)
  (let* ((field-count (field-count layout))
	 (vector (make-count-vector (compute-appears-with-size field-count))))
    (setf (field-layout-appears-with layout) vector)
    (dolist (record records)
      (do ((fields record (cdr fields)))
	  ((endp fields))
	(let* ((xf (car fields))
	       (x (field-index xf layout)))
	  (dolist (yf (cdr fields))
	    (if (eq xf yf)
		(error "Field ~S appears twice in the same record." xf)
		(incf (appears-with x (field-index yf layout) layout))
		)))))))

;;; COEXIST x y layout
;;;   Predicate which returns true if there exists some record which contains
;;;   both of the fields x and y.

(defun coexist (x y layout)
  (plusp (appears-with x y layout)))

;;; IMPLIES x y layout

(defun implies (x y layout)
  (let ((with-count (appears-with x y layout)))
    (and (= (appears x layout) with-count)
	 (or (ordered-fields-p x y layout)
	     (< with-count (appears y layout))))))

;;; IMPLIES-COUNT x layout

(defun implies-count (x layout)
  (aref (field-layout-implies-count layout) x))

(defun set-implies-count (x layout value)
  (setf (aref (field-layout-implies-count layout) x) value))

(defsetf implies-count set-implies-count)

(defun initialize-implies-count (records layout)
  (declare (ignore records))
  (let* ((field-count (field-count layout))
	 (vector (make-count-vector field-count)))
    (setf (field-layout-implies-count layout) vector)
    (dotimes (x field-count)
      (let ((count 0))
	(dotimes (y field-count)
	  (unless (eql x y)
	    (when (implies x y layout) (incf count))))
	(setf (aref vector x) count)))))

;;; CONFLICT x y layout

(defun conflict (x y layout)
  (and (coexist x y layout)
       (not (or (implies x y layout)
		(implies y x layout)))))

;;; UNPLACED x layout
;;;   Predicate which returns true if x has not been assigned a placement.

; *** not used ***
(defun unplaced (x layout)
  (zerop (aref (field-layout-unplaced layout) x)))

(defun set-unplaced (x layout value)
  (setf (aref (field-layout-unplaced layout) x) (if value 0 1)))

(defsetf unplaced set-unplaced)

(defun initialize-unplaced (records layout)
  (declare (ignore records))
  (setf (field-layout-unplaced layout)
	(make-array (field-count layout)
		    :element-type 'bit
		    :initial-element 0)))

(defmacro do-unplaced ((var layout) &body body)
  (let ((unplaced (gensym)))
    `(do ((,unplaced (field-layout-unplaced ,layout))
	  (,var -1))
         ((null (setf ,var (position 0 ,unplaced :start (incf ,var)))))
       (declare (type simple-bit-vector ,unplaced))
       ,@body)))

;;; OFFSET x layout
;;;   Returns the placement of x.  The result is undefined if x has not been
;;;   placed.

(defun offset (x layout)
  (svref (field-layout-offset layout) x))

(defun initialize-offset (records layout)
  (declare (ignore records))
  (setf (field-layout-offset layout)
	(make-array (field-count layout)
		    :element-type t
		    :initial-element nil)))

(defun note-offset (x offset layout)
  (setf (svref (field-layout-offset layout) x) offset)
  (setf (unplaced x layout) nil))

;;; POSITIVE-PLACEMENTS
;;; NEGATIVE-PLACEMENTS
;;;   Vectors containing the first field placed at each offset.  The first
;;;   field placed at a given positive offset is recorded in the offset entry
;;;   of POSITIVE-PLACEMENTS.  Similarly, the first field placed at a given
;;;   negative offset is recorded in the (1- (abs offset)) entry of
;;;   NEGATIVE-PLACEMENTS.  These vectors have a fill pointer and are
;;;   adjustable.

(defun initialize-placement (records layout)
  (declare (ignore records))
  (setf (field-layout-positive-placements layout) (make-placement-table)
	(field-layout-negative-placements layout) (make-placement-table)))

(defun make-placement-table ()
  (make-array 100 :element-type t :adjustable t :fill-pointer 0 :initial-element nil))

;;; WITH-FIELD-LAYOUT-DATA records &body body			[Macro]
;;;   This macro binds and initializes the database used to compute a slot
;;;   layout for the specified records, and then executes body withing the
;;;   context of those bindings.

(defmacro with-field-layout-data ((layout records) &body body)
  `(let ((,layout (make-field-layout ,records))) ,@body))

;;; SORT-IMPATIENT list layout &optional key
;;; MERGE-IMPATIENT list1 list2 layout &optional key
;;;   These functions are used to maintain lists of impatient fields in order
;;;   by decreasing value of the APPEARS function.  By keeping the lists of
;;;   impatient fields ordered properly, the determination of which field to
;;;   place next is optimized.

(defun sort-impatient (list layout &optional key)
  (declare (type list list))
  (sort list #'> :key (if key
			  #'(lambda (x) (appears (funcall key x) layout))
			  #'(lambda (x) (appears x layout)))))

(defun merge-impatient (list1 list2 layout &optional key)
  (declare (type list list1 list2))
  (merge 'list list1 list2 #'>
	 :key (if key
		  #'(lambda (x) (appears (funcall key x) layout))
		  #'(lambda (x) (appears x layout)))))

(defun initial-impatient-set (layout &aux (impatient nil))
  (dotimes (x (field-count layout))
    (when (zerop (implies-count x layout)) (push x impatient)))
  (sort-impatient impatient layout))

;;; PLACE-FIELD x layout
;;;   Place the field x in the first available location.  A location is
;;;   available to x if no other field placed at the location coexists with x.
;;;
;;; This corresponds to the part of the algorithm described by the following
;;; text:
;;;
;;;    place x in the first available position on a side that does not cause
;;;	   conflicts with previously placed fields.  If placement on both
;;;	   sides creates conflicts, choose the side that produces the fewest
;;;	   conflicts.
;;;    if placing x at an offset already occupied by a field y,
;;;	   then merge x with y: for all unplaced fields z,
;;;	   appearsWith[y,z] <- appearsWith[y,z] + appearsWith[x,z]

(defun place-field (x layout)
  (labels ((new-placement (x offset set)
	     ;; Place x in an empty slot in the set, expanding the set.
	     (vector-push-extend x set)
	     (note-offset x offset layout)
	     (return-from place-field nil))
	   (merge-placement (x offset set index)
	     ;; Place x in a slot with other fields, doing any merging.
	     (let ((y (aref set index)))
	       (do-unplaced (z layout)
		 (or (eql x z)
		     (eql y z)
		     (incf (appears-with y z layout)
			   (appears-with x z layout)))))
	     (note-offset x offset layout)
	     (return-from place-field nil))
	   (place-field-1 (x offset set index)
	     (if (eql index (length set))
		 (new-placement x offset set)
		 (merge-placement x offset set index)))
	   (place-positive-field (x index)
	     (place-field-1 x
			    index
			    (field-layout-positive-placements layout)
			    index))
	   (place-negative-field (x index)
	     (place-field-1 x
			    (- -1 index)
			    (field-layout-negative-placements layout)
			    index))
	   (compute-conflict-info (x set)
	     (let ((free nil)
		   (conflict-count 0))
	       (dotimes (i (length set) (values (or free i) conflict-count))
		 (let ((y (aref set i)))
		   (cond ((conflict x y layout) (incf conflict-count))
			 ((and (null free) (not (coexist x y layout)))
			  (setf free i)))))))
	   )
    ;; Determine where to place the field.
    ;;
    ;; The paper this algorithm is based on is not very clear on the specifics
    ;; of this operation.  It says
    ;;
    ;;   place x in the first available position on a side that does not cause
    ;;   conflicts with previously placed fields.  If placement on both sides
    ;;   creates conflicts, choose the side that produces the fewest conflicts
    ;;   (this happens only when no perfect layout is found).
    ;;
    ;; The thing that is unclear is how to break a tie when placement on either
    ;; side produces the same number of conflicts.
    ;;
    ;; The use of the phrase "first available position" would seem to imply
    ;; that a tie should be broken in favor of the side which permits the
    ;; minimum (absolute value) offset assignment.  This method is implemented
    ;; by the code fragment below described as FIRST-AVAILABLE.
    ;;
    ;; An alternative method is to always choose the same direction (positive
    ;; or negative) in the case of a tie in conflict counts.  This method is
    ;; implemented by the code fragment below described as BIAS-ALWAYS.
    ;;
    ;; This question is surprisingly important.  On a real test case it turned
    ;; out that BIAS-ALWAYS outperformed FIRST-AVAILABLE in the wasted space
    ;; test by almost a factor of two in both total wasted space and maximum
    ;; wasted space.  It is not at all apparent to me why this should be the
    ;; case.  I can only conjecture that it has something to do with the
    ;; BIAS-ALWAYS mechanism using a slightly wider total range of offsets.
    ;;
    ;; Note that some bias seems to be better than no bias, but not as good as
    ;; always biasing.  Using the code fragement BIAS-WHEN-ZERO, the total
    ;; wastage was at the high end of what I'd observed for BIAS-ALWAYS when
    ;; using random selection to break ties for which field to place next, with
    ;; the maximum wasted space being intermediate between FIRST-AVAILABLE and
    ;; BIAS-ALWAYS.
    ;;
    ;; I've communicated these findings to the authors of the paper.  They were
    ;; also surprised by the importance of a bias.  They have indicated that
    ;; they are working on an enlarged and more detailed analysis of the
    ;; approach (with more publications to follow), so perhaps some more
    ;; information about this will become available in the future.
    ;;
    ;; FIRST-AVAILABLE
    #|
    (multiple-value-bind (p-index p-conflict)
        (compute-conflict-info x (field-layout-positive-placements layout))
      (multiple-value-bind (n-index n-conflict)
    	  (compute-conflict-info x (field-layout-negative-placements layout))
    	(cond ((< p-conflict n-conflict) (place-positive-field x p-index))
    	      ((< n-conflict p-conflict) (place-negative-field x n-index))
    	      ((< n-index p-index) (place-negative-field x n-index))
    	      (t (place-positive-field x p-index)))))
    |#
    ;; BIAS-WHEN-ZERO
    #|
    (multiple-value-bind (p-index p-conflict)
	(compute-conflict-info x (field-layout-positive-placements layout))
      (if (zerop p-conflict)
	  (place-positive-field x p-index)
	  (multiple-value-bind (n-index n-conflict)
	      (compute-conflict-info x
				     (field-layout-negative-placements layout))
	    (cond ((< p-conflict n-conflict) (place-positive-field x p-index))
		  ((< n-conflict p-conflict) (place-negative-field x n-index))
		  ((< n-index p-index) (place-negative-field x n-index))
		  (t (place-positive-field x p-index))))))
    |#
    ;; BIAS-ALWAYS
    (multiple-value-bind (p-index p-conflict)
	(compute-conflict-info x (field-layout-positive-placements layout))
      (multiple-value-bind (n-index n-conflict)
	  (compute-conflict-info x (field-layout-negative-placements layout))
	(if (<= p-conflict n-conflict)
	    (place-positive-field x p-index)
	    (place-negative-field x n-index))))
    ))

;;; COMPUTE-NEW-IMPATIENT x layout
;;;   Decrement the ImpliesCount for unplaced fields which imply x, collecting
;;;   those fields which have a new ImpliesCount of zero.  Sort and return the
;;;   resulting collection.
;;;
;;; This function corresponds to the portion of the algorithm described by the
;;; following text:
;;;
;;;    for all fields y s.t. y implies x,
;;;	   decrement ImpliesCount[y]
;;;	   if this makes ImpliesCount[y] = 0, add y to impatient

(defun compute-new-impatient (x layout &aux (new-impatient nil))
  (do-unplaced (y layout)
    (when (and (not (eql x y)) (implies y x layout))
      (when (zerop (decf (implies-count y layout)))
	(push y new-impatient))))
  (sort-impatient new-impatient layout))

;;; UPDATE-SETS x impatient desperate not-frustrated layout
;;;   Given a field x to be placed next, update all the data structures.
;;;
;;; There are three sets maintained here and referenced in the main loop (in
;;; compute-global-field-offsets).  These sets are:
;;;
;;; 1. IMPATIENT: A list of the unplaced fields that imply zero unplaced
;;;    fields, ordered by decreasing value of the APPEARS function.
;;; 2. DESPERATE: A list of impatient fields that coexist with one or more
;;;    placed fields, ordered by decreasing value of the APPEARS function.
;;; 3. NOT-FRUSTRATED: A list of conses.  The CAR of each cons indicates a
;;;    desperate field which is not `frustrated', ie. does not coexist with
;;;    fields placed at both positive and negative offsets.  The CDR of each
;;;    cons is true iff the field coexists with some field placed at a positive
;;;    offset.
;;;
;;; *** There is a different representation that might improve the performance.
;;; *** Currently the sets are maintained as lists of field indices, sorted by
;;; *** decreasing APPEARS counts.  If field indices were already sorted by
;;; *** APPEARS counts (which could be done -- remember that ANY ordering may
;;; *** be used to break ties) then the sets could be represented as
;;; *** bit-vectors.  The assignment of field indices has been modified to make
;;; *** this possible, but this change of representation has not been
;;; *** implemented.

(defun update-sets (x impatient desperate not-frustrated layout)
  (declare (type list impatient desperate not-frustrated))
  (let ((new-impatient (compute-new-impatient x layout))
	(new-desperate ())
	(new-not-frustrated ()))
    ;; Place the field x.
    (place-field x layout)
    ;; Compute the new desperate and not-frustrated sets.
    ;;
    ;; This algorithm incrementally updates the desperate and non-frustrated
    ;; lists, rather than regenerating them completely on each iteration.  The
    ;; following is an outline of the changes to the basic algorithm made to
    ;; permit this.
    ;;
    ;; 1. Associate with each entry in not-frustrated an indication as to which
    ;;    of the positive and negative directions it conflicts in (only one
    ;;    direction will be indicated, since otherwise it would be a frustrated
    ;;    field and not belong in this list).
    ;; 2. If x is placed in a positive location, then remove any entries from
    ;;    not-frustrated which coexist with x and already have negative
    ;;    conflicts, since they are now frustrated.  Similarly if x is placed
    ;;    in a negative position.
    ;; 3. Add any newly impatient fields to desperate and not-frustrated, as
    ;;    appropriate.
    ;;
    (labels ((placement-conflict (x set)
	       (host:some #'(lambda (y) (conflict x y layout)) set))
		 ;; This old version with dolist is a bug, since y is an
	         ;; integer, not a list of integers.
	         ;; under lucid, this was skipping the dolist, and always
	         ;; returning nil. That this failed to cause a disaster
	         ;; was just luck.
	         ;; (dotimes (i (length set) nil)
		 ;;    (dolist (y (aref set i))
		 ;;      (when (conflict x y layout)
		 ;;         (return-from placement-conflict t))))
	     (positive-placement-conflict (x)
	       (placement-conflict x
				   (field-layout-positive-placements layout)))
	     (negative-placement-conflict (x)
	       (placement-conflict x
				   (field-layout-negative-placements layout)))
	     (newly-frustrated-positive (entry)
	       (and (cdr entry)
		    (conflict x (car entry) layout)
		    ))
	     (newly-frustrated-negative (entry)
	       (and (not (cdr entry))
		    (conflict x (car entry) layout)
		    ))
	     )
      (setf not-frustrated
	    (if (minusp (offset x layout))
		(delete-if #'newly-frustrated-negative not-frustrated)
		(delete-if #'newly-frustrated-positive not-frustrated)))
      (dolist (y new-impatient)
	(cond ((positive-placement-conflict y)
	       (push y new-desperate)
	       (when (not (negative-placement-conflict y))
		 (push (cons y t) new-not-frustrated)))
	      ((negative-placement-conflict y)
	       (push y new-desperate)
	       (push (cons y nil) new-not-frustrated))))
      ;; Note that new-desperate and new-not-frustrated are sorted in reverse
      ;; order (since they were collected from properly ordered
      ;; new-impatient) so must be reversed before merging.
      (values (merge-impatient impatient new-impatient layout)
	      (merge-impatient desperate (nreverse new-desperate) layout)
	      (merge-impatient not-frustrated
			       (nreverse new-not-frustrated)
			       layout
			       #'car)))))

(defun get-next-field (list layout &optional key)
  (declare (ignore layout key))
  (car list))

;;; This alternative definition of get-next-field introduces some randomness
;;; into the selection among candidates with equal APPEARS values.  Since this
;;; seems to have little overall effect on the resulting field assignment, use
;;; the simpler definition above.
;;;
;;; A change in the representations of the impatient sets to alists keyed by
;;; APPEARS values and sorted by keys would improve the performance here.
;;; However, it might prove to be an overall negative because of the additional
;;; work needed to update the sets. 
;
;(defun get-next-field (list layout &optional key)
;  (let ((appears (appears (if key
;			      (funcall key (car list))
;			      (car list))
;			  layout))
;	(count 0))
;    (dolist (entry (cdr list))
;      (if (> appears (appears (if key
;				  (funcall key entry)
;				  entry)
;			      layout))
;	  (return)
;	  (incf count)))
;    (if (zerop count)
;	(car list)
;	(nth (random (1+ count)) list))))

;;; COMPUTE-GLOBAL-FIELD-OFFSETS records
;;;   This is the main entry point for the algorithm.  It creates the initial
;;;   layout information from the records, collects the initial impatient set,
;;;   and then iterates over selecting and placing a field (updating all the
;;;   data structures as it goes) until there are no impatient fields.  It then
;;;   returns an alist, with the entries being (field-name . placement) pairs.

(defun compute-global-field-offsets (records)
  (with-field-layout-data (layout records)
    (do ((impatient (initial-impatient-set layout))
	 (desperate ())
	 (not-frustrated ()))
	((endp impatient))
      (declare (list impatient desperate not-frustrated))
      (macrolet ((delete-eq (key list)
		   `(delete ,key ,list :test #'eq)))
	(let ((x (or (when (consp not-frustrated)
		       (let ((next (get-next-field not-frustrated
						   layout
						   #'car)))
			 (setf not-frustrated (delete-eq next not-frustrated))
			 (setf next (car next))
			 (setf desperate (delete-eq next desperate))
			 next))
		     (when (consp desperate)
		       (let ((next (get-next-field desperate layout)))
			 (setf desperate (delete-eq next desperate))
			 next))
		     (get-next-field impatient layout))))
	  (setf impatient (delete-eq x impatient))
	  (multiple-value-setq (impatient desperate not-frustrated)
	    (update-sets x impatient desperate not-frustrated layout)))))
    (let ((unplaced ()))
      (do-unplaced (x layout) (push (index-field x layout) unplaced))
      (when unplaced
	(error "The following fields were not placed!~{~%  ~S~}" unplaced)))
    (map 'list #'cons
	 (field-layout-index-field layout)
	 (field-layout-offset layout))))

;;; CHECK-GLOBAL-FIELD-OFFSET-LAYOUT records offsets
;;;   This function is used to ensure that the layout described in offsets is
;;;   actually valid.  It signals a warning for any record which contains more
;;;   than one field assigned to the same offset (this should never happen if
;;;   the implementation of the algorithm is correct), and returns the minimum
;;;   and maximum placement offsets as two values.

(defun check-global-field-offset-layout (records offsets)
  (let ((table (make-hash-table :test 'equal))
	(min 0)
	(max 0))
    (dolist (offset offsets)
      (let ((value (cdr offset)))
	(setf (gethash (car offset) table) value)
	(setf min (min min value))
	(setf max (max max value))))
    (let* ((adjust (- min))
	   (check (make-array (1+ (- max min)))))
      (dolist (record records (values min max))
	(fill check nil)
	(dolist (field record)
	  (let ((index (+ adjust (gethash field table))))
	    (if (svref check index)
		(return (warn "Collisions in ~S." record))
		(setf (svref check index) field))))))))

(defun print-global-offset-info (records offsets &optional stream)
  (cond ((null stream) (setf stream *standard-output*))
	((eq stream t) (setf stream *terminal-io*)))
  (multiple-value-bind (waste slots max-waste min max)
      (compute-global-offset-info records offsets)
    (format stream
	    "~&;;; Allocated ~D slots with ~D wasted slot~P (worst ~D),~@
               ;;; with the range of slot indices being [~D,~D]."
	    slots waste waste max-waste min max)
    ))

(defun compute-global-offset-info (records offsets)
  (let ((offset-table (make-hash-table :test 'equal)))
    (dolist (offset offsets)
      (setf (gethash (car offset) offset-table) (cdr offset)))
    (flet ((compute-wastage (record)
	     (if (null record)
		 (values 0 0 0 -1)
		 (let ((min 0)
		       (max -1)
		       (count 0))
		   (dolist (field record)
		     (let ((offset (gethash field offset-table)))
		       (setf min (min min offset))
		       (setf max (max max offset))
		       (incf count)))
		   (values (- (1+ (- max min)) count)
			   count
			   min
			   max)))))
      (let ((max-wasted 0)
	    (total-wasted 0)
	    (total-slots 0)
	    (min 0)
	    (max -1))
	(dolist (record records)
	  (multiple-value-bind (waste size local-min local-max)
	      (compute-wastage record)
	    (incf total-wasted waste)
	    (incf total-slots size)
	    (setf max-wasted (max max-wasted waste))
	    (setf min (min min local-min))
	    (setf max (max max local-max))))
	(values total-wasted total-slots max-wasted min max)))))

;;; COMPUTE-GLOBAL-SLOT-INDEXES
;;;
;;; This is the entry point to the slot layout mechanism used by the
;;; translator.  It collects all the classes defined in the environment and
;;; computes from them a list of records to be used as the input to
;;; compute-global-field-indexes.  The record associated with each class is a
;;; list of the names of all of the instance slots (effective slot definition
;;; satisfies instance-slot-p) appearing in instances of the class.

(defun collect-records-from-classes (classes env)
  (flet ((make-record (class)
	   (cond ((translator-typep class 'tclos-run:slotted-class env)
		  (mapcan #'(lambda (slotd)
			      (when (instance-slot-p slotd)
				(list (tclos:slot-definition-name slotd))))
			  (tclos:class-slots class)))
		 ((forward-referenced-class-p class)
		  (warn "A class named ~S is referenced but not defined."
			(tclos:class-name class)))
		 )))
    (mapcar #'make-record classes)))

(defun collect-classes-from-environment (env)
  (let ((classes nil))
    (translator-map-environment-names #'(lambda (name class)
					  (declare (ignore name))
					  (push class classes))
				      env
				      'defined-as-class)
    classes))

;;; COMPUTE-GLOBAL-SLOT-INDEXES
;;;
;;; The entry point for computing the slot indexes.
;;;
;;; It returns a list of triples, with the entries being of the form
;;;
;;;   (slot-name constant index)
;;;
;;; where constant is the index constant associated with the slot name and
;;; index is the computed index.

(defun compute-global-slot-indexes (&optional env)
  (setf env (coerce-to-environment env))
  (when (null env) (setf env *default-global-environment*))
  ;; Set all indexes to be unbound
  (flush-global-slot-index-info env)
  (let* ((classes (collect-classes-from-environment env))
	 (records (collect-records-from-classes classes env))
	 (indexes (compute-global-field-offsets records)))
    (when *verbose-warnings*
      (print-global-offset-info records indexes *error-output*)
      (check-global-field-offset-layout records indexes))
    ;; Set the values of the constants from the computed indexes.
    (dolist (info indexes)
      (record-global-slot-index (car info) (cdr info) env))
    ;; Find any slot index constants which are not associated with an instance
    ;; slot and collect them into the indexes too, with a value of zero.
    (map-global-index-constants
         #'(lambda (name constant)
	     (when (not (nth-value 1 (translator-constant-value constant env)))
	       (push (cons name 0) indexes)))
	 'global-slot-index
	 env)
    ;; Set all indexes to be unbound again.  This is to prevent calls to
    ;; constant-value in later translations from incorrectly finding a value.
    (flush-global-slot-index-info env)
    ;; Return a list of triples, sorted by by slot name.
    (mapcar #'(lambda (pair)
		(let ((name (car pair)))
		  (list name (global-slot-index name env) (cdr pair))))
	    (sort indexes #'string< :key #'car))))

(defun record-global-slot-index (name index env)
  (global-slot-index name env)        ; ensure constant exists
  (setf (global-index-constant-value 'global-slot-index name env) index))

(defun flush-global-slot-index-info (env)
  (reset-global-index-constants 'global-slot-index env))

#|
(defun get-records (file)
  (let ((table (make-hash-table))
	(records ()))
    (with-open-file (file file)
      (do (record)
	  ((eq :eof (setf record (read file nil :eof))))
	(push (mapcar #'(lambda (field)
			  (multiple-value-bind (string therep)
			      (gethash field table)
			    (if therep string
				(setf (gethash field table)
				      (format nil "~A" field)))))
		      record)
	      records)))
    (nreverse records)))

(defun test (records &optional return-offsets)
  (let ((offsets (time (compute-global-field-offsets records))))
    (print-global-offset-info records offsets)
    (multiple-value-call #'values
      (when return-offsets offsets)
      (check-global-field-offset-layout records offsets))))

|#

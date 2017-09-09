;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module CELLS

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Jim Allard and Ben Hyde




;;; Forward references

;;; To INSTALL

(declare-forward-reference analyze-compiled-form function)

;;; To PROC-UTILS

(declare-forward-reference evaluating-simulator-procedure? variable)

(declare-forward-reference clear-computation-context-variables function)

(declare-forward-reference var-count function)

;;; To STACK-INST

(declare-forward-reference clean-up-wake-ups-state-if-any function)

(declare-forward-reference set-wake-ups-function function)

(declare-forward-reference open-wake-up-collection-function function)

;;; To STACK-COMP

(declare-forward-reference compile-expression-cell-for-stack function)

;;; To STACK-KERN

(declare-forward-reference stack-eval function)

;;; To PARTS
(declare-forward-references-to-module PARTS
  (get-simple-part-feature function)
  (get-subpart-collection function)
  (compiled-cell-expression-p function)
  (cell-annotations-for-class function))



;;;; Overview of G2 Cell Arrays




;;; This module implements `g2-cell-arrays'.  Cell arrays are the abstraction
;;; for computational entities being used by portions of G2 outside the
;;; inference engine, procedures, and the simulator.

;;; A G2 cell array is an instance of the class g2-cell-array which holds a
;;; collection of cells, each of which contains a registered expression or
;;; designation.  Each cell has further information registered about it, mostly
;;; controlling when the cell gets updated and what controls surround its
;;; evaluation.

;;; There are currently three kinds of cells in cell-arrays: query-cells,
;;; designation cells, and expression cells.  Query cells allow users to
;;; register multi-valued roles and to receive the values via a stream.
;;; Designation cells register a designation to a single item or value.
;;; Expression cells allow users to register expressions and receive datum from
;;; them.

;;; Users of cells register queries, designations, and expressions in
;;; g2-cell-arrays and are given back an index into the cell array which will
;;; be used in all further cell-array operations to identify the registered
;;; cell.  Cell arrays and their contents can be saved in knowledge bases.
;;; Cells can also be deleted from cell arrays, given their index.

;;; Cells hold a cache of the last value computed by them, so that the users of
;;; cells can quickly find the value currently represented by a cell during
;;; redrawing and other operations.

;;; The caches in cells get new values through updating.  In the first
;;; implementation of this facility, there will be no automatic updating
;;; facilities, such as scan rates or event-based updating.  These facilities
;;; will be added in the not too distant future (-jra 1/29/91, I wonder how
;;; long it will really take?).  Updates to the cached values can be triggered
;;; explicitly by calling the function UPDATE-G2-CELL-ARRAY-VALUE, defined in
;;; detail below.

;;; The computation of an update to the cached value of a cell cannot always be
;;; carried out instantaneously within the call to the update function for
;;; cells.  This is true since the computations called for in a cell may have
;;; to wait for data service, may need data from external, networked sources,
;;; or in general may not be able to complete within a single time slice.  This
;;; fact has led to the choice of operations provided for users of cells, which
;;; implement asynchronous cell updating.

;;; Each g2-cell-array has another frame registered as its parent frame.  This
;;; frame should be what G2 users perceive as the frame which contains the
;;; expressions registered in cells.  The parent frame is used by cell arrays
;;; for three purposes: it is used to hold frame notes which report errors in
;;; the compilation of the computational forms stored in cells; it is used to
;;; generate a textual "designation" used to describe the computational forms
;;; in run-time error messages to users; and it is the frame which is informed
;;; on the completion of updates of newly computed values in the cell cache.

;;; The general operations on cells are: registering new cells, deleting cells,
;;; fetching the cached values of cells, and starting updates on cells.

;;; Cells require two operations to be available for parent frames of cells.
;;; When the update to a cell is complete, it invokes a method of the parent
;;; frame of the g2-cell-array, notifying it that the cell now contains a new
;;; cached value.  This notification operation also passes the old cached
;;; value, so that parent frame updates based on the difference between the old
;;; and new caches may be performed.  The second method is one which, given the
;;; index to a cell, returns a text string containing a user understandable
;;; "designation" for the expression stored in that cell.  For example, in a
;;; graph a cell's designation might be "the x-axis label of graph-XXX-4".

;;; Parent frames must also provide hooks for the analyze for consistency
;;; mechanism.  An analyze-for-consistency method must be defined for the
;;; parent frame's class which sets up the proper environment (see INSTALL for
;;; details) and then calls the function analyze-g2-cell-array-for-consistency
;;; passing the g2-cell-array.  When individual cells are modified, the
;;; function analyze-g2-cell-array-cell-for-consistency takes a g2-cell-array
;;; and an index, and analyzes that one cell.




;;;; Summary of G2 Cell Array Operations




;;; Users of this facility should be familiar with the following functions and
;;; macros to handle each of the following purposes:

;;;   Making G2 Cell Arrays: make-frame, rebuild-backpointers-of-g2-cell-array,
;;; delete-frame.

;;;   Removing Cells: delete-cell-from-g2-cell-array, remove-compilations-from-
;;; obsolete-cell-array

;;;   Initiating Cell Updates: update-g2-cell-array-value

;;;   Activation etc.: activate-g2-cell-array deactivate-g2-cell-array

;;;   Using Query Cells: register-query-cell, register-query-cell-designation,
;;; get-query-cell-cache, create-cell-class-type, create-cell-datum-type,
;;; cell-class-type-p, cell-datum-type-p, class-of-cell-class-type,
;;; datum-type-of-cell-datum-type, reclaim-query-cell-stream,
;;; end-of-query-cell-stream-p, and read-query-cell-stream.

;;;   Using Designation Cells: register-designation-cell, register-designation-
;;; cell-designation, get-designation-cell-cache

;;;   Using Expression Cells: register-expression-cell, register-expression-
;;; cell-expression, get-expression-cell-cache

;;; Users of this facility must provide:
;;;  - query-cell-updated, designation-cell-updated, and expression-cell-updated,
;;;  - generate-designation-of-cell so tracing will work,
;;;  - their analzye-for-consistency must propogate the analysis to the cell-array,
;;;  - their cleanup method must retract the consistency analysis,
;;;  - their activate/deactivate methods must propogate the activation.

;;; To create a g2-cell-array, you should make it with make-frame.  The slot
;;; putter for the slot which stores the frame should call rebuild-backpointers-
;;; of-g2-cell-array on the value when it is stored.






;;;; Dynamic State Defined By Cell Arrays




;;; `Cell-index-currently-being-registered' is bound by the routines that
;;; register a computation into a cell.  It is used by the denote method of the
;;; enclosing frame so it can support the generation of a denotation for the
;;; cell when an error occurs during the compile.

(def-kb-specific-variable cell-index-currently-being-registered cells nil)




;;; When expressions are registered into cells the computation-style used for
;;; them is taken from `current-computation-style'.

(def-kb-specific-variable current-computation-style cells)








;;;; Computation Styles: Introduction and Class Definition




;;; Computation styles attempt to give structure to the full set of 
;;; toggles that parameterize the behavor of a single computation in G2.
;;; Computation styles are blocks.  They are kept in a set, one computation
;;; style for each unique pattern of settings.  Like formating styles this
;;; set grows, but it does not shrink.

;;; The type name computation-style is overloaded.  
;;;   - There is a grammar nonterminal computation-style that
;;;     the parser can use to create a parse which once compiled
;;;     creates
;;;   - a computation-style-description, i.e. part description of the part-type 
;;;     computation-style-description.  Computation-style-descriptions are stored
;;;     in blocks and next to expressions to specify how a given computation (or set
;;;     of computations) should behave.  When combined with some default behavor
;;;     settings it becomes possible to compute the full set of toggles.  Once you 
;;;     have a full set of toggles you can create
;;;   - a computation style block for a particular computation.

;;; The user interface to computation styles is defined and implemented in the module
;;; PARTS.  See also get-default-computation-style-of-class for a discussion of how
;;; any given computation's actual computation style is specified.

;;; The memory management of computation styles is analagous to the memory management
;;; for format frames, i.e. many parts of the KB share single instances.  Unlike
;;; format frames, computation styles are not currently named.  Unlike todays format frames 
;;; new computation styles may arise as the KB is developed.

;;; To understand computation styles fully you need to become comfortable 
;;; with the following issues:
;;;   - How their memory is managed.  (see section below)
;;;    - Creating new ones, cloning, deleting.
;;;    - KB Load and merge, kb modules.
;;;   - How save while running interacts with them.
;;;   - How changes of style are propagated to instances and compilations.
;;;   - How changes of global defaults are propagated to instances and compilations.
;;;     (see module PARTS)
;;;   - What all the slots are for.
;;;     - The scanning toggles.
;;;     - The debugging toggles.
;;;     - The data seeking toggles.    (aka backward chaining)
;;;     - The event updating toggles.  (aka forward chaining)
;;;     - The misc toggles
;;;   - How type is handled
;;;   - How the UI works (see computation-style-description in the module PARTS).

(def-class (computation-style block define-predicate)
  (permanent-computation-style-p nil vector-slot save system)
  ;; (or null computation-style)
  (computation-style-next-element nil vector-slot do-not-save system)
  ;; (and fixnum (integer 1 10))
  (computation-style-priority 1 vector-slot save system)
  ;; (or null (and fixnum interval) (and slot-value-float interval)
  (computation-style-scan-interval nil vector-slot save system)
  ;; (or (and fixnum interval) (and slot-value-float interval))
  (computation-style-initial-scan-wait-interval 2 vector-slot save system)
  ;; boolean
  (computation-style-update-only-when-shown t vector-slot save system)
  ;; see slot compiler for tracing-and-breakpoints
  (computation-style-tracing-and-breakpoints nil vector-slot save system)

  ;; What this computation is allowed to request from other places.
  ;; boolean
  (computation-style-may-request-event-updates t vector-slot save system)
  ;; boolean
  (computation-style-may-request-data-seeking nil vector-slot save system)

  ;; What this place is willing to provide to other computations.
  ;; boolean
  (computation-style-may-provide-data-on-request t vector-slot save system)
  ;; boolean
  (computation-style-may-provide-event-updates nil vector-slot save system)
  ;; (member simulator inference-engine)
  (computation-style-value-domain inference-engine vector-slot save system)
  ;; boolean
  (computation-style-update-after-edits T vector-slot save system)

  ;; Parameterization of the request for data service
  ;; (or null (and fixnum interval))
  (computation-style-time-out-when-requesting-data-seeking
    nil vector-slot save system)

  (modules-this-computation-style-has-been-written-in
    nil vector-slot do-not-save)
  (modules-this-computation-style-has-been-referenced-in
    nil vector-slot do-not-save)

  ;; Parameters for evaluation G2 data server expressions.  These control
  ;; network read and write access checking in serve-item-p.
  ;; (or null read write)
  (computation-style-network-access-attempt nil vector-slot save system)
  )

;; All values are scalars, so eql is assumed sufficent for equality checking.

;; Note that invokable via forward chaining actually uses true value updating so
;; we get expiration events.  It is tempting to provide a way to disable that
;; event.  It is also tempting to provide a way the user can suppress 
;; (obsolete-datum).

;; A null scan-interval means no scan.
;; A null time-out means never time out, aka infinity.
;; I believe that value-domain should have been called data-server. - 11/15/91 ben
;;  -- How is changing the global time out handled?

;; Time-out-when-data-seeking must be defaulted to the approprate system table when
;; setting up the dynamic computation style for the compiler or evaluator.










;;;; Computation Styles: Absent Slot Putters




;;; Some slots that used to exist are now gone.

(def-absent-slot-putter computation-style-reference-count (frame slot-value)
  (declare (ignore slot-value))
  (setf (permanent-computation-style-p frame) t))

(def-absent-slot-putter computation-style-invokable-via-forward-chaining (frame slot-value)
  (setf (computation-style-may-request-event-updates frame) slot-value))

(def-absent-slot-putter computation-style-invokable-via-backward-chaining (frame slot-value)
  (setf (computation-style-may-provide-data-on-request frame) slot-value))

(def-absent-slot-putter computation-style-may-cause-backward-chaining (frame slot-value)
  (setf (computation-style-may-request-data-seeking frame) slot-value))

(def-absent-slot-putter computation-style-may-cause-forward-chaining (frame slot-value)
  (setf (computation-style-may-provide-event-updates frame) slot-value))

(def-absent-slot-putter computation-style-trace-message-level
			(computation-style old-value)
  (convert-absent-slot-to-tracing-and-breakpoints
    computation-style old-value 0 tracing-shift))

(def-absent-slot-putter computation-style-warning-message-level
			(computation-style old-value)
  (convert-absent-slot-to-tracing-and-breakpoints
    computation-style old-value 2 warning-shift))

(def-absent-slot-putter computation-style-break-message-level
			(computation-style old-value)
  (convert-absent-slot-to-tracing-and-breakpoints
    computation-style old-value 0 breakpoint-shift))



;;; `Convert-absent-slot-to-tracing-and-breakpoints' is called at KB load from
;;; the absent slot putters for: computation-style-trace-message-level,
;;; computation-style-warning-message-level, and computation-style-break-
;;; message-level.  It will update the computation-style's computation-style-
;;; tracing-and-breakpoints slot to reflect the values that we used to spread
;;; over these individual slots.

(defun convert-absent-slot-to-tracing-and-breakpoints
       (computation-style old-value default-old-value shift)
  (unless (eql default-old-value old-value) ; guess he didn't change the default?
    (let ((computation-style-tracing-and-breakpoints
	    (or (computation-style-tracing-and-breakpoints computation-style)
		completely-unspecified-debugging-code)))
      (setf (computation-style-tracing-and-breakpoints computation-style)
	    (logior
	      (logandc2 computation-style-tracing-and-breakpoints
			(ash message-field-mask shift))
	      (ash old-value shift))))))






;;;; Computation Styles: Primitive Utilities

(defmacro dynamic-computation-style-p (computation-style)
  `(not (permanent-computation-style-p ,computation-style)))




;;; `Compute-hash-of-computation-style' does just that.  Care is required to
;;; assure it is not used prior to loading all the slots of the frame.

(defun compute-hash-of-computation-style (computation-style)
;  #+development 
;  (update-computation-styles-if-necessary)
  (macrolet ((f1 (slot offset) `(ashf (,slot computation-style) ,offset))
	     (f2 (slot offset) `(ashf (if (,slot computation-style) 1 0) ,offset))
	     (f3 (slot offset)
	       (let ((value (gensym)))
		 `(let ((,value (,slot computation-style)))
		    (ashf (cond ((fixnump ,value)
				 (if (<f ,value 0)
				     (-f ,value)
				     ,value))
				((managed-float-p ,value)
				 (with-temporary-gensym-float-creation hash-cs
				   (floore-first
				     (abse (managed-float-value ,value)))))
				(t 0))
			  ,offset)))))
    ;; F1 is for integers, F2 for booleans, F3 for intervals?.  Don't let the
    ;; offset create a bignum.
    (let ((result 
	    (logxorf
	      (f1 computation-style-priority 0)
	      (f3 computation-style-scan-interval 0)
	      (f3 computation-style-initial-scan-wait-interval 0)
	      (f2 computation-style-update-only-when-shown 6))))
      (declare (type fixnum result))
      (setq result
	    (logxorf
	      result
	      (ash (if (computation-style-tracing-and-breakpoints computation-style)
		       (computation-style-tracing-and-breakpoints computation-style)
		       0)
		   7)
	      (f2 computation-style-may-request-event-updates 14)
	      (f2 computation-style-may-request-data-seeking 15)
	      (f2 computation-style-may-provide-data-on-request 16)))
      (setq result
	    (logxorf
	      result
	      (f2 computation-style-may-provide-event-updates 17)
	      (ashf (if (eq 'simulator
			    (computation-style-value-domain computation-style))
			1 0)
		    18)
	      (f2 computation-style-update-after-edits 19)))
      (case (computation-style-network-access-attempt computation-style)
	((read)
	 (setq result
	       (logxorf result #.(ash 1 20))))
	((write)
	 (setq result
	       (logxorf result #.(ash 1 21)))))
      result)))

;; Broken up since due to some C compiler's capacitly limit on large XOR's.




;;; `Computation-style-equal' tests if two computations styles are sufficently
;;; equal.  Of course it does not compare the reference counts or hash table
;;; thread.

;;; The first argument should be a computation-style.  The second argument
;;; should be a permanent computation style.  They are compared for equality.

(defun computation-style-equal
    (first-computation-style permanent-computation-style)
;  #+development 
;  (update-computation-styles-if-necessary)
  #+development
  (assert (permanent-computation-style-p permanent-computation-style))
  (macrolet ((lexical-compare (slot) `(eql (,slot first-computation-style)
					   (,slot permanent-computation-style)))
	     (lexical-compare-fixnums (slot)
	       `(=f (,slot first-computation-style)
		    (,slot permanent-computation-style)))
	     (lexical-compare-symbols (slot)
	       `(eq (,slot first-computation-style)
		    (,slot permanent-computation-style)))
	     (lexical-compare-intervals (slot)
	       (let ((value1 (gensym))
		     (value2 (gensym)))
		 `(let ((,value1 (,slot first-computation-style))
			(,value2 (,slot permanent-computation-style)))
		    (or (and (null ,value1) (null ,value2))
			(and (fixnump ,value1) (fixnump ,value2)
			     (=f ,value1 ,value2))
			(and (managed-float-p ,value1) (managed-float-p ,value2)
			     (with-temporary-gensym-float-creation equal-cs
			       (=e (managed-float-value ,value1)
				   (managed-float-value ,value2)))))))))
    (and
      (lexical-compare-fixnums computation-style-priority)
      (lexical-compare-intervals computation-style-scan-interval)
      (lexical-compare-intervals computation-style-initial-scan-wait-interval)
      (lexical-compare computation-style-update-only-when-shown)
      (lexical-compare computation-style-tracing-and-breakpoints)
      (lexical-compare computation-style-may-request-event-updates)
      (lexical-compare computation-style-may-request-data-seeking)
      (lexical-compare computation-style-may-provide-data-on-request)
      (lexical-compare computation-style-may-provide-event-updates)
      (lexical-compare computation-style-value-domain)
      (lexical-compare computation-style-update-after-edits)
      (lexical-compare-symbols computation-style-network-access-attempt))))




;;; The function `compare-computation-styles-for-installation-differences' takes
;;; two computation styles and returns multiple values describing the
;;; characteristics of installation which need to change if changing the
;;; computation style of an expression to the first one given, from the second
;;; one given.  This function currently returns the following two flags:

;;;   recompile-needed, which indicates that the changes in the computation
;;;   style require that the element to which this computation style applies
;;;   must be recompiled, and

;;;   scan-task-reschedule-needed, which indicates that any existing task which
;;;   causes scanning for the computation style's expressions must be canceled
;;;   and a new one scheduled with the updated information.

;;; Note that the second computation style argument to this function must be a
;;; permanent computation style.

(defun compare-computation-styles-for-installation-differences
    (new-computation-style old-computation-style?)
;  #+development 
;  (update-computation-styles-if-necessary)
  (cond ((null old-computation-style?)
	 (values t t))
	((computation-style-equal new-computation-style old-computation-style?)
	 (values nil nil))
	(t
	 (macrolet ((lexical-compare (slot)
		      `(eql (,slot new-computation-style)
			    (,slot old-computation-style?)))
		    (lexical-compare-intervals (slot)
		      (let ((value1 (gensym))
			    (value2 (gensym)))
			`(let ((,value1 (,slot new-computation-style))
			       (,value2 (,slot old-computation-style?)))
			   (or (and (null ,value1) (null ,value2))
			       (and (fixnump ,value1) (fixnump ,value2)
				    (=f ,value1 ,value2))
			       (and (managed-float-p ,value1)
				    (managed-float-p ,value2)
				    (with-temporary-gensym-float-creation
					equal-cs
				      (=e (managed-float-value ,value1)
					  (managed-float-value ,value2)))))))))
	   (let ((recompile-needed?
		   (not (lexical-compare
			  computation-style-may-request-event-updates)))
		 (scan-task-reschedule-needed?
		   (or (not (lexical-compare computation-style-priority))
		       (not (lexical-compare-intervals
			      computation-style-scan-interval)))))
	     (values recompile-needed?
		     scan-task-reschedule-needed?))))))




;;; `Copy-computation-style' copies all slots from its second argument
;;; to its first argument except the reference count and thread.  It
;;; assumes both arguments are are compuation-styles.  This routine 
;;; checks, in development, that the source is a dynamic computation style.

(defun copy-computation-style (target-computation-style dynamic-computation-style)
;  #+development 
;  (update-computation-styles-if-necessary)
  #+development
  (assert (dynamic-computation-style-p dynamic-computation-style))
  (macrolet ((lexical-copy-slot (slot-name) 
	       `(setf (,slot-name target-computation-style)
		      (,slot-name dynamic-computation-style)))
	     (lexical-copy-slot-value (slot-name) 
	       `(setf (,slot-name target-computation-style)
		      (copy-for-slot-value 
			(,slot-name dynamic-computation-style)))))
    (lexical-copy-slot computation-style-priority)
    (lexical-copy-slot-value computation-style-scan-interval)
    (lexical-copy-slot-value computation-style-initial-scan-wait-interval)
    (lexical-copy-slot computation-style-update-only-when-shown)
    (lexical-copy-slot computation-style-tracing-and-breakpoints)
    (lexical-copy-slot computation-style-may-request-event-updates)
    (lexical-copy-slot computation-style-may-request-data-seeking)
    (lexical-copy-slot computation-style-may-provide-data-on-request)
    (lexical-copy-slot computation-style-may-provide-event-updates)
    (lexical-copy-slot computation-style-value-domain)
    (lexical-copy-slot computation-style-update-after-edits)
    (lexical-copy-slot computation-style-network-access-attempt))
  target-computation-style)



;;; `funcall-function-over-set-of-all-permanent-computation-style' provides
;;; a way to visit all the permanent computation styles.  This is available
;;; only in development.  Note this must iterate over the hash table since
;;; during loading it is possible to have permanent computation styles that
;;; are hanging off blocks-to-delete-after-reading-kb.

(defmacro do-every-permanent-computation-style ((computation-style) &body body)
  `(loop 
;        #+development initially
;			#+development (update-computation-styles-if-necessary)
     for bucket-index from 0 below number-of-buckets-in-computation-style-set
	   do
     (loop for ,computation-style
	       = (managed-svref set-of-all-permanent-computation-style bucket-index)
	       then (computation-style-next-element
		      ,computation-style)
	   while ,computation-style
	   do (progn ,@body))))

(defparameter number-of-buckets-in-computation-style-set 23)

(def-kb-specific-variable set-of-all-permanent-computation-style cells
  (:funcall initialize-set-of-all-permanent-computation-style)
  nil
  reclaim-set-of-all-permanent-computation-style)

;; Ben, the above definitions were moved here to fix a compilation crash.  -jra
;; 12/10/91

#+development
(defun funcall-function-over-set-of-all-permanent-computation-style (function)
  (do-every-permanent-computation-style (computation-style)
    (funcall function computation-style))
  nil)



#+development
(defun describe-computation-style (computation-style)
  (macrolet ((i (n x)
	       `(format t " ~:[~;~:*~A:~]~D" ',n (,x computation-style)))
	     (b (n x)
	       `(format t " ~:[~;~:*~A:~]~:[N~;Y~]" ',n (,x computation-style)))
	     (secs (n x)
	       `(format t " ~:[~;~:*~A:~]~A"
			',n (slot-value-number-value (,x computation-style)))))
    ;; i is for integer, b is for booleans.
    (format t "~%~A" (if (permanent-computation-style-p computation-style) "Perm:" "Dynm:"))
    (i Pri computation-style-priority)
    (secs scan computation-style-scan-interval)
    (secs nil computation-style-initial-scan-wait-interval)
    (format t "TB:~X" (computation-style-tracing-and-breakpoints computation-style))
    (b F computation-style-may-request-event-updates)
    (b nil computation-style-may-request-data-seeking)
    (b nil computation-style-may-provide-data-on-request)
    (b nil computation-style-may-provide-event-updates)
    (format t " ~:[INF~;SIM~]" (eq (computation-style-value-domain computation-style) 'simulator))
    (b UShow computation-style-update-only-when-shown)
    (b UEdit computation-style-update-after-edits)
    (format t " NET ~a" (computation-style-network-access-attempt computation-style))))

#+development
(defun show-all-permanent-computation-styles ()
  (funcall-function-over-set-of-all-permanent-computation-style
    'describe-computation-style))

;#+development
;(defun check-consistency-of-computation-styles ()
;  (let ((count-of-instances 0)
;	(count-of-uses 0))
;    (loop for computation-style being class-instances of 'computation-style
;	  do
;      (incf count-of-instances)
;      (cond
;	((permanent-computation-style-p computation-style)
;	 (assert (permanent-block-p computation-style) () "Type 4 trouble")
;	 (or
;	   (and reading-kb-p
;		(memq computation-style blocks-to-delete-after-reading-kb))
;	   (assert (eq (find-matching-permanent-computation-style-if-any computation-style)
;		       computation-style) () "Type 1 trouble: ~S" computation-style)))
;	(T
;	 (assert (not (permanent-block-p computation-style)) () "Type 5 trouble")
;	 (assert (eql computation-style
;		      the-only-dynamic-computation-style)
;		 ()
;		 "Type 2 trouble: ~S"
;		 computation-style)))
;      ;; Check the slots?
;      (macrolet ((chk (slot type text) `(assert (typep (,slot computation-style) ',type) () ,text)))
;	(assert (or (null (computation-style-next-element computation-style))
;		    (computation-style-p computation-style))
;		() "Type 6 trouble")
;	(chk computation-style-priority (and fixnum (integer 1 10)) "Type 7 trouble")
;	(chk computation-style-scan-interval (ab-lisp:or null fixnum) "Type 8 trouble")
;	(chk computation-style-initial-scan-wait-interval fixnum "Type 9 trouble")
;	(chk computation-style-update-only-when-shown (member nil t) "Type 10 trouble")
;	(chk computation-style-tracing-and-breakpoints (ab-lisp:or null fixnum) "Type 11 trouble")
;	(chk computation-style-may-request-event-updates (member nil t) "Type 12 trouble")
;	(chk computation-style-may-request-data-seeking (member nil t) "Type 13 trouble")
;	(chk computation-style-may-provide-data-on-request (member nil t) "Type 14 trouble")
;	(chk computation-style-may-provide-event-updates (member nil t) "Type 15 trouble")
;	(chk computation-style-value-domain (member g2-simulator inference-engine) "Type 16 trouble")
;	(chk computation-style-update-after-edits  (member nil t) "Type 17 trouble")
;	(chk computation-style-time-out-when-requesting-data-seeking (ab-lisp:or null fixnum) "Type 18 trouble")
;       (chk computation-style-network-access-attempt (member nil read write) "Type 19 trouble")))

;    ;; Scan all blocks and find all references to computation style.
;    (loop for block being class-instances of 'block
;	  as cell-array? = (cell-array block)

;	  when cell-array?
;	    do
;	      (let ((array (g2-cell-array-managed-array cell-array?)))
;		(loop for i from 0 below (managed-array-length array)
;		      as expression-cell = (managed-svref array i)
;		      as computation-style = (g2-expression-cell-computation-style expression-cell)
;		      do
;		  (incf count-of-uses)
;		  (assert (and (computation-style-p computation-style)
;			       (permanent-computation-style-p computation-style))
;			  ()
;			  "Type 3 trouble: ~S ~S ~S" block expression-cell computation-style)
;		  )))
;    (values 'ok :instances count-of-instances :uses count-of-uses)))
;; Don't leave this uncommented, since it is full of forward references.

;; Type 1 trouble: 
;;    a) We might have two entries in the set that are identical.
;;    b) It really isn't in the set.
;;    c) It didn't get put on the blocks-to-delete-after-reading-kb and we are reading and
;;       we decided to delete it.
;; Type 2 trouble: 
;;    a) Multiple dynamic computation styles
;; Type 3
;;    a) It wasn't a computation style, or
;;    a) It wasn't permanent?
;; Type 4: It didn't get flagged as permanbent.
;; Type 5: It should be marked as permanent
;; Type 6..17 something is wrong with the value in a slot, see the code.

;;;; Computation Styles: Memory Management



;;; Each unique pattern of computation style settings occurs once in the KB.  A
;;; set is used to manage this, i.e. the-set-of-all-permanent-computation-styles.
;;; This set is added to whenever a new pattern occurs in some frame or
;;; expression.  It is cleared only when the KB is cleared.  When loading or
;;; merging, additions are made in the initialize-after-reading frame method,
;;; after all the slots used in the hash for the frame have been loaded, and
;;; only if the frame just read isn't already in the set.

;;; One computation lives outside the set, as a scratch pad, stored in
;;; the-only-dynamic-computation-style.  When creating new computation styles
;;; this computation style is filled out and then registered as permanent.

;;; The only operations on the set of permanent computation styles are:
;;; `register-use-of-computation-style', and `deregister-use-of-computation-style' that
;;; modify the reference count.  Members of the set are known as permanent computation
;;; styles.

;;; These names are a historical remanent of a time when the set was managed using reference
;;; counts.  KB modularity made continuing that difficult.  It is now the case that for the
;;; life of a given KB the set only grows.

;;; The predicates `permanent-computation-style-p' and `dynamic-computation-style-p' are
;;; provided.  They are used only by the internals of computation style memory management to
;;; check that certain patterns of usage are obeyed.

;;; The kb-specific-variable `set-of-all-permanent-computation-style' holds the
;;; hash table like data structure that owns all computation style instances.
;;; The set implementation is extremely simple.  The set is a fixed sized 
;;; (23 actually) managed array with each cell holding a slot value list of
;;; computation styles.

;;; The set is saved by code in traversals, that calls code in the section below.

;;; During loading permanent computation styles may exist outside of the
;;; set-of-all-permanent-computation-style, i.e. in the list
;;; blocks-to-delete-after-reading-kb.

;(def-kb-specific-variable set-of-all-permanent-computation-style cells
;  (:funcall initialize-set-of-all-permanent-computation-style)
;  nil
;  reclaim-set-of-all-permanent-computation-style)

;; Ben, the above was moved up in the file.  -jra 12/10/91




;;; Currently there is one dynamic instance of the computation style class.  This one instance
;;; is kept in the kb specific variable `the-only-dynamic-computation-style'.

;; This comment and the three forms below were moved up to get rid of warnings
;; in this file.  -jra 12/11/91


(def-kb-specific-variable the-only-dynamic-computation-style
  cells
  (:funcall make-computation-style-function))

(defun make-computation-style-function ()
  (make-frame 'computation-style))

(defmacro permanent-computation-style-hash-table-bucket-index
    (permanent-computation-style)
  `(modf-positive
     (compute-hash-of-computation-style ,permanent-computation-style)
     number-of-buckets-in-computation-style-set))




;;; `Initialize-set-of-all-permanent-computation-style' is funcalled when a
;;; new inference-engine-parameters system table is created, it creates
;;; an empty set of computation styles, and allows all further code to
;;; assume that the set exists.

(defun initialize-set-of-all-permanent-computation-style ()
;  #+development
;  (slot-value-cons
;    version-of-computation-style-set-implemenatation
;    (allocate-managed-array number-of-buckets-in-computation-style-set))
;  #-development
  (allocate-managed-array number-of-buckets-in-computation-style-set))

(defun reclaim-set-of-all-permanent-computation-style (the-set)
  (reclaim-slot-value the-set))


;;; `Find-matching-permanent-computation-style-if-any' is an subfunction of the
;;; routines that manage the set of all permanent computation styles.

(defun find-matching-permanent-computation-style-if-any (computation-style)
;  #+development 
;  (update-computation-styles-if-necessary)
  (loop with bucket-index = (permanent-computation-style-hash-table-bucket-index
			      computation-style)
	for candiate-computation-style?
	= (managed-svref set-of-all-permanent-computation-style bucket-index)
	    then (computation-style-next-element
		   candiate-computation-style?)
	until (or (null candiate-computation-style?)
		  (computation-style-equal
		    computation-style
		    candiate-computation-style?))
	finally
	  (return candiate-computation-style?)))



;;; `Add-computation-style-from-set-of-all-permanent-computation-styles' is
;;; responsible for inserting computation styles.  It is called when
;;; loading/merging KBs, and when a frames requests a permanent computation
;;; style that isn't currently in the set.  It assumes that the frame is not
;;; already in the set.

(defun add-computation-style-to-set-of-all-permanent-computation-styles  (permanent-computation-style)
;  #+development 
;  (update-computation-styles-if-necessary)
  (let* ((bucket-index 
	   (permanent-computation-style-hash-table-bucket-index
	     permanent-computation-style)))
    (setf (computation-style-next-element permanent-computation-style)
	  (managed-svref set-of-all-permanent-computation-style bucket-index))
    (setf (managed-svref set-of-all-permanent-computation-style bucket-index) 
	  permanent-computation-style)))



;;; `Register-use-of-computation-style' may be called upon either a dynamic or permanent
;;; computation-style.  It returns a computation-style, probably different than the one you
;;; provided, that is permanent.  You may then store that into a persistent slot.

;;; Register-use-of-computation-style will allocate memory when there is currently no
;;; computation style in the set of all permanent computation styles that matchs the one
;;; given.

(defun register-use-of-computation-style (computation-style)
;  #+development 
;  (update-computation-styles-if-necessary)
  (or (if (permanent-computation-style-p computation-style)
	  computation-style)
      (find-matching-permanent-computation-style-if-any computation-style)
      (let ((new-computation-style (copy-computation-style 
				     (make-frame 'computation-style)
				     computation-style)))
	(setf (permanent-computation-style-p new-computation-style) t) 
	(set-permanent-block computation-style)
	(when noting-changes-to-kb-p
	  (set-block-permanently-changed computation-style))
	(add-computation-style-to-set-of-all-permanent-computation-styles new-computation-style)
	new-computation-style)))



;;; `Deregister-use-of-computation-style' is called to indicate that a
;;; slot is no longer interested in this computation style.  This is now
;;; a historical artifact of the good old days when the set of permanent
;;; computation styles was managed with reference counts.

(defun deregister-use-of-computation-style (permanent-computation-style)
  #-development
  (declare (ignore permanent-computation-style))
;  #+development 
;  (update-computation-styles-if-necessary)
  #+development
  (unless (permanent-computation-style-p permanent-computation-style)
    (cerror "Continue." "Attempted to deregister a dynamic computation style.")))






;;;; Computation Styles: Interface For Save, Load, and Merge KB.


;;; When you merge KBs you must merge the two sets of all compuation styles.  If
;;; the KB being merged contains a computation style, call it CSm, identical to
;;; one already known, call it CS1 for this KB, then all pointers to CSm are
;;; replaced with pointers to CS1.

;;; `Get-or-make-entry-to-set-of-all-permanent-computation-styles' enables this trick.
;;; Read-frame-for-kb, just after reading CSm will call this routine to see if an equivalent
;;; CS already exists in the set of permanent computation styles.  If so it will be
;;; slammed into the index space where CSm would have appeared, and it will delete CSm.

(defun get-or-make-entry-to-set-of-all-permanent-computation-styles (incomming-computation-style)
  (or (find-matching-permanent-computation-style-if-any incomming-computation-style)
      (add-computation-style-to-set-of-all-permanent-computation-styles
	incomming-computation-style)))



;; ;;; `traverse-computation-style-for-backup' is a subfunction of
;; ;;; traverse-kb-for-saving in traversals.  It returns a list of journal conses
;; ;;; containing the set of all permanent computation styles, which the caller
;; ;;; must reclaim.
;; 
;; (defun traverse-computation-style-for-backup ()
;; ;  #+development 
;; ;  (update-computation-styles-if-necessary)
;;   (let (result)
;;     (do-every-permanent-computation-style (computation-style)
;;       #+development
;;       (assert (permanent-computation-style-p computation-style))
;;       (journal-push computation-style result))
;;     (nreverse result)))
;; 
;; -- No longer needed due to the change that eliminates a section of all
;; computation styles near the beginning of a KB.  The function below is now
;; defined to replace the remaining use, by savable-block-p. (MHD 2/2/94)


;;; `Savable-computation-style-p' is a a subfunction of savable-block-p that
;;; returns true if computation-style-instance is savable.

(defun savable-computation-style-p (computation-style-instance)
  (do-every-permanent-computation-style (computation-style)
    (when (eq computation-style computation-style-instance)
      (return t))))
  
;; New. (MHD 2/2/94)







;;;; Creating G2 Cell Arrays




;;; To create a g2-cell-array, you should make it with make-frame, and then
;;; store the result in a slot of a nondependent frame.  The slot putter for
;;; that slot must always call rebuild-backpointers-of-g2-cell-array to assure
;;; that the frame's backpointers are correct.

;;; The class `g2-cell-array' contains slots for a managed-array of cell
;;; descriptions and for a set of defaults for the entire cell array.

(def-class (g2-cell-array dependent-frame define-predicate)
  (g2-cell-array-parent-frame nil vector-slot system do-not-save do-not-clone)
  (g2-cell-array-managed-array nil vector-slot system save))

(defun g2-cell-array-managed-array-function (g2-cell-array)
  (g2-cell-array-managed-array g2-cell-array))




;;; Since the cell array is a tree dependent frame we must maintain any pointers
;;; (other than those which form the trunk of the that tree) when saving,
;;; reclaiming, loading, cloning, and building.  The backpointers have the slot
;;; feature DO-NOT-SAVE, to avoid the saving of the slot.

;;; `Rebuild-backpointers-of-g2-cell-array' takes the responsiblity for cloning,
;;; loading, and some of building.  The slot putter of the slot in the cell
;;; array's parent must call rebuild-backpointers-of-g2-cell-array.

(defun rebuild-backpointers-of-g2-cell-array (parent-frame g2-cell-array)
  (setf (g2-cell-array-parent-frame g2-cell-array) parent-frame)
  (rebuild-backpointers-of-cells-of-g2-cell-array g2-cell-array parent-frame)
  nil)




;;; The slot value reclaimers for the backpointers prempt reclaiming going into
;;; a loop.

(def-slot-value-reclaimer g2-cell-array-parent-frame (parent-frame g2-cell-array)
  (declare (ignore parent-frame))
  ;; Avoid cycle with deleting this dependent frame
  (setf (g2-cell-array-parent-frame g2-cell-array) nil))

;; Historical note: In the original implementation of cell arrays the assertion
;; made about backpointers was "They are assured to be valid during those
;; extents in time which other code needs them to be valid." The current
;; assertion is that they are valid when ever the data structure has been
;; completely created.




;;; Remember, all dependent frames must have a copy-frame method.

(def-class-method copy-frame (g2-cell-array)
  (let*-sim ((current-block-of-dependent-frame 'dependent-frame-has-no-owner))
    (clone-frame g2-cell-array)))






;;;; Launching G2 Cell Array Updates




;;; The function `schedule-g2-cell-array-update' takes a g2-cell-array and
;;; schedules all cells to be updated.

(defun schedule-g2-cell-array-update (block)
  (let* ((g2-cell-array (cell-array block))
	 (managed-array (if g2-cell-array
			    (g2-cell-array-managed-array g2-cell-array)
			    nil))
	 (cell-count (if managed-array
			 (managed-array-length managed-array)
			 0)))
    (loop for index from 0 below cell-count
	  for cell = (managed-svref managed-array index)
	  do
      (when cell
	(update-g2-cell-value block g2-cell-array index cell)))))




;;; The function `update-g2-cell-value' takes a cell from a g2-cell-array, along
;;; with the array and its index.  It begins an update to the given cell.

(defun update-g2-cell-value (block g2-cell-array index cell)
  (frame-class-case cell
    (g2-expression-cell
      (schedule-expression-cell-execution block index t))
    (g2-designation-cell
      (compute-new-designation-cell-value g2-cell-array index cell))
    (g2-query-cell
      (compute-new-query-cell-value g2-cell-array index cell))))

;(defun attempt-g2-cell-execution (g2-cell-array index)
;  (let ((cell (managed-svref (g2-cell-array-managed-array g2-cell-array) index)))
;    (frame-class-case cell
;      (g2-expression-cell
;	(attempt-expression-cell-execution cell nil nil))
;      (g2-designation-cell
;	; TBD (attempt-designation-cell-execution cell)
;	)
;      (g2-query-cell
;	; TBD (attempt-query-cell-execution cell)
;	))))






;;;; Initializing and Cleaning Up the Cell Array




;;; The following functions are called from the initialize,
;;; initialize-after-reading, and cleanup methods for block when that block
;;; contains a cell-array.  The handle scheduling and descheduling of cyclic
;;; tasks for cell arrays in runs-while-inactive items.

(defun-void initialize-g2-cell-array (g2-cell-array)
  (let ((parent-frame (g2-cell-array-parent-frame g2-cell-array)))
    (when (runs-while-inactive-p parent-frame)
      (begin-g2-cell-array-evaluations g2-cell-array))))

(defun-void initialize-g2-cell-array-after-reading (g2-cell-array)
  (initialize-g2-cell-array g2-cell-array))

(defun-void cleanup-g2-cell-array (g2-cell-array)
  (let ((parent-frame (g2-cell-array-parent-frame g2-cell-array)))
    (when (runs-while-inactive-p parent-frame)
      (shutdown-g2-cell-array-evaluations g2-cell-array))))

(defun-void note-g2-cell-array-runs-while-inactive-change
    (g2-cell-array parent-frame)
  (if (runs-while-inactive-p parent-frame)
      (begin-g2-cell-array-evaluations g2-cell-array)
      (if (not (active-p parent-frame))
	  (shutdown-g2-cell-array-evaluations g2-cell-array))))





;;;; Activating And Deactivating The Cell Array




;;; The function `activate-g2-cell-array' does just that to the cell array passed as
;;; its only argument.  The parent frame's activation method should
;;; invoke this.  This spawns all tasks associated with the cells and
;;; asserts all registrations of interest the cells may have
;;; in other parts of the KB.

(defun-void activate-g2-cell-array (g2-cell-array)
  (begin-g2-cell-array-evaluations g2-cell-array))

(defun-void begin-g2-cell-array-evaluations (g2-cell-array)
  (let ((managed-array (g2-cell-array-managed-array g2-cell-array)))
    (when managed-array
      (loop for index from 0 below (managed-array-length managed-array)
	    do
	(activate-cell-of-g2-cell-array-1 (managed-svref managed-array index))))))




;;; The function `activate-cell-of-g2-cell-array' takes a g2-cell-array and an
;;; index into an existing cell in that array.  This function will activate the
;;; cell, scheduling any update tasks using the initial wait interval.

(defun-void activate-cell-of-g2-cell-array (g2-cell-array index)
  (activate-cell-of-g2-cell-array-1
    (managed-svref (g2-cell-array-managed-array g2-cell-array) index)))

(defun-void activate-cell-of-g2-cell-array-1 (cell?)
  (when cell?
    (frame-class-case cell?
      ((g2-expression-cell)
       (activate-g2-expression-cell cell?))
      ((g2-query-cell)
       (activate-g2-query-cell cell?))
      ((g2-designation-cell)
       (activate-g2-designation-cell cell?))))
  nil)



;;; `Deactivate-g2-cell-array' does just that to the cell array passed as
;;; its only argument.  The parent frame's deactivation method should
;;; invoke this.  This cancels all tasks associated with the cell and
;;; retracts all registrations of interest this cell array may have
;;; posted with other parts of the KB.

(defun-void deactivate-g2-cell-array (g2-cell-array)
  (let ((parent-frame (g2-cell-array-parent-frame g2-cell-array)))
    (unless (runs-while-inactive-p parent-frame)
      (shutdown-g2-cell-array-evaluations g2-cell-array))))

(defun-void shutdown-g2-cell-array-evaluations (g2-cell-array)
  (let ((managed-array (g2-cell-array-managed-array g2-cell-array)))
    (when managed-array
      (loop for index from 0 below (managed-array-length managed-array)
	    do
	(deactivate-cell-of-g2-cell-array-1 (managed-svref managed-array index))))))




;;; The function `deactivate-cell-of-g2-cell-array' takes a g2-cell-array and an
;;; index into an existing cell for that array and deactivates it.  This is
;;; necessary prior to deletion of a cell, either through this function or
;;; deactivate-g2-cell-array.

(defun-void deactivate-cell-of-g2-cell-array (g2-cell-array cell-index)
  (deactivate-cell-of-g2-cell-array-1
    (managed-svref (g2-cell-array-managed-array g2-cell-array) cell-index)))

(defun-void deactivate-cell-of-g2-cell-array-1 (cell?)
  (when cell?
    (frame-class-case cell?
      ((g2-expression-cell)
       (deactivate-g2-expression-cell cell?))
      ((g2-query-cell)
       (deactivate-g2-query-cell cell?))
      ((g2-designation-cell)
       (deactivate-g2-designation-cell cell?))))
  nil)







;;;; Adding and Deleting Cells From The Cell Array




;;; The function `delete-cell-from-g2-cell-array' takes a g2-cell-array and an
;;; index.  It deletes that cell from the array.  The cell must already have
;;; been deactivated, or orphan tasks might be created.

(defun delete-cell-from-g2-cell-array (g2-cell-array index)
  (let ((managed-array (g2-cell-array-managed-array g2-cell-array)))
    #+development
    (when (g2-expression-cell-cyclic-task-function 
           (managed-svref managed-array index))
      ;; See deactivate for other things that are cleaned up.
      (error "Cells must be inactive prior to deletion."))
    (delete-all-frame-notes-for-component-particular
      current-computation-component-particulars
     *current-computation-frame*)
    (delete-frame (managed-svref managed-array index))
    (setf (managed-svref managed-array index) nil)
    (setf (g2-cell-array-managed-array g2-cell-array)
	  (shrink-or-delete-managed-array-null-elements managed-array))
    nil))




;;; The function `remove-compilations-from-obsolete-cell-array' takes a G2 cell
;;; array which was compiled in some previous version of G2, and removes the
;;; compilations from all contained cells.

(defun remove-compilations-from-obsolete-cell-array (g2-cell-array?)
  (when g2-cell-array?
    (let* ((managed-array (g2-cell-array-managed-array g2-cell-array?))
	   (cell-count (if managed-array
			   (managed-array-length managed-array)
			   0)))
      (loop for index from 0 below cell-count
	    for cell = (managed-svref managed-array index)
	    do
	(when (framep cell)
	  (frame-class-case cell
	    ((g2-expression-cell)
	     (remove-compilation-from-obsolete-expression-cell cell))
	    ((g2-query-cell g2-designation-cell)
	     nil)))))))

;;;



;;; The function `find-new-location-for-cell' takes a g2-cell-array and returns
;;; a fixnum naming an available location for a new cell.  This function is
;;; called by registration functions to allocate a location.

(defun find-new-location-for-cell (g2-cell-array)
  (let ((new-location -1)
	(managed-array (g2-cell-array-managed-array g2-cell-array)))
    (declare (type fixnum new-location))
    (if (null managed-array)
	(progn
	  (setq managed-array (allocate-managed-array 1))
	  (setf (g2-cell-array-managed-array g2-cell-array) managed-array)
	  (setq new-location 0))
	(loop with array-length fixnum = (managed-array-length managed-array)
	      for index from 0 below array-length
	      do
	  (when (null (managed-svref managed-array index))
	    (setq new-location index)
	    (return))
	      finally				; No empty locations
		(setq new-location array-length)
		(setf (g2-cell-array-managed-array g2-cell-array)
		      (adjust-managed-array
			managed-array
			(+f array-length 1)))))
    new-location))







;;;; Analyzing G2 Cell Arrays for Consistency




;;; The function `analyze-g2-cell-array-for-consistency' should be called with
;;; the proper binding environment (as documented in INSTALL) and given the
;;; g2-cell-array.

(defun analyze-g2-cell-array-for-consistency (g2-cell-array)
  (let ((managed-array (g2-cell-array-managed-array g2-cell-array)))
    (when managed-array
      (loop with current-computation-component-particulars 
	      = (slot-value-list 'cell-array-element 0)
	    for index from 0 below (managed-array-length managed-array)
	    do
	(setf (second current-computation-component-particulars) index) 
	(analyze-cell-for-consistency-1 (managed-svref managed-array index))
	    finally 
	      (reclaim-slot-value-list current-computation-component-particulars)))))


;;; The function `analyze-cell-for-consistency-1' takes a cell or NIL and
;;; analyzes that cell.

(defun-void analyze-cell-for-consistency-1 (cell?)
  (when cell?
    (frame-class-case cell?
      ((g2-expression-cell)
       (analyze-g2-expression-cell-for-consistency cell?))
      ((g2-query-cell)
       (analyze-g2-query-cell-for-consistency cell?))
      ((g2-designation-cell)
       (analyze-g2-designation-cell-for-consistency cell?)))))

;; Check for empty cell?



;;; The function `g2-cell-array-expression-cells-have-byte-code-bodies-p'
;;; tests if the non-NIL cells have a byte-code-body.

;;; This function is needed in the consistency-analysis of items with cell-
;;; arrays.

(defun g2-cell-array-expression-cells-have-byte-code-bodies-p (g2-cell-array)
  (let ((managed-array (g2-cell-array-managed-array g2-cell-array)))
    (when managed-array
      (loop for index from 0 below (managed-array-length managed-array)
	    for cell? = (managed-svref managed-array index)
	    with expression-cells-have-byte-code-bodies? = t
	    do
	(when (and cell? (frame-of-class-p cell? 'g2-expression-cell))
	  (unless (g2-expression-cell-byte-code-body-function cell?)
	    (setq expression-cells-have-byte-code-bodies? nil)))
	    until (null expression-cells-have-byte-code-bodies?)
	    finally
	      (return expression-cells-have-byte-code-bodies?)))))






;;;; Cell Classes And Backpointer Maintainance.




;;; The classes `g2-query-cell', `g2-designation-cell, and `expression-cell' are
;;; used to represent registered roles, designations, and expressions in
;;; g2-cell-arrays.

(def-class (g2-cell-array-cell dependent-frame define-predicate)
  )

(def-class-method copy-frame (g2-cell-array-cell)
  (let*-sim ((current-block-of-dependent-frame 'dependent-frame-has-no-owner))
    (clone-frame g2-cell-array-cell)))

(def-class (g2-query-cell g2-cell-array-cell define-predicate)
  (g2-query-cell-generic-designation nil vector-slot system save)
  (g2-query-cell-value-type nil vector-slot system save)
  (g2-query-cell-cached-value nil vector-slot system)
  (g2-query-cell-frame-serial-number? nil vector-slot system))

(def-class (g2-designation-cell g2-cell-array-cell define-predicate)
  (g2-designation-cell-designation nil vector-slot system save)
  (g2-designation-cell-value-type nil vector-slot system save)
  (g2-designation-cell-cached-value nil vector-slot system)
  (g2-designation-cell-frame-serial-number? nil vector-slot system))

(def-slot-value-reclaimer g2-designation-cell-frame-serial-number?
			  (serial-number g2-designation-cell)
  (reclaim-frame-serial-number serial-number)
  (setf (g2-designation-cell-frame-serial-number? g2-designation-cell) nil))

(def-class (g2-expression-cell g2-cell-array-cell define-predicate)
  (g2-expression-cell-value-type nil vector-slot system save)
  (g2-expression-cell-computation-style
    nil vector-slot system save do-not-clone)
  (g2-expression-cell-g2-cell-array
    nil vector-slot system do-not-save do-not-clone)
  (g2-expression-cell-index nil vector-slot system)
  (g2-expression-cell-cached-value nil vector-slot system do-not-clone)
  (g2-expression-cell-wake-up-task nil vector-slot system do-not-clone)
  (things-this-g2-expression-cell-is-interested-in
    nil vector-slot system do-not-clone)
  (g2-expression-cell-cyclic-task nil vector-slot system do-not-clone)
  (g2-expression-cell-byte-code-body nil vector-slot system save)
  (g2-expression-cell-chaining-links nil vector-slot system save)
  (g2-expression-cell-postponed-clean-ups nil vector-slot system do-not-clone))

(defun g2-expression-cell-byte-code-body-function (g2-expression-cell)
  (g2-expression-cell-byte-code-body g2-expression-cell))

#+development
(defun g2-expression-cell-cyclic-task-function (x) 
  (g2-expression-cell-cyclic-task x))

(def-absent-slot-putter g2-expression-cell-expression (ignored-frame expression)
  (declare (ignore ignored-frame))
  (reclaim-slot-value expression))

(def-slot-value-reclaimer g2-expression-cell-g2-cell-array
			  (parent-array g2-expression-cell)
  (declare (ignore parent-array))
  ;; Avoid cycle with deleting this dependent frame
  (setf (g2-expression-cell-g2-cell-array g2-expression-cell) nil))

(def-slot-value-reclaimer g2-expression-cell-computation-style
			  (computation-style)
  (deregister-use-of-computation-style computation-style))

(def-slot-value-reclaimer g2-expression-cell-cached-value
			  (item-or-evaluation-value?)
  (reclaim-if-evaluation-value item-or-evaluation-value?))

(def-class-method copy-frame (g2-expression-cell)
  (let ((result (funcall-superior-method g2-expression-cell)))
    (let*-sim ((current-block-of-dependent-frame 'dependent-frame-has-no-owner))
      (register-use-of-computation-style 
	(setf (g2-expression-cell-computation-style result)
	      (g2-expression-cell-computation-style g2-expression-cell))))
    result))




;;; The function `Rebuild-backpointers-of-cells-of-g2-cell-array' is called
;;; indirectly by the slot putter that owns the parent g2-cell-array.  It
;;; assures that the backpointers are correct after loading and cloning frames
;;; of this kind.

;;; Note that for cloning it must traverse into the chaining links and redirect
;;; them to point to the new parent frame.  Since it doesn't harm anything to do
;;; this redundantly, it will always be done when rebuilding backpointers.  -jra
;;; 9/10/91
 
(defun rebuild-backpointers-of-cells-of-g2-cell-array
       (g2-cell-array parent-frame)
  (let ((managed-array (g2-cell-array-managed-array g2-cell-array)))
    (when managed-array
      (loop for index from 0 below (managed-array-length managed-array)
	    as cell = (managed-svref managed-array index)
	    do
	(when (and cell (g2-expression-cell-p cell))
	  (setf (g2-expression-cell-g2-cell-array cell) g2-cell-array)
	  (setf (g2-expression-cell-index cell) index)
	  (rebuild-backpointers-of-g2-expression-cell-chaining-links
	    cell parent-frame))))))




;;; The function `rebuild-backpointers-of-g2-expression-cell-chaining-links'
;;; redirects forward chaining links to send them to the given parent frame.
;;; This function is called as part of the backpointer regeneration function,
;;; called during slot putting of a g2-cell-array into the parent frame block.

(defun rebuild-backpointers-of-g2-expression-cell-chaining-links
       (g2-expression-cell parent-frame)
  (loop for (nil . forward-chaining-link) ;; See Note 1.
	    in (g2-expression-cell-chaining-links g2-expression-cell)
	do
    (redirect-chaining-link-recipient forward-chaining-link parent-frame)))

;; Note 1: This new destructuring should be in the redirect routine maybe?
;; Bug fix by Ben 9/19/91





;;; The slot putter for the chaining links of a g2-expression-cell should
;;; deinstall any old links stored in the cell, install any new links, and then
;;; change the slot value of the cell.

(def-slot-putter g2-expression-cell-chaining-links
		 (g2-expression-cell chaining-links)
  (let ((old-links (g2-expression-cell-chaining-links g2-expression-cell))
	(current-block-of-dependent-frame
	  (if loading-kb-p
	      'dependent-frame-has-no-owner
	      current-block-of-dependent-frame)))
    (setf (g2-expression-cell-chaining-links g2-expression-cell) chaining-links)
    (deinstall-chaining-links old-links)
    (install-chaining-links chaining-links)
    chaining-links))




;;; The cleanup method for g2-expression-cells sets the chaining links slot
;;; back to NIL so that the properties hold chaining links for this cell are
;;; removed.

(def-class-method cleanup (g2-expression-cell)
  (funcall-superior-method g2-expression-cell)
  (change-slot-value
    g2-expression-cell 'g2-expression-cell-chaining-links nil))

;;;






;;;; Cell Value Types




;;; The macro `create-cell-class-type' takes a class name and returns cell-type
;;; object representing that type.  Cell types are slot values, and may be
;;; copied and reclaimed with the slot value facilities.

;;; The macro `create-cell-datum-type' takes a datum type symbol and returns a
;;; cell-type object representing that type.  The datum type symbols are number
;;; (which prints through write-data-type-for-slot as quantity to users),
;;; integer, float, truth-value, symbol, and text.  Datum cell types are also
;;; slot values.

;;; The macro `cell-class-type-p' and `cell-datum-type-p' are predicates which
;;; differentiate cell class types and cell datum types.  These predicates may
;;; return false positives on data structures which are not currently related to
;;; cell arrays, but look like them.

;;; The macros `class-of-cell-class-type' and `datum-type-of-cell-datum-type'
;;; take their respective cell types, and return the symbols which name the
;;; given types.

(defmacro create-cell-class-type (class)
  `(slot-value-cons 'cell-class ,class))

(defmacro create-cell-datum-type (datum-type)
  datum-type)

(def-substitution-macro cell-class-type-p (cell-type)
  (and (consp cell-type) (eq (car cell-type) 'cell-class)))

(defmacro cell-datum-type-p (cell-type)
  `(valid-datum-type-specification-p ,cell-type))

(defmacro class-of-cell-class-type (cell-class-type)
  `(cdr ,cell-class-type))

(defmacro datum-type-of-cell-datum-type (cell-datum-type)
  cell-datum-type)

(defun convert-cell-type-to-type-specification (cell-type)
  (if (cell-class-type-p cell-type)
      (make-class-type-specification (class-of-cell-class-type cell-type))
      cell-type))






;;;; Query Cell Computations




;;; Query Cells hold designations, possibly generic, which will be role served
;;; to acquire an ordered set of elements.  The cached values of these cells are
;;; always delivered to users through query-cell-streams, defined later in this
;;; section.



;;; The function `register-query-cell' takes a cell array, a parsed, generic
;;; designation, and a cell-type as its arguments and returns a number which is
;;; the cell array location in which that query cell has been registered.  This
;;; query cell is referenced with the returned number in all other operations
;;; dealing with this cell.

;;; The grammar category which should be used to produce the generic designation
;;; is just designation.

(defun register-query-cell (g2-cell-array)
  (let* ((new-location (find-new-location-for-cell g2-cell-array))
	 (managed-array (g2-cell-array-managed-array g2-cell-array))
	 (query-cell (make-frame 'g2-query-cell)))
    (setf (managed-svref managed-array new-location) query-cell)
    new-location))



;;; `activate-g2-query-cell' ...

(defun activate-g2-query-cell (query-cell)
  (declare (ignore query-cell))
  ;; TBD
  )



;;; `deactivate-g2-query-cell' ...

(defun deactivate-g2-query-cell (query-cell)
  (declare (ignore query-cell))
  ;; TBD
  )



;;; The macro `get-query-cell-cache' takes a g2-cell-array and an index to a
;;; query-cell within that array.  This function returns a query-cell-stream to
;;; the current cached value within that query cell.

;;; Note that it is an error to pass an index to this function which does not
;;; name a query-cell.

(defmacro get-query-cell-cache (g2-cell-array query-cell-index)
  `(get-query-cell-cache-given-query-cell
     (managed-svref (g2-cell-array-managed-array ,g2-cell-array)
		    ,query-cell-index)))




;;; The macro `get-query-cell-cache-given-query-cell' is an internal macro of
;;; the query-cell facility which takes a query cell and returns
;;; query-cell-stream to the currently cached value of that cell.

(def-substitution-macro get-query-cell-cache-given-query-cell (query-cell)
  #+development
  (unless (g2-query-cell-p query-cell)
    (error
      "GET-QUERY-CELL-CACHE given an index not naming a g2-query-cell."))
  (let ((cache? (g2-query-cell-cached-value query-cell)))
    (if cache?
	(make-query-cell-stream-to-cached-value
	  cache?
	  (g2-query-cell-frame-serial-number? query-cell))
	nil)))




;;; The macro `make-query-cell-cached-value' takes an eval cons list of cached
;;; role values and creates a data structure suitable for caching in the
;;; query-cell-cached-value slot of a query-cell.  The second argument is the
;;; type, which will be used at some future date to optimize storage of the guts
;;; of this stuff.  Query cell cached values have a reference count within them.
;;; This operation returns a cache with a reference count of one.  When the
;;; frame finally releases this cached value, it should decrement the reference
;;; count with the operation which follows.

(defmacro make-query-cell-cached-value (eval-cons-list-of-values type)
  (declare (ignore type))
  `(eval-cons 1 ,eval-cons-list-of-values))




;;; The macro `decrement-query-cell-reference-count' takes a query-cell cached
;;; value and decrements its reference count.  If the reference count is zero,
;;; this function then reclaims the cache.

(defmacro decrement-query-cell-reference-count
	  (query-cell-cached-value frames?)
  (let* ((rebind? (not (symbolp query-cell-cached-value)))
	 (cached-value (if rebind? (gensym) query-cell-cached-value))
	 (reference-count (gensym))
	 (bindings `((,reference-count (-f (car ,cached-value) 1)))))
    (when rebind?
      (push `(,cached-value ,query-cell-cached-value) bindings))
    `(let* ,bindings
       (if (=f ,reference-count 0)
	   (reclaim-query-cell-cached-value ,cached-value ,frames?)
	   (setf (car ,cached-value) ,reference-count))
       nil)))




;;; The macro `increment-query-cell-reference-count' takes a query-cell cached
;;; value and increments its reference count.  It returns no useful value.

(defmacro increment-query-cell-reference-count (query-cell-cached-value)
  `(incff (car ,query-cell-cached-value)))




;;; The function `reclaim-query-cell-cached-value' takes a query-cell cached
;;; value whose reference count has reached zero and reclaims it.

(defun reclaim-query-cell-cached-value (query-cell-cached-value frames?)
  (if frames?
      (reclaim-eval-list-macro query-cell-cached-value)
      (loop for trailer = (cdr query-cell-cached-value) then value-cons?
	    for value-cons? = (cdr trailer)
	    while value-cons?
	    for value = (car value-cons?)
	    do
	(cond ((managed-float-p value)
	       (reclaim-managed-float value))
	      ((text-string-p value)
	       (reclaim-text-string value)))
	    finally
	      (reclaim-eval-list-given-tail
		query-cell-cached-value trailer)))
  nil)




;;; The structure `query-cell-stream' is used to represent streams of values
;;; provided by query-cells.

(def-structure (query-cell-stream
		 (:constructor make-query-cell-stream-1
			       (query-cell-stream-cached-value
				 query-cell-stream-frame-serial-number
				 query-cell-stream-current-position))
		 (:reclaimer reclaim-query-cell-stream-1))
  query-cell-stream-cached-value
  (query-cell-stream-frame-serial-number nil :reclaimer reclaim-frame-serial-number)
  query-cell-stream-current-position)




;;; The function `make-query-cell-stream-to-cached-value' takes a query cell
;;; cached value and a frame serial number or NIL.  This function increments the
;;; cached value's reference count, and returns a stream to its values.  If the
;;; stream holds no frames, the frame-serial-number?  argument should be NIL.

(defun make-query-cell-stream-to-cached-value
       (query-cell-cached-value frame-serial-number?)
  (let ((new-stream (make-query-cell-stream-1-macro
		      query-cell-cached-value
		      (copy-frame-serial-number frame-serial-number?)
		      (cdr query-cell-cached-value))))
    (increment-query-cell-reference-count query-cell-cached-value)
    new-stream))




;;; The function `reclaim-query-cell-stream' takes a query cell stream and
;;; reclaims it.

(defun reclaim-query-cell-stream (query-cell-cached-value-stream)
  (decrement-query-cell-reference-count
    (query-cell-stream-cached-value query-cell-cached-value-stream)
    (query-cell-stream-frame-serial-number query-cell-cached-value-stream))
  (reclaim-query-cell-stream-1-macro query-cell-cached-value-stream)
  nil)




;;; The function `register-query-cell-designation' is used to install a new
;;; designation into a query cell, or to replace an existing designation with a
;;; new one.  If there was a cached value from the old desigination, this cache
;;; is removed, and the parent frame updated.  This function returns NIL.

(defun register-query-cell-designation
       (g2-cell-array index generic-designation cell-type)
  (let ((query-cell
	  (managed-svref (g2-cell-array-managed-array g2-cell-array) index)))
    (reclaim-slot-value (g2-query-cell-generic-designation query-cell))
    (reclaim-slot-value (g2-query-cell-value-type query-cell))
    (setf (g2-query-cell-generic-designation query-cell)
	  (copy-for-slot-value generic-designation))
    (setf (g2-query-cell-value-type query-cell)
	  (copy-for-slot-value cell-type))
    (update-query-cell-cached-value
      query-cell g2-cell-array index nil nil)
    nil))




;;; The macro `end-of-query-cell-stream-p' is a predicate that takes a
;;; query-cell-stream and returns non-nil when the stream is exhausted.

(def-substitution-macro end-of-query-cell-stream-p (query-cell-stream)
  (or (null (query-cell-stream-current-position query-cell-stream))
      (not (or (null (query-cell-stream-frame-serial-number query-cell-stream))
	       (frame-has-not-been-reprocessed-p
		 (car (query-cell-stream-current-position query-cell-stream))
		 (query-cell-stream-frame-serial-number query-cell-stream))
	       (query-cell-stream-iterate-to-undeleted-frame
		 query-cell-stream)))))

(defun query-cell-stream-iterate-to-undeleted-frame
       (query-cell-stream-with-deleted-frame)
  (loop with stored-frame-serial-number =
	  (query-cell-stream-frame-serial-number
	    query-cell-stream-with-deleted-frame)
	for position-cons =
	    (cdr (query-cell-stream-current-position
		   query-cell-stream-with-deleted-frame))
	    then position-cons
	until (or (null position-cons)
		  (frame-has-not-been-reprocessed-p
		    (car position-cons)
		    stored-frame-serial-number))
	finally
	  (setf (query-cell-stream-current-position
		  query-cell-stream-with-deleted-frame)
		position-cons)
	  (return-from query-cell-stream-iterate-to-undeleted-frame
	    (null position-cons))))




;;; The macro `read-query-cell-stream' takes a query-cell-stream and returns the
;;; next available value in the stream.  If the stream contains frames, it
;;; returns the next available frame.  If it contains datum, it returns the
;;; managed-number-or-value of that datum.  Note that you do not have to reclaim
;;; any datum returned by this operation, and that this facility will not
;;; reclaim the datum returned to you until some time after you have called for
;;; the next datum from this stream.

;;; Also note that you must call this function immediately after calling
;;; end-of-query-cell-stream-p.  If a frame could possibly have been deleted
;;; after the last call to the end of stream predicate, then you must call the
;;; predicate again before calling this reader.

(defmacro read-query-cell-stream (non-empty-query-cell-stream)
    (if (symbolp non-empty-query-cell-stream)
	`(let ((position-cons (query-cell-stream-current-position
				,non-empty-query-cell-stream)))
	   (setf (query-cell-stream-current-position
		   ,non-empty-query-cell-stream)
		 (cdr position-cons))
	   (car position-cons))
	`(let* ((non-empty-query-cell-stream ,non-empty-query-cell-stream)
		(position-cons (query-cell-stream-current-position
				 non-empty-query-cell-stream)))
	   (setf (query-cell-stream-current-position
		   non-empty-query-cell-stream)
		 (cdr position-cons))
	   (car position-cons))))



;;; `Query-cell-updated' is a class method which should be defined for all subclasses of blocks
;;; that use cell arrays containing query-cells.  It is called to notify the block
;;; that an update has occurred.  A block, the cell-array, cell-index, and old and new stream
;;; values are passed.  The old stream value maybe nil.

(def-generic-method query-cell-updated (block cell-array cell-index old-value-stream? new-stream)
  )



;;; The function `compute-new-query-cell-value' takes the g2-cell-array which
;;; contains a query-cell, the index to that query-cell, and the query-cell
;;; itself.  This function creates a query-cell-stream to the old cached value,
;;; drops the reference to the old cached value, computes a new cached value,
;;; caches it, creates a stream to the new cached value, and calls the method
;;; query-cell-updated on the parent frame, passing the g2-cell-array, the index
;;; to this cell, the old value stream, and the new value stream.

(defun compute-new-query-cell-value (g2-cell-array index query-cell)
  (let* ((parent-frame (g2-cell-array-parent-frame g2-cell-array))
	 (cell-type (g2-query-cell-value-type query-cell))
	 (frame-type? (cell-class-type-p cell-type))
	 (raw-type (if frame-type?
		       (class-of-cell-class-type cell-type)
		       (datum-type-of-cell-datum-type cell-type)))
	 (*current-computation-frame* parent-frame))
    (let* ((new-values (serve-eval-list-of-designation-values
			 (g2-query-cell-generic-designation query-cell))))
      ;; Guarantee new cache is ok.
      (unless (if frame-type?
		  (loop for frame in new-values
			always (of-class-p frame raw-type))
		  (loop for temporary-constant in new-values
			always (and (temporary-constant-p temporary-constant)
				    (value-type-compatible
				      (constant-type temporary-constant)
				      raw-type))))
	;; Issue some warning.
	(loop for element in new-values do
	  (reclaim-if-temporary-constant element))
	(reclaim-eval-list new-values)
	(setq new-values nil))
      (unless frame-type?
	(loop for value-cons on new-values
	      for temporary-constant = (car value-cons)
	      do
	  (setf (car value-cons)
		(reclaim-temporary-constant-returning-managed-value
		  temporary-constant))))
      ;; Finally, update the cell.
      (let* ((new-cache?
	       (if new-values
		   (make-query-cell-cached-value new-values cell-type)
		   nil))
	     (new-frame-serial-number?
	       (if (and new-values frame-type?)
		   (copy-frame-serial-number (current-frame-serial-number))
		   nil)))
	(update-query-cell-cached-value
	  query-cell g2-cell-array index new-cache? new-frame-serial-number?)
	(reclaim-frame-serial-number new-frame-serial-number?)
	nil))))




;;; The function `update-query-cell-cached-value' is the internal function of
;;; query cells which installs updated values of the cache.  This function takes
;;; a query-cell, its g2-cell-array, the new cached-value, and the
;;; frame-serial-number if any for the cached value.  This function installs the
;;; new cached value, calls the update function of the parent frame of the
;;; g2-cell-array, and reclaims the old cached value of the query-cell.

(defun update-query-cell-cached-value
       (query-cell g2-cell-array index new-cache? frame-serial-number?)
  (let ((old-value-stream? nil)
	(old-cache? (g2-query-cell-cached-value query-cell)))
    (when (or old-cache? new-cache?)
      (when old-cache?
	(setq old-value-stream?
	      (make-query-cell-stream-to-cached-value
		old-cache?
		(g2-query-cell-frame-serial-number? query-cell)))
	(decrement-query-cell-reference-count
	  old-cache?
	  (g2-query-cell-frame-serial-number? query-cell)))
      (setf (g2-query-cell-cached-value query-cell) new-cache?)
      (frame-serial-number-setf (g2-query-cell-frame-serial-number? query-cell)
	    frame-serial-number?)
      (funcall-method
	'query-cell-updated
	(g2-cell-array-parent-frame g2-cell-array)
	g2-cell-array index
	old-value-stream?
	(if new-cache?
	    (make-query-cell-stream-to-cached-value
	      new-cache? frame-serial-number?)
	    nil)))
    nil))




;;; The slot value reclaimer for the g2-query-cell-cached-value slot of
;;; g2-query-cells should decrement the reference count to the cached value.  If
;;; there are no currently open query-cell-streams to this cached value, it will
;;; then be reclaimed.

;;; reclaim the frame serial number here, rather than in its own slot-value-reclaimer, because it must be reclaimed
;;; after the cached value.
(def-slot-value-reclaimer g2-query-cell-cached-value
			  (cached-value g2-query-cell)
  (decrement-query-cell-reference-count
    cached-value
    (g2-query-cell-frame-serial-number? g2-query-cell))
  (setf (g2-query-cell-cached-value g2-query-cell) nil)
  (reclaim-frame-serial-number (g2-query-cell-frame-serial-number? g2-query-cell))
  (setf (g2-query-cell-frame-serial-number? g2-query-cell) nil)
  nil)

(def-slot-value-reclaimer g2-query-cell-frame-serial-number? (serial-number)
  ;;; already reclaimed in reclaimer for g2-query-cell-cached-value above
  (declare (ignore serial-number))
  nil)

;;; The function `analyze-g2-query-cell-for-consistency' takes a query-cell and
;;; analyzes its stored designation, if any.

(defun analyze-g2-query-cell-for-consistency (query-cell)
  (let ((designation? (g2-query-cell-generic-designation query-cell)))
    (when designation?
      (analyze-compiled-form designation? nil nil))))






;;;; Designation Cell Computations




;;; G2 Designation Cells hold registered designations.  Their cache values are
;;; returned as frames or managed values, not as streams, since they can have
;;; only one value at a time.

;;; The function `register-designation-cell takes a cell array, a parsed, unique
;;; designation, and a cell-type as its arguments and returns a number which is
;;; the cell array location in which that designation cell has been registered.
;;; This designation cell is referenced with the returned number in all other
;;; user operations dealing with this cell.

;;; The grammar category which should be used to produce the designation
;;; is unique-designation (maybe constant-designation).

(defun register-designation-cell (g2-cell-array unique-designation cell-type)
  (let* ((new-location (find-new-location-for-cell g2-cell-array))
	 (managed-array (g2-cell-array-managed-array g2-cell-array))
	 (new-cell (make-frame 'g2-designation-cell)))
    (declare (type fixnum new-location))
    (setf (managed-svref managed-array new-location) new-cell)
    (setf (g2-query-cell-generic-designation new-cell)
	  (copy-for-slot-value unique-designation))
    (setf (g2-query-cell-value-type new-cell)
	  (copy-for-slot-value cell-type))
    new-location))




;;; The function `register-designation-cell-designation' takes a g2-cell-array,
;;; an index to a designation, a new designation, and a new cell-type.  This
;;; will replace the designation and type in a designation-cell and clear its
;;; cache.

(defun register-designation-cell-designation
       (g2-cell-array index unique-designation cell-type)
  (let ((designation-cell
	  (managed-svref (g2-cell-array-managed-array g2-cell-array) index)))
    (reclaim-slot-value (g2-query-cell-generic-designation designation-cell))
    (reclaim-slot-value (g2-query-cell-value-type designation-cell))
    (setf (g2-query-cell-generic-designation designation-cell)
	  (copy-for-slot-value unique-designation))
    (setf (g2-query-cell-value-type designation-cell)
	  (copy-for-slot-value cell-type))
    (update-designation-cell-cached-value
      designation-cell g2-cell-array index nil nil)
    nil))



;;; `activate-g2-designation-cell' ...

(defun activate-g2-designation-cell (designation-cell)
  (declare (ignore designation-cell))
  ;; TBD
  )



;;; `deactivate-g2-designation-cell' ...

(defun deactivate-g2-designation-cell (designation-cell)
  (declare (ignore designation-cell))
  ;; TBD
  )



;;; The macro `get-designation-cell-cache' takes g2-cell-array and an index
;;; into that array that points to a designation cell.  This function will
;;; return a frame, managed-value, or nil from the cache in that cell.  Note
;;; that a NIL could come from this cell in two ways, either the designation did
;;; not denote anything at the last update, or the frame which is previously
;;; denoted has been deleted.

(defmacro get-designation-cell-cache (g2-cell-array index)
  (let ((g2-designation-cell (gensym))
	(cache? (gensym))
	(frame-serial-number? (gensym)))
    `(let* ((,g2-designation-cell
	      (managed-svref (g2-cell-array-managed-array ,g2-cell-array)
			     ,index))
	    (,cache?
	      (g2-designation-cell-cached-value ,g2-designation-cell))
	    (,frame-serial-number?
	      (g2-designation-cell-frame-serial-number? ,g2-designation-cell)))
       (if ,frame-serial-number?
	   (if (frame-has-not-been-reprocessed-p ,cache? ,frame-serial-number?)
	       ,cache?
	       nil)
	   ,cache?))))




;;; The function `compute-new-designation-cell-value' takes a g2-cell-array, an
;;; index to a designation cell, and the designation cell itself as values.  It
;;; begins an update to the designation.

;;; This will have to be rewritten when we can have backward chaining from
;;; roles (like real soon).  -jra 2/1/91

(defun compute-new-designation-cell-value
       (g2-cell-array index designation-cell)
  (let* ((type (g2-designation-cell-value-type designation-cell)) 
	 (*current-computation-frame*
          (g2-cell-array-parent-frame g2-cell-array))
	 (new-value? (evaluate-designation
		       (g2-designation-cell-designation designation-cell)
		       nil)))
    (when new-value?
      (if (cell-class-type-p type)
	  (when (not (of-class-p new-value? (class-of-cell-class-type type)))
	    ;; Issue warning.
	    (reclaim-if-temporary-constant new-value?)
	    (setq new-value? nil))
	  (cond ((or (not (temporary-constant-p new-value?))
		     (not (value-type-compatible
			    (datum-type-of-cell-datum-type type)
			    (constant-type new-value?))))
		 ;; Issue warning.
		 (reclaim-if-temporary-constant new-value?)
		 (setq new-value? nil))
		(t
		 (setq new-value?
		       (reclaim-temporary-constant-returning-managed-value
			 new-value?))))))
    (let ((new-frame-serial-number?
	    (if (and new-value? (cell-class-type-p type))
		(copy-frame-serial-number (current-frame-serial-number))
		nil)))
      (update-designation-cell-cached-value
	designation-cell g2-cell-array index
	new-value? new-frame-serial-number?)
      (reclaim-frame-serial-number new-frame-serial-number?)
      nil)))


;;; `Designation-cell-updated' is a class method which should be defined for all subclasses of blocks
;;; that use cell arrays containing designation-cells.  It is called to notify the block
;;; that an update has occurred.  A block, its cell-array, a cell-index, and old and new values
;;; values are passed.  Either value maybe nil.

(def-generic-method designation-cell-updated (block cell-array cell-index old-value? new-value?)
  )





;;; The function `update-designation-cell-cached-value' takes a
;;; designation-cell, a g2-cell-array, the cell's index, a new value to cache in
;;; the cell, and the frame serial number if any of that frame.  This function
;;; installs the new value in the cell, calls the parent's update function if
;;; the value has changed, and then reclaims the old value.

(defun update-designation-cell-cached-value
       (designation-cell g2-cell-array index new-cache? frame-serial-number?)
  (let ((old-cache? (g2-designation-cell-cached-value designation-cell))
	(old-frame-serial-number?
	  (g2-designation-cell-frame-serial-number? designation-cell)))
    (when (or old-cache? new-cache?)
      (setf (g2-designation-cell-cached-value designation-cell)
	    new-cache?)
      (frame-serial-number-setf (g2-designation-cell-frame-serial-number? designation-cell)
	    frame-serial-number?)
      (funcall-method
	'designation-cell-updated
	(g2-cell-array-parent-frame g2-cell-array)
	g2-cell-array
	index
	(if (or (null old-frame-serial-number?)
		(frame-has-not-been-reprocessed-p
		  old-cache? old-frame-serial-number?))
	    old-cache?
	    nil)
	new-cache?)
      (when (and old-cache? (null old-frame-serial-number?))
	(reclaim-managed-number-or-value old-cache?)))
    nil))




;;; The function `analyze-g2-designation-cell-for-consistency' takes a
;;; g2-designation-cell and analyzes it for consistency.

(defun analyze-g2-designation-cell-for-consistency (g2-designation-cell)
  (let ((designation? (g2-designation-cell-designation g2-designation-cell)))
    (when designation?
      (analyze-compiled-form designation? nil nil))))






;;;; Expression Cell Computations




;;; Expression Cells are used to execute expressions.  Values retrieved from the
;;; caches of expression cells are always managed values, or NIL if no value is
;;; yet available.



;;; `Make-empty-expression-cell' inserts a new expression cell into the
;;; g2-cell-array provided as its one and only argument.  The index of that cell
;;; is returned.  The caller should install that index into his data structures,
;;; and then immediately register an expression into the cell.

;;; This is the one and only case where a change to the cell's cached value does
;;; not propogate an update to the parent frame.  The caller must compensate for
;;; that to assure that the update generated by the initial registration of an
;;; expression will not erase the default cached value.  The cached value is nil
;;; in an empty expression cell.

(defun make-empty-expression-cell (g2-cell-array)
  (let* ((current-block-of-dependent-frame
	   'dependent-frame-has-no-owner)
	 (new-location (find-new-location-for-cell g2-cell-array))
	 (managed-array (g2-cell-array-managed-array g2-cell-array))
	 (new-cell (make-frame 'g2-expression-cell)))
    (setf (managed-svref managed-array new-location) new-cell)
    (setf (g2-expression-cell-g2-cell-array new-cell) g2-cell-array)
    (setf (g2-expression-cell-index new-cell) new-location)
    (setf (g2-expression-cell-value-type new-cell)
	  'empty-expression-cell)
    new-location))




;;; The function `expression-cell-able-to-compute-p' takes an expression cell
;;; and returns whether or not that cell is compiled such that it can attempt to
;;; compute its value.  A reason why it could be able to do so is that it is new
;;; and has no expression registered in it, or that the last expression
;;; registered did not compile correctly.

(defmacro expression-cell-able-to-compute-p (expression-cell)
  `(not (eq (g2-expression-cell-value-type ,expression-cell)
	    'empty-expression-cell)))




;;; The function `remove-compilation-from-obsolete-expression-cell' takes an
;;; expression cell, removes its compilation, and changes the cell so that it is
;;; recognized as unexecutable.

(defun remove-compilation-from-obsolete-expression-cell (expression-cell)
  (change-slot-value expression-cell 'g2-expression-cell-byte-code-body nil)
  (change-slot-value expression-cell 'g2-expression-cell-chaining-links nil)
  (change-slot-value
    expression-cell 'g2-expression-cell-value-type 'empty-expression-cell))




;;; `Register-expression-cell-during-compilation' compiles an expression and
;;; stores it into the given expression cell.

;;; Requirements on the dynamic state include
;;;  - Called within a phrase-consing context, such as provided by an
;;;    editor-state or with-phrase-conses
;;;  - approprate bindings outstanding for
;;;    - *current-computation-frame* and
;;;    - current-computation-style,
;;;  - The analysis of consistency for the parent frame
;;;    should currently be retracted.

;;; This routine has a few side effects on the frame that owns the cell.  New
;;; frame notes may be created as a side effect of the compilation.  The compiled
;;; expression is stored into the cell, the cell registers an interest in the
;;; current computation style.  The cached value is set to NIL.

;;; Those side effects do not finish the task of getting an expression into a
;;; cell.  The slot putter, called once the compile is finished, must store the
;;; cell index into the parent frame, arrange to do the initial update, and
;;; finally spawn any cyclic tasks.  Some of these steps maybe done using the
;;; routine update-g2-expression-cell-after-edit.

;;; In keeping with the style for compilers in the evalutators this routine
;;; never rejects the parse.  (Good thing given its having all these side
;;; effects.) It always returns nil.

;;; The first two arguments (the cell array and cell index) state where the
;;; expression will be installed.  The two remaining arguments (expression and
;;; cell-type) are the expression and type desired.  Then expression is an
;;; parse, like that specified by the grammar type expression The cell-type is a
;;; datum of the type specified in the "Cell Value Types" section above.

;;; Registration does not generate a display update call back to the enclosing
;;; frame.  That's good since the cell index is probably not yet stored into the
;;; enclosing frame.  If the cell is currently installed in its parent frame and
;;; the parent frame is active, it will attempt to incrementally mutate the
;;; installation.

(defun register-expression-cell-during-compilation
       (g2-cell-array index cell-installed-in-parent?
	&optional expression? cell-value-type-specification? domain? attribute?)
  (note-change-to-dependent-frame)
  (let* ((expression-cell
	   (managed-svref (g2-cell-array-managed-array g2-cell-array) index))
	 (old-computation-style?
	   (g2-expression-cell-computation-style expression-cell)))
    (multiple-value-bind (recompile? reschedule-scan?)
	(compare-computation-styles-for-installation-differences
	  current-computation-style old-computation-style?)
      (when old-computation-style?
	(deregister-use-of-computation-style old-computation-style?))
      (setf (g2-expression-cell-computation-style expression-cell) 
	    (register-use-of-computation-style current-computation-style))
      (cond
	(expression?
	 (reclaim-slot-value (g2-expression-cell-value-type expression-cell))
	 (change-slot-value
	   expression-cell 'g2-expression-cell-byte-code-body nil)
	 (change-slot-value
	   expression-cell 'g2-expression-cell-chaining-links nil)
	 (let* ((argument-and-type-list?
		  (when (and (consp expression?)
			     (eq (car-of-cons expression?) 'g2-lambda))
		    (prog1 (second expression?)
			   (setq expression? (third expression?)))))
		(first-pass-compiled-expression?
		  (if (and domain? attribute?)
		      (compile-generic-formula
			expression? domain? attribute?
			(g2-cell-array-parent-frame g2-cell-array))
		      (compile-expression
			expression? nil
			(loop for (binding-name) in argument-and-type-list?
			      collect binding-name using gensym-cons))))
		(byte-code-body?
		  (when first-pass-compiled-expression?
		    (compile-expression-cell-for-stack
		      first-pass-compiled-expression?
		      argument-and-type-list? cell-value-type-specification?)))
		(chaining-links
		  (when (and byte-code-body?
			     (computation-style-may-request-event-updates
			       current-computation-style))
		    (generate-cell-chaining-links
		      'schedule-expression-cell-execution-for-true-value-update
		      (g2-cell-array-parent-frame g2-cell-array)
		      index
		      expression?))))
	   ;; Compile and install the expression, then record the type and
	   ;; computation style.
	   (setf (g2-expression-cell-value-type expression-cell)
		 (if (or (null byte-code-body?)
			 (null (byte-code-body-environment-description
				 byte-code-body?)))
		     'empty-expression-cell
		     (copy-for-slot-value cell-value-type-specification?)))
	   (change-slot-value expression-cell 'g2-expression-cell-byte-code-body
			      byte-code-body?)
	   (change-slot-value expression-cell 'g2-expression-cell-chaining-links
			      chaining-links)))
	;; The recompile call here will cycle back into this fucnction with a
	;; parsed expression.
	(recompile?
	 (recompile-item current-block-of-dependent-frame)))
      (when (and reschedule-scan?
		 cell-installed-in-parent?
		 (runnable-p current-block-of-dependent-frame))
	(schedule-or-deschedule-g2-expression-cell-cyclic-task
	  expression-cell nil nil))
      nil)))




;;; `Register-expression-cell-during-slot-putter' is called after the cell index
;;; is put into the enclosing frame.  It is responsible for the final stages of
;;; installing the expression into the cell if it was not previously installed,
;;; and responding to the edit event.

;;; Nil is always returned.  The routine never fails.  Tasks may be created.  A
;;; display update call back to the enclosing frame occurs in the recursive
;;; descent.

;;; The activation state of the enclosing frame is propagated into the cell.

;;; An attempt to compute a new value is made in the recursive decent of this
;;; function if the KB is paused.  If the system is running, then the attempt is
;;; scheduled.  This attempt will cause a display update call back.  If the
;;; attempt is not made then a display update call back is generated directly.

;;; Note that the update-after-edits flag does not override the
;;; update-only-when-shown flag.

(defun register-expression-cell-during-slot-putter
       (g2-cell-array index cell-previously-installed-in-parent?)
  (let* ((expression-cell
	   (managed-svref (g2-cell-array-managed-array g2-cell-array) index))
	 (computation-style
	   (g2-expression-cell-computation-style expression-cell))
	 (parent-frame (g2-cell-array-parent-frame g2-cell-array))
	 (parent-runnable? (runnable-p parent-frame)))
    (when (and parent-runnable?
	       (not cell-previously-installed-in-parent?))
      (activate-g2-expression-cell expression-cell))
    (cond ((and parent-runnable?
		(or system-is-running (runs-while-inactive-p parent-frame))
		(computation-style-update-after-edits 
		  computation-style))
	   (schedule-expression-cell-execution
	     (g2-cell-array-parent-frame g2-cell-array) index nil)
	   (update-expression-cell-cached-value
	     expression-cell g2-cell-array index nil nil))
	  ((and parent-runnable?
		(and system-has-paused
		     (not (runs-while-inactive-p parent-frame)))
		(computation-style-update-after-edits 
		  computation-style)
		(or (not (computation-style-update-only-when-shown
			   computation-style))
		    (showing-p parent-frame nil)))
	   (attempt-expression-cell-execution-during-slot-putter
	     expression-cell))
	  (t
	   (update-expression-cell-cached-value
	     expression-cell g2-cell-array index nil nil)))
    nil))




;;; `activate-g2-expression-cell' in the recursive decent of activation, and when
;;; a new cell is created in an active computation frame.

(defun-void activate-g2-expression-cell (expression-cell)
  (schedule-or-deschedule-g2-expression-cell-cyclic-task expression-cell t t))




;;; The function `schedule-or-deschedule-expression-cell-cyclic-task' is used to
;;; schedule or reschedule the cyclic task for an expression-cell.  It takes an
;;; argument which controls whether or not the initial wait interval is paid
;;; attention to.

(defun-void schedule-or-deschedule-g2-expression-cell-cyclic-task
    (expression-cell initial-wait? parent-being-activated?)
  (let ((computation-style
	  (g2-expression-cell-computation-style expression-cell)))
    (cancel-task (g2-expression-cell-cyclic-task expression-cell))
    (when computation-style 
      (let* ((scan-interval? (computation-style-scan-interval computation-style))
	     (initial-wait-interval
	       (if initial-wait?
		   (computation-style-initial-scan-wait-interval
		     computation-style)
		   0))
	     (parent-frame
	       (g2-cell-array-parent-frame
		 (g2-expression-cell-g2-cell-array expression-cell))))
	(when (and (or (runnable-p parent-frame) parent-being-activated?)
		   scan-interval?
		   (or (and (fixnump scan-interval?) (>f scan-interval? 0))
		       (and (managed-float-p scan-interval?)
			    (with-temporary-gensym-float-creation schedule-cell
			      (>e (managed-float-value scan-interval?) 0.0))))
		   (or (not (computation-style-update-only-when-shown
			      computation-style))
		       (showing-p parent-frame nil)))
	  (with-temporary-creation
	      schedule-or-deschedule-g2-expression-cell-cyclic-task
	    (with-future-scheduling
		((g2-expression-cell-cyclic-task expression-cell)
		 (computation-style-priority computation-style)
		 (+e (managed-float-value current-g2-time)
		     (if (fixnump initial-wait-interval)
			 (coerce-fixnum-to-gensym-float initial-wait-interval)
			 (managed-float-value initial-wait-interval)))
		 (if (fixnump scan-interval?)
		     (coerce-fixnum-to-gensym-float scan-interval?)
		     (managed-float-value scan-interval?))
		 nil
		 (runs-while-inactive-p parent-frame))
	      (attempt-expression-cell-execution
		expression-cell
		nil
		(may-refer-to-inactive-items-p parent-frame)))))
	nil))))




;;; `deactivate-g2-expression-cell' ...

(defun-void deactivate-g2-expression-cell (expression-cell)
  (cancel-expression-cell-computation expression-cell))




;;; The macro `get-expression-cell-cache' takes a g2-cell-array and an index
;;; to an expression cell.  This returns a managed value, if there is a cached
;;; value, or NIL if there is no value currently cached.

(defmacro get-expression-cell-cache (g2-cell-array index)
  `(g2-expression-cell-cached-value 
     (managed-svref
       (g2-cell-array-managed-array
	 ,g2-cell-array)
       ,index)))




;;; The function `attempt-expression-cell-execution-during-slot-putter' should
;;; call the normal attempter after binding the priority of current task global
;;; variable to the priority of this item.  This is done to keep the backward
;;; chaining stuff, which looks at this variable, from crashing.

(defun-void attempt-expression-cell-execution-during-slot-putter (expression-cell)
  (let ((priority-of-current-task
	  (computation-style-priority
	    (g2-expression-cell-computation-style expression-cell))))
    (attempt-expression-cell-execution
      expression-cell nil
      (may-refer-to-inactive-items-p
	(g2-cell-array-parent-frame
	  (g2-expression-cell-g2-cell-array expression-cell))))))




;;; The function `schedule-expression-cell-execution-for-true-value-update' is
;;; used as the true value update function for those expression cells which are
;;; invokable via forward chaining.  Note that this forward chaining is actually
;;; true value update chaining, in that expiration events are propagated as
;;; well.  This function should schedule a task which will attempt execution.
;;; If there is already a scheduled task in place, then rescheduling should not
;;; be done.

(defun schedule-expression-cell-execution-for-true-value-update
       (containing-block index ignored-frame ignored-slot ignored-old-value
			 ignored-class-if-specific?)
  (declare (ignore ignored-frame ignored-slot ignored-old-value
		   ignored-class-if-specific?))
  (when (runnable-p containing-block)
    (schedule-expression-cell-execution containing-block index nil)))




;;; The function `schedule-expression-cell-execution' is used to trigger the
;;; beginning of an attempt to execute the held expression and update its value.
;;; This is the interface function for facilities which need to trigger
;;; executions on thier own.  The override-update-when-shown?  argument is used
;;; to force an udpate even when update-only-when-shown is true and the block is
;;; not shown.  The function `schedule-expression-cell-execution-given-cell' is
;;; an equivalent call when you already have a pointer to the expression-cell
;;; itself.

(defun-simple schedule-expression-cell-execution
    (containing-block index override-update-when-shown?)
  (let* ((g2-cell-array (cell-array containing-block))
	 (managed-array
	   (when g2-cell-array
	     (g2-cell-array-managed-array g2-cell-array)))
	 (expression-cell
	   (when (and (managed-array-p managed-array)
		      (<f index (managed-array-length managed-array)))
	     (managed-svref managed-array index))))
    (when (and expression-cell
	       (g2-expression-cell-p expression-cell))
      (schedule-expression-cell-execution-given-cell
	expression-cell containing-block override-update-when-shown?))
    nil))

(defun-void schedule-expression-cell-execution-given-cell
    (expression-cell containing-block override-update-when-shown?)
  (unless (or (not (expression-cell-able-to-compute-p expression-cell))
	      (schedule-task-in-place-p
		(g2-expression-cell-wake-up-task expression-cell)))
    (let ((computation-style
	    (g2-expression-cell-computation-style expression-cell)))
      (when (or override-update-when-shown?
		(not (computation-style-update-only-when-shown
		       computation-style))
		(showing-p containing-block nil))
	(with-current-scheduling
	    ((g2-expression-cell-wake-up-task expression-cell)
	     (computation-style-priority computation-style)
	     nil nil
	     (runs-while-inactive-p containing-block))
	  (attempt-expression-cell-execution
	    expression-cell nil
	    (may-refer-to-inactive-items-p containing-block)))))))




;;; The function `expression-cell-computation-in-progress-p' is used to check if
;;; an expression cell is currently attempting to execute its expression.

(defun-simple expression-cell-computation-in-progress-p (containing-block index)
  (let* ((g2-cell-array (cell-array containing-block))
	 (managed-array
	   (when g2-cell-array
	     (g2-cell-array-managed-array g2-cell-array)))
	 (expression-cell
	   (when (and managed-array
		      (<f index (managed-array-length managed-array)))
	     (managed-svref managed-array index))))
    (when (and expression-cell (g2-expression-cell-p expression-cell))
      (or (not (null (schedule-task-in-place-p
		       (g2-expression-cell-wake-up-task expression-cell))))
	  (not (null (things-this-g2-expression-cell-is-interested-in
		       expression-cell)))))))




;;; The function `cancel-scheduled-expression-cell-execution' takes a block and
;;; an index into its cell-array, and cancels any computation scheduled by
;;; schedule expression cell execution.

(defun-allowing-unwind cancel-scheduled-expression-cell-execution
		       (containing-block index)
  (let* ((g2-cell-array (cell-array containing-block))
	 (managed-array
	   (when g2-cell-array
	     (g2-cell-array-managed-array g2-cell-array)))
	 (expression-cell
	   (when (and managed-array
		      (<f index (managed-array-length managed-array)))
	     (managed-svref managed-array index))))
    (when (and expression-cell (g2-expression-cell-p expression-cell))
      (remove-wake-ups-and-clean-up-after-body
	(g2-expression-cell expression-cell)
	nil)
      (cancel-task (g2-expression-cell-wake-up-task expression-cell))
      (update-expression-cell-cached-value
	expression-cell
	(g2-expression-cell-g2-cell-array expression-cell)
	(g2-expression-cell-index expression-cell)
	nil
	nil))
    nil))




;;; The function `attempt-expression-cell-execution' is used to actually perform
;;; executions of the expression stored in an expression cell.  If no value is
;;; returned, wake ups are set.

;;; Note that this function observes the update-only-when-shown component of the
;;; computation style.  The current behavior is to clear the cache when an
;;; update is attempted and the item is not visible.  It was noted in
;;; discussions with Ben, Andy, and Mark that this is not necessarily the best
;;; behavior, in that it would be great to stop the scan task altogether when
;;; the item is not shown.  However, for the moment we will opt for a behavior
;;; compatible with pre-3.0 until we provide enough switches to make it do what
;;; we want.  Some of the toggles might be, clear value on hide, stop scanning
;;; on hide, stop forward chaining and update action updates on hide, and others
;;; I can't think of now.  -jra 8/14/91

;;; Note that we are not yet binding final-evaluation-attempt?  with anything
;;; other than NIL!  This variable controls the behavior of has a value.  In
;;; order to deal accurately with this variable, the idea of timeouts on cells
;;; will have to be added!!!  -jra 8/25/91

(defun-simple attempt-expression-cell-execution
    (expression-cell argument-list allow-inactive-objects?)
  (let* ((g2-cell-array (g2-expression-cell-g2-cell-array expression-cell))
	 (parent-frame (g2-cell-array-parent-frame g2-cell-array))
	 (byte-code-body (g2-expression-cell-byte-code-body expression-cell))
	 (cell-type (g2-expression-cell-value-type expression-cell))
	 (result-value? nil)
	 (computation-style
	   (g2-expression-cell-computation-style expression-cell))
	 (backward-chaining-allowed?
	   (computation-style-may-request-data-seeking computation-style))
	 (current-block-of-dependent-frame parent-frame)
	 (current-computation-style computation-style)
	 (network-access-attempt?
	   (computation-style-network-access-attempt computation-style))
	 ;; Below are the default computation context variables.
	 (current-computation-flags
	   (make-computation-flags
	     :role-serve-inactive-objects? allow-inactive-objects?
	     :attempting-network-read-access-p (eq network-access-attempt? 'read)
           :attempting-network-write-access-p 
           (eq network-access-attempt? 'write)
           :default-dont-compute-new-variable-values 
           (not backward-chaining-allowed?)
           :dont-compute-new-variable-values (not backward-chaining-allowed?)))
	 (current-computation-activity 0)
	 (current-computation-component-particulars
	   (slot-value-list 'cell-array-element
			    (g2-expression-cell-index expression-cell)))
	 (*current-computation-frame* parent-frame)
	 (current-computation-instance expression-cell)
	 (current-environment
	   (if (eq 'simulator
		   (computation-style-value-domain current-computation-style))
	       'simulated-value
	       'inference-engine))
	 ;; profiling is currently undergoing revision ---rdf 7/8/93
;	       (current-profile-structure? nil)
	 (evaluating-simulator-procedure? nil)
	 (explanation-variables nil)
	 ;; Stack-expiration is set below.
	 ;; *variables-that-did-not-have-values* is handled by
	 ;; with-wake-up-management below.
	 saved-warning-level
	 saved-tracing-level
	 saved-breakpoint-level)
    (cancel-task (g2-expression-cell-wake-up-task expression-cell))
    (cond
      ((not (expression-cell-able-to-compute-p expression-cell))
       (enter-tracing-and-breakpoint-context-within-computation-style
	 (enter-skipped-cell-evaluation-message))
       (update-expression-cell-cached-value
        expression-cell g2-cell-array 
        (g2-expression-cell-index expression-cell)
	 nil nil)
       (exit-tracing-and-breakpoint-context
        *current-computation-frame*
	 (exit-skipped-cell-evaluation-message)
	 nil))
      ;;    ((and (computation-style-update-only-when-shown 
      ;; current-computation-style)
      ;;         (not (showing-p parent-frame)))
      ;;    (update-expression-cell-cached-value
      ;;       expression-cell g2-cell-array 
      ;; (g2-expression-cell-index expression-cell)
      ;;       nil nil))
      (t
       (enter-tracing-and-breakpoint-context-within-computation-style
	 (enter-cell-evaluation-message))

       (open-wake-up-collection-function nil)
       ;; added 2/2/94 rdf
       (when profiling-enabled?
	 (increment-profiling-calls parent-frame)
       (posit-profiling-structure parent-frame))
       (let ((environment-vector
	       (allocate-environment-vector
		 (var-count (byte-code-body-environment-description
			   byte-code-body))))
	     (argument-count (length argument-list)))
	 (declare (type fixnum argument-count))
	 (loop for argument in argument-list
	       for argument-index fixnum from 1
	       do
	   (setf (svref environment-vector argument-index) argument))
	 (setq stack-expiration 'never)
	 (stack-eval
	   byte-code-body (byte-code-body-constant-vector byte-code-body)
	   environment-vector (get-fixnum-time) nil 0)
	 (unless (null stack-expiration)
	   (setq result-value? (svref environment-vector 0))
	   (if (null result-value?)
	       (setq stack-expiration nil)
	       (setf (svref environment-vector 0) nil)))
	 (loop for argument-index fixnum from 1 to argument-count
	       do
	   (setf (svref environment-vector argument-index) nil))
	 (reclaim-environment-vector environment-vector))

       (when (and backward-chaining-allowed? (null result-value?))
	 (set-wake-ups-function nil))
       (clean-up-wake-ups-state-if-any)

       (update-expression-cell-cached-value
	 expression-cell
	 g2-cell-array
	 (g2-expression-cell-index expression-cell)
	 result-value?
	 (type-specification-subtype-p '(obsolete-datum) cell-type))

       (exit-tracing-and-breakpoint-context
        *current-computation-frame*
	 (exit-cell-expression-evaluation-message result-value?)
	 nil)))
    (reclaim-slot-value-list current-computation-component-particulars)
    (clear-computation-context-variables)))

(defun enter-skipped-cell-evaluation-message ()
  (twith-output-to-text-string
    (twrite-string "Skipping evaluation attempt for ")
    (denote-component-of-block t)
    (twrite-string " since it currently does not have a valid compilation.")))

(defun exit-skipped-cell-evaluation-message ()
  (twith-output-to-text-string
    (twrite-string "Exiting skipped evaluation of ")
    (denote-component-of-block t)
    (twrite ".")))

(defun enter-cell-evaluation-message ()
  (twith-output-to-text-string
    (twrite-string "Evaluating the expression for ")
    (denote-component-of-block t)
    (twrite-string ".")))

(defun exit-cell-expression-evaluation-message (result-value?)
  (twith-output-to-text-string
    (if result-value?
	(tformat "~NV was the value for " result-value?)
	(twrite-string "No value was computed for "))
    (denote-component-of-block t)
    (twrite ".")))




;;; The function `cancel-expression-cell-computation' takes a g2 expression
;;; cell.  This function takes care of cancelling any tasks executing on behalf
;;; of this operation and removing any requests for variable values.

(defun-allowing-unwind cancel-expression-cell-computation (expression-cell)
  (remove-wake-ups-and-clean-up-after-body
    (g2-expression-cell expression-cell)
    nil)
  (cancel-task (g2-expression-cell-wake-up-task expression-cell))
  (cancel-task (g2-expression-cell-cyclic-task expression-cell))
  (update-expression-cell-cached-value
    expression-cell
    (g2-expression-cell-g2-cell-array expression-cell)
    (g2-expression-cell-index expression-cell)
    nil
    nil)
  nil)







;;; The function `update-expression-cell-cached-value' takes an expression-cell,
;;; g2-cell-array, the index to that expression, a new value to cache, and a
;;; flag indicating whether any old value should be cached as an obsolete value
;;; if the new value is NIL.  This function installs the new cached value into
;;; the cell, notifies the parent frame of updates, and then reclaims the old
;;; value.

(defun update-expression-cell-cached-value
       (expression-cell g2-cell-array index new-cache? cache-obsolete-value?)
  (let ((old-cache? (g2-expression-cell-cached-value expression-cell))
	(old-cache-encapsulated? nil))
    (when (and (null new-cache?)
	       cache-obsolete-value?
	       old-cache?)
      (setq old-cache-encapsulated? t)
      (setq new-cache?
	    (if (evaluation-obsolete-datum-p old-cache?)
		old-cache?
		(make-evaluation-obsolete-datum old-cache?))))
    (setf (g2-expression-cell-cached-value expression-cell) new-cache?)
    (funcall-method
      'expression-cell-updated
      (g2-cell-array-parent-frame g2-cell-array)
      g2-cell-array
      index
      old-cache?
      new-cache?)
    (when (and old-cache? (not old-cache-encapsulated?))
      (reclaim-if-evaluation-value old-cache?))
    nil))



;;; The function `analyze-g2-expression-cell-for-consistency' takes a
;;; g2-expression-cell and analyzes it for consistency.

(defun-void analyze-g2-expression-cell-for-consistency (expression-cell)
  (let ((byte-code-body? (g2-expression-cell-byte-code-body expression-cell)))
    (when byte-code-body?
      (analyze-byte-code-body-for-free-reference-consistency
	(g2-cell-array-parent-frame
	 (g2-expression-cell-g2-cell-array expression-cell))
	byte-code-body?))))






;;;; Update Only When Showing


;;; `event-update-status-of-cell-array-showing' is called upon a block when
;;; ever the (showing-p <block>) changes and that block contains a cell array.
;;; See also event-update-status-of-block-showing.

;;; Note that when ever a new subclass of block starts using cell arrays and it
;;; utilizes the update-only-when-showing toggle that class name must be added to
;;; event-update-status-of-block-showing.

(defun event-update-status-of-cell-array-showing (block now-showing?)
  (declare (ignore now-showing?))
  (let* ((g2-cell-array? (cell-array block))
	 (managed-array? (when g2-cell-array?
			   (g2-cell-array-managed-array g2-cell-array?))))
    (when managed-array?
      (loop for index from 0 below (managed-array-length managed-array?)
	    for cell? = (managed-svref managed-array? index)
	    do
	(when (and cell? (g2-expression-cell-p cell?))
	  (schedule-or-deschedule-g2-expression-cell-cyclic-task
	    cell? nil nil)))))
  nil)






;;;; Framework for recompiling a block with a cell array.



;;; Recompile-item can be configured to call recompile-cell-array for your
;;; flavor of block.  Recompile-cell-array will then use two methods on your
;;; block to recompile the cell array.  The place-reference-of-cell method is
;;; used to find each of the cells, and the
;;; recompile-expression-at-component-particulars is used to recompile that
;;; place.

;;; Unfortunately recompile-expression-at-component-particulars could have
;;; the side-effect whereby the managed-array that is being iterated over is
;;; reclaimed. To prevent this from causing an Abort the loop has been changed 
;;; to re-establish the pointer to the managed-array on every iteration.
;;; See the bug HQ-829152 for details.  - ajs (7/9/96)

(defun recompile-cell-array (block)
  ;; GENSYMCID-1824: Cat-freeform-table issue (UNACEM)
  ;;
  ;; Here we added one more functionality before looping into the cell array:
  ;; clean up all unused cells which doesn't point to any in-use cells in the
  ;; corresponding new-table. -- Chun Tian (binghe), Aug 14, 2016.

  (let ((cell-indexes-in-use nil))
    (frame-class-case block
      (new-table ; NOTE: in fact currently this is the only possible frame class
       (let* ((managed-array (g2-cell-array-managed-array (cell-array block)))
	      (managed-array-length (if managed-array
					(managed-array-length managed-array)
				      0)))
	 ;; Try to shorten the roads
	 (when (=f managed-array-length 0)
	   ;; No need to reclaim used-cell-indexes here, because it's still NIL
	   (return-from recompile-cell-array nil))

	 (let* ((cell-annotations
		 #+chestnut-trans (cell-annotations block)
		 #-chestnut-trans (cell-annotations-for-class block)))
	   (loop for row-part
		     in (get-subpart-collection cell-annotations 'subparts 'row)
		 do
	     (loop for cell-part
		       in (get-subpart-collection row-part 'subparts 'cell)
		   as contents? = (get-simple-part-feature cell-part 'cell-contents)
		   as compiled-cell? = (and (consp contents?)
					    (let ((cell? (car-of-cons contents?)))
					      (and (compiled-cell-expression-p cell?)
						   cell?)))
		   as cell-index? = (and compiled-cell?
					 (get-simple-part-feature
					   compiled-cell? 'expression-cell-index))
		   when cell-index? do
	       (gensym-push cell-index? cell-indexes-in-use)))))))

    (progn
      (loop for managed-array = (g2-cell-array-managed-array (cell-array block))
	    for managed-array-length = (if managed-array
					   (managed-array-length managed-array)
					 0)
	    for cell-index from 0
	    while (<f cell-index managed-array-length)
	    do
	(when-let (cell (managed-svref managed-array cell-index))
	  ;; GENSYMCID-1824: Cat-freeform-table issue (UNACEM)
	  ;; If the current cell index is not used in new-table, clean it up!
	  (frame-class-case block
	    (new-table
	     (unless (memq cell-index cell-indexes-in-use)
	       (when (framep cell)
		 (frame-class-case cell
		   ((g2-expression-cell)
		    (remove-compilation-from-obsolete-expression-cell cell))
		   ((g2-query-cell g2-designation-cell)
		    nil))))))

	  (let ((cell-place-reference 
		  (funcall-method 'place-reference-of-cell block cell-index)))
	    (funcall-method
	      'recompile-expression-at-component-particulars
	      block
	      (evaluation-place-reference-component-particulars 
		cell-place-reference))
	    (reclaim-evaluation-place-reference cell-place-reference)))))

    (when cell-indexes-in-use
      (reclaim-gensym-list-macro cell-indexes-in-use))
    ) ; end of out let
  ) ; end of defun




;;;; Stub Methods for Cell Array Parent Frames




;;; The method `query-cell-updated' is defined here for blocks in development
;;; G2s.  This definition will catch any uses of query cells by frames which
;;; have not yet defined the method.

;;; This method receives the g2-cell-array and index of the query cell which has
;;; been updated.  It also receives a query-cell-stream to the old and new
;;; cached values.  Note that if there was no old cached value, the
;;; old-value-stream?  argument receives a NIL instead.

#+development
(def-class-method query-cell-updated
		  (block g2-cell-array index old-value-stream? new-stream)
  (declare (ignore g2-cell-array index))
  (cerror "Continue"
	  "~a is the parent frame for a g2-cell-array, but had no ~
           query-cell-updated method to receive new value updates.  Pity."
	  block)
  (when old-value-stream?
    (reclaim-query-cell-stream old-value-stream?))
  (reclaim-query-cell-stream new-stream))




;;; The method `designation-cell-updated' is defined for blocks in development
;;; G2s.  This method should be defined for all classes which can be
;;; parent-frames of blocks.  The method receives as arguments the g2-cell-array
;;; and index of the cell that has been updated, the old value (if any) and the
;;; the new value (if any).  The values will be frames or managed values, they
;;; are reclaimed by the cell itself, and if fact these values may be reclaimed
;;; immediately after the return of this method.  Note also that if the old
;;; cached value is a frame which has been deleted, the old value argument will
;;; be NIL.  (Pass a flag instead to indicate that the value was a frame that
;;; has now been deleted?)

#+development
(def-class-method designation-cell-updated
		  (block g2-cell-array index old-value? new-value?)
  (declare (ignore g2-cell-array index))
  (cerror "Continue"
	  "~a is the parent frame for a g2-cell-array, but had no~@
           designation-cell-updated method to receive new value updates.~@
           The old value was ~a and the new value is ~a."
	  block
	  (printable-representation-of-managed-value-or-frame old-value?)
	  (printable-representation-of-managed-value-or-frame new-value?))
  nil)

#+development
(defun printable-representation-of-managed-value-or-frame (x)
  (cond ((managed-float-p x)
	 (cached-managed-float-value x))
	(t x)))




;;; The method `expression-cell-updated' is defined for blocks in development
;;; G2s.  This method should be defined for all classes which can be
;;; parent-frames of blocks.  The method receives the g2-cell-array and index of
;;; the cell that has been updates, a managed value containing the old cached
;;; value (if any), and the new value.  Note that the values passed may be
;;; reclaimed immediately after this method returns.

(def-generic-method expression-cell-updated (block cell-array index old-cache? new-cache?)
  )


;;; In development, for debugging, an expression-cell-updated method is placed on block.

#+development
(def-class-method expression-cell-updated
		  (block g2-cell-array index old-value? new-value?)
  (declare (ignore g2-cell-array index))
  (cerror "Continue"
	  "~a is the parent frame for a g2-cell-array, but had no~@
           expression-cell-updated method to receive new value updates.~@
           The old value was ~a and the new value is ~a."
	  block
	  (extract-cached-number-or-value old-value?)
	  (extract-cached-number-or-value new-value?))
  nil)




;;; The method `generate-designation-of-cell' should generate and return a text
;;; string which gives a user understandable designation which names the expression
;;; stored in the g2-cell-array at the passed index.

(def-generic-method generate-designation-of-cell (block g2-cell-array-index)
  )


;;; The method `generate-designation-of-cell' is defined here for blocks in
;;; development G2s.  This definition will catch any uses of g2-cell-arrays by
;;; classes which have not yet defined this method.

#+development
(defvar return-dummy-cell-designation? nil)

#+development
(def-class-method generate-designation-of-cell (block g2-cell-array-index)
  (unless return-dummy-cell-designation?
    (cerror "Continue, returning dummy designation."
	    "~a is a the parent frame of a g2-cell-array, but had no ~
             generate-designation-of-cell method.  Pity."
	    block))
  (tformat-text-string
    "the g2-cell-array index ~a of ~NF"
    g2-cell-array-index
    block))



;;; `Place-reference-of-cell', a method on blocks that actually have cell
;;; arrays, returns a place reference for place that contains the expression
;;; being computed by the cell-index.

(def-generic-method place-reference-of-cell (block cell-index)
  )



;;; A place-reference-of-cell method is defined in development upon blocks as a
;;; debugging aid.

#+development
(def-class-method place-reference-of-cell (block cell-index)
  (declare (ignore  cell-index))
  (error "There is no place-reference-of-cell method defined for ~S" block))




;;; `Recompile-expression-at-component-particulars' does just that.  It is a
;;; class method on subclasses of blocks that utilize cell arrays.

(def-generic-method recompile-expression-at-component-particulars
		    (block component-particulars)
  )


;;; Recompile-expression-at-component-particulars' has a method defined for
;;; blocks as an aid to debugging, in development.

#+development
(def-class-method recompile-expression-at-component-particulars
		  (block component-particulars)
  (declare (ignore component-particulars))
  (error
    "There is no recompile-expression-at-component-particulars method defined for ~S"
    block))


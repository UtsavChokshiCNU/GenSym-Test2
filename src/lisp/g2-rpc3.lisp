;; -*- Mode: LISP; Syntax: Common-Lisp; Base: 10; Package: AB -*-
(in-package "AB")

;;;; Module G2-RPC3

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All rights reserved.

;;; John Hodgkinson

;;; This module is the second part of the machinery for remote-procedure
;;; execution that is specific to G2 and involves passing items as arguments and
;;; results.  It is a continuation of G2-RPC2, broken up because of the
;;; possibilty that a file of the original size, when translated into C, can
;;; cause compiler errors.  (Also note that module G2-RPC1 contains the
;;; G2-specific machinery for passing values as arguments and results, and
;;; modules GSI-RPC1 and GSI-RPC2 contain RPC machinery for the GSI product.)

;; jh, 2/3/95.  Split this module from G2-RPC2 to isolate errors in the Vax C
;; compiler that don't appear in the debuggable (i.e., non-optimized) image.




;;;; Table of Contents

;;; [2]        Forward References

;;; [14.3.4.4]       G2 Resumable History Protocol
;;; [14.3.4.5]       G2 Resumable List Protocol

;;; [14.3.5]       G2 RPC Argument Protocols

;;; [15]       Sending Side Task to Transmit Resumable Objects After Preflight
;;; [16]       ICP Message Handler to Build Resumable Objects in G2

;;; [18]       Hooks into Existing G2 RPCs
;;; [18.1]       Hooks into G2 RPC Callers
;;; [18.2]       Transformation of G2 RPC Arglist
;;; [18.3]       Modified Pre-object-passing RPC G2 Machinery

;;; [19]       Hooks into G2 RPC Value Return
;;; [19.1]       Hooks for G2 Sending Side to Return RPC Values
;;; [19.2]       Hooks for G2 Receiving Side to Get RPC Values

;;; [20]       Hooks into G2 RPC Error Handling
;;; [21]       G2 Grammar for RPC Argument and Return Types
;;; [22]       G2 System Procedures for Network Registration



;;;; [2] Forward References

(declare-forward-reference
  get-gsi-identifying-attribute-values
  function) ;G2-GSI
(declare-forward-reference
  get-or-make-gsi-sensor
  function) ;G2-GSI
(declare-forward-reference define-or-configure-gsi-sensor function) ;G2-GSI
(declare-forward-reference
  deactivate-dataservice-for-gsi-data-service
  function) ;G2-GSI
(declare-forward-reference
  gsi-register-item
  function) ;G2-GSI
(declare-forward-reference
  local-item-home-function
  function)
(declare-forward-reference
  interface-home-attribute-function
  function)

(declare-forward-reference
  cached-name-for-local-home
  variable)

(declare-forward-reference get-list-of-all-user-visible-attributes function)
(declare-forward-reference icp-socket-of-interface-object function)



;;;; [14.3.4.4] G2 Resumable History Protocol

;; jh, 6/13/94.  The following notes on history-passing are from the "To Do"
;; list of 5/27/94 in RPC-COMMON2.  They should help when it comes time to
;; insert three-semi-worthy doc here.

;; preflight
;;   copy backlog elts into private array in sending resumable object
;;   store
;;     entire ring-buffer structure
;;     current size
;;     index of oldest & newest
;;     index & timestamp of first post-backlog elt
;;       (timestamps now floats?  managed floats?  something else?)
;; transmit
;;   if backlog, transmit that (resumably), reclaim array, & set to nil
;;   if no backlog, determine if array has been rotated
;;     do this by checking size or timestamp of next elt to send
;;       (resizing an array to bigger and then to the original size
;;       is the reason for the latter)
;;     if array has been rotated, locate new index of next elt to send
;;       do this by trying to offset index by amount of resize & check timestamp
;;       failing that, try binary search
;;       failing that, signal problem as with length change in normal array
;;       (all the above heuristics must take multiple identical timestamps
;;       into account)
;;     determine # of elts to send a la get-value-vector-transmission-info


(defun-void g2-receive-add-attribute-history-object
    (attribute-type
      attribute-qualifier?
      attribute-name-or-index
      class-name
      symbolic-attribute-count
      element-type
      resumable-history-length
      timestamps-use-float-array-p
      values-use-float-array-p
      datapoint-count?
      datapoint-age?
      granularity?
      base-time
      lowest-ever
      highest-ever
      time-at-start?)
  (declare (ignore symbolic-attribute-count element-type))
  (cond
    ((subclassp class-name 'variable-or-parameter)
     (let ((new-history-object?
	     (g2-build-remote-object
	       attribute-type
	       attribute-qualifier?
	       attribute-name-or-index
	       class-name)))
       (cond
	 ((and (framep new-history-object?)
	       (frame-of-class-p new-history-object? 'variable-or-parameter))
	  (when (or datapoint-count? datapoint-age? granularity?)
	    (add-history-spec-for-object-passing
	      new-history-object?
	      datapoint-count?
	      datapoint-age?
	      granularity?)
	    (change-slot-value-for-object-passing
	      new-history-object?
	      'variable-or-parameter-stored-histories?
	      (make-cascaded-ring-buffer-for-history-object-passing
		resumable-history-length
		timestamps-use-float-array-p
		values-use-float-array-p
		datapoint-count?
		datapoint-age?
		base-time
		lowest-ever
		highest-ever))
	    (let ((remote-time-at-start?
		    (remote-g2-time-at-start?
		      current-receiving-resumable-object)))
	      (if remote-time-at-start?
		  (when time-at-start?
		    (reclaim-evaluation-float time-at-start?))
		  (setf (remote-g2-time-at-start?
			  current-receiving-resumable-object)
			time-at-start?)))))
	 (t (record-object-building-problem-on-receiving-side
	      'history-object-sent-to-non-history-attribute
	      nil
	      nil
	      class-name)))))
    (t (record-object-building-problem-on-receiving-side
	 'history-object-sent-to-non-history-class-definition
	 nil
	 nil
	 class-name))))


(defun-void add-history-spec-for-object-passing
    (new-history-object datapoint-count datapoint-age granularity)
  (change-slot-value-for-object-passing
    new-history-object
    'variable-or-parameter-history-specification?
    (slot-value-list 'history datapoint-count datapoint-age granularity)))

;;; The macro `iterate-over-history-for-caching' is internal to the G2-RPC3
;;; module.  It is an abstraction designed solely for use by the function
;;; copy-numeric-history-state-into-resumable-history-node, and expects to be
;;; executed in a lexical scope that has bound the following variables:
;;; cached-timestamp-subsequence, cache-index, previous-timestamp?, and
;;; identical-timestamp-count.  The variables history-value and
;;; history-collection-time that also appear in the expansion of this macro are
;;; bound by the iterate-over-history form it uses.  This macro also expects to
;;; be executed in a temporary float creation scope when appropriate.

(defmacro iterate-over-history-for-caching (float-timestamps-p float-values-p)
  (let ((timestamp-setter-form
	  (if float-timestamps-p
	      `(setf (managed-float-aref cached-timestamp-subsequence
					 cache-index)
		     history-collection-time)
	      `(setf (svref cached-timestamp-subsequence cache-index)
		     (if (gensym-float-p history-collection-time)
			 (make-evaluation-float history-collection-time)
			 (copy-evaluation-value history-collection-time)))))
	(timestamp-comparison-form
	  (if float-timestamps-p
	      `(=e previous-timestamp? history-collection-time)
	      `(cond
		 ((and (gensym-float-p history-collection-time)
		       (gensym-float-p previous-timestamp?))
		  (=e previous-timestamp? history-collection-time))
		 ((or (gensym-float-p history-collection-time)
		      (gensym-float-p previous-timestamp?))
		  nil)
		 (t (evaluation-value-eql previous-timestamp?
					  history-collection-time)))))
	(value-setter-form
	  (if float-values-p
	      `(setf (managed-float-aref cached-value-subsequence cache-index)
		     history-value)
	      `(setf (svref cached-value-subsequence cache-index)
		     (if (gensym-float-p history-value)
			 (make-evaluation-float history-value)
			 (copy-evaluation-value history-value))))))
    `(iterate-over-history
       ,timestamp-setter-form
       ,value-setter-form
       (if (and previous-timestamp? ,timestamp-comparison-form)
	   (incff identical-timestamp-count)
	   (setq identical-timestamp-count 0))
       (setq previous-timestamp? history-collection-time)
       (when (>=f (incff cache-index)
		  size-of-cached-subsequence-for-resumable-history)
	 (return-from iterate-over-history)))))

;; jh, 8/24/94.  Temporary fix to timestamp-setter-form,
;; timestamp-comparison-form, and value-setter-form in
;; iterate-over-history-for-caching.  With a quantity history (i.e., a mixture
;; of integer and float values), iterate-over-history places Lisp floats, not
;; Gensym managed floats, in its lexicals history-value and
;; history-collection-time.  The true fix (coming soon) will bypass
;; iterate-over-history entirely and use the managed values throughout.  Such a
;; fix would also let us refrain from entering a temporary-float creation
;; context unless necessary, something not available with iterate-over-history.
;; But for now, since I am getting some use-testing of the object-passing
;; facility and I want my testers to proceed, this fix will do.



(defun get-following-history-timestamp
    (history timestamp-vector base-ring-index delta)
  (let* ((first-uncached-index
	   (advance-active-element-index base-ring-index history delta))
	 (first-uncached-timestamp
	   (get-ring-buffer-value
	     timestamp-vector
	     first-uncached-index
	     possible-float-array))
	 (managed-timestamp
	   (cond
	     ((gensym-float-p first-uncached-timestamp)
	      (allocate-managed-float first-uncached-timestamp))
	     ((managed-float-p first-uncached-timestamp)
	      (copy-managed-float first-uncached-timestamp))
	     ((fixnump first-uncached-timestamp)
	      ;; ... review for temporary float leak in translated code!
	      (make-evaluation-float
		(coerce-fixnum-to-gensym-float first-uncached-timestamp)))
	     #+development
	     (t (cerror
		  "Use NIL and probably crash soon ~
                   (This behavior is what the user would get)"
		  "COPY-HISTORY-STATE-INTO-RESUMABLE-HISTORY-NODE: ~
		   Unexpected timestamp type for ~a"
		  first-uncached-timestamp)))))
    (values first-uncached-index managed-timestamp)))

(defun-void copy-numeric-history-state-into-resumable-history-node
    (history-node
      history
      history-length
      float-vector-for-timestamps-p
      timestamp-vector
      float-vector-for-values-p)
  (setf (index-of-next-cached-history-value? history-node) 0)
  (setf (internal-history-for-object-passing? history-node) history)
  (let ((oldest-element-index (oldest-active-element-index history))
	(cached-timestamp-subsequence
	  (if float-vector-for-timestamps-p
	      (allocate-managed-float-array	    
		size-of-cached-subsequence-for-resumable-history)
	      (allocate-managed-simple-vector
		size-of-cached-subsequence-for-resumable-history)))
	(cached-value-subsequence
	  (if float-vector-for-values-p
	      (allocate-managed-float-array	    
		size-of-cached-subsequence-for-resumable-history)
	      (allocate-managed-simple-vector
		size-of-cached-subsequence-for-resumable-history)))
	(cache-index 0)
	(previous-timestamp? nil)
	(identical-timestamp-count 0)
	(value-history-ring-buffer-or-cascade history))
    (setf (ring-index-of-oldest-history-value history-node)
	  oldest-element-index)
    (setf (cached-timestamp-subsequence-for-resumable-history? history-node)
	  cached-timestamp-subsequence)
    (setf (cached-value-subsequence-for-resumable-history? history-node)
	  cached-value-subsequence)
    (cond
      ((and float-vector-for-timestamps-p float-vector-for-values-p)
       (iterate-over-history-for-caching t t))
      (float-vector-for-timestamps-p
       (iterate-over-history-for-caching t nil))
      (float-vector-for-values-p
       (iterate-over-history-for-caching nil t))
      (t (iterate-over-history-for-caching nil nil)))
    (setf (count-of-preceding-identically-timestamped-values history-node)
	  identical-timestamp-count)
    (when (>f history-length size-of-cached-subsequence-for-resumable-history)
      (multiple-value-bind (first-uncached-index managed-timestamp)
	  (get-following-history-timestamp
	    history
	    timestamp-vector
	    oldest-element-index
	    size-of-cached-subsequence-for-resumable-history)
	(setf (ring-index-of-next-uncached-history-value? history-node)
	      first-uncached-index)
	(setf (timestamp-of-next-uncached-history-value? history-node)
	      managed-timestamp)))))

(defun-void copy-history-state-into-resumable-history-node
    (history-node history-enclosure? history history-spec)
  (setf (internal-history-spec-for-object-passing history-node)
	(copy-list-using-icp-conses history-spec))
  (macrolet ((copy-enclosure-slot-if-any (accessor)
	       `(let ((contents? (,accessor history-enclosure?)))
		  (if contents? (copy-evaluation-value contents?) nil))))
    (if history-enclosure?
	(setf (dynamic-history-info-for-object-passing history-node)      
	      (icp-list
		(copy-enclosure-slot-if-any cascaded-ring-buffer-base-time?)
		;; jh, 6/9/94.  Actually not sure we want the next two, since
		;; the user could change them out from under us, throwing off
		;; subsequent evaluation of max and min history expressions on
		;; the receiving side.
		(copy-enclosure-slot-if-any lowest-value-ever-in-history?)
		(copy-enclosure-slot-if-any highest-value-ever-in-history?)
		(copy-evaluation-float (clock-get g2-time-at-start))))
	(setf (dynamic-history-info-for-object-passing history-node)
	      (icp-list nil nil nil nil))))
  (let ((history-length (ring-buffer-length history)))
    (setf (resumable-sequence-length history-node) history-length)
    (when (>f history-length 0)
      (let* ((timestamp-vector (history-time-vector history))
	     (float-vector-for-timestamps-p
	       (managed-float-array-p timestamp-vector))
	     (float-vector-for-values-p
	       (managed-float-array-p (history-value-vector history))))
	(if (or float-vector-for-timestamps-p float-vector-for-values-p)
	    (with-temporary-gensym-float-creation
		copy-history-state-into-resumable-history-node
	      (copy-numeric-history-state-into-resumable-history-node
		history-node
		history
		history-length
		float-vector-for-timestamps-p
		timestamp-vector
		float-vector-for-values-p))
	    (copy-numeric-history-state-into-resumable-history-node
	      history-node
	      history
	      history-length
	      float-vector-for-timestamps-p
	      timestamp-vector
	      float-vector-for-values-p))))))

;;; Get-history-object-transmission-info must be called within the dynamic
;;; extent of a with-temporary-gensyn-float-creation.  It returns five values:
;;;   number-of-cached-elements-to-transmit?
;;;   cached-interning-details
;;;   number-of-uncached-elements-to-transmit
;;;   ring-index-of-first-uncached-element
;;;   uncached-interning-details
;;;   bandwidth-needed

(defun-simple same-timestamp-as (timestamp managed-float-timestamp)
  (cond
    ((managed-float-p timestamp)
     (=e (managed-float-value managed-float-timestamp)
	 (managed-float-value timestamp)))
    ((gensym-float-p timestamp)
     (=e (managed-float-value managed-float-timestamp)
	 timestamp))
    ((fixnump timestamp)
     (=e (managed-float-value managed-float-timestamp)
	 (coerce-to-gensym-float timestamp)))
    (t nil)))

(defun-simple later-timestamp-than (timestamp managed-float-timestamp)
  (cond
    ((managed-float-p timestamp)
     (>e (managed-float-value managed-float-timestamp)
	 (managed-float-value timestamp)))
    ((gensym-float-p timestamp)
     (>e (managed-float-value managed-float-timestamp)
	 timestamp))
    ((fixnump timestamp)
     (>e (managed-float-value managed-float-timestamp)
	 (coerce-to-gensym-float timestamp)))
    (t nil)))

(defun-simple get-index-of-timestamp-if-any (timestamp history)
  (loop with lowest-possible-index = (oldest-active-element-index history)
	with highest-possible-index = (newest-active-element-index history)
	while (ring-buffer-index<
		history
		lowest-possible-index
		highest-possible-index)
	for probe-offset
	= (halff
	    (ring-buffer-index-difference
	      history
	      highest-possible-index
	      lowest-possible-index))
	do
    (let* ((index-to-try
	     (advance-active-element-index
	       lowest-possible-index
	       history
	       probe-offset))
	   (this-timestamp (get-history-time history index-to-try)))
      (cond
	((same-timestamp-as this-timestamp timestamp)
	 (return index-to-try))
	((later-timestamp-than this-timestamp timestamp)
	 (setq highest-possible-index index-to-try))
	(t (setq lowest-possible-index index-to-try))))
	finally (return nil)))
  
;; To make situate-previous-index-in-identical-timestamps easier to read, there
;; are no implicit returns.  Every exit uses a return-from form.

(defun-simple situate-previous-index-in-identical-timestamps
    (history history-node new-entry-index timestamp)
  (let ((previous-count
	  (count-of-preceding-identically-timestamped-values history-node))
	(oldest-index (oldest-active-element-index history)))
    ;; Give up if there are more previous identically timestamped elements than
    ;; there are previous elements.  We have no way of knowing whether or not
    ;; the element we want dropped off the end.
    (when (<f (ring-buffer-index-difference
		history
		new-entry-index
		oldest-index)
	      previous-count)
       (return-from situate-previous-index-in-identical-timestamps
	 nil))
    (let* ((possible-index-of-first-identical-timestamp
	     (advance-active-element-index
	       new-entry-index
	       history
	       (-f previous-count)))
	   (possible-first-identical-timestamp
	     (get-history-time
	       history
	       possible-index-of-first-identical-timestamp)))
      ;; If there are indeed the expected number of previous identically
      ;; timestamped elements, return the ring index unchanged.
      (when (and (same-timestamp-as
		   possible-first-identical-timestamp
		   timestamp)
		 (or (=f possible-index-of-first-identical-timestamp
			 oldest-index)
		     (not (same-timestamp-as
			    (get-history-time
			      history
			      (decrement-active-element-index
				possible-index-of-first-identical-timestamp
				history))
			    timestamp))))
	(return-from situate-previous-index-in-identical-timestamps
	  new-entry-index)))
    ;; Otherwise, maybe the history was resized twice, skewing the index we
    ;; want.  Look for the first occurring identically timestamped element and
    ;; then go forward
    (let ((earliest-index-with-identical-timestamp?
	    (loop for ring-index
		  = (decrement-active-element-index new-entry-index history)
		      then (decrement-active-element-index ring-index history)
		  while
		  (same-timestamp-as
		    (get-history-time history ring-index)
		    timestamp)
		  finally
		    (return
		      ;; If the earliest element has an identical timestamp, we
		      ;; don't know where we are (since even earlier identical
		      ;; timestamps may have dropped off the end), so give up.
		      (if (=f ring-index oldest-index)
			  nil
			  (increment-active-element-index
			    ring-index
			    history))))))
	(unless earliest-index-with-identical-timestamp?
	  (return-from situate-previous-index-in-identical-timestamps
	    nil))
	(let ((possible-new-entry-index
		(advance-active-element-index
		  earliest-index-with-identical-timestamp?
		  history
		  previous-count)))
	  (when (same-timestamp-as
		  (get-history-time history possible-new-entry-index)
		  timestamp)
	    (return-from situate-previous-index-in-identical-timestamps
	      possible-new-entry-index))
	  (return-from situate-previous-index-in-identical-timestamps
	    nil)))))

(defun-simple locate-new-history-index-if-any (history history-node timestamp)
  (cond
    ;; Give up if the new history is not big enough to contain all the entries
    ;; we have yet to transmit.
    ((<f (ring-buffer-size history)
	 (-f (resumable-sequence-length history-node)
	     (count-of-history-elements-transmitted history-node)))
     nil)
    (t (let* ((old-entry-index
		(ring-index-of-next-uncached-history-value? history-node))
	      (old-index-of-oldest-entry
		(ring-index-of-oldest-history-value history-node))
	      (new-entry-index?
		(or ;; See if the correct timestamp is at old index.
		    (let ((timestamp-at-old-index
			    (get-history-time history old-entry-index)))
		      (and (same-timestamp-as timestamp-at-old-index timestamp)
			   old-entry-index))
		    ;; See if history was rotated by old-index-of-oldest-entry
		    ;; (i.e., it was resized once).
		    (let ((old-index-corrected-for-rotation
			    (advance-active-element-index
			      old-entry-index
			      history
			      (-f old-index-of-oldest-entry))))
		      (and (same-timestamp-as
			     (get-history-time
			       history
			       old-index-corrected-for-rotation)
			     timestamp)
			   old-index-corrected-for-rotation))
		    ;; If all else fails, try binary search for the timestamp.
		    (get-index-of-timestamp-if-any timestamp history))))
	 (cond
	   ;; If we have a potential index at this point, check that the number
	   ;; of preceding elements with identical timestamps matches what we
	   ;; want.
	   (new-entry-index?
	    (situate-previous-index-in-identical-timestamps
	      history
	      history-node
	      new-entry-index?
	      timestamp))
	   (t nil))))))

;; .. The following function should be abstracted with similar code in
;; get-value-vector- and -list-transmission-info.

(defun get-bandwidth-for-untagged-history-value
    (element-type value icp-port)
  (case element-type
    (integer
     (bandwidth-for-icp-fixnum (evaluation-integer-value value)))
    (|float| (bandwidth-for-icp-float))
    (text
     (bandwidth-for-icp-text-string (evaluation-text-value value)))
    (symbol
     (bandwidth-for-icp-symbol (evaluation-symbol-symbol value) icp-port))
    (truth
     (bandwidth-for-icp-truth-value value))
    #+development
    (otherwise
     (cerror
       "Continue, assuming the value consumes 2 bytes ~
        (This behavior is what the user would get)"
       "GET-BANDWIDTH-FOR-UNTAGGED-HISTORY-VALUE: ~
        unknown element type ~s for value ~s"
       element-type
       value)
     2)))

;;; The macro `iterate-over-cached-history-for-transmission-info' is internal to
;;; the G2-RPC3 module.  It is an abstraction designed solely for use by the
;;; function get-cached-history-array-transmission-info, and expects to be
;;; executed in a lexical scope that has bound the following variables:
;;; cached-index, timestamp-vector, value-vector, icp-port, bandwidth-needed,
;;; bandwidth-available, next-cached-index, and max-cached-count.  This macro
;;; also expects to be executed in a temporary float creation scope when
;;; appropriate.

(defmacro iterate-over-cached-history-for-transmission-info
    (float-timestamps-p float-values-p element-type-var?)
  (let ((timestamp-access-form
	  (if float-timestamps-p
	      `(managed-float-aref timestamp-vector cached-index)
	      `(svref timestamp-vector cached-index)))
	(timestamp-info-setter
	  (if float-timestamps-p
	      `(setq timestamp-bandwidth (bandwidth-for-icp-float))
	      `(setq timestamp-bandwidth
		     (bandwidth-for-evaluation-value
		       cached-timestamp
		       icp-port))))
	(value-access-form
	  (if float-values-p
	      `(managed-float-aref value-vector cached-index)
	      `(svref value-vector cached-index)))
	(value-info-setter
	  (cond
	    (element-type-var?
	     `(multiple-value-setq (value-bandwidth corresponding-index?)
		(get-bandwidth-for-untagged-history-value
		  ,element-type-var?
		  cached-value
		  icp-port)))
	    (float-values-p
	     `(setq value-bandwidth (bandwidth-for-icp-float)))
	    (t `(multiple-value-setq (value-bandwidth corresponding-index?)
		  (bandwidth-for-evaluation-value cached-value icp-port))))))
    `(loop with number-of-cached-elements-to-transmit = 0
	   with cached-interning-details = nil
	   for cached-index from next-cached-index below max-cached-count
	   for cached-timestamp = ,timestamp-access-form
	   for cached-value = ,value-access-form
	   do
       (let (timestamp-bandwidth
	      value-bandwidth
	      (corresponding-index? nil))
	 ,timestamp-info-setter
	 ,value-info-setter
	 (let* ((bandwidth-to-transmit
		  (+f timestamp-bandwidth value-bandwidth))
		(new-bandwidth-available
		  (-f bandwidth-available bandwidth-to-transmit)))
	   (cond
	     ((>f new-bandwidth-available 0)
	      (incff bandwidth-needed bandwidth-to-transmit)
	      (setq bandwidth-available new-bandwidth-available)
	      (incff number-of-cached-elements-to-transmit)
	      (when corresponding-index?
		(icp-push (icp-cons cached-index corresponding-index?)
			  cached-interning-details)))
	     (t (return
		  (values number-of-cached-elements-to-transmit
			  next-cached-index
			  (nreverse cached-interning-details)
			  ,(and float-timestamps-p t)
			  ,(and float-values-p t)
			  bandwidth-needed
			  bandwidth-available))))))
	   finally
	     (return
	       (values number-of-cached-elements-to-transmit
		       nil
		       (nreverse cached-interning-details)
		       ,(and float-timestamps-p t)
		       ,(and float-values-p t)
		       bandwidth-needed
		       bandwidth-available)))))

(defun get-cached-history-array-transmission-info
    (resumable-history-node
      element-type?
      icp-port
      next-cached-index
      max-cached-count
      bandwidth-needed
      bandwidth-available)
  (let* ((timestamp-vector
	   (cached-timestamp-subsequence-for-resumable-history?
	     resumable-history-node))
	 (value-vector
	   (cached-value-subsequence-for-resumable-history?
	     resumable-history-node))
	 (float-timestamps-p
	   (managed-float-array-p timestamp-vector))
	 (float-values-p
	   (managed-float-array-p value-vector)))
    (if (or float-timestamps-p float-values-p)
	(with-temporary-gensym-float-creation
	    get-cached-history-array-transmission-info
	  (cond
	    ((and float-timestamps-p float-values-p)
	     (let* ((element-bandwidth (*f (bandwidth-for-icp-float) 2))
		    (number-to-transmit
		      (minf (floorf bandwidth-available element-bandwidth)
			    (-f max-cached-count next-cached-index)))
		    (bandwidth-to-transmit
		      (*f number-to-transmit element-bandwidth))
		    (new-cached-count
		      (+f number-to-transmit next-cached-index)))
	       (values number-to-transmit
		       (if (>=f new-cached-count max-cached-count)
			   nil
			   new-cached-count)
		       nil ;cached-interning-deatils
		       float-timestamps-p
		       float-values-p
		       (+f bandwidth-needed bandwidth-to-transmit)
		       (-f bandwidth-available bandwidth-to-transmit))))
	    (float-timestamps-p
	     (if element-type?
		 (iterate-over-cached-history-for-transmission-info
		   t
		   nil
		   element-type?)
		 (iterate-over-cached-history-for-transmission-info
		   t
		   nil
		   nil)))
	    (float-values-p
	     (if element-type?
		 (iterate-over-cached-history-for-transmission-info
		   nil
		   t
		   element-type?)
		 (iterate-over-cached-history-for-transmission-info
		   nil
		   t
		   nil)))))
	(if element-type?
	    (iterate-over-cached-history-for-transmission-info
	      nil
	      nil
	      element-type?)
	    (iterate-over-cached-history-for-transmission-info
	      nil
	      nil
	      nil)))))

;;; The macro `iterate-over-uncached-history-for-transmission-info' is internal
;;; to the G2-RPC3 module.  It is an abstraction designed solely for use by the
;;; function get-uncached-history-array-transmission-info, and expects to be
;;; executed in a lexical scope that has bound the following variables:
;;; new-ring-index?, history?, timestamp-vector, value-vector, icp-port,
;;; bandwidth-needed, and bandwidth-available. This macro also expects to be
;;; executed in a temporary float creation scope when appropriate.

(defmacro iterate-over-uncached-history-for-transmission-info
    (float-timestamps-p float-values-p element-type-var?)
  (let ((timestamp-access-form
	  (if float-timestamps-p
	      `(managed-float-aref timestamp-vector ring-index)
	      `(managed-svref timestamp-vector ring-index)))
	(timestamp-info-setter
	  (if float-timestamps-p
	      `(setq timestamp-bandwidth (bandwidth-for-icp-float))
	      `(setq timestamp-bandwidth
		     (bandwidth-for-evaluation-value timestamp icp-port))))
	(value-access-form
	  (if float-values-p
	      `(managed-float-aref value-vector ring-index)
	      `(managed-svref value-vector ring-index)))
	(value-info-setter
	  (cond
	    (element-type-var?
	     `(multiple-value-setq (value-bandwidth corresponding-index?)
		(get-bandwidth-for-untagged-history-value
		  ,element-type-var?
		  value
		  icp-port)))
	    (float-values-p
	     `(setq value-bandwidth (bandwidth-for-icp-float)))
	    (t `(multiple-value-setq (value-bandwidth corresponding-index?)
		 (bandwidth-for-evaluation-value value icp-port))))))
    `(loop with number-of-uncached-elements-to-transmit = 0
	   with uncached-interning-details = nil
	   for ring-index = new-ring-index?
	   then (increment-active-element-index ring-index history?)
	   for timestamp = ,timestamp-access-form
	   for value = ,value-access-form
	   do
       (let (timestamp-bandwidth
	      value-bandwidth
	      (corresponding-index? nil))
	 ,timestamp-info-setter
	 ,value-info-setter
	 (let* ((bandwidth-to-transmit
		  (+f timestamp-bandwidth value-bandwidth))
		(new-bandwidth-available
		  (-f bandwidth-available bandwidth-to-transmit)))
	   (cond
	     ((>f new-bandwidth-available 0)
	      (incff bandwidth-needed bandwidth-to-transmit)
	      (setq bandwidth-available new-bandwidth-available)
	      (incff number-of-uncached-elements-to-transmit)
	      (when corresponding-index?
		(icp-push (icp-cons ring-index corresponding-index?)
			  uncached-interning-details)))
	     (t (return
		  (values number-of-uncached-elements-to-transmit
			  new-ring-index?
			  (nreverse uncached-interning-details)
			  ,(and float-timestamps-p t)
			  ,(and float-values-p t)
			  bandwidth-needed))))))
       until (indices-same-for-ring-buffer-or-cascade-p
	       ring-index
	       newest-ring-index)
	   finally
	     (return
	       (values number-of-uncached-elements-to-transmit
		       new-ring-index?
		       (nreverse uncached-interning-details)
		       ,(and float-timestamps-p t)
		       ,(and float-values-p t)
		       bandwidth-needed)))))

(defun get-uncached-history-array-transmission-info
    (resumable-history-node
      element-type?
      resumable-object
      icp-port
      remaining-uncached-count
      bandwidth-needed
      bandwidth-available)
  (with-throw-handling get-uncached-history-array-transmission-info
    (let ((current-object
	    (resumable-instance-current-object resumable-history-node))
	  (toplevel-object
	    (object-or-handle-to-be-passed resumable-object))
	  (history?
	    (internal-history-for-object-passing? resumable-history-node)))
      (unless history?
	(throw*
	  :abort-transmitting-resumable-object
	  (icp-list
	    'g2-history-array-deleted
	    (twith-output-to-text-string
	      (tformat "A history-keeping variable-or-parameter ")
	      (if (eq current-object toplevel-object)
		  (tformat "at top level in the argument list ")
		  (tformat ", being sent as a subobject of ~NF, "
			   toplevel-object))
	      (tformat "has had its history-keeping spec ~
                      changed to \"none\"")))))
      (let ((new-ring-index?
	      (locate-new-history-index-if-any
		history?
		resumable-history-node
		(timestamp-of-next-uncached-history-value?
		  resumable-history-node))))
	(unless new-ring-index?
	  (throw*
	    :abort-transmitting-resumable-object
	    (icp-list
	      'g2-history-array-index-lost
	      (twith-output-to-text-string
		(tformat "A history-keeping variable-or-parameter ")
		(if (eq current-object toplevel-object)
		    (tformat "at top level in the argument list ")
		    (tformat ", being sent as a subobject of ~NF, "
			     toplevel-object))
		(tformat "has overwritten an old value ~
                        before it could be transmitted")))))
	(let ((newest-ring-index (newest-active-element-index history?)))
	  ;; ... I don't believe this can happen until G2 can conclude into past
	  ;; histories.
	  (unless (>=f (ring-buffer-index-difference
			 history?
			 newest-ring-index
			 new-ring-index?)
		       remaining-uncached-count)
	    (throw*
	      :abort-transmitting-resumable-object
	      (icp-list
		'g2-history-array-entries-lost
		(twith-output-to-text-string
		  (tformat "A history-keeping variable-or-parameter ")
		  (if (eq current-object toplevel-object)
		      (tformat "at top level in the argument list ")
		      (tformat ", being sent as a subobject of ~NF, "
			       toplevel-object))
		  (tformat "has overwritten some old values ~
                        before they could be transmitted")))))	  
	  (let* ((timestamp-vector (history-time-vector history?))
		 (value-vector (history-value-vector history?))
		 (float-timestamps-p
		   (managed-float-array-p timestamp-vector))
		 (float-values-p
		   (managed-float-array-p value-vector)))
	    (if (or float-timestamps-p float-values-p)
		(with-temporary-gensym-float-creation
		    get-uncached-history-array-transmission-info
		  (cond
		    ((and float-timestamps-p float-values-p)
		     (let* ((element-bandwidth (*f (bandwidth-for-icp-float) 2))
			    (number-to-transmit
			      (minf
				(floorf bandwidth-available element-bandwidth)
				remaining-uncached-count))
			    (new-bandwidth-needed
			      (+f bandwidth-needed
				  (*f number-to-transmit element-bandwidth))))
		       (values number-to-transmit
			       new-ring-index?
			       nil ;uncached-interning-details
			       t   ;timestamps-use-float-array-p
			       t   ;values-use-float-array-p
			       new-bandwidth-needed)))
		    (float-timestamps-p
		     (if element-type?
			 (iterate-over-uncached-history-for-transmission-info
			   t
			   nil
			   element-type?)
			 (iterate-over-uncached-history-for-transmission-info
			   t
			   nil
			   nil)))
		    (float-values-p
		     (if element-type?
			 (iterate-over-uncached-history-for-transmission-info
			   nil
			   t
			   element-type?)
			 (iterate-over-uncached-history-for-transmission-info
			   nil
			   t
			   nil)))))
		(if element-type?
		    (iterate-over-uncached-history-for-transmission-info
		      nil
		      nil
		      element-type?)
		    (iterate-over-uncached-history-for-transmission-info
		      nil
		      nil
		      nil)))))))))

(defun get-history-array-transmission-info
    (resumable-history-node resumable-object element-type? icp-port)
  (with-throw-handling get-history-array-transmission-info
    (let* ((history-length (resumable-sequence-length resumable-history-node))
	   (number-of-cached-elements-to-transmit 0)
	   cached-interning-details
	   (next-cached-index?
	     (index-of-next-cached-history-value? resumable-history-node))
	   (number-of-uncached-elements-to-transmit 0)
	   timestamps-use-float-array-p
	   values-use-float-array-p
	   uncached-interning-details
	   (bandwidth-needed
	     (+f (if element-type?
		     (bandwidth-for-resumable-node-type-tag)
		     0)
		 (bandwidth-for-resumable-sequence-length)
		 (bandwidth-for-history-float-array-flags)))
	   global-bandwidth
	   network-is-limiting-factor-p
	   bandwidth-available
	   next-uncached-ring-index)
      (multiple-value-setq (global-bandwidth network-is-limiting-factor-p)
	(get-available-object-passing-bandwidth resumable-object))
      (setq bandwidth-available (-f global-bandwidth bandwidth-needed))
      (when next-cached-index?
	(let ((max-cached-count
		(minf size-of-cached-subsequence-for-resumable-history
		      history-length)))
	  (multiple-value-setq (number-of-cached-elements-to-transmit
				 next-cached-index?
				 cached-interning-details
				 timestamps-use-float-array-p
				 values-use-float-array-p
				 bandwidth-needed
				 bandwidth-available)
	    (get-cached-history-array-transmission-info
	      resumable-history-node
	      element-type?
	      icp-port
	      next-cached-index?
	      max-cached-count
	      bandwidth-needed
	      bandwidth-available))))
      (unless next-cached-index?
	(when (timestamp-of-next-uncached-history-value? resumable-history-node)
	  (let ((remaining-uncached-count
		  (-f history-length
		      (maxf size-of-cached-subsequence-for-resumable-history
			    (count-of-history-elements-transmitted
			      resumable-history-node)))))
	    (handle-throw
	      (multiple-value-setq (number-of-uncached-elements-to-transmit
				     next-uncached-ring-index
				     uncached-interning-details
				     timestamps-use-float-array-p
				     values-use-float-array-p
				     bandwidth-needed
				     bandwidth-available)
		(get-uncached-history-array-transmission-info
		  resumable-history-node
		  element-type?
		  resumable-object
		  icp-port
		  remaining-uncached-count
		  bandwidth-needed
		  bandwidth-available))))))
      (values number-of-cached-elements-to-transmit
	      cached-interning-details
	      next-uncached-ring-index
	      number-of-uncached-elements-to-transmit
	      uncached-interning-details
	      timestamps-use-float-array-p
	      values-use-float-array-p
	      bandwidth-needed
	      network-is-limiting-factor-p))))

(defun-simple make-cascaded-ring-buffer-for-history-object-passing
    (resumable-history-length
      timestamps-use-float-array-p
      values-use-float-array-p
      datapoint-count?
      datapoint-age
      base-time
      lowest-ever
      highest-ever)
  (let ((new-buffer (make-history-ring-buffer))
	(ring-buffer-size
	  (if datapoint-count?
	      (maxf resumable-history-length datapoint-count?)
	      resumable-history-length)))
    (setf (history-time-vector new-buffer)
	  (if timestamps-use-float-array-p
	      (get-or-make-ring-buffer-vector
		possible-float-array
		ring-buffer-size)
	      (get-or-make-ring-buffer-vector
		nil
		ring-buffer-size)))
    (setf (history-value-vector new-buffer)
	  (if values-use-float-array-p
	      (get-or-make-ring-buffer-vector
		possible-float-array
		ring-buffer-size)
	      (get-or-make-ring-buffer-vector
		nil
		ring-buffer-size)))
    (setf (ring-buffer-empty? new-buffer) nil)
    (setf (ring-buffer-size new-buffer) ring-buffer-size)
    (setf (newest-active-element-index new-buffer) -1)
    (let ((new-history (make-cascaded-ring-buffer)))
      (setf (runtime-specifications-for-individual-ring-buffers-in-cascade
	      new-history)
	    (history-list
	      (history-list
		datapoint-count? datapoint-age nil)))
      (setf (cascaded-ring-buffers new-history) (history-list new-buffer))
      (setf (cascaded-ring-buffer-base-time? new-history) base-time)
      ;; jh, 6/9/94.  The following setf form contradicts the next two setfs
      ;; after it.  See note this date under
      ;; copy-history-state-into-resumable-history-node for explanation.
      (setf (maintain-high-water-marks-p new-history) nil)
      (setf (lowest-value-ever-in-history? new-history) lowest-ever)
      (setf (highest-value-ever-in-history? new-history) highest-ever)
      new-history)))

;;; The macro `iterate-over-cached-history-range-for-transmission' is internal
;;; to the G2-RPC3 module.  It is an abstraction designed solely for use by the
;;; function g2-transmit-add-history-range, which is the :writer branch in the
;;; ICP value protocol add-history-range for G2.  This macro expects to be
;;; executed in a lexical scope that has bound the following variables:
;;; cache-index, cached-timestamp-vector, cached-value-vector,
;;; number-of-cached-elements, cached-interning-details?, and resumable-node.
;;; This macro also expects to be executed in a temporary float creation scope
;;; when appropriate.  Note that this macro updates resumable-node (a
;;; resumable-history-node structure) appropriately when finished transmitting.

(defmacro iterate-over-cached-history-range-for-transmission
    (float-timestamps-p float-values-p)
  (let ((timestamp-access-form
	  (if float-timestamps-p
	      `(managed-float-aref cached-timestamp-vector cache-index)
	      `(svref cached-timestamp-vector cache-index)))
	(timestamp-writing-form
	  (if float-timestamps-p
	      `(write-icp-double-float-1 timestamp)
	      `(write-icp-history-timestamp timestamp)))
	(value-access-form
	  (if float-values-p
	      `(managed-float-aref cached-value-vector cache-index)
	      `(svref cached-value-vector cache-index)))
	(value-writing-form
	  (if float-values-p
	      `(write-icp-double-float-1 value)
	      `(write-icp-attribute-value value corresponding-index?))))
    `(loop-with-or-without ,(if float-values-p nil `cached-interning-details?)
       repeat number-of-cached-elements
       for cache-index from first-cache-index
       for timestamp = ,timestamp-access-form
       for value = ,value-access-form
       ,@(if float-values-p nil `(with corresponding-index? = nil))
       [ with next-interning-index? = (caar cached-interning-details?) ]
       [ if (and next-interning-index? (=f next-interning-index? cache-index))
	    do
	    (progn (setq corresponding-index?
			 (cdar cached-interning-details?))
		   (reclaim-icp-cons (icp-pop cached-interning-details?))
		   (setq next-interning-index?
			 (caar cached-interning-details?)))
	    else
	    (setq corresponding-index? nil) ]
       do
       ,timestamp-writing-form
       ,value-writing-form
       finally
       (incff (count-of-history-elements-transmitted resumable-node)
	      number-of-cached-elements)
       (incff (index-of-next-cached-history-value? resumable-node)
	      number-of-cached-elements)
       (when (=f (index-of-next-cached-history-value? resumable-node)
		 size-of-cached-subsequence-for-resumable-history)
	 (setf (index-of-next-cached-history-value? resumable-node) nil))
       (reclaim-unprocessed-interning-details-if-any
	 cached-interning-details?))))

;;; The macro `iterate-over-uncached-history-range-for-transmission' is internal
;;; to the G2-RPC3 module.  It is an abstraction designed solely for use by the
;;; function g2-transmit-add-history-range, which is the:writer branch in the
;;; ICP value protocol add-history-range for G2.  This macro expects to be
;;; executed in a lexical scope that has bound the following variables: history,
;;; timestamp-vector, value-vector, ring-index-of-first-uncached-element,
;;; number-of-uncached-elements, uncached-interning-details?, and
;;; resumable-node.  This macro also expects to be executed in a temporary float
;;; creation scope when appropriate.  Note that this macro updates
;;; resumable-node (a resumable-history-node structure) appropriately when
;;; finished transmitting.

(def-substitution-macro all-history-elements-sent-p (resumable-history-node)
  (>=f (count-of-history-elements-transmitted resumable-history-node)
       (resumable-sequence-length resumable-history-node)))

(defmacro iterate-over-uncached-history-range-for-transmission
    (float-timestamps-p float-values-p)
  (let ((timestamp-access-form
	  (if float-timestamps-p
	      `(managed-float-aref timestamp-vector ring-index)
	      `(managed-svref timestamp-vector ring-index)))
	(timestamp-writing-form
	  (if float-timestamps-p
	      `(write-icp-double-float-1 timestamp)
	      `(write-icp-history-timestamp timestamp)))
	(value-access-form
	  (if float-values-p
	      `(managed-float-aref value-vector ring-index)
	      `(managed-svref value-vector ring-index)))
	(value-writing-form
	  (if float-values-p
	      `(write-icp-double-float-1 value)
	      `(write-icp-attribute-value value corresponding-index?)))
	(timestamp-comparison-form
	  (if float-timestamps-p
	      `(=e previous-timestamp? timestamp)
	      `(evaluation-value-eql previous-timestamp? timestamp))))
    `(loop-with-or-without
       ,(if float-values-p nil `uncached-interning-details?)
       repeat number-of-uncached-elements
       with identical-timestamp-count = 0
       for ring-index = ring-index-of-first-uncached-element
       then (increment-active-element-index ring-index history)
       for timestamp = ,timestamp-access-form
       with previous-timestamp? = nil
       for value = ,value-access-form
       ,@(if float-values-p nil `(with corresponding-index? = nil))
       [ with next-interning-index? = (caar uncached-interning-details?) ]
       [ if (and next-interning-index? (=f next-interning-index? ring-index))
	    do
	    (progn (setq corresponding-index?
			 (cdar uncached-interning-details?))
		   (reclaim-icp-cons (icp-pop uncached-interning-details?))
		   (setq next-interning-index?
			 (caar uncached-interning-details?)))
	    else
	    (setq corresponding-index? nil) ]
       do
       ,timestamp-writing-form
       ,value-writing-form
       (if (and previous-timestamp? ,timestamp-comparison-form)
	   (incff identical-timestamp-count)
	   (setq identical-timestamp-count 0))
       (setq previous-timestamp? timestamp)
       finally
       (incff (count-of-history-elements-transmitted resumable-node)
	      number-of-uncached-elements)
       (setf (ring-index-of-oldest-history-value resumable-node)
	     (oldest-active-element-index history))
       (setf (count-of-preceding-identically-timestamped-values
	       resumable-node)
	     identical-timestamp-count)
       (unless (all-history-elements-sent-p resumable-node)
	 (multiple-value-bind (first-uncached-index managed-timestamp)
	     (get-following-history-timestamp
	       history
	       timestamp-vector
	       ring-index
	       1)
	   (setf (ring-index-of-next-uncached-history-value? resumable-node)
		 first-uncached-index)
	   (setf (timestamp-of-next-uncached-history-value? resumable-node)
		  managed-timestamp)))
       (reclaim-unprocessed-interning-details-if-any
	 uncached-interning-details?))))

(defun-void g2-transmit-add-history-range
    (resumable-node
      number-of-cached-elements
      cached-interning-details?
      ring-index-of-first-uncached-element
      number-of-uncached-elements
      uncached-interning-details?
      timestamps-use-float-array-p
      values-use-float-array-p)
  (when (>f number-of-cached-elements 0)
    (let* ((cached-timestamp-vector
	     (cached-timestamp-subsequence-for-resumable-history?
	       resumable-node))
	   (cached-timestamps-use-float-array-p
	     (managed-float-array-p cached-timestamp-vector))
	   (cached-value-vector
	     (cached-value-subsequence-for-resumable-history? resumable-node))
	   (cached-values-use-float-array-p
	     (managed-float-array-p cached-value-vector))
	   (first-cache-index
	     (index-of-next-cached-history-value? resumable-node)))
      (if (or cached-timestamps-use-float-array-p
	      cached-values-use-float-array-p)
	  (with-temporary-gensym-float-creation
	      write-icp-add-history-range-1
	    (cond
	      ((and cached-timestamps-use-float-array-p
		    cached-values-use-float-array-p)
	       (iterate-over-cached-history-range-for-transmission t t))
	      (cached-timestamps-use-float-array-p
	       (iterate-over-cached-history-range-for-transmission t nil))
	      (cached-values-use-float-array-p
	       (iterate-over-cached-history-range-for-transmission nil t))))
	  (iterate-over-cached-history-range-for-transmission nil nil))))
  (when (>f number-of-uncached-elements 0)
    (let* ((history (internal-history-for-object-passing? resumable-node))
	   (timestamp-vector (history-time-vector history))
	   (value-vector (history-value-vector history)))
      (if (or timestamps-use-float-array-p values-use-float-array-p)
	  (with-temporary-gensym-float-creation
	      write-icp-add-history-range-2
	    (cond
	      ((and timestamps-use-float-array-p values-use-float-array-p)
	       (iterate-over-uncached-history-range-for-transmission t t))
	      (timestamps-use-float-array-p
	       (iterate-over-uncached-history-range-for-transmission t nil))
	      (values-use-float-array-p
	       (iterate-over-uncached-history-range-for-transmission nil t))))
	  (iterate-over-uncached-history-range-for-transmission
	    nil
	    nil)))))

;;; The macro `iterate-over-cached-homogeneous-history-range-for-transmission'
;;; is internal to the G2-RPC3 module.  It is an abstraction designed solely for
;;; use by the function g2-transmit-add-homogeneous-history-range, which is the
;;; :writer branch in the ICP value protocol add-history-range for G2.  This
;;; macro expects to be executed in a lexical scope that has bound the following
;;; variables: cache-index, cached-timestamp-vector, cached-value-vector,
;;; element-type, number-of-cached-elements, cached-interning-details?, and
;;; resumable-node.  This macro also expects to be executed in a temporary float
;;; creation scope when appropriate.  Note that this macro updates
;;; resumable-node (a resumable-history-node structure) appropriately when
;;; finished transmitting.

(defmacro iterate-over-cached-homogeneous-history-range-for-transmission
    (float-timestamps-p float-values-p)
  (let ((timestamp-access-form
	  (if float-timestamps-p
	      `(managed-float-aref cached-timestamp-vector cache-index)
	      `(svref cached-timestamp-vector cache-index)))
	(timestamp-writing-form
	  (if float-timestamps-p
	      `(write-icp-double-float-1 timestamp)
	      `(write-icp-history-timestamp timestamp)))
	(value-access-form
	  (if float-values-p
	      `(managed-float-aref cached-value-vector cache-index)
	      `(svref cached-value-vector cache-index))))
    `(loop-with-element-type-case (element-type)
       repeat number-of-cached-elements
       for cache-index from first-cache-index
       for timestamp = ,timestamp-access-form
       for value = ,value-access-form
       [[symbol]
	with next-interning-index? = (caar cached-interning-details?) 
	for corresponding-index? = 
	(if (and next-interning-index?
		 (=f next-interning-index? cache-index))
	    (prog1 (cdar cached-interning-details?)
	      (reclaim-icp-cons (icp-pop cached-interning-details?))
	      (setq next-interning-index? (caar cached-interning-details?)))
	    nil) ]
       do
       ,timestamp-writing-form
       [[integer] (write-icp-fixnum value) ]
       [[float]   (write-icp-double-float-1 value) ]
       [[text]    (write-icp-text-string value) ]
       [[truth]   (write-icp-evaluation-truth-value value) ]
       [[symbol]  (write-icp-possibly-interned-symbol
		    value
		    corresponding-index?) ]
       finally
       (incff (count-of-history-elements-transmitted resumable-node)
	      number-of-cached-elements)
       (incff (index-of-next-cached-history-value? resumable-node)
	      number-of-cached-elements)
       (when (=f (index-of-next-cached-history-value? resumable-node)
		 size-of-cached-subsequence-for-resumable-history)
	 (setf (index-of-next-cached-history-value? resumable-node) nil))
       (reclaim-unprocessed-interning-details-if-any
	 cached-interning-details?))))

;;; The macro `iterate-over-uncached-homogeneous-history-range-for-transmission'
;;; is internal to the G2-RPC3 module.  It is an abstraction designed solely for
;;; use by the function g2-transmit-add-homogeneous-history-range, which is
;;; the:writer branch in the ICP value protocol add-homogeneous-history-range
;;; for G2.  This macro expects to be executed in a lexical scope that has bound
;;; the following variables: history, timestamp-vector, value-vector,
;;; element-type, ring-index-of-first-uncached-element,
;;; number-of-uncached-elements, uncached-interning-details?, and
;;; resumable-node.  This macro also expects to be executed in a temporary float
;;; creation scope when appropriate.  Note that this macro updates
;;; resumable-node (a resumable-history-node structure) appropriately when
;;; finished transmitting.

(defmacro iterate-over-uncached-homogeneous-history-range-for-transmission
    (float-timestamps-p float-values-p)
  (let ((timestamp-access-form
	  (if float-timestamps-p
	      `(managed-float-aref timestamp-vector ring-index)
	      `(managed-svref timestamp-vector ring-index)))
	(timestamp-writing-form
	  (if float-timestamps-p
	      `(write-icp-double-float-1 timestamp)
	      `(write-icp-history-timestamp timestamp)))
	(value-access-form
	  (if float-values-p
	      `(managed-float-aref value-vector ring-index)
	      `(managed-svref value-vector ring-index)))
	(timestamp-comparison-form
	  (if float-timestamps-p
	      `(=e previous-timestamp? timestamp)
	      `(evaluation-value-eql previous-timestamp? timestamp))))
    `(loop-with-element-type-case (element-type)
       repeat number-of-uncached-elements
       with identical-timestamp-count = 0
       for ring-index = ring-index-of-first-uncached-element
       then (increment-active-element-index ring-index history)
       for timestamp = ,timestamp-access-form
       with previous-timestamp? = nil
       for value = ,value-access-form
       [[symbol]
	with next-interning-index? = (caar uncached-interning-details?) 
	for corresponding-index? = 
	(if (and next-interning-index?
		 (=f next-interning-index? ring-index))
	    (prog1 (cdar uncached-interning-details?)
	      (reclaim-icp-cons (icp-pop uncached-interning-details?))
	      (setq next-interning-index? (caar uncached-interning-details?)))
	    nil) ]
       do
       ,timestamp-writing-form
       [[integer] (write-icp-fixnum value) ]
       [[float]   (write-icp-double-float-1 value) ]
       [[text]    (write-icp-text-string value) ]
       [[truth]   (write-icp-evaluation-truth-value value) ]
       [[symbol]  (write-icp-possibly-interned-symbol
		    value
		    corresponding-index?) ]
       (if (and previous-timestamp? ,timestamp-comparison-form)
	   (incff identical-timestamp-count)
	   (setq identical-timestamp-count 0))
       (setq previous-timestamp? timestamp)
       finally
       (incff (count-of-history-elements-transmitted resumable-node)
	      number-of-uncached-elements)
       (setf (ring-index-of-oldest-history-value resumable-node)
	     (oldest-active-element-index history))
       (setf (count-of-preceding-identically-timestamped-values
	       resumable-node)
	     identical-timestamp-count)
       (unless (all-history-elements-sent-p resumable-node)
	 (multiple-value-bind (first-uncached-index managed-timestamp)
	     (get-following-history-timestamp
	       history
	       timestamp-vector
	       ring-index
	       1)
	   (setf (ring-index-of-next-uncached-history-value? resumable-node)
		 first-uncached-index)
	   (setf (timestamp-of-next-uncached-history-value? resumable-node)
		 managed-timestamp)))
       (reclaim-unprocessed-interning-details-if-any
	 uncached-interning-details?))))

(defun-void g2-transmit-add-homogeneous-history-range
    (resumable-node
      element-type
      number-of-cached-elements
      cached-interning-details?
      ring-index-of-first-uncached-element
      number-of-uncached-elements
      uncached-interning-details?
      timestamps-use-float-array-p)
  (let ((values-use-float-array-p (eq element-type '|float|)))
    (when (>f number-of-cached-elements 0)
      (let* ((cached-timestamp-vector
	       (cached-timestamp-subsequence-for-resumable-history?
		 resumable-node))
	     (cached-timestamps-use-float-array-p
	       (managed-float-array-p cached-timestamp-vector))
	     (cached-value-vector
	       (cached-value-subsequence-for-resumable-history?
		 resumable-node))
	     (cached-values-use-float-array-p
	       (managed-float-array-p cached-value-vector))
	     (first-cache-index
	       (index-of-next-cached-history-value? resumable-node)))
	(if (or cached-timestamps-use-float-array-p
		cached-values-use-float-array-p)
	    (with-temporary-gensym-float-creation
		write-icp-add-homogeneous-history-range-1
	      (cond
		((and cached-timestamps-use-float-array-p
		      values-use-float-array-p)
		 (iterate-over-cached-homogeneous-history-range-for-transmission
		   t
		   t))
		(cached-timestamps-use-float-array-p
		 (iterate-over-cached-homogeneous-history-range-for-transmission
		   t
		   nil))
		(cached-values-use-float-array-p
		 (iterate-over-cached-homogeneous-history-range-for-transmission
		   nil
		   t))))
	  (iterate-over-cached-homogeneous-history-range-for-transmission
	    nil
	    nil))))
    (when (>f number-of-uncached-elements 0)
      (let* ((history (internal-history-for-object-passing? resumable-node))
	     (timestamp-vector (history-time-vector history))
	     (value-vector (history-value-vector history)))
	(if (or timestamps-use-float-array-p values-use-float-array-p)
	    (with-temporary-gensym-float-creation
		write-icp-add-homogeneous-history-range-2
	      (cond
		((and timestamps-use-float-array-p values-use-float-array-p)
		 (iterate-over-uncached-homogeneous-history-range-for-transmission
		   t
		   t))
		(timestamps-use-float-array-p
		 (iterate-over-uncached-homogeneous-history-range-for-transmission
		   t
		   nil))
		(values-use-float-array-p
		 (iterate-over-uncached-homogeneous-history-range-for-transmission
		   nil
		   t))))
	    (iterate-over-uncached-homogeneous-history-range-for-transmission
	      nil
	      nil))))))
  
;;; The macro `iterate-over-history-range-for-reception' is internal to the
;;; G2-RPC3 module.  It is an abstraction designed solely for use by the
;;; function g2-receive-add-history-range, which is the :reader branch in the
;;; ICP value protocol add-history-range for G2.  This macro expects to be
;;; executed in a lexical scope that has bound the following variables: history,
;;; timestamp-vector, value-vector, and number-of-elements.  This macro also
;;; expects to be executed in a temporary float creation scope when appropriate.

(defmacro iterate-over-history-range-for-reception
    (float-timestamps-p float-values-p)
  (let* ((timestamp-reading-form
	   (if float-timestamps-p
	       `(read-icp-double-float-1)
	       `(read-icp-history-timestamp)))
	 (timestamp-access-form
	   (if float-timestamps-p
	       `(managed-float-aref timestamp-vector ring-index)
	       `(managed-svref timestamp-vector ring-index)))
	 (value-reading-form
	   (if float-values-p
	       `(read-icp-double-float-1)
	       `(read-icp-attribute-value)))
	 (value-access-form
	   (if float-values-p
	       `(managed-float-aref value-vector ring-index)
	       `(managed-svref value-vector ring-index))))
    `(if (resumable-object-ignoring-input? current-receiving-resumable-object)
	 (loop repeat number-of-elements
	       with starting-newest-ring-index
	       = (increment-active-element-index
		   (newest-active-element-index history)
		   history)
	       for ring-index = starting-newest-ring-index
	       then (increment-active-element-index ring-index history)
	       do
	   ,timestamp-reading-form
	   ,value-reading-form)
	 (loop repeat number-of-elements
	       with starting-newest-ring-index
	       = (increment-active-element-index
		   (newest-active-element-index history)
		   history)
	       for ring-index = starting-newest-ring-index
	       then (increment-active-element-index ring-index history)
	       do
	   (let* ((timestamp ,timestamp-reading-form)
		  (value ,value-reading-form))
	     (setf ,timestamp-access-form timestamp)
	     (setf ,value-access-form value))
	       finally
		 (setf (newest-active-element-index history)
		       ring-index)))))
  
(defun-void g2-receive-add-history-range
    (timestamps-use-float-array-p values-use-float-array-p number-of-elements)
  (let* ((history-item
	   (current-resumable-subobject-being-built?
	     current-receiving-resumable-object))
	 (history (get-history-ring-buffer-if-any history-item nil))
	 (timestamp-vector (history-time-vector history))
	 (value-vector (history-value-vector history)))
    (unless timestamps-use-float-array-p
      (when (managed-float-array-p timestamp-vector)
	(switch-from-managed-float-array-to-managed-array
	  history
	  history-time-vector
	  timestamp-vector)))
    (unless values-use-float-array-p
      (when (managed-float-array-p value-vector)
	(switch-from-managed-float-array-to-managed-array
	  history
	  history-value-vector
	  value-vector)))
    (if (or timestamps-use-float-array-p values-use-float-array-p)
	(with-temporary-gensym-float-creation read-icp-add-history-range
	  (cond
	    ((and timestamps-use-float-array-p values-use-float-array-p)
	     (iterate-over-history-range-for-reception t t))
	    (timestamps-use-float-array-p
	     (iterate-over-history-range-for-reception t nil))
	    (values-use-float-array-p
	     (iterate-over-history-range-for-reception nil t))))
	(iterate-over-history-range-for-reception nil nil))))

;;; The macro `iterate-over-homogeneous-history-range-for-reception' is internal
;;; to the G2-RPC3 module.  It is an abstraction designed solely for use by the
;;; function g2-receive-add-history-range, which is the :reader branch in the
;;; ICP value protocol add-homogeneous-history-range for G2.  This macro expects
;;; to be executed in a lexical scope that has bound the following variables:
;;; history, timestamp-vector, value-vector, element-type, and
;;; number-of-elements.  This macro also expects to be executed in a temporary
;;; float creation scope when appropriate.

(defmacro iterate-over-homogeneous-history-range-for-reception
    (float-timestamps-p float-values-p)
  (let* ((timestamp-reading-form
	   (if float-timestamps-p
	       `(read-icp-double-float-1)
	       `(read-icp-history-timestamp)))
	 (timestamp-access-form
	   (if float-timestamps-p
	       `(managed-float-aref timestamp-vector ring-index)
	       `(managed-svref timestamp-vector ring-index)))
	 (value-access-form
	   (if float-values-p
	       `(managed-float-aref value-vector ring-index)
	       `(managed-svref value-vector ring-index))))
    `(if (resumable-object-ignoring-input? current-receiving-resumable-object)
	 (loop-with-element-type-case (element-type)
	   repeat number-of-elements
	   with starting-newest-ring-index
	   = (increment-active-element-index
	       (newest-active-element-index history)
	       history)
	   for ring-index = starting-newest-ring-index
	   then (increment-active-element-index ring-index history)
	   do
	   ,timestamp-reading-form
	   [[integer] (read-icp-fixnum) ]
	   [[float]   (read-icp-double-float-1) ]
	   [[text]    (read-icp-text-string) ]
	   [[truth]   (read-icp-fixnum) ]
	   [[symbol]  (read-icp-possibly-interned-symbol) ]
	   )
	 (loop-with-element-type-case (element-type)
           repeat number-of-elements
	   with starting-newest-ring-index
	   = (increment-active-element-index
	       (newest-active-element-index history)
	       history)
	   for ring-index = starting-newest-ring-index
	   then (increment-active-element-index ring-index history)
	   for timestamp = ,timestamp-reading-form
	   for value =
	   [[integer] (read-icp-fixnum) ]
	   [[float]   (read-icp-double-float-1) ]
	   [[text]    (read-icp-text-string) ]
	   [[truth]   (read-icp-fixnum) ]
	   [[symbol]  (read-icp-possibly-interned-symbol) ]
	   do
	   (setf ,timestamp-access-form timestamp)
	   (setf ,value-access-form value)
	   finally
	   (setf (newest-active-element-index history)
		 ring-index)))))

(defun g2-receive-add-homogeneous-history-range
    (timestamps-use-float-array-p
      element-type
      number-of-elements)
  (let* ((history-item
	   (current-resumable-subobject-being-built?
	     current-receiving-resumable-object))
	 (history (get-history-ring-buffer-if-any history-item nil))
	 (timestamp-vector (history-time-vector history))
	 (value-vector (history-value-vector history)))
    (unless timestamps-use-float-array-p
      (when (managed-float-array-p timestamp-vector)
	(switch-from-managed-float-array-to-managed-array
	  history
	  history-time-vector
	  timestamp-vector)))
    (let ((values-use-float-array-p (eq element-type '|float|)))
      (if (or timestamps-use-float-array-p values-use-float-array-p)
	  (with-temporary-gensym-float-creation
	      read-icp-add-homogeneous-history-range
	    (cond
	      ((and timestamps-use-float-array-p values-use-float-array-p)
	       (iterate-over-homogeneous-history-range-for-reception t t))
	      (timestamps-use-float-array-p
	       (iterate-over-homogeneous-history-range-for-reception t nil))
	      (values-use-float-array-p
	       (iterate-over-homogeneous-history-range-for-reception nil t))))
	  (iterate-over-homogeneous-history-range-for-reception nil nil)))))

(defun-void g2-write-history-timestamp (history-timestamp)
  (cond
    ((evaluation-integer-p history-timestamp)
     (write-icp-byte attribute-value-integer-tag)
     (write-icp-fixnum history-timestamp))
    ((managed-float-p history-timestamp)
     (write-icp-byte attribute-value-float-tag)
     (write-icp-managed-double-float history-timestamp))
    #+development
    (t (cerror "Continue, writing nothing ~
                (This behavior is what the user would get"
	       "WRITE-ICP-HISTORY-TIMESTAMP: ~
                Unexpected type for timestamp ~a"
	       history-timestamp))))




	   
;;;; [14.3.4.5] G2 Resumable List Protocol

(defun-void g2-send-add-value-list-range
    (number-of-elements resumable-node interning-details?)
  (write-icp-fixnum number-of-elements)
  (loop-with-or-without interning-details?
    for list-index from 1 to number-of-elements
    for list-element = (internal-list-for-object-passing resumable-node)
		     then (list-next-element-real list-element)
    
    with corresponding-index? = nil
    [ with next-interning-index? = (caar interning-details?) ]
    [ if (and next-interning-index?
	      (=f next-interning-index? list-index))
	 do
	 (progn (setq corresponding-index? (cdar interning-details?))
		(reclaim-icp-cons (icp-pop interning-details?))
		(setq next-interning-index? (caar interning-details?)))
	 else
	 (setq corresponding-index? nil) ]
    do
    (write-icp-attribute-value
      (list-element-value list-element)
      corresponding-index?)
    finally
      (setf (internal-list-for-object-passing resumable-node)
	    (list-next-element-real list-element))
      (reclaim-unprocessed-interning-details-if-any interning-details?)))

(defmacro bind-for-list-range-if-possible
    ((current-subobject?-var) &body body)
  (unless (symbolp current-subobject?-var)
    (error "BIND-FOR-LIST-RANGE-IF-POSSIBLE: ~
            current-subobject?-var should be a symbol, not ~s"
	   current-subobject?-var))
  `(let* ((,current-subobject?-var
	     (current-resumable-subobject-being-built?
	       current-receiving-resumable-object))
	  (current-subobject-is-frame-p (framep ,current-subobject?-var)))
     (cond
       ((and current-subobject-is-frame-p
	     (frame-of-class-p ,current-subobject?-var 'value-list))
	nil)
       (current-subobject-is-frame-p
	(record-object-building-problem-on-receiving-side
		 'unexpected-non-value-list
		 nil
		 nil
		 (class ,current-subobject?-var)))
       ((null ,current-subobject?-var)
	(record-object-building-problem-on-receiving-side
	    'premature-access-to-toplevel-g2-value-list
	    nil
	    nil
	    nil))
       (t (record-object-building-problem-on-receiving-side
	    'g2-value-list-deleted-during-object-passing
	    nil
	    nil
	    nil)))
       ,@body))

(defun-void g2-receive-add-value-list-range (number-of-elements)
  (bind-for-list-range-if-possible (current-subobject?)
    (if (resumable-object-ignoring-input?
	  current-receiving-resumable-object)
	(loop repeat number-of-elements
	      do
	  (read-icp-attribute-value))
	(loop with list-element-type = (list-type current-subobject?)
	      repeat number-of-elements
	      for new-value = (read-icp-attribute-value)
	      do
	  (cond
	    ((type-specification-type-p new-value list-element-type)
	     (g2-list-insert-for-object-passing
	       new-value
	       current-subobject?))
	    (t
	     (reclaim-managed-number-or-value new-value)
	     (record-object-building-problem-on-receiving-side
	       'value-list-contains-an-element-inappropriate-for-receiving-array
	       nil
	       nil
	       (class current-subobject?))))))))


(defun-void g2-send-add-homogeneous-value-list-range
    (number-of-elements element-type resumable-node interning-details?)
  (write-icp-fixnum number-of-elements)
  (write-icp-resumable-sequence-element-type element-type)
  (loop-with-element-type-case (element-type)
    for list-index from 1 to number-of-elements
    for list-element = (internal-list-for-object-passing resumable-node)
		     then (list-next-element-real list-element)
    for element-value
	= (list-element-value list-element)
    [[symbol]
     with next-interning-index? = (caar interning-details?) 
     for corresponding-index? = 
     (if (and next-interning-index?
	      (=f next-interning-index? list-index))
	 (prog1 (cdar interning-details?)
	   (reclaim-icp-cons (icp-pop interning-details?))
	   (setq next-interning-index? (caar interning-details?)))
	 nil) ]
    do
    [[integer] (write-icp-fixnum element-value) ]
    [[float]   (write-icp-managed-double-float element-value) ]
    [[text]    (write-icp-text-string element-value) ]
    [[truth]   (write-icp-evaluation-truth-value
		 (evaluation-truth-value-value-function element-value)) ]
    [[symbol]  (write-icp-possibly-interned-symbol
		 element-value
		 corresponding-index?) ]
    finally
      (setf (internal-list-for-object-passing resumable-node)
	    (list-next-element-real list-element))
      (reclaim-unprocessed-interning-details-if-any interning-details?)))

(defun-void g2-receive-add-homogeneous-value-list-range
    (number-of-elements element-type)
  (bind-for-list-range-if-possible (current-subobject?)
    (if (resumable-object-ignoring-input?
	  current-receiving-resumable-object)
	(loop-with-element-type-case (element-type)
	  repeat number-of-elements
		do
	  [[integer] (read-icp-fixnum) ]
	  [[float]   (read-icp-managed-double-float) ]
	  [[text]    (read-icp-text-string) ]
	  [[truth]   (read-icp-evaluation-truth-value) ]
	  [[symbol]  (read-icp-possibly-interned-symbol) ]
		)
	(loop-with-element-type-case (element-type)
	  repeat number-of-elements
		for element =
		[[integer] (read-icp-fixnum) ]
		[[float]   (read-icp-managed-double-float) ]
		[[text]    (read-icp-text-string) ]
		[[truth]   (read-icp-evaluation-truth-value) ]
		[[symbol]  (read-icp-possibly-interned-symbol) ]
		do
	  (g2-list-insert-for-object-passing
	    element
	    current-subobject?)))))

(defun-allowing-unwind check-resumable-value-list-contents
    (resumable-node resumable-object)
  (with-throw-handling check-resumable-value-list-contents
    (let ((current-object
	    (resumable-instance-current-object resumable-node))
	  (toplevel-object
	    (object-or-handle-to-be-passed resumable-object)))
      (when (frame-has-been-reprocessed-p
	      current-object
	      (resumable-instance-reference-serial-number
		resumable-node))
	(throw*
	  :abort-transmitting-resumable-object
	  (icp-list
	    'g2-value-list-subobject-deleted
	    (twith-output-to-text-string
	      (tformat "A g2-value-list ")
	      (cond
		((and (framep toplevel-object)
		      (eq current-object toplevel-object))
		 (tformat "at top level in the argument list "))
		((framep toplevel-object)
		 (tformat ", being sent as a subobject of ~NF, "
			  toplevel-object))
		(t nil))
	      (tformat "has been deleted")))))
      (let ((list-element?
	      (internal-list-for-object-passing resumable-node)))
	(when list-element?
	  (unless (eq (list-element-value list-element?)
		      g2-list-structure-marker)
	    (unless (eql current-object (list-frame list-element?))
	      (throw*
		:abort-transmitting-resumable-object
		(icp-list
		  'g2-value-list-element-removed
		  (twith-output-to-text-string
		    (tformat
		      "An element of the g2-value-list ~NF " current-object)
		    (if (eq current-object toplevel-object)
			(tformat "at top level in the argument list ")
			(tformat ", being sent as a subobject of ~NF, "
				 toplevel-object))
		    (tformat "has been removed")))))))))))

(defmacro enqueue-resumable-objects-waiting-for-unclog
    (resumable-object icp-socket desired-bandwidth)
  (avoiding-variable-capture (icp-socket resumable-object)
    `(progn
       (setf (resumable-object-bandwidth-denied-by-clog? ,resumable-object)
	     ,desired-bandwidth)
       (enqueue ,resumable-object
		(resumable-objects-waiting-for-unclog ,icp-socket)
		(resumable-objects-waiting-for-unclog-tail ,icp-socket)
		icp-cons))))

(defvar minimnal-bandwidth-for-resumable-sequence-range 100)

(defun-simple transmit-resumable-value-list-range
    (resumable-node resumable-object icp-port)
  (with-throw-handling transmit-resumable-value-list-range
    (when (internal-list-for-object-passing resumable-node)
      (handle-throw
	(check-resumable-value-list-contents
	  resumable-node
	  resumable-object))
      (let ((element-type? (homogeneous-element-type? resumable-node))
	    (icp-socket (parent-icp-socket icp-port)))
	(multiple-value-bind (number-of-elements
			       bandwidth-needed
			       elements-remain-p
			       interning-details
			       network-is-limiting-factor-p)
	    (get-value-list-transmission-info
	      resumable-node
	      element-type?
	      resumable-object
	      icp-port)
	  (handle-throw number-of-elements)
	  (when (and elements-remain-p (<=f number-of-elements 0))
	    (reclaim-icp-tree interning-details)
	    (cond
	      (network-is-limiting-factor-p
	       (enqueue-resumable-objects-waiting-for-unclog
		 resumable-object
		 icp-socket
		 minimnal-bandwidth-for-resumable-sequence-range)
	       (handle-throw
		 (suspend-object-passing-transmission
		   resumable-object
		   resumable-node
		   nil ;reschedule-p
		   )))
	      (t
	       (handle-throw
		 (suspend-object-passing-transmission
		   resumable-object
		   resumable-node)))))
	  (allocate-bandwidth-for-resumable-node
	    bandwidth-needed
	    resumable-node
	    resumable-object)
	  (cond
	    ((and elements-remain-p element-type?)
	     (write-icp-add-homogeneous-value-list-range
	       number-of-elements
	       element-type?
	       resumable-node
	       interning-details)
	     (handle-throw
	       (suspend-object-passing-transmission
		 resumable-object
		 resumable-node)))
	    (elements-remain-p
	     (write-icp-add-value-list-range
	       number-of-elements
	       resumable-node
	       interning-details)
	     (handle-throw
	       (suspend-object-passing-transmission
		 resumable-object
		 resumable-node)))
	    (element-type?
	     (write-icp-add-homogeneous-value-list-range
	       number-of-elements
	       element-type?
	       resumable-node
	       interning-details))
	    (t
	     (write-icp-add-value-list-range
	       number-of-elements
	       resumable-node
	       interning-details))))))))





;; ...
;; jh, 3/28/94.  Check soon if there is a better abstraction for slot-constants
;; than that embodied in g2-get-attribute-for-object-passing.  Perhaps slot
;; constants are in flux at this time.  Note that
;; g2-get-attribute-for-object-passing creates an evaluation value that must be
;; reclaimed.  Currently this is done in the :reclaimer for the
;; resumable-attribute-value slot in the resumable-value-node structure.

(defun-simple g2-get-attribute-for-object-passing (object attribute-name)
  (case (resumable-attribute-type attribute-name)
    (attribute
     (let ((base-name (resumable-attribute-base-name attribute-name))
	   (class-qualifier? (resumable-attribute-class-qualifier? attribute-name)))
       (if (memq base-name
		 (all-immediate-object-passing-system-attribute-names))
	   (body-of-g2-get-system-attribute-for-object-passing
	     object
	     base-name)
	   (let ((raw-value?
		    (if (of-class-p object 'object)
			(get-slot-value-if-any object base-name class-qualifier?)
			(frame-or-evaluation-value-user-attribute-value
			  object
			  base-name
			  class-qualifier?))))
	     (cond
	       ((evaluation-value-p raw-value?)
		(copy-evaluation-value raw-value?))
	       ((slot-constantp raw-value?)
		(let ((inner-value (first raw-value?))
		      (constant-type (second raw-value?)))
		  (case constant-type
		    (truth-value
		     ;; ... reclaimed in write-icp-attribute-value
		     ;; review this anomaly!
		     (make-evaluation-truth-value inner-value))
		    (otherwise (copy-evaluation-value inner-value)))))
	       (t raw-value?))))))))

(defun-void g2-write-icp-attribute-value (simple-value corresponding-index?)
  (evaluation-typecase simple-value
    (evaluation-integer (write-icp-byte attribute-value-integer-tag)
			(write-icp-fixnum evaluation-integer))
    (managed-float (write-icp-byte attribute-value-float-tag)
		   (write-icp-managed-double-float managed-float))
    (evaluation-text (write-icp-byte attribute-value-text-tag)
		     (write-icp-text-string evaluation-text))
    (evaluation-truth-value
      (write-icp-byte attribute-value-truth-value-tag)
      (write-icp-evaluation-truth-value evaluation-truth-value))
    (evaluation-symbol
      (write-icp-possibly-interned-symbol
	evaluation-symbol
	corresponding-index?))
    (evaluation-sequence
      (write-icp-byte attribute-value-evaluation-sequence-tag)
      (write-icp-evaluation-sequence evaluation-sequence))
    (evaluation-structure
      (write-icp-byte attribute-value-evaluation-structure-tag)
      (write-icp-evaluation-structure evaluation-structure))
    (evaluation-no-value (write-icp-byte attribute-value-null-tag))))




;;;; [14.3.5] G2 RPC Argument Protocols

(defun-void g2-maybe-continue-rpc-after-object-building (rpc-arglist-structure)
  (let ((previous?
	  (previous-resumable-object-in-rpc-arglist?
	    current-receiving-resumable-object))
	(next?
	  (next-resumable-object-in-rpc-arglist?
	    current-receiving-resumable-object)))
    (cond
      ((and previous? next?)
       (setf (next-resumable-object-in-rpc-arglist? previous?) next?)
       (setf (previous-resumable-object-in-rpc-arglist? next?) previous?))
      (previous?
       (setf (next-resumable-object-in-rpc-arglist? previous?) next?))
      (next?
       (setf (previous-resumable-object-in-rpc-arglist? next?) nil))
      (t (g2-continue-rpc-after-final-object-build rpc-arglist-structure)))))

(defun-simple g2-continue-rpc-after-final-object-build (rpc-arglist-structure)
  ;; Check for deferred problems building any RPC object.
  (let ((rpc-arglist (rpc-arglist-being-built rpc-arglist-structure)))
    (loop for arg in rpc-arglist
	  do
      (when (receiving-resumable-object-p arg)
	(let ((problem? (resumable-object-ignoring-input? arg)))
	  (when problem?
	    (deferred-abort-rpc-for-failed-resumable-object
	      arg
	      (enclosing-rpc-arglist-structure? arg)
	      problem?)
	    (reclaim-receiving-resumable-object arg)
	    (return-from g2-continue-rpc-after-final-object-build)))))
    (let ((converted-rpc-arglist
	    (loop for arg in rpc-arglist
		  collect
		  (cond
		    ((receiving-resumable-object-p arg)
		     (let ((object (resumable-object-being-built? arg)))
		       ;; Object is known non-nil at this point.
		       (setf (g2-rpc-object-handed-off-to-user-p object) t)
		       object))
		    (t (when (framep arg)
			 (setf (g2-rpc-object-handed-off-to-user-p arg) t))
		       arg))
		    using icp-cons))
	  (continuation-tag
	    (continuation-waiting-for-rpc-arglist
	      rpc-arglist-structure)))
      (cond
	((and ;(or system-is-running system-has-paused)
	      (memq continuation-tag '(start call return ole)))
	 (case continuation-tag
	   (start
	    (receive-start-or-call-remote-procedure
	      current-icp-socket
	      (remote-procedure-name-symbol
		(rpc-name-waiting-for-rpc-arglist rpc-arglist-structure))
	      (icp-cons (frame-serial-number-0) (icp-cons nil converted-rpc-arglist))
	      nil))
	   (call
	    (receive-start-or-call-remote-procedure
	      current-icp-socket
	      (remote-procedure-name-symbol
		(rpc-name-waiting-for-rpc-arglist rpc-arglist-structure))
	      (icp-cons (frame-serial-number-0) (icp-cons nil converted-rpc-arglist))
	      (rpc-identifier-waiting-for-rpc-arglist
		rpc-arglist-structure)))
	   (return
	     (let ((remote-procedure-identifier
		     (lookup-remote-procedure-identifier-from-index
		       (rpc-index-waiting-for-rpc-arglist rpc-arglist-structure))))
	       (when (and remote-procedure-identifier
			  (eq 'outstanding
			      (remote-procedure-identifier-state
				remote-procedure-identifier)))
		 (setf (remote-procedure-identifier-state remote-procedure-identifier)
		       'returned))
	       (receive-remote-procedure-values
		 remote-procedure-identifier
		 (icp-cons (frame-serial-number-0) (icp-cons nil converted-rpc-arglist))))
	     ;; Note: converted-rpc-arglist is NOT reclaimed here, but in
	     ;; receive-remote-procedure-values-inside-catch-handlers.
	     )
	   (ole
	    (let ((object-passed-by-ole (car converted-rpc-arglist)))
	      (delete-frame-note-if-any
		'ole-object-passing-in-progress
		object-passed-by-ole)
	      (reclaim-transformed-rpc-argument-list converted-rpc-arglist nil)))))
	(t ;; jh, 5/9/95.  This clause may be reached when the sending side has
	   ;; time to finish transmitting its object before the receiving side
	   ;; returns an rpc-error message (say because the named procedure does
	   ;; not exist on the receiving side).  Removed the #+development
	   ;; cerror therefore and added some genuine memory management as well.
	   (loop for arg in converted-rpc-arglist
		 do
	     (when (framep arg)
	       (setf (g2-rpc-object-handed-off-to-user-p arg) nil)))
	   (reclaim-transformed-rpc-argument-list converted-rpc-arglist nil)))
      (reclaim-receiving-rpc-arglist-structure rpc-arglist-structure))))


;;;; [16] ICP Message Handler to Build Resumable Objects in G2

;;; The function `deferred-abort-rpc-for-failed-resumable-object' is called just
;;; before handing off the RPC arglist, if a failure ever happened while the
;;; handler was building an RPC object argument on the receiving side.  Unless
;;; this function is called after the last resumable object in the arglist has
;;; been built, an ICP out-of-synch error will occur and the entire ICP socket
;;; will need to be shut down.  Hence there is provision in the various
;;; def-icp-value-protocols to check the resumable-object-ignoring-input? slot
;;; of the receiving-resumable-object instead of aborting the build at the
;;; moment an error is detected.

(defun-allowing-unwind deferred-abort-rpc-for-failed-resumable-object
    (resumable-object rpc-arglist problem)
  (let* ((rpc-name? (resumable-object-rpc-name? resumable-object))
	 (continuation
	   (continuation-waiting-for-rpc-arglist rpc-arglist))
	 (attribute-name? (object-building-problem-attribute? problem))
	 (class-name? (object-building-problem-class-name? problem))	 
	 (extra-info-format?
	   (object-building-problem-extra-info-format-string? problem))
	 (extra-info-components
	   (object-building-problem-extra-info problem))
	 (error-string
	   (twith-output-to-text-string
	     (if rpc-name?
		 (tformat "A remote procedure call to ~A has been aborted "
			  rpc-name?)
		 (tformat "A remote procedure call has been aborted "))
	     (when class-name?
	       (tformat
		 "while receiving a subobject of class ~A "
		 class-name?))
	     (when attribute-name?
	       (let ((attribute-substring
		       (if (typep attribute-name? 'fixnum)
			   (tformat-text-string "index ~A" attribute-name?)
			   (tformat-text-string
			     "attribute ~A"
			     attribute-name?))))
		 (tformat "at ~A: " attribute-substring)
		 (reclaim-text-string attribute-substring)))
	     (tformat "~A.  " (object-building-problem-name problem))
	     (when extra-info-format?
	       (apply #'tformat extra-info-format? extra-info-components)))))
    ;; Error-calling-remote-procedure, error-starting-remote-procedure, and
    ;; signal-code-body-invocation-error will reclaim error-string.
    (case continuation
      ((start call)
       (remote-procedure-error
	 current-icp-socket
	 'problem-building-rpc-object-arguments error-string
	 (when (eq continuation 'call)
	   (rpc-identifier-waiting-for-rpc-arglist rpc-arglist))))
      (return
	;; Adapted from receive-remote-procedure-values in PROC-REMOTE.
	(let*-while-true ((remote-procedure-identifier?
			    (lookup-remote-procedure-identifier-from-index
			      (rpc-index-waiting-for-rpc-arglist rpc-arglist)))
			  (remote-procedure-call?
			    (remote-procedure-identifier-caller
			      remote-procedure-identifier?))
			  (caller?
			    (code-body-caller remote-procedure-call?)))
	  (signal-code-body-invocation-error
	    caller? 'rpc-error 1
	    error-string
	    nil nil nil nil nil)))
      (otherwise ;trying to build a handled RPC object
       (remote-procedure-error
	 current-icp-socket
	 'problem-registering-rpc-object-on-network
	 error-string
	 nil)))))




;;;; [15] Sending Side Task to Transmit Resumable Objects After Preflight

(defun suspend-object-passing-transmission
    (resumable-object current-resumable-node &optional (reschedule-p t))
  (with-throw-handling suspend-object-passing-transmission
    (write-icp-suspend-building-object
      (resumable-object-allocated-bandwidth resumable-object))
    (debug-object-passing "(5) scheduling ~s" resumable-object)
    (when (schedule-task-in-place-p
	    (resumable-object-task resumable-object))
      (cancel-task (resumable-object-task resumable-object)))
    (when reschedule-p
      (with-current-scheduling ((resumable-object-task resumable-object)
				(resumable-object-priority resumable-object)
				nil
				nil
				t)
	(try-to-transmit-resumable-object resumable-object)))
    (let ((suspended-resumable-node
	    (if (resumable-instance-or-complex-value-node-p current-resumable-node)
		current-resumable-node
		(resumable-node-parent-node? current-resumable-node))))
      (throw* :suspend-transmitting-resumable-object suspended-resumable-node))))

(defun-allowing-unwind check-resumable-value-vector-contents
    (resumable-node resumable-object)
  (with-throw-handling check-resumable-value-vector-contents
    (let ((current-object
	    (resumable-instance-current-object resumable-node))
	  (toplevel-object
	    (object-or-handle-to-be-passed resumable-object)))
      (when (frame-has-been-reprocessed-p
	      current-object
	      (resumable-instance-reference-serial-number
		resumable-node))
	(throw*
	  :abort-transmitting-resumable-object
	  (icp-list
	    'g2-value-array-deleted
	    (twith-output-to-text-string
	      (tformat "A g2-value-array ")
	      (if (eq current-object toplevel-object)
		  (tformat "at top level in the argument list ")
		  (tformat ", being sent as a subobject of ~NF, "
			   toplevel-object))
	      (tformat "has been deleted")))))
      (unless (<=f (resumable-sequence-length resumable-node)
		   (g2-array-length current-object))
	(throw*
	  :abort-transmitting-resumable-object
	  (icp-list
	    'g2-value-array-length-diminished
	    (twith-output-to-text-string
	      (tformat "A g2-value-array ~NF" current-object)
	      (if (eq current-object toplevel-object)
		  (tformat " at top level in the argument list ")
		  (tformat ", being sent as a subobject of ~NF, "
			   toplevel-object))
	      (tformat "has had its length changed"))))))))

(defun-simple transmit-resumable-value-vector-range
    (resumable-node resumable-object icp-port)
  (with-throw-handling transmit-resumable-value-vector-range
    (let ((remaining-element-count
	    (1+f (highest-empty-value-vector-index resumable-node))))
      (unless (<f remaining-element-count 1)
	(handle-throw
	  (check-resumable-value-vector-contents
	    resumable-node
	    resumable-object))
	(let ((element-type? (homogeneous-element-type? resumable-node))
	      (icp-socket (parent-icp-socket icp-port)))
	  (multiple-value-bind (number-of-elements
				 bandwidth-needed
				 interning-details
				 network-is-limiting-factor-p)
	      (get-value-vector-transmission-info
		resumable-node
		element-type?
		resumable-object
		icp-port)
	    (when (<=f number-of-elements 0)
	      (reclaim-icp-tree interning-details)
	      (cond
		(network-is-limiting-factor-p
		 (enqueue-resumable-objects-waiting-for-unclog
		   resumable-object
		   icp-socket
		   minimnal-bandwidth-for-resumable-sequence-range)
		 (handle-throw
		   (suspend-object-passing-transmission
		     resumable-object
		     resumable-node
		     nil ;reschedule-p
		     )))
		(t
		 (handle-throw
		   (suspend-object-passing-transmission
		     resumable-object
		     resumable-node)))))
	    (allocate-bandwidth-for-resumable-node
	      bandwidth-needed
	      resumable-node
	      resumable-object)
	    (cond
	      ((and (<f number-of-elements remaining-element-count)
		    element-type?)
	       (write-icp-add-homogeneous-value-vector-range
		 number-of-elements
		 element-type?
		 resumable-node
		 interning-details)
	       (handle-throw
		 (suspend-object-passing-transmission
		   resumable-object
		   resumable-node)))
	      ((<f number-of-elements remaining-element-count)
	       (write-icp-add-value-vector-range
		 number-of-elements
		 resumable-node
		 interning-details)
	       (handle-throw
		 (suspend-object-passing-transmission
		   resumable-object
		   resumable-node)))
	      (element-type?
	       (write-icp-add-homogeneous-value-vector-range
		 number-of-elements
		 element-type?
		 resumable-node
		 interning-details))
	      (t
	       (write-icp-add-value-vector-range
		 remaining-element-count
		 resumable-node
		 interning-details)))))))))

(defun-simple transmit-resumable-history-range
    (resumable-node resumable-object icp-port)
  (with-throw-handling transmit-resumable-history-range
    (unless (all-history-elements-sent-p resumable-node)
      (let ((element-type? (homogeneous-element-type? resumable-node))
	    (icp-socket (parent-icp-socket icp-port)))
	(multiple-value-bind (number-of-cached-elements
			       cached-interning-details
			       ring-index-of-first-uncached-element
			       number-of-uncached-elements			   
			       uncached-interning-details
			       uncached-timestamps-use-float-array-p
			       uncached-values-use-float-array-p
			       bandwidth-needed
			       network-is-limiting-factor-p)
	    (get-history-array-transmission-info
	      resumable-node
	      resumable-object
	      element-type?
	      icp-port)
	  (handle-throw number-of-cached-elements)
	  (unless (or (>f number-of-cached-elements 0)
		      (>f number-of-uncached-elements 0))
	    (reclaim-icp-tree cached-interning-details)
	    (reclaim-icp-tree uncached-interning-details)
	    (cond
	      (network-is-limiting-factor-p
	       (enqueue-resumable-objects-waiting-for-unclog
		 resumable-object
		 icp-socket
		 minimnal-bandwidth-for-resumable-sequence-range)
	       (handle-throw
		 (suspend-object-passing-transmission
		   resumable-object
		   resumable-node
		   nil ;reschedule-p
		   )))
	      (t
	       (handle-throw
		 (suspend-object-passing-transmission
		   resumable-object
		   resumable-node)))))
	  (allocate-bandwidth-for-resumable-node
	    bandwidth-needed
	    resumable-node
	    resumable-object)
	  (if element-type?
	      (write-icp-add-homogeneous-history-range
		resumable-node
		number-of-cached-elements
		element-type?
		cached-interning-details
		ring-index-of-first-uncached-element
		number-of-uncached-elements
		uncached-interning-details
		uncached-timestamps-use-float-array-p)
	      (write-icp-add-history-range
		resumable-node
		number-of-cached-elements
		cached-interning-details
		ring-index-of-first-uncached-element
		number-of-uncached-elements
		uncached-interning-details
		uncached-timestamps-use-float-array-p
		uncached-values-use-float-array-p))
	  (unless (all-history-elements-sent-p resumable-node)
	    (handle-throw
	      (suspend-object-passing-transmission
		resumable-object
		resumable-node))))))))



(defun transmit-resumable-node
    (resumable-node resumable-object bandwidth-needed)
  (allocate-bandwidth-for-resumable-node
    bandwidth-needed
    resumable-node
    resumable-object)
  (resumable-node-typecase resumable-node
    (:value
      (write-icp-add-attribute-value
	(resumable-attribute-spec? resumable-node)
	(resumable-attribute-value resumable-node)
	(resumable-value-corresponding-index? resumable-node)))
    (:circular
      (write-icp-add-circular-attribute
	(resumable-attribute-spec? resumable-node)
	(resumable-circular-corresponding-icp-index resumable-node)))
    (otherwise
      (let ((class-name (resumable-instance-class-name resumable-node))
	    (corresponding-index-of-class-name?
	      (resumable-class-name-corresponding-index? resumable-node))
	    (attribute-spec (resumable-attribute-spec? resumable-node))
	    (circularity-index?
	      (get-icp-object-index-for-resumable-instance-node
		resumable-node
		current-icp-port))
	    (attribute-count (symbolic-attribute-count resumable-node)))
	(resumable-node-typecase resumable-node
          (:object
	    (write-icp-add-attribute-object
	      attribute-spec
	      class-name
	      corresponding-index-of-class-name?
	      attribute-count))
	  (:sequence)
	  (:structure)
	  (:object-vector
	    (write-icp-add-attribute-object-vector
	      attribute-spec
	      class-name
	      corresponding-index-of-class-name?
	      attribute-count
	      (resumable-sequence-length resumable-node)))
	  (:value-vector
	    (write-icp-add-attribute-value-vector
	      attribute-spec
	      class-name
	      corresponding-index-of-class-name?
	      attribute-count
	      (homogeneous-element-type? resumable-node)
	      (resumable-sequence-length resumable-node)))
	  (:history
	    (write-icp-add-attribute-history-object
	      attribute-spec
	      class-name
	      corresponding-index-of-class-name?
	      attribute-count
	      (homogeneous-element-type? resumable-node)
	      (resumable-sequence-length resumable-node)
	      (internal-history-spec-for-object-passing resumable-node)
	      (dynamic-history-info-for-object-passing resumable-node)
	      (managed-float-array-p
		(cached-timestamp-subsequence-for-resumable-history?
		  resumable-node))
	      (managed-float-array-p
		(cached-value-subsequence-for-resumable-history?
		  resumable-node))))
	  (:object-list
	    (write-icp-add-attribute-object-list
	      attribute-spec
	      class-name
	      corresponding-index-of-class-name?
	      attribute-count
	      (resumable-sequence-length resumable-node)))
	  (:value-list
	    (write-icp-add-attribute-value-list
	      attribute-spec
	      class-name
	      corresponding-index-of-class-name?
	      attribute-count
	      (homogeneous-element-type? resumable-node)
	      (resumable-sequence-length resumable-node))))
	(when circularity-index?
	  (write-icp-add-resumable-circularity circularity-index?))
	(setf (node-itself-sent-p resumable-node) t)))))

(defmacro all-value-vector-elements-sent-p (resumable-value-vector-node)
  `(<f (highest-empty-value-vector-index ,resumable-value-vector-node) 0))

(defmacro some-value-list-elements-remain-p (resumable-value-list-node)
  `(internal-list-for-object-passing ,resumable-value-list-node))
       
(defun-allowing-unwind transmit-resumable-object
    (resumable-object resumable-node)
  (with-throw-handling transmit-resumable-object
    (prog* ((icp-socket (resumable-object-icp-socket resumable-object))
	    (icp-port (icp-output-port icp-socket)))
     transmit-sequence-contents-if-any
     (resumable-node-typecase resumable-node
       (:value-vector
	 (when (node-itself-sent-p resumable-node)
	   (let ((current-object
		   (resumable-instance-current-object resumable-node)))
	     ;; Not sure if following form is necessary, but it is there in case
	     ;; the internal array was replaced while the transmission task was
	     ;; suspended (say because it was resized).
	     (setf (internal-vector-for-object-passing resumable-node)
		   (get-internal-array-for-object-passing current-object))
	     ;; Following function call throws out of transmit-resumable-object if
	     ;; more vector elements remain (i.e., fails to reach the next goto).
	     (handle-throw
	       (transmit-resumable-value-vector-range
		 resumable-node
		 resumable-object
		 icp-port))
	     ;; Following goto is only executed if all vector elements have been
	     ;; transmitted.
	     (go get-next-node))))
       (:history
	 (when (node-itself-sent-p resumable-node)
	   (let ((current-object
		   (resumable-instance-current-object resumable-node)))
	     ;; Unlike the :value-vector case, the following form is certainly
	     ;; necessary, because modifying the "history-keeping spec" is capable
	     ;; of resizing history vectors or even changing their element-type.
	     (setf (internal-history-for-object-passing? resumable-node)
		   (get-history-ring-buffer-if-any current-object nil))
	     ;; Following function call throws out of transmit-resumable-object if
	     ;; more history elements remain (i.e., fails to reach the next goto).
	     (handle-throw
	       (transmit-resumable-history-range
		 resumable-node
		 resumable-object
		 icp-port))
	     ;; Following goto is only executed if all history elements have been
	     ;; transmitted.
	     (go get-next-node))))
       (:value-list
	 (when (node-itself-sent-p resumable-node)
	   ;; Following function call throws out of transmit-resumable-object if
	   ;; more list elements remain (i.e., fails to reach the next goto).
	   (handle-throw
	     (transmit-resumable-value-list-range
	       resumable-node
	       resumable-object
	       icp-port))
	   ;; Following goto is only executed if all list elements have been
	   ;; transmitted.
	   (go get-next-node)))
       (otherwise (go transmit-node-itself)))
     transmit-node-itself
     (unless (and (resumable-instance-or-complex-value-node-p resumable-node)
		  (node-itself-sent-p resumable-node))
       (let ((bandwidth-needed
	       (bandwidth-needed-for-resumable-node resumable-node icp-port)))
	 (cond
	   ((resumable-object-bandwidth-unavailable-p
	      bandwidth-needed
	      icp-socket)
	    (enqueue-resumable-objects-waiting-for-unclog
	      resumable-object
	      icp-socket
	      bandwidth-needed)
	    ;; Following form throws out of transmit-resumable-object.
	    (handle-throw
	      (suspend-object-passing-transmission
		resumable-object
		resumable-node
		nil ;reschedule-p
		)))
	   ((time-slice-expired-p)
	    (let ((allocated-bandwidth
		    (resumable-object-allocated-bandwidth resumable-object)))
	      ;; The following form stores an estimate of the amount of bandwidth
	      ;; transmissible per timeslice for subsequent object-passing.
	      (when (>f allocated-bandwidth 0)
		(setq most-recent-bandwidth-per-timeslice?
		      (maxf allocated-bandwidth
			    minimum-bandwidth-per-timeslice)))
	      ;; Following form throws out of transmit-resumable-object.
	      (handle-throw
		(suspend-object-passing-transmission
		  resumable-object
		  resumable-node))))
	   (t
	    (handle-throw
	      (transmit-resumable-node
		resumable-node
		resumable-object
		bandwidth-needed))
	    (let ((parent? (resumable-node-parent-node? resumable-node)))
	      (when parent?
		;; Pop is OK here, since current-cons-in-inferior-attributes?
		;; shares with the inferior-attributes slot, which is reclaimed
		;; when the resumable-node structure is.
		(pop (current-cons-in-inferior-attributes? parent?))))
	    (resumable-node-typecase resumable-node
	      (:value-vector
		(unless (all-value-vector-elements-sent-p resumable-node)
		  (go transmit-sequence-contents-if-any)))
	      (:history
		(unless (all-history-elements-sent-p resumable-node)
		  (go transmit-sequence-contents-if-any)))
	      (:value-list
		(when (some-value-list-elements-remain-p resumable-node)
		  (go transmit-sequence-contents-if-any)))
	      (otherwise (go get-next-node)))))))
     get-next-node
     (cond
       ((resumable-instance-or-complex-value-node-p resumable-node)
	(let ((next-node?
		(prog1
		    (car (current-cons-in-inferior-attributes? resumable-node))
		  (when (resumable-object-vector-node-p resumable-node)
		    (incff (current-object-vector-index resumable-node))))))
	  (cond
	    (next-node?
	     (setq resumable-node next-node?))
	    (t (let ((ascension-target? (ascension-target? resumable-node)))
		 (cond
		   (ascension-target?
		    (write-icp-ascend-to-parent
		      (resumable-node-ascension-count? resumable-node))
		    (setq resumable-node ascension-target?)
		    (when (node-itself-sent-p resumable-node)
		      (go get-next-node)))
		   (t (write-icp-finish-building-object
			(resumable-object-allocated-bandwidth resumable-object))
		      (throw* :finished-transmitting-resumable-object t))))))))
     (t (setq resumable-node (resumable-node-parent-node? resumable-node))
	(when (node-itself-sent-p resumable-node)
	  (go get-next-node))))
   (setf (current-resumable-node resumable-object) resumable-node)
   (go transmit-sequence-contents-if-any))))

(defun-allowing-unwind check-toplevel-resumable-node-integrity
    (resumable-object)
  (with-throw-handling check-toplevel-resumable-node-integrity
    (let* ((toplevel-node (toplevel-resumable-node resumable-object))
	   (toplevel-object
	     (resumable-instance-current-object toplevel-node))
	   (toplevel-reference-number
	     (resumable-instance-reference-serial-number
	       toplevel-node)))
      (when (frame-has-been-reprocessed-p
	      toplevel-object
	      toplevel-reference-number)
	(throw*
	  :abort-transmitting-resumable-object
	  (icp-list
	    'rpc-object-argument-deleted
	    (tformat-text-string
	      "An object being sent as an RPC argument has been deleted")))))))



(def-catch-handling-function transmit-resumable-object-with-catch-handlers
    (resumable-object)
  ((:abort-transmitting-resumable-object (abort-info)
   (let* ((rpc-name? (resumable-object-rpc-name? resumable-object))
	  (error-message (second abort-info))
	  (error-string
	    (if rpc-name?
		(tformat-text-string
		  "The remote procedure call ~A ~
                   has been aborted while transmitting: ~A"
		  rpc-name?
		  error-message)
		(tformat-text-string
		  "A remote procedure call ~
                   has been aborted while transmitting: ~A"
		  error-message))))
     (receive-object-passing-remote-procedure-error
       resumable-object
       (first abort-info)
       error-string)
     (loop for info in abort-info
	   when (text-string-p info)
	     do (reclaim-text-string info)
	   finally (reclaim-icp-list abort-info))
     (reclaim-text-string error-string)
     (write-icp-abort-building-object
       (resumable-object-allocated-bandwidth resumable-object))
     (g2-reclaim-sending-resumable-object resumable-object)))
   (:finished-transmitting-resumable-object ()
    (g2-reclaim-sending-resumable-object resumable-object t))
   (:suspend-transmitting-resumable-object (new-resumable-node)
    (setf (current-resumable-node resumable-object) new-resumable-node)))
  (handle-throw
    (check-toplevel-resumable-node-integrity resumable-object))
  (handle-throw
    (transmit-resumable-object
      resumable-object
      (current-resumable-node resumable-object))))

(defun-allowing-unwind transmit-resumable-object-message-group
    (resumable-object icp-port)
  (setf (resumable-object-allocated-bandwidth resumable-object) 0)
  (setf (resumable-object-guessed-bandwidth-p resumable-object) nil)
  (writing-icp-message-group (icp-port)
    (send-icp-continue-building-resumable-object resumable-object)
    (transmit-resumable-object-with-catch-handlers resumable-object)))

(defun-simple try-to-transmit-resumable-object (resumable-object)
  (debug-object-passing
    "try-to-transmit-resumable-object ~s"
    resumable-object)
  (let ((icp-interface?
	  (resumable-object-icp-interface-frame? resumable-object)))
    (cond
      ;; ...
      ;; jh, 2/27/94.  The following cond-clause is not quite right, since it
      ;; ignores the possiblility that a G2/GSI returning values to a remote
      ;; procedure may be using an icp-socket that has been recycled.  At least,
      ;; we have to investigate how existing RPCs solve this problem.
      ((if icp-interface?
	   (frame-has-not-been-reprocessed-p
	     icp-interface?
	     (resumable-object-reference-serial-number resumable-object))
	   t ;; ... copout! (see above note)
	   )
       (let ((icp-socket (resumable-object-icp-socket resumable-object)))
	 (cond
	   ((or (icp-connection-being-shutdown? icp-socket)
		(not (icp-connection-open-p icp-socket)))
	    (g2-reclaim-sending-resumable-object resumable-object))
	   (t (transmit-resumable-object-message-group
		resumable-object
		(icp-output-port icp-socket))))))
      (t (g2-reclaim-sending-resumable-object resumable-object)))))




;;;; [18] Hooks into Existing G2 RPCs

;;;; [18.1] Hooks into G2 RPC Callers

;;;; [18.2] Transformation of G2 RPC Arglist

;; See ghw's 2/4/94 explanation of slot-name conventions for multiple
;; inheritance (MI) above the add-grammar-rules forms for remote-procedure-type
;; and friends below.

(defmacro body-of-get-system-attribute-names-for-object-passing
    (object system-includes)
  (avoiding-variable-capture (object system-includes)
    `(let ((system-attribute-names nil))
       ,@(loop for (nil nil attribute-spec-getter)
		   in object-passing-system-attribute-registry
	       collect
	       `(let ((attribute-spec?
			(,attribute-spec-getter ,object ,system-includes)))
		  (when attribute-spec?
		    (icp-push attribute-spec? system-attribute-names))))
       (nreverse system-attribute-names))))

(defun-simple get-attribute-names-for-object-passing
    (object
      included-attributes?
      excluded-attributes?
      included-system-attributes)
  (let* ((class-description-of-object (class-description-slot object))
	 (slot-descriptions-of-object
	   (slot-descriptions class-description-of-object))
	 (attribute-names? nil)
	 attribute-names-tail)
    (loop for slot-description in slot-descriptions-of-object
	  do
      (when (user-vector-slot-index? slot-description)
	(let (;;(unique-slot-name (unique-slot-name slot-description))
	      (base-slot-name (pretty-slot-name slot-description))
	      (slot-name-with-qualifier-if-necessary
		(denote-slot-using-slot-value-conses
		  slot-description
		  class-description-of-object)))
	  (when (cond
		  (included-attributes?
		   (member slot-name-with-qualifier-if-necessary
			   included-attributes?
			   :test #'equal))
		  (excluded-attributes?
		   (not (member slot-name-with-qualifier-if-necessary
			   excluded-attributes?
			   :test #'equal)))
		  (t t))
	    (let* ((new-attribute-name
		     (make-resumable-attribute-name
		       (if (consp slot-name-with-qualifier-if-necessary)
			   (second slot-name-with-qualifier-if-necessary)
			   nil)
		       base-slot-name))
		   (new-attribute-name-cons
		     (icp-cons new-attribute-name nil)))
	      (if attribute-names?
		  (setf (cdr attribute-names-tail) new-attribute-name-cons)
		  (setq attribute-names? new-attribute-name-cons))
	      (setq attribute-names-tail new-attribute-name-cons)))
	  (when (consp slot-name-with-qualifier-if-necessary)
	    (reclaim-slot-value-list slot-name-with-qualifier-if-necessary)))))
    (nconc (body-of-get-system-attribute-names-for-object-passing
	     object
	     included-system-attributes)
	   attribute-names?)))

(defun-simple writable-exported-attribute-for-object-passing-p (item slot-name)
  (let ((virtual-attribute-structure? (virtual-attribute slot-name)))
    (if virtual-attribute-structure?
	(virtual-attribute-setter? virtual-attribute-structure?)
	(or (let*-while-true
		((slot-description?
		   (get-slot-description-of-frame slot-name item nil))
		 (slot-description-type?
		   (feature-assq 'type (slot-features slot-description?)))
		 (category-symbol
		   (category-symbol-given-slot-type slot-description-type?)))
	      (evaluation-value-to-category-function category-symbol))
	    (let*-while-true
		((alias?
		   (get-slot-name-for-alias-if-any slot-name item))
		 (alias-description?
		   (get-slot-description-of-frame alias? item nil))
		 (slot-description-type?
		   (feature-assq 'type (slot-features alias-description?)))
		 (category-symbol
		   (category-symbol-given-slot-type slot-description-type?)))
	      (evaluation-value-to-category-function category-symbol))))))

(defun-simple get-exported-attribute-names-for-object-passing
    (item included-attributes? excluded-attributes? included-system-attributes)
  (let* ((class-description-of-item (class-description-slot item))
	 (slot-descriptions-of-item
	   (get-list-of-all-user-visible-attributes class-description-of-item))
	 (attribute-names? nil)
	 attribute-names-tail)
    (loop for (slot-name) in slot-descriptions-of-item
	  do
      (when (and (writable-exported-attribute-for-object-passing-p
		   item
		   slot-name)
		 (cond
		   (included-attributes?
		    (memq slot-name included-attributes?))
		   (excluded-attributes?
		    (not (memq slot-name excluded-attributes?)))
		   (t t)))
	(let* ((new-attribute-name
		 (make-resumable-attribute-name nil slot-name))
		 (new-attribute-name-cons
		   (icp-cons new-attribute-name nil)))
	  (if attribute-names?
	      (setf (cdr attribute-names-tail) new-attribute-name-cons)
	      (setq attribute-names? new-attribute-name-cons))
	  (setq attribute-names-tail new-attribute-name-cons))))
    (reclaim-eval-tree slot-descriptions-of-item)
    (nconc (body-of-get-system-attribute-names-for-object-passing
	     item
	     included-system-attributes)
	   attribute-names?)))

(defun-simple make-toplevel-resumable-node
    (object included-attributes excluded-attributes included-system-attributes)
  (current-system-case
    (ab
      (cond
	#|
	((evaluation-sequence-p object)
	 (make-resumable-evaluation-sequence-node
	   object
	   nil
	   nil
	   nil
	   nil
	   nil
	   (g2-array-length object)
	   nil
	   nil))
	((evaluation-structure-p object)
	 (make-resumable-evaluation-structure-node
	   object
	   nil
	   nil
	   nil
	   nil
	   nil
	   (g2-array-length object)
	   nil
	   nil))
	|#
	(t
	 (let ((class-of-object (class object))
	       (serial-number (frame-serial-number object))
	       (attribute-names
		 (get-attribute-names-for-object-passing
		   object
		   included-attributes
		   excluded-attributes
		   included-system-attributes)))
	   (frame-class-case object
	     (value-array
	       (let ((toplevel-node
		       (make-resumable-value-vector-node
			 object
			 (copy-frame-serial-number serial-number)
			 attribute-names
			 (count-of-symbolic-attributes attribute-names)
			 nil
			 class-of-object
			 (g2-array-length object)
			 (get-internal-array-for-object-passing object)
			 nil)))
		 (g2-set-resumable-node-homogeneous-element-type
		   toplevel-node
		   object)
		 toplevel-node))
	     ((item-array g2-array) ;must follow value-array case!
	      (make-resumable-object-vector-node
		object
		(copy-frame-serial-number serial-number)
		attribute-names
		(count-of-symbolic-attributes attribute-names)
		nil
		class-of-object
		(g2-array-length object)
		(get-internal-array-for-object-passing object)
		nil))
	     (variable-or-parameter
	       (let ((history-spec?
		       (variable-or-parameter-history-specification? object)))
		 (cond
		   (history-spec?
		    (let ((toplevel-node
			    (make-resumable-history-node
			      object
			      (copy-frame-serial-number serial-number)
			      attribute-names
			      (count-of-symbolic-attributes attribute-names)
			      nil
			      class-of-object
			      0
			      nil))
			  (history-enclosure?
			    (variable-or-parameter-stored-histories? object))
			  (history?
			    (get-history-ring-buffer-if-any object nil)))
		      (when history?
			(copy-history-state-into-resumable-history-node
			  toplevel-node
			  history-enclosure?
			  history?
			  history-spec?))
		      (g2-set-resumable-node-homogeneous-element-type
			toplevel-node
			object)
		      toplevel-node))
		   (t (make-resumable-object-node
			object
			(copy-frame-serial-number serial-number)
			attribute-names
			(count-of-symbolic-attributes attribute-names)
			nil
			class-of-object
			nil)))))
	     (value-list
	       (let ((toplevel-node
		       (make-resumable-value-list-node
			 object
			 (copy-frame-serial-number serial-number)
			 attribute-names
			 (count-of-symbolic-attributes attribute-names)
			 nil
			 class-of-object
			 (get-internal-list-for-object-passing object)
			 (g2-list-length object)
			 nil)))
		 (g2-set-resumable-node-homogeneous-element-type
		   toplevel-node
		   object)
		 toplevel-node))
	     ((item-list g2-list) ;must follow value-list case!
	      (make-resumable-object-list-node
		object
		(copy-frame-serial-number serial-number)
		attribute-names
		(count-of-symbolic-attributes attribute-names)
		nil
		class-of-object
		(get-internal-list-for-object-passing object)
		(g2-list-length object)
		nil))
	     ;; The following clause must go after more specific object
	     ;; subclasses!
	     (object
	       (make-resumable-object-node
		 object
		 (copy-frame-serial-number serial-number)
		 attribute-names
		 (count-of-symbolic-attributes attribute-names)
		 nil
		 class-of-object
		 nil))
	     ;; the following clause must go last!
	     (item
	       (let ((exported-attribute-names
		       (get-exported-attribute-names-for-object-passing
			 object
			 included-attributes
			 excluded-attributes
			 included-system-attributes)))
		 (make-resumable-object-node
		   object
		   (copy-frame-serial-number serial-number)
		   exported-attribute-names
		   (length exported-attribute-names)
		   nil
		   class-of-object
		   nil)))
	     (t
	       #+development
	       (cerror "Resume, returning nil ~
                    (This behavior is what the user would get)"
		       "MAKE-TOPLEVEL-RESUMABLE-NODE: unknown thing ~a"
		       object)
	       nil))))))
	(gsi
	 ;; ...
	 )))

(defun-allowing-unwind make-sending-resumable-object-given-options
    (rpc-name
      rpc-object
      icp-socket
      interface-frame?
      priority
      included-attributes
      excluded-attributes
      included-system-attributes)
  (let* ((toplevel-resumable-node
	   (make-toplevel-resumable-node
	     rpc-object
	     included-attributes
	     excluded-attributes
	     included-system-attributes))
	 (resumable-object
	   (make-sending-resumable-object
	     rpc-name
	     rpc-object
	     toplevel-resumable-node
	     icp-socket
	     interface-frame?
	     priority
	     nil ;as-handle-p
	     included-attributes
	     excluded-attributes
	     included-system-attributes)))
    (set-index-of-circular-resumable-node
      rpc-object
      resumable-object
      toplevel-resumable-node)
    resumable-object))

(defun-simple var-rpc-info-from-index (descriptions description-index)
  (let ((description (var-general-description-from-index descriptions description-index)))
    (make-remote-procedure-item-info
      (getf description :include-attributes)
      (getf description :exclude-attributes)
      (getf description :include-system-attributes)
      (getf description :include-all-system-attributes)
      (getf description :include-all-system-attributes-except)
      (getf description :kind))))


;;; The function `transform-rpc-argument-or-result-list' returns nil if the
;;; transformation was successful, otherwise it returns an error message, a text
;;; string that the caller must reclaim.


(defun-allowing-unwind transform-rpc-argument-or-result-list
    (remote-procedure-declaration?
      arguments-or-results
      descriptions
      icp-socket
      interface-frame?
      priority
      argument-list-p ;as opposed to result list
      &optional return-info-list
                varargs-p)
  (when (and argument-list-p
	     (<f 0 (var-count descriptions))
	     (getf (var-general-description-from-index
		     descriptions (1-f (var-count descriptions)))
		   :all-remaining))
    (setq varargs-p t))
  (loop with current-computation-flags = current-computation-flags
	initially (setf (role-serve-inactive-objects?)
			(icp-socket-runs-while-inactive icp-socket))
	with info-count = (if argument-list-p
			      (var-count descriptions)
			      (length return-info-list))
	for argument-or-result in arguments-or-results
	for argument-or-result-cons on arguments-or-results
	for rest-args-p = nil then (or rest-args-p restp)
	for description-index = 0 then (if rest-args-p
					   description-index
					   (1+f description-index))
	for restp = (or rest-args-p
			(and varargs-p
			     (=f description-index (1-f info-count))))
	for argument-type-or-class
	    = (when argument-list-p
		(var-type-from-index descriptions description-index))
	for info
	    = (if argument-list-p
		  (var-rpc-info-from-index descriptions description-index)
		  (if restp
		      (car return-info-list)
		      (pop return-info-list)))
	for kind = (remote-procedure-item-info-kind info)
	for by-copy-with-handle-p = (eq 'by-copy-with-handle kind)
	for as-reference-p = (eq 'reference kind)
	for as-handle-p = (eq 'handle kind)
	for frame-p = (framep argument-or-result)
	with previous-sending-resumable-object? = nil
	with designation = nil
	do
    (cond
      ((and argument-type-or-class
	    (evaluation-integer-p argument-or-result)
	    (class-type-specification-p argument-type-or-class)
	    as-handle-p) ; An integer passed as an object handle
       (with-bifurcated-version (pass-item-as-handle-icp-version icp-socket)
	 (return-from transform-rpc-argument-or-result-list
	   (tformat-text-string
	     "The RPC argument or result ~NC was sent as a handle ~
             but the remote process is not equipped for item-passing"
	     argument-or-result))
	 (let* ((constant-value (evaluation-integer-value argument-or-result))
		(handled-object-exists-p
		  (when as-handle-p
		    (get-item-from-local-handle
		      constant-value
		      icp-socket))))
	   (cond
	     ((and as-handle-p (not handled-object-exists-p))
	      (return		 
		(tformat-text-string
		  "The RPC argument or result ~NC was sent as a handle but is ~
                    not the network handle for any object in this interface"
		  constant-value)))
	     (t
	      (let ((resumable-object-as-handle
		      (with-bifurcated-version (resumable-icp-version icp-socket)
			(make-sending-resumable-object-as-handle
			  (if remote-procedure-declaration?
			      (or designation
				  (setq designation
					(get-or-make-up-designation-for-block
					  remote-procedure-declaration?)))
			      'return-remote-procedure-result-as-handle)
			  constant-value
			  icp-socket
			  kind)
			(icp-cons kind constant-value))))
		(reclaim-evaluation-integer argument-or-result)
		;; Replace the temporary constant in the arg or result list.
		(setf (car argument-or-result-cons) resumable-object-as-handle)))))))

      ;; An object argument or result ...
      (frame-p
       (with-bifurcated-version (pass-item-as-copy-icp-version icp-socket)
	 (return-from transform-rpc-argument-or-result-list
	   (tformat-text-string
	     "The RPC argument or result ~NF is an item ~
             but the remote process is not equipped for item-passing"
	     argument-or-result))
	 (cond
	   ;; An object argument to be converted into a reference ...
	   ((and as-reference-p frame-p)
	    (let ((resumable-object-as-handle
		    (with-bifurcated-version (resumable-icp-version icp-socket)
		      (make-sending-resumable-object-as-handle
			(if remote-procedure-declaration?
			    (get-or-make-up-designation-for-block
			      remote-procedure-declaration?)
			    'return-remote-procedure-result-as-object-from-handle)
			argument-or-result
			icp-socket
			kind)
		      (icp-cons kind argument-or-result))))
	      ;; Replace the object in the arglist.
	      (setf (car argument-or-result-cons)
		    resumable-object-as-handle)))
	   
	   ;; An object argument to be converted into a handle ...
	   ((and as-handle-p frame-p)
	    (let ((registration-number
		    (ensure-registration-on-network
		      argument-or-result
		      interface-frame?)))
	      (let ((resumable-object-as-handle
		      (with-bifurcated-version (resumable-icp-version icp-socket)
			(make-sending-resumable-object-as-handle
			  (if remote-procedure-declaration?
			      (get-or-make-up-designation-for-block
				remote-procedure-declaration?)
			      'return-remote-procedure-result-as-object-from-handle)
			  registration-number
			  icp-socket
			  kind)
			(icp-cons kind argument-or-result))))
		;; Replace the object in the arglist.
		(setf (car argument-or-result-cons)
		      resumable-object-as-handle))))
	   ((with-bifurcated-version (rel4-rpc-protocol-supports-non-objects-icp-version icp-socket)
	      (not (of-class-p argument-or-result 'object))
	      nil)
	    (return-from transform-rpc-argument-or-result-list
	      (tformat-text-string
		"The RPC argument or result ~NF was sent by copy, but is not an object ~
                 and the remote process is not equipped to receive non-object items"
		argument-or-result)))
	   ;; An object arg or result to be built on the receiving side ...
	   (t	    
	    (let* ((handle
		     (when (and by-copy-with-handle-p frame-p)
		       (with-bifurcated-version (new-rpc-kinds-icp-version icp-socket)
			 (return-from transform-rpc-argument-or-result-list
			   (tformat-text-string
			     "The RPC argument or result ~NF was sent by copy with a handle ~
                      but the remote process is not equipped to receive by copy with a handle"
			     argument-or-result))
			 (if (with-bifurcated-version-for-output
				 (by-copy-with-handle-supports-references-icp-version icp-socket)
			       nil
			       (item-references-enabled-p icp-socket))
			     t
			     (ensure-registration-on-network argument-or-result interface-frame?)))))
		   (name
		     (if argument-list-p
			 (or designation
			     (setq designation
				   (get-or-make-up-designation-for-block
				     remote-procedure-declaration?)))
			 'return-remote-procedure-result))
		   (resumable-object
		     (with-bifurcated-version (resumable-icp-version icp-socket)
		       (make-sending-resumable-object-given-options
			 name argument-or-result icp-socket interface-frame? priority
			 (remote-procedure-item-info-included-attributes info)
			 (remote-procedure-item-info-excluded-attributes info)
			 (if (remote-procedure-item-info-include-all-system-attributes info)
			     (all-object-passing-system-attribute-names)
			     (remote-procedure-item-info-included-system-attributes info)))
		       (icp-list 'copy argument-or-result info handle))))
	      (with-bifurcated-version (resumable-icp-version icp-socket)
		  (progn
		    ;; Add forward and reverse links.
		    (when previous-sending-resumable-object?
		      (setf (next-resumable-object-in-rpc-arglist?
			      previous-sending-resumable-object?)
			    resumable-object))
		    (setf (previous-resumable-object-in-rpc-arglist?
			    resumable-object)
			  previous-sending-resumable-object?)
		    (setq previous-sending-resumable-object? resumable-object))
		  nil)
		
		;; Replace the object in the arg or result list.
		(setf (car argument-or-result-cons) resumable-object))))))
      ((and (with-bifurcated-version (values-as-handle-icp-version icp-socket)
	      nil
	      t)
	    as-handle-p
	    (or (evaluation-sequence-p argument-or-result)
		(evaluation-structure-p argument-or-result)))
       (register-all-items-in-value argument-or-result interface-frame?)
       (setf (car argument-or-result-cons)
	     (icp-cons 'handle argument-or-result)))       
      (t
       (with-bifurcated-version (resumable-icp-version icp-socket)
	 nil
	 (setf (car argument-or-result-cons)
	       (cond (as-reference-p
		      (icp-cons 'reference argument-or-result))
		     (t
		      (icp-list 'copy argument-or-result info nil)))))))
	finally (return nil)))

(defun-void register-all-items-in-value (value-or-item interface-frame)
  (cond ((evaluation-sequence-p value-or-item)
	 (loop for element being each evaluation-sequence-element of value-or-item
	       do (register-all-items-in-value element interface-frame)))
	((evaluation-structure-p value-or-item)
	 (loop for (key . val) being each evaluation-structure-pair of value-or-item
	       do (register-all-items-in-value val interface-frame)))
	((framep value-or-item)
	 (ensure-registration-on-network value-or-item interface-frame))))






;;;; [18.3] Modified Pre-object-passing G2 RPC Machinery


       






(defun get-rpc-priority-from-computation-context ()
  (cond
    ((rule-instance-p current-computation-instance)
     (ri-priority current-computation-instance))
    ((code-body-invocation-p
       current-computation-instance)
     (code-body-invocation-priority
       current-computation-instance))
    #+development
    (t (cerror
	 "Continue with the call (This behavior is what the user would get)"
	 "START-REMOTE-PROCEDURE: invoked outside a rule or procedure, ~
          with current-computation-instance bound to ~s"
	 current-computation-instance)
       default-procedure-evaluation-priority)))


(defun-allowing-unwind call-remote-procedure-after-checks
    (calling-code-body
      argument-list
      icp-socket?
      remote-procedure-declaration
      icp-interface)
  (let* ((remote-procedure-identifier
	   (make-outgoing-remote-procedure-identifier-from-declaration
	     remote-procedure-declaration))
	 (remote-procedure-call
	  (make-outgoing-remote-procedure-call
	    remote-procedure-identifier
	    remote-procedure-declaration
	    icp-socket?
	    icp-interface)))
    (setf (code-body-invocation-priority remote-procedure-call)
	  (code-body-invocation-priority calling-code-body))
    (setf (code-body-caller remote-procedure-call) calling-code-body)
    (proc-push remote-procedure-call (called-code-bodies calling-code-body))
    (setf (code-body-invocation-frame-serial-number remote-procedure-call)
	  (copy-frame-serial-number (current-frame-serial-number)))
    (setf (procedure-invocation-of-code-body remote-procedure-call) nil)
    (setf (called-code-bodies remote-procedure-call) nil)
    (setf (remote-procedure-identifier-caller remote-procedure-identifier)
	  remote-procedure-call)
    (with-bifurcated-version (resumable-icp-version icp-socket?)
      (loop for arg in argument-list
	    when (and (sending-resumable-object-p arg)
		      (not (transmit-resumable-object-as-handle-p arg)))
	      do (icp-push arg
			   (remote-procedure-identifier-resumable-objects
			     remote-procedure-identifier))
		 (setf (rpc-identifier-for-this-object? arg)
		       remote-procedure-identifier))
      nil)
    (send-rpc-call
      (icp-output-port icp-socket?)
      (code-body-invocation-priority remote-procedure-call)
      (remote-procedure-name-structure remote-procedure-declaration)
      remote-procedure-identifier
      argument-list)))




;;;; [19] Hooks into G2 RPC Value Return

;;;; [19.1] Hooks for G2 Sending Side to Return RPC Values



;;;; [19.2] Hooks for G2 Receiving Side to Get RPC Values
  
(defun-simple check-remote-procedure-result-list-types
       (returned-values
	return-descriptions
	remote-procedure-declaration)
  (loop for evaluation-value-or-frame? in returned-values
	for rest-return-p = nil then (or rest-return-p restp)
	for index = 0 then (if rest-return-p index (1+f index))
	for return-type = (var-type-from-index return-descriptions index)
	for return-description  = (var-general-description-from-index
				    return-descriptions index)
	for restp = (or rest-return-p (getf return-description :all-remaining))
	do
    (cond
      ((receiving-resumable-object-p evaluation-value-or-frame?))
      ((not (evaluation-value-p evaluation-value-or-frame?))
       (loop for temp-to-reclaim in returned-values
	     with resumable-objects-reclaimed-p = nil
	     do
	 (when (evaluation-value-p temp-to-reclaim)
	   (reclaim-evaluation-value temp-to-reclaim))
	 (unless resumable-objects-reclaimed-p
	   (when (receiving-resumable-object-p temp-to-reclaim)
	     (reclaim-receiving-resumable-object temp-to-reclaim)
	     (setq resumable-objects-reclaimed-p t))))
       ;;(reclaim-icp-list returned-values)
       ;; Write-stack-error throws out of this loop.
       (return-from check-remote-procedure-result-list-types
	 (tformat-text-string "The returned value was not of the type ~NT, ~
                               as required by the declaration for ~NF."
			      return-type
			      remote-procedure-declaration)))
      ;; From this point on, evaluation-value-or-frame? must be a temporary
      ;; constant, since this check is only run before
      ;; receiving-resumable-objects can be replaced by the objects they are
      ;; building.
      ((and (valid-datum-type-specification-p return-type)
	    (value-type-compatible
	      return-type
	      (evaluation-value-type evaluation-value-or-frame?))))
      ((and (eq 'handle (getf return-type :kind))
	    (evaluation-integer-p evaluation-value-or-frame?)
	    (let ((constant-value
		    (evaluation-integer-value evaluation-value-or-frame?)))
	      (and (let ((handled-object?
			   (get-item-from-local-handle
			     constant-value
			     current-icp-socket)))
		     (and handled-object?
			  (type-specification-type-p
			    handled-object?
			    return-type)))))))
      (t (loop for temp-to-reclaim in returned-values
	       with resumable-objects-reclaimed-p = nil
	       do
	   (when (evaluation-value-p temp-to-reclaim)
	     (reclaim-evaluation-value temp-to-reclaim))
	   (unless resumable-objects-reclaimed-p
	     (when (receiving-resumable-object-p temp-to-reclaim)
	       (reclaim-receiving-resumable-object temp-to-reclaim)
	       (setq resumable-objects-reclaimed-p t))))
	 ;;(reclaim-icp-list returned-values)
	 ;; Write-stack-error throws out of this loop.
	 (return-from check-remote-procedure-result-list-types
	   (tformat-text-string "The returned value ~A was not of the type ~NT, ~
                                 as required by the declaration for ~NF."
				(evaluation-value-value evaluation-value-or-frame?)
				return-type
				remote-procedure-declaration))))
	finally
	  (return nil)))

(defun-allowing-unwind check-that-remote-procedure-can-receive-values
  (procedure-index returned-values)
  (let* ((ok-p nil)
	 (remote-procedure-identifier
	   (lookup-remote-procedure-identifier-from-index procedure-index))
	 (remote-procedure-call
	   (when remote-procedure-identifier
	     (remote-procedure-identifier-caller remote-procedure-identifier)))
	 (caller
	   (when remote-procedure-call
	     (code-body-caller remote-procedure-call))))
    (when caller
      (let* ((remote-procedure-declaration
	       (remote-procedure-declaration-of-call remote-procedure-call))
	     (return-descriptions
	       (remote-procedure-returned-values-description
		 remote-procedure-declaration))
	     (formal-return-restp-index nil)
	     (caller-procedure-invocation
	       (procedure-invocation-of-code-body caller))
	     (*current-computation-frame*
	       (procedure-of-invocation caller-procedure-invocation))
	     (values-count (length returned-values))
	     (count (invocation-return-value-count caller)))
	(declare (type fixnum values-count count))
	(let ((i (1-f (var-count return-descriptions))))
	  (when (and (<=f 0 i)
		     (getf (var-general-description-from-index return-descriptions i)
			   :all-remaining))
	    (setq formal-return-restp-index i)))
	(cond
	  ((if formal-return-restp-index
	       (<f values-count (1-f (var-count return-descriptions)))
	       (/=f values-count (var-count return-descriptions)))
	   (signal-code-body-invocation-error
	     caller 'rpc-error 1
	     (tformat-text-string
	       "~A values were returned, but the remote procedure declaration ~
                ~a declares that ~a values would be returned."
	       values-count
	       (get-or-make-up-designation-for-block
		 remote-procedure-declaration)
	       (var-count return-descriptions))
	     nil nil nil nil nil))
	  ((>f count values-count)
	   (signal-code-body-invocation-error
	     caller 'rpc-error 1
	     (tformat-text-string
	       "Procedure ~a is requesting more values than ~a can return."
	       (get-or-make-up-designation-for-block 
		 (procedure-of-invocation
		   (procedure-invocation-of-code-body caller)))
	       (get-or-make-up-designation-for-block
		 remote-procedure-declaration))
	     nil nil nil nil nil))
	  (t (let ((error-string?
		     (check-remote-procedure-result-list-types
		       returned-values
		       return-descriptions
		       remote-procedure-declaration)))
	       (cond (error-string?
		      (signal-code-body-invocation-error
			caller 'rpc-error 1 error-string?
			nil nil nil nil nil)
		      nil)
		     (t
		      (setq ok-p t))))))))
    ok-p))

   



;;;; [20] Hooks into G2 RPC Error Handling







;;;; [21] G2 Grammar for RPC Argument and Return Types

(defun cdr-of-second-in-place (list)
  (nconc (phrase-list (first list) (cdr (second list))) (cddr list)))
  

(defun merge-object-passing-property-lists (list-of-property-lists)
  (loop with merged-property-list = nil
	for property-list in list-of-property-lists
	do (loop for property-list-element in property-list
		 do (phrase-push property-list-element merged-property-list))
	finally (return (nreverse merged-property-list))))

;;; The following add-grammar-rules form extends remote-procedure-declarations
;;; to accept objects that will be passed to, and received from, RPC calls.  It
;;; could be argued that this grammar should appear in the local variable
;;; specification of the calling procedure, but on the other hand, end-users
;;; might not need this extra complexity.

;; ghw, 2/4/94 in reply to jh:
;; The grammar for expressions is not yet in.  The attribute-name grammar
;; category will remain a symbol as it was before 4.0.  "::" now is an operator;
;; and for slots that accept class-qualified names, like the default overrides
;; slot, a phrase like "class :: attribute-name" will be prompted and accepted.
;; This will be parsed into a list like this (class-qualified-name class
;; attribute-name).

;; ghw, 2/16/94, to everyone:
;; I committed FRAMES4 with a function called
;; denote-slot-using-slot-value-conses which takes a slot-description and a
;; class-description and returns a class- qualified-name list in the form
;; (class-qualified-name <defining-class> (pretty-slot-name>) when that slot
;; description is not the default slot description of those slot descriptions in
;; the class description with the same pretty slot name; otherwise it returns
;; pretty-slot-name.  The class-qualified- name list is slot-value listed and
;; should be reclaimed by the caller.

;;; The following add-grammar-rules form produces a phrase-tree with the
;;; following layout:
;;;   (:type (class <class-name> &rest <object-passing-property-list> )
;;; where <object-passing-property-list> is a phrase-tree that can contain the
;;; following properties:

;;;   :as-handle-p                either t or nil
;;;   :as-reference-p             either t or nil
;;;   :exclude-attributes         phrase-tree 
;;;   :include-attributes         phrase-tree
;;;   :include-system-attributes  phrase-tree

;;; The :xxx-attributes properties are lists of unqualified or qualified
;;; attribute names.  (Unqualified attribute names are symbols; qualified names
;;; are icp-lists of symbols.)  If the property :as-handle-p is non-nil, none of
;;; the other properties can be non-nil.  If the property :exclude-attributes is
;;; non-nil, the property :include-attributes cannot be non-nil and vice versa.

  
(add-grammar-rules
  '(
    ;; jh, 2/2/94.  If we make class-for-object-passing transform to the "class"
    ;; category instead of "unreserved-symbol", the dreaded "a -> b -> c" bug
    ;; happens and check-remote-procedure-object-passing-type is given the
    ;; enclosing parse result, a cons instead of a symbol.
					;(class-for-object-passing unreserved-symbol 1
					; check-remote-procedure-object-passing-type)
    
    ;; Monadic, no object-passing options is handled below
    ;;   declare remote <name> ( class <class> ) ...

    ;; Monadic with object-passing options:
    ;;   declare remote <name>
    ;;     ( class <class> [
    ;;                      as handle |
    ;;                      as reference |
    ;;                      including attributes : <attributes> |
    ;;                      excluding attributes : <attributes>
    ;;                     ]
    ;;     ) ...
    (remote-procedure-type-list
     ('\( remote-procedure-type-1 '\))
     (2))
    (remote-procedure-type-list
     ('\( all-remaining-remote-procedure-type-1 '\))
     (2))

    (all-remaining-remote-procedure-type-1
     ('all 'remaining remote-procedure-type-1)
     (3 (:all-remaining t)) merge-object-passing-property-lists)
    (remote-procedure-type-1
     ('class class object-passing-kind-and-properties)
     (:type (class 2) . 3))
    (remote-procedure-type-1
     ('item-or-value object-passing-kind-and-properties)
     (:type item-or-datum . 2))
    (remote-procedure-type-1
     ('value object-passing-kind-and-properties)
     (:type datum . 2))
    (remote-procedure-type-1
     ('structure object-passing-kind-and-properties)
     (:type (structure) . 2))
    (remote-procedure-type-1
     ('sequence object-passing-kind-and-properties)
     (:type (sequence) . 2))

    ;; "Inline" (i.e., not parenthesized), no object-passing options:
    ;;   class <class>
    (remote-procedure-type ('class class)
     (:type (class 2)))

    (remote-procedure-type ('class class pass-object-as-handle-p)
     (:type (class 2) . 3))
    (remote-procedure-type ('class class pass-object-with-handle-p)
     (:type (class 2) . 3))

    ;; "Inline" with object-passing options is considered confusing because of
    ;; multiple comma scopes, and so is not offered.

    ;; Parenthesized, no object-passing options:
    ;;   ( class <class> )
    (remote-procedure-type ('\( 'class class '\))
     (:type (class 3)))
    (remote-procedure-type ('\( 'item-or-value '\))
     (:type item-or-datum))
    (remote-procedure-type ('\( 'value '\))
     (:type datum))
    (remote-procedure-type ('\( 'structure '\))
     (:type (structure)))
    (remote-procedure-type ('\( 'sequence '\))
     (:type (sequence)))

    ;; Parenthesized with object-passing options:
    ;;   ( class <class> [
    ;;                     as handle |
    ;;                     as reference |
    ;;                     including only the attributes : <attributes> |
    ;;                     excluding the attributes : <attributes>
    ;;                   ]
    ;;   )
    (remote-procedure-type
     ('\( 'class class object-passing-kind-and-properties '\))
     (:type (class 3) . 4))
    (remote-procedure-type
     ('\( 'item-or-value object-passing-kind-and-properties '\))
     (:type item-or-datum . 3))
    (remote-procedure-type
     ('\( 'value object-passing-kind-and-properties '\))
     (:type datum . 3))
    (remote-procedure-type
     ('\( 'structure object-passing-kind-and-properties '\))
     (:type (structure) . 3))
    (remote-procedure-type
     ('\( 'sequence object-passing-kind-and-properties '\))
     (:type (sequence) . 3))

    (object-passing-kind-and-properties
     object-passing-kind)
    (object-passing-kind-and-properties
     object-passing-properties)
    (object-passing-kind-and-properties
     (pass-object-with-handle-p object-passing-properties)
     (1 2) merge-object-passing-property-lists)
    (object-passing-kind-and-properties
     (object-passing-properties pass-object-with-handle-p)
     (1 2) merge-object-passing-property-lists)
    
    (object-passing-kind pass-object-as-handle-p)
    (object-passing-kind pass-object-with-handle-p)
    
    (pass-object-as-handle-p ('as 'handle) (:kind handle))
    (pass-object-with-handle-p ('with 'handle) (:kind by-copy-with-handle))

    (object-passing-properties
     (include/exclude-attributes-for-object-passing 'and
      include-system-attributes-for-object-passing)
     (1 3) merge-object-passing-property-lists)
    
    (object-passing-properties include/exclude-attributes-for-object-passing)
    (include/exclude-attributes-for-object-passing
     include-attributes-for-object-passing)
    (include/exclude-attributes-for-object-passing
     exclude-attributes-for-object-passing)

    (include-attributes-for-object-passing
     ('including 'only 'the 'user 'attributes '\: user-attribute-names)
     (:include-attributes 7) cdr-of-second-in-place)
    (include-attributes-for-object-passing
     ('including 'only 'the 'user 'attribute user-attribute-name)
     (:include-attributes (6)))
    (exclude-attributes-for-object-passing
     ('excluding 'the 'user 'attributes '\: user-attribute-names)
     (:exclude-attributes 6) cdr-of-second-in-place)
    (exclude-attributes-for-object-passing
     ('excluding 'the 'user 'attribute user-attribute-name)
     (:exclude-attributes (5)))

    (object-passing-properties include-system-attributes-for-object-passing)
    (include-system-attributes-for-object-passing
     ('including 'all 'system 'attributes)
     (:include-all-system-attributes t))
    (include-system-attributes-for-object-passing
     ('including 'all 'system 'attributes 'except '\:
      implemented-object-passing-system-attributes)
     (:include-all-system-attributes-except 7 :include-all-system-attributes t) cdr-of-second-in-place)
    (include-system-attributes-for-object-passing
     ('including 'the 'system 'attributes '\:
      implemented-object-passing-system-attributes)
     (:include-system-attributes 6) cdr-of-second-in-place)
    (include-system-attributes-for-object-passing
     ('including 'the 'system 'attribute
      implemented-object-passing-system-attribute)
     (:include-system-attributes (5)))

    ;; other rules for the implemented-object-passing-system-attribute category
    ;; are added by def-object-passing-system-attribute.
    (implemented-object-passing-system-attribute
     ('history 'of 'variable-or-parameter) history)
    
    (implemented-object-passing-system-attribute
     system-defined-attribute-name)
    ))

(add-grammar-rules-for-list
  'implemented-object-passing-system-attributes
  'implemented-object-passing-system-attribute)

(defun-for-system-procedure enable-references-for-item-passing ()
  (unless g2-to-g2-uses-references-p
    (with-permanent-gensym-float-creation
      (add-grammar-rules
	'((pass-object-as-handle-p ('as 'reference) (:kind reference))

	  (network-attribute-name-or-translation network-attribute-translation)

	  (network-attribute-translation
	   ('\( 'items 'of 'class item-class 'have 'attributes
	    list-of-class-attribute-translations '\) )
	   (class 5 8))
	  (network-attribute-translation
	   ('\( 'items 'of 'class item-class 'have
	    'all 'attributes 'in 'the 'attribute system-or-user-defined-attribute-name '\) )
	   (class 5 (* 12)))
	  
	  (list-of-class-attribute-translations class-attribute-translation)
	  (list-of-class-attribute-translations
	   (class-attribute-translation '\, list-of-class-attribute-translations)
	   (2 1 3) simplify-associative-operation)
	  
	  (class-attribute-translation system-or-user-defined-attribute-name)
	  (class-attribute-translation
	   (user-attribute-name 'having 'network 'name user-attribute-name)
	   (1 4))

	  (designation ('the 'network 'interface 'for designation)
	   (network-interface-for 5))
	  (unique-designation
	   ('the 'network 'interface 'for unique-designation)
	   (network-interface-for 5))
	  (simulation-designation
	   ('the 'network 'interface 'for simulation-designation)
	   (network-interface-for 5))

	  ;; remember about system-slot-overrides-for-consistency-checking,
	  ;; when putting these back!
	  (override-for-class-definition
	   ('item-reference-options '\: options-for-item-reference)
	   (item-reference-options 3 ((network-interface) ())))
	  (override-for-class-definition
	   ('names-of-remote-interface '\: name-or-names)
	   (names-of-remote-interface 3 ((network-interface) ())))
	  (override-for-class-definition
	   ('class-of-remote-interface '\: symbol)
	   (class-of-remote-interface 3 ((network-interface) ()))))))
    (setq g2-to-g2-uses-references-p t)
    (loop for class being the subclasses of 'network-interface
	  do
      (loop for slot-name in '(creation-attributes item-reference-options
			       names-of-remote-interface class-of-remote-interface)
	    for slot-description = (slot-description-from-class class slot-name)
	    do
	(setf (slot-features slot-description)
	      (delete 'do-not-put-in-attribute-tables
		      (slot-features slot-description)
		      :key #'car))))
    (loop with class = 'miscellaneous-parameters
	  for slot-name in '(interface-home-attribute local-item-home)
	  for slot-description = (slot-description-from-class class slot-name)
	  do
      (setf (slot-features slot-description)
	    (delete 'do-not-save
		    (delete 'do-not-put-in-attribute-tables
			    (slot-features slot-description)
			    :key #'car)
		    :key #'car)))
    (let ((entry (assq 'network-interface list-of-user-overridable-system-slots)))
      (setf (second entry) (nconc (second entry)
				  (gensym-list 'creation-attributes 'item-reference-options
					       'names-of-remote-interface 'class-of-remote-interface)))
      (setf (fourth entry) (nconc (fourth entry)
				  (gensym-list 'creation-attributes 'item-reference-options
					       'names-of-remote-interface 'class-of-remote-interface))))
    (copy-evaluation-truth-value evaluation-true-value)))

;; ... jh, 2/2/94.  Problem with "declare remote x ((class y))".  The second
;; open paren gets eaten by the click-to-overwrite mechanism.  Not sure if this
;; is a 4.0 nit or my mistake for having two parens in a row in the grammar.




;;;; [22] G2 System Procedures for Network Registration

;;; We cannot use the internal ICP object index mechanism directly, since an
;;; end-user can hold on to an object index long after it has been re-used.  In
;;; fact, the only way to prevent such reuse is to encode the frame serial
;;; number of the object into the handle.  But then we don't need to key the
;;; handle off the icp-port at all, and we can simply use the frame serial
;;; number as a handle.  This does not increase the risk of frame reuse beyond
;;; the already accepted improbable scenario where the frame serial of a new
;;; object is the same as the old due to fixnum wraparound.

;; jh, 4/25/94.  At first blush, registering the item on the input port seems
;; plausible, since we can then make use of the mechanism that looks up objects
;; given their corresponding ICP index.  Nevertheless, we have to register the
;; index in the output port of the ICP socket.  If we used the input port, we
;; would have to synchronize with the remote process, since at the time that we
;; are registering the item, the remote side might be in the middle of
;; establishing that very same index for another purpose and be on the verge of
;; sending it here.
;;
;; jh, 5/26/94.  Actually, we shouldn't use the ICP corresponding object
;; mechanism at all, since with that we run the risk of a user retaining a
;; handle past the point where the interface has been deactivated, reactivated,
;; and the handle reused with a different object.

;;; The function `ensure-registration-on-network' takes two arguments, a G2 item
;;; to be registered and and ICP interface item, currently (jh, 9/11/94) either
;;; an instance of gsi-data-service or g2-to-g2-data-service.  This function
;;; assumes that the ICP socket contained in the ICP interface is active, i.e.,
;;; it is an icp-socket structure whose icp-connection-open-p slot is non-nil
;;; and whose icp-connection-being-shutdown? slot is nil.  This assumption is
;;; necessary because in the special case where the G2 item is a GSI variable,
;;; ICP messages must be sent to the GSI process.

(defun-for-system-procedure register-on-network-lisp-side
    (rpc-object icp-interface)
  (declare (keeps-g2-local-variables-valid t))
  (macrolet ((assert-validity
		 (test error-symbol format-string &rest format-args)
	       `(unless ,test
		  (return-from register-on-network-lisp-side
		    (values
		      (make-evaluation-integer no-resumable-object-index)
		      (make-evaluation-symbol ',error-symbol)
		      (tformat-text-string ,format-string ,@format-args))))))
    (assert-validity (framep rpc-object)
      cannot-register-non-item
      "~A is not an item, and so cannot be registered on the network"
      rpc-object)
    (assert-validity (framep icp-interface)
      icp-interface-not-item
      "~A is not an item, and so cannot be an ICP interface"
      icp-interface)
    (assert-validity (or (frame-of-class-p icp-interface 'gsi-interface)
			 (frame-of-class-p icp-interface 'g2-to-g2-data-interface))
      no-icp-interface-capability
      "The object ~NF is neither a GSI nor a G2-to-G2 interface")
    (let ((icp-socket? (icp-socket-of-interface-object icp-interface)))
      (assert-validity icp-socket?
	no-icp-connection
	"There is no ICP connection for ~NF"
	icp-interface)
      (assert-validity (and (icp-connection-open-p icp-socket?)
			    (not (icp-connection-being-shutdown? icp-socket?)))
        icp-connection-not-open
	"The ICP connection for ~NF is not open"
	icp-interface)
      (let ((registration-number
	      (register-item-with-socket rpc-object icp-socket? nil)))
	(values (make-evaluation-integer registration-number)
		(make-evaluation-symbol 'no-error-in-register-on-network)
		(
		 copy-constant-wide-string #w""
		 ))))))

(defun-for-system-procedure get-item-from-network-handle-lisp-side
    (g2-network-handle icp-interface)
  (declare (keeps-g2-local-variables-valid t))
  (macrolet ((assert-validity
		 (test error-symbol format-string &rest format-args)
	       `(unless ,test
		  (return-from get-item-from-network-handle-lisp-side
		    (values
		      (make-evaluation-symbol 'no-such-network-item)
		      (make-evaluation-symbol ',error-symbol)
		      (tformat-text-string ,format-string ,@format-args))))))
    (let ((network-handle (evaluation-integer-value g2-network-handle)))
      (reclaim-evaluation-integer g2-network-handle)
      ;; Omitted fixnum check here, because it happened when arguments were
      ;; passed to the system procedure.
      (assert-validity (>f network-handle -1)
	out-of-range-handle
	"The handle ~A must be 0 or greater"
	network-handle)
      (assert-validity (framep icp-interface)
        icp-interface-not-item
	"~A is not an item, and so cannot be an ICP interface"
	icp-interface)
      (assert-validity
	(or (frame-of-class-p icp-interface 'gsi-interface)
	    (frame-of-class-p icp-interface 'g2-to-g2-data-interface))
	no-icp-interface-capability
	"The object ~NF is neither a GSI nor a G2-to-G2 interface")
      (let ((icp-socket? (icp-socket-of-interface-object icp-interface)))
	(assert-validity icp-socket?
	  no-icp-connection
	  "There is no ICP connection for ~NF"
	  icp-interface)
	(assert-validity
	   (and (icp-connection-open-p icp-socket?)
		(not (icp-connection-being-shutdown? icp-socket?)))
	  icp-connection-not-open
	  "The ICP connection for ~NF is not open"
	  icp-interface)
	(let ((network-registry-entry?
		(get-item-from-local-handle network-handle icp-socket?)))
	  (assert-validity
	    network-registry-entry?
	    no-such-item-registered
	    "There is no item registered for handle ~S under interface ~NF"
	    network-handle
	    icp-interface)
	  (values network-registry-entry?
		  (make-evaluation-symbol 'no-error-in-get-item-from-network-handle)
		  (
		   copy-constant-wide-string #w""
		   )))))))

(defun-for-system-procedure get-network-handle-from-item-lisp-side
    (rpc-object icp-interface)
  (declare (keeps-g2-local-variables-valid t))
  (macrolet ((assert-validity
		 (test error-symbol format-string &rest format-args)
	       `(unless ,test
		  (return-from get-network-handle-from-item-lisp-side
		    (values
		      (make-evaluation-integer no-resumable-object-index)
		      (make-evaluation-symbol ',error-symbol)
		      (tformat-text-string ,format-string ,@format-args))))))
    (assert-validity (framep rpc-object)
      cannot-register-non-item
      "~A is not an item, and so cannot have a network handle"
      rpc-object)
    (assert-validity (framep icp-interface)
      icp-interface-not-item
      "~A is not an item, and so cannot be an ICP interface"
      icp-interface)
    (assert-validity
      (or (frame-of-class-p icp-interface 'gsi-interface)
	  (frame-of-class-p icp-interface 'g2-to-g2-data-interface))
      no-icp-interface-capability
      "The object ~NF is neither a GSI nor a G2-to-G2 interface")
    (let ((icp-socket? (icp-socket-of-interface-object icp-interface)))
      (assert-validity icp-socket?
	no-icp-connection
	"There is no ICP connection for ~NF"
	icp-interface)
      (assert-validity (and (icp-connection-open-p icp-socket?)
			    (not (icp-connection-being-shutdown? icp-socket?)))
        icp-connection-not-open
	"The ICP connection for ~NF is not open"
	icp-interface)
      (let ((handle (get-icp-object-index-for-registered-item
		      rpc-object (icp-output-port icp-socket?))))
	(assert-validity handle
	  no-such-handle
	  "No handle for variable ~NF under ICP interface ~NF"
	  rpc-object
	  icp-interface)
	(values
	  (make-evaluation-integer handle)
	  (make-evaluation-symbol 'no-error-in-get-network-handle-from-item)
	  (make-wide-string 0))))))

(defun-for-system-procedure deregister-on-network-lisp-side
    (rpc-object-or-handle icp-interface)
  (declare (keeps-g2-local-variables-valid t))
  (macrolet ((assert-validity
		 (test error-symbol format-string &rest format-args)
	       `(unless ,test
		  (return-from deregister-on-network-lisp-side
		    (values
		      (copy-evaluation-truth-value evaluation-false-value)
		      (make-evaluation-symbol ',error-symbol)
		      (tformat-text-string ,format-string ,@format-args))))))
    (assert-validity (or (framep rpc-object-or-handle)
			 (evaluation-integer-p rpc-object-or-handle))
		     cannot-deregister-non-item
		     "~A is neither an item nor an integer, and so cannot be deregistered"
		     rpc-object-or-handle)
    (assert-validity (framep icp-interface)
		     icp-interface-not-item
		     "~A is not an item, and so cannot be an ICP interface"
		     icp-interface)
    (assert-validity
      (or (frame-of-class-p icp-interface 'gsi-interface)
	  (frame-of-class-p icp-interface 'g2-to-g2-data-interface))
      no-icp-interface-capability
      "The object ~NF is neither a GSI nor a G2-to-G2 interface")
    (let ((icp-socket? (icp-socket-of-interface-object icp-interface)))
      (assert-validity icp-socket?
		       no-icp-connection
		       "There is no ICP connection for ~NF"
		       icp-interface)
      (assert-validity (and (icp-connection-open-p icp-socket?)
			    (not (icp-connection-being-shutdown? icp-socket?)))
		       icp-connection-not-open
		       "The ICP connection for ~NF is not open"
		       icp-interface)
      (unless (framep rpc-object-or-handle)
	(let ((registered-item?
		(get-item-from-local-handle rpc-object-or-handle icp-socket?)))
	  (assert-validity registered-item?
			   no-such-item-registered
			   "There is no item registered for handle ~S ~
                  under interface ~NF"
			   rpc-object-or-handle
			   icp-interface)
	  (setq rpc-object-or-handle registered-item?)))
      (deregister-item-with-socket rpc-object-or-handle icp-socket?)
      ;; Following form is reached if arg was a frame (vide supra).
      (values (copy-evaluation-truth-value evaluation-true-value)
	      (make-evaluation-symbol 'no-error-in-deregister-on-network)
		(
		 copy-constant-wide-string #w""
		 )))))

(defun-for-system-procedure g2-local-home ()
  (declare (keeps-g2-local-variables-valid t))
  (let ((name (name-for-local-home)))
    (unless name
      (stack-error
	cached-top-of-stack
	"The system procedure g2-local-home was called, ~
         but the system table attribute local-item-home ~
         was not set properly"))
    name))

(defun-for-system-procedure g2-item-home (item)
  (declare (keeps-g2-local-variables-valid t))
  (with-slot-evaluation-value-from-user-attribute-if-present
      (value item 'item-home nil (name-for-local-home))
    (or value (name-for-local-home))))

(defun-for-system-procedure g2-lookup-network-interface-for-home (item-home)
  (let ((attribute (or (interface-home-attribute-function) 'names)))
    (if (eq attribute 'names)
	(loop with first-interface = nil
	      for interface in (frame-or-frames-with-this-name item-home)
	      when (frame-of-class-p interface 'network-interface)
		do (if first-interface
		       (return nil)
		       (setq first-interface interface))
	      finally (return first-interface))
	(loop for first-interface = nil
	      for interface being the class-instances of 'network-interface
	      for interface-home = (with-slot-evaluation-value-from-user-attribute-if-present
				       (value interface attribute nil nil)
				     value)
	      when (item-or-value-eql item-home interface-home)
		do (if first-interface
		       (return nil)
		       (setq first-interface interface))
	      finally (return first-interface)))))

(defun-for-system-procedure g2-item-identifying-attributes-for-network (item interface)
  (declare (keeps-g2-local-variables-valid t))
  (identifying-or-creation-attributes-of-item-for-interface item interface t))

(defun-for-system-procedure g2-item-creation-attributes-for-network (item interface)
  (declare (keeps-g2-local-variables-valid t))
  (identifying-or-creation-attributes-of-item-for-interface item interface nil))	

(defun-for-system-procedure g2-lookup-item-from-reference-attributes
    (identifying-attributes interface)
  (declare (keeps-g2-local-variables-valid t))
  (let ((current-network-interface interface))
    (allocate-evaluation-sequence
      (lookup-or-create-item-from-reference-attributes identifying-attributes nil nil nil))))

(defun-for-system-procedure g2-lookup-or-create-item-from-reference-attributes
    (identifying-attributes creation-attributes interface)
  (declare (keeps-g2-local-variables-valid t))
  (let ((current-network-interface interface))
    (lookup-or-create-item-from-reference-attributes identifying-attributes creation-attributes nil t)))

;; Note:   (MHD 2/14/00)
;; ;; Item-reference-parameters:
;; ;;  - was moved to miscellaneous-parameters, until 5.2
;; ;;  - then moved here (5.2 = 6.0 in development)
;; ;;  - then moved back in time for 6.0 final release
;; (def-system-frame item-reference-parameters g2-rpc3
;;   (show-uuids-in-attribute-tables nil (system) (save) (type yes-or-no))
;;   (interface-home-attribute
;;     names system do-not-save (do-not-put-in-attribute-tables)
;;     (type interface-home-attribute))
;;   (local-item-home
;;     nil system do-not-save (do-not-put-in-attribute-tables)
;;     (type local-item-home)))
;; 
;; (def-class-method install-system-table (item-reference-parameters)
;;   (setq cached-name-for-local-home nil)
;;   nil)
;; 
;; (def-class-method deinstall-system-table (item-reference-parameters)
;;   (setq cached-name-for-local-home nil)
;;   nil)
;;
;; Note that interface-home-attribute and local-item-home were never DECLARED
;; savable in KBs.  However, there's code here that may (needs research!) have
;; been reachable that would have enabled its saving in KBs, and apparently
;; enabled references in item passing generally for that KB (and the session?!).
;; Hence, the special def-references-slot macro, which has always been here to
;; deal with that possibility. (MHD 2/14/00)

(defmacro def-references-slot (name)
  `(def-absent-slot-putter ,name (item new-value)
     (declare (ignore item))
     (enable-references-for-item-passing)
     (change-slot-value miscellaneous-parameters ',name new-value)
     new-value))

(def-references-slot interface-home-attribute)
(def-references-slot local-item-home)


;; The following is here just to let us safely reload, and then get rid of
;; item-reference-parameter system-table instances.  Note, too, that misc.
;; param.'s are forward referenced, so they have to be accessed with
;; get-slot-value.  (MHD 2/14/00)

(def-substitute-for-old-class item-reference-parameters miscellaneous-parameters
  last-kb-flags-saved-with-item-reference-parameters)

(def-absent-slot-putter show-uuids-in-attribute-tables (item-reference-parameters value)
  (declare (ignore item-reference-parameters))
  (change-slot-value miscellaneous-parameters 'item-reference-parameters value))

;; Actually, it would be nice if this worked, but it is apparently not called!
;; (MHD 4/2/00)


;;; The `fix-frame-with-substitute-class' is analogous to the same-named method
;;; for debugging parameters.  In the case of debugging parameters, it is called
;;; for frames substituted for tracing-and-breakpoint-parameters or
;;; debugging-message-and-breakpoint-parameters.  Here it is called for frames
;;; substituted for item-reference-parameters.  This is for the release pending
;;; 2/23/00.

(def-class-method fix-frame-with-substitute-class (miscellaneous-parameters)
  (let ((installed-miscellaneous-parameters?
	  (loop for x being each class-instance of 'miscellaneous-parameters
		when (this-system-table-is-installed? x)
		  return x)))
    (when installed-miscellaneous-parameters?
      (change-slot-value
	installed-miscellaneous-parameters?
	'show-uuids-in-attribute-tables
	(get-slot-value
	  miscellaneous-parameters
	  'show-uuids-in-attribute-tables))))
  (delete-frame miscellaneous-parameters))



(defun-simple show-uuids-in-attribute-tables-function ()
  (when (framep miscellaneous-parameters) ; nec.?
    (get-slot-value miscellaneous-parameters 'show-uuids-in-attribute-tables)))

(defun-simple interface-home-attribute-function ()
  (get-slot-value miscellaneous-parameters 'interface-home-attribute))

(defun-simple local-item-home-function ()
  (get-slot-value miscellaneous-parameters 'local-item-home))

(add-grammar-rules
  '((interface-home-attribute system-or-user-defined-attribute-name)

    (local-item-home ('look 'up 'local 'home 'from 'kb 'g2-to-g2-data-interfaces) (*))
    (local-item-home attribute)))

(def-slot-value-compiler interface-home-attribute (parse-result)
  (if (eq parse-result 'none)
      bad-phrase
      parse-result))

(def-slot-value-writer interface-home-attribute (slot-value)
  (write-name-denotation slot-value))

(def-slot-putter interface-home-attribute (frame value initializing?)
  (declare (ignore initializing?))
  (setq cached-name-for-local-home nil)
  (set-slot-value frame 'interface-home-attribute value)
  value)

(def-slot-value-compiler local-item-home (parse-result)
  parse-result)

(def-slot-value-writer local-item-home (slot-value)
  (if (and (consp slot-value) (eq (car slot-value) '*))
      (tformat "look up local home from kb g2-to-g2-data-interfaces")
      (write-evaluation-value slot-value)))

(def-slot-putter local-item-home (frame value initializing?)
  (declare (ignore initializing?))
  (setq cached-name-for-local-home nil)
  (set-slot-value frame 'local-item-home value)
  value)

(defvar cached-name-for-local-home nil)
(defparameter compute-name-for-local-home-p nil)

(defun name-for-local-home ()
  (when compute-name-for-local-home-p
    (if cached-name-for-local-home
	(copy-evaluation-value cached-name-for-local-home)
	(let ((local-home (local-item-home-function)))
	  (if (and local-home (not (and (consp local-home) (eq (car local-home) '*))))
	      (copy-evaluation-value (setq cached-name-for-local-home local-home))
	      (progn
		;; find a g2-to-g2-data-interface connecting to the local host
		;; and the port where we are listening.
		(loop with local-host-name = (get-local-host-name)
		      with listener-info-list = (get-local-host-addresses)
		      with local-interface-list = nil
		      for int being the class-instances of 'g2-to-g2-data-interface
		      for interface-configuration?
			  = (car (get-slot-value-if-any int 'icp-connection-specification))
		      when (and interface-configuration?
				(not (eq (first interface-configuration?) 'localnet))
				(or (equalw #w"localhost" (second interface-configuration?))
				    (equalw local-host-name (second interface-configuration?)))
				(loop with interface-protocol = (first interface-configuration?)
				      with interface-address = (third interface-configuration?)
				      for (protocol address) in listener-info-list
				      thereis (and (case interface-protocol
						     (tcp-ip (char=w #.%\T (charw protocol 0))))
						   (let ((str (tformat-text-string "~A" interface-address)))
						     (prog1 (string-equalw str address)
						       (reclaim-text-string str))))))
			do (gensym-push int local-interface-list)
		      finally
			(reclaim-network-addresses listener-info-list)
			(return
			  (cond ((or (null local-interface-list) (cdr local-interface-list))
				 (reclaim-gensym-list local-interface-list)
				 nil)
				(t
				 (let* ((interface (gensym-pop local-interface-list))
					(attribute
					  (or (interface-home-attribute-function) 'names))
					(value (frame-or-evaluation-value-user-attribute-value
						 interface attribute nil)))
				   (when value
				     (copy-evaluation-value
				       (setq cached-name-for-local-home value))))))))))))))

;; End file with [CR]


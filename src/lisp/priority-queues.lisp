; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module PRIORITY-QUEUES

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Andy Latto

;;; User level Priority queues

;;;; Priority queues.

;;; These don't really belong here; maybe move to their own file?
;;; Implemented as a heap.
;;; 
;;; 
;;; g2-add-to-priority-queue(queue: class priority-queue, item: item, priority: float) = truth-value
;;; 
;;; Adds the item to the queue if it is not present. Returns true if it
;;; is added, false if it was already there.
;;; 
;;; g2-remove-from-priority-queue(queue: class priority-queue, object: item) = truth-value
;;; 
;;; Removes the item from the queue if it is present. Returns true if it
;;; was removed, false if it was not there to remove.
;;; 
;;; g2-change-priority-in-priority-queue(queue: class priority-queue, object: item, new-priority: float) = truth-value
;;; 
;;; Changes the priority of the item in the queue. Returns true if item
;;; was present, false if it was not in the queue.
;;; 
;;; g2-get-highest-from-priority-queue(queue: class priority-queue) = item-or-none, float
;;; 
;;; Returns item with highest priority (that is, smallest float value) in queue, and its priority
;;; or (false, false) if queue is empty. Does not modify the queue.
;;;
;;; g2-remove-highest-from-priority-queue (queue: class priority-queue) = item-or-nonem priority
;;; 
;;; Returns item with highest priority (that is, smallest float value) in queue, and its priority,
;;; or (false, false) if queue is empty. Removes this item from the queue.
;;; 
;;; g2-priority-queue-is-empty(queue: class priority-queue) = boolean
;;; 


(def-class (priority-queue object (foundation-class priority-queue)
			   define-predicate
			   (class-export-comment
			     "priority queues allow insertion of items at priorities, and determination of and removal of top-priority item, all in logarithmic time"))
  (icon-description
    (:funcall-at-load-time
      create-icon-description
      50 50
      ((polychrome (g2-icon-outline . foreground)
		   (g2-icon-background . light-gray)
		   (g2-icon-light-shading . smoke)
		   (g2-icon-dark-shading . dark-gray)
		   (text-region . foreground))
       (variables)
       (background-layer)
       g2-icon-background (solid-rectangle (0 0) (50 50))
       g2-icon-light-shading (filled-polygon ((0 0) (50 0) (47 3) (3 3) (3 47) (0 50))
					     ((0 0) (50 0) (47 3))
					     ((3 3) (3 47) (0 50))
					     ((0 0) (47 3) (3 3))
					     ((3 3) (0 50) (0 0)))
       (lines (5 45) (44 45) (44 5))
       g2-icon-dark-shading
       (filled-polygon ((47 3) (50 0) (50 50) (0 50) (3 47) (47 47))
		       ((47 3) (50 0) (50 50)) ((50 50) (0 50) (3 47))
		       ((47 47) (47 3) (50 50)) ((50 50) (3 47) (47 47)))
       g2-icon-outline (outline (0 0) (0 50) (50 50) (50 0))
       g2-icon-outline (lines (44 5) (5 5) (5 45))
       ;; Put text that looks like this in the icon:  (P-Q, for Priority-Queue)
       ;;   P
       ;;    -
       ;;     Q
       text-region (text #w"P" ( 8 21) large)
       text-region (text #w"-" (21 32) large)
       text-region (text #w"Q" (30 43) large))
      nil nil nil nil nil
      ((g2-icon-outline 27 26 43 42)
       (g2-icon-background 0 0 50 50)
       (g2-icon-light-shading 0 0 50 50)
       (g2-icon-dark-shading 0 0 50 50)
       (g2-icon-outline 0 0 50 50)
       (text-region 8 6 20 26))))
  (priority-queue-object-array
    (:funcall make-priority-queue-initial-object-array)
    vector-slot system)
  (priority-queue-priority-array
    (:funcall make-priority-queue-initial-priority-array)
    vector-slot system)
  (priority-queue-object-table
    (:funcall make-priority-queue-initial-object-table)
    vector-slot system)
  (priority-queue-size 0 vector-slot system))


;;; Size argument here is an estimated current size; too small
;;; a value wastes time, and too large a value wastes space,
;;; but the value given does not affect correctness.
(defparameter priority-queue-initial-size 100)

(defun-simple make-priority-queue-initial-object-array ()
  (allocate-managed-array priority-queue-initial-size))

(defun-simple make-priority-queue-initial-priority-array ()
  (allocate-managed-array priority-queue-initial-size))

;;; Prime hash table sizes are better.
(defun-simple make-priority-queue-initial-object-table ()
  (make-eq-hash-table 101 nil nil))

(def-substitution-macro managed-float-< (x y)
  (<e (managed-float-value x)
      (managed-float-value y)))

(def-substitution-macro managed-float-> (x y)
  (>e (managed-float-value x)
      (managed-float-value y)))

(def-substitution-macro move-queue-object (objects priorities table old-index new-index)
  (setf (managed-svref objects new-index)
	(managed-svref objects old-index))
  (setf (managed-svref priorities new-index)
	(managed-svref priorities old-index))
  (setf (eq-gethash table (managed-svref objects old-index))
	new-index))

(def-substitution-macro set-queue-object (objects priorities table object priority index)
  (setf (managed-svref objects index) object)
  (setf (managed-svref priorities index) priority)
  (setf (eq-gethash table object) index))

(defmacro leftson (index)
  `(1+f (twicef ,index)))

(defmacro rightson (index)
  `(twicef (1+f ,index)))

(defmacro heap-parent (index)
  `(halff (1-f ,index)))


;;; To avoid problems when objects stored in a priority queue are
;;; deleted, we always work at the lower levels with item-references,
;;; rather than items. When an item-reference comes to the top of the
;;; queue, if it references a deleted item, we simply remove the
;;; reference, and proceed to the next item in the queue.

;;; These functions take/return arbitrary things, which in fact will always
;;; be item-references, and just implement priority queue functionality.
;;; They know nothing of reclaiming. (Except that starred ones reclaim the
;;; removed item, though not its priority).
;;; the 

;;; move-queue-object
;;; set-queue-object
;;; priority-queue-add
;;; priority-queue-remove
;;; priority-queue-remove-by-index
;;; priority-queue-change-priority

;;; These functions take/return objects. They know that they have to
;;; reference/dereference items from the lower level functions, and
;;; are also responsible for creating and reclaiming item references and
;;; floats as needed.

;;; get-and-remove-highest-priority
;;; clear-priority-queue
;;; All system procedures
;;; queue-contents

;;; get-highest-priority is an exception. It returns both the object and
;;; the reference, and priority and reference are both shared structure
;;; with queue; if you want to use these, you must copy them. This
;;; is done to optimize the common get-and-remove-highest-priority case,
;;; which calls get-highest-priority, but does not use the reference,
;;; and does not need to copy the priority, since it is being removed
;;; from the queue.

;;; The implementation depends on the fact that item-references are
;;; reference counted, and hence two item-references to the same item
;;; are always eq. This lets us use an eq hash table. We also use
;;; this fact for convenience in change-priority; in theory, we should
;;; be reclaiming the old item reference when we delete the item from
;;; the table, and making a new item reference. In fact, since all
;;; item references to the same item are the same, we don't do this.

;;; Add the specified object to the queue at the specified priority.
;;; Returns t.
;;; If the object is already in the queue, returns nil without
;;; adding the object to the queue. If you want its priority changed,
;;; instead, use priority-queue-change-priority
(defun priority-queue-add (queue object priority)
  (let* ((objects (priority-queue-object-array queue))
	 (priorities (priority-queue-priority-array queue))
	 (table (priority-queue-object-table queue))
	 (current-index (priority-queue-size queue))
	 (array-length (managed-array-length objects)))
    (when (neq (eq-gethash table object 'not-found) 'not-found) 
      (return-from priority-queue-add nil))
    (when (>=f current-index array-length)
      (setf array-length (twicef array-length))
      (setf objects
	    (adjust-managed-array objects array-length))
      (setf (priority-queue-object-array queue) objects)
      (setf priorities
	    (adjust-managed-array priorities array-length))
      (setf (priority-queue-priority-array queue) priorities)
      (setf table (priority-queue-rehash queue)))
    (loop
      (when (=f current-index 0) (return))
       (let ((parent-index (heap-parent current-index)))
	 (when (managed-float-> priority (managed-svref priorities parent-index))
	   (return))
	 (move-queue-object objects priorities table parent-index current-index)
	 (setq current-index parent-index)))
    (set-queue-object objects priorities table object priority current-index)
    (incf (priority-queue-size queue)))
  t)

;;; Returns the priority, if the
;;; object was in the queue, and nil otherwise.
(defun priority-queue-remove (queue object)
  (let ((index (eq-gethash
		 (priority-queue-object-table queue)
		 object
		 'not-found)))
    (unless (eq index 'not-found)
      (priority-queue-remove-by-index queue index))))

(defun priority-queue-remove-by-index (queue current-index)
  (let* ((objects (priority-queue-object-array queue))
	 (priorities (priority-queue-priority-array queue))
	 (table (priority-queue-object-table queue))
	 (new-queue-size (1-f (priority-queue-size queue)))
	 (priority (managed-svref priorities current-index))
	 (moving-object-priority (managed-svref priorities new-queue-size)))
    (eq-remhash table (managed-svref objects current-index))
    (loop
      (let* ((left (leftson current-index))
	     (right (1+f left)))
	(when (>=f left new-queue-size) (return))
	(if (>=f right new-queue-size)
	    (progn
	      (when (managed-float-< (managed-svref priorities left)
			moving-object-priority)
		(move-queue-object objects priorities table
				   left current-index)
		(setq current-index left))
	      (return))
	    (let ((left-priority (managed-svref priorities left))
		  (right-priority (managed-svref priorities right)))
	      (when (and (managed-float-> left-priority
			     moving-object-priority)
			 (managed-float-> right-priority
			     moving-object-priority))
		(return))
	      (let ((new-index (if (managed-float-< left-priority right-priority)
				   left
				   right)))
		(move-queue-object objects priorities table
				   new-index current-index)
		(setq current-index new-index))))))
    (unless (=f new-queue-size current-index)
      (move-queue-object objects priorities table
			 new-queue-size current-index))
    (setf (priority-queue-size queue) new-queue-size)
    ;; Here is where we could replace the arrays with smaller ones,
    ;; if that seemed like a good idea.
    priority)) 

;;; returns old priority, or nil of object was not previously
;;; in queue.
(defun priority-queue-change-priority (queue object new-priority)
  (let ((old-priority (priority-queue-remove queue object)))
    (when old-priority
	(progn (priority-queue-add queue object new-priority)
	       old-priority))))

;;; Returns two values; object with highest priority, and its
;;; priority. Does not modify queue. Returns nil and nil
;;; if queue is empty.
;;; Complication is that if this is an item that has been deleted
;;; (which we discover because it will have vanished from the table,
;;; since the table uses item references), we delete it from the queue
;;; and find the next one.

;;; Note that the priority and reference returned by get-highest-priority
;;; are both shared structure
;;; with the queue; if you want to use these, you must copy them. This
;;; is done to optimize the common get-and-remove-highest-priority case,
;;; which calls get-highest-priority, but does not use the reference,
;;; and does not need to copy the priority, since it is being removed
;;; from the queue.

(defun get-highest-priority (queue)
  (let ((result-ref nil)
	(result nil)
	(objects (priority-queue-object-array queue))
	(priorities (priority-queue-priority-array queue))
	(size (priority-queue-size queue)))
    (loop
      (when (zerop size)
	(setq result nil)
	(return))
      (setq result-ref (managed-svref objects 0))
      (setq result (evaluation-item-reference-referenced-item result-ref))
      (when result (return))
       ;; We've found a reference to a deleted item; try again.
      (decf size)
      (reclaim-managed-float (managed-svref priorities 0))
      (priority-queue-remove-by-index queue 0)
      (reclaim-evaluation-item-reference result-ref))
    (if result
	(values
	  result
	  result-ref
	  (managed-svref priorities 0))
	(values nil nil nil))))

;;; Returns two values; object with highest priority, and its
;;; priority. Returns values nil and nil
;;; if queue is empty. Removes returned object from the queue.
(defun get-and-remove-highest-priority (queue)
  (multiple-value-bind (object object-ref priority)
      (get-highest-priority queue)
    (when priority
      (priority-queue-remove queue object-ref)
      (reclaim-evaluation-item-reference object-ref))
    (values object priority)))

(defun clear-priority-queue (queue)
  (let* ((objects (priority-queue-object-array queue))
	 (priorities (priority-queue-priority-array queue))
	 (table (priority-queue-object-table queue))
	 (size (priority-queue-size queue))
	 (array-length (managed-array-length objects)))
    (reclaim-eq-hash-table table)
    (setf (priority-queue-object-table queue)
          (make-eq-hash-table (1+f array-length) nil nil)) ;; new table size will match the object array size
    (loop for index from 0 below size do
      (reclaim-managed-float (managed-svref priorities index))
      (setf  (managed-svref priorities index) nil)
      (reclaim-evaluation-item-reference (managed-svref objects index))
      (setf  (managed-svref objects index) nil))
    (setf (priority-queue-size queue) 0)))

(def-class-method deactivate (priority-queue)
  (clear-priority-queue priority-queue))

(def-slot-value-reclaimer priority-queue-object-table (value frame)
  (reclaim-eq-hash-table value)
  (setf (priority-queue-object-table frame) nil))

;;; We need a reclaimer here, because we have to reclaim the
;;; the contents of the array, which are item references (hence
;;; evaluation values, not slot values
(def-slot-value-reclaimer priority-queue-object-array (value frame)
  (loop for index from 0 below (priority-queue-size frame)
	do
    (reclaim-evaluation-item-reference (managed-svref value index))
      (setf  (managed-svref value index) nil))
  (reclaim-managed-array value)
  (setf (priority-queue-object-array frame) nil))

;;; We need a reclaimer here, so that things past size (which we
;;; don't bother to nil out) don't get double-reclaimed.
(def-slot-value-reclaimer priority-queue-priority-array (value frame)
  (loop for index from 0 below (priority-queue-size frame)
	do (reclaim-managed-float (managed-svref value index))
	finally
	  (reclaim-managed-array value)))

;;; Note that if the object is successfully added to the queue,
;;; we do not reclaim the priority, a managed-float, because this
;;; is now owned by the priority queue. It will get reclaimed when
;;; this item is removed from the queue, or when the queue is reclaimed.
(defun-for-system-procedure g2-priority-queue-push
    (queue object priority)
  (declare (keeps-g2-local-variables-valid t))
  (let* ((object-ref
	   (get-reference-to-item object))
	 (result
	   (priority-queue-add queue
			       object-ref
			       priority)))
    (unless result
      (reclaim-managed-float priority)
      (reclaim-evaluation-item-reference object-ref))
    (make-evaluation-boolean-value result)))

;;; Note that if the object is successfully added to the queue,
;;; we do not reclaim the new priority, a managed-float, because this
;;; is now owned by the priority queue. It will get reclaimed when
;;; this item is removed from the queue, or when the queue is reclaimed.
(defun-for-system-procedure g2-priority-queue-change-priority
    (queue object new-priority)
  (declare (keeps-g2-local-variables-valid t))
  (let* ((object-ref  (get-reference-to-item object))
	 (old-priority? (priority-queue-change-priority
			  queue
			  object-ref
			  new-priority)))
    ;; This is sort of a kludge; we should be reclaiming the "old"
    ;; object ref, which we remove from the queue, not the "new" object-ref
    ;; which we are inserting into the queue. But since item-references
    ;; are reference counted, it's the same eq object, so it all works out.
    ;; The whole implementation depends on this fact anyway, since
    ;; it uses an eq hash table for the object references.
    (reclaim-evaluation-item-reference object-ref)
    ;; We need to know whether it was found, to return an
    ;; appropriate truth-value. So we need a boolean that
    ;; tells us whether it was found, that can be used
    ;; even after the old priority is reclaimed.
    (let ((found-in-queue (not (null old-priority?))))
      (if found-in-queue
	(reclaim-managed-float old-priority?)
	(reclaim-managed-float new-priority))
      (make-evaluation-boolean-value found-in-queue))))

(defun-for-system-procedure g2-priority-queue-remove-element
    (queue object)
  (declare (keeps-g2-local-variables-valid t))
  (let* ((object-ref (get-reference-to-item object))
	 (old-priority (priority-queue-remove
			 queue
			 object-ref))
	 (result (make-evaluation-boolean-value old-priority)))
    ;; We have to reclaim the object ref twice (that is,
    ;; decrement its reference count by 2); Once for the
    ;; increment we have performed in this function, and
    ;; once because it has been removed from the table.
    (reclaim-evaluation-item-reference object-ref)
    (when old-priority
      (reclaim-managed-float old-priority)
      (reclaim-evaluation-item-reference object-ref))
    result))

(defun-for-system-procedure g2-priority-queue-top (queue)
  (declare (keeps-g2-local-variables-valid t))
  (multiple-value-bind (result result-ref priority)
      (get-highest-priority queue)
    (declare (ignore result-ref))
    (if result
	(values result (copy-managed-float priority))
      (values
	(make-evaluation-boolean-value nil)
	(make-evaluation-boolean-value nil)))))

(defun-for-system-procedure g2-priority-queue-pop
    (queue)
  (declare (keeps-g2-local-variables-valid t))
  (multiple-value-bind (object priority)
      (get-and-remove-highest-priority queue)
    (if object
	(values object priority)
      (values
	(make-evaluation-boolean-value nil)
	(make-evaluation-boolean-value nil)))))

(defun-for-system-procedure g2-priority-queue-is-empty (queue)
  (declare (keeps-g2-local-variables-valid t))
  (make-evaluation-boolean-value (not (get-highest-priority queue))))

  
(defun-for-system-procedure g2-priority-queue-get-priority (queue object)
  (declare (keeps-g2-local-variables-valid t))
  (let* ((object-ref
	   (get-reference-to-item object))
	 (table
	   (priority-queue-object-table queue))
	 (index
	   (eq-gethash table object-ref 'not-found)))
    (if (eq index 'not-found)
	(values
	  (make-evaluation-boolean-value nil)
	  (make-evaluation-boolean-value nil))
	(values 
	  (make-evaluation-boolean-value t)
	  (copy-managed-float (managed-svref
				(priority-queue-priority-array queue)
				index))))))

;;; returns a list of (item . priority) pairs, in order, with the
;;; highest priority (lowest number) first. This is a destructive
;;; operation, that empties the queue.
(defun queue-contents (queue)
  (let ((result nil))
    (loop
      (multiple-value-bind (object priority)
	  (get-and-remove-highest-priority queue)
	(if object
	    (eval-push (eval-cons object priority) result)
	    (return))))
    (nreverse result)))

;;; takes the list returned by queue-contents, and adds the items
;;; back into the queue.
(defun rebuild-priority-queue (pairs queue)
  (loop for (item . priority) in pairs
	do
    (priority-queue-add queue (get-reference-to-item item) priority)))

(def-virtual-attribute g2-priority-queue-number-of-entries
    ((class priority-queue)
     integer
     (exclude-from-wildcard-denotation t))
  :event-updates nil
  :initial ((class) (declare (ignore class)) 0)
  :getter ((priority-queue)
	   (let* ((queue-contents
		    (queue-contents priority-queue))
		  (result (length queue-contents)))
	     (rebuild-priority-queue queue-contents priority-queue)
	     (loop for pair in queue-contents
		   do (reclaim-eval-cons pair)
	       finally (reclaim-eval-list queue-contents))
	     result)))

(def-virtual-attribute g2-priority-queue-sequence
    ((class priority-queue)
     (or (no-item) (sequence))
     (exclude-from-wildcard-denotation t))
  :event-updates nil
  :initial ((class) (declare (ignore class)) 0)
  :getter ((priority-queue)
	   (if (active-p priority-queue)
	       (let* ((queue-contents
			(queue-contents priority-queue))
		      (structure-list
			(loop for pair in queue-contents
			      collect
			      (allocate-evaluation-structure-inline
				'entry
				(car pair)
				'priority
				(copy-managed-float (cdr pair)))
				using eval-cons)))
		 (rebuild-priority-queue queue-contents priority-queue)
		 (loop for pair in queue-contents
		       do (reclaim-eval-cons pair)
		       finally (reclaim-eval-list queue-contents))
		 (allocate-evaluation-sequence structure-list))
	       nil)))



;;; Obsolete, with no cap, since it gives answer that may include
;;; deleted items in the count. now we have
;;; an (expensive) hidden attribute that goes through the
;;; whole queue.
(defun-for-system-procedure g2-priority-queue-length
    (queue)
  (declare (keeps-g2-local-variables-valid t))
  (priority-queue-size queue))


(defun-for-system-procedure g2-priority-queue-clear
    (queue)
  (declare (keeps-g2-local-variables-valid t))
  (clear-priority-queue queue))

;;; For testing
;;; Not updated for new API yet.
#+development(progn
	       
;;; (item . priority) pairs currently in queue.
(defvar ins nil)
(defvar outs nil)

(defvar in-count 0)
(defvar out-count 0)

(defun verify-queue (queue)
  (let ((high (get-highest-priority queue))
	(real-high (car (sort ins #'< :key #'cdr))))
    (unless (eql high (car real-high))
      (error "Queue thinks highest priority item is ~A, but it's really ~A"
	     high (car real-high)))))

(defun random-add (queue ins outs)
  (when outs
    (let* ((index (random out-count))
	   (pair (elt outs index))
	   (object (car pair))
	   (priority (cdr pair)))
      (priority-queue-add queue object priority)
      (setq ins (cons pair ins))
      (incf in-count)
      (setq outs (delete pair outs))
      (decf out-count))))

(defun random-delete (queue ins outs)
  (when ins
    (let* ((index (random in-count))
	   (pair (elt outs index))
	   (object (car pair)))
      (multiple-value-bind (thing priority)
	  (priority-queue-remove queue object)
	(declare (ignore thing)) ;; should check this
	(let ((pair (find ins queue :key #'car)))
	  (unless (eql (cdr pair) priority)
	    (cerror "Priority problem: queue says priority of ~S is ~S, lists say ~S"
		    priority (cdr pair) (car pair)))
	  (setq ins (delete pair ins))
	  (decf in-count)
	  (setq outs (cons pair outs))
	  (incf out-count))))))

(defun random-priority-change (queue ins outs)
  (when ins
    (let* ((index (random in-count))
	   (pair (elt ins index))
	   (object (car pair))
	   (old-priority (cdr pair))
	   (new-priority (random 1.0)))
      (priority-queue-change-priority queue object new-priority)
      old-priority ;; *** Check that the returned priority is the correct old priority.
      (rplacd pair new-priority))))

)


;;; Rehash the table.
;;; It will be called when add priority queue and object array should extend the size.
;;; The function return the new table.
(defun priority-queue-rehash (queue)
  (let* ((queue-size (priority-queue-size queue))
         (hash-size (1+f (twicef queue-size)))
         (objects (priority-queue-object-array queue))
         (old-table (priority-queue-object-table queue))
         (table (make-eq-hash-table hash-size nil nil)))
    (reclaim-eq-hash-table old-table)
    (loop for index from 0 below queue-size
          do
      (setf (eq-gethash table (managed-svref objects index)) index))
    (setf (priority-queue-object-table queue) table)))
